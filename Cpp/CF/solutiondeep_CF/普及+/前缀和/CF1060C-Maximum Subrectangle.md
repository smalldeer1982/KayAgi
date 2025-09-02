# 题目信息

# Maximum Subrectangle

## 题目描述

You are given two arrays $ a $ and $ b $ of positive integers, with length $ n $ and $ m $ respectively.

Let $ c $ be an $ n \times m $ matrix, where $ c_{i,j} = a_i \cdot b_j $ .

You need to find a subrectangle of the matrix $ c $ such that the sum of its elements is at most $ x $ , and its area (the total number of elements) is the largest possible.

Formally, you need to find the largest number $ s $ such that it is possible to choose integers $ x_1, x_2, y_1, y_2 $ subject to $ 1 \leq x_1 \leq x_2 \leq n $ , $ 1 \leq y_1 \leq y_2 \leq m $ , $ (x_2 - x_1 + 1) \times (y_2 - y_1 + 1) = s $ , and $ $$ \sum_{i=x_1}^{x_2}{\sum_{j=y_1}^{y_2}{c_{i,j}}} \leq x. $ $$

## 说明/提示

Matrix from the first sample and the chosen subrectangle (of blue color):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1060C/ea340f2e4123e359048067db39cb97e3a56962fb.png)Matrix from the second sample and the chosen subrectangle (of blue color):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1060C/29ed72ba75c43c8c56e95a795caca1696bad260c.png)

## 样例 #1

### 输入

```
3 3
1 2 3
1 2 3
9
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5 1
5 4 2 4 5
2
5
```

### 输出

```
1
```

# AI分析结果



# Maximum Subrectangle

## 题目描述

给定两个正整数数组 $a$ 和 $b$，长度分别为 $n$ 和 $m$。定义 $n \times m$ 矩阵 $c$ 满足 $c_{i,j} = a_i \cdot b_j$。要求找到一个子矩形，其元素和不超过 $x$，且面积（元素总数）尽可能大。需满足：存在 $1 \leq x_1 \leq x_2 \leq n$，$1 \leq y_1 \leq y_2 \leq m$，使得子矩阵面积为 $(x_2-x_1+1) \times (y_2-y_1+1)$，且 $\sum_{i=x_1}^{x_2}\sum_{j=y_1}^{y_2}c_{i,j} \leq x$。

## 样例 #1

### 输入
```
3 3
1 2 3
1 2 3
9
```

### 输出
```
4
```

---

## 题解分析与结论

### 核心思路
通过数学变换 $\sum \sum (a_i \cdot b_j) = (\sum a_i)(\sum b_j)$，将二维问题转化为一维处理。预处理两个数组所有可能长度的最小区间和，枚举长度组合判断是否满足条件。

### 最优解法
1. **预处理最小区间和**：对数组 $a$ 和 $b$，分别计算每个可能长度的区间和最小值（时间复杂度 $O(n^2)$）
2. **枚举组合**：遍历所有可能的长度组合 $i \times j$，若 $minA[i] \times minB[j] \leq x$ 则更新最大面积

---

## 精选题解

### 题解1：Bitter_Tea（⭐⭐⭐⭐⭐）
**亮点**：  
- 完整展现数学变换过程，代码结构清晰
- 关键变量命名规范（fa/fb 表示最小区间和数组）
- 注释提醒数据类型溢出问题

**核心代码**：
```cpp
// 预处理 a 数组各长度的最小区间和
for(int i=1;i<=n;i++)
    for(int j=1;j<=i;j++)
        fa[i-j+1] = min(fa[i-j+1], sa[i]-sa[j-1]);

// 枚举所有可能组合
for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
        if((ll)fa[i]*fb[j] <= x) 
            ans = max(ans, i*j);
```

### 题解2：PR_CYJ（⭐⭐⭐⭐）
**亮点**：
- 预处理时使用 `0x7f` 初始化确保正确性
- 强调贪心策略的数学证明
- 代码加入防御性数据类型转换

**代码技巧**：
```cpp
memset(mina, 0x7f, sizeof(mina)); // 正确初始化技巧
if ((long long)(mina[i])*minb[j] <= k) // 防御性类型转换
```

---

## 关键技巧与拓展

### 核心技巧
1. **数学变换降维**：利用乘法分配律将二维问题分解为两个一维问题
2. **预处理优化**：通过 $O(n^2)$ 预处理避免暴力枚举的高复杂度
3. **贪心策略**：维护每个长度的最小区间和，保证后续枚举的有效性

### 类似题目
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)（一维最小区间和）
2. [P1719 最大加权矩形](https://www.luogu.com.cn/problem/P1719)（二维前缀和优化）
3. [P1638 逛画展](https://www.luogu.com.cn/problem/P1638)（滑动窗口与区间统计）

---

## 调试心得摘录

1. **数据类型陷阱**：多位题解作者强调 `(long long)` 强制转换的必要性
2. **初始化重要性**：PR_CYJ 指出 `mina[]` 必须初始化为极大值（如 `0x7f`）
3. **数学直觉培养**：Hisaishi_Kanade 提到最初陷入二分答案误区，后通过数学分析找到正解

> "本题看似二维问题，实则通过乘法分配律转化为两个一维问题的组合，这种维度转换思维在矩阵类问题中极为常见" —— Bitter_Tea

---
处理用时：50.35秒