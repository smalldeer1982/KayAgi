# 题目信息

# [USACO11OPEN] Corn Maze S

## 题目描述

This past fall, Farmer John took the cows to visit a corn maze. But this wasn't just any corn maze: it featured several gravity-powered teleporter slides, which cause cows to teleport instantly from one point in the maze to another. The slides work in both directions: a cow can slide from the slide's start to the end instantly, or from the end to the start. If a cow steps on a space that hosts either end of a slide, she must use the slide.

The outside of the corn maze is entirely corn except for a single exit.

The maze can be represented by an N x M (2 <= N <= 300; 2 <= M <= 300) grid. Each grid element contains one of these items:

\* Corn (corn grid elements are impassable) 

\* Grass (easy to pass through!) 

\* A slide endpoint (which will transport a cow to the other endpoint) 

\* The exit

A cow can only move from one space to the next if they are adjacent and neither contains corn. Each grassy space has four potential neighbors to which a cow can travel. It takes 1 unit of time to move from a grassy space to an adjacent space; it takes 0 units of time to move from one slide endpoint to the other.

Corn-filled spaces are denoted with an octothorpe (#). Grassy spaces are denoted with a period (.). Pairs of slide endpoints are denoted with the same uppercase letter (A-Z), and no two different slides have endpoints denoted with the same letter. The exit is denoted with the equals sign (=).

Bessie got lost. She knows where she is on the grid, and marked her current grassy space with the 'at' symbol (@). What is the minimum time she needs to move to the exit space?


## 说明/提示

例如以下矩阵，$N=5,M=6$。

```plain
###=##
#.W.##
#.####
#.@W##
######
```

唯一的一个装置的结点用大写字母 $\tt{W}$ 表示。

最优方案为：先向右走到装置的结点，花费一个单位时间，再到装置的另一个结点上，花费 $0$ 个单位时间，然后再向右走一个，再向上走一个，到达出口处，总共花费了 $3$ 个单位时间。

## 样例 #1

### 输入

```
5 6
###=##
#.W.##
#.####
#.@W##
######
```

### 输出

```
3```

# AI分析结果

这道题主要是在一个包含传送门的玉米迷宫中，求从起点到终点的最短时间，核心思路多围绕广度优先搜索（BFS）及最短路算法展开，不同题解在处理传送门等难点上各有特点。

1. **思路对比**
    - **BFS类**：多数题解采用BFS。基本思路是从起点开始，将可到达的点放入队列逐步搜索。遇到传送门时，需找到另一传送门端点并处理，确保能正确更新路径与步数。如lxzy_的题解，直接用BFS，定义结构体存储坐标与步数，通过队列遍历，遇到传送门时用函数找到另一传送门端点并加入队列。
    - **双向BFS**：lzxhdxx采用双向BFS，从起点和终点同时搜索，每次扩展状态少的队列，相遇时得最优解。此方法需注意传送门的特殊处理，如标记传送门使用次数，避免在传送门处相遇时误判。
    - **最短路算法类**：yuzhechuan将二维矩阵压成一维，用SPFA算法求解。先预处理各点连接关系，传送门按不同情况处理，如单个传送门当普通草地，成对传送门连边时终点设为另一门地址，最后跑SPFA求最短路。ThinkofBlank提出用01 - BFS、将传送门与相邻格连边转化为普通BFS或用最短路算法（如dijkstra结合拆点思想）等方法。
2. **难点处理对比**
    - **传送门处理**：是主要难点。多数题解通过记录传送门位置，遇到传送门时找到对应端点。如maorui_cow用函数判断匹配传送门；lzxhdxx在双向BFS中标记传送门使用次数，避免错误相遇判断。部分题解还考虑传送门可能是中转站、需多次经过等情况。
    - **判重处理**：不同题解采用不同方式。如lxzy_用`vis`数组标记已访问点防止重复访问；lzxhdxx在双向BFS中对传送门和普通点分别标记，处理传送门多次使用及相遇判断问题。
3. **题解评分**
    - **lxzy_**：★★★★ 思路清晰，代码简洁，详细解释BFS思路与实现，对传送门处理有清晰函数，便于理解，适合初学者。
```cpp
struct point{//定义一个名为point的结构体
    int x;//当前可到达点的x坐标
    int y;//当前可到达点的y坐标
    int t;//到达当前点的最小步数
};
queue<point> que;
//...
void goto_another(int &nx,int &ny,int k){//goto_another函数用于寻找另一个传送门，nx、ny代表当前点的坐标，记得要加上取地址符'&'，因为每当贝西踏入一个传送门，它就会立即被传送至另一个传送门，不能在原地停留
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a[i][j]==a[nx][ny]&&(i!=nx||j!=ny)){
                nx=i;
                ny=j;
                return ;
            }
        }
    }
}
//...
while(!que.empty()){
    point f=que.front();
    que.pop();
    if(a[f.x][f.y]=='='){
        cout<<f.t;
        return 0;
    }
    if(a[f.x][f.y]>='A'&&a[f.x][f.y]<='Z'){
        goto_another(f.x,f.y,f.t);
    }
    for(int i=0;i<=3;i++){
        int nx=f.x+dx[i];
        int ny=f.y+dy[i];
        if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&a[nx][ny]!='#'&&!vis[nx][ny]){
            vis[nx][ny]=true;
            que.push((point){nx,ny,f.t+1});
        }
    }
}
```
    - **lzxhdxx**：★★★★ 提出双向BFS新思路，详细分析题目坑点及解决方法，代码结构清晰，对双向BFS各部分有详细讲解。
```cpp
int expand(int sub){
    int nowx = Q[sub].front().first, nowy = Q[sub].front().second; Q[sub].pop();
    for (int i = 1; i <= 4; i++){
        int newx = nowx + dx[i], newy = nowy + dy[i];
        if (newx >= 1 && newy >= 1 && newx <= n && newy <= m && c[newx][newy]!= '#' &&!vis[sub][newx][newy]){
            if (c[newx][newy] >= 'A' && c[newx][newy] <= 'Z'){
                int x = newx, y = newy; 
                vis[sub][newx][newy] = 1;
                cnt[sub][newx][newy] = cnt[sub][nowx][nowy] + 1; 
                handle(newx, newy);
            }
            else vis[sub][newx][newy] = 1;
            Q[sub].push(make_pair(newx, newy));
            cnt[sub][newx][newy] = cnt[sub][nowx][nowy] + 1;
            if (vis[1 - sub][newx][newy]){
                if (c[newx][newy] >= 'A' && c[newx][newy] <= 'Z'){
                    if (vis[1 - sub][newx][newy] == 2 || vis[sub][newx][newy] == 2)
                        return cnt[1 - sub][newx][newy] + cnt[sub][newx][newy];
                }
                else return cnt[1 - sub][newx][newy] + cnt[sub][newx][newy];
            }
        }
    }
    return 0;
}
```
    - **ThinkofBlank**：★★★★ 提供多种思路，包括01 - BFS、转化为普通BFS及最短路算法结合拆点思想，对每种思路分析详细，有一定拓展性。
```cpp
// Method 3代码片段
struct node{
    int v,w,nex;
}t[M<<1];
struct strom{//传送阵 
    int x[3],y[3],e;
}p[26];
bool ys[M];
int las[M],len;
int dis[M][2];
bool vis[M][2];
priority_queue<pair<int,pair<int,int> > >s;
//...
for(int i=1;i<=n;++i){
    for(int j=1;j<=m;++j){
        if(a[i][j-1]=='#'){
            continue;
        }
        if(a[i][j-1]=='@'){
            S=(i-1)*m+j;
        }
        if(a[i][j-1]=='='){
            E=(i-1)*m+j;
        }
        if(a[i][j-1]>='A'&&a[i][j-1]<='Z'){//建立传送阵 
            ys[(i-1)*m+j]=1;
            int v=a[i][j-1]-'A';
            int now=++p[v].e;
            p[v].x[now]=i,p[v].y[now]=j;
        }
        for(int k=0;k<4;++k){
            int xx=i+dx[k],yy=j+dy[k];
            if(xx>0&&xx<=n&&yy>0&&yy<=m&&a[xx][yy-1]!='#'){//四周连边 
                add((i-1)*m+j,(xx-1)*m+yy,1);
            }
        }
    }
}
for(int i=0;i<26;++i){
    if(p[i].e){
        add((p[i].x[1]-1)*m+p[i].y[1],(p[i].x[2]-1)*m+p[i].y[2]);
        add((p[i].x[2]-1)*m+p[i].y[2],(p[i].x[1]-1)*m+p[i].y[1]);
    }
}
dijkstra(S);
printf("%d",dis[E][0]);
```

4. **最优关键思路技巧**
    - **BFS基础上优化**：如双向BFS，从两端同时搜索，减少搜索空间，提高效率，但实现时需注意传送门等特殊情况处理。
    - **图论转化**：将二维迷宫转化为图结构，利用最短路算法求解，通过合理处理传送门连边，将问题转化为标准最短路问题。
5. **拓展思路**
此类题属于带特殊条件的迷宫最短路问题。相似套路有：在其他迷宫问题中加入特殊地形（如陷阱、加速带等），处理方式类似，需针对特殊地形特点调整搜索或最短路算法。还可拓展到三维迷宫等。
6. **相似知识点题目**
    - **P1443 马的遍历**：基础BFS题目，可巩固BFS实现与理解。
    - **P3371 【模板】单源最短路径（弱化版）**：练习最短路算法，如Dijkstra、SPFA等。
    - **P1330 封锁阳光大学**：结合图论与BFS，判断二分图，与本题处理图结构有相似之处。
7. **个人心得摘录总结**
    - **lxzy_**：感觉题目除传送门特判及避免重复路径外难度不大，定位为普及组T2难度。
    - **lzxhdxx**：普通BFS会TLE，采用双向BFS。分享题目坑点，如传送器使用规则、传送器可能多次使用及特殊情况处理，强调双向BFS中传送器相遇判断条件。
    - **maorui_cow**：认为题目简单，普通搜索即可解决。 

---
处理用时：200.93秒