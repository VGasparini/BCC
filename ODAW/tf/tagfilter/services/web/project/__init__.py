import os
from time import sleep

from flask import Flask, render_template, request, redirect
from flask_sqlalchemy import SQLAlchemy

from project.stdout import log
from project.twitter_stream import Extractor
from project.utils import gen_hash

# Flask main file. It generate html page and read input data


# Global vars
tweets = list()
ids = set()
extractors = set()
limit = 5


def add_tweet(tweet):
    """
    Append to tweets list a tuple. Each tuple contains tags information and tweet information
    The tweet ID is added to an IDs set to prevent duplicated tweets
    """
    global tweets

    tweets.append((tweet[1], tweet[0]))
    ids.add(tweet[1].get_id())


def update(extractors):
    """
    Iterate above extractors list updating tweets extracted for each
    """
    global tweets

    for extractor in extractors:
        log("Retrieving data for tag:", str(extractor.hashtag_to_track))
        extractor.run()
        sleep(1)
        for stream in extractor.streams:
            for tweet in stream.listener.tweets:
                if not tweet[1].get_id() in ids:
                    add_tweet((*extractor.hashtag_to_track, tweet[1]))

    tweets.sort(reverse=True)


class App:
    def __init__(self):
        self.app = Flask(__name__)
        self.tags = set()

        @self.app.route("/", methods=["GET", "POST"])
        def index():

            if request.method == "POST":
                # Deal with diferrent buttons pressed

                if "tag_input" in request.form.keys():
                    # Add new tag from input field
                    data = list(request.form["tag_input"].split(";"))
                    for tag in data:
                        if tag not in self.tags:
                            self.tags.add(tag)
                            ex = Extractor([tag])
                            extractors.add(ex)

                elif "tag_button" in request.form.keys():
                    # Removes tag button when is pressed
                    data = request.form["tag_button"]
                    self.tags.remove(data)

                    # Remove tweets from that tag
                    to_delete = list()
                    for i in range(len(tweets)):
                        if tweets[i][1] == data:
                            to_delete.append(i)
                    for i in to_delete[::-1]:
                        tweets.pop(i)

                    # Destroys that tag stream
                    to_delete = list()
                    for i in extractors:
                        if data in i.hashtag_to_track:
                            for stream in i.streams:
                                log("Closing ", data, " stream")
                                stream.disconnect()
                            to_delete.append(i)
                    for i in to_delete[::-1]:
                        extractors.remove(i)
                else:
                    return redirect(request.url)

            sleep(1)
            # Controlling feed showing
            if len(extractors):
                while len(tweets) >= limit:
                    tweets.pop(0)
                update(extractors)

            return render_template(
                "index.html", tweets=tweets, tags=self.tags, recovery_code=""
            )

        @self.app.route("/recovery", methods=["GET", "POST"])
        def recovery():
            if request.method == "POST":
                recovery_code = request.form["hash_input"]
                query = db_select(recovery_code)
                if query:
                    self.tags = query
                    for tag in self.tags:
                        ex = Extractor([tag])
                        extractors.add(ex)
                    recovery_code = ""
            else:
                recovery_code = gen_hash(self.tags)
                query = db_select(recovery_code)
                if not query:
                    db_insert(recovery_code, self.tags)
            return render_template(
                "index.html", tweets=tweets, tags=self.tags, recovery_code=recovery_code
            )

    def run(self):
        port = int(os.environ.get("PORT", 5000))
        self.app.run(host="0.0.0.0", port=port)


app = App().app
app.config.from_object("project.config.Config")
db = SQLAlchemy(app)


class Tag(db.Model):
    __tablename__ = "tags"

    id = db.Column(db.Integer, primary_key=True)
    tags = db.Column(db.String(256), unique=True, nullable=False)

    def __init__(self, idx, tags):
        self.id = idx
        self.tags = tags


def db_insert(pk, data):
    instance = Tag(pk, ";".join(data))
    db.session.add(instance)
    db.session.commit()


def db_select(pk):
    query = Tag.query.get(pk)
    if query is None:
        return False
    else:
        return set(query.tags.split(";"))
