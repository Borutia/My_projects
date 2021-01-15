class MetaClass(type):
    def __new__(cls, *args, **kwargs):
        print('New MetaClass')
        return type.__new__(cls, *args, **kwargs)

    def __init__(self, *args, **kwargs):
        print('Init MetaClass')

    def __call__(self, *args, **kwargs):
        return type.__call__(self, *args, **kwargs)

    def kek(cls):
        print('kek')


class Test(metaclass=MetaClass):
    def __init__(self, value):
        self.value = value


