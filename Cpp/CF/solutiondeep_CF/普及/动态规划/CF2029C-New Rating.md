# 题目信息

# New Rating

## 题目描述

Hello, Codeforces Forcescode!





Kevin used to be a participant of Codeforces. Recently, the KDOI Team has developed a new Online Judge called Forcescode.

Kevin has participated in $ n $ contests on Forcescode. In the $ i $ -th contest, his performance rating is $ a_i $ .

Now he has hacked into the backend of Forcescode and will select an interval $ [l,r] $ ( $ 1\le l\le r\le n $ ), then skip all of the contests in this interval. After that, his rating will be recalculated in the following way:

- Initially, his rating is $ x=0 $ ;
- For each $ 1\le i\le n $ , after the $ i $ -th contest, 
  - If $ l\le i\le r $ , this contest will be skipped, and the rating will remain unchanged;
  - Otherwise, his rating will be updated according to the following rules: 
      - If $ a_i>x $ , his rating $ x $ will increase by $ 1 $ ;
      - If $ a_i=x $ , his rating $ x $ will remain unchanged;
      - If $ a_i<x $ , his rating $ x $ will decrease by $ 1 $ .

You have to help Kevin to find his maximum possible rating after the recalculation if he chooses the interval $ [l,r] $ optimally. Note that Kevin has to skip at least one contest.

## 说明/提示

In the first test case, Kevin must skip at least one contest. If he chooses any interval of length $ 1 $ , his rating after the recalculation will be equal to $ 5 $ .

In the second test case, Kevin's optimal choice is to select the interval $ [3,5] $ . During the recalculation, his rating changes as follows:

 $ $$$ 0 \xrightarrow{a_1=1} 1 \xrightarrow{a_2=2} 2 \xrightarrow{\mathtt{skip}} 2 \xrightarrow{\mathtt{skip}} 2 \xrightarrow{\mathtt{skip}} 2 \xrightarrow{a_6=3} 3 \xrightarrow{a_7=4} 4  $ $ </p><p>In the third test case, Kevin must skip the only contest, so his rating will remain at the initial value of  $ 0 $ .</p><p>In the fourth test case, Kevin's optimal choice is to select the interval  $ \[7,9\] $ . During the recalculation, his rating changes as follows:</p><p> $ $  0 \xrightarrow{a_1=9} 1 \xrightarrow{a_2=9} 2 \xrightarrow{a_3=8} 3 \xrightarrow{a_4=2} 2 \xrightarrow{a_5=4} 3 \xrightarrow{a_6=4} 4 \xrightarrow{\mathtt{skip}} 4 \xrightarrow{\mathtt{skip}} 4 \xrightarrow{\mathtt{skip}} 4  $ $ </p><p>In the fifth test case, Kevin's optimal choice is to select the interval  $ \[5,9\]$$$.

## 样例 #1

### 输入

```
5
6
1 2 3 4 5 6
7
1 2 1 1 1 3 4
1
1
9
9 9 8 2 4 4 3 5 3
10
1 2 3 4 1 3 2 1 1 10```

### 输出

```
5
4
0
4
5```

# AI分析结果

### 题目内容重写
Kevin 曾经是 Codeforces 的参赛者。最近，KDOI 团队开发了一个新的在线评测平台叫做 Forcescode。Kevin 在 Forcescode 上参加了 $n$ 场比赛，第 $i$ 场比赛的表现评分为 $a_i$。现在他黑进了 Forcescode 的后台，准备选择一个区间 $[l,r]$（$1 \le l \le r \le n$），跳过这个区间内的所有比赛。跳过之后，他的评分将按照以下规则重新计算：

- 初始评分为 $x=0$；
- 对于每场比赛 $1 \le i \le n$：
  - 如果 $l \le i \le r$，则跳过这场比赛，评分不变；
  - 否则，评分将根据以下规则更新：
    - 如果 $a_i > x$，评分 $x$ 增加 $1$；
    - 如果 $a_i = x$，评分 $x$ 不变；
    - 如果 $a_i < x$，评分 $x$ 减少 $1$。

你需要帮助 Kevin 找到他选择最优区间 $[l,r]$ 后可能得到的最大评分。注意，Kevin 必须至少跳过一场比赛。

### 题解分析与结论
本题的核心在于如何通过跳过一段连续的比赛区间，使得最终的评分最大化。由于跳过区间会影响评分的计算，因此需要找到最优的跳过区间。多个题解采用了动态规划（DP）的思路，通过状态转移来计算不同情况下的最大评分。

### 高星题解推荐

#### 题解1：作者：chen_z (赞：3)
- **星级**：4星
- **关键亮点**：使用动态规划，通过两个状态 $dp_{i,0}$ 和 $dp_{i,1}$ 分别表示未跳过和已跳过的情况，优化了时间复杂度。
- **核心代码**：
```cpp
for(int i=1;i<=n;i++){
    if(i>1)maxn=max(maxn,dp[i-2][0]);
    if(a[i]>dp[i-1][0])dp[i][0]=dp[i-1][0]+1;
    else if(a[i]==dp[i-1][0])dp[i][0]=dp[i-1][0];
    else dp[i][0]=dp[i-1][0]-1;
    if(a[i]>dp[i-1][1])dp[i][1]=dp[i-1][1]+1;
    else if(a[i]==dp[i-1][1])dp[i][1]=dp[i-1][1];
    else dp[i][1]=dp[i-1][1]-1;
    if(a[i]>maxn)dp[i][1]=max(dp[i][1],maxn+1);
    else if(a[i]==maxn)dp[i][1]=max(dp[i][1],maxn);
    else dp[i][1]=max(dp[i][1],maxn-1);
}
```
- **核心思想**：通过维护两个 DP 状态，分别表示未跳过和已跳过的情况，并在转移时选择最优解。

#### 题解2：作者：TianTianChaoFang (赞：2)
- **星级**：4星
- **关键亮点**：通过二分查找优化了转移过程，将时间复杂度降低到 $O(n \log n)$。
- **核心代码**：
```cpp
for(int i=2;i<=n;i++){
    int pre = query(a[i]);
    int l = 0, r = a[i] + 1;
    while(l + 1 != r){
        int mid = (l + r) >> 1;
        if(query(mid) < pre)l = mid;
        else r = mid;
    }
    dp[i][0] = r;
    add(dp[i-1][1] + 1, 1);
}
```
- **核心思想**：使用二分查找来优化转移过程，确保每次转移都能找到最优的前置状态。

#### 题解3：作者：Super_Cube (赞：2)
- **星级**：4星
- **关键亮点**：通过三个状态 $dp_{i,0/1/2}$ 分别表示未跳过、正在跳过和已跳过的情况，简化了状态转移。
- **核心代码**：
```cpp
for(int i=1;i<=n;++i){
    dp[i][0]=calc(dp[i-1][0],a[i]);
    dp[i][1]=std::max(dp[i-1][0],dp[i-1][1]);
    dp[i][2]=std::max(calc(dp[i-1][1],a[i]),calc(dp[i-1][2],a[i]));
}
```
- **核心思想**：通过三个状态的 DP 转移，简化了问题的复杂度，并确保了最优解的正确性。

### 最优关键思路
1. **动态规划**：通过 DP 状态转移来计算不同情况下的最大评分，是解决本题的核心思路。
2. **二分查找优化**：在转移过程中使用二分查找来优化时间复杂度，确保每次转移都能找到最优的前置状态。
3. **状态简化**：通过多个 DP 状态分别表示未跳过、正在跳过和已跳过的情况，简化了问题的复杂度。

### 可拓展之处
本题的 DP 思路可以拓展到其他类似的区间选择问题，尤其是涉及到区间跳过或区间合并的题目。类似的题目可以通过维护多个状态来简化问题。

### 推荐题目
1. [P1880 [NOI1995] 石子合并](https://www.luogu.com.cn/problem/P1880)
2. [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040)
3. [P1063 能量项链](https://www.luogu.com.cn/problem/P1063)

### 个人心得摘录
- **调试经历**：在实现 DP 转移时，确保每个状态的转移条件正确，避免遗漏或错误。
- **踩坑教训**：在二分查找优化时，注意边界条件的处理，避免出现死循环或错误结果。
- **顿悟感想**：通过多个 DP 状态的维护，可以大大简化问题的复杂度，提高代码的可读性和效率。

---
处理用时：41.44秒