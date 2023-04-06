/*
* https://leetcode.com/problems/longest-substring-with-at-least-k-repeating-characters/description/
* aaabb ,3 -> "aaa"
* abaabc, 2 -> "abaab" a: 3개, b:2개
* abcabd, 2 -> no
*
* 풀이 방식
* 포함되면 안될 char를 찾는다
* 포함되면 안될 character를 못찾으면, (그 string자체가 가능한 substring이므로) input string의 size를 return
* 포함되면 안될 char들 사이에 있는 substring에 대해 재귀적으로 실행한다
*   -중간 substring이 그냥 포함되면 안될 케이스 뿐이라면 무시
* 위에 2번 케이스에서
*   - c는 절대 포함이되면 안됨
*   - 'abaab'c' 처럼 구간을 나누고 재귀적으로 실행
*   - abaab에 대해 재귀적으로 실행, c는 무시
*   - abaab가 가능한 케이스 이므로 return 5
* 위에 3번 케이스에서
*   - 'ab'cab'd'
*   - 'a'b' / 'c'a'b' / 'd' 에 대해 또 실행
*   - 케이스 없음 -> 0
* */

internal class Solution {
    fun longestSubstring(s: String, k: Int): Int {
        val freq = IntArray(26)
        for (c in s.toCharArray()) {
            freq[c - 'a']++
        }
        val cuttingIndex: MutableList<Int> = ArrayList()

        //초기값 세팅
        cuttingIndex.add(-1)
        for (i in s.indices) {
            if (freq[s[i] - 'a'] < k) {
                cuttingIndex.add(i)
            }
        }
        cuttingIndex.add(s.length)
        if (cuttingIndex.size == 2) return s.length
        var max = 0
        for (i in 1 until cuttingIndex.size) {
            if (cuttingIndex[i - 1] + 1 <= cuttingIndex[i] - 1) {
                max = max.coerceAtLeast(
                    longestSubstring(
                        s.substring(cuttingIndex[i - 1] + 1, cuttingIndex[i]), k
                    )
                )
            }
        }
        return max
    }
}