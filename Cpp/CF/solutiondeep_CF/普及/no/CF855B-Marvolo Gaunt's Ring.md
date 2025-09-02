# 题目信息

# Marvolo Gaunt's Ring

## 题目描述

Professor Dumbledore is helping Harry destroy the Horcruxes. He went to Gaunt Shack as he suspected a Horcrux to be present there. He saw Marvolo Gaunt's Ring and identified it as a Horcrux. Although he destroyed it, he is still affected by its curse. Professor Snape is helping Dumbledore remove the curse. For this, he wants to give Dumbledore exactly $ x $ drops of the potion he made.

Value of $ x $ is calculated as maximum of $ p·a_{i}+q·a_{j}+r·a_{k} $ for given $ p,q,r $ and array $ a_{1},a_{2},...\ a_{n} $ such that $ 1<=i<=j<=k<=n $ . Help Snape find the value of $ x $ . Do note that the value of $ x $ may be negative.

## 说明/提示

In the first sample case, we can take $ i=j=k=5 $ , thus making the answer as $ 1·5+2·5+3·5=30 $ .

In second sample case, selecting $ i=j=1 $ and $ k=5 $ gives the answer $ 12 $ .

## 样例 #1

### 输入

```
5 1 2 3
1 2 3 4 5
```

### 输出

```
30
```

## 样例 #2

### 输入

```
5 1 2 -3
-1 -2 -3 -4 -5
```

### 输出

```
12
```

# AI分析结果



# Marvolo Gaunt的戒指

## 题目描述

邓布利多教授正在帮助哈利摧毁魂器。他来到冈特小屋，怀疑这里藏有魂器。他发现了Marvolo Gaunt的戒指并确认其为魂器。虽然摧毁了它，但仍受其诅咒影响。斯内普教授准备给邓布利多恰好x滴药水。

x的计算公式为给定p,q,r和数组a₁,a₂,...aₙ时，满足1≤i≤j≤k≤n的p·aᵢ + q·aⱼ + r·aₖ的最大值。注意x可能为负数。

## 说明/提示

样例1中取i=j=k=5，计算结果为30。样例2中取i=j=1、k=5得到12。

## 样例 #1

### 输入
```
5 1 2 3
1 2 3 4 5
```

### 输出
```
30
```

## 样例 #2

### 输入
```
5 1 2 -3
-1 -2 -3 -4 -5
```

### 输出
```
12
```

---

**算法分类**：动态规划

---

### 题解分析与结论

#### 关键思路对比
1. **动态规划递推**（BoAn、JackWei、Coros_Trusds）
   - 定义状态数组逐步递推计算各阶段最大值
   - 时间复杂度O(n)，空间复杂度可优化至O(1)
2. **区间最值预处理**（一扶苏一、Gaode_Sean、Nicrobot）
   - 预处理前缀后缀最值，枚举中间点结合极值计算
   - 时间复杂度O(n)或O(n log n)

#### 最优解法总结
动态规划解法通过维护三个状态：
- `max(p·a_i)`
- `max(p·a_i + q·a_j)`
- `max(p·a_i + q·a_j + r·a_k)`
每个状态仅依赖前序结果，最终复杂度O(n)且无需额外空间。

---

### 精选题解

#### 1. JackWei的题解（⭐⭐⭐⭐⭐）
**核心亮点**：
- 滚动数组优化空间至O(1)
- 代码简洁高效，仅需单次遍历
```cpp
ll dp[3] = {-INF, -INF, -INF};
for(int i=1; i<=n; i++){
    dp[0] = max(dp[0], (ll)x*p); 
    dp[1] = max(dp[1], dp[0] + (ll)x*q);
    dp[2] = max(dp[2], dp[1] + (ll)x*r);
}
```

#### 2. Gaode_Sean的题解（⭐⭐⭐⭐）
**核心亮点**：
- 前缀最大值与后缀最大值预处理
- 枚举中间点直接计算组合极值
```cpp
for(int i=1; i<=n; i++){
    ans = max(ans, f[i] + a[i]*q + g[i]);
}
```

#### 3. BoAn的题解（⭐⭐⭐⭐）
**核心亮点**：
- 经典的三层状态递推结构
- 状态转移逻辑清晰易理解
```cpp
f[i][1] = max(f[i-1][1], a[i]*p);
f[i][2] = max(f[i-1][2], f[i][1]+a[i]*q);
f[i][3] = max(f[i-1][3], f[i][2]+a[i]*r);
```

---

### 关键技巧总结
- **分阶段动态规划**：将复合条件分解为多个单条件极值问题
- **滚动数组优化**：通过状态覆盖降低空间复杂度
- **符号敏感处理**：根据系数符号选择最大/最小值（在预处理解法中）

---

### 拓展练习
1. [最大子序和](https://www.luogu.com.cn/problem/P1115)（一维极值）
2. [乘积最大子数组](https://www.luogu.com.cn/problem/P1567)（双状态维护）
3. [打家劫舍 III](https://leetcode-cn.com/problems/house-robber-iii/)（树形DP递推）

---

### 心得体会摘录
> "枚举中间点后，发现i和k的最优解可以通过预处理得到，这个转化是解题的关键" —— 一扶苏一  
> "DP状态定义要确保满足i≤j≤k的条件，通过分步递推自然满足这个约束" —— Coros_Trusds  
> "测试时发现负数情况没处理好，意识到初始化必须用极小值而非0" —— BoAn

---
处理用时：73.27秒