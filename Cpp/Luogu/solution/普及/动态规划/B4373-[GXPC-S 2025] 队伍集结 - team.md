# [GXPC-S 2025] 队伍集结 / team

## 题目背景

题目来源：2025 年广西中小学生程序设计挑战赛复赛（进阶组[试题](https://mp.weixin.qq.com/s?__biz=MzI3NDM3MzcwNQ==&mid=2247490166&idx=5&sn=e7ba7e3bc8126027b9abd662518c208b&chksm=ea9c06dd4d18206ed9d88124cc78b947298df2555889e98620204c2ea1471f58c135c00f99fb&mpshare=1&scene=23&srcid=0724dNJdhMxpUHag1dqkhiqL&sharer_shareinfo=7e47197d6e5c044ae705613db988029c&sharer_shareinfo_first=7e47197d6e5c044ae705613db988029c#rd)）。


## 题目描述


233zhang 和他的同学们走在大街上，该街道可视为一条无限长直线。他们各自分散在大街的各个角落，每个人的位置记作 $a_i$ （$a_i$ 是整数，并且不保证唯一）。现在他们需要汇合，你可以给出 $k$ 个汇合点，同学们可以前往任意一个汇合点。汇合点位置可以安排在任意整数位置上。

同学们自然是想要偷懒的，他们会选择离自己位置最近的。由于每个人的体质不同，同学们对于距离各自有不同的不满意系数，记作 $b_i$。对于每个人，他的不满意度计算为 $
(a_i - x)^2 \times b_i
$（其中 $x$ 为距离 $a_i$ 最近的汇合点的位置）。

为避免同学们因汇合点设置不合理而愤怒，你需要尽可能地使同学们的不满意度总和最小，并给出答案。


## 说明/提示

#### 样例解释
- 样例 $1$ 中，我们选择将唯一的一个汇聚点放置在 6 上，此时第一个人他的不满意度为 $(3 - 6)^2 \times 3 = 27$，第二个人他的不满意度为 $(10 - 6)^2 \times 2 = 32$，故总不满意度为 $27 + 32 = 59$。此时为最优解。
- 样例 $2$ 中，我们选择在 50、150 处分别建立汇聚点，第一个人会选择前往 50 位置的汇聚点，第二个人会前往 150 位置的汇聚点。此时总不满意度为 0。

#### 数据范围  
- 对于 10% 的数据，保证 $k = 1$，$0 \le a_i \le 20$，$1 \le k \le n \le 20$。  
- 对于 40% 的数据，保证 $0 \le a_i \le 20$，$1 \le k \le n \le 20$。  
- 对于 100% 的数据，保证 $0 \le a_i \le 200$，$1 \le k \le n \le 200$，$1 \le b_i \le 10^9$。



## 样例 #1

### 输入

```
2 1
3 3
10 2```

### 输出

```
59```

## 样例 #2

### 输入

```
2 2
50 200
150 300```

### 输出

```
0```

## 样例 #3

### 输入

```
5 2
0 3000
25 256
50 114514
150 65536
100 40000```

### 输出

```
69563466```

# 题解

## 作者：_Null_Ptr (赞：5)

前缀和预处理加动态规划，首先将同学们按照他们的位置进行排序，因为最优的汇合点分组一定是连续的区间，这样可以简化问题的处理。然后计算三个前缀和数组，用于计算任意区间内的同学的不满意度相关的总和，从而更快地计算每个区间的最小不满意度。显而易见，这是一道 dp 题，状态可以定义为前 $m$ 个同学分成 $t$ 个组的最小不满意度。

具体实现见代码。
```python
import math
n, k = map(int, input().split())
stu = []
for _ in range(n):
    a, b = map(int, input().split())
    stu.append((a, b))
stu.sort()
a = [x[0] for x in stu]
b = [x[1] for x in stu]
pre_a2b = [0] * (n + 1)
pre_ab = [0] * (n + 1)
pre_b = [0] * (n + 1)
for i in range(1, n + 1):
    ai = a[i - 1]  
    bi = b[i - 1]
    pre_a2b[i] = pre_a2b[i - 1] + ai * ai * bi
    pre_ab[i] = pre_ab[i - 1] + ai * bi
    pre_b[i] = pre_b[i - 1] + bi
val = [[0] *(n + 1)for _ in range(n + 1)]
for i in range(1, n + 1):
    for j in range(i, n + 1):
        sum_a2b = pre_a2b[j] - pre_a2b[i - 1]
        sum_ab = pre_ab[j] -pre_ab[i - 1]
        sum_b = pre_b[j]-pre_b[i - 1]
        x0 = sum_ab/sum_b
        x1 = math.floor(x0)
        x2 = math.ceil(x0)
        c1 = sum_a2b - 2 * x1 * sum_ab + x1 * x1 * sum_b
        c2 = sum_a2b - 2 * x2 * sum_ab + x2 * x2 * sum_b
        val[i][j] = min(c1, c2)
INF = 10**18
dp = [[INF] * (k + 1) for _ in range(n + 1)]
dp[0][0] = 0
for m in range(1, n + 1):
    dp[m][1] = val[1][m]
for t in range(2, k + 1):
    for m in range(t, n + 1):  
        min_val = INF
        for p in range(t - 1, m):
            cur = dp[p][t - 1] + val[p + 1][m]
            if cur < min_val:
                min_val = cur
        dp[m][t] = min_val

print(int(dp[n][k]))
```

---

## 作者：william1118 (赞：3)

## 思路
这题显然可以动态规划。设 $dp_{i,j}$ 表示考虑到了第 $i$ 个人，已经用了 $j$ 个汇合点的最小不满意度。由于我们不知道上一个汇合点划分到了哪个人，因此需要枚举一个 $k$，表示上一个汇合点划分到了哪个人，由此可以得出转移方程：
$$
dp_{i,j} = \min(dp_{i,j},dp_{k,j - 1} + cost(k + 1, i))
$$
其中的 $cost(k + 1, i)$ 为从第 $k + 1$ 个人到第 $i$ 个人当中的所有人到汇合点的不满意度之和，即
$$
cost(k + 1, i) = \sum_{p = k + 1} ^ {i} (a_p - x) ^ 2 b_p
$$
化简可得
$$
cost(k + 1, i) = \sum_{p = k + 1} ^ {i} b_p \cdot x^2 - 2\sum_{p = k + 1} ^ {i} a_p b_p \cdot x+ \sum_{p = k + 1} ^ {i} a_p^2 b_p
$$
不难发现这是一个开口向上的二次函数，当 $x = \frac{ \sum_{p = k + 1} ^ {i} a_p b_p}{\sum_{p = k + 1} ^ {i} b_p}$ 时取到最小值，前缀和维护即可，时间复杂度 $O(n^2m)$，$m$ 为汇合点数量。

## 代码
```cpp
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;
using ll = long long;

const int N = 201;

int n, m;
struct node{
	ll a, b;
}c[N];
ll f[N], g[N], dp[N][N], C[N][N];

bool cmp(node &A, node &B) {
	return A.a < B.a;
}

ll cost(int i, int j) {
  // x不一定是整数，因此要对上取整和下取整的答案取最小值
	int x1 = floor(1.0 * (g[j] - g[i - 1]) / (f[j] - f[i - 1]));
	int x2 = ceil(1.0 * (g[j] - g[i - 1]) / (f[j] - f[i - 1]));
	ll res1 = 0, res2 = 0;
	for (int k = i; k <= j; k++) {
		res1 += 1LL * (c[k].a - x1) * (c[k].a - x1) * c[k].b;
		res2 += 1LL * (c[k].a - x2) * (c[k].a - x2) * c[k].b;
	}
	return min(res1, res2);
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> m;
	if (m == n) return cout << 0, 0;
	for (int i = 1; i <= n; i++) {
		cin >> c[i].a >> c[i].b;
	}
	sort(c + 1, c + n + 1, cmp);
	for (int i = 1; i <= n; i++) {
		f[i] = f[i - 1] + c[i].b, 
		g[i] = g[i - 1] + c[i].a * c[i].b;
		dp[i][0] = 1e18;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			C[i][j] = cost(i, j);
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			dp[i][j] = 1e18;
			for (int k = 0; k < i; k++) {
				dp[i][j] = min(dp[i][j], dp[k][j - 1] + C[k + 1][i]);
			}
		}
	}
	cout << dp[n][m];
	return 0;
}

```
- [AC记录](https://www.luogu.com.cn/record/228710214)

---

## 作者：Lyw_and_Segment_Tree (赞：2)

一眼题，但是细节很多。

首先我们按照点的坐标从左往右依次标号为 $1, 2, 3, \dots, k$。

设 $dp_{i, j}$ 表示把第 $i$ 个点放在 $j$ 位置能得到的答案，可以枚举第 $i - 1$ 个点位置 $t$，则有 $dp_{i, j} = \min(dp_{i - 1, t} + cost(t, j))$，其中 $cost(x, y)$ 表示 $x$ 到 $y$ 这段区间内，学生不满意度的和。

所以我们需要枚举 $i, j, k$ 算出所有 dp 值，注意边界条件 $dp_{0, 0} = 0$，其余的先设为 $\text{INF}$，这里的时间复杂度是 $O(k\max(a_i) ^ 2)$。

但是，这样还没有做完，考虑第 $k$ 个点右侧可能还有学生没有被计算到，所以我们还需要一个函数 $costt(x)$ 来算出 $[x, \max(a_i)]$ 这段区间中学生不满意度之和。

综上，有：

$$ ans = \min_{i = 0}^{\max{a_i}}(dp_{k, i} + costt(i)) $$

把这个 $ans$ 算出来即可。

这样本题看似做完了，实则细节比较多，你需要注意的细节：

- 在算 dp 值的时候要特判 $i = 1$，这时 $cost$ 函数的计算方法也有变化，可以考虑加上一个参数表示是否是这种情况，进行分讨。

- 在算 dp 值的时候 $j$ 最小可以是 $0$，$t$ 可以取到 $j$，这里需要特别注意，如果你不慎把 $j$ 的起点设为 $1$ 从而获得 60 pts 可能是这个原因。

- 要先对 $a_i$ 排序，否则无法计算。

- 其他神秘的细节，似乎没了。

所以最后的时间复杂度主要来源于计算 dp 数组，时间复杂度 $O(k \max(a_i) ^ 2)$。

code：

```cpp
#include <bits/stdc++.h>
#define ll long long
#define db double
#define vec vector
#define pb push_back
#define pll pair<ll, ll>
#define pr pair
#define mkp make_pair
#define endl "\n"

using namespace std;

const ll mod = 998244353;

namespace fastio {char buf[1 << 21], *p1 = buf, *p2 = buf; const ll getc() {return p1 == p2 && ( p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1 ++;}const ll read() {ll x = 0, f = 1;char ch = getc();while (ch < '0' || ch > '9') {if (ch == '-') f = -1; ch = getc();}while (ch >= '0' && ch <= '9') {x = (x << 1) + (x << 3) + (ch ^ 48), ch = getc();}return x * f;} const void write(ll x) {if (x < 0) { putchar('-'), x = -x; } ll sta[35], top = 0; do {sta[top++] = x % 10, x /= 10;} while (x); while (top) putchar(sta[--top] + 48); }}

#define rd fastio::read
#define wt fastio::write
#define gc fastio::getc

ll n, m, q, k, dp[205][305]; // string s;

ll opt, l, r, x, y, z, ans = 1e18;

struct node {
	ll a, b;
	
	friend bool operator < (node x, node y) {
		return x.a < y.a;
	}
} a[200005] ;

ll cost(ll x, ll y, bool f) {
    if (x > y) swap(x, y);

	ll res = 0;
	
	for (ll i = 1; i <= n; i++) {
		if (a[i].a >= x && a[i].a <= y) {
			ll ps = min(a[i].a - x, y - a[i].a);
			
			if (x == 0 && !f) ps = y - a[i].a; 
			
			res += ps * ps * a[i].b; 
		}
	}
	
	return res;
}

ll costt(ll x) {
	ll res = 0;
	
	for (ll i = 1; i <= n; i++) {
		if (a[i].a >= x) {
			res += (a[i].a - x) * (a[i].a - x) * a[i].b;
		}
	}
	
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	ll i, j, u, v, w, q, res = 0, now;
	
	cin >> n >> k; ll mxa = 0;
	
	for (i = 1; i <= n; i++) cin >> a[i].a >> a[i].b, mxa = max(mxa, a[i].a);
	
	sort(a + 1, a + n + 1);
	
    memset(dp, 63, sizeof(dp));

    dp[0][0] = 0;

	for (i = 1; i <= k; i++) {
		for (j = 0; j <= mxa; j++) {			
			for (ll t = 0; t <= j; t++) {
				if (i == 1) {
					dp[i][j] = min(dp[i][j], dp[i - 1][0] + cost(0, j, 0));
				} else {
					dp[i][j] = min(dp[i][j], dp[i - 1][t] + cost(t, j, 1));
				}
			}
		}
	}
	
	for (i = 0; i <= mxa; i++) {
		ans = min(ans, dp[k][i] + costt(i));
	}
	
	cout << ans;
	
	return 0;
}

/*
dp[i][j] 表示第 i 个点设在 j 位置的答案

dp[i][j] = min(dp[i - 1][t] + w(t, j))

2 1
3 3
10 2

59
*/
```

[AC record](https://www.luogu.com.cn/record/229216320)

---

