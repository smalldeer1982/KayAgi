# 题目信息

# [USACO09NOV] Job Hunt S

## 题目描述

Bessie is running out of money and is searching for jobs. Farmer John knows this and wants the cows to travel around so he has imposed a rule that his cows can only make D (1 <= D <= 1,000) dollars in a city before they must work in another city. Bessie can, however, return to a city after working elsewhere for a while and again earn the D dollars maximum in that city. There is no limit on the number of times Bessie can do this.

Bessie's world comprises P (1 <= P <= 150) one-way paths connecting C (2 <= C <= 220) cities conveniently numbered 1..C. Bessie is currently in city S (1 <= S <= C). Path i runs one-way from city A\_i to city B\_i (1 <= A\_i <= C; 1 <= B\_i <= C) and costs nothing to traverse.

To help Bessie, Farmer John will give her access to his private jet service. This service features F (1 <= F <= 350) routes, each of which is a one way flight from one city J\_i to a another K\_i (1 <= J\_i <= C; 1 <= K\_i <= C) and which costs T\_i (1 <= T\_i <= 50,000) dollars. Bessie can pay for the tickets from future earnings if she doesn't have the cash on hand.

Bessie can opt to retire whenever and wherever she wants. Given an unlimited amount of time, what is the most money that Bessie can make presuming she can make the full D dollars in each city she can travel to?  Print -1 if there is no limit to this amount.

奶牛们正在找工作。农场主约翰知道后，鼓励奶牛们四处碰碰运气。而且他还加了一条要求：一头牛在一个城市最多只能赚D（1≤D≤1000）美元，然后它必须到另一座城市工作。当然，它可以在别处工作一阵子后又回到原来的城市再最多赚D美元。而且这样的往返次数没有限制。

城市间有P（1≤P≤150）条单向路径连接，共有C（2≤C≤220）座城市，编号从1到C。奶牛贝茜当前处在城市S（1≤S≤C）。路径i从城市A\_i到城市B\_i（1≤A\_i≤C，1≤B\_i≤C），在路径上行走不用任何花费。

为了帮助贝茜，约翰让它使用他的私人飞机服务。这项服务有F条（1≤F≤350）单向航线，每条航线是从城市J\_i飞到另一座城市K\_i（1≤J\_i≤C，1≤K\_i≤C），费用是T\_i（1≤T\_i≤50000）美元。如果贝茜手中没有现钱，可以用以后赚的钱来付机票钱。

贝茜可以选择在任何时候，在任何城市退休。如果在工作时间上不做限制，贝茜总共可以赚多少钱呢？如果赚的钱也不会出现限制，就输出-1。


## 说明/提示

This world has five cities, three paths and two jet routes. Bessie starts out in city 1, and she can only make 100 dollars in each city before moving on.


Bessie can travel from city 1 to city 5 to city 2 to city 3, and make a total of 4\*100 - 150 = 250 dollars.


Source: USACO 2009 November Silver

这个世界上有五个城市，三条单向路径和两条单向航线。贝茜从一号城市开始她的旅行，她在离开一个城市前最多只能在这个城市赚100美元。


贝茜可以通过从一号城市-->五号城市-->二号城市-->三号城市的旅行赚到4\*100-150=250美元。


(注:在四个城市各赚100美元,从五号城市飞到二号城市花掉150美元)


来源:USACO 2009 十一月银组


## 样例 #1

### 输入

```
100 3 5 2 1
1 5
2 3
1 4
5 2 150
2 5 120
```

### 输出

```
250```

# AI分析结果



### 综合分析与结论  
本题核心在于将点权转化为边权，构建图后求最长路径。若存在正权环则输出-1。关键难点在于建模（点权→边权）和算法选择（SPFA/Bellman-Ford处理最长路及正环检测）。以下题解展示了不同实现方式，均围绕这两个核心展开。

---

### 高星题解推荐  

#### 1. 题解作者：Believe_R_（⭐️⭐️⭐️⭐️）  
**关键亮点**  
- 清晰阐述点权转边权的核心思想，将普通路径边权设为`D`，飞行路径边权设为`D-T_i`。  
- 使用SPFA算法求最长路，通过节点入队次数检测正环，逻辑简洁。  
**代码核心**  
```cpp
void Spfa() {
    queue<int> q;
    q.push(s);
    w[s] = d; vis[s] = 1; cnt[s]++;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        vis[u] = 0;
        if (++cnt[u] > n) { printf("-1\n"); exit(0); } // 正环检测
        for (int i = head[u]; i; i = nex[i]) {
            int v = to[i];
            if (w[v] < w[u] + dis[i]) { // 松弛条件改为求最大
                w[v] = w[u] + dis[i];
                if (!vis[v]) q.push(v), vis[v] = 1;
            }
        }
    }
}
```

#### 2. 题解作者：TOM_闫（⭐️⭐️⭐️⭐️）  
**关键亮点**  
- 通过边权取反将最长路转化为最短路，使用Bellman-Ford实现，代码简洁易懂。  
- 处理负权边和环的思路清晰，适合算法初学者理解。  
**代码核心**  
```cpp
for (int i = 1; i < c; i++) { // Bellman-Ford松弛
    bool updated = false;
    for (int j = 1; j <= p + f; j++) {
        Edge &e = edges[j];
        if (dis[e.to] > dis[e.from] + e.w) {
            dis[e.to] = dis[e.from] + e.w;
            updated = true;
        }
    }
    if (!updated) break;
}
```

#### 3. 题解作者：Dawn_Sdy（⭐️⭐️⭐️⭐️）  
**关键亮点**  
- 明确点权和边权的转换逻辑，直接使用SPFA求最长路。  
- 通过`visn[]`标记当前路径节点，结合`last[]`数组检测正环，实现巧妙。  
**代码核心**  
```cpp
void dfs(int u) {
    for (auto &e : G[u]) {
        if (vis[e.to] && last[u] - last[e.to] + e.w > 0) { // 检测正环
            cout << -1; exit(0);
        }
        if (dis[e.to] < dis[u] + e.w) {
            dis[e.to] = dis[u] + e.w;
            dfs(e.to);
        }
    }
}
```

---

### 最优思路总结  
1. **建模技巧**：将点权`D`转化为边权，普通路径边权为`D`，飞行路径边权为`D-T_i`。  
2. **算法选择**：  
   - SPFA：通过队列动态松弛，检测节点入队次数超过`C`次判定正环。  
   - Bellman-Ford：边权取反后求最短路，适用于小规模数据。  
3. **关键优化**：在松弛条件中维护最大值而非最小值，适应最长路场景。  

---

### 相似题目推荐  
1. [P1807 最长路](https://www.luogu.com.cn/problem/P1807) - 最长路模板题。  
2. [P2648 赚钱](https://www.luogu.com.cn/problem/P2648) - 含超级源点的最长路问题。  
3. [P1938 [USACO09NOV]Job Hunt S](https://www.luogu.com.cn/problem/P1938) - 本题的双倍经验。

---
处理用时：63.18秒