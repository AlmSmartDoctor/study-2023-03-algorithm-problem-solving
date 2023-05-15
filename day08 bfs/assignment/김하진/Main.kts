//class Node(var `val`: Int) {
//    var left: Node? = null
//    var right: Node? = null
//    var next: Node? = null
//}

class Solution {
    private fun bfs(root: Node): List<List<Node>> {
        val result = mutableListOf<List<Node>>()
        val queue = mutableListOf<Node>()
        queue.add(root)
        while (queue.isNotEmpty()) {
            val level = mutableListOf<Node>()
            for (i in 0 until queue.size) {
                val node = queue.removeAt(0)
                level.add(node)
                node.left?.let { queue.add(it) }
                node.right?.let { queue.add(it) }
            }
            result.add(level)
        }
        return result
    }

    private fun connectLevel(level: List<Node>): List<Node> {
        for (i in 0 until level.size - 1) {
            level[i].next = level[i + 1]
        }
        return level
    }

    fun connect(root: Node?): Node? {
        root ?: return null

        val levels = bfs(root)
        levels.forEach { connectLevel(it) }

        return root
    }
}
