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
这些题解主要围绕确定奶牛排名的问题展开，解题关键在于明确每头奶牛与其他奶牛的胜负关系。大部分题解采用 Floyd 算法，利用其传递性来推导所有奶牛间的关系；部分题解使用 DFS 或拓扑排序等方法。

Floyd 算法通过三重循环更新任意两点间的连通性，能高效处理传递关系。DFS 则通过深度优先搜索来统计每头奶牛能赢或输的奶牛数量。拓扑排序结合暴力枚举或栈的操作来确定排名。

### 所选题解
- **作者：xun薰（5星）**
    - **关键亮点**：思路清晰，直接点明 Floyd 算法不仅能求最短路，还能判断点与点的可达性，代码简洁易懂。
    - **核心代码**：
```cpp
for(int k=1;k<=n;k++)
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            f[i][j]=f[i][j]|f[i][k]&f[k][j];
for(int i=1;i<=n;i++){
    int gg=1;
    for(int j=1;j<=n;j++)
        if(i==j)continue;
        else gg=gg&(f[i][j]|f[j][i]);
    ans+=gg;
}
```
    - **核心思想**：先使用 Floyd 算法更新每头奶牛之间的胜负关系，然后检查每头奶牛与其他奶牛的关系是否都已确定，若确定则排名可确定。

- **作者：Believe_R_（4星）**
    - **关键亮点**：详细解释了 Floyd 算法在此题中的应用，即判断图的连通性，还提醒了运算符优先级问题。
    - **核心代码**：
```cpp
for(int k=1;k<=n;++k)
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            f[i][j]=f[i][j] || f[i][k] && f[k][j];
for(int i=1;i<=n;++i){
    int a=1;
    for(int j=1;j<=n;++j){
        if(i==j) continue;
        else a=a && (f[i][j] || f[j][i]);
    }
    ans+=a;
}
```
    - **核心思想**：同样利用 Floyd 算法更新连通性，通过遍历判断每头奶牛与其他奶牛的连通关系是否都已明确，若明确则排名可确定。

- **作者：lixiao189（4星）**
    - **关键亮点**：采用 DFS 方法，思路独特，通过两个图分别存储输赢关系，清晰地解决了间接输赢的问题。
    - **核心代码**：
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
    - **核心思想**：对每头奶牛分别进行赢和输的 DFS 遍历，统计赢和输的奶牛数量，若两者之和等于 `n - 1`，则该奶牛排名可确定。

### 最优关键思路或技巧
- **Floyd 算法**：利用其传递性，通过三重循环更新任意两点间的连通性，高效推导所有奶牛间的胜负关系。
- **DFS 方法**：使用两个图分别存储输赢关系，能清晰处理间接输赢问题。

### 拓展思路
同类型题可考虑增加更多约束条件，如比赛轮次限制、奶牛分组等。类似算法套路可应用于其他具有传递关系的问题，如食物链、等级关系判断等。

### 推荐题目
1. [P1119 灾后重建](https://www.luogu.com.cn/problem/P1119)：考察 Floyd 算法在动态图中的应用。
2. [P2910 [USACO08OPEN]Clear And Present Danger S](https://www.luogu.com.cn/problem/P2910)：涉及 Floyd 算法和路径规划。
3. [P1341 无序字母对](https://www.luogu.com.cn/problem/P1341)：可使用图论和欧拉路径相关知识，与本题图的思想有一定关联。

### 个人心得摘录与总结
- **Believe_R_**：提到从“拓扑排序”过来，但发现本题更适合用 Floyd 算法，提醒注意运算符优先级。总结为做题时要根据题目特点选择合适算法，同时注意细节。
- **塔罗兰**：表示刚开始以为是拓扑排序，实际用 DFS 解决，还介绍了卡常技巧。总结为解题思路可能与直觉不同，可尝试不同方法，同时掌握一些优化技巧。 

---
处理用时：37.98秒