# 题目信息

# Triangles

## 题目描述

Gildong has a square board consisting of $ n $ rows and $ n $ columns of square cells, each consisting of a single digit (from $ 0 $ to $ 9 $ ). The cell at the $ j $ -th column of the $ i $ -th row can be represented as $ (i, j) $ , and the length of the side of each cell is $ 1 $ . Gildong likes big things, so for each digit $ d $ , he wants to find a triangle such that:

- Each vertex of the triangle is in the center of a cell.
- The digit of every vertex of the triangle is $ d $ .
- At least one side of the triangle is parallel to one of the sides of the board. You may assume that a side of length $ 0 $ is parallel to both sides of the board.
- The area of the triangle is maximized.

Of course, he can't just be happy with finding these triangles as is. Therefore, for each digit $ d $ , he's going to change the digit of exactly one cell of the board to $ d $ , then find such a triangle. He changes it back to its original digit after he is done with each digit. Find the maximum area of the triangle he can make for each digit.

Note that he can put multiple vertices of the triangle on the same cell, and the triangle can be a [degenerate triangle](https://cutt.ly/NhbjZ2l); i.e. the area of the triangle can be $ 0 $ . Also, note that he is allowed to change the digit of a cell from $ d $ to $ d $ .

## 说明/提示

In the first case, for $ d=0 $ , no matter which cell he chooses to use, the triangle with vertices at $ (1, 1) $ , $ (1, 3) $ , and $ (3, 1) $ is the biggest triangle with area of $ \cfrac{2 \cdot 2}{2} = 2 $ . Since we should print it multiplied by $ 2 $ , the answer for $ d=0 $ is $ 4 $ .

For $ d=1 $ , Gildong can change the digit of the cell at $ (1, 3) $ into $ 1 $ , making a triangle with vertices on all three $ 1 $ 's that has an area of $ 2 $ .

For $ d=2 $ , Gildong can change the digit of one of the following six cells into $ 2 $ to make a triangle with an area of $ \cfrac{1}{2} $ : $ (1, 1) $ , $ (1, 2) $ , $ (1, 3) $ , $ (3, 1) $ , $ (3, 2) $ , and $ (3, 3) $ .

For the remaining digits (from $ 3 $ to $ 9 $ ), the cell Gildong chooses to change will be the only cell that contains that digit. Therefore the triangle will always be a degenerate triangle with an area of $ 0 $ .

In the third case, for $ d=4 $ , note that the triangle will be bigger than the answer if Gildong changes the digit of the cell at $ (1, 4) $ and use it along with the cells at $ (2, 1) $ and $ (4, 3) $ , but this is invalid because it violates the condition that at least one side of the triangle must be parallel to one of the sides of the board.

## 样例 #1

### 输入

```
5
3
000
122
001
2
57
75
4
0123
4012
3401
2340
1
9
8
42987101
98289412
38949562
87599023
92834718
83917348
19823743
38947912```

### 输出

```
4 4 1 0 0 0 0 0 0 0
0 0 0 0 0 1 0 1 0 0
9 6 9 9 6 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
18 49 49 49 49 15 0 30 42 42```

# AI分析结果

### 题目翻译
# 三角形

## 题目描述
吉东有一个由 $n$ 行 $n$ 列的正方形单元格组成的正方形棋盘，每个单元格包含一个数字（从 $0$ 到 $9$）。第 $i$ 行第 $j$ 列的单元格可以表示为 $(i, j)$，每个单元格的边长为 $1$。吉东喜欢大的东西，所以对于每个数字 $d$，他想找到一个三角形，使得：
- 三角形的每个顶点都在单元格的中心。
- 三角形每个顶点的数字都是 $d$。
- 三角形至少有一条边与棋盘的某一条边平行。你可以假设长度为 $0$ 的边与棋盘的两条边都平行。
- 三角形的面积最大。

当然，他不会仅仅满足于找到这些三角形。因此，对于每个数字 $d$，他会将棋盘上恰好一个单元格的数字改为 $d$，然后找到这样一个三角形。在处理完每个数字后，他会将该单元格的数字改回原来的数字。请找出他能为每个数字构造出的三角形的最大面积。

请注意，他可以将三角形的多个顶点放在同一个单元格上，并且三角形可以是[退化三角形](https://cutt.ly/NhbjZ2l)，即三角形的面积可以为 $0$。此外，他也允许将单元格的数字从 $d$ 改为 $d$。

## 说明/提示
在第一个样例中，对于 $d = 0$，无论他选择使用哪个单元格，以 $(1, 1)$、$(1, 3)$ 和 $(3, 1)$ 为顶点的三角形是最大的三角形，面积为 $\frac{2 \cdot 2}{2} = 2$。由于我们应该输出面积乘以 $2$ 的结果，所以 $d = 0$ 的答案是 $4$。

对于 $d = 1$，吉东可以将单元格 $(1, 3)$ 的数字改为 $1$，从而构成一个由三个 $1$ 作为顶点的三角形，其面积为 $2$。

对于 $d = 2$，吉东可以将以下六个单元格中的任意一个的数字改为 $2$，从而构成一个面积为 $\frac{1}{2}$ 的三角形：$(1, 1)$、$(1, 2)$、$(1, 3)$、$(3, 1)$、$(3, 2)$ 和 $(3, 3)$。

对于其余数字（从 $3$ 到 $9$），吉东选择更改的单元格将是唯一包含该数字的单元格。因此，三角形将始终是面积为 $0$ 的退化三角形。

在第三个样例中，对于 $d = 4$，请注意，如果吉东更改单元格 $(1, 4)$ 的数字，并将其与单元格 $(2, 1)$ 和 $(4, 3)$ 一起使用，三角形的面积会更大，但这是无效的，因为它违反了三角形至少有一条边必须与棋盘的某一条边平行的条件。

## 样例 #1
### 输入
```
5
3
000
122
001
2
57
75
4
0123
4012
3401
2340
1
9
8
42987101
98289412
38949562
87599023
92834718
83917348
19823743
38947912
```

### 输出
```
4 4 1 0 0 0 0 0 0 0
0 0 0 0 0 1 0 1 0 0
9 6 9 9 6 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
18 49 49 49 49 15 0 30 42 42
```

### 算法分类
枚举

### 综合分析与结论
这三道题解的核心思路都是通过枚举的方式，针对每个数字 $d$ 去寻找满足条件的最大面积三角形。它们都考虑到了三角形至少有一条边与棋盘边平行的条件，并分情况讨论来计算最大面积。

- **思路对比**：
    - **WitheredZeal**：分别计算至少有一条边水平和至少有一条边竖直的两种情况，每种情况又细分两种子情况进行枚举。
    - **IntrepidStrayer**：将满足条件的三角形分为两点都是底边端点和有一点不是底边端点两种情况进行讨论。
    - **Little09**：分为两个点的连线与方格纸平行和不平行两种情况，分别对行和列进行预处理和枚举。
- **算法要点对比**：
    - **WitheredZeal**：使用数组记录每种颜色最上、下、左、右的位置，通过两层循环枚举行和列，计算不同情况下的最大面积。
    - **IntrepidStrayer**：使用数组 `top` 记录每行每列最左、右、上、下的颜色位置，`ccc` 记录所有方格中最左、右、上、下的颜色位置，通过枚举颜色和点来计算最大面积。
    - **Little09**：使用数组 `p`、`q` 记录每行每列最左、右的颜色位置，`P`、`Q` 记录整个图中最左、右的颜色位置，通过多次循环和条件判断计算最大面积。
- **解决难点对比**：
    - **WitheredZeal**：需要注意负数相乘可能导致错误，要对计算结果进行清零处理。
    - **IntrepidStrayer**：通过合理的数组记录和枚举方式，避免了判断是否组成三角形的问题。
    - **Little09**：代码实现较为复杂，需要多次循环和条件判断，容易出错。

### 题解评分
- **WitheredZeal**：4星。思路清晰，代码结构较为清晰，对不同情况的处理详细。
- **IntrepidStrayer**：4星。思路简洁明了，通过合理的数组记录和枚举方式，简化了部分判断过程。
- **Little09**：3星。思路正确，但代码实现过于复杂，可读性较差。

### 所选题解
- **WitheredZeal**（4星）
    - **关键亮点**：思路清晰，将水平和竖直情况分开处理，每种情况又细分两种子情况，逻辑明确。
- **IntrepidStrayer**（4星）
    - **关键亮点**：通过合理的数组记录和枚举方式，避免了判断是否组成三角形的问题，简化了代码。

### 重点代码
#### WitheredZeal 的核心代码
```cpp
// 至少有一条边是水平的情况
for (int i=0;i<=9;i++) U[i]=n+1,D[i]=0;
for (int i=1;i<=n;i++)
{
    for (int j=1;j<=n;j++)
    {
        U[a[i][j]]=min(U[a[i][j]],i);
        D[a[i][j]]=max(D[a[i][j]],i);
    }
}
for (int i=1;i<=n;i++)
{
    for (int j=0;j<=9;j++) L[j]=n+1,R[j]=0;
    for (int j=1;j<=n;j++) 
    {
        L[a[i][j]]=min(L[a[i][j]],j);
        R[a[i][j]]=max(R[a[i][j]],j);
    }
    for (int j=0;j<=9;j++)
    {
        ans[j]=max(ans[j],(R[j]-L[j])*max(i-1,n-i));
        int H=max(i-U[j],D[j]-i);
        int W=max(R[j]-1,n-L[j]);
        if (H<0) H=0;
        if (W<0) W=0;
        ans[j]=max(ans[j],W*H);
    }
}
// 至少有一条边是竖直的情况，代码类似
```
**核心实现思想**：先记录每种颜色最上、下的行位置，然后枚举每行，记录该行每种颜色最左、右的列位置，根据不同情况计算最大面积。

#### IntrepidStrayer 的核心代码
```cpp
// 预处理
rep(i, 1, n)
    for(rei j = 1, lst = 10; j <= n && lst; ++ j)
        if(!top[0][i][a[i][j]]) top[0][i][a[i][j]] = j, -- lst;
// ... 其他预处理代码 ...
// 计算最大面积
rep(d, 0, 9) {
    rep(i, 1, n)
        if(top[0][i][d] && top[1][i][d])
            chmax(mx[d], (top[1][i][d] - top[0][i][d]) * max(i - 1, n - i));
    // ... 其他计算代码 ...
}
rep(i, 1, n) rep(j, 1, n) {
    r = a[i][j];
    chmax(mx[r], (j - ccc[0][r]) * max(i - 1, n - i));
    // ... 其他计算代码 ...
}
```
**核心实现思想**：先预处理每行每列和整个方格中每种颜色的位置，然后通过枚举颜色和点，根据不同情况计算最大面积。

### 最优关键思路或技巧
- 使用数组记录每种颜色的边界位置，方便后续计算三角形的底和高。
- 分情况讨论，将满足条件的三角形分为不同类型，分别计算最大面积。

### 可拓展之处
同类型题目可能会改变棋盘的形状（如矩形、圆形等），或者改变三角形的限制条件（如至少两条边平行等）。类似算法套路可以是先对图形进行预处理，记录关键信息，然后通过枚举和分类讨论的方式计算满足条件的最大或最小值。

### 推荐洛谷题目
- P1003 [铺地毯](https://www.luogu.com.cn/problem/P1003)
- P1047 [校门外的树](https://www.luogu.com.cn/problem/P1047)
- P1420 [最长连号](https://www.luogu.com.cn/problem/P1420)

### 个人心得
WitheredZeal 提到“我先对另一篇题解的话表示反驳，我的方法才是最麻烦的（悲）”，总结为作者认为自己的方法比较麻烦。
Little09 提到“估计我的方法是最麻烦的…但是这题没有题解，那我来一发”，总结为作者觉得自己的方法麻烦，但还是分享出来。 

---
处理用时：73.67秒