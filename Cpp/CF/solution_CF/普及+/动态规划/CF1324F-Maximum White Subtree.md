# Maximum White Subtree

## 题目描述

You are given a tree consisting of $ n $ vertices. A tree is a connected undirected graph with $ n-1 $ edges. Each vertex $ v $ of this tree has a color assigned to it ( $ a_v = 1 $ if the vertex $ v $ is white and $ 0 $ if the vertex $ v $ is black).

You have to solve the following problem for each vertex $ v $ : what is the maximum difference between the number of white and the number of black vertices you can obtain if you choose some subtree of the given tree that contains the vertex $ v $ ? The subtree of the tree is the connected subgraph of the given tree. More formally, if you choose the subtree that contains $ cnt_w $ white vertices and $ cnt_b $ black vertices, you have to maximize $ cnt_w - cnt_b $ .

## 说明/提示

The first example is shown below:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1324F/e1f60f9681db9f4f9199c7a23c4eb447ad36532b.png)

The black vertices have bold borders.

In the second example, the best subtree for vertices $ 2, 3 $ and $ 4 $ are vertices $ 2, 3 $ and $ 4 $ correspondingly. And the best subtree for the vertex $ 1 $ is the subtree consisting of vertices $ 1 $ and $ 3 $ .

## 样例 #1

### 输入

```
9
0 1 1 1 0 0 0 0 1
1 2
1 3
3 4
3 5
2 6
4 7
6 8
5 9```

### 输出

```
2 2 2 2 2 1 1 0 2```

## 样例 #2

### 输入

```
4
0 0 1 0
1 2
1 3
1 4```

### 输出

```
0 -1 1 -1```

# 题解

## 作者：WYXkk (赞：19)

upd：修改了一处笔误，请管理员重新审核。感谢[dezhonger](https://www.luogu.com.cn/user/200037)指出。

题目大意：给定一棵**无根**树，每个点都是黑色或白色，设一棵子树的权值是其中白点的个数减去其中黑点的个数，对于每个点，求出包含它的所有子树中权值的最大值。$n\le 2\times10^5$。

解析：思博 tree dp+换根 dp。

若一个点 $i$ 为白色，则令 $col_i=1$，否则令 $col_i=-1$。

我们首先钦定 $1$ 为根，然后假设 $dp_i$ 是以 $i$ 为根的子树的答案，则显然

$$dp_i=col_i+\sum\limits_{v\in son_j}\max(0,dp_j)$$

这第一部分是很显然的。

之后，我们就要换根 dp 了，假设 $dp^\prime_i$ 表示 $i$ 为根的答案，若 $i\neq 1$ 则

$$dp^\prime_i=\max(0,dp^\prime_f-\max(0,dp_i))+dp_i$$

其中 $f$ 表示 $1$ 为根时 $i$ 的父亲，即将父亲的答案消去自身影响后当成自己的子树。

于是 dfs 两遍即可。注意 dp 的顺序，一个是从叶到根，一个是从根到叶。

$\texttt{code:}$

```cpp
#include<cstdio>
#include<iostream>
#include<fstream>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
#define Set(a) memset(a,0,sizeof(a))
#define F(i,a,b) for(register int i=a,i##end=b;i<=i##end;++i)
#define UF(i,a,b) for(register int i=a,i##end=b;i>=i##end;--i)
#define openf(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
#define re register
#define ri re int
#define il inline
typedef long long ll;
typedef unsigned long long ull;
template<typename T> inline T rd(T& x)
{
	T f=1;x=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(; isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(T)(c-'0');
	x*=f;
	return x;
}
ll rd(){ll x;rd(x);return x;}
inline int max(int a,int b){return a>b?a:b;}
inline int min(int a,int b){return a<b?a:b;}
const int inf=1<<30;

const int N=200005;
int col[N],dp[N],dp2[N];
int head[N],to[N<<1],nxt[N<<1],tot=0;void add(int u,int v){to[++tot]=v;nxt[tot]=head[u];head[u]=tot;}
void dfs1(int u,int f)
{
	dp[u]=col[u];
	for(ri i=head[u];i;i=nxt[i]) if(to[i]!=f) {dfs1(to[i],u);dp[u]+=max(0,dp[to[i]]);}
}
void dfs2(int u,int f)
{
	if(u!=1) dp2[u]=max(dp2[f]-max(0,dp[u]),0)+dp[u];
	for(ri i=head[u];i;i=nxt[i]) if(to[i]!=f) dfs2(to[i],u);
}
int main()
{
	int n=rd();
	F(i,1,n) col[i]=2*rd()-1;
	F(i,1,n-1) {int u,v;rd(u);rd(v);add(u,v);add(v,u);}
	dfs1(1,0);dp2[1]=dp[1];dfs2(1,0);
	F(i,1,n) printf("%d ",dp2[i]);
	return 0;
}
```



---

## 作者：F_Mu (赞：16)

**题意**

给定一棵$n$个节点的无根树，每个节点为黑色或者白色，每个点的答案为包含该点的子树（指无根子树）的白色节点数减黑色节点数的最大值

**分析**

对于无根树的题一般指定某一个点为根，不妨设为$1$

我们发现对于$1$号节点，他的某棵子树（将$1$视为根）如果白色节点数大于黑色节点数，则他的答案加上该差值

我们先采用树形$DP$将所有节点都这样统计一遍，这样就获得了来自子树的贡献

即$a[i]$为以$i$为根，所有白色节点数大于黑色节点数的子树的贡献

然后对于除$1$节点以外所有节点，还需要统计与父亲这一棵无向子树的关系

设遍历到$now$节点，子树节点为$to$节点

+ $a[to]>0$，则$now$的答案子树包括$to$节点，$to$节点选择$now$的答案子树和$to$的答案子树中的最大值（因为已经包括，所以不是加和）
  $$
  a[to] = max(a[to], a[now])
  $$

+ $a[to]\leq0$，则$now$的答案子树不包括$to$节点，$to$节点选择与$now$的答案子树进行拼接或不拼接的最大值（因为不包括，所以是加和）
  $$
  a[to] = max(a[to], a[now] + a[to])
  $$
  

```cpp
#pragma GCC optimize(3, "Ofast", "inline")

#include <bits/stdc++.h>

#define start ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define ll long long
#define int ll
#define ls st<<1
#define rs st<<1|1
#define pii pair<int,int>
using namespace std;
const int maxn = (ll) 3e5 + 5;
const int mod = 1000000007;
const int inf = 0x3f3f3f3f;
vector<int> v[maxn];
int a[maxn];

void dfs(int now, int pre) {
    for (auto &to:v[now]) {
        if (to == pre)
            continue;
        dfs(to, now);
        if (a[to] > 0)
            a[now] += a[to];
    }
}

void dfs2(int now, int pre) {
    for (auto &to:v[now]) {
        if (to == pre)
            continue;
        if (a[to] > 0)
            a[to] = max(a[to], a[now]);
        else
            a[to] = max(a[to], a[now] + a[to]);
        dfs2(to, now);
    }
}

signed main() {
    start;
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (a[i] == 0)
            a[i] = -1;
    }
    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    dfs(1, 0);
    dfs2(1, 0);
    for (int i = 1; i <= n; ++i)
        cout << a[i] << ' ';
    return 0;
}
```

---

## 作者：一扶苏一 (赞：14)

# 【DP】 CF1324F Maximum White Subtree

## Description

- 给定一棵 $n$ 个节点无根树，每个节点 $u$ 有一个颜色 $a_u$，若 $a_u$ 为 $0$ 则 $u$ 是黑点，若 $a_u$ 为 $1$ 则 $u$ 是白点。
- 对于每个节点 $u$，选出一个**包含** $u$ 的连通子图，设子图中白点个数为 $cnt_1$，黑点个数为 $cnt_2$，请最大化 $cnt_1 - cnt_2$。并输出这个值。
- $1 \leq n \leq 2 \times 10^5$，$0 \leq a_u \leq 1$。

## Solution

首先不妨钦定 $1$ 是这棵树的根。

我们考虑过一个点 $u$ 的连通块可以被分为两部分，第一部分是以 $u$ 为根的子树内的部分，第二部分是 $u$ 为根的子树外的部分。如果能分别计算出这两部分的最大值，显然将他们加起来就是 $u$ 所在连通块的最大值。

首先考虑第一部分的计算，是一个基础的树形 dp，设 $f_u$ 是考虑以 $u$ 为根的子树，$u$ 所在的连通块的最大值。转移为

$$f_u = \operatorname{colour}_u + \sum\limits_{v \in \operatorname{Subtree}(u)} \max(f_v, 0)$$

其中若 $a_u = 1$，则 $\operatorname{colour}_u = 1$，否则 $\operatorname{colour}_u = -1$。

即枚举 $u$ 的每个子节点 $v$，若 $f_v$ 大于 $0$，则将 $v$ 子树内的连通块与 $u$ 联通。

考虑第二部分的计算，也是一个树形 dp。设 $g_u$ 是整张图去掉以 $u$ 为根的子树，但保留点 $u$ 以后构成的图中，$u$ 所在的连通块的最大值。形象地说，$g_u$ 所代表的连通块要么只有 $u$ 一个节点，要么与 $u$ 直接相连的只有 $u$ 的父亲一个节点。

设 $u$ 的父亲为 $p$，$u$ 的转移一定来自 $g_p$ 和 $u$ 的兄弟节点的子树。即

$$g_u = \operatorname{colour}_u + \max(0, g_p + \sum\limits_{v \in \operatorname{Subtree}(p)}^{v \neq u} \max(f_v,0 ))$$

显然这个 dp 是 $O(n^2)$ 的，我们考虑优化。

注意到 $g_u$ 的最后一个 $\Sigma$ 长得很像 $f_p$ 的计算过程，我们考虑用 $f_p$ 来表示这个式子。

由于

$$f_p = \operatorname{colour}_p + \sum\limits_{v \in \operatorname{Subtree}(p)} \max(f_v, 0)$$

所以

$$\sum\limits_{v \in \operatorname{Subtree}(p)}^{v \neq u} \max(f_v,0 )) = f_p - \max(0, f_u) - \operatorname{colour}_p$$

因此

$$g_u = \operatorname{colour}_u + \max(0, g_p + f_p - \max(0, f_u) - \operatorname{colour}_p)$$

这样就可以 $O(n)$ 计算 $g$ 了。

最后考虑统计答案，我们注意到 $\operatorname{color}_u$ 被算了两遍，所以要在 $g_u$ 中减去一遍。当然，去掉 $\operatorname{color}_u$ 以后，$g_u$ 也可以整个不选。因此

$$ans_u = f_u + \max(0, g_u - \operatorname{colour}_u)$$

做两次 dfs 即可，总时间复杂度 $O(n)$。

## Code

```cpp
const int maxn = 200005;

int n;
int a[maxn], fa[maxn], f[maxn], g[maxn], ans[maxn], h[maxn];
std::vector<int> e[maxn];

void dfs(const int u);
void dfs(const int u, const int ff);

int main() {
  freopen("1.in", "r", stdin);
  qr(n);
  for (int i = 1; i <= n; ++i) {
    qr(a[i]);
  }
  for (int i = 1, u, v; i < n; ++i) {
    u = v = 0; qr(u); qr(v);
    e[u].push_back(v);
    e[v].push_back(u);
  }
  dfs(1, 0);
  g[1] = a[1] ? 1 : -1;
  ans[1] = f[1];
  for (auto u : e[1]) {
    dfs(u);
  }
  for (int i = 1; i <= n; ++i) {
    qw(ans[i], i == n ? '\n' : ' ', true);
  }
  return 0;
}

void dfs(const int u, const int p) {
  fa[u] = p;
  f[u] = a[u] ? 1 : -1;
  for (auto v : e[u]) if (v != p) {
    dfs(v, u);
    if (f[v] > 0) f[u] += f[v];
  }
}

void dfs(const int u) {
  int p = fa[u], tt = g[p] + f[p] - (a[p] ? 1 : -1);
  if (f[u] > 0) tt -= f[u];
  if (tt < 0) tt = 0;
  ans[u] = f[u] + tt;
  g[u] = tt + (a[u] ? 1 : -1);
  for (auto v : e[u]) if (v != fa[u]) {
    dfs(v);
  }
}
```



---

## 作者：KJGKMTZB (赞：7)

换根$dp$入门题，并且水的一批，是连我这种弱智都想得出来的$dp$

首先看题我们可以很容易想到以每个点为根来求出答案的$O(n^2)$做法，那么这时，相信只要是一个知道换根$dp$的人都不难看出此题算法了

首先，给每个黑点赋权值为-1，白点为1，那么$cnt_w-cnt_b$就相当于权值和

我们考虑先进行一次$dfs$，求出每个点在其子树内的答案，设$f[x]$为以x为根的子树的答案

不难得到，${\sum_{v∈x}^{}}max(0,f[v])$ 

接下来，进行第二次$dfs$，对于一个点$x$与它的父亲$fa$，设这个点的答案为$g[x]$

考虑子树内，则$g[x]+=f[x]$

接下来考虑子树外，考虑父亲可以选或者不选，由前面$f$的转移方程可知，如果$f[x]>0$，它必定已经被算进了它的父亲的答案中，则很容易得到$g[x]+=max(0,g[fa]-max(0,f[x]))$

$Code$

```
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <cstdio>
#include <algorithm>
#include <cstring>
#define inf 0x3f3f3f3f
#define rep(a,b,c) for(int a=b;a<=c;a++)
#define per(a,b,c) for(int a=b;a>=c;a--)
const int mod=1e9+7;
const int maxn=2e5+5;
template<class T>inline void read(T &x) {
	T f=1;x=0;char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=(x<<1)+(x<<3)+(s&15);s=getchar();}
	x*=f;
}
template<class T>inline T min(T a,T b) { return a<b?a:b; }
template<class T>inline T max(T a,T b) { return a>b?a:b; }
template<class T>inline T fabs(T a) { return a>0?a:-a; }
struct Edge {
	int u,v;
}e[maxn<<1];
int head[maxn],ecnt;
inline void addedge(int u,int v) { e[++ecnt].v=v;e[ecnt].u=head[u];head[u]=ecnt; }
inline void add(int u,int v) { addedge(u,v); addedge(v,u); }
int f[maxn],g[maxn],v,val[maxn],c[maxn],n,a,b;
inline void dfs1(int x,int fa) {
	f[x]=val[x];
	for(int i=head[x];i;i=e[i].u) {
		if(e[i].v==fa) continue;
		dfs1(e[i].v,x);
		f[x]+=max(f[e[i].v],0);
	}
}
inline void dfs2(int x,int fa) {
	g[x]=f[x];
	g[x]+=max(0,g[fa]-max(f[x],0));
	for(int i=head[x];i;i=e[i].u) {
		if(e[i].v==fa) continue;
		dfs2(e[i].v,x);
	}
}
signed main() {
	read(n);
	rep(i,1,n) read(c[i]),val[i]=(c[i]==0)?-1:1;
	rep(i,1,n-1) read(a),read(b),add(a,b);
	dfs1(1,0);
	//rep(i,1,n) printf("%d %d\n",i,f[i]);
	dfs2(1,0);
	rep(i,1,n) printf("%d ",g[i]);
}
```

---

## 作者：devout (赞：2)

[博客内食用更佳](https://blog.csdn.net/devout_/article/details/104858457)

开始想复杂了，一直在往树剖上想，而且一想就刹不住了

后来感觉像个树形dp，但是T5刚考了dp，T6接着考，不可能吧（flag）

经过了半个小时花在树剖上，突然猛然发现，这是div3的比赛诶，可能考树剖吗？

于是就往傻了想

还是考虑树形DP吧

先随便指定一个根1

我们处理出$f_u$表示以$u$为根节点的子树中，最大的差值，转移其实挺简单的
$$f_u=color_u$$
$$f_u=\sum_{v}^{v\in son_u,f_v>0} f_v$$
然后怎么做呢？

抛开一切数据结构

我们考虑我们DP怎么转移过来的，然后逆着推一下就好了

首先，$ans_1$就是$f_1$

然后我们向下dfs，对于一个点，他有可能有两种情况

1.他爸爸的答案里面包括了他的子树($f_u>0$)

2.他爸爸的答案中没有包括他的子树($f_u\leq 0$)

那么对于第一种情况，有可能是

1.就是他爸爸的答案

2.$f_u$

为什么会有第二种情况呢？比如说他爸爸是-1，那么显然这个点的答案要他爸爸就没有用了（详见样例2）

对于第二种情况，类比第一种情况，答案就是

1.他爸爸的答案-1（因为进入第二种情况的显然这个点是黑点）

2.-1
然后我们一直往下递推就可以啦


经过wa了两次，压哨A了

```cpp
#include <bits/stdc++.h>
using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

typedef long long ll;

const int N=2e5+5;

template<typename T> void read(T &x){
   x=0;int f=1;
   char c=getchar();
   for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
   for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
    x*=f;
}

int n;
int col[N];
int f[N],sum[N],out[N];
int head[N],cnt;

struct Edge{
    int to,next;
}e[N<<1];

void add(int x,int y){
    e[++cnt]=(Edge){y,head[x]},head[x]=cnt;
}

void dfs1(int u,int fa){
    sum[u]=sum[fa]+col[u];
    f[u]=col[u];
    RepG(i,u){
        int v=e[i].to;
        if(v==fa)continue;
        dfs1(v,u);
        if(f[v]>0)f[u]+=f[v];
    }
    // f[u]=max(f[u],0);
}

void dfs2(int u,int fa){
    if(f[u]>0){
        out[u]=max(out[fa],f[u]);
    }
    else {
        out[u]=max(out[fa]+col[u],col[u]);
        RepG(i,u){
            int v=e[i].to;
            if(v==fa)continue;
            if(f[v]>0)out[u]+=f[v];
        }
    }
    RepG(i,u){
        int v=e[i].to;
        if(v==fa)continue;
        dfs2(v,u);
    }
}

int main()
{
    memset(head,-1,sizeof(head));
    read(n);
    Rep(i,1,n)read(col[i]);
    Rep(i,1,n)if(!col[i])col[i]=-1;
    Rep(i,1,n-1){
        int x,y;
        read(x),read(y);
        add(x,y),add(y,x);
    }
    dfs1(1,0);
    // Rep(i,1,n)printf("%d\n",f[i]);
    out[1]=f[1];
    for(int i=head[1];~i;i=e[i].next)dfs2(e[i].to,1);
    Rep(i,1,n)
        printf("%d ",out[i]);
    puts("");
    return 0;
}
```


---

## 作者：寒鸽儿 (赞：1)

树形DP题  
求子树中的贡献比较简单, 设$f_i$为$i$的子树中的贡献, 有$f_i = color_i \sum_{k \in son_{i}}max\{f_k,0\}$， 其中$color_i \in \{-1,1\}$（黑色 /白色）  
然后考虑非根节点, 假设将它作为根节点, 显然原来连接着父节点的边会变成连接着一棵子树。这棵子树也要考虑在内。考虑从上往下$dp$, 记节点$i$的父亲为$fa_i$, 它的兄弟集合$A=son_{fa_i}-i$, $g_i$代表这个额外子树对答案的贡献, 则有$g_i = g_{fa_i}+color_{fa_i}+\sum_{k \in A}f_k$。这个“子树”是可选的, 若其值小于0也可以舍弃。 因此节点$i$的答案为$f_i + max\{g_i, 0\}$。  
```cpp
#include <bits/stdc++.h>
#define endl '\n'
#define rep(i,a,b) for(int i=a;i<=(b);++i)
#define per(i,a,b) for(int i=a;i>=(b);--i)
#define repp(i,a,b) for(int i=a;i<(b);++i)
#define perr(i,a,b) for(int i=a;i>(b);--i)
#define pb push_back
#define rz resize
#define itra(T) vector<T>::iterator
#define VI vector<int>
#define VL vector<long long>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int inf = 0x3f3f3f3f;
const ll linf = 0x3f3f3f3f3f3f3f3f;

inline void ponchline() { cout << "##################################" << endl; }
inline ll qp(ll a, ll b, ll p) { ll res = 1%p; for(;b;b>>=1) { if(b&1)res=res*a%p; a=a*a%p; } return res; }
inline ll gcd(ll a, ll b) { while(b) { int t = b; b = a%b; a=t; } return a; }
mt19937 mrand(random_device{}()); int rnd(int x) { return mrand() % x;}

vector< VI > edge;
vector<int> fa, col, dp1, dp2;

void dfs1(int pre, int cur) {
	fa[cur] = pre;
	dp1[cur]=col[cur];
	for(int ver : edge[cur]) {
		if(ver == pre) continue;
		dfs1(cur, ver);
		dp1[cur] += dp1[ver]<0?0:dp1[ver];
	}
}

void dfs2(int pre, int cur) {
	dp2[cur] = max(dp2[pre]+dp1[pre]-(dp1[cur]>0?dp1[cur]:0), 0);
	for(int ver : edge[cur]) {
		if(ver==pre) continue;
		dfs2(cur, ver);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n,u,v;
	cin >> n;
	edge.rz(n+1);
	fa.rz(n+1);
	col.rz(n+1);
	dp1.rz(n+1);
	dp2.rz(n+1);
	rep(i,1,n) {
		cin>>col[i];
		if(!col[i]) col[i]=-1;
	}
	rep(i,1,n-1) {
		cin>>u>>v;
		edge[u].pb(v);
		edge[v].pb(u);
	}
	dfs1(1,1);
	dfs2(0,1);
	rep(i,1,n) cout << dp1[i] + max(dp2[i], 0) << ' ';
	cout << endl;
	return 0;
}


```

---

## 作者：几何之舞丶 (赞：1)

看了看题解,大多数都是DP.

其实作为一道div3的题来说,这道题也算挺水了.

看一眼数据范围,感觉算法应该是一个O(n).

因为是一个无根树,可以考虑先以1号点为根,DFS一下,求出每个点能达到的最大差值.

此时注意到,只要是包含该节点的子图,就可以,因此我们还需要处理一下每一个节点与它父亲节点的关系,即选择子图的时候要不要选父亲节点.

两边DFS,复杂度O(n),这题就过啦.

话不多说,上代码.一些难理解的地方代码也已经写清楚了.

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<queue>
#include<stack>
#include<vector>
#include<map>
//#include<windows.h>
#include<algorithm>
#define N 200050
#define INF 0x7fffffff
#define int long long 
#define ll long long 
#define lson (now<<1)
#define rson (now<<1|1)
#define pii pair<int ,int >
#define pushup(now)  tr[now].sum=(tr[lson].sum+tr[rson].sum)%mod;
using namespace std;
inline int read(){
	int now=0;char c=getchar();int f=1;
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;c=getchar();
	}
	while(c>='0'&&c<='9'){
		now=(now<<1)+(now<<3)+(c^48);
		c=getchar();
	}
	return f*now;
}
int n,m,ans,size[N],tot,head[N],a[N];
struct node{
    int next,v;
}edge[N<<1];
inline void add(int x,int y){
    edge[++tot].next=head[x];edge[tot].v=y;head[x]=tot;
}
inline int dfs1(int now,int fa){
    size[now]=(a[now]==1?1:-1);
    for(int i=head[now];i;i=edge[i].next){
        int v=edge[i].v;
        if(v==fa)continue;
        int sum=dfs1(v,now);
        if(sum>0)size[now]+=sum;
    }
    return size[now];
}
inline void dfs2(int now,int fa){
    for(int i=head[now];i;i=edge[i].next){
        int v=edge[i].v;
        if(v==fa)continue;
        if(size[v]<0){//如果这个点的size大于0,则在求它父亲的最大插值时,肯定已经选过这个点了,防止重复计数.
            size[v]=max(size[v],size[now]+size[v]);
        }
        else
        size[v]=max(size[v],size[now]);
        dfs2(v,now);
    }
}
signed main(){
    n=read();
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=1;i<n;i++){
        int x,y;x=read();y=read();
        add(x,y);add(y,x);
    }
    dfs1(1,0);
    dfs2(1,0);
    for(int i=1;i<=n;i++)
    printf("%d ",size[i]);
    printf("\n");
    system("pause");
    return 0;
}
```


---

## 作者：夏子汐 (赞：1)

# 说一个不用换根的方法

## Part 1 先求出有根树中每一个节点及其儿子构成的树（包括当前节点）的最大值。

怎么求呢？

设$dp_i$表示第$i$个节点及其儿子树中必须选$i$的最大值。

初值：

$$
dp_i
\begin{cases}
1, &(a_i=1)\\
-1, &(a_i=0)
\end{cases}
$$

DFS回溯时求结果：

**如果$i$的一个儿子的值大于0，就让$i$的值加它（每个儿子互不相通，不存在重复），以保证值最大。**

$$dp_i+=\sum{dp_{son_i}(dp_{son_i}>0)}$$

## Part 2 求节点除了自己和儿子外的树的最大值

**如果最大值时的子树包括不属于它及它的儿子的节点，那么一定包括它的父亲。**

从上往下DFS，访问节点前，更新答案。

$$dp_i=dp_i+dp_{father}(dp_{father}>0)$$

这样是否正确？

连样例都过不了！

**为什么？**

经过思考，你找出了问题：

**一个节点的父亲的答案，可能包括了这个节点及其子树，会导致答案被计算了两遍。**

如何解决？

这里因为是在打比赛时做的，没有多想。直接用了一个map存储对当前节点有贡献的儿子及其答案。（Part 1中的）

转移式变为：
$$
dp_i=dp_i+dp_{father}-g_{father,i}(dp_{father}-g_{father,i}>0)
$$
其中$g_{father,i}$表示节点$i$在Part 1中对节点$father$做出了贡献，值为$g_{father,i}$。

## Part 3 输出答案

$dp_i$即为所求。

## 时间复杂度 $O(n \log n)$。

这里是按照总共有$(n-1)$个儿子，map复杂度为$O(\log n)$计算的，DFS的复杂度为$O(n)$，但显然map跑不满一个$\log$。

### 参考代码：
```cpp
#include<cstdio>
#include<map>
#include<algorithm>
#define ri register in
#define in long long
#define g() getchar()
inline in read(){//快读 
	ri x=0;register char ch=g();
	while(ch>'9' || ch<'0')ch=g();
	while(ch<='9' && ch>='0')
		x=(x<<3)+(x<<1)+ch-'0',ch=g();
	return x;
}
using namespace std;
in a[200005],fir[200005],nex[400005],to[400005],idx;
//dp数组用a代替，后面为链式前向星
map<in,in>v[200005];//map真好！（unordered_map更好） 
void dfs(in x,in fa){//Part 1
	for(in i=fir[x],y;i;i=nex[i]){
		if((y=to[i])==fa)continue;
		dfs(y,x);
		if(a[y]>0)a[x]+=a[y],v[x][y]=a[y];
		//对答案有贡献，更新答案，记录贡献 
	}
	return;
}
void dfs2(in x,in fa){//Part 1 
	in T=a[fa]-v[fa][x];
	//记录若加入不属于自己或儿子（祖孙）的点的贡献，
	//为什么是这样题解里面已经写了。
	//若不存在贡献，v[fa][x]默认为0（map特性）。 
	if(T>0)a[x]+=T;//做出贡献 
	for(ri i=fir[x],y;i;i=nex[i]){
		if((y=to[i])==fa)continue;
		dfs2(y,x);
		//为什么要在开始的时候更新答案呢？
		//因为这一次答案由父亲更新，而不是儿子。 
	}
	return;
}
int main(){
	ri n=read();
	for(ri i=1;i<=n;++i)a[i]=(read()==1)?1:-1;
	for(ri i=1,x,y;i<n;++i)//读入，建边 
		nex[++idx]=fir[x=read()],fir[x]=idx,to[idx]=y=read(),
		nex[++idx]=fir[y],fir[y]=idx,to[idx]=x;
	dfs(1,0),dfs2(1,0);//无根变有根，fa的值也可以为1。 
	for(ri i=1;i<=n;++i)printf("%d ",a[i]);//输出答案。 
	return 0;
}
```
## 效率：
用时 $1.51s$ 内存 $21.49MB$

测试点最大用时：$217ms$

[提交记录](https://www.luogu.com.cn/record/31683026)

附：$O(n \log n)$的复杂度是否正确？有没有极限数据？可以在评论区留言。

---

## 作者：chenxia25 (赞：0)

>### [洛谷题目页面传送门](https://www.luogu.com.cn/problem/CF1324F) & [CodeForces题目页面传送门](https://codeforces.com/contest/1324/problem/F)

>给定一棵树$T=(V,E),|V|=n,|E|=n-1$，节点$i$有一个权值$a_i\in\{0,1\}$，分别表示是白点、黑点。$\forall i\in[1,n]$，找一个树上连通子图，设此图内白、黑点各有$cnt1,cnt2$个，要求最大化$cnt1-cnt2$。输出最大值。

>$n\in\left[1,2\times10^5\right]$。

~~先吐槽一句：为什么我总共就打过$4$场div. 3，其中$3$场的F都是树形DP¿¿¿/yiw~~

非常显然的树形DP+二次扫描与换根。

首先，如果当前要求的这个点$x$是树根的话，那一切都好办了。设$dp_i$表示在以$x$为整棵树的根的情况下，在以$i$为根的子树内选连通子图，必须包含$i$时$cnt1-cnt2$的最大值。目标是$dp_x$，状态转移方程是$dp_i=\sum\limits_{j\in son_i}\max(0,dp_j)+\begin{cases}-1&a_i=0\\1&a_i=1\end{cases}$（累加以每个儿子为根的子树能给$dp_i$带来的贡献的最大值，如果为负就不选）。时间复杂度$\mathrm O(n)$。

然而题目要求对于所有点。不妨先令$1$为根求出所有点的DP值，再一遍二次扫描与换根求出所有点的答案。时间复杂度$\mathrm O(n)$。

总时间复杂度$\mathrm O(n)+\mathrm O(n)=\mathrm O(n)$。

下面是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
const int N=200000;
int n;
bool a[N+1];//点权
vector<int> nei[N+1];
int dp[N+1];
void dfs(int x=1,int fa=0){//求出以1为根时所有点的DP值 
	dp[x]=a[x]?1:-1;
	for(int i=0;i<nei[x].size();i++){
		int y=nei[x][i];
		if(y==fa)continue;
		dfs(y,x);
		dp[x]+=max(0,dp[y]);
	}
}
int ans[N+1];
void dfs0(int x=1,int fa=0){//二次扫描与换根 
	ans[x]=dp[x];//记录答案 
	for(int i=0;i<nei[x].size();i++){
		int y=nei[x][i];
		if(y==fa)continue;
		dp[x]-=max(0,dp[y]);
		dp[y]+=max(0,dp[x]);
		dfs0(y,x);
		dp[y]-=max(0,dp[x]);
		dp[x]+=max(0,dp[y]);
	}
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<n;i++){
		int x,y;
		cin>>x>>y;
		nei[x].pb(y);nei[y].pb(x);
	}
	dfs();
	dfs0();
	for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
	return 0;
}
```

---

