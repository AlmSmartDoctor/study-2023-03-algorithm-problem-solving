////////////// GIVEN //////////////
class ListNode(var `val`: Int) {
    var next: ListNode? = null

    companion object {
        fun of(vararg values: Int): ListNode? {
            if (values.isEmpty()) return null
            val fakeHead = ListNode(values[0])

            values.fold(fakeHead) { acc, i ->
                acc.next = ListNode(i)
                acc.next!!
            }

            return fakeHead.next
        }
    }
}
///////////////////////////////////

// beats 43.63% for time
// beats 53.26% for memory
// maybe can use counting sort
class Solution {
    private fun <T> Array<T>.divideArray(): Pair<Array<T>, Array<T>> {

        return sliceArray(0 until size / 2) to
                sliceArray(size / 2 until size)
    }

    private fun ListNode?.mergeWith(other: ListNode?): ListNode? {
        this ?: return other
        other ?: return this

        var newListNode: ListNode? = null
        var ret: ListNode? = null
        var first = this
        var second = other
        while (first != null && second != null) {
            val next: ListNode
            if (first.`val` < second.`val`) {
                next = first
                first = first.next
            } else {
                next = second
                second = second.next
            }

            if (newListNode == null) {
                newListNode = next
                ret = next
            } else {
                newListNode.next = next
                newListNode = next
            }
        }

        if (first != null)
            newListNode!!.next = first
        else if (second != null)
            newListNode!!.next = second

        return ret
    }

    fun mergeKLists(lists: Array<ListNode?>): ListNode? {
        if (lists.size <= 1)
            return lists.firstOrNull()

        val (first, last) = lists.divideArray()

        return mergeKLists(first).mergeWith(mergeKLists(last))
    }
}

////////////// TEST //////////////
fun printListNode(listNode: ListNode?) {
    var current = listNode
    while (current != null) {
        print("${current.`val`} ")
        current = current.next
    }
    println()
}

fun printSolution(lists: Array<ListNode?>) {
    val result = Solution().mergeKLists(lists)
    printListNode(result)
}

printSolution(arrayOf(ListNode.of(1, 4, 5), ListNode.of(1, 3, 4), ListNode.of(2, 6)))
printSolution(arrayOf(ListNode.of()))
printSolution(arrayOf())
