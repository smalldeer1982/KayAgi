# 题目信息

# [USACO04OPEN] Cave Cows 4

## 题目描述

一道竖直的石墙横在贝茜前面，她必须越过去。

石墙可以看成一个xz平面，贝茜开始的时候在(0，0)，只要她到达 $ z=T $ 
 ( $ 1 \leq T \leq 200000 $ )的位置，就算翻越成功。

墙上有 $ N $ ( $ 1 \leq N \leq 50000 $ )块石头突出，成为贝茜的落蹄石。如果两个落蹄石之间x方向和z方向的距离均不超过2，那贝茜就可以攀上另一块落蹄石。

帮助贝茜计算她是否能够翻越石墙，如果可以，最少需要踩多少块落蹄石。

## 说明/提示

一种可行的方案是：(0,0) -> (1,2) -> (3,2) -> (4,1) -> (6,3) 。

## 样例 #1

### 输入

```
5 3
1 2
6 3
4 1
3 2
0 2```

### 输出

```
4```

# AI分析结果

### 综合分析与结论
这些题解主要围绕如何解决贝茜翻越石墙的最少落蹄石问题，多数采用广度优先搜索（BFS），部分使用最短路算法（Dijkstra、SPFA）和双向广度优先搜索（DBFS）。

#### 思路对比
- **BFS**：多数题解采用BFS，利用`map`标记坐标是否有石头，枚举周围点判断能否到达，避免了 $O(n^2)$ 的连边复杂度。
- **最短路算法**：对石头排序后建图，跑Dijkstra或SPFA，通过排序减少无效边。
- **DBFS**：从起点和终点同时进行BFS，通过标记判断是否相遇。

#### 算法要点
- **BFS**：用队列存储待扩展的点，标记已访问的点避免重复访问。
- **最短路算法**：建图后使用优先队列优化Dijkstra或SPFA求解最短路径。
- **DBFS**：用两个队列分别从起点和终点开始BFS，标记不同的搜索方向。

#### 解决难点
- **坐标标记**：使用`map`解决坐标范围大无法用数组标记的问题。
- **连边优化**：通过枚举周围点或排序减少无效边，降低时间复杂度。

### 所选题解
- **作者：LJC00118（5星）**
    - **关键亮点**：思路清晰，代码规范，使用`map`存储坐标对应的石头编号，枚举周围石头连边后BFS求解。
    - **核心代码**：
```cpp
for(register int i = 1; i <= n; i++) {
    for(register int t1 = -2; t1 <= 2; t1++) {
        for(register int t2 = -2; t2 <= 2; t2++) {
            if(!t1 &&!t2) continue;
            int _x = x[i] + t1, _y = y[i] + t2;
            if(pre.count(make_pair(_x, _y))) {
                adj[i].push_back(pre[make_pair(_x, _y)]);
            }
        }
    }
}
memset(dis, -1, sizeof(dis)); dis[n] = 0; q.push(n);
while(!q.empty()) {
    int u = q.front(); q.pop();
    for(register int i = 0; i < (int)adj[u].size(); i++) {
        int v = adj[u][i];
        if(dis[v] == -1) {
            dis[v] = dis[u] + 1;
            q.push(v);
        }
    }
}
```
- **作者：lidagua1004（4星）**
    - **关键亮点**：思路简洁，使用`map`标记石头位置，BFS过程中枚举周围点判断能否到达。
    - **核心代码**：
```cpp
q.push({0,0,0});
while(!q.empty()){
    int x=q.front().x;
    int y=q.front().y;
    int dep=q.front().dep;
    q.pop();
    if(y==t) return dep;
    for(int i=-2;i<=2;i++){
        for(int j=-2;j<=2;j++){
            int xi=x+i,yj=y+j;
            if(mp[xi][yj]&&!vis[xi][yj]){
                vis[xi][yj]=1;
                q.push({xi,yj,dep+1});
            }
        }
    }
}
```
- **作者：Light_az（4星）**
    - **关键亮点**：代码简洁易懂，同样使用`map`标记石头位置，BFS求解。
    - **核心代码**：
```cpp
q.push({0,0,0});
while(!q.empty()){
    Node p=q.front();
    q.pop();
    if(p.y==k) return p.dep;
    F(i,-2,2) F(j,-2,2){
        x=p.x+i,y=p.y+j;
        if(mp[x][y]&&!vis[x][y]){
            vis[x][y]=1;
            q.push({x,y,p.dep+1});
        }
    }
}
```

### 最优关键思路或技巧
- **使用`map`标记坐标**：解决坐标范围大无法用数组标记的问题。
- **枚举周围点连边**：避免 $O(n^2)$ 的连边复杂度。
- **排序减少无效边**：在最短路算法中，对石头排序后建图，减少无效边。

### 可拓展之处
- **同类型题**：其他需要在二维平面上寻找最短路径的问题，如迷宫问题、过河问题等。
- **类似算法套路**：可以使用A*算法、IDA*算法等启发式搜索算法优化搜索过程。

### 推荐题目
- [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)
- [P1135 奇怪的电梯](https://www.luogu.com.cn/problem/P1135)
- [P1605 迷宫](https://www.luogu.com.cn/problem/P1605)

### 个人心得
- **BreakPlus**：提到链式前向星数组要开大一些，避免卡边数；还祝大家CSP2020 Score++ RP++。
- **HRLYB**：认为在建边时适当剪枝可卡过题目，手写队列比STL队列快，用vis数组标记已访问点保证最优解。 

---
处理用时：33.00秒