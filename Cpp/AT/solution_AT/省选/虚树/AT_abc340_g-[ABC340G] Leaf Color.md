# [ABC340G] Leaf Color

## 题目描述

有一棵包含 $N$ 个顶点的树 $T$，顶点编号为 $1$ 到 $N$。第 $i$ 条边连接顶点 $u_i$ 和顶点 $v_i$。此外，顶点 $i$ 被染成颜色 $A_i$。

请计算满足以下条件的 $T$ 的顶点集合（非空子集）$S$ 的个数，并对 $998244353$ 取模：

- $S$ 所对应的诱导子图 $G$ 满足以下所有条件：
  - $G$ 是一棵树。
  - 所有度数为 $1$ 的顶点的颜色都相同。

诱导子图的定义如下：对于图 $G$ 的顶点子集 $S$，$S$ 所对应的诱导子图是指顶点集合为 $S$，边集合为“$G$ 中两端都属于 $S$ 的所有边”的图。

## 说明/提示

## 限制条件

- $1 \leq N \leq 2 \times 10^5$
- $1 \leq A_i \leq N$
- $1 \leq u_i < v_i \leq N$
- 输入保证图为一棵树
- 输入的所有数均为整数

## 样例解释 1

满足条件的顶点集合有以下 $4$ 种：

- $\lbrace 1 \rbrace$
- $\lbrace 1, 2, 3 \rbrace$
- $\lbrace 2 \rbrace$
- $\lbrace 3 \rbrace$

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
1 2 1
1 2
2 3```

### 输出

```
4```

## 样例 #2

### 输入

```
5
2 2 1 1 1
2 5
3 4
1 3
1 5```

### 输出

```
9```

## 样例 #3

### 输入

```
15
5 3 5 1 1 4 4 4 2 5 5 4 4 2 5
3 13
4 10
7 11
8 9
2 10
2 14
5 11
5 6
6 13
12 13
9 14
9 13
1 13
1 15```

### 输出

```
48```

# 题解

## 作者：封禁用户 (赞：10)

本题中的叶节点实际上指的是度数为 $1$ 的点，中文翻译并不清楚。

我们发现题目中要求原树的子图中叶子节点必须为同一种颜色 $x$。显然，这满足条件的树一定在**由所有颜色为 $x$ 的点构建的虚树**上。

因为 $\forall col_k \neq x$，显然存在 $\forall col_i=col_j=x$，使得 $i,j,k$ 均被选中且 $i,j$ 的简单路径经过 $k$。

有了这个性质就很好做了，构建出虚树，设 $dp_{i,0}$ 为 $i$ 为根且 $i$ 的度数为 $1$ 的方案数，$dp_{i,1}$ 为 $i$ 为根且 $i$ 的度数大于 $1$ 的方案数，$as_i$ 为 $i$ 为根的总方案数。转移：

$$dp_{k,1}=dp_{k,1} \times (as_v+1)+dp_{k,0} \times as_v$$

$$dp_{k,0}=dp_{k,0} + as_v$$

$$as_v = dp_{k,0}+dp_{k,1}+[col_k=x]$$

在 $as_v$ 处加上 $[col_k=x]$ 意为若 $col_k=x$ 则可以加上单独只选它一个的情况。

实现时枚举 $x$，建立所有颜色为 $x$ 的点构建的虚树 $T'$。

对于颜色为 $x$ 的答案为 $\sum_{k\in T'} \bigg(dp_{k,1}+[col_k=x]\times (dp_{k,0}+1)\bigg)$。

## AC code

```cpp
#include<bits/stdc++.h>
#define int long long
#define f(i,j,n) for(int i=j;i<=n;i++)
#define F(i,n,j) for(int i=n;i>=j;i--)
#define updmax(a,b) a=max(a,b)
#define updmin(a,b) a=min(a,b)
#define pb push_back
#define XQZ
using namespace std;
namespace fsd{
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,MAXSIZE,stdin),p1==p2)?EOF:*p1++)
	const int MAXSIZE=1<<20;
	char buf[MAXSIZE],*p1,*p2;
	inline int read(){
		int ak=0,ioi=1;char c=gc();
		while(!isdigit(c)){if(c=='-')ioi=-1;c=gc();}
		while(isdigit(c))ak=ak*10+(c^48),c=gc();
		return ak*ioi;
	}
	inline string reads(){
		string o="";
		char p=gc();
		while(p>'z'||p<'a'){p=gc();}
		while(p<='z'&&p>='a'){o+=p;p=gc();}
		return o;
	}
	inline char readc(){
		char p=gc();
		while(!((p<='z'&&p>='a')||(p<='Z'&&p>='A'))){p=gc();}
		return p;
	}
	inline long double readd(){
		long double ak=0;int ioi=1;char c=gc();
		while(!isdigit(c)){if(c=='-')ioi=-1;c=gc();}
		while(isdigit(c))ak*=10,ak+=c-'0',c=gc();
		c=gc();
		long double q=0.1;
		while(isdigit(c))ak+=(c-'0')*q,q*=0.1,c=gc();
		return ak*ioi;
	}
}
using namespace fsd;
int n;
const int N=2e5+10;
int col[N];
vector<int> cp[N];
vector<int> h[N];
vector<pair<int,int> > h1[N];
int dep[N],dp[N][20];
int dfn[N];
void dfs(int k,int prt,int dpe){
	dep[k]=dpe,dp[k][0]=prt;dfn[k]=++(*dfn);
	for(auto v:h[k]){
		if(v==prt)continue;
		dfs(v,k,dpe+1);
	}
}
void init(){
	dfs(1,0,1);
	f(j,1,19)f(i,1,n)dp[i][j]=dp[dp[i][j-1]][j-1];
}
pair<int,int> getl(int a,int b){
	if(dep[a]<dep[b])swap(a,b);
	int l=0;
	F(j,19,0){
		if(dep[dp[a][j]]>=dep[b])l+=1<<j,a=dp[a][j];
	}
	if(a==b)return {a,l};
	F(j,19,0){
		if(dp[a][j]!=dp[b][j])l+=1<<j+1,a=dp[a][j],b=dp[b][j];
	}
	return {dp[a][0],l+2};
}
void link(int a,int b){
	int s=getl(a,b).second;
	h1[a].push_back({b,s}),h1[b].push_back({a,s});
}
int st[N],top,abb[N][3],as[N],ans;
const int mod=998244353;
void dfs1(int k,int prt,int up,int cl){
	for(auto [v,p]:h1[k]){
		if(v==prt)continue;
		dfs1(v,k,p,cl);
		abb[k][1]=(abb[k][1]*(as[v]+1)%mod+abb[k][0]*as[v]%mod)%mod;
		abb[k][0]=(abb[k][0]+as[v])%mod;
	}
	as[k]=(abb[k][0]+abb[k][1])%mod;
	if(col[k]==cl)as[k]=(as[k]+1)%mod;
	if(col[k]==cl)ans=(ans+as[k]%mod)%mod;
	else ans=(ans+abb[k][1]%mod)%mod;
}
void clear(int k,int prt){
	as[k]=abb[k][0]=abb[k][1]=abb[k][2]=0;
	for(auto [v,p]:h1[k]){
		if(v==prt)continue;
		clear(v,k);
	}
	h1[k].clear();
}
void gs(){
	n=read();
	f(i,1,n)col[i]=read(),cp[col[i]].push_back(i);
	f(i,1,n-1){
		int p=read(),q=read();
		h[p].push_back(q),h[q].push_back(p);
	}
	init();
	f(i,1,n){
		if(!cp[i].size())continue;
		sort(cp[i].begin(),cp[i].end(),[&](int a,int b){return dfn[a]<dfn[b];});
		top=0;st[++top]=1;
		f(j,(cp[i][0]==1),(int)cp[i].size()-1){
			int w=cp[i][j];
			int l=getl(w,st[top]).first;
			if(l!=st[top]){
				int ls=-1;
				while(dep[st[top]]>dep[l]){
					if(~ls)link(ls,st[top]);
					ls=st[top--];
				}
				if(st[top]!=l)st[++top]=l;
				if(~ls)link(ls,st[top]);
			}
			st[++top]=w;
		}
		while(top>1)link(st[top],st[top-1]),top--;
		dfs1(1,0,1,i);
		clear(1,0);
	}
	printf("%lld\n",ans);
}
signed main(){
#ifndef XQZ
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
#endif
#ifdef NXD
	int t=0;cin>>t;while(t--)
#endif
		gs();
	return 0;
}
```

---

## 作者：xkcdjerry (赞：8)

好题，好题，第一次场切 G 写个题解纪念一下

首先显然每个颜色可以分开考虑。  
那么这里称颜色与目前考虑相同的为“有色点”，$a_i=0$；与目前考虑不同的为“无色点”，$a_i=1$。  
那么只需要对于每个颜色统计所有叶子节点都是有色点的连通块个数。

钦定 $1$ 为根节点，令 $f_i$ 为 $i$ 子树内叶子全部都为有色点且必须选 $i$ 的方案数。（注意对 $i$ 是否为有色点不做要求）  
那么 $i$ 的每个儿子 $j$ 都可以选或者不选，若选的话又各有 $f_j$ 种方案。故：

$$f_i=\prod_{j \in sons_i} (f_j+1) \space (a_i=0)$$

如果 $a_i=1$，那么 $i$ 的儿子一个都不选因为会产生一个无色叶子所以是非法的，故有：

$$ f_i = -1 + \prod_{j \in sons_j} (f_j+1) \space (a_i=1)$$

现在考虑怎么统计连通块个数：如果让每个连通块在深度最浅的节点处贡献一次，那么每个连通块显然会被统计恰好一次。因此把所有 $f_i$ 加起来就可以了……吗？

注意如果 $i$ 是一个无色点，那么 $i$ 作为最浅点的时候不仅一个儿子都不选是不合法的，只选一个儿子也会导致 $i$ 变成叶子从而不合法。因此无色点 $i$ 的贡献实际为：

$$f_i-\sum_{j \in sons_i} f_j$$

至此，我们有了一个 $O(nC)$ 的做法，其中 $C$ 为不同的颜色个数。

---

考虑优化：  
首先显然所有无色叶子均是无用的，那么可以不断删除无色叶子直到所有叶子均为有色点。  
又发现，对于树内的无色点 $i$，若其只存在一个儿子 $x$，那么有 $f_i=-1+(f_x+1)=f_x$，贡献为 $f_i-f_x=0$，那么将 $i$ 直接删除对答案没有影响。  
换句话说，我们只需要保留有色点和至少有两个儿子的子树内存在有色点的无色点，**即所有有色点的虚树。**

由于对于所有颜色共有 $n$ 个有色点，那么虚树的总大小也不会超过 $2n$。  
由于被删除的点对答案无影响，可以不做任何修改直接在虚树上跑原来的树 dp，总复杂度为 $O(n)$ 且代码很干净。

赛时为了方便调试采用了 $O(|S| \log n)$ 建虚树。   
```c++
#include <cstdio>
#include <vector>
#include <algorithm>
#define N 200010
#define P 998244353
#define ll long long
using std::vector;
int n,a[N];
vector<int> e[N];

int sz[N],heavy[N],fa[N],dep[N];
void dfs1(int x,int F)
{
    sz[x]=1, fa[x]=F, dep[x]=dep[F]+1;
    for(auto i:e[x]) if(i!=F)
    {
        dfs1(i,x), sz[x]+=sz[i];
        if(sz[i]>sz[heavy[x]]) heavy[x]=i;
    }
}
int dfn[N],cur,root[N];
void dfs2(int x,int R)
{
    dfn[x]=++cur, root[x]=R;
    if(!heavy[x]) return;
    dfs2(heavy[x],R);
    for(auto i:e[x]) if(i!=fa[x]&&i!=heavy[x])
        dfs2(i,i);
}
int lca(int u,int v)
{
    for(;root[u]!=root[v];u=fa[root[u]])
        if(dep[root[u]]<dep[root[v]]) {int t=u; u=v; v=t;}
    return dep[u]<dep[v]?u:v;
}
vector<int> eg[N];
vector<int> fake(vector<int> v)
{
    auto cmp=[&](int x,int y){return dfn[x]<dfn[y];};
    vector<int> ans=v; std::sort(v.begin(),v.end(),cmp);
    for(int i=1;i<v.size();i++) ans.push_back(lca(v[i-1],v[i]));
    ans.push_back(1); sort(ans.begin(),ans.end(),cmp);
    ans.resize(std::unique(ans.begin(),ans.end())-ans.begin());
    static int stk[N]; int top=0;
    for(auto i:ans)
    {
        if(top)
        {
            int t=lca(i,stk[top-1]);
            while(stk[top-1]!=t) top--;
            eg[t].push_back(i);
        }
        stk[top++]=i;
    }
    return ans;
}
ll f[N],ans;
void dfs(int x,int C)
{
    f[x]=1; ll tot=0; for(auto i:eg[x])
        dfs(i,C), tot+=f[i], (f[x]*=(f[i]+1))%=P;
    a[x]!=C?f[x]-=1,ans+=f[x]-tot:ans+=f[x];
}
vector<int> dots[N];
int main()
{
    scanf("%d",&n); for(int i=1;i<=n;i++)
        scanf("%d",a+i), dots[a[i]].push_back(i);
    for(int i=1,u,v;i<n;i++)
        scanf("%d%d",&u,&v),
        e[u].push_back(v),e[v].push_back(u);
    dfs1(1,0), dfs2(1,1);
    for(int i=1;i<=n;i++) if(!dots[i].empty())
    {
        vector<int> v=fake(dots[i]);
        dfs(1,i); for(auto j:v) eg[j].clear();
    }
    printf("%lld",ans%P);
}
```

---

## 作者：喵仔牛奶 (赞：4)

# Solution
## Part I

题目告诉我们，一个合法的子图叶子的颜色一样。考虑枚举每个颜色 $col$ 算贡献。我们把 $c_u=col$ 的点 $u$ 叫做关键点。

在原图处理出深度，我们考虑在一个子图中深度最小的点计算这个子图的贡献。

- 设 $f_{u,0}$ 是只用 $u$ 子树内的点构建子图，$u$ 必选，有多少子图满足叶子颜色是关键点，且 $u$ 的度数 $\leq 1$。
- 设 $f_{u,0}$ 是只用 $u$ 子树内的点构建子图，$u$ 必选，有多少子图满足叶子是关键点，且 $u$ 的度数 $\geq 2$。

转移如下：
- $f_{u,0}\gets 0$，$f_{u,1}\gets 0$。
- 枚举 $u$ 的儿子 $v$： 
	- $f_{u,1}\gets f_{u,1}\times(f_{v,0}+f_{v,1}+1)+f_{u,0}\times(f_{v,0}+f_{v,1})$。
	- $f_{u,0}\gets f_{u,0}+f_{v,0}+f_{v,1}$。
- 若 $u$ 是关键点，则 $f_{u,0}\gets f_{u,0}+1$（算上只选 $u$ 一个点的方案）。

因为 $u$ 度数 $\leq 1$ 时需要满足 $u$ 是关键点，所以这种颜色的答案就是 $\sum_{u=1}^{n}f_{u,0}\times[c_u=col]+f_{u,1}$。

暴力 DP 就可以做到 $\mathcal{O}(n^2)$。

## Part II

发现父亲转移时儿子对父亲答案的影响只与 $(f_{v,0}+f_{v,1})$ 有关。而且，如果 $fa_u$ 不是关键点，则 $f_{fa_u,0}+f_{fa_u,1}=f_{u,0}+f_{u,1}$。

这启示我们对每种颜色建虚树，在虚树上跑 DP 就可以跑出正确的值。

那算答案呢？发现贡献不为 $0$ 的 $u$ 一定满足以下两个条件之一：
- $u$ 是关键点。
- $u$ 存在两个不同的儿子 $v_1,v_2$，使得 $v_1,v_2$ 的子树内都有关键点。

这样的点一定在虚树上，所以说只对虚树上的点算答案就可以算对。~~所以 DP 部分一个字符也不用改。~~

时间复杂度 $\mathcal{O}(n\log n)$。

# Code

```cpp
// writer: Milkcat
// time: 2024.2.11 23:11
#include <bits/stdc++.h>
#define REP(i, l, r) for (int i = (l); i <= (r); ++ i)
#define DEP(i, r, l) for (int i = (r); i >= (l); -- i)
#define fi first
#define se second
#define pb emplace_back
#define mems(x, v) memset((x), (v), sizeof(x))
using namespace std;
namespace Milkcat {
	typedef long long LL;
	typedef pair<LL, LL> pii;
	const int N = 1e6 + 5, mod = 998244353;
	LL n, u, v, ans, c[N], f[N][2];
	vector<int> G[N], R[N], sc[N];
	
	int tot, id[N], dfn[N], st[21][N];
	void dfs1(int u, int fa) {
		dfn[u] = ++ tot, id[tot] = u, st[0][tot] = dfn[fa];
		for (int v : G[u])
			if (v != fa) dfs1(v, u);
	};
	int lca(int u, int v) {
		if (u == v) return u;
		if ((u = dfn[u]) > (v = dfn[v])) swap(u, v);
		int d = __lg(v - u ++);
		return id[min(st[d][u], st[d][v - (1 << d) + 1])];
	}
	void Buildvt(vector<int> t, int n, vector<int>& s) {
		auto cmp = [&](int x, int y) { return dfn[x] < dfn[y]; };
		sort(t.begin(), t.end(), cmp), s = t;
		REP(i, 1, (int)t.size() - 1) s.pb(lca(t[i - 1], t[i]));
		sort(s.begin(), s.end(), cmp), s.erase(unique(s.begin(), s.end()), s.end());
		REP(i, 1, (int)s.size() - 1) {
			int u = lca(s[i - 1], s[i]), v = s[i];
			R[u].pb(v), R[v].pb(u);
		}
	}
	
	void dfs(int u, int fa, int col) {
		for (int v : R[u]) {
			if (v == fa) continue;
			dfs(v, u, col);
			LL p = f[v][0] + f[v][1];
			f[u][1] = (f[u][0] * p + f[u][1] * (p + 1)) % mod;
			f[u][0] = (f[u][0] + p) % mod;
		}
		if (c[u] == col) f[u][0] ++, ans = (ans + f[u][0]) % mod;
		ans = (ans + f[u][1]) % mod;
	}
	int main() {
		cin >> n;
		REP(i, 1, n) cin >> c[i], sc[c[i]].pb(i);
		REP(i, 2, n) cin >> u >> v, G[u].pb(v), G[v].pb(u);
		
		dfs1(1, 0);
		for (int i = 1; i <= __lg(n); i ++)
			for (int j = 1; j + (1 << i) - 1 <= n; j ++)
				st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
		
		REP(i, 1, n) {
			if (!sc[i].size()) continue;
			vector<int> s;
			Buildvt(sc[i], n, s), dfs(s[0], 0, i);
			for (int u : s)
				R[u].clear(), f[u][0] = f[u][1] = 0;
		}
		cout << ans << '\n';
		return 0;
	}
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int T = 1;
    while (T --) Milkcat::main();
    return 0;
}
```

---

## 作者：Register_int (赞：4)

直接对于每一种颜色单独统计答案。设 $dp_{u,c}$ 表示以 $u$ 为根且 **除 $u$ 以外** 任意叶子颜色均为 $c$ 的联通块的个数。此时有转移：

$$dp_{u,c}=\prod_v(dp_{v,c}+1)-[a_u\not=c]$$

前半部分指每个儿子所在的子树可以随便选，后面则是减去全都不选的方案。统计答案时，我们要扣除以 $u$ 为根但 $u$ 是颜色不为 $c$ 的叶子的方案。对于每个 $u$，他对颜色 $c$ 造成的总贡献为：

$$dp_{u,c}-[a_u\not=c]\left(1+\sum_vdp_{v,c}\right)$$

减去的式子是只有一个及以下子树选了点的方案。可以发现，对于每种颜色 $c$ 的转移，它所用到的转移点均在颜色为 $c$ 的点构成的虚树上，暴力枚举颜色建虚树 dp 即可。时间复杂度 $O(n\log n)$。

这里可以偷个懒，求完虚树时我们已经把 dfs 序拍下来了，可以直接倒序转移，不用再写一个搜。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;
const int mod = 998244353;

vector<int> g[MAXN], tg[MAXN], col[MAXN];

int d[MAXN], fa[MAXN][18], lg[MAXN], dfn[MAXN], id;

void init(int u, int f) {
	d[u] = d[f] + 1, fa[u][0] = f, dfn[u] = ++id;
	for (int i = 1; i <= lg[d[u]]; i++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
	for (int v : g[u]) if (v != f) init(v, u);
}

inline 
int lca(int u, int v) {
	if (d[u] < d[v]) swap(u, v);
	for (; d[u] > d[v]; u = fa[u][lg[d[u] - d[v]]]);
	if (u == v) return u;
	for (int i = lg[d[u]]; ~i; i--) if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}

inline 
bool cmp(int x, int y) {
	return dfn[x] < dfn[y];
}

int n, a[MAXN], t[MAXN << 1], cnt; ll dp[MAXN];

inline 
ll solve(int k) {
	sort(col[k].begin(), col[k].end(), cmp), cnt = 0;
	for (int x : col[k]) t[++cnt] = x;
	for (int i = 1; i < col[k].size(); i++) t[++cnt] = lca(col[k][i - 1], col[k][i]);
	sort(t + 1, t + cnt + 1, cmp), cnt = unique(t + 1, t + cnt + 1) - t - 1;
	for (int i = 2; i <= cnt; i++) tg[lca(t[i - 1], t[i])].push_back(t[i]);
	ll res = 0;
	for (int i = cnt, u; i; i--) {
		u = t[i]; ll x = 1, y = 1;
		for (int v : tg[u]) x = x * (dp[v] + 1) % mod, y = (y + dp[v]) % mod;
		dp[u] = x;
		if (a[u] == k) res = (res + x) % mod;
		else res = (res + x - y + mod) % mod, dp[u]--;
	}
	for (int i = 1; i <= cnt; i++) tg[t[i]].clear();
	return res;
}

ll ans;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), col[a[i]].push_back(i);
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v), g[u].push_back(v), g[v].push_back(u);
	}
	for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1; init(1, 0);
	for (int i = 1; i <= n; i++) ans = (ans + solve(i)) % mod;
	printf("%lld", ans);
}
```

---

## 作者：anthonyaaabc (赞：3)

## **简要题意**
给你一颗树，树上每个节点都有一个颜色，问你有多少个子图所有入度为1的点颜色相同。

## 思路
可以考虑一个简单的 dp:

设状态 $dp[i][j]$ 为以 $i$ 为根颜色为 $j$ 的先不考虑根是否入度为 $1$ 以及根的颜色有多少种不同的子图。

显然有转移: 

$$ dp[i][j] = dp[i][j] + dp[v][j] +dp[i][j] \times dp[v][j] $$

其中 $v$ 是 $i$ 的儿子，这个转移的意义就是 $j$ 的子图可以直接继承，也可以与其他的子图合并，合并后子图的根也是在 $i$ 的。 将所有儿子都合并之后，可以将 $dp[i][a[u]]$ 加上 $1$，其中 $a[u]$ 是 $u$ 节点的颜色。 这么做是因为还有一种额外的情况是只有 $u$ 的子图也是合法的。考虑答案 $ans$ 怎么通过这个 dp 统计。 发现每次转移过程中的 $dp[i][j] \times dp[v][j]$ 部分都是可以直接记入答案的，因为此时的根一定度数是大于 $1$ 的，不需要考虑根是否复合要求。还有一种情况是根虽然度数是 $1$ ，但也是符合要求的。 这种可以在转移过程中直接将 $dp[v][a[u]]$ 计入答案，最后再把只有一个点的情况也算上。

这样就得到了一个复杂度为 $ O( n^2 )$ 的 dp 做法了。

观察发现这个 dp 是符合线段树合并的优化的，直接使用线段树合并维护这个 dp ，由于只需要单点合并，是比较好维护的。

复杂度为 $O(n \log n)$ 的。

## 参考代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define lson t[u].ls
#define rson t[u].rs
const int N=200005;
const int mo=998244353;
int n;
vector<int>g[N];
int p;
struct seg
{
    int ls,rs;
    long long val;
}t[605*N];
void change(int &u,int l,int r,int x,long long y)
{
    if(u==0)
    {
        u=++p;
        t[u].ls=0,t[u].rs=0;
        t[u].val=0;
    }
    if(l==r)
    {
        t[u].val+=y;
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid)
    {
        change(lson,l,mid,x,y);
    }
    else
    {
        change(rson,mid+1,r,x,y);
    }
    t[u].val=(t[lson].val+t[rson].val)%mo;
}
long long get(int u,int l,int r,int x)
{
    if(u==0)return 0;
    if(l==r)
    {
        return t[u].val;
    }
    int mid=(l+r)>>1;
    if(x<=mid)
    {
        return get(lson,l,mid,x);
    }
    else
    {
        return get(rson,mid+1,r,x);
    }
}
long long ans=0;
int merge(int x,int y,int l,int r)
{
    if(x==0||y==0)return x+y;
    if(l==r)
    {
        long long vl=t[x].val*t[y].val%mo;
        ans+=vl;
        ans%=mo;
        t[x].val=(t[x].val+t[y].val)%mo+vl;
        t[x].val%=mo;
 
        return x;
    }
    int mid=(l+r)>>1;
    t[x].ls=merge(t[x].ls,t[y].ls,l,mid);
    t[x].rs=merge(t[x].rs,t[y].rs,mid+1,r);
    t[x].val=(t[t[x].ls].val+t[t[x].rs].val)%mo;
    return x;
}
int rt[N];
int a[N];

void dfs(int u,int f)
{
    long long sm=0;
    for(int i=0;i<g[u].size();i++)
    {
        int v=g[u][i];
        if(v==f)continue;
        dfs(v,u);
        sm+=get(rt[v],1,n,a[u]);
        sm%=mo;
        rt[u]=merge(rt[u],rt[v],1,n);
    }
    
    ans+=(sm+1)%mo;
    ans%=mo;
    change(rt[u],1,n,a[u],1);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    for(int i=1;i<n;i++)
    {
        int x,y;
        cin>>x>>y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    t[0]={0,0,0};
    dfs(1,0);
    cout<<ans<<'\n';
}
```



---

## 作者：ReTF (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc340_g)

首先对每个颜色建虚树，把虚树上所有该颜色的点记作关键点，然后 dp。

设 $f_i$ 表示在 $i$ 的子树中选取一个非空子集，且子集中的任意两个数不存在祖先/后代关系的方案数。有如下转移：

$$f_i=(\prod_{s\in son_i}(f_s+1))-1$$

考虑题目要求的连通块中深度最小的节点，该节点为连通块的叶子或非叶子。
枚举该节点，若该节点为叶子，则答案为其子节点的 $f$ 值之和。
若该节点为非叶子，枚举最靠右且与连通块有交集的儿子，类似背包转移即可。最后答案是两个加起来。

[代码](https://atcoder.jp/contests/abc340/submissions/50183105)

---

## 作者：_Ch1F4N_ (赞：3)

第一次 AK ABC，写一下题解。

我们定义 $dp_{u,i}$ 表示以 $u$ 为根且叶子节点颜色为 $i$ 的合法方案数。

假若 $col_{u} = i$ 那么点 $u$ 的度数可以为 $1$，也就是说额外的贡献是 $\sum_{v \in u} dp_{v,col_{u}}$。

然后的常规贡献就考虑在计算 $dp_{u,i}$ 的时候算出来。

每新增一个儿子 $v$，那么原来的子树可以与现在的子树任意组合，也就是 $dp_{u,i} \to dp_{u,i} \times dp_{v,i} + dp_{u,i} + dp_{v,i}$，但是贡献只会是 $dp_{u,i} \times dp_{v,i}$ 因为度数大于 $1$，然后你发现对于 $dp_{v,i} = 0$ 的情况不更新也不产生贡献，所以直接记录下子树内的所有颜色然后树上启发式合并即可。

考虑用哈希表存储所有状态，时间复杂度 $O(n \log n)$，常数有点大但是通过很轻松。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn =2e5+114;
const int mod = 998244353;
unordered_map<int,int> dp[maxn];
unordered_set<int> col[maxn];
int son[maxn],sz[maxn];
vector<int> E[maxn];
int n,ans;
void dfs1(int u,int fa){
    sz[u]=1;
    for(int v:E[u]){
        if(v==fa) continue;
        dfs1(v,u);
        if(sz[v]>sz[son[u]]) son[u]=v;
        sz[u]+=sz[v];
    }
}
int a[maxn];
void dfs2(int u,int fa){
    for(int v:E[u]){
        if(v!=fa) dfs2(v,u),ans+=dp[v][a[u]],ans%=mod;//d[root]=1
    }
    if(son[u]!=0) swap(dp[u],dp[son[u]]),swap(col[u],col[son[u]]);
    for(int v:E[u]){
        if(v!=fa&&v!=son[u]){
            for(int x:col[v]){
                ans+=(dp[u][x]*dp[v][x]%mod);
                ans%=mod;
                dp[u][x]=(dp[u][x]*dp[v][x]%mod+dp[u][x]+dp[v][x])%mod;
                col[u].insert(x);
            }
        }
    }
    dp[u][a[u]]=(dp[u][a[u]]+1)%mod;
    ans++;
    ans%=mod;
    col[u].insert(a[u]);
    return ;
}
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=2;i<=n;i++){
        int u,v;
        cin>>u>>v;
        E[u].push_back(v);
        E[v].push_back(u);
    }
    dfs1(1,0);
    dfs2(1,0);
    cout<<ans<<'\n';
    return 0;
}

```

虽然理论复杂度还行，但是用了哈希表，不优美，考虑把上面那一套搬到线段树合并上，具体而言我们在合并的时候计算答案即可，这样跑得飞快，给出代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5+114;
const int mod = 998244353;
int dp[maxn*50],ls[maxn*50],rs[maxn*50],tot;
int rt[maxn];
int col[maxn],n;
vector<int> E[maxn];
int ans;
void ins(int &cur,int lt,int rt,int x){
    if(cur==0) cur=++tot;
    if(lt==rt){
        dp[cur]=(dp[cur]+1)%mod;
        return ;
    }
    int mid=(lt+rt)>>1;
    if(x<=mid) ins(ls[cur],lt,mid,x);
    else ins(rs[cur],mid+1,rt,x);
}
int ask(int cur,int lt,int rt,int x){
    if(cur==0) return 0;
    if(lt==rt) return dp[cur];
    int mid=(lt+rt)>>1;
    if(x<=mid) return ask(ls[cur],lt,mid,x);
    else return ask(rs[cur],mid+1,rt,x);
}
int merge(int u,int v,int lt,int rt){
    if(u==0||v==0) return u+v;
    if(lt==rt){
        ans=(ans+dp[u]*dp[v])%mod;
        dp[u]=(dp[u]*dp[v]+dp[u]+dp[v])%mod;
        return u;
    }
    int mid=(lt+rt)>>1;
    ls[u]=merge(ls[u],ls[v],lt,mid);
    rs[u]=merge(rs[u],rs[v],mid+1,rt);
    return u;
}
void dfs(int u,int fa){
    for(int v:E[u]){
        if(v!=fa){
            dfs(v,u);
            ans=(ans+ask(rt[v],1,n,col[u]))%mod;
            rt[u]=merge(rt[u],rt[v],1,n);
        }
    }
    ans=(ans+1)%mod;
    ins(rt[u],1,n,col[u]);
    return ;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>col[i];
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        E[u].push_back(v);
        E[v].push_back(u);
    }
    dfs(1,0);
    cout<<ans<<'\n';
    return 0;
}

```


---

## 作者：tyr_04 (赞：2)

[传送门](https://www.luogu.com.cn/problem/AT_abc340_g)

1h 场切，紫的原因是虚树，建完虚树就成功了一大半。

### 思路

先将同一种颜色的节点放到一组，每组分别建一棵虚树，此时树上已经规避掉了大量无用信息。

注意题目中导出的子图是一颗无根树，考虑对于每一个节点分别计算导出的无根树中包含这个节点情况数。

对于第 $x$ 个节点计算出 $now_x$，表示以当前节点为根时子树的叶子节点为当前颜色的情况数（不考虑根是否为当前颜色，建完虚树后树的形态已经确定）。

对于节点 $x$ 的子节点 $y$，计所有 $now_y+1$ 的积为 $p$，所有 $now_y$ 的和为 $sum$。

分以下两种情况：

* 如果当前节点的颜色与当前组的颜色相同，则当前位置可以选择每一个叶子节点是否连边，当前节点对答案的贡献为 $p$；$now_x$ 的值也为 $p$。

* 如果当前节点的颜色与当前组的颜色不同，则当前位置至少要选两个不同的合法叶子节点拼接成一棵合法的树，则当前节点对答案的贡献为总情况数减非法情况数（总情况数为 $p$，不合法情况即为选过的子节点数小于等于 $1$，每个子节点分别贡献一次，此外还有不选任何子节点的 $1$），即 $p-sum-1$；$now_x$ 的值为 $p-1$（根据 $now$ 的定义，只有不选任何子节点的情况不合法，故减一）。

所有答案贡献相加即可，使用二次排序+连边的方式建虚树，在统计每棵树的答案时，每个点最多遍历一次，时间复杂度 $O(n\log n)$。

### code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int n,cnt,dfn[200005],a[200005],sd[200005],fa[200005][25],now[200005],ans=0;
vector<int> v[200005],lx[200005],nv[200005];
bool z[200005],ts[200005];
bool cmp(int x,int y)
{
	return dfn[x]<dfn[y];
}
void dfs(int x,int f)
{
	cnt++;
	dfn[x]=cnt;
	sd[x]=sd[f]+1;
	fa[x][0]=f;
	for(int i=1;i<=20;i++)
	{
		fa[x][i]=fa[fa[x][i-1]][i-1];
	}
	for(int i=0;i<v[x].size();i++)
	{
		int y=v[x][i];
		if(y!=f)
		{
			dfs(y,x);
		}
	}
	return;
}
int lca(int x,int y)
{
	if(sd[x]<sd[y])
	{
		swap(x,y);
	}
	for(int i=20;i>=0;i--)
	{
		if(sd[fa[x][i]]>=sd[y])
		{
			x=fa[x][i];
		}
	}
	if(x==y)
	{
		return x;
	}
	for(int i=20;i>=0;i--)
	{
		if(fa[x][i]!=fa[y][i])
		{
			x=fa[x][i];
			y=fa[y][i];
		}
	}
	return fa[x][0];
}
void xs_dfs(int x,int f)
{
	int sum=1,cs=0;
	for(int i=0;i<nv[x].size();i++)
	{
		int y=nv[x][i];
		if(y!=f)
		{
			xs_dfs(y,x);
			cs++;
			sum*=(now[y]+1);
			sum%=mod;
		}
	}
	if(ts[x]==1)
	{
		ans+=sum;
		ans%=mod;
		now[x]=sum;
	}
	else
	{
		int tj=0;
		for(int i=0;i<nv[x].size();i++)
		{
			int y=nv[x][i];
			if(y!=f)
			{
				tj+=now[y];
				tj%=mod;
			}
		}
		ans=(ans+sum-1-tj+mod);
		ans%=mod;
		now[x]=(sum-1+mod)%mod;
	}
	return;
}
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		lx[a[i]].push_back(i);
	}
	for(int i=1;i<n;i++)
	{
		int x,y;
		cin>>x>>y;
		v[x].push_back(y);
		v[y].push_back(x);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)
	{
		int root=0,maxn=INT_MAX;
		sort(lx[i].begin(),lx[i].end(),cmp);
		for(int j=0;j<lx[i].size();j++)
		{
			z[lx[i][j]]=1;
			ts[lx[i][j]]=1;
			if(sd[lx[i][j]]<=maxn)
			{
				root=lx[i][j];
				maxn=sd[lx[i][j]];
			}
		}
		int o=lx[i].size();
		for(int j=1;j<o;j++)
		{
			int f=lca(lx[i][j-1],lx[i][j]);
			if(z[f]==0)
			{
				z[f]=1;
				lx[i].push_back(f);
				if(sd[f]<=maxn)
				{
					root=f;
					maxn=sd[f];
				}
			}
		}
		sort(lx[i].begin(),lx[i].end(),cmp);
		o=lx[i].size();
		for(int j=1;j<o;j++)
		{
			int f=lca(lx[i][j-1],lx[i][j]);
			if(z[f]==0)
			{
				z[f]=1;
				lx[i].push_back(f);
				if(sd[f]<=maxn)
				{
					root=f;
					maxn=sd[f];
				}
			}
			if(f!=lx[i][j])
			{
				nv[f].push_back(lx[i][j]);
				nv[lx[i][j]].push_back(f);
			}
		}
		if(root!=0)
		{
			xs_dfs(root,0);
		}
		for(int j=0;j<lx[i].size();j++)
		{
			z[lx[i][j]]=0;
			ts[lx[i][j]]=0;
			nv[lx[i][j]].clear();
			now[lx[i][j]]=0;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Anonymely (赞：2)

注意到要求生成树的数量，且给定了度数为 $1$ 的点颜色限制，这启发我们思考如何通过度数为 $1$ 统计生成树数量。

实际上，如果选出度数为 $1$ 的点集，生成树唯一确定，故问题转化为求选出颜色相同的点集数量，满足最后的生成树中度数都为 $1$。

也就是说如果存在 $(1,2),(2,3)$ 两条边，那不能同时让 $1,2,3$ 都度数为 $1$，中间的 $2$ 结点不能作为结束点。

容易发现颜色确定时可以进行一个简单 dp，设 $f_u$ 表示只考虑 $u$ 这颗子树时，存在度数为 $1$ 的点的方案数，转移分 $u$ 颜色是否与枚举的颜色相同做转移

此时复杂度是 $O(n^2)$，但我们注意到做颜色为 $x$ 的转移时有用的只有颜色为 $x$ 的点即他们的“汇合点”，也就是 lca，故建出颜色 $x$ 的虚树做转移即可

复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define QwQ330AwA return 0
#define ll long long

const int N = 2e5 + 5;

int n;
int col[N];
vector <int> pos[N];
vector <int> E[N];
vector <int> e[N];
int dfn[N], tim;
int f[N][19], dep[N];

void dfs(int u, int fa) {
	dfn[u] = ++tim;
	f[u][0] = fa;
	dep[u] = dep[fa] + 1;
	for (int i = 1; i < 19; i++) f[u][i] = f[f[u][i - 1]][i - 1];
	for (auto v : E[u]) if (v != fa) dfs(v, u); 
}

int lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	for (int i = 18; i >= 0; i--) {
		if (dep[f[u][i]] >= dep[v]) u = f[u][i];
	}
	if (u == v) return u;
	for (int i = 18; i >= 0; i--) {
		if (f[u][i] != f[v][i]) u = f[u][i], v = f[v][i];
	}
	return f[u][0];
}

const int mod = 998244353;
ll ans = 0;
int stk[N], top;

#define add(u, v) e[u].push_back(v)

void ins(int u) {
	if (!top) {
		stk[++top] = u;
		return ;
	}
	int lc = lca(stk[top], u);
	while (top >= 2 && dep[stk[top - 1]] > dep[lc]) add(stk[top - 1], stk[top]), top--;
	if (dep[stk[top]] > dep[lc]) add(lc, stk[top]), top--;
	if (!top || stk[top] != lc) stk[++top] = lc;
	stk[++top] = u;
}

int sp;
ll g[N];
vector <int> clr;
void dp(int u) {
	clr.push_back(u);
	ll sum = 1;
	for (auto v : e[u]) dp(v), sum = sum * (g[v] + 1) % mod;
	if (col[u] == sp) {
		ans = (ans + sum) % mod;
		g[u] = sum;
	} else {
		ll res = 0;
		sum = (sum - 1 + mod) % mod;
		for (auto v : e[u]) res = (res + g[v]) % mod;
		ans = (ans + sum - res + mod) % mod;
		g[u] = sum;		
	}
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> col[i];
		pos[col[i]].push_back(i);
	}
	for (int i = 1, u, v; i < n; i++) {
		cin >> u >> v;
		E[u].push_back(v);
		E[v].push_back(u);
	}
	dfs(1, 0);
	for (int i = 1; i <= n; i++) {
		if (pos[i].empty()) continue;
		vector <int> now = pos[i];
		if (col[1] != i) now.push_back(1);
		sort(now.begin(), now.end(), [&](int u, int v) {return dfn[u] < dfn[v];});
		top = 0;
		for (auto x : now) ins(x);
		while (top >= 2) add(stk[top - 1], stk[top]), top--;
		sp = i;
		clr.clear();
		dp(1);
		for (auto x : clr) e[x].clear(), g[x] = 0;
	}
	cout << ans;
	QwQ330AwA;
}
```

---

## 作者：Supor__Shoep (赞：2)

题目要求我们让这个子图中度数为 $1$ 的节点的颜色相同，这启示我们枚举每一个颜色 $col$，然后计算叶子节点全部为 $col$ 的方案数。

对于每一个颜色 $col$，我们考虑计数 DP。先钦定一个根 $root$，设 $dp_i$ 表示在以 $i$ 为根的子树中，包含 $i$ 节点的，**当 $i$ 的父亲节点颜色为 $col$ 时能够合法**的导出子图数量。因此这里 $i$ 可以是任意颜色。为了计算答案，我们记 $f_i$ 表示以 $i$ 为根的子树中，包含 $i$ 节点的合法导出子图数量。这里答案就是 $\begin{aligned}\sum f_i\end{aligned}$ 了。

首先讨论 $dp_i$：

对于每一个儿子 $j$，若只考虑向 $j$ 连边，那么 $j$ 的贡献就是 $dp_j$，当然你不连边的代价就是 $1$，因此根据乘法原理我们得到 $\begin{aligned}dp_i=\prod_{j\in Son(i)}(dp_j+1)\end{aligned}$。

但是要注意：此时的 $dp_i$ 中包含了只选择 $i$ 的情况，当 $i$ 颜色不是 $col$ 时，肯定不合法，因此此时 $\begin{aligned}dp_i=\prod_{j\in Son(i)}(dp_j+1)-1\end{aligned}$。

再讨论 $f_i$：

- 若 $i$ 颜色为 $col$，则 $f_i=dp_i$。

- 否则，我们要减去 $i$ 作为叶子节点的代价，即**容斥**。若 $i$ 只向 $j$ 连边，那么 $j$ 对于 $i$ 的贡献就是 $dp_j$。只选 $i$ 的情况已经在 $dp_i$ 中考虑了，因此 $\begin{aligned}f_i=dp_i-\sum_{j\in Son(i)}dp_j\end{aligned}$。

但是颜色个数可能很多，每次的 DP 太过冗杂了。因此我们再套一个虚树，每次 DP 在虚树上跑就可以了。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5;
const int MOD=998244353;
int n,m;
int head[MAXN],nxt[MAXN<<1],to[MAXN<<1],tot;
void add(int x,int y)
{
	to[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}
int dep[MAXN],anc[MAXN][21],dfn[MAXN],sumdfs;
int vis[MAXN],lg[MAXN];
void dfs_first(int x,int fa)
{
	dfn[x]=++sumdfs,dep[x]=dep[fa]+1,anc[x][0]=fa;
	for(int i=head[x];i;i=nxt[i])
	{
		if(to[i]==fa)	continue;
		dfs_first(to[i],x);
	}
}
int LCA(int x,int y)
{
	if(dep[x]<dep[y])	swap(x,y);
	while(dep[x]>dep[y])	x=anc[x][lg[dep[x]-dep[y]]];
	if(x==y)	return x;
	for(int i=lg[dep[x]];i>=0;i--)
	{
		if(anc[x][i]!=anc[y][i])	x=anc[x][i],y=anc[y][i];
	}
	return anc[x][0];
}
vector<int> vec[MAXN];
int p[MAXN],cnt,k;
int mp[MAXN];
int h[MAXN];
int cmp(int x,int y){ return dfn[x]<dfn[y]; }
int col[MAXN];
vector<int> qs[MAXN];
long long dp[MAXN],f[MAXN],res;
void dfs(int x,int fa)
{
	int len=vec[x].size();
	dp[x]=1;
	long long num=0;
	for(int i=0;i<len;i++)
	{
		int v=vec[x][i];
		if(v==fa)	continue;
		dfs(v,x);
		dp[x]*=(dp[v]+1)%MOD,dp[x]%=MOD;
		num+=dp[v],num%=MOD;
	}
	f[x]=dp[x];
	if(!vis[x])	dp[x]--,dp[x]+=MOD,dp[x]%=MOD,f[x]=dp[x]-num,f[x]+=MOD,f[x]%=MOD;
	res+=f[x],res%=MOD;
}
void read(int &x)
{
	x=0;
	short flag=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	x*=flag;
}
int main()
{
//	freopen("data.in","r",stdin);
//	freopen("data.out","w",stdout);
	read(n);
	int asdf=0;
	for(int i=1;i<=n;i++)	read(col[i]),asdf=max(asdf,col[i]),qs[col[i]].push_back(i);
	for(int i=1;i<n;i++)
	{
		int x,y;
		read(x),read(y);
		add(x,y),add(y,x);
	}
	for(int i=2;i<=n;i++)	lg[i]=lg[i>>1]+1;
	dfs_first(1,0);
	for(int j=1;j<20;j++)
	{
		for(int i=1;i<=n;i++)	anc[i][j]=anc[anc[i][j-1]][j-1];
	}
	for(int t=1;t<=asdf;t++)
	{
		for(int i=1;i<=cnt;i++)	vec[p[i]].clear(),mp[p[i]]=dp[p[i]]=f[p[i]]=0;
		k=qs[t].size();
		if(!k)	continue;
		cnt=0;
		for(int i=1;i<=k;i++)	h[i]=qs[t][i-1],mp[h[i]]=1,p[++cnt]=h[i],vis[h[i]]=1;
		int rt=h[1];
		sort(h+1,h+k+1,cmp);
		for(int i=1;i<k;i++)
		{
			int lca=LCA(h[i],h[i+1]);
			if(!mp[lca])	mp[lca]=1,p[++cnt]=lca;
		}
		sort(p+1,p+cnt+1,cmp);
		for(int i=1;i<cnt;i++)
		{
			int x=p[i],y=p[i+1],z=LCA(x,y);
			vec[z].push_back(y),vec[y].push_back(z);
		}
		dfs(rt,0);
		for(int i=1;i<=k;i++)	vis[h[i]]=0;
	}
	cout<<res;
	return 0;
}
```

---

## 作者：幸存者 (赞：2)

一篇不需要用到虚树的题解，但笔者不太会证明时间复杂度，有没有好心人帮忙证明 / hack？

upd on 2.11：复杂度好像是 $O(n\log^2n)$。

考虑一个很显然的 dp，设 $dp_{i,j}$ 表示 $i$ 子树内的所有度数为 $1$ 的点颜色都为 $j$ 的方案数，注意可以什么都不选，则有 $dp_{i,j}=\prod\limits_{(i,k)\in e}dp_{k,j}$，注意到存在一个特殊情况需要将 $dp_{i,a_i}$ 额外加 $1$。

考虑如何计算答案，我们思考如何通过 $dp_i$ 算出来 $i$ 子树内选 $i$ 的方案数，那么我们需要考虑 $i$ 节点的度数是否为 $1$，于是答案为 $\sum\limits_{j=1}^n(dp_{i,j}-[j\neq a_i]\sum\limits_{(i,k)\in e}(dp_{k,j}-1)-1)$。

我们考虑树上启发式合并，用 map 维护 $dp$，考虑 STL swap 是 $O(1)$ 的，找到 $dp$ 大小最大的一个子结点 $p$ 并把 $dp_i$ 和 $dp_p$ 交换即可。

我们可以考虑同时维护 $dp2_{i,j}$ 代表 $\sum\limits_{(i,k)\in e}(dp_{k,j}-1)$，但计算答案仍然是 $O(\text{siz}(dp_i))$ 的，于是我们可以再维护一个 $f_i=\sum\limits_{j=1}^n(dp_{i,j}-dp2_{i,j}-1)$，然后在 $f_p$ 的基础上修改得到 $f_i$。

最终答案需要再加上 $dp2_{i,a_i}$，对每个 $i$ 这样做即可，具体细节看代码。

```cpp
// superyijin AK IOI
// wangsiyuanZP AK IOI
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define int long long
using namespace std;
int ans, a[200010], f[200010];
vector<int> v[200010], vec[200010];
map<int, int> dp[200010], dp2[200010];
const int mod = 998244353;
void dfs(int x, int fa)
{
	int p = 0;
	for (auto i : v[x])
	{
		if (i == fa) continue;
		dfs(i, x);
		if (dp[i].size() > dp[p].size()) p = i;
	}
	for (auto i : v[x])
	{
		if (i == fa || i == p) continue;
		for (auto j : dp[i]) vec[x].push_back(j.first);
	}
	vec[x].push_back(a[x]);
	sort(vec[x].begin(), vec[x].end());
	vec[x].erase(unique(vec[x].begin(), vec[x].end()), vec[x].end());
	f[x] = f[p];
	for (auto i : vec[p]) f[x] = (f[x] - (dp[p][i] - dp2[p][i] - 1) + mod) % mod, dp2[p][i] = (dp[p][i] - 1 + mod) % mod;
	swap(dp[x], dp[p]);
	swap(dp2[x], dp2[p]);
	for (auto i : v[x])
	{
		if (i == fa || i == p) continue;
		for (auto j : dp[i])
		{
			if (dp[x].count(j.first)) dp[x][j.first] = (dp[x][j.first] * j.second) % mod, dp2[x][j.first] = (dp2[x][j.first] + j.second - 1 + mod) % mod;
			else dp[x][j.first] = j.second, dp2[x][j.first] = (j.second - 1 + mod) % mod;
		}
	}
	if (dp[x].count(a[x])) dp[x][a[x]]++;
	else dp[x][a[x]] = 2;
	dp2[x][a[x]]++;
	for (auto i : vec[x]) f[x] = (f[x] + dp[x][i] - dp2[x][i] - 1 + mod) % mod;
	ans = (ans + f[x] + dp2[x][a[x]]) % mod;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i < n; i++)
	{
		int x, y;
		cin >> x >> y;
		v[x].push_back(y);
		v[y].push_back(x);
	}
	dfs(1, 0);
	cout << ans << endl;
	return 0;
}
// superyijin AK IOI
// wangsiyuanZP AK IOI
```

---

## 作者：MaxBlazeResFire (赞：2)

ABC？真不熟。

看到 $n$ 个点每个点有颜色，立刻想到建虚树。问题转化成虚树上有若干关键点，求满足叶子节点全是关键点的连通块数。

记 $f_{i,0/1/2}$ 表示 $i$ 子树内，以 $i$ 为根的连通块，钦定所有叶子节点都是给定的颜色，点 $i$ 的度数为 $0,1,>1$ 三种情况的方案数，容易做到 $O(n)$。

总复杂度 $O(n\log n)$，瓶颈在于预处理和排序，代码实现中用了欧拉序 $O(1)$ 求 $\rm LCA$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define MAXN 200005
#define mod 998244353

//f[i][0/1/2] 表示考虑子树 i，钦定 i 为连通块根，i 的度数 = 0,= 1,> 1的方案数

int n,c[MAXN],f[MAXN][3],tmp[3],Ans;
int lg2[MAXN << 1],dfn[MAXN],idx,st[19][MAXN << 1],euler[MAXN << 1],edx,pos[MAXN],dep[MAXN];
vector<int> E[MAXN],nE[MAXN],col[MAXN];

inline void chkadd( int &x , int k ){ x += k; if( x >= mod ) x -= mod; }
inline void chkequ( int &x , int k ){ x = k; if( x >= mod ) x -= mod; }

void dp( int x , int fa , int C ){
	f[x][0] = 1,f[x][1] = 0,f[x][2] = 0;
	for( int v : nE[x] ){
		if( v == fa ) continue;
		dp( v , x , C );
		for( int i = 0 ; i < 3 ; i ++ ) tmp[i] = f[x][i],f[x][i] = 0;
		chkadd( f[x][0] , tmp[0] );
		if( c[v] == C ) chkadd( f[x][1] , 1ll * tmp[0] * f[v][0] % mod );
		chkadd( f[x][1] , 1ll * tmp[0] * f[v][1] % mod );
		chkadd( f[x][1] , 1ll * tmp[0] * f[v][2] % mod );
		chkadd( f[x][1] , tmp[1] );
		if( c[v] == C ) chkadd( f[x][2] , 1ll * tmp[1] * f[v][0] % mod );
		chkadd( f[x][2] , 1ll * tmp[1] * f[v][1] % mod );
		chkadd( f[x][2] , 1ll * tmp[1] * f[v][2] % mod );
		chkadd( f[x][2] , 1ll * tmp[2] * f[v][2] % mod );
		if( c[v] == C ) chkadd( f[x][2] , 1ll * tmp[2] * f[v][0] % mod );
		chkadd( f[x][2] , 1ll * tmp[2] * f[v][1] % mod );
		chkadd( f[x][2] , tmp[2] );
	}
}

inline int Min( int u , int v ){ return dep[u] < dep[v] ? u : v; }

inline bool cmp( int u , int v ){ return dfn[u] < dfn[v]; }

inline int Lca( int u , int v ){
	int l = pos[u],r = pos[v]; if( l > r ) swap( l , r );
	int len = lg2[r - l + 1];
	return Min( st[len][l] , st[len][r - ( 1 << len ) + 1] );
}

void dfs( int x , int fa ){
	dfn[x] = ++idx,euler[++edx] = x,pos[x] = edx;
	for( int v : E[x] ){
		if( v == fa ) continue;
		dep[v] = dep[x] + 1,f[0][v] = x,dfs( v , x ),euler[++edx] = x;
	}
}

inline void workC( int C ){
	vector<int> S = col[C]; S.emplace_back( 1 );
	sort( col[C].begin() , col[C].end() , cmp ); int siz = col[C].size();
	for( int i = 0 ; i < siz - 1 ; i ++ ) S.emplace_back( Lca( col[C][i] , col[C][i + 1] ) );
	sort( S.begin() , S.end() , cmp ); int cnt = unique( S.begin() , S.end() ) - S.begin();
	for( int i = 0 ; i < cnt - 1 ; i ++ ){
		int lc = Lca( S[i] , S[i + 1] );
		nE[lc].emplace_back( S[i + 1] ),nE[S[i + 1]].emplace_back( lc );
	} dp( 1 , 0 , C );
	for( int i = 0 ; i < cnt ; i ++ ){
		int ele = S[i];
		chkadd( Ans , f[ele][2] );
		if( c[ele] == C ) chkadd( Ans , f[ele][0] ),chkadd( Ans , f[ele][1] );
	}
	for( int ele : S ) nE[ele].clear(),memset( f[ele] , 0 , sizeof( f[ele] ) );
}

inline void solve(){
	scanf("%d",&n);
	for( int i = 1 ; i <= n ; i ++ ) scanf("%d",&c[i]),col[c[i]].emplace_back( i );
	for( int i = 1 ; i < n ; i ++ ){
		int u,v; scanf("%d%d",&u,&v);
		E[u].emplace_back( v ),E[v].emplace_back( u );
	}
	dfs( 1 , 0 );
	for( int i = 1 ; i <= edx ; i ++ ) st[0][i] = euler[i];
	for( int j = 1 ; j <= 18 ; j ++ )
		for( int i = 1 ; i + ( 1 << j ) - 1 <= edx ; i ++ ) st[j][i] = Min( st[j - 1][i] , st[j - 1][i + ( 1 << ( j - 1 ) )] );
	for( int i = 1 ; i <= n ; i ++ ) workC( i );
	printf("%d\n",Ans);
}

signed main(){
	for( int i = 2 ; i <= MAXN * 2 - 5 ; i ++ ) lg2[i] = lg2[i >> 1] + 1;
	solve();
	return 0;
}
```

---

## 作者：TernaryTree (赞：2)

首先枚举点的颜色。然后我们会发现把这个颜色所有点找出来，建一个虚树，满足条件的连通块就是虚树上的一个连通块，满足这个连通块的叶子是当前颜色的。

我们就把树上的点分成了两类，一类是当前颜色，一类不是。

dp。

$f_{u,0/1}$ 表示 $u$ 作为最顶端的点的连通块数量，$0$ 表示此时 $u$ 不是当前颜色点，并且只有一条连到子树里面的边；$1$ 表示非 $0$ 的情况。

有显然转移：

$$
\begin{aligned}
f_{u,0}&=
\begin{cases}
\sum\limits_{u\to v} f_{v,0}+f_{v,1}&(a_u\neq now) \\
0&(a_u= now) \\
\end{cases} \\
f_{u,1}&=
\begin{cases}
\prod\limits_{u\to v}(f_{v,0}+f_{v,1}+1)-f_{u,0}-1&(a_u\neq now) \\
\prod\limits_{u\to v}(f_{v,0}+f_{v,1}+1)&(a_u= now) \\
\end{cases} \\
\end{aligned}
$$

算上预处理 Dfn 序 LCA，虚树排序的时间，总复杂度 $\Theta(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxd = 21;
const int maxn = 1e6 + 10;
const int mod = 998244353;

int n;
int a[maxn];
vector<int> g[maxn];
vector<int> p[maxn];
int dfn[maxn], dep[maxn], f[maxn], st[maxd][maxn], idx;
int lg[maxn];

void dfs(int u, int fa) {
	dfn[u] = ++idx;
	dep[u] = dep[fa] + 1;
	f[u] = fa;
	st[0][dfn[u]] = u;
	for (int v : g[u]) if (v != fa) dfs(v, u);
}

int lca(int u, int v) {
	if (u == v) return u;
	if (dfn[u] > dfn[v]) swap(u, v);
	int d = lg[dfn[v] - dfn[u]];
	int x = st[d][dfn[u] + 1], y = st[d][dfn[v] - (1 << d) + 1];
	return f[dep[x] < dep[y] ? x : y];
}

vector<int> tr[maxn];
int dp[maxn][2]; 

void dfs2(int u, int fa, int now) {
	int mul = 1;
	for (int v : tr[u]) {
		if (v == fa) continue;
		dfs2(v, u, now);
	}
	if (a[u] != now) {
		dp[u][0] = 1;
		int mul = 1;
		for (int v : tr[u]) {
			if (v == fa) continue;
			mul = mul * (dp[v][0] + dp[v][1] + 1) % mod;
		}
		for (int v : tr[u]) {
			if (v == fa) continue;
			(dp[u][0] += dp[v][0] + dp[v][1]) %= mod;
		}
		dp[u][1] = (mul - dp[u][0] + mod) % mod;
		dp[u][0] = (dp[u][0] + mod - 1) % mod;
	} else {
		dp[u][0] = 0;
		int mul = 1;
		for (int v : tr[u]) {
			if (v == fa) continue;
			mul = mul * (dp[v][0] + dp[v][1] + 1) % mod;
		}
		dp[u][1] = mul;
	}
//	cout << u << " " << dp[u][0] << " " << dp[u][1] << endl;
}

signed main() {
	cin >> n;
	for (int i = 1, x; i <= n; i++) {
		cin >> a[i];
		p[a[i]].push_back(i);
	}
	for (int i = 1, u, v; i < n; i++) {
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	lg[0] = -1, lg[1] = 0;
	for (int i = 2; i < maxn; i++) lg[i] = lg[i >> 1] + 1;
	dfs(1, 0);
	for (int j = 1; j < maxd; j++) {
		for (int i = 1; i + (1 << j) - 1 <= n; i++) {
			int x = st[j - 1][i], y = st[j - 1][i + (1 << j - 1)];
			st[j][i] = dep[x] < dep[y] ? x : y;
		}
	}
	auto cmp = [] (int u, int v) {
		return dfn[u] < dfn[v];
	};
	int tot = 0;
	for (int i = 1; i <= n; i++) {
		if (!p[i].size()) continue;
		sort(p[i].begin(), p[i].end(), cmp);
		int sz = p[i].size();
		for (int j = 1; j < sz; j++) p[i].push_back(lca(p[i][j - 1], p[i][j]));
		sort(p[i].begin(), p[i].end(), cmp);
		p[i].resize(unique(p[i].begin(), p[i].end()) - p[i].begin());
		sz = p[i].size();
		for (int j = 1; j < sz; j++) {
			int u = p[i][j], v = lca(p[i][j - 1], p[i][j]);
			tr[u].push_back(v), tr[v].push_back(u);
		}
		dfs2(p[i][0], 0, i);
		int cur = 0;
		for (int j = 0; j < sz; j++) (cur += dp[p[i][j]][1]) %= mod;
		(tot += cur) %= mod;
		for (int j = 1; j < sz; j++) {
			int u = p[i][j], v = lca(p[i][j - 1], p[i][j]);
			tr[u].pop_back(), tr[v].pop_back();
		}
	}
	cout << tot;
	return 0;
}

```

---

## 作者：Citnaris (赞：1)

### 思路

考虑 dp，令 $f_{i, j}$ 表示 $i$ 的子树中叶节点颜色为 $j$ 的方案数。

注意到树形 dp 从子树转移来的过程中每个子节点可以选或不选，同时我们需要特殊考虑加入点 $i$ 的情况，有转移方程：$f_{i, j} \leftarrow (\prod_{k\in \text{son}(i)}(f_{k, j} + 1) - 1) + [j = a_i]$。

如何统计“整棵生成树经过 $i$ 并恰好都在 $i$ 子树内”的答案？需要有两类情况会产生贡献：

1. $i$ 子树中选了恰好一个子节点 $j$，并且钦定的颜色等于 $i$ 的颜色，因为此时 $i$ 的度数为 $1$
2. $i$ 子树中选了大于等于两个子节点

此时暴力转移的复杂度为 $\Theta(n ^ 2)$。

看到一个树上点有颜色，然后同种颜色点 ... 想到 dsu on tree，不过需要个 map 是 2log 的，因此考虑线段树合并。

维护一个存每个节点不同钦定颜色的 dp 值的动态开点线段树，dp 转移何以直接通过 $f_{i, j}\leftarrow (f_{i, j} + 1)\times (f_{k, j} + 1) - 1$ 把子节点合并上来。统计答案的形式不是很好搞，而线段树可以维护“全局和”与“单点值”，因此我们令 $F_i = \sum f_{i, j}$。容斥一下，总方案减去不合法的方案，那么完全在 $i$ 子树内的并且经过 $i$ 的生成树的个数是 $F_i - \sum F_j + \sum f_{j, a_i}$。

时间空间复杂度均为 $\Theta (n\log n)$。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int NR = 2e5 + 5;
const int MOD = 998244353;

struct Node {
	int dp, ls, rs;
} t[NR << 5];

int n, tot, ans, a[NR], rt[NR];
vector < int > e[NR];

inline void pushup(int p) {
	t[p].dp = 0;
	if (t[p].ls) t[p].dp += t[t[p].ls].dp;
	if (t[p].rs) t[p].dp += t[t[p].rs].dp;
}

inline void modify(int &p, int l, int r, int x) {
    if (!p) p = ++ tot;
    if (l == r) {
        t[p].dp = (t[p].dp + 1) % MOD;
        return;
    }
    int mid = l + r >> 1;
    if (x <= mid) modify(t[p].ls, l, mid, x);
    else modify(t[p].rs, mid + 1, r, x);
	pushup(p);
}

inline int merge(int a, int b, int l, int r) {
    if (!a) return b;
    if (!b) return a;
    if (l == r) {
        t[a].dp = (t[a].dp + t[b].dp + t[a].dp * t[b].dp) % MOD;
        return a;
    }
    int mid = l + r >> 1;
    t[a].ls = merge(t[a].ls, t[b].ls, l, mid);
    t[a].rs = merge(t[a].rs, t[b].rs, mid + 1, r);
	pushup(a);
    return a;
}

inline int query(int p, int l, int r, int x) {
	if (l == r) return t[p].dp;
	int mid = l + r >> 1;
	if (x <= mid) return query(t[p].ls, l, mid, x);
	else return query(t[p].rs, mid + 1, r, x);
}

inline void dfs(int x, int from) {
	for (auto v : e[x]) {
		if (v == from) continue;
		dfs(v, x);
		ans = (ans + query(rt[v], 1, n, a[x]) - t[rt[v]].dp) % MOD;
		merge(rt[x], rt[v], 1, n);
	}
	modify(rt[x], 1, n, a[x]);
	ans = (ans + t[rt[x]].dp) % MOD;
}

signed main() {
    ios :: sync_with_stdio(false), cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i], rt[i] = i, ++ tot;
	for (int i = 1; i < n; ++i) {
		int u, v; cin >> u >> v;
		e[u].push_back(v), e[v].push_back(u);
	}
	dfs(1, 0);
	cout << (ans + MOD) % MOD << '\n';
	return 0;
}
```

---

## 作者：Fhr_lmz (赞：1)

考虑对每种颜色单独计算答案，枚举颜色 $col$，设 $f_u$ 表示选取的点都在 $u$ 的子树内，且度数小于等于 $1$ 的点的颜色为 $col$ 的方案数，有转移方程：

$$
f_u=\prod\limits_{v\in son_u}(f_v+1)-[a_u\ne col]
$$

最后答案即为所有 $f_u$ 的和，特别的，如果 $u$ 的颜色和 $col$ 不同，那么还要减去 $\sum\limits_{v\in son_u}f_v$，这是因为此时不能只选择其中一支子树，否则 $u$ 点的度数为 $1$，违反题意。

这样做的复杂度是 $\mathcal{O}(n^2)$ 的，无法通过全部数据。

容易发现，单次 dp 中有不少节点的 $f$ 值为 $0$，称颜色为 $col$ 的点为关键点。

容易发现，只有两两关键点的 LCA 的 $f$ 值可能不为 $0$，因此建立这几个关键点的虚树，在虚树上跑 dp 即可。

[AC link。](https://atcoder.jp/contests/abc340/submissions/50234033)

---

## 作者：dengchengyu (赞：1)

## abc340_g

如果我们确定了子图的叶子，那么这个子图就确定了。又由于叶子的颜色要相同，所以每种颜色的贡献是互相独立的。

首先如果一种颜色有 $x$ 个点，那么这种颜色的贡献并不是 $2^x-1$，因为可能有一个合法的子图中，这种颜色的点不在叶子处，答案就会多算。

考虑枚举颜色，把这种颜色的点取出来，建出[虚树](https://www.cnblogs.com/dccy/p/18434450)。然后在虚树上 DP。接下来如果一个点的颜色为我们枚举的这个颜色，我们称这个点有颜色。

设 $f_i$ 表示子树 $i$ 内的合法子图数，这里的合法子图指包含 $i$ 的合法子图或者是空集，如果是空集就要求 $i$ 有颜色，这样才能不多算。那么就有
$$
f_i=\prod_{j\in son_i} f_j
$$
接下来，对于一个有颜色的点 $i$，它可以作为合法子图的叶子，所以它的度数没有限制，答案直接加上 $f_i$，再让 $f_i$ 加一，表示可以为空集。

而对于一个没有颜色的点 $i$，它不可以作为合法子图的叶子，即度数要大于一，于是答案在加 $f_i$ 的基础上还要减去度数为一的子图和空集。即
$$
ans+f_i-1-\Big(\sum_{j\in son_i}f_j-1\Big)\to ans
$$
里面的 $f_j-1$ 是因为要减去 $j$ 子树为空集的情况。

时间复杂度的瓶颈在于建虚树，时间复杂度 $O(n\log n)$。

AC 代码：

```cpp
const int N=2e5+5;
vector<int> g[N],h[N];
int n,co[N];
vector<int> c[N];
int fa[N][18],dep[N],dfn[N],dfn1;
void dfs1(int x,int y){
	dep[x]=dep[y]+1,fa[x][0]=y,dfn[x]=++dfn1;
	fu(i,1,18)fa[x][i]=fa[fa[x][i-1]][i-1];
	for(int v:h[x])if(v!=y)dfs1(v,x);
}
int lca(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int i=dep[x]-dep[y],j=0;i;i>>=1,++j)if(i&1)x=fa[x][j];
	if(x==y)return x;
	fd(i,17,0)if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
int d[N*2],tot,Co;
const int mod=998244353;
int f[N],ans;
void dfs2(int x,int y){
	f[x]=1;
	int sum=0;
	for(int v:g[x]){
		if(v==y)continue;
		dfs2(v,x);
		f[x]=(ll)f[x]*f[v]%mod;
		sum=(sum+f[v])%mod;
		sum=(sum-1)%mod;
	}
	if(co[x]==Co){
		ans=(ans+f[x])%mod;
		f[x]=(f[x]+1)%mod;
	}
	else{
		ans=(ans+f[x])%mod;
		ans=(ans+mod-sum-1)%mod;
	}
}
signed main(){
	cin>>n;
	fo(i,1,n)cin>>co[i],c[co[i]].push_back(i);
	fu(i,1,n){
		int u,v; cin>>u>>v;
		h[u].push_back(v),h[v].push_back(u);
	}
	dfs1(1,0);
	fo(i,1,n){
		if(!c[i].size())continue;
		d[tot=1]=1;
		for(auto j:c[i])d[++tot]=j;
		auto cmp=[](int x,int y)->bool{return dfn[x]<dfn[y];};
		sort(d+1,d+1+tot,cmp);
		for(int o=tot,i=2;i<=o;++i)d[++tot]=lca(d[i],d[i-1]);
		sort(d+1,d+1+tot,cmp);
		tot=unique(d+1,d+1+tot)-d-1;
		fo(i,1,tot)g[d[i]].clear();
		auto add=[](int x,int y)->void{g[x].push_back(y),g[y].push_back(x);return;};
		fo(i,2,tot)add(d[i],lca(d[i],d[i-1]));
		Co=i;
		dfs2(1,0);
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：FReQuenter (赞：0)


首先考虑一个 dp：$f_{i,j}$ 表示以 $i$ 为根的子树中，颜色为 $j$，符合题目要求的子树的数量。

由乘法原理，不难写出转移：$f_{i,j}=(f_{i,j}+1)(f_{k,j}+1)$，其中 $k$ 为 $i$ 的儿子。转移时更新答案，每次加上 $f_{i,j}\times f_{k,j}$。注意更新 $f_{i,a_{i}}$ 要和答案一起 $+1$，答案每次加上 $f_{k,a_{i}}$ 表示单独子树。

这个 dp 是 $O(n^2)$ 的。考虑优化。

注意到更新的时候，只有两棵子树都含有同一个颜色才会更新，而颜色一共就 $n$ 种。所以套上启发式合并，使用 map 维护 $f$ 的 $j$ 那一维就做完了。时间复杂度 $O(n\log^2n)$。

与上面类似地，可以使用线段树代替启发式合并的过程。时间复杂度 $O(n\log n)$。

---

## 作者：Nelofus (赞：0)

不妨设 $f_{u,k}$ 表示 $u$ 子树里有多少以 $u$ 为根的树的叶子节点颜色均为 $k$ 。

那么，若点 $u$ 的颜色不为 $k$ ，则：
$$
f_{u,k}=\prod_{v\in \operatorname{son}(u)}(f_{v,k}+1)-1
$$
$+1$ 表示可以不选这个子树里的。但最终要 $-1$，不能全部不选。

当颜色为 $k$ 的时候可以全都不选，所以不 $-1$ 。

但是在统计的时候不能这样统计，因为根节点的度数可能为 $1$ ，分类讨论：

设点 $u$ 的颜色为 $k$，那肯定都是可以的。这部分的答案就是
$$
f_{u,k}
$$
否则，根节点的度数不能为 $1$ 。也就是至少有两个儿子都有这个颜色的子树时才能被计入答案，减掉所有只选一个的方案数：
$$
f_{u,p}-\sum_{v\in \operatorname{son}(u)}f_{v,p}
$$
最终是：
$$
\sum_{p=1}^{n}f_{u,p}-\sum_{v\in \operatorname{son}{u}}\sum_{p=1}^{n}f_{v,p}+\sum_{v\in \operatorname{son}{u}}f_{v,k}
$$

把每个点 $u$ 的式子加起来，最终答案：

$$
\sum_{p=1}^{n}f_{1,p}+\sum_{u\neq 1}f_{u,col_{fa_u}}
$$

随便用什么东西维护都行，我写了个线段树合并。

最后的式子这个 $f_{1,p}$ 其实可能让人感觉有点惊讶，实际上你可以把每个以点 $u$ 为根的子图**看作是联通了 $1\sim u$ 的路径**，所以统计以 $1$ 为根的子树就能统计所有了。

```cpp
//时光如箭岁月如梭
//时不待我我比它更快一步
#include <bits/stdc++.h>
using i64 = long long;

constexpr int N = 2e5 + 10;
constexpr i64 mod = 998244353;

inline int Plus(const int &x, const int &y) {return x + y >= mod ? x + y - mod : x + y;}
inline int Minu(const int &x, const int &y) {return x - y < 0 ? x - y + mod : x - y;}

int tot = 0;
int ans = 0;
int n;
int deg[N];
int col[N];
std::basic_string<int> G[N];
struct node {
	int ls, rs;
	int val;
} tr[N << 5];
int rt[N];

inline void pushup(int u) {
	tr[u].val = Plus(tr[tr[u].ls].val, tr[tr[u].rs].val);
}

void insert(int &u, const int &x, int l, int r, const i64 &k) {
	if (!u) {
		u = ++tot;
	}
	if (l == r) {
		tr[u].val = Plus(tr[u].val, k);
		return ;
	}
	int mid = l + r >> 1;
	if (x <= mid)
		insert(tr[u].ls, x, l, mid, k);
	if (x > mid)
		insert(tr[u].rs, x, mid + 1, r, k);
	pushup(u);
}
void Mul(int &u, const int &x, int l, int r, const i64 &k) {
	if (!u) {
		u = ++tot;
	}
	if (l == r) {
		tr[u].val = 1ll * (tr[u].val + 1) * k % mod;
		return ;
	}
	int mid = l + r >> 1;
	if (x <= mid)
		Mul(tr[u].ls, x, l, mid, k);
	if (x > mid)
		Mul(tr[u].rs, x, mid + 1, r, k);
	pushup(u);
}

i64 val[N];

std::vector<int> pos;
void merge(int &u, int v, int l, int r) {
	if (!u || !v) {
		u = (u | v);
		return ;
	}
	if (l == r) {
		pos.push_back(l);
		val[l] = val[l] * Plus(1, tr[v].val) % mod;
		return ;
	}
	int mid = l + r >> 1;
	merge(tr[u].ls, tr[v].ls, l, mid);
	merge(tr[u].rs, tr[v].rs, mid + 1, r);
	pushup(u);
}

int query(int u, int l, int r, int x) {
	if (l == r) {
		return tr[u].val;
	}
	int mid = l + r >> 1;
	if (x <= mid)
		return query(tr[u].ls, l, mid, x);
	else
		return query(tr[u].rs, mid + 1, r, x);
}

void dfs(int u, int fa) {
	for (const int &v : G[u]) {
		if (v == fa)
			continue;
		dfs(v, u);
	}
	for (const int &v : G[u]) {
		if (v == fa)
			continue;
		merge(rt[u], rt[v], 1, n);
	}

	std::sort(pos.begin(), pos.end());
	pos.resize(std::unique(pos.begin(), pos.end()) - pos.begin());
	for (const auto &c : pos) {
		Mul(rt[u], c, 1, n, val[c]);
		insert(rt[u], c, 1, n, -1);
		val[c] = 1;
	}
	pos.clear();
	insert(rt[u], col[u], 1, n, 1);
	if (fa != 0)
		ans = Plus(ans, query(rt[u], 1, n, col[fa]));
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;

	for (int i = 1; i <= n; i++)
		val[i] = 1;

	for (int i = 1; i <= n; i++) {
		std::cin >> col[i];
	}
	for (int i = 1; i < n; i++) {
		int u, v;
		std::cin >> u >> v;
		deg[u]++, deg[v]++;
		G[u] += v, G[v] += u;
	}
	dfs(1, 0);
	std::cout << Plus(ans, tr[rt[1]].val) << '\n';
	return 0;
}
```

---

## 作者：Richard_Whr (赞：0)

简要题意：

给你一颗树，每个点有颜色。问你有多少个连通块，度为 $1$  的节点的颜色都相同。

首先考虑 $O(n^2)$ 的做法：

设 $f[u][x]$ 表示以 $u$ 为跟的子树中，必选根有多少种方案，使得**他作为父亲的子树是合法的**。

这样设计的原因是为了方便转移，使得状态具有延续性。

初始 $f[u][x]=1$，表示只选根，但很明显对于 $color[u] \neq x$ 是不合法的，为了方便，我们最后减去即可，这里先假装合法。

对于每一颗子树以 $v$ 为根，都有选和不选两种方案：

- 不选：就是 $f[u][x]$；

- 选：原来的每一种方案和这颗子树中的每个方案都可以配对，因此是乘法原理：$f[u][x] \times f[v][x]$；

因此有： 

$$f[u][x]= \prod\limits_{v\in son[u]} (f[v][x]+1)$$

最后记得将某些不合法情况减去。

不过我们可以发现，真正统计答案的时候，$f$ 内的方案不一定都是合法方案，分情况讨论：

- 当该点颜色就是 $x$ 的时候，以 $u$ 为根的连通块内的所有合法方案数就是 $f[u][x]$。

- 当该点颜色不是 $x$ 的时候，以 $u$ 为根的连通块内所有的合法方案，要减掉我们单独选了某个子树的情况，因为这样根的度为 $1$。

对于第二种情况，我们利用辅助数组 $g$

令：
$$g[u][x]=\sum\limits_{v \in son[u]} f[v][x]$$

此时我们就可以统计答案了，对于每个节点，我们统计连通块以他为根的答案（他的深度最小）。

此时需要敏感的点来了，我们发现对于一种颜色，真正就有价值的点并不多，很多转移都是无效而浪费时间的。

考虑建立虚树，这样我们将每种颜色单独抠出来做，即可保证复杂度为 $O(nlogn)$

[代码](https://atcoder.jp/contests/abc340/submissions/50252501)


---

## 作者：cancan123456 (赞：0)

首先考虑枚举度数为 $1$ 的点是什么颜色的，设为 $c$ 颜色，然后设 $f_u$ 表示选出的树以 $u$ 为根且合法的方案数，显然有转移：

$$f_u=\prod_{v\text{ is }u\text{'s son}}(f_v+1),a_u=c$$

$$f_u=\prod_{v\text{ is }u\text{'s son}}(f_v+1)-1-\sum_{v\text{ is }u\text{'s son}}f_v,a_u\ne c$$

答案为 $\sum f_u$，这样就得到了一个 $O(n^2)$ 的做法。

考虑对每个颜色的所有节点分别建[虚树](https://oi-wiki.org/graph/virtual-tree/)。

容易发现，不在虚树上的点对于 DP 是没有影响的，又因为树上 $k$ 个点构成的虚树大小最多为 $2k-1$，所以总时间复杂度为 $O(n)$ 或 $O(n\log n)$，可以通过此题。

这是一份 $O(n\log n)$ 时间复杂度的代码：

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll mod = 998244353;
const int N = 200005;
int a[N], timer, dfn[N], dep[N], fa[N][18], v[2 * N];
ll f[N], ans;
vector < int > vertex[N];
int LCA(int u, int v) {
	if (dep[u] < dep[v]) {
		u ^= v ^= u ^= v;
	}
	for (int i = 17; i >= 0; i--) {
		if (dep[fa[u][i]] >= dep[v]) {
			u = fa[u][i];
		}
	}
	if (u == v) {
		return u;
	} else {
		for (int i = 17; i >= 0; i--) {
			if (fa[u][i] != fa[v][i]) {
				u = fa[u][i];
				v = fa[v][i];
			}
		}
		return fa[u][0];
	}
}
bool cmp_dfn(int x, int y) {
	return dfn[x] < dfn[y];
}
vector < int > G[N], H[N];
void dfs(int u, int fa) {
	dep[u] = dep[fa] + 1;
	::fa[u][0] = fa;
	for (int i = 1; i < 18; i++) {
		::fa[u][i] = ::fa[::fa[u][i - 1]][i - 1];
	}
	timer++;
	dfn[u] = timer;
	for (int v : G[u]) {
		if (v != fa) {
			dfs(v, u);
		}
	}
}
void dp(int u, int fa, int col) {
	f[u] = 1;
	ll sum = 0;
	for (int v : H[u]) {
		if (v != fa) {
			dp(v, u, col);
			f[u] = f[u] * (f[v] + 1) % mod;
			sum = (sum + f[v]) % mod;
		}
	}
	if (a[u] == col) {
		ans = (ans + f[u]) % mod;
	} else {
		ans = (ans + f[u]) % mod;
		f[u] = (f[u] - 1 + mod) % mod;
		ans = (ans - 1 + mod) % mod;
		ans = (ans - sum + mod) % mod;
	}
}
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	for (int u, v, i = 1; i < n; i++) {
		scanf("%d %d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1, 0);
	for (int u = 1; u <= n; u++) {
		vertex[a[u]].push_back(u);
	}
	for (int i = 1; i <= n; i++) {
		int m = vertex[i].size();
		if (m == 0) {
			continue;
		}
		sort(vertex[i].begin(), vertex[i].end(), cmp_dfn);
		for (int j = 0; j < m - 1; j++) {
			v[2 * j + 1] = vertex[i][j];
			v[2 * j + 2] = LCA(vertex[i][j], vertex[i][j + 1]);
		}
		v[2 * m - 1] = vertex[i][m - 1];
		sort(v + 1, v + 2 * m, cmp_dfn);
		int len = unique(v + 1, v + 2 * m) - v - 1;
		for (int i = 1, lca; i < len; i++) {
			lca = LCA(v[i], v[i + 1]);
			H[lca].push_back(v[i + 1]);
			H[v[i + 1]].push_back(lca);
		}
		dp(v[1], 0, i);
		for (int i = 1; i <= len; i++) {
			H[v[i]].clear();
		}
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：苏联小渣 (赞：0)

怎么最近 ABC 的 G 题都那么离谱的。

考虑枚举每一种颜色 $c$，这些颜色在树上出现的位置，设为 $p_1,p_2,...,p_k$，那么假如我们选出 $p$ 一个子集，使这个子集作为叶子结点的集合，那么叶子结点颜色都一样。这个叶子结点的集合在树上会形成一个最小虚树（即，包含选中的叶子结点且大小最小的连通块），这个虚树会有一个根结点，也就是选出叶子的 LCA，设为 $r$，那么对于这个点集，它的根节点一定是 $r$ 或 $r$ 的祖先。

那么我们分类讨论一下：

第一种，根节点是 $r$，也就是说，我们要在这个点集中选出一些点，使得这些点要么没有祖先关系，要么只选两个并且有祖先后代关系。对同色点集建立虚树，后者容易在虚树上 dfs 一遍解决。

现在我们只需要解决前者。也就是说，在虚树上选出一些关键点，使得它们没有祖先后代关系。考虑 dp，设 $f_x$ 表示在 $x$ 子树中选择的答案，有转移：

$$f_x=\prod _{y \in \text{son}(x)} f_y+[a_x=c] $$

因为既可以在子树中选择，也可以选自己不选子树。注意这样转移是包含了全不选的情况的。

最后 $f_1-1$ 就是这个颜色的答案。

现在考虑第二种，也就是说，对于一个同色点 $x$，我们要在它每一个儿子 $y$ 的子树中，分别选若干个结点，使得它们不存在祖先后代关系，显然对于一个同色的 $x$ 直接对 $f_y-1$ 求和即可。

对每个颜色的虚树都处理一遍，时间复杂度 $O(n \log n)$。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
int n, p, p2, x, y, k, top, ans, h[200010], pd[200010], h2[200010], a[200010], dfn[200010], ask[200010], st[200010], dep[200010], siz[200010], F[200010][18];
int ff[200010], pre[200010];
const int mo = 998244353;
struct node{
	int x, y, next;
}d[400010], f[400010];
void add(int x, int y){
	d[++p].y = y, d[p].next = h[x], h[x] = p;
}
void add2(int x, int y){
	f[++p2].y = y, f[p2].next = h2[x], h2[x] = p2;
}
int cmp(int x, int y){
	return dfn[x] < dfn[y];
}
vector <int> pos[200010];
int LCA(int x, int y){
	if (dep[x] < dep[y]) swap(x, y);
	for (int i=17; i>=0; i--){
		if (dep[F[x][i]] >= dep[y]) x = F[x][i];
		if (x == y) return x;
	} 
	for (int i=17; i>=0; i--){
		if (F[x][i] != F[y][i]){
			x = F[x][i], y = F[y][i];
		}
	}
	return F[x][0];
}
void dfs(int x, int fa){
	dfn[x] = ++dfn[0], dep[x] = dep[fa] + 1;
	for (int i=0; i<17; i++){
		F[x][i+1] = F[F[x][i]][i];
	}
	for (int i=h[x]; i; i=d[i].next){
		int y = d[i].y;
		if (y == fa) continue;
		F[y][0] = x;
		dfs(y, x);
	}
}
void dfs2(int x, int fa){
	pre[x] = 0;
	ff[x] = 1;
	if (pd[x]) siz[x] = 1;
	else siz[x] = 0;
	for (int i=h2[x]; i; i=f[i].next){
		int y = f[i].y;
		if (y == fa) continue;
		dfs2(y, x);
		siz[x] += siz[y];
		ff[x] = 1LL * ff[x] * ff[y] % mo;
		if (pd[x]){
			ans = (ans + ff[y]) % mo;
			ans = (ans - 1 + mo) % mo;
		}
	}
	if (pd[x]) ff[x] = (ff[x] + 1) % mo;
}
int main(){
	scanf ("%d", &n);
	for (int i=1; i<=n; i++){
		scanf ("%d", &a[i]);
		pos[a[i]].push_back(i);
	}
	for (int i=1; i<n; i++){
		scanf ("%d%d", &x, &y);
		add(x, y); add(y, x);
	}
	dfs(1, 0);
	for (int i=1; i<=n; i++){
		if (!pos[i].size()) continue;
		k = top = 0;
		for (int j=0; j<pos[i].size(); j++){
			ask[++k] = pos[i][j];
			pd[pos[i][j]] = 1;
		}
		sort (ask+1, ask+k+1, cmp);
		st[++top] = 1;
		h2[1] = p2 = 0;
		for (int j=1; j<=k; j++){
			if (ask[j] == 1) continue;
			int lca = LCA(ask[j], st[top]);
			if (lca != st[top]){
				while (dfn[lca] < dfn[st[top-1]]){
					add2(st[top-1], st[top]);
					top --;
				}
				if (dfn[lca] > dfn[st[top-1]]){
					h2[lca] = 0;
					add2(lca, st[top]);
					st[top] = lca;
				}
				else{
					add2(lca, st[top]);
					top --;
				}
			}
			st[++top] = ask[j];
			h2[ask[j]] = 0;
		}
		for (int j=1; j<top; j++){
			add2(st[j], st[j+1]);
		}
		dfs2(1, 0);
		ans = (ans + ff[1]) % mo;
		ans = (ans - 1 + mo) % mo;
		for (int j=0; j<pos[i].size(); j++){
			pd[pos[i][j]] = 0;
		}
	}
	printf ("%d\n", ans);
	return 0;
}
```

---

## 作者：ケロシ (赞：0)

首先，这种有颜色一样的限制的时候，可以考虑枚举每种颜色，

而对于每一种颜色，考虑虚树维护。

建出每一种颜色的虚树，考虑 dp。

设 $f_i$ 为在 $i$ 子树中选择 $i$ 点，**除了与父亲的连边待定外，其它都合法**时的方案数，

那么对于子树 $v$，可以考虑选或不选，所以方案数要乘上 $f_v+1$，

注意，如果是非关键点，啥子树都不选的话就变为叶子了，所以需要减去 $1$，

所以列出转移方程 $f_u=(\prod_{v\in son(u)}f_v+1) - [u \in T]$，$T$ 表示非关键点的集合。

然后考虑如何统计答案。

对于每一个节点，

当点 $u$ 为关键点，则无论如何都是合法的，直接加入答案。

如果不是关键点，考虑不合法情况，当只选了一颗子树时，

这个点就变为了顶部叶子，需要减掉这种情况，不合法方案数为 $\sum_{v\in son(u)}f_v$，

还有一种没选子树的情况之前的排掉了，无需考虑。

给出代码。

```cpp
const int N = 2e5 + 5;
const int LN = 21;
int n, a[N];
vector<int> e[N], b[N], g[N];
int d[N], f[N][LN];
int dfn[N], dfncnt;
int h[N], m, A[N << 1], len;
mint F[N]; int vis[N];
mint ans;
// 虚树部分
void dfs0(int u, int fa) {
	dfn[u] = ++dfncnt;
	FOR(i, 1, LN - 1) {
		f[u][i] = f[f[u][i - 1]][i - 1];
	}
	for(int v : e[u]) {
		if(v == fa) continue;
		d[v] = d[u] + 1;
		f[v][0] = u;
		dfs0(v, u);
	}
}
int lca(int u, int v) {
	if(d[u] < d[v]) swap(u, v);
	ROF(i, LN - 1, 0) {
		if(d[f[u][i]] >= d[v]) {
			u = f[u][i];
		}
	} 
	if(u == v) return u;
	ROF(i, LN - 1, 0) {
		if(f[u][i] != f[v][i]) {
			u = f[u][i];
			v = f[v][i];
		}
	}
	return f[u][0];
}
bool cmp(int x, int y) {
	return dfn[x] < dfn[y];
}
void build() {
	sort(h + 1, h + m + 1, cmp);
	FOR(i, 1, m - 1) {
		A[++len] = h[i];
		A[++len] = lca(h[i], h[i + 1]);
	}
	A[++len] = h[m];
	sort(A + 1, A + len + 1, cmp);
	len = unique(A + 1, A + len + 1) - A - 1;
	FOR(i, 1, len - 1) {
		int mid = lca(A[i], A[i + 1]);
		F[mid] = F[A[i + 1]] = 0;
		g[mid].push_back(A[i + 1]);
	}
}
// dp
void dfs(int u, int fa) {
	F[u] = 1; mint sum = 0;
	for(int v : g[u]) {
		if(v == fa) continue;
		dfs(v, u);
		F[u] *= F[v] + 1;
		sum += F[v];
	}
	if(!vis[u]) F[u] -= 1;
	ans += F[u];
	if(!vis[u]) ans -= sum;
}
void solve() {
	cin >> n;
	FOR(i, 1, n) cin >> a[i];
	FOR(i, 1, n) b[a[i]].pb(i);
	REP(_, n - 1) {
		int u, v;
		cin >> u >> v;
		e[u].pb(v);
		e[v].pb(u);
	}
	d[1] = 1;
	dfs0(1, 0);
	FOR(i, 1, n) {
		if(!SZ(b[i])) continue;
		m = len = 0;
		for(int u : b[i]) h[++m] = u;
		FOR(j, 1, m) vis[h[j]] = 1; // 关键点
		build();
		dfs(A[1], 0);
		// 记得清空
		FOR(j, 1, m) vis[h[j]] = 0;
		FOR(j, 1, len - 1) {
			int mid = lca(A[j], A[j + 1]);
			F[mid] = F[A[j + 1]] = 0;
			g[mid].clear();
		}
	}
	cout << ans << endl;
}
```


---

## 作者：Hoks (赞：0)

## 前言
这个题，场上没能写出来，真的是太可惜了。

这场前刚学的虚树，可惜不太熟练，想到了没能补出来。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842)。
## 思路分析
这种题看上去就不太好下手，满足叶子节点的颜色一致貌似没有什么优秀解法了。

考虑对每一种颜色考虑，对于每一种颜色跑一边树形 dp。

定义 $f_i$ 表示 $i$ 点子树方案数，$son_i$ 表示 $i$ 的儿子集合。

那么假设现在枚举到的颜色为 $cur$，对于点 $i$，即有一下两种情况：
1. $a_i=cur$ 时，当前点可以成为断点，子树方案数即为 $\prod\limits_{j\in son_i}(f_j+1)$。
2. $a_i\not=cur$ 时，当前点不可成为断点，子树方案即为 $-1+\prod\limits_{j\in son_i}(f_j+1)$。

接着考虑怎么计算答案。

考虑找到每一个分叉点加上答案。

貌似不太好做，因为如果 $a_i\not=cur$ 时，不能以他为断点，会与儿子单次的贡献重复。

直接容斥减去 $\sum\limits_{j\in son_i}f_j$ 即可。

这样的复杂度来到了 $O(n^2)$。

考虑经典 trick，对着每种颜色建一颗虚树，设 $j$ 这个颜色的关键点为 $k_{j,1\sim m_j}$，因为 $\sum\limits_{j=1}^nm_j=n$，所以复杂度来到 $n\log n$。

接着实现下虚树即可，我这里选择每次建图跑起来舒服点。

**虚树数组记得两倍！！！答案记得取模！！！**
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10,INF=0x3f3f3f3f3f3f3f3f,mod=998244353;
int n,cur,ans,a[N<<1],b[N],mp[N],f[N];vector<int>e[N],g[N];stack<int>st,s;
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
namespace tree_decomposition
{
    int fa[N],son[N],si[N],dep[N];
    int top[N],id[N],dfn[N],ed[N],cnt;
	inline void clear(int n)
	{
		memset(son,0,sizeof son);
		cnt=0;for(int i=1;i<=n;i++) e[i].clear();
	}
    inline void dfs1(int u,int ff)
    {
        fa[u]=ff,si[u]=1,dep[u]=dep[ff]+1;dfn[u]=++cnt;
        for(auto v:e[u])
        {
            if(v==ff) continue;
            dfs1(v,u);
            si[u]+=si[v];
            if(si[son[u]]<si[v]) son[u]=v;
        }ed[u]=++cnt;
    }
    inline void dfs2(int u,int topf)
    {
        top[u]=topf;
        if(son[u]) dfs2(son[u],topf);
        for(auto v:e[u])
        {
            if(v==fa[u]||v==son[u]) continue;
            dfs2(v,v);
        }
    }
    inline int LCA(int x,int y)
    {
        while(top[x]!=top[y])
        {
            if(dep[top[x]]<dep[top[y]]) swap(x,y);
            x=fa[top[x]];
        }
        return dep[x]<dep[y]?x:y;
    }
}
using namespace tree_decomposition;
inline bool cmp(int x,int y)
{
    int k1=(x>0)?dfn[x]:ed[-x],k2=(y>0)?dfn[y]:ed[-y];
    return k1<k2;
}
inline void clear(){while(!s.empty()){int u=s.top();s.pop();f[u]=1,mp[u]=0;e[u].clear();}}
inline void dfs(int u)
{
    f[u]=1;int tot=0;
    for(auto v:e[u]) dfs(v),tot+=f[v],f[u]=(f[u]*(f[v]+1))%mod;
    b[u]!=cur?f[u]-=1,ans+=f[u]-tot:ans+=f[u];
}
signed main()
{
    n=read();for(int i=1;i<=n;i++) g[b[i]=read()].emplace_back(i),f[i]=1;
    for(int i=1,u,v;i<n;i++) u=read(),v=read(),e[u].emplace_back(v),e[v].emplace_back(u);
    dfs1(1,0);dfs2(1,1);for(int i=1;i<=n;i++) e[i].clear();
    for(int i=1,k;i<=n;i++)
    {
        if(g[i].empty()) continue;k=g[i].size();cur=i;
        for(int j=0;j<k;j++) a[j+1]=g[i][j],mp[a[j+1]]=1;sort(a+1,a+k+1,cmp);
        for(int j=1,lca=LCA(a[j],a[j+1]);j<k;j++,lca=LCA(a[j],a[j+1])) if(!mp[lca]) a[++k]=lca,mp[lca]=1;
        int nn=k;for(int j=1;j<=nn;j++) a[++k]=-a[j];if(!mp[1]) a[++k]=1,a[++k]=-1;sort(a+1,a+k+1,cmp);
        for(int j=1;j<=k;j++)
            if(a[j]>0) st.push(a[j]);
            else
            {
                int v=st.top();st.pop();s.push(v);
                if(v!=1) e[st.top()].emplace_back(v);
            }
        dfs(1);clear();
    }print(ans%mod);
    genshin:;flush();return 0;
}
```

---

## 作者：huangrenheluogu (赞：0)

要求叶子节点颜色一样，那就钦定一个叶子的颜色，记这个颜色的集合是 $S$，那么我们做的就是选定 $S_1\subseteq S$，并且把 $S_1$ 中的点两两连边就可以了。

发现这样子计数会算重，于是考虑树形 dp，取出这么多点，并且维持原树的形态，感觉和虚树比较像。

而且发现每种颜色个数总和恰好是 $n$，套上虚树试试看。

$f_u$ 表示以 $u$ 的子树的方案数。

考虑转移，如果 $u$ 的颜色和钦定的相同，那么有：

$$f_u=\prod\limits_{v}(f_v+1)$$

意思是每一个子树可以选择或者不选择。

如果都没有选择，那么 $u$ 强制选择，否则是否强制选择都可以，反正不是叶子。

这时候，$u$ 可以作为根，答案累计上 $f_u$。

当 $u$ 不是根的时候，有类似的转移：

$$f_u=\prod\limits_{v}(f_v+1)-1$$

因为 $v$ 不能都不选择。

这时候，如果 $u$ 作为根，需要选择至少两棵子树。因此，答案需要累加 $f_u-\sum\limits_{v}f_v$。

---

