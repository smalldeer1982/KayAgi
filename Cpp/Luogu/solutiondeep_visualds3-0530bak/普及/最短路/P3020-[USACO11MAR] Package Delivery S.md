# 题目信息

# [USACO11MAR] Package Delivery S

## 题目描述

Farmer John must deliver a package to Farmer Dan, and is preparing to make his journey. To keep the peace, he gives a tasty treat to every cow that he meets along his way and, of course, FJ is so frugal that he would like to encounter as few cows as possible.

农夫约翰必须送一个包裹给农夫丹，并准备去旅行。为了保持和平，他必须给每一头遇到的奶牛一些吃的，当然，FJ很节俭，他想可能遇到尽可能少的奶牛。

FJ has plotted a map of N (1 <= N <= 50,000) barns, connected by M (1 <= M <= 50,000) bi-directional cow paths, each with C\_i (0 <= C\_i <= 1,000) cows ambling along it. A cow path connects two distinct barns, A\_i and B\_i (1 <= A\_i <= N; 1 <= B\_i <= N; A\_i != B\_i). Two barns may be directly connected by more than one path. He is currently located at barn 1, and Farmer Dan is located at barn N.

FJ 已经绘制了 $N(1 \le N \le 50000)$ 个谷仓的地图，通过 $M(1 \le M \le 50000)$ 条双向牛道，每条双向牛道上有 $c[i](0 \le c[i] \le 1000)$ 奶牛漫步。双向牛道连接两个不同的谷仓，$a[i]$ 和 $b[i](1 \le a[i] \le N,1 \le b[i] \le N, a[i] \neq b[i])$。两个谷仓可以由一条以上的小路直接连接。他目前在 $1$ 号谷仓，农夫丹位于 $N$ 号谷仓。

Consider the following map:

```cpp
           [2]---
          / |    \
         /1 |     \ 6
        /   |      \
     [1]   0|    --[3]
        \   |   /     \2
        4\  |  /4      [6]
          \ | /       /1
           [4]-----[5] 
                3  
```
The best path for Farmer John to take is to go from 1 -> 2 -> 4 -> 5 -> 6, because it will cost him 1 + 0 + 3 + 1 = 5 treats.

Given FJ's map, what is the minimal number of treats that he should bring with him, given that he will feed each distinct cow he meets exactly one treat? He does not care about the length of his journey.


## 样例 #1

### 输入

```
6 8 
4 5 3 
2 4 0 
4 1 4 
2 1 1 
5 6 1 
3 6 2 
3 2 6 
3 4 4 
```

### 输出

```
5 
```

# AI分析结果



## **唯一算法分类**  
**最短路算法（Dijkstra 堆优化）**

---

## **题解思路、算法要点与解决难点**  
### **核心思路**  
题目本质是求 **1 到 N 的最短路径**，路径权重为各边的奶牛数之和。由于边权非负（$C_i \geq 0$），适用 **Dijkstra 堆优化算法**，时间复杂度 $O((M+N)\log N)$。

### **关键实现对比**  
1. **数据结构**：  
   - 邻接表存储图（避免邻接矩阵空间爆炸）。  
   - 优先队列（堆）维护当前最短距离节点。  

2. **优化点**：  
   - **避免重复处理节点**：寒鸽儿提出用 `if(dnow > d[cur]) continue` 替代 `vis` 数组，减少冗余操作。  
   - **代码效率**：寒鸽儿通过快速读入（`read` 函数优化）提升性能，实测 72ms。  

3. **SPFA 的局限性**：  
   - Zekrom 的 SPFA 实现耗时 1163ms，表明在稀疏图中 SPFA 可能因常数因子劣于 Dijkstra。  
   - Exschawasion 指出 SPFA 可能被特殊数据卡成 $O(NM)$，而 Dijkstra 更稳定。

### **解决难点**  
- **大规模数据处理**：邻接表存储 + 堆优化保证时间和空间效率。  
- **正确初始化**：距离数组初始化为极大值，起点设为 0。  
- **双向边处理**：所有边需添加两次（无向图）。

---

## **题解评分 (≥4星)**  
1. **Sober_Clever（4.5星）**  
   - 代码简洁，标准 Dijkstra 堆优化模板。  
   - 快速读入提升效率，适合新手学习。  

2. **寒鸽儿（4.5星）**  
   - 优化 `vis` 判断逻辑，实测速度最快（72ms）。  
   - 代码规范，变量命名清晰，可读性强。  

3. **Zekrom（4星）**  
   - 提供 Dijkstra 和 SPFA 双实现，对比直观。  
   - 注释详细，适合理解算法差异。  

---

## **最优思路或技巧提炼**  
1. **Dijkstra 堆优化模板**：  
   ```cpp
   priority_queue<pair<int, int>> q;  
   q.push({0, 1});  
   while (!q.empty()) {  
       int u = q.top().second;  
       q.pop();  
       if (vis[u]) continue;  
       vis[u] = 1;  
       for (auto [v, w] : edges[u]) {  
           if (d[v] > d[u] + w) {  
               d[v] = d[u] + w;  
               q.push({-d[v], v});  // 小根堆技巧：存负数  
           }  
       }  
   }  
   ```  
2. **快速读入优化**：  
   ```cpp  
   inline int read() {  
       int x = 0, w = 1;  
       char c = getchar();  
       while (c < '0' || c > '9') { ... }  // 处理负号  
       while (c >= '0' && c <= '9') { ... } // 快速计算数值  
       return x * w;  
   }  
   ```  

---

## **同类型题或类似算法套路**  
- **单源最短路标准题**：洛谷 P4779（Dijkstra 模板）  
- **带负权边**：洛谷 P3385（SPFA 判负环）  
- **稀疏图优化**：洛谷 P4568（分层图最短路）  

---

## **个人心得摘录**  
- **Leap_Frog 的调试教训**：  
  > “把最短路求成最长路还能 AC&TLE 而不 WA？？？”  
  强调审题需仔细，确保模型正确性。  

- **寒鸽儿的代码哲学**：  
  > “建议使用 `if(dnow > d[cur]) continue` 代替 `vis` 数组，据说更高效。”  
  实践验证优化思路的重要性。  

---

## **可视化与算法演示**  
### **核心动画设计**  
1. **像素风格可视化**：  
   - **颜色标记**：  
     - 红色：当前处理的节点（堆顶元素）。  
     - 绿色：已确定最短路径的节点。  
     - 蓝色：优先队列中的候选节点。  
   - **网格绘制**：谷仓用像素方块表示，边权显示为奶牛数。  

2. **操作演示**：  
   - **步进执行**：点击按钮逐步展开 Dijkstra 的松弛过程。  
   - **动态更新距离数组**：右侧面板实时显示 `d[]` 的变化。  

3. **音效与反馈**：  
   - **松弛成功**：播放清脆“叮”声。  
   - **节点加入队列**：短促“咔哒”声。  

### **交互设计**  
- **控制面板**：  
  - 暂停/继续、单步执行、重置。  
  - 切换算法（Dijkstra vs SPFA）对比效率。  

---

## **代码片段（寒鸽儿优化版）**  
```cpp  
void dijkstra() {  
    memset(d, 0x3f, sizeof(d));  
    priority_queue<pair<int, int>> q;  
    q.push({0, 1});  
    d[1] = 0;  
    while (!q.empty()) {  
        int u = q.top().second;  
        int cur_d = -q.top().first;  
        q.pop();  
        if (cur_d > d[u]) continue;  // 关键优化  
        for (int i = head[u]; i != -1; i = nex[i]) {  
            int v = ver[i], w = wei[i];  
            if (d[v] > d[u] + w) {  
                d[v] = d[u] + w;  
                q.push({-d[v], v});  
            }  
        }  
    }  
}  
```  

---

**总结**：本题是经典最短路问题，堆优化 Dijkstra 是效率与稳定性的最佳选择。寒鸽儿的优化实现和 Exschawasion 的算法分析尤为值得学习。

---
处理用时：87.68秒