# 题目信息

# [USACO10NOV] Visiting Cows G

## 题目描述

After many weeks of hard work, Bessie is finally getting a vacation! After many weeks of hard work, Bessie is finally getting a vacation!  numbered 1..N. The cows have set up quite an unusual road network with exactly N-1 roads connecting pairs of cows C1 and C2 (1 <= C1 <= N; 1 <= C2 <= N; C1 != C2) in such a way that there exists a unique path of roads between any two cows.

FJ wants Bessie to come back to the farm soon; thus, he has instructed Bessie that if two cows are directly connected by a road, she may not visit them both. Of course, Bessie would like her vacation to be as long as possible, so she would like to determine the maximum number of cows she can visit.

经过了几周的辛苦工作,贝茜终于迎来了一个假期.作为奶牛群中最会社交的牛,她希望去拜访N(1<=N<=50000)个朋友.这些朋友被标号为1..N.这些奶牛有一个不同寻常的交通系统,里面有N-1条路,每条路连接了一对编号为C1和C2的奶牛(1 <= C1 <= N; 1 <= C2 <= N; C1<>C2).这样,在每一对奶牛之间都有一条唯一的通路. FJ希望贝茜尽快的回到农场.于是,他就指示贝茜,如果对于一条路直接相连的两个奶牛,贝茜只能拜访其中的一个.当然,贝茜希望她的假期越长越好,所以她想知道她可以拜访的奶牛的最大数目.


## 说明/提示

Bessie knows 7 cows. Cows 6 and 2 are directly connected by a road, as are cows 3 and 4, cows 2 and 3, etc. The illustration below depicts the roads that connect the cows:

1--2--3--4

|
5--6--7


Bessie can visit four cows. The best combinations include two cows on the top row and two on the bottom. She can't visit cow 6 since that would preclude visiting cows 5 and 7; thus she visits 5 and 7. She can also visit two cows on the top row: {1,3}, {1,4}, or {2,4}.


## 样例 #1

### 输入

```
7 
6 2 
3 4 
2 3 
1 2 
7 6 
5 6 
```

### 输出

```
4 
```

# AI分析结果



### 综合分析与结论
本题是典型的树形DP问题，核心在于求树的最大独立集。所有题解均围绕树形DP展开，状态定义与转移方程高度一致：设 `dp[u][0/1]` 表示选/不选节点u时的最大值，状态转移为选父节点则子节点不可选，不选父节点则子节点可选可不选。关键区别在于代码实现方式（邻接表/链式前向星）和初始化的处理细节。

### 精选题解推荐

#### 1. 作者：sy_zmq_001（★★★★★）
**关键亮点**  
- 详细解释树形DP思想，类比经典问题《没有上司的舞会》。  
- 提供扩展题目（树形背包问题），增强举一反三能力。  
- 代码使用vector存储树结构，适合初学者理解。  
**核心代码**  
```cpp
void dfs(int nx){
    used[nx]=1;
    for(int i=0;i<son[nx].size();i++){
        int v=son[nx][i];
        if(used[v]==1) continue;
        dfs(v);
        f[nx][1] += f[v][0]; // 选当前节点则子节点不选
        f[nx][0] += max(f[v][0], f[v][1]); // 不选当前节点则子节点任选
    }
}
```

#### 2. 作者：x_faraway_x（★★★★☆）
**关键亮点**  
- 代码简洁高效，使用链式前向星存储树，适合处理大规模数据。  
- 父子关系处理清晰，通过传入父节点避免重复访问。  
**核心代码**  
```cpp
void dfs(int u, int father) {
    f[u][1] = 1; // 初始化选当前节点为1
    for(int e = head[u]; e; e = next[e]) {
        if(adj[e] == father) continue;
        dfs(adj[e], u);
        f[u][0] += max(f[adj[e]][0], f[adj[e]][1]);
        f[u][1] += f[adj[e]][0];
    }
}
```

#### 3. 作者：K2sen（★★★★☆）
**关键亮点**  
- 分享错误尝试（黑白染色贪心）的调试经验，强调树形DP的正确性。  
- 代码清晰，初始化逻辑明确，适合理解DP的底层原理。  
**核心代码**  
```cpp
void dfs(int x, int fx) {
    dp[x][1] = 1;
    for(int i = head[x]; i; i = edge[i].nxt) {
        int to = edge[i].to;
        if(to == fx) continue;
        dfs(to, x);
        dp[x][0] += max(dp[to][0], dp[to][1]);
        dp[x][1] += dp[to][0];
    }
}
```

### 关键思路总结
1. **状态设计**：`dp[u][0]` 表示不选节点u时的最大值，`dp[u][1]` 表示选节点u时的最大值。  
2. **转移方程**：  
   - 选u：`dp[u][1] = 1 + ∑dp[v][0]`（v为子节点）。  
   - 不选u：`dp[u][0] = ∑max(dp[v][0], dp[v][1])`。  
3. **初始化**：每个节点 `dp[u][1] = 1`（自身贡献）。  

### 拓展与举一反三
- **类似问题**：  
  - [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)（树形DP模板题）。  
  - [P2015 二叉苹果树](https://www.luogu.com.cn/problem/P2015)（树形背包问题）。  
  - [P2014 选课](https://www.luogu.com.cn/problem/P2014)（依赖型树形DP）。  
- **思维扩展**：树形DP还可用于路径统计、子树属性计算等，需结合具体问题灵活设计状态。  

### 个人心得摘录
> **K2sen** 的调试经历：  
> “最初尝试黑白染色贪心，但发现样例错误。通过分析反例理解贪心局限性，最终转向树形DP。”  
> **启示**：树形问题中，贪心策略需谨慎验证，DP是更普适的解决方案。

---
处理用时：97.80秒