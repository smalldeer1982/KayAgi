# 题目信息

# Anu Has a Function

## 题目描述

Anu has created her own function $ f $ : $ f(x, y) = (x | y) - y $ where $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR). For example, $ f(11, 6) = (11|6) - 6 = 15 - 6 = 9 $ . It can be proved that for any nonnegative numbers $ x $ and $ y $ value of $ f(x, y) $ is also nonnegative.

She would like to research more about this function and has created multiple problems for herself. But she isn't able to solve all of them and needs your help. Here is one of these problems.

A value of an array $ [a_1, a_2, \dots, a_n] $ is defined as $ f(f(\dots f(f(a_1, a_2), a_3), \dots a_{n-1}), a_n) $ (see notes). You are given an array with not necessarily distinct elements. How should you reorder its elements so that the value of the array is maximal possible?

## 说明/提示

In the first testcase, value of the array $ [11, 6, 4, 0] $ is $ f(f(f(11, 6), 4), 0) = f(f(9, 4), 0) = f(9, 0) = 9 $ .

 $ [11, 4, 0, 6] $ is also a valid answer.

## 样例 #1

### 输入

```
4
4 0 11 6```

### 输出

```
11 6 4 0```

## 样例 #2

### 输入

```
1
13```

### 输出

```
13```

# AI分析结果

### 题目内容重写

#### 题目描述

Anu 定义了一个函数 $f$：$f(x, y) = (x | y) - y$，其中 $|$ 表示按位或运算。例如，$f(11, 6) = (11|6) - 6 = 15 - 6 = 9$。可以证明，对于任何非负整数 $x$ 和 $y$，$f(x, y)$ 的值也是非负的。

Anu 想进一步研究这个函数，并为自己创建了多个问题。但她无法解决所有问题，因此需要你的帮助。以下是其中一个问题：

定义一个数组 $[a_1, a_2, \dots, a_n]$ 的值为 $f(f(\dots f(f(a_1, a_2), a_3), \dots a_{n-1}), a_n)$。给定一个元素不一定唯一的数组，如何重新排列其元素，使得数组的值最大？

#### 说明/提示

在第一个测试用例中，数组 $[11, 6, 4, 0]$ 的值为 $f(f(f(11, 6), 4), 0) = f(f(9, 4), 0) = f(9, 0) = 9$。

$[11, 4, 0, 6]$ 也是一个有效的答案。

#### 样例 #1

##### 输入

```
4
4 0 11 6
```

##### 输出

```
11 6 4 0
```

#### 样例 #2

##### 输入

```
1
13
```

##### 输出

```
13
```

### 算法分类

位运算、贪心

### 题解分析与结论

#### 题解对比与总结

1. **oimaster 的题解**：
   - **关键思路**：通过分析函数 $f(x, y)$ 的二进制性质，发现只有第一个数的某些位对结果有贡献。通过预处理每个数的有效位，找到最大有效位的数作为第一个数，其余数顺序随意。
   - **难点**：理解函数 $f(x, y)$ 的二进制性质，并找到有效位的计算方法。
   - **评分**：4星，思路清晰，代码实现简洁。

2. **lemonfor 的题解**：
   - **关键思路**：贪心策略，找到最高且唯一的二进制位为1的数，将其放在最前面，其余数顺序随意。
   - **难点**：如何高效地找到最高且唯一的二进制位。
   - **评分**：4星，思路明确，代码简洁。

3. **gyh20 的题解**：
   - **关键思路**：枚举每一位，找到有且仅有一个数的第 $i$ 位为1，将其放在第一个位置。
   - **难点**：如何高效地枚举每一位并找到符合条件的数。
   - **评分**：4星，思路清晰，代码实现简洁。

#### 最优关键思路

通过分析函数 $f(x, y)$ 的二进制性质，发现只有第一个数的某些位对结果有贡献。因此，找到最高且唯一的二进制位为1的数，将其放在最前面，其余数顺序随意。

#### 可拓展之处

类似的问题可以通过分析二进制性质来解决，例如：
- 给定一个数组，找到一种排列方式，使得按位与的结果最大。
- 给定一个数组，找到一种排列方式，使得按位异或的结果最大。

#### 推荐题目

1. [P2114 [NOI2014] 起床困难综合症](https://www.luogu.com.cn/problem/P2114)
2. [P2420 让我们异或吧](https://www.luogu.com.cn/problem/P2420)
3. [P4310 绝世好题](https://www.luogu.com.cn/problem/P4310)

#### 个人心得

- **调试经历**：在实现过程中，需要注意二进制位的处理，特别是位运算的优先级和边界情况。
- **顿悟感想**：通过分析函数的二进制性质，可以简化问题并找到高效的解决方案。

---
处理用时：27.20秒