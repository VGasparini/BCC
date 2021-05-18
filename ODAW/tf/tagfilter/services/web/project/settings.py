import os, json

from tweepy import OAuthHandler


class Credentials:
    def __init__(self):
        try:
            self.CONSUMER_KEY = os.environ["CONSUMER_KEY"]
            self.CONSUMER_SECRET = os.environ["CONSUMER_SECRET"]
            self.ACCESS_TOKEN = os.environ["ACCESS_TOKEN"]
            self.ACCESS_TOKEN_SECRET = os.environ["ACCESS_TOKEN_SECRET"]
        except:
            with open("credentials.json", "r") as json_file:
                secrets = json.load(json_file)
            self.CONSUMER_KEY = secrets["CONSUMER_KEY"]
            self.CONSUMER_SECRET = secrets["CONSUMER_SECRET"]
            self.ACCESS_TOKEN = secrets["ACCESS_TOKEN"]
            self.ACCESS_TOKEN_SECRET = secrets["ACCESS_TOKEN_SECRET"]

    def set_credentials(self, **args):
        self.CONSUMER_KEY = args["CONSUMER_KEY"]
        self.CONSUMER_SECRET = args["CONSUMER_SECRET"]
        self.ACCESS_TOKEN = args["ACCESS_TOKEN"]
        self.ACCESS_TOKEN_SECRET = args["ACCESS_TOKEN_SECRET"]

    def authenticate(self):
        auth = OAuthHandler(self.CONSUMER_KEY, self.CONSUMER_SECRET)
        auth.set_access_token(self.ACCESS_TOKEN, self.ACCESS_TOKEN_SECRET)
        return auth
