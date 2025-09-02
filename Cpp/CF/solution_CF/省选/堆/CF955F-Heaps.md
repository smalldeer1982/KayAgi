# Heaps

## 题目描述

You're given a tree with $ n $ vertices rooted at $ 1 $ .

We say that there's a $ k $ -ary heap of depth $ m $ located at $ u $ if the following holds:

- For $ m=1 $ $ u $ itself is a $ k $ -ary heap of depth $ 1 $ .
- For $ m&gt;1 $ vertex $ u $ is a $ k $ -ary heap of depth $ m $ if at least $ k $ of its children are $ k $ -ary heaps of depth at least $ m-1 $ .

Denote $ dp_{k}(u) $ as maximum depth of $ k $ -ary heap in the subtree of $ u $ (including $ u $ ). Your goal is to compute ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF955F/5de2414b533cccf22014f0b7eca5e58cbc6e8f9c.png).

## 说明/提示

Consider sample case one.

For $ k>=3 $ all $ dp_{k} $ will be equal to $ 1 $ .

For $ k=2 $ $ dp_{k} $ is $ 2 $ if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF955F/295fea3eafde0a7829eafa0db84ff6ad03162c9f.png) and $ 1 $ otherwise.

For $ k=1 $ $ dp_{k} $ values are $ (3,1,2,1) $ respectively.

To sum up, $ 4·1+4·1+2·2+2·1+3+1+2+1=21 $ .

## 样例 #1

### 输入

```
4
1 3
2 3
4 3
```

### 输出

```
21
```

## 样例 #2

### 输入

```
4
1 2
2 3
3 4
```

### 输出

```
22
```

# 题解

## 作者：天命之路 (赞：7)

随机跳题跳到的，感觉非常妙。

*2600 评黑还是有点虚高，不过这种方法也确实需要巧思。

下文设 $son(u)$ 表示 $u$ 的儿子集合。

注意到随着叉数的增加，节点个数增长得非常快，另一方面可以发现：

$dp_k(1) \le \log_k n$

也就是说，其实除开 $k = 1$ 的情况外，对于一个节点 $u$ ,合法的深度最多只有 $\log$ 个。

然后注意到，对于固定的深度 $d$，合法的 $k$ 一定是一段区间 $[1,l]$ .

这启发我们把深度作为状态，将 $k$ 作为 $dp$ 值。

**这是一种非常重要的思想，当原本的答案和某一维状态严重地不同阶，且容易由答案反推合法状态，就可以考虑这种换维的操作。**

具体的，设 $F_{u,d}$ 表示要求深度为 $d$ 时最大的合法的 $k$，则状态有 $n\log n$ 个。

显然，$F_{u,d}$ 可以从 $F_{v,d-1}$ 转移而来。（$v \in son(u)$）

事实上，如果可以，我们一定会在 $F_{v,d-1}$ 中取尽量大的值。

所以我们固定 $d$ 后，把所有的 $F_{v,d-1}$ 放进另一个数组 $A$，从大到小排序，然后从 $1$ 到 $|son(u)|$ 枚举预期的叉数 $k$ ，那么实际能达到的叉数就是 $\min(k,A[k])$，对所有 $k$ 取 $\max$ 即可。

$dp$ 完后，发现题目说的是“在 $u$ 的子树内存在的...."，所以还要求个子树 $\max$.

最后统计的时候，将所有 $f[u][d] - 1$ 加起来即可（$-1$是为了扣除 $k = 1$ 的答案）

最后再额外加上 $k = 1$ 的答案，就做完了。

```cpp
const int N = 3e5 + 5,Lg = 19;
typedef long long ll;
int f[N][Lg + 5],dp1[N];
int fir[N],nxt[N << 1],to[N << 1],ect = 0;
inline void addedge(int u1,int v1)
{
	nxt[++ect] = fir[u1];fir[u1] = ect;to[ect] = v1;
}
int n;
void dp_One(int x,int fa)  // 算 k = 1 时的答案
{
	for(int i = fir[x],y;y=to[i],i;i=nxt[i])
	{
		if(y == fa) continue;
		dp_One(y,x);
		dp1[x] = max(dp1[x],dp1[y]);
	}
	++dp1[x];
}
long long ans;
void Dp(int x,int fa) 
{
	f[x][1] = n;
	for(int i = fir[x],y;y=to[i],i;i=nxt[i])
		if(y != fa) Dp(y,x);
	for(int d = 2;d <= Lg;d++)
	{
		std::vector<int> dpv;
		for(int i = fir[x],y;y=to[i],i;i = nxt[i])
			if(y != fa) dpv.push_back(f[y][d - 1]);
		sort(dpv.begin(),dpv.end(),greater<int>()); //从大到小排序
		for(int k = 1;k <= dpv.size();k++)  //枚举预期的叉数
			f[x][d] = max(f[x][d],min(k,dpv[k - 1]));
	}
}
void dfs2(int x,int fa)
{
	for(int i = fir[x],y;y=to[i],i;i=nxt[i])
		if(y != fa) 
		{
			dfs2(y,x);
			for(int d = 1;d <= Lg;d++)
				f[x][d] = max(f[x][d],f[y][d]);
		}
}
int main()
{
	scanf("%d",&n);
	for(int i = 1;i < n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		addedge(u,v);addedge(v,u);
	}
	dp_One(1,0);
	Dp(1,0);
	dfs2(1,0);
	for(int i = 1;i <= n;i++) ans += dp1[i];
	for(int d = 1;d <= Lg;d++)
		for(int i = 1;i <= n;i++)
			ans += max(f[i][d] - 1,0);
	printf("%lld\n",ans);
	return 0;
}
```



---

## 作者：MyukiyoMekya (赞：3)

首先有个很 naïve 的想法：求出所有的 $dp_k(u)$。

$f_{u,k}=x$ 表示 $u$ 的子树中以 $u$ 为根的满 $k$ 叉树最大的深度为 $x$ 。

那么 dp 转移很显然：

$f_{u,k}= $ ( $\{f_{v,k-1}\}$ 中第 $k$ 大的数 +1 )，$v$ 是 $u$ 的儿子，如果不足 $k$ 个，那么就是这个第 $k$ 大的数就是 0。

快速取第 $k$ 大的数可以使用 `std::nth_element` 或者手写实现。

然后 $dp_k(u)$ 就是 $\max\{f_{v,k}\}$ ，$v$ 是 $u$ 子树内所有节点。

时空复杂度 $\Omicron (n^2)$。

然后你会发现有一些性质：

1. $f_{1,k}\le \log_kn$
2. $f_{u,k}\le 2$  $(k\ge \sqrt n)$
3. $f_{u,k}\ge f_{u,k+1}$

我们看性质 2，$k\ge \sqrt n$ 的时候 f 数组只有 1 和 2两种取值，也就是说，$f_u$ 只跟 $u$ 和 $u$ 的儿子有关！那么我们直接一遍通过统计节点儿子个数就可以算出在哪一个 $k$ 的时候 $f_u$ 从 2 变为了 1。时间复杂度 $\Omicron(n)$  。

然后对于 $k< \sqrt n$ 的部分，发现这部分可以直接跑我们上面那个 $n^2$ 的暴力，在这里只要算 $k< \sqrt n$ 的部分所以时间复杂度 $\Omicron(n\sqrt n)$。

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#pragma GCC optimize("O3,Ofast,inline")
#pragma GCC target("avx,avx2")
#include <bits/stdc++.h>
#define reg register
#define mem(x,y) memset(x,y,sizeof x)
#define ln std::puts("")
const int MaxN=300050;
struct Edge
{
	int nxt,to;
}E[MaxN<<2],G[MaxN<<2];
template <class t> inline void read(t &s){s=0;
reg int f=1;reg char c=getchar();while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
while(isdigit(c))s=(s<<3)+(s<<1)+(c^48),c=getchar();s*=f;return;}
template<class t,class ...A> inline void read(t &x,A &...a){read(x);read(a...);}
template <class t> inline void write(t x){if(x<0)putchar('-'),x=-x;
int buf[21],top=0;while(x)buf[++top]=x%10,x/=10;if(!top)buf[++top]=0;
while(top)putchar(buf[top--]^'0');return;}
template <class t>inline bool checkmax(t&x,t y){if(x<y){x=y;return 1;}return 0;}
int hd[MaxN],_hd[MaxN],en,_en;
int f[MaxN],n,K,L;
int pool[MaxN<<5],*poolp=pool;
int topo[MaxN],deg[MaxN],Fath[MaxN],Res[MaxN],*Dr[MaxN],M[MaxN];
long long ans;
inline void adde(int u,int v)
{
	E[++en]=(Edge){hd[u],v};
	hd[u]=en;
}
inline void _adde(int u,int v)
{
	G[++_en]=(Edge){_hd[u],v};
	_hd[u]=_en;
}
inline int* New(int siz)
{
	return poolp+=siz,poolp-siz;
}
inline int cmp(int a,int b)
{
	return a>b;
}
inline int max(int a,int b)
{
    return a>b?a:b;
}
int node0[MaxN],nd0cnt,node1[MaxN],nd1cnt;
inline void toposort()
{
	reg int idx=0;
	std::queue<int> Q;Q.push(1);
	while(!Q.empty())
	{
		reg int u=Q.front();Q.pop();
		topo[++idx]=u;
		for(int i=_hd[u];~i;i=G[i].nxt)
		{
			reg int v=G[i].to;
			if(!(--deg[v]))
				Q.push(v);
		}
	}
	for(int i=1;i<=n;++i)
		++deg[Fath[i]];
	for(int i=1;i<=n;++i)
		if(deg[i])
			Dr[i]=New(deg[i]+1);
		else
			node0[++nd0cnt]=i;
	for(int i=n;i;--i)
		if(deg[topo[i]])
			node1[++nd1cnt]=topo[i];
	Dr[0]=New(2);
}
inline void dfs1(int u,int fa)
{
	Fath[u]=fa;
	for(int i=hd[u];~i;i=E[i].nxt)
	{
		reg int v=E[i].to;
		if(v==fa)
			continue;
		_adde(u,v);
		++deg[v];
		dfs1(v,u);
	}
}
inline void dfs2()
{
	ans+=nd0cnt;
	std::mem(Res,0),std::mem(M,0);
	for(int U=1;U<=nd1cnt;++U)
	{
		reg int u=node1[U],fa=Fath[u],fu;
		if(M[u]>=K)
			std::nth_element(Dr[u],Dr[u]+K-1,Dr[u]+M[u],cmp),fu=Dr[u][K-1]+1;
		else
			fu=1+(deg[u]>=K);
		Res[u]=max(Res[u],fu),ans+=Res[u];
		Res[fa]=max(Res[fa],Res[u]);
		Dr[fa][M[fa]++]=fu;
	}
}
int mxdeg[MaxN];
inline void dfs3(int u,int fa)
{
	reg int cnt=0;
	for(int i=hd[u];~i;i=E[i].nxt)
	{
		reg int v=E[i].to;
		if(v==fa)
			continue;
		++cnt;
		dfs3(v,u);
		checkmax(mxdeg[u],mxdeg[v]);
	}
	checkmax(mxdeg[u],cnt);
}
signed main(void)
{
	std::mem(hd,-1),std::mem(_hd,-1);
	read(n),L=std::sqrt(n);
	reg int u,v;
	for(int i=1;i<n;++i)
		read(u,v),adde(u,v),adde(v,u);
	dfs1(1,0);
	toposort();
	for(K=1;K<=L;++K)
		dfs2();
	dfs3(1,0);
	for(int i=1;i<=n;++i)
		ans+=(std::max(L,mxdeg[i])-L)*2+(n-std::max(L,mxdeg[i]));
	write(ans),ln;
	return 0;
}
```

总时间复杂度 $\mathcal O(n\sqrt n+n)$，n 范围 3e5，时限 2.5s，看上去能过，但是卡了将近一天还是TLontest15。

主要瓶颈出在前面那个 $n\sqrt n$ ，我尝试了先拓扑排序，然后按照反拓扑序来进行模拟树形dp，减少压栈产生的常数，然后手写内存池，以及特殊处理叶子节点来减少常数，确实快了不少，但还是卡不过去qaq

没办法，我们只能从复杂度上进行优化。

我们来看性质 1 和 3：$f_{1,k}\le \log_kn$ ， $f_{u,k}\ge f_{u,k+1}$

$k=1$ 的直接暴力跑一遍，$\Omicron(n)$，（其实这里的 $f_{u,1}$ 就是 u 子树内离 u 最远的点离 u 点的距离）。

我们发现 $k\ge 2$ 的时候 $f$ 数组的取值是 $\log_2 n$ 的，然后根据后面那个性质，我们可以想出一个状态：

$g_{u,j}=k$ 表示最大的 $k$ 使得 $f_{u,k}=j$，这样 $g$ 的第二维就变成 $\log $ 的大小了。也就是说：

$g_{u,j}=k$ 表示 $u$ 子树内以 $u$ 为根要达到 $j$ 深度（这里是以 $u$ 为根的深度），满叉数最大是 $k$。

然后来想怎么转移：

先把所有 $g_{v,j-1}$ 扔进一个数组 $S$，$v$ 是 $u$ 的儿子。然后显然可以二分答案。两只log。

当然你也可以先从大到小排序，然后扫一遍找最大的 $i$ 满足 $S_i\ge i$ ，贪心证一下显然正确，然鹅排序 nlog，还是两只log。。。这时候基排没用。

然后 $g$ 求完后先从子树里取个 max，然后直接算就行了，把所有合法的 $g_{u,j}-1$ 加起来就是答案了。

别忘了加上 $k=1$ 的答案。

$\texttt{Code}$

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
#define ALL(x) (x).begin(),(x).end()
#define ln std::puts("")
#define pb push_back
const int MaxN=300050;
template <class t> inline void read(t &s){s=0;
reg int f=1;reg char c=getchar();while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
while(isdigit(c))s=(s<<3)+(s<<1)+(c^48),c=getchar();s*=f;return;}
template<class t,class ...A> inline void read(t &x,A &...a){read(x);read(a...);}
template <class t> inline void write(t x){if(x<0)putchar('-'),x=-x;
int buf[21],top=0;while(x)buf[++top]=x%10,x/=10;if(!top)buf[++top]=0;
while(top)putchar(buf[top--]^'0');return;}
template <class t>inline bool checkmax(t&x,t y){if(x<y){x=y;return 1;}return 0;}
std::vector<int> E[MaxN];
int dep[MaxN],f[MaxN][20],n;
long long ans;
inline void dfs1(int u,int fa)
{
	for(auto v:E[u])if(v!=fa)
		dfs1(v,u),checkmax(dep[u],dep[v]);
	++dep[u],ans+=dep[u],f[u][1]=n;
	reg int cur=0;
	for(int j=2;j<20;++j)
	{
		std::vector<int> dr;
		for(auto v:E[u])if(v!=fa)
			dr.pb(f[v][j-1]);
		std::sort(ALL(dr),[&](int a,int b)->bool{return a>b;});
		for(cur=0;cur<(int)dr.size()&&dr[cur]>=cur+1;++cur);
		f[u][j]=cur;
	}
}
inline void dfs2(int u,int fa)
{
	for(auto v:E[u])if(v!=fa)
	{
		dfs2(v,u);
		for(int j=1;j<20;++j)
			checkmax(f[u][j],f[v][j]);
	}
}
signed main(void)
{
	read(n);
	reg int u,v;
	for(int i=1;i<n;++i)
		read(u,v),E[u].pb(v),E[v].pb(u);
	dfs1(1,0),dfs2(1,0);
	for(int i=1;i<=n;++i)
		for(int j=1;j<20;++j)
			if(f[i][j])
				ans+=f[i][j]-1;
	write(ans),ln;
	return 0;
}
```



---

## 作者：hj23308 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF955F)

### $\mathcal{Problem}$

给定一棵以 $1$ 为根的树，定义 $dp_k(u)$ 表示在 $u$ 的子树内存在的深度最大的满 $k$ 叉树的深度，求 $\sum_{u=1}^n∑_{k=1}^ndp_k(u)$。

以某个点 $x$ 为根存在一棵深度 $m$ 的满 $k$ 叉树是指，它满足下面任意一条：

- $m=1$。

- 当 $m\neq1$ 时，$x$ 存在 $k$ 个子节点，分别以它们为根存在一棵深度为 $m−1$ 的满 $k$ 叉树。

### $\mathcal{Solution}$

提供一种几乎没有思考量的做法。

首先我们定义 $ f _ k(u) $ 表示以 $ u $ 为根的子树满 $ k $ 叉树的最大深度，直接暴力转移，看似复杂度是 $ \mathcal O(n ^ 2) $ 的。但注意到对于一个点 $ u $，$ k $ 大于其儿子个数时 $ f_k(u) $ 均等于 $ 1 $，而因为儿子数量之和为 $ n - 1 $，所以状态数是 $ \mathcal O(n) $ 级别的，计算 $ f $ 时复杂度降为了 $ \mathcal O(n) $。

题目中要求的 $ dp _ k(u) = \max\{f_k(v) \mid v \in \mathrm{subtree}(u) \} $，使用线段树合并或 dsu on tree 维护，复杂度为 $ \mathcal O(n \log n) $。

时间复杂度 $ \mathcal O(n \log n) $，空间复杂度 $ \mathcal O(n) $。

### [$ \mathcal{Record} $](https://codeforces.com/contest/955/submission/235058813)

### $\mathcal{Code}$

```cpp
#include<bits/stdc++.h>

using namespace std;

#define REP(i, l, r) for (int i = l; i <= r; i++)
#define PER(i, r, l) for (int i = r; i >= l; i--)

const int maxN = 3e5 + 1;

int n, son[maxN];
long long sum[maxN], ans;
vector<int> mx[maxN], dp[maxN];
vector<int> edges[maxN];

void dfs(int u, int prt) {
	if (son[u] == 0) return mx[u].resize(2, 1), sum[u] = 1, ans += n, void();
	vector<vector<int>> tmp(son[u] + 1);
	int mxSon = 0;
	for (auto v: edges[u])
		if (v != prt) {
			dfs(v, u);
			REP(i, 1, min(son[v], son[u])) tmp[i].emplace_back(dp[v][i]);
			if (!mxSon || mx[v].size() > mx[mxSon].size()) mxSon = v;
		}
	dp[u].resize(son[u] + 1);
	sum[u] = sum[mxSon], swap(mx[u], mx[mxSon]);
	if (int(mx[u].size()) <= son[u]) mx[u].resize(son[u] + 1);
	for (auto v: edges[u])
		if (v != prt && v != mxSon)
			REP(i, 1, int(mx[v].size()) - 1) if (mx[v][i] > mx[u][i])
					sum[u] += mx[v][i] - mx[u][i], mx[u][i] = mx[v][i];

	REP(i, 1, son[u]) {
		if (tmp[i].size() < i) dp[u][i] = 2;
		else
			nth_element(tmp[i].begin(), tmp[i].end() - i, tmp[i].end()),
					dp[u][i] = tmp[i][int(tmp[i].size()) - i] + 1;
		if (dp[u][i] > mx[u][i])
			sum[u] += dp[u][i] - mx[u][i], mx[u][i] = dp[u][i];
	}

	ans += sum[u] + n - int(mx[u].size() - 1);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n;
	REP(i, 2, n) {
		int u, v;
		cin >> u >> v;
		edges[u].emplace_back(v);
		edges[v].emplace_back(u);
	}
	REP(i, 1, n) son[i] = int(edges[i].size()) - (i != 1);
	dfs(1, 0), cout << ans << '\n';

	return 0;
}
```

---

## 作者：xfrvq (赞：1)

[$\tt CF955F$](/problem/CF955F)，$\tt^\ast2600$。

首先要知道：设 $deg_u$ 为 $u$ 的儿子个数，有 $\sum deg_u=O(n)$。

我们考虑求出 $dp_k(u)$，然后一个一个加。

但是这个不太好直接求，所以可以求出一个弱化一点的东西：$f_k(u)$ 代表 $u$ 子树内 **以 $u$ 为根** 的 $k$ 叉树最大深度。

容易发现 $f_k(u)$ 分成两类，一类 $\gt1$，一类 $=1$。容易发现后者居多，而前者只有 $\sum deg_u=O(n)$ 种。

我们希望让复杂度尽量优秀，于是考虑 $O(n)$ 的时间里求出 $f_{k}(u)$ 的所有非 $1$ 状态。

我们考虑树形 $\tt DP$ 来求这个东西，设 $S_{u,k}=\{f_{v,k}\}$，其中 $v$ 是 $u$ 的儿子，那么有 $f_{u,k}=\mathtt{kth}(S_{u,k},k)+1$，其中 $\tt kth$ 是取 $k$ 大的意思。

原因很显然，如果第 $k$ 大为 $x$，说明至少有 $k$ 个 $v$ 使得 $f_{v,k}\ge x$，那么以这 $k$ 个儿子各自建 $k$ 叉树，$u$ 连向着  $k$ 个儿子，新 $k$ 叉树深度一定 $\ge x+1$。

$\tt kth$ 就是 $\texttt{std::nth\_element}$。

那我们怎么通过这个 $f$ 推到复杂的 $dp$ 呢？其实 $dp$ 就是 $f$ 的子树最大值。但是 $dp$ 不能直接暴力累加，因为它的状态数不是 $O(n)$ 的。

我们分开每个 $k=1,\cdots,n$ 来处理 $\sum dp_k(u)$，对于某个 $k$，我们把 $deg_u\le k$ 的 $u$ 建成一棵虚树（复杂度 $\sum deg_u$）。

我们考虑虚树上一条边 $fa\to u$，并且 $dp_k(u)=x$。这时候对于 $p\in\{fa,\cdots,u\}$ 这条链除去 $fa$，$dp_k(p)=x$。所以 $u$ 的贡献是 `(dep[u]-dep[fa])*dp[u][k]`。

那就是一个简单的虚树 $\tt DP$ 了。

求 $f$ 和虚树 $\tt DP$ 都可以很简单的做到线性。（我的实现）做不到线性的原因是我不想写 $O(n)-O(1)$ 的 $\tt LCA$（建虚树），最后就是 $O(n\log n)$。

---

## 作者：critnos (赞：1)

提供一个相当简单的线性做法。

求出 $dp_{i,j}$ 表示以 $i$ 为根的 $j$ 叉树的最深深度，显然这里只有 $O(n)$ 个大于 $1$ 的状态（因为每个点的状态数是其儿子数量）。这是很好线性求的。

然后枚举 $k$ 即可，将所有儿子数 $\ge k$ 的点跑虚树求解。这里实现的好就是线性的。

这里虚树可以通过链表删除或者归并求出 dfn 排序的结果，还要写一个 $O(n)-O(1)$ LCA。

[CF 评测记录，里面封装了一个写法很优秀的 O(n)-O(1) LCA](https://codeforces.com/contest/955/submission/172357555)

---

## 作者：mango2011 (赞：0)

糖糖的做法。

对于 $k=1$，可以直接 $O(n)$ 计算。对于 $k>n^\frac{1}{2}$，层数不超过 $2$，也可以直接 $O(n)$ 计算。于是重点就是 $[2,n^\frac{1}{2}]$。直接设计 $f_{u,i}$ 表示 $u$ 的子树内，观察发现 $f_{u,i}\ge f_{u,i+1}$ 并且有 $f_{u,i}\le\log_{2}n$，所以可以通过指针的移动实现总 $O(n\sqrt{n})$ 的复杂度。

然后过不去。但是我们可以考虑再处理掉 $k>n^\frac{1}{3}$ 的部分。这个时候层数不超过 $3$，具体做法就是二分一个然后检验。这一部分的复杂度是 $O(n\log n)$ 的。

所以，总的复杂度是 $O(n^\frac{4}{3})$，可以通过。

[提交记录](https://codeforces.com/contest/955/submission/314749956)

---

## 作者：TernaryTree (赞：0)

一眼了，写个题解。

众所周知暴力是可以做的。$f_{u,i}$ 表示 $u$ 结点为根的满 $i$ 叉树的最大深度，转移需要对 $f_{v,i}+1$ 排个序，取第 $i$ 大即可。这样是 $\Theta(n^2\log n)$。

显然 $i$ 大一点，$f_{u,i}$ 就会很小，因为满 $i$ 叉树的结点数是指数级增长的。我们设定一个阈值 $B$，令 $f_{u,i}$ 中的 $i\le B$，并且另设 dp $g_{u,i}$ 表示 $u$ 结点为根的深度至少为 $i$ 的最大叉数，此处的 $i$ 也 $\le B$。$g_{u,i}$ 的 dp 过程与 $f_{u,i}$ 类似，对 $g_{v,i-1}$ 排序，枚举叉数 $j$，令 $g_{u,i}\gets \max(g_{u,i},\min(j,p_j))$，$p_j$ 为第 $j$ 大的 $g_{v,i-1}$。最后因为是求子树内而不是必须包含 $u$，需要子树求个 $\max$，不必多说。

瞎算算可以得到 $B=8$ 覆盖所有情况，可行。于是我们用 $\Theta(Bn\log n)$ 的复杂度解决了这道题。

```cpp
#include <bits/stdc++.h>
#define int long long
#define fs first
#define sc second
#define ls (u << 1)
#define rs (u << 1 | 1)
#define mid ((l + r) >> 1)
#define lc ls, l, mid
#define rc rs, mid + 1, r
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define per(i, r, l) for (int i = (r); i >= (l); --i)
#define gc getchar
#define pc putchar

using namespace std;
using pii = pair<int, int>;
using vi = vector<int>;

const int maxn = 3e5 + 10;
const int inf = 1e18;
const bool multidata = 0;

template<typename T = int>
T read() {
	T x = 0, f = 1; char c = gc();
	while (c < '0' || c > '9') { if (c == '-') f = -f; c = gc(); }
	while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = gc();
	return x * f;
}

template<typename T = int>
void write(T x) {
	if (x < 0) pc('-'), x = -x;
	if (x < 10) return void (pc(x + '0'));
	write<T>(x / 10), pc(x % 10 + '0');
}

int n, B, ans;
vector<int> tr[maxn];
int deg[maxn];
int f[maxn][30]; // 以 u 为根，度数为 j 的最大深度 
int g[maxn][30]; // 以 u 为根，深度为 j 的最大叉数 

void dfs1(int u, int fa) {
	for (int v : tr[u]) {
		if (v == fa) continue;
		dfs1(v, u);
		++deg[u];
	}
	if (!deg[u]) {
		rep(i, 1, B) f[u][i] = 1;
		g[u][1] = n;
		return;
	}
	rep(i, 1, min(B, deg[u])) {
		f[u][i] = 1e9;
		vector<int> tmp;
		for (int v : tr[u]) if (v != fa) tmp.push_back(f[v][i] + 1);
		sort(tmp.begin(), tmp.end(), greater<int> ());
		f[u][i] = tmp[i - 1];
	} 
	rep(i, deg[u] + 1, B) f[u][i] = 1;
	g[u][1] = n;
	rep(i, 2, B) {
		g[u][i] = 0;
		vector<int> tmp;
		for (int v : tr[u]) if (v != fa) tmp.push_back(g[v][i - 1]);
		sort(tmp.begin(), tmp.end(), greater<int> ());
		per(j, deg[u], 1) g[u][i] = max(g[u][i], min(j, tmp[j - 1]));
	}
}

void dfs2(int u, int fa) {
	for (int v : tr[u]) if (v != fa) dfs2(v, u);
	rep(i, 1, B) for (int v : tr[u]) if (v != fa) f[u][i] = max(f[u][i], f[v][i]);
	rep(i, 1, B) for (int v : tr[u]) if (v != fa) g[u][i] = max(g[u][i], g[v][i]);
}

void fake_main() {
	n = read(), B = min(8ll, n);
	rep(i, 1, n - 1) {
		int u = read(), v = read();
		tr[u].push_back(v);
		tr[v].push_back(u);
	}
	dfs1(1, 0);
	dfs2(1, 0);
	rep(u, 1, n) rep(j, 1, B) ans += f[u][j];
	rep(u, 1, n) rep(j, 1, B) ans += max(g[u][j] - B, 0ll);
//	rep(u, 1, n) {
//		cout << u << ": ";
//		rep(j, 1, B) cout << f[u][j] << " ";
//		cout << endl;
//	}
//	rep(u, 1, n) {
//		cout << u << ": ";
//		rep(j, 1, B) cout << g[u][j] << " ";
//		cout << endl;
//	}
	write(ans);
}

signed main() {
	int T = multidata ? read() : 1;
	while (T--) fake_main();
	return 0;
}
/*
16
1 2 1 3 1 4
2 5 2 6 3 7 4 8 4 9 4 10
8 11 8 12 9 13 9 14 10 15 10 16

19
1 2 1 3 1 4
2 5 2 6 3 7 4 8 4 9 4 10
8 11 8 12 8 13 9 14 9 15 9 16 10 17 10 18 10 19
*/
```

---

