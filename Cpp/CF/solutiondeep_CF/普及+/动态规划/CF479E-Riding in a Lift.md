# 题目信息

# Riding in a Lift

## 题目描述

Imagine that you are in a building that has exactly $ n $ floors. You can move between the floors in a lift. Let's number the floors from bottom to top with integers from $ 1 $ to $ n $ . Now you're on the floor number $ a $ . You are very bored, so you want to take the lift. Floor number $ b $ has a secret lab, the entry is forbidden. However, you already are in the mood and decide to make $ k $ consecutive trips in the lift.

Let us suppose that at the moment you are on the floor number $ x $ (initially, you were on floor $ a $ ). For another trip between floors you choose some floor with number $ y $ ( $ y≠x $ ) and the lift travels to this floor. As you cannot visit floor $ b $ with the secret lab, you decided that the distance from the current floor $ x $ to the chosen $ y $ must be strictly less than the distance from the current floor $ x $ to floor $ b $ with the secret lab. Formally, it means that the following inequation must fulfill: $ |x-y|<|x-b| $ . After the lift successfully transports you to floor $ y $ , you write down number $ y $ in your notepad.

Your task is to find the number of distinct number sequences that you could have written in the notebook as the result of $ k $ trips in the lift. As the sought number of trips can be rather large, find the remainder after dividing the number by $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

Imagine that you are in a building that has exactly $ n $ floors. You can move between the floors in a lift. Let's number the floors from bottom to top with integers from $ 1 $ to $ n $ . Now you're on the floor number $ a $ . You are very bored, so you want to take the lift. Floor number $ b $ has a secret lab, the entry is forbidden. However, you already are in the mood and decide to make $ k $ consecutive trips in the lift.

Let us suppose that at the moment you are on the floor number $ x $ (initially, you were on floor $ a $ ). For another trip between floors you choose some floor with number $ y $ ( $ y≠x $ ) and the lift travels to this floor. As you cannot visit floor $ b $ with the secret lab, you decided that the distance from the current floor $ x $ to the chosen $ y $ must be strictly less than the distance from the current floor $ x $ to floor $ b $ with the secret lab. Formally, it means that the following inequation must fulfill: $ |x-y|<|x-b| $ . After the lift successfully transports you to floor $ y $ , you write down number $ y $ in your notepad.

Your task is to find the number of distinct number sequences that you could have written in the notebook as the result of $ k $ trips in the lift. As the sought number of trips can be rather large, find the remainder after dividing the number by $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 样例 #1

### 输入

```
5 2 4 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5 2 4 2
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5 3 4 1
```

### 输出

```
0
```

# AI分析结果

### 题目内容重写

#### 题目描述

想象你在一栋有 $n$ 层的大楼中。你可以通过电梯在楼层之间移动。楼层从下到上依次编号为 $1$ 到 $n$。现在你位于第 $a$ 层。你感到非常无聊，决定乘坐电梯。第 $b$ 层有一个秘密实验室，禁止进入。然而，你已经决定要进行 $k$ 次连续的电梯旅行。

假设你现在位于第 $x$ 层（初始时你在第 $a$ 层）。对于下一次旅行，你选择某个楼层 $y$（$y \neq x$），电梯将前往该楼层。由于你不能进入第 $b$ 层的秘密实验室，你决定从当前楼层 $x$ 到所选楼层 $y$ 的距离必须严格小于从当前楼层 $x$ 到第 $b$ 层的距离。形式上，必须满足以下不等式：$|x - y| < |x - b|$。电梯成功将你运送到第 $y$ 层后，你将数字 $y$ 记录在笔记本中。

你的任务是找出在 $k$ 次电梯旅行后，笔记本中可能记录的不同数字序列的数量。由于旅行次数可能非常大，请将结果对 $1000000007$（$10^9 + 7$）取模。

#### 样例 #1

##### 输入
```
5 2 4 1
```

##### 输出
```
2
```

#### 样例 #2

##### 输入
```
5 2 4 2
```

##### 输出
```
2
```

#### 样例 #3

##### 输入
```
5 3 4 1
```

##### 输出
```
0
```

---

### 题解综合分析与结论

本题的核心是通过动态规划（DP）来计算在 $k$ 次电梯旅行后可能记录的不同数字序列的数量。由于直接暴力枚举的复杂度较高，题解中普遍采用了前缀和优化或差分优化来降低时间复杂度。

#### 关键思路与技巧
1. **动态规划**：定义状态 $f_{i,j}$ 表示在第 $i$ 层，进行了 $j$ 次旅行的方案数。
2. **前缀和优化**：通过维护前缀和数组，快速计算区间和，避免重复计算。
3. **差分优化**：利用差分数组来优化区间更新操作，进一步降低时间复杂度。
4. **滚动数组**：由于状态转移只依赖于前一次的状态，可以使用滚动数组来优化空间复杂度。

#### 推荐题解

1. **作者：gxy001 (★★★★★)**
   - **关键亮点**：使用前缀和优化，详细解释了状态转移方程，并通过滚动数组优化空间复杂度。
   - **代码核心**：
     ```cpp
     for(int i=1;i<=k;i++){
         for(int j=1;j<=n;j++) f[j]=(s[n]-s[j>>1]-f[j]+mod+mod)%mod;
         for(int j=1;j<=n;j++) s[j]=(s[j-1]+f[j])%mod;
     }
     ```
   - **个人心得**：通过将 $b$ 层视为 $0$ 层，简化了计算过程。

2. **作者：zhaozixu2006 (★★★★☆)**
   - **关键亮点**：使用差分优化，详细解释了如何通过差分数组来优化区间更新操作。
   - **代码核心**：
     ```cpp
     for(int i=0;i<=k;i++){
         for(int j=1;j<=n;j++){
             if(j==b) continue;
             int dis = abs(j - b);
             int l = max(1, j - dis + 1);
             int r = min(n + 1, j + dis);
             dp[i + 1][l] = (dp[i + 1][l] + dp[i][j]) % mod;
             dp[i + 1][r] = (dp[i + 1][r] - dp[i][j] + mod) % mod;
         }
     }
     ```
   - **个人心得**：通过差分数组优化了区间更新操作，减少了时间复杂度。

3. **作者：Crab_Dave (★★★★☆)**
   - **关键亮点**：通过前缀和优化，详细解释了如何通过前缀和数组快速计算区间和。
   - **代码核心**：
     ```cpp
     for(int K=1;K<=kkk;K++){
         for(int i=1;i<b;i++)
             mo(sum[i][K-1]=sum[i-1][K-1]+dp[i][K-1]);
         for(int i=1;i<b;i++){
             mo(dp[i][K]+=sum[i-1][K-1]);
             mo(dp[i][K]+=(sum[(i+b-1)/2][K-1]-sum[i][K-1]+mod)%mod);
         }
     }
     ```
   - **个人心得**：通过前缀和数组优化了区间和的计算，减少了时间复杂度。

---

### 推荐题目
1. **洛谷 P1048 采药**：考察动态规划与背包问题。
2. **洛谷 P1060 开心的金明**：考察动态规划与背包问题。
3. **洛谷 P1091 合唱队形**：考察动态规划与区间优化。

---

### 总结
本题的核心在于通过动态规划结合前缀和或差分优化来高效计算方案数。前缀和优化和差分优化是常见的降低时间复杂度的方法，尤其在涉及区间和或区间更新的问题时非常有效。通过滚动数组可以进一步优化空间复杂度，适合处理大规模数据。

---
处理用时：40.57秒