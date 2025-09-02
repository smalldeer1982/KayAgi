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



### 唯一算法分类
线段树 + 区间覆盖

---

### 题解思路、算法要点与解决难点

#### 核心思路
所有船的成本公式为 `左港权值 * 右港距离`，拆分为两个部分：
1. **左港权值 * 右港坐标** → 线段树区间覆盖固定值
2. **-左港权值 * 当前位置** → 线段树区间覆盖等差数列

#### 解决难点
1. **动态分割区间**：插入新港口时，需要找到相邻港口，切割原有区间，并更新左右区间的表达式。
2. **高效维护拆分项**：用线段树维护两个独立表达式（固定值项和等差数列项），通过区间覆盖和求和快速计算。
3. **数据结构选择**：使用 `set` 快速查询前驱/后继港口，线段树支持区间覆盖和区间求和。

---

### 题解评分（≥4星）

1. **EuphoricStar（5星）**
   - **思路清晰**：明确拆分表达式为两个部分，分别用线段树处理。
   - **实现高效**：时间复杂度 $O((m+q)\log n)$，代码简洁。
   - **关键代码**：
     ```cpp
     // 拆分为两个线段树，分别维护固定值项和等差数列项
     update_fixed(l, r, y_i * x_next); // 固定值覆盖
     update_linear(l, r, -y_i);        // 等差数列覆盖
     ```

2. **OldDriverTree（4星）**
   - **直观模型**：维护每个区间的首项和公差，直接覆盖等差数列。
   - **代码可读性**：显式维护首项和公差的懒标记。
   - **关键代码**：
     ```cpp
     // 区间覆盖等差数列
     modify_segment(l, r, a, d); // a为首项，d为公差
     ```

3. **SunsetLake（4星）**
   - **分治思想**：将每段港口间区域视为独立单元，单独维护总和。
   - **优化技巧**：预处理初始区间的总和，插入时仅修改相邻区间的贡献。

---

### 最优思路或技巧提炼

1. **表达式拆分**：将复杂公式拆分为可独立维护的项（固定值 + 等差数列）。
2. **set + 线段树**：用 `set` 维护动态港口位置，线段树处理区间更新。
3. **懒标记设计**：线段树的懒标记需支持区间覆盖固定值和等差数列。

---

### 同类型题推荐

1. **[P3372 线段树1](https://www.luogu.com.cn/problem/P3372)**：区间加与区间求和。
2. **[P3373 线段树2](https://www.luogu.com.cn/problem/P3373)**：区间加、乘与求和。
3. **[CF52C Circular RMQ](https://codeforces.com/problemset/problem/52/C)**：环形区间加减与最小值查询。

---

### 可视化与算法演示

#### 核心动画设计
1. **线段树节点状态**：
   - **颜色标记**：绿色表示固定值覆盖，蓝色表示等差数列覆盖。
   - **高亮变化**：插入港口时，高亮被切割的区间和新生成的线段树节点。

2. **动态港口插入**：
   - **前驱/后继查询**：用 `set` 显示当前港口位置，插入时展示 `lower_bound` 操作。
   - **区间切割**：动画展示原有区间被分割为三段，并更新线段树的覆盖标记。

3. **复古像素风格**：
   - **Canvas 网格**：每个线段树节点表示为像素块，颜色区分覆盖类型。
   - **音效触发**：插入港口时播放“切割”音效，查询时播放“计算完成”音效。

#### 交互式控制
- **步进执行**：允许单步执行插入或查询操作，观察线段树节点的更新。
- **速度调节**：滑动条控制动画速度，适应不同学习节奏。

---

### 代码片段（核心逻辑）

#### EuphoricStar 题解关键实现
```cpp
set<int> harbors; // 维护港口位置
struct SegmentTree {
    struct Node {
        ll sum, fixed, slope; // 固定值项和斜率项
        bool is_fixed, is_slope; // 懒标记类型
    } tree[N<<2];

    void push_down(int node, int l, int r) {
        int mid = (l + r) >> 1;
        if (tree[node].is_fixed) {
            // 下传固定值标记
            update_fixed(l, mid, tree[node].fixed);
            update_fixed(mid+1, r, tree[node].fixed);
            tree[node].is_fixed = false;
        }
        if (tree[node].is_slope) {
            // 下传等差数列标记
            update_slope(l, mid, tree[node].slope);
            update_slope(mid+1, r, tree[node].slope);
            tree[node].is_slope = false;
        }
    }

    void update_range(int l, int r, ll fixed_val, ll slope_val) {
        // 同时更新固定值和斜率项
        // ...
    }
};
```

---

### 个人心得摘录

> "**拆公式是突破口**：将看似复杂的乘积拆分为可维护的独立项，问题迎刃而解。调试时重点关注区间边界是否正确切割。" —— EuphoricStar

> "**set 的 lower_bound 是关键**：动态维护有序港口位置，必须确保插入后前驱/后继查询的准确性。" —— SunsetLake

---

### 复古游戏化设计（示例）

```javascript
// 伪代码：Canvas 绘制线段树节点
function drawNode(x, y, type) {
    ctx.fillStyle = type === 'fixed' ? '#8BC34A' : '#2196F3';
    ctx.fillRect(x * 30, y * 30, 28, 28); // 像素块
}

// 音效触发
function playSound(effect) {
    const sfx = {
        cut: new Audio('data:audio/wav;base64,UklGRl9...'), // 切割音效
        query: new Audio('data:audio/wav;base64,UklGRl...')
    };
    sfx[effect].play();
}
```

---

### 总结
本题的核心在于动态维护区间表达式，通过拆分公式和高效数据结构（`set` + 线段树）实现快速更新与查询。可视化设计应突出区间切割与标记下传过程，帮助理解动态维护的机制。

---
处理用时：80.57秒