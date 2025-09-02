# [ABC333F] Bomb Game 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc333/tasks/abc333_f

$ N $ 人の人が一列に並んでおり、人 $ i $ は先頭から $ i $ 番目に並んでいます。

以下の操作を、列に並んでいる人が $ 1 $ 人になるまで繰り返します。

- 先頭に並んでいる人を $ \frac{1}{2} $ の確率で列から取り除き、そうでない場合は列の末尾に移す。
 
人 $ i=1,2,\ldots,N $ それぞれについて、人 $ i $ が最後まで列に並んでいる $ 1 $ 人になる確率を $ \text{mod\ }998244353 $ で求めて下さい。(取り除くかどうかの選択はすべてランダムかつ独立です。)

  確率 $ \text{mod\ }\ 998244353 $ の定義この問題で求める確率は必ず有理数になることが証明できます。 また、この問題の制約下では、求める確率を既約分数 $ \frac{y}{x} $ で表したときに $ x $ が $ 998244353 $ で割り切れないことが保証されます。

このとき $ xz\ \equiv\ y\ \pmod{998244353} $ を満たすような $ 0 $ 以上 $ 998244352 $ 以下の整数 $ z $ が一意に定まります。この $ z $ を答えてください。

## 说明/提示

### 制約

- $ 2\leq\ N\leq\ 3000 $
- 入力は全て整数
 
### Sample Explanation 1

人 $ 1 $ が最後まで列に並んでいる $ 1 $ 人になる確率は $ \frac{1}{3} $ です。 人 $ 2 $ が最後まで列に並んでいる $ 1 $ 人になる確率は $ \frac{2}{3} $ です。

## 样例 #1

### 输入

```
2```

### 输出

```
332748118 665496236```

## 样例 #2

### 输入

```
5```

### 输出

```
235530465 792768557 258531487 238597268 471060930```

# 题解

## 作者：rui_er (赞：18)

来个可能有点麻烦但不用动脑子的暴力做法。

直接设 $f_{i,j}$ 表示有 $i$ 个人时，第 $j$ 个人幸存的概率。

显然有 $f_{1,1}=1$。

对于 $i > 1$，分类讨论容易得到：

$$
f_{i,j}=
\begin{cases}
\frac{f_{i,i}}{2},&j = 1\\
\frac{f_{i-1,j-1}+f_{i,j-1}}{2},&1 < j\le i\\
\end{cases}
$$

但是转移成环，无法通过正常方式转移。我们设 $f_{i,1}=x$，然后根据 $f_{i,j}=\frac{f_{i-1,j-1}+f_{i,j-1}}{2}$ 将所有 $f_{i,j}$ 用 $x$ 和常数表示出来，最后根据 $f_{i,1}=\frac{f_{i,i}}{2}$ 即可解得 $x$ 的具体值，再重新把所有 $f_{i,j}$ 算出来即可。

时间复杂度 $O(n^2)$。

```cpp
// Problem: F - Bomb Game 2
// Contest: AtCoder - Toyota Programming Contest 2023#8（AtCoder Beginner Contest 333）
// URL: https://atcoder.jp/contests/abc333/tasks/abc333_f
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x, y, z) for(int x = (y); x <= (z); ++x)
#define per(x, y, z) for(int x = (y); x >= (z); --x)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do {freopen(s".in", "r", stdin); freopen(s".out", "w", stdout);} while(false)
#define endl '\n'
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
    uniform_int_distribution<int> dist(L, R);
    return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

template<int mod>
inline unsigned int down(unsigned int x) {
	return x >= mod ? x - mod : x;
}

template<int mod>
struct Modint {
	unsigned int x;
	Modint() = default;
	Modint(unsigned int x) : x(x) {}
	friend istream& operator>>(istream& in, Modint& a) {return in >> a.x;}
	friend ostream& operator<<(ostream& out, Modint a) {return out << a.x;}
	friend Modint operator+(Modint a, Modint b) {return down<mod>(a.x + b.x);}
	friend Modint operator-(Modint a, Modint b) {return down<mod>(a.x - b.x + mod);}
	friend Modint operator*(Modint a, Modint b) {return 1ULL * a.x * b.x % mod;}
	friend Modint operator/(Modint a, Modint b) {return a * ~b;}
	friend Modint operator^(Modint a, int b) {Modint ans = 1; for(; b; b >>= 1, a *= a) if(b & 1) ans *= a; return ans;}
	friend Modint operator~(Modint a) {return a ^ (mod - 2);}
	friend Modint operator-(Modint a) {return down<mod>(mod - a.x);}
	friend Modint& operator+=(Modint& a, Modint b) {return a = a + b;}
	friend Modint& operator-=(Modint& a, Modint b) {return a = a - b;}
	friend Modint& operator*=(Modint& a, Modint b) {return a = a * b;}
	friend Modint& operator/=(Modint& a, Modint b) {return a = a / b;}
	friend Modint& operator^=(Modint& a, int b) {return a = a ^ b;}
	friend Modint& operator++(Modint& a) {return a += 1;}
	friend Modint operator++(Modint& a, int) {Modint x = a; a += 1; return x;}
	friend Modint& operator--(Modint& a) {return a -= 1;}
	friend Modint operator--(Modint& a, int) {Modint x = a; a -= 1; return x;}
	friend bool operator==(Modint a, Modint b) {return a.x == b.x;}
	friend bool operator!=(Modint a, Modint b) {return !(a == b);}
};

typedef Modint<998244353> mint;

const int N = 3e3 + 5, inv2 = 998244354 / 2;

int n;
mint dp[N][N];

struct Complex {
    mint real, imag;
    Complex(mint r = 0, mint i = 0) : real(r), imag(i) {}
    friend istream& operator>>(istream& in, Complex& a) {return in >> a.real >> a.imag;}
    friend ostream& operator<<(ostream& out, Complex a) {return out << a.real << " " << a.imag;}
    friend Complex operator+(Complex a, Complex b) {return Complex(a.real + b.real, a.imag + b.imag);}
    friend Complex& operator+=(Complex& a, Complex b) {return a = a + b;}
    friend Complex operator*(Complex a, mint b) {return Complex(a.real * b, a.imag * b);}
}tmp[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    dp[1][1] = 1;
    rep(i, 2, n) {
        tmp[1] = Complex(0, 1);
        rep(j, 2, i) tmp[j] = (dp[i - 1][j - 1] + tmp[j - 1]) * inv2;
        mint mul = tmp[i].real / (2 - tmp[i].imag);
        rep(j, 1, i) dp[i][j] = tmp[j].real + tmp[j].imag * mul;
    }
    rep(j, 1, n) cout << dp[n][j] << " \n"[j == n];
    return 0;
}
```

---

## 作者：2huk (赞：16)

# F - Bomb Game 2

## Description

有 $n$ 个人排成一排。你需要进行若干次操作，直到只剩下一个人：

- 有 $\dfrac 12$ 的概率，将第一个人刀了；
- 有 $\dfrac 12$ 的概率，把第一个人挪到最后，其余人的位置向前移。

对于每个 $1 \le i \le n$，求出第 $i$ 个人最终活下来的概率。

## Solution

设 $f_{i, j}$ 表示如果总共有 $i$ 个人，第 $j$ 个人最后活下来的概率。那么转移显然：
$$
f_{i, j} = \left\{\begin{matrix} \dfrac 12 f_{i, i} & (j = 1)\\\dfrac 12(f_{i, j - 1} + f_{i - 1, j - 1})  & (j \ne 1)\end{matrix}\right.
$$
那么第 $i$ 个人最终活下来的概率即为 $f_{n, i}$。

发现转移是有环的。因此考虑解决这个问题。我们可以把 $f_{i, 1}$ 拆开：
$$
\begin{aligned} f_{i, 1} &= \dfrac 12 f_{i, i} \\ &= \dfrac 12 \cdot\dfrac 12(f_{i, i - 1} + f_{i - 1, i - 1}) \\ &= \dfrac 12 \cdot\dfrac 12\left[\dfrac 12(f_{i, i - 2} + f_{i - 1, i - 2}) + f_{i - 1, i - 1}\right] \\ &= \dfrac 12 \cdot\dfrac 12 \left\{ \dfrac 12 \left[ \dfrac 12 (f_{i, i - 3} + f_{i - 1, i - 3}) + f_{i - 1, i - 2}\right] + f_{i - 1, i - 1} \right\} \\ &= \dots \end{aligned}
$$
这样就可以得到一个一元一次方程。即：
$$
2^{-i}f_{i, 1} + \sum_{j = 1}^{i - 1} 2^{j - i -  1}f_{i - 1, j} = f_{i, 1}
$$
移项可得：
$$
f_{i, 1} = \dfrac {\sum_{j = 1}^{i - 1} 2^{j - i - 1}f_{i - 1, j}}{2^{-i} - 1}
$$
然后就无环了，直接转移即可。

## Code

<https://www.luogu.com.cn/paste/rvrlflnu>。

---

## 作者：NaCly_Fish (赞：12)

[题目链接](https://www.luogu.com.cn/problem/AT_abc333_f)

大家平安夜快乐！  
过了这么久都没人愿意写一下，那就由我来干这活吧。

下文中，将「一个人在队头尝试被出局或继续」的过程称为「抛硬币」。
****
### 算法 1

设 $f_{n,k}$ 是有 $n$ 个人的情况下，编号为 $k$ 的人的胜利概率（从 $0$ 开始编号）。考虑让游戏进行到编号为 $k$ 的人即将抛硬币时，这样就能简单地将 $f_{n,k}$ 从 $f_{n-i,0}$ 推过来：

$$f_{n,k}=\frac{1}{2^k}\sum_{i=0}^k\binom kif_{n-i,0}$$

这个式子的意义很明显，编号为 $k$ 的人前面还有 $k$ 个。枚举有多少人出局即可。注意，前面 $k$ 个人是否出局都要确定下来，也就是有 $2^{-k}$ 的概率。

然后就是考虑 $f_{n,0}$ 的递推，显然 $f_{n,0}=f_{n,n-1}/2$，也就是：

$$f_{n,0}=\frac {1}{2^n}\sum_{i=0}^{n-1}\binom{n-1}{i}f_{n-i,0}$$
下面为方便表示设 $g_n=f_{n,0}$：
$$g_n=\frac{1}{2^n-1}\sum_{i=1}^{n-1}\binom{n-1}{i}g_{n-i}$$
朴素地递推就能通过此题，也可以考虑用分治 FFT 求出 $g_1,\cdots,g_n$，然后再一次卷积就能求出答案了。不过这样似乎只能做到 $\Theta(n \log^2 n)$ 的时间复杂度。即使考虑写为生成函数形式：
$$G(x)=\sum_{i\geq 1} \frac{g_i x^i}{(i-1)!}$$
也只能得到 $G(2x)=\text e^xG(x)+x$ 这样的方程。牛顿迭代似乎是处理不了的，也没听说过有其它的方式，只能考虑另寻出路了。


update：[飞雨烟雁](https://www.luogu.com.cn/user/375984) 提示到，等式两边同乘 $\text e^{-2x}$，可以得到

$$\text e^{-2x}G(2x)=\text e^{-x}G(x)+x\text e^{-2x}$$
设 $H(x)=\text e^{-x}G(x)$，则 $H(x)$ 的系数是很容易计算的，再用一次卷积即可求出 $G(x)$。

进一步的做法可以参见 [他的 blog](https://www.luogu.com.cn/blog/Fly37510/FcFPQ-solve)。
****
### 算法 2

~~刚才看到了朴素列式子然后推导的局限性，我们可以稍微转换一下思路~~。  
此做法有参考 AtCoder 上的[题解](https://atcoder.jp/contests/abc333/editorial/8001)。

如果有人挂掉但是不出局，只是继续当游戏搭子的话，可以发现这样并不影响答案，还可以保证人数固定在 $n$ 个，这是方便处理的 —— 现在可以让只剩最后一人时游戏不结束，只有在所有人都挂掉才结束，胜者是最后挂掉的人。

现在考虑第 $i$ （为了与题解保持一致，这里从 $1$ 开始编号）个人在经历了第 $k$ 次抛硬币后就获胜的概率。这需要：

- 他本人在 $k-1$ 次中都存活，在最后一次挂掉，概率为 $2^{-k}$；  
- 他前面的人在 $k$ 次中未都存活，每个人的概率为 $(1-2^{-k})$，合起来是 $(1-2^{-k})^{i-1}$；  
- 他后面的人在 $k-1$ 次中未都存活，总概率为 $(1-2^{1-k})^{n-i}$。

也就是说，设
$$p_{i,k}=2^{-k}(1-2^{-k})^{i-1}(1-2^{1-k})^{n-i}$$
则第 $i$ 个人最终胜利的概率 $a_i$ 就是 $\sum_{k\geq 1}p_{i,k}$。为了方便计算这个东西，设多项式
$$f_i(x)=x(1-x)^{i-1}(1-2x)^{n-i}$$
就有
$$a_i=\sum_{k=1}^\infty f_i(2^{-k})=\sum_{j=1}^n\frac{2^{-j}[x^j]f_i(x)}{1-2^{-j}}$$
有一种简单的处理方法，设
$$G(x)=\sum_{j=1}^n \frac{2^{-j}}{1-2^{-j}}x^{n-j}$$
这样 $a_i$ 就可以表示为 $[x^n]G(x)f_i(x)$，这是 [经典问题](https://www.luogu.com.cn/blog/NaCly-Fish-blog/a-classical-problem)，可以容易地做到 $\Theta(n \log n)$ 的时间复杂度。

参考代码：[Link](https://atcoder.jp/contests/abc333/submissions/48617288)

****

迷思：是否有可能做到 $\Theta(n)$ 的时间复杂度呢？这个问题的难点在于 $G(x)$ 不是微分有限的，它的系数只满足 q-整式递推，计算 $G(x+c)$ 目前似乎还都没有 $\Theta(n)$ 的做法，想要进一步优化还是挺难的。

如果有人会优化的话，还请跟我讲一下。

---

## 作者：Phartial (赞：10)

注意到下标是没有影响的，我们关心的只有位置。

考虑设 $f_{i,j}$ 表示一共有 $i$ 个人时第 $j$ 个人最终存活下来的概率。

那么我们考虑第一个人是寄了还是被换到了后面，有转移方程：

$$
f_{i,j}=\begin{cases}\frac{1}{2}f_{i,i} & j=1\\ \frac{1}{2}(f_{i,j-1}+f_{i-1,j-1}) & j>1\end{cases}
$$

考虑将 $f_{i,j}$ 表示成 $k_{i,j}f_{i,1}+b_{i,j}$ 的形式，对 $j>1$，有：

$$
\begin{aligned}
f_{i,j}
&=\frac{1}{2}(f_{i,j-1}+f_{i-1,j-1})\\
&=\frac{1}{2}(k_{i,j-1}f_{i,1}+b_{i,j-1}+f_{i-1,j-1})\\
&=\frac{1}{2}k_{i,j-1}f_{i,1}+\frac{1}{2}(b_{i,j-1}+f_{i-1,j-1})\\
\end{aligned}
$$

于是有递推关系 $k_{i,j}=\frac{1}{2}k_{i,j-1},b_{i,j}=\frac{1}{2}(b_{i,j-1}+f_{i-1,j-1})$，且 $k_{i,1}=1,b_{i,1}=0$，使用该式递推即可。

求出 $k_{i,i}$ 和 $b_{i,i}$ 后，有：

$$
\begin{aligned}
f_{i,1}
&=\frac{1}{2}f_{i,i}\\
&=\frac{1}{2}k_{i,i}f_{i,1}+\frac{1}{2}b_{i,i}
\end{aligned}
$$

解得 $f_{i,1}=\dfrac{b_{i,i}}{2-k_{i,i}}$，进一步的可以递推出 $f_{i,j}$。于是我们就在 $\mathcal{O}(N^2)$ 的时间复杂度内解决了此题。

```cpp
#include <atcoder/all>
#include <iostream>

using namespace std;
using LL = atcoder::modint998244353;

const int kN = 3001;
const LL i2 = LL(2).inv();

int n;
LL f[kN][kN];

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  f[1][1] = 1;
  for (int i = 2; i <= n; ++i) {
    LL k = 1, b = 0;
    for (int j = 2; j <= i; ++j) {
      k = i2 * k;
      b = i2 * (b + f[i - 1][j - 1]);
    }
    f[i][1] = b / (2 - k);
    for (int j = 2; j <= i; ++j) {
      f[i][j] = i2 * (f[i][j - 1] + f[i - 1][j - 1]);
    }
  }
  for (int i = 1; i <= n; ++i) {
    cout << f[n][i].val() << ' ';
  }
  return 0;
}
```

---

## 作者：Uuuuuur_ (赞：5)

这是一道很典的消元类概率 dp 啊。（虽然我第一次做，但算法早已耳闻）

题意：一个队列有 $N$ 个人，按顺序编号，每次有 $\frac{1}{2}$ 概率将队首扔掉，或者把他移到队末，重复操作，知道只剩下一个，求每个人留在队中的概率。

一看数据范围，很好，直接令 $f[i][j]$ 为还剩 $i$ 个人，排第 $j$ 位的人留在队中的概率。

我们尝试推一下转移方程，初状态 $f[1][1]=1$。从 $1$ 开始，他只有二分之一概率到最后面，所以 $f[i][1]= \frac{1}{2}f[i][i]$，这个有点奇怪，有后效性了，我们先留着，因为也只能推到这个地步了。

再看一般情况，有概率队首扔掉，也有概率队首移到最后面，$f[i][j]=\frac{1}{2}f[i-1][j-1]+\frac{1}{2}f[i][j-1]$，这个方程很友好，不过这不就意味着在同一个 $i$ 维时，要从前往后推吗？那 $f[i][1]$ 怎么办？

这时候，我们发现可以将一般式中的 $f[i][j-1]$ 展开成 $f[i-1][j-2]+f[i][j-2]$，这样不断展开，对于 $f[i][j]$，必定只留下 $f[i][1]$，其他都是已计算出的常量。

令 $f[i][i]=Kf[i][1]+B$，结合 $f[i][1]= \frac{1}{2}f[i][i]$，我们能够将 $f[i][1]$ **算出来**，然后再往后递推。


算我就不算了，式子十分好推。**注意逆元处理**。

这种消元法在涉及概率的动态规划中有很大的应用。处理有后效性的方程，遇到复杂情况，还能用高斯消元。

```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e3 + 5;
multiset<int> s;
const ll mod = 998244353;
ll pow_mod(ll a, ll b) {
	ll res = 1;
	while (b) {
		
		if (b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}
ll f[N][N];
ll add(ll a, ll b) {
	return ((a + b) % mod + mod) % mod;
}
ll mult(ll a, ll b) {
	return ((a % mod * b % mod) % mod + mod) % mod;
}
ll get_inv(ll x) {
	
	return pow_mod(x, mod - 2);
}
ll inv[N];
int n;
int main() {
	cin >> n;
	f[1][1] = 1;
	for (int i = 1; i <= 1000; i++) inv[i] = get_inv(i);
	for (int i = 2; i <= n; i++) {
		ll k = 1, b = 0;
		for (int j = 2; j <= i; j++) {
			k = mult(k, inv[2]);
			b = add(mult(b, inv[2]), mult(inv[2], f[i - 1][j - 1]));
		}
		
		f[i][1] = mult(get_inv(add(2, -k)), b);
		for (int j = 2; j <= i; j++) {
			f[i][j] = add(mult(inv[2], f[i - 1][j - 1]), mult(inv[2], f[i][j - 1]));
		}
	}
	for (int i = 1; i <= n; i++) cout << f[n][i] << ' ';
	return 0;
}
```


---

## 作者：CodingShark (赞：4)

一眼 dp 题。设 $f(i, j)$ 为还剩 $i$ 个人，从前往后第 $j$ 个人获胜的概率。边界条件 $f(1, 1)=1$，转移如下：

$$
f(i, 1) = \frac12 f(i, i)
$$

$$
f(i, j) = \frac12 [f(i-1, j-1) + f(i, j-1)] \quad (2 \le j \le i)
$$

由于同一层的转移是前后依赖的，将第 $i$ 层的转移视作解一个 $i$ 元一次方程来做。这里我是将 $f(i, i)$ 的式子展开，得到：

$$
f(i, i) = \Big(\sum_{k=1}^{i-1} \frac{1}{2^{i-k}} f(i-1,k)\Big) + \frac{1}{2^{i-1}}f(i, 1)
$$

$$
f(i, i) = \frac{2^i}{2^i-1}\Big(\sum_{k=1}^{i-1} \frac{1}{2^{i-k}} f(i-1,k)\Big)
$$

接着算出 $f(i, 1)$，再利用递推式将 $f(i, 2\sim i-1)$ 全部算出来即可。

时间复杂度 $O(n^2)$，空间复杂度 $O(n)$（滚动数组）。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=3005, M=998244353, inv2=499122177;
ll n, f[N][N], pow2[N];
ll qpow(ll x, ll y){
	ll res = 1;
	while (y){
		if (y & 1) res = res * x % M;
		x = x * x % M, y >>= 1;
	} return res;
}
int main(){
	cin >> n;
	pow2[0] = 1;
	for (int i = 1; i <= n; i++) pow2[i] = pow2[i-1] * inv2 % M;
	f[1][1] = 1;
	for (int i = 2; i <= n; i++){
		for (int j = 1; j <= i; j++) f[i&1][j] = 0;
		for (int j = 1; j < i; j++)
			(f[i&1][i] += (f[(i-1)&1][j] * pow2[i-j]) % M) %= M;
		f[i&1][i] = f[i&1][i] * qpow(2, i) % M * qpow(qpow(2, i) - 1, M - 2) % M;
		f[i&1][1] = f[i&1][i] * inv2 % M;
		for (int j = 2; j < i; j++)
			f[i&1][j] = (f[(i-1)&1][j-1] + f[i&1][j-1]) * inv2 % M;
	}
	for (int i = 1; i <= n; i++) cout << f[n&1][i] << " ";
	return 0;
} // qwq
```

---

## 作者：_Cheems (赞：1)

题意：有 $n$ 个人，每次 $\frac 12$ 的概率刀了最左边的人，还活着就移到最右边。重复下去直到只剩一人，对每个 $i$ 求 $i$ 最终存活的概率。$n\le 3\times 10^3$。

显然有 dp，设 $f_{i,j}$ 为有 $i$ 个人时第 $j$ 个人存活的概率，转移分讨第一个人存活：

* $f_{i,j}\gets \frac 12f_{i-1,j-1}$。
* $f_{i,j}\gets \frac 12f_{i,(j-1)\bmod i}$。

把转移画出来，形如一个金字塔，答案就是最下层的点走到塔顶的乘积和（边权都是 $\frac 12$）：

![](https://cdn.luogu.com.cn/upload/image_hosting/nnf07ipe.png)

考虑路径形如：从最底层起点开始绕若干圈、在某个点停下来、走到上面一层，以此类推。所以把答案拆成两部分：不能走重复点的路径、在每一层原地转圈圈的路径。两者相乘即为答案。

对于前者，转移无环可以暴力转移做到 $O(n^3)$，做前后缀和状物优化一下就是 $O(n^2)$ 了。对于后者，显然每一层可以独立算再乘起来，每一层答案用等比数列求和即可计算，$O(n)$。

转移比较简单，可以看代码。
#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define ADD(a, b) a = (a + b) % mod
const int N = 3e3 + 5, mod = 998244353, inv2 = 499122177;
int n, f[N][N], pw[N], h[N];

inline int qstp(int a, int k) {int res = 1; for(; k; a = a * a % mod, k >>= 1) if(k & 1) res = res * a % mod; return res;}
signed main(){
    pw[0] = 1;
    for(int i = 1; i < N; ++i) pw[i] = pw[i - 1] * inv2 % mod;
    cin >> n;
    f[1][1] = h[1] = 1;
    for(int i = 2; i <= n; ++i){
        for(int j = 1, ps = 0; j <= i; ++j){
            ps = (ps * inv2 % mod + f[i - 1][j - 1]) % mod;
            ADD(f[i][j], inv2 * ps % mod);
        }
        for(int j = i, ns = 0; j; --j){
            ns = (ns * 2ll % mod) % mod;
            ADD(f[i][j], pw[1 + i] * ns % mod);
            ADD(ns, f[i - 1][j - 1]);
        }
        h[i] = qstp(1 - pw[i] + mod, mod - 2) % mod * h[i - 1] % mod; 
    }
    for(int i = 1; i <= n; ++i) printf("%lld ", f[n][i] * h[n] % mod);
    return 0;
}
```

---

## 作者：maxyzfj (赞：1)

### 题意简述

有 $n$ 个人站成一列，每次把这个队伍的队首从队伍中移出或移到队尾（两种情况发生的概率均为 $\dfrac{1}{2}$），直到队伍中只剩一个人。求每个人成为最终剩下的那个人的概率。

### 解题思路

最初的思路是令 $f[i][j]$ 表示总共有 $j$ 个人时从前往后第 $i$ 个人成为队伍中最后一个人的概率，然后进行 dp 或消元，求解出 $f[1][n],f[2][n],\cdots,f[n][n]$。

于是我们来推式子：

在总共有 $j$ 个人时（假设总人数小于 $j$ 时的答案已被求出）：

- 第一个人有 $\dfrac{1}{2}$ 的概率一开始就被移出队伍，还有 $\dfrac{1}{2}$ 的概率被移到队尾，因此他成为队伍中最后一个人的概率 $f[1][j]=\dfrac{1}{2}f[j][j]$。

- 至于第 $i$ 个人（$i\not=1$）的情况，设当他第一次成为队首的时候，队伍中总共还剩 $t$ 个人的概率为 $p[i][t]$，那么他成为最后剩下的人的概率 $f[i][j]=\sum\limits_{t=j-i+1}^{j}(p[i][t]\times f[1][t])$。接下来考虑计算 $p[i][t]$。我们注意到，当第 $i$ 个人第一次成为队首时，他前面的 $i-1$ 个人的去留情况总共有 $2^{i-1}$ 种（即每个人是从队伍中移出还是留在队伍中），而其中恰好有 $k$ 个人被删除的情况为 $C_{i-1}^k$ 种，于是 $p[i][t]=\dfrac{C_{i-1}^{j-t}}{2^{i-1}}$，因此 $f[i][j]=\sum\limits_{t=j-i+1}^{j}(\dfrac{C_{i-1}^{j-t}\times f[1][t]}{2^{i-1}})$

- 特别地，最初队尾那个人成为最后剩下的人的概率 $\begin{aligned}f[j][j] & = \sum\limits_{t=1}^{j}(\dfrac{C_{j-1}^{j-t}\times f[1][t]}{2^{j-1}}) \\ & =\sum\limits_{t=1}^{j-1}(\dfrac{C_{j-1}^{t-1}\times f[1][t]}{2^{j-1}})+\dfrac{f[1][j]}{2^{j-1}}  \\ & =\sum\limits_{t=1}^{j-1}(\dfrac{C_{j-1}^{t-1}\times f[1][t]}{2^{j-1}})+\dfrac{f[j][j]}{2^{j}} \end{aligned}$

- 注意到上面这个式子是一个关于 $f[j][j]$ 的一元一次方程，于是可以把 $f[j][j]$ 解出，从而求出 $f[1][j]$；我们还注意到，为了推到总共 $j+1$ 个人的情况时，只需要知道 $f[1][1],f[1][2],\cdots,f[1][j]$ 的值，因此对于任何的 $i\not= 1$ 且 $j\not=n$，我们不需要求出 $f[i][j]$ 的值。

综上，我们可以以 $O(n^2)$ 的复杂度求出 $f[1][n]$ 以及 $f[n][n]$ 的值，然后以 $O(n^2)$ 的复杂度推出 $f[2][n],f[3][n],\cdots,f[n-1][n]$ 的值，总复杂度为 $O(n^2)$。

PS：本题的 $f$ 数组可以变为一维的，$f[j]$ 表示总共有 $j$ 个人时最初的队首成为队伍中最后一个人的概率，方法与上面相同。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
#define mp(x,y) make_pair(x,y)
#define lb(x) (x&(-x))
#define fi first
#define se second
#define pii pair<int,int>
int read(){
	int x=0,f=1;
    char ch=getchar();
	while(ch<'0'||ch>'9'){
    	if(ch=='-')f=-1;
		ch=getchar();
    }
	while(ch>='0'&&ch<='9'){
    	x=x*10+ch-48;
		ch=getchar();
    }
	return x*f;
}
void writ(int x){
    if(x<0){
		putchar('-'),x=-x;
	}
    if(x>9){
		writ(x/10);
	}
    putchar(x%10 +'0');
}
void write(int x,char p=' '){
    writ(x);
    putchar(p);
}
string sread(){
    string t="";
    char c=getchar();
    while(c==' '||c=='\t'||c=='\r'||c=='\n'||c==0||c==EOF){
        c=getchar();
    }
    while(!(c==' '||c=='\t'||c=='\r'||c=='\n'||c==0||c==EOF)){
        t+=c,c=getchar();
    }
    return t;
}
const int mod=998244353,inf=2e18+31,N=3005;
int cal(int a,int b=mod-2){
	int base=a,ret=1;
	while(b){
		if(b&1){
			ret=ret*base%mod;
		}
		base=base*base%mod;
		b>>=1;
	}
	return ret;
}
mt19937 rnd(time(0)^clock());
int n,f[N][N],c[N][N],inv[N]; //inv[i]表示2的i次方模998244353意义下的的逆元 
signed main(){
    n=read();
    c[0][0]=1;
    inv[0]=1;
    for(int i=1;i<=3000;i++){
	    c[i][0]=c[i][i]=1;
    	inv[i]=inv[i-1]*2%mod;
	    for(int j=1;j<i;j++){
	    	c[i][j]=c[i-1][j]+c[i-1][j-1];
	    	c[i][j]%=mod;
		}
	}
    for(int i=1;i<=3000;i++){
    	inv[i]=cal(inv[i]);
	}
	f[1][1]=1;
	for(int j=2;j<=n;j++){
		int num=0;
		for(int t=1;t<j;t++){
			num+=f[1][t]*c[j-1][t-1]%mod*inv[j-1]%mod;
			num%=mod;
		}
		int tt=(1-1*inv[j]+mod*3)%mod;
		f[j][j]=num*cal(tt)%mod;
		f[1][j]=f[j][j]*inv[1]%mod;
	}
	for(int i=2;i<n;i++){
		for(int t=0;t<i;t++){
			f[i][n]+=f[1][n-t]*c[i-1][t]%mod*inv[i-1]%mod;
			f[i][n]%=mod;
		}
	}
	for(int i=1;i<=n;i++){
		write(f[i][n]);
	}
	return 0;
}
```




---

