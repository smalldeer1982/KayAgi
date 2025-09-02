# Colored Subgraphs

## 题目描述

Monocarp has a tree, consisting of $ n $ vertices.

He is going to select some vertex $ r $ and perform the following operations on each vertex $ v $ from $ 1 $ to $ n $ :

- set $ d_v $ equal to the distance from $ v $ to $ r $ (the number of edges on the shortest path);
- color $ v $ some color.

A nice coloring satisfies two conditions:

- for each pair of vertices of the same color $ (v, u) $ , there exists a path from $ v $ to $ u $ that only visits vertices of the same color;
- for each pair of vertices of the same color $ (v, u) $ , $ d_v \neq d_u $ .

Note that Monocarp can choose any amount of different colors he wants to use.

For each used color, he then counts the number of vertices of this color. The cost of the tree is the minimum of these numbers.

What can be the maximum cost of the tree?

## 样例 #1

### 输入

```
4
4
1 2
2 3
3 4
5
1 2
1 3
1 4
1 5
3
1 3
3 2
7
3 2
2 5
7 5
3 1
1 6
1 4```

### 输出

```
4
1
3
3```

# 题解

## 作者：OMG_wc (赞：12)

题意是对一棵无根树，进行某种树链剖分后，使得链长的最小值最大，求出这个最大值。

先想想以 $1$ 为根怎么做？当然是从叶子开始，每条链往上生长，一个点如果有多个儿子，会贪心地选择最短链往上生长。

记 $f_u$ 表示 $u$ 的每个儿子的所在的链长集合，其中链长指的是链中点的个数，叶节点的 $f_u=\varnothing$。

那么 $u$ 会归属于其中的最短链，而次短链开始的其他链长度就永远停留在了原地，所以最终答案不会超过所有 $f_u$ 里的次小值。

最终答案也不会超过 $f_1$ 的最小值加 $1$，那么以 $1$ 为根的答案就算出来了。

然后用换根法来算其他结点为根时的答案，需要一个全局`multiset`维护所有点的次小值集合。具体而言，把根从 $u$ 切换到儿子 $v$ 时，先在 $f_u$ 里删除 $v$ 对 $u$ 的贡献，然后在 $f_v$ 里加上 $u$ 对 $v$ 的贡献，处理完 $v$ 子树后再还原。

时间复杂度 $O(n\log n)$，代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF = 0x3f3f3f3f;
const LL mod = 1e9 + 7;
const int N = 200005;

vector<int> G[N];
multiset<int> f[N]; 
multiset<int> se;   
int ans;

int getlen(int u) {
    return f[u].size() == 0 ? 1 : *f[u].begin() + 1;
}
void add(int u, int val) {
    if (f[u].size() >= 2) se.erase(se.find(*next(f[u].begin())));
    f[u].insert(val);
    if (f[u].size() >= 2) se.insert(*next(f[u].begin()));
}
void del(int u, int val) {
    if (f[u].size() >= 2) se.erase(se.find(*next(f[u].begin())));
    f[u].erase(f[u].find(val));
    if (f[u].size() >= 2) se.insert(*next(f[u].begin()));
}

void dfs1(int u, int fa) {
    for (auto v : G[u]) {
        if (v == fa) continue;
        dfs1(v, u);
        f[u].insert(getlen(v));
    }
    if (f[u].size() >= 2) se.insert(*next(f[u].begin()));
}
void dfs2(int u, int fa) {
    ans = max(ans, min(getlen(u), se.empty() ? INF : *se.begin()));
    for (auto v : G[u]) {
        if (v == fa) continue;
        del(u, getlen(v));
        add(v, getlen(u));
        dfs2(v, u);
        del(v, getlen(u));
        add(u, getlen(v));
    }
}

int main() {
    int _;
    scanf("%d", &_);
    while (_--) {
        int n;
        scanf("%d", &n);
        se.clear();
        for (int i = 1; i <= n; i++) G[i].clear(), f[i].clear();
        for (int i = 1; i < n; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        ans = 0;
        dfs1(1, 0);
        dfs2(1, 0);
        printf("%d\n", ans);
    }
    return 0;
}
```





---

## 作者：2018ljw (赞：1)

简单清新小换根。

枚举 $r$ 为根，显然每个合法的颜色连通块必然是一条直上直下的链。考虑如何最大化最短链。

设 $dp_x$ 表示最优情况下 $x$ 子树到 $x$ 的路径长度，$g_x$ 表示 $x$ 子树内，已经确定长度的路径的最小长度。

显然对于每个点，我们肯定是要选 $dp$ 最小的接到 $x$ 上。因此有 $dp_x=\min\{dp_y\}+1$，$g_x=\min\{g_y,\operatorname{smin}\{dp_y\}\}$。其中 $\operatorname{smin}$ 表示非严格次小值。那么根为 $r$ 的答案即为 $\min\{g_{r},dp_{r}\}$。

维护每个点前三小的 $dp$ 和前二小的 $g$ 即可换根。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
int n,res;
vector<int>g[200001];
int dp[200001],h[200001];
void dfs0(int x,int fr){
	h[x]=n+1;
	int i;
	int mn=n+1,smn=n+1;
	for(i=0;i<g[x].size();i++){
		int y=g[x][i];
		if(y==fr)continue;
		dfs0(y,x);
		h[x]=min(h[x],h[y]);
		if(dp[y]<smn)smn=dp[y];
		if(smn<mn)swap(mn,smn);
	}
	if(mn==n+1)dp[x]=1;
	else dp[x]=mn+1,h[x]=min(h[x],smn);
}
void dfs1(int x,int fr){
	res=max(res,min(h[x],dp[x]));
	int i,j;
	int mg=n+1,smg=n+1,tg=h[x];
	int mn=n+1,smn=n+1,tmn=n+1,td=dp[x];
	for(i=0;i<g[x].size();i++){
		int y=g[x][i];
		smg=min(smg,h[y]);
		if(smg<mg)swap(smg,mg);
		tmn=min(tmn,dp[y]);
		if(tmn<smn)swap(tmn,smn);
		if(smn<mn)swap(smn,mn);
	}
	for(i=0;i<g[x].size();i++){
		int y=g[x][i];
		if(y==fr)continue;
		if(h[y]==mg)h[x]=smg;
		else h[x]=mg;
		if(dp[y]==mn||dp[y]==smn)h[x]=min(h[x],tmn);
		else h[x]=min(h[x],smn);
		if(dp[y]==mn){
			if(smn==n+1)dp[x]=1;
			else dp[x]=smn+1;
		}
		else dp[x]=mn+1;
		int fmn=n+1,fsm=n+1;
		h[y]=n+1;
		for(j=0;j<g[y].size();j++){
			int z=g[y][j];
			fsm=min(fsm,dp[z]);
			if(fsm<fmn)swap(fsm,fmn);
			h[y]=min(h[y],h[z]);
		}
		h[y]=min(h[y],fsm);
		dp[y]=fmn+1;
		dfs1(y,x);
		dp[x]=td;h[x]=tg;
	}
}
void solve(){
	int i;
	scanf("%d",&n);res=0;
	for(i=1;i<=n;i++)g[i].resize(0);
	for(i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		g[x].push_back(y);
		g[y].push_back(x);
	}
	dfs0(1,0);
	dfs1(1,0);
	printf("%d\n",res);
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--)solve();
}
```

---

## 作者：why_cb (赞：1)

~~remake 了无数遍，我是迅哥~~

---

题意：给定一颗无根树，求覆盖满整棵树一组深度只可能递增的链的长度最小值最大。

首先考虑定根情况，由于每个结点只能与它的一个儿子（一条链）相连，所以每次贪心连最短的链必定是最优的。

其次，很容易想到换根去统计所有结点为根时的答案取最大值。

我们先保存原来所有的链长。

现在考虑以 $u$ 为根的一棵树，对于它的子结点 $v$，进行换根，形成一颗以 $v$ 为根的树。

我们分别讨论 $u$ 跟 $v$。

对于 $u$ 来说，它少了一颗子树 $v$，当前仅当 $v$ 是 $u$ 原来子节点中的最短的链时，会对 $u$ 的链产生影响。此时，我们删掉原来以 $u$ 结点为顶点的链（此时 $u$ 为根，必定是链的顶点），再把 $u$ 子结点中的次小值的那条链删除把 $u$ 连上那条链进行插入。

对于 $v$ 来说，它多了一颗子树 $u$，若 $u$ 的新值小于 $v$ 原来子结点的最小值，同上，删掉原来的 $v$ 链，加入原来 $v$ 子结点的最小链，将次小值赋为最小值，删掉 $u$ 链，将 $v$ 连上 $u$ 插入，将 $v$ 的子结点的最小值设为 $u$；若 $u$ 小于 $v$ 原来子节点中的次小值，直接将次小值赋为 $u$。

当回溯时，将所有的值恢复成进入下一层之前，将删除的插入，将插入的删除。

每个结点为根的答案便是所有链长的最小值。

可用 multiset 进行简单维护。

---
Code：

```cpp
void dfs1(int u,int fa)//第一遍以1为根，统计答案。
{//f 为到当前结点的链长，Min1 Min2 分别为子节点中链长的最小值和次小值。
    Min1[u]=Min2[u]=INF;
    for(int i=head[u];i;i=e[i].nxt)
    {
        int v=e[i].to;
        if(v==fa) continue;
        dfs1(v,u);
        if(f[v]<Min1[u]) Min2[u]=Min1[u],Min1[u]=f[v];
        else if(f[v]<Min2[u]) Min2[u]=f[v];
    }
    f[u]=(Min1[u]==INF?0:Min1[u])+1;
    auto it=link.find(Min1[u]);
    if(it!=link.end()) link.erase(it);
    link.insert(f[u]);//统计开始的所有链长
}

void dfs2(int u,int fa)
{
    ans=max(ans,*link.begin());
    for(int i=head[u];i;i=e[i].nxt)
    {
        int v=e[i].to,t1=f[u],t2=f[v],vm1=Min1[v],vm2=Min2[v];
        vector<int> del,ins;
        if(v==fa) continue;
        if(f[v]==Min1[u])//修改 u。
        {
            auto it=link.find(f[u]);
            if(it!=link.end()) link.erase(it),del.push_back(f[u]);
            it=link.find(Min2[u]);
            if(it!=link.end()) link.erase(it),del.push_back(Min2[u]);
            f[u]=(Min2[u]==INF?0:Min2[u])+1;
            link.insert(f[u]);
            ins.push_back(f[u]);
            link.insert(f[v]);
            ins.push_back(f[v]);
        }
        if(f[u]<Min1[v])//修改 v。
        {
            auto it=link.find(f[v]);
            if(it!=link.end()) link.erase(it),del.push_back(f[v]);
            if(Min1[v]!=INF) link.insert(Min1[v]),ins.push_back(Min1[v]);
            Min2[v]=Min1[v];
            Min1[v]=f[u];
            it=link.find(f[u]);
            if(it!=link.end()) link.erase(it),del.push_back(f[u]);
            f[v]=f[u]+1;
            link.insert(f[v]);
            ins.push_back(f[v]);
        }
        else if(f[u]<Min2[v]) Min2[v]=f[u];
        dfs2(v,u);
        f[u]=t1;//还原
        f[v]=t2;
        Min1[v]=vm1;
        Min2[v]=vm2;
        for(auto j:del) link.insert(j);
        for(auto j:ins)
        {
            auto it=link.find(j);
            link.erase(it);
        }
    }
}
```

---

## 作者：tianhangj (赞：1)

机房同学说此题 $O(n)$ 很烦，于是我写了一个。

简要题意：任意选取根，对树进行树链剖分，求最短链最大的长度。

现在考虑定根的 dp 方程：  
$up_i$ 表示节点 $i$ 在子树最优的情况下从这个节点向下属于同一个链的长度。  
$minlen_i$ 表示节点 $i$ 在子树最优的情况下子树内链的最短长度（不包括此节点向上的链）

这个 dp 状态及其容易贪心转移。  
子节点中长度非零的最短链就应该是当前节点 $up_i$ 选择的向上扩展的链。  
余下所有非零长度的链都要和 $minlen_i$ 取 $\min$ 来记录父亲节点的 $minlen$。

转移代码如下（码风比较奇怪）：
```cpp
struct DpType {
    ll minl, up;
    DpType( ll minl_ = numeric_limits<ll>::max(), ll up_ = 0 ) {
        minl = minl_, up = up_;
    }
    // 合并两个 dp 状态
    DpType operator + ( const DpType rhs ) const {
        ll n_minl = min(minl, rhs.minl), n_up;
        ll up1 = min(up, rhs.up ), up2 = max(up, rhs.up );
        #define RT(a,b); return DpType(a,b);
        if ( up1 == 0 && up2 == 0 ) {
            RT(n_minl,0ll);
        } else if ( up1 == 0 ) {
            RT(n_minl, up2);
        } else {
            RT(min(n_minl,up2), up1);
        }
    }
    // 将当前点接到 up 上
    DpType operator () () const {
        return DpType(minl,up+1);
    }
};
```

接下来进行一个换根，但是我不会标准的换根 dp，所以想了一个极其奇怪的做法：

引理：对于每个节点，当某个节点 $fa$ 确定为它的根时，dp 的状态不随根改变。  
（显然成立，故不证明）

于是我们可以记忆化，可以证明，由于总共只有 $n-1$ 条边，因此子节点和父节点的不同的关系总共最多只有 $2n-2$ 个，因此总状态数是 $O(n)$

然后进行一个乱搞，直接顺序钦定根进行处理，搭配记忆化，使用聚合分析可知，dfs 函数最多调用 $O(n)$ 次。

dfs 函数如下：
```cpp
DpType node::dfs( ll fa, ll _id )  {
    if ( nxt.size() == 1 ) return DpType(numeric_limits<ll>::max(),1);
    while ( l < _id - 1 ) {
        update(l+1, nd[nxt[l+1].first].dfs(id, nxt[l+1].second));
    }
    while ( r > _id + 1 ) {
        update(r-1, nd[nxt[r-1].first].dfs(id, nxt[r-1].second));
    }
    DpType result = (Pre(_id-1)+Suf(_id+1))();
    return result;
}
```

这里用到一个小 trick：  
在节点上记录所有相邻节点的 dp 状态，这样可以保证没有多余的 dfs 调用。  
update 即为记录状态的函数。

还有一个：  
利用相邻节点 dp 状态的前后缀来进行处理，这样返回答案是 $O(1)$ 的。

到这里基本上核心的内容都有了。

---

## 作者：SlyCharlotte (赞：1)

[更好的阅读体验？](https://zhuanlan.zhihu.com/p/610522558)

## 题目大意

给你一棵树，$n$ 个节点。你需要给每个节点染色，使得任意颜色相同的节点之间的路径上的点颜色也与前面两个点相同。

$cnt_i$ 表示颜色为 $i$ 的节点数，找到 $\min cnt_i$ 的最大值。

## 简要分析

先不考虑，根不固定的情况，强制钦定 $r =  1$，这里 $r$ 指根节点。

我们发现答案通过二分可以转化成判定性问题，即能否将树划分成若干条自底向上目长度至少为 $k$ 的链。

设 $dep_u$ 表示，自底向上的到达 $u$ 的最短长度，$minx$ 表示么 $x$ 的儿子中 $dep_v$ 的最小值。

显然对于叶子有，$dep_w=1$，而对于非时子节点，显然有转移 $dep_w=minx +1$。

对于不合法的情况，$u$ 存在两个儿子，他们的 $dep_w$ 都要小于 $k$，因为 $u$ 只能和一个儿子往上拼接，两个就不行了，这个记为情況 $1$。

最终只需要判断一下 $dep_1$， 是否不小于 $k$ 即可，这个记为情况 $2$。

然后就是，$r$ 不固定的情况，当然，假设说 $r = 1$ 可行那么我们就直接输出了。

如果情况 $1$ 不合法，子树以外的点作为根是不可能的，因为这个子树的本身结构是不变的，所以我们就需要将 $minx$ 对应的节点 $v$ 变成根。

因为这种情况不合法一定是说明了这个点到 $u$ 距离是小于 $k$ 的，而肯定还有一个 $v’$ 到 $u$ 的距离是小于 $v$ 的，所以我们本质上是把 $v$ 到 $v’$ 的路径涂成一种颜色。

如果情况 $2$ 不合法，那么我们同理，也是找 $minx$ 就行了。

总时间复杂度 $O(n)$。

## 代码实现

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

typedef long long ll;
const ll maxn = 2e5 + 7;
const ll INF = 1e18 + 7, MOD = 998244353;

inline ll read() {
    char cCc;
    ll xXx = 0, wWw = 1;
    while (cCc < '0' || cCc > '9')
        (cCc == '-') && (wWw = -wWw), cCc = getchar();
    while (cCc >= '0' && cCc <= '9')
        xXx = (xXx << 1) + (xXx << 3) + (cCc ^ '0'), cCc = getchar();
    xXx *= wWw;
    return xXx;
}

inline void write(ll xXx) {
    if (xXx < 0)
        putchar('-'), xXx = -xXx;
    if (xXx > 9)
        write(xXx / 10);
    putchar(xXx % 10 + '0');
}

ll n, tx, ty, dep[maxn], minnode[maxn];
vector<ll> G[maxn];

bool dfs(ll u, ll fa, ll k) {
    ll x = 0, y = 0, miny = INF, minx = INF;
    for (auto v : G[u]) {
        if (v == fa)continue;
        if (!dfs(v, u, k))return false;
        if (dep[v] <= minx)y = x, miny = minx, x = minnode[v], minx = dep[v];
        else if (dep[v] <= miny)y = minnode[v], miny = dep[v];
    }

    if (miny < k) {
        tx = x, ty = y;
        return false;
    }

    if (x == 0)dep[u] = 1, minnode[u] = u;
    else dep[u] = minx + 1, minnode[u] = x;

    if (!fa) {
        if (dep[u] < k)tx = minnode[u], ty = 1;
        return dep[u] >= k;
    }

    return true;
}

bool check(ll k) {
    if (dfs(1, 0, k)) return true;
    else if (dfs(tx, 0, k) || dfs(ty, 0, k))return true;
    return false;
}

void solve() {
    n = read();
    for (ll i = 1; i < n; i++) {
        ll u = read(), v = read();
        G[u].push_back(v);
        G[v].push_back(u);
    }

    ll l = 0, r = n, ans = 0;
    while (l <= r) {
        ll mid = (l + r) >> 1;
        if (check(mid))
            ans = mid, l = mid + 1;
        else r = mid - 1;
    }

    cout << ans << '\n';
    for (ll i = 1; i <= n; i++)G[i].clear();
}

signed main() {
//    freopen("code.in","r",stdin);
//    freopen("code.out","w",stdout);
    ll T = read();
    while (T--)solve();
    return 0;
}
```


---

## 作者：Jerrycyx (赞：0)

本文来源：[洛谷专栏](https://www.luogu.com.cn/article/slp7xo0s)、[博客园](https://www.cnblogs.com/jerrycyx/p/18711968)、[CSDN](https://blog.csdn.net/Jerrycyx/article/details/145597655)。

-----

> 简化题意：给定一棵无根树，选择一个树根，构造一种树链剖分使最短的链最长。（只用输出这个最大值）

关键词：“无根树”，而且还要“选择一个最优的节点 $r$”，特征明显，试着往换根 DP 的方面去做。

首先需要求出以 $1$ 为根时，树链剖分使最短链的最大长度。

观察一棵树的结构可以发现，如果把叶节点视为树链开端，那么树链末端只会是根节点或者树上路径分叉的地方。从动态的角度思考，两条树链从叶节点开始延伸，在其 LCA 处会合，此时只能保留一条树链继续向上走，那么自然**优先选择短的那条**，否则这个子树上的答案就此确定为较短链长度，再无可能增大了。

#### 第一次 DP

对于一个节点，首先我们必须要知道所有以它的子节点为末端的树链长度。所以记 $F_x$ 表示以 $x$ 为末端的树链长度，那么根据上面的贪心策略，有（$x$ 为父节点，$y$ 为子节点）：

$$F_x=\min\{F_y\}+1$$

其次，别的未被选中继续延伸的树链也要纳入考虑。设 $G_x$ 表示 $x$ 的子树中没有继续延伸的最短树链长度，其由两个部分组成：所有子节点 $G$ 值的最小值和所有点 $F$ 值的**次小值**（最小值已经延伸出去了）。

$$G_x=\min( \operatorname{secmin}\{F_y\}, \min\{G_y\} )$$

（$\operatorname{secmin}$ 表示次小值）

最后以 $1$ 为根的答案就是 $\min\{F_x,G_x\}$。

#### 第二次 DP

> 换根 DP 考虑的事情是很 Simple 的，就是合并子树外的信息，但是总会有一些讨厌的时候，现在恰好最优的东西刚好就在这个子树内，那我们就只能转移次要的转移点。——[吾王美如画](https://www.luogu.com.cn/user/118273)

本题中你将会遇到大量的这种情况。

按照惯例，换根 $DP$ 的转移方程中出现了最小值，那么就需要记录次小值。所以我们先将 $F$ 扩展成两层 $F_{x,0}$ 和 $F_{x,1}$，把 $G$ 也扩展成两层 $G_{x,0}$ 和 $G_{x,1}$，各自分别表示最小值和次小值。

然后我们就可以丢掉 $\operatorname{secmin}\{F_y\}$，它其实就是 $F_{x,1}$。

接着我们就会发现，转移的时候也同时**直接**需要次小值（而不仅仅是把它作为最小值的备用方案）。此时若 $y$ 恰好是 $F_{x,1}$ 的更新来源，**我们就还需要一个备用方案：次小值的次小值——即第三小值**，用 $F_{x,2}$ 表示。

对于换根 DP 来说上面的原始转移方程不是很好用，它不是一个纯 $\min$ 格式。所以我们需要一些新的状态和新的方程，用小写字母表示。

$F$ 方程中最后那个 $1$ 可以在用到它的时候加，而 $G$ 可以直接拆成两部分（其中一部分可以直接用 $F$ 表示），**两部分可以等到要用到时候再合并起来当作原来的 $G$ 计算**。

$f_{x,0/1/2}$ 表示**不加上 $x$ 本身**的最短/次短/第三短候选树链的长度，转移方程不变只是叶节点的值变为 $0$，有 $F_x=f_x+1$；$g_x$ 则表示以 $x$ 为根的子树中**不包括在 $x$ 处才断开的树链情况下**的最短链长度，那么 $G_x=\min(f_{x,1},g_x)$，它的转移方程可以由之前的方程略微修改得来：

$$g_x=\min\{G_y\}=\min\{\min(f_{y,1},g_y)\}$$

最后答案为 $\max\{\min(F_x,G_x)\}=\max\{\min(f_{x,0}+1,f_{x,1},g_x)\}$

#### 代码细节

这道题细节超多，但是只要记住这两条原则就行了：

+ 不要在叶子节点直接设定 $f_{x,0}$ 为 $0$ 而应该在它的父节点处特判（不然这个 $0$ 就再也无法被更新掉了），因为在换根的时候哪些点是叶子节点是会动态变化的，同时也需要动态地检查。
+ 无论第一次 DP 的转移方程写成什么样子，第二次 DP 判断 $x$ 的结果是否由 $y$ 转移而来时都必须用**完全一模一样**的转移方程。

-----

Codeforces AC 记录：[点击这里](https://codeforces.com/problemset/submission/1796/305800148)

代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;

const int N=2e5+5,INF=0x3f3f3f3f;
int n;

struct Allan{
	int to,nxt;
}edge[N<<1];
int head[N],idx;
inline void add(int x,int y)
{
	edge[++idx]={y,head[x]};
	head[x]=idx;
	return;
}

int f[N][3],g[N][2];
inline void upd(int &src1,int &src2,int x) //更新最小值和次小值 
{
	if(x<src1) src2=src1,src1=x;
	else if(x<src2) src2=x;
	return;
}
inline void upd(int &src1,int &src2,int &src3,int x) //更新最小值、次小值和第三小值 
{
	if(x<src1) src3=src2,src2=src1,src1=x;
	else if(x<src2) src3=src2,src2=x;
	else if(x<src3) src3=x;
	return;
}
int sz[N]; //记录子树大小以便两次 DP 都能动态判断叶节点 
void DFS1(int x,int fa)
{
	sz[x]=1;
	for(int i=head[x];i;i=edge[i].nxt)
	{
		int y=edge[i].to;
		if(y==fa) continue;
		DFS1(y,x);
		sz[x]+=sz[y];
		upd(f[x][0],f[x][1],f[x][2],(sz[y]==1?0:f[y][0])+1); //特判叶节点 
		upd(g[x][0],g[x][1],min(f[y][1],g[y][0]));
	}
	return;
}
void DFS2(int x,int fa)
{
	for(int i=head[x];i;i=edge[i].nxt)
	{
		int y=edge[i].to;
		if(y==fa) continue;
		int fx0,fx1;
		int op=(sz[y]==1?0:f[y][0])+1; //必须保证和上面的转移方程形式一模一样 
		//最小值、次小值最多只能有一个是由y转移而来的（只有我第一次没意识到这个吗？） 
		if(f[x][0]==op) //最小值由y转移而来，不得不选 
		{
			fx0=f[x][1];
			fx1=f[x][2];
		}
		else
		{
			fx0=f[x][0];
			if(f[x][1]==op) fx1=f[x][2]; //次小值由y转移而来，不得不选第三小值 
			else fx1=f[x][1];
		}
		int gx;
		if(g[x][0]==min(f[y][1],g[y][0])) gx=g[x][1]; //最小值由y转移而来，注意这里的方程也要和之前一模一样 
		else gx=g[x][0];
		upd(f[y][0],f[y][1],f[y][2],(n-sz[y]==1?0:fx0)+1); //重点：动态判断x成为y的子节点后是不是叶节点 
		upd(g[y][0],g[y][1],min(fx1,gx));
		DFS2(y,x);
	}
	return;
}

int main()
{
	int T; scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1;i<n;i++)
		{
			int x,y; scanf("%d%d",&x,&y);
			add(x,y),add(y,x);
		}
		for(int i=1;i<=n;i++)
		{
			f[i][0]=f[i][1]=f[i][2]=INF;
			g[i][0]=g[i][1]=INF;
		}
		DFS1(1,0);
		DFS2(1,0);
		int ans=0;
		for(int i=1;i<=n;i++)
			ans=max(ans,min({f[i][0]+1,f[i][1],g[i][0]}));
		printf("%d\n",ans);
		for(int i=1;i<=n;i++)
			head[i]=0;
	}
	return 0;
}
```

---

## 作者：PosVII (赞：0)

**前言**

------------

`换根dp`。

**题解**

------------

一眼换根，但是确实挺难调的，可以 $O(n)$，但是用 `map` 就好写多了。

首先不考虑根不定的情况，这个时候题目就变成了把树划分成不能拐角的链，要求最小链的最大大小。

这时候就是一个 `树形dp` 再加上一点小小的贪心：因为对于结点 $p$，其每一个儿子 $tmp$ 都在且仅在一条链，此时这个结点 $p$ 就划归与所有儿子所在的链中最小的一条就行了。可以 $O(n)$ 处理。维护每个根所在的链的大小和其子树中不在 $p$ 的链的最小值。

但是此时根是不定的，考虑换根。可以证明，每次对于一个点，把它变成根只需要考虑其父亲的其他子结点所在树的状态，用 `map` 存储即可快速查找最小值，然后就很好实现了。

**code**

------------

```
#include<bits/stdc++.h>
template<typename G>inline void read(G&x) {G f=1;x=0;char ch=getchar();while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();if(ch=='-') f=-1,ch=getchar();while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=getchar();x*=f;}
using namespace std;
const int MAXN=2e5+5;
int T,n,u,v,f[MAXN],g[MAXN],ans;
vector<int> G[MAXN];
map<int,int> sf[MAXN],sg[MAXN];
void dfs(int p,int las) {
	int idx=0;f[p]=1e6;sf[p].clear(),sg[p].clear();
	for(auto tmp:G[p]) {
		if(tmp!=las) {
			dfs(tmp,p);
			++sf[p][f[tmp]],++sg[p][g[tmp]];
			f[p]=min(f[p],f[tmp]);
			if(!idx||g[idx]>g[tmp]) idx=tmp;
		}
	}
	g[p]=g[idx]+1;
	for(auto tmp:G[p]) {
		if(tmp!=las&&tmp!=idx) {
			f[p]=min(f[p],g[tmp]);
		}
	}
}
int fs[MAXN],gs[MAXN];
void bfs(int p,int las) {
	if(p!=1) {
		int FS=fs[las],GS=gs[las];
		--sf[las][f[p]],--sg[las][g[p]];
		if(!sf[las][f[p]]) sf[las].erase(f[p]);
		if(!sg[las][g[p]]) sg[las].erase(g[p]);
		auto it1=sf[las].begin(),it2=sg[las].begin();
		if(it1!=sf[las].end()) FS=min(FS,it1->first);
		if(it2!=sg[las].end()) {
			if(it2->first+1<GS) {
				FS=min(FS,GS-1);
				GS=it2->first+1;
				if(it2->second==1) ++it2;
				if(it2!=sg[las].end()) FS=min(FS,it2->first);
			}
			else FS=min(FS,it2->first);
		}
		else if(las==1) GS=1;
		++sf[las][f[p]],++sg[las][g[p]];
		fs[p]=FS,gs[p]=GS+1;
		int SF=1e6,SG=1e6;
		auto it3=sf[p].begin(),it4=sg[p].begin();
		if(it3!=sf[p].end()) SF=min(SF,it3->first);
		if(it4!=sg[p].end()) {
			SG=min(SG,it4->first);
			if(it4->second==1) ++it4;
			if(it4!=sg[p].end()) SF=min(SF,it4->first);
		}
		SF=min(SF,FS);
		if(SG>GS) SF=min(SF,SG),SG=GS;
		else SF=min(SF,GS);
		ans=max(ans,min(SF,SG+1));
	}
	for(auto tmp:G[p]) {
		if(tmp!=las) {
			bfs(tmp,p);
		}
	}
}
signed main() {
	read(T);
	while(T--) {
		read(n);
		for(int i=1;i<=n;++i) G[i].clear();
		for(int i=2;i<=n;++i) {
			read(u),read(v);
			G[u].emplace_back(v);
			G[v].emplace_back(u);
		}
		dfs(1,0);gs[1]=fs[1]=1e6;
		ans=min(f[1],g[1]);
		bfs(1,0);
		printf("%d\n",ans);
	}
	return 0;
}
```

---

