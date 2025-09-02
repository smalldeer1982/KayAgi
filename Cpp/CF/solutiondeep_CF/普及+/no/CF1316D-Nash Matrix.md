# 题目信息

# Nash Matrix

## 题目描述

Nash designed an interesting yet simple board game where a player is simply required to follow instructions written on the cell where the player currently stands.

This board game is played on the $ n\times n $ board. Rows and columns of this board are numbered from $ 1 $ to $ n $ . The cell on the intersection of the $ r $ -th row and $ c $ -th column is denoted by $ (r, c) $ .

Some cells on the board are called blocked zones. On each cell of the board, there is written one of the following $ 5 $ characters — $ U $ , $ D $ , $ L $ , $ R $ or $ X $ — instructions for the player. Suppose that the current cell is $ (r, c) $ . If the character is $ R $ , the player should move to the right cell $ (r, c+1) $ , for $ L $ the player should move to the left cell $ (r, c-1) $ , for $ U $ the player should move to the top cell $ (r-1, c) $ , for $ D $ the player should move to the bottom cell $ (r+1, c) $ . Finally, if the character in the cell is $ X $ , then this cell is the blocked zone. The player should remain in this cell (the game for him isn't very interesting from now on).

It is guaranteed that the characters are written in a way that the player will never have to step outside of the board, no matter at which cell he starts.

As a player starts from a cell, he moves according to the character in the current cell. The player keeps moving until he lands in a blocked zone. It is also possible that the player will keep moving infinitely long.

For every of the $ n^2 $ cells of the board Alice, your friend, wants to know, how will the game go, if the player starts in this cell. For each starting cell of the board, she writes down the cell that the player stops at, or that the player never stops at all. She gives you the information she has written: for each cell $ (r, c) $ she wrote:

- a pair ( $ x $ , $ y $ ), meaning if a player had started at $ (r, c) $ , he would end up at cell ( $ x $ , $ y $ ).
- or a pair ( $ -1 $ , $ -1 $ ), meaning if a player had started at $ (r, c) $ , he would keep moving infinitely long and would never enter the blocked zone.

It might be possible that Alice is trying to fool you and there's no possible grid that satisfies all the constraints Alice gave you. For the given information Alice provided you, you are required to decipher a possible board, or to determine that such a board doesn't exist. If there exist several different boards that satisfy the provided information, you can find any of them.

## 说明/提示

For the sample test 1 :

The given grid in output is a valid one.

- If the player starts at $ (1,1) $ , he doesn't move any further following $ X $ and stops there.
- If the player starts at $ (1,2) $ , he moves to left following $ L $ and stops at $ (1,1) $ .
- If the player starts at $ (2,1) $ , he moves to right following $ R $ and stops at $ (2,2) $ .
- If the player starts at $ (2,2) $ , he doesn't move any further following $ X $ and stops there.

The simulation can be seen below :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1316D/cb2fbba5dfce3a1de517dfe2ea9b356af74a9df6.png)For the sample test 2 :

The given grid in output is a valid one, as a player starting at any cell other than the one at center $ (2,2) $ , keeps moving in an infinitely long cycle and never stops. Had he started at $ (2,2) $ , he wouldn't have moved further following instruction $ X $ .

The simulation can be seen below :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1316D/1eb3dd4d726b75341ce98cd63cef3956c6e3a050.png)

## 样例 #1

### 输入

```
2
1 1 1 1
2 2 2 2```

### 输出

```
VALID
XL
RX```

## 样例 #2

### 输入

```
3
-1 -1 -1 -1 -1 -1
-1 -1 2 2 -1 -1
-1 -1 -1 -1 -1 -1```

### 输出

```
VALID
RRD
UXD
ULL```

# AI分析结果

### 题目中文重写
# Nash矩阵

## 题目描述
Nash设计了一个有趣且简单的棋盘游戏，在这个游戏中，玩家只需遵循当前所在格子上的指令即可。

这个棋盘游戏在一个 $n×n$ 的棋盘上进行。棋盘的行和列编号从 $1$ 到 $n$。第 $r$ 行和第 $c$ 列交叉处的格子记为 $(r, c)$。

棋盘上的一些格子被称为禁区。在棋盘的每个格子上，都写有以下 $5$ 个字符之一 —— $U$、$D$、$L$、$R$ 或 $X$ —— 这些是给玩家的指令。假设当前格子是 $(r, c)$。如果字符是 $R$，玩家应向右移动到格子 $(r, c + 1)$；如果是 $L$，玩家应向左移动到格子 $(r, c - 1)$；如果是 $U$，玩家应向上移动到格子 $(r - 1, c)$；如果是 $D$，玩家应向下移动到格子 $(r + 1, c)$。最后，如果格子中的字符是 $X$，那么这个格子就是禁区，玩家应停留在这个格子（从这时起，他的游戏就没那么有趣了）。

保证所写的字符能让玩家无论从哪个格子开始，都不会走出棋盘。

当玩家从一个格子开始时，他会根据当前格子中的字符移动。玩家会一直移动，直到进入禁区。玩家也有可能会一直无限移动下去。

对于棋盘上的 $n^2$ 个格子，你的朋友Alice想知道，如果玩家从这个格子开始，游戏会如何进行。对于棋盘上的每个起始格子，她写下了玩家最终停留的格子，或者玩家永远不会停止的信息。她给了你她写下的信息：对于每个格子 $(r, c)$，她写下了：
- 一对坐标 $(x, y)$，表示如果玩家从 $(r, c)$ 开始，最终会停在格子 $(x, y)$。
- 或者一对坐标 $(-1, -1)$，表示如果玩家从 $(r, c)$ 开始，他会一直无限移动，永远不会进入禁区。

有可能Alice在试图欺骗你，不存在满足Alice所给所有约束条件的棋盘。对于Alice提供给你的信息，你需要破译出一个可能的棋盘，或者确定这样的棋盘不存在。如果存在多个满足所提供信息的不同棋盘，你可以找到其中任何一个。

## 说明/提示
对于示例测试1：
输出中给出的网格是有效的。
- 如果玩家从 $(1, 1)$ 开始，他遵循 $X$ 指令，不会再移动，停在那里。
- 如果玩家从 $(1, 2)$ 开始，他遵循 $L$ 指令向左移动，停在 $(1, 1)$。
- 如果玩家从 $(2, 1)$ 开始，他遵循 $R$ 指令向右移动，停在 $(2, 2)$。
- 如果玩家从 $(2, 2)$ 开始，他遵循 $X$ 指令，不会再移动，停在那里。

模拟过程如下：
 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1316D/cb2fbba5dfce3a1de517dfe2ea9b356af74a9df6.png)
对于示例测试2：
输出中给出的网格是有效的，因为除了中心格子 $(2, 2)$ 外，从任何格子开始的玩家都会在一个无限循环中一直移动，永远不会停止。如果他从 $(2, 2)$ 开始，他会遵循指令 $X$，不再移动。

模拟过程如下：
 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1316D/1eb3dd4d726b75341ce98cd63cef3956c6e3a050.png)

## 样例 #1
### 输入
```
2
1 1 1 1
2 2 2 2
```
### 输出
```
VALID
XL
RX
```

## 样例 #2
### 输入
```
3
-1 -1 -1 -1 -1 -1
-1 -1 2 2 -1 -1
-1 -1 -1 -1 -1 -1
```
### 输出
```
VALID
RRD
UXD
ULL
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是将点分为会停止和不会停止两类分别处理。对于会停止的点，找到自停止点（终点是自身的点）标记为 `X`，然后通过深度优先搜索（DFS）找到所有终点相同的点并标记对应字符；对于不会停止的点，若单个点则结果为 `INVALID`，否则找相邻的点构成环，再让其他点连到环上。

不同题解在实现细节上略有差异，如处理死循环联通块时找相邻点的方式、DFS 函数的参数设置等，但整体思路一致。

### 所选题解
- little_sun（4星）
  - 关键亮点：思路清晰，对性质的证明很详细，代码注释丰富，逻辑严谨。
- syksykCCC（4星）
  - 关键亮点：代码简洁，将处理会停止和不会停止的点的 DFS 函数统一，减少代码冗余。
- Andrewzdm（4星）
  - 关键亮点：将问题分类讨论，条理清晰，代码实现简单易懂。

### 重点代码
#### little_sun 的 DFS 函数
```cpp
void dfs(int x, int y, int Dx) // 正常联通块求解
{
    if (ans[x][y]) return;
    ans[x][y] = op[Dx];
    for (int i = 0; i <= 3; i++)
    {
        int ex = x + dx[i], ey = y + dy[i];
        if (check(ex, ey) && a[ex][ey] == a[x][y])
            dfs(ex, ey, i);
    }
}
```
核心实现思想：从自停止点开始，通过 DFS 遍历所有终点相同的点，根据当前点到下一个点的方向标记字符。

#### syksykCCC 的 DFS 函数
```cpp
void DFS(int p, int q, int sx, int sy)
{
    REP(i, 0, 3)
    {
        int tx = p + dx[i], ty = q + dy[i];
        if(tx >= 1 && tx <= n && ty >= 1 && ty <= n &&
          ex[tx][ty] == sx && ey[tx][ty] == sy && !ans[tx][ty])
        {
            ans[tx][ty] = dc[i];
            DFS(tx, ty, sx, sy);
        }
    }
}
```
核心实现思想：根据当前点和终点的信息，通过 DFS 遍历所有终点相同的点，标记反方向的字符。

#### Andrewzdm 的 DFS 函数
```cpp
void dfs(int p, int q, char c)
{
    if(matrix[p][q] != '\0')
        return;
    matrix[p][q] = c;
    if(x[p - 1][q] == x[p][q] && y[p - 1][q] == y[p][q])//up
        dfs(p - 1, q, 'D');
    if(x[p + 1][q] == x[p][q] && y[p + 1][q] == y[p][q])//down
        dfs(p + 1, q, 'U');
    if(x[p][q - 1] == x[p][q] && y[p][q - 1] == y[p][q])//left
        dfs(p, q - 1, 'R');
    if(x[p][q + 1] == x[p][q] && y[p][q + 1] == y[p][q])//right
        dfs(p, q + 1, 'L');
}
```
核心实现思想：从自停止点开始，通过 DFS 遍历所有终点相同的点，根据当前点到下一个点的方向标记字符。

### 最优关键思路或技巧
- 利用深度优先搜索（DFS）来遍历所有终点相同的点，标记对应字符，简化了路径的构造过程。
- 将点分为会停止和不会停止两类分别处理，降低了问题的复杂度。

### 拓展思路
同类型题或类似算法套路：
- 其他构造类题目，如根据给定条件构造矩阵、图等。
- 涉及图的遍历和连通性的题目，可使用 DFS 或 BFS 进行求解。

### 推荐题目
- [P1119 灾后重建](https://www.luogu.com.cn/problem/P1119)：涉及图的连通性和最短路径问题。
- [P1330 封锁阳光大学](https://www.luogu.com.cn/problem/P1330)：图的染色问题，可使用 DFS 求解。
- [P1605 迷宫](https://www.luogu.com.cn/problem/P1605)：经典的迷宫搜索问题，可使用 DFS 或 BFS 求解。

### 个人心得
流绪提到存图比较难，试了几种方法，最后用二维结构体成功了。这提示我们在处理复杂数据关系时，选择合适的数据结构很重要，要多尝试不同的方法。 

---
处理用时：60.48秒