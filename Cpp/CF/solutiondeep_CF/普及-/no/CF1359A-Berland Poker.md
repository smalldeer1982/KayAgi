# 题目信息

# Berland Poker

## 题目描述

The game of Berland poker is played with a deck of $ n $ cards, $ m $ of which are jokers. $ k $ players play this game ( $ n $ is divisible by $ k $ ).

At the beginning of the game, each player takes $ \frac{n}{k} $ cards from the deck (so each card is taken by exactly one player). The player who has the maximum number of jokers is the winner, and he gets the number of points equal to $ x - y $ , where $ x $ is the number of jokers in the winner's hand, and $ y $ is the maximum number of jokers among all other players. If there are two or more players with maximum number of jokers, all of them are winners and they get $ 0 $ points.

Here are some examples:

- $ n = 8 $ , $ m = 3 $ , $ k = 2 $ . If one player gets $ 3 $ jokers and $ 1 $ plain card, and another player gets $ 0 $ jokers and $ 4 $ plain cards, then the first player is the winner and gets $ 3 - 0 = 3 $ points;
- $ n = 4 $ , $ m = 2 $ , $ k = 4 $ . Two players get plain cards, and the other two players get jokers, so both of them are winners and get $ 0 $ points;
- $ n = 9 $ , $ m = 6 $ , $ k = 3 $ . If the first player gets $ 3 $ jokers, the second player gets $ 1 $ joker and $ 2 $ plain cards, and the third player gets $ 2 $ jokers and $ 1 $ plain card, then the first player is the winner, and he gets $ 3 - 2 = 1 $ point;
- $ n = 42 $ , $ m = 0 $ , $ k = 7 $ . Since there are no jokers, everyone gets $ 0 $ jokers, everyone is a winner, and everyone gets $ 0 $ points.

Given $ n $ , $ m $ and $ k $ , calculate the maximum number of points a player can get for winning the game.

## 说明/提示

Test cases of the example are described in the statement.

## 样例 #1

### 输入

```
4
8 3 2
4 2 4
9 6 3
42 0 7```

### 输出

```
3
0
1
0```

# AI分析结果

### 题目内容
# 伯兰德州扑克

## 题目描述
伯兰德州扑克游戏使用一副 $n$ 张牌进行，其中 $m$ 张是百搭牌（jokers）。有 $k$ 个玩家参与游戏（$n$ 能被 $k$ 整除）。

在游戏开始时，每个玩家从牌堆中抽取 $\frac{n}{k}$ 张牌（所以每张牌恰好被一个玩家抽取）。拥有最多百搭牌的玩家获胜，他获得的分数等于 $x - y$，其中 $x$ 是获胜玩家手中的百搭牌数量，$y$ 是其他所有玩家中拥有最多百搭牌的数量。如果有两个或更多玩家拥有最多的百搭牌，则他们都是获胜者，并且都获得 $0$ 分。

以下是一些示例：
- $n = 8$，$m = 3$，$k = 2$。如果一个玩家得到 $3$ 张百搭牌和 $1$ 张普通牌，而另一个玩家得到 $0$ 张百搭牌和 $4$ 张普通牌，那么第一个玩家获胜并获得 $3 - 0 = 3$ 分；
- $n = 4$，$m = 2$，$k = 4$。两个玩家拿到普通牌，另外两个玩家拿到百搭牌，所以这两个拿到百搭牌的玩家都是获胜者，并且都获得 $0$ 分；
- $n = 9$，$m = 6$，$k = 3$。如果第一个玩家得到 $3$ 张百搭牌，第二个玩家得到 $1$ 张百搭牌和 $2$ 张普通牌，第三个玩家得到 $2$ 张百搭牌和 $1$ 张普通牌，那么第一个玩家获胜，并且他获得 $3 - 2 = 1$ 分；
- $n = 42$，$m = 0$，$k = 7$。由于没有百搭牌，每个人都得到 $0$ 张百搭牌，每个人都是获胜者，并且每个人都获得 $0$ 分。

给定 $n$、$m$ 和 $k$，计算玩家赢得游戏时可以获得的最大分数。

## 说明/提示
示例中的测试用例在题目描述中有说明。

## 样例 #1
### 输入
```
4
8 3 2
4 2 4
9 6 3
42 0 7
```
### 输出
```
3
0
1
0
```

### 算法分类
贪心

### 题解综合分析与结论
这些题解的核心思路都是基于贪心策略，将百搭牌尽可能多地分配给一个玩家，同时使其他玩家手中的百搭牌数量尽可能少，从而使两者差值最大。主要通过对 $m$ 和 $\frac{n}{k}$ 的大小关系进行分类讨论来确定最大得分：
 - **当 $m \leq \frac{n}{k}$ 时**：可以将所有百搭牌都给一个玩家，此时该玩家的得分就是 $m$。
 - **当 $m > \frac{n}{k}$ 时**：先让一个玩家拿满 $\frac{n}{k}$ 张百搭牌，然后将剩余的 $m - \frac{n}{k}$ 张百搭牌平均分给剩下的 $k - 1$ 个玩家。这里的难点在于对剩余百搭牌平均分配时的处理，因为要保证第二多的玩家手中百搭牌数量尽可能少，所以需要向上取整，即第二多的玩家手中百搭牌数量为 $\left\lceil\frac{m - \frac{n}{k}}{k - 1}\right\rceil$，此时得分就是 $\frac{n}{k} - \left\lceil\frac{m - \frac{n}{k}}{k - 1}\right\rceil$ 。

不同题解在实现细节上略有差异，如向上取整的方式、代码风格和对边界条件的处理等。

### 通用建议与扩展思路
对于此类贪心问题，关键在于明确如何分配资源能使目标最优，即找到贪心策略。在实现过程中，要注意边界条件和特殊情况的处理，以及数学运算的准确性，如向上取整操作。可以拓展到类似的资源分配求最值问题，进一步巩固贪心策略的应用。

### 相似知识点洛谷题目推荐
 - [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
 - [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)
 - [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123) 

---
处理用时：35.85秒