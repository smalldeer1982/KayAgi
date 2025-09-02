# 题目信息

# Pashmak and Graph

## 题目描述

Pashmak's homework is a problem about graphs. Although he always tries to do his homework completely, he can't solve this problem. As you know, he's really weak at graph theory; so try to help him in solving the problem.

You are given a weighted directed graph with $ n $ vertices and $ m $ edges. You need to find a path (perhaps, non-simple) with maximum number of edges, such that the weights of the edges increase along the path. In other words, each edge of the path must have strictly greater weight than the previous edge in the path.

Help Pashmak, print the number of edges in the required path.

## 说明/提示

In the first sample the maximum trail can be any of this trails: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF459E/46950f7ebb1a8fb1042610e7d90ce693216dd148.png).

In the second sample the maximum trail is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF459E/0a8ef1a8d44f73ed1581f13e754f7328cc98bdea.png).

In the third sample the maximum trail is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF459E/077a752077571978dd842d2ca5ed7e4dcecd7b85.png).

## 样例 #1

### 输入

```
3 3
1 2 1
2 3 1
3 1 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 3
1 2 1
2 3 2
3 1 3
```

### 输出

```
3
```

## 样例 #3

### 输入

```
6 7
1 2 1
3 2 5
2 4 2
2 5 2
2 6 9
5 4 3
4 3 4
```

### 输出

```
6
```

# AI分析结果

### 题目内容重写（中文）

Pashmak的作业是一个关于图的问题。尽管他总是尽力完成作业，但他无法解决这个问题。如你所知，他在图论方面非常薄弱，所以请尝试帮助他解决这个问题。

给定一个有向加权图，包含 $n$ 个顶点和 $m$ 条边。你需要找到一条路径（可能不是简单路径），使得路径中的边数最多，并且路径中的边权严格递增。换句话说，路径中的每条边的权值必须严格大于前一条边的权值。

帮助Pashmak，输出所需路径中的边数。

### 题解综合分析与结论

本题的核心是找到一条边权严格递增的路径，且路径中的边数最多。由于路径可以是非简单的（即允许重复经过节点），因此直接使用DFS或BFS会面临复杂的状态转移问题。题解中普遍采用动态规划（DP）的思路，结合边权排序来避免后效性。

#### 关键思路与技巧：
1. **边权排序**：将所有边按权值从小到大排序，确保在DP转移时，边权严格递增。
2. **DP状态转移**：设 $f[i]$ 表示以节点 $i$ 为终点的最长路径的边数。对于每条边 $(u, v, w)$，转移方程为 $f[v] = \max(f[v], f[u] + 1)$。
3. **处理相同边权**：由于要求边权严格递增，相同边权的边需要同时处理，避免相互影响。通常使用临时数组 $g$ 来存储相同边权下的DP值，最后再合并到 $f$ 中。

#### 最优题解推荐：
1. **Star_Cried (5星)**
   - **关键亮点**：思路清晰，代码简洁，通过临时数组 $g$ 处理相同边权的情况，确保DP转移的正确性。
   - **核心代码**：
     ```cpp
     for(int i=1,j;i<=m;i=j+1){
         j=i;
         while(e[j+1].val==e[i].val)j++;
         for(int k=i;k<=j;k++) g[e[k].u]=f[e[k].u],g[e[k].v]=f[e[k].v];
         for(int k=i;k<=j;k++) f[e[k].v]=max(f[e[k].v],g[e[k].u]+1);
     }
     ```

2. **BriMon (4星)**
   - **关键亮点**：详细解释了DP转移的思路，并通过栈来优化相同边权的处理，代码可读性较好。
   - **核心代码**：
     ```cpp
     for (reg int i = 1 ; i <= m ; i ++) {
         int j = i + 1;
         while(ed[i].val == ed[j].val) j ++;
         for (reg int k = i ; k < j ; k ++) {
             g[ed[k].y] = max(g[ed[k].y], f[ed[k].x] + 1);
             stack[++top] = ed[k].y;
         }
         while(top) {
             f[stack[top]] = max(f[stack[top]], g[stack[top]]);
             g[stack[top]] = 0;
             top--;
         }
         i = j - 1;
     }
     ```

3. **xy0313 (4星)**
   - **关键亮点**：通过优先队列处理相同边权的边，确保DP转移的顺序正确，思路较为新颖。
   - **核心代码**：
     ```cpp
     while(que.size()) {
         int u = que.top().x;
         que.pop();
         int x = e[u].x, y = e[u].y, w = e[u].z;
         if(f[x] + 1 > f[y]) {
             if(!cnt[x] || cnt[x] < w) {
                 f[y] = f[x] + 1;
                 cnt[y] = w;
             }
             else if(f[x] > f[y]) {
                 f[y] = f[x];
                 cnt[y] = w;
             }
         }
     }
     ```

### 拓展思路与推荐题目
- **拓展思路**：本题的DP思路可以推广到其他需要处理严格递增或递减的路径问题，如最长下降子序列等。
- **推荐题目**：
  1. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020) - 考察最长上升子序列的变种。
  2. [P1091 合唱队形](https://www.luogu.com.cn/problem/P1091) - 结合DP与图的最长路径问题。
  3. [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144) - 考察最短路径与DP的结合。

### 个人心得总结
- **Star_Cried**：通过临时数组 $g$ 处理相同边权的情况，确保DP转移的正确性，代码简洁高效。
- **BriMon**：使用栈来优化相同边权的处理，思路清晰，代码可读性较好。
- **xy0313**：通过优先队列处理相同边权的边，确保DP转移的顺序正确，思路较为新颖。

---
处理用时：42.94秒