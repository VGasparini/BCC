from utils import read_regex


class Regex:
    def __init__(self, file):
        self.regex = read_regex(file)

    def run_regex(self, raw):
        raw = list(raw)
        self.word = self.regex.format(raw[0], raw[2], raw[1])
        return self.word

    def __str__(self):
        return self.word
