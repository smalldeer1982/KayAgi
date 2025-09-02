# [LMXOI Round 1] Dreamer

## 题目背景

[加强版链接](https://www.luogu.com.cn/problem/U402756)。

这是一道数学题，可是 LMX 给 HQZ 出的。

## 题目描述

定义积性函数 $f(n)=(\mu \ast\operatorname{Id_2})(n)$。

给定 $n,k$，你需要求出 

$$\sum_{i_1\mid n}\sum_{i_2\mid i_1}\cdots\sum_{i_k\mid i_{k-1}}f(i_k)i_1i_k\mu^2\left(\dfrac{i_1}{i_k}\right)$$

#### Tips：

$\mu$ 表示莫比乌斯函数。

关于 $f$，$f(n)=\displaystyle \sum_{d\mid n}\mu(d)\left(\dfrac{n}{d}\right)^2$。

## 说明/提示

对于 $100\%$ 的数据，有 $T \le 20,n\le 10^{24},1\le k\le 10^6,m\le 1.14\times 10^9$。

| 测试点编号 |      $n$      |    $k$     |   $T$    | 特殊性质 |
| :--------: | :-----------: | :--------: | :------: | :------: |
|    $1$     |   $\le 80$    |  $\le 4$   | $\le 5$  |   $N$    |
|    $2$     |  $\le 10^6$   |  $\le 10$  | $\le 5$  |   $N$    |
|    $3$     | $\le 10^{12}$ |  $\le 20$  | $\le 20$ |   $N$    |
|    $4$     | $\le 10^{18}$ |  $\le 1$   | $\le 20$ |   $N$    |
|    $5$     | $\le 10^{18}$ | $\le 10^3$ | $\le 20$ |   $N$    |
|    $6$     | $\le 10^{18}$ | $\le 10^5$ | $\le 20$ |   $A$    |
|    $7$     | $\le 10^{18}$ | $\le 10^6$ | $\le 20$ |   $B$    |
|    $8$     | $\le 10^{24}$ | $\le 10^6$ | $\le 20$ |   $B$    |
|    $9$     | $\le 10^{24}$ | $\le 10^6$ | $\le 20$ |   $C$    |
|    $10\sim20$    | $\le 10^{24}$ | $\le 10^6$ | $\le 20$ |   $N$    |

性质 $A$：保证 $t\le 10$。

性质 $B$：保证 $n$ 的质因子分解 $\displaystyle\prod_{i=1}^t p_i^{\alpha_i}$ 中 $\alpha_i=1$。

性质 $C$：$m$ 是素数，且保证 $\gcd(n,m)=1$。



## 样例 #1

### 输入

```
5
3 998244353
3
3 2
5 1
7 1
4 1000000009
2
2 1
3 2
1 998244353
2
2 2
3 1
11451 191981012
11
2 1
3 1
5 1
7 1
11 1
13 1
17 1
19 1
23 1
29 1
31 1
514 520
2
2 10
3 10```

### 输出

```
189282114
124678
14965
82966193
260
```

# 题解

## 作者：封禁用户 (赞：12)

别人的解法都好强啊，各种积性函数的做法，这里来一个完全暴力的~~赛场上推挂 $4$ 次的~~解法。

（实际上已经简化过了，真正手推的时候推了这玩意的三倍长度……）

（希望管理员审核的时候能有耐心审核 $\LaTeX$。）

（感谢管理员 @lvkaiyi0811 十分耐心地把 $\LaTeX$ 完整地审核了一遍！！！）

首先是一些定义：

令 $g(x)$ 表示 $i_1=x,i_k=1$ 时 $i_2,\dots,i_{k-1}$ 的种类数；

令 $r(x)$ 表示 $x$ 的无平方因子（比如 $r(2^4 \times 3^5 \times 7)=2 \times 3 \times 7$）；

令 $pr(x)$ 表示 $x$ 的不同质因子数量；

令 $f(i)=i^2\prod\limits_{p|i,p \in \mathbb{P}}(1-\frac{1}{p^2})$，下面默认 $p \in \mathbb{P}$。

下面开始推式子：

$
\begin{aligned}
\text{原式}
&=\sum\limits_{i_k|n}\sum\limits_{i_1|\frac{n}{i_k}}f(i_k)i_1i_k^2\mu^2(i_1)g(i_1)\text{（这里认为} i_1 \gets \frac{i_1}{i_k}\text{）}\\
&=\sum\limits_{i_k|n}f(i_k)i_k^2\sum\limits_{i_1|r(\frac{n}{i_k})}i_1g(i_1)\\
&=\sum\limits_{i|n}f(i)i^2\sum\limits_{i_1|r(\frac{n}{i})}i_1(k-1)^{pr(i_1)}\\
&=\sum\limits_{i|n}i^4(\prod\limits_{p|i}(1-\frac{1}{p^2}))(\sum\limits_{i_1|r(\frac{n}{i})}i_1(k-1)^{pr(i_1)})\\
&=\sum\limits_{i|n}i^4(\prod\limits_{p|i}(1-\frac{1}{p^2}))(\prod\limits_{p|r(\frac{n}{i})}(1+p(k-1)))\\
&=\sum\limits_{s|r(n)}(\prod\limits_{p|s}(1+p(k-1)))\sum\limits_{i|n}([r(\frac{n}{i})=s]i^4\prod\limits_{p|r(i)}(1-\frac{1}{p^2}))\\
&=\sum\limits_{s|r(n)}(\prod\limits_{p|s}(1+p(k-1)))\sum\limits_{i|\frac ns}([r(\frac{n}{i})=s]i^4\prod\limits_{p|r(i)}(1-\frac{1}{p^2}))\\
&=\sum\limits_{s|r(n)}(\prod\limits_{p|s}(1+p(k-1)))\sum\limits_{w|r(\frac ns)}(\sum\limits_{i|\frac ns}([r(\frac{n}{i})=s][r(i)=w]i^4\prod\limits_{p|r(i)}(1-\frac{1}{p^2})))\\
&=\sum\limits_{s|r(n)}(\prod\limits_{p|s}(1+p(k-1)))\sum\limits_{w|r(\frac ns)}(\prod\limits_{p|w}(1-\frac{1}{p^2})\sum\limits_{i|\frac ns}([r(\frac{n}{i})=s][r(i)=w]i^4))\\
&=\sum\limits_{s|r(n)}(\prod\limits_{p|s}(1+p(k-1)))\sum\limits_{\frac{r(n)}{s}|w|r(\frac ns)}(\prod\limits_{p_i|w}(1-\frac{1}{p_i^2})\prod\limits_{p_i|w}([p_i|s]\sum\limits_{f=1}^{\alpha_i-1}p_i^{4f}+[p_i\nmid s]p_i^{4\alpha_i}))\\
&=\sum\limits_{s|r(n)}(\prod\limits_{p|s}(1+p(k-1)))\sum\limits_{\frac{r(n)}{s}|w|r(\frac ns)}(\prod\limits_{p_i|w}(1-\frac{1}{p_i^2})\prod\limits_{p_i|\gcd(w,s)}(\sum\limits_{f=1}^{\alpha_i-1}p_i^{4f})\prod\limits_{p_i|\frac{w}{\gcd(w,s)}}(p_i^{4\alpha_i}))\\
&=\sum\limits_{s|r(n)}(\prod\limits_{p|s}(1+p(k-1)))\sum\limits_{\frac{r(n)}{s}|w|r(\frac ns)}(\prod\limits_{p_i|w}(1-\frac{1}{p_i^2})\prod\limits_{p_i|\gcd(w,s)}(p_i^4 \times \frac{p_i^{4(\alpha_i-1)}-1}{p_i^4-1})\prod\limits_{p_i|\frac{w}{\gcd(w,s)}}(p_i^{4\alpha_i}))\\
&=\sum\limits_{s|r(n)}(\prod\limits_{p|s}(1+p(k-1)))\sum\limits_{w|\frac{r(\frac ns)}{\frac{r(n)}{s}}}(\prod\limits_{p_i|w\times \frac{r(n)}{s}}(1-\frac{1}{p_i^2})\prod\limits_{p_i|\gcd(w\times \frac{r(n)}{s},s)}(p_i^4 \times \frac{p_i^{4(\alpha_i-1)}-1}{p_i^4-1})\prod\limits_{p_i|\frac{w\times \frac{r(n)}{s}}{\gcd(w\times \frac{r(n)}{s},s)}}(p_i^{4\alpha_i}))\text{（这里认为} w \gets \frac{w}{\frac{r(n)}{s}}\text{）}\\
&=\sum\limits_{s|r(n)}(\prod\limits_{p|s}(1+p(k-1)))\sum\limits_{w|\frac{r(\frac ns)}{\frac{r(n)}{s}}}(\prod\limits_{p_i|w}(1-\frac{1}{p_i^2})\prod\limits_{p_i|\frac{r(n)}{s}}(1-\frac{1}{p_i^2})\prod\limits_{p_i|\gcd(w,s)}(p_i^4 \times \frac{p_i^{4(\alpha_i-1)}-1}{p_i^4-1})\prod\limits_{p_i|\gcd(\frac{r(n)}{s},s)}(p_i^4 \times \frac{p_i^{4(\alpha_i-1)}-1}{p_i^4-1})\prod\limits_{p_i|\frac{w}{\gcd(w,s)}}(p_i^{4\alpha_i})\prod\limits_{p_i|\frac{\frac{r(n)}{s}}{\gcd(\frac{r(n)}{s},s)}}(p_i^{4\alpha_i}))\\
&=\sum\limits_{s|r(n)}(\prod\limits_{p|s}(1+p(k-1)))\prod\limits_{p_i|\frac{r(n)}{s}}(1-\frac{1}{p_i^2})\prod\limits_{p_i|\gcd(\frac{r(n)}{s},s)}(p_i^4 \times \frac{p_i^{4(\alpha_i-1)}-1}{p_i^4-1})\prod\limits_{p_i|\frac{\frac{r(n)}{s}}{\gcd(\frac{r(n)}{s},s)}}(p_i^{4\alpha_i})\sum\limits_{w|\frac{r(\frac ns)}{\frac{r(n)}{s}}}(\prod\limits_{p_i|w}(1-\frac{1}{p_i^2})\prod\limits_{p_i|\gcd(w,s)}(p_i^4 \times \frac{p_i^{4(\alpha_i-1)}-1}{p_i^4-1})\prod\limits_{p_i|\frac{w}{\gcd(w,s)}}(p_i^{4\alpha_i}))\\
&=\sum\limits_{s|r(n)}(\prod\limits_{p|s}(1+p(k-1)))\prod\limits_{p_i|\frac{r(n)}{s}}(1-\frac{1}{p_i^2})\prod\limits_{p_i|\frac{r(n)}{s}}(p_i^{4\alpha_i})\sum\limits_{w|\frac{r(\frac ns)}{\frac{r(n)}{s}}}(\prod\limits_{p_i|w}(1-\frac{1}{p_i^2})\prod\limits_{p_i|\gcd(w,s)}(p_i^4 \times \frac{p_i^{4(\alpha_i-1)}-1}{p_i^4-1})\prod\limits_{p_i|\frac{w}{\gcd(w,s)}}(p_i^{4\alpha_i}))\\
&=\sum\limits_{s|r(n)}(\prod\limits_{p|s}(1+p(k-1)))\prod\limits_{p_i|\frac{r(n)}{s}}((1-\frac{1}{p_i^2})p_i^{4\alpha_i})\sum\limits_{w|\frac{r(\frac ns)}{\frac{r(n)}{s}}}(\prod\limits_{p_i|w}(1-\frac{1}{p_i^2})\prod\limits_{p_i|\gcd(w,s)}(p_i^4 \times \frac{p_i^{4(\alpha_i-1)}-1}{p_i^4-1})\prod\limits_{p_i|\frac{w}{\gcd(w,s)}}(p_i^{4\alpha_i}))\\
&=\sum\limits_{s|r(n)}(\prod\limits_{p|s}(1+p(k-1)))\prod\limits_{p_i|\frac{r(n)}{s}}((p_i^2-1)p_i^{4\alpha_i-2})\sum\limits_{w|\frac{r(\frac ns)}{\frac{r(n)}{s}}}(\prod\limits_{p_i|w}(1-\frac{1}{p_i^2})\prod\limits_{p_i|\gcd(w,s)}(p_i^4 \times \frac{p_i^{4(\alpha_i-1)}-1}{p_i^4-1})\prod\limits_{p_i|\frac{w}{\gcd(w,s)}}(p_i^{4\alpha_i}))\\
&=\sum\limits_{s|r(n)}(\prod\limits_{p|s}(1+p(k-1)))\prod\limits_{p_i|\frac{r(n)}{s}}((p_i^2-1)p_i^{4\alpha_i-2})\sum\limits_{w_1|\frac{\frac{r(\frac ns)}{\frac{r(n)}{s}}}{\gcd(\frac{r(\frac ns)}{\frac{r(n)}{s}},s)},w_2|\gcd(\frac{r(\frac ns)}{\frac{r(n)}{s}},s)}(\prod\limits_{p_i|w_1w_2}(1-\frac{1}{p_i^2})\prod\limits_{p_i|w_2}(p_i^4 \times \frac{p_i^{4(\alpha_i-1)}-1}{p_i^4-1})\prod\limits_{p_i|w_1}(p_i^{4\alpha_i}))\\
&=\sum\limits_{s|r(n)}(\prod\limits_{p|s}(1+p(k-1)))\prod\limits_{p_i|\frac{r(n)}{s}}((p_i^2-1)p_i^{4\alpha_i-2})\sum\limits_{w_1|\frac{\frac{r(\frac ns)}{\frac{r(n)}{s}}}{\frac{r(\frac ns)}{\frac{r(n)}{s}}}}(\prod\limits_{p_i|w_1}(1-\frac{1}{p_i^2})\prod\limits_{p_i|w_1}(p_i^{4\alpha_i}))\sum\limits_{w_2|\frac{r(\frac ns)}{\frac{r(n)}{s}}}(\prod\limits_{p_i|w_2}(1-\frac{1}{p_i^2})\prod\limits_{p_i|w_2}(p_i^4 \times \frac{p_i^{4(\alpha_i-1)}-1}{p_i^4-1}))\\
&=\sum\limits_{s|r(n)}(\prod\limits_{p|s}(1+p(k-1)))\prod\limits_{p_i|\frac{r(n)}{s}}((p_i^2-1)p_i^{4\alpha_i-2})\sum\limits_{w_2|\frac{r(\frac ns)}{\frac{r(n)}{s}}}(\prod\limits_{p_i|w_2}((1-\frac{1}{p_i^2})p_i^4 \times \frac{p_i^{4(\alpha_i-1)}-1}{p_i^4-1}))\\
&=\sum\limits_{s|r(n)}(\prod\limits_{p|s}(1+p(k-1)))\prod\limits_{p_i|\frac{r(n)}{s}}((p_i^2-1)p_i^{4\alpha_i-2})\sum\limits_{w_2|\frac{r(\frac ns)}{\frac{r(n)}{s}}}(\prod\limits_{p_i|w_2}((p_i^2-1)p_i^2 \times \frac{p_i^{4(\alpha_i-1)}-1}{p_i^4-1}))\\
&=\sum\limits_{s|r(n)}(\prod\limits_{p|s}(1+p(k-1)))\prod\limits_{p_i|\frac{r(n)}{s}}((p_i^2-1)p_i^{4\alpha_i-2})\prod\limits_{p_i|\frac{r(\frac ns)}{\frac{r(n)}{s}}}(1+(p_i^2-1)p_i^2 \times \frac{p_i^{4(\alpha_i-1)}-1}{p_i^4-1})\\
&=\sum\limits_{s|r(n)}(\prod\limits_{p|s}(1+p(k-1)))\prod\limits_{p_i|\frac{r(n)}{s}}((p_i^2-1)p_i^{4\alpha_i-2})\prod\limits_{p_i|\frac{r(\frac ns)}{\frac{r(n)}{s}}}(1+(p_i^2-1)p_i^2 \times \frac{p_i^{4(\alpha_i-1)}-1}{p_i^4-1})
\end{aligned}
$

那么直接爆搜 $s$，搜的过程中每个因子都计算一下三个累成符号的贡献，然后搜完所有因子直接统计即可，时间复杂度 $\Theta(2^t+\sum \alpha_i)$。

如果用矩阵快速幂优化计算 $\frac{p_i^{4(\alpha_i-1)}-1}{p_i^4-1}$，可以做到 $\Theta(2^t+\sum \log \alpha_i)$。

如果运用积性函数，可以让每次搜索变成 $O(1)$，复杂度降为 $\Theta(t+\sum \log \alpha_i) \sim O(t \log \alpha)$。

优化都很好写，然而不写也能过了，就不写了，建议出一个加强版，$T=1,1 \le t \le 5 \times 10^5,1 \le p_i,\alpha_i \le 10^{18}$，等到出了加强版再写那两个优化。

AC 代码：

```cpp
//sum s|r(n)(prod pi|s(1+pi*(k-1))*prod pi|r(n)/s((pi^2-1)*pi^(4ai-2))*prod pi|r(n/s)/(r(n)/s)(pi^2(pi^2-1)(pi^4(ai-1)-1)/(pi^4-1)+1))
//o(i,si)=(pi^4(ai-si)-1)/(pi^4-1)
//o(i,si)=1+pi^4+...+pi^4(ai-si-1)
//vi=pi^2(pi^2-1)o(i,1)+1
//yi=(pi^2-1)*pi^(4ai-2)
//wi=1+pi*(k-1)
//sum s|r(n)(prod pi|s(wi)*prod pi|r(n)/s(yi)*prod pi|r(n/s)/(r(n)/s)(vi))
#include<bits/stdc++.h>
using namespace std;
typedef __int128_t li;
typedef long long ll;
#define gc getchar()
inline li rd(){li x=0;char c=gc;while(c<48||c>57) c=gc;while(c>47&&c<58) x=(x<<3)+(x<<1)+(c^48),c=gc;return x;}
li T,k,m,t,p[19],a[19],u[19],v[19],y[19],w[19],ans;//π(67)=18,2*3*5*...*67*71>1e24
inline li q(li a,li b){return !b?1:b==1?a:b&1?q(a*a%m,b>>1)*a%m:q(a*a%m,b>>1);}
inline li o(li p,int a){li r=0;for(int i=0;i<=a;++i) r=(r*p+1)%m;return r;}
inline void dfs(int x,li e){
	if(x==t){
		ans+=e;
		return;
	}
	dfs(x+1,e*y[x]%m);//sx=0
	if(a[x]==1) dfs(x+1,e*w[x]%m);//sx=1
	else dfs(x+1,e*w[x]%m*v[x]%m);
}
int main(){
	T=rd();
	while(T--){
		k=rd(),m=rd(),t=rd();
		for(int i=0;i<t;++i) p[i]=rd(),a[i]=rd();
		for(int i=0;i<t;++i){
			w[i]=(1+p[i]*(k-1))%m;
			v[i]=(p[i]%m*p[i]%m*((p[i]%m*p[i]%m+m-1)%m)%m*o(p[i]%m*(p[i]%m)%m*(p[i]%m)%m*(p[i]%m)%m,a[i]-2)+1)%m;
			y[i]=((p[i]%m*p[i]%m+m-1)%m)%m*q(p[i]%m,4*a[i]-2)%m;
		}
		ans=0,dfs(0,1);
		cout<<(int)(ans%m)<<"\n";
	}
	return 0;
}
```

---

## 作者：Kreado (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/P10117)。

在做这道题之前请确保你已经熟练了[狄利克雷卷积](https://zhuanlan.zhihu.com/p/646539446)。

## 思路

**无特殊说明，默认 $p$ 为素数**。

$$v(n)=\sum_{i_1\mid n}\sum_{i_2\mid i_1}\cdots\sum_{i_k\mid i_{k-1}}f(i_k)i_1i_k\mu^2\left(\dfrac{i_1}{i_k}\right)$$

把 $i_k$ 提到前面来：


$$\sum_{i_k\mid n}f(i_k)i_k^2\sum_{i_1\mid \frac{n}{i_k}}i_1\mu^2(i_1)\sum_{i_2\mid i_1}\cdots\sum_{i_{k-1}\mid i_{k-2}}1$$

记 $g(x)=\displaystyle \sum_{i_2\mid x}\cdots\sum_{i_{k-1}\mid i_{k-2}}1$，直接求 $g$ 是困难的，但是我们发现 $g$ 的传参都是 Square Free Number，那么该式就相当于若干个子集求和，这个是简单的，得到 $g(x)=(k-1)^{\omega(x)}$。

由于 $\omega$ 是和性函数，放在指数上就是积性函数了，那么整个式子就是一个积性函数，那么

$$
\begin{aligned}
\cdots&=
(((\operatorname{Id_2}\ast \mu )\times \operatorname{Id_2})\ast (1\ast (\operatorname{Id}\times \mu^2\times g)))(n)\\
&=(1\ast ((\operatorname{Id}\times \mu^2 \times g)\ast ((\operatorname{Id_2}\ast \mu)\times \operatorname{Id_2})))(n)

\end{aligned}
$$

显然有 $((\operatorname{Id_2}\ast \mu)\times \operatorname{Id_2})(p^c)=(p^{2c}-p^{2c-2})p^{2c}$，$(1\ast (\operatorname{Id}\times \mu^2\times g))(p^c)=1+p(k-1),(c\ge 1)$。

那么我们能够得到答案在素数幂次的取值

$$v(p^c)=1+p(k-1)+(p^{2c}-p^{2c-2})p^{2c}+(1+p(k-1))\sum_{i=1}^{c-1} (p^{2i}-p^{2i-2})p^{2i},(c\ge 1)$$

由于 $m$ 可能不为素数，所以后面的式子我们要用矩阵快速幂算。

根据积性函数的特性，那么答案就是

$$v(n)=\prod_{i=1}^t v(p_i^{\alpha_i})$$

时间复杂度 $O(Tt\log \alpha),\alpha=\max \{\alpha_i\}$。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int T,t;
ll k,m;

inline void qread(ll &x){
	x=0;char ch;bool f=0;
	while((ch=getchar())&&(ch>'9'||ch<'0')) if(ch=='-') f=1;x=(ch^48);
	while((ch=getchar())&&(ch>='0'&&ch<='9')) x=(x<<1)+(x<<3)+(ch^48),x%=m;
	x=f?-x:x;
}
inline ll ksm(ll a,ll b,ll mod){
    ll z=1;
    while(b){
        if(b&1) z=z*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return z;
}
inline ll upd(ll x){
    return (x%m+m)%m;
}
struct Matrix{
    ll a[2][2];
    inline void init(){a[0][0]=a[1][1]=1;}
    inline void clear(){memset(a,0,sizeof a);}
};
inline Matrix operator *(const Matrix x,const Matrix y){
    Matrix z;z.clear();
    for(ll k=0;k<2;k++)
        for(ll i=0;i<2;i++)
            for(ll j=0;j<2;j++)
                z.a[i][j]=upd(z.a[i][j]+x.a[i][k]*y.a[k][j]);
    return z;
}
inline ll GetSum(ll a,ll d,ll p,ll n){
    Matrix res;res.clear();
    res.a[0][1]=ksm(p,a,m);
    Matrix delt;delt.clear();
    delt.a[0][0]=delt.a[1][0]=1;
    delt.a[1][1]=ksm(p,d,m);
    Matrix r;r.clear();r.init();
    while(n){
        if(n&1) r=r*delt;
        delt=delt*delt;
        n>>=1;
    }
    res=res*r;
    return res.a[0][0];
}
inline ll Getv(ll p,ll c){
    ll res=0;
    res=upd(upd(GetSum(4,4,p,c-1)-GetSum(2,4,p,c-1))*(1+p*k%m)%m);
    res=upd(res+upd(1+p*k%m+ksm(p,2*c,m)*upd(ksm(p,2*c,m)-ksm(p,2*c-2,m))%m));
    return res;
}

int main(){
    scanf("%d",&T);

    while(T--){
        scanf("%lld%lld",&k,&m);
        k=upd(k-1);
        scanf("%d",&t);
        ll ans=1;
        while(t--){
            ll p,c;
            qread(p),scanf("%lld",&c);
            ans=ans*Getv(p,c)%m;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```



---

## 作者：chroneZ (赞：5)

数据范围为什么不再加几个 $0$ 呢/mgx。

枚举 $d = \dfrac{i_1}{i_k}$，此时 $i_2, i_3, \dots, i_{k - 1}$ 的方案数显然可以通过一些组合式直接计算。

记这个方案数为 $g(d)$，则我们可以将原式简化为

$$
\sum_{d | n} g(d) \mu^2(d) d \sum_{i_k | \frac{n}{d}} f(i_k) i_k^2
$$

注意到 $\mu^2(d)$ 非 $0$ 当且仅当 $d$ 是 Square Free Number，因此有意义的 $d$ 只有 $2 ^ {\omega(n)}$ 个，同时 $g(d)$ 的计算也具有了更加简洁的形式：$g(d) = (k - 1) ^ {\omega(d)}$。

考虑直接枚举这 $2 ^ {\omega(n)}$ 个 $d$ 以计算答案，那么我们还需要快速算出式中的 $\sum \limits_{i_k | \frac{n}{d}} f(i_k) i_k ^ 2$。由于 $f$ 和 $\mathbf{id}_2$ 均为积性函数，所以 $h(n) = \sum \limits_{x | n} f(x) x ^ 2$ 同样是积性函数。也就是说，我们可以在枚举 $d$ 每一项质因子的次数时，记当前质因子为 $p$，$\frac{n}{d}$ 中 $p$ 的次数为 $k$，直接将 $h(p ^ k)$ 乘入最终的答案即可。

预处理 $h$，便可以在单次 $\Theta(2 ^ {\omega(n)})$ 的复杂度内算出答案。容易分析出 $\omega(n)$ 最大只会达到 $18$，因此已经足以通过本题。

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

int mod;
namespace basic {
  inline int add(i64 x, i64 y) {return (x + y >= mod ? x + y - mod : x + y);}
  inline int dec(i64 x, i64 y) {return (x - y < 0 ? x - y + mod : x - y);}
  inline void ad(int &x, int y) {x = add(x, y);}
  inline void de(int &x, int y) {x = dec(x, y);}

  inline int qpow(int a, int b) {
    int r = 1;
    while(b) {
      if(b & 1) r = 1ll * r * a % mod;
      a = 1ll * a * a % mod; b >>= 1;
    }
    return r;
  }
  inline int inv(int x) {return qpow(x, mod - 2);}
}
using namespace basic;

int K, n; i64 p[30], k[30];
int f[30][100], g[30][100];

int solve(int cur, int F) {
  if(cur == n + 1) {
    return F;
  }
  int x = solve(cur + 1, 1ll * F * g[cur][k[cur]] % mod);
  int y = solve(cur + 1, 1ll * F * p[cur] % mod * (K - 1) % mod * g[cur][k[cur] - 1] % mod);
  return add(x, y);
}

void Main() {
  cin >> K >> mod >> n;
  for(int i = 1; i <= n; i++) {
    cin >> p[i] >> k[i]; p[i] %= mod;
    f[i][0] = g[i][0] = 1;
    int w = 1ll * p[i] * p[i] % mod;
    for(int j = 1, t = 1; j <= k[i]; j++) {
      f[i][j] = dec(1ll * t * w % mod, t);
      t = 1ll * t * w % mod;
      g[i][j] = add(g[i][j - 1], 1ll * f[i][j] * t % mod);
    }
  }
  cout << solve(1, 1) << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  
  int T; cin >> T;
  while(T--) {
    Main();
  }
}
```

能不能再给力一点啊？可以。

进一步可以发现，不仅 $h(n) = \sum \limits_{x | n} f(x) x ^ 2$ 是积性函数，式中的 $g, \mu ^ 2, \mathbf{id}$ 均为积性函数（关于 $g$，由于 $\omega$ 满足加性，将其放在指数上积性自然成立），因此**答案也是积性函数**。记 $n = \prod p_i ^ {k_i}$，直接对每个 $p_i ^ {k_i}$ 计算答案，则所有的答案之积即为所求。

复杂度是十分优秀的单次 $\Theta(\omega(n) + \log n)$，后面那个 $\log$ 是预处理的复杂度。

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

int mod;
namespace basic {
  inline int add(i64 x, i64 y) {return (x + y >= mod ? x + y - mod : x + y);}
  inline int dec(i64 x, i64 y) {return (x - y < 0 ? x - y + mod : x - y);}
  inline void ad(int &x, int y) {x = add(x, y);}
  inline void de(int &x, int y) {x = dec(x, y);}

  inline int qpow(int a, int b) {
    int r = 1;
    while(b) {
      if(b & 1) r = 1ll * r * a % mod;
      a = 1ll * a * a % mod; b >>= 1;
    }
    return r;
  }
  inline int inv(int x) {return qpow(x, mod - 2);}
}
using namespace basic;

int K, n; i64 p[30], k[30];
int f[30][100], g[30][100];

int solve(int cur) {
  int x = g[cur][k[cur]];
  int y = 1ll * p[cur] % mod * (K - 1) % mod * g[cur][k[cur] - 1] % mod;
  return add(x, y);
}

void Main() {
  cin >> K >> mod >> n;
  for(int i = 1; i <= n; i++) {
    cin >> p[i] >> k[i]; p[i] %= mod;
    f[i][0] = g[i][0] = 1;
    int w = 1ll * p[i] * p[i] % mod;
    for(int j = 1, t = 1; j <= k[i]; j++) {
      f[i][j] = dec(1ll * t * w % mod, t);
      t = 1ll * t * w % mod;
      g[i][j] = add(g[i][j - 1], 1ll * f[i][j] * t % mod);
    }
  }
  int ans = 1;
  for(int i = 1; i <= n; i++) {
    ans = 1ll * ans * solve(i) % mod;
  }
  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  
  int T; cin >> T;
  while(T--) {
    Main();
  }
}
```

---

## 作者：LostKeyToReach (赞：2)

提供一种码量小的做法。

## 准备阶段

- 先把 $f(n)$ 展开：

  $$
  \begin{aligned}
  f(n) &= (\mu \ast \operatorname{Id_2})(n) \\ 
  &= \sum_{d \mid n} \mu(d)\left(\frac nd\right)^2.
  \end{aligned}
  $$

  ~~这个函数显然是积性的。~~

- 记答案为 $S(n)$，则其可表示为：

  $$
    S(n) = \prod_{p \mid n} S_p(p, \alpha), n = \prod p^{\alpha}.
  $$

  $S_p(p, \alpha)$ 具体可以理解为 $n$ 的所有因子对答案的贡献。

- 原式中的 $\mu^2(x)$ 可表示为：

  $$
  \mu^2(x) = \begin{cases}1, & n\text{ is square-free-number,}\\[6pt]0, & \text{otherwise.}\end{cases}
  $$

## 开始解题

你会发现，我们的答案是 $n$ 的因子的嵌套和。我们不妨把每个嵌套和中的 $i_j$ 想象为一条「链」，随后钦定 $p$，使得存在 $x_1, x_2, \ldots x_k$ 满足以下条件：

- $\forall 1 \le j \le k$，$x_j$ 为 $i_j$ 分解质因数后底数为 $p$ 的指数。

- $x_1 \le \alpha$。

- $x_1 - x_k \in \{0, 1\}$。为什么？因为我们要令 $\mu(\frac{i_1}{i_k}) \neq 0$，故 $x_1 - x_k$ 只能 $ < 2$。

在 $\mu(\frac{i_1}{i_k}) = 1$ 的前提下，$i_1$ 会对答案贡献 $p^{x_1}$，$i_k$ 会对答案贡献 $p^{x_k}$，$f(i_k)$ 会对答案贡献 $f(p^{x_k})$。

--------

此时我们的 $S_p(p, \alpha)$ 转换为：

$$
\sum_{0 \le x_k \le x_1 \le \alpha, x_1 - x_k \in \{0, 1\}}(「和」).
$$

「和」包括了：

- $f(p^{x_{k}})$。

- $p^{x_1} \times p^{x_k} = p^{x_1 + x_k}$。

- 链中从 $x_1$ 到 $x_k$ 的方案数。 

我们考虑两种情况进行求解。

1. 当 $x$ 序列「不降」，即 $x_1 - x_k = 0$：
   
   >  此时 $x_1 = x_2 = \ldots = x_k = y$。令 $y \in [0, \alpha]$，则 $y$ 的贡献为：
   >
   > - $f(p^y)$。
   >
   > - $p^{x_1} \times p^{x_k} = p^{2y}$。
   >
   > 此时总贡献为 $\displaystyle\sum_{y = 0} ^ {\alpha}f(p^y)p^{2y}$。

2. 当 $x$ 序列「下降」，即 $x_1 - x_k = 1$：

    > 此时 $x_1 = x_2 = \ldots = x_i = y + 1, x_{i + 1} = x_{i + 2} = \ldots = x_{k} = y, i \in [1, k - 1], y \in [0, a - 1]$，则 $y$ 的贡献为：
    >
    > - $f(p^y)$。
    >
    > - $p^{x_1} \times p^{x_k} = p^{2y + 1}$。
    >
    > 此时总贡献为 $\displaystyle(k - 1)\sum_{y = 0} ^ {\alpha - 1}f(p^y)p^{2y+1}$。

--------

这个两个部分看起来并不是太好搞，那么我们朝 $f(p^y)$ 突破。先把式子写下来：

$$
f(p^y) = \sum_{d \mid p^y}\mu(d)\left(\frac{p^y}{d}\right)^2.
$$

这里的 $d$ 显然是 $1, p, p^2, \ldots, p^y$。

如果你注意力惊人，你会发现 $\mu(1) = 1, \mu(p) = -1, \mu(p^x) = 0 \text{ for } x \ge 2$。这时可以考虑化简原式：

$$
\begin{aligned}
f(p^y) &= \sum_{d \mid p^y}\mu(d)\left(\frac{p^y}{d}\right)^2 \\
&= \mu(1)(p^{y})^2 + \mu(p)(p^{y - 1})^2 \\
&= p^{2y} - p^{2y-2} \\
&= p^{2y-2}(p^2-1).
\end{aligned}
$$

-----------

恭喜你，马上就要成功了！

此时，我们每一项都已知，直接带入：

$$
\begin{aligned}
S(n) &= \prod_{p \mid n}S_p(p, \alpha) \\
&= \prod_{p \mid n}\left[\sum_{y = 0} ^ {\alpha}f(p^y)p^{2y} + (k - 1)\sum_{i = 0} ^ {\alpha - 1}f(p^y)p^{2y+1}\right] \\
&= \prod_{p \mid n}\left\{\left[\sum_{y = 1} ^ {\alpha}p^{4y-2}(p^2-1) + 1\right] + (k - 1)\left[p + \sum_{y = 1} ^ {\alpha - 1}p^{4y - 1}(p^2 - 1)\right]\right\}. \\
\end{aligned}
$$

直接按照这个式子模拟计算即可。

时间复杂度可以做到十分优秀的 $O(t + \sum \alpha_i)$。

参考代码如下：

```cpp
#include <bits/stdc++.h>
#define int long long
constexpr int N = 1e5 + 6;
int power(int a, int b, int m) {
    int ans = 1;
    for (; b > 0; b >>= 1, a = a * a % m) if (b & 1) ans = ans * a % m;
    return ans;
}
int32_t main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    int t;
    std::cin >> t;
    while (t--) {
        int k, m, t;
        std::cin >> k >> m >> t;
        int ans = 1;
        for (int i = 0; i < t; ++i) {
            int p, a;
            std::cin >> p >> a, p %= m;
            int s1 = 1, s2 = p, f = (p * p - 1) % m;
            for (int y = 1; y <= a; ++y) {
                int t1 = power(p,  4LL * y - 2, m), t2 = t1 * p % m;
                s1 = (s1 + t1 * f % m) % m;
                if (y < a) 
                    s2 = (s2 + t2 * f % m) % m;
            }
            int v = (s1 + (k - 1) * s2 % m) % m;
            ans = ans * v % m;
        }
        std::cout << ans << "\n";
    }
}
```

那么如何通过加强版呢？下面给出一个~~口胡的~~做法：

> 注意到原式的 $p^{4y - 2}$ 和 $p^{4y - 1}$ 构成等比数列，考虑在这一部分使用类似快速幂的思想（因为不一定有乘法逆元），可以做到更加优秀的 $O(t + \sum \log \alpha_i)$。

~~代码就不给了，因为我懒。~~

接下来继续推式子：

$$
\begin{aligned}
S(n) &= \prod_{p \mid n}\left\{\left[\sum_{y = 1} ^ {\alpha}p^{4y-2}(p^2-1) + 1\right] + (k - 1)\left[p + \sum_{y = 1} ^ {\alpha - 1}p^{4y - 1}(p^2 - 1)\right]\right\} \\
&= \prod_{p \mid n}\left\{(p^2-1)\left(\sum_{y = 1} ^ {\alpha}p^{4y-2}\right) + 1 + (k - 1)\left[p + (p^2-1)\sum_{y = 1} ^ {\alpha - 1}p^{4y - 1} \\
\right]\right\}\\
&= \prod_{p \mid n}\left\{(p^2-1)\left(p^2\sum_{y = 1} ^ {\alpha}p^{4(y-1)}\right) + 1 + (k - 1)\left[p + p^3(p^2-1)\sum_{y = 1} ^ {\alpha - 1}p^{4(y - 1)} \\
\right]\right\} \\
&= \prod_{p \mid n}\left\{(p^2-1)\left(p^2\sum_{y = 0} ^ {\alpha - 1}(p^4)^y\right) + 1 + (k - 1)\left[p + p^3(p^2-1)\sum_{y = 0} ^ {\alpha - 2}(p^4)^y \\
\right]\right\}.
\end{aligned}
$$

由此可见，我们只需要使用快速幂求公比为 $p^4$ 的等比数列之和即可。

参考代码如下：

```cpp
#include <bits/stdc++.h>
#define int long long
constexpr int N = 1e5 + 6;
int get_sum(int x, int n, int m) {
    #define fr first
    #define se second
    std::pair<int, int> res = {1 % m, 0 % m}, b = {x % m, 1 % m};
    if (n < 0) return 0;
    while (n > 0) {
        if (n & 1) res = {res.fr * b.fr % m, (res.se + res.fr * b.se % m) % m};
        b = {b.fr * b.fr % m, (b.se + b.fr * b.se % m) % m}, n >>= 1;
    }
    return res.second;
}
int32_t main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    int t;
    std::cin >> t;
    while (t--) {
        int k, m, t;
        std::cin >> k >> m >> t;
        int ans = 1;
        for (int i = 0; i < t; ++i) {
            int p, a; std::cin >> p >> a, p %= m;
            int p2 = p * p % m, p3 = p2 * p % m, p4 = p3 * p % m, p5 = p4 * p % m;
            int s1 = (((p4 - p2) % m + m) % m * get_sum(p4, a, m) % m + 1) % m;
            int s2 = (((p5 - p3) % m + m) % m * get_sum(p4, a - 1, m) % m + p) % m;
            int v = ((s1 + (k - 1) % m * s2) % m + m) % m;
            ans = ans * v % m;
        }
        std::cout << ans << "\n";
    }
}
```

但这段代码只能在加强版获得 $95$ 分，有没有神人帮忙卡个常。

---

## 作者：warzone (赞：1)

[可能更好的阅读体验](https://www.luogu.com.cn/blog/wangrx/solution-p10117)

## 题目大意

给定 $n,k,m$，求解

$$\left(\sum_{i_1|n}\sum_{i_2|i_1}\cdots\sum_{i_k|i_{k-1}}(\mu*\mathrm{Id}_2)(i_k)i_1i_k\mu^2\left(\dfrac{i_1}{i_k}\right)\right)\bmod m$$

$n$ 以标准质因子分解 $n=\displaystyle\prod_{i=1}^tp_i^{\alpha_i}$ 的形式给出。

$T$ 组数据。

$\texttt{Data Range:} T\le 20,n\le 10^{24},1\le k\le 10^6,m\le 1.14\times 10^9$ 。

## 题解

以下是一篇贝尔级数的题解。

### 狄利克雷卷积的本质意义

对于数论函数 $f:\N_+\rightarrow\mathbb{C}$，我们发现，如果将质数 $2,3,5,7,\cdots$ 变为元 $x_2,x_3,x_5,x_7,\cdots$，  
则每个数论函数都可视为一无穷元生成函数

$$f(x_2,x_3,x_5,x_7,\cdots)=f(1)+f(2)x_2+f(3)x_3+f(4)x_2^2+f(5)x_5+f(6)x_2x_3+f(7)x_7+f(8)x_2^3+\cdots$$

在此基础上，对于数论函数的狄利克雷卷积

$$(f*g)(n)=\sum_{ab=n}f(a)g(b)=\sum_{d|n}f(d)g\left(\dfrac{n}{d}\right)$$

其本质就是数论函数所对应的无穷元生成函数的乘积。

### 积性函数与贝尔级数

我们定义数论函数的 **贝尔级数** 为

$$f_p(x)=\sum_{k=0}^{+\infty}f(p^k)x^k$$

那么显然，$f$ 为积性函数当且仅当其对应的无穷元生成函数可因式分解为

$$f(x_2,x_3,x_5,x_7,\cdots)=f_2(x_2)f_3(x_3)f_5(x_5)f_7(x_7)\cdots$$

的形式。

因此以下结论是显然的：

- 两个积性函数 $f,g$ 的狄利克雷卷积仍是积性函数，其贝尔级数 $(f*g)_p(x)=f_p(x)g_p(x)$。
- 对于积性函数 $f$，其狄利克雷卷积逆 $f^{-1}$ 仍是积性函数，其贝尔级数为 $f_p^{-1}(x)=\dfrac{1}{f_p(x)}$。

此外，我们还有以下结论：

- 若 $f(n),g(n)$ 为积性函数，则 $f(n)g(n)$ 仍是积性函数，其贝尔级数为 $(f_p\bullet g_p)(x)$，  
  $\bullet$ 表示系数对应位置相乘。

-----------------------------------------------------

回到本题。设

$$i_1=d_1i_2,i_2=d_2i_3,\cdots,i_{k-1}=d_{k-1}i_k$$

那么原式变为

$$\sum_{i_1|n}\sum_{i_k|i_1}(\mu*\mathrm{Id}_2)(i_k)i_1i_k\mu^2\left(\dfrac{i_1}{i_k}\right)\sum_{d_1d_2\cdots d_{k-1}=\frac{i_1}{i_k}}1$$

$$=\sum_{i_1|n}i_1\sum_{i_k|i_1}(\mu*\mathrm{Id}_2)(i_k)i_k\left(\mu^2\left(\dfrac{i_1}{i_k}\right)\sum_{d_1d_2\cdots d_{k-1}=\frac{i_1}{i_k}}1\right)$$

$\mu$ 的贝尔级数为 $1-x$，$\mu^2$ 的贝尔级数为 $1+x$，$1$ 的贝尔级数为 $\dfrac{1}{1-x}$，$\mathrm{Id}_m$ 的贝尔级数为 $\dfrac{1}{1-p^mx}$，  
故答案为积性函数，其贝尔级数为

$$ans_p(x)=\left(\dfrac{1}{1-px}\bullet\left(\left(\dfrac{1-x}{1-p^2x}\bullet \dfrac{1}{1-px}\right)\left((1+x)\bullet\dfrac{1}{(1-x)^{k-1}}\right)\right)\right)\dfrac{1}{1-x}$$

此时我们已经可以直接用机器暴力计算关于 $p,x$ 的二元生成函数的卷积得到结果。也可以手工推柿子，得

$$ans_p(x)=(1+(k-1-p)px-(k-1)p^3x^2)\sum_{i=0}^{+\infty}x^i\sum_{j=0}^ip^{4j}$$

时间复杂度 $\Theta(\sum_{i}\alpha_i)$ 。

### Code

```cpp
/*
this code is made by warzone
2024.1.29 10:40
*/
#include<stdio.h>
typedef __uint128_t ulll;
typedef unsigned long long ull;
typedef unsigned int word;
word case_,k,mod,t;
ulll p[32];
word cnt[32],pre[128];
struct READ{//快读
	char c;
	inline READ(){c=getchar();}
	template<typename type>
	inline READ& operator>>(type &num){
		for(;'0'>c||c>'9';c=getchar());
		for(num=0;'0'<=c&&c<='9';c=getchar())
			num=num*10+(c-'0');
		return *this;
	}
}cin;
int main(){
	for(cin>>case_;case_;--case_){
		cin>>k>>mod>>t;
		for(word i=1;i<=t;++i)
			if(cin>>p[i]>>cnt[i],p[i]==p[i-1])
				--i,--t,cnt[i]+=cnt[i+1];
		word ans=1;
		for(word i=1;i<=t;++i){
			const word get=p[i]%mod;
			const word get2=1ull*get*get%mod;
			const word get3=1ull*get2*get%mod;
			const word get4=1ull*get3*get%mod;
			pre[0]=1;
			for(word j=1,now=1;j<=cnt[i];++j){
				now=1ull*now*get4%mod;
				pre[j]=(pre[j-1]+now)%mod;
			}//预处理 $\sum_{i=0}^{+\infty}x^i\sum_{j=0}^ip^{4j}$
			ull out=pre[cnt[i]];
			if(cnt[i]>=1) out+=1ull*pre[cnt[i]-1]*get%mod*(k-1+mod-get)%mod;
			if(cnt[i]>=2) out+=1ull*pre[cnt[i]-2]*get3%mod*(1+mod-k)%mod;
			ans=out%mod*ans%mod;
		}
		printf("%u\n",ans);
	}
	return 0;
}
```

---

