# 题目信息

# [GCJ 2011 #2] Expensive Dinner

## 题目描述

你的朋友们今晚都要去一家餐厅吃饭。他们都非常擅长数学，但也都很奇怪：你的第 $a$ 个朋友（从 1 开始编号）只有当餐费总额是一个正整数且能被 $a$ 整除时才会感到满意。

你的朋友们会依次进入餐厅。每当有一个人进入餐厅时，如果那个人不满意，那么这群人会立刻叫来一位服务员。

只要餐厅里至少有一个不满意的人，这些不满意的人中就会有一个人购买一份最低价格的食物，使自己变得满意。这个过程会一直持续，直到餐厅里没有人不满意为止，然后服务员才会离开。幸运的是，餐厅出售每一个整数价格的食物。具体例子见第一个样例的解释。

你的朋友们可以以任意顺序进入餐厅。在叫来服务员之后，如果餐厅里有多个人不满意，可以由其中任意一个人先购买食物。所有这些选择的方式可能会影响这群人叫服务员的次数。

作为餐厅老板，你雇佣了一些非常疲惫的服务员。你想要计算你朋友们的“分布值”：他们可能叫服务员的最大次数与最小次数之差。

## 说明/提示

**样例解释**

在第 2 个样例中，假设你的朋友们按顺序 $[1, 2, 3]$ 进入。第 1 号朋友进入，不满意，叫来服务员，买了一份价格为 $1$ 的食物。现在没人不满意。接着第 2 号朋友进入，不满意，叫来服务员，买了一份价格为 $1$ 的食物（总价为 $2$）。现在没人不满意。第 3 号朋友进入，不满意，叫来服务员，买了一份价格为 $1$ 的食物（总价为 $3$）。现在第 2 号朋友不满意，买了一份价格为 $1$ 的食物（总价为 $4$）。现在第 3 号朋友不满意，买了一份价格为 $2$ 的食物（总价为 $6$）。最终没人不满意，总共叫了三次服务员。

如果朋友们的进入顺序是 $[3, 1, 2]$。第 3 号朋友进入，不满意，叫来服务员，买了一份价格为 $3$ 的食物。现在没人不满意。接着第 1 号朋友进入，没有人不满意。第 2 号朋友进入，不满意，叫来服务员，买了一份价格为 $1$ 的食物（总价为 $4$）。现在第 3 号朋友不满意，买了一份价格为 $2$ 的食物（总价为 $6$）。现在没人不满意，总共叫了两次服务员。分布值为 $1$。

**数据范围**

**小数据集（13 分，测试点 1 - 可见）**

- $1 \leq T \leq 100$。
- $1 \leq N \leq 1000$。
- 时间限制：3 秒。

**大数据集（17 分，测试点 2 - 隐藏）**

- $1 \leq T \leq 1000$。
- $1 \leq N \leq 10^{12}$。
- 时间限制：6 秒。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
1
3
6
16```

### 输出

```
Case #1: 0
Case #2: 1
Case #3: 2
Case #4: 5```

# AI分析结果


```cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAX_M = 1000000; // 10^6
vector<int> primes;
vector<bool> is_prime;
vector<vector<long long>> powers; // powers[i] for primes[i]

// Precompute primes up to MAX_M and their power tables
void precompute() {
    is_prime.resize(MAX_M + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= MAX_M; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (long long j = (long long)i * i; j <= MAX_M; j += i) {
                is_prime[j] = false;
            }
        }
    }

    powers.resize(primes.size());
    for (int i = 0; i < primes.size(); i++) {
        long long p = primes[i];
        long long cur = p;
        while (true) {
            powers[i].push_back(cur);
            if (cur > 1000000000000LL / p) break; // Prevent overflow
            cur *= p;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    precompute();
    
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        long long n;
        cin >> n;
        if (n == 1) {
            cout << "Case #" << t << ": " << 0 << '\n';
            continue;
        }
        
        // Compute m = floor(sqrt(n))
        long long m = sqrt(n);
        while (m * m > n) m--;
        while ((m + 1) * (m + 1) <= n) m++;
        
        // Count primes <= m
        int idx = upper_bound(primes.begin(), primes.end(), m) - primes.begin();
        int cnt_prime = idx;
        
        long long sum_exp = 0;
        for (int i = 0; i < idx; i++) {
            auto& vec = powers[i];
            // Find largest power <= n
            auto it = upper_bound(vec.begin(), vec.end(), n);
            if (it != vec.begin()) {
                it--;
                int k = it - vec.begin() + 1; // k = exponent
                sum_exp += k;
            }
        }
        
        long long ans = 1 + sum_exp - cnt_prime;
        cout << "Case #" << t << ": " << ans << '\n';
    }
    return 0;
}
```

### 算法分析：
本题考察数论与数学推导能力，核心在于发现服务员被叫次数与质因子分布的规律：

1. **关键结论**：
   - 最小服务员被叫次数 = $n$ 以内质数个数 $\pi(n)$
   - 最大服务员被叫次数 = $1 + \sum_{p \leq n} \lfloor \log_p n \rfloor$
   - 答案 = $1 + \sum_{p \leq n} \lfloor \log_p n \rfloor - \pi(n)$

2. **算法步骤**：
   - **预处理**：筛法生成 $\sqrt{10^{12}}$ 内所有质数（约 $10^6$ 规模）
   - **幂表构建**：为每个质数预计算其幂次（$p^k \leq 10^{12}$）
   - **查询处理**：
     - 计算 $m = \lfloor \sqrt{n} \rfloor$
     - 二分查找统计 $\leq m$ 的质数个数
     - 对每个质数 $p \leq m$，二分查找最大 $k$ 满足 $p^k \leq n$
     - 公式计算答案 $1 + \sum k - \pi(\sqrt{n})$

3. **复杂度**：
   - 预处理：$O(10^6 \log \log 10^6)$
   - 单次查询：$O(\pi(\sqrt{n}) \cdot \log 40) \approx O(7.8 \times 10^4 \times 6)$
   - 总复杂度：$O(T \cdot \pi(\sqrt{n}) \log 40) \approx 1000 \times 4.68 \times 10^5 = 4.68 \times 10^8$

### 代码亮点：
1. **双预处理优化**：
   - 欧拉筛快速生成质数表
   - 幂表预处理避免重复计算
2. **二分加速**：
   - 质数范围二分（`upper_bound`）
   - 幂次二分查找（$O(\log 40)$ 完成）
3. **溢出防护**：
   - 幂计算时用 `cur > LIMIT / p` 代替乘法
   - `long long` 全程防溢出
4. **精度处理**：
   - 手动调整 `m = floor(sqrt(n))` 避免浮点误差

### 学习笔记：
> **质因数分解的妙用**：将复杂过程转化为质因子指数问题，通过预处理和二分实现高效查询。关键是通过数学推导发现服务员被叫次数只与质因子的最高幂次相关。

### 拓展练习（洛谷）：
1. **P3383 【模板】线性筛素数**（质数筛法基础）
2. **P3912 素数个数**（大范围质数计数）
3. **P1069 分解质因数**（质因数分解应用）

---
处理用时：573.44秒