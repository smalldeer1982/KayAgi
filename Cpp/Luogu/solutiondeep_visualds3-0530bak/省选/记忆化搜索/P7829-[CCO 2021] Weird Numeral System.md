# 题目信息

# [CCO 2021] Weird Numeral System

## 题目描述

Alice 正在思考一个关于 $k$ 进制整数的问题。

普通的 $k$ 进制可以将整数 $n$ 表示为 $d_{m - 1} d_{m - 2} \cdots d_0$，且满足：

1. $0 \leq d_i < k$；
2. $n = \displaystyle\sum_{i = 0}^{m - 1} d_i k^i$。

然而，普通的 $k$ 进制整数对于 Alice 来说太简单了，Alice 更喜欢奇怪的 $k$ 进制整数。它与普通 $k$ 进制整数的差别仅仅在于将 $0 \leq d_i < k$ 换成了 $d_i \in a$，其中 $a$ 为一个长为 $D$ 的数列。

现在有一组固定的 $a_1, a_2, \cdots, a_D$，Alice 想要将 $q$ 个十进制整数 $n_1, n_2, \cdots, n_q$ 全部转化为奇怪的 $k$ 进制整数，这种问题显然更适合写程序来解决。

## 说明/提示

**本题由 @[Leasier](https://www.luogu.com.cn/user/201007) 提供 SPJ。**
#### 数据范围
对于 $100\%$ 的数据，$2 \leq k \leq 10^6$，$1 \leq q \leq 5$，$1 \leq D \leq 801$，$1 \leq M \leq 400$，$-M \leq a_i \leq M$，$-10^{18} \leq n_i \leq 10^{18}$。
#### 题目来源
[CCO2021](https://cemc.math.uwaterloo.ca/contests/computing/2021/index.html) D1T2

## 样例 #1

### 输入

```
3 3 3 1
-1 0 1
15
8
-5```

### 输出

```
1 -1 -1 0
1 0 -1
-1 1 1```

## 样例 #2

### 输入

```
10 1 3 2
0 2 -2
17```

### 输出

```
IMPOSSIBLE```

# AI分析结果



**唯一算法分类**  
贪心算法  

**综合分析与结论**  
本题要求将十进制数转换为每位数字仅限特定集合的k进制数。核心思路是每次选择使商绝对值最小的数字，以确保快速收敛。关键在于模运算处理余数，并选择合适数字保证后续步骤可行。  

**核心算法流程**  
1. **处理n=0的特殊情况**：若允许数字0，直接返回。  
2. **余数计算**：调整余数为正，确保在[0, k)范围内。  
3. **候选筛选**：遍历集合，筛选出余数匹配的数字。  
4. **贪心选择**：选取使商绝对值最小的数字，更新n为商。  
5. **终止条件**：n=0时反转序列输出，否则无解。  

**可视化设计思路**  
- **动画演示**：展示余数计算、候选筛选、商更新步骤。  
- **颜色高亮**：当前n、余数、候选数字突出显示。  
- **步进控制**：允许单步执行观察每步选择。  
- **复古像素风**：用网格表示进制位变化，音效提示关键操作。  

**题解清单 (≥4星)**  
暂无4星及以上题解。  

**最优思路提炼**  
1. **模运算处理**：确保余数非负，筛选合法候选。  
2. **贪心选择策略**：每次选商绝对值最小的，加速收敛。  
3. **路径反转输出**：逆序得到高位到低位的结果。  

**代码实现**  
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int> convert(ll n, int k, const vector<int>& a, int M) {
    if (n == 0) {
        if (find(a.begin(), a.end(), 0) != a.end()) return {0};
        else return {};
    }
    vector<int> digits;
    for (int step = 0; step < M; ++step) {
        ll r = (n % k + k) % k;
        vector<pair<ll, int>> candidates;
        for (int d : a) {
            ll dr = (d % k + k) % k;
            if (dr == r) {
                ll q = (n - d) / k;
                candidates.emplace_back(abs(q), d);
            }
        }
        if (candidates.empty()) return {};
        sort(candidates.begin(), candidates.end());
        int d = candidates[0].second;
        digits.push_back(d);
        n = (n - d) / k;
        if (n == 0) break;
    }
    if (n != 0) return {};
    reverse(digits.begin(), digits.end());
    return digits;
}

int main() {
    int k, q, D, M;
    cin >> k >> q >> D >> M;
    vector<int> a(D);
    for (int& x : a) cin >> x;
    while (q--) {
        ll n;
        cin >> n;
        auto res = convert(n, k, a, M);
        if (res.empty()) {
            cout << "IMPOSSIBLE\n";
        } else {
            for (int i = 0; i < res.size(); ++i) {
                if (i > 0) cout << ' ';
                cout << res[i];
            }
            cout << '\n';
        }
    }
}
```

**同类型题推荐**  
1. P2084 进制转换（基础进制处理）  
2. P1466 集合（模运算与组合问题）  
3. P1045 麦森数（高精度与进制应用）  

**个人心得**  
模运算处理负数是关键，贪心策略需确保商最小。测试极端案例（如大k、负数）验证算法鲁棒性。  

**可视化实现要点**  
- **Canvas网格**：每个方块代表进制位，动态填充数字。  
- **音效反馈**：候选命中、商更新、成功/失败音效。  
- **自动演示**：按步播放，速度可调，回溯路径展示。

---
处理用时：573.40秒