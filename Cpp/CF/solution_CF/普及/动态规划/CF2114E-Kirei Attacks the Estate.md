# Kirei Attacks the Estate

## 题目描述

Once, Kirei stealthily infiltrated the trap-filled estate of the Ainzbern family but was discovered by Kiritugu's familiar. Assessing his strength, Kirei decided to retreat. The estate is represented as a tree with $ n $ vertices, with the root at vertex $ 1 $ . Each vertex of the tree has a number $ a_i $ recorded, which represents the danger of vertex $ i $ . Recall that a tree is a connected undirected graph without cycles.

For a successful retreat, Kirei must compute the threat value for each vertex. The threat of a vertex is equal to the maximum alternating sum along the vertical path starting from that vertex. The alternating sum along the vertical path starting from vertex $ i $ is defined as $ a_i - a_{p_i} + a_{p_{p_i}} - \ldots $ , where $ p_i $ is the parent of vertex $ i $ on the path to the root (to vertex $ 1 $ ).

For example, in the tree below, vertex $ 4 $ has the following vertical paths:

- $ [4] $ with an alternating sum of $ a_4 = 6 $ ;
- $ [4, 3] $ with an alternating sum of $ a_4 - a_3 = 6 - 2 = 4 $ ;
- $ [4, 3, 2] $ with an alternating sum of $ a_4 - a_3 + a_2 = 6 - 2 + 5 = 9 $ ;
- $ [4, 3, 2, 1] $ with an alternating sum of $ a_4 - a_3 + a_2 - a_1 = 6 - 2 + 5 - 4 = 5 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2114E/041b3ada5bf12f77aa5a5a5b9431f1b90937ec72.png) The dangers of the vertices are indicated in red.Help Kirei compute the threat values for all vertices and escape the estate.

## 说明/提示

The tree from the first test case is depicted in the statement, and the maximum variable-sign sums are achieved as follows:

1. $ a_1 = 4 $ ;
2. $ a_2 = 5 $ ;
3. $ a_3 = 2 $ ;
4. $ a_4 - a_3 + a_2 = 6 - 2 + 5 = 9 $ ;
5. $ a_5 = 7 $ .

## 样例 #1

### 输入

```
2
5
4 5 2 6 7
1 2
3 2
4 3
5 1
6
1000000000 500500500 900900900 9 404 800800800
3 4
5 1
2 5
1 6
6 4```

### 输出

```
4 5 2 9 7 
1000000000 1500500096 1701701691 199199209 404 800800800```

# 题解

## 作者：Gaochenxi103_QWQ (赞：4)

发现，一个点的值依赖于从根节点到其的路径，因为一个点的值是这个路径上的最大值，并且如果一知一个节点往上计算过程中的最大值，那么它的子节点的值，就是上述值与它本身值的最大值。

因为往上奇数层是减偶数层是加，考虑分类。\
定义 $dp_{i,0}$ 表示第 $i$ 个节点在偶数层的往上计算过程中的最大值。反之为奇数。

考虑转移。\
容易发现，由于是过程中的最大值，所以 $dp_{i,0}=\max{c_i,dp_{fa,1}+c_i}$。其中 $c_i$ 表示这个节点的本身值。\
对于为什么是由上层奇数层转移过来的，解释为，本层为偶数层，在往上是从奇数层转移来的。

反之 $dp_{i,1}=\max{-c_i,dp_{fa,0}-c_i}$。

总结：一道明显的简单树型 DP。

核心代码。
```cpp
void dfs(int u,int fa)
{
    ans[u]=max(c[u],c[u]+dp[fa][1]);
    dp[u][0]=max(c[u],dp[fa][1]+c[u]);
    dp[u][1]=max(-c[u],dp[fa][0]-c[u]);
    for(auto v:G[u])
    {
        if(v==fa)continue;
        dfs(v,u);
    }
}
```

---

## 作者：wurang (赞：1)

由于需要取反，所以我们记录遍历到第 $p$ 个节点时的最大值和以及最小值。

令该节点为 $p$，其父亲节点 $fa$，则为转移方程如下：

$$
maxx[p] = \max(v[p], v[p] - minn[fa])
$$
$$
minn[p] = \min(v[p], v[p] - maxx[fa])
$$

通过 dfs 依此计算每个节点即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

int t, n;
int u, vv;
int v[200005];
int maxx[200005];
int minn[200005];
vector <int> edge[200005];

void dfs(int p, int fa)
{
    maxx[p] = max(v[p], v[p] - minn[fa]);
    minn[p] = min(v[p], v[p] - maxx[fa]);
    for(int i = 0; i < edge[p].size(); i++)
        if(edge[p][i] != fa) dfs(edge[p][i], p);
}

signed main() 
{
    cin >> t;
    while (t--) 
    {
        memset(maxx, 0, sizeof(maxx));
        memset(minn, 0, sizeof(minn));
        for(int i = 1; i <= n; i++)
            edge[i].clear();
        cin >> n;
        for(int i = 1; i <= n; i++) cin >> v[i];
        for(int i = 1; i <= n - 1; i++)
            cin >> u >> vv, edge[u].push_back(vv), edge[vv].push_back(u);
        dfs(1, 0);
        for(int i = 1; i <= n; i++)
            cout << maxx[i] << " ";
        cout << "\n";
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：1)

简单题。

题意：给你一棵根为 $1$ 号点的树，每个点有一个点权 $a_i$，求这个点到根的路径的最大交错和，交错和的定义为 $a_i-a_{p_i}+a_{p_{p_i}}-\ldots$，其中 $p_i$ 是 $i$ 号节点的父节点。

思路：只需要维护每个点的最大最小值 $mx_i,mn_i$，每新访问一个点，贪心地将 $mx_i$ 设为 $\max(a_i,a_i-mn_{p_i})$，$mn_i$ 设为 $\min(a_i,a_i-mx_{p_i})$ 即可。时间复杂度是 $O(\sum n)$，常数似乎有点大，跑了 $327$ 毫秒。注意不要 `memset`，否则会 TLE。

[代码 & AC 记录](https://codeforces.com/contest/2114/submission/321456187)

---

## 作者：the_Short_Path (赞：0)

## 形式化题意
给定一棵根为 $1$ 的树，每个结点有一个点权 $a_i$，求这个点到根的路径的最大距离。

距离：记  $fa_i$ 为 $i$ 的父节点，则其距离为 $a_i−a_{fa_i}+a_{fa_{fa_i}}-\dots$。

树形 dp，记 $dp_{i,0/1}$ 为加上/减去点权。则转移方程为：
 $$dp_{i,0}=\max(a_i,dp_{fa_i,1}+a_i)$$
 $$dp_{i,1}=\max(-a_i,dp_{fa_i,0}-a_i)$$

# 正解
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, a[200005], dis[200005], dp[200005][2];
vector <int> G[200005];
multiset <int> sx, sy;
void dfs(int u, int fa) {
    dis[u] = max(a[u], a[u] + dp[fa][1]); // 答案为该点的点权与其 dp1 的值的和
    dp[u][0] = max(a[u], dp[fa][1] + a[u]);
    dp[u][1] = max(-a[u], dp[fa][0] - a[u]);
    for (auto v : G[u]) if (v != fa) dfs(v, u); // 特判有环
}
signed main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i], G[i].clear();
        for (int i = 1, u, v; i < n; i++) cin >> u >> v, G[u].push_back(v), G[v].push_back(u);
        dis[1] = a[1];
        dfs(1, -1);
        for (int i = 1; i <= n; i++) cout << dis[i] << " ";
        puts("");
    }
    return 0;
}
```

---

## 作者：IGpig (赞：0)

## CF2114E

### Solution

先看，这是一棵树，所以想树上动态规划。\
发现这个路径是从一号节点开始分奇和偶，所以可以定义 $dp_{0/1,i}$ 表示第 $i$ 个节点在偶数或者奇数层的最大值。
对于一个点 $x$ 和它的父亲 $fa$，所以可以根据题目中的定义有：
$$\begin{cases}dp_{0,x}=\max(-val_x,-val_x+dp_{1,fa})\\dp_{1,x}=\max(val_x,val_x+dp_{1,fa})\end{cases}$$
### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
using LL=long long;
const LL N=2e5+5;
LL t,n, dp[2][N],val[N];
vector<LL> g[N];
void dfs(LL x,LL fa){
    dp[1][x]=max(val[x],val[x]+dp[0][fa]),dp[0][x]=max(-val[x],-val[x]+dp[1][fa]);
    for(auto i : g[x]){
        if(i==fa) continue;
        dfs(i,x);
    }
}
void solve(){
    memset(dp,0,sizeof(dp));
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>val[i];
        g[i].clear();
    }
    for(int i=1,x,y;i<n;i++){
        cin>>x>>y;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }
    dp[0][1]=val[1];
    dp[1][1]=-val[1];
    dfs(1,0);
    for(int i=1;i<=n;i++) cout<<dp[1][i]<<' ';
    cout<<endl;
}
int main(){
    cin>>t;
    while(t--){
        solve();
    }
}
```

---

## 作者：dbywsc (赞：0)

## 思路

一道树上动态规划。要想求以每个点为起点的最大交替和，那么我们可以定义两个数组 $\min n_u$ 和 $\max n_u$ 表示以 $u$ 为根节点的子树的**最小**交替和和**最大**交替和，设每个节点的权值为 $w$，那么对于 $u$ 的子节点 $v$，它的最大交替和就为：$\max n_v = w_v - \min n_u$ 相应的，我们也要维护当前节点的最小交替和，即：$\min n_v = \min(w_v, w_v - \max n_u)$ 最后定义一下边界，令：$\min n_1 = \max n_1 = w_1$ 就可以了。\
需要注意的是本题 $n \leq 2 \times 10^5$，如果整棵树是一条链的话 DFS 会爆栈，所以使用 BFS 。

## 赛时代码：

```cpp
#include <bits/stdc++.h>
#define x first
#define y second
#define endl '\n'
using i64 = long long;
typedef std::pair<i64, i64> PII;
const int N = 2e5 + 10;
i64 w[N], maxn[N], minn[N], ans[N];
int fa[N];
std::vector<int> G[N];
void bfs(void) {
    std::queue<int> q;
    maxn[1] = minn[1] = ans[1] = w[1];
    fa[1] = 0;
    q.push(1);
    while(q.size()) {
        auto u = q.front(); q.pop();
        for(auto v : G[u]) {
            if(v == fa[u]) continue;
            fa[v] = u;
            maxn[v] = w[v] - std::min(0ll, minn[u]);
            minn[v] = std::min(w[v], w[v] - maxn[u]);
            ans[v] = maxn[v];
            q.push(v);
        }
    }
}
/*void dfs(int u, int fa) {
    for(auto v : G[u]) {
        if(v == fa) continue;
        maxn[v] = w[v] - std::min(0ll, minn[u]);
        minn[v] = std::min(w[v], w[v] - maxn[u]);
        ans[v] = maxn[v];
        dfs(v, u);
    }
}*/
void solve(void) {
    memset(fa, 0, sizeof(fa));
    int n; std::cin >> n;
    for(int i = 1; i <= n; i++) G[i].clear();
    memset(maxn, 0 ,sizeof(maxn));
    memset(minn, 0 ,sizeof(minn));
    for(int i = 1; i <= n; i++) std::cin >> w[i];
    for(int i = 1; i < n; i++) {
        int u, v; std::cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    bfs();
    //maxn[1] = minn[1] = ans[1] = w[1];
    //dfs(1, 0);
    for(int i = 1; i <= n; i++) std::cout << ans[i] << " ";
    std::cout << endl;
}
int main(void) {
    //freopen("test.in", "r", stdin);
    std::ios::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while(t--) solve();
    return 0;
}
```

---

