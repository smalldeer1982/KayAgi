# Coins

## 题目描述

You have unlimited number of coins with values $ 1, 2, \ldots, n $ . You want to select some set of coins having the total value of $ S $ .

It is allowed to have multiple coins with the same value in the set. What is the minimum number of coins required to get sum $ S $ ?

## 说明/提示

In the first example, some of the possible ways to get sum $ 11 $ with $ 3 $ coins are:

- $ (3, 4, 4) $
- $ (2, 4, 5) $
- $ (1, 5, 5) $
- $ (3, 3, 5) $

It is impossible to get sum $ 11 $ with less than $ 3 $ coins.

In the second example, some of the possible ways to get sum $ 16 $ with $ 3 $ coins are:

- $ (5, 5, 6) $
- $ (4, 6, 6) $

It is impossible to get sum $ 16 $ with less than $ 3 $ coins.

## 样例 #1

### 输入

```
5 11
```

### 输出

```
3```

## 样例 #2

### 输入

```
6 16
```

### 输出

```
3```

# 题解

## 作者：sysu_yzc (赞：1)

## 思路

直接取$\frac{s}{n}$的上整就行了。

## 上代码
```
#include<iostream>
using namespace std;
int main(){
	int n,s;
	cin>>n>>s;
	if(s%n==0) cout<<s/n;
	else cout<<s/n+1;
	return 0;
}
```

---

## 作者：Sooke (赞：1)

### 题意

给出 $n$ 和 $S$，求最小的 $m$，使存在 $\sum\limits_{i=1}^{m}a_i = S$，其中 $a_i$ 为 $[1,\ n]$  中的整数。

### 解题思路

很显然的一道贪心，每次尽量选大的。

详细地说，从大到小枚举 $i$，设总和 $=S$，就可以选 $\lfloor \frac{S}{i} \rfloor$ 个 $i$。这样还剩下 $S - \lfloor \frac{S}{i} \rfloor \times i$，也就是 $S \mod i$，令 $S = S \mod i$，接着枚举就行了。

### 代码实现

```cpp
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>

int n, s, ans;

int main() {
    std::cin >> n >> s;
    for (int i = n; i >= 1; i--) { ans += s / i; s %= i; }
    std::cout << ans << std::endl;
    return 0;
}
```

---

## 作者：XLost (赞：0)

# 思路:

~~很显然的~~贪心算法，设每次n的值都最大，那么m的最小值就为(s - 1) / n + 1————————（(s / n) 的向上取整）.

# 代码:
```cpp
#include <iostream>

int s, n, m;

int main() {
	std::cin >> n >> s;
	m = (s - 1) / n + 1;
	std::cout << m << std::endl;
	return 0;
}
```
~~这题还可以。~~

---

