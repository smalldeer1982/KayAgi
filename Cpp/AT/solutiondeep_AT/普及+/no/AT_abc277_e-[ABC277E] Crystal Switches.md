# 题目信息

# [ABC277E] Crystal Switches

## 题目描述

【题面翻译】

给定一张 $n$ 个点 $m$ 条边的无向图。每条边有一个权值 $w \in \{0, 1\}$。$w = 0$ 表示这条边无法通过，$w = 1$ 则可以通过。

有 $k$ 个点上面有按钮 $s_i$。

你现在位于 $1$ 号点。每次，你可以做两件事情中的一件：

1. 移动。移到相邻的一个点上，注意这条边一定是可以通行的。
2. 按开关。此时，全部路的边权取反。即：$w = 0$ 变成 $1$，$w = 1$ 变成 $0$。

请问你是否能够到达 $n$ 号点。如果可以，求出最少移动次数。

translated by @[liangbowen](https://www.luogu.com.cn/user/367488).

## 说明/提示

$2 \le n \le 2 \times 10^5$

$1 \le m \le 2 \times 10^5$

$1 \le k \le n$

保证 $1 \le u_i, v_i \le n$，且 $u_i \ne v_i$。

保证 $1 \le s_1 < s_2 < \cdots < s_k \le n$。

## 样例 #1

### 输入

```
5 5 2

1 3 0

2 3 1

5 4 1

2 1 1

1 4 0

3 4```

### 输出

```
5```

## 样例 #2

### 输入

```
4 4 2

4 3 0

1 2 1

1 2 0

2 1 1

2 4```

### 输出

```
-1```

# AI分析结果

### 题目内容
给定一张 $n$ 个点 $m$ 条边的无向图。每条边有一个权值 $w \in \{0, 1\}$。$w = 0$ 表示这条边无法通过，$w = 1$ 则可以通过。

有 $k$ 个点上面有按钮 $s_i$。

你现在位于 $1$ 号点。每次，你可以做两件事情中的一件：

1. 移动。移到相邻的一个点上，注意这条边一定是可以通行的。
2. 按开关。此时，全部路的边权取反。即：$w = 0$ 变成 $1$，$w = 1$ 变成 $0$。

请问你是否能够到达 $n$ 号点。如果可以，求出最少移动次数。

### 算法分类
最短路、分层图

### 题解分析与结论
本题的核心在于如何处理边权的动态变化。通过分层图的思想，将图分为两层：第一层表示边权未取反的状态，第二层表示边权取反后的状态。通过按钮所在的点连接这两层图，从而将问题转化为在分层图中求最短路的问题。

### 所选高星题解
#### 题解1：liangbowen (5星)
**关键亮点**：
- 使用分层图的思想，将图分为两层，分别表示边权未取反和取反后的状态。
- 通过按钮所在的点连接两层图，边权为0，表示切换状态不需要代价。
- 使用Dijkstra算法求解最短路，代码简洁清晰。

**核心代码**：
```cpp
void solve()
{
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    while (m--)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        if (w == 1) ADD(u, v, 1); //第一层
        else ADD(u + n, v + n, 1); //第二层
    }
    while (k--)
    {
        int u;
        scanf("%d", &u);
        ADD(u, u + n, 0); //切换层
    }
    dijkstra(1);
    int t = min(dis[n], dis[n + n]);
    if (t == 0x3f3f3f3f) puts("-1");
    else cout << t << '\n';
}
```

#### 题解2：Y2y7m (4星)
**关键亮点**：
- 使用BFS进行搜索，通过二维vis数组记录每个点的两种状态（边权未取反和取反后的状态）。
- 通过按钮所在的点切换状态，确保不会遗漏任何可能的路径。

**核心代码**：
```cpp
void bfs()
{
    queue<node> q;
    q.push({1,0,0});
    vis[1][0]=1;
    if(s[1])
    {
        q.push({1,0,1});
        vis[1][1]=1;
    }
    while(!q.empty())
    {
        node t=q.front();
        int u=t.u,stat=t.stat;
        q.pop();
        for(int i=0;i<edge[u].size();i++)
        {
            int v=edge[u][i],w=val[u][i];
            int tmp=w^stat;
            if(tmp==0) continue;
            if(vis[v][stat]) continue;
            vis[v][stat]=1;
            if(v==n)
            {
                cout<<t.step+1<<endl;
                exit(0);
            }
            q.push({v,t.step+1,stat});
            if(s[v])
            {
                q.push({v,t.step+1,!stat});
            }
        }
    }
    cout<<-1<<endl;
    return ;
}
```

#### 题解3：MoyunAllgorithm (4星)
**关键亮点**：
- 使用BFS进行搜索，通过二维vis数组记录每个点的两种状态。
- 通过按钮所在的点切换状态，确保不会遗漏任何可能的路径。

**核心代码**：
```cpp
void bfs()
{
    queue<Point>q;
    q.push({1,0,1});
    while(q.size())
    {
        Point p=q.front();
        q.pop();
        int u=p.id,step=p.step,dir=p.opt;
        if(u==N)
        {
            printf("%d\n",step);
            exit(0);
        }
        if(vis[u][dir]) continue;
        vis[u][dir]=1;
        for(auto cur:gra[u])
        {
            int v=cur.first,a=cur.second;
            if(a!=dir) continue;
            if(vis[v][dir]) continue;
            q.push({v,step+1,dir});
        }
        if(swi[u])
        dir=1-dir;
        for(auto cur:gra[u])
        {
            int v=cur.first,a=cur.second;
            if(a!=dir) continue;
            if(vis[v][dir]) continue;
            q.push({v,step+1,dir});
        }
    }
    puts("-1");
    exit(0);
}
```

### 最优关键思路
分层图的思想是解决本题的关键。通过将图分为两层，分别表示边权未取反和取反后的状态，并通过按钮所在的点连接这两层图，从而将问题转化为在分层图中求最短路的问题。这种方法不仅简化了问题的复杂性，还能确保不会遗漏任何可能的路径。

### 拓展思路
类似的分层图思想可以应用于其他动态变化的图论问题，如边权随时间变化、节点状态变化等。通过分层图，可以将动态问题转化为静态问题，从而利用经典算法（如Dijkstra、BFS）进行求解。

### 推荐题目
1. [P4568 [JLOI2011] 飞行路线](https://www.luogu.com.cn/problem/P4568)
2. [P5122 [USACO18DEC]Fine Dining G](https://www.luogu.com.cn/problem/P5122)
3. [P1073 [NOIP2009 提高组] 最优贸易](https://www.luogu.com.cn/problem/P1073)

---
处理用时：40.01秒