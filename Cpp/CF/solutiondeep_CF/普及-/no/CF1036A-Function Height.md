# 题目信息

# Function Height

## 题目描述

You are given a set of $ 2n+1 $ integer points on a Cartesian plane. Points are numbered from $ 0 $ to $ 2n $ inclusive. Let $ P_i $ be the $ i $ -th point. The $ x $ -coordinate of the point $ P_i $ equals $ i $ . The $ y $ -coordinate of the point $ P_i $ equals zero (initially). Thus, initially $ P_i=(i,0) $ .

The given points are vertices of a plot of a piecewise function. The $ j $ -th piece of the function is the segment $ P_{j}P_{j + 1} $ .

In one move you can increase the $ y $ -coordinate of any point with odd $ x $ -coordinate (i.e. such points are $ P_1, P_3, \dots, P_{2n-1} $ ) by $ 1 $ . Note that the corresponding segments also change.

For example, the following plot shows a function for $ n=3 $ (i.e. number of points is $ 2\cdot3+1=7 $ ) in which we increased the $ y $ -coordinate of the point $ P_1 $ three times and $ y $ -coordinate of the point $ P_5 $ one time:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1036A/04a4a03c886e714b20b2d32a2aa307f64861219c.png)Let the area of the plot be the area below this plot and above the coordinate axis OX. For example, the area of the plot on the picture above is 4 (the light blue area on the picture above is the area of the plot drawn on it).

Let the height of the plot be the maximum $ y $ -coordinate among all initial points in the plot (i.e. points $ P_0, P_1, \dots, P_{2n} $ ). The height of the plot on the picture above is 3.

Your problem is to say which minimum possible height can have the plot consisting of $ 2n+1 $ vertices and having an area equal to $ k $ . Note that it is unnecessary to minimize the number of moves.

It is easy to see that any answer which can be obtained by performing moves described above always exists and is an integer number not exceeding $ 10^{18} $ .

## 说明/提示

One of the possible answers to the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1036A/9b7ffb43d6497943731f35d46eb19664771e1698.png)The area of this plot is 3, the height of this plot is 1.

There is only one possible answer to the second example:

 ![](/predownloaded/87/0e/870ecd0db34c7f6d9c82c27dbd8add2b8f3f537c.png)The area of this plot is 12, the height of this plot is 3.

## 样例 #1

### 输入

```
4 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4 12
```

### 输出

```
3
```

## 样例 #3

### 输入

```
999999999999999999 999999999999999986
```

### 输出

```
1
```

# AI分析结果



# Function Height 题解分析

**算法分类**：数学

---

## 题目重写
给定笛卡尔坐标系中 $2n+1$ 个点，初始时所有点位于 $x$ 轴，坐标为 $(i,0)$。每次操作可将奇数下标点（$P_1, P_3, \dots, P_{2n-1}$）的 $y$ 坐标增加 1。求在总面积恰好为 $k$ 的前提下，所有点中最大的 $y$ 坐标的最小可能值。

---

## 题解对比与结论

### 核心思路
所有题解均指出：
1. 每个相邻偶点间的三角形底边长为 2，面积等于其对应的高（$h_i$）。
2. 总面积为 $\sum h_i = k$，要求最小化 $\max(h_i)$。
3. 最优解为平均分配高度，即 $\lceil k/n \rceil$，可通过 $(k + n - 1) // n$ 实现。

### 最优题解
1. **作者：きりと（★★★★★）**
   - **亮点**：代码简洁，直接使用整数运算避免浮点误差。
   - **代码**：
     ```cpp
     cout << (y + x - 1) / x;
     ```

2. **作者：diqiuyi（★★★★☆）**
   - **亮点**：详细推导公式，明确解释 `ceil(k/n)` 的等价实现。
   - **关键说明**：使用 `(k + n - 1) / n` 替代浮点运算的数学原理。

3. **作者：makerlife（★★★★☆）**
   - **亮点**：公式推导清晰，强调数据范围需用 `long long`。
   - **代码片段**：
     ```cpp
     printf("%lld\n", (k + n - (ll)1) / n);
     ```

---

## 关键技巧
1. **向上取整的整数实现**：使用 `(k + n - 1) // n` 代替 `ceil(k/n)`，避免浮点运算的精度问题。
2. **数学建模**：将几何问题转化为数列平均分配问题，利用数学极值原理求解。

---

## 类似题目推荐
1. [P1226 【模板】快速幂](https://www.luogu.com.cn/problem/P1226) - 数学优化技巧。
2. [P1181 数列分段 Section I](https://www.luogu.com.cn/problem/P1181) - 分组求最大值最小。
3. [P1984 [SDOI2008] 烧水问题](https://www.luogu.com.cn/problem/P1984) - 分配热量优化。

---

## 个人心得摘录
- **数据范围陷阱**：多个题解强调必须使用 `long long`（如 `diqiuyi` 题解的注释）。
- **函数选择**：`_lgh_` 的题解提到 `ceil` 函数可能失效，需改用整数运算。
- **思维转换**：`Jerrlee✅` 指出需将几何问题抽象为数学分配模型。

---
处理用时：34.63秒