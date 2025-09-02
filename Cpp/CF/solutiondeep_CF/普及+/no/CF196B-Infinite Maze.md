# 题目信息

# Infinite Maze

## 题目描述

We've got a rectangular $ n×m $ -cell maze. Each cell is either passable, or is a wall (impassable). A little boy found the maze and cyclically tiled a plane with it so that the plane became an infinite maze. Now on this plane cell $ (x,y) $ is a wall if and only if cell ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF196B/90d712000eb85a8bfa2ea0243ba4ea17c7b21954.png) is a wall.

In this problem ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF196B/8f971526abdeb0e01a924ce3de8c76d38e0d2bfd.png) is a remainder of dividing number $ a $ by number $ b $ .

The little boy stood at some cell on the plane and he wondered whether he can walk infinitely far away from his starting position. From cell $ (x,y) $ he can go to one of the following cells: $ (x,y-1) $ , $ (x,y+1) $ , $ (x-1,y) $ and $ (x+1,y) $ , provided that the cell he goes to is not a wall.

## 说明/提示

In the first sample the little boy can go up for infinitely long as there is a "clear path" that goes vertically. He just needs to repeat the following steps infinitely: up, up, left, up, up, right, up.

In the second sample the vertical path is blocked. The path to the left doesn't work, too — the next "copy" of the maze traps the boy.

## 样例 #1

### 输入

```
5 4
##.#
##S#
#..#
#.##
#..#
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
5 4
##.#
##S#
#..#
..#.
#.##
```

### 输出

```
No
```

# AI分析结果

### 题目内容
# 无限迷宫

## 题目描述
我们有一个 $n×m$ 单元格的矩形迷宫。每个单元格要么是可通行的，要么是墙壁（不可通行）。一个小男孩发现了这个迷宫，并将其循环平铺在一个平面上，使得这个平面变成了一个无限迷宫。现在在这个平面上，单元格 $(x,y)$ 是墙壁，当且仅当单元格 $(x \bmod n, y \bmod m)$ 是墙壁。

在本题中，$a \bmod b$ 表示 $a$ 除以 $b$ 的余数。

小男孩站在平面上的某个单元格，他想知道自己是否能从起始位置走得无限远。从单元格 $(x,y)$ 他可以走到以下单元格之一：$(x,y - 1)$，$(x,y + 1)$，$(x - 1,y)$ 和 $(x + 1,y)$，前提是他要去的单元格不是墙壁。

## 说明/提示
在第一个样例中，小男孩可以向上无限远地走，因为有一条垂直的 “畅通路径”。他只需要无限重复以下步骤：上，上，左，上，上，右，上。

在第二个样例中，垂直路径被堵住了。向左的路径也行不通 —— 迷宫的下一个 “副本” 困住了小男孩。

## 样例 #1
### 输入
```
5 4
##.#
##S#
#..#
#.##
#..#
```
### 输出
```
Yes
```

## 样例 #2
### 输入
```
5 4
##.#
##S#
#..#
..#.
#.##
```
### 输出
```
No
```

### 算法分类
深度优先搜索 DFS、广度优先搜索 BFS

### 综合分析与结论
这些题解的核心思路都是通过搜索算法（主要是 DFS 和 BFS）来判断是否能从起点走到无限远。由于迷宫是无限的，不能直接开辟大数组存储，所以都利用了坐标取模的方式来处理。判断条件基本一致，即当通过不同路径到达取模后相同坐标的点时，就说明可以走到无限远。各题解的主要区别在于实现细节，如标记方式、搜索方向处理等。

### 所选的题解
- **作者：filletoto (赞：3)  星级：4星**
    - **关键亮点**：使用三维数组 `vis` 标记点，不仅记录取模后的坐标是否访问过，还记录未取模的坐标，通过比较两者判断是否通过不同路径到达同一点。
    - **个人心得**：无
    - **核心代码**：
```cpp
void dfs(int x,int y,int lx,int ly)
{
    if(vis[x][y][0]&&(vis[x][y][1]!=lx||vis[x][y][2]!=ly)) 
    {
        fl=1;
        return ;
    }
    if(fl) return ;
    vis[x][y][1]=lx;
    vis[x][y][2]=ly;
    vis[x][y][0]=1;
    for(int i=0;i<4;++i) 
    {
        int xx=(x+dx[i]+n)%n;
        int yy=(y+dy[i]+m)%m;
        int lxx=lx+dx[i];
        int lyy=ly+dy[i];
        if(!a[xx][yy]) 
        {
            if(vis[xx][yy][1]!=lxx||vis[xx][yy][2]!=lyy||!vis[xx][yy][0])
                dfs(xx, yy, lxx, lyy);
        }
    }
}
```
核心实现思想：在 `dfs` 函数中，先判断当前点是否满足通过不同路径到达的条件，满足则标记可走到无限远；否则标记当前点及对应的未取模坐标，然后向四个方向搜索，若新点可走且满足未访问或通过不同路径到达的条件，继续递归搜索。

- **作者：xukuan (赞：3)  星级：4星**
    - **关键亮点**：指出常见错误思路并给出 Hack 数据，强调正解是通过 DFS 判断是否能通过不同方式到达取模后相同坐标的点，时间复杂度分析清晰。
    - **个人心得**：无
    - **核心代码**：
```cpp
void dfs(ll x,ll y){
    if(d[x%n][y%m][0]==-1&&d[x%n][y%m][1]==-1){//这个点之前没有到过
        d[x%n][y%m][0]=x;
        d[x%n][y%m][1]=y;
    }
    else if(d[x%n][y%m][0]!=x||d[x%n][y%m][1]!=y) exit(printf("Yes\n")&0);//这个点之前到过并且不是直接到的
    else return;//直接到过这个点
    for(ll i=0; i<4; i++){
        ll X=x+dx[i],Y=y+dy[i];
        if(s[X%n][Y%m]=='.') dfs(X,Y);
    }
}
```
核心实现思想：在 `dfs` 函数中，先判断当前取模后的点是否首次到达，是则记录当前实际坐标；若已到达且实际坐标与之前记录不同，说明可走到无限远并输出；否则直接返回。然后向四个方向搜索，若新点可走则继续递归搜索。

- **作者：Lotus_Land (赞：0)  星级：4星**
    - **关键亮点**：采用 BFS 算法解决问题，通过队列实现，思路清晰，同样利用坐标取模判断是否在不同地图块中走到相同相对位置的点。
    - **个人心得**：无
    - **核心代码**：
```cpp
bool BFS() {
    while(!q.empty())q.pop();
    q.push(make_pair(stx,sty));
    vis[stx][sty]=make_pair(stx,sty);
    sg[stx][sty]=1;
    while(!q.empty()) {
        int x=q.front().first;
        int y=q.front().second;
        q.pop();
        for(int i=0; i<4; i++) {
            int xx=x+fx[i],yy=y+fy[i];
            if(mp[(xx%n+n)%n][(yy%m+m)%m]) {
                if(!sg[(xx%n+n)%n][(yy%m+m)%m]) {
                    sg[(xx%n+n)%n][(yy%m+m)%m]=1;
                    vis[(xx%n+n)%n][(yy%m+m)%m]=make_pair(xx,yy);
                    q.push(make_pair(xx,yy));
                } else {
                    if(vis[(xx%n+n)%n][(yy%m+m)%m]!=make_pair(xx,yy)) {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}
```
核心实现思想：在 `BFS` 函数中，先将起点入队并标记。然后在队列不为空时，取出队首元素，向四个方向搜索新点。若新点可走且未访问过，标记并将其入队；若已访问且实际坐标与之前记录不同，说明可走到无限远返回 `true`，最后若遍历完所有可达点都未满足条件则返回 `false`。

### 最优关键思路或技巧
利用坐标取模处理无限迷宫，通过标记取模后的坐标以及其对应的实际坐标，判断是否能通过不同路径到达取模后相同坐标的点，以此确定能否走到无限远。无论是 DFS 还是 BFS 都围绕此核心思路展开，实现上注意边界处理和标记的准确性。

### 同类型题或类似算法套路拓展
同类型题通常围绕在无限空间或大规模数据下，通过有限的表示（如坐标取模）来解决搜索相关问题。类似算法套路还包括在图的遍历中，通过记录额外信息（如访问路径、层次等）来判断特定条件是否满足。

### 洛谷相似题目推荐
- [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)：通过搜索判断连通区域，与本题通过搜索判断路径特性类似。
- [P1339 热浪](https://www.luogu.com.cn/problem/P1339)：最短路问题，同样涉及图的搜索与路径判断。
- [P1596 [USACO10OCT]Lake Counting S](https://www.luogu.com.cn/problem/P1596)：利用搜索统计连通块数量，在搜索应用上有相似之处。 

---
处理用时：70.26秒