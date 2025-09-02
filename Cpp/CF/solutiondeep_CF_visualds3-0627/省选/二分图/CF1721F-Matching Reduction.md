# 题目信息

# Matching Reduction

## 题目描述

You are given a bipartite graph with $ n_1 $ vertices in the first part, $ n_2 $ vertices in the second part, and $ m $ edges. The maximum matching in this graph is the maximum possible (by size) subset of edges of this graph such that no vertex is incident to more than one chosen edge.

You have to process two types of queries to this graph:

- $ 1 $ — remove the minimum possible number of vertices from this graph so that the size of the maximum matching gets reduced exactly by $ 1 $ , and print the vertices that you have removed. Then, find any maximum matching in this graph and print the sum of indices of edges belonging to this matching;
- $ 2 $ — query of this type will be asked only after a query of type $ 1 $ . As the answer to this query, you have to print the edges forming the maximum matching you have chosen in the previous query.

Note that you should solve the problem in online mode. It means that you can't read the whole input at once. You can read each query only after writing the answer for the last query. Use functions fflush in C++ and BufferedWriter.flush in Java languages after each writing in your program.

## 说明/提示

In this problem, you may receive the verdict "Idleness Limit Exceeded" since it is in online mode. If it happens, it means that either the output format is wrong, or you don't meet some constraint of the problem. You may treat this verdict as "Wrong Answer".

For your convenience, the output for queries in the example is separated by the line ===. Don't print this line in your program, it is done only to make sure that it's easy to distinguish between answers for different queries in the statement.

## 样例 #1

### 输入

```
3 4 4 4
2 2
1 3
2 1
3 4
1
2
1
2```

### 输出

```
1
-4
3
===
2
1 2
===
1
2
2
===
1
2```

# AI分析结果



## 唯一算法分类  
**二分图匹配/网络流 + König定理**

---

## 题解思路与算法要点  
### 核心思路  
1. **König定理**：二分图的最大匹配等于最小点覆盖的大小。删除最小点覆盖中的任意一点，最大匹配减少1。  
2. **残量网络标记**：通过最大流的残量网络，DFS标记可达点，构造最小点覆盖。左部未被标记的点和右部被标记的点组成最小点覆盖。  
3. **动态维护匹配边**：记录当前匹配的边及其总和，删除点时同步更新。

### 解决难点  
- **如何确定最小点覆盖**：通过DFS遍历残量网络，标记从源点可达的顶点。  
- **高效维护匹配边**：使用数组记录每条边的状态，总和通过前缀和或直接累减。  

---

## 题解评分（≥4星）  
1. **Alex_Wei（5星）**  
   - **亮点**：利用独立集与最大匹配的关系，代码结构清晰，直接维护匹配边总和。  
   - **代码片段**：  
     ```cpp  
     for(int i = 1; i <= IC; i++)  
         for(int j = h.hd[i]; j; j = h.nxt[j]) {  
             int it = h.to[j];  
             if(it <= IC || h.limit[j]) continue;  
             eid[i] = mp[{i, it}];  
             sum[i] = sum[i - 1] + eid[i];  
         }  
     ```  
2. **Leasier（4星）**  
   - **亮点**：通过BFS+DFS标记残量网络，直观构造候选点列表。  
   - **代码片段**：  
     ```cpp  
     void dfs2(int u) {  
         vis[u] = true;  
         for(register int i = head[u]; i; i = edge[i].nxt)  
             if(edge[i].dis && !vis[edge[i].end])  
                 dfs2(edge[i].end);  
     }  
     ```  
3. **do_while_true（4星）**  
   - **亮点**：直接维护最小点覆盖集合，删除点后动态更新总和。  

---

## 最优技巧提炼  
1. **残量网络标记法**：通过DFS标记残量网络中源点可达的顶点，快速构造最小点覆盖。  
2. **前缀和优化**：预处理匹配边的前缀和，实现O(1)时间查询总和。  
3. **边状态数组**：用`evis[]`标记每条边是否在当前匹配中，便于快速维护和查询。  

---

## 同类型题目推荐  
1. **P3386**：二分图最大匹配模板题。  
2. **P2764**：最小路径覆盖，需转化为二分图匹配。  
3. **P3355**：骑士共存问题，涉及最大独立集。  

---

## 可视化设计  
### 动画方案  
1. **残量网络标记**：  
   - **颜色区分**：红色表示最小点覆盖中的点，绿色表示其他点。  
   - **动态DFS**：实时展示DFS过程，标记可达点。  
2. **删除点与匹配更新**：  
   - **高亮删除点**：闪烁显示当前删除的顶点。  
   - **匹配边消失**：删除点后，关联的匹配边变为灰色。  
3. **音效与8位风格**：  
   - **音效**：删除点时播放“哔”声，匹配更新时播放“叮”声。  
   - **像素网格**：顶点和边用8位像素块表示，背景音乐为循环芯片音乐。  

### 交互设计  
- **步进控制**：支持暂停/继续，调节动画速度。  
- **自动模式**：AI自动执行删除点操作，展示最优路径。  

---

## 个人心得摘录  
- **Leasier**：强调正确标记残量网络中的点是关键，需注意DFS的方向（从源点或汇点出发）。  
- **Alex_Wei**：通过`assert`验证独立集与匹配的关系，避免逻辑错误。  

---

## 代码实现（核心逻辑）  
```cpp  
// 残量网络标记（Leasier代码片段）  
void dfs2(int u) {  
    vis[u] = true;  
    for(int i = head[u]; i; i = edge[i].nxt) {  
        if(edge[i].dis && !vis[edge[i].end])  
            dfs2(edge[i].end);  
    }  
}  

// 构造候选点列表  
for(int i = 1; i <= n1; i++)  
    if(!vis[i]) candiate[++cnt] = i;  
for(int i = 1; i <= n2; i++)  
    if(vis[i + n1]) candiate[++cnt] = i + n1;  

// 处理类型1查询  
int u = candiate[ptr++];  
sum -= link[u];  
printf("%d\n", u <= n1 ? u : -(u - n1));  
```

---
处理用时：84.48秒