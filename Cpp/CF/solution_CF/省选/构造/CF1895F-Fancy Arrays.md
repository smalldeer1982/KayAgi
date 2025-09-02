# Fancy Arrays

## 题目描述

Let's call an array $ a $ of $ n $ non-negative integers fancy if the following conditions hold:

- at least one from the numbers $ x $ , $ x + 1 $ , ..., $ x+k-1 $ appears in the array;
- consecutive elements of the array differ by at most $ k $ (i.e. $ |a_i-a_{i-1}| \le k $ for each $ i \in [2, n] $ ).

You are given $ n $ , $ x $ and $ k $ . Your task is to calculate the number of fancy arrays of length $ n $ . Since the answer can be large, print it modulo $ 10^9+7 $ .

## 说明/提示

In the first test case of the example, the following arrays are fancy:

- $ [0, 0, 0] $ ;
- $ [0, 0, 1] $ ;
- $ [0, 1, 0] $ ;
- $ [0, 1, 1] $ ;
- $ [0, 1, 2] $ ;
- $ [1, 0, 0] $ ;
- $ [1, 0, 1] $ ;
- $ [1, 1, 0] $ ;
- $ [2, 1, 0] $ .

## 样例 #1

### 输入

```
4
3 0 1
1 4 25
4 7 2
1000000000 40 1000000000```

### 输出

```
9
25
582
514035484```

# 题解

## 作者：ka_da_Duck (赞：11)

题意就是让你求出有多少个长度为 $n$ 的数组，使得相邻两个数相差不超过 $k$，并且**至少**有一个数属于 $[x,x+k-1]$。

我们先看“并且至少有一个数属于 $[x,x+k-1]$”这一条件，需要满足这一条件，就需要同时满 $\max_{i=1}^na_i\ge x$ 且 $\min_{i=1}^{n}a_i\le x+k-1$。

用**容斥原理**转化一下，我们就可以，用 $\min_{i=1}^{n}a_i\le x+k-1$ 的方案总数减去 $\max_{i=1}^na_i\lt x$ 的方案总数。

#### (I) 看 $\min_{i=1}^{n}a_i\le x+k-1$ 的方案总数如何求

我们发现只要确定了 $\min_{i=1}^{n}a_i$ 和 $a$ 的差分数组 $c$，就可以**唯一确定**数组 $a$。

因为 $\min_{i=1}^{n}a_i$ 要小于等于 $x+k-1$ 这个区间中所以有 $x+k$ 中方案选择。因为 $\forall c_i$ 都需要在区间 $[-k,k]$ 中 $(c_i\le k)$，所以有 $2k+1$ 种选择，差分数组上有 $n-1$ 个位置，所以有 $(2k+1)^{n-1}$ 种选择。根据简单的配列组合知识，就可以得到第一部分的总方案数是 $(x+k)\times (2k+1)^{n-1}$。

#### (II) 看 $\max_{i=1}^na_i< x$ 的方案总数如何求

后者就是要求出 $\forall a_i\in [0,x)$ 的方案数。可以发现可以用 DP 求出。

令 $f_{i,j}$ 表示 $a_i=j$ 的总方案个数。可以得到转移方程 $f_{i,j}=\sum_{t=j-k}^{j+k}f_{i-1,t}$。但是题目 $n$ 的数据范围太大并且 $x$ 的范围很小。又发现 $f$ 的转移式恒定不变，考虑矩阵快速幂优化，具体方法如下：
 
定义初始一个 $1\times x$ 的矩阵 $\text{F}$ 以及一个 $x\times x$ 转移矩阵 $\text{G}$，其中 $\text{F}$ 的初始值都是 $1$，$\text{G}$ 的初始值若 $|i-j|\le k$ 则令 $G_{i,j}=1$，最后求 $n$ 次幂即可。

得到了两部分的答案，减一下就可以了，时间复杂度 $O(x^3\log_{2}n)$。

代码：
```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;
const int maxn = 40 + 5, mod = 1e9 + 7;

int n, x, k;

struct Matrix{
	int a[maxn][maxn];
	friend Matrix operator * (const Matrix &u, const Matrix &v) {
		Matrix res;
		memset(res.a, 0, sizeof res.a);
		for (int k = 1; k <= x; ++k) 
			for (int i = 1; i <= x; ++i) 
				for (int j = 1; j <= x; ++j) 
					res.a[i][j] = (res.a[i][j] + u.a[i][k] * v.a[k][j]) % mod;
		return res;
	}
} r1, r2;

int qpow(int a, int b) {
	int res = 1;
	while (b) {
		if  (b & 1) res = res * a % mod;
		b >>= 1, a = a * a % mod;
	}
	return res;
}

void mpow(int k) {
	while (k) {
		if (k & 1) r1 = r1 * r2; 
		r2 = r2 * r2, k >>= 1;
	}
}

void solve() {
	cin >> n >> x >> k;
	int ans = qpow(2 * k + 1, n - 1) * (x + k) % mod;
	for (int i = 1; i <= x; ++i) r1.a[1][i] = 1;
	for (int i = 1; i <= x; ++i) for (int j = 1; j <= x; ++j) r2.a[i][j] = (abs(i - j) <= k);
	mpow(n - 1);
	for (int i = 1; i <= x; ++i) ans = (ans - r1.a[1][i] + mod) % mod;
	cout << ans << '\n';
}

signed main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while (t--) solve();
}
```

---

## 作者：Lightwhite (赞：10)

[portal](http://codeforces.com/problemset/problem/1895/F)

题意：求存在多少个长度为 $n$ 的序列 $a$ 使相邻两数差不超过 $k$，且数列中存在至少一个数在区间 $[x, x + k - 1]$ 内。$1\leq n, k\leq 10^9, 0\leq x\leq 40$。


注意到假设我们确定了差分数组和最小值，就可以得到整个序列的具体值。这是显然的，因为差分数组可以前缀和回去得到所有元素和 $a_1$ 的差，又知道最小值就可以推出全部。同时，两个序列如果差分序列或最小值不同，两者显然不同。

于是我们可以试求 $\min\limits_{1\leq i\leq n}a_i \leq x+k-1$ 且 $|a_i-a_{i+1}|$ 的不同序列个数。发现存在 $(2k+1)^{n-1}$ 种不同的差分序列和 $x+k$ 种最小值满足条件。只需要再除去 $\max\limits_{1\leq i\leq n}a_i<x$ 的方案数即可。

发现这个东西很可 dp。由于序列中数的值域仅为 $[0, x)$，因此直接设 $f_{i, j}$ 表示当前在第 $i$ 位，且 $a_i = j$ 的方案数量，暴力转移实在不可接受。但是由于相邻两数差不超过 $k$ 是当前唯一的限制，直接矩阵快速幂优化即可。时间复杂度 $O(x^3\log n)$。


```cpp
// STOOOOOOOOOOOOOOOOOOOOOOOOO hzt CCCCCCCCCCCCCCCCCCCCCCCORZ
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;
using LL = long long;
using PII = pair<int, int>;
constexpr int kX = 40 + 1, kP = 1e9 + 7;

int T;
int n, x, k;

struct Mat {
  int a[kX][kX];
  Mat() { fill(a[0], a[x] + x + 1, 0); }
  Mat operator*(const Mat &o) const {
    Mat ret;
    for (int i = 0; i < x; i++) {
      for (int k = 0; k < x; k++) {
        for (int j = 0; j < x; j++) {
          ret.a[i][j] = (ret.a[i][j] + 1ll * a[i][k] * o.a[k][j]) % kP;
        }
      }
    }
    return ret;
  }
} a, ret;
int P(int a, int b) {
  int ret = 1;
  for (; b > 0; b /= 2) {
    if (b & 1) {
      ret = 1ll * ret * a % kP;
    }
    a = 1ll * a * a % kP;
  }
  return ret;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> T;
  while (T--) {
    cin >> n >> x >> k;
    int ans = 1ll * P(2 * k + 1, n - 1) * (x + k) % kP;
    for (int i = 0; i < x; i++) {
      for (int j = 0; j < x; j++) {
        a.a[i][j] = (abs(i - j) <= k);
      }
    }
    ret = Mat();
    int b = n - 1;
    for (int i = 0; i < x; i++) {
      ret.a[0][i] = 1;
    }
    for (; b > 0; b /= 2) {
      if (b & 1) {
        ret = ret * a;
      }
      a = a * a;
    }
    for (int i = 0; i < x; i++) {
      ans = (ans - ret.a[0][i] + kP) % kP;
    }
    cout << ans << '\n';
  }
  return 0;
}
```

---

## 作者：orz_z (赞：4)



考虑到 $x\le 40$，肯定是要从这上面考虑的。

我们把存在性容斥掉，答案为总情况数减去所有数在 $[0,x)$ 的情况数再减去所有数在 $(x+k-1,+\infty)$ 的情况。

考虑第一部分和第三部分一起看。

绝对值转成差分序列 $b$，那么 $b_i\in[-k,k]$，即只有 $2k+1$ 种取值。

而第一部分减去第三部分等价于原序列的最小值在 $[0,x+k-1]$。

则这种情况的方案数为 $(x+k)\times (2k+1)^{n-1}$。

剩下的部分就显而易见了。

设计 `dp`，设 $f_{i,j}$ 表示所有数在 $[0,x)$ 且相邻差 $\le k$ 的序列，第 $i$ 位为 $j$ 的方案数。

转移方式固定，矩阵乘法加速转移即可。

时间复杂度 $\mathcal O(x^3\log n)$。



---

## 作者：幽云蓝 (赞：3)

$x\le 40$ 的提示非常明显，尽管如此，推导最终答案的过程仍是十分有趣的。下面所设的变量等均与官方题解保持一致。

容易发现直接求出答案是困难的，转而尝试用所有方案减去所有不满足条件的方案。可以发现“所有方案”是难以定义的，因为本题并没有为 $a$ 数组设定上界。我们不妨人为的为 $a$ 设定一个上界，记其为 $M$。$M$ 需要大于等于 $x+k-1+k(n-1)$（也就是说，要包含所有合法的 $a$ 数组），为了方便，就设其为 $10^{100}$。

定义一个 $a$ 数组是合法的，当且仅当其相邻两数差的绝对值 $\le k$。注意，它不一定满足题目中的条件 $1$！

令 $f(l,r)$ 表示 $a$ 数组的上界为 $r$，下界为 $l$ 时合法的 $a$ 数组数量，可以推出本题答案等于 $f(0,M)-f(0,x-1)-f(x+k, M)$。容易通过矩阵快速幂求出 $f(0,x-1)$，那么问题就转化为求出 $f(0,M)-f(x+k,M)$。

记 $\Delta$ 数组为一个长度为 $n-1$ 的数组，满足 $\Delta_i=a_{i+1}-a_1$。可以发现如果确定了 $a_1$ 的值与 $\Delta$ 数组的值，那么就可以恰好映射到某个 $a$ 数组上。如果确定了 $\max\{\Delta\}$（记其为 $mx$）与 $\min\{\Delta\}$（记其为 $mn$），对于上下界 $l$ 和 $r$，合法的 $a_1$ 数量可以表示为 $\max(0, (r-l)-(mx-mn)+1)$。于是我们得到了一种通过枚举 $\Delta$ 数组来计算 $f(l,r)$ 的方式。

由于 $\Delta$ 数组并不受上下界的影响，我们不妨同时枚举 $\Delta$ 数组来计算 $f(0,M)-f(x+k,M)$ 的值。由于 $M$ 是极大的，我们在计算过程中可以拆去 $\max$：

$$f(0,M)-f(x+k,M)=\sum_{\Delta}(M-0-mx+mn+1)-(M-x-k-mx+mn+1)$$

将括号去掉，可以得到：

$$f(0,M)-f(x+k,M)=\sum_{\Delta}x+k$$

由于 $\Delta$ 数组的数量为 $(2k+1)^{n-1}$，容易计算得到 $f(0,M)-f(x+k,M)=(x+k)(2k+1)^{n-1}$。

于是本题在 $x^3\log n$ 的复杂度内得到解决。

---

## 作者：EuphoricStar (赞：2)

看到题目感觉很怪，没有什么很好的直接做的办法。于是考虑容斥，$\min a_i \le x + k - 1$ 的方案数减去 $\max a_i < x$ 的方案数即为答案。

前者的方案数是好算的。注意到只要确定了 $\min a_i$ 和差分数组 $a_i - a_{i - 1}$ 就能确定 $a_1$，所以 $\min a_i$ 和差分数组的方案相互独立，分别为 $x + k$ 和 $(2k + 1)^{n - 1}$，乘起来即可。

后者发现可以直接做一个 $O(nx)$ 的朴素 dp，设 $f_{i, j}$ 为 $a_i = j$ 的方案数即可。转移容易刻画成矩阵形式，矩阵快速幂优化，就变成 $O(x^3 \log n)$ 了。

时间复杂度 $O(T x^3 \log n)$。

[code](https://codeforces.com/contest/1895/submission/232845741)

说实话想到容斥就做完了，但是我没想到，乐。

---

## 作者：蒟蒻君HJT (赞：2)

存在 $[x,x+k-1]$ 中的数，由于 $x$ 很小，可以想到转化为存在 $[0,x+k-1]$ 中的数且不是所有数都在 $[0,x-1]$ 区间内。

对于前者，考虑先固定差分数组的值，有 $(2k+1)^{n-1}$ 种方案。这样一来，整个数组波动的“形状”就确定了。再注意到存在 $[0,x+k-1]$ 等价于最小值在 $[0,x+k-1]$ 因此最小值有 $x+k$ 种选择，总方案数为 $(x+k)\times (2k+1)^{n-1}$。

容斥掉所有数都在 $[0,x-1]$ 区间内的情况。这种情况每个数都取值都非常有限，容易想到 $\Theta(nV)$ 的做法，$V$ 是值域，即设状态为 $f_{i,j}$ 表示长为 $i$ 的数列，所有数都在 $[0,x-1]$ 中，相邻差不超过 $k$ 且 $a_i=j$ 的方案。发现可以矩阵加速转移。

时间复杂度 $\Theta(T(\log n+x^3))$。

[for reference only.](https://codeforces.com/contest/1895/submission/231264731)

---

## 作者：xiezheyuan (赞：1)

## 简要题意

给定参数 $x,k$，定义一个长度为 $n$ 的序列 $a$ 是好的，当且仅当满足下面所有条件：

- $a_i\in\mathbb{N}$。
- $\exist i\in[1,n],a_i\in[x,x+k-1]$。
- $\forall i\in[2,n],|a_i-a_{i-1}|\leq k$。

你需要计算好的序列数量，答案对 $10^9+7$ 取模。

$T$ 组数据。$1\leq n,k\leq 10^9,0\leq x\leq 40,1\leq T\leq 50$。

## 思路

### Part 1

首先最难考虑的限制就是 $\exist i\in[1,n],a_i\in[x,x+k-1]$，我们将其转换为两条限制：

- $\max a_i\geq x$。
- $\min a_i\leq x+k-1$。

容易发现，假如我们可以同时满足这两条限制，则等价于满足原本的第二条限制。

然后我们发现“同时”也是难以考虑到，不妨容斥。改为求满足第二个条件的数量，减去不满足第一个条件的数量。

### Part 2

> $\min a_i\leq x+k-1$。

考虑原本的第三条限制 $\forall i\in[2,n],|a_i-a_{i-1}|\leq k$，那么取 $b=\Delta a$ 即 $a$ 的差分数组，则 $b_i\in[-k,k]$。

考虑如何在差分数组上体现出 $\min$，意料之中的是 $\min$ 在差分数组中无法体现，并且 $\min$ 信息与差分数组是完全独立的，通过这两个信息可以还原 $a$（方法就是对 $\Delta a$ 求前缀和，选取最小值，然后加上 $\min$ 和前缀和最小值的差，并补充第一项）。

于是计数就非常简单了，最小值数量是 $|[0,x+k-1]|=x+k$，差分数组的数量是 $(|[-k,k]|)^{n-1}=(2k+1)^{n-1}$，于是这一部分的答案是：

$$
\boxed{(x+k)(2k+1)^{n-1}}
$$

这一部分时间复杂度 $O(T\log n)$，并不是本题的复杂度瓶颈。

### Part 3

> $\max a_i<x$。

最大值小于 $x$，差分数组的每一项位于 $[-k,k]$，求序列数量。这是经典的 dp 问题，设 $f(i,j)$ 表示前 $i$ 个数，最后一项为 $j$ 的方案数，不难有转移：

$$
\boxed{f(i,j)=[0\leq j<x]\sum_{t=j-k}^{j+k}f(i-1,t)}
$$

初值 $f(1,i)=[0\leq i<x]$ 表示第一个数没有特别的限制。

这个 dp 时间复杂度 $O(nx^2)$ 无法承受，不过这个转移是加法线性组合的形式，可以考虑矩阵快速幂优化，这是容易的。

时间复杂度 $O(Tx^3\log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1e9 + 7;
int Add(int x, int y){ return (x + y) >= mod ? (x + y - mod) : (x + y); }
int Sub(int x, int y){ return (x - y) < 0 ? (x - y + mod) : (x - y); }
int Mul(int x, int y){ return 1ll * x * y % mod; }

int fastpow(int x, int y){
    int ret = 1;
    for(;y;y>>=1,x=Mul(x, x)){ if(y & 1) ret = Mul(ret, x); }
    return ret;
}

int n, x, k;

struct matrix{
    int a[45][45], n, m;
    int* operator[](int i){ return a[i]; }
    matrix(){ memset(a, 0, sizeof(a)); }
};

matrix operator*(matrix a, matrix b){
    matrix ret; ret.n = a.n, ret.m = b.m;
    for(int i=0;i<a.n;i++){
        for(int k=0;k<a.m;k++){
            for(int j=0;j<b.m;j++) ret[i][j] = Add(ret[i][j], Mul(a[i][k], b[k][j]));
        }
    }
    return ret;
}

matrix fastpow(matrix a, int b){
    matrix ret; ret.n = ret.m = a.n;
    for(int i=0;i<a.n;i++) ret[i][i] = 1;
    while(b){
        if(b & 1) ret = ret * a;
        a = a * a, b >>= 1;
    }
    return ret;
}

void solve(){
    cin >> n >> x >> k;
    matrix mat; mat.n = mat.m = x;
    for(int i=0;i<x;i++){
        for(int j=max(i-k,0);j<=min(i+k,x);j++) mat[j][i] = 1;
    }
    matrix ret; ret.n = 1, ret.m = x;
    for(int i=0;i<x;i++) ret[0][i] = 1;
    ret = ret * fastpow(mat, n - 1);
    int ans = 0;
    for(int i=0;i<x;i++) ans = Add(ans, ret[0][i]);
    ans = Sub(Mul(fastpow(Add(Add(k, k), 1), n - 1), Add(x, k)), ans);
    cout << ans << '\n';
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int t; cin >> t;
    while(t--) solve();
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：Gold14526 (赞：1)

$\rm Problem:$[Fancy Arrays](https://www.luogu.com.cn/problem/CF1895F)

$\rm Difficulty:2600(CodeForces)$

### 题意

定义有至少一个数在区间 $[x,x+k-1]$ 内且相邻两个数的差的绝对值不超过 $k$ 的非负整数序列为 Fancy arrays。

现在给出 $n,x,k(1\le n,k \le 10^9,0\le x\le 40)$，求长度为 $n$ 的 Fancy arrays 的个数，对 $10^9+7$ 取模。

### 做法

我们定义“有至少一个数在区间 $[x,x+k-1]$ 内”为条件一，“相邻两个数的差的绝对值不超过 $k$”为条件二。

显然答案为序列最小值在 $[0,x+k-1]$ 内且满足条件二的序列个数，减去整个序列都在 $[0,x-1]$ 的序列个数。

考虑怎么算最小值在 $[0,x+k-1]$ 内且满足条件二的序列个数，即选择一个 $[0,x+k-1]$ 内的数作为最小值，显然是 $x+k$ 种选法，再求差分数组的个数，显然为 $(2k+1)^{n-1}$，所以这个数就是 $(x+k)(2k+1)^{n-1}$。

考虑怎么求整个序列都在 $[0,x-1]$ 的序列个数，显然可以 dp，设 $dp_{x,y}$ 为前 $x$ 个数以 $y$ 结尾的方案数，显然有转移方程 $dp_{i,j}=\sum_{t=i-k}^{i+k}dp_{i-1,t}$，但是 $n$ 太大了，考虑矩阵快速幂，具体的，初始矩阵为一个 $1\times x$ 的全 $1$ 矩阵，转移矩阵 $A$ 是一个 $x\times x$ 的矩阵，满足 $A_{i,j}=[|i-j|\le k]$。

然后减一下就是答案了。

### 代码
```cpp
#include<bits/stdc++.h>
#define cint const int
#define cmtx const matrix
using namespace std;
int num;
char ch;
int read()
{
	num=0;
	ch=getchar();
	while(ch<'0'||ch>'9')
	{
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		num=(num<<1)+(num<<3)+ch-'0';
		ch=getchar();
	}
	return num;
}
cint mod=1e9+7;
struct matrix{
	short n,m;
	int a[41][41];
}first,dp,emp;
int n,x,k;
matrix operator*(cmtx x,cmtx y)
{
	matrix z;
	z.n=x.n;
	z.m=y.m;
	for(short i=0;i<z.n;++i)
	{
		for(short j=0;j<z.m;++j)
		{
			z.a[i][j]=0;
			for(int k=0;k<x.m;++k)
			{
				z.a[i][j]=(1ll*x.a[i][k]*y.a[k][j]+z.a[i][j])%mod;
			}
		}
	}
	return z;
}
void init()
{
	emp.n=emp.m=x;
	for(int i=0;i<x;++i)
	{
		for(int j=0;j<x;++j)
		{
			emp.a[i][j]=(i==j);
		}
	}
	dp.n=dp.m=x;
	for(int i=0;i<x;++i)
	{
		for(int j=0;j<x;++j)
		{
			dp.a[i][j]=(j>=i-k&&j<=i+k);
		}
	}
	first.n=1;
	first.m=x;
	for(int i=0;i<x;++i)
	{
		first.a[0][i]=1;
	}
}
matrix mpow(cmtx a,cint b)
{
	if(b==0)return emp;
	matrix t=mpow(a,b>>1);
	if(b==b>>1<<1)return t*t;
	return t*t*a;
}
int qpow(cint a,cint b)
{
	if(b==0)return 1;
	int t=qpow(a,b>>1);
	if(b==b>>1<<1)return 1ll*t*t%mod;
	return 1ll*t*t%mod*a%mod;
}
void solve()
{
	n=read();
	x=read();
	k=read();
	init();
	cmtx mul=first*mpow(dp,n-1);
	int sum=0;
	for(int i=0;i<x;++i)
	{
		sum=(sum+mul.a[0][i])%mod;
	}
	printf("%d\n",(1ll*qpow(k<<1|1,n-1)*(x+k)+mod-sum)%mod);
}
int main()
{
	int T=read();
	while(T--)solve();
	return 0;
}
```

---

## 作者：dalao_see_me (赞：1)

妙妙数数题。

第一个限制看起来不是很好做，所以要用容斥，容斥以后第一个限制就变成了存在 $a_i\in[x, x + k - 1]$，另外还要减去所有 $a_i<x$ 的情况。

先看第二部分，设 $f_{i,j}$ 是 dp 了前 $i$ 个数，其中 $a_i=j$ 的方案数，转移枚举 $a_{i+1}$ 填什么。这部分可以用矩阵快速幂优化至 $O(x^3\log n)$。

然后是第一部分，相当于一个折线，其中最小值 $\le x+k-1$。枚举差分数组，相当于确定了折线的形态，然后最小值有 $x+k$ 种取值，那式子写出来就是 $(2k+1)^{n-1}(x+k)$。

代码实现不难。

---

## 作者：Others (赞：1)

一道不板的矩快题。

~~无论任何知识，混了些思维我就不会了。~~

由于限制了相邻两项的差，而直接计数又不太可能，所以从差分下手。如果不管自然数的限制及存在一个有限制的数的限制，这里的方案数是最小值取值数 $\times(2k+1)^{n-1}$，再考虑其限制，可以发现 $[x,x+k-1]$ 刚好没有跨过一个 $k$，所以只要最小值在 $[0,x+k-1]$ 中且最大值足够大，这一切都满足了。

所以考虑固定最小值（再加上差分数组就可以确定整个序列），然后把存在 $[x,x+k-1]$ 变成存在 $[0,x+k-1]-$ 全在 $[0,x-1]$ 中的方案数。

第一坨：方案数是 $(x+k)\times(2k+1)^{n-1}$。

第二坨：由于 $x$ 很小 $n$ 很大，条件反射的就是矩快了。这段就是板了。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod=1000000007;
int T,n,x,k,ans;
struct mat {
	int f[41][41];
	mat operator*(const mat &p) const {
		mat tmp;
		memset(tmp.f,0,sizeof(tmp.f));
		for(int k=0;k<x;k++) 
			for(int i=0;i<x;i++) 
				if(f[i][k]) 
					for(int j=0;j<x;j++) 
						tmp.f[i][j]=(tmp.f[i][j]+1ll*f[i][k]*p.f[k][j]%mod)%mod;
		return tmp;
	}
}base,now;
int qpow(int x,int y) {
	int ans=1;
	while(y) {
		if(y&1) ans=1ll*ans*x%mod;
		x=1ll*x*x%mod,y>>=1;
	}
	return ans;
}
int main() {
	cin >> T;
	while(T--) {
		cin >> n >> x >> k;
		ans=1ll*qpow((2*k+1)%mod,n-1)*(x+k)%mod;
		for(int i=0;i<x;i++) now.f[0][i]=1;
		for(int i=0;i<x;i++) 
			for(int j=0;j<x;j++) 
				base.f[i][j]=abs(i-j)<=k;
		n--;
		while(n) {
			if(n&1) now=now*base;
			base=base*base,n>>=1;
		}
		for(int i=0;i<x;i++) ans=(ans-now.f[0][i]+mod)%mod;
		printf("%d\n",ans);
	}
	return 0;
}


```

---

## 作者：Ericby666 (赞：0)

题意实际就是要求出长度为 $n$ 且满足下列两个条件的序列。
- $\exists i\in[1,n]$，$a_i\in[x,x+k-1]$。
- $ \forall i\in[2,n]$，$\left|a_i-a_{i-1}\right|\le k$。

先考虑第一个条件，要使序列中至少有一个数在区间 $[x,x+k-1]$ 中，则需要同时满足两个条件。
1. $\max_{i=1}^na_i\ge x$
2. $\min_{i=1}^na_i\le x+k-1$

使用容斥原理转化，最终答案就是满足 $\min_{i=1}^na_i\le x+k-1$ 的方案总数减去满足 $\max_{i=1}^na_i<x$ 的方案总数。

第一步，求满足 $\min_{i=1}^na_i\le x+k-1$ 的方案总数。

这里可以发现一条性质：只要确定 $\min_{i=1}^na_i$ 和 $a$ 的差分序列 $d$，就可以**唯一确定**序列 $a$。

由于 $\min_{i=1}^na_i$ 的取值范围为 $[0,x+k-1]$，所以 $\min_{i=1}^na_i$ 共有 $x+k$ 种取值。

由于第二个条件的限制，对于差分序列 $d$，显然 $d$ 中所有元素的取值范围为 $[-k,k]$，所以 $d$ 中的每个元素都有 $2k+1$ 种取值。

又因为差分序列 $d$ 有 $n-1$ 位，（这里不考虑差分序列的第一位，因为它不影响序列 $a$ 中元素的相对大小）所以差分序列 $d$ 共有 $(2k+1)^{n-1}$ 种取值。

根据乘法原理，满足 $\min_{i=1}^na_i\le x$ 的方案总数共有 $(x+k)\times(2k+1)^{n-1}$ 种。

第二步，求满足 $\max_{i=1}^na_i<x$ 的方案总数。

这个问题可以转化为求 $\forall a_i\in[0,x)$ 的方案总数，考虑 DP。

用 $f_{i,j}$ 表示 $a_i=j$ 的方案总数，可以得到 $f_{i,j}=\sum_{t=j-k}^{j+k}f_{i-1,t}$。

题目给出的 $n$ 的范围太大，$x$ 的范围又太小，同时转移方程固定，一眼矩阵快速幂。

定义一个 $1\times x$ 的矩阵 $M$ 和一个 $x\times x$ 的矩阵 $N$。$M$ 的初始元素全为 $1$，如果 $\left|i-j\right|\le k$，则令 $N_{i,j}=1$,否则令 $N{i,j}=0$。接着直接跑矩阵快速幂就可以得出满足 $\max_{i=1}^na_i<x$ 的方案总数了。

将两个步骤的答案相减就可以得到最终的答案了，时间复杂度为 $O(x^3\log_2n)$。

AC 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int t,n,x,k,ans;
struct Matrix{
	int Ma[45][45];
	friend Matrix operator*(const Matrix &a,const Matrix &b){
		Matrix res;
		memset(res.Ma,0,sizeof res.Ma);
		for(int i=1;i<=x;i++)
			for(int j=1;j<=x;j++)
				for(int k=1;k<=x;k++)
					res.Ma[i][j]=(res.Ma[i][j]+a.Ma[i][k]*b.Ma[k][j])%mod;
		return res;
	}
}rans,rnow;
int numPow(int a,int k){
	int res=1;
	while(k){
		if(k&1)res=res*a%mod;
		a=a*a%mod;
		k>>=1;
	}
	return res;
}
void MatrixPow(Matrix &a,Matrix &b,int k){
	while(k){
		if(k&1)a=a*b;
		b=b*b;
		k>>=1;
	}
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>x>>k;
		ans=(x+k)*numPow(2*k+1,n-1)%mod;
		for(int i=1;i<=x;i++)rans.Ma[1][i]=1;
		for(int i=1;i<=x;i++)
			for(int j=1;j<=x;j++)
				rnow.Ma[i][j]=(abs(i-j)<=k);
		MatrixPow(rans,rnow,n-1);
		for(int i=1;i<=x;i++)ans=(ans-rans.Ma[1][i]+mod)%mod;
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：complete_binary_tree (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/CF1895F)

首先，一看这题很像 dp，但是发现直接做 dp 做不了。那么考虑反过来做。

考虑容斥：答案等价于 $\min\{a_i\} \le x + k$ 的序列数减去 $\max\{a_i\} < x$ 的序列数。

前者不难得出是 $(x + k) \cdot (2k + 1)^{n - 1}$，后者可以考虑 dp。

令 $f(i,j)$ 表示第 $i$ 位选择 $j$ 来保证这个序列 $\max\{a_i\} < x$ 的方案数。

转移可以枚举 $j$，然后从 $[j - k,j + k]$ 转移。注意判下边界 $[0,x)$。

这样是 $O(Tnx)$ 的，$n \le 10^9$ 过不去。

发现这个转移与 $i$ 无关。所以直接矩阵快速幂优化到 $O(Tx^3\log n)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int X = 45, N = 1e4 + 5, mod = 1e9 + 7;

int n, k, x, t;
typedef long long ll;

struct mat { 
	int a[X][X];
	int n, m;
	void csh(int n, int m) { 
		memset(a, 0, sizeof a);
		this->n = n, this->m = m;
	}
	void build() {
		for (int i = 0; i <= n; ++i) {
			a[i][i] = 1;
		}
	}
} mt, mt2;

mat operator* (mat a, mat b){
	mat c;
	int n = a.n, m = b.m;
	c.csh(n, m);
	for(int i = 0; i <= n; ++i){
		for(int j = 0; j <= m; ++j){
			for(int k = 0; k <= a.m; ++k){
				c.a[i][j] += 1ll * a.a[i][k] * b.a[k][j] % mod; 
				c.a[i][j] %= mod;
			}
		}
	}
	return c;
}

mat ksm(mat a, int b) {
	mat ans, x;
    x.csh(a.n, a.m);
	x = a;
    ans.csh(a.n, a.m);
	ans.build();
	while(b){
		if(b & 1) ans = ans * x;
		x = x * x;
		b >>= 1;
	}
	return ans;
}

namespace FastIO{
    char OutputDevide = ' ';
    template<typename T>inline void read(T& x){T f=1;x = 0;char ch = getchar();while(ch<'0'||ch >'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-48,ch=getchar();x*=f;}
    template<typename T,typename ... Args>inline void read(T& x,Args& ...args){read(x),read(args...);}
    template<typename T>inline void write(T x){if(x<0){putchar('-'),write(-x);return;}if(x/10)write(x/10);putchar(x%10+48);}
    template<typename T,typename ... Args>inline void write(T x,Args ...args){write(x),putchar(OutputDevide),write(args...);}
};
using FastIO::read, FastIO::write;

inline int ksm( int a, int b ) {
    ll x = a, ans = 1;
    while( b ) {
        if( b & 1 ) ans = ans * x % mod;
        x = x * x % mod, b >>= 1;
    }
    return ans;
}

int main(){
    read( t );
    while( t-- ) {
        read( n, x, k );
        ll ans = 1ll * ( x + k ) * ksm( ( 2 * k + 1 ) % mod, n - 1 ) % mod;
        mt.csh( x - 1, x - 1 );
        for( int i = 0; i < x; ++i )
            for( int j = max( 0, i - k ); j <= min( i + k, x - 1 ); ++j )
                mt.a[i][j]++;
        mt = ksm( mt, n - 1 );
        for( int i = 0; i < x; ++i )
            for( int j = 0; j < x; ++j )
                ans -= mt.a[i][j], ans = ( ans % mod + mod ) % mod;
        printf( "%lld\n", ans );
    }
    return 0;
}
```

---

## 作者：KingPowers (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF1895F)

注意到第一个条件有一个至少，这个限制是很难处理的，考虑直接容斥掉，用 $\min\{a_i\}\le x +k-1$ 的方案数减去 $\max\{a_i\}\le x-1$ 的方案数，同时要求满足第二个条件。

现在只需要对两种情况分别计数了对吧，$\min$ 的限制挺少见的我们先看 $\max$。注意到 $x\le 40$ 所以此限制下 $a_i$ 的值域很小，考虑设 $f_{i,j}$ 表示填了 $i$ 个数最后一个填了 $j$ 的方案数，那么就有 $f_{i,j}\times [|j-t|<=k]\to f_{i+1,t}$，直接矩阵快速幂优化即可，这步时间复杂度 $O(x^3\log n)$。

现在只需要数限制 $\min$ 的情况，相邻元素差的约束启示我们在差分数组上考虑问题。设 $b_i=a_i-a_{i-1}(i>2)$，那么每个 $b_i$ 的值域就是 $[-k,k]$，一共 $2k+1$ 种填法，所以 $b_{i}$ 的数量就有 $(2k+1)^{n-1}$ 种。对于每个差分数组 $b$，只要决定初值 $a_1$ 就可以确定整个序列 $a$ 了，而对最终序列 $a$ 的其它限制只有 $\min\{a_i\}\le x+k-1$，也就是 $\min\{a_i\}\in[0,x+k-1]$，最小值共有 $x+k$ 种可能，所以总方案数就是 $(x+k)(2k+1)^{n-1}$，这步时间复杂度 $O(\log n)$。

后者减去前者就是答案，然后做完了。

```cpp
#include<bits/stdc++.h>
//#define int long long
#define For(i, a, b) for(int i = (a); i <= (b); i++)
#define Rof(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
const int N = 5e5 + 5;
template<int mod>
unsigned int down(unsigned int x) {return x >= mod ? x - mod : x;}
template<int mod>
struct ModInt{
	unsigned int x;
	ModInt() = default;
	ModInt(unsigned int x) : x(x) {}
	friend istream& operator>>(istream& in, ModInt& a) {return in >> a.x;}
	friend ostream& operator<<(ostream& out, ModInt a) {return out << a.x;}
	friend ModInt operator+(ModInt a, ModInt b) {return down<mod>(a.x + b.x);}
	friend ModInt operator-(ModInt a, ModInt b) {return down<mod>(a.x - b.x + mod);}
	friend ModInt operator*(ModInt a, ModInt b) {return 1ULL * a.x * b.x % mod;}
	friend ModInt operator/(ModInt a, ModInt b) {return a * ~b;}
	friend ModInt operator^(ModInt a, int b) {ModInt ans = 1; for(; b; b >>= 1, a *= a) if(b & 1) ans *= a; return ans;}
	friend ModInt operator~(ModInt a) {return a ^ (mod - 2);}
	friend ModInt operator-(ModInt a) {return down<mod>(mod - a.x);}
	friend ModInt& operator+=(ModInt& a, ModInt b) {return a = a + b;}
	friend ModInt& operator-=(ModInt& a, ModInt b) {return a = a - b;}
	friend ModInt& operator*=(ModInt& a, ModInt b) {return a = a * b;}
	friend ModInt& operator/=(ModInt& a, ModInt b) {return a = a / b;}
	friend ModInt& operator^=(ModInt& a, int b) {return a = a ^ b;}
	friend ModInt& operator++(ModInt& a) {return a += 1;}
	friend ModInt operator++(ModInt& a, int) {ModInt x = a; a += 1; return x;}
	friend ModInt& operator--(ModInt& a) {return a -= 1;}
	friend ModInt operator--(ModInt& a, int) {ModInt x = a; a -= 1; return x;}
	friend bool operator==(ModInt a, ModInt b) {return a.x == b.x;}
	friend bool operator!=(ModInt a, ModInt b) {return !(a == b);}
};
using mint = ModInt<1000000007>;
struct Matrix{
	int n;
	mint v[41][41];
	Matrix(int n = 0):n(n){memset(v, 0, sizeof v);}
	friend Matrix operator*(const Matrix &a, const Matrix &b){
		Matrix c; c.n = a.n;
		For(i, 0, c.n) For(j, 0, c.n) For(k, 0, a.n)
			c.v[i][j] += a.v[i][k] * b.v[k][j];
		return c; 
	}
};
int n, k, x;
mint qpow(mint x, int y){
	mint res = 1;
	for(; y; x = x * x, y >>= 1)
		if(y & 1) res = res * x;
	return res;
}
Matrix qpow(Matrix x, int y){
	Matrix res(x.n);
	For(i, 0, x.n) res.v[i][i] = 1;
	while(y){
		if(y & 1) res = res * x;
		x = x * x; y >>= 1;
	}
	return res;
}
mint calc(int limit){
	if(limit < 0) return 0;
	Matrix F(limit), G(limit);
	For(i, 0, limit) F.v[0][i] = 1;
	For(i, 0, limit) For(j, 0, limit)
		if(abs(i - j) <= k) G.v[i][j] = 1;
	G = qpow(G, n - 1); F = F * G;
	mint ans = 0;
	For(i, 0, limit) ans += F.v[0][i];
	return ans;
}
void Solve(){
	cin >> n >> x >> k;
	mint ans = (x + k) * qpow((mint)2 * k + 1, n - 1);
	ans -= calc(x - 1);
	cout << ans << '\n';
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int T = 1; cin >> T;
	while(T--) Solve();
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

考虑容斥。

不难发现方案一定满足 $\min(a_i) \leq x+k-1$，并且 $\max(a_i) \geq x$，考虑用满足第一个条件的方案数减去满足 $\max(a_i) \leq x-1$ 的方案数（显然满足这个限制第一个限制也被满足）。

然后计数第一个限制，不妨枚举最小值，最小值有 $x+k$ 种取值，差分数组有 $(2 \times k+1)^{n-1}$ 种取值，两个都确定了这个数组也被确定，由于最小值非负，所以整个序列非负。

计数第二个限制，不妨设计状态 $f_{i,j}$ 表示第 $i$ 位填 $j$ 的方案数，由于 $j \leq x$ 所以直接丢到矩阵上去维护即可做到 $O(T x^3 \log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 1e9+7;
struct Matrix{
    int a[50][50];
    int n,m;
    Matrix(int N=0,int M=0,int C=0){
        n=N,m=M;
        for(int i=0;i<=n;i++)
            for(int j=0;j<=m;j++) a[i][j]=C;
        return ;
    }
    Matrix operator*(const Matrix &x)const{
        Matrix res=Matrix(n,x.m);
        for(int i=0;i<=n;i++)
            for(int k=0;k<=m;k++)
                for(int j=0;j<=x.m;j++) res.a[i][j]=(res.a[i][j]+a[i][k]*x.a[k][j])%mod;
        return res;
    }
}e,base;
int qpow(int a,int b){
    if(b==0) return 1;
    if(b==1) return a;
    int res=qpow(a,b/2);
    res=res*res%mod;
    if(b%2==1) res=res*a%mod;
    return res;
}
Matrix Matrixqpow(Matrix a,int b){
    if(b==0) return e;
    if(b==1) return a;
    Matrix res=Matrixqpow(a,b/2);
    res=res*res;
    if(b%2==1) res=res*a;
    return res;
}
void work(){
    int n,x,k;
    cin>>n>>x>>k;
    e=Matrix(x-1,x-1,0);
    base=Matrix(x-1,x-1,0);
    for(int i=0;i<x;i++) e.a[i][i]=1;
    for(int i=0;i<x;i++){
        for(int j=0;j<x;j++){
            if(abs(i-j)<=k){
                base.a[i][j]=1;
            }
        }
    }
    Matrix s=Matrix(0,x-1,1);
    s=s*Matrixqpow(base,n-1);
    int ans=0;
    for(int i=0;i<x;i++) ans=(ans+s.a[0][i])%mod;
    cout<<(((x+k)%mod)*qpow((2*k+1)%mod,n-1)+mod-ans)%mod<<'\n';
    return ;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin>>T;
    while(T--) work();
    return 0;
}

```


---

