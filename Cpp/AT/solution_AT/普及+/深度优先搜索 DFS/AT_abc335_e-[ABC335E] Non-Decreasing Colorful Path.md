# [ABC335E] Non-Decreasing Colorful Path

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc335/tasks/abc335_e

$ N $ 頂点 $ M $ 辺の連結な無向グラフがあり、 $ i $ 番目の辺は頂点 $ U_i $ と頂点 $ V_i $ を双方向に結びます。  
 また、全ての頂点に整数が書いてあり、頂点 $ v $ には整数 $ A_v $ が書かれています。

頂点 $ 1 $ から頂点 $ N $ への単純なパス ( 同じ頂点を複数回通らないパス ) に対して、以下のように得点を定めます。

- パス上の頂点に書かれた整数を通った順に並べた数列 を $ S $ とする。
- $ S $ が広義単調増加になっていない場合、そのパスの得点は $ 0 $ である。
- そうでない場合、 $ S $ に含まれる整数の種類数が得点となる。
 
頂点 $ 1 $ から頂点 $ N $ への全ての単純なパスのうち、最も得点が高いものを求めてその得点を出力してください。

  $ S $ が広義単調増加であるとは? 長さ $ l $ の数列 $ S=(S_1,S_2,\dots,S_l) $ が広義単調増加であるとは、 全ての整数 $ 1\ \le\ i\ について\ S_i\ \le\ S_{i+1} $ を満たすことを言います。

## 说明/提示

### 制約

- 入力は全て整数
- $ 2\ \le\ N\ \le\ 2\ \times\ 10^5 $
- $ N-1\ \le\ M\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ A_i\ \le\ 2\ \times\ 10^5 $
- グラフは連結である
- $ 1\ \le\ U_i\ <\ V_i\ \le\ N $
- $ i\ \neq\ j $ なら $ (U_i,V_i)\ \neq\ (U_j,V_j) $
 
### Sample Explanation 1

$ 1\ \rightarrow\ 3\ \rightarrow\ 4\ \rightarrow\ 5 $ というパスについて $ S=(10,30,40,50) $ となり、このパスの得点は $ 4 $ で、これが最大です。

### Sample Explanation 2

頂点 $ 1 $ から頂点 $ N $ への単純パスであって、 $ S $ が広義単調増加となるものはありません。この場合、最大の得点は $ 0 $ です。

## 样例 #1

### 输入

```
5 6
10 20 30 40 50
1 2
1 3
2 5
3 4
3 5
4 5```

### 输出

```
4```

## 样例 #2

### 输入

```
4 5
1 10 11 4
1 2
1 3
2 3
2 4
3 4```

### 输出

```
0```

## 样例 #3

### 输入

```
10 12
1 2 3 3 4 4 4 6 5 7
1 3
2 9
3 4
5 6
1 2
8 9
4 5
8 10
7 10
4 6
2 8
6 7```

### 输出

```
5```

# 题解

## 作者：TernaryTree (赞：9)

E>F /oh/oh/oh 

---

首先就想，对于一条边 $(u,v)$，去给它定一个向，若 $a_u\neq a_v$，则由 $a_i$ 小的连向大的，因为我们不可能从大的往回跑，这是显然的；

接下来考虑，若 $a_u=a_v$ 应该如何处理。显然这些点实际上是等价的，既不对答案做出贡献，也不会对答案做出限制。所以我们把这些连通的且点权两两相同的点看作是一个点，用并查集缩一下就行。

现在缩完点，所有的 $a_u=a_v$ 的边都扔掉了，而 $a_u\neq a_v$ 的情况实际上 $u,v$ 是作为都在新图上其被缩在同权联通块的新点（根据这里，我们不难知道在后面的处理中，对一个原图上的点要进行并查集上 `find` 之后才能得到新图的对应点）。由于我们是由偏序关系连的有向边，容易发现这张图是张 DAG。

问题转化为：如何在 DAG 上跑出 $1$ 到 $n$ 的最长路？细节十分甚至九分地多，给大家看一份错误代码：

```cpp
queue<int> q;
q.push(1);
f[1] = 1;
while (!q.empty()) {
	int u = q.front();
	q.pop();
	for (int v : g[u]) {
		f[v] = max(f[v], f[u] + 1);
		indeg[v]--;
		if (!indeg[v]) q.push(v);
	}
}
```

这里犯了两个错误。

第一个：$1$ 号点对应在新图上应为 `find(1)`。这里前面有提到过。

第二个：来看一个 hack 数据。

```
in:
5 4
1 2 3 4 5
1 4 
2 4
3 4
4 5
out:
3
```

然而这份代码会输出 $0$。原因在于，我们的 $2$ 和 $3$ 号点并没有入队，从而导致 $4$ 号点的 `indeg` 达不到 $0$，$4$ 号点也入不了队；而 $5$ 号点因此无法被更新答案，所以输出为 $0$。

如何解决呢，我们可以发现我们的需求是，导出一张 $1$ 为拓扑起点，$n$ 为拓扑终点，并且所有点都可以被正常入队的子图。实际上我们从 $1$ 开始跑一个 dfs 记录下哪些点被经过了，就可以知道哪些点可以正常入队了。然后，我们再去算每个点的 `indeg`，这样就是对的了。

复杂度是 $\Theta(n\alpha(n))$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define fs first
#define sc second

using namespace std;

const int maxn = 1e6 + 10;
typedef pair<int, int> pii;

int n, m, ans;
int a[maxn];
int fa[maxn];
pii e[maxn];
int cnt;
vector<int> g[maxn];
int indeg[maxn];
int f[maxn];

int find(int x) {
	return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);
}

int h[maxn];

void dfs(int u) {
	h[u] = 1;
	for (int v : g[u]) if (!h[v]) dfs(v);
}

signed main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i], fa[i] = i;
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		u = find(u), v = find(v);
		if (a[u] == a[v]) {
			if (u != v) fa[u] = v;
		} else {
			e[++cnt] = {u, v};
		}
	}
	for (int i = 1; i <= cnt; i++) {
		int u = e[i].fs, v = e[i].sc;
		u = find(u), v = find(v);
		if (a[u] > a[v]) swap(u, v);
		g[u].push_back(v);
	}
	dfs(find(1));
	for (int i = 1; i <= cnt; i++) {
		int u = e[i].fs, v = e[i].sc;
		u = find(u), v = find(v);
		if (a[u] > a[v]) swap(u, v);
		if (h[u] && h[v]) indeg[v]++;
	}
	queue<int> q;
	q.push(find(1));
	f[find(1)] = 1;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int v : g[u]) {
			f[v] = max(f[v], f[u] + 1);
			indeg[v]--;
			if (!indeg[v]) q.push(v);
		}
	}
	ans = f[find(n)];
	cout << ans << endl;
	return 0;
}

```

---

## 作者：_qingshu_ (赞：5)

真是神奇，赛时居然没有调出来...
# 题意：

给定一个无向图，求所有从点 $1$ 至点 $n$ 的简单且经过点权单调不降路径中经过的不同点权最大个数。

# 思路：

首先考虑精简图，对于 $a_u>a_v$ 的情况下，该边一定是无效的，所以我们考虑只往图中添加 $a_u\le a_v$ 的边，注意这是一个无向图，所以需要判断正反两次。

其次，普通的 dij 肯定是不行的，我们需要重新更改一下逻辑。

- 对于优先队列：

	考虑自己手写排序逻辑，如果说两者点权相同，那么优先选择从 $1$ 到该点路径上不同颜色更多的。否则选择点权更小的。不需要考虑对于后面的选择，我们排序逻辑仅仅为当前可能最优，如果不是会在后面更改回来的。又因为优先队列的优先级与写的是反的，需要注意一下。
    
- 对于跑图：
	明显的，如果遍历到的点 $v$ 的点权大于现在这个点 $x$，答案数会加一，所以我们当一下结果成立时会更新到这个点：
```cpp 
num[v]<num[x]+(a[x]<a[v])
```


最后的代码就很好构建了，比较板子的一道题。

# Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[5200010];
vector<int>e[5200010];
int num[5200010];
struct Node{
	int id,colorn;
	Node(int idin,int colorin):
		id(idin),colorn(colorin){};
	inline bool operator < (const Node in)const{
		return (a[id]==a[in.id]?colorn<in.colorn:a[id]>a[in.id]);
	}
};
priority_queue<Node>q;
inline void dij(){
	num[1]=1;
	q.push(Node(1,1));
	while(!q.empty()){
		auto x=q.top();
		q.pop();
		for(int v : e[x.id]){
			if(num[v]<num[x.id]+(a[x.id]<a[v])){
				num[v]=num[x.id]+(a[x.id]<a[v]);
				q.push(Node(v,num[v]));
			}
		}
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		if(a[u]<=a[v])e[u].emplace_back(v);
		if(a[v]<=a[u])e[v].emplace_back(u);
	}
	dij();
	cout<<num[n];
}
```

---

## 作者：CQ_Bob (赞：5)

好题。

有些翻译软件会把题意翻错，看英文题面就是了。

## 分析

对于最大价值，我们只需要考虑 $S$ 不减的价值最大，然后和 $0$ 取最大值。由于 $S$ 不减，图似乎可以转化成有向图然后拓扑。但是对于 $S_i=S_j$ 的情况，又似乎不行。

注意到如果我们在一个点权均为 $V$ 的环上走，只要走出这个环，就不会再回来了。所以我们完全可以把直接连接的价值相同的点缩成一个点，其连边就是所之前 $S_u\ne S_v$ 的边。

这样就可以直接拓扑了。用并查集把点缩在一起。令 $f_i$ 表示集合 $i$ 的答案，则有 $f_i = \max \{f_j+1|j \to i\}$。初始化除 $f_{s_1}$ 外均为极小值（$s_i$ 为 $i$ 所在集合）。

注：建边可能需要在缩点之后进行，不能有点向 $1$ 所在集合连边。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define PII pair<int,int>
#define x first
#define y second

il int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x*f;
}

const int N=2e5+10;
int n,m,val[N];
int ne[N],e[N],h[N],idx;
int fa[N],f[N];
struct edge{
	int x,y;
}E[N];
int d[N];

il void add(int a,int b){ne[++idx]=h[a],e[idx]=b,h[a]=idx;}
il int find(int x){return (fa[x]==x?x:fa[x]=find(fa[x]));}
il void topu(){
	queue<int> qu;
	for(re int i=1;i<=n;++i) f[i]=-1e18;
	f[find(1)]=1;
	for(re int i=1;i<=n;++i) if(find(i)==i&&!d[i]) qu.push(i);
	while(!qu.empty()){
		int now=qu.front();qu.pop();
		for(re int i=h[now];i;i=ne[i]){
			int j=e[i];--d[j];
			f[j]=max(f[j],f[now]+1);
			if(!d[j]) qu.push(j);
		}
	}
	return ;
}
il void solve(){
	n=read(),m=read();
	for(re int i=1;i<=n;++i) fa[i]=i,val[i]=read();
	for(re int i=1;i<=m;++i){
		E[i]={read(),read()};
		if(val[E[i].x]==val[E[i].y]) fa[find(E[i].x)]=find(E[i].y);
	}	
	for(re int i=1;i<=m;++i)
		if(val[E[i].x]>val[E[i].y]&&find(E[i].x)!=find(1)) add(find(E[i].y),find(E[i].x)),++d[find(E[i].x)];
		else if(val[E[i].x]<val[E[i].y]&&find(E[i].y)!=find(1)) add(find(E[i].x),find(E[i].y)),++d[find(E[i].y)];
	topu();
	printf("%lld\n",max(0ll,f[find(n)]));
	return ;
}

signed main(){
	solve();
	return 0;
}
```


---

## 作者：block_in_mc (赞：3)

## 题意简述

在一个连通的无向图中，第 $i$ 个点的点权为 $a_i$。求一条从 $1$ 到 $n$ 的简单路径，满足所经过的点点权单调不降，只需要输出这条路径经过了多少个点权不同的点。

特别地，如果不存在这样的路径，答案为 $0$。

## 解题思路

本篇题解使用**最短路**算法。

先考虑在 DAG 上如何解决此题。考虑使用拓扑排序进行 dp。对于边 $u\rightarrow v$，状态转移方程为：

$$dp_v=\begin{cases}\max\{dp_v,dp_u+1\}\ \ (a_v>a_u)\\\max\{dp_v,dp_u\}\ \ (a_v=a_u)\end{cases}$$

现在考虑在无向图上怎么进行这个过程。容易发现，问题的关键在于**枚举的顺序**。

考虑应该以什么样的顺序枚举每一个点。结论是：对于当前答案不为 $0$ 的点，优先按照点权从小到大枚举，如果点权相等，按照目前 $dp$ 值从大到小枚举。

先不严谨地考虑为什么这样做：优先用点权小的点更新点权大的点，否则点权大的点可能后来还会被点权小的点更新；点权相同时，优先选择目前 $dp$ 值更大的一个点，它更难被其它点更新。

这个过程可以使用堆优化的 Dijkstra 维护，具体细节可以看下面代码。

## 正确性证明

待更新。

~~赛时蒙了九发蒙出了正确答案~~。遗憾的是，我不确定这个算法是否正确。

如果有人能够提供此算法的正确性证明或一组 hack 数据，请私聊我。

按照目前的测试，点权相同时，优先选择目前 $dp$ 值更大的一个点是必要的。其它方式均无法通过此题。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 200100;
struct node {
    int id, v, r;
    bool operator< (const node & nd) const { 
        if (v != nd.v) return v > nd.v;
        return r < nd.r;
    }
};
vector<int> g[N];
int n, m, s, e, a[N], vis[N], res[N];
void dijkstra(int st) {
    priority_queue<node> q;
    res[st] = 1;
    q.push({st, a[st], 1});
    while (!q.empty()) {
        int p = q.top().id; q.pop();
        if (vis[p]) continue;
        vis[p] = 1;
        for (int ed : g[p]) {
            if (!vis[ed]) {
                if (a[ed] > a[p]) {
                    res[ed] = max(res[ed], res[p] + 1);
                    q.push({ed, a[ed], res[ed]});
                }
                if (a[ed] == a[p]) {
                    res[ed] = max(res[ed], res[p]);
                    q.push({ed, a[ed], res[ed]});
                }
            }
        }
    }
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &s, &e);
        g[s].push_back(e), g[e].push_back(s);
    }
    dijkstra(1);
    printf("%d", res[n]);
    return 0;
}
```

---

## 作者：LiJoQiao (赞：2)

[更好的阅读体验](https://www.cnblogs.com/LiJoQiao/p/17955920)

[洛谷题面](https://www.luogu.com.cn/problem/AT_abc335_e)

感觉有点毒瘤，不过还是有些 trick 在的。

题意翻译（复制于洛谷题面）：

> 给定一个 $N$ 个点 $M$ 条无向边的图，图上每个点都有其颜色。求所有经过点权单调不降的路径中，出现的不同颜色的个数最多是多少。

由于是单调不降的路径，所以可以点权大的点到点权小的点的路径对结果没有影响，可以当有向边连。  
点权相同且相连的点可以来回走，对结果没有影响，可以缩成一个点。

这样这张无向图就变成了由点权小的点到点权大的点的 DAG。

建图的时候把所有边先存起来，等用并查集将所有点缩成一个的时候再连边。

然后我们可以在这张图上来计 $1$ 到 $N$ 这条路径上不同颜色的个数。

有的题解里用了 Dijkstra 等算法，由于 DAG 的性质所以求解的本质一样，不再赘述。

由于是 DAG，所以可以跑拓扑排序，但是直接 dp 是不对的，有可能变为了以其他点为起点到 $N$ 的路径。

我们可以将其他点的 dp 值初始化为负无穷，然后 $1$ 点的 dp 值为 $1$，此时进行转移要么是 $1$ 到 $N$ 路径的值，要么是负无穷，进行一次判断即可。

代码如下。

```cpp
#include<bits/stdc++.h>
using namespace std;
template<typename T>
T read(){
    T f=1,x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+(ch^48);ch=getchar();}
    return f*x;
}
constexpr int MAXN=2e5+10,MAXM=2e5+10;
int n,m,a[MAXN],fa[MAXN],cnt,head[MAXN],tcnt,dp[MAXN],in[MAXN];
bool vis[MAXN];
struct EDGE1{
    int v,nxt;
}edge[MAXM];
struct EDGE2{
    int u,v;
}tedge[MAXM];
void add(int u,int v){
    edge[++cnt]={v,head[u]};
    head[u]=cnt;
    ++in[v];
}
namespace sol{
    int sget(int x){
        if(fa[x]==x)return x;
        else return fa[x]=sget(fa[x]);
    }
    void merge(int x,int y){
        fa[sget(y)]=sget(x);
    }
    void solve(){
        n=read<int>();m=read<int>();
        for(int i=1;i<=n;++i){
            a[i]=read<int>();
            fa[i]=i;
        }
        for(int i=1,u,v;i<=m;++i){
            u=read<int>();v=read<int>();
            if(a[u]==a[v])merge(u,v);
            else{
                if(a[u]>a[v])swap(u,v);
                //a[u]<a[v] 
                tedge[++tcnt]={u,v};
            }
        }
        for(int i=1;i<=tcnt;++i){
            add(sget(tedge[i].u),sget(tedge[i].v));
        }
        queue<int>q;
        for(int i=1;i<=n;++i){
        	if(!in[sget(i)]){
        		in[sget(i)]=1;
        		q.push(sget(i));
			}
		}
		memset(dp,0x80,sizeof(dp));
		dp[sget(1)]=1;
        while(!q.empty()){
        	int u=q.front();q.pop(); 
            for(int i=head[u];i;i=edge[i].nxt){
            	int v=edge[i].v;
            	dp[v]=max(dp[u]+1,dp[v]);
            	--in[v];
            	if(in[v]==0){
            		q.push(v);
				}
			}
        }
        printf("%d\n",max(dp[sget(n)],0));
    }
}
int main(){
    sol::solve();
    return 0;
}
```



---

## 作者：CQ_Bab (赞：1)

# 思路
其实挺简单的，就是我们可以发现对于一条边如果两边的 $a$ 不一样那么这条边是可以定向的然后我们就只需要考虑对于两边的 $a$ 相同的情况，如果相同那么我们可以发现其实可以缩成一个点（毕竟走了这么多个点也等于只走一个）。那么我们就可以萌生出一种想法，那就是对于每一条边如果点权不同则直接定向，否则建双向边然后再跑一遍缩点，最后从 $1$ 所在的连通块跑一便最长路即可。

这里我用的迪杰斯特拉。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
#define fire signed
#define kong putchar(' ')
#define end putchar('\n')
#define in(x) scanf("%lld",&x)
#define lcm(x,y) x*y/__gcd(x,y)
#define pb push_back
#define w(x)  while(x--)
#define il inline
il void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
int n,m;
int a[200100];
const int N=2e5+10;
vector<int>v[N];
int dfn[N],idx,low[N],is[N],tot,co[N];
stack<int>s;
void tarjan(int x) {
	dfn[x]=low[x]=++idx;
	is[x]=1;
	s.push(x);
	for(auto to:v[x]) {
		if(!dfn[to]) tarjan(to),low[x]=min(low[x],low[to]);
		else if(is[to]) low[x]=min(low[x],dfn[to]);
	}
	if(low[x]==dfn[x]) {
		tot++;
		int p;
		do{
			p=s.top();
			s.pop();
			is[p]=false;
			co[p]=tot;
		}while(p!=x);
	}
}
#define pa pair<int,int>
int dis[N];
struct node{
	int x,y;
}edg[N<<2];
int id,head[N];
void add(int x,int y) {
	edg[++id]={y,head[x]};
	head[x]=id;
}
void dij(int s) {
	priority_queue<pa>q;
	q.push({1,s});
	dis[s]=1;
	while(q.size()) {
		int x=q.top().second;
		q.pop();
		for(int i=head[x];i;i=edg[i].y) {
			int to=edg[i].x;
			if(dis[to]<dis[x]+1) {
				dis[to]=dis[x]+1;
				q.push({dis[to],to}) ;
			}
		}
	}
}
fire main() {
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	in(n),in(m);
	rep(i,1,n) in(a[i]);
	rep(i,1,m) {
		int x,y;
		in(x),in(y);
		if(a[x]<a[y]) v[x].pb(y);
		else if(a[x]>a[y]) v[y].pb(x);
		else v[x].pb(y),v[y].pb(x); 
	}
	rep(i,1,n) if(!dfn[i]) tarjan(i);
	rep(i,1,n) {
		for(auto to:v[i]) {
			if(co[i]!=co[to]) {
				add(co[i],co[to]);
			}
		}
	}
	dij(co[1]);
	cout<<dis[co[n]]<<endl;	
	return false;
}
```

---

## 作者：_shine_ (赞：1)

可以发现如果两点 $u,v$ 中 $a_u>a_v$，则从 $u$ 到 $v$ 的边无意义可以删掉，而从 $v$ 到 $u$ 的边可以加上。

定义 $f_j$ 表示为从 $1$ 出发经过点 $j$ 到达点 $n$ 的最大值，而这里可发现 $f_{j}$ 有 $2$ 种情况：

$\left\{\begin{matrix}f_{j}=f_{i}+1\left(a_i<a_j,f_i+1>f_j\right)\\f_{j}=f_{i}\left(a_i=a_j,f_i>f_j\right)\end{matrix}\right.$

这里 $i$ 表示的是任意一个与 $j$ 相连的边。

剩下的情况中 $f_{j}$ 不变，最终答案为 $f_n$。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
vector<int>e[maxn];
int n,m,a[maxn];
int dist[maxn];
bool vis[maxn];
void get_dfs(int u){
	vis[u]=1;
	for(int i=0;i<e[u].size();++i){int j=e[u][i];if(vis[j]==1)continue;
		if(a[u]<a[j] && dist[u]+1>dist[j])dist[j]=dist[u]+1,get_dfs(j);
		if(a[u]==a[j] && dist[u]>dist[j])dist[j]=dist[u],get_dfs(j);
	}
	vis[u]=0;
}
signed main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)scanf("%d",&a[i]);
	for(int i=1;i<=m;++i){int x,y;scanf("%d%d",&x,&y);if(a[x]<=a[y])e[x].push_back(y);if(a[y]<=a[x])e[y].push_back(x);}
	for(int i=1;i<=n;++i)sort(e[i].begin(),e[i].end(),[](int x,int y){return a[x]<a[y];});
	dist[1]=1;get_dfs(1);
	printf("%d\n",dist[n]);
	return 0;
}
```


---

## 作者：lfxxx (赞：1)

考虑把值相同且相连的点合并起来，那么不减就变成了严格递增。

然后把无向边按照权值小到大变有向边问题变成最长路，跑一遍 topo 即可。

由于是从 $1$ 开始所以建边算入度的时候要把从其出发不可抵达的点排除掉。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+114;
int a[maxn],n,m;
int In[maxn],use[maxn];
vector<int> edge[maxn],E[maxn];
int U[maxn],V[maxn];
int fa[maxn];
int found(int u){
    return fa[u]=(fa[u]==u?u:found(fa[u]));
}
void dfs(int u){
    use[u]=1;
    for(int v:edge[u]){
        if(use[v]==0) dfs(v);
    }
}
int dp[maxn];
void topo(){
    queue<int> q;
    dp[found(1)]=1;
    q.push(found(1));
    while(q.size()>0){
        int u=q.front();
        q.pop();
        for(int v:E[u]){
            dp[v]=max(dp[v],dp[u]+1);
            In[v]--;
            if(In[v]==0) q.push(v);
        }
    }
    return ;
}
void build(){
    dfs(found(1));
    for(int u=1;u<=n;u++){
        for(int v:edge[u]){
            if(use[u]==1&&use[v]==1) E[u].push_back(v),In[v]++;
        }
    }
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i],fa[i]=i;
    for(int i=1;i<=m;i++){
        cin>>U[i]>>V[i];
        if(a[found(U[i])]==a[found(V[i])]) fa[found(U[i])]=found(V[i]);
    }
    for(int i=1;i<=m;i++){
        int u=U[i],v=V[i];
        u=found(u),v=found(v);
        if(u==v) continue;
        if(a[u]>a[v]) swap(u,v);
        edge[u].push_back(v);
    }
    build();
    topo();
    cout<<dp[found(n)]<<' ';
    return 0;
}

```


---

## 作者：FReQuenter (赞：0)

考虑把所有联通的点权相同的点缩成一个点，并且将双向边改成从点权小的点往大的点连边。这样子就只需要对于新图求 $1$ 到 $n$ 的最长路径就可以了。这里给出一个拓扑排序的做法。

需要注意的是，拓扑排序求入度需要从点 $1$ 进行一遍搜索不然次序会错。缩完的新图记得判断重边和自环。不要使用spfa跑最短路求最长路径。新图 $1$ 和 $n$ 的编号不一定是 $1$ 和 $n$（两位数罚时人飘过/youl

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define int long long
#pragma GCC optimize(2,3,"inline","-Ofast")
using namespace std;
int n,m,ans,a[200005],o[200005],ind[200005],p[200005],dp[200005];
vector<int> gv[200005];
vector<pair<int,int>> v;
bool vis[200005];
int find(int x){
	if(x!=o[x]) o[x]=find(o[x]);
	return o[x];
}
void dfs(int now){
	for(auto nx:gv[now]){
		ind[nx]++;
		if(!vis[nx]){
			vis[nx]=1;
			dfs(nx);
		}
	}
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i],o[i]=i;
	map<pair<int,int>,bool> mp;
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		if(find(x)==find(y)) continue;
		if(mp[{x,y}]) continue;
		mp[{x,y}]=mp[{y,x}]=1;
		if(a[x]==a[y]&&find(x)!=find(y)) o[find(x)]=find(y);
		else if(a[x]!=a[y]){
			if(a[x]<a[y]) swap(x,y);
			v.push_back({y,x});
		}
	}
	mp.clear();
	for(auto nx:v){
		int u=find(nx.fi),v=find(nx.se);
		if(mp[{u,v}]||u==v) continue;
		mp[{u,v}]=mp[{v,u}]=1;
		gv[u].push_back(v);
	}
	for(int i=1;i<=n;i++){
		p[i]=find(i);
	}
	set<int> st;
	for(int i=1;i<=n;i++) st.insert(p[i]);
	dp[p[1]]=1;
	queue<int> q;
	vector<int> idx;
	for(auto nx:st) idx.push_back(nx);
	vis[p[1]]=1;
	dfs(p[1]);
	q.push(p[1]);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(auto nx:gv[u]){
			dp[nx]=max(dp[nx],dp[u]+1),ind[nx]--;
			if(ind[nx]==0) q.push(nx);
		}
	}
	cout<<dp[p[n]];
}
```

---

## 作者：SkyLines (赞：0)

## 题目分析

因为点权必须单调不降，所以只有 $a_u \le a_v$（$v$ 为 $u$ 的子节点）时，才能从 $u$ 跳到 $v$，如果 $a_u=a_v$，那就能从 $u$ 跳到 $v$，也能从 $v$ 跳到 $u$，是无意义的。可以将 $a$ 数组相等的点缩成一个点，最后统计答案即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int min_(int aa, int bb){
	return aa < bb ? aa : bb;
}
int max_(int aa, int bb){
	return aa > bb ? aa : bb;
}
int abs_(int aa){
	return aa > 0 ? aa : -aa;
}
int pow_(int aa, int bb, int cc){
    int ans = 1;
    while(bb){
        if(bb & 1) ans = ans * aa % cc;
        aa = aa * aa % cc;
        bb >>= 1;
    }
    return ans;
}
const int N = 2e5 + 5;
int n, m, a[N], ans[N], x, y, fa[N], vv, U, fu, su, fv;
vector<int> v[N];
struct node{
	int val, num;
	bool operator<(const node &aa){
		return val < aa.val;
	}
} tmp[N];
int find(int aa){
	if(!fa[aa]) return aa;
	return fa[aa] = find(fa[aa]);
}
void merge(int aa, int bb){
	if(find(aa) == find(bb)) return ;
	fa[find(aa)] = find(bb);
	return ;
}
int main(){
	for(int i = 0; i < N; i++) ans[i] = -1e9;
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++){
		scanf("%d", &tmp[i].val);
		tmp[i].num = i;
		a[i] = tmp[i].val;
	}
	for(int i = 1; i <= m; i++){
		scanf("%d %d", &x, &y);
		v[x].push_back(y);
		v[y].push_back(x);
		if(a[x] == a[y]) merge(x, y);
	}
	sort(tmp + 1, tmp + n + 1);
	ans[find(1)] = 1;
	for(int i = 1, j = 0; i <= n; i = j + 1){
		j = i;
		while(j + 1 <= n && tmp[j].val == tmp[j + 1].val) j++;
		for(int k = i; k <= j; k++){
			U = tmp[k].num;
			fu = find(U);
			if(ans[fu] == -1e9) continue;
			su = v[U].size();
			for(int ii = 0; ii < su; ii++){
				vv = v[U][ii];
				if(a[vv] <= a[U]) continue;
				fv = find(vv);
				ans[fv] = max_(ans[fv], ans[fu] + 1);
			}
		}
	}
	printf("%d", max_(0, ans[find(n)]));
	return 0;
}
```

---

## 作者：heyx0201 (赞：0)

# ABC335E Non-Decreasing Colorful Path 题解
## Des.
> 给定一个 $N$ 个结点 $M$ 条边的无向连通图，求出 $1$ 到 $N$ 中得分最高的点。
> 得分的定义：对于一条从 $1$ 到 $N$ 的简单路径：
> - 设 $S$ 是写在路径沿线顶点上的按照顶点被访问的顺序排列的整数序列。
> - 若 $S$ 不是非递减的，那么得分为 $0$。
> - 否则，得分为 $S$ 中不同的整数的个数。

## Sol.
求 $S$ 中不同的整数的个数，那么可以把多个相同点权的点合并，方便求答案。

具体思路：首先对每个连通块进行区分，然后记录下每个连通块的点权，再在连通块之间按照拓扑序从小到大建图，最后就是按拓扑序从小到大 `dp`，状态是 $dp_v = \max \{ dp_v, dp_u+1 \}$。

更具体的我会在代码中添加注释。

## Cod.
```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 10;

int n, m, a[MAXN], cnt, x[MAXN], id[MAXN], dp[MAXN];
int vis[MAXN];
vector<int> g[MAXN], connect[MAXN];

void dfs(int u) {
  if (vis[u]) {
    return;
  }
  vis[u] = cnt; // 记录连通块的编号，以便区分
  for (int v : g[u]) {
    if (a[v] == a[u]) { // 连通块
      dfs(v);
    }
  }
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1, u, v; i <= m; i++) {
    cin >> u >> v;
    g[u].push_back(v), g[v].push_back(u);
  }
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
      x[++cnt] = a[i]; // 记录点权
      dfs(i);
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j : g[i]) {
      // 拓扑序建图
      if (x[vis[i]] < x[vis[j]]) {
        connect[vis[i]].push_back(vis[j]);
      }
    }
  }
  fill(dp + 2, dp + cnt + 1, -1e9); // 初始化 dp 数组
  for (int i = 1; i <= cnt; i++) {
    id[i] = i;
  } // 初始化 id
  sort(id + 1, id + cnt + 1, [](const int &i, const int &j) {
    return x[i] < x[j];
  }); // 按照 x 从小到大排序
  for (int i = 1; i <= cnt; i++) {
    int u = id[i];
    for (int v : connect[u]) {
      dp[v] = max(dp[v], dp[u] + 1); // dp
    }
  }
  cout << max(dp[vis[n]] + 1 /* 对于连通块来说的路径长度，本题不关注路径长度，只求得分 */, 0 /* 如果状态没有求解过，也就是 1-n 没有简单路径相连，就为 0 */);
  return 0;
}
```

---

## 作者：yanhao40340 (赞：0)

## 题意

$n$ 个点，$m$ 条边的无向图，每个点有点权 $a_i$。

一条路径经过点的点权序列如果单调不降，那么该路径的权值为序列中不同数的个数。否则权值为 $0$。

求从 $1$ 到 $n$ 的所有简单路径中，权值最大的为多少。

数据范围：$n,m,a_i \le 2\times 10^5$。

## 分析

先不考虑原题。

如果这是一张 DAG，那么可以将点权从小到大排序，逐个更新答案。时间复杂度 $\Theta(n \log n + m)$。

回到原题。考虑将原图变成一个 DAG。

设一条**无向边**连接 $u$ 和 $v$ 两个顶点。

如果 $a_u \ne a_v$，那么将其替换成从小的一端到大的一端的**有向边**一定不会更劣。

如果 $a_u = a_v$，那么可以将 $u$ 和 $v$ 并为一个点。可以使用并查集维护。

至此，我们已经将原图变成了一个 DAG，所以就做完了。

时间复杂度 $\Theta(n \log n + m)$。瓶颈在排序。

## 代码

赛时代码。省略快读快输等缺省源。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int maxn=2e5+5;
int a[maxn],b[maxn],f[maxn],fa[maxn];
int findfa(int x){
	return (x==fa[x]?x:fa[x]=findfa(fa[x]));
}
vector<int> g[maxn],mp[maxn];
bool vis[maxn];
bool cmp(int p,int q){
	return a[fa[p]]<a[fa[q]];
}
int main(){
	int n=read(),m=read();
	for (int i=1;i<=n;++i) a[i]=read(),b[i]=i,fa[i]=i;
	for (int i=1;i<=m;++i){
		int u=read(),v=read();
		if (a[u]>a[v]) g[u].push_back(v);
		if (a[v]>a[u]) g[v].push_back(u);
		if (a[u]==a[v]){
			int fax=findfa(u),fay=findfa(v);
			if (fax^fay) fa[fax]=fay;
		}
	}
    for (int i=1;i<=n;++i) fa[i]=findfa(i);
	for (int i=1;i<=n;++i){
		mp[fa[i]].push_back(i);
	}
	stable_sort(b+1,b+n+1,cmp);
	f[fa[1]]=1;vis[fa[1]]=true;
	for (int i=1;i<=n;++i){
		int cur=fa[b[i]];
        if (a[cur]<=a[fa[1]]) continue;
        if (!vis[cur]) vis[cur]=true;
        else continue;
		for (int it:mp[cur]){
			for (int j:g[it]){
                if (f[fa[j]]==0) continue;
				f[cur]=max(f[cur],f[fa[j]]+1);
			}
		}
	}
	write(f[fa[n]]);
	return 0;
}
```

---

## 作者：FL_sleake (赞：0)

### 题意简述

给定一个 $n$ 个点 $m$ 条边的无向图，每个点有一个点权 $a_i$。对于每条从 $1$ 到 $n$ 的简单路径，路径的美丽值定义如下：

令序列 $s$ 为按顺序走过的点的点权构成的序列。若 $s$ 不是单调不下降序列，该路径美丽值为 $0$。否则，该路径美丽值为 $s$ 中不同元素的个数。

输出 $1$ 到 $n$ 的简单路径中美丽值最大为多少。

### 解题思路

首先按照点权排序。排序完之后，对于第 $i$ 个点，我们只需要从它前面找小于它的点转移。但是我们不太好处理点权相同的点。如何解决？当点权为 $x$ 的点全部转移完之后，再 dfs 跑一遍点权为 $x$ 的点，取其中的最大值进行转移即可。总的时间复杂度应该是 $\Theta(n)$，但是常数较大。

### 代码示例

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,dp[200010],num=0,vis[200010]={0},b[200010];
struct node{
	int u,num;
	bool operator<(const node &b)const{
		return num<b.num;
	}
}a[200010];
vector<int> G[200010];
set<int> s;
void dfs(int x){
	s.insert(x);
    //将遍历的点存进来
	num=max(num,dp[x]);
    //取最大值
	vis[x]=1;
	for(int v:G[x]) if(!vis[v]&&b[v]==b[x]) dfs(v);
    //注意，只扫和当前点点权相同的点
}
signed main(){
	memset(dp,-0x3f,sizeof(dp));
    //初始化不能为0，否则转移会出问题
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i].num,a[i].u=i,b[i]=a[i].num;
    //b数组存储了每个点的点权
    //因为a数组排序后会打乱，所以b数组方便后续使用
	sort(a+1,a+n+1);
    //按点权排序
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dp[1]=1;
    //1号点出发
	for(int i=1;i<=n;i++){
		for(int v:G[a[i].u]){
			if(a[i].num>b[v]) dp[a[i].u]=max(dp[a[i].u],dp[v]+1);
			if(a[i].num==b[v]) dp[a[i].u]=max(dp[a[i].u],dp[v]);	
		}
        //扫一遍跟它相邻的点，进行更新
		if(a[i].num!=a[i+1].num||i==n){
        //如果当前点的点权和下一个点不同，说明点权和当前点点权相同的点全部更新完毕
        //可以进行一次总转移了
			int j=i;
			while(a[j].num==a[i].num&&j>=1){
            //扫所有的点权和当前点相同的点
				if(!vis[a[j].u]){
					s.clear();
					num=-0x3f3f3f3f3f3f3f3f;
					dfs(a[j].u);
                    //找其中的最大值
					for(int v:s) dp[v]=num;
                    //赋值
				}
				j--;
			}
		}
	}
	cout<<(dp[n]<0?0:dp[n])<<endl;
	return 0;
}
```

---

## 作者：_Z_F_R_ (赞：0)

个人觉得考虑的点较多。

显然的，若有多个点数值相同且连通，那么可以将其缩成一个点。缩点后，若只保留从小值到导致的单项边，那么该图为 DAG。

然后就可以 DP 了，显然转移方程为 $f_v = \max\{f_u + 1\}$，其中 $u$ 表示存在有向边从 $u$ 到 $v$。

注意：
- DP 中所有的点必须是并查集合并后留下的新点；（~~不会就我赛时 WA 了吧 QwQ~~）
- 要把 $a_i < a_1$ 或 $a_i > a_n$ 的所有结点 $i$ 删去，否则会导致 $1$ 和 $n$ 不是起终点，影响 DP；
- 对于初始 $1$ 结点合并后所在新点 $st$，$f_{st} \gets 1$，对于初始 $n$ 结点合并后所在新点 $fi$，$f_{fi} \gets 0$，其余 $f_i$ 赋值为负无穷即可；

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 200005;
int n, m, a[N];
struct Edge {
	int to, nxt;
}e[N << 1];
ll f[N];
int cntedge, head[N], id[N];
void Add_Edge(int u, int v) { // 链式前向星
	e[++cntedge].to = v;
	e[cntedge].nxt = head[u];
	head[u] = cntedge;
}
struct DSU { // 并查集
	int fa[N];
	void Init(int n) {
		int i;
		for(i = 1; i <= n; i++)
			fa[i] = i;
	}
	int Find_Root(int x) {
		return (fa[x] == x)?x:(fa[x] = Find_Root(fa[x]));
	}
	void Join(int x, int y) {
		int rx = Find_Root(x), ry = Find_Root(y);
		fa[rx] = ry;
	}
}dsu;

int main() {
	int i;
	scanf("%d%d", &n, &m);
	for(i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	dsu.Init(n);
	vector<pair<int, int> > vec;
	for(i = 1; i <= m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		if(a[u] == a[v]) {
			dsu.Join(u, v); // 合并点
		}
		else {
			if(a[u] < a[1] || a[u] > a[n] || a[v] < a[1] || a[v] > a[n]) { // 断边，这样后期会自动忽略该点
				continue;
			}
			vec.push_back(make_pair(u, v));
		}
	}
	for(auto p : vec) {
		int u = dsu.Find_Root(p.first), v = dsu.Find_Root(p.second);
		if(a[u] < a[v]) {
			Add_Edge(u, v), id[v]++;
		}
		else {
			Add_Edge(v, u), id[u]++;
		}
//		printf("%d %d\n", u, v);
	}
	queue<int> q;
	for(i = 1; i <= n; i++) {
		if(dsu.Find_Root(i) != i) {
			continue;
		}
		if(!id[i]) {
			q.push(i);
		}
		if(dsu.Find_Root(1) == i) {
			f[i] = 1;
		}
		else if(dsu.Find_Root(n) == i) {
			f[i] = 0;
		}
		else {
			f[i] = -1e15;
		}
	}
	while(!q.empty()) { // 拓补 + DP
		int top = q.front();
		q.pop();
//		cout << top << ' ' << f[top] << endl;
		for(i = head[top]; i; i = e[i].nxt) {
			int v = e[i].to;
			id[v]--;
			f[v] = max(f[v], f[top] + 1);
			if(!id[v]) {
				q.push(v);
			}
		} 
	}
	printf("%lld", f[dsu.Find_Root(n)]);
	return 0;
}
```

---

## 作者：what_can_I_do (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc335_e)

首先先把无向图转化成有向图。设每一个点的权值为 $w_i$，那么若 $w_u\ge w_v$，则连一条从 $u$ 到 $v$ 的边。若 $w_u\le w_v$，则连一条从 $v$ 到 $u$ 的边，这样可以直接使路径满足点权单调不降。

接下来缩点把环缩成点。明显的，一个环的形成只能是这个环里所有点权相同，所以我们就可以直接处理掉点权相同且相连的点。

最后跑记忆化搜索就行，由于点权单调不降，所以不会在新的图中的任意路径中遇到点权相同的两个点。

# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int w[200010];
vector<int> g[200010],rg[200010];
int dfn[200010],low[200010],tot=0;
int z[200010],top=0;
bool vis[200010];
int dy[200010];
int sum=0;
int st,ed;
int dp[200010]; 
inline void tarjan(int k)
{
	tot++,dfn[k]=low[k]=tot,top++,z[top]=k,vis[k]=1;
	for(register int i=0;i<g[k].size();i++)
	{
		int x=g[k][i];
		if(!dfn[x]) tarjan(x),low[k]=min(low[k],low[x]);
		else if(vis[x]) low[k]=min(low[k],dfn[x]);
	}
	if(low[k]==dfn[k])
	{
		sum++;
		while(1)
		{
			int x=z[top];
			top--,dy[x]=sum,vis[x]=0;
			if(x==k) break;
		}
	}
}
inline int dfs(int k)
{
	if(dp[k]!=-999999999) return dp[k];
	if(k==ed)
	{
		dp[k]=1;
		return 1;
	}
	vis[k]=1;
	for(register int i=0;i<rg[k].size();i++)
	{
		int x=rg[k][i];
		if(vis[x]) continue;
		dp[k]=max(dp[k],dfs(x)+1);
	}
	vis[k]=0;
	return dp[k];
}
int main()
{
	scanf("%d%d",&n,&m);
	for(register int i=1;i<=n;i++) scanf("%d",&w[i]);
	for(register int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		if(w[u]<=w[v]) g[u].push_back(v);
		if(w[v]<=w[u]) g[v].push_back(u);
	}
	for(register int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
	for(register int i=1;i<=n;i++)
		for(register int j=0;j<g[i].size();j++)
		{
			int x=dy[i],y=dy[g[i][j]];
			if(x==y) continue;
			rg[x].push_back(y);
		}
	for(register int i=1;i<=sum;i++) dp[i]=-999999999;
	st=dy[1],ed=dy[n],dfs(st);
	if(dp[st]<1) printf("0");
	else printf("%d",dp[st]);
	return 0;
}
```

---

## 作者：lhc0707 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc335_e)

### 题解

原来的图较为复杂，不方便操作，考虑把原图精简成 DAG。

首先，因为路径上的点权必须单调不降，所以所有从点权大的点向点权小的点连的边都是无用的，直接在输入的时候处理掉就可以。然后考虑到在一坨相邻的点权相同的点之间来回跳是没有意义的，因此可以用并查集把这些点缩成一个点，显然缩点之后每条单调不降路径上都不可能出现两个点权相同的点。最后，这个图被我们缩成了 DAG，DFS 统计答案即可。

### 代码

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
using namespace std;
inline void read(int &x){
    x=0;bool f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f^=1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    x=(f?x:-x);
}
void write(int x){if(x<10){putchar(x+'0');return;}write(x/10);putchar(x%10+'0');}
void print(int x,char c){if(x<0){putchar('-');x=-x;}write(x);putchar(c);}
const int N=200005;
int n,m,a[N],fa[N],d[N],siz[N];
vector< pair<int,int> > e;
vector<int> G[N];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void merge(int u,int v)
{
	u=find(u),v=find(v);
	if(u!=v)
	{
		if(siz[u]<siz[v])swap(u,v);
		siz[u]+=siz[v];
		fa[v]=u;
	}
}
int calc(int u)
{
	if(d[u]!=-1e9)return d[u];
	for(int v:G[u])d[u]=max(d[u],calc(v)+1);
	return d[u];
}
int main()
{
    read(n),read(m);
    for(int i=1;i<=n;i++)read(a[i]),fa[i]=i,siz[i]=1;
    for(int i=1;i<=m;i++)
    {
        int u,v;read(u),read(v);
        e.push_back(make_pair(u,v));
        if(a[u]==a[v])merge(u,v);
    }
    for(auto edge:e)
    {
        int u=edge.first,v=edge.second;
        u=find(u),v=find(v);
        if(u==v)continue;
        if(a[u]>a[v])swap(u,v);
        G[u].push_back(v);
    }
    for(int i=1;i<=n;i++)d[i]=-1e9;
    d[find(n)]=1;
    print(max(0,calc(find(1))),'\n');
    return 0;
}
```

---

