def sanitize(args):
    t = []
    for tag in args:
        t.append(tag.lower())
    return sorted(t)


def gen_hash(list_tags):
    t = "".join(sanitize(list_tags))
    return str(hash(t))[-8:]
