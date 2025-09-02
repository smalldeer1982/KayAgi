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
本题主要求在有障碍物的地图中，两点间激光通信所需的最少镜子数量，即最少转弯次数。各题解主要围绕广度优先搜索（BFS）、深度优先搜索（DFS）和最短路算法展开。

BFS 类题解通过队列不断扩展节点，利用标记数组避免重复搜索，部分使用双端队列优化；DFS 类题解通过递归搜索所有可能路径，使用记忆化数组剪枝；最短路类题解通过构建分层图，将问题转化为图的最短路问题。

### 所选题解
- **作者：IRipple（4星）**
    - **关键亮点**：思路清晰，通过模拟扩展过程，结合 BFS 和 DFS 实现，代码注释详细，易于理解。
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
    - **核心实现思想**：使用 BFS 扩展队首点的四个方向，每次 DFS 进行染色工作，标记每个点所需的镜子数量。

- **作者：Delva（4星）**
    - **关键亮点**：采用分层图思想，将问题转化为图的最短路问题，使用 Dijkstra 算法求解，思路新颖。
    - **核心代码**：
```cpp
const int inf = 0x7fffffff, maxn = 103, maxp = maxn*maxn*4;
const int dx[]={0,0,0,1,-1},dy[]={0,1,-1,0,0};
char M[maxn][maxn];
#define pNum (n*m*4)
#define point_ID(t,i,j) ((t-1)*n*m+(i-1)*m+j)
int n,m,head[maxp],cnt,dis[maxp],sx,sy,ex,ey;
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
    - **核心实现思想**：建立 4 层相同的图，层内建权值为 0 的边，层间建权值为 1 的边，从每一层的起点到每一层的终点跑 Dijkstra 算法求最短路。

- **作者：学而思李老师（4星）**
    - **关键亮点**：使用双端队列 BFS，通过记录上一步方向判断是否需要增加镜子，优化搜索过程。
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
    - **核心实现思想**：使用双端队列 BFS，不需要改变方向的状态 push 到队首，需要改变方向的状态 push 到队尾，通过 vis 数组记录最优解。

### 最优关键思路或技巧
- **记忆化搜索**：在 DFS 中使用三维数组记录每个点在不同方向下的最少转弯次数，避免重复搜索，如 hongzy、yangyujia18 等题解。
- **分层图最短路**：将问题转化为分层图的最短路问题，通过构建图和边，使用 Dijkstra 等算法求解，如 Delva 题解。
- **双端队列 BFS**：根据是否需要改变方向，将状态分别 push 到队首和队尾，优化搜索过程，如学而思李老师题解。

### 可拓展之处
同类型题包括求迷宫中两点间的最短路径、最少转弯次数等问题，可使用 BFS、DFS、最短路等算法解决。类似算法套路包括记忆化搜索、分层图、双端队列优化等。

### 推荐题目
- P1126 机器人搬重物
- P1649 单向双轨道
- P1849 [USACO05DEC]Scales S

### 个人心得摘录与总结
- **Zekrom**：一开始尝试用双端队列做最短路，结果因激光的方向性导致单调性不成立而失败，最终使用普通队列 BFS 并扩展 vis 数组解决问题。总结：在使用双端队列优化时，要确保问题满足单调性条件。

---
处理用时：54.63秒