# https://leetcode.com/problems/serialize-and-deserialize-bst/submissions/952759374/
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Codec:

    def serialize(self, root: Optional[TreeNode]) -> str:
        """Encodes a tree to a single string.
        """
        if not root: return ""
        queue = [root]
        tree = []
        while queue:
            node = queue.pop(0)
            if node:
                tree.append(node.val)
                queue.append(node.left)
                queue.append(node.right)
            else:
                tree.append(-1)

        return ",".join(map(str, tree))

    def deserialize(self, data: str) -> Optional[TreeNode]:
        """Decodes your encoded data to tree.
        """
        if not data: return []
        data = data.split(",")
        tree = [int(x) for x in data]
        root = TreeNode(tree[0])
        queue = [root]

        i = 1
        while queue:
            node = queue.pop(0)
            if tree[i] != -1:
                node.left = TreeNode(tree[i])
                queue.append(node.left)
            i += 1
            
            if tree[i] != -1:
                node.right = TreeNode(tree[i])
                queue.append(node.right)
            i += 1
        return root

# Your Codec object will be instantiated and called as such:
# Your Codec object will be instantiated and called as such:
# ser = Codec()
# deser = Codec()
# tree = ser.serialize(root)
# ans = deser.deserialize(tree)
# return ans