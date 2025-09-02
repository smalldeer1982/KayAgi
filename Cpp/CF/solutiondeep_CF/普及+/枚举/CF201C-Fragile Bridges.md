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

### 题目重写
# 脆弱的桥梁

## 题目描述
你正在玩一款电子游戏，刚刚进入奖励关卡，此关卡的唯一目标是尽可能多地得分。作为一个完美主义者，你决定在获得该关卡的最高分之前不离开。

奖励关卡由排成一行的 $n$ 个小平台组成，从左到右编号为 $1$ 到 $n$，以及 $(n - 1)$ 座连接相邻平台的桥梁。平台之间的桥梁非常脆弱，对于每座桥，事先已知从其一端走到另一端，在它永远坍塌之前可以通过的次数。

玩家的操作如下。首先，他选择其中一个平台作为英雄的起始位置。之后，玩家可以通过未损坏的桥梁自由地在平台间移动英雄。一旦英雄发现自己所在的平台没有连接未损坏的桥梁，关卡自动结束。玩家在关卡结束时获得的分数计算为英雄在平台间移动的次数。请注意，如果英雄开始通过某座桥移动，他必须继续沿同一方向移动，直到到达一个平台。

找出你需要获得多少分，才能确保没有人能打破你的记录，从而安心进入下一关。

## 说明/提示
在样例中获得 5 分的一种可能是从平台 3 开始，依次移动到平台 4、3、2、1 和 2。之后，唯一未损坏的桥是平台 4 和 5 之间的桥，但这座桥离英雄当前所在的平台 2 太远了。

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

### 综合分析与结论
这些题解主要思路都是通过动态规划（DP）来解决问题，差异在于状态定义和转移方程的推导。
1. **思路**：多数题解将路线拆分为向左、向右的单向路径分别处理，通过DP计算不同条件下的最大得分，最后合并答案。部分题解考虑最终路径形态，利用前缀和等优化计算。
2. **算法要点**：定义合适的DP状态，如从某点向左/右走，保证或不保证回到该点的最大分数；根据桥的通过次数奇偶性和能否返回等条件推导状态转移方程。
3. **解决难点**：难点在于合理定义DP状态以准确描述问题，以及根据桥的通过次数特性（奇偶性、能否走满次数）推导复杂的状态转移方程。

### 所选的题解
- **作者：pythoner713 (赞：3)  星级：5星**
    - **关键亮点**：思路清晰，详细阐述状态定义及转移方程推导过程，结合图片辅助理解，代码简洁明了。
    - **个人心得**：无
    - **重点代码及核心思想**：
```cpp
// 核心代码为DP过程
for(int i = 2; i <= n; i++){
    if(a[i - 1] > 1) f[i][1] = f[i - 1][1] + a[i - 1] / 2 * 2;
    f[i][0] = max(f[i][1], f[i - 1][0] + a[i - 1] -!(a[i - 1] & 1));
    f[i][0] = max(f[i][0], f[i - 1][1] + a[i - 1]);
}
for(int i = n - 1; i; i--){
    if(a[i] > 1) g[i][1] = g[i + 1][1] + a[i] / 2 * 2;
    g[i][0] = max(g[i][1], g[i + 1][0] + a[i] -!(a[i] & 1));
    g[i][0] = max(g[i][0], g[i + 1][1] + a[i]);
}
// 计算最终答案
for(int i = 1; i <= n; i++){
    ans = max(ans, max(f[i][0] + g[i][1], f[i][1] + g[i][0]));
}
```
核心思想是先分别通过正向和反向的循环计算从每个点向左、向右走的不同状态下的最大得分，最后遍历每个点，取两种组合方式（先左后右、先右后左）得分的最大值作为最终答案。

- **作者：Wf_yjqd (赞：2)  星级：4星**
    - **关键亮点**：从最终路径形态出发，提出维护多个数组表示不同方向和通过次数条件下的最大答案，利用前缀和优化复杂度。
    - **个人心得**：无
    - **重点代码及核心思想**：
```cpp
// 计算tl数组（从x出发向左每个桥经过偶数次的最大答案）
for(ll i = 2; i <= n; i++)
    tl[i]=(a[i - 1]>1?tl[i - 1]:0)+se(a[i - 1]);
// 计算tr数组（从x出发向右每个桥经过偶数次的最大答案）
for(ll i = n; i >= 1; i--)
    tr[i]=(a[i]>1?tr[i + 1]:0)+se(a[i]);
// 计算qzdis数组（1到x每个桥经过奇数次的最大答案）
for(ll i = 1; i <= n; i++)
    qzdis[i]=qzdis[i - 1]+se(a[i]+1)-1;
maxl = tl[1];
ans = tl[1]+tr[1];
// 枚举j，更新答案
for(ll i = 2; i <= n + 1; i++){
    maxl = max(maxl, tl[i]-qzdis[i - 1]);
    ans = max(ans, tr[i]+qzdis[i - 1]+maxl);
}
```
核心思想是先通过三次循环分别计算出向左、向右经过偶数次桥的最大得分数组以及经过奇数次桥的前缀和数组，然后在枚举过程中，通过记录前缀最大的 $l_i - qzdis_i$ 来更新最终答案。

- **作者：Liynw (赞：0)  星级：4星**
    - **关键亮点**：详细讲述思路来源，从错误解法逐步引导出正解，对DP状态定义和转移方程解释细致，提示注意下标含义。
    - **个人心得**：从错误的暴搜及优化思路中，发现问题所在，进而明确与离开后是否回来有关，从而确定正解思路。
    - **重点代码及核心思想**：
```cpp
// 正向DP计算往左走的情况
for(int i = 2; i <= n - 1; i++){
    dp[i][0]=max(dp[i - 1][0],dp[i - 1][1])+((a[i - 1]&1)?a[i - 1]:(a[i - 1]-1));
    if(a[i - 1]>1) dp[i][1]=dp[i - 1][1]+((a[i - 1]&1)?(a[i - 1]-1):a[i - 1]); 
}
// 反向DP计算往右走的情况
for(int i = n; i; i--){
    dp[i][2]=max(dp[i + 1][2],dp[i + 1][3])+((a[i]&1)?a[i]:(a[i - 1]-1));
    if(a[i]>1) dp[i][3]=dp[i + 1][3]+((a[i]&1)?(a[i]-1):a[i]);
}
// 计算最终答案
for(int i = 1; i <= n; i++) ans=max(ans,max(dp[i][0]+dp[i][3],dp[i][1]+dp[i][2]));
```
核心思想是先正向循环计算从每个点往左走，不回来和回来两种情况下的最大得分，再反向循环计算往右走的同样两种情况的最大得分，最后遍历每个点，取两种组合方式得分的最大值作为最终答案。

### 最优关键思路或技巧
将不定路线问题拆分为向左、向右的单向路径问题，通过合理定义DP状态（考虑是否回到起点），根据桥通过次数的奇偶性等特性推导状态转移方程，利用线性DP求解。

### 可拓展思路
同类型题通常涉及路径规划与限制条件下的最优解问题，类似算法套路是根据问题特点合理定义DP状态，结合限制条件推导状态转移方程。例如在一些网格行走、管道连接等场景中，根据行走规则和资源限制来设计DP解法。

### 推荐洛谷题目
1. [P1233 木棍加工](https://www.luogu.com.cn/problem/P1233)：涉及对物品属性的处理和动态规划，与本题处理桥的通过次数类似，需合理定义状态和转移方程。
2. [P1880 [NOI1995] 石子合并](https://www.luogu.com.cn/problem/P1880)：区间DP问题，通过划分区间来确定状态转移，与本题将路线拆分处理的思维类似。
3. [P3951 小凯的疑惑](https://www.luogu.com.cn/problem/P3951)：数论与动态规划结合，通过分析数字关系确定状态和转移，锻炼从条件中提取关键信息构建DP的能力。 

---
处理用时：38.72秒