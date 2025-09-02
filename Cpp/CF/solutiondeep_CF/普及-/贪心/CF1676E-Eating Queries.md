# 题目信息

# Eating Queries

## 题目描述

Timur has $ n $ candies. The $ i $ -th candy has a quantity of sugar equal to $ a_i $ . So, by eating the $ i $ -th candy, Timur consumes a quantity of sugar equal to $ a_i $ .

Timur will ask you $ q $ queries regarding his candies. For the $ j $ -th query you have to answer what is the minimum number of candies he needs to eat in order to reach a quantity of sugar greater than or equal to $ x_j $ or print -1 if it's not possible to obtain such a quantity. In other words, you should print the minimum possible $ k $ such that after eating $ k $ candies, Timur consumes a quantity of sugar of at least $ x_j $ or say that no possible $ k $ exists.

Note that he can't eat the same candy twice and queries are independent of each other (Timur can use the same candy in different queries).

## 说明/提示

For the first test case:

For the first query, Timur can eat any candy, and he will reach the desired quantity.

For the second query, Timur can reach a quantity of at least $ 10 $ by eating the $ 7 $ -th and the $ 8 $ -th candies, thus consuming a quantity of sugar equal to $ 14 $ .

For the third query, there is no possible answer.

For the fourth query, Timur can reach a quantity of at least $ 14 $ by eating the $ 7 $ -th and the $ 8 $ -th candies, thus consuming a quantity of sugar equal to $ 14 $ .

For the second test case:

For the only query of the second test case, we can choose the third candy from which Timur receives exactly $ 3 $ sugar. It's also possible to obtain the same answer by choosing the fourth candy.

## 样例 #1

### 输入

```
3
8 7
4 3 3 1 1 4 5 9
1
10
50
14
15
22
30
4 1
1 2 3 4
3
1 2
5
4
6```

### 输出

```
1
2
-1
2
3
4
8
1
1
-1```

# AI分析结果



# Eating Queries 吃糖查询

## 题目描述

Timur 有 $n$ 颗糖果，第 $i$ 颗糖的糖分为 $a_i$。他将进行 $q$ 次查询，每次查询给定一个目标糖分 $x_j$，要求回答吃掉最少多少颗糖才能使总糖分 ≥ $x_j$，若无法达到则输出 -1。所有查询相互独立（同一颗糖可在不同查询中重复使用）。

## 样例输入输出
见原题描述

---

## 题解综合分析

### 核心算法共性
所有题解均采用以下三步策略：
1. **降序排序**：将糖果按糖分从大到小排序
2. **前缀和预处理**：计算排序后的前缀和数组
3. **二分查找**：利用单调性快速定位最小糖果数

### 关键优化对比
| 优化点                | 手动二分实现 | STL lower_bound | 额外优化处理       |
|----------------------|------------|----------------|------------------|
| 边界条件处理          | 需自行判断  | 自动处理        | 先检查总和是否足够 |
| 代码简洁度            | 较低        | 极高           | 前缀和复用数组    |
| 时间复杂度            | O(n+qlog n)| 同左           | 同左             |

---

## 精选题解（4★+）

### 1. Otue 的题解（5★）
**亮点**：
- 直接使用 `lower_bound` 简化二分逻辑
- 前缀和数组独立存储避免污染原数据
- 预处理阶段即判断总和是否足够

```cpp
sort(a + 1, a + n + 1, cmp); // 降序排序
for (int i = 1; i <= n; i++) 
    sum[i] = sum[i - 1] + a[i];
// 查询时：
if (sum[n] < x) puts("-1");
else cout << lower_bound(...) - sum;
```

### 2. Coros_Trusds 的题解（4.5★）
**亮点**：
- 独立 solve 函数增强可读性
- 完整的手动二分模板
- 输入输出流加速处理

```cpp
int l = 1, r = n, ans = -1;
while (l <= r) {
    int mid = l + r >> 1;
    if (sum[mid] >= x) {
        ans = mid;
        r = mid - 1;
    } else {
        l = mid + 1;
    }
}
```

### 3. 5k_sync_closer 的题解（4★）
**亮点**：
- 复用原数组存储前缀和节省空间
- 极简代码风格（仅 23 行）

```cpp
sort(a + 1, a + n + 1, cmp);
for(int i = 2; i <= n; ++i) 
    a[i] += a[i - 1]; // 原数组存储前缀和
s = lower_bound(a + 1, a + n + 1, x) - a;
```

---

## 最优思路提炼
1. **贪心排序**：降序排列保证每次选择糖分最大的
2. **前缀和预处理**：O(n) 时间建立单调递增序列
3. **二分加速查询**：利用单调性将单次查询时间降至 O(logn)
4. **边界预判**：先检查总和是否小于查询值

## 同类拓展题目
1. [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)  
   （前缀和+区间查找）
2. [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)  
   （二分答案经典题）
3. [P1182 数列分段](https://www.luogu.com.cn/problem/P1182)  
   （最大值最小化问题）

---

## 调试心得摘录
> "发现暴力枚举会超时，突然意识到前缀和与二分的组合可以完美解决时间复杂度问题" —— CYZZ  
> **总结**：当发现 O(nq) 复杂度时，应立刻想到利用单调性进行二分优化

> "最初忘记处理总和不足的情况，导致二分返回错误下标" —— happy_zero  
> **总结**：使用 lower_bound 前必须验证可行性，否则可能返回伪解

---
处理用时：53.65秒