internal class Solution {
    fun maxArea(height: IntArray): Int {
        var area = 0
        var i = 0
        var j = height.size - 1
        while (i < j) {
            val heightVar = height[i].coerceAtMost(height[j])
            val areaVar = heightVar * (j - i)
            area = area.coerceAtLeast(areaVar)
            if(height[i] < height[j]) i++
            else j--
        }
        return area
    }
}