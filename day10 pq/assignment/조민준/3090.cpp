// 참고: https://www.acmicpc.net/workbook/view/1016
// 출처: https://www.acmicpc.net/problem/3090

#include<iostream>
#include<queue>

using namespace std;

template<typename T>
class custom_priority_queue : public priority_queue<T, vector<T>>
{
  public:

      bool remove(const T& value) {
          auto it = find(this->c.begin(), this->c.end(), value);
       
          if (it == this->c.end()) {
              return false;
          }
          if (it == this->c.begin()) {
              // deque the top element
              this->pop();
          }    
          else {
              // remove element and re-heap
              this->c.erase(it);
              make_heap(this->c.begin(), this->c.end(), this->comp);
         }
         return true;
     }
};

struct elem{
    int idx;
    int n;
    int diff = 0;

    bool operator<(const elem& e) const{
        return diff > e.diff;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    custom_priority_queue<elem> pq;

    elem arr[100000];
    int n, t;
    cin >> n >> t;

    for(int i = 0; i < n; i++){
        arr[i].idx = i;
        cin >> arr[i].n;
    }

    for(int i = 0; i < n - 1; i++){
        int diff = abs(arr[i].n - arr[i + 1].n);
        arr[i].diff = diff;
        pq.push(arr[i]);
    }

    for(int i = 0; i < t; i++){
        elem target = pq.top(), sub_target;
        pq.pop();
        if(target.diff == 0) break;

        target.diff--;
        if(arr[target.idx].n > arr[target.idx + 1].n){
            arr[target.idx].n--;

            if(target.idx != 0){
                sub_target = arr[target.idx - 1];
                sub_target.diff = abs(arr[target.idx - 1].n - arr[target.idx].n);
            }
        }else{
            arr[target.idx + 1].n--;

            if(target.idx + 1 != n - 1){
                sub_target = arr[target.idx + 1];
                sub_target.diff = abs(arr[target.idx + 1].n - arr[target.idx + 2].n);
            }
        }

        pq.push(target);
        if(sub_target.diff != 0){
            pq.remove(sub_target);
            pq.push(sub_target);
        }
    }

    for(int i = 0; i < n; i++){
        cout << arr[i].n << " ";
    }

    return 0;
}