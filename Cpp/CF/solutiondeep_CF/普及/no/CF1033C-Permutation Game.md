# 题目信息

# Permutation Game

## 题目描述

After a long day, Alice and Bob decided to play a little game. The game board consists of $ n $ cells in a straight line, numbered from $ 1 $ to $ n $ , where each cell contains a number $ a_i $ between $ 1 $ and $ n $ . Furthermore, no two cells contain the same number.

A token is placed in one of the cells. They take alternating turns of moving the token around the board, with Alice moving first. The current player can move from cell $ i $ to cell $ j $ only if the following two conditions are satisfied:

- the number in the new cell $ j $ must be strictly larger than the number in the old cell $ i $ (i.e. $ a_j > a_i $ ), and
- the distance that the token travels during this turn must be a multiple of the number in the old cell (i.e. $ |i-j|\bmod a_i = 0 $ ).

Whoever is unable to make a move, loses. For each possible starting position, determine who wins if they both play optimally. It can be shown that the game is always finite, i.e. there always is a winning strategy for one of the players.

## 说明/提示

In the first sample, if Bob puts the token on the number (not position):

- $ 1 $ : Alice can move to any number. She can win by picking $ 7 $ , from which Bob has no move.
- $ 2 $ : Alice can move to $ 3 $ and $ 5 $ . Upon moving to $ 5 $ , Bob can win by moving to $ 8 $ . If she chooses $ 3 $ instead, she wins, as Bob has only a move to $ 4 $ , from which Alice can move to $ 8 $ .
- $ 3 $ : Alice can only move to $ 4 $ , after which Bob wins by moving to $ 8 $ .
- $ 4 $ , $ 5 $ , or $ 6 $ : Alice wins by moving to $ 8 $ .
- $ 7 $ , $ 8 $ : Alice has no move, and hence she loses immediately.

## 样例 #1

### 输入

```
8
3 6 5 4 2 7 1 8
```

### 输出

```
BAAAABAB
```

## 样例 #2

### 输入

```
15
3 11 2 5 10 9 7 13 15 8 4 12 6 1 14
```

### 输出

```
ABAAAABBBAABAAB
```

# AI分析结果

### 题目内容重写
**排列游戏**

#### 题目描述
在一天的忙碌后，Alice和Bob决定玩一个小游戏。游戏棋盘由$n$个排成一行的格子组成，编号从$1$到$n$，每个格子中有一个数字$a_i$，且$a_i$在$1$到$n$之间，且所有$a_i$互不相同。

一个棋子被放在其中一个格子上。Alice和Bob轮流移动棋子，Alice先手。当前玩家可以从格子$i$移动到格子$j$，当且仅当满足以下两个条件：
- 新格子$j$中的数字必须严格大于旧格子$i$中的数字（即$a_j > a_i$），
- 棋子移动的距离必须是旧格子$i$中数字的倍数（即$|i-j|\bmod a_i = 0$）。

无法移动棋子的玩家输掉游戏。对于每个可能的起始位置，确定如果双方都采取最优策略，谁会获胜。可以证明游戏总是有限的，即总有一方有必胜策略。

#### 说明/提示
在第一个样例中，如果Bob将棋子放在数字（不是位置）：
- $1$：Alice可以移动到任何数字。她可以通过选择$7$获胜，因为Bob无法移动。
- $2$：Alice可以移动到$3$和$5$。如果她选择$5$，Bob可以通过移动到$8$获胜。如果她选择$3$，她获胜，因为Bob只能移动到$4$，之后Alice可以移动到$8$。
- $3$：Alice只能移动到$4$，之后Bob通过移动到$8$获胜。
- $4$、$5$、$6$：Alice通过移动到$8$获胜。
- $7$、$8$：Alice无法移动，因此她立即输掉游戏。

#### 样例 #1
##### 输入
```
8
3 6 5 4 2 7 1 8
```
##### 输出
```
BAAAABAB
```

#### 样例 #2
##### 输入
```
15
3 11 2 5 10 9 7 13 15 8 4 12 6 1 14
```
##### 输出
```
ABAAAABBBAABAAB
```

### 算法分类
动态规划、图论

### 题解分析与结论
本题的核心是通过动态规划和图论的方法，确定每个起始位置的胜负状态。两位作者的题解都采用了类似的方法，即通过构建有向无环图（DAG）并进行拓扑排序，来确定每个位置的胜负状态。

#### 叶ID的题解（评分：5星）
- **关键亮点**：详细解释了博弈论中的必胜与必败状态，并通过动态规划从大到小进行状态转移，确保了时间复杂度在合理范围内。
- **代码实现**：通过枚举倍数的方法，减少了时间复杂度，代码清晰且高效。

```cpp
for(int i=n;i>=1;i--) {
    int u = pos[i];
    status[u] = 0;
    int v = u;
    while(v - arr[u] > 0) v-=arr[u];
    for(;v<=n;v+=arr[u]) {
        if(!(arr[u] < arr[v])) continue;
        if(status[v] == 0) {
            status[u] = 1; break;
        }
    }
}
```

#### cosf的题解（评分：4星）
- **关键亮点**：通过反向建边和拓扑排序来确定每个位置的胜负状态，思路清晰，代码简洁。
- **代码实现**：使用拓扑排序的方法，确保了每个位置的胜负状态能够正确传递。

```cpp
for (int i = 1; i <= n; i++) {
    for (int j = i - val[i]; j >= 1; j -= val[i]) {
        if (val[j] > val[i]) {
            e[j].push_back(i);
            in[i]++;
        }
    }
    for (int j = i + val[i]; j <= n; j += val[i]) {
        if (val[j] > val[i]) {
            e[j].push_back(i);
            in[i]++;
        }
    }
}
```

### 最优关键思路
- **动态规划与拓扑排序结合**：通过从大到小的顺序进行状态转移，确保每个位置的胜负状态能够正确确定。
- **枚举倍数优化**：通过只枚举距离为当前格子数字倍数的格子，减少时间复杂度，确保算法高效。

### 可拓展之处
- **类似问题**：可以扩展到其他博弈论问题，如Nim游戏、取石子游戏等，通过动态规划和图论的方法解决。
- **算法优化**：在类似的问题中，可以通过枚举倍数或其他优化方法，减少时间复杂度，提高算法效率。

### 推荐题目
1. [P2734 [USACO3.3]游戏](https://www.luogu.com.cn/problem/P2734)
2. [P2960 [USACO09OPEN]工作调度](https://www.luogu.com.cn/problem/P2960)
3. [P2947 [USACO09MAR]向右看齐](https://www.luogu.com.cn/problem/P2947)

---
处理用时：36.65秒