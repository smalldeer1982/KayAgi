# 题目信息

# Good Subarrays (Easy Version)

## 题目描述

This is the easy version of this problem. In this version, we do not have queries. Note that we have multiple test cases in this version. You can make hacks only if both versions of the problem are solved.

An array $ b $ of length $ m $ is good if for all $ i $ the $ i $ -th element is greater than or equal to $ i $ . In other words, $ b $ is good if and only if $ b_i \geq i $ for all $ i $ ( $ 1 \leq i \leq m $ ).

You are given an array $ a $ consisting of $ n $ positive integers. Find the number of pairs of indices $ (l, r) $ , where $ 1 \le l \le r \le n $ , such that the array $ [a_l, a_{l+1}, \ldots, a_r] $ is good.

## 说明/提示

In the first test case, all subarrays of $ a $ are good, so all pairs are suitable.

In the second test case, the pairs $ (1, 1) $ , $ (2, 2) $ , and $ (3, 3) $ are suitable. For example, when $ (l, r) = (1, 2) $ , the array $ b=[1,1] $ is not good because $ b_2 < 2 $ .

## 样例 #1

### 输入

```
3
3
1 2 3
3
1 1 1
4
2 1 4 3```

### 输出

```
6
3
7```

# AI分析结果

### 题目内容重写

#### 题目描述

这是该问题的简单版本。在这个版本中，我们没有查询。请注意，在这个版本中我们有多个测试用例。只有当两个版本的问题都解决时，你才能进行 hack。

一个长度为 $m$ 的数组 $b$ 是好的，当且仅当对于所有 $i$，第 $i$ 个元素大于或等于 $i$。换句话说，$b$ 是好的当且仅当 $b_i \geq i$ 对于所有 $i$（$1 \leq i \leq m$）。

给定一个由 $n$ 个正整数组成的数组 $a$，找到满足条件的索引对 $(l, r)$ 的数量，其中 $1 \le l \le r \le n$，使得数组 $[a_l, a_{l+1}, \ldots, a_r]$ 是好的。

#### 说明/提示

在第一个测试用例中，$a$ 的所有子数组都是好的，因此所有对都满足条件。

在第二个测试用例中，对 $(1, 1)$、$(2, 2)$ 和 $(3, 3)$ 满足条件。例如，当 $(l, r) = (1, 2)$ 时，数组 $b=[1,1]$ 不是好的，因为 $b_2 < 2$。

#### 样例 #1

##### 输入

```
3
3
1 2 3
3
1 1 1
4
2 1 4 3
```

##### 输出

```
6
3
7
```

### 算法分类
二分、双指针

### 题解分析与结论

#### 题解1：lenlen
- **星级**：4
- **关键亮点**：使用倍增和二分查找来维护最大值，时间复杂度为 $O(n \log n)$，思路清晰，代码实现较为复杂但优化程度高。
- **核心实现思想**：对于每个 $i$，计算 $b_i = i+1-a_i$，然后使用倍增维护区间最大值，通过二分查找找到最小的 $l$ 满足条件。

#### 题解2：with_no_signal
- **星级**：5
- **关键亮点**：利用单调性，通过简单的双指针维护最小 $l$，时间复杂度为 $O(n)$，代码简洁且高效。
- **核心实现思想**：定义变量 $nw$ 表示满足条件的最小 $l$，每次更新 $nw$ 为 $i+1-a_i$ 和 $nw$ 的较大值，累加符合条件的区间数。

#### 题解3：loser_seele
- **星级**：4
- **关键亮点**：使用双指针维护符合条件的区间，时间复杂度为 $O(n)$，思路清晰，代码实现简单。
- **核心实现思想**：通过双指针维护满足条件的区间，左指针右移时不断增加右指针，累加符合条件的区间数。

### 最优关键思路或技巧
- **双指针维护单调性**：利用双指针维护满足条件的最小 $l$，时间复杂度为 $O(n)$，代码简洁且高效。
- **二分查找优化**：通过二分查找和倍增维护区间最大值，时间复杂度为 $O(n \log n)$，适用于需要更复杂维护的场景。

### 可拓展之处
- **类似问题**：可以扩展到需要维护区间最大值或最小值的问题，如滑动窗口最大值、区间最小值等。
- **算法套路**：双指针和二分查找是解决区间问题的常用技巧，可以应用于多种类似问题。

### 推荐题目
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P1440 求m区间内的最小值](https://www.luogu.com.cn/problem/P1440)
3. [P1638 访问艺术馆](https://www.luogu.com.cn/problem/P1638)

### 个人心得摘录
- **lenlen**：通过倍增和二分查找优化了最大值的维护，虽然代码复杂但效率高。
- **with_no_signal**：利用单调性简化了问题，代码简洁且高效，适合快速解决问题。
- **loser_seele**：双指针的实现简单直观，适合对时间复杂度要求不高但需要快速实现的情况。

---
处理用时：29.86秒