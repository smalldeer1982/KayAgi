# 题目信息

# Maximal Binary Matrix

## 题目描述

You are given matrix with $ n $ rows and $ n $ columns filled with zeroes. You should put $ k $ ones in it in such a way that the resulting matrix is symmetrical with respect to the main diagonal (the diagonal that goes from the top left to the bottom right corner) and is lexicographically maximal.

One matrix is lexicographically greater than the other if the first different number in the first different row from the top in the first matrix is greater than the corresponding number in the second one.

If there exists no such matrix then output -1.

## 样例 #1

### 输入

```
2 1
```

### 输出

```
1 0 
0 0 
```

## 样例 #2

### 输入

```
3 2
```

### 输出

```
1 0 0 
0 1 0 
0 0 0 
```

## 样例 #3

### 输入

```
2 5
```

### 输出

```
-1
```

# AI分析结果

### 题目重写
给定一个 $n$ 行 $n$ 列的矩阵，初始时所有元素均为 0。你需要在该矩阵中放置 $k$ 个 1，使得最终的矩阵关于主对角线（从左上角到右下角的对角线）对称，并且字典序最大。

一个矩阵的字典序大于另一个矩阵，当且仅当在从上到下、从左到右的顺序中，第一个不同的元素在第一个矩阵中大于第二个矩阵中的对应元素。

如果不存在这样的矩阵，则输出 -1。

### 样例 #1
#### 输入
```
2 1
```
#### 输出
```
1 0 
0 0 
```

### 样例 #2
#### 输入
```
3 2
```
#### 输出
```
1 0 0 
0 1 0 
0 0 0 
```

### 样例 #3
#### 输入
```
2 5
```
#### 输出
```
-1
```

### 题解分析与结论
本题的核心在于如何构造一个对称且字典序最大的矩阵。各题解的主要思路是通过贪心算法，优先在前几行放置 1，并确保对称性。以下是各题解的关键点对比：

1. **贪心算法**：大多数题解采用贪心策略，优先在前几行放置 1，确保字典序最大。
2. **对称性处理**：对于非对角线元素，放置 1 时需要同时放置其对称位置的 1，以确保矩阵对称。
3. **特殊情况处理**：当 $k$ 为奇数时，只能在对角线上放置 1；当 $k$ 大于 $n^2$ 时，直接输出 -1。

### 精选题解
#### 题解1：frankchenfu (赞：3)
**星级：4.5**
**关键亮点**：
- 使用递归函数 `solve` 来填充矩阵，优先在前几行放置 1，确保字典序最大。
- 通过递归调用处理剩余 1 的放置，确保对称性。
- 代码简洁且高效，边界条件处理得当。

**核心代码**：
```cpp
void solve(int n, int pos, int k) {
    if (k == 1) {
        a[pos][pos] = 1;
        return;
    }
    if (k == 0) return;
    if (k <= (n << 1) - 1) {
        for (int i = pos; i <= pos + (k - 1 >> 1); i++)
            a[pos][i] = a[i][pos] = 1;
        solve(n - 1, pos + 1, (k & 1) ^ 1);
    } else {
        for (int i = pos; i <= pos + n - 1; i++)
            a[pos][i] = a[i][pos] = 1;
        solve(n - 1, pos + 1, k - (n << 1) + 1);
    }
}
```

#### 题解2：wflhx2011 (赞：2)
**星级：4**
**关键亮点**：
- 从 $(1,1)$ 开始依次遍历矩阵，优先在前几行放置 1，确保字典序最大。
- 对于非对角线元素，同时放置其对称位置的 1，确保对称性。
- 代码简洁，边界条件处理得当。

**核心代码**：
```cpp
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
        if (a[i][j] == 0) {
            if (i == j) a[i][j] = 1, k--;
            else if (k == 1) a[i][i] = 1, k--;
            else a[i][j] = a[j][i] = 1, k -= 2;
        }
        if (k == 0) break;
    }
    if (k == 0) break;
}
```

#### 题解3：syf2008 (赞：2)
**星级：4**
**关键亮点**：
- 从第一行开始依次遍历矩阵，优先在前几行放置 1，确保字典序最大。
- 对于非对角线元素，同时放置其对称位置的 1，确保对称性。
- 代码简洁，边界条件处理得当。

**核心代码**：
```cpp
for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
        if (k == 0) goto ss;
        if (a[i][j]) continue;
        if (i == j) a[i][j] = 1, k--;
        else if (k >= 2) a[i][j] = a[j][i] = 1, k -= 2;
    }
}
```

### 最优关键思路
1. **贪心策略**：优先在前几行放置 1，确保字典序最大。
2. **对称性处理**：对于非对角线元素，同时放置其对称位置的 1，确保矩阵对称。
3. **边界条件处理**：当 $k$ 为奇数时，只能在对角线上放置 1；当 $k$ 大于 $n^2$ 时，直接输出 -1。

### 拓展思路
- **类似题目**：可以考虑类似的矩阵填充问题，如要求矩阵满足其他对称性条件或字典序最小。
- **优化思路**：可以通过数学方法进一步优化填充策略，减少递归深度或循环次数。

### 推荐题目
1. [P1008 三连击](https://www.luogu.com.cn/problem/P1008)
2. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)
3. [P1019 单词接龙](https://www.luogu.com.cn/problem/P1019)

### 个人心得总结
- **调试经历**：在处理边界条件时，容易忽略 $k$ 为奇数的情况，导致无法构造对称矩阵。
- **踩坑教训**：在贪心策略中，优先在前几行放置 1 时，需要确保对称性，否则会导致矩阵不对称。
- **顿悟感想**：通过递归和贪心策略的结合，可以高效地解决矩阵填充问题，同时确保字典序最大和对称性。

---
处理用时：49.46秒