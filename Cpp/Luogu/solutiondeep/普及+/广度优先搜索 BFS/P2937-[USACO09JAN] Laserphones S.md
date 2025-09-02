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

本题的核心在于通过BFS或DFS搜索算法，找到从起点到终点的最小转弯次数（即最小镜子数量）。大部分题解采用了BFS，部分使用了DFS，且多数题解通过方向标记、分层图、双端队列等技巧进行优化。以下是对各题解的总结与对比：

1. **BFS与DFS的选择**：BFS是更常见的选择，因为它天然适合求解最短路径问题。DFS则通常需要剪枝或记忆化来避免超时。
2. **方向标记**：许多题解通过记录当前方向来避免重复搜索，减少了不必要的计算。
3. **分层图**：部分题解通过构建分层图，将方向作为状态的一部分，从而将问题转化为最短路问题。
4. **双端队列**：部分题解使用双端队列优化BFS，将不改变方向的点放入队首，改变方向的点放入队尾，从而减少转弯次数的计算。
5. **剪枝与记忆化**：DFS题解通常通过记忆化或剪枝来优化搜索过程，避免重复计算。

### 精选题解

#### 1. **作者：IRipple (赞：24)**
- **星级**：★★★★★
- **关键亮点**：通过BFS逐层扩展，记录每个点的扩展步数，思路清晰，代码简洁。
- **核心代码**：
  ```cpp
  void bfs(){
      while(!q.empty()){
          node u=q.front(),v=u;
          q.pop();
          u.num++;
          v=u; v.x=u.x-1; dfs(1,v); // 上
          v=u; v.x=u.x+1; dfs(2,v); // 下
          v=u; v.y=u.y-1; dfs(3,v); // 左
          v=u; v.y=u.y+1; dfs(4,v); // 右
      }
  }
  ```
- **个人心得**：通过逐层扩展，记录每个点的步数，避免了复杂的剪枝和记忆化。

#### 2. **作者：Delva (赞：20)**
- **星级**：★★★★☆
- **关键亮点**：通过分层图将问题转化为最短路问题，使用Dijkstra算法求解，思路新颖。
- **核心代码**：
  ```cpp
  for(int t=1;t<=4;++t){ // 层内建图
      for(int i=1;i<=n;++i){
          for(int j=1;j<=m;++j){
              int nx=i+dx[t],ny=j+dy[t];
              if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&M[i][j]!='*'&&M[nx][ny]!='*')
                  addEdge(point_ID(t,i,j),point_ID(t,nx,ny),0);
          }
      }
  }
  ```
- **个人心得**：通过分层图将方向作为状态的一部分，转化为最短路问题，思路巧妙。

#### 3. **作者：学而思李老师 (赞：6)**
- **星级**：★★★★☆
- **关键亮点**：使用双端队列优化BFS，将不改变方向的点放入队首，改变方向的点放入队尾，优化了转弯次数的计算。
- **核心代码**：
  ```cpp
  if(tmp.last == 0 || i == tmp.last){ // 不改变方向
      if(vis[xx][yy] >= tmp.t && a[xx][yy] != 1){
          vis[xx][yy] = tmp.t;
          d.push_front(Node{xx, yy, tmp.t, i});
      }
  } else { // 改变方向
      if(vis[xx][yy] >= tmp.t + 1 && a[xx][yy] != 1){
          vis[xx][yy] = tmp.t + 1;
          d.push_back(Node{xx, yy, tmp.t + 1, i});
      }
  }
  ```
- **个人心得**：通过双端队列优化BFS，减少了转弯次数的计算，思路清晰。

### 最优关键思路与技巧

1. **方向标记**：通过记录当前方向，避免重复搜索，减少计算量。
2. **分层图**：将方向作为状态的一部分，转化为最短路问题，适合复杂场景。
3. **双端队列优化BFS**：将不改变方向的点放入队首，改变方向的点放入队尾，优化了转弯次数的计算。

### 拓展与举一反三

1. **类似题目**：
   - [P1126 机器人搬重物](https://www.luogu.org/problemnew/show/P1126)：类似的最少转弯次数问题。
   - [P1649 障碍物赛跑](https://www.luogu.org/problemnew/show/P1649)：通过障碍物的最短路径问题。
   - [P1849 双端队列BFS](https://www.luogu.org/problemnew/show/P1849)：双端队列优化的BFS问题。

2. **调试与顿悟**：
   - **IRipple**：通过逐层扩展，避免了复杂的剪枝和记忆化，思路清晰。
   - **Delva**：通过分层图将方向作为状态的一部分，转化为最短路问题，思路新颖。
   - **学而思李老师**：通过双端队列优化BFS，减少了转弯次数的计算，思路清晰。

---
处理用时：37.37秒