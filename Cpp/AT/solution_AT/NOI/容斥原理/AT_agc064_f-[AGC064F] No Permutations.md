# [AGC064F] No Permutations

## 题目描述

给定一个正整数 $N$。请计算满足以下条件的长度为 $3N$ 的数列 $A$ 的个数，并将结果对 $998244353$ 取模后输出。

- $A$ 中每个 $1$ 到 $N$ 的整数恰好各出现 $3$ 次。
- $A$ 的任意长度为 $N$ 的连续子序列都不是数列 $(1, 2, \ldots, N)$ 的一个排列。

## 说明/提示

## 限制条件

- $1 \leq N \leq 2 \times 10^5$
- 输入均为整数

## 样例解释 1

例如，$A = (1, 3, 3, 2, 2, 2, 1, 1, 3)$ 满足题目中的条件。而 $A = (1, 3, 3, 2, 2, 3, 1, 1, 2)$ 不满足条件，因为 $A$ 的第 $5, 6, 7$ 个元素组成的连续子序列是数列 $(1, 2, 3)$ 的一个排列。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3```

### 输出

```
132```

## 样例 #2

### 输入

```
123456```

### 输出

```
31984851```

# 题解

## 作者：littlez_meow (赞：3)

upd on 2025.1.1：式子出现了一些打错的地方。

### 思路

搬运一下官方题解做法。

直接做肯定没法做，考虑容斥。

记所有长度为 $n$ 的区间的集合 $R=\{[1,n+1),[2,n+2),\cdots,[2n+1,3n+1)\}$，设 $S\subseteq R$，定义 $f(S)$ 表示 $(-1)^{|S|}$ 乘上满足“$S$ 中任意区间都是 $1\sim n$ 的排列”的方案数。下面如无特殊说明，区间全部左闭右开。

则答案为 $\sum\limits_{S\subseteq R}f(S)$。

当 $S=\varnothing$ 时，$f(S)=\dfrac{(3n)!}{(3!)^n}$，也就是把相同值元素看作不同再除以每种方案重复算的次数。下面只讨论 $S\neq\varnothing$ 的情况。

定义两个区间 $[l,l+n),[r,r+n)$ 相交当且仅当 $|l-r|\le n$，注意 $|l-r|=n$ 的时候也是相交。定义一个连通块是一个区间的集合 $T$，满足对于其中任意两个区间 $a,b$，都存在一个区间的序列 $a=r_1,r_2,\cdots,r_k=b$，其中 $r_i(2\le i\le k)$ 与 $r_{i-1}$ 相交。此时称 $T$ 是连通的，其长度为区间 $\bigcup_{x\in T} x$ 的长度，记为 $\operatorname{len}(T)$。

直接计算所有 $S\subseteq R,S\neq\varnothing$（下记为 $S\in 2^R\setminus\{\varnothing\}$，即 $S$ 是 $R$ 的幂集的元素）的贡献不好算，我们把 $2^R\setminus\{\varnothing\}$ 划分成两个集合分别计算贡献。如无特殊说明，下面默认 $S\in 2^R\setminus\{\varnothing\}$，全集是 $2^R\setminus\{\varnothing\}$。

设 $P\subseteq 2^R$ 是满足以下条件的 $S$ 的集合：存在一个区间 $x\in S$，满足对于所有 $y\in S$，$x,y$ 相交。再设 $Q$ 是 $P$ 的补集。

那么下面就剩下了两个问题：计算 $\sum\limits_{S\in P}f(S)$ 和 $\sum\limits_{S\in Q}f(S)$。

#### 计算 $\sum\limits_{S\in P}f(S)$

设 $\operatorname{len}(S)=n+L$，$S$ 中区间左端点分别为 $l_0<l_1<\cdots<l_k$，不难发现 $l_k=l_0+L$，则排列的方案数有以下几部分：

* $[l_0,l_0+n)$ 是 $1\sim n$ 的排列，方案数 $n!$。

* $[l_0+n,l_1+n)$ 是区间 $[l_0,l_1)$ 的排列，方案数 $(l_1-l_0)!$。

* $[l_1+n,l_2+n)$ 是区间 $[l_1,l_2)$ 的排列，方案数 $(l_2-l_1)!$。

* 依此类推，$[l_{k-1}+n,l_k+n)$ 是区间 $[l_{k-1},l_k)$ 的排列，方案数 $(l_k-l_{k-1})!$。

* 不被任何区间包含的 $2n-L$ 个元素，方案数 $\rho(2n-L)=\dfrac{(2n-L)!}{2^{\max(n-L,0)}}$。这是因为总共有 $(2n-L)!$ 种方案，其中有 $\max(n-L,0)$ 对相同元素会算重。

全部乘起来，把容斥系数拆到求积号里面，有 $f(S)=-n!\rho(2n-L)\prod\limits_{i=1}^k(-(l_i-l_{i-1})!)$。

枚举 $L$ 求和得到 $\sum\limits_{S\in P}f(S)=-n!\sum\limits_{L=0}^{2n}\rho(2n-L)\sum\limits_{S\in P,\operatorname{len}(S)=n+L}\prod\limits_{i=1}^k(-(l_i-l_{i-1})!)$。

问题转化为求 $\sum\limits_{S\in P,\operatorname{len}(S)=n+L}\prod\limits_{i=1}^k(-(l_i-l_{i-1})!)$。

观察发现 $l_i-l_{i-1}$ 是一组 $L$ 的拆分，可以用生成函数描述。但是生成函数只是无脑加起来，并不能满足 $S\in P$ 的限制。所以我们考虑放宽限制。

设 $P'$ 表示连通的 $S$ 的集合。容易得到 $P\subseteq P'$。因此要求 $\sum\limits_{S\in P',\operatorname{len}(S)=n+L}\prod\limits_{i=1}^k(-(l_i-l_{i-1})!)-\sum\limits_{S\in P'\setminus P,\operatorname{len}(S)=n+L}\prod\limits_{i=1}^k(-(l_i-l_{i-1})!)$。

先来解决式子的第一项。正如刚刚说的，求积号里是一个拆分，可以用生成函数描述。

设 $w(L)=[x^L]\dfrac{1}{1+\sum\limits_{i=1}^n i!x^i}$，则 $\sum\limits_{S\in P',\operatorname{len}(S)=n+L}\prod\limits_{i=1}^k(-(l_i-l_{i-1})!)=(2n-L+1)w(L)$。这里 $2n-L+1$ 是 $l_0$ 的选法。

求 $w(1)\sim w(2L)$ 可以用多项式求逆 $O(n\log n)$ 求出来。

接下来就是本题最难的部分，求 $\sum\limits_{S\in P'\setminus P,\operatorname{len}(S)=n+L}\prod\limits_{i=1}^k(-(l_i-l_{i-1})!)$。

我们先考虑 $S\in P'\setminus P$ 长什么样子。设 $S$ 最左边的区间是 $[u,u+n)$，最右边是 $[v,v+n)$。你发现，由于每个区间长为 $n$，因此任意一个 $S$ 中区间都会和 $[u,u+n),[v,v+n)$ 中恰好一个相交。这是因为如果和两个相交就属于 $P$ 了，和两个都不相交长度就不可能到达 $n$。

于是，设和 $[u,u+n)$ 相交的区间的集合是 $U$，和 $[v,v+n)$ 相交的区间的集合是 $V$。显然，$U,V$ 都是连通的。$U$ 的长度是 $n+x$，区间左端点是 $u=u_0<u_1<\cdots<u_p=u+x$；$V$ 的长度是 $n+y$，区间左端点是 $v=v_0<v_1<\cdots<v_q=v+x$；$z$ 是 $U,V$ 的交的长度，即 $z=(u_p+n)-v_0$。则，$x+y-z+n=L,x\in[0,n),y\in[0,n),z\in(0,\min\{x,y\})$。不妨令 $(x,y,z)$ 的三元组的集合是 $A$，即 $A=\{(x,y,z)\in\mathbb{Z}^3|x\in[0,n),y\in[0,n),z\in[0,\min\{x,y\})\}$。三元组中 $z$ 是最小的。

所以有 $\sum\limits_{S\in P'\setminus P,\operatorname{len}(S)=n+L}\prod\limits_{i=1}^k(-(l_i-l_{i-1})!)=\sum\limits_{S\in P'\setminus P,\operatorname{len}(S)=n+L}(v_0-u_p)!\prod\limits_{i=1}^p(-(u_i-u_{i-1})!)\prod\limits_{i=1}^q(-(v_i-v_{i-1})!)$。这里前面没有负号是因为 $U,V$ 的负号消掉了。

类似于上面的讨论，我们有该式等于 $\sum\limits_{S\in P'\setminus P,\operatorname{len}(S)=n+L}(n-z)!w(x)w(y)$。

枚举 $S$ 变为枚举 $(x,y,z)$，得到该式等于 $(2n-L+1)\sum\limits_{(x,y,z)\in A,x+y-z+n=L}(n-z)!w(x)w(y)$。$2n-L+1$ 是 $l_0$ 的选法。

不妨设 $B_L=-\sum\limits_{(x,y,z)\in A,x+y-z=L-n}(n-z)!w(x)w(y)$。我们需要快速求出 $B_0\sim B_{n}$。这里前面的负号是为了把之前的式子前面的减变成加。

考虑分治。设 `solve(l,r)` 表示将满足 $x,y,z\in[l,r)$ 的所有 $(x,y,z)\in A$ 的贡献加进 $B_{x+y-z}$，再设 $m=\lfloor\dfrac{l+r}{2}\rfloor$。一共有三种贡献：

* $x,y,z<m$ 或 $x,y,z\ge m$ 时，可以递归下去。

* $z<m\le\min\{x,y\}$ 时，$x,y$ 可以任取 $[m,r)$ 的值，与 $z$ 无关。我们要对于每个 $L$ 求出 $\sum\limits_{x+y-z=L-n}[z\in[l,m)][x\in[m,r)][y\in[m,r)](n-z)!w(x)w(y)$。可以先把 $x,y$ 做和卷积，再把结果和 $z$ 做差卷积，用 NTT 做到 $O((r-l)\log(r-l))$。

* $z\le\min\{x,y\}<m\le\max\{x,y\}$ 时，由于 $x,y$ 是对称的，不妨令 $x<y$ ，答案乘 $2$ 即可，这是因为 $x=y$ 必不可能满足 $\min\{x,y\}<m\le\max\{x,y\}$。因此有 $z\le x<m\le y$，先把 $x,z$ 做差卷积，再和 $y$ 做和卷积即可 $O((r-l)\log(r-l))$。

时间复杂度 $O(n\log^2 n)$。

#### 计算 $\sum\limits_{S\in Q}f(S)$

类似于上面的讨论，设 $S$ 最左边的区间是 $[u,u+n)$，最右边是 $[v,v+n)$，任意一个 $S$ 中区间都会和 $[u,u+n),[v,v+n)$ 中恰好一个相交。设和 $[u,u+n)$ 相交的区间的集合是 $U$，和 $[v,v+n)$ 相交的区间的集合是 $V$。显然，$U,V$ 都是连通的。$U$ 的长度是 $n+x$，区间左端点是 $u=u_0<u_1<\cdots<u_p=u+x$；$V$ 的长度是 $n+y$，区间左端点是 $v=v_0<v_1<\cdots<v_q=v+x$；$z$ 是 $U,V$ 的距离，即 $z=v-u-n$。

排列的方案数有以下几部分：

* 不被 $[u,u+n),[v,v+n)$ 包含的部分，一共 $n!$ 种方案。

* $[u,u+n)$ 包含的部分：

  * $[u_p,u+n)$ 是不在 $[u+n,u+n+x)$ 元素的排列，方案数 $(n-x)!$。
 
  * $[u_{p-1},u_p)$ 是 $[u_{p-1}+n,u_p+n)$ 元素的排列，方案数 $(u_p-u_{p-1})!$。
 
  * 依此类推，$[u_0,u_1)$ 是区间 $[u_0+n,u_1+n)$ 的排列，方案数 $(u_1-u_0)!$。
 
* $[v,v+n)$ 包含的部分，类似地，方案数 $(n-y)!\prod\limits_{i=1}^q(v_i-v_{i-1})!$。

拆一下容斥系数，有 $f(S)=n!(n-x)!(n-y)!\prod\limits_{i=1}^p(-(u_i-u_{i-1})!)\prod\limits_{j=1}^q(-(v_j-v_{j-1})!)$。

枚举 $S$ 变成枚举 $(x,y,z)$，结合 $Q$ 的定义，我们有 $\sum\limits_{S\in Q}f(S)=n!\sum\limits_{z=1}^n(n-z+1)\sum\limits_{x=0}^{z-1}\sum\limits_{y=0}^{z-1}w(x)w(y)(n-x)!(n-y)!$。

化简即为 $\sum\limits_{S\in Q}f(S)=n!\sum\limits_{z=1}^n(n-z+1)\left(\sum\limits_{i=0}^{z-1}w(i)(n-i)!\right)^2$。$n-z+1$ 是选择 $u_0$。

可以前缀和优化做到 $O(n)$ 计算。

综上，我们以 $O(n\log^2 n)$ 的时间复杂度解决了这个问题。

### 代码

```cpp
#include<bits/stdc++.h>
#define File(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
#define ll long long
#define F(i,a,b) for(int i(a),i##i##end(b);i<=i##i##end;++i)
#define R(i,a,b) for(int i(a),i##i##end(b);i>=i##i##end;--i)
#define vi vector<int>
using namespace std;
const int MAXN=1<<20,MOD=998244353,INV2=499122177,INV6=166374059,G=3;
inline ll qpow(ll base,int expo){
	ll res(1);
	while(expo){
		(expo&1)&&(res=res*base%MOD);
		base=base*base%MOD,expo>>=1;
	}
	return res;
}
const int INVG=qpow(G,MOD-2);
int gpow[21],invgpow[21];
inline void calc(){
	F(i,1,20) gpow[i]=qpow(G,(MOD-1)>>i),invgpow[i]=qpow(INVG,(MOD-1)>>i);
	return;
}
inline void meow(int&t){
	t<0&&(t+=MOD);
	t>=MOD&&(t-=MOD);
	return;
}
int rev[MAXN];
inline void NTT(int*poly,int len,bool inv){
	F(i,0,len-1) (i<rev[i])&&(swap(poly[i],poly[rev[i]]),1);
	static ll g[MAXN];
	g[0]=1;
	for(int i(1),expo(1);i<len;i<<=1,++expo){
		ll omega=inv?invgpow[expo]:gpow[expo];
		F(j,1,i-1) g[j]=g[j-1]*omega%MOD;
		for(int j(0);j<len;j+=(i<<1)) F(k,0,i-1){
			int&x(poly[j|k]),&y(poly[i|j|k]);
			ll qwq(g[k]*y%MOD);
			y=x-qwq;
			y<0&&(y+=MOD);
			x+=qwq;
			x>=MOD&&(x-=MOD);
		}
	}
	if(inv){
		ll invl=qpow(len,MOD-2);
		F(i,0,len-1) poly[i]=poly[i]*invl%MOD;
	}
	return;
}
inline void build_rev(int n){
	F(i,0,n-1) rev[i]=(rev[i>>1]>>1)|((i&1)?(n>>1):0);
	return;
}
struct poly{
	int num[MAXN]={};
	int len=0;
	
	inline void resize(const int a){
		for(;len>a;--len) num[len]=0;
		len=a;
		if(len<0) len=0;
		return;
	}
	inline poly operator+(const poly a)const{
		poly res;
		res.len=max(a.len,len);
		F(i,0,res.len) res.num[i]=num[i]+a.num[i],meow(res.num[i]);
		return res;
	}
	inline poly operator+(const int a)const{
		poly res=*this;
		int&qwq(res.num[0]);
		qwq+=a;
		meow(qwq);
		return res;
	}
	inline poly operator-(const poly a)const{
		return a*(-1)+*this;
	}
	inline poly operator-(const int a)const{
		return *this+(-a);
	}
	inline poly operator*(const poly a)const{
		poly x,y=*this;
		if(a.len*1ll*len<=1e5){
			x.len=a.len+len;
			F(i,0,len) F(j,0,a.len){
				int&qwq(x.num[i+j]);
				qwq=(qwq+a.num[j]*1ll*num[i])%MOD;
			}
			return x;
		}
		x=a;
		int expo=max(__lg(((len+a.len+1)<<1)+1)+1,1),l=1<<expo;
		build_rev(l);
		NTT(x.num,l,0);
		NTT(y.num,l,0);
		F(i,0,l-1) x.num[i]=1ll*x.num[i]*y.num[i]%MOD;
		NTT(x.num,l,1);
		x.resize(len+a.len);
		return x;
	}
	inline poly operator*(const int a)const{
		poly res=*this;
		F(i,0,len){
			int&qwq(res.num[i]);
			qwq=a*1ll*qwq%MOD;
			meow(qwq);
		}
		return res;
	}
	inline poly inv(){
		poly res;
		res.num[0]=qpow(num[0],MOD-2);
		for(int l(2),expo(1);l<(len<<1);l<<=1,++expo){
			int tmp[MAXN]={};
			F(i,0,(l<<1)-1) rev[i]=(rev[i>>1]>>1)|((i&1)<<expo);
			memcpy(tmp,num,sizeof(int)*l);
			NTT(tmp,l<<1,0);
			NTT(res.num,l<<1,0);
			F(i,0,(l<<1)-1){
				int&qwq(res.num[i]),t(2-1ll*qwq*tmp[i]%MOD);
				meow(t);
				qwq=1ll*qwq*t%MOD;
			}
			NTT(res.num,l<<1,1);
			F(i,l,(l<<1)-1) res.num[i]=0;
		}
		res.resize(len);
		return res;
	}
};
int px[MAXN],py[MAXN];
inline vi mul(const vi&x,const vi&y){
	int n=x.size()+y.size()-1;
	n=1<<(__lg(n)+1);
	build_rev(n);
	F(i,0,x.size()-1) px[i]=x[i];
	F(i,x.size(),n-1) px[i]=0;
	F(i,0,y.size()-1) py[i]=y[i];
	F(i,y.size(),n-1) py[i]=0;
	NTT(px,n,0),NTT(py,n,0);
	F(i,0,n-1) px[i]=px[i]*1ll*py[i]%MOD;
	NTT(px,n,1);
	vi res(x.size()+y.size()-1);
	F(i,0,res.size()-1) res[i]=px[i];
	return res;
}
int n;
ll fact[MAXN],B[MAXN];
poly w;
inline ll rho(int L){
	return fact[2*n-L]*qpow(INV2,max(n-L,0))%MOD;
}
inline void m_le_xy(int l,int m,int r){
	vector<int>x(r-l+1),y(r-l+1);
	F(i,m,r-1) (x[i-l]+=w.num[i])>=MOD&&(x[i-l]-=MOD);
	F(i,l,m-1) y[r-i]=fact[n-i];
	x=mul(x,x);
	x=mul(x,y);
	F(i,max(r-2*l,0),x.size()-1){
		int qwq=i-r+l*2;
		if(qwq>n) break;
		(B[qwq]+=x[i])>=MOD&&(B[qwq]-=MOD);
	}
	return;
}
inline void x_le_m_le_y(int l,int m,int r){
	vector<int>x(r-l+1),y(r-l+1);
	F(i,l,m-1) (x[i-l]+=w.num[i])>=MOD&&(x[i-l]-=MOD);
	F(i,l,m-1) y[r-i]=fact[n-i];
	x=mul(x,y);
	F(i,0,min(int(x.size()-1),r-l)) x[i]=0;
	F(i,0,r-l) y[i]=0;
	F(i,m,r-1) y[i-l]=w.num[i];
	x=mul(x,y);
	F(i,max(r-2*l,0),x.size()-1){
		int qwq=i-r+l*2;
		if(qwq>n) break;
		(B[qwq]+=x[i])>=MOD&&(B[qwq]-=MOD);
		(B[qwq]+=x[i])>=MOD&&(B[qwq]-=MOD);
	}
	return;
}
void solve(int l,int r){
	if(r-l<=1) return;
	int m=(l+r)>>1;
	solve(l,m),solve(m,r);
	m_le_xy(l,m,r);
	x_le_m_le_y(l,m,r);
	return;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	calc();
	cin>>n;
	fact[0]=1;
	F(i,1,3*n) fact[i]=fact[i-1]*i%MOD;
	F(i,0,n) w.num[i]=fact[i];
	w.len=2*n+1;
	w=w.inv();
	int ans=fact[3*n]*qpow(INV6,n)%MOD;
	F(L,0,2*n) ans=(ans+rho(L)*(MOD-fact[n])%MOD*(2*n-L+1)%MOD*w.num[L])%MOD;//S in P'
	solve(0,n);
	F(L,n,2*n) ans=(ans+rho(L)*(MOD-fact[n])%MOD*(2*n-L+1)%MOD*B[L-n])%MOD;//S in P'\P
	ll sum=0;
	F(z,1,n){//S in Q
		sum=(sum+w.num[z-1]*fact[n-z+1])%MOD;
		ans=(ans+fact[n]*(n-z+1)%MOD*sum%MOD*sum)%MOD;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：fydj (赞：2)

官方题解和之前的一篇题解好像都有不正确的地方，根据自己的理解重新修正了一些细节。应该是正确的。

下标从 $0$ 开始。先把所有长度为 $n$ 的区间（左闭右开）拿出来，$[0,n),[1,n+1),\dots,[2n,3n)$。设这些 $2^n$ 个区间集合的集合为 $R$，那么对于 $S\in R$，设 $f(S)$ 表示集合 $S$ 中的区间都包含了一个完整的排列的方案数，乘以容斥系数 $(-1)^{|S|}$。答案就是 $\sum_{S\in R}f(S)$。

定义区间 $[l1,l1+n)$ 和 $[l2,l2+n)$ 相交，当且仅当 $|l1-l2|\le n$。

如果 $S$ 是空集，答案是好算的，是 $\frac{(3n)!}{6^n}$。剩下的 $S$，分成两类，一类是集合内存在一个区间和集合中其它的所有区间相交，这种区间集合的集合为 $P$；另一类是不存在这样一个区间，设为 $Q$。

先考虑算 $\sum_{S\in P}f(S)$。设集合 $S$ 内包含 $k+1$ 个区间，为 $[l_0,l_0+n),\dots,[l_k,l_k+n)$，设 $l_k=l_0+L$。那么 $f(S)=-n!\frac{(2n-L)!}{2^{\max(n-L,0)}}\prod _{i=1}^k -(l_i-l_{i-1})!$。其中 $\frac{(2n-L)!}{2^{\max(n-L,0)}}$ 表示不被 $S$ 包含的剩余位置的选法，分母的意义是有 $\max(n-L,0)$ 种数有两个，要避免交换位置算重。第一个 $n!$ 表示区间 $[l_0,l_0+n)$ 的方案，后面的 $(l_i-l_{i-1})!$ 表示 $[l_{i-1}+n,l_{i}+n)$ 的方案。可以枚举 $L\in [0,2n]$，变为计算长度为 $n+L$ 的集合的 $\prod _{i=1}^k -(l_i-l_{i-1})!$ 之和。

继续容斥。设 $P'$ 为连通的区间集合的集合，这里不要求“存在一个区间和集合中其它的所有区间相交”，因为这个条件很麻烦。算出 $S\in P'$ 的贡献要减去 $S\in P'/P$ 的贡献。

计算 $\sum_{S\in P'} \prod _{i=1}^k -(l_i-l_{i-1})!$。注意到 $\sum_{i=1}^k (l_i-l_{i-1})=l_k-l_0=L$，相当于 $L$ 的一个拆分。可以用生成函数 $\frac{1}{1+\sum_{i>0}i!x^i}$ 表示。设 $w_L=[x^L]\frac{1}{1+\sum_{i>0}i!x^i}$，则枚举 $L$ 后这部分的贡献为 $(2n-L+1)w_L$。前面的 $2n-L+1$ 是 $l_0$ 的选法。这部分可以用多项式求逆做到 $O(n\log n)$。

最难的部分，计算 $\sum_{S\in P'/P} \prod _{i=1}^k -(l_i-l_{i-1})!$。设最左边的区间为 $[u_0,u_0+n)$，和它相交的区间为 $[u_0,u_0+n),\dots,[u_p,u_p+n)$，这些区间的集合记为 $U$，最右边的区间为 $[v_q,v_q+n)$，和它相交的区间为 $[v_0,v_0+n),\dots,[v_q,v_q+n)$，这些区间的集合记为 $V$。集合 $S$ 中的每一个区间一定只会恰好出现在 $U,V$ 中的一个集合内，否则它就属于 $P$。则 $\prod _{i=1}^k -(l_i-l_{i-1})!=-(u_p-v_0)!\prod_{i=1}^p -(u_i-u_{i-1})!\prod _{i=1}^q -(v_i-v_{i-1})!$。

记 $U$ 和 $V$ 的交的长度为 $z$，则 $z=u_p+n-v_0$。那么原式的 $-(u_p-v_0)!$ 可以转换为 $-(n-z)!$。设 $U$ 的长度为 $n+x$，$V$ 的长度为 $n+y$，类似上一部分，两个连乘可以分别表示为 $w_x$ 和 $w_y$。由于 $P'/P$ 的性质，$x\in [0,n),y\in [0,n),z\in [0,\min(x,y))$，并且根据区间长度可以得到 $x+y-z=n-L$。把负号去掉，设 $\sum_{x+y-z=i} (n-z)!w_xw_y=B_i$，考虑计算出 $B_{1,2,\dots,n}$。

可以用分治的方法计算。设 `solve(l,r)` 表示考虑 $x,y,z\in [l,r)$ 的贡献。设 $mid=\lfloor\frac {l+r}{2}\rfloor$。

+ $x,y,z\in [l,mid)$ 或 $x,y,z\in [mid,r)$，可以分治下一层计算。
+ $z\in [l,mid),x,y\in [mid,r)$，可以先对 $x,y$ 做一遍和卷积再跟 $z$ 做一遍差卷积实现。
+ $z\in [l,\min(x,y)),\min(x,y)\in [l,mid),\max(x,y)\in [mid,r)$，可以先对 $\min(x,y),z$ 做一遍差卷积，再和 $z$ 做一遍和卷积。因为 $x,y$ 可以互换，所以要 $\times 2$。

这个部分的时间复杂度是 $O(n\log ^2n)$ 的，是本题的瓶颈。

终于计算完 $\sum_{S\in P}f(S)$ 了，现在考虑 $\sum_{S\in Q}f(S)$。这个部分相对不难。

还是类似。设最左边的区间为 $[u_0,u_0+n)$，和它相交的区间为 $[u_0,u_0+n),\dots,[u_p,u_p+n)$，这些区间的集合记为 $U$，最右边的区间为 $[v_q,v_q+n)$，和它相交的区间为 $[v_0,v_0+n),\dots,[v_q,v_q+n)$，这些区间的集合记为 $V$。记 $U$ 和 $V$ 的距离为 $z$，$U$ 的长度为 $n+x$，$V$ 的长度为 $n+y$。

可以把除去 $[u_0,u_0+n)$ 和 $[v_q,v_q+n)$ 剩下的 $n$ 个位置的方案处理了，有 $n!$ 种情况。剩下的以 $U$ 举例，$[u_p,u_0+n)$ 的贡献是 $-(n-x)!$，$[u_{p-1},u_p)$ 的贡献是 $-(u_p-u_{p-1})!$，以此类推可以得到 $U$ 的贡献为 $-(n-x)!\prod _{i=1}^p -(u_i-u_{i-1})!$。类似的，$V$ 的贡献是 $-(n-y)!\prod _{i=1}^q -(v_i-v_{i-1})!$。所以总的贡献是 $n!(n-x)!(n-y!)\prod _{i=1}^p -(u_i-u_{i-1})!\prod _{i=1}^q -(v_i-v_{i-1})!$，其中两个连乘可以表示为 $x,y$ 的分拆。

区间总长度为 $2n+z$，$u_0$ 有 $n-z+1$ 种选法，所以总的方案为 $n!\sum_{z=1}^n(n-z+1)\sum_{x=0}^{z-1}\sum_{y=0}^{z-1}w_xw_y(n-x)!(n-y)!$。注意到 $x,y$ 的地位相同，所以可以转化为 $n!\sum_{z=1}^n(n-z+1)(\sum_{i=0}^{z-1}w_i(n-i)!)^2$。用前缀和优化可以做到 $O(n)$。

总的时间复杂度为 $O(n\log ^2n)$，可以通过。[代码](https://atcoder.jp/contests/agc064/submissions/61279748)。

---

