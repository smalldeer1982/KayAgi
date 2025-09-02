# 题目信息

# Reposts

## 题目描述

One day Polycarp published a funny picture in a social network making a poll about the color of his handle. Many of his friends started reposting Polycarp's joke to their news feed. Some of them reposted the reposts and so on.

These events are given as a sequence of strings "name1 reposted name2", where name1 is the name of the person who reposted the joke, and name2 is the name of the person from whose news feed the joke was reposted. It is guaranteed that for each string "name1 reposted name2" user "name1" didn't have the joke in his feed yet, and "name2" already had it in his feed by the moment of repost. Polycarp was registered as "Polycarp" and initially the joke was only in his feed.

Polycarp measures the popularity of the joke as the length of the largest repost chain. Print the popularity of Polycarp's joke.

## 样例 #1

### 输入

```
5
tourist reposted Polycarp
Petr reposted Tourist
WJMZBMR reposted Petr
sdya reposted wjmzbmr
vepifanov reposted sdya
```

### 输出

```
6
```

## 样例 #2

### 输入

```
6
Mike reposted Polycarp
Max reposted Polycarp
EveryOne reposted Polycarp
111 reposted Polycarp
VkCup reposted Polycarp
Codeforces reposted Polycarp
```

### 输出

```
2
```

## 样例 #3

### 输入

```
1
SoMeStRaNgEgUe reposted PoLyCaRp
```

### 输出

```
2
```

# AI分析结果

### 题目中文重写
## 转发

### 题目描述
有一天，波利亚尔普（Polycarp）在社交网络上发布了一张有趣的图片，并发起了一个关于他的手柄颜色的投票。他的许多朋友开始将波利亚尔普的笑话转发到他们的动态中。其中一些人又转发了这些转发内容，以此类推。

这些事件以字符串 “name1 reposted name2” 的序列形式给出，其中 name1 是转发笑话的人的名字，name2 是笑话从其动态中被转发的人的名字。保证对于每个字符串 “name1 reposted name2”，用户 “name1” 的动态中之前没有这个笑话，而 “name2” 在转发时其动态中已经有了这个笑话。波利亚尔普注册名为 “Polycarp”，最初这个笑话只在他的动态中。

波利亚尔普将这个笑话的受欢迎程度定义为最长转发链的长度。请打印出波利亚尔普的笑话的受欢迎程度。

### 样例 #1
#### 输入
```
5
tourist reposted Polycarp
Petr reposted Tourist
WJMZBMR reposted Petr
sdya reposted wjmzbmr
vepifanov reposted sdya
```
#### 输出
```
6
```

### 样例 #2
#### 输入
```
6
Mike reposted Polycarp
Max reposted Polycarp
EveryOne reposted Polycarp
111 reposted Polycarp
VkCup reposted Polycarp
Codeforces reposted Polycarp
```
#### 输出
```
2
```

### 样例 #3
#### 输入
```
1
SoMeStRaNgEgUe reposted PoLyCaRp
```
#### 输出
```
2
```

### 综合分析与结论
- **思路对比**：
    - 封禁用户：使用 Dijkstra 算法，将字符串通过 `map` 映射为数字编号的顶点，构建图后求最长路径。
    - _FILARET_：运用弗洛伊德（Floyd）算法，同样借助 `map` 处理字符串，通过邻接矩阵存储图，进行松弛操作求最长路径。
    - long_long：通过简单的逻辑判断，根据输入的名字关系更新转发链长度，记录最大值。
    - ifyml：把字符串映射为数字，构建邻接矩阵，使用 Floyd 算法找出路径并求最大值。
    - Southern_Dynasty：利用题目中转发的性质，构建内向树森林，求内向树的最大深度。
- **算法要点**：
    - 封禁用户：Dijkstra 算法求最长路径，`map` 映射字符串。
    - _FILARET_：Floyd 算法求最长路径，`map` 映射字符串，邻接矩阵存储图。
    - long_long：简单的逻辑判断和更新。
    - ifyml：Floyd 算法求最长路径，`map` 映射字符串，邻接矩阵存储图。
    - Southern_Dynasty：构建内向树森林，求内向树最大深度，`gp_hash_table` 处理字符串。
- **解决难点**：
    - 主要难点在于字符串的处理，各题解都使用了不同的数据结构（如 `map`、`gp_hash_table`）将字符串映射为数字。另外，对于图的构建和最长路径的求解，不同题解采用了不同的算法。

### 题解评分
- 封禁用户：4 星。思路清晰，代码实现完整，使用 Dijkstra 算法解决问题，有详细的注释。
- _FILARET_：3 星。对 Floyd 算法的原理有一定解释，但代码中存在一些多余的注释和调试代码，影响可读性。
- long_long：2 星。思路简单，但逻辑存在缺陷，没有考虑到复杂的转发关系。
- ifyml：3 星。代码实现基本正确，但存在一些小问题，如注释不够详细。
- Southern_Dynasty：3 星。思路独特，但只给出了代码链接，没有具体代码实现。

### 所选题解
- 封禁用户（4 星）
    - **关键亮点**：使用 Dijkstra 算法求最长路径，通过 `map` 映射字符串，代码实现完整，注释详细。
    - **重点代码**：
```cpp
inline void dijkstra(int s)
{
    priority_queue<P,vector<P>,greater<P> >q;
    for(register int i=1;i<=n;i++) d[i]=1e9;
    d[s]=0;
    q.push(P{0,s});
    while(!q.empty())
    {
        P p=q.top();
        q.pop();
        int v=p.second;
        if(d[v]<p.first) continue;
        for(register int i=0;i<G[v].size();i++)
        {
            edge e=G[v][i];
            if(d[e.to]>d[v]+e.cost)
            {
                d[e.to]=d[v]+e.cost;
                q.push(P{d[e.to],e.to});
            }
        }
    }
    for(register int i=1;i<=n;i++) if(d[i]!=1e9&&ans<d[i]) ans=d[i]; 
    printf("%d\n",ans+1);
    return;
}
```
核心实现思想：使用优先队列优化的 Dijkstra 算法，从起点开始，不断更新到其他顶点的最短距离，最后找出最大距离。

### 最优关键思路或技巧
- 使用 `map` 或 `gp_hash_table` 等数据结构将字符串映射为数字，方便处理图的顶点。
- 对于图的最长路径问题，可以使用 Dijkstra 或 Floyd 等算法求解。

### 可拓展之处
同类型题或类似算法套路：
- 社交网络中的信息传播问题，如病毒传播路径、谣言传播范围等。
- 图的遍历和路径搜索问题，如最短路径、最长路径、连通分量等。

### 洛谷题目推荐
- P1119 灾后重建（Floyd 算法）
- P3371 单源最短路径（Dijkstra 算法）
- P2850 [USACO06DEC]Wormholes G（图的负环判断）

### 个人心得摘录与总结
封禁用户提到在进行连边操作之前，要先将名字的每个字符都设为小写，这是一个容易忽略的细节，需要注意输入数据的大小写问题。 

---
处理用时：47.45秒