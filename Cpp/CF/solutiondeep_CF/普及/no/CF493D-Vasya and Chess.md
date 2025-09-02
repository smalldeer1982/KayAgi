# 题目信息

# Vasya and Chess

## 题目描述

Vasya decided to learn to play chess. Classic chess doesn't seem interesting to him, so he plays his own sort of chess.

The queen is the piece that captures all squares on its vertical, horizontal and diagonal lines. If the cell is located on the same vertical, horizontal or diagonal line with queen, and the cell contains a piece of the enemy color, the queen is able to move to this square. After that the enemy's piece is removed from the board. The queen cannot move to a cell containing an enemy piece if there is some other piece between it and the queen.

There is an $ n×n $ chessboard. We'll denote a cell on the intersection of the $ r $ -th row and $ c $ -th column as $ (r,c) $ . The square $ (1,1) $ contains the white queen and the square $ (1,n) $ contains the black queen. All other squares contain green pawns that don't belong to anyone.

The players move in turns. The player that moves first plays for the white queen, his opponent plays for the black queen.

On each move the player has to capture some piece with his queen (that is, move to a square that contains either a green pawn or the enemy queen). The player loses if either he cannot capture any piece during his move or the opponent took his queen during the previous move.

Help Vasya determine who wins if both players play with an optimal strategy on the board $ n×n $ .

## 说明/提示

In the first sample test the white queen can capture the black queen at the first move, so the white player wins.

In the second test from the statement if the white queen captures the green pawn located on the central vertical line, then it will be captured by the black queen during the next move. So the only move for the white player is to capture the green pawn located at $ (2,1) $ .

Similarly, the black queen doesn't have any other options but to capture the green pawn located at $ (2,3) $ , otherwise if it goes to the middle vertical line, it will be captured by the white queen.

During the next move the same thing happens — neither the white, nor the black queen has other options rather than to capture green pawns situated above them. Thus, the white queen ends up on square $ (3,1) $ , and the black queen ends up on square $ (3,3) $ .

In this situation the white queen has to capture any of the green pawns located on the middle vertical line, after that it will be captured by the black queen. Thus, the player who plays for the black queen wins.

## 样例 #1

### 输入

```
2
```

### 输出

```
white
1 2
```

## 样例 #2

### 输入

```
3
```

### 输出

```
black
```

# AI分析结果



【中文重写题目】

# Vasya 与棋局

## 题目描述

Vasya 决定学习国际象棋。传统象棋对他而言似乎不够有趣，于是他发明了自己的象棋规则。

皇后可以攻击其所在行、列及对角线上所有未被阻挡的敌方棋子。若一个敌方棋子位于皇后所在行、列或对角线，且路径上没有其他棋子阻挡，皇后可以移动至该位置并吃掉该棋子。

现有一个 $n×n$ 的棋盘，坐标 $(r,c)$ 表示第 $r$ 行第 $c$ 列。白方皇后初始位于 $(1,1)$，黑方皇后初始位于 $(1,n)$，其余格子均为中立棋子。

双方轮流移动，白方先手。每次移动必须吃掉一个棋子（可以是敌方皇后或中立棋子）。无法进行合法移动或己方皇后已被吃掉的玩家判负。

请确定在双方采用最优策略时，哪方会获胜。

## 说明/提示

- 第一个样例中白皇后可直接吃掉黑皇后获胜
- 第二个样例详细展示了双方交替移动中立棋子直至白方被迫进入危险位置的过程

---

**算法分类**：数学/组合数学

---

### 题解综合分析

所有题解均基于棋盘规模 $n$ 的奇偶性建立必胜策略：
- **偶数棋盘**：白方首步占据优势位置后，通过镜像策略迫使黑方陷入被动
- **奇数棋盘**：黑方采用镜像策略最终围剿白方

---

### 优质题解推荐

1. **codeLJH114514（5星）**
   - **关键亮点**：清晰图解镜像策略的博弈过程，完整数学证明
   - **代码实现**：直接判断奇偶性输出结果，处理了多解情况的要求
   ```cpp
   cout << (n & 1 ? "black" : "white\n1 2");
   ```

2. **Fearliciz（4星）**
   - **核心洞见**：将问题转化为对称博弈模型，强调模仿策略的重要性
   - **调试经验**：指出该类型题目需优先考虑对称策略的思维方向

3. **I_have_been_here（4星）**
   - **空间划分法**：将棋盘划分为对称区域，分析中间分界线的战略意义
   - **代码简洁性**：使用简单条件判断实现核心逻辑

---

### 关键思路提炼

**对称博弈策略**：
1. **偶数维度**：先手通过首步移动建立主动对称，后续镜像对手操作直至获胜
2. **奇数维度**：后手利用中心对称性反制先手，最终形成围剿
3. **决胜关键**：中间列/行的控制权决定胜负归属

---

### 拓展应用

类似对称博弈问题常见于：
1. 棋盘覆盖问题（洛谷P1219）
2. 取石子游戏（Nim博弈变形）
3. 双人轮流操作的矩阵游戏

---

### 推荐习题

1. [P1259 黑白棋游戏](https://www.luogu.com.cn/problem/P1259) - 对称移动策略
2. [P2580 取石子游戏](https://www.luogu.com.cn/problem/P2580) - 奇偶性博弈
3. [P4136 棋盘覆盖](https://www.luogu.com.cn/problem/P4136) - 分治与对称性

---

### 心得摘录

- **codeLJH114514**："当白走到中间列时，黑方必定处于镜像位置从而形成绝杀" → 强调关键决胜点的判断
- **Fearliciz**："遇到必胜策略题优先考虑模仿" → 提供通用解题思路
- **skywang**："调试记录：这题肯定一次AC的啦" → 体现对问题本质的深刻理解

---
处理用时：62.33秒