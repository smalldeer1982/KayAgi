# 题目信息

# Sweets Game

## 题目描述

Karlsson has visited Lillebror again. They found a box of chocolates and a big whipped cream cake at Lillebror's place. Karlsson immediately suggested to divide the sweets fairly between Lillebror and himself. Specifically, to play together a game he has just invented with the chocolates. The winner will get the cake as a reward.

The box of chocolates has the form of a hexagon. It contains 19 cells for the chocolates, some of which contain a chocolate. The players move in turns. During one move it is allowed to eat one or several chocolates that lay in the neighboring cells on one line, parallel to one of the box's sides. The picture below shows the examples of allowed moves and of an unacceptable one. The player who cannot make a move loses.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF63E/d39dc87a25b4bbc8e9ef90055ec2e2d8c38df358.png)Karlsson makes the first move as he is Lillebror's guest and not vice versa. The players play optimally. Determine who will get the cake.

## 样例 #1

### 输入

```
  . . .
 . . O .
. . O O .
 . . . .
  . . .
```

### 输出

```
Lillebror```

## 样例 #2

### 输入

```
  . . .
 . . . O
. . . O .
 O . O .
  . O .
```

### 输出

```
Karlsson```

# AI分析结果

### 题目翻译

Karlsson 再次拜访了 Lillebror。他们在 Lillebror 家发现了一盒巧克力和一个大奶油蛋糕。Karlsson 立即建议将甜点公平地分给 Lillebror 和自己。具体来说，他们要用巧克力玩一个游戏，胜者将获得蛋糕作为奖励。

巧克力盒呈六边形，包含 19 个格子，其中一些格子中有巧克力。玩家轮流进行操作。每次操作可以吃掉一条直线上相邻的一个或多个巧克力，且这条直线必须与盒子的一边平行。下图展示了允许的操作和不允许的操作。无法进行操作的玩家输掉游戏。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF63E/d39dc87a25b4bbc8e9ef90055ec2e2d8c38df358.png)

Karlsson 作为客人先手。双方都采取最优策略。请确定谁将获得蛋糕。

### 样例 #1

#### 输入

```
  . . .
 . . O .
. . O O .
 . . . .
  . . .
```

#### 输出

```
Lillebror
```

### 样例 #2

#### 输入

```
  . . .
 . . . O
. . . O .
 O . O .
  . O .
```

#### 输出

```
Karlsson
```

---

### 题解分析与结论

#### 题解对比与评分

1. **xuchenhao2008 (5星)**
   - **关键亮点**：使用了状态压缩和记忆化搜索，详细处理了六边形网格的边界和方向问题，代码注释详细，逻辑清晰。
   - **难点处理**：通过预处理六边形的行数和方向偏移量，简化了斜向移动的判断。
   - **代码实现**：核心代码通过递归和状态压缩判断必胜策略，时间复杂度为 O(2^19)。

2. **Elairin176 (4星)**
   - **关键亮点**：同样使用状态压缩和记忆化搜索，预处理了所有可能的取法，代码简洁。
   - **难点处理**：通过预处理所有可能的取法，简化了搜索过程。
   - **代码实现**：核心代码通过 DFS 和状态压缩判断必胜策略，时间复杂度为 O(2^19)。

3. **Ghosty_Neutrino (3星)**
   - **关键亮点**：使用状态压缩和记忆化搜索，代码简洁。
   - **难点处理**：通过枚举所有可能的取法，简化了搜索过程。
   - **代码实现**：核心代码通过 DFS 和状态压缩判断必胜策略，时间复杂度为 O(2^19)。

#### 最优关键思路与技巧

- **状态压缩**：将六边形网格的每个格子状态压缩为一个二进制数，便于存储和判断。
- **记忆化搜索**：通过记忆化搜索避免重复计算，提高效率。
- **预处理**：预处理六边形网格的行数和方向偏移量，简化斜向移动的判断。

#### 可拓展之处

- **类似题目**：可以扩展到其他形状的网格或更多格子的情况，如正方形网格或更大规模的六边形网格。
- **算法套路**：状态压缩和记忆化搜索是解决类似博弈问题的常用套路，可以应用于其他类似的取石子游戏或棋盘游戏。

#### 推荐题目

1. [P2148 [SDOI2009]E&D](https://www.luogu.com.cn/problem/P2148)
2. [P2575 [SCOI2010]序列操作](https://www.luogu.com.cn/problem/P2575)
3. [P3185 [HNOI2007]分裂游戏](https://www.luogu.com.cn/problem/P3185)

#### 个人心得摘录

- **xuchenhao2008**：通过预处理六边形的行数和方向偏移量，简化了斜向移动的判断，避免了复杂的边界处理。
- **Elairin176**：预处理所有可能的取法，简化了搜索过程，提高了代码的可读性和效率。
- **Ghosty_Neutrino**：通过枚举所有可能的取法，简化了搜索过程，但代码可读性较差，注释较少。

### 核心代码片段

```cpp
int dfs(int pl, int cur) {
    if (ans[cur] == 1) return pl;
    else if (ans[cur] == -1) return 1 - pl;

    int to, res = 1 - pl;
    if (cur == 0) return res;

    rep(st, 0, 19) {
        if ((cur & (1 << st)) == 0) continue;

        to = cur;
        for (int i = st; i < pre[row[st]] + len[row[st]]; i++) {
            if ((to & (1 << i)) == 0) break;
            to -= (1 << i);
            if (vis[1 - pl][to] == 0) {
                vis[1 - pl][to] = 1;
                res = dfs(1 - pl, to);
                vis[1 - pl][to] = 0;
                if (res == pl) {
                    ans[cur] = 1;
                    return res;
                }
            }
        }

        to = cur;
        for (int i = st;;) {
            if ((to & (1 << i)) == 0) break;
            to -= (1 << i);
            if (vis[1 - pl][to] == 0 && i != st) {
                vis[1 - pl][to] = 1;
                res = dfs(1 - pl, to);
                vis[1 - pl][to] = 0;
                if (res == pl) {
                    ans[cur] = 1;
                    return res;
                }
            }
            if (row[i] == 5) break;
            if (i + boost[row[i]] >= pre[row[i] + 1] + len[row[i] + 1]) break;
            i += boost[row[i]];
        }

        to = cur;
        for (int i = st;;) {
            if ((to & (1 << i)) == 0) break;
            to -= (1 << i);
            if (vis[1 - pl][to] == 0 && i != st) {
                vis[1 - pl][to] = 1;
                res = dfs(1 - pl, to);
                vis[1 - pl][to] = 0;
                if (res == pl) {
                    ans[cur] = 1;
                    return res;
                }
            }
            if (row[i] == 5) break;
            if (i + deboost[row[i]] < pre[row[i]] + len[row[i]]) break;
            i += deboost[row[i]];
        }
    }
    ans[cur] = -1;
    return res;
}
```

---
处理用时：59.16秒