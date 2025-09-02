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
这些题解主要围绕寻找两点间最少镜子数量（即最少转弯次数）展开，采用的算法有 BFS、DFS 及最短路算法。BFS 类题解通常利用队列扩展节点，根据方向和障碍物判断是否继续扩展；DFS 类题解则通过递归搜索，结合记忆化或剪枝优化。最短路类题解构建分层图或使用双端队列优化。

### 所选题解
- **作者：IRipple (赞：24)，4星**
  - **关键亮点**：思路清晰，通过模拟扩展过程，使用 BFS 和 DFS 结合的方式，代码实现简洁易懂。
  - **个人心得**：无

### 重点代码
```cpp
struct node{
    int x,y;
    int num;
}s,t;
queue<node> q;

void dfs(int fx,node u){ 
    int x=u.x,y=u.y,p=u.num; 
    if(a[x][y]<p || a[x][y]==inf) return;
    if(x<1 || y<1 || x>n || y>m) return;

    if(fx==1){
        a[x][y]=p;
        q.push((node){x,y,p});
        dfs(1,(node){x-1,y,p});
    }
    if(fx==2){
        a[x][y]=p;
        q.push((node){x,y,p});
        dfs(2,(node){x+1,y,p});
    }
    if(fx==3){
        a[x][y]=p;
        q.push((node){x,y,p});
        dfs(3,(node){x,y-1,p});
    }
    if(fx==4){
        a[x][y]=p;
        q.push((node){x,y,p});
        dfs(4,(node){x,y+1,p});
    }
}

void bfs(){
    while(!q.empty()){
        node u=q.front(),v=q.front();
        q.pop();
        u.num++;
        v=u; v.x=u.x-1;
        dfs(1,v);
        v=u; v.x=u.x+1;
        dfs(2,v);
        v=u; v.y=u.y-1;
        dfs(3,v);
        v=u; v.y=u.y+1;
        dfs(4,v);
    }
}
```
**核心实现思想**：定义 `node` 结构体存储节点信息，`bfs` 函数扩展队首节点的四个方向，`dfs` 函数进行染色和递归扩展，通过 `a` 数组记录扩展步数，最终得到终点的最少镜子数量。

### 最优关键思路或技巧
- **记忆化**：在 DFS 或 BFS 中使用数组记录到达每个点的最优解，避免重复计算。
- **分层图**：将问题转化为分层图最短路问题，通过层内和层间建边，利用最短路算法求解。
- **剪枝**：在搜索过程中，若当前状态不是最优解，则提前终止搜索。

### 可拓展之处
同类型题如机器人路径规划、迷宫最短路径等，都可使用 BFS、DFS 或最短路算法解决。类似算法套路包括状态压缩、双向 BFS 等。

### 推荐题目
- P1126 机器人搬重物
- P1649 单向通行
- P1849 爱与愁的心痛

### 个人心得摘录与总结
- **Zekrom**：一开始尝试用双端队列做最短路，结果因激光的方向性导致单调性不成立而失败，最终将 `vis` 数组扩展到 3 维，用普通队列 BFS 求解。总结是要注意算法的适用条件，遇到问题及时调整思路。 

---
处理用时：24.99秒