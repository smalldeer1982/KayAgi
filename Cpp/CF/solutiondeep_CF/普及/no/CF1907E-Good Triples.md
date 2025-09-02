# 题目信息

# Good Triples

## 题目描述

Given a non-negative integer number $ n $ ( $ n \ge 0 $ ). Let's say a triple of non-negative integers $ (a, b, c) $ is good if $ a + b + c = n $ , and $ digsum(a) + digsum(b) + digsum(c) = digsum(n) $ , where $ digsum(x) $ is the sum of digits of number $ x $ .

For example, if $ n = 26 $ , then the pair $ (4, 12, 10) $ is good, because $ 4 + 12 + 10 = 26 $ , and $ (4) + (1 + 2) + (1 + 0) = (2 + 6) $ .

Your task is to find the number of good triples for the given number $ n $ . The order of the numbers in a triple matters. For example, the triples $ (4, 12, 10) $ and $ (10, 12, 4) $ are two different triples.

## 说明/提示

In the first example, the good triples are $ (0, 0, 11) $ , $ (0, 1, 10) $ , $ (0, 10, 1) $ , $ (0, 11, 0) $ , $ (1, 0, 10) $ , $ (1, 10, 0) $ , $ (10, 0, 1) $ , $ (10, 1, 0) $ , $ (11, 0, 0) $ .

In the second example, there is only one good triple $ (0, 0, 0) $ .

## 样例 #1

### 输入

```
12
11
0
1
2
3
4
5
3141
999
2718
9999999
10000000```

### 输出

```
9
1
3
6
10
15
21
1350
166375
29160
1522435234375
3```

# AI分析结果



# Good Triples

## 题目描述

给定一个非负整数 $n$（$n \ge 0$）。称一个非负整数三元组 $(a, b, c)$ 是好的，当且仅当满足 $a + b + c = n$ 且 $digsum(a) + digsum(b) + digsum(c) = digsum(n)$，其中 $digsum(x)$ 表示 $x$ 的各位数字之和。

例如，当 $n = 26$ 时，三元组 $(4, 12, 10)$ 是好的，因为 $4 + 12 + 10 = 26$，且 $(4) + (1+2) + (1+0) = (2+6)$。

你的任务是计算给定 $n$ 的好三元组数量。三元组的顺序不同视为不同情况。

## 算法分类
组合数学

---

## 题解分析与结论

### 关键结论
- **不进位法则**：当且仅当三个数相加时每一位都不产生进位，才能满足数位和相等的条件。进位会导致数位和减少 $9k$（$k$ 为进位次数），而等式左侧数位和不变。
- **独立位处理**：将 $n$ 按十进制位拆解，每一位单独计算拆分方案数，最终通过乘法原理相乘。

### 最优思路
对于每一位数字 $d$，计算将其拆分为三个非负整数之和的方案数，即求满足 $a_i + b_i + c_i = d$ 的非负整数解的数量，该值为 $\frac{(d+1)(d+2)}{2}$。将所有位的方案数相乘即为最终答案。

---

## 精选题解

### 题解1：yhx0322（4星）
**关键亮点**：简洁推导组合数公式，代码直接应用公式计算。
```cpp
int ans = 1;
while (n) {
    int d = n % 10;
    ans *= (d + 1) * (d + 2) >> 1LL; // 等价于 C(d+2,2)
    n /= 10;
}
```

### 题解2：Special_Tony（4星）
**关键亮点**：明确插板法原理，代码实现极简。
```cpp
sum *= (n % 10 + 2) * (n % 10 + 1) / 2;
```

### 题解3：Confringo（4星）
**关键亮点**：通过预处理优化计算，逻辑清晰。
```cpp
for (int i=0; i<=9; ++i)
    for (int j=0; j<=9; ++j)
        for (int k=0; k<=9; ++k)
            if (i+j+k < 10) cnt[i+j+k]++;
```

---

## 核心代码实现
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int T, n;
    cin >> T;
    while (T--) {
        cin >> n;
        long long ans = 1;
        while (n) {
            int d = n % 10;
            ans *= (d + 1) * (d + 2) / 2;
            n /= 10;
        }
        cout << ans << '\n';
    }
    return 0;
}
```

---

## 拓展与心得

### 同类题目推荐
1. [P1869 数位和](https://www.luogu.com.cn/problem/P1869) - 数位性质分析
2. [P2119 魔法阵](https://www.luogu.com.cn/problem/P2119) - 组合数学应用
3. [CF1036C Classy Numbers](https://www.luogu.com.cn/problem/CF1036C) - 数位限制问题

### 解题心得
- **打表观察**：通过小样例发现不进位规律（如 99 的答案是 9 的平方）。
- **组合数学应用**：将数位拆分转化为插板法模型，简化计算。
- **独立位处理**：利用乘法原理分解复杂问题，降低维度。

---
处理用时：58.31秒