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
这些题解主要围绕如何计算从拖拉机初始位置到原点最少移除干草堆的数量展开，采用了多种搜索算法，如普通BFS、01 BFS、优先队列BFS、SPFA、Dijkstra等，部分题解还结合了DFS辅助搜索。

不同算法的核心差异在于处理干草堆的方式和队列的使用策略。普通BFS通过多次搜索移除干草堆直到到达原点；01 BFS和双端队列BFS利用队列特性，将无干草堆的点优先处理，保证队列中节点答案的单调性；优先队列BFS则以移动的干草数为关键字构建小根堆，贪心求解；Dijkstra将连通块看作点，通过连边求最短路。

### 所选题解
- **一只书虫仔（4星）**
  - **关键亮点**：思路清晰，详细介绍了01 BFS的实现方法，代码注释完善，对01 BFS的适用场景有总结。
  - **个人心得**：该题解是教练给的思路和代码，作者进行研究学习。
- **_Atyou（4星）**
  - **关键亮点**：对双端队列BFS的原理和细节解释清晰，代码中包含快读快写优化，复杂度分析明确。
  - **个人心得**：强调了草堆范围外的处理细节，避免数组越界。
- **soy_un_perro（4星）**
  - **关键亮点**：采用优先队列广搜，以移动的干草数为第一关键字构建小根堆，借助贪心思想求解，代码简洁。
  - **个人心得**：无。

### 重点代码
#### 一只书虫仔（01 BFS）
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
**核心思想**：使用双端队列，遇到干草堆的点加入队尾，无干草堆的点加入队首，保证队列中节点答案的单调性。

#### _Atyou（双端队列BFS）
```cpp
while (q.size()) {
    int x=q.front().first, y=q.front().second; q.pop_front();
    if (x == 0 && y == 0) { //到了坐标原点 
        write(f[x][y]);  
        return 0;
    }
    for (register int i=0; i<4; i++) {
        int x0=x+dx[i], y0=y+dy[i];
        if (x0 < 0 || x0 > 1001 || y0 < 0 || y0 > 1001) continue; //超出范围 
        if (v[x0][y0]) continue; 
        v[x0][y0]=1;
        f[x0][y0]=f[x][y]+a[x0][y0]; //更新答案 
        if (a[x0][y0]) q.push_back(make_pair(x0, y0)); //有草堆压到队尾 
        else q.push_front(make_pair(x0, y0)); //没草堆压到队首，优先更新其他点  
    }
}
```
**核心思想**：与01 BFS类似，利用双端队列特性，优先处理无干草堆的点。

#### soy_un_perro（优先队列BFS）
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
**核心思想**：以移动的干草数为第一关键字构建小根堆，每次取出堆顶元素进行扩展，直到到达原点。

### 最优关键思路或技巧
- **01 BFS和双端队列BFS**：对于边权只有0和1的最短路问题，利用双端队列的特性，将边权为0的点优先处理，保证队列中节点答案的单调性，可优化时间复杂度。
- **优先队列BFS**：以移动的干草数为关键字构建小根堆，借助贪心思想，每次取出堆顶元素进行扩展，可快速找到最优解。

### 可拓展之处
同类型题或类似算法套路：
- **边权只有0和1的最短路问题**：如迷宫问题，某些路径可以免费通过，某些路径需要消耗一定代价，可使用01 BFS求解。
- **带权图的最短路问题**：可使用Dijkstra、SPFA等算法求解，注意处理负权边的情况。

### 推荐题目
- [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)：考察最短路算法和路径计数。
- [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)：Dijkstra和SPFA算法的模板题。
- [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)：Dijkstra算法的模板题，数据范围更大。

### 个人心得总结
- **一只书虫仔**：通过教练给的思路和代码进行研究学习，加深对01 BFS的理解。
- **_Atyou**：强调了草堆范围外的处理细节，避免数组越界，在实际编程中要注意边界条件的处理。

---
处理用时：49.54秒