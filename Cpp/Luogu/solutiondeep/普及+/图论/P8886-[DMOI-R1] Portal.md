# 题目信息

# [DMOI-R1] Portal

## 题目背景

出题人正在玩一款叫 Portal 的游戏。但由于他太菜了，于是找来了你，让你帮他过几个他过不去的关卡。

什么？你说你不会玩？

玩家需要通过传送门枪到达出口。利用传送门枪射击可开出两种门，分别是橙色门和蓝色门，两面都可作入口及出口。在创造门的时候，另一道同样颜色的门会消失，即是说同时间不可能存在两道同色的门，最多只可同时存在一道蓝色及一道橙色的门。

两道传送门在三维空间之中的两个地点创造出视觉上及物理上的连系，传送门的立点只限于平面，玩家从门出来时会自动配合地心吸力调整身体水平。

出题人把所有希望都寄托于你身上了哟。哦，对了，因为出题人是个白嫖党，因此他拥有的是盗版 Portal。

## 题目描述

在一个 $n \times n$ 的二维平面图上，用 $(x,y)$ 表示地图第 $x$ 行第 $y$ 列。每个点都是墙、虚空和地面中的一种，分别用 `#`，`*`，`.` 表示。玩家只能站在地面上。**地图之外都是墙。**

你手里有一个传送门枪，可以发射蓝色和橙色的传送门，只能朝上下左右四个方向使用。

在选定一个方向和颜色后，将会在该方向上第一个碰到的墙的墙面上建造选定颜色的传送门，并摧毁之前建造的这种颜色的传送门。两种颜色的传送门不能被建立在同一墙面。

玩家可以朝上下左右四个方向的空地移动。玩家还可以在不同色传送门之间穿梭。假如玩家朝一堵墙移动并且墙面上有传送门，并且当前已经建立了两个传送门，那么会从另一个传送门出来（必须保证出来也站在陆地上）。

出来的时候，玩家会站在另一个门外的空地上，**四个方向都可以。**

一开始玩家站在 $(1,1)$，目的地是 $(n,n)$。求最少使用多少次传送门枪才能到达目的地。

**注意哦，这里的使用指的是穿过多少面传送门。**

## 说明/提示

### 样例1解释

我们用白色格子表示空地，黑色格子表示墙，蓝色格子表示蓝色传送门，橙色格子表示橙色传送门，可以画出第一局的如下地图：

![](https://cdn.luogu.com.cn/upload/image_hosting/s16tq3vq.png)

走到橙色传送门处，从橙色传送门进入，蓝色传送门出即可。

而第二局地图如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/v7q0izdk.png)


走到蓝色传送门处，从蓝色传送门进入，橙色传送门出即可。

### 数据范围

对于 $20\%$ 的数据，$n \le 10$。

对于 $60\%$ 的数据，$n \le 100$。

对于另外 $10\%$ 的数据，$T=1$ 且不存在虚空。

对于 $100\%$ 的数据，$2 \le n \le 500$，$1 \le T \le 10$。

## 样例 #1

### 输入

```
2
5
..###
#.#.#
#..##
...#.
.###.
5
..#..
##..#
#.#..
..#..
.#...```

### 输出

```
2
2```

## 样例 #2

### 输入

```
4
5
...*.
*##*.
#..*.
#*###
.....
5
.#*..
.**.#
###.*
***.*
**...
5
.**..
***.#
###.*
***.*
*****
5
.**..
***.#
###..
***.*
***..```

### 输出

```
4
2
```

## 样例 #3

### 输入

```
见下发文件portal1.in```

### 输出

```
见下发文件portal1.ans```

## 样例 #4

### 输入

```
见下发文件portal2.in```

### 输出

```
见下发文件portal2.ans```

# AI分析结果

### 综合分析与结论
这两道题解都围绕如何计算在二维地图中使用传送门枪从起点到终点的最少使用次数展开。andychen_2012 的题解将连通的空地视为连通块，构建有向图求最短路径；SteveHans 的题解把地图中的格子抽象成点，通过建图和双端队列广搜求最短路。

### 所选题解
- **andychen_2012（5星）**
    - **关键亮点**：思路清晰，详细分析了各种连通块之间的可达情况，代码实现严谨，对部分分和正解都有提及。
    - **个人心得**：出题人 std 挂掉，漏考虑一次判断，新造数据卡不掉错误的 std，写题解时才发现手造数据使原 std 挂掉，经过多次对拍仍卡不掉错误，只好把原 std 贴出希望被 hack。
- **SteveHans（4星）**
    - **关键亮点**：对题意解释详细，给出了多个重要推论，使用双端队列广搜优化了求最短路的过程。

### 重点代码及核心思想
#### andychen_2012
```cpp
inline void bfs(){
    // 标记连通块
    int cnt=0;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            if(s[i][j]=='.'&&!col[i][j]){
                head=1,tail=0;
                ++cnt;
                q[++tail]=(node{i,j});
                while(head<=tail){
                    node h=q[head++];
                    int x=h.x,y=h.y;
                    col[x][y]=cnt;
                    for(int i=0;i<4;++i){
                        int tx=x+dx[i],ty=y+dy[i];
                        if(s[tx][ty]!='.') continue;
                        if(!col[tx][ty]){
                            col[tx][ty]=cnt;
                            q[++tail]=(node{tx,ty});
                        }
                    }
                }
            }
        }
    }
    // 处理每个连通块周围的墙
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            if(col[i][j]){
                int g=col[i][j];
                if(s[i-1][j]=='#'){
                    if(only[g][0]==-1){
                        only[g][0]=i-1;
                        only[g][1]=j;
                    }
                    else
                        only[g][0]=only[g][1]=-2;
                }
                // 其他方向同理
            }
        }
    }
    // 构建有向图
    for(int i=0;i<=n+1;++i){
        for(int j=0;j<=n+1;++j){
            if(s[i][j]=='#'){
                for(int k=1;k<=4;++k) cango[k]=-1;
                bool nowflag=0;
                if(i<n&&col[i+1][j]) cango[1]=col[i+1][j],nowflag=1;
                // 其他方向同理
                if(!nowflag) continue;
                // 四个方向扩展找可达连通块建边
                for(int k=j-1;k>=1&&s[i][k]!='#';--k){
                    int c=col[i][k];
                    if(c){
                        for(int l=1;l<=4;++l){
                            if(cango[l]==-1) continue;
                            if(c==cango[l]) continue;
                            if(mps[mp(c,cango[l])]&&mps[mp(cango[l],c)]) continue;
                            if(only[c][0]==-1) continue;
                            if(k==j-1){
                                if(only[cango[l]][0]==-2){
                                    if(!mps[mp(cango[l],c)]){
                                        mps[mp(cango[l],c)]=1;
                                        add(cango[l],c);
                                    }
                                }
                                continue;
                            }
                            if(only[c][0]==i&&only[c][1]==j) continue;
                            if(mps[mp(c,cango[l])]) continue;
                            mps[mp(c,cango[l])]=1;
                            add(c,cango[l]);
                        }
                    }
                }
                // 其他方向同理
            }
        }
    }
    // Dijkstra 求最短路径
    dis[1]=0;
    for(int i=2;i<=cnt;++i) dis[i]=INF;
    priority_queue<pair<int,int> > q2;
    q2.push(mp(0,1));
    while(!q2.empty()){
        int u=q2.top().second;
        q2.pop();
        for(int i=hd[u];i;i=e[i].nxt){
            int v=e[i].to;
            if(dis[v]>dis[u]+1){
                dis[v]=dis[u]+1;
                q2.push(mp(-dis[v],v));
            }
        }
    }
    // 清空数据
    mps.clear();
    for(int i=1;i<=ecnt;++i) e[i]=edge{0,0};
    ecnt=0;
    for(int i=1;i<=cnt;++i) hd[i]=0;
    cnt=0;
}
```
**核心思想**：先通过 BFS 标记连通块，再处理每个连通块周围的墙，然后根据墙的位置和连通块的可达情况构建有向图，最后使用 Dijkstra 算法求起点所在连通块到终点所在连通块的最短路径。

#### SteveHans
```cpp
void build() //建立模型
{
    // 枚举每个空地
    for (int i = 1; i <= n; i ++)
        for (int j = 1; j <= n; j ++)
            if (s[i][j] == '.')
            {
                for (int u = 0; u < 4; u ++)
                {
                    int x = i + dx[u], y = j + dy[u];
                    if (!x || x > n ||!y || y > n)
                    {
                        add(g[x][y], g[i][j], 1);
                    }
                    int a = g[i][j], b = g[x][y]; 
                    if (s[x][y] == '.') add(a, b, 0);
                    else if (s[x][y] == '#') add(b, a, 1); 
                }
                // 枚举此点第一个碰到的墙，建立边
                int t = j + 1;
                while (t <= n && s[i][t]!= '#') t ++;
                add(g[i][j], g[i][t], 1);
                t = j - 1;
                while (t > 0 && s[i][t]!= '#') t --;
                add(g[i][j], g[i][t], 1);
                t = i + 1;
                while (t <= n && s[t][j]!= '#') t ++;
                add(g[i][j], g[t][j], 1); 
                t = i - 1;
                while (t > 0 && s[t][j]!= '#') t --;
                add(g[i][j], g[t][j], 1); 
            }
}

int bfs() //双端队列广搜求最短路
{
    memset(d, 0x3f, sizeof d);
    memset(st, 0, sizeof st);
    d[g[1][1]] = 0;

    deque<int> q;
    q.push_back(g[1][1]);

    while (q.size())
    {
        int t = q.front(); q.pop_front();
        
        if (st[t]) continue;
        st[t] = true;

        if (t == g[n][n]) return d[t];

        for (int i = h[t]; i; i = ne[i])
        {
            int j = e[i];
            if (d[j] > d[t] + w[i])
            {
                d[j] = d[t] + w[i];
                if (w[i]) q.push_back(j);
                else q.push_front(j);
            }
        }
    }

    return -1;
}
```
**核心思想**：`build` 函数将地图中的格子抽象成点，根据空地与空地、墙与空地的关系建图，边权根据情况设为 0 或 1。`bfs` 函数使用双端队列广搜求从起点到终点的最短路径。

### 最优关键思路或技巧
- **连通块抽象**：将连通的空地视为连通块，简化问题，减少不必要的计算。
- **建图思想**：把问题抽象成图论问题，通过构建有向图，利用图的算法求解最短路径。
- **双端队列广搜**：在边权只有 0 和 1 的情况下，使用双端队列广搜可以优化求最短路的过程。

### 可拓展之处
同类型题可能会增加地图的维度、传送门的规则或其他限制条件，类似算法套路可以是继续使用图论算法，根据新的规则调整建图方式和求解过程。

### 洛谷相似题目推荐
- P1144 最短路计数
- P1629 邮递员送信
- P3371 单源最短路径（弱化版）

---
处理用时：58.15秒