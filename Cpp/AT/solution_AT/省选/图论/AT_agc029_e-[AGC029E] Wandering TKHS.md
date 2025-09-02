# [AGC029E] Wandering TKHS

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc029/tasks/agc029_e

高橋君の会社は $ N $ 個の部屋からなり、各部屋には $ 1 $ から $ N $ の番号が割り振られています。 また、$ N-1 $ 本の通路があり、$ i $ 番目の通路は部屋 $ a_i $ と部屋 $ b_i $ を繋いでいます。 どの $ 2 $ つの部屋の間もこれらの通路のみを通って移動できることが分かっています。

今高橋君はある部屋に迷い込んでしまいました。この部屋を $ r $ とします。 そこで、高橋君は自分の部屋である部屋 $ 1 $ に戻るために、以下の方法で移動することを繰り返すことにしました。

- 今まで訪れた部屋に隣接する部屋の中でまだ訪れていない部屋の内、番号が一番小さい部屋に移動する。

部屋 $ 1 $ に戻るまでに行う必要のある移動の回数を $ c_r $ とします。 $ c_2,c_3,...,c_N $ をすべて求めてください。 ただし、$ 1 $ 回の移動でいくつの通路を通るとしても、移動は $ 1 $ 回として数えられることに注意してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ a_i,b_i\ \leq\ N $
- $ a_i\ \neq\ b_i $
- 入力で与えられるグラフは木である。

### Sample Explanation 1

例えば部屋 $ 2 $ に迷い込んでいた場合、高橋君は以下のように移動します。 - 部屋 $ 6 $ に移動する。 - 部屋 $ 3 $ に移動する。 - 部屋 $ 4 $ に移動する。 - 部屋 $ 5 $ に移動する。 - 部屋 $ 1 $ に移動する。

## 样例 #1

### 输入

```
6
1 5
5 6
6 2
6 3
6 4```

### 输出

```
5 5 5 1 5```

## 样例 #2

### 输入

```
6
1 2
2 3
3 4
4 5
5 6```

### 输出

```
1 2 3 4 5```

## 样例 #3

### 输入

```
10
1 5
5 6
6 10
6 4
10 3
10 8
8 2
4 7
4 9```

### 输出

```
7 5 3 1 3 4 7 4 5```

# 题解

## 作者：gyh20 (赞：19)

发一个 $O(n)$ 的题解。

问题可以看作对于每一个 $x$，计算它对哪些 $y$ 有贡献。

令 $z=lca(x,y)$。

首先，在 $x$ 到 $z$ 之前一定不会到 $y$，故可以把问题转化到 $z$ 上，视为 $z$ 已被选。

此时，$y$ 能被选当且仅当 $y$ 到 $z$ 的路径最大值（包括 $y$ 不包括 $z$）小于 $z$ 到根的路径最大值（不包括 $z$ 也不包括根），因为到根之前必定会经过这些点，而若其中的最大值是下一个，则一定先会走到 $y$ 所在的子树。

进一步考虑，若 $z$ 的父亲合法，则 $z$ 一定合法，因为下半部分的路径最大值只会减小，上半部分的路径最大值只会增加，所以说，我们只用找到深度最小的 $z$ 即可。

这个东西很好直接用数据结构维护，但由于有些麻烦，且题目中还有未利用的条件，这里继续介绍 $O(n)$ 的做法。

对于每一个点 $y$，观察它到根的路径最大值 $A$，若 $z$ 选取在 $A$ 的下方，则上方一定大于下方，若 $z$ 选取在 $A$ 的上方，则下方一定大于上方。

唯一的问题就是 $A$ 这个位置能否被选。

记录一下路径次大值，判断在 $A$ 上方还是下方即可。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int n,head[200002],dfn[200002],c[200002],cnt,siz[200002],a[200002],tim,b[200002],v[200002],fr[200002];
struct edge{int to,next;}e[400002];
inline void add(re int x,re int y){e[++cnt]=(edge){y,head[x]},head[x]=cnt;}
inline void dfs(re int x,re int y){
	dfn[x]=++tim,a[x]=a[y],b[x]=b[y],siz[x]=1;
	if(x>a[x])b[x]=a[x],a[x]=x,fr[x]=x;
	else if(x>b[x])b[x]=x;
	if(dfn[b[x]]>dfn[a[x]])++v[fr[x]];
	else ++v[a[x]];
	for(re int i=head[x];i;i=e[i].next)
		if(e[i].to^y)fr[e[i].to]=(a[x]==x?e[i].to:fr[x]),dfs(e[i].to,x),siz[x]+=siz[e[i].to];
}
int main(){
	n=read();
	for(re int i=1,x,y;i<n;++i)x=read(),y=read(),add(x,y),add(y,x);
	dfs(1,1);
	for(re int i=2;i<=n;++i)c[dfn[i]]+=v[i],c[dfn[i]+siz[i]]-=v[i];
	for(re int i=2;i<=n;++i)c[i]+=c[i-1];
	for(re int i=2;i<=n;++i)printf("%d ",c[dfn[i]]);
}
```


---

## 作者：FZzzz (赞：9)

自然考虑 $u$ 走到根的过程中会不会经过 $v$。令 $w$ 为 $u$ 和 $v$ 的 lca，那 $u$ 必然是先走到 $w$ 再走到 $v$。容易发现 $w$ 会经过 $v$ 的条件为：$w$ 到根的最大值（不包含 $w$）大于 $w$ 到 $v$ 的最大值（也不包含 $w$）。

考虑 $v$ 到根的最大值 $x$。发现 $x$ 上面的所有点都是不满足条件的，而 $x$ 到 $v$（不包括 $x$）的所有点都是满足条件的。$x$ 满不满足条件呢？发现只需要记录 $v$ 到 $x$ 上的次大值，然后判断它和 $x$ 的位置关系即可。

那么现在我们发现：每个节点能贡献到的节点是一个子树。使用差分维护即可，时间复杂度 $O(n)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll readint(){
	ll x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c)&&c!='-') c=getchar();
	if(c=='-'){
		f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
const int maxn=2e5+5;
int n;
vector<int> g[maxn];
int fa[maxn],dep[maxn],son[maxn],c[maxn];
void dfs1(int u,int mx,int mx2){
	dep[u]=dep[fa[u]]+1;
	if(u>mx){
		mx2=mx;
		mx=u;
	}
	else mx2=max(mx2,u);
	if(u>1) c[dep[mx2]<dep[mx]?mx:son[mx]]++;
	for(int v:g[u]) if(v!=fa[u]){
		fa[v]=u;
		son[u]=v;
		dfs1(v,mx,mx2);
	}
}
void dfs2(int u){
	c[u]+=c[fa[u]];
	for(int v:g[u]) if(v!=fa[u]) dfs2(v);
}
int main(){
	#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	#endif
	n=readint();
	for(int i=1;i<n;i++){
		int a,b;
		a=readint();
		b=readint();
		g[a].push_back(b);
		g[b].push_back(a);
	}
	dfs1(1,0,0);
	dfs2(1);
	for(int i=2;i<=n;i++) printf("%d ",c[i]);
	#ifdef LOCAL
	fprintf(stderr,"%f\n",1.0*clock()/CLOCKS_PER_SEC);
	#endif
	return 0;
}
```
~~看起来每一步都很显然但是放一起就是一步都不会.jpg~~

---

## 作者：x义x (赞：9)

首先，你可以把问题想象成是往一个容器中注水，问何时能到达 $1$ 号点。

**观察 1.** 有一个点很难越过，它是 $n$。直接不断按最大元素分治即可得到 $O(n^2)$ 的复杂度。

但是这个思路不是很好扩展。继续考虑。

**观察 2.** $r$ 到达 $1$ 时必须先越过 $fa(r)\rightarrow 1$ 上的最大值 $M(r)$。这之后的行为和 $M(r)$ 到达 $1$ 的行为几乎相同，但是不会继续扩展 $M(r)$ 的 $r$ 所在方向的子树：因为它已经被一圈高于 $M(r)$ 的无法越过的墙围起来了。

虽然以上思路还是不很好做但至少给了一点启示。

设 $Q(u, x)$ 为从 $u$ 出发，只走 $\le x$ 的点，能走到多少 $u$ 的子树中的点（不包括 $u$）。我们得到以下做法：

- 若 $r>M\circ fa(r)$，则 $r$ 和 $fa(r)$ 的唯一区别就只是 $r$ 会扩展自己所在子树，而且会且只会扩展到大小为 $M(r)$。于是有

$$
c(r)=c\circ fa(r)+Q(r,M(r))+1
$$

- 否则 $r<M\circ fa(r)$，则 $r$ 和 $fa(r)$ 的区别是 $r$ 在和 $fa(r)$ 等价之前要多越过 $fa(r)$，具体来说

$$
c(r)=c\circ fa(r)+Q(r,M(r))-Q(r,M\circ fa(r))
$$

那么现在的问题只剩下求 $Q(r,M(r)),Q(r,M\circ fa(r))$ 了。可以用线段树合并，但是其实记忆化爆搜就可以：

一个点可能被搜到的是 $M(r), Mfa(r), Mfafa(r), ...$。

- 如果 $M(r) > Mfa(r)$，也就是说 $fa(r)$ 很大，那么 $Mfafa(r)$ 之后的这些就搜不进来了；

- 否则只能是 $M(r) = Mfa(r)$，那么需要的值不会变多。

于是一个点所需要的值最多只有 $3$ 个。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn = 200005;

int n;
vector<int> g[maxn];
int fa[maxn], M[maxn];
void init(int x) {
	M[x] = max(M[fa[x]], fa[x]);
	for(int y : g[x]) if(y != fa[x])
		fa[y] = x, init(y);
}
map<int, int> Q[maxn];
int getQ(int x, int v) {
	if(Q[x].count(v)) return Q[x][v];
	int ans = 1;
	for(int y : g[x]) if(y != fa[x] && y <= v) ans += getQ(y, v);
	return Q[x][v] = ans;
}

int f[maxn];
void solve(int x) {
	if(x == 1) f[x] = 0;
	else if(x > M[fa[x]]) f[x] = f[fa[x]] + Q[x][M[x]];
	else f[x] = f[fa[x]] + Q[x][M[x]] - Q[x][M[fa[x]]];
	for(int y : g[x]) if(y != fa[x]) solve(y);
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; i++) {
		int u, v; scanf("%d%d", &u, &v);
		g[u].push_back(v), g[v].push_back(u);
	}
	init(1);
	for(int i = 1; i <= n; i++) getQ(i, M[i]), getQ(i, M[fa[i]]);
	solve(1);
	for(int i = 2; i <= n; i++) printf("%d ", f[i]);
}
```

---

## 作者：pigstd (赞：6)

vp 的时候没调完……吐了。

考虑点 $u$ 时候的答案，设点 $u$ 到点 $1$ 所经过的编号最大的点（不包括本身）是 $p_u$，在到达过 $p_u$ 之前，所有编号 $< p_u$ 的点都会被经过，这意味着若 $u<p_u$，那么点 $u$ 的联通块中所有的点都会被经过，否则点 $u$ 到 $p_u$ 的前一级祖先中的联通块，以及 $u$ 的所有儿子的联通块，都会被经过，然后到了点 $p_u$ 之后，答案并不是简单的加上 $p_u$ 的答案，因为你在 $p_u$ 时候的答案与原来的点本身还会有算重，算重的部分就是对于所有 $<p_{p_u}$ 的点的联通块中的连通块大小。

然后你全部离线下来然后转换成加点用并查集维护就好了。

[code](https://atcoder.jp/contests/agc029/submissions/27904871)。

---

## 作者：feecle6418 (赞：3)

*没有思维能力怎么做 AGC？数据结构来凑。*

首先有一个显然的结论，都不能说性质，因为过于显然……

> 只要从 $y$ 开始扩展到了 $x$（$y$ 在 $x$ 子树中），就一定会扩展到以 $x$ 为根的、所有数都小于等于 $x$ 到 $1$ 上路径最大值的连通块。

有了这个结论就可以把这题做出来了！！首先尝试把问题数据结构化，即让它形如“给一棵树，有一些询问，每次询问是……”。

把询问设定为：给定 $x,k$，求出满足以下条件的 $y$ 的数量（记为 $Q(x,k)$）：

1. $y$ 在 $x$ 子树中。
2. $y\to x$ 路径上所有点小于等于 $k$。

那么原问题可以写为：

> 从 1 开始 dfs 整棵树，记录目前链上的最大值和 $cur$，设 $1$ 到 $p$ 的最大值是 $mx_p$。到 $x$ 时把 $cur$ 加上 $Q(x,mx_x)$，减去 $Q(fa_x,mx_{fa_x})$。求出每个点的 $cur$。

现在只需要快速求 $Q$。离线询问，按照 $x$ 编号递增顺序加边，加边的时候合并连通块，需要支持查询连通块内在子树内的数的个数，以 dfs 序为下标做线段树合并即可。

时间复杂度：$O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Query{
	int x,l,r,dlt,id;
};
#define size Size
int n,ans[200005],root[200005],c[4000005][2],s[4000005],size[200005],sign,dfn[200005],tot,f[200005];
vector<int> g[200005];
vector<Query> Q[200005];
void Upd(int &p,int l,int r,int x,int y){
	if(!p)p=++tot;
	s[p]+=y;
	if(l==r)return ;
	int mid=(l+r)/2;
	if(x<=mid)Upd(c[p][0],l,mid,x,y);
	else Upd(c[p][1],mid+1,r,x,y);
}
int Merge(int p,int q,int l,int r){
	if(!p||!q)return p+q;
	int mid=(l+r)/2;
	c[p][0]=Merge(c[p][0],c[q][0],l,mid);
	c[p][1]=Merge(c[p][1],c[q][1],mid+1,r);
	return s[p]=s[c[p][0]]+s[c[p][1]],p;
}
int Que(int p,int l,int r,int x,int y){
	if(x<=l&&r<=y)return s[p];
	int mid=(l+r)/2,ret=0;
	if(x<=mid)ret+=Que(c[p][0],l,mid,x,y);
	if(mid<y)ret+=Que(c[p][1],mid+1,r,x,y);
	return ret;
}
void dfs1(int x,int fa){
	size[x]=1,dfn[x]=++sign;
	for(int y:g[x]){
		if(y==fa)continue;
		dfs1(y,x),size[x]+=size[y];
	}
}
void dfs2(int x,int fa,int mx){
	if(x<=mx)Q[mx].push_back({x,dfn[x],dfn[x]+size[x]-1,1,x});
	else {
		for(int y:g[x])if(y!=fa)Q[mx].push_back({y,dfn[y],dfn[y]+size[y]-1,1,x});
		ans[x]++;
	}
	for(int y:g[x]){
		if(y==fa)continue;
		Q[mx].push_back({y,dfn[y],dfn[y]+size[y]-1,-1,y});
		dfs2(y,x,max(mx,x));
	}
}
void dfs3(int x,int fa){
	ans[x]+=ans[fa];
	for(int y:g[x]){
		if(y==fa)continue;
		dfs3(y,x);
	}
}
int gf(int x){
	return x==f[x]?x:f[x]=gf(f[x]);
}
int main(){
	cin>>n;
	for(int i=1,x,y;i<n;i++)cin>>x>>y,g[x].push_back(y),g[y].push_back(x);
	dfs1(1,0),dfs2(1,0,0);
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=n;i++){
		Upd(root[i],1,n,dfn[i],1);
		for(int j:g[i]){
			if(j>i)continue;
			root[i]=Merge(root[i],root[gf(j)],1,n),f[gf(j)]=i;
		}
		for(Query j:Q[i])ans[j.id]+=j.dlt*Que(root[gf(j.x)],1,n,j.l,j.r);
	}
	dfs3(1,0);
	for(int i=2;i<=n;i++)printf("%d ",ans[i]-1);
}
```

---

## 作者：kyEEcccccc (赞：2)

分析一下题目给出的过程。直觉告诉我们关键在于点 $r$ 到 $1$ 的这条路径。一个结论是整个过程中访问的编号最大的点就是这条路径上的最大点，证明可以考虑如果访问了不在路径上的更大的点，在此之前一定可以够到 $1$，于是矛盾。

于是可以发现最大值很重要，那么直觉告诉我们首先观察一下全局最大值，假设这个点是 $s$。这个点很厉害，所有在它子树外的点都永远不会进入它这个子树。所以当我们计算它子树外的节点的答案时，我们可以直接把 $s$ 的一整个子树全部删除，然后接着找剩下的全局最大值，递归进行。而所有 $s$ 子树内的节点，在访问完 $s$ 以后，它在子树外的行为都和 $s$ 的父亲完全相同。那么在最后对答案做一个类似前缀和的操作即可。现在我们只要考虑子树内部的答案和 $s$ 自己的答案。

假设 $s$ 有 $k$ 个儿子，那么总共有 $k$ 个小子树，考虑任何一棵小子树里面的某个点，在这个点访问 $s$ 之前，它一定要把子树内还没有被删除的所有点全部访问一遍（因为 $s$ 是当前全局最大值）。于是这部分的贡献可以直接算出来。然后它到达了 $s$，如果它往子树外面走，刚才已经说明，这部分贡献是可以直接从 $s$ 的父亲的答案获得的，于是只需要考虑它折下去进入另一个小子树。你会发现，它能走到那些点，取决于它到达 $s$ 以后，往根走的那段路上的最大值，这是因为我们一开始给出的结论。那么这个贡献对于所有小子树都很好算，直接预处理出来即可。

时间复杂度线性，只需要用 DFS。

```cpp
// Author: kyEEcccccc

#include <bits/stdc++.h>

using namespace std;

using LL = long long;
using ULL = unsigned long long;

#define F(i, l, r) for (int i = (l); i <= (r); ++i)
#define FF(i, r, l) for (int i = (r); i >= (l); --i)
#define MAX(a, b) ((a) = max(a, b))
#define MIN(a, b) ((a) = min(a, b))
#define SZ(a) ((int)((a).size()) - 1)

constexpr int N = 200005;

int n;
vector<int> to[N];

int par[N];
int mx[N];

void init_tree(int u)
{
	MAX(mx[u], u);
	for (auto v : to[u])
	{
		if (v == par[u]) continue;
		par[v] = u;
		mx[v] = mx[u];
		init_tree(v);
	}
}

int bel[N];

int dfs1(int u)
{
	int res = 1;
	for (auto v : to[u])
	{
		if (v == par[u] || bel[v] != 0) continue;
		res += dfs1(v);
	}
	return res;
}

int dfs2(int u, int lim)
{
	if (u > lim) return 0;
	int res = 1;
	for (auto v : to[u])
	{
		if (v == par[u] || bel[v] != 0) continue;
		res += dfs2(v, lim);
	}
	return res;
}

int ans[N];

void dfs3(int u, int x, int b)
{
	ans[u] = x;
	bel[u] = b;
	for (auto v : to[u])
	{
		if (v == par[u] || bel[v] != 0) continue;
		dfs3(v, x, b);
	}
}

void dfs4(int u)
{
	for (auto v : to[u])
	{
		if (v == par[u]) continue;
		ans[v] += ans[bel[v]];
		dfs4(v);
	}
}

signed main(void)
{
	// freopen(".in", "r", stdin);
	// freopen(".out", "w", stdout);
	ios::sync_with_stdio(0), cin.tie(nullptr);

	cin >> n;
	F(i, 1, n - 1)
	{
		int u, v; cin >> u >> v;
		to[u].push_back(v);
		to[v].push_back(u);
	}

	init_tree(1);

	FF(u, n, 2)
	{
		if (bel[u] != 0) continue;
		vector<pair<int, pair<int, int>>> sub;
		int sum2 = 0;
		for (auto v : to[u])
		{
			if (v == par[u] || bel[v] != 0) continue;
			sub.push_back({v, {dfs1(v), dfs2(v, mx[par[u]])}});
			sum2 += sub.back().second.second;
		}
		ans[u] = sum2 + 1;
		bel[u] = par[u];
		for (auto t : sub) dfs3(t.first, sum2 + 1 - t.second.second + t.second.first, par[u]);
	}

	dfs4(1);

	F(i, 2, n) cout << ans[i] << " \n"[i == n];
	
	return 0;
}
```

---

## 作者：Graphcity (赞：1)

考察从 $x$ 开始的方案中是否会经过 $y$。找到 $x,y$ 的最近公共祖先 $k$，显然如果要走到 $y$ 就必然先经过 $k$。如果路径 $1\to k$（不含 $k$）的最大值比路径 $k\to y $（不含 $k$）的最大值要大，那么 $y$ 就会被经过，否则就不会被经过。

注意到 $k$ 从深往浅枚举的过程中，$k\to y$ 的最大值会越来越大，而 $1\to k$ 的最大值越来越小。也就是说，越往上走就越难满足性质。所以我们可以利用倍增找到对于每个 $y$ 最浅的满足条件的祖先。这个祖先的子树中的点方案中均能经过 $y$，否则均不能经过。

我们按照 dfs 的方式依次求出每个点的答案。进入一个结点时，把所有刚好在这个子树时满足限制的点加入，出去时则撤销这些加入操作。加入和撤销很容易用区间覆盖的线段树做到。查询就是找所有满足限制的点的数量。

总时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e5;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,ans[Maxn+5],dfn[Maxn+5],cur;
int fa[Maxn+5],dep[Maxn+5],siz[Maxn+5];
int mx[Maxn+5],h[Maxn+5][20],anc[Maxn+5][20];
int t[Maxn*4+5],tag[Maxn*4+5];
vector<int> v[Maxn+5],w[Maxn+5];
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)

inline void push_up(int p,int l,int r)
{
    if(tag[p]) t[p]=0;
    else if(l==r) t[p]=1;
    else t[p]=t[ls(p)]+t[rs(p)];
}
inline void Build(int l,int r,int p)
{
    t[p]=r-l+1; if(l==r) return;
    int mid=(l+r)>>1; Build(l,mid,ls(p)),Build(mid+1,r,rs(p));
}
inline void dfs0(int x,int f)
{
    fa[x]=f,dfn[x]=++cur,dep[x]=dep[f]+1,siz[x]=1;
    mx[x]=max(x,mx[f]),h[x][0]=x,anc[x][0]=f;
    For(i,1,19) anc[x][i]=anc[anc[x][i-1]][i-1];
    For(i,1,19) h[x][i]=max(h[x][i-1],h[anc[x][i-1]][i-1]);
    for(auto y:v[x]) if(y!=f) dfs0(y,x),siz[x]+=siz[y];
}
inline void Modify(int nl,int nr,int l,int r,int p,int k)
{
    if(l<=nl && nr<=r) {tag[p]+=k; push_up(p,nl,nr); return;}
    int mid=(nl+nr)>>1;
    if(l<=mid) Modify(nl,mid,l,r,ls(p),k);
    else Modify(mid+1,nr,l,r,rs(p),k);
    push_up(p,nl,nr);
}
inline void dfs(int x,int f)
{
    for(auto y:w[x]) Modify(1,n,dfn[y],dfn[y]+siz[y]-1,1,-1);
    ans[x]=t[1];
    for(auto y:v[x]) if(y!=f) dfs(y,x);
    for(auto y:w[x]) Modify(1,n,dfn[y],dfn[y]+siz[y]-1,1,1);
}

int main()
{
    n=read();
    For(i,1,n-1)
    {
        int a=read(),b=read();
        v[a].push_back(b),v[b].push_back(a);
    }
    dfs0(1,0);
    For(i,1,n)
    {
        int x=i,y=x;
        Rof(j,19,0) if(anc[x][j] && max(y,h[x][j])<=mx[fa[anc[x][j]]])
            y=max(y,h[x][j]),x=anc[x][j];
        w[x].push_back(i);
    }
    Build(1,n,1);
    For(i,1,n) Modify(1,n,dfn[i],dfn[i]+siz[i]-1,1,1);
    dfs(1,0);
    For(i,2,n) printf("%d ",ans[i]-1);
    printf("\n");
    return 0;
}
```

---

## 作者：xht (赞：1)

## [Wandering TKHS](https://atcoder.jp/contests/agc029/tasks/agc029_e)

### 题意

- 给定一棵 $n$ 个点的树。
- 你现在在某个点 $r$，你要到 $1$ 去。
- 每次你会移动到未去过的，且与去过的点相邻的编号最小的点。
- 你要求出对于 $r \in [2,n]$，从 $r$ 到 $1$ 的移动次数。
- $n \le 2 \times 10^5$。

### 题解

把 $1$ 当做根，设 $f_x$ 表示 $x$ 的父亲，$m_x$ 表示 $1 \to f_X$ 的路径上编号最大的点，$h_{x,y}$ 表示从 $x$ 开始不经过 $f_x$ 和其它编号 $>y$ 的点的情况下能到达多少个点，$c_x$ 表示 $x$ 的答案。

考虑对于每个 $x$，讨论一下可知 $c_x - c_{f_x}$ 为 $h_{x,m_x} - [x < m_x][x < m_{f_x}]h_{x,m_{f_x}}$。

而对于 $h$ 有 $h_{x,y} = 1 + \sum_{z \in \text{son}(x)} [z \le y]h_{z,y}$。

注意到对于 $h_{x,y}$，有用的 $y$ 值只有 $m_x$ 和 $m_{f_X}$，因此总状态数为 $\mathcal O(n)$，时间复杂度也为 $\mathcal O(n)$。

### 代码

```cpp
const int N = 2e5 + 7;
int n, m[N], c[N];
vi e[N];
unordered_map<int, int> h[N];

void dfs1(int x, int f) {
	if (x == 1) m[x] = -1;
	else {
		m[x] = max(m[f], f), h[x][m[x]] = 0;
		if (x < m[x] && m[f] > x) h[x][m[f]] = 0;
	}
	for (pi o : h[x])
		for (int y : e[x])
			if (y < o.fi) h[y][o.fi] = 0;
	for (int y : e[x])
		if (y != f) dfs1(y, x);
	for (auto &o : h[x]) {
		++o.se;
		for (int y : e[x])
			if (y < o.fi) o.se += h[y][o.fi];
	}
	if (x == 1) return;
	if (x > m[x]) c[x] += h[x][m[x]];
	else {
		c[x] += h[x][m[x]];
		if (m[f] > x) c[x] -= h[x][m[f]];
	}
}

void dfs2(int x, int f) {
	c[x] += c[f];
	for (int y : e[x])
		if (y != f) dfs2(y, x);
}
 
int main() {
	rd(n);
	for (int i = 1, x, y; i < n; i++)
		rd(x, y), e[x].pb(y), e[y].pb(x);
	dfs1(1, 0), dfs2(1, 0);
	for (int i = 2; i <= n; i++)
		print(c[i], " \n"[i==n]);
	return 0;
}
```

---

## 作者：晴空一鹤 (赞：0)

模拟赛被卡输入输出了，火大。

我们把 $1$ 号房间当作根，那么从节点 $i$ 出发必然要经过 $i$ 的到根链。

考虑一个点 $x$ 是否会加入集合。我们把 $x$ 的到根链取出来，那它与必经的点的交是一个后缀，我们把这个后缀最前面的点记为 $y$，那么当且仅当 $y$ 前的链的最大值比 $y$ 后的链的最大值要小时（注意两者都不包括 $y$） $x$ 会被加入集合。原因显然。

容易发现这玩意是有单调性的，因此我们可以对每个 $x$ 求出可能的最靠后的 $y$，并在 $y$ 上打一个 $+1$ 标记，表示当且仅当 $i$ 在 $y$ 的子树内时会把 $x$ 加入集合。这个 $y$ 要么就在到根链的最大值处，要么就在最大值的儿子处，dfs 时记录一下最大值与次大值的位置即可。

最后对于 $i$ 的答案就是 $i$ 到根链的标记和，直接再 dfs 一遍统计即可。时间复杂度 $O(n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=500005;
int c,n,u,v,mx[N],mxx[N],ans[N];
bool f[N];
vector<int>qp[N];
void inline dfs(int x,int fa,int las){
     mx[x]=mx[fa],mxx[x]=mxx[fa],f[x]=f[fa];
     if(x>mx[fa]){mxx[x]=mx[x];mx[x]=x;f[x]=0;}
     else if(x<mx[fa]&&x>mxx[fa])mxx[x]=x,f[x]=1;
     if(f[x]==0)ans[mx[x]]++;
     else ans[las]++;
     for(int i=0;i<qp[x].size();i++)if(qp[x][i]!=fa)if(mx[x]!=x)dfs(qp[x][i],x,las);else dfs(qp[x][i],x,qp[x][i]);
}
void inline dfs2(int x,int fa){
    if(x!=fa)ans[x]+=ans[fa];
    for(int i=0;i<qp[x].size();i++)if(qp[x][i]!=fa)dfs2(qp[x][i],x);
}
int main(){
   ios::sync_with_stdio(false);
   cin.tie(0),cout.tie(0);
   cin>>n;
   for(int i=1;i<n;i++){cin>>u>>v;qp[u].push_back(v),qp[v].push_back(u);}
   dfs(1,1,1);
   dfs2(1,1);
   for(int i=2;i<=n;i++){cout<<ans[i]-1<<" ";
   }
}

```

---

## 作者：hegm (赞：0)

### [[AGC029E] Wandering TKHS](https://www.luogu.com.cn/problem/AT_agc029_e)

妙妙思维题。

我们让原树按照 $1$ 为根节点。

把点从大到小加入到树中，对于当前 $x$ 来说，他的点集和他的父亲 $y$ 的点集有一部分相同，所有属于 $y$ 的点集，也一定属于 $x$ 的点集，并且 $x$ 多出来的一部分一定是在他的子树内。

考虑具体哪些点是 $x$ 多出来的部分,我们再 $x$ 的子树内广搜，遇到小于 $y$ 到跟路径上最大值 $z$ 的点就加入，那么这部分就是 $x$ 集合多出来的点。

对于在 $x$ 子树内的节点，它的答案和 $x$ 有重合部分，但是会比 $x$ 多，多出来的部分就是这个节点所在的 $x$ 某一个孩子的子树大小（剖去已经加入过的比 $x$ 大的节点的子树）。

这部分我们可以直接求出来，因为只要在 $x$ 的同一个孩子的子树内，那么答案一定一样。

做完之后我们把 $x$ 的子树从树中删除，因为剩下的点不可能进入这里。

最后处理出来所有的答案之后再对全树进行一遍更新即可。

复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define ull unsigned long long
#define make make_pair
#define N 200005
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n;
struct fig
{
	int to,next;
}k[N*2];int head[N],tot;
void add(int from,int to)
{
	k[++tot].to=to;
	k[tot].next=head[from];
	head[from]=tot;
}
int id[N],w[N],fa[N],mx[N],sum[N],siz[N];
bool vis[N];
void dfs(int now,int f)
{
	fa[now]=f;mx[now]=max(mx[f],now);
	for(int i=head[now];i;i=k[i].next)
	{
		if(k[i].to==f)continue;
		dfs(k[i].to,now);
	}
}
void solve(int now,int p,int tg)
{
	if((now>p&&now!=tg)||vis[now])
	{
		sum[now]=0;
		return ;
	}
	sum[now]=1;
	for(int i=head[now];i;i=k[i].next)
	{
		if(k[i].to==fa[now])continue;
		solve(k[i].to,p,tg);
		sum[now]+=sum[k[i].to];
	}
}
void run(int now,int tg)
{
	if(vis[now])
	{
		siz[now]=0;
		return ;
	}
	id[now]=tg;siz[now]=1;
	for(int i=head[now];i;i=k[i].next)
	{
		if(k[i].to==fa[now])continue;
		run(k[i].to,tg);
		siz[now]+=siz[k[i].to];
	}
}
void get(int now)
{
	w[now]+=w[id[now]];
	for(int i=head[now];i;i=k[i].next)
	{
		if(k[i].to==fa[now])continue;
		get(k[i].to);
	}
}
void del(int now)
{
	if(vis[now])return ;
	vis[now]=1;
	for(int i=head[now];i;i=k[i].next)
	{
		if(k[i].to==fa[now])continue;
		del(k[i].to);
	}
}
signed main()
{
	n=read();
	for(int i=1,u,v;i<n;i++)
	{
		u=read();v=read();
		add(u,v);add(v,u);
	}
	dfs(1,0);
	for(int i=n;i>=2;i--)
	{
		if(vis[i])continue;
		id[i]=fa[i];
		solve(i,mx[fa[i]],i);
		w[i]=sum[i];
		for(int j=head[i];j;j=k[j].next)
		{
			if(k[j].to>i||k[j].to==fa[i])continue;
			run(k[j].to,k[j].to);
			id[k[j].to]=i;
			w[k[j].to]=-sum[k[j].to]+siz[k[j].to];
		}
		del(i); 
	}
	get(1);
	for(int i=2;i<=n;i++)cout<<w[i]<<" ";
	return 0;
}

```

---

## 作者：lzqy_ (赞：0)

乐死了，赛时做法比题解都要复杂。

点集 $x$ 扩展到的集合可以分为两部分，子树 $x$ 内的和需要经过父边的。对于后一部分，发现它和 $S_{fa_x}$ 中不在子树 $x$ 内的点是相同的。

考虑从上往下遍历整棵树，用 set 存下子树内遍历到的连通块的底部元素。遍历儿子时继承对应子树内的底部元素，并将子节点编号小于 $\{1\rightarrow x\}$ 的点暴力扩展。这个过程可以通过将 set 拍在值域线段树上解决。

树链剖分后用启发式合并维护上述过程，时间复杂度 $O(n\log ^2n)$。

```cpp
#include<bits/stdc++.h>
#define il inline
using namespace std;
const int inf=1<<30;
const int maxn=200010;
const int MAXN=maxn*100;
il int read(){
    int x=0;
    char c=getchar();
    for(;!(c>='0'&&c<='9');c=getchar());
    for(;c>='0'&&c<='9';c=getchar())
        x=(x<<1)+(x<<3)+c-'0';
    return x;
}
set<int>s[maxn];
vector<int>v[maxn];
int rt[maxn],ls[MAXN],rs[MAXN],d[MAXN];
int zson[maxn],sz[maxn],dfn[maxn],DFN[maxn],f[maxn],idx,cnt;
int id[maxn],ans[maxn],cur[maxn],n;
void init1(int fa,int x){
    f[x]=fa;
    for(int i=0;i<v[x].size();i++)
        if(v[x][i]^fa){
            init1(x,v[x][i]),sz[x]+=sz[v[x][i]];
            if(sz[v[x][i]]>sz[zson[x]]) zson[x]=v[x][i];
        }
    sz[x]++;
}
void init2(int fa,int x){
    dfn[x]=++idx,DFN[idx]=x;
    if(zson[x]) init2(x,zson[x]);
    for(int i=0;i<v[x].size();i++)
        if(v[x][i]!=fa&&v[x][i]!=zson[x]) init2(x,v[x][i]);
}
void Add(int &i,int l,int r,int x,int k){
    if(!i) i=++cnt;
    if(l==r){
        d[i]=k;
        return ;
    }int mid=l+r>>1;
    if(mid>=x) Add(ls[i],l,mid,x,k);
    else Add(rs[i],mid+1,r,x,k);
    d[i]=max(d[ls[i]],d[rs[i]]);
}
void Del(int i,int l,int r,int x){
    if(l==r){
        d[i]=0;
        return ;
    }int mid=l+r>>1;
    if(mid>=x) Del(ls[i],l,mid,x);
    else Del(rs[i],mid+1,r,x);
    d[i]=max(d[ls[i]],d[rs[i]]);
}
int solve(int t,int i,int l,int r,int R){
    if(!d[i]||l>R) return 0;
    if(l==r){
        int j,sum=0;
        for(j=cur[d[i]];j<v[d[i]].size()&&v[d[i]][j]<R;cur[d[i]]++,j++){
            if(cur[v[d[i]][j]]<v[v[d[i]][j]].size())
                Add(rt[t],1,n,v[v[d[i]][j]][cur[v[d[i]][j]]],v[d[i]][j]);
            s[t].insert(dfn[v[d[i]][j]]);
            sum++;
        }
        if(cur[d[i]]<v[d[i]].size())
            Add(rt[t],1,n,v[d[i]][cur[d[i]]],d[i]);
        else s[t].erase(dfn[d[i]]);
        d[i]=0;
        return sum;
    }
    int mid=l+r>>1;
    int sum=solve(t,ls[i],l,mid,R);
    sum+=solve(t,rs[i],mid+1,r,R);
    d[i]=max(d[ls[i]],d[rs[i]]);
    return sum;
}
bool In(int x,int y){return dfn[y]>=dfn[x]&&dfn[y]<dfn[x]+sz[x];}
void dfs(int fa,int x,int sum){
    int y=id[x],num,tot;
    if(s[y].empty()){
        if(cur[x]<v[x].size())
            Add(rt[y],1,n,v[x][cur[x]],x);
        s[y].insert(dfn[x]),sum++;
    }
    while(tot=solve(y,rt[y],1,n,fa)) sum+=tot;
    ans[x]=sum;
    for(int i=v[x].size()-1;~i;i--)
        if(v[x][i]!=zson[x]){
            while(!s[y].empty()&&In(v[x][i],num=DFN[*--s[y].end()])){
                if(cur[num]<v[num].size())
                    Add(rt[v[x][i]],1,n,v[num][cur[num]],num);
                if(cur[num]<v[num].size())
                    Del(rt[y],1,n,v[num][cur[num]]);
                s[v[x][i]].insert(dfn[num]),s[y].erase(dfn[num]);
            }
            dfs(max(fa,x),v[x][i],sum);
        }
    if(!zson[x]) return ;
    if(!s[y].empty()&&(num=DFN[*s[y].begin()])==x){
        s[y].erase(dfn[num]);
        if(cur[num]<v[num].size())
            Del(rt[y],1,n,v[num][cur[num]]);
    }
    id[zson[x]]=y,dfs(max(fa,x),zson[x],sum);
}
int main(){
    //int Time=clock();
    n=read();
    for(int i=1;i<n;i++){
        int x=read(),y=read();
        v[x].push_back(y);
        v[y].push_back(x);
    }
    for(int i=1;i<=n;i++)
        sort(v[i].begin(),v[i].end());
    for(int i=1;i<=n;i++) id[i]=i;
    init1(0,1),init2(0,1);
    for(int i=2;i<=n;i++)
        for(int j=0;j<v[i].size();j++)
            if(v[i][j]==f[i]){
                v[i].erase(v[i].begin()+j);
                break;
            }
    for(int i=0;i<v[1].size();i++) dfs(1,v[1][i],0);
    for(int i=2;i<=n;i++)
        printf("%d ",ans[i]);
    printf("\n");
    //printf("t = %.3lf\n",(clock()-Time)*1.0/CLOCKS_PER_SEC);
    return 0;
}

```

---

