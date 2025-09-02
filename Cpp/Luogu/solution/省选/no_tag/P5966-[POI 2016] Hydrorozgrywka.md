# [POI 2016] Hydrorozgrywka

## 题目描述

给定一个 $n$ 个点 $m$ 条边的无向连通图，保证每条边属于且只属于一个环。

两个人在这张图上玩游戏，一开始他们会在某个节点放一个棋子，然后依次移动这个棋子，已经走过的边不能再走，谁不能移动谁就输了。

请求出所有先手必胜的策略中游戏开始时放棋子的位置。

## 说明/提示

对于 $100\%$ 的数据，$3\le n,m\le 5 \times 10^5$，$1\le a,b\le n$，$a\ne b$。

## 样例 #1

### 输入

```
6 7
1 2
2 3
3 1
3 4
4 5
5 6
6 3```

### 输出

```
1
1
1
2
1
2```

# 题解

## 作者：JCY_ (赞：3)

[更好的阅读体验](https://www.cnblogs.com/JCY-std/p/17861921.html)

# 题解

建出原图的圆方树。由于原图无重边，不妨把桥看作二元环建树，这样圆点只与方点直接相连。

圆方树定某一圆点为根后，若点 $u$ 是圆点，定义点 $u$ 的子仙人掌为点 $u$ 子树中的圆点在原图的导出子图，定义该子仙人掌的根为点 $u$；若点 $u$ 是方点，定义点 $u$ 的子仙人掌为点 $u$ 子树中的圆点和点 $u$ 的父亲在原图的导出子图，定义该子仙人掌的根为点 $u$ 的父亲。

考虑如何判断棋子在点 $x$ 是否先手必胜。在圆方树上定圆点点 $x$ 为根，手玩发现上文的「子仙人掌」结构是重要的：子仙人掌的包含关系呈树形，因此玩家只能在子仙人掌的根处选择是否进入。

这启发我们在圆方树上进行关于子树（即子仙人掌）信息的树形 dp。

在一切的之前先想象一下圆方树上 dp 的过程：方点的转移是合并若干个根节点串成环的子仙人掌的信息，圆点的转移是合并若干个共且仅共根节点的子仙人掌的信息。

## 设计 dp 状态

最直接的设计 dp 状态的方法是 $f_u = 0 / 1$ 表示只考虑点 $u$ 的子仙人掌，棋子在其根 先手必败 / 先手必胜。不难发现这种状态设计把「棋子最终停留在子仙人掌的根」看作失败，但由于我们上述状态设计中只考虑点 $u$ 的子仙人掌，实际上棋子最终停留在子仙人掌的根后还可能进入其他子仙人掌进行游戏。这一缺陷导致该 dp 状态设计无法准确进行「进入一个子仙人掌然后出来」这种转移。

我们想象子仙人掌的根节点向外部连出一条边。

0. 如果先手必败，那么先手会直接走那条边。

1. 如果先手必胜并且可以逼迫后手最终停留在非根节点，先手会进行这个必胜的游戏。

2. 否则，先手可以直接选择走那条边，也可以选择逼迫后手走那条边。

我们把这三种情况分别对应 $f_u = 0 / 1 / 2$。

## 进行 dp 转移

下文中点 $v$ 代表点 $u$ 的某一个儿子。

### 方点

如果点 $u$ 只有一个儿子，则它代表了一条桥边。此时必有 $f_u \neq 2$，因此 $f_u \leftarrow [f_v = 0]$。

否则，考虑在环上按照某个方向走一圈的过程：

如果我们碰上了一个 $f_v = 0$ 的仙人掌，当前玩家必然会忽略它。

如果我们碰上了一个 $f_v = 1$ 的仙人掌，当前玩家必胜。

如果我们碰上了一个 $f_v = 2$ 的仙人掌，当前玩家可以`选择`是否改变先后手，因此当前玩家必胜。

> 任何一个公平组合游戏中，如果你能在某一时刻有两种进入完全相同的局面、但先后手不同的决策，那么你是必胜的（这里的决策相当于把有向图上的很多已经确定会走的步打包成一步）。

因此找到环上向左走和向右走遇到的第一个 $f_v \neq 0$ 的 $v$，根据走的距离的奇偶性分别判断是否必胜即可。二者中有至少一者必胜则 $f_u \leftarrow 1$，否则 $f_u \leftarrow 0$。

特殊情况是 $\forall v, f_v = 0$，这种情况下只能绕着环走一圈。如果环是奇环则 $f_u \leftarrow 2$，否则 $f_u \leftarrow 0$。

### 圆点

如果 $\exists v, f_v = 1$，则 $f_u \leftarrow 1$。这是因为当前玩家肯定会选择进入这个子仙人掌。

否则，如果 $2 \nmid \sum_v [f_v = 2]$ 则 $f_u \leftarrow 2$，反之 $f_u \leftarrow 0$。这是因为 $2 \nmid \sum_v [f_v = 2]$ 时如果先手选择先改变一次先后手，在这之后每当后手通过一棵 $f_v = 2$ 的子仙人掌改变了先后手，先手总能通过另一棵改变回去。

## 换根

综上，我们容易得到一个 $O(n^2)$ 的算法，上述过程容易换根 dp 做到 $O(n)$。

### 2025.7.19 修正代码换根 dp 部分的错误实现

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using i128 = __int128;
using u128 = unsigned __int128;
template <typename T>
void chkmax(T &x, const T &y) {
  if (x < y) x = y;
}
template <typename T>
void chkmin(T &x, const T &y) {
  if (y < x) x = y;
}
constexpr int MAXN = 5e5 + 10;
int n, dfn[MAXN], low[MAXN], dfc, stk[MAXN], tp, num, dwn[MAXN * 2];
int cnt1[MAXN], cnt2[MAXN], up[MAXN * 2], all[MAXN], posl[MAXN * 2],
    posr[MAXN * 2];
vector<int> og[MAXN], g[MAXN * 2];
void tarjan(int u) {
  dfn[u] = low[u] = ++dfc;
  stk[++tp] = u;
  for (auto v : og[u]) {
    if (!dfn[v]) {
      tarjan(v);
      chkmin(low[u], low[v]);
      if (low[v] == dfn[u]) {
        g[u].emplace_back(++num);
        while (true) {
          int t = stk[tp--];
          g[num].emplace_back(t);
          if (t == v) break;
        }
      }
    } else {
      chkmin(low[u], dfn[v]);
    }
  }
}
void dfs1(int u) {
  for (auto v : g[u]) dfs1(v);
  if (u <= n) {
    for (auto v : g[u]) {
      if (dwn[v] == 1) {
        ++cnt1[u];
      } else if (dwn[v] == 2) {
        ++cnt2[u];
      }
    }
    if (cnt1[u]) {
      dwn[u] = 1;
    } else {
      dwn[u] = (cnt2[u] & 1 ? 2 : 0);
    }
  } else {
    if (g[u].size() == 1) {
      dwn[u] = !dwn[g[u][0]];
    } else {
      posl[u] =
          find_if(g[u].begin(), g[u].end(), [](int x) { return dwn[x]; }) -
          g[u].begin();
      if (posl[u] == (int)g[u].size()) {
        dwn[u] = (g[u].size() & 1 ? 0 : 2);
      } else {
        posr[u] =
            find_if(g[u].rbegin(), g[u].rend(), [](int x) { return dwn[x]; }) -
            g[u].rbegin();
        dwn[u] = (posl[u] & 1) || (posr[u] & 1);
      }
    }
  }
}
void dfs2(int u) {
  if (u <= n) {
    if (cnt1[u] + (up[u] == 1)) {
      all[u] = 1;
    } else {
      all[u] = ((cnt2[u] + (up[u] == 2)) & 1 ? 2 : 0);
    }
    for (auto v : g[u]) {
      if (cnt1[u] + (up[u] == 1) - (dwn[v] == 1)) {
        up[v] = 1;
      } else {
        up[v] = ((cnt2[u] + (up[u] == 2) - (dwn[v] == 2)) & 1 ? 2 : 0);
      }
      dfs2(v);
    }
  } else {
    if (g[u].size() == 1) {
      up[g[u][0]] = !up[u];
      dfs2(g[u][0]);
    } else {
      static int nxt[MAXN];
      for (int i = g[u].size() - 1, lst = g[u].size(); i >= 0; --i) {
        nxt[i] = lst;
        if (dwn[g[u][i]]) lst = i;
      }
      if (up[u]) posl[u] = -1;
      for (int i = 0, v, lst = (up[u] ? -1 : -2); i < (int)g[u].size(); ++i) {
        v = g[u][i];
        if (lst == -2 && nxt[i] == (int)g[u].size()) {
          up[v] = (g[u].size() & 1 ? 0 : 2);
        } else if (lst == -2) {
          up[v] = !((i + posr[u]) & 1) || !((nxt[i] - i) & 1);
        } else if (nxt[i] == (int)g[u].size()) {
          up[v] = !((i - lst) & 1) || ((g[u].size() - i + posl[u]) & 1);
        } else {
          up[v] = !((i - lst) & 1) || !((nxt[i] - i) & 1);
        }
        if (dwn[v]) lst = i;
      }
      for (auto v : g[u]) dfs2(v);
    }
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int m;
  cin >> n >> m;
  while (m--) {
    int u, v;
    cin >> u >> v;
    og[u].emplace_back(v);
    og[v].emplace_back(u);
  }
  num = n;
  tarjan(1);
  dfs1(1);
  dfs2(1);
  for (int i = 1; i <= n; ++i) cout << 2 - (bool)all[i] << "\n";
  return 0;
}
/*
g++ Hydro.cpp -o Hydro -std=c++14 -O2 -Wall -Wextra -Wshadow -g
-fsanitize=address,undefined
*/
```

---

## 作者：XuYueming (赞：1)

## 前言

题目链接：[洛谷](https://www.luogu.com.cn/problem/P5966)。

为啥没桥啊，没用到什么性质啊。

为啥没重边啊，没用到什么性质啊。

推荐阅读：[《圆方树学习笔记 —— 一种关于点双连通分量的思考方式》](https://www.cnblogs.com/XuYueming/p/18313014)。

[更好的体验](https://www.cnblogs.com/XuYueming/p/18992600)。

## 题意简述

原题无桥，不妨加强。原题无重边，不妨加强。

$n$ 个点、$m$ 条边的仙人掌上的博弈游戏。玩家可以选择一条没被经过的边，将棋子从边的一边移动到另一边。无法移动的玩家输。对于每一个点，求出棋子一开始在该点，先手是否有必胜策略。

$n\leq5\times10^5$。

## 题目分析

显然建出圆方树，树形 DP。设 $f_u=0/1$ 表示先手从 $u$ 开始，只考虑 $u$ 的子仙人掌，是否必胜 / 必败。

但是这个状态有缺陷，因为有可能绕了一圈回到 $u$，继续往子仙人掌以外走。总共有以下四种情况：

1. 先手如果往子仙人掌里走必败，即被堵在了 $u$ 的某一个子孙中；
1. 先手如果往子仙人掌里走必胜，后手被堵在了 $u$ 的某一个子孙中；
1. 先手如果往子仙人掌里走，回到 $u$，轮到后手，且不会再往子仙人掌里走。
1. 先手如果往子仙人掌里走，回到 $u$，轮到先手，且不会再往子仙人掌里走。

可以直接记 $f_u=0/1/2/3$ 吗？2,3 局面并不是互斥的，也就是说，先手可能可以选择先手回到 $u$，也可以选择后手回到 $u$。

所以记 $f_{u,0/1/2/3}\in\{\text{true},\text{false}\}$ 表示先手走进 $u$ 的子仙人掌中，先手是否必胜、先手是否必败、先手是否可以选择先手 / 后手回到 $u$ 走下一步。只有在 $f_{u,0/1}=\text{false}$ 的前提下，$f_{u,2/3}$ 才是有意义的。当然，也有可能 $f_{u,0/1/2/3}=\text{false}$，这种情况下由后手来决定谁回到 $u$。

对于根节点，只要 $f_{u,0/3}=\text{true}$ 就是必胜的。转移的话，分情况讨论。

1. $u$ 是方点
    1. 如果这个点双不是个环（即两点被桥连接）

        如果 $f_{v,1}=\text{true}$ 或 $f_{v,0}=\text{false}\land f_{v,3}=\text{false}$ 说明后手必败，先手必胜，$f_{u,0}=\text{true}$，其他均为 $\text{false}$；
        
        否则如果 $f_{v,0}=\text{true}$ 或 $f_{v,3}=\text{true}$ 说明后手必胜，先手必败，$f_{u,1}=\text{true}$，其他均为 $\text{false}$；
        
        不存在其他情况。
    1. 如果这个点双是个环

        一定会按环序依次经过环上的点，不妨先考虑顺时针。显然，一旦经过一个子仙人掌，这个子仙人掌之后就不会被访问到了。
        
        先考虑是否存在必胜必败的情况。
        
        1. 经过一个点 $f_{v,1}=\text{true}$：

            先手显然会跳过这个点，直接走到下一个点。
        1. 经过一个点 $f_{v,0}=\text{true}$：

            先手显然选择走进这个子仙人掌，**必胜**。
        1. 经过一个点 $f_{v,2}=\text{true}$：

            先手走不走无所谓，都会走到下一个点。
        1. 经过一个点 $f_{v,3}=\text{true}$：
        
            先手既可以选择走进去，换成后手，走向下一个点，也可以直接走到下一个点。也就是说，先手可以选择是否改变先后手。那么后继状态如果必胜，先手不会改变先后手，否则先手改变先后手，同样**必胜**。
        1. 经过一个点 $f_{v,2}=f_{v,3}=\text{false}$：

            先手如果走进去，后手就能够根据下一步的必胜必败，使得先手必败。所以先手不会走进去，而是直接前往下一个点。
        
        不存在其他情况。
        
        那么只要有一个 $f_{v,0/3}=\text{true}$，找到第一次出现的位置，看看奇偶性，就能判断先手必胜还是必败。同样逆时针做一遍。如果顺逆时针有一种情况先手必胜，那么先手就必胜，$f_{u,0}=\text{true}$，否则无论怎样，先手必败，$f_{u,1}=\text{true}$。
        
        如果没有 $f_{v,0/3}=\text{true}$，考虑求 $f_{u,2/3}$。
        
        发现没有必胜情况，先手都是往下一步走，所以如果是奇环，必定是先手回到 $u$，$f_{u,3}=\text{true}$；否则一定是后手回到 $u$，$f_{u,2}=\text{true}$。
1. $u$ 是圆点

    如果有个方儿子 $f_{v,0}=\text{true}$，那么 $u$ 必胜，$f_{u,0}=\text{true}$。
    
    如果每个方儿子都是 $f_{v,1}=\text{true}$ 或 $f_{v,2}=f_{v,3}=\text{false}$，那么 $u$ 必败，因为 $u$ 必须要行动，往任意一个孩子走都是必败的，$f_{u,1}=\text{true}$。
    
    如果满足 $f_{v,3}=\text{true}$ 的方儿子个数为奇数，那么 $u$ 就能改变先后手，即：先走到一个孩子里改变一次先后手，之后每次后手尝试改变先后手之后，$u$ 都能通过走到另一个孩子里改回来，$f_{u,3}=\text{true}$。
    
    如果满足 $f_{v,3}=\text{true}$ 的方儿子个数为偶数，并且有一个 $f_{v,2}=\text{true}$，$u$ 就能保持先手，之后每次后手尝试改变先后手之后，$u$ 都能通过走到另一个孩子里改回来，$f_{u,2}=\text{true}$。

我们惊奇地发现，不存在 $f_{u,2/3}$ 同时为 $\text{true}$ 的情况。但是存在 $f_{u,0/1/2/3}$ 全为 $\text{false}$ 的情况。其实也没什么用。

于是我们有了 $\mathcal{O}(n(n+m))$ 的做法。套路化用换根 DP 做到 $\mathcal{O}(n+m)$，考验大家码力的时候到了。

## 代码

Gen 见 [link](https://www.cnblogs.com/XuYueming/p/18313014)。

$\mathcal{O}(n(n+m))$ 和不怎么优雅的 $\mathcal{O}(n+m)$ 的代码见 [link](https://www.cnblogs.com/XuYueming/p/18992600)。

---

## 作者：OIer_Automation (赞：1)

## LG5966. [POI 2016] Hydrorozgrywka

额……我有一个不同与其他做法的设计。

仙人掌肯定考虑圆方树，考虑继用普通树上的 dp 设计：令 $f_i$ 表示从 $i$ 点出发，不走出 $i$ 点所在子树是否必胜。显然这个数组只对圆点有意义，因此转移是较为简单可以分类讨论出来的：

* 如果当前点的子树中存在**可以到达的**必胜点或**可以逼迫对方走的**必败点，那么这个点必胜。

  **可以到达的**必胜点指的是在当前点子树内所有大小大于 $2$ 的方点，在其原图对应环上两个方向上的第一个必胜点（没有则不考虑），且到当前点距离为偶数的点。因为我们选择这个方向走，沿途的点都是必败，所以不会提前走到其他的点，而走到这个点时先手可以走入这个必胜的子树，因此先手必胜。

  **可以逼迫对方走的**必败点指的是在所有大小等于 $2$ 的方点，沿着原图对应边到达的必败点。因为此时后手先走而必败，因此先手必胜。

* 否则如果当前点子树内的没有必胜点的方点的大小和为奇数，那么这个点必胜。

  因为先手一定可以通过走奇环来切换先后手的顺序，而因为其他的方点没有使先手必胜的点，从而当后手先走时其必败，因此先手必胜。

我们可以在子树内方点统计有多少个必胜点到当前点的距离为偶数和没有必胜点的环的大小和，那么转移的总复杂度是 $O(n)$ 的。

然而考虑到我们走完 $i$ 所在子树后可以接着走子树外的环，那么这个做法是否有正确性？答案是有的。考虑如果存在一个圆点在不走出子树的情况下必胜，说明要么走到了一个非根的结点（这种情况正确性显然），要么说明回到根节点的最后一步是先手走的，进一步说明我们可以在这个点走入子树达到切换先后手顺序的目的，而后面面临的选择都是一样的，那么我们可以根据后面的必胜性决定当前的决策，不难看出我们总能找到必胜策略，因此认为这个点必胜是没有问题的。

这样可以求出以某一个点为起点时的必胜性，对于所有点的必胜性只需要进行换根 dp 即可做到 $O(n)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define il inline

const int N=5e5+5,M=1e6+5;

int n,m,vcc,tot,top;
int dfn[N],low[N],stk[N],sum[M],cnt[M];
bitset<N>dp;
vector<int>g[N],h[M],que[N];

il void AddEdge(int u,int v,vector<int> g[]){g[u].push_back(v),g[v].push_back(u);}
il void Tarjan(int u){
    dfn[u]=low[u]=++tot;
    if(g[u].empty())return ;
    stk[++top]=u;
    for(int v:g[u]){
        if(!dfn[v]){
            Tarjan(v),low[u]=min(low[u],low[v]);
            if(low[v]>=dfn[u]){
                int w;AddEdge(++vcc,u,h);
                do AddEdge(vcc,w=stk[top--],h);
                while(v!=w);
            }
        }else low[u]=min(low[u],dfn[v]);
    }
}
il void Dfs1(int u,int f){
    for(int v:h[u])if(v!=f)Dfs1(v,u);
    if(u<=n){
        for(int v:h[u])if(v!=f)sum[u]+=sum[v],cnt[u]+=cnt[v];
        dp[u]=cnt[u]||(sum[u]&1);
    }else{
        int sz=h[u].size(),pre,nxt;
        if(sz==2)return cnt[u]=!dp[h[u][1]],void();
        for(pre=1;pre<sz;pre++)if(dp[h[u][pre]])break;
        if(pre==sz)sum[u]=sz;
        else{
            for(nxt=sz-1;nxt;nxt--)if(dp[h[u][nxt]])break;
            if(!(pre&1)||!((sz-nxt)&1))cnt[u]=1;
        }
    }
}
il void Dfs2(int u,int f){
    if(u<=n){
        sum[u]+=sum[f],cnt[u]+=cnt[f],dp[u]=cnt[u]||(sum[u]&1);
        for(int v:h[u])if(v!=f){
            int _sm=sum[u]-sum[v],_c=cnt[u]-cnt[v];
            if(_c||(_sm&1))que[v-n].push_back(0);
            Dfs2(v,u);
        }
    }else{
        int _u=u-n,sz=h[u].size();
        if(sz==2)return cnt[u]=!que[_u].size(),Dfs2(h[u][1],u);
        for(int i=1;i<sz;i++)if(dp[h[u][i]])que[_u].push_back(i);
        for(int i=1,p=0,_sz=que[_u].size();i<sz;i++){
            int v=h[u][i],pre=-1,nxt=-1;
            sum[u]=cnt[u]=0;
            if(p<_sz&&que[_u][p]<i)p++;
            if(p)pre=que[_u][p-1];
            if(p<_sz&&que[_u][p]==i)p++;
            if(p<_sz)nxt=que[_u][p];
            if(pre==-1&&nxt==-1)sum[u]=sz;
            else{
                if(pre==-1)pre=que[_u].back()-sz;
                if(nxt==-1)nxt=que[_u].front()+sz;
                if(!((i-pre)&1)||!((nxt-i)&1))cnt[u]=1;
            }
            Dfs2(v,u);
        }
    }
}

int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n>>m,vcc=n;
    for(int i=1,u,v;i<=m;i++)cin>>u>>v,AddEdge(u,v,g);
    Tarjan(1),Dfs1(1,0),Dfs2(1,0);
    for(int i=1;i<=n;i++)cout<<(dp[i]?1:2)<<"\n";
}
```

---

## 作者：qwer6 (赞：0)

## 1. Description

给定一张 $n$ 个点 $m$ 条边的无向图，保证每一条边都属于且只属于一个环，两个人在图上玩游戏，游戏开始时在图上的某一个节点放一个棋子，然后两人轮流选择一条与当前棋子所在节点连接的边，走到这条边的另一个节点，已经走过的边不能再走。询问从每个节点开始游戏，先手是否必胜。

## 2. Solution

首先显然可以看出这张图是一张不存在割边的仙人掌图，所以考虑建出圆方树后在圆方树上 DP。

首先考虑在圆方树上 DP 的过程，分开圆点和方点讨论。

对于圆点，我们选择方点**并不是走出一步**，而是选择要进入哪一个环，因此遍历儿子时可以不按照顺序随意遍历。

对于方点，我们相当于从方点的父亲开始遍历整个环，因此需要严格按照点在环上的顺序遍历儿子。

不过幸运的是，我们并不需要自己手动去保证方点的儿子按照点在环上的顺序排序，在建立圆方树的时候就自然而然满足了这个条件了。

对于这种博弈题，在树形 DP 时，我们一般设计的状态就是 $f_u$，表示从 $u$ 出发，向 $u$ 的子树中走，先手是否必胜。

这样对于一颗仙人掌来说显然是不够的，因为对于一般的树，我们走入子树后无法再次走出这棵子树，而对于仙人掌来说，我们在圆方树上走，显然还是可以回到子树的根，走到其他的环中继续游戏的，所以我们需要增加一下状态：$f_u=0/1/2$ 分别表示先手必败，先手必胜且结束的位置不在根，先手必胜但结束的位置还在根，这样我们才可以进行走到其他环中继续游戏这种转移。

那么我们同样分开圆点和方点考虑转移，对于每一个点，我们记录 $cnt_{u,val}$ 表示在 $u$ 的所有儿子 $v$ 中，$f_v=val$ 的点有多少个。

首先考虑圆点，这比较简单，分成三种情况：

1. $cnt_{u,1}\ne 0$，那么先手肯定选择进入这种环，由于先手必胜且结束的位置不在根，所以对于这个圆点，也是先手必胜且结束的位置不在根，将 $f_u$ 设为 $1$.
2. 此时 $u$ 的所有儿子中只有 $0$ 或 $2$ 两种状态，我们只考虑 $2$ 的数量，当 $cnt_{u,2}\equiv 1\pmod1$ 时，先手可以选择调换先后手，那么当不考虑 $2$ 时，如果先手必败，那么就调换先后手，否则不调换，先手必胜，但是结束的位置还在根，所以将 $f_u$ 设为 $2$。
3. 否则，先手必败，$f_u$ 设为 $0$。

其次考虑方点，分为两种情况：

1. $cnt_{u,1}=0$ 且 $cnt_{u,2}=0$，判断环长的奇偶性，奇环将 $f_u$ 设为 $2$，偶环将 $f_u$ 设为 $0$。
2. 考虑遍历环的过程，如果遇到 $f_u=0$ 的节点，那么当前玩家必然不走入这个环，遇到 $f_u=1$ 的节点，当前玩家必胜，遇到 $f_u=2$ 的节点，当前玩家可以选择调换先后手，显然必胜，因此我们正着遍历一次这个环，反着遍历一次这个环，判断第一个遇到的非零值时是先手行动还是后手行动，就可以判断先手是否必胜，如果必胜，那么 $f_u$ 设为 $1$，否则设为 $0$。

以上过程可以写出一个 $O(n^2)$ 的暴力 DP（但是并不好写），为了优化，我们考虑换根。

对于圆点向方点换根，这一过程是简单的，我们只需要去除当前方点对 $cnt_u$ 的影响，重新计算圆点的 dp 值，即得到当前方点为根时该圆点的 dp 值。

但是从方点到圆点换根就不是那么好做了，考虑到以方点为根的情况对于最后的答案没有意义，所以我们略过计算方点为根时方点的 DP 值，尝试计算与方点相连的圆点作为根的时候，这个方点的 DP 值，而前文说过：

> 相当于从方点的父亲开始遍历整个环，因此需要严格按照点在环上的顺序遍历儿子。

这个时候换根了，我们自然也要根据点在环上的顺序遍历儿子，这个乍一看不好做，但其实也比较简单，直接记录整个环，拆环成链，那么对于下标为 $i$ 的儿子，它对应的环就是 $[i,i+len-1]$，那么顺时针遇到的第一个非零值就是 $[i+1,i+len-1]$ 中第一个非零值，同理，逆时针遇到的第一个非零值就是 $[i+1,i+len-1]$ 中最后一个非零值，预处理即可。

最后得到一个时间复杂度 $O(n)$ 的做法。

## 3. Code

```c++
/*by qwer6*/
/*略去缺省源与快读快写*/
const int N=5e5+5;
int n,m;
int f[N<<1],cnt[N<<1][3],nxt[N<<1],val[N<<1],son[N<<1];
struct Graph{
	struct Edge{
		int v,nxt;
	}e[N<<1];
	int n,cnt_edge;
	int head[N<<1];
	void init(int _n=0){
		n=_n,cnt_edge=0;
		for(int i=1;i<=n;i++)head[i]=0;
	}
	void AddEdge(int u,int v){
		e[++cnt_edge]={v,head[u]};
		head[u]=cnt_edge;
	}
}Tr;
namespace BuildTree{
int top,cnt_dcc,cnt_dfn;
int dfn[N],low[N],st[N];
bool vis[N];
struct Graph{
	struct Edge{
		int v,nxt;
	}e[N<<1];
	int n,cnt_edge;
	int head[N];
	void init(int _n=0){
		n=_n,cnt_edge=0;
		for(int i=1;i<=n;i++)head[i]=0;
	}
	void AddEdge(int u,int v){
		e[++cnt_edge]={v,head[u]};
		head[u]=cnt_edge;
	}
}G;
void Tarjan(int u){
	vis[u]=1;
	st[++top]=u;
	dfn[u]=low[u]=++cnt_dfn;
	for(int i=G.head[u],v=G.e[i].v;i;i=G.e[i].nxt,v=G.e[i].v){
		if(!vis[v]){
			Tarjan(v);
			tomin(low[u],low[v]);
			if(low[v]>=dfn[u]){
				++cnt_dcc;
				do{
					Tr.AddEdge(cnt_dcc,st[top]);
				}while(st[top--]!=v);
				Tr.AddEdge(u,cnt_dcc);
			}
		}else tomin(low[u],dfn[v]);
	}
}
void solve(){
	cnt_dcc=n;
	Tarjan(1);
}
}
int cal(int u){
	if(cnt[u][1])return 1;
	if(cnt[u][2]&1)return 2;
	return 0;
}
void dfs(int u){
	cnt[u][0]=cnt[u][1]=cnt[u][2]=0;
	for(int i=Tr.head[u],v=Tr.e[i].v;i;i=Tr.e[i].nxt,v=Tr.e[i].v){
		dfs(v);
		cnt[u][f[v]]++;
	}
	if(u>n){
		int len=0;
		for(int i=Tr.head[u],v=Tr.e[i].v;i;i=Tr.e[i].nxt,v=Tr.e[i].v)
			val[len++]=f[v];
		if(cnt[u][0]==len){
			if(len&1)f[u]=0;
			else f[u]=2;
			return ;
		}
		f[u]=0;
		for(int i=0;i<len;i++){
			if(val[i]){
				if(i&1)f[u]=1;
				break;
			}
		}
		for(int i=len-1;i>=0;i--){
			if(val[i]){
				if((len-i-1)&1)f[u]=1;
				break;
			}
		}
	}else f[u]=cal(u);
}
void redfs(int u,int fa){
	if(u<=n){
		f[u]=cal(u);
		for(int i=Tr.head[u],v=Tr.e[i].v;i;i=Tr.e[i].nxt,v=Tr.e[i].v)
			redfs(v,u);
	}else{
		int len=0;
		cnt[fa][f[u]]--;
		val[len]=cal(fa);
		son[len]=fa;
		len++;
		cnt[fa][f[u]]++;
		for(int i=Tr.head[u],v=Tr.e[i].v;i;i=Tr.e[i].nxt,v=Tr.e[i].v){
			val[len]=cal(v);
			son[len]=v;
			len++;
		}
		int tot=0,tmp=len;
		for(int i=0;i<len;i++){
			if(val[i])tot++;
			val[tmp]=val[i];
			son[tmp]=son[i];
			tmp++;
		}
		nxt[(len<<1)-1]=len<<1;
		for(int i=(len<<1)-2;i>=0;i--){
			nxt[i]=nxt[i+1];
			if(val[i+1])nxt[i]=i+1;
		}
		for(int i=1,v,l,r=0;i<len;i++){
			v=son[i];
			if(val[i])tot--;
			if(tot==0){
				if(len&1)
					cnt[v][2]++;
				else
					cnt[v][0]++;
			}else{
				l=nxt[i];
				while(nxt[r]<i+len)r=nxt[r];
				if((l-i+1)&1||(i+len-r+1)&1)cnt[v][1]++;
				else cnt[v][0]++; 
			}
			if(val[i])tot++;
		}
		for(int i=Tr.head[u],v=Tr.e[i].v;i;i=Tr.e[i].nxt,v=Tr.e[i].v)
			redfs(v,u);
	}
}
signed main(){
	read(n),read(m);
	for(int i=1,u,v;i<=m;i++){
		read(u),read(v);
		BuildTree::G.AddEdge(u,v);
		BuildTree::G.AddEdge(v,u);
	}
	BuildTree::solve();
	dfs(1);	
	redfs(1,0);
	for(int i=1;i<=n;i++)
		puts(f[i]?"1":"2");
}
```

---

