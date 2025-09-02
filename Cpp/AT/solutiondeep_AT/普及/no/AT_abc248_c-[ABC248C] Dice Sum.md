# 题目信息

# [ABC248C] Dice Sum

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc248/tasks/abc248_c

長さ $ N $ の整数からなる数列 $ A=(A_1,\ldots,A_N) $ であって、以下の条件を全て満たすものは何通りありますか？

- $ 1\le\ A_i\ \le\ M $ $ (1\ \le\ i\ \le\ N) $
- $ \displaystyle\sum\ _{i=1}^N\ A_i\ \leq\ K $

ただし、答えは非常に大きくなることがあるので、答えを $ 998244353 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N,\ M\ \leq\ 50 $
- $ N\ \leq\ K\ \leq\ NM $
- 入力は全て整数

### Sample Explanation 1

条件を満たす数列は以下の $ 6 $ つです。 - $ (1,1) $ - $ (1,2) $ - $ (1,3) $ - $ (2,1) $ - $ (2,2) $ - $ (3,1) $

### Sample Explanation 2

答えを $ 998244353 $ で割った余りを出力してください。

## 样例 #1

### 输入

```
2 3 4```

### 输出

```
6```

## 样例 #2

### 输入

```
31 41 592```

### 输出

```
798416518```

# AI分析结果



【中文题目重写】

# [ABC248C] Dice Sum

## 题目描述

构造一个长度为 $ N $ 的整数序列 $ A=(A_1,\ldots,A_N) $，满足以下所有条件：

- $ 1\le\ A_i\ \le\ M $ $ (1\ \le\ i\ \le\ N) $
- $ \displaystyle\sum\ _{i=1}^N\ A_i\ \leq\ K $

求满足条件的方案数，结果对 $ 998244353 $ 取模。

## 说明/提示

### 制約

- $ 1\ \leq\ N,\ M\ \leq\ 50 $
- $ N\ \leq\ K\ \leq\ NM $
- 输入均为整数

### 样例解释 1

符合条件的数列共 $ 6 $ 个：  
- $ (1,1) $  
- $ (1,2) $  
- $ (1,3) $  
- $ (2,1) $  
- $ (2,2) $  
- $ (3,1) $

### 样例解释 2

注意输出结果对 $ 998244353 $ 取模后的值。

---

**【算法分类】**  
动态规划

**【题解分析与结论】**  
本题核心是动态规划结合前缀和优化。关键点在于：

1. **状态设计**：定义 `dp[i][j]` 表示前 `i` 个数的和为 `j` 的方案数。
2. **转移优化**：利用前缀和数组将原本 $O(NMK)$ 的时间复杂度优化至 $O(NK)$。
3. **边界处理**：初始状态 `dp[0][0] = 1`，确保空序列的和为0的方案唯一。

**【最优题解选录】**

⭐️⭐️⭐️⭐️⭐️ **动态规划+前缀和优化**  
- **关键思路**：通过前缀和数组快速计算区间和，避免重复计算。
- **代码亮点**：简洁高效，利用取模避免溢出。
- **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353;

int main() {
    int N, M, K;
    cin >> N >> M >> K;
    vector<vector<int>> dp(N+1, vector<int>(K+1, 0));
    dp[0][0] = 1;
    
    for (int i = 1; i <= N; ++i) {
        vector<int> prefix(K+1, 0);
        prefix[0] = dp[i-1][0];
        for (int j = 1; j <= K; ++j) 
            prefix[j] = (prefix[j-1] + dp[i-1][j]) % MOD;
        
        for (int j = 1; j <= K; ++j) {
            int l = max(0, j - M);
            int r = j - 1;
            if (l > r) continue;
            int sum = (prefix[r] - (l > 0 ? prefix[l-1] : 0) + MOD) % MOD;
            dp[i][j] = sum;
        }
    }
    
    int ans = 0;
    for (int j = 0; j <= K; ++j) 
        ans = (ans + dp[N][j]) % MOD;
    cout << ans << endl;
}
```

**【关键技巧】**  
- **前缀和优化**：在动态规划中，若当前状态的转移需要累加前驱状态的某个区间和，可以预处理前缀和数组来加速。
- **负数取模处理**：减法取模时，先加模数再取模，避免负数。

**【拓展训练】**  
相似动态规划+前缀和优化题目：  
1. [P2513 逆序对统计](https://www.luogu.com.cn/problem/P2513)  
2. [P4095 股票交易](https://www.luogu.com.cn/problem/P4095)  
3. [P6567 买表（加强版）](https://www.luogu.com.cn/problem/P6567)

---
处理用时：183.90秒