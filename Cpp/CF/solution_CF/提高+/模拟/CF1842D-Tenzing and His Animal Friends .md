# Tenzing and His Animal Friends 

## 题目描述

Tell a story about me and my animal friends.



Tenzing has $ n $ animal friends. He numbers them from $ 1 $ to $ n $ .

One day Tenzing wants to play with his animal friends. To do so, Tenzing will host several games.

In one game, he will choose a set $ S $ which is a subset of $ \{1,2,3,...,n\} $ and choose an integer $ t $ . Then, he will play the game with the animals in $ S $ for $ t $ minutes.

But there are some restrictions:

1. Tenzing loves friend $ 1 $ very much, so $ 1 $ must be an element of $ S $ .
2. Tenzing doesn't like friend $ n $ , so $ n $ must not be an element of $ S $ .
3. There are m additional restrictions. The $ i $ -th special restriction is described by integers $ u_i $ , $ v_i $ and $ y_i $ , suppose $ x $ is the total time that exactly one of $ u_i $ and $ v_i $ is playing with Tenzing. Tenzing must ensure that $ x $ is less or equal to $ y_i $ . Otherwise, there will be unhappiness.

Tenzing wants to know the maximum total time that he can play with his animal friends. Please find out the maximum total time that Tenzing can play with his animal friends and a way to organize the games that achieves this maximum total time, or report that he can play with his animal friends for an infinite amount of time. Also, Tenzing does not want to host so many games, so he will host at most $ n^2 $ games.

## 说明/提示

In the first test case:

1. Tenzing will host a game with friend $ \{1\} $ for $ 1 $ minute.
2. Tenzing will host a game with friends $ \{1,4\} $ for $ 1 $ minute.
3. Tenzing will host a game with friends $ \{1,3\} $ for $ 1 $ minute.
4. Tenzing will host a game with friends $ \{1,2,3,4\} $ for $ 1 $ minute.

If after that, Tenzing host another game with friends $ \{1,2\} $ for $ 1 $ minute. Then the time of exactly one of friends $ 2 $ or $ 3 $ with Tenzing will becomes $ 2 $ minutes which will not satisfy the $ 3 $ -rd special restriction.

In the second test case, there is no special restrictions. So Tenzing can host a game with friend $ \{1\} $ for an infinite amount of time.

## 样例 #1

### 输入

```
5 4
1 3 2
1 4 2
2 3 1
2 5 1```

### 输出

```
4 4
10000 1
10010 1
10100 1
11110 1```

## 样例 #2

### 输入

```
3 0```

### 输出

```
inf```

# 题解

## 作者：不知名用户 (赞：20)

看完给个赞再走呗。

[原题链接](https://www.luogu.com.cn/problem/CF1842D)

#### 题面翻译

Tenzing 有 $n$ 个朋友，每次举办聚会可以邀请一些朋友，有如下限制：

* $1$ 必须参加，$n$ 不能参加。

* 有 $m$ 条限制 $(u, v, w)$，表示 $u$ 和 $v$ 中只有一个在聚会中的总时间不超过 $w$。

### Part 1: 从最短路的性质分析本题为何是最短路

本题将 $(u,v,w)$ 当作一条连接着 $u\leftrightarrow v$，长度为 $w$ 的双向边，$n\to 1$ 的最短路就是答案，为什么？

最短路中的三角不等式，它是 `Bellman-Ford` 作为结束的一个标志。具体内容为：设 $dis_i$ 表示 $1\to i$ 的最短路，若有一条连接着 $u\to v$，长度为 $w$ 的单向边，就有 $dis_u+w\ge dis_v$。否则与最短路的定义矛盾。

再回归本题，如何将聚会时间类比到最短路上？

设 $dis$ 表示每人的参会时长，那么两人 $u$ 和 $v$ 中只有一个在聚会中的总时间不超过 $w$ 是不是代表两人总参会时长（绝对值）之差不超过 $w$，和 $dis_u+w\ge dis_v,dis_v+w\ge dis_u$ 不就是一个意思吗？

因为 $n$ 不能参会，所以 $dis_n=0$；因为 $1$ 每次都要参会，所以 $1$ 的参会时长等于总时长。当然这只说明聚会时长要小于等于 $n\to1$ 的最短路，另一方面（大于等于）以构造证明。

$n\le100$，真的良心，直接 `Floyd` 即可。

```cpp
for(i=1;i<=n;i++)
	for(j=1;j<=n;j++)
		dis[i][j] = (i != j) * 1e15;
while(m--)
{
	int u, v, w;
	cin>>u>>v>>w;
	dis[u][v] = dis[v][u] = min(dis[u][v],w);
}
for(k=1;k<=n;k++)
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			if(dis[i][k]+dis[k][j]<dis[i][j])
				dis[i][j] = dis[i][k] + dis[k][j];
```

### Part 2: 如何构造

感谢 UID=90036 同学的[博文](https://www.luogu.com.cn/blog/buaa-czx/solution-cf1842d)教会了我。

每次取还能聚会的且可聚会时间最少的人与其它可聚会的人都聚会（时间以他的可聚会时间），并从所有人（可聚会）的聚会时间中减去本次聚会时间（其实就是用一个优先队列维护 $dis$），直到 $1$ 不能聚会为止。

```cpp
int *d = dis[n];
if(d[1]==1e15) return cout<<"inf", 0;
priority_queue<int>pq;
for(i=1;i<=n;i++) if(d[i]) pq.push(-d[i]);
int lst = 0;
while(d[1])
{
	int t = -pq.top() - lst;pq.pop();
	lst += t;
	if(!t) continue;
	top++;
	for(i=1;i<=n;i++)
	{
		if(d[i]) opt[top][i] = 1, d[i] -= t;
		else opt[top][i] = 0;
	}
	opt[top][0] = t;
}
```

---

## 作者：Zimo_666 (赞：15)

## [CF1842D] Tenzing and His Animal Friends 

### Description

Tenzing 有 $n$ 个朋友，每次举办聚会可以邀请一些朋友，有如下限制：

* $1$ 必须参加，$n$ 不能参加。

* 有 $m$ 条限制 $(u, v, w)$，表示 $u$ 和 $v$ 中只有一个在聚会中的总时间不超过 $w$。

最大化聚会总时间，并给出相应方案，即给出总聚会时间，每次聚会给出参与聚会的人和单次聚会时长。

### Solution

我们考虑建图做法，首先我们可以把限制 $(u, v, w)$ 建边，而后我们考虑因为 $n$ 不能参加聚会，所以 $u\to n $ 也有相应限制，我们考虑类似从 $n$ 开始扩散的做法，即 $u$ 在 $w$ 时刻前必须从 $n$ 走到 $u$，因而这样向前推可以得任何点必须在他的父节点等待 $w_i$ 时刻前被到达，因而对于整张图考虑即相应总聚会时间最大值为 $1\to n$ 的最短路。考虑将 $n$ 作为起点用迪杰斯特拉算法跑最短路。不合法状态即 $1\to n$ 最短路为极大值。

而后我们考虑构造，对于任何一个点 $i$ 他的状态取决于当前的 $dis_i$ 是否大于 0，大于 0 则状态为 1，反之为 0。我们考虑枚举一个时刻 $T$ 的 $T'=\min ({dis_k},k\in{u})$，则在从当前时刻过渡到这个时刻所有点的 $dis$ 均被去掉 $T$，因而将这个时刻和所有点的状态存进 vector 中维护即可。当 $dis_1$ 为 0 时结束更新答案。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
const int inf=4557430888798830398;
const int N=5e5+7;
vector<pair<int,int> > G[N];
int dis[N<<2];
bool _vis[N<<2];
int n,m,k;
int a[N];
//const int inf=1e9;

struct node{
	int dis,id;
	friend bool operator < (node a,node b){
		return a.dis>b.dis;
	}
};

void Dj(int s){
	memset(_vis,0,sizeof _vis);
	priority_queue<node> q;
	memset(dis,0x3f,sizeof dis);
	dis[s]=0;
  q.push({0,s});
	while(!q.empty()){
		int u=q.top().id;
		q.pop();
		if(_vis[u]) continue;
		_vis[u]=1;
		for(auto i:G[u]){
			int k=i.first,w=i.second;
			if(dis[k]>dis[u]+w){
				dis[k]=dis[u]+w;
				q.push({dis[k],k});
			}
		}
	}
}

struct node2 {
    int sta[110],t;
};

vector<node2> ans;

signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v,w;scanf("%lld%lld%lld",&u,&v,&w);
		G[u].push_back(make_pair(v,w)),G[v].push_back(make_pair(u,w));
	}
	Dj(n);
	if(dis[1]>=inf) return printf("inf"),0;
	printf("%lld ",dis[1]);
  while(dis[1]!=0){
	  int _min=inf;
		for(int i=1;i<=n;i++) if(dis[i]>0&&dis[i]<_min) _min=dis[i];
		node2 a;
		for(int i=1;i<=n;i++) a.sta[i]=dis[i]>0;
		a.t=_min;
		ans.push_back(a);
		for(int i=1;i<=n;i++) dis[i]-=_min;
	}
	printf("%lld\n",ans.size());
	for(auto it:ans){
	  for(int i=1;i<=n;i++){
			printf("%lld",it.sta[i]);
		}
	  printf(" %lld\n",it.t); 
	}
  return 0;
}
```



---

## 作者：buaa_czx (赞：12)

# 题目大意  
Tenzing 有 $n$ 个朋友，编号为 $1$ 至 $n$，每次举办聚会可以邀请其中的一些朋友参加，且朋友 $1$ 必须参加，朋友 $n$ 必须不参加。另有 $m$ 条限制，每条限制包含 $u,v,w$，表示朋友 $u$ 和朋友 $v$ 中只有一个在聚会中的总时间不超过 $w$。  
问聚会总时间的最大值，和相应的聚会方案(聚会的总次数，每次聚会的参加情况和每次聚会的时长)。
# 思路  
先构造出图论模型，注意到朋友 $n$ 每次聚会都不参加，则不难发现 $n$ **的相邻节点 $m$ 的参会总时长必须不超过** $w_{mn}$，由此又可以推出，**对于每个点 $i$，它的参会总时长必须不超过它到点 $n$ 的距离**。又因为点 $1$ 必须每次都参会，因此最大的聚会总时间即为点 $1$ 到点 $n$ 的最短路。显然，如果 $1$ 与 $n$ 不相连，说明最大聚会总时间没有上限。  
下面再考虑如何构造出聚会方案。设存在两个集合 $S,T$，集合 $S$ 中为还能参加聚会的点，集合 $T$ 中为不能再参加聚会的点。最初 $T$ 中仅有 $n$ 一个元素。联系到上述每个点最大参会总时长的得出方式，我们每次从 $S$ 中选择一个参会时间上限最短的点 $x$，让 $S$ 中的所有点都参加一次聚会，时长为 $x$ 的参会时间上限。一直这样进行下去，直到点 $1$ 不在 $S$ 当中。  
不难发现这个思路与 dijkstra 算法存在共通之处，我们进行一次使用 dijkstra 算法求 $n$ 到 $1$ 的最短路即可。
# 代码
```cpp
struct Node {
    int val;
    vector<int> nex, w;
} g[110];
struct Dist {
    int poi, dist;
};
struct Game {
    int par[110], t;
};
bool operator>(const Dist x, const Dist y) { return x.dist > y.dist; }
priority_queue<Dist, vector<Dist>, greater<Dist>> q;
int n, m, fi[110], vis[110], dist[110] = {INF}, t = 0;
vector<Game> ans;
int find(int x) { return x == fi[x] ? x : fi[x] = find(fi[x]); }
void build(int u, int v, int w) {
    g[u].nex.pb(v);
    g[u].w.pb(w);
    fi[find(u)] = find(v);
}
signed main() {
    ios;
    cin >> n >> m;
    rep(i, 1, n) { fi[i] = i; }
    rep(i, 0, m - 1) {
        int u, v, w;
        cin >> u >> v >> w;
        build(u, v, w);
        build(v, u, w);
    }
    if (find(1) != find(n))
        cout << "inf\n";
    else {
        mem(dist, 0x3f3f3f3f);
        int curr = n;
        dist[n] = 0;
        q.push({n, 0});
        while (!q.empty()) {
            curr = q.top().poi;
            q.pop();
            if (vis[curr])
                continue;
            vis[curr] = 1;
            rep(i, 0, (int)g[curr].nex.size() - 1) {
                int v = g[curr].nex[i], cost = g[curr].w[i];
                if (!vis[v] && dist[v] > dist[curr] + cost) {
                    dist[v] = dist[curr] + cost;
                    q.push({v, dist[v]});
                }
            }
        }
        cout << dist[1] << " ";
        while (dist[1] != 0) {
            int minn = INF;
            rep(i, 1, n) {
                if (dist[i] > 0 && dist[i] < minn)
                    minn = dist[i];
            }
            Game a;
            rep(i, 1, n) { a.par[i] = dist[i] > 0; }
            a.t = minn;
            ans.pb(a);
            rep(i, 1, n) { dist[i] -= minn; }
        }
        cout << ans.size() << endl;
        for (auto it : ans) {
            rep(i, 1, n) { cout << it.par[i]; }
            cout << " " << it.t << endl;
        }
    }
    return 0;
}
```

---

## 作者：FFTotoro (赞：6)

很好的一道图论建模题。

看到 $m$ 个约束很容易想到对约束的两个对象建边，然后构造一个无向带权图 $G$ 出来。下面规定 $d_{i,j}$ 为 $G$ 中 $i$ 到 $j$ 的最短路长度。

如果 $G$ 中 $1$ 和 $n$ 之间不连通，那么丁真可以玩无限久：只用让丁真和 $1$ 所在的连通块中的所有动物一起玩，就可以玩无限久。否则 $n$ 的限制条件最终一定会影响到 $1$，导致丁真不能玩无限久。

现在考虑有解时怎么构造解。两种想法，一种是一开始能玩的全部一起玩（即第一次游戏最大化 $01$ 集合中 $1$ 的个数），然后每次会删掉几个不满足条件的，最后一直删到不能再删；还有一种是开始游戏前只有 $1$ 还有 $d_{1,i}=0$ 的 $i$，开始游戏后每次可以添加几个动物玩，直到最后不能再添加。这里着重介绍一下第二种解法。

一开始集合里只有 $1$ 一个动物。接下来对于任意两只相互有约束的动物，为最大限度利用时间，先加入的那只可以把它们两只动物之间约束的时间自己全部消耗完。具体地，假设两只动物分别在时刻 $t_1$ 和 $t_2$ 加入集合，它们之间的时间限制为 $w$，有 $|t_1-t_2|\le w$。显然这是一个典型的差分约束算法；只需要按照 $d_{1,i}(2\le i<n)$ 从小到大排序，依次将每一只动物放进集合（如果 $d_{1,i}=d_{1,j}$ 相同那么将 $i$ 和 $j$ 同时放入集合）；对于相邻的两次游戏，令第二次游戏新加入的动物与 $1$ 之间的最短路为 $x$，上一次游戏加入的动物与 $1$ 之间的最短路为 $y$，那么第一次游戏持续时间应该为 $y-x$。一直放到必须把 $n$ 加进去时结束游戏。可以证明游戏轮数最多为 $n-1$，玩的最多时间为 $d_{1,n}$，符合题意。

实现过程可以使用优先队列维护。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
typedef pair<int,int> pii;
main(){
  ios::sync_with_stdio(false);
  int n,m,c=0; cin>>n>>m;
  vector<vector<int> > d(n,vector<int>(n,2e18));
  vector<bool> b(n);
  for(int i=0;i<n;i++)d[i][i]=0; // 初始化
  for(int i=0;i<m;i++){
    int u,v,w; cin>>u>>v>>w;
    d[u-1][v-1]=d[v-1][u-1]=w;
  } // 建边
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      for(int k=0;k<n;k++)
        if(i!=j&&i!=k&&j!=k)
          d[j][k]=min(d[j][k],d[j][i]+d[i][k]);
  // Floyd 算法预处理最短路
  if(d[0][n-1]==2e18)cout<<"inf\n"; // 可以玩无限久
  else{
    vector<pair<vector<bool>,int> > r;
    priority_queue<pii,vector<pii>,greater<pii> > q;
    for(int i=0;i<n;i++)
      if(d[0][i])q.emplace(d[0][i],i);
      else b[i]=true;
    while(!q.empty()&&!b[n-1]){
      int u=q.top().second; q.pop();
      if(b[u])continue;
      r.emplace_back(b,d[0][u]-c),c=d[0][u];
      for(int i=1;i<n;i++)
        if(d[0][i]==d[0][u])b[i]=true; // 打标记
    } // 每次取出剩下的中与 1 最短路最小的几个数
    cout<<d[0][n-1]<<' '<<r.size()<<endl;
    for(auto [x,y]:r){
      for(bool i:x)cout<<i;
      cout<<' '<<y<<endl;
    }
  }
  return 0;
}
```

---

## 作者：Autre (赞：5)

首先以 $m$ 条 special restrictions 为边建一幅无向图，对于某一分钟的选取方案，我们定义关键边为两侧的点一个被选中，另一个未被选中的边。

然后考察任意一条 $1\to n$ 的路径，不难发现，点 $1$ 总需要被选取，点 $n$ 不可以被选取，因此任何一种选取朋友的方案的任意一刻，这条路径上至少有一条关键边。而在一种游戏方案中，每一条边为关键边的时间不超过它的边权。于是游戏时长不可能超过 $1\to n$ 的任意一条路径的长度，也就不可能超过 $1\to n$ 的最短路。

证明了游戏时长存在一个上界，现在需要构造一种方案使得游戏时长能够达到这个上界。记 $d_i$ 为 $1\to i$ 的最短路，点 $i$ 在 $[1,d_i)$ 这个时间段不被选取，在 $[d_i,d_n]$ 的时间段被选取，于是任意一条边权为 $w$ 的边 $(u,v)$ 满足 $|d_u-d_v|\le w$（最短路的性质），而前者即这条边作为关键边的时长，从而保证了题目的 special restrictions 成立。

然后就可以如此构造答案。

```C++
#include<algorithm>
#include<iostream>
#include<cstring>

const int N = 100;
long long g[N][N], t[N];
int main() {
    int n, m, k; std::cin >> n >> m, memset(g, 0x3f, sizeof g);
    for (int i=0; i<n; i++) g[i][i] = 0;
    for (int u, v, w; m--;) std::cin >> u >> v >> w,
        g[u-1][v-1] = g[v-1][u-1] = w;
    for (int k=0; k<n; k++) for (int i=0; i<n; i++) for (int j=0; j<n; j++)
        g[i][j] = std::min(g[i][j], g[k][i]+g[k][j]);
    if (*g[n-1] == 0x3f3f3f3f3f3f3f3f) return puts("inf"), 0;
    for (int i=0; i<n; i++) t[i] = *g[i];
    std::sort(t, t+n), k = std::lower_bound(t, std::unique(t, t+n), *g[n-1])-t;
    printf("%lld %ld\n", *g[n-1], k);
    for (int i=0; i<k; printf(" %lld\n", t[i+1]-t[i]), i++)
        for (int j=0; j<n; j++) printf("%d", *g[j] <= t[i]);
}
```

---

## 作者：strcmp (赞：3)

**题目大意：**

$1$ 必须参加聚会，$n$ 必须不参加聚会。另有 $m$ 个限制 $(u,\,v,\,y)$，代表只有 $u$ 一个参加聚会的次数，和只有 $v$ 一个参加聚会的次数，这两个值**有且只有一个**小于等于 $y$。


------------

读题半小时切题五分钟了属于是。

注意到 $n$ 不能参加、$1$ 必须参加的限制很怪，必然是要在上面搞事情的。

考虑搞出每个人的参会时间 $w_u$。

那么对于限制 $(u,\,v,\,y)$，容斥一下就可以得到 $w_u - w_v \le y$ 和 $w_v - w_u \le y$。即 $w_u \le w_v + y$ 和 $w_v \le w_u + y$。

我们发现这跟最短路的限制一模一样！具体的，对于限制连接 $(u,\,v)$ 的双向边，边权为 $y$，那么如果找到了一个最短路，最短路的 $\text{dist}$ 数组就是 $w$。

$n$ 不能参加，就可以设置 $w_n = 0$；因为 $1$ 必然参加，那么聚会总时间就是 $w_1$。剩下的用 floyd 跑最短路就行了。

接下来的问题是怎么去构造，一个想法是把所有 $i \dots n$ 的最短路长度排序去重存进 $c$ 里，则 $(i,\,j)$ 是 $1$ 的条件是 $w_{1,\,j} \le c_i$，第 $i$ 行持续 $c_{i + 1} - c_i$ 秒。

```cpp
#include <bits/stdc++.h>
#define X first
#define Y second
using namespace std;
typedef long long int ll;
using pll = pair<ll, ll>;
const int maxn = 2e5 + 10;
const ll inf = 114514191981052013LL;
int n, m; ll a[maxn], d[505][505], c[maxn];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			d[i][j] = (i == j ? 0 : inf);
		}
	}
	for (int i = 1; i <= m; i++) {
		int u, v; ll y;
		scanf("%d%d%lld", &u, &v, &y);
		d[u][v] = d[v][u] = y;
	}
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
			}
		}
	}
	if (d[1][n] >= inf) puts("inf");
	else {
		int p = 0;
		for (int i = 1; i <= n; i++) if (d[1][i] <= d[1][n]) c[++p] = d[1][i];
		sort(c + 1, c + p + 1);
		p = unique(c + 1, c + p + 1) - c - 1;
		printf("%lld %d\n", d[1][n], p - 1);
		for (int i = 1; i <= p - 1; i++) {
			for (int j = 1; j <= n; j++) printf("%d", (d[1][j] <= c[i]));
			printf(" %lld\n", c[i + 1] - c[i]);
		}
	}
	return 0;
}
```

---

## 作者：cinis (赞：2)

### 移演丁真，鉴定为：最短路

#### 题意：

给出一张 $ n $ 节点 $ m $ 条边的图，需要求出 $ k \leq n^2 $ 个不同的集（对于相同的集不做数量限制），满足每个集合包括 $ 1 $ 号结点且不包括 $ n $ 号结点，并且使不在同一个集合中在一条边两端的结点的集合出现的次数不超过该边的权值，以使全部集合大小之和最大。

#### 题解：

在开始讲解之前，为方便先设链接 $ u,v $ 结点的边的权值-**不同时出现**两端结点的值为 $ f(u,v) $。

首先容易猜出一个除 $ n $ 号结点以外包括全部结点的集合是最优情况，因为这除了减少与 $ n $ 号结点相连的边的 $ f(n,i) , (i\in[1,n-1]) $ 之外对于其他边全无影响。

其次，在这样的贪心下当一个边 $ u-v $ 的 $ f(u,v) $ 削减为 $ 0 $ 时，由于 $ u $ 和 $ v $ 此后不能再不同时出现，那么 $ u $ 和 $ v $ 都不能再次出现（在贪心中于 $ u $ 和 $ v $ 必有一个在开始削减 $ f(u,v) $ 之前无法出现的结点，否则不能对 $ u-v $ 的 $ f(u,v) $ 产生削减的条件，即 $ u $ 和 $ v $ 不同时出现），所以程序将于结点 $ 1 $ 不可存在于集合中而结束。

这样一来，我们就发现这实际上很接近一个**最短路**程序。这个最短路的起点为 $ n $ 号结点，终点为 $ 1 $ 号结点。在无法到达 $ 1 $ 号结点的情况下，答案为 'inf'。

在实现层面，对于求每个集的问题可以考虑按顺序对每个结点距离 $ n $ 号结点的距离上，从除 $ n $ 外的全集按照距离顺序逐渐除掉该结点对应的元素，在排序上我使用了大根堆。

时间复杂度为 $ O(N\log{N}) $，瓶颈为最短路算法，可以通过题目。

代码：
```cpp
LL N,M,u[5451],v[5451],w[5451],dis[105];//n,m,u_i,v_i,w_i, 每个结点距离 n 结点的距离
LL aln[12001][101],en,alnt[12001];//每个不同的集合，不同集合的数量，每个不同集合重复的数量
vector<pii >G[105];//图
bool vis[600000];//dij 算法是否处理完成某个点（其实不需要？）
struct node{
	LL id,dis;
	bool operator < (const node &B) const{return dis>B.dis;}
};
void dij(){
	priority_queue<node>q;
	memset(dis,0x7f,sizeof dis);
	dis[N]=0;
	q.push((node){N,0});
	while(q.size()){
		LL x=q.top().id;
		q.pop();
		if(vis[x])continue;
		vis[x]=1;
		for(pii j:G[x]){
			LL y=j.fi,ww=j.se;
			if(dis[y]<=dis[x]+ww)continue;
			dis[y]=dis[x]+ww;
			q.push((node){y,dis[y]});
		}
	}
    return ;
}//最短路算法（堆优化 Dijkstra ）
priority_queue<node>qn;//排序每个结点距离
void solve(){
	N=read(),M=read();
	rep(i,1,M){
		u[i]=read(),v[i]=read(),w[i]=read();
		G[u[i]].pb(mp(v[i],w[i]));
		G[v[i]].pb(mp(u[i],w[i]));//手动联编
	}
	dij();
	if(dis[1]>1000000000000000000ll){puts("inf");return ;}//如果无法到达输出无穷
	LL ltm=dis[1];
	rep(i,1,N-1)aln[0][i]=1;//全集，除n
	rep(i,1,N-1){
		qn.push((node){i,dis[i]});
	}//录入每个结点距离
	LL lst=0;
	while(qn.size()&&qn.top().dis<=1000000000000000000ll){//存在剩余结点，剩余结点可到达
		if(qn.top().dis==lst){
			aln[en][qn.top().id]=0;
			qn.pop();
			continue;
		}
		alnt[en]=qn.top().dis-lst;
		lst=qn.top().dis;
		rep(i,1,N)aln[en+1][i]=aln[en][i];
		aln[++en][qn.top().id]=0;//更新不可用的结点（集合元素）
		if(en>11000)break;//如果不同集合数量超过 n^2
		qn.pop();
	}
	if(en>=N*N){//如果超过 n^2，由于集合元素单调递减，舍弃第 n^2 个集合以后的集合
		en=N*N-1;
		LL lt=0;
		rep(i,0,en)lt+=alnt[i];
		printf("%lld %lld\n",lt,en+1);
		rep(i,0,en){
			rep(j,1,N)printf("%lld",aln[i][j]);
			printf(" %lld\n",alnt[i]);
		}
		return ;
	}
	rep(i,0,en){
		if(aln[i][1]==0){en=i-1;break;}//否则集合结束于第一个不可存在 1 号结点的集合的前驱集合
	}
	printf("%lld %lld\n",dis[1],en+1);
	rep(i,0,en){
		rep(j,1,N)printf("%lld",aln[i][j]);
		printf(" %lld\n",alnt[i]);
	}
}
```

---

## 作者：zhongpeilin (赞：1)

## D. Tenzing and His Animal Friends
题目大意：$N$ 个人要开 party，每一次 party $1$ 必须在，$n$ 必须不在，有 $m$ 个限制，每次给你 $u_{i},v_{i},y_{i}$，表示 $u_{i}$ 或 $v_{i}$ 独自在场的时间不超过 $y_{i}$，请问 party 最长多久?  

-----
解题思路：不难想到如果 $x, n, y$ 有限制，那么 $x$ 最多开 $y$ 的 party，如果还有一个 $u$ 满足 $u, x, z$ 的话，$u$ 最多开 $z + y$ 的party...以此类推。在此，我们发现了两个性质：  

1.如果建完图后 $1$ 和 $n$ 不连通，则 $1$ 一直开 party，答案：$\inf$.  
2.一个点最多可以开他到 $n$ 的最短路径长度的 party.

那么不难想到，为了 party 时间最大，我们每一次尽可能少的限制消耗他。  
就是假设 $A$ 是现在还可以加入开 party 的点的集合，$B$ 表示现在已经不能开 party 的集合。  
那么我们这一次就是将 $A$ 集合中 $dis$ 最小的点选出来，这次开 party 的人就是 $A$ 集合，开的时间是此人到 $n$ 的最短路径减去前几次的答案，开完后将这个人划入 $B$ 集合即可。

[AC Code](https://codeforces.com/contest/1842/submission/219082271)


---

