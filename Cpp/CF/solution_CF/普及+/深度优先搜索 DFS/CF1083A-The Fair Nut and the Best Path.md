# The Fair Nut and the Best Path

## 题目描述

The Fair Nut is going to travel to the Tree Country, in which there are $ n $ cities. Most of the land of this country is covered by forest. Furthermore, the local road system forms a tree (connected graph without cycles). Nut wants to rent a car in the city $ u $ and go by a simple path to city $ v $ . He hasn't determined the path, so it's time to do it. Note that chosen path can consist of only one vertex.

A filling station is located in every city. Because of strange law, Nut can buy only $ w_i $ liters of gasoline in the $ i $ -th city. We can assume, that he has infinite money. Each road has a length, and as soon as Nut drives through this road, the amount of gasoline decreases by length. Of course, Nut can't choose a path, which consists of roads, where he runs out of gasoline. He can buy gasoline in every visited city, even in the first and the last.

He also wants to find the maximum amount of gasoline that he can have at the end of the path. Help him: count it.

## 说明/提示

The optimal way in the first example is $ 2 \to 1 \to 3 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1083A/9cde903713bc2c3037de1f95f6d689e21702b992.png)The optimal way in the second example is $ 2 \to 4 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1083A/ba9b6431b860ed0c426ce30e31a270fdf4bfbaf1.png)

## 样例 #1

### 输入

```
3
1 3 3
1 2 2
1 3 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5
6 3 2 5 0
1 2 10
2 3 3
2 4 1
1 5 1
```

### 输出

```
7
```

# 题解

## 作者：JustBlack (赞：8)

### FN and  the Best Path

1. 题意：点有正权，边有负权。在这样的无根树中找到一条权重最大的链并输出权重

2. 想法：显然是树形dp ，dp\[i][0] 表示以 i 为终点的权重最大的路径，dp\[i][1] 表示 i 为中间点的权重最大的路径。所以在树形dp中找到大儿子(max1)和二儿子(max2)，不难得到转移方程：

   - dp\[u][0]=max1+a[u]

   - dp\[u][1]=max1+max2+a[u]

     （记得及时更新答案就ok了）

1. So… 上代码

   ```c++
   // cf: The Fair Nut and the Best Path
   #include <bits/stdc++.h>
   #define lli long long
   #define MAXN 300005
   using namespace std;
   
   struct hp {
   	int to,nxt,w;
   }e[2*MAXN];
   
   int n;
   int a[MAXN];
   lli ans;
   lli dp[MAXN][2];
   int tot;
   int head[MAXN];
   
   void add(int u,int v,int w)
   {
   	tot++;
   	e[tot].to=v;
   	e[tot].w=w;
   	e[tot].nxt=head[u];
   	head[u]=tot;
   }
   
   void dfs(int u,int fa)
   {
   	lli max1=0,max2=0;
   	for(int i=head[u];i;i=e[i].nxt)
   	{
   		int v=e[i].to;
   		if(v==fa) continue;
   		dfs(v,u);
   		if(dp[v][0]-e[i].w>=max1)
   		{
   			max2=max1;
   			max1=dp[v][0]-e[i].w;
   		}
   		else if(dp[v][0]-e[i].w>max2)
   			max2=dp[v][0]-e[i].w;
   	}
   	dp[u][1]=max1+max2+a[u];
   	dp[u][0]=max1+a[u];
   	ans=max(ans,max(dp[u][0],dp[u][1]));
   }
   
   int main()
   {
   	scanf("%d",&n);
   	for(int i=1;i<=n;i++) scanf("%d",a+i);
   	for(int i=1;i<n;i++)
   	{
   		int u,v,w;
   		scanf("%d%d%d",&u,&v,&w);
   		add(u,v,w),add(v,u,w);
   	}
   	dfs(1,0);
   	printf("%lld\n",ans);
   }
   ```

   

---

## 作者：hehelego (赞：6)

正解前面都说过了.这里**给出一个正确性的证明**


首先我们注意到这里路径是**有向**的,即正向反向走不一定同时合法,如果合法,两种方式得到的权值相等.  

$$w_1=1,w_2=11,e(1,2)=10$$

这样就出现了.然后我们注意到这个性质**如果在某处出现了正向反向不同时合法,必定在这里断开为两部分,取原路径的一部分更优秀**.

考虑枚举路径LCA为x,是不是能存在一个子树中的点$v_0$直接从$v_0$的最长链无法走到根而从其他子树中的点$v_x$走到$x$后再进入$v_0$是合法的.但是考虑一下这里的贡献.

我们沿用上一个题解的符号.$dp_v$为$v$结束的子树内最长链.

$w_v$表示$v->x$的边权.

$$dp_{(v_0)}\lt w_{v_0}$$

$$dp_{(v_x)}\geq w_{(v_x)}\quad dp_{(v_x)}-w_{(v_x)}\geq w_{v_0}$$

走到根停止与走到$v_0$中与最长链拼接的答案是

$$dp_{(v_x)}-w_{(v_x)}+c_x$$
$$dp_{(v_x)}-w_{(v_x)}+c_x-w_{v_0}+dp_{(v_0)}$$

显然前者更优秀...不然$v_0$就能走到根了.



---


跨过$x$的路径必然是两端都可以走上$x$的,这个我们选取最长次长最优秀.一条不"分叉"的链我们用$dp_x$,所以这种方法考虑了所有合法且可能是最优解的路径.故是正确的.



---

## 作者：Nicrobot (赞：4)

树形 DP。

首先任意时刻收益值不为负是多余的限制，因为如果路径有一段贡献是负的，那不如把它删掉，结果会更优。

显然树上任意路径 $u \to v$ 都可以转换为 $u \to \text{LCA}(x,y)$ 和 $\text{LCA}(x,y) \to v$ 两部分。对于一个结点 $p$，考虑其子树内结点对的最长路径，则答案为点 $p$ 到其子树内的点路径的值的最大值与次大值之和，统计计算即可。


考虑快速从子节点往转移路径的最值，对于一个子树，它的父亲只需要它到到其子树内的点路径的值的最大值（因为不能重复地走这一棵子树），记录即可。

时间复杂度 $O(n)$。


代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 10;

int n;
int w[N];
long long ans = 0;
long long dp[N];
vector<pair<int, int> > e[N];

void dfs(int now, int fa) {
	long long p1 = 0, p2 = 0;
	for (pair<int, int> tmp : e[now]) {
		int i = tmp.first, c = tmp.second;
		if (i == fa) continue;
		dfs(i, now);
		long long t = dp[i] - c; // 到 i 这棵子树内结点路径的最值 
		if (t > p1) p2 = p1, p1 = t; // 更新总体最值和次大值 
		else if (t > p2) p2 = t;
	}
	dp[now] = p1 + w[now];  // 记录最值方便转移 
	ans = max(ans, p1 + p2 + w[now]);  // 更新答案 
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> w[i];
	}
	for (int i = 1; i < n; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		e[u].push_back({v, w});
		e[v].push_back({u, w});
	}
	dfs(1, 0);
	cout << ans;
	return 0;
}


```

---

## 作者：CRTL_xzh2009 (赞：2)

# 题意
可以将题意转化为：在一棵树上求一条路径（所有点的权值和减去所有边的权值和最大）。

# 分析

可以想到，任何路径 $(u,v)$，都可以拆分为 $(u,LCA(u,v))$ 和 $(LCA(u,v),v)$。

我们可以 $\texttt{DFS}$ 记录每个点 $u$，到其子孙结点的最大费用和 $dp[u][0]$（不包含 $u$ 点）与来自不同子树的次大费用和 $dp[u][1]$（不包含 $u$ 点）。则经过 $u$ 的路径，最大费用就是 $dp[u][0]+dp[u][1]+w[u]$。

别忘了一个特殊情况，经过 $u$ 的路径还有可能是以 $u$ 为端点的。即 $dp[u][0]+w[u]$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define N 600005
int n;
ll a[N],ans=-0x7fffffffffffff;
int nxt[N],to[N],h[N],vis[N],tot;
ll c[N],f1[N],f2[N];
inline void add(int u,int v,ll cost){
	nxt[++tot]=h[u],h[u]=tot,to[tot]=v,c[tot]=cost;
}
void dfs(int u,int fa){
	f1[u]=f2[u]=0;
	for(int i=h[u];i;i=nxt[i]){
		int v=to[i];
		if(v==fa)continue;dfs(v,u);
		if(f1[v]+a[v]-c[i]>f1[u])f2[u]=f1[u],f1[u]=f1[v]-c[i]+a[v];
		else if(f1[v]+a[v]-c[i]>f2[u])f2[u]=f1[v]-c[i]+a[v];
	}	
	ans=max(ans,f1[u]+f2[u]+a[u]);
}
int main(){
	//freopen("path.in","r",stdin);
	//freopen("path.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%lld",a+i);
	}
	for(int i=1;i<=n-1;++i){
		int u,v;
		ll c;
		scanf("%d%d%lld",&u,&v,&c);
		add(u,v,c),add(v,u,c);
	}
	dfs(1,0);
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：ningago (赞：1)

令 $a \to b$ 表示 $a$ 与 $b$ 存在一条无向边，$f[a]$ 表示 $a$ 的父节点，$\mathrm{smax}$ 函数表示求**次大值**。

对于每个节点 $k$ ，我们考虑在 $k$ 的子树里瞎跑，且经过 $k$ 的最大值。

因此可以分出两种情况：

- $dp[k][0]$ 表示以 $k$ 为终点：

由于是树上问题，所以有 $k$ 的每个儿子的子树都互不连通，则如果要到达 $k$ 则只能是 $k$ 的儿子的子树，即 
$$dp[k][0] = w[k]+\max_{k\to nx,nx != f[k] }dp[nx][0]$$

- $dp[k][1]$ 表示以 $k$ 为路径上的中间点：

不难发现，此定义就是从 $k$ 的一个儿子里跑到 $k$ 再跑到另一个儿子。

则有 
$$dp[k][1] = w[k]+\max_{k \to nx,nx != f[k]}dp[nx][0] $$
$$+ \mathrm{smax}_{k \to nx,nx != f[k]}dp[nx][0]$$

（如果从 $dp[nx][1]$ 转移，是不可行的，因为此时 $nx$ 不是终点，而路径的终点是 $nx$ 的其他子树中的点）。

综上所述，

$$\begin{cases}dp[k][0] = w[k]+\max_{k\to nx,nx != f[k] }dp[nx][0]\\dp[k][1] = w[k]+\max_{k \to nx,nx != f[k]}dp[nx][0] \\ \,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,+ \mathrm{smax}_{k \to nx,nx != f[k]}dp[nx][0]\end{cases}$$

Code:
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

#define ll long long
#define N 300010
using namespace std;

ll n;
ll h[N << 1],e[N << 1],w[N << 1],ne[N << 1],idx;
inline void add(ll x,ll y,ll k)
{
	ne[++idx] = h[x];
	e[idx] = y;
	w[idx] = k;
	h[x] = idx;
}
ll c[N],dp[N][2],ans;

void dfs(ll k,ll fa)
{
	ll fi = 0,se = 0;
	//printf("k = %d\n",k);
	for(ll i = h[k];~i;i = ne[i])
	{
		ll nx = e[i];
		if(nx == fa)
			continue;
		dfs(nx,k);
		if(dp[nx][0] - w[i] >= fi)
		{
			se = fi;
			fi = dp[nx][0] - w[i];
		}
		else if(dp[nx][0] - w[i] > se)
		{
			se = dp[nx][0] - w[i];
		}
	}
	dp[k][1] = fi + se + c[k];
	dp[k][0] = fi + c[k];
	ans = max(ans,max(dp[k][1],dp[k][0]));
}

int main()
{
	memset(h,-1,sizeof(h));
	memset(dp,-1,sizeof(dp));
	scanf("%lld",&n);
	for(ll i = 1;i <= n;i++)
		scanf("%lld",&c[i]);
	for(ll i = 1,x,y,z;i < n;i++)
	{
		scanf("%lld%lld%lld",&x,&y,&z);
		add(x,y,z);
		add(y,x,z);
	}
	dfs(1,0);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：_lxy_ (赞：0)

### 题意

给定一棵树，经过边时会损失边权大小的收益，经过点时会增加点权大小的收益。问一条路径的最大收益。

### 分析

很容易想到树形 dp。对于每个点而言，以它作为中转点的最优收益是一条进入它的最优的链的收益加上从它走出的和走入那条链完全没有交点的最优的链的收益。

首先 dfs 一下，$f_u$ 表示到达结点 $u$ 的最大收益，对于子结点 $v$ ，如果 $f_v$ 减去连接 $u,v$ 边的边权为负数，说明不合法。$f_u=a_u+\max(f_v)$ ，其中 $a_u$ 表示 $u$ 的点权，记录从哪里转移的，记为 $p_u$。

然后再 dfs 一遍，$dp_u$ 表示以结点 $u$ 作为中转点的链的最大收益，对于子结点 $v$ ，如果 $f_v$ 减去连接 $u,v$ 的边权再加上 $f_u$ 为负数，说明不合法。$dp_u=f_u+\max(f_v)\ (v \neq p[u])$ 。

最后输出 $\max(dp_i)$ 即可。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define mem(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> Pair;
const int inf=2139062143;
inline void qread(){}template<class T1,class ...T2>
inline void qread(T1 &a,T2&... b)
{
    register T1 x=0;register bool f=false;char ch=getchar();
    while(ch<'0') f|=(ch=='-'),ch=getchar();
    while(ch>='0') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    x=(f?-x:x);a=x;qread(b...);
}
template<class T> T qmax(T x,T y){return x>y?x:y;}
template<class T,class ...Arg> T qmax(T x,T y,Arg ...arg){return qmax(x>y?x:y,arg...);}
template<class T> T qmin(T x,T y){return x<y?x:y;}
template<class T,class ...Arg> T qmin(T x,T y,Arg ...arg){return qmin(x<y?x:y,arg...);}
const int MAXN=3e5+7;
int n,dp[MAXN],a[MAXN],ans,f[MAXN],p[MAXN];
vector<Pair>tree[MAXN];
void dfs(int u,int fa)
{
    int mx=0;f[u]=a[u];
    for(auto v:tree[u])
    {
        if(fa==v.first) continue;
        dfs(v.first,u);
        if(f[v.first]-v.second<0) continue; // 只要路径上一个时刻的收益为负数就不合法
        if(f[v.first]-v.second>mx)
        {
            mx=f[v.first]-v.second; // 更新f值
            p[u]=v.first; // 记录路径
        }
    }f[u]+=mx;
}
void dfs1(int u,int fa)
{
    int mx=0;dp[u]=f[u];
    for(auto v:tree[u])
    {
        if(fa==v.first) continue;
        dfs1(v.first,u);
        if(v.first==p[u]) continue; // 不能走回头路
        if(f[u]+f[v.first]-v.second<0) continue; // 不合法
        mx=qmax(mx,f[v.first]-v.second);
    }dp[u]+=mx;
}
signed main()
{
    qread(n);int i,j;for(i=1;i<=n;i++) qread(a[i]);
    for(i=0;i<n-1;i++)
    {
        int u,v,w;qread(u,v,w);
        tree[u].push_back(Pair(v,w));
        tree[v].push_back(Pair(u,w));
    }dfs(1,-1);dfs1(1,-1);
    for(i=1;i<=n;i++) ans=qmax(ans,dp[i]);printf("%lld\n",ans);
    return 0;
}
```

---

