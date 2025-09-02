# 题目信息

# Frequency Mismatch (Easy Version)

## 题目描述

This is the easy version of the problem. The difference between the two versions of this problem is the constraint on $ k $ . You can make hacks only if all versions of the problem are solved.

You are given an undirected tree of $ n $ nodes. Each node $ v $ has a value $ a_v $ written on it. You have to answer queries related to the tree.

You are given $ q $ queries. In each query, you are given $ 5 $ integers, $ u_1, v_1, u_2, v_2, k $ . Denote the count of nodes with value $ c $ on path $ u_1 \rightarrow v_1 $ with $ x_c $ , and the count of nodes with value $ c $ on path $ u_2 \rightarrow v_2 $ with $ y_c $ . If there are $ z $ such values of $ c $ such that $ x_c \neq y_c $ , output any $ \min(z, k) $ such values in any order.

## 说明/提示

For query $ 1 $ , the first path is $ 1 \rightarrow 2 \rightarrow 4 $ , coming across the multiset of values $ \{5, 2, 4\} $ . On the second path $ 4 \rightarrow 2 \rightarrow 5 $ , we have the multiset $ \{4, 2, 3\} $ . Two numbers — $ 3 $ and $ 5 $ occur a different number of times, hence we print one of them.

In query $ 2 $ , there is no difference between the paths, hence we output $ 0 $ .

In query $ 3 $ , the first path is just the node $ 5 $ , resulting in the multiset $ \{3\} $ , and the second path $ 4 \rightarrow 2 \rightarrow 1 \rightarrow 3 $ gives $ \{4, 2, 5, 3\} $ . The numbers $ 5 $ , $ 2 $ and $ 4 $ occur a different number of times.

## 样例 #1

### 输入

```
5
5 2 3 4 3
1 2
1 3
2 4
2 5
3
1 4 4 5 1
2 3 2 3 1
5 5 4 3 1```

### 输出

```
1 5
0
1 2```

# AI分析结果



## 算法分类
树的可持久化线段树、哈希与LCA的结合应用

---

## 综合分析与结论

### 核心思路
1. **路径统计模型**：通过可持久化线段树维护每个节点到根节点的权值出现次数信息，利用树链分解（LCA）将路径统计转化为四个线段树的组合操作。
2. **哈希加速比较**：为每个颜色随机哈希权值，路径的哈希值为各节点权值之和，利用线段树快速比较两路径的哈希是否相等。
3. **递归差异查找**：在线段树上递归查找哈希不同的区间，直到找到叶子节点（具体颜色），最多收集k个差异项。

### 解决难点
- **路径动态统计**：传统遍历无法处理多次查询，可持久化线段树通过差分实现O(1)路径合并。
- **高效差异检测**：哈希值允许快速比较，线段树结构支持分层定位差异点，避免全量检查。

### 可视化设计思路
- **树与线段树联动**：左侧展示树结构，高亮当前查询路径；右侧显示两路径对应的线段树节点哈希值对比。
- **递归过程动画**：用颜色标记线段树当前检查的区间（红：差异，绿：相同），动态展开左右子树。
- **像素音效**：发现差异时播放“哔”声，收集到k个差异后播放胜利音效。

---

## 题解评分（≥4星）

1. **WRuperD（4.5星）**  
   - 亮点：完整实现路径哈希与递归差异查找，代码结构清晰，利用mt19937生成高质量随机权值。  
   - 优化点：采用单哈希但冲突概率低，空间管理较优。

2. **strcmp（4星）**  
   - 亮点：双哈希增强鲁棒性，代码精简，LCA预处理高效。  
   - 优化点：未显式处理fa[lca]，需结合权值修正。

---

## 核心代码实现

**可持久化线段树构建**
```cpp
int add(int l, int r, int pos, int val, int prex) {
    int x = ++psz;
    s[x] = s[prex] + val;
    if (l == r) return x;
    if (pos <= mid) ls[x] = add(l, mid, pos, val, ls[prex]);
    else rs[x] = add(mid+1, r, pos, val, rs[prex]);
    return x;
}
```

**递归差异查找**
```cpp
vector<int> query(int l, int r, int u1, int v1, int lca1, ...) {
    if (哈希相同) return {};
    if (叶子节点) return {当前颜色};
    vector<int> left = 递归左子树;
    if (left.size() < k) {
        vector<int> right = 递归右子树;
        left.insert(end(left), begin(right), end(right));
    }
    return left;
}
```

---

## 同类题目推荐
1. **P3302 [SDOI2013]森林** - 动态树上的路径第k大，需结合可持久化线段树。
2. **P2633 Count on a tree** - 路径权值第k小，类似主席树应用。
3. **P4211 [LNOI2014]LCA** - 深度分析与路径统计结合LCA。

---

## 可视化与像素动画方案

### 动画设计
- **树结构展示**：Canvas绘制树形图，点击查询时高亮u1-v1和u2-v2路径。
- **线段树对比**：左右两面板分别显示两路径的线段树，差异节点闪烁红光。
- **8位音效**：差异发现时播放短促“哔”，错误路径播放低音。

### 代码片段（JS伪代码）
```javascript
function drawTree(ctx, nodes, edges) {
    edges.forEach(e => drawLine(ctx, e)); // 绘制树边
    nodes.forEach(n => drawNode(ctx, n)); // 绘制节点
}

function compareSegTrees(t1, t2) {
    if (t1.hash != t2.hash) {
        playSound('beep'); // 触发差异音效
        if (isLeaf(t1)) collectDiff(t1.color);
        else {
            compareSegTrees(t1.left, t2.left);
            compareSegTrees(t1.right, t2.right);
        }
    }
}
```

---

## 个人心得摘录
- **哈希冲突教训**：初期使用单哈希导致WA，改为双哈希后通过（lfxxx题解提及）。
- **LCA细节**：忘记处理fa[lca]导致统计错误，需明确路径为u+v-lca-fa[lca]（WRuperD注释强调）。

---
处理用时：83.69秒