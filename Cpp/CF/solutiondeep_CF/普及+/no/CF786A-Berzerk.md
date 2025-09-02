# 题目信息

# Berzerk

## 题目描述

Rick 和 Morty 在玩一个版本的 Berzerk 游戏。这个游戏需要很大的空间，所以他们使用电脑玩这个游戏。



游戏中有 $n$ 个标号从 $1 \sim n$ 的物体围成一个圆圈（顺时针标号）， 物体 $1$ 表示黑洞，其它物体表示星

球，且某一个星球上有一个怪物，Rick 和 Morty 不知道这个怪物在哪个星球上，只知道这个怪物在游

戏开始时没有进入黑洞。但就目前而言，他们希望为每种可能的情况做好准备。



Rick 和 Monty 每人有一个数的集合，集合中的数在 $[1,n-1]$ 之间。Rick 的集合是 $s_1$，其中有 $k_1$ 个

数，Morty 的集合是 $s_2$，其中有 $k_2$ 个数。游戏开始后，两人轮流操作。在操作中，玩家必须从他的集

合中选出一个数 $x$，怪物将从当前位置顺时针移动 $x$ 个位置，如果怪物移动后进入了黑洞，则该玩家获胜。



你的任务是对于每一个怪物的位置以及玩家先后手顺序，判断游戏先手获胜、后手获胜、无限循环。（每个玩家都采取最优操作）

## 样例 #1

### 输入

```
5
2 3 2
3 1 2 3
```

### 输出

```
Lose Win Win Loop
Loop Win Win Win
```

## 样例 #2

### 输入

```
8
4 6 2 3 4
2 3 6
```

### 输出

```
Win Win Win Win Win Win Win
Lose Win Lose Lose Win Lose Lose
```

# AI分析结果

### 题目内容
# Berzerk

## 题目描述
Rick和Morty在玩一个版本的Berzerk游戏。这个游戏需要很大的空间，所以他们使用电脑玩这个游戏。

游戏中有 $n$ 个标号从 $1 \sim n$ 的物体围成一个圆圈（顺时针标号），物体 $1$ 表示黑洞，其它物体表示星球，且某一个星球上有一个怪物，Rick和Morty不知道这个怪物在哪个星球上，只知道这个怪物在游戏开始时没有进入黑洞。但就目前而言，他们希望为每种可能的情况做好准备。

Rick和Monty每人有一个数的集合，集合中的数在 $[1,n - 1]$ 之间。Rick的集合是 $s_1$，其中有 $k_1$ 个数，Morty的集合是 $s_2$，其中有 $k_2$ 个数。游戏开始后，两人轮流操作。在操作中，玩家必须从他的集合中选出一个数 $x$，怪物将从当前位置顺时针移动 $x$ 个位置，如果怪物移动后进入了黑洞，则该玩家获胜。

你的任务是对于每一个怪物的位置以及玩家先后手顺序，判断游戏先手获胜、后手获胜、无限循环。（每个玩家都采取最优操作）

## 样例 #1
### 输入
```
5
2 3 2
3 1 2 3
```
### 输出
```
Lose Win Win Loop
Loop Win Win Win
```

## 样例 #2
### 输入
```
8
4 6 2 3 4
2 3 6
```
### 输出
```
Win Win Win Win Win Win Win
Lose Win Lose Lose Win Lose Lose
```

### 算法分类
搜索（深度优先搜索DFS和广度优先搜索BFS均有涉及）

### 题解综合分析与结论
这些题解都基于博弈论的基本结论：能转移到必败态的状态就是必胜态，只能转移到必胜态的状态就是必败态。由于已知位置1（黑洞）是必败态，所以都采用从位置1逆向推导各位置对于不同先手玩家的胜负情况的思路。不同之处在于实现方式，有的使用DFS（深度优先搜索），有的使用BFS（广度优先搜索），还有的使用拓扑排序（本质也是BFS思想）。

### 所选的题解
- **作者：Siyuan (赞：26)  星级：5星  关键亮点**：思路清晰，基于博弈论经典结论，通过DFS逆向推导每个位置和先后手的胜负情况，代码简洁明了，直接体现核心思路。
```cpp
#include <cstdio>
#include <algorithm>

const int N=7e3+5;
int n,k[2],a[2][N],cnt[2][N];
bool vis[2][N],win[2][N];

void dfs(int v,int now) {
    if(vis[v][now]) return;
    vis[v][now]=1;
    int u=v^1;
    for(int i=1;i<=k[u];++i) {
        int pre=(now-a[u][i]+n-1)%n+1;
        if(pre==1) continue;
        if(!win[v][now]) {
            win[u][pre]=1;
            dfs(u,pre);
        } else if(++cnt[u][pre]==k[u]) {
            win[u][pre]=0;
            dfs(u,pre);
        }
    }
}
int main() {
    scanf("%d",&n);
    for(int o=0;o<=1;++o) {
        scanf("%d",&k[o]);
        for(int i=1;i<=k[o];++i) scanf("%d",&a[o][i]);
    }
    dfs(0,1),dfs(1,1);
    for(int o=0;o<=1;++o) {
        for(int i=2;i<=n;++i) {
            printf("%s%c",vis[o][i]?win[o][i]?"Win":"Lose":"Loop"," \n"[i==n]);
        }
    }
    return 0;
}
```
核心实现思想：定义 `dfs(v, now)` 表示当前在 `now` 位置，玩家 `v` 先手。通过枚举上一次玩家 `u` 的操作 `x`，从 `now - x` 位置转移到 `now` 位置（排除 `now - x` 等于1的情况）。根据当前位置的胜负态来推导上一位置的胜负态，若当前为必败态，则上一位置为必胜态；若当前为必胜态且所有转移位置均为必胜态，则上一位置为必败态。
 - **作者：_ZSR_ (赞：2)  星级：4星  关键亮点**：采用BFS实现，通过维护度数来判断状态转移，逻辑清晰，利用队列实现状态的逐层更新。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=7e3+10;
typedef pair<int,int> pii;
int n;
int a[2][N],b[2];
int f[2][N];
int deg[2][N];
inline int pre (int x, int y)
{
    return (x-y+n-1)%n+1;
}
void solve () {
    queue<pii> q;
    f[0][1]=f[1][1]=2;
    q.push({1,0});
    q.push({1,1});
    while (q.size()) 
    {
        auto it=q.front(); 
        q.pop();
        int u=it.first,d=it.second;
        for (int i=1;i<=b[!d];++i) 
        {
            int v=pre(u,a[!d][i]);
            if (f[!d][v]) continue;
            if (f[d][u]==1) 
            {
                if (--deg[!d][v]==0) 
                {
                    f[!d][v]=2;
                    q.push({v,!d});
                }
            }
            else 
            {
                f[!d][v]=1;
                q.push({v,!d});
            }
        }
    }
}
int main () 
{
    scanf("%d",&n);
    for (int i=0;i<2;++i) 
    {
        scanf("%d",&b[i]);
        for (int j=1;j<=b[i];++j)
        {
            scanf("%d",&a[i][j]);
        }
    }
    for (int i=0;i<2;++i)
    {
        for (int j=2;j<=n;++j)
        {
            deg[i][j]=b[i];
        }
    }
    solve();
    for (int i=0;i<2;++i)
    {
        for (int j=2;j<=n;++j) 
        {
            if (f[i][j]==0) printf("Loop ");
            if (f[i][j]==1) printf("Win ");
            if (f[i][j]==2) printf("Lose ");
        }
        puts("");
    }
    return 0;
}
```
核心实现思想：从已知的必败态（位置1）开始，将其加入队列。每次从队列取出一个状态，根据当前状态的胜负情况更新前驱状态，并根据前驱状态的度数判断是否为必败态，若度数减为0则为必败态，否则根据当前状态更新前驱状态为必胜态，不断循环直到队列为空。
 - **作者：yimuhua (赞：2)  星级：4星  关键亮点**：同样基于DFS逆向推导，代码简洁，利用记忆化搜索避免重复计算，逻辑清晰易懂。
```cpp
#include <bits/stdc++.h>
using namespace std;
bool vis[2][7005], win[2][7005];
int n, b[2], a[2][7005], cnt[2][7005];
void dfs(bool f, int x) {
    if(vis[f][x])
        return;
    vis[f][x] = 1, f =!f;
    for(int i = 1; i <= b[f]; i++) {
        int pre = (x - a[f][i] + n - 1) % n + 1;
        if(pre ^ 1) {
            if(!win[!f][x])
                win[f][pre] = 1, dfs(f, pre);
            else if(++cnt[f][pre] == b[f])
                win[f][pre]= 0, dfs(f, pre);
        }
    }
    return;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for(int i = 0; i < 2; i++) {
        cin >> b[i];
        for(int j = 1; j <= b[i]; j++)
            cin >> a[i][j];
    }
    dfs(0, 1), dfs(1, 1);
    for(int i = 0; i < 2; i++) {
        for(int j = 2; j <= n; j++)
            cout << (vis[i][j]? win[i][j]? "Win " : "Lose " : "Loop ");
        cout << '\n';
    }
    return 0;
}
```
核心实现思想：定义 `dfs(f, x)` 表示当前在 `x` 位置，玩家 `f` 先手。通过记忆化搜索，避免重复计算已访问过的状态。在搜索过程中，根据当前位置的胜负情况，按照博弈论结论更新前驱位置的胜负态。

### 最优关键思路或技巧
1. **逆向思维**：从已知的必败态（黑洞位置1）开始逆向推导其他位置的胜负情况，避免正向搜索可能出现的循环依赖问题。
2. **状态标记与维护**：无论是DFS还是BFS，都通过标记状态（如是否访问过、胜负态等）和维护相关计数器（如能转移到必胜态的数量、度数等）来准确判断每个状态的性质。

### 同类型题或类似算法套路拓展
同类型题目通常围绕博弈论展开，特点是给定游戏规则和初始状态，要求判断玩家的最优策略或胜负情况。类似算法套路是基于博弈论的基本结论，从已知的终止状态（如必败态）逆向推导其他状态的性质。可以通过DFS或BFS实现，在实现过程中注意状态的标记、更新以及避免重复计算。

### 洛谷相似题目推荐
1. **P2197 【模板】nim游戏**：经典的Nim游戏模板题，通过异或运算判断胜负，考察对博弈论基本概念的理解。
2. **P1247 取火柴游戏**：同样是关于取火柴的博弈问题，需要分析不同取法下的胜负情况，与本题类似，需要运用逆向思维推导。
3. **P3185 [HNOI2007] 分裂游戏**：涉及到状态转移和博弈策略的分析，通过逆向思考不同状态间的关系来确定最优策略，与本题思路相似。 

---
处理用时：86.38秒