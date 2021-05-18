from project.settings import *
from project.stream import *
from project.stdout import log


class Extractor:
    """
    This class creates the data listener based on a list of tags to filter
    Each listener stores a list of tweets
    """

    def __init__(self, hashtag_to_track):
        self.credentials = Credentials().authenticate()
        try:
            self.api = API(
                self.credentials,
                wait_on_rate_limit=True,
                wait_on_rate_limit_notify=True,
            )
            self.api_owner = self.api.me()
        except:
            log("Error: Unable to authenticate")

        self.hashtag_to_track = hashtag_to_track
        self.streams = list()
        self.state = False

    def run(self):
        if not self.state:
            try:
                self.state = True
                atual_stream = ""
                for tag in self.hashtag_to_track:
                    listener = Listener()
                    # Setting limit to better network usage
                    listener.set_limit(3)
                    myStream = Stream(auth=self.api.auth, listener=listener)
                    atual_stream = myStream
                    myStream.filter(track=[tag], is_async=True)
                    self.streams.append(myStream)
            except Exception as e:
                atual_stream.disconnect()
                log(str(e))
                log.exit("Twitter stream disconnected")
