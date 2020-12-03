class PrivateExc:
    pass


class ZeroClass:
    pass


class FirstClass(ZeroClass):
    def __init__(self, value):
        self.value = value

    def display(self):
        print('FirstClass')

    def __setattr__(self, key, value):
        if key in self.privates:
            raise PrivateExc(key)
        else:
            self.__dict__[key] = value

    # def __new__(cls, *args, **kwargs):
    #    pass


class SecondClass(FirstClass):
    privates = ['val']

    def __init__(self, value):
        FirstClass.__init__(self, value)

    def display(self):
        print(self.value)

    def __str__(self):
        return str(self.value)

    def __repr__(self):
        return 'SecondClass({})'.format(self.value)

    def __add__(self, other):
        return SecondClass(self.value + other)

    def __radd__(self, other):
        return SecondClass(other + self.value)

    def __iadd__(self, other):
        self.value += other
        return self

    def __sub__(self, other):
        return SecondClass(self.value - other)

    def __lt__(self, other):
        return self.value > other

    def __gt__(self, other):
        return self.value < other

    def __call__(self, *args, **kwargs):
        print('call ', self.value)

    def __getitem__(self, index):
        return self.value[index]

    def __setitem__(self, index, value):
        self.value[index] = value

    def __iter__(self):
        # return self
        for num in self.value:
            yield num

    # def __next__(self):
    #     if self.start == len(self.value):
    #         raise StopIteration
    #     item = self.value[self.start]
    #     self.start += 1
    #     return item

    def __contains__(self, x):
        return x in self.value

    # def __getattr__(self, attr_name):
    #     if attr_name == 'name':
    #         return 'SecondClass'
    #     else:
    #         raise AttributeError(attr_name)

    def __delattr__(self, key):
        del self.__dict__[key]

    def __bool__(self):
        if len(self.value) > 0:
            return True
        return False

    def __len__(self):
        return len(self.value)

    def __del__(self):
        print('del class')


def create_any_class(class_name, *args, **kwargs):
    return class_name(*args, **kwargs)


def see_tree_of_class(class_name):
    for name in class_name.__bases__:
        print(class_name.__name__, name)
        see_tree_of_class(name)


class TestCounter:
    count = 0

    def __init__(self):
        self.name = 'lel'
        TestCounter.count += 1

    @staticmethod
    def print_count():
        print(TestCounter.count)

    @classmethod
    def print_count(cls):
        print(TestCounter.count)

    @property
    def name1(self):
        print(self.name)


class Attrs:
    def __init__(self):
        self.my_dict = {}

    def __getattr__(self, item):
        if item == 'name':
            return self.name
        else:
            raise AttributeError(item)

    # def __setattr__(self, key, value):
    #     if key == 'name':
    #         self.__dict__[key] = value
    #     else:
    #         raise AttributeError(key)

    def __getitem__(self, index):
        return self.my_dict[index]

    def __setitem__(self, index, value):
        self.my_dict[index] = value


def main():
    cl = Attrs()
    cl.name = 'lel'
    cl['kek'] = 'kek'
    # print(cl.name)
    # print(cl['kek'])
    # print(cl.__dict__)


if __name__ == '__main__':
    main()