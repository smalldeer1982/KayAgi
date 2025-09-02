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



---

**唯一算法分类**  
BFS

---

### 综合分析与结论  
**核心思路**  
将问题转化为余数分解问题，使用 BFS 分层搜索可能的余数状态，每次尝试从给定集合中选取数字，确保剩余部分可继续分解，直至余数为零。通过记录已访问的余数避免重复计算，保证找到最短解。

**核心难点**  
1. **余数处理**：需确保每一步的余数计算为整数，处理正负数取模的边界条件。  
2. **路径记录**：需逆向构造数字序列（从低位到高位），最终反转输出。  
3. **终止条件**：设置最大位数限制（如 60 步）避免无限循环。

**搜索过程可视化设计**  
- **节点表示**：每个节点为当前余数，边为选择的数字。  
- **队列操作**：每次扩展节点时遍历所有合法数字，生成新余数入队。  
- **颜色标记**：已访问节点标红，当前处理节点标绿，有效路径标黄。  
- **终止条件**：余数为零时高亮路径并播放成功音效。

---

### 题解清单  
暂无用户提供的题解，根据算法思路，可给出以下自研题解：

---

### 代码实现与核心逻辑  
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int> solve(ll k, const vector<int>& a, ll n) {
    const int MAX_STEPS = 60;
    queue<pair<ll, vector<int>>> q;
    unordered_set<ll> visited;

    q.push({n, {}});
    visited.insert(n);

    while (!q.empty()) {
        auto [r, digits] = q.front(); q.pop();

        if (r == 0) {
            reverse(digits.begin(), digits.end());
            return digits;
        }

        if (digits.size() >= MAX_STEPS) continue;

        for (int ai : a) {
            ll candidate = r - ai;
            if (candidate % k != 0) continue;
            ll next_r = candidate / k;

            if (!visited.count(next_r)) {
                vector<int> new_digits = digits;
                new_digits.push_back(ai);
                q.push({next_r, new_digits});
                visited.insert(next_r);
            }
        }
    }

    return {};
}

int main() {
    int k, q, D, M;
    cin >> k >> q >> D >> M;
    vector<int> a(D);
    for (int& x : a) cin >> x;

    while (q--) {
        ll n;
        cin >> n;
        auto res = solve(k, a, n);
        if (res.empty()) {
            cout << "IMPOSSIBLE\n";
        } else {
            for (int x : res) cout << x << ' ';
            cout << '\n';
        }
    }
}
```

**核心逻辑**  
- **BFS 初始化**：起始余数为 `n`，空序列。  
- **余数分解**：遍历集合 `a`，筛选合法候选生成新余数。  
- **路径记录**：按低位到高位顺序记录数字，最终反转输出。  
- **剪枝优化**：`visited` 集合避免重复状态，最大步数限制避免死循环。

---

### 最优思路提炼  
1. **逆向分解**：从余数出发，按位逆向构造数字（低位优先），避免指数计算。  
2. **状态剪枝**：用哈希表记录余数，确保每个状态仅处理一次。  
3. **最短路径优先**：BFS 天然保证找到最短解（最少位数）。

---

### 相似题型与拓展  
1. **LeetCode 494. Target Sum**（状态分解与路径计数）  
2. **洛谷 P1585 魔法阵**（余数处理与 BFS 结合）  
3. **CodeForces 1352E Special Permutation**（数值分解与集合匹配）

---

### 可视化设计要点  
**复古像素风格实现**  
- **Canvas 绘制**：余数节点以网格排列，边用箭头表示选择数字。  
- **音效触发**：访问新节点播放“哔”声，找到解时播放胜利音效。  
- **自动演示**：按 BFS 顺序自动展开节点，步进间隔可调。  
- **颜色方案**：使用 8-bit 色调（绿、红、黄）区分状态。

---

**示例：搜索过程动画**  
![BFS 搜索动图示例](https://via.placeholder.com/400x200/000000/FFFFFF/?text=BFS+Visualization)  
（动态演示余数分解与路径扩展，绿色为当前节点，黄色为解路径）

---
处理用时：221.24秒