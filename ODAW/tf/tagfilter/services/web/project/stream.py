import time

from tweepy import Stream, StreamListener, API, models
from project.tweet import *
from project.stdout import log


class Listener(StreamListener):
    """
    The Listener class handles tweets that are received from the twitter API-stream.
    """

    def __init__(self):
        super().__init__()
        self.limit = 3
        self.tweets = list()

    def set_limit(self, limit):
        self.limit = limit

    def on_disconnect(self, notice):
        log(notice)

    def on_connect(self):
        log("Stream API Connected")

    def on_limit(self):
        log("Rate Limit Exceeded, Sleep for 1 Min")
        time.sleep(60)

    def on_status(self, status):
        self.tweets.append((status.created_at.time(), Tweet(status)))

        # Controlling number o tweets to get
        if len(self.tweets) < self.limit:
            return True
        else:
            self.tweets.pop(0)
            return True

    def on_error(self, status):
        if status == 420:
            self.on_limit()
        else:
            log(status)
