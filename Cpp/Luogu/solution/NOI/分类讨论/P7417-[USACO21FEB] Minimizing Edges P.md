# [USACO21FEB] Minimizing Edges P

## 题目描述

Bessie 有一个连通无向图 $G$。$G$ 有 $N$ 个编号为 $1\ldots N$ 的结点，以及 $M$ 条边（$2\le N\le 10^5, N-1\le M\le \frac{N^2+N}{2}$）。$G$ 有可能包含自环（一个结点连到自身的边），但不包含重边（连接同一对结点的多条边）。

令 $f_G(a,b)$ 为一个布尔函数，对于每一个 $1\le a\le N$ 和 $0\le b$，如果存在一条从结点 $1$ 到结点 $a$ 的路径恰好经过了 $b$ 条边，则函数值为真，否则为假。如果一条边被经过了多次，则这条边会被计算相应的次数。

Elsie 想要复制 Bessie。具体地说，她想要构造一个无向图 $G'$，使得对于所有的 $a$ 和 $b$，均有 $f_{G'}(a,b)=f_G(a,b)$。

Elsie 想要进行最少数量的工作，所以她想要构造最小可能的图。所以，你的工作是计算 $G'$ 的边数的最小可能值。

每个输入包含 $T$（$1\le T\le 5\cdot 10^4$）组独立的测试用例。保证所有测试用例中的 $N$ 之和不超过 $10^5$，且所有测试用例中的 $M$ 之和不超过 $2\cdot 10^5$。


## 说明/提示

#### 样例 1 解释

在第一个测试用例中，Elsie 可以通过从 $G$ 中移除 $(2,5)$ 来构造得到 $G'$。或者，她也可以构造一张包含以下边的图，因为她并未被限制只能从 $G$ 中移除边：

```
1 2
1 4
4 3
4 5
```

Elsie 显然不能得到比 $N-1$ 更优的解，因为 $G'$ 一定也是连通的。

#### 样例 2 解释

在以上这些测试用例中，Elsie 都不能做得比 Bessie 更优。

#### 测试点性质：

 - 对于另外 $5\%$ 的数据，满足 $N\le 5$。
 - 对于另外 $10\%$ 的数据，满足 $M=N$。
 - 对于另外 $20\%$ 的数据，如果并非对于所有的 $b$ 均有 $f_G(x,b)=f_G(y,b)$，则存在 $b$ 使得 $f_G(x,b)$ 为真且 $f_G(y,b)$ 为假。
 - 对于另外 $30\%$ 的数据，满足 $N\le 10^2$。   
 - 对于另外 $25\%$ 的数据，没有额外限制。

供题：Benjamin Qi

## 样例 #1

### 输入

```
2

5 5
1 2
2 3
2 5
1 4
4 5

5 5
1 2
2 3
3 4
4 5
1 5```

### 输出

```
4
5```

## 样例 #2

### 输入

```
7

8 10
1 2
1 3
1 4
1 5
2 6
3 7
4 8
5 8
6 7
8 8

10 11
1 2
1 5
1 6
2 3
3 4
4 5
4 10
6 7
7 8
8 9
9 9

13 15
1 2
1 5
1 6
2 3
3 4
4 5
6 7
7 8
7 11
8 9
9 10
10 11
11 12
11 13
12 13

16 18
1 2
1 7
1 8
2 3
3 4
4 5
5 6
6 7
8 9
9 10
9 15
9 16
10 11
11 12
12 13
13 14
14 15
14 16

21 22
1 2
1 9
1 12
2 3
3 4
4 5
5 6
6 7
7 8
7 11
8 9
8 10
12 13
13 14
13 21
14 15
15 16
16 17
17 18
18 19
19 20
20 21

20 26
1 2
1 5
1 6
2 3
3 4
4 5
4 7
6 8
8 9
8 11
8 12
8 13
8 14
8 15
8 16
8 17
9 10
10 18
11 18
12 19
13 20
14 20
15 20
16 20
17 20
19 20

24 31
1 2
1 7
1 8
2 3
3 4
4 5
5 6
6 7
6 9
8 10
10 11
10 16
10 17
10 18
10 19
10 20
11 12
12 13
13 14
14 15
15 16
15 17
15 18
15 19
15 20
15 21
15 22
15 23
15 24
21 22
23 24```

### 输出

```
10
11
15
18
22
26
31```

# 题解

## 作者：约瑟夫用脑玩 (赞：19)

换一种方式来解释这道题的贪心可能更好理解一点。

首先我们得知道新图只与函数 $f$ 的值有关，而由于我们可以在一条边上来回横跳，所以 $f$ 是否有值取决于奇/偶最短路的长度，那么我们用 $O(n)$ BFS 出最短路即可。

注意特判一下每个点只有奇数路径或偶数路径，即这是个二分图，那么直接用原图的最短路树就可以表示了。

否则，每个点都会有奇数和偶数路径，设一个点的奇最短路和偶最短路二元组为 $(x,y)$。

由于顺序并没有关系，且为了~~好看~~方便，我们取 $x$ 为奇偶中较短的最短路，$y$ 为较长的，即 $x<y$。

那么考虑导致 $(x,y)$ 的方式：

- 有另一个点奇偶最短路分别为 $(x-1,y-1)$ ，并连了一条边。

- 有两个点分别为① $(x-1,y+1)$ 和② $(x+1,y-1)$ ，都连了一条边。注意当 $x+1=y$ 时，有 $(x+1,y-1)=(y-1,x+1)=(x,y)$

![](https://cdn.luogu.com.cn/upload/image_hosting/aguh2rnz.png?x-oss-process=image/resize,m_lfit,h_200,w_200)

解释一下：第二个方式中①的第一维保证较小最短路为 $x$，②第二维保证了较大最短路为 $y$，而他们的其他维由于与 $(x,y)$ 的点有直接连边故最大都只能 $+1$。

第一种方式只用一条边显然血赚，但可能没有 $(x-1,y-1)$ 的点，此时就只能用第二种方式。

所以才出现了如下的贪心方法：

- 按先 $x+y$ 为第一维，再 $x$ 为第二维依次考虑。（下图中纵坐标为倒着的 $x+y$，横坐标为倒着的 $x$，故先从上到下，再从右到左依次考虑，也就是把上图往右掰了一点）

![](https://cdn.luogu.com.cn/upload/image_hosting/7ha8ys65.png?x-oss-process=image/resize,m_lfit,h_200,w_400)

- 如果右边 $(x-1,y+1)$ 没有第二种方式的需求传过来，那么 $(x,y)$ 直接选第一种方式。

  否则 $(x,y)$ 的一部分点用于满足其需求，于是还会有需求往左 $(x+1,y-1)$ 传，如果 $(x,y)$ 点数有多余的就还是用第一种方式。

  最后我们会传到 $x+1=y$ 的边界，此时就相当于同类连边不再传了。

  这样看的话，就是将必须用第二种方式的边一直往左传，传到边界用每个点 $\frac{1}{2}$ 的代价消掉，而传时还有 $1$ 的代价，故将本来用 $2$ 的代价减小为 $1.5$ 的代价。

  注意到 $1.5<1$，故有多余不用传时尽量还是用第一种方式。

和其他题解最后的做法都一样，但思路可能会好理解点qwq。

[估计没人看的代码](https://www.luogu.com.cn/paste/sy8zqruq)

Upd：修改了一点小锅，以前是对的表述就没改了。（虽然读着有点奇怪）

---

## 作者：crashed (赞：13)

# 题目

[点这里](https://www.luogu.com.cn/problem/P7417)看题目。

# 分析

~~这道题就离离离离离谱~~

首先不难发现 $f_G(u,x)$ 实际上只和到达 $u$ 的**奇偶最短路长度**相关。

那么很快就导出一种特例——即对于某个点，存在两种奇偶性的最短路的情况，可以发现此时 $G$ 是二分图。那么我们只需要考虑一种最短路，因此可以直接建立最短路树，得到答案为 $n-1$ 。

考虑一般情况，即 $G$ 上面有奇环的情况，此时对于任意的点，都有两种奇偶性的最短路。因此可以设 $d_u$ 表示 $u$ 的**最短路**，而用 $d'_u$ 表示 $u$ 的**奇偶性与 $d_u$ 不同的另一条最短路**。一个显然的性质是 $d<d'$ 。

分析一下 $G'$ 必须满足的条件：

1. 在 $u$ 的邻接点中，必须有一个点 $v$ ，满足 $d_u=d_v+1$ ；
2. 在 $u$ 的邻接点中，必须有一个点 $v$ ，满足 $d'_u=d'_v+1$ **或者** $d'_u=d_v+1$ ；

注意到我们其实只关心 $(d,d')$ 这样的有序对，我们就可以得到集合 $S(d,d')=\{u|d_u=d,d'_u=d'\}$ 。再简化一点，我们其实只关心 $S(d,d')$ 的大小，所以我们可以直接设 $f(d,d')=|S(d,d')|$ 。

根据之前的条件，我们再分析一下对于 $(d,d')$ ，它的连边情况：

1. 直接和 $(d-1,d'-1)$ 相连；
2. 直接和 $(d-1,d'+1)$ 和 $(d+1,d'-1)$ 相连；
3. 如果 $d+1=d'$ ，此时可以和 $(d-1,d'+1)$ 和 $(d,d')$ 相连，这种情况特殊在它的表现是**在 $S$ 内部连边**；

画一个图会更好理解：

![explanation.png](https://i.loli.net/2021/03/20/qweMzoHbnLWAVtR.png)

注意到，如果按照 $d+d'$ 分层，那么只有 1 为跨层连，而 2,3 均为同层连。这启发我们可以**按照 $d+d'$ 和  $d$ 的优先级进行处理**。

一个显然的性质是：如果我们可以找到一种最优的连边方法，使得**每个点的 $d$ 和 $d'$ 都可以转移过来**，那么这就是最优解之一。

~~其实不一定很显然，但是看起来是对的，证明 " 下次一定 "~~

因此我们就可以考虑给每个点找相邻点，不难想到可以按顺序贪心！

下面我们就可以愉快地讨论了：

1. 如果 $f(d-1,d'-1)>0,f(d-1,d'+1)=0$ ，那么没得说，只能全部连到 $f(d-1,d'-1)$ 上；

2. 如果 $f(d-1,d'-1)>0,f(d-1,d'+1)>0$ 且 $d+1<d'$ ，此时有可能 $S(d-1,d'+1)$ 的点需要连接到 $S(d,d')$ 中的点来。设这样的需求边为 $t$ 条，分类讨论：

   1. 如果 $t\le f(d,d')$ ，那么可以先分配 $t$ 个连接，剩下的点可以直接连到 $(d-1,d'-1)$ 上面一次解决问题；而钦定的 $t$ 个点还需要满足 $d'$ ，因此需要向 $S(d+1,d'-1)$ 连 $t$ 条边。
   2. 如果 $t>f(d,d')$ ，那么我们也可以重复地连 $t$ 条边，此时 $S(d,d')$ 里的点还需要满足 $d'$ 。经过下面的分析，我们可以知道将 $f(d,d')$ 条边**连至 $(d+1,d'-1)$ 会更优**。

   注意到上面我们默认存在 $(d+1,d'-1)$ ；如果不存在，那么下传的给 $(d+1,d'-1)$ 的边只能连到 $(d-1,d'-1)$ 。

3. 如果 $f(d-1,d'-1)>0,f(d-1,d'+1)>0$ 且 $d+1=d'$ ，此时我们可以在 $(d,d')$ 内部连边。这部分的讨论类似于 2 部分；但特殊的情况是，这样的 $(d,d')$ **一定找不到对应的 $(d+1,d'-1)$ ，所以原本下传的 $t$ 条边需要内部消化**，不难发现这样的贡献是 $\lceil\frac t 2\rceil$ 。

   在这里我们也可以解释为什么 2.2 中需要下传：无论这 $t$ 条边连在哪里，它一定会带来贡献；但如果向下传递，它就有可能连接到 $d+1=d'$ 的点，使得只缺 $d'$ 的点变多。粗算一下，只缺 $d'$ 的点代价为 $\frac{1}{2}$ ，而 $d,d'$ 都缺的点代价为 $1$ ，显然这样会划算一些。

运用 set 可以获得 $O(n\log_2n)$ 的复杂度，足以通过本题。如果分层并用指针应该可以做到 $O(n)$ 。


# 代码

```cpp
#include <set>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

#define rep( i, a, b ) for( int i = (a) ; i <= (b) ; i ++ )
#define per( i, a, b ) for( int i = (a) ; i >= (b) ; i -- )

typedef pair<int, int> Node;

const int INF = 0x3f3f3f3f;
const int MAXN = 1e5 + 5, MAXM = 2e5 + 5;

#define DX first
#define DY second

template<typename _T>
void read( _T &x )
{
	x = 0; char s = getchar(); int f = 1;
	while( s < '0' || '9' < s ) { f = 1; if( s == '-' ) f = -1; s = getchar(); }
	while( '0' <= s && s <= '9' ) { x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar(); }
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ) putchar( '-' ), x = - x;
	if( 9 < x ) write( x / 10 );
	putchar( x % 10 + '0' );
}

struct Edge
{
	int to, nxt;
}Graph[MAXM << 2];

set<Node> s;
Node seq[MAXN];

int dist[MAXN << 1];

int head[MAXN << 1];
int N, M, cnt;

bool Cmp( const Node &x, const Node &y )
{
	int tx = x.DX + x.DY, ty = y.DX + y.DY;
	return tx == ty ? x.DX < y.DX : tx < ty;
}

void Clean()
{
	cnt = 0, s.clear();
	rep( i, 1, N << 1 ) head[i] = 0;
}

void AddEdge( const int from, const int to )
{
	Graph[++ cnt].to = to, Graph[cnt].nxt = head[from];
	head[from] = cnt;
}

void AddE( const int from, const int to )
{
	AddEdge( from, to ), AddEdge( to, from );
}

void BFS()
{
	static int q[MAXN << 1], h, t;
	h = 1, t = 0; rep( i, 1, N << 1 ) q[i] = 0;
	rep( i, 1, N << 1 ) dist[i] = INF;
	dist[q[++ t] = 1] = 0;
	for( int u, v ; h <= t ; )
	{
		u = q[h ++];
		for( int i = head[u] ; i ; i = Graph[i].nxt )
			if( dist[v = Graph[i].to] > dist[u] + 1 )
				dist[q[++ t] = v] = dist[u] + 1;
	}
}

int main()
{
	int T;
	read( T );
	while( T -- )
	{
		read( N ), read( M ), Clean();
		rep( i, 1, M ) { int a, b; 
			read( a ), read( b ); 
			AddE( a, b + N ), AddE( a + N, b );
		}
		BFS(); bool flg = true;
		rep( i, 1, N )
		{
			if( dist[i] < dist[i + N] ) seq[i] = Node( dist[i], dist[i + N] );
			else seq[i] = Node( dist[i + N], dist[i] );
			if( seq[i].DY == INF ) flg = false;
		}
		if( flg == false ) { write( N - 1 ), putchar( '\n' ); continue; }
		
		sort( seq + 1, seq + 1 + N, Cmp ); int ans = 0, t = 0;
		for( int i = 1, r ; i <= N ; i = r )
		{
			for( r = i ; r <= N && seq[r] == seq[i] ; r ++ );
			s.insert( seq[i] );
			Node lu = Node( seq[i].DX - 1, seq[i].DY - 1 );
			flg = s.find( lu ) != s.end();
			if( t <= r - i ) 
			{
				if( flg ) ans += ( i > 1 ) * ( r - i );
				else ans += ( i > 1 ) * ( r - i ), t = r - i;
			}
			else ans += ( i > 1 ) * t, t = r - i;
			if( r > N || seq[r] != Node( seq[i].DX + 1, seq[i].DY - 1 ) )
			{
				if( seq[i].DX + 1 != seq[i].DY ) ans += t;
				else ans += t + 1 >> 1; t = 0;
			}
		}
		write( ans ), putchar( '\n' );
	}
	return 0;
}
```cpp


---

## 作者：丛雨 (赞：7)

### Minimizing Edges P

> 题意:构造新图G'，边数最短的满足若在G上n点能从点1走k步到达，则G'上也应同样满足；且不存在点n，G'上能走k步到达而在G上不能

我们先得知道一个性质，若定义**奇最短路**为从1到点n走奇数条边的最短路，**偶最短路**为从1到点n走偶数条边的最短路，则满足条件的G'的奇最短路以及偶最短路与G中相等

显然可知，因为知道若奇/偶最短路为x,则x+2、x+4...都可以通过先走出去再走回来构造出

我们就可以进入本题最ex的分类讨论了！

1. 图为二分图

可知一个点要么只有奇最短路，要么只有偶最短路，只用对最短路分层，则可知只用选n-1条边连成树即可

2. 图为非二分图(即既有奇最短路也有偶最短路)

假设点n的最短路(奇/偶)为二元组(x,y),__注意这里的x,y其实与奇偶没多大关系，因为显然为一奇一偶，这里的(x,y)为无序数对，后文默认x<y__ 

①$i\leftarrow j,(x_i,y_i)=(x_j+1,y_j+1)$

②$x+1<y.i\leftarrow j_1,j_2.(x_i,y_i)=(x_{j_1}-1,y_{j_1}+1)=(x_{j_2}+1,y_{j_2}-1)$

②$x+1=y.i\leftarrow j_1,j_2.(x_i,y_i)=(x_{j_1},y_{j_1})=(x_{j_2}+1,y_{j_2}-1)$，$i$可能等于$j_1$

我们可以发现若我们按照x+y排序，则①为~~跨膜运输~~，而②③为内部消耗

所以我们以x+y为第一关键字，x为第二关键字排序，从小往大贪心地选。大力讨论一下即可

```cpp
#include<bits/stdc++.h>
using namespace std;
# define ll long long
# define read read1<ll>()
# define Type template<typename T>
Type T read1(){
	T t=0;char k;bool vis=0;
	do (k=getchar())=='-'&&(vis=1);while('0'>k||k>'9');
	while('0'<=k&&k<='9')t=(t<<3)+(t<<1)+(k^'0'),k=getchar();
	return vis?-t:t;
}
# define fre(k) freopen(k".in","r",stdin);freopen(k".out","w",stdout)
struct B{
	int x,y;
	B(int _x=0,int _y=0):x(_x),y(_y){}
	bool operator <(const B &t)const{return x+y==t.x+t.y?y<t.y:x+y<t.x+t.y;}
	bool operator ==(const B &t)const{return x==t.x&&y==t.y;}
};
map<int,int>U[100015],S[100015];
struct E{int u,t;}G[400005];
int f[100005],s,m,tot,dis[100005][2],q[200005];
bool r[200005];vector<B>tem;
void add(int u,int v){
	G[++tot].u=v;G[tot].t=f[u];f[u]=tot;
	G[++tot].u=u;G[tot].t=f[v];f[v]=tot;
}
int main(){q[0]=1;r[0]=0;
	for(int T=read;T--;){
		s=read,m=read;tot=0;
		memset(f,0,s+1<<2);
		memset(dis,-1,s+1<<3);
		for(int i=1;i<=m;++i)add(read,read);
		for(int i=0;i<=s+5;++i)S[i].clear(),U[i].clear();
		dis[1][0]=0;
		for(int i=0,j=1;i!=j;++i){
			int n=q[i];
			for(int x=f[n];x;x=G[x].t)
				if(!~dis[G[x].u][!r[i]]){
					r[j]=!r[i];q[j]=G[x].u;++j;
					dis[G[x].u][!r[i]]=dis[n][r[i]]+1;
				}
		}int ans=0;
		if(!~dis[1][1])ans=s-1;
		else if(dis[1][1]==1)ans=s;
			else{tem.clear();
				for(int i=2;i<=s;++i){
					int x=dis[i][0],y=dis[i][1];
					if(y>x)swap(x,y);
					++S[x][y];tem.push_back(B(x,y));
				}S[dis[1][1]][0]=1;
				sort(tem.begin(),tem.end());
				B v(114514,-1);
				for(int i=0;i<tem.size();++i){
					if(v==tem[i])continue;
					v=tem[i];
					int cnt=S[v.x][v.y],h=S[v.x-1][v.y-1],p=U[v.x+1][v.y-1];
					if(!h)ans+=max(cnt-p,0)+(v.y+1<v.x?U[v.x][v.y]=cnt:cnt+1>>1);
					else if(!p)ans+=cnt;
					else ans+=max(cnt-p,0)+(v.y+1<v.x?U[v.x][v.y]=min(cnt,p):min(cnt,p)+1>>1);
				}
			}
		printf("%d\n",ans);
	}
	return 0;
}
```

题外话：现在看来其实也不是很难，主要是前面那个性质没想到，结果考试时就一直往生成函数上想，就GG了

---

## 作者：C20203030 (赞：7)

__题目描述__

[点此看题](https://www.luogu.com.cn/problem/P7417)

这道题基本不涉及任何算法，但是思维难度极高。

网上没有这道题的题解，我的思路是从官方题解那里学来的，希望能帮到你。

__解法__

首先讲一讲为什么我考试的时候会暴毙掉，因为我觉得最优解的构造是和原图紧密相关的，所以我在原树上搞，然后就凉了。因为这道题的提问方式是**构造一个新图**，没有人告诉你一定要在原图上面改，**所以在适当的时候一定要抛弃原图**。

---

首先可以求出数组 $a[i][0/1]$ 表示到 $i$ 的奇数最短路和偶数最短路，不难发现因为可以反复经过最近的一条边，所以两个图相等当且当且仅当跑出来的 $a$ 数组相等，$a$ 数组可以很容易 $O(n)$ 直接 $\tt bfs$ 求出。

求出原图的 $a$ 数组之后就不要管原图了，设 $h(i)=(\min(a[i][0/1]),\max(a[i][0/1]))$ 就表示按大小排的奇偶路径二元组，首先如果原图是二分图那么特判掉，答案是 $n-1$（因为二分图的情况 $a[i][0/1]$ 有一个没有意义，所以特判），然后我们来**考虑点 $i$ 合法的时候满足什么条件**，点 $1$ 太特殊了，所以我们暂时不考虑它，设 $h(i)=(x,y)$：

- 如果和 $j$ 连边就直接让他满足条件了，那么 $h(j)=(x-1,y-1)$
- 如果 $x+1<y$，同时和 $j_1,j_2$ 连边（一个点解决 $x$ 或者解决 $y$），则 $h(j_1)=(x-1,y+1),h(j_2)=(x+1,y-1)$
- 如果 $x+1=y$，同时和 $j_1,j_2$ 连边，则 $h(j_1)=(x-1,y+1),h(j_2)=(x,y)$

再来多解释下上面的结论，首先为什么情况这么唯一呢？因为 $\tt tly$ 巨佬告诉我们了一个三角形不等式(?)，也就是有边相连的点的最短路只会绝对值之差小于等于 $1$，那么就只用讨论 $x-1,x,x+1$ 这些情况，然后为了保证第一维小于等于第二维所以才讨论一下分出第二种情况和第三种情况。

现在考虑怎么用这个结论来做题吧，我们把 $(x,y)$ 相同的点分到一起，然后你发现情况 $2/3$ 的 $x+y$ 和一定，所以可以把 $x+y$ 一定的点划分成一层，同一层的按 $x$ 排序，这样 $h(j)$ 就是连向以前层的，$h(j_1)$ 是连向同层但是是之前的点，还是分情况来讨论，设 $S(x,y)$ 表示 $h(i)=(x,y)$ 这类点的点数，那么有这样几种情况：

> 下面就直接用贪心做了，因为第一种情况只用连一条边，而二三种情况可能会连两条边，依据这个为主要思想贪心即可。

- $S(x-1,y-1)\not=0,S(x-1,y+1)=0$，那么直接无脑连向 $(x-1,y-1)$ 即可。
- $S(x-1,y-1)=0,S(x-1,y+1)\not=0$，那么拿到以前 $(x-1,y+1)$ 连向 $(x,y)$ 的边数 $cnt$，然后增加 $\max(0,S(x,y)-cnt)$ 即可，再根据 $x,y$ 的关系可以知道是连向 $(x,y)$ 还是 $(x+1,y-1)$，如果是连向 $(x+1,y-1)$ 那么就修改一下它的 $cnt$ 即可。
- $S(x-1,y-1)\not=0,S(x-1,y+1)\not=0$，那么以前有的 $cnt$ 条边只需要再增加一条边就可以使得这个点合法，而且会让 $(x+1,y-1)$ 的 $cnt$ 增加，所以我们优先执行这个操作。如果这 $cnt$ 条边用完了那么我们连向 $(x-1,y-1)$ 即可。

具体实现就写一个 $\tt map$ 即可，还有就是上面都没有考虑 $1$ 这个特殊的点，如果 $1$ 有自环的话那么需要特判，直接输出 $n$ 即可。~~然后就耐性地讨论吧~~，时间复杂度 $O(n\log n)$

```c++
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;
#define pii pair<int,int>
#define make make_pair 
const int M = 200005;
const int inf = 1e9;
int read()
{
	int x=0,f=1;char c;
	while((c=getchar())<'0' || c>'9') {if(c=='-') f=-1;}
	while(c>='0' && c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int T,n,m,k,ans,tot,f[M],a[M][2];
map<pii,int> mp,cnt;
struct edge
{
	int v,next;
	edge(int V=0,int N=0) : v(V) , next(N) {}
}e[2*M];
struct node
{
	int x,y;
	bool operator < (const node &b) const
	{
		if(x+y!=b.x+b.y) return x+y<b.x+b.y;
		return x<b.x;
	}
}b[M];
void bfs()
{
	for(int i=1;i<=n;i++)
		for(int j=0;j<=1;j++)
			a[i][j]=inf;
	queue<int> q;
	q.push(1);a[1][0]=0;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=f[u];i;i=e[i].next)
		{
			int v=e[i].v;
			if(a[u][0]<inf && a[v][1]==inf)
			{
				a[v][1]=a[u][0]+1;
				q.push(v);
			}
			if(a[u][1]<inf && a[v][0]==inf)
			{
				a[v][0]=a[u][1]+1;
				q.push(v);
			}
		}
	}
}
void solve()
{
	bfs();
	if(a[1][1]==1)//1有自环
	{
		printf("%d\n",n);
		return ;
	}
	for(int i=1;i<=n;i++)//是二分图 
		if(a[i][0]==inf || a[i][1]==inf)
		{
			printf("%d\n",n-1);
			return ;
		}
	for(int i=1;i<=n;i++)//把每个点分类 
	{
		pii t=make(a[i][0],a[i][1]);
		if(t.first>t.second) swap(t.first,t.second);
		mp[t]++;
		if(mp[t]==1)//加到数组上面排序
			b[++k]=node{t.first,t.second};
	}
	sort(b+1,b+1+k);
	for(int i=1;i<=k;i++)
	{
		int x=b[i].x,y=b[i].y;
		pii t=make(x,y),t3=make(x+1,y-1);
		pii t1=make(x-1,y-1),t2=make(x-1,y+1);
		if(mp[t1]>0 && mp[t2]==0)
			ans+=mp[t];//直接连上去
		if(mp[t1]==0 && mp[t2]>0)
		{
			ans+=max(0,mp[t]-cnt[t]);//补连向j1的边
			if(x+1==y)//是第三种情况
				ans+=(mp[t]+1)/2;//上取整 
			else
			{
				ans+=mp[t];//连到(x+1,y-1)去
				cnt[t3]+=mp[t]; 
			}
		}
		if(mp[t1]>0 && mp[t2]>0)
		{
			if(mp[t]>cnt[t])
				ans+=mp[t]-cnt[t];//连(x-1,y-1)
			cnt[t]=min(cnt[t],mp[t]);//别忘了写这个 
			if(x+1==y)
				ans+=(cnt[t]+1)/2;
			else
			{
				ans+=cnt[t];
				cnt[t3]+=cnt[t];
			}
		}
	}
	printf("%d\n",ans);
}
int main()
{
	//freopen("minimizing.in","r",stdin);
	//freopen("minimizing.out","w",stdout);
	T=read();
	while(T--)
	{
		mp.clear();
		cnt.clear();
		n=read();m=read();
		tot=1;k=0;ans=0;
		for(int i=1;i<=n;i++)
			f[i]=0;
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read();
			e[++tot]=edge(v,f[u]),f[u]=tot;
			e[++tot]=edge(u,f[v]),f[v]=tot;
		}
		solve();
	}
}
```



---

## 作者：MaxFwl (赞：4)

由于是无向图，只要在一条边上来回跳路径长度就会加二，所以题目转化为求一张边数最少的图使得该图与原图每个点奇偶最短路长度相等，这个性质是类似 P5663 的。

考虑先 bfs 求出每个点的奇偶最短路，如果该图为二分图，即到每个点的路径长度奇偶性唯一，则直接建最短路树，显然最优，下面考虑其余情况。

定义当一个点奇偶最短路分别为 $x$ 和 $y$ 时，该点表示为 $(x, y)$，考虑到可能的最优的情况应该只有两种：

+ $(x, y)$ 点由一个 $(y - 1, x - 1)$ 点转移，需要一条边。

+ $(x, y)$，由一个 $(y - 1, x + 1)$ 点与一个 $(y + 1, x - 1)$ 点转移来，需要两条边。

显然上面那种更优，但当对于一个 $(x, y)$ 点，不存在任何一个 $(y - 1, x - 1)$ 点时，就只能选下面那种了，这是本题贪心的基本思想。

考虑到 $x, y$ 互换，这样的形式很难求解，于是改变定义：定义当一个点奇偶最短路为 $x$ 和 $y$ 时，该点表示为 $(x, y)(x > y)$。

于是如果把 $x + y$ 作为行数，$y$ 作为列数，可以发现转移要么是从上方的 $(x - 1, y - 1)$ 点连边，要么是从左边的 $(x + 1, y - 1)$ 和右边的 $(x - 1, y + 1)$ 各连一条边。

考虑贪心，可以将所有的点按照先行后列的顺序排序，这样在贪心的时候就只需要考虑左边的点是否按第二种情况连边，若有，就只需要满足这些点的需求。

剩下的部分直接贪心就可以了，即若有至少一个 $(x - 1, y - 1)$ 点，就按第一种情况连边，否则按第二种情况连边。

考虑转移边界，若有 $x = y + 1$，则向右连边变为 $(x + 1, y - 1)$，发现不满足定义，继续分析，发现相当于向自己连自环边，由于是无向边，一次可以满足两个连边的需求。

考虑具体实现，可以使用两个 map，一个记录点数，一个记录需求量，排序后贪心地转移即可，总复杂度 $O(Tm + Tn \times \log{n})$。

注意边 $(1, 1)$ 出现而第一个点并不会计算贡献的情况要特判，注意奇偶最短路上限 $> n - 1$ 要开大数组多清空。

[code](https://www.luogu.com.cn/paste/2kjt41rx)。

---

## 作者：Anonymely (赞：3)

真的很难。

首先由于是无向图，可以对一条边反复横跳使得最短路 $+2$，故只需要考虑奇偶最短路。

由于图联通，若没有奇环，则所有点要么只有奇最短路，要么只有偶最短路，只需要构造最短路树即可。

考虑一般情况，将二元组用 $(x,y),x<y$ 表示。

考虑 $(x,y)$ 的连边：

1. $(x-1,y-1)$
2. $(x-1,y+1)$ 和 $(x+1,y-1)$

解释一下第二个，就是 $x,y$分别从不同的点跑过来最短，而由于要满足 $dis_u+1 \ge dis_v$，第二维限制最多 $+1$。

当 $x+1=y$ 时 $x+1 > y-1$，$(y-1,x+1)=(x,y)$。

我们要最小化边数量，贪心考虑一定是要第一种最优，而第二种的边发现都满足 $x+y=d$，故按照 $x+y$ 分层贪心。

记 $c$ 为 $(x-1,y+1)$ 对 $(x,y)$ 有几条链接。对于 $(x,y)$：

1. $siz(x,y) \ge c$，往 $(x-1,y+1)$ 连 $c$ 条，若存在 $(x-1,y-1)$，则往上连 $c - siz(x,y)$ 条边，否则全往 $(x+1,y-1)$ 连。
2. $siz(x,y) \le c$，往 $(x-1,y+1)$ 连 $siz(x,y)$ 条，往 $(x+1,y-1)$ 连 $c$ 条。

对于上述情况，若出现不存在 $(x+1,y-1)$，则说明这个点是全局结尾或满足 $x+1=y$，此时若 $x+1=y$ 则向自己连 $\frac{c}{2}$ 条边，否则 $c$ 条。

不难发现上述贪心最优。


```cpp
#include <bits/stdc++.h>
using namespace std;

#define QwQ01AwA return 0
#define ll long long
#define look_time cerr << 1.0 * clock() / CLOCKS_PER_SEC << '\n'
template <typename T> void ckmax(T &x, const T y) {x = max(x, y);}
template <typename T> void ckmin(T &x, const T y) {x = min(x, y);}

const int N = 1e5 + 5;
int n, m;
vector <int> e[N];
int dis[N][2];

void bfs() {
	for (int i = 1; i <= n; i++) dis[i][0] = dis[i][1] = 1e9;
	queue < array <int, 2> > q;
	q.push({1, 0}), dis[1][0] = 0;
	while (!q.empty()) {
		auto [u, o] = q.front();
		q.pop();
		for (auto v : e[u]) {
			if (dis[v][o ^ 1] > dis[u][o] + 1) {
				dis[v][o ^ 1] = dis[u][o] + 1;
				q.push({v, o ^ 1});
			}
		}
	}
}

map < pair <int, int>, int> siz;

void solve() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) e[i].clear();
	for (int i = 1, u, v; i <= m; i++) {
		cin >> u >> v;
		e[u].push_back(v), e[v].push_back(u);
	}
	bfs();
	for (int i = 1; i <= n; i++) {
		if (dis[i][0] == 1e9 || dis[i][1] == 1e9) {
			cout << n - 1 << '\n';
			return;
		}
	}
	siz.clear();
	vector < pair <int, int> > w;
	for (int i = 1; i <= n; i++) {
		if (dis[i][0] > dis[i][1]) swap(dis[i][0], dis[i][1]);
		siz[{dis[i][0], dis[i][1]}]++;
		w.push_back({dis[i][0] + dis[i][1], dis[i][0]});
	}
	sort(w.begin(), w.end(), [](auto u, auto v) {return u.first == v.first ? u.second < v.second : u.first < v.first;});
	w.erase(unique(w.begin(), w.end()), w.end());
	int ans = 0, lst = 0;
	for (auto [y, x] : w) {
		y -= x;
		int cc = siz[{x, y}];
		if (lst <= cc) {
			ans += bool(x) * cc;
			if (!siz.count({x - 1, y - 1})) lst = cc;
		} else ans += lst, lst = cc;
		if (!siz.count({x + 1, y - 1})) {
			if (x + 1 != y) ans += lst;
			else ans += (lst + 1) / 2;
			lst = 0;
		}
	}
	cout << ans << '\n';
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin >> t;
	while (t--) solve();
	QwQ01AwA;
}
```

---

## 作者：ღꦿ࿐ (赞：3)

首先路径不要求是简单的所以可以通过反复走一条边使得路径长度 $+2$。存在长度为 $x$ 的路径意味着一定存在长度为 $x+2$ 的路径，所以我们只关心一个点的奇最短路和偶最短路。

如果原图是一个二分图，那么每个点要么只存在奇路径要么只存在偶路径，所以只关心最短路。按照 $dis_i$ 分层后，每个点连接到上一层即可，答案为 $n-1$。

接下来只考虑原图不是二分图的情况：令到该点的最短路长度为 $x_i$，与最短路径奇偶不同的最短路长度为 $y_i$，我们需要使得新图所有 $(x_i,y_i)$ 和原图相同。

首先有一条边连接的 $(x_u,y_u),(x_v,y_v)$ 一定有 $|x_u-x_v|\leq 1 ,|y_u-y_v| \leq 1$，否则可以用较小者去更新较大者。


所以一个点  $(x,y)$ 只可能和 $(x\pm 1,y\pm 1)$ 连边（当然 $x=y-1$ 时 $(x+1,y-1)$ 为 $(x,y)$ 自己）。


考察一组 $(x,y)$ 的由来，由最短路的构成，一定满足以下两种情况之一：

- 从 $(x-1,y-1)$ 转移来。 
- 从 $(x-1,y+1)$ 得到 $x$，从 $(x+1,y-1)$ 得到 $y$（当 $x=y-1$ 时 $(x+1,y-1)$ 为 $(x,y)$ 自己）。

$(x+1,y+1)$ 可连可不连（对于这个点来说）。


特殊情况是 $x=0$ 即 $1$ 号点不需要向  $(x-1,y+1)$ 连边。

然后接下来的思路很妙：考虑前面二分图按照 $dis$ 分层，而现在难以按照 $dis$ 分层了，分层的目的是为了将原图分成若干个相对较为独立的部分，现在考虑按照  $x+y$ 分层，于是现在只需要考虑每层向上一层连当边和向这一层的前后连的边。


称 $(x-1,y-1)$ 为 $(x,y)$ 的“上面”，$(x-1,y+1)$ 为“左边”，$(x+1,y-1)$ 为“右边”，每个点要么连上面，要么同时连左右（右可能是自环）。

接下来考虑一层一层做。

考虑每层的样子一定形如有若干段，如果不是末尾可以连接自环的段的话一定两个端点都可以向上连。如果末尾可以连接自环那么末尾可能不能向上。（因为这些 $(x,y)$ 是由原图求出来的，所以一定存在一种合法的构造，不会存在一个点上面左右都不能连接），如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/naebrbl9.png)


如果一段中的所有点都可以向上连，最优的办法肯定是所有点都向上连，因为这样只需要消耗一条边。

如果一坨点不能向上连，那么一定会向左右连边。考虑从左到右依次处理每坨点：

如果这坨点有一些点已经被左侧连边了，那么连接这些点向右的边会更优，因为只需要连接一条边且能够为右边的点提供一条边。否则一定向上连会更优，向上连只会消耗一条边，而向左右连需要消耗两条边，可以为右边提供一条边，如果右边需要一条边会在考虑到右边的时候连接左边。

证明就是考虑将一坨连接到父亲的点且没有连接左侧的点转为连接到左侧右侧一定是不优的，因为可能可以将一段向父亲连接的点转成向左右连边，但是最左侧的点仍然必须选择向父亲连边，所以无法更优，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/sozbg6vl.png)

其根本原因在于向左的边一直传递到最左边坨无法减少连边数（最左点必须向上连）而向右的边可能能够在最右边坨连接同坨中的点，一次消耗两个点。

所以分别考虑每层的每段，具体的连边策略如下：

每段的第一坨点，必须来源于上方（连上面）。

如果这坨点有一部分被左侧连接了，那么直接将这坨点连接到右边，采用连接左右。
	
如果这坨点剩下的可以连接父亲，就连接父亲，否则连接左右两侧，我们在上面分析了，你不会因为这条连向左边的边而将左侧点从连接上方反悔为连接左右。

时间复杂度 $O(n + m)$。











---

## 作者：Kevin090228 (赞：3)

### Minimizing Edges

容易想到这实际上是要求到每个点的偶最短路和奇最短路长度不变。

我们用点对 $(x,y)$ 表示一个点 $u$，其中 $x,y$ 分别是到 $u$ 的奇/偶最短路长度。为了唯一性考虑，不妨设 $x<y$。

先不考虑结点 $1$。让一个点对 $(x,y)$ 在新图中满足要求，有两种方法：

1. 让它和一个 $(x-1,y-1)$ 点连边；
2. 让它和 $(x-1,y+1)$ 点和 $(x+1,y-1)$ 点各连一条边。

注意有一个特殊情况：在 $(x,y)$ 满足 $x+1=y$ 时，实际上 $(x+1,y-1)$ 是 $(y-1,x+1)$，即 $(x,y)$。

设 $f(x,y)$ 表示点对 $(x,y)$ 的出现次数。考虑以 $x+y$ 为第一维从大到小，$x$ 为第二维从小到大贪心。对于一个点：

1. 存在 $(x-1,y-1)$ 的点，且不存在 $(x-1,y+1)$ 的点：直接将其与 $(x-1,y-1)$ 点连边即可，代价 $1$。

2. 不存在 $(x-1,y-1)$ 的点，但存在 $(x-1,y+1)$ 的点：设考虑点 $(x-1,y+1)$ 时，它向 $(x,y)$ 连的边数为 $c$。我们将 $c$ 修改到 $\max(c,f(x,y))$，然后向 $(x+1,y-1)$ 连 $f(x,y)$ 条边即可。

3. $(x-1,y-1)$ 和 $(x-1,y+1)$ 都存在：

   这时候我们分析一下各种操作的代价，有：

   - 方法一：代价为 $1$。
   - 方法二：利用之前 $(x-1,y+1)$ 连过来的边时：代价为 $1$，且能向后贡献一条边；否则：代价为 $2$。

   所以容易想到先利用之前的边，再用方法一。

4. $(x-1,y-1)$ 和 $(x-1,y+1)$ 都不存在：~~那你在搞笑~~。因为原图的最短路同样只能由上文两种方式得来，所以这种情况不存在。

实现似乎不是很难，先 BFS 一下，然后用 map 啥的维护向后连了多少边即可。

时间复杂度 $O(n\log n)$ 或 $O(n)$。

---

## 作者：mskqwq (赞：2)

我们只关系 $1$ 到每个点的奇偶最短路，设 $1$ 到 $u$ 的奇偶最短路分别为 $d_{u,0/1}$，首先特判两种简单的情况：二分图和 $1$ 有自环，答案分别为 $n-1$ 和 $n$。

可以把每个奇偶最短路相同的点放到一个集合 $(x,y)$，其中 $x,y$ 表示奇偶最短路的较小值和较大值。思考怎么构造出 $(x,y)$，第一种情况是 $(x,y)$ 连向一个 $(x-1,y-1)$，$(x,y)$ 被同时贡献。还有一种情况是分别被贡献，也就是连向了两个集合 $(x-1,y+1)$ 和 $(x+1,y-1)$，因为讨论下奇偶可以发现不可能连 $(x-1,y)$ 或者 $(x,y-1)$。值得注意的是当 $x+1=y$ 时，连向 $(x+1,y-1)$ 就相当于在 $(x,y)$ 内部连边。 

将所有集合按 $x+y$ 分层，同一层内的集合按 $x$ 从大到小排序，然后每个集合只会和同层的或者上一层的连边。我们有一个贪心策略：对于一个集合 $(x,y)$，如果存在 $(x-1,y-1)$ 就全部连向它，否则向它左右两边的连边。

但这还不够，考虑 $(x,x+1)$ 这个集合，若它右边的集合往它连了 $k$ 条边，那么只需要在 $(x,x+1)$ 内部连 $\lceil \frac k 2 \rceil$ 条边即可满足要求，因为一条边可以解决两个点。所以上面的贪心策略还需要补充一点：尽量把在同一层内的连边推到 $(x,x+1)$ 这个集合内。

我们按层考虑，同一层内从右往左遍历集合，记 $k$ 表示上一个集合**将要**向当前的集合的连边数量，接着做一些分讨，先假设 $x+1 \neq y$。

若上一个集合 $(x-1,y+1)$ 不为空，那么在 $(x,y)$ 内取 $k$ 个点连回去，注意这 $k$ 个点还要接着向 $(x+1,y-1)$ 内的点连边，然后把剩下的点连向 $(x-1,y-1)$。注意还要分讨 $(x,y)$ 的数量和 $k$ 的大小关系来更新答案和新的 $k$。

否则， $(x,y)$ 内的所有点都要向下一个和上一个集合内连边。依旧分讨 $(x,y)$ 的数量和 $k$ 的大小关系做更新。

还要一种情况是 $(x+1,y-1)$ 为空，我们就不能再向它连边，所有的边只能连向 $(x-1,y-1)$。

最后 $x+1=y$ 的情况差不多类似，只是它不能继续向下一个集合内连边，只能在自己内部连。

```cpp
#include <set>
#include <map>
#include <queue>
#include <ctime>
#include <cstdio>
#include <vector>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#define fi first
#define se second
#define ep emplace
#define MISAKA main
#define mp make_pair
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define rg(x) x.begin(),x.end()
#define pc(x) __builtin_popcount(x)
#define mems(a,x) memset(a,x,sizeof(a))
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define _rep(i,a,b) for(int i=(a);i>=(b);--i)
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define FIO(FILE) freopen(FILE".in","r",stdin),freopen(FILE".out","w",stdout)
using namespace std;
bool __st;
inline int read(){
    char c=getchar();int f=1,x=0;
    for(;c<48||c>57;c=getchar())if(c=='-') f=-1;
    for(;47<c&&c<58;c=getchar()) x=(x<<3)+(x<<1)+(c^48);
    return x*f;
}
const int N=2e5+10,mod=998244353;
int n,m,ans,d[N][2];vector<int> g[N];
unordered_map<int,int> cnt[N];
void misaka(){
    rep(i,0,2*n) g[i].clear(),cnt[i].clear();ans=0;
    n=read(),m=read();
    rep(i,1,n) d[i][0]=d[i][1]=1e9;
    rep(i,1,m){
        int u=read(),v=read();
        g[u].eb(v);g[v].eb(u);
    }
    queue<tuple<int,int,int>> q;
    q.ep(1,0,0);d[1][0]=0;
    while(!q.empty()){
        auto [u,t,D]=q.front();q.pop();
        for(int v:g[u])if(d[v][t^1]>D+1)
            d[v][t^1]=D+1,q.ep(v,t^1,D+1);
    }
    if(d[1][1]==1e9){printf("%d\n",n-1);return;}
    if(d[1][1]==1){printf("%d\n",n);return;}
    vector<pii> s;
    rep(i,1,n){
        int x=d[i][0],y=d[i][1];
        if(x>y) swap(x,y);
        if(++cnt[x][y]==1) s.eb(x,y);
    }
    sort(rg(s),[](pii a,pii b){return mp(a.fi+a.se,a.fi)<mp(b.fi+b.se,b.fi);});
    rep(i,0,(int)s.size()-1){
        int nw=s[i].fi+s[i].se,j=i,k=0;
        while(j+1<s.size()&&s[j+1].fi+s[j+1].se==nw) j++;
        rep(p,i,j){
            auto [x,y]=s[p];int c=cnt[x][y];
            if(!x) continue;
            ans+=k;
            if(x+1==y){
                if(cnt[x-1][y-1]) ans+=(min(c,k)+1>>1)+max(0,c-k);
                else ans+=max(0,c-k)+(c+1>>1);
                break;
            }
            if(cnt[x-1][y-1]) ans+=max(0,c-k),k=min(k,c);
            else ans+=max(0,c-k),k=c;
            if(k&&!cnt[x+1][y-1]) ans+=k;
        }
        i=j;
    }
    printf("%d\n",ans);
}
bool __ed;
signed MISAKA(){
    #ifdef LOCAL_MSK
    atexit([](){
    debug("\n%.3lfs  ",(double)clock()/CLOCKS_PER_SEC);
    debug("%.3lfMB\n",abs(&__st-&__ed)/1024./1024);});
    #endif
    
    int T=read();
    while(T--) misaka();
    return 0;
}

```

---

## 作者：一粒夸克 (赞：1)



### Declarations：

给定一张图，令 $f_{G}(a,b)$ 表示图 $G$ 中点 $1$ 到 $a$ 是否有一条长度为 $b$ 的边。

要求一张图 $G'$ 使得 $\forall f_{G'}(a,b)=f_{G}(a,b)$，最小化  $G'$ 的边数。

### solution：

首先考虑 $f_{G}$ 的决定因素。

如果有一条从 $1$ 到 $u$ 的路径，长度为 $k$，那么我们只要在路径上的某条边上迂回一下，就可以得到一条长度为 $k+2$ 的路径。

那么显然，如果点 $1$ 到 $u$ 的奇数长度的最短路为 $x$，偶数最短路为 $y$，那么有：
$$ \left\{
\begin{aligned}

 f_{G}(u,2 * n+1)  & =[2*n+1>x]\\
 
 f_{G}(u,2 * n)   & =[2*n>y]\\
\end{aligned}
\right.
$$


因此，只要分别求出了 $1$ 到每个点的奇数最短路和偶数最短路，就可以确定整张图的 $f_{G}$ 。

保证了 $f_{G}$ 后，我们考虑如何最小化边数。

因为奇数最短路与偶数最短路一定一个是奇数一个是偶数。

我们忽略奇数最短路与偶数最短路的顺序，另大的为 $x$ 小的为 $y$，把 $(x,y)$ 撒到二维坐标系里。

因为 $(x,y)$ 一奇一偶，因此不会有两个点是相邻的，所有在原图上相连的点与在新图上可能相连的点，都是在对角线上相邻的。

那么可能与点 $(x,y)$ 相邻的点时 $(x-1,y-1)$、$(x+1,y-1)$、$(x-1,y+1)$、$(x+1,y+1)$。

$(x+1,y+1)$显然不会对 $(x,y)$ 产生贡献，只是 $(x,y)$ 可能会作为 $(x+1-1,y+1-1)$ 对 $(x+1,y+1)$ 产生贡献。

如果点 $(x,y)$ 有 $(x-1,y-1)$ 可以与它相连，那么只要连了这个点，其它的就不用管了。

如果没有，那它就只能分别于 $(x-1,y+1)$ 和 $(x+1,y-1)$ 相连。

对于 $x=y+1$ 的点，$(x-1,y+1)$ 还是它自己，因此要连自环。

用两个 map 维护一下即可。

**PS：以上算法针对的是一般图，对于二分图和 $1$ 号点有自环的图，最优解就是它的最短路树，需要特判**

### code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n,m;
int dis[300005],pre[300005];
int ver[400005],ne[400005],head[400005],cnt;
inline void link(int x,int y){
	ver[++cnt]=y;
	ne[cnt]=head[x];
	head[x]=cnt;
}
queue<int> q;
map<int,int> mp[400005],mp2[400005];
struct data{
	int x,y;
	data(int _x,int _y){x=_x;y=_y;}
	inline bool operator <(const data &b)const{
		if(x+y!=b.x+b.y)return x+y<b.x+b.y;
		return y<b.y;
	}
	inline bool operator ==(const data &b)const{
		return x==b.x&&y==b.y;
	}
};
vector<data> vec;
int a[200005];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);
		int ans=0;vec.clear();//因为可以反复走，有的点的最短路会比n大
		for(int i=1;i<=n;i++)dis[i<<1]=dis[i<<1|1]=1e9;
		for(int i=1;i<=2*n;i++)mp[i].clear();
		for(int i=1;i<=2*n;i++)mp2[i].clear();
		for(int i=1;i<=n;i++)head[i]=0;cnt=1;
		for(int i=1;i<=m;i++){
			int x,y;
			scanf("%d%d",&x,&y);
			link(x,y);link(y,x);
		}
		dis[2]=0;
		q.push(2);
		while(!q.empty()){
			int w=q.front();q.pop();
			int is=(w&1),x=(w>>1);
			for(int i=head[x];i;i=ne[i]){
				int u=ver[i];
				if(dis[u<<1|(is^1)]>dis[w]+1){
					dis[u<<1|(is^1)]=dis[w]+1;
					pre[u<<1|(is^1)]=(i>>1);
					q.push(u<<1|(is^1));
				}
			}
		}
		bool is=1;
		for(int i=1;i<=n;i++)if(dis[i<<1]!=1e9&&dis[i<<1|1]!=1e9)is=0;
		if(dis[3]==1e9){
			printf("%d\n",n-1);
			continue;
		}
		else if(dis[3]==1){
			printf("%d\n",n);
			continue;
		}
		else{
			for(int i=2;i<=n;++i){
				int x=dis[i<<1],y=dis[i<<1|1];
				if(y>x)swap(x,y);mp[x][y]++;
				vec.push_back(data(x,y));
			}mp[dis[3]][0]=1;
			sort(vec.begin(),vec.end());
			data tmp=data(-1,-1);
			for(vector<data>::iterator it=vec.begin();it!=vec.end();it++){
				if(tmp==(*it))continue;
				tmp=(*it);
				int cnt=mp[tmp.x][tmp.y],pre=mp[tmp.x-1][tmp.y-1];
				int nxt=mp2[tmp.x+1][tmp.y-1];
				if(!pre)ans+=max(cnt-nxt,0)+(tmp.y+1!=tmp.x?mp2[tmp.x][tmp.y]=cnt:(cnt+1)>>1);
				else if(!nxt)ans+=cnt;
				else ans+=max(cnt-nxt,0)+(tmp.y+1!=tmp.x?mp2[tmp.x][tmp.y]=min(cnt,nxt):(min(cnt,nxt)+1)>>1);
			}
		}
		printf("%d\n",ans);
	}

	return 0;
}
```



---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/P7417)

**题目大意**

> 给定 $n$ 个点 $m$ 条边的无向图，构造一张边数最少的图使得 $\forall (u,x)$，两图中同时存在或不存在 $1\to u$ 长度为 $x$ 的路径。
>
> 数据范围：$n\le 10^5,m\le 2\times 10^5$。

**思路分析**

由于我们可以在同一条边上来回移动，那么只要到每个点奇数长度和偶数长度最短路相同即可。

设这两条最短路为 $(x,y)$，其中 $x<y$，那么这样的一个点只能和 $(x-1,y-1)$ 连接，或者同时连接 $(x+1,y-1),(x-1,y+1)$。

特别的，如果 $y=x+1$，那么连接另一个 $(x,y)$ 以及一个 $(x-1,y+1)$。

我们可以把所有点按 $x+y$ 分组，同一组内的问题相对独立，按 $x$ 从小到大扫描：

首先如果存在 $(x-1,y-1)$ 那么优先连接肯定更优，否则连接 $(x-1,y+1)$ 和 $(x+1,y-1)$。

如果 $(x+1,y-1)$ 已经和当前点连接，那么继续连接 $(x-1,y+1)$ 而非 $(x-1,y-1)$，因为此时不断连接到 $(x,x+1)$，只需要一条边就能解决两个点。

模拟上述过程即可，注意特判二分图和 $1$ 有自环的情况。

时间复杂度 $\mathcal O(n\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+5,inf=1e9;
vector <int> G[MAXN];
map <int,int> f[MAXN],g[MAXN];
int n,m,d[MAXN][2];
void solve() {
	scanf("%d%d",&n,&m);
	for(int i=0;i<=n;++i) f[i].clear(),g[i].clear(),G[i].clear(),d[i][0]=d[i][1]=inf;
	for(int i=1,u,v;i<=m;++i) scanf("%d%d",&u,&v),G[u].push_back(v),G[v].push_back(u);
	queue <array<int,2>> Q; d[1][0]=0,Q.push({1,0});
	while(Q.size()) {
		int u=Q.front()[0],r=Q.front()[1]^1; Q.pop();
		for(int v:G[u]) if(d[v][r]==inf) d[v][r]=d[u][r^1]+1,Q.push({v,r});
	}
	if(d[1][1]==inf) return printf("%d\n",n-1),void();
	if(d[1][1]==1) return printf("%d\n",n),void();
	vector <array<int,2>> P;
	for(int i=1;i<=n;++i) {
		int x=min(d[i][0],d[i][1]),y=max(d[i][0],d[i][1]);
		if(!f[x][y]++&&i>1) P.push_back({x+y,x});
	}
	int ans=0;
	sort(P.begin(),P.end());
	for(auto it:P) {
		int x=it[1],y=it[0]-it[1],sz=f[x][y],pr=g[x-1][y+1];
		ans+=max(0,sz-pr); //to right or up
		if(f[x-1][y-1]) sz=min(sz,pr);
		ans+=(y==x+1?(sz+1)/2:g[x][y]=sz); //to left
	}
	printf("%d\n",ans);
}
signed main() {
	int _; scanf("%d",&_);
	while(_--) solve();
	return 0;
}
```

---

## 作者：wht_1218 (赞：0)

## Description

一个有 $N$ 个结点的无向图 $G$，可能包含自环，不包含重边，一条边可以重复走。   
构造一个尽可能小的图 $G'$，使得对于任意 $a,b$，结点 $1$ 至结点 $a$ 在 $G,G'$ 中均存在一条路径的长度为 $b$。

## Solution

有点恶心的分类讨论，老师讲完再看题解然后琢磨。

题目中说一条边可以走多次，所以我们用一个二元组 $(x,y)$ 表示，$x$ 为奇数条边的最短路，$y$ 为偶数条边的最短路。

求最短路直接使用 `bfs` 即可。

我们需要提前判断二分图与自环的情况。

我们把 $(x,y)$ 相同的二元组归在一个集合，$(x,y)$ 可以连向 $(x-1,y-1)$ 或者连向 $(x-1,y+1)$ 和 $(x+1,y-1)$ 这两个集合这一部分可以分类讨论。在 $x+1=y$ 时需要单独讨论，读者可以先自己手搓几个样例验证。默认在接下来的分类讨论里 $x+1\neq y$。

我们可以把这张图按照 $x+y$ 分层，每个集合按 $x$ 从大到小排序。（当然你也可以从小到大，只是为了符合接下来的讨论）。

对于一个集合 $(x,y)$，我们优先把边连至 $(x-1,y-1)$，其次考虑同层连边，此时尽量连至相邻集合 $(x,x+1)$，因为一条边“控制”两个点。注意 $(x-1,y-1)$ 的集合**为空时**不能连边，其他集合同理。

若 $(x-1,y+1)$ 不为空，则从 $(x,y)$ 中取出 $k$ 个点连向 $(x-1,y+1)$ 和 $(x+1,y-1)$，剩下的点连向 $(x-1,y-1)$ 即可。若 $(x-1,y+1)$ 为空时，所有点直接连向 $(x+1,y-1)$。

对于相邻的集合 $(x,x)$ 与 $(x,x+1)$，若 $(x,x+1)$ 连了 $k$ 条边，$(x,x)$ 只需供出 $\lceil \frac k 2 \rceil$ 个点即可。

对于 $x+1=y$ 时相当于内部连边，但**只能内部连边**。

代码有点抽象。。。

```cpp
#ifndef _CPP_FILE
#define _CPP_FILE
#include<bits/stdc++.h>
using namespace std;
const int TI=1;
const long long TL=1ll;
const double TD=1.0;
const long double TLD=1.0;
const double eps=1e-6;
const long double leps=1e-12;
#define il inline
#define re register
#define rei register int
il int max(rei a,rei b){return a>b?a:b;}
il int min(rei a,rei b){return a<b?a:b;}
il int abs(rei x){return x>0?x:-x;}
#define imx INT_MAX
#define imn INT_MIN
#define lmx LLONG_MAX
#define lmn LLONG_MIN
#define nmx (N)
#define nmn (-N)
#define umap unordered_map
#define pii pair<int,int>
#define mset multiset
/* 2025 UPD*/
//#define w_fread

#define ll long long
#define F(i,x,y,z) for(rei (i)=(x);(i)<=(y);(i)+=(z))
#define rep(i,x,y) for(rei (i)=(x);(i)<=(y);++(i))
#define per(i,x,y) for(rei (i)=(x);(i)>=(y);--(i))
#define allstl(v) (v).begin(),(v).end()
#define allarr(v,n) (v)+1,(v)+(n)+1
#define Mios ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define inputarr(len,a) rep(i,1,(len))cin>>a[i]
#define printarr(len,a) rep(i,1,(len))cout<<a[i]<<' '
#define rinputarr(len,a) per(i,(len),1)cin>>a[i]
#define rprintarr(len,a) per(i,(len),1)cout<<a[i]<<' '
#define pb push_back
#define eb emplace_back
#define pob pop_back
#define mkp make_pair
il void tmx(rei &x,rei y){x=max(x,y);return;}
il void tmn(rei &x,rei y){x=min(x,y);return;}
#define arrmx(to,l,r,a) rep((i),(l),(r))to=max(to,a[i]);
#define arrmn(to,l,r,a) rep((i),(l),(r))to=min(to,a[i]);
#define fi first
#define se second
#define bg begin
#define ed end
#define rbg rbegin
#define red rend
#define FILEIO(s) freopen(s,"r",stdin),freopen(s,"w",stdout);
#define ump unordered_map
#define vi vector<int>
#define vpii vector<pii>
#define mkt make_tuple

#ifdef w_fread
#undef Mios
#undef inputarr
#undef printarr
#undef rinputarr
#undef rprintarr
namespace iofast{
	template<typename T>
	il T read(){
		re T x=0;
		bool f=0;
		char c=getchar();
		while(c<'0'||c>'9')c=getchar(),f=(c=='-'?1:f);
		while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();
		return f?-x:x;
	}
	template<typename T>
	il void read(re T &x){
		x=0;
		re bool f=0;
		char c=getchar();
		while(c<'0'||c>'9')c=getchar(),f=(c=='-'?1:f);
		while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();
	}
	template<typename T>
	il void write(const re T &x){
		x>9?write(x/10):void(0);
		putchar(x%10+'0');
	}
}
#define Mios ;
#define inputarr(len,a) rep(i,1,(len))iofast::read(a[i])
#define printarr(len,a) rep(i,1,(len))iofast::write(a[i]),putchar(' ')
#define rinputarr(len,a) per(i,(len),1)iofast::read(a[i])
#define rprintarr(len,a) per(i,(len),1)iofast::write(a[i]),putchar(' ')

#endif

/*redefine 2025*/
#define rank LmU1MDVj
#define x0 YzFhYTAz
#define y0 OGNiNGUw
#define x1 MGQ4ZTVk
#define x2 NjE1M2I5
#define y1 MjhlMzNl
#define y2 NWIwNTk2
#define link Mjk0ZjJm
#define ___ NzYxMzBj
#define hash ZWRmZjlj

/**/

//#define _O2
//#define _O3
//#define _Ofast
#ifdef _O2
#define __USE_O2__
#pragma optimize(2)
#endif
#ifdef _O3
#define __USE_O3__
#pragma optimize(3)
#endif
#ifdef _Ofast
#define __USE_Ofast__
#pragma optimize("Ofast")
#endif
//#define int long long
//undef register
/*
1->X 's Odd and Even Minist Edge in dis_X_0,1 --- BFS

dis_1,1 == inf erfentu , ans=n-1
dis_1,1 == 1 zihuan(1->1 is Even Minist Edge)  , ans=n



1. (x,y) -> (x-1,y-1) ***

			(x-1,y+1) *
2. (x,y) ->    AND
			(x+1,yl-1) *
			
			(x-1,y)   X
NOT(x,y) ->   AND
			(x,y-1)   X
			
Know (x,y) -> (x+k,y+w) k,w=1 or -1  k,w not equare 0

if x+1==y (x,y) -> (x+1,y-1) == in (x,y)

And if map can't find (x+k,y+w), can't (x,y) -> (x+k,y+w).

--------------------------------------------------

sort: first(x+y,less),second(x,greater).
(x,y) -> (x,?) or (x-1,?)


*/
const int N=3e5+7,inf=0x3f3f3f3f,mod=998244353;
int n,m,dis[N][2];
unordered_map<int,int> mp[N];
vector<int> g[N];
vector<pii> gg;

struct node{
	int x,y,t;
};
queue<node> q;
il bool cmp(pii a,pii b){
	return (pii){a.fi+a.se,a.fi}<(pii){b.fi+b.se,b.fi};
}
void to_dis(){
	//q.push((node){1,0});
	q.emplace((node){1,0,0});
	while(!q.empty()){
		node p=q.front();q.pop();
		rei x=p.x,y=p.y,t=p.t;
		for(rei yy:g[x]){
			if(dis[yy][y^1]>t+1){
				dis[yy][y^1]=t+1;
				//cerr<<dis[yy][y^1]<<" "<<t+1<<" DIS\n";
				//q.push((node){yy,y^1,t+1});
				q.emplace((node){yy,y^1,t+1});
				
			}
		}
	}
}
int solve(){
	rei ans=0;
	rep(i,0,(signed int)gg.size()-1){
    	rei now=gg[i].fi+gg[i].se;
    	rei j=i,k=0;
    	while(j+1<gg.size()&&gg[j+1].fi+gg[j+1].se==now){
    		++j;
		}rep(l,i,j){
			pii p=gg[l];
			rei x=p.fi,y=p.se;
			rei r=mp[x][y];
			if(!x)continue;
			ans+=k;
			if(x+1==y){
				ans+=max(0,r-k);
				if(mp[x-1].find(y-1)!=mp[x-1].end()){
					ans+=(min(r,k)+1>>1);
				}else{
					ans+=(r+1>>1);
				}break;
			}ans+=max(0,r-k);
			if(mp[x-1].find(y-1)!=mp[x-1].end()){
				tmn(k,r);
			}else{
				k=r;
			}
			if(k&&mp[x+1].find(y-1)==mp[x+1].end())ans+=k;
		}
		i=j;
		//cerr<<ans<<'\n';
	}
	//cerr<<ans<<"\n";
	return ans;
}
void sol(){
	gg.clear();
	rep(i,0,n<<1)g[i].clear(),mp[i].clear();
	while(!q.empty())q.pop();
	cin>>n>>m;
	rep(i,1,n)dis[i][0]=dis[i][1]=inf;
	rep(i,1,m){
		rei x,y;cin>>x>>y;
		g[x].eb(y), g[y].eb(x);
	}dis[1][0]=0;
	to_dis();
	if(dis[1][1]==inf){
		cout<<n-1<<"\n";return;
	}if(dis[1][1]==1){
		cout<<n<<"\n";return;
	}rep(i,1,n){
        rei x=dis[i][0],y=dis[i][1];
        if(x>y)swap(x,y);
        if(!mp[x][y])gg.eb(x,y);
        ++mp[x][y];
        //cerr<<mp[x][y]<<" "<<x<<" "<<y<<" "<<i<<"\n";
    }sort(gg.begin(),gg.end(),cmp);
	cout<<solve()<<"\n";
}
signed main(){
    Mios;
    rei T;cin>>T;while(T--){
    	sol();	
	}


    return 0;
}
#endif
//-O2 -std=c++14 -DLOCAL -Wall -Wextra -Wshadow -Wl,-stack=536870912


```

---

## 作者：一只绝帆 (赞：0)

首先发现 $f(x)$ 的信息相当于奇偶最短路，如果只有纯的最短路我们是好做的，把最短路画在数轴上，每个点随便在上一层选一个父亲即可。

两维的，用类似的方法我们画在平面上，令奇偶最短路分别是 $x,y$，则我们画在 $(\min(x,y),\max(x,y))$ 上。

由于奇偶性，这个图中只有斜对角存在邻居，而上下左右没有。

按照平面直角坐标系的上下左右来论，一个点要么从左下角转移过来，要么某一维从左上转移，某一维从右下转移。

考虑从左下往右上扫描线，每次把一层点与开头联通，观察一个连通块，两个端点必定可以使用一类边（否则该图无法构造出来），于是变成了一个序列问题：$a_i$ 表示该位置有多少点，$b_i$ 表示该位置能否使用一类边，我们把每个 $a_i\ge 1$ 的连续段拉出来单独处理。

考虑所有 $b_i=0$ 的空腔，这里面的每个点都必须要连向两侧，所以贡献是 $a_l+a_r+\sum_{i=l}^{r-1}\max(a_i,a_{i+1})$。

> 解决了这些点后，有一些点已经被自动解决了（例如 $b:[1,0,0,1,0,0,1]$，中间的那个位置有一部分点就被解决了），而剩下的点要解决它们至少需要 $1$ 的代价，而我们刚好可以用 $1$ 的代价（直接使用一类边），所以代价是方便计算的。

这个分析是错误的，错在“至少需要 $1$ 的代价”，事实上对于一个 $0111110$（假设有 $x$ 个 $1$）的连续段，在处理完 $0$ 后，我们有 $\min a$ 次机会，花费 $x-1$ 拯救 $x$ 个点。

注意序列的最右端不太一样，一个点的右下角可以不在 $x\le y$ 的图上，例如 $(a,a+1)$ 可以与自己相互转移，所以如果使用二类边，向右下的边只需要 $\lceil\frac{ num}{2}\rceil$ 条边即可，一类边仍然需要 $num$ 条。

不过 $1.5>1$，最右边的边界情况只能说明，有现成的左边界能用那我们就用，用不了我们就还是用一类边。

所以我们从左往右扫描，传递二类边即可，最后剩下的点用一类边补齐。

一个很重要的误区是：$1$ 号点必定在第一层（这是因为 $1\to dis_p(x)$ 和 $dis_{\neg p}(x)\to 1$ 的道路是对偶的），但第一层点并不一定只有一个，满足 $x=0$ 的点只有一号点，它只需要转移 $y$ 而无需转移 $x$，其他点仍需要从两边转移过来。

（如果第一层点只有一个的话，那之后的每层都只能有一个了。）

---

## 作者：nullqtr_pwp (赞：0)

由于 $f_G(a,b)$ 可以走重边，所以我们只关心奇最短路以及偶最短路。

判掉一下每个点只有奇数路径或偶数路径，即二分图，可以直接最短路树，在两题都需要特判掉。

本题的重点在于确认 $G'$ 的结构。考虑 $(x_i,y_i)$ 为不同奇偶的最短路数对，要求 $x_i<y_i$。对于原图的 $(x_i,y_i)$，将每个点拆成两个奇偶性的点之后跑 BFS 就可以 $O(m)$ 求。

注意到相邻边的 $x,y$ 都的差值都 $\leq 1$，否则可以更新掉。

考虑能得出这样的图的连边形态：

- $(x_i,y_i)$ 与 $(x_i-1,y_i-1)$ 相连。
- $(x_i,y_i)$ 与 $(x_i-1,y_i+1)$，$(x_i+1,y_i-1)$ 相连。
- 注意到 $x_i+1=y_i$ 的点可以直接连 $(y_i,y_i-1)=(x_i,y_i)$ 以及 $(x_i-1,x_i)$。

考虑对原图按照 $(x_i+y_i)$ 为第一关键字，$x_i$ 为第二关键字排序。那么将所有边定向，就是一个分层的好看的 $\text{DAG}$。考虑直接按照顺序贪心。令 $cnt_{x,y}$ 表示 $(x,y)$ 的出现次数。

考虑怎么连前驱，可能的前驱有且只有两种：$(x-1,y-1)$ 和 $(x-1,y+1)$。

注意到每层的连边形态都是若干条链，并且结尾如果为 $(x_i,x_i+1)$ 甚至可以互相连。

考虑怎么处理所有点对为 $(x_i,y_i)$ 的点。

- 若存在 $(x-1,y-1)$ 且不存在 $(x-1,y+1)$，那么只能向上连。
- 若不存在 $(x-1,y-1)$ 且存在 $(x-1,y+1)$，那么考虑这些点不仅需要往 $(x-1,y+1)$ 连边，还要往后面的 $(x+1,y-1)$ 连边。这个东西后效性很大，考虑怎么处理。考虑以前 $(x-1,y+1)$ 的连边的对象唯一，那么可以令 $t$ 表示没有及时处理掉的，需要往后连的，那么关于现在就需要增加 $\max(cnt_{x,y}-t,0)$ 往前连的边。考虑往后连的东西，$x=y-1$ 时可以直接内部连，消掉，这样一定不劣，因为一次消了两个。否则只能往后连。
- 若两者都存在，考虑优先往前面匹配时不劣，然后是往上面连，最后才是连额外的东西。

用 map 随便维护下就 $O(n\log n)$ 了。

---

## 作者：C1942huangjiaxu (赞：0)

思维难度很高的一道题，试图把贪心的部分说清楚。

首先注意到可以在一条边上来回走，因此只要确定了到点 $a$ 的奇数最短路和偶数最短路，就能确定 $f(a)$。

奇偶最短路可以用广搜求出。

特判掉二分图的情况，剩下情况每个点都存在奇偶最短路。

不妨设点 $i$ 奇偶最短路的值为 $(x_i,y_i)(x_i\lt y_i)$，考虑与 $i$ 相邻的点要满足什么条件：

- 存在点 $j$ 满足 $(x_j,y_j)=(x_i-1,y_i-1)$。
- 存在点 $j$ 和点 $k$，满足 $(x_j,y_j)=(x_i-1,y_i+1),(x_k,y_k)=(x_i+1,y_i-1)$。

对于 $i$，至少要满足上述条件中的一条。

注意 $1$ 号点因为 $x_1=0$，只要满足存在 $k$ 使得 $(x_k,y_k)=(x_i+1,y_i-1)$ 就行了，这里影响并不大。

**定义 $x_i+y_i$ 相同的点为同一层的点，同一层的点中 $x_i$ 较大的点在 $x_i$ 较小的点的左边。**

对于点 $i$ ，定义上部点为 $(x_i-1,y_i-1)$，左部点为 $(x_i+1,y_i-1)$，右部点为 $(x_i-1,y_i+1)$，同时类似的定义与 $i$ 相邻的边。

对于一个点 $i$，我们将 $i$ 的**上部边和左部边**的贡献算在 $i$ 上。

注意到有一些**特殊点满足 $x_i+1=y_i$**，它的左部点和它本身所处的集合相同，所以特殊点的左部边可以看做只有 $\frac 1 2 $ 的贡献，因为一条边可以满足 $2$ 个点。

可以发现，特殊点每个点至少有 $\frac 1 2$ 的贡献，其余点每个点至少有 $1$ 的贡献。

对于同一层的点，考虑从右往左确定每个点连的边，假设当前考虑点 $i$。

+ 若 $i$ 没有右部边，则 $i$ 必须连上部边。（如果 $i$ 没有上部点，说明之前的右部边连少了，强行补上右部边，这里会使某个点的贡献大于 $1$。）

+ 若 $i$ 有右部边，则 $i$ 可以选择连接上部边或者左部边。

**发现有右部边的情况下，选择严格多余没有的情况，所以在代价最小的前提下我们希望尽量多连同一层的边。**

因此我们在 $i$ 有右部边的情况下会**选择连左部边。**

**如果有 $2$ 个同层的特殊点都有右部边，那么每个点有 $\frac 1 2$ 的贡献，否则有 $1$ 的贡献，这也意味着多连同层的边是更优的。**

但我们并不会额外增加同一层的边，因为这样最多只会使一个特殊点的贡献少 $\frac 1 2$，而加入的边有 $1$ 的贡献。

直接按照上述过程贪心即可。

参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int T,n,m;
int d[N][2];
vector<int>e[N];
map<pair<int,int>,int>mp;
struct node{
	int x,y;
}t[N];
bool cmp(node a,node b){
	return a.x+a.y==b.x+b.y?a.x<b.x:a.x+a.y<b.x+b.y;
}
void solve(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)e[i].clear(),d[i][0]=d[i][1]=-1;
	for(int i=1,x,y;i<=m;++i){
		scanf("%d%d",&x,&y);
		e[x].push_back(y);
		e[y].push_back(x);
	}
	queue<pair<int,int> >q;
	d[1][0]=0,q.push({1,0});
	while(!q.empty()){
		auto [x,y]=q.front();
		q.pop();
		for(auto v:e[x])if(d[v][y^1]==-1){
			d[v][y^1]=d[x][y]+1;
			q.push({v,y^1});
		}
	}
	if(d[1][1]==-1)return printf("%d\n",n-1),void();
	vector<node>a;
	mp.clear();
	for(int i=1;i<=n;++i){
		t[i]={d[i][0],d[i][1]};
		if(t[i].x>t[i].y)swap(t[i].x,t[i].y);
		if(!mp.count({t[i].x,t[i].y}))a.push_back(t[i]);
		++mp[{t[i].x,t[i].y}];
	}
	sort(a.begin(),a.end(),cmp);
	int ct=0,ans=0;
	for(int i=0;i<a.size();++i){
		if(i+1<a.size()&&a[i+1].x==a[i].x+1&&a[i+1].y==a[i].y-1){
			int c=mp[{a[i].x,a[i].y}];
			ct=min(ct,c);
			c-=ct,ans+=ct;
			if(mp.count({a[i].x-1,a[i].y-1}))ans+=c;
			else ct+=c,ans+=((a[i].x>0)+1)*c;
		}else{
			int c=mp[{a[i].x,a[i].y}];
			if(a[i].x+1==a[i].y){
				ct=min(ct,c);
				c-=ct;
				if(mp.count({a[i].x-1,a[i].y-1}))ans+=(ct+1>>1)+c;
				else ct+=c,ans+=(a[i].x>0)*c+(ct+1>>1);
			}else ans+=c;
			ct=0;
		}
	}
	printf("%d\n",ans);
}
int main(){
	scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```

---

## 作者：Nasaepa (赞：0)

注意到对于 $\forall a,b$ 当 $f_G(a,b)$ 成立时， $f_G(a,b+2)$ 一定成立。且 $b \bmod 2 = (b+2) \bmod 2$，因此本题和奇偶有关。

我们只需要关心每个点的奇偶最短路就行了。先用 bfs 跑出每个点的奇偶最短路，对于点 $i$，设 $x_i$ 为其奇偶最短路中较小的一条，$y_i$ 为其中较大的一条。显然要么所有点都没有 $y_i$，要么所有点都有 $y_i$。没有 $y_i$ 的情况为二分图，此时需要特判，建立最短路树作为图 $G'$，输出 $n - 1$ 即可。

此时我们可以用 $(x,y)$ 表示一个点并在图 $G'$ 中将其进行连边了。认为一个点的 $x$ 坐标越小越**靠上**，一个点的 $y$ 坐标越小越**靠左**。显然，一个点必须与一个在左边的点连边，且必须与一个在上面的点连边，定义连接这种边的过程定义为**维护点**，邻接的两个点横纵坐标的绝对差不能超过 $1$。显然，可以以如下几种方法连边：

1. 将边连接到 $(x-1,y-1)$ 即左上角。称为 1 类边。
2. 将边连接到 $(x-1,y+1)$ 和 $(x+1,y-1)$ 即左下角和右上角。称为 2 类边，当左下角的点不存在时需要特殊考虑。
3. 当 $x + 1 = y$ 时可以通过内部点自行连边构造合法方案。称为 3 类边。

注意到 2 类边维护的点都的 $x+y$ 都是相同的，可以将点按照 $x+y$ 为第一关键字，$x$ 为第二关键字升序排序，一条一条斜线处理，在维护点时 $x$ 的值会沿着连边往左下方维护，$y$ 的值会沿着连边往右上方维护。

考虑对于点 $(x,y)$ 对其进行贪心，每次考虑往左上方连边还是往右上方连边，显然一个点向自己的左上方连边只需要一条边就可以维护自己的 $x$ 和 $y$。但是注意到有可能有一些点没有 $(x-1,y-1)$ 的点，也有一些点因为贪心策略无法连接左上角的点，因此需要向左下角连边。维护 $t$ 表示 $(x-1,y+1)$ 有多少个点需要连接到 $(x,y)$。这时候需要分类讨论。设 $cnt$ 为 $(x,y)$ 点的个数。

当 $t \le cnt$ 时，需要分成两种情况，有 $(x-1,y-1)$ 的情况和没有的情况。当有时，可以让 $(x,y)$ 的 $t$ 个点和右上角连边，剩下的点连到左上角，对答案的贡献为 $cnt$ ，此时仍然有 $t$ 个点需要向左下角连边，容易证明，那 $t$ 个点往左上角连边的策略**一定不优于最优策略**。当没有时，需要让 $cnt$ 个点都和右上角连边，对答案的贡献也为 $cnt$，此时有 $cnt$ 个点需要向左下角连边。

当 $t > cnt$ 时，把 $t$ 条边连向 $(x,y)$ 并且让 $cnt$ 个点都往左下方连边，对答案的贡献为 $t$。

注意需要考虑 $(x+1,y-1)$ 即左下角点不存在的特殊情况，此时需要考虑 $x + 1 = y$ 是否成立。如果成立，则需要下传的 $t$ 个点需要自行解决 $y$ 的维护问题，只需要这 $t$ 个点每个点都有一条连向 $(x,x+1)$ 的边即可由 $x$ 维护 $y$，容易得到对答案的贡献为 $\lceil\frac{t}{2}\rceil$ 。当 $x+1 \ne y$ 时，由于一定可以构造合法方案，此时 $(x-1,y-1)$ 一定存在，将所有点都连过去即可，对答案的贡献为 $t$。

注意特判 $1$ 号点，这个点**不会产生任何贡献**，容易证明，在排序完成后排在数组下标为 $1$ 位置的一定是 $1$ 号点。
 
将所有贡献加起来就是答案了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
#define lowbit(x) (x&-x)
#define pii pair<int,int>
#define N 100010
#define M 400010
namespace graph{
    int head[N],nxt[M],to[M];
    int cnt_edge;
    inline void connect_head(const int &x,const int &y){
        ++cnt_edge;
        nxt[cnt_edge] = head[x],to[cnt_edge] = y,head[x] = cnt_edge;
    }
}
using namespace graph;
int T,n,m,u,v,cnt,r,t,x,y,ans;
int g[2][N];// 最短路
pii h[N],la,lc,*px;
inline bool cmp(const pii &n1,const pii &n2){
    if(n1.first + n1.second != n2.first + n2.second)return n1.first + n1.second < n2.first + n2.second;
    return n1.first < n2.first;
}
bool fa,tb;
struct node{int x,p;node(const int &x_ = 0,const int &p_ = 0){x = x_,p = p_;}}q[N<<1],*front,*tail;
// 奇数偶数最短路
inline void bfs(){
    front = tail = q;
    *(tail++) = node(1,0);
    g[0][1] = 0;
    int x,p;
    while(front != tail){
        x = front->x,p = front->p,++front;
        for(int edg = head[x];edg;edg = nxt[edg]){
            const int &v = to[edg];
            if(g[!p][v] != INF)continue;
            g[!p][v] = g[p][x] + 1;
            *(tail++) = node(v,!p);
        }
    }
}
// 主函数
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin >> T;
    while(T--){
        cin >> n >> m;
        // 重置图
        cnt_edge = 0;
        memset(head,0,(n<<2)+20);
        memset(g[0],0x3f,(n<<2)+20);
        memset(g[1],0x3f,(n<<2)+20);
        while(m--){
            cin >> u >> v;
            connect_head(u,v),connect_head(v,u);
        }
        bfs();
        bool flag = 0;
        for(int i = 1;i <= n;++i){// 特判二分图
            if(g[0][i] != INF && g[1][i] != INF){
                if(g[0][i] > g[1][i])swap(g[0][i],g[1][i]);
                h[i] = make_pair(g[0][i],g[1][i]);
                continue;
            }
            cout << n - 1 << '\n';flag = 1;break;
        }
        if(flag)continue;
        sort(h+1,h+n+1,cmp);
        // 求出值
        t = ans = tb = 0;// tb 用于特判 i 是否为 1
        px = h+1;// 用于动态维护 (x-1,y-1)
        for(int i = 1;i <= n;i = r){
            r = i,cnt = 0;
            while(r <= n && h[r] == h[i])++r,++cnt;
            // 三类分讨
            x = h[i].first,y = h[i].second;
            la = make_pair(x-1,y-1),lc = make_pair(x+1,y-1);
            // 移动 px
            while(px->first+px->second < x+y-2 || (px->first+px->second == x+y-2 && px->first < x-1))++px;
            fa = (*px == la);
            if(t <= cnt){
                ans += tb*cnt;
                if(!fa)t = cnt;
            }else ans += tb*t,t = cnt;
            // 到一行的末尾了
            if(h[r] != lc || r > n){
                if(x + 1 != y)ans += t;
                else ans += (t+1>>1);
                t = 0;
            }
            tb = 1;
        }

        cout << ans << '\n';
    }
    return 0;
}
```

---

## 作者：Hypercube (赞：0)

好题。

首先很显然的是，题目给出的约束相当于 $1$ 到所有点经过奇数和偶数条边的最短路。我们的任务就是构造一张图，在 $1$ 到所有点奇偶最短路不变的情况下最小化边数。

首先先判掉两种简单情况，一个是原图为二分图，另一个是 $1$ 有自环。原图为二分图的情况答案为 $n-1$，即构造原图的最短路树。最短路树存在是因为最短路转移为 DAG（无负环）。$1$ 有自环的情况答案即为原图，显然构造不出更优的解。

我们考虑将一个点看做点对 $(x,y)$，满足 $x<y$，即奇偶最短路的较小值和较大值组成的二元组。我们发现要使得 $(x,y)$ 成立，要么存在 $(x-1,y-1)$ 向其连边，要么同时存在 $(x+1,y-1),(x-1,y+1)$ 向其连边。特别的，当 $y=x+1$ 时，$(x+1,y-1)$ 与 $(x,y)$ 等价（准确地说，$(x+1,y-1)$ 应当写作 $(y-1,x+1)$。

转移显然分为两类，其中一类可以无后效性地处理，另一部分无法避免后效性。那我们只能放弃 dp，考虑贪心。

对于当前状态 $(x,y)$，我们不仅要考虑当前状态，还要考虑 $(x-1,y+1)$ 带来的后效性。具体体现在 $(x+1,y-1)$ 每存在一条向 $(x+2,y-2)$ 连的边，就要有一条连向 $(x,y)$ 的边。这类边必须连，并且可以对于 $(x,y)$，需要付出的代价仅为 $1$，无疑是可以提前的。在存在 $(x-1,y-1)$ 的情况下，我们显然可以把剩余的点直接连上去，否则就只能向前向后连边，这样不但对后来有影响，并且代价为 $2$，优先级最低。

其实上面说代价为 $2$ 并不严谨，因为这条边可能会使 某个$(x+1,y-1)$ 代价降为 $1$，但这样平均一下是 $1.5$，仍然不优。

需要讨论的情况很多，建议思考完备再写代码。

---

