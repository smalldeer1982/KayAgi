# 题目信息

# Teams Forming

## 题目描述

There are $ n $ students in a university. The number of students is even. The $ i $ -th student has programming skill equal to $ a_i $ .

The coach wants to form $ \frac{n}{2} $ teams. Each team should consist of exactly two students, and each student should belong to exactly one team. Two students can form a team only if their skills are equal (otherwise they cannot understand each other and cannot form a team).

Students can solve problems to increase their skill. One solved problem increases the skill by one.

The coach wants to know the minimum total number of problems students should solve to form exactly $ \frac{n}{2} $ teams (i.e. each pair of students should form a team). Your task is to find this number.

## 说明/提示

In the first example the optimal teams will be: $ (3, 4) $ , $ (1, 6) $ and $ (2, 5) $ , where numbers in brackets are indices of students. Then, to form the first team the third student should solve $ 1 $ problem, to form the second team nobody needs to solve problems and to form the third team the second student should solve $ 4 $ problems so the answer is $ 1 + 4 = 5 $ .

In the second example the first student should solve $ 99 $ problems to form a team with the second one.

## 样例 #1

### 输入

```
6
5 10 2 3 14 5
```

### 输出

```
5
```

## 样例 #2

### 输入

```
2
1 100
```

### 输出

```
99
```

# AI分析结果



# Teams Forming 题解分析

## 题目重述

### 题目描述

某大学有 $n$ 名学生（保证 $n$ 是偶数），第 $i$ 名学生的编程能力值为 $a_i$。教练希望将这些学生分成 $\frac{n}{2}$ 个两人团队，要求每个团队的两名学生能力值相同（可通过解题提升能力值，每解一题能力值加1）。求最小总解题数。

### 样例解释

- 样例1输入 `6 5 10 2 3 14 5`，排序后为 `[2,3,5,5,10,14]`，最佳分组为 (2,3)、(5,5)、(10,14)，解题数为 1+0+4=5。
- 样例2输入 `2 1 100`，需将1提升99次，总解题数99。

---

## 算法分类
**贪心、排序**

---

## 题解对比与结论

### 核心思路
1. **排序后相邻配对**：将能力值排序后，相邻两个学生配对，计算差值总和。
2. **数学证明**：对于四个有序数 $a \leq b \leq c \leq d$，相邻配对 $(b-a)+(d-c)$ 总差值最小。

### 最优题解（评分≥4星）

#### 1. YYen 题解（★★★★★）
**关键亮点**：  
- 明确给出贪心策略的数学证明，用四个数的差值对比说明相邻配对最优性。
- 代码清晰，数组索引从1开始便于理解。

**核心代码**：
```cpp
sort(a + 1, a + n + 1);
for (int i = 1; i <= n; i += 2) 
    ans += a[i + 1] - a[i];
```

#### 2. Zechariah 题解（★★★★☆）
**关键亮点**：  
- 从后向前遍历配对，同样基于贪心策略，提供另一种实现视角。
- 通过反证法说明不存在更优的配对方式。

**核心代码**：
```cpp
sort(a + 1, a + n + 1);
for (int i = n; i >= 2; i -= 2)
    ans += a[i] - a[i - 1];
```

#### 3. Trimsteanima 题解（★★★★☆）
**关键亮点**：  
- 代码简洁高效，直接体现排序和差值累加的核心逻辑。
- 从0索引开始处理，适合习惯C风格数组的读者。

**核心代码**：
```cpp
sort(a, a + n);
for (i = 0; i < n; i += 2)
    ans += a[i + 1] - a[i];
```

---

## 关键思路总结
1. **贪心策略**：排序后相邻配对，确保每对差值最小。
2. **数学优化**：通过局部最优（相邻配对）推导全局最优，避免复杂计算。
3. **代码实现**：统一使用排序和步进2的循环结构，时间复杂度 $O(n \log n)$。

---

## 拓展建议
- **同类问题**：  
  - [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：贪心排序处理等待时间。  
  - [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)：双指针配对求最小组数。  
  - [P1209 修理牛棚](https://www.luogu.com.cn/problem/P1209)：间隔排序选择最大空隙。  

- **调试技巧**：  
  - 验证排序后的配对是否覆盖所有元素。  
  - 检查数组索引边界（如从0或1开始时的循环条件）。

---
处理用时：124.12秒