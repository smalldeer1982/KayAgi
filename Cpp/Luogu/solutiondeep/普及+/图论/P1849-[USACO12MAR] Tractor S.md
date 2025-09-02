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
这些题解主要围绕如何计算从拖拉机初始位置到原点最少移除干草堆数量展开，采用了多种搜索算法。其中 01 BFS、双端队列 BFS 和优先队列广搜应用较多，这些方法能利用边权为 0 或 1 的特点高效求解。部分题解采用多次 BFS、SPFA、DFS 辅助 BFS 等方法，但复杂度相对较高。整体来看，01 BFS 和双端队列 BFS 思路清晰、复杂度低，是较优选择。

### 所选题解
- 作者：一只书虫仔 (赞：13)，4 星
  - 关键亮点：思路清晰，详细介绍 01 BFS 方法，代码简洁易懂，对 01 BFS 适用场景有总结。
  - 个人心得：该题解是课上考试题，教练给了思路和代码让作者研究。
- 作者：_Atyou (赞：11)，4 星
  - 关键亮点：详细解释双端队列 BFS 原理和细节，复杂度分析清晰，代码规范。
  - 个人心得：无。
- 作者：soy_un_perro (赞：9)，4 星
  - 关键亮点：采用优先队列广搜，借助贪心思想，代码实现简洁。
  - 个人心得：无。

### 重点代码及核心实现思想
#### 01 BFS（一只书虫仔）
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
核心思想：使用双端队列，遇到干草堆将节点加入队尾，否则加入队首，保证队列中节点答案的单调性。

#### 双端队列 BFS（_Atyou）
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
核心思想：与 01 BFS 类似，走四个方向，遇到草堆压到队尾，没遇到压到队头，保证队列中节点答案单调。

#### 优先队列广搜（soy_un_perro）
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
核心思想：建立以移动的干草数为第一关键字的小根堆，借助贪心，取出堆顶坐标为 (0, 0) 时即为最优解。

### 最优关键思路或技巧
- **01 BFS 和双端队列 BFS**：适用于边权为 0 或 1 的最短路问题，通过双端队列维护节点顺序，保证队列中节点答案的单调性，提高搜索效率。
- **优先队列广搜**：利用优先队列建立小根堆，以移动的干草数为第一关键字，借助贪心思想快速找到最优解。

### 可拓展之处
同类型题如迷宫问题、网格最短路径问题等，只要能转化为边权为 0 或 1 的最短路问题，都可尝试使用 01 BFS 或双端队列 BFS 求解。类似算法套路还有 Dijkstra 算法、SPFA 算法等，可根据具体问题选择合适的算法。

### 推荐题目
- [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)
- [P1330 封锁阳光大学](https://www.luogu.com.cn/problem/P1330)
- [P1608 路径统计](https://www.luogu.com.cn/problem/P1608)

### 个人心得总结
- 一只书虫仔：通过研究教练给的思路和代码学习 01 BFS 方法，对 01 BFS 适用场景有了更深入的理解。
- maple_tzc：使用 SPFA 时要注意数组越界问题，数组要开大一些，避免出现莫名错误。

---
处理用时：42.01秒