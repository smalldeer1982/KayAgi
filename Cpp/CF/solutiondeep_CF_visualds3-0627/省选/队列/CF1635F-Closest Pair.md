# 题目信息

# Closest Pair

## 题目描述

There are $ n $ weighted points on the $ OX $ -axis. The coordinate and the weight of the $ i $ -th point is $ x_i $ and $ w_i $ , respectively. All points have distinct coordinates and positive weights. Also, $ x_i < x_{i + 1} $ holds for any $ 1 \leq i < n $ .

The weighted distance between $ i $ -th point and $ j $ -th point is defined as $ |x_i - x_j| \cdot (w_i + w_j) $ , where $ |val| $ denotes the absolute value of $ val $ .

You should answer $ q $ queries, where the $ i $ -th query asks the following: Find the minimum weighted distance among all pairs of distinct points among the points in subarray $ [l_i,r_i] $ .

## 说明/提示

For the first query, the minimum weighted distance is between points $ 1 $ and $ 3 $ , which is equal to $ |x_1 - x_3| \cdot (w_1 + w_3) = |-2 - 1| \cdot (2 + 1) = 9 $ .

For the second query, the minimum weighted distance is between points $ 2 $ and $ 3 $ , which is equal to $ |x_2 - x_3| \cdot (w_2 + w_3) = |0 - 1| \cdot (10 + 1) = 11 $ .

For the fourth query, the minimum weighted distance is between points $ 3 $ and $ 4 $ , which is equal to $ |x_3 - x_4| \cdot (w_3 + w_4) = |1 - 9| \cdot (1 + 2) = 24 $ .

## 样例 #1

### 输入

```
5 5
-2 2
0 10
1 1
9 2
12 7
1 3
2 3
1 5
3 5
2 4```

### 输出

```
9
11
9
24
11```

# AI分析结果



---

## **算法分类**
**离线处理 + 树状数组/线段树**

---

## **题解思路与核心难点**
### **核心思路**
所有题解的核心思路基于以下关键结论：**最优点对只能是每个点与其左右最近的权重更小的点**。通过单调栈预处理每个点的左右邻居（L_i和R_i），得到O(n)个候选点对。离线处理查询，按右端点排序，利用树状数组维护左端点的最小值。

### **解决难点**
1. **候选点对的推导**  
   反证法证明：若存在更优的点对，则必然能找到更近的点对，矛盾。这确保了只需考虑O(n)个点对。
2. **高效预处理L_i和R_i**  
   使用单调栈维护递增序列，确保每个点的左右最近较小权重点在O(n)时间内找到。
3. **离线查询处理**  
   将查询按右端点排序，扫描时动态维护候选点对的最小值，树状数组优化查询为O(log n)。

### **可视化设计**
- **单调栈预处理动画**：  
  动态显示每个点入栈出栈过程，高亮当前处理的点i及其对应的L_i/R_i。
- **树状数组更新与查询**：  
  逐步插入候选点对的权值，颜色标记当前处理的右端点及对应的查询区间。
- **复古像素风格**：  
  用8位网格显示点坐标，栈操作时播放经典音效，树状数组更新时显示像素块变化。

---

## **题解评分（≥4星）**
1. **GaryH（5星）**  
   详细推导结论，代码清晰，实践性强。
2. **Tyyyyyy（4星）**  
   代码简洁，预处理和查询分离明确。
3. **yzy1（4星）**  
   实现完整，注释详细，适合学习。

---

## **最优技巧提炼**
1. **单调栈预处理邻居**  
   维护递增栈，快速找到每个点的左右最近较小权重点。
2. **离线扫描与树状数组结合**  
   将二维区间查询转化为一维后缀最小值问题，利用树状数组高效维护。
3. **反证法证明候选点对**  
   通过逻辑推导减少候选点对数量，复杂度从O(n²)降至O(n)。

---

## **同类型题推荐**
- **二维数点**：CF522D、P1972  
- **离线区间最值**：P2163、P4113  
- **单调栈应用**：LC 84（柱状图中最大矩形）

---

## **推荐洛谷题目**
1. **P1972 [SDOI2009]HH的项链**  
   （离线+树状数组统计区间不同元素）
2. **P2163 [SHOI2007]园丁的烦恼**  
   （二维数点离线处理）
3. **P5490 【模板】扫描线**  
   （区间统计的经典扫描线方法）

---

## **个人心得摘录**
- **渔歌**：  
  “最开始以为x无序，导致思路错误，后来发现x有序才解决——注意题目条件是解题关键！”
- **dead_X**：  
  “调试时发现未处理右端点的边界情况，需注意栈空时的默认值。”

---

## **核心算法代码**
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5 + 10;
const ll INF = 1e18;

int n, q, x[N], w[N], L[N], R[N];
vector<pair<int, int>> queries[N];
vector<int> pairs[N];
ll ans[N];

struct BIT {
    ll tree[N];
    void init() { fill(tree, tree + N, INF); }
    void update(int x, ll v) {
        for (; x > 0; x -= x & -x) 
            tree[x] = min(tree[x], v);
    }
    ll query(int x) {
        ll res = INF;
        for (; x <= n; x += x & -x)
            res = min(res, tree[x]);
        return res;
    }
} bit;

int main() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> x[i] >> w[i];
    
    // 预处理L[i]
    stack<int> stk;
    for (int i = 1; i <= n; i++) {
        while (!stk.empty() && w[stk.top()] > w[i]) stk.pop();
        L[i] = stk.empty() ? 0 : stk.top();
        stk.push(i);
    }
    
    // 预处理R[i]
    stk = stack<int>();
    for (int i = n; i >= 1; i--) {
        while (!stk.empty() && w[stk.top()] > w[i]) stk.pop();
        R[i] = stk.empty() ? 0 : stk.top();
        stk.push(i);
    }

    // 生成候选点对
    for (int i = 1; i <= n; i++) {
        if (L[i]) pairs[i].push_back(L[i]);
        if (R[i]) pairs[R[i]].push_back(i);
    }

    // 处理查询
    for (int i = 1; i <= q; i++) {
        int l, r; cin >> l >> r;
        queries[r].emplace_back(l, i);
    }

    bit.init();
    for (int r = 1; r <= n; r++) {
        for (int l : pairs[r]) {
            ll val = 1LL * (x[r] - x[l]) * (w[r] + w[l]);
            bit.update(l, val);
        }
        for (auto [l, id] : queries[r]) 
            ans[id] = bit.query(l);
    }

    for (int i = 1; i <= q; i++) 
        cout << ans[i] << "\n";
    return 0;
}
```

---

## **可视化算法演示**
### **动画设计**
1. **单调栈预处理**  
   - 像素网格显示点坐标，红色高亮当前点i。
   - 栈内元素用绿色标记，弹出元素时播放“哔”音效。
2. **树状数组更新**  
   - 插入候选点对时，黄色标记插入位置，树状数组对应节点变蓝。
3. **查询处理**  
   - 当前右端点用紫色标记，查询区间显示为橙色框，结果用闪烁提示。

### **交互功能**
- **速度调节**：滑动条控制动画速度（0.5x~3x）。
- **模式切换**：手动步进/Auto模式（自动播放）。
- **音效开关**：启用/禁用操作音效。

### **复古风格**
- **8位调色板**：16色，像素化坐标轴和数据结构。
- **背景音乐**：循环播放FC经典BGM，操作音效为8位风格。

---

通过此设计，学习者可直观理解候选点对的生成与查询处理，深入掌握离线+树状数组的经典套路。

---
处理用时：147.19秒