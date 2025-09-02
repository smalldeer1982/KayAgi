# 题目信息

# Sakurako and Water

## 题目描述

During her journey with Kosuke, Sakurako and Kosuke found a valley that can be represented as a matrix of size $ n \times n $ , where at the intersection of the $ i $ -th row and the $ j $ -th column is a mountain with a height of $ a_{i,j} $ . If $ a_{i,j} < 0 $ , then there is a lake there.

Kosuke is very afraid of water, so Sakurako needs to help him:

- With her magic, she can select a square area of mountains and increase the height of each mountain on the main diagonal of that area by exactly one.

More formally, she can choose a submatrix with the upper left corner located at $ (i, j) $ and the lower right corner at $ (p, q) $ , such that $ p-i=q-j $ . She can then add one to each element at the intersection of the $ (i + k) $ -th row and the $ (j + k) $ -th column, for all $ k $ such that $ 0 \le k \le p-i $ .

Determine the minimum number of times Sakurako must use her magic so that there are no lakes.

## 样例 #1

### 输入

```
4
1
1
2
-1 2
3 0
3
1 2 3
-2 1 -1
0 0 -1
5
1 1 -1 -1 3
-3 1 4 4 -4
-1 -1 3 0 -5
4 5 3 -3 -1
3 1 -3 -1 5```

### 输出

```
0
1
4
19```

# AI分析结果



# Sakurako and Water

## 题目描述

在与 Kosuke 的旅程中，Sakurako 和 Kosuke 发现了一个可以用 $n \times n$ 矩阵表示的山谷。矩阵中第 $i$ 行第 $j$ 列的山峰高度为 $a_{i,j}$。若 $a_{i,j} < 0$，则该位置有湖泊。

Sakurako 的魔法可以选定一个正方形区域，将该区域主对角线上的所有山峰高度增加 1。每次操作需要满足子矩阵的左上角 $(i,j)$ 和右下角 $(p,q)$ 满足 $p-i = q-j$。

求消除所有湖泊所需的最小操作次数。

## 样例 #1

### 输入

```
4
1
1
2
-1 2
3 0
3
1 2 3
-2 1 -1
0 0 -1
5
1 1 -1 -1 3
-3 1 4 4 -4
-1 -1 3 0 -5
4 5 3 -3 -1
3 1 -3 -1 5
```

### 输出

```
0
1
4
19
```

---

### 题解综合分析

**核心思路**：每条主对角线（i-j 相同的元素）独立处理，操作次数由该对角线上的最小值决定。若最小值为负数，则需操作其绝对值次数。

**最优策略**：对于每条对角线，记录所有元素的最小值，累加所有负最小值的绝对值之和。

### 高星题解推荐

#### 1. 作者：Super_Cube（⭐⭐⭐⭐⭐）
**关键亮点**：
- 提出"对角线独立"的核心观点
- 推导出直接求最小值的数学公式
- 代码简洁高效，时间复杂度 O(n²)

**核心代码**：
```cpp
for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
        b[i-j+n]=min(b[i-j+n],a[i][j]);
for(int i=1;i<=(n<<1)-1;i++)
    ans += max(0,-b[i]);
```

#### 2. 作者：lailai0916（⭐⭐⭐⭐⭐）
**实现亮点**：
- 使用偏移量处理负数索引
- 详细处理输入边界
- 完整展示预处理和计算过程

**调试心得**：
> "通过将 i-j 转换为正数索引，避免了数组越界问题。"

#### 3. 作者：chenxi2009（⭐⭐⭐⭐）
**优化技巧**：
- 使用动态维护最大值代替最终遍历
- 紧凑的代码结构
- 包含完整的输入输出处理

**关键片段**：
```cpp
int c = i-j;
int id = c + n-1;
maxx[id] = max(maxx[id], -a[i][j]);
```

---

### 举一反三
1. **同类型题**：涉及矩阵对角线操作的问题，如 [CF1391D](https://www.luogu.com.cn/problem/CF1391D)（矩阵斜边处理）
2. **类似技巧**：分治思想处理独立子问题，如 [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)（对角线约束处理）
3. **优化套路**：预处理极值加速计算，如 [P1719 最大加权矩形](https://www.luogu.com.cn/problem/P1719)（前缀和+极值维护）

### 推荐练习
1. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219) - 对角线约束应用
2. [CF1391D](https://www.luogu.com.cn/problem/CF1391D) - 矩阵斜边特性运用
3. [P1719 最大加权矩形](https://www.luogu.com.cn/problem/P1719) - 极值预处理技巧

---
处理用时：70.90秒