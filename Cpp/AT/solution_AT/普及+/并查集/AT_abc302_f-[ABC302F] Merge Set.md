# [ABC302F] Merge Set

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc302/tasks/abc302_f

黒板に $ 1 $ 以上 $ M $ 以下の整数からなる集合 $ N $ 個 $ S_1,S_2,\dots,S_N $ が書かれています。ここで、$ S_i\ =\ \lbrace\ S_{i,1},S_{i,2},\dots,S_{i,A_i}\ \rbrace $ です。

あなたは、以下の操作を好きな回数（$ 0 $ 回でもよい）行うことが出来ます。

- $ 1 $ 個以上の共通した要素を持つ $ 2 $ 個の集合 $ X,Y $ を選ぶ。$ X,Y $ の $ 2 $ 個を黒板から消し、新たに $ X\cup\ Y $ を黒板に書く。
 
ここで、$ X\cup\ Y $ とは $ X $ か $ Y $ の少なくともどちらかに含まれている要素のみからなる集合を意味します。

$ 1 $ と $ M $ が両方含まれる集合を作ることが出来るか判定してください。出来るならば、必要な操作回数の最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ \le\ N\ \le\ 2\ \times\ 10^5 $
- $ 2\ \le\ M\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ \sum_{i=1}^{N}\ A_i\ \le\ 5\ \times\ 10^5 $
- $ 1\ \le\ S_{i,j}\ \le\ M(1\ \le\ i\ \le\ N,1\ \le\ j\ \le\ A_i) $
- $ S_{i,j}\ \neq\ S_{i,k}(1\ \le\ j\ <\ k\ \le\ A_i) $
- 入力は全て整数である。
 
### Sample Explanation 1

まず、$ \lbrace\ 1,2\ \rbrace $ と $ \lbrace\ 2,3\ \rbrace $ を選んで消し、$ \lbrace\ 1,2,3\ \rbrace $ を追加します。 そして、$ \lbrace\ 1,2,3\ \rbrace $ と $ \lbrace\ 3,4,5\ \rbrace $ を選んで消し、$ \lbrace\ 1,2,3,4,5\ \rbrace $ を追加します。 すると $ 2 $ 回の操作で $ 1 $ と $ M $ を両方含む集合を作ることが出来ます。$ 1 $ 回の操作では目標を達成できないため、答えは $ 2 $ です。

### Sample Explanation 2

始めから $ S_1 $ が $ 1,M $ を共に含むため、必要な操作回数の最小値は $ 0 $ 回です。

## 样例 #1

### 输入

```
3 5
2
1 2
2
2 3
3
3 4 5```

### 输出

```
2```

## 样例 #2

### 输入

```
1 2
2
1 2```

### 输出

```
0```

## 样例 #3

### 输入

```
3 5
2
1 3
2
2 4
3
2 4 5```

### 输出

```
-1```

## 样例 #4

### 输入

```
4 8
3
1 3 5
2
1 2
3
2 4 7
4
4 6 7 8```

### 输出

```
2```

# 题解

## 作者：2huk (赞：11)

## 题目描述

有 $N$ 个集合 $S_1,S_2,\dots,S_N$，其中 $\left| S_i \right| = A_i,\ S_{i, j} \in [1, M]$。

每次选择两个满足 $\left| S_i \cap S_j \right| \ge 1$ 的集合 $S_i,S_j$，将它们删掉并加上一个新集合 $S_i \cup S_j$。

问最少多少次操作使得存在一个集合 $S_i$ 满足 $1,M \in S_i$。

- $ 1\ \le\ N\ \le\ 2\ \times\ 10^5 $
- $ 2\ \le\ M\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ \sum\limits_{i=1}^{N}\ A_i\ \le\ 5\ \times\ 10^5 $
- $ 1\ \le\ S_{i,j}\ \le\ M(1\ \le\ i\ \le\ N,1\ \le\ j\ \le\ A_i) $
- $ S_{i,j}\ \neq\ S_{i,k}(1\ \le\ j\ <\ k\ \le\ A_i) $

## 分析

这道题可以抽象成图论最短路问题。

考虑这样建图：对于每两个集合 $S_i$ 和 $S_j$，如果有一个元素 $k$ 满足 $k \in S_i,k \in S_j$，那么就建一条 $S_i \longleftrightarrow S_j$ 的无向边，表示可以将 $S_i$ 和 $S_j$ 集合合并。

那么显然答案就是某一个包含 $1$ 的集合到某一个包含 $M$ 的集合的最短路。

这样的想法是不错的。但是建图时的时间复杂度是 $\Theta(N^2)$，而这个复杂度是无法接受的。

观察数据范围 $ 1\ \le\ \sum\limits_{i=1}^{N}\ A_i\ \le\ 5\ \times\ 10^5 $，所以我们考虑把集合和点进行联系。

对于一个集合 $S_i$，把这个集合和所有其中的元素连接无向边，形成一个[二分图](https://oi-wiki.org/graph/bi-graph/)，那么跑最短路时只需要从 $1$ 点跑到 $M$ 点即可。

为了方便区分，我们把集合重新编号，即将 $S_i$ 编号为 $i + M$。所以样例数据建出来的图就应该是这个样子：

![](https://s1.ax1x.com/2023/05/24/p972FMT.png)

其中左边是集合中的元素，右边是集合编号。

这时跑最短路就会多了一些本来不存在的边。首先多了一条起点（也就是 $1$ 点）连向某一个集合的边，也多了一条终点（也就是 $M$ 点）连向集合的边。其次对于原来的每条边现在都多了一条从元素指向集合的边，所以最终答案应该为 $\dfrac{res - 2}2$（$res$ 为从 $1$ 点到 $M$ 点的最短路）。

这样问题就解决了。求最短路可以直接 `BFS`。

[$\text{Code}$](https://atcoder.jp/contests/abc302/submissions/41667586)

---

## 作者：Svemit (赞：8)

[cnblogs](https://www.cnblogs.com/Svemit/p/17418264.html)

[传送门](https://atcoder.jp/contests/abc302/tasks/abc302_f)

[Luogu传送门](https://www.luogu.com.cn/problem/AT_abc302_f)

算是比较简单的 F

### $Solution$：

建 $m$ 个元素的点和 $n$ 个集合的点，每个集合向该集合内的元素连一条边权为 $0$ 的边，元素向集合连一条边权为 $1$ 的边，然后跑 $1 \sim m$ 的最短路。注意到得到的答案是合并 $1$ 和 $m$ 的最少的集合数量，所以答案要减一，可以跑 01bfs，我赛时直接贺 dijkstra 的板子了。

code
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
const int N = 5e5 + 5, M = N, INF = 0x3f3f3f3f;
const LL mod = 1e9 + 7;
int n, m;
int h[N], nxt[M << 1], to[M << 1], val[M << 1], cnt;
int dist[N];
bool st[N];
void add(int u, int v, int w)
{
	to[++ cnt] = v, val[cnt] = w, nxt[cnt] = h[u], h[u] = cnt;
}
void dijkstra(int s)
{
	for(int i = 1;i <= n + m;i ++) dist[i] = INF, st[i] = false;
	priority_queue<PII, vector<PII>, greater<PII> > q;
	dist[s] = 0;
	q.push({0, s});
	while(q.size())
	{
		int u = q.top().second;
		q.pop();
		if(st[u]) continue;
		st[u] = true;
		for(int i = h[u];i;i = nxt[i])
		{
			int v = to[i], w = val[i];
			if(dist[v] > dist[u] + w)
			{
				dist[v] = dist[u] + w;
				q.push({dist[v], v});
			}
		}
	}
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	cin >> n >> m;
	for(int i = 1; i <= n; i ++)
	{
		int len;
		cin >> len;
		while(len --)
		{
			int x;
			cin >> x;
			add(i, n + x, 0);
			add(n + x, i, 1);
		}
	}
	dijkstra(n + 1);
	if(dist[n + m] == INF) dist[n + m] = 0;
	cout << dist[n + m] - 1 << '\n';
    return 0;
}
```
[Submission #41592583](https://atcoder.jp/contests/abc302/submissions/41592583)


---

## 作者：shellyang2023 (赞：5)

## 题意简述：

简单来说本题就是给定几个集合，让我们求**几次合并操作**可以让 $1$ 和 $M$ 在一个集合内。

## 正文：

我们可以**把元素看作点**，两两连边，答案即 
$1$ **到** $m$ **的最短路长度** $−1$。

时间复杂度 $O(∑s_i^2)$，期望得分 $70$ 分。

我们可以对上述方法加以优化，**建立一个虚点** $m+k$ ，答案则是 $1$ **到** $m$ **的最短路长度除以** $2$ **再** $-1$。

至于最短路用 dijkstra 就可以了

时间复杂度 $O(∑s_i)$，可以通过。

见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
struct Node {
	int y,val;
	bool operator < (const Node A) const {
		return val>A.val;
	}
}node;
int arr[N],brr[N];
int t,n,m,len,h,f,ans;
int dis[N],vis[N];
vector <Node> vec[N];
priority_queue <Node> q;
void dijkstra (int s,int t) {//最短路  
	memset(dis,127,sizeof(dis));
	memset(vis,0,sizeof(vis));
	node.y=1;node.val=0;
	q.push(node);
	dis[1]=0;
	while(!q.empty()) {
		node=q.top();
		q.pop();
		int x=node.y;
		if(vis[x]==1) {
			continue;
		}
		vis[x]=1;
		for(int i=0;i<vec[x].size();i++) {
			int y=vec[x][i].y;
			int v=vec[x][i].val;
			if(dis[y]>dis[x]+v) {
				dis[y]=dis[x]+v;
				node.y=y;node.val=dis[x]+v;
				q.push(node);
			}
		}
	}
}
int main () {
//	freopen("memory.in","r",stdin);
//	freopen("memory.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m+n;i++) {//清0  
		vec[i].clear();
	}
	for(int k=1;k<=n;k++) {
		cin>>len;
		for(int i=1;i<=len;i++) {//虚点建边  
			cin>>arr[i];
			node.val=1;node.y=m+k;
			vec[arr[i]].push_back(node);
			node.val=0;node.y=arr[i];
			vec[m+k].push_back(node);
		}
	}	
	dijkstra(1,m);
	ans=dis[m];
	if(ans>1e9) {//特判  
		cout<<-1<<endl;
		return 0;
	}
	cout<<ans-1<<endl;//要-1  
	return 0;
}
```

---

## 作者：Leaper_lyc (赞：5)

很好的图论建模题。

如果两个集合可以合并，我们就在这两个集合间连一条边权为 $1$ 的无向边，那么合并两个集合 $S_i,S_j$ 就相当于走了 $i\to j$ 这条边，代价为 $1$。

于是有了一种做法：对于每个 $x\in[1,m]$，让所有包含了元素 $x$ 的集合两两连边，然后跑最短路。

但是两两连边的复杂度是 $O(n^2)$ 的，不能通过此题。

考虑如何优化建边。

用 $\frac{n\times (n - 1)}{2}$ 条边来联通这些集合太浪费了，可以用菊花结构来联通它们：用元素 $x$ 作为菊花的中心，对于每个 $x\in S_i$ 的 $i$，连边 $i\to x$，边权为 $1$，连边 $x\to i$，边权为 $0$。

或者边 $i\to x$ 的边权为 $0$，边 $x\to i$ 的边权为 $1$ 也行。

为什么这样连边？

思考从 $i$ 走到 $j$ 的过程：走了 $i\to x,x\to j$ 这两条边，其中 $i\to x$ 的代价为 $1$，$x \to j$ 的代价为 $0$，就是把原来的边 $i\to j$ 转换为两条边，边权和要保证不变。

注意跑出来的 $dis$ 数组表示的是经过了多少个集合，而要求的是合并次数，所以答案要减一。

由于边权只有 $0$ 和 $1$，可以用 01bfs 解决，跑得会更快一点。

但本人用的是 dijkstra。

代码：
```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;
const int N = 2e5 + 10;
int n, m;
int dis[N << 1];
vector < pair <int, int> > g[N << 1];
inline int rd() {
    int x = 0; char ch = getchar();
    for (; ch < 48 || ch > 57; ch = getchar());
    for (; ch > 47 && ch < 58; ch = getchar())
        x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
priority_queue < pair <int, int> > q;
void dij(int s) {
    while (!q.empty()) q.pop();
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0; q.push(make_pair(0, s));
    while (!q.empty()) {
        int u = q.top().second; q.pop();
        for (int i = 0, v, w; i < (int)g[u].size(); i++) {
            v = g[u][i].first, w = g[u][i].second;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                q.push(make_pair(-dis[v], v));
            }
        }
    }
}
signed main() {
    n = rd(), m = rd();
    for (int i = 1, t, x; i <= n; i++) {
        t = rd();
        for (int j = 1; j <= t; j++) {
            x = rd();
            g[i].push_back(make_pair(x + n, 1));
            g[x + n].push_back(make_pair(i, 0));
        }
    }
    dij(n + 1);
    if (dis[n + m] == dis[0]) puts("-1");
    else printf("%d", dis[n + m] - 1);
}
```

---

## 作者：小胖同学 (赞：3)

# [ABC302F] Merge Set 题解

## 题意：

给定 $N$ 个串 $S$，第 $i$ 个串长度为  $A_i$，$S_{i,j} \in (1 \dots M)$

规定当两个串 $S_i \cap S_j \neq \varnothing$ 则可以将两串合并。

求出最小的合并次数，使得有一个串同时包含 $1$ **和** $M$。

无解输出 $-1$。

原题面：[[Link]](https://atcoder.jp/contests/abc302/tasks/abc302_f)

## 题解

我认为这道题最大的难点在于读题，要求是有一个串同时包含 $1$ **和** $M$，**而不是** 同时包含 $1$ **到** $M$。

首先看到两个串合并的条件是有交集，可以想到根据两个串是否有交进行建图。直接枚举两个串时间复杂度显然是不对的，所以考虑用下面的方法建图。

![](https://cdn.luogu.com.cn/upload/image_hosting/4jeq0dwo.png)

样例 1 举例。如图，我们将每个串向它的每一个数字连一条长度为 $1$ 的边。这样建图后会发现，每个串会贡献两次长度，$n$ 个串需要合并 $n - 1$ 次，所以假设 $1$ 到 $M$ 的最短距离为 $len$ 最终的答案为 $\frac {len} 2 - 1$。由于边长都为 $1$ 直接拓扑即可，时间复杂度为 $O(N + \sum_{i=1}^N A_i)$。

## 代码

传送门：[[Link](https://www.luogu.com.cn/paste/084i7cyq)]



---

## 作者：Augen_stern (赞：2)

## Part 1: 分析求解 

套路建图题，读完题不难可以构造出一个二分图，左边是每个集合，称为集合点，右边是 $1-m$，称为数字点；

而题目要求的是一个集合**包含** $1$ **和** $m$ 的最少操作步数。

一次操作中使用的两个集合相当于从第一个集合点到其中的一个数字点再到第二个集合点，代价为 $1$，而我们拥有的集合可以走向任意在集合中的数字点且代价为 $0$。

所以我们只需要将每一个集合点连向相匹配的数字点，代价为 $0$，将每一个数字点连向相匹配的集合点，代价为 $1$，跑跑最短路就好了。

## Part 2: CODE

```cpp
//#pragma GCC optimize(3)
#include<iostream>
#include<climits>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<ctime>
#include<assert.h>
#include<algorithm>
#include<queue>
#include<map>
#include<set>
#include<vector>
//#include<random>
//#include<chrono>
#define int long long
//#define double long double
using namespace std;
const long long INF=LLONG_MAX/2ll;
const long long mod=998244353;
//const long long mod=1000000007;
const double Pai=acos(-1);
const double eps=1e-8;
int n,m,cnt=0;
int dis[1000005],h[1000005],vst[1000005];
struct edge {
	int to,next,v;
}e[1000005];
void addedge(int x,int y,int z) {
	cnt++;
	e[cnt].to=y;
	e[cnt].v=z;
	e[cnt].next=h[x];
	h[x]=cnt;
}
priority_queue< pair<int,int> > q;
void Dij(int s) {
	for(int i=1;i<=n+m;i++) dis[i]=INF,vst[i]=0;
	dis[s]=0,q.push({-dis[s],s});
	while(!q.empty()) {
		int u=q.top().second;q.pop();
		if(vst[u]) continue;
		vst[u]=1;
		for(int i=h[u];i;i=e[i].next) {
			int y=e[i].to;
			if(dis[y]>dis[u]+e[i].v) {
				dis[y]=dis[u]+e[i].v;
				q.push({-dis[y],y});
			}
		}
	}
}
signed main() {
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++) {
		int x;scanf("%lld",&x);
		for(int j=1;j<=x;j++) {
			int y;scanf("%lld",&y);
			addedge(i+m,y,0),addedge(y,i+m,1);
		}
	}
	Dij(1);
	if(dis[m]==INF) puts("-1");
	else printf("%lld",dis[m]-1);
	return 0;
}
```


---

## 作者：_zzzzzzy_ (赞：1)

# 思路
套路建图题，我们可以对于每一个集合的每一个点之间两两建边边权为 `1`，表示可以通过 `1` 的代价从一个集合跳到另一个集合，最后跑一边最短路就行了。

但这样我们是要建 $O(N^2)$ 条边，我们考虑怎么样优化建图，我们可以对于每一个集合建一个新的虚拟点我们把集合的元素连一条边到虚拟点边权是 `1`，从虚拟点连边到集合中的点边权是 `0`，这样我们同样也能实现刚刚的建图。

最后跑一边最短路，因为边权只有 `0` 和 `1`，那么就可以 $O(N)$ 的求最短路。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int maxn = 1000000;
int d[maxn];
vector<pair<int, bool>> e[maxn];
bool vis[maxn];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		int q;
		cin >> q;
		for (int j = 1; j <= q; j++) {
			int x;
			cin >> x;
			e[x].push_back({m + i, 1});
			e[m + i].push_back({x, 0});
		}
	}
	deque<int>Q;
	memset(d, 0x3f, sizeof d);
	Q.push_back(1);
	d[1] = 0;
	while (Q.size()) {
		int u = Q.front();
		Q.pop_front();
		if (vis[u]) {
			continue;
		}
		vis[u] = 1;
		for (auto [v, w] : e[u]) {
			if (d[v] > d[u] + w) {
				d[v] = d[u] + w;
				if (w == 0) {
					Q.push_front(v);
				}
				else {
					Q.push_back(v);
				}
			}
		}
	}
	if (d[m] == 0x3f3f3f3f) {
		d[m] = 0;
	}
	cout << d[m] - 1;
	return 0;
}
```

---

## 作者：happybob (赞：1)

非常套路的建图最短路。

首先有一个非常好思考的做法，对于 $i,j$，如果 $i$ 的集合和 $j$ 的集合有交集，那么连 $i \leftrightarrow j$ 的边。

但这样建图复杂度已经达到了 $O(n^2)$ 以上，无法承受。

于是我们考虑转化。两个集合有交集，相当于有至少一个相同元素。

对于 $i$，我们连所有的 $i \leftrightarrow a_{i,j}$。这样原本的一对 $(i,j)$ 如果有交集，就可以转化为 $i \rightarrow x \rightarrow j$。于是就可以最短路做了。

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <stack>
#include <vector>
#include <utility>
#include <cstdlib>
#include <string>
using namespace std;

#define ll long long

const int N = 2e5 + 5, INF = 2e9, MOD = 1e9 + 7;
vector<int> c[N];

inline int read()
{
	int op = 1, x = 0;
	char ch = getchar();
	while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
	while (ch == '-')
	{
		op = -op;
		ch = getchar();
	}
	while (ch >= '0' and ch <= '9')
	{
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * op;
}

inline void write(int x)
{
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

int n, m, t;
vector<int> G[5 * N];
int dis[N * 5];

int bfs(int u, int v)
{
	queue<int> q;
	q.push(u);
	memset(dis, 0x3f, sizeof dis);
	dis[u] = 0;
	while (q.size())
	{
		int u = q.front();
		q.pop();
		for (int j : G[u])
		{
			if (dis[j] == dis[5 * N - 1])
			{
				dis[j] = dis[u] + 1;
				q.push(j);
			}
	}
	}
	return dis[v];
}

vector<int> v;

int main()
{
	// freopen("*.in", "r", stdin);
	// freopen("*.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		for (int j = 1; j <= x; j++)
		{
			int k;
			scanf("%d", &k);
			if (k == 1)
			{
				v.emplace_back(i);
			}
			c[i].emplace_back(k);
			G[i].emplace_back(k + n);
			G[k + n].emplace_back(i);
		}
	}
	for (int i : v)
	{
		G[0].emplace_back(i);
		G[i].emplace_back(0);
	}
	int x = bfs(0, m + n);
	if (x == dis[5 * N - 1]) printf("-1\n");
	else printf("%d\n", x / 2 - 1);
	return 0;
}
```


---

## 作者：sherry_lover (赞：0)

# AT_abc302_f [ABC302F] Merge Set 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_abc302_f)

## 思路

合并的过程容易想到最短路，考虑怎么建图。

### 把集合视为点

对于两个集合 $x,y$，枚举元素 $z$，若 $x,y$ 都含有 $z$，则在 $x,y$ 之间连边。答案即一个含有 $1$ 的集合与一个含有 $n$ 的集合之间的最短路长度最小值。

由于边权都是 $1$，用 BFS 更快。

时间复杂度 $O(n^2m)$，用 bitset 优化后 $O(\frac{n^2m}{\omega})$，不能通过本题。

### 把元素视为点

对于一个集合内的任意两个元素 $x,y$，在它们之间连边。答案即 $1$ 到 $m$ 的最短路长度 $−1$。

时间复杂度 $O(\sum s^2_i)$。

如何优化？

注意到两两连边浪费。对每个集合建立虚点，把所有集合内元素连向它。答案即 $1$ 到 $m$ 的最短路长度除以 $2$ 再减 $1$。证明楼下大佬讲的很详细了。

时间复杂度 $O(\sum s_i)$，可以通过本题。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m;
vector<int> g[400005];
bool vis[400005];
int bfs()
{
    queue<pair<int,int> > q;
    q.push({1,0});
    vis[1] = 1;
    while(!q.empty())
    {
        auto u = q.front();
        q.pop();
        if(u.first == m) return u.second;
        for(auto i:g[u.first])
        {
            if(!vis[i])
            {
                vis[i] = 1;
                q.push({i,u.second+1});
            }
        }
    }
    return -1;
}
int main()
{
    cin >> n >> m;
    for(int i = 1;i <= n+m;i++)
    {
        g[i].clear();
        vis[i] = 0;
    }
    for(int i = 1,s;i <= n;i++)
    {
        cin >> s;
        for(int j = 1,x;j <= s;j++)
        {
            cin >> x;
            g[m+i].push_back(x);
            g[x].push_back(m+i);
        }
    }
    cout << bfs()/2-1 << endl;
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 题意

有 $ N $ 个集合 $ S_1, S_2, \cdots, S_N $，每个集合中的每个数都在 $ 1 \sim M $ 范围内。

定义一次操作为：

>  选择两个包含相同元素的集合，合并它们。

问至少要多少次操作才能让某一个集合内同时有 $ 1 $ 和 $ M $。

## 思路

构造一个包含 $ N + M $ 个点的二分图。其中左边有 $ N $ 个点表示集合，右边有 $ M $ 个点表示集合内的数字。

如果一个集合 $ S_i $ 包含数字 $ j $，那就从左边的第 $ i $ 个点连到右边的第 $ j $ 个点。

以样例 1 为例：

![](https://cdn.luogu.com.cn/upload/image_hosting/e5jrbu0n.png)

然后我们从右边的 $ 1 $ 号点跑 BFS 处理与右边的 $ M $ 号点的距离，路上经过的集合即为要合并的集合。

设从右边 $ 1 $ 号点到右边 $ M $ 号点的长度为 $ D $，则实际答案为 $ \frac{D}{2} - 1 $。

## Code

```cpp
// Problem: F - Merge Set
// Contest: AtCoder - TOYOTA MOTOR CORPORATION Programming Contest 2023#2 (AtCoder Beginner Contest 302)
// URL: https://atcoder.jp/contests/abc302/tasks/abc302_f
// Memory Limit: 1024 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;

#define Set 0
#define Num 200003
// 蒟蒻喜欢用 Set + i 表示左边的 i 号点，用 Num + i 表示右边的 i 号点

vector<int> graph[400005];
int dis[400005];

int bfs(int m) {
	memset(dis, -1, sizeof dis);
	queue<int> que;
	que.push(Num + 1); // 从右边的 1 号点开始
	dis[Num + 1] = 0;
	while (que.size()) { // BFS
		int u = que.front();
		que.pop();
		for (int v : graph[u]) {
			if (dis[v] == -1) {
				dis[v] = dis[u] + 1;
				que.push(v);
			}
		}
	}
	if (dis[Num + m] == -1) { // 无解需特判
		return -1;
	}
	return dis[Num + m] / 2 - 1; // 实际答案为 D/2 - 1
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		int len;
		scanf("%d", &len);
		for (int j = 0; j < len; j++) {
			int x;
			scanf("%d", &x);
			graph[Set + i].push_back(Num + x);
			graph[Num + x].push_back(Set + i);
		}
	}
	printf("%d", bfs(m));
	return 0;
}
```



---

## 作者：wangzikang (赞：0)

这个题感觉可以放到 E，F 感觉有点水。

我们先把每个数变成一个点，编号是 $1,2,3, \dots ,n-1,n$。

然后我们将每个集合变成一个点，编号是 $n+1,n+2,n+3, \dots ,n+m-1,n+m$。

这样，我们再将每个集合与每个集合中的数连边，使集合 to 数的边权为 1，数 to 集合的边权为 0，反过来也一样，不影响答案。

显然，我们在这个图上跑最短路，最短路减一就是答案。

Why 减一?

因为这个图的最短路实际上是求的合并了几个集合，所以要减一。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >q;
int n,m,num,s;
int he[1000010],d[1000010],inq[1000010];
struct node{
    int nxt;
    int to;
    int dis;
}edg[2000200];
void add(int a,int b,int c){
    edg[++num].to=b;
    edg[num].dis=c;
    edg[num].nxt=he[a];
    he[a]=num;
}
void dst(int s){
    memset(d,0x3f,sizeof(d));
    memset(inq,0,sizeof(inq));
    q.push(make_pair(0,s));
    d[s]=0;
    while(!q.empty()){
        int x=q.top().second;
        q.pop();
        if(inq[x])continue;
        inq[x]=1;
        int t=he[x];
        while(t){
            if(d[edg[t].to]>d[x]+edg[t].dis&&!inq[edg[t].to])
            {
                d[edg[t].to]=d[x]+edg[t].dis;
                q.push(make_pair(d[edg[t].to],edg[t].to));
            }
            t=edg[t].nxt;
        }
    }    
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		int dpp;
		cin>>dpp;
		while(dpp--){
			int v;
			cin>>v;
			add(i,v+n,0);
			add(v+n,i,1);
		}
	}
	dst(1+n);
	cout<<(d[n+m]==0x3f3f3f3f?-1:d[n+m]-1);
	return 0;
}
```


---

## 作者：Kylin_ZHH (赞：0)

# ABC302F题解

~~这个题赛时没打出来~~，~~太蒟了~~

集合与集合之间，根据交集不为空的关系，有连边。但由于 $n$ 有 $10^5$ 的大小，因此不能 $O(n^2)$ 建边。

但由于所有集合的所有数加起来只有 $10^5+5$，如果一个集合 $i$ 有数字 $j$，我们可以连一条从 $i$ 到 $j$ 的边，让数字 $j$ 充当集合与集合之间的中介。这样边数只有 $10^5+5$ 条。

即有两类点，一类是表示集合的点，一类是表示数字的点，集合 $to$ 数字的边权为 $0$，数字 $to$ 集合的边权为 $1$。

答案就是从 $1$ 号点到 $m$ 号点的最短路距离减一。

因为边权只有 $0$ 和 $1$，且在搜索时边权是交替出现的，所以直接BFS即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
using LL=long long;
const int inf = 1e9 + 7;
int main(){
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<array<int, 2>>> edge(n + m);
    for(int i = 0; i < n; ++ i){
        int x;
        cin >> x;
        while(x--){
            int v;
            cin>>v;
            --v;
            edge[v].push_back({m + i, 1});
            edge[m + i].push_back({v, 0});
        }
    }
    vector<int> dis(n + m, inf);
    dis[0] = 0;
    queue<array<int, 2>> team;
    team.push({dis[0], 0});
    while(!team.empty()){
        auto [expect, u] = team.front();
        team.pop();
        for(auto &[v, w] : edge[u]){
            if (dis[u] + w < dis[v]){
                dis[v] = dis[u] + w;
                team.push({dis[v], v});
            }
        }
    }
    if (dis[m - 1] == inf)
        dis[m - 1] = 0;
    cout << dis[m - 1] - 1 << 'n';
	  return 0;
}

```


---

## 作者：Genius_Star (赞：0)

### 题意：

给定 $N$ 个集合 $S_1, S_2, \dots, S_N$，每个集合大小为 $A_i$，元素均来自于 $[1, M]$。

每次可以选择两个满足 $\left| S_i \cap S_j \right| \ge 1$ 的集合 $S_i, S_j$，将它们删掉并加上一个新集合 $S_i \cup S_j$。

求最少多少次操作，能够使得存在一个集合 $S_i$ 满足 $1, M$ 均在 $S_i$ 中。

### 思路：

一开始所有的集合都是不连通的，因此我们可以将每个集合都看作一个点，每次操作会将两个点连接在一起。

我们的目标是求出什么时候会出现 $1, M$ 在同一个连通块中。

假设我们已经得到了一个连通块，我们考虑往其中加入一个新的集合 $S$，它的大小为 $A$，其中有 $k$ 个元素与这个连通块中的某个点相同，那么我们只需要计算加入这个集合的代价即可：假设这个连通块中有 $n$ 个点，那么我们需要删去两个点，同时再加入一个点，因此代价为 $(n - 2) + (A - k) + 1 = n + A - k - 1$。

于是我们可以将所有的点看作图中的节点，然后对于每一对节点之间，如果它们对应的集合有至少一个元素相同，那么就在它们之间连一条边，边权为它们之间合并的代价。

最后我们只需要求出从 $1$ 号节点到 $M$ 号节点的最短路即可。

### 复杂度分析：

对于每一对节点间的连边，我们只需要检查一下它们对应的集合是否有至少一个元素相同即可，因此时间复杂度是 $O((\sum_{i=1}^{N} A_i)^2)$，可以通过本题。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAXN=4e5+10,MAXE=1e6+10;
ll val[MAXE],nex[MAXE],head[MAXN],vis[MAXN],cnt,n,m;
struct Node{
	ll id,step;
};
void add_edge(ll u,ll v){
	val[++cnt]=v,nex[cnt]=head[u],head[u]=cnt;
}
ll bfs(){
	queue<Node> q;
	q.push({1,0});
	vis[1]=1;
	while(!q.empty()){
		Node t=q.front();
		q.pop();
		if(t.id==m){
			return t.step;
		}
		for(ll i=head[t.id];i;i=nex[i]){
			if(vis[val[i]]==0){
				vis[val[i]]=1;
				q.push({val[i],t.step+1});
			}
		}
	}
	return 0;
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	scanf("%lld%lld",&n,&m);
	for(ll i=1;i<=n;i++){
		ll a;
		scanf("%lld",&a);
		for(ll j=1;j<=a;j++){
			ll x;
			scanf("%lld",&x);
			add_edge(x,i+m);
			add_edge(i+m,x);
		}
	}
	printf("%lld",bfs()/2-1);
	return 0;
}
```
祝愿大家 ABC 集体 AK 啦~

---

