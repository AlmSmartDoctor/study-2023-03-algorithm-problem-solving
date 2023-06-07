lateinit var parent: IntArray
lateinit var matrix: Array<IntArray>
lateinit var rank: IntArray
lateinit var plan: IntArray

fun main(args: Array<String>) {
    val br = System.`in`.bufferedReader()

    val n = br.readLine().trim().toInt()
    val m = br.readLine().trim().toInt()

    matrix = Array(n + 1) { IntArray(n + 1) }
    parent = IntArray(n + 1) { it }
    rank = IntArray(n + 1) { 1 }
    plan = IntArray(m)

    for (i in 1..n) {
        val input = br.readLine().trim().split(" ").map { it.toInt() }
        for (j in 1..n) {
            matrix[i][j] = input[j - 1]
        }
    }


    for (i in 1..n) {
        for (j in 1..n) {
            if (matrix[i][j] == 1) {
                if(find(i) == find(j)) continue
                union(i, j)
            }
        }
    }

    plan = br.readLine().trim().split(" ").map { it.toInt() }.distinct().toIntArray()


    val root = find(plan[0])
    for (i in 1 until plan.size + 1) {
        if (root != find(plan[i - 1])) {
            println("NO")
            return
        }
    }
    println("YES")
}

fun find(x: Int): Int {
    return if (x == parent[x]) x
    else {
        val p = find(parent[x])
        parent[x] = p
        p
    }
}

fun union(x: Int, y: Int) {
    val px = find(x)
    val py = find(y)

    if (px == py) return

    if (rank[px] > rank[py]) {
        parent[py] = px
    } else {
        parent[px] = py
    }
    if (rank[px] == rank[py]) {
        rank[py]++
    }
}