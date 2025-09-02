# 【模板】Berlekamp–Massey 算法

## 题目背景

前置技能：线性递推 $\&~\rm BM$ 算法。

同时，请注意优化你的空间。保证最短递推式**唯一**。

出题人为强行二合一感到很抱歉，但是其实也是可以学习一下 $k^2 \log n$ 线性递推的——保证在 `-O2` 指令下可以过。

## 题目描述

给出一个数列 $P$ 从 $0$ 开始的前 $n$ 项。

求序列 $P$ 在 $\bmod~998244353$ 下的最短线性递推式，并在 $\bmod~998244353$ 下输出 $P_m$。

## 说明/提示

对于 $100 \%$ 的数据，$n < m \le {10}^9$，$1 \le n \le 10000$，保证递推式最长不超过 $5000$。

## 样例 #1

### 输入

```
4 10
1 1 2 3
```

### 输出

```
1 1 
89
```

## 样例 #2

### 输入

```
5 10
3 7 27 95 339```

### 输出

```
3 2
691707
```

# 题解

## 作者：皎月半洒花 (赞：22)

然而是个板子。

因为迄今为止没有什么人写这道题，所以选择自己抛砖引个玉。

学习BM算法推荐以下两个博客

[zzd的博客](https://www.cnblogs.com/zhouzhendong/p/Berlekamp-Massey.html)

[zzq的博客](https://www.cnblogs.com/zzqsblog/p/6877339.html)

~~这俩名字好对称啊~~

然后其实BM的用途就是一个求递推式，但事实上完全可以用来打表。遇到很zz的计数题或者什么，只要脸好一般都是可以找到低次线性递推式子。所以这也不妨是一个黑科技。

之后BM求出来的式子直接拿线性递推跑一下就好。此处如果你写的$k^2 \log n$的暴力常数比较小的话，也是可以跑过去的——卡常数可以参照zzq的博客，他滚了一下空间并且时间上也是很优的。

~~所以不要说我毒瘤啊~~

时限上也是完全够的~~不像某多点求值和快速插值~~。只是注意一下线性递推的时候清零就好。

代码就不上了，都是板子，还是各位自己写吧qwq

____

然而因为没有代码被管理给ban了，所以还是上一下BM算法的板子吧：

```cpp
vector <LL> f[MAXN] ;
int fail[MAXN] ; LL delta[MAXN], now ;
inline void BM(int I){
    int i, j ;
    for (i = 1 ; i <= I ; ++ i){
        for (now = base[i], j = 0 ; j < f[M].size() ; ++ j)
            now = (now - base[i - j - 1] * f[M][j] % Mod) % Mod ;
        delta[i] = now ; if (!delta[i]) continue ; fail[M] = i ;
        if (!M) { f[++ M].resize(i), delta[i] = base[i] ;  continue ; }
        int Id = M - 1, v = f[Id].size() - fail[Id] + i ;
        for (j = 0 ; j < M ; ++ j)
            if (i - fail[j] + f[j].size() < v)
                Id = j, v = i - fail[j] + f[j].size() ;
        f[M + 1] = f[M] ; ++ M ; while (f[M].size() < v) f[M].push_back(0) ;
        LL mul = delta[i] * expow(delta[fail[Id]], Mod - 2) % Mod ;
        (f[M][i - fail[Id] - 1] += mul) %= Mod  ;
        for (j = 0 ; j < f[Id].size() ; ++ j)
            (f[M][i - fail[Id] + j] -= mul * f[Id][j]) %= Mod ;
    }
    K = f[M].size() ;
    for (i = 0 ; i < f[M].size() ; ++ i)
        p[i + 1] = (f[M][i] % Mod + Mod) % Mod, cout << p[i + 1] << " " ; puts("") ;
}
。。。。。。
int main(){
    int W ; cin >> W >> N ; rr int Len = 1, l = 0, i ;
    for (i = 1 ; i <= W ; ++ i) scanf("%lld", &base[i]) ; BM(W) ;
    while (Len < (K << 1)) Len <<= 1, ++ l ; F[0] = 1 ; Len <<= 1, ++ l ;
    for (i = 0 ; i < Len ; ++ i) R[i] = (R[i >> 1] >> 1) | ((i & 1) << (l - 1)) ;
    for (i = 1 ; i <= K ; ++ i) G[K - i] = Mod - p[i] ; T[1] = G[K] = 1, reverse(G, G + K + 1), _Inv(G, IG, Len >> 1) ;
    reverse(G, G + K + 1), NTT(G, Len, 1), NTT(IG, Len, 1) ;
    while(N){
        NTT(T, Len, 1) ;
        if (N & 1) {
            NTT(F, Len, 1) ;
            for (i = 0 ; i < Len ; ++ i) F[i] = F[i] * T[i] % Mod ;
            NTT(F, Len, -1) ; _Div(F, Len) ;
        }
        for (i = 0 ; i < Len ; ++ i) (T[i] *= T[i]) %= Mod ; NTT(T, Len, -1) ; _Div(T, Len), N >>= 1 ;
    }
    for (i = 0 ; i < K ; ++ i) (Ans += (F[i] * base[i + 1]) % Mod) %= Mod ; printf("%lld\n", Ans) ; return 0 ;
}
```

---

## 作者：sunnuozhou (赞：18)

[更优阅读体验](https://sunnuozhou.github.io/2020/04/22/Berlekamp-Massey%E7%AE%97%E6%B3%95%E7%AE%80%E4%BB%8B/)

本题由BM算法和矩阵特征多项式两部分构成

# Berlekamp-Massey算法

Berlekamp-Massey算法，简称BM算法，是用来求解一个数列最短线性递推式的算法，时间复杂度为 $O(n^2)$。


## 算法流程

记数列为 $\{a_1,a_2,..,a_n\}$，只考虑 $\{a_1,a_2,..,a_i\}$的最短线性递推为 $R_i$，$a_{i+1}$ 和用 $R_i$ 推算出的下一个数的差为 $delta_i$。特别的，$R_0=\{\}$。
现在考虑如果我们已经知道了 $R_1,R_2,..R_{i-1}$，如何求 $R_i$？

- 如果 $delta_{i-1}=0$，那么显然 $R_i=R_{i-1}$

- 如果 $R_{i-1}$ 为 $\{\}$，那么 $R_i=\{0,0,..,0\}$，共 $i$ 个0。

- 否则我们需要对 $R_{i-1}$ 进行调整来得到 $R_i$。一个简单的思想是找到一个线性递推式 $R'=\{r'_1,r'_2,..,r'_k\}$ 满足 $\sum_{j=1}^kr'_j\times a_{w-j}=0$ 对所有 $k<w<i$ 成立，并且在 $i$ 处的值为 $delta_{i-1}$。那么 $R_i$ 就可以等于 $R_{i-1}+R'$。

- 一种可行的构造方案是对于 $0\le w<i-1$，可以使 $R'=\{0,0,..,0,\frac{delta_{i-1}}{delta_w},-\frac{delta_{i-1}}{delta_w}\times R_w\}$，其中0的个数为 $i-w-2$。

- 为了使 $R_i$ 最短，找到一个 $w$ 使得 $R'$ 最短即可。

其中有用的 $R_i$ 只有当前的 $R_i$ 和使 $R'$ 最短的 $R_w$，并不需要记录所有 $R_i$，空间是 $O(n)$ 的。
用这个方法生成的线性递推正确性是显然的，但我并不会证明一定是最短的。~~但是过了模板题~~



## 代码

```cpp
void BM(ll *a,int n,vector<ll>&ans){
	ans.clear();
	vector<ll> lst;
	int w=0;ll delta=0;
	for(int i=1;i<=n;i++){
		ll tmp=0;
		for(int j=0;j<ans.size();j++)
			tmp=(tmp+a[i-1-j]*ans[j])%mod;
		if((a[i]-tmp)%mod==0) continue;
		if(!w){
			w=i;delta=a[i]-tmp;
			for(int j=i;j;j--) ans.push_back(0);
			continue;
		}
		vector<ll> now=ans;
		ll mul=(a[i]-tmp)*fp(delta,mod-2)%mod;
		if(ans.size()<lst.size()+i-w) ans.resize(lst.size()+i-w);
		ans[i-w-1]=(ans[i-w-1]+mul)%mod;
		for(int j=0;j<lst.size();j++) ans[i-w+j]=(ans[i-w+j]-mul*lst[j])%mod;
		if(now.size()-i<lst.size()-w){
			lst=now;w=i;delta=a[i]-tmp;
		}
	}
}

```

# 特征多项式

## 基本概念

因为模板题要用，就顺带讲一下。

一个 $n\times n$ 矩阵A的特征多项式为$f(\lambda)=det(I_n\lambda-A)$，其中 $I_n$ 为 $n$ 阶单位矩阵，$det$ 为行列式运算。
而一个线性递推矩阵如下：
$$
A=
\left\{
	\begin{matrix}
	a_1 & a_2 & \cdots & a_{n-1} &a_n\\
	1 & 0 & \cdots & 0 & 0 \\
	\vdots & \vdots & \ddots & \vdots& \vdots \\
	0 & 0 & \cdots  & 0 & 0 \\
	0 & 0 & \cdots  & 1 & 0 \\
	\end{matrix} 
\right\}
$$
$$
f(\lambda)=
\left |
	\begin{matrix}
	\lambda-a_1 & -a_2 & \cdots & -a_{n-1} &-a_n\\
	-1 & \lambda & \cdots & 0 & 0 \\
	\vdots & \vdots & \ddots & \vdots& \vdots \\
	0 & 0 & \cdots  & \lambda & 0 \\
	0 & 0 & \cdots  & -1 & \lambda \\
	\end{matrix} 
\right|
$$

展开第一行得:

$$f(\lambda)=(\lambda-a_1)A_{1,1}+(-a_2)A_{1,2}+\cdots+(-a_n)A_{1,n}$$

其中 $A_{i,j}$ 为 $A$ 的代数余子式，显然结果为
$$f(\lambda)=\lambda^n-\sum_{i=1}^na_i\lambda^{n-i}$$


## 实用

现在考虑求递推式的第 $m$ 项，即 $A^{m-1}\times\vec H $ 的最后一项。
根据[Cayley-Hamilton定理](https://zh.wikipedia.org/wiki/凱萊–哈密頓定理)可得，$f(A)=0$

于是有
$$A^{m-1}=g(A)\times f(A)+r(A)$$
其中 $r(A)$ 的最高项次数小于 $n$。
由于 $f(A)=0$，可以得到 $A^{m-1}=r(A)$。
这里可以暴力地快速幂算出 $r(A)$，也可以使用多项式取模+快速幂的方式~~但我不会~~

现在要求的就是 $\sum_{i=0}^{n-1}r_i\times A^i \times \vec H$ 的最后一项。
其中 $A_i\times \vec H$ 的最后一项为 $H_{i+1}$。
所以
$$ans=\sum_{i=0}^{n-1}r_i\times H_{i+1}$$

时间复杂度为 $O(n^2\log m)$或$O(n\log n\log m)$

## 代码

```cpp
ll calc(int m,vector<ll>&coef,ll*h){
	if(m<=coef.size()) return h[m];
	int k=coef.size();
	static ll f[N],g[N],res[N],p[N];
	p[0]=-1;
	for(int i=1;i<=k;i++) p[i]=coef[i-1];
	for(int i=0;i<=2*k;i++) f[i]=g[i]=0;
	f[0]=1;
	if(k>1) g[1]=1;
	else g[0]=p[0];
	auto mul = [&](ll *a,ll *b,ll *c){
		for(int i=0;i<=2*k;i++) res[i]=0;
		for(int i=0;i<k;i++)
			for(int j=0;j<k;j++)
				res[i+j]=(res[i+j]+a[i]*b[j])%mod;
		for(int i=2*k;i>=k;i--)
			if(res[i]%mod)
				for(int j=k;~j;j--)
					res[i-j]=(res[i-j]+res[i]*p[j])%mod;
		for(int i=0;i<2*k;i++) c[i]=res[i];
		return 0;
	};
	for(;m;m>>=1,mul(g,g,g))
		if(m&1) mul(f,g,f);
	ll ans=0;
	for(int i=0;i<k;i++)
		ans=(ans+h[i+1]*f[i])%mod;
	return ans;
}
```

# 完整代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define lld long ll
using namespace std;
template<typename tn> void read(tn &a){
	tn x=0,f=1; char c=' ';
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0';
	a=x*f;
}
const int N = 10010,mod = 998244353;
ll h[N];
int n,m;
ll fp(ll a,ll k){
	ll ans=1;
	for(;k;k>>=1,a=a*a%mod)
		if(k&1) ans=a*ans%mod;
	return ans;
}
void BM(ll *a,int n,vector<ll>&ans){
	ans.clear();
	vector<ll> lst;
	int w=0;ll delta=0;
	for(int i=1;i<=n;i++){
		ll tmp=0;
		for(int j=0;j<ans.size();j++)
			tmp=(tmp+a[i-1-j]*ans[j])%mod;
		if((a[i]-tmp)%mod==0) continue;
		if(!w){
			w=i;delta=a[i]-tmp;
			for(int j=i;j;j--) ans.push_back(0);
			continue;
		}
		vector<ll> now=ans;
		ll mul=(a[i]-tmp)*fp(delta,mod-2)%mod;
		if(ans.size()<lst.size()+i-w) ans.resize(lst.size()+i-w);
		ans[i-w-1]=(ans[i-w-1]+mul)%mod;
		for(int j=0;j<lst.size();j++) ans[i-w+j]=(ans[i-w+j]-mul*lst[j])%mod;
		if(now.size()-i<lst.size()-w){
			lst=now;w=i;delta=a[i]-tmp;
		}
	}
}
ll calc(int m,vector<ll>&coef,ll*h){
	if(m<=coef.size()) return h[m];
	int k=coef.size();
	static ll f[N],g[N],res[N],p[N];
	p[0]=-1;
	for(int i=1;i<=k;i++) p[i]=coef[i-1];
	for(int i=0;i<=2*k;i++) f[i]=g[i]=0;
	f[0]=1;
	if(k>1) g[1]=1;
	else g[0]=p[0];
	auto mul = [&](ll *a,ll *b,ll *c){
		for(int i=0;i<=2*k;i++) res[i]=0;
		for(int i=0;i<k;i++)
			for(int j=0;j<k;j++)
				res[i+j]=(res[i+j]+a[i]*b[j])%mod;
		for(int i=2*k;i>=k;i--)
			if(res[i]%mod)
				for(int j=k;~j;j--)
					res[i-j]=(res[i-j]+res[i]*p[j])%mod;
		for(int i=0;i<2*k;i++) c[i]=res[i];
		return 0;
	};
	for(;m;m>>=1,mul(g,g,g))
		if(m&1) mul(f,g,f);
	ll ans=0;
	for(int i=0;i<k;i++)
		ans=(ans+h[i+1]*f[i])%mod;
	return ans;
}
int main(){
	read(n);read(m);
	for(int i=1;i<=n;i++)
		read(h[i]);
	vector<ll> ans;
	BM(h,n,ans);
	for(auto x:ans) cout<<(x+mod)%mod<<' ';
	cout<<'\n';
	cout<<(calc(m,ans,h)+mod)%mod<<'\n';
	return 0;
}
```



---

## 作者：Karry5307 (赞：12)

既然$\texttt{\color{black}F\color{red}lower\_pks}$抛了一块砖，那我就来引一块可能有点瑕疵的玉吧。

### 题意

给定$P_0\cdots P_n$和$m$，求$P$的最短递推式以及$P_m$。

$\texttt{Data Range:}m\leq 10^9,1\leq n\leq 10^4$

### 题解

首先讲一下$\texttt{Berlekamp-Massey Algorithm}$吧，这东西使用的是类似于拉格朗日插值的思想，所以下文会综合理解。

考虑现在的递推式$f_n=\sum\limits_{i=0}^{n-1}a_if_i$满足$P_1\cdots P_n$，但是在$P_{n+1}$这个地方萎了。怎么办？

于是我们想一种插值的方式。假设插出来的多项式已经拟合了前$n$个点，$n+1$个点萎了，就像这样

![](https://s2.ax1x.com/2019/08/07/eoSkjI.jpg)

紫色的点都被拟合了，而红色的点萎了。

这时构造一个多项式使得那些拟合上了的点的$x$坐标代入进去为$0$，并且过那个萎了的点，像这样

![](https://s2.ax1x.com/2019/08/07/eoSVDP.jpg)

把两个函数加起来，有

![](https://s2.ax1x.com/2019/08/07/eoSEut.jpg)

这样，就把那个萎了的点也拟合上去了。

按照这种方法，考虑构造递推式$g_n=\sum\limits_{i=0}^{n-1}b_ig_i$，使得在前$n$项都为$0$，而第$n+1$项为$P_{n+1}$。（其实不为$0$就好了）

于是考虑如果我们之前处理过的话，那么就可以通过这个东西简单移项得到$g$了。最近的一个肯定最优。


$\texttt{example}$什么的就不给了，可以找$\texttt{\color{black}z\color{red}{zq}}$大神的博客。

求出递推式后线性递推照样做。

### 代码

由于$\texttt{\color{black}F\color{red}lower\_pks}$这样的大神仙不屑于给出完整代码，我这种小蒟蒻看了好长时间，所以本着惠及你谷用户，考虑给出完整代码。

还有，$\texttt{\color{black}N\color{red}aCly\_Fish}$是怎么写出那么长的代码的？

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=3e5+51,MOD=998244353,G=3,INVG=332748118;
ll exponent,fd,cnt=1,limit=-1,rres,ptr;
ll rev[MAXN],f[MAXN],g[MAXN],tmp[MAXN],tmp2[MAXN],tmp3[MAXN],tbm[MAXN];
ll res[MAXN],base[MAXN],fail[MAXN];
li delta[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline ll qpow(ll base,ll exponent)
{
    li res=1;
    while(exponent)
    {
        if(exponent&1)
        {
            res=1ll*res*base%MOD;
        }
        base=1ll*base*base%MOD,exponent>>=1;
    }
    return res;
}
inline void NTT(ll *cp,ll cnt,ll inv)
{
    ll cur=0,res=0,omg=0;
    for(register int i=0;i<cnt;i++)
    {
        if(i<rev[i])
        {
            swap(cp[i],cp[rev[i]]);
        }
    }
    for(register int i=2;i<=cnt;i<<=1)
    {
        cur=i>>1,res=qpow(inv==1?G:INVG,(MOD-1)/i);
        for(register ll *p=cp;p!=cp+cnt;p+=i)
        {
            omg=1;
            for(register int j=0;j<cur;j++)
            {
                ll t=1ll*omg*p[j+cur]%MOD,t2=p[j];
                p[j+cur]=(t2-t+MOD)%MOD,p[j]=(t2+t)%MOD;
                omg=1ll*omg*res%MOD;
            }
        }
    }
    if(inv==-1)
    {
        ll invl=qpow(cnt,MOD-2);
        for(register int i=0;i<=cnt;i++)
        {
            cp[i]=1ll*cp[i]*invl%MOD;
        }
    }
}
inline void inv(ll fd,ll *f,ll *res)
{
    static ll tmp[MAXN];
    if(fd==1)
    {
        res[0]=qpow(f[0],MOD-2);
        return;
    }
    inv((fd+1)>>1,f,res);
    ll cnt=1,limit=-1;
    while(cnt<(fd<<1))
    {
        cnt<<=1,limit++;
    }
    for(register int i=0;i<cnt;i++)
    {
        tmp[i]=i<fd?f[i]:0;
        rev[i]=(rev[i>>1]>>1)|((i&1)<<limit);
    }
    NTT(tmp,cnt,1),NTT(res,cnt,1);
    for(register int i=0;i<cnt;i++)
    {
        res[i]=1ll*(2-1ll*tmp[i]*res[i]%MOD+MOD)%MOD*res[i]%MOD;
    }
    NTT(res,cnt,-1);
    for(register int i=fd;i<cnt;i++)
    {
        res[i]=0;
    }
}
inline void mod(ll *f)
{
    static ll tmp[MAXN],q[MAXN];
    ll deg=fd<<1;
    while(!f[--deg]);
    if(deg<fd)
    {
	return;
    }
    for(register int i=0;i<cnt;i++)
    {
    	tmp[i]=i<=deg?f[i]:0;
    }
    reverse(tmp,tmp+1+deg);
    for(register int i=deg+1-fd;i<=deg;i++)
    {
    	tmp[i]=0;
    }
    NTT(tmp,cnt,1);
    for(register int i=0;i<cnt;i++)
    {
    	q[i]=(li)tmp[i]*tmp3[i]%MOD;
    }
    NTT(q,cnt,-1);
    for(register int i=0;i<cnt;i++)
    {
    	tmp[i]=0;
    	q[i]=i<=deg-fd?q[i]:0;
    }
    reverse(q,q+1+deg-fd),NTT(q,cnt,1);
    for(register int i=0;i<cnt;i++)
    {
        tmp[i]=(li)q[i]*g[i]%MOD;
    }
    NTT(tmp,cnt,-1);
    for(register int i=0;i<fd;i++)
    {
        f[i]=(f[i]-tmp[i]+MOD)%MOD;
    }
    for(register int i=0;i<cnt;i++)
    {
        q[i]=tmp[i]=0,f[i]=i<fd?f[i]:0;
    }
}
vector<li>bmf[MAXN];
inline void BerlekampMassey(ll length,ll *base,ll *res)
{
	ll cur=0;
    for(register int i=1;i<=length;i++)
    {
    	li curr=base[i];
        for(register int j=0;j<bmf[cur].size();j++)
        {
            curr=(curr-(li)base[i-j-1]*bmf[cur][j]%MOD)%MOD;
        }
        delta[i]=curr;
        if(!delta[i])
        {
            continue;
        }
        fail[cur]=i;
        if(!cur)
        {
            bmf[++cur].resize(i),delta[i]=base[i];
            continue;
        } 
        ll id=cur-1,x=bmf[id].size()-fail[id]+i;
        for(register int j=0;j<cur;j++)
        {
            if(i-fail[j]+bmf[j].size()<x)
            {
            	id=j,x=i-fail[j]+bmf[j].size();
            }
        }
        bmf[cur+1]=bmf[cur],cur++;
        while(bmf[cur].size()<x)
        {
            bmf[cur].push_back(0);
        }
        li mul=(li)delta[i]*qpow(delta[fail[id]],MOD-2)%MOD;
        bmf[cur][i-fail[id]-1]=(li)(bmf[cur][i-fail[id]-1]+mul)%MOD;
        for(register int j=0;j<bmf[id].size();j++)
        {
            ll t=(li)mul*bmf[id][j]%MOD;
            bmf[cur][i-fail[id]+j]=(bmf[cur][i-fail[id]+j]-t+MOD)%MOD;
        }
    }
    ptr=cur;
    for(register int i=0;i<bmf[cur].size();i++)
    {
    	res[i+1]=(bmf[cur][i]%MOD+MOD)%MOD;
    }
} 
int main()
{
    fd=read(),exponent=read();
    for(register int i=0;i<fd;i++)
    {
    	tbm[i+1]=f[i]=(read()+MOD)%MOD;
    }
    BerlekampMassey(fd,tbm,tmp);
    for(register int i=1;i<=bmf[ptr].size();i++)
    {
    	printf("%d ",tmp[i]);
    }
    puts("");
    for(register int i=1;i<=fd;i++)
    {
    	g[fd-i]=MOD-tmp[i];
    }
    g[fd]=1;
    for(register int i=0;i<=fd;i++)
    {
    	tmp2[i]=g[i];
    }
    reverse(tmp2,tmp2+1+fd),inv(fd<<1,tmp2,tmp3);
    for(register int i=0;i<=fd;i++)
    {
    	tmp2[i]=0;
    }
    while(cnt<(fd<<2))
    {
    	cnt<<=1,limit++;
    }   
    for(register int i=0;i<cnt;i++)
    {
    	rev[i]=(rev[i>>1]>>1)|((i&1)<<limit);
    }
    NTT(g,cnt,1),NTT(tmp3,cnt,1),base[1]=res[0]=1;
    while(exponent)
    {
        if(exponent&1)
        {
            NTT(res,cnt,1),NTT(base,cnt,1);
            for(register int i=0;i<cnt;i++)
            {
                res[i]=(li)res[i]*base[i]%MOD;
            }
            NTT(res,cnt,-1),NTT(base,cnt,-1),mod(res);
        }
        NTT(base,cnt,1);
        for(register int i=0;i<cnt;i++)
        {
            base[i]=(li)base[i]*base[i]%MOD;
        }
        NTT(base,cnt,-1),mod(base),exponent>>=1;
    }
    for(register int i=0;i<fd;i++)
    {
    	rres=(rres+(li)res[i]*f[i]%MOD)%MOD;
    }
    printf("%d\n",rres);
}
```

---

## 作者：ZnPdCo (赞：9)

本题由 BM 算法和线性递推两部分组成。

# BM 算法

我们定义递推系数 $\{a_0,\cdots,a_{k-1}\}$ 满足 $f_i=\sum_{j=0}^{k-1} a_jf_{i-j-1},\forall i\ge k$。BM 算法就是给定若干 $f$，要求最短的 $\{a\}$。

考虑使用调整法。按顺序考虑 $\{f\}$ 的每一位，我们记处理到 $f_i$ 时的递推系数为 $F_i$。

显然初始时存在 $F_0=\{\}$，当我们处理到 $f_i$ 时，存在两种情况：

- 递推系数对于 $a_i$ 依旧成立，此时我们令 $F_i=F_{i-1}$；

- 递推系数对于 $a_i$ 不成立，此时我们需要对 $F_{i-1}$ 进行调整，依旧存在两种情况：

  - 当 $F_{i-1}=\{\}$ 时，也就是说这是第一次对递推系数进行修改，说明 $a_i$ 是第一个非零的情况，我们令 $F_i=\{\underbrace{0,\cdots,0}_{i个}\}$，因为此时 $k=i+1$，显然满足定义。

  - 否则，我们可以考虑类似于拉格朗日插值的方法，假设当前的误差 $\Delta i=f_i-\sum_{j=0}^{k-1} a_jf_{i-j-1}$，那么原本的递推系数就是在 $x<i$ 时取值为 $0$ 但在 $x=i$ 时取值为 $\Delta i$ 的。我们构造一个在 $x<i$ 时取值为 $0$ 但在 $x=i$ 时取值为 $-\Delta i$ 的递推系数，两个递推系数相加即可得到一个在 $x\le i$ 时取值都为 $0$ 的递推系数，使得满足题目条件。

    考虑怎么构造，我们设上一次调整的位置是 $k$，且上一次调整时的误差是 $\Delta k$。我们构造新的递推系数 $G=\{\underbrace{0,0,0,0}_{i-k-1个},\dfrac{\Delta i}{\Delta k},-\dfrac{\Delta i}{\Delta k}F_{k-1}\}$，后面的 $-\dfrac{\Delta i}{\Delta k}F_{k-1}$ 表示将 $F_{k-1}$ 每项乘以 $-\dfrac{\Delta i}{\Delta k}$ 接在后面。

    不难验证此时 $G$ 在 $x=i$ 时取值为 $-\Delta i$。两系数相加即可。

    由于我们要求最短递推式，所以我们希望 $\text{len}(F_{k})-k$ 尽量短，我们选择最小的 $k$ 以及它的 $F$ 与 $\Delta$ 储存即可。

时间复杂度 $O(n^2)$，空间复杂度 $O(n)$。

# 线性递推

我们将 $f_m=\sum_{i=0}^{k-1} a_jf_{m-i-1}$ 的每一项展开，有：
$$
f_{m-i-1}=\sum_{j=0}^{k-1} a_jf_{m-i-1-j-1}
$$
带入并整理得：
$$
f_m=\sum_{i=0}^{k-1}\sum_{j=0}^{k-1} a_ia_jf_{m-i-j-2}
$$
得：
$$
f_m=\sum_{x=0}^{2k-2}\sum_{i+j=x} a_ia_jf_{m-x-2}
$$
我们发现各项展开后，$f_m$ 可以通过 $f_{m-2},\cdots,f_{m-2k}$ 表示。

我们对 $f_{m-i},\forall 2\le i\le k$ 展开，并将系数向上式代入，最终就能把原递推式通过 $f_{m-k-1},\cdots,f_{m-2k}$ 这 $k$ 项表示。

于是我们就得到了新的 $k$ 阶递推式。

最后再用新得递推式将各项展开，以此类推，最后得出 $f_m$ 用 $f_{m-(n-1)k-1},\cdots,f_{m-nk}$ 表示出来的结果，其中 $m-nk<k$。因为 $m-(n-1)k-1$ 可能会超过 $k$，但再往前推是没有必要且更麻烦的，因为 $m-(n-1)k-1<2k$，在最开始时暴力算出 $f_k,\cdots,f_{2k-1}$ 就可以了。

以上过程可以用快速幂维护。时间复杂度 $O(n^2\log n)$。虽说不是最优的，但过这题够了。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define P 998244353
#define N 10010
using namespace std;
ll n, m, q;
ll qpow(ll x, ll y) {
	if(y == 0) return 1;
	if(y % 2 == 1) return x * qpow(x, y - 1) % P;
	ll tmp = qpow(x, y / 2);
	return tmp * tmp % P;
}
vector<ll> bm(vector<ll> f) {
	vector<ll> v, last;
	ll k = -1, delta = 0;
	for(int i = 0; i < (ll)f.size(); i ++) {
		ll tmp = 0;
		for(ll j = 0; j < (ll)v.size(); j ++) {
			(tmp += f[i - j - 1] * v[j] % P) %= P;
			if(tmp < 0) tmp += P;
		}
		
		if(f[i] == tmp) continue;
		
		if(k == -1) {
			k = i;
			delta = (f[i] - tmp) % P;
			if(delta < 0) delta += P;
			v = vector<ll>(i + 1);
			
			continue;
		}
		
		vector<ll> u = v;
		ll val = ((f[i] - tmp) % P + P) % P * qpow(delta, P - 2) % P;
		
		if(v.size() < last.size() + i - k) v.resize(last.size() + i - k);
		
		(v[i - k - 1] += val) %= P;
		
		for(ll j = 0; j < (ll)last.size(); j ++) {
			(v[i - k + j] -= val * last[j] % P) %= P;
			if(v[i - k + j] < 0) v[i - k + j] += P;
		}
		
		if((ll)u.size() - i < (ll)last.size() - k) {
			last = u;
			k = i;
			delta = (f[i] - tmp) % P;
			if(delta < 0) delta += P;
		}
	}
	return v;
}

vector<ll> mul(vector<ll> x, vector<ll> y, vector<ll> a) {
	vector<ll> res(2 * q);
	vector<ll> tmp(2 * q);
	
	for(ll i = 0; i < q; i ++) {
		for(ll j = 0; j < q; j ++) {
			(tmp[i + j] += x[i] * y[j] % P) %= P;
		}
	}
	
	for(ll i = 0; i < q - 1; i ++) {
		for(ll j = 0; j < q; j ++) {
			(tmp[i + j + 1] += tmp[i] * a[j] % P) %= P;
		}
	}
	
	for(ll i = 0; i < q; i ++) {
		res[i] = tmp[i + q - 1];
	}
	
	return res;
}

ll linear_recurrence(vector<ll> f, vector<ll> a) {
	if(m < q * 2) {
		return f[m];
	}
	
	vector<ll> x = a, w = a;
	
	ll t = (m - q) / q, rem = (m - q) % q;
	while(t) {
		if(t & 1)
			w = mul(w, x, a);
		x = mul(x, x, a);
		t /= 2;
	}
	
	ll res = 0;
	for(ll i = 0; i < q; i ++) {
		(res += w[i] * f[rem + q - i - 1] % P) %= P;
		if(res < 0) res += P;
	}
	
	return res;
}
int main() {
	scanf("%lld %lld", &n, &m);
	vector<ll> f(n);
	for(ll i = 0; i < n; i ++) {
		scanf("%lld", &f[i]);
	}
	auto a = bm(f);
	q = a.size();
	for(ll i = 0; i < q; i ++) {
		printf("%lld ", a[i]);
	}
	printf("\n");
	for(ll i = n; i < q * 2; i ++) {
		f.push_back(0);
		for(ll j = 0; j < q; j ++) {
			(f[i] += a[j] * f[i - j - 1] % P) %= P;
			if(f[i] < 0) f[i] += P;
		}
	}
	printf("%lld", linear_recurrence(f, a));
}
```

---

## 作者：Aleph1022 (赞：8)

参考自[ EI 的文章](https://blog.csdn.net/EI_Captain/article/details/115840021?spm=1001.2014.3001.5501)。

首先一个重要的条件是观测讨论区可知此题最短递推式长度 $\le n/2$（否则最短递推式是可能不唯一的）。

那么容易知道，对于给定的有理分式 $f$ 的前 $2n$ 项，我们只需要给出一组 $p/q \equiv f \pmod{x^{2n}}$，其中 $\deg p < n,\deg q \le n$ 即可正确拟合。

接下来考虑将问题**适当泛化**为「**有理函数重建**」问题：  
> 给定域上的多项式 $f(x),M(x)$，设 $\deg M = n$，对于多项式 $p,q$ 满足 $\deg p < k,\deg q \le n-k$ 且 $p\equiv qf \pmod M$，称 $p,q$ 是 $f$ 的一个 $(k,n-k)$ 有理逼近。

可以发现，在这题里我们令 $M(x)=x^{2n}$，求出一组 $(n,n)$ 有理逼近即可。

接下来考虑如何解决这个问题。类似熟知的欧几里得算法，将同余式改写为方程 $p=qf+Mt$，然后考虑仿照欧几里得算法的过程：  
一开始我们有
$$
\begin{bmatrix}f\\M\end{bmatrix}=\begin{bmatrix}1&0\\0&1\end{bmatrix}\begin{bmatrix}f\\M\end{bmatrix}
$$

过程中，考虑某个时刻的状态是
$$
\begin{bmatrix}A\\B\end{bmatrix}=\begin{bmatrix}X_A&Y_A\\X_B&Y_B\end{bmatrix}\begin{bmatrix}f\\M\end{bmatrix}
$$

设 $k=\deg A+1,m=\deg B$，那么不妨**归纳假设** $\deg X_A,\deg X_B \le n-k$，即 $A,X_A$ 是一组 $(k,n-k)$ 有理逼近。  
接下来尝试将 $A$ 取模 $B$，令 $d$ 为商数，则自然有 $\deg d < k-m$。  
而接下来只需首先令 $(X_A,X_B)$ 变为 $(X_A-dX_B,X_B)$，度数均  $<n-m$。当然，接下来还需要交换 $A,B$ 和 $X_A,X_B$。

那么我们必然会找到某个时刻使得 $\deg A < n/2,\deg X_A \le n/2$，在此刻停止即可。

事实上通过 HALF-GCD 算法，我们还可以实现 $\Theta(n \log^2 n)$ 的 BM（甚至也可以求出任意阶段的有理逼近）！

顺便贴一个自己用的暴力代码：
```cpp
#include <cstdio>
#include <vector>
#include <utility>

using namespace std;

typedef long long ll;

const int mod = 998244353;
inline int norm(int x) {
  return x >= mod ? x - mod : x;
}
inline int reduce(int x) {
  return x < 0 ? x + mod : x;
}
inline int neg(int x) {
  return x ? mod - x : 0;
}
inline void add(int &x, int y) {
  if ((x += y - mod) < 0)
    x += mod;
}
inline void sub(int &x, int y) {
  if ((x -= y) < 0)
    x += mod;
}
inline void fam(int &x, int y, int z) {
  x = (x + (ll)y * z) % mod;
}
inline int qpow(int a, int b) {
  int ret = 1;
  for (; b; b >>= 1)
    (b & 1) && (ret = (ll)ret * a % mod),
    a = (ll)a * a % mod;
  return ret;
}

int n, m;
vector<int> base;

pair<vector<int>, vector<int>> berlekampMassey(int n, const vector<int> &base) {
  vector<int> u(n * 2 + 1), v(n * 2), x, y(1, 1);
  u[n * 2] = 1;
  for (int i = 0; i < v.size(); ++i)
    v[i] = base[i];
  while (1) {
    while (!v.empty() && !v.back())
      v.pop_back();
    if (v.size() - 1 < n && y.size() - 1 <= n)
      break;
    x.resize(max(x.size(), u.size() - v.size() + y.size()));
    int t = neg(qpow(v.back(), mod - 2));
    for (int i = u.size() - v.size(); i >= 0; --i) {
      int c = (ll)t * u[i + v.size() - 1] % mod;
      for (int j = 0; j < y.size(); ++j)
        fam(x[i + j], c, y[j]);
      for (int j = 0; j < v.size(); ++j)
        fam(u[i + j], c, v[j]);
    }
    swap(u, v), swap(x, y);
  }
  int inv = qpow(y[0], mod - 2);
  for (int i = 0; i < y.size(); ++i)
    y[i] = (ll)y[i] * inv % mod;
  for (int i = 0; i < v.size(); ++i)
    v[i] = (ll)v[i] * inv % mod;
  return make_pair(v, y);
}

int bostanMori(int n, vector<int> p, vector<int> q) {
  p.resize(q.size() - 1);
  vector<int> u(p.size()), v(q.size());
  for (; n; n >>= 1) {
    for (int i = 0; i < v.size(); ++i) {
      v[i] = 0;
      int id = i << 1;
      for (int j = 0; j <= id; ++j)
        if (j < q.size() && id - j < q.size())
          fam(v[i], j & 1 ? neg(q[j]) : q[j], q[id - j]);
    }
    for (int i = 0; i < u.size(); ++i) {
      u[i] = 0;
      int id = (i << 1) | (n & 1);
      for (int j = 0; j <= id; ++j)
        if (j < q.size() && id - j < p.size())
          fam(u[i], j & 1 ? neg(q[j]) : q[j], p[id - j]);
    }
    p = u, q = v;
  }
  return (ll)p[0] * qpow(q[0], mod - 2) % mod;
}
inline int bostanMori(int n, pair<vector<int>, vector<int>> f) {
  return bostanMori(n, f.first, f.second);
}

int main() {
  scanf("%d%d", &n, &m);
  vector<int> base(n);
  for (int i = 0; i < n; ++i)
    scanf("%d", &base[i]);
  auto f = berlekampMassey(n >> 1, base);
  auto q = f.second;
  for (int i = 1; i < q.size(); ++i)
    printf("%d%c", neg(q[i]), " \n"[i == q.size() - 1]);
  printf("%d\n", bostanMori(m, f));
}
```

---

## 作者：gxy001 (赞：3)

对于数列 $\{a_0,a_1 \dots\}$，存在有限数列 $\{r_0,r_1\dots r_{m-1}\}$，使得 $p\ge m-1,\sum\limits_{i=0}^{m-1}r_ia_{p-i}=0$，那么我们称数列 $r$ 为数列 $a$ 的线性递归式，若 $r_0=1$，则称 $r$ 为线性递推式，称其阶数为 $m-1$。

容易发现，如果设 $r$ 的生成函数为 $R$，设 $a$ 的生成函数为 $A$，设 $S=AR$，则 $S$ 的次数不超过 $m-2$。

### Berlekamp-Massey 算法

已知数列 $\{a_0,a_1\dots a_{n-1}\}$，Berlekamp-Massey 算法会对其每个前缀 $\{a_0,a_1\dots a_i\}$ 求出这一前缀的最短线性递推式 $r^{(i)}$，我们设 $|r^{(i)}|-1=l_i$，即 $l_i$ 为线性递推式 $r^{(i)}$ 的阶，显然有 $l_{i-1}\le l_i$。我们令 $r^{(-1)}=\{1\}$。

### 算法流程

**引理**：若 $r^{(i-1)}$ 不是 $\{a_0,a_1,a_2\dots a_i\}$ 的线性递推式，那么有 $l_i\ge i+1-l_{i-1}$。

**证明**：反证法，设 $l_i\le i-l_{i-1}$，设 $r^{(i-1)}=\{p_0,p_1\dots p_{l_{i-1}}\},r^{(i)}=\{q_0,q_1\dots q_{l_i}\}$。

我们有 $l_i\le j\le i,a_j=-\sum\limits_{t=1}^{l_i}q_ta_{j-t}$。

由于 $l_i\le i-l_{i-1}$，我们可以做出如下变换。

$$
\begin{aligned}
-\sum\limits_{j=1}^{l_{i-1}}p_ja_{i-j}&=\sum\limits_{j=1}^{l_{i-1}}p_j\sum\limits_{k=1}^{l_i}q_ka_{i-j-k}\\
&=\sum\limits_{k=1}^{l_i}q_k\sum\limits_{j=1}^{l_{i-1}}p_ja_{i-j-k}\\
&=-\sum\limits_{k=1}^{l_i}q_ka_{i-k}\\
&=a_i
\end{aligned}
$$

所以 $r^{(i-1)}$ 是 $\{a_0,a_1,a_2\dots a_i\}$ 的线性递推式，矛盾。

于是，我们有 $l_i\ge \max(i+1-l_{i-1},l_{i-1})$。

下面给出一种构造使得 $l_i=\max(i+1-l_{i-1},l_{i-1})$，显然这样的 $r^{(i)}$ 即为 $\{a_0,a_1,a_2\dots a_i\}$ 的最短线性递推式。

如果 $r^{(i-1)}$ 是 $\{a_0,a_1,a_2\dots a_i\}$ 的线性递推式，$r^{(i)}=r^{(i-1)}$。

否则，我们设 $a$ 的生成函数为 $A$，$r^{(i)}$ 的生成函数为 $R^{(i)}$，设 $S^{(i)}\equiv AR^{(i)}\pmod{x^{i+1}}$，则有 $S^{(i)}$ 的次数不超过 $l_i-1$，即 $R^{(i)}$ 的次数 $-1$。

考虑由 $R^{(i-1)}$ 推出 $R^{(i)}$，由于 $r^{(i-1)}$ 不是 $\{a_0,a_1,a_2\dots a_i\}$ 的线性递推式，我们有 $AR^{(i-1)}\equiv S^{(i-1)}+dx^i\pmod{x^{i+1}}$。

若 $0\le j< i,l_j=0$，我们令 $r^{(i)}=\{1,0\dots 0\}$，此处有 $i+1$ 个 $0$，显然满足 $l_i=i+1-l_{i-1}$。

否则我们考虑上一次 $l_p>l_{p-1}$ 的情形，设当时的情况为 $AR^{(p-1)}\equiv S^{(p-1)}+cx^p\pmod{x^{p+1}}$，给两侧分别乘上 $x^{i-p}dc^{-1}$，那么有 $x^{i-p}dc^{-1}AR^{(p-1)}\equiv x^{i-p}dc^{-1}S^{(p-1)}+dx^i\pmod {x^{i+1}}$。

两式相减可以得到 $A(R^{(i-1)}-x^{i-p}dc^{-1}R^{(p-1)})\equiv S^{(i-1)}-x^{i-p}dc^{-1}S^{(p-1)}\pmod {x^{i+1}}$。

显然 $S^{(i-1)}-x^{i-p}dc^{-1}S^{(p-1)}$ 的次数不超过 $R^{(i-1)}-x^{i-p}dc^{-1}R^{(p-1)}$ 的次数 $-1$。

所以我们令 $R^{(i)}=R^{(i-1)}-x^{i-p}dc^{-1}R^{(p-1)}$ 即可。

由归纳法，我们设 $l_p=\max(l_{p-1},p+1-l_{p-1})$，由于 $l_p>l_{p-1}$，所以 $l_p=p+1-l_{p-1}$，那么 $l_i=\max(l_{i-1},i-p+l_{p-1})=\max(l_{i-1},i+1-l_p)=\max(l_{i-1},i+1-l_{i-1})$。

时间复杂度 $O(n^2)$。

**引理**：对于一个无限数列，若我们已知其线性递推式阶数不超过 $s$，则只需取 $\{a_0,a_1\dots a_{2s-1}\}$ 的最短线性递推式即可。

**证明**：反证，令 $t$ 为最小的满足 $t\ge 2s,r^{(t)}\ne r^{(2s-1)}$ 的数，由上一个引理，我们就有 $l_t\ge t+1-l_{2s-1}\ge t+1-s\ge 2s+1-s\ge s+1$，矛盾。

### 线性递推数列的单点求值

设数列 $\{a_0,a_1\dots \}$ 的线性递推式为 $\{r_0,r_1\dots r_{m-1}\}$，我们现在要求解 $a_n$。

我们需要已知 $a_0,a_1\dots a_{m-2}$。

设 $F(x)=\sum\limits_{i=0}^{m-1}r_ix^{m-1-i}$，$G(x)=x^n\bmod F(x)=\sum\limits_{i=0}^{m-2}g_ix^i$。

则答案为 $\sum\limits_{i=0}^{m-2}g_ia_i$。

时间复杂度 $O(m\log m\log n)$ 或 $O(m^2\log n)$，取决于是否使用 FFT 加速卷积。

```cpp
#include<iostream>
using std::cin;
using std::cout;
int const mod=998244353;
int pow(int x,int y){
	int res=1;
	while(y){
		if(y&1) res=1ll*res*x%mod;
		x=1ll*x*x%mod,y>>=1;
	}
	return res;
}
int n,m,r[5010],a[10010],len;
int bm(int *a,int n,int *r){
	int len=1,p=0,clen=0,dt=0;
	static int cr[5010];
	r[0]=1;
	for(int i=0;i<n;i++){
		int d=0;
		for(int j=0;j<len;j++) d=(d+1ll*a[i-j]*r[j])%mod;
		if(d==0) continue;
		if(len==1){
			len=i+2,p=i,cr[0]=1,clen=1,dt=d;
			continue;
		}
		int u=1ll*d*pow(dt,mod-2)%mod;
		if(i-p+clen>len){
			static int pr[5010];
			for(int i=0;i<len;i++) pr[i]=r[i];
			for(int j=0;j<clen;j++) pr[i-p+j]=(pr[i-p+j]-1ll*cr[j]*u%mod+mod)%mod;
			for(int i=0;i<len;i++) cr[i]=r[i];
			int tmp=clen;
			clen=len,dt=d;
			len=i-p+tmp;
			p=i;
			for(int i=0;i<len;i++) r[i]=pr[i];
		}else for(int j=0;j<clen;j++) r[i-p+j]=(r[i-p+j]-1ll*cr[j]*u%mod+mod)%mod;
	}
	return len-1;
} 
int getans(int *r,int len,int m,int *a){
	static int x[20010],res[20010];
	x[1]=1,res[0]=1;
	if(len==1) x[0]=1ll*(mod-x[1])*r[1]%mod,x[1]=0;
	int t=2*len-2;
	auto mul=[&t,&len](int *a,int *b,int *p){
		static int tmp[20010];
		for(int i=0;i<=t;i++) tmp[i]=0;
		for(int i=0;i<len;i++) for(int j=0;j<len;j++) tmp[i+j]=(tmp[i+j]+1ll*a[i]*b[j])%mod;
		for(int i=0;i<=t;i++) a[i]=tmp[i];
		for(int i=t;i>=len;i--){
			int u=(mod-a[i])%mod;
			a[i]=0;
			for(int j=1;j<=len;j++) a[i-j]=(a[i-j]+1ll*u*p[j])%mod;
		}
	};
	while(m){
		if(m&1) mul(res,x,r);
		mul(x,x,r);
		m>>=1;
	}
	int ans=0;
	for(int i=0;i<len;i++) ans=(ans+1ll*a[i]*res[i])%mod;
	return ans;
}
int main(){
	std::ios::sync_with_stdio(false),cin.tie(nullptr);
	cin>>n>>m;
	for(int i=0;i<n;i++) cin>>a[i];
	len=bm(a,n,r);
	for(int i=1;i<=len;i++) cout<<(mod-r[i])%mod<<' ';
	cout<<'\n'<<getans(r,len,m,a)<<'\n';
	return 0;
}
```



---

