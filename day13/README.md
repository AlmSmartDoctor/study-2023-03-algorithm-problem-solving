# 최소 스패닝 트리(Minimum Spanning Tree)

## Spanning Tree?

- 그래프에서 일부 간선을 선택해서 만든 트리

- 그래프 내의 모든 정점을 포함하는 트리

- 간선의 수가 가장 적은 그래프

## Spanning Tree의 특징

- 여러 Spanning Tree가 존재 가능

- DFS, BFS로 찾을 수 있고

- 사이클이 없다

- 간선의 수 n-1

통신 네트워크 구축 같은 곳에 쓰인다고 한다

## MST?

- 간선의 가중치 합이 최소

- 마찬가지로, n-1의 간선 / 사이클이 없음

## MST 구현 방법

### Kruskal 알고리즘

간선으로 iterate / Greedy method

먼저 간선을 가중치 오름차순으로 정렬

1. 간선을 선택
   1. 가중치가 가장 낮은 간선 선택
   2. 간선이 사이클을 형성하면 제거
2. 해당 간선을 MST 집합에 추가

```c++
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;


int parent[5];	//노드 연결용, 연결노드가 바뀌는지 체크

class Edge{
public:
	int node[2];
	int distance;
	Edge(int a, int b, int distance){
		this->node[0] = a;
		this->node[1] = b;
		this->distance = distance;
	}

	//오름차순 정렬 기준
	bool operator<(Edge &edge){
		return this->distance < edge.distance;
	}
};

// 부모 탐색
int findParent(int node){
	if(parent[node]==node) return node;
	return findParent(parent[node]);
}

//두 노드를 작은값을 기준으로 연
void unionParent(int node1, int node2){
	node1 = findParent(node1);
	node2 = findParent(node2);
	if(node1<node2) parent[node2] = node1;
	else parent[node1] = node2;
}

//싸이클이 존재하면 true, 아니면 false를 반환
bool isCycle(int node1, int node2){
	node1 = findParent(node1);
	node2 = findParent(node2);
	if(node1==node2) return true;
	else return false;
}

int main(){
	//그래프 생
	vector<Edge> v;
	v.push_back(Edge(0, 1, 10));
	v.push_back(Edge(0, 2, 5));
	v.push_back(Edge(1, 2, 7));
	v.push_back(Edge(1, 3, 4));
	v.push_back(Edge(2, 3, 3));
	v.push_back(Edge(2, 4, 2));
	v.push_back(Edge(3, 4, 1));

	//간선 가중치 기준 오름차순 정렬
	sort(v.begin(), v.end());

	//부모노드 초기화
	for(int i=1; i<=5; i++){
		parent[i] = i;
	}

	int sum = 0;	// 간선의 가중치 합

	for(int i=0;i<v.size();++i){
		//싸이클 여부 확인
		if(!isCycle(v[i].node[0], v[i].node[1])){
			sum += v[i].distance;
			unionParent(v[i].node[0], v[i].node[1]);
		}
	}

    // 최소 신장 트리 가중치 합 출력
	printf("%d\n", sum);

	return 0;
}
```

### Kruskal 알고리즘 시간 복잡도

간선을 가중치로 정렬 -> e log e

사이클 생성 여부 -> union-find 알고리즘 이용

### Prim 알고리즘

정점으로 iterate

1. 시작 정점을 MST 집합에 추가
2. 이전에 만들어진 MST 집합에 인접한 정점 중 최소 간선으로 연결된 정점 추가
3. 정점을 모두 포함할 때까지 반복

```c++
//code by RiKang, weeklyps.com
#include <bits/stdc++.h>
#define PII pair<int,int>

using namespace std;

const int N = 1005, INF = 2140000000;

vector<PII> ad[N];  // ad[i] : i 노드가 출발지인 간선들, first = 목적지, second = 비용
int dist[N];        // dist[i] : 선택된 노드들과 i 노드가 연결되어 있는 간선의 비용 중 최소비용
bool selected[N];   // selected[i] : i 가 이전에 선택된 노드인가?

long long prim(int pn){
    long long ret = 0;
    for(int i=1; i<=pn; i++){ // 초기화
        dist[i] = INF;
        selected[pn] = false;
    }
    dist[1] = 0;              // 1번 노드부터 선택
    for(int i=1; i<=pn; i++){
        int now=-1, min_dist = INF;
        for(int j=1; j<=pn; j++){
            if(!selected[j] && min_dist > dist[j]){
                min_dist = dist[j];
                now = j;
            }
        }
        if(now<0) return (long long)INF; // 연결 그래프가 아님
        ret+=min_dist;
        selected[now] = true;
        for(auto edge: ad[now])
            dist[edge.first] = min(dist[edge.first], edge.second);
    }
    return ret;
}

int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    while(m--){
        int v1,v2,c;
        scanf("%d %d %d",&v1,&v2,&c);
        ad[v1].push_back(PII(v2,c));
        ad[v2].push_back(PII(v1,c));
    }
    printf("%lld",prim(n));
    return 0;
}
```

### Prim 알고리즘 시간 복잡도

V-1번 인접한 정점까지의 가중치를 비교 => V^2

### Prim 변형

최소 힙으로 트리에 포함될 간선을 찾으면 E log V (다익스트라랑 비슷)

```c++
//code by RiKang, weeklyps.com
#include <bits/stdc++.h>
#define PII pair<int,int>

using namespace std;

const int N = 1005, INF = 2140000000;

vector<PII> ad[N];  // ad[i] : i 노드가 출발지인 간선들, first = 비용, second = 목적지
priority_queue<PII, vector<PII>, greater<PII> > dist;        // dist : 선택될 가능성이 있는 간선들
bool selected[N];   // selected[i] : i 가 이전에 선택된 노드인가?

void add_edge(int node){
    for(auto edge: ad[node]){
        dist.push(edge);
    }
}

long long prim(int pn){
    long long ret = 0;
    for(int i=1; i<=pn; i++){ // 초기화
        selected[pn] = false;
    }
    dist.push(PII(0,1));
    for(int i=1; i<=pn; i++){
        int now=-1, min_dist = INF;
        while(!dist.empty()){
            now = dist.top().second;
            if(!selected[now]){
                min_dist = dist.top().first;
                break;
            }
            dist.pop();
        }
        if(min_dist==INF) return (long long)INF; // 연결 그래프가 아님
        ret+=min_dist;
        selected[now] = true;
        add_edge(now);
    }
    return ret;
}

int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    while(m--){
        int v1,v2,c;
        scanf("%d %d %d",&v1,&v2,&c);
        ad[v1].push_back(PII(c,v2));
        ad[v2].push_back(PII(c,v1));
    }
    printf("%lld",prim(n));
    return 0;
}

```

## 어떤거 쓰지?

E log E vs V^2

그래프 내에 적은 숫자의 간선만을 가지는 ‘희소 그래프(Sparse Graph)’의 경우 Kruskal 알고리즘이 적합

그래프에 간선이 많이 존재하는 ‘밀집 그래프(Dense Graph)’ 의 경우는 Prim 알고리즘이 적합

### ElogE = V^2 그래프

![wolframAlpha](wolframAlpha.png)

김하진:

김재헌: https://www.acmicpc.net/problem/23743

박상준: https://leetcode.com/problems/min-cost-to-connect-all-points/description/

박진영:

서민혁:

유태정: https://www.acmicpc.net/problem/4386

이재혁:

이성구: https://www.acmicpc.net/problem/2887

조민준:

정준우:

한태혁: https://leetcode.com/problems/min-cost-to-connect-all-points/
