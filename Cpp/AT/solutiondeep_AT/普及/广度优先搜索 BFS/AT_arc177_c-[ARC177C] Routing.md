# 题目信息

# [ARC177C] Routing

## 题目描述

有一个 $N$ 行 $N$ 列（用 $(i, j)$ 表示矩阵第 $i$ 行第 $j$ 列的元素）的矩阵被刷满了红色和蓝色。现在要矩阵的一些格子刷上紫色，使得矩阵**同时**满足以下两个条件：
- 从 $(1, 1)$ 走到 $(N, N)$，保证存在一条路径使其只经过红色和紫色；
- 从 $(1, N)$ 走到 $(N, 1)$，保证存在一条路径使其只经过蓝色和紫色

注意，**行动时他可以往任何一个方向前进。**

那么，问题来了，至少要将多少格子刷成紫色才能使以上两个条件成立呢？

## 样例 #1

### 输入

```
5

RBRBB

RBRRR

RRRBR

RBBRB

BBRBR```

### 输出

```
3```

## 样例 #2

### 输入

```
5

RBBBB

BBBBB

BBBBB

BBBBB

BBBBR```

### 输出

```
7```

## 样例 #3

### 输入

```
10

RRBBBBBBBB

BRRBBBBBBB

BBRRBBBBBB

BBBRRBBBBB

BBBBRRBBBB

BBBBBRRBBB

BBBBBBRRBB

BBBBBBBRRB

BBBBBBBBRR

BBBBBBBBBR```

### 输出

```
2```

## 样例 #4

### 输入

```
17

RBBRRBRRRRRBBBBBB

BBRBRBRRBRRBRRBBR

BRBRBBBRBBRBBRBBB

RBRRBBBBBBRRBRRRR

RRRRRBRBRRRBBRBBR

RRRRRBRRBRBBRRRBB

BBBRRRBRBRBBRRRBB

BBRRRBRBBBRBRRRBR

RRBBBBBBBBBBBRBRR

RRRBRRBRBRBRBRBBB

RRBRRRRBRBRRBRBBR

RRRBBRBRBBBRBBRBR

BBRBBRRBRRRBBRBBB

BBBRBRRRRRRRBBRBB

RRRRRBRBRBBRRBRRR

BRRRRBBBRRRBRRBBB

BBRRBBRRRBBBRBBBR```

### 输出

```
8```

# AI分析结果

### 题目重写
【题目内容】
# [ARC177C] Routing

## 题目描述

有一个 $N$ 行 $N$ 列（用 $(i, j)$ 表示矩阵第 $i$ 行第 $j$ 列的元素）的矩阵被刷满了红色和蓝色。现在要矩阵的一些格子刷上紫色，使得矩阵**同时**满足以下两个条件：
- 从 $(1, 1)$ 走到 $(N, N)$，保证存在一条路径使其只经过红色和紫色；
- 从 $(1, N)$ 走到 $(N, 1)$，保证存在一条路径使其只经过蓝色和紫色

注意，**行动时他可以往任何一个方向前进。**

那么，问题来了，至少要将多少格子刷成紫色才能使以上两个条件成立呢？

## 样例 #1

### 输入

```
5

RBRBB

RBRRR

RRRBR

RBBRB

BBRBR```

### 输出

```
3```

## 样例 #2

### 输入

```
5

RBBBB

BBBBB

BBBBB

BBBBB

BBBBR```

### 输出

```
7```

## 样例 #3

### 输入

```
10

RRBBBBBBBB

BRRBBBBBBB

BBRRBBBBBB

BBBRRBBBBB

BBBBRRBBBB

BBBBBRRBBB

BBBBBBRRBB

BBBBBBBRRB

BBBBBBBBRR

BBBBBBBBBR```

### 输出

```
2```

## 样例 #4

### 输入

```
17

RBBRRBRRRRRBBBBBB

BBRBRBRRBRRBRRBBR

BRBRBBBRBBRBBRBBB

RBRRBBBBBBRRBRRRR

RRRRRBRBRRRBBRBBR

RRRRRBRRBRBBRRRBB

BBBRRRBRBRBBRRRBB

BBRRRBRBBBRBRRRBR

RRBBBBBBBBBBBRBRR

RRRBRRBRBRBRBRBBB

RRBRRRRBRBRRBRBBR

RRRBBRBRBBBRBBRBR

BBRBBRRBRRRBBRBBB

BBBRBRRRRRRRBBRBB

RRRRRBRBRBBRRBRRR

BRRRRBBBRRRBRRBBB

BBRRBBRRRBBBRBBBR```

### 输出

```
8```

### 题解分析与结论

#### 综合分析与结论
本题的核心在于将矩阵中的格子涂成紫色，以满足两条路径的条件。通过将问题转化为图论中的最短路问题，可以有效地求解。具体来说，可以将矩阵中的每个格子视为图中的一个节点，相邻的格子之间连边，边权根据目标颜色（红色或蓝色）决定。通过两次最短路算法（如 Dijkstra 或 01BFS），分别计算从起点到终点的最小代价，最终将两次的结果相加即为答案。

#### 最优关键思路或技巧
1. **图论转化**：将矩阵中的格子转化为图中的节点，相邻格子之间连边，边权根据目标颜色决定。
2. **最短路算法**：使用 Dijkstra 或 01BFS 算法计算从起点到终点的最小代价。
3. **独立处理**：两条路径的涂色操作互不影响，可以分别计算后再相加。

#### 可拓展之处
类似的问题可以扩展到更高维度的矩阵或更复杂的路径条件，依然可以通过图论中的最短路算法解决。

#### 推荐题目
1. [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)
2. [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)
3. [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)

### 精选题解

#### 题解1：__Floze3__ (4星)
**关键亮点**：
- 使用 01BFS 算法，时间复杂度为 $O(n^2)$，效率较高。
- 思路清晰，代码简洁，易于理解。

**核心代码**：
```cpp
inline void bfs(int sx,int sy,int ex,int ey,char ch)
{
    q.push_front(aaa{sx,sy,(mp[sx][sy]!=ch)});
    dis[sx][sy]=(mp[sx][sy]!=ch);
    while(!q.empty())
    {
        aaa now=q.front();
        q.pop_front();
        if(now.x==ex&&now.y==ey)
        {
            ans+=dis[ex][ey];
            while(!q.empty()) q.pop_front();
            for(int i=1;i<=n;i++)
                for(int j=1;j<=n;j++)
                    dis[i][j]=1e9;
            return;
        }
        for(int i=0;i<4;i++)
        {
            int x=now.x+dx[i],y=now.y+dy[i];
            if(x<1||x>n||y<1||y>n) continue;
            if(dis[now.x][now.y]+(ch!=mp[x][y])<dis[x][y])
            {
                dis[x][y]=dis[now.x][now.y]+(ch!=mp[x][y]);
                if(ch!=mp[x][y])
                    q.push_back(aaa{x,y,dis[x][y]});
                else
                    q.push_front(aaa{x,y,dis[x][y]});
            }
        }
    }
}
```

#### 题解2：ma_niu_bi (4星)
**关键亮点**：
- 使用优先队列实现 Dijkstra 算法，思路清晰。
- 代码结构良好，易于调试和扩展。

**核心代码**：
```cpp
priority_queue <node> q;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++) scanf("%s", s[i] + 1);
    memset(b, 0x3f, sizeof(b));
    memset(r, 0x3f, sizeof(r));
    b[1][1] = (s[1][1] == 'B');
    q.push({1, 1, b[1][1]});
    while (!q.empty()) {
        node now = q.top(); q.pop();
        if (vis[now.x][now.y]) continue;
        vis[now.x][now.y] = 1;
        if (now.x == n && now.y == n) continue;
        for (int i = 0; i < 4; i ++) {
            int xx = now.x + xz[i], yy = now.y + yz[i];
            if (xx < 1 || xx > n || yy < 1 || yy > n) continue;
            if (b[xx][yy] > now.d + (s[xx][yy] == 'B')) {
                b[xx][yy] = now.d + (s[xx][yy] == 'B');
                q.push({xx, yy, b[xx][yy]}); 
            }
        }
    }
    memset(vis, 0, sizeof(vis));
    r[n][1] = (s[n][1] == 'R');
    q.push({n, 1, r[n][1]});
    while (!q.empty()) {
        node now = q.top(); q.pop();
        if (vis[now.x][now.y]) continue;
        vis[now.x][now.y] = 1;
        if (now.x == 1 && now.y == n) continue;
        for (int i = 0; i < 4; i ++) {
            int xx = now.x + xz[i], yy = now.y + yz[i];
            if (xx < 1 || xx > n || yy < 1 || yy > n) continue;
            if (r[xx][yy] > now.d + (s[xx][yy] == 'R')) {
                r[xx][yy] = now.d + (s[xx][yy] == 'R');
                q.push({xx, yy, r[xx][yy]}); 
            }
        }
    }
    printf("%d\n", b[n][n] + r[1][n]);
    return 0;
}
```

#### 题解3：I_will_AKIOI (4星)
**关键亮点**：
- 使用图论中的最短路算法，思路清晰。
- 代码结构良好，易于理解。

**核心代码**：
```cpp
priority_queue<Data>q;
int main()
{
  ios::sync_with_stdio(0);
  memset(d,0x3f,sizeof(d));
  cin>>n;
  for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) cin>>c[i][j];
  for(int i=1;i<=n;i++)
  {
    for(int j=1;j<=n;j++)
    {
      for(int k=0;k<4;k++)
      {
        int nx=i+fx[k],ny=j+fy[k];//往一个点的四个方向尝试连边
        if(nx<1||nx>n||ny<1||ny>n) continue;
        G[(i-1)*n+j].push_back(Data{(nx-1)*n+ny,(c[nx][ny]=='B')});
      }
    }
  }
  d[1]=0;
  q.push(Data{1,0});
  while(!q.empty())//跑红色的最短路
  {
  	w=q.top(),x=w.to;
  	q.pop();
    if(vis[x]) continue;
    vis[x]=1;
    for(int i=0;i<G[x].size();i++)
    {
      int y=G[x][i].to;
      if(d[x]+G[x][i].val<d[y])
      {
      	d[y]=d[x]+G[x][i].val;
      	if(!vis[y]) q.push(Data{y,d[y]});
	    }
	  }
  }
  ans+=d[n*n];
  memset(d,0x3f,sizeof(d));
  memset(vis,0,sizeof(vis));
  for(int i=1;i<=n*n;i++) G[i].clear(); 
  for(int i=1;i<=n;i++)
  {
    for(int j=1;j<=n;j++)
    {
      for(int k=0;k<4;k++)
      {
        int nx=i+fx[k],ny=j+fy[k];//建边
        if(nx<1||nx>n||ny<1||ny>n) continue;
        G[(i-1)*n+j].push_back(Data{(nx-1)*n+ny,(c[nx][ny]=='R')});
      }
    }
  }
  d[n]=0;
  q.push(Data{n,0});
  while(!q.empty())//跑蓝色最短路
  {
  	w=q.top(),x=w.to;
  	q.pop();
    if(vis[x]) continue;
    vis[x]=1;
    for(int i=0;i<G[x].size();i++)
    {
      int y=G[x][i].to;
      if(d[x]+G[x][i].val<d[y])
      {
      	d[y]=d[x]+G[x][i].val;
      	if(!vis[y]) q.push(Data{y,d[y]});
	    }
	  }
  }
  ans+=d[(n-1)*n+1];
  cout<<ans;
  return 0;
}
```

---
处理用时：106.79秒