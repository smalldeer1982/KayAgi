# [ABC254E] Small d and k

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc254/tasks/abc254_e

$ N $ 頂点 $ M $ 辺の単純無向グラフがあり、各頂点には $ 1,\ldots,N $ と番号が付けられています。 $ i=1,\ldots,M $ に対し、 $ i $ 番目の辺は頂点 $ a_i $ と頂点 $ b_i $ を結びます。また、**各頂点の次数は $ 3 $ 以下です。**

$ i=1,\ldots,Q $ に対し、次のクエリに答えてください。

- 頂点 $ x_i $ との距離が $ k_i $ 以下であるような頂点の番号の総和を求めよ。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 1.5\ \times\ 10^5 $
- $ 0\ \leq\ M\ \leq\ \min\ (\frac{N(N-1)}{2},\frac{3N}{2}) $
- $ 1\ \leq\ a_i\ \lt\ b_i\ \leq\ N $
- $ i\neq\ j $ ならば $ (a_i,b_i)\ \neq\ (a_j,b_j) $
- 与えられるグラフの各頂点の次数は $ 3 $ 以下
- $ 1\ \leq\ Q\ \leq\ 1.5\ \times\ 10^5 $
- $ 1\ \leq\ x_i\ \leq\ N $
- $ 0\ \leq\ k_i\ \leq\ 3 $
- 入力はすべて整数

### Sample Explanation 1

$ 1 $ 番目のクエリでは、頂点 $ 1 $ との距離が $ 1 $ 以下であるような頂点は頂点 $ 1 $ のみなので $ 1 $ が答えです。 $ 2 $ 番目のクエリでは、頂点 $ 2 $ との距離が $ 2 $ 以下であるような頂点は頂点 $ 2,3,4,5,6 $ なのでこれらの総和の $ 20 $ が答えになります。 $ 3 $ 番目以降のクエリも同様にして答えを求められます。

## 样例 #1

### 输入

```
6 5
2 3
3 4
3 5
5 6
2 6
7
1 1
2 2
2 0
2 3
4 1
6 0
4 3```

### 输出

```
1
20
2
20
7
6
20```

# 题解

## 作者：zhujiangyuan (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc254_e)

ABC 的 E 题这么简单？

## 题意
给定 $n$ 个点 $m$ 条边的简单无向图，特别地，**保证每个点的度数不超过** $3$。$q$ 次询问，给定 $x,k$，求所有距离 $x$ 不超过 $k$ 的点（包括 $x$）的编号和。

## Solution

看到题面中“**求所有距离 $x$ 不超过 $k$ 的点（包括 $x$）的编号和**”这句话，考虑广搜，因为广搜是按照距离搜的，这样更好的计算距离。

每次询问时，BFS 一次，初始时定义 $d_x=0$，即 $x$ 与 $x$ 的距离为 $0$，然后将 $x$ 进队。每次取出队头 $y$，扫描与 $y$ 相连的所有边，这些边的另一端点 $i$ 与 $y$ 的距离 $d_j=d_y+1$。这样扫下去就行了，记得用 $vis$ 数组标记该店是否访问过。

由于广搜是按照距离搜的，所以访问的点与点 $x$ 的距离是 $1,2,3$ 这样递增的，所以扫到 $d_y>k$ 时，就跳出循环，因为剩下的距离都是大于 $k$ 的。

## Code

本人较懒，用 `vector` 存图，码量少多了。~~`vector` 真的太方便了！~~
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=150010;
int n,m,Q,x,k,d[N];
vector<int>G[N];
ll ans;
bool vis[N];
void bfs()
{
	ans=0;//答案每次清零
	memset(vis,0,sizeof(vis));//标记数组清零
	queue<int>q;
	q.push(x);
	d[x]=0;
	vis[x]=1;
	while(q.size())
	{
		int y=q.front();q.pop();
		if(d[y]>k) break;//距离大于k
		ans+=y;
		for(auto i:G[y])//扫描与y相连的边，此处"i"即为该边另一端点
		{
			if(!vis[i]) vis[i]=1,q.push(i),d[i]=d[y]+1;
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int u,v;
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);//无向图存边存两次
	}
	cin>>Q;
	while(Q--)
	{
		cin>>x>>k;
		bfs();
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：Redamancy_Lydic (赞：2)

## 简略的题意

$n$ 个点 $m$ 条边的无向图，有 $q$ 次询问，每次给 $x,k$，求所有距离 $x$ 不超过 $k$ 的点的和。

## 小小的分析

~~一眼广搜~~。

题意很明显，用邻接表存图，然后从 $x$ 开始广搜，用 $d$ 数组存储距离，每次拓展将合法点放进队列里，并计算当前距离 $d_y=d_x+1$，最后把点权累加到答案里即可。

需要注意，因为是多测，所以每次计算前需要清空数组。

小贴士：判断是否访问过的数组 $vis$ 标记最好写在前面，否则可能会漏掉初始点 ~~就像我因为这个傻憨憨的调样例~~。

然后就可以放码了。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
int w=1,s=0;char ch=getchar();
while(!isdigit(ch)){if(ch=='-') w=-1;ch=getchar();}
while(isdigit(ch)){s=s*10+(ch-'0');ch=getchar();}
return w*s;
}
int n,m,k,q;
int head[900100],len,dis[500100];
struct no
{
	int y,nxt;
}edge[900100];
void add(int a,int b)
{
	edge[++len].y=b;
	edge[len].nxt=head[a];
	head[a]=len;
}//链式前向星存图 
int d[500100];//距离数组 
bool vis[300000];
void bfs(int x,int k)
{
	int ans=0;
	memset(vis,0,sizeof vis);
	queue<int> q;
	q.push(x);
	d[x]=0;
	vis[x]=1;//就比如这个 
	while(q.size())
	{
		int x=q.front();
		q.pop();
		if(d[x]>k) 
		break;
		ans+=x;
		for(int i=head[x];i;i=edge[i].nxt)//遍历 
		{
			int y=edge[i].y;
			if(!vis[y])
			{
				d[y]=d[x]+1;//更新状态 
				q.push(y);//入队 
				vis[y]=1;//标记 
			}
		}
    }
    printf("%d\n",ans);
}
signed main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
    	int x,y;
    	x=read();y=read();
    	add(x,y);add(y,x);//无向图，存两次 
	}
	int Q=read();
	while(Q--)
	{
		int x=read();int k=read();
		bfs(x,k);
	}
    return 0;
}
```



---

## 作者：Tsawke (赞：2)

# [[ABC254E] Small d and k](https://www.luogu.com.cn/problem/AT_abc254_e) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC254E)

## 题面

给定 $ n $ 个点 $ m $ 条边的简单无向图，特别地，**保证每个点的度数不超过** $ 3 $。$ q $ 次询问，给定 $ x, k $，求所有距离 $ x $ 不超过 $ k $ 的点（包括 $ x $）的编号和。

## Solution

属实是一道水题，最开始还在想有什么性质，比如是不是最多是一棵二叉树之类的。。。然后突然发现保证了 $ 0 \le k_i \le 3 $，于是这道题就变成了一道无脑宽搜了。图建出来之后每次询问在 $ x $ 点宽搜一下即可。只需要注意判一下 `vis` 和注意别漏了 $ x $ 本身即可，最终复杂度即为 $ O(3^kq) $，显然能过。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

template < typename T = int >
inline T read(void);

struct Edge{
    Edge* nxt;
    int to;
    OPNEW;
}ed[610000];
ROPNEW(ed);
Edge* head[160000];

int N, M;
bitset < 160000 > vis;

int bfs(int S, int D){
    if(!D)return S;
    basic_string < int > nods;
    queue < pair < int, int > > cur;
    cur.push({S, 0}), vis[S] = true, nods += S;
    while(!cur.empty()){
        auto tp = cur.front(); cur.pop();
        for(auto i = head[tp.first]; i; i = i->nxt)
            if(!vis[SON]){
                vis[SON] = true;
                nods += SON;
                if(tp.second + 1 < D)cur.push({SON, tp.second + 1});
            }
    }int ret(0);
    for(auto nod : nods)vis[nod] = false, ret += nod;
    return ret;
}

int main(){
    N = read(), M = read();
    for(int i = 1; i <= M; ++i){
        int s = read(), t = read();
        head[s] = new Edge{head[s], t};
        head[t] = new Edge{head[t], s};
    }int Q = read();
    while(Q--){
        int S = read(), D = read();
        printf("%d\n", bfs(S, D));
    }
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2022_12_06 初稿

---

## 作者：filletoto (赞：1)

## 思路
有题目可知，这个图是简单无向图，所以我们可以用 `vector` 存图。

通过题目中保证每个点的度数不超过 $3$ 可知，这题我们可用 `BFS` 做。

我们只要以当前点 $x$ 为起点沿着图一层层进行遍历，一旦距离和起点相差超过 $k$ 就终止。注意用一个数组 $vis$ 来记录这个点有没有走过。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,T,x,k,d[150005];
vector<int> G[150005];
long long ans;
bool vis[150005];
void bfs()
{
	ans=0;
	memset(vis,0,sizeof(vis));
	queue<int>q;
	q.push(x);
	d[x]=0;
	vis[x]=1;
	while(q.size())
	{
		int y=q.front();
		if(d[y]>k) break;
		ans+=y;
		for(auto i:G[y])
		{
			if(!vis[i]) 
			{
				vis[i]=1;
				q.push(i);
				d[i]=d[y]+1;
			}
		}
		q.pop();
	}
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int u,v;
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	cin>>T;
	while(T--)
	{
		cin>>x>>k;
		bfs();
		cout << ans << endl;
	}
	
	
	return 0;
}
```

---

## 作者：fuwei123 (赞：1)

首先注意到一个特殊条件，每个点的度数 $d_u$ 不超过 $3$，$k\le3$。那也就是说，假设离 $x$ 距离不超过 $k$ 的节点个数是 $cnt$，那么 $cnt$ 不会超过 ${d_u}^k$，也就是不会超过 $27$。所以直接暴力 bfs 就好了，复杂度 $O(Q\cdot cnt)$，可以通过此题。

注意这里 $vis$ 数组的清空**不能** memset，要**记录一下**这次访问过的节点有哪些，然后**只清空**那些**访问过的点**就行，这样才能保证复杂度。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1.5 * 1e6;
int n, m, Q, a[N], cnt;//a记录dfs访问了哪些点 
vector<int>G[N];
bool vis[N];
struct node{
	int now, pos;
};
queue<node>q;
int bfs(int x, int k){
	vis[x] = 1;
	q.push({0, x});
	a[cnt = 1] = x;
	int res = 0;
	while(!q.empty()){
		node fr = q.front();
		q.pop();
		int u = fr.pos, d = fr.now;
		if(d > k)break;
		res += u;
		if(d == k)continue;
		for(int i = 0;i < G[u].size();i++){
			int v = G[u][i];
			if(vis[v])continue;
			q.push({d + 1, v});
			vis[v] = 1;
			a[++cnt] = v;
		}
	}
	for(int i = 1;i <= cnt;i++)vis[a[i]] = 0;
	return res;
}
signed main(){
	ios::sync_with_stdio(0);
	cin >> n >> m;
	for(int i = 1;i <= m;i++){
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	cin >> Q;
	while(Q--){
		int x, k;
		cin >> x >> k;
		cout << bfs(x, k) << "\n";
	}
	return 0;
}


```


---

## 作者：chengning0909 (赞：1)

# abc 254 e

[AT 链接](https://atcoder.jp/contests/abc254/tasks/abc254_e)

[洛谷链接](https://www.luogu.com.cn/problem/AT_abc254_e)

## 题意

给定一个 $n$ 个点 $m$ 条边的简单无向图，点分别编号为 $1, 2, \dots, n$，第 $i$ 条边连接 $a_i$ 和 $b_i$。每个点的度数至多为 $3$。

对于 $i = 1, 2, \dots, q$，请你求出距离点 $x_i$ 距离不超过 $k_i$ 的点的编号之和。

$1 \le n \le 1.5 \times 10 ^ 5$。

$0 \le m \le \min(\frac{n(n - 1)}{2}, \frac{3n}{2})$。

$1 \le a_i, b_i \le n$。

$1 \le q \le 1.5 \times 10 ^ 5$。

$1 \le x_i \le n$。

$1 \le k_i \le 3$。

## 思路

dfs 或者 bfs（搜索）。

题目有两个很明显的提示：**每个点的度数至多为 $3$** 和 **$1 \le k_i \le 3$**。

这就说明，每次最多找到 $3 ^ 3$ 个点。

直接搜索即可。

------

### 注意

因为是图，所以需要标记每个点是否被走到过，因为每次清空标记数组过于浪费时间，所以可以用一个额外的数组记录最后一次更新最短路是在第几次询问。

-------

时间复杂度为 $O(q \times 3 ^ 3)$。

```cpp

#include <bits/stdc++.h>

using namespace std;

const int N = 1.5e5 + 10;

int n, m, q, x, k, mmax[N], d[N];
vector<int> g[N];

long long Solve(int x, int k, int id) {
  long long ans = x;
  queue<int> que;
  que.push(x), mmax[x] = id, d[x] = 0;  // 初始状态
  while (!que.empty()) {
    int u = que.front();
    que.pop();
    if (d[u] >= k) {  // 如果最短路超过 k[i]
      break;
    }
    for (int v : g[u]) {
      if (mmax[v] < id) {
        mmax[v] = id, que.push(v), ans += v, d[v] = d[u] + 1;  //入队
      }
    }
  }
  return ans;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  while (m--) {
    int a, b;
    cin >> a >> b;
    g[a].push_back(b), g[b].push_back(a);
  }
  cin >> q;
  for (int i = 1; i <= q; i++) {
    cin >> x >> k;
    cout << Solve(x, k, i) << '\n';
  }
  return 0;
}
```

---

## 作者：xvl_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc254_e)

一道暴力题。

度数和 $k$ 那么小？直接暴力 $n$ 遍 bfs，注意 bfs 的队列只能 `push` 距离不超过 $3$ 的点。但有个问题，每次 bfs 都需要清空一次距离数组，这样子的时间复杂度是 $O(n^2)$ 的。但也不难想到，距离数组中被赋值的地方不会很多，记录一下就行。

### Code
```cpp
#include <bits/stdc++.h>

const long long IMX = 1ll << 30;
const long long LMX = 1ll << 60;
const long long MOD = 998244353;

using ll = long long;
using i128 = __int128;
using ld = long double;
using f128 = __float128;

namespace xvl_ { 
	#define SP(n, x) std :: setprecision(n) << std :: fixed << x
	#define REP(i, l, r) for (auto i = (l); i <= (r); i++)
	#define PER(i, r, l) for (auto i = (r); i >= (l); i--)
	#define DEBUG(x) std :: cerr << #x << " = " << x << '\n'
	#define SZ(x) (x.size())
	#define fst first
	#define snd second
	template <typename T> T Max(T a, T b) { return a > b ? a : b; } template <typename T, typename... Args> T Max(T a, Args... args) { return a > Max(args...) ? a : Max(args...); }
	template <typename T> T Min(T a, T b) { return a < b ? a : b; } template <typename T, typename... Args> T Min(T a, Args... args) { return a < Min(args...) ? a : Min(args...); }
}
using namespace std;
using namespace xvl_;
struct Node { ll id, cnt; };
ll n, m, q;
ll dis[150005];
vector <int> G[150005];
vector <pair <int, int>> D[150005];
// first 代表编号，second 代表步数
void bfs(ll s) {
	if (s == 1) fill(dis + 1, dis + 1 + n, IMX);
	else for (auto v : D[s - 1]) dis[v.fst] = IMX;
	queue <Node> q;
	vector <int> p;
	q.push({s, 0}), dis[s] = 0;
	while (!q.empty()) {
		Node cur = q.front();
		q.pop();
		for (auto v : G[cur.id]) {
			if (cur.cnt + 1 < dis[v] and cur.cnt + 1 <= 3) {
				dis[v] = cur.cnt + 1;
				p.push_back(v);
				q.push({v, dis[v]});
			}
		}
	}
	D[s].push_back(make_pair(s, 0));
	for (auto v : p) {
		if (dis[v] <= 3) D[s].push_back(make_pair(v, dis[v]));
	}
}
int main() {
	// freopen("InName.in", "r", stdin);
	// freopen("OutName.out", "w", stdout);
	ios :: sync_with_stdio(0);
	cin.tie(nullptr);
	cin >> n >> m;
	REP(i, 1, m) {
		ll u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	REP(i, 1, n) bfs(i);
	cin >> q;
	while (q--) {
		ll x, k, ans = 0;
		cin >> x >> k;
		for (auto v : D[x]) {
			if (v.snd <= k) ans += v.fst;
		}
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：zk_y (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc254_e)

## 前言

这道题目我使用了 ``vector`` 来存储数组，因为如果暴力存储，空间会爆炸的。所以在这里我们使用空间和码量都比较好的 ``vector`` 来存储边.

## 题目思路

题目让我们求所有距离 $x$ 不超过 $k$ 的点（包括 $x$）的编号和。我们怎么计算呢？

我们看一下题目的数据范围，因为这道题目每个点的度数都小于等于 $3$。所以，我们可以使用广度优先搜索。

我们如何进行广度优先搜索呢？

我们可以开一个结构体，然后存储每次开始需要操作的 $x$ 和 $y$ 坐标。每次把要询问的点的坐标直接压入队首。然后每次取出队首，进行一些操作，最后将操作完的数（这里是操作完后的坐标）再次压入队列中就可以了。

不过我们最好还是写一个函数，把 ``bfs`` 封装起来，最后我们每次询问调用就可以了。

注意使用 ``vis`` 数组优化的（因为有多次询问，我们需要每次清空 ``vis`` 数组），不过记得开在外面，当然开在里面也可以，就是有点费时间和空间。（不过我的队列就开在里面……）


---
# AC代码
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
const int N=2e5;//方便一点
struct INT{
	int num,step;
}top,first;
int n,m,x,y,k;
vector<int> edges[N];
bool vis[N];
int bfs(int z,int deep){//进行深度和初始的bfs函数
	memset(vis,0,sizeof(vis));
	int ans=0;
	vis[z]=1;
	queue<INT> way;
	top.num=z;top.step=0;
	way.push(top);
	while(!way.empty()){
		first=way.front();
		way.pop();
		ans+=first.num;
		for(int i=0;i<edges[first.num].size();i++){
			if(!vis[edges[first.num][i]]){
				top.num=edges[first.num][i];
				top.step=first.step+1;
				vis[top.num]=1;
				if(top.step<=deep)way.push(top);
			}
		}
	}
	return ans;//结束！
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		edges[x].push_back(y);
		edges[y].push_back(x);
	}
	scanf("%d",&k);
	for(int i=1;i<=k;i++){
		scanf("%d%d",&x,&y);
		printf("%d\n",bfs(x,y));
	}
	return 0;
}
```


---

