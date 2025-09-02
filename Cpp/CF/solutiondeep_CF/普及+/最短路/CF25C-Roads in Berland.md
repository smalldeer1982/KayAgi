# 题目信息

# Roads in Berland

## 题目描述

There are $ n $ cities numbered from 1 to $ n $ in Berland. Some of them are connected by two-way roads. Each road has its own length — an integer number from 1 to 1000. It is known that from each city it is possible to get to any other city by existing roads. Also for each pair of cities it is known the shortest distance between them. Berland Government plans to build $ k $ new roads. For each of the planned road it is known its length, and what cities it will connect. To control the correctness of the construction of new roads, after the opening of another road Berland government wants to check the sum of the shortest distances between all pairs of cities. Help them — for a given matrix of shortest distances on the old roads and plans of all new roads, find out how the sum of the shortest distances between all pairs of cities changes after construction of each road.

## 样例 #1

### 输入

```
2
0 5
5 0
1
1 2 3
```

### 输出

```
3 ```

## 样例 #2

### 输入

```
3
0 4 5
4 0 9
5 9 0
2
2 3 8
1 2 1
```

### 输出

```
17 12 ```

# AI分析结果

### 题目翻译
# 伯兰的道路

## 题目描述
在伯兰有 $n$ 个从 1 到 $n$ 编号的城市。其中一些城市由双向道路相连。每条道路都有自己的长度——一个 1 到 1000 之间的整数。已知从每个城市都可以通过现有的道路到达其他任何城市。此外，对于每一对城市，都知道它们之间的最短距离。伯兰政府计划修建 $k$ 条新道路。对于每条计划修建的道路，都知道它的长度以及它将连接哪两个城市。为了控制新道路建设的正确性，在每开通一条新道路后，伯兰政府希望检查所有城市对之间最短距离的总和。请帮助他们——根据旧道路上的最短距离矩阵和所有新道路的规划，找出在每条道路建成后，所有城市对之间最短距离的总和如何变化。

## 样例 #1
### 输入
```
2
0 5
5 0
1
1 2 3
```
### 输出
```
3
```

## 样例 #2
### 输入
```
3
0 4 5
4 0 9
5 9 0
2
2 3 8
1 2 1
```
### 输出
```
17 12
```

### 综合分析与结论
- **思路对比**：所有题解都采用 Floyd 算法解决问题，因为题目要求计算所有点对之间的最短路径和，且点数较少（$n\leq300$），Floyd 适合求解多源最短路。不同题解在处理新边加入时略有差异，但核心都是当新边长度小于原最短距离时，更新相关点对的最短距离。
- **算法要点**：
    - 初始化：读取原最短距离矩阵。
    - 新边处理：若新边更短，则更新相关点对的最短距离。
    - 求和：计算所有点对最短距离的总和。
- **解决难点**：
    - **时间复杂度**：避免 $O(n^4)$ 的超时算法，通过只更新与新边端点相关的路径，将时间复杂度优化到 $O(n^3)$。
    - **重复计算**：在求和时，注意避免同一条边被重复计算，一般通过除以 2 来处理。

### 高评分题解
- **作者：Suiseiseki（5 星）**
    - **关键亮点**：思路清晰，代码简洁，有小优化（当能够更新时才做 Floyd 操作），对结果的处理（用 long long 存储并除以 2）有明确注释。
    - **核心代码**：
```cpp
if(mp[a][b]>c){
    mp[a][b]=mp[b][a]=c;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i==j){
                continue;
            }
            mp[i][j]=mp[j][i]=mn(mp[i][j],mp[i][a]+mp[a][j]);
            mp[i][j]=mp[j][i]=mn(mp[i][j],mp[i][b]+mp[b][j]);
        }
    }
}
for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
        sum+=mp[i][j];
    }
}
printf("%I64d ",sum>>1);
```
核心思想：当新边更短时，更新矩阵中相关点对的最短距离，然后重新计算所有点对的最短距离总和并输出。

- **作者：dzz1537568241（4 星）**
    - **关键亮点**：详细解释了 Floyd 算法的原理和本题使用 Floyd 的原因，对 Floyd 算法的理解有独特的比喻，代码结构清晰。
    - **核心代码**：
```cpp
if(a[t1][t2] > t3){
    int k = t1;
    a[t1][t2] = t3;
    a[t2][t1] = t3;
    k = t1;
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            if(i == j)continue;
            a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
            a[j][i] = a[i][j];
        }
    }
    k = t2;
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            if(i == j)continue;
            a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
            a[j][i] = a[i][j];
        }
    }
}
ans = 0;
for(int i = 1; i <= N; i++){
    for(int j = 1; j <= N; j++){
        ans += a[i][j];
    }
}
p[kkk] = ans/2;
```
核心思想：当新边更短时，分别以新边的两个端点为中间点更新最短距离矩阵，然后计算总和并存储结果。

- **作者：szbszb（4 星）**
    - **关键亮点**：指出类似题目，对答案的初始化有详细说明，避免了第一条新边更长时输出错误的问题，代码简洁易懂。
    - **核心代码**：
```cpp
if (p[x][y]<=l){
    printf("%lld ",ans);
    continue;
}
p[x][y]=l;
p[y][x]=l;
for (i=1;i<=n;i++)
    for (j=1;j<=n;j++)
        if (i!=j)
        {
            p[i][j]=min(p[i][j],p[i][x]+p[x][j]);
            p[i][j]=min(p[i][j],p[i][y]+p[y][j]);
        }
ans=0;
for (i=1;i<=n;i++)
    for (j=i+1;j<=n;j++)
        ans+=p[i][j];
printf("%lld ",ans);
```
核心思想：若新边更短，更新矩阵中相关点对的最短距离，重新计算总和并输出；若新边更长，直接输出当前总和。

### 最优关键思路或技巧
- **算法选择**：根据题目要求（多源最短路）和数据范围（$n\leq300$），选择 Floyd 算法。
- **时间优化**：每次只更新与新边端点相关的路径，避免 $O(n^4)$ 的超时算法。
- **结果处理**：用 long long 存储结果，避免溢出，同时注意避免同一条边被重复计算。

### 拓展思路
同类型题或类似算法套路：
- 加点问题：如 [P1119 灾后重建](https://www.luogu.org/problem/P1119)，与本题类似，只是一个是加边，一个是加点。
- 动态规划思想：Floyd 算法本质上是动态规划，可用于解决其他具有最优子结构和重叠子问题的问题。

### 洛谷相似题目推荐
- [P1119 灾后重建](https://www.luogu.org/problem/P1119)
- [P2910 [USACO08OPEN]Clear And Present Danger S](https://www.luogu.org/problem/P2910)
- [P1744 采购特价商品](https://www.luogu.org/problem/P1744)

### 个人心得摘录与总结
- **作者：PrincessYR✨～**：一开始用 Dijkstra 算法卡了一个小时，后来发现正解是 Floyd 算法。总结是要根据题目要求（全源最短路）和数据范围选择合适的算法，Dijkstra 适合单源最短路，Floyd 适合多源最短路。

---
处理用时：40.23秒