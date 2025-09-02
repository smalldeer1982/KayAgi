# Team Work

## 题目描述

You have a team of $ N $ people. For a particular task, you can pick any non-empty subset of people. The cost of having $ x $ people for the task is $ x^{k} $ .

Output the sum of costs over all non-empty subsets of people.

## 说明/提示

In the first example, there is only one non-empty subset $ {1} $ with cost $ 1^{1}=1 $ .

In the second example, there are seven non-empty subsets.

\- $ {1} $ with cost $ 1^{2}=1 $

\- $ {2} $ with cost $ 1^{2}=1 $

\- $ {1,2} $ with cost $ 2^{2}=4 $

\- $ {3} $ with cost $ 1^{2}=1 $

\- $ {1,3} $ with cost $ 2^{2}=4 $

\- $ {2,3} $ with cost $ 2^{2}=4 $

\- $ {1,2,3} $ with cost $ 3^{2}=9 $

The total cost is $ 1+1+4+1+4+4+9=24 $ .

## 样例 #1

### 输入

```
1 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 2
```

### 输出

```
24
```

# 题解

## 作者：NaCly_Fish (赞：60)

~~嗯，你看这群人，才推出 $\Theta(k \log k)$ 就不往下了，真是太逊了~~

提供一种时间复杂度 $\Theta(k)$ 的做法。

$$\sum_{i=0}^n \binom ni i^k$$
将 $i^k$ 用第二类 Stirling 数展开
$$=\sum_{i=0}^n \binom ni \sum_{j=1}^k \begin{Bmatrix} k \\ j \end{Bmatrix}i^{\underline j}$$
$$=\sum_{j=1}^k \begin{Bmatrix} k \\ j \end{Bmatrix}j! \sum_{i=0}^n \binom ni \binom ij$$
$$=\sum_{j=1}^k \begin{Bmatrix} k \\ j \end{Bmatrix}j! \sum_{i=0}^n \binom nj \binom{n-j}{i-j}$$
$$=\sum_{j=1}^k \begin{Bmatrix} k \\ j \end{Bmatrix}j! \binom nj \sum_{i=0}^{n-j} \binom{n-j}{i}$$
$$=\sum_{j=1}^k \begin{Bmatrix} k \\ j \end{Bmatrix} j! \binom{n}{j} 2^{n-j}$$
很多人推到这里就停了，因为一行第二类 Stirling 数可以很容易的用一次卷积计算；但将其进一步展开，就可以做到更优的复杂度。

在 $n > k$ 的时候，原式等于
$$\sum_{j=1}^k \binom nj 2^{n-j} \sum_{i=1}^j \binom jii^k(-1)^{j-i}$$
~~使用魔法~~ 交换一下求和顺序
$$=\sum_{i=1}^k i^k\sum_{j=i}^k \binom nj\binom ji 2^{n-j}(-1)^{j-i}$$
$$=\sum_{i=1}^k i^k\binom ni \sum_{j=i}^k  \binom{n-i}{j-i}2^{n-j}(-1)^{j-i}$$
$$=\sum_{i=1}^k \binom ni i^k 2^{n-i}\sum_{j=0}^{k-i} \binom{n-i}{j} \left( - \frac 12\right)^j$$
设 $f_i$ 为后面那个和式的值，考虑递推：  
（为了方便下面表示，设 $w=-0.5$）

$$f_{i}-f_{i+1}$$
$$= \left(\sum_{j=0}^{k-i} \binom{n-i}{j} w^j \right)-\left( \sum_{j=0}^{k-i-1} \binom{n-i-1}{j}w^j\right)$$
把前一个和式中 $j=k-i$ 的项提出来，其他的并进去
$$= \binom{n-i}{k-i}w^{k-i}+ \sum_{j=0}^{k-i-1} \left( \binom{n-i}{j} - \binom{n-i-1}{j}\right) w^j$$
$$=\binom{n-i}{k-i}w^{k-i}+\sum_{j=0}^{k-i-1} \binom{n-i-1}{j-1} w^j$$
$$= \binom{n-i}{k-i}w^{k-i}+w\sum_{j=0}^{k-i-2} \binom{n-i-1}{j}w^j$$
再把那个和式最后缺的一项补回来
$$=\binom{n-i}{k-i} w^{k-i}+w \left( f_{i+1}-\binom{n-i-1}{k-i-1}w^{k-i-1}\right)$$
$$=\binom{n-i}{k-i} w^{k-i}+wf_{i+1}-\binom{n-i-1}{k-i-1}w^{k-i}$$
$$= \binom{n-i-1}{k-i}w^{k-i}+wf_{i+1}$$
于是得到递推式
$$f_i=(w+1)f_{i+1} + \binom{n-i-1}{k-i}w^{k-i}$$
递推处理组合数，再线性筛出 $i^k$，就可以做到严格的 $\Theta(k)$ 了。

```cpp
#pragma GCC optimize ("unroll-loops")
#pragma GCC optimize (2)
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#define N 5007
#define ll long long
#define p 1000000007
#define reg register
using namespace std;
 
inline int power(int a,int t){
    int res = 1;
    while(t){
        if(t&1) res = (ll)res*a%p;
        a = (ll)a*a%p;
        t >>= 1;
    }
    return res;
}
 
int n,m,k,cnt;
int f[N],inv[N],pw[N],pr[N>>1],c[N];
 
int solve1(){
    int res = 0;
    for(reg int i=1;i<=n;++i) res = (res+(ll)c[i]*pw[i])%p;
    return res;
}
 
const int w = 500000003;
 
int solve2(){
    int c2,mul,res = 0;
    mul = c2 = f[k] = 1;
    for(reg int i=k-1;i;--i){
        c2 = (ll)c2*(n-i-1)%p*inv[k-i]%p;
        mul = (ll)mul*w%p;
        f[i] = ((ll)c2*mul+(ll)(w+1)*f[i+1])%p;
    }
    mul = p-w;
    for(reg int i=1;i<=k;++i){
        res = (res+(ll)pw[i]*c[i]%p*mul%p*f[i])%p;
        mul = (ll)mul*(p-w)%p;
    }
    res = (ll)res*power(2,n)%p;
    return res;
}
 
int main(){
    scanf("%d%d%d",&n,&k);
    c[0] = inv[1] = pw[1] = 1;
    c[1] = n;
    for(reg int i=2;i<=k+1;++i){
        inv[i] = (ll)(p-p/i)*inv[p%i]%p;
        c[i] = (ll)c[i-1]*inv[i]%p*(n-i+1)%p;
        if(!pw[i]){
            pr[++cnt] = i;
            pw[i] = power(i,k);
        }
        for(reg int j=1;j<=cnt&&i*pr[j]<=k;++j){
            pw[i*pr[j]] = (ll)pw[i]*pw[pr[j]]%p;
            if(i%pr[j]==0) break;
        }
    }
    if(n<=k+1) printf("%d",solve1());
    else printf("%d",solve2());
    return 0;	
}
```

~~CF1278F 和这题其实是一个做法，双倍经验~~

---

## 作者：Great_Influence (赞：21)

数论推式子。

$\sum\limits_{i=1}^nC(n,i)i^k$

$=\sum\limits_{i=0}^nC(n,i)i^k$

$=\sum\limits_{i=0}^n\frac{n!}{i!(n-i)!}\sum\limits_{j=0}^kS(k,j)C(i,j)j!$

$=\sum\limits_{i=0}^n\frac{n!}{(n-i)!}\sum\limits_{j=0}^kS(k,j)\frac{1}{(i-j)!}$

$=\sum\limits_{i=0}^n\sum\limits_{j=0}^kS(k,j)\frac{n!}{(n-i)!(i-j)!}$

$=\sum\limits_{j=0}^kS(k,j)\sum\limits_{i=0}^n\frac{(n-j)!}{(n-i)!(i-j)!}*\frac{n!}{(n-j)!}$

$=\sum\limits_{j=0}^kS(k,j)\frac{n!}{(n-j)!}\sum\limits_{i=0}^n C(n-j,n-i)$

$=\sum\limits_{j=0}^kS(k,j)\frac{n!}{(n-j)!}2^{n-j}$

(其中$S(i,j)$表示第二类斯特林数)

此时即可$O(k^2)$预处理第二类斯特林数，在$O(k)$计算即可。

注意第1步。当k=0时，根据后面的计算，$0^0$被算为1，需要在最后减去。

代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#define Rep(i,a,b) for(register int i=(a),i##end=(b);i<=i##end;++i)
#define Repe(i,a,b) for(register int i=(a),i##end=(b);i>=i##end;--i)
#define For(i,a,b) for(i=(a),i<=(b);++i)
#define Forward(i,a,b) for(i=(a),i>=(b);--i)
template<typename T>inline void read(T &x)
{
	T f=1;x=0;char c;
	for(c=getchar();!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=x*10+(c^48);
	x*=f;
}
using namespace std;
void file()
{
#ifndef ONLINE_JUDGE
	freopen("dt.in","r",stdin);
	freopen("dt.out","w",stdout);
#endif
}
static int n,k;
const int mod=1e9+7;
const int MAXN=5e3+7;
static int S[MAXN][MAXN];
inline void predone(int lim)
{
	S[0][0]=1;
	Rep(i,1,lim)Rep(j,1,i)
		S[i][j]=(S[i-1][j-1]+1ll*S[i-1][j]*j%mod)%mod;
}
static int ans;
inline int power(int a,int b)
{
	static int sum;
	for(sum=1;b;b>>=1,a=1ll*a*a%mod)if(b&1)
		sum=1ll*sum*a%mod;
	return sum;
}
int main()
{
	file();
	read(n);read(k);
	predone(k);
	static int lag=1,p2=power(2,n),inv2=power(2,mod-2);
	Rep(i,0,k)
	{
		ans=(ans+1ll*lag*S[k][i]%mod*p2%mod)%mod;
		lag=1ll*lag*(n-i)%mod;
		p2=1ll*p2*inv2%mod;
	}
	if(!k)--ans;
	printf("%d\n",ans);
	return 0;
}


```

---

## 作者：litble (赞：13)

将原题看作：有$n$个箱子，从中选出$i$个箱子，然后把$k$个不同的球装在这$i$个箱子中，求方案数。

发现$k$个球最多装在$k$个箱子里，会有很多空箱，所以设$f(i,j)$表示$i$个球装在$j$个箱子里，没有空箱的方案数，那么答案会变成：
$$\sum_{i=1}^k f(k,i)2^{n-i}$$

这样一个$f(i,j)$让我们想起第二类斯特林数。当然，选择哪$j$个箱子还有待确定，所以答案就是：
$$\sum_{i=1}^k S(k,i)\frac{n!}{(n-k)!} 2^{n-i}$$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define RI register int
const int mod=1000000007;
int n,K,ans;
int S[5005][5005];
int ksm(int x,int y) {
	int re=1;
	for(;y;y>>=1,x=1LL*x*x%mod) if(y&1) re=1LL*re*x%mod;
	return re;
}
void prework() {
	S[0][0]=1;
	for(RI i=1;i<=K;++i)
		for(RI j=1;j<=i;++j)
			S[i][j]=(S[i-1][j-1]+1LL*j*S[i-1][j]%mod)%mod;
}
int main()
{
	scanf("%d%d",&n,&K),prework();
	for(RI i=1;i<=n&&i<=K;++i) {
		int kl=1LL*S[K][i]*ksm(2,n-i)%mod;
		for(RI j=n-i+1;j<=n;++j) kl=1LL*kl*j%mod;
		ans=(ans+kl)%mod;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Iratis (赞：12)

### 正文

题目想要求出如下式子：

$$ \sum_{i=1}^n\binom n i \times i^k $$

我们发现这很像二项式定理的分支：

$$ (x+1)^n=\sum_{i=0}^n\binom n i  x^i $$

对于上面的式子，似乎只需要反复求导提出 $ i $ 即可，于是我们来试一试：

$$ n(x+1)^{n-1}=\sum_{i=0}^n\binom n i i\times x^{i-1}  $$

两边同时乘上 $ x $。

$$ nx(x+1)^{n-1}=\sum_{i=0}^n\binom n i i\times x^i $$

再次进行求导：

$$ n(x+1)^{n-1}+n(n-1)x(x+1)^{n-2}=\sum_{i=0}^n\binom n i i^2\times x^{i-1} $$

有点规律，重复上面的操作：

$$ LHS=n(x+1)^{n-1}+n(n-1)x(x+1)^{n-2}+2n(n-1)x(x+1)^{n-2}+n(n-1)(n-2)x^2(x+1)^{n-2} $$

$$ LHS=n(x+1)^{n-1}+3n(n-1)x(x+1)^{n-2}+n(n-1)(n-2)x^2(x+1)^{n-2} $$

$$ RHS=\sum_{i=0}^n\binom n i i^3\times x^{i-1} $$

我们发现每次求导后，左式会增加一个多项式，而这一轮中的左式显然存在规律，我们只需要计算好系数即可。

假设经过 $ k $ 次求导后左式为 $ \sum_{i=1}^k a_i\times n^{\underline{i}}\times x^{i-1}\times (x+1)^{n-i} $

乘上 $ x $ 后得 $ \sum_{i=1}^k a_i\times n^{\underline{i}}\times x^i\times (x+1)^{n-i} $

我们想要推到至 $ k+1 $ 的左式 $ \sum_{i=1}^{k+1} b_i\times n^{\underline{i}}\times x^{i-1}\times (x+1)^{n-i} $

容易发现此时第 $ i $ 项求导会变为 $ a_i\times i\times n^{\underline{i}}\times x^{i-1}\times (x+1)^{n-i}+a_i\times n^{\underline{i+1}}\times x^i\times (x+1)^{n-i-1} $

所以推出 $ b $ 数组关于 $ a $ 数组的递推式：$ b_i=a_i\times i+a_{i-1} $。

所以系数问题我们也解决了。

最后一步，代入 $ x=1 $，发现右式为 $ \sum_{i=0}^n\binom n i i^k $。

发现这个式子在 $ i=0 $ 是答案为 $ 0 $，所以即为题目所求式。

那么答案即为 $ \sum_{i=1}^k a_i\times n^{\underline{i}}\times 2^{n-i} $。

代码如下：

```cpp
#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
#define int long long
#define md(a) a=(a%mod+mod)%mod
#define file(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
const int N=5005,mod=1e9+7;
int n,ned,a[N],b[N],fac[N],inv[N],upd,ans,mul=1;
int qp(int a,int n)
{
	if(n==0)return 1;int p=qp(a,n/2);p=p*p%mod;
	if(n&1)return p*a%mod;return p;
}
void init()
{
	fac[0]=1,upd=5000;
	for(int i=1;i<=upd;i++)fac[i]=fac[i-1]*i%mod;
	inv[upd]=qp(fac[upd],mod-2);
	for(int i=upd-1;i>=0;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int n,int m){if(n<m)return 0;return fac[n]*inv[m]%mod*inv[n-m]%mod;}
void pl(int x)
{
	for(int i=1;i<=x;i++)b[i]=a[i-1]%mod+i*a[i]%mod,b[i]%=mod;
	for(int i=1;i<=x;i++)a[i]=b[i];
}
signed main()
{
	cin>>n>>ned,init(),a[1]=1;
	for(int i=2;i<=ned;i++)pl(i);
	for(int i=1;i<=ned;i++)
	{
		mul*=n-i+1,mul%=mod;
		ans+=a[i]*mul%mod*qp(2,n-i)%mod,ans%=mod;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：Aleph1022 (赞：10)

看到某 lmpp 在群里说了这道题，立刻跑过来看一眼。  
这不就 Binomial Sum 吗？

考察
$$
\begin{aligned}
\sum\limits_{i=0}^n \binom ni i^k
&= \left[\frac{z^k}{k!}\right] \sum\limits_{i=0}^n \binom ni \mathrm e^{iz} \\
&= \left[\frac{z^k}{k!}\right] (1 + \mathrm e^z)^n
\end{aligned}
$$

注意
$$
\left[\frac{z^k}{k!}\right] \mathrm e^{iz} = i^k
$$

则令 $F(z) = (1+z)^n$，其满足 ODE
$$
(1+z)F'(z)-nF(z) = 0
$$

令 $\mathscr F(z+1) = F(z+1) \bmod z^{k+1}$，注意
$$
(2+z)F'(z+1) - nF(z+1) = 0
$$

手算一下可知
$$
(2+z)\mathscr F'(z+1) - n\mathscr F(z+1) = (k-n)\binom nk z^k 2^{n-k}
$$

提取系数，可以递推。

通过 [EI 科技](https://www.luogu.com.cn/blog/EntropyIncreaser/zai-tan-binomial-sum-duo-xiang-shi-fu-ge-cha-zhi-yu-tai-lei-zhan-kai) 可知 $\left[\frac{z^k}{k!}\right] F(\mathrm e^z) = \left[\frac{z^k}{k!}\right] \mathscr F(\mathrm e^z)$，而
$$
\begin{aligned}
\left[\frac{z^k}{k!}\right] \mathscr F(\mathrm e^z)
&= \left[\frac{z^k}{k!}\right] \sum\limits_{i=0}^k \mathrm e^{iz} [z^i]\mathscr F(z) \\
&= \sum\limits_{i=0}^k i^k [z^i]\mathscr F(z)
\end{aligned}
$$

通过线性筛计算 $k$ 次幂，时间复杂度 $\Theta(k)$。

---

## 作者：jijidawang (赞：9)

首先根据观察可以知道
$$\dfrac1{2^{n-k}}\sum_{i=0}^n\dbinom nii^k$$
是关于 $n$ 的 $k$ 次多项式 .

证明如下：

答案肯定是关于 $n$ 的多项式，下面分析次数 .

根据经典思路，令 $\displaystyle f_{k,n}(z)=\sum_{i=1}^n\dbinom nii^kz^i=g_{k,n}(z)\cdot(z+1)^{n-k}$，其中 $g_{k,n}$ 是一关于 $n$ 的多项式 .
$$\begin{aligned}\dfrac{\mathrm d}{\mathrm dz}(f_{k,n}(z)z)&=f_{k,n}(z)+zf'_{k,n}(z)\\&=g_{k,n}(z)\cdot(z+1)^{n-k}+z(g_{k,n}'(z)\cdot(z+1)^{n-k}+(n-k)g_{k,n}(z)\cdot(z+1)^{n-k-1})\\&=g_{k,n}(2)2^{n-k}+2(g'_{k,n}(z)2^{n-k}+(n-k)g_{k,n}(2)2^{n-k-1})\\&=(n-k+1)g_{k,n}(2)2^{n-k}+2g'_{k,n}(2)2^{n-k}\\&=2^{n-k}((n-k+1)g_{k,n}(2) + 2g'_{k,n}(2))\end{aligned}$$
第三个等号处代入 $z=1$ .

归纳即可得到为 $k$ 次 .

***

于是暴力 $\Theta(k^2)$ 求点值后 Lagrange 插值即可，时间复杂度 $\Theta(k^2)$ .

---

## 作者：Fading (赞：8)

### $\sum_{i=1}^nC_n^i\times i^k$

就是求这个式子

好像有点毒瘤

我们考虑如何快速求$i^k$

有一个东西叫做第二类斯特林数

如果你不知到第二类斯特林数，可以看看我的[组合数学的一些小知识总结](https://www.luogu.org/blog/wohaocaia/zu-ge-shuo-xue-di-yi-suo-xiao-zhi-shi-zong-jie-wei-wan-post)才刚开始写，未完待续，大佬轻喷。

有一条性质就是这个东西

$$i^k=\sum_{j=0}^kS_k^j×j!×C_i^j$$

直接扔进去

$$=\sum_{i=1}^nC_n^i\sum_{j=0}^kS_k^j×j!×C_i^j$$

$$=\sum_{i=1}^n\sum_{j=0}^kC_n^i\times S_k^j×j!×C_i^j$$

换一个位置

$$=\sum_{j=0}^k\sum_{i=1}^nC_n^i\times S_k^j×j!×C_i^j$$

$$=\sum_{j=0}^kS_k^j×j!\sum_{i=1}^nC_n^i×C_i^j$$

$$=\sum_{j=0}^kS_k^j×j!\sum_{i=1}^n(\frac {n!}{i!(n-i)!}\cdot\frac{i!}{(i-j)!(j)!})$$

$$=\sum_{j=0}^kS_k^j×j!\sum_{i=1}^n(\frac {n!}{(n-i)!(i-j)!(j)!})$$

$$=\sum_{j=0}^kS_k^j\sum_{i=1}^n(\frac {n!}{(n-i)!(i-j)!})$$

~~消消乐~~

然后注意到$n-i+i-j=n-j$

所以凑一凑

$$=\sum_{j=0}^kS_k^j\sum_{i=1}^n[\frac {(n-j)!(n!)}{(n-i)!(i-j)!(n-j)!}]$$

$$=\sum_{j=0}^kS_k^j\sum_{i=1}^n\frac {n!}{(n-j)!}[\frac {(n-j)!}{(n-i)!(i-j)!}]$$

$$=\sum_{j=0}^kS_k^j\frac {n!}{(n-j)!}\sum_{i=1}^nC_{n-j}^{n-i}$$

注意到$\sum_{i=0}^mC_{m}^{i}=2^m$

$$\sum_{j=0}^kS_k^j\frac {n!}{(n-j)!}\sum_{i=1}^nC_{n-j}^{n-i}$$

这里好像后面的东西还加多了……

$$=\sum_{j=0}^kS_k^j\frac {n!}{(n-j)!}2^{n-j}$$

暴力递推第二类斯特林数就可以做到$O(k^2)$

但是如果$k,$很$,$大$,$怎么办？

有一个第二类斯特林数通项公式

$$S_k^n=\sum_ {i=0}^n \frac {(-1)^{i}}{i!}\times \frac{(n-i)^k}{(n-i)!}$$

在$k$固定的情况下，设$S_k^n=h(n)$

$$\frac {(-1)^{i}}{i!}=f(i)$$

$$\frac{i^k}{i!}=g(i)$$

这里显然是一个卷积的形式

即

$$h(n)=f(i)\times g(n-i)$$

所以$NTT$就可以优化到$O(klog_2k)$啦！

答案 $=\sum_{j=0}^kS_k^j\frac {n!}{(n-j)!}2^{n-j}$

$\frac {n!}{(n-j)!}$有一点恶心啊，$n$是$10^9!!!$

那展开一下就是$\ n\cdot (n-1)\cdot (n-2)\cdot...\ \cdot(n-j+1)$

循环的时候算掉就好啦！

由于太毒瘤了，模数不是$998244353$，所以我用了三模数

然后巨慢，只有$rank\ 4$

代码如下：
```
#include<bits/stdc++.h>
#define ijc 1000000007
#define int long long
#define ll long long
using namespace std;
int n,m,k,r[400006],lim;
ll f[44001],ans[3][44001],h[44001],w[44001],_a[44001],_b[44001],g[44001];
ll P[3]={998244353,1004535809,469762049};
inline ll fast_pow(ll a,ll b,ll p){
    ll t=1;a%=p;
    while (b){
        if (b&1) t=t*a%p;
        b>>=1;a=a*a%p;
    }
    return t;
}
inline void NTT(ll f[],int lim,int id,ll ljc){
    for (int i=0;i<lim;i++){
        if (i<r[i]) swap(f[r[i]],f[i]);
    }
    w[0]=1;
    for (int len=1;len<lim;len<<=1){
    	ll gen=fast_pow(3,(ljc-1)/(len<<1)*id+ljc-1,ljc);
    	for (int i=1;i<lim;i++) w[i]=w[i-1]*gen%ljc;
        for (int i=0;i<lim;i+=len<<1){
            ll *f1=f+i,*f2=f1+len;
            for (int j=0;j<len;j++){
                ll x=f1[j]%ljc,y=f2[j]*w[j]%ljc;
                f1[j]=(x+y)%ljc;f2[j]=(x-y+ljc)%ljc;
            }
        }
    }
    if (id==1) return;
    ll Inv=fast_pow(lim,ljc-2,ljc);
    for (int i=0;i<lim;i++) f[i]=f[i]*Inv%ljc;
}
inline void mul(ll Ans[],int lim,ll p){
    memcpy(_a,f,sizeof(f)),memcpy(_b,g,sizeof(g));
    NTT(_a,lim,1,p);NTT(_b,lim,1,p);
    for (int i=0;i<=lim;i++) Ans[i]=(ll)_a[i]*_b[i]%p;
    NTT(Ans,lim,-1,p);
}
inline ll Gets(ll A,ll B,ll C,ll inv1,ll inv2,ll p12){
    ll t=(B-A+P[1])%P[1]*inv1%P[1]*P[0]+A;
    return ((C-t%P[2]+P[2])%P[2]*inv2%P[2]*(p12%ijc)%ijc+t)%ijc;
}
signed main(){
    cin>>n>>k;
    f[0]=1;g[0]=0;g[1]=1;
    ll fac=1;
    for (int i=2;i<=k;i++){
        fac=1LL*fac*i%ijc;
        ll Iv=fast_pow(fac,ijc-2,ijc);
        g[i]=fast_pow(i,k,ijc)*Iv%ijc;
    }
    fac=1;
    for (int i=1;i<=k;i++){
        fac=fac*i%ijc;
        f[i]=(ijc+(i%2?-1:1)*fast_pow(fac,ijc-2,ijc)%ijc)%ijc;
    }
    ll lim=1,len=0;
    while (lim<=(k<<1)) lim<<=1,len++;
    for (int i=0;i<lim;i++){
        r[i]=(r[i>>1]>>1)|((i&1)<<(len-1));
    }
    for (int i=0;i<3;i++) mul(ans[i],lim,P[i]);
    ll p12=1LL*P[0]*P[1],inv1=fast_pow(P[0],P[1]-2,P[1]),inv2=fast_pow(p12,P[2]-2,P[2]);
    for (int i=0;i<=k;i++) h[i]=Gets(ans[0][i],ans[1][i],ans[2][i],inv1,inv2,p12);
    fac=1;ll anss=0,two=fast_pow(2,n,ijc);inv2=fast_pow(2,ijc-2,ijc);//前面全是三模数NTT
    for (int j=0;j<=k;j++){
        anss=(anss+1LL*fac*h[j]%ijc*two%ijc)%ijc;
        fac=1LL*fac*(n-j)%ijc;
        two=two*inv2%ijc;
    }
    cout<<anss<<endl;
}
```

---

## 作者：w33z8kqrqk8zzzx33 (赞：2)

别的题解太强了，我都不会。。。

其实，会做 CF1278F 就会做这道题了。如果把 $m$ 设成 $2$，那么就变成每一个人可以选（Joker）或者可以不选（另外一个牌）。应为期望=所有可能结果权值之和除以结果个数，把期望乘 $2^n$ 得到答案。

因此，CF1278F 和这道题的唯一区别是 $m=2$ 并且要把答案乘以一个 $2^n$ 来把期望转换成总共的和。

[来看 CF1278F 的题解](https://www.luogu.com.cn/blog/220037/solution-cf1278f)

主要代码：

```cpp
const int MOD = 1000000007;

int dp[5005][5005];

int qpow(const int&b, const int&e) {
	if(!e) return 1;
	if(!(e&1)) return qpow(1ll*b*b%MOD,e>>1);
	return 1ll*b*qpow(b,e-1)%MOD;
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m, k; gi(n), m = 2, gi(k);
	dp[0][0] = 1;
	rep(len, k+1)
		rep(distinct, min(k,n)+1) {
			dp[len+1][distinct+1] = (1ll*(n-distinct)*dp[len][distinct]+dp[len+1][distinct+1])%MOD;
			dp[len+1][distinct] = (1ll*distinct*dp[len][distinct]+dp[len+1][distinct])%MOD;
		}
	m = qpow(m, MOD-2);
	int ans = 0, cm = qpow(2, n);
	rep(distinct, min(k,n)+1) {
		ans = (ans+1ll*cm*dp[k][distinct])%MOD;
		cm = 1ll*cm*m%MOD;
	}
	cout << ans << endl;
}

```

---

## 作者：撤云 (赞：2)

[广告](https://www.cnblogs.com/hbxblog/p/10198947.html)
#### 题目链接
[戳我](https://www.luogu.org/problemnew/show/CF932E)
#### 题意
有$n$个箱子，从中选出$i$个箱子，然后把$k$个不同的球装在这$i$个箱子中，求方案数。

实际上这题就是求:
$$ \sum_{i=1}^nc_n^i*i^k$$
不知道为什么翻译直接把这个写出来了，莫名其妙。

直接求这个式子肯定不行，$n$很大会超时，所以我们应该化简式子
$$\sum_{i=1}^nc_n^i*i^k$$
$$=\sum_{i=0}^nc_n^i*i^k$$
根据第二类斯特林数的性质：
$$n^k=\sum_{i=0}^nS(k,i)*i!*C(n,i)$$
所以式子可以继续化简：
$$=\sum_{i=0}^nc_n^i*\sum_{j=0}^kS(k,j)*j!*C(i,j)$$
$$=\sum_{i=0}^nc_n^i*\sum_{j=0}^kS(k,j)*j!*\frac{i!}{j!*(i-j)!}$$
$$=\sum_{i=0}^nc_n^i*\sum_{j=0}^kS(k,j)*\frac{i!}{(i-j)!}$$
$$=\sum_{i=0}^n\frac{n!}{i!(n-i)!}*\sum_{j=0}^kS(k,j)*\frac{i!}{(i-j)!}$$
$$=\sum_{i=0}^n\sum_{j=0}^kS(k,j)*\frac{i!}{(i-j)!}*\frac{n!}{i!(n-i)!}$$
$$=\sum_{i=0}^n\sum_{j=0}^kS(k,j)*\frac{n!}{(i-j)!*(n-i)!}$$
$$=\sum_{i=0}^nS(k,j)\sum_{j=0}^k\frac{(n-j)!}{(i-j)!*(n-i)!}*\frac{n!}{(n-j)!}$$
$$=\sum_{i=0}^nS(k,j)\sum_{j=0}^kC(n-j,n-i)*\frac{n!}{(n-j)!}$$
$$=\sum_{i=0}^nS(k,j)*\frac{n!}{(n-j)!}\sum_{j=0}^kC(n-j,n-i)$$
$$=\sum_{i=0}^nS(k,j)*\frac{n!}{(n-j)!}*2^{n-j}$$

所以这就可以直接做了

#### code

```cpp
#include<cstdio>
#define rg register
#define file(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout);
using namespace std;
typedef long long ll;
const int mod=1e9+7;
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9') f=(c=='-')?-1:1,c=getchar();
    while(c>='0'&&c<='9') x=x*10+c-48,c=getchar();
    return f*x;
}
ll s[5011][5011];
int n,k;
inline void init(){
    s[0][0]=1;
    for(rg int i=1;i<=k;i++)
        for(rg int j=1;j<=i;j++)
            s[i][j]=(s[i-1][j-1]+j*s[i-1][j])%mod;
}
inline ll ksm(int b){
    ll ans=1,a=2;
    while(b){
        if(b&1)
            ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans%mod;
}
main(){
    n=read(),k=read();
    init();
    ll p=ksm(n),ans=0,js=1,inv=ksm(mod-2);
    for(rg int i=0;i<=k;i++){
        ans+=s[k][i]*p%mod*js,p*=inv,p%=mod;
        ans%=mod;
        js=js*(n-i)%mod;
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：leozhang (赞：1)

斯特林数好题：

求$\sum_{i=1}^{n}C_{n}^{i}i^{k}$

首先第二类斯特林数有一个性质：

$x^{n}=\sum_{i=0}^{n}S_{2}(n,k)C_{x}^{k}k!$

那么我们展开原来的表达式，得到：

$\sum_{i=1}^{n}C_{n}^{i}i^{k}$=$\sum_{i=0}^{n}C_{n}^{i}i^{k}$=$\sum_{i=0}^{n}C_{n}^{i}\sum_{j=0}^{k}S_{2}(k,j)C_{i}^{j}j!$

整理一下后面的式子，顺便展开组合数，得到：

$\sum_{i=0}^{n}\frac{n!}{i!(n-i)!}\sum_{j=0}^{k}S_{2}(k,j)\frac{i!}{j!(i-j)!}j!$

立刻能继续整理：

$\sum_{i=0}^{n}\frac{n!}{(n-i)!}\sum_{j=0}^{k}S_{2}(k,j)\frac{1}{(i-j)!}$

调整一下枚举顺序：

$\sum_{j=0}^{k}S_{2}(k,j)\sum_{i=0}^{n}\frac{n!}{(n-i)!(i-j)!}$

再补一项：

$\sum_{j=0}^{k}S_{2}(k,j)\sum_{i=0}^{n}\frac{n!}{(n-i)!(i-j)!}\frac{(n-j)!}{(n-j)!}$

这样就可以整理出一个组合数：

$\sum_{j=0}^{k}S_{2}(k,j)\sum_{i=0}^{n}\frac{n!}{(n-j)!}\frac{(n-j)!}{(n-i)!(i-j)!}$

也就是：

$\sum_{j=0}^{k}S_{2}(k,j)\sum_{i=0}^{n}\frac{n!}{(n-j)!}C_{n-j}^{n-i}$

再提一项出来：

$\sum_{j=0}^{k}S_{2}(k,j)\frac{n!}{(n-j)!}\sum_{i=0}^{n}C_{n-j}^{n-i}$

后面那个求和式发现是对杨辉三角的某一行求和，根据结论，有：

$\sum_{j=0}^{k}S_{2}(k,j)\frac{n!}{(n-j)!}2^{n-j}$

这就可以算了

第二类斯特林数递推式：$S_{2}(i,j)=S_{2}(i-1,j-1)+jS_{2}(i-1,j)$

代码：

```cpp
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#define ll long long
using namespace std;
const ll mode=1000000007;
ll S[5005][5005];
int n,k;
ll pow_mul(ll x,ll y)
{
    ll ret=1;
    while(y)
    {
        if(y&1)ret=ret*x%mode;
        x=x*x%mode,y>>=1;
    }
    return ret;
}
int main()
{
    scanf("%d%d",&n,&k);
    S[0][0]=1;
    for(int i=1;i<=k;i++)for(int j=1;j<=i;j++)S[i][j]=(j*S[i-1][j]+S[i-1][j-1])%mode;
    ll las=1,mul=pow_mul(2,n),inv=(mode+1)>>1;
    ll ans=0;
    for(int i=0;i<=k;i++)
    {
        ans=(ans+S[k][i]*las%mode*mul%mode)%mode;
        las=las*(n-i)%mode;
        mul=mul*inv%mode;
    }
    printf("%lld\n",ans);
    return 0;
} 
 
```


---

## 作者：AThousandSuns (赞：1)

在我的博客园看效果更佳：[点这里](https://www.cnblogs.com/1000Suns/p/10544194.html)

**upd：感谢@sermoon指出符号出错了……已修改。**

很水的一道题。

根据第二类斯特林数的性质：

$$n^k=\sum^k_{i=1}\begin{Bmatrix}k\\i\end{Bmatrix}i!\dbinom{n}{i}$$

那么直接套进去：

$$\sum\limits^n_{i=1}\dbinom{n}{i}\sum^k_{j=1}\begin{Bmatrix}k\\j\end{Bmatrix}j!\dbinom{i}{j}$$

$$\sum^k_{j=1}\begin{Bmatrix}k\\j\end{Bmatrix}j!\sum\limits^n_{i=j}\dbinom{n}{i}\dbinom{i}{j}$$

$$\sum^k_{j=1}\begin{Bmatrix}k\\j\end{Bmatrix}j!\sum\limits^n_{i=j}\dfrac{n!}{i!(n-i)!}\dfrac{i!}{j!(i-j)!}$$

$$\sum^k_{j=1}\begin{Bmatrix}k\\j\end{Bmatrix}j!\sum\limits^n_{i=j}\dfrac{n!}{(n-i)!}\dfrac{1}{j!(i-j)!}$$

$$\sum^k_{j=1}\begin{Bmatrix}k\\j\end{Bmatrix}j!\sum\limits^n_{i=j}\dfrac{n!}{j!(n-j)!}\dfrac{(n-j)!}{(n-i)!(i-j)!}$$

$$\sum^k_{j=1}\begin{Bmatrix}k\\j\end{Bmatrix}j!\sum\limits^n_{i=j}\dbinom{n}{j}\dbinom{n-j}{i-j}$$

$$\sum^k_{j=1}\begin{Bmatrix}k\\j\end{Bmatrix}j!\dbinom{n}{j}\sum\limits^n_{i=j}\dbinom{n-j}{i-j}$$

$$\sum^k_{j=1}\begin{Bmatrix}k\\j\end{Bmatrix}j!\dbinom{n}{j}\sum\limits^{n-j}_{i=0}\dbinom{n-j}{i}$$

$$\sum^k_{j=1}\begin{Bmatrix}k\\j\end{Bmatrix}j!\dbinom{n}{j}2^{n-j}$$

如果我们知道了所有的 $\begin{Bmatrix}k\\j\end{Bmatrix}$ 那么这个式子可以做到 $O(k\log n)$。

由于本题 $k^2$ 已经足够，而且模数不友好，直接递推就好了。

时间复杂度 $O(k^2+k\log n)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1000000007;
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define ROF(i,a,b) for(int i=(a);i>=(b);i--)
#define MEM(x,v) memset(x,v,sizeof(x))
inline int read(){
    int x=0,f=0;char ch=getchar();
    while(ch<'0' || ch>'9') f|=ch=='-',ch=getchar();
    while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
    return f?-x:x;
}
int n,k,S[5050][5050];
inline int qpow(int a,int b){
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%mod) if(b&1) ans=1ll*ans*a%mod;
    return ans; 
}
int main(){
    n=read();k=read();
    S[0][0]=1;
    FOR(i,1,k) FOR(j,1,i) S[i][j]=(S[i-1][j-1]+1ll*S[i-1][j]*j)%mod;
    int c=1,f=1,ans=0;
    FOR(i,1,min(n,k)){
        c=1ll*c*(n-i+1)%mod*qpow(i,mod-2)%mod;
        f=1ll*f*i%mod;
        ans=(ans+1ll*c*S[k][i]%mod*f%mod*qpow(2,n-i))%mod;
    }
    printf("%d\n",ans);
}
```

---

## 作者：GoldenPotato137 (赞：0)

* [蒟蒻博客][1]
* [CodeForces][2]

---
# Solution
~~这题写得我脑壳疼，我好菜啊~~

.

显然，这题让我们求$\sum_{i=1}^{n}C_n^i\times i^k$

这个$i^k$让人浑身难受，我们可以考虑把它搞掉，能搞掉某个数的幂次方的有啥？本蒟蒻只会第二类斯特林数。

.

所以说我们无脑把第二类斯特林数带进去再说：

$\sum_{i=1}^{n}C_n^i\times \sum_{j=0}^{i}S(k,j)*j!*C_i^j$

.

然后把组合数展开：

$\sum_{i=1}^{n}\frac{n!}{i!(n-i)!}\times \sum_{j=0}^{i}S(k,j)*j!*\frac{i!}{j!(i-j)!}$

.

因为前面那一项与j无关，我们可以把它放到后面去

$\sum_{i=1}^{n} \sum_{j=0}^{i} \frac{n!}{i!(n-i)!} * S(k,j)*j!*\frac{i!}{j!(i-j)!}$

.

约分得：

$\sum_{i=1}^{n} \sum_{j=0}^{i} \frac{n!}{(n-i)!} * S(k,j)*\frac{1}{(i-j)!}$

.

因为$k$很小，$j$很大，而第二类斯特林数的定义告诉我们，当$j>k$时，$S(k,j)=0$。因此，我们可以考虑把$S(k,j)$放到外面来处理，根据[交换和号][3]的原则，我们可以处理前面两个$\sum$来方便把$S(k,j)$提到外面来。

交换和号后得：

$\sum_{j=0}^{n} \sum_{i=j}^{n} \frac{n!}{(n-i)!} * S(k,j)*\frac{1}{(i-j)!}$

.

然后就可以把$S(k,j)$提到外面来了：

$\sum_{j=0}^{n} S(k,j) \times \sum_{i=j}^{n} \frac{n!}{(n-i)!}*\frac{1}{(i-j)!}$

.

考虑到一点，当我们的$j>k$的时候，$S(k,j)=0$，因此，我们前面$j$的枚举范围可以缩小为$min(k,n)$

$\sum_{j=0}^{min(n,k)} S(k,j) \times \sum_{i=j}^{n} \frac{n!}{(n-i)!}*\frac{1}{(i-j)!}$

.

这时候我们可以发现：后面那个循环长得非常像组合数，考虑上下同时乘以$(n-j)!$让它变成组合数:

$\sum_{j=0}^{min(n,k)} S(k,j) \times \sum_{i=j}^{n} \frac{n!}{(n-j)!}*\frac{(n-j)!}{(n-i)!*(i-j)!}$

$\sum_{j=0}^{min(n,k)} S(k,j) \times \sum_{i=j}^{n} \frac{n!}{(n-j)!}*C_{(n-j)}^{(n-i)}$

.

同理，我们可以把后面那个阶乘提到前面去

$\sum_{j=0}^{min(n,k)} S(k,j)*\frac{n!}{(n-j)!} \times \sum_{i=j}^{n} C_{(n-j)}^{(n-i)}$

.

我们还可以注意到，后面那个循环：当$i<j$的时候，算出来的东西是没有意义的，因此我们可以改变循环范围为$i=0$ 来方便把那个难以计算的$\sum$变为方便计算的$2^x$的形式

$\sum_{j=0}^{min(n,k)} S(k,j)*\frac{n!}{(n-j)!} \times \sum_{i=0}^{n} C_{(n-j)}^{(n-i)}$

.

$\sum_{j=0}^{min(n,k)} S(k,j)*\frac{n!}{(n-j)!} \times 2^{(n-j)}$

.

搞定，到目前为止，这里里面的所有东西都可以方便的求出来了：

$S(k,j)$可以用$k^2$的递推暴力求算~~神犇们大可用FFT或NTT快速计算，可惜我太菜了并不会~~

$\frac{n!}{(n-j)!}$可以用一个$O(k)$的暴力递推算即可

$2^{(n-j)}$........如果不会算的话请自行右上角

.

时间复杂度$O(n^2)$

酱紫，这题就被我们A掉啦~

撒花ヾ(●´∀｀●) 

.

---
# Code
```cpp
//CF932E Team Work
//Jan,15th,2019
//第二类斯特林数的应用+奇奇怪怪的推公式
#include<iostream>
#include<cstdio>
using namespace std;
const int poi=1000000007;
long long FastPow(long long A,long long B)
{
	if(B==0) return 1;
	long long t_ans=FastPow(A,B/2);
	t_ans=t_ans*t_ans%poi;
	if(B%2==1) t_ans=t_ans*A%poi;
	return t_ans;
}
const int N=5000+100;
long long S[N][N],jc[N];
int n,K;
int main()
{
	scanf("%d%d",&n,&K);
	
	S[1][1]=1;
	for(int i=2;i<=K;i++)
		for(int j=1;j<=i;j++)
			S[i][j]=(S[i-1][j-1]+j*S[i-1][j])%poi;
	jc[0]=1;
	for(int i=1;i<=K;i++)
		jc[i]=jc[i-1]*(n-i+1)%poi;
	
	long long ans=0;
	int t=min(n,K);
	for(int i=0;i<=t;i++)
		ans+=S[K][i]*jc[i]%poi*FastPow(2,n-i),ans%=poi;
		
	printf("%lld",ans);
	return 0;
}

```




[1]:https://www.cnblogs.com/GoldenPotato/p/10275604.html
[2]:http://codeforces.com/problemset/problem/932/E
[3]:https://blog.csdn.net/github_35736728/article/details/80933891

---

