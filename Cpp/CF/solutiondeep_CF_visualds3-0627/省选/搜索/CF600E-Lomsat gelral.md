# 题目信息

# Lomsat gelral

## 题目描述

You are given a rooted tree with root in vertex $ 1 $ . Each vertex is coloured in some colour.

Let's call colour $ c $ dominating in the subtree of vertex $ v $ if there are no other colours that appear in the subtree of vertex $ v $ more times than colour $ c $ . So it's possible that two or more colours will be dominating in the subtree of some vertex.

The subtree of vertex $ v $ is the vertex $ v $ and all other vertices that contains vertex $ v $ in each path to the root.

For each vertex $ v $ find the sum of all dominating colours in the subtree of vertex $ v $ .

## 样例 #1

### 输入

```
4
1 2 3 4
1 2
2 3
2 4
```

### 输出

```
10 9 3 4
```

## 样例 #2

### 输入

```
15
1 2 3 1 2 3 3 1 1 3 2 2 1 2 3
1 2
1 3
1 4
1 14
1 15
2 5
2 6
2 7
3 8
3 9
3 10
4 11
4 12
4 13
```

### 输出

```
6 5 4 3 2 3 3 1 1 3 2 2 1 2 3
```

# AI分析结果



**【算法分类】**  
其他搜索（树上启发式合并 DSU on Tree）

---

### **题解思路与核心难点**  
**核心问题**：统计每个子树中出现次数最多的颜色编号和。  
**核心算法对比**：  
1. **DSU on Tree（启发式合并）**：  
   - **关键思路**：利用重链剖分特性，优先处理重儿子子树，保留其信息；轻儿子子树暴力统计后清空，避免重复计算。  
   - **难点**：正确识别重儿子，分层处理子树贡献，复杂度优化至 O(n log n)。  
   - **数据结构**：使用数组维护颜色计数与当前最大值。  

2. **线段树合并**：  
   - **关键思路**：每个节点维护值域线段树，合并子树线段树时统计颜色出现次数。  
   - **难点**：动态开点线段树的空间管理，合并时的节点合并策略。  
   - **数据结构**：动态开点线段树，维护最大值和编号和。  

3. **莫队算法**：  
   - **关键思路**：将树转化为 DFS 序区间，通过分块处理区间查询。  
   - **难点**：维护出现次数最大值的高效性，分块优化至 O(n√n)。  

---

### **最优思路提炼**  
**DSU on Tree 的核心优化**：  
1. **重儿子优先**：预处理子树大小，优先处理重儿子子树以保留其贡献。  
2. **轻子树暴力**：轻儿子子树遍历后清空，避免影响兄弟子树计算。  
3. **颜色计数与最大值维护**：单次遍历中动态更新颜色出现次数及当前最大值。  

**代码片段示例（DSU on Tree）**：  
```cpp
void dfs(int x, int f, int p) {
    ap[c[x]]++; // 更新颜色计数
    if (ap[c[x]] > mx) mx = ap[c[x]], sum = c[x];
    else if (ap[c[x]] == mx) sum += c[x];
    for (int i = first[x]; i; i = nex[i]) {
        int y = v[i];
        if (y == f || y == p) continue; // 跳过父节点和重儿子
        DFS(y, x, p);
    }
}
```

---

### **可视化设计要点**  
**动画演示（DSU on Tree）**：  
1. **节点染色**：重儿子子树用蓝色标记，轻儿子用红色。  
2. **遍历过程**：  
   - 轻子树遍历时显示计数增加，回溯时颜色计数清空。  
   - 重子树遍历后保留颜色计数，合并到父节点时高亮显示。  
3. **动态统计**：右侧面板实时显示当前子树的最大出现次数和颜色和。  

**复古像素风格**：  
- **8位调色板**：使用蓝、红、黄区分不同子树类型。  
- **音效设计**：  
  - 遍历新节点时播放短促“滴”声。  
  - 重子树合并时播放合成器音效。  
- **Canvas 网格**：树结构以网格布局展示，节点按层级排列。  

---

### **推荐相似题目**  
1. **CF570D Tree Requests**（子树字符频次统计）  
2. **CF208E Blood Cousins**（树上层级查询）  
3. **LOJ #2845「离线版」子树颜色出现次数**（线段树合并应用）  

---

### **题解评分与亮点**  
1. **YellowBean_Elsa（DSU on Tree）** ⭐⭐⭐⭐⭐  
   - **亮点**：代码简洁，复杂度分析清晰，注释详细。  
   - **代码片段**：预处理重儿子，递归时跳过重子树优化。  

2. **辰星凌（DSU on Tree + 分治）** ⭐⭐⭐⭐  
   - **亮点**：对比多种算法，分治策略补充说明。  
   - **心路历程**：“手玩树结构理解启发式合并的精髓”。  

3. **Styx（线段树合并）** ⭐⭐⭐⭐  
   - **亮点**：动态开点线段树实现完整，维护最大值逻辑清晰。  
   - **代码技巧**：合并时复用节点减少内存消耗。  

---

### **总结与扩展**  
**核心思维模式**：  
- **子树问题转化**：通过 DFS 序或树链特性将子树问题转为序列操作。  
- **分层处理贡献**：优先处理稳定部分（如重子树），动态维护可变部分。  

**举一反三**：  
- 类似问题可尝试优先选择 DSU on Tree（空间高效）或线段树合并（逻辑直观）。  
- 莫队算法适用于允许离线且区间可分的场景。

---
处理用时：59.87秒