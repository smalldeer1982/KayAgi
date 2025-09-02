# 题目信息

# [USACO12MAR] Tractor S

## 题目描述

经过一天漫长的工作，农场主 John 完全忘记了他的拖拉机还在场地中央。他的奶牛们总喜欢和他搞些恶作剧，它们在场地的不同位置丢下 $n$ 堆干草。这样 John 就必须先移走一些干草堆才能将拖拉机开走。

拖拉机和干草堆都可以看作是二维平面上的点，它们的坐标都是整数，没有哪堆干草的坐标和拖拉机的初始坐标一致。John 驾驶拖拉机只能沿着坐标轴的方向移动若干单位长度，比如说，他可以先朝北移动 $2$ 个单位长度，再向东移动 $3$ 个单位长度等等。拖拉机不能移动到干草堆所占据的点。

请你帮助 John 计算一下，最少要移动多少堆干草才能将拖拉机开回坐标原点。

## 说明/提示

对于 $100\%$ 的数据，保证 $1 \leq n \leq 5 \times 10^4$，$1 \leq x_i, y_i \leq 10^3$。

## 样例 #1

### 输入

```
7 6 3 
6 2 
5 2 
4 3 
2 1 
7 3 
5 4 
6 4 ```

### 输出

```
1 ```

# AI分析结果

### 综合分析与结论
这些题解主要围绕如何计算从拖拉机初始位置到原点最少移除干草堆的数量展开，大多采用搜索算法，如 BFS、01 BFS、优先队列 BFS、SPFA 等，部分还结合了 DFS 或图论算法。不同题解在思路和实现上各有特点，有的注重易理解性，有的追求优化效率。

### 所选题解
- 作者：一只书虫仔（4星）
  - 关键亮点：思路清晰，详细介绍了 01 BFS 的使用，代码结构简洁，对 01 BFS 的应用场景有总结。
  - 个人心得：题目是课上考试题，由教练提供思路和代码进行研究。
- 作者：_Atyou（4星）
  - 关键亮点：双端队列 BFS 思路明确，对细节处理有详细说明，保证了队列中节点答案的单调性，复杂度较低。
  - 个人心得：无。
- 作者：soy_un_perro（4星）
  - 关键亮点：使用优先队列广搜，借助贪心思想，以移动的干草数为第一关键字建立小根堆，逻辑清晰。
  - 个人心得：无。

### 重点代码及核心思想
#### 一只书虫仔
```cpp
while (!q.empty()) {
    Node cur = q.front();
    q.pop_front();
    for (int k = 0; k < 4; k++) {
        Node nxt;
        nxt.x = cur.x + stx[k], nxt.y = cur.y + sty[k];
        if (nxt.x < 0 || nxt.x >= MAXM) continue;
        if (nxt.y < 0 || nxt.y >= MAXM) continue;
        if (step[nxt.x][nxt.y] != -1) continue;
        if (map[nxt.x][nxt.y]) {
            step[nxt.x][nxt.y] = step[cur.x][cur.y] + 1;
            q.push_back(nxt);
        }
        else {
            step[nxt.x][nxt.y] = step[cur.x][cur.y];
            q.push_front(nxt);
        }
    }
}
```
核心思想：01 BFS，使用双端队列 `deque`，遇到干草堆的点加入队尾，无干草堆的点加入队首，保证队列中节点的最优性。

#### _Atyou
```cpp
while (q.size()) {
    int x=q.front().first, y=q.front().second; q.pop_front();
    if (x == 0 && y == 0) {
        write(f[x][y]);  
        return 0;
    }
    for (register int i=0; i<4; i++) {
        int x0=x+dx[i], y0=y+dy[i];
        if (x0 < 0 || x0 > 1001 || y0 < 0 || y0 > 1001) continue;
        if (v[x0][y0]) continue; 
        v[x0][y0]=1;
        f[x0][y0]=f[x][y]+a[x0][y0];
        if (a[x0][y0]) q.push_back(make_pair(x0, y0));
        else q.push_front(make_pair(x0, y0));
    }
}
```
核心思想：双端队列 BFS，遇到草堆的点压到队尾，没遇到草堆的点压到队头，保证队列中节点答案的单调性。

#### soy_un_perro
```cpp
while(!q.empty())
{
    x=-q.top().second.first;
    y=-q.top().second.second;
    step=-q.top().first;
    q.pop();
    if (x==0 && y==0)
        return step;
    for(int i=0;i<4;i++)
    {
        if (x+dx[i]>=0 && x+dx[i]<=1050 
        && y+dy[i]>=0 && y+dy[i]<=1050 
        && !v[x+dx[i]][y+dy[i]])
        {
            if (m[x+dx[i]][y+dy[i]])
                q.push(make_pair(-step-1,make_pair(-x-dx[i],-y-dy[i])));
            else
                q.push(make_pair(-step,make_pair(-x-dx[i],-y-dy[i])));
            v[x+dx[i]][y+dy[i]]=1;
        }
    }
}
```
核心思想：优先队列广搜，以移动的干草数为第一关键字建立小根堆，贪心选取最优解。

### 最优关键思路或技巧
- **01 BFS**：适用于边权为 0 或 1 的最短路问题，通过双端队列，将边权为 0 的点加入队首，边权为 1 的点加入队尾，保证队列中节点的最优性，时间复杂度较低。
- **优先队列广搜**：以移动的干草数为第一关键字建立小根堆，借助贪心思想，每次选取移动干草数最少的点进行扩展，能快速找到最优解。

### 拓展思路
同类型题或类似算法套路：
- 涉及网格图的最短路问题，边权为 0 或 1 时可考虑 01 BFS。
- 求最小代价的路径问题，可使用优先队列广搜，以代价为关键字建立小根堆。

### 推荐题目
- [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)
- [P1346 电车](https://www.luogu.com.cn/problem/P1346)
- [P4779 单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)

### 个人心得总结
- 一只书虫仔：通过研究教练给的思路和代码学习 01 BFS，认识到 01 BFS 在边权为 0 或 1 的最短路问题中的实用性。
- maple_tzc：使用 SPFA 时要注意数组越界问题，数组要开大一些，避免不必要的错误。

---
处理用时：41.81秒