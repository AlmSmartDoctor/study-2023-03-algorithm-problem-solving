import sys

input = sys.stdin.readline


class Node:
    def __init__(self, pokemon=None, idx=None):
        self.pokemon = pokemon
        self.idx = idx
        self.left = None
        self.right = None


class BST:
    def __init__(self):
        self.parent = None

    def add(self, pokemon, idx):
        node = Node(pokemon, idx)
        parent = None
        current = self.parent

        while current:
            parent = current
            if node.pokemon < current.pokemon:
                current = current.left
            else:
                current = current.right

        if parent is None:
            self.parent = node
        elif node.pokemon < parent.pokemon:
            parent.left = node
        else:
            parent.right = node

    def search(self, pokemon):
        node = self.parent

        while True:
            if node == None:
                return node
            elif node.pokemon == pokemon:
                return node.idx
            elif pokemon < node.pokemon:
                node = node.left
            else:
                node = node.right


if __name__ == "__main__":
    N, M = map(int, input().split())
    pList = []
    bst = BST()

    for i in range(N):
        pName = input().rstrip()
        pList.append(pName)
        bst.add(pName, i)

    for i in range(M):
        problem = input().rstrip()

        if not problem[0].isdigit():
            print(bst.search(problem) + 1)
        else:
            print(pList[int(problem) - 1])
