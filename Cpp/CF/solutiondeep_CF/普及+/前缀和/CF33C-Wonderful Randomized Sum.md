# 题目信息

# Wonderful Randomized Sum

## 题目描述

Learn, learn and learn again — Valera has to do this every day. He is studying at mathematical school, where math is the main discipline. The mathematics teacher loves her discipline very much and tries to cultivate this love in children. That's why she always gives her students large and difficult homework. Despite that Valera is one of the best students, he failed to manage with the new homework. That's why he asks for your help. He has the following task. A sequence of $ n $ numbers is given. A prefix of a sequence is the part of the sequence (possibly empty), taken from the start of the sequence. A suffix of a sequence is the part of the sequence (possibly empty), taken from the end of the sequence. It is allowed to sequentially make two operations with the sequence. The first operation is to take some prefix of the sequence and multiply all numbers in this prefix by $ -1 $ . The second operation is to take some suffix and multiply all numbers in it by $ -1 $ . The chosen prefix and suffix may intersect. What is the maximum total sum of the sequence that can be obtained by applying the described operations?

## 样例 #1

### 输入

```
3
-1 -2 -3
```

### 输出

```
6
```

## 样例 #2

### 输入

```
5
-4 2 0 5 0
```

### 输出

```
11
```

## 样例 #3

### 输入

```
5
-1 10 -5 10 -2
```

### 输出

```
18
```

# AI分析结果



# Wonderful Randomized Sum 的题解分析

## 题目重写
### 题目描述
Valera 遇到了一个数学难题：给定一个包含 $n$ 个数字的序列，允许进行两次操作：第一次选取任意前缀（可以为空）将所有元素乘以 -1，第二次选取任意后缀（可以为空）将所有元素乘以 -1。前缀和后缀可以相交，求最终能得到的最大序列和。

### 输入样例
```
3
-1 -2 -3
```
### 输出样例
```
6
```

---

## 题解综合分析
### 关键思路总结
1. **数学推导转换**：通过观察前缀后缀相交抵消的特性，将问题转化为求原序列的最大子段和。设原序列总和为 $S$，中间未变化部分的和为 $C$，则最终和为 $2C-S$。
2. **Kadane 算法应用**：使用线性时间复杂度的最大子段和算法求解 $C$，时间复杂度 $O(n)$。
3. **逆向思维优化**：将前缀和后缀的符号反转操作转换为保留中间段的符号不变，其余部分反转两次。

---

## 高分题解推荐
### 1. LuckyCloud 的题解（⭐⭐⭐⭐⭐）
**核心亮点**：
- 通过数学推导将问题转化为经典最大子段和问题
- 代码简洁高效，时间复杂度 $O(n)$
- 逻辑清晰，推导过程严谨

**关键代码**：
```cpp
long long sum = 0, max_sub = 0, current = 0;
for (int i = 0; i < n; ++i) {
    current = max(current + a[i], 0LL);
    max_sub = max(max_sub, current);
    sum += a[i];
}
cout << 2 * max_sub - sum;
```
**实现思想**：维护当前子段和 `current`，当累加值为负时重置，最终取历史最大值。

### 2. Level_Down 的题解（⭐⭐⭐⭐）
**核心亮点**：
- 逆向思维直接计算反转后的影响
- 代码极简，仅需一次遍历
- 巧妙利用最大子段和的相反数关系

**代码片段**：
```cpp
int sum = 0, max_ending_here = 0, max_so_far = 0;
for (int i = 0; i < n; ++i) {
    sum += a[i];
    max_ending_here = max(max_ending_here + a[i], 0);
    max_so_far = max(max_so_far, max_ending_here);
}
cout << 2 * max_so_far - sum;
```

### 3. _lxy_ 的题解（⭐⭐⭐⭐）
**核心亮点**：
- 明确将问题拆分为保留段与反转段的数学关系
- 代码精简且包含详细注释
- 直接输出公式结果，无需额外存储

**代码特点**：
```cpp
int mx = 0, maxx = 0;
for (int x : a) {
    mx = max(mx + x, 0);
    maxx = max(maxx, mx);
}
cout << 2 * maxx - sum;
```

---

## 最优思路总结
**核心技巧**：将问题转化为求最大子段和的经典问题，利用 Kadane 算法的线性时间复杂度特性。通过数学公式 $ans = 2C - S$ 直接计算结果，其中 $C$ 是最大子段和，$S$ 是原序列总和。

**同类题目拓展**：
1. [最大子段和](https://www.luogu.com.cn/problem/P1115)（洛谷 P1115）
2. [乘积最大子数组](https://leetcode.cn/problems/maximum-product-subarray/)（LeetCode 152）
3. [环形子数组的最大和](https://leetcode.cn/problems/maximum-sum-circular-subarray/)（LeetCode 918）

---

## 相似题目推荐
1. **洛谷 P1115** - 最大子段和（直接应用 Kadane 算法）
2. **洛谷 P1121** - 环状最大子段和（环形数组变种）
3. **洛谷 P1982** - 小朋友的数字（最大子段和与前缀特性结合）

---
处理用时：48.15秒