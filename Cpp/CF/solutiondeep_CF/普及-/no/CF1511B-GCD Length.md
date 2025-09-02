# 题目信息

# GCD Length

## 题目描述

You are given three integers $ a $ , $ b $ and $ c $ .

Find two positive integers $ x $ and $ y $ ( $ x > 0 $ , $ y > 0 $ ) such that:

- the decimal representation of $ x $ without leading zeroes consists of $ a $ digits;
- the decimal representation of $ y $ without leading zeroes consists of $ b $ digits;
- the decimal representation of $ gcd(x, y) $ without leading zeroes consists of $ c $ digits.

 $ gcd(x, y) $ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ x $ and $ y $ .

Output $ x $ and $ y $ . If there are multiple answers, output any of them.

## 说明/提示

In the example:

1. $ gcd(11, 492) = 1 $
2. $ gcd(13, 26) = 13 $
3. $ gcd(140133, 160776) = 21 $
4. $ gcd(1, 1) = 1 $

## 样例 #1

### 输入

```
4
2 3 1
2 2 2
6 6 2
1 1 1```

### 输出

```
11 492
13 26
140133 160776
1 1```

# AI分析结果

### 题目内容
# GCD长度

## 题目描述
给定三个整数 $a$、$b$ 和 $c$ 。

找到两个正整数 $x$ 和 $y$（$x > 0$，$y > 0$），使得：
- $x$ 的十进制表示不含前导零，且由 $a$ 位数字组成；
- $y$ 的十进制表示不含前导零，且由 $b$ 位数字组成；
- $\gcd(x, y)$（$x$ 和 $y$ 的最大公约数）的十进制表示不含前导零，且由 $c$ 位数字组成。

$\gcd(x, y)$ 表示整数 $x$ 和 $y$ 的[最大公约数（GCD）](https://en.wikipedia.org/wiki/Greatest_common_divisor)。

输出 $x$ 和 $y$ 。如果有多个答案，输出任意一个。

## 说明/提示
在示例中：
1. $\gcd(11, 492) = 1$
2. $\gcd(13, 26) = 13$
3. $\gcd(140133, 160776) = 21$
4. $\gcd(1, 1) = 1$

## 样例 #1
### 输入
```
4
2 3 1
2 2 2
6 6 2
1 1 1```
### 输出
```
11 492
13 26
140133 160776
1 1```

### 算法分类
构造

### 题解综合分析与结论
这些题解的核心思路都是先构造出具有 $c$ 位的 $\gcd(x, y)$，再基于此构造满足位数要求的 $x$ 和 $y$，同时保证 $x$ 与 $y$ 除以 $\gcd(x, y)$ 的商互质。不同之处主要在于构造 $\gcd(x, y)$ 以及满足互质条件的具体方式。
1. **构造 $\gcd(x, y)$ 的方式**：多数题解选择构造 $\gcd(x, y)$ 为 $10^{c - 1}$，如“云浅知处”“___cjy__”等题解；部分题解采用其他方式，如“FutaRimeWoawaSete”用 $2$ 的幂构造，“sjr3065335594”用随机数构造。
2. **保证商互质的方法**：
    - 用质数构造，如“云浅知处”预处理不同区间的质数，“TainityAnle”“linyuhao”“dead_X”分别使用不同质数组合构造 $x$ 和 $y$。
    - 利用数字特性，如“xiaoyuchenp”“Mophie”“oimaster”“_VEGETABLE_OIer_xlc”“hubin1”“Aw顿顿”等通过构造特定形式的数，使 $x$ 和 $y$ 除以 $\gcd(x, y)$ 的商互质，如利用 $10^{a - c}$ 与 $10^{b - c + 1} - 1$ 互质（因为 $10^{b - c + 1} - 1$ 不被 $2$ 或 $5$ 整除）。

### 通用建议与扩展思路
对于此类构造题，关键在于抓住题目核心条件，从简单情况入手思考构造方法。本题中先确定 $\gcd(x, y)$ 的构造形式，再围绕其构造 $x$ 和 $y$ 是常见思路。类似题目通常会给定一些约束条件要求构造符合条件的数或结构，可以多尝试从特殊值、简单形式出发，寻找规律。例如在构造具有特定性质的数时，可考虑质数、幂次方等特殊数的性质，以及数字组合方式对结果的影响。

### 相似知识点洛谷题目
1. [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)：通过数学分析和构造方法解决连续自然数求和问题。
2. [P2619 魔法阵](https://www.luogu.com.cn/problem/P2619)：需要根据给定条件构造满足要求的魔法阵，涉及数的性质和组合构造。
3. [P1306 斐波那契公约数](https://www.luogu.com.cn/problem/P1306)：结合斐波那契数列性质与最大公约数的构造求解。 

---
处理用时：37.17秒