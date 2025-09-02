# Scheme

## 题目描述

求让该图变成强联通图至少增加多少边，并构造方案。

## 说明/提示

$2 \leq n \leq 10^5$

## 样例 #1

### 输入

```
3
3 3 2
```

### 输出

```
1
3 1
```

## 样例 #2

### 输入

```
7
2 3 1 3 4 4 1
```

### 输出

```
3
2 5
2 6
3 7
```

# 题解

## 作者：封禁用户 (赞：9)

这道题目没有人发题解？！

我来发一波$\rm QwQ$

这题很容易让人联想到缩点，因为题意的原因一定会存在回路，可是试想，缩点之后，可能有很多很多环，然后怎样去处理这么多入度出度都为$0$的缩点？而且这些缩点是要按照顺序去连接的，否则肯定无法强连通，不仅是这些环，还有不是环的缩点，缩完点之后的处理反而变的很是复杂。

所以这题的思路得换！因为这一题一题的原因，我们可以直接$dfs$去搜索入度为$0$的点最终的尾巴，还有就是环自身就相当于一个入度为$0$的点，也得$dfs$，搜索完了之后我们可以得到很多链式的起点和终点，然后我们要做的就是把这些链按照顺序首尾相连就$ok$！

$\rm My$ $\rm Code$
```cpp
#include <bits/stdc++.h>
int nxt[100010],rd[100010];
int vis[100010];
using namespace std;
vector<int>head,tail;
int dfs(int x)
{
	vis[x]=1;
	if (!vis[nxt[x]]) return vis[x]=dfs(nxt[x]);
	else return vis[x]=x;
}
int main()
{
	memset(vis,0,sizeof(vis));
	int n;
	scanf("%d",&n);
	for (int i=1; i<=n; i++)
	{
		scanf("%d",&nxt[i]);
		rd[nxt[i]]++;
	}
	int k=0;
	for (int i=1; i<=n; i++)
		if (!rd[i])
		{
			k++;
			head.push_back(i);
			tail.push_back(dfs(i));
		}
	int kk=k;
	for (int i=1; i<=n; i++)
		if (!vis[i])
		{
			k++;
			head.push_back(i);
			tail.push_back(dfs(i));
		}
	if (k==1&&!kk) k=0;
	printf("%d\n",k);
	for (int i=0; i<k; i++) printf("%d %d\n",tail[i],head[(i+1)%k]);
	return 0;
}
```

---

## 作者：Rainybunny (赞：5)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[$luogu$](https://www.luogu.org/problem/CF22E).
# 题解
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;( 这道题本有$dfs$的简单解法, 可以参考其他巨佬的$blog$. )  

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;关于强连通图, 自然的想到$Tarjan$缩点. 观察题目, 我们可以发现输入图的特殊性质: $(\forall u)\text{outd}(u)=1$. 即每个点的出度都为$1$. 考虑缩点之后, 一个由环压缩成的点是没有出度的! 如图:  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![graph1.png](https://i.loli.net/2019/10/28/gjJfMSQdWbLnoiz.png)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;缩点后:  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![graph2.png](https://i.loli.net/2019/10/28/dlaUtJzcW9fI37R.png)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;考虑缩点建图时反向建边, 就能得到一片有向森林, 从无入度的点 ( 也即是原来没有出度的环 ) 出发, 可以遍历一棵树. 接着思考如何构造新的边:  

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$Firstly$, 对于整个图来说, 首先应该连成一个大环. 所以将这些树任意排列, 取第$i$棵树的一片叶子连向第$i+1$棵树的根, 特别地, 第$n$棵树的一片叶子连向第$1$棵树的根.  

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$Secondly$, 将每棵树中没有连向根节点的叶子顺次相连即可. 如图 ( 标记$A$为第一步的连边, 标记$B$为第二步的连边, 其余为缩点后反向图的连边 ):  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![graph3.png](https://i.loli.net/2019/10/28/xo7mvrZD1iWJF83.png)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;实现时, 可以采取类似链式前向星的操作, 发现两个叶子时, 将目标叶子连向新的叶子, 再将新的叶子记为目标叶子, 最后将目标叶子连向下一树的根即可. 注意在输出时边要再次反向.
# 代码
```cpp
#include <stack>
#include <cstdio>
#include <vector>
#include <utility>

#define Int register int

using namespace std;

const int MAXN = 1e5;
int n, Cnte, CprC, Head[MAXN + 5] = {}, CprH[MAXN + 5] = {};
int Indx, Cnts, DFN[MAXN + 5] = {}, Low[MAXN + 5] = {}, SCC[MAXN + 5] = {}, Repres[MAXN + 5] = {};
int Cntt, ind[MAXN + 5] = {}, outd[MAXN + 5] = {}, hd[MAXN + 5] = {}, tl[MAXN + 5] = {}, Vis[MAXN + 5] = {};
bool Instk[MAXN + 5] = {};
vector<pair<int, int> > Ans;
stack<int> S;

struct Edge { int To, _nxt; } Graph[MAXN + 5] = {}, CprG[MAXN + 5] = {};

inline int Min ( const int a, const int b ) { return a < b ? a : b; }

inline void Link ( const int From, const int To ) {
	Graph[++ Cnte] = { To, Head[From] };
	Head[From] = Cnte;
}

inline void CprLink ( const int From, const int To ) {
	CprG[++ CprC] = { To, CprH[From] };
	CprH[From] = CprC;
}

inline void Tarjan ( const int u ) {
	int v;
	DFN[u] = Low[u] = ++ Indx, Instk[u] = true, S.push ( u );
	for ( Int i = Head[u]; i; i = Graph[i]._nxt ) {
		if ( ! DFN[v = Graph[i].To] ) {
			Tarjan ( v ), Low[u] = Min ( Low[u], Low[v] );
		} else if ( Instk[v] ) {
			Low[u] = Min ( Low[u], DFN[v] );
		}
	}
	if ( DFN[u] == Low[u] ) {
		Repres[++ Cnts] = u;
		do {
			v = S.top (); S.pop (), Instk[v] = false;
			SCC[v] = Cnts;
		} while ( v ^ u );
	}
}

inline void MakeGraph () {
	for ( Int i = 1; i <= n; ++ i ) {
		int u = SCC[i], v;
		for ( Int j = Head[i]; j; j = Graph[j]._nxt ) {
			if ( ( v = SCC[Graph[j].To] ) ^ u ) {
				CprLink ( v, u ), ++ outd[v], ++ ind[u];
			}
		}
	}
}

inline void DFS ( const int Color, const int u ) {
	if ( Vis[u] ) return ;
	Vis[u] = Color; bool Leaf = true;
	for ( Int i = CprH[u], v; i; i = CprG[i]._nxt ) {
		Leaf &= Vis[v = CprG[i].To];
		DFS ( Color, v );
	}
	if ( Leaf ) {
		if ( tl[Color] ) Ans.push_back ( { u, tl[Color] } );
		tl[Color] = u;
	}
}

inline void Work () {
	scanf ( "%d", &n );
	for ( Int i = 1, f; i <= n; ++ i ) scanf ( "%d", &f ), Link ( i, f );
	for ( Int i = 1; i <= n; ++ i ) {
		if ( ! DFN[i] ) {
			Tarjan ( i );
		}
	}
	MakeGraph ();
	if ( Cnts == 1 ) { puts ( "0" ); return ; }
	for ( Int i = 1; i <= Cnts; ++ i ) {
		if ( ! ind[i] ) {
			hd[++ Cntt] = i, DFS ( Cntt, i );
			if ( Cntt > 1 ) Ans.push_back ( { hd[Cntt], tl[Cntt - 1] } );
		}
	}
	Ans.push_back ( { hd[1], tl[Cntt] } );
	printf ( "%u\n", Ans.size () );
	for ( pair<int, int> e: Ans ) printf ( "%d %d\n", Repres[e.first], Repres[e.second] );
}

int main () {
	Work ();
	return 0;
}

/*
12
4 5 6 5 6 4 10 11 12 11 12 10

6
2 3
1 2
8 9
7 8
10 1
4 7
*/
```

---

## 作者：封禁用户 (赞：3)

# CF22E Scheme 题解
[题目传送门](https://www.luogu.com.cn/problem/CF22E)
## 思路。
看到了强连通图，很容易想到了缩点。由于边数是等于点数的，所以我们缩完点得到的一定是一片森林。

接下来需要我们想出一种构造方法。

首先，对于任意一个叶子节点，它肯定需要至少一条边成为它的入边，而对于任意一个根节点，它也至少需要一条边成为它的出边。由于一条边只能带来一个入边与一个出边，且叶子节点数量大于根节点，所以最后的答案即加边的数量肯定是叶子节点的个数。

可我们又该如何去构造它呢。由于每个根节点数相对来说较少，我们可以先将它们与一个叶子节点相匹配，但必须要保证整个图的连通，所以我们可以依次将一个叶子节点连到下一棵树的根节点上，而这棵树的其它叶子节点，接到它上面即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define MAXN 100005
typedef long long LL;
typedef unsigned long long uLL;
const LL INF=0x7f7f7f7f7f7f7f7f;
const int mo=1e9+7;
typedef pair<LL,LL> pii;
template<typename _T>
void read(_T &x){
	_T f=1;x=0;char s=getchar();
	while(s>'9'||s<'0'){if(s=='-')f=-1;s=getchar();}
	while('0'<=s&&s<='9'){x=(x<<3)+(x<<1)+(s^48);s=getchar();}
	x*=f;
}
int dfn[MAXN],low[MAXN],sta[MAXN],stak;
int n,tot,head[MAXN],idx,cnt,fa[MAXN];
int belong[MAXN],pre[MAXN],sum,Fa[MAXN];
int din[MAXN],dout[MAXN],ans;
bool insta[MAXN];
queue<int> q;
vector<int> G[MAXN],vec;
struct edge{int to,nxt;}e[MAXN<<1];
void addEdge(int u,int v){e[++tot]=(edge){v,head[u]};head[u]=tot;}
int findSet(int x){return Fa[x]==x?x:Fa[x]=findSet(Fa[x]);}
void unionSet(int a,int b){
	int u=findSet(a),v=findSet(b);
	if(u==v)return ;Fa[u]=v;
}
void tarjan(int u){
	dfn[u]=low[u]=++idx;sta[++stak]=u;insta[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!dfn[v])tarjan(v),low[u]=min(low[u],low[v]);
		else if(insta[v])low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]){
		cnt++;int v;pre[cnt]=u;
		do{
			v=sta[stak--];
			belong[v]=cnt;insta[v]=0;
		}while(u!=v);
	}
}
signed main(){
	read(n);
	for(int i=1;i<=n;i++)read(fa[i]),addEdge(i,fa[i]);
	for(int i=1;i<=n;i++)if(!dfn[i])tarjan(i);
	//for(int i=1;i<=n;i++)printf("%d:%d %d\n",i,belong[i],fa[i]);
	for(int i=1;i<=cnt;i++)Fa[i]=i;
	for(int i=1;i<=n;i++)
		if(belong[fa[i]]!=belong[i]){
			//printf("%d %d %d %d\n",i,fa[i],belong[i],belong[fa[i]]);
			din[belong[fa[i]]]++,dout[belong[i]]++,
			unionSet(belong[i],belong[fa[i]]);
		}
	if(cnt==1){puts("0");return 0;}
	for(int i=1;i<=cnt;i++)if(!din[i])G[findSet(i)].push_back(i);
	for(int i=1;i<=cnt;i++)if(!dout[i])sum++,ans+=G[i].size(),vec.push_back(i);
	printf("%d\n",ans);
	for(int i=1;i<=vec.size();i++){
		int siz=G[vec[i-1]].size();
		for(int j=1;j<siz;j++)
			printf("%d %d\n",pre[G[vec[i-1]][j-1]],pre[G[vec[i-1]][j]]);
		if(i<vec.size())printf("%d %d\n",pre[vec[i-1]],pre[G[vec[i]][0]]);
		else printf("%d %d\n",pre[vec[i-1]],pre[G[vec[0]][0]]);
	}
	return 0;
}
```
本人小中考前最后一篇题解，也祝各位无论在经历什么，都能获得自己满意的结果。

---

## 作者：Binary_Lee (赞：3)

## [题面传送门](https://www.luogu.com.cn/problem/CF22E)

### upd on 2023.11.03

修正一些错误，感谢 @XHY20180718 的提出

### 解决思路

这里提供一种不受到边数限制的做法，比较无脑。

先考虑对于 DAG 最少添加多少边可以强联通。设入度为 $0$ 的点的数量为 $cnt_{in}$，出度为 $0$ 的点的数量为 $cnt_{out}$，结论是：添加边数为 $\max(cnt_{in},cnt_{out})$。

如何得到？可以参考下面的连边方式：

![](https://cdn.luogu.com.cn/upload/image_hosting/baxklee6.png)

对于每一个连通块，没有入度的点间相邻连边，没有出度的点间相邻连边。不同连通块之间，相邻的没有出度的连到没有入度的（就算是只有一个连通块也要自己和自己连，保证强连通）。

所以我们需要做的：

1. 将原图转化为 DAG，可以使用 Tarjan 缩点，这里不细讲。

2. 把 DAG 分成一个个连通块，找出各连通块中没有入度的点、没有出度的点。

3. 按照上述方法连边。

具体细节可以看代码。

### AC Code

```cpp
//If, one day, I finally manage to make my dreams a reality...
//I wonder, will you still be there by my side?
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false)
#define TIE cin.tie(0),cout.tie(0)
#define int long long
#define y1 cyy
#define fi first
#define se second
#define cnt1(x) __builtin_popcount(x)
#define mk make_pair
#define pb push_back
#define pii pair<int,int>
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define lbt(x) (x&(-x))
using namespace std;
int n,v,dfn[200005],low[200005],col[200005],id[200005],stk[200005];
int timer,tot,cnt,top,in[200005],out[200005],head[200005],Tot;
int U[200005],V[200005];
bool vis[200005],mark[200005];
vector<int> a[200005];
vector<pii> ans;
struct ltk{
	vector<int> nin,nout;  //连通块中没有入度、没有出度的点集
}l[200005];
struct node{
	int to,nxt;
}e[200005];
void add(int u,int v){
	e[++tot]={v,head[u]},head[u]=tot;
	U[tot]=u,V[tot]=v;  //要重新建图，所以记边
}
void tarjan(int x){
	dfn[x]=low[x]=++timer,stk[++top]=x,vis[x]=1;
	for(int i=head[x];i;i=e[i].nxt){
		int tmp=e[i].to;
		if(!dfn[tmp]){
			tarjan(tmp);
			low[x]=min(low[x],low[tmp]);
		}
		else if(vis[tmp]) low[x]=min(low[x],dfn[tmp]);
	}
	if(dfn[x]==low[x]){
		cnt++,id[cnt]=x;   //id[i]表示强连通分量 i 的代表点
		do{
			col[stk[top]]=cnt,vis[stk[top--]]=0;
		}while(stk[top+1]!=x);
	}
}
void dfs(int x,int c){
	if(!in[x]) l[c].nin.pb(id[x]);   //加入没有入度点
	if(!out[x]) l[c].nout.pb(id[x]);   //加入没有出度点
	for(int i=0;i<a[x].size();i++){
		int tmp=a[x][i];
		if(!mark[tmp]) mark[tmp]=1,dfs(tmp,c);
	}
}
signed main(){
	IOS;TIE;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>v,add(i,v);
	for(int i=1;i<=n;i++){
		if(!dfn[i]) top=0,tarjan(i);
	}
	if(cnt==1){   //注意特判：如果原图已经是一个强连通分量，不用加边
		cout<<0<<endl;
		return 0;
	}
	for(int i=1;i<=tot;i++){
		int x=col[U[i]],y=col[V[i]];
		if(x^y) a[x].pb(y),a[y].pb(x),in[y]++,out[x]++;   //重新建图
	}
	for(int i=1;i<=cnt;i++){
		if(!mark[i]) mark[i]=1,dfs(i,++Tot);   //找连通块
	}
	for(int i=1;i<=Tot;i++){
		for(int j=1;j<l[i].nin.size();j++) ans.pb(mk(l[i].nin[j-1],l[i].nin[j]));   //同连通块没有入度点相邻连接
		for(int j=1;j<l[i].nout.size();j++) ans.pb(mk(l[i].nout[j-1],l[i].nout[j]));   //同连通块没有出度点相邻连接
	}
	for(int i=2;i<=Tot;i++) ans.pb(mk(l[i-1].nout.back(),l[i].nin[0]));
	ans.pb(mk(l[Tot].nout.back(),l[1].nin[0]));   //相邻连通块连接
	cout<<ans.size()<<endl;
	for(auto i:ans) cout<<i.fi<<' '<<i.se<<endl;
	return 0;
}
```

---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 2300}$
---
### 解题思路：

首先先感性认知一下按照题目描述生成的图大概是什么样的。每一个点都有且只有一条出边，不一定有入边。那么也就是一个基环内向树。即：一个环上生出一些链，这些链上的边指向环。

一个基环内向树缩点之后就变成了一个“头”和若干条“尾巴”，尾巴指向头。可能有很多这样的树。

将一个“尾巴”和头并到一起可以直接从“头”上的任意一个点连一条边到“尾巴”的末端。如果有很多这样的子图，可以类似地将另一个子图的“头”上的一个点连一条边到当前的子图的“尾巴”上，如果当前的子图的“头”能够再连一条边到那一个的“尾巴”上，也就能够构成一个强联通了。

那么不妨将留下一个“尾巴”用来构成强联通，其他剩下的“尾巴”都直接和本图的头相连。每一个子图的“头”都向下一个子图留下的那一条“尾巴”上连边。

特殊地，当一个图只有一个“头”的时候，如果还有别的子图，可以任意再找一个点作为“尾巴”从而将这个子图并入整个大图。

---
实际操作的时候，并没有必要真的写一个缩点出来，任意找一个未被访问过的点进行访问，直到访问到一个之前已经经过的点为止，这个重复被访问的点就可以代表“头”，标记下来。复杂度 $O(n)$。

然后把入度为 $0$ 的点并到打上的标记上，也就是之前标记的代表“头”点，把当前这个点作为“尾巴”的代表。

按照上面说的模拟就行了。

---
### 代码：

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=200005;
int n,head[MAXN],nxt[MAXN],num[MAXN],tot,d[MAXN],vis[MAXN],h[MAXN],cnt,x;
vector <int> v[MAXN],l;
void add(int x,int y){
	nxt[++tot]=head[x];
	head[x]=tot;
	num[tot]=y;
	d[y]++;
}
int dfs(int now){
	if(h[now])return h[now];
	if(vis[now]){
		h[now]=now;
		l.push_back(now);
		return now;
	}
	vis[now]=1;
	for(int i=head[now];i;i=nxt[i]){
		h[now]=dfs(num[i]);
		if(h[now])return h[now];
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		add(i,x);
	}
	for(int i=1;i<=n;i++)if(vis[i]==0)dfs(i);
	for(int i=1;i<=n;i++)
	if(d[i]==0)v[h[i]].push_back(i),cnt++;
	if(l.size()==1){
		if(cnt==0){
			printf("0\n");
			return 0;
		}
		printf("%d\n",v[l[0]].size());
		for(int i=0;i<v[l[0]].size();i++)
		printf("%d %d\n",l[0],v[l[0]][i]);
		return 0;
	}
	for(int i=0;i<l.size();i++){
		if(v[l[i]].empty()){
			v[l[i]].push_back(l[i]);
			cnt++;
		}
	}//处理环 
	printf("%d\n",cnt);
	for(int i=0;i<l.size();i++)
	for(int j=1;j<v[l[i]].size();j++)
	printf("%d %d\n",l[i],v[l[i]][j]);
	for(int i=0;i<l.size()-1;i++)
	printf("%d %d\n",l[i],v[l[i+1]][0]);
	printf("%d %d\n",l[l.size()-1],v[l[0]][0]);
	return 0;
}
```


---

## 作者：RyexAwl (赞：1)

题意可以转化为：给定基环内向树森林，加最少的边使得图强连通。

考虑一棵基环内向树的环，一定不存在一条有向边 $u\to v$ ，其中 $u$ 属于环， $v$ 不属于环。

那么我们将一棵基环内向树缩点后，一定是以环所在的强连通分量为根节点的内向树。

对于一棵内向树来说，任意一个节点都可以到达根节点，那么我们只需要将根节点与所有叶子连接即可。

对于由 $k$ 棵内向树构成的内向树森林，我们可以加 $k-1$ 条边合并成一棵内向树。

并且我们可以每次将其 “挂到” 叶子节点上，使得每次合并能够使得叶子节点个数 - 1 。

合并后根节点往叶子节点连边即可。

那么答案即内向树森林的叶子节点个数和。

时间复杂度 $O(n)$ 。

```cpp
#include <bits/stdc++.h>

#define rep(i,l,r) for (int i = l; i <= r; i++)
#define per(i,r,l) for (int i = r; i >= l; i--)
#define fi first
#define se second
#define prt std::cout
#define gin std::cin
#define edl std::endl

namespace wxy{

typedef std::pair<int,int> PII;

const int N = 5e5 + 50;

int n,f[N];

int dfn[N],low[N],times;

int top,stk[N],idx[N],scc;

std::vector<int> pos[N],rpos[N],loc;

bool vis[N],rt[N];

std::vector<PII> outs;

struct Graph{
	int head[N],edge[N],fail[N],deg[N],tot;
	inline void clear(){
		memset(head,0,sizeof head);
		memset(deg,0,sizeof deg);
		tot = 0;
	}
	inline void add(int x,int y) {
		edge[++tot] = y;
		fail[tot] = head[x];
		head[x] = tot; deg[y]++;
	}
}G1,G2;

void tarjan(int x) {
	vis[x] = true; stk[++top] = x; dfn[x] = low[x] = ++times;
	for (int i = G1.head[x]; i; i = G1.fail[i]) {
		int v = G1.edge[i];
		if (!dfn[v]) {
			tarjan(v); low[x] = std::min(low[x],low[v]);
		} else if (vis[v]) low[x] = std::min(low[x],dfn[v]);
	}
	if (low[x] == dfn[x]) {
		int y = -1; ++scc;
		do {
			y = stk[top--]; vis[y] = false;
			pos[scc].push_back(y); idx[y] = scc;
		} while (x != y);
	}
}

void dfs(int x,int fa,int root) {
	if (G2.deg[x] == 1 && x != root) rpos[root].push_back(x);
	for (int i = G2.head[x]; i; i = G2.fail[i]) {
		int v = G2.edge[i];
		if (v == fa) continue;
		dfs(v,x,root);
	}
}

inline void main(){
    #ifndef ONLINE_JUDGE
        freopen("in.in","r",stdin);
        freopen("out.out","w",stdout);
    #endif
    gin >> n; G1.clear(); G2.clear();
	rep(i,1,n) {
		int x; gin >> x; f[i] = x;
		G1.add(i,f[i]);
	}
	rep(i,1,n)
		if (!dfn[i]) tarjan(i);
	for (int i = 1; i <= scc; i++)
		if (pos[i].size() > 1) {
			rt[pos[i][0]] = true;
			loc.push_back(pos[i][0]);
		}
	rep(i,1,n) {
		if (idx[i] != idx[f[i]]){
			G2.add(pos[idx[i]][0],pos[idx[f[i]]][0]);
			G2.add(pos[idx[f[i]]][0],pos[idx[i]][0]);
		}
	} 
	for (int i = 0; i < loc.size(); i++) dfs(loc[i],-1,loc[i]);
	int pp = -1;
	for (int i = 0; i < loc.size(); i++)
		if (rpos[loc[i]].size() > 0) pp = i;
	if (pp == -1) {
		if (loc.size() == 1) {
			prt << 0;
			return;
		}
		prt << loc.size() << edl; 
		loc.push_back(loc[0]);
		for (int i = 0; i < loc.size() - 1; i++)
			prt << loc[i] << " " << loc[i + 1] << edl;
		return;
	} 
	if (pp != 0) std::swap(loc[0],loc[pp]);
	for (int i = 1; i < loc.size(); i++) {
		int ve = rpos[loc[0]][rpos[loc[0]].size() - 1]; rpos[loc[0]].pop_back();
		outs.push_back(std::make_pair(loc[i],ve));
		if (rpos[loc[i]].size() == 0) {
			rpos[loc[0]].push_back(loc[i]);
		} else {
			for (int k = 0; k < rpos[loc[i]].size(); k++) 
				rpos[loc[0]].push_back(rpos[loc[i]][k]);
		}
	}
	for (int i = 0; i < rpos[loc[0]].size(); i++) {
		int v = rpos[loc[0]][i];
		outs.push_back(std::make_pair(loc[0],v));
	}
	prt << outs.size() << edl;
	for (int i = 0; i < outs.size(); i++)
		prt << outs[i].fi << " " << outs[i].se << edl;
}

}signed main(){wxy::main(); return 0;}
```


---

## 作者：_XHY20180718_ (赞：0)

给出一种不考虑边数限制的做法。

## 题意简述：

给定一张图，求让该图变成强联通图至少增加多少边并输出边。

## 思路：

一开始想：这不就是[校园网络](https://www.luogu.com.cn/problem/P2812)吗？直接出度为 $0$ 的连接入度为 $0$ 的不就行了？

然后发现：这题图不保证连通？那怎么办？~~多加几条边~~？肯定会使得答案更劣的。

我们考虑一下本来的做法，其实就是让入度为 $0$ 和出度为 $0$ 的节点全部消失，那我们将整个图合在一起不就行了？

## 具体做法：

先将每个弱连通的 DAG 之间分开，可以使用并查集判弱连通，然后再依次讨论。

对于每个 DAG，先让入度为 $0$ 的点依次连起来，这样这个 DAG 就只有一个入度为 $0$ 的点了，且代价不变。

而一个 DAG 中所有出度为 $0$ 的点全部连在下一个 DAG 中第一个出度为 $0$ 的点，代价同样不会变化。

这样子就可以让所有入度为 $0$ 和出度为 $0$ 的点全部抵消。

代价依然是出度为 $0$ 和入度为 $0$ 的点数之间的最大值。

时间复杂度：$\mathcal{O}(n\alpha(m)+m)$

## 代码环节：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m,ansr,ansc;
int fa[N],sz[N],tot[N];
int low[N],dfn[N],Time;
int rd[N],cd[N],st[N],r;
int ltk[N],cnt,id;
int head[N],ei,f[N],idx[N];
bool is[N],vis[N];
struct edge{
    int u,v,nxt;
}egs[N];
vector<int>lk[N];
vector<int>ver[N],vec[N];
vector<pair<int,int> >ans[N];
inline void add(int u,int v){if(u!=v)egs[++ei]={u,v,head[u]};head[u]=ei;}
void tarjan(int u){
    st[++r]=u,is[u]=1;
    low[u]=dfn[u]=++Time;idx[Time]=u;
    for(int i=head[u];i;i=egs[i].nxt){
        const int v=egs[i].v;
        if(!dfn[v])tarjan(v),low[u]=min(low[u],low[v]);
        else if(is[v])low[u]=min(low[u],dfn[v]);
    }
    if(low[u]==dfn[u]){
        int v;f[++cnt]=st[r];
        do{
            v=st[r--],ltk[v]=cnt,is[v]=0;
        }while(u!=v);
    }
}
inline int find(int x){
    while(x!=fa[x])x=fa[x]=fa[fa[x]];
    return x;
}
inline void merge(int x,int y){
    x=find(x),y=find(y);
    if(!(x^y))return;
    if(sz[x]<sz[y])swap(x,y);
    sz[x]+=sz[y],fa[y]=x;
}
signed main(){
    cin>>n;int u,v;
    for(u=1; u<=n; ++u)cin>>v,add(u,v);
    for(u=1; u<=n; ++u)
        if(!dfn[u])tarjan(u);
    for(int i=1; i<=cnt; ++i)fa[i]=i,sz[i]=1;
    for(int i=1; i<=ei; ++i){
        int u=ltk[egs[i].u],v=ltk[egs[i].v];
        if(u!=v)++cd[u],++rd[v],merge(u,v);
    }
    for(int i=1; i<=cnt; ++i){
        int u=find(i);
        if(!tot[u])tot[u]=++id;
        lk[tot[u]].push_back(i);
    }
    for(int i=1; i<=id; ++i)
        for(auto v:lk[i]){
            if(!rd[v])ver[i].push_back(v),++ansr;
            if(!cd[v])vec[i].push_back(v),++ansc;
        }
    if(cnt==1)cout<<"0\n",exit(0);
    cout<<max(ansr,ansc)<<'\n';
    for(int i=1; i<id; ++i){
        for(auto v:vec[i])
            cout<<f[v]<<' '<<f[ver[i+1][0]]<<'\n';
        for(int j=1; j<ver[i].size(); ++j)
            cout<<f[ver[i][j-1]]<<' '<<f[ver[i][j]]<<'\n';
    }for(auto v:vec[id])
        cout<<f[v]<<' '<<f[ver[1][0]]<<'\n';
    for(int j=1; j<ver[id].size(); ++j)
        cout<<f[ver[id][j-1]]<<' '<<f[ver[id][j]]<<'\n';
    return 0;
}
```


---

