# 题目信息

# [国家集训队] Crash的数字表格 / JZPTAB

## 题目描述

今天的数学课上，Crash 小朋友学习了最小公倍数（Least Common Multiple）。对于两个正整数 $a$ 和 $b$，$\text{lcm}(a,b)$ 表示能同时被 $a$ 和 $b$ 整除的最小正整数。例如，$\text{lcm}(6, 8) = 24$。

回到家后，Crash 还在想着课上学的东西，为了研究最小公倍数，他画了一张 $ n \times m$ 的表格。每个格子里写了一个数字，其中第 $i$ 行第 $j$ 列的那个格子里写着数为 $\text{lcm}(i, j)$。

看着这个表格，Crash 想到了很多可以思考的问题。不过他最想解决的问题却是一个十分简单的问题：这个表格中所有数的和是多少。当 $n$ 和 $m$ 很大时，Crash 就束手无策了，因此他找到了聪明的你用程序帮他解决这个问题。由于最终结果可能会很大，Crash 只想知道表格里所有数的和对 $20101009$ 取模后的值。



## 说明/提示

#### 样例输入输出 1 解释

该表格为：

|$1$|$2$|$3$|$4$|$5$|
|:-:|:-:|:-:|:-:|:-:|
|$2$|$2$|$6$|$4$|$10$|
|$3$|$6$|$3$|$12$|$15$|
|$4$|$4$|$12$|$4$|$20$|

#### 数据规模与约定

- 对于 $30\%$ 的数据，保证 $n, m \le 10^3$。
- 对于 $70\%$ 的数据，保证 $n, m \le 10^5$。
- 对于 $100\%$ 的数据，保证 $1\le n,m \le 10^7$。

## 样例 #1

### 输入

```
4 5```

### 输出

```
122```

# AI分析结果


### 题目分析

本题要求计算 $\sum_{i=1}^n \sum_{j=1}^m \text{lcm}(i,j)$ 对 $20101009$ 取模的结果。数据范围 $n, m \leq 10^7$，需要高效的算法设计。

#### 核心算法：莫比乌斯反演与数论分块
1. **问题转化**：
   - 利用 $\text{lcm}(i,j) = \frac{i \cdot j}{\gcd(i,j)}$，将原式转化为：
     \[
     \sum_{i=1}^n \sum_{j=1}^m \frac{i \cdot j}{\gcd(i,j)}
     \]
   - 枚举 $\gcd(i,j) = d$，得到：
     \[
     \sum_{d=1}^{\min(n,m)} d \sum_{i=1}^{\lfloor n/d \rfloor} \sum_{j=1}^{\lfloor m/d \rfloor} i \cdot j \cdot [\gcd(i,j)=1]
     \]

2. **莫比乌斯反演**：
   - 利用 $[\gcd(i,j)=1] = \sum_{k|\gcd(i,j)} \mu(k)$，进一步推导：
     \[
     \sum_{d=1}^{\min(n,m)} d \sum_{k=1}^{\lfloor \min(n,m)/d \rfloor} \mu(k) \cdot k^2 \cdot S\left(\left\lfloor \frac{n}{d \cdot k} \right\rfloor\right) \cdot S\left(\left\lfloor \frac{m}{d \cdot k} \right\rfloor\right)
     \]
     其中 $S(x) = \frac{x(x+1)}{2}$ 是等差数列求和公式。

3. **变量替换与积性函数设计**：
   - 令 $T = d \cdot k$，替换后得到：
     \[
     \sum_{T=1}^{\min(n,m)} T \cdot g(T) \cdot S\left(\left\lfloor \frac{n}{T} \right\rfloor\right) \cdot S\left(\left\lfloor \frac{m}{T} \right\rfloor\right)
     \]
     其中 $g(T) = \sum_{d|T} d \cdot \mu(d)$ 是积性函数。

4. **线性筛预处理**：
   - $g(T)$ 是积性函数，可通过线性筛预处理：
     - $g(1) = 1$。
     - 对质数 $p$，$g(p) = 1 - p$。
     - 若 $i$ 与质数 $p$ 互质，$g(i \cdot p) = g(i) \cdot g(p)$。
     - 若 $p \mid i$，则 $g(i \cdot p) = g(i)$。
   - 计算 $h(T) = T \cdot g(T)$ 的前缀和数组 $S_h(T)$。

5. **数论分块优化**：
   - 外层枚举 $T$，利用 $S\left(\left\lfloor \frac{n}{T} \right\rfloor\right)$ 和 $S\left(\left\lfloor \frac{m}{T} \right\rfloor\right)$ 的分段性质，将 $T$ 分成若干块。
   - 每块区间 $[l, r]$ 满足 $\left\lfloor \frac{n}{l} \right\rfloor = \left\lfloor \frac{n}{r} \right\rfloor$ 且 $\left\lfloor \frac{m}{l} \right\rfloor = \left\lfloor \frac{m}{r} \right\rfloor$。
   - 块内贡献为 $(S_h[r] - S_h[l-1]) \cdot S\left(\left\lfloor \frac{n}{l} \right\rfloor\right) \cdot S\left(\left\lfloor \frac{m}{l} \right\rfloor\right)$。

#### 时间复杂度
- 预处理：$O(n)$。
- 查询：$O(\sqrt{n})$（单次数论分块）。

### 精选优质题解参考
1. **Siyuan 的题解**：
   - **亮点**：推导清晰，代码简洁，使用两层数论分块，时间复杂度 $O(n^{3/4})$。
   - **代码规范性**：变量命名合理，结构清晰，关键步骤有注释。
   - **优化点**：预处理 $\mu(k) \cdot k^2$ 的前缀和，直接用于分块计算。

2. **pengym 的题解**：
   - **亮点**：详细推导每一步的数学变换，强调积性函数的性质，代码包含详细注释。
   - **实践价值**：提供完整的调试经历（如边界处理），适合学习者理解细节。

3. **George1123 的题解**：
   - **亮点**：代码高效，使用狄利克雷卷积和杜教筛优化至 $O(n^{2/3})$，适合进阶学习。
   - **技巧总结**：强调积性函数的线性筛实现和分块技巧，代码模块化封装。

### 核心难点辨析与解题策略
1. **难点1：状态定义与转移方程**：
   - 如何准确定义 $g(T) = \sum_{d|T} d \cdot \mu(d)$ 并证明其积性。
   - **解决方案**：利用莫比乌斯函数的性质，结合积性函数的乘法性质推导。

2. **难点2：双层分块实现**：
   - 外层枚举 $d$，内层枚举 $k$，需协调两层分块的边界。
   - **解决方案**：变量替换 $T = d \cdot k$ 合并为一层分块，简化复杂度。

3. **难点3：负数取模处理**：
   - $g(T)$ 可能为负数，前缀和计算需调整到 $[0, \text{mod})$。
   - **解决方案**：每次计算后取模并加 $\text{mod}$ 再取模，避免负数。

### C++ 核心代码实现赏析
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e7 + 10;
const int mod = 20101009;

int vis[N], prime[N], cnt;
ll mu[N], g[N], S[N]; // g(T) = sum_{d|T} d * μ(d)

void init() {
    mu[1] = 1;
    for (int i = 2; i < N; i++) {
        if (!vis[i]) {
            prime[++cnt] = i;
            mu[i] = -1;
            g[i] = (1 - i + mod) % mod; // g(p) = 1 - p
        }
        for (int j = 1; j <= cnt && i * prime[j] < N; j++) {
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                g[i * prime[j]] = g[i]; // p|i 时 g(i*p) = g(i)
                break;
            }
            mu[i * prime[j]] = -mu[i];
            g[i * prime[j]] = g[i] * g[prime[j]] % mod; // 积性性质
        }
    }
    // 计算 h(T) = T * g(T) 的前缀和
    for (int i = 1; i < N; i++) {
        ll h = i * g[i] % mod;
        S[i] = (S[i - 1] + h) % mod;
    }
}

ll sum1(ll x) { // 等差数列求和 S(x) = x(x+1)/2
    return x * (x + 1) / 2 % mod;
}

int main() {
    init();
    int n, m;
    scanf("%d%d", &n, &m);
    if (n > m) swap(n, m);

    ll ans = 0;
    for (int l = 1, r; l <= n; l = r + 1) {
        r = min(n / (n / l), m / (m / l)); // 分块右端点
        ll sum_block = (S[r] - S[l - 1] + mod) % mod;
        ll sum_n = sum1(n / l); // S(floor(n/T))
        ll sum_m = sum1(m / l); // S(floor(m/T))
        ans = (ans + sum_block * sum_n % mod * sum_m % mod) % mod;
    }
    printf("%lld\n", ans);
    return 0;
}
```

### 算法可视化：像素动画演示
设计一个 **8位像素风格动画** 展示数论分块过程：
1. **场景设计**：
   - 网格表示 $1$ 到 $n$ 的整数轴，每个像素块代表一个分块区间 $[l, r]$。
   - 不同颜色标记当前分块：绿色（计算中）、黄色（已计算）、灰色（未计算）。

2. **动画流程**：
   - **初始化**：网格全灰，控制面板显示 `Start`。
   - **分块演示**：从 $l=1$ 开始，计算 $r$，高亮区间 $[l, r]$ 为绿色，显示当前块贡献值。
   - **数据更新**：显示 $S_h[r] - S_h[l-1]$、$S(n/l)$、$S(m/l)$ 的实时计算。
   - **音效**：分块移动时播放“滴答”声，完成时播放“完成”音效。

3. **交互控制**：
   - 步进按钮：单步执行分块。
   - 速度滑块：调整分块计算速度。
   - 暂停/继续：控制动画播放。

### 拓展练习与相似问题
1. **相似问题**：
   - **P3455 [POI2007] ZAP-Queries**：基础莫比乌斯反演，求 $\sum_{i=1}^a \sum_{j=1}^b [\gcd(i,j)=k]$。
   - **P2522 [HAOI2011] Problem B**：扩展至多维莫比乌斯反演。
   - **P3312 [SDOI2014] 数表**：结合约数和性质的莫比乌斯反演。

2. **洛谷推荐**：
   - **P2260 [清华集训] 模积和**：复杂数论分块与模运算。
   - **P3704 [SDOI2017] 数字表格**：积性函数与莫比乌斯反演结合。
   - **P3768 简单的数学题**：杜教筛进阶应用。

### 学习心得与经验分享
- **调试技巧**：处理负数取模时，统一使用 `(x % mod + mod) % mod` 保证非负。
- **积性函数**：深刻理解积性性质（如 $g(p^k)=1-p$）可简化线性筛设计。
- **分块优化**：将双重循环通过变量替换合并为单层分块，显著提升效率。

通过本题，可系统掌握莫比乌斯反演与数论分块的核心思想，并应用于更复杂的数论问题中。

---
处理用时：233.77秒