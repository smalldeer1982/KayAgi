# [ARC184C] Mountain and Valley Folds

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc184/tasks/arc184_c

厚さを無視できる細長い紙があります。右端を持ち上げ、中央を折り目にして左端に合わせて折りたたむ操作を $ 100 $ 回行い、もとに戻します。このとき紙には折り目が $ 2^{100}\ -\ 1 $ 個あり、これらは山折り、谷折りの $ 2 $ 種類に分類できます。下の図は $ 2 $ 回操作を行った状態を表した図で、赤い実線は山折り、赤い点線は谷折りを表します。

山折り、谷折りとは- ある折り目が山折りであるとは、折り目が紙の裏面同士が重なる方向に折られたことをいいます。
- ある折り目が谷折りであるとは、折り目が紙の表面同士が重なる方向に折られたことをいいます。

![image of folds](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_arc184_c/a6888c2d5e0c2b2f18956db7954caa4251b38be7.png)

長さ $ N $ の非負整数列 $ A\ =\ (A_1,\ A_2,\ \dots\ ,A_N) $ が与えられます。ここで $ 0\ =\ A_1\ <\ A_2\ <\ \dots\ <\ A_N\ \leq\ 10^{18} $ です。

$ 1 $ 以上 $ 2^{100}\ -\ A_N\ -\ 1 $ 以下の整数 $ i $ に対し、 $ f(i) $ を以下のように定義します。

- $ k\ =\ 1,\ 2,\ \dots\ ,N $ のうち、左から $ i\ +\ A_k $ 番目の折り目が山折りであるものの個数

$ f(1),\ f(2),\ \dots\ ,f(2^{100}\ -\ A_N\ -\ 1) $ の最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^3 $
- $ 0\ =\ A_1\ <\ A_2\ <\ \dots\ <\ A_N\ \leq\ 10^{18} $

### Sample Explanation 1

山折り、谷折りをそれぞれ `M`, `V` と表すことにすると、折り目には `MMVM` と連続する箇所が存在します。`MMMM` と連続する箇所は存在しないので、答えは $ 3 $ となります。

## 样例 #1

### 输入

```
4
0 1 2 3```

### 输出

```
3```

## 样例 #2

### 输入

```
6
0 2 3 5 7 8```

### 输出

```
4```

# 题解

## 作者：LingLuo_VividCycle (赞：12)

$i\equiv 1\pmod 4$ なら、$i$ 番目の折り目は谷折りである。$i\equiv 3\pmod 4$ なら、$i$ 番目の折り目は山折りである。更に、$i$ が偶数の場合、$i$ 番目の折り目と $\dfrac i2$ 番目の折り目は同じ折りである。そして、$i$ が $a2^b$（$a$ は奇数である）の形で表されるなら、$i$ 番目の折り目は、$a\equiv 3\pmod 4$ である場合にのみ山折りとなる、逆もまた然り。$i$ が負数の場合、$i$ 番目の折り目も同様に定義される。しかし、ゼロ番目の折り目が谷折りと呼びます。

$2^b$ が最大の山折りは $a2^b$ 番目の折り目を仮定する。適切な差を選択して、$a=-1$ になら、$f$ の値は変わらない。そして、すべての $A_i$ と $-2^b$ を列挙する、全体で $O(N^2\log A)$ で解くことができました。

---

## 作者：Lgx_Q (赞：8)

我们考虑所有编号为奇数的折痕，其形如 `VMVMVM...`，其中 `V` 表示下凹，`M` 为上凸。这个可以证明：

+ 归纳证明。考虑第一个折痕，其在最后一次对折时产生，显然为 `V`。

+ 假设前 $2^c - 1$ 条奇数编号的折痕形如 `VMVMVM...`，第 $2^c$ 条折痕会将前面这些折痕对称过去并取反（例如会在 `VMVMVMV` 末尾接上 `MVMVMVMV`，变为 `VMVMVMVMVMVMVMV`），因此前 $2^{c+1} - 1$ 条奇数编号的折痕也满足这个结构。

类似的，我们可以推广这个结论：对于任意一个 $c(0\le c\le 99)$，拎出所有编号的 lowbit 为 $2^b$ 的折痕，它们的结构形如 `VMVMVM...`。证明可以考虑忽略所有 lowbit 小于 $2^c$ 的折痕，就是上面的结论。

接下来回到原问题，我们首先对 $a_{1...n}$ 分类，分成奇数和偶数两类。

令 $k$ 为 $a_{1...n}$ 需要加的增量。如果 $k$ 为奇数，则 $a$ 中的偶数的贡献可以确定；如果 $k$ 为偶数，则 $a$ 中的奇数的贡献可以确定。

当 $k$ 为偶数时，为了确定贡献是 $0$ 还是 $1$，我们还需要对 $\frac {k} 2$ 的奇偶性即 $k \bmod 4 = 2$ 或 $k \bmod 4 = 0$ 进行分类讨论。当 $k \bmod 4 = 0$ 时，贡献为 $\sum\limits_{i = 1} ^ n [a_i \bmod 4 = 3]$；当 $k \bmod 4 = 2$ 时，贡献为 $\sum\limits_{i = 1} ^ n [a_i \bmod 4 = 1]$。

设 $f(a, u)$ 为对于给定的 $a$ 序列，满足 $k \bmod 2 = u$ 的答案。当 $u = 0$ 即 $k$ 为偶数时，我们还需要求所有偶数组成的序列答案，设 $b$ 序列为 $a$ 中所有偶数除以二组成的序列。注意有个隐性条件：当 $k \bmod 4 = 0$ 时，从 $f(b, 0)$ 处转移过来；当 $k \bmod 4 = 2$ 时，从 $f(b, 1)$ 处转移过来。

$u = 1$ 的情况是类似的。当递归层数达到 $\log_2 a$ 时可以直接返回，每个数至多被遍历 $O(\log a)$ 次，时间复杂度 $O(n\log a)$。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define fi first
#define se second
#define mkp make_pair
#define pir pair <ll, ll>
#define pb emplace_back
#define i128 __int128
using namespace std;
const ll maxn = 1010, inf = 1e18;
ll n, a[maxn], b[maxn];
pir solve(ll d, ll l, ll r) {
	if(l > r) return mkp(0, 0);
	if(d == 1) return mkp(-inf, r - l + 1);
	ll cnt[4] = {}, pl = l, pr = r;
	for(ll i = l; i <= r; i++) {
		if(a[i] & 1) b[pl++] = a[i];
		else b[pr--] = a[i];
		++cnt[a[i] & 3];
	} 
	for(ll i = l; i <= r; i++) a[i] = b[i] >> 1;
	pir x = solve(d - 1, l, pl - 1), y = solve(d - 1, pr + 1, r);
	pir ret;
	ret.fi = max(cnt[2] + x.fi, cnt[0] + x.se);
	ret.se = max(cnt[3] + y.se, cnt[1] + y.fi);
	return ret;
}
int main() {
	scanf("%lld", &n);
	for(ll i = 1; i <= n; i++) scanf("%lld", a + i);
	pir ret = solve(100, 1, n);
	printf("%lld", max(ret.fi, ret.se));
	return 0;
}
```

---

## 作者：Petit_Souris (赞：1)

一开始毫无头绪，折了半天纸看不出咋做。后来得到提示根据 lowbit 分类，总算看出规律了。

我们先拿出一张干净的草稿纸开始折叠，比如先折四折，发现折痕依次为 $\texttt{001001100011011}$。$0$ 表示谷，$1$ 表示峰。容易证明折 $i+1$ 折的折痕的一段前缀就是折 $i$ 折的折痕。

这个肯定是有一定规律的。我们提取出所有的奇数位，发现恰好是 $\texttt{01010101}$，把这些删掉之后得到的 $\texttt{0010011}$ 又正好是三折的前缀，再递归提取下去，发现实际上就是按照 lowbit 分类，每类内部是 01 交替的。

现在可以考虑 dp 了。设 $f(S,0/1)$ 表示集合 $S$，钦定 $k\bmod 2=0/1$ 的最大答案。转移的时候，从低往高考虑，那么分成末尾为 $0/1$ 的情况，两侧是独立的，且一侧的贡献可以直接算出来。因此复杂度为 $\mathcal O(n\log A)$。

[submission](https://atcoder.jp/contests/arc184/submissions/59320251)

---

## 作者：Composite_Function (赞：1)

叠甲：没有证明做法正确性，欢迎且希望 hack。主要介绍折痕性质的证明。

首先有结论：若 $x=(\overline{x_n...,x_m0...0})_2$，则 $x$ 是 "mountain fold" 当且仅当 $x_m=x_{m+1}=1$。

下用 $1$ 表示 "mountain fold"，$0$ 表示 "valley fold"。

首先注意到每一次折纸的时候产生的都是一正一反的折痕，且插入在原来每个折痕，这意味着，假设第 $k$ 次的折痕是 $x_1,...x_{2^k-1}$，那么第 $k+1$ 的折痕为 $0,x_1,1,x_2,0,...,x_{2^k-1},1$。

然后可以使用归纳法说明每一次产生的折痕的前一半和原来的折痕完全相同。事实上，如果第 $k$（$k > 1$） 次是 $x_1,...,x_{2^k - 1}$，且第 $k$ 次折痕和第 $k - 1$ 次折痕前一半相同。那么第 $k + 1$ 次折痕的前一半是 $0,x_1,1,...,x_{2^{k - 2} - 1},1$。而第 $k$ 次的折痕是 $0,x_1,1,...,x_{2^{k - 2} - 1},1$（归纳假设可以得到）。这就完成了归纳。

这一点告诉我们，无论这多少次，前面的不会改变。那么进一步，对于 $a_{4k + 1} = 0,a_{4k + 3} = 1$，这是由于每折一次多出来的那些折痕。而对于 $a_{2k}$，是在某一次中在两侧添加折痕所得的位置，在加折痕之前是第 $k$ 个，其实就是 $a_{k}$。进而就得到了结论。

然后就可以按二进制 DP 即可了，但是想要介绍另一个玄学做法。

直接暴力枚举 $i$，大概扫到 $30000$ 左右，然后使用一些小剪枝即可。目前没有证明正确性 / hack。

```cpp
#include <bits/stdc++.h>
using namespace std;

struct FastIO {
	inline FastIO& operator >> (short& x) {
		x = 0;
		char f = 0, ch = getchar();
		while (ch > '9' || ch < '0') f |= (ch == '-'), ch = getchar();
		while (ch <= '9' && ch >= '0') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
		return x = (f ? -x : x), *this;
	}
	inline FastIO& operator >> (int& x) {
		x = 0;
		char f = 0, ch = getchar();
		while (ch > '9' || ch < '0') f |= (ch == '-'), ch = getchar();
		while (ch <= '9' && ch >= '0') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
		return x = (f ? -x : x), *this;
	}
	inline FastIO& operator >> (long long& x) {
		x = 0;
		char f = 0, ch = getchar();
		while (ch > '9' || ch < '0') f |= (ch == '-'), ch = getchar();
		while (ch <= '9' && ch >= '0') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
		return x = (f ? -x : x), *this;
	}
	inline FastIO& operator >> (double& x) {
		x = 0;
		char f = 0, ch = getchar();
		double d = 0.1;
		while (ch > '9' || ch < '0') f |= (ch == '-'), ch = getchar();
		while (ch <= '9' && ch >= '0') x = x * 10 + (ch ^ 48), ch = getchar();
		if (ch == '.') {
			ch = getchar();
			while (ch <= '9' && ch >= '0') x += d * (ch ^ 48), d *= 0.1, ch = getchar();
		}
		return x = (f ? -x : x), *this;
	}
} rin;

#define ll long long
#define uint unsigned int
#define reg register
#define ld long double
#define uint unsigned int
#define ull unsigned long long
#define qint const int&
#define qll const ll&
#define quint cosnt uint&
#define qull const ull&

inline void qmod(int& x, const int& mod) {
	x = x >= mod? x - mod : x;
}

#define int long long

const int N = 1010;
int n, a[N], ans;

inline bool getnum(int x) {
	while (!(x & 1)) x >>= 1;
	return (x & 3) == 3;
}

signed main() {
	rin >> n;
	for (int i = 1; i <= n; ++i) {
		rin >> a[i];
	}
	for (int x = 1; x <= 3e4; ++x) {
		int sum = 0;
		for (int j = 1; j <= n; ++j) {
			sum += getnum(x + a[j]);
			if (sum + n - j <= ans) break;
		}
		ans = max(ans, sum);
	}
	cout << ans << endl;
	return 0;
}
```

---

