import java.lang.StringBuilder
import java.time.DayOfWeek
import java.util.PriorityQueue
import kotlin.math.abs
import kotlin.math.min

lateinit var xArray: Array<Pair<Int, Int>>
lateinit var yArray: Array<Pair<Int, Int>>
lateinit var zArray: Array<Pair<Int, Int>>
lateinit var visited: Array<Boolean>
lateinit var parent: IntArray
lateinit var rank: IntArray



fun main(args: Array<String>) {
    val br = System.`in`.bufferedReader()
    val n = br.readLine().toInt()


    val distanceMap: MutableMap<Pair<Int, Int>, Int> = mutableMapOf()

    xArray = Array(n) { Pair(0, 0) }
    yArray = Array(n) { Pair(0, 0) }
    zArray = Array(n) { Pair(0, 0) }
    visited = Array(n) { false }
    parent = IntArray(n) { it }
    rank = IntArray(n) { 0 }

    repeat(n) {
        val (x, y, z) = br.readLine().split(" ").map { it.toInt() }
        xArray[it] = Pair(x, it)
        yArray[it] = Pair(y, it)
        zArray[it] = Pair(z, it)
    }
    xArray.sortBy { it.first }
    yArray.sortBy { it.first }
    zArray.sortBy { it.first }

    repeat(n-1){
        val (x1, x2) = xArray[it]
        val (y1, y2) = yArray[it]
        val (z1, z2) = zArray[it]
        val (x3, x4) = xArray[it+1]
        val (y3, y4) = yArray[it+1]
        val (z3, z4) = zArray[it+1]

        val xDistance = abs(x1 - x3)
        val yDistance = abs(y1 - y3)
        val zDistance = abs(z1 - z3)

        distanceMap[Pair(x2, x4)] = min(xDistance, distanceMap[Pair(x2, x4)]?: Int.MAX_VALUE)
        distanceMap[Pair(y2, y4)] = min(yDistance, distanceMap[Pair(y2, y4)]?: Int.MAX_VALUE)
        distanceMap[Pair(z2, z4)] = min(zDistance, distanceMap[Pair(z2, z4)]?: Int.MAX_VALUE)
    }
//
//    var distanceList = distanceMap.toList()
//    distanceList = distanceList.sortedBy { it.second }

    var distanceList = PriorityQueue<Pair<Pair<Int, Int>, Int>>{ o1, o2 -> o1.second - o2.second }
    distanceMap.forEach { distanceList.add(Pair(it.key, it.value)) }



    var sumOfDistance = 0
    repeat(distanceList.size){
        var it = distanceList.poll()
//        if(!isCycle(parent, distanceList[it].first.first, distanceList[it].first.second)){
//            sumOfDistance += distanceList[it].second
//            unionParent(parent, distanceList[it].first.first, distanceList[it].first.second)
//        }
        if(!isCycle(parent, it.first.first, it.first.second)){
            sumOfDistance += it.second
            unionParent(parent, it.first.first, it.first.second)
        }
    }

    println(sumOfDistance)

}



fun findParent(parent: IntArray, x: Int): Int {
    if (parent[x] == x) return x
    parent[x] = findParent(parent, parent[x])
    return parent[x]
}

fun unionParent(parent: IntArray, a: Int, b: Int) {
    val (a, b) = Pair(findParent(parent, a), findParent(parent, b))
    if(a == b) return
    if(rank[a] > rank[b]) parent[b] = a
    else parent[a] = b
    if(rank[a] == rank[b]) rank[b]++
}

fun isCycle(parent: IntArray, a: Int, b: Int): Boolean {
    val (a, b) = Pair(findParent(parent, a), findParent(parent, b))
    return a == b
}