# [ABC390B] Geometric Sequence

## 题目描述

给定一个长度为 $N$ 的正整数序列 $A = (A_1, A_2, \ldots, A_N)$。  
请判断 $A$ 是否为等比数列。

## 说明/提示

### 约束条件

- $2 \leq N \leq 100$
- $1 \leq A_i \leq 10^9$
- 输入的所有值均为整数

### 样例解释 1

$A = (3, 6, 12, 24, 48)$。$A$ 是以首项 $3$、公比 $2$、项数 $5$ 构成的等比数列。因此，输出 `Yes`。

### 样例解释 2

$A = (1, 2, 3)$。由于 $A_1 : A_2 = 1 : 2 \neq 2 : 3 = A_2 : A_3$，$A$ 不是等比数列。因此，输出 `No`。

### 样例解释 3

$A$ 是以首项 $10$、公比 $0.8$、项数 $2$ 构成的等比数列。因此，输出 `Yes`。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
3 6 12 24 48```

### 输出

```
Yes```

## 样例 #2

### 输入

```
3
1 2 3```

### 输出

```
No```

## 样例 #3

### 输入

```
2
10 8```

### 输出

```
Yes```

# 题解

## 作者：FlowerAccepted (赞：6)

介绍两种解法。第二种简便一些。

# Solution 1

## 解题思路

这道题需要我们首先算出 $A_1$ 和 $A_2$ 的比 $d = \frac{A_2}{A_1}$，作为公比；

然后从 $2$ 开始枚举 $i$ 到 $N - 1$，判断 $\frac{A_{i + 1}}{A_i}$ 是否等于 $d$，如果是，继续程序，否则输出 `No` 并退出。

## 实现细节

**前方高能！这是本题难点！**

注意到，公比是一个**正有理数**（即正整数或正分数），

可以发现`double` 的精度是不够的，任何存一个数的精度也不够，这就只能存分数。Python 的 numpy 库有分数计算功能，可是评测机用不了。

不妨设 $d = \frac{p}{q}$；

可以尝试 $p = A_2$，$q = A_1$，但这样判断 $\frac{A_{i + 1}}{A_i}$ 是否等于 $d$ 就会十分麻烦；

于是我们可以存**最简假分数**，这样只要判断 $\frac{A_{i + 1}}{p}$ 是否等于 $\frac{A_i}{q}$（即判断是不是这个分数的倍数）就可以了。

但如何获取最简假分数呢？$\gcd$，对，就是 $\gcd$（最大公因数）。

这里使用辗转相除法求 $\gcd$。如果你不知道 $\gcd$，可以[在百度上搜索一下](https://www.baidu.com/s?wd=gcd)，这里不再赘述。

“食”用方法是这样的，设 $g = \gcd(A_1, A_2)$，则 $p = \frac{A_2}{g}$，$q = \frac{A_1}{g}$；

判断时要注意整数除法的四舍五入问题。

## 代码呈现

```cpp
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring> // 我的码风谔谔
using namespace std;

int a[105]; // 开大

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b); // 辗转相除（小学奥数谔谔）
}

int main() {
    int n, p, q, g;
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }
    if (n == 2) { // 在 N = 2 时恒成立
        cout << "Yes";
        return 0;
    }
    g = gcd(a[1], a[2]);
    p = a[2] / g;
    q = a[1] / g; // 算 d
    for (int i = 2; i < n; i ++) { // 枚举，无需重复
        if (a[i + 1] / p != a[i] / q || a[i + 1] / p * p != a[i + 1] || a[i] / q * q != a[i]) { // 后面两个表达式防止整型除法四舍五入的误差
            cout << "No";
            return 0;
        }
    }
    cout << "Yes"; // 过关斩将的等比数列 lol
    return 0;
}

```

至此，此题 Accepted。

## 复杂度分析

很明显，算法的时间复杂度是 $O(n)$（$\gcd$ 的复杂度是 $O(\log(A))$，当 $N$ 较小时可能会超过 $O(n)$）。

# Solution 2

## 前言

应 [chen_zhe](/user/8457) 建议，将这种简便一些的解法写一下。

## 解题思路

在一个等比数列里，对于 $A_i$（$2 \le i < N$），令公比为 $d$ 有

$$
\begin{aligned}
   {A_i}^2 &= A_i \times A_i \\
           &= A_i \times A_i \times \frac{1}{d} \times d \\
           &= (A_i \times \frac{1}{d}) \times (A_i \times d) \\
           &= A_{i - 1} \times A_{i + 1}
\end{aligned}
$$

所以只要判断 ${A_i}^2$ 是否等于 $A_{i - 1} \times A_{i + 1}$ 即可。

注意整形溢出。

## 代码呈现
```cpp
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int a[105]; // 开大

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }
    if (n == 2) { // 在 N = 2 时恒成立
        cout << "Yes";
        return 0;
    }
    for (int i = 2; i < n; i ++) { // 枚举
        if (1ll * a[i] * a[i] != 1ll * a[i - 1] * a[i + 1]) { // 开 long long
            cout << "No";
            return 0;
        }
    }
    cout << "Yes"; // 过关斩将的等比数列 lol
    return 0;
}

```

至此，此题 Accepted。

## 复杂度分析

实打实的 $O(n)$。

---

