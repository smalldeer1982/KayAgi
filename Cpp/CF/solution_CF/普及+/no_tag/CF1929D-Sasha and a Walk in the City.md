# Sasha and a Walk in the City

## 题目描述

Sasha 想和他的女友在城市中散步。该城市由 $n$ 个路口组成，编号为 $1$ 到 $n$ 。它们中的某些被道路连接，从任何一个路口出发，都可以恰好通向任何其他路口，换句话说，这些路口和它们之间的道路组成了一棵树。

其中有一些路口被认为很危险。由于在城市中独自走路是不安全的，所以Sasha 不想在散步时经过三个或更多的危险路口。

Sasha 认为，一组路口如果满足以下条件则称它为好的：
- 如果在城市中只有这组路口中的路口是危险的，那么城市中的任何简单路径都包含不超过两个危险路口。

然而，Sasha 并不知道哪些路口是危险的，因此他对城市中不同好的路口组合的数量感兴趣。由于这个数量可能很大，输出其模数为 $998244353$ 的值。

简单路径是指最多经过每个路口一次的路径。

## 说明/提示

在第一个测试用例中，有 $2^3-1=7$ 个集合是可以选的，除了集合 $\{1,2,3\}$ 以外，因为如果在城市中只有 $\{1,2,3\}$ 中的路口是危险的，那么路口 $1,2,3$ 对应的道路构成的简单路径 $1-2-3$ 包含了 $3$ 个危险路口。因此，一共有 $7-1=6$ 个合法路口集合。

在第二个测试用例中，有 $2^4-1=15$ 个集合是可以选的，但是其中 $\{1,2,3,4\}, \{1,2,3\},\{1,3,4\},\{2,3,4\}$ 不是合法的集合。因此一共有 $15-4=11$ 个合法路口集合。城市分布如下图所示：

![](https://espresso.codeforces.com/6099716106eb21a756456f73670fc0f51b161ac2.png)

## 样例 #1

### 输入

```
4
3
1 3
3 2
4
3 4
2 3
3 1
5
1 2
3 4
5 1
2 3
4
1 2
2 3
3 4```

### 输出

```
7
12
16
11```

# 题解

## 作者：w9095 (赞：12)

[CF1929D Sasha and a Walk in the City](https://www.luogu.com.cn/problem/CF1929D)

简单树形动态规划。

我们把选取到的点称为黑点，由题意得，一个合法的点集能使树中任意一条简单路径上的黑点数量不超过两个。也就是说，如果黑点数量多于 $2$，对于任意两个黑点，它们如果在同一个节点的子树内，必然是兄弟关系。否则，一旦存在祖先关系，由于黑点数量多于 $2$，必然有一个黑点可以与这两个点组成一条黑点数量超过两个的简单路径。

设状态 $dp_{i,j}$ 表示以 $i$ 为根的子树内，从根到叶子节点最多经过 $j$ 个黑点。显然，只有 $j$ 等于 $0,1$ 或 $2$ 时，状态是合法的。

考虑如何转移，对于 $dp_{i,0}$，显然等于 $1$。

对于 $dp_{i,1}$，由于根到叶子节点最多经过黑点数最大值为 $1$，最多就是两条到根的路径合并，经过 $1+1=2$ 个黑点，所以每一个儿子内可以任意选择。另外，每个子树内还可以从没有黑点涂子树的根上的黑点变成有 $1$ 个黑点，所以还需要加入没有黑点的方法数。根据乘法原理，可以推出如下转移式：

$$dp_{i,1}=\prod_{j\in son(i)}(dp_{j,0}+dp_{j,1})=\prod_{j\in son(i)}(1+dp_{j,1})$$

对于 $dp_{i,2}$，由于根到叶子节点最多经过黑点数最大值为 $2$，所以只能有一个子树内的 $dp$ 值可以转移来，否则必然可以构造一条黑点数量超过两个的简单路径。另外，每个子树内还可以从 $1$ 个黑点涂子树的根上的黑点变成有 $2$ 个黑点，所以还需要加入 $1$ 个黑点的方法数。根据加法原理，可以推出如下转移式：

$$dp_{i,2}=\sum_{j\in son(i)}(dp_{j,1}+dp_{j,2})$$

以 $1$ 为整棵树的根，最后的答案为 $dp_{1,0}+dp_{1,1}+dp_{1,2}$，也就是 $1+dp_{1,1}+dp_{1,2}$。

```cpp
#include <bits/stdc++.h>
using namespace std;
struct edge
{
	long long v,nxt;
}e[800000];
long long t,u,v,n,mod=998244353,h[800000],f[800000][3],cnt=0;
void add_edge(long long u,long long v)
{
	e[++cnt].nxt=h[u];
	e[cnt].v=v;
	h[u]=cnt;
}
 
void init()
{
	for(int i=1;i<=n;i++)h[i]=0,f[i][1]=1,f[i][2]=0;
	cnt=0;
}
 
void dfs(long long x,long long fa)
{
	for(int i=h[x];i;i=e[i].nxt)
	    if(e[i].v!=fa)
	       {
		   dfs(e[i].v,x);
		   f[x][1]=(f[x][1]*(f[e[i].v][1]+1)%mod)%mod; 
		   f[x][2]=(f[x][2]+f[e[i].v][1]+f[e[i].v][2])%mod;
	       }
}
 
int main()
{
	scanf("%lld",&t);
	while(t--)
	   {
	   	scanf("%lld",&n);
	   	init();
	   	for(int i=1;i<=n-1;i++)
	   	    {
	   	    scanf("%lld%lld",&u,&v);
	   	    add_edge(u,v),add_edge(v,u);
			}
		dfs(1,0);
		printf("%lld\n",(f[1][1]+f[1][2]+1)%mod);
	   }
	return 0;
}
```

---

## 作者：zhicheng (赞：12)

### 思路

考虑 DP。设 $dp_u$ 表示 $u$ 这个点所在子树中选点的方案数，满足任意两个点都没有祖先-后代关系。有：

$$
dp_u=\prod_{v\in son_u}(dp_v+1)
$$

表示 $v$ 这个子树可以选某个方案或根本不选。答案就是 $1+\sum\limits_{i=1}^{n}dp_i$。

为什么这个是正确的呢？考虑我们钦定 $u$ 的儿子中如果一个点都没有选或只有一个子树选了点就把 $u$ 选上（只有仅选 $u$ 时会向上传）。这样可以保证不重不漏。最后再加上一个点都不选的方案即可。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=300010,mod=998244353;
int n,ans,tot,first[N],nnext[N<<1],to[N<<1],dp[N];
void add(int x,int y){
	nnext[++tot]=first[x];
	first[x]=tot;
	to[tot]=y;
}
void dfs(int u,int fa){
	dp[u]=1;
	for(int e=first[u];e;e=nnext[e]){
		if(to[e]!=fa){
			dfs(to[e],u);
			dp[u]=1ll*dp[u]*(dp[to[e]]+1)%mod;
		}
	}
	ans=(ans+dp[u])%mod;
}
int main(){
	int t,a,b;
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		tot=ans=0;
		for(int i=1;i<=n;i++){
			first[i]=0;
		}
		for(int i=1;i<=n-1;i++){
			scanf("%d%d",&a,&b);
			add(a,b);
			add(b,a);
		}
		dfs(1,0);
		printf("%d\n",(ans+1)%mod);
	}
}
```

---

## 作者：_HCl_ (赞：5)

本题解想法有一点点奇特。

# CF1929D 题解

**题意简述**

要求你对树上的某些节点进行染色，使得整棵树中，所有的简单路径上最多只有两个被染色点。

求出染色方案数。

**思路引导**

显然是树形 DP，考虑怎么设计状态。

先直接考虑每一棵子树的答案。发现，如果子树中存在两个被染色点，并且有祖先关系，会非常难处理。因此我们先去考虑不包含祖先关系的答案。

设 $f_x$ 表示不包含两个有祖先关系的被染色点的染色方案数。那么有：
$$f_x=1+\prod_{y\in son_x} f_y$$
其中 $\prod f_y$ 表示每个子树的每个染色方案都是可以取的，是合法的。加上 $1$ 是考虑只有根节点被染色，其它点全空的方案。

再来考虑只有祖先关系的答案，换言之，两个染色点都在一条链上。设 $g_x$ 表示在链上的染色方案。那么有：
$$ g_x=\sum_{y\in son_x} (f_y-1)+\sum_{y\in son_x} g_y$$
第一个求和表示，选择一棵子树用 $f$ 染色，根节点染色。但是当子树全空时是不能这么做的（不然只染根节点就变成 $f$ 染色了），所以要 $-1$。

第二个求和表示，选择一棵子树用 $g$ 染色，根节点不染色。

答案就是 $f_1+g_1$。

对于边界条件，$f_{leaf}=2$，$g_{leaf}=0$，也很好理解。

**代码**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=300005,MOD=998244353;
int n;
vector<int> e[N];
int f[N],g[N];
void dfs(int x,int fa){
    int prod=1,sum=0,flag=0;
    for(int y:e[x]){
        if(y==fa)continue;
        flag=1;
        dfs(y,x);
        prod=prod*f[y]%MOD;
        sum=(sum+f[y]+g[y]-1)%MOD;
    }
    if(flag)f[x]=prod+1,g[x]=sum%MOD;
    else f[x]=2,g[x]=0;
}
void doit(){
    cin>>n;
    for(int i=1;i<=n;++i)e[i].clear();
    for(int i=1;i<n;++i){
        int u,v;
        scanf("%lld%lld",&u,&v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1,0);
    cout<<(f[1]+g[1])%MOD<<"\n";
}
signed main(){
    int T;
    cin>>T;
    while(T--)doit();
}
```

---

## 作者：114514xxx (赞：3)

## 题意
给定一棵节点数为 $n$ 的树，初始的点的颜色都为白色，现在你可以将一些点染为黑色，但要使树上任何简单路径上有不超过 $2$ 个黑点。问有多少种染色方案，答案对 $998244353$ 取模。

## 思路
为方便起见，我们设 $1$ 为这棵树的根节点。

设 $f_{u,x}$ 表示以 $u$ 这个点为根的子树上一共有 $x$ 个黑点有 $f_{u,x}$ 种方案。

先考虑 $f_{u,0}$ 的情况。当以 $u$ 的为根的子树没有黑点时，显然只有 $1$ 种方案。即 $f_{u,0}=1$。

以下记 $S_u$ 为 $u$ 的子节点的集合。

接下来讨论关于 $f_{u,1}$ 的状态转移方程。一开始 $f_{u,1}$ 的值肯定为 $1$，这是因为我们可以将 $u$ 染为黑色。当不将 $u$ 染为黑色时，肯定是 $u$ 的子节点中有黑色的点，并且可以从子节点任选。因此根据乘法原理有以下式子： 
$$
\begin{aligned}
f_{u,1}&=\prod_{j\in S_u} (f_{j,0}+f_{j,1})\\
      &=\prod_{j\in S_u}(1+f_{j,1})
\end{aligned}
$$

最后讨论关于 $f_{u,2}$ 的状态转移方程。这种情况比较简单。也是考虑是否 $u$ 是否染成黑色。先考虑 $u$ 为黑色时，以 $u$ 为根的子树中最多只有 $1$ 个被染成黑色的点。可以得到以下式子：
$$
\begin{aligned}
f_{u,2}=\sum_{j\in S_u}f_{j,1}
\end{aligned}
$$
当 $u$ 没被染色时，肯定只能从 $f_{j,2}$ 转移过来，可以得到以下式子：
$$
\begin{aligned}
f_{u,2}=\sum_{j\in S_u}f_{j,2}
\end{aligned}
$$
综上，得到：
$$
\begin{aligned}
f_{u,2} &= \sum_{j\in S_u}f_{j,2}+\sum_{j\in S_u}f_{j,1}\\
        &=\sum_{j\in S_u}(f_{j,2}+f_{j,1})
\end{aligned}
$$
因为根节点为 $1$，所以最终答案为 $1+f_{1,1}+f_{1,2}$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+25;
const int mod=998244353;
struct Edge{
    int to,next;
}edge[N*2];
int head[N],cnt,n;
int f[N][5];
inline void add(int x,int y){
    edge[++cnt].to=y;
    edge[cnt].next=head[x];
    head[x]=cnt;
}
inline void dfs(int u,int fa){
    for(int i=head[u];i;i=edge[i].next){
        int v=edge[i].to;
        if(v==fa)continue;
        dfs(v,u);
        f[u][1]=((f[u][1]%mod)*(1+f[v][1]%mod))%mod;
        f[u][2]=(f[u][2]%mod+(f[v][1]+f[v][2])%mod)%mod;
    }
}
inline void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        edge[i].to=0;
        edge[i].next=0;
        head[i]=0;
    }//多测记得清空
    cnt=0;
    int u,v;
    for(int i=1;i<n;i++){
        cin>>u>>v;
        add(u,v),add(v,u);
    }
    for(int i=1;i<=n;i++)
        f[i][1]=1,f[i][2]=0;
    dfs(1,0);
    cout<<(1%mod+f[1][1]%mod+f[1][2]%mod)%mod<<endl;
}
int t;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--)
        solve();
}

```

---

## 作者：FugiPig (赞：3)

# 题解 CF1929D

题目链接：[洛谷题目链接](https://www.luogu.com.cn/problem/CF1929D)，[CF题目链接](https://codeforces.com/problemset/problem/1929/D)。

更好的阅读体验：[link](https://www.luogu.com.cn/blog/fugi-tech/solution-CF1929D)。

## 1. 题意简述

有一棵 $n$ 个节点的树（$2\le n\le 3\times10^5$），可以将某些节点设为**危险的**，问有多少种方法选择危险节点，且使得树上的任意一条简单路径包含的危险的节点个数不超过 $2$（对 $998244353$ 取模）。

## 2. 求解思路

我们发现这道题需要统计方法数，所以我们优先考虑 DP。由于直接统计不太方便，我们对其性质进行分析。

可以发现，如果任意叶子到根的路径上的危险节点个数不超过 $1$，则这种方案一定是合法的。这是因为我们可以将 $u$ 到 $v$ 的简单路径拆分为 $u-\operatorname{lca}(u,v)$ 和 $\operatorname{lca}(u,v)-v$，而这两段路径的危险节点个数均不超过 $1$，所以总危险节点个数不超过 $2$。

对于这种情况，其方案数的统计是较为简单的。我们设 $dp_u$ 表示以 $u$ 为根的子树中使得任意叶子到 $u$ 的路径上的危险节点个数不超过 $1$ 的方案数。则对于 $u$，若 $u$ 的儿子构成的集合为 $\operatorname{son}(u)$，可列状态转移方程 $dp_u=\prod_{v\in \operatorname{son}(u)}dp_v+1$。其中将 $dp_v$ 乘起来代表如果 $u$ 不危险，则儿子可以随便选。而 $1$ 代表 $u$ 危险而 $u$ 子树内其他节点均不危险的情况。特别的，对于叶子节点，其 $dp$ 值为 $2$，即选或不选。

而对于任意叶子到根的路径上的危险节点个数为 $2$ 的情况（显然不可能超过 $2$），我们设任意一条叶子到根的危险节点个数为 $2$ 的路径上较高的危险节点为 $u$。则其余的危险节点显然只能在以 $u$ 的唯一一个儿子为根的子树中选，否则可以构造一条从以 $u$ 的某个儿子为根的子树中的一个危险点到 $u$，再到另外的一个危险点的非法路径。所以点 $u$ 在这种情况下贡献的答案为 $\sum_{v\in son(u)}(dp_v-1)$，减去 $1$ 的原因是要排除以某个儿子为根的子树中一个也不选的情况。

综上，如果设根为 $1$，则最终的答案为：

 $$dp_1+\sum_{u\in V}\sum_{v\in son(u)}(dp_v-1)=\sum_{u\in V}dp_u-n+1$$

时间复杂度显然为 $O(n)$。

## 3. 代码实现

代码实现还是较为简单的，只要学过树形 DP 就可以看懂。~~不过本蒟蒻的码风可能不太正常。~~

```cpp
#include<iostream>
#include<vector>
using namespace std;
const int maxn=3e5+5,mod=998244353;
typedef long long ll;
vector<int> G[maxn];
ll dp[maxn],ans;
void dfs(int cur,int fa)
{
	dp[cur]=1;
	for(int v1=0;v1<G[cur].size();v1++)
	{
		int v=G[cur][v1];
		if(v==fa)continue;
		dfs(v,cur);
		dp[cur]=dp[cur]*dp[v]%mod;
	}
	dp[cur]++;
	ans+=dp[cur]; 
}
int main()
{
	int it;
	scanf("%d",&it);
	while(it--)
	{
		int in;
		scanf("%d",&in);
		for(int v1=1;v1<=in;v1++)G[v1].clear();
		for(int v1=1;v1<=in-1;v1++)
		{
			int ix,iy;
			scanf("%d %d",&ix,&iy);
			G[ix].push_back(iy);
			G[iy].push_back(ix);
		}
		ans=1-in;
		dfs(1,0);
		printf("%lld\n",ans%mod);
	}
	return 0;
}
```

---

## 作者：hh弟中弟 (赞：2)

[题目](https://www.luogu.com.cn/problem/CF1929D)

大致题意：在一棵树上选危险点，使得选完以后树上任意两点的简单路径上有不超过 $2$ 个危险点，问方案数 $(\operatorname{mod}p,p=998244353)$

**考虑树形 DP**，设 $f_{i,0/1}$ 表示节点 $i$ 的子树内是否存在有 $2$ 个危险点的路径时的方案数。

对于每个叶子结点，显然有 $f_{i,0}=2$ 和 $f_{i,1}=0$，不妨设 $1$ 节点为根，写出状态转移方程
$$\begin{cases}\large f_{u,0}=(\prod\limits_{v\in son_u} f_{v,0})+1\ \ (\operatorname{mod}p)
\\\large f_{u,1}=f_{u,1}+f_{v,1}+f_{v,0}-1(v\in son_u)\ \ (\operatorname{mod}p)
\end{cases}$$
其中 $f_{u,0}$ 的转移运用了乘法原理，对于所有 $v$ 节点的子树内没有危险点的情况，此时可以选上 $u$ 节点本身，形成一个没有危险路径的新方案，所以要加 $1$。

而 $f_{u,1}$ 的转移运用了加法原理，对于 $v$ 节点的子树内没有危险路径且有危险点的方案数，此时可以选上 $u$ 节点本身形成一个有危险路径的新方案，所以加 $f_{v,0}-1$。

最后输出 $ans=f_{1,0}+f_{1,1}$ 即可。


```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
inline int read(){
    char ch=getchar();int x=0,f=1;
    for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;
    for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
    return x*f;
}
const int mod=998244353,N=3e5+10;
std::vector<int> v[N];
int n,f[N][2];
inline void dfs(int x,int fa){
    if(v[x].size()==1&&v[x][0]==fa){f[x][1]=0,f[x][0]=2;return;}
    int sum=1;
    for(int y:v[x]){
        if(y==fa)continue;
        dfs(y,x);
        sum=sum*f[y][0]%mod;
        f[x][1]=(f[x][1]+f[y][1]+f[y][0]-1+mod)%mod;
    }
    f[x][0]=(sum+1)%mod;
}
inline void work(){
    n=read();
    for(int i=1;i<=n;++i)v[i].clear();
    for(int i=1;i<=n;++i)f[i][1]=f[i][0]=0;
    for(int i=1;i<n;++i){
        int a=read(),b=read();
        v[a].push_back(b),v[b].push_back(a);
    }
    dfs(1,0);
    std::cout<<(f[1][1]+f[1][0])%mod<<'\n';
} 
main(){
    //freopen("in.in","r",stdin),freopen("out.out","w",stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(0),std::cout.tie(0);
    int T=read();
    while(T--)work();
}
```


---

## 作者：COsm0s (赞：1)

树形 dp。

首先，树上的任意一点，满足从根节点到此点的“危险点”的数量只能为 $0,1,2$。

那么我们直接设 $f_{i, j}$ 为从其后代的叶子结点到当前点，每条链的“危险点”的最大值为 $j$ 个（$j \in \{0,1,2\}$）的方案数。

+ $f_{i,0}=1$，这是显然的。

+ 对于 $f_{i,1}$，我们有两种情况：

	+ 使 $i$ 点为危险点，那么其子树内不能有危险点存在，否则就与“危险点为 $1$”矛盾。那么 $f_{i,1} = f_{i,1} + \max\limits_{j=edge_i} f_{j,0}$ 即 $f_{i,1} = f_{i,1} + 1$。
   + 使 $i$ 不是危险点，每棵子树都可以不选点或选一个，即 $f_{i,1} = f_{i,1} + \prod\limits_{j=edge_i} (f_{j,1} + 1)-1$。

	综上，$f_{i,1} = \prod\limits_{j=edge_i} (f_{j,1} + 1)$。
    
+ 对于 $f_{i,2}$，同样有两种情况。

	+ 对于不选 $i$，最多只有一棵子树有 $1$ 个“危险点”，否则就会形成 $3$ 个“危险点”的链（即第一个被选中的点 $\to i\to$ 第二个被选中的点）。
    
    	转移为 $f_{i,2} = f_{i,2} + \sum\limits_{j=edge_i} f_{j,1}$。
    
   + 选 $i$ 则方程同上推导，$f_{i,2} = f_{i,2} + \sum\limits_{j=edge_i} f_{j,2}$。
   
  综上，$f_{i,2} = \sum\limits_{j=edge_i} f_{j,1} + \sum\limits_{j=edge_i} f_{j,2}$。
  
答案即为 $\sum f_{1,j}$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 3e5 + 5, mod = 998244353;
int n, f[N][2];
vector<int> e[N];
void dfs(int u, int fa) {
	for(int v : e[u]) {
		if(v == fa) continue;
		dfs(v, u);
		(f[u][0] *= (f[v][0] + 1)) %= mod;
		(f[u][1] += f[v][0] + f[v][1]) %= mod;
	}
//	cout << e[u].size() << ' ' << f[u][1] << ' ' << f[u][0] << '\n';
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	int T = 1;
	cin >> T;
	while(T --) {
		cin >> n;
		for(int i = 1; i <= n; i ++) 
			e[i].clear(), f[i][0] = 1, f[i][1] = 0;
		for(int i = 1, u, v; i < n; i ++) {
			cin >> u >> v;
			e[u].emplace_back(v);
			e[v].emplace_back(u);
		}
		dfs(1, 0);
		cout << (f[1][1] + f[1][0] + 1) % mod << '\n';
	}
	return 0;
}
```

---

## 作者：2020kanade (赞：0)

题目：[CF1929D](https://www.luogu.com.cn/problem/CF1929D)

少废话直接上做法。当前（2024.2.28）题解区有一篇状态定义一致的写法，但是转移有一点不同，大概算是不同解法。

因为题目对合法路径的限制比较优秀，我们考虑直接在状态里往死里加东西：$f_{u,0/1,0/1/2}$ 为结点 $u$ 的子树中，自己没选或选了（$0/1$），子树中除了点 $u$ 之外所有点到点 $u$ 的路径上被选的点的最大数量为 $0/1/2$ 时的答案。

考虑被选择的点的路径转移方式：$f_{u,0/1,0}$ 都是子树中除了自己之外不能选任意结点，区别只在自己选没选，方案数都是 $1$；$f_{u,1,2}$ 直接就不合法，方案数是 $0$；剩下的部分考虑从子树转移，$f_{u,0,2}$ 这种情况只有一个子树能够选点，否则当前结点会作为 $\operatorname{LCA}$ 被不合法路径撅烂，而这个选点的子树，要么结点自己被选了加上子树里面还有一个，要么两个都在子树里面，这俩分别对应 $f_{v,1,1},f_{v,0,2}$；$f_{u,1,1}$ 同理，为了防止当前结点成为那个被撅烂的 $\operatorname{LCA}$ 只能从一个子树中选剩下的一个点，这个点要么来自儿子的子树内部，要么就是儿子，分别对应 $f_{v,0,1},f_{v,1,0}$，后者直接是 $1$。

相对困难一点的就是 $f_{u,0,1}$，因为此时不存在不同子树之间以当前点作为 $LCA$ 构造不合法路径的情况，会以多个子树作为前继转移。考虑乘法原理，儿子子树可以一个点也不选或者只选一个，选的话这个点也有儿子本身和儿子子树两种来源，转移就是 $f_{u,0,1}=f_{u,0,1}\times(f_{v,0,1}+f_{v,0,0}+f_{v,1,0})$，后两个为定值，直接换成 $1$，转移可以写成 $f_{u,0,1}=f_{u,0,1}\times(f_{v,0,1}+2)$。注意这样直接转移会算重，我们可以分析出来，最终会将一个点也不选的情况也计入，我们直接在转移完成后减 $1$ 即可去重。

最终答案是整棵树中的所有合法情况，也就是 $f_{rt,0,0/1/2}+f_{rt,1,0/1}$，实际上因为 $f_{u,1,2}=0$，加上也无所谓。

时间复杂度线性。这个做法如果写过 [这道典题](https://www.luogu.com.cn/problem/CF461B) 或者 [建造军营](https://www.luogu.com.cn/problem/P8867) 理解大概比较容易。

代码是赛时的，注释里面的方程可能有部分出入，实测没有影响。

```cpp
//written by Amekawa_kanade
#include<bits/stdc++.h>
using namespace std;
void syncoff()//fuck you sync
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
}
#define endl '\n'
const int N=5e5+11;
using ll=long long;
using i128=__int128;
using ld=long double;
const ll JT=998244353;
const ll GEH=1e9+7;
const ll ZLH=1e9+9;
int t,n,k,m,q;
//dp[u][0/1][0/1/2]
//dp[u][0][0]=1
//dp[u][0][1]=dp[u][0][1]*(dp[v][0][0]+dp[v][1][0]+dp[v][0][1])
//dp[u][0][2]=\sum dp[v][0][2]+dp[v][1][1]
//dp[u][1][0]=1
//dp[u][1][1]=\sum dp[v][0][1]+1
//dp[u][1][2]=0
//ans:dp[rt][0][0]+[0][1]+[0][2]+[1][0]+[1][1]
ll f[N][2][3];
vector<int> G[N];
void treedp(int u,int fa)
{
	f[u][0][0]=f[u][1][0]=f[u][0][1]=1;bool son=0;
	for(auto v:G[u])
	{
		if(v==fa) continue;
		treedp(v,u);
		f[u][0][1]=f[u][0][1]*((f[v][0][1]+f[v][1][0]+f[v][0][0])%JT)%JT;
		f[u][0][2]=(f[u][0][2]+(f[v][0][2]+f[v][1][1])%JT)%JT;
		f[u][1][1]=(f[u][1][1]+(f[v][0][1]+f[v][1][0])%JT)%JT;
	}
	f[u][0][1]=(f[u][0][1]-1ll+JT)%JT;
	//cout<<u<<":"<<f[u][0][0]<<' '<<f[u][0][1]<<' '<<f[u][0][2]<<' '<<f[u][1][0]<<' '<<f[u][1][1]<<endl;
}
void clr()
{
	for(int i=1;i<=n;++i) for(int j=0;j<=2;++j) f[i][0][j]=f[i][1][j]=0;
	for(int i=1;i<=n;++i) G[i].clear();
}
void solve()
{
	cin>>n;
	for(int i=1;i<n;++i)
	{
		int iu,iv;cin>>iu>>iv;
		G[iu].push_back(iv),G[iv].push_back(iu);
	}
	treedp(1,0);
	ll ans=(f[1][0][0]+f[1][0][1]+f[1][0][2])%JT;
	//cout<<f[1][0][0]<<' '<<f[1][0][1]<<' '<<f[1][0][2]<<' '<<f[1][1][0]<<' '<<f[1][1][1]<<endl;
	ans=(ans+(f[1][1][0]+f[1][1][1])%JT)%JT;
	cout<<ans<<endl;clr();
}
int main()
{
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：ATZdhjeb (赞：0)

### 题目大意

给定一棵 $n$ 个点的树，称这棵树上的一个点集是好的，当且仅当点集中的点权可能为 $1$ 或 $0$，而点集外的点权均为 $0$ 时，树上任意一条链经过点的点权和不超过 $2$。求好的点集数，对 $998244353$ 取模。

数据组数 $1\le T\le 10^4$。

点数 $2\le \sum n\le 3\times10^5$。

### 简要分析

其实题目等价于计数 **使得树上任一链均不经过超过 $2$ 个选中的点** 的选点方案数。因为根据定义，若一个好的点集中存在 $0$ 权点，那么把它变成 $1$ 之后的点集必然是好的，故我们可以将它中的所有点均赋为 $1$（即选中）；而任一满足上述条件的选点方案也对应了一个只包含选中的点的好的点集。这样选点方案就和好的点集一一对应了。

接下来不妨先排除不选点的情况，令 $f_{0/1,u}$ 表示在以 $u$ 为根的子树中，任意一个点到 $u$ 的链至多经过了 $1/2$ 个选中的点的选点方案数，令 $v$ 为 $u$ 的儿子，考虑转移：

- $f_{0,u}$ 的转移方式：
	1. 当选中 $u$ 时，则不能有子树中存在选中的点，否则该点到 $u$ 至少经过 $2$ 个选中的点，故这种情况对 $f_{0,u}$ 的贡献为 $1$。
   2. 当不选中 $u$ 时，则每颗子树均可以不选点或从 $f_{0,v}$ 做出贡献，故这种情况对 $f_{0,u}$ 的贡献为 $\prod(f_{0,v}+1)-1$。

	综上，$f_{0,u}=\prod(f_{0,v}+1)$。
- $f_{1,u}$ 的转移方式：
	1. 当选中 $u$ 时，至多只能存在一棵子树有选中的点（否则从某一子树中选中的一点出发，经 $u$ 到另一子树中某一选中点的路径经过了至少 $3$ 个选中点），且该子树只能从 $f_{0,v}$ 做出贡献（原因显然）。这种情况对 $f_{1,u}$ 的贡献为 $\sum f_{0,v}$。
   2. 当不选中 $u$ 时，至多只能存在一棵子树有选中的点，且该子树只能从 $f_{1,v}$ 做出贡献，原因与上一种情况类似，不再赘述。此时的贡献为 $\sum f_{1,v}$。
   
   综上，$f_{1,u}=\sum f_{1,v}+\sum f_{0,v}$。
   
然后，这题就做完了，答案就是 $f_{0,1}+f_{1,1}+1$（此时要把不选点的情况加回来）。时间复杂度 $O(n)$，可以通过本题。

### 代码实现

```cpp
#include <bits/stdc++.h>
#define ll long long
#define mp make_pair
#define pii pair<int,int>
#define cpx complex<double>
#define INF 0x3f3f3f3f
#define mod 998244353
#define rep(i,a,b) for (int (i) = (a); (i) <= (b); ++(i))
#define per(i,a,b) for (int (i) = (a); (i) >= (b); --(i))

using namespace std;

inline int input() {
	int x = 0,f = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c <= '9' && c >= '0') {
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
	return x * f;
}

inline char get() {
	char c = getchar();
	while (isspace(c)) c = getchar();
	return c;
}

const double PI = acos(-1);

int T,n,dp[2][300010];
vector<int> e[300010];

void DFS(int u,int fa) {
	dp[0][u] = 1;
	for (int i : e[u]) if (i != fa) {
		DFS(i,u);
		dp[1][u] = (dp[1][u] + (dp[0][i] + dp[1][i]) % mod) % mod;
		dp[0][u] = 1LL * dp[0][u] * (dp[0][i] + 1) % mod;
	}
}

void solve() {
	n = input();
	rep (i,1,n) {
		e[i] = vector<int>();
		dp[0][i] = dp[1][i] = 0;
	}
	rep (i,1,n - 1) {
		int u = input(),v = input();
		e[u].push_back(v);
		e[v].push_back(u);
	}
	DFS(1,0);
	printf("%d\n",(dp[0][1] + dp[1][1] + 1) % mod);
}

int main() {
	T = input();
	while (T--) solve();
	return 0;
}
```

---

## 作者：灵乌路空 (赞：0)

知识点：树形 DP。

发现关键点集合法当且仅当不存在两关键点的 $\operatorname{lca}$ 是另一关键点。这东西看着很树形 DP 的样子，考虑枚举子树的根，考虑以该点为 $\operatorname{lca}$ 的关键点进行 DP。

脑子一抽设了个比较抽象的 DP 状态。记 $f_{u, 0/1}$ 表示钦定节点 $u$ 不选/选，在 $u$ 的子树中以 $u$ 为一端的链上**有且仅有 1 个关键点**且子树合法的以 $u$ 为根的子树的关键点集数；类似地记 $g_{u, 0/1}$ 表示钦定节点 $u$ 不选/选，在 $u$ 的子树中以 $u$ 为一端的链上**有且仅有 2 个关键点**且子树合法的以 $u$ 为根的子树的关键点集数。

注意上面的状态钦定子树中至少有 1 个关键点。显然有 $\forall 1\le u\le n,\ f_{u, 1} = 1$ 恒成立。

然后考虑 DFS 转移。对于节点 $u$，考虑枚举其所有子节点 $v$：
- 对于 $f_{u, 0}$，需要满足在 $v$ 的子树中以 $v$ 为一端的链上关键点数**不大于 1** 且关键点集不能全部为空。发现它们互不影响，则根据乘法原理： 

  $$f_{u, 0} = \prod_{v\in \operatorname{son}(u)} \left(f_{v,0} +f_{v,1} + 1\right) - 1$$
- 对于 $g_{u, 0}$，需要满足**有且仅有一个** $v$ 满足在其子树中以 $v$ 为一端的链上**有且仅有 2 个关键点**，则根据加法原理：
  $$g_{u, 0} = \sum_{v\in \operatorname{son}(u)} \left(g_{v, 0} + g_{v, 1}\right)$$

- 对于 $g_{u, 1}$，需要满足**有且仅有一个** $v$ 满足在其子树中以 $v$ 为一端的链上**有且仅有 1 个关键点**，则根据加法原理：
  
  $$g_{u, 1} = \sum_{v\in \operatorname{son}(u)} (f_{v, 0} + f_{v, 1})$$

答案即为（记得考虑上空集）：

$$f_{1, 0} + f_{1, 1} + g_{1, 0} + g_{1, 1} + 1$$

```cpp
//树形 DP
/*
By:Luckyblock
*/
#include <bits/stdc++.h>
#define LL long long
const int kN = 3e5 + 10;
const LL p = 998244353;
//=============================================================
int n;
LL f[kN][2], g[kN][2];
std::vector <int> v[kN];
//=============================================================
void Dfs(int u_, int fa_) {
  f[u_][1] = 1;
  LL s = 1;
  for (auto v_: v[u_]) {
    if (v_ == fa_) continue;
    Dfs(v_, u_);
    s *= (f[v_][0] + f[v_][1] + 1), s %= p;
    g[u_][0] += (g[v_][0] + g[v_][1]) % p, g[u_][0] %= p;
    g[u_][1] += f[v_][0] + f[v_][1], g[u_][1] %= p;
  }
  f[u_][0] = (s - 1 + p) % p;
  // std::cout << u_ << ":" << f[u_][0] << " " << g[u_][0] << " " << g[u_][1] << "\n";
}
//=============================================================
int main() {
  //freopen("1.txt", "r", stdin);
  std::ios::sync_with_stdio(0), std::cin.tie(0);
  int T; std::cin >> T;
  while (T --) {
    std::cin >> n;
    for (int i = 1; i <= n; ++ i) {
      f[i][0] = f[i][1] = g[i][0] = g[i][1] = 0;
      v[i].clear();
    }
    for (int i = 1; i < n; ++ i) {
      int u_, v_; std::cin >> u_ >> v_;
      v[u_].push_back(v_);
      v[v_].push_back(u_);
    }
    Dfs(1, 0);

    std::cout << (f[1][0] + f[1][1] + g[1][0] + g[1][1] + 1) % p << "\n";
  }
  return 0;
}
```

---

## 作者：Reunite (赞：0)

题意：给一棵树，每个点可以有 $0/1$ 的权，求所有 $2^n$ 种方案中，不存在点权和 $\ge 3$ 的路径的方案数。

## 一
---

这里讲一个赛时的无脑做法吧，我们设 $f_{u,0/1,0/1/2}$ 表示考虑以 $u$ 为根的子树，$u$ 的点权为 $0/1$，子树内**不包含** $u$ 的最大竖直方向的路径和为 $0/1/2$ 的方案数。

初始化，$f_{u,0,0}=f_{u,0,1}=1$。不解释。

考虑 $u$ 与第一棵子树合并，我们显然有：

$$f_{u,i+j,x}=\sum_{j \in {0,1},i \in{0,1,2}} f_{v,i,j} \ (x\in{0,1},i+j+x \le2)$$

然后考虑 $u$ 与非第一棵子树合并，有：

$$F_{\max(i,j+y),x}=\sum_{x \in{0,1},y\in{0,1},i\in{0,1,2},j\in{0,1,2}}f_{u,i,x}\cdot f_{v,j,y} \ (i+x+y+j \le 2))$$

这里的 $F$ 是因为防止计数时数据的重复覆盖。

时空复杂度是 $O(n)$ 的，应该有更简洁的做法，但赛时无脑简单就对了。

---

## 二
---
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define int long long
#define mod 998244353
using namespace std;

int t,n;
int f[300005][3][2];
vector <int> g[300005];

inline void in(int &n){
	n=0;
	char c=getchar();bool ok=c=='-';
	while(c<'0' || c>'9') c=getchar(),ok|=c=='-';
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	n=(ok?-n:n);
	return ;
}

inline void dfs(int u,int fa){
	f[u][0][0]=f[u][0][1]=1;
	bool ok=1;
	for(int v:g[u]){
		if(v==fa) continue;
		dfs(v,u);
		int F[10][2]={0};
		if(ok){
			for(int x:{0,1}){
				for(int y:{0,1}){
					for(int i:{0,1,2}){
						if(i+x+y>=3) continue;
						(F[i+y][x]+=f[v][i][y])%=mod;
					}
				}
			}
			for(int x:{0,1})
				for(int y:{0,1,2})
					f[u][y][x]=F[y][x];

			ok=0;
			continue;
		}
		for(int x:{0,1}){
			for(int y:{0,1}){
				for(int i:{0,1,2}){
					for(int j:{0,1,2}){
						if(x+y+i+j>=3) continue;
						int xx=max(i,j+y);
						(F[xx][x]+=f[u][i][x]*f[v][j][y]%mod)%=mod;
					}
				}
			}
		}
		for(int x:{0,1})
			for(int y:{0,1,2})
				f[u][y][x]=F[y][x];
	}

}

signed main(){
	in(t);
	while(t--){
		in(n);
		for(int i=1;i<=n;i++) g[i].clear(),f[i][0][0]=f[i][1][0]=f[i][2][0]=f[i][0][1]=f[i][1][1]=f[i][2][1]=0;
		for(int i=1;i<n;i++){
			int u,v;
			in(u),in(v);
			g[u].emplace_back(v);
			g[v].emplace_back(u);
		}
		dfs(1,0);
		int s=0;
		for(int x:{0,1})
			for(int y:{0,1,2})
				if(x+y<=2)
					(s+=f[1][y][x])%=mod;
		printf("%lld\n",s);
	}

	return 0;
}
```

---

