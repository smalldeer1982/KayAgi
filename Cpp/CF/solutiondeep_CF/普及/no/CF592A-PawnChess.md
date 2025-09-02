# 题目信息

# PawnChess

## 题目描述

Galois is one of the strongest chess players of Byteforces. He has even invented a new variant of chess, which he named «PawnChess».

This new game is played on a board consisting of 8 rows and 8 columns. At the beginning of every game some black and white pawns are placed on the board. The number of black pawns placed is not necessarily equal to the number of white pawns placed.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF592A/9900e176569f519565c0c8328f093726ce1eb9d2.png)Lets enumerate rows and columns with integers from 1 to 8. Rows are numbered from top to bottom, while columns are numbered from left to right. Now we denote as $ (r,c) $ the cell located at the row $ r $ and at the column $ c $ .

There are always two players A and B playing the game. Player A plays with white pawns, while player B plays with black ones. The goal of player A is to put any of his pawns to the row $ 1 $ , while player B tries to put any of his pawns to the row $ 8 $ . As soon as any of the players completes his goal the game finishes immediately and the succeeded player is declared a winner.

Player A moves first and then they alternate turns. On his move player A must choose exactly one white pawn and move it one step upward and player B (at his turn) must choose exactly one black pawn and move it one step down. Any move is possible only if the targeted cell is empty. It's guaranteed that for any scenario of the game there will always be at least one move available for any of the players.

Moving upward means that the pawn located in $ (r,c) $ will go to the cell $ (r-1,c) $ , while moving down means the pawn located in $ (r,c) $ will go to the cell $ (r+1,c) $ . Again, the corresponding cell must be empty, i.e. not occupied by any other pawn of any color.

Given the initial disposition of the board, determine who wins the game if both players play optimally. Note that there will always be a winner due to the restriction that for any game scenario both players will have some moves available.

## 说明/提示

In the first sample player A is able to complete his goal in 3 steps by always moving a pawn initially located at $ (4,5) $ . Player B needs at least 5 steps for any of his pawns to reach the row $ 8 $ . Hence, player A will be the winner.

## 样例 #1

### 输入

```
........
........
.B....B.
....W...
........
..W.....
........
........
```

### 输出

```
A
```

## 样例 #2

### 输入

```
..B.....
..W.....
......B.
........
.....W..
......B.
........
........
```

### 输出

```
B
```

# AI分析结果



### 题目内容重写

**题目名称**：PawnChess

**题目描述**：  
Galois 是 Byteforces 最强的国际象棋选手之一，他发明了一种名为「PawnChess」的新变种。游戏在一个 8x8 的棋盘上进行，初始放置若干黑兵和白兵。玩家 A 执白兵，目标是让任意白兵到达第 1 行；玩家 B 执黑兵，目标是让任意黑兵到达第 8 行。A 先移动，双方交替操作。每一步必须选择一个己方棋子向目标方向移动一格（白兵向上，黑兵向下），且目标位置必须为空。游戏在任意玩家达成目标时立即结束，判定该玩家获胜。给定初始棋盘，求双方均采取最优策略时的胜者。

---

### 分类标签  
**模拟**

---

### 题解分析与结论  
题目核心是模拟双方棋子的移动，计算白兵和黑兵到达目标行的最小步数，并考虑棋子间的阻挡关系。关键点在于：  
1. **阻挡判断**：同一列中，若白兵下方有黑兵，则无法到达目标行；反之，若黑兵上方有白兵，也无法到达目标行。  
2. **步数计算**：白兵在行 `i` 需要 `i-1` 步到达第 1 行；黑兵在行 `i` 需要 `8-i` 步到达第 8 行。  

现有题解普遍存在**步数计算错误**（例如将黑兵步数错误计算为 `9-i` 而非 `8-i`），但思路正确。正确的解法需确保步数计算准确，并通过遍历列找到未被阻挡的最优棋子。

---

### 正确代码实现思路  
1. **遍历每列**，分别计算白兵和黑兵的最小可行步数。  
2. **白兵处理**：从下往上找第一个白兵，检查下方是否有黑兵阻挡，若无则记录步数。  
3. **黑兵处理**：从上往下找第一个黑兵，检查上方是否有白兵阻挡，若无则记录步数。  
4. **比较双方最小步数**，若白方步数 ≤ 黑方步数，A 胜；否则 B 胜。  

```cpp
#include <iostream>
using namespace std;

int main() {
    char board[9][9]; // 棋盘，行从 1 到 8
    int min_white = 1e9, min_black = 1e9;

    // 输入棋盘
    for (int i = 1; i <= 8; ++i)
        for (int j = 1; j <= 8; ++j)
            cin >> board[i][j];

    // 处理每列
    for (int j = 1; j <= 8; ++j) {
        // 找白兵的最小步数（最下方的未被黑兵阻挡的白兵）
        for (int i = 8; i >= 1; --i) {
            if (board[i][j] == 'W') {
                bool blocked = false;
                for (int k = i + 1; k <= 8; ++k) {
                    if (board[k][j] == 'B') {
                        blocked = true;
                        break;
                    }
                }
                if (!blocked) {
                    min_white = min(min_white, i - 1);
                    break; // 取最下方的可行白兵
                }
            }
        }

        // 找黑兵的最小步数（最上方的未被白兵阻挡的黑兵）
        for (int i = 1; i <= 8; ++i) {
            if (board[i][j] == 'B') {
                bool blocked = false;
                for (int k = i - 1; k >= 1; --k) {
                    if (board[k][j] == 'W') {
                        blocked = true;
                        break;
                    }
                }
                if (!blocked) {
                    min_black = min(min_black, 8 - i);
                    break; // 取最上方的可行黑兵
                }
            }
        }
    }

    cout << (min_white <= min_black ? "A" : "B");
    return 0;
}
```

---

### 拓展与举一反三  
1. **同类问题**：类似棋盘模拟问题需注意行列遍历顺序和阻挡判断，如 [P1514 棋盘覆盖](https://www.luogu.com.cn/problem/P1514)。  
2. **优化思维**：预处理阻挡关系可减少重复计算，如标记每列的黑白阻挡区间。  
3. **推荐题目**：  
   - [P1217 棋盘问题](https://www.luogu.com.cn/problem/P1217)  
   - [P1433 棋盘覆盖](https://www.luogu.com.cn/problem/P1433)  
   - [P1548 棋盘游戏](https://www.luogu.com.cn/problem/P1548)  

---

### 个人心得  
- **步数计算陷阱**：行号与步数的转换需严格验证，避免因偏移导致错误。  
- **遍历方向关键**：白兵应从下往上找最下方的可行棋子，黑兵应从上往下找最上方的可行棋子。  
- **测试用例覆盖**：需覆盖极端情况（如棋子已在目标行、完全阻挡等）以验证代码正确性。

---
处理用时：336.56秒