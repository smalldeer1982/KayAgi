# 【模板】Chirp Z-Transform

## 题目描述

给定一个 $n$ 项多项式 $P(x)$ 以及 $c, m$，请计算 $P(c^0),P(c^1),\dots,P(c^{m-1})$。所有答案都对 $998244353$ 取模。

## 说明/提示

对于 $100\%$ 的数据，$1\le n,m\le 10^6,0\le c,a_i<998244353$.

## 样例 #1

### 输入

```
3 3 3
3 3 3```

### 输出

```
9 39 273```

# 题解

## 作者：s_r_f (赞：12)

$ans_i = F(c^i) = \sum\limits_{j=0}^{n-1} a_jc^{ij}$

众所周知, $ij = \binom{i+j}{2} - \binom{i}{2} - \binom{j}{2}$ :

$ans_i = c^{-\binom{i}{2}} \sum\limits_{j=0}^{n-1} a_jc^{-\binom{j}{2}} c^{\binom{i+j}{2}}$

不难发现这是一个卷积形式，模数 $998244353$ 为 NTT 模数, NTT 即可。

几个细节：

$1.$ 注意到我们是把一个长度为 $n+m$ 的多项式和 长度为 $n$ 的多项式做卷积，但是我们只需要卷积结果的第 $n - (n+m-1)$ 项,由于 NTT 是循环卷积，所以我们可以把多项式长度设为 $n+m$ , 对答案没有影响。

$2.$ 每次用快速幂算 $c^{-\binom{i}{2}}$ 和 $c^{\binom{i}{2}}$ 是$\Theta((n+m)\log mod)$ 的,非常慢。

可以 $\Theta(\sqrt{mod})$ 预处理然后光速幂 $\Theta(1)$ 查询,或者用两次前缀积直接递推结果.

code(最慢的点324ms) : 
```cpp
#include <bits/stdc++.h>
#define LL unsigned long long
#define uint unsigned int
using namespace std;
template <typename T> void read(T &x){
	static char ch; x = 0,ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) x = x * 10 + ch - '0',ch = getchar();
}
inline void write(int x){if (x > 9) write(x/10); putchar(x%10+'0'); }
const int P = 998244353,N = 1<<21;
inline uint power(uint x,int y){
	y %= P-1;
	static uint r; r = 1; while (y){ if (y&1) r = (LL)r * x % P; x = (LL)x * x % P,y >>= 1; }
	return r;
}
int n,m,c,R[N],L; uint a[N],w[N<<1],iw[N<<1],pwc[N],ipwc[N],F[N],G[N];
inline int getR(int n){
	int i,l = 1,Lim = 2; while (Lim <= n) Lim <<= 1,++l;
	for (i = 0; i < Lim; ++i) R[i] = (R[i>>1]>>1) | ((i&1)<<l-1);
	return Lim;
}
inline void NTT(uint *A,int n){
	register int i,j,k; uint v;
	for (i = 1; i < n; ++i) if (i < R[i]) swap(A[i],A[R[i]]);
	for (i = 1; i < n; i <<= 1) for (j = 0; j < n; j += i << 1) for (k = j; k < i+j; ++k)
		v = (LL)A[k+i] * w[(i<<1)+k-j] % P,A[k+i] = (A[k]<v)?(A[k]+P-v):(A[k]-v),A[k] = (A[k]+v>=P)?(A[k]+v-P):(A[k]+v);
}
inline void iNTT(uint *A,int n){
	register int i,j,k; uint v;
	for (i = 1; i < n; ++i) if (i < R[i]) swap(A[i],A[R[i]]);
	for (i = 1; i < n; i <<= 1) for (j = 0; j < n; j += i << 1) for (k = j; k < i+j; ++k)
		v = (LL)A[k+i] * iw[(i<<1)+k-j] % P,A[k+i] = (A[k]<v)?(A[k]+P-v):(A[k]-v),A[k] = (A[k]+v>=P)?(A[k]+v-P):(A[k]+v);
	for (i = 0,v = power(n,P-2); i < n; ++i) A[i] = (LL)A[i] * v % P;
}
int main(){
	register int i,j; uint v;
	read(n),read(c),read(m);
	pwc[1] = c,ipwc[1] = power(c,P-2);
	for (pwc[0] = i = 1; i <= n+m; ++i) pwc[i] = (LL)pwc[i-1] * pwc[1] % P;
	for (pwc[0] = i = 1; i <= n+m; ++i) pwc[i] = (LL)pwc[i] * pwc[i-1] % P;
	for (ipwc[0] = i = 1; i <= max(n,m); ++i) ipwc[i] = (LL)ipwc[i-1] * ipwc[1] % P;
	for (ipwc[0] = i = 1; i <= max(n,m); ++i) ipwc[i] = (LL)ipwc[i] * ipwc[i-1] % P;
	for (i = 0; i < n; ++i) read(a[i]),a[i] = (LL)a[i] * (i?ipwc[i-1]:1) % P;
	L = getR(n+m);
	for (i = 1,j = 2; j <= L; ++i,j <<= 1){
		int l = j + (j>>1);
		w[j] = 1,v = power(3,(P-1)/j);
		for (register int k = j+1; k <= l; ++k) w[k] = (LL)w[k-1] * v % P;
		iw[j] = 1,v = power(v,P-2);
		for (register int k = j+1; k <= l; ++k) iw[k] = (LL)iw[k-1] * v % P;
	}
	for (F[0] = 1,i = 1; i <= n+m; ++i) F[i] = pwc[i-1];
	for (i = 1; i <= n; ++i) G[i] = a[n-i];
	NTT(F,L); NTT(G,L);
	for (i = 0; i < L; ++i) F[i] = (LL)F[i] * G[i] % P;
	iNTT(F,L);
	for (i = 0; i < m; ++i) write((LL)F[i+n] * (i?ipwc[i-1]:1) % P),putchar(i<m?' ':'\n');
	return 0;
}
```

---

## 作者：peterwuyihong (赞：5)

题意：给你一个多项式 $P(x)$，和常数 $c$，求出 $P(c^i),i\in\{0,1,2\ldots m-1\}$

$$P(c)=a_0+a_1c+a_2c^2+\ldots a_{n-1}c^{n-1}$$

$$P(c^j)=\sum_{i=0}^{n-1}a_ic^{ij}$$

然后使用一个令人迷惑的操作，即 $ij=\dbinom {i+j}2-\dbinom i 2-\dbinom j 2$

$$P(c^j)=\sum_{i=0}^{n-1}a_ic^{\binom {i+j}2-\binom i 2-\binom j 2}$$

$$P(c^j)=c^{-\binom j 2}\sum_{i=0}^{n-1}a_ic^{\binom {i+j}2-\binom i 2}$$

减法卷积，你令 $\text{myee}_{n-1+m-1-i-j}=c^{\binom {i+j}2}$，然后

$$P(c^j)=c^{-\binom j 2}\sum_{i=0}^{n-1}\text{myee}_{n-1+m-1-j-i}a_ic^{-\binom i 2}$$

把后面的 $a$ 补成 $0$。

$$P(c^j)=c^{-\binom j 2}\sum_{i=0}^{n-1+m-1-j}\text{myee}_{n-1+m-1-j-i}a_ic^{-\binom i 2}$$

卷就行了。

```cpp
signed main(){
  int n,c,m;
  cin>>n>>c>>m;
  poly a;Read(a,n);a.resize(n+m-1);
  poly myee(n+m-1),g(n+m-1);
  for(int i=0;i<=n+m-2;i++)
    myee[n-1+m-1-i]=ksm(c,(i-1ll)*i/2%(p-1)),
    g[i]=Mul(ksm(c,p-1-(i*(i-1ll)/2)%(p-1)),a[i]);
  poly ans=myee*g;
  rep(i,0,m-1)cout<<Mul(ans[n-1+m-1-i],ksm(c,p-1-(i-1ll)*i/2%(p-1)))<<' ';
}
```

---

## 作者：Aleph1022 (赞：5)

题目所求即对于 $j = 0\dots m-1$ 求出
$$P(c^j) = \sum\limits_{i=0}^{n-1} c^{ij} a_i$$

的值。

容易证明 $ij = \frac{(i+j)^2-i^2-j^2}2$。  
那么
$$\begin{aligned}P(c^j) &= \sum\limits_{i=0}^{n-1} c^{ij} a_i\\&=\sum\limits_{i=0}^{n-1} c^{\frac{(i+j)^2-i^2-j^2}2} a_i\\&=c^{-\frac{j^2}2} \sum\limits_{i=0}^{n-1} c^{\frac{(i+j)^2}2} \cdot \left(a_ic^{-\frac{i^2}2}\right)\end{aligned}$$

不难发现这是卷积的形式，NTT 即可。  
——真的吗？

注意到指数可能不是整数，这意味着需要考虑二次剩余。  
但是很可能不存在。

然而另有 $ij = \binom{i+j}2 - \binom i2 - \binom j2$。  
用同样的方法可以推得卷积式子，并且指数都变成了整数。  
$O(n \log n) / O(n \log {\rm mod})$ 即可，其中 ${\rm mod}$ 为模数。

---

## 作者：Ruiqun2009 (赞：4)

## 简介

Chirp Z 变换，又称 Bluestein 算法，是任意长度的卷积。

这个算法可以在 $O(n\log n)$ 的时间复杂度内求解等比数列点值。

更形象化地：

给定三个整数 $n,m,c$，以及一个多项式 $A(x)$。

这个算法可以在 $O((n+m)\log (n+m))$ 的时间复杂度内求出
$$
A(1),A(c),A(c^2),\cdots,A(c^{m-1})
$$
当然，是在模意义下的。

## 实现

我们有几种实现方式。讲讲最主流的方式：

先想想组合数。根据组合数的定义 $\binom{n}{m}=\frac{n!}{m!(n-m)!}(n\geq m\geq 0)$，我们可以得到
$$
\binom{n}{2}=\dfrac{n!}{2!(n-2)!}=\dfrac{n(n-1)}{2}
$$
**这里即便除以零也没事，因为如同分式方程，没有必要在中途检验。**

首先是这个式子
$$
\begin{aligned}
xy&=\dfrac{x^2+y^2+2xy-x^2-y^2}{2}\\
&=\dfrac{x^2+y^2+2xy-x-y-x^2-y^2+x+y}{2}\\
&=\dfrac{x^2+y^2+2xy-x-y}{2}-\dfrac{x^2-x}{2}-\dfrac{y^2-y}{2}\\
&=\binom{x+y}{2}-\binom{x}{2}-\binom{y}{2}
\end{aligned}
$$
然后我们将要求的东西代入函数里
$$
\begin{aligned}
A(c^{k})&=\sum_{i=0}^{\deg A}c^{ik}A\lbrack i\rbrack\\
&=\sum_{i=0}^{\deg A}c^{\binom{i+k}{2}-\binom{i}{2}-\binom{k}{2}}A\lbrack i\rbrack\\
&=c^{-\binom{k}{2}}\sum_{i=0}^{\deg A}c^{\binom{i+k}{2}-\binom{i}{2}}A\lbrack i\rbrack
\end{aligned}
$$
这已经明摆着的是一个卷积的形式了。

我们只需要预处理出 $c$ 的幂，然后做卷积，最后乘上 $c^{-\binom{k}{2}}$ 就可以了。

---

但是显然这**甚至没有直接计算快**。我们试着加速。

设
$$
\begin{aligned}
P(x)&=\sum_{i=0}^{\deg A}A\lbrack \deg A-i\rbrack c^{-\binom{\deg A-i}{2}}x^i\\
Q(x)&=\sum_{i=0}^{\deg A}c^{\binom{i}{2}}x^i
\end{aligned}
$$
于是我们有
$$
\begin{aligned}
P(x)\lbrack i\rbrack&=A\lbrack \deg A-i\rbrack c^{-\binom{\deg A-i}{2}}\\
Q(x)\lbrack i\rbrack&=c^{\binom{i}{2}}
\end{aligned}
$$
再推一波式子。
$$
\begin{aligned}
(P(x)Q(x))\lbrack\deg A+k\rbrack&=\sum_{i=0}^{\deg A+k}(P(x)\lbrack \deg A+k-i\rbrack\times Q(x)\lbrack i\rbrack)\\
&=\sum_{i=0}^{\deg A+k}(A\lbrack{\color{red}i-k}\rbrack\times c^{-\binom{\color{red}i-k}{2}}\times c^\binom{i}{2})
\end{aligned}
$$
注意到此时 $i-k$ 可能小于零。于是我们设 $\forall i\not\in\lbrack0,\deg A\rbrack,A\lbrack i\rbrack=0$。

**在这一步中计算组合数发生除以零是没事的，因为如同分式方程，没有必要在中途检验。**
$$
\begin{aligned}
(P(x)Q(x))\lbrack\deg A+k\rbrack&=\sum_{i=0}^{\deg A+k}(A\lbrack i-k\rbrack\times c^{-\binom{i-k}{2}}\times c^\binom{i}{2})\\
&=\sum_{i=-k}^{\deg A}(A\lbrack i\rbrack\times c^{\binom{i+k}{2}-\binom{i}{2}})\\
&=\sum_{i=0}^{\deg A}(A\lbrack i\rbrack\times c^{\binom{i+k}{2}-\binom{i}{2}})\\
&=c^{\binom{k}{2}}\times A(c^k)
\end{aligned}
$$

于是我们对 $P(x)$ 和 $Q(x)$ 做卷积，可以得到 $c^{\binom{0}{2}}\times A(c^0),c^{\binom{1}{2}}\times A(c^1),\cdots,c^{\binom{m-1}{2}}\times A(c^{m-1})$。

**注意到 $\binom{0}{2}$ 和 $\binom{1}{2}$ 是不合法的，所以我们只能套公式。**

由于得到的结果是 $m$ 项的，所以我们要做的卷积长度为 $\deg A+m$（精确来说应该是 $2^{\lceil\log(\deg A+m)\rceil}$）。

## 代码
```cpp
inline void ChirpZ(size_t n, mint c, size_t m, vector<mint> a, vector<mint>& b) {
	static vector<mint> pwc, ipwc, f, g;
	pwc.resize(n + m + 1);
	ipwc.resize(n + m + 1);
	size_t i = 1, iend = std::max(n, m);
	pwc[1] = c;
	ipwc[1] = c.inv();
	for (pwc[0] = i = 1; i <= n + m; i++) pwc[i] = pwc[i - 1] * pwc[1];
	for (pwc[0] = i = 1; i <= n + m; i++) pwc[i] = pwc[i] * pwc[i - 1];
	for (ipwc[0] = i = 1; i <= iend; i++) ipwc[i] = ipwc[i - 1] * ipwc[1];
	for (ipwc[0] = i = 1; i <= iend; i++) ipwc[i] = ipwc[i] * ipwc[i - 1];
	for (i = 1; i < n; i++) a[i] *= ipwc[i - 1];
	size_t len = 1;
	int x = -1;
	while (len < n + m) len <<= 1, x++;
	get_rev(len, x);
	f.resize(len);
	g.resize(len);
	f[0] = 1;
	std::copy_n(pwc.begin(), n + m, f.begin() + 1);
	for (i = 1; i <= n; i++) g[i] = a[n - i];
	mul(n + m, n + m, f, g, f, len);
	b.resize(m);
	b[0] = f[n];
	for (i = 1; i < m; i++) b[i] = f[i + n] * ipwc[i - 1];
}
```

参考资料：

1. [Chirp Z 变换 - OI-Wiki](https://oi-wiki.org/math/poly/czt/)

---

## 作者：cyffff (赞：3)

[$\text{Link}$](https://www.luogu.com.cn/problem/P6800)

upd 2021.7.15：修式子和 $\LaTeX$。
## 题意
给 $n,m,c$ 和 $n-1$ 次多项式 $F(x)$，求出 $\forall k\in[0,m) F(c^k)$.

## 解法
首先我们有
$$F(c^k)=\sum_{i=0}^{n-1}a_ic^{ik}$$
考虑化 $ik$，
$$ik=\dfrac{2ik}{2}$$
$$=\dfrac{i^2+2ik+k^2-i-k-i^2+i-k^2+k}{2}$$
$$=\binom{i+k}{2}-\binom{i}{2}-\binom{k}{2}$$
于是就有 
$$F(c^k)=\sum_{i=0}^{n-1}a_ic^{ik}$$
$$=\sum_{i=0}^{n-1}a_ic^{\binom{i+k}{2}-\binom{i}{2}-\binom{k}{2}}$$
$$=c^{-\binom{k}{2}}\sum_{i=0}^{n-1}a_ic^{-\binom{i}{2}}c^{\binom{i+k}{2}}$$
预处理一下可以 $O(n\log n)$。

部分代码：
```cpp
n=read(),_c=read(),m=read();
c[0]=ic[0]=1;
for(int i=1;i<=n+m;i++){
	c[i]=1ll*c[i-1]*_c%mod;
}
for(int i=1;i<=n+m;i++){
	c[i]=1ll*c[i-1]*c[i]%mod;
}
ic[1]=qpow(_c,mod-2);
int qq=ic[1];
for(int i=1;i<=max(n,m);i++){
	ic[i]=1ll*ic[i-1]*qq%mod;
}
for(int i=1;i<=max(n,m);i++){
	ic[i]=1ll*ic[i-1]*ic[i]%mod;
}
f[0]=read();
for(int i=1;i<n;i++){
	f[i]=1ll*read()*ic[i-1]%mod;
}
init(n+m);
g[0]=1;
for(int i=1;i<=n+m;i++){
	g[i]=c[i-1];
}
reverse(f,f+n+1);
Mul(f,g);
for(int i=0;i<m;i++){
	write(1ll*f[i+n]*(i?ic[i-1]:1)%mod);
	out[len++]=' ';
}
```
再见 qwq~

---

## 作者：Fuyuki (赞：2)

$P(c^m)=\sum_{i=0}^{n-1}a_ic^{im}$

$\qquad\ \ \ \ =\sum_{i=0}^{n-1}a_ic^{\binom{i+m}{2}-\binom{i}{2}-\binom{m}{2}}$

$\qquad\ \ \ \ =c^{-\binom{m}{i}}\sum_{i=0}^{n-1}(a_ic^{-\binom{i}{2}})c^{\binom{i+m}{2}}$

这显然是个减法卷积的形式，可以在 $O((n+m)log)$ 的时间内求出。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define I inline int
#define V inline void
#define ll long long int
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define ROF(i,a,b) for(int i=a;i>=b;i--)
const int N=1<<21,mod=998244353;
int n,c,m,lmt,a[N],b[N],t[N],w[N],r[N];
I Pow(ll t,int x,ll s=1){
	for(;x;x>>=1,t=t*t%mod)if(x&1)s=s*t%mod;
	return s;
}
V init(int n){
	int l=-1,wn;
	for(lmt=1;lmt<=n;lmt<<=1)l++;
	FOR(i,1,lmt-1)r[i]=r[i>>1]>>1|(i&1)<<l;
	wn=Pow(3,mod>>++l),w[lmt>>1]=1;
	FOR(i,lmt/2+1,lmt-1)w[i]=1ll*w[i-1]*wn%mod;
	ROF(i,lmt/2-1,1)w[i]=w[i<<1];
}
V DFT(int*a,int l){
	static unsigned long long int tmp[N];
	int t,u=__builtin_ctz(lmt/l);
	FOR(i,0,l-1)tmp[i]=a[r[i]>>u];
	for(int i=1;i<l;i<<=1)for(int j=0,d=i<<1;j<l;j+=d)FOR(k,0,i-1)
		t=tmp[i|j|k]*w[i|k]%mod,tmp[i|j|k]=tmp[j|k]+mod-t,tmp[j|k]+=t;
	FOR(i,0,l-1)a[i]=tmp[i]%mod;
}
V IDFT(int*a,int l){
	reverse(a+1,a+l),DFT(a,l);
	int bk(mod-mod/l);
	FOR(i,0,l-1)a[i]=1ll*a[i]*bk%mod;
}
I f(int x){return 1ll*x*(x-1)/2%(mod-1);}
V dot(int*a,int*b,int l,int*c){while(l--)*c++=1ll**a++**b++%mod;}
int main(){
	scanf("%d%d%d",&n,&c,&m),init(n+m-1<<1);
	FOR(i,0,n-1)scanf("%d",a+i);
	FOR(i,0,n-1)a[i]=Pow(c,mod-1-f(i),a[i]);
	FOR(i,0,n+m-1)b[i]=Pow(c,f(i));
	reverse(a,a+n),DFT(a,lmt),DFT(b,lmt),dot(a,b,lmt,t),IDFT(t,lmt);
	FOR(i,0,m-1)cout<<Pow(c,mod-1-f(i),t[i+n-1])<<' ';
	return 0;
} 
```

---

## 作者：0xyz (赞：1)

我们就是要在一个多项式上求一个等比数列对应的函数值。

直接大力推导，注意到

$$\begin{aligned}C_{i+j}^2-C_i^2-C_j^2&=\frac{(i+j)(i+j-1)-i(i-1)-j(j-1)}{2}\\&=\frac{(i+j)^2-(i+j)-i^2+i-j^2+j}{2}\\&=\frac{(i+j)^2-i^2-j^2}{2}\\&=ij\end{aligned}$$

得到

$$\begin{aligned}P(c^i)&=\sum\limits_{j=0}\limits^{n-1}a_jc^{ij}\\&=\sum\limits_{j=0}\limits^{n-1}a_jc^{C_{i+j}^2-C_i^2-C_j^2}\\&=c^{-C_i^2}\sum\limits_{j=0}\limits^{n-1}a_jc^{-C_j^2}c^{C_{i+j}^2}\end{aligned}$$

这种形式可以卷积。令 $b_j=a_{-j}c^{-C_{-j}^2},d_j=c^{C_{j}^2}$。

那么 $P(c^i)=c^{C_i^2}\sum\limits_{j=0}^{n-1}b_{-j}d_{i+j}$。

但是这个 $b_{-j}$ 有点难搞。改成令 $b_j=a_{n-1-j}c^{-C_{n-1-j}^2},d_j=c^{C_{j}^2}$。

那么 $P(c^i)=c^{-C_i^2}\sum\limits_{j=0}^{n-1}b_{n-1-j}d_{i+j}$。

这样差不多可以了。我们发现，最多需要下标为 $n+m-2$
的 $d$，$n-1$ 的 $b$，所以我们可以用长为 $n$ 的 $b$ 和长为 $n+m-1$ 的 $d$ 卷积，也只需要这么多了。

最后的答案，我们将 $b$ 和 $d$ 卷好后，得到多项式 $p$，那么 $\forall i\in\{0,1,…,m-1\},P(c^i)=c^{-C_i^2}p_{n-1+i}$。我们在求解的时候，遇到次幂为负数的式子，可以先针对它的绝对值快速幂，然后再求逆元。

时间复杂度 $O((n+m)(\log mod+\log (n+m)))$，空间复杂度 $O(n+m)$，可以通过此题。注意数组要开到大于等于 $2n+m-1$ 的最小的 $2$ 的次幂，这里是 $2^{22}=4194304$。

```cpp
inline void CZT(){
	cin>>n>>c>>m;
	for(ll i=0;i<n;i++)cin>>a[i];
	for(ll i=0;i<n;i++)b[i]=a[n-1-i]*ksm(ksm(c,(n-1-i)*(n-2-i)/2),mod-2)%mod;
	for(ll i=0;i<n+m-1;i++)d[i]=ksm(c,i*(i-1)/2);
	for(l=1,Q=-1;l<=n+n+m-1;l<<=1,Q++);
	for(ll i=0;i<l;i++)re[i]=(re[i>>1]>>1)|((i&1)<<Q);
	NTT(b,l,1);NTT(d,l,1);
	for(ll i=0;i<l;i++)b[i]=b[i]*d[i]%mod;
	NTT(b,l,-1);
	for(ll i=0;i<m;i++)cout<<ksm(ksm(c,i*(i-1)/2),mod-2)*b[n-1+i]%mod<<' ';
}
```

可以优化一下这个算法。注意到我们对于 $c$ 的次幂计算得特别频繁，所以可以用 $O(\sqrt{mod})$ 预处理 $O(1)$ 查询，达到 $O(\sqrt{mod}+(n+m)\log(n+m))$ 的时间复杂度。这里就不放代码了。

有疑问或者建议可以评论或者私信。

---

## 作者：Anoshag_Ruwan (赞：0)

首先是关于不用 chirp-Z transform 的经典做法，需要求的是个等比数列 $C$ 的多项式多点求值，由于 $n,m$ 范围都在极限的 $10^6$ 级别，所以 $O(n \log^2n)$ 且常数巨大的多项式多点求值是过不了的。观察一下 $f(c^i)=\sum\limits_{j \ge 0}^{n-1}a_jc^{ij}$ 这个形式，发现比较难搞的是 ${ij}$，最好让指数上只有与 $i$ 或 $j$ 或其线性组合相关的东西。

于是想到核心转化：$ij$=$\tbinom{i+j}{2}-\tbinom{i}{2}-\tbinom{j}{2}$

$f(c^i)=\sum\limits_{j \ge 0}^{n-1}a_jc^{\tbinom{i+j}{2}-\tbinom{i}{2}-\tbinom{j}{2}}=c^{-\tbinom{i}{2}}\sum\limits_{j \ge 0}^{n-1}a_jc^{-\tbinom{j}{2}} \times c^{\tbinom{i+j}{2}}$

这是个典型的减法卷积形式，将其中一个数列反向再启动 ntt 板子即可。注意由于 ntt 是循环卷积，即如果使用 $2^k$ 次单位根，则结果的第 $x$ 项 $=\sum\limits_{i \in Z}f(2^ki+x)$，只需要总长度为 $n+m$ 对答案是不影响的。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm> 
using namespace std;
int q[2200011],r[2200011],k1,a[2200011],b[2200011],c[2200011],c1[2200011];
const int p=998244353;
inline int add(int x,int y){return x+y>=p?x+y-p:x+y;}
inline int ksm(int x,int y){
	int k=1,l=x;
	while(y){if(y&1)k=k*1ll*l%p;l=l*1ll*l%p,y>>=1;}
	return k;
}
inline void bter(){
	for(int i=0;i<k1;i++)
		r[i]=(r[i>>1]>>1)|(i&1?k1>>1:0);}
inline void bz(int *f){
	for(int i=0,k=ksm(k1,p-2);i<k1;i++)
		f[i]=f[i]*1ll*k%p;}
inline void ntt(int *f,bool m){
	int i,j,k,l,h;
	for(i=0;i<k1;i++)
		if(i<r[i])swap(f[i],f[r[i]]);
	for(i=1;i<k1;i<<=1){
		l=ksm(m?3:332748118,(p-1)/(i<<1));
		for(j=q[0]=1;j<i;j++)q[j]=q[j-1]*1ll*l%p;
		for(j=0;j<k1;j+=i<<1)
			for(h=j;h<j+i;h++)
				k=q[h-j]*1ll*f[h+i]%p,f[h+i]=add(f[h],p-k),f[h]=add(f[h],k);}
}
inline int rd(){
	int i=0,j=1;char g=getchar();
	while(g>57||g<48)g=getchar();
	while(g>47&&g<58)i=(i<<3)+(i<<1)+g-48,g=getchar();
	return i*1ll*j;
}
int main()
{
	int i,j,k,mx,u1,u2,n=rd(),gb=rd(),m=rd(),nv=ksm(gb,p-2);
	for(i=c[0]=c1[0]=u1=u2=1;i<=n+m;i++)
		c[i]=c[i-1]*1ll*u1%p,c1[i]=c1[i-1]*1ll*u2%p,\
		u1=u1*1ll*gb%p,u2=u2*1ll*nv%p; 
	for(k1=1;k1<n<<1||k1<n+m;k1<<=1);
	for(i=0;i<n;i++)a[i]=rd()*1ll*c1[i]%p;
	for(i=0;i<n+m-2-i;i++)swap(c[i],c[n+m-2-i]);
	bter();ntt(a,1);ntt(c,1);
	for(i=0;i<k1;i++)
		a[i]=a[i]*1ll*c[i]%p;
	ntt(a,0);bz(a);
	for(i=0;i<m;i++)
		c1[i]=c1[i]*1ll*a[n+m-i-2]%p;
	for(i=0;i<m;i++)
		printf("%d ",c1[i]);
	printf("\n");
	return 0;
}
```


---

