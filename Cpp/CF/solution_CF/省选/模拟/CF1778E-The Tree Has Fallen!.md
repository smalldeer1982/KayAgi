# The Tree Has Fallen!

## 题目描述

Recently, a tree has fallen on Bob's head from the sky. The tree has $ n $ nodes. Each node $ u $ of the tree has an integer number $ a_u $ written on it. But the tree has no fixed root, as it has fallen from the sky.

Bob is currently studying the tree. To add some twist, Alice proposes a game. First, Bob chooses some node $ r $ to be the root of the tree. After that, Alice chooses a node $ v $ and tells him. Bob then can pick one or more nodes from the subtree of $ v $ . His score will be the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of all the values written on the nodes picked by him. Bob has to find the maximum score he can achieve for the given $ r $ and $ v $ .

As Bob is not a good problem-solver, he asks you to help him find the answer. Can you help him? You need to find the answers for several combinations of $ r $ and $ v $ for the same tree.

Recall that a tree is a connected undirected graph without cycles. The subtree of a node $ u $ is the set of all nodes $ y $ such that the simple path from $ y $ to the root passes through $ u $ . Note that $ u $ is in the subtree of $ u $ .

## 说明/提示

In each of the below figures, the green-colored node is the node picked by Bob, and the red-colored node is the node picked by Alice. The values of the nodes are placed in the blue boxes beside the nodes.

Consider the first example. In the first query, if we put the root node $ 4 $ at the top of the tree, the tree looks like the below figure:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1778E/ec5505273106a94c8de6163a7eb02cfed05d66b0.png) Tree with root node $ 4 $ in the first query.  The nodes in the subtree of the node $ 2 $ are $ [2,1,5,6,3] $ . Among them, Bob can pick node $ 3 $ , node $ 5 $ , and node $ 6 $ . His score will be $ a_3 \oplus a_5 \oplus a_6 = 8 \oplus 6 \oplus 1 = 15 $ . He can't achieve any score more than this.In the second query, if the root node $ 3 $ is placed at the top of the tree, the tree looks like the below figure:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1778E/e8877e490994d631f06ea136adde33088a4a965e.png) Tree with root node $ 3 $ in the second query.  The only node in the subtree of the node $ 5 $ is $ 5 $ . Bob can only pick the node $ 5 $ . His score will be $ a_5 = 6 $ .In the third query, if the root node $ 1 $ is placed at the top of the tree, the tree looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1778E/da6101f2a6fef24f0e85fee849038943b916b568.png) Tree with root node $ 1 $ in the third query.  The nodes in the subtree of the node $ 2 $ are $ [2,3,6,4] $ . Among them, Bob can pick node $ 2 $ , node $ 3 $ , and node $ 4 $ . His score will be $ a_2 \oplus a_3 \oplus a_4 = 12 \oplus 8 \oplus 25 = 29 $ . He is not able to score higher than that.

## 样例 #1

### 输入

```
3
6
12 12 8 25 6 1
1 5
1 2
2 6
2 3
2 4
3
4 2
3 5
1 2
2
3 8
1 2
4
2 2
2 1
1 2
1 1
3
3 8 7
1 2
2 3
2
2 2
2 1```

### 输出

```
15
6
29
11
3
8
11
15
3```

# 题解

## 作者：封禁用户 (赞：10)

### 题目传送门

[洛谷](https://www.luogu.com.cn/problem/CF1778E)

[CF](https://codeforces.com/contest/1778/problem/E)

### 分析

看到异或最大，我们首先要想到[线性基](https://oi-wiki.org/math/linear-algebra/basis/)。

我们先定 $1$ 为根，求一个 dfs 序。

对于 $r$ 和 $v$ 的关系，我们分三种情况讨论：

1.  $r = v$ 时，取区间 $[1,n]$ （即整颗树）。

1.  当 $v$ 为 $r$ 的祖先时，取 $r$ 的祖先中深度小于 $v$ 且深度最大的节点（$v$ 的子节点）记为 $t$，取区间 $[1,L_t-1]$ 和区间 $[R_t+1,n]$。

1.  其它情况，取区间 $[L_v,R_v]$。

对于第二种情况，我们可以把原数组复制两倍，把后缀和前缀合并成一个区间。

我们从前到后扫描，不断地加入数。由于是从前到后的，线性基中应当贪心地保留位置最大的数。

时间复杂度只有 $O(n \log N)$，其中 $N$ 是值域范围。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename T>inline void read(register T &x)
{
	register T p = 1,num = 0;
	char c = getchar();
	while(c < '0'||c > '9')
	{
		if(c == '-') p = -p;
		c = getchar();
	}
	while('0' <= c&&c <= '9')
	{
		num = (num<<3)+(num<<1)+(c^48);
		c = getchar();
	}
	x = p * num;
}
template<typename T>inline void write(register T x)
{
	if(x < 0) putchar('-'),x = -x;
	if(x > 9) write(x/10);
	putchar(x%10+48);
}
#define D(i,a,b) for(register int i=a;i>=b;--i)
#define F(i,a,b) for(register int i=a;i<=b;++i)
#define ll long long
#define pii pair<int,int>
#define N 200010
int head[N],nxt[N<<1],to[N<<1],cnt;
inline void add(int u,int v)
{
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = v;
}
pii a[N<<1];
int ans[N],t,n,q;
vector<pii> b[N<<1];
int L[N],R[N],f[N][20],dep[N],times = 0;
void dfs(int u,int fa)
{
	L[u] = ++times;
	f[u][0] = fa;
	dep[u] = dep[fa] + 1;
	for(register int i = head[u];i;i = nxt[i])
	{
		int v = to[i];
		if(v == fa) continue;
		dfs(v,u);
	}
	R[u] = times;
}
inline int lca(int u,int v)
{
	if(dep[u] < dep[v]) swap(u,v);
	D(i,18,0)
		if(dep[f[u][i]] >= dep[v])
			u = f[u][i];
	if(u == v) return u;
	D(i,18,0)
		if(f[u][i] != f[v][i])
			u = f[u][i],v = f[v][i];
	return f[u][0];
}
inline int near(int u,int v)
{
	D(i,18,0)
		if(dep[f[v][i]] > dep[u])
			v = f[v][i];
	return v;
}
struct ji_ni_tai_mei
{
	int a[35],p[35]; 
	inline void clear()  
	{
		memset(a,0,sizeof(a));
		memset(p,0,sizeof(p));
	}	
	inline void update(int t,int x)
	{
		D(i,30,0)
		{
			if(!(x & (1<<i))) continue;
			if(!a[i])
			{
				a[i] = x,p[i] = t;
				break;
			}
			if(t > p[i])
			{
				swap(t,p[i]);
				int tp = x^a[i];
				a[i] = x;
				x = tp;
			}
			else x ^= a[i];
		}
	}
	inline int query(int l)
	{
		int ret = 0;
		D(i,30,0)
			if(p[i] >= l&&(ret ^ a[i]) > ret)
				ret ^= a[i];
		return ret;	
	}
}ikun;
inline bool cmp(const pii &x,const pii &y)
{
	return L[x.first] < L[y.first];
}
int main()
{
	read(t);
	while(t--)
	{
		read(n);
		F(i,1,n) read(a[i].second),a[i].first = i;
		cnt = times = 0;
		F(i,0,n) head[i] = 0;
		F(i,1,n-1)
		{
			int u,v;
			read(u),read(v);
			add(u,v);
			add(v,u);	
		}
		dfs(1,0);
		F(i,1,18) 
			F(j,1,n)
				f[j][i] = f[f[j][i-1]][i-1];
		sort(&a[1],&a[n+1],cmp);
		F(i,n+1,n<<1) a[i] = a[i-n];
		read(q);
		F(i,1,n<<1) b[i].clear();
		F(i,1,q)
		{
			int u,v;
			read(u),read(v);	
			int x = lca(u,v);
			if(u == v) b[n].push_back((pii){i,1});
			else if(x == v) 
			{
				int t = near(v,u);
				b[L[t]+n-1].push_back((pii){i,R[t]+1});
			}
			else b[R[v]].push_back((pii){i,L[v]});
		}
		ikun.clear();
		F(i,1,n<<1)
		{
			ikun.update(i,a[i].second);
			for(auto p:b[i]) ans[p.first] = ikun.query(p.second);
		}
		F(i,1,q) write(ans[i]),putchar('\n');
	}
	return 0;
}
```


---

## 作者：D2T1 (赞：2)

## 题意

给定一棵 $n$ 个节点的无根树，每个节点有点权，$q$ 次询问，每次询问以 $r$ 为根，$v$ 的子树中任选若干个点点权异或和最大值。

## 题解

首先以 $1$ 为根，对于每个节点求出它的子树的线性基。然后求出 dfn 序，以及 dfn 序的前后缀线性基。

假设这次询问 $v$ 的子树，对于不同的 $r$，答案只可能有三种情况：

- $r=v$，此时答案就是整棵树的答案。
- $r$ 不在 $v$ 的子树中，此时以 $r$ 为根和以 $1$ 为根 $v$ 的子树是相同的，所以答案就是 $v$ 子树的答案。
- $r$ 在 $v$ 的子树中且不为 $v$，这时 $v$ 的子树就会变了。具体地，我们让 $r$ 往上跳，跳 $dep_r-dep_v$ 次会跳到 $v$，那么跳 $dep_r-dep_v-1$ 次到的节点就是 $v$ 的一个子节点，那么现在 $v$ 的子树就是整棵树**除了这个子节点的子树**的部分。学过树剖的都知道，一个节点的子树对应 dfn 序的一个连续段，那么除掉这个子树的其他部分就对应一段前缀加上一段后缀。答案就是对应的前缀线性基和后缀线性基合并后的答案。

时间复杂度 $O(n\log^2a_i)$

```cpp
/*
    name: The Tree Has Fallen!
    id:   CF1778E
    date: 2023/02/01
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int t, n, q, a[N], fat[N][20], dep[N], dfn[N], siz[N], fdfn[N], cnt;
vector<int> g[N];

struct LinearBasis{
	int p[32];
	void ins(int k){
		for(int i = 31; i >= 0; -- i){
			if(!(k&(1<<i))) continue;
			if(!p[i]) return p[i] = k, void();
			k ^= p[i];
		}
		return; 
	}
	void ins(LinearBasis x){
		for(int i = 31; i >= 0; -- i)
			ins(x.p[i]);
	}
	int getmx(){
		int ans = 0;
		for(int i = 31; i >= 0; -- i) ans = max(ans, ans^p[i]);
		return ans;
	}
} s[N], pre[N], suf[N], ans;

void clear(){
	for(int i = 0; i <= n + 1; ++ i){
		g[i].clear();
		dep[i] = siz[i] = dfn[i] = fdfn[i] = 0;
		for(int j = 0; j < 20; ++ j){
			fat[i][j] = 0;
		}
		memset(s[i].p, 0, sizeof(s[i].p));
		memset(pre[i].p, 0, sizeof(pre[i].p));
		memset(suf[i].p, 0, sizeof(suf[i].p));
	}
	cnt = 0;
}

void dfs(int x, int fa){
	dep[x] = dep[fa] + 1;
	dfn[x] = ++ cnt;
	siz[x] = 1;
	s[x].ins(a[x]);
	fdfn[cnt] = x;
	fat[x][0] = fa;
	for(int i = 1; i < 20; ++ i){
		fat[x][i] = fat[fat[x][i-1]][i-1];
	}
	for(int i : g[x]){
		if(i == fa){
			continue;
		}
		dfs(i, x);
		siz[x] += siz[i];
		s[x].ins(s[i]);
	}
}

int jump(int x, int k){
	for(int i = 19; i >= 0; -- i){
		if((k >> i) & 1){
			x = fat[x][i];
		}
	}
	return x;
}

int main(){
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		for(int i = 1; i <= n; ++ i){
			scanf("%d", &a[i]);
		}
		for(int i = 1; i < n; ++ i){
			int u, v;
			scanf("%d%d", &u, &v);
			g[u].push_back(v);
			g[v].push_back(u);
		}
		dfs(1, 0);
		memset(pre[0].p, 0, sizeof(pre[0].p));
		memset(suf[n+1].p, 0, sizeof(suf[n+1].p));
		for(int i = 1; i <= n; ++ i){
			pre[i].ins(a[fdfn[i]]);
			pre[i].ins(pre[i-1]);
		}
		for(int i = n; i >= 1; -- i){
			suf[i].ins(a[fdfn[i]]);
			suf[i].ins(suf[i+1]);
		}
		scanf("%d", &q);
		while(q--){
			int r, v;
			scanf("%d%d", &r, &v);
			if(r == v){
				printf("%d\n", pre[n].getmx());
			} else if(dep[r] <= dep[v] || jump(r, dep[r]-dep[v]) != v){
				printf("%d\n", s[v].getmx());
			} else {
				memset(ans.p, 0, sizeof(ans.p));
				int k = jump(r, dep[r]-dep[v]-1);
				ans.ins(pre[dfn[k]-1]);
				ans.ins(suf[dfn[k]+siz[k]]);
				printf("%d\n", ans.getmx());
			}
		}
		clear();
	}
	return 0;
}

```

---

## 作者：Purslane (赞：1)

# Solution

换根 + 线性基。

先把树当做 $1$ 的有根树。

若 $v$ 不是 $r$ 的祖先，那么 $v$ 的新子树就是原树的子树。

否则，设 $r$ 在 $1$ 树中的是在 $v$ 的儿子 $k$ 的子树中的，那么 $v$ 的子树实际上是原树扣去 $k$ 的子树。

其实可以直接用 DFS 序处理第二种情况。

但是很容易使用线性基合并来维护。

复杂度 $O(n \log^2 V)$。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
int T,n,q,a[MAXN],dep[MAXN],fa[MAXN][20];
struct LB {
	int v[31];
	void insert(int u) {
		roff(i,30,0) if(u&(1<<i)) {
			if(!v[i]) return v[i]=u,void();	
			u^=v[i];
		}
		return ;
	}
	int calc(void) {
		int ans=0;
		roff(i,30,0) if((ans^v[i])>ans) ans^=v[i];
		return ans;	
	}
};
LB operator +(LB A,LB B) {
	ffor(i,0,30) if(B.v[i]) A.insert(B.v[i]);	
	return A;
}
LB sub[MAXN],ot[MAXN];
vector<int> G[MAXN];
void dfs(int u,int f) {
	dep[u]=dep[f]+1,fa[u][0]=f;
	ffor(i,1,19) fa[u][i]=fa[fa[u][i-1]][i-1];
	memset(sub[u].v,0,sizeof(sub[u].v));
	memset(ot[u].v,0,sizeof(ot[u].v));
	sub[u].insert(a[u]);
	for(auto v:G[u]) if(v!=f) dfs(v,u),sub[u]=sub[u]+sub[v];
	return ;
}
void DFS(int u,int f) {
	for(auto v:G[u]) if(v!=f) ot[v]=ot[u],ot[v].insert(a[u]);
	LB pre; memset(pre.v,0,sizeof(pre.v));
	for(auto v:G[u]) if(v!=f) ot[v]=ot[v]+pre,pre=pre+sub[v];
	reverse(G[u].begin(),G[u].end()),memset(pre.v,0,sizeof(pre.v));
	for(auto v:G[u]) if(v!=f) ot[v]=ot[v]+pre,pre=pre+sub[v];
	for(auto v:G[u]) if(v!=f) DFS(v,u);
	return ;
}
int lca(int u,int v) {
	if(dep[u]<dep[v]) swap(u,v);
	int dt=dep[u]-dep[v],id=0;
	while(dt) {
		if(dt&1) u=fa[u][id];
		id++,dt>>=1;
	}
	if(u==v) return u;
	roff(i,19,0) if(fa[u][i]!=fa[v][i]) u=fa[u][i],v=fa[v][i];
	return fa[u][0];
}
int jump(int u,int dt) {
	ffor(i,0,19) if(dt&(1<<i)) u=fa[u][i];
	return u;	
}
int calc(int r,int v) {
	if(r==v) return sub[1].calc();
	int l=lca(r,v);
	if(l!=v) return sub[v].calc();
	r=jump(r,dep[r]-dep[v]-1);
	return ot[r].calc();
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) {
		cin>>n;
		ffor(i,1,n) cin>>a[i];
		ffor(i,1,n) G[i].clear();
		ffor(i,1,n-1) {int u,v;cin>>u>>v,G[u].push_back(v),G[v].push_back(u);}
		dfs(1,0),DFS(1,0);
		cin>>q;
		ffor(i,1,q) {int r,v;cin>>r>>v,cout<<calc(r,v)<<'\n';}
	}
	return 0;
}
```

---

## 作者：QwQcOrZ (赞：1)

咋没人写个单 $\log$ 题解。

求出一个以 $1$ 为根的 dfn 序。询问时讨论一下 $r$ 和 $v$ 的关系，可以将子树定位到 dfn 序的一段区间，或者一段前缀并上一段后缀。

前缀并后缀可以通过将整个序列复制一份，变为一段区间。

现在问题变为查询区间答案。

离线，从左向右扫描整个序列，在右端点处计算答案。

维护一个“最右线性基”，即插入时遇到两个等价的基，我们保留位置靠右的基，然后继续插入另一个基。（具体内容可以参考代码）

若左端点为 $l$，线性基中位置 $\geq l$ 的基所构成的线性基即为这个区间的线性基。

直接在这个线性基里查询即可，时间复杂度 $\mathcal O((n+Q)\log V)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+5;

struct basis {
	int f[30],p[30];
	basis() {
		memset(f,0,sizeof(f));
		memset(p,0,sizeof(p));
	}
	void insert(int pos,int x) {
		for (int i=29;i>=0;i--) {
			if (x>>i&1) {
				if (f[i]) {
					if (pos>p[i]) {
						swap(pos,p[i]);
						swap(x,f[i]);
					}
					x^=f[i];
				} else {
					p[i]=pos;
					f[i]=x;
					return;
				}
			}
		}
	}
	int query(int l) {
		int ret=0;
		for (int i=29;i>=0;i--) {
			if (ret>>i&1) {
				continue;
			}
			if (p[i]>=l) {
				ret^=f[i];
			}
		}
		return ret;
	}
}b;
int n,Q,a[N],dfn[N],ndfn[N],siz[N],cntdfn;
vector<int>e[N],son[N];
void dfs(int now,int father) {
	ndfn[dfn[now]=++cntdfn]=now;
	siz[now]=1;
	for (int to:e[now]) {
		if (to==father) {
			continue;
		}
		dfs(to,now);
		son[now].emplace_back(to);
		siz[now]+=siz[to];
	}
}
int ans[N];
vector<pair<int,int>>q[N+N];
void work() {
	for (int i=1;i<=n+n;i++) {
		q[i].clear();
	}
	cntdfn=0;
	cin>>n;
	for (int i=1;i<=n;i++) {
		cin>>a[i];
		e[i].clear();
		son[i].clear();
	}
	for (int i=1;i<n;i++) {
		int u,v;
		cin>>u>>v;
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}
	dfs(1,0);
	cin>>Q;
	for (int i=1;i<=Q;i++) {
		int r,x;
		cin>>r>>x;
		if (r==x) {
			q[n].emplace_back(1,i);
		} else if (dfn[r]<dfn[x]||dfn[x]+siz[x]<=dfn[r]) {
			q[dfn[x]+siz[x]-1].emplace_back(dfn[x],i);
		} else {
			int p=*--upper_bound(son[x].begin(),son[x].end(),r,[&](int x,int y) {
				return dfn[x]<dfn[y];
			});
			q[dfn[p]-1+n].emplace_back(dfn[p]+siz[p],i);
		}
	}
	b=basis();
	for (int i=1;i<=n+n;i++) {
		b.insert(i,a[ndfn[(i-1)%n+1]]);
		for (auto [l,id]:q[i]) {
			ans[id]=b.query(l);
		}
	}
	for (int i=1;i<=Q;i++) {
		cout<<ans[i]<<"\n";
	}
}

signed main() {
	ios::sync_with_stdio(false),cin.tie(0);
	cout.precision(10),cout.setf(ios::fixed);
	
	int T;
	cin>>T;
	while (T--) {
		work();
	}
	
	return 0;
}
```

---

## 作者：ningago (赞：1)

使用线性基及其可合并性解决此类问题。

考虑经典的换根子树操作：

首先用任意根（默认为 $1$）求出子树线性基。

- 若 $r=v$，则为全局查询。
- 若 $r$ 在 $v$ 的子树内，令 $t$ 为 $1-r$ 路径上 $v$ 的儿子，则为查询 $v$ 的子树除去 $t$ 子树的答案。
- 其余情况，则为和 $1$ 为根相同。

其中 $1,3$ 情况使用 $1$ 为根子树线性基即可，$2$ 情况可使用倍增查询 $t$，维护 dfn 的前后缀线性基进行求解。

时间复杂度 $O((n+m)\log^2A)$。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

#define N 200010

struct Base
{
	int p[32];
	void ins(int x)
	{
		for(int i = 30;~i;i--)
		{
			if(x & (1 << i))
			{
				if(!p[i])
				{
					p[i] = x;
					break;
				}
				else
					x ^= p[i];
			}
		}
	}
	void operator = (const Base &B)
	{
		for(int i = 30;~i;i--)
			p[i] = B.p[i];
	}
	void operator += (const Base &B)
	{
		for(int i = 30;~i;i--)
			ins(B.p[i]);
	}
	int query_max()
	{
		int res = 0;
		for(int i = 30;~i;i--)
		{
			if((res ^ p[i]) > res)
				res ^= p[i];
		}
		return res;
	}
	void clear()
	{
		for(int i = 30;~i;i--)
			p[i] = 0;
	}
};

int h[N],e[N << 1],ne[N << 1],idx;
void add_edge(int x,int y)
{
	ne[++idx] = h[x];
	h[x] = idx;
	e[idx] = y;
}
void add(int x,int y)
{
	add_edge(x,y);
	add_edge(y,x);
}
Base pre[N],suc[N];
int dfn[N],fdfn[N],dfncnt;
Base sum[N];
int a[N],sz[N];

int kfa[N][25];

void dfs(int k,int fa)
{
	dfn[k] = ++dfncnt;
	kfa[k][0] = fa;
	for(int i = 1;i <= 20;i++)
		kfa[k][i] = kfa[kfa[k][i - 1]][i - 1];
	sz[k] = 1;
	fdfn[dfncnt] = k;
	sum[k].ins(a[k]);
	for(int i = h[k];~i;i = ne[i])
	{
		int nx = e[i];
		if(nx == fa)
			continue;
		dfs(nx,k);
		sum[k] += sum[nx];
		sz[k] += sz[nx];
	}
}

int T;
int n,m;

int main()
{
	memset(h,-1,sizeof(h));
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i = 1;i <= n;i++)
			scanf("%d",&a[i]);
		for(int i = 1,x,y;i < n;i++)
		{
			scanf("%d%d",&x,&y);
			add(x,y);
		}
		dfs(1,1);
		pre[0].clear();
		for(int i = 1;i <= n;i++)
		{
			pre[i].ins(a[fdfn[i]]);
			pre[i] += pre[i - 1];
		}
		suc[n + 1].clear();
		for(int i = n;i >= 1;i--)
		{
			suc[i].ins(a[fdfn[i]]);
			suc[i] += suc[i + 1];
		}
		scanf("%d",&m);
		Base now;
		for(int i = 1,r,v;i <= m;i++)
		{
			scanf("%d%d",&r,&v);
			now.clear();
			if(r == v)
				now = pre[n];
			else if(dfn[v] <= dfn[r] && dfn[r] <= dfn[v] + sz[v] - 1)
			{
				int t = r;
				for(int i = 20;~i;i--)
				{
					int f = kfa[t][i];
					if(dfn[v] <= dfn[f] && dfn[f] <= dfn[v] + sz[v] && v != f)
						t = f;
				}
				int L = dfn[t];
				int R = dfn[t] + sz[t] - 1;
				now = pre[L - 1];
				now += suc[R + 1];
				now.ins(a[v]);
			}
			else
				now = sum[v];
			printf("%d\n",now.query_max());
		}
		for(int i = 1;i <= n;i++)
		{
			h[i] = -1;
			pre[i].clear();
			suc[i].clear();
			sum[i].clear();
			dfn[i] = fdfn[i] = 0;
			sz[i] = 0;
		}
		for(int i = 1;i <= idx;i++)
			ne[i] = 0;
		idx = dfncnt = 0;
	}	
	return 0;
}
```

---

## 作者：xfrvq (赞：1)

[$\tt Link$](/problem/CF1778E)。

是这样的，设值域为 $V$，线性基大小为 $O(\log V)$，支持 $O(\log V)$ 时间内插入一个数，以及查询当前选出若干个数可以的最大异或值；$O(\log^2 V)$ 时间复杂度合并两个线性基，方法是把其中一个的每一个数插入到另一个里面。

换根板板，讨论三种情况，不会就看 [$\tt CF916E$](/problem/CF916E)。

然后换根后子树就只有两种情况，一种是原树某个点的子树，一种是全局除了某个点的原树上子树。

第一种情况写个树形 $\tt dp$ 算算子树线性基。第二种情况是全局除掉某个 $\tt dfn$ 区间，可以拆成一个前缀和后缀的合并，预处理前缀、后缀线性基即可。

代码挺好写的。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int T,n,m,a[N],in[N],out[N];
vector<int> G[N];
int dep[N],siz[N],son[N],fa[N];
int dfn[N],pnt[N],top[N],tot;

struct jjj{
	int v[35];
	
	void clr(){ memset(v,0,sizeof v); }
	
	void ins(int x){
		for(int i = 31;~i;--i){
			if(!(x & (1 << i))) continue;
			if(!v[i]){ v[i] = x; break; }
			x ^= v[i];
		}
	}
	
	int qry(){
		int ans = 0;
		for(int i = 31;~i;--i)
			ans = max(ans,ans ^ v[i]);
		return ans;
	}
	
	void mrg(const jjj& _){
		for(int i = 31;~i;--i) ins(_.v[i]);
	}
} pr[N],sf[N],st[N];

jjj mrg(const jjj &a,const jjj &b){
	jjj res = a;
	for(int i = 31;~i;--i) res.ins(b.v[i]);
	return res;
}

void dfs1(int u,int ft){
	st[u].clr(); st[u].ins(a[u]);
	dep[u] = dep[fa[u] = ft] + 1;
	siz[u] = 1; son[u] = 0;
	for(int v : G[u]) if(v != ft){
		dfs1(v,u);
		siz[u] += siz[v];
		if(siz[v] > siz[son[u]]) son[u] = v;
		st[u].mrg(st[v]);
	}
}

void dfs2(int u,int tp){
	top[u] = tp; pnt[dfn[u] = ++tot] = u;
	if(son[u]) dfs2(son[u],tp);
	for(int v : G[u]) if(v != son[u] && v != fa[u]) dfs2(v,v);
	G[u].clear(); G[u].shrink_to_fit();
}

int lca(int x,int y){
	while(top[x] != top[y]){
		if(dep[top[x]] < dep[top[y]]) swap(x,y);
		x = fa[top[x]];
	}
	return dep[x] < dep[y] ? x : y;
}

int sonlca(int x,int y){
    while(top[x] != top[y]){
        if(dep[top[x]] < dep[top[y]]) swap(x,y);
        if(fa[top[x]] == y) return top[x];
        x = fa[top[x]];
    }
    return son[dep[x] < dep[y] ? x : y];
}

void solve(){
	scanf("%d",&n);
	for(int i = 1;i <= n;++i) scanf("%d",a + i);
	for(int i = 1,u,v;i < n;++i){
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	tot = 0; dfs1(1,0); dfs2(1,1);
	for(int i = 1;i <= n;++i)
		pr[i] = pr[i - 1],pr[i].ins(a[pnt[i]]);
	sf[n + 1].clr();
	for(int i = n;i >= 1;--i)
		sf[i] = sf[i + 1],sf[i].ins(a[pnt[i]]);
	for(int i = 1;i <= n;++i){
		in[i] = st[i].qry();
		out[i] = mrg(pr[dfn[i] - 1],sf[dfn[i] + siz[i]]).qry();
	}
	scanf("%d",&m);
	for(int x,u;m--;){
		scanf("%d%d",&x,&u);
		if(x == u) printf("%d\n",in[1]);
		else if(lca(x,u) != u) printf("%d\n",in[u]);
		else printf("%d\n",out[sonlca(u,x)]);
	}
}

int main(){ for(scanf("%d",&T);T--;solve()); return 0; }
```

---

## 作者：nullqtr_pwp (赞：0)

从一堆数里面选任意个数使得它们的异或和最大，这是**线性基**板子。

考虑没有换根操作的影响，我们将 $v$ 的子树的所有节点的点权插入 $l_v$ 的线性基中。答案显然是 $l_v$ 的贪心。求出最开始 $l_i$ 可以通过该节点与子结点线性基合并来求。

现在考虑换根的影响，手模一下容易发现：

$r=v$ 时或 $v$ **不在**原树 $1\rightarrow r$ 上的路径时，容易发现 $v$ 的子树的结点不变，答案仍是 $l_v$ 的贪心。

考虑 $r\ne v$ 且 $v$ **在**原树 $1\rightarrow r$ 上的路径的情况。

找点 $u$ 是 $v$ 的其中一个子结点且 $u$ **在**原树 $1\rightarrow r$ 上的路径上。容易发现，$v$ 的子树的结点是全树内节点**除去** $u$ 的子树的节点。找 $u$ 这一步用树上倍增可以做到 $O(\log n)$ 的复杂度。

这个怎么做到呢？注意到子树内的 dfs 序是连续的。令点 $i$ 的 dfs 序是 $d_i$，$i$ 的子树的大小是 $s_i$。那么 $u$ 的子树的节点的 dfs 序是 $[d_u,s_u+d_u-1]$。

不算这一段区间的话，可以求 dfs 序为 $[1,d_u-1]\cup[s_u+d_u,n]$ 的信息。考虑到多组询问，预处理这个前缀和后缀即可。

时间复杂度 $O(n\log n\log \max a_i)$。

友情提示，注意清空树上倍增的信息。我因为这玩意 WA 了 $17$ 发。
```cpp
const int maxn=309309;
vector<int>g[maxn];
namespace linear_basis{
	struct lmx{
		int p[32];
		void insert(int x){ dF(i,30,0) if(x&(1<<i)){ if(!p[i]) return p[i]=x,void();x^=p[i];}}
		int query(){ int rt=0; dF(i,30,0) rt=max(rt,rt^p[i]); return rt;}
		void clear(){ memset(p,0,sizeof(p)); }
		void output(){ F(i,0,30) printf("%d ",p[i]); HH;}
	}l[maxn],p[maxn],s[maxn];
	lmx operator+(lmx a,lmx b){
		lmx fqd=a;
		dF(i,30,0) if(b.p[i]) fqd.insert(b.p[i]);
		return fqd;
	}
};
using namespace linear_basis;
int f[maxn][20],a[maxn],d[maxn],lg[maxn],n,tim,sz[maxn],dfn[maxn],rev[maxn];
void dfs(int u,int fa){
	l[u].insert(a[u]);
	d[u]=d[fa]+1;
	dfn[u]=++tim;
	rev[tim]=u;
	sz[u]=1;
	f[u][0]=fa;
	for(int i=1;(1<<i)<=d[u];i++) f[u][i]=f[f[u][i-1]][i-1];
	for(int v:g[u]) 
		if(v!=fa){
			dfs(v,u);
			l[u]=l[u]+l[v];
			sz[u]+=sz[v];
		}
}
int lca(int x,int y) {
    if(d[x]<d[y])swap(x,y);
    dF(i,lg[d[x]],0) if(d[f[x][i]]>=d[y]) x=f[x][i];
    if(x==y) return x;
    dF(i,lg[d[x]],0) if(f[x][i]^f[y][i]) x=f[x][i],y=f[y][i];
    return f[x][0];
}
bool fl=0;
void solve(int u,int v){
	if(u==v) return printf("%d\n",l[1].query()),void();
	if(lca(u,v)==v){
		dF(i,lg[n],0) if(dfn[f[u][i]]>=dfn[v]&&dfn[f[u][i]]<=dfn[v]+sz[v]&&f[u][i]^v) u=f[u][i];
		lmx ans; ans.clear();
		ans=ans+p[dfn[u]-1];
		ans=ans+s[dfn[u]+sz[u]];
		ans.insert(a[v]);
		return printf("%d\n",ans.query()),void();
	}
	else return printf("%d\n",l[v].query()),void();
}
void Solve(){
	n=read();
	tim=0;
	F(i,1,n) a[i]=read(),g[i].clear(),l[i].clear(),p[i].clear(),s[i].clear(),sz[i]=0;
	F(i,1,n) F(j,0,19) f[i][j]=0;
	F(i,1,n-1){
		int u=read(),v=read();
		g[u].pb(v);
		g[v].pb(u);
	}
	dfs(1,1);
	p[0].clear();
	s[n+1].clear();
	F(i,1,n){
		p[i].insert(a[rev[i]]);
		p[i]=p[i-1]+p[i];
	}
	dF(i,n,1){
		s[i].insert(a[rev[i]]);
		s[i]=s[i+1]+s[i];
	}
	int t=read();
	while(t--){
		int u=read(),v=read();
		solve(u,v);
	}
}
```


---

## 作者：E1_de5truct0r (赞：0)

来一个最暴力的线性基题解。

首先我们可以发现，如果不换根，我们对每个节点维护其子树内的线性基即可。对第 $i$ 个节点，我们不妨记这个线性基为 $a_i$。

然后考虑换根。假设我们以 $1$ 为根，这个时候换根到了 $z$。我们点 $x$ 的子树变化：

1. $x$ 在以 $1$ 为根意义下，$z$ 子树内：显然 $x$ 的子树还是原来的子树，答案不变。

2. $x$ 在以 $1$ 为根意义下 $z$ 子树外，且不是 $z$ 的祖先：这个时候 $x$ 向上走到 $z$ 的路径就是 $x \rightarrow \text{LCA}(x,z) \rightarrow z$，那么 $x$ 的子树还是原来的子树，答案不变。

3. $x$ 在以 $1$ 为根意义下，是 $z$ 的祖先：

	![](https://cdn.luogu.com.cn/upload/image_hosting/b2klslb6.png)
    
	容易看出这个就是整个树，挖掉 $z$ 到 $x$ 路径上最后一个点 $y$ 的子树之后，组成的线性基的答案。我们不妨对点 $y$ 把这个答案记为 $b_y$。
    
4. $x=z$：整个树组成的线性基取最大，就是答案。

然后我们考虑分别维护 $a_i$ 和 $b_i$。以下令 $\oplus$ 符号表示线性基的合并运算，$\bigoplus$ 表示连续合并运算：

$a_i$ 很简单，不难发现有这个递推式子：

$$a_i=w_i \oplus \bigoplus\limits_{v \in son_i} a_v$$

$b_i$ 略微复杂，但我们还是不难推出递推式子：

$$b_v=b_{i} \oplus \bigoplus_{x \in son_i \text{并且} x \neq v}a_{x}$$

$a_i$ 直接维护即可，$b_i$ 后面那块可以直接拆成前缀线性基和后缀线性基。然后每次对输入的 $x,y$，倍增的判断祖先关系即可。

复杂度 $O(n \log^2 W)$，$W$ 为值域。

有点小卡常，建议交 C++20。不保证每次都过，但是一定可以过。

## Code

```cpp
#include <bits/stdc++.h>
#define _cst const
#define _IfD long long
#define _siz 20
char buf[1<<_siz],buffer[1<<_siz],*p1=buf,*p2=buf,c=' ';
int op1=-1; _cst int op2=(1<<_siz)-1;
inline char gc(){return (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<_siz,stdin)),p1==p2?EOF:*p1++);}
inline void flush(){fwrite(buffer,1,op1+1,stdout),op1=-1;}
inline void pc(_cst char &x){if(op1==op2)flush();buffer[++op1]=x;}
template<typename T>void read(T &w){
	w=0;bool f=1;char ch=gc();
	for(;ch<=32;ch=gc()); if(ch=='-')f=0;
	for(;'0'<=ch && ch<='9';ch=gc()) w=(w<<1)+(w<<3)+(ch^48);
	w=f?w:-w;
}template<typename T,typename ...Arg>void read(T &w,Arg &...arg){
	read(w); read(arg...);
}template<typename T>void wrt(T x){
  	if(x<0) pc('-'),x=-x;
	if(x>9) wrt(x/10);
	pc(x%10|48);
}template<typename T>void write(T x){
	wrt(x); pc(c);
}template<typename T,typename ...Arg>void write(T x,Arg ...arg){
	write(x); write(arg...);
}inline _IfD pow_10(_IfD x){
    _IfD base=10,ans=1;
    while(x) ans*=((x&1)?base:1),base*=base,x>>=1;
    return ans;
}template<typename T>void readd(T &w){
    w=0; _IfD x=0,cnt=0; bool f=1; char ch=gc();
    for(;ch<=32;ch=gc()); if(ch=='-')f=0;
    for(;'0'<=ch && ch<='9';ch=gc()) x=(x<<1)+(x<<3)+(ch^48);
    w=(T)(f?x:-x);
    if(ch!='.') return; x=0,ch=gc();
    for(;'0'<=ch && ch<='9';ch=gc(),++cnt) x=(x<<1)+(x<<3)+(ch^48);
    T tmp=(T)(x/(T)pow_10(cnt));
    w=w+(T)(f?tmp:-tmp);
}template<typename T,typename ...Arg>void readd(T &w,Arg &...arg){
	readd(w); readd(arg...);
}
template<typename T>inline T qmax(_cst T &a,_cst T &b){return a>b?a:b;}
template<typename T,typename ...Arg>inline T qmax(_cst T &a,_cst T &b,_cst Arg &...arg){return qmax(a,qmax(b,arg...));}
template<typename T>inline T qmin(_cst T &a,_cst T &b){return a<b?a:b;}
template<typename T,typename ...Arg>inline T qmin(_cst T &a,_cst T &b,_cst Arg &...arg){return qmin(a,qmin(b,arg...));}
template<typename T>inline void qswap(T &a,T &b){a+=b,b=a-b,a-=b;}

using namespace std;

#define int long long

const int MAXN=200005,N=31;

struct Basis{
	int h[N];
	Basis(){memset(h,0,sizeof(h));}
	void clear(){memset(h,0,sizeof(h));}
	void insert(int x){
		for(int j=N-1;j>=0;j--){
			if((x>>j)&1) 
				if(!h[j]){h[j]=x; break;}
				else x^=h[j];
		}
	}
	int qry(){
		int ans=0;
		for(int j=N-1;j>=0;j--)
			if((ans^h[j])>ans) ans^=h[j];
		return ans;
	}
}a[MAXN],b[MAXN];
int w[MAXN];
vector<Basis> pre[MAXN],suf[MAXN];
vector<int> E[MAXN];
const Basis operator + (const Basis &x,const Basis &y){
	Basis z;
	for(int j=N-1;j>=0;j--) z.insert(x.h[j]);
	for(int j=N-1;j>=0;j--) z.insert(y.h[j]);
	return z;
}

int f[MAXN][20],dep[MAXN];

void dfs(int u,int fa){
	f[u][0]=fa; dep[u]=dep[fa]+1;
	int p=-1; a[u].insert(w[u]);
	for(int i=0;i<E[u].size();i++){
		int v=E[u][i];
		if(v==fa){p=i;continue;}
		dfs(v,u);
		a[u]=a[u]+a[v];
	}
	if(p!=-1) swap(E[u][p],E[u][0]);
	else E[u].insert(E[u].begin(),0);
}
void dfs1(int u,int fa){
	pre[u].resize(E[u].size()+1);
	suf[u].resize(E[u].size()+1);
	suf[u][E[u].size()].clear();
	for(int i=1;i<E[u].size();i++){
		int v=E[u][i];
		pre[u][i]=pre[u][i-1]+a[v];
	}
	for(int i=E[u].size()-1;i>0;i--){
		int v=E[u][i];
		suf[u][i]=suf[u][i+1]+a[v];
	}
	for(int i=1;i<E[u].size();i++){
		int v=E[u][i];
		b[v]=b[u]+pre[u][i-1]+suf[u][i+1];
		b[v].insert(w[u]);
		dfs1(v,u);
	}
}
int check(int u,int v){
	if(dep[v]>dep[u]) return 0;
	int tmp=dep[u]-dep[v],U=u;
	for(int j=0;j<20;j++) if(tmp>>j&1) u=f[u][j];
	if(u!=v) return 0; tmp--; u=U;
	for(int j=0;j<20;j++) if(tmp>>j&1) u=f[u][j];
	return u;
}

void solve(){
	int n; read(n);
	for(int i=1;i<=n;i++) a[i].clear(),b[i].clear(),E[i].clear(),pre[i].resize(0),suf[i].resize(0);
	for(int i=1;i<=n;i++) read(w[i]);
	for(int i=1;i<n;i++){
		int u,v; read(u,v);
		E[u].push_back(v);
		E[v].push_back(u);
	}
	dfs(1,0); dfs1(1,0);
	for(int j=1;j<20;j++) for(int i=1;i<=n;i++) f[i][j]=f[f[i][j-1]][j-1];
	int q; read(q);
	while(q--){
		int x,y; read(x,y);
		if(x==y){
			wrt(a[1].qry()),pc(10);
		}else{
			int tmp=check(x,y); 
	//		cout<<x<<' '<<y<<' '<<tmp<<'\n';
			if(!tmp) wrt(a[y].qry()),pc(10);
			else wrt(b[tmp].qry()),pc(10);
		}
	}
}

signed main(){
	int T; read(T);
	while(T--) solve();
	return flush(),0;
}
```

---

## 作者：Smallbasic (赞：0)

不用那么麻烦的分讨，直接换根是可以做的。

首先选数异或和最大是显然可以线性基，我们的任务就是考虑维护子树线性基。

把询问离线，先 dfs 一遍求出子树线性基，再 dfs 一遍求以每个点为根的答案。第二遍 dfs 维护子树线性基的方法和换根 dp 类似。假设要把根 $r$ 的儿子 $v$ 换到根上，就 swap 一下 $r,v$ 的线性基，再求出 $r$ 没有儿子 $v$ 的线性基即可，这个预处理一下前缀和后缀的线性基可以很方便求出来。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

inline int read() {
	register int s = 0, f = 1; register char ch = getchar();
	while (!isdigit(ch)) f = (ch == '-' ? -1 : 1), ch = getchar();
	while (isdigit(ch)) s = (s * 10) + (ch & 15), ch = getchar();
	return s * f;
}

inline void otp(int x) {
	(x >= 10) ? otp(x / 10), putchar((x % 10) ^ 48) : putchar(x ^ 48);
}

vector<int> nxt[N];

struct base {
	vector<int> bs;
	inline base() { bs.resize(33, 0); for (int &i : bs) i = 0; }
	inline void clear() { bs.resize(33, 0); for (int &i : bs) i = 0; }
	inline void insert(int x) {
		for (int i = 31; ~i; --i) {
			if (!((x >> i))) continue;
			if (!bs[i]) { bs[i] = x; break; }
			x ^= bs[i];
		}
	}
	inline int query() {
		int res = 0;
		for (int i = 31; ~i; --i)
			if ((res ^ bs[i]) > res) res ^= bs[i];
		return res;
	}
	inline void merge(const base &b) {
		for (int x : b.bs) if (x) insert(x);
	}
} tr[N];

//inline void print(int x) {
//	sort(tr[x].bs.begin(), tr[x].bs.end());
//	cerr << "V : " << x << " = ";
//	for (int i : tr[x].bs) 
//		if (i) cerr << i << ' ';
//	cerr << endl;
//}

int q[N], ans[N], val[N], T, n, m;
vector<int> ask[N];

inline void dfs(int now, int fa) {
	tr[now].insert(val[now]);
	for (int i : nxt[now]) {
		if (i != fa) {
			dfs(i, now);
			tr[now].merge(tr[i]);
		}
	}
}

inline void calc(int now, int fa) {
	for (int i : ask[now])
		ans[i] = tr[q[i]].query();
	base pre, tmp = tr[now], qwq;
	vector<base> suf; suf.resize(nxt[now].size());
	for (int i = nxt[now].size() - 1; ~i; --i) {
		if (i == nxt[now].size() - 1) {
			if (nxt[now][i] != fa) suf[i] = tr[nxt[now][i]];
		} else {
			suf[i] = suf[i + 1];
			if (nxt[now][i] != fa) suf[i].merge(tr[nxt[now][i]]);
		}
	} pre.insert(val[now]);
	if (fa) pre.merge(tr[fa]);
	for (int i = 0; i < nxt[now].size(); ++i) {
		int v = nxt[now][i];
		if (v == fa) continue;
		tr[now] = pre; pre.merge(tr[v]);
		if (i < nxt[now].size() - 1) tr[now].merge(suf[i + 1]);
		qwq = tr[v]; tr[v] = tmp;
		calc(v, now);
		tr[v] = qwq; tr[now] = tmp;
	}
}

int main() {
//	freopen("qwq.txt", "r", stdin);
	T = read();
	while (T--) {
		n = read();
		for (int i = 1; i <= n; ++i) val[i] = read();
		for (int i = 1, u, v; i < n; ++i) {
			u = read(); v = read();
			nxt[u].push_back(v); nxt[v].push_back(u);
		} dfs(1, 0);
		m = read();
		for (int i = 1, x; i <= m; ++i) {
			x = read(); q[i] = read();
			ask[x].push_back(i);
		} calc(1, 0);
		for (int i = 1; i <= m; ++i) otp(ans[i]), putchar('\n');
		for (int i = 1; i <= n; ++i) {
			ask[i].clear();
			nxt[i].clear();
			tr[i].clear();
		}
	} return 0;
}
```

---

## 作者：hgzxwzf (赞：0)

## [CF1778E](https://www.luogu.com.cn/problem/CF1778E)
看到选择一些数使得这些数的异或值最大，那肯定是线性基没跑了。

不妨假设一开始根为 $1$ 号点。

不难发现如果 $r$ 不在 $v$ 的子树内，那么在以 $r$ 为根的树中 $v$ 的子树和在以 $1$ 号点为根时一样，否则假设 $x$ 为既是 $r$ 的祖先又是 $v$ 的儿子的节点，那么在以 $r$ 为根的树中 $v$ 的子树就是除去以 $1$ 根时 $x$ 子树内节点以外的所有点。

第一种情况很好处理，一遍 dfs 就可以得到每个子树内所有节点权值构成的线性基。

对于第二种情况，可以用 dfs 序解决，我们知道一棵子树内节点的 dfs 序是连续的，那么删去一棵子树就相当于删去一段区间，剩下了一个前缀和后缀，所以维护前后缀线性基即可。

### Code
```cpp
const int N=2e5+10;

int a[N],idx,dfn[N],son[N][35],pre[N][35],suf[N][35],dep[N],fa[N][25],out[N],node[N];
vector<int>e[N];

void Insert(int *st,int x)
{
	per(i,0,30)
		if(x>>i&1)
		{
			if(st[i]) x^=st[i];
			else {st[i]=x;return ;}
		}
}

void merge(int *a,int *b)
{
	rep(i,0,30)
		if(b[i]) Insert(a,b[i]);
}

void dfs(int cur)
{
	rep(i,0,30) son[cur][i]=0;
	Insert(son[cur],a[cur]);
	dfn[cur]=++idx;
	node[idx]=cur;
	rep(k,0,(int) e[cur].size()-1)
	{
		int nt=e[cur][k];
		if(nt==fa[cur][0]) continue;
		fa[nt][0]=cur;
		dep[nt]=dep[cur]+1;
		dfs(nt);
		merge(son[cur],son[nt]);
	}
	out[cur]=idx;
}

int get_mx(int *st)
{
	int ans=0;
	per(i,0,30)
		ans=max(ans,ans^st[i]);
	return ans;
}

int st[35];

int main()
{
//	freopen("in","r",stdin);
//	freopen("out","w",stdout);
	int T;
	cin>>T;
	while(T--)
	{
		int n;
		cin>>n;
		rep(i,1,n) e[i].clear();
		rep(i,1,n)
			rep(j,0,30)
				pre[i][j]=suf[i][j]=0;
		rep(i,1,n) cin>>a[i];
		rep(i,1,n-1)
		{
			int u,v;
			cin>>u>>v;
			e[u].push_back(v);
			e[v].push_back(u);
		}
		idx=0;
		dep[1]=1;
		dfs(1);
		Insert(pre[1],a[node[1]]);
		Insert(suf[n],a[node[n]]);
		rep(i,2,n)
		{
			rep(j,0,30) pre[i][j]=pre[i-1][j];
			Insert(pre[i],a[node[i]]);
		}
		per(i,1,n-1)
		{
			rep(j,0,30) suf[i][j]=suf[i+1][j];
			Insert(suf[i],a[node[i]]);
		}
		rep(j,1,20)
			rep(i,1,n)
				fa[i][j]=fa[fa[i][j-1]][j-1];
		int q;
		cin>>q;
		while(q--)
		{
			int r,v;
			cin>>r>>v;
			if(dfn[r]<dfn[v]||dfn[r]>out[v])
			{
				cout<<get_mx(son[v])<<endl;
			}
			else if(r!=v)
			{
				per(i,0,20) if(dep[fa[r][i]]>dep[v]) r=fa[r][i];
				rep(i,0,30) st[i]=pre[dfn[r]-1][i];
				if(out[r]<n) merge(st,suf[out[r]+1]);
				cout<<get_mx(st)<<endl;
			}
			else cout<<get_mx(son[1])<<endl;
		}
	}
	return 0;
}
```


---

