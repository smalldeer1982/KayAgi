# 题目信息

# Ilya and Sticks

## 题目描述

In the evening, after the contest Ilya was bored, and he really felt like maximizing. He remembered that he had a set of $ n $ sticks and an instrument. Each stick is characterized by its length $ l_{i} $ .

Ilya decided to make a rectangle from the sticks. And due to his whim, he decided to make rectangles in such a way that maximizes their total area. Each stick is used in making at most one rectangle, it is possible that some of sticks remain unused. Bending sticks is not allowed.

Sticks with lengths $ a_{1} $ , $ a_{2} $ , $ a_{3} $ and $ a_{4} $ can make a rectangle if the following properties are observed:

- $ a_{1}<=a_{2}<=a_{3}<=a_{4} $
- $ a_{1}=a_{2} $
- $ a_{3}=a_{4} $

A rectangle can be made of sticks with lengths of, for example, $ 3 3 3 3 $ or $ 2 2 4 4 $ . A rectangle cannot be made of, for example, sticks $ 5 5 5 7 $ .

Ilya also has an instrument which can reduce the length of the sticks. The sticks are made of a special material, so the length of each stick can be reduced by at most one. For example, a stick with length $ 5 $ can either stay at this length or be transformed into a stick of length $ 4 $ .

You have to answer the question — what maximum total area of the rectangles can Ilya get with a file if makes rectangles from the available sticks?

## 样例 #1

### 输入

```
4
2 4 4 2
```

### 输出

```
8
```

## 样例 #2

### 输入

```
4
2 2 3 5
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4
100003 100004 100005 100006
```

### 输出

```
10000800015
```

# AI分析结果



# Ilya and Sticks

## 题目描述

在比赛后的晚上，Ilya 感到无聊，他想最大化某些东西。他想起自己有一套 $n$ 根木棍和一个工具。每根木棍的长度为 $l_i$。

Ilya 决定用这些木棍组成矩形，并希望通过调整木棍长度使得所有矩形的总面积最大化。每根木棍最多用于一个矩形，允许部分木棍未被使用。木棍不能弯曲。

四根长度分别为 $a_1, a_2, a_3, a_4$ 的木棍可以组成矩形，当且仅当满足以下条件：
- $a_1 \leq a_2 \leq a_3 \leq a_4$
- $a_1 = a_2$
- $a_3 = a_4$

例如，$3,3,3,3$ 或 $2,2,4,4$ 可以组成矩形，而 $5,5,5,7$ 不能。

工具可以将每根木棍的长度最多减少 1。例如，长度为 5 的木棍可以保持 5 或变为 4。

求 Ilya 能得到的最大矩形总面积。

## 样例输入输出

### 样例 #1
输入：
```
4
2 4 4 2
```
输出：
```
8
```

### 样例 #2
输入：
```
4
2 2 3 5
```
输出：
```
0
```

### 样例 #3
输入：
```
4
100003 100004 100005 100006
```
输出：
```
10000800015
```

---

**算法分类**：贪心

---

## 题解分析与结论

### 核心思路
所有题解均基于贪心策略，核心要点如下：
1. **排序**：将木棍长度从大到小排序，优先选择较大的边。
2. **配对规则**：遍历相邻木棍，若差值 ≤1 则视为可配对，每次收集两个配对形成矩形的边。
3. **面积计算**：两两配对的边相乘累加，确保总和最大。

### 解决难点
- **正确配对逻辑**：需处理奇数个配对的情况，剩余未配对的边需舍弃。
- **避免提前终止**：部分题解（如 G2_NIKO）在首次无法配对时直接返回，导致后续有效配对被忽略，此为常见错误点。

---

## 精选题解

### 题解作者：OIerJiang_1017（4星）
**关键亮点**：
- 通过双重循环正确处理所有可能的配对，不会遗漏后续组合。
- 代码清晰，逻辑紧凑，无冗余操作。

**核心代码**：
```cpp
sort(f + 1, f + n + 1, cmp);
for(int i = 2; i <= n; i++)
    if(f[i-1] - f[i] <= 1) {
        if(a != 0) {
            b += a * f[i];
            a = 0;
            i++;
        } else {
            a = f[i];
            i++;
        }
    }
```

---

### 题解作者：Alexxu2024（4星）
**关键亮点**：
- 简洁的配对逻辑，使用临时变量 `chang` 存储边。
- 正确处理奇数次配对，代码可读性高。

**核心代码**：
```cpp
sort(a+1,a+1+n,cmp);
long long sum=0, chang=0;
for(int i=1; i<=n; i++) {
    if(a[i]==a[i+1] || a[i]==a[i+1]+1) {
        if(chang == 0) {
            chang = a[i+1];
            i++;
        } else {
            sum += a[i+1] * chang;
            chang = 0;
            i++;
        }
    }
}
```

---

### 题解作者：czh___（4星）
**关键亮点**：
- 逆向遍历已排序数组，逻辑等效但实现新颖。
- 通过从后向前处理，巧妙避免索引越界问题。

**核心代码**：
```cpp
sort(a, a + n);
for(long long i = n-2; i >= 0; i--) {
    if(a[i+1] - a[i] <= 1) {
        if(m) {
            s += m * a[i];
            m = 0;
            i--;
        } else {
            m = a[i];
            i--;
        }
    }
}
```

---

## 最优思路总结
1. **贪心排序**：从大到小排序确保优先使用较大边。
2. **相邻配对**：仅允许差值为 0 或 1 的相邻木棍配对。
3. **动态累加**：维护临时变量存储未配对的边，两两相乘后累加面积。

---

## 拓展与相似题目
1. **P1094 纪念品分组**：贪心配对，最小化组数。
2. **P1106 删数问题**：贪心删除数字使剩余数最大。
3. **P1233 木棍加工**：贪心排序后动态规划处理。

---
处理用时：192.14秒