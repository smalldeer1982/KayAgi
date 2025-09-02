# 题目信息

# Fillomino 2

## 题目描述

Fillomino is a classic logic puzzle. (You do not need to know Fillomino in order to solve this problem.) In one classroom in Yunqi town, some volunteers are playing a board game variant of it:

Consider an $ n $ by $ n $ chessboard. Its rows are numbered from $ 1 $ to $ n $ from the top to the bottom. Its columns are numbered from $ 1 $ to $ n $ from the left to the right. A cell on an intersection of $ x $ -th row and $ y $ -th column is denoted $ (x, y) $ . The main diagonal of the chessboard is cells $ (x, x) $ for all $ 1 \le x \le n $ .

A permutation of $ \{1, 2, 3, \dots, n\} $ is written on the main diagonal of the chessboard. There is exactly one number written on each of the cells. The problem is to partition the cells under and on the main diagonal (there are exactly $ 1+2+ \ldots +n $ such cells) into $ n $ connected regions satisfying the following constraints:

1. Every region should be connected. That means that we can move from any cell of a region to any other cell of the same region visiting only cells of the same region and moving from a cell to an adjacent cell.
2. The $ x $ -th region should contain cell on the main diagonal with number $ x $ for all $ 1\le x\le n $ .
3. The number of cells that belong to the $ x $ -th region should be equal to $ x $ for all $ 1\le x\le n $ .
4. Each cell under and on the main diagonal should belong to exactly one region.

## 说明/提示

The solutions to the examples are illustrated in the following pictures: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1517C/9c1f0c1849ccf4ce0e7b23176bd91c953e348595.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1517C/9e88a2fdc4b038adc182da7d0d66d5d0dcc6a27e.png)

## 样例 #1

### 输入

```
3
2 3 1```

### 输出

```
2
2 3
3 3 1```

## 样例 #2

### 输入

```
5
1 2 3 4 5```

### 输出

```
1
2 2
3 3 3
4 4 4 4
5 5 5 5 5```

# AI分析结果

### 题目内容重写

#### Fillomino 2

**题目描述**

Fillomino 是一种经典的逻辑谜题。（你不需要了解 Fillomino 来解决这个问题。）在云栖镇的一个教室里，一些志愿者正在玩一个棋盘游戏的变体：

考虑一个 $n \times n$ 的棋盘。行从上到下编号为 $1$ 到 $n$，列从左到右编号为 $1$ 到 $n$。位于第 $x$ 行和第 $y$ 列交叉处的单元格记为 $(x, y)$。棋盘的主对角线是单元格 $(x, x)$，其中 $1 \le x \le n$。

在棋盘的主对角线上写有一个 $\{1, 2, 3, \dots, n\}$ 的排列。每个单元格上恰好写有一个数字。问题是将主对角线及其下方的单元格（共有 $1+2+ \ldots +n$ 个单元格）划分为 $n$ 个连通区域，满足以下约束：

1. 每个区域必须是连通的。这意味着我们可以从区域的任意一个单元格移动到同一区域的任意其他单元格，且只访问同一区域的单元格，并且只能从一个单元格移动到相邻的单元格。
2. 第 $x$ 个区域必须包含主对角线上数字为 $x$ 的单元格，其中 $1 \le x \le n$。
3. 第 $x$ 个区域包含的单元格数量必须等于 $x$，其中 $1 \le x \le n$。
4. 主对角线及其下方的每个单元格必须恰好属于一个区域。

**说明/提示**

样例的解决方案如下图所示：![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1517C/9c1f0c1849ccf4ce0e7b23176bd91c953e348595.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1517C/9e88a2fdc4b038adc182da7d0d66d5d0dcc6a27e.png)

**样例 #1**

**输入**

```
3
2 3 1
```

**输出**

```
2
2 3
3 3 1
```

**样例 #2**

**输入**

```
5
1 2 3 4 5
```

**输出**

```
1
2 2
3 3 3
4 4 4 4
5 5 5 5 5
```

### 算法分类
构造

### 题解分析与结论

题目要求将棋盘主对角线及其下方的单元格划分为 $n$ 个连通区域，每个区域的大小等于其对应的数字，并且每个区域必须包含主对角线上对应的数字。大多数题解都采用了贪心的构造方法，即从主对角线上的每个数字开始，尽可能向左或向下扩展，直到填满所需的单元格数量。

### 所选题解

#### 题解1：Gokix (5星)
**关键亮点**：
- 详细证明了构造方法的正确性，确保每个区域都能被正确填充。
- 代码简洁明了，逻辑清晰，易于理解。

**核心代码**：
```cpp
for(i=1;i<=n;i++){
    u=i;v=i;
    for(j=1;j<a[i][i];j++){
        if(a[u][v-1]==0 && v-1>=1){
            a[u][v-1]=a[i][i];
            v--;
        }
        else if(a[u+1][v]==0 && u+1<=n){
            a[u+1][v]=a[i][i];
            u++;
        }
        else{
            cout<<-1<<endl;
            return 0;
        }
    }
}
```
**核心思想**：从每个主对角线上的数字开始，尽可能向左或向下扩展，直到填满所需的单元格数量。

#### 题解2：Ratio_Y (4星)
**关键亮点**：
- 倒序考虑，优先在边缘区域放数，避免出现“隔断”情况。
- 代码实现简洁，复杂度为 $\mathcal{O(n^2)}$。

**核心代码**：
```cpp
for(int i=n;i>=1;i--){
    dh[i][i]=a[i];
    int sum=1,x=i,y=i;
    while(sum<a[i]){
        if(x<n&&!dh[x+1][y]) dh[x+1][y]=a[i],x=x+1,sum++;
        else dh[x][y-1]=a[i],y=y-1,sum++;
    }
}
```
**核心思想**：从第 $n$ 行开始，优先向下扩展，避免影响上方的填充。

#### 题解3：Booksnow (4星)
**关键亮点**：
- 从左往右遍历 $p$ 数组，逐个构造连通块，确保每个区域都能被正确填充。
- 代码逻辑清晰，易于理解。

**核心代码**：
```cpp
for(register int i=1;i<=n;i++){
    ans[i][i]=p[i];
    int nx=i,ny=i;
    for(register int j=2;j<=p[i];j++){
        if(ny-1>0&&!ans[nx][ny-1]) ny--;
        else nx++;
        ans[nx][ny]=p[i]; 
    }
}
```
**核心思想**：从左往右遍历 $p$ 数组，逐个构造连通块，优先向左扩展，无法向左时向下扩展。

### 最优关键思路或技巧
- **贪心构造**：从主对角线上的每个数字开始，尽可能向左或向下扩展，直到填满所需的单元格数量。
- **倒序处理**：从第 $n$ 行开始，优先向下扩展，避免影响上方的填充。

### 可拓展之处
- 类似的问题可以扩展到其他形状的棋盘或不同的填充规则，如填充矩形区域或更复杂的连通区域。
- 可以尝试使用其他构造方法，如深度优先搜索（DFS）或广度优先搜索（BFS）来填充区域。

### 推荐题目
1. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)
2. [P1074 靶形数独](https://www.luogu.com.cn/problem/P1074)
3. [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040)

### 个人心得摘录
- **Gokix**：通过证明构造方法的正确性，确保每个区域都能被正确填充，避免了不必要的错误。
- **Ratio_Y**：倒序处理可以有效避免“隔断”情况，确保每个区域都能被正确填充。
- **Booksnow**：从左往右遍历 $p$ 数组，逐个构造连通块，逻辑清晰，易于理解。

---
处理用时：39.99秒