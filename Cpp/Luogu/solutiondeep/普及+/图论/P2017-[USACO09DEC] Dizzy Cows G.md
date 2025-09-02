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
这些题解核心思路均围绕拓扑排序展开，旨在为无向边确定方向以构建有向无环图（DAG）。不同题解在实现细节上有所差异，如存边方式、拓扑排序的具体操作等，但本质都是利用拓扑序为无向边定向。

### 所选题解
- **作者：小年轻w（5星）**
    - **关键亮点**：思路清晰，代码简洁高效，详细注释便于理解，对拓扑排序过程处理得当。
    - **核心代码**：
```cpp
while(h<t) {
    int u=q[++h]; 
    for(int i=head[u];i;i=e[i].pre) {
        if(e[i].val==0) {
            into[e[i].to]--; 
            if(into[e[i].to]==0) q[++t]=e[i].to;
        } 
    }
    for(int i=head[u];i;i=e[i].pre)
        if(e[i].val==1) e[i^1].val=2;
}
```
    - **核心思想**：通过拓扑排序，先处理有向边更新入度，再标记无向边方向，确保无环。

- **作者：Hehe_0（4星）**
    - **关键亮点**：提供了BFS和DFS两种拓扑排序实现方式，代码注释详细，适合学习拓扑排序。
    - **BFS核心代码**：
```cpp
while(q.size()>0)
{
    int x=q.front();
    q.pop();
    t[x]=cnt++;
    for(int i=0;i<a[x].size();i++)
    {
        in[a[x][i]]--;
        if(in[a[x][i]]==0)
            q.push(a[x][i]);
    }
}
```
    - **核心思想**：BFS进行拓扑排序，记录节点拓扑序，根据拓扑序为无向边定向。
    - **DFS核心代码**：
```cpp
void dfs(int x) 
{ 
    for(int i=0;i<a[x].size();i++)
    { 
        if(!v[a[x][i]])
            dfs(a[x][i]);
    }
    v[x]=1;
    t[x]=cnt;
    cnt++;
    return ; 
}
```
    - **核心思想**：DFS进行拓扑排序，记录节点拓扑序，根据拓扑序为无向边定向。

- **作者：小手冰凉（4星）**
    - **关键亮点**：代码简洁，逻辑清晰，准确实现了拓扑排序为无向边定向的思路。
    - **核心代码**：
```cpp
void topsort()
{
    while(!q.empty()){
        int now=q.front(); q.pop();
        for(int i=l[now];i;i=e[i].next)
            if(!(--d[e[i].y])){
                q.push(e[i].y);
                t[e[i].y]=++cnt;
            }
    }
}
```
    - **核心思想**：拓扑排序记录节点拓扑序，根据拓扑序为无向边定向。

### 最优关键思路或技巧
- **利用拓扑序定向**：拓扑排序后，无向边从拓扑序小的点指向拓扑序大的点，可保证图无环。
- **标记无向边**：在拓扑排序过程中，标记无向边方向，避免重复处理。

### 拓展思路
同类型题可拓展到更复杂的图结构，如带权图、多重边图等。类似算法套路可用于解决任务调度、依赖关系等问题，通过拓扑排序确定任务执行顺序或依赖关系。

### 推荐题目
- P1137 旅行计划
- P3243 [HNOI2015]菜肴制作
- P4017 最大食物链计数

### 个人心得摘录与总结
- **Christopher_Yan**：最初写了假拓扑WA成10分，后来深入理解拓扑本质，发现按拓扑排序染色无向边可解决问题。总结为对算法理解要深入，不能凭直觉写代码。 

---
处理用时：25.11秒