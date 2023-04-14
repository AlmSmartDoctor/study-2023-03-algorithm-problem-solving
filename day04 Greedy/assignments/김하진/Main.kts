
// 현재 상태: Fail (44/53)
// 시도한 것들
// 1. 단순 카운팅으로 풀 수 있을까 -> 실패
// 2. (현재) 선형 탐색으로 풀 수 있을까 -> 실패
//   - bbaaaaaaaaaaaaaaacccccc일 때 delete c and replace c -> delete two a and replace four a 를 처리하기 어려움
//   - 시도할 예정인 것: 상수 횟수의 선형 탐색으로 해결 가능할지
class Solution {
    fun strongPasswordChecker(password: String): Int {
        var requiredInsertion = maxOf(6 - password.length, 0)
        var requiredDeletion = maxOf(password.length - 20, 0)

        var requiredReplacementByCharacterType = 0
        if (!password.contains(Regex("[a-z]")))
            requiredReplacementByCharacterType += 1
        if (!password.contains(Regex("[A-Z]")))
            requiredReplacementByCharacterType += 1
        if (!password.contains(Regex("[1-9]")))
            requiredReplacementByCharacterType += 1
        requiredReplacementByCharacterType = maxOf(requiredReplacementByCharacterType - requiredInsertion, 0)

        var answer = 0
        if (password.length > 2) {
            var iMinusTwo: Char? = null
            var iMinusOne: Char? = null

            password.forEach {
                if (iMinusTwo == iMinusOne && iMinusOne == it) {
                    answer += 1
                    if (requiredInsertion > 0) {
                        requiredInsertion -= 1
                        requiredReplacementByCharacterType -= 1
                        iMinusTwo = null
                        iMinusOne = null
                    }
                    else if (requiredDeletion > 0) {
                        requiredDeletion -= 1
                        iMinusTwo = iMinusOne
                        iMinusOne = it
                    }
                    else if (requiredReplacementByCharacterType > 0) {
                        requiredReplacementByCharacterType -= 1
                        iMinusTwo = null
                        iMinusOne = null
                    }
                    else {
                        iMinusTwo = null
                        iMinusOne = null
                    }
                }
                else {
                    iMinusTwo = iMinusOne
                    iMinusOne = it
                }
            }
        }
        answer += maxOf(requiredInsertion, requiredReplacementByCharacterType)
        answer += requiredDeletion

        return answer
    }
}
