# 题目信息

# Primal Sport

## 题目描述

Alice and Bob begin their day with a quick game. They first choose a starting number $ X_{0}>=3 $ and try to reach one million by the process described below.

Alice goes first and then they take alternating turns. In the $ i $ -th turn, the player whose turn it is selects a prime number smaller than the current number, and announces the smallest multiple of this prime number that is not smaller than the current number.

Formally, he or she selects a prime $ p&lt;X_{i-1} $ and then finds the minimum $ X_{i}>=X_{i-1} $ such that $ p $ divides $ X_{i} $ . Note that if the selected prime $ p $ already divides $ X_{i-1} $ , then the number does not change.

Eve has witnessed the state of the game after two turns. Given $ X_{2} $ , help her determine what is the smallest possible starting number $ X_{0} $ . Note that the players don't necessarily play optimally. You should consider all possible game evolutions.

## 说明/提示

In the first test, the smallest possible starting number is $ X_{0}=6 $ . One possible course of the game is as follows:

- Alice picks prime 5 and announces $ X_{1}=10 $
- Bob picks prime 7 and announces $ X_{2}=14 $ .

In the second case, let $ X_{0}=15 $ .

- Alice picks prime 2 and announces $ X_{1}=16 $
- Bob picks prime 5 and announces $ X_{2}=20 $ .

## 样例 #1

### 输入

```
14
```

### 输出

```
6
```

## 样例 #2

### 输入

```
20
```

### 输出

```
15
```

## 样例 #3

### 输入

```
8192
```

### 输出

```
8191
```

# AI分析结果



# Primal Sport

## 题目描述

Alice 和 Bob 以一场快速游戏开始他们的一天。他们首先选择一个起始数 $X_0 \geq 3$，并通过以下过程尝试达到一百万。

Alice 先手，之后两人交替进行。在第 $i$ 回合，当前玩家选择一个小于当前数的质数 $p$，并宣布该质数的最小倍数且不小于当前数的值。

形式化地，玩家选择一个质数 $p < X_{i-1}$，并找到最小的 $X_i \geq X_{i-1}$ 使得 $p$ 整除 $X_i$。注意，若当前数已能被所选质数整除，则数值不变。

给定 $X_2$，帮助 Eve 确定可能的起始数 $X_0$ 的最小值。玩家不一定采取最优策略，需考虑所有可能的游戏路径。

## 题解对比与分析

### 关键思路总结
1. **逆向推导**：从已知的 $X_2$ 倒推可能的 $X_1$ 和 $X_0$ 的范围。
2. **最大质因数预处理**：利用筛法预处理每个数的最大质因数，快速计算范围边界。
3. **区间枚举**：$X_1$ 的范围为 $[X_2 - p_2 +1, X_2]$，其中 $p_2$ 是 $X_2$ 的最大质因数。对每个 $X_1$，其对应的 $X_0$ 最小值为 $X_1 - p_1 +1$（$p_1$ 为 $X_1$ 的最大质因数）。
4. **剪枝优化**：仅需枚举 $X_1$ 的可能区间，避免无效计算。

### 高星题解推荐

#### 题解1：作者 Blunt_Feeling（4星）
**核心亮点**：  
- 使用埃氏筛预处理最大质因数，代码简洁高效。
- 直接枚举区间并取最小值，逻辑清晰。

**代码核心**：
```cpp
For(i,2,x2)
    if(!a[i])
        for(int j=i*2;j<=x2;j+=i)
            a[j]=i;
int x0=x2;
For(i,x2-a[x2]+1,x2) 
    x0=min(x0,i-a[i]+1);
```

#### 题解2：作者 ModestCoder_（4星）
**核心亮点**：  
- 采用线性筛法预处理最大质因数，时间复杂度更优。
- 利用素数标记数组避免重复判断。

**代码核心**：
```cpp
for (int i = 2; i <= n; ++i){
    if (!flag[i]) prime[++tot] = a[i] = i;
    for (int j = 1; j <= tot && i * prime[j] <= n; ++j){
        flag[i * prime[j]] = 1, a[i * prime[j]] = a[i];
        if (i % prime[j] == 0) break;
    }
}
int ans = n;
for (int i = n - a[n] + 1; i <= n; ++i)
    if (flag[i]) ans = min(ans, i - a[i] + 1);
```

#### 题解3：作者 cbyybccbyybc（4星）
**核心亮点**：  
- 预处理逻辑与 Blunt_Feeling 类似，但代码结构更易读。
- 显式处理合数筛选，避免无效质数计算。

**代码核心**：
```cpp
for(int i=2;i<=n;i++){
    if(mark[i]==false) arr[++cur]=a[i]=i;
    for(int j=1;j<=cur&&i*arr[j]<=n;j++){
        mark[i*arr[j]]=true;
        a[i*arr[j]]=a[i];
        if(i%arr[j]==0) break;
    }
}
int ans=n;
for(int i=n-a[n]+1;i<=n;i++)
    if(mark[i]) 
        ans=min(ans,i-a[i]+1);
```

### 最优技巧提炼
- **最大质因数预处理**：通过筛法预处理每个数的最大质因数，将时间复杂度优化至线性。
- **逆向区间推导**：利用数学关系确定区间边界，避免穷举所有可能。
- **剪枝策略**：仅处理有效区间内的数，减少无效计算。

### 拓展建议
- **同类问题**：涉及质因数分解、逆向推导的最值问题（如 CF1228C、CF1107E）。
- **筛法变种**：练习使用不同筛法处理质因数相关属性（如最小质因数、质因数个数等）。

### 推荐练习题
1. [CF1107E - Vasya and Binary String](https://codeforces.com/problemset/problem/1107/E)（逆向动态规划）
2. [CF1228C - Primes and Multiplication](https://codeforces.com/problemset/problem/1228/C)（质因数分解与贡献计算）
3. [P1072 Hankson 的趣味题](https://www.luogu.com.cn/problem/P1072)（质因数分解与约束条件）

---
处理用时：175.11秒