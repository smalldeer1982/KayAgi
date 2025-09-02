# [AGC062E] Overlap Binary Tree

## 题目描述

给定一个奇数 $N$ 和一个非负整数 $K$。

请计算满足以下所有条件的整数对序列 $((L_1,R_1),(L_2,R_2),\dots,(L_N,R_N))$ 的个数，并对 $998244353$ 取模。

- $(L_1,R_1,L_2,R_2,\dots,L_N,R_N)$ 是 $1$ 到 $2N$ 的一个排列。
- $L_1 \leq L_2 \leq \dots \leq L_N$。
- 对于所有 $1 \leq i \leq N$，有 $L_i \leq R_i$。
- 恰好有 $K$ 个 $i$ 满足 $L_i+1=R_i$。
- 存在一个以 $1$ 到 $N$ 编号的 $N$ 个顶点的**有根二叉树** $T$，满足下述性质：
  - 在 $T$ 中，顶点 $i$ 和 $j$ 存在祖先-子孙关系，当且仅当区间 $[L_i,R_i]$ 和 $[L_j,R_j]$ 有交集。

这里，有根二叉树指的是每个节点的子节点数为 $0$ 或 $2$ 的有根树。在树 $T$ 中，如果顶点 $j$ 在连接根和顶点 $i$ 的简单路径上，或者顶点 $i$ 在连接根和顶点 $j$ 的简单路径上，则称顶点 $i$ 和 $j$ 存在祖先-子孙关系。

## 说明/提示

### 限制条件

- $1 \leq N < 2 \times 10^5$
- $0 \leq K \leq N$
- $N$ 是奇数
- 输入的所有值均为整数

### 样例解释 1

例如，$(L_1,R_1)=(1,5),(L_2,R_2)=(2,3),(L_3,R_3)=(4,6)$ 时，只有 $i=2$ 满足 $L_i+1=R_i$，即恰好有 $1$ 个。此外，对于第 $5$ 个条件中描述的树，顶点 $1$ 作为根，其子节点为顶点 $2$ 和 $3$，这样的有根树是满足条件的。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 1```

### 输出

```
2```

## 样例 #2

### 输入

```
1 0```

### 输出

```
0```

## 样例 #3

### 输入

```
521 400```

### 输出

```
0```

## 样例 #4

### 输入

```
199999 2023```

### 输出

```
283903125```

# 题解

## 作者：xcyle (赞：3)

~~为啥这题没有英文题解~~

---

先不考虑 $k$ 的限制。考虑枚举二叉树，数有多少个满足条件的区间序列。经过下面的分析可以说明，每个区间序列会恰好被数一次。

由深到浅确定这些区间的位置关系，一个点上的区间 $l,r$ 需要满足和子树的区间都交，那么 $l$ 必须在左子树所有右端点左边，容易发现这个选法是“不断向左儿子走的次数” $+1$，$r$ 的选法同理。

因此可以把树剖成若干条链，一条长度为 $d$ 的链贡献 $(d+1)!$ 的系数，一棵树的总方案数是所有系数之积。

转化一下计数对象，将一条链缩成一个点，新图两点间有边当且仅当在原树对应的链有交。原树上的链长变为新树上的度数。

于是问题变为对点有标号的，以某条边作为根的有根树计数，且区分根的左右儿子，容易证明钦定度数后连边的方案数是 $2(n-1)!$，而一棵树会被重复计数 $n!$ 次，即：
$$
\frac{2}{n}[x^{2n-2}](\sum\limits_{d=1}^n(d+1)!x^d)^n
$$
考虑 $k$ 的限制，这样的点一定是叶子，并且会将所在长度为 $d$ 的链的系数由 $(d+1)!$ 变为 $d!$。其它叶子的贡献是 $(d+1)!-d!$。最终答案为：

$$
\frac{2}{n}\binom{n}{k}[x^{2n-2}](\sum\limits_{d=1}^nd!x^d)^k(\sum\limits_{d=1}^n((d+1)!-d!)x^d)^{n-k}
$$
多项式快速幂即可，复杂度 $O(n\log n)$。

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_agc062_e)

**题目大意**

> 定义一个长度为 $n$ 的二元组序列 $[(l_1,r_1),(l_2,r_2),\cdots,(l_n,r_n)]$ 是好的，当且仅当：
>
> * $(l_1,r_1,l_2,r_2,\cdots,l_n,r_n)$ 构成一个 $1\sim 2n$ 的排列。
> * $l_1<l_2<l_3<\cdots<l_n$。
> * $\forall 1\le i\le n,l_i<r_i$。
> * 恰好存在 $k$ 个 $i$ 满足 $l_i+1=r_i$。
> * 存在一个有 $n$ 个节点的有根树满足对于任意 $i,j$，$i,j$ 在树上有祖先-后代关系当且仅当区间 $[l_i,r_i],[l_j,r_j]$ 有交（可以是包含关系），并且该树满足每个节点有零个或两个儿子。
>
> 给定 $n,k$，数有多少个好的二元组序列，对 $998244353$ 取模。

**思路分析**

先不考虑第四个限制，考虑把一个合法序列建成二叉树。

显然和所有区间都有交的区间只有一个，把这个区间提到根上，然后删掉。

那么剩下的 $n-1$ 个区间可以分成值域不相交的恰好两部分，分别递归左右子树即可。

显然一个区间序列可以对应一棵无标号二叉树，那么枚举一棵无标号二叉树尝试计算对应的合法序列数量。

自下往上确定每个区间，考虑 $l_u$ 的取值，显然 $l_u\le\min_{v\in\mathrm{subtree}(u)} r_v$。

我们考虑 $l_u$ 在子树里的 $2siz_u$ 个点里相对顺序，那么插入方案数为 $1+\sum_{i\in\mathrm{subtree}(u)} l_i\le \min r$，显然 $\min r$ 在从 $u$ 出发不断向左走到的那个叶子上，而合法的 $i$ 肯定就是这条不断向左走到的链上的节点。

设 $i$ 向左走的链上有 $d$ 个点，那么方案数为 $d+1$。



从叶子上计数，设这个叶子向上最多走 $d$ 条同向边，那么总方案数为 $(d+1)!$。

设叶子数 $m=\dfrac {n+1}2$，那么我们可以把这 $m$ 条链缩起来，即把 $i$ 的父亲设为从第 $i$ 个叶子所在的链顶所在的链。

最终会得到一棵有两个根的无标号树（根之间有顺序），这两个根就是原树根节点所在的两条同向链。

一个转化的例子如下图（来自官方题解）：

![](https://img.atcoder.jp/agc062/1105d56d10327df9f290809836bf3009.jpg)

可以发现一条链的长度在转化后就是一个点的度数。

给 $m$ 个点标号，设第 $i$ 个点的度数为 $d_i$，那么贡献就是 $\prod_{i=1}^{m}(d_i+1)!$。

然后考虑生成树的个数，每次选一条边，然后找一个没有父亲的点当儿子，方案数为 $\prod_{i=1}^{m-2} (m-i)\times (m-i+1)$。

最后除去选边的顺序 $(m-2)!$，再区分两个根的顺序得到总方案数为 $2(m-1)!$。

用生成函数描述答案：
$$
\mathrm{Ans}=\dfrac{2(m-1)!}{m!}[z^{2m-2}]\left(\sum_{i=1}^{m-1}(i+1)!z^i\right)^m
$$
现在考虑加入第四个限制，显然长度为 $1$ 的区间肯定是叶子，如果走到底得到的点是一个长度为 $1$ 的区间，那么 $l_u$ 不能插入这两个点中间，方案数为 $d$。

那么一个叶子被钦定长度为 $1$，方案数会变成 $d!$，钦定长度 $>1$ 就会得到方案数为 $(d+1)!-d!$，得到：
$$
\mathrm{Ans}=\dfrac{2(m-1)!}{m!}\binom mk[z^{2m-2}]\left(\sum_{i=1}^{m-1} i!z^i\right)^k\left(\sum_{i=1}^{m-1} ((i+1)!-i!)z^i\right)^{m-k}
$$
用多项式快速幂解决，注意到两个多项式的 $z^1$ 系数都为 $1$，约去一个 $z$ 即可方便处理。

时间复杂度 $\mathcal O(n\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Polynomial {
const int MOD=998244353,N=1<<18,G=3;
int rev[N],inv[N],w[N<<1];
int ksm(int a,int b=MOD-2,int p=MOD) {
	int ret=1;
	for(;b;a=1ll*a*a%p,b=b>>1) if(b&1) ret=1ll*ret*a%p;
	return ret;
}
void poly_init() {
	inv[1]=1;
	for(int i=2;i<N;++i) inv[i]=1ll*(MOD-MOD/i)*inv[MOD%i]%MOD;
	for(int k=1;k<=N;k<<=1) {
		int x=ksm(G,(MOD-1)/k); w[k]=1;
		for(int i=1;i<k;++i) w[i+k]=1ll*x*w[i+k-1]%MOD;
	}
}
int plen(int x) { int y=1; for(;y<x;y<<=1); return y;  }
void ntt(int *f,bool idft,int n) {
	for(int i=0;i<n;++i) {
		rev[i]=(rev[i>>1]>>1);
		if(i&1) rev[i]|=n>>1;
	}
	for(int i=0;i<n;++i) if(rev[i]<i) swap(f[i],f[rev[i]]);
	for(int k=2,x,y;k<=n;k<<=1) {
		for(int i=0;i<n;i+=k) {
			for(int j=i;j<i+k/2;++j) {
				x=f[j],y=1ll*f[j+k/2]*w[k+j-i]%MOD;
				f[j]=(x+y>=MOD)?x+y-MOD:x+y,f[j+k/2]=(x>=y)?x-y:x+MOD-y;
			}
		}
	}
	if(idft) {
		reverse(f+1,f+n);
		for(int i=0,x=ksm(n);i<n;++i) f[i]=1ll*f[i]*x%MOD;
	}
}
void poly_inv(const int *f,int *g,int n) {
	static int a[N];
	g[0]=ksm(f[0]);
	int k=2;
	for(;k<(n<<1);k<<=1) {
		for(int i=0;i<k;++i) a[i]=f[i];
		ntt(g,0,k<<1),ntt(a,0,k<<1);
		for(int i=0;i<(k<<1);++i) {
			g[i]=(2-1ll*a[i]*g[i]%MOD)*g[i]%MOD;
			if(g[i]<0) g[i]+=MOD;
		}
		ntt(g,1,k<<1);
		memset(g+k,0,sizeof(int)*k);
	}
	memset(g+n,0,sizeof(int)*(k-n));
	memset(a,0,sizeof(int)*k);
}
void poly_ln(const int *f,int *g,int n) {
	static int a[N],b[N];
	poly_inv(f,a,n);
	for(int i=1;i<n;++i) b[i-1]=1ll*i*f[i]%MOD;
	int m=plen(n<<1);
	ntt(a,0,m),ntt(b,0,m);
	for(int i=0;i<m;++i) a[i]=1ll*a[i]*b[i]%MOD;
	ntt(a,1,m);
	g[0]=0;
	for(int i=1;i<n;++i) g[i]=1ll*a[i-1]*inv[i]%MOD;
	memset(g+n,0,sizeof(int)*(m-n));
	memset(a,0,sizeof(int)*m);
	memset(b,0,sizeof(int)*m);
}
void poly_exp(const int *f,int *g,int n) {
	static int a[N];
	g[0]=1;
	int k=2;
	for(;k<(n<<1);k<<=1) {
		poly_ln(g,a,k);
		for(int i=0;i<k;++i) a[i]=(f[i]+MOD-a[i])%MOD;
		++a[0];
		ntt(a,0,k<<1),ntt(g,0,k<<1);
		for(int i=0;i<(k<<1);++i) g[i]=1ll*g[i]*a[i]%MOD;
		ntt(g,1,k<<1);
		memset(g+k,0,sizeof(int)*k);
	}
	memset(g+n,0,sizeof(int)*(k-n));
	memset(a,0,sizeof(int)*k);
}
void poly_qpow(const int *f,int *g,int n,int k) {
	static int a[N];
	poly_ln(f,a,n);
	for(int i=0;i<n;++i) a[i]=1ll*a[i]*k%MOD;
	poly_exp(a,g,n);
	memset(a,0,sizeof(int)*n);
}
}
using Polynomial::ntt;
using Polynomial::ksm;
const int N=1<<18,MOD=998244353;
int n,m,k,f[N],g[N],fac[N],ifac[N],a[N],b[N];
signed main() {
	Polynomial::poly_init();
	scanf("%d%d",&n,&k),m=(n+1)>>1;
	if(n==1) return puts(k?"1":"0"),0;
	if(k>m) return puts("0"),0;
	for(int i=fac[0]=ifac[0]=1;i<N;++i) ifac[i]=ksm(fac[i]=1ll*fac[i-1]*i%MOD);
	for(int i=1;i<m;++i) f[i-1]=fac[i],g[i-1]=(fac[i+1]+MOD-fac[i])%MOD;
	Polynomial::poly_qpow(f,a,m,k);
	Polynomial::poly_qpow(g,b,m,m-k);
	ntt(a,0,N),ntt(b,0,N);
	for(int i=0;i<N;++i) a[i]=1ll*a[i]*b[i]%MOD;
	ntt(a,1,N);
	printf("%lld\n",2ll*ksm(m)*fac[m]%MOD*ifac[k]%MOD*ifac[m-k]%MOD*a[m-2]%MOD);
	return 0;
}
```

---

