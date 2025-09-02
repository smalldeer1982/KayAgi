# 题目信息

# [USACO09JAN] Laserphones S

## 题目描述

The cows have a new laser-based system so they can have casual conversations while out in the pasture which is modeled as a W x H grid of points (1 <= W <= 100; 1 <= H <= 100).

The system requires a sort of line-of-sight connectivity in order to sustain communication. The pasture, of course, has rocks and trees that disrupt the communication but the cows have purchased diagonal mirrors ('/' and '\' below) that deflect the laser beam through a 90 degree turn. Below is a map that illustrates the

problem.

H is 8 and W is 7 for this map.  The two communicating cows are notated as 'C's; rocks and other blocking elements are notated as '\*'s:

```plain
7 . . . . . . .         7 . . . . . . . 
6 . . . . . . C         6 . . . . . /-C 
5 . . . . . . *         5 . . . . . | * 
4 * * * * * . *         4 * * * * * | * 
3 . . . . * . .         3 . . . . * | . 
2 . . . . * . .         2 . . . . * | . 
1 . C . . * . .         1 . C . . * | . 
0 . . . . . . .         0 . \-------/ . 
0 1 2 3 4 5 6           0 1 2 3 4 5 6 
```
Determine the minimum number of mirrors M that must be installed to maintain laser communication between the two cows, a feat which is always possible in the given test data.


## 样例 #1

### 输入

```
7 8 
....... 
......C 
......* 
*****.* 
....*.. 
....*.. 
.C..*.. 
....... 
```

### 输出

```
3 
```

# AI分析结果

### 综合分析与结论
本题的核心是在给定地图中，求从一个奶牛位置到另一个奶牛位置所需的最少镜子数量，本质是求最少转弯次数。各题解主要围绕广度优先搜索（BFS）、深度优先搜索（DFS）以及最短路算法展开。

- **BFS类**：通过队列不断扩展节点，记录镜子数量，部分使用双端队列优化，利用标记数组避免重复搜索。
- **DFS类**：通过递归搜索所有可能路径，使用记忆化数组剪枝，避免重复计算。
- **最短路类**：构建分层图，将问题转化为最短路问题，使用Dijkstra算法求解。

### 所选题解
- **作者：IRipple (赞：24)，4星**
  - **关键亮点**：思路清晰，通过模拟扩展过程，结合BFS和DFS实现，代码注释详细，易于理解。
  - **核心代码**：
```cpp
struct node{
    int x,y;
    int num;
}s,t;
queue<node> q;
void dfs(int fx,node u){ 
    int x=u.x,y=u.y,p=u.num; 
    if(a[x][y]<p || a[x][y]==inf) return;
    if(x<1 || y<1 || x>n || y>m) return;
    if(fx==1){
        a[x][y]=p;
        q.push((node){x,y,p});
        dfs(1,(node){x-1,y,p});
    }
    // 其他方向类似
}
void bfs(){
    while(!q.empty()){
        node u=q.front(),v=q.front();
        q.pop();
        u.num++;
        v=u; v.x=u.x-1; dfs(1,v);
        // 其他方向类似
    }
}
```
  - **核心思想**：使用BFS扩展队首点的四个方向，每次扩展使用DFS进行染色，标记每个点所需的镜子数量。

- **作者：Delva (赞：20)，4星**
  - **关键亮点**：采用分层图的思想，将问题转化为最短路问题，使用Dijkstra算法求解，思路新颖。
  - **核心代码**：
```cpp
#define pNum (n*m*4)
#define point_ID(t,i,j) ((t-1)*n*m+(i-1)*m+j)
struct Edge{
    int next,to,w;
    Edge(){}
    Edge(int a,int b,int c){next=a,to=b,w=c;}
    bool operator <(const Edge &e)const{return w>e.w;}
}edge[maxp<<2];
void addEdge(int u,int v,int w){
    edge[++cnt]=Edge(head[u],v,w);
    head[u]=cnt;
}
int dj(int s){
    for(int i=1;i<=pNum;++i)dis[i]=inf;dis[s]=0;
    priority_queue<Edge> que;
    que.push(Edge(0,s,dis[s]));
    while(!que.empty()){
        Edge fe = que.top();que.pop();
        if(dis[fe.to]!=fe.w)continue;
        for(int i=head[fe.to];i;i=edge[i].next) {
            Edge ne = edge[i];
            if(dis[ne.to]>dis[fe.to]+ne.w){
                dis[ne.to]=dis[fe.to]+ne.w;
                que.push(Edge(0,ne.to,dis[ne.to]));
            }
        }
    }
}
```
  - **核心思想**：建立4层相同的图，层内建权值为0的边，层间建权值为1的边，从每一层的起点到每一层的终点跑最短路，统计最小花费。

- **作者：学而思李老师 (赞：6)，4星**
  - **关键亮点**：使用双端队列BFS，通过记录上一步方向判断是否需要增加镜子，优化搜索过程。
  - **核心代码**：
```cpp
struct Node
{
    int x, y, t, last;
};
deque<Node> d;
const int dx[] = {0, -1, 0, 0, 1};
const int dy[] = {0, 0, -1, 1, 0};
while(!d.empty())
{
    Node tmp = d.front();
    d.pop_front();
    if(tmp.x == ex && tmp.y == ey)
    {
        cout << tmp.t << endl;
        return 0;
    }
    for(int i = 1; i <= 4; i ++)
    {
        int xx = tmp.x + dx[i], yy = tmp.y + dy[i];
        if(xx <= 0 || xx > n || yy <= 0 || yy > m) continue;
        if(tmp.last == 0 || i == tmp.last)
        {
            if(vis[xx][yy] >= tmp.t && a[xx][yy] != 1)
            {
                vis[xx][yy] = tmp.t;
                d.push_front(Node{xx, yy, tmp.t, i});
            }
        }
        else
        {
            if(vis[xx][yy] >= tmp.t + 1 && a[xx][yy] != 1) 
            {
                vis[xx][yy] = tmp.t + 1;
                d.push_back(Node{xx, yy, tmp.t + 1, i});
            }
        }
    }
}
```
  - **核心思想**：使用双端队列BFS，不需要改变方向的状态push到队首，需要改变方向的状态push到队尾，通过vis数组记录最优解。

### 最优关键思路或技巧
- **分层图**：将问题转化为图论问题，通过构建分层图，将转弯操作转化为图中的边，利用最短路算法求解。
- **记忆化搜索**：在DFS中使用记忆化数组记录每个状态的最优解，避免重复计算，提高效率。
- **双端队列BFS**：根据状态的优劣，将不需要改变方向的状态push到队首，需要改变方向的状态push到队尾，优化搜索过程。

### 可拓展之处
同类型题通常涉及在地图中寻找最短路径、最少操作次数等问题，可使用BFS、DFS、最短路算法等解决。类似算法套路包括：
- 标记数组：使用标记数组记录节点的访问状态、最优解等，避免重复搜索。
- 方向数组：使用方向数组方便枚举节点的上下左右四个方向。
- 剪枝优化：在搜索过程中，根据问题的特点进行剪枝，减少不必要的搜索。

### 推荐题目
- [P1126 机器人搬重物](https://www.luogu.org/problemnew/show/P1126)：涉及在地图中移动，求最少转弯次数。
- [P1649 迷宫](https://www.luogu.org/problemnew/show/P1649)：在迷宫中寻找最短路径，可能需要转弯。
- [P1849 玉米田](https://www.luogu.com.cn/problem/P1849)：与本题类似，可使用双端队列BFS求解。

### 个人心得摘录与总结
- **Zekrom**：一开始尝试用双端队列做最短路，结果发现由于激光的方向性，单调性不成立，不能直接使用双端队列求最短路，最终将vis数组扩展到3维，使用普通队列BFS求解。总结：在使用算法时，要充分考虑问题的特点，确保算法的适用性。

---
处理用时：46.83秒