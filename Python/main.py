import time
import random

class TreeNode:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

class BST:
    def __init__(self):
        self.root = None

    def insert(self, value):
        start_time = time.time()

        def _insert(node, value):
            if node is None:
                return TreeNode(value)
            elif value < node.value:
                node.left = _insert(node.left, value)
            elif value > node.value:
                node.right = _insert(node.right, value)
            return node

        self.root = _insert(self.root, value)
        end_time = time.time()
        return (end_time - start_time) * 1000

    def delete(self, value):
        start_time = time.time()

        def _delete(node, value):
            if node is None:
                return None
            if value < node.value:
                node.left = _delete(node.left, value)
            elif value > node.value:
                node.right = _delete(node.right, value)
            else:
                if node.left is None:
                    return node.right
                elif node.right is None:
                    return node.left
                temp_val = self._min_value(node.right)
                node.value = temp_val
                node.right = _delete(node.right, temp_val)
            return node

        self.root = _delete(self.root, value)
        end_time = time.time()
        return (end_time - start_time) * 1000

    def _min_value(self, node):
        current = node
        while current.left is not None:
            current = current.left
        return current.value

    def search(self, value):
        start_time = time.time()

        def _search(node, value):
            if node is None or node.value == value:
                return node is not None
            elif value < node.value:
                return _search(node.left, value)
            else:
                return _search(node.right, value)

        found = _search(self.root, value)
        end_time = time.time()
        return (end_time - start_time) * 1000, found

class ListNode:
    def __init__(self, value):
        self.value = value
        self.next = None

class LinkedList:
    def __init__(self):
        self.head = None

    def insert_at_beginning(self, value):
        start_time = time.time()
        new_node = ListNode(value)
        new_node.next = self.head
        self.head = new_node
        end_time = time.time()
        return (end_time - start_time) * 1000

    def insert_at_end(self, value):
        start_time = time.time()
        new_node = ListNode(value)
        if self.head is None:
            self.head = new_node
        else:
            current = self.head
            while current.next:
                current = current.next
            current.next = new_node
        end_time = time.time()
        return (end_time - start_time) * 1000

    def delete(self, value):
        start_time = time.time()
        current = self.head
        prev = None
        while current:
            if current.value == value:
                if prev is None:
                    self.head = current.next
                else:
                    prev.next = current.next
                del current
                end_time = time.time()
                return (end_time - start_time) * 1000
            prev = current
            current = current.next
        end_time = time.time()
        print("Element not found in LinkedList.")
        return (end_time - start_time) * 1000

    def search(self, value):
        start_time = time.time()
        current = self.head
        found = False
        while current:
            if current.value == value:
                found = True
                break
            current = current.next
        end_time = time.time()
        return (end_time - start_time) * 1000, found

class DynamicArray:
    def __init__(self):
        self.array = []

    def insert_at_beginning(self, value):
        start_time = time.time()
        self.array.insert(0, value)
        end_time = time.time()
        return (end_time - start_time) * 1000

    def insert_at_end(self, value):
        start_time = time.time()
        self.array.append(value)
        end_time = time.time()
        return (end_time - start_time) * 1000

    def delete(self, value):
        start_time = time.time()
        try:
            self.array.remove(value)
        except ValueError:
            print("Element not found in Array.")
        end_time = time.time()
        return (end_time - start_time) * 1000

    def search(self, value):
        start_time = time.time()
        found = value in self.array
        end_time = time.time()
        return (end_time - start_time) * 1000, found

def test_structure_operations():
    bst = BST()
    linked_list = LinkedList()
    dynamic_array = DynamicArray()

    while True:
        print("\nChoose operation to test:")
        print("1. Insert")
        print("2. Delete")
        print("3. Search")
        print("4. Display Structures")
        print("5. Exit")

        operation = int(input("Select operation (1-5): "))

        if operation == 5:
            print("Exiting.")
            break

        if operation not in [1, 2, 3, 4]:
            print("Invalid selection, try again.")
            continue

        if operation in [1, 2, 3]:  # Insert, Delete, Search
            value = int(input("Enter integer value to operate with: "))

        if operation == 1:
            print(f"\nInserting {value}...")
            print(f"BST Insert Time: {bst.insert(value):.2f} ms")
            print(f"Linked List Insert at Beginning Time: {linked_list.insert_at_beginning(value):.2f} ms")
            print(f"Array Insert at End Time: {dynamic_array.insert_at_end(value):.2f} ms")
        elif operation == 2:
            print(f"\nDeleting {value}...")
            print(f"BST Delete Time: {bst.delete(value):.2f} ms")
            print(f"Linked List Delete Time: {linked_list.delete(value):.2f} ms")
            print(f"Array Delete Time: {dynamic_array.delete(value):.2f} ms")
        elif operation == 3:
            print(f"\nSearching for {value}...")
            time_bst, found_bst = bst.search(value)
            print(f"BST Search Time: {time_bst:.2f} ms, Found: {'Yes' if found_bst else 'No'}")
            time_ll, found_ll = linked_list.search(value)
            print(f"Linked List Search Time: {time_ll:.2f} ms, Found: {'Yes' if found_ll else 'No'}")
            time_arr, found_arr = dynamic_array.search(value)
            print(f"Array Search Time: {time_arr:.2f} ms, Found: {'Yes' if found_arr else 'No'}")
        elif operation == 4:
            print("\nBST Elements:")
            bst.display()
            print("Linked List Elements:")
            linked_list.display()
            print("Array Elements:")
            dynamic_array.display()

test_structure_operations()
