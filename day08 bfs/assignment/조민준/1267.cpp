#include<iostream>
#include<queue>
#include<set>

using namespace std;

struct elem{
	int n;
	int count;
};
elem elems[1001];
queue<int> get_target[1001];

int main(int argc, char** argv)
{
	int test_case;
	int T = 10;

	freopen("input.txt", "r", stdin);

	for(test_case = 1; test_case <= T; ++test_case)
	{
		int v, e;
		set<int> task;
		cin >> v >> e;


		for(int i = 1; i <= v; i++){
			elem e = {i, 0};
			elems[i] = e;
			task.insert(i);
			get_target[i] = queue<int>();
		}

		for(int i = 0; i < e; i++)
		{
			int a, b;
			cin >> a >> b;

			get_target[a].push(b);
			elems[b].count++;
		}

		cout << "#" << test_case;

		int task_size = 0;
		
		while(!task.empty()){
			if(task_size == task.size()) break;
			task_size = task.size();
			queue<int> erased;
			
			for(int idx: task){
				elem cur = elems[idx];

				if(cur.count == 0){
					erased.push(idx);
					auto cur_target = get_target[idx];

					while(!cur_target.empty()){
						int t = cur_target.front();
						cur_target.pop();
						elems[t].count--;
					}
				}
			}

			while(!erased.empty()){
				int t = erased.front();
				erased.pop();
				task.erase(t);

				cout << " " << t;
			}
		}

		cout << endl;
	}

	return 0;
}