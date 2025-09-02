# 题目信息

# Fragile Bridges

## 题目描述

You are playing a video game and you have just reached the bonus level, where the only possible goal is to score as many points as possible. Being a perfectionist, you've decided that you won't leave this level until you've gained the maximum possible number of points there.

The bonus level consists of $ n $ small platforms placed in a line and numbered from $ 1 $ to $ n $ from left to right and ( $ n-1 $ ) bridges connecting adjacent platforms. The bridges between the platforms are very fragile, and for each bridge the number of times one can pass this bridge from one of its ends to the other before it collapses forever is known in advance.

The player's actions are as follows. First, he selects one of the platforms to be the starting position for his hero. After that the player can freely move the hero across the platforms moving by the undestroyed bridges. As soon as the hero finds himself on a platform with no undestroyed bridge attached to it, the level is automatically ended. The number of points scored by the player at the end of the level is calculated as the number of transitions made by the hero between the platforms. Note that if the hero started moving by a certain bridge, he has to continue moving in the same direction until he is on a platform.

Find how many points you need to score to be sure that nobody will beat your record, and move to the next level with a quiet heart.

## 说明/提示

One possibility of getting $ 5 $ points in the sample is starting from platform $ 3 $ and consequently moving to platforms $ 4 $ , $ 3 $ , $ 2 $ , $ 1 $ and $ 2 $ . After that the only undestroyed bridge is the bridge between platforms $ 4 $ and $ 5 $ , but this bridge is too far from platform $ 2 $ where the hero is located now.

## 样例 #1

### 输入

```
5
2 1 2 1
```

### 输出

```
5
```

# AI分析结果

### 题目内容重写（中文）

你正在玩一款游戏，刚刚进入了一个奖励关卡，目标是通过尽可能多的得分来获得最高分数。作为一个完美主义者，你决定在获得最大可能分数之前不会离开这个关卡。

奖励关卡由 $n$ 个小平台组成，这些平台按从左到右依次编号为 $1$ 到 $n$，并且有 $n-1$ 座桥连接相邻的平台。这些桥非常脆弱，每座桥从一端到另一端可以经过的次数是已知的。

玩家的操作如下：首先选择一个平台作为英雄的起始位置。之后，玩家可以自由地通过未损坏的桥在平台之间移动英雄。当英雄发现自己所在的平台没有未损坏的桥连接时，关卡自动结束。玩家在关卡结束时获得的分数为英雄在平台之间移动的次数。注意，如果英雄开始通过某座桥移动，他必须继续朝同一方向移动，直到到达一个平台。

请找出你需要获得的分数，以确保没有人能打破你的记录，并安心进入下一关。

### 样例 #1

#### 输入
```
5
2 1 2 1
```

#### 输出
```
5
```

### 题解分析与结论

该题的核心在于如何通过动态规划（DP）来计算从每个平台出发向左或向右移动的最大得分。题解的主要思路是将问题分解为向左和向右两个方向的子问题，分别计算每个方向的得分，然后合并结果得到最终的最大得分。

#### 关键思路与技巧
1. **状态定义**：大多数题解都采用了类似的状态定义，即 `dp[i][0]` 表示从平台 $i$ 向左移动且不返回的最大得分，`dp[i][1]` 表示向左移动且必须返回的最大得分，`dp[i][2]` 和 `dp[i][3]` 分别表示向右移动的两种情况。
2. **状态转移**：状态转移的关键在于如何处理桥的耐久度。对于不返回的情况，尽量“榨干”桥的耐久度；对于返回的情况，需要确保桥的耐久度足够支持往返。
3. **合并结果**：最终的最大得分是通过合并向左和向右的得分得到的，即 `max(dp[i][0] + dp[i][3], dp[i][1] + dp[i][2])`。

#### 推荐题解
1. **作者：pythoner713**  
   **星级：5**  
   **关键亮点**：思路清晰，状态定义合理，代码简洁且易于理解。通过将问题分解为向左和向右两个方向的子问题，分别进行DP计算，最后合并结果。  
   **核心代码**：
   ```cpp
   for(int i = 2; i <= n; i++){
       if(a[i - 1] > 1) f[i][1] = f[i - 1][1] + a[i - 1] / 2 * 2;
       f[i][0] = max(f[i][1], f[i - 1][0] + a[i - 1] - !(a[i - 1] & 1));
       f[i][0] = max(f[i][0], f[i - 1][1] + a[i - 1]);
   }
   for(int i = n - 1; i; i--){
       if(a[i] > 1) g[i][1] = g[i + 1][1] + a[i] / 2 * 2;
       g[i][0] = max(g[i][1], g[i + 1][0] + a[i] - !(a[i] & 1));
       g[i][0] = max(g[i][0], g[i + 1][1] + a[i]);
   }
   for(int i = 1; i <= n; i++){
       ans = max(ans, max(f[i][0] + g[i][1], f[i][1] + g[i][0]));
   }
   ```

2. **作者：Liynw**  
   **星级：4.5**  
   **关键亮点**：详细解释了状态转移的逻辑，特别是如何处理桥的耐久度和返回的情况。代码实现清晰，且对边界条件处理得当。  
   **核心代码**：
   ```cpp
   for(int i = 2; i <= n; i++){
       dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]) + ((a[i - 1] & 1) ? a[i - 1] : (a[i - 1] - 1));
       if(a[i - 1] > 1) dp[i][1] = dp[i - 1][1] + ((a[i - 1] & 1) ? (a[i - 1] - 1) : a[i - 1]);
   }
   for(int i = n - 1; i >= 1; i--){
       dp[i][2] = max(dp[i + 1][2], dp[i + 1][3]) + ((a[i] & 1) ? a[i] : (a[i] - 1));
       if(a[i] > 1) dp[i][3] = dp[i + 1][3] + ((a[i] & 1) ? (a[i] - 1) : a[i]);
   }
   for(int i = 1; i <= n; i++){
       ans = max(ans, max(dp[i][0] + dp[i][3], dp[i][1] + dp[i][2]));
   }
   ```

3. **作者：zhou_ziyi**  
   **星级：4**  
   **关键亮点**：状态定义和转移逻辑清晰，代码简洁且易于理解。通过将问题分解为向左和向右两个方向的子问题，分别进行DP计算，最后合并结果。  
   **核心代码**：
   ```cpp
   for(int i = 2; i <= n; i++){
       dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]) + ((a[i - 1] & 1) ? a[i - 1] : (a[i - 1] - 1));
       if(a[i - 1] > 1) dp[i][1] = dp[i - 1][1] + ((a[i - 1] & 1) ? (a[i - 1] - 1) : a[i - 1]);
   }
   for(int i = n - 1; i >= 1; i--){
       dp[i][2] = max(dp[i + 1][2], dp[i + 1][3]) + ((a[i] & 1) ? a[i] : (a[i] - 1));
       if(a[i] > 1) dp[i][3] = dp[i + 1][3] + ((a[i] & 1) ? (a[i] - 1) : a[i]);
   }
   for(int i = 1; i <= n; i++){
       ans = max(ans, max(dp[i][0] + dp[i][3], dp[i][1] + dp[i][2]));
   }
   ```

### 最优关键思路与技巧
1. **状态定义**：将问题分解为向左和向右两个方向的子问题，分别定义状态 `dp[i][0]` 和 `dp[i][1]` 表示不返回和必须返回的最大得分。
2. **状态转移**：根据桥的耐久度，合理计算每个状态的得分，确保在返回和不返回的情况下都能得到最大得分。
3. **合并结果**：通过合并向左和向右的得分，得到最终的最大得分。

### 可拓展之处
该题的思路可以拓展到类似的路径规划问题，特别是在需要考虑路径的往返和资源消耗的情况下。类似的题目可以考察如何在有限的资源下规划最优路径。

### 推荐题目
1. [P1004 方格取数](https://www.luogu.com.cn/problem/P1004)
2. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
3. [P1057 传球游戏](https://www.luogu.com.cn/problem/P1057)

---
处理用时：62.50秒