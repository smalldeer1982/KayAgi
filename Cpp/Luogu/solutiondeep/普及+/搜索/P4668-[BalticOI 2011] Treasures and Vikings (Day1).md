# 题目信息

# [BalticOI 2011] Treasures and Vikings (Day1)

## 题目描述

You have a treasure map that is arranged into a $N \times M$ grid. A grid square may be either sea or part of an island. In addition, the map shows the treasure and an enemy Viking ship that occupies one (sea) square. Finally, for convenience you have also drawn your own position.

Now you must set up a fixed route to get the treasure. The route must start at your position, end at the treasure, and consist of a sequence of moves. In each move, you can go only to an (horizontally or vertically) adjacent square that is not part of an island. But beware: The Viking ship might follow you, using the same kind of moves! After each of your moves according to your route, the Viking ship may move or not. Your move and the Vikings’ reaction together is called a round.

After every round, the following checks are made:

-    If you are in line with the Viking ship (you are in the same vertical or horizontal line as the Viking ship with only sea between the Viking ship and you), you are dead.
-    If you aren’t dead and at the treasure-spot, you get the treasure.

Write a program that decides whether it is possible to set up a fixed route in advance such that you can get the treasure by following this route and will not get killed by the Vikings – no matter how the Viking ship moves.

## 说明/提示

**Sample Explanation 1**

The route is:go down for three times,go right for three times too,go down at last.

**数据范围**

对于 $50\%$ 的数据，$1 \le N,M \le 200$。

对于所有数据，$1 \le N,M \le 700$。

## 样例 #1

### 输入

```
5 7
Y.....V
..I....
..IIIII
.......
...T...```

### 输出

```
YES```

## 样例 #2

### 输入

```
5 7
Y....V.
..I....
..IIIII
.......
...T...```

### 输出

```
NO```

## 样例 #3

### 输入

```
2 3
.YT
VII```

### 输出

```
NO```

# AI分析结果



### 综合分析与结论
本题需在保证玩家路径不被维京船攻击的前提下找到固定路线，核心在于高效处理维京船的攻击范围。题解主要分为两类思路：**实时扩展攻击标记**和**预处理行列最短时间**。最优解法通过预处理或同步 BFS 将时间复杂度优化至 $O(NM)$，确保大数据下的可行性。

---

### 精选题解

#### 1. XYY1411 的题解（⭐⭐⭐⭐⭐）
**关键亮点**：
- **攻击范围动态标记**：每次维京船移动后，实时标记其攻击线（横向和纵向），直到遇到岛屿。
- **双队列同步 BFS**：分别处理玩家和维京船的移动，确保攻击范围实时更新。
- **位运算状态压缩**：用位掩码高效存储格子的攻击状态，减少空间和时间开销。
**代码核心**：
```cpp
void vikatk(int x, int y) {
    // 标记横向和纵向攻击范围
    for (int j = y; j > 0 && !island; j--) ... // 横向左
    for (int j = y; j <= m && !island; j++) ... // 横向右
    for (int i = x; i > 0 && !island; i--) ... // 纵向上
    for (int i = x; i <= n && !island; i++) ... // 纵向下
}
```
**个人心得**：通过分离攻击标记的横向和纵向，避免重复计算，确保每个点最多被处理两次。

#### 2. serene_analysis 的题解（⭐⭐⭐⭐⭐）
**关键亮点**：
- **行列最短时间预处理**：计算维京船到每行/列的最短时间，将攻击判断降为 $O(1)$。
- **动态规划优化**：通过两次遍历（正向和反向）预处理每行每列的最小到达时间。
**代码核心**：
```cpp
// 预处理行和列的最短时间
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
        linv[i][j] = min(linv[i-1][j], vdis[i][j]); // 行最短
        colv[i][j] = min(colv[i][j-1], vdis[i][j]); // 列最短
    }
}
// 反向更新确保全局最小
for (int i = n; i >= 1; i--) {
    for (int j = m; j >= 1; j--) {
        linv[i][j] = min(linv[i+1][j], linv[i][j]);
        colv[i][j] = min(colv[i][j+1], colv[i][j]);
        vdis[i][j] = min(linv[i][j], colv[i][j]); // 综合行列
    }
}
```

#### 3. Cutata 的题解（⭐⭐⭐⭐）
**关键亮点**：
- **同步双队列 BFS**：交替处理玩家和维京船的移动，确保步骤一致。
- **实时攻击范围扩散**：维京船每移动一步后立即扩散攻击线。
**代码核心**：
```cpp
while (玩家队列非空) {
    扩展维京船队列，标记攻击线;
    扩展玩家队列，避开攻击标记;
    if (到达宝藏) return YES;
}
```

---

### 关键思路与技巧总结
1. **攻击范围预处理**：通过 BFS 或动态规划预处理维京船的攻击时间，将攻击判断复杂度降为 $O(1)$。
2. **同步 BFS 优化**：双队列交替处理玩家和维京船的移动，实时更新攻击标记。
3. **状态压缩**：使用位运算或二维数组高效存储攻击状态，减少冗余计算。

---

### 相似题目推荐
1. **P1443 马的遍历**（BFS 最短路径，动态扩展）
2. **P1162 填涂颜色**（矩阵染色，预处理边界）
3. **P1131 潜伏者**（路径规划与条件判断）

---
处理用时：186.38秒