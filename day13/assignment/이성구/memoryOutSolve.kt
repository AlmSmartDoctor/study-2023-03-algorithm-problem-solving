import java.util.*
import kotlin.math.abs

data class Edge(val u: Int, val v: Int, val cost: Int) : Comparable<Edge> {
    override fun compareTo(other: Edge) = this.cost - other.cost
}

fun main(args: Array<String>) {
    val br = System.`in`.bufferedReader()
    val n = br.readLine().toInt()

    val parent = IntArray(n) { it }
    val rank = IntArray(n) { 0 }
    val points = mutableListOf<List<Int>>()

    repeat(n) {
        val point = br.readLine().split(" ").map { it.toInt() }
        points.add(point)
    }

    val edges = PriorityQueue<Edge>()

    for (i in 0 until 3) { // for x, y, and z
        points.indices.sortedBy { points[it][i] }.let { sortedIndices ->
            for (j in 0 until n - 1) {
                val u = sortedIndices[j]
                val v = sortedIndices[j + 1]
                val cost = abs(points[u][i] - points[v][i])
                edges.offer(Edge(u, v, cost))
            }
        }
    }

    var sumOfDistance = 0
    while (edges.isNotEmpty()) {
        val edge = edges.poll()
        if (!isCycle(parent, edge.u, edge.v)) {
            unionParent(parent, rank, edge.u, edge.v)
            sumOfDistance += edge.cost
        }
    }

    println(sumOfDistance)
}

fun findParent(parent: IntArray, x: Int): Int {
    if (parent[x] == x) return x
    parent[x] = findParent(parent, parent[x])
    return parent[x]
}

fun unionParent(parent: IntArray, rank: IntArray, a: Int, b: Int) {
    val parentA = findParent(parent, a)
    val parentB = findParent(parent, b)
    if (parentA != parentB) {
        if (rank[parentA] > rank[parentB]) {
            parent[parentB] = parentA
        } else {
            parent[parentA] = parentB
            if (rank[parentA] == rank[parentB]) rank[parentB]++
        }
    }
}

fun isCycle(parent: IntArray, a: Int, b: Int): Boolean {
    return findParent(parent, a) == findParent(parent, b)
}
