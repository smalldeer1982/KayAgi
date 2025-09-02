# 题目信息

# [USACO08JAN] Cow Contest S

## 题目描述

$ N (1 ≤ N ≤ 100) $ cows, conveniently numbered $ 1 ~ N $ , are participating in a programming contest. As we all know, some cows code better than others. Each cow has a certain constant skill rating that is unique among the competitors.

The contest is conducted in several head-to-head rounds, each between two cows. If cow $ A $ has a greater skill level than cow $ B (1 ≤ A ≤ N; 1 ≤ B ≤ N; A ≠ B) $, then cow $ A $ will always beat cow $ B $ .

Farmer John is trying to rank the cows by skill level. Given a list the results of $ M (1 ≤ M ≤ 4,500) $ two-cow rounds, determine the number of cows whose ranks can be precisely determined from the results. It is guaranteed that the results of the rounds will not be contradictory.

FJ的 $N$（$1 \leq N \leq 100$）头奶牛们最近参加了场程序设计竞赛。在赛场上，奶牛们按 $1, 2, \cdots, N$ 依次编号。每头奶牛的编程能力不尽相同，并且没有哪两头奶牛的水平不相上下，也就是说，奶牛们的编程能力有明确的排名。 整个比赛被分成了若干轮，每一轮是两头指定编号的奶牛的对决。如果编号为 $A$ 的奶牛的编程能力强于编号为 $B$ 的奶牛 （$1 \leq A, B \leq N$，$A \neq B$)，那么她们的对决中，编号为 $A$ 的奶牛总是能胜出。 FJ 想知道奶牛们编程能力的具体排名，于是他找来了奶牛们所有 $M$（$1 \leq M \leq 4,500$）轮比赛的结果，希望你能根据这些信息，推断出尽可能多的奶牛的编程能力排名。比赛结果保证不会自相矛盾。

## 说明/提示

样例解释：

编号为 $2$ 的奶牛输给了编号为 $1, 3, 4$ 的奶牛，也就是说她的水平比这 $3$ 头奶牛都差。而编号为 $5$ 的奶牛又输在了她的手下，也就是说，她的水平比编号为 $5$ 的奶牛强一些。于是，编号为 $2$ 的奶牛的排名必然为第 $4$，编号为 $5$ 的奶牛的水平必然最差。其他 $3$ 头奶牛的排名仍无法确定。

## 样例 #1

### 输入

```
5 5
4 3
4 2
3 2
1 2
2 5```

### 输出

```
2
```

# AI分析结果

### 综合分析与结论
这些题解主要围绕如何确定奶牛排名展开，核心在于判断每头奶牛与其他奶牛的胜负关系是否完全确定。主要涉及Floyd算法、DFS、拓扑排序等方法。
1. **Floyd算法**：利用Floyd算法不仅能求最短路，还能判断图的连通性这一特性。通过`f[i][j] = f[i][j] | (f[i][k] & f[k][j])`更新每两点间的关系，若某点与其余n - 1个点的关系都确定，则其排名可确定。
2. **DFS方法**：构建正反两个图分别存储输赢关系，从每个点出发进行DFS遍历，统计赢的和输的奶牛数量，若两者之和为n - 1，则该奶牛排名可确定。
3. **拓扑排序**：有通过多次拓扑排序判断某点在不同拓扑序列中位置是否不变来确定其排名；也有结合拓扑排序与其他方法来确定点与点之间的胜负关系。

从质量上看，部分题解思路清晰、代码简洁且有注释辅助理解，部分题解存在代码复杂、思路阐述不够清晰等问题。

### 所选的题解
- **作者：xun薰 (赞：142)  星级：5星**
    - **关键亮点**：思路清晰，直接点明Floyd算法不仅能求最短路还能判断连通性，代码简洁明了，无冗余操作。
    - **重点代码**：
```cpp
for(int k=1;k<=n;k++)
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
          f[i][j]=f[i][j]|f[i][k]&f[k][j];
for(int i=1;i<=n;i++){
    int gg=1;
    for(int j=1;j<=n;j++)
    if(i==j)continue;else 
     gg=gg&(f[i][j]|f[j][i]);
     ans+=gg;
}
```
    - **核心思想**：通过Floyd算法更新每头奶牛与其他奶牛的胜负关系，若某头奶牛与其余所有奶牛的胜负关系都确定（即`f[i][j] | f[j][i]`对所有`j`都成立），则其排名可确定。
- **作者：Believe_R_ (赞：43)  星级：4星**
    - **关键亮点**：详细解释了Floyd算法在此题中的应用，即判断图的连通性，还特别提醒了运算符优先级问题，对初学者友好。
    - **重点代码**：
```cpp
for(int k=1;k<=n;++k)
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
        f[i][j]=f[i][j] || f[i][k] && f[k][j];
for(int i=1;i<=n;++i)
{
    int a=1;
    for(int j=1;j<=n;++j)
    {
        if(i==j) continue;
        else a=a && (f[i][j] || f[j][i]);
    }
    ans+=a;
}
```
    - **核心思想**：与xun薰题解类似，利用Floyd算法判断奶牛间的胜负关系，通过遍历确认每头奶牛与其他奶牛的关系是否都确定，从而确定其排名。
- **作者：lixiao189 (赞：29)  星级：4星**
    - **关键亮点**：采用DFS方法，思路独特，将问题转化为求每头奶牛赢和输的奶牛数量，逻辑清晰。
    - **重点代码**：
```cpp
void dfs_win(int x){
    vector <int> :: iterator it;
    for(it=win_graph[x].begin();it!=win_graph[x].end();it++){
        if(vis_win[*it]==0){
            sum_win++;
            vis_win[*it]=1;
            dfs_win(*it);
        }
    }
}
void dfs_lose(int x){
    vector <int> :: iterator it;
    for(it=lose_graph[x].begin();it!=lose_graph[x].end();it++){
        if(vis_lose[*it]==0){
            sum_lose++;
            vis_lose[*it]=1;
            dfs_lose(*it);
        }
    }
}
for(int i=1;i<=n;i++){
    memset(vis_win,0,sizeof(vis_win));
    memset(vis_lose,0,sizeof(vis_lose));
    sum_win=0;sum_lose=0;
    dfs_win(i);
    dfs_lose(i);
    if(sum_win+sum_lose==n-1) ans++;
}
```
    - **核心思想**：从每头奶牛出发，分别在正向图（赢的关系）和反向图（输的关系）中进行DFS遍历，统计赢和输的奶牛数量，根据数量和是否为n - 1判断该奶牛排名是否可确定。

### 最优关键思路或技巧
1. **利用Floyd算法判断连通性**：通过`f[i][j] = f[i][j] | (f[i][k] & f[k][j])`简洁地更新节点间关系，快速判断每头奶牛与其他奶牛的胜负关系，时间复杂度为$O(n^3)$，适用于本题较小的数据规模。
2. **DFS遍历统计关系**：构建正反图，从每个点DFS遍历统计赢和输的奶牛数量，逻辑直观，代码实现相对简单。

### 可拓展之处
此类题目属于图论中判断节点关系及确定节点状态的问题。类似套路是将实际问题转化为图结构，利用图的连通性、路径等特性解决。同类型题可考虑增加边的权值、改变图的结构（如无向图、有向无环图等）来增加难度。

### 相似知识点洛谷题目
1. **P1119 灾后重建**：涉及Floyd算法在动态图中的应用，根据时间顺序更新图的连通性。
2. **P3382 【模板】三分法**：虽主要考察三分法，但其中可能涉及到类似通过判断关系来确定结果的逻辑思维。
3. **P2831 [NOIP2016 提高组] 愤怒的小鸟**：需要通过分析点与点之间的关系，利用状态压缩动态规划解决，与本题判断奶牛关系有一定相似性。

### 个人心得摘录与总结
部分作者提到最初思路错误，如认为是拓扑排序题，但实际用Floyd算法更合适。这表明在解题时不能仅依赖直觉或题目表面特征，需深入分析题目本质。还有作者强调了运算符优先级问题，提醒在使用位运算等操作时要特别注意，避免因优先级错误导致结果出错。 

---
处理用时：51.40秒