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



### 综合分析与结论
该题为单源最短路模板题，核心是选择合适的最短路算法并正确实现。所有题解均围绕 Dijkstra 堆优化与 SPFA 展开，关键差异在于算法选择、重复节点处理优化、代码风格等。在 5w 级数据下，堆优化 Dijkstra 更稳定，SPFA 存在被极端数据卡风险。

---

### 高星题解推荐

#### 1. 寒鸽儿（⭐⭐⭐⭐⭐）
**关键亮点**：  
- 采用「松弛前判断 d[cur] 有效性」代替传统 vis 数组，避免无效松弛  
- 代码简洁高效（72ms），使用快速读入优化  
- 邻接表采用 -1 终止标记，减少内存占用  

**核心代码片段**：
```cpp
if(dmen > d[cur]) continue; // 关键优化点
for(int i = head[cur]; i != -1; i = nex[i])
    if(d[ver[i]] > d[cur] + wei[i]) {
        d[ver[i]] = d[cur] + wei[i];
        q.push(make_pair(-d[ver[i]], ver[i]));
    }
```

#### 2. Zekrom（⭐⭐⭐⭐）
**关键亮点**：  
- 同时提供 Dijkstra 与 SPFA 实现，对比实测时间（159ms vs 1163ms）  
- 标准邻接表实现，代码可读性强  
- 包含详细输入输出模板，适合新手学习  

**算法对比**：
```cpp
// Dijkstra 核心
priority_queue<pair<int,int>> q;
if(d[v] > d[u] + z){
    d[v] = d[u] + z;
    q.push(make_pair(-d[v], v)); 
}

// SPFA 核心
if(d[to] > d[x] + len){
    d[to] = d[x] + len;
    if(!vis[to]) Q.push(to), vis[to]=1;
}
```

#### 3. Exschawasion（⭐⭐⭐⭐）
**关键亮点**：  
- 系统分析各最短路算法优劣，制作对比表格  
- 强调算法选择策略（无负权首选 Dijkstra）  
- 提供完整 SPFA 实现，代码结构清晰  

**关键见解**：
> "SPFA 平均情况 O(kM) 但可能被网格图卡到 O(NM)，比赛中优先选择 Dijkstra"

---

### 关键思路与技巧
1. **堆优化 Dijkstra 实现要点**：  
   - 优先队列存储负数实现小根堆：`q.push(make_pair(-d[v], v))`  
   - 松弛前检查 `if(dmen > d[cur])` 跳过无效节点  
   - 使用 0x3f3f3f3f 初始化距离数组  

2. **邻接表优化**：  
   - 双向边需两次 `addedge(u,v,w)`  
   - 采用链式前向星存储，内存更紧凑  

3. **输入输出优化**：  
   - 快速读入函数（如寒鸽儿的位运算实现）  
   - 避免使用 `cin/cout` 防止超时  

---

### 同类题目推荐
1. [P4779【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)  
   - 强化版 Dijkstra 练习，数据规模更大  

2. [P3371【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)  
   - 基础最短路实现，适合新手  

3. [P3385【模板】负环](https://www.luogu.com.cn/problem/P3385)  
   - 练习 SPFA 判断负环技巧  

---

### 题解个人心得摘录
**Leap_Frog 的调试经历**：  
> "把最短路求成长路导致 TLE，提醒务必注意松弛方向。即使代码逻辑正确，算法目标错误也会导致灾难性后果"

**寒鸽儿的优化经验**：  
> "用 `dnow > d[cur]` 代替 vis 数组，实测可提升约 30% 效率，这对大规模数据至关重要"  

**Exschawasion 的算法选择**：  
> "SPFA 的代码量略大于 Dijkstra，但能处理负权。比赛中若无负权，优先选择更稳定的堆优化 Dijkstra"

---
处理用时：51.01秒