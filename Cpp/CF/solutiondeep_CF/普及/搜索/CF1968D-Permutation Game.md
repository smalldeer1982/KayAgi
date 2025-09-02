# 题目信息

# Permutation Game

## 题目描述

Bodya and Sasha found a permutation $ p_1,\dots,p_n $ and an array $ a_1,\dots,a_n $ . They decided to play a well-known "Permutation game".

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

Both of them chose a starting position in the permutation.

The game lasts $ k $ turns. The players make moves simultaneously. On each turn, two things happen to each player:

- If the current position of the player is $ x $ , his score increases by $ a_x $ .
- Then the player either stays at his current position $ x $ or moves from $ x $ to $ p_x $ .

 The winner of the game is the player with the higher score after exactly $ k $ turns.Knowing Bodya's starting position $ P_B $ and Sasha's starting position $ P_S $ , determine who wins the game if both players are trying to win.

## 说明/提示

Below you can find the explanation for the first testcase, where the game consists of $ k=2 $ turns.

 TurnBodya's positionBodya's scoreBodya's moveSasha's positionSasha's scoreSasha's movefirst $ 3 $  $ 0 + a_3 = 0 + 5 = 5 $ stays on the same position $ 2 $  $ 0 + a_2 = 0 + 2 = 2 $ moves to $ p_2=1 $ second $ 3 $  $ 5 + a_3 = 5 + 5 = 10 $ stays on the same position $ 1 $  $ 2 + a_1 = 2 + 7 = 9 $ stays on the same positionfinal results $ 3 $  $ 10 $  $ 1 $  $ 9 $ As we may see, Bodya's score is greater, so he wins the game. It can be shown that Bodya always can win this game.

## 样例 #1

### 输入

```
10
4 2 3 2
4 1 2 3
7 2 5 6
10 8 2 10
3 1 4 5 2 7 8 10 6 9
5 10 5 1 3 7 10 15 4 3
2 1000000000 1 2
1 2
4 4
8 10 4 1
5 1 4 3 2 8 6 7
1 1 2 1 2 100 101 102
5 1 2 5
1 2 4 5 3
4 6 9 4 2
4 2 3 1
4 1 3 2
6 8 5 3
6 9 5 4
6 1 3 5 2 4
6 9 8 9 5 10
4 8 4 2
2 3 4 1
5 2 8 7
4 2 3 1
4 1 3 2
6 8 5 3
2 1000000000 1 2
1 2
1000000000 2```

### 输出

```
Bodya
Sasha
Draw
Draw
Bodya
Sasha
Sasha
Sasha
Sasha
Bodya```

# AI分析结果

### 题目翻译

**排列游戏**

#### 题目描述

Bodya 和 Sasha 发现了一个排列 $ p_1,\dots,p_n $ 和一个数组 $ a_1,\dots,a_n $。他们决定玩一个著名的“排列游戏”。

一个长度为 $ n $ 的排列是一个由 $ n $ 个不同的整数组成的数组，这些整数从 $ 1 $ 到 $ n $，顺序任意。例如，$ [2,3,1,5,4] $ 是一个排列，但 $ [1,2,2] $ 不是排列（$ 2 $ 在数组中出现了两次），$ [1,3,4] $ 也不是排列（$ n=3 $ 但数组中有 $ 4 $）。

他们两人各自选择了一个起始位置。

游戏持续 $ k $ 轮。玩家同时进行移动。在每一轮中，每个玩家会发生以下两件事：

- 如果玩家当前的位置是 $ x $，他的得分增加 $ a_x $。
- 然后玩家可以选择停留在当前位置 $ x $，或者从 $ x $ 移动到 $ p_x $。

游戏结束后，得分更高的玩家获胜。已知 Bodya 的起始位置 $ P_B $ 和 Sasha 的起始位置 $ P_S $，确定谁会获胜，假设双方都尽力赢得比赛。

#### 说明/提示

下面是对第一个测试用例的解释，游戏持续 $ k=2 $ 轮。

| 轮数 | Bodya 的位置 | Bodya 的得分 | Bodya 的移动 | Sasha 的位置 | Sasha 的得分 | Sasha 的移动 |
|------|--------------|--------------|--------------|--------------|--------------|--------------|
| 第一轮 | 3            | $0 + a_3 = 0 + 5 = 5$ | 停留在原地 | 2            | $0 + a_2 = 0 + 2 = 2$ | 移动到 $ p_2=1 $ |
| 第二轮 | 3            | $5 + a_3 = 5 + 5 = 10$ | 停留在原地 | 1            | $2 + a_1 = 2 + 7 = 9$ | 停留在原地 |

最终结果：Bodya 的位置 $ 3 $，得分 $ 10 $；Sasha 的位置 $ 1 $，得分 $ 9 $。可以看到，Bodya 的得分更高，因此他赢得了比赛。可以证明，Bodya 在这种情况下总是可以获胜。

### 题解分析与结论

#### 综合分析

本题的核心在于如何计算两个玩家在 $ k $ 轮游戏中的最大得分。由于玩家可以选择停留在当前位置或移动到 $ p_x $，因此他们的移动路径会形成一个环或链。最优策略是找到一个得分最高的位置，并在该位置停留尽可能多的轮数。

大多数题解都采用了类似的思路：从起始位置开始，沿着 $ p $ 数组移动，记录路径上的得分，并计算在每个位置停留时的总得分，最终取最大值进行比较。

#### 关键思路与技巧

1. **路径遍历与得分计算**：从起始位置开始，沿着 $ p $ 数组移动，记录路径上的得分，并计算在每个位置停留时的总得分。
2. **循环检测**：由于 $ p $ 是一个排列，移动路径最终会进入一个循环，因此可以通过检测是否回到起点来判断是否进入循环。
3. **贪心策略**：最优策略是找到一个得分最高的位置，并在该位置停留尽可能多的轮数。

#### 推荐题解

1. **作者：spire001 (赞：7)**  
   - **星级：4.5**  
   - **关键亮点**：代码简洁，思路清晰，通过遍历路径并计算每个位置的得分，最终取最大值进行比较。  
   - **核心代码**：
     ```cpp
     for(int i = sa; tk; i = b[i]) {
         if(box[i]) break; box[i] = 1;
         sum1 = max(sum1, ns + (long long)a[i] * tk);
         tk--; ns += a[i];
     }
     ```
   - **个人心得**：作者提到“如果最优策略是逛完一圈后再回到某个位置不动的话，那么直接到这个位置不动不就更优了吗”，体现了贪心策略的直观理解。

2. **作者：DrAlfred (赞：6)**  
   - **星级：4**  
   - **关键亮点**：通过图论的角度分析问题，将排列视为有向图，并通过枚举最终停留的位置来计算最大得分。  
   - **核心代码**：
     ```cpp
     for (int i = 0; i <= min((size_t)k, BR.size() - 1); i++) {
         maxB = max(maxB, bSum + (k - i) * a[BR[i]]);
         bSum += a[BR[i]];
     }
     ```
   - **个人心得**：作者提到“两人最终应该会在某个点停止不动”，强调了贪心策略的合理性。

3. **作者：Pursuewind (赞：5)**  
   - **星级：4**  
   - **关键亮点**：通过 BFS 遍历路径，记录每个位置的得分，并取最大值进行比较。  
   - **核心代码**：
     ```cpp
     void BFS(int s) {
         while (!q.empty()) q.pop();
         Record(s, 0, 0);
         while (!q.empty()) {
             int x = q.front().now;
             int res = q.front().res;
             int step = q.front().step;
             if (step >= k) return ;
             q.pop();
             Record(p[x], res + a[x], step + 1);
         }
     }
     ```
   - **个人心得**：作者提到“当 $ k $ 很大时，他们很可能会移动到点权最大的点，然后呆在上面不动了”，体现了对问题的深入理解。

### 推荐题目

1. **洛谷 P1968 - 排列游戏**  
   本题与 CF1968D 类似，考察排列与贪心策略的结合。

2. **洛谷 P1967 - 最大生成树**  
   考察图论与贪心策略的结合，与本题的图论分析思路相似。

3. **洛谷 P1969 - 最小生成树**  
   考察图论与贪心策略的结合，与本题的图论分析思路相似。

---
处理用时：48.66秒