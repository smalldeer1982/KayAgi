# 题目信息

# Mahmoud and Ehab and the bipartiteness

## 题目描述

Mahmoud and Ehab continue their adventures! As everybody in the evil land knows, Dr. Evil likes bipartite graphs, especially trees.

A tree is a connected acyclic graph. A bipartite graph is a graph, whose vertices can be partitioned into $ 2 $ sets in such a way, that for each edge $ (u,v) $ that belongs to the graph, $ u $ and $ v $ belong to different sets. You can find more formal definitions of a tree and a bipartite graph in the notes section below.

Dr. Evil gave Mahmoud and Ehab a tree consisting of $ n $ nodes and asked them to add edges to it in such a way, that the graph is still bipartite. Besides, after adding these edges the graph should be simple (doesn't contain loops or multiple edges). What is the maximum number of edges they can add?

A loop is an edge, which connects a node with itself. Graph doesn't contain multiple edges when for each pair of nodes there is no more than one edge between them. A cycle and a loop aren't the same .

## 说明/提示

Tree definition: <a>https://en.wikipedia.org/wiki/Tree\_(graph\_theory)</a>

Bipartite graph definition: [https://en.wikipedia.org/wiki/Bipartite\_graph](https://en.wikipedia.org/wiki/Bipartite_graph)

In the first test case the only edge that can be added in such a way, that graph won't contain loops or multiple edges is $ (2,3) $ , but adding this edge will make the graph non-bipartite so the answer is 0.

In the second test case Mahmoud and Ehab can add edges $ (1,4) $ and $ (2,5) $ .

## 样例 #1

### 输入

```
3
1 2
1 3
```

### 输出

```
0
```

## 样例 #2

### 输入

```
5
1 2
2 3
3 4
4 5
```

### 输出

```
2
```

# AI分析结果



# Mahmoud and Ehab and the bipartiteness

## 题目描述

Mahmoud和Ehab继续他们的冒险！在邪恶之地，所有人都知道Dr. Evil喜欢二分图，尤其是树。

树是一个无环连通图。二分图是指可以将顶点分成两个集合，使得每条边的两个顶点属于不同集合的图。题目要求在一棵给定的树中添加尽可能多的边，使得最终的图仍然是二分图且是简单图（无自环和重边），求最大可添加的边数。

## 说明/提示
- 树定义：连通无环图
- 二分图定义：顶点可划分为两个互不相交的集合，每条边连接两个不同集合的顶点
- 样例1中无法添加边，样例2可添加两条边

---

### 关键思路总结
1. **树天然是二分图**：通过染色法将节点分为黑白两组，相邻节点颜色不同
2. **最大边数公式**：完全二分图边数为两集合节点数乘积，减去原有边数(n-1)即为答案
3. **实现方式**：DFS/BFS染色统计两色节点数，套用公式计算

---

### 精选题解分析

#### 1. Hamer_sans（★★★★★）
**核心亮点**：
- 详细解释二分图性质及公式推导
- 强调long long类型防止溢出
- 完整实现邻接表存储+DFS染色
```cpp
void dfs(int x,int pos){
    color[x] = pos;
    ++cnt[pos];
    for(int i=head[x];i;i=ne[i]){
        int y=ver[i];
        if(!color[y]) dfs(y,3-pos);
    }
}
```
**个人心得**："十年OI一场空，不开long long见祖宗"

#### 2. SuperJvRuo（★★★★☆）
**核心亮点**：
- 代码简洁高效（仅35行）
- 使用结构体存储邻接表
- 直接推导式输出结果
```cpp
void dfs(int point,int c){
    color[point]=c;
    ++cnt[c];
    for(int i=first[point];i;i=edge[i].next)
        if(!color[edge[i].to])
            dfs(edge[i].to,c==1?2:1);
}
```

#### 3. BreakPlus（★★★★☆）
**创新点**：
- 使用BFS实现染色
- 层次计算通过深度奇偶性
- 代码包含错误检测机制
```cpp
void bfs(int x){
    while(!que.empty()){
        int tmp=que.front();
        que.pop();
        vis[tmp]=1;
        for(int i=0;i<edge[tmp].size();i++){
            int nowp=edge[tmp][i];
            if(col[nowp]==col[tmp]) return; // 错误检测
            if(!vis[nowp]){
                que.push(nowp);
                col[nowp]=(col[tmp]+1)%2;
            }
        }
    }
}
```

---

### 相似题目推荐
1. P3386 【模板】二分图匹配
2. P1330 封锁阳光大学（二分图染色应用）
3. P1155 双栈排序（二分图性质应用）

---

### 扩展思考
当树变为普通图时，需先检测是否为二分图（无奇环）。同类问题可变形为求最大匹配数、最小顶点覆盖等，均可通过染色法扩展解决。二分图性质在社交网络划分、任务调度等问题中有广泛应用。

---
处理用时：39.96秒