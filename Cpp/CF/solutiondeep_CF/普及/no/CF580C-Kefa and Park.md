# 题目信息

# Kefa and Park

## 题目描述

Kefa decided to celebrate his first big salary by going to the restaurant.

He lives by an unusual park. The park is a rooted tree consisting of $ n $ vertices with the root at vertex $ 1 $ . Vertex $ 1 $ also contains Kefa's house. Unfortunaely for our hero, the park also contains cats. Kefa has already found out what are the vertices with cats in them.

The leaf vertices of the park contain restaurants. Kefa wants to choose a restaurant where he will go, but unfortunately he is very afraid of cats, so there is no way he will go to the restaurant if the path from the restaurant to his house contains more than $ m $ consecutive vertices with cats.

Your task is to help Kefa count the number of restaurants where he can go.

## 说明/提示

Let us remind you that a tree is a connected graph on $ n $ vertices and $ n-1 $ edge. A rooted tree is a tree with a special vertex called root. In a rooted tree among any two vertices connected by an edge, one vertex is a parent (the one closer to the root), and the other one is a child. A vertex is called a leaf, if it has no children.

Note to the first sample test: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF580C/3cc68e912c69745e5c96ffcfeb5680e415b9867a.png) The vertices containing cats are marked red. The restaurants are at vertices 2, 3, 4. Kefa can't go only to the restaurant located at vertex $ 2 $ .

Note to the second sample test: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF580C/3d11dcb54f6b1deed424e5699c584e06f67a1d2b.png) The restaurants are located at vertices 4, 5, 6, 7. Kefa can't go to restaurants 6, 7.

## 样例 #1

### 输入

```
4 1
1 1 0 0
1 2
1 3
1 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
7 1
1 0 1 1 0 0 0
1 2
1 3
2 4
2 5
3 6
3 7
```

### 输出

```
2
```

# AI分析结果



# 中文题目重写  
## Kefa 与公园  

### 题目描述  
Kefa 决定用他的第一笔大薪水去餐厅庆祝。  
他住在一个奇特的公园旁，该公园是由 $n$ 个顶点构成的带根树（根在顶点 1）。顶点 1 也是 Kefa 的家。不幸的是，公园里某些顶点有猫。  

树的叶子节点包含餐厅。Kefa 想选择一个餐厅前往，但他非常害怕猫，因此如果从餐厅到家的路径中出现超过 $m$ 个连续有猫的顶点，他就不会选择该餐厅。  

请帮助 Kefa 计算他能去的餐厅数量。  

### 输入输出要求  
输入包含树结构、节点猫标记和约束条件，输出合法餐厅数目。  

**算法分类**：深度优先搜索 DFS  

---

# 题解分析与结论  
**核心思路**：通过DFS遍历树结构，在路径遍历时维护连续猫节点计数，当遇到叶子节点时验证路径合法性。  

**关键技巧**：  
1. **连续计数维护**：根据当前节点是否含猫，决定清零或递增连续计数器  
2. **剪枝优化**：当连续计数超过 m 时立即终止该路径的遍历  
3. **叶节点判定**：通过邻接表长度或度数判断（需排除根节点特殊情况）  

---

# 精选题解  

## 题解1：作者 sukimo（4星）  
**关键亮点**：  
- 三参数维护（当前节点、当前连续、历史最大连续）  
- 入度判断叶节点（避免根节点误判）  
- 双向边处理（防止父节点回溯）  

**核心代码**：  
```cpp  
void dfs(int x, int now_cnt, int _max) {
    if (_max > m) return;
    if (in[x] == 1 && x != 1) { tot++; return; } // 叶节点判定
    vis[x] = 1;
    for (int i = fir[x]; i; i = edge[i].next) {
        int v = edge[i].to;
        if (!vis[v]) {
            int q = val[v] ? now_cnt + 1 : 0;
            dfs(v, q, max(_max, q)); // 传递当前连续与历史最大
        }
    }
}
```  

---

## 题解2：作者 Z1qqurat（4星）  
**关键亮点**：  
- 使用vector邻接表简化树结构存储  
- 参数设计简洁（当前节点、父节点、连续计数）  
- 叶节点判断逻辑清晰  

**核心代码**：  
```cpp  
void dfs(int x, int fa, int sum) {
    if (sum > m) return;
    if (x != 1 && T[x].size() == 1) { dp++; return; } // 叶节点判断
    for (int y : T[x]) {
        if (y == fa) continue;
        if (a[y] == 1) dfs(y, x, sum + 1);
        else dfs(y, x, 0); // 根据猫标记重置或累加
    }
}
```  

---

## 题解3：作者 D2T1（4星）  
**关键亮点**：  
- 显式处理根节点初始值（a[1]的初始传递）  
- 使用邻接表size直接判断叶节点  
- 参数命名清晰易懂  

**核心代码**：  
```cpp  
void dfs(int u, int fa, int sum) {
    if (sum > m) return;
    if (u != 1 && Edge[u].size() == 1) { ans++; return; }
    for (int v : Edge[u]) {
        if (v == fa) continue;
        if (a[v]) dfs(v, u, sum + 1);
        else dfs(v, u, 0); // 清零逻辑
    }
}
```  

---

# 同类题目推荐  
1. [P1359 二叉苹果树](https://www.luogu.com.cn/problem/P1359) - 树形DP与路径选择  
2. [P2015 二叉苹果树（加强版）](https://www.luogu.com.cn/problem/P2015) - 树状结构路径约束  
3. [CF977E Cyclic Components](https://www.luogu.com.cn/problem/CF977E) - 图遍历与连通块性质

---
处理用时：56.95秒