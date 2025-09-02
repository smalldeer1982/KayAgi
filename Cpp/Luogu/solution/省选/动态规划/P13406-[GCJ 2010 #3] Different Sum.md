# [GCJ 2010 #3] Different Sum

## 题目描述

我们为 Google Code Jam 2010 设计了一个很棒的问题，涉及选手们解决一个“字谜算式”（cryptarithm）。但我们需要你帮助生成该问题的测试用例；更准确地说，我们关心的是那些足够“好”（具体定义见下文）以便转换为字谜算式的加法等式。

你不需要了解什么是字谜算式来解决本题，因为我们会提供所有必要的定义。我们将字谜算式定义为如下格式的加法等式：所有被加数（加数）和结果（和）都右对齐，如下所示：

```
124
 31
 25
---
180
```

此外，对于字谜算式的每一列，所有加数在该列上的数字都必须互不相同。注意，这个约束不包括结果（和）。例如，上述等式的第一列只有数字 $1$，第二列有数字 $2,3$ 和 $2$，第三列有数字 $4, 1$ 和 $5$。这个等式不是一个字谜算式，因为第二列出现了两个 $2$。但如果我们将最后一个加数替换为 $15$（和替换为 $170$），那么它就是一个字谜算式。

注意，字谜算式中的加数都为正数，且不允许有前导零。加数的顺序不重要（换句话说，仅加数顺序不同的两个等式被视为相同的等式）。

上面的例子是在 $10$ 进制下的，但我们也对其他进制下的字谜算式感兴趣。注意，在 $b$ 进制下，“数字”可以是 $0$ 到 $b-1$ 之间的任意整数。下面是一个 $23$ 进制下的字谜算式：

```
 I7B
 JJJ
----
1F47
```

在这个例子中，"I" 代表数字 $18$，"B" 代表数字 $11$，"J" 代表数字 $19$，"F" 代表数字 $15$。用十进制表示，这两个加数分别为 $18\times 23^2 + 7\times 23 + 11 = 9694$ 和 $19\times 23^2 + 19\times 23 + 19 = 10507$，和为 $1\times 23^3 + 15\times 23^2 + 4\times 23 + 7 = 20201$。请注意，用字母表示 $10$ 及以上的数字只是为了例子更清晰；在本题中如何表示这些数字并不重要。

给定和 $N$ 以及进制 $B$，有多少个不同的字谜算式？

由于答案可能非常大，请输出对 $1000000007$ 取模的结果。

## 说明/提示

**样例解释**

以下是和为 $6$ 的 $4$ 个字谜算式：

```
6   1   2   1
-   5   4   2
6   -   -   3
    6   6   -
            6
```

以下是在 $4$ 进制下和为 $8=(20)_4$ 的 $4$ 个字谜算式：

```
20   11   13   10
--    3    1    3
20   --   --    1
     20   20   --
               20
```

**数据范围**

- $1 \leq T \leq 20$。

**小数据范围（7 分，测试点 1 - 可见）**

- 时间限制：~~30~~ 3 秒。
- $1 \leq N \leq 100$。
- $2 \leq B \leq 10$。

**大数据范围（22 分，测试点 2 - 隐藏）**

- 时间限制：~~120~~ 20 秒。
- $1 \leq N \leq 10^{18}$。
- $2 \leq B \leq 70$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
6 10
8 4```

### 输出

```
Case #1: 4
Case #2: 4```

# 题解

## 作者：CuteChat (赞：3)

复杂度 $O(B^4 + B^3 \log_B N)$ 的做法，似乎爆标了，~~虽然已经过去了 15 年~~。

## 题解

### 初步观察

首先需要有一个初步的思考方向，题目说列上的每一个数位不能相同，那么肯定是以列为一个大单位去做 dp，并且肯定是从低位到高位。

记 $\operatorname{dp}(c, j, n)$ 表示目前在第 $c$ 列，目前加法进位是 $j$，有 $n$ 个加数的情况下竖式的总数。

这时就需要决定当前这一列要怎么填写数字，假设填写的数字总和是 $s$，那么当前这一列对应的求和结果就是 $(s + j) \bmod B$，这个结果应该是确定的，因为输入告诉了结果的每一位，而唯一会变的是 $\lfloor\dfrac{s + j}{B}\rfloor$，也就是下一列的进位。

因此如果假设下一列进位是 $j'$，$N$ 的第 $c$ 位是 $d_c$，那么当前这一列的数字和就应该是 $j' \times B + d_c - j$。

不过此时存在一个问题，就是转到下一列时，有一些行是不用填写数字的，而且一旦有一行没有填写数字，那么这一行以后就永远填写不了数字了，就好像是从整个竖式中消失了一样。而具体消失了哪几个行是不知道的，是需要枚举的。

这样，$\operatorname{dp}(c, j, n)$ 的转移的基本框架就出来了，需要枚举一个数字表示新的进位，记作 $j'$，然后还需要枚举一个数字表示下一列有多少行实际的数字，记作 $n'$，于是就可以从 $\operatorname{dp}(c+1,j',n')$ 转移过来。

### 转移系数

具体的转移系数有一点复杂，因为我们能发现一个问题，那就是如果有一行数字在第 $c$ 列填写了一个数字 $0$，而恰好在第 $c+1$ 列又没有数字了，这样这个数字就被添上了一个前导零，就不合法了，因此对于数字 $0$ 需要分类讨论。

如果这一列不填 $0$，那么转移系数就是要找到从 $[1,B)$ 的所有整数中不重复选择 $n$ 个数满足和为 $j' \times B + d_c - j$ 的方案数，把这个数求出来后，当前列的方案数量就出来了，但是还需要从当前的 $n$ 行保留 $n'$ 行，而要保留 $n'$ 行的方案数其实应该是 $\dfrac{n!}{(n-n')!}$，这两者相乘就是转移系数。

:::info[为什么不是 $\dbinom{n}{n'}$？]{open}
如果要避免算重，就要保证当前列填写的数字一定都是有序的，具体的一定是从整个竖式最上面的数字到最下面的数字中，第 $c$ 位一定要是从小到大递增的。

如果算出来了从 $[1,B)$ 的所有整数中选择 $n$ 个数满足和为 $j' \times B + d_c - j$ 的方案数，那么就把这 $n$ 个数字一个一个填上去即可。

对于下一位，自然是需要从 $n$ 行数中选择 $n'$ 行出来，但是在选择 $n'$ 行出来后，是可以任意决这 $n'$ 行在第 $c+1$ 位的大小顺序的，因此就是 $\dfrac{n!}{(n-n')!}$。这些竖式都一定是不同的。

下文同理。
:::

如果要填 $0$ 这个数字，这时候显然 $0$ 只会被填一次，然后还要要求这个数字一定要被选在枚举的 $n'$ 个数字中，此时的选择方案数量就是 $\dfrac{(n-1)!}{(n-n')!}\times n'$，组合意义显然，此处不赘述，然后只需要从 $[1,B)$ 的所有整数中选 $n-1$ 个数填上去即可。

### 收尾

此时就只剩下了最后一个问题，从 $[1,B)$ 的所有整数中选 $x$ 个数，满足和为 $s$ 的方案数。这种问题就很好解决，设 $\operatorname{cnt}(n,s,x)$ 表示从 $[n,B)$ 的所有整数选 $x$ 个数，要求和为 $s$，那么转移就两种，一种是选择 $n$ 这个数，另一种是不选 $n$ 这个数，因此 $\operatorname{cnt}(n,s,x)=\operatorname{cnt}(n+1,s-n,x-1)+\operatorname{cnt}(n+1,s,x)$，边界 $\operatorname{cnt}(B,0,0)=1$。

这样，$\operatorname{dp}(c,j,n)$ 的转移就很明显了：

$$\operatorname{dp}(c+1,j',n') \times \dfrac{n!}{(n-n')!}\times \operatorname{cnt}(1,j' \times B+d_c-j,n)\newline
{}+\operatorname{dp}(c+1,j',n') \times \dfrac{(n-1)!}{(n-n')!}\times n'\times \operatorname{cnt}(1,j' \times B+d_c-j,n-1)\newline
\to \operatorname{dp}(c,j,n)$$

边界 $\operatorname{dp}(\text{Maxdig}+1,0,0)=1$，$\text{Maxdig}$ 是 $N$ 的最大位数。一切准备就绪后，最终的答案就是 $\displaystyle\sum_{i=1}^{B} \operatorname{dp}(1,0,i)$。

于是，我们就终于得到了一个 $O(B^4 \log_B{N})$ 的做法啦！

### 代码

需要特判一些细节，例如转移转到负数下标的要特判，然后因为这个代码是直接从记忆化搜索改过来的，因此可能有点丑（包括但不限于正着 dp 倒着转的操作）。

:::info[$O(B^4\log_B{N})$ 参考代码]

```cpp lines=46-52
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int p = 1e9 + 7;
int n, b, digs[71], digt, frc[128], inv[128];
int dp2[71][71*71][71];
int dp1[71][71][71];
pair<int, int> sm1[71][71][71];
int C(int x, int y) {
	if (x < y || y < 0 || x < 0) return 0;
	return frc[x] * inv[y] % p * inv[x - y] % p;
}
int A(int x, int y) {
	if (x < y || y < 0 || x < 0) return 0;
	return frc[x] * inv[x - y] % p;
}

void solve(int tc) {
	cin >> n >> b;
	digt = 0;
	while (n) {
		digs[++digt] = n % b;
		n /= b;
	}
	for (int now = b; now >= 1; --now) {
		for (int sums = 0; sums <= b * b; ++sums) {
			for (int nums = 0; nums <= b; ++nums) {
				if (now == b) dp2[now][sums][nums] = (sums == 0 && nums == 0);
				else {
					int ans = dp2[now + 1][sums][nums];
					if (sums >= now && nums) ans += dp2[now + 1][sums - now][nums - 1];
					dp2[now][sums][nums] = ans % p;
				}
			}
		}
	}
	for (int col = digt + 1; col >= 1; --col) {
		for (int jw = 0; jw < b; ++jw) {
			for (int nums = 0; nums <= b; ++nums) {
				if (col == digt + 1) {	
					dp1[col][jw][nums] = (jw == 0 && nums == 0);
				} else {
					int ans = 0;
					for (int njw = 0; njw < b; ++njw) {
						if (digs[col] - jw + njw * b < 0) continue;
						int ans1 = 0, ans2 = 0; // ans1 表示不填零方案数，ans2 表示填 0 方案数
						for (int nnum = 0; nnum <= nums; ++nnum) {
							ans1 += dp1[col + 1][njw][nnum] * A(nums, nnum) % p;
							ans2 += dp1[col + 1][njw][nnum] * A(nums - 1, nnum - 1) % p * nnum % p;
						}
				        ans1 %= p;
				        ans2 %= p;
						ans += ans1 * dp2[1][digs[col] - jw + njw * b][nums] % p; // 乘上当前列填数方案数即可
						if (nums) ans += ans2 * dp2[1][digs[col] - jw + njw * b][nums - 1] % p;
						ans %= p;
					}
					dp1[col][jw][nums] = ans;
				}
			}
		}
	}
	int ans = 0;
	for (int ns = 1; ns <= b; ++ns) {
		ans += dp1[1][0][ns] % p;
	}
	cout << ans % p << "\n";
}
 
signed main() {
	ios::sync_with_stdio(0); cin.tie(0);
	frc[0] = frc[1] = inv[0] = inv[1] = 1;
	for (int i = 2; i <= 100; ++i) {
		frc[i] = frc[i - 1] * i % p;
		inv[i] = (p - p / i) * inv[p % i] % p;
	}
	for (int i = 2; i <= 100; ++i) {
		inv[i] = inv[i - 1] * inv[i] % p;
	}
	int tc; cin >> tc;
	for (int i = 1; i <= tc; ++i) {
		cout << "Case #" << i << ": ";
		solve(i);
	}
	return 0;
}
```
:::

### 优化

然而，上面这一份代码是可以被极限数据卡到约 $30\text{s}$ 左右，~~可恶的~~洛谷搬题人只给了 $20\text{s}$ 时限，在 QOJ 上也有点吃力。为了完美通过这道题，需要优化 $\operatorname{dp}(c,j,n)$ 这一部分。

可以发现 $\operatorname{cnt}(1,j' \times B+d_c-j,n-1)$ 和 $\operatorname{cnt}(1,j' \times B+d_c-j,n)$ 这个部分和 $n'$ 没有关系，所以可以单独提出来，而 $\operatorname{dp}(c+1,j',n') \times \dfrac{(n-1)!}{(n-n')!}\times n'$ 和 $\operatorname{dp}(c+1,j',n') \times \dfrac{n!}{(n-n')!}$ 这两个部分和预先枚举的 $j$ 是没有关系的，所以这一部分是可以直接预处理的，没有必要重复计算。

具体可以参考上面代码的高亮部分，可以发现这一片段都和 `jw` 变量（对应枚举的 $j$）没有任何关系，因此随便上一些手法进行预处理或者记忆化即可。

因此部分被优化至了 $O(B^3 \log_{B} N)$，总时间复杂度 $O(B^4 + B^3 \log_B N)$。

:::info[$O(B^4 + B^3 \log_B N)$ 参考代码]
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int p = 1e9 + 7;
int n, b, digs[71], digt, frc[128], inv[128];
int dp2[71][71*71][71];
int dp1[71][71][71];
pair<int, int> sm1[71][71][71];
int C(int x, int y) {
	if (x < y || y < 0 || x < 0) return 0;
	return frc[x] * inv[y] % p * inv[x - y] % p;
}
int A(int x, int y) {
	if (x < y || y < 0 || x < 0) return 0;
	return frc[x] * inv[x - y] % p;
}

void solve(int tc) {
	cin >> n >> b;
	digt = 0;
	while (n) {
		digs[++digt] = n % b;
		n /= b;
	}
	for (int now = b; now >= 1; --now) {
		for (int sums = 0; sums <= b * b; ++sums) {
			for (int nums = 0; nums <= b; ++nums) {
				if (now == b) dp2[now][sums][nums] = (sums == 0 && nums == 0);
				else {
					int ans = dp2[now + 1][sums][nums];
					if (sums >= now && nums) ans += dp2[now + 1][sums - now][nums - 1];
					dp2[now][sums][nums] = ans % p;
				}
			}
		}
	}
	for (int col = digt + 1; col >= 1; --col) {
		if (col != digt + 1) {
			for (int njw = 0; njw < b; ++njw) {
				for (int nums = 0; nums <= b; ++nums) {
					int ans1 = 0, ans2 = 0;
					for (int nnum = 0; nnum <= nums; ++nnum) {
						ans1 += dp1[col + 1][njw][nnum] * A(nums, nnum) % p;
						ans2 += dp1[col + 1][njw][nnum] * A(nums - 1, nnum - 1) % p * nnum % p;
					}
					ans1 %= p;
					ans2 %= p; 
					sm1[col][njw][nums] = {ans1, ans2};
				}
			}
		}
		for (int jw = 0; jw < b; ++jw) {
			for (int nums = 0; nums <= b; ++nums) {
				if (col == digt + 1) {	
					dp1[col][jw][nums] = (jw == 0 && nums == 0);
				} else {
					int ans = 0;
					for (int njw = 0; njw < b; ++njw) {
						int ans1 = sm1[col][njw][nums].first, ans2 = sm1[col][njw][nums].second;
						if (digs[col] - jw + njw * b >= 0) {
							ans += ans1 * dp2[1][digs[col] - jw + njw * b][nums] % p;
							if (nums) ans += ans2 * dp2[1][digs[col] - jw + njw * b][nums - 1] % p;
						}
						ans %= p;
					}
					dp1[col][jw][nums] = ans;
				}
			}
		}
	}
	int ans = 0;
	for (int ns = 1; ns <= b; ++ns) {
		ans += dp1[1][0][ns] % p;
	}
	cout << ans % p << "\n";
}
 
signed main() {
	ios::sync_with_stdio(0); cin.tie(0);
	frc[0] = frc[1] = inv[0] = inv[1] = 1;
	for (int i = 2; i <= 100; ++i) {
		frc[i] = frc[i - 1] * i % p;
		inv[i] = (p - p / i) * inv[p % i] % p;
	}
	for (int i = 2; i <= 100; ++i) {
		inv[i] = inv[i - 1] * inv[i] % p;
	}
	int tc; cin >> tc;
	for (int i = 1; i <= tc; ++i) {
		cout << "Case #" << i << ": ";
		solve(i);
	}
	return 0;
}
```
:::

---

