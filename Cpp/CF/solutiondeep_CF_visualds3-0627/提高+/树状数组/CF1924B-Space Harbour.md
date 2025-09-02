# 题目信息

# Space Harbour

## 题目描述

There are $ n $ points numbered $ 1 $ to $ n $ on a straight line. Initially, there are $ m $ harbours. The $ i $ -th harbour is at point $ X_i $ and has a value $ V_i $ . It is guaranteed that there are harbours at the points $ 1 $ and $ n $ . There is exactly one ship on each of the $ n $ points. The cost of moving a ship from its current location to the next harbour is the product of the value of the nearest harbour to its left and the distance from the nearest harbour to its right. Specifically, if a ship is already at a harbour, the cost of moving it to the next harbour is $ 0 $ .

Additionally, there are $ q $ queries, each of which is either of the following $ 2 $ types:

- $ 1 $ $ x $ $ v $ — Add a harbour at point $ x $ with value $ v $ . It is guaranteed that before adding the harbour, there is no harbour at point $ x $ .
- $ 2 $ $ l $ $ r $ — Print the sum of the cost of moving all ships at points from $ l $ to $ r $ to their next harbours. Note that you just need to calculate the cost of moving the ships but not actually move them.

## 说明/提示

For the first type $ 2 $ query, the cost for ships at positions $ 2 $ , $ 3 $ , $ 4 $ and $ 5 $ are $ 3(3 \times 1) $ , $ 0 $ , $ 96(24 \times 4) $ and $ 72(24 \times 3) $ respectively.

For the second type $ 2 $ query, since the ship at position $ 5 $ is already at a harbour, so the cost is $ 0 $ .

For the third type $ 2 $ query, the cost for ships at position $ 7 $ and $ 8 $ are $ 15(15 \times 1) $ and $ 0 $ respectively.

## 样例 #1

### 输入

```
8 3 4
1 3 8
3 24 10
2 2 5
1 5 15
2 5 5
2 7 8```

### 输出

```
171
0
15```

# AI分析结果



### 算法分类
**线段树 + 区间维护**

---

### 题解思路与解决难点
#### 核心思路
1. **港口分割区间**：相邻港口间的点构成独立区间，每个点的贡献可拆分为 `左港口价值 * 右港口距离`。
2. **动态维护区间**：插入新港口时，将原有区间拆分为左右两个新区间，并更新对应的贡献计算。
3. **线段树优化**：通过线段树维护区间乘积和等差数列，支持区间覆盖和快速查询。

#### 关键难点
1. **动态区间拆分**：插入港口时需要快速找到左右相邻港口，确定受影响的区间。
2. **标记下传与合并**：线段树需处理多个标记（如首项、公差、区间覆盖值），需精确计算区间贡献变化。
3. **公式拆解优化**：将贡献公式拆分为线性组合，便于用线段树维护两个独立部分的和。

---

### 题解评分（≥4星）
1. **EuphoricStar（5星）**  
   - 思路清晰，拆解公式为两个独立部分，用线段树区间覆盖高效维护。
   - 代码简洁，时间复杂度稳定为 `O((m+q) log n)`。
2. **SunsetLake（4星）**  
   - 维护每个港口的 `val` 和 `dis` 标记，直观体现贡献拆分。
   - 通过线段树懒标记处理区间加减和覆盖。
3. **OldDriverTree（4星）**  
   - 用线段树维护等差数列首项和公差，支持区间覆盖和求和。
   - 利用 `set` 快速定位港口，逻辑清晰。

---

### 最优思路提炼
1. **公式拆解**：贡献公式 `V_l * (r - x)` 拆为 `V_l * r - V_l * x`，分别维护两个部分的和。
2. **线段树双标记**：
   - 维护 `V_l * r` 的总和（区间覆盖值）。
   - 维护 `V_l` 的总和，结合区间坐标和计算 `V_l * x`。
3. **动态分割区间**：用 `set` 维护港口位置，快速找到插入点前后的港口，分割并更新区间。

---

### 类似题目推荐
1. **[CF522D Closest Equals](https://www.luogu.com.cn/problem/CF522D)**  
   - 动态维护区间最小值，结合离线查询。
2. **[P3372 线段树1](https://www.luogu.com.cn/problem/P3372)**  
   - 基础线段树模板，练习区间加减和求和。
3. **[P5490 扫描线](https://www.luogu.com.cn/problem/P5490)**  
   - 处理区间覆盖与合并，类似港口分割思路。

---

### 代码核心实现
```cpp
// 线段树节点结构
struct Node {
    int l, r;
    ll sum_vr; // Σ(V_l * r)
    ll sum_v;  // Σ(V_l)
    ll tag_vr, tag_v; // 覆盖标记
};

// 区间覆盖操作
void update(int u, int l, int r, ll vr, ll v) {
    if (tr[u].l > r || tr[u].r < l) return;
    if (l <= tr[u].l && tr[u].r <= r) {
        tr[u].sum_vr = vr * (tr[u].r - tr[u].l + 1);
        tr[u].sum_v = v * (tr[u].r - tr[u].l + 1);
        tr[u].tag_vr = vr;
        tr[u].tag_v = v;
        return;
    }
    pushdown(u);
    update(ls, l, r, vr, v);
    update(rs, l, r, vr, v);
    pushup(u);
}

// 插入港口逻辑
void insert_harbor(int x, int v) {
    auto it = st.lower_bound(x);
    int r = *it, l = *--it;
    update(1, l+1, x-1, v * x, v); // 更新左区间
    update(1, x+1, r-1, v * r, v); // 更新右区间
    st.insert(x);
}
```

---

### 可视化设计
#### 算法演示
1. **Canvas 动态绘制**：
   - **线段树结构**：以网格展示线段树节点，高亮当前操作的区间。
   - **港口位置**：用不同颜色标记港口，插入时显示分割动画。
2. **像素风格**：
   - **8位色板**：线段树节点用绿色（正常）、红色（覆盖中），港口用黄色方块。
   - **音效**：插入港口时播放“滴”声，查询时播放“嘟”声。

#### 交互功能
- **步进控制**：按钮控制执行插入/查询，观察线段树节点更新。
- **自动模式**：AI 自动插入随机港口，展示动态分割过程。

---

### 复古游戏化实现
```javascript
// 示例：Canvas 绘制线段树
function drawSegmentTree() {
    ctx.fillStyle = "#2C3E50"; // 背景色
    ctx.fillRect(0, 0, canvas.width, canvas.height);
    nodes.forEach(node => {
        ctx.fillStyle = node.highlight ? "#E74C3C" : "#27AE60";
        ctx.fillRect(node.x, node.y, node.w, node.h);
        ctx.fillText(node.sum, node.x + 5, node.y + 15);
    });
}

// 音效触发
function playSound(effect) {
    const sfx = {
        insert: [520, 0.2], query: [660, 0.3]
    };
    oscillator.frequency.setValueAtTime(sfx[effect][0], audioCtx.currentTime);
    gain.gain.setValueAtTime(sfx[effect][1], audioCtx.currentTime);
}
```

---

### 总结
通过线段树维护动态区间贡献，结合 `set` 快速定位港口，实现高效更新与查询。拆解公式为线性组合简化计算，复古可视化增强理解，适合算法教学与竞赛训练。

---
处理用时：94.69秒