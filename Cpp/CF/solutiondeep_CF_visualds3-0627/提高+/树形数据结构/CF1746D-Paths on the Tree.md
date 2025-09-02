# 题目信息

# Paths on the Tree

## 题目描述

You are given a rooted tree consisting of $ n $ vertices. The vertices are numbered from $ 1 $ to $ n $ , and the root is the vertex $ 1 $ . You are also given a score array $ s_1, s_2, \ldots, s_n $ .

A multiset of $ k $ simple paths is called valid if the following two conditions are both true.

- Each path starts from $ 1 $ .
- Let $ c_i $ be the number of paths covering vertex $ i $ . For each pair of vertices $ (u,v) $ ( $ 2\le u,v\le n $ ) that have the same parent, $ |c_u-c_v|\le 1 $ holds.

 The value of the path multiset is defined as $ \sum\limits_{i=1}^n c_i s_i $ .It can be shown that it is always possible to find at least one valid multiset. Find the maximum value among all valid multisets.

## 说明/提示

In the first test case, one of optimal solutions is four paths $ 1 \to 2 \to 3 \to 5 $ , $ 1 \to 2 \to 3 \to 5 $ , $ 1 \to 4 $ , $ 1 \to 4 $ , here $ c=[4,2,2,2,2] $ . The value equals to $ 4\cdot 6+ 2\cdot 2+2\cdot 1+2\cdot 5+2\cdot 7=54 $ .

In the second test case, one of optimal solution is three paths $ 1 \to 2 \to 3 \to 5 $ , $ 1 \to 2 \to 3 \to 5 $ , $ 1 \to 4 $ , here $ c=[3,2,2,1,2] $ . The value equals to $ 3\cdot 6+ 2\cdot 6+2\cdot 1+1\cdot 4+2\cdot 10=56 $ .

## 样例 #1

### 输入

```
2
5 4
1 2 1 3
6 2 1 5 7
5 3
1 2 1 3
6 6 1 4 10```

### 输出

```
54
56```

# AI分析结果



**唯一算法分类**：贪心算法 + 树的深度优先搜索 (DFS)

---

### **题解思路与算法要点**

#### **核心思路**
- **贪心分配**：每个节点将路径次数平均分配给子节点，余数优先分配给贡献最大的子树。
- **递归处理**：从根节点开始，逐层递归分配次数，保证兄弟节点次数差 ≤1。
- **增量计算**：利用优先队列或排序选出余数次数的最大增量路径。

#### **解决难点**
1. **平均分配与余数处理**：每个节点的子节点至少分配 `⌊k/son⌋` 次，剩余 `rest = k % son` 次需分配给贡献最大的子节点。
2. **增量维护**：递归返回当前子树的最大可能增量，供父节点选择最优余数分配。
3. **时间复杂度优化**：通过优先队列或排序避免重复计算，确保时间复杂度为 O(n log n)。

#### **关键变量与数据结构**
- `fen = k / son`：子节点基础分配次数。
- `rest = k % son`：需额外分配的子节点数。
- **优先队列/排序**：存储子树的增量贡献，选出前 `rest` 个最大值。

---

### **题解评分 (≥4星)**

1. **GalwayGirl (5星)**
   - **亮点**：代码结构清晰，优先队列维护增量贡献，递归逻辑简洁。
   - **代码可读性**：高，变量命名直观，递归函数易理解。

2. **LYY_yyyy (4星)**
   - **亮点**：代码极简，直接通过排序处理增量，省去显式优先队列。
   - **优化点**：未使用记忆化，但递归深度合理，实际效率较高。

3. **As_Snow (4星)**
   - **亮点**：记忆化搜索优化重复计算，代码通用性强。
   - **复杂度**：需处理 `map` 的键冲突，但理论时间复杂度最优。

---

### **最优思路提炼**
1. **递归分配策略**：每个节点将 `k` 次路径按 `⌊k/son⌋` 分配给子节点，余数选最大增量子树。
2. **增量返回机制**：递归返回当前子树的最大可能贡献（路径和），供父节点决策余数分配。
3. **数据结构优化**：利用优先队列或排序快速选出前 `rest` 大增量，确保全局最优。

---

### **同类型题与算法套路**
- **通用解法**：树形贪心 + 递归增量计算。
- **类似题目**：
  1. **洛谷 P1273**：有线电视网（树形DP + 资源分配）。
  2. **洛谷 P2014**：选课（树形依赖背包问题）。
  3. **洛谷 P2585**：三色二叉树（树结构处理 + 贪心）。

---

### **代码核心实现**
```cpp
// GalwayGirl 的递归实现（关键部分）
long long dfs2(int now, long long k, int fa) {
    ans += k * w[now];  // 当前节点贡献
    if (!son[now]) return w[now];  // 叶子节点返回自身值
    long long fen = k / son[now], rest = k % son[now];
    priority_queue<long long> q;
    for (子节点 v) {
        q.push(dfs2(v, fen, now));  // 递归处理子节点
    }
    if (rest) {
        // 选前 rest 个最大增量
        while (rest--) ans += q.top(), q.pop();
    }
    return q.top() + w[now];  // 返回当前子树的最大增量
}
```

---

### **可视化与算法演示**
#### **动画设计**
1. **树形结构展示**：以根节点为起点，递归展开子树，高亮当前处理节点。
2. **分配过程**：
   - **颜色标记**：当前节点为红色，子节点分配时渐变为绿色。
   - **优先队列动态显示**：实时展示队列中增量贡献的变化。
3. **步进控制**：支持单步执行，观察 `fen` 和 `rest` 的分配逻辑。

#### **复古像素风格**
- **颜色方案**：8位色调色板（红/绿/蓝代表不同状态）。
- **音效触发**：
  - **关键分配**：8-bit "beep" 音效。
  - **完成递归**：上扬音调提示子树处理完毕。

---

### **个人心得摘录**
> “最大链可以递归求取，每个节点维护堆存储增量贡献，防止父节点重复使用。”  
> —— GalwayGirl 题解中的核心观察，强调递归与数据结构的结合。

---
处理用时：79.96秒