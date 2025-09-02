# [集训队互测 2023] Tree Topological Order Counting

## 题目描述

给定一颗 $n$ 个点的有根树，$1$ 是根，记 $u$ 的父亲是 $fa_u$。另给出一长度为 $n$ 的权值序列 $b$。

称一个长度为 $n$ 的排列 $a$ 为这颗树的合法拓扑序，当且仅当 $\forall 2 \le u \le n,a_u > a_{fa_u}$。

对每个点 $u$，定义 $f(u)$ 为，在所有这颗树的合法拓扑序中，$b_{a_u}$ 之和。

现在对 $1 \le u \le n$，求 $f(u) \bmod 10^9+7$。

## 说明/提示

| Subtask | $n \le$ | 特殊限制 | 分值 |
| :-----: | :-----: | :------: | :--: |
|   $1$   |  $10$   |    无    | $5$  |
|   $2$   |  $20$   |    无    | $10$ |
|   $3$   |  $100$  |    无    | $15$ |
|   $4$   |  $350$  |    无    | $15$ |
|   $5$   | $3000$  |    A     | $15$ |
|   $6$   | $3000$  |    无    | $20$ |
|   $7$   | $5000$  |    无    | $20$ |

特殊限制 A：$\forall 1 \le i \le n,b_i=i$。

对于所有数据：$2 \le n \le 5000$，$1 \le fa_i < i$，$0 \le b_i < 10^9+7$。

## 样例 #1

### 输入

```
5
1 1 3 2
3 5 4 4 1
```

### 输出

```
18 27 27 15 15 
```

## 样例 #2

### 输入

```
5
1 1 3 1
1 2 3 4 5
```

### 输出

```
12 42 32 52 42
```

# 题解

## 作者：tobie (赞：15)

[题目传送门](https://www.luogu.com.cn/problem/P10013)

关于这题的第一想法肯定是对于每个 $x$ 计算贡献。

对于一个点 $x$，在拓扑序中的位置应当在它的所有祖先之后，这引导我们将 $x$ 到 $1$ 的链单独提取出来进行dp。

令 $dp_{u,i}$ 表示当前考虑到 $u$，$x$ 前面有 $i$ 个数的方案数。那么有

$$dp_{fa_u,j+k}\leftarrow dp_{u,j}\times\binom{j+k-1}{j}\times\binom{siz_{fa_u}-j-k-1}{siz_v-j-1}\times C$$

其中 $C$ 表示 $fa_u$ 除去 $u$ 子树外的拓扑序数量。

转移一次的时间复杂度为 $siz_u\times(siz_{fa_u}-siz_u)$，对每个 $x$ 求出答案的时间复杂度为 $O(n^2)$，总时间复杂度为 $O(n^3)$，考虑优化。

可以发现，对于每个 $x$ 做dp时，是从 $x$ 开始dp，在根节点计算贡献，**同时每个 $x$ 的dp的转移具有很强的相似性**。

如果说我们能够按照传统树形dp的方法，从根节点开始dp，在每个节点计算贡献，那么时间复杂度就可以缩减到 $O(n^2)$，可以认为是对所有 $x$ 同时dp以减小复杂度。

那我们能把dp反过来做吗？其实是可以的。我们可以将dp状态的转移看做有向图，转移系数看做边，那么原先的dp相当于计算从 $dp_{x,\star}$ 出发，到达 $dp_{1,\star}$ 的所有路径的边权之积的和。那当我们将这个有向图反过来，那就等价于交换了起点和终点，得到：

$$dp_{u,j+k}\times\binom{j+k-1}{j}\times\binom{siz_{fa_u}-j-k-1}{siz_v-j-1}\times C\rightarrow dp_{v,j}$$

总时间复杂度为 $O(n^2)$

```cpp#include<iostream>
#include<cstdio>
using namespace std;
#define int long long
const int N=5009,mod=1000000007;
int n;
struct Edge{
	int nxt,to;
	Edge(){} Edge(int x,int y){nxt=x,to=y;}
}edge[N*2];
int head[N],edge_cnt=0;
void Add_edge(int u,int v){edge[++edge_cnt]=Edge(head[u],v);head[u]=edge_cnt;}
int c[N][N],jc[N];
void ycl(int n)
{
	for(int i=0;i<=n;i++)
	{
		c[i][0]=1;
		for(int j=1;j<=i;j++) c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
	}
	jc[0]=1;
	for(int i=1;i<=n;i++) jc[i]=jc[i-1]*i%mod;
}
int ksm(int x,int y){int res=1;for(;y;y>>=1,x=x*x%mod) if(y&1) res=res*x%mod;return res;}
int siz[N],tpcnt[N];
void dfs1(int now,int fa)
{
	siz[now]=1;tpcnt[now]=1;
	for(int i=head[now],v;i;i=edge[i].nxt)
	if((v=edge[i].to)!=fa)
	{
		dfs1(v,now);
		siz[now]+=siz[v];
		tpcnt[now]=tpcnt[now]*tpcnt[v]%mod*ksm(jc[siz[v]],mod-2)%mod;
	}
	tpcnt[now]=tpcnt[now]*jc[siz[now]-1]%mod;
}
int dp[N][N],ans[N];
void dfs2(int u,int fa)
{
	ans[u]=dp[u][0]*tpcnt[u]%mod;
	for(int i=head[u],v;i;i=edge[i].nxt)
	if((v=edge[i].to)!=fa)
	{
		int fxk=tpcnt[u]*(jc[siz[v]]*jc[siz[u]-siz[v]-1]%mod)%mod*ksm(tpcnt[v]*jc[siz[u]-1]%mod,mod-2)%mod;
		for(int j=0;j<siz[v];j++)
		for(int k=1;k<=siz[u]-siz[v];k++)
		dp[v][j]=(dp[v][j]+dp[u][j+k]*c[j+k-1][j]%mod*c[siz[u]-j-k-1][siz[v]-j-1]%mod*fxk%mod)%mod;
		dfs2(v,u);
	}
}
signed main()
{
	scanf("%lld",&n);
	ycl(n);
	for(int i=2,f;i<=n;i++) scanf("%lld",&f),Add_edge(i,f),Add_edge(f,i);
	for(int i=0;i<n;i++) scanf("%lld",&dp[1][i]);
	dfs1(1,0);
	dfs2(1,0);
	for(int i=1;i<=n;i++) printf("%lld ",ans[i]);
}
```

---

## 作者：george0929 (赞：12)

树上 DP 好题。

### DP 状态

和顺序有关的问题，在 DP 状态设计时，如果整体不好考虑，可以考虑当前 DP 完的集合在离散化后的状态，转移时乘上组合数。

$f_{u,i}$ 表示不考虑子树 $u$ 内部，将 $u$ 和子树 $u$ 外的节点拓扑序离散化后，节点 $u$ 的拓扑序为 $i$ 的方案数。

转移方向自上而下。

### 答案计算

**子问题 $1$**：一个离散化的整数序列，大小为 $m$，插入 $k$ 个有序数字的方案数是多少？

解答：逆向考虑，相当于从大小为 $m+k$ 的序列中选 $k$ 个分裂出来，答案为 $\binom{m+k}{k}$。

**子问题 $2$**：一个树的总共拓扑序个数是多少？

解答：我们有现成的结论，一个树的拓扑序个数为 $\frac{n!}{\prod_{i=1}^{n} sz_i}$。

则答案计算如下：

$$ans_i=\sum\limits_{j=1}^n b_j\times f_{i,j}\times \underbrace{\binom{(n-sz_i-j+1)+(sz_i-1)}{sz_i-1}}_{\text{第一部分}}\times \underbrace{\frac{sz_i!}{\prod_{k\in subtree(i)} sz_k}}_{\text{第二部分}}$$

第一部分解释：将大小为 $sz_i-1$ 的子树拓扑序插入到比 $i$ 拓扑序大的 $n-sz_i-j+1$ 个已经确定拓扑序的节点中。

第二部分解释：分配 $i$ 子树内部拓扑序。

维护 $g_u=\prod_{k\in subtree(u)} sz_k$，即可 $O(n^2)$ 计算答案。

### 初始值

$f_{1,1}=1$。

### 转移方程

设 $u$ 是 $v$ 的父节点，$u\to v$ 的转移如下：

$$f_{v,i}=\sum\limits_{j=1}^{i-1} f_{u,j}\times \underbrace{\binom{(n-sz_u+1-i)+(sz_u-sz_v-1)}{sz_u-sz_v-1}}_{\text{第一部分}}\times \underbrace{\frac{(sz_u-sz_v)!}{\prod\limits_{x\in subtree_u\land x\notin subtree_v} sz_x}}_{\text{第二部分}}$$

第一部分解释：将子树 $u$ 除去子树 $v$ 后的其他节点（不含 $u$）的拓扑序（大小为 $sz_u-sz_v-1$）插入到比 $u$ 拓扑序大的 $n-sz_u+1-i$ 个已经确定拓扑序的节点中。

第二部分解释：分配子树 $u$ 除去子树 $v$ 外的其他节点的拓扑序。

第二部分可表示为 $\frac{(sz_u-sz_v)!}{g_u\div g_v\div sz_u\times (sz_u-sz_v)}$。

前缀和优化后时间复杂度 $O(n^2)$。

### 代码实现

分两次 dfs，第一次算 $sz$ 和 $g$，第二次算 $f$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
int ksm(int a,int b){
	int res=1;
	while(b){
		if(b&1) res=res*a%mod;
		a=a*a%mod;
		b/=2;
	}
	return res;
}
int fac[10005],Ifac[10005];
void init(){
	const int V=1e4;
	fac[0]=1;
	for(int i=1;i<=V;i++) fac[i]=fac[i-1]*i%mod;
	Ifac[V]=ksm(fac[V],mod-2);
	for(int i=V-1;i>=0;i--) Ifac[i]=Ifac[i+1]*(i+1)%mod;
}
int C(int n,int m){
	if(n<0||m<0||n<m) return 0;
	return fac[n]*Ifac[m]%mod*Ifac[n-m]%mod;
}
//----------------
int n,b[5005];
vector<int> V[5005];
int f[5005][5005];
int sz[5005],g[5005];
void dfs1(int u){
	sz[u]=g[u]=1;
	for(int v:V[u]){
		dfs1(v);
		sz[u]+=sz[v];
		g[u]=g[u]*g[v]%mod;
	}
	g[u]=g[u]*sz[u]%mod;
}
void dfs2(int u){
	int invg=ksm(g[u],mod-2);
	for(int v:V[u]){
		int invsz=ksm(sz[u]-sz[v],mod-2);
		for(int i=1;i<=n-sz[v]+1;i++){
			f[v][i+1]=f[u][i]*C(n-sz[u]+1-i+sz[u]-sz[v]-1,sz[u]-sz[v]-1)%mod;
			f[v][i+1]=f[v][i+1]*fac[sz[u]-sz[v]]%mod*g[v]%mod*invg%mod*sz[u]%mod*invsz%mod; 
			f[v][i+1]=(f[v][i+1]+f[v][i])%mod;
		}
		dfs2(v);
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	init();
	cin>>n;
	for(int i=2;i<=n;i++){
		int p;
		cin>>p;
		V[p].push_back(i);
	}
	for(int i=1;i<=n;i++) cin>>b[i];
	dfs1(1);
	f[1][1]=1;
	dfs2(1);
	for(int i=1;i<=n;i++){
		int ans=0;
		int invg=ksm(g[i],mod-2)%mod;
		for(int j=1;j<=n;j++){
			int res=b[j]*f[i][j]%mod;
			res=res*C(n-sz[i]-j+1+sz[i]-1,sz[i]-1)%mod;
			res=res*fac[sz[i]]%mod*invg%mod;
			ans=(ans+res)%mod;
		}
		cout<<ans<<" ";
	}
	return 0;
}

```

---

## 作者：Drind (赞：5)

[tobie](https://www.luogu.com.cn/user/192044) 大神的题解真的是神了！但是因为语言太简练了，我们都没看懂......我好不容易看懂了，就对大神的题解做个解释吧！

首先我们要对于每个点 $x$ 求出 $x$ 在拓扑序的第 $i$ 位时的方案数，这样才能统计答案。那么我们就要对于每个 $x$ 单独计算。因为只有根到 $x$ 这一条链上的点，才会被要求在拓扑序里出现在 $x$ 前面，所以我们考虑从 $x$ 一路计算到根，这里就应该使用动态规划解决了。

注意！注意！接下来的内容里，$u$ 字母和 $x$ 字母表示的东西完全不同！！！$u$ 是 dp 状态里，处理到哪个节点。而 $x$ 是我们先前钦定的一个点，现在正在计算关于 $x$ 的答案。

我们设状态为 $f_{u,i}$，代表现在处理到这条链上的 $u$ 节点（注意是从下往上的），在只考虑 $u$ 的子树的情况下，已经有 $i$ 个点的拓扑序小于 $x$ 的方案数。这样，转移方程就是：

$$f_{fa_u,j+k} \gets f_{u,j}\times \dbinom{j+k-1}{j}\times \dbinom{siz_{fa_u}-j-k-1}{siz_u-j-1}\times C$$

详细解释一下这个方程，乘的第一个组合数大致意思就是把考虑 $u$ 的时候，在 $x$ 前面的 $j$ 个数插入在目前的 $j+k-1$ 个数字里。第二个组合数同理，是把 $x$ 后面的数插进来。而最后的 $C$ 代表 $fa_u$ 整个子树里除了 $u$ 的子树以外所有部分的拓扑序总数，这个可以用一次树形 dp 算出来，先不在这里讲了。

初值的话，就是 $f_{x,0}$ 的值为 1。统计答案的话，$f_{1,i}$ 的值代表最终 $x$ 的拓扑序为 $i+1$，乘 $b_{i+1}$ 加入答案即可。

但是如果我们这么做，就是类似于在树上做了 $n$ 次树上背包，单次背包复杂度是平方，所以总复杂度是 $O(n^3)$，我们不能接受。观察这个式子，虽然我们确定了一个 $x$，是作为 dp 起点，但是整个 dp 过程跟这个 $x$ 并没有关系，所以很多次 dp 我们都在做无用功。如果我们能从上往下做，复杂度就正确了。

在这里，我们对于每次 dp 交换起点和终点，也就是说初值为 $dp_{1,i}=b_{i+1}$，答案为 $dp_{x,0}$，然后从上往下 dp，这样我们就可以在 $O(n^2)$ 的复杂度内解决这个问题。

具体证明的话，感性理解一下，可以把每个状态看成一个点，然后转移方程看成一条边，最后我们要求从 $s$ 到 $t$ 所有路径乘积和，这个是可以反过来做的。

最后填一下前面的坑，如何树形 dp 算子树内有多少种拓扑序。我们设 $g_u$ 为子树 $u$ 内拓扑序数量，那么从 $v\in son_u$ 转移到 $u$ 的方程就是一个多重集排列：

$$f_u= \frac{(siz_u-1)!}{\prod_vsiz_v!}\prod_v f_v$$

如果我们要剔除 $u$ 的某一个子树，就把他的贡献除掉即可，具体详见代码。

```cpp
// Problem: P10013 [集训队互测 2023] Tree Topological Order Counting
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10013
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
const int p=1e9+7;
int _abs(int x){if(x<0) return -x; return x;}

struct node{
	int to,nxt;
}edge[N*2]; int head[N],cnt;
void add(int u,int v){
	edge[++cnt].to=v;
	edge[cnt].nxt=head[u];
	head[u]=cnt;
}
void adde(int u,int v){
	add(u,v); add(v,u);
}

int fac[N],ifac[N];
int qpow(int a,int index){
	int ans=1;
	while(index){
		if(index&1) ans=ans*a%p;
		a=a*a%p; index>>=1;
	}
	return ans;
}

void init(int n){
	fac[0]=ifac[0]=1;
	for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%p;
	ifac[n]=qpow(fac[n],p-2);
	for(int i=n-1;i>=1;i--) ifac[i]=ifac[i+1]*(i+1)%p;
}
int C(int n,int m){
	if(n<0||m<0||n<m) return 0;
	return fac[n]*ifac[m]%p*ifac[n-m]%p;
}

int f[N],siz[N],g[5010][5010],F[N];
void dfs1(int u){
	f[u]=1; siz[u]=1;//f是拓扑序数量
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].to; dfs1(v);
		siz[u]+=siz[v];
		f[u]=f[u]*f[v]%p*ifac[siz[v]]%p;
	}
	f[u]=f[u]*fac[siz[u]-1]%p;
}

void dfs2(int u){
	F[u]=g[u][0]*f[u]%p;//先统计答案
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].to;
		int tmp=f[u]*fac[siz[v]]%p*fac[siz[u]-siz[v]-1]%p*qpow(f[v]*fac[siz[u]-1]%p,p-2)%p;//这个就是方程里的C，可以注意一下这里是如何把子树 v 的贡献除掉的。
		for(int j=0;j<siz[v];j++){
			for(int k=1;k<=siz[u]-siz[v];k++){
				g[v][j]=(g[v][j]+C(j+k-1,j)%p*C(siz[u]-j-k-1,siz[v]-j-1)%p*g[u][j+k]%p*tmp%p)%p;//上文提到的转移方程
			}
			
		}
		dfs2(v);
	}
}

inline void fake_main(){
	int n; cin>>n;
	for(int i=2;i<=n;i++){
		int f; cin>>f;
		add(f,i);
	}
	for(int i=0;i<n;i++) cin>>g[1][i];
	dfs1(1); dfs2(1);
	for(int i=1;i<=n;i++) cout<<F[i]<<" "; cout<<"\n";
}

signed main(){
	init(N-10);
	ios::sync_with_stdio(false);
	int t; t=1;
	while(t--) fake_main();
}
```

---

## 作者：Purslane (赞：4)

# Solution

考虑直接对每个 $u$ 计算使他排名为 $rnk$ 的拓扑序个数。

很容易发现，我们要考虑 $1 \to u$ 路径上所有点外挂的情况。

设 $dp_{u,i}$ 表示，不考虑 $u$ 子树以内的拓扑序的情况，$u$ 排在第 $i$ 位的方案数。

> 注意，我们这里维护的是所有不在 $u$ 子树内的节点的相对拓扑序。

当 $u$ 往 $u$ 的儿子 $v$ 转移时，考虑把 $v$ 的兄弟节点加在 $u$ 的拓扑序后面，并且考虑这些兄弟节点的顺序。

容易发现，假设 $v$ 的排名为 $r$，所有 $u$ 的排名 $<r$ 的状态都可以转移过来，而且系数都一样。所以可以使用后缀优化 DP 优化转移即可。

复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=5000+10,MOD=1e9+7;
int n,sze[MAXN],b[MAXN],frac[MAXN],inv[MAXN],tcnt[MAXN];
vector<int> G[MAXN];
int qpow(int base,int p) {
	int ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;
	}
	return ans;
}
void dfs1(int u) {
	tcnt[u]=1,sze[u]=1;
	for(auto v:G[u]) dfs1(v),sze[u]+=sze[v],tcnt[u]=tcnt[u]*tcnt[v]%MOD*inv[sze[v]]%MOD;
	tcnt[u]=tcnt[u]*frac[sze[u]-1]%MOD;
	return ;
}
int dp[MAXN][MAXN];
int C(int u,int d) {
	return frac[d]*inv[u]%MOD*inv[d-u]%MOD;	
}
void dfs2(int u) {
	int mul=1;
	for(auto v:G[u]) mul=mul*tcnt[v]%MOD*inv[sze[v]]%MOD;
	for(auto v:G[u]) {
		int insv=qpow(tcnt[v]*inv[sze[v]]%MOD,MOD-2);
		ffor(r,1,n-sze[u]+1) dp[v][r+1]=(dp[v][r+1]+dp[u][r]*mul%MOD*insv%MOD*frac[sze[u]-sze[v]-1]%MOD*C(sze[u]-sze[v]-1,n-sze[u]+1-r+sze[u]-sze[v]-1))%MOD;	
	}
	for(auto v:G[u]) ffor(r,1,n-sze[v]+1) dp[v][r]=(dp[v][r]+dp[v][r-1])%MOD;
	for(auto v:G[u]) dfs2(v);
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n,frac[0]=1;
	ffor(i,1,n) frac[i]=frac[i-1]*i%MOD;
	inv[n]=qpow(frac[n],MOD-2);
	roff(i,n-1,0) inv[i]=inv[i+1]*(i+1)%MOD;
	ffor(i,2,n) {int f;cin>>f,G[f].push_back(i);}
	ffor(i,1,n) cin>>b[i];
	dfs1(1);
	dp[1][1]=1;
	dfs2(1);
	ffor(i,1,n) {
		int ans=0;
		ffor(j,1,n-sze[i]+1) {
			int cnt=dp[i][j]*tcnt[i]%MOD*C(sze[i]-1,n-j)%MOD;
			ans=(ans+cnt*b[j])%MOD;
		}
		cout<<ans<<' ';
	}
	return 0;
}
```

---

## 作者：Naib (赞：4)

直接想法是把 $1\sim x$ 这条链拿出来 DP。设 $f_{x,i}$ 表示递归到 $x$ 的时候 $x$ 的拓扑序是 $i$ 的方案数（暂且未考虑 $x$ 的子树）。那么有转移：
$$
f_{y\in son_{x},i+k-1}=\sum f_{x,i} \times {n-siz_{x}-i+1+siz_{x}-siz_{y}-1\choose siz_{x}-siz_{y}-1}\times C
$$
其中中间的组合数代表合并拓扑序在 $x$ 点之后的方案数，有两部分：

- 一个是 $x$ 的祖先的其他子树构成的拓扑序，一共有 $n-siz_{x}-i+1$ 个。
- 另一部分是当前 $x$ 除去儿子 $y$ 的其他儿子构成的拓扑序，一共 $siz_{x}-siz_{y}-1$ 个。

最后乘上 $C$（ $x$ 除去 $y$ 子树的其他子树的拓扑序数）就能够转移了。

显然注意到一个 $f_{x,i}$ 对于转移的 $y$ 是一段后缀，所以前缀和优化一下就是 $O(n^2)$ 的了。

注意最后求解答案的时候还要考虑 $x$ 本身的儿子带来的贡献。

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll maxn=5005, mo=1e9+7;

ll n;
ll siz[maxn], cnt[maxn], f[maxn][maxn], c[maxn][maxn], b[maxn];
vector<ll> g[maxn];

ll qpow(ll a,ll p) {
    ll res=1;
    while(p) {
        if(p&1) res=res*a%mo;
        p>>=1, a=a*a%mo;
    }
    return res;
}

void dfs(ll x) {
    cnt[x]=siz[x]=1;
    for(ll y:g[x]) {
        dfs(y);
        cnt[x]=cnt[x]*cnt[y]%mo*c[siz[x]+siz[y]-1][siz[y]]%mo;
        siz[x]+= siz[y];
    }
    return ;
}

void dfs2(ll x) {
    for(ll y:g[x]) {
        ll C=cnt[x]*qpow(cnt[y],mo-2)%mo*qpow(c[siz[x]-1][siz[y]],mo-2)%mo;
        for(ll i=1;i<=n-siz[x]+1;i++) {
            ll C2=c[n-siz[x]-i+1+siz[x]-siz[y]-1][siz[x]-siz[y]-1]*f[x][i]%mo*C%mo;
            f[y][i+1]=(f[y][i+1]+C2)%mo;
        }
        for(ll i=2;i<=n-siz[y]+1;i++) f[y][i]=(f[y][i]+f[y][i-1])%mo;
        dfs2(y);
    }
    return ;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin>>n;
    for(ll i=0;i<=n;i++) {
        for(ll j=0;j<=i;j++) {
            if(!j||i==j) c[i][j]=1;
            else c[i][j]=(c[i-1][j-1]+c[i-1][j])%mo;
        }
    }
    for(ll i=2;i<=n;i++) {
        ll p; cin>>p;
        g[p].push_back(i);
    }
    for(ll i=1;i<=n;i++) cin>>b[i];
    f[1][1]=1;
    dfs(1), dfs2(1);
    for(ll i=1;i<=n;i++) {
        ll ans=0;
        for(ll j=1;j<=n;j++) ans=(ans+b[j]*f[i][j]%mo*cnt[i]%mo*c[n-siz[i]-j+1+siz[i]-1][siz[i]-1]%mo)%mo;
        cout<<ans<<' ';
    }
    cout<<'\n';
    return 0;
}
```

---

## 作者：OccDreamer (赞：4)

首先题目里面写了每一个数都有权值，**一般**这种题只能去想求出每一个的具体方案数，那么也就是我们得求出 $h_{i,j}$ 表示在所有合法拓扑序中 $a_i=j$ 的方案数。

一颗树的拓扑序数量是 $\dfrac{n!}{\prod siz_i}$，相信大家都知道。

因为我们需要保证这一棵树满足拓扑排序的条件，不难先去考虑 $a_x=v$，并且我们确定 $x$ 的祖先的选数情况这时的方案数是多少。

不妨假设从 $1$ 到 $x$ 的数分别是 $v_1,v_2,v_3\dots v_k$，点分别是 $p_1,p_2,p_3\dots p_k$。

那么我们首先考虑 $p_k$ 子树内选数情况是 $\binom{n-v_k}{siz_{p_k}-1}$，然后再去考虑 $p_{k-1}$ 子树内选数情况，容易推出是 $\binom{n-v_{k-1}-siz_{p_k}}{siz_{p_{k-1}}-siz_{p_k}-1}$，以此类推，我们将这一部分的乘积叫做**选数方案**。

然后对于一些无关的子树直接用树的拓扑序数量把方案数算了就行。

这样我们就知道 $a_x=v$ 并且知道 $1 \to x$ 路径上的所有数的方案数怎么算了。

考虑 $y$ 是 $x$ 儿子，$a_y=z$，对于 $y$ 而言，**选数方案**会有什么变化，你会发现 $P_{y,z}=\dfrac{P_{x,v}}{\binom{n-v}{siz_{x}-1}}\binom{n-z}{siz_y-1}\binom{n-v-siz_y}{siz_x-siz_y-1}$，其中 $P_{i,j}$ 表示 $i$ 这个点选 $j$ 的**选数方案**。

**上面这个式子中只和 $x,v,y,z$ 有关系，其它的都是常量。**

写出 $P$ 的递推式子：$P_{i,j}=\binom{n-j}{siz_i-1}\sum_{k < j} \dfrac{P_{u,k}}{\binom{n-k}{siz_u-1}}\binom{n-k-siz_i}{siz_u-siz_i-1}$，其中 $u$ 是 $i$ 父亲节点。

$ans_x=\sum P_{x,i}b_iT$，其中 $T$ 是无关的子树的方案数。

关于 $P$ 的转移容易做到 $O(1)$，总时间复杂度 $O(n^2)$。

---

## 作者：Wei_Han (赞：1)

> 给定一棵树，给定权值数组 $b$，定义树的拓扑序为 $a$，对于一个点 $u$，其答案为所有可能 $a$ 的 $\sum b_{a_u}$，求所有点的答案。
> 
> $1 \le n \le 5\times 10^3$。

树的拓扑序计数，我怎么又忘了。

先给出结论，对于一个 $n$ 个点的树，其拓扑序数量为：

$$\frac{n!}{\prod siz_u}$$

考虑证明，设 $f_u$ 表示以 $u$ 为根的子树内拓扑序数量，则每次合并儿子是等价于将 $siz_u - 1$ 个点分配到若干集合当中，即：

$$\binom{siz_u-1}{siz_{v_1},siz_{v_2},\dots,siz_{v_k}} = \frac{(siz_u-1)!}{\prod_v siz_v!}$$

其中 $v$ 表示儿子，得到的式子就是组合数相消得到的。

然后除了根节点，每一个点对答案的贡献是 $\frac{(siz_v-1)!}{siz_v!} = \frac{1}{siz_v}$，那么把他们并起来，就是 $\frac{(n-1)!}{\prod \limits_{u\neq 1} siz_u}$，为了好看，把根节点拼上去，就得到了上式。

然后回到原题，考虑 dp，设 $f_{u,i}$ 表示以 $u$ 为根的子树还没走，$u$ 的拓扑序为 $i$ 的方案数，每次枚举 $u$ 的一个儿子 $v$ 转移：

$$f_{v,i} = \sum \limits_{j=1}^{i-1} f_{u,j} \binom{n-siz_u-j}{siz_u-siz_v-1} \frac{(siz_u-siz_v)!}{\prod \limits_{x \in t(u)-t(v)} siz_x}$$

组合数的系数是考虑 $u$ 子树外已经选完了，$v$ 子树内没选，选 $v$ 的兄弟子树的方案数，后面部分是对这 $siz_u - siz_v$ 个点的树的拓扑序计数，注意转移时扣掉 $v$ 子树需要修改 $u$ 的 $siz$。

预处理 $\prod siz_u$ 并前缀和优化可以做到 $O(1)$ 转移，复杂度 $O(n^2)$。

统计答案时，要考虑子树内的填数方法，即 $ans_u = \sum \limits_{i=1}^n b_i f_{u,i} \binom{n-i}{siz_u-1} \frac{siz_v!}{\prod \limits_{v \in t(u)} siz_v}$。

[Submission](https://www.luogu.com.cn/record/231683346)

---

## 作者：Guosn (赞：0)

## 前置芝士
- 将 $k$ 个数插入到 $m$ 个数中，方案数为 $\binom{m + k}{k}$，相当于从 $m + k$ 个数中拿 $k$ 个。  
- 一棵树的拓扑序个数是 $n!\over \prod sz_u$。对于一棵树有 $n!$ 种的排列，因为对于一个点 $u$ 他必须在它子树内的点前面，所以只有 $sz_u-1!$ 种的排列，相当于除以 $sz_u$，从根往下递归，总共除以 $\prod sz_u$
## 题解
下文中所指 $u$ 的子树含 $u$。  

发现一个点的拓扑序，只与他的父亲有关，所以考虑从上往下转移。设 $f_{u,i}$，表示不考虑 $u$ 子树内的点，其他点都已经考虑完了，$u$ 的拓扑序是 $i$ 的方案数。  

DP 转移：  
当从 $f_{u,j}$ 转移到 $f_{v,i}$ 时，要将除了 $v$ 以外的拓扑序安排好，相当将 $sz_u-sz_v-1$ 个点（$u$ 已经安排好了），插入到已经确定的 $n - sz_u + 1$ 个拓扑序中，但又因为子树的拓扑序比 $u$ 的大，所以只有 $n - sz_u + 1 -j$ 个点可以插，插完后再分配拓扑序。  
即（其中 $k$ 是 $v$ 子树以外的节点） ：
$$f_{v,i} = \sum_{j = 1} ^{i - 1} f_{u,j} \times \binom{n - sz_u - j + 1 + sz_u-sz_v-1}{sz_u-sz_v-1}\times \frac{(sz_u - sz_v - 1)!}{\prod sz_k}$$
化简后：
$$f_{v,i} = \sum_{j = 1} ^{i - 1} f_{u,j} \times \binom{n -sz_v- j}{sz_u-sz_v-1}\times \frac{(sz_u - sz_v - 1)!}{\prod sz_k}$$

统计答案：  
计算点 $i$ 的答案时，要将其子树内 $sz_i - 1$ 的点插入到已经确定的 $n - sz_i + 1$ 个已经确定的拓扑序种，而且还要比 $i$ 的拓扑序大，故（$v$ 是 $u$ 子树内的点）：  
$$ans_i = \sum_{j = 1} ^n b_j\times f_{i,j}\times \binom{n - sz_i + 1 - j + sz_i - 1}{sz_i - 1} \times \frac{sz_i!}{\prod sz_v}$$
化简：     
$$ans_i = \sum_{j = 1} ^n b_j\times f_{i,j}\times \binom{n -  j}{sz_i - 1} \times \frac{sz_i!}{\prod sz_v}$$

时间复杂度 $O(n^3)$ 考虑优化：$f_{v,i}$ 只比 $f_{v,i - 1}$ 多了 $f_{u,i - 1} \times \binom{n -sz_v- (i - 1)}{sz_u-sz_v-1}\times \frac{(sz_u - sz_v - 1)!}{\prod sz_k}$ 可以前缀和优化。    
时间复杂度 $O(n^2)$。  
**注意** ，要判断数组越界，组合数要取模（可能很大）。
## code
```cpp
#include<bits/stdc++.h>
#define N 5010
#define int long long
#define pb push_back
#define md 1000000007
#define Fo(a, b) for(auto a : b) 
#define fo(a, b, c) for(int b = a; b <= c; b++)
#define _fo(a, b, c) for(int b = a; b >= c; b--)
using namespace std;
int n, b[N], fac[N], sz[N], prod[N], C[N][N], f[N][N], ans[N];
vector<int>G[N]; 
int fast(int a, int p){
	int s = 1;
	while(p){
		if(p & 1) s = s * a % md;
		a = a * a % md;
		p >>= 1;
	}
	return s;
}
void init(){
	fac[0] = 1;
	fo(1, i, 5000) fac[i] = fac[i - 1] * i % md; 
	fo(0, i, n) C[i][0] = 1;
	fo(1, i, n) fo(1, j, i) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % md;
	prod[0] = 1, f[1][1] = 1;
}
void dfs(int u){
	sz[u] = prod[u] = 1;
	Fo(v, G[u]){
		dfs(v); 
		sz[u] += sz[v], prod[u] = prod[u] * prod[v] % md; 
	}
	prod[u] = prod[u] * fast(sz[u], md - 2) % md;
}
void calc(int v, int u){
	int tp = fac[sz[u] - sz[v] - 1];
 	Fo(cur, G[u]){
		if(v == cur) continue;
		tp = tp * prod[cur] % md;
	}
//	cout << "u;" << u << ' ' << "v:" << v << ' ' << "tp:" << tp << "\n";
	fo(1, i, n){
		if(n - sz[v] - i + 1 >= 0) f[v][i] = (f[v][i - 1] + f[u][i - 1] * C[n - sz[v] - i + 1][sz[u] - sz[v] - 1] % md * tp % md) % md;
	}
}
void solve(int u){
	Fo(v, G[u]){
		calc(v, u), solve(v);
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n;
	fo(2, i, n){
		int fa; cin >> fa;
		G[fa].pb(i);
	}
//	fo(1, i, n){
//		Fo(v, G[i]) cout << v << ' ';
//		cout << "\n";
//	}
	fo(1, i, n) cin >> b[i];
	init();
	//cout << C[4][2] << ' ';
	dfs(1), solve(1);
	//fo(1, i, n) cout << prod[i] << ' '; 
	fo(1, i, n) fo(1, j, n) 
		if(n >= j) ans[i] = (ans[i] + b[j] * f[i][j] % md * C[n - j][sz[i] - 1] % md * fac[sz[i]] % md * prod[i] % md) % md;
	fo(1, i, n) cout << ans[i] << ' ';
	return 0;
}

```

---

## 作者：R_shuffle (赞：0)

大概的思路是简单的，从上到下考虑拓扑序。

那么考虑怎么设计 dp 状态，不难发现实际上只能设 $f_{i,j}$ 表示 $i$ 的拓扑序为 $j$ 的方案数。假设已经得到了 $f$，怎么求答案。不难发现 $i$ 的答案就是 $\sum f_{i,j}{n-j\choose size_i-1}b_j$。

那么就考虑 $f_{i,j}$ 怎么求。考虑一个点 $u$ 及其父亲 $fa$，那么显然 $f_{u,j}$ 可以由 $f_{fa,k}(k<j)$ 转移来。由于在转移的时候我们需要在 $fa$ 和 $u$ 之间塞一些点，但是这些点具体是哪些我们并不关心。现在朴素转移是简单的，考虑优化，由于这些枚举 $k$ 是不必要的，所以考虑把前缀一起转移。

首先考虑设 $cnt_u$ 表示 $u$ 子树内的所有点的拓扑序的方案数，这个就是多重组合数，dfs 的时候顺便处理一下即可。然后考虑每次转移的时候考虑什么。显然需要先把其他的兄弟子树的方案数求好，然后考虑把当前子树插入的类似插空法的思路。每次前缀和优化一下即可。时间复杂度 $O(n^2)$。

---

## 作者：Erine (赞：0)

好题，考虑令 $f_{u,i}$ 为考虑了 $u$ 及 $u$ 子树**之外**的点，$u$ 的排名是 $i$ 的方案数，其中 $i\in (dep_u,n-siz_u+1]$。考虑从 $f_{u,i}$ 向 $f_{v,j}$ 转移。

![](https://cdn.luogu.com.cn/upload/image_hosting/69svdn0a.png)

那么我们会发现原本在 $u$ 时，有绿色部分的点；拓扑序在 $[1,i]$ 范围内的点**不会改变拓扑序**。$[i+1,n-siz_u+1]$ 范围内的点就会单独拎出来。而对于红色部分的点，首先可以通过众所周知的方法计算出子树拓扑序数（对于一棵有 $|V|$ 个结点的树，拓扑序数为 $\dfrac{|V|!}{\prod_{u\in V}siz_u}$），记为 $g_u$。那么我们发现你要把 $u\to v',v\neq v'$ 的 $v'$ 拿出来，$g_{v'}$ 乘在一起。其次，我们还需要在 $[i+1,n-siz_v+1]$ 中，先钦定 $j$ 位置上填的是 $v$，再将原来的 $[i+1,n-siz_u+1]$ 和除了 $v$ 之外的 $siz_{v'}$ 进行排列。所以转移式子为：

$$f_{v,j}\gets f_{u,i}\cdot \dfrac{(n-siz_v-i)!\prod_{u\to v', v'\neq v}g_{v'}}{\prod_{u\to v', v'\neq v}siz_{v'}!}$$

不难发现对于特定的 $(u,v,i)$ 转移系数都是固定的。于是差分优化转移即可。

对于统计答案，仍然考虑 $[i+1,n]$ 才会发生改变。所以点 $u$ 的答案是

$$ans_u=\sum_{i=dep_u+1}^{n-siz_u+1}b_if_{u,i}g_u\dbinom{n-i}{siz_u-1}$$

综上，我们 $\Theta(n^2)$ 解决了此题。

```cpp
f[1][1] = 1;
per(u, n, 1) {
	g[u] = fac[siz[u] - 1];
	for (int v : tr[u]) g[u] = g[u] * g[v] % mod * ifac[siz[v]] % mod;
	ig[u] = power(g[u], mod - 2);
}
rep(u, 1, n) {
	rep(i, dep[u] + 1, n - siz[u] + 2) (f[u][i] += f[u][i - 1]) %= mod;
	rep(i, dep[u] + 1, n - siz[u] + 1) {
		int mul = ifac[n - siz[u] - i + 1];
		for (int v : tr[u]) mul = mul * ifac[siz[v]] % mod * g[v] % mod;
		for (int v : tr[u]) {
			int x = f[u][i] * mul % mod * fac[n - siz[v] - i] % mod * fac[siz[v]] % mod * ig[v] % mod;
			(f[v][i + 1] += x) %= mod, (f[v][n - siz[v] + 2] += mod - x) %= mod;
		}
	}
	int ans = 0;
	rep(i, dep[u] + 1, n - siz[u] + 1) (ans += b[i] * f[u][i] % mod * C(n - i, n - siz[u] - i + 1) % mod * g[u] % mod) %= mod;
	write(ans), pc(' ');
}
```

---

