# 题目信息

# [USACO09DEC] Dizzy Cows G

## 题目描述

The cows have taken to racing each other around the farm but they get very dizzy when running in circles, and everyone knows that dizzy cows don't produce any milk. Farmer John wants to convert all of the two-way cow paths in the farm to one-way paths in order to eliminate any 'cycles' and prevent the cows from getting dizzy.  A 'cycle' enables a cow to traverse one or more cow paths and arrive back at her starting point, thus completing a loop or circle.

The farm comprises N pastures (1 <= N <= 100,000) conveniently numbered 1..N. M1 (1 <= M1 <= 100,000) one-way cow paths and M2 two-way cow paths (1 <= M2 <= 100,000) connect the pastures. No path directly connects a pasture to itself, although multiple paths might connect two different pastures. A cow may or may not be able to travel between any two given pastures by following a sequence of cow paths.

Your job is to assign a direction to the two-way cow paths such that the entire farm (ultimately with only one-way paths) has no cycles. That is, there should be no sequence of one-way cow paths which leads back to its starting position. The existing one-way cow paths do not form a cycle and should be left as they are.

One-way cow paths run from pasture A\_i (1 <= A\_i <= N) to pasture B\_i (1 <= B\_i <= N). Two-way cow paths connect pastures X\_i (1 <= X\_i <= N) and Y\_i (1 <= Y\_i <= N).

Consider this example:

```cpp
1-->2 
|  /| 
| / | 
|/  | 
3<--4 
```
The cow paths between pastures 1 and 3, 2 and 3, and 2 and 4 are two-way paths. One-way paths connect 1 to 2 and also 4 to 3. One valid way to convert the two-way paths into one-way paths in such a way that there are no cycles would be to direct them from 1 to 3, from 2 to 3, and from 3 to 4:

```cpp
1-->2 
|  /| 
| / | 
vL  v 
3<--4 
```


## 样例 #1

### 输入

```
4 2 3
1 2
4 3
1 3
4 2
3 2
```

### 输出

```
1 3
4 2
2 3```

# AI分析结果

### 综合分析与结论
这些题解的核心思路都是利用拓扑排序来解决问题。拓扑排序可以得到图中节点的一个线性顺序，使得对于有向边 $(u, v)$，$u$ 在顺序中总是在 $v$ 之前，基于这个性质来确定无向边的方向，从而保证图中无环。

各题解的主要区别在于实现拓扑排序的方式（如使用 BFS 或 DFS）以及处理无向边的细节。部分题解使用邻接表存储图，部分使用 `vector` 存储边信息，还有的使用自定义结构体来记录边的属性。

### 所选题解
- **作者：小年轻w（4星）**
  - **关键亮点**：思路清晰，代码实现简洁明了，使用邻接表存储图，通过标记无向边的方式确定其方向，避免形成环。
  - **个人心得**：无

### 重点代码
```cpp
// 小年轻w的题解
inline void addedge(int x,int y,int w) 
{
    e[++cnt].to = y;e[cnt].from=x;
    e[cnt].pre = head[x] ;
    e[cnt].val=w; 
    head[x] =cnt;
}
int main(){
    scanf("%d%d%d",&n,&e1,&e2) ;
    for(int i=1;i<=e1;i++) {
        scanf("%d%d",&x,&y) ;
        addedge(x,y,0);into[y]++;
    } 
    for(int i=1;i<=n;i++) 
        if(into[i]==0) q[++t]=i;
    if(cnt%2==0) cnt++;
    for(int i=1;i<=e2;i++){
        scanf("%d%d",&x,&y);
        addedge(x,y,1);
        addedge(y,x,1);
    }
    while(h<t) {
        int u=q[++h] ; 
        for(int i=head[u];i;i=e[i].pre) {
            if(e[i].val==0) {
                into[e[i].to]--; 
                if(into[e[i].to]==0) q[++t]=e[i].to;
            } 
         }
         for(int i=head[u];i;i=e[i].pre)
             if(e[i].val==1) e[i^1].val=2;
     }
    for(int i=1;i<=cnt;i++)
        if(e[i].val==1) printf("%d %d\n",e[i].from,e[i].to);
    return 0 ;
}
```
**核心实现思想**：
1. 首先读入有向边和无向边，有向边记录入度，无向边双向添加但不记录入度。
2. 将入度为 0 的节点加入队列。
3. 进行拓扑排序，对于有向边，更新其指向节点的入度，若入度变为 0 则加入队列；对于无向边，标记其反向边，以确定方向。
4. 最后输出所有标记为未处理的无向边。

### 最优关键思路或技巧
- **利用拓扑排序的性质**：拓扑排序得到的节点顺序可以保证有向边的方向一致性，通过这个顺序来确定无向边的方向，能有效避免环的形成。
- **标记无向边**：在拓扑排序过程中，对无向边进行标记，确保每条无向边只被处理一次，并且方向确定后不会改变。

### 可拓展之处
同类型题或类似算法套路：
- **有向图的环检测**：在拓扑排序过程中，如果最终存在节点的入度不为 0，则说明图中存在环。
- **任务调度问题**：给定一系列任务和任务之间的依赖关系，如何安排任务的执行顺序，使得所有任务都能完成且不违反依赖关系。

### 推荐题目
- [P1137 旅行计划](https://www.luogu.com.cn/problem/P1137)：拓扑排序求最长路径。
- [P1347 排序](https://www.luogu.com.cn/problem/P1347)：通过拓扑排序判断图的连通性和是否存在环。
- [P2746 [USACO5.3]校园网Network of Schools](https://www.luogu.com.cn/problem/P2746)：涉及图的强连通分量和拓扑排序。

### 个人心得摘录与总结
- **Christopher_Yan**：一开始按直觉写了假拓扑，WA 成 10 分，后来仔细考虑拓扑的本质，发现直接按拓扑排序将走过的无向边染色即可。总结为对拓扑排序的理解要深入，不能仅凭直觉，要仔细思考其本质和应用场景。 

---
处理用时：34.99秒