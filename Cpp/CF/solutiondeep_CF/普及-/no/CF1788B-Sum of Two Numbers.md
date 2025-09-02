# 题目信息

# Sum of Two Numbers

## 题目描述

The sum of digits of a non-negative integer $ a $ is the result of summing up its digits together when written in the decimal system. For example, the sum of digits of $ 123 $ is $ 6 $ and the sum of digits of $ 10 $ is $ 1 $ . In a formal way, the sum of digits of $ \displaystyle a=\sum_{i=0}^{\infty} a_i \cdot 10^i $ , where $ 0 \leq a_i \leq 9 $ , is defined as $ \displaystyle\sum_{i=0}^{\infty}{a_i} $ .

Given an integer $ n $ , find two non-negative integers $ x $ and $ y $ which satisfy the following conditions.

- $ x+y=n $ , and
- the sum of digits of $ x $ and the sum of digits of $ y $ differ by at most $ 1 $ .

It can be shown that such $ x $ and $ y $ always exist.

## 说明/提示

In the second test case, the sum of digits of $ 67 $ and the sum of digits of $ 94 $ are both $ 13 $ .

In the third test case, the sum of digits of $ 60 $ is $ 6 $ , and the sum of digits of $ 7 $ is $ 7 $ .

## 样例 #1

### 输入

```
5
1
161
67
1206
19```

### 输出

```
1 0
67 94
60 7
1138 68
14 5```

# AI分析结果

### 题目内容
# 两数之和

## 题目描述
一个非负整数 $a$ 的各位数字之和，是指将其写成十进制形式后，各位数字相加的结果。例如，$123$ 的各位数字之和是 $6$，$10$ 的各位数字之和是 $1$。形式化地，对于 $\displaystyle a=\sum_{i=0}^{\infty} a_i \cdot 10^i$，其中 $0 \leq a_i \leq 9$，其各位数字之和定义为 $\displaystyle\sum_{i=0}^{\infty}{a_i}$。

给定一个整数 $n$，找到两个非负整数 $x$ 和 $y$，使其满足以下条件：
- $x + y = n$，并且
- $x$ 的各位数字之和与 $y$ 的各位数字之和相差最多为 $1$。

可以证明这样的 $x$ 和 $y$ 总是存在的。

## 说明/提示
在第二个测试用例中，$67$ 的各位数字之和与 $94$ 的各位数字之和均为 $13$。

在第三个测试用例中，$60$ 的各位数字之和为 $6$，$7$ 的各位数字之和为 $7$。

## 样例 #1
### 输入
```
5
1
161
67
1206
19
```
### 输出
```
1 0
67 94
60 7
1138 68
14 5
```
### 算法分类
构造
### 综合分析与结论
这些题解的核心思路都是通过对整数 $n$ 的不同情况进行分类讨论来构造满足条件的 $x$ 和 $y$。主要难点在于当 $n$ 为奇数且 $\lfloor\frac{n}{2}\rfloor$ 的个位为 $9$ 时，如何构造使得 $x$ 和 $y$ 的数位和相差不超过 $1$。
- **思路方面**：多数题解先区分 $n$ 的奇偶性，偶数情况直接令 $x = y = \frac{n}{2}$；奇数时，若 $\lfloor\frac{n}{2}\rfloor$ 个位不为 $9$，则 $x=\lfloor\frac{n}{2}\rfloor + 1$，$y=\lfloor\frac{n}{2}\rfloor$ 。对于困难情况，部分题解采用按位拆分 $n$，将每一位尽量平均分配给 $x$ 和 $y$，奇数位时交替让 $x$ 或 $y$ 多 $1$；有的题解通过递归并调整参数避免进位影响数位和；还有通过打表方式处理连续 $9$ 的情况。
- **算法要点**：关键在于对 $n$ 的不同情况准确分类，以及针对不同情况设计合理的构造方法，利用整数的除法、取余等运算实现。
- **解决难点**：当 $\lfloor\frac{n}{2}\rfloor$ 个位为 $9$ 时，通过按位分配、递归调整或者打表等方式，确保 $x$ 和 $y$ 的数位和满足条件。

由于所有题解质量均未达到4星，故不列出具体题解，仅给出通用建议与扩展思路。

### 通用建议与扩展思路
- **通用建议**：在解决这类构造性问题时，要全面分析各种可能情况，从简单情况入手，逐步深入到复杂情况。代码实现时注意边界条件和细节处理，例如整数运算的精度问题、循环终止条件等。
- **扩展思路**：此类构造题可拓展到其他进制下的数字构造问题，或者对数字的其他属性进行限制的构造问题。类似算法套路通常是先对输入数据进行分类，然后针对不同类别设计满足条件的构造策略。

### 相似知识点洛谷题目
- [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)：通过数学分析和枚举来构造满足和条件的连续自然数序列。
- [P1464 Function](https://www.luogu.com.cn/problem/P1464)：根据给定的函数定义和条件，通过递归或递推构造函数值。
- [P1966 火柴排队](https://www.luogu.com.cn/problem/P1966)：利用排序和数学方法构造最优的火柴排列方式，以满足距离最小的条件。 

---
处理用时：35.93秒