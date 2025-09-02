# 题目信息

# Determine Winning Islands in Race

## 题目描述

MOOOOOOOOOOOOOOOOO

— Bessie the Cow, The Art of Racing on Islands



Two of Farmer John's cows, Bessie and Elsie, are planning to race on $ n $ islands. There are $ n - 1 $ main bridges, connecting island $ i $ to island $ i + 1 $ for all $ 1 \leq i \leq n - 1 $ . Additionally, there are $ m $ alternative bridges. Elsie can use both main and alternative bridges, while Bessie can only use main bridges. All bridges are one way and can only be used to travel from an island with a lower index to an island with a higher index.

Initially, Elsie starts on island $ 1 $ , and Bessie starts on island $ s $ . The cows alternate turns, with Bessie making the first turn. Suppose the cow is on island $ i $ . During a cow's turn, if there are any bridges connecting island $ i $ to island $ j $ , then the cow can move to island $ j $ . Then, island $ i $ collapses, and all bridges connecting to island $ i $ also collapse. Also, note the following:

- If there are no bridges connecting island $ i $ to another island, then island $ i $ collapses, and this cow is eliminated from the race.
- If the other cow is also on island $ i $ , then after this cow moves to another island, the island collapses, and the other cow is eliminated from the race.
- After an island or bridge collapses, no cows may use them.
- If a cow is eliminated, their turn is skipped for the rest of the race.

The race ends once either cow reaches island $ n $ . It can be shown that regardless of the cows' strategies, at least one cow reaches island $ n $ . Bessie wins if and only if she reaches island $ n $ first.

For each $ 1 \leq s \leq n - 1 $ , determine whether Bessie wins if she starts the race on island $ s $ . Assume both cows follow optimal strategies to ensure their own respective victories.

## 说明/提示

In the first test case, there are no alternative bridges for Elsie to overtake Bessie and reach island $ n $ first, so Bessie will win on all islands because she always moves first.

In the second case, Bessie will lose if she starts on island $ 3 $ because:

- Bessie's Turn: Take a main bridge from island $ 3 $ to island $ 4 $ .
- Elsie's Turn: Take a main bridge from island $ 1 $ to island $ 2 $ .
- Bessie's Turn: Take a main bridge from island $ 4 $ to island $ 5 $ .
- Elsie's Turn: Take an alternative bridge from island $ 2 $ to island $ 6 $ . Elsie reaches island $ n $ first.

## 样例 #1

### 输入

```
5
6 0
6 1
2 6
6 1
1 5
10 4
1 3
1 6
2 7
3 8
15 3
2 8
4 9
8 15```

### 输出

```
11111
11011
10011
100001111
11000111000111```

# AI分析结果

### 题目内容中文重写
# 确定岛屿竞赛的获胜方

## 题目描述

哞~~~~~~~~~~~~~~~~

——奶牛贝西《岛屿竞赛的艺术》

农夫约翰的两头奶牛，贝西（Bessie）和埃尔西（Elsie），计划在 $n$ 个岛屿上进行一场比赛。有 $n - 1$ 座主桥，对于所有 $1 \leq i \leq n - 1$，这些主桥将岛屿 $i$ 连接到岛屿 $i + 1$。此外，还有 $m$ 座备用桥。埃尔西可以使用主桥和备用桥，而贝西只能使用主桥。所有的桥都是单向的，只能从编号较小的岛屿通向编号较大的岛屿。

初始时，埃尔西从岛屿 $1$ 出发，贝西从岛屿 $s$ 出发。奶牛们轮流行动，贝西先行动。假设奶牛当前在岛屿 $i$ 上。在奶牛的回合中，如果有任何桥将岛屿 $i$ 连接到岛屿 $j$，那么这头奶牛可以移动到岛屿 $j$。然后，岛屿 $i$ 会坍塌，所有连接到岛屿 $i$ 的桥也会坍塌。同时，请注意以下几点：
- 如果没有桥将岛屿 $i$ 连接到其他岛屿，那么岛屿 $i$ 会坍塌，这头奶牛将被淘汰出比赛。
- 如果另一头奶牛也在岛屿 $i$ 上，那么在这头奶牛移动到另一个岛屿后，该岛屿坍塌，另一头奶牛将被淘汰出比赛。
- 当一个岛屿或一座桥坍塌后，任何奶牛都不能再使用它们。
- 如果一头奶牛被淘汰，那么在比赛的剩余时间里，它的回合将被跳过。

一旦有任何一头奶牛到达岛屿 $n$，比赛就结束。可以证明，无论奶牛们采取何种策略，至少有一头奶牛会到达岛屿 $n$。当且仅当贝西首先到达岛屿 $n$ 时，贝西获胜。

对于每个 $1 \leq s \leq n - 1$，确定如果贝西从岛屿 $s$ 开始比赛，她是否会获胜。假设两头奶牛都遵循最优策略以确保自己获胜。

## 说明/提示
在第一个测试用例中，没有备用桥供埃尔西超过贝西并先到达岛屿 $n$，所以贝西在所有岛屿上都会获胜，因为她总是先行动。

在第二个测试用例中，如果贝西从岛屿 $3$ 出发，她会输，原因如下：
- 贝西的回合：从岛屿 $3$ 通过主桥移动到岛屿 $4$。
- 埃尔西的回合：从岛屿 $1$ 通过主桥移动到岛屿 $2$。
- 贝西的回合：从岛屿 $4$ 通过主桥移动到岛屿 $5$。
- 埃尔西的回合：从岛屿 $2$ 通过备用桥移动到岛屿 $6$。埃尔西先到达岛屿 $n$。

## 样例 #1
### 输入
```
5
6 0
6 1
2 6
6 1
1 5
10 4
1 3
1 6
2 7
3 8
15 3
2 8
4 9
8 15
```

### 输出
```
11111
11011
11011
100001111
11000111000111
```

### 综合分析与结论
这些题解的核心思路都是通过分析 Elsie 能获胜的情况，来推断 Bessie 的胜负。由于 Bessie 只能走主桥，Elsie 若要获胜就需借助备用桥超过 Bessie。各题解的主要区别在于如何计算 Elsie 的最短路径以及处理 Bessie 起点和 Elsie 获胜区间的方式。

### 所选题解
1. **作者：KarmaticEnding（5星）**
    - **关键亮点**：思路清晰，通过反向思考 Elsie 获胜的条件，利用差分数组合并区间，有效降低了时间复杂度。代码实现简洁明了，注释详细，易于理解。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+10;
int T,n,m;
int d[MAXN],s[MAXN],dis[MAXN];
vector<int> g[MAXN];
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        for(int i=0;i<=n;++i){
            d[i]=s[i]=0;
            g[i].clear();
            dis[i]=0x3f3f3f3f;
        }
        dis[1]=0;
        for(int i=0,u,v;i<m;++i){
            scanf("%d%d",&u,&v);
            g[u].push_back(v);
        }
        for(int u=1;u<=n;++u){
            dis[u]=min(dis[u],dis[u-1]+1);
            for(int v:g[u]){
                if(v-u>dis[u]+1){
                    ++d[u+1];
                    --d[v-dis[u]-1];
                }
                dis[v]=min(dis[v],dis[u]+1);
            }
        }
        for(int i=1;i<=n;++i){
            s[i]+=s[i-1]+d[i];
        }
        for(int i=1;i<n;++i){
            if(s[i]){
                putchar('0');
            }
            else{
                putchar('1');
            }
        }
        putchar('\n');
    }
    return 0;
}
```
    - **核心实现思想**：先初始化距离数组 `dis`，然后遍历每个节点，更新其距离。对于每个备用桥，若满足一定条件则更新差分数组 `d`。最后通过前缀和计算 `s` 数组，根据 `s` 数组的值判断 Bessie 的胜负。

2. **作者：Redshift_Shine（4星）**
    - **关键亮点**：采用线性 DP 方法，通过分析 Elsie 淘汰 Bessie 的充要条件，逐步更新 Elsie 走到每个位置的最小用时，思路严谨，代码简洁。
    - **核心代码**：
```c++
#include <iostream>
#include <vector>
using namespace std;
const int N = 2e5 + 10;
int n, m, dp[N], mnp;
vector<int> road[N];
bool res[N];
void run()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        road[i].clear();
        dp[i] = i;
    }
    for (int i = 1, x, y; i <= m; i++)
    {
        scanf("%d%d", &x, &y);
        road[x].emplace_back(y);
    }
    mnp = 0;
    res[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        dp[i - 1] = min(dp[i - 1], dp[i - 2] + 1);
        for (auto &j : road[i - 1])
        {
            dp[j] = min(dp[j], dp[i - 1] + 1);
            mnp = max(mnp, j - dp[j]);
        }
        res[i] = (i > mnp);
    }
    for (int i = 1; i < n; i++)
    {
        printf("%d", res[i]);
    }
    putchar('\n');
}
int main()
{
    int T = 1;
    scanf("%d", &T);
    while (T--)
        run();
}
```
    - **核心实现思想**：初始化 `dp` 数组，通过遍历每个节点和其连接的备用桥，更新 `dp` 数组和全局最小 `s` 值 `mnp`。最后根据 `mnp` 判断 Bessie 的胜负。

3. **作者：yshpdyt（4星）**
    - **关键亮点**：详细分析了 Elsie 获胜的条件，通过枚举 Elsie 先到达的点，在求最短路的过程中顺带统计答案，使用差分数组维护贡献，思路巧妙。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define N 200005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const int mod=1e9+7;
const int inf=1e18;
const double eps=1e-6;

int n,m,f[N],sum[N];
vector<int> v[N];
bool vis[N];
queue<int>q;
void add(int l,int r){
    sum[l]++,sum[r+1]--;
}
void fc(){
    for(int i=1;i<=n;i++)f[i]=inf,vis[i]=0;
    f[1]=0;
    q.push(1);
    while(!q.empty()){
        int t=q.front();
        q.pop();
        if(vis[t]==1)continue;
        vis[t]=1;
        for(auto y:v[t]){
            if(f[y]>f[t]+1){
                f[y]=f[t]+1;
                q.push(y);
            }
            if(y-f[t]-2>=t+1)add(t+1,y-f[t]-2);
        }
    }
}
void sol(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        v[i].clear(),sum[i]=0;
        v[i].push_back(i+1);
    }
    for(int i=1,x,y;i<=m;i++){
        cin>>x>>y;
        v[x].push_back(y);
    }
    fc();
    for(int i=1;i<n;i++){
        sum[i]=sum[i-1]+sum[i];
        if(sum[i])cout<<0;
        else cout<<1;
    }
    cout<<endl;
}
int main(){
    int ttt;
    cin>>ttt;
    while(ttt--)sol();
    return 0;
}
```
    - **核心实现思想**：使用 BFS 求最短路，在更新最短路的过程中，根据 Elsie 获胜的条件更新差分数组 `sum`。最后通过前缀和判断 Bessie 的胜负。

### 最优关键思路或技巧
- **反向思考**：不直接考虑 Bessie 获胜的情况，而是分析 Elsie 获胜的条件，简化了问题。
- **差分数组**：用于合并区间，将区间更新的时间复杂度从 $O(n)$ 降低到 $O(1)$。
- **线性 DP**：利用单向边的特性，通过逐步更新状态，计算 Elsie 走到每个位置的最小用时。

### 可拓展之处
同类型题可能会改变地图结构、边的属性或奶牛的移动规则。类似算法套路包括分析获胜条件、计算最短路径、处理区间问题等。

### 推荐洛谷题目
1. [P1119 灾后重建](https://www.luogu.com.cn/problem/P1119)：涉及图的最短路径和动态规划。
2. [P1880 石子合并](https://www.luogu.com.cn/problem/P1880)：区间动态规划问题。
3. [P2888 [USACO07NOV]Cow Hurdles S](https://www.luogu.com.cn/problem/P2888)：图的最短路问题，可使用 Floyd 算法。

### 个人心得
作者 Redshift_Shine 提到在题解区存在将解法复杂化以凸显水平的不良风气，强调应追求更低时间复杂度和更易理解的解法。这提醒我们在解题和分享题解时，要注重方法的简洁性和实用性。 

---
处理用时：62.24秒