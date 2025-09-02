# Presents in Bankopolis

## 题目描述

Bankopolis is an incredible city in which all the $ n $ crossroads are located on a straight line and numbered from $ 1 $ to $ n $ along it. On each crossroad there is a bank office.

The crossroads are connected with $ m $ oriented bicycle lanes (the $ i $ -th lane goes from crossroad $ u_{i} $ to crossroad $ v_{i} $ ), the difficulty of each of the lanes is known.

Oleg the bank client wants to gift happiness and joy to the bank employees. He wants to visit exactly $ k $ offices, in each of them he wants to gift presents to the employees.

The problem is that Oleg don't want to see the reaction on his gifts, so he can't use a bicycle lane which passes near the office in which he has already presented his gifts (formally, the $ i $ -th lane passes near the office on the $ x $ -th crossroad if and only if $ min(u_{i},v_{i})&lt;x&lt;max(u_{i},v_{i}))) $ . Of course, in each of the offices Oleg can present gifts exactly once. Oleg is going to use exactly $ k-1 $ bicycle lane to move between offices. Oleg can start his path from any office and finish it in any office.

Oleg wants to choose such a path among possible ones that the total difficulty of the lanes he will use is minimum possible. Find this minimum possible total difficulty.

## 说明/提示

In the first example Oleg visiting banks by path $ 1→6→2→4 $ .

Path $ 1→6→2→7 $ with smaller difficulity is incorrect because crossroad $ 2→7 $ passes near already visited office on the crossroad $ 6 $ .

In the second example Oleg can visit banks by path $ 4→1→3 $ .

## 样例 #1

### 输入

```
7 4
4
1 6 2
6 2 2
2 4 2
2 7 1
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4 3
4
2 1 2
1 3 2
3 4 2
4 1 1
```

### 输出

```
3
```

# 题解

## 作者：xzggzh1 (赞：15)

题意：

一个有向图，节点有编号，找一条经过 $k$ 个点的最短路径，要求是当前边不能跃过已经经过的节点。即对于路径中的边 $x \to y$ ，不存在以前经过的点 $t$ 使得 $x <t<y$ 。

 $ 1 \leq n,k \leq 80 $ ， $ m \leq 2000$ 。

---

每一次经过一条边都会使得可以到达的边的范围缩小。

考虑到  $ 1 \leq n,k \leq 80 $ 我们不难想到直接把可以去的区间存下来做$\rm DP$，

再按照类似区间$\rm DP$的做法开一维 $0,1$ 表示当前到达的端点是左端点还是右端点，然后直接转移即可。

具体的说，我们可以设 $f[i][j][k][0/1]$ 表示经过 $i$ 个点，可以去的区间是 $[j,k]$ ，现在在 左端点/右端点。其中第一维可以用滚动数组存。

---

剩下的一些小细节可以看代码：

```cpp
const int N=85;
int n,K,m,u,v,c,cc[N][N],f[2][N][N][2],i,j,k,nw,ans=1<<30;
int main(){
	memset(cc,1,sizeof cc);
	scanf("%d%d%d",&n,&K,&m);
	while(m--)scanf("%d%d%d",&u,&v,&c),cc[u][v]=min(cc[u][v],c);
	memset(f[0],1,sizeof f[0]);
	for(i=1;i<=n;++i)f[0][0][i][1]=f[0][i][n+1][0]=0;
	while(--K){
		nw^=1;memset(f[nw],1,sizeof f[nw]);
		for(i=0;i<=n-1;++i)for(j=i+2;j<=n+1;++j)for(k=i+1;k<j;++k){
			f[nw][i][k][1]=min(f[nw][i][k][1],min(f[!nw][i][j][1]+cc[j][k],f[!nw][i][j][0]+cc[i][k]));
			f[nw][k][j][0]=min(f[nw][k][j][0],min(f[!nw][i][j][0]+cc[i][k],f[!nw][i][j][1]+cc[j][k]));
		}
	}
	for(i=0;i<=n+1;++i)for(j=0;j<=n+1;++j)ans=min(ans,min(f[nw][i][j][0],f[nw][i][j][1]));
	if(ans>1<<20)ans=-1;
	printf("%d\n",ans);
}

```

---

## 作者：船酱魔王 (赞：1)

# CF793D 题解

## 题意回顾

给定 $ n $ 点 $ m $ 边有向图。我们需要找到一条长度为 $ k $ 的链，使得：

* 链上的点相互不同。

* 对于两个链上相邻的点 $ u,v $，不存在 $ u<r<v $ 使得 $ r $ 在链上且在 $ u,v $ 之前。

* 在此基础上，链的长度最小。

$ 1 \le n,k \le 80 $，$ 0 \le m \le 2000 $。

## 分析

$ n,k $ 范围很小，可以考虑设计与 $ n,k $ 相关的高复杂度多项式级别 DP。

我们发现，如果已经确定链上的已知点 $ u $ 及前面的点，记点号小于 $ u $ 的点的最大点号值为 $ r $，点号大于 $ u $ 的点的最小值为 $ v $，则下一个点的点号要不然在 $ (r,u) $ 之间，要不然在 $ (u,v) $ 之间，且这些点都有可能成为下一个点（当然还需要 $ u $ 向这个点连一条边）。


因此，我们的 DP 状态只需要 $ l,r,k',pos $，表示目前我们可选的点的范围 $ (l,r) $，我们还需要走 $ k' $ 步，我们目前在 $ pos $。因为 $ pos=l $ 或 $ pos=r $，所以我们只需要记录 $ ps \in \{0,1\} $ 表示 $ pos=l $ 还是 $ pos=r $。

对于被 $ pos $ 连边的所有 $ v $，显然有状态转移方程：

$$ dp_{l,r,k',pos}=\min\{dp_{l,v,k'-1,v},dp_{v,r,k'-1,v}+w_{pos,v}\} $$

因此，$ dp_{0,n+1,k+1,0} $ 即为答案（需要建立虚点 $ 0 $ 向所有点连 $ 0 $ 边）。

这里使用记忆化搜索来实现本题。

## AC 代码

```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
const int N = 85;
const int inf = 1e9 + 5;
int n, k;
int m;
struct node {
    int to;
    int w;
};
node make(int v0, int w0) {
    node res;
    res.to = v0;
    res.w = w0;
    return res;
}
vector<node> g[N];
int dp[N][N][N][2];//between ... and ...(non-included), need go ... steps, you are in 0-left/1-right
int solve(int l, int r, int st, int ps) {
    if(dp[l][r][st][ps] != -1) {
        return dp[l][r][st][ps];
    }
    if(st == 1) {
        return dp[l][r][st][ps] = 0;
    }
    if(l >= r - 1) {
        return inf;
    }
    dp[l][r][st][ps] = inf;
    if(ps == 0) {
        for(int i = 0; i < g[l].size(); i++) {
            int v = g[l][i].to;
            int w = g[l][i].w;
            if(l < v && v < r) {
                dp[l][r][st][ps] = min(dp[l][r][st][ps], min(solve(l, v, st - 1, 1), solve(v, r, st - 1, 0)) + w);
            }
        }
    } else {
        for(int i = 0; i < g[r].size(); i++) {
            int v = g[r][i].to;
            int w = g[r][i].w;
            if(l < v && v < r) {
                dp[l][r][st][ps] = min(dp[l][r][st][ps], min(solve(l, v, st - 1, 1), solve(v, r, st - 1, 0)) + w);
            }
        }
    }
    return dp[l][r][st][ps];
}
int main() {
    cin >> n >> k;
    cin >> m;
    int u, v, w;
    for(int i = 1; i <= m; i++) {
        cin >> u >> v >> w;
        g[u].push_back(make(v, w));
    }
    for(int i = 1; i <= n; i++) {
        g[0].push_back(make(i, 0));
    }
    memset(dp, -1, sizeof(dp));
    int ans = solve(0, n + 1, k + 1, 0);
    if(ans != inf) {
        printf("%d\n", ans);
    } else {
        printf("-1\n");
    }
    return 0;
}

```

---

