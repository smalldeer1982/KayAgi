# [AGC040F] Two Pieces

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc040/tasks/agc040_f

数直線上に，区別できない $ 2 $ つの駒が置かれています． どちらの駒も最初，座標 $ 0 $ にあります．（駒は同じ座標に同時に存在できます）

これらの駒に対して，以下の $ 2 $ 種類の操作が可能です．

- 好きな駒を $ 1 $ つ選び，$ 1 $ 大きい座標に移動する．
- 座標の小さい駒を，座標の大きい駒の位置へと移動する． なお，もともと $ 2 $ つの駒が同じ座標に置いてある場合は何も起きないが，その場合でも $ 1 $ 回の操作として数える．

以上の操作を好きな順番で $ N $ 回繰り返して，$ 2 $ つの駒の一方が座標 $ A $，他方が座標 $ B $ にあるようにしたいです． このような動かし方が何通りあるかを求めてください． ただし答えは非常に大きくなることがあるので，$ 998244353 $ で割ったあまりを求めてください．

なお，ある $ 2 $ つの動かし方 $ x,y $ が異なるとは，整数 $ i $ ($ 1\ \leq\ i\ \leq\ N $) であって， $ ( $ 動かし方 $ x $ で $ i $ 回目の操作後に駒の置いてある座標の集合 $ ) $ と $ ( $ 動かし方 $ y $ で $ i $ 回目の操作後に駒の置いてある座標の集合 $ ) $ が異なるものが存在することを意味します．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^7 $
- $ 0\ \leq\ A\ \leq\ B\ \leq\ N $
- 入力される値はすべて整数である．

### Sample Explanation 1

以下の $ 4 $ 通りの動かし方があります． なお，$ (x,y) $ で，駒の座標がそれぞれ $ x,y $ にある状態を表しています． - $ (0,0)→(0,0)→(0,1)→(0,2)→(0,3)→(1,3) $ - $ (0,0)→(0,0)→(0,1)→(0,2)→(1,2)→(1,3) $ - $ (0,0)→(0,0)→(0,1)→(1,1)→(1,2)→(1,3) $ - $ (0,0)→(0,1)→(1,1)→(1,1)→(1,2)→(1,3) $

## 样例 #1

### 输入

```
5 1 3```

### 输出

```
4```

## 样例 #2

### 输入

```
10 0 0```

### 输出

```
1```

## 样例 #3

### 输入

```
10 4 6```

### 输出

```
197```

## 样例 #4

### 输入

```
1000000 100000 200000```

### 输出

```
758840509```

# 题解

## 作者：Time_tears (赞：18)

太神了，我只能说太神了。

~~写个题解检验一下自己是否真正理解了。~~

首先我们是能够想到一种 $Dp$ 的做法，但复杂度过高，简单口胡一下就是设 $f_{i,j,k}$ 表示将 $A,B$ 都移到了 $i$ 这个位置，用了 $j$ 次操作，且中间有 $k$ 个地方 $A,B$ 相同了的方案数，转移就直接转移，也很麻烦就不写了。

然后我们思考一下，这个 $Dp$ 到底是因为什么才需要这么多维的呢。

就是因为 $2$ 操作，假如没有 $2$ 操作，我们的 $Dp$ 是完全不用设这么多维来转移的，所以我们现在只考虑 $1$ 操作。

我们把前面的那个点称作 $b$ 点，后面的称作 $a$ 点，在只考虑 $1$ 操作的前提下，显然 $b$ 点要走 $B$ 次，但 $a$ 点要走多少次我们并不知道，所以我们枚举 $a$ 点走了 $k$ 步。

为了避免重复，我们强制让 $a,b$ 之间的距离 $\geqslant1$，因为 $a,b$ 的距离从 $1 \rightarrow 0$ 的时候，我们无法区别是用了 $2$ 操作，还是把后面的那个点向前移了一步，所以不妨把这种情况就放到 $2$ 操作里面，前面直接计数距离 $\geqslant1$ 的。

现在我们要求的就是 $a$ 走了 $k$ 步， $b$ 走了 $B$ 步的方案数，且 $a,b$ 距离时刻 $\geqslant1$，这个用路径计数可以 $O(1)$ 做到。

然后我们现在要把 $2$ 操作加入 $1$ 操作的操作序列中。

设 $d_i$ 是执行完第 $i$ 个操作后 $a,b$ 的距离，每个能加入 $2$ 的位置都一定满足不存在 $j(i<j)$ 使得 $d_j \leqslant d_i$， 若存在，则执行 $2$ 操作会使得 $a$ 的位置大于 $b$ 的位置。

所以现在 $2$ 操作能够插入的位置就是每个 $i$ 满足 $d_i \in [0,A-k]$ 且 $i$ 是一个合法的能插入的位置，这样的位置显然有 $A-k+1$ 个而且必定是 $A-k+1$ 个，因为大于 $A-k$ 的部分是不满足限制的，具体的可以自行证明。

所以现在我们是要在 $A-k+1$ 个位置中插入 $n-B-k$ 个 $2$ 操作，但是要注意最后一个 $2$ 操作必须放在最后一个位置，所以相当于自由的部分只有 $n-B-k-1$，直接用隔板法即可，也是 $O(1)$ 计算。

总复杂度就是枚举 $k$ 的复杂度，$O(n)$ 。

~~这代码真短~~

```cpp
#include<bits/stdc++.h>
#define N 10000005
using namespace std;
const int mod=998244353;
int n,A,B,ans,fac[N],inv[N];
int Ksm(int a,int n,int ans=1) {
	for(; n; n>>=1,a=1ll*a*a%mod)if(n&1)ans=1ll*ans*a%mod;
	return ans;
}
int C(int n,int m) {
	if(n<0||m<0||n<m)return 0;
	return 1ll*fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int Mod(int x) {
	return x<mod?x:x-mod;
}
int Get(int a) {
	return Mod(C(a+B-1,a)-C(a+B-1,a-1)+mod);
}
int main() {
	cin>>n>>A>>B;if(!A&&!B)return puts("1"),0;
	for(int i=fac[0]=1; i<=n; ++i)fac[i]=1ll*fac[i-1]*i%mod;
	inv[n]=Ksm(fac[n],mod-2);for(int i=n-1; ~i; --i)inv[i]=inv[i+1]*(i+1ll)%mod;
	for(int a=0,mx=min(n-B,min(A,B-1)); a<=mx; ++a) {
		if(n-B-a) {
			int nn=n-B-a-1,mm=A-a+1;
			ans=(ans+1ll*Get(a)*C(nn+mm-1,mm-1))%mod;
		} else if(a==A)ans=Mod(ans+Get(a));
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：Log_x (赞：12)

## Solution

- 神仙题 QAQ

- 考虑非 DP 的做法。

- 为了简化问题，我们用二元组 $(x,d)$ 表示两点中坐标数值更大的点在 $x$ 且坐标数值更小的点到坐标数值更大的点的距离为 $d$，每次有以下三种操作：

  1. 将 $x$ 和 $d$ 同时加 $1$；
  2. 若 $d \ge 2$，将 $d$ 减 $1$；
  3. 将 $d$ 变为 $0$。

- 先考虑只进行 `操作1` 和 `操作2` 的方案数，枚举进行 `操作1` 和 `操作2` 的总次数，过程中要保证 $d$ 始终大于 $0$，用类似卡特兰数的计算方法计算即可。

- 令只进行 `操作1` 和 `操作2` 之后坐标数值较小的点的坐标为 $k$。

- 若 `操作3` 的数量为 $0$，方案合法当且仅当 $k = A$。

- 若 `操作3` 的数量大于 $0$，考虑将 `操作3` 插入到 `操作1` 和 `操作2` 的序列中。

- 将序列中第 $i$ 次操作后 $d$ 的值记作 $d_i$，可以发现 `操作3` 能够插在第 $i$ 次操作之后当且仅当不存在 $j(i < j)$ 使得 $d_j \le d_i$。

- 为了让最后的 $d$ 为 $B - A$，最后一次 `操作3` 一定是插在 $d$ 最后一次为 $A - k$ 的操作之后，那么剩余的 `操作3` 就可以插在 $d$ 最后一次为 $0 \sim A - k$ 的任意一个操作之后，用插板法计算即可。

- 时间复杂度 $\mathcal O(n)$。

## Code

```cpp
#include <bits/stdc++.h>

const int N = 1e7 + 5;
const int mod = 998244353;
int fra[N], inv[N];
int n, a, b, ans;

template <class T>
inline T Min(T x, T y) {return x < y ? x : y;}

inline void add(int &x, int y)
{
	x += y;
	x >= mod ? x -= mod : 0;
}

inline void dec(int &x, int y)
{
	x -= y;
	x < 0 ? x += mod : 0;
}

inline void add_prod(int &x, int u, int v)
{
	x = (1ll * u * v + x) % mod;
}

inline int quick_pow(int x, int k)
{
	int res = 1;
	while (k)
	{
		if (k & 1)
			res = 1ll * res * x % mod;
		x = 1ll * x * x % mod;
		k >>= 1;
	}
	return res;
}

inline int C(int n, int m)
{
	if (n < m)
		return 0;
	return 1ll * fra[n] * inv[n - m] % mod * inv[m] % mod;
}

inline int ask(int k)
{
	int res = C(k + b - 1, b - 1);
	dec(res, C(k + b - 1, k - 1));
	return res;
}

int main()
{
	scanf("%d%d%d", &n, &a, &b);
	if (a == 0 && b == 0)
		return puts("1"), 0;
	fra[0] = 1;
	for (int i = 1; i <= n; ++i)
		fra[i] = 1ll * fra[i - 1] * i % mod;
	inv[n] = quick_pow(fra[n], mod - 2);
	for (int i = n; i >= 1; --i)
		inv[i - 1] = 1ll * inv[i] * i % mod;

	for (int k = 0, km = Min(n - b, Min(a, b - 1)); k <= km; ++k)
	{
		int tmp = k ? ask(k) : 1;
		if (n - b - k == 0)
		{
			if (k == a)
				add(ans, tmp);
		}
		else
		{
			int x = n - b - k - 1,
				y = a - k + 1;
			if (x >= 0)
				add_prod(ans, tmp, C(x + y - 1, y - 1));
		}
	}
	printf("%d\n", ans);
	return 0;
}

```

---

## 作者：Y_B_X (赞：9)

[原题链接](https://www.luogu.com.cn/problem/AT5664)

将两个棋位置放到二维平面上，前面的作第一维，则走到的点不会超过 $y=x$ 这条线。

设 $n\geq m,f(n,m,k)$ 为走 $k$ 步到 $(n,m)$ 的方案数。

不妨设 $A\geq B$，则要求的答案为 $f(A,B,N)$。

直接三元生成函数不太好搞，考虑先只管 $n=m$ 时的答案。

则 $n>m$ 时，枚举最后一次在 $y=x$ 直线上的转移：

$$\displaystyle f(n,m,k)=\sum_{i=0}^m\left(\binom{n+m-2i-1}{m-i}-\binom{n+m-2i-1}{n-i}\right)f(i,i,k+2i-n-m)$$
$$=\sum_{i=0}^m\binom{n+m-2i}{m-i}\dfrac{n-m}{n+m-2i}f(i,i,k+2i-n-m)$$

其中的组合数就相当于从 $(i,i)$ 走到 $(n,m)$ 且不碰到 $y=x$ 的方案数。

对于 $n=m$，枚举最后一次“跳”过来前的位置：

$$f(n,n,k)=\sum_{m=0}^nf(n,m,k-1)=\sum_{m=0}^n\sum_{i=0}^m\binom{n+m-2i}{m-i}\dfrac{n-m}{n+m-2i}f(i,i,k-1+2i-n-m)$$

设 $\displaystyle F(x,y)=\sum_{n\geq 0}\sum_{k\geq 0}f(n,n,k)x^ny^k$

$$F(x,y)=1+\sum_{n\geq 0,k\geq 1}\sum_{m=0}^{n}\sum_{i=0}^m\binom{n+m-2i}{m-i}\dfrac{n-m}{n+m-2i}f(i,i,k-1+2i-n-m)$$

$$=1+\sum_{k\geq 1}\sum_{i\geq 0}\sum_{m\geq i}\sum_{n\geq m}\binom{n+m-2i}{m-i}\dfrac{n-m}{n+m-2i}f(i,i,k-1+2i-n-m)$$

$$=1+\sum_{k\geq 0}\sum_{i\geq 0}\sum_{m\geq 0}\sum_{n\geq m}\binom{n+m}{m}\dfrac{n-m}{n+m}f(i,i,k-n-m)x^{n+i}y^{k+1}$$

$$=1+y\sum_{m\geq 0}\sum_{n\geq m}\binom{n+m}{m}\dfrac{n-m}{n+m}x^ny^{n+m}\sum_{k\geq 0}\sum_{i\geq 0}f(i,i,k)x^iy^k$$

$$=1+yF(x,y)\left(\sum_{n\geq 0}\sum_{m=0}^{n}\binom{n+m}{m}\dfrac{n-m}{n+m}x^ny^{n+m}\right)$$

设 $\displaystyle T(x,y)=\sum_{n\geq 0}\sum_{m=0}^n\binom{n+m}{m}\dfrac{n-m}{n+m}x^ny^{m}$，有 $\displaystyle F(x,y)=\dfrac{1}{1-yT(xy,y)}$

考虑如何求出 $T(x,y)$ 的封闭形式，先取出 $[x^n]$ 的系数：

$$t_n(y)=\sum_{m=0}^n\binom{n+m}{m}\dfrac{n-m}{n+m}y^m$$

先暂且令 $a=n$，然后为了卷积的形式保留分子的 $n$：

$$t_n(y)=[x^n]\sum_{n\geq 0}x^n\sum_{m=0}^n\binom{a+m}{m}\dfrac{y^m}{a+m}(n-m)$$

$$=[x^n]\left(\sum_{n\geq 0}nx^n\right)\left(\sum_{n\geq 0}\binom{a+n}{n}\dfrac{y^n}{a+n}x^n\right)$$

$$=[x^n]\dfrac{x}{(1-x)^2}\dfrac{1}{a}\sum_{n\geq 0}\binom{a+n-1}{n}(xy)^n$$

$$=\dfrac{1}{a}[x^{n-1}]\dfrac{1}{(1-x)^2}\dfrac{1}{(1-xy)^a}$$

$$=\dfrac{1}{n}[x^{n-1}]\left(\dfrac{1}{1-x}\right)'(1-xy)^{-n}$$

全然的拉格朗日反演形式，而 $U(x)=x(1-xy)$ 的反函数是 $V(x)=\dfrac{1-\sqrt{1-4xy}}{2y}$

所以 $T(x,y)=\dfrac{1}{1-V(x)}=\dfrac{1}{1-\dfrac{1-\sqrt{1-4xy}}{2y}}$

于是 $F(x,y)=\dfrac{1}{1-yT(xy,y)}=\dfrac{1}{1-y\dfrac{1}{1-\dfrac{1-\sqrt{1-4xy^2}}{2y}}}$

而答案为 $\displaystyle f(A,B,N)=\sum_{i=0}^B\binom{A+B-2i}{B-i}\dfrac{A-B}{A+B-2i}f(i,i,2i+N-A-B)$

所以希望求出 $[x^i][y^{2i+N-A-B}]F(x,y)$。

由于 $F(x,y)$ 封闭形式中 $x$ 仅一次的出现伴随着 $y^2$，

令 $s\leftarrow A+B-N,w\leftarrow \dfrac{1-\sqrt{1-4x}}{2}$，有

$$[x^i][y^{2i-s}]F(x,y)=[x^i][y^{-s}]\dfrac{1}{1-y\dfrac{1}{1-\dfrac{1-\sqrt{1-4x}}{2y}}}=[x^i][y^{-s}]\dfrac{1}{1-y\dfrac{1}{1-\dfrac{w}{y}}}=[x^i][y^s]\dfrac{1}{1-\dfrac{1}{y-wy^2}}$$

把其展开取系数： $\displaystyle [y^s]\dfrac{1}{1-\dfrac{1}{y-wy^2}}=[y^s]\sum_{k\geq 0}y^{-k}\dfrac{1}{(1-wy)^{k}}=[y^s]\sum_{k\geq 0}\sum_{p\geq 0}\binom{k+p-1}{p}w^py^{p-k}=\sum_{p\geq s}\binom{2p-s-1}{p}w^p$

注意最后一个求和符号的界限，由于 $k,p\geq 0,k+p\geq p$，$2p-s$ 也需要 $\geq p$，因此 $p\geq s$ 

$$\displaystyle [x^i]\sum_{p\geq s}\binom{2p-s-1}{p}x^p\left(\dfrac{1-\sqrt{1-4x}}{2x}\right)^p$$
$$=[x^i]\sum_{p\geq s}\binom{2p-s-1}{p}x^p\sum_{r}\binom{2r+p}{r}\dfrac{p}{2r+p}x^r$$
$$=\sum_{p\geq s}\binom{2p-s-1}{p}\binom{2i-p}{i-p}\dfrac{p}{2i-p}$$

我们得到 $\displaystyle f(A,B,N)=\sum_{i}\binom{A+B-2i}{B-i}\dfrac{A-B}{A+B-2i}\sum_{p\geq s}\binom{2p-s-1}{p}\binom{2i-p-1}{i-p}\dfrac{p}{i}$

这并不好化简，但前面 $\dbinom{A+B-2i}{B-i}\dfrac{A-B}{A+B-2i}$ 的模样会感觉在推导过程中相似。

设 $d=A-B$，则上面的变为 $\dbinom{2(B-i)+d}{B-i}\dfrac{d}{2(B-i)+d}$，很有卷积的形式。

把与其相似的那条式子带入 $f(A,B,N)$：

$$f(A,B,N)=\sum_{i=0}^B\dbinom{2(B-i)+d}{B-i}\dfrac{d}{2(B-i)+d}[x^i]\left(\sum_{p\geq s}\binom{2p-s-1}{p}x^p\sum_{r}\binom{2r+p}{r}\dfrac{p}{2r+p}x^r\right)$$

这样就很清楚了，设 $\displaystyle \phi_{d,s}(x)=\sum_{A,B,N\geq 0}f(A,B,N)x^B[A-B=d][A+B-N=s]$，就有：

$$\phi_{d,s}(x)=\left(\sum_{i}\binom{2i+d}{i}\dfrac{d}{2i+d}x^i\right)\left(\sum_{p\geq s}\binom{2p-s-1}{p}x^p\sum_{r}\binom{2r+p}{r}\dfrac{p}{2r+p}x^r\right)$$
$$=\sum_{p\geq s}\binom{2p-s-1}{p}x^p\left(\sum_{r}\binom{2r+p}{r}\dfrac{p}{2r+p}x^r\right)\left(\sum_{i}\binom{2i+d}{i}\dfrac{d}{2i+d}x^i\right)$$
$$=\sum_{p\geq s}\binom{2p-s-1}{p}x^p\sum_{i}\binom{2i+p+d}{i}\dfrac{p+d}{2i+p+d}x^i$$

其中用到了 $\displaystyle \sum_{i}\binom{2i+a}{i}\binom{2n-2i+b}{n-i}\dfrac{a}{2i+a}\dfrac{b}{2n-2i+b}=\binom{2n+a+b}{n}\dfrac{a+b}{2n+a+b}$

这本质上是广义二项级数 $\mathcal{B}_t(x)^a\mathcal{B}_t(x)^b=\mathcal{B}_t(x)^{a+b}$ 在 $t=2$ 时的特例。

而我们要的就是 $\displaystyle [x^B]\phi_{d,s}(x)$，它等于

$$\sum_{p\geq s}\binom{2p-s-1}{p}\binom{2B-2p+p+d}{B-p}\dfrac{p+d}{2B-2p+p+d}$$

把 $d=A-B$ 带入后化简一下：

$$\sum_{p=0}^{B}\binom{2p-s-1}{p}\binom{A+B-p}{B-p}\dfrac{p+A-B}{A+B-p}$$

设 $a(p)=\dbinom{2p-s-1}{p}[p\geq s]$，这在 $p\geq s+1$ 时是很正常的组合数，再看看 $p=s$ 时的情况。

在 $s<0$ 时 $a(s)$ 一定是 $0$；$s>0$ 时 $a(s)=\dbinom{s-1}{s}$ 也是 $0$。

但在 $s=0$ 时 $a(s)=\dbinom{-1}{0}=1$ 要注意特判一下。

然后做代换 $p\leftarrow B-p$ 我们就能得到简洁的答案：

$$f(A,B,N)=\sum_{p=0}^B\binom{A+p}{p}\dfrac{A-p}{A+p}a\left(B-p\right)$$

于是这题能在线性时空复杂度内解决。

$\texttt{Code:}$

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e7+10;
const int mod=998244353;
int n,m,nn,x,y,A,B,s;
int fac[N],ifac[N],a[N];
ll res,ans;
inline void qpow(ll x,int k){
	res=1;
	while(k){
		if(k&1)res=res*x%mod;
		x=x*x%mod;k>>=1;
	}
}
inline void init(int n){
	int i;
	fac[0]=ifac[0]=1;
	for(i=1;i<=n;++i)fac[i]=1ll*fac[i-1]*i%mod;
	qpow(fac[n],mod-2);ifac[n]=res;
	for(i=n;i;--i)ifac[i-1]=1ll*ifac[i]*i%mod;
}
main(){
	scanf("%d%d%d",&n,&B,&A);
	A<B?swap(A,B),0:0;int i;
	init(max(n,A+B));s=A+B-n;
	if(!A&&!B)return putchar(49),0;
	for(i=max(s+1,0);i<=B;++i)
		a[i]=1ll*fac[(i<<1)-s-1]*ifac[i]%mod*ifac[i-s-1]%mod;
	s||(a[0]=1);
	for(i=0;i<=B;++i)
		ans+=1ll*fac[A+i-1]*ifac[i]%mod*(A-i)%mod*a[B-i]%mod;
	printf("%d",ans%mod*ifac[A]%mod);
}
```

#### 后续：

其实在 $s\leq 0$ 时，由于 $p\geq s$ 的限制没了，$\phi_{d,s}(x)$ 能推出其封闭形式：

$$\sum_{p}\binom{2p-s-1}{p}x^p\sum_{i}\binom{2i+p+d}{i}\dfrac{p+d}{2i+p+d}x^i$$
$$=\sum_{p}\binom{2p-s-1}{p}x^p\mathcal{B}_2(x)^{p+d}$$
$$=\mathcal{B}_2(x)^d\sum_{p}\binom{2p-s-1}{p}\left(x\mathcal{B}_2(x)\right)^{p}$$
$$=\mathcal{B}_2(x)^d\dfrac{\mathcal{B}_2(x\mathcal{B}_2(x))^{-s-1}}{\sqrt{1-4x\mathcal{B}_2(x)}}$$
$$=\left(\dfrac{1-\sqrt{1-4x}}{2x}\right)^d\dfrac{1}{\sqrt{2\sqrt{1-4x}-1}}\left(\dfrac{1-\sqrt{2\sqrt{1-4x}-1}}{1-\sqrt{1-4x}}\right)^{-s-1}$$
$$=\dfrac{1}{\sqrt{2\sqrt{1-4x}-1}}\left(\dfrac{1-\sqrt{1-4x}}{2x}\right)^{d+s+1}\left(\dfrac{1-\sqrt{2\sqrt{1-4x}-1}}{2x}\right)^{-s-1}$$

于是你可以固定 $d,-s$ 并开到 $10^{18}$ 级别，然后让 $B$ 取 $[0,10^5]$ 内的整数全部输出答案，

在这样一道 $\text{Yet Another Two Pieces Problem}$  中，大概组合意义能凉凉了。

---

## 作者：Mortidesperatslav (赞：8)

组合意义神仙题……

看其他题解没看懂讲的是什么意思，所以自己写一篇 qwq。

### 前置知识：隔板法

有 $n$ 个相同的球，放进 $m$ 个不同的盒子里，要求每个盒子不为空，有多少种方法？

答案是 $C_{n-1}^{m-1}$。我们可以看做在 $n$ 个球中间插入 $m-1$ 个隔板，因为有 $n-1$ 个空隙，选出 $m-1$ 个，所以答案是 $C_{n-1}^{m-1}$。

有 $n$ 个相同的球，放进 $m$ 个不同的盒子里，有多少种方法？

同理可得，答案是 $C_{m+n-1}^{n}$。

### 本题做法

因为两个棋相同，所以不放设两个棋为 $u,v$，且 $u \leq v$。

考虑在移动 $v$ 的操作中插入移动 $u$ 的操作。

首先插入令 $u$ 加上 $1$ 的操作，假设有 $i$ 个，我们枚举 $i$（考虑始终满足 $u \neq v$，把 $u=v-1$ 的操作转为操作二）。根据插板法第一个例子可以知道是 $C_{B+i-1}^{i}-C_{B+i-1}^{i-1}$。

然后考虑插入令 $u=v$ 的操作。注意到可以相邻。空位有 $n-B-i$ 个。要插入 $A-i$ 个，根据插板法第二个例子可以知道是 $C_{n-B-i+A-i-1}^{A-i}=C_{n+A-B-2i-1}^{A-i}$。

乘起来即可。但是有一个细节：若 $i+B=n$，当且仅当 $i=A$ 时有贡献，贡献为 $C_{B+i-1}^{i}-C_{B+i-1}^{i-1}$。

最后是 $i$ 的值域。显然是 $\min\{A,\min\{B-1,n-B\}\}$。

然后做就行了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 998244353;
int n, a, b, fac[10000005], inv[10000005], ans;
int qpow(int x, int k){
	int ans = 1;
	while (k){
		if (k & 1)
			ans = ans * x % mod;
		x = x * x % mod;
		k >>= 1;
	}
	return ans;
}
int qmod(int a, int b){
	return a * qpow(b, mod - 2) % mod;
}
int C(int n, int m){
	return fac[n] * inv[n - m] % mod * inv[m] % mod;
}
int nmod(int x){
	return (x % mod + mod) % mod;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n >> a >> b;
	if (!a && !b){
		cout << 1;
		return 0;
	}
	fac[0] = 1;
	for (int i = 1; i <= n; i++)
		fac[i] = fac[i - 1] * i % mod;
	for (int i = 0; i <= n; i++)
		inv[i] = qmod(1, fac[i]);
	for (int i = 0; i <= min(min(a, b - 1), n - b); i++){
		if (n - b - i == 0){
			if (i == a)
				ans = (ans + nmod(C(b + i - 1, i) - C(b + i - 1, i - 1))) % mod;
		}else{
			int qwq = (nmod(C(b + i - 1, i) - C(b + i - 1, i - 1))) % mod;
			ans = (ans + (qwq * C(n + a - b - 2 * i - 1, a - i) % mod)) % mod;
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Aleph1022 (赞：8)

不妨设 $a\le b$。

大力转化为格点路径。考虑按碰到 $y=x$ 的位置把操作序列拆分，那么先考虑一个这样的问题：从 $(0,0)$ 走到 $(i,m)$ $(i < m)$ 且不碰到 $y=x$ 的路径数。  
令 $C = x(1+C)^2$ 为卡特兰数的 GF，$G(u,v)$ 为这样的路径的 BGF，则显然
$$
G(u,v) = \frac1{1-v(1+C(uv))}
$$

令 $F(u,v,w)$ 为答案的 GF，其中 $u,v$ 计量坐标，$w$ 计量操作数，有
$$
F(u,v,w) = \frac{G(uw,vw)}{1-wG(w,uvw)}
$$

换元
$$
\begin{aligned}
[u^av^bw^n]F(u,v,w)
&= [x^ay^{b-a}w^n] F(x/y,y,w) \\
&= [x^ay^{b-a}w^n] \frac{w^{b-a}(1+C(xw^2))^{b-a}}{1-wG(w,xw)}
\end{aligned}
$$

考虑
$$
[x^a]x^kw^k(1+C(xw^2))^{b-a+k} = w^{2a-k} [x^a] x^k(1+C(x))^{b-a+k}
$$

不妨设

$$
t^k = [x^a] x^k (1+C(x))^{b-a+k}
$$

则答案为
$$
[w^{n-a-b}] \frac{1-t/w}{1-t/w-w} = [w^{n-a-b}](1-t/w) \sum_{i\ge 0}\sum_{j\ge 0} \binom{i+j}j (t/w)^i w^j
$$

然后用（另类）拉格朗日反演可以算出 $t^k$：
$$
\begin{aligned}
t^k &= [x^a] x^k (1+C(x))^{b-a+k} \\
&= [x^a] \frac{x^k}{(1+x)^{2k}} (1+x)^{b-a+k} \frac{1-x}{(1+x)^3} (1+x)^{2a+2} \\
&= [x^{a-k}] (1-x)(1+x)^{a+b-k-1}
\end{aligned}
$$

代码：
```cpp
#include <cstdio>
#include <algorithm>

using ll = long long;

using namespace std;

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

const int N = 2e7;

int fac[N + 5], ifac[N + 5];
inline int binom(int n, int m) {
  return n < m || m < 0 ? 0 : (ll)fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

int n, a, b, lim;

inline int f(int k) {
  if (k == a + b)
    return b == 0;
  return reduce(binom(a + b - k - 1, a - k) - binom(a + b - k - 1, a - k - 1));
}

int ans;

int main() {
  scanf("%d%d%d", &n, &a, &b), lim = max(a + b, n);
  fac[0] = 1;
  for (int i = 1; i <= lim; ++i)
    fac[i] = (ll)fac[i - 1] * i % mod;
  ifac[lim] = qpow(fac[lim], mod - 2);
  for (int i = lim; i; --i)
    ifac[i - 1] = (ll)ifac[i] * i % mod;
  for (int i = 0; i <= a; ++i) {
    int j = n - a - b + i;
    if (j < 0)
      continue;
    int coe = reduce(binom(i + j, i) - binom(i - 1 + j, i - 1));
    fam(ans, coe, f(i));
  }
  printf("%d\n", ans);
}
```

---

## 作者：whiteqwq (赞：5)

[AGC040F Two Pieces](https://www.luogu.com.cn/problem/AT5664) 解题报告：

[更好的阅读体验](https://www.cnblogs.com/xiaoziyao/p/15913372.html)

## 题意

数轴上有两个棋子，初始都在 $0$ 位置，进行 $n$ 次操作，每次将一个棋子移动一步或者是把靠后的棋子移到靠前的棋子的位置，两个棋子无法区分，求最后两个棋子分别到 $A,B$ 的方案数。

$1\leqslant n\leqslant 10^7$。

## 分析

orz p_b_p_b。

不妨令 $1$ 为坐标较大的棋子，$2$ 为另一个，令 $A\geqslant B$。

把 $2$ 的坐标和 $1$ 的坐标作为数对，看作二维平面上的一个点。我们画出直线 $y=x$，那么让 $1$ 走一步就是向右（记为操作 $1$），让 $2$ 走一步就是向上（记为操作 $2$），让 $2$ 跳到 $2$ 就是跳到直线上（记为操作 $3$），且操作 $2$ 不能碰触直线，最后要到达  $(A,B)$。

操作 $3$ 次数为 $0$ 的时候很容易处理，可以类似卡特兰数使用折线法。（注意是不能碰触直线，所以要将坐标系整体左移一格）

我们发现跳到直线上很难处理，我们将操作 $3$ 转化成将直线移到当前位置上。记最后一次操作的坐标为 $(x_0,y_0)$，那么我们的终点就应该是 $(A-1,B-(x_0-y_0))$。（$A-1$ 的原因上面说了）

但是还是很难考虑，我们考虑在确定了 $(x_0-y_0)$ 以及行走出来的格路之后，将操作 $3$ 插入操作序列。观察可以得到，对于让直线变为 $y=x-k$ 的操作 $3$，它的插入位置一定只能是这个直线与格路的最后一个交点（容易发现满足条件的操作 $3$ 即 $0,1,\cdots,k$），于是枚举 $x_0-y_0$，然后插板法计算即可。

复杂度 $O(n)$。

## 代码

```
#include<stdio.h>
const int maxn=10000005,mod=998244353;
int n,a,b,ans;
int fac[maxn],nfac[maxn],inv[maxn]; 
inline int C(int a,int b){
	return b==0? 1:((a<b||b<0)? 0:1ll*fac[a]*nfac[b]%mod*nfac[a-b]%mod);
}
int main(){
	fac[0]=nfac[0]=1;
	for(int i=1;i<maxn;i++)
		fac[i]=1ll*fac[i-1]*i%mod,inv[i]=i==1? 1:(mod-1ll*(mod/i)*inv[mod%i]%mod),nfac[i]=1ll*nfac[i-1]*inv[i]%mod;
	scanf("%d%d%d",&n,&b,&a);
	if(a==0&&b==0){
		puts("1");
		return 0;
	}
	for(int i=0;i<=b&&i<a&&i<n-a;i++)//(a-1,i)
		ans=(ans+1ll*(C(i+a-1,i)-C(i+a-1,i-1)+mod)*C((n-a-i-1)+(b-i+1)-1,(b-i+1)-1))%mod;
	if(a+b==n)
		ans=(ans+0ll+C(a+b-1,b)-C(a+b-1,b-1)+mod)%mod;
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：EuphoricStar (赞：3)

第二道问号题。

设 $A \ge B$。我们现在将点的坐标刻画到二维平面上。相当于找到一条 $(0, 0) \to (A, B)$ 的路径，要求不能跨过直线 $y = x$。有 $3$ 种移动方式：

1. 向右移动一格。
2. 向上移动一格。
3. 将当前点提到直线 $y = x$ 上，也就是将 $y$ 坐标赋值为 $x$ 坐标。

为了避免算重，其中 $2$ 操作要求向上移动一格后，点不能在直线 $y = x$ 上。

若不使用操作 $3$ 答案是好算的。相当于找到一条 $(1, 0) \to (A, B)$ 的不**接触**直线 $y = x$ 的一条路径，考虑容斥，将任意一条与直线 $y = x$ 有交的路径的最后一个交点拿出来，把这之前的部分沿直线 $y = x$ 翻转，可以发现有交点的方案数就是 $(0, 1) \to (A, B)$ 的方案数。所以无交点的方案数是 $\binom{A + B - 1}{A - 1} - \binom{A + B - 1}{A}$。

若使用操作 $3$，考虑相对运动，将把点提到直线 $y = x$ 上，变成将直线拉到 $y = x - k$。设在点 $(x_0, y_0)$ **最后一次**使用操作 $3$，设 $k = x_0 - y_0$，那么我们的终点是 $(A, B - k)$，直线最终位于 $y = x - k$。

考虑分配除了最后一次的操作 $3$。我们确定了一条 $(1, 0) \to (A, B - k)$ 的折线后，一个点 $(x, x - d)$ 可以使用操作 $3$ 当且仅当这个点是直线 $y = x - d$ 与折线的最后一个交点。发现 $d = 0, 1, \ldots, k$ 都唯一对应一个点。于是我们把 $n - A - (B - k) - 1$ 次操作 $3$（减 $1$ 是因为 $d = k$ 至少要使用一次操作 $3$）分配到这 $k + 1$ 个点上，插板算即可。

[code](https://atcoder.jp/contests/agc040/submissions/48499588)

---

## 作者：analysis (赞：2)

抽象成格路上的行动，每次可以向上走或向右走或飞到 $y=x$ 上,注意到两棋子没有区别所以强制在 $y=x$ 上方行走。

我们把行动分为若干段，以触碰到 $y=x$ 为分界。在两个分界点之间的行动按照 $|x-y|=d$ 最后出现的位置分界大概是 Y-Y-Y-X 的形式（`Y` 是令 $|x-y|$ 加一的操作，`-` 是若干次操作满足 $|x-y|\geq|x_0-y_0|$ 使得最后 $|x-y|=|x_0-y_0|$，`X` 是回到 $y=x$）。

`-` 明显就是卡特兰数，有 GF $C=x(1+C)^2$。`Y` 就是走一步，向上（$y+1$）。先不管 `X`（因为最后一段可能不用到这种操作），移动的整体 GF 就是 $G(u,v)=\frac{1}{1-v(1+C(uv))}$。

还有 `X` 就是把缺少的 $x$ 补上。三种情况都是操作数加一。枚举 `X` 前的移动，则有一段的 GF：

$$
\sum_{a,b}([u^av^b]G(u,v))u^bv^bw^{a+b+1}=wG(w,uvw)
$$

所以答案就是：

$$
[u^av^bw^n]\frac{G(uw,vw)}{1-wG(w,uvw)}
$$

换元，令 $x=uv$，则答案：

$$
[x^av^{b-a}w^n]\frac{\frac{1}{1-vw(1+C(xw^2))}}{1-\frac{w}{1-xw(1+C(xw^2))}}
$$

注意到 $v$ 分布异常集中，先消掉 $v$：

$$
[x^aw^n]\frac{(w(1+C(xw^2)))^{b-a}}{1-\frac{w}{1-xw(1+C(xw^2))}}
$$

为了简洁方便，设 $t=w(1+C(xw^2))$，则：

$$
[x^aw^n]\frac{(1-xt)t^{b-a}}{1-(xt+w)}\\\
=[x^aw^n] (\sum_{i \geq 0}(xt+w)^it^{b-a}-\sum_{i \geq 0}(xt+w)^ixt^{b-a+1})
$$

先解决第一个：

$$
[x^aw^n]\sum_{i \geq 0}(xt+w)^it^{b-a}\\\
=[x^aw^n]\sum_{i \geq 0}\sum_{j \geq 0}\binom{i}{j}x^jw^{b-a+i}(1+C(xw^2))^{b-a+j}\\\
=[w^n]\sum_{j \geq 0}([x^{a-j}] (1+C(xw^2))^{b-a+j})\sum_{i \geq 0}\binom{i}{j}w^{b-a+i}\\\
=[w^n]\sum_{j \geq 0}(w^{2(a-j)}[x^{a-j}] (1+C(x))^{b-a+j})\sum_{i \geq 0}\binom{i}{j}w^{b-a+i}\\\
=\sum_{j \geq 0}\binom{n-a-b+2j}{j}[x^{a-j}] (1+C(x))^{b-(a-j)}
$$

先放着，再来看第二个：

$$
[x^aw^n] \sum_{i \geq 0}(xt+w)^ixt^{b-a+1}\\\
=\sum_{j \geq 0}\binom{n-a-b+2j+1}{j}[x^{a-j-1}]  (1+C(x))^{b-(a-j-1)}
$$

可见问题在于求 $f(n)=[x^n] (1+C(x))^{b-n}$。

$C$ 的复合逆为 $h(x)=\frac{x}{(x+1)^2}$。根据（另类）拉格朗日反演得到：

$$
f(n)=[x^n] (1+C(x))^{b-n}\\\
=[x^n] ((1+x)^{b+n}-2x(1+x)^{b+n-1})\\\
=([x^n] (1+x)^{b+n}-2[x^{n-1}] (1+x)^{b+n-1})\\\
=\binom{b+n}{n}-2\binom{b+n-1}{n-1}
$$

可见，答案为：

$$
= \sum_{j \geq 0}\binom{n-a-b+2j}{j}f(a-j)-\binom{n-a-b+2j+1}{j}f(a-j-1)
$$

$f$ 中组合数限制了 $j$ 的范围，枚举到 $a$ 即可。

[code](https://atcoder.jp/contests/agc040/submissions/61452499)

---

## 作者：_lbw_ (赞：2)

upd on 2023.1.12：额，我怎么把标题起错了。

upd on 2023.1.29：修了锅，然后补了点东西。

alpha1022 的题解人话版。

先将问题转化到坐标轴上。

下文中 G 指只往右或上走且不碰到 $y=x$ 的走法，冲指 2 操作。

首先我们只考虑一操作，也就是 G ，将其 GF 设为 $G(u,v)(u<v)$。

将向右走记为 `(`，向上走记为 `)`，我们设一个合法括号匹配为 $C$，那么最终括号序列一定长这样：`C(C(C(C(C(C`。

As we know，Catalan 数的 GF 为 $C=x(1+C)^2$。

于是我们考虑每次加入一个 `(` 和一个合法括号序列，它的 GF 为 $v\times (1+\sum C(a)u^a v^a)=v(1+C(uv))$。

于是 $G(u,v)=\textsf{SEQ}(v(1+C(uv)))=\dfrac1{1-v(1+C(uv))}$ 。

定义答案的 GF 为 $F(u,v,w)$，$u,v$ 计量坐标，$w$ 计量次数。

接下来思考答案走一步的 GF，它包含一次 G 和一次冲。

设 G 走了 $(a,b)$，最后一次冲到 $(b,b)$，它对 $u$ 的贡献为 $b$，对 $v$ 的贡献为 $b$，对 $w$ 的贡献为 $a+b+1$，对方案数的贡献为 $G(a,b)$，全部乘起来就是 $\sum G(a,b)w(w)^a(uvw)^b=wG(w,uvw)$。

而只有 G 的 GF 同理可得为 $\sum G(a,b)(uw)^a(vw)^b=G(uw,vw)$

所以 $F(u,v,w)=G(uw,vw)\times \textsf{SEQ}(wG(w,uvw))=\dfrac{G(uw,vw)}{1-wG(w,uvw)}$，答案即为 $[u^av^bw^n]F(u,v,w)$

发现分子只与 $uv$ 有关，设 $uv$ 为 $x$，$v$ 为 $y$。

$$[u^av^bw^n]F(u,v,w)=[x^ay^{b-a}w^n]\dfrac{G(wx/y,yw)}{1-wG(w,xw)}$$

$$=[x^aw^n]\dfrac{[y^{b-a}]G(wx/y,yw)}{1-wG(w,xw)}$$

$$[y^{b-a}]G(wx/y,yw)=[y^{b-a}]\dfrac 1{1-yw(1+C(w^2x))}$$

$$=[y^{b-a}]\textsf{SEQ}(yw(1+C(w^2x)))$$

想想 SEQ 的意义？

$$=w^{b-a}(1+C(w^2x))^{b-a}$$

$$[x^aw^n]\dfrac{[y^{b-a}]G(wx/y,yw)}{1-wG(w,xw)}=[x^aw^n]\frac{w^{b-a}(1+C(w^2x))^{b-a}}{1-wG(w,xw)}$$

接下来有点难化简了，直接粗暴把 $G(w,xw)$ 带入 $\dfrac{w}{1-xw(1+C(xw^2))}$，设 $t=1+C(xw^2)$。

原式可以变为 $\dfrac{w^{b-a}t^{b-a}}{1-\dfrac{w}{1-xwt}}=w^{b-a}t^{b-a}\times \dfrac{1-xwt}{1-xwt-w}$

然后我们暴力把分母展开啊，就变成了：

$(1-xwt)\sum\limits_{i\geq 0}(xwt+w)^iw^{b-a}t^{b-a}=(1-xwt)T=T-xwtT$

我们先只考虑 $[x^aw^n]T$ 的计算，剩下的在会做 $T$ 后同理。

用二项式定理展开：$T=\sum\limits_{i\ge0}\sum\limits_{j\ge0}\dbinom{i}{j}(xwt)^iw^jw^{b-a}t^{b-a}$，这个时候我们发现关于 $x$ 的项比较少且只与 $x$ 有关，可以先处理（注意 $t$ 与 $x$ 也有关！！）。

$$[x^aw^n]\sum\limits_{i\ge0}\sum\limits_{j\ge0}\dbinom{i}{j}(xwt)^iw^jw^{b-a}t^{b-a}$$

$$=[w^n]\sum\limits_{i\ge0}[x^a](xwt)^it^{b-a}\sum\limits_{j\ge0}\dbinom{i}{j}w^jw^{b-a}$$

$$[x^a]x^iw^it^{i+b-a}=[x^a]x^iw^i(1+C(xw^2))^{i+b-a}$$

注意到 $(1+C(wx^2))^{i+b-a}$ 里应当有 $a-i$ 个 $x$，且 $xw^2$ 是在一起的，故知后面有 $2(a-i)$ 个 $w$，所以：

$$[x^a]x^iw^i(1+C(wx^2))^{i+b-a}=[x^a]x^iw^iw^{2a-2i}(1+C(x))^{i+b-a}=w^{2a-i}[x^a]x^i(1+C(x))^{i+b-a}$$

于是枚举 $i$ 后考察 $w$ 的个数可以发现唯一确定了一个 $j$。

问题便只剩下了 $[x^a]x^i(1+C(x))^{i+b-a}$ 回归 $C$ 的定义式不难想到利用拉格朗日反演解决，具体过程可以参见 alpha1022 的博客。

综上，本题得到 GF 的解决。







---

## 作者：james1BadCreeper (赞：0)

考虑没有 $2$ 操作怎么做。为了避免重复计数，强制让 $a,b$ 距离 $\ge 1$（我们只区分操作时的位置，因此 $=0$ 的会在考虑 $2$ 操作时统计）。反射容斥做一下即可。

考虑加入操作 $2$。考虑枚举一次操作 $2$ 造成的移点贡献，也就是枚举最后一次进行操作 $2$ 时的 $k=x-y$，那么可以视作将终点拉到 $(A,B-k)$，将此视为新的格路。

将剩余的 $n-A-(B-k)-1$ 个 $3$ 操作分配到操作序列中，实际上是要给到 $k+1$ 个点（在它们身上进行 $3$ 操作），它们是直线 $y=x-d$（$d\in [0,k]$，$d>k$ 越过了之前钦定的最后一次 $3$ 操作）与新的格路的最后一个交点，只有最后一个交点是合法的，否则会有将 $y$ 坐标 +1 类的操作无法进行。分配之后，会将移动 $k$ 的贡献分摊掉。

特判 $A+B=n$ 的情况即可。

```cpp
#include <bits/stdc++.h>
using namespace std; 
const int P = 998244353; 
const int N = 2e7 + 5; 

inline int poww(int a, int b) {
    int r = 1; 
    for (; b; b >>= 1, a = 1ll * a * a % P) if (b & 1) r = 1ll * r * a % P; 
    return r; 
}
int n, A, B; 
int fac[N], ifac[N]; 
inline void initFac(void) {
    for (int i = fac[0] = 1; i < N; ++i) fac[i] = 1ll * fac[i - 1] * i % P; 
    ifac[N - 1] = poww(fac[N - 1], P - 2); 
    for (int i = N - 2; i >= 0; --i) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % P; 
}
inline int C(int n, int m) {
    if (m < 0 || n < m || n < 0) return 0; 
    return 1ll * fac[n] * ifac[m] % P * ifac[n - m] % P; 
}
inline int F(int a, int b) {
    return (C(a + b - 1, a - 1) - C(a + b - 1, b - 1) + P) % P; 
}

int main(void) {
    initFac(); 
    cin >> n >> B >> A; // A >= B
    if (A == 0 && B == 0) return cout << "1\n", 0; 
    int ans = (A + B == n ? F(A, B) : 0); 
    for (int k = 0; k <= B; ++k)
        // B - k 次 up
        ans = (ans + 1ll * F(A, B - k) * C(n - A - (B - k) - 1 + k, k)) % P; 
    cout << ans << '\n'; 
    return 0;
}
```

---

