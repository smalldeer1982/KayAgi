# Cow and Fields

## 题目描述

### 题意简述

给定一个有 $n$ 个节点 $m$ 条边的无向图，一个顶点集$S$。

你需要选择两个顶点 $u,v(u\ne v,u\in S,v\in S)$ 并连接这两个顶点（允许 $u,v$ 之间已经有连边），求连接后从顶点 $1$ 到顶点 $n$ 最短路的最大值。

**注意，该操作仅能进行一次。**

保证给定的图联通。

## 样例 #1

### 输入

```
5 5 3
1 3 5
1 2
2 3
3 4
3 5
2 4```

### 输出

```
3```

## 样例 #2

### 输入

```
5 4 2
2 4
1 2
2 3
3 4
4 5```

### 输出

```
3```

# 题解

## 作者：DeaphetS (赞：35)

这里将介绍一个其它题解里没有提到的奇怪的二分做法，请各位看官们笑纳。

Binary search is **USEFUL**!

题意：给定一个 $n$ 个点 $m$ 条边的简单无向连通图，并指定 $k$ 个特殊点。要求在特殊点之间加一条边使得从 $1$ 到 $n$ 的最短路最大，输出这个最大值。

一般这种题有一个通用的套路就是以起点和终点为源点各跑一次单源最短路，在这题里我们直接 $\texttt{BFS}$ 即可。这样我们就能对每个点 $i$ 求出其到点 $1$ 的距离 $dis(1,i)$ 与到点 $n$ 的距离 $dis(n,i)$。接着我们就需要考虑加入一条边 $(s,t)$ 产生的贡献，其为 `min(dis[1][s]+dis[t][n],dis[1][t]+dis[s][n])+1`。我们的目的就是最大化这个贡献，这样就能让结果的最短路尽可能大。这里我们采用一个 **useful** 的算法，也就是**二分**来解决这个问题。

二分贡献的值 $w$，那么我们要做的就是判断是否存在 $s,t$ 使得 `min(dis[1][s]+dis[t][n],dis[1][t]+dis[s][n])+1>=w` 成立，那么就是要让括号内的两项同时大于等于 $w-1$。我们进行移项，会得到我们要判断的式子实际上就是：

$$\begin{cases} dis(t,n)\ge w-dis(s,1)-1\\ dis(t,1)\ge w-dis(s,n)-1\\ \end{cases} $$

那么我们枚举 $s$，把 $dis(t,n)$ 和 $dis(t,1)$ 看成与 $t$ 有关的两个数组 $a,b$。就变成了每次要判断是否存在 $t$ 使得 `a[t]>=w1 && b[t]>=w2` 成立。

那么采用求解二维偏序同样的技巧，我们在枚举 $s$ 的时候，按照 $dis(s,1)$ 升序的规律枚举，并同样地把 $t$ 按照 $dis(t,n)$ 降序排列。这样就能做到每次询问时，$w_1$ 的值是单调下降的，那么就使用双指针，把满足 $a_t\ge w_1 $ 的 $t$ 对应的 $b_t$ 加进来，之后再判断是否存在 $b_t \ge w_2 $ 即可。使用树状数组维护的话时间复杂度为 $O(n\log ^2n)$，虽然是双 $\log$ 但是跑得飞快。需要注意的是由于不能加一个自环进去，所以需要在枚举到 $s$ 时要暂时把 $b_s$ 的贡献去掉（如果此时 $b_s$ 被加到了树状数组内）。

但注意到，实际上我们最后只需要判断一个存在性，所以只需要在过程中维护 $b_t$ 的最大值和次大值（为了维护去掉 $b_s$ 的情况）即可，时间复杂度 $O(n\log n)$。虽然实践证明加了这个优化后反而跑得更慢了（草。

$O(n\log ^2n)$的代码如下，不要忘了最后要和原本的最短路取 $\min$：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 200020
#define mp make_pair
int n,m,k,dis[N][2];
vector<int>d[N],t,e;
struct BIT
{
	int t[N],cnt;
	int lowbit(int x){return x&(-x);}
	void init(){cnt=0;memset(t,0,sizeof(t));}
	void cg(int x,int c){cnt+=c;while(x<N)t[x]+=c,x+=lowbit(x);}
	int ask(int x){int r=0;while(x)r+=t[x],x-=lowbit(x);return r;}
	int Q(int x){return ask(max(x-1,0))<cnt;}
}T;
bool cmp(int x,int y){return dis[x][0]<dis[y][0];}
bool cmp2(int x,int y){return dis[x][1]>dis[y][1];}
void BFS(int st,int o)
{
	queue<int>q;
	q.push(st);
	while(!q.empty()){
		int x=q.front();q.pop();
		for(auto y:d[x])if(!dis[y][o] && y!=st){
			dis[y][o]=dis[x][o]+1;
			q.push(y);
		}
	}
}
bool check(int w)
{
	int i=0;
	T.init();
	for(auto s:t){
		int w1=w-dis[s][0]-1;
		while(i<k && dis[e[i]][1]>=w1)
			T.cg(dis[e[i]][0]+1,1),i++;
		if(dis[s][1]>=w1)T.cg(dis[s][0]+1,-1);
		if(T.Q(w-dis[s][1]))return true;
		if(dis[s][1]>=w1)T.cg(dis[s][0]+1,1);
	}
	return false;
}
int Useful()
{
	int l=1,r=dis[n][0],mid;
	while(l<r){
		mid=l+r+1>>1;
		if(check(mid))l=mid;
		else r=mid-1;
	}
	return l;
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=k;i++){
		int x;
		scanf("%d",&x);
		t.push_back(x);
		e.push_back(x);
	}
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		d[u].push_back(v);
		d[v].push_back(u);
	}
	BFS(1,0),BFS(n,1);
	sort(t.begin(),t.end(),cmp);
	sort(e.begin(),e.end(),cmp2);
	printf("%d\n",min(dis[1][1],Useful()));
}
```

名言警句：**Stop learning useless algorithms, go and solve some problems, learn how to use binary search.**


---

## 作者：OMG_wc (赞：15)

题意是给一个 $n$ 个点的无向图，其中有 $k$ 个特殊点，你必须在两个特殊点之间添加一条边，使得 $1$ 到 $n$ 的最短路尽可能大。

给出一种和官方题解不一样的方法（dls第一次提交就是这么做的）：

首先用 BFS 以 $1$ 和 $n$ 分别求两次最短路，分别记为 $x_i$ 和 $y_i$，原图的最短距离 $x_n$ 记为 $T$。那么最终答案就是  $\min(T,\max\{x_i+y_j+1\})$，其中 $i,j$ 分别为两个特殊点的下标。

我们对特殊点的编号按照 $x_i$ 升序进行排序，得到两个新的序列：

$x_1,x_2,x_3,\cdots,x_k$  (升序的)

$y_1,y_2,y_3,\cdots,y_k$   



- **结论一：对每个$x_i$，只需考虑其右边的 $y$**

证明：设 $j<i$，那么 $x_i+y_j\ge x_j+y_j \ge T$ ，说明其结果不会影响最终答案。换言之，本来我们要考虑的是 $\min(x_i+y_j,x_j+y_i)$，现在只需考虑 $x_j+y_i$。

~~那么对 $y$ 求个后缀 $\max$ 不就好了？~~

其实没必要，因为还能进一步贪心：

- **结论二：对每个$x_i$，只需考虑相邻点 $y_{i+1}$**

证明：

若存在 $y_{i+1}\ge y_i$，那么 $x_i+y_{i+1}\ge x_i+y_i\ge T$，即这种情况计算相邻的时候，就可以让最大值超过 $T$ 了。

若不存在，则说明 $y_i$ 是降序的，那么 $x_i+y_{i+1}\ge x_i+y_j(j>i+1)$，即最大值只会出现在相邻位置。



综上，最终答案为 $\min(T,\max\{x_i+y_{i+1}+1\})$

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF = 0x3f3f3f3f;
const LL mod = 1e9 + 7;
const int N = 200005;

vector<int> a;
vector<int> G[N];
int d[N], f[N];  //d是从1开始最短路，f是从n开始最短路
int b[N];
bool cmp(int p1, int p2) {
    return d[p1] < d[p2];
}
int main() {
    int n, m, g;
    scanf("%d%d%d", &n, &m, &g);
    while (g--) {
        int x;
        scanf("%d", &x);
        a.push_back(x);
    }
    while (m--) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    queue<int> q;
    memset(d, -1, sizeof d);
    memset(f, -1, sizeof f);
    q.push(1);
    d[1] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto v : G[u]) {
            if (d[v] == -1) {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }
    q.push(n);
    f[n] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto v : G[u]) {
            if (f[v] == -1) {
                f[v] = f[u] + 1;
                q.push(v);
            }
        }
    }
    sort(a.begin(), a.end(), cmp);
    int ans = 0;
    for (int i = 0; i < a.size() - 1; i++) {
        ans = max(ans, d[a[i]] + f[a[i + 1]] + 1);
    }
    ans = min(d[n], ans);
    cout << ans << endl;
    return 0;
}

```




---

## 作者：syksykCCC (赞：8)

我们可以预处理出 $1 \to u$ 的最短路记为 $dis_{1\ u}$，$u \to n$ 的最短路记为 $dis_{2 \ u}$。

这个可以通过正反各 BFS 一遍得到。

接下来介绍两种不同的解法。

## Solution1

对于 $u$，**必须经过它** 的最短路长度显然是 $dis_{1 \ u} + dis_{2\ u}$。

现在，我们在 $u, v$ 之间添加了一条边。

那么，设想 $dis_{1 \ u}$ 的求解过程，它是可以从任何一个和 $u$ 相邻的点转移过来的，这些转移点中显然不包含 $v$。那么现在无非就是多了一种从 $v$ 转移的情况，也就是说，$dis_{1 \ u} \gets \min(dis_{1 \ u}, dis_{1, v} + 1)$。

如果原来 $dis_{1 \ u} \le dis_{1, v} + 1$，那么这个转移就没意义了，所以只考虑有意义的情况。显然，$dis_{2 \ u}$ 是不变的，所以，新的最短路长度就是

$$ dis_{1 \ v} + 1 + dis_{2 \ u} $$

算出缩短的长度：

$\Delta = (dis_{1 \ u} + dis_{2 \ u}) - (dis_{1 \ v} + 1 + dis_{2 \ u})$   
$\quad = dis_{1 \ u} - dis_{1 \ v} - 1$

想要让 $\Delta$ 尽可能小，显然，我们选择的 $v$ 应当是满足 $dis_{1 \ u} - dis_{1 \ v}$ 最小的。而别忘了这里的条件是 $dis_{1 \ v} + 1 \le dis_{1 \ u}$，也就是说，$dis_{1 \ v} < dis_{1 \ u}$。所以按照 $dis_1$ 对 $a$ 排序，边就一定是建在 $a_{i -1}$ 和 $a_i$ 之间的啦！

有人会问，$dis_{1 \ a_i} = dis_{1 \ a_{i -1}}$，不就不满足了吗？

没错，但是答案只和 $dis_1$ 的值有关，和 $a_i$ 无关，即便这里出现了一个无意义的建边，但是 $a_{i-1}$ 和它前面建的边，不就相当于 $a_i$ 和 $a_{i-1}$ 前面建的边吗？

时间复杂度 $\mathcal O(n \log n)$。

```cpp
#include <bits/stdc++.h>
#define rep(i, x, y) for(register int i = x; i < y; i++)
#define REP(i, x, y) for(register int i = x; i <= y; i++)
using namespace std;
const int N = 2e5 + 5;
int n, m, k, ans;
int a[N], dis1[N], dis2[N];
vector<int> G[N];
queue<int> que;
inline bool cmp(int x, int y) { return dis1[x] < dis1[y]; }
int main()
{
	ios::sync_with_stdio(false);
	cin >> n >> m >> k;
	REP(i, 1, k) cin >> a[i];
	REP(i, 1, m)
	{
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	memset(dis1, -1, sizeof dis1);
	dis1[1] = 0;
	que.push(1);
	while(!que.empty())
	{
		int u = que.front();
		que.pop();
		for(int v : G[u]) if(dis1[v] == -1)
		{
			dis1[v] = dis1[u] + 1;
			que.push(v);
		}
	}
	memset(dis2, -1, sizeof dis2);
	dis2[n] = 0;
	que.push(n);
	while(!que.empty())
	{
		int u = que.front();
		que.pop();
		for(int v : G[u]) if(dis2[v] == -1)
		{
			dis2[v] = dis2[u] + 1;
			que.push(v);
		}
	}
	sort(a + 1, a + k + 1, cmp);
	ans = 0;
	rep(i, 1, k) ans = max(ans, min(dis1[n], min(dis1[a[i]] + dis2[a[i + 1]], dis1[a[i + 1]] + dis2[a[i]]) + 1));
	cout << ans << endl;
	return 0;
}
```

## Solution 2

比如我们的边添加在 $u, v$ 之间。

一条 **必须经过** $\left< u, v \right>$ 的 $1 \to n$ 路径长度怎么表示（不经过那么这条边就没意义了）？

$$ \min(dis_{1 \ u} + dis_{2 \ v} + 1, dis_{1 \ v} + dis_{2 \ u} + 1)$$

原来最短路的长度显然是 $dis_{1\ n}$，然后分类讨论一下。

1. 如果 $dis_{1 \ u} + dis_{2 \ v} + 1 \le dis_{1 \ v} + dis_{2 \ u} + 1$

> 这时，新路径的长度为 $dis_{1 \ u} + dis_{2 \ v} + 1$。 

> 路径的缩短长度 $\Delta = dis_{1 \ n} - (dis_{1 \ u} + dis_{2 \ v} + 1)$，我们想要 $\Delta$ 尽可能小。

> $\Delta = dis_{1 \ n} - dis_{1 \ u} - dis_{2 \ v} - 1$   
$\quad = dis_{1 \ n} - 1 - (dis_{1 \ u} + dis_{2 \ v})$

> 显然，$(dis_{1 \ u} + dis_{2 \ v})$ 取到 $\max$ 时，$\Delta$ 最小。

2. 如果 $dis_{1 \ u} + dis_{2 \ v} + 1 \ge dis_{1 \ v} + dis_{2 \ u} + 1$

> 这时，新路径的长度为 $dis_{1 \ v} + dis_{2 \ u} + 1$。 

> 路径的缩短长度 $\Delta = dis_{1 \ n} - (dis_{1 \ v} + dis_{2 \ u} + 1)$，我们想要 $\Delta$ 尽可能小。

> $\Delta = dis_{1 \ n} - dis_{1 \ v} - dis_{2 \ u} - 1$   
$\quad = dis_{1 \ n} - 1 - (dis_{1 \ v} + dis_{2 \ u})$

> 显然，$(dis_{1 \ v} + dis_{2 \ u})$ 取到 $\max$ 时，$\Delta$ 最小。

贪心吗？注意，我们虽然是想要一个东西取到 $\max$，但是这是两种情况，我们满足了一种情况的 $\max$ 时很可能会发现它的条件并不满足这种情况。

所以，排序一遍直接输出的想法告吹了 QwQ。

那么只好在满足条件的范围内取值。

第一种情况的条件移项后其实是什么？$dis_{1\ u} - dis_{2\ u} \le dis_{1\ v} - dis_{2\ v}$。

第二种情况呢？$dis_{1\ u} - dis_{2\ u} > dis_{1\ v} - dis_{2\ v}$。

所以，我们只要把 $a$ 按照 $dis_1 - dis_2$ 升序排序，枚举一个 $a_i$ 作为 $v$，它前面的都是第一种情况，后面的都是第一种情况。所以，维护 **前缀** $dis_1 \max$ 作为 $u$，和 **后缀** $dis_2 \max$ 作为 $u$，都试一下就行了！

时间复杂度也是 $\mathcal O(n \log n)$。

```cpp
#include <bits/stdc++.h>
#define rep(i, x, y) for(register int i = x; i < y; i++)
#define REP(i, x, y) for(register int i = x; i <= y; i++)
#define PER(i, x, y) for(register int i = x; i >= y; i--)
using namespace std;
const int N = 2e5 + 5;
int n, m, k, ans;
int a[N], dis1[N], dis2[N], pre[N], suf[N];
vector<int> G[N];
queue<int> que;
inline bool cmp(int x, int y) 
{
	return dis1[x] - dis2[x] < dis1[y] - dis2[y]; 
}
int main()
{
	ios::sync_with_stdio(false);
	cin >> n >> m >> k;
	REP(i, 1, k) cin >> a[i];
	REP(i, 1, m)
	{
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	memset(dis1, -1, sizeof dis1);
	dis1[1] = 0;
	que.push(1);
	while(!que.empty())
	{
		int u = que.front();
		que.pop();
		for(int v : G[u]) if(dis1[v] == -1)
		{
			dis1[v] = dis1[u] + 1;
			que.push(v);
		}
	}
	memset(dis2, -1, sizeof dis2);
	dis2[n] = 0;
	que.push(n);
	while(!que.empty())
	{
		int u = que.front();
		que.pop();
		for(int v : G[u]) if(dis2[v] == -1)
		{
			dis2[v] = dis2[u] + 1;
			que.push(v);
		}
	}
	sort(a + 1, a + k + 1, cmp);
	REP(i, 1, k) pre[i] = max(pre[i - 1], dis1[a[i]]);
	PER(i, k, 1) suf[i] = max(suf[i + 1], dis2[a[i]]);
	REP(i, 1, k)
	{
		if(i > 1) ans = max(ans, min(dis1[n], dis2[a[i]] + 1 + pre[i - 1]));
		if(i < k) ans = max(ans, min(dis1[n], dis1[a[i]] + 1 + suf[i + 1]));
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：wangyibo201026 (赞：6)

## 题意

给你一个图，再给你一个集合，让你在集合里连一条边，使得最短路最大（边权为 $1$）。

## 思路

我们定义一些前置数组：

定义 $dis_i$ 表示 $1$ 到 $i$ 的最短路径，$dis2_i$ 表示 $i$ 到 $n$ 的最短路径，$d_{i,j}$ 表示 $i$ 到 $j$ 的最短路。

首先，我们知道，如果在集合中连一条边的话，那么 $newdis_n \le olddis_n$，那么这里以连的两个点为 $u, v$ 举例：

![](https://cdn.luogu.com.cn/upload/image_hosting/zw6awx0d.png)

那么此时就可以得出柿子：$dis_u + 1 + dis2_v \le dis_n$。

同理，如果 $dis_u + 1 + dis2_v \le dis_n$ 的话，那么就有 $dis_u + 1 + dis2_v \le dis_v + dis2_v$（道理如上）。

柿子 $dis_u + 1 + dis2_v \le dis_v + dis2_v$ 可以化简成 $dis_u + 1 \le dis_v$。移项后可以得出 $dis_v - dis_u \ge 1$，所以我们发现 $d_{u, v}$ 要尽可能小才行，所以我们可以按照 $dis_i$ 排序，每次的相邻两个 $i$ 和 $i + 1$ 就一定是可能的最小的 $d_{u, v}$。

由于最后的答案可能大于 $dis_n$，所以我们还要跟 $dis_n$ 比较一下。

## 代码

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long    //开 long long

using namespace std;

const int N = 4e5 + 5;

int n, m, k, maxi = 0;
bool vis[N];
int a[N];
int dis[3][N];     //这里是预处理两个 dis 数组

int tot, head[N];

struct Node{
  int to, next;
}edges[N];

void add(int u, int v){
  tot++;
  edges[tot].to = v;
  edges[tot].next = head[u];
  head[u] = tot;
}

void dijkstra(int s, int k){    //dijkstra 模板，其实这里可以用 bfs
  memset(vis, false, sizeof(vis));
  priority_queue<pair<int, int>> q;
	for(int i = 1; i <= n; i++) {
		dis[k][i] = 1e9;
	}
	dis[k][s] = 0;
	q.push(make_pair(dis[k][s], s));
	while(!q.empty()) {
		int x = q.top().second;
		q.pop();
		if(vis[x]) {
			continue;
		}
		vis[x] = true;
		for(int i = head[x]; i; i = edges[i].next) {
			if(1 + dis[k][x] < dis[k][edges[i].to]) {
				dis[k][edges[i].to] = 1 + dis[k][x];
				q.push(make_pair(-dis[k][edges[i].to], edges[i].to));
			}
		}
	}
}

bool cmp(int x, int y){
  return dis[1][x] < dis[1][y];
}

signed main(){
  cin >> n >> m >> k;
  for(int i = 1; i <= k; i++){
    cin >> a[i];
  }
  for(int i = 1; i <= m; i++){
    int u, v;
    cin >> u >> v;
    add(u, v);
    add(v, u);
  }
  dijkstra(1, 1);
  dijkstra(n, 2);
  sort(a + 1, a + 1 + k, cmp);    //按照 dis[i] 排序
  for(int i = 1; i < k; i++){
    maxi = max(maxi, dis[1][a[i]] + dis[2][a[i + 1]] + 1);    //最后计算答案
  }
  maxi = min(maxi, dis[1][n]);    //还要跟 dis[n] 比一比
  cout << maxi << endl;
  return 0;
}
```

---

## 作者：LiveZoom (赞：1)

# 题解 CF1307D 【Cow and Fields】

题目就是让你求连接$S$中的两个点，最短路的最大值。

我们考虑$S$中的任意两点$u,v$，令$dis1_k$为$1\to k$的最短路，$dis2_k$为$k\to n$的最短路。我们看到连接之后$u,v$距离为$1$，则我们要让$dis1_u+dis2_v+1$最大，于是就想到了一个$O(k^2+m\log n)$的算法明显超时。

- ## 优化

我们看到$dis1_u+1+dis2_v\leq dis1_v+dis2_v\leq dis1_n$且，由$dis1_v+dis2_v$已知则可以推出最短路从$dis1_v+dis2_v$减少了$dis1_v-dis1_u-1$，此时我们让$dis1_v-dis1_u$最小则最短路为最大值。

- ## 代码实现

1. 跑两边SPFA找出$dis1$和$dis2$的值。

2. 按$dis1_k$的值从小到大排序。

3. 取最大的最短路输出。

- ## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

static char buf[1 << 20], *p1, *p2;
char getc () {
    if (p1 == p2) {
        p1 = buf;
        p2 = buf + fread(buf, 1, 1 << 20, stdin);
        if (p1 == p2) return EOF;
    }
    return *p1++;
}
template <typename _Tp> void read (_Tp &x) {
    _Tp f = 0;
    int sign = 1;
    char ch = getc();
    while (ch < '0' || ch > '9') {
        if (ch == '-') sign = -1;
        ch = getc();
    }
    while (ch >= '0' && ch <= '9') {
        f = (f << 1) + (f << 3) + (ch ^ 48);
        ch = getc();
    }
    x = f * sign;
}

const int N = 2e5 + 5;

struct node {
	int ind, dis;
	node (int _ind, int _dis) {
		ind = _ind;
		dis = _dis;
	}
};

vector <int> G[N];

int n, m, k;
int a[N], u, v;

int dis1[N], dis2[N];

bool cmp (int a, int b) {/排序
	return dis1[a] < dis1[b];
}

void SPFA1 () {
	memset(dis1, 0x3f, sizeof(dis1));
	dis1[1] = 0;
	queue <node> q;
	q.push(node(1, 0));
	bool vis[N] = {false};
	vis[1] = true;
	while (!q.empty()) {
		node nowfront = q.front();
		q.pop();
		vis[nowfront.ind] = false;
		for (int i = 0; i < G[nowfront.ind].size(); ++i) {
			int nextid = G[nowfront.ind][i];
			if (vis[nextid] == true) continue ;
			if (dis1[nextid] > dis1[nowfront.ind] + 1) {
				dis1[nextid] = dis1[nowfront.ind] + 1;
				vis[nextid] = true;
				q.push(node(nextid, dis1[nextid]));
			} 
		}
	}
}

void SPFA2 () {
	memset(dis2, 0x3f, sizeof(dis1));
	dis2[n] = 0;
	queue <node> q;
	q.push(node(n, 0));
	bool vis[N] = {false};
	vis[n] = true;
	while (!q.empty()) {
		node nowfront = q.front();
		q.pop();
		vis[nowfront.ind] = false;
		for (int i = 0; i < G[nowfront.ind].size(); ++i) {
			int nextid = G[nowfront.ind][i];
			if (vis[nextid] == true) continue ;
			if (dis2[nextid] > dis2[nowfront.ind] + 1) {
				dis2[nextid] = dis2[nowfront.ind] + 1;
				vis[nextid] = true;
				q.push(node(nextid, dis2[nextid]));
			} 
		}
	}
}

int main() {
	read(n), read(m), read(k);
	for (int i = 1; i <= k; ++i) {
		read(a[i]);
	}
	for (int i = 1; i <= m; ++i) {
		read(u), read(v);
		G[u].push_back(v), G[v].push_back(u); 
	}
	SPFA1(), SPFA2();//跑最短路
	sort(a + 1, a + 1 + k, cmp);
	int ans = 0;
	for (int i = 1; i < k; ++i) {
		ans = max(ans, dis1[a[i]] + dis2[a[i + 1]] + 1);//取最大值时的最短路
	}
	ans = min(ans, dis1[n]);//如果答案都大于1->n的距离，则不可能是最短路
	cout << ans << endl; 
	return 0;
}
```

# The end

求通过

---

## 作者：Reanap (赞：1)

这道题考场思路大概想到一半，然后就结束了。。。
~~主要还是死在B题~~

根据正常人的思维，肯定是先跑两遍$BFS$维护一下起点和终点到当前点的距离。

我的考场思路是选两个特殊田地，使得他们分别到起点和终点的距离之和$+1$尽可能地大，但是在实际操作中我却发现，可能存在我们计算的路径并非从起点经过这两个点到终点的最短路径，但是只要把计算到起点距离的换成到终点距离，到终点距离换成到起点距离时，就是符合题意的。

~~于是本次比赛的第四个贪心诞生了~~
将这些点按照里起点的近远顺序排序。有什么好处呢，我发现在这个序列中对于$i$ , $j$ , $i < j$ , $i$到起点的距离+$j$到终点的距离+$1$就是经过这两个点的最短路径。这样就可以非常愉快地计算了。

下面我的代码是用堆来写的（因为我在考场用堆乱搞过，懒得改了）

```cpp
#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 2e5 + 5;
int head[MAXN] , nxt[MAXN << 1] , to[MAXN << 1] , cnt;
void add(int u , int v) {nxt[++cnt] = head[u];head[u] = cnt;to[cnt] = v;}
int n , m , k , a[MAXN] , dp[MAXN][2] , vis[MAXN];
void bfs(int x , int c) {
	queue <int> q;
	q.push(x);
	vis[x] = !c;
	while(!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = head[x]; i; i = nxt[i]) {
			if(vis[to[i]] != c) continue;
			dp[to[i]][c] = dp[x][c] + 1;
			q.push(to[i]); 
			vis[to[i]] = !c;
		}
	}
} 
priority_queue <pair<int , int> , vector <pair<int , int> > , greater<pair<int , int> > > q;
int main() {
	scanf("%d %d %d" , &n , &m , &k);
	for (int i = 1; i <= k; ++i) {
		scanf("%d" , &a[i]);
	}
	for (int i = 1; i <= m; ++i) {
		int u , v;
		scanf("%d %d" , &u , &v);
		add(u , v);
		add(v , u);
	}
	bfs(1 , 0);
	bfs(n , 1);
	for (int i = 1; i <= k; ++i) q.push(make_pair(dp[a[i]][0] , dp[a[i]][1]));
	int ans = 0 , cmax = -1e9; 
	for (int i = 1; i <= k; ++i) {
		ans = max(ans , cmax + q.top().second + 1);
		cmax = max(cmax , q.top().first);
		q.pop();
	}
	printf("%d" , min(ans , dp[n][0]));
	return 0;
}

```

---

## 作者：邮差将军 (赞：1)

- **题目大意：**

给你一个 $n$ 个点的图（每条边长均为 $1$）和 $k$ 个特殊点，要在 $k$ 个特殊点中选择两个点连边，使得 $1,n$ 之间的最短路径长度最长，求这个最长长度。$2\le k \le n\le 10^5$.

- **分析：**

首先求出 $1,n$ 两个点的单源最短路径。这 $k$ 个特殊点中，我们另第 $i$ 个特殊点到 $1$ 的距离为 $x_i$ ，到 $n$ 的距离为 $y_i$ 。设答案是连接 $x_i,x_j$ 两点。则我们要：

$$maximize\left\{\min\left(x_i+y_j,x_j+y_i \right) \right\}$$
不妨设 $x_i+y_j<x_j+y_i$ ，则有 $x_i-x_j<y_i-y_j$ 。因此我们将每个点按照 $x$ 排序，维护第 $i$ 个点到第 $n$ 个点 $y$ 的最大值。假设取了第 $i$ 个点的 $x_i$ ，则 $j$ 点一定在 $i$ 点的后面。我们遍历一遍取哪个 $i$ 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 50;
int n, m, k;
int a[MAXN], ans;

int head[MAXN], tot;
struct Edge
{
    int nex, to, dis;
}eg[MAXN << 1];
void add(int a, int b, int c = 1)
{
    eg[++tot] = {head[a], b, c};
    head[a] = tot;
}

int maxy[MAXN];
struct Node
{
    int dis1, disn;
    bool operator < (const Node &x) const
    {
        return dis1 - disn < x.dis1 - x.disn;
    }
}nd[MAXN];

typedef pair<int, int> pii;
#define mp make_pair
int dis[MAXN], vis[MAXN];
priority_queue<pii, vector<pii>, greater<pii> > pq;
void Dijkstra(int rt) // 略去单源最短路径模版

int dis1[MAXN], disn[MAXN];

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1; i <= k; i++) scanf("%d", &a[i]);
    for(int i = 1, a, b; i <= m; i++)
    {
        scanf("%d%d", &a, &b);
        add(a, b); add(b, a);
    }
    Dijkstra(1); for(int i = 1; i <= n; i++) dis1[i] = dis[i];
    Dijkstra(n); for(int i = 1; i <= n; i++) disn[i] = dis[i];
    
    for(int i = 1; i <= k; i++) nd[i] = (Node){dis1[a[i]], disn[a[i]]};
    sort(nd + 1, nd + k + 1);
    for(int i = k; i; i--) maxy[i] = max(maxy[i + 1], nd[i].disn);
    for(int i = 1; i < k; i++) ans = max(ans, nd[i].dis1 + maxy[i + 1] + 1);
    ans = min(ans, dis1[n]); printf("%d\n", ans);
    
    return 0;
}
```

---

