# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def convertBST(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        sum = 0
        
        def sol(root):
            nonlocal sum
            if root:
                sol(root.right)
                root.val += sum
                sum = root.val
                sol(root.left)
            return root
        
        return sol(root)
