# 题目信息

# Directing Edges

## 题目描述

You are given a graph consisting of $ n $ vertices and $ m $ edges. It is not guaranteed that the given graph is connected. Some edges are already directed and you can't change their direction. Other edges are undirected and you have to choose some direction for all these edges.

You have to direct undirected edges in such a way that the resulting graph is directed and acyclic (i.e. the graph with all edges directed and having no directed cycles). Note that you have to direct all undirected edges.

You have to answer $ t $ independent test cases.

## 说明/提示

Explanation of the second test case of the example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1385E/d35669c68d98d1dcefc83e24fe388de76c760c1f.png)

Explanation of the third test case of the example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1385E/641ca4dc132da9f3a738d8606128481e262df751.png)

## 样例 #1

### 输入

```
4
3 1
0 1 3
5 5
0 2 1
1 1 5
1 5 4
0 5 2
1 3 5
4 5
1 1 2
0 4 3
1 3 1
0 2 3
1 2 4
4 5
1 4 1
1 1 3
0 1 2
1 2 4
1 3 2```

### 输出

```
YES
3 1
YES
2 1
1 5
5 4
2 5
3 5
YES
1 2
3 4
3 1
3 2
2 4
NO```

# AI分析结果

### 题目翻译
## 给边定向

### 题目描述
给定一个由 $n$ 个顶点和 $m$ 条边组成的图。给定的图不一定是连通的。有些边已经有了方向，你不能改变它们的方向。其他边是无向边，你必须为所有这些无向边选择一个方向。

你必须以这样的方式给无向边定向，使得得到的图是有向无环图（即所有边都有方向且没有有向环的图）。注意，你必须给所有无向边定向。

你需要回答 $t$ 个独立的测试用例。

### 说明/提示
示例中第二个测试用例的解释：

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1385E/d35669c68d98d1dcefc83e24fe388de76c760c1f.png)

示例中第三个测试用例的解释：

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1385E/641ca4dc132da9f3a738d8606128481e262df751.png)

### 样例 #1
#### 输入
```
4
3 1
0 1 3
5 5
0 2 1
1 1 5
1 5 4
0 5 2
1 3 5
4 5
1 1 2
0 4 3
1 3 1
0 2 3
1 2 4
4 5
1 4 1
1 1 3
0 1 2
1 2 4
1 3 2
```
#### 输出
```
YES
3 1
YES
2 1
1 5
5 4
2 5
3 5
YES
1 2
3 4
3 1
3 2
2 4
NO
```

### 算法分类
图论

### 综合分析与结论
这些题解的核心思路都是先判断由有向边构成的图是否存在环，若存在环则无解，输出 `NO`；若不存在环，则对有向边进行拓扑排序，记录每个点的拓扑序，然后将无向边按照拓扑序小的点指向拓扑序大的点的规则进行定向，最后输出定向后的图。

不同题解的主要区别在于代码实现的细节，如存图方式（链式前向星、邻接表等）、拓扑排序的具体实现（BFS 或 DFS）等，但整体思路是一致的。

### 所选题解
- **作者：MY（一名蒟蒻） (赞：55)，4星**
    - **关键亮点**：思路清晰，代码注释详细，易于理解。
    - **核心实现思想**：使用链式前向星存图，通过 `top_sort` 函数进行拓扑排序，判断是否存在环，若不存在环则按规则输出定向后的边。
```cpp
bool top_sort()//核心
{
    int u,sum=0;
    for(int i=1;i<=n;i++) if(!du[i]) que.push(i);
    while(!que.empty())
    {
        u=que.front(); que.pop();
        top[u]=++sum;//注意这里的拓扑序
        for(int i=fir[u];i;i=e[i].nex)
        {
            du[e[i].to]--;
            if(!du[e[i].to]) que.push(e[i].to);
        }
    }
    if(sum != n) return false;
    return true;//如果可以拓扑每个点一定都入队了一次
}
```
- **作者：iMya_nlgau (赞：12)，4星**
    - **关键亮点**：使用邻接表存图，代码结构清晰，逻辑明确。
    - **核心实现思想**：通过 `toposort` 函数进行拓扑排序，若存在环则输出 `NO`，否则按规则输出定向后的边。
```cpp
inline bool toposort(int n){
    queue<int> q;
    for(rgi i=1;i<=n;i++)
        if(deg[i]==0) q.push(i);
    while(!q.empty()){
        int x=q.front(); q.pop();
        topo[x]=++tot;
        for(rgi i=head[x];i;i=e[i].nxt){
            int y=e[i].to;
            if(--deg[y]==0) q.push(y);
        }
    }
    if(tot<n) return false;
    return true;
}
```
- **作者：_lyx111 (赞：4)，4星**
    - **关键亮点**：思路完整，代码规范，对算法流程有详细的总结。
    - **核心实现思想**：使用链式前向星存图，通过 `toposort` 函数进行拓扑排序，判断是否存在环，若不存在环则按规则输出定向后的边。
```cpp
bool toposort() //寻找合法的拓扑序 
{
    for(int i=1;i<=n;i++)
        if(!deg[i]) que.push(i); //将入度为 0 的点入队 
    while(!que.empty()) //队列不为空 
    {
        int u=que.front(); que.pop(); //取队首 
        id++; t[u]=id; //记录 u 在合法拓扑序中的位置 
        for(int i=hea[u];i;i=edg[i].nxt) //将 u 能到达的所有点的入度减一 
        {
            int v=edg[i].to;
            deg[v]--;
            if(!deg[v]) que.push(v);
        }
    }
    if(id==n) return 1; //存在合法的拓扑序 
    else return 0; //无解 
}
```

### 关键思路或技巧
- **拓扑排序的应用**：通过拓扑排序判断有向图是否存在环，并记录每个点的拓扑序，为无向边的定向提供依据。
- **无向边定向规则**：将无向边按照拓扑序小的点指向拓扑序大的点的规则进行定向，可保证图中不存在环。

### 拓展思路
同类型题或类似算法套路：
- 其他关于图的定向问题，如给定一些边的方向限制，要求构造满足条件的有向图。
- 拓扑排序的其他应用，如任务调度、课程安排等问题。

### 推荐题目
- [P1113 杂务](https://www.luogu.com.cn/problem/P1113)
- [P1347 排序](https://www.luogu.com.cn/problem/P1347)
- [P2746 [USACO5.3]校园网Network of Schools](https://www.luogu.com.cn/problem/P2746)

### 个人心得摘录与总结
- **KellyFrog**：最初想通过选出一个没有出度的点，将跟这个点有关的边都指向它来解决问题，但出度不好维护，后来考虑建图，只建方向确定的边的反向边，然后进行拓扑排序。总结：在解决问题时，当一种思路实现起来有困难，可以尝试换一种思路，从不同的角度思考问题。
- **chenxia25**：顺序做到这题时想了 DFS、Tarjan 缩点都没有思路，最后才想到拓扑排序。总结：在解决图论问题时，拓扑排序是一种常用的方法，当其他方法行不通时，可以考虑使用拓扑排序。 

---
处理用时：55.47秒