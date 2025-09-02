# [USTCPC 2025] 图上交互题4 / Constructive Shortest Path

## 题目背景

USTCPC 设置 3s 时限为了使得 python 通过。洛谷改为 1s 时限。

2024 年 12 月 28 日 14:59:50，随着最后一发 E 题的提交出现了 Wrong Answer，小 G 的 EC-Final 比赛结束了。

虽然这道铜牌细节题没有通过，但小 G 还是如愿以偿的获得了银牌。为什么呢？他的队友和他合力砍下了一道金牌题 K，这题非常考验对于最短路算法的理解。

克露丝卡尔酱衷心地希望大家能够对于不同的算法有深刻的理解而非仅仅是背诵，因而出了这道题同样也考验对于最短路算法的理解。

~~小 G 的竞赛生涯还会继续吗？谁知道呢？~~

## 题目描述

给定一个 $n$ 个点，$m$ 条边的**无向图**。第 $i$ 条边 $(u_i,v_i)$ 有一个**未知边权** $a_i$。

对于任何一条**路径**，定义其**代价**如下：设路径为 $(p_0,p_1,...,p_k)$，其中要求 $(p_{i-1},p_i)$ 是无向图中的边，设其为第 $e_i$ 条边。那么路径的代价即为 $\sum\limits_{i=1}^{k} a_{e_i}$。（该路径可以经过重复点和重复边，即 $p$ 和 $e$ 可以包含重复的数）

定义 $f(x,y)$ 为从 $x$ 到 $y$ 的所有路径中代价的**最小值**。特别地，当 $x=y$ 时，$f(x,y)=0$。

给定 $n,m$，再对于每条边 $(u_i,v_i)$ 给定 $f(u_i,v_i)$，你需要求出是否存在一组合法的 $a_i$，如果有解，你还需要构造一组解。

注： $f(x,y)$ 就是最短路径的长度，这么写题面只是为了与该系列其它题目风格类似。

## 说明/提示

![](https://cdn.luogu.com.cn/upload/image_hosting/chqq6le8.png)

考虑 $f(3,1)$：

+ 考虑路径 $3\rightarrow 1$，路径的代价为 $114514$。
+ 考虑路径 $3\rightarrow 1\rightarrow 2\rightarrow 3\rightarrow 1$，路径的代价为 $114514+0+1+114514=114515$。
+ 考虑路径 $3\rightarrow 2\rightarrow 1$，路径的代价为 $1+0=1$。

此外还存在其他路径，但可以证明不存在代价比 $1$ 更小的路径，故 $f(3,1)=1$。

## 样例 #1

### 输入

```
3 3
1 2 0
2 3 1
3 1 1```

### 输出

```
Yes
0 1 114514```

## 样例 #2

### 输入

```
1 1
1 1 114514```

### 输出

```
NO```

# 题解

## 作者：Moonlight_dreams (赞：4)

## [题目](https://www.luogu.com.cn/problem/P12043)

### 代码思路

其实这是一个比较模版的 Floyd 算法的题目。。。

#### 首先，什么是 Floyd

Floyd 就是这是一个图算法，用于求解图中每对顶点之间的最短路径问题。这是一个经典的动态规划算法，用来解决图中任意两个顶点对间最小路径的问题。

#### 解决思路

首先是初始化：

将 $dij$ 数组全部设为无限大，因为我们需要求的是最小路径。然后循环 $n$ 次，每次将 $dij_{i,i}$ 赋值为 1。

接着就是将输入的 $dij_{u , v}$ 和 $dij_{v , u}$ 都设为边权。

接着就是运用 Floyd 算法，计算 $dij$ 数组（计算的公式是 `dij[x][y] = min(dij[x][y] , dij[x][k] + dij[k][y]);`）。

最后就是输出答案。

## AC 代码如下

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 505 , M = 1e5 + 5;
int dij[N][N];
struct stu
{
	int x , y , val;
}s[M];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n , m;
	cin >> n >> m;
	memset(dij , 0x3f , sizeof dij);
	for (int i = 1; i <= n; i++)
	{
		dij[i][i] = 0;
	}
	for (int i = 1; i <= m; i++)
	{
		cin >> s[i].x >> s[i].y >> s[i].val;
		int u = s[i].x , v = s[i].y , w = s[i].val;
		dij[u][v] = dij[v][u] = min(dij[u][v] , w);
	}
	for (int k = 1; k <= n; k++)
	{
		for (int x = 1; x <= n; x++)
		{
			for (int y = 1; y <= n; y++)
			{
				dij[x][y] = min(dij[x][y] , dij[x][k] + dij[k][y]);
			}
		}
	}
	for (int i = 1; i <= m; i++)
	{
		if (dij[s[i].x][s[i].y] < s[i].val)
		{
			cout << "No";
			return 0;
		}
	}
	cout << "Yes" << endl;
	for (int i = 1; i <= m; i++)
	{
		cout << s[i].val << " ";
	}
	return 0;
}
```

---

## 作者：guoshengyu1231 (赞：2)

# 题意
给你一张图中两点之间的最短路，让你构造一张图，如果无法构造，输出`no`。否则输出`yes`，并输出两点之间的边权。
# 思路
首先考虑第一问，我们需要根据最短路判断一张图是否存在。那这就不得不提到图的一个性质，那就是图的最短路满足三角形不等式。 $\\$ 
举个例子：比如我跟你说点 $1$ 到点 $3$ 的最短路距离为 $100$，但我又跟你说点 $1$ 到点 $2$ 的最短路距离和点 $2$ 到点 $3$ 的最短路距离都只有 $1$。那这显然是自相矛盾的，因为点 $1$ 到点 $3$ 的最短路距离完全可以是点 $1$ 到点 $2$ 的最短路距离加上点 $2$ 到点 $3$ 的最短路距离。就好比一个三角形的三条边一样，必须满足任意两边之和必须大于第三边。当然在最短路里等于是可取的。 $\\$ 
所以我们只需要判断是否是这种情况即可。 $\\$ 
那我们该如何判断呢？这个其实很简单，只需要再跑一遍最短路，然后再看看最短路的距离有没有变化即可。 $\\$ 
由于数据范围很小，而且要求的是多源最短路径，很容易联想到 [Floyd 算法](https://cloud.tencent.com/developer/article/2056742)。
 $\\$ 

接下来第二问就非常简单了，因为此时的最短路都是合法的，所以我们直接假设两点的边权就是最短路，这样一定满足图的最短路的三角形不等式。
# 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=505;
const int maxm=100005;
int n,m,x[maxm],y[maxm],c[maxm];
int dp[maxn][maxn];
signed main()
{
	cin>>n>>m;
	memset(dp,0x3f,sizeof dp);
	for(int i=1;i<=n;i++) dp[i][i]=0;
	for(int i=1;i<=m;i++)
	 {
	 	cin>>x[i]>>y[i]>>c[i];
	 	dp[x[i]][y[i]]=dp[y[i]][x[i]]=min(dp[x[i]][y[i]],c[i]);
	 }
	for(int k=1;k<=n;k++)
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++) dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j]);
	for(int i=1;i<=m;i++)
	 {
	 	if(dp[x[i]][y[i]]<c[i])
	 	 {
	 	 	cout<<"no";
	 	 	return 0;
		 }
	 }
	cout<<"yes\n";
	for(int i=1;i<=m;i++) cout<<c[i]<<' ';
	return 0;
}
```

---

## 作者：Vae_L (赞：1)

很无聊的题。

因为所有的边权在求完最短路后都会被松弛掉，所以将两个点之间的最短路当作边权是完全合法的。

如果在将两个点之间的最短路当作边权跑完 Floyd 之后最短路发生了改变也就代表所给的最短路一定可以通过一些方式变得更优，也就无解。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[505][505],m,u[100005],v[100005],w[100005];
int main()
{
    cin>>n>>m;
    memset(a,0x3f,sizeof a);
    for(int i=1;i<=n;i++) a[i][i]=0;
    for(int i=1;i<=m;i++) 
    {
		cin>>u[i]>>v[i]>>w[i];
		a[u[i]][v[i]]=a[v[i]][u[i]]=min(a[u[i]][v[i]],w[i]);
	}
	for(int k=1;k<=n;k++)
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
			}
		}
	}
	for(int i=1;i<=m;i++)
	{
		if(a[u[i]][v[i]]<w[i]) 
		{
			cout<<"No";
			return 0;
		}
	}
	cout<<"Yes\n";
	for(int i=1;i<=m;i++) cout<<w[i]<<" ";
    return 0;
}

---

## 作者：hgckythgcfhk (赞：1)

广告：[USTCPC2025 题解汇总（部分）](https://www.luogu.com.cn/article/xl8dsc9j)。

设 $dis(G,u,v)$ 表示在图 $G$ 上 $u$ 到 $v$ 的最短路，设 $A$ 表示原图，$B=\{(u,v)\in A |(u,v,dis(A,u,v))\}$。

也就是说 $B$ 是 $A$ 的边然后把边权改成最短路后形成的新图。$\forall(u,v)\in A,dis(A,u,v)\le dis(B,u,v)$，感性理解一下，$B$ 里的所有边都是 $A$ 的边组合而来的。

先算出所有 $dis(B,x,y)$，如果有 $dis(B,x,y)<dia(A,x,y)=f(x,y)$ 则一定无解。

根据上述结论，在 $B$ 中一定直接走两个点的边，这样肯定是合法的，也就是是说，先判一下最短路对不对然后直接用输入的东西建边就行。

 以下是线下选手 $42$ 队提供的赛时代码，非常感谢 $42$ 队。

```cpp
#include<iostream>
using namespace std;
typedef long long ll;
const int N=510,M=2e5+10;
const ll inf=1e12;
int n,m;
ll a[M],g[N][N];
bool ans=false;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j)g[i][j]=0;
			else g[i][j]=inf;
		}
	}
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d%d%lld",&u,&v,a+i);
		if(g[u][v]!=inf){
			if(g[u][v]!=a[i])ans=true;
		}
		g[u][v]=g[v][u]=a[i];
	}
	for(int k=1;k<=n;k++){
		if(ans)break;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(g[i][j]==inf)continue;
				if(g[i][k]+g[k][j]<g[i][j]){
					ans=true;
					break;
				}
			}
			if(ans)break;
		}
		if(ans)break;
	}
	if(ans){
		printf("No");
	}else{
		printf("Yes\n");
		for(int i=1;i<=m;i++)printf("%lld ",a[i]);
	}
	return 0;
}
```

---

## 作者：l15130880055 (赞：0)

## [USTCPC 2025] 图上交互题4 / Constructive Shortest Path

### Problem

给你一张图但是不给你边权，只给你图上点间的最短路长度，构造原图的边权。


### 闲话
和之前场切过的一道题 [P11170](https://www.luogu.com.cn/problem/P11170) 很像啊，如果有解答案都是给的那个 $f(u,v)$，但是比那道题简单不少，我来说一下为什么 $f(u,v)$ 一定符合条件的一组答案和如何判断无解。

### Solution
抛开原图不谈，直接把他给这个 $f(u,v)$ 当做 $u$ 和 $v$ 之间的边权建出的新图，新图中的 $u$ 和 $v$ 之间的最短路一定是不大于原图的。

因为题目给的是**最短路**，原图中点间的边权只可能比 $f(u,v)$ 更大，不可能比这个小，所以我们可以理解为新图的边权一定是小于**等于**原图的。

只要满足这个条件就一定有解，上面强调了可以**等于**，所以给定的 $f(u,v)$ 一定是一组解，$n$ 很小直接做 Floyd 即可。

时间复杂度 $O(n^3 + m)$。
### Code


```cpp
constexpr int MX = 510;
int n, m, f[MX][MX], w[MX * MX];
std::vector<std::pair<int, int> > G[MX];
inline void solve() {
	memset(f, 0x3f, sizeof f);
	Fastio::cin >> n >> m;
	for(int i = 1, u, v; i <= m; i++){
		Fastio::cin >> u >> v >> w[i];
		f[u][v] = std::min(f[u][v], w[i]);
		f[v][u] = std::min(f[v][u], w[i]);
		G[u].push_back({v, w[i]});
		G[v].push_back({u, w[i]});
	}
	for(int i = 1; i <= n; i++){
		f[i][i] = 0;
	}
	for(int k = 1; k <= n; k++){
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= n; j++){
				f[i][j] = std::min(f[i][j], f[i][k] + f[k][j]);
			}
		}
	}
	for(int u = 1; u <= n; u++){
		for(auto b : G[u]){
			if(b.second > f[u][b.first]){
				std::cout << "No" << '\n';
				return;
			}
		}
	}
	std::cout << "Yes" << '\n';
	for(int i = 1; i <= m; i++){
		Fastio::cout << w[i] << ' ';
	}
}
```

---

## 作者：Grand_Dawn (赞：0)

来自出题人的题解：

考虑图 $G'(u,v,f(u_i,v_i))$，即根据输入的数据进行建图。

然后考虑新图上的最短路必然有 $d_{G'}(x,y)\ge d_G (x,y)$，因为 $G'$ 中的边都是通过 $G$ 中的边组合而来（有点类似 Bellman-Ford 算法的思想）

因此，我们对于 $G'$ 跑 Floyd 算法求出所有的最短路 $d_{G'}(x,y)$。

如果出现了$d_{G'}(u_i,v_i)<f(u_i,v_i)=d_G (u_i,v_i)$ 则无解。

若不存在以上情况，则可以令 $a_i=f(u_i,v_i)$ 就有 $G'=G$ ，由之前的结论必然不存在 $d_G (u_i,v_i)<a_i$。而由于 $u_i$ 可以直接走 $a_i$ 到达 $v_i$，故有 $d_G (u_i,v_i)\le a_i$。

因此，以上构造有 $d_G (u_i,v_i)=a_i$，符合条件。

时间复杂度 $\Theta(n^3+m)$。

---

## 作者：VinstaG173 (赞：0)

还是诈骗题。

由于最短路满足三角不等式，显然在 $a_i=f(u_i,v_i)$ 的图中求出的最短路不大于原图中的最短路。直接以此为基础用 Floyd 算法求出最短路，若有 $(u_i,v_i)$ 最短路小于 $f(u_i,v_i)$ 则无解，否则此构造即满足题目要求。

时间复杂度 $O(n^3+m)$，空间复杂度 $O(n^2+m)$。谢谢这题让我重新学了一遍怎么写 Floyd。

Code:
```cpp
int n,m,flag;
int u[100003];
int v[100003];
ll w[100003];
ll f[503][503];
inline void solve(){
	cin>>n>>m;flag=1;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			f[i][j]=1e18;
	for(int i=0;i<m;++i){
		cin>>u[i]>>v[i]>>w[i];
		f[u[i]][v[i]]=f[v[i]][u[i]]=min(f[u[i]][v[i]],w[i]);
	}for(int i=1;i<=n;++i)
		f[i][i]=0;
	
	for(int k=1;k<=n;++k)
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
	
	for(int i=0;i<m;++i)
		if(f[u[i]][v[i]]<w[i]){
			flag=0;break;
		}
	
	if(!flag){
		cout<<"No\n";
		return;
	}cout<<"Yes\n";
	for(int i=0;i<m;++i)
		cout<<w[i]<<" ";
}
```

---

