# [ICPC 2017 WF] Posterize

## 题目描述

![](https://cdn.luogu.com.cn/upload/image_hosting/gc3c052t.png)

数字图像中的像素可以用三个范围在 $0$ 到 $255$ 之间的整数表示，分别表示红、绿、蓝三种颜色的强度。为了压缩图像或创造艺术效果，许多照片编辑工具包括一个 `posterize` 操作，其工作原理如下。每个颜色通道单独检查；这个问题只关注红色通道。对于红色通道，posterized 图像最多允许 $k$ 个整数，而不是允许从 $0$ 到 $255$ 的所有整数。每个像素的原始红色强度被替换为允许整数中最接近的一个。照片编辑工具选择一组 $k$ 个整数，以最小化原始图像中所有像素引入的平方误差之和。如果有 $n$ 个像素的原始红色值为 $r_{1}, \ldots, r_{n}$，并且有 $k$ 个允许的整数 $v_{1}, \ldots, v_{k}$，则平方误差之和定义为

$$\sum\limits_{i=1}^n \min\limits_{1 \le j \le k}(r_i-v_j)^2$$

你的任务是计算在给定参数 $k$ 和图像像素红色强度描述的情况下，可以实现的最小平方误差之和。

## 说明/提示

时间限制：2 秒，内存限制：512 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
2 1
50 20000
150 10000
```

### 输出

```
66670000
```

## 样例 #2

### 输入

```
2 2
50 20000
150 10000
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4 2
0 30000
25 30000
50 30000
255 30000
```

### 输出

```
37500000
```

# 题解

## 作者：__xxy_free_ioi__ (赞：4)

# 题解：P6934 \[ICPC 2017 WF] Posterize

区间 DP（~~为啥我总感觉不像~~）

## 解法

我们可以直接预处理一个 $f$ 数组，其中 $f_{i, j}$ 表示将区间 $i \sim j$ 全部转化为一种颜色的误差最小值，由于数据很小，直接暴力算即可。再定义一个数组 $g$，其中 $g_{i,j}$ 表示将 $1 \sim i$ 中的颜色转化为 $j$ 种颜色的最小值。那么，转移式就是 $g_{i,j} = \min(g_{i,j}, g_{l, j - 1} + f_{l+1,i})$，其中 $l \le i - 1$。其实就是把它拆成两份，将 $l+1 \sim i$ 转化为一种颜色，剩下的就是 $g_{l, j-1}$。

## 代码

```
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 300;

int n, k;
int r[N], p[N], f[N][N], g[N][N];

signed main() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
		cin >> r[i] >> p[i];
	
	memset(f, 0x3f, sizeof f);
	memset(g, 0x3f, sizeof g);
	g[0][0] = 0;
	
	for (int c = 0; c < 256; c++) 
		for (int i = 1; i <= n; i++) {
			int s = 0;
			for (int j = i; j <= n; j++)
				f[i][j] = min(f[i][j], s += p[j] * (r[j] - c) * (r[j] - c));
		}
	
	for (int i = 1; i <= n; i++)
		for (int j = 1, x = min(i, k); j <= x; j++)
			for (int l = 0; l < i; l++)
				g[i][j] = min(g[i][j], g[l][j - 1] + f[l + 1][i]);
	
	return cout << g[n][k] << '\n', 0;
}
```

---

## 作者：LJY_ljy (赞：2)

可以发现 $k, r, d \leq 256$ 而 $p$ 很大，所以可以考虑本题的时间复杂度仅和 $k, r, d$ 有关且不劣于 $\mathrm{O}(n^3), n = 256$.

考虑 dp. 

设 $dp[i][cnt]$ 表示 $v[1] < v[2] < \cdots < v[i] = cnt, v[i + 1] = v[i + 2] = \cdots = v[k] = +\infty$ 时的最小误差。（可以理解为我们目前只有 $cnt$ 个 $v[i]$）

则 
$$
dp[i][cnt] = \min_{j < i}\{dp[j][cnt - 1] + \sum_{r[k] > \frac{i + j}{2}} (r[k] - i)^2 - (r[k] - j)^2\}
$$

因为 $\left | r[k] - i \right | < \left | r[k] - j \right | \Leftrightarrow r[k] > \dfrac{i + j}{2}$

由于枚举 $i, j, cnt$ 已经是 $\mathrm{O}(n^3)$ 时间复杂度的了，故需要在 $\mathrm{O}(1)$ 的时间复杂度内计算出 $\displaystyle \sum_{r[k] > \frac{i + j}{2}} (r[k] - i)^2 - (r[k] - j)^2$.

由于
$$
\sum_{r[k] > \frac{i + j}{2}} (r[k] - i)^2 - (r[k] - j)^2 = (2j - 2i) sum[\frac{i + j}{2}][0] + (i^2 - j^2) sum[\frac{i + j}{2}][1]
$$

其中
$$
sum[x][0] = \sum_{r[k] > x} r[k]
$$

$$
sum[x][1] = \#\{r[k] > x \ | \ k\}
$$

故可以考虑前缀和，先记录出前缀和的差分数组，后进行累加得到前缀和数组即可。


```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdlib>
using namespace std;

const long long MAXN = 300;
const long long INF = 1e15;

inline long long read() {
	long long x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch)) {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (isdigit(ch)) {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * f;
}

struct node {
	long long r, p;
	bool operator < (const node &a) const {
		return r < a.r;
	}
} a[MAXN];

long long k, d;
long long dp[MAXN][MAXN]; 
long long DD[MAXN][2], sum[MAXN][2];

int main() {
	d = read(); k = read();
	for (long long i = 1; i <= d; i++) {
		a[i].r = read();
		a[i].p = read();
		DD[a[i].r][0] = a[i].r * a[i].p;
		DD[a[i].r][1] = a[i].p;
	}
	sort(a + 1, a + 1 + d);
	sum[0][0] = DD[0][0]; 
	sum[0][1] = DD[0][1];
	for (long long i = 1; i <= 255; i++) {
		for (long long j = 0; j < 2; j++)
			sum[i][j] = sum[i - 1][j] + DD[i][j];
	}
	for (long long j = 0; j <= 255; j++) {
		for (long long kk = 1; kk <= 256; kk++)
			dp[j][kk] = INF;
	}
	for (long long i = 0; i <= 255; i++) {
		dp[i][1] = 0;
		for (long long j = 1; j <= d; j++) {
			dp[i][1] += a[j].p * (a[j].r - i) * (a[j].r - i);
		}
	}
	for (long long cnt = 2; cnt <= k; cnt++) {
		for (long long i = 0; i <= 255; i++) {
			for (long long j = 0; j < i; j++) {
				long long A = (2 * j - 2 * i) * (sum[255][0] - sum[(i + j) / 2][0]) + (i * i - j * j) * (sum[255][1] - sum[(i + j) / 2][1]);
				dp[i][cnt] = min(dp[i][cnt], dp[j][cnt - 1] + A); 
			}
		}
	}
	long long minn = INF;
	for (long long i = 0; i <= 255; i++) {
		minn = min(minn, dp[i][k]);
	}
	printf("%lld\n", minn); 
	return 0;
}
```

---

## 作者：cyc001 (赞：0)

首先我们可以考虑一下的题目简化版，假设我们知道每一个区间的最小差值 $cost_{l,r}$，这道题又该怎么求？

其实此处答案比较明显，可以使用线性 DP 求解。

设 $D_{i,j}$ 表示在区间 $[0,j]$ 内用了 $i$ 段不同的区间，则状态转移方程如下：
$$
D_{i,j}=\underset{x=i-1}\min^j D_{i-1,x}+cost_{x+1,j}
$$
而 $cost$ 数组则可以预处理求出，做法如下：
$$
cost_{l,r}=\underset{x=0}\min^{255}\underset{y=l}\sum^r (r_y-i)^2 p_y
$$
时间复杂度为 $O(d^3)$

最后就是~~喜闻乐见~~的代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN = 307;
typedef long long lint;
lint D[NN][NN], cost[NN][NN];
struct str {
	lint v, n;
	bool operator<(const str& st) const {
		return v < st.v;
	}
};
lint cking(lint x) { return x > 0 ? x : 0; }
int main(){
	ios::sync_with_stdio(false), cin.tie(0);
	int n, k; cin >> n >> k;
	vector<str> vs(n);
	for (auto& i : vs) cin >> i.v >> i.n;
	sort(vs.begin(), vs.end());
	memset(cost, 0x3f, sizeof(cost));
	memset(D, 0x3f, sizeof(D));
	D[0][0] = 0; const lint _inf = D[NN - 1][NN - 1];
	for (int i = 0; i < 256; ++i) for (int j = 0; j < n; ++j) {
		lint ci = 0; cost[j][j] = 0;
		for (int x = j; x < n; ++x) {
			ci += (vs[x].v - i) * (vs[x].v - i) * vs[x].n;
			cost[j][x] = min(ci, cost[j][x]);
		}
	}
	for (int i = 0; i < n; ++i) {
		D[1][i] = cost[0][i];
		for (int j = 2; j <= k; ++j) {
			for (int x = 0; x < i; ++x) D[j][i] = min(D[j][i], D[j - 1][x] + cost[x + 1][i]);
		}
	}
	cout << D[k][n - 1] << endl;
	return 0;
}
```

---

