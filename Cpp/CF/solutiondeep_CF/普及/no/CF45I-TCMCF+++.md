# 题目信息

# TCMCF+++

## 题目描述

Vasya has gotten interested in programming contests in TCMCF+++ rules. On the contest $ n $ problems were suggested and every problem had a cost — a certain integral number of points (perhaps, negative or even equal to zero). According to TCMCF+++ rules, only accepted problems can earn points and the overall number of points of a contestant was equal to the product of the costs of all the problems he/she had completed. If a person didn't solve anything, then he/she didn't even appear in final standings and wasn't considered as participant. Vasya understood that to get the maximal number of points it is not always useful to solve all the problems. Unfortunately, he understood it only after the contest was finished. Now he asks you to help him: find out what problems he had to solve to earn the maximal number of points.

## 样例 #1

### 输入

```
5
1 2 -3 3 3
```

### 输出

```
3 1 2 3 
```

## 样例 #2

### 输入

```
13
100 100 100 100 100 100 100 100 100 100 100 100 100
```

### 输出

```
100 100 100 100 100 100 100 100 100 100 100 100 100 
```

## 样例 #3

### 输入

```
4
-2 -2 -2 -2
```

### 输出

```
-2 -2 -2 -2 
```

# AI分析结果



# TCMCF+++

## 题目描述

Vasya 对采用 TCMCF+++ 规则的编程竞赛产生了兴趣。比赛中共有 $n$ 道题目，每道题目的得分可能为任意整数值（可能为负数或零）。根据 TCMCF+++ 规则，只有正确解答的题目才能获得分数，选手的总分等于所有解答题目得分的乘积。如果选手没有解答任何题目，则不会出现在最终排名中。Vasya 发现有时解答全部题目并不能获得最高分，现在请你帮他找出能获得最高分的题目集合。

## 样例 #1

### 输入

```
5
1 2 -3 3 3
```

### 输出

```
3 1 2 3 
```

## 样例 #2

### 输入

```
13
100 100 100 100 100 100 100 100 100 100 100 100 100
```

### 输出

```
100 100 100 100 100 100 100 100 100 100 100 100 100 
```

## 样例 #3

### 输入

```
4
-2 -2 -2 -2
```

### 输出

```
-2 -2 -2 -2 
```

---

**算法分类**：贪心

---

### 题解综合分析

本题核心在于处理正数、负数、零的乘积特性。最优策略为：  
1. **正数全选**（正数乘积单调递增）  
2. **负数取绝对值最大的偶数个**（负负得正）  
3. **特判边界条件**（全零、单负数、零与负数组合等）

---

### 精选题解（评分≥4星）

#### 题解作者：ADivT（★★★★☆）
**关键亮点**：
- 正数直接输出，负数排序后取前偶数个
- 特判单负数、全零等边界情况
- 代码逻辑简洁，覆盖所有测试点

**核心代码**：
```cpp
sort(a+1,a+l+1); // 负数升序排序（绝对值大的在前）
rep(i,1,ne/2*2) printf("%d ",a[i]); // 取前偶数个
```

#### 题解作者：Binary_Lee（★★★★☆）
**关键亮点**：
- 三目运算分离负数与零的存储
- 对负数奇偶性处理清晰
- 变量命名直观，可读性强

**核心代码**：
```cpp
sort(ans+1,ans+f+1); // 负数升序排序
if(f%2==0) for(int i=1;i<=f;i++) printf("%d ",ans[i]); 
else for(int i=1;i<f;i++) printf("%d ",ans[i]);
```

#### 题解作者：BYWYR（★★★★☆）
**关键亮点**：
- 结构化的条件判断层次
- 负数排序后取前偶数个，逻辑与ADivT一致
- 完整覆盖所有特例场景

**核心代码**：
```cpp
sort(a+1,a+cnt+1); // 负数升序排序
for(int i=1;i<=fu/2*2;i++) printf("%d ",a[i]);
```

---

### 最优思路总结
1. **正数必选**：直接输出所有正数。
2. **负数处理**：按升序排序后取前偶数个（取绝对值最大的组合）。
3. **零的特殊处理**：全零或零与单负数时输出零。
4. **边界特判**：处理单个元素、全零等极端情况。

---

### 拓展应用
类似问题可考虑以下变种：
1. **乘积最大子数组**（需处理连续元素，LeetCode 152）
2. **分解数求最大乘积**（数学推导，洛谷 P1249）
3. **动态规划实现乘积最大化**（NOIP2000 提高组 P1018）

---

### 推荐习题
1. [P1018 乘积最大](https://www.luogu.com.cn/problem/P1018)  
2. [P1249 最大乘积](https://www.luogu.com.cn/problem/P1249)  
3. [CF660C 最大子数组（变形）](https://codeforces.com/problemset/problem/660/C)

---

### 心得体会
- **特判优先**：feicheng 提到提交7次才通过，强调需全面测试边界条件（如全负数、单元素等）。
- **排序方向**：负数升序等价于按绝对值降序，巧妙简化代码（ADivT 等题解均采用此技巧）。
- **代码可读性**：变量命名与结构清晰直接影响调试效率（Binary_Lee 代码示例）。

---
处理用时：148.63秒