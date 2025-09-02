# [ABC243E] Edge Deletion

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc243/tasks/abc243_e

$ N $ 頂点 $ M $ 辺の単純連結無向グラフが与えられます。  
 辺 $ i $ は頂点 $ A_i $ と頂点 $ B_i $ を結ぶ長さ $ C_i $ の辺です。

以下の条件を満たすようにいくつかの辺を削除します。削除する辺の数の最大値を求めてください。

- 辺を削除した後のグラフも連結である。
- 全ての頂点対 $ (s,t) $ について、頂点 $ s $ と頂点 $ t $ の間の距離が削除前と削除後で変化しない。

## 说明/提示

### 注釈

単純連結無向グラフとは、単純かつ連結で辺に向きの無いグラフのことをいいます。  
 グラフが単純であるとは、グラフが自己ループや多重辺を含まないことをいいます。  
 グラフが連結であるとは、グラフ上の任意の $ 2 $ 頂点 $ s,\ t $ について $ s $ から $ t $ へ辺をたどって行けることをいいます。  
 頂点 $ s $ と頂点 $ t $ の間の距離とは、頂点 $ s $ と頂点 $ t $ の間の最短路の長さのことをいいます。

### 制約

- $ 2\ \leq\ N\ \leq\ 300 $
- $ N-1\ \leq\ M\ \leq\ \frac{N(N-1)}{2} $
- $ 1\ \leq\ A_i\ \lt\ B_i\ \leq\ N $
- $ 1\ \leq\ C_i\ \leq\ 10^9 $
- $ i\ \neq\ j $ ならば $ (A_i,\ B_i)\ \neq\ (A_j,\ B_j) $ である。
- 与えられるグラフは連結である。
- 入力はすべて整数である。

### Sample Explanation 1

辺を削除する前の全ての頂点対の距離は次の通りです。 - 頂点 $ 1 $ と頂点 $ 2 $ の距離は $ 2 $ - 頂点 $ 1 $ と頂点 $ 3 $ の距離は $ 5 $ - 頂点 $ 2 $ と頂点 $ 3 $ の距離は $ 3 $ 辺 $ 3 $ を削除しても全ての頂点間の距離は変化しません。また、問題文の条件を満たすように $ 2 $ 本以上の辺を削除することはできないので、答えは $ 1 $ 本になります。

### Sample Explanation 2

どの辺も削除することができません。

## 样例 #1

### 输入

```
3 3
1 2 2
2 3 3
1 3 6```

### 输出

```
1```

## 样例 #2

### 输入

```
5 4
1 3 3
2 3 9
3 5 3
4 5 3```

### 输出

```
0```

## 样例 #3

### 输入

```
5 10
1 2 71
1 3 9
1 4 82
1 5 64
2 3 22
2 4 99
2 5 1
3 4 24
3 5 18
4 5 10```

### 输出

```
5```

# 题解

## 作者：Rigel (赞：15)

## 思路

先求出任意两点间的最短路长度。由于 $N\leq 300$，考虑使用 Floyd。在松弛 $i$、$j$ 之间路径同时，判断新旧路径长度是否相等。若是，则将 $f_{i,j}$ 标记为 $1$，表示 $i$、$j$ 之间有多条最短路。

最后对于每条边（起点为 $u$，终点为 $v$，边权为 $w$），判断：

- $f_{u,v}$ 是否为 $1$。

- $u$、$v$ 之间的最短路长度是否大于 $w$。

若满足任一条件，则 $ans \leftarrow ans+1$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define maxn 310
#define maxm 45010
using namespace std;
int n,m,a[maxn][maxn],f[maxn][maxn],ans;
struct edge{
	int u,v,w;
}e[maxm];
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')ret=ret*10+(ch&15),ch=getchar();
	return ret*f;
}
signed main(){
	memset(a,0x3f,sizeof(a));
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		a[u][v]=a[v][u]=w;
		e[i]=(edge){u,v,w};
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(i==j||i==k||k==j)continue;
				int nw=a[i][k]+a[k][j];
				if(nw==a[i][j])f[i][j]=1;
				if(nw<a[i][j])a[i][j]=nw;
			}
		}
	}
	for(int i=1;i<=m;i++){
		int u=e[i].u,v=e[i].v,w=e[i].w;
		ans+=(a[u][v]!=w||f[u][v]);
	}
	printf("%lld\n",ans);
	return 0;
}

---

## 作者：ikunTLE (赞：11)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc243_e)

### 思路

假设我们要删除 $u\to v$ 这条边，若可以删除，必然存在 $u\to k\to v$ 的长度更短。

不难发现，这一点与 Floyd 的思想非常接近。我们可以用 $f_{i,j}$ 统计最短路的基础上，用 $g_{i,j}$ 表示 $i\to j$ 是否有多条最短路。最后统计出每条边是否满足可以删除的条件即可。

时间复杂度 $\mathcal{O}(N^3)$，可以通过此题。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=3e2+10,M=5e4+10;
int f[N][N];
bool g[N][N];
struct node{
	int u,v,w;
}a[M];
int main(){
	int n=read(),m=read();
	memset(f,0x3f,sizeof(f));
	for(int i=1;i<=m;++i){
		int u=read(),v=read(),w=read();
		f[u][v]=f[v][u]=w,a[i]={u,v,w};
	}
	for(int k=1;k<=n;++k)
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j){
				if(i==j||i==k||k==j)
					continue;
				if(f[i][j]==f[i][k]+f[k][j])
					g[i][j]=true;
				f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
			}
	for(int k=1;k<=n;++k)
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j){
				if(i==j||i==k||k==j)
					continue;
				if(f[i][j]==f[i][k]+f[k][j])
					g[i][j]=true;
				f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
			}
	int sum=0;
	for(int i=1;i<=m;++i)
		if(g[a[i].u][a[i].v]||f[a[i].u][a[i].v]!=a[i].w)
			++sum;
	printf("%d\n",sum);
	return 0;
}
```

---

## 作者：Zyh_AKer (赞：11)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc243_e)
## 题意  
给你一张无重边无自环的联通带权无向图，  
定义 $d(i,j)$ 是 $i$ 到 $j$ 的最短路径上的边权之和。  
你需要删除一些边。要求删完之后的图满足下列条件：  
* 图仍然联通；
* 对于 $1 \le i,j \le N$，删边前的 $d(i,j)$ **等于**删边后的 $d(i,j)$  
现在问你最多能删多少条边。  
数据保证：  
* $2 \le N \le 300$
* $N-1 \le M \le  \displaystyle \frac{N(N−1)}{2} $
* $1 \le u < v \le N$
* $1 \le w \le 10^9$
* 图是联通的，没有重边和自环。
## 思路
我们可以发现，如果 $u \to v$ 可以被删去，那么肯定有另一个 $k$ 可以构成 $u \to k \to v$，并且$u \to k \to v$ 的长度 $\le$ $u \to v$ 的长度，也就是说 $u \to v$ 这条边的边权并不是点 u 到点 v 的最短路或点 u 到点 v 不止一条最短路，这时，我们就可以删去 $u \to v$ 这条边。  
我们可以直接跑 floyd 算出全源最短路，算出每个 $d(i,j)$   
时间复杂度：$O(n^3)$。
## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=305,M=50000;
int n,m,ans;
long long g[N][N];
struct node{
	int u,v;
	long long w;
}a[M];
bool d[N][N];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>m;
	memset(g,0x3f3f3f3f,sizeof(g));
	for (int i=1;i<=n;i++)
	{
		g[i][i]=0;
	}
	for (int i=1;i<=m;i++)
	{
		cin>>a[i].u>>a[i].v>>a[i].w;
		g[a[i].u][a[i].v]=a[i].w;
		g[a[i].v][a[i].u]=a[i].w;
	}
	for (int k=1;k<=n;k++)
	{
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=n;j++)
			{
				if (g[i][j]==(g[i][k]+g[k][j]) && i!=k && k!=j)//如果有多条最短路，d[i][j]=true。
				{
					d[i][j]=true;
				}
				g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
			}
		}
	}
	for (int i=1;i<=m;i++)
	{
		if (g[a[i].u][a[i].v]!=a[i].w || d[a[i].u][a[i].v])
		{
			ans++;
		}
	}
	cout<<ans;
	return 0;
}
```
求过。

---

## 作者：mysterys (赞：5)

# 题目大意
-  给定一张无重边无自环无向图。
-  求出它的全源最短路。
-  问最多删除多少条边，使删除后所有点到其他点的最短路不变。
# 思路
1.  考虑 Floyd 思想：一条边是否可以被另外两条边替代？
 1. 如果可以，那么意味着这一条边可以删除。
 1. 如果不可以，则反之。
 1. 可以用一点点的逆向思维：统计出不可以删的边，用总边数减去不可以删的边，剩下的即为所求。
# 注意事项
- $1\ \leq\ C_i\ \leq\ 10^9$，所以需要开 ```long long```。
- $2\ \leq\ N\ \leq\ 300 $，所以最短路只需要 Floyd 即可。
- 统计答案时要注意自环。
- 因为是无向图，所以统计出的答案需要除以二。
- 有玄学原因会使答案为负数，所以要特判。当然，如果有大佬知道为什么，可以私信蒟蒻。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,ans;
int dis[305][305];//邻接矩阵存图。
bool f;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i!=j) dis[i][j]=1e9;
		}
	}
	for(int i=1;i<=m;i++){
		int u,v,d;
		cin>>u>>v>>d;
		dis[u][v]=d;
		dis[v][u]=d;
	}//无向图，双向建边。
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
			}
		}
	}//Floyd。
	for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
        	if(i==j) continue;//排除自环。
        	f=1;
            for(int k=1;k<=n;k++){
                if(i!=k&&j!=k&&dis[i][j]==dis[i][k]+dis[k][j]){
                    f=0;
                    break;//只要找到一个点满足即可。
                }
            }
            ans+=f;
        }
    }
    ans/=2;//无向图，结果要除以二。
    cout<<(m-ans>0?m-ans:0);//特判
	return 0;
}
```
蒟蒻的第一篇题解，求过qwq。

---

## 作者：hellolin (赞：4)

[题面(洛谷)](https://www.luogu.com.cn/problem/AT_abc243_e)

[题面(AtCoder)](https://atcoder.jp/contests/abc243/tasks/abc243_e)

AtCoder Problems 评级难度：$\texttt{\color{#337dff}1637}$

**UPD1**: 补充了结论的说明，使代码更易读。

## 题意

- 给你一张无重边无自环的联通带权无向图。
- 定义 $d(i,j)$ 是 $i$ 到 $j$ 的最短路径上的边权之和。
- 你需要删除一些边。要求删完之后的图满足下列条件：
  - 图仍然联通；
  - 对于 $1\le i,j\le N$，删边前的 $d(i,j)$ **等于**删边后的 $d(i,j)$。
- 现在问你最多能删多少条边。
- 数据保证：
  - $2\le N\le 300,\ N-1\le M\le \frac{N(N-1)}{2}$。
  - $1\le u< v\le N,\ 1\le w\le 10^9$。
  - 图是联通的，没有重边和自环。

## 思路

思路很简洁，先跑一遍最短路，$N\le 300$，所以用 Floyd 就行了。

对于每一个点对 $(i,j)$ 满足 $1\le i,j\le N,\ i\not = j$，如果能够找到一个新的点 $k$ 满足 $1\le k\le N,\ i\not = k,\ j\not =k$ 且 $d(i,j)=d(i,k)+d(k,j)$ 说明这一条边是可以删去的。

注意无向图记录的 $\mathrm{ans}$ 要除以二。

## 代码

``` cpp
#include <bits/stdc++.h>
// #include <atcoder/all>
using namespace std;
#define int long long
const static int N=500,INF=1e18+114514;
int n,m,u,v,w;
int gra[N][N],ans;
bool f;
inline void solve()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(i!=j)gra[i][j]=INF;
    for(int i=1;i<=m;i++)
    {
        cin>>u>>v>>w;
        gra[u][v]=w;
        gra[v][u]=w;
    }
    for(int k=1;k<=n;k++)for(int i=1;i<=n;i++)for(int j=1;j<=n;j++) // Floyd
        gra[i][j]=min(gra[i][j],gra[i][k]+gra[k][j]);
    ans=0; // 记录不可以删的边
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(i!=j)
            {
                f=0;
                for(int k=1;k<=n;k++)
                {
                    if(i!=k&&j!=k)
                    {
                        if(gra[i][j]==gra[i][k]+gra[k][j]) // 如果这个条件成立说明这条边可以删除
                        {
                            f=1;
                            break; // 至少有一个 k 点满足条件就可以跳出了
                        }
                    }
                }
                ans+=!f;
            }
        }
    }
    ans/=2; // 无向图，结果要除以二
    cout<<m-ans<<endl;
}
#undef int
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}
```

---

## 作者：sherry_lover (赞：3)

# AT_abc243_e [ABC243E] Edge Deletion 题解
[题目传送门](https://www.luogu.com.cn/problem/AT_abc243_e)

其实很多题解都讲得很详细了，这里就再补充一点做法。

容易发现，要满足删边前的 $d(i,j)$ 等于删边后的 $d(i,j)$，那么 $i$ 到 $j$ 一定有多条最短路。

所以我们在用 floyd 求最短路需要更新的时候，就可以判断 $f_{x,y}$ 是否等于 $f_{x,k}+f_{k,y}$，注意 $x,y$ 不等于 $k$。

最后遍历每条边求答案，注意如果这条边两端点的最短路不等于这条边的长度时，这条边可以删去，也要加入答案中。

------------
Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
long long f[305][305],ans,w[90005];
pair<int,int> b[90005];
bool vis[305][305];
int main()
{
	memset(f,0x3f3f,sizeof(f));
	cin >> n >> m;
	for(int i = 1;i <= n;i++) f[i][i] = 0;
	for(int i = 1,u,v,k;i <= m;i++)
	{
		cin >> u >> v >> k;
		b[i] = {u,v};
		w[i] = k;
		f[u][v] = k;
		f[v][u] = k;
	}
	for(int k = 1;k <= n;k++)
	{
  		for(int x = 1;x <= n;x++)
		{
    		for(int y = 1;y <= n;y++)
			{
				if(f[x][y] == f[x][k]+f[k][y] && k != x && k != y) vis[x][y] = 1;
      			f[x][y] = min(f[x][y],f[x][k]+f[k][y]);
    		}
  		}
	}
	for(int i = 1;i <= m;i++)
	{
		int u = b[i].first,v = b[i].second;
		ans += (f[u][v] != w[i] || vis[u][v]);
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Atserckcn (赞：3)

## [[ABC243E] Edge Deletion](https://www.luogu.com.cn/problem/AT_abc243_e) 题解

### 题目简述：

给定一张无重边无自环的联通带权无向图，需删除若干条边，使得删去后的图满足以下条件：

+ 图是连通图；

+ $\forall\ i,j \ \in M$，其最短路径不变。

求最多能删除几条边。

### 数据范围：

+ $2\le N \le 300$

+ $N-1\le M\le \frac{N(N-1)}{2}$

+ $1\le u \le v \le N$

+ $1\le w \le 10^9$ 注意：不开 `long long` 见祖宗。

### 思路简述

因为题目要求是不影响任意两点之间的最短路径，所以我们可以一次性求出所有点的最短路径，用 Floyd 算法求，时间复杂度 $O(N^3)$​。

我们发现，若有一条 $u\rightarrow v$ 的边能够删去，则必定会有一个点 $k$，满足 $u\rightarrow k\rightarrow v \le u\rightarrow v$。

若删去该边后，不影响最短路径长度（等于也算），则该边可删去。

在此基础上，定义一个数组，用来统计两点间的这条边是否可以删去。

其余的，就按照基本的最短路代码求吧。

特别，因为 $w\le 10^9$，记得开 `long long`。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m,ans;
ll u,v,w;
const ll MAXN=305,MAXM=90005,inf=1e18+5;
ll g[MAXN][MAXN];//邻接表存图
bool vis[MAXN][MAXN];
struct EDGE{//结构体存图
	ll from,to,w;
}edge[MAXM];
int main(){
	scanf("%lld%lld",&n,&m);
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=n;j++)
			if(i!=j)
				g[i][j]=inf;//初始化
	for(ll i=1;i<=m;i++)
	{
		scanf("%lld%lld%lld",&edge[i].from,&edge[i].to,&edge[i].w);
        //虽然题目保证没有重边，但是判断是个好习惯
		g[edge[i].from][edge[i].to]=min(g[edge[i].from][edge[i].to],edge[i].w);
		g[edge[i].to][edge[i].from]=min(g[edge[i].to][edge[i].from],edge[i].w);
	}
	for(ll k=1;k<=n;k++)
	{
		for(ll i=1;i<=n;i++)
		{
			for(ll j=1;j<=n;j++)
			{
				if(j!=k&&i!=k&&g[i][j]==g[i][k]+g[k][j])//这条边已经确认可以删去
					vis[i][j]=true;
				if(g[i][j]>g[i][k]+g[k][j])//正常的松弛
					g[i][j]=g[i][k]+g[k][j];
			}	
		}	
	}
	for(ll i=1;i<=m;i++)
		if(vis[edge[i].from][edge[i].to]||g[edge[i].from][edge[i].to]!=edge[i].w)
			ans++;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：I_LOVE_MATH (赞：2)

### 题目大意

给出一个无向连通图，在保证任两点最短路 $d(u,v)$ 不变的情况下，最多能删多少边。

### 解题思路

考虑一条边满足什么条件可以删。

给出结论：**当 $d(u,v) \le w$ 且 $d(u,v)$ 所代表的路径不经过 $(u,v)$ 时，可以删去边 $(u,v)$**。

证明：当 $d(u,v) \le w$ 时，如果有两点之间的最短路要从 $u$ 到 $v$，那么走 $d(u,v)$ 所代表的路径一定不劣，因此任意两点最短路一定可以不走 $(u,v)$，此边可以删去。

现在考虑如何实现算法，观察到数据范围： $n\le 300$，考虑使用 Floyd 算法。

- 当 $d(u,v) < w$ 时，只需用 Floyd 计算两点间最短路再判断大小即可。
- 当 $d(u,v) = w$ 且 $d(u,v)$ 所代表的路径不经过 $(u,v)$ 时，由于此时 $d(u,v) = w$ ，在 Floyd 松弛时如果发现松弛后与当前最短路相等（且 $k$ 与 $i$、$j$ 不相等），用一个布尔数组记录这两点间最短路不唯一即可。

### 代码

```cpp
#include<bits/stdc++.h>
#define endl "\n"
#define ll long long
using namespace std;

const int N = 310, M = 1e5 + 10;

struct edge
{
	int u, v;
	ll w;
} e[M];

int n, m, ans;
ll dis[N][N];
bool b[N][N];

int main()
{
	ios :: sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	memset(dis, 0x3f, sizeof dis);
	for (int i = 1; i <= m; i++)
	{
		cin >> e[i].u >> e[i].v >> e[i].w;
		dis[e[i].u][e[i].v] = dis[e[i].v][e[i].u] = e[i].w;
	}
	for (int k = 1; k <= n; k++)
	{
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if (dis[i][j] == dis[i][k] + dis[k][j] && i != k && j != k)
				{
					b[i][j] = 1;
				}
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
			}
		}
	}
	for (int i = 1; i <= m; i++)
	{
		if (b[e[i].u][e[i].v] == 1 || dis[e[i].u][e[i].v] < e[i].w)
		{
			ans++;
		}
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：zxdjmq (赞：2)

# ABC243E Edge Deletion

## 题意：

一张简单联通带权无向图，询问最多删多少边能保证任意两点间最短路长度不变。$N\le 300$。

## 解法：

看到数据范围就猜到是 Floyd 了，问题在如何用 Floyd 解。

一个显而易见的结论：一条边可以被删除仅当有另外一条联通两点的路径长度小于等于该边。因为另外一条路径可以作为这两点的最短路，经过这两点的最短路也可以走这条更短的路径，所以这条边没有必要存在。

然后改一下 Floyd 板子就可以了。

**Code**:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=305,inf=1e16;
ll n,m;
ll e[N][N],dis[N][N];
bool vis[N][N];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    //初始化Floyd
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            dis[i][j]=inf;
    for(int i=1;i<=n;i++)dis[i][i]=0;
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        dis[u][v]=dis[v][u]=e[u][v]=e[v][u]=w;
    }
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            if(i==k)continue;
            for(int j=1;j<=n;j++){
                if(j==k || i==j)continue;
                if(dis[i][k]+dis[k][j]<=dis[i][j] && e[i][j])vis[i][j]=vis[j][i]=1;//如果存在i-j的边且这条边不是唯一最优，标记其可以删除。
                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            if(vis[i][j])ans++;
    cout<<ans;
    return 0;
}
```

---

## 作者：SunburstFan (赞：2)

### E - Edge Deletion 

#### 题目大意

有一张有 $N$ 个顶点，有 $M$ 条边的带边权无向图，问能删多少条边，使得每两点之间的最短路长度不变。

#### 解题思路

注意到这道题中 $N$ 的范围很小，考虑 floyd 求全源最短路，再松弛边的时候，如果松弛的边距离与当前最短路长度相等，那么显然这条边时可以删去的。

```cpp
for(int k=1;k<=n;k++)
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            if(low[i][j]==low[i][k]+low[k][j]&&i!=k&&j!=k){ //如果距离相等
                f[i][j]=1;
            }

            low[i][j]=min(low[i][j],low[i][k]+low[k][j]);
        }

for(int i=1;i<=m;i++){
    //有两种情况可以删边：前面记录的状态可以删去；当前两点之间最短路不经过这条边
    if(f[e[i].u][e[i].v]||low[e[i].u][e[i].v]!=e[i].d){
        ans++;
    }
}    

cout<<ans<<"\n";

```

---

## 作者：Lan_yan (赞：2)

算法显然用 Floyd。对于我这种蒟蒻来说，Dijstra 和 SPFA 不会运用，也没得选了。

一共只有两种情况可以删边，一是在进行松弛操作时 $dis$ 数组刚好松弛后还是原来的样子。

```dis[i][j]==dis[i][k]+dis[k][j];```

同时注意 $i$ 和 $j$ 与 $k$ 不相等。

二是在完成全源最短路后 $dis$ 数组与最初连边时不一样，即有更优路线。

所以这条路线可以被忽略，删除。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,dis[305][305],ans=0,op[305][305],u[90005],v[90005],d[90005];
int main()
{
	int i,j,k;
	scanf("%d%d",&n,&m);
	memset(dis,0x3f3f3f3f,sizeof(dis));
	for(i=1;i<=m;i++)
	{
		scanf("%d%d%d",&u[i],&v[i],&d[i]);
		dis[u[i]][v[i]]=d[i];dis[v[i]][u[i]]=d[i];
	}
	for(i=1;i<=n;i++)dis[i][i]=0;
	for(k=1;k<=n;k++)
	{
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=n;j++)
			{
				if(dis[i][j]==dis[i][k]+dis[k][j]&&i!=k&&j!=k)op[i][j]=1;
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
			}
		}
	}
	for(i=1;i<=m;i++)
	{
		if(op[u[i]][v[i]]||dis[u[i]][v[i]]!=d[i])ans++;
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：b2314huangruizhong (赞：2)

## 题目大意 ##

有一个带权无向图（无重边无自环）。

设 $i$ 点到 $j$ 点的最短路经为 $ d(i,j) $。

现在要删掉一些边，让图满足：

+ 图依然联通。

+ 对于 $1\le i,j \le N$，删边前的 $d(i,j)$ **等于**删边后的 $d(i,j)$。

问你最多能删几条边。

数据范围：

- $2\le N\le 300$
- $N-1\le M\le \frac{N(N-1)}{2}$
- $1\le u< v\le N$
- $1\le w\le 10^9$
- 图是联通的，没有重边和自环。

# 思路 #

如果一条边 $u\to v$ 能被删除，那就说明，一定存在一个比它更短的路径 $u\to k\to v$，所以边 $u\to v$ 才能删除。

只要原来的边 $u\to v$ 的边权比 $d(u,v)$ 小，那就说明这条边可以删除。

用 floyd 算法跑出所有 $d(i,j)$。

由于 $1\le w\le 10^9$，记得开 `long long`。

复杂度 $O(N^3)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=305;
int n,m,ans;
long long g[N][N];//用邻接矩阵存图
bool d[N][N];
struct node{
	int u,v;
	long long w;//不开long long见祖宗
}a[N*N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);//关流，读入加速
	cin>>n>>m;
	memset(g,0x3f3f3f3f,sizeof(g));//long long时占64b，是int的两倍
	for(int i=1;i<=n;i++)g[i][i]=0;
	for(int i=1;i<=m;i++){
		cin>>a[i].u>>a[i].v>>a[i].w;
		g[a[i].u][a[i].v]=g[a[i].v][a[i].u]=a[i].w;}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++){
				if(g[i][j]==(g[i][k]+g[k][j])&&i!=k&&k!=j)d[i][j]=true;//如果有多条最短路，d[i][j]=true
				g[i][j]=min(g[i][j],g[i][k]+g[k][j]);}
	for(int i=1;i<=m;i++)
		if(g[a[i].u][a[i].v]!=a[i].w||d[a[i].u][a[i].v])ans++;//统计答案
	cout<<ans;
	return 0;}//完结撒花
```

点个赞吧。

---

## 作者：moziqian (赞：1)

其实不难。

首先，简单地判断需要删去的边满足的条件：

将第 $i$ 条边两端点记作 $a_i, b_i$，边权为 $c_i$，当 $a_i$ 到 $b_i$ 的路径中存在小于 $c_i$ 的情况（可以发现这条路径不是第 $i$ 条边），一定能删除该边，因为任何经过该边的路径中必须经过这两个端点，而这两个端点又有更短的路径，因此这条路径一定不是最短路。

当路径中存在有长度不等于 1 的路径等于 $c_i$ 的情况，也能删除该边，同理。

其次，基于原图删边，要是每次删边后都符合要求，删边是否有冲突？

不会，因为任意两点间的最短路在删边前后不变，满足【条件】的依然满足，否则还是不满足。
 
 剩下的边都是被保留的边，因为他们至少会被自己使用。

 因此得解，用 floyd 预处理两点间的最短路，然后对于每条边判断是否能删，也就是是否有长度不为 1 的路径小于或等于该边。
 
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=305,maxm=1e5+5,inf=1e18;
int n,m,u[maxm],v[maxm],w[maxm],f[maxn][maxn],unused;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            f[i][j]=inf;// 避免特判，当 i=j 时也取 inf
        }
    }
    for(int i=1;i<=m;i++){
        cin>>u[i]>>v[i]>>w[i];
        f[u[i]][v[i]]=w[i];
        f[v[i]][u[i]]=w[i];
    }
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
            }
        }
    }
    int ans=0;
    for(int i=1;i<=m;i++){
        int a=u[i],b=v[i],c=w[i];
        unused=0;
        for(int j=1;j<=n;j++){
            if(f[a][j]+f[j][b]<=c){
            	unused=1;// 因为 i=j 时取了 inf，所以这句话的用意在判断长度至少为 2 的边
            	break;
			}
        }
        ans+=unused;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：Merge_all (赞：1)

根据数据范围一眼 Floyd。

先跑一遍求出所有点对的距离。

考虑输入的每一条边：如果找到一个中转点 $k$ 使得从端点 $a$ 走到 $k$ 再走到 $b$ 的距离和 $dist_{a, b}$ 相同，则可以删掉这条边。

---

## 作者：Tairitempest (赞：1)

## [ABC243E] Edge Deletion
最短路可以使用 Floyd 解决。

（Floyd 算法友情链接：https://oiwiki.com/graph/shortest-path/#floyd-%E7%AE%97%E6%B3%95 ）

然后你会发现，如果在做 Floyd 过程中用两条短边替代了一条长边，那么这条长边就不再需要了，因为可以直接走这两条短边。同样的。如果两条短边和一条长边效果相同，那么这条长边就不再需要了，因为可以直接走这两条短边。这样的话用邻接矩阵记录有的边，跑一遍 Floyd 然后记录剩下的边的数量，就可以算出删除的边的数量。

复杂度 $O(n^3)$。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m,u,v,w,ans;
ll dis[310][310];
bool sign[310][310];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			dis[i][j]=1e18;
	for(int i=1;i<=m;i++){
		cin>>u>>v>>w;
		dis[u][v]=dis[v][u]=w;
		sign[u][v]=sign[v][u]=true;
	}
	
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(dis[i][j]>=dis[i][k]+dis[k][j]){
					dis[i][j]=dis[i][k]+dis[k][j];
					dis[j][i]=dis[i][k]+dis[k][j];
					sign[i][j]=sign[j][i]=false;
				}
			}
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(sign[i][j]) ans++;
	cout<<m-ans/2<<endl;
	return 0;
}
```

---

## 作者：DragonForge (赞：1)

# AT_abc243_e [ABC243E] Edge Deletion

[题目传送门](https://www.luogu.com.cn/problem/AT_abc243_e)

## 题目有效信息
给你一张无重边无自环的连通带权无向图。

定义 $d(i,j)$ 是 $i$ 到 $j$ 的最短路径上的边权之和。

你需要删除一些边。要求删完之后的图满足下列条件：

图仍然联通。

对于 $1 \le i,j \le N$，删边前的 $d(i,j)$ 等于删边后的 $d(i,j)$。

现在问你最多能删多少条边。

数据保证：
- $ 2 \leq N \leq 300 $
- $ N-1 \leq M \leq \frac{N(N-1)}{2} $
- $ 1 \leq A_i \lt B_i \leq N $
- $ 1 \leq C_i \leq 10^9 $
- 图是联通的，没有重边和自环。

## 分析
根据题目描述，本题需要实现的是一个最短路的代码。由于要求的有关所有点之间的最短路以及 $2 \leq N \leq 300$，我们可以大胆的尝试使用 `Floyd` 算法。

---
这时，我们想到如果 $i \to j$ 这条边是要删除的边，那么存在一个点 `k`，使得 $i \to k$ 与 $k \to j$ 的两条边的边权和为会 $\le i \to j$ 的边权。

---
分析完这些，代码也应该能打的出来了。但是需要注意一点：十年 OI 一场空，不开 `longlong` 见祖宗。
[提交记录](https://www.luogu.com.cn/record/181812302)

Code：

```cpp
#include<bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN=310;
const int MAXM=50010;

struct node{
	int u,v;
	int w;
}e[MAXM];

int n,m,ans;
int f[MAXN][MAXN];
bool d[MAXN][MAXN];

signed main(){
	cin>>n>>m;
	for(int i=0;i<=n;i++){
		for(int j=0;j<=n;j++){
			f[i][j]=0x3f3f3f3f3f3f3f3fll;
		}
	}
	for(int i=1;i<=n;i++){
		f[i][i]=0;
	}
	for(int i=1;i<=m;i++){
		cin>>e[i].u>>e[i].v>>e[i].w;
		f[e[i].u][e[i].v]=e[i].w;
		f[e[i].v][e[i].u]=e[i].w;
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(f[i][j]==(f[i][k]+f[k][j]) && i!=k && k!=j){
					d[i][j]=true;
				}
				f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
			}
		}
	}
	for(int i=1;i<=m;i++){
		if(f[e[i].u][e[i].v]!=e[i].w||d[e[i].u][e[i].v]){
			ans++;
		}
	}
	cout<<ans;
	return 0;
}
```
### 完结散花！
（求过）

---

## 作者：O_v_O (赞：1)

# abc_243 E Edge Deletion

## 题意

给定一个 $n$ 个顶点 $m$ 条边的无向简单图，你需要求出最大删除的边的数量，使得任意两个点 $s$、$t$，他们之间的最短距离不变。

## 数据范围

- $2 \le N \le 300$
- $N - 1 \le M \le \frac{N(N-1)}{2}$
- $1 \le A_i \le B_i \le N$
- $C_i \le 10^9$

## 思路

我们可以发现 $N \le 300$ ，而题目要让删除的边对于任意两个点的最短距离都不变，所以我们可以跑一遍 Floyd，将每两个点的最短距离给跑出来，然后判断每一条边，他是否影响 $s$ 到 $t$ 的最短路，如果不影响，我们就让答案加 $1$。最后要让答案除 $2$，因为这是无向图，会重复计算。

这里还有个问题，如果按我们上面的方法，会出现负数情况，为什么呢？答案就是边数小于点数，这样的图会变成一棵树，任何一条边都不能删去。

## *ac code*

```cpp
#include<bits/stdc++.h>

using namespace std;
const int N = 310;

int n, m, ans;
long long dis[N][N]; // 记得开 long long

int main() {
  cin >> n >> m;
  if (m < n) { // 特判，如果边小于点数输出 0
    cout << 0;
    return 0;
  }
  for (int i = 1; i <= n; i++) { // 初始化
    for (int j = 1; j <= n; j++) {
      if (i != j) {
        dis[i][j] = 1e9;
      }
    }
  }
  for (int i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    dis[x][y] = dis[y][x] = z;
  }
  for (int k = 1; k <= n; k++) { // Floyd
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) { // 枚举边
      if (i == j) {
        continue;
      }
      bool f = 1;
      for (int k = 1; k <= n; k++) {
        if (i != k && j != k && dis[i][j] == dis[i][k] + dis[k][j]) {
          f = 0;
          break;
        } // 如果发现两个点的与这个边有关，这个边就不能删去
      }
      ans += f;
    }
  }
  ans /= 2;
  cout << m - ans;
  return 0;
}
```

---

## 作者：D23lhc (赞：1)

### 分析

首先，我们可以看出将连接 $i,j$ 的边删去后，$i,j$ 之间的最短路径可以被 $i,k+k,j$ 之间的最短路径所代替。于是我们先使用 floyd 算法跑一遍最短路，求出 dis 数组。然后枚举每条边，该边满足上述结论，就令答案累加即可。

## 核心代码
```
for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			if(j!=G[i].u&&j!=G[i].v&&dis[G[i].u][j]+dis[j][G[i].v]==dis[G[i].u][G[i].v]){
				ans++; break;
			}
```

---

## 作者：hanjinghao (赞：1)

# 思路

首先，跑一遍全源最短路，时间复杂度 $ O(n ^ 3) $。

令 $ dis_{i,j} $ 表示 $ i $ 到 $ j $ 之间的最短路。枚举每条边 $ (x,y) $ ，如果存在不同于 $ x,y $ 的第三点 $ z $，使得 $ dis_{x,z} + dis_{z,y} = dis_{x,y} $，那么 $ (x,y) $ 这条边就是可以被删掉的。

把能删的边都删掉就可以了。

总时间复杂度 $ O(n ^ 3 + nm) $。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

template < typename T >
inline const void read(T &x)
{
	bool flg = x = 0;
	char c;
	while ((c = getchar()) < 48 || c > 57)
		flg |= c == '-';
	do
		x = (x << 1) + (x << 3) + (c ^ 48);
	while ((c = getchar()) > 47 && c < 58);
	if (flg) x = -x;
}

int OUTPUT[45];

template < typename T >
inline const void write(T x)
{
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	int len = 0;
	do
	{
		OUTPUT[++len] = x % 10 | 48;
		x /= 10;
	}while (x);
	while (len)
		putchar(OUTPUT[len--]);
}

template < typename T >
inline const void writesp(const T x)
{
	write(x);
	putchar(32);
}

template < typename T >
inline const void writeln(const T x)
{
	write(x);
	putchar(10);
}

const int N = 305;
long long dis[N][N];
pair < int, int > e[N * N];

template < typename T >
inline void Chkmin(T &x, T y)
{
	if (y < x) x = y;
}

int main()
{
	int n, m, ans = 0;
	read(n);
	read(m);
	for (int i = 1; i <= n; ++i)
		for (int j = i + 1; j <= n; ++j)
			dis[i][j] = dis[j][i] = 0x3f3f3f3f3f3f3f3f;
	for (int i = 1; i <= m; ++i)
	{
		read(e[i].first);
		read(e[i].second);
		read(dis[e[i].first][e[i].second]);
		dis[e[i].second][e[i].first] = dis[e[i].first][e[i].second]; 
	}
	for (int k = 1; k <= n; ++k)
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				Chkmin(dis[i][j], dis[i][k] + dis[k][j]);
	for (int i = 1; i <= m; ++i)
		for (int j = 1; j <= n; ++j)
			if (j != e[i].first && j != e[i].second && dis[e[i].first][e[i].second] == dis[e[i].first][j] + dis[j][e[i].second])
			{
				++ans;
				break;
			}
	writeln(ans);
	return 0;
}
```

---

## 作者：Nahia (赞：0)

### 思路

不难发现，如果 $u \to v$ 这条边可以删，那么必定存在一条边 $u \to k \to v$，并且长度小于等于 $u \to v$ 的长度，这是我们便可以删除 $u \to v$ 这条边。

直接用 Floyd 算出最短路，最后统计一下即可。

时间复杂度：$\mathcal{O}(n^3)$。

### solution

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e2+10;
const int M=5e4+10;
int f[N][N];
bool g[N][N];
struct node{
	int u,v,w;
}a[M];
int main(){
	int n,m;
	cin>>n>>m;
	memset(f,0x3f,sizeof(f));
	for(int i=1;i<=m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		f[u][v]=f[v][u]=w;
		a[i]={u,v,w};
	}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++){
				if(i==j||i==k||k==j)
					continue;
				if(f[i][j]==f[i][k]+f[k][j])
					g[i][j]=1;
				f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
			}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++){
				if(i==j||i==k||k==j)
					continue;
				if(f[i][j]==f[i][k]+f[k][j])
					g[i][j]=1;
				f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
			}
	int ans=0;
	for(int i=1;i<=m;++i)
		if(g[a[i].u][a[i].v]||f[a[i].u][a[i].v]!=a[i].w) ans++;
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：yaaaaaan (赞：0)

## 思路
题目要求删除一些边使得最短路不变，则我们思考如果能删除 $x$ 到 $y$ 的边，那一定会有一个中转点 $z$ 使得如果从 $x$ 到 $z$ 的最短路加上 $z$ 到 $y$ 的最短路等于 $x$ 到 $y$ 的最短路。那这条边就可以删除。

明白思路后，观察数据范围很小，用 floyd 跑最短路即可。

## code


```cpp
#include<bits/stdc++.h>
#define int long long
#pragma GCC optmize(3)
using namespace std;
int n,m,ans;
int dis[301][301],b[301][301];
struct st{
	int x,y,z;
}e[900001];
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	memset(dis,0x3f,sizeof(dis));
	for(int i=1;i<=m;i++)
	{
		int x,y,z;
		cin>>x>>y>>z;
		dis[x][y]=z;
		dis[y][x]=z;
		e[i]={x,y,z};
	}
	for(int k=1;k<=n;k++)
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
			}
		}
	}
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n;j++)
		{
//			cout<<e[i].x<<" "<<e[i].y<<" "<<j<<" "<<dis[e[i].x][j]+dis[j][e[i].y]<<" "<<dis[i][j]<<"\n";
			if(j!=e[i].x&&j!=e[i].y&&dis[e[i].x][j]+dis[j][e[i].y]==dis[e[i].x][e[i].y]) 
			{
				ans++;
				break;
			}
		}
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：PDAST (赞：0)

图论练手题，但我为什么赛时没过？
## 题意
给你一张无向图，请你求出在不影响任意两点的最短距离以及连通性的情况下，能删去的边的最大数量。
## 思路
我们发现，当两个点之间的最短路径不为经过直接连接这两个点的边时，这条边就可以被删去。再看数据范围，弗洛伊德完全没问题，我们只要在转移时标记那些所连两点最短距离小于等于这条边边权的边，并删去这些边不就行了！
## 代码
~~我知道你们最想看这个~~。
~~~cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int dis[301][301],vis[301][301],u[100001],v[100001],w[100001];
signed main(){
	int n,m,ans=0;
	cin>>n>>m;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)dis[i][j]=(i==j?0:0x7fffffff);
	for(int i=1;i<=m;i++){
		cin>>u[i]>>v[i]>>w[i];
		dis[u[i]][v[i]]=dis[v[i]][u[i]]=w[i];
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			if(i==k)continue;
			for(int j=1;j<=n;j++){
				if(j==k)continue;	
				if(dis[i][k]+dis[j][k]<dis[i][j])dis[i][j]=dis[i][k]+dis[j][k];
				else if(dis[i][k]+dis[j][k]==dis[i][j])vis[i][j]=1;
			}
		}
	}
	for(int i=1;i<=m;i++){
		if(w[i]>dis[u[i]][v[i]]||w[i]==dis[u[i]][v[i]]&&vis[u[i]][v[i]])ans++;
	}
	cout<<ans;
}
~~~

---

## 作者：Merge_all (赞：0)

### 思路：
- 首先数据范围较小，可以用一点**暴力的做法**。
- 处理出**每两个点之间的最短距离**，可以用 Floyd 求出来。
- 我们发现想要删除 $u$ 到达 $v$ 的边，就要**保证任意的一个中转点** $x$ 使得 $dis_{u,x}+dis_{x,v}=dis_{u,v}$，每次循环枚举即可。

### 代码：
```
#include<bits/stdc++.h>

using namespace std;

#define int long long

const int N=350;

int dis[N][N],n,m;
int ans;

struct node{
	int u,v,w;
}e[N*N];

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	memset(dis,0x3f,sizeof(dis));
	for(int i=1;i<=m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		e[i]={u,v,w};
		dis[u][v]=dis[v][u]=w;
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
			}
		}
	}
	for(int i=1;i<=m;i++){
		bool flag=false;
		for(int j=1;j<=n;j++){
			if(j==e[i].u||j==e[i].v) continue;
			if(dis[e[i].u][j]+dis[j][e[i].v]==dis[e[i].u][e[i].v]) flag=true;
		}
		if(flag) ans++;
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：UnfortunatelyDead (赞：0)

其实是求有多少条边能被替换掉。

考虑一条边被替换，就是 $(u_i,v_i)$ 这条边，存在一条 $u_i \rightarrow v_i$ 的路径，其路径长度总和不劣于 $w_i$，那么 $i$ 号边可以被替换掉。  
但是其实这样子并不好找，我们其实可以把路径一分为二，分成两个部分，首先一个基本事实是 $dis_{u_i,k} + dis_{k,v_i} = dis_{u_i,v_i}$，而 $k$ 作为中转点即断点，本质上是起着沟通作用，那么被替换就变成了存在一个点 $k$ 即可。

$dis$ 数组可以 `Floyd` 预处理出来，代码过于简单不放了。

---

## 作者：majoego (赞：0)

很巧妙的一题，Floyd 好题，很像一道叫做：[重要的城市](https://www.luogu.com.cn/problem/P1841) 的题。

我一开始思考的是，对于每一次 Floyd 转移成功的时候用一个 $vis_{i,j} = k$ 来记录，然后到后面在逐个递归往前推，后面发现其实是有反例的。

所以，我们考虑直接跑一边 Floyd 板子。对于 $dis_{i,j} = dis_{i,k} + dis_{k,j}$ 的情况，直接记录一下答案，即可。~~由于举不出反例所以这是正解。~~

当然，仔细想想，这肯定是对的。主函数代码超过 $5$ 行的都是没有练习过压行的。

[link](https://atcoder.jp/contests/abc243/submissions/51179629)。

---

## 作者：mojoege (赞：0)

## 题意

给你一张无重边无自环的联通带权无向图。

定义 $d(i,j)$ 是 $i$ 到 $j$ 的最短路径上的边权之和。

你需要删除一些边。要求删完之后的图满足下列条件：

- 图仍然联通。
- 对于 $1\le i,j\le N$，删边前的 $d(i,j)$ **等于**删边后的 $d(i,j)$。

现在问你最多能删多少条边。

## 分析

我们有了一个朴素的思路：用 dijkstra 跑一遍“全源最短路”记录哪条边没有在任意一条最短路上然后统计答案即可。

但是上面这个方法很难实现，那就去想 Floyd。Floyd 很容易求出来全源最短路，但是哪条边是最短路上的边不知道，现在问题就转换成了：已知任意两个点之间的最短路，求哪条边是在最短路上的。

考虑 Floyd 的性质，经过松弛的边肯定不是最短路，那只要在处理完 $dis$ 之后枚举所有边，看这条边是否被松驰过，如果是直接累加答案。具体的，松弛操作的判断可以直接去枚举除了这条边两个端点的点 $k$ 看这两个端点到 $k$ 的距离是否是他们俩的最短距离就好了。

这里我们不用考虑删完边后它是不是联通的，因为如果有一条边是最短路上的边，它一定没有被松弛，统计答案时也不会记录它，而这条边肯定是它左侧部分点到右侧部分点最短路上的，也就是这条边左边和右边的点至少有这条边连着，肯定是联通的。

最终复杂度 $O(n^3+nm)$ 可以过。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m, ans;
int dis[305][305];//最短路数组
struct edge{
    int u, v, w;
}e[100005];

int main(){
    cin >> n >> m;
    memset(dis, 0x3f, sizeof(dis));
    for (int i = 1, u, v, w; i <= m; i++){
        cin >> u >> v >> w;
        e[i].u = u, e[i].v = v, e[i].w = w;
        dis[u][v] = dis[v][u] = w;
    }
    for (int i = 1; i <= n; i++) dis[i][i] = 0;
    for (int k = 1; k <= n; k++){
        for (int i = 1; i <= n; i++){
            for (int j = 1; j <= n; j++) dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);//Floyd
        }
    }
    for (int i = 1; i <= m; i++){
        int flag = 0;
        for (int j = 1; j <= n; j++){
            if (j != e[i].u && j != e[i].v && dis[e[i].u][e[i].v] == dis[e[i].u][j] + dis[j][e[i].v]) flag = 1;//被松驰过，记录答案
        }
        ans += flag;
    }
    cout << ans;
    return 0;
}
```

---

## 作者：_qingshu_ (赞：0)

# 思路：

首先看到 $2\le N \le 300$，考虑先 floyd 求出全源最短路，这个是好实现的，就是初值需要赋大一点。

考虑操作，发现如果去寻找那些边是可以删除的话，无法及时确认对其余点是否存在影响（删除存在后效性），且一但出现我们需要跑一边全图去寻找路径，这会导致代码非常麻烦且很有可能会 T 掉。

那么考虑正难则反，发现可以删除的就是全部的边减去不能删除的边，又看到图中无重边无自环。那么我们考虑去计算不能删除的边的数量。

当两点之间最短路径唯一时，路径上的边一定都不可以删除，这是好想的。考虑如何求得路径，发现路径上任意两点之间的路径依然是唯一的，那么可以考虑去遍历所有的二元组，每当两点之间路径唯一且两者之间最短路等于其直接连边长度的时候，我们可以唯一确定不可删除的边，而我们遍历所有的二元组，可以保证所有的边都会被判断，保证正确性。

时间复杂度 $\mathcal{O}(n^3)$。

# Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,ans,flag,dis[520][520];
int main(){
	cin>>n>>m;
	ans=m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			dis[i][j]=10000000000000;
		}
		dis[i][i]=0;
	}
	for(long long i=1,u,v,w;i<=m;i++){
		cin>>u>>v>>w;
		dis[u][v]=dis[v][u]=min(dis[u][v],w);
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			flag=1;
			for(int k=1;k<=n;k++){
				if(k!=i&&k!=j&&dis[i][j]==dis[i][k]+dis[k][j]){
					flag=0;
					break;
				}
			}
			ans-=flag;
		}
	}
	cout<<ans;
} 
```

---

## 作者：FireRain (赞：0)

# 思路

首先发现对于一条从 $u$ 到 $v$ 的点能被删，说明一定有一个中转点 $x$ 使得 $u \to x \to v$ 的最短路径长度与未删边之前的最短路径相等。

那么定义 $d_{i,j}$ 表示从 $i$ 到 $j$ 的最短距离，如果 $u \to v$ 的边可以删，一定有一个 $x$，满足 $x \neq u \wedge x \neq v \wedge d_{i,x} + d_{x,j} = d_{i,j}$。

$d$ 数组可以直接使用 Floyd 求解。时间复杂度 $\Theta(n^3)$。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long

using namespace std;

const int N = 310,M = 1e5 + 10,inf = 0x3f3f3f3f;
int n,m,ans;
int d[N][N];

struct edge{
    int a,b,c;
}g[M];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

signed main(){
    memset(d,inf,sizeof(d));
    n = read();
    m = read();
    for (re int i = 1;i <= n;i++) d[i][i] = 0;
    for (re int i = 1;i <= m;i++){
        int a,b,c;
        a = read();
        b = read();
        c = read();
        g[i] = {a,b,c};
        d[a][b] = d[b][a] = c;
    }
    for (re int k = 1;k <= n;k++){
        for (re int i = 1;i <= n;i++){
            for (re int j = 1;j <= n;j++) d[i][j] = min(d[i][j],d[i][k] + d[k][j]);
        }
    }
    for (re int i = 1;i <= m;i++){
        bool falg = false;
        for (re int j = 1;j <= n;j++){
            if (j == g[i].a || j == g[i].b) continue;
            if (d[g[i].a][g[i].b] == d[g[i].a][j] + d[j][g[i].b]) falg = true;
        }
        ans += falg;
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：taojinchen (赞：0)

# 思路
我们先依照题意把图建好。当两点之间的最短路可以通过其他点周转过来时，这条边则可以不要，因为不要这一条边也可以保证两点间的最短路不变，基于这样一种贪心的思想，我们可以尽可能的多删几条边，我们可以统计直接输出。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[305][305],i,j,k,t,n,m,f[305][305],ans,vis[305][305];
int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n>>m;
  for(i=1;i<=n;i++){
    for(j=1;j<=n;j++){//初始化
      vis[i][j]=1;
      f[i][j]=1e18;
    }
  }
  while(m--){
    cin>>i>>j;
    cin>>f[i][j];//输入
    f[j][i]=f[i][j];//建图
    vis[i][j]=0;
  }
  for(k=1;k<=n;k++){//最短路
    for(i=1;i<=n;i++){
      for(j=1;j<=n;j++){
        f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
      }
    }
  }
  for(k=1;k<=n;k++){
    for(i=1;i<n;i++){
      if(k==i)continue;
      for(j=i+1;j<=n;j++){
        if(k==j)continue;
        if(f[i][j]==f[i][k]+f[k][j]&&vis[i][j]==0){//删边
          ans++;//统计
          vis[i][j]=1;//标记，不可以重复删同一条边
        }
      }
    }
  }
  cout<<ans;//输出
  return 0;
}
```


---

## 作者：ghx0052 (赞：0)

# 思路：

赛时以为是求 $n$ 遍最短路，标记所有最短路上的边，然后剩下的就是可以删的，但是这样删很有可能删多了，也处理不了这样的情况：

```cpp
3 3
1 2 2
2 3 3
1 3 5
```

还是考虑松弛操作，对于一条边 $[u,v]$ 来说，如果它被松弛了，则说明这条边不是最短路上的边，不需要留下，因为可以经过其他更短的边从 $u$ 到达 $v$。

这题的 $n$ 很小，我们可以使用 `floyd` 求出任意两点的最短路，然后枚举边判断该边是否被松弛过，累计可以删除的边。

# 代码：

```cpp
struct Edge {
    int u, v, w;
};

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 1, vector<int>(n + 1, INF));
    for (int i = 1; i <= n; i++) {
        g[i][i] = 0;
    }
    vector<Edge> e(m);
    for (int i = 0; i < m; i++) {
        cin >> e[i].u >> e[i].v >> e[i].w;
        g[e[i].u][e[i].v] = g[e[i].v][e[i].u] = e[i].w;
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                ckmin(g[i][j], g[i][k] + g[k][j]);
            }
        }
    }

    int cnt = 0;
    for (auto [u, v, w] : e) {
        bool ok = true;
        for (int k = 1; k <= n; k++) {
            if (k != u && k != v && g[u][v] >= g[u][k] + g[k][v]) {
                ok = false;
            }
        }
        cnt += ok;
    }
    cout << m - cnt << "\n";
    return 0;
}
```

---

