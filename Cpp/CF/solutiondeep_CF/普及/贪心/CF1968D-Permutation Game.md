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

### 题目内容重写

**排列游戏**

## 题目描述

Bodya 和 Sasha 发现了一个排列 $ p_1,\dots,p_n $ 和一个数组 $ a_1,\dots,a_n $。他们决定玩一个著名的“排列游戏”。

一个长度为 $ n $ 的排列是一个由 $ n $ 个不同的整数组成的数组，这些整数从 $ 1 $ 到 $ n $ 且顺序任意。例如，$ [2,3,1,5,4] $ 是一个排列，但 $ [1,2,2] $ 不是排列（因为 $ 2 $ 出现了两次），$ [1,3,4] $ 也不是排列（因为 $ n=3 $ 但数组中出现了 $ 4 $）。

两人各自选择了一个起始位置。

游戏进行 $ k $ 轮。玩家同时行动。每轮中，每个玩家会发生以下两件事：

- 如果玩家当前的位置是 $ x $，他的得分增加 $ a_x $。
- 然后玩家可以选择停留在当前位置 $ x $，或者从 $ x $ 移动到 $ p_x $。

游戏结束后，得分更高的玩家获胜。已知 Bodya 的起始位置 $ P_B $ 和 Sasha 的起始位置 $ P_S $，如果两人都采取最优策略，确定谁会获胜。

## 说明/提示

下面是对第一个测试用例的解释，游戏进行 $ k=2 $ 轮。

| 轮次 | Bodya 的位置 | Bodya 的得分 | Bodya 的移动 | Sasha 的位置 | Sasha 的得分 | Sasha 的移动 |
|------|--------------|--------------|--------------|--------------|--------------|--------------|
| 第一轮 | 3 | 0 + 5 = 5 | 停留在原地 | 2 | 0 + 2 = 2 | 移动到 $ p_2=1 $ |
| 第二轮 | 3 | 5 + 5 = 10 | 停留在原地 | 1 | 2 + 7 = 9 | 停留在原地 |

最终结果：Bodya 的位置为 3，得分为 10；Sasha 的位置为 1，得分为 9。可以看出，Bodya 的得分更高，因此他赢得了游戏。可以证明，Bodya 总能赢得这个游戏。

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

### 题解分析与结论

本题的核心在于如何在 $k$ 轮内通过移动或停留来最大化得分。由于排列 $p$ 的性质，玩家的移动路径会形成一个环或链，因此可以通过遍历路径来找到最优的停留点。

#### 关键思路：
1. **路径遍历**：由于排列 $p$ 的性质，玩家的移动路径会形成一个环或链，因此可以通过遍历路径来找到最优的停留点。
2. **贪心策略**：玩家在遍历路径时，应尽可能早地停留在得分最高的点，以最大化后续的得分。
3. **暴力枚举**：对于每个可能的停留点，计算在该点停留的得分，并选择最大值。

#### 最优策略：
- 玩家在遍历路径时，应记录当前路径上的得分，并在每个点计算停留后的总得分，选择最大值。

### 评分较高的题解

#### 1. 作者：DrAlfred (赞：6)
- **星级**：4.5
- **关键亮点**：通过图论的角度分析问题，将排列视为有向图，使用 DFS 遍历路径，并枚举每个可能的停留点来计算最大得分。
- **代码实现**：
  ```cpp
  set<int> B, S;
  vector<int> BR, SR;
  for (; !B.count(pb); pb = p[pb]) {
      B.insert(pb), BR.push_back(pb);
  }
  for (; !S.count(ps); ps = p[ps]) {
      S.insert(ps), SR.push_back(ps);
  }
  i64 maxB = 0, maxS = 0, bSum = 0, sSum = 0;
  for (int i = 0; i <= min((size_t)k, BR.size() - 1); i++) {
      maxB = max(maxB, bSum + (k - i) * a[BR[i]]);
      bSum += a[BR[i]];
  }
  for (int i = 0; i <= min((size_t)k, SR.size() - 1); i++) {
      maxS = max(maxS, sSum + (k - i) * a[SR[i]]);
      sSum += a[SR[i]];
  }
  ```
- **个人心得**：通过将排列视为有向图，可以更清晰地分析玩家的移动路径，从而更容易找到最优策略。

#### 2. 作者：Pursuewind (赞：5)
- **星级**：4
- **关键亮点**：使用 BFS 遍历路径，并在每个点计算停留后的得分，选择最大值。
- **代码实现**：
  ```cpp
  void BFS(int s){
      while (!q.empty()) q.pop();
      Record(s, 0, 0);
      while (!q.empty()){
          int x = q.front().now;
          int res = q.front().res;
          int step = q.front().step;
          if (step >= k) return ;
          q.pop();
          Record(p[x], res + a[x], step + 1);
      }
  }
  ```
- **个人心得**：通过 BFS 遍历路径，可以确保在 $k$ 轮内找到最优的停留点，且代码实现较为简洁。

#### 3. 作者：JuRuoOIer (赞：0)
- **星级**：4
- **关键亮点**：通过遍历路径，记录每个点的得分，并选择最大值，代码简洁且易于理解。
- **代码实现**：
  ```cpp
  while(cnt<k&&!vis[sa]){
      vis[sa]=1;
      if(a[sa]>mxx){
          mxx=a[sa];
          mxa=max(mxa,tot+a[sa]*(k-cnt));
      }
      cnt++;
      tot+=a[sa];
      sa=p[sa];
  }
  ```
- **个人心得**：通过简单的遍历和贪心策略，可以快速找到最优的停留点，代码实现较为高效。

### 推荐题目
1. [P1967 货车运输](https://www.luogu.com.cn/problem/P1967)
2. [P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)
3. [P3388 【模板】割点（割顶）](https://www.luogu.com.cn/problem/P3388)

这些题目都涉及到图论和路径遍历的相关知识，可以帮助进一步巩固本题的解题思路。

---
处理用时：57.47秒