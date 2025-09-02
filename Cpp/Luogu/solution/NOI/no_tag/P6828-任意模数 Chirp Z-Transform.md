# 任意模数 Chirp Z-Transform

## 题目背景

大家应该知道原时空限是 1.23s 345MB。

## 题目描述

给定一个 $n$ 项多项式 $P(x)$ 以及 $c, m$，请计算 $P(c^0),P(c^1),\dots,P(c^{m-1})$。所有答案都对 $10^9+7$ 取模。

## 说明/提示

对于 $100\%$ 的数据，$1\le n,m\le 6\cdot10^5,0\le c,a_i<10^9+7$.  
| 测试点编号 | $n,m$ 限制 |
| :-----------: | :-----------: |
| $1$ | $n=m=1000$ |
| $2$ | $n=m=64000$ |
| $3$ | $n=m=5\cdot10^5$ |
| $4$ | $n=5\cdot10^5,m=6\cdot10^5$ |
| $5$ | $n=6\cdot10^5,m=5\cdot10^5$ |

出题人很遗憾由于精度和洛谷自带资料限制无法开到 $10^6$。  
提示：$7$ 次 $FFT$ 可能过不了。  
提示：出题人没有用 `long double`。

## 样例 #1

### 输入

```
6 108616 6
1 0 8 6 1 6```

### 输出

```
22 772456230 866731294 299746576 978045696 394365866```

# 题解

## 作者：cyffff (赞：19)

[$\text{Link}$](https://www.luogu.com.cn/problem/P6828)

板子题，极限卡常~~差评~~。

居然没有题解，就来写一篇吧。

upd2021.7.15：修式子和 $\LaTeX$。
## 题意
给 $n,m,c$ 和 $n-1$ 次多项式 $F(x)$，求出 $\forall k\in[0,m) F(c^k)$。

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
可以卷积。

见模数为 $998244353$ 的[版本](https://www.luogu.com.cn/problem/P6800)。

模数不对就用 $\text{MTT}$，时间复杂度 $O(n\log n)$。
****
然而这道题还没结束，我们发现了时限 1.23s 空限 345MB，没错，这道题卡时间+卡空间。

下面给出本题卡常的几个技巧：

- $\text{MTT}$ 必须用 $4$ 次 $\text{FFT}$,不知道三模 $\text{NTT}$ 能不能过，好像在[板子题](https://www.luogu.com.cn/problem/P4245)道三模 $\text{NTT}$ 时间和空间都比 $\text{MTT}$ 优秀。
- 手动二分数组大小，$N=2.1\times 10^6$ 左右就行了。
- 预处理单位根幂。
- 开 `double` 而不是 `long double`。
- 有良好的编码习惯，只在乘法时开 `long long`，数组开 `int`，加减法尽量少使用 `%` 运算。
- `fread`，`fwrite` 快读快写。
- 在夜深人静的时候交/多交亿次等评测机波动。

为了方便各位神仙调试，这里给出大部分代码：
```cpp
#define ll long long
#define ld double
const ld pi=acos(-1);
const int mod=1e9+7,N=2.1e6;
inline void print(int *a){
	for(int i=0;a[i]||a[i+1]||a[i+2]||a[i+3]||a[i+4]||a[i+5];i++){
		printf("%d ",a[i]);
	}
	puts("");
}
struct comp{
	double x,y;
	comp(ld a=0,ld b=0){x=a,y=b;}
	comp neg(){
		return comp(x,-y);
	}
	friend comp operator+(const comp &a,const comp &b){
		return comp(a.x+b.x,a.y+b.y);
	}
	friend comp operator-(const comp &a,const comp &b){
		return comp(a.x-b.x,a.y-b.y);
	}
	friend comp operator*(const comp &a,const comp &b){
		return comp(a.x*b.x-a.y*b.y,a.y*b.x+a.x*b.y);
	}
};
struct ntt{
	comp A[N],B[N],C[N],D[N],qp[N];
	int n,rev[N],f[N],g[N],lim,c[N],ic[N];
	int m,_c;
	inline void init(int n,int mode=1){
		if(mode){
			int l=0;
			for(lim=1;lim<=n;lim<<=1)l++;
			for(int i=1;i<lim;i++){
				rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
			}
			for(int i=1;i<lim;i<<=1){
				for(int j=0;j<i;j++){
					qp[lim/i*j]=comp(cos(j*pi/i),sin(j*pi/i));
				}
			}
		}else{
			for(lim=1;lim<=n;lim<<=1);
		}
	}
	inline int qpow(int x,int y){
		int res=1;
		while(y){
			if(y&1) res=1ll*res*x%mod;
			x=1ll*x*x%mod;
			y>>=1;
		}
		return res;
	}
	inline void FFT(comp *a,int tpe){
		for(int i=0;i<lim;i++){
			if(i<rev[i]){
				swap(a[i],a[rev[i]]);
			}
		}
		for(int i=1;i<lim;i<<=1){
			for(int j=0;j<lim;j+=(i<<1)){
				for(int k=0;k<i;k++){
					comp t=a[i+j+k]*(tpe==1?qp[lim/i*k]:qp[lim/i*k].neg());
					a[i+j+k]=a[j+k]-t;
					a[j+k]=a[j+k]+t;
				}
			}
		}
	}
	inline void MTT(int *f,int *g,int *ans){
		for(int i=0;i<lim;i++){
			A[i].x=f[i]>>15,A[i].y=f[i]&32767;
			C[i].x=g[i]>>15,C[i].y=g[i]&32767;
		}
		FFT(A,1);
		FFT(C,1);
		for(int i=1;i<lim;i++){
			B[i]=A[lim-i].neg();
		}
		B[0]=A[0].neg();
		for(int i=1;i<lim;i++){
			D[i]=C[lim-i].neg();
		}
		D[0]=C[0].neg();
		for(int i=0;i<lim;i++){
			comp aa=(A[i]+B[i])*comp(0.5,0);
			comp bb=(A[i]-B[i])*comp(0,-0.5);
			comp cc=(C[i]+D[i])*comp(0.5,0);
			comp dd=(C[i]-D[i])*comp(0,-0.5);
			A[i]=aa*cc+comp(0,1)*(aa*dd+bb*cc);
			B[i]=bb*dd;
		}
		FFT(A,-1);
		FFT(B,-1);
		for(int i=0;i<lim;i++){
			int aa=(ll)(A[i].x/lim+0.5)%mod;
			int bb=(ll)(A[i].y/lim+0.5)%mod;
			int cc=(ll)(B[i].x/lim+0.5)%mod;
			ans[i]=((1ll*aa*(1<<30)+1ll*bb*(1<<15)+cc)%mod+mod)%mod;
		}
	}
	inline void MAIN(){
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
		MTT(f,g,f);
		for(int i=0;i<m;i++){
			write((long long)f[i+n]*(i?ic[i-1]:1)%mod);
			out[len++]=' ';
		}
	}
}w;
```
最慢点 1.23s（没错卡常卡到这种程度），最大空间 196.23MB。

希望各位~~卡常愉快~~，早日卡过~。

若有问题请私信/评论。
****
再见 qwq~

---

## 作者：Ruiqun2009 (赞：3)

本文分两部分：Chirp-Z Transform 和 MTT。
## Chirp-Z Transform
### 简介
Chirp-Z 变换（Chirp-Z Transform），又称 Bluestein 算法，是任意长度的卷积。

这个算法可以在 $O(n\log n)$ 的时间复杂度内求解等比数列点值。

更形象化地：

给定三个整数 $n,m,c$，以及一个多项式 $A(x)$。

这个算法可以在 $\Theta((n+m)\log (n+m))$ 的时间复杂度内求出
$$
A(1),A(c),A(c^2),\cdots,A(c^{m-1})
$$
当然，是在模意义下的。
### 实现
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
### 代码
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
## MTT
### 预处理单位根
还是一个比较简单的提高精度的科技。

通过预处理单位根算出 $\omega_{len}^i$，而不是每次都乘，这样会掉精度。

同时能减小常数，避免重复的运算。
```cpp
inline void get_rev(size_t len, int x) {
    if (len == rev.size()) return;
    rev.resize(len);
    for (size_t i = 0; i < len; i++) rev[i] = rev[i >> 1ull] >> 1ull | (i & 1ull) << x;
    omegas.resize(len);
    for (size_t i = 0; i < len; i++) omegas[i] = cp(std::cos(two * pi / len * i), std::sin(two * pi / len * i));
}
inline void FFT(vector<cp>& a, size_t n, bool type) {
    for (size_t i = 1ull; i < n; ++i) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
    for (size_t i = 2ull; i <= n; i <<= 1ull) for (size_t j = 0ull, l = (i >> 1ull), ch = n / i; j < n; j += i) for (size_t k = j, now = 0ull; k < j + l; k++) {
        cp x = a[k], y = a[k + l] * (type ? omegas[now] : omegas[now].conj());
        a[k] = x + y;
        a[k + l] = x - y;
        now += ch;
    }
    if (!type) {
        for (size_t i = 0; i < n; i++) {
            a[i].real() /= n;
            a[i].imag() /= n;
        }
    }
}
```
### 第一轮合并
我们发现，在 $7$ 次 FFT 的拆系数 FFT 中，复数中我们只用了实部，并没有使用虚部。我们尝试使用。

我们设
$$
\begin{aligned}
P_0(x)&=A_0(x)+\mathrm{i}A_1(x)\\
P_1(x)&=A_0(x)-\mathrm{i}A_1(x)\\
Q(x)&=B_0(x)+\mathrm{i}B_1(x)
\end{aligned}
$$
然后我们将他们乘起来，得到
$$
\begin{aligned}
P_0(x)Q(x)&=(A_0(x)+\mathrm{i}A_1(x))(B_0(x)+\mathrm{i}B_1(x))\\
&=A_0(x)B_0(x)-A_1(x)B_1(x)+\mathrm{i}(A_0(x)B_1(x)+A_1(x)B_0(x))\\
P_1(x)Q(x)&=(A_0(x)-\mathrm{i}A_1(x))(B_0(x)+\mathrm{i}B_1(x))\\
&=A_0(x)B_0(x)+A_1(x)B_1(x)+\mathrm{i}(A_0(x)B_1(x)-A_1(x)B_0(x))\\
\end{aligned}
$$
于是
$$
\begin{aligned}
P_0(x)Q(x)+P_1(x)Q(x)&=2(A_0(x)B_0(x)+\mathrm{i}A_0(x)B_1(x))\\
P_1(x)Q(x)-P_0(x)Q(x)&=2(A_1(x)B_1(x)-\mathrm{i}A_1(x)B_0(x))
\end{aligned}
$$
我们可以在上述式子中找出所有我们所需要的项。

总计 $5$ 次 FFT。

代码：
```cpp
inline void mul(size_t n, size_t m, const vector<mint>& a, const vector<mint>& b, vector<mint>& c, size_t len) {
    const size_t up = sqrt(mint::mod());
    mint v1, v2, v3;
    static size_t i;
    vector<cp> P(len, cp(0, 0)), Q(len, cp(0, 0)), R(len, cp(0, 0));
    for (i = 0ull; i < n; i++) {
        P[i] = cp(a[i].val() % up, a[i].val() / up);
        Q[i] = P[i].conj();
    }
    for (i = 0ull; i < m; i++) R[i] = cp(b[i].val() % up, b[i].val() / up);
    FFT(P, len, true);
    FFT(Q, len, true);
    FFT(R, len, true);
    for (i = 0ull; i < len; i++) {
        P[i] = P[i] * R[i];
        Q[i] = Q[i] * R[i];
    }
    FFT(P, len, false);
    FFT(Q, len, false);
    c.resize(n + m - 1);
    for (i = 0ull; i < n + m - 1; i++) {
        v1 = llround((P[i].real() + Q[i].real()) / two);
        v2 = llround((Q[i].real() - P[i].real()) / two);
        v3 = llround(P[i].imag());
        c[i] = v1 + v2 * up * up + v3 * up;
    }
}
```
实测[不能通过](https://www.luogu.com.cn/record/93881015)。
### 第二轮合并
本质上就是对 $P_0(x)$ 和 $P_1(x)$ 的合并。
#### 第一种合并方式
这是 OIer 最常写的拆系数 FFT 版本。

通过上边提到的特性计算出了 $\mathcal{F}(F_0(x))\lbrack i\rbrack$ 和 $\mathcal{F}(F_1(x))\lbrack i\rbrack$。但是这种方法不同就在于，它直接求出了 $A_0(x),A_1(x)$。然后将 $A_0(x)B_0(x)+\mathrm{i}A_0(x)B_1(x)$ 和 $A_1(x)B_0(x)+\mathrm{i}A_1(x)B_1(x)$ 算出。

然后按照定义合并。
#### 第二种合并方式
设 FFT 长度为 $n$。根据 FFT 的定义 $\mathcal{F}(F(x))\lbrack i\rbrack=F(\omega_{n}^i)=\sum_{j=0}^{n-1}\omega_{n}^{ij}F\lbrack j\rbrack$，我们能得到
$$
\begin{aligned}
\mathcal{F}(P_0(x))\lbrack i\rbrack&=P_0(\omega_{n}^i)\\
&=A_0(\omega_{n}^i)+\mathrm{i}A_1(\omega_{n}^i)\\
&=\sum_{j=0}^{n-1}\omega_{n}^{ij}A_0\lbrack j\rbrack
+\mathrm{i}
\sum_{j=0}^{n-1}\omega_{n}^{ij}A_1\lbrack j\rbrack\\
&=\sum_{j=0}^{n-1}\omega_{n}^{ij}(A_0\lbrack j\rbrack
+\mathrm{i}
A_1\lbrack j\rbrack)\\
\mathcal{F}(P_1(x))\lbrack n-i\rbrack&=P_1(\omega_{n}^{-i})\\
&=A_0(\omega_{n}^{-i})-\mathrm{i}A_1(\omega_{n}^{-i})\\
&=\sum_{j=0}^{n-1}\omega_{n}^{-ij}A_0\lbrack j\rbrack
-\mathrm{i}
\sum_{j=0}^{n-1}\omega_{n}^{-ij}A_1\lbrack j\rbrack\\
&=\sum_{j=0}^{n-1}\omega_{n}^{-ij}(A_0\lbrack j\rbrack-\mathrm{i}A_1\lbrack j\rbrack)\\
\end{aligned}
$$
考虑单位根的几何意义 $\omega_{n}^i=\cos\dfrac{2\pi i}{n}+\mathrm{i}\sin\dfrac{2\pi i}{n}$。

代入上式，得到
$$
\begin{aligned}
\mathcal{F}(P_0(x))\lbrack i\rbrack
&=\sum_{j=0}^{n-1}\omega_{n}^{ij}(A_0\lbrack j\rbrack
+\mathrm{i}
A_1\lbrack j\rbrack)\\
&=\sum_{j=0}^{n-1}(\cos\dfrac{2\pi ij}{n}+\mathrm{i}\sin\dfrac{2\pi ij}{n})(A_0\lbrack j\rbrack
+\mathrm{i}
A_1\lbrack j\rbrack)\\
&=\sum_{j=0}^{n-1}(\cos\dfrac{2\pi ij}{n}\times A_0\lbrack j\rbrack-\sin\dfrac{2\pi ij}{n}\times A_1\lbrack j\rbrack+\mathrm{i}(\sin\dfrac{2\pi ij}{n}\times A_0\lbrack j\rbrack+\cos\dfrac{2\pi ij}{n}\times A_1\lbrack j\rbrack))\\
\mathcal{F}(P_1(x))\lbrack n-i\rbrack&=\sum_{j=0}^{n-1}\omega_{n}^{-ij}(A_0\lbrack j\rbrack-\mathrm{i}A_1\lbrack j\rbrack)\\
&=\sum_{j=0}^{n-1}(\cos\dfrac{-2\pi ij}{n}+\mathrm{i}\sin\dfrac{-2\pi ij}{n})(A_0\lbrack j\rbrack-\mathrm{i}A_1\lbrack j\rbrack)\\
&=\sum_{j=0}^{n-1}(\cos\dfrac{2\pi ij}{n}-\mathrm{i}\sin\dfrac{2\pi ij}{n})(A_0\lbrack j\rbrack-\mathrm{i}A_1\lbrack j\rbrack)\\
&=\sum_{j=0}^{n-1}(\cos\dfrac{2\pi ij}{n}\times A_0\lbrack j\rbrack-\sin\dfrac{2\pi ij}{n}\times A_1\lbrack j\rbrack-\mathrm{i}(\sin\dfrac{2\pi ij}{n}\times A_0\lbrack j\rbrack+\cos\dfrac{2\pi ij}{n}\times A_1\lbrack j\rbrack)\\
\end{aligned}
$$

然后我们发现 $\mathcal{F}(P_0(x))\lbrack i\rbrack$ 和 $\mathcal{F}(P_1(x))\lbrack n-i\rbrack$ 是共轭的。（这个我在 [这篇文章](https://www.luogu.com.cn/blog/_post/458869) 里提到过）

于是我们对 $P_0$ 做 FFT 之后，可以根据定义得到 $P_1$ FFT 后的结果。

总计 $4$ 次 FFT。

代码：
##### 第一种 $4$ 次 FFT 的拆系数 FFT
```cpp
inline void mul(int n, int m, const int& p, vector<int> a, vector<int> b, vector<int>& c) {
    static cp da, db, dc, dd, rel(0.5, 0), img(0, -0.5);
    static const int up = 1 << 15;
    static int v1, v2, v3;
    int len = 1, x = -1;
    while (len < n + m) len <<= 1, x++;
    a.resize(len);
    b.resize(len);
    get_rev(len, x);
    for (int i = 0; i < len; i++) {
        a[i] = i < n ? (a[i] % p + p) % p : 0;
        b[i] = i < m ? (b[i] % p + p) % p : 0;
    }
    vector<cp> P(len, cp(0, 0)), Q(len, cp(0, 0)), R(len, cp(0, 0));
    for (int i = 0; i < len; i++) {
        P[i] = cp(a[i] >> 15, a[i] & 32767);
        Q[i] = cp(b[i] >> 15, b[i] & 32767);
    }
    FFT(P, len, 1);
    FFT(Q, len, 1);
    for (int i = 0; i < len; i++) {
        R[i] = P[(len - i) & (len - 1)].conj();
    }
    for (int i = 0; i < len; i++) {
        auto x = P[i];
        auto y = R[i];
        P[i] = (x + y) * rel;
        R[i] = (x - y) * img;
    }
    for (int i = 0; i < len; i++) {
        P[i] = P[i] * Q[i];
        Q[i] = R[i] * Q[i];
    }
    FFT(P, len, -1);
    FFT(Q, len, -1);
    c.clear();
    c.resize(len);
    for (int i = 0; i < len; i++) {
        v1 = (int)(P[i].real() + 0.5);
        v2 = (int)(P[i].imag() + 0.5) + (int)(Q[i].real() + 0.5);
        v3 = (int)(Q[i].imag() + 0.5);
        c[i] = 1ll * v1 * up % p * up % p + 1ll * v2 * up % p + v3 % p;
        c[i] = (c[i] % p + p) % p;
    }
}
```
##### 第二种 $4$ 次 FFT 的拆系数 FFT
```cpp
inline void mul(size_t n, size_t m, const vector<mint>& a, const vector<mint>& b, vector<mint>& c, size_t len) {
    const size_t up = sqrt(mint::mod());
    mint v1, v2, v3;
    vector<cp> P(len, cp(0, 0)), Q(len, cp(0, 0)), R(len, cp(0, 0));
    for (size_t i = 0ull; i < n; i++) P[i] = cp(a[i].val() % up, a[i].val() / up);
    for (size_t i = 0ull; i < m; i++) R[i] = cp(b[i].val() % up, b[i].val() / up);
    FFT(P, len, true);
    FFT(R, len, true);
    Q[0] = P[0].conj();
    for (size_t i = 1ull; i < len; i++) Q[i] = P[len - i].conj();
    for (size_t i = 0ull; i < len; i++) {
        P[i] = P[i] * R[i];
        Q[i] = Q[i] * R[i];
    }
    FFT(P, len, false);
    FFT(Q, len, false);
    c.resize(n + m - 1);
    for (size_t i = 0ull; i < n + m - 1; i++) {
        v1 = llround((P[i].real() + Q[i].real()) / two);
        v2 = llround((Q[i].real() - P[i].real()) / two);
        v3 = llround(P[i].imag());
        c[i] = v1 + v2 * up * up + v3 * up;
    }
}
```

---

## 作者：MaxBlazeResFire (赞：1)

### 本写法不用卡常，写对了一遍过。

居然没有人上经典的 $\rm DIT-DIF$ 优化（包括多项式乘法和任意模数多项式乘法的模板也没有）？

这种优化可以直接把你的 $\rm NTT$ 和 $\rm FFT$ 运行常数砍掉一大半。单优化就可以让你的 $9$ 次 $\rm NTT$ 和 $5$ 次 $\rm FFT$ 在 $2^{21}$ 长度的卷积下跑进 1.0s.

想学习的话请进 ~~某不认识的大佬的~~ [再探 FFT – DIT 与 DIF，另种推导和优化](https://charleswu.site/archives/3065)，里面有详尽的解释。

这种写法的好处在于，用 $\rm DIF$ 实现 $\rm DFT$，用 $\rm DIT$ 实现 $\rm IDFT$，**免去蝴蝶变换** 的同时，还可以 **让单位根移动次数降到 $O(n)$ 级别。**

唯一有点麻烦的就是 $\rm NTT$ 模数的选取，若卷积长度为 $2^n$，则你需要选取一个可以写为 $t\times 2^k+1$ 且满足 $k\geq n+2$ 的质数当模数。

本题中卷积长度为 $2^{21}$，故选择 $998244353=119\times2^{23}+1,469762049=7\times2^{26}+1,167772161=5\times2^{25}+1$ 当作三模 $\rm NTT$ 的模数。

$\displaystyle Ans_i=P(c^i)=\sum_{j=0}^{n-1}p_jc^{ij}=\sum_{j=0}^{n-1}p_jc^{\binom{i+j}{2}-\binom{i}{2}-\binom{j}{2}}$.

记 $\displaystyle C_i=c^{\binom{i}{2}},D_i=\frac{1}{C_i},E_i=D_ip_i$，则原式为 $\displaystyle D_i\sum_{j=0}^{n-1}C_{i+j}E_j$，那么这就是一个经典的减法卷积，我在这里选择翻转 $E$.

程序里有加法卷积与减法卷积对应的封装。注意 $C$ 的下标范围达到了 $n+m$.

复杂度 $O(n\log n)$.由于这个优化实在太强了所以直接把原板子搬过来不用卡常都能过。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 2100005

const int mod = 1000000007;

typedef vector<int> poly;

inline int read(){
	int x = 0; char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();
	while( ch >= '0' && ch <= '9' ) x = x * 10 + ch - 48,ch = getchar();
	return x;
}

int n,c,m;

inline int fp( int x , int p , int mod ){ int res = 1; while( p ){ if( p & 1 ) res = res * x % mod; x = x * x % mod; p >>= 1; } return res; }
inline int inv( int x , int mod ){ return fp( x , mod - 2 , mod ); }

const int mod1 = 998244353,mod2 = 469762049,mod3 = 167772161; //解锁新模数：5*2^25+1
const int inv1 = inv( mod1 , mod2 ),mul = mod1 * mod2,inv2 = inv( mul % mod3 , mod3 );

struct Int{
	int x,y,z;
	Int( int num = 0 ): x(num),y(num),z(num){}
	Int( int a , int b , int c ): x(a),y(b),z(c){}
	inline Int reduce( Int A ){ return Int( A.x + ( A.x >> 63 & mod1 ) , A.y + ( A.y >> 63 & mod2 ) , A.z + ( A.z >> 63 & mod3 ) ); }
	inline Int operator +( Int A ){ return reduce( Int( x + A.x - mod1 , y + A.y - mod2 , z + A.z - mod3 ) ); }
	inline Int operator -( Int A ){ return reduce( Int( x - A.x , y - A.y , z - A.z ) ); }
	inline Int operator *( Int A ){ return Int( x * A.x % mod1 , y * A.y % mod2 , z * A.z % mod3 ); }
	inline int val(){
		int tmp = ( y - x + mod2 ) % mod2 * inv1 % mod2 * mod1 + x;
		return ( ( z - tmp % mod3 + mod3 ) % mod3 * inv2 % mod3 * ( mul % mod ) % mod + tmp ) % mod;
	}
};

namespace polybase{
	Int gw[MAXN],tmp[MAXN];
	inline void polypre( int T = 21 ){
		gw[0] = Int( 1 );
		gw[1 << T] = Int( fp( fp( 3 , 119 , mod1 ) , 1 << ( 21 - T ) , mod1 ) , fp( fp( 3 , 7 , mod2 ) , 1 << ( 24 - T ) , mod2 ) , fp( fp( 3 , 5 , mod3 ) , 1 << ( 23 - T ) , mod3 ) );
		for( int i = T ; i ; i -- ) gw[1 << ( i - 1 )] = gw[1 << i] * gw[1 << i];
		for( int i = 1 ; i < ( 1 << T ) ; i ++ ) gw[i] = gw[i & ( i - 1 )] * gw[i & -i];
	}
	inline void DIT( Int *A , int len ){
		for( int i = 0 ; i < len ; i ++ ) tmp[i] = A[i];
		for( int i = 1 ; i < len ; i <<= 1 ){
			Int *k = tmp;
			for( Int *g = gw ; k < tmp + len ; k += i << 1 , g ++ ){
				for( Int *x = k ; x < k + i ; x ++ ){
					Int o = x[i];
					x[i] = ( *x - o ) * *g,*x = *x + o;
				}
			}
		}
		Int iv( inv( len , mod1 ) , inv( len , mod2 ) , inv( len , mod3 ) );
		for( int i = 0 ; i < len ; i ++ ) A[i] = tmp[i] * iv;
		reverse( A + 1 , A + len );
	}
	inline void DIF( Int *A , int len ){
		for( int i = 0 ; i < len ; i ++ ) tmp[i] = A[i];
		for( int i = len / 2 ; i ; i >>= 1 ){
			Int *k = tmp;
			for( Int *g = gw ; k < tmp + len ; k += i << 1 , g ++ ){
				for( Int *x = k ; x < k + i ; x ++ ){
					Int o = x[i] * *g;
					x[i] = *x - o,*x = *x + o;
				}
			}
		}
		for( int i = 0 ; i < len ; i ++ ) A[i] = tmp[i];
	}
	inline poly polymul( poly A , poly B ){
		int n = A.size(),m = B.size(),L = n + m - 1,len = 1;
		while( len < L ) len <<= 1;
		static Int tA[MAXN],tB[MAXN];
		for( int i = 0 ; i < n ; i ++ ) tA[i] = Int( A[i] );
		for( int i = n ; i < len ; i ++ ) tA[i] = Int( 0 );
		for( int i = 0 ; i < m ; i ++ ) tB[i] = Int( B[i] );
		for( int i = m ; i < len ; i ++ ) tB[i] = Int( 0 );
		DIF( tA , len ),DIF( tB , len );
		for( int i = 0 ; i < len ; i ++ ) tA[i] = tA[i] * tB[i];
		DIT( tA , len );
		poly Ans( L ); for( int i = 0 ; i < L ; i ++ ) Ans[i] = ( tA[i].val() + mod ) % mod;
		return Ans;
	}
	inline poly polyTmul( poly A , poly B ){
		int n = A.size(),m = B.size();
		reverse( B.begin() , B.end() );
		B = polymul( A , B );
		for( int i = 0 ; i < n ; i ++ ) A[i] = B[i + m - 1];
		return A;
	}
}

using namespace polybase;

int base[MAXN] = {0},pbase[MAXN] = {0};

inline int Rpow( int X ){ return pbase[X / ( 2 * n )] * base[X % ( 2 * n )] % mod; }

poly C,D,E,P;

signed main(){
	polypre();
	n = read(),c = read(),m = read();
	base[0] = 1;
	for( int i = 1 ; i <= MAXN - 5 ; i ++ ) base[i] = base[i - 1] * c % mod;
	pbase[0] = 1;
	for( int i = 1 ; i <= MAXN - 5 ; i ++ ) pbase[i] = pbase[i - 1] * base[2 * n] % mod;
	P.resize( n ),C.resize( n + m ),D.resize( n ),E.resize( n );
	for( int i = 0 ; i < n ; i ++ ) P[i] = read();
	for( int i = 0 ; i < n + m ; i ++ ) C[i] = Rpow( i * ( i - 1 ) / 2 );
	for( int i = 0 ; i < n ; i ++ ) D[i] = inv( Rpow( i * ( i - 1 ) / 2 ) , mod );
	for( int i = 0 ; i < n ; i ++ ) E[i] = P[i] * inv( Rpow( i * ( i - 1 ) / 2 ) , mod ) % mod;
	C = polyTmul( C , E );
	for( int i = 0 ; i < m ; i ++ ) C[i] = C[i] * inv( Rpow( i * ( i - 1 ) / 2 ) , mod ) % mod;
	for( int i = 0 ; i < m ; i ++ ) printf("%lld ",( C[i] + mod ) % mod); puts("");
	return 0;
}
```

---

## 作者：RuSun (赞：0)

注意到 $ki = \binom {i + k} 2 - \binom i 2 - \binom k 2$ ，那么有

$$
\begin {aligned}
P(c ^ k) & = \sum _ {i = 0} ^ {n - 1} [x ^ i]P (c ^ k) ^ i \\\\
& = \sum _ {i = 0} ^ {n - 1} [x ^ i]Pc ^ {ki} \\\\
& = \sum _ {i = 0} ^ {n - 1} [x ^ i]Pc ^ {\binom {i + k} 2 - \binom i 2 - \binom k 2} \\\\
& = c ^ { - \binom k 2}\sum _ {i = 0} ^ {n - 1} [x ^ i]Pc ^ {\binom {i + k} 2 - \binom i 2} \\\\
\end {aligned}
$$

可以写作关于 $i$ 和关于 $i + k$ 的多项式的卷积。

写了 3 模数 NTT ，交了 16 发后卡过。

提供几个卡常思路：

- 快读快写。

- CRT 的三个系数提前处理。

- 优化取模。

- 预处理 $c ^ {\binom i 2}$ 。

- 其他细节。

```
#include <cstdio>
#include <algorithm>
using namespace std;
template <class Type>
void read (Type &x)
{
    char c;
    bool flag = false;
    while ((c = getchar()) < '0' || c > '9')
        flag |= c == '-';
    x = c - '0';
    while ((c = getchar()) >= '0' && c <= '9')
        x = (x << 3) + (x << 1) + c - '0';
    if (flag) x = ~x + 1;
}
template <class Type, class ...Rest>
void read (Type &x, Rest &...y) { read(x); read(y...); }
template <class Type>
void write (Type x)
{
    if (x < 0) putchar('-'), x = ~x + 1;
    if (x > 9) write(x / 10);
    putchar('0' + x % 10);
}
typedef __int128 L;
typedef long long LL;
const int N = 5e6 + 10, p1 = 998244353, p2 = 1004535809, p3 = 469762049, p = 1e9 + 7;
const L inf = (L)N * p * p, mul = (L)p1 * p2 * p3;
int bit, tot, rev[N];
int binpow (int b, int k = p - 2)
{
    int res = 1;
    for (; k; k >>= 1, b = (LL)b * b % p)
        if (k & 1) res = (LL)res * b % p;
    return res;
}
template <const int &mod>
struct NTT
{
    void adj (int &x) { x += x >> 31 & mod; }
    int binpow (int b, int k = mod - 2)
    {
        int res = 1;
        for (; k; k >>= 1, b = (LL)b * b % mod)
            if (k & 1) res = (LL)res * b % mod;
        return res;
    }
    void ntt (int *x, int op)
    {
        for (int i = 0; i < tot; ++i)
            if (rev[i] > i) swap(x[rev[i]], x[i]);
        for (int mid = 1; mid < tot; mid <<= 1)
        {
            int w1 = binpow(3, (mod - 1) / (mid << 1));
            if (!~op) w1 = binpow(w1);
            for (int i = 0; i < tot; i += mid << 1)
                for (int j = 0, k = 1; j < mid; ++j, k = (LL)k * w1 % mod)
                {
                    int p = x[i | j], q = (LL)k * x[i | j | mid] % mod;
                    x[i | j] = x[i | mid | j] = p;
                    adj(x[i | j] += q - mod), adj(x[i | j | mid] -= q);
                }
        }
        if (~op) return;
        int itot = binpow(tot);
        for (int i = 0; i < tot; ++i)
            x[i] = (LL)x[i] * itot % mod;
    }
    void PolyMul (int n, int *f, int m, int *g, int *w)
    {
        static int A[N], B[N];
        for (int i = 0; i < n; ++i) adj(A[i] = f[i] - mod);
        for (int i = 0; i < m; ++i) adj(B[i] = g[i] - mod);
        ntt(A, 1), ntt(B, 1);
        for (int i = 0; i < tot; ++i)
            w[i] = (LL)A[i] * B[i] % mod;
        ntt(w, -1);
    }
};
NTT <p1> q1; NTT <p2> q2; NTT <p3> q3;
const L k1 = (L)p2 * p3 * q1.binpow((LL)p2 * p3 % p1), k2 = (L)p1 * p3 * q2.binpow((LL)p1 * p3 % p2), k3 = (L)p1 * p2 * q3.binpow((LL)p1 * p2 % p3);
int CRT (int x1, int x2, int x3)
{
    L res = (x1 * k1 + x2 * k2 + x3 * k3) % mul;
    if (res >= inf) res -= mul;
    if (res <= -inf) res += mul;
    return res % p;
}
void init (int x)
{
    bit = 1;
    while (x - 1 > 1 << bit) ++bit;
    tot = 1 << bit;
    for (int i = 0; i < tot; ++i)
        rev[i] = rev[i >> 1] >> 1 | ((i & 1) << bit - 1);
}
int main ()
{
    static int n, c, ic, m, g[N], ig[N], A[N], B[N], C[N], D[N], E[N];
    read(n, c, m);
    init(n + m);
    ic = binpow(c);
    g[0] = ig[0] = 1;
    for (int i = 1, t = 1, it = 1; i < n + m; ++i, t = (LL)t * c % p, it = (LL)it * ic % p)
        g[i] = (LL)g[i - 1] * t % p, ig[i] = (LL)ig[i - 1] * it % p;
    for (int i = 0; i < n; ++i)
        read(A[i]), A[i] = (LL)A[i] * ig[i] % p;
    for (int i = 0; i < n + m; ++i)
        B[n + m - 1 - i] = g[i];
    q1.PolyMul(n, A, n + m, B, C);
    q2.PolyMul(n, A, n + m, B, D);
    q3.PolyMul(n, A, n + m, B, E);
    for (int i = 0; i < n + m; ++i)
        A[i] = CRT(C[i], D[i], E[i]);
    for (int i = 0; i < m; ++i, putchar(' '))
        write((LL)A[n + m - 1 - i] * ig[i] % p);
    return 0;
}
```

---

