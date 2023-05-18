#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



vector<vector<int>> binary_search_tree(300000, vector<int>(3, -1));
ll c = 0;
int last_index = 0;

// node = {number, left_child_position, right_child_position}
void insert_in_tree(int number, int node)
{
    c++;
    if (number < binary_search_tree[node][0])
    {
        if (binary_search_tree[node][1] == -1)
        {
            last_index += 1;
            binary_search_tree[node][1] = last_index;
            binary_search_tree[last_index][0] = number;
        }
        else
        {
            insert_in_tree(number, binary_search_tree[node][1]);
        }
    }
    else // 중복 없어서 else if 안해줘도 됨
    {
        if (binary_search_tree[node][2] == -1)
        {
            last_index += 1;
            binary_search_tree[node][2] = last_index;
            binary_search_tree[last_index][0] = number;
        }
        else
        {
            insert_in_tree(number, binary_search_tree[node][2]);
        }
    }

}
int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int N, x;
    cin >> N >> x;
    binary_search_tree[last_index][0] = x;
    cout << c << "\n";
    for (int i = 1; i < N; i++)
    {    
        cin >> x;
        insert_in_tree(x, 0);
        cout << c << "\n";
    }
}
