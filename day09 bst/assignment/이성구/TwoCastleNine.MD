
https://leetcode.com/problems/recover-binary-search-tree/submissions/952722304/



```kotlin
class Solution {
    fun recoverTree(root: TreeNode?): Unit {
        var first: TreeNode? = null
        var second: TreeNode? = null
        
        var pre: TreeNode = TreeNode(Int.MIN_VALUE)
        
        fun inorder(root: TreeNode?) {
            if (root == null) return
            
            inorder(root.left)
            
            if (first == null && pre.`val` > root.`val`) {
                first = pre
            }
            
            if (first != null && pre.`val` > root.`val`) {
                second = root
            }
            
            pre = root
            
            inorder(root.right)
        }
        
        inorder(root)
        val temp = first!!.`val`
        first!!.`val` = second!!.`val`
        second!!.`val` = temp
    }
}
```
