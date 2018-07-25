
class Value:
    def __init__(self):
        self.value = None

    def __get__(self, obj, type):
        return self.value

    def __set__(self, obj, value):
        self.value = value * (1 - obj.commission)

class Account:
    amount = Value()

    def __init__(self, commission):
        assert commission < 1.0
        self.commission = commission
