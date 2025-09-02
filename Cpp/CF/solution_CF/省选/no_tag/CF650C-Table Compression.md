# Table Compression

## 题目描述

Little Petya is now fond of data compression algorithms. He has already studied gz, bz, zip algorithms and many others. Inspired by the new knowledge, Petya is now developing the new compression algorithm which he wants to name dis.

Petya decided to compress tables. He is given a table $ a $ consisting of $ n $ rows and $ m $ columns that is filled with positive integers. He wants to build the table $ a' $ consisting of positive integers such that the relative order of the elements in each row and each column remains the same. That is, if in some row $ i $ of the initial table $ a_{i,j}&lt;a_{i,k} $ , then in the resulting table $ a'_{i,j}&lt;a'_{i,k} $ , and if $ a_{i,j}=a_{i,k} $ then $ a'_{i,j}=a'_{i,k} $ . Similarly, if in some column $ j $ of the initial table $ a_{i,j}&lt;a_{p,j} $ then in compressed table $ a'_{i,j}&lt;a'_{p,j} $ and if $ a_{i,j}=a_{p,j} $ then $ a'_{i,j}=a'_{p,j} $ .

Because large values require more space to store them, the maximum value in $ a' $ should be as small as possible.

Petya is good in theory, however, he needs your help to implement the algorithm.

## 说明/提示

In the first sample test, despite the fact $ a_{1,2}≠a_{21} $ , they are not located in the same row or column so they may become equal after the compression.

## 样例 #1

### 输入

```
2 2
1 2
3 4
```

### 输出

```
1 2
2 3
```

## 样例 #2

### 输入

```
4 3
20 10 30
50 40 30
50 60 70
90 80 70
```

### 输出

```
2 1 3
5 4 3
5 6 7
9 8 7
```

# 题解

## 作者：VainSylphid (赞：2)

降智导致思路错了好几次……

## 题意简述

给定一个 $n\times m$ 个正整数构成的矩阵，把矩阵里的数用正整数重写一遍，满足同一行和同一列的相对大小关系不变，不同行列之间的数没有限制，且矩阵中的最大值尽可能小。

## 思路

观察到这个东西有点像差分约束，那么首先对矩阵中的每个位置建个对应点。

把同一行上的数排个序，那么相同的数在新矩阵里的值也得相同，可以先用并查集把他们的对应点合并起来，这样建边的时候会方便一点。对于同一列同理。

对于同一行上不相等且排序后相邻的两个数，设较小的为 $a$，较大的为 $b$，那么显然需要满足 $b-a\geq 1$。我们发现这个东西和最长路的式子很像，所以连一条从 $a$ 到 $b$ 边权为 $1$ 的边。对于同一列同理。

然后我们发现这是个有向无环图，所以可以用拓扑排序跑最长路。方便起见，可以建一个超级源点，然后向所有点连边。

建边和拓扑排序的复杂度是 $O(nm)$ 的，瓶颈在于排序是 $O(nm \log nm)$ 的，~~用基数排序就可以 $O(nm)$ 了~~。

## 代码

其实不需要 long long，写上去是个人习惯。


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct node{
	ll v,id;
}c[2000005];
bool cmp(node A,node B)
{
	return A.v < B.v;
}
ll n,m,t[2000005],h[2000005],tot,du[2000005],dis[2000005];
ll idx(ll x,ll y)
{
	return (x - 1) * m + y;
}
struct edge{
	ll v,nxt;
}e[4000005];
void addedge(ll u,ll v)
{
	e[++tot] = {v,h[u]},h[u] = tot,du[v]++;
}
ll fa[1000005],sz[1000005];
ll find(ll x)
{
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}
void merge(ll x,ll y)
{
	ll fx = find(x),fy = find(y);
	if(fx == fy)
	    return;
	if(sz[fx] > sz[fy])
	    swap(fx,fy);
	sz[fy] += sz[fx],sz[fx] = 0,fa[fx] = fy;
}
queue<ll> q;
int main()
{
	scanf("%lld%lld",&n,&m);
	for(ll i = 1;i <= n;i++)
	    for(ll j = 1;j <= m;j++)
	        scanf("%lld",&t[idx(i,j)]);
	for(ll i = 1;i <= n * m;i++)
	    fa[i] = i,sz[i] = 1;
	for(ll i = 1;i <= n;i++)
	{
	    for(ll j = 1;j <= m;j++)
	        c[j] = {t[idx(i,j)],j};
	    sort(c + 1,c + 1 + m,cmp);
	    for(ll j = 2;j <= m;j++)
	        if(c[j].v == c[j - 1].v)
	            merge(idx(i,c[j - 1].id),idx(i,c[j].id));
	}
	for(ll j = 1;j <= m;j++)
	{
	    for(ll i = 1;i <= n;i++)
	        c[i] = {t[idx(i,j)],i};
	    sort(c + 1,c + 1 + n,cmp);
	    for(ll i = 2;i <= n;i++)
	        if(c[i].v == c[i - 1].v)
	            merge(idx(c[i - 1].id,j),idx(c[i].id,j));
    }
	for(ll i = 1;i <= n;i++)
	{
	    for(ll j = 1;j <= m;j++)
	        c[j] = {t[idx(i,j)],j};
	    sort(c + 1,c + 1 + m,cmp);
	    for(ll j = 2;j <= m;j++)
	        if(c[j].v != c[j - 1].v)
	            addedge(find(idx(i,c[j - 1].id)),find(idx(i,c[j].id)));
	}
	for(ll j = 1;j <= m;j++)
	{
	    for(ll i = 1;i <= n;i++)
	        c[i] = {t[idx(i,j)],i};
	    sort(c + 1,c + 1 + n,cmp);
	    for(ll i = 2;i <= n;i++)
	        if(c[i].v != c[i - 1].v)
	            addedge(find(idx(c[i - 1].id,j)),find(idx(c[i].id,j)));
	}
	for(ll i = 1;i <= n;i++)
	    for(ll j = 1;j <= m;j++)
	    addedge(0,find(idx(i,j)));
	q.push(0);
	while(q.size())
	{
		ll tmp = q.front();
		q.pop();
		for(ll i = h[tmp];i;i = e[i].nxt)
		{
			du[e[i].v]--,dis[e[i].v] = max(dis[e[i].v],dis[tmp] + 1);
			if(!du[e[i].v])
			    q.push(e[i].v);
		}
	}
	for(ll i = 1;i <= n;i++)
	    for(ll j = 1;j <= m;j++)
	        printf("%lld%c",dis[find(idx(i,j))]," \n"[j == m]);
	return 0;
}
```

---

## 作者：EastPorridge (赞：2)

最近有点点背过头了，必须得涨涨人品了，害怕去春测的路上被雷劈死。

题解区全是并查集缩点之后跑拓扑最长路，很长，不优雅，给一种优雅的。

我们如果将当前所有的点从小到大排序，按照这个顺序填数，填进去肯定是单调不减的，起码填后现在这个数绝对不会比上个数小。

再考虑那个大小约束，我们维护一个横向的和纵向的最大值所处位置，如果我们的 $a > a_{\max}$，压缩后的答案至少要比最大的那个还要大 $1$；等于的情况除外，此时我们合并并查集就可以了，此时我们得到的答案一定是此时横向和纵向最大值的位置，更新一下。

### Code.

```cpp
#include<bits/stdc++.h>
#define id(x,y) ((x-1)*m+y)
int read()
{
	int x=0; bool f=0; char ch=getchar();
	while(ch < '0' || ch > '9') f|=(ch == '-'),ch=getchar();
	while(ch >= '0' && ch <= '9') x=x*10+(ch^48),ch=getchar();
	return f ? -x : x;
}
using namespace std;
const int N=1e6+10;
int a[N],n,m,f[N],ans[N],px[N],py[N];
int find(int x) {if(f[x] != x) f[x]=find(f[x]); return f[x];}
struct node
{
	int x,y,pos;
	bool operator < (const node &o) const {
		return a[pos] < a[o.pos];
	}
} pl[N];
int main()
{
	n=read(); m=read(); for(int i=1;i<=n*m;i++) f[i]=i;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) {int p=id(i,j); pl[p]=node{i,j,p}; a[p]=read();}
	stable_sort(pl+1,pl+1+n*m);
	for(int i=1;i<=n*m;i++)
	{
		int fx=find(px[pl[i].x]),fy=find(py[pl[i].y]),p=find(pl[i].pos);
		if(a[p] == a[fx]) f[fx]=p; if(a[p] == a[fy]) f[fy]=p; px[pl[i].x]=py[pl[i].y]=p;
		ans[p]=max(ans[fx]+(a[p] != a[fx]),ans[fy]+(a[p] != a[fy]));
	}
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) printf("%d%c",ans[find(id(i,j))]," \n"[j == m]);
	return 0;
}
```

---

## 作者：奇米 (赞：2)

# 题解 - $\mathrm{CF650C}$

## 题目意思

* [题目传送门](https://www.luogu.com.cn/problem/CF650C)

## $\mathrm{Sol}$

* **并查集+拓扑**

* 首先我们考虑关系图很能想到拓扑排序对吧！然后我们可以把一行中权值相同的点合成一个联通块。

* 于是就重新建图（及不同联通块之间连边）

* 还有我们不好找起点于是就随意定个虚点以其为起点跑有向图上的最长路即可。

* 时间复杂度：$O(n\times m \log (n\times m))$

## $\mathrm{Code}$

```cpp
#include <bits/stdc++.h>
#define For(i,a,b) for ( int i=(a);i<=(b);i++ )
#define Dow(i,b,a) for ( int i=(b);i>=(a);i-- )
#define GO(i,x) for ( int i=head[x];i;i=e[i].nex )
#define mem(x,s) memset(x,s,sizeof(x))
#define cpy(x,s) memcpy(x,s,sizeof(x))
#define YES return puts("YES"),0
#define NO return puts("NO"),0
#define GG return puts("-1"),0
#define pb push_back
#define lowbit(x) x&(-x)
using namespace std;

inline int read()
{
	int sum=0,ff=1; char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-') ff=-1;
		ch=getchar();
	}
	while(isdigit(ch))
		sum=sum*10+(ch^48),ch=getchar();
	return sum*ff;
}

const int mod=1e9+7;
const int mo=998244353;
const int N=1e6+5;

int n,m,fa[N],in[N],d[N],id;

inline int ID(int x,int y) {return (x-1)*m+y;}
inline int min(int x,int y) {if(x<y) return x; return y;}
inline int max(int x,int y) {if(x>y) return x; return y;}

inline int find(int x)
{
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}

struct Node
{
	int x,id;
	inline bool friend operator < (const Node&a,const Node&b)
	{
		return a.x<b.x;
	}
};
vector<Node> a[N],b[N];
vector<int> G[N];

int main()
{
	n=read();
	m=read();
	For(i,1,n) For(j,1,m) 
	{
		int x=read();
		++id;fa[id]=id;
		a[i].pb((Node){x,ID(i,j)});
		b[j].pb((Node){x,ID(i,j)});
	}
	For(i,1,n) 
	{
		sort(a[i].begin(),a[i].end());
		For(j,0,m-2) 
		{
			Node A=a[i][j],B=a[i][j+1];
			if(A.x==B.x) fa[find(A.id)]=find(B.id);
		}
	}
	For(i,1,m) 
	{
		sort(b[i].begin(),b[i].end());
		For(j,0,n-2)
		{
			Node A=b[i][j],B=b[i][j+1];
			if(A.x==B.x) fa[find(A.id)]=find(B.id);
		}
	}
	For(i,1,n*m) if(find(i)==i) G[0].pb(i),in[i]++;
	For(i,1,n) For(j,0,m-2)
	{
		Node A=a[i][j],B=a[i][j+1];
		int x=find(A.id),y=find(B.id);
		if(x!=y) G[x].pb(y),in[y]++;
	}
	For(i,1,m) For(j,0,n-2)
	{
		Node A=b[i][j],B=b[i][j+1];
		int x=find(A.id),y=find(B.id);
		if(x!=y) G[x].pb(y),in[y]++;
	}
	queue<int> q;
	q.push(0);
	while(q.size())
	{
		int u=q.front();q.pop();
		For(i,0,(int)G[u].size()-1) 
		{
			int v=G[u][i];
			d[v]=max(d[u]+1,d[v]);
			if(!(--in[v])) q.push(v);
		}
	}
	For(i,1,n) 
	{
		For(j,1,m) printf("%d ",d[find(ID(i,j))]);
		puts("");
	}
	return 0;
}
```


---

## 作者：panyf (赞：0)

首先，将所有**同一行或同一列**并且值相等的点用并查集缩点。

之后，将每行每列的点排序，将排序后相邻的点连边。

注意此时图不一定连通，因此再建一个超级源点像所有点连边。

最后用拓扑排序求每个点到源点的最长路，即为答案。

总时间复杂度 $O(nm\log nm)$ 。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
vector<int>e[N];
vector<pair<int,int> >a[N],b[N];
int d[N],g[N],q[N],f[N];
int getf(int x){return f[x]==x?x:f[x]=getf(f[x]);}
int main(){
	int id=0,i,j,k,l,n,m,h=0,t=1;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;++i){
		for(j=1;j<=m;++j){
			scanf("%d",&k),++id,f[id]=id;
			a[i].push_back({k,id}),b[j].push_back({k,id});
		}
	}
	for(i=1;i<=n;++i){
		sort(a[i].begin(),a[i].end());
		for(j=a[i].size(),k=1;k<j;++k){
			if(a[i][k].first==a[i][k-1].first)f[getf(a[i][k].second)]=getf(a[i][k-1].second);
		}
	}
	for(i=1;i<=m;++i){
		sort(b[i].begin(),b[i].end());
		for(j=b[i].size(),k=1;k<j;++k){
			if(b[i][k].first==b[i][k-1].first)f[getf(b[i][k].second)]=getf(b[i][k-1].second);
		}
	}//排序，并查集缩点
	for(i=1;i<=id;++i)if(f[i]==i)e[0].push_back(i),g[i]=1;//源点连边
	for(i=1;i<=n;++i){
		for(j=a[i].size(),k=1;k<j;++k){
			if(a[i][k].first!=a[i][k-1].first)l=getf(a[i][k].second),e[getf(a[i][k-1].second)].push_back(l),++g[l];
		}
	}
	for(i=1;i<=m;++i){
		for(j=b[i].size(),k=1;k<j;++k){
			if(b[i][k].first!=b[i][k-1].first)l=getf(b[i][k].second),e[getf(b[i][k-1].second)].push_back(l),++g[l];
		}
	}//相邻点连边
	q[1]=0;
	while(h<t){
		i=q[++h];
		for(auto j:e[i]){
			--g[j];
			if(!g[j])q[++t]=j,d[j]=d[i]+1;
		}
	}//拓扑排序
	for(i=1,id=0;i<=n;++i){
		for(j=0;j<m;++j)printf("%d ",d[getf(++id)]); 
		puts("");
	}
	return 0;
}
```


---

