# 题目信息

# [USACO2.4] 穿越栅栏 Overfencing

## 题目描述

Farmer John 在外面的田野上搭建了一个巨大的用栅栏围成的迷宫。幸运的是，他在迷宫的边界上留出了两段栅栏作为迷宫的出口。更幸运的是，他所建造的迷宫是一个“完美的”迷宫：即你能从迷宫中的任意一点找到一条走出迷宫的路。

给定迷宫的宽度 $W$（$1 \leq W \leq 38$）及高度 $H$（$1 \leq H \leq 100$）。$2 \times H+1$ 行，每行 $2 \times W+1$ 的字符以下面给出的格式表示一个迷宫。然后计算从迷宫中最“糟糕”的那一个点走出迷宫所需的步数（即使从这一点以最优的方式走向最靠近的出口，它仍然需要最多的步数）。

当然了，牛们只会水平或垂直地在 X 或 Y 轴上移动，他们从来不走对角线。每移动到一个新的方格算作一步（包括移出迷宫的那一步）。

这是一个 $W=5,H=3$ 的迷宫：

```plain
+-+-+-+-+-+
|         |
+-+ +-+ + +
|     | | |
+ +-+-+ + +
| |     |  
+-+ +-+-+-+
```
如上图的例子，栅栏的柱子只出现在奇数行或奇数列。每个迷宫只有两个出口。

## 说明/提示

翻译来自NOCOW

USACO 2.4


## 样例 #1

### 输入

```
5 3
+-+-+-+-+-+
|         |
+-+ +-+ + +
|     | | |
+ +-+-+ + +
| |     |  
+-+ +-+-+-+```

### 输出

```
9
```

# AI分析结果

### 综合分析与结论

该题目要求从迷宫中找到最“糟糕”的点，即从该点到出口的最短路径最长。题解主要集中在如何高效地处理迷宫输入、如何通过BFS或DFS计算最短路径、以及如何优化搜索过程。大多数题解采用了BFS，部分题解还提到了输入格式的处理和搜索过程中的优化技巧。

### 所选高星题解

#### 1. 作者：奔波儿霸 (4星)
**关键亮点**：
- 采用双向BFS，从两个出口分别进行搜索，记录每个点到出口的最短距离。
- 详细说明了输入格式的处理和搜索过程中的优化技巧。
- 代码结构清晰，注释详细，易于理解。

**个人心得**：
- 作者提到调试了2小时，主要问题在于输入格式的处理和搜索过程中的边界条件。

**核心代码**：
```cpp
void BFS(int num) {
    memset(vis, 0, sizeof(vis));
    while (!Q.empty()) Q.pop();
    vis[sx[num]][sy[num]] = 1;
    temp.sum = 0, temp.x = sx[num], temp.y = sy[num];
    Q.push(temp);
    while (!Q.empty()) {
        now = Q.front();
        int x = now.x, y = now.y, s = now.sum;
        Q.pop();
        dis[x][y] = min(s, dis[x][y]);
        for(int i=0; i<4; i++) {
            int xx = dx[i]+x, yy = dy[i]+y;
            int zx = rx[i]+x, zy = ry[i]+y;
            if(!vis[xx][yy] && map[xx][yy] == ' ' && xx <= 2*n+1 && xx > 0 && yy <= 2*m+1 && yy > 0 && map[zx][zy] == ' ' && (x != sx[num] || y != sy[num])) {
                vis[xx][yy] = 1;
                temp.x = xx, temp.y = yy, temp.sum = s+1;
                Q.push(temp);
            }
            if(!vis[zx][zy] && map[zx][zy] == ' ' && x == sx[num] && y == sy[num] && zx <= 2*n+1 && zy <= 2*m+1 && zx > 0 && zy > 0) {
                vis[zx][zy] = 1;
                temp.x = zx, temp.y = zy, temp.sum = s+1;
                Q.push(temp);
            }
        }
    }
}
```

#### 2. 作者：Manjusaka丶梦寒 (4星)
**关键亮点**：
- 通过将字符矩阵转换为数字矩阵，简化了搜索过程。
- 详细说明了如何通过BFS计算每个点到出口的最短距离。
- 代码结构清晰，注释详细，易于理解。

**个人心得**：
- 作者提到输入格式的处理较为复杂，通过多次尝试最终解决了问题。

**核心代码**：
```cpp
void bfs(int x,int y)
{
    ans[x][y]=0;
    vis[x][y]=1;
    str.x=x;str.y=y;
    que.push(str);
    while(!que.empty())
    {
        cur=que.front();
        que.pop() ;
        for(int i=0;i<4;i++)
        {
            str.x=cur.x+dx[i];
            str.y=cur.y+dy[i];
            if(map[str.x][str.y]!=2&&str.x>=1&&str.x<=h
            &&str.y>=1&&str.y<=w&&!vis[str.x][str.y])
            {
                ans[str.x][str.y]=min(ans[cur.x][cur.y]+map[str.x][str.y],ans[str.x][str.y]);
                            
                vis[str.x][str.y]=1;
                que.push(str); 
            }
        }
    } 
    memset(vis,0,sizeof(vis));
}
```

#### 3. 作者：HighPerformanceRobot (4星)
**关键亮点**：
- 通过反向思维，从出口开始进行BFS，记录每个点到出口的最短距离。
- 详细说明了输入格式的处理和搜索过程中的优化技巧。
- 代码结构清晰，注释详细，易于理解。

**个人心得**：
- 作者提到调试了3小时，主要问题在于输入格式的处理和搜索过程中的边界条件。

**核心代码**：
```cpp
void bfs(int x,int y)
{
    ans[x][y]=0;
    vis[x][y]=1;
    str.x=x;str.y=y;
    que.push(str);
    while(!que.empty())
    {
        cur=que.front();
        que.pop() ;
        for(int i=0;i<4;i++)
        {
            str.x=cur.x+dx[i];
            str.y=cur.y+dy[i];
            if(map[str.x][str.y]!=2&&str.x>=1&&str.x<=h
            &&str.y>=1&&str.y<=w&&!vis[str.x][str.y])
            {
                ans[str.x][str.y]=min(ans[cur.x][cur.y]+map[str.x][str.y],ans[str.x][str.y]);
                            
                vis[str.x][str.y]=1;
                que.push(str); 
            }
        }
    } 
    memset(vis,0,sizeof(vis));
}
```

### 最优关键思路与技巧
1. **双向BFS**：从两个出口分别进行BFS，记录每个点到出口的最短距离，最后取最大值。
2. **输入格式处理**：通过`gets`或`getline`处理输入，确保读取完整的迷宫信息。
3. **搜索优化**：通过记录每个点的最短距离，避免重复搜索，提高效率。

### 可拓展之处
- **类似题目**：可以扩展到其他迷宫类题目，如寻找最短路径、判断是否可达等。
- **算法套路**：BFS、DFS等搜索算法在迷宫类题目中广泛应用，可以通过练习类似题目加深理解。

### 推荐题目
1. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)
2. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)
3. [P1131 拯救大兵瑞恩](https://www.luogu.com.cn/problem/P1131)

### 个人心得总结
- **调试经历**：多位作者提到调试时间较长，主要问题在于输入格式的处理和搜索过程中的边界条件。
- **顿悟感想**：通过多次尝试和调试，最终解决了问题，加深了对搜索算法的理解。

---
处理用时：55.03秒