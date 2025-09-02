# 题目信息

# Lunar New Year and a Wander

## 题目描述

Lunar New Year is approaching, and Bob decides to take a wander in a nearby park.

The park can be represented as a connected graph with $ n $ nodes and $ m $ bidirectional edges. Initially Bob is at the node $ 1 $ and he records $ 1 $ on his notebook. He can wander from one node to another through those bidirectional edges. Whenever he visits a node not recorded on his notebook, he records it. After he visits all nodes at least once, he stops wandering, thus finally a permutation of nodes $ a_1, a_2, \ldots, a_n $ is recorded.

Wandering is a boring thing, but solving problems is fascinating. Bob wants to know the lexicographically smallest sequence of nodes he can record while wandering. Bob thinks this problem is trivial, and he wants you to solve it.

A sequence $ x $ is lexicographically smaller than a sequence $ y $ if and only if one of the following holds:

- $ x $ is a prefix of $ y $ , but $ x \ne y $ (this is impossible in this problem as all considered sequences have the same length);
- in the first position where $ x $ and $ y $ differ, the sequence $ x $ has a smaller element than the corresponding element in $ y $ .

## 说明/提示

In the first sample, Bob's optimal wandering path could be $ 1 \rightarrow 2 \rightarrow 1 \rightarrow 3 $ . Therefore, Bob will obtain the sequence $ \{1, 2, 3\} $ , which is the lexicographically smallest one.

In the second sample, Bob's optimal wandering path could be $ 1 \rightarrow 4 \rightarrow 3 \rightarrow 2 \rightarrow 3 \rightarrow 4 \rightarrow 1 \rightarrow 5 $ . Therefore, Bob will obtain the sequence $ \{1, 4, 3, 2, 5\} $ , which is the lexicographically smallest one.

## 样例 #1

### 输入

```
3 2
1 2
1 3
```

### 输出

```
1 2 3 
```

## 样例 #2

### 输入

```
5 5
1 4
3 4
5 4
3 2
1 5
```

### 输出

```
1 4 3 2 5 
```

## 样例 #3

### 输入

```
10 10
1 4
6 8
2 5
3 7
9 4
5 6
3 4
8 10
8 9
1 10
```

### 输出

```
1 4 3 7 9 8 6 5 2 10 
```

# AI分析结果



### 算法分类
**贪心 + 优先队列（堆）**

---

### 题解思路与难点分析
#### 核心思路
- **贪心策略**：每一步选择当前可到达的最小节点，保证字典序最小。
- **数据结构**：用小根堆（`priority_queue`）或自动排序的集合（`set`）维护候选节点。
- **标记机制**：节点一旦加入堆/集合就标记为已访问，避免重复入队。

#### 难点对比
| 题解方案             | 核心难点解决                                                                 | 数据结构选择     | 时间复杂度 |
|----------------------|-----------------------------------------------------------------------------|------------------|------------|
| 优先队列（堆）       | 如何快速找到当前可访问的最小节点                                            | 小根堆           | O(m log n) |
| 集合（自动排序）     | 维护候选节点的有序性（需手动处理重复插入问题）                              | set              | O(m log n) |
| 链式前向星预处理排序 | 邻接表预处理时按节点编号排序，避免动态排序（但需额外预处理）                | 排序后的邻接表   | O(m log m) |

#### 关键实现细节
1. **标记时机**：节点在加入堆时立即标记为已访问（否则可能重复入队）。
2. **邻接表处理**：邻接表存储时需按升序排序（部分题解未显式排序，但堆自动处理顺序）。
3. **重边处理**：题目允许重边，但无需特殊处理（不影响贪心策略）。

---

### 题解评分（≥4星）
1. **Believe_R_**（⭐⭐⭐⭐⭐）  
   - **亮点**：详细解释堆的作用与贪心逻辑，代码附带注释，强调去重优化。
   - **代码**：使用链式前向星存图，优先队列维护候选节点。
   ```cpp
   priority_queue<int, vector<int>, greater<int>> q;
   q.push(1);
   while (!q.empty()) {
       int h = q.top(); q.pop();
       vis[h] = 1; ans[++sum] = h;
       for (遍历邻接节点) if (!vis[p]) { vis[p] = 1; q.push(p); }
   }
   ```

2. **lemon2021**（⭐⭐⭐⭐）  
   - **亮点**：类比 Dijkstra 算法，强调贪心与最短路的相似性，代码简洁。
   - **代码**：邻接表存图，优先队列直接处理节点编号。
   ```cpp
   vector<int> a[MAXN]; // 邻接表
   priority_queue<int, vector<int>, greater<int>> q;
   ```

3. **Dog_Two**（⭐⭐⭐⭐）  
   - **亮点**：明确指出与 Dijkstra 的优先级差异，代码高度简洁。
   - **代码**：直接使用 STL 邻接表，无需显式排序。
   ```cpp
   while (!q.empty()) {
       int u = q.top(); q.pop();
       if (vis[u]) continue;
       vis[u] = true; ans.push_back(u);
       for (auto v : G[u]) if (!vis[v]) q.push(v);
   }
   ```

---

### 最优思路提炼
1. **贪心选择**：每一步选当前可达的最小节点。
2. **堆维护候选集**：用小根堆动态维护可访问节点。
3. **立即标记策略**：节点入堆时立即标记，避免重复处理。

---

### 类似题目推荐
1. **[P5318 【深基18.例3】查找文献](https://www.luogu.com.cn/problem/P5318)**  
   （图的 DFS/BFS，需处理多邻接点排序）
2. **[CF977E Cyclic Components](https://codeforces.com/problemset/problem/977/E)**  
   （图遍历 + 环检测，需维护连通性）
3. **[P2278 操作系统](https://www.luogu.com.cn/problem/P2278)**  
   （优先队列模拟进程调度，类似贪心优先级）

---

### 个人心得摘录
- **Believe_R_**：  
  *“堆排序复杂度优秀，插入删除 O(log n)，比每次重新排序高效得多”*  
  （强调堆在动态维护有序性中的优势）

- **FlyInTheSky**：  
  *“扩展时就要打标记，否则 MLE 警告！”*  
  （关键实现教训：延迟标记会导致队列爆炸）

---

### 可视化设计
#### 核心动画逻辑
1. **节点状态颜色**：
   - **白色**：未访问  
   - **绿色**：在优先队列中  
   - **红色**：已加入结果序列  

2. **动画步骤**：
   - **Step 1**：初始节点1变绿，加入队列。
   - **Step 2**：弹出队列最小节点（高亮红色），遍历其邻接节点。
   - **Step 3**：将未访问的邻接节点变绿并入队。
   - **Step 4**：循环直到队列为空。

#### 复古像素风格实现
```javascript
// 伪代码：Canvas 绘制节点与队列
const canvas = document.getElementById('pixel-canvas');
const ctx = canvas.getContext('2d');

function drawNode(node, color) {
    ctx.fillStyle = color;
    ctx.fillRect(node.x * 16, node.y * 16, 14, 14); // 16x16 像素块
}

// 示例：节点1变绿
drawNode(node1, '#00FF00');
```

#### 音效设计
- **入队音效**：8-bit 短促“哔”声（Web Audio API 生成 500Hz 方波）。
- **出队音效**：低音“咚”声（200Hz 方波，持续 0.1秒）。

---

### 核心代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

vector<int> G[MAXN];
bool vis[MAXN];
vector<int> ans;

int main() {
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    
    priority_queue<int, vector<int>, greater<int>> q;
    q.push(1); vis[1] = true;
    
    while (!q.empty()) {
        int u = q.top(); q.pop();
        ans.push_back(u);
        for (int v : G[u]) {
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }
    }
    
    for (int x : ans) cout << x << " ";
    return 0;
}
```

---
处理用时：87.47秒