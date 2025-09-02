# [ABC387G] Prime Circuit

## 题目描述

给定编号为 $1$ 到 $N$ 的 $N$ 个顶点的简单无向连通图 $G$，求满足以下条件的图的数量对 $998244353$ 取模的结果：

- $G$ 中任意回路的边数均为素数。  
  此处回路定义为允许重复经过顶点但**不允许**重复经过边的闭路径。

## 说明/提示

### 约束条件

- $N$ 是满足 $1 \leq N \leq 2.5 \times 10^5$ 的整数

### 样例解释 1

满足条件的图 $G$ 有以下 4 种：  
- 边集为 $(1, 2), (1, 3)$ 的图  
- 边集为 $(1, 2), (2, 3)$ 的图  
- 边集为 $(1, 3), (2, 3)$ 的图  
- 边集为 $(1, 2), (1, 3), (2, 3)$ 的图  

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3```

### 输出

```
4```

## 样例 #2

### 输入

```
2025```

### 输出

```
879839321```

## 样例 #3

### 输入

```
61261```

### 输出

```
202537766```

# 题解

## 作者：emmoy (赞：4)

## 问题大意

求有 $n$ 个顶点（有标号）的所有简单无向连通图（即无重边无自环的无向连通图）$G$ 中满足以下条件的图的个数，答案模 $998244353$。

对于 $G$ 中的每个环，该环中的边数都是质数。

环可以重复经过同一顶点，但不能重复经过同一条边。

## 解法

借鉴了 at 第二篇题解。

首先我们发现如果图 $G$ 中有重复经过同一顶点的环，那么图 $G$ 绝对不合法。

因为这种环绝对是由两个及以上的简单环（即没有重复经过同一顶点）拼起来的。

而如果这个环由两个简单环拼凑起来，由于原图是简单无向图，于是没有长度为 $1$ 和 $2$ 的环，于是两个简单环的环长就为奇质数，加起来就为大于 $2$ 的偶数，就不是指数，所以不合法。

有由两个以上的简单环拼起来的环的图绝对有由两个简单环拼起来的环，于是也不合法。

所以我们知道绝对不会有两个环有点相交。

于是如果我们将原图的环全部缩成点，那么原图就会变成一棵树。

根据扩展卡莱定理，有 $n$ 个点，组成了 $a_1,a_2,a_3,\cdots,a_m$ 的 $m$ 个连通块，再用边连起来而组成一棵树的方案数为 $n^{m-2}\prod_{i=1}^{m}a_i$。

想看证明可以看[这篇博客](https://www.cnblogs.com/A-Quark/p/16417307.html)，~~主要因为我不会证~~。

那么再将式子化简一下，就可以得到 $\prod_{i=1}^{m}a_in\over n^2$。

那么，由于树上节点可以是环缩成的也可以本来就是一个点，于是环长 $s$ 就可以等于 $1$ 或奇质数。

那么答案就是先枚举缩完点树上有 $m$ 个点，每个点的原大小为 $s_i,i\in[1,m]$，那么对于每一种情况答案为 ${1\over n^2} \sum_{i=1}^ms_i\times n\times C(s_i)$。

其中

$$
C(x)=\begin{cases}
1&(x=1)\\
{(x-1)!\over 2}&(x>1)
\end{cases}
$$

乘上 $C(s_i)$ 是因为环内的点可以排列，但要求旋转后不一致，所以是 $(x-1)!$，又因为是无向环，所以还要除以 $2$。

由于 $1\over n^2$ 与 $s$ 无关，所以可以将所有答案求出后再乘上 $1\over n^2$。

由于点有标号，所以是排列，所以考虑对于 $s$ 的指数生成函数。

$$
\begin{aligned}
F(x)&=\sum_{i=1\vee (i\geqslant3\wedge i\in \mathbb{P})}i\times n\times C(i)\times{x^i\over i!}\\
&=nx+\sum_{i\geqslant3\wedge i\in \mathbb{P}}i\times n\times {(i-1)!\over 2}\times{x^i\over i!}\\
&=nx+\sum_{i\geqslant3\wedge i\in \mathbb{P}}{n\over 2}x^i\\
\end{aligned}
$$

对于总答案 $G(x)$，其指数生成函数为

$$
\begin{aligned}
G(x)=\sum_{i=0}{F(x)^i\over i!}=e^{F(x)}
\end{aligned}
$$

多项式 $\exp$ 即可。

答案就是生成函数的第 $n$ 项，其系数为 $n![x^n]G(x)$ 。

别忘了最后再乘上 $1\over n^2$。

## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
const int p=998244353,y=3,ny=332748118;
int n;
int r[N],a[N],ans[N],f[N],g[N];
int ksm(int a,int b=p-2){
	int ans=1;
	for(;b;b>>=1,a=a*a%p) if(b&1) ans=ans*a%p;
	return ans;
}
void NTT(int *a,int len,int type){
	for(int i=1;i<len;i++) if(i<r[i]) swap(a[i],a[r[i]]);
	for(int mid=1;mid<len;mid<<=1){
		const int wn=ksm((type?y:ny),(p-1)/(mid<<1));
		for(int R=mid<<1,j=0;j<len;j+=R){
			int w(1);
			for(int k=0;k<mid;k++,w=w*wn%p){
				int x=a[j+k],y=a[j+k+mid]*w%p;
				a[j+k]=(x+y)%p;
				a[j+k+mid]=(x+p-y)%p;
			}
		}
	}
	if(type) return;
	int inv=ksm(len);
	for(int i=0;i<len;i++) a[i]=a[i]*inv%p;
}
void inv(int *a,int *b,int len){
	if(len==1) {b[0]=ksm(a[0]);return;}
	inv(a,b,(len+1)>>1);
	int m=len<<1;
	int limit,l;
	for(limit=1,l=0;limit<m;limit<<=1,l++);
	for(int i=1;i<limit;i++) r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	for(int i=0;i<len;i++) f[i]=a[i];
	for(int i=len;i<limit;i++) f[i]=0;
	NTT(f,limit,1),NTT(b,limit,1);
	for(int i=0;i<limit;i++) b[i]=b[i]*((2+p-f[i]*b[i]%p)%p)%p;
	NTT(b,limit,0);
	for(int i=len;i<limit;i++) b[i]=0;
}
void mul(int*f,int *g,int l1,int l2){
	int limit,l;
	for(limit=1,l=0;limit<=l1+l2;limit<<=1,l++);
	for(int i=1;i<limit;i++) r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	NTT(f,limit,1),NTT(g,limit,1);
	for(int i=0;i<limit;i++) f[i]=f[i]*g[i]%p;
	NTT(f,limit,0);
	for(int i=limit-1;i>=1;i--) f[i]=f[i-1]*ksm(i,p-2)%p;
}
int h[N];
void ln(int *a,int *b,int len){
	for(int i=1;i<len;i++) h[i-1]=a[i]*i%p;
	inv(a,b,len);
	mul(b,h,len,len-1);
	b[0]=0;
}
void expp(int *a,int *b,int len){
	if(len==1) {b[0]=1;return;}
	expp(a,b,(len+1)>>1);
	int m=len<<1,limit,l;
	for(limit=1,l=0;limit<m;limit<<=1,l++);
	for(int i=0;i<limit;i++) g[i]=0;
	ln(b,g,len);
	for(int i=len;i<limit;i++) g[i]=0;
	for(int i=0;i<len;i++) f[i]=a[i];
	for(int i=len;i<limit;i++) f[i]=0;
	for(int i=1;i<limit;i++) r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	NTT(f,limit,1),NTT(g,limit,1),NTT(b,limit,1);
	for(int i=0;i<limit;i++) b[i]=((1-g[i]+p)%p+f[i])%p*b[i]%p;
	NTT(b,limit,0);
	for(int i=len;i<limit;i++) b[i]=0;
}
int pr[N],vis[N],cnt;
signed main(){
	cin>>n;
	for(int i=2;i<=3e5;i++){//筛素数
		if(!vis[i]) pr[++cnt]=i;
		for(int j=1;j<=cnt&&pr[j]*i<=3e5;j++){
			vis[i*pr[j]]=1;
			if(!(i%pr[j])) break;
		}
	}
	a[1]=n;
	for(int i=2;i<=cnt;i++) a[pr[i]]=n*((p+1)/2)%p;//F(x)函数
	expp(a,ans,n+10);//多项式exp
	int an=ans[n];//得到第n项
	for(int i=1;i<=n;i++) an=an*i%p;
	cout<<an*ksm(n*n%p,p-2)%p;
	return 0;
}
```

---

## 作者：qczrz6v4nhp6u (赞：3)

### Solution

下文中的环可以经过重复的点，但不能经过重复的边。

首先有经典结论：没有偶环 $\iff$ 原图是点仙人掌，且每一个环长度都是奇数。证明考虑如果有两个奇环拼在一起一定会产生偶环即可。

类似地，考虑推广到本题。由于是简单图，所以不存在长度为 $2$ 的环。容易发现上述推导仍然成立，所以这样一个图等价于每个环长都是质数的点仙人掌。

将环视为一个边双，则每个边双的大小要么是 $1$ 要么是奇质数。设每个边双的大小是 $s_1,s_2,\cdots,s_k$（其中 $\sum s_i=n$ 且 $s_i\le s_{i+1}$），这些边双要连成一棵树，系数就是：

$${n\choose s_1,s_2,\cdots,s_k}\times \prod_{c=1}^n\frac1{(\sum_{i=1}^k[s_i=c])!}\times \prod_{i=1}^kf(s_i)\times n^{k-2}\prod_{i=1}^ks_i$$

其中

$$f(x)=\begin{cases}1&\text{if }x=1\\\frac{(x-1)!}{2}&\text{if }x\text{ is an odd prime}\\
0&\text{otherwise}\end{cases}$$

前两个系数是分配标号的方案数，第三个是本质不同环的方案数，最后一个是所有连通块连成一棵树的方案数。令 $s_i\in(\mathbb P\cup\{1\})\setminus\{2\}$，则上述系数即为

$$n!\times\prod_{c=1}^n\frac1{(\sum_{i=1}^k[s_i=c])!}\times n^{k-2}\times \prod_{i=1}^k\frac{1}{1+[s_i>1]}$$

然后有两种做法。一种是枚举边双的个数，具体地，设 $G(z)=z+\frac{1}{2}\sum_{i\in \mathbb P\setminus\{2\}}z^i$，则答案即为

$$\sum_{k\ge 1}[z^n]G^k(z)\times \frac{n!}{k!}\times n^{k-2}$$

除以一个 $k!$ 是因为直接计算 $G(z)$ 的幂会导致一种 $s_1,s_2,\cdots,s_k$ 被计算 $\frac{k!}{\prod_{c=1}^n(\sum_{i=1}^k[s_i=c])!}$ 次，而分母部分刚好与每一种方案的贡献系数抵消了。再记 $H(z)=\sum_{k\ge 1}\frac{n^k}{k!}\times z^k$，则答案即为

$$\frac{n!}{n^2}\times [z^n]H(G(z))$$

可以使用 [noshi91 科技](https://www.luogu.com.cn/problem/P10249) 在 $O(n\log^2 n)$ 时间内计算。进一步，注意到 $H(z)=\exp(nz)-1$，我们完全可以直接 $\exp$ 的来着，可以在 $O(n\log n)$ 或 $O(n\log^2 n)$ 时间内计算。

另一种做法是将 $\frac{1}{\prod_{c=1}^n(\sum_{i=1}^k[s_i=c])!}$ 与 $n^k$ 揉进系数中做完全背包。具体地，答案即为

$$\begin{aligned}
&\frac{n!}{n^2}\times [z^n]\Big((\sum_{i\ge 0}\frac{n^iz^i}{i!})\times \prod_{p\in\mathbb P\setminus \{2\}}(\sum_{i\ge 0}\frac{n^iz^{pi}}{2^ii!})\Big)\\
=&~\frac{n!}{n^2}\times [z^n]\Big(\exp(nz)\times\prod_{p\in\mathbb P\setminus\{2\}}\exp(\frac{nz^p}{2})\Big)\\
=&~\frac{n!}{n^2}\times[z^n]\exp(nz+\sum_{p\in\mathbb P\setminus\{2\}}\frac{nz^p}{2})
\end{aligned}$$

得到了跟刚刚一样的结果，直接 $\exp$ 即可。

另外，似乎有人直接 $O(\dfrac{n^2}{\log n})$ DP 也过了，不懂 12s 放给谁的。

### Code

$O(n\log^2 n)\exp$：

```cpp
#include<bits/stdc++.h>
using namespace std;
using ui=unsigned int;
using ll=long long;
using ull=unsigned long long;
using i128=__int128;
using u128=__uint128_t;
using pii=pair<int,int>;
#define fi first
#define se second
constexpr int N=524290,mod=998244353,g=3,inv2=(mod+1)>>1;
inline ll add(ll x,ll y){return (x+=y)>=mod&&(x-=mod),x;}
inline ll Add(ll &x,ll y){return x=add(x,y);}
inline ll sub(ll x,ll y){return (x-=y)<0&&(x+=mod),x;}
inline ll Sub(ll &x,ll y){return x=sub(x,y);}
inline ll qpow(ll a,ll b){
	ll res=1;
	for(;b;b>>=1,a=a*a%mod)
		if(b&1)res=res*a%mod;
	return res;
}
int n;
ll fac[N],ifac[N];
inline ll inv(int n){return ifac[n]*fac[n-1]%mod;}
ll F[N],G[N];
int lim,ilim,rev[N];ll w[N];
void initNTT(int n){
	lim=1;
	while(lim<=n)lim<<=1;
	ilim=qpow(lim,mod-2);
	for(int i=1;i<lim;i++)
		rev[i]=(rev[i>>1]>>1)|((i&1)*(lim>>1));
	for(int i=1;i<lim;i<<=1){
		ll wn=qpow(g,(mod-1)/(i<<1)),cur=1;
		for(int j=0;j<i;j++,cur=cur*wn%mod)w[i|j]=cur;
	}
}
void NTT(ll *F,int type){
	for(int i=0;i<lim;i++)
		if(i<rev[i])
			swap(F[i],F[rev[i]]);
	for(int i=1;i<lim;i<<=1)
		for(int j=0;j<lim;j+=i<<1)
			for(int k=0;k<i;k++){
				ll x=F[j|k],y=w[i|k]*F[i|j|k]%mod;
				F[j|k]=add(x,y),F[i|j|k]=sub(x,y);
			}
	if(type==1)return;
	reverse(F+1,F+lim);
	for(int i=0;i<lim;i++)F[i]=F[i]*ilim%mod;
}
void muleq(ll *F,ll *G,int n,int m){ // F <- F*G
	static ll A[N],B[N];
	for(int i=0;i<=n;i++)A[i]=F[i];
	for(int i=0;i<=m;i++)B[i]=G[i];
	if(1ll*n*m<=1000){
		for(int i=0;i<=n+m;i++)F[i]=0;
		for(int i=0;i<=n;i++)
			for(int j=0;j<=m;j++)
				F[i+j]=(F[i+j]+A[i]*B[j])%mod;
	}
	else{
		initNTT(n+m);
		for(int i=n+1;i<lim;i++)A[i]=0;
		for(int i=m+1;i<lim;i++)B[i]=0;
		NTT(A,1),NTT(B,1);
		for(int i=0;i<lim;i++)A[i]=A[i]*B[i]%mod;
		NTT(A,-1);
		for(int i=0;i<=n+m;i++)F[i]=A[i];
	}
}
void exp(ll *F,ll *G,int l,int r){ // exp(F) -> G
	if(l==r){
		if(l)G[l]=G[l]*qpow(l,mod-2)%mod;
		else G[l]=1;
		return;
	}
	int mid=(l+r)>>1;
	static ll A[N],B[N];
	exp(F,G,l,mid);
	for(int i=0;i<=mid-l;i++)A[i]=G[i+l];
	for(int i=0;i<=r-l;i++)B[i]=F[i];
	muleq(A,B,mid-l,r-l);
	for(int i=mid+1;i<=r;i++)Add(G[i],A[i-l-1]);
	exp(F,G,mid+1,r);
}
void Exp(ll *F,ll *G,int n){
	static ll A[N];
	for(int i=1;i<=n;i++)A[i-1]=i*F[i]%mod;
	A[n]=0;
	exp(A,G,0,n);
}
int p[N],plen;bool v[N];
void sieve(int n){
	for(int i=2;i<=n;i++){
		if(!v[i])p[++plen]=i;
		for(int j=1;i*p[j]<=n;j++){
			v[i*p[j]]=1;
			if(i%p[j]==0)break;
		}
	}
	plen=max(plen,1);
	p[1]=1;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	sieve(n);
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	ifac[n]=qpow(fac[n],mod-2);
	for(int i=n;i>=1;i--)ifac[i-1]=ifac[i]*i%mod;
	for(int i=1;i<=plen;i++)F[p[i]]=1ll*n*(i==1?1:inv2)%mod;
	Exp(F,G,n);
	cout<<fac[n]*qpow(n,mod-3)%mod*G[n]%mod<<'\n';
	return 0;
}
```

---

## 作者：CarroT1212 (赞：2)

考虑嵌套环会发生什么。这要求小环长度为质数，大环长度也是质数。简单图环长不能为 $2$，所以所有环的长度都是奇数。当两个小环的长度都为奇数的时候，大环长度一定是偶数（加起来同时减去中间的链），完犊子了。所以不存在嵌套环。

所以题意顺利变成：多少个 $n$ 个点的点仙人掌满足所有环长度都为质数。（点仙人掌：每个点最多在一个环里）

扯到仙人掌计数咱就不困了啊。

> 要是沿用[荒漠计数](https://www.luogu.com.cn/problem/P5434)的主流做法然后特殊处理环大小的话，后期会出现一堆多项式复合，然后似乎就不得不用到新鲜出炉的 $O(n\log^2 n)$ 多项式复合科技……
>
> （官解还真是这个，ABC 你无敌了）

其实有一个比较亲民的做法。设 $f_n$ 为 $n$ 个有标号点组成的合法环数量，单点也当作环。有 $f_n=\begin{cases}1&n=1\\\frac{(n-1)!}{2}&n\ge 3 \text{ and }n\text{ is prime}\\0&\text{otherwise}\end{cases}$。

如果已知图上的所有连通块（此题为环）的大小 $s_1,s_2,\cdots,s_k\,(\sum s_i=n)$，那么连接它们形成一棵无根树状物的方案数为 $n^{k-2}\prod s_i$（[Cayley 定理经典推论](https://www.luogu.com.cn/problem/CF156D)），再算上环内方案数，那么环大小分别为 $s_1,s_2,\cdots,s_k$ 的合法图个数就是 $n^{k-2}\prod s_if_{s_i}$。

设 $ia_i$ 的 EGF 为 $F$（$F(x)=\sum\limits_{i=1}^k \frac{ia_i}{i!}x^i=nx+\sum\limits_{i=3,i\text{ is prime}}^k\frac{n}{2}x^i$），答案 EGF 为 $G$。

由多项式 exp 在 EGF 上的组合意义可知，$G=\frac{1}{n^2}\exp(nF)$。把 $G$ $n$ 次项系数乘个 $n!$ 丢出来即是答案。

NTT 单 $\log$ 做完了。

> 这个做法在荒漠计数里是不能直接用的，因为 $F$ 预处理和仙人掌点数挂钩。（不过魔改一下开头的 Cayley 公式也许有戏？）

```cpp
ll n,fac[N],vis[N];
void mian() {
	scanf("%lld",&n);
	fps F(n+1);
	F[1]=n,fac[0]=fac[1]=1;
	for (ll i=2;i<=n;i++) {
		fac[i]=fac[i-1]*i%P;
		if (!vis[i]) {
			if (i>=3) F[i]=n*qp(2)%P;
			for (ll j=i+i;j<=n;j+=i) vis[j]=1;
		}
	}
	F=F.exp();
	cout<<F[n]*fac[n]%P*qp(n*n%P)%P;
}
```

---

## 作者：analysis (赞：1)

### G - Prime Circuit

简单无向连通图说明环的长度大于 $2$，结合题目要求可以知道环长应为奇质数。

> 观察
>
> 环间不能有共顶点。

可以归纳证明这个结论。

那就是把若干个点或环连成树。

然后有一个经典结论：大小为 $a_1,a_2,\cdots,a_k$ 的连通块连成树的方案数为 $(\sum a_i)^{k-2}(\prod a_i)$。

就是要维护 $\sum\prod a_i$，考虑合法连通块（点与奇质数环）的 EGF 为 $G=1+\sum_{p \geq 3,p\text{ is prime}} \frac{(p-1)!}{2}\frac{x^p}{p!}$。把 $a_i$ 放进去维护就变成了 $G=1+\sum_{p \geq 3,p\text{ is prime}} \frac{x^p}{2}$。

于是求的就是 $n![x^n]\sum_i \frac{G^in^{i-2}}{i!}=n!n^{-2}[x^n]\exp(nG)$，直接做就好了，$O(\mathsf{M}(n))$。

[参考实现](https://atcoder.jp/contests/abc387/submissions/61407072)

---

另一个解法，快进到得到观察。

考虑为图指定一个根（答案乘上 $n$），设其 EGF 为 $F$。

考虑每次创建一个根连接若干连通块，多个根可能形成一个环，然后再指定一个新的根，于是有：
$$
G(x)=1+\sum_{p \geq 3,p\text{ is prime}} p \times\frac{x^p}{2p}=1+\sum_{p \geq 3,p\text{ is prime}} \frac{x^p}{2}\\
F(x)=G(x\exp{F(x)})
$$
考虑 $H(x)=x\exp{F(x)}$ 及其复合逆 $H(h(x))=x$，有：
$$
F(x)=G(x\exp{F(x)})\\
H(x)=x\exp{F(x)}=x\exp{G(x\exp{F(x)})}=x\exp{G(H(x))}\\
x=h(x)\exp{G(x)} \Rightarrow h(x)=\frac{x}{\exp{G(x)}}\\
$$
$n \geq 1$，直接拉反就好了：
$$
n![x^n]F(x)=n![x^n]G(H(x))=n!n^{-1}[x^{n-1}]G'(\frac{x}{h(x)})^n\\
=n!n^{-1}[x^{n-1}]G'(\exp{G(x)})^n
$$
还要注意无根，所以把 $n$ 除掉，答案应该是 $n!n^{-2}[x^{n-1}]G'(\exp{G(x)})^n$，$O(\mathsf{M}(n))$。

[参考史现](https://atcoder.jp/contests/abc387/submissions/61417640)

当然，如果我们再推几步：
$$
n!n^{-2}[x^{n-1}]G'(x)(\exp{G(x)})^n\\\
=n!n^{-3}[x^{n-1}]nG'(x)(\exp{nG(x)})\\\
=n!n^{-3}[x^{n-1}] (\exp{nG(x)})'\\\
=n!n^{-3}n[x^{n}]\exp{nG(x)}\\\
=n!n^{-2}[x^{n}]\exp{nG(x)}
$$
和第一个是一样的。

---

## 作者：zhenjianuo2025 (赞：1)

考虑如果有两个彼此相交的质数长度环，那么它们的轮廓将会组成一个更大的长度为偶数的环，因此不符合题意。

所以合法的结构形成一棵仙人掌。假设有 $m$ 个环或者单点，大小分别是 $c_1,c_2,\ldots,c_m$，它们将会连成一棵树，方案数是 $n^{m-2}\prod c_i$（根据 Prufer 定理推论）。

设 $f_i$ 表示 $i$ 个有标号点组成一棵树的 **系数和**，那么枚举 $1$ 号点所在的环长，可以得到转移 $f_i=n\sum_{j=1}^i [j=1\operatorname{or}j\in P]j\binom{i-1}{j-1}\frac12(j-1)!f_{i-j}$。答案是 $n^{-2}f_n$。用最朴素的 $O\left(\frac{n^2}{\ln n}\right)$ 暴力，注意以下细节就可以 3600ms 冲过去。

- 在 $j$ 的循环外面预处理好只和 $i$ 有关的系数；
- 算完 $f_{i-j}$ 后随即把 $(i-j)!$ 乘进 $f_{i-j}$ 里面；
- 用一个 `__int128` 变量存下 $f_i$，不用时时取模，留到最后算完再取模。

---

## 作者：ReTF (赞：0)

快进到点仙人掌，环长奇质数。

假设有 $k$ 个环或者孤点，第 $i$ 个有 $s_i$ 个点，连 $k-1$ 条边得到的连通点仙人掌有 $\displaystyle n^{k-2}\prod_{i=1}^k s_i=n^{-2}\prod_{i=1}^k ns_i$ 个。这个可以 prufer 序列来证。

然后就是对每个大小算选出 $k$ 个这个大小的环或者孤点的方案数，最后卷起来就行。

如果这个大小 $v=1$，有 GF：

$$F_v(x)=\sum_{k\ge 0}\dfrac{n^kx^{vk}}{k!}$$

否则有 GF：

$$F_v(x)=\sum_{k\ge 0}\dfrac{n^kx^{vk}}{2^kk!}$$

然后我们需要对于所有 $v$ 把 $F_v(x)$ 都卷起来，最后得到函数 $F(x)$，$n=i$ 的答案就是 $[x^i]F(x)i^{-2}i!$。

直接卷就爆！可以转化成 $\ln$ 相加最后再 $\exp$ 回去，根据经典结论 $\ln$ 完得到的多项式只有所有 $x^{vk}$ 的系数可能不为 $0$，所以可以**将所有的 $x^v$ 替换成 $x$ 之后**暴力 $\ln$，时间复杂度 $\log n\log\log n$。

刚才这个做法太弱智了，考虑去掉 $\ln$ 直接推出 $\ln$ 完长什么样，设为 $G(x)$，以 $v\neq 1$ 为例，注意已经将所有的 $x^v$ 替换成了 $x$：

$$\begin{aligned}
\ln F_v(x)&=G(x)\\
\dfrac{F'_v(x)}{F_v(x)}&=G'(x)\\
\dfrac{\displaystyle\sum_{k\ge 0}\dfrac{n^{k+1}x^{k}}{2^{k+1}k!}}{\displaystyle\sum_{k\ge 0}\dfrac{n^kx^{k}}{2^kk!}}&=G'(x)\\
G'(x)&=\dfrac{n}{2}\\
G(x)&=\dfrac{n}{2}x
\end{aligned}$$

$v=1$ 可以类似的去推，推出来 $G(x)=nx$。

然后就 $O(1)$ 了，总复杂度是单个 $\exp$ 一个 $\log$。

---

## 作者：_abcd_ (赞：0)

## [[ABC387G] Prime Circuit](https://atcoder.jp/contests/abc387/tasks/abc387_g)

我们注意到一个非常重要的性质：所有 $ > 2 $ 的偶数都不是质数！

因此，假设图中有两个环，且他们有相同的点，那么将他们异或一下就能形成新的环。显然，在原来的两个环和新环中，至少有一个环的长度是偶数，这是不行的。因此图必须是一个仙人掌。

那题目就转换成：有标号仙人掌计数，且所有环的长度都是质数。如果所有环都已经确定下来了，那么就需要连若干条边将他们串成一个仙人掌。根据 [$ \rm prufer $ 序列](https://oi-wiki.org/graph/prufer/#%E5%9B%BE%E8%BF%9E%E9%80%9A%E6%96%B9%E6%A1%88%E6%95%B0)，假设有 $ k $ 个环，且第 $ i $ 个环的长度为 $ s_i $，则一共有 $ n^{k-2} \prod\limits_{i=1}^k s_i = n^{-2} \prod\limits_{i=1}^k n s_i $ 种串法。这就非常好算了！对于一个大小为 $ m $ 的环，他的贡献就是 $ nm $，而他的方案数是 $ \frac{(m-1)!}{2} $，当 $ m=1 $ 时方案数为 $ 1 $。只需要把这个 $ \rm EGF $ 做一个 $ \exp $ 就行了。复杂度 $ O(n \log n) $。

---

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pn putchar('\n')
#define mset(a,x) memset(a,x,sizeof a)
#define mcpy(a,b) memcpy(a,b,sizeof a)
#define all(a) a.begin(),a.end()
#define fls() fflush(stdout)
#define mod 998244353
#define int ll
#define maxn 250005
#define i2 499122177
#define N 524288
using namespace std;
int re()
{
    int x=0;
    bool t=1;
    char ch=getchar();
    while(ch>'9'||ch<'0')
        t=ch=='-'?0:t,ch=getchar();
    while(ch>='0'&&ch<='9')
        x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return t?x:-x;
}
int ksm(int x,int y)
{
    int ret=1;
    while(y)
    {
        if(y&1)ret=ret*x%mod;
        x=x*x%mod,y>>=1;
    }
    return ret;
}
void dq(int &x)
{
    if(x>=mod)x-=mod;
    if(x<0)x+=mod;
}
int n;
bool isnp[maxn];
vector<int>pr;
int phi[maxn],mu[maxn];
int jc[maxn],inv[maxn];
void zh_init()
{
    jc[0]=1;
    for(int i=1;i<=n;i++)
        jc[i]=jc[i-1]*i%mod;
    inv[n]=ksm(jc[n],mod-2);
    for(int i=n;i;i--)
        inv[i-1]=inv[i]*i%mod;
}
int A(int x,int y)
{
    if(x<y)return 0;
    return jc[x]*inv[x-y]%mod;
}
int C(int x,int y)
{
    return A(x,y)*inv[y]%mod;
}
void prime_init()
{
    mu[1]=phi[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(!isnp[i])
        {
            pr.push_back(i);
            phi[i]=i-1;
            mu[i]=-1;
        }
        for(int j:pr)
        {
            int x=i*j;
            if(x>n)
                break;
            isnp[x]=1;
            if(i%j==0)
            {
                mu[x]=0;
                phi[x]=phi[i]*j;
                break;
            }
            mu[x]=-mu[i];
            phi[x]=phi[i]*(j-1);
        }
    }
}
namespace polynomial
{
    int gn[N<<1],gi[N<<1],rev[N<<1],iv[N+1];
    void poly_init()
    {
        for(int i=1;i<=N;i<<=1)
        {
            gn[i]=ksm(3,(mod-1)/i);
            gi[i]=ksm(gn[i],i-1);
        }
        gn[0]=gi[0]=1;
        for(int i=1;i<N<<1;i++)
        {
            int j=1<<__lg(i);
            gn[i]=gn[i-1]*gn[j]%mod;
            gi[i]=gi[i-1]*gi[j]%mod;
        }
        for(int i=2;i<=N;i<<=1)
        {
            for(int j=i;j<i<<1;j++)
            {
                rev[j]=rev[j-i>>1|i]>>1;
                if(j&1)
                    rev[j]|=i>>1;
            }
        }
        iv[0]=iv[1]=1;
        for(int i=2;i<=N;i++)
            iv[i]=(mod-mod/i)*iv[mod%i]%mod;
    }
    int getn(int n)
    {
        return n==1?1:1<<__lg(n-1)+1;
    }
    struct Poly
    {
        int a[N];
        int& operator [] (int x)
        {
            return a[x];
        }
        void print(int n,int l=0)
        {
            for(int i=l;i<l+n;i++)
                printf("%lld ",a[i]);
            pn;
        }
        void cpy(Poly& t,int n,int l=0)
        {
            for(int i=l;i<l+n;i++)
                a[i]=t[i];
        }
        void clr(int n,int l=0)
        {
            for(int i=l;i<l+n;i++)
                a[i]=0;
        }
        void NTT(int n,int ty=1)
        {
            for(int i=0,*t=rev+n;i<n;i++,t++)
            {
                if(*t<i)
                    swap(a[i],a[*t]);
            }
            for(int i=1;i<n;i<<=1)
            {
                for(int j=0;j<n;j+=i<<1)
                {
                    int *x=(ty==1?gn:gi)+(i<<1)-1;
                    for(int k=j;k<j+i;k++,x++)
                    {
                        int l=a[k],r=*x*a[k+i]%mod;
                        a[k]=l+r,a[k+i]=l-r;
                        a[k]=a[k]>=mod?a[k]-mod:a[k];
                        a[k+i]=a[k+i]<0?a[k+i]+mod:a[k+i];
                    }
                }
            }
            if(ty==-1)
            {
                for(int i=0;i<n;i++)
                    a[i]=a[i]*iv[n]%mod;
            }
        }
        void mul(Poly& F,Poly& G,int n)
        {
            n=getn(n);
            F.NTT(n);
            G.NTT(n);
            for(int i=0;i<n;i++)
                a[i]=F[i]*G[i]%mod;
            NTT(n,-1);
        }
        void bni(Poly& t,int n)
        {
            if(n==1)
            {
                a[0]=ksm(t[0],mod-2);
                return;
            }
            clr(n>>1,n>>1);
            static Poly tni1,tni2;
            tni1.cpy(*this,n);
            tni2.cpy(t,n);
            tni1.mul(tni1,tni2,n);
            tni1.clr(n>>1);
            tni2.cpy(*this,n);
            tni1.mul(tni1,tni2,n);
            for(int i=n>>1;i<n;i++)
                dq(a[i]=-tni1[i]);
        }
        void ni(int n)
        {
            static Poly tni0;
            n=getn(n);
            tni0.cpy(*this,n);
            for(int i=1;i<=n;i<<=1)
                bni(tni0,i);
        }
        void dao(int n)
        {
            for(int i=1;i<n;i++)
                a[i-1]=i*a[i]%mod;
            a[n-1]=0;
        }
        void jf(int n)
        {
            for(int i=n-1;i;i--)
                a[i]=a[i-1]*iv[i]%mod;
            a[0]=0;
        }
        void ln(int n)
        {
            static Poly tln;
            n=getn(n);
            tln.cpy(*this,n<<1);
            tln.dao(n);
            ni(n);
            mul(*this,tln,n<<1);
            jf(n);
        }
        void exp(int n)
        {
            n=getn(n);
            static Poly texp0;
            texp0.cpy(*this,n);
            a[0]=1;
            a[1]=0;
            for(int len=2;len<=n;len<<=1)
            {
                static Poly texp1,texp2,texp3;
                texp1.bni(*this,len>>1);
                texp1.bni(*this,len);
                texp2.cpy(texp1,len);
                texp3.cpy(*this,len);
                texp3.dao(len);
                texp3.clr(len,len);
                texp2.clr(len,len);
                texp2.mul(texp2,texp3,len<<1);
                texp2.jf(len);
                dq(texp2[0]=1-texp2[0]);
                for(int i=1;i<len;i++)
                    dq(texp2[i]=texp0[i]-texp2[i]);
                clr(len,len);
                mul(*this,texp2,len<<1);
                clr(len,len);
                texp1.clr(len,len);
            }
        }
        void mi(int n,int m)
        {
            n=getn(n);
            ln(n);
            for(int i=0;i<n;i++)
                (a[i]*=m)%=mod;
            exp(n);
        }
    }F;
}
using namespace polynomial;
signed main()
{
    poly_init();
    n=re();
    prime_init();
    zh_init();
    F[1]=n;
    for(int i=3;i<=n;i++)
    {
        if(!isnp[i])
            F[i]=i2*n%mod;
    }
    F.exp(n+1);
    printf("%lld\n",F[n]*jc[n]%mod*ksm(n*n%mod,mod-2)%mod);
    return 0;
}
```

---

