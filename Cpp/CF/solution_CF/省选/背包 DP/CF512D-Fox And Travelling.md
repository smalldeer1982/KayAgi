# Fox And Travelling

## 题目描述

Fox Ciel is going to travel to New Foxland during this summer.

New Foxland has $ n $ attractions that are linked by $ m $ undirected roads. Two attractions are called adjacent if they are linked by a road. Fox Ciel has $ k $ days to visit this city and each day she will visit exactly one attraction.

There is one important rule in New Foxland: you can't visit an attraction if it has more than one adjacent attraction that you haven't visited yet.

At the beginning Fox Ciel haven't visited any attraction. During her travelling she may move aribtrarly between attraction. After visiting attraction $ a $ , she may travel to any attraction $ b $ satisfying conditions above that hasn't been visited yet, even if it is not reachable from $ a $ by using the roads (Ciel uses boat for travelling between attractions, so it is possible).

 She wants to know how many different travelling plans she can make. Calculate this number modulo $ 10^{9}+9 $ for every $ k $ from $ 0 $ to $ n $ since she hasn't decided for how many days she is visiting New Foxland.

## 说明/提示

In the first sample test for $ k=3 $ there are 4 travelling plans: $ {1,2,3},{1,3,2},{3,1,2},{3,2,1} $ .

In the second sample test Ciel can't visit any attraction in the first day, so for $ k&gt;0 $ the answer is $ 0 $ .

In the third sample test Foxlands look like this:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF512D/addf9e605d9b5e373ca5aa72327b83279751f9e5.png)

## 样例 #1

### 输入

```
3 2
1 2
2 3
```

### 输出

```
1
2
4
4
```

## 样例 #2

### 输入

```
4 4
1 2
2 3
3 4
4 1
```

### 输出

```
1
0
0
0
0
```

## 样例 #3

### 输入

```
12 11
2 3
4 7
4 5
5 6
4 6
6 12
5 12
5 8
8 9
10 8
11 9
```

### 输出

```
1
6
31
135
483
1380
3060
5040
5040
0
0
0
0
```

## 样例 #4

### 输入

```
13 0
```

### 输出

```
1
13
156
1716
17160
154440
1235520
8648640
51891840
259459200
37836791
113510373
227020746
227020746
```

# 题解

## 作者：xht (赞：33)

> [CF512D Fox And Travelling](https://codeforc.es/contest/512/problem/D)

## 题意

- 给定一张 $n$ 个点 $m$ 条边的无向图。
- 一个点只有当**与它直接相连的点中最多只有一个点未被遍历过时**才可被遍历。
- 询问对于每个 $k \in [0,n]$，遍历 $k$ 个点的方案数。
- $n \le 100$，$m \le \frac{n(n-1)}2$，答案对 $10^9+9$ 取模。

## 题解

首先，在环中的点一定不会被遍历。

用类似拓扑排序的过程可以把环上的点全部扔掉，剩下的点会构成若干个有根树和无根树，其中有根树的根是树中**唯一与环中的点相连**的点。

每棵树求出答案后，01 背包合并即可，中间只需要乘上一个组合数。

对于有根树，设 $f_{i,j}$ 为 $i$ 的子树中选 $j$ 个的方案数，那么就是树上背包，同样需要乘上一个组合数。

对于无根树，以树中每个点为根做一次有根树的树上背包，这样会发现每种选择 $i$ 个点的方案会被多算 $s - i$ 次，其中 $s$ 为这棵无根树的大小，那么除掉即可。

总时间复杂度 $\mathcal O(n^3)$，其中背包经过了上下界优化，原理简单来说就是「每对点只会在 LCA 处合并一次」。

## 代码

```cpp
const int N = 107;
int n, m, d[N], w[N], b[N], s[N], S;
vi e[N];
modint p[N], v[N], vp[N], f[N][N], ans[N];

inline modint C(int a, int b) {
	return p[a] * vp[b] * vp[a-b];
}

void dfs(int x, int o, int &s) {
	b[x] = o, ++s;
	for (ui i = 0; i < e[x].size(); i++) {
		int y = e[x][i];
		if (!d[y] && !b[y]) dfs(y, o, s);
	}
}

void dp(int x, int fa) {
	s[x] = 1, f[x][0] = 1;
	for (ui i = 0; i < e[x].size(); i++) {
		int y = e[x][i];
		if (b[x] != b[y] || y == fa) continue;
		dp(y, x);
		for (int j = 0; j < s[y]; j++) f[x][s[x]+j] = 0;
		for (int j = s[x] - 1; ~j; j--)
			for (int k = 1; k <= s[y]; k++)
				f[x][j+k] += f[x][j] * f[y][k] * C(j + k, j);
		s[x] += s[y];
	}
	f[x][s[x]] = f[x][s[x]-1];
}

void get(int x) {
	dp(x, 0);
	for (int i = 0; i <= s[x]; i++) f[0][i] += f[x][i];
}

int main() {
	rd(n), rd(m);
	p[0] = v[0] = 1;
	for (int i = 1; i <= n; i++) p[i] = p[i-1] * i;
	vp[n] = p[n] ^ -1;
	for (int i = n; i; i--) v[i] = p[i-1] * vp[i], vp[i-1] = vp[i] * i;
	for (int i = 1, x, y; i <= m; i++) rd(x), rd(y), e[x].pb(y), e[y].pb(x), ++d[x], ++d[y];
	queue<int> q;
	for (int i = 1; i <= n; i++) if (d[i] <= 1) w[i] = 1, q.push(i);
	while (q.size()) {
		int x = q.front();
		q.pop();
		for (ui i = 0; i < e[x].size(); i++) {
			int y = e[x][i];
			if (--d[y] <= 1 && !w[y]) w[y] = 1, q.push(y);
		}
	}
	for (int i = 1; i <= n; i++) if (d[i] == 1) dfs(i, i, s[i]);
	for (int i = 1; i <= n; i++) if (!d[i] && !b[i]) dfs(i, i, s[i]);
	ans[0] = 1;
	for (int i = 1; i <= n; i++)
		if (i == b[i]) {
			int o = s[i];
			if (d[i] == 1) get(i);
			else {
				for (int j = 1; j <= n; j++)
					if (b[j] == i) get(j);
				for (int j = 0; j <= o; j++) f[0][j] *= v[o-j];
			}
			for (int j = S; ~j; j--)
				for (int k = 1; k <= o; k++)
					ans[j+k] += ans[j] * f[0][k] * C(j + k, j);
			for (int j = 0; j <= o; j++) f[0][j] = 0;
			S += o;
		}
	for (int i = 0; i <= n; i++) print(ans[i]);
	return 0;
}
```

---

## 作者：cosmicAC (赞：21)

这道题$n=100$还有三秒时限，所以大家纷纷使用$O(n^3)$算法通过了。下面我提供一种$O(n^2)$的算法。

首先，把输入的图求边双、缩点。如果一个边双有至少两个点，这个边双中的任何一个点就肯定不可能被遍历到（因为环里没有叶子）。所以，只需要考虑缩点之后的森林，其中有一些点不能选的情况下，遍历$k$个节点的方案数（因为现在可以选的点和原图的点是一一对应的）。

森林里的每棵树显然是独立的。由于可以自由组合，答案的EGF就是每棵树答案的EGF的卷积。所以我们只需要会求每一棵树的答案，就可以用$O(n^2)$的暴力卷积求出整个森林的答案。

考虑一棵树的答案是怎么求出来的。容易发现，最终被遍历到的点一定是这棵（**无根**）树的一些（两两不交的）子树。令$G_t$表示（**无根**）子树$t$答案的EGF，那么这棵树的EGF就等于

$$\sum_{S\textrm{是一些子树的集合}}\prod_{\textrm{子树}t\in S}G_t$$

乍一看挺对的？然而这个等式其实会重复计算一些方案。比如说第一个样例，序列$[1,3,2]$会在子树集合为$\{\{1,2\},\{3\}\}$时计算到，也会在子树集合为$\{\{1\},\{2,3\}\}$时计算到。

但是这个等式在绝大多数情况下都是对的。准确地说，**如果没有选中全部的点，就不会造成重复的计算**。所以分成两部分考虑：选中了这棵树中所有的点时对答案的贡献；没有全部选中时对答案的贡献。整棵树的答案就是把这两部分贡献加起来就行了。

选中了一棵树中全部的点的方案数
---
注意这里用的是“方案数”而不是EGF，因为点数已经被固定了。

考虑枚举**最后一个**遍历到的点。假设其为$p$。此时可以把$p$定为整棵树的根，题目的限制就变成了“**遍历一个点之前，必须遍历其子树中所有的点**”。可以发现这样统计是不重不漏的。

考虑dp。设$F_i$为以$p$为根时，$i$子树内的遍历方案数。由于各个子树之间是独立的，可以自由组合，并且$i$在其子树之内一定最后才被遍历，有一个简单的转移：

$$F_i=(siz_i-1)!\prod_{j\textrm{是}i\textrm{的儿子}}\frac{F_j}{siz_j!}$$

这里的$siz_i$是子树$i$的大小。当然，如果第$i$个点被钦定成不能选的了，就有$F_i=0$。

答案就是$\sum{F_p}$。单遍DP的复杂度是线性的，所以总复杂度$O(n^2)$。

存在至少一个点没有被选中时的EGF
---

随便选一个点$rt$做根。可以发现，此时最多只会有一个被“上下颠倒”了的子树。所以可以想到换根DP。

首先使用上一节的方法，求出以$rt$为根时的所有$F_i$。然后考虑$i$号点子树之内答案的EGF，把它记作$G_i(x)$。要不然是从每个子树选一个$G$组合起来，要不然就是单选一个$F_i$。所以转移是

$$G_i(x)=\frac{F_i}{siz_i!}x^{siz_i}+\prod_{j\textrm{是}i\textrm{的儿子}}G_j(x)$$

这里的卷积暴力实现即可。复杂度分析和树上背包是一模一样的，每一对点只会在它们的$LCA$处对复杂度产生贡献。所以是$O(n^2)$。

然后是换根的部分。我们通过一个DFS枚举每个点$p$，强制这个“上下颠倒”了的子树的根是$p$的父亲。**此时不是$p$后代的点必须全部被选中**。假设$p$子树之外的点全部选中时的方案数是$Out_p$，对整棵树EGF的贡献就是
$$\frac{Out_p}{(siz_{rt}-siz_p)!}x^{siz_{rt}-siz_p}(G_p(x)-\frac{F_p}{siz_p!}x^{siz_p})$$

从$G_p(x)$中扣除最后一项，是因为这里强制至少一个点不被选中了。容易发现每个点计算这个贡献的复杂度是$O(n)$的，所以总复杂度还是$O(n^2)$。

考虑$Out_p$从$p$转移到$p$的一个儿子$i$的过程，可以发现计算过程和$F_p$几乎是一模一样的：

$$Out_i=\frac{(siz_{rt}-siz_i+1)!}{(siz_{rt}-siz_p)!}Out_p\prod_{j\textrm{是}p\textrm{的儿子},j\ne i}\frac{F_j}{siz_j!}$$

这个暴力乘起来即可，复杂度是$O(n^2)$的。和$F$一样需要特判$p$点被钦定成不能选了的情况。

----

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll mod=1e9+9;
int n,m,_,dfn[2010],low[2010],tp,id[2010],cnt;
int siz[2010],Rt,vis[2010],sz[2010],sta[2010],ban[2010];
ll fac[2010],ifc[2010],f[2010],g[2010][2010],h[2010],ans[2010],_ans[2010],F[2010],o[2010];
basic_string<int> vv[2010],v[2010];
ll po(ll a,ll b=mod-2){ll r=1;for(;b;b/=2,a=a*a%mod)if(b&1)r=r*a%mod;return r;}
void tarjan(int p,int fa){
	dfn[p]=low[p]=++_;sta[++tp]=p;
	for(int i:vv[p])if(!dfn[i])
		tarjan(i,p),low[p]=min(low[p],low[i]);
	else if(i!=fa)low[p]=min(low[p],dfn[i]);
	if(low[p]==dfn[p]){
		++cnt;int tot=0;
		while(tp){
			id[sta[tp]]=cnt;
			tot++;
			if(tot>1)ban[cnt]=1;
			if(sta[tp--]==p)break;
		}
	}
}
void dfs(int p,int fa=0){
	f[p]=siz[p]=1;vis[p]=1;
	for(int i:v[p])if(i!=fa){
		dfs(i,p);siz[p]+=siz[i];
		(f[p]*=f[i]*ifc[siz[i]]%mod)%=mod;
	}
	g[p][0]=1;int sz=1;
	for(int i:v[p])if(i!=fa){
		memset(h,0,sizeof h);
		for(int j=0;j<sz+siz[i];j++)
			for(int k=0;k<=siz[i] && k<=j;k++)
				(h[j]+=g[i][k]*g[p][j-k])%=mod;
		sz+=siz[i];
		for(int j=0;j<sz;j++)g[p][j]=h[j];
	}
	(f[p]*=fac[siz[p]-1])%=mod;
	if(ban[p])f[p]=0;
	g[p][siz[p]]=f[p]*ifc[siz[p]]%mod;
}
void dfs2(int p,int fa=0){
	F[p]=sz[p]=1;
	for(int i:v[p])if(i!=fa){
		dfs2(i,p);sz[p]+=sz[i];
		(F[p]*=F[i]*ifc[sz[i]]%mod)%=mod;
	}
	(F[p]*=fac[sz[p]-1])%=mod;
	if(ban[p])F[p]=0;
}
void dfs1(int p,int fa=0){
	ll op=o[p]*ifc[siz[Rt]-siz[p]]%mod;
	for(int i=0;i<siz[p];i++)
		(ans[i+siz[Rt]-siz[p]]+=g[p][i]*op)%=mod;
	dfs2(p);
	(ans[siz[Rt]]+=F[p]*ifc[siz[Rt]])%=mod;
	for(int i:v[p])if(i!=fa){
		o[i]=op;
		for(int j:v[p])if(j!=fa && i!=j)(o[i]*=f[j]*ifc[siz[j]]%mod)%=mod;
		(o[i]*=fac[siz[Rt]-siz[i]-1])%=mod;
		if(ban[p])o[i]=0;
		dfs1(i,p);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	ifc[0]=fac[0]=1;
	for(int i=1;i<=n;i++)ifc[i]=po(fac[i]=fac[i-1]*i%mod);
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		vv[x]+=y,vv[y]+=x;
	}
	for(int i=1;i<=n;i++)if(!dfn[i])tp=0,tarjan(i,0);
	for(int i=1;i<=n;i++)for(int j:vv[i])if(id[j]!=id[i] && !~v[id[j]].find(id[i]))
		v[id[j]]+=id[i],v[id[i]]+=id[j];
	_=1;_ans[0]=1;
	for(int i=1;i<=cnt;i++)if(!vis[i]){
		memset(ans,0,sizeof ans);
		dfs(i);Rt=i;o[Rt]=1;
		dfs1(Rt);
		memset(h,0,sizeof h);
		for(int i=0;i<_+siz[Rt];i++)
			for(int j=0;j<=siz[Rt] && j<=i;j++)
				(h[i]+=ans[j]*_ans[i-j])%=mod;
		_+=siz[Rt];
		memcpy(_ans,h,sizeof _ans);
	}
	for(int i=0;i<=n;i++)
		printf("%lld\n",(_ans[i]*fac[i]%mod+mod)%mod);
	return 0;
}
```

---

## 作者：MatrixCascade (赞：10)

同学推的题，感觉不算很困难（每一步都挺自然的）

首先进行一次拓扑排序，把有可能被删掉的点给筛出来。然后你发现这些点组成的边集构成了一个森林。

里面有两类树，一类是独立的树，另一类是连在一个环上的树。

我们先考虑第二类树，设计 $dp_{i,j}$ 表示以 $i$ 为根的子树中，选 $j$ 个点的方案数。

合并 $i$ 点的子树的答案的时候就直接用树形背包的方法，再加上组合数合并。具体为 $dp_{i,j+k}=dp_{i,j}\times dp_{son,k}\times \binom {j+k}{k}$，这个式子意思就是：$i$ 节点的第 $k$ 个子树的选点方案和前 $k-1$ 个子树的选点方案是不冲突的，因此可以直接相乘再组合数合并答案。注意为了避免重复更新答案，你应该开一个临时数组把答案存进去（也可以倒序枚举），等合并完再转回来。特别的，$dp_{i,siz_i}=dp_{i,siz_i-1}$（根节点必须最后删）

对于第一类树，感觉可以钦定最后一个被删的是哪个点，但更简单的方法是直接对每个点为根跑一遍第二类树的方法，然后发现选 $i$ 个点的情况在**没被选的 $siz-i$ 个点为根的时候**会被统计，因此答案要除以 $siz-i$（如果全选是特殊情况，不需要除）

然后就是森林合并答案，就用类似合并子树的方法组合数合并就可以了。

代码太长就放[提交记录](https://codeforces.com/contest/512/submission/164023646)了。

---

## 作者：louhao088 (赞：7)

可以把选点看为删点，那么题目就变为只有入度为 1 或 0 的点能删，问删 k 个点的方案数。

由此我们可以发现，如果一个点在环中，那他肯定不能删。如果一条链连接两个环他也肯定不能删。我们可以用拓扑排序判断那些点可以删，哪些点不行。

然后我们发现，剩下的点必然构成一个森林，且这其中有一些是有根树，有一些是无根树。有根树是连在不能被选的点上，我们可以先枚举这个点，然后对这个根做树形 dp。

具体如下：我们令 $g[i][j]$ 表示在以 i 为根的子树里，选择 j 个的方案数。转移就是合并子树。$g[i][j]=\sum g[son][k] \times g[i][j-k] \times C^k_j$。

无根树的话，就把这棵树上的每个点都做一次根计算，把答案加起来，在除以 $s-k$，$s$ 表示树的大小，$k$ 表示选 $k$ 个点。

然后把所有答案合并即可。


------------
代码如下

```cpp
// Problem: CF512D Fox And Travelling
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF512D
// Memory Limit: 250 MB
// Time Limit: 3000 ms
// 2022-01-20 09:43:53
// Author : louhao088
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
//static char buf[1000000],*p1=buf,*p2=buf;
//#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
#define pi pair<int,int>
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define ls (rt<<1)
#define rs (rt<<1|1)
#define mid (l+r>>1)
#define lowbit (x&-x)
#define int long long
const int maxn=200+5,M=34005,mod=1e9+9;
inline int read()
{
	char ch=getchar();bool f=0;int x=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
inline void print(int x)
{
    static int a[55];int top=0;
    if(x<0) putchar('-'),x=-x;
    do{a[top++]=x%10,x/=10;}while(x);
    while(top) putchar(a[--top]+48);
}
int n,m,inv[maxn],fac[maxn],in[maxn],c[maxn],f[maxn],sum[maxn],s[maxn],g[maxn][maxn],h[maxn],vis[maxn],x,y,st[maxn],p[maxn],tot,iv[maxn];
vector<int>e[maxn];queue<int>q;
int Pow(int x,int y){int res=1;while(y){if(y&1)res=res*x%mod;x=x*x%mod;y=y/2;};return res;}
int C(int x,int y){return fac[x]*inv[x-y]%mod*inv[y]%mod;}
void dfs(int x,int fa)
{
	if(!c[x])return;
	for(int i=0;i<=n;i++)g[x][i]=0;
	vis[x]=1;g[x][0]=1;s[x]=0;
	for(auto i:e[x])
		if(i^fa)
		{
			dfs(i,x);
			for(int j=0;j<=s[i]+s[x];j++)h[j]=0;
			for(int j=0;j<=s[i];j++)
				for(int k=0;k<=s[x];k++)
					h[j+k]=(h[j+k]+g[x][k]*g[i][j]%mod*C(j+k,j)%mod)%mod;
			for(int j=0;j<=s[i]+s[x];j++)g[x][j]=h[j];s[x]+=s[i];
		}
	s[x]++;g[x][s[x]]=g[x][s[x]-1];
}
void dfs1(int x,int fa){st[++tot]=x;for(auto i:e[x])if(i^fa)dfs1(i,x);}
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read(),m=read();fac[0]=1;inv[0]=1;f[0]=1;iv[0]=1;
	for(int i=1;i<=2*n;i++)fac[i]=fac[i-1]*i%mod,inv[i]=Pow(fac[i],mod-2),iv[i]=Pow(i,mod-2);
	for(int i=1;i<=m;i++)x=read(),y=read(),in[x]++,in[y]++,e[x].push_back(y),e[y].push_back(x);
	for(int i=1;i<=n;i++)if(in[i]<=1)q.push(i);
	while(!q.empty())
	{
		int x=q.front();q.pop();c[x]=1;
		for(auto i:e[x])
			if(!c[i]){in[i]--;if(in[i]<=1)q.push(i);}
	}
	for(int i=1;i<=n;i++)
		if(!c[i])
			for(auto j:e[i])
				if(c[j])
				{
					dfs(j,i);memset(h,0,sizeof h);
					for(int k=0;k<=n;k++)
						for(int l=0;l<=n-k;l++)
							h[k+l]+=f[k]*g[j][l]%mod*C(k+l,k)%mod,h[k+l]%=mod;
					for(int k=0;k<=n;k++)f[k]=h[k]%mod;
				}
	for(int i=1;i<=n;i++)
		if(!vis[i])
		{
			if(!c[i])continue;
			dfs1(i,0);memset(p,0,sizeof p);
			for(int j=1;j<=tot;j++)
			{
				dfs(st[j],0);
				for(int k=0;k<=tot;k++)
					p[k]+=g[st[j]][k],p[k]%=mod;
			}
			for(int k=0;k<=tot;k++)p[k]=p[k]*iv[tot-k]%mod;
			tot=0;memset(h,0,sizeof h);
			for(int k=0;k<=n;k++)
				for(int l=0;l<=n-k;l++)
					h[k+l]=(h[k+l]+f[k]*p[l]%mod*C(k+l,k)%mod)%mod;
			for(int k=0;k<=n;k++)f[k]=h[k]%mod;
		}
	for(int i=0;i<=n;i++)print(f[i]),puts("");
 	return 0;
}
```


---

## 作者：tzc_wk (赞：4)

[题面传送门](https://codeforces.ml/contest/512/problem/D)

题意：

给出一张无向图，每次你可以选择一个度数 $\leq 1$ 的点并将其删除。

问对于 $k=0,1,2,\dots,n$，有多少个删除 $k$ 个点的序列，答案模 $10^9+9$。

$1\leq n\leq 100$

很容易发现，环上的点是永远不可能被删除的。于是我们对原图做一遍拓扑排序，求出哪些点可能被删除。

显然这些能被删除的点一定会形成一棵森林。

而森林中的每个连通块又可以分为两类：一种是该连通块在原图中属于的连通块中有环相连。另一种是该连通块在原图中本身就是一棵树。

对于第一种情况，一定有且仅有一个点 $x$ 与环相邻。此时 $x$ 一定是连通块中最后一个被删除的。我们就以 $x$ 为根跑一遍树上背包。具体来说，设 $dp_{i,j}$ 表示 $i$ 子树中选了 $j$ 个点的方案数。由于我们这是有根树，必须选完 $x$ 子树内所有点才能选 $x$。转移就正常求个卷积，再乘上个组合数的系数即可。由于任意两点之间最多被合并一次，复杂度 $n^2$。

对于第二种情况，我们并没有给这棵树定根。所以我们考虑以树上每个点为根都跑一次树上背包。但这样会重复计算。对于选了 $i$ 个点的方案，在以未被选择 $s-i$ 个点为根情况下都被算了一次。故答案除以 $s-i$。

然后最后再总体跑一遍背包即可。时间复杂度 $\mathcal O(n^3)$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
template<typename T> void read(T &x){
	x=0;char c=getchar();T neg=1;
	while(!isdigit(c)){if(c=='-') neg=-1;c=getchar();}
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	x*=neg;
}
const int MAXN=100;
const int MAXM=4950;
const int MOD=1e9+9;
int qpow(int x,int e){int ret=1;for(;e;x=1ll*x*x%MOD,e>>=1) if(e&1) ret=1ll*ret*x%MOD;return ret;}
int n,m,deg[MAXN+5],to[MAXM*2+5],ec=0,nxt[MAXM*2+5],hd[MAXN+5];
void adde(int u,int v){to[++ec]=v;nxt[ec]=hd[u];hd[u]=ec;}
bool vis[MAXN+5];
int from[MAXN+5],cmp=0,siz[MAXN+5],rt[MAXN+5],con[MAXN+5],c[MAXN+5][MAXN+5];
void dfs0(int x){
	if(from[x]) return;from[x]=cmp;siz[cmp]++;
//	printf("%d %d\n",x,cmp);
	for(int e=hd[x];e;e=nxt[e]) if(vis[to[e]]) dfs0(to[e]);
}
int dp[MAXN+5][MAXN+5],s[MAXN+5],tmp[MAXN+5],dpc[MAXN+5][MAXN+5];
void dfs(int x,int f){
//	printf("%d %d\n",x,f);
	s[x]=1;dp[x][0]=1;
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(y==f) continue;dfs(y,x);
		memset(tmp,0,sizeof(tmp));
		for(int i=0;i<=s[x];i++) for(int j=0;j<=s[y];j++)
			tmp[i+j]=(tmp[i+j]+1ll*dp[x][i]*dp[y][j]%MOD*c[i+j][i]%MOD)%MOD;
		s[x]+=s[y];
		for(int i=0;i<=s[x];i++) dp[x][i]=tmp[i];
	} dp[x][s[x]]=dp[x][s[x]-1];
//	for(int i=0;i<=s[x];i++) printf("%d %d %d\n",x,i,dp[x][i]);
}
int iv[MAXN+5],ans[MAXN+5]; 
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<=MAXN;i++){
		c[i][0]=1;
		for(int j=1;j<=i;j++) c[i][j]=(c[i-1][j]+c[i-1][j-1])%MOD;
	}
	iv[0]=1;for(int i=1;i<=MAXN;i++) iv[i]=qpow(i,MOD-2);
	for(int i=1;i<=m;i++){
		int u,v;scanf("%d%d",&u,&v);
		adde(u,v);adde(v,u);deg[u]++;deg[v]++;
	}
	queue<int> q;
	for(int i=1;i<=n;i++) if(deg[i]<=1) q.push(i);
	while(!q.empty()){
		int x=q.front();q.pop();vis[x]=1;//printf("%d\n",x);
		for(int e=hd[x];e;e=nxt[e]){
			int y=to[e];deg[y]--;
			if(deg[y]<=1&&!vis[y]) q.push(y);
		}
	}
	for(int i=1;i<=n;i++) if(vis[i]&&!from[i]) cmp++,dfs0(i);
	for(int i=1;i<=n;i++) for(int e=hd[i];e;e=nxt[e]) if(vis[i]&&!vis[to[e]]) con[i]=to[e],rt[from[i]]=i;
//	for(int i=1;i<=cmp;i++) printf("%d\n",rt[i]);
	for(int i=1;i<=n;i++) if(vis[i]){
		if(rt[from[i]]&&i==rt[from[i]]){
			memset(dp,0,sizeof(dp));memset(s,0,sizeof(s));
			dfs(i,con[i]);
			for(int j=0;j<=siz[from[i]];j++) dpc[from[i]][j]=dp[i][j];
		} else if(!rt[from[i]]){
			memset(dp,0,sizeof(dp));memset(s,0,sizeof(s));
			dfs(i,0);//printf("%d\n",i);
//			for(int j=1;j<=siz[from[i]];j++) printf("%d ",dp[i][j]);printf("\n");
			for(int j=0;j<=siz[from[i]];j++) dpc[from[i]][j]=(dpc[from[i]][j]+dp[i][j])%MOD;
		}
	}
	for(int i=1;i<=cmp;i++) if(!rt[i]){
		for(int j=0;j<=siz[i];j++) dpc[i][j]=1ll*dpc[i][j]*iv[siz[i]-j]%MOD;
	} ans[0]=1;
//	for(int i=1;i<=cmp;i++) for(int j=0;j<=siz[i];j++) printf("%d %d %d\n",i,j,dpc[i][j]); 
	for(int i=1;i<=cmp;i++) for(int j=n;j;j--) for(int k=1;k<=min(siz[i],j);k++)
		ans[j]=(ans[j]+1ll*ans[j-k]*dpc[i][k]%MOD*c[j][k])%MOD;
	for(int i=0;i<=n;i++) printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：zhimao (赞：3)

本题解不讲述 $O(n^3)$ 做法 ， 而讲述如何用多项式把它优化到 $O(n^2\log_2n)$

### 前言

en... 此题让我明白了常数的力量~~或许 n 太小了？？？我也不知道~~

### 正文

显然 ，合并两个节点的信息的暴力是个卷积形式 ， 
$$ans[i]=\sum_{j=\max(0,i-sz[x])}^{sz[y]}f[x][i-j]\times f[y][j]\times C_{i}^{j}$$
其中 $f[x][i]$ 代表在子树 $x$ 中有序选 $i$ 个的方案数 。
$$=\sum_{j=\max(0,i-sz[x])}^{sz[y]}f[x][i-j]\times f[y][j]\times \frac{i!}{j!\times(i-j)!}$$
$$=\sum_{j=\max(0,i-sz[x])}^{sz[y]}\frac{f[x][i-j]}{(i-j)!}\times \frac{f[y][j]}{j!}\times i!$$
$$=i!\times \sum_{j=\max(0,i-sz[x])}^{sz[y]}\frac{f[x][i-j]}{(i-j)!}\times \frac{f[y][j]}{j!}$$

于是 ， 两个被卷的数组元素除以它们下标的阶乘 ， 卷完后乘回它们的下标即可 。

然而我们一看模数 ： 1000000009  ！它不是 NTT 模数 ，又很大 ， 则必须写拆系数 FFT 或 三模 NTT 。 然后写完后比较它们的时间 ：

![](https://cdn.luogu.com.cn/upload/image_hosting/vusg1idt.png)

这就是常数的力量！！！

大常数选手当场猝死 。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1000000009;
const long double pi=acos(-1);
struct C
{
    long double r,q;
    C(){}
    C(long double a,long double b){r=a,q=b;}
    C operator + (C x){return C(r+x.r,q+x.q);}
    C operator - (C x){return C(r-x.r,q-x.q);}
    C operator * (C x){return C(r*x.r-q*x.q,r*x.q+q*x.r);}
}u[4000],v[4000],x,y,w1,w2;
int k=1,re[4005],c[4005],d[4005],g[4005],h[4005],n,m,m1,len,root,size[1000],lr[1000],f[1000][1000],a[1000],b[1000],hea[1000],nex[100000],wen[100000],bo[1000],boo[1000],booo[1000],fac[1005],inv[1005];
int kp(int a,int b)
{
	int c=1;
	while(b)
	{
		if(b&1) c=1ll*c*a%mod;
		a=1ll*a*a%mod;
		b>>=1;
	}
	return c;
}
void mo(int &x)
{
	if(x>=mod) x-=mod;
}
void add(int x,int y)
{
	++len;
	nex[len]=hea[x];
	wen[len]=y;
	hea[x]=len;
}
int invt(int x)
{
	if(!x) return 1;
	return 1ll*fac[x-1]*inv[x]%mod;
}
void DFT(C c[],int bo)
{
    for(int i=0;i<k;i++)
        if(re[i]>i) swap(c[i],c[re[i]]);
    for(int mid=1;mid<k;mid<<=1)
    {
        x={cos(pi/mid),bo*sin(pi/mid)};
        for(int r=mid<<1,j=0;j<k;j+=r)
        {
            y={1,0};
            for(int i=0;i<mid;i++)
            {
                w1=c[j+i],w2=c[j+i+mid]*y;
                c[j+i]=w1+w2;
                c[j+i+mid]=w1-w2;
                y=y*x;
            }
        }
    }
}
long long divi(long double xx,long long yy)
{
    long long z=(long long)(xx/yy);
    if(abs(z*yy-xx)<=0.000001) return z;
    if(xx>0) z=(long long)(xx/yy+0.5); else z=(long long)(xx/yy-0.5);
    return z;
}
void topo()
{
	int l=1,r=0;
	for(int i=1;i<=n;i++)
		if(booo[i]<=1)
		{
			bo[i]=1;
			lr[++r]=i;
		}
	while(l<=r)
	{
		int x=lr[l];
		for(int i=hea[x];i;i=nex[i])
			if(!bo[wen[i]])
			{
				--booo[wen[i]];
				if(booo[wen[i]]<=1)
				{
					bo[wen[i]]=1;
					lr[++r]=wen[i];
				}
			}
		++l;
	}
}
void dfs(int x,int y)
{
	boo[x]=1;
	b[++m1]=x;
	for(int i=hea[x];i;i=nex[i])
		if(wen[i]!=y)
		{
			if(!bo[wen[i]]) root=x; else dfs(wen[i],x);
		}
}
void merge(int x,int y)
{
    long long q=sqrt(mod)+1;
    for(int i=0;i<k;i++) u[i].r=u[i].q=v[i].r=v[i].q=0;
    for(long long i=0;i<=size[x];i++) f[x][i]=1ll*f[x][i]*inv[i]%mod;
    for(long long i=0;i<=size[y];i++) f[y][i]=1ll*f[y][i]*inv[i]%mod;
    for(long long i=0;i<=size[x];i++) c[i]=f[x][i]/q,d[i]=f[x][i]%q;
    for(long long i=0;i<=size[y];i++) g[i]=f[y][i]/q,h[i]=f[y][i]%q;
    for(long long i=0;i<=size[x];i++) u[i].r=c[i],u[i].q=-d[i];
    for(long long i=0;i<=size[y];i++) v[i].r=h[i],v[i].q=g[i];
    DFT(u,1);
    DFT(v,1);
    for(long long i=0;i<k;i++) u[i]=u[i]*v[i];
    DFT(u,-1);
    for(long long i=0;i<k;i++) f[x][i]=(((divi(u[i].r,k)*q)%mod-divi(u[i].q,k)%mod)%mod+mod)%mod;
    for(int i=0;i<k;i++) u[i].r=u[i].q=0;
    for(long long i=0;i<=size[x];i++) u[i].r=c[i];
    for(long long i=0;i<=size[y];i++) u[i].q=g[i];
    DFT(u,1);
    for(long long i=0;i<k;i++) u[i]=u[i]*u[i];
    DFT(u,-1);
    for(long long i=0;i<k;i++) mo(f[x][i]+=(divi(u[i].q,k*2)*q%mod*q%mod+divi(u[i].q,k*2)%mod)%mod);
	size[x]+=size[y];
    for(long long i=0;i<=size[x];i++) f[x][i]=1ll*f[x][i]*fac[i]%mod;
}
void dp(int x,int y)
{//cout<<x<<" "<<y<<endl;
	for(int i=0;i<=size[x];i++) f[x][i]=0;
	size[x]=0;
	f[x][0]=1;
	for(int i=hea[x];i;i=nex[i])
		if(wen[i]!=y&&bo[wen[i]])
		{
			dp(wen[i],x);
			merge(x,wen[i]);
		}
	f[x][size[x]+1]=f[x][size[x]];
	++size[x];
}
int main()
{
    int len=0;
    while(k<210) k<<=1,++len;
    for(int i=0;i<k;i++) re[i]=(re[i>>1]>>1)|((i&1)<<(len-1));
	scanf("%d%d",&n,&m);
	fac[0]=1;
	for(int i=1;i<=1000;i++) fac[i]=1ll*fac[i-1]*i%mod;
	inv[1000]=kp(fac[1000],mod-2);
	for(int i=1000;i;i--) inv[i-1]=1ll*inv[i]*i%mod;//cout<<inv[2]<<endl;
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
		++booo[x];
		++booo[y];
	}
	topo();
	f[0][0]=1;
	for(int i=1;i<=n;i++)
		if(bo[i]&&!boo[i])
		{
			root=m1=0;
			dfs(i,0);
			if(root)
			{
				dp(root,0);
				merge(0,root);
			}
			else
			{
				for(int i=0;i<=m1;i++) a[i]=0;
				for(int i=1;i<=m1;i++)
				{
					dp(b[i],0);
					for(int j=0;j<=m1;j++) mo(a[j]+=f[b[i]][j]);//cout<<f[b[i]][j]<<endl;cout<<endl;
				}
				for(int i=0;i<=m1;i++) f[b[1]][i]=1ll*a[i]*invt(m1-i)%mod;
				size[b[1]]=m1;
				merge(0,b[1]);
			}
		}
	for(int i=0;i<=n;i++) printf("%d\n",f[0][i]);
	return 0;
}
```


---

## 作者：姬小路秋子 (赞：2)

题意：一张n个点的无向图，现在你要遍历其中的$m$个点（$1<=m<=n$），问方案数。

一个点当前可被遍历的条件是，与它直接相连的点中最多只有一个未被遍历。

题解：
不难发现环上的点永远无法被遍历。

把能遍历的点拎出来，我们得到了一棵棵树。

考虑对每棵树进行dp。

我们可以发现一个很重要的性质：这样的一棵树中最多只有一个点与不是这棵树上的其他点（也就是无法遍历到的点）相连！！！

如果有这样的一个点，那我们就指认它为根，然后进行树形dp。

$dp[i][j]$ 表示到$i$，其子树中选了$j$个点的方案。

设$i$的子树中有x个点，那么$dp[i][x]$的转移只能为$dp[i][x]=dp[i][x-1]$

如果没有，那我们就枚举每个点作为根。
 
 然后把答案累加，最后对于每个m，总方案数/m就行了。
 
 转移方程就是组合数随便乘乘就可以了。
 
 这题的难点就在于看出这棵树的性质
 
 代码（别人的）：
 ```c
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
const ll mod=1000000009;
ll powmod(ll a,ll b) {ll res=1;a%=mod;for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
// head

const int N=110;
int n,m,u,v,vis[N],q[N],d[N],spe[N];
ll binom[N][N];
VI ver,dp[N],ret,e[N];
void dfs(int u,int f=-1) {
    ver.pb(u);
    rep(i,0,SZ(e[u])) {
        int v=e[u][i];
        if (vis[v]==1&&v!=f) dfs(v,u);
    }
}
void merge(VI &a,VI &b) {
    VI ret;
    rep(i,0,SZ(a)+SZ(b)-1) ret.pb(0);
    rep(i,0,SZ(a)) rep(j,0,SZ(b))
        ret[i+j]=(ret[i+j]+binom[i+j][j]*a[i]%mod*b[j])%mod;
    a=ret;
}
void print(VI &a) {
//	for (auto p:a) printf("%d ",p);
//	puts("");
}
void gao(int u,int f=-1) {
    dp[u].clear(); dp[u].pb(1);
    for (auto v:e[u]) {
        if (v==f||!vis[v]) continue;
        gao(v,u);
        merge(dp[u],dp[v]);
    }
    dp[u].pb(*dp[u].rbegin());
//	print(dp[u]);
}
int main() {
//	freopen("in.txt","r",stdin);
    scanf("%d%d",&n,&m);
    rep(i,0,n+1) {
        binom[i][0]=binom[i][i]=1;
        rep(j,1,i) binom[i][j]=(binom[i-1][j-1]+binom[i-1][j])%mod;
    }
    rep(i,0,m) {
        scanf("%d%d",&u,&v);--u; --v;
        e[u].pb(v); e[v].pb(u);
        d[u]++; d[v]++;
    }
    int t=0;
    rep(i,0,n) if (d[i]<=1) vis[q[t++]=i]=1;
    rep(i,0,t) {
        int u=q[i];
        rep(j,0,SZ(e[u])) {
            int v=e[u][j];
            if (vis[v]) continue;
            if ((--d[v])<=1) q[t++]=v,vis[v]=1;
        }
    }
    VI ret; ret.pb(1);
    rep(i,0,n) for (auto v:e[i]) if (!vis[v]) spe[i]=1;
    rep(i,0,n) if (vis[i]==1) {
        ver.clear();
        dfs(i);
        print(ver);
        VI pp;
        rep(j,0,SZ(ver)+1) pp.pb(0);
        int rt=-1;
        for (auto u:ver) if (spe[u]) rt=u;
        if (rt==-1) {
            for (auto u:ver) {
                gao(u);
                rep(j,0,SZ(ver)+1) pp[j]=(pp[j]+dp[u][j])%mod;
            }
            rep(j,0,SZ(ver)) pp[j]=pp[j]*powmod(SZ(ver)-j,mod-2)%mod;
        } else {
            gao(rt);
            pp=dp[rt];
        }
        print(pp);
        merge(ret,pp);
        print(ret);
        for (auto u:ver) vis[u]=0;
    }
    while (SZ(ret)<=n) ret.pb(0);
    rep(i,0,SZ(ret)) {
        printf("%d\n",ret[i]);
    }
}
```
 

---

## 作者：RQ。。。 (赞：1)

# T1 CF512D Fox And Travelling

- 给定一张 n 个点 m 条边的无向图。
- 一个点只有当**与它直接相连的点中最多只有一个点未被遍历过时**才可被遍历。
- 询问对于每个 $k \in [0,n]$，遍历 k 个点的方案数。
- $n \le 100，m \le \frac{n(n-1)}{2}$ ，答案对 $10^9+9$ 取模

**solution**

明确一点，环上的点是不可能被遍历到的。

所以，第一步就是处理出所有的能被遍历到的点。

然后，考虑去掉了环，那么剩下的这些树(剩下的一定是树)中树分两种，

一种是所有的点都能被遍历到，另一种是它的根与环上的某一点相连，那么根只能最后被遍历到，

于是设计一个dp , $dp[x][i]$ 表示 x的子树中选择i个点方案数。

$dp[x][j+k] = dp[x][j] * dp[v][k] * C(j + k , j)$

对于第二种树，显然只能以与环上相连的点为根，第一种树可以以所有的点为根进行一次dp，之后再减去算重的，

令tot为总个数，那么选i个就会被算tot - i次。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 105 , mod = 1e9+9;
inline int read()
{
	register int x = 0 , f = 0; register char c = getchar();
	while(c < '0' || c > '9') f |= c == '-' , c = getchar();
	while(c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48) , c = getchar();
	return f ? -x : x;
}
int n , m , rot;
int du[N] , ail[N] , vis[N] , now[N] , siz[N] , C[N][N] , f[N][N] , inv[N];
vector<int> G[N] , tmp;

void topsort()
{
	static queue<int> q;
	for(int i = 1 ; i <= n ; ++i) if(du[i] <= 1) q.push(i) , ail[i] = 1;
	while(q.size())
	{
		int x = q.front(); q.pop();
		for(auto v : G[x]) if(!ail[v] && (--du[v]) <= 1) ail[v] = 1 , q.push(v);
	}
}

void Getroot(int x , int fa)
{
	vis[x] = 1; tmp.push_back(x);
	for(auto v : G[x]) if(v != fa) if(!ail[v]) rot = x; else Getroot(v , x);
}

void calc(int u , int v)
{
	static int tmp[N]; memset(tmp , 0 , sizeof tmp);
	for(int i = 0 ; i <= n ; ++i)
		for(int j = 0 ; i + j <= n ; ++j)
			tmp[i+j] = (tmp[i+j] + (LL)f[u][i] * f[v][j] % mod * C[i+j][i] % mod) % mod;
	for(int i = 0 ; i <= n ; ++i) f[u][i] = tmp[i];
}

void dfs(int x , int fa)
{
	memset(f[x] , 0 , sizeof f[x]);
	f[x][0] = siz[x] = 1;
	for(auto v : G[x]) if(v != fa && ail[v]) dfs(v , x) , siz[x] += siz[v] , calc(x , v);
	f[x][siz[x]] = f[x][siz[x] - 1];
}

int main()
{
	n = read(); m = read();
	for(int i = 1 , u , v; i <= m ; ++i)
		du[u = read()]++ , du[v = read()]++ , G[u].push_back(v) , G[v].push_back(u);
	topsort(); f[0][0] = 1;
	for(int i = 0 ; i <= n ; ++i)
	{
		C[i][i] = C[i][0] = 1;
		for(int j = 1 ; j < i ; ++j) C[i][j] = ((LL)C[i-1][j] + C[i-1][j-1]) % mod;
	}
	inv[0] = inv[1] = 1;
	for(int i = 2 ; i <= n ; ++i) inv[i] = ((LL)mod - mod / i) * inv[mod % i] % mod;
	for(int i = 1 ; i <= n ; ++i) if(!vis[i] && ail[i])
	{
		rot = -1; tmp.clear(); Getroot(i , 0);
		if(~rot)
			dfs(rot , 0) , calc(0 , rot);
		else
		{
			int tot = tmp.size(); memset(now , 0 , sizeof now);
			for(auto v : tmp)
			{
				dfs(v , 0);
				for(int j = 0 ; j <= n ; ++j) now[j] = ((LL)now[j] + f[v][j]) % mod;
			}
			for(int j = 0 ; j <= tot ; ++j) now[j] = (LL)now[j] * inv[tot - j] % mod;
			memset(f[tmp[0]] , 0 , sizeof f[tmp[0]]);
			for(int j = 0 ; j <= tot ; ++j) f[tmp[0]][j] = now[j];
			calc(0 , tmp[0]);
		}
	}
	for(int i = 0 ; i <= n ; ++i) cout << f[0][i] << '\n';
	return 0;
}
```



---

## 作者：_ZSR_ (赞：0)

### [CF512D Fox And Travelling](https://www.luogu.com.cn/problem/CF512D)

显然，环上的任何点都不可能被选择，于是我们可以进行一遍拓扑排序，把环上的点全部找出来。那么剩下的点就构成了一片森林。森林里的树分为两种，一种是有根树，即有一个点连着环上的一个点的树，一种是无根树，即完全跟环没有关联的树。

优先考虑有根树，因为它的限制更强一些：根节点必须最后选择。套路地，令 $dp_{i,j}$ 表示在以节点 $i$ 为根的子树中，选择了 $j$ 个点的方案数。转移方程就是 $dp_{u,j+k}=\sum_{v \in son_u} dp_{u,j} \times dp_{v,k} \times C_{j+k}^j$。接下来考虑无根树。我们显然可以把无根树的每一个节点都当作根然后跑一遍有根树的做法，但是这样会重复计算。假设树上的节点个数为 $tot$，当前计算的是选择 $i$ 个点的方案数，那么这些方案会在以剩下的 $tot-i$ 个节点为根的时候都计算一遍，因此最后要除以 $tot-i$。

大概思路就是这样，具体实现看代码吧。

code
```
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=110,M=5e3,mod=1e9+9;
int n,m,tot;
int hd[N],to[M<<1],nxt[M<<1],idx;
int f[N],h[N],p[N];
int tr[N],deg[N],sz[N];
int g[N][N];
int fac[N],inv[N],iv[N];
queue<int> q;
bool st[N],vis[N];
inline void add(int a,int b)
{
	to[++idx]=b;
	nxt[idx]=hd[a];
	hd[a]=idx;
}
inline int ksm(int a,int b)
{
	int res=1;
	while (b)
	{
		if (b&1) res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
inline int C(int a,int b)
{
	return fac[a]*inv[a-b]%mod*inv[b]%mod;
}
inline void topsort()
{
	for (int i=1;i<=n;++i) if (deg[i]<=1) q.push(i);
	while (q.size())
	{
		int u=q.front();
		q.pop();
		st[u]=true;
		for (int i=hd[u];i;i=nxt[i])
		{
			int v=to[i];
			if (!st[v])
			{
				if (--deg[v]<=1) q.push(v);
			}
		}
	}
}
void dfs1(int u,int fa)
{
	if (!st[u]) return;
	for (int i=0;i<=n;++i) g[u][i]=0;//处理无根树的时候树的形态会改变，因此每次都要初始化
	sz[u]=0;
	vis[u]=true;
	g[u][0]=1;
	for (int i=hd[u];i;i=nxt[i])
	{
		int v=to[i];
		if (v==fa) continue;
		dfs1(v,u);
		for (int j=0;j<=sz[u]+sz[v];++j) h[j]=0;
		for (int j=0;j<=sz[u];++j)
		{
			for (int k=0;k<=sz[v];++k)
			{
				h[j+k]=(h[j+k]+g[u][j]*g[v][k]%mod*C(j+k,j)%mod)%mod;
			}
		}
		for (int j=0;j<=sz[u]+sz[v];++j) g[u][j]=h[j];
		sz[u]+=sz[v];
	}
	++sz[u],g[u][sz[u]]=g[u][sz[u]-1];//根要最后选择
}
void dfs2(int u,int fa)
{
	tr[++tot]=u;
	for (int i=hd[u];i;i=nxt[i])
	{
		int v=to[i];
		if (v==fa) continue;
		dfs2(v,u);
	}
}
signed main()
{
	scanf("%lld%lld",&n,&m);
	fac[0]=f[0]=iv[0]=1;
	for (int i=1;i<=n;++i) fac[i]=fac[i-1]*i%mod;//i!
	inv[n]=ksm(fac[n],mod-2);
	for (int i=n-1;i>=0;--i) inv[i]=inv[i+1]*(i+1)%mod;//i!的逆元
	for (int i=1;i<=n;++i) iv[i]=inv[i]*fac[i-1]%mod;//i的逆元
	for (int i=1;i<=m;++i)
	{
		int u,v;
		scanf("%lld%lld",&u,&v);
		++deg[u],++deg[v];
		add(u,v),add(v,u);
	}
	topsort();
	for (int i=1;i<=n;++i)
	{
		if (!st[i])//是环上的点
		{
			for (int j=hd[i];j;j=nxt[j])
			{
				int u=to[j];
				if (st[u])//处理有根树
				{
					dfs1(u,i);
					memset(h,0,sizeof h);
					for (int k=0;k<=n;++k)
					{
						for (int l=0;l<=n-k;++l)
						{
							h[k+l]=(h[k+l]+f[k]*g[u][l]%mod*C(k+l,k)%mod)%mod;
						}
					}
					for (int k=0;k<=n;++k) f[k]=h[k];//更新总答案
				}
			}
		}
	}
	for (int i=1;i<=n;++i)
	{
		if (st[i]&&!vis[i])//处理无根树
		{
			tot=0;
			dfs2(i,0);//处理出树上的所有节点
			memset(p,0,sizeof p);
			for (int j=1;j<=tot;++j)
			{
				dfs1(tr[j],0);
				for (int k=0;k<=tot;++k) p[k]=(p[k]+g[tr[j]][k])%mod;
			}
			for (int j=0;j<=tot;++j) p[j]=p[j]*iv[tot-j]%mod;
			memset(h,0,sizeof h);
			for (int j=0;j<=n;++j)
			{
				for (int k=0;k<=n-j;++k)
				{
					h[j+k]=(h[j+k]+f[j]*p[k]%mod*C(j+k,j)%mod)%mod;
				}
			}
			for (int j=0;j<=n;++j) f[j]=h[j];
		}
	}
	for (int i=0;i<=n;++i) printf("%lld\n",f[i]);
	return 0;
}
```


---

## 作者：chenxia25 (赞：0)

看了整个题解区，好像就我一个小丑的做法是 $\mathrm O(n^4)$（并不是什么所谓「上下界优化」能优化的，另外我寻思树上背包正常写不就是「每个点对都会在 LCA 贡献恰好一次」吗）……也来写个题解吧，毕竟是不同的做法。

首先假设图连通，因为各连通分量是独立的，二项卷积起来就是最终答案。

处于至少一个环上的点显然不会被删。容易想到求出所有边双，并缩点，得到一棵树。如果某个边双大小超过 1，那就是不能被删的，否则可以被删除，我们称不能被删的边双对应到边双缩点树上的点是坏的。

如果至少有一个坏点，那就很好做了吧。直接以某个坏点为根，由于根永远不会被删除，所以删除的顺序永远是自下往上的（删完所有儿子才能删自己）。那就树形背包就好了，用二项卷积合并，复杂度 $\mathrm O(n^2)$。

重点是没有坏点的情况，这时候选哪个点为根都不能保证它不被删或最后被删。我们可以分情况讨论：

1. 根节点没有被删，或者根节点被删时所有邻居已经无了（也就是最后一个被删）。这部分仿照至少有一个坏点，树形 DP 就行了。
2. 根节点被删时，存在一个儿子 $Y$ 没被删。这个儿子是唯一的，直接枚举是哪个儿子，不会算重。接下来有若干限制：

   1. 其他儿子子树全部要删完，且要在删根之前被删。
   2. $Y$ 的子树随便删多少个，但是 $Y$ 要在根之后被删。

   可以看到，只要维护一个三维 DP，$f_{x, s, p}$ 表示子树 $x$ 内删了 $s$ 个点，且根（也就是 $x$）是第 $p$ 个被删的（如果没被删，则 $p = s + 1$）的方案数，这样转移便可以封闭。
   转移时枚举 $Y$，以及子树 $Y$ 删的数量 $s$，$Y$ 是子树内第 $p$ 个删的，再枚举根的删除时间在子树 $Y$ 内的相对位置 $q(q \leq p)$。贡献可以 $\mathrm O(1)$ 计算：在根后删的显然只有子树 $Y$ 内的那 $s + 1 - q$ 个，剩下的在根之前删的各子树内的点可以自由组合，用可重集排列数乘在前面就行。

容易知道第二部分复杂度是 $\mathrm O(n^4)$，但由于它其实是 $\mathrm O\!\left(n^2\sum sz_x\right)$，$\sum sz_x$ 即使出成链状还带个 $\frac 12$  的常数，其他部分由于各种偏序关系又带个若干分之一的常数，所以神奇地以 31ms 的用时跑过去了。

```cpp
const int P = 1e9 + 9;

int qp(int x, int e = P - 2) { int res = 1; for(; e; e >>= 1, x = (ll)x * x % P) if(e & 1) res = (ll)res * x % P; return res; }

const int N = 110;

int n, m;
int comb[N][N], fc[N], ifc[N];
vi F[N];

bool cut[N][N];
int dfn[N], low[N], ndfn;
vi cc;
void dfs(int x, int fa = 0) {
  dfn[x] = low[x] = ++ndfn;
  cc.pb(x);
  for(int y : F[x]) if(y != fa) {
    if(dfn[y]) {
      cmn(low[x], dfn[y]);
    } else {
      dfs(y, x);
      cmn(low[x], low[y]);
      if(low[y] == dfn[y]) cut[x][y] = cut[y][x] = true;
    }
  }
}

struct Ufs {
  int fa[N];
  int root(int x) { return fa[x] ? fa[x] = root(fa[x]) : x; }
  void mrg(int x, int y) {
    x = root(x), y = root(y);
    if(x != y) fa[x] = y;
  }
} ufs;
int cid[N];
vi E[N];
bool bad[N];

void conv(int *f, int &fn, int *g, int gn) {
  static int h[N];
  for(int i = 0; i <= fn + gn; ++i) h[i] = 0;
  for(int i = 0; i <= fn; ++i) for(int j = 0; j <= gn; ++j) {
    h[i + j] = (h[i + j] + (ll)f[i] * g[j] % P * comb[i + j][i]) % P;
  }
  fn += gn;
  for(int i = 0; i <= fn; ++i) f[i] = h[i];
}

namespace allGood {
  int f[N][N][N], g[N][N], sz[N];
  void init() {
    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));
    memset(sz, 0, sizeof(sz));
  }
  void dfs(int x, int fa = 0) {
    g[x][0] = 1;
    for(int y : E[x]) if(y != fa) {
      dfs(y, x);
      conv(g[x], sz[x], g[y], sz[y]);
    }
    ++sz[x], g[x][sz[x]] = g[x][sz[x] - 1];
    for(int i = 0; i <= sz[x]; ++i) (f[x][i][i + (i < sz[x])] += g[x][i]) %= P;
    if(sz(E[x]) - !!fa == 0) return;
    for(int Y : E[x]) if(Y != fa) {
      int val = 1;
      for(int y : E[x]) if(y != fa && y != Y) {
        val = (ll)val * f[y][sz[y]][sz[y]] % P * ifc[sz[y]] % P;
      }
      for(int s = 0; s <= sz[Y]; ++s) for(int p = 1; p <= min(sz[Y], s + 1); ++p) {
        for(int q = 1; q <= p; ++q) {
          int howMany = sz[x] - (sz[Y] - s), &obj = f[x][howMany][howMany - (s + 1 - q)];
          int ad = (ll)val * f[Y][s][p] % P * fc[howMany - (s + 2 - q)] % P * ifc[q - 1] % P;
          obj = (obj + ad) % P;
        }
      }
    }
  }
}

namespace existBad {
  int f[N][N], sz[N];
  void init() {
    memset(f, 0, sizeof(f));
    memset(sz, 0, sizeof(sz));
  }
  void dfs(int x, int fa = 0) {
    f[x][0] = 1;
    for(int y : E[x]) if(y != fa) {
      dfs(y, x);
      conv(f[x], sz[x], f[y], sz[y]);
    }
    ++sz[x];
    if(!bad[x]) f[x][sz[x]] = f[x][sz[x] - 1];
  }
}

void mian() {
  cin >> n >> m;
  comb[0][0] = 1; for(int i = 1; i <= n; ++i) for(int j = 0; j <= i; ++j) comb[i][j] = (comb[i - 1][j] + (j ? comb[i - 1][j - 1] : 0)) % P;
  fc[0] = ifc[0] = 1; for(int i = 1; i <= n; ++i) fc[i] = (ll)fc[i - 1] * i % P, ifc[i] = qp(fc[i]);
  while(m--) {
    int x, y; cin >> x >> y;
    F[x].pb(y), F[y].pb(x);
  }
  static int ans[N]; ans[0] = 1;
  int alr = 0;
  for(int i = 1; i <= n; ++i) if(!dfn[i]) {
    cc.clear();
    dfs(i);
    for(int x : cc) for(int y : F[x]) if(!cut[x][y]) ufs.mrg(x, y);
    m = 0;
    for(int x : cc) if(!ufs.fa[x]) cid[x] = ++m;
    memset(bad, 0, sizeof(bad));
    for(int x : cc) if(ufs.fa[x]) bad[cid[x] = cid[ufs.root(x)]] = true;
    for(int j = 1; j <= n; ++j) E[j].clear();
    int edgesAdded = 0;
    for(int x : cc) for(int y : F[x]) if(cid[x] != cid[y]) ++edgesAdded, E[cid[x]].pb(cid[y]);
    assert(edgesAdded == 2 * (m - 1));
    if(count(bad + 1, bad + n + 1, true)) {
      existBad::init();
      int rt = 0;
      for(int j = 1; j <= m; ++j) if(bad[j]) rt = j;
      existBad::dfs(rt);
      conv(ans, alr, existBad::f[rt], m);
    } else {
      assert(sz(cc) == m);
      allGood::init();
      int rt = 1;
      allGood::dfs(rt);
      static int res[N]; memset(res, 0, sizeof(res));
      for(int j = 0; j <= m; ++j) for(int p = 1; p <= j + 1; ++p) res[j] = (res[j] + allGood::f[rt][j][p]) % P;
      conv(ans, alr, res, m);
    }
  }
  for(int i = 0; i <= n; ++i) cout << ans[i] << nl;
}
```

---

## 作者：HC20050615 (赞：0)

# 思路
我们可以这样理解这道题：
所有仅连有 $0$ 或 $1$ 条边 的点可以被删去，求删去 $k$ 个点的方案数。

很容易发现，这种问题很像拓扑的操作。我们可以先不考虑 $k$ 的限制，来想一想究竟有那些点可以被删去。做一次拓扑排序，拓扑排序删不掉的点一定不会被选。

注意，不可以仅通过找环来判断点可不可以被选，因为非环上的点也不一定能够选。想象一下，有一个点连接了两个环，那这个点一定选不了。（当然，找环并不是不能做这道题，但会很复杂。）

不过，我们这种拓扑排序的做法一定是正确的。

感性证明一下：（~~不会有人证不来吧~~）

如果当拓扑的队列之中的所有点都被弹出，此时还有点未被入栈，由于图的状态不在改变，这些点一定不能在以后被入栈。由于点的删除只会使其他点的连边数减小或不变，且顺序与删去点后状态无关。所以，当拓扑停止时，我们一定已将所有的点全部删去。

在我们删除了这些点之后，由于环上的点一定不能选，肯定已经删去。所以，剩下的图变为了一个森林。森林中的一部分树与环相连，而一部分树没有，我们称其为有根树和无根树。有根树的根为其与环相连的点。可以证明，每棵树一定至多有一个点与一个环相连，或者说一棵树上的所有点的边中，仅有一条边与一个环上的点相连。

证明：

若一棵树上有两个点与环相连，则这两点之间一定存在一条树上的路径。我们会发现，由于两端点无法删去，此路径上所有的点都无法删去，与条件不符。

于是对于这些树进行动态规划就行了，然后再整个做一个大背包。

时间复杂度为 $O(n^4)$ ，瓶颈在每棵树的动归上。理论上是能过的，但我就是过不了（常数太大）。

所以，我们需要使用上下界优化，其实就是把动归循环里的上下界减小，并非什么很复杂的东西，但是优化效果十分明显。

然后我们的时间复杂度优化到了 $O(n^3)$ ，完全可以通过本题。（大佬们说是 $n^3$ ，不知道怎么去证）。
# Code
~~绝对没有防抄袭~~

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int v[20001];
int nxt[20001];
int d[101];
int tot;
int mod=1e9+9;
int rd[101];
inline void add(int x,int y)
{
	v[++tot]=y;
	nxt[tot]=d[x];
	d[x]=tot;
	return ;
}
queue<int>q;
bool b[101];
int root[101];
int group[101];
inline void color(int now,int c)
{
	if(group[now])
	{
		return ;
	}
	group[now]=c;
	for(register int i=d[now];i;i=nxt[i])
	{
		if(b[v[i]])
		{
			color(v[i],c);
		}
	}
	return ;
}
inline int inv(int a)
{
	int k=mod-2;
	int ans=1;
	while(k)
	{
		if(k&1)
		{
			ans=(long long)ans*a%mod;
		}
		a=(long long)a*a%mod;
		k/=2;
	}
	return ans;
}
int f[101][101];
int g[101][101];
int ans[101];
int siz[101];
int p[201];
inline int C(int x,int y)
{
	return (long long)p[x]*inv(p[y])%mod*inv(p[x-y])%mod;
}
inline void dfs(int now,int last)
{
	siz[now]=1;
	f[now][0]=1;
	for(register int i=d[now];i;i=nxt[i])
	{
		if(v[i]!=last&&b[v[i]])
		{
			dfs(v[i],now);
			for(register int j=siz[now]-1;j>=0;j--)
			{
				for(register int k=1;k<=siz[v[i]];k++)
				{
					f[now][j+k]+=(long long)f[now][j]*f[v[i]][k]%mod*C(j+k,j)%mod;
					f[now][j+k]%=mod;
				}
			}
			siz[now]+=siz[v[i]];
		}
	}
	f[now][siz[now]]=f[now][siz[now]-1];
	return ;
}
int main()
{
	p[0]=1;
	for(int i=1;i<=200;i++)
	{
		p[i]=(long long)p[i-1]*i%mod;
	}
	cin>>n>>m;
	for(register int i=1;i<=m;i++)
	{
		int x,y;
		cin>>x>>y;
		add(x,y);
		add(y,x);
		rd[x]++;
		rd[y]++;
	}
	for(register int i=1;i<=n;i++)
	{
		if(rd[i]==1||rd[i]==0)
		{
			q.push(i);
		}
	}
	while(!q.empty())
	{
		int t=q.front();
		b[t]=1;
		q.pop();
		for(register int i=d[t];i;i=nxt[i])
		{
			rd[v[i]]--;
			if(rd[v[i]]==1)
			{
				q.push(v[i]);
			}
		}
	}
	tot=0;
	for(register int i=1;i<=n;i++)
	{
		if((!group[i])&&b[i])
		{
			color(i,++tot);
		}	
		for(register int j=d[i];j;j=nxt[j])
		{
			if(!b[v[j]])
			{
				root[group[i]]=i;
				break;
			}
		}
	}
	ans[0]=1;
	for(register int i=1;i<=tot;i++)
	{
		int sizz=0;
		if(root[i])
		{
			dfs(root[i],-1);
			for(register int j=0;j<=siz[root[i]];j++)
			{
				g[i][j]=f[root[i]][j];
			}
			sizz=siz[root[i]];
		}
		else
		{
			for(register int j=1;j<=n;j++)
			{
				if(group[j]==i)
				{
					sizz++;
					dfs(j,-1);
					for(register int k=0;k<=n;k++)
					{
						g[i][k]+=f[j][k];
						g[i][k]%=mod;
					}
					memset(f,0,sizeof(f));
					memset(siz,0,sizeof(siz));
				}
			}
			for(register int j=0;j<sizz;j++)
			{
				g[i][j]=(long long)g[i][j]*inv(sizz-j)%mod;
			}
		}
		for(register int j=n;j>=0;j--)
		{
			for(register int k=1;k<=sizz;k++)
			{
				ans[j+k]+=(long long)ans[j]*g[i][k]%mod*C(j+k,j)%mod;
				ans[j+k]%=mod;
			}
		}
	}
	for(register int i=0;i<=n;i++)
	{
		cout<<ans[i]<<endl;
	}
	return 0;
}
```


---

## 作者：tommymio (赞：0)

树形背包题。

考虑到环上的点并不会产生任何影响。因此我们可以将图稍加转化，转化成若干棵有根树和无根树。有根树的根为与环直接相连的点，无根树则是不与任何环相连的一个连通块。转化的过程可以使用拓扑排序完成。

对于有根树，直接统计即可。对于无根树，我们对其每个点作为根的方案数统计一次，发现若选取 $i$ 个点，无根树大小为 $S$，会重复统计同一种方案 $S-i$ 次，其中 $i<S$。证明的话，我们可以分类讨论选择序列与根的关系：若序列中含有根，则一定选取了 $S$ 个点，因为我们钦定根是最后被选取的点，不符合题设。若序列中不含有根，则会被统计 $S-i$ 次。于是证毕。

计算出每棵树的答案以后，用同样的方式计算出森林的答案即可。

状态：$f[x,i]$ 为子树 $x$ 内有序取了 $i$ 个点的方案数。

转移：
$$
f[x,i]=\sum_{j>0} f[x,i-j]\times f[y,j]\times\binom{i}{j}
$$

一定要记得清空 $f$ 啊awa

```cpp
/* stuff you should look for
	* int overflow, array bounds, uppercase/lowercase
	* special cases (n=1?)
	* do sth. instead of nothing and stay organized
	* WRITE STUFF DOWN
	* DON'T GET STUCK ON ONE APPROACH
*/
#include<cstdio>
#include<queue>
typedef long long ll;
const int mod=1e9+9;
int n,cnt=0;
int ans[105];
int pw[105],inv[105],sz[105];
int vis[105],deg[105],bel[105];
int h[105],to[10005],ver[10005];
int f[105][105],C[105][105];
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline void add(int x,int y) {to[++cnt]=y;ver[cnt]=h[x];h[x]=cnt;}
inline ll pow(ll x,ll p) {ll res=1; for(;p;p>>=1) {if(p&1) res=res*x%mod; x=x*x%mod;} return res;}
inline void topo() {
	std::queue<int> Q; 
	for(register int x=1;x<=n;++x) {if(deg[x]<=1) Q.push(x),vis[x]=1;}
	while(Q.size()) {
		int x=Q.front(); Q.pop();
		for(register int i=h[x];i;i=ver[i]) {
			int y=to[i]; 
			if((--deg[y])<=1&&!vis[y]) Q.push(y),vis[y]=1;
		}
	}
}
inline void dfs(int x,int clr,int &sz) {
	++sz; bel[x]=clr; //printf("%d %d\n",x,clr);
	for(register int i=h[x];i;i=ver[i]) {int y=to[i]; if(!bel[y]&&!deg[y]) dfs(y,clr,sz);}
}
inline void buildTree() {
	for(register int x=1;x<=n;++x) if(deg[x]==1) dfs(x,x,sz[x]);
	for(register int x=1;x<=n;++x) if(!bel[x]&&!deg[x]) dfs(x,x,sz[x]);//printf("x=%d\n",x);
}
inline void dp(int x,int fa) {
	f[x][0]=1; sz[x]=1; f[x][1]=0;
	for(register int i=h[x];i;i=ver[i]) {
		int y=to[i]; if(y==fa||bel[x]!=bel[y]) continue;
		dp(y,x); 
		for(register int j=1;j<=sz[y];++j) f[x][sz[x]+j]=0;
		for(register int j=sz[x];j>=0;--j) {
			for(register int k=1;k<=sz[y];++k) {
//				if(k>j) break;
//				(f[x][j]+=f[x][j-k]*1ll*f[y][k]%mod*C[j][k]%mod)%=mod;
				(f[x][j+k]+=f[x][j]*1ll*f[y][k]%mod*C[j+k][k]%mod)%=mod;
			}
		}
		sz[x]+=sz[y];
	}
	f[x][sz[x]]=f[x][sz[x]-1];
//	printf("x=%d ",x);
//	for(register int j=1;j<=sz[x];++j) printf("%d ",f[x][j]); printf("\n");
}
inline void work(int x) {
	dp(x,-1);
	for(register int i=0;i<=sz[x];++i) (f[0][i]+=f[x][i])%=mod;
}
int main() {
	n=read(); int m=read();
	for(register int i=0;i<=n;++i) {
		C[i][0]=1;
		for(register int j=1;j<=i;++j) C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	}
	for(register int i=1;i<=m;++i) {
		int x=read(),y=read();
		add(x,y); add(y,x);
		++deg[x]; ++deg[y]; 
	} 
	topo();
	buildTree();
	int tot=0; ans[0]=1;
	for(register int x=1;x<=n;++x) {
		if(bel[x]==x) {
			int S=sz[x]; tot+=S;
			if(deg[x]==1) {work(x);}
			else {
				for(register int i=1;i<=n;++i) if(bel[i]==x) work(i);
				for(register int i=0;i<S;++i) f[0][i]=f[0][i]*1ll*pow(S-i,mod-2)%mod;
			}
			for(register int i=tot;i>=1;--i) {
				for(register int j=1;j<=S;++j) {
					if(i<j) break;
					(ans[i]+=ans[i-j]*1ll*f[0][j]%mod*C[i][j]%mod)%=mod;
				}
			}
			for(register int i=0;i<=S;++i) f[0][i]=0;
		}
	}
	for(register int i=0;i<=n;++i) printf("%d\n",ans[i]);
	return 0;
}
```
 

---

## 作者：Piwry (赞：0)

做的时候想了很久的 $O(n^2)$ 算法，然而最后还是没想出，只得发一个 $O(n^3)$ 的题解了qaq（之后大概会补 $O(n^2)$）

另外一种实际上做不到 $O(n^2)$ 的思路值得一提：结合 $O(n^3)$ 解法的结论（可见下文），考虑用换根 dp 得出以每个点为根的背包 dp 值

然而虽然每次父亲删除贡献的均摊复杂度是 $O(n)$ 的，每次合并父亲处贡献的均摊复杂度却可能是 $O(n^2)$。例如对于一条链，设链的一边（度数为 $1$）为初始根，在第二次 dfs 时合并父亲贡献的操作次数约为 $\sum\limits_{i=1}^n(i(n-i))=\frac {n(n+1)} 2-\frac {n(n+1)(2n+1)} 6=n(n+1)\cdot\frac {n-1} 6$，是 $O(n^3)$ 的

可以形象地理解为，第二次 dfs 的每次操作有可能将以每个结点为根，做第一次 dfs 的**最坏**单次操作的复杂度拿过来了

## 解析

可以发现，对于在某个**环**上的结点，它是永远不可能被遍历的；或者说，可以遍历的结点集合构成的子图总是一个森林

我们预先将这些结点找出来（可以用 tarjan 或者用类似拓扑排序的方式），森林里的树就有两种：在原图是无根树的树，在原图连着某个环的树

可以知道这颗树最多有一个结点连着原图的环（否则这棵树上就存在环了），而这个结点必须要等它在树上所有有边相接的结点都被遍历后才能遍历；类似的，这些相连的结点也要求 “更外围” 的结点被遍历后才能被遍历。

这就形成了父子关系，可以考虑做树 dp，我们设与环相接的结点为整颗树的根，所有父亲结点都必须等儿子都遍历完才能选

设 $dp(u, k)$ 表示以 $u$ 为根的子树选了 $k$ 个结点的方案数。对于每颗子树中都确定的一种次序，不同子树间的结点次序是可以随意交换的，由此可得加入新子树的转移方程：

$dp(u, i+j)'=\binom {i+j} i\cdot dp(u, i)\cdot dp(v, j)$

$v$ 是 $u$ 的儿子

其中 $dp(u, size_u)$ 比较特殊，它等于 $dp(u, size_u-1)$（我们可以在 dfs 返回时计算它），因为要选 $u$ 必须等子树都遍历完，顺序是确定的

由此我们也得出 dp 的初值：`dp[u][0] =1`，其余均缺省为 $0$

&nbsp;

接下来再考虑无根树。如果我们随意选一个根，再按上面的方法做，会发现少算了一部分贡献：因为总是要求子树选完后才能选，而在无根树上是可能存在从某个结点父亲处遍历而来的情况的

可以想到以每个结点为根做一次 dp，然后再去除多算的贡献。

考虑一种可能的遍历会被重复算多少次。如果设置的根不属于该遍历序列，这种方案在每次 dp 都会被计算一次；如果属于该遍历序列，除非该遍历选了整颗无根树，否则这种方案是不可能被计数的，因为设置的根要求所有儿子都被选才能遍历到，遍历设置的根一定要选整颗树。而对于选了整颗无根树的遍历，设置某结点为根相当于钦定某个结点最后选；以每个结点为根 dp 得到的方案和恰好是不重不漏地计数的

于是我们只需将每次 dp 得到的在根的答案都加起来；对于遍历了 $k$ 个结点，$k<s$ 的方案，我们最后除 $s-k$ 即可，其中 $s$ 为该无根树的大小

## CODE

注意如果不用上下界优化是 $O(n^4)$ 的，用了是 $O(n^3)$ 的。不过都能过qwq

```cpp
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
#define ll long long
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast","-funroll-loops","-fdelete-null-pointer-checks")
#pragma GCC target("ssse3","sse3","sse2","sse","avx2","avx")
using std::queue;
using std::vector;

const int MAXN =110;
const int M =1e9+9;

/*------------------------------C------------------------------*/

int C[MAXN][MAXN];

inline void preC(int n){
	for(int i =0; i <= n; ++i){
		C[i][0] =1;
		for(int j =1; j <= i; ++j)
			C[i][j] =((ll)C[i-1][j-1]+C[i-1][j])%M;
	}
}

/*------------------------------Inv------------------------------*/

int inv[MAXN];

inline void preInv(int n){
	inv[1] =1;
	for(int i =2; i <= n; ++i)
		inv[i] =1ll*(-M/i+M)*inv[M%i]%M;
}

/*------------------------------Map------------------------------*/

vector<int> E[MAXN];

inline void addedge(int u, int v){
	E[u].push_back(v), E[v].push_back(u);
}

/*------------------------------Dfs------------------------------*/

int dp[MAXN][MAXN]/*子树选了 k 个点的方案数*/, tmp[MAXN];
int siz[MAXN];

void dfs(int u, int fa){
	siz[u] =1;
	dp[u][0] =1;
	for(int v:E[u])
		if(v != fa){
			dfs(v, u);
			for(int i =0; i <= siz[u]; ++i)
				tmp[i] =dp[u][i], dp[u][i] =0;
			for(int i =0; i <= siz[u]/*min(n, siz[u])*/; ++i)
				for(int j =0; j <= siz[v]/*min(n, min(siz[v], ...))*/; ++j)
					dp[u][i+j] =(dp[u][i+j]+1ll*C[i+j][i]*tmp[i]%M*dp[v][j]%M)%M;
			siz[u] +=siz[v];
		}
	dp[u][siz[u]] =dp[u][siz[u]-1];
}

/*------------------------------Dfs2------------------------------*/

int dp2[MAXN][MAXN], tmp2[MAXN];
int siz2[MAXN];

void dfs2(int u, int fa){
	siz2[u] =1;
	dp2[u][0] =1;
	for(int v:E[u])
		if(v != fa){
			dfs2(v, u);
			for(int i =0; i <= siz2[u]; ++i)
				tmp2[i] =dp2[u][i], dp2[u][i] =0;
			for(int i =0; i <= siz2[u]; ++i)
				for(int j =0; j <= siz2[v]; ++j)
					dp2[u][i+j] =(dp2[u][i+j]+1ll*C[i+j][i]*tmp2[i]%M*dp2[v][j]%M)%M;
			siz2[u] +=siz2[v];
		}
	dp2[u][siz2[u]] =dp2[u][siz2[u]-1];
}

int siz_t[MAXN];

/*计算出这颗无根树的答案并放至 dp[pos][.] 中，计算树大小*/
void dfs_calc(int u, int fa, int pos, const int &n){
	siz_t[u] =1;
	for(int v:E[u])
		if(v != fa){
			dfs_calc(v, u, pos, n);
			siz_t[u] +=siz_t[v];
		}
	
	memset(dp2, 0, sizeof(dp2));
	dfs2(u, 0);
	for(int k =0; k <= n/*或该无根树大小*/; ++k)
		dp[pos][k] =((ll)dp[pos][k]+dp2[u][k])%M;
}

/*------------------------------Pre------------------------------*/

vector<int> Epre[MAXN];
bool color[MAXN];
int d[MAXN];
queue<int> V;
vector<int> Root, T;

inline void addedgePre(int u, int v){
	Epre[u].push_back(v), Epre[v].push_back(u);
}

/*为新图连边*/
void dfs_link(int u, int fa){
	color[u] =0;
	for(int v:Epre[u])
		if(v != fa){
			if(color[v]){
				addedge(u, v);
				dfs_link(v, u);
			}
			else/*u 接了一个环，要作为根*/
				Root.push_back(u);
		}
}

/*------------------------------Main------------------------------*/

inline int read(){
	int x =0; char c =getchar();
	while(c < '0' || c > '9') c =getchar();
	while(c >= '0' && c <= '9') x = (x<<3) + (x<<1) + (48^c), c =getchar();
	return x;
}

int ans[MAXN];

int main(){
	int n =read(), m =read();
	for(int i =0; i < m; ++i){
		int u =read(), v =read();
		addedgePre(u, v);
		++d[u], ++d[v];
	}
	
	for(int i =1; i <= n; ++i)
		if(d[i] == 1 || d[i] == 0 /*<-*/)
			V.push(i);
	while(!V.empty()){/*类似拓排的方式建新图*/
		int u =V.front();
		V.pop();
		if(color[u])
			continue;
		color[u] =1;
		bool flg =0;
		for(int v:Epre[u])
			if(!color[v]){
				--d[v];
				if(d[v] == 1 || d[v] == 0)
					V.push(v);
				flg =1;
			}
		if(flg == 0)/*一个点所在连通块都被删完了，这个连通块一定是树*/
			T.push_back(u);
	}
	for(int i =1; i <= n; ++i)
		if(color[i])
			dfs_link(i, 0);
	preInv(n);
	preC(n);
	
	for(int rt:Root)
		dfs(rt, 0);
	for(int u:T){
		dfs_calc(u, 0, u, n);
		for(int k =0; k < siz_t[u]; ++k)
			dp[u][k] =1ll*dp[u][k]*inv[siz_t[u]-k]%M;
	}
	ans[0] =1;
	for(int t:Root){
		for(int i =0; i <= n; ++i)
			tmp[i] =ans[i], ans[i] =0;
		for(int i =0; i <= n; ++i)
			for(int j =0; j <= n && i+j <= n; ++j)
				ans[i+j] =(ans[i+j]+1ll*C[i+j][i]*tmp[i]%M*dp[t][j]%M)%M;
	}
	for(int t:T){
		for(int i =0; i <= n; ++i)
			tmp[i] =ans[i], ans[i] =0;
		for(int i =0; i <= n; ++i)
			for(int j =0; j <= n && i+j <= n; ++j)
				ans[i+j] =(ans[i+j]+1ll*C[i+j][i]*tmp[i]%M*dp[t][j]%M)%M;
	}
	
	for(int i =0; i <= n; ++i)
		printf("%d\n", ans[i]);
}
```

---

## 作者：Purple_wzy (赞：0)

题面：https://www.luogu.com.cn/problem/CF512D

题意：给定一张$n$个点$m$条边的无向图。

一个点只有当与它直接相连的点中最多只有一个点未被遍历过时才可被遍历。

询问对于每个$k$$\in$[0,n],遍历$k$个点的方案数。

$n$ $\le$ 100,$m$ $\le$ $\frac{n(n-1)}2$ ,答案对1e9+9取模。

题解：

先考虑哪些点可以被遍历到。显然，环上的点不可能被遍历到。

这样，我们把环去掉，就得到了一个森林。

但是这样之后，仍有点无法被遍历到。比如被夹在两个环之间的点。

用边双缩点判断显得太过繁琐，

我们可以用类似拓扑排序的方法求出可以被遍历到的点。

之后，考虑每个连通块（树）：

1.如果这棵树有节点与环相连，那么它一定是这棵树里最后被遍历到的点。

（可以思考一下为什么这样的点最多只有一个）

那么我们可以认为这个节点是树根，进行树上背包DP。

设$f[i][j]$表示在i的子树内有序地选了$j$个点的方案数。

转移时，枚举每个子树，然后把它们的$f$卷起来就好。

最后算$i$本身的贡献时，因为$i$是最后加进去的点（$i$的祖先一定在$i$后面被遍历到），

直接$f[i][siz[i]]=f[i][siz[i]-1]$即可。

2.如果没有节点与环相连，我们可以分别钦定树中的每个节点为根，然后做法和上述一样。

将所有情况的答案加起来，对于每个$j$,还需要除以一个$siz-j$,

因为当有siz-j个点未被遍历时，被遍历到的j个点的方案会在所有以这$siz-j$个点为根做DP时被计算过。

最后把每棵树的贡献卷起来就大功告成了。

时间复杂度:O($n^3$)

代码：
```
#include<bits/stdc++.h>
using namespace std;
#define re register int
#define F(x,y,z) for(re x=y;x<=z;x++)
#define FOR(x,y,z) for(re x=y;x>=z;x--)
typedef long long ll;
#define I inline void
#define IN inline int
#define C(x,y) memset(x,y,sizeof(x))
#define STS system("pause")
template<class D>I read(D &res){
	res=0;register D g=1;register char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')g=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		res=(res<<3)+(res<<1)+(ch^48);
		ch=getchar();
	}
	res*=g;
}
struct E{
	int to,nt;
}e[40400];
#define T e[k].to
const int Mod=1e9+9;
int n,m,head[220],tot,X,Y,du[220],vis[220],v[220],root,C[220][220],ans[220],f[220][220],inv[220],now[220],son[220],siz[220];
I add(int x,int y){e[++tot].to=y;e[tot].nt=head[x];head[x]=tot;}
queue<int>q;
vector<int>vec;
IN Pow(int x,int y){
	re res=1;
	while(y){
		if(y&1)res=(ll)res*x%Mod;
		x=(ll)x*x%Mod;
		y>>=1;
	}
	return res;
}
I findroot(int x,int fa){
	v[x]=1;
	vec.emplace_back(x);
	for(re k=head[x];k!=-1;k=e[k].nt){
		if(T==fa)continue;
		if(!vis[T]){root=x;continue;}
		findroot(T,x);
	}
}
I Plus(int &x,int y){x+=y;if(x>=Mod)x-=Mod;}
I mul(int x,int y){
	re t[220];
	C(t,0);
	F(i,0,n){
		F(j,0,n){
			Plus(t[i+j],(ll)((ll)f[x][i]*f[y][j]%Mod)*C[i+j][i]%Mod);
		}
	}
	F(i,0,n)f[x][i]=t[i];
}
I D_1(int x,int fa){
	C(f[x],0);siz[x]=1;f[x][0]=1;
	for(re k=head[x];k!=-1;k=e[k].nt){
		if(T==fa||!vis[T])continue;
		D_1(T,x);siz[x]+=siz[T];
		mul(x,T);
	}
	f[x][siz[x]]=f[x][siz[x]-1];
	//cout<<x<<":";
	//F(i,0,m)cout<<f[x][i]<<" ";
	//cout<<endl;
}
int main(){
	read(n);read(m);inv[0]=1;f[0][0]=1;C[0][0]=1;
	F(i,1,n)inv[i]=Pow(i,Mod-2),C[i][0]=1;
	F(i,1,n){
		F(j,1,i)C[i][j]=(C[i-1][j]+C[i-1][j-1])%Mod;
	}
	C(head,-1);tot=-1;
	F(i,1,m){
		read(X);read(Y);
		add(X,Y);add(Y,X);
		du[X]++;du[Y]++;son[X]++;son[Y]++;
	}
	F(i,1,n)if(du[i]<=1)q.push(i),vis[i]=1;
	while(!q.empty()){
		m=q.front();q.pop();
		for(re k=head[m];k!=-1;k=e[k].nt){
			if(vis[T])continue;du[T]--;
			if(du[T]<=1)q.push(T),vis[T]=1;
		}
	}
	//F(i,1,n)cout<<vis[i]<<" ";
	//cout<<endl;
	F(i,1,n){
		if(!vis[i]||v[i])continue;
		vec.clear();
		root=-1;findroot(i,0);
		//cout<<"!";
		//for(auto p:vec)cout<<p<<" ";
		//cout<<endl;	
		if(root!=-1){
			D_1(root,0);
			//F(i,0,m)cout<<f[root][i]<<" ";
			//cout<<endl;
			mul(0,root);
			//F(i,0,n)Plus(ans[i],f[root][i]);
		}
		else{
			m=vec.size();C(now,0);
			for(auto p:vec){
				D_1(p,0);//F(i,0,m)cout<<f[p][i]<<" ";
				//cout<<endl;
				F(i,0,n)Plus(now[i],f[p][i]);
			}
			C(f[vec[0]],0);
			F(i,0,m)f[vec[0]][i]=(ll)now[i]*inv[m-i]%Mod;
			//F(i,0,m)cout<<f[vec[0]][i]<<" ";cout<<endl;
			mul(0,vec[0]);
			//F(i,0,n)Plus(ans[i],(ll)now[i]*inv[m-i]%Mod);
		}
	}
	F(i,0,n)cout<<f[0][i]<<endl;
	return 0;
}
```
推荐一下我的博客：https://www.cnblogs.com/Purple-wzy/

---

