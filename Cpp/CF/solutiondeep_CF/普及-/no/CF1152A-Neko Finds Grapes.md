# 题目信息

# Neko Finds Grapes

## 题目描述

On a random day, Neko found $ n $ treasure chests and $ m $ keys. The $ i $ -th chest has an integer $ a_i $ written on it and the $ j $ -th key has an integer $ b_j $ on it. Neko knows those chests contain the powerful mysterious green Grapes, thus Neko wants to open as many treasure chests as possible.

The $ j $ -th key can be used to unlock the $ i $ -th chest if and only if the sum of the key number and the chest number is an odd number. Formally, $ a_i + b_j \equiv 1 \pmod{2} $ . One key can be used to open at most one chest, and one chest can be opened at most once.

Find the maximum number of chests Neko can open.

## 说明/提示

In the first example, one possible way to unlock $ 3 $ chests is as follows:

- Use first key to unlock the fifth chest,
- Use third key to unlock the second chest,
- Use fourth key to unlock the first chest.

In the second example, you can use the only key to unlock any single chest (note that one key can't be used twice).

In the third example, no key can unlock the given chest.

## 样例 #1

### 输入

```
5 4
9 14 6 2 11
8 4 7 20
```

### 输出

```
3```

## 样例 #2

### 输入

```
5 1
2 4 6 8 10
5
```

### 输出

```
1```

## 样例 #3

### 输入

```
1 4
10
20 30 40 50
```

### 输出

```
0```

# AI分析结果



# 中文重述题目

## 题目描述

某天，Neko 发现了 $n$ 个宝箱和 $m$ 把钥匙。第 $i$ 个宝箱上写着整数 $a_i$，第 $j$ 把钥匙上写着整数 $b_j$。当且仅当钥匙与宝箱上的数字之和为奇数时，钥匙可以打开宝箱。每把钥匙最多开一个宝箱，每个宝箱最多被打开一次。求最多能打开的宝箱数量。

---

**算法分类**：数学

---

## 题解综合分析

所有题解均基于**奇偶性数学原理**，核心思路为：
1. 统计宝箱中的奇/偶数数量（记为 $a_{odd}, a_{even}$）
2. 统计钥匙中的奇/偶数数量（记为 $b_{odd}, b_{even}$）
3. 最大匹配数为 $\min(a_{odd}, b_{even}) + \min(a_{even}, b_{odd})$  
（奇数+偶数=奇数，偶数+奇数=奇数）

---

## 精选题解（评分≥4星）

### 题解1：Dancing_Wave（4星）
**关键亮点**：代码极简，直接通过模运算统计奇偶数量。  
**核心代码**：
```cpp
int cnt1[2], cnt2[2]; // cnt1记录宝箱奇偶，cnt2记录钥匙奇偶
for(int i=1;i<=n;i++) cnt1[read()%2]++;
for(int i=1;i<=m;i++) cnt2[read()%2]++;
cout << min(cnt1[0], cnt2[1]) + min(cnt1[1], cnt2[0]);
```

### 题解2：WKAHPM（4星）
**关键亮点**：变量命名清晰，注释明确。  
**核心代码**：
```cpp
int lenji1, lenou1; // 宝箱奇偶计数
int lenji2, lenou2; // 钥匙奇偶计数
cout << min(lenji1, lenou2) + min(lenji2, lenou1);
```

### 题解3：ljc20020730（4星）
**关键亮点**：代码规范，输入处理简洁。  
**核心代码**：
```cpp
int cntA[2], cntB[2]; // 统计奇偶
for (int i=1;i<=n;i++) cntA[t%2]++;
for (int i=1;i<=m;i++) cntB[t%2]++;
ans = min(cntA[1], cntB[0]) + min(cntA[0], cntB[1]);
```

---

## 最优技巧总结
- **奇偶性配对**：利用奇偶相加为奇数的数学性质，将问题转化为统计交叉配对的最小值。
- **桶计数优化**：通过两个长度为2的数组（奇偶桶）快速统计元素属性，时间复杂度优化至 $O(n+m)$。

---

## 拓展练习
1. [P1469 找筷子](https://www.luogu.com.cn/problem/P1469) - 利用异或性质找唯一奇数个数元素
2. [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102) - 统计满足条件的数对数量
3. [P1638 逛画展](https://www.luogu.com.cn/problem/P1638) - 滑动窗口与奇偶性结合

---
处理用时：49.15秒