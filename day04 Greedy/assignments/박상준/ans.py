class Solution:
    def partitionLabels(self, s: str) -> List[int]:
        char_dict = collections.defaultdict(list)
        answer = []

        for idx in range(0, len(s)): 
            char = s[idx]
            if len(char_dict[char]) < 2: 
                char_dict[char].extend([idx,idx])
            else: 
                char_dict[char][1] = idx
        
        sort_list = sorted(list(char_dict.values()), key=lambda x:x[0], reverse=True)
        from_idx, to_idx = -1, -1
        
        while len(sort_list): 
            target = sort_list.pop()
            if from_idx == -1 and to_idx == -1: 
                from_idx, to_idx = target[0], target[1]
            elif target[0] > to_idx: 
                answer.append(to_idx - from_idx + 1) 
                from_idx, to_idx = -1, -1
                sort_list.append(target)
            else: 
                to_idx = max(target[1], to_idx)

        answer.append(to_idx - from_idx + 1)
        return answer
    