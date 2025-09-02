# 题目信息

# [USACO12MAR] Tractor S

## 题目描述

经过一天漫长的工作，农场主 John 完全忘记了他的拖拉机还在场地中央。他的奶牛们总喜欢和他搞些恶作剧，它们在场地的不同位置丢下 $n$ 堆干草。这样 John 就必须先移走一些干草堆才能将拖拉机开走。

拖拉机和干草堆都可以看作是二维平面上的点，它们的坐标都是整数，没有哪堆干草的坐标和拖拉机的初始坐标一致。John 驾驶拖拉机只能沿着坐标轴的方向移动若干单位长度，比如说，他可以先朝北移动 $2$ 个单位长度，再向东移动 $3$ 个单位长度等等。拖拉机不能移动到干草堆所占据的点。

请你帮助 John 计算一下，最少要移动多少堆干草才能将拖拉机开回坐标原点。

## 说明/提示

对于 $100\%$ 的数据，保证 $1 \leq n \leq 5 \times 10^4$，$1 \leq x_i, y_i \leq 10^3$。

## 样例 #1

### 输入

```
7 6 3 
6 2 
5 2 
4 3 
2 1 
7 3 
5 4 
6 4 ```

### 输出

```
1 ```

# AI分析结果

• 综合分析与结论：
    - 这些题解主要围绕如何找到从拖拉机初始位置到原点最少移除干草堆数量的问题，多数采用搜索算法。
    - 思路上，有的从起始点广搜，有的从原点反搜，有的通过特殊数据结构优化搜索。
    - 算法要点包括方向数组定义移动方向，用数组标记干草堆位置、访问状态等。
    - 解决难点在于如何在保证正确性的同时优化搜索，避免重复搜索，提高效率。
    - 综合质量来看，以下3条题解相对较好：
  - 作者：一只书虫仔 (赞：13)
    - 星级：4星
    - 关键亮点：采用01 bfs，借助deque数据结构，将边权为0（无干草堆）的节点push到队首，边权为1（有干草堆）的节点push到队尾，保证答案单调性，每个点只需访问一次，复杂度低。
    - 个人心得：教练提供思路和代码进行研究学习。
    - 核心代码：
```cpp
const int stx[4] = {0, 1, 0, -1};
const int sty[4] = {1, 0, -1, 0};
//...
while (!q.empty()) {
    Node cur = q.front();
    q.pop_front();
    for (int k = 0; k < 4; k++) {
        Node nxt;
        nxt.x = cur.x + stx[k], nxt.y = cur.y + sty[k];
        if (nxt.x < 0 || nxt.x >= MAXM) continue;
        if (nxt.y < 0 || nxt.y >= MAXM) continue;
        if (step[nxt.x][nxt.y]!= -1) continue;
        if (map[nxt.x][nxt.y]) {
            step[nxt.x][nxt.y] = step[cur.x][cur.y] + 1;
            q.push_back(nxt);
        }
        else {
            step[nxt.x][nxt.y] = step[cur.x][cur.y];
            q.push_front(nxt);
        }
    }
}
```
核心实现思想：每次从队列取出当前节点，向四个方向拓展新节点，根据新节点是否为干草堆决定加入队首或队尾，同时更新到达该点的步数。
  - 作者：_Atyou (赞：11)
    - 星级：4星
    - 关键亮点：双端队列BFS，与01 bfs思路类似，走四个方向，遇到草堆的压到队尾，没遇到草堆的压到队头，保证队列中节点答案单调性，每个点只访问一次，复杂度为O（1000^2）。
    - 核心代码：
```cpp
const int dx[]={1, -1, 0, 0}, dy[]={0, 0, -1, 1};
//...
while (q.size()) {
    int x=q.front().first, y=q.front().second; q.pop_front();
    if (x == 0 && y == 0) { 
        write(f[x][y]);  
        return 0;
    }
    for (register int i=0; i<4; i++) {
        int x0=x+dx[i], y0=y+dy[i];
        if (x0 < 0 || x0 > 1001 || y0 < 0 || y0 > 1001) continue; 
        if (v[x0][y0]) continue; 
        v[x0][y0]=1;
        f[x0][y0]=f[x][y]+a[x0][y0]; 
        if (a[x0][y0]) q.push_back(make_pair(x0, y0)); 
        else q.push_front(make_pair(x0, y0)); 
    }
}
```
核心实现思想：从队列取出当前节点，判断是否到达原点，否则向四个方向拓展新节点，根据新节点是否为干草堆决定加入队首或队尾，并更新到达该点的答案。
  - 作者：soy_un_perro (赞：9)
    - 星级：4星
    - 关键亮点：优先队列广搜，建立以移动的干草数为第一关键字的小根堆，利用贪心思想，当取出堆顶坐标为(0, 0)时即为最优解。
    - 核心代码：
```cpp
priority_queue <pair<int,pair<int,int> > > q; 
//...
q.push(make_pair(0,make_pair(-sx,-sy)));
v[sx][sy]=1;
while(!q.empty())
{
    x=-q.top().second.first;
    y=-q.top().second.second;
    step=-q.top().first;
    q.pop();
    if (x==0 && y==0)
        return step;
    for(int i=0;i<4;i++)
    {
        if (x+dx[i]>=0 && x+dx[i]<=1050 
        && y+dy[i]>=0 && y+dy[i]<=1050 
        &&!v[x+dx[i]][y+dy[i]])
        {
            if (m[x+dx[i]][y+dy[i]])
                q.push(make_pair(-step-1,make_pair(-x-dx[i],-y-dy[i])));
            else
                q.push(make_pair(-step,make_pair(-x-dx[i],-y-dy[i])));
            v[x+dx[i]][y+dy[i]]=1;
        }
    }
}
```
核心实现思想：将起始点加入优先队列，每次从队列取出堆顶元素，判断是否到达原点，否则向四个方向拓展新节点，根据新节点是否为干草堆调整堆中元素的优先级，并标记新节点已访问。
• 最优关键思路或技巧：利用双端队列或优先队列优化BFS，通过合理安排节点入队顺序，保证答案单调性，减少重复搜索，提高算法效率。
• 可拓展之处：此类题属于图论中求最短路问题，当边权只有0和1时，01 bfs或双端队列BFS是很好的解决方法；对于一般边权，可考虑Dijkstra、SPFA等算法。类似套路如在网格图中求从起点到终点的最少代价等问题。
• 推荐题目：
    - P3371 【模板】单源最短路径（弱化版）
    - P1339 热浪
    - P4779 【模板】单源最短路径（标准版）
• 个人心得摘录与总结：
    - 一只书虫仔：通过研究教练给的思路和代码学习01 bfs，认识到01 bfs适用于边权0或1的最短路问题。总结出该技巧在tg组较实用。 

---
处理用时：44.26秒