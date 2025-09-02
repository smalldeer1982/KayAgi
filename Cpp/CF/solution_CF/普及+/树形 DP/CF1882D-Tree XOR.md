# Tree XOR

## 题目描述

给定一棵有 $n$ 个顶点的树，顶点编号为 $1$ 到 $n$。对于每个顶点 $i$（$i = 1, 2, \ldots, n$），顶点 $i$ 上写有一个整数 $a_i$。你希望通过施展若干次（可以为零次）“法术”使得所有 $a_i$ 都相等。

假设你将树以某个顶点作为根。在每次施法时，你可以选择任意一个顶点 $v$ 和任意一个非负整数 $c$，然后对于 $v$ 的子树 $^{\dagger}$ 中的所有顶点 $i$，将 $a_i$ 替换为 $a_i \oplus c$。这次法术的代价为 $s \cdot c$，其中 $s$ 是该子树中的顶点数。这里 $\oplus$ 表示[按位异或运算](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。

设 $m_r$ 表示以顶点 $r$ 作为树根时，使所有 $a_i$ 相等所需的最小总代价。请你求出 $m_1, m_2, \ldots, m_n$。

$^{\dagger}$ 假设以顶点 $r$ 作为树根。如果从顶点 $i$ 到 $r$ 的简单路径上包含顶点 $v$，则顶点 $i$ 属于 $v$ 的子树。

## 说明/提示

在第一个测试用例中，计算 $m_1$ 时，将树以顶点 $1$ 作为根。

1. 第一次施法，选择 $v=2$，$c=1$。施法后，$a$ 变为 $[3, 3, 0, 1]$。本次施法代价为 $3$。
2. 第二次施法，选择 $v=3$，$c=3$。施法后，$a$ 变为 $[3, 3, 3, 1]$。本次施法代价为 $3$。
3. 第三次施法，选择 $v=4$，$c=2$。施法后，$a$ 变为 $[3, 3, 3, 3]$。本次施法总代价为 $2$。

此时数组 $a$ 中所有值都相等，总代价为 $3 + 3 + 2 = 8$。

$m_2$、$m_3$、$m_4$ 的计算方法类似。

在第二个测试用例中，目标已经达成，因为只有一个顶点。

由 ChatGPT 4.1 翻译

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

## 作者：西瓜nd (赞：14)

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

## 作者：xkcdjerry (赞：6)

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

## 作者：Demeanor_Roy (赞：5)

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

## 作者：ZHR100102 (赞：2)

[Blog](https://www.cnblogs.com/zhr0102/p/18970222)

## Sol.1 换根 DP

注意到操作是子树异或，最终树的形态是所有节点都相等，考虑从**差分**数组的角度思考，则每次操作都只会改变一个节点的差分值；且每个节点与父节点的差分值必须为 $0$，根节点除外。同时可以把这个差分值**移到和父节点的边上**，用边权表示。

固定根的做法是容易的，直接计算每个子树的大小，然后对每条边的边权分别计算即可。考虑如何进行 $u\to v$ 的换根，可以画出如下的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/8grhi7jz.png)

从 $u$ 到 $v$，第一步要减掉 $u$ 的子树因 $u,v$ 的边造成的贡献；第二步就是要加上以 $v$ 为根后 $u$ 的子树的贡献。因为边权是始终不变的，且换根后只有 $u$ 的子树大小变成了 $n-sz_v$，所以转移方程为：

$$dp_v=dp_u+(a_u\oplus a_v)\times (n-sz_v)-(a_u\oplus a_v)\times sz_v= dp_u+(a_u\oplus a_v)\times (n-2\times sz_v)$$

时间复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=200005;
ll n,a[N],dp[N],sz[N],dp2[N];
vector<int>g[N];
void dfs1(int u,int fa)
{
	sz[u]=1;
	for(auto v:g[u])
	{
		if(v==fa)continue;
		dfs1(v,u);
		sz[u]+=sz[v];
		dp[u]+=dp[v]+(a[u]^a[v])*sz[v];
	}
}
void dfs2(int u,int fa)
{
	for(auto v:g[u])
	{
		if(v==fa)continue;
		dp2[v]=dp2[u]+(a[u]^a[v])*(n-2*sz[v]);
		dfs2(v,u);
	}
}
void solve()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		g[i].clear();
		dp[i]=dp2[i]=0;
	}
	for(int i=1;i<n;i++)
	{
		int u,v;
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs1(1,0);
	dp2[1]=dp[1];
	dfs2(1,0);
	for(int i=1;i<=n;i++)cout<<dp2[i]<<" ";
	cout<<'\n';
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	while(t--)solve();
	return 0;
}
```

还有一种树形 DP 思路，推式子后注意到把其余节点的值**全部搞成根节点的值一定更优**，直接换根 DP 即可。口胡的做法，我没写。

## Sol.2 树上差分

从每条边的**贡献**角度考虑，发现先确定一个根之后，根换到的位置如果在边的子树外，则对应的大小为 $sz_v$，否则一定为 $n-sz_v$。在子树内的贡献是好做的，拍在 DFS 序上或者**树上差分**都能做；但是对子树外的就不太好做了。因此考虑**容斥**，先把所有的点当成子树外的点全局加一遍，再将子树内的多减去一遍子树外的贡献即可。

时间复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=200005;
ll n,a[N],sz[N],f[N],ans[N],all;
vector<int>g[N];
void dfs1(int u,int fa)
{
	sz[u]=1;
	for(auto v:g[u])
	{
		if(v==fa)continue;
		dfs1(v,u);
		sz[u]+=sz[v];
		all+=sz[v]*(a[u]^a[v]);
		f[v]+=(n-2*sz[v])*(a[u]^a[v]);
	}
}
void dfs2(int u,int fa)
{
	ans[u]=all+f[u];
	for(auto v:g[u])
	{
		if(v==fa)continue;
		f[v]+=f[u];
		dfs2(v,u);
	}
}
void solve()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		g[i].clear();
		f[i]=0;
	}
	for(int i=1;i<n;i++)
	{
		int u,v;
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	all=0;
	dfs1(1,0);
	dfs2(1,0);
	for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
	cout<<'\n';
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	while(t--)solve();
	return 0;
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

## 作者：xrz114514 (赞：0)

# CF1882D 题解
## 思路
可以先考虑根为 1 的情况。  
发现如果要让一个子树相等的话，一定会让其等于其的根结点的值。所以，设使 $u$ 的子树相等的最小总代价为 $dp_u$，则可以使其从每个儿子子树转移来，也就是说，如果 $a_u$ 与 $a_v$ 不同，则需给 $v$ 进行一次异或 $a_u \oplus a_v$ 的操作，由于 $v$ 子树内值都一样，不会影响。所以，$dp_u = \sum\limits_{v \in son_u} (dp_v + (a_u \oplus a_v) \times siz_v)$。其中，$siz_v$ 是 $v$ 的子树大小。

之后，考虑换根。每次将根节点从 $u$ 转移到 $v$ 时，$u$ 与 $v$ 的关系发生变化。所以假设原来的答案为 $w$，则转移后的答案为 $w + (a_u \oplus a_v) \cdot (n - 2 \cdot siz_v)$。

时间：$O(n)$。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 2e5 + 1;

int t, n, a[N];
ll dp[N], siz[N];
vector<int> g[N];

void dfs(int u, int fa){
  siz[u] = 1;
  for(int e : g[u]){
    if(e == fa){
      continue;
    }
    dfs(e, u);
    siz[u] += siz[e];
    dp[u] = dp[u] + 1ll * siz[e] * (a[u] ^ a[e]) + dp[e];
  }
}

void Solve(int u, int fa, ll w){
  for(int e : g[u]){
    if(e == fa){
      continue;
    }
    dp[e] = w + 1ll * (a[u] ^ a[e]) * ((n - siz[e]) - siz[e]);
    Solve(e, u, dp[e]);
  }
}

void Solve(){
  cin >> n;
  fill(dp + 1, dp + n + 1, 0);
  for(int i = 1; i <= n; ++i){
    cin >> a[i];
    g[i].clear();
  }
  for(int i = 1, u, v; i < n; ++i){
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs(1, 0);
  Solve(1, 0, dp[1]);
  for(int i = 1; i <= n; ++i){
    cout << dp[i] << ' ';
  }
  cout << '\n';
}

int main(){
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> t;
  while(t--){
    Solve();
  }
  return 0;
}
```

---

## 作者：yuhong056 (赞：0)

# 题解：CF1882D Tree XOR
## 题意
给定一棵带点权树，每次操作可以将一个子树内点权都 $\operatorname{xor} c$，会花费 $c \times $ 子树的大小元。

求对于每个节点为根的情况，求最少花费多少元能使树上的点权全部相等。
## 思路
看到这种位运算，我们就可以想到将点权进行拆位分析。

假设我们将点权全部拆成了 $0$ 或 $1$。

我们可以发现：
> 我们会将所有非根的节点的权值都变成根节点的权值。

原因是：若改变了根节点的权值，那么我们子树任然要做不改变根节点的权值时的操作。

因此，我们可以进行树 dp。

但是，还要求出对于每个节点为根的情况，因此需要使用换根 dp。

式子可见代码。
## 代码
```cpp
#include<bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 2e5 + 25;

int n;
int a[MAXN];
ll ans[MAXN], dp[MAXN], sz[MAXN];

vector<int>e[MAXN];

void dfs1(int u, int fa) {
  sz[u] = 1;
  for(int v : e[u]) {
    if(v == fa)continue;
    dfs1(v, u);
    int k = a[u] ^ a[v];
    dp[u] += sz[v] * k + dp[v];
    sz[u] += sz[v];
  }
  ans[u] = dp[u];
}

void dfs2(int u, int fa) {
  for(int v : e[u]) {
    if(v == fa)continue;
    int k = a[u] ^ a[v];
    ans[v] += ans[u] - dp[v] + 1LL * n * k - 2 * sz[v] * k;
    dfs2(v, u);
  }
}

void solve() {
  cin >> n;
  for(int i = 1; i <= n; i++) {
    cin >> a[i];
    e[i].clear();
    ans[i] = dp[i] = sz[i] = 0;
  }
  for(int i = 1, u, v; i < n; i++) {
    cin >> u >> v;
    e[u].push_back(v);
    e[v].push_back(u);
  }
  dfs1(1, 0);
  dfs2(1, 0);
  for(int i = 1; i <= n; i++) {
    cout << ans[i] << ' ';
  }
  cout << '\n';
}

int main(){
  ios::sync_with_stdio(0), cin.tie(0);
  int T;
  for(cin >> T; T--; solve());
  return 0;
}
```

---

## 作者：Fusiyi (赞：0)

# CodeForces - 1882D Tree XOR

## 题意

给定一棵有 $n$ 个顶点的树，顶点编号为 $1$ 到 $n$。对于每个顶点 $i$（$i = 1, 2, \ldots, n$），顶点 $i$ 上写有一个整数 $a_i$。你希望通过若干次操作使得所有 $a_i$ 都相等。

假设你将树以某个顶点作为根。在每次操作，你可以选择任意一个顶点 $v$ 和任意一个非负整数 $c$，然后对于 $v$ 的子树中的所有顶点 $i$，将 $a_i$ 替换为 $a_i \oplus c$。代价为 $s \cdot c$。

设 $m_r$ 表示以顶点 $r$ 作为树根时，使所有 $a_i$ 相等所需的最小总代价。请你求出 $m_1, m_2, \ldots, m_n$。

## 思路

换根 dp 模板。

先求出以 $1$ 为根的代价。

对于每一个节点，如果我们改变它的父亲，是不会使它与父亲相等的，所以我们每一次改变都只能将自己变得与父亲相等。且每一次改变不会对子树内部造成影响。

所以：$v$ 为当前节点，$u$ 为它的父亲，只能将 $a_v$ 替换为 $a_v \oplus (a_u \oplus a_v)$, 代价为 $s \cdot (a_u \oplus a_v)$。

预处理出每一个节点以它为子树的根时的代价总和，然后换根求出所有的答案。

怎么换根？

![](https://cdn.luogu.com.cn/upload/image_hosting/xl4vcraw.png)

如图，树以 $1$ 为根，将树转换为以 $2$ 为根。

我们可以先将 $1$ 和 $2$ 之间的边拆开。

![](https://cdn.luogu.com.cn/upload/image_hosting/gtwy9w5j.png)

然后将 $1$ 链接到 $2$ 上。

![](https://cdn.luogu.com.cn/upload/image_hosting/dq8f359j.png)

（虽然删了跟没删一样）。

我们可以通过删边来改变值。

## 代码

~~~Cpp
#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using namespace std;

const int N = 2e5 + 3;
int t, n;
int a[N], u, v;
vector <int> e[N];
ll sz[N], dp[N];
ll ans[N];

/***
dp为代价
sz为子树大小
***/

void dfs1(int u, int fa){
    sz[u] = 1;
    for(int i = 0; i < e[u].size(); i ++){
        int v = e[u][i];
        if(v == fa) continue;

        dfs1(v, u);

        sz[u] += sz[v];
        dp[u] += (a[u] ^ a[v]) * sz[v] + dp[v];
    }
}

void dfs(int u, int fa){
    ans[u] = dp[u];
    for(int i = 0; i < e[u].size(); i ++){
        int v = e[u][i];
        if(v == fa) continue;

        ll s1_u = dp[u], s2_u = sz[u];
        ll s1_v = dp[v], s2_v = sz[v];

        sz[u] = s2_u - s2_v;///删边
        sz[v] = s2_v + sz[u];///加边
        dp[u] = s1_u - s1_v - (a[u] ^ a[v]) * s2_v;///删边
        dp[v] = s1_v + dp[u] + (a[u] ^ a[v]) * sz[u];///加边

        dfs(v, u);

        dp[u] = s1_u, sz[u] = s2_u;
        dp[v] = s1_v, sz[v] = s2_v;
        ///一定要记得改回来
    }
}

int main(){
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    cin >> t;
    while(t --){
        cin >> n;
        for(int i = 1; i <= n; i ++){
            cin >> a[i];
            dp[i] = sz[i] = ans[i] = 0;
            e[i].clear();
        }
        for(int i = 1; i < n; i ++){
            cin >> u >> v;
            e[u].push_back(v);
            e[v].push_back(u);
        }

        dfs1(1, 0);
        dfs(1, 0);

        for(int i = 1; i <= n; i ++){
            cout << ans[i] << ' ';
        }
        cout << '\n';
    }

    return 0;
}



~~~

---

## 作者：_Chronostatis_ (赞：0)

## 题意
给定一棵大小为 $n$ 的树，每个点有一个点权 $a_i$。每次可以对一棵子树进行异或操作，代价为子树大小乘上异或的值。对每个 $1 \le i \le n$，求出以 $i$ 为根的将整棵树变为相同的数的最小代价。

## 思路
显然，我们让整棵树的值变为一个点的值更为方便。由异或的性质，两个不同的数异或上一个相同的数不可能变为相等，所以如果我们选取一个在子树内的点，那么无法保证这棵子树内的点都相同。

所以对每个点 $u$ 和其子节点 $v_1, v_2, \dots, v_k$，将以 $v_1, v_2, \dots, v_k$ 为根的子树的值全部修改为 $a_u$，由于我们是从下到上操作（dfs 的顺序），所以下面的值按照这个方法已经全部相等，且等于 $v_i$ 的值，每次操作只需要将答案增加 $sz_v \cdot (a_{v_i} \oplus a_u)$ 即可，其中 $sz_u$ 表示以 $u$ 点为根的子树大小。

但是这样并不能求出每个节点的值。所以我们考虑[换根 dp](https://oi-wiki.org/dp/tree/)。现在来推转移式。我们设已经求出的以 1 为根的树的答案为 $dp$ 数组，以节点 $u$ 为根的答案为 $ans_u$。

![](https://cdn.luogu.com.cn/upload/image_hosting/syt4gzi8.png)

如上图，整棵树的值为 $a_u$。我们发现，当树根从 $u$ 转移至 $v$ 时，$u$ 左边的子树需要将答案更新为 $a_v$，以 $v$ 为根的子树可以减少一次将答案变为 $a_u$ 的操作。所以 

$$
ans_v = ans_u - sz_v \cdot (a_u \oplus a_v) + (n - sz_v) \cdot (a_u \oplus a_v)
$$

一开始将 $ans_1$ 置为 $dp_1$，再做一遍 dfs 即可。

## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 2e5 + 10;

int n, a[MAXN];
ll dp[MAXN], ans[MAXN], sz[MAXN];
vector<int> g[MAXN];

void dfs(int u, int fa) {
  sz[u] = 1;
  for (int v : g[u]) {
    if (v == fa) continue;
    dfs(v, u);
    sz[u] += sz[v], dp[u] += dp[v];
    if (a[v] != a[u]) {
      dp[u] += sz[v] * (a[u] ^ a[v]);
    }
  }
}

void dfs2(int u, int fa) {
  for (int v : g[u]) {
    if (v == fa) continue;
    ans[v] = ans[u] + (n - (sz[v] << 1)) * (a[u] ^ a[v]);
    dfs2(v, u);
  }
}

void Solve() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    g[i].clear();
  }
  for (int i = 1, u, v; i < n; i++) {
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  fill(dp + 1, dp + n + 1, 0);
  dfs(1, 0);
  ans[1] = dp[1];
  dfs2(1, 0);
  for (int i = 1; i <= n; i++) {
    cout << ans[i] << ' ';
  }
  cout << '\n';
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  int T;
  for (cin >> T; T--; Solve());
  return 0;
}
```

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

## 作者：Unnamed114514 (赞：0)

容易发现这是一个换根。首先，贪心地就能想到是使子树全部转化成根节点的点权。

位拆，然后可以定义 $f_{i,0/1}$ 表示把以 $i$ 为根的子树全部转化成 $0/1$ 的最小花费。

然后就可以拆成向下转化和向上转化 $2$ 个部分，向上转化直接就是 $f_{u,a_u}$，然后向上转化就是打换根了。

我们定义 $s_0,s_1$ 分别表示向上转化成 $0$ 和 $1$ 的花费，然后直接对 $a_u,a_v$ 进行分类讨论即可。

---

