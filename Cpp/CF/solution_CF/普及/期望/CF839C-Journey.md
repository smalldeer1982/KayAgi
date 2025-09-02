# Journey

## 题目描述

## 问题描述

在七大王国里有 $n$ 个城市和 $n-1$ 条道路，每条道路连接两个城市，并且通过这些道路我们可以从任何一个城市到达任何一个城市。

席恩和阿莎在第一个城市骑上马，他们要通过这些路开始一次旅行。但是有雾，所以他们看不见他们的马带他们去了哪里。当马抵达一个城市的时候（包括第一个城市），它会去跟当前这个城市相连的城市。但是这是一匹奇怪的马，它只去他们以前没有去过的城市。在每个城市，马以相同的概率移动去上述符合要求的城市，并且当没有这样的城市（可走）时，马就停下了。

每条路的长度都是 $1$，旅行从城市 $1$ 开始，问这次旅行的期望长度（旅行长度的期望值）是多少？你可以通过[这个链接](https://en.wikipedia.org/wiki/Expected\_value)来阅读一些关于期望（平均）值的文字。

## 说明/提示

在第一个例子中，他们的旅行可能以同等的概率停止于城市 $3$ 或城市 $4$。去城市 $3$ 的距离是 $1$，去城市 $4$ 的距离是 $2$，所以期望是 $1.5$。

在第二个例子中，他们的旅行可能停止于城市 $4$ 或城市 $5$。去这些城市的距离都是 $2$，所以期望是 $2$。

## 样例 #1

### 输入

```
4
1 2
1 3
2 4
```

### 输出

```
1.500000000000000
```

## 样例 #2

### 输入

```
5
1 2
1 3
3 4
2 5
```

### 输出

```
2.000000000000000
```

# 题解

## 作者：E1_de5truct0r (赞：7)

## 思路

这道题其实并不难，容易的点就在于这是一棵树，否则大概率要评 2400+ 了。我一开始想了 3 分钟没思路就是没看到这是棵树。

首先，你需要知道一个树的性质：

- 任意两点之间的最短路径是唯一的。

	这个很好证明，因为如果不是唯一的，那么显然树上存在环，和树的定义矛盾。因此得证。

那么再回来看这道题。就可以用树形 dp 解决了。

令 $dp_i$ 表示从 $i$ 向 $i$ 的子树走，步数期望值是多少。

显然的，$i$ 的期望等于它所有儿子的期望 +1。那么转移方程就推出来了：

$dp_i = \dfrac{\sum\limits_{v \in son_i} dp_v+1}{|son_i|}$

最后的输出就是 $dp_1$。

## 代码

```cpp
#include <cstdio>
#include <vector>
using namespace std;
double dp[100005];
vector<int> E[100005];
void dfs(int u,int fa)
{
	int cnt=0;
	for(int i=0;i<E[u].size();i++)
	{
		int v=E[u][i];
		if(v==fa) continue;
		dfs(v,u);
		dp[u]+=(dp[v]+1.0);
		cnt++;
	}
	if(cnt) dp[u]/=(double)cnt;
}
int main()
{
	int n; scanf("%d",&n);
	for(int i=1;i<n;i++) 
	{
		int x,y; scanf("%d%d",&x,&y);
		E[x].push_back(y);
		E[y].push_back(x);
	}
	dfs(1,0);
	printf("%.10lf",dp[1]);
	return 0;
}
```

---

## 作者：caidzh (赞：4)

蒟蒻终于自己想出了期望题！~~这么蠢的东西自己想出来也没用。。。~~

首先我们知道旅行结束一定是在叶子结点上，所以最终答案一定是叶子结点的期望的总和

那么怎么计算叶子结点的期望呢？这个期望可以认为是根到叶子结点的距离乘上到达这个叶子结点的概率。由于不能走回头路，所以距离很好求，可以通过一次$dfs$完成

接下来考虑概率的计算，我们可以这样考虑，在一个岔路口，我们以等同的概率分开，相当于原来的概率分流出去（可以自己想象一下），这也可以在$dfs$传入一个参数来模拟这个过程，搜到叶子时的参数就是这个概率

代码如下
```
#include<bits/stdc++.h>
using namespace std;
int inline read(){
    int num=0,neg=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')neg=-1;c=getchar();}
    while(isdigit(c)){num=(num<<3)+(num<<1)+c-'0';c=getchar();}
    return num*neg;
}
const int maxn=100010;
int n,head[maxn],cnt,out[maxn],dep[maxn];double ans;
struct Edge{int nxt,to;}edge[maxn<<1];
void add_edge(int x,int y){edge[++cnt].nxt=head[x];edge[cnt].to=y;head[x]=cnt;}
void dfs(int x,int fa,double exp){
	int flag=0;dep[x]=dep[fa]+1;
	for(int i=head[x];i;i=edge[i].nxt){
		int v=edge[i].to;if(v==fa)continue;flag=1;
		if(fa==0)dfs(v,x,exp*(1.0/out[x]));else dfs(v,x,exp*(1.0/(out[x]-1)));
	}if(!flag)ans+=(double)(dep[x]-1)*exp;
}
int main()
{
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add_edge(u,v);add_edge(v,u);out[v]++;out[u]++;
	}dfs(1,0,1);printf("%.9lf",ans);
	return 0;
}
```


---

## 作者：Lauzun (赞：2)

终于来了一道蓝题$qwq$

最近正在重学期望，就来了这么一道期望加DFS练练手

首先先给出期望的计算公式：期望=概率$*$代价

本题中概率即 **父节点的概率/当前节点所能到达的点数（注意根节点所能到达的点数即为它的边数，而其他除叶节点之外的节点所能达到的点数为它的边数$ - 1$，因为它的边有一条是通向父节点的，而父节点马已经去过了，显然是不能回去的）**；而代价呢，就是**节点深度**。

我们猛然发现，这两个东西都可以由DFS得到啊

然后继续观察题目可知，一共$n$个点，$n - 1$条边，显然这是一棵树

$so$，我们从根节点开始搜索，枚举它的每一条边，然后继续搜子节点，概率变为父节点概率（根节点即为$1$）$/$节点边数，把代价（深度）$+ 1$。

搜索到第二个节点，继续枚举每一条边，搜索子节点，概率变为父节点概率（即由根节点计算得到的概率）$/$（节点边数 $- 1$）（至于为什么要$- 1$，上面已经解释清楚了），把代价$+ 1$。

搜索到叶节点，没有可以只有一条边与其父节点相连，又不能走回去，所以就可以计算答案了。答案就是概率$*$代价，即前面计算得到的概率 $*$  前面计算得到的深度。然后返回就可以了。

具体怎么实施代码里面的注释应该已经写得很清楚了，希望$dalao$包容小萌新。

一些小细节：

1、关于如何让马不往回走，即如何让搜索不往回搜。可以$bool$一个$flag$数组，初始化用$memset$全部弄成$false$，如果访问过了就变成$true$。每次遍历边的时候判断一下就好了。

2、关于存图。一共两种存图方式，可能各位前向星用的比较多，但$vector$好写好想好遍历本蒟蒻就用$vector$啦$qwq$。

3、如何判断到了叶节点。大概两个条件，首先这个节点的边数为$1$，其次它不是根节点。

奉上AC代码
```cpp
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#define maxn 100005
using namespace std;
int n;//总的城市数 
double ans = 0;//记录答案，记得要使用double类型 
bool fl[maxn];//判定此点是否被访问过 
vector<int> q[maxn];//存图用的 

int dfs( int x, double qw, int len ) {//利用DFS进行期望计算 
	if( q[x].size() == 1 && x != 1 ) {//q.size为1并且此时不在根节点，即已经到了叶节点 
		ans += qw * len;//计算答案，期望计算方法为代价*概率，qw为概率，len（即深度）就是代价 
		return 0;
	}
	for( int i = 0; i < q[x].size(); i ++ ) {//遍历 
		int k = q[x][i];
		if( fl[k] == false ) {//没访问过才访问（不然就可能顺着根回去了） 
			fl[k] = true;
			if( x == 1 ) {
				dfs( k, qw * 1 / q[x].size(), len + 1 );
			}
			else dfs( k, qw * 1 / ( q[x].size() - 1 ), len + 1 ); 
		}
	}
}

int main() {
	scanf("%d",&n);
	for( int i = 1; i < n; i ++ ) {
		int x, y;
		scanf( "%d %d", &x, &y );
		q[x].push_back( y );
		q[y].push_back( x );//Vector存图，没必要前向星，怎么简单怎么来 
	}
	memset( fl, false, sizeof( fl ) );
	fl[1] = true;
	dfs( 1, 1, 0 );
	printf( "%.15lf", ans );
}
```

感觉自己还有很多地方写得不到位，希望各位理解啦$qwq$

---

## 作者：bryce (赞：1)

正在学概率期望，正好遇上了一道。

## 思路

### 一、存树

应该没什么好讲的。

[链式前向星](https://www.cnblogs.com/riced/p/13776297.html)不懂的同学自己看链接，这里就不讲解了。

### 二、求概率

我们观察一下样例一。

```cpp
4
1 2
1 3
2 4
```

我们把它转化为树的形式，以 1 为根。

![](https://cdn.luogu.com.cn/upload/image_hosting/dkj2yqtv.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

因为马以相同的概率向子节点移动，所以马从节点 1 移动到节点 2 和节点 3 的概率是相等的。

因为节点 2 只有一个子结点，所以马一定会移动到节点 4。

综上所述，节点 1 到节点 2 和节点 3 的概率为 $\dfrac{1}{2}$，而节点 1 到节点 4 的概率为节点 2 的概率乘上节点 4 的概率，可以得到 $p(4)=\dfrac{1}{2} \times 1 = \dfrac{1}{2}$。

于是我们可以用搜索求出父亲节点的概率，再求子节点的概率。

### 三、求期望

首先我们要知道求期望的公式。

$$E(x) = \sum_{i\in S}p(i)\times i$$

因为旅途只会在叶子节点停止，所以旅行的期望长度就为所有叶子节点的期望总和。

于是可以得到，叶子节点的期望就为叶子结点的深度乘上叶子节点的概率，而深度也可以用搜素求。

然后期望就可以求出来了。

## 代码

```cpp
#include<iostream>
#include<iomanip>

using namespace std;

int n, head[100001], cnt;
int f[100001];
double dt[100001], p[100001], ans;//dt表示深度，p表示概率

struct node{
	int to, nxt;
}e[200001];

void add(int u, int v){//存树
	cnt++;
	e[cnt].to = v;
	e[cnt].nxt = head[u];
	head[u] = cnt;
}

void dfs(int u, int v, int d){//求出概率和深度
	double size = 0;
	for (int i = head[u]; i; i = e[i].nxt){
		if (e[i].to != v){
			size++;
		}
	}
	for (int i = head[u]; i; i = e[i].nxt){
		if (e[i].to != v){
			p[e[i].to] = p[u] * (double)1 / size;
			dt[e[i].to] = d;
			dfs(e[i].to, u, d + 1);
		}
	}
}

void build(int u, int v){//求出叶子节点并计算答案
	int size = 0;
	for (int i = head[u]; i; i = e[i].nxt){
		if (e[i].to != v){
			size++;
		}
	}
	if (size){
		for (int i = head[u]; i; i = e[i].nxt){
			if (e[i].to != v){
				build(e[i].to, u);
			}
		}
	}else{
		ans += (double)dt[u] * p[u];
	}
}

int main(){
	cin >> n;
	for (int i = 1; i < n; i++){
		int u, v;
		cin >> u >> v;
		add(u, v);
		add(v, u);
	}
	p[1] = 1.0;
	dt[1] = 0;
	dfs(1, 0, 1);
	build(1, 0);
	cout << fixed << setprecision(10) << ans;
	return 0;
}
```

完结，点个赞吧。

---

## 作者：Overstars (赞：1)

CF刷DP专题做到了这题，这道题是真的妙，特意开通了博客来写这道题的题解。

先来看下期望数学公式，离散型随机变量$X$的数学期望可表示为
$$E(X)=\sum_{i=1}^nx_ip_i$$
式中$p_i$为事件$x_i$发生的概率。

所以在该节点向下行走的期望长度就等于$ \sum$子节点行走概率$\times$子节点期望长度$+1$。($+1$是因为多出来了父节点到子节点的距离）

我们令$dp[i]$表示$i$号节点向下行走长度的数学期望。因为叶子节点不能向下行走，所以叶子结点的期望显然为0。

我们需要在dfs的过程中为无向图定向，统计每个结点的出度（即这个节点有多少个子节点），方便计算概率。人物在节点$x$上时，向各个子结点行走的概率相等，都为$\frac{1}{outdeg(x)}$，在回溯的过程中进行期望计算$x$节点期望即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100005;
struct edge
{
	int v,nex;
} e[maxn<<1];
double dp[maxn];
int head[maxn],cnt,deg[maxn];
inline add(int u,int v)
{
	e[++cnt].v=v;
	e[cnt].nex=head[u];
	head[u]=cnt;
}
void dfs(int x,int fa)
{
	for(int i=head[x];~i;i=e[i].nex)
	{
		int v=e[i].v;
		if(v==fa)
			continue;
		deg[x]++;//统计出度
		dfs(v,x);
	}
	for(int i=head[x];~i;i=e[i].nex)
	{
		int v=e[i].v;
		if(v==fa)
			continue;//回溯,计算期望
		dp[x]+=(double)(1.0/deg[x])*(dp[v]+1);
	}
}
int main()
{
	memset(head,-1,sizeof(head));
	int n,u,v;
	cin>>n;
	for(int i=1;i<n;i++)
	{
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	dfs(1,0);
	cout<<setiosflags(ios::fixed)<<setprecision(9)<<dp[1]<<endl;
	return 0;
}
```
第一次在洛谷上写题解，有什么不当之处希望大家指出QAQ。




---

## 作者：L_Y_T (赞：1)

### 蒟蒻用了一个十分麻烦的方法....

___
思路:设f[i]代表从1号节点走到i号节点的概率,deep代表i号节点的深度(设1好节点深度为0).

那么,由于这是一颗树,所以 只要统计每个叶节点到根节点的距离(也就是叶节点的深度)与从根节点走到i号节点的概率 求和就可以了


从u节点走到下一个节点的概率是 1/son[u] (son[i]代表i号节点的子节点个数)

设fa[i]为i的父节点
则f[i] = f[fa[i]] * (1.0/son[i]) 

最后统计叶节点 deep[left] * f[i]就好了

___

至于我的做法:
>首先用vector存图,求出树的深度,并记录树节点的遍历顺序,重新进行建(单向向下的)树,然后进行dfs到tree[u].size()为0(没有儿子,也就是叶节点)的点,进行求和

___
```cpp
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <vector>
#define maxn 100010
using namespace std ;
int n ;
vector<int>tree[maxn] ;
int read(){
	int x = 0 , f = 1 ; char s = getchar() ;
	while(s > '9' || s < '0') {if(s == '-') f = -1 ; s = getchar() ;}
	while(s <='9' && s >='0') {x = x * 10 + (s-'0'); s = getchar() ;}
	return x*f ;
}double f[maxn] ;
int deep[maxn] , vis[maxn] , F[maxn] ;
void dfs(int u ,int fa,int dep) {
	deep[u] = dep + 1 ;
	vis[u] = 1 ; 
	F[u] = fa ;  
	for(int i = 0 ; i < tree[u].size() ; i ++ ) {
		int v = tree[u][i] ;
		if(vis[v] || v == fa) continue ;
		dfs(v,u,dep+1) ;
	}
} 
double ans = 0 ;
void Dfs(int u) {
	vis[u] = 1 ;
	if(!tree[u].size()) {
		ans += f[F[u]]*deep[u] ;
	}else
	f[u] = f[F[u]]*(1.0/tree[u].size()) ;
	for(int i = 0 ; i < tree[u].size() ; i ++) {
		int v = tree[u][i] ;
		Dfs(v) ;
	}
}
int main () {
	n = read() ;
	for(int i = 1 ; i < n ; i ++) {
		int x = read() , y = read() ;
		tree[x].push_back(y) ;
		tree[y].push_back(x) ; 
	}dfs(1,0,-1) ;
	f[0] = 1 ;
	memset(vis,0,sizeof(vis)) ;
	memset(tree,0,sizeof(tree)) ;
	for(int i = 1 ; i <= n ; i ++) {
		tree[F[i]].push_back(i) ;
	}
	Dfs(1) ;
	printf("%.15lf",ans) ;
	return 0 ;
}
```

---

## 作者：曼恩薄荷 (赞：1)

作为一个不会期望概率的数学蒟蒻，竟然靠着自己的YY，打出了这道题。有点小骄傲，看到还没有题解，便发篇题解庆祝一下。



------------


我的大体思路如下：
利用bfs，求出从1号点到其他各个点的概率rk[i]。
同时由于边权只有1，所以在广搜过程中，也可以顺便求出1号点到各个点的距离dis[i]。
如果当前搜到的点已经没有可以扩展的点的话，那么就用这个点的rk和dis累加答案即可。
下面上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;

struct Edge{
	int to,next;
}e[maxn*2];


int head[maxn],dis[maxn],chu[maxn];
int n,k,vis[maxn];
double ans,rk[maxn];

void bfs()
{
	vis[1] = 1;
	rk[1] = 1.0000;//必然会到1号点，概率为1。 
	queue<int>q;
	q.push(1);
	while(!q.empty())//广搜过程 
	{
		int u = q.front();
		q.pop();
		vis[u] =  1;
		vector<int>next;
		for(int i=head[u];i;i=e[i].next)//统计这个点能到达的点的数量。 
		{
			int to = e[i].to;
			if(!vis[to])
				next.push_back(to); 
		}
		if(!next.size())//如果这个点已经无法继续扩展，就更新答案。 
		{
			ans += (double)(dis[u]*rk[u]);
			continue;
		}
		for(int i=0;i<next.size();i++)//继续扩展，同时计算出下个点的距离,和概率。 
		{
			int to = next[i];
			dis[to] = dis[u] + 1;
			rk[to] = rk[u]*(double)(1.000000/next.size());//下个点期望 = 当前点概率*到达每个点的概率(古典概型了解一下QwQ)
			q.push(to);
		}
	}
}

void add(int u,int v)//邻接表存边。 
{
	e[++k].to = v;
	e[k].next = head[u];
	head[u] = k;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	bfs();
	printf("%.6lf",ans);
	return 0;
}
```

---

## 作者：Scinerely (赞：0)

# Journey
## 问题描述

在七大王国里有 $n$ 个城市和 $n-1$ 条道路，每条道路连接两个城市，并且通过这些道路我们可以从任何一个城市到达任何一个城市。

席恩和阿莎在第一个城市骑上马，他们要通过这些路开始一次旅行。但是有雾，所以他们看不见他们的马带他们去了哪里。当马抵达一个城市的时候（包括第一个城市），它会去跟当前这个城市相连的城市。但是这是一匹奇怪的马，它只去他们以前没有去过的城市。在每个城市，马以相同的概率移动去上述符合要求的城市，并且当没有这样的城市（可走）时，马就停下了。

每条路的长度都是 $1$，旅行从城市 $1$ 开始，问这次旅行的期望长度（旅行长度的期望值）是多少？

## 题目分析
$n$ 个城市和 $n-1$ 条道路，这不是刚好一颗树吗！

这是一道有关期望的题目。题目问的是，旅行的期望长度。现在，思考一下，旅行的终点点会在哪里。从树的根节点出发，每次不会走回头路，只会向当前节点的儿子节点行进，那么终点只会在整棵树的叶子节点。仔细思考一下是不是。

接下来思考怎么求出答案。首先，期望有线性性：
$$E(AB)=E(A)+E(B)$$

根据这个，对于本题而言，旅行的期望长度，可以变成走到所有叶子节点的路程期望之和。有了大体的思路，接下来，就看怎么算了。有：

$$E(x)=\sum_{i\in S}p(i)\times i$$

考虑怎么求出 $p(i)$。这个十分简单，如果设节点 $i$ 的儿子数量为 $a_i$ ,知道了这些，我们可以求出到达他的每一个儿子节点的概率 $p(son)$ :
$$p(son)=\dfrac {p(i)}{a_i}$$

我们知道的，根节点 $1$ 城市就是起点，到达的概率是 $100%$ ，通过上述的方式，可以知道到达整棵树每个节点的概率。

最后，到达每个叶子节点 $i$ 的路程是 $dep_i$ ，那么 $E(i)=dep_i\times p(i)$ 
将每个叶子节点的期望统计，就是我们所求的答案。

代码实现如下：

# $code$
```
#include<bits/stdc++.h>
#define ll long long
#define MAXN 100010
using namespace std; 
inline ll read(){ll x=0,f=1;char ch=getchar();if(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
inline void write(int x){if(x==0){putchar('0');return;}if(x<0){putchar('-');x=-x;}char s[22];int tmp=x,cnt=0;while(tmp>0){s[cnt++]=tmp%10+'0';tmp/=10;}while(cnt>0) putchar(s[--cnt]);} 
ll n,cnt,head[MAXN*2];
double p[MAXN],ans,dep[MAXN];
struct tree{ll next,to;}t[MAXN*2];
void add(ll f,ll e){
	cnt++;
	t[cnt].to=e;
	t[cnt].next=head[f];
	head[f]=cnt;
}
void dfs1(ll x,ll dad,ll d){
	double sum=0;
	for(int i=head[x];i;i=t[i].next){
		if(t[i].to!=dad) sum++;
	}
	for(int i=head[x];i;i=t[i].next){
		if(t[i].to!=dad){
			p[t[i].to]=(double)p[x]/sum;
			dep[t[i].to]=d+1;
			dfs1(t[i].to,x,d+1); 
		}
	}
}
void dfs2(ll x,ll dad){
	ll sum=0;
	for(int i=head[x];i;i=t[i].next){
		if(t[i].to!=dad) sum++;
	}
	if(sum==0){
		ans+=(double)p[x]*dep[x];//askdfsuyhdfshdasyhgfasdhgfas
		return ;
	}
	for(int i=head[x];i;i=t[i].next){
		if(t[i].to!=dad){
			dfs2(t[i].to,x);
		}
	}
}
int main(){
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
	n=read();
	for(int i=1;i<n;i++){
		ll first=read(),end=read();//s'd'k'fu'y'h's'g'du'f'sDjhdgwigsdiyhzsiduasjkdgasidf 
		add(first,end);add(end,first);
	}
	p[1]=1;dep[1]=0;
	dfs1(1,0,0);
    dfs2(1,0);
    printf("%.15lf",ans);
}
```

全剧终，乘号已经更正

---

## 作者：Dzhao (赞：0)

绿豆蛙的归宿弱化版。

题意：从 $1$ 号节点开始走，问期望往下走多少步后，会无法继续走。

我们令 $F[u]$ 表示从 $u$ 号节点开始往下走的期望步数是多少，那么我们可以很显然的通过期望的定义得到下面的状态转移方程：

$$F[u]=\dfrac{\sum_{v\in son}F[v]+1}{|son|}$$

然后就可以开始写代码啦！

$\mathcal{View\ Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
template <typename T> inline void rd(T &x)
{
	x=0;bool f=0;char c=getchar();
	while(!isdigit(c)) {if(c=='-') f=1;c=getchar();}
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f) x=-x;
}
const int N=1e5+5,M=2e5+5;
int ver[M],nxt[M],h[N],tot,n;
double dp[N];
inline void add(int x,int y) {ver[++tot]=y,nxt[tot]=h[x],h[x]=tot;}
void dfs(int u,int fa)
{
	int cnt=0;
	for(int i=h[u];i;i=nxt[i])
	{
		int v=ver[i];
		if(v==fa) continue;
		dfs(v,u);cnt++;
	}
	for(int i=h[u];i;i=nxt[i])
		if(ver[i]!=fa) dp[u]+=dp[ver[i]]+1;
	if(cnt) dp[u]/=cnt;
}

int main()
{
	rd(n);
	for(int i=1,x,y;i<n;i++)
	{
		rd(x),rd(y);
		add(x,y),add(y,x);
	}
	dfs(1,0);
	printf("%lf\n",dp[1]);
	return 0;
}
```

做完这道题建议去做一下绿豆蛙的归宿，与本题唯一区别就是把树换成了 DAG。

---

## 作者：Graphcity (赞：0)

首先，题目给出的图共有 $n-1$ 条边，且任意两个点互相连通。也就是说，这张图就是一棵树。又因为不能走之前经过的结点（ 也就是父结点 ），它其实还是一棵有根树。

题目也可以转化为：从根结点 1 到叶结点的期望距离。

我们设 $E(x)$  为从第 $x$ 个结点开始，走到叶结点的期望距离。

另外，我们假设结点 $x$ 的儿子共有 $k$ 个，分别为 $son_1$ , $son_2$ , $\cdots$ , $son_k$ 。

根据期望的计算公式可以得到这个状态转移方程：

$$
E(x)= 1+\sum_{i=1}^{k}E(son_i) \cdot \dfrac{1}{k}
\ \ \ (k>0)
$$

当 $x$ 为叶结点时，$E(x)=0$ 。

整个过程可以用 dfs 来解决。最终的结果就是 $E(1)$ 。

```cpp
#include<bits/stdc++.h>
#define Maxn int(1e5)
using namespace std;

struct Node//链式前向星
{
	int to,nxt;
} Edge[(Maxn<<1)+5];
int tot,Head[Maxn+5];

inline void Addedge(int x,int y)//加边
{
	Edge[++tot].to=y;
	Edge[tot].nxt=Head[x];
	Head[x]=tot;
}

int n;
double E[Maxn+5];

inline void dfs(int x,int f)//dfs计算期望
{
	int nowsiz=0;//nowsiz:儿子个数
	for(register int i=Head[x];i;i=Edge[i].nxt)
	{
		int y=Edge[i].to;
		if(y==f) continue;
		dfs(y,x);
		E[x]+=E[y];
		++nowsiz;
	}
	if(nowsiz)//对不是叶子的结点计算期望
		E[x]=(E[x]/nowsiz)+1;
}

int main()
{
	scanf("%d",&n);//输入
	for(register int i=1;i<n;++i)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		Addedge(a,b);
		Addedge(b,a);
	}
	dfs(1,0);
	printf("%.10lf",E[1]);
    return 0;
}
```

---

