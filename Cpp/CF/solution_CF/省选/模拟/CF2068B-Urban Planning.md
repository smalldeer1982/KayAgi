# Urban Planning

## 题目描述

你负责规划一座新城市！该城市将用一个矩形网格表示，其中每个单元格要么是公园，要么是建筑区。

居民自然希望在城市的公园中散步。具体来说，一个矩形散步区域是指满足以下条件的矩形网格区域：
- 在水平和垂直方向上都至少有 2 个单元格
- 矩形边界上的所有单元格都是公园
- 矩形内部的单元格可以是任意类型

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2068B/650c150729643ceb8f9e562a8913c8a60e9dc725.png) 示例矩形散步区域（深色背景单元格）。你最喜欢的数字是 $k$。为了留下永恒的印记，你需要设计一个恰好包含 $k$ 个矩形散步区域的城市。


## 说明/提示

在样例中，以下是五个可能的矩形散步区域：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2068B/b694d5d43c1db4ce1affb71fd91eaaed1c603a15.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2068B/c0a42475b8538edc0aa9b0c24e8955d114133a0f.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2068B/3749b31d2137b1ef71c23fc5617c6194a72b29cb.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2068B/63f27f79f27b688ddc9ce6f1ac0e857ca91dc99e.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2068B/e7cc09f62ba9dcdd869e9d3cff8988b91b93cc46.png)

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5```

### 输出

```
3 4
####
#.##
####```

# 题解

## 作者：stardust_Ray (赞：0)

翻译一下官 sol。

首先考虑一种暴力构造，从上往下从左到右能填 `#` 就填 `#`，对于第 $i$ 行第 $j$ 个它的贡献就是它前面连续 `#` 的数量乘上 $i - 1$，但是如果到第 $i$ 行的时候 $k$ 还剩下的数量 $<i - 1$ 就会出问题。

考虑在这个做法上面打补丁，如果有一整行都没有对数量有新的贡献，那么就把这一行全部填成 `.`，把上下两部分分开，那么接下来一行的贡献又可以从 $1$ 乘前面连续 `#` 的数量开始。这个做法可以通过 $k\le 4 \times 10^{12}$。

对于 $k \le 4.194 \times 10^{12}$，我们发现如果把 $2024\times 2024$ 的方格填满也只有 $4.191\times 10^{12}$ 的数量，也就是我们需要一个几乎填满的做法，而上面这个做法显然不符合我们的要求。

我们考虑先找到一个最小的 $n$ ，满足对于一个大小为 $n \times (n+1)$ 的满的矩形里面的合法子矩形数量 $\ge p$。然后从一个满的 $n \times (n + 1)$ 网格按照 $(0,0),(1,0),(0,1),(1,1),(2,0),(0,2),(2,1),(1,2),(2,2)\dots$ 的顺序删除，直到剩下的合法矩形数量 $p$ 满足 $k - p \ge n(n - 1)$，同时因为删掉一个点最多减少 $n^2$ 个合法矩形，所以 $k - p = O(n^2)$。

然后我们考虑在第 $n+1$ 行和第 $n+2$ 列加入 `#` 来把剩下的 $k - p$ 补上。因为 $k-p\ge n(n-1)$ 所以我们必然可以找到一组解把 $k - p$ 划分成 $an + b(n+1)$，然后我们就可以用若干个 $\frac{x(x - 1)}2$ 来合成 $a$ 和 $b$。

由于相邻两个的差是 $O(n^3)$ 的，删掉一个点的时候会少掉 $O(n^2)$ 个合法矩形，所以删掉的点数是 $O(n)$ 的，也就是只有 $O(\sqrt n)$ 个行/列被影响了，其它 $n - O(\sqrt n)$ 个行/列依旧是满的，又由于此时 $a,b$ 都是 $O(n)$ 的，所以在 $n$ 比较大的时候完全充足。对于 $n$ 比较小的跑暴力构造即可。

然而我们发现 $n$ 还需要满足 $n\le 2023$ 的限制，但是我们发现在最极限的情况下，如果 $n$ 取 $2023$，那么 $a,b$ 最多也只有大约 $1700000$，在这一情况下对 $\frac{x(x-1)}2$ 的贪心最多也只需要 $1950$ 行，所以我们依旧可以使用这个构造。

贴个代码：

```cpp
// Start: 2025-04-30 08:28:06
#include <bits/stdc++.h>
#define For(i, j, k) for(int i = (j); i <= (k); ++i)
#define ForDown(i, j, k) for(int i = (j); i >= (k); --i)
#define Debug(fmt, args...) fprintf(stderr, "(func %s, line #%d): " fmt, __func__, __LINE__, ##args), fflush(stderr)
#define debug(fmt, args...) fprintf(stderr, fmt, ##args), fflush(stderr)
#define within :
#define LJY main
using namespace std;
typedef long long ll;
const int N = 2050;
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
ll k, n, m;
char s[N][N];
void print() {
	printf("%d %d\n", n, m);
	For(i, 1, n) { For(j, 1, m) putchar(s[i][j]); puts("");}
	exit(0);
}
bool solve1() { // 暴力构造
	n = m = 2025; ll now = k; int lst = 1;
	For(i, 1, m) s[1][i] = '#';
	For(i, 2, n) {
		ll cnt = 0; bool flg = 0;
		For(j, 1, m) {
			if (s[i - 1][j] == '.') { cnt = 0; continue;}
			ll p = (i - lst) * cnt;
			if (now >= p) now -= p, s[i][j] = '#', cnt++, flg |= (bool)p;
			else cnt = 0;
		}
		if (!flg) { // 如果这一行没有新的贡献，那么把上下两部分分开
			For(j, 1, m) s[i][j] = '.';
			i++; lst = i;
			For(j, 1, m) s[i][j] = '#';
		}
	} return !now;
}
signed LJY() {
	For(i, 1, 2025) For(j, 1, 2025) s[i][j] = '.';
	cin >> k; if (solve1()) print();
	For(i, 1, 2025) For(j, 1, 2025) s[i][j] = '.';
	n = 2023;
	ForDown(i, 2022, 1) if ((ll)i * (i - 1) * i * (i + 1) / 4 + i * (i - 1) >= k) n = i; else break; // 找到合适的 n
	For(i, 1, n) For(j, 1, n + 1) s[i][j] = '#';
	ll now = n * (n - 1) / 2 * n * (n + 1) / 2;
	For(i, 1, n) if(k - now < n * (n - 1)) { // 不断删去直到 k - p >= n(n - 1)
		For(j, 1, i - 1) if (k - now < n * (n - 1))
			now -= (n - i) * (n + 1 - j), s[i][j] = '.';
		For(j, 1, i) if (k - now < n * (n - 1))
			now -= (n - j) * (n + 1 - i), s[j][i] = '.';
	} k -= now;
	ll q = k % n, p = (k - q * (n + 1)) / n;
	while (p > q + n) p -= n + 1, q += n; // 找到 a, b
	now = n + 1;
	auto getval = [](ll x) {return (int)((1 + sqrtl(1 + 8 * x)) / 2);};
	while (p) { // 贪心
		ll x = getval(p); p -= x * (x - 1) / 2;
		For(i, now - x + 1, now) s[n + 1][i] = '#';
		now = now - x - 1;
	} now = n;
	while (q) { // 贪心
		ll x = getval(q); q -= x * (x - 1) / 2;
		For(i, now - x + 1, now) s[i][n + 2] = '#';
		now = now - x - 1;
	} m = n + 2, n = n + 1, print();
	return 0;
}
```

---

