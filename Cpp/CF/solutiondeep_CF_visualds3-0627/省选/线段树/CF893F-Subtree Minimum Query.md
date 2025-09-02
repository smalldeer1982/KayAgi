# 题目信息

# Subtree Minimum Query

## 题目描述

You are given a rooted tree consisting of $ n $ vertices. Each vertex has a number written on it; number $ a_{i} $ is written on vertex $ i $ .

Let's denote $ d(i,j) $ as the distance between vertices $ i $ and $ j $ in the tree (that is, the number of edges in the shortest path from $ i $ to $ j $ ). Also let's denote the  $ k $ -blocked subtree of vertex $ x $ as the set of vertices $ y $ such that both these conditions are met:

- $ x $ is an ancestor of $ y $ (every vertex is an ancestor of itself);
- $ d(x,y)<=k $ .

You are given $ m $ queries to the tree. $ i $ -th query is represented by two numbers $ x_{i} $ and $ k_{i} $ , and the answer to this query is the minimum value of $ a_{j} $ among such vertices $ j $ such that $ j $ belongs to $ k_{i} $ -blocked subtree of $ x_{i} $ .

Write a program that would process these queries quickly!

Note that the queries are given in a modified way.

## 样例 #1

### 输入

```
5 2
1 3 2 3 5
2 3
5 1
3 4
4 1
2
1 2
2 3
```

### 输出

```
2
5
```

# AI分析结果



---

**唯一算法分类**：主席树（可持久化线段树）

---

### **题解思路与核心难点**

#### **核心算法流程**
1. **DFS序与深度预处理**  
   将子树查询转化为连续的 DFS 区间 `[dfn[x], dfn[x]+siz[x]-1]`，深度信息 `dep[x]` 用于限制查询范围。
2. **深度分层构建主席树**  
   按深度从小到大依次插入节点到主席树，每个深度版本 `root[dep]` 维护当前及之前深度的所有节点权值。
3. **查询优化**  
   直接查询 `root[dep[x]+k]` 版本的线段树中的子树区间，无需处理深度下限（子树中不存在更小的深度）。

#### **可视化设计思路**
- **动画方案**  
  1. **DFS序与深度展示**：以树形结构展示，DFS 遍历时标记每个节点的 `dfn` 和 `dep` 值。  
  2. **主席树构建演示**：动态显示按深度插入节点的过程，每个版本 `root[i]` 用不同颜色区分。  
  3. **查询高亮**：高亮查询区间 `[dfn[x], dfn[x]+siz[x]-1]` 和深度范围 `dep[x]` 到 `dep[x]+k`。
- **复古像素风格**  
  使用 8-bit 风格网格展示 DFS 序区间，主席树版本切换时播放「滴」音效，查询命中最小值时触发「成功」音效。

---

### **题解评分（≥4星）**
1. **kouylan（5星）**  
   - **亮点**：代码简洁，利用 DFS 序与主席树深度分层的思路清晰。  
   - **关键代码**：按深度排序节点后构建主席树，查询时直接取 `dep[x]+k` 版本。
2. **GoldenPotato137（4.5星）**  
   - **亮点**：BFS 分层插入节点，博客详细说明「深度时间轴」思想。  
   - **关键代码**：动态开点线段树维护不同深度的最小值。
3. **mrsrz（4星）**  
   - **亮点**：代码高效，直接利用主席树差分思想，预处理最大深度。  
   - **关键代码**：按深度排序后构建可持久化线段树。

---

### **最优思路提炼**
1. **DFS序 + 深度分层**  
   将子树映射为连续区间，深度限制转化为时间轴版本控制。  
2. **主席树优化查询**  
   可持久化结构使得查询任意深度范围的时间复杂度为 `O(log n)`。  
3. **边界处理技巧**  
   利用 `min(dep[x]+k, max_depth)` 避免越界，简化代码逻辑。

---

### **相似题目推荐**
1. **洛谷 P2633**  
   强制在线求子树第 K 小，需结合 DFS 序和主席树。  
2. **洛谷 P3302**  
   子树合并与动态最小权值查询，适用线段树合并。  
3. **Codeforces 916E**  
   子树操作与深度限制的综合应用。

---

### **关键代码实现（kouylan版）**
```cpp
void dfs(int x, int pre) {
    dfn[x] = ++cnt; siz[x] = 1;
    for (auto y : tree[x]) {
        if (y != pre) {
            dfs(y, x);
            siz[x] += siz[y];
        }
    }
}

void build_persistent_segment_tree() {
    sort(p + 1, p + n + 1, [](int a, int b) { 
        return dep[a] < dep[b]; 
    });
    for (int i = 1; i <= n; i++) {
        insert(root[dep[p[i]]], root[dep[p[i-1]]], 
               1, n, dfn[p[i]], a[p[i]]);
    }
}

int query(int x, int k) {
    int max_dep = dep[x] + k;
    return query_segment_tree(root[max_dep], 
           dfn[x], dfn[x] + siz[x] - 1);
}
```

---

### **可视化实现要点**
1. **Canvas动画**  
   - 网格表示 DFS 序，每个格子显示节点权值和深度。  
   - 插入新深度节点时，对应格子闪烁并更新颜色。  
2. **音效设计**  
   - 插入节点：8-bit 风格「哔」声（频率随深度变化）。  
   - 查询命中：经典 FC 过关音效。  
3. **自动演示模式**  
   按深度逐步构建主席树，查询时自动定位区间，支持速度调节。

---

**总结**：通过 DFS 序映射子树区间，结合深度分层的主席树实现高效查询，是处理此类子树+深度限制问题的经典范式。

---
处理用时：78.67秒