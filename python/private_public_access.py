traceMe = False


def trace(*args):
    if traceMe: print('[' + ' '.join(map(str, args)) + ']')


def accessControl(faillf):
    def onDecorator(aClass):
        class onlnstance:
            def __init__(self, *args, **kwargs):
                self.__wrapped = aClass(*args, **kwargs)

            def __getattr__(self, attr):
                trace('get:', attr)
                if faillf(attr):
                    raise TypeError('private attribute fetch: ' + attr)
                # извлечение закрытого атрибута
                else:
                    return getattr(self.__wrapped, attr)

            def __setattr__(self, attr, value):
                trace(self, attr, value)
                if attr == '_onlnstance__wrapped':
                    self.__dict__[attr] = value
                elif faillf(attr):
                    raise TypeError('private attribute change: ' + attr)
                # изменение закрытого атрибута
                else:
                    setattr(self.__wrapped, attr, value)
        return onlnstance
    return onDecorator


def Private(*attributes):
    return accessControl(faillf=(lambda attr: attr in attributes))


def Public(*attributes):
    return accessControl(faillf=(lambda attr: attr not in attributes))


@Private('age', 'name')
class TestPrivate:
    def __init__(self, age, name):
        self.age = age
        self.name = name

    def print_info(self):
        print('{}: {}'.format(self.name, self.age))


@Public('print_info')
class TestPrivate:
    def __init__(self, age, name):
        self.age = age
        self.name = name

    def print_info(self):
        print('{}: {}'.format(self.name, self.age))


def main():
    test_private = TestPrivate(23, 'Dmitry')
    test_private.print_info()

    test_public = TestPrivate(23, 'Dmitry')
    test_public.print_info()


if __name__ == '__main__':
    main()