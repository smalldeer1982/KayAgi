# 题目信息

# [USACO07OCT] Obstacle Course S

## 题目描述

Consider an N x N (1 <= N <= 100) square field composed of 1

by 1 tiles. Some of these tiles are impassible by cows and are marked with an 'x' in this 5 by 5 field that is challenging to navigate:

```cpp
. . B x . 
. x x A . 
. . . x . 
. x . . . 
. . x . . 
```
Bessie finds herself in one such field at location A and wants to move to location B in order to lick the salt block there.  Slow, lumbering creatures like cows do not like to turn and, of course, may only move parallel to the edges of the square field. For a given field, determine the minimum number of ninety degree turns in any path from A to B. The path may begin and end with Bessie facing in any direction. Bessie knows she can get to the salt lick.



## 说明/提示

只可以上下左右四个方向行走，并且不能走出这些格子之外。开始和结束时的方向可以任意。

### 数据范围及约定

对于全部数据，保证 $2\le N\le 100$。


## 样例 #1

### 输入

```
3
. x A
. . .
B x .```

### 输出

```
2```

# AI分析结果

### 综合分析与结论

这些题解主要围绕如何通过BFS或DFS求解从起点到终点的最小转弯次数。难点在于如何记录和更新转弯次数，避免重复计算，并优化搜索效率。大多数题解采用了BFS，部分使用了DFS或DFS+记忆化搜索。BFS的优势在于可以保证第一次到达终点时的转弯次数是最小的，而DFS则需要通过剪枝和记忆化来优化。

### 所选高分题解

#### 1. 作者：GNAQ (赞：36)
- **星级**：5星
- **关键亮点**：使用了BFS+方向扩展的思路，通过记录每个点的转弯次数，确保每次扩展时转弯次数最小。代码结构清晰，优化了搜索效率。
- **个人心得**：通过BFS的特性，确保第一次到达终点时的转弯次数是最小的，避免了DFS的重复搜索问题。

```cpp
void bfs()
{
    memset(vis, false, sizeof(vis));
    memset(dist, 0x3f, sizeof(dist));
    priority_queue<qNode>que;

    while (!que.empty()) {
        que.pop();
    }
    dist[start] = 0;
    que.push(qNode(start, 0));
    qNode tmp;

    while (!que.empty()) {
        tmp = que.top();
        que.pop();
        int u = tmp.v;
        if (vis[u]) {
            continue;
        }
        vis[u] = true;
        for (int i = 0; i < E[u].size(); i++) {
            int v = E[tmp.v][i].v;
            int cost = E[u][i].cost;
            if (!vis[v] && dist[v] > dist[u] + cost) {
                dist[v] = dist[u] +cost;
                que.push(qNode(v, dist[v]));
            }
        }
    }
}
```

#### 2. 作者：白烛葵 (赞：37)
- **星级**：4.5星
- **关键亮点**：使用了洪水填充（Flood Fill）优化BFS，通过一次搜索即可得到最小转弯次数，避免了多次搜索的冗余。
- **个人心得**：通过洪水填充的方式，减少了搜索的次数，提高了效率。

```cpp
while(l<r)//开搜
{
    for(i=0;i<4;i++)//枚举坐标变量，进行4方移动
    for(k=1;;k++)//用于洪水填充的数组
    {
        int xx=hrb[l].x+k*xy[i],yy=hrb[l].y+k*yx[i];
        //枚举一个常数k，与坐标变量相乘
        if(lxy[xx][yy]==1)break;
        if(xx<=0||xx>n||yy<=0||yy>n)break;
        //碰边或走过了，停止填充
        lxy[xx][yy]=1;//打标记
        emm[xx][yy]=emm[hrb[l].x][hrb[l].y]+1;
        //停了，说明该转弯了，于是当前点的次数为原坐标的加1
        //该处不用取min，是因为洪水填充记得是拐弯次数，到目标点，拐弯次数自然是最少的
        hrb[r].x=xx;
        hrb[r].y=yy;
        r++;//进行队列
    }
    l++;
}
```

#### 3. 作者：hht2005 (赞：2)
- **星级**：4星
- **关键亮点**：使用了双端队列优化的Dijkstra算法，通过边权为0或1的特性，优化了搜索效率。
- **个人心得**：通过双端队列的特性，减少了堆优化的复杂度，提高了搜索效率。

```cpp
while(!q.empty())//dijkstra
{
    node x=q.front();
    q.pop_front();
    if(x.x==tx&&x.y==ty)//终点被取出，得到答案
    {
        printf("%d\n",v[x.x][x.y][x.f]);
        return 0;
    }
    if(b[x.x][x.y][x.f])continue;//被取出过，continue
    b[x.x][x.y][x.f]=1;
    for(int i=0;i<4;i++)//枚举四个方向
    {
        int x1=x.x+dx[i],y1=x.y+dy[i];
        if(a[x1][y1]=='.'/*越界即为空字符*/&&v[x.x][x.y][x.f]+(x.f!=i)<v[x1][y1][i])
        {
            v[x1][y1][i]=v[x.x][x.y][x.f]+(i!=x.f);
            if(i==x.f)q.push_front((node){x1,y1,i});//边权为零,从队头入队。
            else q.push_back((node){x1,y1,i});//否则，从队尾入队
        }
    }
}
```

### 最优关键思路或技巧

1. **BFS+方向扩展**：通过记录每个点的转弯次数，确保每次扩展时转弯次数最小。
2. **洪水填充**：通过一次搜索即可得到最小转弯次数，减少了搜索的次数。
3. **双端队列优化的Dijkstra**：通过边权为0或1的特性，优化了搜索效率。

### 可拓展之处

1. **类似算法套路**：可以应用于其他需要记录路径状态的最短路径问题，如最小步数、最小转弯次数等。
2. **同类型题**：可以参考洛谷的P2937（类似的最小转弯次数问题）。

### 推荐题目

1. **P2937**：类似的最小转弯次数问题。
2. **P1141**：BFS+洪水填充的经典题目。
3. **P1162**：BFS+方向扩展的应用。

### 个人心得总结

- **调试经历**：在BFS中，记录转弯次数时需要注意方向的变化，避免重复计算。
- **踩坑教训**：DFS如果不加剪枝和记忆化，容易超时。
- **顿悟感想**：通过BFS的特性，可以保证第一次到达终点时的转弯次数是最小的，避免了DFS的重复搜索问题。

---
处理用时：42.62秒