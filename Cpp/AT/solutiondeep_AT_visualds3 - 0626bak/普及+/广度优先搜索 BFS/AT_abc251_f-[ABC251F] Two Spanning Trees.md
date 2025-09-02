# 题目信息

# [ABC251F] Two Spanning Trees

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc251/tasks/abc251_f

$ N $ 頂点 $ M $ 辺の無向グラフ $ G $ が与えられます。 $ G $ は**単純**（自己ループおよび多重辺を持たない）かつ**連結**です。

$ i\ =\ 1,\ 2,\ \ldots,\ M $ について、$ i $ 番目の辺は頂点 $ u_i $ と頂点 $ v_i $ を結ぶ無向辺 $ \lbrace\ u_i,\ v_i\ \rbrace $ です。

下記の $ 2 $ つの条件をともに満たすような $ G $ の $ 2 $ つの全域木 $ T_1,T_2 $ を $ 1 $ 組構成してください。（ $ T_1 $ と $ T_2 $ は異なる全域木である必要はありません。）

- $ T_1 $ は下記を満たす。
  
  > $ T_1 $ を頂点 $ 1 $ を根とする根付き木とみなしたとき、$ G $ の辺のうち $ T_1 $ に含まれないすべての辺 $ \lbrace\ u,\ v\ \rbrace $ について、$ u $ と $ v $ は $ T_1 $ において祖先と子孫の関係にある。
- $ T_2 $ は下記を満たす。
  
  > $ T_2 $ を頂点 $ 1 $ を根とする根付き木とみなしたとき、$ G $ の辺のうち $ T_2 $ に含まれない辺 $ \lbrace\ u,\ v\ \rbrace $ であって、$ u $ と $ v $ が $ T_2 $ において祖先と子孫の関係にあるようなものは存在しない。

ここで、「根付き木 $ T $ において頂点 $ u $ と頂点 $ v $ が祖先と子孫の関係にある」とは、「 $ T $ において $ u $ が $ v $ の祖先である」と「 $ T $ において $ v $ が $ u $ の祖先である」のうちどちらかが成り立つことをいいます。

本問題の制約下において上記の条件を満たす $ T_1 $ と $ T_2 $ は必ず存在することが示せます。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ N-1\ \leq\ M\ \leq\ \min\lbrace\ 2\ \times\ 10^5,\ N(N-1)/2\ \rbrace $
- $ 1\ \leq\ u_i,\ v_i\ \leq\ N $
- 入力はすべて整数
- 与えられるグラフは単純かつ連結

### Sample Explanation 1

上記の出力例において、$ T_1 $ は $ 5 $ 本の辺 $ \lbrace\ 1,\ 4\ \rbrace,\ \lbrace\ 4,\ 3\ \rbrace,\ \lbrace\ 5,\ 3\ \rbrace,\ \lbrace\ 4,\ 2\ \rbrace,\ \lbrace\ 6,\ 2\ \rbrace $ を持つ $ G $ の全域木です。この $ T_1 $ は問題文中の条件を満たします。実際、$ G $ の辺のうち $ T_1 $ に含まれない各辺に関して、 - 辺 $ \lbrace\ 5,\ 1\ \rbrace $ について、頂点 $ 1 $ は頂点 $ 5 $ の祖先であり、 - 辺 $ \lbrace\ 1,\ 2\ \rbrace $ について、頂点 $ 1 $ は頂点 $ 2 $ の祖先であり、 - 辺 $ \lbrace\ 1,\ 6\ \rbrace $ について、頂点 $ 1 $ は頂点 $ 6 $ の祖先です。 また、$ T_2 $ は $ 5 $ 本の辺 $ \lbrace\ 1,\ 5\ \rbrace,\ \lbrace\ 5,\ 3\ \rbrace,\ \lbrace\ 1,\ 4\ \rbrace,\ \lbrace\ 2,\ 1\ \rbrace,\ \lbrace\ 1,\ 6\ \rbrace $ を持つ $ G $ の全域木です。この $ T_2 $ は問題文中の条件を満たします。実際、$ G $ の辺のうち $ T_2 $ に含まれない各辺に関して、 - 辺 $ \lbrace\ 4,\ 3\ \rbrace $ について、頂点 $ 4 $ と頂点 $ 3 $ は祖先と子孫の関係になく、 - 辺 $ \lbrace\ 2,\ 6\ \rbrace $ について、頂点 $ 2 $ と頂点 $ 6 $ は祖先と子孫の関係になく、 - 辺 $ \lbrace\ 4,\ 2\ \rbrace $ について、頂点 $ 4 $ と頂点 $ 2 $ は祖先と子孫の関係にありません。

### Sample Explanation 2

$ 3 $ 本の辺 $ \lbrace\ 1,\ 2\rbrace,\ \lbrace\ 1,\ 3\ \rbrace,\ \lbrace\ 1,\ 4\ \rbrace $ を持つ木 $ T $ が $ G $ の唯一の全域木です。 $ G $ の辺のうちこの木 $ T $ に含まれない辺は存在しないので、明らかに、$ T $ は $ T_1 $ の条件と $ T_2 $ の条件をともに満たします。

## 样例 #1

### 输入

```
6 8

5 1

4 3

1 4

3 5

1 2

2 6

1 6

4 2```

### 输出

```
1 4

4 3

5 3

4 2

6 2

1 5

5 3

1 4

2 1

1 6```

## 样例 #2

### 输入

```
4 3

3 1

1 2

1 4```

### 输出

```
1 2

1 3

1 4

1 4

1 3

1 2```

# AI分析结果



1. **算法分类选择**  
   **其他搜索**

---

## 题解思路、算法要点与解决难点

### 核心思路
- **T₁构造（DFS生成树）**：通过深度优先搜索（DFS）遍历图生成的树，所有非树边均为返祖边（满足祖先-子孙关系）。
- **T₂构造（BFS生成树）**：通过广度优先搜索（BFS）遍历图生成的树，非树边仅存在于同层或跨层但无祖先关系的节点间。

### 算法要点
1. **DFS生成树**：
   - **访问顺序**：递归或栈实现，优先深入子节点。
   - **返祖边性质**：DFS遍历中未访问的相邻节点会被优先处理，保证非树边连接已访问节点时必为返祖边。
   - **数据结构**：递归栈、邻接表、`visited`数组。

2. **BFS生成树**：
   - **访问顺序**：队列实现，逐层扩展。
   - **层级结构**：同层节点无父子关系，跨层非树边节点最近公共祖先必为根节点。
   - **数据结构**：队列、邻接表、`visited`数组。

### 解决难点
- **DFS正确性证明**：需确保非树边只能是返祖边（DFS遍历顺序保证）。
- **BFS正确性证明**：需确保非树边不构成祖先-子孙关系（层级遍历避免跨层返祖）。

---

## 题解评分 (≥4星)

1. **Nahida_Buer (★★★★☆)**  
   - **亮点**：清晰区分DFS/BFS性质，代码简洁高效，直接输出遍历边。
   - **代码**：使用`bitset`优化访问标记，分离DFS/BFS逻辑。

2. **Pengzt (★★★★☆)**  
   - **亮点**：结合Tarjan算法背景，明确DFS无横叉边、BFS无返祖边的理论依据。
   - **代码**：逻辑简明，快速实现遍历。

3. **LionBlaze (★★★★☆)**  
   - **亮点**：通过图示直观解释DFS/BFS生成树的边类型差异。
   - **心得**：结合Gold定理分析DFS的横叉边排除机制。

---

## 最优思路或技巧提炼

1. **DFS/BFS性质利用**：
   - DFS的非树边必为返祖边，BFS的非树边必无祖先关系。
   - 直接输出DFS/BFS遍历的边即可构造满足条件的生成树。

2. **代码优化**：
   - 使用邻接表存储图，避免重复遍历。
   - 分离`visited`标记数组，分别处理DFS/BFS。

---

## 同类型题与类似算法套路

- **相似题目**：构造特定性质的生成树（如最小高度树、欧拉回路生成树）。
- **通用套路**：利用搜索算法的遍历顺序特性（如DFS的深度优先性、BFS的层级性）解决图结构问题。

---

## 推荐题目

1. [P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)  
   **关联**：DFS/BFS生成树与LCA计算。

2. [P1395 会议](https://www.luogu.com.cn/problem/P1395)  
   **关联**：BFS求树的中心。

3. [P2661 信息传递](https://www.luogu.com.cn/problem/P2661)  
   **关联**：DFS找环，返祖边应用。

---

## 个人心得摘录

- **Nahida_Buer**：通过样例推导DFS/BFS的应用，验证非树边性质。
- **LionBlaze**：图示辅助分析DFS的横叉边排除机制，增强理论理解。

---

## 可视化与算法演示

### 动画设计
1. **并行对比**：
   - **左侧Canvas**：展示DFS遍历，节点按递归深度染色（深色为深层）。
   - **右侧Canvas**：展示BFS遍历，节点按层级染色（同一层颜色相同）。

2. **交互功能**：
   - **步进控制**：按钮控制单步执行DFS/BFS。
   - **速度调节**：滑动条调整遍历速度。
   - **高亮标记**：当前访问节点（闪烁）、待访问队列（边框高亮）。

3. **复古像素风格**：
   - **节点**：8-bit方块，DFS用绿色渐变，BFS用蓝色渐变。
   - **音效**：访问节点时播放“哔”声，完成遍历播放胜利音效。

### 代码片段（伪代码）
```javascript
// DFS动画核心逻辑
function dfsStep(u) {
    highlight(u); // 高亮当前节点
    for (v of adj[u]) {
        if (!visited[v]) {
            drawEdge(u, v, 'green'); // 绘制树边
            visited[v] = true;
            setTimeout(() => dfsStep(v), 500); // 延迟递归
        } else if (isAncestor(v, u)) {
            drawEdge(u, v, 'red'); // 返祖边
        }
    }
}

// BFS动画核心逻辑
function bfsStep() {
    let u = queue.dequeue();
    highlight(u);
    for (v of adj[u]) {
        if (!visited[v]) {
            drawEdge(u, v, 'blue');
            visited[v] = true;
            queue.enqueue(v);
        } else if (!isSameLevel(u, v)) {
            drawEdge(u, v, 'yellow'); // 跨层非树边
        }
    }
    if (queue.length) setTimeout(bfsStep, 300);
}
```

---

## 核心代码实现（C++）

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
vector<int> adj[N];
bool vis[N];

void dfs(int u) {
    vis[u] = true;
    for (int v : adj[u]) {
        if (!vis[v]) {
            cout << u << " " << v << endl;
            dfs(v);
        }
    }
}

void bfs() {
    queue<int> q;
    q.push(1);
    vis[1] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (!vis[v]) {
                cout << u << " " << v << endl;
                vis[v] = true;
                q.push(v);
            }
        }
    }
}

int main() {
    int n, m; cin >> n >> m;
    while (m--) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1);
    memset(vis, 0, sizeof(vis));
    bfs();
    return 0;
}
```

---
处理用时：94.73秒