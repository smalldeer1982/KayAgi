# 题目信息

# Trails (Easy)

## 题目描述

Harry Potter is hiking in the Alps surrounding Lake Geneva. In this area there are $ m $ cabins, numbered 1 to $ m $ . Each cabin is connected, with one or more trails, to a central meeting point next to the lake. Each trail is either short or long. Cabin $ i $ is connected with $ s_i $ short trails and $ l_i $ long trails to the lake.

Each day, Harry walks a trail from the cabin where he currently is to Lake Geneva, and then from there he walks a trail to any of the $ m $ cabins (including the one he started in). However, as he has to finish the hike in a day, at least one of the two trails has to be short.

How many possible combinations of trails can Harry take if he starts in cabin 1 and walks for $ n $ days?

Give the answer modulo $ 10^9 + 7 $ .

## 样例 #1

### 输入

```
3 2
1 0 1
0 1 1```

### 输出

```
18```

# AI分析结果

### 题目内容重写

Harry Potter 正在日内瓦湖周围的阿尔卑斯山中徒步旅行。该区域有 $m$ 个小屋，编号为 1 到 $m$。每个小屋通过一条或多条小径连接到湖边的中央集合点。每条小径要么是短的，要么是长的。小屋 $i$ 通过 $s_i$ 条短小径和 $l_i$ 条长小径连接到湖边。

每天，Harry 从他当前所在的小屋走一条小径到日内瓦湖，然后从湖边走一条小径到任意一个小屋（包括他开始时的小屋）。然而，由于他必须在一天内完成徒步，因此两条小径中至少有一条必须是短的。

如果 Harry 从第 1 号小屋开始，并徒步 $n$ 天，那么他有多少种可能的路径组合？

答案需要对 $10^9 + 7$ 取模。

### 样例 #1

#### 输入

```
3 2
1 0 1
0 1 1
```

#### 输出

```
18
```

### 题解分析与结论

本题的核心是通过动态规划（DP）来计算 Harry 在 $n$ 天内从第 1 号小屋出发，最终到达任意小屋的路径总数。由于每天的两条路径中至少有一条是短的，因此需要排除两条路径都是长路径的情况。

大多数题解采用了类似的 DP 思路，设 $dp_{i,j}$ 表示第 $i$ 天到达第 $j$ 号小屋的方案数。转移方程通常为：

$$ dp_{i,j} = \sum_{k=1}^m dp_{i-1,k} \times (s_j \times s_k + s_j \times l_k + l_j \times s_k) $$

其中，$s_j$ 和 $l_j$ 分别表示第 $j$ 号小屋的短路径和长路径数量。

### 精选题解

#### 题解1：作者：Shxt_Plus (★★★★☆)

**关键亮点：**
- 提供了从 Easy 到 Hard 的完整解题思路，逐步优化了时间复杂度。
- 在 Hard 版本中，通过矩阵快速幂将时间复杂度优化到 $O(2^3 \log n)$，适合大规模数据。

**代码实现：**
```cpp
int n, m, s[105], l[105], dp[1005][105];
signed main(){
    cin >> m >> n;
    for(int i = 1; i <= m; i++) cin >> s[i];
    for(int i = 1; i <= m; i++){
        cin >> l[i];
        r[i] = l[i] + s[i];
    }
    dp[0][1] = 1;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            int sum = 0;
            for(int k = 1; k <= m; k++){
                sum += (r[j] * r[k] - l[j] * l[k]) * dp[i - 1][k];
                sum %= MOD;
            }
            dp[i][j] = sum;
        }
    }
    int sum = 0;
    for(int i = 1; i <= m; i++){
        sum += dp[n][i];
        sum %= MOD;
    }
    cout << sum;
    return 0;
}
```

#### 题解2：作者：KukCair (★★★★☆)

**关键亮点：**
- 代码简洁，逻辑清晰，适合初学者理解。
- 直接使用了三重循环进行 DP 转移，易于实现。

**代码实现：**
```cpp
int n, m, s[105], l[105], dp[1005][105];
signed main(){
    cin >> m >> n;
    for(int i = 1; i <= m; i++) cin >> s[i];
    for(int i = 1; i <= m; i++) cin >> l[i];
    dp[0][1] = 1;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            for(int k = 1; k <= m; k++){
                dp[i][j] += dp[i-1][k] * (s[j] * s[k] + s[j] * l[k] + l[j] * s[k]);
                dp[i][j] %= MOD;
            }
        }
    }
    int ans = 0;
    for(int i = 1; i <= m; i++) ans = (ans + dp[n][i]) % MOD;
    cout << ans;
    return 0;
}
```

#### 题解3：作者：_Weslie_ (★★★★☆)

**关键亮点：**
- 详细解释了矩阵快速幂的优化思路，适合进阶学习者。
- 提供了矩阵构造的具体方法，帮助理解矩阵优化的核心思想。

**代码实现：**
```cpp
matrix qpow(matrix a, long long b){
    matrix res;
    for(int i = 1; i <= m; i++) res.a[1][i] = 0;
    res.a[1][1] = 1;
    while(b){
        if(b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}
```

### 最优关键思路

1. **动态规划（DP）**：通过状态转移方程 $dp_{i,j} = \sum_{k=1}^m dp_{i-1,k} \times (s_j \times s_k + s_j \times l_k + l_j \times s_k)$ 来计算每天的路径数。
2. **矩阵快速幂优化**：对于大规模数据，可以通过构造转移矩阵并使用矩阵快速幂将时间复杂度优化到 $O(m^3 \log n)$ 或更低。

### 可拓展之处

- **类似问题**：可以扩展到更复杂的路径限制问题，如多条路径、路径长度限制等。
- **矩阵优化**：矩阵快速幂不仅适用于 DP 优化，还可以用于其他需要快速幂计算的场景，如斐波那契数列、图论中的路径计数等。

### 推荐题目

1. [P3390 矩阵快速幂](https://www.luogu.com.cn/problem/P3390)
2. [P1939 矩阵加速](https://www.luogu.com.cn/problem/P1939)
3. [P1962 斐波那契数列](https://www.luogu.com.cn/problem/P1962)

### 个人心得总结

- **调试经历**：在实现 DP 时，确保状态转移方程的正确性非常重要，尤其是在处理取模运算时，容易忽略某些边界条件。
- **踩坑教训**：在矩阵快速幂的实现中，矩阵乘法的顺序和初始化需要特别注意，否则容易导致结果错误。

---
处理用时：48.71秒