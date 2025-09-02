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



# 算法分类：区间操作与数据结构

---

## 综合分析与结论

### 核心算法流程与难点
1. **珂朵莉树（Chtholly Tree）**  
   - **核心思想**：将连续区间合并为若干节点，通过 split/assign 操作处理区间覆盖，暴力遍历查询第一个空区间。  
   - **难点**：操作3的区间反转需要遍历修改每个节点的 val 值，可能产生大量碎片但实际效率较高。  
   - **可视化设计**：用不同颜色表示区间是否被覆盖（如红色为1，蓝色为0），每次操作后高亮分裂点，反转时动态变色。

2. **线段树 + 离散化**  
   - **核心思想**：离散化后维护区间和，通过标记下传处理覆盖/反转，递归查询左子树优先找第一个0。  
   - **难点**：离散化需包含所有可能影响 MEX 的端点（如 l-1, r+1, 1），标记叠加逻辑需谨慎处理。  
   - **可视化设计**：树形结构分层展示，当前操作路径用黄色高亮，标记下传时显示父子节点状态变化。

3. **分块与平衡树**  
   - **分块**：按离散化后的块处理区间操作，暴力遍历块内元素查询 MEX。  
   - **平衡树**：动态维护区间段，类似珂朵莉树但更复杂，需处理动态开点和标记下传。  

---

## 题解清单（≥4星）

### 1. 珂朵莉树（作者：Unnamed114514）  
**评分**：★★★★☆  
**亮点**：代码简洁，利用 `set` 存储区间节点，assign 和 rever 操作直接覆盖/遍历修改。  
**关键代码**：  
```cpp
void assign(int l, int r, int val) {
    auto itr = split(r + 1), itl = split(l);
    s.erase(itl, itr);
    s.insert(node{l, r, val});
}
```
**心得**：初始插入 `1e18+1` 的0区间保证查询始终有效。

### 2. 线段树 + 离散化（作者：Acestar）  
**评分**：★★★★☆  
**亮点**：离散化处理巧妙，维护 sum/tag/rev 标记，查询时优先左子树。  
**关键代码**：  
```cpp
int query() {
    if (sum[rt] == n) return n + 1; // n为离散化后的最大位置
    int l = 1, r = n, ans = 1;
    while (l <= r) { // 线段树二分
        if (sum[ls] < mid - l + 1) r = mid;
        else l = mid + 1;
    }
    return l;
}
```
**心得**：离散化时需将 `r+1` 加入以保证正确性。

### 3. 动态开点平衡树（作者：Froggy）  
**评分**：★★★★☆  
**亮点**：动态维护区间段，节点存储 `[l,r]` 范围，直接处理区间操作。  
**关键代码**：  
```cpp
void serve(int l, int r) { // 区间反转
    split(l), split(r + 1);
    for (auto it = s.lower_bound(l); it != s.end() && it->l <= r; ++it)
        it->val ^= 1;
}
```
**心得**：相比线段树更灵活，但实现复杂度较高。

---

## 最优思路与技巧提炼

### 关键思路
1. **离散化边界处理**：必须包含 `1`, `l`, `r`, `r+1` 等可能影响 MEX 的位置。  
2. **标记叠加逻辑**：线段树的覆盖标记优先级高于反转标记，反转时需处理子节点原有标记。  
3. **暴力查询优化**：珂朵莉树每次查询只需遍历 `set` 找到第一个 `val=0` 的区间左端点。  

---

## 同类题目推荐
1. **CF915E**：动态开点线段树处理区间覆盖与计数。  
2. **P2574**：区间翻转与查询，线段树维护反转标记。  
3. **P3968**：动态开点平衡树处理区间操作。  

---

## 可视化与算法演示

### 珂朵莉树操作动画
1. **初始状态**：整个区间显示为蓝色（val=0）。  
2. **操作1（覆盖为1）**：选定区间变为红色，分裂边界高亮黄色。  
3. **操作3（反转）**：区间颜色反转，动态显示遍历修改过程。  
4. **查询MEX**：从左到右扫描蓝色区间，命中时闪烁绿色。  

### 复古像素风格设计
- **颜色方案**：  
  - 蓝色（#0000FF）：未覆盖区间  
  - 红色（#FF0000）：已覆盖区间  
  - 黄色（#FFFF00）：当前操作区间边界  
- **音效**：  
  - 覆盖/反转：8-bit "beep" 音效  
  - 查询成功：上升音阶  
- **Canvas 绘制**：  
  ```javascript
  function drawNode(node) {
      ctx.fillStyle = node.val ? '#FF0000' : '#0000FF';
      ctx.fillRect(node.l * scaleX, 0, (node.r - node.l + 1) * scaleX, 50);
  }
  ```

---

## 个人心得摘录
> "初始插入 `1e18+1` 的0区间是保证查询始终有效的关键，否则当所有区间被覆盖为1时无法找到 MEX。"  
> —— 珂朵莉树题解作者  

> "离散化时漏掉 `r+1` 会导致最后一个有效位置无法被检测，必须特别注意边界。"  
> —— 线段树题解调试记录  

---

## 核心代码实现（珂朵莉树）

```cpp
struct node {
    int l, r;
    mutable int val;
    bool operator<(const node &t) const { return l < t.l; }
};

set<node> s;

auto split(int pos) {
    auto it = s.lower_bound(node{pos});
    if (it != s.end() && it->l == pos) return it;
    --it;
    int l = it->l, r = it->r, v = it->val;
    s.erase(it);
    s.insert(node{l, pos - 1, v});
    return s.insert(node{pos, r, v}).first;
}

void assign(int l, int r, int val) {
    auto itr = split(r + 1), itl = split(l);
    s.erase(itl, itr);
    s.insert(node{l, r, val});
}

int query() {
    for (auto &nd : s) 
        if (!nd.val) return nd.l;
    return 1e18 + 1; // 保证不会执行到
}
```

---
处理用时：80.64秒