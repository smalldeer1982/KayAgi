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

### 综合分析与结论

本题的核心是通过BFS（广度优先搜索）找到从起点到终点的最短路径，难点在于处理传送门的强制传送机制。传送门的存在使得路径搜索变得复杂，因为进入传送门后必须立即传送到对应的位置，且传送不消耗时间。大多数题解通过BFS的基本框架，结合对传送门的特殊处理，成功解决了问题。

#### 关键思路与技巧：
1. **BFS框架**：大多数题解使用BFS进行最短路径搜索，BFS天然适合解决最短路径问题，因为它按层遍历，首次到达终点的路径即为最短路径。
2. **传送门处理**：传送门的处理是本题的核心难点。常见的处理方式是在BFS中遇到传送门时，直接跳转到对应的传送门位置，并将该位置加入队列继续搜索。
3. **标记与优化**：为了避免重复访问，大多数题解使用`vis`数组标记已访问的点。对于传送门，部分题解选择不标记传送门，因为传送门可能需要多次访问。
4. **双向BFS**：部分题解提到双向BFS，从起点和终点同时进行搜索，能够有效减少搜索空间，提升效率。

#### 通用建议与扩展思路：
- **传送门处理**：传送门的处理可以抽象为“跳跃点”，在BFS中遇到跳跃点时，直接跳转到目标位置。这种思路可以推广到其他类似的跳跃或传送机制问题。
- **双向BFS**：在路径搜索问题中，双向BFS是一种常见的优化手段，尤其适用于起点和终点明确且路径较长的情况。
- **标记策略**：对于需要多次访问的点（如传送门），标记策略需要灵活调整，避免过早标记导致路径无法继续搜索。

### 精选题解

#### 题解1：作者：lxzy_ (赞：191)
- **星级**：★★★★★
- **关键亮点**：
  - 使用BFS框架，清晰易懂。
  - 对传送门的处理非常简洁，通过`goto_another`函数直接跳转到对应传送门位置。
  - 代码结构清晰，注释详细，适合初学者学习。
- **个人心得**：作者提到“传送门需要特判一下，并注意不要重复计算路径”，强调了传送门处理的难点。

```cpp
void goto_another(int &nx,int &ny,int k) {
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=m;j++) {
            if(a[i][j]==a[nx][ny]&&(i!=nx||j!=ny)) {
                nx=i; ny=j; return;
            }
        }
    }
}
```

#### 题解2：作者：lzxhdxx (赞：87)
- **星级**：★★★★☆
- **关键亮点**：
  - 使用双向BFS进行优化，减少搜索空间。
  - 详细讨论了传送门的多次使用问题，并提出了解决方案。
  - 代码结构清晰，注释详细，适合有一定基础的读者。
- **个人心得**：作者提到“双向广搜必须分清传送器用了一次还是两次”，强调了传送门处理的复杂性。

```cpp
int expand(int sub) {
    int nowx = Q[sub].front().first, nowy = Q[sub].front().second; Q[sub].pop();
    for(int i=1;i<=4;i++) {
        int newx = nowx + dx[i], newy = nowy + dy[i];
        if(newx>=1&&newy>=1&&newx<=n&&newy<=m&&c[newx][newy]!='#'&&!vis[sub][newx][newy]) {
            if(c[newx][newy]>='A'&&c[newx][newy]<='Z') {
                int x = newx, y = newy;
                vis[sub][newx][newy] = 1, cnt[sub][newx][newy] = cnt[sub][nowx][nowy] + 1;
                handle(newx, newy);
            }
            else vis[sub][newx][newy] = 1;
            Q[sub].push(make_pair(newx, newy)), cnt[sub][newx][newy] = cnt[sub][nowx][nowy] + 1;
            if(vis[1-sub][newx][newy]) {
                if(c[newx][newy]>='A'&&c[newx][newy]<='Z') {
                    if(vis[1-sub][newx][newy]==2||vis[sub][newx][newy]==2)
                        return cnt[1-sub][newx][newy] + cnt[sub][newx][newy];
                }
                else return cnt[1-sub][newx][newy] + cnt[sub][newx][newy];
            }
        }
    }
    return 0;
}
```

#### 题解3：作者：ThinkofBlank (赞：11)
- **星级**：★★★★☆
- **关键亮点**：
  - 提出了三种不同的解法，包括BFS、双向BFS和最短路算法（SPFA、Dijkstra）。
  - 详细分析了每种解法的优缺点，适合进阶学习。
  - 代码实现较为复杂，但思路清晰，适合有一定算法基础的读者。
- **个人心得**：作者提到“本题存在0、1两种边权，怎么搞呢？”，强调了传送门带来的边权变化问题。

```cpp
void dijkstra(int X) {
    memset(dis,0x3f3f,sizeof(dis));
    dis[X][0]=0;
    s.push(make_pair(0,make_pair(X,0)));
    while(!s.empty()) {
        int x=s.top().second.first;
        int y=s.top().second.second;
        s.pop();
        if(vis[x][y]) continue;
        vis[x][y]=1;
        if(!y) {
            for(int i=las[x];i;i=t[i].next) {
                int v=t[i].v,w=t[i].w,T=ys[v];
                if(dis[v][T]>dis[x][y]+w) {
                    dis[v][T]=dis[x][y]+w;
                    s.push(make_pair(-dis[v][T],make_pair(v,T)));
                }
            }
        } else {
            for(int i=las[x];i;i=t[i].next) {
                if(t[i].w) continue;
                int v=t[i].v;
                if(dis[v][0]>dis[x][1]) {
                    dis[v][0]=dis[x][1];
                    s.push(make_pair(-dis[v][0],make_pair(v,0)));
                }
            }
        }
    }
}
```

### 推荐题目
1. **P1443 马的遍历**：经典的BFS问题，适合练习BFS的基本应用。
2. **P1746 离开中山路**：类似于本题的BFS问题，适合进一步巩固BFS的应用。
3. **P1825 玉米田迷宫**：与本题类似，涉及传送门机制的BFS问题，适合深入学习。

---
处理用时：69.01秒