# 题目信息

# Polygon

## 题目描述

Polygon is not only the best platform for developing problems but also a square matrix with side $ n $ , initially filled with the character 0.

On the polygon, military training was held. The soldiers placed a cannon above each cell in the first row and a cannon to the left of each cell in the first column. Thus, exactly $ 2n $ cannons were placed.

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1360E/af538d3417e3bff02f7ca9d4302ffeb8985b4df9.png)Initial polygon for $ n=4 $ . Cannons shoot character 1. At any moment of time, no more than one cannon is shooting. When a 1 flies out of a cannon, it flies forward (in the direction of the shot) until it collides with a polygon border or another 1. After that, it takes the cell in which it was before the collision and remains there. Take a look at the examples for better understanding.

More formally:

- if a cannon stands in the row $ i $ , to the left of the first column, and shoots with a 1, then the 1 starts its flight from the cell ( $ i, 1 $ ) and ends in some cell ( $ i, j $ );
- if a cannon stands in the column $ j $ , above the first row, and shoots with a 1, then the 1 starts its flight from the cell ( $ 1, j $ ) and ends in some cell ( $ i,         j $ ).

For example, consider the following sequence of shots:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1360E/b0a2a2240d9a0a11c84c2c0dd9be686db3e431b3.png) 1. Shoot the cannon in the row $ 2 $ . 2. Shoot the cannon in the row $ 2 $ . 3. Shoot the cannon in column $ 3 $ .

You have a report from the military training on your desk. This report is a square matrix with side length $ n $ consisting of 0 and 1. You wonder if the training actually happened. In other words, is there a sequence of shots such that, after the training, you get the given matrix?

Each cannon can make an arbitrary number of shots. Before the training, each cell of the polygon contains 0.

## 说明/提示

The first test case was explained in the statement.

The answer to the second test case is NO, since a 1 in a cell ( $ 1, 1 $ ) flying out of any cannon would continue its flight further.

## 样例 #1

### 输入

```
5
4
0010
0011
0000
0000
2
10
01
2
00
00
4
0101
1111
0101
0111
4
0100
1110
0101
0111```

### 输出

```
YES
NO
YES
YES
NO```

# AI分析结果

### 题目内容重写（中文）

Polygon 不仅是最好的问题开发平台，也是一个边长为 $n$ 的正方形矩阵，初始时每个单元格都填充字符 0。

在 Polygon 上进行了军事训练。士兵们在第一行的每个单元格上方放置了一门大炮，并在第一列的每个单元格左侧放置了一门大炮。因此，总共放置了 $2n$ 门大炮。

初始的 Polygon 矩阵（$n=4$）如下图所示。大炮发射字符 1。在任何时刻，最多只有一门大炮在发射。当 1 从大炮中飞出时，它会向前飞行（沿着发射方向），直到碰到 Polygon 的边界或另一个 1。之后，它会停留在碰撞前的单元格中并保持不变。请查看示例以更好地理解。

更正式地说：

- 如果一门大炮位于第 $i$ 行，第一列的左侧，并发射 1，那么 1 从单元格 ($i$, $1$) 开始飞行，并在某个单元格 ($i$, $j$) 结束；
- 如果一门大炮位于第 $j$ 列，第一行的上方，并发射 1，那么 1 从单元格 ($1$, $j$) 开始飞行，并在某个单元格 ($i$, $j$) 结束。

例如，考虑以下发射序列：

1. 发射第 2 行的大炮。
2. 再次发射第 2 行的大炮。
3. 发射第 3 列的大炮。

你桌上有军事训练的报告。这份报告是一个边长为 $n$ 的正方形矩阵，由 0 和 1 组成。你想知道训练是否真的发生了。换句话说，是否存在一个发射序列，使得训练后得到给定的矩阵？

每门大炮可以进行任意次数的发射。在训练之前，Polygon 的每个单元格都包含 0。

### 题解分析与结论

#### 综合分析

所有题解的核心思路都是通过检查矩阵中的每个 1 是否满足“其右侧或下侧至少有一个 1 或边界”的条件来判断矩阵是否合法。具体来说，如果某个 1 的右侧和下侧都是 0，那么这个 1 无法通过大炮发射得到，因此矩阵不合法。

#### 最优思路总结

1. **边界处理**：最右列和最下行的 1 总是合法的，因为它们可以碰到边界。
2. **合法性检查**：对于非边界位置的 1，必须确保其右侧或下侧至少有一个 1，否则矩阵不合法。
3. **遍历矩阵**：通过遍历矩阵中的每个 1，检查其右侧和下侧是否满足上述条件。

#### 推荐题解

1. **作者：Zhoumy**  
   - **星级**：4.5  
   - **关键亮点**：代码简洁，逻辑清晰，直接通过遍历矩阵判断合法性，没有多余的复杂操作。
   - **核心代码**：
     ```cpp
     for(int j=1;j<n;j++)for(int k=1;k<n;k++)if(a[j][k]=='1'&&a[j][k+1]=='0'&&a[j+1][k]=='0')die=1;
     ```

2. **作者：Warriors_Cat**  
   - **星级**：4  
   - **关键亮点**：通过预处理边界为 1，简化了边界条件的判断，代码逻辑清晰。
   - **核心代码**：
     ```cpp
     for(int i=1;i<=n;i++)a[n+1][i]=1,a[i][n+1]=1;
     for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(a[i][j]==1&&!a[i+1][j]&&!a[i][j+1])flag=0;
     ```

3. **作者：lu_fish**  
   - **星级**：4  
   - **关键亮点**：通过直接判断每个 1 的右侧和下侧是否为 0，逻辑简单明了，代码易于理解。
   - **核心代码**：
     ```cpp
     for(int i=1;i<n&&pd;i++)for(int j=1;j<n&&pd;j++)if(f[i][j]=='1'&&f[i+1][j]=='0'&&f[i][j+1]=='0')pd=0;
     ```

### 关键实现技巧

- **边界预处理**：将矩阵的最右列和最下行预先设置为 1，简化边界条件的判断。
- **提前退出**：在发现不合法情况时，立即退出循环，减少不必要的计算。

### 拓展思路

类似的问题可以通过检查特定条件来判断矩阵或图形的合法性。例如，判断一个矩阵是否可以通过某种操作生成，或者判断一个图形是否符合某种规则。

### 推荐题目

1. [P1042 矩阵取数游戏](https://www.luogu.com.cn/problem/P1042)
2. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)
3. [P1010 幂次方](https://www.luogu.com.cn/problem/P1010)

---
处理用时：40.22秒