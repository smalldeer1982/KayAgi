# 题目信息

# PolandBall and Hypothesis

## 题目描述

PolandBall is a young, clever Ball. He is interested in prime numbers. He has stated a following hypothesis: "There exists such a positive integer $ n $ that for each positive integer $ m $ number $ n·m+1 $ is a prime number".

Unfortunately, PolandBall is not experienced yet and doesn't know that his hypothesis is incorrect. Could you prove it wrong? Write a program that finds a counterexample for any $ n $ .

## 说明/提示

A prime number (or a prime) is a natural number greater than $ 1 $ that has no positive divisors other than $ 1 $ and itself.

For the first sample testcase, $ 3·1+1=4 $ . We can output $ 1 $ .

In the second sample testcase, $ 4·1+1=5 $ . We cannot output $ 1 $ because $ 5 $ is prime. However, $ m=2 $ is okay since $ 4·2+1=9 $ , which is not a prime number.

## 样例 #1

### 输入

```
3
```

### 输出

```
1```

## 样例 #2

### 输入

```
4
```

### 输出

```
2```

# AI分析结果

### 题目内容（中文重写）
# PolandBall与假设

## 题目描述
PolandBall是一个年轻且聪明的球。他对质数很感兴趣。他提出了如下假设：“存在一个正整数 $n$，使得对于每个正整数 $m$，$n·m + 1$ 都是质数”。

不幸的是，PolandBall经验不足，不知道他的假设是错误的。你能证明这个假设是错误的吗？编写一个程序，为任意的 $n$ 找到一个反例。

## 说明/提示
质数（或素数）是大于 $1$ 且除了 $1$ 和它自身外没有其他正因数的自然数。

对于第一个样例测试用例，$3·1 + 1 = 4$。我们可以输出 $1$。

在第二个样例测试用例中，$4·1 + 1 = 5$。我们不能输出 $1$，因为 $5$ 是质数。然而，$m = 2$ 是可以的，因为 $4·2 + 1 = 9$，$9$ 不是质数。

## 样例 #1
### 输入
```
3
```
### 输出
```
1
```

## 样例 #2
### 输入
```
4
```
### 输出
```
2
```

### 算法分类
枚举

### 综合分析与结论
- **思路对比**：
    - tZEROちゃん的题解采用从 $1$ 开始逐个枚举 $m$ 的值，对每个 $m$ 计算 $n·m + 1$ 并判断其是否为质数，若不是质数则输出 $m$。
    - tangyifei009的题解先预处理出 $1$ 到 $1000$ 内的质数，再从 $1$ 到 $1000$ 枚举 $m$，判断 $n·m + 1$ 是否为质数，若不是则输出 $m$。
    - xsI666的题解通过数学推导发现当 $n > 2$ 时，$n·(n - 2)+1=(n - 1)·(n - 1)$ 不是质数，对于 $n\leq2$ 则单独讨论。
- **算法要点对比**：
    - tZEROちゃん的题解核心是实现一个判断质数的函数，然后进行枚举。
    - tangyifei009的题解核心是预处理质数表，再进行枚举判断。
    - xsI666的题解核心是数学推导，根据不同的 $n$ 情况直接得出结果。
- **解决难点对比**：
    - tZEROちゃん的题解难点在于判断质数的函数实现和枚举的终止条件（找到反例即停止）。
    - tangyifei009的题解难点在于质数表的预处理和枚举范围的确定。
    - xsI666的题解难点在于数学规律的发现和不同情况的分类讨论。
- **评分**：
    - tZEROちゃん：3星。思路清晰，代码简洁，但判断质数的函数存在逻辑错误（$n = 1$ 不是质数，判断错误）。
    - tangyifei009：2星。采用了预处理质数表的方法，但枚举范围有限，可能存在无法找到反例的情况。
    - xsI666：4星。通过数学推导直接得出结果，时间复杂度低，代码简洁。

### 所选题解
- xsI666（4星）：关键亮点是通过数学推导发现规律，避免了枚举，时间复杂度为 $O(1)$。

### 重点代码及核心实现思想
```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read()
{
    int f = 1, x = 0;
    char c = getchar();

    while (c < '0' || c > '9')
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }

    while (c >= '0' && c <= '9')
    {
        x = x * 10 + c - '0';
        c = getchar();
    }

    return f * x;
}

int n, m;

int main()
{
    n = read();
    if (n > 2)
    {
        printf("%d", n - 2);
        return 0;
    }
    if (n == 2)
    {
        printf("4");
        return 0;
    }
    if (n == 1)
    {
        printf("3");
        return 0;
    }
    return 0;
}
```
核心实现思想：通过数学推导得出当 $n > 2$ 时，$n·(n - 2)+1=(n - 1)·(n - 1)$ 不是质数，直接输出 $n - 2$；对于 $n = 2$ 和 $n = 1$ 的情况，分别找出对应的反例 $4$ 和 $3$ 并输出。

### 可拓展之处
同类型题或类似算法套路：对于一些数学相关的题目，可以尝试通过数学推导找出规律，避免暴力枚举，从而降低时间复杂度。例如一些数论相关的题目，如判断某个数是否为完全平方数、找出满足特定条件的数等。

### 推荐洛谷题目
1. P1075 [NOIP2012 普及组] 质因数分解：https://www.luogu.com.cn/problem/P1075
2. P1217 [USACO1.5] 回文质数 Prime Palindromes：https://www.luogu.com.cn/problem/P1217
3. P3383 【模板】线性筛素数：https://www.luogu.com.cn/problem/P3383

### 个人心得摘录与总结
tangyifei009：做题时未想到特例，愚蠢地采用逐一枚举质数方法。总结：在解题时要充分考虑各种情况，尝试寻找更优的解法，避免盲目采用暴力枚举的方法。 

---
处理用时：35.54秒