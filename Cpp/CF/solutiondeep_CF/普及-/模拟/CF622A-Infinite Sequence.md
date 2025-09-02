# 题目信息

# Infinite Sequence

## 题目描述

Consider the infinite sequence of integers: $ 1,1,2,1,2,3,1,2,3,4,1,2,3,4,5... $ . The sequence is built in the following way: at first the number $ 1 $ is written out, then the numbers from $ 1 $ to $ 2 $ , then the numbers from $ 1 $ to $ 3 $ , then the numbers from $ 1 $ to $ 4 $ and so on. Note that the sequence contains numbers, not digits. For example number $ 10 $ first appears in the sequence in position $ 55 $ (the elements are numerated from one).

Find the number on the $ n $ -th position of the sequence.

## 样例 #1

### 输入

```
3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
```

### 输出

```
2
```

## 样例 #3

### 输入

```
10
```

### 输出

```
4
```

## 样例 #4

### 输入

```
55
```

### 输出

```
10
```

## 样例 #5

### 输入

```
56
```

### 输出

```
1
```

# AI分析结果

### 题目中文重写
# 无限序列

## 题目描述

考虑无限整数序列：$1,1,2,1,2,3,1,2,3,4,1,2,3,4,5...$ 。该序列按以下方式构建：首先写出数字 $1$，然后写出从 $1$ 到 $2$ 的数字，接着写出从 $1$ 到 $3$ 的数字，再写出从 $1$ 到 $4$ 的数字，依此类推。请注意，序列包含的是数字，而不是数位。例如，数字 $10$ 首次出现在序列的第 $55$ 个位置（元素从 $1$ 开始编号）。

找出序列中第 $n$ 个位置上的数字。

## 样例 #1
### 输入
```
3
```
### 输出
```
2
```

## 样例 #2
### 输入
```
5
```
### 输出
```
2
```

## 样例 #3
### 输入
```
10
```
### 输出
```
4
```

## 样例 #4
### 输入
```
55
```
### 输出
```
10
```

## 样例 #5
### 输入
```
56
```
### 输出
```
1
```

### 题解综合分析与结论
这些题解主要围绕如何找出给定无限序列中第 $n$ 个位置上的数字展开。思路大致可分为模拟和数学两种方法。

- **模拟方法**：通过循环逐步构建序列，直到找到第 $n$ 个位置的数字。但由于数据范围大，容易超时，如 Aw顿顿 最初的暴力模拟解法。
- **数学方法**：将序列分组，利用等差数列求和公式确定第 $n$ 个数字所在的组，进而求出该数字。这种方法效率高，能避免超时问题。

### 高评分题解
1. **作者：Insouciant21（5星）**
    - **关键亮点**：思路清晰，利用等差数列求和公式列方程求解前面完整节的数量，代码简洁明了。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    long long n;
    scanf("%lld", &n);
    long long num = (-1 + sqrt(1 + 8 * n)) / 2.0;
    long long res = n - num * (num + 1) / 2;
    if (res == 0)
        res = num;
    printf("%lld", res);
    return 0;
}
```
    - **核心实现思想**：先通过等差数列求和公式 $\frac{m(m + 1)}{2}=n$ 求解 $m$，向下取整得到前面完整节的数量。再用 $n$ 减去前面完整节的数字个数，得到答案。若结果为 $0$，则表示第 $n$ 项为该节的最后一项，答案为 $m$。

2. **作者：伟大的王夫子（4星）**
    - **关键亮点**：同样运用数学方法，明确设出 $n$ 与前面组数 $k$ 的关系，通过求解不等式得到 $k$ 的最大值，进而求出结果。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n;
int main() {
    cin >> n;
    long long k = ceil((sqrt(8.0 * n + 1))) / 2 - 1;
    long long m = n - k * (k + 1) / 2;
    if (m == 0) printf("%lld", k);
    else printf("%lld", m);
}
```
    - **核心实现思想**：设 $n=\frac{k(k + 1)}{2}+m$，通过求解不等式 $\frac{k(k + 1)}{2}\leq n$ 得到 $k$ 的最大值。再计算 $m$，若 $m = 0$，则输出 $k$；否则输出 $m$。

### 最优关键思路或技巧
利用等差数列求和公式 $\frac{n(n + 1)}{2}$ 来确定第 $n$ 个数字所在的组，避免了模拟方法的高时间复杂度。

### 拓展思路
同类型题可能会改变序列的构建规则，但解题思路类似，可先找出序列的规律，再通过数学公式或分组的方法求解。

### 洛谷相似题目推荐
1. [P1009 阶乘之和](https://www.luogu.com.cn/problem/P1009)：考察数学计算和高精度处理。
2. [P1035 级数求和](https://www.luogu.com.cn/problem/P1035)：涉及数列求和与条件判断。
3. [P1217 [USACO1.5]回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)：需要结合数学性质和枚举法求解。

### 个人心得摘录与总结
- **Aw顿顿**：尝试暴力模拟超时后，意识到模拟方法在处理大数据时的局限性，从而转向数学解法。
- **LW_h_FP**：最初想到模拟，但因数据太大放弃，通过观察序列规律，采用减法操作找到答案。 

---
处理用时：24.67秒