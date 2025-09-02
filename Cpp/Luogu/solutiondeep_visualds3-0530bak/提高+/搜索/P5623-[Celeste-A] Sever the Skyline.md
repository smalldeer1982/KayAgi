# 题目信息

# [Celeste-A] Sever the Skyline

## 题目背景

> 废弃的城市里充满了机关和陷阱，而今晚，我们将

> ——划破这城市的天际线

## 题目描述

Madeline 来到了被废弃的城市，这座城市里满是机关，还有一台不知所谓的机器在向外发射着光信号。

通过 Madeline 强大的观察力，她发现光信号其实对应着某种冲刺顺序，按照顺序冲刺之后，她发现她冲刺的轨迹构成了这座废弃城市的天际线。

多年以后，当 Madeline 回忆她登山的旅途时，已经不记得这座城市的天际线长什么样了，只记得所有建筑高度的和为 $n$，并且每座建筑的高度可以表示为 $p^iq^j$，$p,q$ 为素数且 $i,j \geq 0,i+j\geq 1$。

Madeline 知道，这座城市的天际线是很有美感的，不存在两座建筑使得它们的高度成**整倍数**关系(1倍也是整倍数)，例如若存在一座高度为 $2$ 的建筑，就一定不能存在高度为 $4$ 的建筑。

由于 Madeline 的记忆相当模糊，所以她可能要求你多次对于一个特定的记忆给出一个合法的天际线。

## 说明/提示

对于前 $30\%$ 的数据，保证 $n \leq 100$，

对于另外 $20\%$ 的数据，保证 $p,q \leq 3$

对于 $100\%$ 的数据，保证 $1 < n \leq 10^{18}, p,q \leq 40, p < q, T \leq 10000$

对于最后 $30\%$ 的数据，采用捆绑测试，仅当您通过了所有测试点才能得分。

保证数据的生成方式为：

均匀随机两个质数 $p,q$，随机选择若干个 $p^iq^j$，保证它们不成倍数，将 $p^iq^j$ 的和作为 $n$，若这组数据满足当前数据点的要求，则保留，若不满足，则重新生成。

对于最后 $30\%$ 数据点，对于 $n$ 要求 $n > 10^{17}$。

对于最后 $30\%$ 数据点中的部分测试点，要求至少选出 $4$ 个 $p^iq^j$ 来组成 $n$。

**本题 spj 认可的格式为：行末无空格，每组输出行末换行。**

**若格式不正确，您可能会获得 UKE**

## 样例 #1

### 输入

```
3
15 2 3
10 2 5
416873881340965120 2 7```

### 输出

```
6 9
10
8507630225817856 19446011944726528 22224013651116032 12699436372066304 8293509467471872 4739148267126784 1354042362036224 3094953970368512 1768545125924864 32339110874054656 5279854836580352 1508529953308672 3448068464705536 3940649673949184 288230376151711744
```

# AI分析结果



## 算法分类
其他搜索

## 综合分析与结论
题目要求将数n分解为多个互不为倍数的p^i q^j之和。关键在于生成候选数并利用DFS+剪枝策略快速找到符合条件的数集。

### 核心思路
1. **候选数生成**：枚举所有p^i q^j形式的数，并按降序排列。
2. **DFS+剪枝**：从最大候选数开始尝试，检查倍数关系，并利用前缀和进行可行性剪枝。

### 解决难点
- **候选数生成**：需高效枚举所有可能的p^i q^j，避免数值溢出。
- **倍数关系判断**：每选一个数后，需确保后续选择的数不与已选数成倍数。
- **剪枝优化**：前缀和剪枝大幅减少无效搜索路径，避免超时。

### 搜索过程可视化设计
- **节点表示**：每个候选数为一个节点，颜色区分已选/未选。
- **动画展示**：实时显示当前选择的数、剩余值、剪枝条件触发。
- **步进控制**：允许单步执行，观察DFS的回溯过程。
- **颜色标记**：红色表示当前选中数，绿色为合法候选，灰色为被剪枝。

## 题解评分与亮点
无现有题解，需自行实现DFS+剪枝策略。

## 最优思路提炼
1. **降序候选数**：优先尝试大数，快速逼近n。
2. **倍数关系剪枝**：维护已选集合，确保新增数不与之成倍数。
3. **前缀和剪枝**：提前终止无法凑出剩余值的分支。

## 同类型题推荐
1. **洛谷P1036**（子集和问题）
2. **洛谷P1092**（剪枝搜索）
3. **洛谷P2327**（数论+DFS）

## 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<ll> ans;
vector<ll> candidates;
vector<ll> prefix;
ll p, q, n;

bool dfs(int idx, ll s, vector<ll>& path) {
    if (s == 0) {
        ans = path;
        return true;
    }
    for (int i = idx; i < candidates.size(); ++i) {
        ll x = candidates[i];
        if (x > s) continue;
        bool valid = true;
        for (ll y : path) {
            if (x % y == 0 || y % x == 0) {
                valid = false;
                break;
            }
        }
        if (!valid) continue;
        if (prefix[i] < s) continue; // 剪枝
        path.push_back(x);
        if (dfs(i + 1, s - x, path)) return true;
        path.pop_back();
    }
    return false;
}

void solve() {
    ans.clear();
    candidates.clear();
    // 生成候选数
    for (ll i = 0, pow_p = 1; ; pow_p *= p, ++i) {
        if (pow_p > n) break;
        for (ll j = 0, pow_q = 1; ; pow_q *= q, ++j) {
            ll val = pow_p * pow_q;
            if (val > n) break;
            if (i + j >= 1) candidates.push_back(val);
            if (pow_q > n / q) break; // 防止溢出
        }
        if (i > 0 && pow_p > n / p) break;
    }
    // 去重并排序
    sort(candidates.rbegin(), candidates.rend());
    candidates.erase(unique(candidates.begin(), candidates.end()), candidates.end());
    // 计算前缀和
    prefix.assign(candidates.size(), 0);
    if (!candidates.empty()) {
        prefix.back() = candidates.back();
        for (int i = candidates.size() - 2; i >= 0; --i)
            prefix[i] = prefix[i + 1] + candidates[i];
    }
    // DFS
    vector<ll> path;
    dfs(0, n, path);
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> p >> q;
        solve();
        for (size_t i = 0; i < ans.size(); ++i) {
            if (i) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }
    return 0;
}
```

## 可视化设计要点
- **8位像素风格**：候选数以像素方块表示，选中时闪烁。
- **动画效果**：Canvas绘制候选数队列，绿色表示合法选择。
- **音效触发**：选中数时播放8位音效，成功时播放胜利旋律。
- **自动演示**：AI模式自动选择候选数，展示DFS的决策过程。

---
处理用时：1371.23秒