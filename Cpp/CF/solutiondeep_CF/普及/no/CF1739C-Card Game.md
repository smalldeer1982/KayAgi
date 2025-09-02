# 题目信息

# Card Game

## 题目描述

Consider a game with $ n $ cards ( $ n $ is even). Each card has a number written on it, between $ 1 $ and $ n $ . All numbers on the cards are different. We say that a card with number $ x $ is stronger than a card with number $ y $ if $ x > y $ .

Two players, Alex and Boris, play this game. In the beginning, each of them receives exactly $ \frac{n}{2} $ cards, so each card belongs to exactly one player. Then, they take turns. Alex goes first, then Boris, then Alex again, and so on.

On a player's turn, he must play exactly one of his cards. Then, if the opponent doesn't have any cards stronger than the card played, the opponent loses, and the game ends. Otherwise, the opponent has to play a stronger card (exactly one card as well). These two cards are removed from the game, and the turn ends. If there are no cards left, the game ends in a draw; otherwise it's the opponent's turn.

Consider all possible ways to distribute the cards between two players, so that each of them receives exactly half of the cards. You have to calculate three numbers:

- the number of ways to distribute the cards so that Alex wins;
- the number of ways to distribute the cards so that Boris wins;
- the number of ways to distribute the cards so that the game ends in a draw.

You may assume that both players play optimally (i. e. if a player can win no matter how his opponent plays, he wins). Two ways to distribute the cards are different if there is at least one card such that, in one of these ways, it is given to Alex, and in the other way, it is given to Boris.

For example, suppose $ n = 4 $ , Alex receives the cards $ [2, 3] $ , and Boris receives the cards $ [1, 4] $ . Then the game may go as follows:

- if Alex plays the card $ 2 $ , then Boris has to respond with the card $ 4 $ . Then, Alex's turn ends, and Boris' turn starts. Boris has only one card left, which is $ 1 $ ; he plays it, and Alex responds with the card $ 3 $ . So, the game ends in a draw;
- if Alex plays the card $ 3 $ , then Boris has to respond with the card $ 4 $ . Then, Alex's turn ends, and Boris' turn starts. Boris has only one card left, which is $ 1 $ ; he plays it, and Alex responds with the card $ 2 $ . So, the game ends in a draw.

So, in this case, the game ends in a draw.

## 说明/提示

In the first test case, Alex wins if he receives the card $ 2 $ (he plays it, and Boris cannot respond). If Alex receives the card $ 1 $ , the game ends in a draw.

In the second test case:

- Alex wins if he receives the cards $ [3, 4] $ , $ [2, 4] $ or $ [1, 4] $ ;
- Boris wins if Alex receives the cards $ [1, 2] $ or $ [1, 3] $ ;
- the game ends in a draw if Alex receives the cards $ [2, 3] $ .

## 样例 #1

### 输入

```
5
2
4
6
8
60```

### 输出

```
1 0 1
3 2 1
12 7 1
42 27 1
341102826 248150916 1```

# AI分析结果

### 题目内容重写
# 卡牌游戏

## 题目描述

考虑一个游戏，其中有 $n$ 张牌（$n$ 为偶数）。每张牌上写有一个数字，数字在 $1$ 到 $n$ 之间。所有牌上的数字互不相同。我们说一张数字为 $x$ 的牌比一张数字为 $y$ 的牌更强，如果 $x > y$。

两名玩家，Alex 和 Boris，玩这个游戏。开始时，每人恰好获得 $\frac{n}{2}$ 张牌，因此每张牌属于且仅属于一个玩家。然后，他们轮流进行游戏。Alex 先手，然后是 Boris，接着是 Alex，依此类推。

在玩家的回合中，他必须打出自己的一张牌。然后，如果对手没有比打出的牌更强的牌，对手输掉游戏，游戏结束。否则，对手必须打出一张更强的牌（同样是一张牌）。这两张牌被移出游戏，回合结束。如果没有剩余的牌，游戏以平局结束；否则，轮到对手的回合。

考虑所有可能的牌分配方式，使得每人恰好获得一半的牌。你需要计算三个数字：

- 使得 Alex 获胜的牌分配方式数；
- 使得 Boris 获胜的牌分配方式数；
- 使得游戏以平局结束的牌分配方式数。

你可以假设双方都采取最优策略（即如果玩家无论如何都能获胜，他会获胜）。两种牌分配方式不同，如果至少有一张牌在一种方式中属于 Alex，而在另一种方式中属于 Boris。

例如，假设 $n = 4$，Alex 获得牌 $[2, 3]$，Boris 获得牌 $[1, 4]$。那么游戏可能如下进行：

- 如果 Alex 打出牌 $2$，Boris 必须回应牌 $4$。然后，Alex 的回合结束，Boris 的回合开始。Boris 只有一张牌 $1$；他打出它，Alex 回应牌 $3$。因此，游戏以平局结束；
- 如果 Alex 打出牌 $3$，Boris 必须回应牌 $4$。然后，Alex 的回合结束，Boris 的回合开始。Boris 只有一张牌 $1$；他打出它，Alex 回应牌 $2$。因此，游戏以平局结束。

因此，在这种情况下，游戏以平局结束。

## 说明/提示

在第一个测试用例中，如果 Alex 获得牌 $2$，他获胜（他打出它，Boris 无法回应）。如果 Alex 获得牌 $1$，游戏以平局结束。

在第二个测试用例中：

- 如果 Alex 获得牌 $[3, 4]$、$[2, 4]$ 或 $[1, 4]$，他获胜；
- 如果 Alex 获得牌 $[1, 2]$ 或 $[1, 3]$，Boris 获胜；
- 如果 Alex 获得牌 $[2, 3]$，游戏以平局结束。

## 样例 #1

### 输入

```
5
2
4
6
8
60```

### 输出

```
1 0 1
3 2 1
12 7 1
42 27 1
341102826 248150916 1```

### 算法分类
组合数学

### 题解分析与结论
题目要求计算在给定牌数 $n$ 的情况下，Alex 获胜、Boris 获胜以及平局的牌分配方式数。由于双方都采取最优策略，因此可以通过组合数学的方法来计算这些情况数。

### 精选题解
#### 题解1：Sycamore_Ma (5星)
**关键亮点**：
- 通过定义状态 $a_i$、$b_i$、$t_i$ 分别表示总牌数为 $i$ 时 Alex 获胜、Boris 获胜和平局的发牌方式数。
- 利用组合数和状态转移公式进行递推，最终得出结果。
- 代码清晰，组合数预处理和状态转移实现简洁。

**核心代码**：
```cpp
void table(){
    for (int i = 0; i <= 60; i ++) {
        c[i][0] = c[i][i] = 1;
        for (int j = 1; j < i; j ++) {
            c[i][j] = (c[i-1][j-1] + c[i-1][j]) % MOD;
        }
    }
    
    a[2] = 1;   b[2] = 0;   t[2] = 1;
    for (int i = 4; i <= 60; i += 2){
        t[i] = 1;
        a[i] = c[i-2][(i/2)-2] + c[i-2][(i-2)/2] + b[i-2];
        a[i] %= MOD;
        b[i] = MOD + MOD + c[i][i/2] - a[i] - 1;
        b[i] %= MOD;
    }
}
```

#### 题解2：Hedgehog_210508 (4星)
**关键亮点**：
- 通过分析平局的情况，发现每轮后手都有比先手大的牌，手牌固定，只有一种。
- 利用组合数和快速幂逆元处理组合数计算，代码简洁。

**核心代码**：
```cpp
ll c(ll a,ll b){
    return p[a]%M*qp(p[b],M-2)%M*qp(p[a-b],M-2)%M; 
}
```

#### 题解3：XenonWZH (4星)
**关键亮点**：
- 通过分析每轮的最大牌和次大牌，分情况讨论先手和后手的获胜情况。
- 利用组合数学和递推公式计算获胜情况数，代码清晰。

**核心代码**：
```cpp
inline int C(const int n, const int k) {
    if (k < 0 || k > n) return 0;
    if (k == 0) return 1;
    return fac[n] * facInv[k] % MOD * facInv[n - k] % MOD;
}
```

### 最优关键思路或技巧
1. **组合数学**：通过组合数计算不同牌分配方式数，利用组合数预处理和递推公式进行状态转移。
2. **状态转移**：通过定义状态 $a_i$、$b_i$、$t_i$，利用组合数和状态转移公式进行递推，最终得出结果。
3. **优化计算**：利用快速幂和逆元处理组合数计算，提高计算效率。

### 可拓展之处
类似的问题可以通过组合数学和状态转移的方法来解决，特别是在涉及最优策略和牌分配的问题中。可以进一步研究其他组合数学问题，如排列组合、概率论等。

### 推荐题目
1. [P1357 组合数问题](https://www.luogu.com.cn/problem/P1357)
2. [P2822 组合数问题](https://www.luogu.com.cn/problem/P2822)
3. [P3807 卢卡斯定理](https://www.luogu.com.cn/problem/P3807)

---
处理用时：50.34秒