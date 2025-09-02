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



# Riding in a Lift

## 题目描述

想象你在一栋有 $n$ 层的大楼中，可以通过电梯在楼层间移动。楼层从下到上编号为 $1$ 到 $n$。你当前在 $a$ 层，$b$ 层是禁止进入的实验室。你要进行 $k$ 次连续的电梯移动，每次移动需满足：若当前在 $x$ 层，选择的下一层 $y$ 必须满足 $|x-y|<|x-b|$ 且 $y \ne x$。求所有可能的移动序列总数模 $10^9+7$ 的结果。

## 样例

### 样例 #1
输入：
```
5 2 4 1
```
输出：
```
2
```

### 样例 #2
输入：
```
5 2 4 2
```
输出：
```
2
```

### 样例 #3
输入：
```
5 3 4 1
```
输出：
```
0
```

---

### 精选题解分析

#### 题解作者：gxy001（★★★★★）
**核心思路**：
1. **坐标转换**：将问题转化为只能在 $b$ 层的一侧移动。若初始位置 $a>b$ 则所有楼层减去 $b$，否则将 $b$ 视为坐标原点，将 $a$ 转换为 $b-a$。
2. **前缀和优化DP**：定义 $f[i][j]$ 表示走 $j$ 步到达 $i$ 层的方案数。利用前缀和数组 $s$ 将转移复杂度从 $O(n^2k)$ 降为 $O(nk)$。
3. **滚动数组**：使用一维数组滚动更新，优化空间复杂度。

**关键代码**：
```cpp
int const mod=1000000007;
long long n,k,a,b,f[5010],s[5010];
if(a>b) n-=b,a-=b; // 坐标转换
else n=b-1,a=b-a;
f[a]=1;
for(int j=1;j<=k;j++){
    // 利用前缀和快速计算区间和
    for(int i=1;i<=n;i++) 
        f[i] = (s[n] - s[i/2] - f[i] + 2*mod) % mod;
    // 更新前缀和数组
    for(int i=1;i<=n;i++) 
        s[i] = (s[i-1] + f[i]) % mod;
}
```

#### 题解作者：zhaozixu2006（★★★★☆）
**核心思路**：
1. **差分优化**：在每层计算可转移的区间 $[l,r)$，通过差分标记区间增减。
2. **区间剔除**：特别处理当前层 $j$ 的剔除，避免停留原地。
3. **前缀和恢复**：最后通过前缀和将差分数组还原为实际计数。

**亮点**：
```cpp
for(int j=1;j<=n;j++){
    int d=abs(j-b), l=max(1,j-d+1), r=min(n+1,j+d);
    // 差分标记区间增加
    dp[i+1][l] = (dp[i+1][l] + dp[i][j]) % mod;
    dp[i+1][r] = (dp[i+1][r] - dp[i][j] + mod) % mod;
    // 剔除j点的影响
    if(l <= j && j < r){
        dp[i+1][j] = (dp[i+1][j] - dp[i][j] + mod) % mod;
        dp[i+1][j+1] = (dp[i+1][j+1] + dp[i][j]) % mod;
    }
}
```

#### 题解作者：XTianShuo（★★★★☆）
**创新点**：
- 不进行坐标转换，直接通过区间计算确定合法转移范围。
- 使用二维差分数组，以当前状态更新未来状态，避免重复计算。

**关键公式**：
$$
l = \max(1, j-d+1),\ r = \min(n, j+d-1)
$$
其中 $d=|j-b|-1$，确保严格满足距离条件。

---

### 关键思路总结
1. **坐标转换**：通过将 $b$ 层转换为边界点，将问题限制在单侧，简化后续计算。
2. **前缀和优化**：将区间求和复杂度从 $O(n)$ 降为 $O(1)$，是优化动态规划转移的常用技巧。
3. **差分标记法**：通过标记区间起点和终点，最后用前缀和恢复结果，适用于需要大量区间更新的场景。
4. **滚动数组**：在状态转移仅依赖前一状态时，使用滚动数组可将空间复杂度从 $O(nk)$ 降为 $O(n)$。

---

### 拓展与相似题目
1. **区间DP优化**：CF266E（区间操作与前缀和结合）
2. **差分技巧**：洛谷P3368（树状数组+差分）
3. **动态规划优化**：洛谷P2285（打鼹鼠，O(n²) DP优化）

### 调试心得
- **坐标转换陷阱**：若未正确处理坐标转换后的边界情况（如新n的计算），会导致数组越界。
- **差分符号处理**：差分减法操作后需立即取模，避免出现负数。
- **严格距离判断**：计算区间端点时需注意开闭区间，如使用 `(i+b-1)/2` 而非 `(i+b)/2` 来确保严格小于条件。

---
处理用时：55.83秒