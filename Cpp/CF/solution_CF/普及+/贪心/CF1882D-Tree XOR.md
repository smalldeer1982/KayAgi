# Tree XOR

## 题目描述

You are given a tree with $ n $ vertices labeled from $ 1 $ to $ n $ . An integer $ a_{i} $ is written on vertex $ i $ for $ i = 1, 2, \ldots, n $ . You want to make all $ a_{i} $ equal by performing some (possibly, zero) spells.

Suppose you root the tree at some vertex. On each spell, you can select any vertex $ v $ and any non-negative integer $ c $ . Then for all vertices $ i $ in the subtree $ ^{\dagger} $ of $ v $ , replace $ a_{i} $ with $ a_{i} \oplus c $ . The cost of this spell is $ s \cdot c $ , where $ s $ is the number of vertices in the subtree. Here $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Let $ m_r $ be the minimum possible total cost required to make all $ a_i $ equal, if vertex $ r $ is chosen as the root of the tree. Find $ m_{1}, m_{2}, \ldots, m_{n} $ .

 $ ^{\dagger} $ Suppose vertex $ r $ is chosen as the root of the tree. Then vertex $ i $ belongs to the subtree of $ v $ if the simple path from $ i $ to $ r $ contains $ v $ .

## 说明/提示

In the first test case, to find $ m_1 $ we root the tree at vertex $ 1 $ .

1. In the first spell, choose $ v=2 $ and $ c=1 $ . After performing the spell, $ a $ will become $ [3, 3, 0, 1] $ . The cost of this spell is $ 3 $ .
2. In the second spell, choose $ v=3 $ and $ c=3 $ . After performing the spell, $ a $ will become $ [3, 3, 3, 1] $ . The cost of this spell is $ 3 $ .
3. In the third spell, choose $ v=4 $ and $ c=2 $ . After performing the spell, $ a $ will become $ [3, 3, 3, 3] $ . The cost of this spell is $ 2 $ .

Now all the values in array $ a $ are equal, and the total cost is $ 3 + 3 + 2 = 8 $ .

The values $ m_2 $ , $ m_3 $ , $ m_4 $ can be found analogously.

In the second test case, the goal is already achieved because there is only one vertex.

## 样例 #1

### 输入

```
2
4
3 2 1 0
1 2
2 3
2 4
1
100```

### 输出

```
8 6 12 10 
0```

# 题解

## 作者：西瓜nd (赞：12)

[题目传送门](https://www.luogu.com.cn/problem/CF1882D)

## 题意简述

给定一棵树，每个点有点权 $a_i$。

每次可以选择一个点 $x$ 和一个值 $c$，将以点 $x$ 为根的子树内的所有点的权值都异或上 $c$，代价为 $s_x\times c$，$s_x$ 代表子树大小。

对于每个 $i\in[1,n]$，点 $i$ 为根时分别求出让所有点权都相等的最小代价。

## 题目分析

考虑一个以 $u$ 为根的子树，其儿子为 $son_u$。

因为每次异或都会对一整个子树进行，假设子树 $u$ 中存在不同权值的点，那么对 $u$ 操作后子树内的点权值仍然不会相等，这是不好的。所以在处理这颗子树前，应该先让每个 $son_u$ 为根的子树内权值相等。

自然可以想到设计一个 $dp_i$ 状态，代表对以 $i$ 为根的子树操作后权值都相等的代价。

接着考虑异或的策略。

贪心的想一下，可以发现对儿子操作比起对根操作会更优，也就是把所有点都异或成根的值更优。

怎么证明呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/boh47ww6.png)

如图，假设现在有这样一颗树（为了方便，让点 $2,3$ 都代表以其为根的一颗子树，且其子树内权值都相等）。现在有两种操作方案，一个是把所有点都异或成根的值，另一种是把所有点都异或成另一个值。

方案一只要把每个儿子节点 $son_u$ 都异或上 $(a_u\oplus a_{son_u})$ 即可，花费代价为 $w_1=s_2\times(a_1 \oplus a_2)+s_3\times(a_1 \oplus a_3)$。

方案二需要将所有点都异或成同一个值，设对点 $i$ 异或的值为 $c_i$ $(c_i\neq 0)$，那么就有
$$
a_1\oplus c_1=a_2\oplus c_1\oplus c_2=a_3\oplus c_1\oplus c_3
$$
都异或一下 $c_1$ 就有
$$
a_1=a_2\oplus c_2=a_3\oplus c_3
$$
移项，有
$$
a_1\oplus a_2=c_2 , a_1\oplus a_3=c_3
$$

方案一花费代价就变为 $w_1=s_2\times c_2+s_3\times c_3$。

方案二花费代价为 
$$
\begin{aligned}
w_2&=s_1\times c_1+s_2\times c_2+s_3\times c_3\\
&=s_2\times (c_1+c_2)+s_3\times (c_1+c_3) +c_1
\end{aligned}
$$

于是 $w_1< w_2$ ，并且显然其他情况也成立。

所以，把所有点都异或成根的值一定会更优。

有了这个，就非常简单了。我们可以将 dp 状态改为， $dp_i$ 代表对以 $i$ 为根的子树操作后权值都等于根的权值的代价。状态转移方程为
$$
dp_i=\sum_{j\in son_i} (dp_j+s_j\times (a_i\oplus a_j))
$$

然后换根 dp 即可，复杂度 $O(n)$。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
const int maxn=200005;
int T,n;
int a[maxn];
int dp[maxn],f[maxn];
int siz[maxn];
vector<int>g[maxn];

void dfs1(int x,int fath){
    siz[x]=1;
    for(int to:g[x]){
        if(to==fath)continue;
        dfs1(to,x);
        siz[x]+=siz[to];
        dp[x]+=dp[to]+siz[to]*(a[x]^a[to]);
    }
    f[x]=dp[x];
}

void dfs2(int x,int fath){
    for(int to:g[x]){
        if(to==fath)continue;
        f[to]+=f[x]-(dp[to]+siz[to]*(a[x]^a[to]))+(n-siz[to])*(a[x]^a[to]);
        dfs2(to,x);
    }
}

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];

    for(int i=1;i<n;i++){
        int x,y;
        cin>>x>>y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    dfs1(1,0);
    dfs2(1,0);

    for(int i=1;i<=n;i++){
        cout<<f[i]<<" ";
    }
    cout<<'\n';

    for(int i=1;i<=n;i++){
        dp[i]=f[i]=siz[i]=0;
        g[i].clear();
    }
}

signed main(){
    cin>>T;

    while(T--){
        solve();
    }
    
    return 0;
}

```



---

## 作者：xkcdjerry (赞：5)

所有题解的解法都是换根 dp，这里给个树上差分做法。

首先考虑如何对单个根解决：  
令 $b_x=a_x \oplus a_{fa_x}$，那么显然除了对 $x$ 本身的操作，任何操作都不会影响 $b_x$ 的值。  
那么为了让所有 $a_x$ 相同，即让所有 $b_x(x \neq root)$ 变为 $0$，需要的代价就是 $-na_{root}+\sum_{i=1}^n b_i \times sz_i$。

这里需要特判 $root$ 并删去很不自然，考虑一个经典 trick：根的权值不重要的时候可以把权值挂在连向父亲的边上。那么有：  
$$w_i=a_{u_i} \oplus a_{v_i}$$
$$Ans=\sum_{i=1}^{n-1} w_i \min(sz_{u_i},sz_{v_i})$$
（$\min$ 本质是为了选择出这个边最早是哪个点的权值）

（以下为方便，不失一般性的假设 $u_i$ 在根为 $1$ 时为 $v_i$ 的父亲，且 $v_i$ 子树大小为 $sv$）

我们发现一个好玩的东西：这个式子里除了 $\min(sz_{u_i},sz_{v_i})$ 一项**均与 $root$ 无关**，且这一项只有两个取值：  
根在 $v_i$ 子树内时这项为 $n-sv$，否则为 $sv$。（画图易证）

那么我们可以先以 $1$ 为根 `dfs` 一遍，然后分别枚举每个边计算它对每个根的贡献。即对 $v_i$ 子树外的点全部加 $w_isz_{v_i}$，对 $v_i$ 子树内的点加上 $w_i(n-sz_{v_i})$。  

这样有点恶心，换个方式：

全局加 $w_isz_{v_i}$，$v_i$ 子树加 $w_i(n-2sz_{v_i})$。

这样显然可以树上差分 $O(1)$ 做，最后再 `dfs` 一遍求个和就是答案，总复杂度 $O(n)$。

赛时代码，略丑陋

```c++
#include <cstdio>
#include <vector>
#define N 200010
#define ll long long
using std::vector;
int n,a[N],sz[N];
ll f[N];
vector<int> e[N];
void dfs1(int x,int fa)
{
    sz[x]=1;
    for(auto i:e[x]) if(i!=fa)
    {
        dfs1(i,x);
        sz[x]+=sz[i];
    }
    if(fa)
    {
        ll w=a[x]^a[fa];
        f[1]+=sz[x]*w;
        //这样感觉清楚点
        f[x]-=sz[x]*w;
        f[x]+=(n-sz[x])*w;
    }
}
void dfs2(int x,int fa)
{
    f[x]+=f[fa];
    for(auto i:e[x]) if(i!=fa) dfs2(i,x);
}
void once()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) e[i].clear(),f[i]=0;
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    for(int i=1,u,v;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs1(1,0); dfs2(1,0);
    for(int i=1;i<=n;i++) printf("%lld ",f[i]);
    puts("");
}
int main()
{
    int T; scanf("%d",&T);
    while(T--) once();
}
```

---

## 作者：Demeanor_Roy (赞：4)

- [原题链接](https://www.luogu.com.cn/problem/CF1882D)

- 完全不需要什么换根 dp。

------------

考虑一棵树当根固定时，只要你不进行一些奇奇怪怪的操作，答案其实是固定的。这一点你不妨从下往上考虑即可。

具体来说，答案可以写成：

$$\sum_{i=1}^{n}{[i \ne root]sz_i} \times {({v_i}\oplus{v_{fa_i}})}$$

直接做是 $O(n^2)$ 的。

不妨考虑每一条边的贡献，发现对于边 $(u,v)$，令 $m$ 表示 $u$ 为根这棵子树的大小，则当根在 $u$ 的子树里时， $ans + (n-m) \times {({v_u}\oplus{v_v})} \rightarrow ans$；否则有  $ans + m \times {({v_u}\oplus{v_v})}  \rightarrow ans$。

于是将树拍成 dfs 序，差分维护即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2e5+10;
int T,n,tim,v[N],sz[N],dfn[N];
int h[N],e[N<<1],ne[N<<1],idx;
long long ans[N];
inline void add(int a,int b)
{
	e[idx]=b;ne[idx]=h[a];h[a]=idx++;
}
inline void dfs(int u,int fa)
{
	sz[u]=1;dfn[u]=++tim;
	for(int i=h[u];~i;i=ne[i])
	{
		if(e[i]==fa) continue;
		dfs(e[i],u);
		sz[u]+=sz[e[i]];
		ans[1]+=1ll*sz[e[i]]*(v[u]^v[e[i]]);
		ans[dfn[e[i]]]+=1ll*(n-sz[e[i]]*2)*(v[u]^v[e[i]]);
		ans[dfn[e[i]]+sz[e[i]]]-=1ll*(n-sz[e[i]]*2)*(v[u]^v[e[i]]);		
	}
}
inline void solve()
{
	tim=idx=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) h[i]=-1,ans[i]=0,scanf("%d",&v[i]);
	for(int i=1;i<n;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		add(a,b);add(b,a);
	}
	dfs(1,1);
	for(int i=1;i<=n;i++) ans[i]+=ans[i-1];
	for(int i=1;i<=n;i++) printf("%lld ",ans[dfn[i]]);puts("");
}
int main()
{
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```


---

## 作者：Reunite (赞：3)

## 一
---

首先，每一位相互独立，因为我们可以把 $c$ 拆成一位一位单独考虑这一位全部变成 $0$ 还是 $1$。先就考虑以 $1$ 为根的情况，我们发现最优操作是确定的，以全部变成 $1$ 为例，从根开始，因为如果 $u$ 目前这一位是 $0$，那么为了让它变成 $1$，我们只能让这一整个子树异或上对应的值；而如果这一位是 $1$ 的话，那么我们再让这个子树操作一定不优。

这样的话，暴力的做法就能确定了，以每个点为根开始 DFS，从上到下维护根到 $u$ 的操作次数，直接一遍扫即可。时间复杂度 $O(n^2\log_2V)$。无法接受。

考虑这似乎是一种很典的换根 DP，先处理出以 $1$ 为根的答案，再根据这个开始换根。记 $fa$ 为 $u$ 的以 $1$ 为根时的父节点，$g_{u,0/1}$ 为以 $u$ 为根时，将整个树这一位全部变成 $0/1$ 的答案，$a_u$ 为这一二进制位上是 $0/1$。那么：

- $a_{fa}=a_u$：  此时以 $u$ 为根和以 $fa$ 为根没有本质区别，$g_u=g_{fa}$。

- $a_{fa}\neq a_v$：
	
    - $a_{fa}=1$： $g_{u,0}=g_{fa,0}-2w\cdot sz_u$，$g_{u,1}=g_{fa,1}+2w\cdot (n-sz_u)$。
    
    - $a_{fa}=0$： $g_{u,1}=g_{fa,1}-2w\cdot sz_u$，$g_{u,0}=g_{fa,0}+2w\cdot (n-sz_u)$。
    
每一位换根做完之后，对 $f_u$ 加上 $\min \{g_{u,0},g_{u,1}\}$ 即可。时间复杂度 $O(n \log_2 n)$，可以通过。

## 二
----
```cpp

void dfs(int u,int fa,int w){
	for(int i=h[u];i;i=edge[i].nxt){
		int v=edge[i].v;
		if(v==fa) continue;
		if((a[v]&w)==(a[u]&w))
			g[v][0]=g[u][0],g[v][1]=g[u][1];
		else{
			if(a[u]&w){
				g[v][0]=g[u][0]-2ll*w*sz[v];
				g[v][1]=g[u][1]+2ll*w*(n-sz[v]);
			}
			else{
				g[v][1]=g[u][1]-2ll*w*sz[v];
				g[v][0]=g[u][0]+2ll*w*(n-sz[v]);
			}
		}
		dfs(v,u,w);
	}
}
```

---

## 作者：y_kx_b (赞：2)

题意：一棵树，点有点权 $a_i$，当根为 $r$ 时一次操作为选定一个节点 $u$ 和一个非负整数 $c$，然后让 $u$ 子树内所有节点点权异或上 $c$，这次操作的代价为 $c\times siz_u$，$siz_u$ 是 $u$ 的子树大小。对于每个 $r\in[1, n]$，你可以进行若干次操作，询问让所有点点权相同的最小代价和是多少。$1\leqslant n\leqslant 2\times10^5$，$0\leqslant a_i<2^{20}$。

对每个点作为根求一遍答案，看起来就很换根 dp。事实确实如此。先考虑 $r=1$ 时怎么求答案。

因为一次操作是对一个子树内所有节点全部异或，所以对于一个点权不相同的 $(u, fa_u)$ 对，我们必须且仅需在 $u$ 处用一次 $c=a_u\oplus a_{fa_u}$ 的操作。

发现操作是无序的，于是设 $dp1_u$ 表示（$1$ 为根的情况下）把 $u$ 的子树内点点权全部变成 $a_u$ 所需要的最小代价。显然 $dp1_u=\sum\limits_{v\in son(u)}dp1_v+siz_v\times(a_u\oplus a_v)$。

考虑换根 dp，设 $dp2_u$ 表示 $fa_u$ 及其往上所有部分点权全部变成 $a_u$ 的最小代价，后面就是板子就不写了（）。（$dp2_u=\big(dp2_{fa_u}+dp1_{fa_u}-dp1_u-siz_u\times(a_u\oplus a_{fa_u})\big)+(n-siz_u)\times(a_u\oplus a_{fa_u})$）

时间复杂度 $O(n)$，[code](https://codeforces.com/contest/1882/submission/225228171)。

---

## 作者：syysongyuyang (赞：1)

固定根，注意到对于树上每一个 $(u,fa_u)$，如果 $a_u\not = a_{fa_u}$，则有 $(a_u \oplus a_{fa_u})\times siz_u$ 的贡献。

则有 $f_u =\sum\limits_{v\in son_u} f_v + (a_u \oplus a_{v})\times siz_v$。

考虑换根，对于 $(u,fa_u)$，换根后 $u$ 原子树内贡献不变，去掉了 $fa_u$ 扣掉 $u$ 原先子树的贡献，加上了 $(u,fa_u)$ 的贡献。

则有 $g_u = (g_{fa_u}+f_{fa_u}-f_u-siz_u \times (a_u \oplus a_{fa_u})) + (n-siz_u) \times (a_u \oplus a_{fa_u})$。

时间复杂度 $\Theta(n)$。



---

## 作者：hcywoi (赞：0)

对于一颗子树，我们一定是先将其根节点所有儿子所在的子树变成相同，然后再将这颗子树变成相同。

我们设 $f_i$ 表示第 $i$ 个节点的父亲节点，$siz_i$ 表示第 $i$ 个节点的子树大小。

我们需要求 $\displaystyle\sum_{i=1}^{n}(a_i\oplus a_{f_i})\times siz_i$。

换根 DP 即可，时间复杂度 $\mathcal O(n)$。

```cpp
#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; i ++ ) {
        std::cin >> a[i];
    }

    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < n - 1; i ++ ) {
        int u, v;
        std::cin >> u >> v;
        u --, v -- ;
        adj[u].push_back(v), adj[v].push_back(u);
    }

    std::vector<i64> siz(n);
    std::vector<i64> f(n), g(n);
    auto dfs = [&](auto self, int x, int p) -> void {
        siz[x] = 1;
        for (auto y: adj[x]) {
            if (y == p) {
                continue;
            }
            self(self, y, x);
            siz[x] += siz[y];
            f[x] += f[y] + 1LL * (a[x] ^ a[y]) * siz[y];
        }
    };
    dfs(dfs, 0, -1);
    
    auto dfs1 = [&](auto self, int x, int p) -> void {
        if (p != -1) {
            g[x] = g[p] + f[p] - f[x] + 1LL * (n - 2 * siz[x]) * (a[x] ^ a[p]);
        }
        for (auto y: adj[x]) {
            if (y == p) {
                continue;
            }
            self(self, y, x);
        }
    };
    dfs1(dfs1, 0, -1);

    for (int i = 0; i < n; i ++ ) {
        std::cout << f[i] + g[i] << " \n"[i == n - 1];
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t -- ) {
        solve();
    }

    return 0;
}
```

---

## 作者：qwq___qaq (赞：0)

容易发现这是一个换根。首先，贪心地就能想到是使子树全部转化成根节点的点权。

位拆，然后可以定义 $f_{i,0/1}$ 表示把以 $i$ 为根的子树全部转化成 $0/1$ 的最小花费。

然后就可以拆成向下转化和向上转化 $2$ 个部分，向上转化直接就是 $f_{u,a_u}$，然后向上转化就是打换根了。

我们定义 $s_0,s_1$ 分别表示向上转化成 $0$ 和 $1$ 的花费，然后直接对 $a_u,a_v$ 进行分类讨论即可。

---

