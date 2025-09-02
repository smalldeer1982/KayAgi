# 题目信息

# Array Walk

## 题目描述

You are given an array $ a_1, a_2, \dots, a_n $ , consisting of $ n $ positive integers.

Initially you are standing at index $ 1 $ and have a score equal to $ a_1 $ . You can perform two kinds of moves:

1. move right — go from your current index $ x $ to $ x+1 $ and add $ a_{x+1} $ to your score. This move can only be performed if $ x<n $ .
2. move left — go from your current index $ x $ to $ x-1 $ and add $ a_{x-1} $ to your score. This move can only be performed if $ x>1 $ . Also, you can't perform two or more moves to the left in a row.

You want to perform exactly $ k $ moves. Also, there should be no more than $ z $ moves to the left among them.

What is the maximum score you can achieve?

## 说明/提示

In the first testcase you are not allowed to move left at all. So you make four moves to the right and obtain the score $ a_1 + a_2       + a_3 + a_4 + a_5 $ .

In the second example you can move one time to the left. So we can follow these moves: right, right, left, right. The score will be $ a_1 + a_2 + a_3 + a_2 + a_3 $ .

In the third example you can move four times to the left but it's not optimal anyway, you can just move four times to the right and obtain the score $ a_1 + a_2 + a_3 + a_4 + a_5 $ .

## 样例 #1

### 输入

```
4
5 4 0
1 5 4 3 2
5 4 1
1 5 4 3 2
5 4 4
10 20 30 40 50
10 7 3
4 6 8 2 9 9 7 4 10 9```

### 输出

```
15
19
150
56```

# AI分析结果

### 题目重写
#### 题目描述
给定一个由 $n$ 个正整数组成的数组 $a_1, a_2, \dots, a_n$。初始时你站在索引 $1$ 的位置，得分为 $a_1$。你可以执行以下两种移动操作：

1. **向右移动**：从当前索引 $x$ 移动到 $x+1$，并将 $a_{x+1}$ 加到你的得分中。此操作只能在 $x<n$ 时执行。
2. **向左移动**：从当前索引 $x$ 移动到 $x-1$，并将 $a_{x-1}$ 加到你的得分中。此操作只能在 $x>1$ 时执行。此外，你不能连续执行两次或更多次向左移动。

你需要执行恰好 $k$ 次移动，并且在所有移动中，向左移动的次数不能超过 $z$ 次。求你能获得的最大得分。

#### 说明/提示
- 在第一个测试用例中，你不能向左移动。因此，你只能向右移动四次，得分为 $a_1 + a_2 + a_3 + a_4 + a_5$。
- 在第二个测试用例中，你可以向左移动一次。因此，你可以按照以下步骤移动：右、右、左、右。得分为 $a_1 + a_2 + a_3 + a_2 + a_3$。
- 在第三个测试用例中，你可以向左移动四次，但这并不是最优解。你只需向右移动四次，得分为 $a_1 + a_2 + a_3 + a_4 + a_5$。

#### 样例 #1
##### 输入
```
4
5 4 0
1 5 4 3 2
5 4 1
1 5 4 3 2
5 4 4
10 20 30 40 50
10 7 3
4 6 8 2 9 9 7 4 10 9
```
##### 输出
```
15
19
150
56
```

### 算法分类
动态规划

### 题解分析与结论
本题的核心是通过动态规划来求解在有限步数和有限向左移动次数下的最大得分。大多数题解采用了动态规划的思路，部分题解还结合了贪心策略。以下是各题解的要点和难点对比：

1. **动态规划**：大多数题解使用二维或三维的动态规划数组来记录在不同状态下的最大得分。状态转移方程通常基于当前的位置、已执行的向左移动次数以及上一步的移动方向。
2. **贪心策略**：部分题解通过贪心策略来优化动态规划的过程，例如在向左移动时选择收益最大的位置进行“横跳”。
3. **前缀和优化**：一些题解使用前缀和来快速计算特定区间的得分，从而减少计算量。

### 高星题解推荐
1. **作者：钓鱼王子 (赞：16)**
   - **星级**：5星
   - **关键亮点**：使用了二维动态规划数组，状态转移方程清晰，代码简洁高效。
   - **核心代码**：
     ```cpp
     for(re int i=0;i<=k;++i){
         for(re int j=1;j<=n;++j){
             dp[j][i]=dp[j-1][i]+a[j];
             if(i&&j!=n)dp[j][i]=max(dp[j][i],dp[j+1][i-1]+a[j]);
             if(j-1+i*2==m)ans=max(ans,dp[j][i]);
         }
     }
     ```
   - **实现思想**：通过二维数组 `dp[j][i]` 记录在位置 $j$ 且已向左移动 $i$ 次时的最大得分，状态转移方程考虑了向右和向左移动的情况。

2. **作者：Yizhixiaoyun (赞：11)**
   - **星级**：4星
   - **关键亮点**：结合了贪心策略，通过“横跳”来最大化收益，代码逻辑清晰。
   - **核心代码**：
     ```cpp
     for(register int i=0;i<=min(z,num/2);++i) ans=max(ans,sum[num-i*2]+b[num-i*2]*i);
     ```
   - **实现思想**：通过贪心策略选择最优的“横跳”位置，利用前缀和快速计算得分。

3. **作者：lingfunny (赞：6)**
   - **星级**：4星
   - **关键亮点**：使用了三维动态规划数组，考虑了上一步的移动方向，避免了连续向左移动的情况。
   - **核心代码**：
     ```cpp
     for(int i=1;i<=z;++i)
     for(int j=1;j<=k-i*2+1;++j){
         dp[i][j][1] = dp[i-1][j+1][0]+a[j];
         dp[i][j][0] = max(dp[i][j-1][0]+a[j], dp[i][j-1][1] + a[j]);
     }
     ```
   - **实现思想**：通过三维数组 `dp[i][j][k]` 记录在位置 $j$ 且已向左移动 $i$ 次时的最大得分，状态转移方程考虑了上一步的移动方向。

### 最优关键思路
最优解通常结合了动态规划和贪心策略，通过状态转移方程和前缀和优化来高效求解最大得分。动态规划的状态设计是关键，通常需要考虑当前位置、已执行的向左移动次数以及上一步的移动方向。

### 可拓展之处
本题可以拓展到更复杂的移动规则或更多的限制条件，例如允许连续向左移动但限制总次数，或者引入更多的移动方向（如上下移动）。

### 推荐题目
1. [P1048 采药](https://www.luogu.com.cn/problem/P1048) - 动态规划经典问题，与本题类似。
2. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060) - 动态规划与贪心结合的问题。
3. [P1091 合唱队形](https://www.luogu.com.cn/problem/P1091) - 动态规划与贪心策略的结合。

### 个人心得
- **调试经历**：在实现动态规划时，状态转移方程的设计是关键，需要仔细考虑所有可能的移动情况。
- **踩坑教训**：避免连续向左移动的情况需要在状态转移方程中特别处理，否则会导致错误的结果。
- **顿悟感想**：结合贪心策略可以显著优化动态规划的效率，特别是在选择最优移动路径时。

---
处理用时：47.86秒