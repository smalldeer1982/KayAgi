# 题目信息

# Close Tuples (easy version)

## 题目描述

This is the easy version of this problem. The only difference between easy and hard versions is the constraints on $ k $ and $ m $ (in this version $ k=2 $ and $ m=3 $ ). Also, in this version of the problem, you DON'T NEED to output the answer by modulo.

You are given a sequence $ a $ of length $ n $ consisting of integers from $ 1 $ to $ n $ . The sequence may contain duplicates (i.e. some elements can be equal).

Find the number of tuples of $ m = 3 $ elements such that the maximum number in the tuple differs from the minimum by no more than $ k = 2 $ . Formally, you need to find the number of triples of indices $ i < j < z $ such that

 $ $$$\max(a_i, a_j, a_z) - \min(a_i, a_j, a_z) \le 2. $ $ </p><p>For example, if  $ n=4 $  and  $ a=\[1,2,4,3\] $ , then there are two such triples ( $ i=1, j=2, z=4 $  and  $ i=2, j=3, z=4 $ ). If  $ n=4 $  and  $ a=\[1,1,1,1\]$$$, then all four possible triples are suitable.

## 样例 #1

### 输入

```
4
4
1 2 4 3
4
1 1 1 1
1
1
10
5 6 1 3 2 9 8 1 2 4```

### 输出

```
2
4
0
15```

# AI分析结果

### 题目内容重写

**题目描述**

这是该问题的简单版本。简单版本和困难版本之间的唯一区别在于对 $k$ 和 $m$ 的约束（在这个版本中 $k=2$ 和 $m=3$）。此外，在这个版本的问题中，你不需要对答案取模。

给定一个长度为 $n$ 的整数序列 $a$，序列中的整数从 $1$ 到 $n$。序列可能包含重复元素（即某些元素可能相等）。

找到满足以下条件的 $m = 3$ 个元素的元组的数量：元组中的最大值与最小值的差不超过 $k = 2$。形式上，你需要找到满足以下条件的三元组索引 $i < j < z$ 的数量：

$$
\max(a_i, a_j, a_z) - \min(a_i, a_j, a_z) \le 2.
$$

例如，如果 $n=4$ 且 $a=[1,2,4,3]$，那么有两个这样的三元组（$i=1, j=2, z=4$ 和 $i=2, j=3, z=4$）。如果 $n=4$ 且 $a=[1,1,1,1]$，那么所有四个可能的三元组都满足条件。

### 算法分类
组合数学

### 题解分析与结论

该问题的核心在于如何高效地统计满足条件的三元组数量。由于题目要求最大值与最小值的差不超过2，因此可以通过排序后利用组合数学的方法来简化问题。大多数题解都采用了排序后枚举最小值，并通过二分查找或双指针来确定最大值的位置，进而计算满足条件的区间内的组合数。

### 评分较高的题解

#### 题解1：作者：light_ght (赞：6)
**星级：4.5**
**关键亮点：**
- 通过排序后枚举最小值，利用组合数公式计算满足条件的区间内的三元组数量。
- 使用双指针优化查找过程，避免了重复计算。
- 代码简洁，逻辑清晰。

**核心代码：**
```cpp
sort(ght+1, ght+t+1);
int r=1;
for(int i=1;i<=t;i++){
    while(ght[r+1]<=2+ght[i] && r+1<=t) 
        r++;
    if(r>=i+2)
        cnt+=(ll)(r-i-1)*(r-i);
}
```
**实现思想：**
排序后，使用双指针确定满足条件的区间，然后利用组合数公式计算区间内的三元组数量。

#### 题解2：作者：Weekoder (赞：5)
**星级：4.5**
**关键亮点：**
- 通过排序后枚举最小值，利用二分查找确定最大值的位置。
- 使用高斯求和公式计算区间内的三元组数量，避免了重复计算。
- 代码逻辑清晰，优化程度高。

**核心代码：**
```cpp
int bin_search(int X) {
    int l = X - 1, r = n + 1;
    while (l + 1 < r) {
        int mid = l + r >> 1;
        if (a[mid] - a[X] <= 2)
            l = mid;
        else
            r = mid;
    }
    return l;
}

int sum(int l, int r) {
    return (l + r) * (r - l + 1) / 2;
}
```
**实现思想：**
排序后，通过二分查找确定满足条件的区间，然后利用高斯求和公式计算区间内的三元组数量。

#### 题解3：作者：Graphcity (赞：4)
**星级：4**
**关键亮点：**
- 通过排序后枚举最小值，利用二分查找确定最大值的位置。
- 使用组合数公式计算区间内的三元组数量。
- 代码简洁，逻辑清晰。

**核心代码：**
```cpp
inline int Find(int x) {
    int l=1,r=n;
    while(l<r){
        int mid=(l+r+1)/2;
        if(a[mid]<=x) l=mid;
        else r=mid-1;
    }
    return l;
}
```
**实现思想：**
排序后，通过二分查找确定满足条件的区间，然后利用组合数公式计算区间内的三元组数量。

### 最优关键思路或技巧
1. **排序后枚举最小值**：通过排序将问题转化为在有序数组中寻找满足条件的区间，简化了最大最小值的计算。
2. **双指针或二分查找**：利用双指针或二分查找快速确定满足条件的区间，避免了暴力枚举的低效。
3. **组合数学**：通过组合数公式计算区间内的三元组数量，避免了重复计算。

### 可拓展之处
该问题的解法可以推广到更一般的条件，例如最大值与最小值的差不超过 $k$，或者元组的长度 $m$ 不同。类似的问题可以通过排序后利用组合数学的方法来解决。

### 推荐题目
1. [P1462E2 - Close Tuples (hard version)](https://www.luogu.com.cn/problem/CF1462E2)
2. [P1462E1 - Close Tuples (easy version)](https://www.luogu.com.cn/problem/CF1462E1)
3. [P1462E3 - Close Tuples (hard version)](https://www.luogu.com.cn/problem/CF1462E3)

### 个人心得摘录
- **light_ght**：在排序后枚举最小值时，通过双指针避免了重复计算，优化了时间复杂度。
- **Weekoder**：通过高斯求和公式计算区间内的三元组数量，避免了重复计算，提高了代码的效率。
- **Graphcity**：使用二分查找确定满足条件的区间，简化了问题的复杂度。

---
处理用时：40.10秒