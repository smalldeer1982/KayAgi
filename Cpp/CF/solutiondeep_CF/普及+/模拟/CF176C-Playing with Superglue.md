# 题目信息

# Playing with Superglue

## 题目描述

Two players play a game. The game is played on a rectangular board with $ n×m $ squares. At the beginning of the game two different squares of the board have two chips. The first player's goal is to shift the chips to the same square. The second player aims to stop the first one with a tube of superglue.

We'll describe the rules of the game in more detail.

The players move in turns. The first player begins.

With every move the first player chooses one of his unglued chips, and shifts it one square to the left, to the right, up or down. It is not allowed to move a chip beyond the board edge. At the beginning of a turn some squares of the board may be covered with a glue. The first player can move the chip to such square, in this case the chip gets tightly glued and cannot move any longer.

At each move the second player selects one of the free squares (which do not contain a chip or a glue) and covers it with superglue. The glue dries long and squares covered with it remain sticky up to the end of the game.

If, after some move of the first player both chips are in the same square, then the first player wins. If the first player cannot make a move (both of his chips are glued), then the second player wins. Note that the situation where the second player cannot make a move is impossible — he can always spread the glue on the square from which the first player has just moved the chip.

We will further clarify the case where both chips are glued and are in the same square. In this case the first player wins as the game ends as soon as both chips are in the same square, and the condition of the loss (the inability to move) does not arise.

You know the board sizes and the positions of the two chips on it. At the beginning of the game all board squares are glue-free. Find out who wins if the players play optimally.

## 样例 #1

### 输入

```
1 6 1 2 1 6
```

### 输出

```
First```

## 样例 #2

### 输入

```
6 5 4 3 2 1
```

### 输出

```
First```

## 样例 #3

### 输入

```
10 10 1 1 10 10
```

### 输出

```
Second```

# AI分析结果



# 题目重写

## 题目描述

两名玩家在一个 $n×m$ 的矩形棋盘上进行游戏。初始时，两个不同的方格上各有一枚棋子。第一个玩家的目标是通过移动使两枚棋子到达同一方格，第二个玩家则使用超级胶水阻止对方。

### 游戏规则
- 玩家轮流行动，先手玩家先动。
- 先手每回合选择一枚未固定的棋子，向上下左右移动一格，不能出界。若移动到有胶水的格子，该棋子被永久固定。
- 后手每回合在空余格子（无棋子、无胶水）放置胶水，胶水永久生效。
- 若先手移动后两棋同格则胜利。若先手无法移动（两棋均被固定）则后手胜利。

已知棋盘尺寸及初始棋子位置，双方最优策略下求胜者。

# 题解综合分析

## 关键思路总结
所有题解均基于**坐标差分析**，核心结论为：
- 当两棋子的横向差 $d_x$ 和纵向差 $d_y$ 满足以下条件之一时，后手必胜：
  1. $\max(d_x, d_y) > 4$
  2. $\max(d_x, d_y) = 4$ 且 $\min(d_x, d_y) = 3$
- 其余情况先手必胜

该结论通过大量棋盘模拟得出，本质是先手能否在有限步内达成目标而不被胶水封锁。

## 精选题解

### 题解作者：hongshixiaobai（⭐️⭐️⭐️⭐️）
**关键亮点**  
- 条件判断简洁清晰，直接处理坐标差排序后的最大/最小值。
- 代码规范性强，使用数组存储坐标避免变量名冲突。

**核心代码**
```cpp
int d[2] = {abs(x0 - x1), abs(y0 - y1)};
if(d[0] < d[1]) swap(d[0], d[1]);
if((d[0] == 4 && d[1] == 3) || d[0] > 4) cout << "second";
else cout << "first";
```

### 题解作者：frankchenfu（⭐️⭐️⭐️⭐️）
**关键亮点**  
- 独立实现绝对值函数，增加代码可移植性。
- 条件判断逻辑与主流解法一致，注释说明临界情况。

**核心代码**
```cpp
int dis1 = abs(x1 - x2), dis2 = abs(y1 - y2);
if(dis1 > dis2) swap(dis1, dis2);
if(dis1 >= 3 && dis2 >= 4 || dis1 > 4 || dis2 > 4)
    puts("Second");
else puts("First");
```

## 实现技巧
1. **坐标差排序**：将较大的差值统一处理，简化条件判断。
2. **临界条件特判**：单独处理 (4,3) 的特殊情况。
3. **变量命名优化**：使用数组存储坐标避免保留字冲突。

## 拓展建议
此类博弈问题的核心是**寻找关键状态的分界线**。类似题目可关注：
1. 棋盘游戏中的必胜态分析（如尼姆博弈变种）
2. 基于曼哈顿/切比雪夫距离的状态判断
3. 有限步数内的最优策略模拟

## 相似题目推荐
1. [P2734 [USACO3.3] 游戏 A Game](https://www.luogu.com.cn/problem/P2734) - 区间博弈模型
2. [P1259 黑白棋游戏](https://www.luogu.com.cn/problem/P1259) - 状态转移与必胜策略
3. [CF8C Looking for Order](https://www.luogu.com.cn/problem/CF8C) - 坐标系统下的最优路径规划

---
处理用时：53.83秒