# 题目信息

# Segmentation Folds

## 题目描述

Peter 喜欢折线段玩。有一条线段位于数轴上的区间 $[\ell, r]$。现如今正是折叠线段的好时机，Peter 决定小心翼翼地对这条线段进行折叠。每次操作中，他可以选择以下两种方式之一（在可能的情况下）：

1. 操作 $\tt{LTR}$：他从左向右折线段，使得左端点 $\ell$ 与某个点 $x$ 重合（$\ell < x \le r$），并且 $\ell + x$ 是质数。当他选择此操作时，总是选取最大的 $x$ 值。折叠后，线段所在的区间变为 $[\frac{1}{2}(\ell + x), r]$。
   
2. 操作 $\tt{RTL}$：他从右向左折线段，使得右端点 $r$ 与某个点 $x$ 重合（$\ell \le x < r$），并且 $r + x$ 是质数。当他选择此操作时，总是选取最小的 $x$ 值。折叠后，线段所在的区间变为 $[\ell, \frac{1}{2}(r + x)]$。

一个折叠序列是指这两种操作的组合。Peter 想要通过多次折叠，使线段的长度尽可能短，且无法再缩短。区间的长度自然定义为 $r - \ell$。考虑以下例子：假设我们折叠一段初始为 $[1, 30]$ 的线段。有三种折叠方式能使最终区间长度最短，如下图所示。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2041F/be032bc113ac39f401b84d34f2c5f31947b110d1.png)

请你帮助 Peter 确定有多少种不同的折叠序列可以使线段达到最短长度。结果需要对 $998244353$ 取模。

注：一个大于 $1$ 的整数 $p$ 是质数，当且仅当不存在整数 $a, b > 1$ 使得 $p = ab$。

## 样例 #1

### 输入

```
3
1 30
16 18
142857 240135```

### 输出

```
3
1
63```

# AI分析结果



---

**唯一算法分类**：数学建模与质数筛法结合的状态搜索

---

### **综合分析与结论**

1. **核心算法流程**  
   - **区间放大**：将原区间 $[l, r]$ 乘以 2 转化为整数区间 $[2l, 2r]$，避免浮点运算。  
   - **质数筛法**：预处理 $\sqrt{2r}$ 内质数，用区间筛法筛选 $[2l, 2r]$ 内的质数集合。  
   - **状态搜索**：  
     - **操作选择**：每个状态 $[L, R]$ 可进行两种操作：  
       - **LTR**：找最大质数 $p$ 使得 $L < p \le R$，生成新区间 $[\frac{p}{2}, R]$。  
       - **RTL**：找最小质数 $p$ 使得 $L \le p < R$，生成新区间 $[L, \frac{p}{2}]$。  
     - **终止条件**：当区间无法再折叠时（即无质数满足条件），记录区间长度和路径数。  
   - **动态规划优化**：记忆化存储每个状态的最短长度及路径数，避免重复计算。

2. **可视化设计思路**  
   - **像素风格动画**：  
     - **网格表示数轴**：用 Canvas 绘制数轴网格，区间端点用不同颜色方块标记。  
     - **质数高亮**：当前操作对应的质数 $p$ 显示为闪烁像素块。  
     - **折叠动画**：展示区间端点向中点移动的过程，配合“折叠”音效。  
   - **音效设计**：  
     - **成功折叠**：播放 8-bit 上升音效。  
     - **无法操作**：短促下降音效。  
   - **AI 自动演示**：按最优路径自动执行折叠，每步间隔可调。

---

### **题解清单 (4.5星)**

- **关键亮点**：  
  1. **质数筛法优化**：通过区间筛法高效处理大范围质数，时间复杂度 $\mathcal{O}(n \log \log n)$。  
  2. **状态转移剪枝**：每个状态仅有 $\mathcal{O}(\log n)$ 前驱，直接搜索复杂度线性。  
  3. **整数化处理**：将区间乘以 2 避免浮点误差，提升代码鲁棒性。

---

### **代码核心实现**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 998244353;
const int MAXN = 1e6 + 5;

vector<ll> primes;
bool is_prime[MAXN];

// 预处理小质数用于区间筛
void sieve() {
    memset(is_prime, true, sizeof(is_prime));
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i < MAXN; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (ll j = i * i; j < MAXN; j += i)
                is_prime[j] = false;
        }
    }
}

// 区间筛法获取 [L, R] 内的质数
vector<ll> segment_sieve(ll L, ll R) {
    vector<bool> is_prime_seg(R - L + 1, true);
    for (ll p : primes) {
        if (p * p > R) break;
        ll start = max(p * p, (L + p - 1) / p * p);
        for (ll j = start; j <= R; j += p)
            is_prime_seg[j - L] = false;
    }
    vector<ll> res;
    for (ll i = L; i <= R; i++)
        if (i >= 2 && is_prime_seg[i - L])
            res.push_back(i);
    return res;
}

map<pair<ll, ll>, pair<ll, ll>> memo; // (l, r) → (min_len, count)

pair<ll, ll> dfs(ll l, ll r, const vector<ll>& primes_list) {
    if (memo.count({l, r})) return memo[{l, r}];
    
    // 尝试 LTR 和 RTL 操作
    vector<pair<ll, ll>> next_states;
    
    // LTR 操作：找最大的 p = l + x，且 p ∈ (l, r]
    auto it_upper = upper_bound(primes_list.begin(), primes_list.end(), r);
    if (it_upper != primes_list.begin()) {
        it_upper--;
        if (*it_upper > l) {
            ll p = *it_upper;
            next_states.emplace_back((l + p) / 2, r);
        }
    }
    
    // RTL 操作：找最小的 p = r + x，且 p ∈ [l, r)
    auto it_lower = lower_bound(primes_list.begin(), primes_list.end(), l);
    if (it_lower != primes_list.end() && *it_lower < r) {
        ll p = *it_lower;
        next_states.emplace_back(l, (r + p) / 2);
    }
    
    if (next_states.empty()) { // 终止状态
        return memo[{l, r}] = {r - l, 1};
    }
    
    ll min_len = 1e18, cnt = 0;
    for (auto [nl, nr] : next_states) {
        auto [clen, c] = dfs(nl, nr, primes_list);
        if (clen < min_len) {
            min_len = clen;
            cnt = c;
        } else if (clen == min_len) {
            cnt = (cnt + c) % MOD;
        }
    }
    return memo[{l, r}] = {min_len, cnt};
}

int main() {
    sieve();
    int T; cin >> T;
    while (T--) {
        ll l, r; cin >> l >> r;
        l *= 2, r *= 2;
        auto primes_seg = segment_sieve(l, r);
        memo.clear();
        auto [len, ans] = dfs(l, r, primes_seg);
        cout << ans % MOD << endl;
    }
    return 0;
}
```

---

### **同类型题与类似套路**

1. **质数筛法优化**：如区间筛法解决大范围质数问题（例：洛谷 P1835）。  
2. **状态转移搜索**：如 BFS/DFS 结合记忆化处理状态转移（例：动态规划最短路径计数）。  
3. **离散化处理**：将连续问题转化为离散质数操作。

---

### **推荐题目**

1. **洛谷 P1835**：素数密度（区间筛法模板题）。  
2. **洛谷 P1379**：八数码难题（状态搜索与记忆化）。  
3. **洛谷 P1020**：导弹拦截（动态规划与离散化结合）。

---
处理用时：95.98秒