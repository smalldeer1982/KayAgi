# Tokens on Graph

## 题目描述

You are given an undirected connected graph, some vertices of which contain tokens and/or bonuses. Consider a game involving one player — you.

You can move tokens according to the following rules:

- At the beginning of the game, you can make exactly one turn: move any token to any adjacent vertex.
- If the movement of the token ended on the bonus, then you are allowed to make another turn with any other token.

You can use different bonuses in any order. The same bonus can be used an unlimited number of times. Bonuses do not move during the game.

There can be several tokens in one vertex at the same time, but initially there is no more than one token in each vertex.

The vertex with number $ 1 $ is the finish vertex, and your task is to determine whether it is possible to hit it with any token by making turns with the tiles according to the rules described above. If a token is initially located at the vertex of $ 1 $ , then the game is considered already won.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1790G/9201a652a27a905e421aac504488f1f5afaa448d.png) The finish line is in black, the bonuses are in red, the chips are in grey.  For example, for a given graph, you can reach the finish line with a chip from the $ 8 $ th vertex by making the following sequence of turns: 1. Move from the $ 8 $ -th vertex to the $ 6 $ -th.
2. Move from the $ 7 $ -th vertex to the $ 5 $ -th.
3. Move from the $ 6 $ -th vertex to the $ 4 $ -th.
4. Move from the $ 5 $ -th vertex to the $ 6 $ -th.
5. Move from the $ 4 $ -th vertex to the $ 2 $ -nd.
6. Move from the $ 6 $ -th vertex to the $ 4 $ -th.
7. Move from the $ 2 $ -nd vertex to the $ 1 $ -st vertex, which is the finish.

## 说明/提示

- The first test case is explained in the statement.
- In the second test case, there is only one token which can make only one turn, and it cannot reach the finish.
- In the third test case, the token can reach the finish line in $ 1 $ turn.
- In the fourth test case, you need to make just one turn from $ 2 $ to $ 1 $ .
- In the sixth test case, the token is initially at node number $ 1 $ , so we win immediately.

## 样例 #1

### 输入

```
6
8 10
2 4
7 8
2 4 5 6
1 2
2 3
2 4
3 4
3 5
4 6
5 6
5 7
6 8
7 8


5 4
1 1
5
3
1 2
2 3
3 4
4 5


2 1
1 0
2


1 2


4 3
1 2
2
3 4
1 2
2 3
2 4


5 4
3 2
5 3 4
2 4
1 2
2 3
3 4
4 5


1 0
1 1
1
1```

### 输出

```
YES
NO
YES
YES
YES
YES```

# 题解

## 作者：Leasier (赞：4)

这道 3G 就算不考虑 WA on 1 那一发我还是 WA 了两发，没救了 /kk

------------

考虑一条符合条件的路径：$u \to p_1 \to p_2 \to \cdots p_k \to 1$，其中 $p_1, p_2, \cdots, p_k$ 均为 bonus。

那在走这条路径时，我们需要其他棋子干啥呢？除了第一步 $u \to p_1$，后面每一步都需要其他棋子走一步才能接着走。

考虑从 $1$ 开始 bfs 求出其到每个点只走 bonus 的最短路，现在我们还需要知道从每个点出发只走 bonus 至多走几步，设之为 $v_u$。

1. $u$ 周围没有 bonus

此时走不动，则 $v_u = 0$。

2. $u$ 周围有 bonus，但不存在 bonus 周围还有 bonus

此时只能走一步，则 $v_u = 1$。

3. $u$ 周围有 bonus，且存在 bonus 周围还有 bonus

此时可以反复横跳，则 $v_u = +\infty$。

于是可以求得其他棋子可以提供的步数，即其 $v_i$ 之和。

时间复杂度为 $O(\sum(n + m))$。

代码：
```cpp
#include <iostream>
#include <queue>
#include <cstdio>

using namespace std;

typedef long long ll;

typedef struct {
	int nxt;
	int end;
} Edge;

int cnt;
int head[200007], bucket[200007], dis[200007], val[200007];
bool bonus[200007], inf[200007];
Edge edge[400007];
queue<int> q;

inline void init(int n){
	cnt = 0;
	for (int i = 1; i <= n; i++){
		head[i] = bucket[i] = 0;
		dis[i] = 0x7fffffff;
		bonus[i] = false;
	}
}

inline void add_edge(int start, int end){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].end = end;
}

inline void bfs(int start){
	dis[start] = 0;
	q.push(start);
	while (!q.empty()){
		int cur = q.front(), dis_i = dis[cur] + 1;
		q.pop();
		for (int i = head[cur]; i != 0; i = edge[i].nxt){
			int x = edge[i].end;
			if (bonus[x] && dis[x] == 0x7fffffff){
				dis[x] = dis_i;
				q.push(x);
			}
		}
	}
}

int main(){
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++){
		int n, m, p, b;
		scanf("%d %d", &n, &m);
		scanf("%d %d", &p, &b);
		init(n);
		for (int j = 1; j <= p; j++){
			int x;
			scanf("%d", &x);
			bucket[x]++;
		}
		for (int j = 1; j <= b; j++){
			int x;
			scanf("%d", &x);
			bonus[x] = true;
		}
		for (int j = 1; j <= m; j++){
			int u, v;
			scanf("%d %d", &u, &v);
			add_edge(u, v);
			add_edge(v, u);
		}
		if (bucket[1] > 0){
			cout << "YES" << endl;
			continue;
		}
		ll sum = 0;
		bool ans = false;
		for (int j = 1; j <= n; j++){
			if (bonus[j]){
				inf[j] = false;
				for (int k = head[j]; k != 0; k = edge[k].nxt){
					int x = edge[k].end;
					if (bonus[x]){
						inf[j] = true;
						break;
					}
				}
			}
		}
		for (int j = 1; j <= n; j++){
			val[j] = 0;
			for (int k = head[j]; k != 0; k = edge[k].nxt){
				int x = edge[k].end;
				if (bonus[x]){
					if (!inf[x]){
						val[j] = max(val[j], 1);
					} else {
						val[j] = 0x7fffffff;
					}
				}
			}
		}
		for (int j = 2; j <= n; j++){
			sum += (ll)bucket[j] * val[j];
		}
		bfs(1);
		for (int j = 2; j <= n && !ans; j++){
			if (bucket[j] > 0){
				for (int k = head[j]; k != 0; k = edge[k].nxt){
					int x = edge[k].end;
					if (x == 1 || (bonus[x] && dis[x] != 0x7fffffff && sum - val[j] >= dis[x])){
						ans = true;
						break;
					}
				}
			}
		}
		if (ans){
			cout << "YES" << endl;
		} else {
			cout << "NO" << endl;
		}
	}
	return 0;
}
```

---

## 作者：happybob (赞：2)

感觉是比较好想的。

考虑对于每个点判断从这个点出发能不能到达 $1$ 号点。能到达的必要条件是存在一条从这个点到 $1$ 的路径，其上除了这个点和 $1$ 号点外的所有点都是特殊点。

但这个条件并不充分。由于每到一个特殊点，我们要移动一个**其他**棋子，所以我们必然想让这条路径尽量短。容易广搜在 $O(n+m)$ 的复杂度内处理这个东西。

接着我们考虑其他棋子的贡献。分为四种：

1. 存在一个点上有棋子，且这个点是特殊点，与其相邻的点中有至少一个特殊点。这种情况下，来回走，就可以无限地贡献。

2. 存在一个点上有棋子，这个点不是特殊点，但这个点相邻的点中有至少一个点在大小不小于 $2$ 地特殊点连通块中。容易发现也是无限贡献。

3. 这个点相邻地点只有大小为 $1$ 地连通块，贡献为这个点棋子数量，显然，由于每个点只能出去一次，且回不来。

4. 这个点相邻点中没有特殊点。贡献为 $0$。

上述分类都容易计算，于是做完了。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#include <string>
#include <vector>
using namespace std;
 // 111321443123
const int N = 2e5 + 5;

int t, n, p, b, m;
vector<int> G[N];
bool is[N];
int c[N];
int dis[N];

void bfs()
{
	queue<int> q;
	q.push(1);
	for (int i = 2; i <= n; i++) dis[i] = -1;
	dis[1] = 0;
	while (q.size())
	{
		int u = q.front();
		q.pop();
		for (auto& j : G[u])
		{
			if (dis[j] == -1)
			{
				dis[j] = dis[u] + 1;
				if (is[j]) q.push(j);
			}
		}
	}
}

int cc[N];

int main()
{
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> t;
	while (t--)
	{
		cin >> n >> m >> p >> b;
		for (int i = 1; i <= n; i++)
		{
			cc[i] = 0;
			G[i].clear();
			is[i] = 0;
			c[i] = 0;
		}
		for (int i = 1; i <= p; i++)
		{
			int x;
			cin >> x;
			c[x]++;
		}
		for (int i = 1; i <= b; i++)
		{
			int x;
			cin >> x;
			is[x] = 1;
		}
		for (int i = 1; i <= m; i++)
		{
			int u, v;
			cin >> u >> v;
			G[u].emplace_back(v);
			G[v].emplace_back(u);
		}
		for (int i = 1; i <= n; i++)
		{
			for (auto& j : G[i])
			{
				if (is[j]) cc[i]++;
			}
		}
		bfs();
		long long nowres = 0;
		for (int i = 1; i <= n; i++)
		{
			if (is[i] && cc[i])
			{
				nowres += N * 1LL * c[i];
			}
			else if (cc[i])
			{
				bool f = 0;
				for (auto& j : G[i])
				{
					if (is[j])
					{
						int nc = cc[j] - (is[i]);
						if (nc > 0)
						{
							f = 1;
						}
					}
				}
				if (f) nowres += N * 1LL * c[i];
				else nowres += c[i];
			}
		}
		if (c[1] > 0) cout << "YES\n";
		else
		{
			bool ff = 0;
			for (int i = 2; i <= n; i++)
			{
				if (dis[i] == -1 || !c[i]) continue;
				int g = dis[i] - 1;
				long long nres = nowres;
				if (is[i] && cc[i])
				{
					nres -= N * 1LL;
				}
				else if (cc[i])
				{
					bool f = 0;
					for (auto& j : G[i])
					{
						if (is[j])
						{
							int nc = cc[j] - (is[i]);
							if (nc > 0)
							{
								f = 1;
							}
						}
					}
					if (f) nres -= N * 1LL;
					else nres--;
				}
				if (nres >= g)
				{
					ff = 1;
					//cout << i << " " <<
				}
			}
			if (ff) cout << "YES\n";
			else cout << "NO\n";
		}
	}
	return 0;
}
```

---

## 作者：banned_gutongxing (赞：1)

## 思路

首先我们来想一想什么时候无解。如果一个令牌能够走到 1 节点，那么路上的点必须是关键点。那么我们从 1 节点沿着关键点走下来所能到的点就有可能最后到达 1 节点。所以我们可以从 1 节点开始 BFS，直到点为非关键点。统计 BFS 树上的令牌数 $sum$：

+ $sum=0$\
	此时没有一个令牌能够到达 1 节点，无解。
+ $sum\ge2$\
	此时至少两个令牌，我们只用其中两个令牌。此时两个令牌可以你走一步，我也走一步到达 1 节点，一定有解。
+ $sum=1$\
	此时只有一个令牌，只能让这个令牌走到 1 节点。此时考虑一下其他的令牌。
	1. 如果令牌是关键点：
        + 如果能到达的点包含关键点，此时这个令牌可以左右横跳，这个令牌走一步，树上的令牌走一步，必定有解。
        + 如果不能到达关键点，此时这个令牌所贡献的只有 1 步。
   2. 如果令牌是普通的点：
       + 如果能够到达关键点：
           + 如果这个关键点可以左右横跳，那么也是有解
           + 如果这个关键点只能走一步，那么这个普通的点的贡献为 1 步。
       
       + 如果不能到达关键点：那么这个普通的点的贡献为 0 步。
   
   最后，如果贪心地走。先让树上关键点前进一步，若其他令牌提供的步数能让关键点走完接下来的路程，那么就是可以的，不然就不行。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 3e5+100;
const int INF = 0x3f3f3f3f3f3f;
//Normal
int T,n,m,p,b;
bool che[MAXN];
bool VIP[MAXN];
int sol[MAXN];
vector<int> v[MAXN]; 
//BFS
bool vis[MAXN];
int dis[MAXN];
struct Bfs_node{
	int id,step;
};
queue<Bfs_node> q;
bool Push(int id,int step){
	if(vis[id]) return false;
	vis[id] = 1;
	dis[id] = step;
	q.push({id,step});
	return true;
}
void bfs(){
	Push(1,0);
	while(!q.empty()){
		auto x = q.front();q.pop();
		for(int i:v[x.id]){
			if((VIP[x.id])) Push(i,x.step+1);
		}
	}
}
//Normal
void clear(){
	for(int i = 1;i<=n;i++){
		VIP[i] = 0;
		che[i] = 0;
		vis[i] = 0;
		dis[i] = 0;
		sol[i] = 0;
		v[i].clear();
	}
}
//Debug
int Debug_cnt;
void Debug(){
	while(++Debug_cnt<=T){
		if(Debug_cnt==4363){
			scanf("%lld%lld",&n,&m);
			printf("%lld %lld\n",n,m);
			scanf("%lld%lld",&p,&b);
			printf("%lld %lld\n",p,b);
			for(int i = 1;i<=p;i++){
				int x;scanf("%lld",&x);
				printf("%lld ",x);
			}puts("");
			for(int i = 1;i<=b;i++){
				int x;scanf("%lld",&x);
				printf("%lld ",x);
			}puts("");
			for(int i = 1;i<=m;i++){
				int x,y;
				scanf("%lld%lld",&x,&y);
				printf("%lld %lld\n",x,y);
			}
		}else{
			scanf("%lld%lld",&n,&m);
			scanf("%lld%lld",&p,&b);
			for(int i = 1;i<=p;i++){
				int x;scanf("%lld",&x);
			}
			for(int i = 1;i<=b;i++){
				int x;scanf("%lld",&x);
			}
			for(int i = 1;i<=m;i++){
				int x,y;
				scanf("%lld%lld",&x,&y);
			}
		}
	}
	exit(0);
}

signed main(){
	scanf("%lld",&T);
//	if(T==10000){
//		Debug();
//	}
	while(T--){
		scanf("%lld%lld",&n,&m);
		clear();
		scanf("%lld%lld",&p,&b);
		for(int i = 1;i<=p;i++){
			int x;scanf("%lld",&x);
			che[x] = 1;
		}
		for(int i = 1;i<=b;i++){
			int x;scanf("%lld",&x);
			VIP[x] = 1;
		}
		VIP[1] = 1;
		for(int i = 1;i<=m;i++){
			int x,y;
			scanf("%lld%lld",&x,&y);
			v[x].push_back(y);
			v[y].push_back(x);
		}
		bfs();
		int cnt=0,tmp,tmp1;
		for(int i = 1;i<=n;i++){
			if(che[i]&&vis[i]){
				cnt++;
				tmp = dis[i];
				tmp1 = i;
			}
		}
		if(cnt>=2) puts("Yes");
		else if(cnt==0) puts("No");
		else{
			for(int i = 1;i<=n;i++){
				if(VIP[i]){
					for(int j:v[i]){
						if(VIP[j]){
							sol[i] = INF;
							break;
						}
					}
				}
			}
			for(int i = 1;i<=n;i++){
				if(!VIP[i]){
					for(int j:v[i]){
						if(VIP[j]){
							if(sol[j]==INF) sol[i] = INF;
							else sol[i] = max(sol[i],1ll);
						}
					}
				}
			}
			bool bj = 0;int cnt = 0;
			for(int i = 1;i<=n;i++){
				if(che[i]&&i!=tmp1){
					if(sol[i]==INF){
						bj = 1;
						break;
					}
					cnt+=sol[i];
				}
			}
			if(bj) puts("Yes");
			else{
				if(cnt+1>=tmp) puts("Yes");
				else puts("No");
			}
		}
	}
	return 0;
}
/*
1
5 4
2 4
4 3 
1 5 4 2 
1 2
2 3
3 4
3 5

*/
```

---

## 作者：qw1234321 (赞：1)

难度 \*$2300$，其实比较水。

先求出终点（$1$）到每个点的最短路，用 BFS 实现即可。

其次，考虑枚举一下被辅助到终点的棋子是哪一颗，设为 $i$，其他的棋子在 $i$ 移动的时候起辅助作用，即 $i$ 每向 $1$ 走一步其他棋子也在特殊点上来回走辅助 $i$ 点有足够的步数到达终点 $1$。

于是求出每个点能辅助 $i$ 走几步即可，设当前辅助点为 $u$。

1. $u$ 为红点且为灰点（特殊点和棋子）：

若有一特殊点 $v$，使 $u,v$ 之间有边，那么棋子 $u$ 便可以在 $u,v$ 之间来回走，贡献为无数步。

反之，$u$ 无法进行移动，贡献为 $0$ 步。

2. $u$ 仅为灰点（只是棋子）：

（1）若有一特殊点 $v$，使 $u,v$ 之间有边：

若还有一特殊点 $w$，且 $v,w$ 之间有边，那么棋子 $u$ 可以先走到 $v$，然后在 $v,w$ 之间来回走，贡献为无数步。

反之，则棋子 $u$ 走到 $v$ 后无法进行移动，贡献为 $1$ 步。

（2）无一特殊点 $v$，使 $u,v$ 之间有边：

$u$ 无法进行移动，贡献为 $0$ 步。

于是便得到了每个点的贡献步数。

code：

```cpp
#include<bits/stdc++.h>
#define int long long
#define il inline
namespace things{
	il int rd(){
		int f = 1, x = 0;
		char ch = getchar();
		while(ch < '0' || ch > '9'){
			if (ch == '-') f = -1;
			ch = getchar();
		}
		while(ch >= '0' && ch <= '9'){
			x = x * 10 + ch - '0';
			ch = getchar();
		}
		return x * f;
	}
}
using namespace things;
using namespace std;

const int N = 2e5 + 5, M = 4e5 + 5, INF = 0x3f3f3f3f;
int n, m, p, b, ok[N], st[N];
struct node{
	int to, next;
}e[M];
int dis[N], ans[N], sum;
vector<int> g[N];
map<int, int> mp;

queue<int> q;
void bfs(int s){
	q.push(s);
	dis[s] = 0;
	while(q.size()){
		int u = q.front();
		q.pop();
		for (int v : g[u]){
			if (dis[v] > dis[u] + 1 && (u == 1 || ok[u])){
				dis[v] = dis[u] + 1;
				q.push(v);
			}
		}
	}
}

int calc(int u){
	if (ok[u]){
		for (int v : g[u]){
			if (ok[v]) return INF;
		}
	}
	else{
		for (int v : g[u]){
			if (ok[v]){
				for (int w : g[v]){
					if (ok[w]) return INF;
				}
				return 1;
			}
		}
	}
	return 0;
}

il void work(){
	n = rd(), m = rd(), p = rd(), b = rd();
	for (int i = 1; i <= n; i++) dis[i] = INF, ok[i] = 0, g[i].clear();
	sum = 0, mp.clear();
	for (int i = 1; i <= p; i++) st[i] = rd(), mp[st[i]] = 1;
	for (int i = 1, x; i <= b; i++){
		x = rd();
		ok[x] = 1;
	}	
	for (int i = 1, u, v; i <= m; i++){
		u = rd(), v = rd();
		g[u].push_back(v), g[v].push_back(u);
	}
	bfs(1);
	for (int i = 1; i <= p; i++) ans[st[i]] = calc(st[i]), sum += ans[st[i]];
	for (int i = 1; i <= p; i++){
		if (dis[st[i]] < INF && dis[st[i]] - 1 <= sum - ans[st[i]]){
			cout << "YES\n";
			return ;
		}
	}
	cout << "NO\n";
}

signed main(){
	int t = 1;
	t = rd();
	while(t--) work();
	return 0;
}
```

---

## 作者：紊莫 (赞：1)

思路比较简单，~~但是我看错题~~。

首先我们进行一次 BFS，求出从每个点到 $1$ 号点的最短距离。那么我们枚举最终走到 $1$ 的那个棋子，发现除了一开始的点和 $1$ 号点，他只能走特殊点，并且需要一个其他的点来辅助。那么我们计算每个点作为辅助能贡献几步，这个比较好算，因为当特殊点的数量大于 $2$ 的时候答案就是无穷大。然后枚举的时候比较一下自己需要移动的步数（最短路长）和**其他**点能贡献的答案即可。

具体看代码。

```cpp
const int N=200005,M=(N<<1),inf=0x3f3f3f3f,mod=1e9+7;
int n,m,p,sum,b,t[N],c[N],d[N],v[N]; vector<int> G[N];
int find(int x){for(int i:G[x])if(t[i]) {return 1;} return 0;}
void bfs(){
	memset(d,0x3f,sizeof d);queue<Pair> q; q.push({1,0}); d[1]=0; while(q.size()){
		int f = q.front().first; q.pop(); 
		if(t[f]||f==1){for(int i:G[f])if(d[f]+1<d[i]){q.push({i,d[i]=d[f]+1});}}
	}
}
int ck(int x){
	int ans = 0;
	if(t[x]){
		ans = find(x)?inf:0;
	}else {
		for(int i:G[x]) if(t[i]){
			if(find(i)) ans = inf;
			else ans = max(ans,1ll);
		}
	}
	return ans;
}
void solve(int T){
	n = rd();m = rd();p = rd();b = rd(); F(i,1,p) c[rd()] = 1;F(i,1,b) t[rd()] = 1;
	F(i,1,m){int u = rd(),v = rd();G[u].push_back(v), G[v].push_back(u);}
	bfs(); F(i,1,n){if(c[i]) sum += v[i] = ck(i);} //F(i,1,n) cerr<<v[i]<<' ';cerr<<endl;
	int ans=0; F(i,1,n){if(c[i]&&d[i]<inf&&sum-v[i]>=d[i]-1) {ans = 1; break;}}
	puts(ans?"YES":"NO");sum = 0;F(i,1,n) t[i] = c[i] = 0,G[i].clear();
}
```


---

## 作者：elbissoPtImaerD (赞：1)

考虑枚举移动到终点的棋子位置。

其他棋子在轮流移动时起过渡作用。

考虑其它棋子能贡献多少步数：

1. 没有特殊点和 $u$ 相邻：$0$。
2. 存在特殊点和 $u$ 相邻：  
	若特殊点连通块 $=1$：$1$。  
   连通块大小 $>1$：$\inf$。

先预处理处最短路，再处理出每个点的贡献步数即可 check。

```cpp
il void Solve()
{
  int n,m;
  rd(n),rd(m);
  ve<ve<int>>G(n);
  auto[a,tg]=[&]
  {
    int k,kk;
    rd(k),rd(kk);
    ve<int>a(k),b(n),c(n);
    for(int x;k--;rd(x),++c[--x]);
    for(int x;kk--;rd(x),--x,b[x]|=1);
    return make_pair(c,b);
  }();
  for(int u,v,_=m;_--;rd(u),rd(v),--u,--v,G[u].pb(v),G[v].pb(u));
  if(a[0]) return wrt("Yes\n"),void();
  auto dis=[&]
  {
    ve<int>dis(n,-1);
    sd queue<int>q;
    for(tg[0]=1,q.ep(dis[0]=0);q.size();)
    {
      int u=q.front();
      q.pop();
      for(int v:G[u])
      if(!~dis[v]&&tg[u]) dis[v]=dis[u]+1,q.ep(v);
    }
    return dis;
  }();
  ve<int>c(n);
  for(int u=0;u<n;++u) for(int v:G[u]) c[u]|=tg[v];
  LL s=0;
  ve<int>g(n);
  for(int u=0;u<n;++u) if(a[u]&&c[u])
  {
    int f=0;
    for(int v:G[u]) if(tg[v]) f|=c[v];
    g[u]=f?m+1:1,s+=1ll*g[u]*a[u];
  }
  int f=0;
  for(int u=0;u<n;++u) if(~dis[u]&&a[u]) f|=s-g[u]>=dis[u]-1;
  wrt(f?"Yes\n":"No\n");
  return;
}
```

[$\color{green}{\checkmark}$](https://codeforces.com/contest/1790/submission/239804480)

---

## 作者：2018ljw (赞：0)

把 $1$ 号点视为红色，显然只需要考虑每个红色连通块及其相邻棋子的情况。

首先必须要有至少一个棋子在 $1$ 的连通块内。如果至少有两个棋子在块内必定有解，否则考虑其它棋子运动情况。

这个棋子一定是要沿最短路走到 $1$ 的，所以先从 $1$ 跑一边道中只经过红色点的最短路。

那么我们只关心其它棋子能否凑出中间需要的 $dis-1$ 步。

若另一个棋子能走到大小 $\ge 2$ 的连通块，那么这两个棋子交替行动即可。

否则只需要统计有多少棋子能进行一次行动即可。[record](https://codeforces.com/contest/1790/submission/211248678)。

---

