# 题目信息

# Colorful Table

## 题目描述

You are given two integers $ n $ and $ k $ . You are also given an array of integers $ a_1, a_2, \ldots, a_n $ of size $ n $ . It is known that for all $ 1 \leq i \leq n $ , $ 1 \leq a_i \leq k $ .

Define a two-dimensional array $ b $ of size $ n \times n $ as follows: $ b_{i, j} = \min(a_i, a_j) $ . Represent array $ b $ as a square, where the upper left cell is $ b_{1, 1} $ , rows are numbered from top to bottom from $ 1 $ to $ n $ , and columns are numbered from left to right from $ 1 $ to $ n $ . Let the color of a cell be the number written in it (for a cell with coordinates $ (i, j) $ , this is $ b_{i, j} $ ).

For each color from $ 1 $ to $ k $ , find the smallest rectangle in the array $ b $ containing all cells of this color. Output the sum of width and height of this rectangle.

## 说明/提示

In the first test case, the entire array $ b $ consists of color $ 1 $ , so the smallest rectangle for color $ 1 $ has a size of $ 2 \times 2 $ , and the sum of its sides is $ 4 $ .

In the second test case, the array $ b $ looks like this:

1112One of the corner cells has color $ 2 $ , and the other three cells have color $ 1 $ . Therefore, the smallest rectangle for color $ 1 $ has a size of $ 2 \times 2 $ , and for color $ 2 $ it is $ 1 \times 1 $ .

In the last test case, the array $ b $ looks like this:

1111112221123211222111111

## 样例 #1

### 输入

```
5
2 1
1 1
2 2
1 2
3 5
3 2 4
4 2
1 2 1 2
5 3
1 2 3 2 1```

### 输出

```
4 
4 2 
0 6 6 2 0 
8 6 
10 6 2```

# AI分析结果

### 题目内容重写

#### 题目描述

给定两个整数 $n$ 和 $k$，以及一个大小为 $n$ 的整数数组 $a_1, a_2, \ldots, a_n$。已知对于所有 $1 \leq i \leq n$，$1 \leq a_i \leq k$。

定义一个大小为 $n \times n$ 的二维数组 $b$，其中 $b_{i, j} = \min(a_i, a_j)$。将数组 $b$ 表示为一个正方形，左上角的单元格为 $b_{1, 1}$，行从上到下编号为 $1$ 到 $n$，列从左到右编号为 $1$ 到 $n$。单元格的颜色为其中写入的数字（即坐标为 $(i, j)$ 的单元格的颜色为 $b_{i, j}$）。

对于每种颜色从 $1$ 到 $k$，找出数组 $b$ 中包含该颜色所有单元格的最小矩形，并输出该矩形的宽度和高度之和。

#### 说明/提示

在第一个测试用例中，整个数组 $b$ 由颜色 $1$ 组成，因此颜色 $1$ 的最小矩形大小为 $2 \times 2$，其边长之和为 $4$。

在第二个测试用例中，数组 $b$ 如下所示：

```
1 1 1 2
```

其中一个角落的单元格为颜色 $2$，其他三个单元格为颜色 $1$。因此，颜色 $1$ 的最小矩形大小为 $2 \times 2$，颜色 $2$ 的最小矩形大小为 $1 \times 1$。

在最后一个测试用例中，数组 $b$ 如下所示：

```
1 1 1 1 1
1 1 2 2 1
1 2 3 2 1
1 2 2 1 1
1 1 1 1 1
```

#### 样例输入

```
5
2 1
1 1
2 2
1 2
3 5
3 2 4
4 2
1 2 1 2
5 3
1 2 3 2 1
```

#### 样例输出

```
4 
4 2 
0 6 6 2 0 
8 6 
10 6 2
```

### 算法分类

**模拟**

### 题解分析与结论

本题的核心在于如何高效地找到每种颜色在矩阵中的最小覆盖矩形。由于矩阵是对称的，且每个单元格的值由两个数组元素的最小值决定，因此可以通过模拟的方式找到每种颜色的最小覆盖矩形。

### 精选题解

#### 题解1：SunnyYuan (4星)

**关键亮点**：
- 通过维护 `first` 和 `last` 数组，记录每个颜色第一次和最后一次出现的位置。
- 使用 `max_last` 和 `min_first` 数组，快速找到每种颜色的最小覆盖矩形。
- 代码清晰，逻辑严谨，时间复杂度为 $O(n + k)$。

**代码实现**：
```cpp
void solve() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        if (!first[a[i]]) first[a[i]] = i;
        last[a[i]] = i;
    }
    for (int i = 0; i <= k + 1; i++) min_first[i] = INF, max_last[i] = -INF;
    for (int i = k; i >= 1; i--) {
        if (last[i]) max_last[i] = max(max_last[i + 1], last[i]);
        else max_last[i] = max_last[i + 1];
    }
    for (int i = k; i >= 1; i--) {
        if (first[i]) min_first[i] = min(min_first[i + 1], first[i]);
        else min_first[i] = min_first[i + 1];
    }
    for (int i = 1; i <= k; i++) {
        if (!first[i]) {
            cout << "0 ";
            continue;
        }
        int p1 = min_first[i], p2 = max_last[i];
        cout << 2 * (p2 - p1 + 1) << ' ';
    }
    cout << '\n';
    for (int i = 0; i <= k; i++) first[i] = last[i] = max_last[i] = min_first[i] = 0;
}
```

#### 题解2：xwh_hh (4星)

**关键亮点**：
- 通过维护 `l` 和 `r` 数组，记录每个颜色在数组中的最左和最右位置。
- 使用简单的遍历和更新操作，快速找到每种颜色的最小覆盖矩形。
- 代码简洁，时间复杂度为 $O(n + k)$。

**代码实现**：
```cpp
void solve() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        if (a[i] > nowmax) {
            for (int j = nowmax + 1; j <= a[i]; j++) l[j] = i;
            nowmax = a[i];
        }
    }
    nowmax = 0;
    for (int i = n; i >= 1; i--) {
        if (a[i] > nowmax) {
            for (int j = nowmax + 1; j <= a[i]; j++) r[j] = i;
            nowmax = a[i];
        }
    }
    for (int i = 1; i <= k; i++) cout << 2 * (r[i] - l[i] + 1) << ' ';
    cout << '\n';
}
```

#### 题解3：Cynops (4星)

**关键亮点**：
- 通过维护 `L_i` 和 `R_i`，记录每种颜色的最左和最右位置。
- 使用简单的遍历和更新操作，快速找到每种颜色的最小覆盖矩形。
- 代码简洁，时间复杂度为 $O(n + k)$。

**代码实现**：
```cpp
void solve() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        if (a[i] > nowmax) {
            for (int j = nowmax + 1; j <= a[i]; j++) L[j] = i;
            nowmax = a[i];
        }
    }
    nowmax = 0;
    for (int i = n; i >= 1; i--) {
        if (a[i] > nowmax) {
            for (int j = nowmax + 1; j <= a[i]; j++) R[j] = i;
            nowmax = a[i];
        }
    }
    for (int i = 1; i <= k; i++) cout << 2 * (R[i] - L[i] + 1) << ' ';
    cout << '\n';
}
```

### 最优关键思路

通过维护每个颜色在数组中的最左和最右位置，可以快速找到每种颜色在矩阵中的最小覆盖矩形。由于矩阵是对称的，只需计算一维的长度，然后乘以2即可得到矩形的宽度和高度之和。

### 拓展思路

类似的问题可以通过维护区间信息来解决，例如使用线段树或树状数组来快速查询区间内的最大值或最小值。

### 推荐题目

1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P3372 线段树 1](https://www.luogu.com.cn/problem/P3372)
3. [P3368 树状数组 2](https://www.luogu.com.cn/problem/P3368)

---
处理用时：44.98秒