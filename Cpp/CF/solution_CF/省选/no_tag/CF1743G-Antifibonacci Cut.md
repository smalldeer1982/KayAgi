# Antifibonacci Cut

## 题目描述

Note that the memory limit is unusual.

Let's define the sequence of Fibonacci strings as follows: $ f_0 $ is 0, $ f_1 $ is 1, $ f_i $ is $ f_{i-1} + f_{i-2} $ for $ i>1 $ ( $ + $ denotes the concatenation of two strings). So, for example, $ f_2 $ is 10, $ f_3 $ is 101, $ f_4 $ is 10110.

For a given string $ s $ , let's define $ g(s) $ as the number of ways to cut it into several (any number, possibly even just one) strings such that none of these strings are Fibonacci strings. For example, if $ s $ is 10110101, $ g(s) = 3 $ since there are three ways to cut it:

- 101101 $ + $ 01;
- 1011 $ + $ 0101;
- 1011 $ + $ 01 $ + $ 01.

You are given a sequence of strings $ s_1, s_2, \dots, s_n $ . Calculate $ g(s_1), g(s_1 + s_2), \dots, g(s_1 + s_2 + \ldots + s_n) $ . Since these values can be huge, print them modulo $ 998244353 $ .

## 样例 #1

### 输入

```
1
10110101```

### 输出

```
3```

## 样例 #2

### 输入

```
3
1111
1
0```

### 输出

```
2
3
3```

## 样例 #3

### 输入

```
6
10110101
100100001110
0000001100010001
1111
1001010100101010101001
000100000010101111```

### 输出

```
3
561
1466229
9887505
972227653
52128355```

# 题解

## 作者：Leasier (赞：5)

Update on 2024.11.10：感谢 [BigJoker]https://www.luogu.com.cn/user/364122)。

先无视空间限制，考虑空间限制正常的情况下怎么做。

首先可以处理出所有斐波那契串的哈希值以及 $\displaystyle\sum_{i = 1}^n s_i$ 的哈希值。

接下来考虑 dp，设 $dp_i$ 表示以 $i$ 结尾的串的无斐波那契拆分数。

初值：$dp_0 = 1$。

转移：$dp_i = \displaystyle\sum_{j = 0}^{i - 1} [[i + 1, j] \text{is not a fibonacci string}] f_j$。

注意到若设 $m = |\displaystyle\sum_{i = 1}^n s_i|$，则可能出现斐波那契串只有 $O(\log m)$ 个，于是我们记个前缀和并枚举可能的斐波那契串转移即可。时间复杂度为 $O(m \log m)$。

---

现在我们来考虑如何卡空间。

首先我们希望不再记录斐波那契串。单次求斐波那契串的某一项显然可以通过不断减去斐波那契数列中的某一项在 $O(\log m)$ 内求出。

另一方面，我们能不能不记录原串呢？其实是可以的，我们只需要记录当前可能的转移点 $j$，这里我们需要保证 $[j + 1, i]$ 为一个斐波那契串的**前缀**。由于 $fib_{i - 2}$ 为 $fib_i = fib_{i - 2} + fib_{i - 3} + fib_{i - 2}$ 的最长 border（原因如左），于是总项数是 $O(\log m)$ 级别的。从 $i \to i + 1$ 时，我们只需要删去不为前缀的数以及添加 $i$ 即可。

时间复杂度为 $O(m \log^2 m)$，空间复杂度为 $O(\log m + \max |s_i|)$。

代码：
```cpp
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 31, M = 1e3 + 7, mod = 998244353;
int fib[N + 7];
char s[M];
vector<pair<int, int> > v1, v2;

inline int get(int x){
	int t = x;
	for (int i = N; i >= 2; i--){
		if (x > fib[i]) x -= fib[i];
	}
	return x == 1;
}

inline bool check(int x){
	for (int i = 0; i <= N; i++){
		if (x == fib[i]) return true;
	}
	return false;
}

int main(){
	int n, pos = 0, sum = 1, lst;
	scanf("%d", &n);
	fib[0] = fib[1] = 1;
	for (int i = 2; i <= N; i++){
		fib[i] = fib[i - 1] + fib[i - 2];
	}
	v1.push_back(make_pair(0, 1));
	for (int i = 1; i <= n; i++){
		int len;
		scanf("%s", &s[1]);
		len = strlen(&s[1]);
		for (int j = 1; j <= len; j++){
			int size = v1.size(), ch = s[j] - '0';
			pos++;
			lst = sum;
			v2.clear();
			for (int k = 0; k < size; k++){
				int len = pos - v1[k].first;
				if (len == 1 || get(len) == ch){
					if (check(len)) lst = ((lst - v1[k].second) % mod + mod) % mod;
					if (ch == 1 || len > 1) v2.push_back(v1[k]);
				}
			}
			sum = (sum + lst) % mod;
			v2.push_back(make_pair(pos, lst));
			v1 = v2;
		}
		cout << lst << endl;
	}
	return 0;
}
```

---

## 作者：Alex_Wei (赞：2)

[CF1743G Antifibonacci Cut](https://www.luogu.com.cn/problem/CF1743G)

设 $m = \sum |s_i|$。

**VP 做法**：

考虑朴素 DP，设 $g_i$ 表示 $i$ 前缀方案数，则 $g_i = \sum\limits_{j < i} g_j - \sum\limits_{j\in S(i)} g_j$，其中 $S(i)$ 表示使得 $s[j + 1, i]$ 为斐波那契串的 $j$ 的集合。显然 $|S(i)| = \mathcal{O}(\log m)$，可直接 KMP 匹配，时间复杂度 $\mathcal{O}(m\log m)$，空间复杂度 $\mathcal{O}(m)$，无法接受。

考虑 KMP 的过程，如果 $f_i$ 在 $s$ 中出现，因为 $f_i = f_{i - 2} + f_{i - 3} + f_{i - 2}$ 的最长 border 为 $f_{i - 2}$（不会证明，感性理解），所以下一个最长匹配长度为 $|f_{i - 2}|$，这说明 $f_i$ 在 $s$ 中出现次数为 $\mathcal{O}(\frac m {|f_i|})$。据此考虑根号分治。

用 bitset 存下 $s$。

若 $f_i > \sqrt m$，则预处理出 $f_i$ 所有出现位置 $T$，标记 $-g_{j - |f_i|} \to g_j(j\in T)$，转移总数为 $\mathcal{O}(\sqrt m)$。

对于 $f_i < \sqrt m$，维护最近 $\sqrt m$ 个 DP 值即可。

用哈希维护字符串匹配，时间复杂度 $\mathcal{O}(m\log m)$，空间复杂度 $\mathcal{O}(\frac m w)$。[代码](https://codeforces.com/contest/1743/submission/183800601)。

**官方解法**：

对于任意 $i > 1$，一定有 $f_i$ 是 $f_{i + 1}$ 的前缀。因此，考虑 $f_{\infty}$，每个产生 $-g_j\to g_i$ 的 $s[j + 1, i]$ 一定是它的前缀。

假设 $s[j + 1, i]$ 是 $f_{\infty}$ 的前缀，$s[j' + 1, i](j < j')$ 同样是 $f_{\infty}$ 的前缀，则 $s[j' + 1, i]$ 为 $s[j + 1, i]$ 的 border。所有这样的 $s[j + 1, i]$ 之间的 border 关系形成全序关系，可用一条链描述，而 $f_{\infty}$ 每个前缀的最长 border 不会太长（不会证明，感性理解），所以这条链的长度为 $\mathcal{O}(\log m)$。因此，我们可以直接维护所有 $j$ 及其对应 $g_j$。

需要 $\mathcal{O}(m\log m)$ 次求出 $f_{\infty}$ 的第 $i$ 个字符，及判断一个数是否为斐波那契数。预处理时间 $\mathcal{O}(m\log m)$ 空间 $\mathcal{O}(\frac m w)$，[代码](https://codeforces.com/contest/1743/submission/183815857)。不预处理做到时间 $\mathcal{O}(m\log ^ 2 m)$，空间 $\mathcal{O}(\log m)$，[代码](https://codeforces.com/contest/1743/submission/183814902)。

---

