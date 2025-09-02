# [AGC063E] Child to Parent

## 题目描述

有一棵有 $N$ 个顶点的有根树，顶点编号为 $1$ 到 $N$。顶点 $1$ 是根，顶点 $i$（$2\leq i\leq N$）的父节点是 $P_i$。

给定一个非负整数 $r$ 和一个非负整数列 $A = (A_1, \ldots, A_N)$。你可以对这个数列进行任意次（也可以不进行）如下操作：

- 选择一个满足 $i \geq 2$ 且 $A_i \geq 1$ 的 $i$。将 $A_i$ 变为 $A_i - 1$，并将 $A_{P_i}$ 变为 $A_{P_i} + r$。

请你求出，最终可能得到的不同非负整数列 $A$ 的个数，答案对 $998244353$ 取模。

## 说明/提示

## 限制条件

- $2 \leq N \leq 300$
- $1 \leq P_i \leq i-1$（$2 \leq i \leq N$）
- $0 \leq r \leq 10^9$
- $0 \leq A_i \leq 10^9$

## 样例解释 1

最终可能得到的 $A$ 有以下 $4$ 种：$(1,1,1)$、$(3,0,1)$、$(3,1,0)$、$(5,0,0)$。

## 样例解释 2

最终可能得到的 $A$ 有以下 $5$ 种：$(1,1,1)$、$(1,2,0)$、$(2,0,1)$、$(2,1,0)$、$(3,0,0)$。

## 样例解释 3

最终可能得到的 $A$ 有以下 $6$ 种：$(1,1,1)$、$(1,3,0)$、$(3,0,1)$、$(3,2,0)$、$(5,1,0)$、$(7,0,0)$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
1 1
2
1 1 1```

### 输出

```
4```

## 样例 #2

### 输入

```
3
1 2
1
1 1 1```

### 输出

```
5```

## 样例 #3

### 输入

```
3
1 2
2
1 1 1```

### 输出

```
6```

## 样例 #4

### 输入

```
5
1 1 3 3
2
0 1 0 1 2```

### 输出

```
48```

## 样例 #5

### 输入

```
5
1 1 3 3
123456789
1 2 3 4 5```

### 输出

```
87782255```

# 题解

## 作者：Lynkcat (赞：5)

设 $c_i$ 表示第 $i$ 个点进行的 $-1$ 次数，我们去计算 $c_i$ 序列的个数即为答案。

设 $d_u=a_u+\sum_{v\in son_u}r\cdot c_v$，发现唯一的限制是 $0\leq c_u\leq d_u$。我们尝试维护 $f_i$ 表示 $i$ 子树的方案数，发现想要做到上述转移的话我们需要知道所有方案的 $d_u$ 的和，而要能知道 $d_u$ 的和，我们则需要知道 $d_u^2$ 的和，以此类推。

于是尝试记 $f_{i,j}$ 为所有方案 $c_i^j$ 的和，最后的答案是 $f_{1,0}$。发现我们要做的事情是先用二项式定理把儿子的 $f$ 合并起来然后加上 $a_u$。然后再把每个 $c_i^j$ 变成 $0^j+1^j+...+c_i^j$，这部分想要知道 $\sum c_i^j$ 变化过后的值只需要知道 $f_{i,0\sim j+1}$ 的值，然后暴力算一下转移的系数就行。

时间复杂度 $O(n^3)$。

```c++
// Problem: E - Child to Parent
// Contest: AtCoder - AtCoder Grand Contest 063
// URL: https://atcoder.jp/contests/agc063/tasks/agc063_e
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define poly vector<int>
#define IOS ios::sync_with_stdio(false)
#define ll long long
#define mp make_pair
#define mt make_tuple
#define pa pair < int,int >
#define fi first
#define se second
#define inf 1e18
#define mod 998244353
#define sz(x) (int)((x).size())
#define int ll
#define N 325
using namespace std;
int dp[N][N],coef[N][N];
int n,r,pw[N];
int C[N][N];
poly G[N];
int a[N],tmp[N];
int quickPower(int x,int y)
{
	int res=1;
	while (y)
	{
		if (y&1) res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
inline poly mul(poly &x,poly &y)
{
	poly res(x.size()+y.size()-1,0);
	for (int i=0;i<x.size();i++)
		for (int j=0;j<y.size();j++)
			res[i+j]=(res[i+j]+x[i]*y[j]%mod)%mod;
	return res;
}
inline poly add(poly &x,poly &y)
{
	poly res(max(x.size(),y.size()),0);
	for (int i=0;i<res.size();i++)
	{
		if (i<x.size()) res[i]=(res[i]+x[i])%mod;
		if (i<y.size()) res[i]=(res[i]+y[i])%mod;
	}
	return res;
}
inline poly div(poly &x,poly &y)
{
	poly nw=x;
	poly res(x.size()+1-y.size(),0);
	for (int i=x.size()-y.size();i>=0;i--)
	{
		res[i]=nw[i+y.size()-1]*quickPower(y.back(),mod-2)%mod;
		for (int j=y.size()-1;j>=0;j--)
		{
			nw[i+j]=(nw[i+j]-res[i]*y[j]%mod+mod)%mod;
		}
	}
	return res;
}	
inline poly cz(poly &a,poly &b)
{
	poly res(1,0);
	poly nw(1,1);
	for (int i=0;i<a.size();i++)
	{
		poly now(2,0);
		now[1]=1,now[0]=(mod-a[i])%mod;
		nw=mul(nw,now);
	}
	
	for (int i=0;i<a.size();i++)
	{
		poly now(2,0);
		now[1]=1,now[0]=(mod-a[i])%mod;
		nw=div(nw,now);
		int o=quickPower(b[i],mod-2);
		for (int j=0;j<a.size();j++)
			if (j!=i)
			{
				o=o*(a[i]-a[j]+mod)%mod;
			}
		o=quickPower(o,mod-2);
		for (auto &u:nw) u=u*o%mod;
		res=add(res,nw);
		o=quickPower(o,mod-2);
		for (auto &u:nw) u=u*o%mod;
		nw=mul(nw,now);
	}
	while (res.size()&&res.back()==0) res.pop_back();
	return res;
}
void dfs(int k,int fa,int dep)
{
	dp[k][0]=1;
	for (auto u:G[k])
	{
		if (u==fa) continue;
		dfs(u,k,dep+1);
		for (int i=dep+1;i>=0;i--)
		{
			int nxt=0;
			for (int j=0;j<=i;j++)
				nxt=(nxt+dp[k][j]*dp[u][i-j]%mod*C[i][j]%mod)%mod;
			dp[k][i]=nxt;
		}
	}
	if(k==1) return;
	for (int i=0,x=1;i<=dep+1;i++,x=x*r%mod)
		dp[k][i]=dp[k][i]*x%mod;
	for (int i=dep+1;i>=0;i--)
	{
		int nxt=0,coef=1;
		for (int j=i;j>=0;j--,coef=coef*a[k]%mod)
			nxt=(nxt+dp[k][j]*coef%mod*C[i][j]%mod)%mod;
		dp[k][i]=nxt;
	}
	for (int i=0;i<=dep;i++)
	{
		tmp[i]=0;
		for (int j=0;j<=i+1;j++)
			tmp[i]=(tmp[i]+dp[k][j]*coef[i][j]%mod)%mod;
	}
	for (int i=0;i<=dep;i++) dp[k][i]=tmp[i];
}
void BellaKira()
{
	cin>>n;
	for (int i=2;i<=n;i++)
	{
		int x;
		cin>>x;
		G[x].push_back(i);
	}
	cin>>r;
	pw[0]=1;
	for (int i=1;i<=n;i++) pw[i]=pw[i-1]*r%mod;
	for (int i=1;i<=n;i++)
		cin>>a[i];
	dfs(1,0,0);
	cout<<dp[1][0]<<'\n';
}
signed main()
{
	IOS;
	cin.tie(0);
	for (int i=0;i<=302;i++)
	{
		C[i][0]=1;
		for (int j=1;j<=i;j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
		poly x,y;
		int pre=(i==0);
		for (int j=1;j<=i+2;j++)
		{
			x.push_back(j);
			pre=(pre+quickPower(j,i))%mod;
			y.push_back(pre);
		}
		poly z=cz(x,y);
		for (int j=0;j<z.size();j++)
		{
			coef[i][j]=z[j];
		}
	}
	int T=1;
	while (T--)
	{
		BellaKira();
	}
		cout<<endl;
}
```

---

## 作者：xiaoyaowudi (赞：3)

无聊，写发题解玩玩。

前前情提要：银了，滚去 whk 了。

前情提要：那天晚上上语文课上到九点，下课了跑去倒序开题。一开始以为 E 会了，写了一个小时假了，被家长抓走锻炼睡觉去了。第二天花了 20 分钟过了。非常难过。

记 $f\left(u,i\right)$ 表示 $u$ 这个点，只考虑 $u$ 这个子树，$u$ 向父亲贡献的进位数的 $i$ 次方之和。当 $i=0$ 即为方案数。

那么，记 $x_v$ 为 $u$ 的儿子 $v$ 向 $u$ 的进位数。则可以得到：

$$
f\left(u,i\right)=\sum_{\left\{x_v\right\}}\left(\sum_{k=0}^{\displaystyle b_u+\sum r\times x_v} k^i\right)
$$

众所周知，里面那个自然数幂和是关于 $b_u+\sum r\times x_v$ 的一个多项式。而这个多项式的每一项的系数都可以通过一个 EGF 卷积的形式直接得到。做之前儿子的多项式复合上 $rx$ 即可。

因为这个 dp 第二维的范围是 dep，而且还要进行复合，因此复杂度是 $\mathcal{O}\left(n^3\right)$。

为什么那么简单的 E 赛时都没过！

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
constexpr int N(310),p(998244353);
int fac[N+1],ifac[N+1],inv[N+1],B[N],pre[N][N+1],dep[N];
std::vector<int> es[N];
int f[N][N],r;
void dfs(int u,int d=1)
{
	for(int i(0),t(1);i<=d;++i,t=1ll*t*B[u]%p) f[u][i]=1ll*t*ifac[i]%p;
	for(int v:es[u])
	{
		dfs(v,d+1);
		static int tmp[N];
		std::fill(tmp,tmp+d+1,0);
		for(int j(0);j<=d;++j) f[v][j]=1ll*f[v][j]*ifac[j]%p;
		for(int i(0);i<=d;++i)
		{
			for(int j(0);j+i<=d;++j) tmp[i+j]=(tmp[i+j]+1ll*f[u][i]*f[v][j])%p;
		}
		std::copy(tmp,tmp+d+1,f[u]);
	}
	for(int i(0);i<=d;++i) f[u][i]=1ll*f[u][i]*fac[i]%p;
	static int g[N];
	for(int i(0);i<d;++i)
	{
		g[i]=0;
		for(int j(0);j<=i+1;++j) g[i]=(g[i]+1ll*pre[i][j]*f[u][j])%p;
	}
	for(int i(0),t(1);i<d;++i,t=1ll*t*r%p) f[u][i]=1ll*g[i]*t%p;
}
int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);int n;std::cin>>n;
	inv[1]=1;for(int i(2);i<=N;++i) inv[i]=1ll*(p-p/i)*inv[p%i]%p;
	fac[0]=ifac[0]=1;for(int i(1);i<=N;++i) fac[i]=1ll*fac[i-1]*i%p,ifac[i]=1ll*ifac[i-1]*inv[i]%p;
	B[0]=1;
	for(int i(1);i<N;++i)
	{
		int cur(0);
		for(int j(0);j<i;++j) cur=(cur+(1ll*fac[i+1]*ifac[j]%p*ifac[i+1-j]%p)*B[j])%p;
		B[i]=1ll*(p-cur)*inv[i+1]%p;
	}
	for(int i(0);i<=n;++i)
	{
		for(int j(0);j<=i;++j) pre[i][i+1-j]=1ll*inv[i+1]*(1ll*fac[i+1]*ifac[j]%p*ifac[i+1-j]%p)%p*B[j]%p;
		pre[i][i]=(pre[i][i]+1)%p;
	}
	for(int i(2),t;i<=n;++i) std::cin>>t,es[t].emplace_back(i);std::cin>>r;
	for(int i(1);i<=n;++i) std::cin>>B[i];int ans(1);
	for(int v:es[1]) dfs(v),ans=1ll*ans*f[v][0]%p;
	std::cout<<ans<<std::endl;
	return 0;
}
```

---

## 作者：_LHF_ (赞：3)

讲个笑话，这题我出过链的版本，不过 AGC 的时候我并没有开到这题，~~并且赛后做这道题时做了好久才发现是自己出过的题~~。


设 $c_i$ 表示第 $i$ 个点被操作的次数，我们显然只需要数本质不同的 $c_i$。

有 $c_x\le A_x+R\sum_{y\in son_x}c_y$，如果数 $\sum c_x^k$，那其实只需要知道所有方案的 $A_x+R\sum_{y\in son_x}c_y$ 的 $0\sim k+1$ 次方即可。

设 $f_{i,j}$ 表示以 $i$ 为根的子树内所有方案的 $c_i^j$ 的和，当 $j=0$ 的时候可以认为是在数数量。

先考虑只有一个儿子的情况怎么转移，~~显然随便转移。~~

不然的话，转移其实是一个卷积的形式，设 $x$ 点深度为 $d_x$，那么复杂度应该是 $(|son_x|d_x^2)$ 的，所以说最坏情况就是链的情况，复杂度 $O(n^3)$，显然可以使用卷积优化做到 $O(n^2\log n)$。

为了方便，我们可以先将所有的 $A_i$ 增加 $1$，这样小于等于就变成了小于，可能实现起来更方便一点。



---

## 作者：DaiRuiChen007 (赞：2)

[Problem Link](https://www.luogu.com.cn/problem/AT_agc063_e)

**题目大意**

> 给定 $n$ 个点的有根树，每个节点上有一个数 $a_i$。
>
> 每次操作可以选定 $a_u>0$ 然后 $a_u\gets a_u-1,a_{fa(u)}\gets a_{fa(u)}+r$。
>
> 求有多少个不同的 $\{a_i\}$ 可以被生成。
>
> 数据范围：$n\le 300,a_i,r\le 10^9$。

**思路分析**

首先合法操作必然可以调成从下到上，那么我们设 $f_{u,i}$ 表示 $u$ 子树向上进位 $i$ 的答案。

那么每次 $f'_{u,i+jr}\gets f_{u,i}\times f_{v,j}$，然后 $f_u$ 做后缀和。

先考虑根节点上的 $f$，用生成函数 $f_u$ 刻画：那么我们要求的就是所有方案中 $a_u+r\sum j_v$ 的值之和。

那么分拆下去我们要知道 $\sum_j jf_{v,j}$，进一步要知道 $\sum_j j^2f_{w,j}$，其中 $fa(w)=v$。

设 $F_{u,k}=\sum f_{u,i}i^k$，那么考虑转移：
$$
\begin{aligned}
F'_{u,k}&=\sum_if'_{u,i}i^k\\
&=\sum_i (i+jr)^k\sum_{j} f_{u,i}f_{v,j}\\
&=\sum_{i} \binom kp f_{u,i}i^p\sum_{j} f_{v,j}j^{k-p}r^{k-p}\\
&=\sum_i\binom kpr^{k-p}F_{u,p}F_{v,k-p}
\end{aligned}
$$
转移很简单，考虑每次做后缀和：
$$
F'_{u,k}=\sum f_{u,i}(0^k+1^k+2^k+\cdots +i^k)
$$
把自然数幂和看成一个关于 $i$ 的 $k+1$ 次多项式，这个是经典的，就能从 $F_{u,0\sim k+1}$推出 $F'_{u,k}$，显然 $F_{u}$ 只要考虑 $k\le dep_u$ 的答案。

在做后缀和前求出 $F_{rt,0}$ 就是答案。

时间复杂度 $\mathcal O(n^3)$.

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MOD=998244353;
ll ksm(ll a,ll b=MOD-2,ll p=MOD)  {
	ll ret=1;
	for(;b;a=a*a%p,b=b>>1) if(b&1) ret=ret*a%p;
	return ret;
}
int a[305],n,R;
ll C[305][305],S[305][305],f[305][305],g[305];
vector <int> G[305];
void dfs(int u,int d) {
	for(int i=0;i<=d;++i) f[u][i]=ksm(a[u],i);
	for(int v:G[u]) {
		dfs(v,d+1);
		memset(g,0,sizeof(g));
		for(int i=0;i<=d;++i) {
			ll pw=1;
			for(int j=0;j<=i;++j,pw=pw*R%MOD) {
				g[i]=(g[i]+f[v][j]*f[u][i-j]%MOD*C[i][j]%MOD*pw)%MOD;
			}
		}
		memcpy(f[u],g,sizeof(f[u]));
	}
	if(d>1) {
		memset(g,0,sizeof(g));
		for(int i=0;i<d;++i) {
			for(int j=0;j<=i+1;++j) g[i]=(g[i]+S[i][j]*f[u][j])%MOD;
		}
		memcpy(f[u],g,sizeof(f[u]));
	}
}
signed main() {
	scanf("%d",&n);
	for(int i=0;i<=n+1;++i) for(int j=C[i][0]=1;j<=i;++j) {
		C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD;
	}
	S[0][1]=1;
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=i+1;++j) S[i][j]=C[i+1][j];
		for(int j=0;j<i;++j) for(int k=0;k<=j+1;++k) {
			S[i][k]=(S[i][k]-S[j][k]*C[i+1][j])%MOD;
		}
		for(int j=0;j<=i+1;++j) S[i][j]=(S[i][j]+MOD)*ksm(i+1)%MOD;
	}
	++S[0][0];
	for(int i=2,x;i<=n;++i) scanf("%d",&x),G[x].push_back(i);
	scanf("%d",&R);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	dfs(1,1);
	printf("%lld\n",f[1][0]);
	return 0;
}
```

---

## 作者：masterhuang (赞：0)

首先合法操作必然可以调成从下到上。

你先想一个暴力 **dp**：设 $f_{u,i}$ 表示 $u$ 子树向上进位 $i$​ 的答案。

转移就下面给 $j$ 个上来，上面 $+jr$。

那么每次 $f'_{u,i+jr} \leftarrow f_{u,i} \times f_{v,j}$，**然后对 $f_u$​ 做后缀和**。

---

先考虑根节点上的 $f$，用生成函数 $f_u$ 刻画：那么我们要求的就是所有方案中 $a_u+r \sum j_v$ 的值之和。

那么分拆下去我们要知道 $\sum\limits_j jf_{v,j}$，进一步要知道 $\sum\limits_j j^2 f_{w,j}$，其中 $P_w = v$。

这**启发**我们上**狄利克雷生成函数**：设 $F_{u,k} = \sum f_{u,i}i^k$，那么考虑转移：
$$
\begin{aligned}
F'_{u,k} &= \sum_i f'_{u,i}i^k \\
&= \sum_{i,j} (i+jr)^k f_{u,i}f_{v,j} \\
&= \sum_{p=0}^k\sum\limits_{i} \binom{k}{p} f_{u,i}i^p \sum_j f_{v,j}j^{k-p}r^{k-p} \\
&= \sum_{p=0}^k \binom{k}{p} r^{k-p} F_{u,p}F_{v,k-p}
\end{aligned}
$$
这时候难点在于还要对 $f$ 后缀和，然后计算出之后的 $F$。
$$
F'_{u,k}=\sum\limits_{i}i^k\sum\limits_{j\ge i} f_{u,j}=\sum\limits_{j} f_{u,j}\sum\limits_{i=1}^{j} i^k=\sum\limits_{j} f_{u,j}S(j,k)
\\
S(n,m)=\sum\limits_{i=1}^n i^m
$$
考虑经典自然数幂和转多项式，设**伯努利数**为 $B_n$。

有：$B_0=1,\sum\limits_{i=0}^n\dbinom{t+1}{i}B_i=0$。

则：
$$
S(n,m)=\dfrac{1}{m+1}\sum\limits_{i=0}^m \dbinom{m+1}{i} B_i n^{t+1-i}
\\
{\bf{let}}:S(n,m)=\sum\limits_{i=0}^{m+1}A(m,i)n^i
$$
就有：
$$
F'_{u,k}=\sum\limits_{j} f_{u,j}\sum\limits_{i=0}^{k+1}A(k,i)j^i=\sum\limits_{i=0}^{k+1} A(k,i) F_{u,i}
$$
直接暴力算即可。复杂度 $\mathcal{O}(n^3)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define fr(x) freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);
using namespace std;
const int N=305,mod=998244353;
int n,r,a[N],C[N][N],S[N][N],f[N][N],g[N];
basic_string<int>E[N];
inline int md(int x){return x>=mod?x-mod:x;}
inline int ksm(int x,int p){int s=1;for(;p;(p&1)&&(s=1ll*s*x%mod),x=1ll*x*x%mod,p>>=1);return s;}
void dfs(int x,int d)
{
	for(int i=0;i<=d;i++) f[x][i]=ksm(a[x],i);
	for(int y:E[x])
	{
		dfs(y,d+1);memset(g,0,(n+1)<<2);
		for(int k=0;k<=d;k++) for(int p=0,pw=1;p<=k;p++,pw=1ll*pw*r%mod)
			g[k]=(g[k]+1ll*C[k][p]*pw%mod*f[x][k-p]%mod*f[y][p])%mod;
		memcpy(f[x],g,(n+1)<<2);
	}
	if(d^1)
	{
		memset(g,0,(n+1)<<2);
		for(int i=0;i<d;i++) for(int j=0;j<=i+1;j++)
			g[i]=(g[i]+1ll*f[x][j]*S[i][j])%mod;
		memcpy(f[x],g,(n+1)<<2);
	}//用系数做"前缀和"
}
int main()
{
	scanf("%d",&n);
	for(int i=2,x;i<=n;i++) scanf("%d",&x),E[x]+=i;
	scanf("%d",&r);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=*C[0]=1;i<=n+1;i++) for(int j=*C[i]=1;j<=i;j++)
		C[i][j]=md(C[i-1][j]+C[i-1][j-1]);
	S[0][1]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=i+1;j++) S[i][j]=C[i+1][j];
		for(int j=0;j<i;j++) for(int k=0;k<=j+1;k++) 
			S[i][k]=(S[i][k]+1ll*(mod-S[j][k])*C[i+1][j])%mod;
		for(int j=0,I=ksm(i+1,mod-2);j<=i+1;j++) S[i][j]=1ll*S[i][j]*I%mod;
	}S[0][0]++;//预处理自然数幂和的系数，和题解说的完全不一致，是另一种方法
	return dfs(1,1),cout<<f[1][0],0;
}
```

---

