# 题目信息

# MEX Queries

## 题目描述

You are given a set of integer numbers, initially it is empty. You should perform $ n $ queries.

There are three different types of queries:

- 1 $ l $ $ r $ — Add all missing numbers from the interval $ [l,r] $
- 2 $ l $ $ r $ — Remove all present numbers from the interval $ [l,r] $
- 3 $ l $ $ r $ — Invert the interval $ [l,r] $ — add all missing and remove all present numbers from the interval $ [l,r] $

After each query you should output MEX of the set — the smallest positive (MEX $ >=1 $ ) integer number which is not presented in the set.

## 说明/提示

Here are contents of the set after each query in the first example:

1. $ {3,4} $ — the interval $ [3,4] $ is added
2. $ {1,2,5,6} $ — numbers $ {3,4} $ from the interval $ [1,6] $ got deleted and all the others are added
3. $ {5,6} $ — numbers $ {1,2} $ got deleted

## 样例 #1

### 输入

```
3
1 3 4
3 1 6
2 1 3
```

### 输出

```
1
3
1
```

## 样例 #2

### 输入

```
4
1 1 3
3 5 6
2 4 4
3 1 6
```

### 输出

```
4
4
4
1
```

# AI分析结果



# 算法分类  
**线段树 + 离散化**

---

# 题解思路与难点分析  

## 核心思路  
1. **离散化处理**  
   - 将操作涉及的端点 $l_i, r_i, r_i+1$ 和初始值 $1$ 离散化，映射到较小值域  
   - 确保离散化后包含所有可能影响 MEX 的临界点（如 $r_i+1$ 可能成为答案）  

2. **线段树维护区间状态**  
   - 维护三种标记：覆盖标记（赋 0/1）、翻转标记  
   - 每次操作通过标记下传更新区间状态  
   - 查询时递归检查左子树是否存在 0，快速定位 MEX  

3. **标记优先级处理**  
   - 覆盖标记优先级高于翻转标记  
   - 翻转操作需考虑当前标记状态，避免冲突  

## 解决难点  
- **大值域处理**：离散化将 $10^{18}$ 映射到 $O(n)$ 级别值域  
- **多标记冲突**：明确标记下传顺序，保证操作正确性  
- **高效查询**：利用线段树二分特性，实现 $O(\log n)$ 时间查询 MEX  

---

# 题解评分 (≥4星)  

1. **题解作者：傅思维666（4.5★）**  
   - 亮点：完整实现线段树+离散化，注释详细  
   - 关键代码：正确处理标记下传与翻转优先级  

2. **题解作者：Acestar（4.2★）**  
   - 亮点：离线离散化实现清晰，代码结构规范  
   - 优化：动态维护区间和与翻转状态  

3. **题解作者：Unnamed114514（4.0★）**  
   - 亮点：珂朵莉树暴力实现，代码极简  
   - 缺点：非随机数据可能退化为 $O(n)$  

---

# 最优思路提炼  

1. **离散化关键点**  
   - 包含所有操作端点及其相邻点（$l_i-1, r_i+1$）  
   - 必须包含初始值 1 作为离散化元素  

2. **线段树标记合并**  
   ```cpp  
   void pushdown(int p) {
       if (tag[p] == 1) { // 覆盖标记优先
           sum[ls] = len[ls], sum[rs] = len[rs];
           tag[ls] = tag[rs] = 1;
           rev[ls] = rev[rs] = 0;
       } else if (tag[p] == 0) { 
           sum[ls] = sum[rs] = 0;
           tag[ls] = tag[rs] = 0;
           rev[ls] = rev[rs] = 0;
       }
       if (rev[p]) { // 翻转标记
           sum[ls] = len[ls] - sum[ls];
           sum[rs] = len[rs] - sum[rs];
           rev[ls] ^= 1, rev[rs] ^= 1;
       }
       tag[p] = -1, rev[p] = 0;
   }
   ```  

3. **MEX 查询优化**  
   - 递归优先检查左子树是否全为 1，否则继续左子树  

---

# 类似题目推荐  
1. **[CF915E](https://www.luogu.com.cn/problem/CF915E)** - 动态区间赋值与计数  
2. **[P2574](https://www.luogu.com.cn/problem/P2574)** - 区间翻转与求和  
3. **[P3968](https://www.luogu.com.cn/problem/P3968)** - 动态开点平衡树维护区间  

---

# 可视化设计  

## 算法动画方案  
1. **Canvas 动态绘制线段树**  
   - **颜色标记**：  
     - 绿色：当前操作的区间  
     - 红色：覆盖标记（赋 1）  
     - 蓝色：翻转标记  
   - **节点高亮**：查询路径上的节点用黄色边框标注  

2. **复古像素风格**  
   - **8位调色板**：  
     - 背景：深蓝 (#2c3e50)  
     - 线段树节点框：浅灰 (#bdc3c7)  
     - 标记区域：橙 (#e67e22)  
   - **音效设计**：  
     - 覆盖操作：短促 "哔" 声  
     - 翻转操作：电子翻转音  
     - 找到 MEX：胜利音效  

3. **交互控制**  
   - 速度滑块调节动画速率  
   - 单步执行按钮观察标记下传细节  

## 核心代码片段  
```javascript  
class SegmentTreeViz {
  constructor(canvas) {
    this.ctx = canvas.getContext('2d');
    this.nodes = []; // 存储线段树节点坐标与状态
    this.highlightPath = []; // 当前查询路径
  }

  drawNode(node, color) {
    // 绘制节点矩形框与状态
    this.ctx.fillStyle = color;
    this.ctx.fillRect(node.x, node.y, 50, 30);
    this.ctx.strokeStyle = '#bdc3c7';
    this.ctx.strokeRect(node.x, node.y, 50, 30);
  }

  animateUpdate(l, r, type) {
    // 高亮操作区间并更新节点状态
    this.nodes.forEach(node => {
      if (node.l >= l && node.r <= r) {
        this.drawNode(node, '#e74c3c'); // 红色高亮
        applyMarkEffect(node, type);     // 应用标记动画
      }
    });
  }
}
```

---

# 代码实现  

## 关键代码（线段树 + 离散化）  
```cpp  
const int MAXN = 4e5 + 10;

struct Query { int op; ll l, r; } q[MAXN];
vector<ll> vals; // 离散化数组

struct Node {
    int sum, tag, rev; // tag: -1无,0赋0,1赋1; rev: 是否翻转
} tr[MAXN << 2];

void pushdown(int p, int l, int r) {
    int mid = (l + r) >> 1;
    if (tr[p].tag != -1) { // 处理覆盖标记
        tr[p<<1].sum = (tr[p].tag ? mid - l + 1 : 0);
        tr[p<<1|1].sum = (tr[p].tag ? r - mid : 0);
        tr[p<<1].tag = tr[p<<1|1].tag = tr[p].tag;
        tr[p<<1].rev = tr[p<<1|1].rev = 0;
    }
    if (tr[p].rev) { // 处理翻转
        tr[p<<1].sum = (mid - l + 1) - tr[p<<1].sum;
        tr[p<<1|1].sum = (r - mid) - tr[p<<1|1].sum;
        tr[p<<1].rev ^= 1, tr[p<<1|1].rev ^= 1;
    }
    tr[p].tag = -1, tr[p].rev = 0;
}

void update(int p, int l, int r, int ql, int qr, int op) {
    if (ql <= l && r <= qr) {
        if (op == 1 || op == 2) { // 覆盖操作
            tr[p].sum = (op == 1) ? (r - l + 1) : 0;
            tr[p].tag = (op == 1);
            tr[p].rev = 0;
        } else { // 翻转操作
            tr[p].sum = (r - l + 1) - tr[p].sum;
            tr[p].rev ^= 1;
        }
        return;
    }
    pushdown(p, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) update(p<<1, l, mid, ql, qr, op);
    if (qr > mid) update(p<<1|1, mid+1, r, ql, qr, op);
    tr[p].sum = tr[p<<1].sum + tr[p<<1|1].sum;
}

int query(int p, int l, int r) {
    if (l == r) return l;
    pushdown(p, l, r);
    int mid = (l + r) >> 1;
    if (tr[p<<1].sum < mid - l + 1) return query(p<<1, l, mid);
    else return query(p<<1|1, mid+1, r);
}

int main() {
    // 离散化处理
    vals.push_back(1);
    for (int i = 1; i <= m; ++i) {
        vals.push_back(q[i].l);
        vals.push_back(q[i].r);
        vals.push_back(q[i].r + 1);
    }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());

    // 线段树初始化
    build(1, 1, vals.size());

    for (int i = 1; i <= m; ++i) {
        int l_id = lower_bound(vals.begin(), vals.end(), q[i].l) - vals.begin() + 1;
        int r_id = lower_bound(vals.begin(), vals.end(), q[i].r) - vals.begin() + 1;
        update(1, 1, vals.size(), l_id, r_id, q[i].op);
        printf("%lld\n", vals[query(1, 1, vals.size()) - 1]);
    }
}
```

---
处理用时：102.38秒