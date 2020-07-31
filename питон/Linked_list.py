
class Node:
    def __init__(self, value=None):
        self.value = value
        self.next = None
        self.prev = None


class Singly_Linked_List:
    def __init__(self):
        self.head = None

    def print_list(self):
        if self.head is None:
            print('Linked list is empty')
            return
        temp = self.head
        list = []
        while temp is not None:
            list.append(temp.value)
            temp = temp.next
        print(" ".join(map(str, list)))

    def add_elem_in_head(self, value):
        new_node = Node(value)
        new_node.next = self.head
        self.head = new_node

    def add_elem_in_end(self, value):
        new_node = Node(value)
        if self.head is None:
            self.head = new_node
            return
        temp = self.head
        while temp.next is not None:
            temp = temp.next
        temp.next = new_node

    def add_after_elem(self, after, value):
        new_node = Node(value)
        temp_head = self.head
        while temp_head is not None:
            if temp_head.value == after:
                temp = temp_head.next
                temp_head.next = new_node
                new_node.next = temp
                return
            else:
                temp_head = temp_head.next


class Doubly_Linked_List:
    def __init__(self):
        self.head = None
        self.tail = None

    def print_list(self):
        if self.head is None:
            print('Linked list is empty')
            return
        temp = self.head
        list = []
        while temp is not None:
            list.append(temp.value)
            temp = temp.next
        print(" ".join(map(str, list)))

    def check_init(self, value):
        if self.head is None:
            new_node = Node(value)
            self.head = new_node
            self.tail = new_node
            return True
        return False

    def add_elem_in_head(self, value):
        if not self.check_init(value):
            new_node = Node(value)
            new_node.next = self.head
            new_node.next.prev = new_node
            self.head = new_node

    def add_elem_in_end(self, value):
       if not self.check_init(value):
           new_node = Node(value)
           self.tail.next = new_node
           self.tail.next.prev = self.tail
           self.tail = self.tail.next

    def print_from_last(self):
        temp = self.tail
        list = []
        while temp is not None:
            list.append(temp.value)
            temp = temp.prev
        print(" ".join(map(str, list)))

    def add_before_elem(self, before, value):
        if not self.check_init(value):
            new_node = Node(value)
            temp_head = self.head
            while temp_head is not None:
                if temp_head.next.value == before:
                    new_node.next = temp_head.next
                    new_node.next.prev = new_node
                    temp_head.next = new_node
                    temp_head.next.prev = temp_head
                    return
                temp_head = temp_head.next

    def delete_first(self):
        self.head.next.prev = None
        self.head = self.head.next

def main():
    # linked_list = Singly_Linked_List()
    # linked_list.add_elem_in_end(10)
    # linked_list.add_elem_in_end(12)
    # linked_list.print_list()

    linked_list = Doubly_Linked_List()
    for _ in range(10):
        linked_list.add_elem_in_end(_)

    linked_list.add_before_elem(5, 100)
    linked_list.delete_first()
    linked_list.print_list()
    linked_list.print_from_last()

if __name__ == '__main__':
    main()
