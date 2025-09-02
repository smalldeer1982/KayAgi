# Unbearable Controversy of Being

## 题目描述

Tomash keeps wandering off and getting lost while he is walking along the streets of Berland. It's no surprise! In his home town, for any pair of intersections there is exactly one way to walk from one intersection to the other one. The capital of Berland is very different!

Tomash has noticed that even simple cases of ambiguity confuse him. So, when he sees a group of four distinct intersections $ a $ , $ b $ , $ c $ and $ d $ , such that there are two paths from $ a $ to $ c $ — one through $ b $ and the other one through $ d $ , he calls the group a "damn rhombus". Note that pairs $ (a,b) $ , $ (b,c) $ , $ (a,d) $ , $ (d,c) $ should be directly connected by the roads. Schematically, a damn rhombus is shown on the figure below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF489D/8b5a60981c3e3bd62ad47b07d6098988071c0c74.png)Other roads between any of the intersections don't make the rhombus any more appealing to Tomash, so the four intersections remain a "damn rhombus" for him.

Given that the capital of Berland has $ n $ intersections and $ m $ roads and all roads are unidirectional and are known in advance, find the number of "damn rhombi" in the city.

When rhombi are compared, the order of intersections $ b $ and $ d $ doesn't matter.

## 样例 #1

### 输入

```
5 4
1 2
2 3
1 4
4 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4 12
1 2
1 3
1 4
2 1
2 3
2 4
3 1
3 2
3 4
4 1
4 2
4 3
```

### 输出

```
12
```

# 题解

## 作者：songhongyi (赞：3)

题目简述：求一个有向图有多少组四个点$a,b,c,d$，存在$a \to b$,$a \to d$,$b \to c$和$d \to c$这4条边，即构成下图的形状？  
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF489D/8b5a60981c3e3bd62ad47b07d6098988071c0c74.png)  
我们可以换一种角度考虑，对于这种菱形，我们把它想象成$(a,c)$两点之间有两条恰经过一个点的路径。

那我们可以先预处理出每两点之间恰经过一个点的路径的条数，这很容易办到，然后$a,c$两点间的菱形的个数就是从所有路径中选出两条的方案数，即$C_{cnt}^2$($cnt$就是$a,c$两点之间恰经过一个点的路径的条数)，两重循环计算即可。

$C_a^2$可以表示成$\dfrac {a(a-1)}2$，代码就是`(a*(a-1))/2`。

代码如下  
```cpp

// Problem : CF489D Unbearable Controversy of Being
// Contest : Luogu
// URL : https://www.luogu.com.cn/problem/CF489D
// Memory Limit : 250 MB
// Time Limit : 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <iostream>
#include <vector>
using namespace std;
vector< int > edges[ 3010 ]; //vector存图
void add_edge( int u, int v )  //增加一条边的函数
{
    edges[ u ].push_back( v );  //注意是有向图，不建反向边
}
int cnt[ 3010 ][ 3010 ];
int main()
{
    int n, m;
    cin >> n >> m;
    for ( int i = 1; i <= m; i++ )
    {
        int u, v;
        cin >> u >> v;
        add_edge( u, v );
    } // 把图读进来存好
    for ( int i = 1; i <= n; i++ )
    {
        for ( auto j : edges[ i ] ) //枚举每一条边
        {
            for ( auto k : edges[ j ] ) //枚举每个边到达点的所有出边
            {
                if ( k != i ) //可能出现正好有向图里两点之间两个方向的边都有，过滤掉
                {
                    cnt[ i ][ k ]++;  //这时候i -> j -> k就是一条i和k之间恰经过j一个节点的路径
                }
            }
        }
    }
    int ans = 0; //开始统计答案
    for ( int i = 1; i <= n; i++ )
    {
        for ( int j = 1; j <= n; j++ ) // 枚举每两个点
        {
            ans += cnt[ i ][ j ] * ( cnt[ i ][ j ] - 1 ) / 2; //计算两点间菱形个数
        }
    }
    cout << ans << endl;//输出答案
}
```

---

## 作者：bzzltl (赞：1)

## 题目大意

给定一张有向图，求问存在几组四个点满足 $\left( a,b\right)$,$\left( a,d\right)$,$\left( b,c\right)$,$\left( d,c\right)$，达到如图所示的效果。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF489D/8b5a60981c3e3bd62ad47b07d6098988071c0c74.png)



## 题目分析

分析题目，可以发现菱形能否构成和 $a$ 能否到达 $c$ 有关，而菱形的数目和有多少条类似 $a \to b \to c$ 或者 $a \to d \to c$ 这样的路径有关。

所以需要完成 2 个操作，一个是判断两点之间是否存在间隔一个点这样的关系，另一个是记录存在这样关系的两点之间的路径数目。

设 x 为两点间满足关系的路径数目，因为是任取 2 条构成菱形，所以这 2 个点做的贡献是 $C_{x}^{2}$，即为 $\dfrac{x\left( x-1\right) }{2}$。

注意到 $n$ 特别小，所以可以直接开个二维数组记录信息。

## AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+6;
const int M=3e3+7;
const int IM=2147483647;
const long long LLM=9223372036854775807;

inline int read()
{
	int x=0,y=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') y=-y;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^'0');c=getchar();}
	return x*y;
}

int n,m,ans,mp[M][M];
vector<int>vec[N];

signed main()
{
	n=read(),m=read();
	for(int i=1;i<=m;i++)
	{
		int u=read(),v=read();
		vec[u].push_back(v);
	}
	for(int u=1;u<=n;u++)
		for(int i=0;i<vec[u].size();i++)
			for(int j=0;j<vec[vec[u][i]].size();j++)
				if(u!=vec[vec[u][i]][j]) mp[u][vec[vec[u][i]][j]]++;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			ans+=mp[i][j]*(mp[i][j]-1)/2;
	printf("%d\n",ans);
	return 0;
}

```

---

## 作者：Mars_Dingdang (赞：1)

这道题确实挺水，用了 Floyd 的思想。数据范围有误。
## 题目大意

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF489D/8b5a60981c3e3bd62ad47b07d6098988071c0c74.png)

在一个有向图中，求类似于上图的菱形，即 $4$ 个点 $a,b,c,d$ 同时存在 $(a,b),(a,d),(b,c),(d,c)$ 四条边组成的菱形的个数

$1 \le n \le 3000,1 \le m \le 30000$。

## 大体思路
对于一个有向无权图 $G$，求如上图所示的菱形，等价于求出 $a,c$，$s.t.\ a,c\in[1,n]\cap \mathbb Z$ 且 $dist(a\to c)=dist(a\to b)+dist(b\to c)=1+1=2$。

假设这样的路径条数为 $k$ 条，则任选两条即可组成满足要求的菱形，因此答案为 $\dbinom k 2=\dfrac{k(k-1)}2$。

因此问题转换为如何求 $dist(a\to c)=2$。考虑这个式子中出现 $dist(a\to b)+dist(b\to c)$，联想到 Floyd 算法。

因此，令 $deg(u,v)$ 表示 $dist(u\to v)=2$ 的条数，计算时枚举所有节点 $x$，再枚举其所有出点 $y$ 作为中转点，假设 $y$ 的出点为 $z$，则 $x\neq z$ 时 $x\to y\to z$ 便是一条满足要求的路径，$deg(x,z)\leftarrow deg(x,z)+1$。

```cpp
	rep(u, 1, n) //枚举起点
		for(int i = head[u]; ~i; i = nxt[i]) {//遍历所有出边
			int v = ver[i];//枚举中转点
			for(int j = head[v]; ~j; j = nxt[j]) //再遍历其出边
				if(ver[j] != u) deg[u][ver[j]] ++;//记录路径数
		}
```

时间复杂度：$O(n^2 + tm)$，$t$ 视图的的构造方式而定。

## 完整代码
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define rep(ii,aa,bb) for(re int ii = aa; ii <= bb; ii++)
#define Rep(ii,aa,bb) for(re int ii = aa; ii >= bb; ii--)
typedef long long ll;
typedef unsigned long long ull;
const int maxn = 3e3 + 5, maxm = 1e5 + 5;
namespace IO_ReadWrite {
	#define re register
	#define gg (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1<<21, stdin), p1 == p2) ? EOF :*p1++)
	char buf[1<<21], *p1 = buf, *p2 = buf;
	template <typename T>
	inline void read(T &x){
		x = 0; re T f=1; re char c = gg;
		while(c > 57 || c < 48){if(c == '-') f = -1;c = gg;}
		while(c >= 48 &&c <= 57){x = (x<<1) + (x<<3) + (c^48);c = gg;}
		x *= f;return;
	}
	inline void ReadChar(char &c){
		c = gg;
		while(!isalpha(c)) c = gg;
	}
	template <typename T>
	inline void write(T x){
		if(x < 0) putchar('-'), x = -x;
		if(x > 9) write(x/10);
		putchar('0' + x % 10);
	}
	template <typename T>
	inline void writeln(T x){write(x); putchar('\n');}
}
using namespace IO_ReadWrite;
int ver[maxm], nxt[maxm], head[maxn], tot;
inline void add(int u, int v){
	ver[++tot] = v; nxt[tot] = head[u]; head[u] = tot;
}//链式前向星
int n, m, deg[maxn][maxn];
int main() {
	read(n); read(m);
	memset(head, -1, sizeof head);
	memset(nxt, -1, sizeof nxt);
	rep(i, 1, m) {
		int u, v;
		read(u); read(v);
		add(u, v);
	}
	
	rep(u, 1, n) //枚举起点
		for(int i = head[u]; ~i; i = nxt[i]) {//遍历所有出边
			int v = ver[i];//枚举中转点
			for(int j = head[v]; ~j; j = nxt[j]) //再遍历其出边
				if(ver[j] != u) deg[u][ver[j]] ++;//记录路径数
		}
	
	ll ans = 0;
	rep(i, 1, n)
		rep(j, 1, n)//统计答案
			ans += (deg[i][j] * (deg[i][j] - 1) >> 1);
	writeln(ans);
	return 0;
}
```

---

## 作者：_JF_ (赞：0)

[CF489D Unbearable Controversy of Being ](https://www.luogu.com.cn/problem/CF489D)

和所有题解区神仙不太一样的做法。

考虑枚举 $b,d$。

我们可以与处理出来，对于点对 $(x,y)$ 有多少个点同时连向了他们，以及有多少个点同时被他们连上。

这个其实可以暴力处理，因为点的数量只有 $3000$ 个。合法的组数估算最多也就是 $3000\times3000\times10$。

处理同时被他们连上的点考虑反图即可。

然后统计的时候直接乘法原理即可。

但是发现一个巨大问题，可能有重复。就是连向 $(x,y)$ 和 $(x,y)$ 同时连向的，可能是同一个点，这是不合法的。

考虑去重，我的做法是用空间换时间，也就是先在同时连向 $(x,y)$ 标记，这个就是扫 $x$ 和 $y$ 的出边标记即可。同理处理出同时 $(x,y)$ 连出去的。

最后再对着重复标记的减去，显然重复的只有可能在 $x$ 出去的点中产生，具体实现看代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =3003;
#define int long long
int In[N][N],Out[N][N];
vector<int> g[N],G[N];
bool Vis[N],Vis1[N],Vis2[N],Vis3[N];
int ans,n,m;
void init(){
	for(int i=1;i<=n;i++)
		for(int j=0;j<g[i].size();j++)
			for(int k=0;k<g[i].size();k++){
				if(j==k)	continue;
				In[g[i][j]][g[i][k]]++;
			}
}
void init1(){
	for(int i=1;i<=n;i++)
		for(int j=0;j<G[i].size();j++)
			for(int k=0;k<G[i].size();k++){
				if(j==k)	continue;
				Out[G[i][j]][G[i][k]]++;
			}
}
void Slove(){
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if(i!=j)	ans+=In[i][j]*Out[i][j];
}
void calc(){
	for(int i=1;i<=n;i++)	
		for(int j=i+1;j<=n;j++){
			for(int k=0;k<g[i].size();k++)	Vis[g[i][k]]=true;
			for(int k=0;k<g[j].size();k++)
				if(Vis[g[j][k]]==true)	Vis1[g[j][k]]=true;
			for(int k=0;k<G[i].size();k++)	Vis2[G[i][k]]=true;
			for(int k=0;k<G[j].size();k++)
				if(Vis2[G[j][k]]==true)	Vis3[G[j][k]]=true;
			for(int k=0;k<g[i].size();k++)	if(Vis1[g[i][k]]==true&&Vis3[g[i][k]]==true)	ans--;
			for(int k=0;k<g[i].size();k++)	Vis[g[i][k]]=false,Vis1[g[i][k]]=false;
			for(int k=0;k<G[i].size();k++)	Vis3[G[i][k]]=false,Vis2[G[i][k]]=false;
		}
}
signed main(){
	cin>>n>>m;
	for(int i=1,u,v;i<=m;i++)	cin>>u>>v,g[u].push_back(v),G[v].push_back(u);
	init(),init1(),Slove(),calc();
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：Grow2011 (赞：0)

## 题目大意

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF489D/8b5a60981c3e3bd62ad47b07d6098988071c0c74.png)

在一个有向图中，求在这张有向图中包含几个上图的菱形。

## 题目解析
 
从图可以看出，这个“菱形”其实就是由两条由 $a$ 连向 $c$ 且只经过一个点的路径组成。

设从 $a$ 到 $c$ 且只经过一个点的路径数量为 $S$，从组合数学的角度来说，这个“菱形”的数量就为 $C^2_S = \displaystyle\frac{S\cdot(S-1)}{2}$，这里的 $C$ 为[组合数](https://baike.baidu.com/item/%E7%BB%84%E5%90%88%E6%95%B0/2153250?fr=ge_ala)。

**怎么求这个路径数呢？**

这个实则不难。我们可以对于每个点往外拓展两步，把拓展到的点的路径树都加一，最后求值就可以了。

**注意：**

- **从 $a$ 且只经过一个点到 $a$ 的路径是不能计算的。**

- **答案增加的时候要与 0 取 $\max$。**

附代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,x,y,ans; 
vector<int>vt[3005];
int f[3005];
int main(){
    cin >> n >> m;
    while(m--){
    	cin >> x >> y;
    	vt[x].push_back(y);//建立有向边 
	}
	for(int i = 1;i<=n;i++){
		for(int j = 1;j<=n;j++)f[j] = 0;//清空 
		for(int j = 0;j<vt[i].size();j++){//第一步 
			int fi = vt[i][j];
			for(int k = 0;k<vt[fi].size();k++){//第二步 
				f[vt[fi][k]]++;//到 vt[fi][k] 的路径数加一 
			}
		}
		for(int j = 1;j<=n;j++){
			if(i==j)continue;//排除自身 
			ans+=max(0,(f[j]-1)*f[j]/2);//增加答案 
		}
	}
	cout << ans;//输出答案 
	return 0;
}
```

---

## 作者：durex_com (赞：0)

# 很蠢的一道题
暴力枚举两个由两条边构成的点，剩下的像小学数线段一样统计答案就可以了。

```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<cmath>
#include<queue>
#include<functional>
using namespace std;
struct zk
{
	int u,v,next;
}e[60001];
int head[3001];
int cnt=0;
int n,m;
void add(int  u,int v)
{
	e[cnt].u=u;
	e[cnt].v=v;
	e[cnt].next=head[u];
	head[u]=cnt++;
}
int vis[3001][3001];
int main()
{
	scanf("%d%d",&n,&m);
	int a,b;
	memset(head,-1,sizeof(head));
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		add(a,b);
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=head[i];j!=-1;j=e[j].next)
		{
			int v=e[j].v;
			for(int k=head[v];k!=-1;k=e[k].next)
			{
				if (e[k].v!=i)vis[i][e[k].v]++;
			}
		}
	}
	long long ans=0;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	{
		ans+=vis[i][j]*(vis[i][j]-1)/2;
	}
	printf("%lld",ans);
	return 0;
}
```

---

