# 题目信息

# [ARC159D] LIS 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc159/tasks/arc159_d

数列 $ X $ があります。初め、$ X $ は空です。  
 高橋君は $ i=1,2,\ldots,N $ の順に次の操作をしました。

- $ X $ の末尾に $ l_i,l_i+1,\ldots,r_i $ をこの順番で追加する。
 
操作後の $ X $ の狭義単調増加部分列の長さの最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ l_i\ \leq\ r_i\ \leq\ 10^9 $
- 入力はすべて整数
 
### Sample Explanation 1

操作後の $ X $ は $ (1,2,3,4,10,11,7,8,9,10) $ です。 この数列の $ 1,2,3,4,7,8,9,10 $ 項目からなる部分列は狭義単調増加であり、かつこれが長さが最大のものです。

### Sample Explanation 2

操作後の $ X $ は $ (1,1,1,1) $ です。

## 样例 #1

### 输入

```
4

1 1

2 4

10 11

7 10```

### 输出

```
8```

## 样例 #2

### 输入

```
4

1 1

1 1

1 1

1 1```

### 输出

```
1```

## 样例 #3

### 输入

```
1

1 1000000000```

### 输出

```
1000000000```

# AI分析结果



**唯一算法分类**: 动态规划（线段树优化）

---

### **题解思路与算法要点**

1. **核心思路**  
   - **状态定义**: 设 `dp[i]` 表示以第 `i` 次操作结尾的 `r_i` 为末尾的最长严格递增子序列（LIS）长度。  
   - **转移方程**:  
     - **无交集**: 若之前区间的 `r_j < l_i`，则当前区间可完整拼接，贡献为 `dp[j] + (r_i - l_i + 1)`。  
     - **有交集**: 若 `r_j ≥ l_i`，则只能拼接 `r_j + 1` 至 `r_i` 部分，贡献为 `dp[j] + (r_i - r_j)`。  
     - 最终转移方程：  
       ```  
       dp[i] = max( max_{r_j < l_i} (dp[j] + r_i - l_i + 1), max_{r_j ≥ l_i} (dp[j] - r_j) + r_i )  
       ```

2. **数据结构优化**  
   - **线段树维护**：使用两棵线段树分别维护：  
     - `Tree1`：维护 `dp[j]` 的最大值（用于无交集的 `r_j < l_i` 情况）。  
     - `Tree2`：维护 `dp[j] - r_j` 的最大值（用于有交集的 `r_j ≥ l_i` 情况）。  
   - **离散化**：将 `l_i` 和 `r_i` 离散化以适配线段树的数值范围。

3. **关键难点**  
   - **离散化处理**：需正确离散化 `l_i` 和 `r_i`，确保线段树查询的区间边界正确。  
   - **线段树初始化**：初始插入虚拟节点 `j=0` 以处理首个区间。  
   - **边界条件**：例如 `r_j < l_i` 时的查询范围需为 `[1, l_i-1]`。

---

### **题解评分 (≥4星)**

1. **良心WA题人 (★★★★☆)**  
   - **亮点**：代码结构清晰，两棵线段树明确分离逻辑，离散化处理完整。  
   - **优化**：动态维护 `f[i]` 和 `f[i]-r_i` 的最大值，时间复杂度严格 `O(n log n)`。

2. **Iratis (★★★★☆)**  
   - **亮点**：代码简洁，直接贴出关键转移逻辑，省略冗余步骤。  
   - **技巧**：使用 `lower_bound` 快速离散化，线段树查询范围处理精准。

3. **namelessgugugu (★★★★☆)**  
   - **亮点**：贪心策略维护区间集合，无需离散化，思维新颖。  
   - **实现**：利用 `set` 合并区间，时间复杂度稳定 `O(n log n)`。

---

### **最优思路与技巧提炼**

1. **动态规划优化**  
   - **状态设计**：以区间末尾 `r_i` 为关键点，避免处理连续区间内部细节。  
   - **分治转移**：将转移拆分为无交集和有交集两种情况，分别用线段树维护。

2. **离散化与线段树**  
   - **离散化方法**：将所有 `l_i` 和 `r_i` 排序去重后映射到连续整数。  
   - **线段树操作**：单点更新与区间查询最大值，复杂度 `O(log n)`。

3. **贪心策略**  
   - **区间合并**：通过 `set` 维护递增区间，动态调整重叠部分，减少冗余计算。

---

### **相似题目推荐**

1. **LeetCode 354. Russian Doll Envelopes**  
   - **标签**：二维 LIS，排序 + 贪心/动态规划。  
   - **关联点**：类似的分治优化思路，需处理多维约束。

2. **洛谷 P1020 导弹拦截**  
   - **标签**：经典 LIS 及贪心解法。  
   - **关联点**：动态规划与贪心策略的对比。

3. **洛谷 P4303 [AHOI2006]基因匹配**  
   - **标签**：LCS 问题，数据结构优化。  
   - **关联点**：离散化与线段树维护区间最大值。

---

### **可视化设计思路**

1. **算法演示**  
   - **线段树更新**：用动画展示每次插入新区间时，两棵线段树的更新过程。  
   - **颜色标记**：高亮当前操作的 `l_i` 和 `r_i`，以及线段树中查询的区间。  

2. **复古像素风格**  
   - **Canvas 绘制**：以网格表示线段树节点，不同颜色区分 `Tree1` 和 `Tree2`。  
   - **音效触发**：插入区间时播放“点击”音效，查询时播放“扫描”音效。  

3. **交互功能**  
   - **步进控制**：允许单步执行，观察每个操作后的线段树状态。  
   - **自动演示**：AI 模式自动执行，展示最优解的生成过程。

---

### **核心代码片段（良心WA题人）**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int NN=2e5+4;
int f[NN],l[NN],r[NN];
struct node {
    struct segment_tree { int l, r, v; } tr[NN<<3];
    void pushup(int u) { tr[u].v = max(tr[u<<1].v, tr[u<<1|1].v); }
    void build(int u, int l, int r) {
        tr[u] = {l, r, 0};
        if (l == r) { tr[u].v = -1e9; return; }
        int mid = l + (r-l)/2;
        build(u<<1, l, mid); build(u<<1|1, mid+1, r);
        pushup(u);
    }
    void modify(int u, int p, int v) {
        if (tr[u].l == tr[u].r) { tr[u].v = max(tr[u].v, v); return; }
        int mid = tr[u].l + (tr[u].r - tr[u].l)/2;
        if (p <= mid) modify(u<<1, p, v);
        else modify(u<<1|1, p, v);
        pushup(u);
    }
    int query(int u, int l, int r) {
        if (tr[u].l >= l && tr[u].r <= r) return tr[u].v;
        int mid = tr[u].l + (tr[u].r - tr[u].l)/2, res = -1e9;
        if (l <= mid) res = max(res, query(u<<1, l, r));
        if (r > mid) res = max(res, query(u<<1|1, l, r));
        return res;
    }
} A, B;

signed main() {
    int n; scanf("%lld", &n);
    vector<int> nums;
    for (int i=1; i<=n; i++) {
        scanf("%lld%lld", &l[i], &r[i]);
        nums.push_back(l[i]); nums.push_back(r[i]);
    }
    nums.push_back(0); // 虚拟节点 j=0
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    A.build(1, 1, nums.size()); B.build(1, 1, nums.size());
    A.modify(1, 1, 0); B.modify(1, 1, 0); // 初始化 j=0
    int ans=0;
    for (int i=1; i<=n; i++) {
        int pl = lower_bound(nums.begin(), nums.end(), l[i]) - nums.begin() +1;
        int pr = lower_bound(nums.begin(), nums.end(), r[i]) - nums.begin() +1;
        // 查询两种情况的最大值
        int val1 = A.query(1, 1, pl-1) + (r[i] - l[i] +1);
        int val2 = B.query(1, pl, pr) + r[i];
        f[i] = max(val1, val2);
        ans = max(ans, f[i]);
        // 更新线段树
        A.modify(1, pr, f[i]);
        B.modify(1, pr, f[i] - r[i]);
    }
    printf("%lld", ans);
    return 0;
}
```

---

### **个人心得摘录**

- **初始化陷阱**：虚拟节点 `j=0` 的插入至关重要，否则首个区间无法正确处理。  
- **离散化细节**：需将所有 `l_i` 和 `r_i` 加入离散化数组，避免查询越界。  
- **边界检查**：线段树查询时需处理 `l > r` 的情况，否则会导致逻辑错误。

---
处理用时：137.39秒