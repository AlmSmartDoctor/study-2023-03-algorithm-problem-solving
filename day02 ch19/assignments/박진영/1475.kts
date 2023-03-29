import java.util.Stack

/**
 * 문제 https://leetcode.com/problems/final-prices-with-a-special-discount-in-a-shop/description/
 *
 * int array A가 있을때, A[i]는 i번째 물건의 가격이다
 * 특정조건을 만족하는 j가 있으면, 해당 A[i]에서 A[j]만큼의 가격을 할인한다. 그렇지 않으면 정상가
 * (특정조건: j > i, A[j] < A[i] 를 만족하는 가장 작은 값)
 */
fun main() {

    Solution()
        .finalPrices(prices = intArrayOf(8,4,6,2,3))
        .also { list -> println(list.joinToString(",") { it.toString() }) }
}

class Solution {
    fun finalPrices(prices: IntArray): IntArray {
        val stack = Stack<Int>()
        if (prices.isEmpty()) return intArrayOf()
        return prices
            .foldRightIndexed(IntArray(prices.size)) { index: Int, i: Int, acc: IntArray ->
                while (stack.isNotEmpty() && stack.peek() > i) {
                    stack.pop()
                }
                acc[index] = if (stack.isEmpty()) i
                else (i - stack.peek())
                stack.push(i)
                acc
            }
    }
}