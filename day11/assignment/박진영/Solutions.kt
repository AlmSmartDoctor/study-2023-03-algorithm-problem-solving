class Solution {
    data class Node(
        val cur: Int,
        val dist: Int,
        val stops: Int
    )

    fun findCheapestPrice(n: Int, flights: Array<IntArray>, src: Int, dst: Int, k: Int): Int {

        val q = mutableListOf<Node>()
        val upper = Array(n) { Int.MAX_VALUE }
        val adjacentMap = flights.groupBy { (first) -> first }
        upper[src] = 0
        q.add(
            Node(src,0,-1)
        )
        while(q.isNotEmpty()) {
            val node = q.removeAt(0)
            if(node.stops > k -1 ) continue

            adjacentMap.getOrDefault(node.cur, emptyList()).forEach { (_, there, cost) ->
                if( upper[there] > (node.dist + cost)) {
                    upper[there] = node.dist + cost
                    q.add(
                        Node(
                            there,
                            upper[there],
                            node.stops + 1
                        )
                    )
                }
            }
        }

        return if(upper[dst] != Int.MAX_VALUE) upper[dst]
        else -1
    }
}
