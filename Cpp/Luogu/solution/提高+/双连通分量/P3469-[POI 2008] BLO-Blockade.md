# [POI 2008] BLO-Blockade

## 题目描述

B 城有 $n$ 个城镇（从 $1$ 到 $n$ 标号）和 $m$ 条双向道路。

每条道路连结两个不同的城镇，没有重复的道路，所有城镇连通。


把城镇看作节点，把道路看作边，容易发现，整个城市构成了一个无向图。

请你对于每个节点 $i$ 求出，把与节点 $i$ 关联的所有边去掉以后（不去掉节点 $i$ 本身），无向图有多少个有序点 $(x,y)$，满足 $x$ 和 $y$ 不连通。

## 说明/提示

$n\le 100000$，$m\le500000$。

## 样例 #1

### 输入

```
5 5
1 2
2 3
1 3
3 4
4 5
```

### 输出

```
8
8
16
14
8
```

# 题解

## 作者：songhn (赞：207)

首先可以对第$i$个节点进行讨论

假如$i$不是割点（即把$i$和它有关的所有边都去除后图依然联通）那么这个图只有$i$是独立在外面的，由于求的是有序点对，所以除了$i$以外的$n-1$个点作为一个大的连通图对$i$加边，即为$2*(n-1)$对

假如$i$是割点，那么会把图分为$a$个连通块以及$i$本身,由于tarjan在求割点的过程中是一棵搜索树往下遍历，所以除了它和它的子树外，还会有其他剩余点共同构成另一个连通块（有点类似树的重心的求法）设$i$所有子树的和为$sum$,第$i$个子树的节点总数为$t[i]$，点对的数量便为$$t[1]*(n-t[1])+t[2]*(n-t[2])+\cdots+t[a]*(n-t[a])+(n-1)+(1+sum)*(n-sum-1)$$

所以在求割点的过程中每遇到一个$low[v]>=dfn[u]$便把对数加上$t[i]*(n-t[i])$最后假如不是割点那直接把对数更新为$2*(n-1)$是割点则加上$n-1+(n-sum-1)*(sum+1)$
最后遍历输出答案即可
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1000010;
inline int read()
{
	int x=0,t=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')t=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x*t;
}
int n,m,head[maxn],num=0;
int dfn[maxn],low[maxn],size[maxn],tot=0;
long long ans[maxn];
bool cut[maxn];
struct node{
	int v,nex;
}e[maxn];
void add(int u,int v)
{
	e[++num].v=v;
	e[num].nex=head[u];
	head[u]=num;
}
void tarjan(int u)
{
	dfn[u]=low[u]=++tot;
	size[u]=1;
	int flag=0,sum=0;
	for(int i=head[u];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(!dfn[v])
		{
			tarjan(v);
			size[u]+=size[v];
			low[u]=min(low[u],low[v]);
			if(low[v]>=dfn[u])
			{
				ans[u]+=(long long)size[v]*(n-size[v]);
				sum+=size[v];
				flag++;
				if(u!=1||flag>1) cut[u]=true;
			}
		}
		else low[u]=min(low[u],dfn[v]);
	}
	if(!cut[u]) ans[u]=2*(n-1);
	else ans[u]+=(long long)(n-sum-1)*(sum+1)+(n-1);
}
int main()
{
	n=read(),m=read();
	for(int i=1;i<=m;i++)
	{
		int x,y;
		x=read(),y=read();
		add(x,y),add(y,x);
	}
	tarjan(1);
	for(int i=1;i<=n;i++) printf("%lld\n",ans[i]);
	return 0;
}

```

---

## 作者：小菜鸟 (赞：89)

好像重点讲数学和图论的都有，然而并没有两个都详细讲的。。。  

所以作为我少有的不看题解A掉的紫题，十分有必要写一篇题解方便自己和各位大佬。。。

------

### 题意：  

​		给定一张无向联通图$(V,E)$，对于每一个点$P\in V$，求当$P$不能被经过时满足$u,v$不连通的有序点对数。  

------

### 题解：  

一道十分适合练习$Tarjan$的图论题。  

对于每一个点，考虑将其删除对图会产生什么影响，进而计算答案。  

------

不是割点：~~显然只是少了个点而已，~~答案就是$2(n-1)$。  

是割点：~~还是少了一个点~~  

删除割点将会导致整个图变成多个联通块。容易发现不同联通块内的点之间不能互相到达。  

即大小为$size_a,size_b$的两个联通块对答案产生$2 size_a size_b$的贡献。

那么设全图有$n$个点，删除该割点产生$k$个联通块，则答案就是联通块两两配对产生的贡献之和。  

即$2(n-1)+\sum_{i=1}^k \sum_{j=1,j\neq i}^{k}size_i \times size_j$  

这里需要$O(n^2)$卷起来，遇到菊花图就凉了。。。  

考虑优化，显然$\sum_{j=1,j\neq i}^k size_j =n-size_i-1$  

所以上式化为$2(n-1)+\sum_{i=1}^k size_i \times( n-size_i-1 )$  

不是割点可以认为割掉以后产生一个大小为$1$的联通块，不必单独处理。

------

考虑$Tarjan$如何求联通块大小。  

$Tarjan$实际上是在$dfs$生成树上，利用$dfn$和$low$对返祖边进行标记。  

所以一个点的子树可以分成两类：存在返祖边或不存在。  

对于前者，割掉该点并不影响连通性，所以和祖先算作一个联通块；  

对于后者，割掉该点将使得其变为独立的联通块，所以在搜索时顺便计算$size$。  

于是可以方便地算出后者的$size$之和$sum$，而前者总大小即为$n-sum-1$。  

在搜索时一边累加$sum$，一边累加答案，最后加上$n-1$，得到的是无序点对的个数。  

输出时乘以二即可。。。  

------

### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using std::freopen;
using std::fread;
using std::scanf;
using std::printf;
using std::min;

char gc()
{
	static char buf[1<<18],*p1=buf,*p2=buf;
	if(p1==p2)
	{
		p2=(p1=buf)+fread(buf,1,1<<18,stdin);
		if(p1==p2)return EOF;
	}
	return *p1++;
}
template<typename _Tp>
void read(_Tp& x)
{
	x=0;
	char c=gc();
	while(c<'0'||c>'9')c=gc();
	while(c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+(c^48);
		c=gc();
	}
}
template<typename _Tp>
void write(_Tp x)
{
	if(x>=10)write(x/10);
	putchar((x%10)^48);
}

const int N=100005,M=500005;

int n,m;

int head[N],dfn[N],low[N];
int size[N];
long long ans[N];

struct Edge
{
	int next,to;
};
Edge E[M<<1];


int tot;
void add(int u,int v)
{
	E[++tot].next=head[u];
	E[tot].to=v;
	head[u]=tot;
}

int cnt;
void tarjan(int u)
{
	dfn[u]=low[u]=++cnt;
	long long sum=0;
	size[u]=1;
	for(int i=head[u];i;i=E[i].next)
	{
		int v=E[i].to;
		if(!dfn[v])
		{
			tarjan(v,u);
			size[u]+=size[v];
			if(low[v]>=dfn[u])//判断不存在返祖边的情况
			{
				ans[u]+=size[v]*sum;//计算这一棵子树的贡献
				sum+=size[v];
			}
			low[u]=min(low[u],low[v]);
		}
		else
		{
			low[u]=min(low[u],dfn[v]);
		}
	}
	ans[u]+=(n-sum-1)*sum;//别忘了计算剩下的点产生的贡献！
	ans[u]+=n-1;
}

int main()
{
	read(n),read(m);
	for(int i=0;i<m;++i)
	{
		int u,v;
		read(u),read(v);
		add(u,v);
		add(v,u);
	}
	tarjan(1);
	for(int i=1;i<=n;++i)
	{
		write(ans[i]*2);//之前求出无序点对，这里乘2
		putchar('\n');
	}
}
```

------

P.S. 这题被我校ZJOI2018 rk2神仙拿来出模拟赛，结果数据出现负数导致几乎所有原本A掉这题的人爆50。。。

---

## 作者：nekko (赞：11)

根据圆方树的性质，可以得知每个圆点都是一个割点

也就是说，对于圆点 $u$，如果原来 $(x, y)$ 连通且经过 $u$，那么删掉 $u$ 后它们就不在连通了

于是问题就成了树上对于每个点，求有多少条经过它的路径

计算子树大小就行了

~~圆方树真无脑暴力啊~~

```
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 3e6 + 10;

int n, m, head[N], rest[N], to[N], tot, sta[N], top, cnt, dfn[N], low[N], clk, sz[N];
ll ans[N];
vector<int> g[N];
void add(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}
void lk(int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
}

void tarj(int u, int fa) {
    dfn[u] = low[u] = ++ clk;
    sta[++ top] = u;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(!dfn[v]) {
            tarj(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] >= dfn[u]) {
                ++ cnt;
                lk(u, cnt);
                int tmp;
                do {
                    tmp = sta[top --];
                    lk(tmp, cnt);
                } while(tmp != v);
            }
        } else if(v != fa) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

void dfs(int u, int fa) {
    for(int i = 0 ; i < g[u].size() ; ++ i) {
        int v = g[u][i];
        if(v == fa) continue;
        dfs(v, u);
        ans[u] += 2ll * sz[v] * sz[u];
        sz[u] += sz[v];
    }
    sz[u] += u <= n;
    ans[u] += 2ll * (sz[u] - 1) * (n - sz[u]);
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= m ; ++ i) {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v), add(v, u);
    }
    cnt = n;
    tarj(1, 0);
    dfs(1, 0);
    for(int i = 1 ; i <= n ; ++ i) {
        printf("%lld\n", ans[i] + 2 * (n - 1));
    }
}
```

---

## 作者：elijahqi (赞：10)

刚写完模板题来刷这题，顿时连题解都没看就有思路了

只不过wa了好多发，其实可能因为数据弱，我这个对于重边其实是没法很好的处理的

我如果要不是割点的话 那么取缔我造成的影响只会是n-1

如果我是割点（割点分两种情况讨论） 1、我是父节点，我的儿子超过了两个

2、我不是父节点，我儿子的Low值小于我的dfn值

记录dep

对于我是父节点，且我的儿子数超过两个的这种情况，我只有在dep[儿子]=dep[我]+1的情况下才做，否则会重复


```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define N 110000
#define M 550000
inline int read(){
    int x=0;char ch=getchar();
    while (ch<'0'||ch>'9') ch=getchar();
    while (ch<='9'&&ch>='0'){x=x*10+ch-'0';ch=getchar();}
    return x;
}
long long ans[N];
struct node{
    int y,next;
}data[M<<1];
int size[N],dfn[N],low[N],h[N],num,n,fa[N],m,dep[N];
void tarjan(int x){
    dfn[x]=low[x]=++num;int child=0;size[x]++;int z=0;ans[x]+=n-1;
    for (int i=h[x];i;i=data[i].next){
        int y=data[i].y;
        if (fa[x]==y) continue;
        if (!dfn[y]){dep[y]=dep[x]+1;
            fa[y]=x;child++;tarjan(y);low[x]=min(low[x],low[y]);
            size[x]+=size[y];
            if (fa[x]&&low[y]>=dfn[x]) {
                z+=size[y];ans[x]+=(long long)size[y]*(n-z-1);
            }
        }else low[x]=min(low[x],dfn[y]);
    }
    
    if (!fa[x]&&child>=2){
        for (int i=h[x];i;i=data[i].next){
            int y=data[i].y;
            if (fa[y]==x&&dep[y]-dep[x]==1){
                for (int j=data[i].next;j;j=data[j].next){
                    int y1=data[j].y;
                    if (dep[y1]-dep[x]==1)ans[x]+=(long long)size[y]*size[y1];
                }
            }
        }
    }
}
int main(){
    freopen("3469.in","r",stdin);
    n=read();m=read();
    for (int i=1;i<=m;++i){
        int x=read(),y=read();
        data[++num].y=y;data[num].next=h[x];h[x]=num;
        data[++num].y=x;data[num].next=h[y];h[y]=num;
    }num=0;dep[1]=1;
    tarjan(1);
    for (int i=1;i<=n;++i) printf("%lld\n",ans[i]<<1);
    return 0;
}
```

---

## 作者：ShuYuMo (赞：8)

# 写在前面
这是一道剖析算法本质的题目

# 关于`Tarjan`

> `Tarjan`的本质就是一个`DFS`
>                 ——苟新杰老师

既然是`DFS`，那么在执行的过程中会形成一颗`DFS`树。
如果这个树点是一个割点，那么思考一下这个点的几个孩子是什么？
> `Tarjan`过程中形成的`DFS`树，如果这个点是割点，那么这个点的孩子们就是删去这个点后断开的几部分。

为什么？	
假设这个点的孩子（子树）分别有`SonTree1`、`SonTree2` 和`SonTree3`。	
`SonTree1`、`SonTree2` 和`SonTree3`不会属于一个强连通分量。	
因为如果这些儿子属于一个强连通分量，那么在遍历第一个儿子(`SonTree1`)的时候，其他儿子(`SonTree2` 和`SonTree3`)一定能被便利到，而绝对不会成为当前点的子树。

# 关于本题

两种情况：
 - 如果当前点不是割点，那么删去之后影响不大，只能导致当前被封锁的点到不了其他点，其他点也到不了当前被封锁的点。
 - 如果当前点是割点，那么删去之后会断成几大块儿。对于每一块，到剩下的每一个不属于这一块儿的点都不能继续拜访，设这一块大小为$S$，总点数为$n$，那么这一块儿产生的不能拜访数为：
    $$Ans += S \times (n - s)$$
   对每一块儿都要这么做。统计答案即可。注意：这个点上面的所有也是一块儿，大小计算方法与求`树的重心`类似。就是用总点数减去当前点为根的子树大小。

# 关于代码

```cpp
/*!
 * FileName: luogu-3469.cpp
 * This Problem is on luogu. The ID of the problem is 3469. 
 * Copyright(c) 2019 Shu_Yu_Mo
 * MIT Licensed
 * Luogu: https://www.luogu.org/space/show?uid=44615
 * Github: https://github.com/oldsuold/
 * Gitee: https://gitee.com/Shu_Yu_Mo/
 * These words were created by an amazing tool on 2019-08-13 08:29:07 written by Shu_Yu_Mo.
 */
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstring>
#include<iostream>
#include<cmath>
#include<vector>
#include<queue>
#include<algorithm>
#define inf 0x7fffffff
#define int long long
using namespace std;
const int _N = 110000;
const int _M = 1010000 ;
inline int read()
{
    char c = getchar(); int sign = 1; int x = 0;
    while(c > '9' || c < '0') { if(c=='-')sign = -1; c = getchar(); } 
    while(c <= '9' && c >= '0') { x *= 10; x += c - '0'; c = getchar(); }
    return x * sign;
}
int head[_N];
int tot = 0;
struct edges{
	int node;
	int nxt;
}edge[_M];
void add(int u, int v)
{
	edge[++tot].nxt = head[u];
	head[u] = tot;
	edge[tot].node = v;
}
int n, m;
int dfn[_N];
int low[_N];
int dfnClock = 0; 
bool isCut[_N];
int size[_N];
int Ans[_N];
void tarjan(int now, int fa)
{
	low[now] = dfn[now] = ++dfnClock;
	size[now] = 1;
	int child = 0;
	Ans[now] = 0;
	int SumForSon = 0;
	for(register int i = head[now];i;i = edge[i].nxt)
	{
		int exNode = edge[i].node;
		if(dfn[exNode] == 0)
		{
			child ++;
			tarjan(exNode, now);
			size[now] += size[exNode];
			low[now] = min(low[now], low[exNode]);
			if(low[exNode] >= dfn[now])
			{
				SumForSon += size[exNode];
				Ans[now] += (size[exNode] * (n - size[exNode]));
				isCut[now] = true;
			}
		}
		else
			low[now] = min(low[now], dfn[exNode]);
	}
	if(child < 2 && fa < 0) isCut[now] = false;
	if(!isCut[now]) Ans[now] = (n - 1) << 1;
	else Ans[now] += (n - SumForSon - 1) * (SumForSon + 1) + (n - 1);
}

signed main()
{
	n = read(), m = read();
	for(register int i = 1;i <= m;i++)
	{
		int tmpx = read(), tmpy = read();
		add(tmpx, tmpy);
		add(tmpy, tmpx);
	}
	memset(isCut, false, sizeof(isCut));
	tarjan(1, -1);
	for(register int i = 1;i <= n;i++)
			printf("%lld\n", Ans[i]);
    return 0;
}
```

---

## 作者：chihik (赞：5)

这道题一看就是到好（shui）题，~~毕竟自己因long long的问题的错了几次~~。好吧，不废话，开始讲解：

这道题一看就是求**无向图**中，**去掉一个点后无法连通的点对**，但注意：

1. $( x , y )$ 和$ ( y , x )$算作不同的点[](https://cdn.luogu.com.cn/upload/pic/62965.png)对
2. 即使点被删除后，也要计入无法连通数，但显然他们是不联通的


首先 $i$ 跟其他$n-1$个点肯定不能互通。如果$i$是割点，那么去掉$i$之后的几个不同连通分量就不能互通,那我们现在就想办法求一下去掉$i$后被切断的连通分量。先观察一下下图：

![](https://cdn.luogu.com.cn/upload/pic/61297.png)


黄点是一个割点，我们先考虑以它为根的子树的联通情况：

我们用$child[u]$表示以$u$为根的子树的大小，显然
$$
child[u]=\sum_{v \in u}child[v]
$$
这个我们可以在$Tarjan$中算出。

我们再定义$sum$为当前u已经遍历到的子树的节点个数，$s$为去掉$u$点后子树中的点无法连通的情况。

那么，每次遍历子节点$v$  ,  $s=s+sum*child[v]$  , $sum=sum+child[v]$



现在在考虑子树内部与外部的联通情况，$u$的子树大小为$sum$,外部节点为$n-sum-1$,去掉点$u$后，这些点也是无法连通的，$t$为去掉u点后子树中的点与外部的点无法连通的情况。

那么，$t=sum*(n-sum-1)$

结合注意事项1,2，我们可以得到：$Ans[u]=[s+t+(n-1)]*2$，这就是最后的答案了。




代码如下：
```cpp
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 100000;
int n,m,x,y;
vector< int > Graph[ MAXN + 5 ];

void Read( int &x ) {
	int f = 1;
	x = 0;
	char s = getchar( );
	
	while( s < '0' || s > '9' ) {
		if( s == '-' ) f = -1;
		s = getchar( );
	}
	while( s >= '0' && s <= '9' ) {
		x = x * 10 + s - 48;
		s = getchar( );
	}
	x *= f;
}
void Write( long long x ) {
	if( x < 0 ) {
		x = -x;
		putchar('-');
	}
	if( x >= 10 ) Write( x / 10 );
	putchar( x % 10 + 48 );
}
int Max( int x , int y ) {
	return x > y ? x : y;
}
int Min( int x , int y ) {
	return x < y ? x : y;
}

int dfn[ MAXN + 5 ] , low[ MAXN + 5 ] , child[ MAXN + 5 ] , depth;
long long Ans[ MAXN + 5 ];

void Tarjan( int u , int fa ) {
	dfn[ u ] = low[ u ] = ++ depth;
	child[ u ] = 1;
	//printf("%d %d\n",u,depth);
	long long sum = 0;
	for( int i = 0 ; i < Graph[ u ].size( ) ; i ++ ) {
		int v = Graph[ u ][ i ];
		if( v == fa ) continue;
		
		if( !dfn[ v ] ) {
			Tarjan( v , u );
			child[ u ] += child[ v ];
			
			if( low[ v ] >= dfn[ u ] ) {
				Ans[ u ] += child[ v ] * sum;
				sum += child[ v ];
			}
			low[ u ] = Min( low[ u ] , low[ v ] );
		}
		
		else if( v != fa && dfn[ u ] > dfn[ v ] )
			low[ u ] = Min( low[ u ] , dfn[ v ] );
	}
	Ans[ u ] = ( Ans[ u ] + sum * ( n - sum - 1 ) + n - 1 ) * 2;
}

int main( ) {
	Read( n ) , Read( m );
	for( int i = 1 ; i <= m ; i ++ ) {
		Read( x ) , Read( y );
		Graph[ x ].push_back( y );
		Graph[ y ].push_back( x );
	}
	Tarjan( 1 , -1 );
	
	for( int i = 1 ; i <= n ; i ++ )
		Write( Ans[ i ] ) , putchar('\n');
	return 0;
}
```

---

## 作者：KesdiaelKen (赞：5)

好久没有打过题解了，碰到这道不错的题，决定再来练练手。
对于题意，翻译其实已经表达的十分清楚了：**求每个点被删除之后有多少点对不能互相到达（包括被删掉的点）**。我们将每一个点的这一数值称作$ans[i]$。

首先，我们先要处理一个东西：**即使不删除任何一个点也会存在的不能互相到达的点对的数量（称其为$left$）**。为什么会有$left$存在呢？是因为**原图不一定是联通的！（嗯……经本人实验，数据里其实并没有不连通的数据点……或许是我没看懂题？）**而处理出这一部分的点对数量则比较简单。可以用dfs处理每一个连同块中含有的节点数，然后将它们一一相乘，得出总和。然而这样做有一个问题：这样的时间复杂度就是$O(N^2)$的了，肯定会超时。因此，我们对此进行改进：使用乘法结合律，每处理出一个连同块的节点数，就用之前所有连同块节点数之和乘它，汇总到总和里面，然后将它再加入连同块节点数之和。如此，便可以用$O(N)$求出。

那么删除点之后的部分该如何求呢？显然，这道题与割点有十分明显的关联。（不知道割点的同学请务必先做[【模板】割点（割顶）](https://www.luogu.org/problemnew/show/P3388)）如果节点$i$不是割点，那么删除它后这一个图必仍然是联通的，因此其它点对互相之间都不会组成符合要求的点对。所以就只有节点$i$与其他所有点对组成的这$n-1$个点对符合要求。当然，如果节点$i$是割点，也同样会包含这$n-1$个点对，只不过对于非i的节点直接也会产生一些点对。**那么这些点对又该如何统计呢？**

这一部分的处理就会稍有些复杂。首先，如果$i$是割点，那么我们就需要求割掉$i$之后**被分离**的那些连同块的点数。最难处理的就是存在$i$父节点的那一个连同块，比较难统计数量。这里用了一个比较傻的，但是容易理解的方法。我们先记录下在原图上，每一个点所属的连同块的节点数量$sum[i]$。然后对于割点$i$进行处理的时候，对于那些不存在$i$父节点的连同块，我们可以在tarjan时同时使用dfs记录连同块点数。这样我们就得到了这些连同块所包含的点数，我们将它们加和得到$he[i]$。于是，存在$i$父节点的连同块的点数易得了：$sum[i]-he[i]-1$。

之后，我们再来一遍dfs。此时对于每一个割点已经知道它所有割出的连同块的点数了。这时候，我们就用乘法结合律对他们进行统计，得出每一个割点产生的不连通点对数量。

最后对以上所有得出的结果进行加和输出即可。

**当然，这一题还是有坑的。**需要注意的点如下:

1. 需要使用long long（不需要高精度，经过简单极值计算可得出）！

2. 注意统计时重复被计算的点对——对于节点$i$，$i$与不属于自己连同块的点之间的点对数量被重复计算了两次，需要减掉。

3. 因为是有序点对，所以输出要乘2！

代码如下：

```
#include<cstdio>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
struct Edge//链式前向星存边
{
	int t,nexty;
}edge[1500000];
int head[500000]={0};
int cnt=0;
void add(int a,int b)
{
	cnt++;
	edge[cnt].t=b;
	edge[cnt].nexty=head[a];
	head[a]=cnt;
}
int dfn[500000]={0},low[500000]={0};
bool iscut[500000]={0};long long fads[500000]={0};
long long jhds[500000]={0};
long long ans[500000]={0};
int js=0,visjs=0;
int vis[500000]={0};
long long zds;
void dfs1(int node)//计算每一个连同块节点数
{
	vis[node]=visjs;zds++;
	for(int i=head[node];i;i=edge[i].nexty)if(vis[edge[i].t]!=visjs)dfs1(edge[i].t);
}
void dfs2(int node)//将每一个节点所在连同块节点数“告诉”每一个节点
{
	vis[node]=visjs;jhds[node]=zds;
	for(int i=head[node];i;i=edge[i].nexty)if(vis[edge[i].t]!=visjs)dfs2(edge[i].t);
}
long long tj(int node,int fa)//tarjan
{
	dfn[node]=low[node]=++js;
	int child=0;
	long long sum=0,sl=1,lc;
	for(int i=head[node];i;i=edge[i].nexty)
	{
		if(edge[i].t==fa)continue;
		if(!dfn[edge[i].t])
		{
			child++;
			sl+=lc=tj(edge[i].t,node);
			low[node]=min(low[node],low[edge[i].t]);
			if(low[edge[i].t]>=dfn[node]){iscut[node]=true;sum+=lc;}
		}
		else low[node]=min(low[node],dfn[edge[i].t]);
	}
	if(fa==-1&&child==1)iscut[node]=false;
	if(iscut[node])fads[node]=jhds[node]-sum-1;//求存在父节点的连同块的点数
	return sl;
}
long long cal(int node)//统计答案
{
	vis[node]=visjs;
	long long sl=1,lc,timnum=fads[node];
	for(int i=head[node];i;i=edge[i].nexty)
	{
		if(vis[edge[i].t]==visjs)continue;
		sl+=lc=cal(edge[i].t);
		if(!iscut[node])continue;
		if(low[edge[i].t]>=dfn[node]){ans[node]+=timnum*lc;timnum+=lc;}
	}
	return sl;
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	int a,b;
	while(m--)
	{
		scanf("%d%d",&a,&b);
		add(a,b);add(b,a);
	}
	long long xqadd=0,xqsum=0;
	for(int i=1;i<=n;i++)
	if(!vis[i])
	{
		zds=0;
		visjs++;
		dfs1(i);
		visjs++;
		dfs2(i);
		xqadd+=xqsum*zds;xqsum+=zds;//对初始的点对数量进行计算
	}
	for(int i=1;i<=n;i++)if(!dfn[i])tj(i,-1);
	for(int i=1;i<=n;i++)vis[i]=0;visjs=0;
	for(int i=1;i<=n;i++)
	if(!vis[i])
	{
		visjs++;
		cal(i);
	}
	for(int i=1;i<=n;i++)printf("%lld\n",ans[i]*2+(long long)n*2-2+xqadd*2-(long long)n*2+jhds[i]*2);//统计最终答案，记得*2
	return 0;
}
```

---

## 作者：Celebrate (赞：4)

在[博客](https://blog.csdn.net/zsyzClb/article/details/85171497) 
中食用味道更佳

对于每一个点，可以分为两种情况

1.

这个点不是是割点（去掉这个点以后原图不联通），那么结果就为 (n-1) * 2 ， 就是这个点的居民不能访问别的人，别的人也不能访问这个人

2.

如果这是割点，那么去掉以后就会支离破碎

先定义一个size[u]表示以u为根的子树中有多少个节点

那么在u为割点的情况下，对于每一个子树，我们都

```cpp

ans[i] = ans[i] + size[v] * ( n - size[v] ) ;

```

说明这一个子树中的居民（不包括u）都不能和非子树（这里包括u，因为u被关在里面了嘛）的居民不能来往

并且顺便判断割点

如果这样做，那是肯定会错的

 

因为我们只考虑到了非割点的情况

和

以u为根的子树对外界的来往

而没有考虑到外界对这可树的来往

于是我们定义一个ss数组，表示以i为根的子树的点的数量-1（不包括u，并且当且仅当u对于这棵子树来说是割点的情况）

这里要注意一点，ss != size[u] ，想想这是为什么

所以外界对这可树的来往就要


```cpp
ans[u] =  ans[u] + ( n - ss - 1 ) * ( ss + 1 ) + ( n - 1 )
 
// ( n - ss - 1 ) * ( ss + 1 ) 表示树之外的点对子树的来往
 
// ( n - 1 ) 表示u对其他点的来往

```

因为全部点都是联通的，所以我们只用Tarjan（1）就ok了

代码 ( 希望能够帮到您 )

```cpp
#include <iostream>
#include <cstring>
 
using namespace std ;
 
typedef long long LL ;
 
const int N = 1e5 + 10 ;
const int M = 5e5 + 10 ;
 
struct edge { 
	int v , nxt ;
}e[M<<1] ; int tot , last[N] ;
inline void add ( int u , int v ) {
	e[++tot] = (edge){ v , last[u] } ;
	last[u] = tot ;
	e[++tot] = (edge){ u , last[v] } ;
	last[v] = tot ;
}
	
int n , m ;
 
int id , dfn[N] , low[N] ;
int size[N] ; LL ans[N] ;
bool gedian[N] ; 
 
void Tarjan ( int u ) {
	dfn[u] = low[u] = ++id ;
	size[u] = 1 ; int cnt = 0 , ss = 0 ;
	for ( int i = last[u] ; i != -1 ; i = e[i].nxt ) {
		int v = e[i].v ;
		if ( dfn[v] == 0 ) {
			Tarjan( v ) ; size[u] += size[v] ;
			low[u] = min ( low[u] , low[v] ) ;
			if ( dfn[u] <= low[v] ) {
				cnt ++ ; ss += size[v] ;
				ans[u] += (LL)size[v] * ( n - size[v] ) ;
				if ( u != 1 || cnt > 1 ) gedian[u] = 1 ;
			}		
		}
		else low[u] = min ( low[u] , dfn[v] ) ;
	}
	if ( gedian[u] == 0 ) ans[u] = 2 * ( n-1 ) ;
	else ans[u] += (LL)( n - ss - 1 ) * ( ss + 1 ) + ( n - 1 ) ;
}
int main() {
	cin >> n >> m ; int u , v ;
	tot = -1 , memset ( last , -1 , sizeof( last ) ) ;
	for ( int i = 1 ; i <= m ; i ++ )
		cin >> u >> v , add( u , v ) ;
	memset ( gedian , 0 , sizeof( gedian ) ) ;
	Tarjan( 1 ) ;
	for ( int i = 1 ; i <= n ; i ++ ) 
		cout << ans[i] << endl ;
	return 0 ;
}

```


---

## 作者：Santiego (赞：3)

### 思路

容易想到用$\text{Tarjan}$求割点。对于非割点，会损失$2\times(n-1)$次访问（注意是互相访问，所以要乘2）；对于割点，损失的访问次数即为$\sum^{k}_{i=1}sz[i]\times(n-sz[i])$（割点被删后，产生$k$个联通块，第$i$个联通块大小为$sz[i]$）。在求割点时顺便安装上述分类讨论即可。

注意：求完$u$的子树中所有割点后，还要加上剩下来的大联通块$(n-sum-1)\times(sum+1)$和自己$1\times(n-1)$次访问。

### 代码

```cpp
#include <cstdio>
#define MAXN 100010
#define MAXM 500010*2
#define MIN(A,B) ((A)<(B)?(A):(B))
#define MAX(A,B) ((A)>(B)?(A):(B))
#define ll long long
using namespace std;
int head[MAXN],vv[MAXM],nxt[MAXM],tot;
int read(){
    int w=1,q=0;char ch=' ';
    while(ch!='-'&&(ch<'0'||ch>'9'))ch=getchar();
    if(ch=='-')w=-1,ch=getchar();
    while(ch>='0'&&ch<='9')q=q*10+ch-'0',ch=getchar();
    return w*q;
}
void add_edge(int u, int v){
    vv[++tot]=v;
    nxt[tot]=head[u];
    head[u]=tot;
}
int n,m;
ll ans[MAXN];
int dfn[MAXN],cnt,low[MAXN],sz[MAXN];
void tarjan(int u){
    dfn[u]=++cnt;
    low[u]=dfn[u];
    sz[u]=1;
    int son_sz=0,sum=0;
    bool cut=0;
    for(int i=head[u];i;i=nxt[i]){
        int v=vv[i];
        ++son_sz;
        if(dfn[v]==0){
            tarjan(v);
            low[u]=MIN(low[u], low[v]);
            sz[u]+=sz[v];
            if(low[v]>=dfn[u]){
                sum+=sz[v];
                ans[u]+=(ll)sz[v]*(n-sz[v]);
                if(u!=1) cut=1;
            }
        }else low[u]=MIN(low[u], dfn[v]);
    }
    if(u==1&&son_sz>1) cut=1;
    if(!cut) ans[u]=(n-1)*2;
    else ans[u]+=(ll)(n-sum-1)*(sum+1)+n-1;
}
int main() {
    n=read(),m=read();
    while(m--){
        int a=read(),b=read();
        add_edge(a,b);
        add_edge(b,a);
    }
    tarjan(1);
    for(int i=1;i<=n;++i) printf("%lld\n", ans[i]);
    return 0;
}
```




---

## 作者：command_block (赞：3)

很好的一道tarjan题啊。

看到题面就知道是**缩点双联通分量**就或者**找割点**了。

至于上述两个东西如处理，请右转[模板区](https://www.luogu.org/problemnew/show/P3388)

**缩点双联通分量**或**找割点**都可以解决本题。

两者其实本质是一样的，区别就在于前者常数大，码量大，思想复杂，没有很好的**利用$tarjan$算法的性质**。

所以我们来讲利用割点来求解的(~~复杂度严格O(n+m)的~~)算法。

假如您封锁一个城镇,可以视为把所有与这个点相关的边都断开(也就是**阻止人们进入，离开或者路过那里**)。

这样的话，必然把图分成几部分，这这些部分的大小设为$\Large{c_1,c_2,c_3...c_n}$。

比如说这张图(谁知道出处?)

![](http://img.blog.csdn.net/20130505212216043)

http://img.blog.csdn.net/20130505212216043

可以看到47节点被封锁之后整个图变为了四部分。

那么，对于第i堆的所有人，访问其他堆的愿望都不能满足，访问自己人还是可以的。

所以第i堆的贡献为$\Large{c_i(n(\text{所有c的总和})-c_i})$

怎么知道每个点的$\Large{c}$数组呢？$tarjan$算法可以做到。

```
别小看dfs.
                             ——算法导论
```

$tarjan$这个算法有很多的优秀性质。

求割点的时候，利用了$\large{low[sun]<=dfn[u]}$这个判别，这个判别的意思就是：这个子树中的所有节点都跑不出割点的魔掌，被分割了出去。

也就是说相当于一堆。(不懂看代码)

把这些堆都求出来了之后，别忘记：

1.这个点本身也算一堆。

2.除此之外剩下的都算一堆。

这个算法虽然每个节点的${total_c}$不同，但是${total_c}$的总量为$O(m)$所以复杂度正确。

**P.S** long long要开足!!WA·80-90的注意一下

Code：

```cpp
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector>
using namespace std;
vector<int> g[100500];
int n,m,from,to,tim,
    dfn[100500],low[100500];
long long c[100500],ans[100500];
void dfs(int num,int fa)
{
  low[num]=dfn[num]=++tim;
  ans[num]=0;c[num]=1;
  long long tmp=1;//自己在自己的子树中
  //tmp: 子树节点和 
  for (int i=0,v;i<g[num].size();i++)
   if (!dfn[v=g[num][i]]){
     dfs(v,num);
     c[num]+=c[v];
     low[num]=min(low[num],low[v]);
     if (low[v]>=dfn[num]){
	   ans[num]+=c[v]*((long long)n-c[v]);
	   tmp+=c[v];//某个可以被阻断的子树 
	 }
   }else if (g[num][i]!=fa)
     low[num]=min(low[num],dfn[v]);
  ans[num]+=1*(n-1);//算这个点本身成一块
  ans[num]+=((long long)n-tmp)*tmp;//剩下不在dfs搜索树字树中的 
}
void t(int root)
{
  //对根的特殊处理，类似上面
  low[root]=dfn[root]=++tim;
  ans[root]=0;
  int tmp=0;
  for (int i=0,v;i<g[root].size();i++)
   if (!dfn[v=g[root][i]])
    {tmp++;dfs(v,root);ans[root]+=((long long)n-c[v])*c[v];}
  ans[root]+=1*(n-1); 
}
int main()
{
  scanf("%d%d",&n,&m);
  for (int i=1;i<=m;i++){
    scanf("%d%d",&from,&to);
    g[from].push_back(to);
    g[to].push_back(from);
  }t(1);
  for (int i=1;i<=n;i++)
   printf("%lld\n",ans[i]);
}
```

[AC记录](https://www.luogu.org/recordnew/show/15031747)

---

## 作者：斯茂 (赞：3)

像往常一样，我这个渣渣看不懂任何一个题解

所以自己来写一个

说一下这题的思路吧

首先非常显然，这题和割（鸽）点的过程有关。（但是并不需要真正求出来）

割点的原理相信大家都知道，不知道的建议先做割点模板

进行tarjan的过程中，如果在搜索树上，一个点的一棵子树的low>=dfn，那么在该点断开后，这棵子树将不能到达该点的祖先和兄弟们。这时候我们就要进行计数。

但是，计数的最大难点就在于怎么能不重不漏的计算到所有情况。

为了不数重，记size[i]为i所在子树大小，ua为在考虑x这个点所在子树是，已经计算过的无法到达x的祖先，兄弟的子树的大小之和（理解一下这句话）

考虑第k棵子树时，如果它的low<dfn，不管他，否则记
```
ua+=size[x.son[k]]; ans[x]+=2*size[x.son[k]]*(n-ua-1) 

```

至于为什么要*2，因为是有序数对

当然把一个点断开后，其他店都不能到它，它也不能到其他点，所以:
```
ans[i]+=2*(n-1)
```
此题保证原图联通，所以直接tarjan(1,0)就行了

如果看不懂公式可以参考我的代码，感觉代码更容易理解一点。



```
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
int n;
int dfn[100005], low[100005], sz[100005], cnt;
long long ans[100005];
vector <int> V[100005];
void tarjan(int x, int f)
{
  int i, r, SZ = 1, ua = 0;//SZ是此树为根的子树大小，ua是目前已经枚举到的在x断开后不能与祖先相连的点集大小 
  dfn[x] = low[x] = ++cnt;
  for(i = 0; i < V[x].size(); i++)
  {
    r = V[x][i];
    if(r == f) continue;
    if(!dfn[r])
    {
      tarjan(r, x);
      SZ += sz[r];
      low[x] = min(low[x], low[r]);
      if(low[r] >= dfn[x])//这棵子树回不去
	  {
	    ua += sz[r];
		ans[x] += (long long)2 * sz[r] * (n - ua - 1);
	  }
	}
	else
	  low[x] = min(low[x], dfn[r]);
  }
  sz[x] = SZ;
  ans[x] += 2 * (n - 1);
}
int main(int argc, char **argv)
{
	int m, a, b, i;
	scanf("%d %d", &n, &m);
	for(i = 1; i <= m; i++)
	{
	  scanf("%d %d", &a, &b);
	  V[a].push_back(b);
	  V[b].push_back(a);
	}
	tarjan(1, 0);
	for(i = 1; i <= n; i++)
	  printf("%lld\n", ans[i]);
	return 0;
}

```

---

## 作者：_louhc (赞：1)

# [P3469[POI2008]BLO-Blockade](https://www.luogu.org/problemnew/show/P3469)
~~这次是BLO。。。不是LO了QAQ~~ ---致管理员

------

# 算法

Tarjan找割点

# 思路

> I.设在搜索树T中以x为根的树包含的点集为SubTree(x)。
>
> II.这里去除割点可以理解为删除与该点相连的所有边。
>
> III.这里提到的连通块是指当某一割点去除时：1.其中任何两个点都能相互到达 2.没有更大的连通块包含该块 当然，根据II，我们把单独的X也看做一个连通块
>
> IV.为了方便，我们直接将(x,y)(满足x不能到y)成为“点对”
>
> V. ~S：S的补集，A^B：在A中不包括点B的所有点构成的集合

利用Tarjan查找割点的同时，我们可以找出该割点X去除后剩余的连通块（有两种情况，一种是在SubTree(X)^X中，另一种是~SubTree(X)）。

只要能够理解割点的求解过程，这还是很好理解的，这里不再赘述。

然后要求“点对”。

对于一个点X，不管是否为割点，点对(i,j)为“点对”，当且仅当

> i != j且i、j属于两个不同的连通块

根据定义，很容易证明这个推论。

代码有多种写法，这里选取**我能想到的**最简单的写法。

在枚举连通块时，ans加上`s[to[i]] * ( n - s[to[i]] )`，即一次性处理一个连通块的所有点，它们与其他不属于这个连通块的点都构成“点对”。当然，别忘了X与~SubTree(X)。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define MAXN 100005
#define MAXM 1000005

int n, m;
int hd[MAXN], nxt[MAXM], to[MAXM], tot;
int dfn[MAXN], low[MAXN], root, num;
LL ans[MAXN];
int s[MAXN];

void Add( int x, int y ){ nxt[++tot] = hd[x]; hd[x] = tot; to[tot] = y; }

void DFS( int x ){
	s[x] = 1;
	low[x] = dfn[x] = ++num;
	LL b(0);
	for ( int i = hd[x]; i; i = nxt[i] ){
		if ( !dfn[to[i]] ){
			DFS( to[i] ); s[x] += s[to[i]];
			low[x] = min( low[x], low[to[i]] );
			if ( dfn[x] <= low[to[i]] ) ans[x] += (long long)s[to[i]] * ( n - s[to[i]] ), b += s[to[i]];//发现新的连通块！
		} else low[x] = min( low[x], dfn[to[i]] );
	}
	ans[x] += (long long)( n - b - 1 ) * ( b + 1 ) + ( n - 1 );//算上~SubTree(X)与X
}

int main(){
	scanf( "%d%d", &n, &m );
	for ( int i = 1; i <= m; ++i ){
		int x, y; scanf( "%d%d", &x, &y ); Add( x, y ); Add( y, x );
	}
	DFS( 1 );
	for ( int i = 1; i <= n; ++i ) printf( "%lld\n", ans[i] );
	return 0;
}

```



---

## 作者：Doubeecat (赞：1)

## 题目链接：

[[POI2008]BLO-Blockade](<https://www.luogu.org/problem/P3469>)

## 题目描述：

有 $n$ 个节点的无向图，定义封锁一个点为切断这个点的所有连边。求每个节点被封锁后图内的不连通有序点对个数。

## 解题思路：

Tarjan。

首先分类讨论一下，封锁一个点有两种情况：

1. 不是割点

   这种情况好搞，从图中显然可以看出只有自己和其他 $n - 1 $ 个节点不连通，因为是有序节点，所以答案为 $2 \times (n-1)$

   ![](https://s2.ax1x.com/2019/09/08/n3Muo8.png)

2. 是割点

   这种情况就有意思了。

   我们可以发现，如果点 i 为割点，显然去掉这个点之后整个图会变成几个联通块，如下图：

   ![](https://s2.ax1x.com/2019/09/08/n3MWFO.png)

   这种情况我们也很好发现，把联通块的大小两两相乘可得答案。

   记第 i 个联通块为$s_i$

   但是把联通块大小两两相乘的复杂度为 $O(n^2)$ 不能接受，我们可以在 dfs 时把搜索树子树大小算出来，记为 $siz[i]$

   最后的答案即为： 

   $(n - 1 - \sum_{i=1}^{t}siz[s_k])*(1+\sum_{i=1}^{t}siz[s_k])$ 

## 代码：

```cp
#include <cstdio>
#include <cctype>
#include <algorithm>
using namespace std;
const int N = 100010;
const int M = 500010<<1;
inline int read() {
	int x = 0,f = 1;char v = getchar();
	while (!isdigit(v)) {if (v =='-') f = -1;v = getchar();}
	while (isdigit(v)) {x = x * 10 + v - 48;v = getchar();}
	return x * f;
}
int nxt[M],hd[N],to[M],tot = 1,cnt,dfn[N],low[N],siz[N],n,m;
long long ans[N];
bool cut[N];

inline void adde(int u,int v) {
	to[++tot] = v;nxt[tot] = hd[u];hd[u] = tot;
}

inline void addedge(int u,int v) {
	adde(u,v);adde(v,u);
}

void tarjan(int x) {
	dfn[x] = low[x] = ++cnt;
	siz[x] = 1;
	int flag = 0,sum = 0;
	for (int i = hd[x];i;i = nxt[i]) {
		int v = to[i];
		if (!dfn[v]) {
			tarjan(v);
			low[x] = min(low[x],low[v]);
			siz[x] += siz[v];
			if (low[v] >= dfn[x]) {
				flag++;
				ans[x] += (long long)siz[v]*(n - siz[v]);
				sum += siz[v];
				if (x != 1 || flag > 1) {
					cut[x] = 1;
				}
			}
		}	
		else {
			low[x] = min(low[x],dfn[v]);
		}
	}
	if (cut[x]) {
		ans[x] += (long long)(n - sum - 1) * (sum + 1) + (n - 1);
	}
	else {
		ans[x] = 2*(n-1);
	}
}

int main() {
	n = read(),m = read();
	for (int i = 1;i <= m;++i) {
		int x = read(),y = read();
		if (x == y) {
			continue;
		}
		addedge(x,y);
		
	}
	tarjan(1);
	for (int i = 1;i <= n;++i) {
		printf("%lld\n",ans[i]);
	}
	return 0;
}
```

## 参考：

部分思路来自于lyd的《算法竞赛进阶指南》



---

## 作者：寒鸽儿 (赞：1)

[博客食用效果更佳](https://www.luogu.org/blog/oldherd/solution-p3469)
### tarjan割点ex
由题意可知，我们所求的是割掉点之后产生的非连通块之间的关系。  
如果这个点不是割点，那么它会被孤立然而剩下的n-1个点仍然连通。所以一共增加了2(n-1)个非连通有序点对。  
判断割点很容易想到tarjan算法。不是割点的点自然可以直接判断答案为2(n-1)。  
既然用到了tarjan，我们不妨深入挖掘其性质，看看能否求得删除割点后的答案。  
一个结点x是割点，当它不为根结点且有至少一个子节点y满足dfn[y]>=low[x]或者它为根节点但有至少两个结点满足上述割点判定式。  
由此联想到，如果删除了一个割点x，那么满足上述判别式的子树均独立成为一个连通块，且不与子树外的结点连通。  
所以删除割点后的局面就是，各满足判别式的子树成独立的连通块，该割点成独立连通块，剩余结点构成独立的连通块。只要我们求出每块的大小，由数学方法很容易推出计算公式来。  
由于我们做tarjan算法是沿着搜索树的，故而可以很容易地递推统计出子树的大小。
```
删掉割点的答案： t[1]*(n-t[1])+t[2]*(n-t[2])+... + (n-1) + (1+sum)*(n-sum-1)
删掉非割点的答案： 2*(n-1)
```
附上ac代码
```cpp
#include <cstdio>
#include <cstring>

using namespace std;

const int maxn = 100010, maxm = 500010;
int n;

#define min(x, y) (x) < (y) ? (x) : (y)

int head[100010], ver[maxm<<1], nex[maxm<<1], tot;

inline void addedge(int u, int v) {
    ver[tot] = v; nex[tot] = head[u]; head[u] = tot++;
}

long long ans[maxn];
int dfn[maxn], low[maxn], cut[maxn], size[maxn], dfs_clock = 1;

inline void tarjan(int cur) {
    dfn[cur] = low[cur] = dfs_clock++; size[cur] = 1;
    int flag = 0, sum = 1;
    for(int i = head[cur]; i != -1; i = nex[i]) {
        if(!dfn[ver[i]]) {
            tarjan(ver[i]);
            low[cur] = min(low[cur], low[ver[i]]);
            size[cur] += size[ver[i]];
            if(dfn[cur] <= low[ver[i]]) {
                flag++;
                sum += size[ver[i]];
                ans[cur] += (long long)(n - size[ver[i]]) * size[ver[i]];
                if(cur != 1 || flag > 1) cut[cur] = 1;
            }
        } else {
            low[cur] = min(low[cur], dfn[ver[i]]);
        }
    }
    if(cut[cur]) ans[cur] += (n - 1) + (long long)(n - sum) * sum;
    else ans[cur] = 2 * (n - 1);
}

int main() {
    int m, u, v;
    scanf("%d %d", &n, &m);
    memset(head, -1, sizeof(head));
    while(m--) {
        scanf("%d %d", &u, &v);
        addedge(u, v); addedge(v, u);
    }
    tarjan(1);
    for(int i = 1; i <= n; i++)
        printf("%lld\n", ans[i]);
    return 0;
}
```
欢迎互相关注(然而在oi界蒟蒻的圈很小)。  
最后再次安利一下[蒟蒻的洛谷博客](https://www.luogu.org/blog/oldherd/)

---

## 作者：dread (赞：0)

- 既然刚学了割边割点，我就来写一波题解。。
1. 根据割点的定义，若节点$i$不是割点，就把节点i关联的所有边都去掉后，只有与其他$n - 1$个节点之间是联通的。但是因为题目中$(x,y)$与$(y,x)$算不同的点对，所以答案为$2*(n - 1)$。
2. 若节点$i$是割点，则把节点$i$关联的边去掉后，图会分成若干个连通块。我们需要求出连通块的大小，两两相乘再相加。设在搜索树上，节点$i$的子节点集合中，有$t$个点$s_{1},s_{2},s_{3},...,s_{t}$满足割点的判定法则$dfn[i]\leq low[s_{k}]$。最后会变成至多$t + 2$个连通块。
3. 我们可以在tarjan算法深搜的时候，顺便求出每棵子树的大小。若$size[x]$为以$x$为根的子树大小。最后的答案很明显就是
$\sum_{k = 1}^{t}size[s_{k}]*(n - size[s_{k}]])+1*(n-1)+(n-1-\sum_{k = 1}^{t}size[s_{k}])*(1+\sum_{k = 1}^{t}size[s_{k}])$
# Code:

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 1e5 + 10, M = 5e5 + 10;
struct edge {
	int y, nxt;
}e[M * 2];
int lin[M], len = 1;
int dfn[N], low[N], num, size[N];
int n, m;
ll ans[N];
bool cut[N];
inline ll read() {
	ll s = 0, f = 1;
	char ch;
	for(; ch < '0' || ch > '9'; ch = getchar())	if(ch == '-')	f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar())	s = (s << 1) + (s << 3) + ch -'0';
	return s * f;
}

inline void insert(int xx, int yy) {
	e[++len] = {yy, lin[xx]};
	lin[xx] = len;
	e[++len] = {xx, lin[yy]};
	lin[yy] = len;
}

inline void tarjan(int x) {
	dfn[x] = low[x] = ++num;
	size[x] = 1;
	int flag = 0, sum = 0;
	for(int i = lin[x]; i; i = e[i].nxt) {
		int y = e[i].y;
		if(!dfn[y]) {
			tarjan(y);
			size[x] += size[y];
			low[x] = min(low[x], low[y]);
			if(low[y] >= dfn[x]) {
				flag++;
				ans[x] += (ll)size[y] * (n - size[y]);
				sum += size[y];
				if(x != 1 || flag > 1)	cut[x] = 1;
			}
		} else low[x] = min(low[x], dfn[y]);
	}
	if(cut[x])	ans[x] += (ll)(n - sum - 1) * (sum + 1) + (n - 1);
	else	ans[x] = 2 * (n - 1);
}

int main() {
	n = read();
	m = read();
	for(int i = 1; i <= m; ++i)	{
		int xx = read(), yy = read();
		if(xx == yy)	continue;
		insert(xx, yy);
	}
	tarjan(1);
	for(int i = 1; i <= n; ++i)	printf("%lld\n", ans[i]);
	return 0;
}
```
求过

---

