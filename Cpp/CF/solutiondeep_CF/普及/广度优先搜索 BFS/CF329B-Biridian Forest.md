# 题目信息

# Biridian Forest

## 题目描述

你发现你身处一片森林，你需要找到出口逃离这里。但是在森林中还有其他人和很多树木。他们会给你造成阻碍。

所有人都会沿向终点的最短路径行进。

## 样例 #1

### 输入

```
5 7
000E0T3
T0TT0T0
010T0T0
2T0T0T0
0T0S000
```

### 输出

```
3
```

## 样例 #2

### 输入

```
1 4
SE23
```

### 输出

```
2
```

# AI分析结果

### 题目内容重写
你发现你身处一片森林，你需要找到出口逃离这里。但是在森林中还有其他人和很多树木。他们会给你造成阻碍。

所有人都会沿向终点的最短路径行进。

### 样例 #1

#### 输入

```
5 7
000E0T3
T0TT0T0
010T0T0
2T0T0T0
0T0S000
```

#### 输出

```
3
```

### 样例 #2

#### 输入

```
1 4
SE23
```

#### 输出

```
2
```

### 题解分析与结论

#### 综合分析
本题的核心算法是广度优先搜索（BFS），所有题解都采用了从终点出发的BFS策略，记录每个点到终点的最短距离，然后统计那些距离小于等于起点到终点距离的点上的人数。这种策略大大减少了搜索的复杂度，避免了从每个点出发进行BFS的高时间复杂度。

#### 最优关键思路
1. **从终点出发的BFS**：从终点开始进行BFS，记录每个点到终点的最短距离，这样可以一次性计算出所有点到终点的距离，避免了多次BFS的冗余计算。
2. **剪枝优化**：在BFS过程中，一旦搜索到起点，记录下起点到终点的距离，后续搜索中可以直接跳过那些距离大于该值的点，进一步优化了搜索效率。
3. **距离初始化**：将所有点的距离初始化为无穷大，避免误判那些无法到达终点的点。

#### 可拓展之处
- **类似问题**：可以扩展到其他需要计算最短路径的问题，如迷宫问题、网格图的最短路径问题等。
- **算法套路**：从终点出发的BFS策略可以广泛应用于需要计算多个点到某个特定点的最短路径的问题。

### 推荐题目
1. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)
2. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)
3. [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141)

### 所选高分题解

#### 题解1：作者：hswfwkj_ (赞：25)
**星级：5星**
**关键亮点**：
- 从终点出发的BFS策略，详细解释了如何记录每个点到终点的距离。
- 代码注释详细，易于理解。
- 优化了搜索效率，避免了不必要的计算。

**核心代码**：
```cpp
void Bfs(int X,int Y){
    int head=0,tail=1,rx,ry,i;
    int dx[5]={0,0,0,1,-1};
    int dy[5]={0,1,-1,0,0};
    q[1].x=X;
    q[1].y=Y;
    q[1].step=0;
    q[1].sum=a[X][Y];
    while(head<tail){
        head++;
        for(i=1;i<=4;i++){
            rx=q[head].x+dx[i];
            ry=q[head].y+dy[i];
            if(a[rx][ry]<10&&a[rx][ry]>=0&&rx<=n&&rx>=1&&ry<=m&&ry>=1){
                tail++;
                q[tail].step=q[head].step+1;
                q[tail].sum=a[rx][ry];
                a[rx][ry]=10;
                q[tail].x=rx;
                q[tail].y=ry;
                if(q[tail].x==xx&&q[tail].y==yy)
                k=q[tail].step;
            }
        }
    }
}
```

#### 题解2：作者：Asphy7xia (赞：3)
**星级：4星**
**关键亮点**：
- 使用了`vis`数组标记已访问的点，提升了搜索效率。
- 详细解释了如何通过`len`变量进行剪枝优化。

**核心代码**：
```cpp
while (! q.empty ())
{
    node tmp = q.front ();
    q.pop ();
    int x = tmp.x, y = tmp.y;
    if (map[x][y] == -2)  len = tmp.step;
    if (tmp.step <= len && map[x][y] != -2)  ans += map[x][y];
    if (tmp.step >= len)  continue;
    for (int i = 1; i <= 4; i++)
    {
        int nx = x + fx[i], ny = y + fy[i];
        if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && map[nx][ny] != -1 && ! vis[nx][ny])
        {
            q.push ((node) {nx, ny, tmp.step + 1});
            vis[nx][ny] = true; 
        }
    }
}
```

#### 题解3：作者：Terraria (赞：1)
**星级：4星**
**关键亮点**：
- 详细解释了BFS的剪枝策略，如何通过`maxn`变量进行优化。
- 代码结构清晰，易于理解。

**核心代码**：
```cpp
while(!q.empty()){
    infor now=q.front();
    q.pop();
    int x=now.x,y=now.y,dis=now.dis;
    if(dis>maxn||vis[x][y]) continue;
    vis[x][y]=true;
    if(mp[x][y]=='S'){
        maxn=dis;
        continue;
    }
    if(mp[x][y]>='0'&&mp[x][y]<='9') ans=ans+(mp[x][y]-'0');
    for(int i=1;i<=4;i++){
        int xx=x+dx[i];
        int yy=y+dy[i];
        if(xx<1||xx>n||yy<1||yy>m||mp[xx][yy]=='T'||vis[xx][yy]) continue;
        infor to;
        to.x=xx,to.y=yy,to.dis=dis+1;
        q.push(to);
    }
}
```

### 个人心得总结
- **调试经历**：在BFS过程中，初始化距离为无穷大非常重要，避免误判无法到达终点的点。
- **踩坑教训**：从终点出发的BFS策略可以大大减少计算量，避免从每个点出发进行BFS的高时间复杂度。
- **顿悟感想**：BFS的剪枝优化是提升算法效率的关键，合理利用剪枝可以显著减少不必要的计算。

---
处理用时：57.91秒