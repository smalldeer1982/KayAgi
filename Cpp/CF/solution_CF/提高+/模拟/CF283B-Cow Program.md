# Cow Program

## 题目描述

Farmer John has just given the cows a program to play with! The program contains two integer variables, $ x $ and $ y $ , and performs the following operations on a sequence $ a_{1},a_{2},...,a_{n} $ of positive integers:

1. Initially, $ x=1 $ and $ y=0 $ . If, after any step, $ x<=0 $ or $ x&gt;n $ , the program immediately terminates.
2. The program increases both $ x $ and $ y $ by a value equal to $ a_{x} $ simultaneously.
3. The program now increases $ y $ by $ a_{x} $ while decreasing $ x $ by $ a_{x} $ .
4. The program executes steps 2 and 3 (first step 2, then step 3) repeatedly until it terminates (it may never terminate). So, the sequence of executed steps may start with: step 2, step 3, step 2, step 3, step 2 and so on.

The cows are not very good at arithmetic though, and they want to see how the program works. Please help them!

You are given the sequence $ a_{2},a_{3},...,a_{n} $ . Suppose for each $ i $ $ (1<=i<=n-1) $ we run the program on the sequence $ i,a_{2},a_{3},...,a_{n} $ . For each such run output the final value of $ y $ if the program terminates or -1 if it does not terminate.

## 说明/提示

In the first sample

1. For $ i=1, $ $ x $ becomes ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF283B/c3adc91e6a416ef5e3a3efeecae9ab6c709eb6f3.png) and $ y $ becomes $ 1+2=3 $ .
2. For $ i=2, $ $ x $ becomes ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF283B/25cfed609f3dc5147a57c7f4ac4fe5ab1317ed75.png) and $ y $ becomes $ 2+4=6. $
3. For $ i=3, $ $ x $ becomes ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF283B/3160e5591c358bc094f55b65bd30a378832bf854.png) and $ y $ becomes $ 3+1+4=8. $

## 样例 #1

### 输入

```
4
2 4 1
```

### 输出

```
3
6
8
```

## 样例 #2

### 输入

```
3
1 2
```

### 输出

```
-1
-1
```

# 题解

## 作者：Juanzhang (赞：4)

**思路：**

- **记**忆化**搜**索

$dp_{sel,i}$表示到$i$点时，$sel$为$0$ —— $step2$，$sel$为$1$ —— $step3$

**状态转移方程：**

$dp_{sel,i}=dp_{!sel,i+(sel?-a[x]:a[x])}$

此题的难点在于，如何利用以前的计算判圈

于是可用两个数组记录是否出发过，是否已回去的$01$状态

**代码** ~~略压行~~

``` cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn = 2e5 + 10;
ll dp[2][maxn];
int n, a[maxn];
bool u[2][maxn], v[2][maxn];

ll dfs(int x, int sel) {
	if (x < 1 || x > n) {
		return 0;
	}
	if (u[sel][x]) {
		return v[sel][x] ? dp[sel][x] : -1;
	}
	u[sel][x] = 1;
	ll t = dfs(x + (sel ? -a[x] : a[x]), sel ^ 1);
	v[sel][x] = 1;
	return dp[sel][x] = (~t ? t + a[x] : t);
}

int main() {
	scanf("%d", &n);
	for (int i = 2; i <= n; i++) {
		scanf("%d", a + i);
	}
	for (int i = 1; i < n; i++) {
		a[1] = i;
		printf("%I64d\n", ~dfs(a[1] + 1, 1) ? dp[1][a[1] + 1] + a[1] : -1);
	}
	return 0;
}
```

当然，此题也可以$bfs$，类似于**最短路**的思想，不断更新。此处不做过多介绍

**代码**

``` cpp
#include <bits/stdc++.h>
using namespace std;

#define fir first
#define sec second

typedef long long ll;
typedef pair <int, int> pii;
const int maxn = 2e5 + 10;
ll dp[2][maxn];
int n, a[maxn];

vector <pii> e[2][maxn], q;

int main() {
	dp[0][1] = -1;
	scanf("%d", &n);
	for (int i = 2; i <= n; i++) {
		scanf("%d", a + i);
	}
	for (int i = 2; i <= n; i++) {
		if (i - a[i] < 1) {
			dp[0][i] = a[i];
			q.push_back(make_pair(0, i));
		} else {
			e[1][i - a[i]].push_back(make_pair(0, i));
		}
		if (i + a[i] > n) {
			dp[1][i] = a[i];
			q.push_back(make_pair(1, i));
		} else {
			e[0][i + a[i]].push_back(make_pair(1, i));
		}
	}
	for (int i = 0; i < q.size(); i++) {
		const pii u = q[i];
		for (int j = 0; j < e[u.fir][u.sec].size(); j++) {
			const pii v = e[u.fir][u.sec][j];
			q.push_back(v);
			dp[v.fir][v.sec] = dp[u.fir][u.sec] + a[v.sec];
		}
	}
	for (int i = 1; i < n; i++) {
		if (!dp[0][i + 1]) {
			puts("-1");
		} else {
			printf("%I64d\n", dp[0][i + 1] + i);
		}
	}
	return 0;
}
```

---

## 作者：灵茶山艾府 (赞：3)

记忆化搜索，需要一点技巧。

定义 $dp[x][d]$ 表示当前位置为 $x$，且当前执行的是第二个操作($d=1$)或第三个操作($d=0$) 的最终 $y$ 值(死循环时为 $-1$)。

这样定义后就可以记忆化搜索了，$d=1$ 时 `x+=a[x]`，$d=0$ 时 `x-=a[x]`，然后根据 $x$ 的范围决定是返回还是递归，在这个过程中累加并记录 $y$ 的值。

由于可能在递归的中途，访问到先前的位置，所以可以在递归前设置 $dp[x][d]$ 的值为 $-1$，避免无限递归。

AC 代码（Golang）:

```go
package main

import (
	"bufio"
	. "fmt"
	"os"
)

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var n int
	Fscan(in, &n)
	a := make([]int, n+1)
	for i := 2; i <= n; i++ {
		Fscan(in, &a[i])
	}

	dp := make([][2]int64, n+1)
	var f func(int, int) int64
	f = func(x, d int) (y int64) {
		if x > 1 {
			dv := &dp[x][d]
			if *dv != 0 {
				return *dv
			}
			*dv = -1 // 关键：递归之前，先设置 dp 值为 -1，这样若后面再次递归到同样的位置，可以直接返回 -1
			defer func() { *dv = y }()
		}
		y = int64(a[x])
		if d == 1 { // 第二步
			x += a[x]
		} else { // 第三步
			x -= a[x]
		}
		if x == 1 { // 死循环
			return -1
		}
		if x <= 0 || x > n { // 超出边界
			return y
		}
		yy := f(x, d^1)
		if yy == -1 { // 死循环
			return -1
		}
		return y + yy
	}
	for a[1] = 1; a[1] < n; a[1]++ {
		Fprintln(out, f(1, 1))
	}
}
```


---

## 作者：a_small_penguin (赞：2)

什么是 DP？我不知道，我只知道什么叫做暴力。

这道题是一道 DP 的板题，但我不善 DP，于是就用暴力淼过去了。

对于每个查询，就为从 $1$ 跳过去的点多出的贡献再加上 $1$ 的点值。

对于暴力的 dfs，传入一个二元组 $(x, d)$，代表当到了 $x$，该进行操作 $d + 1$ 时的状态，返回值是到这个状态下多出的贡献。

直接爆搜是不能过的，所以我们应该使用记忆化搜索。

### 对于一些特判：

如果二元组 $(x, d)$ 这个状态已经访问过了，且这个状态还没有返回值，那么就一定有环，返回 $-\infty$。

如果二元组 $(x, d)$ 已经访问过且有值，那么直接返回值。

如果 $x < 1 \text{或} n < x$ 那么就直接返回 $0$，因为到这里就结束，不会有多余的贡献。

如果 $x = 1$ 那么就一定有环，返回 $-\infty$。

### 对于其余的情况

$$
dfs(x, d) = \begin{cases}
  dfs(x + a_x, d) + a_x & d = 0 \\
  dfs(x - a_x, d) + a_x & d = 1
\end{cases}
$$


Code：
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define inf64 0x7fffffffffffffff

int n;
int a[200009];
int f[200009][2];
bool c[200009][2];

inline long long dfs(int x, int d) {
	if(x == 1) return -inf64;
	if(x < 1 || x > n) return 0;
	if(f[x][d]) return f[x][d];
	if(c[x][d]) return -inf64;

	if(d)
		c[x][d] = 1, f[x][d] = dfs(x - a[x], 0) + a[x];
	else
		c[x][d] = 1, f[x][d] = dfs(x + a[x], 1) + a[x];
	return f[x][d];
}

signed main() {

	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n;
	for(int i = 2; i <= n; i++)
		cin >> a[i];
	for(int i = 2; i <= n; i++)
		f[i][1] = dfs(i, 1);
	for(int i = 2; i <= n; i++)
		if(f[i][1] < 0) cout << -1 << "\n";
		else cout << f[i][1] + i - 1 << "\n";

	return 0;

}
```

---

