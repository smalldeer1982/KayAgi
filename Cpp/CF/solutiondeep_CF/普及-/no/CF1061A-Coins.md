# 题目信息

# Coins

## 题目描述

You have unlimited number of coins with values $ 1, 2, \ldots, n $ . You want to select some set of coins having the total value of $ S $ .

It is allowed to have multiple coins with the same value in the set. What is the minimum number of coins required to get sum $ S $ ?

## 说明/提示

In the first example, some of the possible ways to get sum $ 11 $ with $ 3 $ coins are:

- $ (3, 4, 4) $
- $ (2, 4, 5) $
- $ (1, 5, 5) $
- $ (3, 3, 5) $

It is impossible to get sum $ 11 $ with less than $ 3 $ coins.

In the second example, some of the possible ways to get sum $ 16 $ with $ 3 $ coins are:

- $ (5, 5, 6) $
- $ (4, 6, 6) $

It is impossible to get sum $ 16 $ with less than $ 3 $ coins.

## 样例 #1

### 输入

```
5 11
```

### 输出

```
3```

## 样例 #2

### 输入

```
6 16
```

### 输出

```
3```

# AI分析结果



# Coins

## 题目描述

给定无限个面值为 $1, 2, \ldots, n$ 的硬币。你需要选择若干硬币使其总和为 $S$（允许重复使用相同面值的硬币）。求所需硬币的最少数量。

## 说明/提示

第一个样例中，用 3 个硬币组成 11 的方式包括：  
- (3,4,4)  
- (2,4,5)  
- (1,5,5)  
- (3,3,5)  

第二个样例中，用 3 个硬币组成 16 的方式包括：  
- (5,5,6)  
- (4,6,6)  

---

**算法分类**: 贪心

---

### 题解分析与结论

所有题解均基于贪心思想：尽可能使用大面值硬币以减少总数量。核心公式为 $\lceil \frac{S}{n} \rceil$，即通过数学计算直接得出结果，时间复杂度为 $O(1)$。

#### 精选题解

1. **sysu_yzc（5星）**  
   **关键亮点**: 直接数学推导，代码简洁高效。  
   **核心思路**: 使用 $\lceil \frac{S}{n} \rceil$ 公式，通过判断余数是否存在来决定是否加1。  
   **代码片段**:
   ```cpp
   if(s%n==0) cout<<s/n;
   else cout<<s/n+1;
   ```

2. **XLost（5星）**  
   **关键亮点**: 公式等价变形为 $(S-1)/n +1$，避免浮点运算。  
   **核心思路**: 通过整数运算直接实现向上取整。  
   **代码片段**:
   ```cpp
   m = (s - 1) / n + 1;
   ```

---

### 最优思路总结

**关键技巧**:  
- 利用数学公式直接计算，无需遍历。  
- 避免浮点运算的整数实现技巧：$(S-1)/n +1$。

**可拓展方向**:  
- 类似贪心问题（如找零钱问题）中，当硬币面值连续时可直接数学优化。  
- 非连续面值时需用动态规划或完全背包解法。

---

### 同类题目推荐

1. [P1031 均分纸牌](https://www.luogu.com.cn/problem/P1031)  
   **标签**: 贪心、数学  
   **难度**: 普及-

2. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)  
   **标签**: 贪心、字符串处理  
   **难度**: 普及-

3. [P1209 [USACO1.3] 修理牛棚 Barn Repair](https://www.luogu.com.cn/problem/P1209)  
   **标签**: 贪心、排序  
   **难度**: 普及-

---
处理用时：67.66秒