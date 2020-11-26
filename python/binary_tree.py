
class Node:
    def __init__(self, key=None, value=None, left=None, right=None, parent=None):
        self.key = key
        self.value = value
        self.left = left
        self.right = right
        self.parent = parent

    def has_left(self):
        return self.left

    def has_right(self):
        return self.right


class Binary_tree:
    def __init__(self):
        self.root = None
        self.size = 0

    def add(self, key, value):
        if self.root is not None:
            self._add(key, value, self.root)
        else:
            self.root = Node(key, value)
        self.size += 1

    def _add(self, key, value, current_root):
        if key < current_root.key:
            if current_root.has_left():
                self._add(key, value, current_root.left)
            else:
                current_root.left = Node(key, value, parent=current_root)
        else:
            if current_root.has_right():
                self._add(key, value, current_root.right)
            else:
                current_root.right = Node(key, value, parent=current_root)

    def get(self, key):
        if self.root is not None:
            res = self._get(key, self.root)
            if res:
                return res.value
            else:
                return None
        else:
            return None

    def _get(self, key, current_root):
        if not current_root:
            return None
        elif current_root.key == key:
            return current_root
        elif key < current_root.key:
            return self._get(key, current_root.left)
        else:
            return self._get(key, current_root.right)

    def print_post_order(self):
        print_list = []
        self._print_post_order(self.root, print_list)
        print(" ".join(map(str, print_list)))

    def _print_post_order(self, current_root, print_list):
        if current_root:
            self._print_post_order(current_root.left, print_list)
            self._print_post_order(current_root.right, print_list)
            print_list.append(current_root.key)

    def print_pre_order(self):
        print_list = []
        self._print_pre_order(self.root, print_list)
        print(" ".join(map(str, print_list)))

    def _print_pre_order(self, current_root, print_list):
        if current_root:
            print_list.append(current_root.key)
            self._print_pre_order(current_root.left, print_list)
            self._print_pre_order(current_root.right, print_list)

    def print_in_order(self):
        print_list = []
        self._print_in_order(self.root, print_list)
        print(" ".join(map(str, print_list)))

    def _print_in_order(self, current_root, print_list):
        if current_root:
            self._print_in_order(current_root.left, print_list)
            print_list.append(current_root.key)
            self._print_in_order(current_root.right, print_list)


def main():
    tree = Binary_tree()
    n = int(input())
    my_list = list(map(int, input().split()))
    for _ in my_list:
        tree.add(_, _+1)

    tree.print_post_order()


if __name__ == '__main__':
    main()
