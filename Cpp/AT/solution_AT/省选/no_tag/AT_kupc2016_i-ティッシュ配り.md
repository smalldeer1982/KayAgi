# ティッシュ配り

## 题目描述

[problemUrl]: https://atcoder.jp/contests/kupc2016/tasks/kupc2016_i

Eli- $ 1 $ さんは仕事時間が $ N $ 秒のティッシュ配りのバイトをすることにした. Eli- $ 1 $ さんは特殊能力である分身を利用してなるべく多くのティッシュを配ることにした. Eli- $ gen $ さんができる行動は次の 2 種類である.

- $ gen\ \times\ C $ ( $ C $ は分身にかかる時間の係数) 秒をかけてEli- $ gen $ さんとEli- $ (gen\ +\ 1) $ さんの 2 人に分身する.
- 世代( $ =\ gen $ )に関わらず $ 1 $ 秒をかけてちょうど $ 1 $ 個のティッシュを配る.

配りながら分身するということはできない. $ N $ , $ C $ が与えられたとき, Eli- $ 1 $ さんが分身と合計で最大何個のティッシュを配ることができるかを求めよ. ただし, 配れるティッシュの数は非常に大きくなることがあるため $ 1000000007 $ ($ =\ 10^9\ +\ 7 $) で割った余りを解答として出力せよ.

## 说明/提示

### 制約

- $ 1\ \leq\ Q\ \leq\ 100000\ =\ 10^5 $
- $ 1\ \leq\ N_q\ \leq\ 100000\ =\ 10^5 $
- $ 1\ \leq\ C_q\ \leq\ 20000\ =\ 2\ \times\ 10^4 $

### 部分点

 $ Q\ =\ 1 $ を満たすデータセットに正解した場合は $ 30 $ 点の部分点が与えられる.

追加制約のないデータセットに正解した場合は追加で $ 270 $ 点が与えられ，合計で $ 300 $ 点が得られる.

### Sample Explanation 1

$ 1 $ つめのクエリでは, 分身しないと $ 20 $ 個しか配れないところを, 分身後 $ 2 $ 人が $ 12 $ 個ずつ配ることで $ 24 $ 個配ることができ, これが最大である. $ 2 $ つめのクエリでは, 分身しても $ 2 $ 人がそれぞれ $ 8 $ 個ずつしか配れないため, 分身せずに $ 20 $ 個配るほうがよい.

### Sample Explanation 2

以下の図のようにすればよい. 黒線は分身を表し, 赤線はティッシュを配ることを表している. !\[\](/img/other/kupc2016/sushi/sample2.png) このケースは部分点の追加制約を満たす.

### Sample Explanation 3

$ 1000000007 $ ( $ 10^9\ +\ 7 $ ) で割った余りを出力する必要があることに注意せよ. このケースは部分点の追加制約を満たす.

## 样例 #1

### 输入

```
2
20 8
20 12```

### 输出

```
24
20```

## 样例 #2

### 输入

```
1
20 3```

### 输出

```
67```

## 样例 #3

### 输入

```
1
200 1```

### 输出

```
148322100```

# 题解

## 作者：2huk (赞：6)

考虑只有一次询问怎么做。

考虑 DP。设 $f(i, j)$ 表示若最开始有一个等级为 $i$ 的机器人，在 $j$ 秒内最多能发多少张传单。转移有：

$$
f(i,j)=\max (j, f(i,j-ic)+f(i+1,j-ic))
$$

表示接下来这个机器人是否复制至少一个。当然后者能转移的前提是 $j \ge ic$。答案为 $f(1,n)$。

不难发现一个机器人最终的等级不会很大。升到某个级别的所花事件是一个等差数列，也就是说它的等级最大 $\sqrt n$。所以第一维是 $\mathcal O(\sqrt n)$ 的。所以一次询问的复杂度是 $\mathcal O(n \sqrt n)$。

对吗？

注意到 $f$ 的值会很大（所以题目要求取模），这个 $\max$ 不好做。写高精度复杂度肯定不对。因此考虑挖掘一些性质，避开这个比较，直接转移。

注意到，让等级为 $i$ 的机器人再复制一个后，答案**至少**为 $2(j-ci)$，即这两个不会再复制，而是一直发传单到结束。

那么如果 $2(j-ci) \ge j$，即复制一个一定不劣于不复制，那么一定选择复制。换言之 $f(i,j)$ 会从 $f(i,j-ci)+f(i+1,j-ci)$ 转移过来。

否则如果 $j > 2(j-ci)$，是否不复制一定最优呢？

是的。因为这等价于 $j < 2ci$，其意义是**剩下的 $j$ 时间内无法复制 $\ge 2$ 个机器人**，也就是最多复制 $1$ 个。而复制 $1$ 个不优，所以就不复制了。换言之 $f(i,j)$ 会从 $f(i,j-ci)+f(i+1,j-ci)$ 转移过来。

这样就解决了一次询问。

$$
f(i,j) = \begin{cases}
f(i,j-ci)+f(i+1,j-ci) & j < 2ci \\
j & j \ge 2ci
\end{cases}
$$

---

考虑多次询问。

注意到最终能直接或间接转移到 $f(i,j)$ 的所有状态 $f(i',j')$ 一定满足 $j \equiv j' \pmod c$。这里有点类似完全背包。

所以重新令 $f'(i,j)=f(i,jc)$。不难发现：

$$
f'(i,j) = \begin{cases}
f'(i,j-i)+f'(i+1,j-i) & j < 2i \\
j & j \ge 2i
\end{cases}
$$

所以答案就是 $f'(1,\lfloor n/c \rfloor) \times c$。乘 $c$ 的原因是第二种转移时状态值不对。

显然不对。因为还剩 $n \bmod c$ 的时间我们没有考虑。显然在这点时间里没有机器人能来的及再复制。因此我们记录 $g(i,j)$ 表示考虑一个等级为 $i$ 的机器人在 $j$ 个时间内传单数量最多的情况下，最多复制几个机器人（包括自己）。

然后答案为 $f'(1,\lfloor n/c \rfloor) \times c + g(1,\lfloor n/c \rfloor) \times (n \bmod c)$。

```cpp
// Problem: 
//     ティッシュ配り
//   
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_kupc2016_i
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

// #define tests
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, P = 1e9 + 7;

int q, n, c;
int f[500][N], g[500][N];

void solve() {
	for (int i = 498; i; -- i )
		for (int j = 1; j < N; ++ j ) {
			if (j >= i * 2) {
				// 生更好
				f[i][j] = (f[i + 1][j - i] + f[i][j - i]) % P;
				g[i][j] = (g[i + 1][j - i] + g[i][j - i]) % P;
			} else {
				f[i][j] = j;
				g[i][j] = 1;
			}
		}
	
	cin >> q;
	while (q -- ) {
		cin >> n >> c;
		cout << (1ll * f[1][n / c] * c + 1ll * g[1][n / c] * (n % c)) % P << '\n';
	}
}

signed main() {
	freopen("robot.in", "r", stdin);
	freopen("robot.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int T = 1;
#ifdef tests
	cin >> T;
#endif
	while (T -- ) solve();
	return 0;
}
```

---

## 作者：Chenyanxi0829 (赞：3)

发现人的最优策略肯定是先一直生成最后再一直发传单，接着发现一个人会生成当且仅当 $2c\times i\le$ 剩下的时间，于是推出最后 $n\bmod c$ 的时间所有人都会发传单，于是把时间每 $c$ 秒分一段就可以直接转化成求 $c=1$ 时的答案。设 $f_{i,j}$ 表示编号为 $i$ 的人只剩 $j$ 的时间最多发多少传单，转移按照之前的结论如果 $2i\le j$，$f_{i,j}\gets f_{i,j-i}+f_{i+1,j-i}$，否则 $f_{i,j}\gets j$，由于还需要计算最后 $n\bmod c$ 发的传单，还需要顺带计算 $g_{i,j}$ 表示这一过程中的总人数。这时复杂度为 $O(N^2)$，其中 $N$ 为 $n$ 的最大值，但是发现编号为 $i$ 的人最早的出现时间为 $\frac{i(i-1)}{2}$，所以编号最大值是 $O(\sqrt N)$ 级别的，就没问题了。

### 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 1e5 + 5, B = 450, mod = 1e9 + 7;

int q, dp[B][kMaxN], c[B][kMaxN], t;

inline void A(int &x, int y) { x += y, x >= mod && (x -= mod); }

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  dp[1][0] = 1;
  for (int i = 1; i * (i - 1) / 2 <= 100000; t = i, i++) {
  }
  for (int i = t; i >= 1; i--) {
    for (int j = 0; j + i * (i - 1) / 2 <= 100000; j++) {
      j >= 2 * i ? (dp[i][j] = dp[i + 1][j - i], A(dp[i][j], dp[i][j - i]), c[i][j] = c[i + 1][j - i], A(c[i][j], c[i][j - i]), 0) : (dp[i][j] = j, c[i][j] = 1);
    }
  }
  cin >> q;
  for (int i = 1, n, z; i <= q; i++) {
    cin >> n >> z, cout << (1ll * z * dp[1][n / z] % mod + 1ll * n % z * c[1][n / z]) % mod << '\n';
  }
  return 0;
}
```

---

## 作者：xukehg (赞：2)

很好的题！

先考虑 $c = 1$ 如何处理。很明显每个机器人之间可以独立，且先造机器人再发传单的策略一定不劣。设 $f_{i,j}$ 表示 $i$ 号机器人在 $j$ 秒内最多能发几张传单。如果 $2 \times (i - j) < i$，即造机器人没有好处，我们就不造机器人，$f_{i,j} = j$。否则我们就造一个机器人出来，让生产的机器人在 $i - j$ 秒内收益最大化，即 $f_{i,j} = f_{i,i - j} + f_{i + 1,i - j}$。注意到制造 $i$ 型机器人至少要 $\frac{i \times (i - 1)}{2}$ 秒，故上限为 $\sqrt{n}$ 级别。最终答案为 $f_{1,n}$。

现在考虑 $c \neq 1$ 的情况，显然有贡献 $f_{1,n / c} \times c$。但显然不对，因为还有 $n \bmod c$ 秒。我们可以记 $g_{i,j}$ 表示 $f_{i,j}$ 取最大时有多少个机器人，则答案为 $f_{1,n / c} \times c + g_{1,n / c} \times (n \bmod c)$。有没有可能少发传单，多造一些机器人更优呢？答案是不能。因为多早一个机器人至少要 $c$ 秒，而此时已经不足 $c$ 秒，收不回成本，故答案有正确性。

[记录。](https://atcoder.jp/contests/kupc2016/submissions/59861608)

---

