fun main() {
    val n = readln().toInt()
    val r = readln().toInt()

    val disjointSet = DisjointSet(n)
    val relations = Array(r) {
        intArrayOf()
    }

    repeat(r) {
        val inputs = readln().split(' ')

        val relation = IntArray(3)
        relation[0] = if (inputs[0] == "E") 0 else 1
        relation[1] = inputs[1].toInt() - 1
        relation[2] = inputs[2].toInt() - 1
        relations[it] = relation
    }

    val enemies = Array(n) {
        IntArray(n)
    }

    relations.forEach { (relation, u, v) ->
        if (relation == 1) disjointSet.union(u, v)
        else {
            enemies[u][v] = 1
            enemies[v][u] = 1
        }
    }


    relations.forEach { (relation, u, v) ->
        if (relation == 1) return@forEach

        enemies[u].forEachIndexed { index, i ->
            if (i != 1 || index == v) return@forEachIndexed
            disjointSet.union(v, index)
        }
        enemies[v].forEachIndexed { index, i ->
            if (i != 1 || index == u) return@forEachIndexed
            disjointSet.union(u, index)
        }
    }

    println(disjointSet.size)
}

class DisjointSet(
    n: Int,
) {
    private var parent: IntArray = IntArray(n) { it }
    private var rank: IntArray = IntArray(n) { 1 }

    val size: Int
        get() = parent.toSet().size

    fun find(u: Int): Int {
        if (parent[u] == u) return u
        return find(parent[u]).also { parent[u] = it }
    }

    fun union(u: Int, v: Int) {
        var uSet = find(u)
        var vSet = find(v)

        if (uSet == vSet) return
        if (rank[uSet] > rank[vSet]) {
            val t = uSet
            uSet = vSet
            vSet = t
        }

        parent[uSet] = vSet
        if (rank[uSet] == rank[vSet]) rank[vSet]++
    }

}