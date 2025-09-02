# [ICPC 2020 Nanjing R] Fireworks

## 题目描述

Kotori is practicing making fireworks for the upcoming hanabi taikai$^1$. It takes her $n$ minutes to make a single firework, and as she is not really proficient in making fireworks, each firework only has a probability of $p \times 10^{-4}$ to be perfect.

After she finishes making a firework, she can just start making the next firework, or take $m$ minutes to light all the remaining fireworks finished before. If there is at least one perfect firework among the lit ones, she will be happy and go to rest. Otherwise, she will continue practicing. Can you tell her the minimum expected practicing time before she goes to rest if she takes the optimal strategy?

Notice that no matter how many fireworks remain, it always takes $m$ minutes to light them all.

$^1$ Hanabi taikai: Romaji of the Japanese word ``花火大會``, which means the firework... err... party?

## 样例 #1

### 输入

```
3
1 1 5000
1 1 1
1 2 10000```

### 输出

```
4.0000000000
10141.5852891136
3.0000000000```

# 题解

## 作者：一只绝帆 (赞：5)

upd on 2023.9.12:成小丑了

高中数学选修三告诉我们有一个东西叫几何分布。

简单来说就是你做某件事，每次 $p$ 的概率成功，不成功就从头再来，则期望进行次数 $\frac 1 p$，这个很好理解吧，如果每次花费 $x$ 的代价，则期望代价 $\frac x p$。

于是我可爱的又臭又长的式子就只有最后证明凸函数是有用的了。

原题解：

我不知道为什么这个题大家过的这么猛。

我只知道我写了两黑板的式子，中间还推错了两次。

公式量可能较大。

首先简化一下题意，假装造一个烟花只需要 $1$ 的代价，也就是 $m\gets \frac m n$，最后再 $ans\gets ans\times n$。

考虑一个最优策略一定是造 $x$ 个烟花检查一次，造 $x$ 个烟花检查一次，这个 $x$ 一定是定值（因为如果检查失败了那么可以规约到最开始的时刻）。

那我们考虑写出一个关于 $x$ 的式子然后求最值。

第一组就成功的概率是 $1-(1-p)^x$，时间是 $x+m$；第二次成功概率是 $(1-p)^x(1-(1-p)^x)$，时间是 $2(x+m)$……

（注意不是 $2x+m$，因为你做完前 $x$ 个并不能实时知道自己成功了没有。）

所以我们可以写出答案：

$$\sum_{i=0}^{\infty}(1-p)^{ix}\left(1-(1-p)^x\right)(i+1)(x+m)$$

无穷级数肯定求不了一点，那我们考虑化简这个可爱的东西。

首先是把无用项提到前面。

$$\begin{aligned}
    & \sum_{i=0}^{\infty}(1-p)^{ix}\left(1-(1-p)^x\right)(i+1)(x+m) \\
=\  & \left(1-(1-p)^x\right)(x+m)\sum_{i=0}^{\infty}(1-p)^{ix}(i+1)\\
\end{aligned}$$

然后我们考虑如何求这个东西：$\sum_{i=0}^{\infty}(1-p)^{ix}(i+1)$。

这不是普通的等比数列求和，也不是等差数列求和，而是等比等差数列各项分别相乘再求和。

我们可以用类似于推等比数列求和公式的方法来推。

$$\begin{aligned}
\texttt{设}\ S_{k}&=\sum_{i=0}^{k}(1-p)^{ix}(i+1)\\ \texttt{则}\ (1-p)^xS_k&=\sum_{i=0}^k(1-p)^{(i+1)x}(i+1)
\\ &=\sum_{i+1=1}^{k+1}(1-p)^{(i+1)x}(i+1) \\&=\sum_{i=1}^{k+1}(1-p)^{ix}i\\\texttt{则} \ (1-p)^xS_k-S_k&=(1-p)^{(k+1)x}(k+1)-\sum_{i=1}^k(1-p)^{ix}-1\\\texttt{则}\ S_k&=\frac{(1-p)^{(k+1)x}(k+1)-\sum\limits_{i=1}^k(1-p)^{ix}-1}{(1-p)^x-1}\end{aligned}$$

发现好像还有一个可爱的 $\sum$，但是此时已经是等比数列求和了，简单搞一搞：

$$\begin{aligned}\texttt{设}\ T_{k}&=\sum_{i=1}^k(1-p)^{ix}\\\texttt{则}\ (1-p)^xT_k&=\sum_{i=1}^k(1-p)^{(i+1)x}\\&=\sum_{i+1=2}^{k+1}(1-p)^{(i+1)x}\\&=\sum_{i=2}^{k+1}(1-p)^{ix}\\\texttt{则}\ (1-p)^xT_k-T_k&=(1-p)^{(k+1)x}-(1-p)^x\\\texttt{则}\ T_k&=\frac{(1-p)^{(k+1)x}-(1-p)^x}{(1-p)^x-1}\end{aligned}$$

好！

那我们接着化简 $S_k$ 吧！

$$\begin{aligned}S_k&=\frac{(1-p)^{(k+1)x}(k+1)-\sum\limits_{i=1}^k(1-p)^{ix}-1}{(1-p)^x-1}\\&=\frac{(1-p)^{(k+1)x}(k+1)-\frac{(1-p)^{(k+1)x}-(1-p)^x}{(1-p)^x-1}-1}{(1-p)^x-1}
\end{aligned}$$

然后我们令 $k\to \infty$，分别讨论每个含 $k$ 的式子。

- $(1-p)^{(k+1)x}(k+1)$：由于左方是指数式子，增长率一定比右边的线性式子快，所以 $(1-p)^{(k+1)x}(k+1)\to 0$。

- $(1-p)^{(k+1)x}\to 0$，这个很显然。

所以：

$$\begin{aligned}S_{\infty}&=\frac{-\frac{-(1-p)^x}{(1-p)^x-1}-1}{(1-p)^x-1}\\&=\frac{1+\frac{(1-p)^x}{1-(1-p)^x}}{1-(1-p)^x}\end{aligned}$$

那么就可以求出答案了：

$$\begin{aligned}ans&=\left(1-(1-p)^x\right)(x+m)S_{\infty}\\&=\left(1-(1-p)^x\right)(x+m)\frac{1+\frac{(1-p)^x}{1-(1-p)^x}}{1-(1-p)^x}\\&=(x+m)\left(1+\frac{(1-p)^x}{1-(1-p)^x}\right)\\&=(x+m)\left(\frac{1}{1-(1-p)^x}\right)\\&=\frac{x+m}{1-(1-p)^x}\end{aligned}$$

但是由于我们 $x$ 是设好的常量，我们还得对 $x$ 求 $\min\limits_x\frac{x+m}{1-(1-p)^x}$。

~~画出函数图像~~下面我们证一下这个东西是凸的。

$$\begin{aligned} \texttt{设} \ f(x)&=\frac{x+m}{1-(1-p)^x}\\\texttt{则}\ f'(x)&=\frac{\ln\left(1-p\right)\left(1-p\right)^x\left(x+m\right)}{\left(1-\left(1-p\right)^x\right)^2}+\dfrac{1}{1-\left(1-p\right)^x}\end{aligned}$$

后面那一项显然随 $x$ 增大而减小，前面那一项的 $(1-p)^x(x+m)$ 乘起来是单减的，分母是单增的，所以总体就是单减的。

所以该函数切线斜率随 $x$ 增大而减小，是凸函数。

（不会求导，现去求导软件上扒拉的/kk。）

既然是凸的，直接三分即可。

Code：
```cpp
#include<bits/stdc++.h>
#define F(i,a,b) for(int i(a),i##end(b);i<=i##end;i++)
#define gc getchar
using namespace std;typedef long double db;
int read() {
	int s=0;char c=gc(),w=0;
	while(c<'0'||c>'9') w|=c=='-',c=gc();
	while(c>='0'&&c<='9') s=s*10+(c^48),c=gc();
	return w?-s:s;
} const db eps=1e-13;
db n,m,p,q;
db check(db x) {return (x+m)/(1-pow(1-p,x));}
int main() {
	F(T,1,read()) {
		n=read();m=(db)read()/n;p=(db)read()/10000;q=1-p;
		int L=1,R=1e9,mid;
		while(L<=R) {
			mid=L+R>>1;
			if(L+10>=R) break;
			if(check(mid)<check(mid+1)) R=mid+1;
			else L=mid;
		} db ans=1e20;
		F(i,L,R) ans=min(ans,check(i));
		printf("%.10Lf\n",ans*n);
	}
	return 0;
}
```

---

## 作者：ccg12345 (赞：1)

## 思路

令 $x = 1 - p$，我们先证明一个简单的引理：最优的情况必然是重复做 $t$ 个烟花并测试。

$prove$：假设我们的最优解是在先做 $t$ 个烟花后测试取得，并且还没有一个完美的，那么就相当于回到了初始状态，最优解必定是再做 $t$ 个烟花并测试，以此类推。

由题意，一个烟花制作失败的概率为 $x$，那么易得成功 $t$ 个的概率为 $1 - x^t$，又有花费的时间为 $m + t \times n$，这是一个几何分布，那么 $f(t) = \frac{m + t \times n}{1 - x^t}$，求个导 $f'(t) = \frac{n \times (1 - x^t) + (m + t \times n) \times (1 - x^t) \times \ln{t}}{(1 - x^t)^2}$（如果有误请指出），简单化简之后发现 $f(t)$ 为单峰函数，那么直接三分即可。

[代码](https://www.luogu.com.cn/paste/8rne7ij1)

---

## 作者：SDLTF_凌亭风 (赞：1)

式子写出来，题就很显然。

考虑在做了 $x$ 个烟花后放掉是最优的，如果放掉之后再也没有好烟花放了，那么状态可以看做回到了起始位置，那也还得做 $x$ 个烟花。所以每一次做烟花的数是固定的。

那么就假设你做了 $x$ 个烟花，然后把他们全部放掉。

根据题意，花费的时间为 $xn+m$，每轮好烟花的概率为 $1-(1-p)^x$。

高中数学选修三告诉我们，这是一个几何分布，则他的期望时间 $T$ 为：

$$
T=\dfrac{xn+m}{1-(1-p)^x}
$$

导一下发现这是个单峰函数，那么直接三分就可以得到答案。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
double n, m, p;
inline double qp(double a, int b) { double ans = 1; for(; b; a *= a, b >>= 1) if(b & 1) ans *= a; return ans; }
inline double f(int k) { double t = 1.0 - qp(1.0 - p, k); return (!t) ? (double)0x3f3f3f3f : (k * n * 1.0 + m) / t; }
int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	int T, mid1, mid2; cin >> T;
	for(double f1, f2; T; -- T) {
		cin >> n >> m >> p, p *= 1e-4;
		int l = 1, r = 0x3f3f3f3f; double res = (double)0x3f3f3f3f3f3f3f3f;
		while(r > l) mid1 = l + (r - l) / 3, mid2 = r - (r - l) / 3, f1 = f(mid1), f2 = f(mid2), res = min(res, min(f1, f2)), (f1 < f2) ? (r = mid2 - 1) : (l = mid1 + 1); 
		cout << fixed << setprecision(10) << res << endl;
	}
}
```

---

## 作者：hellolin (赞：0)


# P9627 [ICPC2020 Nanjing R] Fireworks 题解

建议前往 [note.hellolin.cf](https://note.hellolin.cf/solutions/p9627/) 获得更好的阅读体验！

不难看出一个结论，最佳决策一定是我做了 $a$ 个烟花后测试一波（此时没有烟花放了是吧，我们可以认为回到了一开始一个烟花都没做），再做了 $a$ 个烟花再测试一波，以此类推。

这个时候我们考虑，一个烟花失败的概率是 $1-p$，那么一个烟花成功的概率是 $1-(1-p)$，$a$ 个烟花成功的概率是 $1-(1-p)^a$。

再考虑一下，做 $a$ 的烟花所需的时间（包括测试）是 $m+an$，综合一下我们可以列出一个计算期望时间的函数：

$$
f(a)=\dfrac{m+an}{1-(1-p)^a}
$$

这个问题就转化成了求 $f(a)$ 的最小值（$a\in \N_+$），很显然这是单调的对吧（因为你做越多烟花时间肯定越多），直接快乐二分。

``` cpp
using ll = long long;
using ld = long double;

constexpr static ll N = 2e9 + 11;
constexpr static ld Eps = 1e-7;
ll T, n, m, l, r;
ld p;

void solve() {
    std::cout << std::fixed << std::setprecision(10);
    auto calc = [&](ll x) {
        return ((ld)m + (ld)x * n) / ((ld)1.0 - fpow((ld)1.0 - p, x));
    }; // 计算期望时间的函数，就是上文中的 f(a)
    for(std::cin >> T; T--; [&](){
        std::cin >> n >> m >> p;
        p *= 1e-4; // 注意输进来的 p 要乘 1e-4
        l = 0, r = N;
        while(l < r) {
            ll mid = (l + r) >> 1;
            if (calc(mid + 1) - calc(mid) < Eps)
                l = mid + 1;
            else
                r = mid;
        }
        std::cout << calc(l) << nl; // 注意是左端点
    }());
}
```

---

