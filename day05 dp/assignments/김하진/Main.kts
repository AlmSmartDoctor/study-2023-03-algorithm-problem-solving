class Solution {
    private val products: MutableMap<Pair<Int, Int>, Int> = hashMapOf()

    private tailrec fun recurse(index: Int, nums: IntArray) {
        if (index >= nums.size) return

        products[index to index] = nums[index]

        for (i in 0 until index) {
            products[i to index] = products[i to index - 1]!! * nums[index]
        }

        recurse(index + 1, nums)
    }

    fun maxProduct(nums: IntArray): Int {
        recurse(0, nums)

        @Suppress("UNNECESSARY_NOT_NULL_ASSERTION") // Kotlin 1.3
        return products.values.max()!!
    }
}

fun printSolution(nums: IntArray) {
    println(Solution().maxProduct(nums))
}

printSolution(intArrayOf(2, 3, -2, 4))
printSolution(intArrayOf(-2, 0, -1))
printSolution(intArrayOf(-2))
