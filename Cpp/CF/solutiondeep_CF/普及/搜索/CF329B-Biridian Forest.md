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
# 森林中的竞争

## 题目描述

你发现自己身处一片森林中，需要找到出口逃离。森林中还有其他人和许多树木，他们会给你带来阻碍。

所有人都会沿着通往终点的最短路径行进。

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

### 题解综合分析

本题的核心是通过广度优先搜索（BFS）来计算每个点到终点的最短距离，并统计在主角到达终点前能够到达终点的人数。所有题解都采用了从终点开始进行BFS的策略，这样可以有效地减少搜索范围并提高效率。

### 精选题解

#### 题解1：作者：hswfwkj_ (赞：25)
- **星级**：4.5
- **关键亮点**：详细解释了从终点开始BFS的优势，代码注释清晰，逻辑严谨。
- **个人心得**：强调了从终点开始搜索的重要性，并提供了详细的代码注释，帮助读者理解每一步的实现。

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
- **星级**：4
- **关键亮点**：使用了`vis`数组来标记已访问的点，提高了搜索效率，代码结构清晰。
- **个人心得**：强调了使用`vis`数组的重要性，并提供了读入字符的函数，使代码更加模块化。

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
- **星级**：4
- **关键亮点**：简洁明了地解释了BFS的实现，代码结构清晰，逻辑严谨。
- **个人心得**：强调了从终点开始搜索的优势，并提供了详细的代码注释，帮助读者理解每一步的实现。

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

### 最优关键思路或技巧
1. **从终点开始BFS**：这样可以减少搜索范围，提高效率。
2. **使用`vis`数组标记已访问的点**：避免重复访问，提高搜索效率。
3. **初始化距离为无穷大**：防止误判，确保统计的准确性。

### 可拓展之处
- **类似题目**：可以考虑扩展到多维地图或动态障碍物的情况。
- **算法优化**：可以考虑使用双向BFS或A*算法进一步优化搜索效率。

### 推荐题目
1. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)
2. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)
3. [P1131 [ZJOI2007] 时态同步](https://www.luogu.com.cn/problem/P1131)

---
处理用时：45.51秒