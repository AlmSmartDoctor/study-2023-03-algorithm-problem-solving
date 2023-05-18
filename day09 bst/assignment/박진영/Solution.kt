/** https://leetcode.com/problems/minimum-number-of-vertices-to-reach-all-nodes/
 *           4
 *        /   \
 *       2     5
 *     / \    / \
 *    1   3  6   7
 *    최초 접근 bfs
 *    -> q써서 하려는데 절단 되는케이스 ( 위 예에서 [3,4] )
 *      에는 어떻게 접근해야할까에서 막힘
 * 
 *    분할 정복
 *      - 분할 정복 방식으로 변경
 *      - 각각의 subTree로 쪼개고,
 *      - 각각의 subTree의 결과를 상위 Node에서의 결과 값으로 합침
 *        1) 현재 노드가 범위 사이일때 -> root = node , left=leftSubTree's trim result , right = rightSubTree's trim result 
 *                      [     node     ]
 *                      /             \
 *       leftSub's TrimResult       rightSubTree's TrimResult
 *       
 *        2) 현재 노드가 범위보다 작을때 -> root = rightSubTree's TrimResult
 *        
 *        3 ) 현재 노드가 범위보다 클때 -> root = leftSubTree's TrimResult
 *        
 **/
class Solution {
    fun trimBST(root: TreeNode?, low: Int, high: Int): TreeNode? {
        return solve(root, low, high)
    }

    // return => input node에 대한 trim 결과값
    private fun solve(node: TreeNode?, low: Int, high: Int): TreeNode? {
        if (node == null) return null

        return if (node.`val` < low) solve(node.right, low, high)
        else if (node.`val` > high) solve(node.left, low, high)
        else {
            node.left = solve(node.left, low, high)
            node.right = solve(node.right, low, high)
            node
        }
    }
}
