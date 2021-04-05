class Node:
    def __init__(self, value):
        self.parent = None
        self.left_child = None
        self.right_child = None
        self.value = value


class Binary_tree:
    def __init__(self):
        self.root = None

    def insert(self, value):
        if self.root is None:
            self.root = Node(value)
        else:
            self._insert(value, self.root)

    def _insert(self, value, current_root):
        if value < current_root.value:
            if current_root.left_child:
                self._insert(value, current_root.left_child)
            else:
                new_node = Node(value)
                new_node.parent = current_root
                current_root.left_child = new_node
        else:
            if current_root.right_child:
                self._insert(value, current_root.right_child)
            else:
                new_node = Node(value)
                new_node.parent = current_root
                current_root.right_child = new_node

    def inorder(self):
        self._inorder(self.root)

    def _inorder(self, current_root):
        if current_root.left_child:
            self._inorder(current_root.left_child)
        print(current_root.value)
        if current_root.right_child:
            self._inorder(current_root.right_child)

    def check_tree(self):
        return self._check_tree(self.root)

    def _check_tree(self, current_root):
        if current_root.left_child:
            if current_root.value < current_root.left_child.value:
                return False
            self._check_tree(current_root.left_child)
        elif current_root.right_child:
            if current_root.value > current_root.right_child.value:
                return False
            self._check_tree(current_root.right_child)
        return True

    def search(self, value):
        return self._search(value, self.root)

    def _search(self, value, current_root):
        if current_root is None:
            return None
        elif current_root.value == value:
            return current_root
        elif current_root.value > value:
            return self._search(value, current_root.left_child)
        else:
            return self._search(value, current_root.right_child)

    def minimum(self):
        return self._minimum(self.root)

    def _minimum(self, current_root):
        if current_root.left_child is None:
            return current_root
        return self._minimum(current_root.left_child)

    def maximum(self):
        return self._maximum(self.root)

    def _maximum(self, current_root):
        if current_root.right_child is None:
            return current_root
        return self._maximum(current_root.right_child)

    def successor(self, current_root):
        if current_root.right_child:
            return self._minimum(current_root.right_child)
        if current_root == self.maximum():
            return None
        parent = current_root.parent
        while parent.right_child == current_root:
            current_root = parent
            parent = parent.parent
        return parent

    def predecessor(self, current_root):
        if current_root.left_child:
            return self._maximum(current_root.left_child)
        parent = current_root.parent
        while parent.left_child == current_root:
            current_root = parent
            parent = parent.parent
        return parent

    def transplant(self, u, v):
        if not u.parent:
            self.root = v
        elif u == u.parent.left_child:
            u.parent.left_child = v
        else:
            u.parent.right_child = v
        if v:
            v.parent = u.parent

    def delete(self, current_root):
        if not current_root.left_child:
            self.transplant(current_root, current_root.right_child)
        elif not current_root.right_child:
            self.transplant(current_root, current_root.left_child)
        else:
            y = self._minimum(current_root.right_child)
            if y.parent != current_root:
                self.transplant(y, y.right_child)
                y.right_child = current_root.right_child
                y.right_child.parent = y
            self.transplant(current_root, y)
            y.left_child = current_root.left_child
            y.left_child.parent = y

    def display(self):
        lines, *_ = self._display_aux(self.root)
        for line in lines:
            print(line)

    def _display_aux(self, current_root):
        # No child.
        if current_root.right_child is None and current_root.left_child is None:
            line = '%s' % current_root.value
            width = len(line)
            height = 1
            middle = width // 2
            return [line], width, height, middle

        # Only left child.
        if current_root.right_child is None:
            lines, n, p, x = self._display_aux(current_root.left_child)
            s = '%s' % current_root.value
            u = len(s)
            first_line = (x + 1) * ' ' + (n - x - 1) * '_' + s
            second_line = x * ' ' + '/' + (n - x - 1 + u) * ' '
            shifted_lines = [line + u * ' ' for line in lines]
            return [first_line,
                    second_line] + shifted_lines, n + u, p + 2, n + u // 2

        # Only right child.
        if current_root.left_child is None:
            lines, n, p, x = self._display_aux(current_root.right_child)
            s = '%s' % current_root.value
            u = len(s)
            first_line = s + x * '_' + (n - x) * ' '
            second_line = (u + x) * ' ' + '\\' + (n - x - 1) * ' '
            shifted_lines = [u * ' ' + line for line in lines]
            return [first_line,
                    second_line] + shifted_lines, n + u, p + 2, u // 2

        # Two children.
        left, n, p, x = self._display_aux(current_root.left_child)
        right, m, q, y = self._display_aux(current_root.right_child)
        s = '%s' % current_root.value
        u = len(s)
        first_line = (x + 1) * ' ' + (n - x - 1) * '_' + s + y * '_' + (
                    m - y) * ' '
        second_line = x * ' ' + '/' + (n - x - 1 + u + y) * ' ' + '\\' + (
                    m - y - 1) * ' '
        if p < q:
            left += [n * ' '] * (q - p)
        elif q < p:
            right += [m * ' '] * (p - q)
        zipped_lines = zip(left, right)
        lines = [first_line, second_line] + [a + u * ' ' + b for a, b in
                                             zipped_lines]
        return lines, n + m + u, max(p, q) + 2, n + u // 2


def main():
    tree = Binary_tree()
    tree.insert(6)
    tree.insert(1)
    tree.insert(12)
    tree.insert(15)
    tree.insert(3)
    tree.insert(10)
    tree.insert(7)
    tree.insert(9)
    tree.insert(11)
    #tree.inorder()
    print('delete')
    r = tree.search(1)
    tree.delete(r)
    #tree.inorder()
    tree.display()

    # print(tree.check_tree())
    # print(tree.minimum())
    # r = tree.search(3)
    # print(tree.successor(r).value)
    # r = tree.search(7)
    # print(tree.predecessor(r).value)


if __name__ == '__main__':
    main()
    