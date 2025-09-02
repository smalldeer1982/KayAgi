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

### 题目内容重写

#### 题目描述

Farmer John 的两头奶牛 Bessie 和 Elsie 计划在 $n$ 个岛屿上进行比赛。岛屿之间有 $n - 1$ 座主桥，连接岛屿 $i$ 和岛屿 $i + 1$（$1 \leq i \leq n - 1$）。此外，还有 $m$ 座备用桥。Elsie 可以使用主桥和备用桥，而 Bessie 只能使用主桥。所有桥都是单向的，只能从编号较低的岛屿前往编号较高的岛屿。

初始时，Elsie 位于岛屿 $1$，Bessie 位于岛屿 $s$。两头奶牛轮流行动，Bessie 先手。假设奶牛位于岛屿 $i$，在它的回合中，如果有桥从岛屿 $i$ 连接到岛屿 $j$，那么它可以移动到岛屿 $j$。随后，岛屿 $i$ 会坍塌，所有连接到岛屿 $i$ 的桥也会坍塌。此外：

- 如果没有桥从岛屿 $i$ 连接到其他岛屿，那么岛屿 $i$ 会坍塌，这头奶牛被淘汰。
- 如果另一头奶牛也在岛屿 $i$，那么在这头奶牛移动到另一个岛屿后，岛屿 $i$ 会坍塌，另一头奶牛被淘汰。
- 岛屿或桥坍塌后，奶牛不能再使用它们。
- 如果一头奶牛被淘汰，它的回合将被跳过。

比赛在一头奶牛到达岛屿 $n$ 时结束。可以证明，无论奶牛采取什么策略，至少有一头奶牛会到达岛屿 $n$。Bessie 获胜当且仅当她先到达岛屿 $n$。

对于每个 $1 \leq s \leq n - 1$，确定如果 Bessie 从岛屿 $s$ 开始比赛，她是否能获胜。假设两头奶牛都采取最优策略以确保各自的胜利。

#### 说明/提示

在第一个测试用例中，Elsie 没有备用桥可以超过 Bessie 并先到达岛屿 $n$，因此 Bessie 在所有岛屿上都会获胜，因为她总是先手。

在第二个测试用例中，如果 Bessie 从岛屿 $3$ 开始，她会输，因为：

- Bessie 的回合：从岛屿 $3$ 通过主桥移动到岛屿 $4$。
- Elsie 的回合：从岛屿 $1$ 通过主桥移动到岛屿 $2$。
- Bessie 的回合：从岛屿 $4$ 通过主桥移动到岛屿 $5$。
- Elsie 的回合：从岛屿 $2$ 通过备用桥移动到岛屿 $6$。Elsie 先到达岛屿 $n$。

### 题解分析与结论

#### 题解对比与评分

1. **KarmaticEnding (5星)**
   - **关键亮点**：通过反向思考，考虑 Elsie 在什么情况下会赢，利用差分数组维护区间覆盖，最终通过前缀和判断 Bessie 是否获胜。思路清晰，代码简洁。
   - **个人心得**：通过考虑 Elsie 的获胜条件，简化了问题的复杂性。

2. **Redshift_Shine (4星)**
   - **关键亮点**：使用线性 DP 计算 Elsie 的最短路径，并通过比较 Bessie 和 Elsie 的到达时间来判断胜负。思路清晰，代码易读。
   - **个人心得**：通过动态规划逐步更新 Elsie 的最短路径，避免了复杂的区间合并。

3. **yshpdyt (4星)**
   - **关键亮点**：通过 BFS 计算 Elsie 的最短路径，并使用差分数组标记 Bessie 无法获胜的区间。思路清晰，代码简洁。
   - **个人心得**：通过 BFS 优化了最短路径的计算，避免了复杂的 DP 更新。

#### 最优关键思路

- **反向思考**：通过考虑 Elsie 的获胜条件，简化了问题的复杂性。
- **差分数组**：利用差分数组维护区间覆盖，最终通过前缀和判断 Bessie 是否获胜。
- **动态规划**：通过线性 DP 或 BFS 计算 Elsie 的最短路径，避免了复杂的区间合并。

#### 可拓展之处

- **类似问题**：可以扩展到其他类型的图论问题，如最短路径、区间覆盖等。
- **算法套路**：差分数组和动态规划的结合可以用于解决类似的区间覆盖问题。

#### 推荐题目

1. [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)
2. [P3384 【模板】树链剖分](https://www.luogu.com.cn/problem/P3384)
3. [P3385 【模板】负环](https://www.luogu.com.cn/problem/P3385)

### 核心代码片段

#### KarmaticEnding 的代码

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

#### Redshift_Shine 的代码

```cpp
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

#### yshpdyt 的代码

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
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    int ttt;
    cin>>ttt;
    while(ttt--)sol();
    return 0;
}
```

---
处理用时：79.28秒