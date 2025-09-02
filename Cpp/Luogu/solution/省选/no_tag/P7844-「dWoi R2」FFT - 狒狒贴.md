# 「dWoi R2」FFT / 狒狒贴

## 题目背景

狱原权太正在尝试学习 FFT ……

## 题目描述

给定一个长度为 $2^n$ 的非负整数序列 $a_0,a_1,\cdots,a_{2^n-1}$，请计算序列 $A=\text{DFT}^k(a)$。

其中 $\text{DFT}(b)_i$ 定义为：

$$\text{DFT}(b)_i=\sum_{j=0}^{2^n-1}b_j\omega^{ij}\mod{998244353}$$
$$\omega\equiv3^{\frac{998244352}{2^n}}\pmod{998244353}$$

## 说明/提示

#### 数据规模与约定

 - Subtask 1（10 pts）：$n\le 11$ 且 $k\le 10$；
 - Subtask 2（10 pts）：$k\le 10$；
 - Subtask 3（20 pts）：$n\le 5$；
 - Subtask 4（30 pts）：$n\le 11$；
 - Subtask 5（30 pts）：无额外限制。

对于所有数据，$1\le n\le 17$，$1\le k\le10^{18}$，$0\le a_i\le 998244353$。

## 样例 #1

### 输入

```
3 3
1 2 3 4 5 6 7 8```

### 输出

```
288 831546728 224054051 383438562 998244321 614805727 774190238 166697561```

# 题解

## 作者：云浅知处 (赞：5)

方便起见，下文用 $n$ 表示原题中的 $2^n$。

我们注意到 $\text{DFT}$ 这个东西实际上就是乘一个范德蒙德矩阵：

$$
V=
\begin{bmatrix}
1&1&1&\cdots&1\\
1&\omega&\omega^2&\cdots&\omega^{n-1}\\
1&\omega^2&\omega^4&\cdots&\omega^{2(n-1)}\\
1&\omega^3&\omega^6&\cdots&\omega^{3(n-1)}\\
\vdots&\vdots&\vdots&\ddots&\vdots\\
1&\omega^{n-1}&\omega^{2(n-1)}&\cdots&\omega^{(n-1)(n-1)}\\
\end{bmatrix}
$$

因此计算 $\text{DFT}^k$ 实际也就是计算这个矩阵的 $k$ 次方。

我们先手算一下 $V^2$ 试试：

$$
V^2_{ij}=\sum_{k=0}^{n-1}\omega^{ik+kj}=\left(\sum_{k=0}^{n-1}\omega^{k}\right)\omega^{i+j}
$$

注意到除非 $i+j=n$ 或 $i+j=0$，那么这个 $\sum\omega^k$ 就会直接变成 $0$ 把整个消掉。

也就是说，$V$ 平方之后大概是个这个样子：

$$
V^2=
\begin{bmatrix}
n&0&0&\cdots&0\\
0&0&0&\cdots&n\\
\vdots&\vdots&\vdots&\ddots&\vdots\\
0&0&n&\cdots&0\\
0&n&0&\cdots&0\\
\end{bmatrix}
$$

我们惊讶地发现把一个东西乘上 $V^2$ 实际上就等价于：

> **每一项都乘上 $n$，然后翻转后 $n-1$ 项**。

也就是说，如果再乘上 $V^4$，后 $n-1$ 项转了回来，那就相当于每一项乘上 $n^2$。

那么我们先算出来 $\left\lfloor\dfrac{k}{4}\right\rfloor$ 先乘一下，再做 $k\bmod 4$ 次 NTT 就行了。

时间复杂度为 $O(n\log n+n\log k)$。

```cpp
#include<complex>
#include<iostream>
#include<cmath>
#include<cstdlib>
#include<cstdio>
#include<algorithm>

#define int long long
#define MAXN 2100000

using namespace std;

int x[MAXN],y[MAXN],z[MAXN];
int N,M;

int read(){
	int x=0;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar());
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x;
}

int rev[MAXN],k,L;

const int mod=998244353;
const int g=3;
const int g1=332748118;

void init(){
    rev[0]=0;
    for(int i=0;i<k;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(L-1));
}

int ksm(int x,int y){
    x%=mod;int ans=1;
    for(int i=y;i;i>>=1,x=x*x%mod)if(i&1)ans=ans*x%mod;
    return ans%mod;
}

void ntt(int *a,int sz,int tag){
    for(int i=1;i<sz;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
    int n=log2(sz);
    for(int i=1;i<=n;i++){
        int m=1<<i,wn;
        if(tag==1)wn=ksm(g,(mod-1)/(m));
        else wn=ksm(g1,(mod-1)/(m));
        for(int j=0;j<sz;j+=m){
            int omega=1;
            for(int l=0;l<m/2;l++){
                int x=omega*a[j+l+m/2]%mod,y=a[j+l]%mod;
                a[j+l]=(y+x)%mod;a[j+l+m/2]=(y-x+mod)%mod;
                omega=omega*wn%mod;
            }
        }
    }
}

int K,qwq;

signed main(){

    qwq=read(),K=read();
    N=(1<<qwq)-1;
    for(int i=0;i<=N;i++)x[i]=(read()+mod)%mod;

    for(k=1,L=0;k<=N;k<<=1,L++);

    int qwq=(int)(K/4)*2;K%=4;
    for(int i=0;i<=N;i++)x[i]=x[i]*(ksm((N+1),qwq)%mod)%mod;

    init();
    for(int i=1;i<=K;i++)ntt(x,k,1);

    for(int i=0;i<=N;i++)cout<<x[i]%mod<<" ";
    puts("");

    return 0;
}
```

---

## 作者：一只书虫仔 (赞：4)

from DreamWasTaken。

$$\text{DFT}(b)_i=\sum_{j=0}^{2^n-1}b_j\omega^{ij}\mod{998244353}$$

$\text{DFT}$ 本身没可见性质，考虑迭代：

$$\text{DFT}^2(b)_i=\sum_{j=0}^{2^n-1}\left(\sum_{k=0}^{2^n-1}b_k\omega^{jk}\right)\omega^{ij}=\sum_{k=0}^{2^n-1}b_k\sum_{j=0}^{2^n-1}\omega^{j(k+i)}$$

由单位根反演，有：

$$\text{DFT}^2(b)_i=\sum_{k=0}^{2^n-1}b_k2^n[k+i\in\{0,2^n\}]$$
$$\text{DFT}^2(b)_i=2^nb_{2^n-i\mod2^n}$$

再迭代一次得到：

$$\text{DFT}^4(b)_i=4^nb_i$$

对每一项乘 $4^{\lfloor \frac k 4\rfloor}$，再进行 $k\bmod 4$ 次 DFT 即可。

---

## 作者：FjswYuzu (赞：2)

下面记 $n=2^N$。

考虑 NTT 的实际过程。将多项式 $f$ 看作矩阵 $[f_0,f_1,\cdots ,f_{n-1}]$，NTT 的过程实际上就是乘上矩阵 $\frac{1}{n}M_1M_2$，其中 $M_1$ 为：

$$
\begin{bmatrix}
\omega^{0\times 0}_n & \omega^{0\times 1}_n & \dots & \omega^{0\times (n-1)}_n \\
\omega^{1\times 0}_n & \omega^{1\times 1}_n & \dots & \omega^{1\times (n-1)}_n \\
\vdots & \vdots & \ddots & \vdots \\
\omega^{(n-1)\times 0}_n & \omega^{(n-1)\times 1}_n & \dots & \omega^{(n-1)\times (n-1)}_n \\
\end{bmatrix}
$$

$M_2$ 就是 $M_1$ 每个元素幂次取相反数。显然 $M_2 = M_1^{-1}$。这个矩阵在运算意义来说是求出多项式 $f$ 的 $n$ 个点值，在线性代数意义下是在 $M_1$ 意义下观察一个向量。

这个题我们只需要求 $f \times M_1^k$ 就好了。

先观察一下。因为最终乘回来后还有系数 $\dfrac{1}{n}$，猜测经过一次线性变换后 $f$ 的模长是之前的 $\sqrt n$ 倍（并且你可以发现在 NTT 模数下 $n$ 一定存在二次剩余，奇妙啊）。

但是我们直接对每项乘上 ${\sqrt n}^k$ 显然是错的，因为我们乘到的位置每次是有区别的。我们要深挖一些性质。

先贴上一份[代码](https://www.luogu.com.cn/paste/ddo6yarn)，这份代码可以输出 $\frac{M1}{\sqrt 8}^i$，此时 $n=8$。

容易发现规律：在 $n \bmod 4=2$ 的时候和 $n \bmod 4=0$ 的时候，由特点突出的矩阵构成，分别指反转 $1 \sim n-1$ 项和不变。

我们考虑和 NTT 过程有机结合。在没有迭代的 NTT 版本中，IDFT 是直接反转 $1 \sim n-1$ 位，那么是不是有迹可循了呢？

那么这个问题的解决就非常方便了。我们做四次 NTT 相当于对每项乘上 $n^2$。那么我们最多做三遍 NTT。直接做就好了。

当然你直接打表看出 $n^2$ 的规律也是好的。

```cpp
int main(){
	N=read(),k=read();
	f.resize(n=(1<<N));
	for(LL i=0;i<n;++i)	rev[i]=(rev[i>>1]>>1)|((i&1)*(n>>1));
	LL coe=QuickPow(Mul(n,n),k/4);
	for(LL i=0;i<n;++i)	f[i]=Mul(read(),coe);
	k&=3;
	while(k-->0)	NTT(f);
	for(LL i=0;i<n;++i)	write(f[i]),putchar(i+1==n?'\n':' ');
	return 0;
}
```

---

## 作者：Melo_qwq (赞：1)

我们记 $2^n=m$。

发现 $k$ 很大，考虑使用矩阵刻画每次 $\rm DFT$ 操作。

初始矩阵用行向量表示成：
$$
\vec{a}=
\begin{bmatrix}
a_0&a_1&a_2&\cdots &a_{m-2}&a_{m-1}
\end{bmatrix}
$$

发现每次 $\rm DFT$ 操作等价于乘上转移矩阵：

$$
\vec{b}=
\begin{bmatrix}
1&1&1&\cdots&1&1\\
1&\omega&\omega^2&\cdots&\omega^{m-2}&\omega^{m-1}\\
1&(\omega^{1})^2&(\omega^{2})^2&\cdots&(\omega^{m-2})^2&(\omega^{m-1})^2\\
\vdots&\vdots&\vdots&\ddots&\vdots&\vdots\\
1&(\omega^1)^{m-1}&(\omega^2)^{m-1}&\cdots&(\omega^{m-2})^{m-1}&(\omega^{m-1})^{m-1}
\end{bmatrix}
$$
原操作等价于 $\vec{a}\leftarrow \vec{a}\times(\vec{b})^k$。

后面这个 $(\vec{b})^k$ 是不是可以简化？我们看一看 $k=2$ 的时候。

令 $\vec{B}=\vec{b}\times\vec{b}$，那么有：

$$
B_{i,j}=\displaystyle\sum_{k=0}^{m-1}b_{i,k}\times b_{k,j}=\displaystyle\sum_{k=0}^{m-1}\omega^{(i+j)k}
$$

当 $m\mid i+j$ 时，显然有 $\omega^{(i+j)k}=3^{998244352r}\equiv1\pmod {998244353},r\in\mathbb{N}$，此时 $B_{i,j}=m$。

否则利用等比数列求和可知 $B_{i,j}=0$。

那么可以写出矩阵 $\vec{B}$：

$$
\begin{bmatrix}
m&0&0&\cdots&0&0\\
0&0&0&\cdots&0&m\\
0&0&0&\cdots&m&0\\
\vdots&\vdots&\vdots&\ddots&\vdots&\vdots\\
0&0&m&\cdots&0&0\\
0&m&0&\cdots&0&0
\end{bmatrix}
$$
我们发现原序列乘 $\vec{B}$ 的结果，就是原序列每一项乘 $m$，再把后 $m-1$ 项翻转一下。

那如果乘 $(\vec{B})^2$，结果不就是原序列每一项直接乘 $m^2$ 吗？

这样就很好做了，只需要先把原序列中的每个数乘上 $\lfloor\frac{k}{4}\rfloor$ 个 $m^2$，再做 $k\bmod4$ 次 NTT 就做完了。

复杂度 $\Theta(n2^n)$，可以通过本题。

Code

```cpp
#include <bits/stdc++.h>
#define int long long 
#define f(i ,m ,n ,x) for (int i = (m) ; i <= (n) ; i += (x))

template < typename T > inline void read ( T &x ) {
	x = 0 ;
	bool flag (0) ; char ch = getchar () ;
	while (! isdigit (ch)) {
		flag = ch == '-' ;
		ch = getchar () ;
	} while (isdigit (ch)) {
		x = (x << 1) + (x << 3) + (ch ^ 48) ;
		ch = getchar () ; 
	} flag ? x = - x : 0 ;
} template < typename T ,typename ...Args >
inline void read ( T &x ,Args &...tmp ) {
	read (x) ,read (tmp...) ;
}

const int N = 131100 ,mod = 998244353ll ,g = 3ll ;
int n ,k ,infer[N] ,lim ,a[N] ;

inline int qpow (int bs ,int p) {
	int ans = 1ll ;
	while (p) {
		if (p & 1ll) (ans *= bs) %= mod ;
		(bs *= bs) %= mod ;
		p >>= 1ll ;
	} return ans ;
}

inline void NTT (int a[]) {
	f (i ,1 ,lim - 1 ,1) 
		if (infer[i] > i) std :: swap (a[infer[i]] ,a[i]) ;
	for (int len = 2 ,mid = 1 ; len <= lim ; mid = len ,len <<= 1) {
    	int gn = qpow (g ,(mod - 1) / len) ;
		f (st ,0 ,lim - 1 ,len) {
			int g0 = 1ll ;
			f (i ,0 ,mid - 1 ,1) {
				int x = a[st + i] ,y = g0 * a[st + i + mid] % mod ;
				a[st + i] = (x + y) % mod ;
				a[st + i + mid] = (x - y + mod) % mod ;
				(g0 *= gn) %= mod ;
			}
		}
	}
}

signed main () {
	read (n ,k) ;
	lim = (1 << n) ;
	f (i ,0 ,lim - 1 ,1) read (a[i]) ,a[i] %= mod ;
	int mi = qpow (lim ,2 * (k / 4)) ;
	f (i ,0 ,lim - 1 ,1) (a[i] *= mi) %= mod ;
	f (i ,1 ,lim - 1 ,1) infer[i] = (infer[i >> 1] >> 1) | ((i & 1) << (n - 1)) ;
	f (i ,1 ,k % 4 ,1) NTT (a) ;
	f (i ,0 ,lim - 1 ,1) std :: cout << a[i] << " \n"[i == lim - 1] ;
	return 0 ;
}
```

---

## 作者：Galois_Field_1048576 (赞：1)

令 $N=$ 原来题面中的 $n$，题解中的 $n=2^N$。

回忆 IDFT 的公式推导，结论是 IDFT 是 DFT 的柿子中序列翻转再乘 $\dfrac 1n$，等价地来说，DFT 就是把 IDFT 的柿子中序列翻转再乘 $n$。  
于是，我们可以把奇数项的 DFT 考虑成 DFT，把偶数项的 DFT 考虑成变换过的  IDFT。考虑 $k=4$ 的情况，第一次 DFT $\to$ IDFT：DFT 与 IDFT 抵消，留下序列翻转乘 $n$；第二次 DFT $\to$ IDFT：DFT 与 IDFT 抵消，翻转与前面的翻转抵消，留下乘 $n^2$。  
这样的话我们发现执行 $4$ 次 DFT 会使得序列整个乘 $n^2$，于是考虑如下的算法：  
1. 把 $b$ 的每一项乘 $n^{2\left\lfloor k/4\right\rfloor}$。
1. 如果 $k \bmod 4 \in \{2,3\}$，则将序列翻转，然后把每一项乘 $n$。
1. 如果 $k \bmod 2 = 1$，则对序列进行一次 NTT。


---

## 作者：qwq自动机 (赞：1)

Solution for [P7844 dWoi R2 - FFT](https://www.luogu.com.cn/problem/P7844)。

---

为方便讨论，下面令 $m=2^n$，$p=998244353$。

## Subtask 1

$m\leq 2^{11}, k\leq 10$。

暴力模拟复杂度 $>O(m^2k)$ 级别直接 T 飞。

某些玄学的似乎能过？

~~其实我也不知道怎么只拿这一个 subtask。~~

## Subtask 2

注意到这里的 $k$ 非常小。如果你会 NTT 的话就可以直接暴力 $k$ 次 NTT，复杂度 $O(km\log m)=O(kn2^n)$ 可以直接水过。

## Subtask 3 ~ 5

这里开始就要思考正解了。

如果将原序列表示成一个向量
$$
\vec a=\left(\begin{matrix}a_0\\a_1\\\vdots\\a_{m-1}\end{matrix}\right)
$$
可以知道做一次这个 DFT 相当于给 $\vec a$ 左乘一个矩阵
$$
M=\left[\begin{matrix}1&1&1&\cdots&1\\1&\omega&\omega^2&\cdots&\omega^n\\1&\omega^2&\omega^4&\cdots&\omega^{2n}\\\vdots&\vdots&\vdots&\ddots&\vdots\\1&\omega^{m-1}&\omega^{2(m-1)}&\cdots&\omega^{(m-1)^2}\end{matrix}\right]
$$
所以所求的序列（如果也表示成向量 $\vec A$ 的话）就是 $M^k\cdot\vec a$。

那么看到这里有一个 $M^k$，可以试试矩阵快速幂：复杂度 $O(m^3\log k)=O(2^{3n}\log k)$，可以通过 Subtask 3。

矩阵快速幂 $\log k$ 还是不够快，怎么办？尝试一下能不能搞成 $O(1)$ 之类的。

注意到这个 $k$ 非常令人难受，我们给它代一个特值 $2$，然后手算一下 $M^2$（设其第 $i$ 行 $j$ 列为 $(M^2)_{i,j}$，$i,j$ 从 $0$ 开始）：
$$
\begin{aligned}
(M^2)_{i,j}&=\sum_{k=0}^{m-1}M_{i,k}M_{k,j}&&\text{矩阵乘法定义}\\
&=\sum_{k=0}^{m-1}\omega^{ik}\omega^{kj}&&\text{观察上面 }M\text{ 的定义可知 }M_{i,j}=\omega^{ij}\\
&=\sum_{k=0}^{m-1}\omega^{k(i+j)}&&\text{显然}
\end{aligned}
$$
此时需要分类讨论。

$$\text{——分类讨论开始——}$$

1. 当 $m\mid (i+j)$ 时，由 $\omega=3^{\frac {p-1}m}$ 知

$$
\begin{aligned}
\omega^{k(i+j)}&=\omega^{kdm}&&(d\in\mathbb Z)\\
&=3^{(p-1)r}&&(r=kd\in\mathbb Z)\\
&=(3^{p-1})^r\\
&\equiv1^r\equiv1\pmod p
\end{aligned}
$$

（最后一步就是费小求逆元）

所以此时
$$
\begin{aligned}
(M^2)_{i,j}&=\sum_{k=0}^{m-1}1=m
\end{aligned}
$$

2. 当 $m\nmid (i+j)$ 时，可知

$$
\begin{aligned}
(M^2)_{i,j}&=\sum_{k=0}^{m-1}\omega^{k(i+j)}\\
&=\omega^{i+j}\sum_{k=0}^{m-1}\omega^k&&\text{提出来}\\
&=\omega^{i+j}\dfrac {\omega^m-1}{\omega-1}&&\text{等比数列求和}\\
\end{aligned}
$$

注意到
$$
\begin{aligned}
\omega^m-1&=(3^{\frac {p-1}m})^m-1\\
&=3^{p-1}-1\\
&\equiv 1-1\equiv0\pmod p
\end{aligned}
$$
所以此时
$$
\begin{aligned}
(M^2)_{i,j}&=0
\end{aligned}
$$
$$\text{——分类讨论结束——}$$

经过上面的讨论我们可以得出 $M^2$ 大概是这样的：
$$
\left[\begin{matrix}m&0&0&\cdots&0&0\\0&0&0&\cdots&0&m\\0&0&0&\cdots&m&0\\\vdots&\vdots&\vdots&\ddots&\vdots&\vdots\\0&0&m&\cdots&0&0\\0&m&0&\cdots&0&0\end{matrix}\right]
$$
然后我们把 $\vec a$ 乘过去就可以惊奇的发现：
$$
M^2\cdot \vec a=m\left(\begin{matrix}a_0\\a_{m-1}\\a_{m-2}\\\vdots\\a_1\end{matrix}\right)
$$
就是说给 $\vec a$ 左乘一个 $M^2$ 就等价于将 $\vec a$ 除第一个数外所有数翻转，然后再乘上一个 $m$。

好的，那么乘上 $M^2$（就是做两次 DFT）是这样，那么做四次就可以直接给原来序列的乘个 $m^2$！

所以我们就可以先给整个序列的数都乘上 $m^{2\lfloor\frac k4\rfloor}$，然后对乘了之后的序列进行剩下的 $k\bmod 4$ 次 DFT。

显然前面的可以用快速幂在 $O(m\log k)$ 解决。那么只需要考虑后面的。

如果后面的 $k\bmod 4$ 次 DFT 用暴力 $O(m^2)$ 的话，可以过掉 Subtask 4（总复杂度 $O(m^2+m\log k)$）。

但是我们可以直接做 NTT 然后就可以把那个 $O(m^2)$ 变成 $O(m\log m)$ 然后成功的过掉 Subtask 5。

## Code
有了思路代码就好写了。

注意特判 $k<4$ 的情况。

```cpp
#include <iostream>
const int MOD = 998244353, G = 3, MAXN = 1 << 17;
using ll = long long;
ll qpow(ll a, ll b = MOD - 2) // 快速幂
{
    ll ans = 1;
    while (b)
    {
        if (b & 1)
            (ans *= a) %= MOD;
        (a *= a) %= MOD;
        b >>= 1;
    }
    return ans;
}
int InvG = qpow(G), tr[MAXN << 2];
ll f[MAXN << 2];
void NTT(ll *f, int n) // 板子
{
    for (int i = 0; i < n; i++)
        if (i < tr[i])
            std::swap(f[i], f[tr[i]]);
    for (int l = 2; l <= n; l <<= 1)
    {
        ll root = qpow(G, (MOD - 1) / l);
        for (int k = 0; k < n; k += l)
        {
            ll cur = 1;
            for (int i = k; i < (l >> 1) + k; i++)
            {
                ll qwq = cur * f[i + (l >> 1)] % MOD;
                f[i + (l >> 1)] = f[i] - qwq;
                if (f[i + (l >> 1)] < 0)
                    f[i + (l >> 1)] += MOD;
                f[i] += qwq;
                if (f[i] >= MOD)
                    f[i] -= MOD;
                (cur *= root) %= MOD;
            }
        }
    }
}
int main()
{
    int n;
    long long k;
    std::cin >> n >> k;
    int len = 1 << n;
    for (int i = 0; i < len; i++)
        std::cin >> f[i];
    tr[0] = 0;
    for (int i = 1; i < len; i++)
        tr[i] = (tr[i >> 1] >> 1) | (i & 1 ? len >> 1 : 0);
    long long mul = qpow(len, (k / 4) * 2);
    if (mul) // 特判 k < 4
        for (int i = 0; i < len; i++)
            (f[i] *= mul) %= MOD;
    int NTTtimes = k % 4;
    for (int i = 1; i <= NTTtimes; i++) // 做 k % 4 次 NTT
        NTT(f, len);
    for (int i = 0; i < len; i++)
        std::cout << f[i] << ' ';
    return 0;
}
```

$$\text{—— The End ——}$$



---

## 作者：jijidawang (赞：0)

SoyTony 科技 orz。

考虑 DFT 相当于代入 $\omega^i$，IDFT 相当于代入 $\omega^{-i}$ 后除以项数。

显然 $\omega^{2^n}=1$，于是可以发现代入 $\omega^{-i}$ 对应序列翻转，考虑给恰一半的 DFT 翻转改成 IDFT，除以项数的部分可以直接提出来。

发现这样操作会产生 $\dfrac k2$ 次翻转，两次翻转才能抵消，于是不管除以项数的部分则答案有长为 $4$ 的循环节，前面直接做，后面散的部分暴力 NTT 即可。

时间复杂度 $\Theta(n2^n)$。

---

