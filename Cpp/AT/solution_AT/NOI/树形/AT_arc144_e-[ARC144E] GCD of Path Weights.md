# [ARC144E] GCD of Path Weights

## 题目描述

给定一个有 $N$ 个顶点、$M$ 条边的有向图 $G$。顶点编号为 $1, 2, \ldots, N$。第 $i$ 条边是从 $a_i$ 指向 $b_i$ 的有向边，且 $a_i < b_i$。

定义正整数序列 $W = (W_1, W_2, \ldots, W_N)$ 的**美丽度**为：满足下述条件的正整数 $x$ 的最大值。

- 对于 $G$ 中从顶点 $1$ 到顶点 $N$ 的任意一条路径 $(v_1, \ldots, v_k)$（$v_1 = 1, v_k = N$），都有 $\sum_{i=1}^k W_{v_i}$ 是 $x$ 的倍数。

给定整数序列 $A = (A_1, A_2, \ldots, A_N)$。请你构造正整数序列 $W = (W_1, \ldots, W_N)$，使得 $A_i \neq -1$ 时 $W_i = A_i$，并求出所有可能的 $W$ 的美丽度的最大值。如果最大值不存在，则输出 `-1`。

## 说明/提示

## 限制条件

- $2 \leq N \leq 3 \times 10^5$
- $1 \leq M \leq 3 \times 10^5$
- $1 \leq a_i < b_i \leq N$
- 若 $i \neq j$，则 $(a_i, b_i) \neq (b_j, a_j)$
- 给定的图 $G$ 中，存在从顶点 $1$ 到顶点 $N$ 的路径。
- $A_i = -1$ 或 $1 \leq A_i \leq 10^{12}$

## 样例解释 1

从顶点 $1$ 到顶点 $N$ 的路径有 $(1,2,4)$ 和 $(1,3,4)$ 共两条。例如 $W = (5, 3, 7, 8)$ 的美丽度为 $4$。实际上，$W_1 + W_2 + W_4 = 16$，$W_1 + W_3 + W_4 = 20$，两者都是 $4$ 的倍数。

## 样例解释 2

从顶点 $1$ 到顶点 $N$ 的路径有 $(1,2,4)$、$(1,3,4)$、$(1,4)$ 共三条。例如 $W = (5, 3, 7, 8)$ 的美丽度为 $1$。

## 样例解释 3

例如 $W = (3, 10^{100}, 10^{100}, 7)$ 的美丽度为 $10^{100} + 10$。因为 $W$ 的美丽度可以无限大，所以最大值不存在。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 4
1 2
1 3
2 4
3 4
-1 3 7 -1```

### 输出

```
4```

## 样例 #2

### 输入

```
4 5
1 2
1 3
2 4
3 4
1 4
-1 3 7 -1```

### 输出

```
1```

## 样例 #3

### 输入

```
4 4
1 2
1 3
2 4
3 4
3 -1 -1 7```

### 输出

```
-1```

## 样例 #4

### 输入

```
5 5
1 3
3 5
2 3
3 4
1 4
2 -1 3 -1 4```

### 输出

```
9```

# 题解

## 作者：tzc_wk (赞：10)

挺 trivial 又 OI 化的一个想法，但是没想出来。

首先考虑确定了所有 $a_i$、如何判断是否所有 $1\sim n$ 的路径的点权和都是一个给定的数 $x$ 的倍数。首先点权转边权和。类比网络流建图中的拆点处理即可，这样问题转化为判断是否所有 $1\sim n$ 的边权和是否都是 $x$ 的倍数。

针对这个问题，我们有如下结论：

> 对于一张带权 DAG，所有 $1\sim n$ 的路径的边权和都是 $x$ 的倍数，当且仅当我们扣掉到达不了 $n$ 和不能从 $1$ 到达的点后，存在一组序列 $\{p_i\}$，使得对于任意一条边 $(u,v,w)$，均有 $p_v-p_u\equiv w\pmod{x}$。

这个思想最早在 CF241E 中出现。常应用于差分约束。

回到此题来，我们考虑有 $-1$ 的情况，先考虑如何判断 $x$ 是否可能成为答案，显然对于所有权值已经确定的边 $(u,v,w)$，都要有 $p_v\equiv p_u+w\pmod{x}$，使用带权并查集维护，遇到环就判一下起点和终点是否势能相等即可。至于求最大的 $x$，显然我们 check 一个 $x$ 是否合法的时候，等价于 check $x$ 是否是一堆数中所有数的因数，这样你只用对这些数求 $\gcd$ 即可，还是使用可持久化并查集维护。

---

## 作者：EuphoricStar (赞：8)

喵喵题。

考虑若所有点权都已确定，如何求 $1$ 到 $n$ 所有路径权值和的 $\gcd$。

考虑如何 check 一个 $x$ 是否合法。考虑拆点，把点权转成边权，在新图上连边 $u \to u'$，边权 $a_u$；$u' \to u$，边权 $-a_u$；原图 $u \to v$ 的边在新图上连边 $u' \longleftrightarrow v$，边权 $0$。那么需要判断新图的所有环权值和模 $x$ 意义下都是 $0$。

考虑若所有环权值和都为 $0$，那么任意两点间所有路径的边权之和模 $x$ 意义下都相等。若一个点到另一个点路径的边权之和有两种，设为 $a, b$，那么需要满足 $x \mid |a - b|$。跑出新图的一棵生成树，设根到 $i$ 的路径边权和为 $g_i$。若设一条非树边为 $u \to v$，边权为 $d$，那么需要满足 $g_u - g_v + d \equiv 0 \pmod x$。所以 $x$ 是所有这样的 $|g_u + d - g_v|$ 的因数。那么把所有 $|g_u + d - g_v|$ 取 $\gcd$ 就是答案。

还有个问题是点权可能不确定。点权不确定的点就不连 $u$ 和 $u'$ 之间的边，因为它们的边权可以随意赋值。这样新图可能不连通，跑出一个生成树森林即可。

[code](https://atcoder.jp/contests/arc144/submissions/47821551)

---

## 作者：Leasier (赞：5)

下文中设原图为 $G_1$，拆点后的新图为 $G_2$。

设答案非 $-1$ 时为 $x$，则我们只需要将所有权值为 $-1$ 的点置为 $x$ 即可，我们将在接下来的讨论中忽略它们所拆的边。

考虑将 $G_1$ 中的点 $u$ 拆成双向边 $(u, u', a_u)$，原来的边 $u \to v$ 拆成双向边 $(u', v, 0)$。现在我们需要讨论 $G_2$ 中的边权。

考虑先在 $G_1$ 中去掉所有 $1$ 不能到达或不能到达 $n$ 的点，在 $G_2$ 中也去掉这些点及其拆出的点。

对于 $G_2$ 中任意一条 $1 \to u \to v \to n'$ 的路径，如果我们将权值为 $w$ 的 $u \to v$ 换成另一条权值为 $w'$ 的路径，则 $x \mid |w - w'|$。

对于剩下的点，我们考虑抓出 $G_2$ 中的连通块，对每个连通块跑出任意一棵生成树，则对于该连通块内任意一条**不全是树边的路径**，我们都可以通过若干次把非树边替换成树上路径的操作将其变为一条全是树边的路径。

设 $T(u, v)$ 表示树上 $u, v$ 间边权和，则一条非树边 $(u, v, w)$ 替换为树上路径所带来的边权和减少量为 $T(u, v) - w$，于是 $x \mid |T(u, v) - w|$。

由于非树边一共只有 $O(m)$ 条，我们直接统计即可。

最后还有一个小问题：$G_2$ 中可能本来存在 $1 \to n'$ 的路径，而我们在上述操作中并没有统计到。实现时可以直接加边 $(1, n', 0)$。

综上，时间复杂度为 $O((n + m) \log w)$，其中 $w$ 为值域 $3 \times 10^{17}$。

代码：
```cpp
#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
	int nxt;
	int end;
	ll dis;
} Edge;

int cnt1 = 0, cnt2 = 0, cnt3 = 0;
int head1[300007], head2[300007], head3[600007];
ll val[600007];
bool vis1[300007], vis2[300007], vis3[600007];
Edge edge1[300007], edge2[300007], edge3[1200007];

inline void add_edge1(int start, int end){
	cnt1++;
	edge1[cnt1].nxt = head1[start];
	head1[start] = cnt1;
	edge1[cnt1].end = end;
}

inline void add_edge2(int start, int end){
	cnt2++;
	edge2[cnt2].nxt = head2[start];
	head2[start] = cnt2;
	edge2[cnt2].end = end;
}

inline void add_edge3(int start, int end, ll dis){
	cnt3++;
	edge3[cnt3].nxt = head3[start];
	head3[start] = cnt3;
	edge3[cnt3].end = end;
	edge3[cnt3].dis = dis;
}

void dfs1(int u){
	vis1[u] = true;
	for (int i = head1[u]; i != 0; i = edge1[i].nxt){
		int x = edge1[i].end;
		if (!vis1[x]) dfs1(x);
	}
}

void dfs2(int u){
	vis2[u] = true;
	for (int i = head2[u]; i != 0; i = edge2[i].nxt){
		int x = edge2[i].end;
		if (!vis2[x]) dfs2(x);
	}
}

ll gcd(ll a, ll b){
	return b == 0 ? a : gcd(b, a % b);
}

ll dfs3(int u, int n){
	ll ans = 0;
	vis3[u] = true;
	for (int i = head3[u]; i != 0; i = edge3[i].nxt){
		int x = edge3[i].end, x_ = x <= n ? x : x - n;
		if (vis1[x_] && vis2[x_]){
			if (!vis3[x]){
				val[x] = val[u] + edge3[i].dis;
				ans = gcd(ans, dfs3(x, n));
			} else {
				ans = gcd(ans, llabs(val[x] - val[u] - edge3[i].dis));
			}
		}
	}
	return ans;
}

int main(){
	int n, m;
	ll ans = 0;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++){
		int a, b, a_;
		scanf("%d %d", &a, &b);
		a_ = a + n;
		add_edge1(a, b);
		add_edge2(b, a);
		add_edge3(a_, b, 0);
		add_edge3(b, a_, 0);
	}
	for (int i = 1; i <= n; i++){
		ll a;
		scanf("%lld", &a);
		if (a != -1){
			int i_ = i + n;
			add_edge3(i, i_, a);
			add_edge3(i_, i, -a);
		}
	}
	add_edge3(1, n * 2, 0);
	dfs1(1);
	dfs2(n);
	for (int i = 1; i <= n; i++){
		if (vis1[i] && vis2[i]){
			int i_ = i + n;
			if (!vis3[i]) ans = gcd(ans, dfs3(i, n));
			if (!vis3[i_]) ans = gcd(ans, dfs3(i_, n));
		}
	}
	if (ans == 0){
		printf("-1");
	} else {
		printf("%lld", ans);
	}
	return 0;
}
```

---

## 作者：Ice_teapoy (赞：4)

欢迎来康康蒟蒻的博客，获得更佳阅读体验QAQ

https://juejin.cn/post/7189800442858045495
# 题目大意
给定有 $n$ 个点 $m$ 条边的有向无环图，给定长度为 $n$ 的整数数组 $a_1,a_2,...,a_n$。若 $a_i(1\le i\le n)$ 为 $-1$，说明图中第 $i$ 个节点的点权未知，否则说明该点的点权为 $i$。为点权未知的节点赋值，最大化从节点 $1$ 到节点 $n$ 之间所有路径点权和的最大公约数。

若不存在最大的答案，输出 `-1`。
# 思路
容易发现图中 $1$ 无法到达、或者无法到达 $n$ 的节点对答案没有影响，可以直接删去。然后我们进行一步转化，路径点权和让人无从下手，我们先把每个节点拆成两个节点，则点权转变为边权。比如样例 $1$:
```in
4 4
1 2
1 3
2 4
3 4
-1 3 7 -1
```
我们转化后建出的图为：

![image.png](https://p3-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/291775a5965443bea41e203534ab4400~tplv-k3u1fbpfcp-watermark.image?)

假设从节点 $1$ 到节点 $n$ 之间所有路径边权和都是 $x$ 的倍数，那么一定可以给每个点分配一个权值 $p_1,p_2,,...,p_n$，使得对每条有权值的有向边 $(u,v,w)$，都满足 $p_v\equiv p_u+w\pmod x$。因为我们只关心有向边两端点权值的相对大小，我们可以用加权并查集进行维护：\
记 $f[x]$ 表示 $x$ 在加权并查集中的父节点，$dt[x]$ 表示 $p_x+dt[x]\equiv p_{f[x]}\pmod x$。\
路径压缩如下图所示，直接令 $dt$ 相加即可：

![image.png](https://p6-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/51f2c943ea7047b696e9eba91548aea3~tplv-k3u1fbpfcp-watermark.image?)
------
所以用并查集维护两点之间的差有什么用处呢？下面我们来说明求解该问题的具体流程。

首先我们先将原图中的边加入到加权并查集中，这些边的边权均为 $0$。

![image.png](https://p6-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/4d038e9fdb5c4df8923e37a4f5bce4f3~tplv-k3u1fbpfcp-watermark.image?)

然后对于输入的旧图上第 $i$ 个点的点权 $a_i$，也就是转化后点 $i.1$ 和 $i.2$ 之间的边权，先查询两种是否在同一个并查集中：
- 如果不在，需要进行合并。

![image.png](https://p1-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/7e17304d9c3d4b39913a607cb51bf185~tplv-k3u1fbpfcp-watermark.image?)
- 如果在，说明 $dt[i.1]\equiv dt[i.2]+a[i]\mod x$，所以最后的答案是 $|dt[i.2]+a[i]-dt[i.1]|$ 的因数。

这样我们就可以找到所有给定点权对答案进行的限制了，显然我们自己乱填的点权不会给答案更多限制，所以对所有限制取最大公约数即可。注意如果从节点 $1$ 能直接通过确定边权的路径到达节点 $n$，那么最终的答案还需要与任一从节点 $1$ 到节点 $n$ 的路径长度取最大公约数（见样例 $4$）。

# 代码
```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <iostream>
#include <math.h>
#include <map>
#include <queue>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;
using LL=long long;
const int N=1e6+5;
//const LL mod=998244353;
const LL mod=1e9+7;
int n,m,k,x[N],y[N];
LL a[N],dt[N];
int f[N],vis[N],vv[N];
vector<int> e[N];
int find(int x)
{
	if (f[x]==x) return x;
	find(f[x]);
	dt[x]=dt[x]+dt[f[x]];
	return f[x]=f[f[x]];
}
void dfs(int u)
{
	vv[u]=1;
	if (u==n) vis[u]=1;
	for (auto v:e[u])
	{
		if (!vv[v]) dfs(v);
		if (vis[v]) vis[u]=1;
	}
}
LL gcd(LL a,LL b)
{
	if (b) return gcd(b,a%b);
	return a;
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n*2;++i) f[i]=i;
	for (int i=1;i<=m;++i)
	{
		scanf("%d%d",&x[i],&y[i]);
		e[x[i]].push_back(y[i]);
	}
	dfs(1);
	if (!vis[n]) return printf("-1\n"),0;
	for (int i=1;i<=m;++i)
		if (vis[x[i]]&&vis[y[i]]) f[find(x[i]*2)]=find(y[i]*2-1);
	LL ans=0;
	for (int i=1;i<=n;++i)
	{
		scanf("%lld",&a[i]);
		if (!vis[i]) continue;
		if (a[i]==-1) continue;
		if (find(i*2-1)!=find(i*2))
		{
			dt[f[i*2-1]]=a[i]-dt[i*2-1];
			f[f[i*2-1]]=i*2;
		}
		else ans=gcd(ans,abs(dt[i*2]+a[i]-dt[i*2-1]));
	}
	if (find(1)==(n*2)) ans=gcd(ans,dt[1]);
	if (ans==0) ans--;
	printf("%lld\n",ans);
	return 0;
}
```



---

## 作者：DaiRuiChen007 (赞：2)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc144_e)

**题目大意**

> 给定 $n$ 个点 $m$ 条边的 DAG，点有点权，有一些点权不确定，找到一种方式最大化所有 $1\to n$ 路径点权和的 $\gcd$。
>
> 数据范围：$n\le 3\times 10^5$。

**思路分析**

先删除所有不在 $1\to n$ 路径上的点，然后拆点成边，使得答案变成路径边权和。

设答案为 $p$，根据经典结论，存在一组序列 $d_1\sim d_n$ 使得 $\forall (u,v)\in E,d_u+w(u,v)\equiv d_v\pmod p$。

把图看成无向图，只要处理所有环的 $\gcd$ 即可。

用可持久化并查集维护 $d_{rt}-d_u$ 的值，遇到环时把答案和 $d_u+w(u,v)-d_v$ 取 $\gcd$ 即可。

时间复杂度 $\mathcal O((n+m)\alpha(n))$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=3e5+5;
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a; }
bool vs[MAXN],vt[MAXN];
vector <int> G[MAXN];
int n,m,fa[MAXN<<1];
ll a[MAXN],d[MAXN<<1],ans=0;
void dfs(int u) {
	vs[u]=true;
	if(u==n) vt[u]=true;
	for(int v:G[u]) {
		if(!vs[v]) dfs(v);
		vt[u]|=vt[v];
	}
}
int find(int x) {
	if(x==fa[x]) return x;
	int c=find(fa[x]);
	d[x]+=d[fa[x]],fa[x]=c;
	return c;
}
signed main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=2*n;++i) fa[i]=i;
	for(int i=1,u,v;i<=m;++i) {
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
	}
	dfs(1);
	if(!vt[1]) return puts("-1"),0;
	for(int i=1;i<=n;++i) if(vt[i]) for(int j:G[i]) if(vt[j]) {
		fa[find(i+n)]=find(j);
	}
	for(int i=1;i<=n;++i) {
		scanf("%lld",&a[i]);
		if(vt[i]&&~a[i]) {
			if(find(i)!=find(i+n)) {
				int x=find(i);
				d[x]=a[i]-d[i],fa[x]=i+n;
			} else {
				ans=gcd(ans,abs(d[i+n]+a[i]-d[i]));
			}	
		}
	}
	if(find(1)==2*n) ans=gcd(ans,d[1]);
	printf("%lld\n",ans?ans:-1ll);
	return 0;
}
```

---

## 作者：cwfxlh (赞：1)

## [AT_arc144_e [ARC144E] GCD of Path Weights](https://www.luogu.com.cn/problem/AT_arc144_e)   

首先删掉 1 不能到达的点和不能到达 $n$ 的点。    

将一个点拆成两个点，于是变成了研究边权的取值。考虑对于一个值 $x$，如何判定所有的 1 到 $n$ 的路径长度都是其倍数。显然对于每个 $i$，有唯一的 $dis_i$ 表示所有到 $i$ 的路径长度对 $x$ 取模的值，并且对于每条边 $(u,v,w)$ 都有 $dis_u+w\equiv dis_v\bmod x$。于是使用并查集判定。如果出现边的权值不确定，那么忽略这条边，显然这是正确的。     

接下来思考怎么找到最大的 $x$。做一遍判定，在合并并查集的过程中，如果出现两个本已属于一个并查集的点合并，两个点分别是 $v_{rt}+a$ 和 $v_{rt}+b$，差为 $c$，则答案必须是 $|b-a-c|$ 的因数。于是对所有这样的东西取个 $\gcd$ 就可以了。复杂度 $O((n+m)\alpha(n))$。    

本人的一个隐蔽挂点：当答案对 0 取 $\gcd$ 且答案目前为 -1 时，不要改答案。     

代码：    

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k1,k2,k3,k4,k5,k6,k7,k8,k9,ans=-1,vis[600003],a[600003];
pair<int,int>bcj[600003];
vector<int>e[600003],ne[600003];
void upd(int X){
	if(X==0)return;
	X=abs(X);
	if(ans==-1)ans=X;
	else ans=__gcd(ans,X);
	return;
}
void dfs(int now,int vvv){
	vis[now]|=vvv;
	for(auto i:e[now])if(!(vis[i]&vvv))dfs(i,vvv);
	return;
}
pair<int,int>finf(int now){
	if(bcj[now].first!=now){
		int uu=bcj[now].second;
		bcj[now]=finf(bcj[now].first);
		bcj[now].second+=uu;
	}
	return bcj[now];
}
void merge(int X,int Y,int v){
	pair<int,int>v1=finf(X);
	pair<int,int>v2=finf(Y);
	if(v1.first!=v2.first){
		bcj[v1.first]=make_pair(v2.first,v2.second-v1.second-v);
		return;
	}
	upd(v2.second-v1.second-v);
	return;
}
signed main(){
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>k1>>k2;
		e[k1].emplace_back(k2);
		ne[k2].emplace_back(k1);
	}
	for(int i=1;i<=n;i++)cin>>a[i];
	dfs(1,1);
	for(int i=1;i<=n;i++)swap(e[i],ne[i]);
	dfs(n,2);
	if(vis[1]!=3||vis[n]!=3){
		cout<<-1;
		return 0;
	}
	for(int i=1;i<=n*2;i++)bcj[i]=make_pair(i,0);
	for(int i=1;i<=n;i++){
		if(vis[i]!=3)continue;
		if(a[i]!=-1)merge(i*2-1,i*2,a[i]);
	}
	for(int i=1;i<=n;i++){
		if(vis[i]!=3)continue;
		for(auto j:ne[i])if(vis[j]==3)merge(i*2,j*2-1,0);
	}
	merge(1,2*n,0);
	cout<<ans;
	return 0;
}
```

---

## 作者：exCat (赞：0)

困难题。

## 前置

带权并查集。

## 思路

1. 首先拆点将点权化为边权，对于原图的边 $(u,v)$ 变成 $(u_{out},v_{in})$ 边权设为 $0$,拆出来的两个点 $(u_{in},u_{out})$ 之间的边权设为给出的点权，问题变为边权和最大公因数。 

2. 我们发现对于点权和的最大公因数最大没什么想法，所以先考虑如果 $1 \to n$ 的所有路径都是 $x$ 的倍数 。我们对每个点设一个 $d_i$ 表示 $1$ 到 $i$ 的某一条路径的边权和对 $x$ 取模后是  $d_i$，且对任意一条边 $(u,v)$ 都满足 $d_v-d_u \equiv w(u,v) \pmod x$ ，还要满足对于 $d_s\equiv d_t\pmod x$。我们可以证明存在这样的 $d$ 是 $1 \to n$ 的所有路径都是 $x$ 的倍数的充分必要条件。

3. 具体证明如下：先证必要性，首先我们可以确定任意一条 $1\to i$ 路径的边权和取模后是唯一的，如果不唯一，这两条路径拼上后面一条相同的路径到 $t$ 的边权和取模后一定不同，就不满足条件。值唯一那么对每一条边肯定满足 $d_v-d_u \equiv w(u,v) \pmod x$。再证充分性，我们取任意一条路径 $s\to u_1\to u_2\to ...\to t$ ，有 $d_s\equiv d_t\pmod x$ 和 $d_s+w(s,u_1)+w(u_1,u_2)+...+w(u_n,t)\equiv d_t \pmod x$ （这个式子就是将 $d_v\equiv d_u+w(u,v)$ 不断展开得到的），有这两个式子就有 $w(s,u_1)+w(u_1,u_2)+...+w(u_n,t)\equiv 0\pmod x$，证毕。

4. 现在回到原题，我们可以算出一些  $d_i$ 的值（边权不确定的就不管），对于这些  $d_i$ 一定满足上面的式子，那么路径的 $\gcd$ 就会被限制，对于式子给出的所有限制求  $\gcd$ 即可得出本题的答案。

5. 观察上面的式子是两个点的差，所以我们要关注两点之间的差即可，用加权并查集来维护联通块里任意两点的差值。对于图上的每条边，如果 $(u,v)$ 不联通就将两个并查集合并起来，如果连通就有了限制 $dt_u \equiv dt_v+a_i \pmod x$ (考虑将三个上面的边的限制写出，进行一些简单的代换即可)。那么  $x$  一定是 $dt_u-dt_v+a_i$ 的因子，对于所有这样的限制求 $\gcd$ 即可。

6. 注意如果本身存在任一 $1$ 到 $n$ 的路径（边权确定）也要与之取最大公因数。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long//看数据范围 
const int N=6e5+10;
int fa[N],dt[N],vis[N],vv[N],l[N],r[N],n,m,a[N];
vector<int> ve[N];
int find(int x)
{
	if(fa[x]==x)return x;
	find(fa[x]);
	dt[x]+=dt[fa[x]];
	return fa[x]=fa[fa[x]];
}
void dfs(int u)
{
	vis[u]=1;
	if(u==n){vv[n]=1;return ;} 
	for(int v:ve[u])
	{
		if(!vis[v])dfs(v);
		if(vv[v])vv[u]=1; 
	} 
}
void add2(int x,int y,int z)
{
	fa[x]=y;
	dt[x]=z;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=2*n;i++)fa[i]=i;
	for(int i=1;i<=m;i++)
	{
		cin>>l[i]>>r[i];
		ve[l[i]].push_back(r[i]);
	}
	for(int i=1;i<=n;i++)cin>>a[i];
	dfs(1);
	if(vv[n]==0)
	{
		cout<<"-1"<<'\n';
		return 0;
	}
	for(int i=1;i<=m;i++)
		if(vv[l[i]]&&vv[r[i]])add2(find(n+l[i]),find(r[i]),0);
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		if(!vv[i]||a[i]==-1)continue;
		int f1=find(i),f2=find(n+i);
		if(f1==f2)
		{
			ans=__gcd(ans,abs(dt[n+i]+a[i]-dt[i]));
		}
		else add2(f1,n+i,a[i]-dt[i]);
	}
	if(find(1)==n*2)ans=__gcd(ans,dt[1]);
	cout<<(ans==0?-1:ans)<<'\n';
	return 0; 
} 
```

## 思考

关于拆点我有一些思考，有可能是假的，只是写出来和大家讨论。

为什么一定要拆点呢？我们发现将 $d_i$ 的定义换成点权和也可以证是充要条件（仿照即可），但是没有人用点权写。如果直接设为点权，对于一个点权不确定的点，我们对它的限制其实是所有指向它的点的 $d_i$ 要相同，这就等价于是对拆完点之后的每个点入点的限制（因为中间的边权是 $0$ ）。所以我们可以不拆点，遇到每个点对所有指向它的点写限制。

---

