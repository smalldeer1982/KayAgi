# 题目信息

# Chess For Three

## 题目描述

Three friends gathered to play a few games of chess together.

In every game, two of them play against each other. The winner gets $ 2 $ points while the loser gets $ 0 $ , and in case of a draw, both players get $ 1 $ point each. Note that the same pair of players could have played any non-negative number of times (possibly zero). It is also possible that no games were played at all.

You've been told that their scores after all the games were played were $ p_1 $ , $ p_2 $ and $ p_3 $ . Additionally, it is guaranteed that $ p_1 \leq p_2 \leq p_3 $ holds.

Find the maximum number of draws that could have happened and print it. If there isn't any way to obtain $ p_1 $ , $ p_2 $ and $ p_3 $ as a result of a non-negative number of games between the three players, print $ -1 $ instead.

## 说明/提示

In the first example, no games were played at all, so no draws could occur either.

For the second example, exactly one game occurred between the second and the third player and it ended in draw, so the answer is $ 1 $ .

It's easy to see that there's no set of games achieving the scores in third example, so the answer for it is $ -1 $ .

## 样例 #1

### 输入

```
7
0 0 0
0 1 1
1 1 1
1 1 2
3 3 3
3 4 5
1 1 10```

### 输出

```
0
1
-1
2
-1
6
2```

# AI分析结果

### 题目内容重写

# 三人象棋

## 题目描述

三位朋友聚在一起玩了几局象棋。

在每一局比赛中，两人对弈。胜者获得2分，败者获得0分，如果平局，双方各得1分。注意，同一对玩家可能进行了任意非负次数的对局（可能为零）。也有可能没有进行任何比赛。

你被告知他们在所有比赛后的得分分别为 $ p_1 $ , $ p_2 $ 和 $ p_3 $ 。此外，保证 $ p_1 \leq p_2 \leq p_3 $ 成立。

找出可能发生的最大平局数并输出。如果无法通过非负数的比赛次数得到 $ p_1 $ , $ p_2 $ 和 $ p_3 $ 作为结果，则输出 $ -1 $ 。

## 说明/提示

在第一个例子中，没有进行任何比赛，因此也没有平局。

对于第二个例子，第二和第三位玩家之间进行了一局比赛并以平局结束，因此答案为 $ 1 $ 。

很容易看出，第三个例子中没有一组比赛可以实现这些得分，因此答案为 $ -1 $ 。

## 样例 #1

### 输入

```
7
0 0 0
0 1 1
1 1 1
1 1 2
3 3 3
3 4 5
1 1 10
```

### 输出

```
0
1
-1
2
-1
6
2
```

### 题解分析与结论

由于暂无题解，我们将从题目本身出发，分析可能的解题思路。

#### 解题思路

1. **总分验证**：首先，总得分必须是偶数，因为每局比赛的总分为2分（无论是胜负还是平局）。如果总得分不是偶数，直接输出-1。

2. **平局数的计算**：平局数的最大值可以通过以下步骤计算：
   - 计算总得分 $ S = p_1 + p_2 + p_3 $。
   - 计算非平局比赛的得分贡献，即每局非平局比赛贡献2分。
   - 平局数的最大值等于总得分减去非平局比赛的得分贡献，再除以2。

3. **特殊情况处理**：如果平局数的计算结果为负数，或者无法通过合理的比赛次数得到给定的得分，则输出-1。

#### 关键思路

- **总分验证**：确保总得分的合理性。
- **平局数的计算**：通过总得分和非平局比赛的得分贡献来计算最大平局数。
- **特殊情况处理**：确保计算结果在合理范围内。

#### 扩展思路

- 类似的问题可以扩展到更多玩家或不同得分规则的情况。
- 可以考虑使用动态规划或贪心算法来优化计算过程。

### 推荐题目

1. [P1002 过河卒](https://www.luogu.com.cn/problem/P1002) - 考察动态规划的应用。
2. [P1048 采药](https://www.luogu.com.cn/problem/P1048) - 考察背包问题的应用。
3. [P1057 传球游戏](https://www.luogu.com.cn/problem/P1057) - 考察动态规划和状态转移的应用。

### 通用建议

- 在解决类似问题时，首先要确保输入数据的合理性。
- 通过数学推导和逻辑分析，找出问题的关键点。
- 使用适当的算法和数据结构来优化计算过程。

---
处理用时：31.09秒