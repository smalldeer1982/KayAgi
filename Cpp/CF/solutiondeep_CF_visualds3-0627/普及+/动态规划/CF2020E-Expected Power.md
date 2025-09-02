# 题目信息

# Expected Power

## 题目描述

You are given an array of $ n $ integers $ a_1,a_2,\ldots,a_n $ . You are also given an array $ p_1, p_2, \ldots, p_n $ .

Let $ S $ denote the random multiset (i. e., it may contain equal elements) constructed as follows:

- Initially, $ S $ is empty.
- For each $ i $ from $ 1 $ to $ n $ , insert $ a_i $ into $ S $ with probability $ \frac{p_i}{10^4} $ . Note that each element is inserted independently.

Denote $ f(S) $ as the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of all elements of $ S $ . Please calculate the expected value of $ (f(S))^2 $ . Output the answer modulo $ 10^9 + 7 $ .

Formally, let $ M = 10^9 + 7 $ . It can be shown that the answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 \pmod{M} $ . Output the integer equal to $ p \cdot q^{-1} \bmod M $ . In other words, output such an integer $ x $ that $ 0 \le x < M $ and $ x \cdot q \equiv p \pmod{M} $ .

## 说明/提示

In the first test case, $ a = [1, 2] $ and each element is inserted into $ S $ with probability $ \frac{1}{2} $ , since $ p_1 = p_2 = 5000 $ and $ \frac{p_i}{10^4} = \frac{1}{2} $ . Thus, there are $ 4 $ outcomes for $ S $ , each happening with the same probability of $ \frac{1}{4} $ :

- $ S = \varnothing $ . In this case, $ f(S) = 0 $ , $ (f(S))^2 = 0 $ .
- $ S = \{1\} $ . In this case, $ f(S) = 1 $ , $ (f(S))^2 = 1 $ .
- $ S = \{2\} $ . In this case, $ f(S) = 2 $ , $ (f(S))^2 = 4 $ .
- $ S = \{1,2\} $ . In this case, $ f(S) = 1 \oplus 2 = 3 $ , $ (f(S))^2 = 9 $ .

Hence, the answer is $ 0 \cdot \frac{1}{4} + 1 \cdot \frac{1}{4} + 4\cdot \frac{1}{4} + 9 \cdot \frac{1}{4} = \frac{14}{4} = \frac{7}{2} \equiv 500\,000\,007 \pmod{10^9 + 7} $ .

In the second test case, $ a = [1, 1] $ , $ a_1 $ is inserted into $ S $ with probability $ 0.1 $ , while $ a_2 $ is inserted into $ S $ with probability $ 0.2 $ . There are $ 3 $ outcomes for $ S $ :

- $ S = \varnothing $ . In this case, $ f(S) = 0 $ , $ (f(S))^2 = 0 $ . This happens with probability $ (1-0.1) \cdot (1-0.2) = 0.72 $ .
- $ S = \{1\} $ . In this case, $ f(S) = 1 $ , $ (f(S))^2 = 1 $ . This happens with probability $ (1-0.1) \cdot 0.2 + 0.1 \cdot (1-0.2) = 0.26 $ .
- $ S = \{1, 1\} $ . In this case, $ f(S) = 0 $ , $ (f(S))^2 = 0 $ . This happens with probability $ 0.1 \cdot 0.2 = 0.02 $ .

Hence, the answer is $ 0 \cdot 0.72 + 1 \cdot 0.26 + 0 \cdot 0.02 = 0.26 = \frac{26}{100} \equiv 820\,000\,006 \pmod{10^9 + 7} $ .

## 样例 #1

### 输入

```
4
2
1 2
5000 5000
2
1 1
1000 2000
6
343 624 675 451 902 820
6536 5326 7648 2165 9430 5428
1
1
10000```

### 输出

```
500000007
820000006
280120536
1```

# AI分析结果



---

## 题目翻译

# 期望的平方

## 题目描述

给定一个包含 $n$ 个整数的数组 $a_1,a_2,\ldots,a_n$，以及一个概率数组 $p_1, p_2, \ldots, p_n$。

定义随机多重集合 $S$（即允许重复元素）的构造方式如下：

- 初始时 $S$ 为空。
- 对于每个 $i$ 从 $1$ 到 $n$，以 $\frac{p_i}{10^4}$ 的概率将 $a_i$ 插入 $S$。各元素的插入相互独立。

定义 $f(S)$ 为 $S$ 中所有元素的异或值。要求计算 $(f(S))^2$ 的期望值，并对 $10^9 + 7$ 取模。

具体而言，令 $M = 10^9 + 7$。答案可以表示为不可约分数 $\frac{p}{q}$，其中 $q \not \equiv 0 \pmod{M}$。输出 $p \cdot q^{-1} \bmod M$。

## 说明/提示

样例一解释中展示了四种可能的 $S$ 及其概率分布，通过加权平均计算得到期望。样例二展示了重复元素对异或结果的影响。

## 输入输出样例

见原题内容。

---

## 算法分类  
**线性DP**

---

## 综合分析与结论

### 核心思路
问题本质是计算所有可能子集的异或平方期望。由于异或运算的位特性，可以采用动态规划维护每个可能的异或值的概率，最终计算加权平方和。

### 关键难点与解决方案
1. **状态压缩**：异或结果的最大值仅与 $a_i$ 的范围（≤1023）相关，因此可用 1024 个状态表示所有可能的异或值。
2. **概率转移**：每个元素有选/不选两种可能，需将前驱状态的异或值概率按概率分配到当前状态。
3. **模数处理**：分数概率需转换为模数乘法逆元运算，避免浮点精度问题。

### 动态规划设计
- **状态定义**：`dp[i][j]` 表示处理前 $i$ 个元素后异或和为 $j$ 的概率。
- **转移方程**：  
  `dp[i][j] = (不选概率) * dp[i-1][j] + (选概率) * dp[i-1][j^a_i]`
- **滚动优化**：使用双数组交替更新，空间复杂度优化至 $O(1024)$。

### 可视化设计
1. **网格动画**：以 Canvas 绘制 32x32 的网格，每个格子代表一个异或值，颜色深浅表示概率大小。
2. **高亮标记**：处理第 $i$ 个元素时，用闪烁边框标记当前操作的 `a_i` 值。
3. **音效反馈**：状态更新时播放短促电子音效，最终计算时播放胜利音效。
4. **8位像素风格**：采用复古绿黑配色，模拟早期计算机终端界面。

---

## 题解清单（≥4星）

### 题解1（Zeoykkk，★★★★☆）  
**亮点**：  
- 清晰定义状态转移方程，直接利用异或值域压缩状态。  
- 时间复杂度 $O(n \cdot 1024)$，适合大规模数据。

### 题解2（__3E24AC7002AD9292__，★★★★★）  
**亮点**：  
- 代码实现简洁，使用滚动数组优化空间。  
- 显式处理模逆元，避免浮点误差。

---

## 核心代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1e9 + 7;
const int MAXV = 1024;

ll f[2][MAXV];

ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

int main() {
    int T; cin >> T;
    const ll INV = qpow(10000, MOD - 2); // 1e4的逆元
    
    while (T--) {
        int n; cin >> n;
        vector<int> a(n + 1), p(n + 1);
        for (int i = 1; i <= n; ++i) cin >> a[i];
        for (int i = 1; i <= n; ++i) cin >> p[i];
        
        memset(f, 0, sizeof f);
        int cur = 0;
        f[cur][0] = 1;
        
        for (int i = 1; i <= n; ++i) {
            int nxt = cur ^ 1;
            memset(f[nxt], 0, sizeof f[nxt]);
            
            for (int j = 0; j < MAXV; ++j) {
                ll prob_sel = p[i] * INV % MOD; // 选中的概率
                ll prob_not = (10000 - p[i]) * INV % MOD; // 不选的概率
                
                // 不选当前元素
                f[nxt][j] = (f[nxt][j] + f[cur][j] * prob_not) % MOD;
                // 选当前元素，异或上a[i]
                f[nxt][j ^ a[i]] = (f[nxt][j ^ a[i]] + f[cur][j] * prob_sel) % MOD;
            }
            cur = nxt;
        }
        
        ll ans = 0;
        for (int j = 0; j < MAXV; ++j)
            ans = (ans + f[cur][j] * j % MOD * j) % MOD;
        cout << ans << '\n';
    }
}
```

---

## 同类型题目推荐
1. **CF1139D Steps to One**：期望概率与动态规划结合。
2. **LOJ 6485. 位运算统计**：位运算性质与状态压缩DP。
3. **洛谷 P2111 考前的游戏**：概率期望与异或操作的综合应用。

---

## 可视化与游戏化设计

### 动画方案
- **网格更新**：每次处理元素时，用绿色高亮当前处理的 `a_i`，红色表示转移来源状态。
- **音效同步**：每次状态转移时播放 8-bit 点击声，最终结果展示时播放 16-bit 胜利音效。

### 复古风格
- **调色板**：采用 Commodore 64 风格的 16 色方案，状态值用不同色阶表示概率密度。
- **自动演示**：按空格键启动/暂停自动播放，方向键控制单步前进/回退。

### 积分系统
- **正确转移**：每次成功转移奖励 10 分，连续正确转移触发连击加倍。
- **错误提示**：若概率和超过 1+1e-6（考虑浮点误差），播放警告音效并扣除 50 分。

---

通过以上设计，学习者可以直观观察动态规划的状态转移过程，并在游戏化交互中深入理解算法核心。

---
处理用时：102.17秒