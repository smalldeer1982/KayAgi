# 题目信息

# Unbearable Controversy of Being

## 题目描述

Tomash keeps wandering off and getting lost while he is walking along the streets of Berland. It's no surprise! In his home town, for any pair of intersections there is exactly one way to walk from one intersection to the other one. The capital of Berland is very different!

Tomash has noticed that even simple cases of ambiguity confuse him. So, when he sees a group of four distinct intersections $ a $ , $ b $ , $ c $ and $ d $ , such that there are two paths from $ a $ to $ c $ — one through $ b $ and the other one through $ d $ , he calls the group a "damn rhombus". Note that pairs $ (a,b) $ , $ (b,c) $ , $ (a,d) $ , $ (d,c) $ should be directly connected by the roads. Schematically, a damn rhombus is shown on the figure below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF489D/8b5a60981c3e3bd62ad47b07d6098988071c0c74.png)Other roads between any of the intersections don't make the rhombus any more appealing to Tomash, so the four intersections remain a "damn rhombus" for him.

Given that the capital of Berland has $ n $ intersections and $ m $ roads and all roads are unidirectional and are known in advance, find the number of "damn rhombi" in the city.

When rhombi are compared, the order of intersections $ b $ and $ d $ doesn't matter.

## 样例 #1

### 输入

```
5 4
1 2
2 3
1 4
4 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4 12
1 2
1 3
1 4
2 1
2 3
2 4
3 1
3 2
3 4
4 1
4 2
4 3
```

### 输出

```
12
```

# AI分析结果

### 题目内容
# 存在的难以忍受的争议

## 题目描述
托马什在贝兰德的街道上行走时，总是会走神并迷路。这并不奇怪！在他的家乡，对于任意一对十字路口，从一个十字路口走到另一个十字路口都只有一种方式。而贝兰德的首都却大不相同！

托马什注意到，即使是简单的歧义情况也会让他感到困惑。所以，当他看到一组四个不同的十字路口 \(a\)、\(b\)、\(c\) 和 \(d\)，使得从 \(a\) 到 \(c\) 有两条路径 —— 一条经过 \(b\)，另一条经过 \(d\)，他就把这组路口称为“可恶的菱形”。注意，\((a,b)\)、\((b,c)\)、\((a,d)\)、\((d,c)\) 这几对路口应该由道路直接相连。示意性地，一个可恶的菱形如下图所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF489D/8b5a60981c3e3bd62ad47b07d6098988071c0c74.png)
其他路口之间的道路并不会让这个菱形对托马什更有吸引力，所以这四个路口对他来说仍然是一个“可恶的菱形”。

已知贝兰德的首都有 \(n\) 个十字路口和 \(m\) 条道路，且所有道路都是单向的并且预先已知，求城市中“可恶的菱形”的数量。

在比较菱形时，路口 \(b\) 和 \(d\) 的顺序无关紧要。

## 样例 #1
### 输入
```
5 4
1 2
2 3
1 4
4 3
```
### 输出
```
1
```

## 样例 #2
### 输入
```
4 12
1 2
1 3
1 4
2 1
2 3
2 4
3 1
3 2
3 4
4 1
4 2
4 3
```
### 输出
```
12
```

### 算法分类
图论

### 综合分析与结论
这些题解的核心思路都是围绕找出从 \(a\) 到 \(c\) 恰经过一个点的路径数量，再通过组合数学计算菱形数量。
 - **思路方面**：多数题解通过枚举点和边来统计路径数，如遍历每个点的出边，再遍历出边到达点的出边，记录满足条件的路径。部分题解从不同角度，如枚举 \(b\)、\(d\) 点对来预处理相关信息。
 - **算法要点**：利用二维数组记录路径数量，通过三重循环实现路径统计，最后两重循环计算菱形数量。
 - **解决难点**：主要难点在于避免重复统计路径和菱形，如通过判断条件过滤掉不合法路径。

### 所选的题解
 - **作者：songhongyi（5星）**
    - **关键亮点**：思路清晰，代码简洁。先通过`vector`存图，再用三重循环统计每两点间恰经过一个点的路径数，最后两重循环计算菱形数量，逻辑连贯。
    - **重点代码**：
```cpp
// 存图
void add_edge( int u, int v )  
{
    edges[ u ].push_back( v );  
}
// 统计路径数
for ( int i = 1; i <= n; i++ )
{
    for ( auto j : edges[ i ] ) 
    {
        for ( auto k : edges[ j ] ) 
        {
            if ( k!= i ) 
            {
                cnt[ i ][ k ]++;  
            }
        }
    }
}
// 计算菱形数量
int ans = 0;
for ( int i = 1; i <= n; i++ )
{
    for ( int j = 1; j <= n; j++ ) 
    {
        ans += cnt[ i ][ j ] * ( cnt[ i ][ j ] - 1 ) / 2; 
    }
}
```
 - **作者：bzzltl（4星）**
    - **关键亮点**：代码使用`vector`存图，通过`read`函数优化输入，整体结构完整，逻辑清晰。
    - **重点代码**：
```cpp
// 读入图
for(int i=1;i<=m;i++)
{
    int u=read(),v=read();
    vec[u].push_back(v);
}
// 统计路径数
for(int u=1;u<=n;u++)
    for(int i=0;i<vec[u].size();i++)
        for(int j=0;j<vec[vec[u][i]].size();j++)
            if(u!=vec[vec[u][i]][j]) mp[u][vec[vec[u][i]][j]]++;
// 计算菱形数量
for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
        ans+=mp[i][j]*(mp[i][j]-1)/2;
```
 - **作者：Mars_Dingdang（4星）**
    - **关键亮点**：提到利用Floyd的思想，通过链式前向星存图，代码结构清晰，对时间复杂度有分析。
    - **重点代码**：
```cpp
// 链式前向星存图
inline void add(int u, int v){
    ver[++tot] = v; nxt[tot] = head[u]; head[u] = tot;
}
// 统计路径数
rep(u, 1, n) 
    for(int i = head[u]; ~i; i = nxt[i]) {
        int v = ver[i];
        for(int j = head[v]; ~j; j = nxt[j]) 
            if(ver[j]!= u) deg[u][ver[j]] ++;
    }
// 计算菱形数量
ll ans = 0;
rep(i, 1, n)
    rep(j, 1, n)
        ans += (deg[i][j] * (deg[i][j] - 1) >> 1);
```

### 最优关键思路或技巧
利用二维数组记录从一个点到另一个点恰经过一个点的路径数量，通过多层循环枚举边和点来实现路径统计，最后利用组合数学公式计算菱形数量。这种方法充分利用了题目数据范围较小的特点，直接通过暴力枚举和简单的数据结构解决问题。

### 可拓展之处
同类型题常出现在图论相关题目中，主要考察对图的结构分析和路径统计。类似套路是通过预处理某些路径信息，再利用组合数学知识计算符合特定条件的子图数量。例如在一些有向无环图中，统计满足特定路径关系的子结构数量。

### 推荐洛谷题目
 - [P1330 封锁阳光大学](https://www.luogu.com.cn/problem/P1330)：图论相关，涉及对图的遍历和节点状态判断。
 - [P2746 [USACO5.3]校园网Network of Schools](https://www.luogu.com.cn/problem/P2746)：通过对有向图的强连通分量分析解决问题，与本题分析图结构的思路类似。
 - [P3387 【模板】缩点](https://www.luogu.com.cn/problem/P3387)：利用缩点算法处理有向图问题，有助于加深对图论算法的理解和应用。

### 个人心得
无

---
处理用时：62.08秒