# 题目信息

# Weird Sum

## 题目描述

Egor has a table of size $ n \times m $ , with lines numbered from $ 1 $ to $ n $ and columns numbered from $ 1 $ to $ m $ . Each cell has a color that can be presented as an integer from $ 1 $ to $ 10^5 $ .

Let us denote the cell that lies in the intersection of the $ r $ -th row and the $ c $ -th column as $ (r, c) $ . We define the manhattan distance between two cells $ (r_1, c_1) $ and $ (r_2, c_2) $ as the length of a shortest path between them where each consecutive cells in the path must have a common side. The path can go through cells of any color. For example, in the table $ 3 \times 4 $ the manhattan distance between $ (1, 2) $ and $ (3, 3) $ is $ 3 $ , one of the shortest paths is the following: $ (1, 2) \to (2, 2) \to (2, 3) \to (3, 3) $ .

Egor decided to calculate the sum of manhattan distances between each pair of cells of the same color. Help him to calculate this sum.

## 说明/提示

In the first sample there are three pairs of cells of same color: in cells $ (1, 1) $ and $ (2, 3) $ , in cells $ (1, 2) $ and $ (2, 2) $ , in cells $ (1, 3) $ and $ (2, 1) $ . The manhattan distances between them are $ 3 $ , $ 1 $ and $ 3 $ , the sum is $ 7 $ .

## 样例 #1

### 输入

```
2 3
1 2 3
3 2 1```

### 输出

```
7```

## 样例 #2

### 输入

```
3 4
1 1 2 2
2 1 1 2
2 2 1 1```

### 输出

```
76```

## 样例 #3

### 输入

```
4 4
1 1 2 3
2 1 1 2
3 1 2 1
1 1 2 1```

### 输出

```
129```

# AI分析结果

### 题目内容重写

#### 题目描述

Egor 有一个大小为 $n \times m$ 的表格，行编号从 $1$ 到 $n$，列编号从 $1$ 到 $m$。每个单元格的颜色可以用一个整数表示，范围从 $1$ 到 $10^5$。

我们定义单元格 $(r, c)$ 为第 $r$ 行和第 $c$ 列的交点。两个单元格 $(r_1, c_1)$ 和 $(r_2, c_2)$ 之间的曼哈顿距离是它们之间的最短路径的长度，路径中的每个相邻单元格必须共享一条边。路径可以经过任何颜色的单元格。例如，在 $3 \times 4$ 的表格中，单元格 $(1, 2)$ 和 $(3, 3)$ 之间的曼哈顿距离是 $3$，其中一条最短路径是：$(1, 2) \to (2, 2) \to (2, 3) \to (3, 3)$。

Egor 决定计算所有相同颜色的单元格对之间的曼哈顿距离之和。请你帮助他计算这个和。

#### 说明/提示

在第一个样例中，有三对相同颜色的单元格：$(1, 1)$ 和 $(2, 3)$，$(1, 2)$ 和 $(2, 2)$，$(1, 3)$ 和 $(2, 1)$。它们之间的曼哈顿距离分别是 $3$、$1$ 和 $3$，总和为 $7$。

#### 样例 #1

##### 输入

```
2 3
1 2 3
3 2 1
```

##### 输出

```
7
```

#### 样例 #2

##### 输入

```
3 4
1 1 2 2
2 1 1 2
2 2 1 1
```

##### 输出

```
76
```

#### 样例 #3

##### 输入

```
4 4
1 1 2 3
2 1 1 2
3 1 2 1
1 1 2 1
```

##### 输出

```
129
```

### 算法分类
前缀和、排序

### 题解分析与结论

本题的核心是计算所有相同颜色的单元格对之间的曼哈顿距离之和。由于曼哈顿距离可以分解为行和列的绝对差之和，因此可以将问题转化为分别计算行和列的绝对差之和，再相加得到最终结果。

大多数题解都采用了类似的思路：首先按颜色分类，然后对每种颜色的行和列分别排序，最后利用前缀和或类似的优化方法来计算绝对差之和。这种方法的时间复杂度为 $O(nm \log nm)$，能够有效处理题目中的最大数据范围。

### 精选题解

#### 题解1：西湖水妖 (4星)

**关键亮点**：
- 使用 `vector` 存储每种颜色的行和列，避免了空间浪费。
- 通过排序和前缀和优化，将时间复杂度降低到 $O(nm \log nm)$。
- 代码清晰，逻辑严谨。

**核心代码**：
```cpp
for(int i = 1; i < 100001; ++ i)
{
    sort(a[i].begin(), a[i].end());
    sort(b[i].begin(), b[i].end());
    partial_sum(a[i].begin(), a[i].end(), sum.begin());
    for(int j = 1; j < a[i].size(); ++ j)
    {
        ans += a[i][j] * j;
        ans -= sum[j - 1];
    }
    partial_sum(b[i].begin(), b[i].end(), sum.begin());
    for(int j = 1; j < b[i].size(); ++ j)
    {
        ans += b[i][j] * j;
        ans -= sum[j - 1];
    }
}
```

#### 题解2：daniEl_lElE (4星)

**关键亮点**：
- 使用 `vector` 存储每种颜色的行和列，并通过排序和前缀和优化计算。
- 代码简洁，逻辑清晰，易于理解。

**核心代码**：
```cpp
for(int i = 1; i <= 100000; i++){
    sort(r[i].begin(), r[i].end());
    int tot = 0, cnt = 0;
    for(auto j : r[i]){
        ans += (j * cnt - tot);
        tot += j;
        cnt++;
    }
}
```

#### 题解3：_QWQ__QWQ_ (4星)

**关键亮点**：
- 使用 `vector` 存储每种颜色的行和列，并通过排序和前缀和优化计算。
- 代码简洁，逻辑清晰，易于理解。

**核心代码**：
```cpp
for(int i = 1; i <= 100001; i++){
    for(int j = 0; j < vx[i].size(); j++){
        ans += j * vx[i][j];
        ans -= (vx[i].size() - j - 1) * vx[i][j];
        ans += j * vy[i][j];
        ans -= (vy[i].size() - j - 1) * vy[i][j];
    }
}
```

### 最优关键思路与技巧

1. **按颜色分类**：将相同颜色的单元格的行和列分别存储，便于后续处理。
2. **排序与前缀和**：对每种颜色的行和列进行排序，利用前缀和优化绝对差之和的计算。
3. **分开计算行和列**：将曼哈顿距离分解为行和列的绝对差之和，分别计算后再相加。

### 可拓展之处

类似的问题可以通过将距离分解为多个独立的部分，分别计算后再合并结果。例如，欧几里得距离可以分解为平方和的形式，同样可以利用类似的优化方法。

### 推荐题目

1. [P6067 [USACO05JAN] Moo Volume S](https://www.luogu.com.cn/problem/P6067)
2. [P5094 [USACO05JAN] Moo Volume S](https://www.luogu.com.cn/problem/P5094)
3. [P1648 [USACO05JAN] Moo Volume S](https://www.luogu.com.cn/problem/P1648)

### 个人心得摘录

- **西湖水妖**：通过前缀和优化，避免了重复计算，大大提高了代码效率。
- **daniEl_lElE**：排序后利用前缀和计算绝对差之和，代码简洁且高效。
- **_QWQ__QWQ_**：将行和列的绝对差之和分开计算，逻辑清晰，易于理解。

---
处理用时：45.98秒