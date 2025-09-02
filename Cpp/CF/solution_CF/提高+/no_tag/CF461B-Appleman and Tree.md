# Appleman and Tree

## 题目描述

给你一棵有 $n$ 个节点的树，下标从 $0$ 开始。

第 $i$ 个节点可以为白色或黑色。

现在你可以从中删去若干条边，使得剩下的每个部分恰有一个黑色节点。

问有多少种符合条件的删边方法，答案对 $10^9+7$ 取模。

## 样例 #1

### 输入

```
3
0 0
0 1 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
6
0 1 1 0 4
1 1 0 0 1 0
```

### 输出

```
1
```

## 样例 #3

### 输入

```
10
0 1 2 1 4 4 4 0 8
0 0 0 1 0 1 1 0 0 1
```

### 输出

```
27
```

# 题解

## 作者：Crab_Dave (赞：22)

## CF461B Appleman and Tree 题解

+ ### 题意

  给出一棵以 $0$ 为根的树，除根之外有些点是黑色，有些点是白色。

  求有多少种划分方案数，使得将树划分成若干个连通块并且每个连通块有且仅有一个黑点，对 $10^9+7$ 取模。

+ ### 思路

  树形dp。

  设 $dp[u][0/1]$ 表示 $u$ 点属于一个无黑点/有且仅有一个黑点的连通块时的方案数。

  对于 $dp[u][1]$：$dp[u][1]=dp[u][1]*dp[v][0]+dp[u][1]*dp[v][1]+dp[u][0]*dp[v][1]$

  其中三项的转移情况分别是：（儿子不合理，贴到父亲上）+（父子都合理，中间划开）+（父亲不合理，贴到儿子上）

  同理，对于 $dp[u][0]$：$dp[u][0]=dp[u][0]*dp[v][0]+dp[u][0]*dp[v][1]$

  即：（父子不合理）+（儿子合理，于是划开）

  初始化为 $dp[u][color[u]]=1$

+ ### 部分代码

  ```cpp
  void dfs(int u){dp[u][c[u]]=1;
  	for(int i=head[u];i;i=e[i].next){
  		int v=e[i].to; if(v==fa[u])continue; dfs(v);
  		dp[u][1]=dp[u][1]*(dp[v][0]+dp[v][1])%mod+dp[u][0]*dp[v][1]%mod;
  		dp[u][1]%=mod;dp[u][0]=dp[u][0]*(dp[v][0]+dp[v][1])%mod;
  	}
  }
  ```

---

## 作者：Zimo_666 (赞：10)

# [CF461B] Appleman and Tree

## Description

给你一棵有 $n$ 个节点的树，下标从 $0$ 开始。

第 $i$ 个节点可以为白色或黑色。

现在你可以从中删去若干条边，使得剩下的每个部分恰有一个黑色节点。

问有多少种符合条件的删边方法，答案对 $10^9+7$ 取模。

## Solution

- 这题考虑断开哪些边反而不好计算，转而考虑进行树形DP。

- 考虑设 $f_{i,j}$ 表示以 $i$ 为根的联通块内有 $j$ 个黑点的方案数，显然 $j=0$ 或 $j=1$。

  我们考虑从子树往下转移时，父子节点的边是否断开即可转移。

  设 $fa_y=x$。

  则有若该条边断开，那么 $y$ 子树必须合法，即有 $f_{x,0}\leftarrow f_{x,0}\times f_{y,1}$ 和 $f_{x,1}\leftarrow f_{x,1}\times f_{y,1}$。

  若连上则有 $y$ 合法性可以转移给 $x$，即有 $f_{x,0}\leftarrow f_{x,0}\times f_{y,0}$ 和 $f_{x,1}\leftarrow f_{x,0}\times f_{y,1}+f_{x,1}\times f_{y,0}$。

- 答案为 $f_{0,1}$。记得读入点颜色时是 $0\to n-1$。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+7;
vector<int> G[N<<2];
int n,col[N];
const int mod=1e9+7;
int dp[N][10];
void dfs(int u,int father){
	dp[u][col[u]]=1;
	for(int k:G[u]){
		if(k==father) continue;
		dfs(k,u);
		dp[u][1]=dp[u][1]%mod*(dp[k][0]%mod+dp[k][1]%mod)%mod+dp[u][0]%mod*dp[k][1]%mod;
		dp[u][1]%=mod;
		dp[u][0]=dp[u][0]%mod*(dp[k][0]%mod+dp[k][1]%mod)%mod;
		dp[u][0]%=mod;
	}
}
signed main(){
	cin>>n;
	for(int i=1;i<=n-1;i++){
		int p;scanf("%lld",&p);
		G[p].push_back(i);
		G[i].push_back(p); 
	}
	for(int i=0;i<n;i++){
		scanf("%lld",&col[i]);
	}
	dfs(0,-1);
	printf("%lld",dp[0][1]%mod);
}
```



---

## 作者：GIFBMP (赞：7)

又是一道好题！

我们对于每棵子树考虑，一个点要么在只有一个黑点的块里，要么所在的块里一个黑点也没有，这显然是满足无后效性的，于是我们考虑DP。

我们设 $f_{x,1}$ 表示当前根为 $x$，当前在某个只有一个黑点的连通块里的方案数，$f_{x,0}$ 表示当前根为 $x$，当前在某个没有黑点的连通块里的方案数，则有：

$$f_{x,1}=f_{x,1}\times(f_{v,0}+f_{v,1})+f_{x,0}\times f_{v,1}$$

$$f_{x,0}=f_{x,0}\times(f_{v,0}+f_{v,1})$$

显然答案为 $f_{1,1}$。

初值十分好推，即：

$$f_{i,col_i}=1$$

**细节：这题的点是从0开始编号的，我被这个坑了好几次……**

**细节2：两个DP式的顺序不能颠倒，因为第一个要用上一层的状态……**

Code:

```cpp
#include <cstdio>
#include <vector>
using namespace std ;
const int MAXN = 1e5 + 10 , mod = 1e9 + 7 ;
int n , col[MAXN] ; 
long long f[MAXN][2] ;
vector <int> G[MAXN] ;
void dfs (int x , int fa) {
	f[x][col[x]] = 1 ;
	for (int i = 0 ; i < G[x].size () ; i++) {
		int v = G[x][i] ;
		if (v == fa) continue ;
		dfs (v , x) ;
		f[x][1] = (f[x][1] * ((f[v][0] + f[v][1]) % mod) % mod + f[x][0] * f[v][1] % mod) % mod ;
		f[x][0] = f[x][0] * ((f[v][0] + f[v][1]) % mod) % mod ;
	}
}
int main () {
	scanf ("%d" , &n) ;
	for (int i = 1 ; i < n ; i++) {
		int v ;
		scanf ("%d" , &v) ;
		G[i + 1].push_back (v + 1) ;
		G[v + 1].push_back (i + 1) ;  
	}
	for (int i = 1 ; i <= n ; i++)
		scanf ("%d" , &col[i]) ;
	dfs (1 , 0) ;
	printf ("%lld" , f[1][1]) ;
	return 0 ;
}
```

---

## 作者：QwQcOrZ (赞：6)

一个比较麻烦的做法，如果想要更简洁的转移可以看其他题解

------------

### 树形dp

设 $dp_{i,0/1}$ 表示节点 $i$ 在有且仅有一个 $1$/没有一个 $1$ 的连通块内的划分方案数

当 $col_i$ 为 $0$ 时，$dp_{i,0}=\prod dp_{son,0}+dp_{son,1}$

（若儿子连通块内没有 $1$ 则必须连到父亲，若儿子连通块内有 $1$ 则必须不连父亲）

$dp_{i,1}=\sum\limits_{j\in son}dp_{j,1}\prod\limits_{k\in son\land k\ne j} dp_{k,0}+dp_{k,1}$

（意义为枚举连通块有 $1$ 的儿子，然后其它儿子的方案数和 $dp_{i,0}$ 同理）

当 $col_i$ 为 $1$ 时，$dp_{i,0}=0$

（如果当前节点为 $1$ 那么显然不可能连通块内没有 $1$）

$dp_{i,1}=\prod dp_{son,0}+dp_{son,1}$

（这里与第一个转移式同理）

可以发现复杂度瓶颈在于计算当 $col_i$ 为 $0$ 时的 $dp_{i,1}$

这里可以通过记前后缀积或逆元等方式计算

我~~因为比较懒~~，这里用了逆元，于是复杂度变成了 $O(nlogn)$

如果记前后缀积复杂度可以达到 $O(n)$

$Code Below$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
const int p=1e9+7;

inline int read()
{
	register int s=0;
	register char c=getchar(),lc='+';
	while (c<'0'||'9'<c) lc=c,c=getchar();
	while ('0'<=c&&c<='9') s=s*10+c-'0',c=getchar();
	return lc=='-'?-s:s;
}
void write(register int x)
{
	if (x<0)
	{
		putchar('-');
		x=-x;
	}
	if (x<10) putchar(x+'0');
	else
	{
		write(x/10);
		putchar(x%10+'0');
	}
}
inline void print(const register int x,const register char c='\n')
{
	write(x);
	putchar(c);
}
struct edge
{
	int to,nxt;
}e[N];
int head[N],cnt=0;
void add(int u,int v)
{
	e[++cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
int dp[N][2];
bool col[N];
int power(int a,int b)
{
	int ret=1;
	while (b)
	{
		if (b&1) ret=ret*a%p;
		a=a*a%p;
		b/=2;
	}
	return ret;
}
void dfs(int now)
{
	int mul=1,count=0;
	for (int i=head[now];i;i=e[i].nxt)
	{
		int to=e[i].to;
		dfs(to);
		mul=mul*((dp[to][0]+dp[to][1])%p)%p;
	}
	for (int i=head[now];i;i=e[i].nxt)
	{
		int to=e[i].to;
		count=(count+mul*power((dp[to][0]+dp[to][1])%p,p-2)%p*dp[to][1]%p)%p;
	}
	if (col[now]==0)
	{
		dp[now][0]=mul;
		dp[now][1]=count;
	}
	else
	{
		dp[now][0]=0;
		dp[now][1]=mul;
	}
}

signed main()
{
	int n=read();
	for (int i=2;i<=n;i++)
	{
		int fa=read()+1;
		add(fa,i);
	}
	for (int i=1;i<=n;i++) col[i]=read();
	dfs(1);
//	for (int i=1;i<=n;i++) print(dp[i][0],' '),print(dp[i][1]);
	print(dp[1][1]);

	return 0;
}
```

---

## 作者：w33z8kqrqk8zzzx33 (赞：5)

在树上做统计，很快想到树形动态规划。

树形动规通常第一个状态是一棵子树，在这个题目里面也可以这样用。

但是这个题目里，对与某个子树，这个子树的根可能还没有配上一个黑色节点。应为对与一个子树只有子树根所在的块可以扩展，仅需要在保存子树所在的块里面有没有一个黑色节点。

设 $DP[i][0]$ 为有多少种方案来把 $i$ 的子树分块，使得 $i$ 所在的块没有一个黑色节点。相似，设 $DP[i][1]$ 为有多少种方案来把 $i$ 的子树分块，使得 $i$ 所在的块有恰好一个一个黑色节点。

退出来式子：

当 $u$ 是黑色节点，

$$DP[u][0]=0$$
$$DP[u][1]=\prod_{(u,v)\in G}(DP[v][0]+DP[v][1])$$

（对与一个孩子节点 $v$，如果孩子所在的块里面有黑色节点，那么必须把这条边切开，如果没有，必须连）

当 $u$ 是白色节点，

$$DP[u][0]=\prod_{(u,v)\in G}(DP[v][0]+DP[v][1])$$

（和以上道理一样）

$$DP[u][1]=\sum_{(u,v)\in G}(\frac{DP[u][0]DP[v][1]}{DP[v][0]+DP[v][1]})$$

（这个等价于对与一个孩子 $v$，所有别的孩子都和 $DP[u][0]$  一样处理，但是把 $DP[v][1]$ 练上来，来提供唯一的黑色节点）

加上算逆元就好了。

主要代码：

```cpp
vector<int> elist[100005];
int color[100005];
int dp[100005][2];

int qpow(const int&b, const int&e) {
	if(!e) return 1;
	if(!(e&1)) return qpow(1ll*b*b%MOD,e>>1);
	return 1ll*b*qpow(b,e-1)%MOD;
}

void dfs(int u) {
	for(int&v:elist[u])dfs(v);
	if(color[u]) {
		dp[u][1] = 1;
		for(int& v:elist[u]) dp[u][1]=1ll*dp[u][1]*(dp[v][0]+dp[v][1])%MOD;
	} else {
		dp[u][0] = 1;
		for(int&v:elist[u]) dp[u][0]=1ll*dp[u][0]*(dp[v][0]+dp[v][1])%MOD;
		for(int&v:elist[u]) {
			dp[u][1] += 1ll*dp[u][0]*qpow((dp[v][0]+dp[v][1])%MOD,MOD-2)%MOD*dp[v][1]%MOD;
			if(dp[u][1] >= MOD) dp[u][1] -= MOD;
		}
	}
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; gi(n);
	rep1(i, n-1) {
		int f; gi(f);
		elist[f].pb(i);
	}
	rep(i, n) gi(color[i]);
	dfs(0);
	print(dp[0][1]);
}

```

---

## 作者：GalwayGirl (赞：3)

又是一道练习树形 dp 的好题

## Sloution
设 $f_{i,0}$ 为第 $i$ 个节点属于一个无黑点的连通块的方案数，$f_{i,1}$ 为第 $i$ 个节点属于有且仅有一个黑点的连通块的方案数。可以推出如下转移方程：

$f_{fa,1}=f_{fa,1}×f_{son,1}+f_{fa,1}×f_{son,0}+f_{fa,0}×f_{son,1}$

$f_{fa,0}=f_{fa,0}×f_{son,1}+f_{fa,0}×f_{son,0}$

最后贴上完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+100,mod=1e9+7;
int n,head[N],color[N],c;
long long f[N][3];
struct xzh{
    int next,to;
}edge[2*N];
void add(int u,int v){

    c++;
    edge[c].next=head[u];
    edge[c].to=v;
    head[u]=c;
}
void dfs(int now,int fa){
    f[now][color[now]]=1;
    long long ans1=0,ans0=0;
    for(int i=head[now];i;i=edge[i].next){
        int v=edge[i].to;
        if(v==fa)continue;
        dfs(v,now);
        ans1+=f[now][1]*f[v][1]+f[now][1]*f[v][0]+f[now][0]*f[v][1];
        ans0+=f[now][0]*f[v][1]+f[now][0]*f[v][0];
    }
    f[now][1]+=ans1;
    f[now][0]+=ans0;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        int u;
        scanf("%d",&u);
        add(u,i);
        add(i,u);
    }
    for(int i=0;i<n;i++)scanf("%d",&color[i]);
    dfs(0,-1);
    printf("%lld",f[0][1]);
    return 0;
}
```


---

## 作者：GavinZheng (赞：3)

# CF461B Appleman and Tree

[传送门](https://www.luogu.org/problem/CF461B)

一道比较容易的树形DP。

考虑用$dp[i][1]$代表将$i$分配给$i$的子树内黑点的方案数，$dp[i][0]$代表将$i$分配给$i$的子树之外的黑点的方案数。

首先，考虑分给$i$的子树黑点的情况：$dp[i][1]=\sum _{p\in son_i} dp[p][0]\prod _{t\in son_i,t\neq p} (dp[t][1]+dp[t][0])$

再考虑分给其他子树的情况：$dp[i][0]=\prod _{t\in son_i}(dp[t][0]+dp[t][1])$

特别的，当这个点是黑点时，$dp[i][0]=0,dp[i][1]=\prod_{t\in son_i} (dp[t][1]+dp[t][0])$

初始化一个点最深的点时，如果点为白点$dp[i][0]=1,dp[i][1]=0$，否则$dp[i][0]=0,dp[i][1]=1$

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<vector>
#define ll long long
#define mod 1000000007
#define maxn (int)(1e5+100)
using namespace std;
ll dp[maxn][2],n;
ll pre[maxn],suc[maxn];
vector<int>side[maxn];
bool col[maxn];
int cnt,list[maxn];
void dfs(int now,int fa) {
    if(side[now].size()==1&&fa!=0) {
        if(col[now])dp[now][0]=0,dp[now][1]=1;
        else dp[now][0]=1,dp[now][1]=0;
        return;
    }
    dp[now][0]=1,dp[now][1]=0,pre[0]=1;
    for(int i=0;i<side[now].size();i++) {
        int v=side[now][i];if(v==fa)continue;
        dfs(v,now);
        dp[now][0]*=dp[v][0]+dp[v][1];dp[now][0]%=mod;
    }
    cnt=0;
    for(int i=0;i<side[now].size();i++) {
        int v=side[now][i];if(v==fa)continue;
        list[++cnt]=v;
    }
    suc[cnt+1]=1;
    if(col[now]){dp[now][1]=dp[now][0];dp[now][0]=0;return;}
    for(int i=1;i<=cnt;i++) {pre[i]=pre[i-1]*(dp[list[i]][0]+dp[list[i]][1]);pre[i]%=mod;}
    for(int i=cnt;i>=1;i--) {suc[i]=suc[i+1]*(dp[list[i]][0]+dp[list[i]][1]);suc[i]%=mod;}
    for(int i=1;i<=cnt;i++) {
       dp[now][1]+=dp[list[i]][1]*((pre[i-1]*suc[i+1])%mod);dp[now][1]%=mod;
    }
    return;
}
int main() {
    ios::sync_with_stdio(0);
    cin>>n;
    for(int i=2;i<=n;i++) {
        int u;cin>>u;u++;side[i].push_back(u);side[u].push_back(i);
    }
    for(int i=1;i<=n;i++)cin>>col[i];
    dfs(1,0);
    cout<<dp[1][1];
    return 0;
}
```



---

## 作者：RiceFruit (赞：2)

[题目链接](https://www.luogu.com.cn/problem/CF461B)

## 题目大意

给你一颗 $n$ 个点的树，每个节点是黑色或白色，你可以删去一些边，是的删完后每个连通块都有且仅有一个黑色节点。求符合条件的删边方法数，答案对 $10^9+7$ 取模。数据范围：$1\le n \le 10^5$。

## 思路

看到这种有关树的题目，自然想到动态规划。

我们设 $f_{x,0}$ 表示以 $x$ 为根的子树中，$x$ 所在的连通块没有黑点，$f_{x,1}$ 表示以 $x$ 为根的子树中，$x$ 所在的连通块有且仅有一个黑点，易得 $f_{1,1}$ 为最终答案。

我们不妨设 $son_x$ 表示 $x$ 的儿子的集合，$y$ 为 $x$ 的儿子。

先考虑 $f_{x,0}$ 的转移。

$\texttt{I.}x$  是一个白点：

若 $y$ 所处的连通块内   没有黑点，则一定要连向 $x$，若有黑点，则一定不能连向 $x$。

故方案数为 $\prod\limits_{y\in son_x} f_{y,0}+f_{y,1}$。

$\texttt{II.}x$ 是一个黑点：

不可能，直接跳过。

在考虑 $f_{x,1}$ 的转移。

$\texttt{I.}x$ 是一个白点。

则要求 $y$ 所处的连通块一定要有黑点，故方案数为 $\sum\limits_{y\in son_x} f_{x,0}\cdot f_{y,1}$。

$\texttt{II.}x$ 是一个黑点。

则 $y$ 所处的连通块有无黑点都可以：因为如果有黑点，那么就断开这条边；若没有黑点，那么就连上这条边。故方案数为 $\sum\limits_{y\in son_x} f_{x,1}\cdot (f_{y,0}+f_{y,1})$。

那么转移式就推完了，下面整理一下：

对于每个 $x$ 的儿子 $y$，都做如下转移：

$f_{x,1}=f_{x,1}\cdot (f_{y,0}+f_{y,1})+f_{x,0}\cdot f_{y,1}$。

$f_{x,0}=f_{x,0}\cdot (f_{y,0}+f_{y,1})$。

**注意**：一定要分好 $f_{x,0}$ 和 $f_{x,1}$ 的顺序。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5,mod=1e9+7;
inline int read();
int n;
struct sa{
    int nxt;
    int to;
}e[N<<2];
int h[N],cnt,u;
void add(int u,int v){
    e[++cnt]=(sa){h[u],v};
    h[u]=cnt;
    return;
}
bool val[N];
int f[N][2];
void dfs(int x,int fa){
    for(int i=h[x];~i;i=e[i].nxt){
        int y=e[i].to;
        if(y==fa)continue;
        dfs(y,x);
        int tmp1=f[x][1]*((f[y][0]+f[y][1])%mod)%mod;
        int tmp2=f[x][0]*f[y][1];
        f[x][1]=(tmp1+tmp2)%mod;
        f[x][0]=f[x][0]*((f[y][0]+f[y][1])%mod)%mod;
    }
    return;
}
signed main(){
    memset(h,-1,sizeof h);
	n=read();
    for(int i=1;i<n;i++){
        u=read();
        add(u,i);
        add(i,u);
    }
    for(int i=0;i<n;i++){
        val[i]=read();
        f[i][val[i]]=1;
    }
    dfs(0,-1);
    printf("%lld\n",f[0][1]);
	return 0;
}
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
```



---

## 作者：Yizhixiaoyun (赞：1)

在树上求方法数，树形 $\text{dp}$ 不难想到。

令 $dp_{i,j}$ 表示第 $i$ 个点所属有 $j$ 个黑点的联通块的方案数。由于目标状态所需要的联通块是有 $1$ 个黑点的，因此只需要 $dp_{i,0}$ 与 $dp_{i,1}$ 即可。

状态转移易得。考虑研究父亲节点与儿子节点的关系，无论父亲还是儿子，只要不满足要求，那么就将它并入对方。否则都合理，那么为了追求更多的方案数就将它们分开。

需要注意的是，节点下标从 $0$ 开始。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
const int maxn=1e5+5;
int read(){
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-') f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=x*10+c-48;
        c=getchar();
    }
    return x*f;
}
int n;
int a[maxn];
int dp[maxn][2];

int cnt_edge,head[maxn];
struct edge{
    int to,nxt;
}e[maxn<<1];
void add(int u,int v){
    e[++cnt_edge].nxt=head[u];
    e[cnt_edge].to=v;
    head[u]=cnt_edge;
}
void dfs(int u,int fa){
    dp[u][a[u]]=1;
    for(register int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;
        if(v==fa) continue;
        dfs(v,u);
        dp[u][1]=(dp[u][1]*((dp[v][0]+dp[v][1])%mod)%mod+dp[u][0]*dp[v][1]%mod)%mod;
		dp[u][0]=dp[u][0]*((dp[v][0]+dp[v][1])%mod)%mod;
    }
}

inline void init(){
    n=read();
    for(register int i=2;i<=n;++i){
        int u=read()+1;
        add(u,i);add(i,u);    
    }
    for(register int i=1;i<=n;++i) a[i]=read();
}

signed main(){
    init();
    dfs(1,0);
    printf("%lld",dp[1][1]);
}
```

---

## 作者：TernaryTree (赞：1)

不懂啊，这有 $2000$？

$f_{u,0/1}$ 表示 $u$ 为子树时 $u$ 所在连通块内没有/有黑色点的方案数。

则

$$
\begin{aligned}
f_{u,0}&=
\begin{cases}
\prod\limits_{u\to v}(f_{v,0}+f_{v,1})&(a_u=0) \\
0&(a_u=1)
\end{cases}\\ \\
f_{u,1}&=
\begin{cases}
\sum\limits_{u\to v'}f_{v',1}\dfrac{\prod\limits_{u\to v}(f_{v,0}+f_{v,1})}{f_{v',0}+f_{v',1}}&(a_u=0) \\
\prod\limits_{u\to v}(f_{v,0}+f_{v,1})&(a_u=1)
\end{cases}
\end{aligned}
$$

带一个求逆元是 $\Theta(n\log n)$ 的。当然可以做一个前缀积一个后缀积优化到线性。代码不给了。

---

## 作者：glorious_dream (赞：0)

[洛谷题面](https://www.luogu.com.cn/problem/CF461B)

感觉是非常经典的一道题，最近好像总是见到，今天也算给它做了，发一篇题解来记录一下。

这道题是一道树形 DP 题，设 $f[u][0/1]$ 表示 $u$ 点属于一个无黑点 $/$ 有且仅有一个黑点的联通块时的方案数。我们考虑如何进行转移。

对于 $f[u][1]$，我们考虑如果 $u$ 在一个有且仅有一个黑点的联通块时，对于它的儿子 $v$，有三种情况：

 1. 儿子是不合法的，那么我们需要把儿子和 $u$ 放在一个联通块里，也就是儿子要贴着父亲，对应的贡献是$f[u][1] \times f[v][0]$。
 
 2. 儿子是合法的，那么我们可以从中间断开，对应的贡献是 $f[u][1] \times f[v][1]$。
 
 3. 父亲是不合法的，那么需要把 $u$ 和它的儿子放到一个联通块里，对应的贡献是 $f[u][0] \times f[v][1]$。

所以对于 $f[u][1]$ 的转移就是 $f[u][1] = f[u][1] \times (f[v][0] + f[v][1]) + f[u][0] \times f[v][1]$。

对于 $f[u][0]$，有两种情况：

 1. 父亲不合法的同时，儿子也不合法，那么把父亲和儿子放在一起，对应的贡献是 $f[u][0] \times f[v][0]$。
 
 2. 父亲不合法，但儿子合法，那么就从中间断开，对应的贡献是 $f[u][0] \times f[v][1]$。

所以对于 $f[u][0]$ 的转移就是 $f[u][0] = f[u][0] \times (f[v][0] + f[v][1])$。

初始的状态是 $f[u][color[u]] = 1$，最后的答案如果以 $1$ 为根的话就是 $f[1][1]$。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define drep(a,b,c) for(int a(b) ; a>=(c) ; --a)
#define rep(a,b,c) 	for(int a(b) ; a<=(c) ; ++a)
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch == '-') f=-1 ; ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
inline void print(int x){
	if(x < 0) putchar('-'),x = -x;
	if(x >= 10) print(x / 10);
	putchar(x % 10 + '0');
}
const int M = 2e5+10;
const int mod = 1e9+7;
int n,cnt;
int head[M],col[M];
ll f[M][2];
struct Edge{
	int to,nxt;
}e[M<<1];
inline void add(int u,int v){
	e[++cnt].to = v;
	e[cnt].nxt = head[u];
	head[u] = cnt;
}
void dfs(int u,int fa){
	f[u][col[u]] = 1;
	for(int i(head[u]) ; i ; i=e[i].nxt){
		int v = e[i].to;
		if(v == fa) continue;
		dfs(v,u);
		f[u][1] = f[u][1] * f[v][1] % mod + f[u][1] * f[v][0] % mod + f[u][0] * f[v][1] % mod;
		f[u][0] = f[u][0] * f[v][0] % mod + f[u][0] * f[v][1] % mod;
		f[u][1] %= mod;
		f[u][0] %= mod;
	}
}
signed main(){
	n = read();
	rep(i,2,n){
		int u = read() + 1;
		add(u,i),add(i,u);
	}
	rep(i,1,n) col[i] = read();
	dfs(1,0);
	printf("%lld\n",f[1][1]);
	return 0;
}
```


---

