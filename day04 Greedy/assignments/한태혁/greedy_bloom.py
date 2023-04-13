class Solution:
    def earliestFullBloom(self, plantTime: List[int], growTime: List[int]) -> int:
        flower = [[plantTime[i], growTime[i]] for i in range(len(plantTime))]

        totalDays = 0
        workedDays = 0

        flower.sort(key=lambda x : (-x[1], x[0]))
        for i in range(len(plantTime)):
            totalDays = max(totalDays, (workedDays + flower[i][0] + flower[i][1]))
            workedDays += flower[i][0]

        return totalDays
        
'''
'Best Solution'

class Solution:
    def earliestFullBloom(self, plantTime: List[int], growTime: List[int]) -> int:
        res = 0
        for grow, plant in sorted(zip(growTime, plantTime)):
            res = max(res, grow) + plant
        return res
'''