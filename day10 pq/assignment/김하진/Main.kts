class Solution {
    fun mergeKLists(lists: Array<ListNode?>): ListNode? {
        if (lists.isEmpty()) {
            return null
        }

        val priorityQueue = PriorityQueue<Int>()

        lists.forEach {
            var node = it
            while (node != null) {
                priorityQueue.add(node.`val`)
                node = node.next
            }
        }

        if (priorityQueue.isEmpty())
            return null

        val head = ListNode(priorityQueue.poll())

        var tail: ListNode = head
        while (!priorityQueue.isEmpty()) {
            tail.next = ListNode(priorityQueue.poll())
            tail = tail.next!!
        }

        return head
    }
}
