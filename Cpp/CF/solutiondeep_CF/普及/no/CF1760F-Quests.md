# 题目信息

# Quests

## 题目描述

There are $ n $ quests. If you complete the $ i $ -th quest, you will gain $ a_i $ coins. You can only complete at most one quest per day. However, once you complete a quest, you cannot do the same quest again for $ k $ days. (For example, if $ k=2 $ and you do quest $ 1 $ on day $ 1 $ , then you cannot do it on day $ 2 $ or $ 3 $ , but you can do it again on day $ 4 $ .)

You are given two integers $ c $ and $ d $ . Find the maximum value of $ k $ such that you can gain at least $ c $ coins over $ d $ days. If no such $ k $ exists, output Impossible. If $ k $ can be arbitrarily large, output Infinity.

## 说明/提示

In the first test case, one way to earn $ 5 $ coins over $ 4 $ days with $ k=2 $ is as follows:

- Day 1: do quest 2, and earn $ 2 $ coins.
- Day 2: do quest 1, and earn $ 1 $ coin.
- Day 3: do nothing.
- Day 4: do quest 2, and earn $ 2 $ coins.

 In total, we earned $ 2+1+2=5 $ coins.In the second test case, we can make over $ 20 $ coins on the first day itself by doing the first quest to earn $ 100 $ coins, so the value of $ k $ can be arbitrarily large, since we never need to do another quest.

In the third test case, no matter what we do, we can't earn $ 100 $ coins over $ 3 $ days.

## 样例 #1

### 输入

```
6
2 5 4
1 2
2 20 10
100 10
3 100 3
7 2 6
4 20 3
4 5 6 7
4 100000000000 2022
8217734 927368 26389746 627896974
2 20 4
5 1```

### 输出

```
2
Infinity
Impossible
1
12
0```

# AI分析结果

【题目内容】
# 任务

## 题目描述

有 $ n $ 个任务。如果你完成第 $ i $ 个任务，你将获得 $ a_i $ 个金币。你每天最多只能完成一个任务。然而，一旦你完成了一个任务，你在接下来的 $ k $ 天内不能再完成同一个任务。（例如，如果 $ k=2 $ 并且你在第 $ 1 $ 天完成了任务 $ 1 $，那么你在第 $ 2 $ 天和第 $ 3 $ 天不能再次完成它，但在第 $ 4 $ 天可以再次完成。）

给你两个整数 $ c $ 和 $ d $。找到最大的 $ k $，使得你可以在 $ d $ 天内获得至少 $ c $ 个金币。如果不存在这样的 $ k $，输出 Impossible。如果 $ k $ 可以无限大，输出 Infinity。

## 说明/提示

在第一个测试用例中，一种在 $ 4 $ 天内获得 $ 5 $ 个金币且 $ k=2 $ 的方法如下：

- 第 1 天：完成任务 2，获得 $ 2 $ 个金币。
- 第 2 天：完成任务 1，获得 $ 1 $ 个金币。
- 第 3 天：什么都不做。
- 第 4 天：再次完成任务 2，获得 $ 2 $ 个金币。

总共获得了 $ 2+1+2=5 $ 个金币。在第二个测试用例中，我们可以在第一天完成任务 1，获得 $ 100 $ 个金币，因此 $ k $ 可以无限大，因为我们不需要再完成其他任务。

在第三个测试用例中，无论我们做什么，都无法在 $ 3 $ 天内获得 $ 100 $ 个金币。

## 样例 #1

### 输入

```
6
2 5 4
1 2
2 20 10
100 10
3 100 3
7 2 6
4 20 3
4 5 6 7
4 100000000000 2022
8217734 927368 26389746 627896974
2 20 4
5 1```

### 输出

```
2
Infinity
Impossible
1
12
0```

【算法分类】贪心

【题解分析与结论】
本题的核心在于通过贪心策略找到最大的 $k$，使得在 $d$ 天内能够获得至少 $c$ 个金币。大多数题解采用了贪心+二分的思路，首先对任务按金币数从大到小排序，然后通过二分法枚举 $k$，判断在给定的 $k$ 下是否能够满足条件。部分题解还通过前缀和优化了计算过程。

【精选题解】
1. **作者：liujy_**（★★★★★）
   - **关键亮点**：清晰的二分思路，结合贪心策略，代码简洁高效。
   - **核心代码**：
     ```cpp
     bool check(int k){
         int sum=s[min(n,k+1)]*(d/(k+1));
         sum+=s[min(n,d%(k+1))];
         return sum>=c;
     }
     ```
   - **个人心得**：通过二分法快速找到最大的 $k$，结合贪心策略确保每次选择最优任务。

2. **作者：cjh20090318**（★★★★☆）
   - **关键亮点**：详细的贪心分析，枚举 $k$ 的思路清晰，代码结构合理。
   - **核心代码**：
     ```cpp
     for(k=d-1;k>=0;k--){
         int x=d%(k+1);
         if(b[min(n,x)]+d/(k+1)*b[min(n,k+1)]>=c){
             printf("%d\n",k);
             return;
         }
     }
     ```
   - **个人心得**：通过枚举 $k$ 的方式，确保找到最大的 $k$，结合前缀和优化计算。

3. **作者：ZBH_123**（★★★★☆）
   - **关键亮点**：二分答案结合贪心策略，代码简洁，逻辑清晰。
   - **核心代码**：
     ```cpp
     bool check(int x){
         int len=x+1;
         long long money=d/len*sum[min(n,len)]+sum[min(d%len,n)];
         return money>=c;
     }
     ```
   - **个人心得**：通过二分法快速找到最大的 $k$，结合贪心策略确保每次选择最优任务。

【最优关键思路】
1. **贪心策略**：将任务按金币数从大到小排序，确保每次选择最优任务。
2. **二分法**：通过二分法快速找到最大的 $k$，减少枚举次数。
3. **前缀和优化**：通过前缀和快速计算每个周期内的金币总数，优化计算效率。

【拓展思路】
类似的问题可以通过贪心+二分的方式解决，尤其是在需要找到某个参数的最大值或最小值时。例如，在资源分配、任务调度等问题中，贪心策略结合二分法可以有效地找到最优解。

【推荐题目】
1. P1083 [NOIP2012 提高组] 借教室（二分+差分）
2. P1316 丢瓶盖（二分+贪心）
3. P2678 跳石头（二分+贪心）

---
处理用时：38.15秒