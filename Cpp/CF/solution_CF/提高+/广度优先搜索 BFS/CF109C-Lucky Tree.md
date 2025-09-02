# Lucky Tree

## 题目描述

彼得喜欢幸运数字。这里所说的幸运数字是由 $4$ 和 $7$ 组成的正整数。比如，数字 $47$，$744$，$4$ 是幸运数字，而 $5$，$17$，$467$ 就不是。

一天，彼得遇到一棵由 $n$ 个点组成的树。另外，这棵树是带权的，即每条边有一个权值（由一个正整数表示）。如果一条边的权值是一个幸运数字，那么我们就说这条边是一条幸运边。说明一下，一棵 $n$ 个结点的树是由 $n$ 个结点和 $(n-1)$ 条边组的无环的无向图。

彼得好奇，在树中有多少个满足以下条件的三元组 $(i,j,k)$（$i,j,k$是三个不同的点）。  
1. $i$ 到 $j$ 有路径，$i$ 到 $k$ 也有路径；  
2. 每条路径中至少有一条幸运边。

数字的顺序是有意义的，举例说明，三元组 $(1,2,3)$，$(2,1,3)$ 和 $(1,3,2)$ 是三个不同的序列。

现在要求计算在树中存在多少个这样的三元组关系。

样例解释： 样例一中的 $16$ 种情况分别为：$(1,2,4)$，$(1,4,2)$，$(2,1,3)$，$(2,1,4)$，$(2,3,1)$，$(2,3,4)$，$(2,4,1)$，$(2,4,3)$，$(3,2,4)$，$(3,4,2)$，$(4,1,2)$，$(4,1,3)$，$(4,2,1)$，$(4,2,3)$，$(4,3,1)$ 和 $(4,3,2)$。

## 样例 #1

### 输入

```
4
1 2 4
3 1 2
1 4 7
```

### 输出

```
16
```

## 样例 #2

### 输入

```
4
1 2 4
1 3 47
1 4 7447
```

### 输出

```
24
```

# 题解

## 作者：BlankAo (赞：11)

断开所有幸运边，形成很多连通块。则在一个联通块中选出点 $i$，在其它点中任意选两个点 $j,k$，则 $(i,j,k)$ 一定是合法的。

所以枚举每个连通块 $T$，设其大小为 $|T|$，则答案为 $\sum\limits_{T}2\binom{n-|T|}{2}\times |T|$。  

由于题解未通过，理由是说明过少，加入算式解释：

$\binom{n-|T|}{2}$ 意思是在其它点中选两个，乘 $2$ 是因为它们是有序的，乘 $|T|$ 是因为此连通块的每个点都会产生如此贡献。

```c++
#include<bits/stdc++.h>
#define rep(i,x,y) for(int i=x;i<=y;++i)
#define mar(o) for(int E=fst[o];E;E=e[E].nxt)
#define v e[E].to
#define lon long long
using namespace std;
const int n7=101234;
struct dino{int to,nxt;}e[n7*2];
int n,fst[n7],ecnt,siz[n7],cnt;lon ans;
bool vis[n7];

int rd(){
	int shu=0;bool fu=0;char ch=getchar();
	while( !isdigit(ch) ){if(ch=='-')fu=1;ch=getchar();}
	while( isdigit(ch) )shu=(shu<<1)+(shu<<3)+ch-'0',ch=getchar();
	return fu?-shu:shu;
}

void edge(int sta,int edn){
	ecnt++;
	e[ecnt]=(dino){edn,fst[sta]};
	fst[sta]=ecnt;
}

void dfs(int o,int fa){
	siz[cnt]++,vis[o]=1;
	mar(o){
		if(v==fa)continue;
		dfs(v,o);
	}
}

int main(){
	n=rd();
	rep(i,1,n-1){
		int sta=rd(),edn=rd(),w=rd();
		while(w){
			if( (w%10)^4&&(w%10)^7 ){w=1;break;}
			else w=w/10;
		}
		if(w)edge(sta,edn),edge(edn,sta);
	}
	rep(i,1,n){
		if(vis[i])continue;
		cnt++,dfs(i,0);
	}
	rep(i,1,cnt)ans=ans+1ll*(n-siz[i])*(n-siz[i]-1)*siz[i];
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：xxboyxx (赞：9)

## 思路

可以发现这个边权的大小与答案没有关系，我们只需要处理这条边是否是幸运边即可，那么如果这条边是幸运边，那么就设这条边为 $1$，否则为 $0$。

对于每一个三元组其实可以只枚举其中的 $i$，而剩下的两个则可以使用树形动态规划求出。

### 状态设计

设 $s_x$ 表示以这个点为根的子树的节点个数（包括节点 $x$）。

设 $f_x$ 表示这个点到以这个点为根的子树的点的路径中有幸运边的节点个数。

设 $g_x$ 表示这个点到非以这个点为根的子树的点的路径中有幸运边的节点个数。

### 状态转移

假设我们有如下一棵树，以 $5$ 号节点为三元组的第一个。

![](https://cdn.luogu.com.cn/upload/image_hosting/vyb39aud.png)

#### 求点到子树的点中有幸运边的节点个数

$5$ 号节点到 $6$ 号节点是一条幸运边，那么 $5$ 号到 $6$ 号和 $10$ 号都有幸运边。所以当 $x$ 与其子节点有幸运边时 $f_x$ 加上 $s_y$。（$x$ 为父亲，$y$ 为儿子）

$5$ 号节点到 $7$ 号节点没有幸运边，那么 $5$ 号就只能到 $9$ 号，也就是只能到 $7$ 号到过的节点。所以当 $x$ 与其子节点没有幸运边时 $f_x$ 加上 $f_y$。

#### 求点到非子树的点中有幸运边的节点个数

$5$ 号节点到 $2$ 号节点有幸运边，那么 $5$ 号到 $1$ 号、$2$ 号、$3$ 号和 $4$ 号都有幸运边。也就是说除了它的子树其他都可以到达。所以当 $y$ 与其父节点有幸运边时 $g_y=s_1-s_y$。

现在又以 $7$ 号节点为三元组的第一个。

![](https://cdn.luogu.com.cn/upload/image_hosting/0nhl2a3q.png)

$7$ 号节点到 $5$ 号节点没有幸运边，那么 $7$ 号到 $6$ 号、$10$ 号、$2$ 号、$4$ 号、$1$ 号、$3$ 号和 $8$ 号都有幸运边。也就是父亲向上可以到达的和向下可以到达的的和减去它自己的子树。所以当 $y$ 与其父节点没有幸运边时 $g_y=g_x+f_x-f_y$。

### 答案

已经求出来每个点向上和向下的个数了，由于 $i$ 已经被固定，应该求 $j$ 和 $k$，的位置种数。其实就是一个排列，分三种情况。

#### 一、两个都在下

$f_x \times (f_x-1)$

#### 二、两个都在下

$f_y \times (f_y-1)$

#### 三、一个在上一个在下

$2 f_x \times f_y$

可以交换位置所以要乘二。

最后枚举 $i$ 加和即可。

## 注意

由于求 $g$ 时需要用到 $f$，所以应该先求 $f$ 后求 $y$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,maxx=-1e18,ans;
int f[1000005];
int s[1000005];
int dp1[1000005];
int dp2[1000005];
vector<int> g[1000005];
vector<int> v[1000005];
int luck(int x)//判断幸运数 
{
	while (x)
	{
		if (x%10!=4 && x%10!=7)
			return 0;
		x/=10;
	}
	return 1;
}
void dfs(int x)//求s_x 
{
	s[x]=1;
	f[x]=1;
	int l=g[x].size();
	for (int i=0;i<l;i++)
	{
		int y=g[x][i];
		if (f[y]==0)
		{
			dfs(y);
			s[x]+=s[y];
		}
	}
}
void dfs1(int x)//求f_x 
{
	f[x]=1;
	int l=g[x].size();
	for (int i=0;i<l;i++)
	{
		int y=g[x][i];
		if (f[y]==0)
		{
			dfs1(y);
			if (v[x][i]==1)
				dp1[x]+=s[y];
			else
				dp1[x]+=dp1[y];
		}
	}
}
void dfs2(int x)//求g_x 
{
	f[x]=1;
	int l=g[x].size();
	for (int i=0;i<l;i++)
	{
		int y=g[x][i];
		if (f[y]==0)
		{
			if (v[x][i]==1)
				dp2[y]=s[1]-s[y];
			else
				dp2[y]=dp2[x]+dp1[x]-dp1[y];
			dfs2(y);
		}
	}
}
signed main()
{
	cin>>n;
	for (int i=1;i<n;i++)
	{
		int x,y,z;
		cin>>x>>y>>z;
		int k=luck(z);
		g[x].push_back(y);
		g[y].push_back(x);
		v[x].push_back(k);
		v[y].push_back(k);
	}
	dfs(1);
	memset(f,0,sizeof(f));
	dfs1(1);
	memset(f,0,sizeof(f));
	dfs2(1);
	for (int i=1;i<=n;i++)//计算答案 
		ans+=dp1[i]*(dp1[i]-1)+dp2[i]*(dp2[i]-1)+dp1[i]*dp2[i]*2;
	cout<<ans;
	return 0;
}
```

---

## 作者：苹果蓝17 (赞：9)

[题目传送门](https://www.luogu.com.cn/problem/CF109C)

[更好的阅读体验](https://www.cnblogs.com/Appleblue17/p/14800397.html)

#### 题意简述

一棵树，其中有若干条关键边，求有多少点三元组 $(i,j,k)$ 满足 $i$ 与 $j$ 间有关键边且 $i$ 与 $k$ 间有关键边。

$n \leq 10^5$。

#### 题目分析

~~同学说这题很有迷惑性。~~

考虑转化 $i$ 与 $j$ 间有关键边的条件，很容易想到将所有关键边断开后会形成若干联通块 $t_1,t_2,\cdots,t_k$。

设点 $u$ 所属的联通块为 $s_u$，即 $u \in s_u$。

显然 $u$ 和 $v$ 间有关键边当且仅当 $s_u \neq s_v$。
$$
\begin{aligned}  ans  & =\sum_{i \neq j \neq k} [s_i \neq s_j][s_i \neq s_k]\\  & =\sum_{i} \sum_{j \neq k}[s_i \neq s_j][s_i \neq s_k]\\  & =\sum_{i} 2\dbinom{n-|s_i|}{2}\\  & =2\sum_{i_1}^n \dbinom{n-|s_i|}{2}\\  & =2\sum_{i_1}^k |t_i| \dbinom{n-|t_i|}{2}\\  \end{aligned}
$$
`dfs` 计算联通块大小，组合数直接计算即可。

时间复杂度 $O(n)$。

拓展 1：点带权。

记 $W=\sum\limits_{i=1}^n w_i$，$W_k=\sum\limits_{i \in s_k}^n w_i$（即该点所在联通块的点权和），$W_k=\sum\limits_{i \in s_k}^n w_i^2$。

$$
\begin{aligned}  ans  & =\sum\limits_{i}w_i(\sum\limits_{j,k}[s_i \neq s_j][s_i \neq s_k]w_jw_k-\sum\limits_{j} [s_i \neq s_j]w_j^2)\\  & =\sum\limits_i w_i[(W-W_i)^2-W_i']\\  \end{aligned}
$$
拓展 2：多元组。

若将条件改为 $p$ 元组，且任意两点间有关键边，即为任意两点不同属一个联通块。

即从 $k$ 个数里任意选出 $p$ 个数的积之和。

这是一个经典问题，即 $[x^p]\prod_{i=1}^k (1+t_ix)$，分治+FFT 即可在 $O(k\log^2 k)$ 的时间复杂度内解决。

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long N=1e5+5;
struct nod{
	long long to,nxt,w;
}e[N*2];
long long head[N],cnt;
void add(long long u,long long v,long long w){
	e[++cnt].to=v;
	e[cnt].w=w;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
long long check(long long x){
	while(x){
		if(x%10!=4 && x%10!=7) return 0;
		x/=10;
	}
	return 1;
}
long long n,id,ans;
bool vis[N];
void dfs(long long u){
	vis[u]=1;
	id++;
	for(long long i=head[u];i;i=e[i].nxt){
		long long v=e[i].to;
		if(vis[v] || e[i].w) continue;
		dfs(v);
	}
}

int main(){
	cin>>n;
	for(long long i=1;i<n;i++){
		long long u,v,w;
		scanf("%lld%lld%lld",&u,&v,&w);
		long long t=check(w);
		add(u,v,t);
		add(v,u,t);
	}
	for(long long i=1;i<=n;i++){
		if(!vis[i]){
			id=0;
			dfs(i);
			ans+=id*(n-id)*(n-id-1);
		}
	}
	printf("%lld",ans);
}
```

---

## 作者：Ginger_he (赞：3)

首先按照幸运边把这棵树断开，我们只需要知道每个连通块内的点的个数，假设有 $m$ 个连通块。接下来分成两种情况讨论，三个点在不同的连通块中，以及有两个点在同一个连通块中。

对于第一种情况，我们可以随意选且随意排序，所以答案为

$$6\times\sum_{i=1}^m\sum_{j=i+1}^m\sum_{k=j+1}^ma_ia_ja_k$$

对于上面这个式子，我们可以先求出 $a_i$ 的后缀和 $f_i$，再求出 $a_if_{i+1}$ 的后缀和 $g_i$，那么答案就可以转化为

$$6\times\sum_{i=1}^m a_ig_{i+1}$$

对于第二种情况，只能是另一个点与处在同一个连通块的这两个点连边，我们枚举相同的这两个点的连通块，令 $s=\sum\limits_{i=1}^ma_i$，那么答案就是

$$\sum_{i=1}^m(s-a_i)a_i(a_i-1)$$

总方案数把两部分的答案加起来即可，时间复杂度 $\Theta(n)$

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 100005
struct node
{
	int v,w;
};
int n,m,cnt,u,v,w,p;
ll s,res1,res2,a[N],f[N],g[N],h[N];
bool vis[N];
vector<node> e[N];
void dfs(int x)
{
	vis[x]=1,cnt++;
	for(auto i:e[x])
	{
		int v=i.v,w=i.w;
		if(vis[v]||w)
			continue;
		dfs(v);
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		p=1;
		while(w)
		{
			p&=(w%10==4||w%10==7);
			w/=10;
		}
		e[u].push_back(node{v,p});
		e[v].push_back(node{u,p});
	}
	for(int i=1;i<=n;i++)
	{
		if(!vis[i])
		{
			cnt=0;
			dfs(i);
			a[++m]=cnt,s+=cnt;
		}
	}
	for(int i=m;i>=1;i--)
	{
		f[i]=f[i+1]+a[i];
		g[i]=g[i+1]+a[i]*f[i+1];
		res1+=a[i]*g[i+1];
		res2+=(s-a[i])*a[i]*(a[i]-1);
	}
	printf("%lld\n",6*res1+res2);
	return 0;
}
```

---

## 作者：I_am_Accepted (赞：2)

### Preface

（一开始）哇，树形 DP 解决。

（看难度）哇！好水的紫题。

（写完看题解）哇！我是↑↓。

### Analysis

其实这道题可以用连通块解决，但是树形 DP 更有扩展意义。

设「幸运边」的边权为 $1$，否则为 $0$。

先将树定根，不妨 $\text{root}\!=\!1$。

对于固定的节点 $x$，与她之间路径有「幸运边」的点分成两类：在 $x$ 子树中的和不在的。

子树中的可以用简单的 DP 解决，设个数为 $a_i$。

再来第二遍 DFS，这时将每个节点的「不在这个节点子树内的与她之间有幸运边的点的个数」下传到儿子们，设为 $b_i$。

这样两遍 DFS $O(n)$ 解决问题。

最后答案为

$$\sum\limits_{i=1}^n(a_i+b_i)(a_i+b_i-1)$$

### Code

[Link](https://codeforces.com/contest/109/submission/151200906)

---

## 作者：王熙文 (赞：2)

## 思路

考虑换根树形 dp。

设 $dp_i$ 表示从 $i$ 能到多少个 $j$，它们之间的路径有 lucky 边。

### 第一次 dfs

从下往上。

先处理每个节点（设其为 $u$）子树内有多少个 $j$。

首先，对于叶节点，肯定一个都没有。

对于其他节点，遍历其所有子节点（对于其中一个子节点设其为 $v$），分类讨论：

* 如果 $u,v$ 之间的边是 lucky 边：$u$ 一定能到 $v$ 子树下所有的点，那么 $dp_u$ 加上 $siz_v$。（$siz_v$ 表示 $v$ 的子树大小，在第一次 dfs 中处理）
* 如果 $u,v$ 之间的边不是 lucky 边：$u$ 只能到 $v$ 的子树中 $dp_v$ 个点，即 $v$ 能到的点 $u$ 也能到。 

### 第二次 dfs

从上往下。

处理的是最终的 $dp$ 数组。

对于一个节点（设其为 $v$）与其父节点（设其为 $u$），分类讨论：

* 如果 $v,u$ 之间的边是 lucky 边：除了 $v$ 这个子树里的点不确定，其他的点都一定能走到，所以 $dp_v$ 加上 $siz_1-siz_v$。
* 如果 $v,u$ 之间的边不是 lucky 边：从上文可以发现，$dp_u$ 中一定有 $dp_v$ 这些点，所以 $dp_v$ 变成 $dp_u$。

### 统计答案：

一个点可以到的点有 $dp_i$ 个，选择一个点（题目中所说的 $j$）的方案数有 $dp_i$，选择另一个点（题目中所说的 $k$）的方案数有 $dp_i-1$ 个，所以遍历所有的点，每次答案加上 $dp_i \times (dp_i-1)$。

## 参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int tot=0,var[200010],len[200010],nxt[200010],head[100010];

bool xy(int x) // 是否为幸运边
{
	bool flag=1;
	while(x)
	{
		if(x%10!=4 && x%10!=7)
		{
			flag=0;
			break;
		}
		x/=10;
	}
	return flag;
}

void add(int u,int v,int w)
{
	int l=xy(w);
	var[++tot]=v;
	len[tot]=l;
	nxt[tot]=head[u];
	head[u]=tot;
	var[++tot]=u;
	len[tot]=l;
	nxt[tot]=head[v];
	head[v]=tot;
}

int siz[100010];

long long dp[100010];

void dfs(int u,int fa) // 第一次 dfs
{
	siz[u]=1;
	for(int i=head[u]; i; i=nxt[i])
	{
		int v=var[i];
		if(v==fa) continue;
		dfs(v,u);
		if(len[i]) dp[u]+=siz[v];
		else dp[u]+=dp[v];
		siz[u]+=siz[v];
	}
}

void dfs2(int u,int fa) // 第二次 dfs
{
	for(int i=head[u]; i; i=nxt[i])
	{
		int v=var[i];
		if(v==fa) continue;
		if(len[i]) dp[v]+=siz[1]-siz[v];
		else dp[v]=dp[u];
		dfs2(v,u);
	}
}

int main()
{
	int n,u,v,w;
	scanf("%d",&n);
	for(int i=1; i<=n-1; ++i)
	{
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
	}
	dfs(1,0);
	dfs2(1,0);
	long long ans=0;
	for(int i=1; i<=n; ++i) // 统计答案
	{
		ans+=dp[i]*(dp[i]-1);
	}
	printf("%lld",ans);
	return 0;
}
```

~~祭作者第一次不看题解 AC 换根 dp~~

---

## 作者：Farkas_W (赞：2)

### 思路：

$\quad$树形$DP +$ 容斥 ， $f[x]$ 表示以 $x$ 为根的子树中有几个点到 $x$ 的路径包含幸运边， $g[x]$ 表示除了 $x$ 的子树外有几个点到 $x$ 的路径包含幸运边，最后统计答案就是 $ans=\sum_{i=1}^n$ $(f[i]\times (f[i]-1)+g[i]\times (g[i]-1)+2\times f[i]\times g[i])$，数组 $f$ 和 $g$ 的转移也很简单，当 $y$ 是 $x$的儿子时，若 $x$ 和 $y$ 的连边为幸运边，那么 $f[x]+=size[y]$ ， $y$ 的子树(包括 $y$)到 $x$ 的路径都包含幸运边，否则 $f[x]+=f[y]$ ， $g$ 的转移也类似，如果x和y的连边是幸运边，那么 $g[y]=(n-size[y])$ ，否则 $g[y]=g[x]+f[x]-f[y]$ ，两遍 $dfs$ 即可完成的操作，一遍自下而上，一遍自上而下，时间复杂度为 $O(3n)$ 。

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<algorithm>
#include<cstring>
using namespace std;
#define re register int
#define int long long
#define LL long long
#define il inline
#define next nee
#define inf 1e18
il int read()
{
  int x=0,f=1;char ch=getchar();
  while(!isdigit(ch)&&ch!='-')ch=getchar();
  if(ch=='-')f=-1,ch=getchar();
  while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
  return x*f;
}
il void print(int x)
{
  if(x<0)putchar('-'),x=-x;
  if(x/10)print(x/10);
  putchar(x%10+'0');
}
const int N=1e5+5;
int n,m,next[N<<1],go[N<<1],head[N],tot,father[N],size[N],f[N],g[N],ans;
bool s[N<<1];
il bool check(int x)//判断是否是幸运数字
{
  while(x)
    {
      if(x%10!=7&&x%10!=4)return 0;
      x/=10;
    }
  return 1;
}
il void Add(int x,int y,bool z)
{next[++tot]=head[x];head[x]=tot;go[tot]=y;s[tot]=z;}
il void dfs1(int x,int fa,bool z)//第一遍dfs，处理f数组
{
  father[x]=fa;size[x]=1;
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {
      if(y==fa)continue;
      dfs1(y,x,s[i]);
      size[x]+=size[y];
      if(s[i])f[x]+=size[y];
      else f[x]+=f[y];
    }
}
il void dfs2(int x)//第二遍dfs，处理g数组
{
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {
      if(y==father[x])continue;
      if(s[i])g[y]=n-size[y];
      else g[y]=g[x]+f[x]-f[y];
      dfs2(y);
    }
}
signed main()
{
  n=read();
  for(re i=1;i<n;i++)
    {re x=read(),y=read(),z=check(read());Add(x,y,z);Add(y,x,z);}
  dfs1(1,0,0);dfs2(1);
  for(re i=1;i<=n;i++)
    ans+=f[i]*(f[i]-1)+g[i]*(g[i]-1)+f[i]*g[i]*2;//简单的组合数学计算方案
  print(ans);
  return 0;
}
```

---

## 作者：Starlight_Glimmer (赞：2)

首先，可以轻而易举地判断出哪些边是幸运边 哪些边是非幸运边
为方便描述，定义从一个点出发经过至少一条幸运边到达的点为这个点的幸运点

考虑每一个点 如果知道了它的幸运点的个数为N
那么该点对答案的贡献就是N*(N-1)
最暴力的方法挨个求显然会超时 下面考虑优化

法1.考虑换根
设当前点为u 将根换到点v
若边(u,v)是幸运边 则转为v为根的树后，u的所有子树上的点都是v的幸运点
若边(u,v)不是幸运边 则没有影响 v的幸运点就是u的幸运点

法2.正难则反 考虑非幸运点的个数 再用总数-非幸运点的个数-1(自身)得运点个数
 砍掉所有的幸运边 和当前点联通的点都是它的非幸运点
 想到同一个联通块里的点的非幸运点的个数是一样的
 我们需要求出联通块的个数和大小 可以用并查集维护 
 
 还可以直接用总方案数减去不满足条件的方案数 
 (注意 不符合情况的有两种 一种是i到j和i到k 都不包含幸运边 还有一种是其中一个包含幸运边
  
  
  下面给出最后一种方法的代码：
  
  
  ```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
#define MAXN 100005
#define LL long long
int f[MAXN],n;
LL siz[MAXN];
void Init()
{
	for(int i=1;i<=n;i++)
		f[i]=i,siz[i]=1;
	return ;
}
int Find(int x)
{
	if(f[x]==x)
		return x;
	int p=Find(f[x]);
	siz[p]+=siz[x];
	siz[x]=0;
	return f[x]=p;
}
void Union(int x,int y)
{
	int u=Find(f[x]),v=Find(f[y]);
	if(u<v)
	{
		f[v]=u;
		siz[u]+=siz[v];
		siz[v]=0;
	}
	if(u>v)
	{
		f[u]=v;
		siz[v]+=siz[u];
		siz[u]=0;
	}
	return ;
}
bool check(int x)
{
	while(x)
	{
		int tmp=x%10;
		if(tmp!=4&&tmp!=7)
			return 0;
		x/=10;
	}
	return 1;
}
int main()
{
	scanf("%d",&n);
	if(n<3)
	{
		printf("0\n");
		return 0;
	}
	Init();
	for(int i=1;i<=n-1;i++)
	{
		int u,v,w;
		scanf("%d %d %d",&u,&v,&w);
		if(!check(w))
			Union(u,v);
	}
	LL ans=0;
	for(int i=1;i<=n;i++)
		if(Find(f[i])==i)
		{
			if(siz[i]>2)
				ans+=siz[i]*(siz[i]-1)*(siz[i]-2);
			ans+=siz[i]*(siz[i]-1)*(n-siz[i])*2;
		}
	ans=(LL)n*(n-1)*(n-2)-ans;
	printf("%lld\n",ans);
	return 0;
} 

```
倒数第二种方法的代码 比之上一种 改了一点点
```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
#define MAXN 100005
#define LL long long
int f[MAXN],n;
LL siz[MAXN];
void Init()
{
	for(int i=1;i<=n;i++)
		f[i]=i,siz[i]=1;
	return ;
}
int Find(int x)
{
	if(f[x]==x)
		return x;
	int p=Find(f[x]);
	siz[p]+=siz[x];
	siz[x]=0;
	return f[x]=p;
}
void Union(int x,int y)
{
	int u=Find(f[x]),v=Find(f[y]);
	if(u<v)
	{
		f[v]=u;
		siz[u]+=siz[v];
		siz[v]=0;
	}
	if(u>v)
	{
		f[u]=v;
		siz[v]+=siz[u];
		siz[u]=0;
	}
	return ;
}
bool check(int x)
{
	while(x)
	{
		int tmp=x%10;
		if(tmp!=4&&tmp!=7)
			return 0;
		x/=10;
	}
	return 1;
}
int main()
{
	scanf("%d",&n);
	if(n<3)
	{
		printf("0\n");
		return 0;
	}
	Init();
	for(int i=1;i<=n-1;i++)
	{
		int u,v,w;
		scanf("%d %d %d",&u,&v,&w);
		if(!check(w))
			Union(u,v);
	}
	LL ans=0;
	for(int i=1;i<=n;i++)
		if(Find(f[i])==i)
		{
			int num=n-siz[i];
			ans+=(LL)num*(num-1)*siz[i];
		}
	printf("%lld\n",ans);
	return 0;
} 

```

  

---

## 作者：Unnamed114514 (赞：1)

首先，对于每条边，若边权为幸运数字，则记作 $1$，否则记作 $0$。

考虑到这里针对的是 $i\rightarrow j,i\rightarrow k$ 的两条路径，于是考虑求出每个 $i$ 的贡献。

- $\operatorname{LCA}(j,k)=i$（双下）

在这种情况下，$i\rightarrow j,i\rightarrow k$ 都是向下的路径，于是可以考虑求出向下的包含 $1$ 的路径总数，记作 $dp_i$。

假设当前边为 $(u,v,w)$，那么有：

- 若 $w=0$，那么此时只有先到 $v$ 才可能到达包含 $1$ 的边：$dp_u\gets dp_u+dp_v$。

- 若 $w=1$，那么此时 $v$ 这棵子树上任意节点都满足，记 $siz_v$ 为点 $v$ 的子树的大小，有：$dp_u\gets dp_u+siz_v$。

那么我们现在求出来了 $dp_i$，其中 $dp_i$ 中任意两个边均可匹配，由于不考虑顺序，那么此时的贡献就是 $dp_i(dp_i-1)$。

- $\operatorname{LCA}(i,j)=i,\operatorname{LCA}(i,k)=k$（一上一下）

向下很好求，就是 $dp_i$，那么我们此时记向上的答案是 $f_i$，此时显然应该从上往下转移。

假设当前边为 $(u,v,w)$，有：

- $w=0$，那么此时只有到 $u$ 有 $1$ 的边的节点可以造成贡献，但是，值得注意的是，$u$ 的其它子树都是有贡献的，即：$f_v\gets f_u+dp_u-dp_v$。

- $w=1$，显然其它所有节点都能造成贡献，答案就是 $n-siz_v$。

乘法原理，但是，先上后下和先下后上是两种不同的情况。因此，$i$ 的贡献是 $2dp_if_i$。

- $\operatorname{LCA}(i,j)=j,\operatorname{LCA}(i,k)=k$（双上）

同第一种情况，答案应该是 $f_i(f_i-1)$。

时间复杂度 $O(n)$。

---

## 作者：Zhao_daodao (赞：1)

# [Lucky Tree 题目传送门](https://www.luogu.com.cn/problem/CF109C)

### 说在前面
本题我看已经有许多题解用了 `dp` 做，本蒟蒻就提供一种新颖的做法：并查集。

## 输入和输出
输入一个整数 $n$，接下来输入 $(n-1)$ 行，第 $i$ 行有三个整数 $u_{i}$，$v_{i}$，$w_{i}$，分别表示有边相连的两个点和这条边的权值。

输出一行，表示题目中所要计算的三元组个数。

# 题目分析
每一条边带有一个 $bool$ 变量，代表这条边是否是“幸运边”。
定义函数 $check(x,y,z)$，其中 $(x,y,z)$ 满足以下所有条件时 $check(x,y,z)$ 是 $true$。
+ $i$ 到 $j$ 有路径，$i$ 到 $k$ 也有路径；
+ $i$ 到 $k$ 和 $i$ 到 $j$ 的路径中都要至少有一条幸运边。

$ans=\sum\limits_{i,j,k}^{i,j,k\in U}[i\ne j][j\ne k][k\ne i]check(i,j,k)$

# 题目做法
按照幸运边把这棵树断开，我们只需要知道每个连通块内的点的个数，假设一共有 $T$ 个连通块。对于每一个节点 $i$，假设 $i$ 在并查集 $T_{k}$ 中。则：$ans_{i}=\sum\limits_{j}^{j\notin T_{k}}\sum\limits_{k}^{k\notin T_{k}}[j\ne k]$

$ans=\sum\limits_{i=1}^{n}ans_{i}$

通过并查集可以快速求出答案，复杂度 $O(n)$。

# 参考代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e5+5;
int n,m,ans;
int siz[MAXN],fa[MAXN];
int find(int x){
    if(x==fa[x])return fa[x];
    return fa[x]=find(fa[x]);
}
bool check(int x){
    while(x){
        if(x%10!=4&&x%10!=7)
            return false;
        x/=10;
    }
    return true;
}
void edgeadd(int u,int v,int w){
    if(find(u)==find(v))return ;
    siz[find(u)]+=siz[find(v)];
    siz[find(v)]=0;
    fa[find(v)]=find(u);
}
signed main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1;i<=n;i++)
        fa[i]=i,siz[i]=1;
    for(int i=1,u,v,w;i<n;i++){
        cin>>u>>v>>w;
        if(!check(w))
            edgeadd(u,v,w);
    }
    for(int i=1;i<=n;i++)
        if(siz[i])
            ans+=siz[i]*(n-siz[i])*(n-siz[i]-1);
    cout<<ans;
}
```

---

## 作者：Superiority (赞：1)

# 思路

首先，不难想出用 $0$ 或 $1$ 来作为边权，$1$ 表示这条边是一个幸运边，$0$ 表示不是一条幸运边。

然后，我们考虑树形 DP 如何设计状态。我们可以定义 $f_i$ 为以 $i$ 作为根节点时的能到达 $i$ 且路上有幸运边的节点个数。不难发现，如果只有 $f_i$ 的话，便会漏掉 $i$ 节点除自己子树以为能到达自己且路上有幸运边的节点。所以还要定义一个 $g_i$ 表示除自己子树以为能到达自己且路上有幸运边的节点。

接着，我们来推动态转移式方程。根据定义可以很显然的得出如果当这个**节点**与其**子节点**的边权为 $1$ 时，此时的 $f_x$ 就等于儿子节点的**所有子节点的个数**即 $f_x=s_y$，反之如果不行的话则 $f_x=f_y$。接着是 $g_x$，同理也要分成两种情况。当这个**节点**与它的**父亲节点**边权为 $1$ 时，那 $g_x$ 就加上除自己以外的所有点，也就是 $g_y = n - s_y$。反之要加上 $g_x$，可是便会漏掉父亲的子节点，所以还要加上 $f_x$，但 $f_x$ 里又包含了 $f_y$ 会导致重复计算，所以要减去 $f_y$。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN=1e6+5;
const int INF=1e18;
int n;
bool vis[MAXN];
int s[MAXN];
int a[MAXN];
int f[MAXN],g[MAXN];
vector<pair<int,int>> v[MAXN];
int ans;
int lucky(int x){
	while(x){
		if(x%10!=4&&x%10!=7) return 0;
		x/=10;
	}
	return 1;
}
void init(){
	for(int i=1;i<=n;i++) vis[i]=false;
}
void dfs(int x){
	vis[x]=true;
	s[x]++;
	for(int i=0;i<v[x].size();i++){
		if(!vis[v[x][i].first]){
			dfs(v[x][i].first);
			s[x]+=s[v[x][i].first];
			if(v[x][i].second) f[x]+=s[v[x][i].first];
			else f[x]+=f[v[x][i].first];
		}
	}
}
void deeps(int x){
	vis[x]=true;
	for(int i=0;i<v[x].size();i++){
		if(!vis[v[x][i].first]){
			if(v[x][i].second) g[v[x][i].first]+=s[1]-s[v[x][i].first];
			else g[v[x][i].first]+=g[x]+f[x]-f[v[x][i].first];
			deeps(v[x][i].first);
		}
	}
}
signed main(){
	cin>>n;
	for(int i=1;i<n;i++){
		int x,y,value;
		cin>>x>>y>>value;
		v[x].push_back({y,lucky(value)});
		v[y].push_back({x,lucky(value)});
	}
	init();
	dfs(1);
	init();
	deeps(1);
	for(int i=1;i<=n;i++) ans+=f[i]*(f[i]-1)+g[i]*(g[i]-1)+f[i]*g[i]*2;
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：ZBH_123 (赞：1)

## 这是一道树形 DP
### 1.设计状态
既然是用 DP 求解，那么第一步就是设计状态。如何设计状态呢？分析题目我们可以得知，这道题其实就是求到第 $i$ 个点经过了幸运边的点（以下简称幸运点）的个数，最后再通过幸运点的个数算出题目要求的三元组的个数。既然要求幸运点的个数，那我们就直接设 $dp_{i}$ 为以 $i$ 为根的子树中到达 $i$ 的幸运点的个数，设 $f_{i}$ 为以 $i$ 为根的子树之外的节点中幸运点的个数。这样，状态就设计好了。
### 2.状态转移方程
状态设计好了，接下来就应该开始推导状态转移方程了。我们先来看 $dp_{i}$ 如何转移。这里我们设 $i$ 的子结点为 $k$，$size_{i}$ 为以 $i$ 为根的子树的结点个数。那么，接下来我们就开始分情况讨论。第一种情况是从 $i$ 到 $k$ 的这条边是幸运边。在这种情况下，以 $k$ 为根的子树中的所有结点都可以变成幸运点。所以在这种情况下的状态转移方程是：
$$dp_{i}=\sum size_{k}$$
第二种情况是从 $i$ 到 $k$ 的这条边不是幸运边。在这种情况下，以 $k$ 为根的子树中只有那些本来就是幸运点的结点才能成为幸运点。所以在这种情况下的状态转移方程是：
$$dp_{i}=\sum dp_{k}$$
仿照 $dp_{i}$ 的状态转移方程的推导过程，我们来推一下 $f_{i}$ 的状态转移方程。同理，在 $i$ 到 $k$ 的这条边是幸运边的情况下，整棵树的结点个数 $size_{root}$ 减去 $size_{k}$。状态转移方程如下：
$$f_{i}=size_{root}-size_{k}$$
在 $i$ 到 $k$ 的这条边不是幸运边的情况下，$f_{i}$ 就只能是以 $i$ 为根的子树之外的幸运点的个数，也就是 $f_{i}+dp_{i}-dp_{k}$。这样，$f_{i}$ 的状态转移方程就被我们推出来了。
### 3.程序实现
一个程序上的细节就是，$dp_{i}$ 需要先算出叶结点的 $dp_{i}$ 后再计算，而 $f_{i}$ 则需要先算出根结点的 $f_{i}$ 再往下计算。最后统计答案的时候，有三种情况需要计算。第一种情况是全部从子树中获取三元组的其他结点，为 $dp_{i} \times (dp_{i}-1)$。第二种情况是全部从子树外的结点中获取三元组的其他结点，为 $f_{i} \times (f_{i}-1)$。最后一种情况是从子树中获取一个，从子树外的结点中再获取一个，为 $dp_{i} \times f_{i}$。

就这样，这道题就被我们解决了。

AC 代码：
```cpp
#include<iostream>
#include<cstring>
#include<vector>
#define ll long long
using namespace std;
int n,x,y,z;
bool vis[100001];
ll dp[100001],f[100001],Size[100001],ans;
struct edge{
	int to,w;
	bool flag;
};
vector<edge>node[100001];
void dfs(int x){
	bool flag=0;
	for(int i=0;i<node[x].size();i++){
		if(!vis[node[x][i].to]){
			flag=1;
			vis[node[x][i].to]=1;
			dfs(node[x][i].to);
			vis[node[x][i].to]=0;
			Size[x]+=Size[node[x][i].to];//在计算 size 的时候顺便计算 dp	
			if(node[x][i].flag)
				dp[x]+=Size[node[x][i].to];
			else
				dp[x]+=dp[node[x][i].to];
		}
	}
	Size[x]++;
	if(!flag)
		return;
}
void getdp(int x){//用换根 DP 的方式计算 f
	for(int i=0;i<node[x].size();i++){
		if(!vis[node[x][i].to]){
			if(node[x][i].flag)
				f[node[x][i].to]=Size[1]-Size[node[x][i].to];
			else
				f[node[x][i].to]=f[x]+dp[x]-dp[node[x][i].to];
			vis[node[x][i].to]=1;
			getdp(node[x][i].to);
			vis[node[x][i].to]=0;
		}
	}
}
int main(){
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>x>>y>>z;
		bool bbb=0;
		while(z>0){//判断幸运边
			int tmp=z%10;
			if(tmp!=4&&tmp!=7){
				bbb=1;
				node[x].push_back((edge){y,z,0});
				node[y].push_back((edge){x,z,0});
				break;
			}
			z/=10;
		}
		if(bbb==0){
			node[x].push_back((edge){y,z,1});
			node[y].push_back((edge){x,z,1});
		}
	}
	vis[1]=1;
	dfs(1);
	memset(vis,0,sizeof(vis));
	vis[1]=1;
	for(int i=0;i<node[1].size();i++){
		if(!vis[node[1][i].to]){
			if(node[1][i].flag)
				f[node[1][i].to]=Size[1]-Size[node[1][i].to];
			else
				f[node[1][i].to]=dp[1]-dp[node[1][i].to];
			vis[node[1][i].to]=1;
			getdp(node[1][i].to);
		}
	}
	for(int i=1;i<=n;i++)
		ans+=dp[i]*(dp[i]-1)+f[i]*(f[i]-1)+2*dp[i]*f[i];//统计答案
	cout<<ans;
	return 0;
}
```

---

## 作者：quarmer (赞：1)

首先看他让求得三元组，要先从 $i$ 到 $j$，再从 $j$ 到 $k$。可以理解为以 $j$ 为中转站，从 $i$ 到 $k$。

然后思考，以 $x$ 为中转站的三元组怎么算？设 $g_{i}$ 表示在 $i$ 的子树中与 $i$ 的路径上有至少一条边为幸运边的点的个数。则这些点任两个做三元组两边的元素都可，则在 $x$ 的子树中，答案为 $g_{x} \times (g_{x}-1)$。

然后想如何求 $g_{i}$。设 $y$ 为 $x$ 的子节点，$edge(x,y)$ 为连接 $x,y$ 两点的边。若 $edge(x,y)$ 为幸运边，则 $y$ 的子树中所有的点都可以计入 $g_{x}$，否则，将 $g_{y}$ 计入 $g_{x}$。则 $x$ 对于每一个 $y$，方程为：

$\begin{cases}
   g_{x} = g_{x} + g_{y}  & \text{ if } edge(x,y) \text { is lucky} \\
   g_{x} = g_{x} + sz_{y} &  \text{ if } edge(x,y) \text { is not lucky}
\end{cases}$

但是此时我们只求出来了根节点的值，但是需要得到每一个点的值，考虑换根。

依然设 $y$ 为 $x$ 的子节点，$edge(x,y)$ 为连接 $x,y$ 两点的边。若 $edge(x,y)$ 为幸运边，则 $x$ 的子树中除 $y$ 的子树中所有的点都可以计入 $g_{x}$，否则，$g_{y}=g_{x}$。则换根时 $x$ 对于每一个 $y$，方程为：

$\begin{cases}
   g_{y} = g_{y} + n - sz_{y}  &\text{ if } edge(x,y) \text { is lucky} \\
   g_{y} = g_{x}  &  \text{ if } edge(x,y) \text { is not lucky}
\end{cases}$

最后放一下代码：
```cpp
#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <stack>
#include <queue>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#define l(p) t[p].l
#define r(p) t[p].r
#define maxn(p) t[p].maxn
#define maxd(p) t[p].maxd
#define int long long
#define lb(x) (x & (-x))
using namespace std ;
const int mod = 1e9 + 7 ;
int read() {
	char ch ;int s = 0 ;int w = 1;
	while((ch = getchar()) >'9' || ch < '0' )if(ch == '-')w = -1 ;
	while(ch >= '0' && ch <= '9')s = (s << 1) + (s << 3) + (ch ^ 48) , ch = getchar() ;
	return s * w ;
}
void print(int x) {
	if(x > 9)print(x / 10) ;
	putchar(x % 10 + '0') ;
}                                   
void prn(int x) {   
	if(x < 0) putchar('-'), x = -x ;                     
	print(x) ;                                          
	putchar('\n') ;            
}  
int n ;
int head[400005], ver[400005], nxt[400005], edge[400005], tote ;
void add(int x, int y, int z) {
	ver[++tote] = y, nxt[tote] = head[x], head[x] = tote, edge[tote] = z ;
} 
int g[100005], f[100005] ;
int sz[100005] ;
bool check(int x) {
	while(x) if(x % 10 != 4 && x % 10 != 7) return 0 ; else x /= 10 ;
	return 1 ;
}
void dfs1(int x, int fa) {
	sz[x] = 1 ;
	for(int i = head[x] ; i ; i = nxt[i]) {
		int y = ver[i] ;
		if(y == fa) continue ;
		dfs1(y, x) ;
		sz[x] += sz[y] ;
		if(check(edge[i])) g[x] += sz[y] ;
		else g[x] += g[y] ;
	}
}
int ans ;
void getans(int x, int fa) {
	ans += g[x] * (g[x] - 1) ;
	for(int i = head[x] ; i ; i = nxt[i]) {
		int y = ver[i] ;
		if(fa == y) continue ;
		int t = g[y] ;
		if(check(edge[i])) g[y] = g[y] + n - sz[y] ;
		else g[y] = g[x] ;
		getans(y, x) ;
		g[y] = t ;
	}
}
signed main() {
	n = read() ;
	for(int i = 1 ; i < n ; i++) {
		int x = read(), y = read(), z = read() ;
		add(x, y, z) ;
		add(y, x, z) ;
	}
	dfs1(1, 0) ;
	getans(1, 0) ;
	cout << ans ;
	return 0 ;
}
```

---

## 作者：IkunTeddy (赞：0)

# 做法分析
此题一看就可以考虑树形 DP 但是当前点 $u$ 的答案可以从其儿子 $v$ 传导过来，也可以从其父亲 $f$ 传导过来所以一般的树形 DP 是不行的，但换根 DP 刚好符合我们的要求。

我们需要三个数组，一个 $size$，$dp$ 和 $f$ 分别来记录当前点的子树的节点个数，从儿子传来的答案数和从父亲传来的答案数。
接下来就是状态转移方程了：

如果当前边为幸运边，那么 $u$ 的所有子结点都能跟他构成三元组，而且 $v$ 的所有父亲也能跟他构成三元组，所以 $dp_u$ 就等于所有 $size_v$ 之和，$f_{v}= size_1 -size_v$。

如果不为幸运边就只能继承子树的答案，所以 $dp_u$ 等于所有 $dp_v$ 之和。$f_v=f_u+dp_u-dp_v$。

答案的三元组总数可以是：

1. 都从子树取。

2. 都从父亲中取。

3. 子树中取一个，父亲中取一个。


3 种情况加起来就只最终答案。

# Code
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
#define LL long long
const int maxn=100000+10;
int check(int x){
	int k=x;
	while(x>0){
		if(x%10!=4&&x%10!=7) return 0;
		x=x/10;
	}
	return 1;
}
struct edge{
	int x;
	int flag;
};
vector<edge> vt[maxn];
LL ans;
LL dp[maxn][2];
LL size[maxn];
int vis[maxn];

void dfs_size(int u,int f){
	int l=vt[u].size();
	size[u]=1;
	for(int i=0;i<l;i++){
		int v=vt[u][i].x;
		int tmp=vt[u][i].flag;
		if(v==f) continue;
		dfs_size(v,u);
		size[u]+=size[v];
		if(tmp==1){
			dp[u][0]+=size[v];
		}else{
			dp[u][0]+=dp[v][0];
		}
	}
}

void dfs(int u,int f){
	int l=vt[u].size();
	vis[u]=1;
	for(int i=0;i<l;i++){
		int v=vt[u][i].x;
		int tmp=vt[u][i].flag;
		if(v==f) continue;
		if(tmp==1){
			dp[v][1]=size[1]-size[v];
		}else {
			dp[v][1]=dp[u][1]+dp[u][0]-dp[v][0];
		}
		dfs(v,u);
	}
	//cout<<u<<" "<<dp[u][0]<<" "<<dp[u][1]<<endl;
	ans+=dp[u][0]*(LL)(dp[u][0]-1)+dp[u][1]*(LL)(dp[u][1]-1)+2*(dp[u][0]*(LL)dp[u][1]);
}

int main(){
	int n;
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v,w;
		cin>>u>>v>>w;
		int c=check(w);
		vt[u].push_back({v,c});
		vt[v].push_back({u,c});
		//cout<<u<<" "<<v<<" "<<c<<endl;
	}
	dfs_size(1,0);
	//for(int i=1;i<=n;i++) cout<<size[i];
	//cout<<endl;
	dfs(1,1);
	cout<<ans;

	return 0;
}

```


---

## 作者：Supor__Shoep (赞：0)

本人懒得去直接算答案，所以我直接用总的三元组数量减去不合法的数量。

怎么求不合法的数量呢？不合法时，我们需要使得两条路径上**都没有**或者**其中一个有**幸运数字。

- 对于“都没有”的情况，我们考虑用并查集将相邻的不幸运边合并成同一个集合，然后在其中选择三个不同的节点，设并查集大小为 $siz$，则答案就是 $siz(siz-1)(siz-2)$；

- 对于“其中一个有”的情况，我们先在集合当中确定一个点作为 $x$，然后在集合内以及集合外各选择一个节点作为 $y$ 或者 $z$，由于选出来之后两者在三元组中的顺序可以调换一次，所以答案为 $2\times siz(siz-1)(n-siz)$。

而总的三元组数量非常好求，就相当于在 $n$ 个节点中选择 $3$ 个点并进行排序，数量为 $A_{n}^{3}=n(n-1)(n-2)$。

因此总共的合法答案为：

$$n(n-1)(n-2)-\sum siz(siz-1)(siz-2)+2\times siz(siz-1)(n-siz)$$

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e5+5;
int n,m;
int check(int x)//判断幸运数字
{
	while(x>0)
	{
		int temp=x%10;
		if(temp!=4ll&&temp!=7ll)	return 0;
		x/=10;
	}
	return 1;
}
int res;
int fa[MAXN],siz[MAXN];
int find(int x)
{
	if(fa[x]==x)	return x;
	return fa[x]=find(fa[x]);
}
set<int> st;
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)	fa[i]=i,siz[i]=1ll;
	for(int i=1;i<n;i++)
	{
		int x,y,z;
		cin>>x>>y>>z;
		int flag=check(z);
		if(!flag)
		{
			x=find(x),y=find(y);
			if(x==y)	continue;
			fa[x]=y,siz[y]+=siz[x];//合并集合
		}
	}
	if(n<=2ll)//特判
	{
		puts("0");
		return 0;
	}
	res=n*(n-1ll)*(n-2ll);//三元组总数量
	for(int i=1;i<=n;i++)	st.insert(find(i));
	for(set<int>::iterator it=st.begin();it!=st.end();it++)
	{
		if(siz[*it]==1ll)	continue;//加不加无所谓
		res-=siz[*it]*(siz[*it]-1ll)*(n-siz[*it])*2ll+siz[*it]*(siz[*it]-1ll)*(siz[*it]-2ll);//减去不合法的
	}
	cout<<res;
	return 0;
}
```

---

## 作者：lgswdn_SA (赞：0)

清新换根题（好久没做树形 DP 了竟然忘了套路换根）

考虑暴力的话，直接枚举 $i$，然后树形 DP 一下求出答案。然后这很显然可以换根优化。

考虑 $f(u)$ 表示子树内有多少 $w$ 满足 $[u,w]$ 路径是 lucky 的，$g(u)$ 表示子树外的数量。

先考虑 $f_u$ 的转移。转移分类讨论，$(u,v)$ 是 lucky 边以及不是 lucky 边的情况。如果是，那么整一个子树都合法；如果不是，那么 lucky 边就在儿子的子树中。所以有转移

$$
f_u=\sum_{v\in son_u} sz_v[lucky(u,v)]+f_v[unlucky(u,v)]
$$

考虑 $g_v$ 的转移，同样分类讨论。如果 $u,v$ 是 lucky 边，那么$v$ 子树外所有点到 $v$ 的路径都是 lucky 的；如果不是，那么分两种情况：从 $u$ 子树外过来和兄弟节点过来。父亲子树外的贡献为 $g_u$，兄弟的贡献为 $f_u-f_v$。所以有转移

$$
g_v=(n-sz_v)[lucky(u,v)]+(g_u+f_u-f_v)[unlucky(u,v)]
$$

考虑计算答案。我们枚举点 $i$。有 4 种情况，分别为 $j$ 在子树内/外，$k$ 在子树内/外。我们先随便选，然后再减去 $j,k$ 相同的情况即可。

$$
ans=\sum_i (f_i+g_i)^2-\sum_i (f_i+g_i)
$$

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(register int i=(a);i<=(b);i++)
#define per(i,a,b) for(register int i=(a);i>=(b);i--)
using namespace std;
const int N=1e5+9;
typedef pair<int,bool> pii;

inline int read() {
    register int x=0, f=1; register char c=getchar();
    while(c<'0'||c>'9') {if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+c-48,c=getchar();}
    return x*f;
}

int n,sz[N],f[N],g[N],ans;
vector<pii>e[N];

bool lucky(int x) {
	while(x) {
		if(x%10!=4&&x%10!=7) return 0;
		x/=10;
	}
	return 1;
}

void dfs1(int u,int fa) {
	sz[u]=1;
	for(auto to:e[u]) {
		int v=to.first, w=to.second;
		if(v==fa) continue;
		dfs1(v,u);
		sz[u]+=sz[v];
		f[u]+=(w?sz[v]:f[v]);
	}
}
void dfs2(int u,int fa) {
	for(auto to:e[u]) {
		int v=to.first, w=to.second;
		if(v==fa) continue;
		g[v]=(w?n-sz[v]:g[u]+f[u]-f[v]);
		dfs2(v,u); 
	}
	ans+=(f[u]+g[u])*(f[u]+g[u])-f[u]-g[u];
}

signed main() {
	n=read();
	rep(i,2,n) {
		int u=read(), v=read(), w=read(); bool l=lucky(w);
		e[u].push_back(make_pair(v,l)),
		e[v].push_back(make_pair(u,l));
	}
	dfs1(1,0);
	dfs2(1,0);
	printf("%lld\n",ans);
	return 0;
}
```

---

