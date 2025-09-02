# 题目信息

# [USACO06OCT] Cows on Skates G

## 题目描述

**本题使用 Special Judge。**

Farmer John 把农场划分为了一个 $r$ 行 $c$ 列的矩阵，并发现奶牛们无法通过其中一些区域。此刻，Bessie 位于坐标为 $(1,1)$ 的区域，并想到坐标为 $(r,c)$ 的牛棚享用晚餐。她知道，以她所在的区域为起点，每次移动至相邻的四个区域之一，总有一些路径可以到达牛棚。

这样的路径可能有无数种，请你输出任意一种，并保证所需移动次数不超过 $100000$。

## 说明/提示

**【数据范围】**

对于 $100\%$ 的数据，$1\le r\le 113$，$1\le c\le 77$。

------------

**【样例说明】* *

![](https://cdn.luogu.com.cn/upload/image_hosting/3gsutffb.png)

图为样例输出的示意图。答案不唯一。

## 样例 #1

### 输入

```
5 8
..*...**
*.*.*.**
*...*...
*.*.*.*.
....*.*.```

### 输出

```
1 1
1 2
2 2
3 2
3 3
3 4
2 4
1 4
1 5
1 6
2 6
3 6
3 7
3 8
4 8
5 8```

# AI分析结果

### 综合分析与结论

本题解主要围绕DFS和BFS两种搜索算法展开，目的是在矩阵中找到从起点到终点的路径。大部分题解都采用了DFS，部分题解使用了BFS。DFS的实现中，关键在于如何记录路径和避免重复访问，而BFS则需要通过队列和路径记录来实现。整体来看，DFS的实现较为简单，但容易陷入递归深度过大的问题；BFS虽然实现稍复杂，但在某些情况下效率更高。

### 所选高分题解

#### 1. 作者：MY（一名蒟蒻） (赞：122)
- **星级**：4.5
- **关键亮点**：
  - 使用DFS实现，代码简洁易懂。
  - 通过`book`数组标记已访问节点，避免重复访问。
  - 使用`f`变量控制路径输出，确保只输出一条路径。
- **个人心得**：
  - 提到“book数组不需要取消标记”，避免了不必要的回溯，提升了效率。
  
**核心代码**：
```cpp
void dfs(int x, int y, int step) {
    if(x == r && y == c) {
        for(int i=1;i<step;i++) printf("%d %d\n",ax[i],ay[i]);
        printf("%d %d",r,c);
        f=true;
        return ;
    }
    ax[step]=x; ay[step]=y;
    book[x][y]=1;
    for(int i=0;i<4;i++) {
        dfs(x+next[i][0], y+next[i][1], step+1);
        if(f) return ;
    }
}
```

#### 2. 作者：do_while_false (赞：30)
- **星级**：4
- **关键亮点**：
  - 使用DFS，通过`vis`数组标记已访问节点。
  - 使用`ans`数组记录路径，输出时直接遍历数组。
  - 通过`exit(0)`直接结束程序，确保只输出一条路径。
  
**核心代码**：
```cpp
void dfs(int x, int y) {
    if(x==r&&y==c) {
        print();
        exit(0);
    }
    for(int i=0;i<4;i++) {
        int xx=x+dx[i], yy=y+dy[i];
        if(!vis[xx][yy] && xx>0 && xx<=r && yy>0 && yy<=c && a[xx][yy]=='.') {
            vis[xx][yy]=1;
            num++;
            ans[num][0]=xx; ans[num][1]=yy;
            dfs(xx, yy);
            num--;
        }
    }
}
```

#### 3. 作者：☆木辛土申☆ (赞：16)
- **星级**：4
- **关键亮点**：
  - 使用BFS实现，通过队列进行层次遍历。
  - 使用`dist`数组记录路径，通过递归输出路径。
  - 代码结构清晰，注释详细。
  
**核心代码**：
```cpp
void bfs(int sx, int sy) {
    std::queue<std::pair<int,int> > q;
    q.push(std::make_pair(sx,sy));
    vis[sx][sy]=true;
    while(!q.empty()) {
        int x=q.front().first;
        int y=q.front().second;
        q.pop();
        for(int i=1;i<=4;i++) {
            int xx=x+fx[i], yy=y+fy[i];
            if(illegal(xx,yy)) continue;
            dist[xx][yy][0]=x; dist[xx][yy][1]=y;
            vis[xx][yy]=true;
            q.push(std::make_pair(xx,yy));
            if(xx==r&&yy==c) break;
        }
    }
}
```

### 最优关键思路与技巧

1. **DFS优化**：在DFS中，通过`book`数组标记已访问节点，避免重复访问，且不需要回溯，提升了效率。
2. **BFS路径记录**：在BFS中，通过`dist`数组记录每个节点的前驱节点，最后通过递归输出路径。
3. **提前终止**：使用`exit(0)`或`f`变量控制，确保只输出一条路径，避免不必要的搜索。

### 拓展思路

- **同类型题**：类似的问题包括迷宫问题、最短路径问题等，可以使用DFS或BFS解决。
- **算法套路**：DFS适合路径较少的情况，BFS适合路径较多或需要最短路径的情况。

### 推荐题目

1. [P1596 - 迷宫](https://www.luogu.com.cn/problem/P1596)
2. [P1506 - 拯救小哈](https://www.luogu.com.cn/problem/P1506)
3. [P1162 - 填涂颜色](https://www.luogu.com.cn/problem/P1162)

### 个人心得总结

- **调试经历**：部分题解提到在调试过程中遇到了TLE问题，通过优化标记数组和路径记录方式解决了问题。
- **踩坑教训**：在DFS中，回溯标记数组会导致效率低下，取消回溯可以显著提升性能。
- **顿悟感想**：DFS和BFS各有优劣，选择适合的算法可以事半功倍。

---
处理用时：27.99秒