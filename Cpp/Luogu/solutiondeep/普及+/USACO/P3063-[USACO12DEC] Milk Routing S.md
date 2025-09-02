# 题目信息

# [USACO12DEC] Milk Routing S

## 题目描述

Farmer John's farm has an outdated network of M pipes (1 <= M <= 500) for pumping milk from the barn to his milk storage tank.  He wants to remove and update most of these over the next year, but he wants to leave exactly one path worth of pipes intact, so that he can still pump milk from the barn to the storage tank.

The pipe network is described by N junction points (1 <= N <= 500), each of which can serve as the endpoint of a set of pipes.  Junction point 1 is the barn, and junction point N is the storage tank.  Each of the M bi-directional pipes runs between a pair of junction points, and has an associated latency (the amount of time it takes milk to reach one end of the pipe from the other) and capacity (the amount of milk per unit time that can be pumped through the pipe in steady state).  Multiple pipes can connect between the same pair of junction points.

For a path of pipes connecting from the barn to the tank, the latency of the path is the sum of the latencies of the pipes along the path, and the capacity of the path is the minimum of the capacities of the pipes along the path (since this is the "bottleneck" constraining the overall rate at which milk can be pumped through the path).  If FJ wants to send a total of X units of milk through a path of pipes with latency L and capacity C, the time this takes is therefore L + X/C.

Given the structure of FJ's pipe network, please help him select a single path from the barn to the storage tank that will allow him to pump X units of milk in a minimum amount of total time.




## 说明/提示

FJ wants to send 15 units of milk through his pipe network.  Pipe #1 connects junction point 1 (the barn) to junction point 2, and has a latency of 10 and a capacity of 3.  Pipes #2 and #3 are similarly defined.


The path 1->3 takes 14 + 15/1 = 29 units of time.  The path 1->2->3 takes 20 + 15/2 = 27.5 units of time, and is therefore optimal.


约翰想要通过管网运送15个单位的牛奶。管道1连接节点1（谷仓）和节点2，延迟为10，容量为3。管道2和管道3也以相似的方式来定义。


路径1->3花费14+15/1=29个单位的时间。路径1->2->3花费20+15/2=27.5个单位的时间，用时最少。


## 样例 #1

### 输入

```
3 3 15 
1 2 10 3 
3 2 10 2 
1 3 14 1 
```

### 输出

```
27 
```

# AI分析结果

### 综合分析与结论
这些题解主要围绕如何在给定的图中找到一条路径，使得运送牛奶的总时间 $L + X/C$ 最小。由于需要同时考虑延迟 $L$ 和容量 $C$ 两个相互矛盾的因素，大部分题解采用枚举容量，再跑最短路求延迟的思路。算法上主要使用 DFS、SPFA、Dijkstra 等。

### 所选题解
- **作者：Eleven谦 (赞：23)，4星**
    - **关键亮点**：思路清晰，详细阐述了同时维护 $L$ 和 $C$ 两个值的困难，并逐步引导出枚举容量的解题思路，代码注释详细。
    - **个人心得**：无

### 重点代码
```cpp
// 枚举容量，跑最短路更新答案
for(register int i=1;i<=m;i++) {
    dijkstra(flag[i]);
    if(dis[n]!=20050206) ans=min(ans,dis[n]+x/flag[i]);
}
```
**核心实现思想**：通过枚举每条边的容量，以该容量为限制条件跑 Dijkstra 最短路，求出对应的延迟 $L$，进而计算 $L + X/C$，取最小值作为最终答案。

### 最优关键思路或技巧
- **枚举容量**：由于 $L$ 和 $C$ 相互矛盾，无法同时维护，通过枚举容量，固定一个值，再跑最短路求另一个值，将问题简化。
- **最短路算法**：使用 Dijkstra 或 SPFA 等最短路算法，在枚举容量的基础上，快速求出对应的延迟。

### 可拓展之处
同类型题或类似算法套路：当遇到需要同时考虑多个相互矛盾的因素的最短路问题时，可采用枚举其中一个因素，再求解另一个因素的方法。

### 推荐题目
1. [P5837 [USACO19DEC]Milk Pumping G](https://www.luogu.com.cn/problem/P5837)
2. [P1462 通往奥格瑞玛的道路](https://www.luogu.com.cn/problem/P1462)
3. [P3063 [USACO12DEC]Milk Routing S](https://www.luogu.com.cn/problem/P3063)

### 个人心得摘录与总结
- **作者：sunxiaofan**：提到原 spfa 做法存在“后效性”问题，在第 11 个测试点会 wa，通过跑两次 spfa（一次从 1 到 n，一次从 n 到 1）解决该问题。总结：在处理复杂的最短路问题时，要注意数据的特殊性，可能存在后效性等问题，需要通过多次计算或其他方法来解决。 

---
处理用时：22.60秒