# Going Home

## 题目描述

# 回家

在网格地图上有 $n$ 个人和 $n$ 个房子。在每个单位时间里，每个人都可以在相邻的点上水平或垂直移动一个单位步。对于每个人，你需要为他每走一步支付 $1$ 美元的旅行费，直到他进入一所房子。由于每栋房子只能容纳一个人，这项任务很复杂。  
你的任务是计算你需要支付的最低金额，以便将这 $n$ 个人送到那 $n$ 个不同的房子里。输入是场景的地图，`.` 表示空白空间，`H`表示该点上的房子，`m`表示在该点上有一个人。  
你可以把网格地图上的每个点想象成一个相当大的正方形，所以它可以同时容纳 $n$ 个人物；此外，如果一个人在没有进入房子的情况下踩在有房子的网格上，也没关系。

## 样例 #1

### 输入

```
2 2
.m
H.
5 5 
HH..m 
..... 
.....
.....
mm..H
7 8
...H....
...H....
...H.... 
mmmHmmmm 
...H.... 
...H.... 
...H.... 
0 0```

### 输出

```
2
10
28```

# 题解

## 作者：William2022 (赞：1)

# Going Home 题解  
## 题目大意  
在一个 $n\times m$ 的地图上，存在等量的人和房子，一个人走到一个房子的代价为他们的曼哈顿距离。  
我们需要安排人与房子的对应关系，使得**总代价**最小。    
$n,m\leq 100$  
## 样例分析  
```
HH..m 
..... 
.....
.....
mm..H
```
按照题目画出的图走就是最优方法。  
![](https://cdn.luogu.com.cn/upload/image_hosting/b1wflf76.png)    
$ans=10$  
## 思考  
注意到：  
1. 每一个人都要找到房子，每一个房子都要找到人，是**匹配**问题
2. 匹配时候不同的对应关系有不同的**代价**

根据第一条，想到网络流进行匹配，考虑到第二条，应当使用费用流。  
## 图论建模  
人和房子是对应的，网络流建立如下：  
1. 每个人作为源点，仅能流出 $1$ 的流量  
2. 每个房子作为汇点，仅能接受 $1$ 的流量
  
而对于每个人都可以选择每个房子，所以对于每一个人，连接到每一个房子，费用为他们之间的曼哈顿距离。  
跑最小费用最大流。  
## 程序设计  
1. 一个超级源点，对每一个人指向一条流量为 $1$，费用为 $0$ 的边  
2. 一个超级汇点，所有房子对其指向一条流量为 $1$，费用为 $0$ 的边  
3. 枚举每一个人，对每个房子指向一条费用为他们之间曼哈顿距离的边  
4. 答案即为最大流的最小费用

代码
```cpp
#include<bits/stdc++.h>
typedef long long ll;

const int E=25e6+10;
const int V=1e4+10;

int n,m;

struct pair{int x,y,id;};//这里的id指这个人或者房子在图中的编号
struct Star{int to,w,c,nxt;};
Star e[E*2];
int hd[V],star=1;

void addEdge(int u,int v,int w,int c){
	star++;
	e[star]={v,w,c,hd[u]};
	hd[u]=star;
}
void CostFlow(int u,int v,int w,int c){//建立流量边
	addEdge(u,v,w,c);
	addEdge(v,u,0,-c);
}

const int S=1,T=2;//超级源点，超级汇点
int cnt=2;//往后开点

int Distance(const pair &a,const pair &b){
	return abs(a.x-b.x)+abs(a.y-b.y);
}

int dis[V],pre[V];

bool SPFA(){
	std::bitset<V> in;
	std::queue<int> q;
	memset(dis,0x3f,sizeof(dis));
	
	q.push(S);
	dis[S]=0;
	in[S]=1;
	
	while(!q.empty()){
		int u=q.front();q.pop();
		in[u]=0;
		
		for(int id=hd[u];id;id=e[id].nxt){
			int v=e[id].to,w=e[id].w,c=e[id].c;
			if(!w)continue;
			
			if(dis[u]+c<dis[v]){
				pre[v]=id;
				dis[v]=dis[u]+c;
				if(!in[v]){
					q.push(v);
					in[v]=1;
				}
			}
		}
	}
	return (dis[T]<(int)(1e9));// 能否到达汇点
}
ll SSP(){//最小费用最大流 ssp
	ll ans=0;
	while(SPFA()){
		ans+=dis[T];
		for(int u=T;u!=S;u=e[pre[u]^1].to){
			e[pre[u]].w=0;
			e[pre[u]^1].w=1;
		}
	}
	return ans;
}

ll solve(){
	star=1;
	memset(hd,0,sizeof(hd));
	//输入
	std::vector<pair> H,M;//分别代表人和房子出现的位置
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char c;
			std::cin>>c;
			if(c=='H')H.push_back({i,j,++cnt});
			else if(c=='m')M.push_back({i,j,++cnt});
		}
	}
	
	//图论建模
	for(pair p:H)CostFlow(S,p.id,1,0);
	for(pair p:M)CostFlow(p.id,T,1,0);
	
	for(pair a:H){
		for(pair b:M){
			CostFlow(a.id,b.id,1,Distance(a,b));
		}
	}
	//最小费用最大流
	
	return SSP();
}

signed main(){
	std::ios::sync_with_stdio(0);std::cout.tie(0);std::cin.tie(0);
	
	while(std::cin>>n>>m){
		if(!n)break;
		std::cout<<solve()<<"\n";
	}
}
```

---

## 作者：CommonDigger (赞：1)

题意：给每个人匹配一个房子，使得每个人回家的路程之和最小。

容易证明对每个人寻找最近的房子的贪心思想是错误的。可以考虑将房子连上源点，人连上汇点，每个人到每个房子连边，计算最小费用最大流。

类似的二分图（或者网络流？）的建模套路还有将横纵坐标建点，原本的点当作边等等。

Dinic 貌似会写挂，调了好久还是改成了 EK。更多细节见代码注释。

```cpp
/*
Luogu P10943 Going Home
https://www.luogu.com.cn/problem/P10943
*/
#include <iostream>
#include <queue>
#include <cstring>
#define INF 1061109567
using namespace std;
const int N=205, M=10205;
int n, m, g, gh, gm, S, T;
int head[N], dep[N], dis[N], pre[N], idx=1, C, ans;
bool vis[N];
struct edge {
    int to, nxt, w, c;
}e[M*2];
struct point { // 记录人或房子坐标的点
    int x, y;
    point(int x=0, int y=0) {
        this->x=x;
        this->y=y;
    }
}house[105], men[105];
void add_edge(int u, int v, int w, int c) {
    e[++idx].to=v;
    e[idx].w=w;
    e[idx].c=c;
    e[idx].nxt=head[u];
    head[u]=idx;
    e[++idx].to=u;
    e[idx].w=0;
    e[idx].c=-c;
    e[idx].nxt=head[v];
    head[v]=idx;
}
int dist(int ih, int im) { // 求编号为ih的房子与编号为im的人之间距离
    return abs(house[ih].x-men[im].x) + abs(house[ih].y-men[im].y);
}
int min2(int x, int y) {
    return x<y ? x : y;
}
void init() {
    for (int i=1;i<N;i++) head[i]=0;
    idx=1, gh=0, gm=0, ans=0, C=0;
}
bool spfa() {
    memset(dis, 0x3f, sizeof(dis));
    dis[S]=0;
    queue<int>q;
    q.push(S);
    while (!q.empty()) {
        int x=q.front();
        q.pop();
        vis[x]=false;
        for (int i=head[x]; i; i=e[i].nxt) {
            int to=e[i].to;
            if (dis[to] > dis[x]+e[i].c && e[i].w) {
                dis[to] = dis[x]+e[i].c;
                pre[to] = i;
                if (!vis[to]) {
                    vis[to]=true;
                    q.push(to);
                }
            }
        }
    }
    return dis[T] != INF;
}
void EK() {
    while (spfa()) {
        int min_flow=INF;
        for (int walker=T; walker!=S; walker=e[pre[walker]^1].to)
            min_flow = min2(min_flow, e[pre[walker]].w);
        for (int walker=T; walker!=S; walker=e[pre[walker]^1].to) {
            e[pre[walker]].w -= min_flow;
            e[pre[walker]^1].w += min_flow;
            C += e[pre[walker]].c*min_flow;
        }
    }
}
void GoHome() {
    init();
    cin >> n >> m;
    if (n+m == 0) return;
    char temp;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++) {
            cin >> temp;
            // gh gm 分别记录房子和人总数
            if (temp=='H') house[++gh]=point(i, j);
            else if (temp=='m') men[++gm]=point(i, j);
        }
    g=gh; // g：匹配的数量
    S=1, T=1+g+g+1;
    // 源点向每个房子连边，边权为1表示房子只能容纳一个人
    for (int i=1;i<=g;i++) add_edge(1, 1+i, 1, 0);
    // 每个人向汇点连边，边权为1表示一个人只能属于一个房子
    for (int i=1;i<=g;i++) add_edge(1+g+i, T, 1, 0);
    for (int i=1;i<=g;i++)
        for (int j=1;j<=g;j++)
            add_edge(1+i, 1+g+j, 1, dist(i, j));
    EK();
    cout << C << "\n";
    GoHome();
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    GoHome();
}
```

---

## 作者：CNS_5t0_0r2 (赞：0)

比较板的二分图带权匹配。

注意到人之间是相互独立的，房子之间也是相互独立的，并且一个人只能住在一个房子里，这恰好满足二分图的建模条件。

对于任意 $i \in [1,n],j \in [1,n]$ 将第 $i$ 个人和第 $j$ 个房子连边，边权为两点的曼哈顿距离。最小费用就是最大权匹配中边权和最小者。

我用的是费用流写法，本题不卡费用流，所以用普通的 EK 就能过。

```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second
using namespace std;
const int N = 5002,M = 5e4 + 9,INF = 0x3f3f3f3f3f3f3f3f;//5002好闪！ 
int n,m;
int s,t;
pair<int,int> l[N],r[N];
int cnt_l,cnt_r;
struct edge{
	int to,cap,cost,nex;
} e[M << 1];
int head[N],ecnt;
void addedge(int u,int v,int c,int w){
	ecnt++;
	e[ecnt] = (edge){v,c,w,head[u]};
	head[u] = ecnt;
}
int pre[N];
int flow[N],dis[N];
bool in_queue[N];
int SPFA(int s,int t){
	for(int i = 0;i <= cnt_l + cnt_r + 1;i++){
		dis[i] = INF;
		in_queue[i] = false;
	}
	flow[s] = INF;
	dis[s] = 0;
	queue<int> q;
	q.push(s);
	in_queue[N] = true;
	while(!q.empty()){
		int u = q.front();
		q.pop();
		in_queue[u] = false;
		for(int i = head[u];i;i = e[i].nex){
			int v = e[i].to,c = e[i].cap,w = e[i].cost;
			if(!c)
				continue;
			if(dis[v] > dis[u] + w){
				dis[v] = dis[u] + w;
				flow[v] = min(flow[u],c);
				pre[v] = i;
				if(!in_queue[v]){
					in_queue[v] = true;
					q.push(v);
				}
			}
		}
	}
	if(dis[t] == INF)
		return 0;
	return flow[t];
}
void update(int f){
	int cur = t;
	while(cur != s){
		int i = pre[cur];
		e[i].cap -= f;
		e[i ^ 1].cap += f;
		cur = e[i ^ 1].to;
	}
}
int max_flow,min_cost;
void clear(){
	ecnt = 1;
	max_flow = min_cost = 0;
	for(int i = 0;i <= cnt_l + cnt_r + 1;i++)
		head[i] = 0;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	while(1){
		cin >> n >> m;
		if(!n && !m)
			return 0;
		cnt_l = cnt_r = 0;
		for(int i = 1;i <= n;i++){
			char str[N];
			cin >> (str + 1);
			for(int j = 1;j <= m;j++){
				if(str[j] == 'H')
					l[++cnt_l] = make_pair(i,j);
				if(str[j] == 'm')
					r[++cnt_r] = make_pair(i,j);
			}
		}
		clear();
		s = 0;t = cnt_l + cnt_r + 1;
		for(int i = 1;i <= cnt_l;i++){
			for(int j = 1;j <= cnt_r;j++){
				addedge(i,j + cnt_l,1,abs(l[i].x - r[j].x) + abs(l[i].y - r[j].y));
				addedge(j + cnt_l,i,0,-(abs(l[i].x - r[j].x) + abs(l[i].y - r[j].y)));
			}
		}
		for(int i = 1;i <= cnt_l;i++){
			addedge(s,i,1,0);
			addedge(i,s,0,0);
		}
		for(int i = cnt_l + 1;i <= cnt_l + cnt_r;i++){
			addedge(i,t,1,0);
			addedge(t,i,0,0);
		}
		while(1){
			int f = SPFA(s,t);
			if(!f)
				break;
			max_flow += f;
			min_cost += f * dis[t];
			update(f);
		}
		cout << min_cost << '\n';
	}
	return 0;
}
```

---

