
https://leetcode.com/problems/recover-binary-search-tree/submissions/952722304/

```kotlin
class Solution {
    fun recoverTree(root: TreeNode?): Unit {
        var first: TreeNode? = null
        var second: TreeNode? = null

        var preNode: TreeNode = TreeNode(Int.MIN_VALUE)

        fun recursive(root: TreeNode?) {
            if (root == null) return

            recursive(root.left)

            if (first == null && preNode.`val` > root.`val`) {
                first = preNode
            }

            if (first != null && preNode.`val` > root.`val`) {
                second = root
            }

            preNode = root

            recursive(root.right)
        }

        recursive(root)
        val temp = first!!.`val`
        first!!.`val` = second!!.`val`
        second!!.`val` = temp
    }
}
```
