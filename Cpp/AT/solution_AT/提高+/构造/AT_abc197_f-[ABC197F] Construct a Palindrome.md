# [ABC197F] Construct a Palindrome

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc197/tasks/abc197_f

$ N $ 頂点 $ M $ 辺の、単純とは限らない連結な無向グラフがあります。  
 辺 $ i $ は頂点 $ A_i $ と頂点 $ B_i $ を結んでおり、文字 $ C_i $ が書かれています。  
 頂点 $ 1 $ から頂点 $ N $ へのパス (同じ辺や頂点を複数回通っても構わない) を $ 1 $ つ選び、通る辺に書かれている文字を順に並べて文字列を作ります。  
 この文字列が回文になることはあるかを判定し、あるならばそのような回文の長さとして考えられる最小値を求めてください。

## 说明/提示

### 制約

- $ 2\ \le\ N\ \le\ 1000 $
- $ 1\ \le\ M\ \le\ 1000 $
- $ 1\ \le\ A_i\ \le\ N $
- $ 1\ \le\ B_i\ \le\ N $
- $ C_i $ は英小文字
- 与えられるグラフは連結である

### Sample Explanation 1

辺 $ 1,\ 2,\ 3,\ 1,\ 2,\ 4,\ 5,\ 6,\ 7,\ 8 $ の順に通ると、出来上がる文字列は `abcabbacba` となり、回文となります。 これより短い回文を作ることはできないので、答えは $ 10 $ です。

### Sample Explanation 2

辺 $ 2,\ 3,\ 4,\ 5,\ 5 $ の順に通ると `aabaa` という文字列を作ることができ、これは回文です。 同じ辺や頂点を複数回通っても構わないことに注意してください。

### Sample Explanation 3

出来上がる文字列が回文となることはありません。

## 样例 #1

### 输入

```
8 8
1 2 a
2 3 b
1 3 c
3 4 b
4 5 a
5 6 c
6 7 b
7 8 a```

### 输出

```
10```

## 样例 #2

### 输入

```
4 5
1 1 a
1 2 a
2 3 a
3 4 b
4 4 a```

### 输出

```
5```

## 样例 #3

### 输入

```
3 4
1 1 a
1 2 a
2 3 b
3 3 b```

### 输出

```
-1```

# 题解

## 作者：liyujia (赞：2)

### 题意

给定一个 $n$ 个点 $m$ 条边的无向连通图，可能有重边，自环，每条边有一个小写字母 $c_i$。求满足以下条件的路径的最小长度：

* 起点为 $1$，终点为 $n$
* 把路径上所有经过的边的 $c_i$ 按顺序拼接，形成的字符串是回文的。

若不存在满足条件的路径，输出 `-1`。

### 解法

作为 F 真不难。

首先改写条件，回文就相当于第一个字符和最后一个相同，第二个和倒数第二个相同，依此类推。

单向处理不了，所以不难想到双向的搜索。

考虑以下过程：初始两个位置分别是 $1,n$，每次两个位置各选择一条连出的边，满足边上的字母相同，并向另一个端点移动，最终两个位置重合。

设这个相同的位置是 $s$，此时 $1\rightarrow s$ 的路径和 $n\rightarrow s$ 的路径所形成的字符串相同。将 $n\rightarrow s$ 反过来，再在前面接上 $1\rightarrow s$，最终会得到一条满足条件的路径。

于是把两个位置放进状态中，再进行广搜。

不过这只能处理长度为偶数的情况，对于长度为奇数时的情况，只需要找到两个位置之间恰好隔了一条边的情况，其它过程是相同的，在统计答案时再处理。一些实现细节可以看代码。

设点 $i$ 的度数是 $deg_i$，时间复杂度 $O(\sum_i\sum_j deg_i\times deg_j)=O(\sum_i deg_i\times \sum_jdeg_j)=O(m^2)$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, h[2005], ne[2005], d[1005][1005], e[2005], cnt;
char w[2005];
void add(int u, int v, char c){
	ne[++cnt] = h[u], e[cnt] = v, w[cnt] = c, h[u] = cnt;
}
void bfs(){
	memset(d, -1, sizeof d);
	queue <pair <int, int> > q;
	q.push({1, n}), d[1][n] = 0;
	while(!q.empty()){
		auto t = q.front();
		q.pop();
		int x = t.first, y = t.second;
//		cout << x << ' ' << y << endl;
		for(int i = h[x]; ~i; i = ne[i])
			for(int j = h[y]; ~j; j = ne[j])
				if(w[i] == w[j]){
					if(d[e[i]][e[j]] != -1) continue;
					d[e[i]][e[j]] = d[x][y] + 2, q.push({e[i], e[j]});
				}
	}
}
int main(){
	memset(h, -1, sizeof h);
    cin >> n >> m;
    char w;
    for(int i = 1, u, v; i <= m; i++)
    	cin >> u >> v >> w, add(u, v, w), add(v, u, w);
    bfs();
    int ans = 1e9;
    for(int i = 1; i <= n; i++)
    	if(d[i][i] != -1)
			ans = min(ans, d[i][i]);
	for(int i = 1; i <= n; i++)
		for(int j = h[i]; ~j; j = ne[j])
			if(d[i][e[j]] != -1)
				ans = min(ans, d[i][e[j]] + 1);
    cout << (ans == 1e9? -1: ans);
	return 0;
}
```

---

## 作者：CQ_Bob (赞：1)

## 分析

考虑暴力。

定义 $dis_{i,j}$ 表示从 $1$ 走到 $i$，从 $n$ 走到 $j$ 的最短路。对于两条边 $x \to x'$ 和 $y \to y'$，如果这两条边上边权相同，那很显然是可以同时走的。

所以把所有的这样的边重新建出来，跑一个最短路。答案分为两种情况：

1. 最短路是偶数。则答案的 $i=j$，即 $ans=\min\limits_{i=1}^{n} dis_{i,i}  \times 2$。

2. 最短路是奇数。则答案为：$ans=\min\limits_{i \ne j}^{} dis_{i,j} \times 2 +1$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define pii pair<int,int>
#define x first
#define y second
#define gc getchar()
#define rd read()
#define debug() puts("------------")

namespace yzqwq{
	il int read(){
		int x=0,f=1;char ch=gc;
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=gc;}
		while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=gc;
		return x*f;
	}
	il int qmi(int a,int b,int p){
		int ans=1;
		while(b){
			if(b&1) ans=ans*a%p;
			a=a*a%p,b>>=1;
		}
		return ans;
	}
	il auto max(auto a,auto b){return (a>b?a:b);}
	il auto min(auto a,auto b){return (a<b?a:b);}
	il int gcd(int a,int b){
		if(!b) return a;
		return gcd(b,a%b);
	}
	il int lcm(int a,int b){
		return a/gcd(a,b)*b;
	}
	il void exgcd(int a,int b,int &x,int &y){
		if(!b) return x=1,y=0,void(0);
		exgcd(b,a%b,x,y);
		int t=x;
		x=y,y=t-a/b*x;
		return ;
	}
	mt19937 rnd(time(0));
}
using namespace yzqwq;

const int N=2e6+10,M=1e3+10;
int n,m;
struct node{int y;char z;};
vector<node> e[N];
vector<pii> v[M][M];
int dis[M][M],vis[M][M];

il void dij(){
	memset(dis,0x3f,sizeof(dis)),
	memset(vis,0   ,sizeof(vis));
	priority_queue<pair<int,pii>,vector<pair<int,pii>>,greater<pair<int,pii>>> qu;
	qu.push({0,{1,n}}),dis[1][n]=0;
	while(!qu.empty()){
		int dist=qu.top().x,x=qu.top().y.x,y=qu.top().y.y;
		qu.pop();
		if(vis[x][y]) continue;
		vis[x][y]=1;
		for(auto i:v[x][y]){
			if(dis[i.x][i.y]>dist+1)
				dis[i.x][i.y]=dist+1,
				qu.push({dis[i.x][i.y],{i.x,i.y}});
		}
	}
	return ;
}

il void solve(){
	n=rd,m=rd;
	for(re int i=1;i<=m;++i){
		int x=rd,y=rd;char s;cin>>s;
		e[x].push_back({y,s}),
		e[y].push_back({x,s});
	}
	for(re int i=1;i<=n;++i)
	for(re int j=1;j<=n;++j){
		if(i==j) continue;
		for(auto x:e[i])
		for(auto y:e[j])
			if(x.z==y.z) v[i][j].push_back({x.y,y.y}); 
	}
	dij();int Min=1e18;
	for(re int i=1;i<=n;++i) Min=min(Min,dis[i][i]*2);
	for(re int i=1;i<=n;++i)
	for(re int j=1;j<=n;++j)
	for(auto k:v[i][j]){
		if(k.x==j&&k.y==i) Min=min(Min,dis[i][j]*2+1);
	}
	printf("%lld\n",Min>1e9?-1:Min);
	return ;
}

signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int t=1;while(t--)
	solve();
	return 0;
}

```

---

## 作者：Mason123456 (赞：1)

# ABC197F

### 前言

update 24/5/28：添加前言部分，修改 `bfs` 部分代码定义问题，增加 `vis` 数组的定义及作用。

### 分析

从头开始分析一遍。

回文串要满足头对头，尾对尾的特性，并且题目要求以 $1$ 开始，$n$ 节点结尾。加上要求最短路，我们就可以使用**广搜**进行处理。

### 思路

广搜是从 $1$ 节点和 $n$ 节点开始搜索，如果发现以 $a$ 与 $b$ 为出发节点的两条边 $l_1,l_2$ 颜色相同时，就继续搜索。于是 `bfs` 程序就是这样的：

```cpp
const int N = 1e3 + 5;
struct O {
	int u;// 节点编号 
	char r;// 节点颜色 
};
vector<O> g[N];// vector存图
struct node {
	int front;// 从1出发的搜索路线 
	int end;// 从n出发的搜索路线 
	int stp;// 搜索步数 
};
int n, m;// 如题

bool cg[N][N];// 邻接表存图
bool vis[N][N];// rtj

void bfs() {
	queue<node> q;
	q.push({1, n, 0});
	while(!q.empty()) {
		node t = q.front();
		q.pop();
		int s = t.stp + 1;
		for(auto x : g[t.front]) {
			for(auto y : g[t.end]) {
				if(x.r == y.r && !vis[x.u][y.u]) { // 是同一个颜色
					vis[x.u][y.u] = 1;
					q.push(node {x.u, y.u, s});
				}
			}
		}
	}
}
```

其中，`node` 数据结构的定义比较讲究。懂的人知道是双端广搜，不懂的人~~像我一样~~就当是普通的广搜就好了。`front` 表示从 $1$ 开始搜索的路线 $l_1$ 的末端点（通俗的讲就是搜到哪了），`end` 表示从 $n$ 开始搜索的路线 $l_2$ 的末端点。`stp` 表示从两端开始搜的步数。

关于 `vis` 数组的设定，我们发现当左端搜索路线和右端搜索路线已经重复时，肯定已经处理过了，所以要保证搜索路线最短（因为是 `bfs`），就不用再重复搜索。

里面的 `vis[x][y]` 数组表示点 $x$ 和点 $y$ 有没有同时作为结尾搜索过。所以，对于搜索，一共有 $n^2$ 个点。

再来考虑答案。看这个图：

![](https://p.sda1.dev/17/4aec2497a218278bda7105549d7ea3ce/graph1.png)

其中，$n=8$。

很显然，对于左边，当从 $1$ 和 $n$ 开始搜索搜到同一个点时，它肯定是一个答案。对于右边，我们发现当步数为奇时，`front` 与 `end` 连通也是一种情况。

所以就有了答案判断：

```cpp
if(t.front == t.end)	ans = min(ans, t.stp * 2);
if(cg[t.front][t.end])	ans = min(ans, t.stp * 2 + 1);
```

`cg[x][y]` 是邻接表存图法。

### 时间复杂度

对于思路，肯定不难想，也最多只有绿的难度。真正的时间复杂度证明才让题目成了蓝题。

设 $\text{deg}(x)$ 表示 $x$ 的**出边**， 时间复杂度暂设 $ans$。

$$
\therefore ans= \sum_{1 \le a \le n} \sum_{1 \le b \le n} \text{deg}(a) \times \text{deg}(b)
$$

$$
ans = \text{deg}(1)\times \text{deg}(1) + \text{deg}(1) \times\text{deg}(2)+\dots
$$

$$
= \text{deg}(2)\times \text{deg}(1) + \text{deg}(2)\times\text{deg}(2) \dots
$$

$$
\dots
$$

$$
\therefore ans = \text{deg}(1) \times(\text{deg}(1) + \text{deg}(2) + \dots) + \text{deg}(2) \times(\text{deg}(1) + \text{deg}(2) + \dots) + \dots
$$

$$
\therefore ans = \sum_{1 \le a \le n} \text{deg}(a) \times \sum_{1 \le b \le n}\text{deg}(b) = m^2
$$

所以，这题的时间复杂度就是 $O(m^2)$ 了。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 5;
struct O {
	int u;// 节点
	char r;// 颜色
};
struct node {
	int front;// rtj
	int end;
	int stp;
};

int n, m;
vector<O> g[N];// vector存图
bool cg[N][N];// 邻接表
bool vis[N][N];
int ans = INT_MAX;

void bfs() {
	queue<node> q;
	q.push({1, n, 0});
	while(!q.empty()) {
		node t = q.front();
		q.pop();
		if(t.front == t.end)	ans = min(ans, t.stp * 2);
		if(cg[t.front][t.end])	ans = min(ans, t.stp * 2 + 1);
		int s = t.stp + 1;
		for(auto x : g[t.front]) {
			for(auto y : g[t.end]) {
				if(x.r == y.r && !vis[x.u][y.u]) { // 是同一个颜色
					vis[x.u][y.u] = 1;
					q.push(node {x.u, y.u, s});
				}
			}
		}
	}
}

int main() {
	cin>>n>>m;
	for(int i = 1; i <= m; i++) {
		int x, y;
		char r;
		cin>>x>>y>>r;
		g[x].push_back({y,r});
		g[y].push_back({x,r});
		cg[x][y] = cg[y][x] = 1;
	}
	bfs();
	if(ans == INT_MAX)	cout<<-1;
	else cout<<ans<<"\n";
	return 0;
}
```

关于 `c++` 的 `auto` 语法，可以自行百度一下。

---

## 作者：qzhwlzy (赞：0)

### 题目大意

给定一张 $n$ 个点 $m$ 条边的无向图，边有一个字母作为边权。求从 $1$ 到 $n$ 的最短路径长度，使得路径上的字母连起来是一个回文串。无解输出 `-1`。

### 思路

回文串即首尾字母相同、第二个和倒数第二个字母相同……于是，我们可以采用双向广搜，即从 $1$ 和 $n$ 同时开始搜，若有两条边边权一样就一起跳，用 $f_{i,j}$ 表示 $1\rightarrow i$，$n\rightarrow j$ 的最小路径长度，然后爆搜转移即可。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#define maxn 1005
#define pii pair<int,int>
#define m_p make_pair
#define a_f first
#define a_s second
using namespace std;
int n,m,u,v; char ch; struct edge{int to,nex; char ch;}a[maxn*2]; int head[maxn],cnt=0;
void add(int from,int to,char ch){a[++cnt]=(edge){to,head[from],ch}; head[from]=cnt;}
int f[maxn][maxn]; queue<pii> q;
void bfs(){
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) f[i][j]=1e9; f[1][n]=0; q.push(m_p(1,n)); while(!q.empty()){
		pii top=q.front(); q.pop();
		for(int i=head[top.a_f];i;i=a[i].nex) for(int j=head[top.a_s];j;j=a[j].nex)
			if(a[i].ch==a[j].ch&&f[a[i].to][a[j].to]==1e9)
				{f[a[i].to][a[j].to]=f[top.a_f][top.a_s]+2; if(a[i].to!=a[j].to) q.push(m_p(a[i].to,a[j].to));}
	}
}
int main(){
	scanf("%d%d",&n,&m); for(int i=1;i<=m;i++) scanf("%d%d %c",&u,&v,&ch),add(u,v,ch),add(v,u,ch);
	bfs(); int ans=1e9; for(int i=1;i<=n;i++) ans=min(ans,f[i][i]); // 长度为偶数
	for(int i=1;i<=n;i++) for(int j=head[i];j;j=a[j].nex) ans=min(ans,f[i][a[j].to]+1); // 长度为奇数
	printf("%d",ans==1e9?-1:ans); return 0;
}
```

---

