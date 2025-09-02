# Ehab and a component choosing problem

## 题目描述

给定一棵包含 $n$ 个节点的树。每个节点 $u$ 有一个权值 $a_u$。你需要选择一个整数 $k$（$1 \le k \le n$），然后选择 $k$ 个互不重叠的连通块（即每个节点至多属于一个连通块）。设你选择的所有节点的集合为 $s$。你希望最大化以下表达式：

$$
\frac{\sum\limits_{u \in s} a_u}{k}
$$

换句话说，你希望最大化所选节点权值之和与所选连通块数量之比。如果有多种方案能够取得最大值，你还需要**最大化 $k$**。

注意，相邻的节点可以属于不同的连通块，详见第三个样例。

## 说明/提示

一个连通块是指这样一个节点集合：对于集合中的任意两个节点，存在仅经过集合内节点的路径将它们连通。

在第一个样例中，最优方案是选择整棵树。

在第二个样例中，你只有一种选择（只能选节点 1），因为不能选择 0 个连通块。

在第三个样例中，注意你可以只选节点 1，或者选节点 1 和节点 3，甚至选整棵树，分数都是 $-1$，但我们要最大化 $k$。

在第四个样例中，最优方案是选择节点 1 和节点 3。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
1 2 3
1 2
1 3
```

### 输出

```
6 1```

## 样例 #2

### 输入

```
1
-2
```

### 输出

```
-2 1```

## 样例 #3

### 输入

```
3
-1 -1 -1
1 2
2 3
```

### 输出

```
-3 3```

## 样例 #4

### 输入

```
3
-1 -2 -1
1 2
1 3
```

### 输出

```
-2 2```

# 题解

## 作者：一扶苏一 (赞：4)

[更好的阅读体验](https://www.cnblogs.com/yifusuyi/p/10245226.html)

## Description

给定一棵 $n$ 个节点的树，点有点权 $a_u$，可能为负。现在请你在树上找出 $k~(1~\leq~k~\leq~n)$ 个不相交集合，使得每个集合中的每对点都可以通过本集合中的点互相到达，假设选出的 $k$ 个集合的并集为 $s$，要求最大化：

$$\frac{\sum_{u \in s} a_u}{k}$$

如果有多解请输出 $k$ 最大的解

## Input

第一行是节点个数 $n$。

下面一行 $n$ 个数代表点权

下面 $n - 1$ 行描述这棵树

## Output

输出一行两个整数，分别是选出的点权和以及 $k$

**不约分**

## Solution

#### 结论：在不限元素个数时，要求选出元素的平均值最大，则最优解一定为只选择元素值最大的元素。如果有多个元素的值最大，选择个数对答案无影响。

证明：数学归纳法，先将元素按照权值降序排序。当只选择 $1$ 个元素的时候，显然选择第一个元素最优。考虑已经选了 $k$ 个元素，现在要决定是否选 $k + 1$ 个元素。由于是降序排序的，则这个元素的权值显然不大于前面所有元素的平均值。设前面所有元素的平均值为 $a$，第 $k + 1$ 个元素的权值为 $w$，则选择该元素后的平均值为 $\frac{ak + w}{k + 1}$ 。要判断它和原平均值 $a$ 的关系，则对它们做差，记 $\delta~=~\frac{ak + w}{k + 1} - a$

则

$$\delta~=~\frac{ak}{k + 1} + \frac{w}{k + 1}- \frac{a(k + 1)}{k + 1}~=~\frac{w}{k + 1} - \frac{a}{k + 1}~=~\frac{w - a}{k + 1}$$

前面已经论证 $w~\leq~a$，于是 $\delta~\leq~0$。当且仅当 $w~=~a$ 即前 $k + 1$ 个元素权值相同时，等号成立。证毕。

于是根据这个结论，问题就被转化成了：求一个符合要求的集合使得这个集合的权值和尽可能大，然后统计有多少个这样的不想交的集合。

第一问显然可以直接树形DP，设 $f_u$ 为 $u$ 的子树中必选 $u$ 的集合的最大权值，则有：

$$f_u~=~\sum_{to} \max(f_{to}, 0)$$

于是就可以求出最大的权值了。考虑统计答案时，由于要求的是不相交的集合，所以我们每将一个集合加入贡献以后再将这个集合删掉，一边统计答案一遍DP就可以了。

## Code

```cpp
#include <cstdio>
#include <algorithm>
#ifdef ONLINE_JUDGE
#define freopen(a, b, c)
#define putchar(o) \
puts("I am a cheater!")
#endif
#define rg register
#define ci const int
#define cl const long long

typedef long long int ll;

namespace IPT {
	const int L = 1000000;
	char buf[L], *front=buf, *end=buf;
	char GetChar() {
		if (front == end) {
			end = buf + fread(front = buf, 1, L, stdin);
			if (front == end) return -1;
		}
		return *(front++);
	}
}

template <typename T>
inline void qr(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch=IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = (x << 1) + (x << 3) + (ch ^ 48), ch = IPT::GetChar();
	if (lst == '-') x = -x;
}

template <typename T>
inline void ReadDb(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch = IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = x * 10 + (ch ^ 48), ch = IPT::GetChar();
	if (ch == '.') {
		ch = IPT::GetChar();
		double base = 1;
		while ((ch >= '0') && (ch <= '9')) x += (ch ^ 48) * ((base *= 0.1)), ch = IPT::GetChar();
	}
	if (lst == '-') x = -x;
}

namespace OPT {
	char buf[120];
}

template <typename T>
inline void qw(T x, const char aft, const bool pt) {
	if (x < 0) {x = -x, putchar('-');}
	rg int top=0;
	do {OPT::buf[++top] = char(x % 10 + '0');} while (x /= 10);
	while (top) putchar(OPT::buf[top--]);
	if (pt) putchar(aft);
}

const int maxn = 300010;
const int maxm = 600010;

struct Edge {
	int to;
	Edge *nxt;
};
Edge edge[maxm], *hd[maxn];int ecnt;
inline void cont(ci from, ci to) {
	Edge &e = edge[++ecnt];
	e.to = to; e.nxt = hd[from]; hd[from] = &e;
}

int n, cnt;
ll ans = -(1ll << 62);
ll MU[maxn], frog[maxn];

void reading();
void dfs(ci, ci, ci);

int main() {
	freopen("1.in", "r", stdin);
	qr(n);
	for (rg int i = 1; i <= n; ++i) qr(MU[i]);
	reading();
	dfs(1, 0, 1); dfs(1, 0, 0);
	qw(ans * cnt, ' ', true); qw(cnt, '\n', true);
	return 0;
}

void reading() {
	int a, b;
	for (rg int i = 1; i < n; ++i) {
		a = b = 0; qr(a); qr(b);
		cont(a, b); cont(b, a);
	}
}

void dfs(ci u, ci fa, ci op) {
	frog[u] = MU[u];
	for (Edge *e = hd[u]; e; e = e->nxt) {
		int &to = e->to;
		if (to == fa) continue;
		dfs(to, u, op);
		if (frog[to] > 0) frog[u] += frog[to];
	}
	if (op) ans = std::max(ans, frog[u]);
	else if (frog[u] == ans) ++cnt, frog[u] = -(1ll << 60);
}
```

## Summary

选择任意个元素使得平均值最大时，只选择最大的就好啦

---

## 作者：FReQuenter (赞：2)

发现一个抽象的事情：取到 $k=1$ 的时候一定有题目里定义的那个式子的最大值。因为取到一个和最大的连通块之后，再往它里面加入元素显然不符合“最大的”限制；另外再取一个也只能让答案变小或不变。

令 $f_i$ 表示以 $i$ 为根的子树内取到的最大连通块之和。则 $f_{i}=\sum f_{j}$，其中 $f_j\ge0$ 且 $j$ 是 $i$ 的儿子。

考虑如何求 $k$ 的最大值。一种想法是算 $f$ 有多少个最大值，但这样显然会算重。所以我们再跑一遍 dp，优先取深度低的（保证取最多），取完一个就把其 $f_i$ 赋值成 $0$ 不让它继续贡献。

```cpp
#include<bits/stdc++.h>
#define int long long
#define MAXN 300005
using namespace std;
int n,ans=-1e18,sum,a[MAXN],f[MAXN];
vector<int> gv[MAXN];
void dfs1(int now,int father){
	f[now]=a[now];
	for(auto nx:gv[now]) if(nx!=father) {dfs1(nx,now);if(f[nx]>0) f[now]+=f[nx];}
	ans=max(ans,f[now]);
}
void dfs2(int now,int father){
	f[now]=a[now];
	for(auto nx:gv[now]) if(nx!=father) {dfs2(nx,now);if(f[nx]>0) f[now]+=f[nx];}
	if(f[now]==ans) {sum++;f[now]=-1;}
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<n;i++){
		int x,y;
		cin>>x>>y;
		gv[x].push_back(y);
		gv[y].push_back(x);
	}
	dfs1(1,0);
	memset(f,0,sizeof(f));
	dfs2(1,0);
	cout<<ans*sum<<' '<<sum; 
}
```

---

## 作者：xuantianhao (赞：0)

## [Ehab and a component choosing problem](https://www.luogu.com.cn/problem/CF1088E)

思路一 $n^2$ 的 DP。

考虑设 $f[i][j][0/1]$ 表示：

节点 $i$，子树分了 $j$ 个集合，节点 $i$ 是否在某个集合内的最大值。

但是这样是没有前途的，你再怎么优化也优化不了，还是只能从题目本身的性质入手。

思路二分析性质，$O(n)$ 解决。

发现，答案最大也不会超过最大的那个集合的和。

我们考虑把每个集合看成一个数。那么，题目就让我们从一堆数中选一些数，使得它们的平均值最大。只选最大的那一个数，则答案就是最大的那一个数；但是最大的数可能不止一个，因此要找到所有值最大且互不相交的集合的数量。

找到最大的那个集合，可以直接 $O(n)$ 的 DP 出来。设 $f_x$ 表示以 $x$ 为根的子树中，包含 $x$ 的所有集合中最大的那个，则有

$$f_x=\sum\limits_{y\in son_x}\max(f_y,0)$$

这样最大的那个集合就是 $f_x$ 的最大值。

至于互不重叠的限制嘛，再 DP 一遍，当一个 $f_x$ 达到最大时，计数器 $++$，并将 $f_x$ 清零。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,val[300100],f[300100],mx=0x8080808080808080,res,head[300100],cnt;
bool vis[300100];
struct node{
    int to,next;
}edge[600100];
void ae(int u,int v){
    edge[cnt].next=head[u],edge[cnt].to=v,head[u]=cnt++;
    edge[cnt].next=head[v],edge[cnt].to=u,head[v]=cnt++;
}
void dfs1(int x,int fa){
    f[x]=val[x];
    for(int i=head[x];i!=-1;i=edge[i].next)if(edge[i].to!=fa)dfs1(edge[i].to,x),f[x]+=max(0ll,f[edge[i].to]);
}
void dfs2(int x,int fa){
    f[x]=val[x];
    for(int i=head[x];i!=-1;i=edge[i].next)if(edge[i].to!=fa)dfs2(edge[i].to,x),f[x]+=max(0ll,f[edge[i].to]);
    if(f[x]==mx)res++,f[x]=0x8080808080808080;
}
signed main(){
    scanf("%lld",&n),memset(head,-1,sizeof(head));
    for(int i=1;i<=n;i++)scanf("%lld",&val[i]);
    for(int i=1,x,y;i<n;i++)scanf("%lld%lld",&x,&y),ae(x,y);
    dfs1(1,0);
    for(int i=1;i<=n;i++)mx=max(mx,f[i]);
    dfs2(1,0);
    printf("%lld %lld\n",1ll*res*mx,res);
    return 0;
}
```

---

## 作者：Yuby (赞：0)

[题面](https://www.luogu.com.cn/problem/CF1088E)

点数：2400

## 分析

题意即为最大化集合的和的平均值。

### 结论：

取权值和最大的一个连通块就是平均值最大。

### 证明：

设当前权值和最大的连通块的权值和为 $x$，设另一集合的权值和和为 $y$。若加入后得到的平均数更大，则 $x<\dfrac{x+y}{2}$。就有 $x<y$，不满足 $x$ 为权值最大的连通块的假设。

因此，只取一个权值最大的连通块即可使平均值最大。但注意到题目中还要求最大化 $k$，不难发现只有所有选出的连通块的权值和相等，才能继续保证平均值最大。证明类似前面的证明，略。注意到不可能存在两个权值和最大的连通块相连，不然把这两个连通块合并之后权值必然更大。所以在求出最大的权值和之后再跑一遍深搜，把用过的赋值为 0 即可。

复杂度：$O(n)$。

核心代码：

```cpp
const ll MAXN=3e5+7;
ll n,a[MAXN],ans=-LLINF,m,dp[MAXN];
vector<ll>tree[MAXN];
void dfs(ll u,ll fa)
{
	dp[u]=a[u];
	for(ll i=0;i<tree[u].size();i++)
	{
		ll v=tree[u][i];
		if(v==fa)continue;
		dfs(v,u);
		dp[u]+=max(dp[v],0);
	}
	ans=max(ans,dp[u]);
}
void dfs1(ll u,ll fa)
{
	dp[u]=a[u];
	for(ll i=0;i<tree[u].size();i++)
	{
		ll v=tree[u][i];
		if(v==fa)continue;
		dfs1(v,u);
		dp[u]+=max(dp[v],0);
	}
	if(dp[u]==ans)
	{
		m++;dp[u]=0;
	}
}
int main()
{
 	//freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    n=read();
    for(ll i=1;i<=n;i++)a[i]=read();
    for(ll i=1;i<n;i++)
    {
    	ll u=read(),v=read();
    	tree[u].push_back(v);
    	tree[v].push_back(u);
	}dfs(1,0);dfs1(1,0);
	write(ans*m),pc(32),write(m),pc(10);
	return 0;
}
```



---

