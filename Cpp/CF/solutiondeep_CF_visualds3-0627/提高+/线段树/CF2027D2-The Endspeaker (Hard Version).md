# 题目信息

# The Endspeaker (Hard Version)

## 题目描述

这是这道题目的困难版本。与简单版本的区别在于，你还需要输出达到最优解的操作序列数量。你需要解决这两种版本才能进行 hack。

现在给定一个数组 $ a $，长度为 $ n $，以及一个数组 $ b $，长度为 $ m $（保证 $ b_i > b_{i+1} $ 对所有 $ 1 \le i < m $ 成立）。初始时，$ k $ 的值为 $ 1 $。你的目标是通过执行以下两种操作之一反复将数组 $ a $ 变为空：

- 类型 $ 1 $ 操作 — 在 $ k < m $ 且数组 $ a $ 不为空时，你可以将 $ k $ 的值加 $ 1 $。这种操作不需要花费任何代价。
- 类型 $ 2 $ 操作 — 你可以移除数组 $ a $ 的一个非空前缀，使得这个前缀的和不大于 $ b_k $。这种操作的代价为 $ m - k $。

你需要让将数组 $ a $ 变为空的总操作代价最小化。如果无法通过任何操作序列达到这一目标，请输出 $ -1 $。否则，输出最小总操作代价以及产生命中该代价的操作序列数量，对 $ 10^9 + 7 $ 取模。

若两个操作序列在任一步骤中选择了不同种类的操作，或移除前缀的大小不同，则它们视为不同。

## 说明/提示

以下为一个测试用例的示例，其中最优操作序列的总费用为 $ 1 $，共有 $ 3 $ 种：

- 所有这 $ 3 $ 种序列都以类型 $ 2 $ 的操作开头，移除前缀 $ [9] $，使得 $ a = [3, 4, 3] $，产生代价 $ 1 $。然后执行类型 $ 1 $ 操作，把 $ k $ 提升一位，此后所有操作均无代价。
- 一种序列依次移除前缀 $ [3, 4] $ 和 $ [3] $。
- 另一种序列依次移除前缀 $ [3] $ 和 $ [4, 3] $。
- 还有一种序列依次移除前缀 $ [3] $，再移除 $ [4] $，最后移除 $ [3] $。

在第二个测试用例中，由于 $ a_1 > b_1 $，无法移除任何前缀，因此无论如何都无法使数组 $ a $ 变为空。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
4 2
9 3 4 3
11 7
1 2
20
19 18
10 2
2 5 2 1 10 3 2 9 9 6
17 9
10 11
2 2 2 2 2 2 2 2 2 2
20 18 16 14 12 10 8 6 4 2 1
1 6
10
32 16 8 4 2 1```

### 输出

```
1 3
-1
2 11
10 42
4 1```

# AI分析结果



---

**唯一算法分类**  
动态规划 + 线段树优化

---

### **题解思路与算法要点**

#### **核心思路**
1. **状态设计**：定义动态规划状态 `dp[i][j]` 表示当前 `k=i`，处理到数组 `a` 的第 `j` 个位置时的最小代价和对应方案数。
2. **转移方式**：
   - **类型1操作**：直接继承 `k+1` 的状态（无代价）。
   - **类型2操作**：对于每个位置 `j`，利用前缀和和二分查找找到最大可移除前缀终点 `to`，将代价 `m-i` 和方案数区间更新到 `[j+1, to]`。
3. **优化手段**：线段树维护区间最小代价及合并方案数，支持区间更新和单点查询，避免暴力遍历。

#### **解决难点**
- **快速确定前缀范围**：通过前缀和数组与二分查找，将每次查找 `to` 的时间降为 `O(log n)`。
- **方案数合并**：线段树节点存储最小代价和方案数，在区间更新时自动合并相同代价的方案数。
- **复杂度控制**：线段树优化使得总复杂度为 `O(nm log n)`，满足题目约束。

---

### **最优思路与技巧提炼**
1. **线段树的高效维护**  
   - **节点设计**：每个线段树节点存储当前区间的最小代价和对应的方案数。
   - **区间更新**：在类型2操作中，将 `dp[j] + m-i` 的值批量更新到区间 `[j+1, to]`，避免逐个更新。
   - **合并规则**：若新代价更小则覆盖，相等则累加方案数，否则忽略。
   
2. **滚动数组优化空间**  
   只需维护当前 `k` 和 `k+1` 的状态，空间复杂度降至 `O(n)`。

3. **前缀和与二分查找**  
   预处理 `a` 的前缀和数组，快速计算子数组和，并用二分查找确定最大可移除前缀终点 `to`。

---

### **题解评分 (≥4星)**

#### **Super_Cube (★★★★☆)**  
- **亮点**：线段树实现清晰，区间更新与合并逻辑完整，代码可读性较高。
- **代码片段**：
  ```cpp
  void upd(int p,int l,int r,const pli&x){
    if(t[p].l>=l&&t[p].r<=r)return t[p].v+=x;
    tag_down(p);
    int mid=t[p].l+t[p].r>>1;
    if(l<=mid)upd(p<<1,l,r,x);
    if(r>mid)upd(p<<1|1,l,r,x);
  }
  ```

#### **灵乌路空 (★★★★☆)**  
- **亮点**：双指针优化实现 `O(nm)` 复杂度，前缀和滚动数组减少空间占用。
- **代码片段**：
  ```cpp
  while (l <= r && sum[r] - sum[l - 1] > b[i]) ++l;
  if (l <= r) {
    r1 = std::max(r1, l - 1);
    while (r1 < r - 1 && f[now][r1 + 1] == f[now][l - 1]) ++r1;
  }
  ```

#### **CReatiQ (★★★★☆)**  
- **亮点**：模板化线段树设计，代码简洁易懂，直接面向问题建模。
- **代码片段**：
  ```cpp
  dp.rangeApply(i+1,to+1,{now.val+m-k,now.ways});
  ```

---

### **可视化与算法演示**

#### **动画方案设计**
1. **线段树动态更新**  
   - **颜色标记**：当前操作的 `k` 值用不同颜色表示，线段树节点颜色深浅反映代价大小。
   - **步进控制**：允许单步执行，观察每个 `k` 和 `j` 的更新过程。
   
2. **前缀和与二分查找**  
   - **高亮显示**：当前检查的区间 `[j, to]`，动态绘制二分查找过程。
   - **音效触发**：成功找到 `to` 时播放确认音效，失败时播放错误音效。

#### **复古像素风格实现**
- **Canvas 绘制**：用 8 位像素网格表示数组 `a` 和 `b`，线段树节点用方块表示，颜色区分代价层级。
- **音效设计**：
  - **区间更新**：短促“滴”声。
  - **找到最优解**：上扬音调。
  - **操作错误**：低音“哔”声。
- **自动演示模式**：AI 按最优路径自动执行，展示线段树更新和方案数合并过程。

---

### **同类型题推荐**
1. **CF977F Consecutive Subsequence**（动态规划 + 哈希优化）
2. **LeetCode 1326. Minimum Number of Taps to Open to Water a Garden**（贪心 + 区间覆盖）
3. **洛谷 P1886 滑动窗口**（单调队列优化）

---

### **核心代码实现**
```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef std::pair<ll, int> pli;
const ll inf = 0x3f3f3f3f3f3f3f3f;
const int mod = 1e9+7;

struct SegmentTree {
    struct Node { int l, r; pli val; };
    std::vector<Node> tree;
    void build(int p, int l, int r) {
        tree[p].l = l, tree[p].r = r;
        tree[p].val = {inf, 0};
        if (l == r) {
            if (l == 1) tree[p].val = {0, 1};
            return;
        }
        int mid = (l + r) >> 1;
        build(p<<1, l, mid);
        build(p<<1|1, mid+1, r);
    }
    void push_down(int p) {
        if (tree[p].val.first != inf) {
            tree[p<<1].val = merge(tree[p<<1].val, tree[p].val);
            tree[p<<1|1].val = merge(tree[p<<1|1].val, tree[p].val);
            tree[p].val = {inf, 0};
        }
    }
    pli merge(const pli &a, const pli &b) {
        if (a.first < b.first) return a;
        if (a.first > b.first) return b;
        return {a.first, (a.second + b.second) % mod};
    }
    void update(int p, int l, int r, const pli &v) {
        if (tree[p].l >= l && tree[p].r <= r) {
            tree[p].val = merge(tree[p].val, v);
            return;
        }
        push_down(p);
        int mid = (tree[p].l + tree[p].r) >> 1;
        if (l <= mid) update(p<<1, l, r, v);
        if (r > mid) update(p<<1|1, l, r, v);
    }
    pli query(int p, int pos) {
        if (tree[p].l == tree[p].r) return tree[p].val;
        push_down(p);
        int mid = (tree[p].l + tree[p].r) >> 1;
        if (pos <= mid) return query(p<<1, pos);
        else return query(p<<1|1, pos);
    }
};

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int n, m; scanf("%d%d", &n, &m);
        std::vector<ll> a(n+1), b(m+1);
        for (int i=1; i<=n; ++i) scanf("%lld", &a[i]), a[i] += a[i-1];
        for (int i=1; i<=m; ++i) scanf("%d", &b[i]);

        SegmentTree seg;
        seg.tree.resize(4*(n+2));
        seg.build(1, 1, n+1);

        pli ans = {inf, 0};
        for (int k=1; k<=m; ++k) {
            for (int j=1; j<=n; ++j) {
                auto val = seg.query(1, j);
                if (val.first == inf) continue;
                ll sum_limit = a[j-1] + b[k];
                int to = std::upper_bound(a.begin()+j, a.end(), sum_limit) - a.begin();
                if (to > j) {
                    val.first += m - k;
                    seg.update(1, j+1, to, val);
                    if (to == n+1) ans = seg.merge(ans, val);
                }
            }
        }
        if (ans.first == inf) puts("-1");
        else printf("%lld %d\n", ans.first, ans.second);
    }
    return 0;
}
```

---

**个人心得**  
- **线段树合并逻辑**：在区间更新时需仔细处理方案数合并，避免遗漏或重复计数。
- **前缀和边界**：注意前缀和数组的索引偏移，确保二分查找正确。

---
处理用时：134.24秒