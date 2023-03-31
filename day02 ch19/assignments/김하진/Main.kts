import java.util.Deque
import java.util.LinkedList

enum class Senator(val input: Char, val output: String) {
    RADIANT('R', "Radiant"),
    DIRE('D', "Dire"),
    ;

    companion object {
        fun from(input: Char): Senator = values().first { it.input == input }
    }
}

class Solution {
    fun predictPartyVictory(senate: String): String {
        val input = senate.map { Senator.from(it) }
        val deque: Deque<Senator> = LinkedList(input)

        val remainingMembers = Senator
            .values()
            .associateWith { deque.count { inQueue -> inQueue == it } }
            .toMutableMap()

        while (!remainingMembers.values.contains(0)) {
            val senator = deque.poll()
            val shouldRemove = when (senator) {
                Senator.RADIANT -> Senator.DIRE
                Senator.DIRE -> Senator.RADIANT
            }
            remainingMembers[shouldRemove] = remainingMembers[shouldRemove]!! - 1
            deque.remove(shouldRemove)
            deque.addLast(senator)
        }

        return deque.poll().output
    }
}

// println(Solution().predictPartyVictory("RD"))
// println(Solution().predictPartyVictory("RDD"))
// println(Solution().predictPartyVictory("RRR"))
