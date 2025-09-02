# 题目信息

# Find a Mine

## 题目描述

This is an interactive problem.

You are given a grid with $ n $ rows and $ m $ columns. The coordinates $ (x, y) $ represent the cell on the grid, where $ x $ ( $ 1 \leq x \leq n $ ) is the row number counting from the top and $ y $ ( $ 1 \leq y \leq m $ ) is the column number counting from the left. It is guaranteed that there are exactly $ 2 $ mines in the grid at distinct cells, denoted as $ (x_1, y_1) $ and $ (x_2, y_2) $ . You are allowed to make no more than $ 4 $ queries to the interactor, and after these queries, you need to provide the location of one of the mines.

In each query, you can choose any grid cell $ (x, y) $ , and in return, you will receive the minimum Manhattan distance from both the mines to the chosen cell, i.e., you will receive the value $ \min(|x-x_1|+|y-y_1|, |x-x_2|+|y-y_2|) $ .

Your task is to determine the location of one of the mines after making the queries.

## 说明/提示

In the first test case, we start by querying the upper-left corner $ (1, 1) $ and get the result $ 3 $ , which means that there is a mine on the counter diagonal, and there is no mine above it.

In the image below, each cell contains a number indicating the distance to the blue cell. The green cells are candidates to contain the nearest mine.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1934C/9f8890c987cfc62ebf33297af68261e59cb82050.png)Then we ask three cells on that diagonal, and at the last query, we get the result $ 0 $ , which means that a mine is found at the position $ (2, 3) $ .

The second mine was located at the position $ (3, 2) $ .

In the second test case, we start by asking the lower-right corner $ (5, 5) $ , and get the result $ 1 $ , which means that one of the two neighbours contains a mine, let's call it mine $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1934C/529c76a59b6e1128854ef8942281235840d099a4.png)Then we ask cell $ (2, 2) $ . We can see that these green cells don't intersect with the green cells from the first query, so they contain the other mine, let's call it mine $ 2 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1934C/759e71e2b3a5d456c063d438414900b4ab40b3f1.png)Query $ 3 $ is cell $ (3, 3) $ . These cells contain mine $ 1 $ , but we still don't know where exactly. Nevertheless, we can determine that the only possible cell for mine $ 2 $ is $ (1, 1) $ , because all other candidates are at a distance closer than $ 3 $ for this query.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1934C/9b91f7f88f4e4ce648a34002d2c4a2f09feeedee.png)

## 样例 #1

### 输入

```
2
4 4

3

2

2

0

5 5

1

2

3```

### 输出

```
? 1 1

? 1 4

? 4 1

? 2 3

! 2 3

? 5 5

? 2 2

? 3 3

! 1 1```

# AI分析结果



# Find a Mine

## 题目描述

这是一个交互题。

给定一个 $n$ 行 $m$ 列的网格，坐标 $(x, y)$ 表示网格中的单元格，其中 $x$（$1 \leq x \leq n$）是从顶部开始计数的行号，$y$（$1 \leq y \leq m$）是从左侧开始计数的列号。网格中恰好有两个地雷，分别位于不同的单元格 $(x_1, y_1)$ 和 $(x_2, y_2)$。你可以进行最多 $4$ 次询问，之后需要输出其中一个地雷的位置。

每次询问时，你可以选择一个网格单元格 $(x, y)$，交互器将返回该单元格到两个地雷的曼哈顿距离的最小值，即 $\min(|x-x_1|+|y-y_1|, |x-x_2|+|y-y_2|)$。

你的任务是确定其中一个地雷的位置。

---

## 题解分析与结论

### 关键思路总结
1. **几何对称性分析**：曼哈顿距离的几何意义为以查询点为中心的菱形区域，通过查询三个角落点（如 $(1,1)$、$(1,m)$、$(n,1)$）可构造多组直线方程，求解交点确定候选地雷位置。
2. **方程联立**：将每次查询结果转化为线性方程（例如 $x + y = d + 2$），联立两两方程解出候选坐标。
3. **合法性验证**：通过检查解是否为整数且在网格范围内，筛选出合法候选点。
4. **最终验证询问**：对候选点进行最后一次询问，若返回 $0$ 则为答案，否则取另一候选点。

---

### 高分题解推荐

#### 题解作者：hgckythgcfhk（★★★★☆）
**核心思路**：
1. 询问三个角落点 $(1,1)$、$(1,m)$、$(n,1)$，得到三个距离值 $a,b,c$。
2. 联立方程解出两组可能的解：
   - 第一组：由 $(1,1)$ 和 $(1,m)$ 的方程联立。
   - 第二组：由 $(1,1)$ 和 $(n,1)$ 的方程联立。
3. 检查解的合法性后，用最后一次询问确定最终答案。

**代码要点**：
```cpp
ll a = get(1,1), b = get(1,m), c = get(n,1);
// 解第一组方程
ll x1 = (a + b - m + 3) / 2, y1 = a + 2 - x1;
if (x1合法 && y1合法) {
    询问(x1,y1)是否为0，是则输出；
}
// 解第二组方程
ll y2 = (a + c - n + 3) / 2, x2 = a + 2 - y2;
输出(x2,y2);
```

---

#### 题解作者：Louis_lxy（★★★★☆）
**核心思路**：
1. 类似的三次询问，构造两组方程。
2. 直接通过最后一次询问验证候选点，避免复杂分类。

**代码亮点**：
```cpp
a = get(1,1), b = get(1,m), c = get(n,1);
// 解第一组方程并验证
y = (a + m + 1 - b) / 2, x = a + 2 - y;
if (坐标合法) 询问该点，若为0直接输出；
// 否则解第二组方程并输出
y = (a + c + 3 - n) / 2, x = a + 2 - y;
```

---

#### 题解作者：I_will_AKIOI（★★★★☆）
**核心思路**：
1. 首询问 $(1,1)$ 确定地雷所在的对角线。
2. 询问对角线端点，通过曼哈顿距离特性计算候选点。
3. 最后一次询问验证候选点。

**代码片段**：
```cpp
int d1 = query(1,1);
计算对角线端点 (x1,y1) 和 (x2,y2);
int d2 = query(x1,y1), d3 = query(x2,y2);
计算候选点并验证其中一个是否为0。
```

---

### 同类型题目推荐
1. **曼哈顿距离应用**：[P3395 路障](https://www.luogu.com.cn/problem/P3395)
2. **交互题与几何分析**：[CF1017D The Wu](https://www.luogu.com.cn/problem/CF1017D)
3. **多条件联立方程**：[P3958 奶酪](https://www.luogu.com.cn/problem/P3958)

---
处理用时：62.98秒