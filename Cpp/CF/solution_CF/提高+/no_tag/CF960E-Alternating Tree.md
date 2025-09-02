# Alternating Tree

## 题目描述

Given a tree with $ n $ nodes numbered from $ 1 $ to $ n $ . Each node $ i $ has an associated value $ V_i $ .

If the simple path from $ u_1 $ to $ u_m $ consists of $ m $ nodes namely $ u_1 \rightarrow u_2 \rightarrow u_3 \rightarrow \dots u_{m-1} \rightarrow u_{m} $ , then its alternating function $ A(u_{1},u_{m}) $ is defined as $ A(u_{1},u_{m}) = \sum\limits_{i=1}^{m} (-1)^{i+1} \cdot V_{u_{i}} $ . A path can also have $ 0 $ edges, i.e. $ u_{1}=u_{m} $ .

Compute the sum of alternating functions of all unique simple paths. Note that the paths are directed: two paths are considered different if the starting vertices differ or the ending vertices differ. The answer may be large so compute it modulo $ 10^{9}+7 $ .

## 说明/提示

Consider the first example.

A simple path from node $ 1 $ to node $ 2 $ : $ 1 \rightarrow 2 $ has alternating function equal to $ A(1,2) = 1 \cdot (-4)+(-1) \cdot 1 = -5 $ .

A simple path from node $ 1 $ to node $ 3 $ : $ 1 \rightarrow 3 $ has alternating function equal to $ A(1,3) = 1 \cdot (-4)+(-1) \cdot 5 = -9 $ .

A simple path from node $ 2 $ to node $ 4 $ : $ 2 \rightarrow 1 \rightarrow 4 $ has alternating function $ A(2,4) = 1 \cdot (1)+(-1) \cdot (-4)+1 \cdot (-2) = 3 $ .

A simple path from node $ 1 $ to node $ 1 $ has a single node $ 1 $ , so $ A(1,1) = 1 \cdot (-4) = -4 $ .

Similarly, $ A(2, 1) = 5 $ , $ A(3, 1) = 9 $ , $ A(4, 2) = 3 $ , $ A(1, 4) = -2 $ , $ A(4, 1) = 2 $ , $ A(2, 2) = 1 $ , $ A(3, 3) = 5 $ , $ A(4, 4) = -2 $ , $ A(3, 4) = 7 $ , $ A(4, 3) = 7 $ , $ A(2, 3) = 10 $ , $ A(3, 2) = 10 $ . So the answer is $ (-5) + (-9) + 3 + (-4) + 5 + 9 + 3 + (-2) + 2 + 1 + 5 + (-2) + 7 + 7 + 10 + 10 = 40 $ .

Similarly $ A(1,4)=-2, A(2,2)=1, A(2,1)=5, A(2,3)=10, A(3,3)=5, A(3,1)=9, A(3,2)=10, A(3,4)=7, A(4,4)=-2, A(4,1)=2, A(4,2)=3 , A(4,3)=7 $ which sums upto 40.

## 样例 #1

### 输入

```
4
-4 1 5 -2
1 2
1 3
1 4
```

### 输出

```
40
```

## 样例 #2

### 输入

```
8
-2 6 -4 -4 -9 -3 -7 23
8 2
2 3
1 4
6 5
7 6
4 7
5 8
```

### 输出

```
4
```

# 题解

## 作者：Awlgot (赞：7)

## CF960E：



提供一种简洁易懂的写法。

可简化为树上黑白染色。

首先想到树形DP，如果是棵有根树，状态转移方程如下：
$$
{f[x][0]=f[y][1]+siz[y] \times a[x]}
$$

$$
f[x][1]=f[y][0]-siz[y]\times a[x]
$$

记 $siz[x]$ 表示子树大小，$f[x][0/1]$ 表示当前点颜色为 $0/1$ 时的答案。

因为对于子树中每个点都会有一条路径，所以每新加入一个点 $x$，贡献为 $siz[x]\times a[x]\times (-1)^{0/1}$。

现在就有了一个 $O(n^2)$ 的做法。

考虑换根。

设 $g[x][0/1]$ 表示以当前点 $x$ 为根时的答案。

就是减去父节点对以当前点为起点的路径的贡献，再加上当前点应产生的贡献。

转移方程如下：
$$
g[y][0]=g[x][1]+siz[y]\times a[x]+(n-siz[y])\times a[y]
$$

$$
g[y][1]=g[x][0]-siz[y]\times a[x]-(n-siz[y])\times a[y]
$$

时间复杂度 $O(n)$。

[code](https://codeforces.com/contest/960/submission/176151017)

---

## 作者：localhost (赞：6)

这篇题解可能是对楼下的补充

我们考虑每个点能贡献多少次

![无标题.png](https://i.loli.net/2019/10/25/Evy74V8rpIaec1F.png)

设当前节点为$x$,路径有三种情况，上图分别对应情况$1$，情况$2$，情况$3$

1. $x$子树内$\rightarrow x \rightarrow x$子树外(包括$x$)
    
2. $x$子树内(包括$x$)$\rightarrow x \rightarrow x$子树内

3. $x$子树外$\rightarrow x \rightarrow x$子树内

我们可以先处理出与$x$的距离为偶数和与$x$的距离为奇数的点的个数，分别记作$f_x,g_x$

那么$f_x = 1 + \sum g_{to},g_x = 1 + \sum f_{to}$($to$指$x$的孩子)

我们来考虑所有情况

1. $ans += V_x \times (f_x-g_x) \times (n-siz_x+1)$(可以在$x$的子树中随机选一个往子树外面走(可以指走到$x$))

2. $ans += V_x \times (g_{to}-f_{to}) \times (siz_x-siz_{to}-1)$
  
   $ans+= V_x \times (siz_x-1)$(可以从$x$直接向下走)

3. 我们需要记录$x$子树外与$x$的距离为偶数和与$x$的距离为奇数的点的个数，分别记作$uf_x,ug_x$

	我们可以通过$bfs$从上到下来处理,那么
    
   $uf_x=ug_{fa_x}+g_{fa_x}-f_x$
    
   $ug_x=uf_{fa_x}+f_{fa_x}-g_x$
   
   $ans += V_x \times (uf_x-ug_x) \times siz_x$
   
接下来放代码：

```cpp
#include<bits/stdc++.h>
#define Fur(i,x,y) for(int i=x;i<=y;++i)
#define fl(i,x) for(int i=head[x],to;to=e[i].to,i;i=e[i].nxt)
using namespace std;
#define N 200011
#define mod 1000000007
int n,cnt=0,head[N];
long long ans=0;
struct edge{
    int to,nxt;
}e[N*2];
void add(int x,int y){
    e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;
}
int a[N],siz[N],f[N],g[N],fa[N];
void dfs(int x){
    f[x]=siz[x]=1;
    fl(i,x)if(to!=fa[x]){
        fa[to]=x;dfs(to);
        siz[x]+=siz[to];
        f[x]+=g[to];
        g[x]+=f[to];
    }
    // 1:
    ans=(ans+1ll*(f[x]-g[x])*(n-siz[x]+1)%mod*a[x]%mod)%mod;
    //2:
    ans=(ans+1ll*(siz[x]-1)*a[x]%mod)%mod;
    fl(i,x)if(to!=fa[x])
        ans=(ans+1ll*(g[to]-f[to])*(siz[x]-siz[to]-1)%mod*a[x]%mod)%mod;
}
int uf[N],ug[N];
void bfs(){
    queue<int>q;
    fl(i,1)q.push(to);
    while(!q.empty()){
        int x=q.front();q.pop();
        uf[x]=ug[fa[x]]+g[fa[x]]-f[x];
        ug[x]=uf[fa[x]]+f[fa[x]]-g[x];
        ans=(ans+1ll*(uf[x]-ug[x])*siz[x]%mod*a[x]%mod)%mod;
        fl(i,x)if(to!=fa[x])q.push(to);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin>>n;
    Fur(i,1,n)cin>>a[i];
    int x,y;
    Fur(i,1,n-1)cin>>x>>y,add(x,y),add(y,x);
    dfs(1);
    bfs();
    cout<<(ans+mod)%mod<<endl;
}
```

---

## 作者：yijan (赞：4)

~~不知道为啥今天突然想水篇题解~~

感觉比较典型的树上dp。。

考虑对于每一个点的权值会被记录多少次（（

（稍微思考一下会发现）经过点$u$的路线一定只有三种情况

1. 从$u$为根的子树上的一点到树中除开$u$子树的点（下---$u$---上）
2. 设$u$的儿子$v$，从$v$的子树中选择一点到除了$v$的另外一个儿子的子树上的一点（下---$u$---另一个下）
3. 从除了$u$为根的子树上的点到$u$再到$u$为根的子树上的一点（上---$u$---下）

这里要注意，由于题目这个“有向权值”的特殊性，第一种和第三中不能合并。。因为从下想上$u$的权值可能是正的，但是从上向下就不一定了呢！

那么怎么讨论上面的三种情况呢？下面就是树形dp的套路了

考虑记录一个S[x][0/1]表示$x$点为根的子树上：

0： 有多少个点到$x$距离为偶数  
1： 有多少个点到$x$距离为奇数

首先这个数组是可以dp的。。因为毕竟只统计子树上的没有后效性

那么对于第一种情况（显然）

$ans = ans + (s[u][0]-s[u][1]) \times (n - siz[u] + 1) \times V[u]$

第二种情况就有点小坑了，注意$u$本身向下的情况也需要讨论进去。。那么对于儿子$v$有： （这里的siz是指已经统计完了的整个子树的siz）

$ans = ans + (s[v][1] - s[v][0]) \times (siz[u]-siz[v]-1) \times V[u]$

（后面的-1是要排除自己到自己的情况，因为已经在第一种情况算过了）  
第二种情况还没完！还有自己向下

$ans = ans + (siz[u]-1)\times V[u]$

第三种情况的统计可能稍微麻烦点，但是也是树形dp的套路

考虑对所有点按照深度排序，用一个数组sup[u][0/1]来记录从$u$上方到达$u$的距离为偶数/奇数个的个数。由于深度是排序了的，sup也可以直接通过$u$的父亲dp出来。。有如下递推式（$pre[u]$表示$u$的父亲）

$sup[u][0] = sup[pre[u]][1] + s[pre[u]][1] - s[u][0]$

（1 类似不累赘）

然后用sup就可以轻松统计第三种情况的答案了呢~

$ans = ans + (sup[u][0] - sup[u][1]) \times siz[u] \times V[u]$


非常需要注意的是边界情况的讨论（就是$u$本身到其他的点的情况的计算），这个细节~~困扰了菜鸡我10分钟~~细想一下就可以做不累赘了~~

code

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector>
using namespace std;
#define MAXN 200006
#define P 1000000007
typedef long long ll;
int n , V[MAXN];
vector<int> G[MAXN];
int s[MAXN][2] , siz[MAXN] , pre[MAXN] , dep[MAXN] , sup[MAXN][2];
ll ans , tot;
void dfs( int u , int fa ) {
	siz[u] = 1 , s[u][0] = 1;
	for( int i = 0 ; i < G[u].size() ; ++ i ) {
		int v = G[u][i];
		if( v == fa ) continue;
		pre[v] = u , dep[v] = dep[u] + 1;
		dfs( v , u );
		s[u][0] += s[v][1] , s[u][1] += s[v][0];
		siz[u] += siz[v];
	}
	for( int i = 0 ; i < G[u].size() ; ++ i ) {
		int v = G[u][i];
		if( v == fa ) continue;
		ans += 1ll * ( s[v][1] - s[v][0] ) % P * V[u] % P * ( siz[u] - siz[v] - 1 ) % P , ans %= P;
	}
	ans += 1LL * ( siz[u] - 1 ) * V[u] % P , ans %= P;
	ans += 1LL * ( s[u][0] - s[u][1] ) * V[u] % P * ( n - siz[u] + 1 ) % P , ans %= P;
}
int idx[MAXN];
bool cmp( int a , int b ) {
	return dep[a] < dep[b];
}
int main() {
	cin >> n;
	for( int i = 1 ; i <= n ; ++ i ) 
		scanf("%d",&V[i]) , tot += 1LL * V[i] , idx[i] = i;
	for( int i = 1 , u , v ; i < n ; ++ i ) {
		scanf("%d%d",&u,&v);
		G[u].push_back( v ) , G[v].push_back( u );
	}
	dfs( 1 , 1 );
	sort( idx + 1 , idx + 1 + n , cmp );
	for( int i = 2 , u ; i <= n ; ++ i ) {
		u = idx[i];
		sup[u][0] = sup[pre[u]][1] + ( s[pre[u]][1] - s[u][0] );
		sup[u][1] = sup[pre[u]][0] + ( s[pre[u]][0] - s[u][1] );
		ans += 1LL * ( sup[u][0] - sup[u][1] ) % P * V[u] % P * ( siz[u] ) % P , ans %= P;
	}
	cout << ( ans + P ) % P << endl;
} 
```

---

## 作者：Hovery (赞：2)

## Problem

[Alternating Tree
](https://www.luogu.com.cn/problem/CF960E)

## Sol

比较简单的题，就对于每个节点来说，一条链会有两种情况覆盖到它。

$1.$ 子树内的点到当前点再到子树外。

$2.$ 子树内的点到当前点再到另一棵子树。

然后又看到这个点的贡献会和 $-1$ 的次方有关，考虑分奇偶处理。

由于它的贡献只和到起点的奇偶性有关，统计答案就不讲了，反正自己能推出来。

先以 $1$ 为根把整棵子树遍历一遍，然后找到它子树内有几个点（包括它自己）到它的距离为奇数/偶数。扫的时候可以顺便把第二种情况做了。

至于第一种情况，去用换根求出它子树外到它的距离为奇数/偶数的点，然后就可以把第一种情况也处理了。

## Code

```cpp
#include<bits/stdc++.h>
#define pb push_back
#define int long long
using namespace std;

const int mod = 1e9 + 7;

int n;
int a[200010], f[200010][2], ans = 0;
vector<int> G[200010];

void dfs(int now, int fa)
{
    f[now][0] = 1;
    for (auto i : G[now])
    if (i ^ fa)
    {
        dfs(i, now);
        int x, y;
        x = f[i][0];
        y = f[i][1];
        ans = ans + (f[now][0] - f[now][1]) * (x + y) % mod * a[now] % mod;
        ans = (ans % mod + mod) % mod;
        ans = ans + (y - x) * (f[now][0] + f[now][1]) % mod * a[now] % mod;
        ans = (ans % mod + mod) % mod;
        f[now][0] += y;
        f[now][1] += x;
    }
}

void dfss(int now, int fa)
{
    if (now == 1)
    {
        for (auto i : G[now])
        if (i ^ fa)
        {
            dfss(i, now);
        }
        return;
    }
    int x = f[fa][0] - f[now][1], y = f[fa][1] - f[now][0];//x -> even to fa
    ans = ans + (f[now][0] - f[now][1]) * (x + y) % mod * a[now] % mod;
    ans = (ans % mod + mod) % mod;
    ans = ans + (y - x) * (f[now][0] + f[now][1]) % mod * a[now] % mod;
    ans = (ans % mod + mod) % mod;
    f[now][0] += y;
    f[now][1] += x;
    for (auto i : G[now])
    if (i ^ fa)
    {
        dfss(i, now);
    }
}

signed main()
{
    cin >> n;
    for (int i = 1;i <= n;i++)
    {
        cin >> a[i];
    }
    for (int i = 1;i < n;i++)
    {
        int x, y;
        cin >> x >> y;
        G[x].pb(y);
        G[y].pb(x);
    }
    dfs(1, 0);
    dfss(1, 0);
    for (int i = 1;i <= n;i++)
    {
        ans = ((ans + a[i]) % mod + mod) % mod;
    }
    cout << ans;
}
```

---

## 作者：__stick (赞：2)

# 题意
给出一颗有点权的树，树上有向路径 $\{a_1,a_2,\cdots,a_k \}$ 的权值被定义为：
$$
\sum_{i=1}^k(-1)^{i+1}\cdot w_{a_i}
$$

求树上所有路径的权值和。

# 思路
拿来练习点分治真的很不错。

这个题是询问树上所有路径和，首先想到点分治，考虑如果快速求出来经过根节点的答案。

首先不难想到按顺序考虑子树，考虑一个的贡献后加一个（这个会点分治的应该都会吧）。

想如何维护这个贡献，不难想到对树上路径按照结尾节点深度的奇偶性分层，则答案就很好统计。

由于限制路径必须经过根节点，所以我们发现合法路径两个端点必须处在奇偶性相同的层上（根节点两侧的正负必须保持一致）。

于是只需要维护一下已经遍历过部分的奇数/偶数深度的路径权值和，数量和，记为 $sum1,sum2,siz1,siz2$。

则在算贡献的时候直接大力讨论取对应奇偶性的节点考虑即可，如果当前是奇数，则算上贡献 $sum1+siz1\times dis$，偶数就注意了，我们的 $dis$ 是按照根节点是正数的情况求的，此时开头节点的权值是负的，不合法，所以路径贡献整体乘上 $-1$ 即可。

实现细节看代码。

然后就可以快乐分治下去了。

# code
这里有一个坑点，求重心要重新求 siz，虽然不求复杂度正确，但是有一个较大的常数，这里在处理当前节点的时候顺手重新求一遍 siz 即可，否则会 TLE 72。

```cpp
const int MAXN=2e5+10;
vector<int>e[MAXN];
int siz[MAXN],son[MAXN];
bool book[MAXN];
int rt,sum;
void getroot(int u,int fa)
{
	siz[u]=1,son[u]=0;
	for(auto&v:e[u])if(v^fa&&!book[v])
	{
		getroot(v,u);
		siz[u]+=siz[v];
		cmax(son[u],siz[v]);
	}
	cmax(son[u],sum-siz[u]);
	if(son[u]<son[rt])rt=u;
 
}
int a[MAXN];
ll ans=0;
ll s1=0,s2=0;
int siz1,siz2;
void getdis(int u,int fa,int op,int d)
{
	if(op)(d+=a[u])%=mod,ans+=(s1+(ll)d*siz1)%mod;
	else (d+=mod-a[u])%=mod,ans+=mod-(s2+(ll)d*siz2)%mod;
	for(auto& v:e[u])
	{
		if(v==fa||book[v])continue;
		getdis(v,u,op^1,d);	
	}	
}
void insert(int u,int fa,int op,int d)
{
	if(op)(d+=a[u])%=mod,siz1++,(s1+=d)%=mod;
	else (d+=mod-a[u])%=mod,siz2++,(s2+=d)%=mod;
	siz[u]=1;
	for(auto& v:e[u])
	{
		if(v==fa||book[v])continue;
		insert(v,u,op^1,d);	
		siz[u]+=siz[v];
	}
}
void getans(int u)
{
	s1=0,s2=0;
	siz1=siz2=0;
	s1+=a[u],siz1++;
	for(auto& v:e[u])if(!book[v])
	{	
		getdis(v,u,0,0);
		insert(v,u,0,a[u]);//这里带上根节点的权值，原因显然
		siz[u]+=siz[v];//在这里顺手求一下当前树正确的 siz
	}
}
void dfs(int u)
{
	book[u]=1;
	getans(u);
	for(auto&v:e[u])if(!book[v])
	{
		rt=0,sum=siz[v],getroot(v,u);	
		dfs(rt);
	}
}
signed main()
{
	son[0]=1e9;
	int n=R();
	for(int i=1;i<=n;i++)a[i]=(R()%mod+mod)%mod;
	int u,v;
	for(int i=1;i<n;i++)
	{
		u=R(),v=R();
		e[u].push_back(v);
		e[v].push_back(u);
	}
	sum=n;

	dfs(1);
	ans=ans*2%mod;//有向，所以乘 2
	for(int i=1;i<=n;i++)ans+=a[i];//一个点也算路径！
	cout<<ans%mod;
	return 0;
}
```


---

## 作者：liujiaxi123456 (赞：1)

## 关键词：最优解法，详细数学式子
### 思路：
**全局点对贡献**，考虑在 $lca$ 处统计跨越答案。

设当前 $lca$ 为 $u$，当前枚举到第 $i$ 个儿子为 $v$，$u$ 的前 $i-1$ 个子树中一点到 $u$ 的距离（不包括 $u$ 点权）为 $x$，$v$ 子树中一点到 $v$ 的距离（不包括 $u$ 点权）为 $y$，则可得到如下式子：

$ans_{u} = \sum \sum x+y$

$ans_{u} = \sum\left\{x(size_v+1)+\sum y\right\}$

$ans_{u} = (size_v+1)\sum x + size_u\sum y$

显然，$\sum x$ 和 $\sum y$ 都是可以预处理的。

发现长度为偶数的路径由于求两遍，会抵消，因此只需要求奇数路径，最后再乘二即可。

因此，记录 $f_u$ 和 $g_u$ 分别表示路径长度为奇数/偶数时的 $\sum x$，如下：

$ans_u = \left\{\begin{matrix}
  & g_u\cdot fsize_v + f_v\cdot gsize_u\\
  & f_u\cdot gsize_v + g_v\cdot fsize_u
\end{matrix}\right.$

$f_u' = f_u + g_v - a_u\cdot gsize_v$

$g_u' = g_u + f_v + a_u\cdot fsize_v$

式子很优美，常数也很小，轻松最优解。

具体边界看代码。
### Code：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn = 2e5+5, MOD = 1e9+7;

namespace EDGE {
	int sz, head[Maxn];
	struct Edge { int next, to; } edge[Maxn*2];
	inline void Add_edge(int u, int v) {
		edge[++sz] = {head[u], v};
		head[u] = sz;
	}
} using namespace EDGE;

namespace Josh_zmf {
	
	int N; ll fsize[Maxn], gsize[Maxn], a[Maxn], f[Maxn], g[Maxn], ans;

	inline void dfs(int u, int faa) {
		gsize[u]++, g[u] += a[u];
		for(int i=head[u], v; i; i=edge[i].next) {
			v = edge[i].to;
			if(v == faa)	continue;
			dfs(v, u);
			// printf("u:%d, v:%d, ans:%lld, fu:%lld, gu:%lld, fszu:%d, gszu:%d\n", u, v, ans, f[u], g[u], fsize[u], gsize[u]);
			ans += g[u]*(fsize[v]) + gsize[u]*f[v];
			ans += f[u]*(gsize[v]) + fsize[u]*g[v];
			(f[u] += g[v] - a[u]*gsize[v]) %= MOD, fsize[u] += gsize[v];
			(g[u] += f[v] + a[u]*fsize[v]) %= MOD, gsize[u] += fsize[v];
		}
		ans %= MOD, fsize[u] %= MOD, gsize[u] %= MOD;
		// printf("u:%d, ans:%lld, f:%lld, g:%lld, fsize:%lld, gsize:%lld\n", u, ans, f[u], g[u], fsize[u], gsize[u]);
	}

	inline int main() {
		cin>> N; ll tmp = 0;
		for(int i=1; i<=N; i++)	cin>> a[i], tmp += a[i];
		for(int i=1, u, v; i<N; i++)	cin>> u>> v, Add_edge(u, v), Add_edge(v, u);
		dfs(1, 0);
		cout<< ((ans*2 + tmp)%MOD + MOD) %MOD;
		return 0;
	}

}

int main() {
	Josh_zmf::main();
	return 0;
}
```
### 结语：
都看到这里了，点个赞再走吧。：）

---

## 作者：Chthologist7507 (赞：1)

树上 DP。

考虑每一条经过 $u$ 的路径的走向，可分为 $3$ 类。

- 子树 $\rightarrow u\rightarrow$ 其他。

- 其他 $\rightarrow u\rightarrow$ 子树。

- 子树 $\rightarrow u\rightarrow$ 子树。

我们设 $s[u][0]$ 表示以 $u$ 为根的子树中距离 $u$ 为偶数的点数，$s[u][1]$ 表示以 $u$ 为根的子树中距离 $u$ 为奇数的点数。

- 对于情况 $1$，贡献为 $(s[u][0]-s[u][1])\times w[u]\times(n-sz[u]+1)$，$w[u]$ 表示点权，$sz[u]$ 表示子树节点数。

- 对于情况 $2$，我们要统计 $u$ 上方（即深度小于 $u$）的距离 $u$ 为奇数或偶数的点数，分别为 $f[u][0]$ 和 $f[u][1]$，那么贡献为 $(f[u][0]-f[u][1])\times w[u]\times sz[u]$，考虑计算 $f$，我们将节点按照深度排序之后就有 $f[u][0]=f[fa[u]][1]+s[fa[u]][1]-s[u][0],f[u][1]=f[fa[u]][0]+s[fa[u]][0]-s[u][1]$。

- 对于情况 $3$，贡献为 $(s[v][1]-s[v][0])\times w[u]\times(sz[u]-sz[v]-1)+(sz[u]-1)\times w[u]$，分别表示 $u$ 子树向下和 $u$ 节点向下。

没了，坑点主要在于关于 $u$ 自身的讨论。

[code](https://codeforces.com/contest/960/submission/166661813)

---

## 作者：w33z8kqrqk8zzzx33 (赞：1)

给一个代码量少一点，适合比赛时写的一个换根 dp 做法。

考虑每一个节点的贡献是由什么造成的：

 1. 这个点当起点，去所有别的店（每次 $1$ 贡献）
 2. 这个点当一个中间点或者终点，并且里起点偶数边的距离（每次 $1$ 贡献）
 3. 当边的距离是奇数（每次 $-1$ 贡献）

显然类型 1 贡献次数是 $n$。假设当前节点是根节点，固定一下起点所在的子树。那么 2 的从某个子树贡献次数就是（子树里偶数距离节点个数）乘（全局在这个子树外的点），3 是对奇数距离类似情况。偶数距离和奇数距离节点个数可以直接用换根维护。

赛时代码：

```cpp
// writer: w33z8kqrqk8zzzx33
#include <bits/stdc++.h>
using namespace std;

#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)
#define fi first
#define se second
#define pb push_back
 
#define ll long long
#define pii pair<int, int>
//#define int ll
const int MOD = 1000000007;

struct data {
    int ev, od;
} ndat[200005];

void makeFa(int fa, int ch) {
    ndat[fa] = {ndat[fa].ev + ndat[ch].od, ndat[fa].od + ndat[ch].ev};
}

void disown(int fa, int ch) {
    ndat[fa] = {ndat[fa].ev - ndat[ch].od, ndat[fa].od - ndat[ch].ev};
}

ll ans = 0;
vector<int> elist[200005];
int val[200005], n;

void dfs1(int u, int f) {
    ndat[u] = {1, 0};
    for(int& v:elist[u]) {
        if(v == f) continue;
        dfs1(v, u);
        makeFa(u, v);
    }
}

void reroot(int u, int f) {
    ll oans = ans;
    ans = (ans + 1ll * val[u] * n) % MOD;
    for(int& v:elist[u])
        ans = (ans + 1ll * val[u] * (n - ndat[v].ev - ndat[v].od) % MOD *
        (MOD + ndat[v].od - ndat[v].ev)) % MOD;
    for(int& v:elist[u]) {
        if(v == f) continue;
        disown(u, v);
        makeFa(v, u);
        reroot(v, u);
        disown(v, u);
        makeFa(u, v);
    }
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    rep1(i, n) {
        cin >> val[i];
        val[i] = (MOD + val[i]) % MOD;
    }
    rep(i, n-1) {
        int u, v; cin >> u >> v;
        elist[u].pb(v);
        elist[v].pb(u);
    }
    dfs1(1, -1);
    reroot(1, -1);
    cout << ans << endl;
}

```

---

## 作者：皎月半洒花 (赞：1)

秒了。~~指想出来但写了一年~~

然后一眼就是点分…不过好像比较麻烦的样子。

或者考虑直接树形 $dp$ 。就只需要统计出每个点在多少条路径上是奇数位置，多少条路径上是偶数位置。这个可以用比较 trivial 的 up_and_down 技巧来做。具体的，考虑对于奇偶位置分别维护三个信息，$f,g,h$ 分别表示「起点在子树外、终点在子树内」、「起点在子树内，终点在子树外」、「起点在子树内，终点在子树内」三种信息，其中第三种依赖于第二种，第一种需要第二种进行 up_and_down 。这样就可以结合子树 $size$ 直接算出贡献来了。

有小细节需要注意。就是 $f_x,g_x$ 在处理奇数的时候需要判一下 $x$ 的边界。

```cpp
#include <cstdio>

#include <vector>

typedef long long ll ;

typedef std :: vector <int> vint ;

#define il inline

#define p_b push_back

const int N = 200010 ;

const int P = 1000000007 ;

using namespace std ;

ll ans ;

int n ;
ll f[N][3] ;
ll g[N][3] ;
int size[N] ;
int base[N] ;

vint E[N] ;

template <typename T>
il void add(T &x, ll y, int mod = P){
    x += y ; x = x >= mod ? x - mod : x ;
}
template <typename T>
il void dec(T &x, ll y, int mod = P){
    x -= y ; x = x < 0 ? x + mod : x ;
}

void dfs(int x, int fa){
    f[x][0] = size[x] = 1 ;
    for (auto y : E[x]){
        if (y == fa) continue ;
        dfs(y, x) ; size[x] += size[y] ;
        f[x][0] += g[y][0] ; g[x][0] += f[y][0] ;
    }
    for (auto y : E[x]){
        if (y == fa) continue ;
        add(f[x][2], (size[x] - size[y] - 1) * g[y][0] % P) ;
        add(g[x][2], (size[x] - size[y] - 1) * f[y][0] % P) ;
    }
}
void dfs2(int x, int fa){
    for (auto y : E[x]){
        if (y == fa) continue ;
        f[y][1] = g[x][1] ;
        g[y][1] = f[x][1] ;
        f[y][1] += (g[x][0] - f[y][0]) ;
        g[y][1] += (f[x][0] - g[y][0]) ;
        dfs2(y, x) ;
    }
}
void solve(){
    for (int x = 1 ; x <= n ; ++ x){
        add(ans, f[x][2] * base[x] % P) ;
        dec(ans, g[x][2] * base[x] % P) ;
        dec(ans, base[x]) ;
//        printf("%lld\n", ans) ;
        add(ans, (f[x][1] + 1) * size[x] % P * base[x] % P) ;
//        printf("%lld\n", ans) ;
        add(ans, f[x][0] * (n - size[x] + 1) % P * base[x] % P) ;
//        printf("%lld\n", ans) ;
        dec(ans, g[x][1] * size[x] % P * base[x] % P) ;
//        printf("%lld\n", ans) ;
        dec(ans, g[x][0] * (n - size[x] + 1) % P * base[x] % P) ;
//        printf("%lld\n", ans) ; puts("-----------") ;
    }
}
int main(){
    scanf("%d", &n) ; int x, y ;
    for (int i = 1 ; i <= n ; ++ i) scanf("%d", &base[i]) ;
    for (int i = 1 ; i < n ; ++ i)
        scanf("%d%d", &x, &y), E[x].p_b(y), E[y].p_b(x) ;
    dfs(1, 0) ; dfs2(1, 0) ; solve() ; printf("%lld\n", ans % P) ;
}
```


---

## 作者：SFlyer (赞：0)

鉴定为：2 min 会，30 min 写。

对于每一个点计算答案。求子树中，有多少个奇数/偶数长度的链。如果 $1$ 为根，$f_{u,0}=\sum f_{v,1}+1,f_{u,1}=\sum f_{v,0}$。然后换根。发现这个是对的，但是有点难写（就是，还得一边算一边贡献答案），因此考虑其他做法。

我们讨厌的是啥？就是绕弯（i.e. $u\rightarrow lca(u,v)\rightarrow v$）。所以设 $f_{i,0/1}$ 为 $u$ 子树中的链，现在 $u$ 是加还是减，的总贡献。其实就是我们变成了对于每一格起始端点计算答案，这样如果起始端点是根，就没有绕弯了，也可以换根 dp，更好写。换根的时候不要忘了减去父亲的贡献！

$f_{u,0}=a_u+\sum_v f_{v,1}+a_u\times sz_v$，$g_{v,0}=\sum g_{u,1}+a_v\times (n-sz_v)-(-a_u\times sz_v)$，$f/g_{*,1}$ 的情况同理。

---

## 作者：SamHJD (赞：0)

> 给出一棵有点权的树，对于一条路径，设与起点距离为偶数（包括起点）的点的集合为 $S$，其余点集合为 $T$，则这条路径的贡献为 $\sum_{u\in S} a_u-\sum_{u\notin S} a_u$。
>
> 求所有路径的贡献和。

不难发现将整个图黑白染色后，相同颜色的点即为满足 $dis(u,v)\equiv 0\pmod 2$ 的点对。

单独考虑每个点的贡献。

设当前点为 $u$，我们找出所有与 $u$ 同色的点，以这些点为起点并且经过 $u$ 的路径都可以使 $u$ 造成 $a_u$ 的贡献，不同色的点同理，经过 $u$ 的路径会使 $u$ 造成 $-a_u$ 的贡献。

设 $c_i\in[0,1]$ 为 $i$ 的颜色，$cnt_{i,0/1}$ 为 $i$ 的子树中颜色为 $1/0$ 的点的个数，枚举 $u$ 的字节点 $v$，可以写出计算式：
$$
ans_u=\begin{cases}(cnt_{v,c_u}-cnt_{v,1-c_u})\times (n-siz_v)\times a_u\\((cnt_{1,c_u}-cnt_{u,c_u})-(cnt_{1,1-c_u}-cnt_{u,1-c_u}))\times siz_u\times a_u\\n\times a_u\end{cases}
$$
其中第一个式子为 $u$ 子结点的子树的贡献，第二个式子为树上除去 $u$ 子树的部分的贡献，第三个式子为以 $u$ 为起点的路径的贡献。

```cpp
#include "bits/stdc++.h"
#define int long long 
#define rep(i,s,t) for(int i=s;i<=t;++i)
#define per(i,t,s) for(int i=t;i>=s;--i)
using namespace std;
template<typename T>
inline void read(T &x) {
	x=0;int f=1;char c=getchar();
	for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=x*10+c-'0';
	x*=f;
}
const int N=2e5+10,MOD=1e9+7;
int n,a[N],ecnt,head[N],col[N],cnt[N][3],res,siz[N],f[N];
struct E{
	int v,next;
}e[N*2];
void add(int u,int v){
	e[++ecnt]={v,head[u]};
	head[u]=ecnt;
}
void dfs(int u,int fa){
	f[u]=fa;
	col[u]=3-col[fa];
	cnt[u][col[u]]++;
	siz[u]=1;
	for(int i=head[u];i;i=e[i].next){
		if(e[i].v==fa) continue;
		dfs(e[i].v,u);
		cnt[u][1]+=cnt[e[i].v][1];
		cnt[u][2]+=cnt[e[i].v][2];
		siz[u]+=siz[e[i].v];
	}
}
signed main(){
	read(n);
	rep(i,1,n) read(a[i]);
	rep(i,1,n-1){
		int u,v;read(u);read(v);
		add(u,v);add(v,u);
	}
	col[0]=1;
	dfs(1,0);
	rep(u,1,n){
		for(int i=head[u];i;i=e[i].next){
			if(e[i].v==f[u]) continue;
			res=(res+cnt[e[i].v][col[u]]*(n-siz[e[i].v])%MOD*a[u]%MOD);
			int x=cnt[e[i].v][3-col[u]]*(n-siz[e[i].v])%MOD*a[u]%MOD;
			res=(res-x+MOD)%MOD;
		}
		res=(res+(cnt[1][col[u]]-cnt[u][col[u]])*siz[u]%MOD*a[u]%MOD);
		res=(res-(cnt[1][3-col[u]]-cnt[u][3-col[u]])*siz[u]%MOD*a[u]%MOD);
		res=(res+n*a[u])%MOD;
	}
	printf("%lld",(res+MOD)%MOD);
	return 0;
}
```

---

## 作者：1234567890sjx (赞：0)

令 $f_{i,0/1}$ 表示当前是 $i$ 号点，颜色为 $0$ 或 $1$ 时答案是多少，$g_i$ 表示若以 $1$ 为根 $i$ 号节点的深度。

显然有 $f_{i,0}=\sum_{j\in \textrm{G}_i} (f_{j,1}+g_j\times a_i)$，$f_{i,1}=\sum_{j\in \textrm{G}_i}(f_{j,0}-g_j\times a_i)$。

令 $h_{i,0/1}$ 表示当前根节点为 $i$ 点时的答案。比较好做，就是用原答案加上当前点对总的答案产生的贡献，然后再减掉当前点的父亲节点对总的答案产生的贡献即可。

换根一下。时间复杂度 $O(n)$。

---

## 作者：SegTree (赞：0)

考虑对每个结点单算该点权值的贡献。（注意下面都指的是以该点为根时的情况）

+ 该路径的起点来自一颗子树，并且起点的深度和该点奇偶性相同。

+ 该路径的起点来自一颗子树，并且起点的深度和该点奇偶性不同。

+ 该路径的起点是它本身。

第一种和第二种，求出 $cnt1_{u,x}$ 和 $cnt2_{u,x}$ 表示以 $u$ 为根时对于 $x\in son_u$ 求出在 $x$ 子树内深度为偶数的点和深度为奇数的点。则贡献为 $cnt1_x\cdot (n-siz_x)\cdot a_u-cnt2_x\cdot(n-siz_x)\cdot a_u$。处理 $cnt1$ 和 $cnt2$，可以把它搞到 dfn 序上查询区间奇数的个数和偶数的个数，一个前缀和即可。对于不是根的点记得考虑它的外子树。

第三种，终点任意，所以是 $a_un$。

时间复杂度 $\mathcal{O}(n)$。

[代码](https://codeforces.com/contest/960/submission/235718089)。

---

## 作者：TernaryTree (赞：0)

并不难的一道 *$2300$，很容易独立想出来，代码也不难写。

注意到计算的是有向路径的权值和。不妨先考虑偶数个点构成的路径 $u\to v$，显然 $u\to v$ 的权值与 $v\to u$ 的权值相加为 $0$，所以我们不用考虑长度为偶数的路径。

接下来考虑奇数个点组成的路径，此时 $u\to v$ 和 $v\to u$ 的权值相同。看到 $(-1)^i$ 这种交替出现结构很不爽，结合路径长度奇偶性很容易想到黑白染色，相邻的两个结点染不同色，若 $u,v$ 同色则路径上经过奇数个点。同时将染为黑色的结点权值改为其相反数。

问题转换为了，计算两两白点路径点权和与两两黑点路径点权和，两者作差。

路径点权求和问题的经典套路是拆贡献，我们考虑一个点 $u$ 会对答案造成多少贡献，也就是有多少两端结点都是颜色 $c$ 的路径会经过这个点。不妨设当 $u$ 为根的时候，其每个子树内颜色为 $c$ 的结点个数为 $\{s_v\}$。设 $k$ 为 $u$ 的子树个数，则路径数为：

$$
\begin{aligned}
&\sum_{i=1}^{k}\sum_{j=i+1}^k s_is_j\\
=&\dfrac12\left(\sum_{i=1}^{k}\sum_{j=1}^k s_is_j-\sum_{i=1}^k s_i^2\right)\\
=&\dfrac12\left(\left(\sum_{i=1}^{k}s_i\right)^2-\sum_{i=1}^k s_i^2\right)\\
\end{aligned}
$$

这部分可以线性计算。

当然，如果当前结点 $u$ 的颜色与正在计算的端点颜色相同，路径数还要加上所有当前颜色减一，因为这个点也可以作为端点。

核心代码：

```cpp
void calc(int u, int fa, int z) {
    int sum = 0, res = 0;
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v == fa) continue;
        calc(v, u, z);
        sum = (sum + siz[v][z]) % mod;
        res = (res + siz[v][z] * siz[v][z] % mod) % mod;
        // 加上原树上自己子节点的
    }
    sum = (sum + siz[1][z] - siz[u][z]) % mod;
    res = (res + (siz[1][z] - siz[u][z]) * (siz[1][z] - siz[u][z]) % mod) % mod;
    // 当自己成为根，父亲就会成为儿子，所以父亲以上的也要计算。
    res = (sum * sum % mod - res + mod) % mod * inv2 % mod;
    if (c[u] == z) res = (res + siz[1][z] - 1) % mod; // 颜色相同
    tot = (tot + res * a[u] % mod) % mod; // 统计答案
}
```

这样交上去你会获得 WA on #18 的好成绩，为什么呢？

调试发现，当 $n=1$ 时，答案总输出 $0$，这说明长度为 $1$ 的路径没有算入。而长度为 $1$ 的路径不存在方向之分，所以只贡献一次，也就是 $\sum a_i$。

简单改一下，我们就可以愉快地 AC 了。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxn = 1e6 + 10;
const int mod = 1e9 + 7;
const int inv2 = 5e8 + 4;

int n;
int a[maxn];
vector<int> g[maxn];
int c[maxn];
int siz[maxn][2];

void dfs(int u, int fa, bool z) {
    c[u] = z;
    if (z) a[u] = (-a[u] + mod) % mod;
    ++siz[u][z];
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v == fa) continue;
        dfs(v, u, !z);
        siz[u][0] += siz[v][0], siz[u][1] += siz[v][1];
    }
}

int ans, tot, tmp;

void calc(int u, int fa, int z) {
    int sum = 0, res = 0;
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v == fa) continue;
        calc(v, u, z);
        sum = (sum + siz[v][z]) % mod;
        res = (res + siz[v][z] * siz[v][z] % mod) % mod;
    }
    sum = (sum + siz[1][z] - siz[u][z]) % mod;
    res = (res + (siz[1][z] - siz[u][z]) * (siz[1][z] - siz[u][z]) % mod) % mod;
    res = (sum * sum % mod - res + mod) % mod * inv2 % mod;
    if (c[u] == z) res = (res + siz[1][z] - 1) % mod;
    tot = (tot + res * a[u] % mod) % mod;
}

signed main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], tmp = (tmp + a[i] + mod) % mod;
    for (int i = 1, u, v; i < n; i++) cin >> u >> v, g[u].push_back(v), g[v].push_back(u);
    dfs(1, 0, 0);
    tot = 0, calc(1, 0, 0), ans = (ans + tot + mod) % mod;
    tot = 0, calc(1, 0, 1), ans = (ans - tot + mod) % mod;
    cout << (ans * 2 % mod + tmp) % mod << endl;
    return 0;
}
```

---

## 作者：cmll02 (赞：0)

这个东西一看就和奇偶性有关，先对整个树黑白染色一下。

对于一条路径，上面的一个点如果和起点同色就是正贡献，否则就是负贡献。

这样容易发现，经过点数为偶数的路径其实是假的，不会产生任何贡献（交换起点和终点后贡献变成了原来的相反数）。

所以我们只要统计经过点数量为奇数的路径。

我们拆分一个点的贡献，以一个黑点为例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/77i5t5by.png)

维护一下子树内黑白点个数即可对每个点分别算贡献。

[Code link](https://codeforces.com/contest/960/submission/130799037)

---

## 作者：弦巻こころ (赞：0)

~~由于kid被发配边疆(指坐在老师面前),于是就只能写题解混时间力~~

思路与代码难度都很简单(确信

我们考虑计算每个点的贡献.

我们记$f[x][0/1]$为当以1为根时这个点子树距离其为 偶数 / 奇数 的数量(包括自己)

$g[0/1]$为深度为偶数和奇数点的个数  (这里用不上换根,因为只需要储存2个值就能知道以当前点为根事距离其为奇偶的点的个数)

考虑如何计算贡献,我们发现对于长度为奇数的路径,它是没有贡献的(来回正好抵消),对于长度为偶数的点,分为正贡献和负贡献.

当一条路径对当前点有正贡献时,路径的起点与终点需距离当前点为偶数,我们发现只要起点和终点的路径经过当前点就会产生贡献.


1.子树内选一个点再在子树外选一个点

贡献为 ($d$为当前深度&$1$,乘2是因为有向路径要算两遍贡献)
$$a[x]* (g[d]-f[x][0]) * f[x][0]* 2 $$


2.子树内选两个点

如何求这种情况路径个数呢,思路很简单,我们用所有路径的减去不合法路径就行了.

贡献为
$$a[x] *f[x][0]*f[x][0] -\sum _{to \in s[x] }f[to][1]*f[to][1] $$

合并一下贡献为
$$a[x]* (g[d]* 2-f[x][0]) * f[x][0] -\sum _{to \in s[x] }f[to][1]*f[to][1] $$

负贡献与正贡献同理.
贡献为(此时$d$为$d$^$1$,打不出来异或符号,悲)
$$-a[x] * (g[d]* 2-f[x][1]) * f[x][1] +\sum _{to \in s[x] }f[to][0] * f[to][0] $$

将正负贡献加起来即可

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=514514;
const int mod=1e9+7;
#define ll long long
struct edge{int v,nt;}e[N];
ll kkr,f[N][2],g[2],a[N],cnt;
int n,tot,hd[N];
void add(int x,int y) {e[++tot].v=y;e[tot].nt=hd[x];hd[x]=tot;}
void dfs(int x,int fa){f[x][0]=1;
	for(int i=hd[x],to;i;i=e[i].nt){to=e[i].v;
		if(fa==to)continue;dfs(to,x);
		f[x][0]+=f[to][1];f[x][1]+=f[to][0];
	}
}
void solve(int x,int fa,int d){//我在下面提前把g乘了2所以这里没有乘
	cnt=((g[d]-f[x][0])*f[x][0]-(g[d^1]-f[x][1])*f[x][1])%mod; 
	kkr=(kkr+cnt*a[x])%mod;	
	for(int i=hd[x],to;i;i=e[i].nt){to=e[i].v;
		if(fa==to)continue;solve(to,x,d^1);
		kkr=(kkr+f[to][0]*f[to][0]%mod*a[x]%mod+mod)%mod;
		kkr=(kkr-f[to][1]*f[to][1]%mod*a[x]%mod)%mod;
       //减去不合法方案
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(int i=1,x,y;i<n;i++)scanf("%d%d",&x,&y),add(x,y),add(y,x);
	dfs(1,0);g[0]=f[1][0]<<1,g[1]=f[1][1]<<1;solve(1,0,0);
	printf("%lld",(kkr%mod+mod)%mod);
}
```




---

## 作者：ifffer_2137 (赞：0)

### 题意
给定一棵带点权的树，求所有有向路径的权值和。

一条有向路径的权值如下定义：

设这条路径依次经过的点的权值分别为 $a_1,a_2\ldots a_k$。

则路径的权值为 $a_1\times (-1)^2+a_2\times (-1)^3+\ldots+a_k\times (-1)^{(k+1)}$。

答案对 $10^9+7$ 取模。
### 分析
考虑每个点的贡献，以它为起点的总贡献是 $a_u\times n$。然后以它为根，当选定一棵子树内的某个点为起点时，可以发现根据它和 $u$ 的路径长度奇偶性已经确定了 $a_u$ 的系数，终点可以在其它子树里任意，所以我们令 $dp_u$ 表示 $u$ 子树内到 $u$ 距离为奇数的点数量和到 $u$ 距离为偶数的点数量之差，这时只需要求出以每个点为根时的各子树 $dp$ 值和 $siz$ 即可简单统计答案。

看到这个数据范围，可以考虑换根了，在第二次遍历的时候维护一个 $k_u$ 表示 $u$ 子树外的答案，往下递归时，$k_{fa}$ 累加上 $u$ 的各兄弟 $dp$ 值即可。

具体柿子建议阅读代码。
### 代码
RMJ 炸了所以只在 CF 上[过了](https://codeforces.com/problemset/submission/960/265496975)……
```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
    char ch=getchar();int x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=2e5+5;
const int mod=1e9+7;
int n,ans;
int a[maxn];
vector<int> tr[maxn];
int dp[maxn],siz[maxn];
void dfs1(int u,int f){
	dp[u]=-1;
	siz[u]=1;
	for(int v:tr[u]){
		if(v==f) continue;
		dfs1(v,u);
		siz[u]+=siz[v];
		dp[u]-=dp[v];
	}
}
void dfs2(int u,int f,int k){
	for(int v:tr[u]){
		if(v==f) continue;
		ans=(ans+(a[u]+mod)%mod*((dp[v]+mod)%mod)%mod*(n-siz[v])%mod+mod)%mod;
	}
	ans=(ans+(a[u]+mod)%mod*((k+mod)%mod)%mod*siz[u]%mod+mod)%mod;
	int s=-k-1;
	for(int v:tr[u]){
		if(v==f) continue;
		s-=dp[v];
	}
	for(int v:tr[u]){
		if(v==f) continue;
		dfs2(v,u,s+dp[v]);
	}
}
signed main(){
	cin.tie(0),cout.tie(0);
	n=read();
	for(int i=1;i<=n;i++) a[i]=read(),ans=(ans+(a[i]+mod)%mod*n%mod+mod)%mod;
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		tr[u].eb(v),tr[v].eb(u);
	}
	dfs1(1,0);
	dfs2(1,0,0);
	cout<<ans<<endl;
	return 0;
}
```

---

