
https://leetcode.com/problems/recover-binary-search-tree/submissions/952722304/

```kotlin
class Solution {
    fun recoverTree(root: TreeNode?): Unit {
        //swap할 Node들을 각각 first와 second에 저장한다.
        var first: TreeNode? = null
        var second: TreeNode? = null

        var preNode: TreeNode = TreeNode(Int.MIN_VALUE)

        fun recursive(curNode: TreeNode?) {
            if (curNode == null) return

            recursive(curNode.left)

            if (first == null && preNode.`val` > curNode.`val`) {
                first = preNode
            }

            if (first != null && preNode.`val` > curNode.`val`) {
                second = curNode
            }

            preNode = curNode

            recursive(curNode.right)
        }
        
        //재귀 진입
        recursive(root)
        
        //swap을 한다.
        val temp = first!!.`val`
        first!!.`val` = second!!.`val`
        second!!.`val` = temp
    }
}
```
