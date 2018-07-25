import functools
import json

def to_json(fn):
    @functools.wraps(fn)
    def wrapped(*args, **kwargs):
        return json.dumps(fn(*args, **kwargs))
    return wrapped


if __name__ == "__main__":
    @to_json
    def get_data():
        return {'a': None}

    print(get_data())