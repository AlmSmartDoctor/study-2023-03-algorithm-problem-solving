// https://leetcode.com/problems/kth-largest-element-in-a-stream/description/
/**
 * 최초시도 -> bruteforce(
 *  - 3이상이면 대충 넣
 *  - 아니면 제대로 넣고
class KthLargest(k: Int, nums: IntArray) {

private val zerobaseK = k - 1
private val sortedMutableList: MutableList<Int> = nums.sortedDescending().toMutableList()

fun add(`val`: Int): Int {
for (i in 0 .. sortedMutableList.size) {
if (i > zerobaseK || i == sortedMutableList.size) {
sortedMutableList.add(`val`)
break
}
if (sortedMutableList[i] < `val`) {
sortedMutableList.add(i, `val`)
break
}
}
return sortedMutableList[zerobaseK]
}

}
 * */
class KthLargest(private val k: Int, nums: IntArray) {

    private val pq = PriorityQueue<Int>()

    init {
        pq.addAll(nums.asIterable())
        while (pq.size > k) {
            pq.poll()
        }
    }

    fun add(`val`: Int): Int {
        pq.add(`val`)
        if (pq.size > k) {
            pq.poll()
        }
        return pq.first()
    }

}