# 题目信息

# Staircases

## 题目描述

You are given a matrix, consisting of $ n $ rows and $ m $ columns. The rows are numbered top to bottom, the columns are numbered left to right.

Each cell of the matrix can be either free or locked.

Let's call a path in the matrix a staircase if it:

- starts and ends in the free cell;
- visits only free cells;
- has one of the two following structures: 
  1. the second cell is $ 1 $ to the right from the first one, the third cell is $ 1 $ to the bottom from the second one, the fourth cell is $ 1 $ to the right from the third one, and so on;
  2. the second cell is $ 1 $ to the bottom from the first one, the third cell is $ 1 $ to the right from the second one, the fourth cell is $ 1 $ to the bottom from the third one, and so on.

In particular, a path, consisting of a single cell, is considered to be a staircase.

Here are some examples of staircases:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1598E/30e6b70a090f9657a06b957e8113944b3c2b16f3.png)Initially all the cells of the matrix are free.

You have to process $ q $ queries, each of them flips the state of a single cell. So, if a cell is currently free, it makes it locked, and if a cell is currently locked, it makes it free.

Print the number of different staircases after each query. Two staircases are considered different if there exists such a cell that appears in one path and doesn't appear in the other path.

## 样例 #1

### 输入

```
2 2 8
1 1
1 1
1 1
2 2
1 1
1 2
2 1
1 1```

### 输出

```
5
10
5
2
5
3
1
0```

## 样例 #2

### 输入

```
3 4 10
1 4
1 2
2 3
1 2
2 3
3 2
1 3
3 4
1 3
3 1```

### 输出

```
49
35
24
29
49
39
31
23
29
27```

## 样例 #3

### 输入

```
1000 1000 2
239 634
239 634```

### 输出

```
1332632508
1333333000```

# AI分析结果

### 题目内容翻译
## 楼梯

### 题目描述
给定一个由 $n$ 行 $m$ 列组成的矩阵。行从上到下编号，列从左到右编号。

矩阵中的每个单元格可以是空闲的或锁定的。

如果矩阵中的一条路径满足以下条件，则称其为楼梯：
- 起点和终点都在空闲单元格中；
- 仅访问空闲单元格；
- 具有以下两种结构之一：
  1. 第二个单元格在第一个单元格的右侧 $1$ 个位置，第三个单元格在第二个单元格的下方 $1$ 个位置，第四个单元格在第三个单元格的右侧 $1$ 个位置，依此类推；
  2. 第二个单元格在第一个单元格的下方 $1$ 个位置，第三个单元格在第二个单元格的右侧 $1$ 个位置，第四个单元格在第三个单元格的下方 $1$ 个位置，依此类推。

特别地，仅由一个单元格组成的路径也被视为楼梯。

以下是一些楼梯的示例：

![示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1598E/30e6b70a090f9657a06b957e8113944b3c2b16f3.png)

最初，矩阵的所有单元格都是空闲的。

你需要处理 $q$ 个查询，每个查询都会翻转单个单元格的状态。也就是说，如果一个单元格当前是空闲的，则将其锁定；如果一个单元格当前是锁定的，则将其解锁。

在每次查询后，打印不同楼梯的数量。如果存在一个单元格，它出现在一条路径中但不出现在另一条路径中，则认为这两条楼梯是不同的。

### 样例 #1
#### 输入
```
2 2 8
1 1
1 1
1 1
2 2
1 1
1 2
2 1
1 1
```
#### 输出
```
5
10
5
2
5
3
1
0
```

### 样例 #2
#### 输入
```
3 4 10
1 4
1 2
2 3
1 2
2 3
3 2
1 3
3 4
1 3
3 1
```
#### 输出
```
49
35
24
29
49
39
31
23
29
27
```

### 样例 #3
#### 输入
```
1000 1000 2
239 634
239 634
```
#### 输出
```
1332632508
1333333000
```

### 算法分类
动态规划

### 综合分析与结论
这些题解主要围绕动态规划来解决问题，核心在于定义合适的状态表示和状态转移方程。
- **思路对比**：多数题解定义了不同的状态数组，如 $f(i,j)$、$g(i,j)$ 或 $f_{i,j,0/1}$ 来表示以 $(i,j)$ 为起点的不同方向的楼梯数量。
- **算法要点**：先计算初始状态下的楼梯总数，对于每次修改，根据修改位置的状态变化，更新相关状态数组和总楼梯数。
- **解决难点**：关键在于处理修改操作时，如何高效地更新受影响的状态，避免不必要的计算。多数题解采用暴力更新受影响的 $O(n)$ 个格子的状态，时间复杂度为 $O(qn)$。

### 所选题解
- **作者：pythoner713（4星）**
  - **关键亮点**：思路清晰，状态定义简洁，通过定义 $f(i,j)$ 和 $g(i,j)$ 分别表示第一步向右和向下的台阶数量，明确给出状态转移方程，且对重复统计的单个格子进行了处理。
- **作者：KSToki（4星）**
  - **关键亮点**：详细分析了无询问时的动态规划思路，对于修改操作的处理逻辑清晰，通过标记格子状态，暴力更新受影响的格子状态，代码实现较为完整。
- **作者：Dtw_（4星）**
  - **关键亮点**：先给出暴力思路，再进行优化，通过深度优先搜索（DFS）来更新受影响的状态，代码注释详细，便于理解。

### 重点代码
#### 作者：pythoner713
```cpp
// 对于 free cells 有转移
f(i,j)=g(i,j+1)+1;
g(i,j)=f(i+1,j)+1;
// 对于 locked cells 则
f(i,j)=g(i,j)=0;
// 答案计算
ans = sum(f(i,j)+g(i,j)) - cnt;
```
**核心实现思想**：定义状态 $f(i,j)$ 和 $g(i,j)$ 分别表示第一步向右和向下的台阶数量，根据格子状态进行状态转移，最后计算总台阶数并减去重复统计的单个格子数。

#### 作者：KSToki
```cpp
// 无询问时的状态转移
For(i,1,n)
    For(j,1,m)
    {
        f[i][j][0]=f[i-1][j][1]+1;
        f[i][j][1]=f[i][j-1][0]+1;
        ans+=f[i][j][0]+f[i][j][1];
    }
// 修改操作
while(q--)
{
    x=read();
    y=read();
    if(!v[x][y])
    {
        --cnt;
        ans-=f[x][y][0]+f[x][y][1];
        f[x][y][0]=f[x][y][1]=0;
        // 更新受影响的格子
        ...
    }
    else
    {
        ++cnt;
        f[x][y][0]=f[x-1][y][1]+1;
        f[x][y][1]=f[x][y-1][0]+1;
        ans+=f[x][y][0]+f[x][y][1];
        // 更新受影响的格子
        ...
    }
    v[x][y]^=1;
    putll(ans-cnt);
}
```
**核心实现思想**：先计算无询问时的状态，对于每次修改，根据格子状态的变化，更新状态数组和总台阶数，并暴力更新受影响的格子状态。

#### 作者：Dtw_
```cpp
// 深度优先搜索更新状态
void dfs(int x, int y, int c, int k)
{
    if (x < 1 || x > n || y < 1 || y > m) return;
    if (!a[x][y]) return;
    res -= f[x][y][k];
    f[x][y][k] -= c;
    res += f[x][y][k];
    if (k) dfs(x + 1, y, c, 0);
    else dfs(x, y + 1, c, 1);
}
// 修改操作
while (q--)
{
    int x, y;
    cin >> x >> y;
    if (a[x][y])
    {
        cnt--;
        res -= f[x][y][0] + f[x][y][1];
        dfs(x, y + 1, f[x][y][0], 1);
        dfs(x + 1, y, f[x][y][1], 0);
        f[x][y][0] = f[x][y][1] = 0;
    }
    else
    {
        cnt++;
        f[x][y][0] = f[x - 1][y][1] + 1; 
        f[x][y][1] = f[x][y - 1][0] + 1;
        res += f[x][y][0] + f[x][y][1];
        dfs(x, y + 1, -f[x][y][0], 1);
        dfs(x + 1, y, -f[x][y][1], 0);
    }
    a[x][y] ^= 1;
    cout << res - cnt << endl;
}
```
**核心实现思想**：通过深度优先搜索（DFS）来更新受影响的状态，对于每次修改，根据格子状态的变化，更新状态数组和总台阶数。

### 最优关键思路或技巧
- **状态定义**：通过合理定义状态数组，如 $f_{i,j,0/1}$ 或 $f(i,j)$、$g(i,j)$，来表示不同方向的楼梯数量，便于状态转移。
- **重复处理**：注意单个格子的重复统计问题，通过减去空闲格子的数量来避免重复计算。
- **局部更新**：修改操作只会影响到左上方 $O(n)$ 级别个格子的状态，因此可以暴力更新这些格子的状态，降低时间复杂度。

### 可拓展之处
同类型题或类似算法套路：
- 其他网格图上的路径计数问题，如不同形状的路径（如折线、蛇形等）的计数。
- 带有条件限制的路径问题，如路径上的权值和满足一定条件等。

### 推荐题目
- [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)
- [P1048 采药](https://www.luogu.com.cn/problem/P1048)
- [P1176 路径计数2](https://www.luogu.com.cn/problem/P1176)

### 个人心得
- **作者：I_am_Accepted**：本人 VP 中写挂了 QwQ。总结：在实现过程中可能会因为细节处理不当而导致代码出错，需要仔细检查。

---
处理用时：89.78秒