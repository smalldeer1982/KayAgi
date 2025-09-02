# 题目信息

# [USACO08NOV] Guarding the Farm S

## 题目描述

The farm has many hills upon which Farmer John would like to place guards to ensure the safety of his valuable milk-cows.

He wonders how many guards he will need if he wishes to put one on top of each hill. He has a map supplied as a matrix of integers; the matrix has N (1 < N <= 700) rows and M (1 < M <= 700) columns. Each member of the matrix is an altitude H\_ij (0 <= H\_ij <= 10,000). Help him determine the number of hilltops on the map.

A hilltop is one or more adjacent matrix elements of the same value surrounded exclusively by either the edge of the map or elements with a lower (smaller) altitude. Two different elements are adjacent if the magnitude of difference in their X coordinates is no greater than 1 and the magnitude of differences in their Y coordinates is also no greater than 1.


## 说明/提示

There are three peaks: The one with height 4 on the left top, one of the points with height 2 at the bottom part, and one of the points with height 1 on the right top corner.


## 样例 #1

### 输入

```
8 7 
4 3 2 2 1 0 1 
3 3 3 2 1 0 1 
2 2 2 2 1 0 0 
2 1 1 1 1 0 0 
1 1 0 0 0 1 0 
0 0 0 1 1 1 0 
0 1 2 2 1 1 0 
0 1 1 1 2 1 0 
```

### 输出

```
3 
```

# AI分析结果

### 综合分析与结论
这些题解主要围绕农场山丘数量计算问题展开，核心在于判断矩阵中哪些区域可构成山丘。多数题解采用排序后搜索的策略，利用深度优先搜索（DFS）或广度优先搜索（BFS）来遍历矩阵。

#### 思路对比
- **排序后搜索**：多数题解将矩阵元素按高度从大到小排序，从最高的点开始搜索，避免重复计算。如素质玩家孙1超、沉辰、Khassar等的题解。
- **先排除后计数**：ouuan的题解先扫一遍找出周围有比自己高的格子所在的连通块，将其排除，剩下的连通块即为山丘。
- **直接枚举判断**：吉瑞降临、巨型方块等的题解直接枚举每个色块，判断其是否为山丘。

#### 算法要点
- **数据结构**：使用结构体存储矩阵元素的坐标和高度，方便排序。
- **搜索算法**：DFS和BFS是主要的搜索算法，用于遍历矩阵中的连通块。
- **标记数组**：使用标记数组记录已访问的格子，避免重复访问。

#### 解决难点
- **重复计算问题**：通过从高到低排序和标记已访问的格子，避免重复计算山丘数量。
- **边界处理**：在搜索过程中，需要判断是否越界，确保程序的正确性。

### 所选题解
- **素质玩家孙1超（4星）**
    - **关键亮点**：思路清晰，代码注释详细，使用快读优化输入。
    - **个人心得**：原没看懂题目意思，被坑了好久，认为题目意思不是非常明确。
- **沉辰（4星）**
    - **关键亮点**：思路简洁，使用BFS进行搜索，代码结构清晰。
    - **个人心得**：无。
- **ouuan（4星）**
    - **关键亮点**：提出了独特的判断山丘的方法，先排除不可能是山丘的连通块，再计数。
    - **个人心得**：想过从高到低搜索的做法，但总感觉自己会写错。

### 重点代码
#### 素质玩家孙1超的核心代码
```cpp
void dfs(int x,int y)
{
    if(x>n||y>m||!x||!y) return;//越界 
    flag[x][y]=1;//标记 
    for(int i=0;i<8;i++)//搜索 
        if(!flag[x+dx[i]][y+dy[i]]&&q[x+dx[i]][y+dy[i]]<=q[x][y])
            dfs(x+dx[i],y+dy[i]);
}
```
**核心实现思想**：深度优先搜索，从当前点出发，向八个方向扩展，标记已访问的格子，确保扩展的格子高度不高于当前点。

#### 沉辰的核心代码
```cpp
void bfs(int x,int y)
{
    qx.push(x);qy.push(y);
    v[x][y]=1;
    while(!qx.empty())
    {
      fx=qx.front();qx.pop();
      fy=qy.front();qy.pop();
      H=h[fx][fy];
      for(int i=0;i<=7;i++)
      {
        rx=X[i]+fx;ry=Y[i]+fy;
        if(rx<1 || rx >n || ry<1 || ry>m) continue;
        if(v[rx][ry]) continue;    
        if(h[rx][ry]<=H)
        {
          qx.push(rx);qy.push(ry);
          v[rx][ry]=1;    
        }
      }    
    }
}
```
**核心实现思想**：广度优先搜索，使用队列存储待扩展的格子，从当前点出发，向八个方向扩展，标记已访问的格子，确保扩展的格子高度不高于当前点。

#### ouuan的核心代码
```cpp
void dfs(int x,int y)
{
    if (vis[x][y]||x==0||y==0||x>n||y>m)
    {
        return;
    }
    
    vis[x][y]=true;
    
    for (int i=0;i<8;++i)
    {
        if (a[x][y]==a[x+dir[i][0]][y+dir[i][1]])
        {
            dfs(x+dir[i][0],y+dir[i][1]);
        }
    }
}
```
**核心实现思想**：深度优先搜索，从当前点出发，向八个方向扩展，标记已访问的格子，确保扩展的格子高度与当前点相同。

### 最优关键思路或技巧
- **排序优化**：将矩阵元素按高度从大到小排序，从最高的点开始搜索，可有效避免重复计算。
- **标记数组**：使用标记数组记录已访问的格子，避免重复访问，提高效率。
- **搜索算法**：DFS和BFS是解决连通块问题的常用算法，根据具体情况选择合适的搜索算法。

### 可拓展之处
同类型题或类似算法套路包括：
- **岛屿数量问题**：判断矩阵中岛屿的数量，每个岛屿由相邻的陆地格子组成。
- **连通分量问题**：计算图中连通分量的数量，每个连通分量由相互连通的节点组成。
- **洪水填充问题**：将矩阵中某个区域的颜色填充为另一种颜色，填充的区域由相邻的相同颜色的格子组成。

### 推荐题目
- [P1596 [USACO10OCT]Lake Counting S](https://www.luogu.com.cn/problem/P1596)
- [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)
- [P2002 消息扩散](https://www.luogu.com.cn/problem/P2002)

### 个人心得总结
- 素质玩家孙1超：原没看懂题目意思，被坑了好久，认为题目意思不是非常明确。
- ouuan：想过从高到低搜索的做法，但总感觉自己会写错。
- Hiraeth：在递归调用时，全局变量的值会被改变，导致错误，以后在DFS里面只用局部变量。

---
处理用时：45.17秒