class Solution:
    def minSwapsCouples(self, row: List[int]) -> int:

        par = [2*(i//2) for i in range(len(row))]
        rank = [1 for i in range(len(row))]

        def find(n1):
            res = n1
            while par[res]!=res:
                par[res] = par[par[res]]
                res = par[res]

            return res

        def union(n1,n2):

            p1,p2 = find(n1),find(n2)

            if p1 == p2:
                return 0
            
            if rank[p2] > rank[p1]:
                par[p1] = p2
                rank[p2] += rank[p1]
            else:
                par[p2] = p1
                rank[p1] += rank[p2]
            return 1

        res = 0
        for n1,n2 in zip([row[i] for i in range(0,len(row),2)],[row[i] for i in range(1,len(row),2)]):
            print(n1, " ", n2)
            res += union(n1,n2)

        print(f"rank: {rank}")
        print(f"par: {par}")
        return res