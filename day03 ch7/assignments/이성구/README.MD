문제 설명: 2개의 정렬된 배열이 주어집니다. 
이때, 2배열들의 중간값들을 구하는 것이 문제입니다.

이때 두 배열들의 총 개수가 홀수이면 중간값이 딱 떨어져서 그냥 중간값을 뱉으면 됩니다.
하지만 두 배열들의 총 개수가 짝수이면 중간의 2개 값의 평균값을 뱉으면 됩니다.

예시: 
[1,3] [2] 가 있다면 2.00000이 output이 됩니다.

[1,2] [3,4]가 있다면 2.50000가 output이 됩니다.

시간복잡도: log(n+m) n,m은 각각 input배열들의 size을 의미합니다.


힌트가 될까 싶어서, 완전탐색으로 해봤습니다.

```C++
class Solution {
public:
    //완전탐색.
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
        vector<int> v;
        for (auto num: nums1)v.push_back(num);//O(n)
        for (auto num: nums2)v.push_back(num);//O(m)

        sort(v.begin(), v.end());//O((n+m)Log(n+m))

        int size = v.size();

        if (size % 2) {//홀수 0 1 2 3 4
            return v[size / 2];
        } else {// 짝수 0 1 2 3
            return (v[size / 2] + v[size / 2 - 1]) / 2.0;
        }
    }
};
```
시간복잡도가 많이 초과되었습니다. -> 노답


 시간 복잡도를 보고 divide and conquer로 해야 된다고 생각이 들었습니다. 


```C++
class Solution {
public:
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
        int len1 = nums1.size(), len2 = nums2.size();
        //전체의 중간지점을 구하자.
        int k = (len1 + len2 + 1) / 2;

        //홀수인 경우 한번만 계산
        int median1 = findK(nums1, nums2, 0, len1 - 1, 0, len2 - 1, k);
        if ((len1 + len2) % 2 == 1)return median1;

        //짝수인 경우 한번 더 계산.
        int median2 = findK(nums1, nums2, 0, len1 - 1, 0, len2 - 1, k + 1);
        return (median1 + median2) / 2.0;
    }

    //이게 핵심임.
    int findK(vector<int> &nums1, vector<int> &nums2, int l1, int r1, int l2, int r2, int k) {
        //base case(Conquer)
        if (l1 > r1) {
            return nums2[l2 + k - 1];
        }
        if (l2 > r2) {
            return nums1[l1 + k - 1];
        }
        int mid1 = (l1 + r1) / 2, mid2 = (l2 + r2) / 2;

        // Divide
        if (nums1[mid1] <= nums2[mid2]) {
            //중간지점의 크기가 2번째 배열이 크거나 같은 경우.
            if (k <= (mid1 - l1 + 1) + (mid2 - l2)) return findK(nums1, nums2, l1, r1, l2, mid2 - 1, k);
            else return findK(nums1, nums2, mid1 + 1, r1, l2, r2, k - (mid1 - l1) - 1);
        } else {//1번째 배열이 더 큰 경우
            if (k <= (mid1 - l1) + (mid2 - l2 + 1)) return findK(nums1, nums2, l1, mid1 - 1, l2, r2, k);
            else return findK(nums1, nums2, l1, r1, mid2 + 1, r2, k - (mid2 - l2) - 1);
        }
    }
};
```
결국 우리의 목표는 중간값 구하기 최종 리턴값의 왼쪽과 오른쪽의 개수를 맞추면 되는 것이다. 그걸위해 k값을 구하는 함수를 들여다 보도록 하자.
```C++ 
if (nums1[mid1] <= nums2[mid2])
```

mid2가 mid1보다 크다는건 mid2의 앞에 적어도 l1부터 mid1까지의 개수와 l2부터 mid2까지의 개수가 있다는 것입니다.
```C++ 
if (k <= (mid1 - l1 + 1) + (mid2 - l2))
```
이때 k의 값이 mid2의 앞에있는 개수보다 작다면 우리는 k값을 찾기위해 r2의 값을 mid2 - 1의 값으로 수정해야 합니다.

```C++ 
if (nums1[mid1] <= nums2[mid2])
```
아까의 조건문을 다시 봅시다.

또 mid1의 뒤에는 적어도 mid1부터 r1까지의 개수와 mid2부터 r2까지의 개수가 존재하고 있습니다.
 
이때 k의 값이 mid1의 뒤에 있는 개수보다 크다면 l1의 값을 mid1 + 1로 수정합니다. 

또 k의 값도 mid1 - l1 + 1만큼 빼줘야 합니다. 왜냐하면 l1의 값을 옮기면서 k의 값도 그만큼 왼쪽으로 이동한 것처럼 해야하기 때문입니다.


```C++
if (l1 > r1) {
    return nums2[l2 + k - 1];
}
if (l2 > r2) {
    return nums1[l1 + k - 1];
}
```
base case을 한번 봅시다.

l1이 r1보다 큰 상황이 되었다는 것은 더이상 nums1 배열에서는 k번째 배열을 찾을 수 없는 상황입니다. 
따라서 nums2에서 찾아야 합니다. 우리는 k의 위치를 l의 값이 증가하는 것에 맞추어서 수정했으므로 l2 + k - 1의 위치가 k 번째 위치가 됩니다.
