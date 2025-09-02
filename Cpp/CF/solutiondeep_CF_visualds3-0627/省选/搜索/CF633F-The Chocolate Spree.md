# 题目信息

# The Chocolate Spree

## 题目描述

Alice and Bob have a tree (undirected acyclic connected graph). There are $ a_{i} $ chocolates waiting to be picked up in the $ i $ -th vertex of the tree. First, they choose two different vertices as their starting positions (Alice chooses first) and take all the chocolates contained in them.

Then, they alternate their moves, selecting one vertex at a time and collecting all chocolates from this node. To make things more interesting, they decided that one can select a vertex only if he/she selected a vertex adjacent to that one at his/her previous turn and this vertex has not been already chosen by any of them during other move.

If at any moment one of them is not able to select the node that satisfy all the rules, he/she will skip his turns and let the other person pick chocolates as long as he/she can. This goes on until both of them cannot pick chocolates any further.

Due to their greed for chocolates, they want to collect as many chocolates as possible. However, as they are friends they only care about the total number of chocolates they obtain together. What is the maximum total number of chocolates they may pick?

## 说明/提示

In the first sample, Alice may start at the vertex $ 9 $ and Bob at vertex $ 8 $ . Alice will select vertex $ 1 $ and Bob has no options now. Alice selects the vertex $ 7 $ and they both stop.

In the second sample, both of them will pick either of the nodes alternately.

## 样例 #1

### 输入

```
9
1 2 3 4 5 6 7 8 9
1 2
1 3
1 4
1 5
1 6
1 7
1 8
1 9
```

### 输出

```
25
```

## 样例 #2

### 输入

```
2
20 10
1 2
```

### 输出

```
30
```

# AI分析结果



### 算法分类
**其他搜索**（基于树形动态规划，核心逻辑依赖DFS遍历树结构）

---

### 题解思路与算法要点
**核心问题**：在树中寻找两条不相交路径，使得它们的权值和最大。  
**难点**：两条路径的形态组合复杂，需覆盖以下情况：
1. 两条路径位于不同子树
2. 一条路径经过当前节点，另一条在子树中
3. 路径可能以当前节点为分叉点

**树形DP状态设计**：
- `f[u][0]`：以u为根的子树中两条不相交链的最大和
- `f[u][1]`：以u为根的子树中最长单链的值
- `g[u]`：u到叶子节点的链与另一条链的组合最大值
- `h[u]`：子节点中最长单链的最大值
- `down[u]`：从u到叶子节点的最长链

**DFS遍历与状态转移**：
1. **DFS遍历**：自底向上合并子树信息。
2. **状态更新**：通过比较不同子树的链组合，动态更新各状态。例如：
   - `f[u][0]`可能由以下情况更新：子树中的两条链、当前链+子链、跨子树的两条链等。
3. **关键转移逻辑**：
   ```cpp
   f[cur][0] = max(f[cur][0], f[cur][1] + f[u][1]); // 合并两条子链
   f[cur][0] = max(f[cur][0], down[cur] + g[u]);    // 当前链+子链组合
   f[cur][1] = max(f[cur][1], down[cur] + down[u]); // 更新最长链
   ```

---

### 题解评分（≥4星）
1. **NOIPZZY（5星）**  
   - 思路清晰，状态设计简洁，覆盖所有情况。
   - 代码结构紧凑，注释明确，适合快速理解核心逻辑。
2. **Liuxizai（4星）**  
   - 状态命名直观，转移逻辑详细注释。
   - 代码可读性高，但部分冗余状态略微增加复杂度。
3. **tzc_wk（4星）**  
   - 创新性结合换根DP，思路独特。
   - 代码优化程度高，但实现细节较复杂。

---

### 最优思路与技巧
1. **状态设计**：通过多维度状态描述子树中的链组合，确保覆盖所有可能路径形态。
2. **合并策略**：在DFS回溯时，利用子树信息动态更新父节点状态，优先比较最长链与跨子树组合。
3. **剪枝优化**：维护前缀/后缀最大值数组，避免重复计算子节点贡献。

---

### 类似题目推荐
1. **洛谷P4383**：树的最长路径（树形DP经典题）
2. **洛谷P3177**：树上选点使距离和最大（状态合并思路相似）
3. **Codeforces 1092F**：树中带权路径和最大化（换根DP应用）

---

### 可视化与算法演示
**动画设计要点**：
1. **树结构绘制**：以根节点为中心展开，用不同颜色区分已访问/未访问节点。
2. **状态值动态更新**：高亮当前处理的子树，展示`f[u][0]`、`f[u][1]`等状态的实时数值变化。
3. **回溯过程演示**：用箭头表示状态合并方向，突出父节点如何综合子节点信息。

**复古像素风格实现**：
- **Canvas绘制**：每个节点显示为8位风格方块，状态值以像素字体标注。
- **音效触发**：节点访问时播放短促“哔”声，状态更新时播放“滴”声。
- **自动演示模式**：按DFS顺序自动遍历节点，用户可暂停观察当前状态。

---

### 代码核心片段（NOIPZZY解法）
```cpp
void dfs(int cur, int fa) {	
    f[cur][0] = f[cur][1] = g[cur] = down[cur] = w[cur];
    h[cur] = 0;
    for (int u : G[cur]) {
        if (u == fa) continue;
        dfs(u, cur);
        // 更新两条链的最大值
        f[cur][0] = max({f[cur][0], f[u][0], f[cur][1] + f[u][1], 
                        down[cur] + g[u], g[cur] + down[u]});
        // 更新最长单链
        f[cur][1] = max({f[cur][1], f[u][1], down[cur] + down[u]});
        // 更新组合链
        g[cur] = max({g[cur], w[cur] + g[u], down[cur] + f[u][1], 
                     down[u] + w[cur] + h[cur]});
        h[cur] = max(h[cur], f[u][1]);
        down[cur] = max(down[cur], down[u] + w[cur]);
    }
}
```

---

### 个人心得摘录
> **huyufeifei**提到：“不要怕多设状态，重点在于把所有情况都描述出来。”  
> **Rina_048**调试时因漏掉状态转移细节导致WA，强调边界条件的重要性。

---
处理用时：70.64秒