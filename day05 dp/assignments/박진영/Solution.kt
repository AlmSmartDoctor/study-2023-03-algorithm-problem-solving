// 19 / no memo => 2682 ms
// 19  => 177 ms
class Solution {
    private val array = IntArray(20) { -1 }
        .apply {
            set(0, 1)
            set(1, 1)
        }

    fun numTrees(n: Int): Int {
        if (array[n] != -1) return array[n]

        var max = 0
        for (i in 0 until n) {
            max += (numTrees(i) * numTrees(n - i - 1))
        }
        array[n] = max
        return max
    }
}