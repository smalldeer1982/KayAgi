# 题目信息

# Planets

## 题目描述

## 题面
在宇宙里有 $n$  个星球，分别编号为 $1,2,...,n$  。Jack现在在 $1$  号星球上，他要去 $n$  号星球。已知一些星球之间有双向的传送通道，Jack可以通过这些传送通道移动。每次传送需要一些时间，在不同的星球之间传送也可能需要不同时间。

当有其他人在使用这个星球的传送通道时，Jack无法离开这个星球。比如，如果有人在 $t$  时刻使用通道，那Jack只能在 $t+1$  时刻离开（如果t+1时刻没有人在使用通道）。

现在，Jack想请你计算他最早可以在哪个时刻到达 $n$  号星球。Jack在0时刻出发。

## 样例 #1

### 输入

```
4 6
1 2 2
1 3 3
1 4 8
2 3 4
2 4 5
3 4 3
0
1 3
2 3 4
0
```

### 输出

```
7
```

## 样例 #2

### 输入

```
3 1
1 2 3
0
1 3
0
```

### 输出

```
-1
```

# AI分析结果

### 题解综合分析与结论
本题是一个带有时间限制的最短路问题，核心在于处理每个星球在某些时刻传送通道被占用的情况。各题解的主要思路都是在经典最短路算法（SPFA、Dijkstra）基础上，增加对时间限制的判断。

#### 思路对比
- **雨季、wangyibo201026、_Fontainebleau_、Prurite**：使用SPFA算法，通过map记录每个星球不能出发的时刻，在松弛操作前检查当前时间是否可用，不可用则等待。
- **FreeTimeLove、ljk_Elaina、lzyqwq、happy_dengziyue、wfycsw、__Hacheylight__**：采用Dijkstra算法，其中FreeTimeLove用vector存储不能出发的时间并二分查找，其他题解用set或map记录限制。

#### 算法要点
- **SPFA**：利用队列不断更新最短路径，时间复杂度在稀疏图中接近$O(m)$，但可能会被特殊数据卡TLE。
- **Dijkstra**：使用优先队列（堆）优化，每次取出距离最小的点进行松弛，时间复杂度为$O((n + m)logn)$。

#### 解决难点
- **时间限制处理**：使用map、set、vector等数据结构记录每个星球不能出发的时刻，在松弛操作前检查并等待。
- **INF取值**：由于答案可能接近int上限，需要将INF设为足够大的值（如2e9）。

### 高评分题解
1. **雨季（5星）**
    - **关键亮点**：思路清晰，代码注释详细，对可能出现的TLE和INF取值问题进行了提示。
    - **个人心得**：指出INF赋值1e9不够大，应赋2e9；计算等待时间的代码要放在循环外，否则会TLE。
    - **核心代码**：
```cpp
while(!q.empty()) {
    x=q.front();
    q.pop_front();
    vis[x]=0;
    d=dis[x];
    while(mp[x][d]) d++;
    for(int i=h[x];i;i=e[i].nex) {
        xx=e[i].v;
        if(dis[xx]>d+e[i].c) {
            dis[xx]=d+e[i].c;
            if(!vis[xx]) {
                vis[xx]=1;
                if(q.empty()||dis[xx]>dis[q.front()]) q.push_back(xx);
                else q.push_front(xx);
            }
        }
    }
}
```
核心思想：在SPFA算法的基础上，每次取出队首元素后，计算该点的出发时间（跳过被占用的时间），然后进行松弛操作。

2. **FreeTimeLove（4星）**
    - **关键亮点**：提供了不用map/set的Dijkstra做法，使用vector存储不能出发的时间并二分查找，避免了map的常数开销。
    - **核心代码**：
```cpp
int qry(int u,int ti){//出发时间 
    int l=1,r=k[u]+1,mid;
    if(l==r)return ti;
    while(l<r){
        mid=(l+r)>>1;
        if(t[u][mid]<ti)
            l=mid+1;
        else
            r=mid;
    }
    if(t[u][l]>ti)return ti;
    while(l++<=k[u])
        if(t[u][l-1]+1<t[u][l])
            return t[u][l-1]+1;
}
```
核心思想：通过二分查找找到第一个大于等于当前时间的不能出发时间，若当前时间可用则直接返回，否则往后找相邻两个不能出发时间的间隔，返回间隔中的最小值。

3. **ljk_Elaina（4星）**
    - **关键亮点**：使用Dijkstra算法，代码简洁，对优先队列的使用和可能出现的TLE问题进行了详细说明。
    - **个人心得**：指出maxtime用1e9不够，至少1e9 + 1e5；代码中`if(dist[cur]!=w) continue;`若不写可能会TLE；优先队列压入负值可使绝对值小的先出队，忘写负号会TLE。
    - **核心代码**：
```cpp
while(!q.empty()){
    int cur=q.top().f;
    int w=-q.top().se;
    q.pop();
    if(dist[cur]!=w) continue;
    while(s[cur].count(w)) w++;
    for(int i=0;i<ed[cur].size();i++){
        int to=ed[cur][i].f;
        int w1=ed[cur][i].se;
        if(dist[to]>w+w1){
            dist[to]=w+w1;
            q.push(mp(to,-dist[to]));
        }
    }
}
```
核心思想：在Dijkstra算法中，每次取出队首元素后，检查该点是否已被松弛，若未被松弛则计算出发时间（跳过被占用的时间），然后进行松弛操作。

### 最优关键思路或技巧
- **数据结构选择**：使用map、set、vector等数据结构记录每个星球不能出发的时刻，避免使用二维数组导致MLE。
- **二分查找**：在查找第一个大于等于当前时间的不能出发时间时，使用二分查找可以将时间复杂度从$O(n)$降低到$O(logn)$。
- **INF取值**：将INF设为足够大的值（如2e9），避免答案接近int上限时出现错误。

### 可拓展之处
同类型题可能会增加更多的限制条件，如不同星球的等待规则不同、传送通道有使用次数限制等。类似算法套路可用于解决带有时间、资源等限制的路径规划问题，关键在于在经典算法基础上增加对限制条件的处理。

### 洛谷相似题目推荐
1. [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)：经典的单源最短路径问题，可用于练习Dijkstra和SPFA算法。
2. [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)：同样是单源最短路径问题，但数据范围更大，需要使用堆优化的Dijkstra算法。
3. [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)：在最短路的基础上，要求统计最短路径的数量，可加深对最短路算法的理解。

---
处理用时：40.69秒