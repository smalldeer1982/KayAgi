# 题目信息

# [USACO08JAN] Cell Phone Network G

## 题目描述

Farmer John has decided to give each of his cows a cell phone in hopes to encourage their social interaction. This, however, requires him to set up cell phone towers on his N (1 ≤ N ≤ 10,000) pastures (conveniently numbered 1..N) so they can all communicate.

Exactly N-1 pairs of pastures are adjacent, and for any two pastures A and B (1 ≤ A ≤ N; 1 ≤ B ≤ N; A ≠ B) there is a sequence of adjacent pastures such that A is the first pasture in the sequence and B is the last. Farmer John can only place cell phone towers in the pastures, and each tower has enough range to provide service to the pasture it is on and all pastures adjacent to the pasture with the cell tower.

Help him determine the minimum number of towers he must install to provide cell phone service to each pasture.

Farmer John 想让他的所有牛用上手机以便相互交流。他需要建立几座信号塔在 $N$ 块草地中。已知与信号塔相邻的草地能收到信号。给你 $N-1$ 个草地 $(A,B)$ 的相邻关系，问：最少需要建多少个信号塔能实现所有草地都有信号。


## 样例 #1

### 输入

```
5
1 3
5 2
4 3
3 5
```

### 输出

```
2
```

# AI分析结果

### 综合分析与结论
本题是在树上求解最小支配集问题，题解主要分为树形 DP 和贪心两种思路。

#### 树形 DP 思路
定义状态表示节点及其子树的覆盖情况，一般有三种状态：被自己覆盖、被儿子覆盖、被父亲覆盖。通过深度优先搜索遍历树，根据子节点的状态更新父节点的状态。难点在于处理被儿子覆盖的状态，需保证至少有一个儿子放置信号塔，部分题解采用反悔机制解决。

#### 贪心思路
从叶子节点或深度最大的节点开始，若节点未被覆盖，则在其父节点放置信号塔，保证覆盖范围最大。可使用优先队列维护节点深度，或按深度倒序排序节点。

### 所选题解
- **InnovatorNZ（5星）**
    - **关键亮点**：思路清晰，代码注释详细，通过三种状态（-1、0、1）简洁地表示节点需求，避免复杂状态转移方程。
    - **核心代码**
```cpp
int dfs(int u, int p){
    int chosen=-1;    
    for(auto val:conn_matrix[u]){    
        if(val!=p){      
            int ret=dfs(val, u);    
            if(ret==-1)        
                chosen=1;    
            else if(ret==1 && chosen!=1)    
                chosen=0;    
        }
    }
    if(chosen==1) ans++;    
    return chosen;      
}
```
    - **核心思想**：深度优先搜索，根据子节点状态更新当前节点状态，若子节点需要父亲放置天线，则当前节点放置；若子节点放置了天线，则当前节点无需放置。

- **Apro1066（4星）**
    - **关键亮点**：思路详细，对状态转移方程推导清晰，引入反悔机制解决被儿子覆盖状态的问题。
    - **核心代码**
```cpp
void dfs(int i,int fa)
{
    bool f(0);
    register int j,p(inf);
    for(j=head[i];j;j=e[j].nxt)
    {
        int v(e[j].to);
        if(v==fa) continue;
        dfs(v,i);
        dp[i][0]+=min(dp[v][1],min(dp[v][0],dp[v][2]));
        dp[i][1]+=min(dp[v][0],dp[v][2]);
        dp[i][2]+=min(dp[v][0],dp[v][2]);
        p=min(p,dp[v][0]-min(dp[v][2],dp[v][0]));
    }
    dp[i][2]+=p;
    dp[i][0]++;
}
```
    - **核心思想**：深度优先搜索，更新三种状态的最小信号塔数，通过记录差值保证被儿子覆盖状态下至少有一个儿子放置信号塔。

- **何卓然（4星）**
    - **关键亮点**：从最小支配集角度分析问题，贪心策略清晰，按深度优先遍历序列的反向进行贪心，保证正确性。
    - **核心代码**
```cpp
void dfs(int cur,int d)
{
    vis[cur] = true;
    deep[cur] = d;
    a[++cnt] = cur;
    REP(i,0,edges[cur].size())
    {
        if (!vis[edges[cur][i]])
        {
            father[edges[cur][i]] = cur;
            dfs(edges[cur][i],d+1);
        }
    }
}
int greedy()
{
    bool s[10005]; 
    bool set[10005]; 
    int ans = 0;
    for(int i=n;i>0;i--)
    {
        int t = a[i];
        if(!s[t])
        {
            if(!set[father[t]])
            {
                set[father[t]]=true;
                ans++;
            }
            s[t]=true;
            s[father[t]]=true;
            s[father[father[t]]]=true;
        }
    }
    return ans;
}
```
    - **核心思想**：深度优先搜索记录节点深度和遍历序列，按反向序列贪心，若节点未被覆盖且父节点不在支配集，则将父节点加入支配集。

### 最优关键思路或技巧
- **树形 DP**：定义合理状态，利用深度优先搜索进行状态转移，引入反悔机制处理特殊情况。
- **贪心**：从叶子节点或深度最大节点开始，选择父节点放置信号塔，使用优先队列或排序维护节点顺序。

### 拓展思路
此类题目特点是在树上选尽量少的点打标记，使每个点与最近标记点距离不超过一定限制。通用解法为建树、初始化深度、按深度从深到浅遍历，若节点后代无满足条件的标记点，则在其祖宗处打标记。

### 相似题目推荐
1. [P2016 战略游戏](https://www.luogu.org/problemnew/show/P2016)
2. [P2279 [HNOI2003]消防局的设立](https://www.luogu.org/problem/P2279)
3. [P3942 将军令](https://www.luogu.org/problem/P3942)

### 个人心得摘录与总结
- **林志杰**：调试时因数据范围问题爆掉，提醒注意数据范围。
- **yzbsy**：用拓扑排序替代 dfs 进行树形 DP，提供不同实现思路。 

---
处理用时：42.64秒