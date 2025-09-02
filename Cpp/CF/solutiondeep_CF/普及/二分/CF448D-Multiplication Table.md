# 题目信息

# Multiplication Table

## 题目描述

Bizon the Champion isn't just charming, he also is very smart.

While some of us were learning the multiplication table, Bizon the Champion had fun in his own manner. Bizon the Champion painted an $ n×m $ multiplication table, where the element on the intersection of the $ i $ -th row and $ j $ -th column equals $ i·j $ (the rows and columns of the table are numbered starting from 1). Then he was asked: what number in the table is the $ k $ -th largest number? Bizon the Champion always answered correctly and immediately. Can you repeat his success?

Consider the given multiplication table. If you write out all $ n·m $ numbers from the table in the non-decreasing order, then the $ k $ -th number you write out is called the $ k $ -th largest number.

## 说明/提示

A $ 2×3 $ multiplication table looks like this:

`<br></br>1 2 3<br></br>2 4 6<br></br><br></br>`

## 样例 #1

### 输入

```
2 2 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 3 4
```

### 输出

```
3
```

## 样例 #3

### 输入

```
1 10 5
```

### 输出

```
5
```

# AI分析结果

### 题目内容重写（中文）

**乘法表**

**题目描述**

Bizon the Champion不仅迷人，而且非常聪明。

当我们还在学习乘法表时，Bizon the Champion已经用自己的方式在玩了。他画了一个$n×m$的乘法表，其中第$i$行第$j$列的元素等于$i·j$（表的行和列从1开始编号）。然后他被问到：表中第$k$大的数是多少？Bizon the Champion总是能立即正确回答。你能重复他的成功吗？

考虑给定的乘法表。如果你将表中所有$n·m$个数按非递减顺序写出，那么你写出的第$k$个数就是第$k$大的数。

**说明/提示**

一个$2×3$的乘法表如下：

`<br></br>1 2 3<br></br>2 4 6<br></br><br></br>`

**样例 #1**

**输入**

```
2 2 2
```

**输出**

```
2
```

**样例 #2**

**输入**

```
2 3 4
```

**输出**

```
3
```

**样例 #3**

**输入**

```
1 10 5
```

**输出**

```
5
```

### 题解综合分析与结论

本题的核心在于如何在$n×m$的乘法表中快速找到第$k$大的数。由于直接暴力枚举所有数并排序的时间复杂度较高（$O(nm \log nm)$），因此需要更高效的算法。大多数题解都采用了**二分查找**的方法，通过二分答案来快速定位第$k$大的数。

**关键思路与技巧：**

1. **二分查找**：利用乘法表的单调性，通过二分查找来确定第$k$大的数。每次二分时，计算小于等于某个数的元素个数，判断是否满足条件。
2. **优化计算**：在二分查找的过程中，通过遍历每一行，计算该行中小于等于某个数的元素个数，从而快速得到总数。
3. **边界处理**：在二分查找时，注意处理边界条件，确保最终找到的数确实是第$k$大的数。

### 所选高分题解

#### 题解1：Mxfg（5星）

**关键亮点：**
- 思路清晰，详细解释了二分查找的原理和实现。
- 代码简洁，可读性强，优化程度高。
- 通过遍历每一行，计算小于等于某个数的元素个数，避免了直接排序的高时间复杂度。

**核心代码：**
```cpp
bool check(long long x) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += min(m, x / i);
    }
    return sum >= k;
}
```

#### 题解2：yu__xuan（4星）

**关键亮点：**
- 详细解释了二分查找的思路，并提供了计算小于和等于某个数的元素个数的方法。
- 代码结构清晰，逻辑严谨。
- 通过额外的计算等于某个数的元素个数，进一步确保了二分查找的准确性。

**核心代码：**
```cpp
ll sum = 0, tmp = 0;
for (int i = 1; i <= n; ++i) {
    sum += min((mid - 1) / i, m);
    if (mid % i == 0 && mid / i <= m) tmp++;
}
if (sum <= k - 1 && sum + tmp >= k) {
    write(mid);
    return 0;
}
```

#### 题解3：iiawaKL（4星）

**关键亮点：**
- 思路简洁明了，代码实现简单。
- 通过二分查找和遍历每一行，快速计算小于某个数的元素个数。
- 代码可读性强，适合初学者理解。

**核心代码：**
```cpp
bool check(long long x) {
    ll sum = 0;
    for (int i = 1; i <= n; i++) sum += min(m, x / i);
    return sum < k;
}
```

### 最优关键思路总结

1. **二分查找**：利用乘法表的单调性，通过二分查找快速定位第$k$大的数。
2. **优化计算**：在二分查找过程中，通过遍历每一行，计算该行中小于等于某个数的元素个数，从而快速得到总数。
3. **边界处理**：在二分查找时，注意处理边界条件，确保最终找到的数确实是第$k$大的数。

### 可拓展之处

1. **类似问题**：类似的问题包括在二维矩阵中查找第$k$大的数，或者在有序矩阵中查找某个数。
2. **算法套路**：二分查找+优化计算的方法可以应用于其他需要在有序结构中查找特定元素的问题。

### 推荐题目

1. **P2440 木材加工**（二分查找）
2. **P2678 跳石头**（二分查找）
3. **P3382 【模板】三分法**（三分查找）

这些题目都涉及到二分查找的应用，可以帮助进一步巩固和拓展二分查找的技巧。

---
处理用时：40.53秒