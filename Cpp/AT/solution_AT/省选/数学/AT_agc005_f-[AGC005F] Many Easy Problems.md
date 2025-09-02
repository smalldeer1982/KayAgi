# [AGC005F] Many Easy Problems

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc005/tasks/agc005_f

高橋君はある日青木君から以下の様な問題を貰いました。

- $ N $ 頂点の木と、整数 $ K $ が与えられる。木の頂点は $ 1,2,...,N $ と番号がついているものとし、辺は $ (a_i,\ b_i) $ で表す。
- 頂点の集合 $ S $ について $ f(S) $ を、$ S $ をすべて含む部分木の頂点数の最小値とする
- 木から $ K $ 個の頂点を選ぶ方法は $ _NC_K $ 通りあるが、それぞれについて選んだ頂点を $ S $ とし、 $ f(S) $ の総和を求める
- 答えは大きくなることがあるので、$ 924844033 $(素数) で割ったあまりを出力する

高橋君にとってこの問題は簡単すぎました。なので $ K\ =\ 1,2,...,N $ 全てについてこの問題を解くことにしました。

## 说明/提示

### 制約

- $ 2\ ≦\ N\ ≦\ 200,000 $
- $ 1\ ≦\ a_i,\ b_i\ ≦\ N $
- 与えられるグラフは木である

### Sample Explanation 1

!\[\](https://atcoder.jp/img/agc005/44e2fd5d5e0fe66d1d238ee502639e4e.png) 上図は、$ K=2 $ の場合を図示している。ピンク色の頂点が選んだ頂点で、赤く囲われたのが頂点数最小の部分木である。

## 样例 #1

### 输入

```
3
1 2
2 3```

### 输出

```
3
7
3```

## 样例 #2

### 输入

```
4
1 2
1 3
1 4```

### 输出

```
4
15
13
4```

## 样例 #3

### 输入

```
7
1 2
2 3
2 4
4 5
4 6
6 7```

### 输出

```
7
67
150
179
122
45
7```

# 题解

## 作者：hwk0518 (赞：29)

这道题的思路是比较巧妙的。

若正向考虑，要求出每个大小为k的点集的贡献，复杂度势必是指数级别的。所以我们反向考虑问题，考虑每个点对$ans_k$的贡献。

我们知道，大小为k的点集有$C(n,k)$个。能使一个点i不对$ans_k$产生贡献的点集当且仅当以下两种情况之一成立：

(1)这个集合中所有点都在以i的某个儿子为根的子树中；

(2)这个集合中所有点都不在以i为根的子树中。

于是我们设$siz_x$表示以x为根的子树大小，设$contrib_{i,j}$表示i对$ans_j$的贡献。则有：

$contrib_{i,j}=C(n,j)-(\sum_{v=son_i} C(v,j))-C(n-siz_i,j)$

$ans_j=\sum_{i=1 \to n} contrib_{i,j}$

可以发现，直接暴力计算是$O(n^2)$的。

还是运用正难则反的思想，设$cnt_k$表示有多少个点i满足$siz_i=k$，特别地，设$siz_{i+n}=n-siz_{i}$。

于是$ans_j=C(n,j)*n-\sum_{i=j \to n} cnt_i*C(i,j)$

展开组合数，得到：

$ans_j=C(n,j)*n-\sum_{i=j \to n} cnt_i*\frac{i!}{j!(i-j)!}$

$ans_j=C(n,j)*n-\frac{1}{j!}\sum_{i=j \to n} cnt_i*\frac{i!}{(i-j)!}$

设$a_i=cnt_i*i!$，$b_i=\frac{1}{i!}$，

则$ans_j=C(n,j)*n-\frac{1}{j!}\sum_{i=j \to n}a_ib_{i-j}$

现在的主要问题是如何加速计算$tmp_j=\sum_{i=j \to n}a_ib_{i-j}$

设$brev_i=b_{n-i}$

构造生成函数$A=a_0x^0+...+a_nx^n$

$B=brev_0x^0+...+brev_nx^n$

设C=AB，则$C_{j+n}$是

$\sum_{i=j \to n}a_ibrev_{n+j-i}$
=$\sum_{i=j \to n}a_ib_{i-j}$，刚好就是$tmp_i$。

用NTT卷积即可。

时间复杂度：$O(nlogn)$

**划重点！本题的原根是5！不是3！**

这是本人用markdown写的第一篇题解。看在努力背诵markdown公式的份上，给个赞啦【可怜】，谢谢！

代码：

```

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<algorithm>
#include<math.h>
using namespace std;

const int N=2e5+5;
const int M=5e5+5;
const int T=1e6+5;
const int mod=924844033;
const int sqr=5;
const int sqrinv=554906420;

int n,u,v,siz[N],limit,lg;
int E,ot[M],ne[M],g[N];
int fac[N],inv[N],infac[N];
int a[T],b[T],r[T];

int F_p(int x,int y)
{
	int bas=x,ret=1;
	while(y)
	{
		if(y&1) ret=1LL*ret*bas%mod;
		bas=1LL*bas*bas%mod;
		y>>=1;
	}
	return ret;
}

void add(int u,int v)
{
	ot[++E]=v;
	ne[E]=g[u];
	g[u]=E;
}

void init()
{
	int i;
	scanf("%d",&n);
	for(i=1;i<n;++i)
	{
		scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}
}

void dfs(int x,int fath)
{
	siz[x]=1;
	int p,to;
	for(p=g[x];p;p=ne[p])
	{
		to=ot[p];
		if(to==fath) continue;
		dfs(to,x);
		siz[x]+=siz[to];
		++a[siz[to]];
	}
	++a[n-siz[x]];
}

int solve_complex(int x,int tp)
{
	if(~tp) return F_p(sqr,x);
	else return F_p(sqrinv,x);
}

void DFT(int *A,int tp)
{
	int i;
	for(i=0;i<limit;++i)
		if(i<r[i])
			swap(A[i],A[r[i]]);
	
	int len,j,k;
	for(len=1;len<limit;len<<=1)
	{
		int wn=solve_complex((mod-1)/(2*len),tp);
		for(j=0;j<limit;j+=len<<1)
		{
			int w=1;
			for(k=0;k<len;++k,w=1LL*w*wn%mod)
			{
				int x=A[j+k];
				int y=1LL*w*A[j+k+len]%mod;
				A[j+k]=x+y,A[j+k+len]=x-y;
				if(A[j+k]>=mod) A[j+k]-=mod;
				if(A[j+k+len]<0) A[j+k+len]+=mod;
			}
		}
	}
}

void prework()
{
	int i;dfs(1,0);
	fac[0]=1;for(i=1;i<=n;++i) fac[i]=1LL*fac[i-1]*i%mod;
	inv[1]=1;for(i=2;i<=n;++i) inv[i]=1LL*inv[mod%i]*(mod-mod/i)%mod;
	infac[0]=1;for(i=1;i<=n;++i) infac[i]=1LL*infac[i-1]*inv[i]%mod;
}

void work()
{
	int i;a[0]=0;
	for(i=0;i<=n;++i) a[i]=1LL*a[i]*fac[i]%mod;
	for(i=0;i<=n;++i) b[i]=infac[n-i];
	
	limit=1;
	while(limit<=2*n) limit<<=1,++lg;
	for(i=1;i<limit;++i) r[i]=(r[i>>1]>>1)|((i&1)<<(lg-1));
	
	DFT(a,1),DFT(b,1);
	for(i=0;i<limit;++i) a[i]=1LL*a[i]*b[i]%mod;
	DFT(a,-1);
	
	int INV=F_p(limit,mod-2);
	for(i=1;i<=n;++i) a[i+n]=1LL*a[i+n]*INV%mod*infac[i]%mod;
	for(i=1;i<=n;++i) a[i]=1LL*fac[n]*infac[i]%mod*infac[n-i]%mod*n%mod;
	for(i=1;i<=n;++i)
	{
		a[i]-=a[i+n];
		if(a[i]<0) a[i]+=mod;
	}
	for(i=1;i<=n;++i) printf("%d\n",a[i]);
}

int main()
{
	init();prework();work();
	return 0;
}

```

---

## 作者：Arghariza (赞：7)

- 题意：

给定一棵无根树，定义 $f(i)$，对于所有大小为 $i$ 的点集，求出能够包含它的最小连通块大小之和。对于 $i=1 \to n$ 的所有 $i$，求出 $f(i)$。

$N \le2\times 10^5$。

- 做法：

难以对点集的所有情况进行统计，转而计算每个点 $u$ 对答案的贡献。

从反面考虑，计算 $u$ 不被放进点集的方案数。不难发现，当且仅当**点集内所有点都在 $u$ 某个儿子的子树内或不在 $u$ 的子树内**时，$u$ 没有被放进点集。这样的方案数为 $\sum\limits_{v\in son(u)}\dbinom{sz_v}{i}$。（注意：这里的 $son,sz$ 指 $u$ 为整棵树的根时的情况，也就是说其他情况下 $u$ 的父亲在此时也有可能是 $u$ 的儿子，当初理解这一步用了很久）。

因为总方案数为在 $n$ 个点中选 $i$ 个，于是 $u$ 的总贡献为 $\dbinom{n}{i}-\sum\limits_{v\in son(u)}\dbinom{sz_v}{i}$,得到 $f(i)=\sum\limits_{u}\left(\dbinom{n}{i}-\sum\limits_{v\in son(u)}\dbinom{sz_v}{i}\right)=n\dbinom{n}{i}-\sum\limits_{u}\sum\limits_{v\in son(u)}\dbinom{sz_v}{i}$。

枚举 $sz_v$，记 $c_i$ 为子树大小为 $i$ 的方案数（同前面的 $son,sz$，这里说的子树**同样计算 $u$ 以上不属于 $u$ 子树的部分**），$f(i)=n\dbinom{n}{i}-\sum\limits_{k=i}^{n}c_k\dbinom{k}{i}$。

把组合数拆开：

$$\begin{aligned}f(i)&=n\dbinom{n}{i}-\sum\limits_{k=i}^{n}c_k\dbinom{k}{i}\\&=n\dbinom{n}{i}-\sum\limits_{k=i}^{n}c_k\dfrac{k!}{i!(k-i)!}\\&=n\dbinom{n}{i}-\dfrac{1}{i!}\sum\limits_{k=0}^{n-i}\dfrac{1}{k!}\times (k+i)!\times c_{k+i}\end{aligned}$$

令 $g(x)=\dfrac{1}{x!},f(x)=(n-x)!c_{n-x}$：

$$\begin{aligned}f(i)&=n\dbinom{n}{i}-\dfrac{1}{i!}\sum\limits_{k=0}^{n-i}\dfrac{1}{k!}\times (k+i)!\times c_{k+i}\\&=n\dbinom{n}{i}-\dfrac{1}{i!}\sum\limits_{k=0}^{n-i}g(k)f(n-i-k)\end{aligned}$$

右边就变成了一个加法卷积的形式，预处理阶乘，$\mathtt{NTT}$ 计算即可。

```cpp
#include <bits/stdc++.h>
#define int long long
namespace mystd {
    inline int read() {
        char c = getchar();
        int x = 0, f = 1;
        while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
        while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + c - '0', c = getchar();
        return x * f;
    }
    inline void write(int x) {
        if (x < 0) x = ~(x - 1), putchar('-');
        if (x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
}
using namespace std;
using namespace mystd;

const int gn = 5;
const int gi = 554906420;
const int mod = 924844033;
const int maxn = 2e5 + 200;
struct edge { int to, nxt; } e[maxn << 1];
int n, tot, sz[maxn], cnt[maxn], head[maxn], fac[maxn], inv[maxn], ifac[maxn];
int len, lim, liv, f[maxn << 2], g[maxn << 2], rev[maxn << 2];

void add_edge(int u, int v) {
    e[++tot] = (edge) { v, head[u] };
    head[u] = tot;
}

void dfs(int u, int fa) {
    sz[u] = 1;
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (v == fa) continue;
        dfs(v, u), sz[u] += sz[v], cnt[sz[v]]++;
    }
    cnt[n - sz[u]]++;
}

int C(int n, int m) { return fac[n] * ifac[m] % mod * ifac[n - m] % mod; }
int ksm(int p, int q) {
    int res = 1;
    while (q) {
        if (q & 1) res = res * p % mod;
        p = p * p % mod;
        q >>= 1;
    }
    return res;
}

void ntt(int *f, int flg) {
    for (int i = 0; i < lim; i++) if (i < rev[i]) swap(f[i], f[rev[i]]);
    for (int i = 1; i < lim; i <<= 1) {
        int tg = ksm(flg ? gn : gi, (mod - 1) / (i * 2));
        for (int j = 0, w = 1; j < lim; j += i * 2, w = 1) {
            for (int k = 0; k < i; k++, w = w * tg % mod) {
                int x = f[j + k], y = f[i + j + k] * w % mod;
                f[j + k] = (x + y) % mod, f[i + j + k] = (x - y + mod) % mod;
            }
        }
    }
}

signed main() {
    n = read();
    for (int i = 1, u, v; i <= n - 1; i++) {
        u = read(), v = read();
        add_edge(u, v), add_edge(v, u);
    }
    dfs(1, 0);
    fac[0] = inv[1] = ifac[0] = 1;
    for (int i = 2; i <= n; i++) inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod, ifac[i] = ifac[i - 1] * inv[i] % mod;
    for (int i = 1; i <= n; i++) f[n - i] = cnt[i] * fac[i] % mod;
    for (int i = 0; i <= n; i++) g[i] = ifac[i];
    for (lim = 1; lim <= 2 * n; lim <<= 1, len++) {}
    liv = ksm(lim, mod - 2);
    for (int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
    ntt(f, 1), ntt(g, 1);
    for (int i = 0; i < lim; i++) f[i] = f[i] * g[i] % mod;
    ntt(f, 0), reverse(f, f + n + 1);
    for (int i = 1; i <= n; i++) write(((n * C(n, i) % mod - ifac[i] * f[i] % mod * liv % mod) + mod) % mod), puts("");
    return 0;
}
```

---

## 作者：K8He (赞：5)

[AGC005F](https://www.luogu.com.cn/problem/AT_agc005_f)

第一步转化是直接求 $f(k)$ 比较困难，于是分别计算每个点的贡献。

考虑计算点 $u$ 对 $f(k)$ 有何贡献，直接讨论跨过它的点对贡献比较麻烦，于是使用容斥：

$$
\dbinom{n}{k} - \dbinom{n - size_u}{k} - \sum_{v\text{ is }u\text{'s son}}\dbinom{size_v}{k}
$$

得到了 $O(n^2)$ 的算法，对于优化不难想到从整体所有点上考虑这几项的贡献：对于$\dbinom{n}{k}$，每个点的值都一样，贡献 $n$ 遍；对于 $-\sum\dbinom{size_v}{k}$，除根以外的每个点都当过恰好一次儿子贡献一次，可以直接求和：

$$
f(k) = n\dbinom{n}{k} - \left(\sum_{u\neq root}\dbinom{size_u}{k} + \dbinom{n - size_u}{k}\right)
$$

依旧是一个不好处理的形式。考虑用一个桶 $cnt_i$ 存下有多少个 $size_u=i$ 和 $n - size_u=i$，相同的值只统计一次。（感觉上可能把组合数部分转化成仅与下标相关更有利于拆分成卷积形式）

$$
\begin{aligned}
f(k)
&= n\dbinom{n}{k} - \sum_{i=k}^{n}cnt_i\dbinom{i}{k}\\
&= n\dbinom{n}{k} - \sum_{i=1k}^{n}cnt_i\frac{i!}{k!(i - k)!}\\
&= n\dbinom{n}{k} - \frac{1}{k!}\sum_{i=k}^{n}cnt_ii!\frac{1}{(i - k)!}\\
\end{aligned}
$$

发现作为复杂度瓶颈的后者转化成了一个差卷积的形式。构造多项式 $A[i] = cnt_{n - i}(n - i)!$，$B[i] = \dfrac{1}{i!}$，$F(z) = (A\times B)(z)$。带回原式：

$$

\begin{aligned}
f(k)
&= n\dbinom{n}{k} - \frac{1}{k!}\sum_{i = k}^{n}A[n - i]B[i - k]\\
&= n\dbinom{n}{k} - \frac{1}{k!}\sum_{i = 0}^{n - k}A[n - k - i]B[i]\\
&= n\dbinom{n}{k} - \frac{1}{k!}F[n - k]\\
\end{aligned}
$$

$F(z)$ 使用 NTT 优化，做到了 $O(n\log n)$ 的时间复杂度。

注意到模数的原根不是 $3$，不过可以使用比较通用的原根 $114514$。

[AtCoder Submission .](https://atcoder.jp/contests/agc005/submissions/51409511)

---

## 作者：Fading (赞：2)

神奇题目，没想到算贡献的我瑟瑟发抖...

发现这种组合题看别人的推导过程很轻松，但考场上却很难想到...

------------

首先我们可以这么做：

#### 对于要求的每一个$f(k)$，枚举所有点对它的贡献。

对于一个点$i$，首先我们知道，大小为$k$的点集不包含$i$点的充要条件是：

所有$k$个点都在**以$i$的儿子为根**的子树内（**以$i$为树根**）。

然后我们容斥一下，就可以推出式子：

其中$\text{size}$表示子树大小（以$i$为根的情况下）。

$$f(k)=\sum_{i=1}^n(C_n^k-\sum_{u\in \text{son}_i}C_{\text{size}_u}^k)$$

前面的东西很好求，我们看看后面的，设

$$g(k)=\sum_{i=1}^n\sum_{u\in \text{son}_i}C_{\text{size}_u}^k$$

现在比较麻烦，这个东西非常的烦人，因为有$2$个$\sum$。我们考虑使用套路：

设$\lambda(j)$为

对于$1\sim i$中**所有的$u$**，它所有儿子$v$，$\text{size}_v=j$的方案数。

$$\therefore g(k)=\sum_{j=1}^{n}C_j^k\lambda(j)$$

$$\therefore g(k)=\sum_{j=k}^{n}\frac {j!}{k!(j-k)!}\lambda(j)$$

$$\therefore g(k)k!=\sum_{j=k}^{n}{\lambda(j)j!}\frac 1{(j-k)!}$$

很好，得到了我们喜闻乐见的卷积形式。

这道题就做完了。

翻转系数后求卷积即可。

------------

关于$\lambda$怎么求？换根 dp 一下不就好了？

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ljc 924844033
using namespace std;
#ifdef Fading
#define gc getchar
#endif
#ifndef Fading
inline char gc(){
    static char now[1<<16],*S,*T;
    if (T==S){T=(S=now)+fread(now,1,1<<16,stdin);if (T==S) return EOF;}
    return *S++;
}
#endif
inline ll read(){
    register ll x=0,f=1;char ch=gc();
    while (!isdigit(ch)){if(ch=='-')f=-1;ch=gc();}
    while (isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=gc();}
    return (f==1)?x:-x;
}
struct edge{
    int to,nxt;
}e[400001];
ll sz[400001],tot,head[2200001];
inline void made(int from,int to){
    e[++tot].to=to;e[tot].nxt=head[from];head[from]=tot;
}
ll n,w[2200001],C[1000001],inv[1000001],fac[1000001],r[2200001],f[2200001],g[2200001];
inline ll fast_pow(ll a,ll b,ll p){
    ll t=1;a%=p;
    while (b){
        if (b&1LL) t=t*a%p;
        b>>=1LL;a=a*a%p;
    }
    return t;
}
inline void NTT(ll *f,ll lim,ll id){
    w[0]=1;
    for (int i=0;i<lim;i++){
        if (i>r[i]) swap(f[i],f[r[i]]);
    }
    for (int len=1;len<lim;len<<=1){
        ll gen=fast_pow(5,(ljc-1)/(len<<1)*id+ljc-1,ljc);
        for (int i=1;i<len;i++) w[i]=w[i-1]*gen%ljc;
        for (int i=0;i<lim;i+=len<<1){
            ll *f1=f+i,*f2=f1+len;
            for (int j=0;j<len;j++){
                ll x=f1[j],y=f2[j]*w[j]%ljc;
                f1[j]=(x+y)%ljc;
                f2[j]=(x-y+ljc)%ljc;
            }
        }
    }
    if (id==1) return;
    ll INV=fast_pow(lim,ljc-2,ljc);
    for (int i=0;i<lim;i++) f[i]=f[i]*INV%ljc;
}
void dfs(int u,int fa){
    sz[u]=1;
    for (int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;
        if (v==fa) continue;
        dfs(v,u);sz[u]+=sz[v];g[sz[v]]++;
    }
    g[n-sz[u]]++;
}
inline ll getC(ll n,ll m){
    return fac[n]*inv[m]%ljc*inv[n-m]%ljc;
}
signed main(){
    n=read();
    fac[0]=inv[0]=inv[1]=1;
    for (ll i=1;i<=n;i++) fac[i]=fac[i-1]*i%ljc;
    for (ll i=2;i<=n;i++) inv[i]=(ljc-(ljc/i)*inv[ljc%i]%ljc)%ljc;
    for (ll i=1;i<=n;i++) inv[i]=inv[i-1]*inv[i]%ljc;
    for (int i=1;i<n;i++){
    	int x=read(),y=read();
    	made(x,y);made(y,x);
    }
    dfs(1,0);
    g[0]=0;
    for (int i=1;i<=n;i++) C[i]=n*getC(n,i)%ljc;
    for (int i=1;i<=n;i++) g[i]=g[i]*fac[i]%ljc;
    for (int i=0;i<=n;i++) f[i]=inv[i];
    reverse(g,g+1+n);
    ll lim=1,len=0;
    n++;
    while (lim<=(n<<1)) lim<<=1,len++;
    for (int i=0;i<lim;i++) r[i]=(r[i>>1]>>1)|((i&1)<<(len-1));
    NTT(f,lim,1);NTT(g,lim,1);
    for (int i=0;i<lim;i++) f[i]=f[i]*g[i]%ljc;
    NTT(f,lim,-1);
    n--;
    for (int i=1;i<=n;i++) f[i]=f[i]*inv[n-i]%ljc;
    for (int i=1;i<=n;i++) printf("%lld\n",(C[i]-f[n-i]+ljc)%ljc);
    return 0;
}


```

顺手$rank2$（逃

---

## 作者：SnowTrace (赞：1)

感觉是很套路的题啊，但是我又不会。

看到这样一个东西想了一下直接考虑点集不好做，那么我们考虑每个点的贡献。

手玩一下可以发现，如果一个点没有贡献，要么是它的子树（子树不包含这个点本身）里把所有关键点都包含了，要么是它的子树里一个关键点都没有。

我们拿总的方案数减去没有贡献的方案数，这个很好表示，对于一个点来说（关键点个数为 $k$），它的贡献是：

$\sum {nC^k_n-\sum_i\sum_{j \in son_i}C_{sz_j}^k-\sum_iC_{n-sz_i}^k}$

第一项可以直接做，后面的所有数（$sz_j，n-sz_i$）丢进桶里，设为 $cnt_i$ 表示 $C_{i}^k$ 在这个和式中出现了多少次，改写式子：

原式 $ =\sum C^k_icnt_i = \sum \frac{i!cnt_i}{k!(i-k)!}$，是差卷积的形式，那么我们可以使用 NTT 解决。

注意这个模数，它的原根是 $5$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 924844033;
int a[2100005],b[2100005],r[2100005];
int n,m,limit,L,k;
int qp(int p,int q){
	int ans = 1,pro = p;
	while(q){
		if(q&1)ans = ans*pro%mod;
		pro = pro*pro%mod;q>>=1;
	}return ans;
}const int g = 5,gi = qp(g,mod-2);
int jie[500005],inv[500005];
int C(int n,int m){
	return jie[n]*inv[m]%mod*inv[n-m]%mod;
}
void NTT(int *a,int type){
	for(int i =0;i<limit;i++)if(i<r[i])swap(a[r[i]],a[i]);
	for(int mid = 1;mid<limit;mid<<=1){
		int wn = qp(type == 1?g:gi,(mod-1)/(mid<<1));
		for(int j = 0;j<limit;j+=(mid<<1)){
			int w = 1;
			for(int k= 0;k<mid;k++,w = w*wn%mod){
				int x = a[j+k],y = w*a[j+k+mid]%mod;
				a[j+k] =(x+y)%mod;
				a[j+k+mid] = (x-y+mod)%mod;
			}
		}
	}if(type == -1){
		int inv = qp(limit,mod-2);
		for(int i =0;i<limit;i++)a[i] = a[i]*inv%mod;
	}
}void poly_mul(int* a,int* b,int deg){
	L = 0,limit = 1;
	while(limit<=deg)limit<<=1,L++;
	for(int i =0;i<limit;i++){
		r[i] = (r[i>>1]>>1)|((i&1)<<(L-1));
	}NTT(a,1),NTT(b,1);
	for(int i =0;i<limit;i++)a[i] = a[i]*b[i]%mod;
	NTT(a,-1);
}
vector<int>p[200005];
int sz[200005];
int cnt[200005];
void dfs(int now,int fa){
	sz[now] = 1;
	for(int x:p[now]){
		if(x == fa)continue;
		dfs(x,now);
		cnt[sz[x]]++;
		sz[now]+=sz[x];
	}
	cnt[n-sz[now]]++;
}
int ans[200005];
signed main(){
	jie[0] = inv[0] = 1;for(int i = 1;i<=500000;i++)jie[i] = jie[i-1]*i%mod,inv[i] = qp(jie[i],mod-2);
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n;
	for(int i = 1;i<n;i++){
		int a,b;cin >> a >> b;
		p[a].push_back(b),p[b].push_back(a);
	}
	dfs(1,1);
	for(int i = 1;i<=n+1;i++)b[i] = inv[n-i+1];
	for(int i = 1;i<=n;i++)a[i] = cnt[i]*jie[i]%mod;
	for(int i = 1;i<=n;i++)ans[i] = C(n,i)*n%mod;
	poly_mul(a,b,n+n);
	for(int i = 1;i<=n;i++)ans[i] = (ans[i]-(a[n+i+1]*inv[i])%mod+mod)%mod;
	for(int i = 1;i<=n;i++)cout << ans[i] << endl;
	return 0;
}
```

---

## 作者：APJifengc (赞：1)

我做法太弱智了，简单写下。

首先点集连通块大小可以用寻宝游戏的做法去做，按照 dfs 序排序后将两两距离加和除以二就是生成树的边数，加一就是答案。那么大致就是一个 $ans_k = \sum_S \frac{\mathrm{dis}(s_1, s_k)+\sum \mathrm{dis}(s_i, s_{i + 1})}{2} + 1$。

拆式子，后面那个 $1$ 显然是 $\binom{n}{k}$，前者考虑枚举每个点对 $\mathrm{dis}(i, j)$ 的贡献，发现要不然作为前者要不然作为后者贡献，作为前者就是剩下的数都选在两个数中间，作为后者就是剩下的 $k-2$ 个数都选在两个数两边，那么就是 $ans_k = \sum_{i=1}^n \sum_{j={i+1}}^n\mathrm{dis}(i, j)(\binom{n - (j - i + 1)}{k - 2} + \binom{j - i - 1}{k - 2}) + \binom{n}{k}$。

考虑生成函数，中间组合数的生成函数显然是 $(1+x)^{n - (j - i + 1)}$（先把 $k-2$ 看作 $k$），这个东西与 $j-i$ 有关系，我们先考虑换元，令 $u = x+1$，那么我们考虑求出 $F(x) = \sum_{i=1}^n \sum_{j={i+1}}^n\mathrm{dis}(i, j) u^{j - i}$，然后通过多项式平移即可得出原答案。

直接把 $\mathrm{dis}(i, j)$ 拆成树上差分的形式，然后我们重点考虑怎么求 $\mathrm{dep}(\mathrm{lca}(i, j))$。考虑拆贡献，若一个点能对此造成贡献，那么这两个点的 dfs 序都在这个点子树的区间内。那么我们只需要考虑有多少点对在这个区间内即可，大概形如 $\sum_{i=1}^m \sum_{j=i+1}^m u^{j - i}$，这个是一个二阶后缀和就能解决的事情。剩下的 $\mathrm{dep}(i)$ 和 $\mathrm{dep}(j)$ 也是前缀加 $1$ 的形式，一阶后缀和即可。

---

## 作者：FunnyCreatress (赞：1)

提供一种不同的推柿方法，虽然十分废物。

记一个连通块的一组边界点为 $a_{1..k}$，按 dfs 序排序后，有：
$$V=1+\sum_{i=1}^kdep_{a_i}-\sum_{i=1}^{k-1}dep_{lca(a_i,a_{i+1})}-dep_{lca(a_1...a_k)}$$

其中 $V$ 为该连通块中的点数。

考虑每个点对答案的贡献，第一部分对 $ans_k$ 的贡献显然为 $\dbinom nk+\dbinom {n-1}{k-1}\sum dep_i$。

第二部分对 $ans_k$ 的贡献如下：
$$\begin{aligned}&\sum_idep_i\sum_{x<y}[lca(x,y)=i]\dbinom{n-j+i-1}{k-2}\\=&\sum_idep_i\sum_{t=1}^{sz_i-1}\dbinom{n-t-1}{k-2}\sum_{x=1}^{n-t}[lca(x,x+t)=i]\end{aligned}$$

后面那个东西，可以先假装子树内每对 dfn 相距 $t$ 的点都可行，然后把在同一棵子树内的贡献减掉。

$$\begin{aligned}=&\sum_idep_i\sum_{t=1}^{sz_i-1}\dbinom{n-t-1}{k-2}(\max\{sz_i-t\}-\sum_{y\in son_i}\max\{sz_y-t,0\})\\=&\sum_{t=1}^{n-1}\dbinom{n-t-1}{k-2}\sum_i\max\{sz_i-t,0\}\end{aligned}$$

此处根的深度为 $1$，后面的可以两次差分后前缀和做出来，设为 $f(t)$。

$$\begin{aligned}=&\sum_{t=1}^{n-1}\dbinom{n-t-1}{k-2}f(t)\\=&\sum_{t=1}^{n-1}\dfrac{f(t)(n-t-1)!}{(k-2)!(n-t+1-k)!}\end{aligned}$$

是差卷积的形式，直接反转其中一个卷起来就行了。

第三部分的贡献比较显然：
$$\sum_i\dbinom{sz_i}k$$

用二项式定理搞出生成函数，发现是一个简单多项式向左平移一单位得到的，使用多项式平移，也是差卷积的形式。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1.1e6+5,P=924844033;
int n,k,r[N],fact[N],invf[N],invp[N],g[N],Lim,h[N],cnt[N],ff[N],gg[N],hh[N];
int dep[N],sd,sz[N],f[N],hd[N],nxt[N<<1],to[N<<1],tot;
void add(int x,int y){to[++tot]=y,nxt[tot]=hd[x],hd[x]=tot;}
inline int add_mod(int x,int y){return (x+=y)>=P?x-P:x;}
void dfs(int x,int Fa){
	sd=add_mod(dep[x]=dep[Fa]+1,sd),sz[x]=1;
	for(int i=hd[x],y;i;i=nxt[i])
		if((y=to[i])!=Fa)dfs(y,x),sz[x]+=sz[y];
}
int qpow(int x,int y){
	int res=1;
	for(;y;x=1ll*x*x%P,y>>=1)
		if(y&1)res=1ll*res*x%P;
	return res;
}
void ntt(int *a,int lim,bool flag){
	for(int i=1;i<lim;i++)if(i<(r[i]=(r[i>>1]>>1)|((i&1)*lim>>1)))swap(a[i],a[r[i]]);
	for(int i=1;i<lim;i<<=1){
		int wn=qpow(flag?5:(P*3ll+1)/5,(P-1)/(i<<1));
		for(int j=0;j<lim;j+=i<<1)
			for(int k=0,w=1,x,y;k<i;w=1ll*w*wn%P,k++)
				x=a[j+k],y=1ll*w*a[i+j+k]%P,a[j+k]=add_mod(x,y),a[i+j+k]=add_mod(x,P-y);
	}
	if(flag)return;
	for(int i=0,invn=qpow(lim,P-2);i<lim;i++)a[i]=1ll*a[i]*invn%P;
}
void mul(int *a,int *b,int *c,int lim,int w){
	for(int i=0;i<lim;i++)ff[i]=a[i],gg[i]=b[i];
	ntt(ff,lim,1),ntt(gg,lim,1);
	for(int i=0;i<lim;i++)ff[i]=1ll*ff[i]*gg[i]%P;
	ntt(ff,lim,0);
	for(int i=0;i<=w;i++)c[i]=ff[i];
	for(int i=0;i<lim;i++)ff[i]=gg[i]=0;
}
void trans(int *a,int *b,int lim){
	for(int i=0;i<lim;i++)ff[i]=1ll*fact[lim-i-1]*a[lim-i-1]%P,gg[i]=invf[i];
	mul(ff,gg,hh,lim<<1,lim);
	for(int i=0;i<lim;i++)b[i]=1ll*hh[lim-i-1]*invf[i]%P,hh[lim-i-1]=0;
}
int main(){
	scanf("%d",&n);Lim=1<<(int)ceil(log2(n*3));
	fact[1]=fact[0]=invf[1]=invf[0]=invp[1]=1;
	for(int i=2;i<=Lim;i++)fact[i]=1ll*fact[i-1]*i%P,invp[i]=1ll*(P-P/i)*invp[P%i]%P,invf[i]=1ll*invf[i-1]*invp[i]%P;
	for(int i=1,x,y;i<n;i++)scanf("%d%d",&x,&y),add(x,y),add(y,x);
	dfs(1,0);
	for(int i=1;i<=n;i++)f[sz[i]-1]++,cnt[sz[i]]++;
	for(int i=n-1;~i;i--)f[i]+=f[i+1];
	for(int i=n-1;~i;i--)f[i]=add_mod(f[i],f[i+1]);
	for(int i=0;i<=(n-1>>1);i++)swap(f[i],f[n-1-i]);
	for(int i=0;i<n;i++)f[i]=1ll*fact[i]*f[i]%P,g[n-i]=invf[i];
	mul(f,g,f,Lim,Lim),trans(cnt,h,1<<(int)ceil(log2(n))+1);
	printf("%d\n",n);
	for(int i=2;i<=n;i++)
		printf("%d\n",((1ll*fact[n]*invf[i-1]%P*invf[n-i+1]%P*(sd+1ll*invp[i]*(n-i+1)%P)%P-1ll*invf[i-2]*f[n+i-2]%P-h[i])%P+P)%P);
	return 0;
}
```

---

## 作者：tzc_wk (赞：1)

~~1900 分 AGC F 神题，一看就是我不会做的亚子啊/kk~~

考虑对于给定的集合 $S$ 怎样求 $f(S)$，一个点 $u$ 会对 $f(S)$ 产生 $1$ 的贡献当且仅当 $u\in S$ 或者 $u$ 有两个子树中包含 $S$ 内的节点。

反过来说，一个点 $u$ 不会对 $f(S)$ 产生贡献当且仅当 $S$ 中的点全在 $u$ 的某个子树中。

假设我们规定的集合 $S$ 的大小为 $k$，对于某个点 $u$，有 $m$ 个大小分别为 $s_1,s_2,\dots,s_m$ 的子树，那么共有 $\dbinom{s_1}{k}+\dbinom{s_2}{k}+\dots+\dbinom{s_m}{k}$ 个集合 $S$ 满足 $u$ 不会对 $f(S)$ 产生贡献。

从反面考虑，拿总贡献 $n\times\dbinom{n}{k}$ 减去不会产生的贡献。i.e，$ans_k=n\times\dbinom{n}{k}-\sum\limits_{u=1}^n\sum\limits_{j=1}^{m_u}\dbinom{s_{u,j}}{k}$，其中 $m_u$ 为以 $u$ 为根的子树个数，$s_{u,1},s_{u,2},\dots,s_{u,m_u}$ 分别为这 $m_u$ 个子树的大小。

显然我们并不用考虑这 $u_m$ 个子树具体是什么，只用关心它的大小。故我们可以求出大小为 $s$ 的子树的个数 $c_s$，原式变为 $ans_k=n\times\dbinom{n}{k}-\sum\limits_{s=1}^nc_s\times\dbinom{s}{k}$。

拆组合数，得到 $ans_k=n\times\dbinom{n}{k}-\sum\limits_{s=1}^nc_s\times\dfrac{s!}{k!(s-k)!}$

把 $\dfrac{1}{k!}$ 提到外面去可以得到：$ans_k=n\times\dbinom{n}{k}-\dfrac{1}{k!}\times\sum\limits_{s=1}^nc_s\times\dfrac{s!}{(s-k)!}$

令 $a_i=c_i\times i!,b_i=\dfrac{1}{i!}$，那么原式变为 $ans_k=n\times\dbinom{n}{k}-\dfrac{1}{k!}\times\sum\limits_{s=1}^na_sb_{s-k}$

发现又是 $\sum\limits_{x-y=i}f_xg_y$ 的形式，立马将其中某个数组翻转一下。我是令 $b'_i=b_{n-i+1}$，求一下 $a$ 和 $b'$ 的卷积就行了。

还有这题模数是 $924844033$，其原根是 $5$……

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
const int pr=5;
const int MOD=924844033;
const int MAXN=2e5;
const int MAXT=1<<19;
int n,hd[MAXN+5],nxt[MAXN*2+5],to[MAXN*2+5],ec=0;
void adde(int u,int v){to[++ec]=v;nxt[ec]=hd[u];hd[u]=ec;}
int c[MAXN+5],sz[MAXN+5];
void dfs(int x,int f){
	sz[x]=1;
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(y==f) continue;
		dfs(y,x);sz[x]+=sz[y];c[sz[y]]++;
	} if(x!=1) c[n-sz[x]]++;
}
int qpow(int x,int e){int ret=1;for(;e;e>>=1,x=1ll*x*x%MOD) if(e&1) ret=1ll*ret*x%MOD;return ret;}
int f[MAXN+5],ff[MAXN+5];
int calc(int x,int y){return 1ll*f[x]*ff[y]%MOD*ff[x-y]%MOD;}
int LEN=1,LOG=0,a[MAXT+5],b[MAXT+5],h[MAXT+5],ipr,rev[MAXT+5],prs[MAXT+5][2],inv[MAXT+5];
void NTT(int *a,int len,int type){
	int lg=log2(len);
	for(int i=0;i<len;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg-1));
	for(int i=0;i<len;i++) if(i<rev[i]) swap(a[i],a[rev[i]]);
	for(int i=2;i<=len;i<<=1){
		int W=prs[i][type<0];
		for(int j=0;j<len;j+=i){
			int w=1;
			for(int k=0;k<(i>>1);k++,w=1ll*w*W%MOD){
				int X=a[j+k],Y=1ll*a[(i>>1)+j+k]*w%MOD;
				a[j+k]=(X+Y)%MOD;a[(i>>1)+j+k]=(X-Y+MOD)%MOD;
			}
		}
	}
	if(type==-1) for(int i=0;i<len;i++) a[i]=1ll*a[i]*inv[len]%MOD;
}
int main(){
	scanf("%d",&n);ipr=qpow(pr,MOD-2);
	for(int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		adde(u,v);adde(v,u);
	} dfs(1,0);
//	for(int i=1;i<=n;i++) printf("%d\n",c[i]);
	f[0]=1;for(int i=1;i<=n;i++) f[i]=1ll*f[i-1]*i%MOD;
	ff[n]=qpow(f[n],MOD-2);for(int i=n-1;~i;i--) ff[i]=1ll*ff[i+1]*(i+1)%MOD;
	while(LEN<=n+n) LEN<<=1,LOG++;
	for(int i=1;i<=LEN;i<<=1){
		inv[i]=qpow(i,MOD-2);
		prs[i][0]=qpow(pr,(MOD-1)/i);
		prs[i][1]=qpow(ipr,(MOD-1)/i);
	}
	for(int i=1;i<=n;i++) a[i]=1ll*c[i]*f[i]%MOD;
	for(int i=0;i<=n;i++) b[i]=ff[n-i];
	NTT(a,LEN,1);NTT(b,LEN,1);
	for(int i=0;i<LEN;i++) h[i]=1ll*a[i]*b[i]%MOD;
	NTT(h,LEN,-1);
	for(int i=1;i<=n;i++){
		printf("%d\n",(1ll*n*calc(n,i)%MOD-1ll*ff[i]*h[n+i]%MOD+MOD)%MOD);
	}
	return 0;
}
```

---

## 作者：Kinandra (赞：1)

标签: NTT, 生成函数.

$S_T$ 表示包含点集 $T$ 所有点的最小连通块.

#### Part1

考虑求 $f(k)$, 点 $u$ 要是在某种选择方案 $T$ 中没有贡献(即 $u\notin S_T$) ,  则选择的所有点都在 以 $u$ 为根, $u$ 的某**一个**儿子 $v$ 的子树内, 所以 $u$ 的贡献即为 ${n\choose k}-\sum_v{sz_v\choose k}$ , 我们可以将减去部分的贡献放在边上. 以任意的点为根, 减去的部分即为 $g(k)=\sum_{u\neq root} {sz_u\choose k}+{n-sz_u\choose k}$.

所以 $f(k)=n{n\choose k}-\sum_{u\neq root} {sz_u\choose k}+{n-sz_u\choose k}$ , 预处理阶乘我们可以得到一个 $\mathcal  O(n^2)$ 的算法, 还不够优秀.

#### Part2

发现瓶颈在于减去的那一部分, 观察减去的部分, 减去的贡献都是 $x\choose k$ 的形式, 从这里入手进行优化.

定义 $cnt_x$ 表示 $x\choose k$ 被减去了多少次, 则 $g(k)=\sum_{x=1}^{n-1}cnt_x{x\choose k} = \frac{1}{k!}\sum_{x=1}^{n-1}cnt_xx!\frac{1}{(x-k)!}$ , 这个式子很容易化为卷积的形式求解.

具体的, 设 $a_x=cnt_xx!,b_{n-x-1}=\frac{1}{x!}$ , 则 $g(k)=\frac{1}{k!}\sum_{x=1}^{n-1}a_xb_{n-x+k-1}$.

时间复杂度 $\mathcal O(n\log n)$ .(黑题之耻就是你哒)

```cpp
#include <bits/stdc++.h>
#define mod 924844033
using namespace std;
int read();
int M(int x) { return x >= mod ? x - mod : x; }
int fsp(int bs, int p) {
    int rt = 1;
    while (p) {
        if (p & 1) rt = 1ll * rt * bs % mod;
        bs = 1ll * bs * bs % mod, p >>= 1;
    }
    return rt;
}

int n;

int fac[200005], caf[200005];
void init() {
    int lim = 200000;
    fac[0] = 1;
    for (int i = 1; i <= lim; ++i) fac[i] = 1ll * fac[i - 1] * i % mod;
    caf[lim] = fsp(fac[lim], mod - 2);
    for (int i = lim; i >= 1; --i) caf[i - 1] = 1ll * caf[i] * i % mod;
}
int C(int x, int y) { return 1ll * fac[x] * caf[y] % mod * caf[x - y] % mod; }

vector<int> e[200005];
void add(int u, int v) { e[u].push_back(v), e[v].push_back(u); }
int cnt[200005];
int dfs(int u, int fa) {
    int sz = 1;
    for (int i = 0, v, t; i < e[u].size(); ++i)
        if ((v = e[u][i]) != fa) ++cnt[t = dfs(v, u)], ++cnt[n - t], sz += t;
    return sz;
}
int rtt[600005];
void getrtt(int len, int w) {
    for (int i = 1; i < len; ++i) rtt[i] = (rtt[i >> 1] >> 1) | ((i & 1) << w);
}
struct Poly {
    int x[600005];
    int &operator[](int p) { return x[p]; }
    void ntt(int len) {
        for (int i = 1; i < len; ++i)
            if (rtt[i] > i) swap(x[i], x[rtt[i]]);
        for (int l = 2; l <= len; l <<= 1) {
            int m = l >> 1, O = fsp(5, (mod - 1) / l);
            for (int i = 0; i < len; i += l)
                for (int j = i, tO = 1, t; j < i + m; ++j) {
                    t = 1ll * x[j + m] * tO % mod;
                    x[j + m] = M(x[j] - t + mod), x[j] = M(x[j] + t);
                    tO = 1ll * tO * O % mod;
                }
        }
    }

    void idft(int len) {
        ntt(len), reverse(x + 1, x + len);
        int ny = fsp(len, mod - 2);
        for (int i = 0; i < len; ++i) x[i] = 1ll * x[i] * ny % mod;
    }
} a, b;

int main() {
    n = read(), init();
    for (int i = 1, u, v; i < n; ++i) u = read(), v = read(), add(u, v);
    dfs(1, 0);
    for (int i = 1; i < n; ++i) a[i] = 1ll * cnt[i] * fac[i] % mod;
    for (int i = 0; i < n; ++i) b[n - i - 1] = caf[i];

    int len = 2, w = 1;
    while (len < (n << 1)) len <<= 1, ++w;
    getrtt(len, w - 1), a.ntt(len), b.ntt(len);
    for (int i = 0; i < len; ++i) a[i] = 1ll * a[i] * b[i] % mod;
    a.idft(len);

    for (int i = 1; i <= n; ++i) {
        printf("%d\n", M(1ll * n * C(n, i) % mod -
                         1ll * a[n + i - 1] * caf[i] % mod + mod));
    }
    return 0;
}

int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
```



---

## 作者：nekko (赞：1)

我不知道发生了什么，只有第一次提交能过，之后就TLE了……

考虑贡献，假设一共选择 $k$ 个

### 选了

$$\sum_{i=1}^{n} {n-1 \choose k-1}$$

### 没选

$$\sum_{i=1}^{n}\sum_{x=1}^{k}{a_i-1 \choose x}{n-a_i \choose k-x}$$

### 算总账

$$\begin{aligned} f_k =&\sum_{i=1}^{n} {n-1 \choose k-1}+\sum_{i=1}^{n}\sum_{x=1}^{k}{a_i-1 \choose x}{n-a_i \choose k-x}-\sum_{i \to j} {a_j \choose k} \\ =&n{n-1 \choose k-1}+\sum_{i=1}^{n} {n-1 \choose k}-{n-a_i \choose k} -\sum_{i=2}^{n} {a_i \choose k} \\ =&n \left({n-1 \choose k-1}+{n-1 \choose k}\right)-\sum_{i=1}^{n} {n-a_i \choose k}+ {a_i \choose k}[i \ge 2] \\ =&n {n \choose k}-\sum_{i=1}^{n} {n-a_i \choose k} + {a_i \choose k} [i \ge 2] \\ \end{aligned}$$

至此可以发现只需要计算下面这个东西就行了：

$$ \begin{aligned} p_k =&\sum_{i=1}^{n}{a_i \choose k} \\ \end{aligned} $$

设 $c_k=\sum_{i=1}^{n}[a_i=k]$

$$ \begin{aligned} p_k = &\sum_{i \in V} {v \choose k}c_v \\ = &\sum_{i \in V} \frac{v!}{k!(v-k)!}c_v \end{aligned} $$

注意到可行的 $a_i$ 范围是 $0 \le a_i \le 2n$，也就是说：

$$ \begin{aligned} k!p_k =&\sum_{i=0}^{2n}i!c_i\frac{1}{(i-k)!} \\ =&\sum_{i=0}^{2n}i!c_i\frac{1}{(i-k)!} \end{aligned} $$

设 $X_i=i!c_i,Y_i=(2n-i)!,Z_k=k!p_k$，则：

$$Z_k=\sum_{i=0}^{2n}X_iY_{2n-i+k}$$

令 $\forall t > 2n,X_{t}=0$，则有：

$$ \begin{aligned} Z_{2n+k} =&\sum_{i=0}^{2n+k}X_iY_{2n-i+k} \\ =&\sum_{i+j=2n+k}X_iY_{j} \\ \end{aligned} $$

于是就是一个普通的卷积形式了

```
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 4e5 + 10, mod = 924844033;

int n, m;
ll f[N], fac[N], invfac[N], a[N], b[N], c[N], d[N], e[N];
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

vector<int> g[N]; int fa[N];

void dfs(int u, int fa) {
    :: fa[u] = fa;
    a[u] = 1;
    for(int v: g[u]) {
        if(v == fa) continue;
        dfs(v, u);
        a[u] += a[v];
    }
}

ll C(int n, int m) {
    return m < 0 || n < m ? 0 : fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}

ll Cn_1k[N];

namespace CALC {
    ll p[N], X[N * 10], Y[N * 10], f[N * 10];
    int a[N], len, inv;
    const int g[2] = { 5, pw(5, mod - 2) };
    ll pw(ll a, ll b) {
        ll r = 1;
        for( ; b ; b >>= 1, a = a * a % mod)
            if(b & 1)
                r = r * a % mod;
        return r;
    }
    int rev(int x, int n) {
        int res = 0;
        for(int i = 0 ; (1 << i) < n ; ++ i) {
            res = (res << 1) | ((x >> i) & 1);
        }
        return res;
    }
    void ntt(ll *a, int ty, int n) {
        for(int i = 0 ; i < n ; ++ i) f[rev(i, n)] = a[i];
        for(int i = 2 ; i <= n ; i <<= 1) {
            ll wn = pw(g[ty], (mod - 1) / i);
            for(int j = 0 ; j < n ; j += i) {
                ll w = 1;
                for(int k = j ; k < j + i / 2 ; ++ k) {
                    ll u = f[k], v = w * f[k + i / 2] % mod;
                    f[k] = (u + v) % mod;
                    f[k + i / 2] = (u - v) % mod;
                    w = w * wn % mod;
                }
            }
        }
        for(int i = 0 ; i < n ; ++ i) {
            a[i] = f[i];
            if(ty) a[i] = a[i] * inv % mod;
        }
    }

    void init() {
        len = 1; while(len < 4 * n) len <<= 1;
        for(int i = 0 ; i <= 2 * n ; ++ i) Y[i] = invfac[2 * n - i];
        inv = pw(len, mod - 2);
        ntt(Y, 0, len);
    }
    void sol() {
        int mx = 0;
        for(int i = 0 ; i < len ; ++ i) X[i] = 0;
        for(int i = 1 ; i <= n ; ++ i) if(a[i] >= 0) ++ X[a[i]], mx = max(mx, a[i]);
        for(int i = 0 ; i <= mx ; ++ i) if(X[i]) (X[i] *= fac[i]) %= mod;
        ntt(X, 0, len);
        for(int i = 0 ; i < len ; ++ i) (X[i] *= Y[i]) %= mod;
        ntt(X, 1, len);
        for(int k = 1 ; k <= m ; ++ k) p[k] = X[2 * n + k] * invfac[k] % mod;
    }
}

void solf() {
    CALC :: a[1] = -1;
    for(int i = 2 ; i <= n ; ++ i) {
        CALC :: a[i] = a[i];
    }
    CALC :: sol();
    for(int k = 1 ; k <= m ; ++ k) {
        (f[k] -= CALC :: p[k]) %= mod;
    }
    
    for(int i = 1 ; i <= n ; ++ i) {
        CALC :: a[i] = n - a[i];
    }
    CALC :: sol();
    for(int k = 1 ; k <= m ; ++ k) {
        (f[k] -= CALC :: p[k]) %= mod;
    }
}

int main() {
    scanf("%d", &n), m = n;
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        fac[i] = fac[i - 1] * i % mod;
    }
    invfac[n] = pw(fac[n], mod - 2);
    for(int i = n - 1 ; i ; -- i) {
        invfac[i] = invfac[i + 1] * (i + 1) % mod;
    }
    dfs(1, 0);

    CALC :: init();
    solf();

    for(int k = 1 ; k <= m ; ++ k) {
        (f[k] += n * C(n, k) % mod) %= mod;
        printf("%lld\n", (f[k] + mod) % mod);
    }
}
```

---

## 作者：0xyz (赞：0)

考虑每个点的贡献，有：

$$\begin{aligned}f_i&=\sum\limits_{1\le x\le n}\bigg(C^{i}_{n}-\sum\limits_{(x,y)\in E}C^{i}_{sz_y}\bigg)\\&=nC^{i}_{n}-\sum\limits_{1\le x\le n}\sum\limits_{(x,y)\in E}C^{i}_{sz_y}\\&=nC^{i}_{n}-\sum\limits_{i\le j\le n}cnt_j\times C^{i}_{j}\\&=nC^{i}_{n}-\frac{1}{i!}\sum\limits_{i\le j\le n}cnt_j\times (j!)\times\frac{1}{(j-i)!}\\&=nC^{i}_{n}-\frac{[x^{n+i}]h_i}{i!}\end{aligned}$$

其中 $cnt_i$ 表示分别以所有节点为根时根的大小为 $i$ 的子树个数总和，$f=\sum\limits_{0\le i\le n}cnt_i\times (i!)x^i,g=\sum\limits_{0\le i\le n}\frac{1}{(n-i)!}x^i,h=fg$。用 NTT，$O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll _=1e6+5,mod=924844033,p=5,q=554906420;
ll n,m,re[_],a[_],b[_],c[_],f[_],g[_],z[_];
vector<ll>e[_];
inline ll ksm(ll a,ll b){
	ll r=1;
	for(;b;a=a*a%mod,b>>=1)
		if(b&1)r=r*a%mod;
	return r;
}
inline void NTT(ll *a,ll len,ll tp){
	for(ll i=0;i<len;i++)
		if(i<re[i])swap(a[i],a[re[i]]);
	for(ll mid=1;mid<len;mid<<=1){
		ll wn=ksm(tp?p:q,(mod-1)/(mid<<1));
		for(ll r=mid<<1,j=0;j<len;j+=r){
			ll w=1;
			for(ll k=0;k<mid;k++,w=w*wn%mod){
				ll s=a[j+k],t=w*a[j+mid+k]%mod;
				a[j+k]=(s+t)%mod;a[j+mid+k]=(s+mod-t)%mod;
			}
		}
	}
}
inline void mul(ll *a,ll *b,ll len){
	ll l=0,mxl=1;
	while(mxl<=len)mxl<<=1,l++;
	for(ll i=0;i<mxl;i++)re[i]=(re[i>>1]>>1)|((i&1)<<(l-1));
	NTT(a,mxl,1);NTT(b,mxl,1);
	for(ll i=0;i<mxl;i++)a[i]=a[i]*b[i]%mod;
	NTT(a,mxl,0);
	ll inv=ksm(mxl,mod-2);
	for(ll i=0;i<mxl;i++)a[i]=a[i]*inv%mod;
}
void dfs(ll x,ll fa){
	z[x]=1;
	for(ll y:e[x])
		if(y!=fa)dfs(y,x),z[x]+=z[y],c[z[y]]++;
	c[n-z[x]]++;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;a[0]=1;
	for(ll i=1;i<=n;i++)a[i]=a[i-1]*i%mod;
	b[n]=ksm(a[n],mod-2);
	for(ll i=n;i;i--)b[i-1]=b[i]*i%mod;
	for(ll i=1,x,y;i<n;i++)cin>>x>>y,e[x].push_back(y),e[y].push_back(x);
	dfs(1,0);
	for(ll i=0;i<=n;i++)f[i]=c[i]*a[i]%mod,g[i]=b[n-i];
	mul(f,g,n+n);
	for(ll i=1;i<=n;i++)cout<<(n*a[n]%mod*b[i]%mod*b[n-i]%mod+mod-f[n+i]*b[i]%mod)%mod<<'\n';
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

挺简单的题。

一个点不会被统计入答案中，当且仅当把这个点删掉之后，其他关键点都在同一个联通块中，且没有某一个关键点被删掉。

假设一个点删去之后，所有子树的大小是 $s_1,s_2,s_3,\dots,s_t$，那么这个点对于 $i=k$ 的答案的贡献就是：

$$
\binom{n}{k} - \sum_{i=1}^t \binom{s_i}{k}
$$

因此我们可以计算出每个 $s$ 的贡献 $cnt_s$，对于每个 $k$ 求出

$$
\sum_{i=1}^n cnt_i\binom{i}{k} = \sum_{i=1}^n \dfrac{i!cnt_i}{k!(i-k)!}
$$

可以认为是 $i!cnt_i$ 的生成函数和 $\dfrac{1}{i!}$ 的生成函数的差卷积。

使用 NTT 维护即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1000000+10,MOD=924844033;
int n,sze[MAXN],f[MAXN],g[MAXN],k,rev[MAXN],cnt[MAXN],frac[MAXN],inv[MAXN];
vector<int> G[MAXN];
int qpow(int base,int p) {
	int ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;
	}
	return ans;
}
void dfs(int u,int f) {
	sze[u]=1;
	for(auto v:G[u]) if(v!=f) dfs(v,u),sze[u]+=sze[v];
	vector<int> vc;
	for(auto v:G[u]) if(v!=f) vc.push_back(sze[v]);
	if(u!=1) vc.push_back(n-sze[u]);
	cnt[n]++;
	for(auto id:vc) cnt[id]--;
	return ;	
}
void ntt(int *f,int k,int op) {
	rev[0]=0;
	ffor(i,1,k-1) rev[i]=(rev[i>>1]>>1)+(k>>1)*(i&1);
	ffor(i,0,k-1) if(rev[i]>i) swap(f[i],f[rev[i]]);
	int lst=1,len=1;
	while(len<k) {
		lst=len,len<<=1;
		int omega=qpow(5,(MOD-1)/len);
		if(op==-1) omega=qpow(omega,MOD-2);
		ffor(i,0,k/len-1) {
			int l=i*len,r=l+len-1,tmp=1;
			ffor(j,l,l+lst-1) {
				int x=f[j],y=f[j+lst];
				f[j]=(x+y*tmp)%MOD,f[j+lst]=(x-y*tmp)%MOD,tmp=tmp*omega%MOD;
			}
		}
	}
	if(op==-1) {
		int inv=qpow(k,MOD-2);
		ffor(i,0,k-1) f[i]=f[i]*inv%MOD;	
	}
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n-1) {
		int u,v;
		cin>>u>>v;
		G[u].push_back(v),G[v].push_back(u);
	}
	dfs(1,0);
	frac[0]=1;
	ffor(i,1,n) frac[i]=frac[i-1]*i%MOD;
	inv[n]=qpow(frac[n],MOD-2);
	roff(i,n-1,0) inv[i]=inv[i+1]*(i+1)%MOD;
	ffor(i,0,n) f[i]=frac[i]*cnt[i]%MOD;
	ffor(i,0,n) g[i]=inv[n-i];
	k=1;
	while(k<=n+n) k<<=1;
	ntt(f,k,1),ntt(g,k,1);
	ffor(i,0,k-1) f[i]=f[i]*g[i]%MOD;
	ntt(f,k,-1);
	ffor(i,1,n) cout<<(f[i+n]*inv[i]%MOD+MOD)%MOD<<'\n';
	return 0;
}
```

---

## 作者：lhm_ (赞：0)

考虑每个点 $x$ 对答案的贡献，即总方案数减去不合法方案数，得：
$$
\large\begin{aligned}

f_i&=\sum_{x=1}^n\left(\binom{n}{i}-\sum_{\exists e(x,y)} \binom{size_y}{i}\right) \\

&=n\binom{n}{i}-\sum_{x=1}^n\sum_{\exists e(x,y)} \binom{size_y}{i} \\

\end{aligned}
$$
设 $cnt_i$ 为子树大小为 $i$ 的子树个数，得：
$$
\large\begin{aligned}

f_i&=n\binom{n}{i}-\sum_{j=i}^n cnt_j\binom{j}{i} \\

&=n\binom{n}{i}-\sum_{j=i}^n cnt_j\frac{j!}{i!(j-i)!} \\

&=n\binom{n}{i}-\frac{1}{i!}\sum_{j=i}^n \frac{cnt_jj!}{(j-i)!} \\

&=n\binom{n}{i}-\frac{1}{i!}\sum_{j=0}^{n-i} \frac{cnt_{i+j}(i+j)!}{j!} \\

\end{aligned}
$$
发现第二项是一个减法卷积的形式，用 $NTT$ 即可求解。

```cpp
#include<bits/stdc++.h>
#define maxn 800010
#define P 924844033
#define G 5
using namespace std;
typedef long long ll;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
ll n;
ll rev[maxn],f[maxn],g[maxn],fac[maxn],ifac[maxn],siz[maxn],cnt[maxn];
struct edge
{
    int to,nxt;
}e[maxn];
int head[maxn],edge_cnt;
void add(int from,int to)
{
    e[++edge_cnt]={to,head[from]},head[from]=edge_cnt;
}
ll qp(ll x,ll y)
{
    ll v=1;
    while(y)
    {
        if(y&1) v=v*x%P;
        x=x*x%P,y>>=1;
    }
    return v;
}
int calc(int n)
{
    int lim=1;
    while(lim<=n) lim<<=1;
    for(int i=0;i<lim;++i)
        rev[i]=(rev[i>>1]>>1)|((i&1)?lim>>1:0);
    return lim;
}
void NTT(ll *a,int lim,int type)
{
    for(int i=0;i<lim;++i)
        if(i<rev[i])
            swap(a[i],a[rev[i]]);
    for(int len=1;len<lim;len<<=1)
    {
        ll wn=qp(G,(P-1)/(len<<1));
        for(int i=0;i<lim;i+=len<<1)
        {
            ll w=1;
            for(int j=i;j<i+len;++j,w=w*wn%P)
            {
                ll x=a[j],y=w*a[j+len]%P;
                a[j]=(x+y)%P,a[j+len]=(x-y+P)%P;
            }
        }
    }
    if(type==1) return;
    ll inv=qp(lim,P-2);
    for(int i=0;i<lim;++i) a[i]=a[i]*inv%P;
    reverse(a+1,a+lim);
}
void mul(ll *f,ll *g)
{
    int lim=calc(n<<1);
    NTT(f,lim,1),NTT(g,lim,1);
    for(int i=0;i<lim;++i) f[i]=f[i]*g[i]%P;
    NTT(f,lim,-1);
}
void dfs(int x,int fa)
{
    siz[x]=1;
    for(int i=head[x];i;i=e[i].nxt)
    {
        int y=e[i].to;
        if(y==fa) continue;
        dfs(y,x),siz[x]+=siz[y];
    }
    cnt[siz[x]]++,cnt[n-siz[x]]++;
}
ll C(ll n,ll m)
{
    return fac[n]*ifac[m]%P*ifac[n-m]%P;
}
void init()
{
    fac[0]=ifac[0]=1;
    for(int i=1;i<=n;++i) fac[i]=fac[i-1]*i%P;
    ifac[n]=qp(fac[n],P-2);
    for(int i=n-1;i;--i) ifac[i]=ifac[i+1]*(i+1)%P;
}
int main()
{
    read(n),init();
    for(int i=1;i<n;++i)
    {
        int x,y;
        read(x),read(y);
        add(x,y),add(y,x);
    }
    dfs(1,0),g[0]=1;
    for(int i=1;i<=n;++i) f[i]=cnt[n-i]*fac[n-i]%P,g[i]=ifac[i];
    mul(f,g),reverse(f,f+n+1);
    for(int i=1;i<=n;++i) printf("%lld\n",(n*C(n,i)%P-ifac[i]*f[i]%P+P)%P);
    return 0;
}
```

---

## 作者：Hyscere (赞：0)

~~注意到模数为$441\cdot 2^{21}+1$，嘿嘿~~

首先要想到考虑贡献，然后这题就简单了。

设当前要算的为$f(i)$，我们考虑第$x$个点的贡献，显然可以得到贡献为：
$$\binom{n}{i}-\sum_{v\in son_{x}}\binom{sz_v}{i}$$
就是所有的方案减去这个点选不到的方案，其中$sz_v$表示以$x$为根$v$的$\rm size$。

然后累和：
$$f(i)=\sum_{x=1}^{n}\left(\binom{n}{i}-\sum_{v\in son_{x}}\binom{sz_v}{i}\right)$$
$$=n\binom{n}{i}-\sum_{x=1}^{n}\sum_{v\in son_x}\binom{sz_v}{i}$$
后面那块不好处理，我们可以记个桶$cnt(s)$表示大小为$s$的子树出现了多少次，这个一遍$\rm dfs$就可以算出来。

那么把式子化一下：
$$f(i)=n\binom{n}{i}-\sum_{j=1}^{n}cnt(j)\binom{j}{i}$$
$$=n\binom{n}{i}-\frac{1}{i!}\sum_{j=i}^{n}\frac{cnt(j)j!}{(j-i)!}$$
注意到后面可以转化为卷积的形式，设：
$$g(i)=cnt(i)i!,h(i)=\frac{1}{i!}$$
后面的$\sum$就是：
$$\sum_{j=i}^{n}g(j)h(j-i)=\sum_{j=0}^{n-i}g(j-i)h(j)$$
我们$\rm reverse$一下$g$：
$$\sum_{j=0}^{n-i}g_R((n-i)-j)h(j)$$
$NTT$优化就好了，复杂度$O(n\log n)$。

注意这个神奇的模数原根是$5$，我一开始写成$3$还以为是$NTT$挂了...

```cpp
#include<bits/stdc++.h>
using namespace std;

void read(int &x) {
    x=0;int f=1;char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-f;
    for(;isdigit(ch);ch=getchar()) x=x*10+ch-'0';x*=f;
}

void print(int x) {
    if(x<0) putchar('-'),x=-x;
    if(!x) return ;print(x/10),putchar(x%10+48);
}
void write(int x) {if(!x) putchar('0');else print(x);putchar('\n');}

#define lf double
#define ll long long
#define end puts("NO"),exit(0)

const int maxn = 1e6+10;
const int inf = 1e9;
const lf eps = 1e-8;
const int mod = 924844033;

int add(int x,int y) {return x+y>mod?x+y-mod:x+y;}
int del(int x,int y) {return x-y<0?x-y+mod:x-y;}
int mul(int x,int y) {return 1ll*x*y-1ll*x*y/mod*mod;}

int qpow(int a,int x) {
    int res=1;
    for(;x;x>>=1,a=mul(a,a)) if(x&1) res=mul(a,res);
    return res;
}

int fac[maxn],ifac[maxn],inv[maxn],pos[maxn],N,mxn,bit,n;
int w[maxn],rw[maxn],f[maxn],g[maxn],h[maxn],head[maxn],tot,sz[maxn];
struct edge{int to,nxt;}e[maxn<<1];

void ins(int u,int v) {e[++tot]=(edge){v,head[u]},head[u]=tot;}

void dfs(int x,int fa) {
    sz[x]=1;
    for(int i=head[x];i;i=e[i].nxt) 
        if(e[i].to!=fa) dfs(e[i].to,x),sz[x]+=sz[e[i].to],g[sz[e[i].to]]++;
    g[n-sz[x]]++;
}

void ntt_init() {
    w[0]=rw[0]=1,w[1]=qpow(5,(mod-1)/mxn);
    for(int i=2;i<=mxn;i++) w[i]=mul(w[i-1],w[1]);
    rw[1]=qpow(w[1],mod-2);
    for(int i=2;i<=mxn;i++) rw[i]=mul(rw[i-1],rw[1]);
}

void ntt_get(int len) {
    for(bit=0,N=1;N<=len;N<<=1,bit++);
    for(int i=0;i<N;i++) pos[i]=pos[i>>1]>>1|((i&1)<<(bit-1));
}

void ntt(int *r,int op) {
    for(int i=1;i<N;i++) if(pos[i]>i) swap(r[i],r[pos[i]]);
    for(int i=1,d=mxn>>1;i<N;i<<=1,d>>=1) 
        for(int j=0;j<N;j+=i<<1) 
            for(int k=0;k<i;k++) {
                int x=r[j+k],y=mul((op==-1?rw:w)[k*d],r[i+j+k]);
                r[j+k]=add(x,y),r[i+j+k]=del(x,y);
            }
    if(op==-1) {int d=qpow(N,mod-2);for(int i=0;i<N;i++) r[i]=mul(r[i],d);}
}

int main() {
    read(n);for(int x,y,i=1;i<n;i++) read(x),read(y),ins(x,y),ins(y,x);
    dfs(1,0);fac[0]=ifac[0]=inv[0]=inv[1]=1;
    for(int i=1;i<=n;i++) fac[i]=mul(fac[i-1],i);
    for(int i=2;i<=n;i++) inv[i]=mul(mod-mod/i,inv[mod%i]);
    for(int i=1;i<=n;i++) ifac[i]=mul(ifac[i-1],inv[i]);
    for(int i=0;i<=n;i++) h[i]=ifac[i],g[i]=mul(g[i],fac[i]);
    g[0]=0;
    
    reverse(g,g+n+1);for(mxn=1;mxn<=n<<1;mxn<<=1);
    ntt_init(),ntt_get(n<<1),ntt(g,1),ntt(h,1);
    for(int i=0;i<N;i++) f[i]=mul(g[i],h[i]);
    ntt(f,-1);
    for(int i=1;i<=n;i++) write(del(mul(n,mul(fac[n],mul(ifac[i],ifac[n-i]))),mul(ifac[i],f[n-i])));
    return 0;
}
```

---

## 作者：WhiteEurya (赞：0)

给定一棵无根树，定义 $f(i)$，对于所有大小为 $i$ 的点集，求出能够包含它的最小连通块大小之和。对于 $i=1 \to n$ 的所有 $i$，求出 $$f(i)$$。

---------------

定义 $s_i$ 表示 $i$ 号点为根的子树大小。

当我们统计树上路径长度的时候，可以对每一条边考虑它被经过了多少次。

同样的，统计连通块大小，我们就对每一个点考虑它被经过了多少次。

在一棵 $n$ 个点的树上，选出 $k$ 个点，总共有 $C(n,k)$ 种方案。但是有两种情况需要舍去：点在上面选和在下面选。（注意选自己这个点也算是在下面）

在上面选的方案数为 $C(n,n-s_x)$

在下面选的方案数为

$$\sum_ {y \in x}C(n,s_y)$$

也就是对于每个子树都要计算答案。要不然会算漏。

那么一个节点 $x$ 在 $i=k$ 的时候对答案的贡献为：
$$
C(n,k) - \sum_{y \in x}C(n,s_y)- C(n,n-s_x)
$$
考虑 $C(n,k)$ 这一项，在答案里会带个系数 $a_i$。

注意到无论 $k$ 怎么改变，系数是不会变的。因为贡献式对系数的计算与 $k$ 无关。该枚举的还是要枚举。

这样把一个点的贡献拆成若干个组合数之和。那么对于 $i=k$，它对答案的贡献就是：
$$
\sum_{x=k}^n a_x \times C(n,x)
$$
也就是对于每一个大小大于 $k$ 的树都要计算答案。

发现这样子计算是 $n^2$ 的。考虑化简这个式子。
$$
\sum_{x=k}^na_x \times \frac{x!}{k!(x-k)!} 
$$

$$
\frac{1}{k!}\sum_{x=k}^n (a_x \times x!) \times \frac{1}{(x-k)!}
$$

记 $F(x)=a_x \times x!$，$G(x)=\frac{1}{(x-k)!}$ (注意这里是数组翻转后得到的结果。)

把 $G(x)$ 翻转一下，得到 $G(n-x)$，这样就能卷积了。

这是一个卷积的形式，可以直接计算。记答案为 $A(x)​$

也就是：
$$
A(k)=\sum_{x+y=k}F(x)*G(y)
$$

分析一下指数： $F(x)$ 的指数为 $x$，$G(n-x)$ 的指数为 $n-x+k$

相加后得到 $n+k$

那么 $i=k$ 时我们要计算入答案的系数为 $A(n+k)$

这样得到 $f(i)$ 的计算式：
$$
f(i)=\frac{1}{i!} \times A(i+k)
$$

-----------------

还有一些小问题。比如模数是 $924844033$

原根不是 $3$。简易推导一下：

> $g^{k} = 1 \pmod p$ 当且仅当 $k=p-1$ 时成立，则称 $g$ 是 $p$ 的原根。 

根据原根的验证方法，我们枚举 $g=2,3,4,5,6$ 来验证。

$g=2$。写程序验证得当 $k=77070336$ 时原式也成立，所以不是原根。

$g=3$。写程序验证得当 $k=7340032$ 时原式也成立，所以不是原根。

$g=4$。写程序验证得当 $k= 38535168$ 时原式也成立，所以不是原根。

$g=5$，发现只有当 $k=p-1$ 才成立，所以这道题的原根设置为 $5$

~~写程序枚举原根的是不是就我一个人啊qwq，应该有更快捷的方法吧~~

```
#include <bits/stdc++.h>

#define int long long

const int Mod = 924844033;
const int G = 5;
const int MaxN = 3e6 + 10;

struct Edge {
    int To, Next;
}Road[MaxN];

int N, M;
int Cnt = 0, Last[MaxN];

void Add(int U, int V) {
    Road[++Cnt] = (Edge) {V, Last[U]};
    Last[U] = Cnt; 
}

int Size[MaxN];
int Coe[MaxN];
using namespace std;

void Dfs(int Now, int Pa) {
    Coe[N] += 1; Size[Now] = 1;
    for(int i = Last[Now]; i; i = Road[i].Next) {
        int To = Road[i].To;
        if(To ^ Pa) {
            Dfs(To, Now); 
            Coe[Size[To]] -= 1;
            if(Coe[Size[To]] < 0) 
                Coe[Size[To]] = (Coe[Size[To]] + Mod) % Mod;
            Size[Now] += Size[To]; 
        }
    }
    Coe[N - Size[Now]] -= 1;
    if(Coe[N - Size[Now]] < 0) 
        Coe[N - Size[Now]] = (Coe[N - Size[Now]] + Mod) % Mod;
}

int Kasumi(int A, int B) {
    int Ans = 1, Base = A;
    B = (B + (Mod - 1)) % (Mod - 1);
    while(B) {
        if(B & 1) Ans = Base * Ans % Mod;
        Base = Base * Base % Mod;
        B >>= 1;
    }
    return Ans;
} 

int Fac[MaxN], Inv[MaxN];

void Init() {
    Fac[0] = 1; Inv[0] = 1;
    for(int i = 1; i <= N << 1; i++) Fac[i] = Fac[i - 1] * i % Mod;
    for(int i = 1; i <= N << 1; i++) Inv[i] = Kasumi(Fac[i], Mod - 2);
}

int C(int A, int B) {
    return Fac[A] % Mod * Inv[B] % Mod * Inv[A - B] % Mod;
} 

int Rev[MaxN];

#define Swap(A, B) A ^= B ^= A ^= B

void Ntt(int *A, int N, int Flag) {
    for(int i = 0; i < N; i++) 
        if(i < Rev[i]) Swap(A[i], A[Rev[i]]);
    for(int i = 1; i < N; i <<= 1) {
        int W = Kasumi(G, Flag * (Mod - 1) / (i << 1));
        for(int j = 0; j < N; j += (i << 1)) {
            int Wn = 1;
            for(int k = 0; k < i; k++, Wn = Wn * W % Mod) {
                int x = A[j + k], y = A[i + j + k] * Wn % Mod;
                A[j + k] = (x + y) % Mod;
                A[i + j + k] = (x - y + Mod) % Mod;
            }
        }
    }
    if(!~Flag) {
        int T = Kasumi(N, Mod - 2);
        for(int i = 0; i < N; i++) A[i] = A[i] * T % Mod;
    }
}

int Ans[MaxN];
int A[MaxN], B[MaxN];

main() {
    scanf("%lld", &N);
    for(int i = 1, A, B; i <= N - 1; i++) 
        scanf("%lld%lld", &A, &B), Add(A, B), Add(B, A);
    Init(); Dfs(1, 0);
    for(int i = 0; i <= N; i++) A[i] = Coe[i] * Fac[i] % Mod, B[i] = Inv[i];
    std::reverse(B, B + N + 1);
    int Len = 1, Log = 0;
    while(Len <= (N << 1)) Len <<= 1, Log += 1;
    for(int i = 0; i < Len; i++)
        Rev[i] = (Rev[i >> 1] >> 1) | ((i & 1) << (Log - 1));
    Ntt(A, Len, 1); Ntt(B, Len, 1);
    for(int i = 0; i < Len; i++) A[i] = A[i] * B[i] % Mod;
    Ntt(A, Len, -1);
    for(int i = 0; i < Len; i++) Ans[i] = A[i];
    for(int i = 1; i <= N; i++) {
        int P = Ans[N + i] * Inv[i] % Mod;
        P = (P + Mod) % Mod;
        printf("%lld\n", P % Mod);
    }
} 
```

#### 附录

[洛谷 AT2064 Many Easy Problems](https://www.luogu.org/problemnew/show/AT2064)

---

