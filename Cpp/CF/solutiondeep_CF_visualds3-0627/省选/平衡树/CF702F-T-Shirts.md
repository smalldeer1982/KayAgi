# 题目信息

# T-Shirts

## 题目描述

The big consignment of t-shirts goes on sale in the shop before the beginning of the spring. In all $ n $ types of t-shirts go on sale. The t-shirt of the $ i $ -th type has two integer parameters — $ c_{i} $ and $ q_{i} $ , where $ c_{i} $ — is the price of the $ i $ -th type t-shirt, $ q_{i} $ — is the quality of the $ i $ -th type t-shirt. It should be assumed that the unlimited number of t-shirts of each type goes on sale in the shop, but in general the quality is not concerned with the price.

As predicted, $ k $ customers will come to the shop within the next month, the $ j $ -th customer will get ready to spend up to $ b_{j} $ on buying t-shirts.

All customers have the same strategy. First of all, the customer wants to buy the maximum possible number of the highest quality t-shirts, then to buy the maximum possible number of the highest quality t-shirts from residuary t-shirts and so on. At the same time among several same quality t-shirts the customer will buy one that is cheaper. The customers don't like the same t-shirts, so each customer will not buy more than one t-shirt of one type.

Determine the number of t-shirts which each customer will buy, if they use the described strategy. All customers act independently from each other, and the purchase of one does not affect the purchase of another.

## 说明/提示

In the first example the first customer will buy the t-shirt of the second type, then the t-shirt of the first type. He will spend 10 and will not be able to buy the t-shirt of the third type because it costs 4, and the customer will owe only 3. The second customer will buy all three t-shirts (at first, the t-shirt of the second type, then the t-shirt of the first type, and then the t-shirt of the third type). He will spend all money on it.

## 样例 #1

### 输入

```
3
7 5
3 5
4 3
2
13 14
```

### 输出

```
2 3 
```

## 样例 #2

### 输入

```
2
100 500
50 499
4
50 200 150 100
```

### 输出

```
1 2 2 1 
```

# AI分析结果



### 算法分类
**平衡树 + 势能分析**

---

### 题解思路与核心难点

#### 核心思路
1. **排序处理**：将 T-Shirts 按品质降序、价格升序排序，确保优先处理高性价比商品。
2. **平衡树维护顾客预算**：用 FHQ Treap 或 Splay 维护所有顾客的预算，每次处理一个商品时：
   - 将顾客分为 `<c`、`[c, 2c)`、`≥2c` 三部分。
   - **≥2c 部分**：直接打标记减去 `c`。
   - **[c, 2c) 部分**：暴力删除节点，修改后重新插入平衡树。
3. **势能分析**：每个数被暴力处理次数为 O(log V)，总复杂度 O(n log n log V)。

#### 解决难点
- **平衡树合并冲突**：修改后的 `[c, 2c)` 部分可能破坏树的有序性，需暴力重构。
- **标记下传**：维护 `钱数减少标记` 和 `购买次数标记`，在 split/merge 时正确下传。

---

### 题解评分 (≥4星)

1. **tzc_wk (5星)**
   - **亮点**：完整实现 FHQ Treap，利用 `split` 三部分处理，代码简洁。
   - **代码**：关键函数 `dfsins` 处理暴力插入，标记下传逻辑清晰。

2. **hsfzLZH1 (4星)**
   - **亮点**：详细注释与平衡树操作分步拆解，适合初学者理解。
   - **技巧**：显式维护 `minu`（钱减少量）和 `tag`（购买次数）标记。

3. **Rainy_chen (4星)**
   - **亮点**：代码高度模块化，`del` 函数处理暴力插入，逻辑紧凑。
   - **优化**：复用节点内存池减少空间占用。

---

### 最优思路提炼

#### 关键步骤
1. **排序商品**：确保按策略购买。
2. **三区间拆分**：
   ```cpp
   split(rt, c-1, x, y); // <c 部分
   split(y, 2*c-1, y, z); // [c, 2c) 和 ≥2c 部分
   ```
3. **暴力插入中间区间**：
   ```cpp
   for (节点 in y) {
       y.val -= c; y.ans++;
       insert_into(x, y); // 插入到 <c 部分
   }
   ```

#### 势能分析
- **复杂度保证**：每次暴力插入使钱数至少减半，每个数最多处理 O(log V) 次。

---

### 类似题目推荐

1. **[CF1515I Phoenix and Diamonds](https://codeforces.com/problemset/problem/1515/I)**  
   - 动态维护物品集合，分块处理类似势能分析。

2. **[P8522 [Ynoi2077] hlcpq](https://www.luogu.com.cn/problem/P8522)**  
   - 结合线段树与分块思想处理高维查询。

3. **[CF1290E Cartesian Tree](https://codeforces.com/problemset/problem/1290/E)**  
   - 平衡树维护区间性质，动态调整结构。

---

### 代码核心片段

#### FHQ Treap 关键操作
```cpp
void dfsins(int x, int &y, int z) {
    if (!x) return;
    pushdown(x);
    dfsins(t[x].lc, y, z);
    dfsins(t[x].rc, y, z);
    t[x].lc = t[x].rc = 0;
    t[x].val -= z;
    t[x].ans++;
    insert(y, x); // 插入到新树
}

void solve(int c) {
    int x, y, z;
    split(rt, c-1, x, y);
    split(y, 2*c-1, y, z);
    if (z) apply_tag(z, -c, 1); // 标记处理
    dfsins(y, x, c); // 暴力插入中间部分
    rt = merge(x, z);
}
```

---

### 可视化设计

#### 动画方案
1. **平衡树分裂**：高亮三个区间：
   - `<c`：绿色，`[c, 2c)`：黄色，`≥2c`：红色。
2. **暴力插入**：黄色节点逐个飞入左侧树，伴随“金币减少”音效。
3. **标记下传**：红色节点闪烁，显示数值减少和计数增加。

#### 复古像素风格
- **颜色方案**：16 色调色板，树节点用 8x8 像素块表示。
- **音效**：使用 [Web Audio API](https://developer.mozilla.org/zh-CN/docs/Web/API/Web_Audio_API) 播放：
  - `split/merge`：短促“滴”声。
  - 购买成功：经典马里奥金币音效。

#### 交互控制
- **步进按钮**：允许单步执行 split/insert 操作。
- **速度调节**：滑动条控制动画速度（0.5x~3x）。

---

### 总结
通过平衡树维护动态集合，结合势能分析优化暴力操作，是解决此类问题的通用范式。核心在于分块处理与正确维护标记，确保复杂度的同时保持代码简洁。

---
处理用时：64.05秒