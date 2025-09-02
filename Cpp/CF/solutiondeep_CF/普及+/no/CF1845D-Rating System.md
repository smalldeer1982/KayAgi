# 题目信息

# Rating System

## 题目描述

You are developing a rating system for an online game. Every time a player participates in a match, the player's rating changes depending on the results.

Initially, the player's rating is $ 0 $ . There are $ n $ matches; after the $ i $ -th match, the rating change is equal to $ a_i $ (the rating increases by $ a_i $ if $ a_i $ is positive, or decreases by $ |a_i| $ if it's negative. There are no zeros in the sequence $ a $ ).

The system has an additional rule: for a fixed integer $ k $ , if a player's rating has reached the value $ k $ , it will never fall below it. Formally, if a player's rating at least $ k $ , and a rating change would make it less than $ k $ , then the rating will decrease to exactly $ k $ .

Your task is to determine the value $ k $ in such a way that the player's rating after all $ n $ matches is the maximum possible (among all integer values of $ k $ ). If there are multiple possible answers, you can print any of them.

## 说明/提示

In the first example, if $ k=3 $ , then the rating changes as follows: $ 0 \rightarrow 3 \rightarrow 3 \rightarrow 4 \rightarrow 6 $ .

In the second example, if $ k=0 $ , then the rating changes as follows: $ 0 \rightarrow 0 \rightarrow 0 \rightarrow 0 $ .

In the third example, if $ k=25 $ , then the rating changes as follows: $ 0 \rightarrow 4 \rightarrow 6 $ .

In the fourth example, if $ k=6 $ , then the rating changes as follows: $ 0 \rightarrow 5 \rightarrow 6 \rightarrow 6 \rightarrow 8 \rightarrow 7 \rightarrow 6 \rightarrow 8 $ .

## 样例 #1

### 输入

```
4
4
3 -2 1 2
3
-1 -2 -1
2
4 2
7
5 1 -3 2 -1 -2 2```

### 输出

```
3
0
25
6```

# AI分析结果

### 题目内容重写（中文）

你正在为一个在线游戏开发一个评分系统。每次玩家参与一场比赛后，玩家的评分会根据比赛结果发生变化。

初始时，玩家的评分为 $0$。共有 $n$ 场比赛；在第 $i$ 场比赛后，评分的变化为 $a_i$（如果 $a_i$ 为正，评分增加 $a_i$；如果 $a_i$ 为负，评分减少 $|a_i|$。序列 $a$ 中没有零）。

系统有一个额外的规则：对于一个固定的整数 $k$，如果玩家的评分达到了 $k$，它将永远不会低于 $k$。形式上，如果玩家的评分至少为 $k$，且评分变化会使它低于 $k$，那么评分将减少到恰好 $k$。

你的任务是确定 $k$ 的值，使得在所有 $n$ 场比赛后，玩家的评分尽可能大（在所有整数 $k$ 中）。如果有多个可能的答案，你可以输出其中任何一个。

### 算法分类
贪心、前缀和

### 题解分析与结论

#### 综合分析与结论
该题的核心在于通过贪心策略和前缀和来最大化玩家的最终评分。大多数题解都利用了前缀和的性质，通过枚举某个位置的前缀和作为 $k$，然后计算后续的评分变化。最优的 $k$ 通常是某个前缀和的最大值，因为它能够有效地防止评分下降。

#### 所选高星题解

1. **作者：Sumikura (赞：24)**  
   **星级：5星**  
   **关键亮点：**  
   - 将问题转化为求最小子段和，思路清晰且高效。
   - 通过前缀和和最小子段和的结合，巧妙地找到了最优的 $k$。
   - 代码简洁，逻辑明确。

   **核心代码：**
   ```cpp
   for(int i(1); i <= n; i++) {
       sum += a[i];
       if(sum > 0) sum = 0, ed = i;
       if(sum < ans) ans = sum, ans1 = ed;
   }
   for(int i(1); i <= ans1; i++) num += a[i];
   cout << num << "\n";
   ```
   **实现思想：**  
   通过遍历数组，计算前缀和，并记录最小子段和的位置。最终，$k$ 即为最小子段和之前的前缀和。

2. **作者：formkiller (赞：13)**  
   **星级：4星**  
   **关键亮点：**  
   - 通过枚举前缀和的最大值作为 $k$，并结合后续的前缀和变化，计算最终评分。
   - 思路清晰，代码可读性强。

   **核心代码：**
   ```cpp
   for(int i = 1; i <= N; ++i) {
       ma = max(ma, sum[i]);
       if(ans < ma + sum[N] - sum[i]) {
           ans = ma + sum[N] - sum[i];
           anss = ma;
       }
   }
   printf("%lld\n", anss);
   ```
   **实现思想：**  
   通过枚举每个位置的前缀和，计算该位置作为 $k$ 时的最终评分，并选择最大值对应的 $k$。

3. **作者：Sanyueyetu (赞：8)**  
   **星级：4星**  
   **关键亮点：**  
   - 通过前缀和和后缀和的结合，找到最优的 $k$。
   - 思路新颖，代码简洁。

   **核心代码：**
   ```cpp
   for(int i = 1; i <= n; i++) {
       qian[i] = qian[i - 1] + a[i];
       sum[i] = maxsum = max(maxsum, qian[i]);
   }
   for(int i = n; i >= 0; i--) {
       hou[i] = hou[i + 1] + a[i];
       if(maxsum < sum[i] + hou[i + 1]) {
           maxsum = sum[i] + hou[i + 1];
           ans = sum[i];
       }
   }
   cout << ans << endl;
   ```
   **实现思想：**  
   通过计算前缀和和后缀和，找到前缀和和后缀和的最大组合，从而确定最优的 $k$。

### 最优关键思路或技巧
1. **前缀和与最小子段和结合：** 通过计算前缀和和最小子段和，可以有效地找到最优的 $k$，从而最大化最终评分。
2. **枚举前缀和的最大值：** 通过枚举前缀和的最大值作为 $k$，并结合后续的前缀和变化，可以快速计算出最终评分。
3. **前缀和与后缀和结合：** 通过计算前缀和和后缀和，找到前缀和和后缀和的最大组合，从而确定最优的 $k$。

### 可拓展之处
1. **类似问题：** 可以扩展到其他需要最大化或最小化某个值的题目，例如股票买卖问题、最大子数组和问题等。
2. **算法套路：** 前缀和与贪心策略的结合在解决类似问题时非常有效，可以广泛应用于各种优化问题。

### 推荐题目
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)
2. [P1216 数字三角形](https://www.luogu.com.cn/problem/P1216)
3. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)

### 个人心得摘录
- **Sumikura：** "通过观察这个式子，我们发现 $sum$ 越小新 Rating 就会越大，这不就是求最小子段和吗？" 这个观察非常关键，直接引导了问题的解决思路。
- **formkiller：** "既然最后的若干次操作摆脱了 $k$ 的限制，我们就枚举这个摆脱限制的起始位置。" 这个思路清晰地解释了如何通过枚举来找到最优解。
- **Sanyueyetu：** "所以我们唯一要做的就是确定一段后缀，以及一段前缀，这两段之间可以像上面的例子中第 $2$ 次到第 $6$ 次之间一样忽略，然后最大化这一段前缀和后缀的和。" 这个思路新颖且有效，通过前缀和和后缀和的结合，找到了最优的 $k$。

---
处理用时：51.50秒