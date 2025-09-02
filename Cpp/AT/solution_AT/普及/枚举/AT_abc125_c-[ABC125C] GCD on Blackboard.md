# [ABC125C] GCD on Blackboard

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc125/tasks/abc125_c

$ N $ 個の整数 $ A_1,\ A_2,\ ...,\ A_N $ が黒板に書かれています。

あなたはこの中から整数を $ 1 $ つ選んで、$ 1 $ 以上 $ 10^9 $ 以下の好きな整数に書き換えます。

元の整数と同じ整数に書き換えても構いません。

書き換えた後の $ N $ 個の整数の最大公約数の最大値を求めてください。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $

### Sample Explanation 1

$ 7 $ を $ 4 $ に書き換えると $ 3 $ つの整数の最大公約数は $ 2 $ となり、これが最大です。

### Sample Explanation 3

元の整数と同じ整数に書き換えることも可能です。

## 样例 #1

### 输入

```
3
7 6 8```

### 输出

```
2```

## 样例 #2

### 输入

```
3
12 15 18```

### 输出

```
6```

## 样例 #3

### 输入

```
2
1000000000 1000000000```

### 输出

```
1000000000```

# 题解

## 作者：SpeedStar (赞：7)

#### 算法分析

本题的做法和[双子序列最大和](https://www.luogu.com.cn/problem/P2642)这题做法比较类似。本题也就是挖掉某个数，然后求剩余数的最大公约数，使得最大公约数尽可能的大。如果暴力的话，必然是过不了。然后我们可以考虑优化：先预处理出每个数两边的 $gcd$，即 $l[i]$ 和 $r[i]$，而 $l[i+1]=gcd(l[i],a[i])$，$r[i-1]=gcd(r[i],a[i])$，
然后枚举每个数，通过求 $gcd(l[i], r[i])$ 来更新答案。


#### C++ 代码

```cpp
#include <bits/stdc++.h>

using std::cin;
using std::cout;
using std::vector;
using std::gcd;
using std::max;

int main() {
	int n;
	cin >> n;
	
	vector<int> a(n);
	for (int i = 0; i < n; ++i) cin >> a[i];
	
	vector<int> l(n), r(n);
	for (int i = 0; i < n - 1; ++i) l[i + 1] = gcd(l[i], a[i]);
	for (int i = n - 1; i >= 1; --i) r[i - 1] = gcd(r[i], a[i]);
	
	int ans = 1;
	for (int i = 0; i < n; ++i) ans = max(ans, gcd(l[i], r[i]));
	cout << ans << '\n';
	
	return 0;
}
```


---

