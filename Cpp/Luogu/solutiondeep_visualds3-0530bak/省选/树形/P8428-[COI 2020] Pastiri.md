# 题目信息

# [COI 2020] Pastiri

## 题目描述

给定一棵 $N$ 点的树，点编号为 $1$ 到 $N$，现在在 $K$ 个点上有羊，你的任务是在树上分配一些牧羊人。

这些牧羊人很懒，只会看管离他最近的羊。当然如果有多个离他最近的羊，那么他会都看管。

当然，牧羊人可以和羊在同一个点上，但这样牧羊人只会看管这一个点上的那个羊。

求一种牧羊人的分配方案使得牧羊人总数最小。

## 说明/提示

#### 样例 3 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/qwahnh8z.png)

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（8 pts）：$1 \le N \le 5 \times 10^5$，任意一个点 $i$ 都与 $i+1$ 相连（$1 \le i \le N-1$）。
- Subtask 2（18 pts）：$1 \le K \le 15$，$1 \le N \le 5 \times 10^5$。
- Subtask 3（23 pts）：$1 \le N \le 2000$。
- Subtask 4（51 pts）：$1 \le N \le 5 \times 10^5$。

对于 $100\%$ 的数据，$1 \le K \le N$，$1 \le a_i,b_i \le N$，$1 \le  o_i \le N$。

**本题使用 Special Judge，checker 提供者 @[Lynkcat](https://www.luogu.com.cn/user/120911)，感谢他的贡献。**

#### 说明

翻译自 [Croatian Olympiad in Informatics 2020 B Pastiri](https://hsin.hr/coci/archive/2019_2020/olympiad_tasks.pdf)。

## 样例 #1

### 输入

```
4 2
1 2
2 3
3 4
1 4```

### 输出

```
2
1 3```

## 样例 #2

### 输入

```
9 5
1 2
2 3
3 4
3 5
1 6
1 7
7 8
8 9
2 5 6 7 9```

### 输出

```
3
1 4 9```

## 样例 #3

### 输入

```
20 9
1 2
2 3
2 4
4 5
4 6
5 7
7 8
8 9
7 10
10 11
6 12
6 13
6 17
13 14
14 15
14 16
17 18
18 19
18 20
1 3 9 11 12 15 16 19 20```

### 输出

```
3
5 14 18```

# AI分析结果



**唯一算法分类**：贪心算法

---

### **综合分析与结论**

**核心思路**：  
题目要求在树上放置最少的牧羊人，使得每个羊都被其最近的牧羊人覆盖。所有题解均采用贪心策略，核心步骤为：  
1. **预处理距离**：通过多源 BFS 计算每个节点到最近羊的距离 `dis`。  
2. **按深度贪心**：将羊按深度从大到小排序，每次处理未被覆盖的最深羊。  
3. **跳祖先找位置**：从当前羊向上跳祖先，直到无法满足 `dis[父节点] = dis[当前节点] + 1`，此时该祖先即为牧羊人位置。  
4. **标记覆盖区域**：从牧羊人位置出发，DFS 遍历所有满足 `dis[子节点] = dis[当前节点] - 1` 的节点，标记覆盖的羊。

**关键难点**：  
- **正确性证明**：为何选择最深的羊及其最高祖先最优？  
  答：最深的羊未被覆盖时，必须有一个牧羊人覆盖它。选择最高祖先能覆盖该路径上所有可能更深的羊，同时避免与其他子树冲突。  
- **复杂度优化**：DFS 遍历时，通过 `dis` 判断是否继续递归，确保每个节点仅访问一次，保证线性时间复杂度。

**可视化设计**：  
- **动画流程**：  
  1. 树结构展示，羊节点高亮为红色。  
  2. 显示多源 BFS 计算 `dis` 的过程，颜色渐变表示距离。  
  3. 按深度排序羊后，逐个处理：当前羊闪烁，向上跳祖先时路径高亮。  
  4. 放置牧羊人（黄色标记），DFS 覆盖区域扩散（绿色覆盖）。  
- **复古像素风格**：  
  - 树节点用 8x8 像素方块表示，羊为红色，牧羊人为黄色，覆盖区域渐变绿色。  
  - 音效：放置牧羊人时播放短促“滴”声，覆盖完成时播放成功音效。  
- **交互控制**：支持暂停/继续，步进执行，调节动画速度。

---

### **题解清单 (≥4星)**

1. **cc0000（5星）**  
   **亮点**：代码简洁高效，预处理和贪心逻辑清晰，DFS 标记时通过 `dis` 剪枝，确保线性复杂度。  

2. **wYYSZLwSSY（4星）**  
   **亮点**：详细解释贪心策略的正确性，优化 DFS 条件判断，避免冗余遍历。  

3. **MerlinLee（4星）**  
   **亮点**：代码可读性强，通过 `d[]` 数组标记覆盖状态，逻辑直观。  

---

### **核心代码实现**

**关键逻辑片段（cc0000 的代码）**：
```cpp
// 多源 BFS 预处理 dis
void spfa() {
    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            if (dis[v] > dis[u] + 1) {
                dis[v] = dis[u] + 1;
                if (!vis[v]) Q.push(v), vis[v] = 1;
            }
        }
    }
}

// 贪心选择牧羊人位置
sort(O + 1, O + 1 + K, cmp); // 按深度排序
for (int i = 1; i <= K; i++) {
    if (d[O[i]]) continue;
    int f = O[i];
    while (fa[f] && dis[fa[f]] == dis[f] + 1) f = fa[f];
    dfs(f, dis[f]); // 标记覆盖区域
    Ans.push_back(f);
}

// DFS 标记覆盖
void dfs(int u, int s) {
    d[u] = 1;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (dis[v] == s - 1 && !d[v]) dfs(v, s - 1);
    }
}
```

---

### **同类型题与推荐题目**

1. **P3523 [POI2011] DYN-Dynamite**  
   - 类似贪心：选择最远需覆盖点，向上找最优位置。  

2. **P3942 将军令**  
   - 树覆盖问题，贪心选择最深节点并覆盖其 k 层祖先。  

3. **P2279 [HNOI2003] 消防局的设立**  
   - 最小覆盖问题，贪心或树形 DP 解决。  

---

### **个人心得摘录**

- **调试教训**：DFS 标记时必须严格判断 `dis[子节点] = dis[当前节点] - 1`，否则会错误覆盖无关节点。  
- **顿悟点**：贪心策略的正确性源于“最深节点必须被覆盖，而最高祖先能最大化覆盖范围”。  

---

### **可视化与游戏化设计**

**Canvas 动画伪代码**：  
```javascript
// 初始化树和羊
drawTree();
sheepNodes.forEach(node => highlight(node, 'red'));

// BFS 计算 dis
bfsQueue.forEach(step => {
    highlightCurrentNode(step.u);
    updateDisColor(step.v, dis[step.v]);
    playSound('step');
});

// 贪心处理羊
sortedSheep.forEach(sheep => {
    highlight(sheep, 'blue');
    let pos = findAncestor(sheep);
    highlight(pos, 'yellow');
    playSound('place');
    dfsCover(pos, dis[pos]);
});

// DFS 覆盖
function dfsCover(node, s) {
    if (s < 0) return;
    highlight(node, 'green');
    node.children.forEach(child => {
        if (child.dis === s - 1) dfsCover(child, s - 1);
    });
}
```

**复古风格**：  
- 颜色：红色（羊）、黄色（牧羊人）、绿色（覆盖区）。  
- 音效：8-bit 风格音效，覆盖成功时播放胜利旋律。

---
处理用时：80.37秒