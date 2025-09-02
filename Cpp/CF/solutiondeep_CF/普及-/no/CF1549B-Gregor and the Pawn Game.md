# 题目信息

# Gregor and the Pawn Game

## 题目描述

There is a chessboard of size $ n $ by $ n $ . The square in the $ i $ -th row from top and $ j $ -th column from the left is labelled $ (i,j) $ .

Currently, Gregor has some pawns in the $ n $ -th row. There are also enemy pawns in the $ 1 $ -st row. On one turn, Gregor moves one of his pawns. A pawn can move one square up (from $ (i,j) $ to $ (i-1,j) $ ) if there is no pawn in the destination square. Additionally, a pawn can move one square diagonally up (from $ (i,j) $ to either $ (i-1,j-1) $ or $ (i-1,j+1) $ ) if and only if there is an enemy pawn in that square. The enemy pawn is also removed.

Gregor wants to know what is the maximum number of his pawns that can reach row $ 1 $ ?

Note that only Gregor takes turns in this game, and the enemy pawns never move. Also, when Gregor's pawn reaches row $ 1 $ , it is stuck and cannot make any further moves.

## 说明/提示

In the first example, Gregor can simply advance all $ 3 $ of his pawns forward. Thus, the answer is $ 3 $ .

In the second example, Gregor can guarantee that all $ 4 $ of his pawns reach the enemy row, by following the colored paths as demonstrated in the diagram below. Remember, only Gregor takes turns in this "game"!

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1549B/eb2df5f00e8c7d1290d3251e314fd1200ad28d29.png)In the third example, Gregor's only pawn is stuck behind the enemy pawn, and cannot reach the end.

In the fourth example, Gregor has no pawns, so the answer is clearly $ 0 $ .

## 样例 #1

### 输入

```
4
3
000
111
4
1111
1111
3
010
010
5
11001
00000```

### 输出

```
3
4
0
0```

# AI分析结果

### 题目内容
# Gregor和兵棋游戏

## 题目描述
有一个大小为 $n$ 乘 $n$ 的棋盘。从顶部数第 $i$ 行、从左侧数第 $j$ 列的方格标记为 $(i, j)$ 。

目前，Gregor在第 $n$ 行有一些兵。在第 $1$ 行也有敌方的兵。在一回合中，Gregor移动他的一个兵。如果目标方格中没有兵，一个兵可以向上移动一格（从 $(i, j)$ 移动到 $(i - 1, j)$ ）。此外，当且仅当斜上方方格中有敌方的兵时，一个兵可以斜向上移动一格（从 $(i, j)$ 移动到 $(i - 1, j - 1)$ 或 $(i - 1, j + 1)$ ），同时敌方的兵也会被移除。

Gregor想知道他最多有多少个兵可以到达第 $1$ 行？

注意，在这个游戏中只有Gregor轮流行动，敌方的兵从不移动。另外，当Gregor的兵到达第 $1$ 行时，它就会被困住，不能再进行任何移动。

## 说明/提示
在第一个例子中，Gregor可以简单地将他的 $3$ 个兵全部向前推进。因此，答案是 $3$ 。

在第二个例子中，Gregor可以保证他的 $4$ 个兵全部到达敌方所在行，如下面图表中彩色路径所示。记住，在这个 “游戏” 中只有Gregor轮流行动！

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1549B/eb2df5f00e8c7d1290d3251e314fd1200ad28d29.png)
在第三个例子中，Gregor唯一的兵被困在敌方兵后面，无法到达终点。

在第四个例子中，Gregor没有兵，所以答案显然是 $0$ 。

## 样例 #1
### 输入
```
4
3
000
111
4
1111
1111
3
010
010
5
11001
00000
```
### 输出
```
3
4
0
0
```

### 算法分类
贪心

### 题解综合分析与结论
这些题解的核心思路均为贪心算法。要点在于从左到右枚举棋子，对每个棋子按特定优先级选择移动方向：优先考虑向前移动到顶，若不行则看左边有敌方棋子就向左，最后右边有敌方棋子则向右移动。难点在于证明贪心的正确性，多数题解从当前行空地利用、棋子移动对后续棋子影响等角度进行说明，如当前行空地只有当前行棋子能利用所以直接向前移动；从左往右枚举使得左边棋子移动决策不会影响右边棋子；向右移动虽可能影响右边棋子向左移动，但综合考虑不会比不移动差等。

### 通用建议与扩展思路
对于此类贪心问题，关键在于找到合理的贪心策略，并严谨证明其正确性。可拓展到其他类似棋盘移动类的贪心题目，例如改变棋盘布局、棋子移动规则等。在解决这类问题时，要深入分析每个决策对后续状态的影响，以此确定贪心的方向和优先级。

### 相似知识点洛谷题目
1. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)：通过合理分组来实现贪心策略。
2. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)：从高位到低位贪心选择删除数字。
3. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：根据接水时间贪心排序。 

---
处理用时：32.62秒