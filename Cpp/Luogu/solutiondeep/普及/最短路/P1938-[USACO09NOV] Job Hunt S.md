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

本题的核心在于将点权（每个城市赚取的固定金额）转化为边权，并通过图论算法求解最长路。由于图中可能存在正环（即无限赚钱的情况），需要判断是否存在正环并输出-1。大多数题解采用了SPFA或Bellman-Ford算法来解决这个问题，部分题解还提到了使用Floyd算法或DFS进行求解。

#### 关键思路：
1. **点权转边权**：将每个城市的点权（D）转化为边权，普通路径的边权为D，飞行路径的边权为D-T（T为飞行费用）。
2. **最长路求解**：通过SPFA或Bellman-Ford算法求解最长路，注意处理负权边和正环。
3. **正环检测**：在SPFA或Bellman-Ford中，通过记录每个节点的入队次数或松弛次数来判断是否存在正环。

#### 通用建议：
- **算法选择**：SPFA和Bellman-Ford是处理负权边和正环检测的常用算法，Floyd算法虽然也能处理，但时间复杂度较高，不推荐用于大规模数据。
- **优化技巧**：在SPFA中，可以通过记录节点的入队次数来判断正环，避免无限循环。

#### 扩展思路：
- **超级源点**：如果起点不固定，可以通过引入超级源点来简化问题。
- **双倍经验**：类似题目可以通过相同的思路解决，如P2648 赚钱。

### 推荐的洛谷题目：
1. [P1807 最长路_NOI导刊2010提高（07）](https://www.luogu.org/problem/P1807)
2. [P2648 赚钱](https://www.luogu.org/problem/P2648)
3. [P1938 [USACO09NOV]找工就业Job Hunt](https://www.luogu.org/problem/P1938)

### 所选高分题解

#### 题解1：作者：Believe_R_ (赞：45)
- **星级**：★★★★★
- **关键亮点**：
  - 详细解释了如何将点权转化为边权，并说明了最长路的求解方法。
  - 提供了SPFA的实现代码，并解释了正环检测的逻辑。
  - 代码结构清晰，注释详细，易于理解。
- **个人心得**：作者强调了Dijkstra算法无法处理负权环的问题，提醒读者选择合适的算法。

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
                w[v]=w[u]+dis[i];      //我是用第一种求最长路的算法做的~qwq
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

#### 题解2：作者：TOM_闫 (赞：22)
- **星级**：★★★★☆
- **关键亮点**：
  - 提出了将边权取反后求最短路的思路，简化了最长路的求解。
  - 使用了Bellman-Ford算法，并优化了松弛过程。
  - 代码简洁，逻辑清晰。
- **个人心得**：作者提到Bellman-Ford算法虽然简单，但在数据量不大的情况下表现良好。

```cpp
for(i=1;i<c;i++)
{
    pd=false;   //加上pd可以优化bellman-ford，减少无用功
    for(j=1;j<=p+f;j++)
        if(dis[mapp[j].v]>dis[mapp[j].u]+mapp[j].w)
        {
            pd=true;
            dis[mapp[j].v]=dis[mapp[j].u]+mapp[j].w;
        }
    if(pd==false) break;
}
```

#### 题解3：作者：GLZP (赞：20)
- **星级**：★★★★☆
- **关键亮点**：
  - 通过SPFA求解最长路，并详细解释了正环检测的逻辑。
  - 代码结构清晰，注释详细，易于理解。
- **个人心得**：作者强调了SPFA的时间复杂度为O(玄学)，提醒读者注意算法的选择。

```cpp
void spfa()
{
    maxx=0;
    priority_queue< pair<int,int> > q;
    dis[s]=t;
    vis[s]=1; 
    tim[s]++;
    q.push(make_pair(t,s));
    while(q.size())
    {
        int u=q.top().second,v=1;
        q.pop();
        vis[u]=0;
        tim[u]++;
        if(tim[u]>n)
        {
            printf("-1");
            return;
        }
        for(int i=head[u];i;i=edge[i].nst)
        {
            v=edge[i].to;
            if(dis[u]+edge[i].dis>dis[v])
            {
                dis[v]=dis[u]+edge[i].dis;
                if(!vis[v])
                {
                    q.push(make_pair(-dis[v],v));
                    vis[v]=1;
                }
            }
        }
    }
}
```

### 最优关键思路总结
1. **点权转边权**：将每个城市的点权（D）转化为边权，普通路径的边权为D，飞行路径的边权为D-T（T为飞行费用）。
2. **最长路求解**：通过SPFA或Bellman-Ford算法求解最长路，注意处理负权边和正环。
3. **正环检测**：在SPFA或Bellman-Ford中，通过记录每个节点的入队次数或松弛次数来判断是否存在正环。

### 拓展与举一反三
- **超级源点**：如果起点不固定，可以通过引入超级源点来简化问题。
- **双倍经验**：类似题目可以通过相同的思路解决，如P2648 赚钱。

---
处理用时：46.12秒