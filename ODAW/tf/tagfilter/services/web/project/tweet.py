import datetime

from project.user import *
from datetime import timedelta


class Tweet:
    """
    Tweet class stores the tweet data that we use
    """

    def __init__(self, data):
        self.date = (data.created_at + timedelta(hours=-3)).time()
        self.user = User(data.author)
        self.id = data.id_str
        self.tweet_url = "https://twitter.com/{}/status/{}".format(
            self.user.get_username(), self.id
        )
        self.is_quote = data.is_quote_status
        self.hashtags = [tag["text"] for tag in data.entities["hashtags"]]

        """
        If is a quote tweet, creates new 3 attr:
            original_tweet_url contains url to original tweet that is quoted
            original_tweet_user contains an User object about original tweet user
            quote_text wich contains quote text. It tryies to get 240 version.
        """
        if self.is_quote:
            self.original_tweet_url = data.quoted_status_permalink["url"]
            self.original_tweet_user = User(data.quoted_status.author)
            if data.quoted_status.truncated:
                self.quote_text = data.quoted_status.extended_tweet["full_text"]
            else:
                self.quote_text = data.quoted_status.text

        if data.truncated:
            self.original_text = data.extended_tweet["full_text"]
        else:
            self.original_text = data.text

    def __str__(self):
        tweet_date = "[" + str(self.date) + "] "
        tweet_user = str(self.user)
        tweet_text = ""
        tweet_tags = "None" if self.hashtags == None else " ".join(self.hashtags)
        tweet_url = self.tweet_url
        if self.is_quote:
            tweet_text = (
                '"'
                + self.quote_text
                + '" '
                + "\n--- Retweeting @"
                + self.original_tweet_user.get_username()
                + "\n"
            )
        tweet_text += '"' + self.original_text + '" '

        return (
            "-" * 3
            + tweet_date
            + " "
            + tweet_user
            + " tweeted:\n"
            + tweet_text
            + "\nTags: "
            + tweet_tags
            + "\nUrl: "
            + tweet_url
        )

    def __gt__(self, other):
        # Greater operator used on sort
        if self.date > other.date:
            return True
        else:
            return False

    def get_date(self):
        return "[" + str(self.date) + "] "

    def get_user(self):
        return self.user

    def get_tags(self):
        return "" if not len(self.hashtags) else ("#" + " #".join(self.hashtags))

    def get_url(self):
        return self.tweet_url

    def get_text(self):
        tweet_text = '"' + self.original_text + '" '

        return tweet_text

    def get_is_quote(self):
        return self.is_quote

    def get_ret_user(self):
        return self.original_tweet_user

    def get_ret_text(self):
        return '"' + self.quote_text + '"'

    def get_id(self):
        return self.id
