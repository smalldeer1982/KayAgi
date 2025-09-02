# 题目信息

# [USACO09NOV] Job Hunt S

## 题目描述

Bessie is running out of money and is searching for jobs. Farmer John knows this and wants the cows to travel around so he has imposed a rule that his cows can only make D (1 <= D <= 1,000) dollars in a city before they must work in another city. Bessie can, however, return to a city after working elsewhere for a while and again earn the D dollars maximum in that city. There is no limit on the number of times Bessie can do this.

Bessie's world comprises P (1 <= P <= 150) one-way paths connecting C (2 <= C <= 220) cities conveniently numbered 1..C. Bessie is currently in city S (1 <= S <= C). Path i runs one-way from city A\_i to city B\_i (1 <= A\_i <= C; 1 <= B\_i <= C) and costs nothing to traverse.

To help Bessie, Farmer John will give her access to his private jet service. This service features F (1 <= F <= 350) routes, each of which is a one way flight from one city J\_i to a another K\_i (1 <= J\_i <= C; 1 <= K\_i <= C) and which costs T\_i (1 <= T\_i <= 50,000) dollars. Bessie can pay for the tickets from future earnings if she doesn't have the cash on hand.

Bessie can opt to retire whenever and wherever she wants. Given an unlimited amount of time, what is the most money that Bessie can make presuming she can make the full D dollars in each city she can travel to?  Print -1 if there is no limit to this amount.

奶牛们正在找工作。农场主约翰知道后，鼓励奶牛们四处碰碰运气。而且他还加了一条要求：一头牛在一个城市最多只能赚D（1≤D≤1000）美元，然后它必须到另一座城市工作。当然，它可以在别处工作一阵子后又回到原来的城市再最多赚D美元。而且这样的往返次数没有限制。

城市间有P（1≤P≤150）条单向路径连接，共有C（2≤C≤220）座城市，编号从1到C。奶牛贝茜当前处在城市S（1≤S≤C）。路径i从城市A\_i到城市B\_i（1≤A\_i≤C，1≤B\_i≤C），在路径上行走不用任何花费。

为了帮助贝茜，约翰让它使用他的私人飞机服务。这项服务有F条（1≤F≤350）单向航线，每条航线是从城市J\_i飞到另一座城市K\_i（1≤J\_i≤C，1≤K\_i≤C），费用是T\_i（1≤T\_i≤50000）美元。如果贝茜手中没有现钱，可以用以后赚的钱来付机票钱。

贝茜可以选择在任何时候，在任何城市退休。如果在工作时间上不做限制，贝茜总共可以赚多少钱呢？如果赚的钱也不会出现限制，就输出-1。


## 说明/提示

This world has five cities, three paths and two jet routes. Bessie starts out in city 1, and she can only make 100 dollars in each city before moving on.


Bessie can travel from city 1 to city 5 to city 2 to city 3, and make a total of 4\*100 - 150 = 250 dollars.


Source: USACO 2009 November Silver

这个世界上有五个城市，三条单向路径和两条单向航线。贝茜从一号城市开始她的旅行，她在离开一个城市前最多只能在这个城市赚100美元。


贝茜可以通过从一号城市-->五号城市-->二号城市-->三号城市的旅行赚到4\*100-150=250美元。


(注:在四个城市各赚100美元,从五号城市飞到二号城市花掉150美元)


来源:USACO 2009 十一月银组


## 样例 #1

### 输入

```
100 3 5 2 1
1 5
2 3
1 4
5 2 150
2 5 120
```

### 输出

```
250```

# AI分析结果

### 综合分析与结论
这些题解的核心思路均是将点权转化为边权，把问题转化为求最长路问题，同时要判断图中是否存在正环（存在正环则输出 -1）。不同题解在求最长路的算法选择上有所不同，主要涉及 SPFA、Bellman - Ford、Floyd 等算法，还有使用 DFS 求解的。

### 所选题解
- **作者：Believe_R_（5星）**
    - **关键亮点**：思路清晰，详细阐述了将点权转边权的方法以及求最长路的两种常见做法，代码注释丰富，还给出了相关模板题和双倍经验题的提示。
    - **个人心得**：无
- **作者：TOM_闫（4星）**
    - **关键亮点**：提出将边权取反转化为最短路问题，选择 Bellman - Ford 算法求解，代码简洁，对算法优化有一定体现。
    - **个人心得**：无
- **作者：Dawn_Sdy（4星）**
    - **关键亮点**：思路明确，详细说明了如何处理点权和边权，对图中存在正环的判断方法解释清晰，代码有卡常处理。
    - **个人心得**：提到 SPFA 时间复杂度为 O(玄学)所以需要卡常。

### 重点代码
#### Believe_R_ 的核心代码
```cpp
void Spfa()
{
    q.push(s);
    w[s]=d; vis[s]=1; cnt[s]++;
    while(!q.empty())
    {
        int u=q.top(); q.pop();
        vis[u]=0;
        if(++cnt[u]>n) {printf("-1\n"); exit(0);}  
        for(int i=head[u];i;i=nex[i])
        {
            int v=to[i];
            if(w[v]<w[u]+dis[i])
            {
                w[v]=w[u]+dis[i];
                if(!vis[v])
                {
                    q.push(v);
                    vis[v]=1;
                }
            }
        }
    }
}
```
**核心实现思想**：使用 SPFA 算法求最长路，通过队列不断更新节点的最长路距离，同时记录节点入队次数，若入队次数大于节点数则说明存在正环，输出 -1。

#### TOM_闫的核心代码
```cpp
for(i=1;i<c;i++)
{
    pd=false;
    for(j=1;j<=p+f;j++)
        if(dis[mapp[j].v]>dis[mapp[j].u]+mapp[j].w)
        {
            pd=true;
            dis[mapp[j].v]=dis[mapp[j].u]+mapp[j].w;
        }
    if(pd==false) break;
}
//判负环
pd=false;
for(j=1;j<=p+f;j++)
        if(dis[mapp[j].v]>dis[mapp[j].u]+mapp[j].w)
        {
            pd=true;
            dis[mapp[j].v]=dis[mapp[j].u]+mapp[j].w;
        }
if(pd==true) 
{
    printf("-1\n");
    return 0;
}
```
**核心实现思想**：使用 Bellman - Ford 算法求最短路（边权取反），通过多次松弛操作更新节点的最短路距离，最后判断是否存在负环（原问题的正环），若存在则输出 -1。

#### Dawn_Sdy 的核心代码
```cpp
inline void SPFA()//SPFA
{
    for (register int i=1;i<=n;i++)
        dist[i]=-INF;
    std::queue <int> q;
    dist[s]=d;
    vst[s]=1;
    tot[s]=1;
    q.push(s);
    while (!q.empty())
    {
        int x=q.front();
        q.pop();
        vst[x]=0;
        for (register int i=head[x];i;i=edge[i].next)
        {
            int y=edge[i].v;
            int z=edge[i].w;
            if (dist[y]<dist[x]+z)
            {
                tot[y]++;
                if (tot[y]>=n)//判断图中有没有正环
                {
                    printf("-1");
                    err=1;
                    return ;
                }
                dist[y]=dist[x]+z;
                if (!vst[y])
                {
                    vst[y]=1;
                    q.push(y);
                }
            }
        }
    }
}
```
**核心实现思想**：使用 SPFA 算法求最长路，同样记录节点入队次数，若入队次数大于等于节点数则说明存在正环，输出 -1。

### 最优关键思路或技巧
- **点权转边权**：将每个城市的赚钱数（点权）转化为边权，普通边权设为 $D$，飞行边权设为 $D - T$，方便使用图论算法求解。
- **正环判断**：在求最长路过程中，记录每个节点的入队次数，若入队次数大于节点数，则说明图中存在正环，可无限赚钱，输出 -1。

### 可拓展之处
同类型题或类似算法套路：
- 涉及点权和边权混合的图论问题，可考虑将点权转化为边权，再使用常见的图论算法求解。
- 求最长路问题可使用 SPFA、Bellman - Ford 等算法，注意判断正环的情况。

### 推荐题目
- [P1807 最长路_NOI导刊2010提高（07）](https://www.luogu.org/problem/P1807)
- [P2648 赚钱](https://www.luogu.org/problemnew/show/P2648)
- [P1938 [USACO09NOV]找工就业Job Hunt](https://www.luogu.org/problemnew/show/P1938)

### 个人心得总结
- Dawn_Sdy 提到 SPFA 时间复杂度为 O(玄学)所以需要卡常，在实际使用中可通过减少不必要的头文件、使用寄存器变量等方式进行优化。
- 孑思提到第一天学差分约束 WA 了三遍，失去信心，说明学习新算法需要不断实践和总结，遇到问题不要轻易放弃。

---
处理用时：40.87秒