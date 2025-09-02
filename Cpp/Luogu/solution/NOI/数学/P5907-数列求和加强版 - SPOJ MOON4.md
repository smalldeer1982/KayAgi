# 数列求和加强版 / SPOJ MOON4

## 题目背景

[原题链接](https://www.luogu.com.cn/problem/P4948)

## 题目描述

给定 $n,a,k$，求：

$$\sum_{i=1}^n i^k a^i$$
答案对 $998244353$ 取模。

## 说明/提示

【数据范围】    
对于 $20\%$ 的数据，$1\le n,k \le 10^5$。  
对于 $100\%$ 的数据，$1\le k \le 10^7$，$1\le n,a \le 998244352$。

## 样例 #1

### 输入

```
6 4 3```

### 输出

```
1030980```

## 样例 #2

### 输入

```
233333333 114514 1919810```

### 输出

```
3191086```

# 题解

## 作者：warzone (赞：12)

[可能更好的阅读体验](https://www.luogu.com.cn/blog/wangrx/solution-p5907)


## 题目大意

给定 $n,a,k$，求

$$\sum_{i=1}^ni^ka^i$$

答案对 $998244353$ 取模。

$\texttt{Data Range:} 1\le k\le 10^7,1\le n,a\le 998244352$

## 题解

前置芝士：[有限微积分](https://www.luogu.com.cn/blog/wangrx/finite-calculus)

[原做法](https://www.luogu.com.cn/blog/wangrx/solution-p4948) 因需求第二类斯特林数有着 $\Theta(n\log n)$ 的瓶颈，这一做法不再适用。  

但原做法仍有相当程度的借鉴性，具体地，设 $f(n)=\displaystyle{\sum}_0^n{x^ka^x\delta x}$，

则 $f(x)=a^xg(x)-a^0g(0),g(x)$ 为 $k$ 次函数。答案即 $f(n+1)-f(1)$。

若已知 $g(0),g(1),g(2),\cdots g(k)$，我们可以 $\Theta(k)$ 拉格朗日插值求出 $g(n+1)$。

考虑如何求出 $g(m)\ (0\le m\le k)$，显然线性筛出 $i^k$  后 $f(m)$ 可以 $\Theta(k)$ 递推，于是

$$g(m)=a^{-m}(g(0)+f(m))$$

问题变成了如何求出 $g(0)$ 。

$g(x)$ 为 $k$ 次函数，因此其 $(k+1)$ 阶差分为 $0$，于是

$$\Delta^{k+1}g(0)=\sum_{i=0}^{k+1}\dbinom{k+1}{i}(-1)^{k+1-i}\mathrm{E}^ig(0)=0$$

$$\sum_{i=0}^{k+1}\dbinom{k+1}{i}(-1)^{k+1-i}g(i)=0$$

$$\sum_{i=0}^{k+1}\dbinom{k+1}{i}(-1)^{k+1-i}a^{-i}(g(0)+f(i))=0$$

$$g(0)(a^{-1}-1)^{k+1}+\sum_{i=0}^{k+1}\dbinom{k+1}{i}(-1)^{k+1-i}a^{-i}f(i)=0$$

$$g(0)=-(1-a^{-1})^{-k-1}\sum_{i=0}^{k+1}\dbinom{k+1}{i}(-a)^{-i}f(i)$$

代入即可 $\Theta(k)$ 算出 $g(0)$。

特别的，$a=1$ 时，$f(x)=g(x),g(x)$为 $k+1$ 次而非 $k$ 次，直接插值即可。

---

## 作者：myee (赞：8)

### 前言

我去写了一道叫做[礼物](https://www.luogu.com.cn/problem/P5364)的数数题，三分钟推完柿子直接做，然后 Peter 说洛谷上有个加强版。

我感觉很 Hard，所以过来学了个科技。

然后又不会插值的想法，所以去学了学传说中的 EI 科技 [Binomial Sums](https://www.luogu.com.cn/blog/EntropyIncreaser/zai-tan-binomial-sum-duo-xiang-shi-fu-ge-cha-zhi-yu-tai-lei-zhan-kai)。

---
### 思路

我们令 $n\leftarrow n+1$。

答案即 $\sum_0^nx^ka^x\delta x$。

$$\sum x^ka^x\delta x=
x^k{a^x\over a-1}
-{a\over a-1}\sum a^x\Delta x^k\delta x$$

$$
\sum_0^nx^ka^x\delta x={n^ka^n\over a-1}+{a\over1-a}\sum_{p=0}^{k-1}\binom kp\sum_0^na^xx^p\delta x
$$

$$
f_k=\sum_0^nx^ka^x\delta x
$$

算出 $f$ 的 EGF，显然答案即

$$
[{z^k\over k!}]{1-(ae^z)^n\over1-ae^z}
$$

我们记

$$F(z)={1-z^n\over1-z}$$

答案即 $[{z^k\over k!}]F(ae^z)$。

记

$$\mathcal F(z+a)=F(z+a)\bmod z^{k+1}$$

答案即 $[{z^k\over k!}]\mathcal F(ae^z)$。

既有

$$(1-z)F'(z)=-nz^{n-1}+F(z)$$

于是

$$(1-z-a)F'(z+a)=-n(z+a)^{n-1}+F(z+a)$$

可得

$$(1-z-a)\mathcal F'(z+a)-\mathcal F(z+a)=-((z+a)^n\bmod z^{k+1})'-(k+1)z^k[z^k]\mathcal F(z+a)$$

$$(1-z)\mathcal F'(z)-\mathcal F(z)=-(((z+a)^n\bmod z^{k+1})\circ(z-a))'-(k+1)(z-a)^k[z^k]\mathcal F(z)$$

而

$$\sum_{i=0}^k\binom nia^{n-i}(z-a)^i=\sum_{p=0}^k\binom npz^pa^{n-p}(-1)^{k-p}\binom{n-p-1}{k-p}$$

不难想到提取系数转成递推。

---
然后 $[z^0]\mathcal F$ 咋算？

$$
[z^0]\mathcal F=\sum_{i=0}^k(-a)^i\sum_{j=i}^{n-1}\binom jia^{j-i}=1+(-1)^ka\sum_{j=0}^{n-2}a^j\binom jk
$$

${\rm I}.a\neq1$

$$g_k=\sum_0^{n-1}a^x\binom xk\delta x$$

$$
\sum a^x\binom xk\delta x
={a^x\binom xk\over a-1}-{a\over a-1}\sum a^x\binom x{k-1}\delta x
$$

$$g_k={a^{n-1}\binom{n-1}k\over a-1}-{a\over a-1}g_{k-1}$$

$g$ 很容易线性递推。

${\rm II}.a=1$

$$[z^0]\mathcal F=1+(-1)^k\binom{n-1}{k+1}$$

---
记 $w=[z^k]\mathcal F(z)$，那么提取系数转成递推，每个数可以表示为 $kw+b$ 形式，最后高斯消元解出 $w$ 既得 $\mathcal F$ 系数，于是答案就可做了。（比较奇怪的是没有出现解出无数多个 $w$ 的情况，个中理由我也不大清楚）

$$h_p=[z^p]\mathcal F$$

$$
ans=[{z^k\over k!}]\mathcal F(ae^z)
=\sum_ih_ia^i[{z^k\over k!}]e^{iz}
=\sum_ih_ia^ii^k
$$

线性筛预处理 $i^k$，总复杂度 $O(k+\log n)$。

---
### Code

代码挂一下吧，稍微卡了卡空间常数。

```cpp
const ullt Mod=998244353,g=3;
typedef mod_ullt<Mod>modint;
typedef std::vector<modint>modvec;
typedef poly_NTT<Mod,g>poly;
typedef poly_eval<Mod,g>eval;
typedef poly_inter<Mod,g>inter;
typedef poly_cpd<Mod,g>cpd;
modint A[10000005],B[10000005];
modint F1[10000005],F2[10000005];
bol Ok[10000005];
int main()
{
    A[0]=1;for(uint i=1;i<=10000001;i++)A[i]=A[i-1]*i;
    B[10000001]=A[10000001].inv();for(uint i=10000001;i;i--)B[i-1]=B[i]*i;
    uint n,k;modint a;
    scanf("%u",&n),n++,a.read(),scanf("%u",&k);
    modint t1=a._power(n),t2=(-a)._power(k),q=a.inv(),w;
    modint i1=(a-1).inv(),i2=a._power(n-1);
    if(a==1)
    {
        F1[0]=B[k+1];
        for(uint i=0;i<=k;i++)F1[0]*=n-1-i;
        F1[0]=1+((k&1)?Mod-1:1)*F1[0];
    }
    else{
        modint now=(i2-1)*i1;w=n-1;
        for(uint i=1;i<=k;i++)
        {
            now=(-a*now+w*i2)*i1,w=w*(n-i-1)*B[i+1]*A[i];
        }
        F1[0]=now*a*(k&1?Mod-1:1)+1;
    }
    F2[k]=1;for(uint i=k-1;i;i--)F2[i]=F2[i+1]*(n-i-1)*B[k-i]*A[k-i-1];
    w=1;
    for(uint i=1;i<=k;i++)
    {
        t1*=q,w*=(n-i+1)*B[i]*A[i-1];
        F1[i]=F1[i-1]-w*t1*(((k-i)&1)?Mod-1:1)*F2[i],F2[i]=F2[i-1]-(k+1)*A[k]*B[i-1]*B[k-i+1]*t2*B[i]*A[i-1];
        t2*=-q;
    }
    w=F1[k]/(1-F2[k]);
    for(uint i=0;i<=k;i++)F2[i]=F1[i]+F2[i]*w;
    modint ans;
    F1[0]=0,F1[1]=1;
    std::vector<uint>Prime;
    for(uint i=2;i<=k;i++)
    {
        if(!Ok[i])
        {
            Prime.push_back(i);
            w=modint(i)._power(k);
            for(ullt j=i;j<=k;j*=i)
            {
                Ok[j]=true;
                F1[j]=F1[j/i]*w;
            }
        }
        for(ullt p:Prime)
            if(i*p<=k&&i%p)
            {
                for(ullt t=p;t*i<=k;t*=p)
                {
                    Ok[t*i]=true;
                    F1[t*i]=F1[t]*F1[i];
                }
            }
            else break;
    }
    w=1;
    for(uint i=0;i<=k;i++)
        ans+=F2[i]*w*F1[i],w*=a;
    ans.println();
    return 0;
}
```


---

## 作者：critnos (赞：5)

$a=1$ 和 $n\le k$ 平凡。

$$\sum_{i=0}^{n-1}i^ka^i$$

$$[\dfrac {x^k} {k!}]\sum_{i=0}^{n-1}(ae^x)^i$$

$$[\dfrac {x^k} {k!}]\dfrac {(ae^x)^n-1}{ae^x-1}$$

考虑写出 $(ae^x-1)^{-1}$，

不妨写成 $(ae^x-a+(a-1))^{-1}$。

广义二项式

$$\sum_{i\ge 0}C(-1,i)(ae^x-a)^i(a-1)^{-1-i}$$

令 $p=\dfrac 1 {1-a}$，其实就是

$$-p\sum_{i\ge 0}(pa(e^x-1))^i$$

注意到 $e^x-1$ 常数项为 $0$，$0\le i\le k$，然后乘起来得到

$$-p[\dfrac {x^k} {k!}]((ae^x)^n-1)\sum_{i=0}^k(pa(e^x-1))^i$$

$$-p[\dfrac {x^k} {k!}]((ae^x)^n-1)\sum_{i=0}^k(pa)^i\sum_{j=0}^iC(i,j)(e^x)^j(-1)^{i-j}$$

$$-p\sum_{i=0}^k(pa)^i\sum_{j=0}^iC(i,j)[a^n(j+n)^k-j^k](-1)^{i-j}$$

$$-p\sum_{j=0}^k[a^n(j+n)^k-j^k]\sum_{i=0}^k(pa)^i(-1)^{i-j}C(i,j)$$

观察一下后面的东西：

$$f_j=\sum_{i=0}^k(pa)^i(-1)^{i-j}C(i,j)$$

$$f_j-f_{j-1}=\sum_{i=0}^k(pa)^i(-1)^{i-j}C(i,j)+\sum_{i=0}^k(pa)^i(-1)^{i-j}C(i,j-1)$$

$$\sum_{i=0}^k(pa)^i(-1)^{i-j}C(i+1,j)$$

$$\sum_{i=1}^{k+1}(pa)^{i-1}(-1)^{i-j-1}C(i,j)$$

$$\dfrac {f_j-(-1)^j+(pa)^{k+1}(-1)^{k+1-j}C(k+1,j)} {-pa}$$

那么 $f_{j-1}$ 可以由 $f_j$ 得出。

还有一个问题：$(j+n)^k$ 怎么求？这个可以用区间筛做。据某裙友说复杂度大约是 $O(k\log\log n)$。

[代码实现](https://www.luogu.com.cn/paste/jqn9g6hk)

感觉这个推导方法还是好用的，P6031 可以用这个避开斯特林数而快速地推到最后递推的地方。

---

## 作者：gxy001 (赞：4)

本题解使用 EI 科技 载谭 Binomial Sum。

给定 $n,q,k$，求 $\sum_{i=0}^ni^kq^i$。

$G(x)$ 取 $qe^x$，$F(x)$ 取 $\frac{1-x^{n+1}}{1-x}$，我们已知 $\forall 0\le i\le k,[\frac{x^k}{k!}](qe^x)^i=q^ii^k$，求 $\sum_{i=0}^ni^kq^i=[\frac{x^k}{k!}]F(G(x))$。

$F(x)$ 满足的微分方程是 $F(x)+(x-1)F^{\prime}(x)=(n+1)x^{n}$。

即 $-nF(x)+((2-n)x+n)F^{\prime}(x)+(x^2-x)F^{\prime\prime}(x)=0$​。

设 $F_0(x+q)=F(x+q)\bmod x^{k+1}$。

我们要求的答案就等于 $[\frac{x^k}{k!}]F_0(G(x))$，这是因为 $F_0(x+q)=F(x+q)\bmod x^{k+1}$，且 $G(x)-q$ 没有常数项，那么将 $G(x)-q$ 代入 $F_0(x+q)$ 结果的 $k$ 次项系数就应该等于代入 $F(x+q)$ 结果的 $k$ 次项系数，因为 $(G(x)-q)^i$ 在 $i>k$ 时时不会对 $k$ 次项产生贡献的。

$$
\begin{aligned}
-nF(x+q)+((2-n)(x+q)+n)F^{\prime}(x+q)+((x+q)^2-(x+q))F^{\prime\prime}(x+q)&=0\\
-nF(x+q)+((2-n)x+2q-nq+n)F^{\prime}(x+q)+(x^2+(2q-1)x+q^2-q)F^{\prime\prime}(x+q)&=0\\
-nF_0(x+q)+((2-n)x+2q-nq+n)F_0^{\prime}(x+q)+(x^2+(2q-1)x+q^2-q)F_0^{\prime\prime}(x+q)&=ax^k+bx^{k-1}\\
\end{aligned}
$$

设 $c=[x^k]F(x+q),d=[x^{k-1}]F(x+q)$，则上式 $a,b$ 分别为

$$
\begin{aligned}
a&=-nc+(2-n)kc+k(k-1)c\\
b&=-nd+(2-n)(k-1)d+(2q-nq+n)kc+(k-1)(k-2)d+(2q-1)k(k-1)c\\
\end{aligned}
$$

考虑求出 $c,d$，$c=\sum_{i=0}^n[x^k] (x+q)^i=\sum_{i=k}^nq^{i-k}\binom ik$。

$$
\begin{aligned}
h_k&=\sum_{i=k}^nq^{i-k}\binom ik\\
&=\sum_{i=k}^nq^{i-k}(\binom {i-1}{k-1}+\binom{i-1}{k})\\
&=\sum_{i=k-1}^{n-1}q^{i-(k-1)}\binom {i}{k-1}+q\sum_{i=k}^{n-1}q^{i-k}\binom{i}{k}\\
&=h_{k-1}-q^{n-k+1}\binom n{k-1}+q(h_k-q^{n-k}\binom nk)
\end{aligned}
$$

递推即可，注意特判 $q=1$。

然后根据

$$
-nF_0(x)+((2-n)x+n)F_0^{\prime}(x)+(x^2-x)F_0^{\prime\prime}(x)=a(x-q)^k+b(x-q)^{k-1}
$$

求出 $F_0$ 即可，设 $[x^i]F_0(x)=f_i$，那么有

$$
-nf_i+(2-n)if_{i}+n(i+1)f_{i+1}+i(i-1)f_i-(i+1)if_{i+1}=a(-q)^{k-i}\binom ki+b(-q)^{k-1-i}\binom {k-1}i
$$

$$
f_i=\frac{a(-q)^{k-i}\binom ki+b(-q)^{k-1-i}\binom {k-1}i+(i-n)(i+1)f_{i+1}}{(i-n)(i+1)}
$$

我们已知 $f_{k+1}=0$，就可以求出 $f_{0\sim k}$ 了，那么答案就是 $\sum_{i=0}^ni^kq^i=\sum_{i=0}^kf_i[\frac{x^k}{k!}](qe^x)^i=\sum_{i=0}^kf_iq^ii^k$。

注意， $n\le k$ 的时候求解 $f_i$ 时的 $(i-n)$ 会出问题，暴力即可。

```cpp
#include<iostream>
using std::cin;
using std::cout;
int const mod=998244353;
int n,k,q,p[1000010],pw[10000010],fac[10000010],ifac[10000010],cnt;
bool b[10000010];
int pow(int x,int y){
	int res=1;
	while(y){
		if(y&1) res=1ll*res*x%mod;
		x=1ll*x*x%mod,y>>=1;
	}
	return res;
}
void init(int n){
	pw[1]=1;
	for(int i=2;i<=n;i++){
		if(!b[i]) p[++cnt]=i,pw[i]=pow(i,k);
		for(int j=1;j<=cnt&&i*p[j]<=n;j++){
			b[i*p[j]]=1,pw[i*p[j]]=1ll*pw[i]*pw[p[j]]%mod;
			if(i%p[j]==0) break;
		}
	}
	fac[0]=1;
	for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
	ifac[n]=pow(fac[n],mod-2);
	for(int i=n;i;i--) ifac[i-1]=1ll*ifac[i]*i%mod;
}
int C(int n,int m){
	return 1ll*fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}
int main(){
	std::ios::sync_with_stdio(false),cin.tie(nullptr);
	cin>>n>>q>>k;
	init(k);
	for(int i=1,d=q;i<=k;i++,d=1ll*d*q%mod) pw[i]=1ll*pw[i]*d%mod;
	if(n<=k){
		int ans=0;
		for(int i=1;i<=n;i++) ans=(ans+pw[i])%mod;
		cout<<ans<<'\n';
		return 0;
	}
	int c=1,d=1;
	if(q==1){
		d=ifac[k];
		for(int i=0;i<k;i++) d=1ll*d*(n+1-i)%mod;
		c=1ll*d*pow(k+1,mod-2)%mod*(n+1-k)%mod;
	}else{
		static int C[10000010];
		int iv=pow(1-q+mod,mod-2),f=(1ll-pow(q,n+1)+mod)*iv%mod;
		if(k==1) d=f;
		C[0]=1;
		for(int i=1;i<=k;i++) C[i]=1ll*C[i-1]*(n-i+1)%mod;
		for(int i=1;i<=k;i++) C[i]=1ll*C[i]*ifac[i]%mod;
		for(int i=k,pw=pow(q,n-k);~i;i--,pw=1ll*pw*q%mod) C[i]=(mod-1ll)*C[i]%mod*pw%mod;
		for(int i=1;i<=k;i++){
			f=(f+C[i-1]+1ll*q*C[i])%mod*iv%mod;
			if(i==k) c=f;
			if(i==k-1) d=f;
		}
	}
	int a=((mod-1ll)*n%mod*c+(2ll-n+mod)*k%mod*c+1ll*k*(k-1)%mod*c)%mod;
	int b=((mod-1ll)*n%mod*d+(2ll-n+mod)*(k-1)%mod*d+((2*q-1ll*n*q+n)%mod+mod)*k%mod*c+(k-1ll)*(k-2)%mod*d+(2*q-1ll+mod)*k%mod*(k-1)%mod*c)%mod;
	int f=0,ans=0;
	q=mod-q;
	static int p[10000010],cv[10000010];
	p[0]=cv[0]=1;
	for(int i=1;i<=k;i++) p[i]=1ll*p[i-1]*q%mod;
	for(int i=1;i<=k;i++) cv[i]=1ll*cv[i-1]*(i-n+mod)%mod*(i+1)%mod;
	int iv=pow(cv[k],mod-2);
	for(int i=k;i;i--){
		cv[i]=1ll*iv*cv[i-1]%mod;
		iv=1ll*iv*(i-n+mod)%mod*(i+1)%mod;
	}
	for(int i=k;i;i--){
		f=(f+(1ll*a*p[k-i]%mod*C(k,i)+1ll*b*p[k-i-1]%mod*C(k-1,i))%mod*cv[i])%mod;
		ans=(ans+1ll*f*pw[i])%mod;
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：hhoppitree (赞：3)

可以证明：若记 $G(n)=\sum\limits_{i=0}^{n-1}i^ka^i$，则存在 $k$ 次多项式 $F(n)$ 使得，$G(n)=a^nF(n)-F(0)$。

由 $G(n+1)-G(n)=n^ka^n=a^{n+1}F(n+1)-a^nF(n)$，故 $F(n+1)=\dfrac{n^k+F(n)}{a}$，故可对任意 $0\le i\le k+1$ 递推出 $F(i)=k_iF(0)+b_i$。

由 $F(n)$ 是 $k$ 次多项式知 $\sum\limits_{i=0}^{k+1}(-1)^i\dbinom{k+1}{i}F(i)=0$，此时即可解出 $F(0)$，进而得出 $F$ 的前 $k+1$ 项，使用拉格朗日插值即可求出 $F(n)$，最终得到 $G(n)$，即为答案，容易做到 $\mathcal{O}(k+\log n)$。

---

## 作者：Lyrella (赞：2)

在开始前我们可以先判掉 $a=1$ 的情况。此时答案变成了 $\sum i^k$，我们可以 $\mathcal O(k)$ 拉插求解，具体可见 [CF622F](https://www.luogu.com.cn/problem/CF622F)。

在这里我们还是证一下这个东西是 $k+1$ 次多项式。

证明考虑**扰动法**：
$$
\begin{aligned}
S_k(n)&=\sum_{i=0}^ni^k\\
&=\sum_{i=0}^n(i+1)^k-(n+1)^k\\
&=\sum_{i=0}^n\sum_{j=0}^k{k\choose j}i^j-(n+1)^k\\
&=\sum_{j=0}^k{k\choose j}S_j(n)-(n+1)^k\\
&=\sum_{j=0}^{k-2}{k\choose j}S_j(n)+kS_{k-1}(n)+S_k(n)-(n+1)^k
\end{aligned}
$$
化简有：
$$
S_k(n)={(n+1)^{k+1}-\sum\limits_{i=0}^{k-1}{k+1\choose i}S_i(n)\over k+1}
$$
这个东西就可以拉插了。~~正片结束赠片开始。~~

开始沉浸式推式子，对于这种 $n$ 巨大的式子我们的想法是考虑有限积分。设 $f(n)=\sum_0^nx^ka^x\delta x$，那么我们要求的即为 $f(n+1)-f(1)$。对于普通版我们可以直接把 $f(n)$ 里面的普通幂拆成下降幂直接做，但是这样你需要求斯特林数，复杂度是 $\mathcal O(n^2)$ 或 $\mathcal O(n\log n)$ 的：
$$
\begin{aligned}
\sum_{i=1}^ni^ka^i&=\sum_{j=0}^k{k\brace j}\sum_{i=1}^ni^{\underline{j}}a^i\\
&=\sum_{i=0}^k{k\brace i}\sum\nolimits_{1}^{n+1}x^{\underline{i}}a^x\delta x
\end{aligned}
$$
我们可以对式子进行分部求和：
$$
\sum u\Delta v=uv-\sum \text Ev\Delta u
$$
于是就有：
$$
\begin{aligned}
\sum\nolimits x^{\underline{k}}a^x\delta x&={x^{\underline{k}}a^x\over a-1}-\sum{a^{x+1}\over a-1}kx^{\underline{k-1}}\delta x\\
&={x^{\underline{k}}a^x\over a-1}-{ka\over a-1}\sum a^{x}x^{\underline{k-1}}\delta x\\
\end{aligned}
$$
最后归纳可得：
$$
\sum\nolimits x^{\underline{k}}a^x\delta x={a^x\over a-1}\sum_{i=0}^k\left(-{a\over a-1}\right)^ik^{\underline{i}}x^{\underline{k-i}}
$$
我们可以发现这是一个 $k$ 次多项式，因为启动斯特林数的复杂度无法接受，于是设 $f(n)=a^ng(x)-a^0g(0)$，可以得到 $g(m)=a^{-m}(f(m)+g(0))$，注意这里 $g$ 为 $k$ 次多项式。

到这里我们如果能够求出 $g(0)$ 就可以递推出 $g(x),x\in[1,k]$，然后又因为 $f$ 是一个 $k$ 的多项式于是我们就可以 $\mathcal O(k)$ 拉插求了。考虑求 $g(0)$。

因为我们知道 $g$ 是一个 $k$ 次多项式，所以有：
$$
\begin{aligned}
\Delta^{k+1}g&=0\\
\left(\text E-1\right)^{k+1}g&=0\\
\sum_{i=0}^{k+1}{k+1\choose i}(-1)^{k+1-i}g(i)&=0\\
\sum_{i=0}^{k+1}{k+1\choose i}(-1)^{k+1-i}a^{-i}[f(i)+g(0)]&=0\\
-\left(1-a\over a\right)^{k+1}g(0)&=\sum_{i=0}^{k+1}{k+1\choose i}(-1)^{k+1-i}a^{-i}f(i)\\
g(0)&=-\left(1-a\over a\right)^{-k-1}\sum_{i=0}^{k+1}{k+1\choose i}(-1)^{k+1-i}a^{-i}f(i)
\end{aligned}
$$
于是就可以先求出 $f(i)$ 再得到 $g(0)$ 了，有了 $g(0)$ 后就好拉插做了，复杂度 $\mathcal O(k)$。

---

## 作者：arrow_king (赞：2)

本文希望让没学过有限微积分的读者弄明白“为什么 $g(n)$ 是一个 $k$ 次多项式”，这也是本题拉插做法的难点之一。~~我才不会告诉你我是看不懂有限微积分的式子~~

# 题意

求
$$
\sum_{i=1}^ni^ka^i
$$
在模 $998244353$ 意义下的值。$n\le998244352$，$k\le10^7$。

# 思路

首先 $a=1$ 的情况是 CF622F，可以直接拉格朗日插值做到 $O(k)$ 求答案。

我们设
$$
f(n)=\sum_{i=0}^{n-1}i^ka^i
$$
我们猜测 $f(n)$ 可以表示成 $a^n$ 乘上一个 $k$ 次多项式的形式。下面给出证明：

我们设多项式 $f_m(n)=(n-m)^ka^{-m}$，那么 $i^k=a^{n-i}f_{n-i}(n)$，而 $f_m(n)$ 显然是 $k$ 次多项式。考虑 $f$ 的形式
$$
f(n)=\sum_{i=0}^{n-1}a^ii^k=a^n\sum_{i=0}^{n-1}f_{n-i}(n)
$$
所以右边那一坨最高就是 $k+1$ 次多项式，但是最高次项系数是 $\sum_{i=1}^na^{-i}$，是一个收敛级数，因此可以证明不会有 $n^{k+1}$ 项。所以原命题得证。

----

因此我们设 $f(n)=a^ng(n)-a^0g(0)$，其中 $g$ 是一个 $k$ 次多项式。

我们考虑到答案就是 $f(n+1)-f(1)$，因此试着用拉格朗日插值法求出 $f(n+1)$ 的值。因为 $g$ 是 $k$ 次多项式，所以我们只需要 $g(0),g(1),\dots,g(k)$ 就可以用连续点值的 $O(k)$ 插值（还是见 CF622F）。而 $g(n)$ 的值又可以通过
$$
g(n)=\dfrac{f(n)+a^0g(0)}{a^n}
$$
求出，而 $f$ 显然可以 $O(k)$ 递推，因此我们只需要求出 $g(0)$。

考虑到 $g$ 是 $k$ 次多项式，因此 $\Delta^{k+1}g=0$，而
$$
\begin{aligned}
\Delta^{k+1}g(0)&=(\mathsf E-1)^{k+1}g(0)\\
&=\sum_{i=0}^{k+1}\dbinom{k+1}i(-1)^{k-i+1}\mathsf E^ig(0)\\
&=\sum_{i=0}^{k+1}\dbinom{k+1}i(-1)^{k-i+1}g(i)\\
&=\sum_{i=0}^{k+1}\dbinom{k+1}i(-1)^{k-i+1}a^{-i}[g(0)+f(i)]\\
&=g(0)(a^{-1}-1)^{k+1}+\sum_{i=0}^{k+1}\dbinom{k+1}i(-1)^{k-i+1}a^{-i}f(i)=0
\end{aligned}\\
g(0)=-(1-a^{-1})^{-k-1}\sum_{i=0}^{k+1}\dbinom{k+1}i(-a)^{-i}f(i)
$$

显然可以 $O(k)$ 求解。因此我们可以在 $O(k)$ 求出 $f(0)\sim f(k)$ 和 $g(0)\sim g(k)$，因此就可以拉插求出 $g(n+1)$。

> 解释一下这个式子。符号 $\mathsf E$ 是一个针对函数的**操作**，定义为
> $$
> \mathsf Ef(x)=f(x+1)
> $$
> 而差分的定义是
> $$
> \Delta f(n)=f(n+1)-f(n)=(\mathsf E-1)f(n)
> $$
> 因此高阶差分操作 $\Delta^n$ 可以被二项式定理展开为
> $$
> \Delta^n=(\mathsf E-1)^n=\sum_{k=0}^n\dbinom nk\mathsf E^k(-1)^{n-k} 
> $$
> 而显然有 $\mathsf E^nf(x)=f(x+n)$。

得到了 $g(0)$ 就可以描述整个 $g$ 函数了。最后只需要拉格朗日插值求出 $g(n+1)$ 就可以得到最终的答案：
$$
a^{n+1}g(n+1)-ag(1)
$$

----

顺便说一下线性的拉格朗日插值。

普通的拉格朗日插值公式是：
$$
f(n)=\sum_{i=1}^kf(x_i)\prod_{j\neq i}\dfrac{n-x_j}{x_i-x_j}
$$
在线性过程中首先需要的是 $f(1),f(2),\dots,f(k)$，这样 $x_i=i$，因此我们看分子分母是什么：

分母很显然。
$$
(i-1)(i-2)\cdots1(-1)(-2)\cdots(k-i)=(-1)^{k-i}(i-1)!(k-i)!
$$
分子也显然：
$$
(n-1)(n-2)\cdots(n-i+1)(n-i-1)\cdots(n-k)
$$
处理前后缀积就可以 $O(1)$ 查询了！


# 代码

本题的核心代码。

```cpp
il ll lagrange(ll *f,ll n,ll x) {
//线性的拉格朗日插值，为了方便，修改了上面的公式使得它能够支持从 f(0),f(1),...,f(k) 插值出 f(n)
	prod[0][0]=x,prod[1][n+1]=1;
	for(int i=1;i<=n;i++) prod[0][i]=1ll*prod[0][i-1]*(x-i)%mod;
	for(int i=n;i>=0;i--) prod[1][i]=1ll*prod[1][i+1]*(x-i)%mod;
	ll ans=0;
	for(int i=0;i<=n;i++) {
		ll mul=((n-i)&1)?mod-1:1,a=1ll*(i==0?1:prod[0][i-1])*prod[1][i+1]%mod,b=1ll*(i==0?1:inv[i])*inv[n-i]%mod;
		ans=(ans+1ll*mul*f[i]%mod*a%mod*b%mod)%mod;
	}
	return ans;
}
il void sieve(ll k) {}
//线性筛出 1~10000000 的 k 次幂

il ll solve_sum(ll n,ll a,ll k) {
	sieve(k);
	ll inva=qpow(a,mod-2);
	f[0]=0;for(ll i=0,now=1;i<=k+1;i++,now=1ll*now*a%mod) f[i+1]=(f[i]+1ll*poww[i]*now%mod)%mod;
	if(n<=k) return f[n+1];
//注意：本题卡空间，这行注释上面的 f 是式子中的 f，下面的 f 是式子中的 g，万万分清！
//不这么做会MLE*8
	f[0]=0;for(ll i=0,pww=1;i<=k+1;i++,pww=1ll*pww*(mod-inva)%mod) f[0]=(f[0]+1ll*C(k+1,i)*pww%mod*f[i]%mod)%mod;
	f[0]=1ll*(mod-f[0])%mod*qpow(qpow((1ll-inva+mod)%mod,k+1),mod-2)%mod;
	for(ll i=1,pww=inva;i<=k;i++,pww=1ll*pww*inva%mod) f[i]=1ll*(f[0]+f[i])%mod*pww%mod;
	ll g_n1=lagrange(f,k,n+1);
	return (1ll*qpow(a,n+1)*g_n1%mod-1ll*a*f[1]%mod+mod)%mod;
}
il void solve_kpowersum() {}
//解决 a=1 的特殊情况
```

---

## 作者：Martin_MHT (赞：2)

# 洛谷P5907 数列求和加强版 / SPOJ MOON4
### 题面描述
求
$$\sum_{i=1}^ni^ka^i$$
对 $998244353$ 取模的结果。


### $O(k)$ 做法
为了推导方便，下令 $p = a^{-1}$。即求
$$\sum_{i=1}^n\frac{i^k}{p^i}$$

我们裂项，即尝试寻找多项式 $f(x)$，使得

$$\frac{x^k}{p^x} = \frac{f(x)}{p^{x-1}} - \frac{f(x+1)}{p^x}$$

即
$$x^k = pf(x) - f(x+1)(*)$$

答案将是 $f(1) - \frac{f(n+1)}{p^n}$。

显然 $\deg f = k$。

这样临项点值的差，由于恒等式 $(x + 1)^{\underline{n}}- x ^ {\underline{n}} = nx^{\underline{n-1}}$，可以考虑展开成下降幂来推导。具体地，设 $f(x) = \sum\limits_{i = 0}^n c_ix^{\underline{i}}$，则可以展开 $(*)$ 式：

$$
    \begin{aligned}
        x^k = \sum^k_{i = 0}\begin{Bmatrix}k \\ i\end{Bmatrix}x^{\underline{i}} &= \sum_{i = 0}^k pc_ix^{\underline{i}} - \sum_{i = 0}^k c_i(x + 1)^{\underline{i}} \\
        &= \sum_{i = 0}^k(p-1)c_ix^{\underline{i}} - \sum_{i=1}^kic_ix^{\underline{i-1}} \\
        &= (p-1)c_kx^{\underline{k}}+\sum_{i=0}^{k-1}((p-1)c_i-(i+1)c_{i+1})x^{\underline{i}}
    \end{aligned}$$

对比系数能够得到：

$$(p - 1)c_k = \begin{Bmatrix}k \\ k\end{Bmatrix} = 1$$

$i = 0, 1...,k-1$：

$$(p - 1)c_i - (i+1)c_{i+1} = \begin{Bmatrix}k \\ i\end{Bmatrix} $$

求一行斯特林数是 $O(k \log k)$ 的，需要进一步优化。

直接求每一项系数也许有些困难，但是这里有一个取巧的办法：
如果我们知道 $f(0)$，那么通过 $(*)$ 式，可以递推出 $f(1), ...f(k)$，那么就可以利用这 $k+1$ 个点值进行线性拉格朗日插值，避开了这个难处。

而 $f(0)=c_0$，因此下面我们只需要求出 $c_0$ 即可。通过上面的递推式，我们恰好可以将这个系数的递推式求出来，即 

$$c_0 = \frac 1 {p - 1}\sum_{i = 0}^k\begin{Bmatrix}k \\ i\end{Bmatrix} \frac{i!}{(p-1)^i}$$

这个式子是可以 $O(k)$ 求解的，参见 EI 的 Binomial Sum。由于我也是第一次学这个所以下面还是写一下过程。

下面令 $t = (p-1)^{-1}$，求

$$\sum_{i = 0}^k\begin{Bmatrix}k \\ i\end{Bmatrix} t^i i!$$

写成生成函数就是

$$\begin{aligned}
        \sum_{i = 0}^kt^i \begin{Bmatrix}k \\ i\end{Bmatrix} i! &= \sum_{i = 0}^k t^i \left[\frac{z^k}{k!}\right](\exp z-1)^i \\ &= \left[\frac{z^k}{k!}\right]\sum_{i=0}^k (t(\exp z - 1))^i \\ &= \left[\frac{z^k}{k!}\right] \frac 1 {1 - t(\exp z - 1)}
    \end{aligned}
$$

令 $u = \exp z$，对于 $z$ 来说，这本应是一个无穷级数，但利用 $\exp z - 1$ 没有常数项的性质，我们可以将对于 $u$ 的求和上限限制在 $k$ 处（截断），之后的项都不会有贡献。因此就是求

$$\left[\frac{z^k}{k!}\right] \frac {1 - (t(\exp z - 1))^{k+1}} {1 - t(\exp z - 1)}$$

那么 GF 写作：

$$G(u) = \frac {1 - (t(u-1))^{k+1}}{1-t(u-1)}$$

这是一个关于 $u$ 的有理分式，将分母移到一边就可以 $O(k)$ 求出 $u^i$  处系数，然后就做完了。我不想省略下面的细节，继续推导。我们设  $G(u) = \sum\limits_{i\ge0}g_iu^i$，那么
$$g_0 = G(0) = \frac{1+t^{k+1}(-1)^k}{1+t}$$

$$(1+t-tu)G = 1-t^{k+1}(u-1)^{k+1}$$

提取系数就是

$$(1+t)g_i-tg_{i-1}=t^{k+1}\binom{k+1}{i}(-1)^{k-i}$$

最后，我们得到了，
$$\begin{aligned}
    c_0 &= t \left[\frac{z^k}{k!}\right] \sum_{i=0}^k g_i \exp iz \\ &= t\sum_{i=0}^k g_i i^k
\end{aligned}$$

这道题几乎做完了。剩下的就是特判 $a=p=1$ 的情况，此时问题退化为自然数幂和，可以直接线性拉格朗日插值。

代码（代码中，使用 $m$ 代替了 $k$）：
```cpp
#include <cstdio>
#define ll long long
const int M = 1e7, mod = 998244353;
inline int mul(int a, int b) {return (ll)a * b % mod;}
inline int add(int a, int b) {int ret = a + b; return ret >= mod ? ret - mod : ret;}
inline int minus(int a, int b) {int ret = a - b; return ret < 0 ? ret + mod : ret;}
inline int qpow(int a, int b) {
    int ret = 1;
    for(; b; b >>= 1, a = mul(a, a))
        if(b & 1)   ret = mul(ret, a);
    return ret;
}
int f[M + 5], g[M + 5], p, n, m, ip, ip1;
int fac[M + 5], invf[M + 5];
int pre, suf[M + 5];
int cnt, v[M + 5], pr[M >> 2], pwm[M + 5];
inline int C(int m, int n) {return (ll)fac[m] * invf[n] % mod * invf[m - n] % mod;}
inline int pn1(int num, int p) {return p & 1 ? mod - num : num;}

int main() {
    scanf("%d%d%d", &n, &ip, &m);
    //initialization
    fac[0] = 1;
    p = qpow(ip, mod - 2);
    for(int i = 1; i <= m + 1; ++i) fac[i] = mul(fac[i - 1], i);
    invf[m + 1] = qpow(fac[m + 1], mod - 2);
    for(int i = m; i >= 0; --i) invf[i] = mul(invf[i + 1], i + 1);

    pwm[1] = 1;
    for(int i = 2; i <= m + 2; ++i) {
        if(!v[i]) v[i] = pr[++cnt] = i, pwm[i] = qpow(i, m);
        for(int j = 1; j <= cnt; ++j) {
            if(pr[j] > v[i] || i * pr[j] > m + 2)    break;
            v[i * pr[j]] = pr[j];
            pwm[i * pr[j]] = mul(pwm[i], pwm[pr[j]]);
        }
    }
    ip1 = qpow(p - 1, mod - 2);
    if(p ^ 1) {
	    //calulate g, f
	    int t1 = qpow(ip1 + 1, mod - 2), t2 = qpow(ip1, m + 1);
	    // t1 = 1/t + 1, t2 = t ^ {m + 1}
	    g[0] = mul(t1, 1 + pn1(t2, m));
	    for(int i = 1; i <= m; ++i) {
	        g[i] = mul(t1, mul(ip1, g[i - 1]) + mul(C(m + 1, i), pn1(t2, m - i)));
	        f[0] = add(f[0], mul(pwm[i], g[i]));
	    }
		f[0] = mul(ip1, f[0]);
	}
    if(p ^ 1)	for(int i = 1; i <= m; ++i)
        	f[i] = minus(mul(p, f[i - 1]), pwm[i - 1]);
	else for(int i = 1; i <= m + 1; ++i)
		f[i] = add(f[i - 1], pwm[i]);
       
    //prepare for lagruange interpolation
    if(p == 1)	--n, ++m;
    pre = n + 1, suf[m + 1] = 1;
//    for(int i = 1; i <= m; ++i) pre[i] = mul(pre[i - 1], (mod + n + 1 - i) % mod);
    for(int i = m; i >= 1; --i) suf[i] = mul(suf[i + 1], minus(n + 1, i));
    
    //calculate answer
    int Ans = mul(f[0], pn1(mul(suf[1], invf[m]), m));
    for(int i = 1; i <= m; ++i)
       Ans = add(Ans, pn1(mul(f[i], mul(mul(pre, suf[i + 1]), mul(invf[i], invf[m - i]))), m - i)),
    	pre = mul(pre, minus(n + 1, i));
    if(p ^ 1)	Ans = minus(f[1], mul(Ans, qpow(qpow(p, n), mod - 2)));
	
    printf("%d", Ans);
    return 0;
}

```

---

## 作者：forest114514 (赞：1)

**P5907 数列求和加强版 / SPOJ MOON4**

一个过程稍微详细一点的 Binomial Sums 的做法。

求 $\sum\limits_{i=0}^{k}a^ii^n$，$k\leq n$ 的时候暴力就行了，为了和学习笔记统一 $n,k$ 和题目中是相反的。

不难构造出 $G(x)=ae^x,b_X=[x^n]G(x)^i,F(x)=\frac{1-x^{k+1}}{1-x}$，答案就是 $[x^n]F(G(x))$。

小 F 认为一阶线性 ODE 都是齐次的，邮电部诗人了。

  $$
   \begin{aligned}
   	F(x)+(x-1)F'(x)&=(x^{k+1}-1)'=(x^{k+1})'\\
   	F(x+a)+(x+a-1)F'(x+a)&=\left[(x+a)^{k+1}\right]'\\
   	\mathbb F(x+a)+(x+a-1)\mathbb F'(x+a)&=\left[\sum\limits_{i=0}^{n}\binom{k+1}{i}a^{k+1-i}x^i\right]'+(n+1)x^n\sum\limits_{i=n}^{k}\binom{i}{n}a^{i-n}\\
   	\mathbb F(x)+(x-1)\mathbb F'(x)&=\left[\sum\limits_{i=0}^{n}\binom{k+1}{i}a^{k+1-i}(x-a)^i\right]'+(n+1)(x-a)^n\sum\limits_{i=n}^{k}\binom{i}{n}a^{i-n}\\
   	\mathbb F(x)+(x-1)\mathbb F'(x)&=\left[\sum\limits_{i=0}^{n}\binom{k+1}{i}a^{k+1-i}\sum\limits_{j=0}^{i}\binom{i}{j}(-a)^{i-j}x^j\right]'+(n+1)\sum\limits_{i=n}^{k}\binom{i}{n}a^{i-n}\sum\limits_{j=0}^{n}\binom{n}{j}(-a)^{n-j}x^j\\
   	
   \end{aligned}
   $$
   好了现在有几个问题需要解决：

   1. $\sum\limits_{i=0}^{n}\binom{k+1}{i}a^{k+1-i}\sum\limits_{j=0}^{i}\binom{i}{j}(-a)^{i-j}x^j$，相信做过省选联考那道组合数问题的同志们立马能知道怎么推。
      $$
      \begin{aligned}
       &\sum\limits_{i=0}^{n}\binom{k+1}{i}a^{k+1-i}\sum\limits_{j=0}^{i}\binom{i}{j}(-a)^{i-j}x^j\\
      =&\sum\limits_{i=0}^{n}\sum\limits_{j=0}^{i}\binom{k+1}{i}\binom{i}{j}(-1)^{i-j}a^{k+1-j}x^j\\
      =&\sum\limits_{i=0}^{n}\sum\limits_{j=0}^{i}\binom{k+1}{j}\binom{k-j}{i-j}(-1)^{i-j}a^{k+1-j}x^j\\
      =&\sum\limits_{j=0}^{n}\binom{k+1}{j}a^{k-j}x^j\sum\limits_{d=0}^{n-j}\binom{k+1-j}{d}(-1)^{d}\\
      
      &\text{注意到}\\
      &\sum\limits_{d=0}^{n-j}\binom{k+1-j}{d}(-1)^{d}\\
      =&\sum\limits_{d=0}^{n-j}\left[\binom{k-j}{d}+\binom{k-j}{d-1}\right](-1)^{d}\\
      =&\sum\limits_{d=0}^{n-j}\binom{k-j}{d}(-1)^{d}-\sum\limits_{d=0}^{n-j-1}\binom{k-j}{d}(-1)^{d}\\
      =&\binom{k-j}{n-j}(-1)^{n-j}\\
      &\text{所以原式等于} \sum\limits_{j=0}^{n}(-1)^{n-j}\binom{k+1}{j}\binom{k-j}{n-j}a^{k-j}x^j\\
      &\text{显然导数就是}\sum\limits_{j=1}^{n}(-1)^{n-j}\binom{k+1}{j}\binom{k-j}{n-j}a^{k-j}jx^{j-1}
      
      \end{aligned}
      $$

2. $\sum\limits_{i=n}^{k}\binom{i}{n}a^{i-n}$ 怎么求，相信会推上面的式子这个也不难推，不妨设这个东西为 $T(n)$，先特判 $a=1$ 就是 $\binom{k+1}{n+1}$。
   $$
   \begin{aligned}
   T(0)&=\sum\limits_{i=1}^{k}a^i=\frac{a^{k+1}-1}{a-1}
   \\
   T(n)&=\sum\limits_{i=n}^{k}\binom{i}{n}a^{i-n}\\
   &=\sum\limits_{i=n}^{k}\left[\binom{i-1}{n}+\binom{i-1}{n-1}\right]a^{i-n}\\
   &=a\sum\limits_{i-1=n}^{k-1}\binom{i-1}{n}a^{i-1-n}+\sum\limits_{i-1=n-1}^{k-1}
   \binom{i-1}{n-1}a^{(i-1)-(n-1)}\\
   &=a(T(n)-\binom{k}{n}a^{k-n})+T(n-1)-\binom{k}{n-1}a^{k-n+1}\\
   &=aT(n)+T(n-1)-\binom{k+1}{n}a^{k-n+1}
   \end{aligned}
   $$
   可以直接 $O(n)$ 递推，$(k+1)^{\underline{i}}$ 是好求的。

最后直接递推的时候从低往高递推不是很方便，但是我们的 $\mathbb F$ 既然是 $F$ 的截断 $[x^n]\mathbb F$ 是容易求的，反着推简单很多。

时间复杂度按本题的符号的话是 $O(k)$。

---

## 作者：Starrykiller (赞：1)

[可能更好的阅读体验](https://www.cnblogs.com/Starrykiller/p/18009867/sol-p5904-p4948)

本题解是对 [warzone 的题解](https://www.luogu.com.cn/blog/_post/386265)的补充。如果你对有限微积分不是很了解，可以阅读 ta 的有限微积分 blog。

题意：求

$$
\sum_{i=1}^n i^k a^i
$$

- 普通版：$k\leq 2\times 10^3$。

- 加强版：$k\leq 10^7$。

如果你的普通版用的不是 warzone 的方法，可以参阅[此处](https://www.luogu.com.cn/blog/_post/385439)。由于一些奇怪的原因我无法把普通版的推导过程展示于此。

我们考虑加强版。

考虑 $a=1$，其实就是 [CF622F](https://www.luogu.com.cn/problem/CF622F)。但是本题中 $k\leq 10^7$，直接计算每一个数的 $k$ 次幂可能会寄。

但是我们知道，$n$ 个数中有 $\Theta(\dfrac{n}{\ln n})$ 个素数。考虑到 $\operatorname{Id}^k$ 是一个**完全积性函数**，于是我们只在素数处计算其 $k$ 次幂，然后在线性筛时顺便推出其他数的幂即可，这样时间复杂度是 $\Theta(\dfrac{k\log k}{\ln k})=\Theta(k)$ 的。

以下默认 $a\neq 1$。


设 $\displaystyle f(n)={\sum}_0^n x^ka^x\delta x$，答案即为 $f(n+1)-f(1)$。

注意到在普通版中我们有

$$
\begin{aligned}
\sum a^xx^k\delta x&=\dfrac{\textcolor{red}{a^x}x^{\underline{k}}}{a-1}-\frac{a\cdot k}{a-1}\textcolor{red}{a^{x}}\sum x^{\underline{k-1}}\delta x \\
&=a^x\left(\frac{x^{\underline{k}}}{a-1}-\frac{a\cdot k}{a-1}\sum x^{\underline{k-1}}\right)
\end{aligned}
$$

$a^x$ 右边的那一包东西显然是一个 $k$ 次多项式，不妨设为 $g(x)$。则我们有 

$${\sum}_l^r a^xx^k\delta x=a^rg(r)-a^lg(l)$$

则

$$f(n)=a^ng(n)-a^0g(0)$$

如果我们能知道 $g(0),g(1),\cdots,g(n)$ 的点值，就不难应用 Lagrange 插值法在 $\Theta(k)$ 内求出 $g(n+1)$。那么问题转化为如何求 $g(0),g(1),\cdots,g(n)$。

我们考虑到 


$$f(n)=a^ng(n)-a^0g(0)$$

即

$$g(n)=\frac{f(n)+g(0)}{a^{n}}$$

$f(0),f(1),\cdots,f(k)$ 可以 $\Theta(k)$ 递推。那么现在的当务之急就是求出 $g(0)$ 了。

我们知道 $\deg g=k$，这意味着 $\Delta^{k+1} g=0$。

于是

$$
\sum_{i=0}^{k+1}{k+1\choose i}(-1)^{k+1-i}\mathbf{E}^{i}g(0)=0 $$
$$
\sum_{i=0}^{k+1}{k+1\choose i}(-1)^{k+1-i}g(i)=0 $$
$$
\sum_{i=0}^{k+1}{k+1\choose i}(-1)^{k+1-i}a^{-i}[f(i)+g(0)]=0 $$
$$
\sum_{i=0}^{k+1}{k+1\choose i}(-1)^{k+1-i}a^{-i}f(i)+\sum_{i=0}^{k+1}{k+1\choose i}(-1)^{k+1-i}a^{-i}g(0)=0 $$
$$
\sum_{i=0}^{k+1}{k+1\choose i}(-1)^{k+1-i}a^{-i}f(i)+(a^{-1}-1)^{k+1}g(0)=0 $$
$$
g(0)=-(a^{-1}-1)^{-(k+1)}\sum_{i=0}^{k+1}{k+1\choose i}(-1)^{k+1-i}a^{-i}f(i)
$$

不难 $\Theta(k)$ 求出。综上我们在 $\Theta(k)$ 的时间复杂度内解决了本题。

答案即为 $a^{n+1}g(n+1)-a\cdot g(1)$

顺便讲一下如何 $\Theta(k)$ 插值。

注意到我们只需要算 $g(n+1)$。

我们有

$$
g(n+1)=\sum_{i=0}^{k}g(i)\frac{\prod_{j\neq i}(n+1-j)}{\prod_{j\neq i}(i-j)}$$

分母就是

$$i(i-1)\cdots 2\cdot 1\cdot (-1)\cdot (-2)\cdots (i-k)$$

即为

$$(-1)^{k-i}i!(k-i)!$$

分子就是

$$\frac{(n+1-0)(n+1-1)\cdots(n+1-k)}{n+1-i}$$

所以分式即为

$$(-1)^{k-i}\frac{(n+1-0)(n+1-1)\cdots(n+1-k)}{(n+1-i)i!(k-i)!}$$

可以前后缀预处理做到严格 $\Theta(k)$。

---

