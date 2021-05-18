from datetime import datetime


def log(*message):
    date = "[" + str(datetime.now()) + "]"
    text = "".join(message)
    print(date, text)
    return
