# 题目信息

# Greedy Monocarp

## 题目描述

有 $n$ 个宝箱，第 $i$ 个有 $a_i$ 枚金币。对于每个宝箱，你可以加入任何非负整数枚金币，最终使得所有宝箱中金币的总数不小于 $k$。

在你加入金币之后，贪婪的 Monocarp 会来取金币。他会一个一个的取走宝箱，每次取走金币最多的宝箱，直到他取走金币的总数至少为 $k$。

你想要 Monocarp 取走尽量少的金币，所以你需要给宝箱增加一定的金币，使得 Monocarp 取走恰好 $k$ 枚金币。算出你最少需要加入多少枚金币。

## 样例 #1

### 输入

```
4
5 4
4 1 2 3 2
5 10
4 1 2 3 2
2 10
1 1
3 8
3 3 3```

### 输出

```
0
1
8
2```

# AI分析结果



**唯一算法分类**  
贪心算法

---

**综合分析与结论**  

本题的核心在于确定如何通过最少的金币添加，使得Monocarp在取宝箱时恰好取到k枚金币。通过分析，最优策略是枚举可能被选中的宝箱数量m，并构造非递增序列以确保取宝箱顺序正确，同时最小化金币添加量。

**核心难点**  
1. **非递增序列构造**：调整后的宝箱金币数必须满足非递增顺序，以确保Monocarp按正确顺序取宝箱。
2. **最小化添加量**：在满足总和≥k的条件下，尽可能减少金币的添加量。

**解决方案**  
1. **排序预处理**：将宝箱按原始金币数降序排列。
2. **枚举m值**：对每个可能的m（1到n），计算前m个宝箱的最小金币添加量。
3. **贪心调整**：对每个m，枚举前i个宝箱保持原值，剩余m-i个调整到公共值t，使得总和≥k且t尽可能小。

**可视化设计思路**  
- **动画步骤**：展示排序后的宝箱、枚举m的过程，以及逐步调整后m个宝箱的数值变化。
- **高亮关键步骤**：当前处理的m值、调整后的公共t值、总添加量计算。
- **颜色标记**：用不同颜色区分原始值与调整后的值，突出非递增顺序的维护。

---

**最优思路提炼**  

1. **降序排序**：原始数组降序排列后，简化后续处理。
2. **枚举m与i**：对每个m，枚举前i项保持原值，后m-i项调整到公共t值。
3. **数学优化**：计算t的最小值，确保总和≥k且非递增顺序，通过前缀和快速计算添加量。

---

**代码实现**  

```cpp
#include <bits/stdc++.h>
using namespace std;

long long solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int &x : a) cin >> x;
    sort(a.rbegin(), a.rend());
    
    vector<long long> prefix(n + 1);
    for (int i = 0; i < n; ++i) prefix[i + 1] = prefix[i] + a[i];
    
    long long res = LLONG_MAX;
    for (int m = 1; m <= n; ++m) {
        long long s = prefix[m];
        if (s >= k) {
            res = 0;
            break;
        }
        long long min_add = LLONG_MAX;
        for (int i = 0; i <= m; ++i) {
            long long sum_i = prefix[i];
            long long remaining = k - sum_i;
            if (remaining <= 0) continue;
            int num = m - i;
            if (num <= 0) continue;
            long long required_t = (remaining + num - 1) / num;
            int a_i_plus1 = (i < m) ? a[i] : 0;
            long long lower_t = max(required_t, (long long)a_i_plus1);
            long long upper_t = (i >= 1) ? a[i - 1] : LLONG_MAX;
            if (i >= 1 && lower_t > upper_t) continue;
            long long add = lower_t * num - (prefix[m] - prefix[i]);
            min_add = min(min_add, add);
        }
        res = min(res, min_add);
    }
    return res;
}

int main() {
    int t;
    cin >> t;
    while (t--) cout << solve() << '\n';
}
```

---

**相似题目推荐**  
1. P1090 [合并果子]：贪心策略优化总和。
2. P1223 [排队接水]：排序与贪心结合。
3. P3817 小A的糖果：通过调整满足序列条件的最小操作数。

---
处理用时：518.11秒