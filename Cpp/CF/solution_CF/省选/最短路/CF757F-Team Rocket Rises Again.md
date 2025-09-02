# Team Rocket Rises Again

## 题目描述

It's the turn of the year, so Bash wants to send presents to his friends. There are $ n $ cities in the Himalayan region and they are connected by $ m $ bidirectional roads. Bash is living in city $ s $ . Bash has exactly one friend in each of the other cities. Since Bash wants to surprise his friends, he decides to send a Pikachu to each of them. Since there may be some cities which are not reachable from Bash's city, he only sends a Pikachu to those friends who live in a city reachable from his own city. He also wants to send it to them as soon as possible.

He finds out the minimum time for each of his Pikachus to reach its destination city. Since he is a perfectionist, he informs all his friends with the time their gift will reach them. A Pikachu travels at a speed of $ 1 $ meters per second. His friends were excited to hear this and would be unhappy if their presents got delayed. Unfortunately Team Rocket is on the loose and they came to know of Bash's plan. They want to maximize the number of friends who are unhappy with Bash.

They do this by destroying exactly one of the other $ n-1 $ cities. This implies that the friend residing in that city dies, so he is unhappy as well.

Note that if a city is destroyed, all the roads directly connected to the city are also destroyed and the Pikachu may be forced to take a longer alternate route.

Please also note that only friends that are waiting for a gift count as unhappy, even if they die.

Since Bash is already a legend, can you help Team Rocket this time and find out the maximum number of Bash's friends who can be made unhappy by destroying exactly one city.

## 说明/提示

In the first sample, on destroying the city $ 2 $ , the length of shortest distance between pairs of cities $ (3,2) $ and $ (3,4) $ will change. Hence the answer is $ 2 $ .

## 样例 #1

### 输入

```
4 4 3
1 2 1
2 3 1
2 4 1
3 1 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
7 11 2
1 2 5
1 3 5
2 4 2
2 5 2
3 6 3
3 7 3
4 6 2
3 4 2
6 7 3
4 5 7
4 7 7
```

### 输出

```
4
```

# 题解

## 作者：AThousandSuns (赞：19)

《关于我随机开 CF 然后刷到支配树模板自闭一万年这件事》

那么，如果像我一样，不会支配树~~也不想学~~怎么办呢？

---

提供一个时间复杂度 $O(n+m\log n)$（瓶颈在最短路），空间复杂度 $O(n+m)$，不需要支配树（我相信我没有自己发明），更不需要倍增 LCA 和 LCT 的做法。

（截至 2021.3.21，该做法在 CF 上是最优解。）~~（虽然可能是评测机进化了）~~

首先还是要跑一遍 Dijkstra，建出最短路 DAG。

问题变成删除除了 $s$ 以外的一个点，使得 $s$ 无法到达的点数尽可能多。

注意我们只需要求最大值，所以没有必要把每个点删掉都求一遍。

首先，如果一个点入度为 $1$ 且它的入点不是 $s$，那么删它肯定不如删它的入点优。因为删掉它的入点后，它也无法被到达。也就是说一条“链”可以被缩成一个点。

那么做一遍拓扑排序，每次看所有入边的入点是否被缩成了同一个点。如果是，那么将当前点也缩进去。

缩完之后，每个点要么入度 $\ge 2$，要么入点是 $s$，要么自己就是 $s$。那么无论删掉哪个异于 $s$ 的点，其它点都能从 $s$ 到达。不能到达的只有当前点以及和它缩在一起的点。

对每个缩在一起的点集求大小最大值即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int maxn=666666,mod=998244353;
#define PB push_back
#define MP make_pair
#define lson o<<1,l,mid
#define rson o<<1|1,mid+1,r
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define ROF(i,a,b) for(int i=(a);i>=(b);i--)
#define MEM(x,v) memset(x,v,sizeof(x))
inline int read(){
    int x=0,f=0;char ch=getchar();
    while(ch<'0' || ch>'9') f|=ch=='-',ch=getchar();
    while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
    return f?-x:x;
}
int n,m,s,el,head[maxn],to[maxn],nxt[maxn],w[maxn];
int el2,head2[maxn],to2[maxn],nxt2[maxn],deg[maxn];
int q[maxn],h,r,id[maxn],sz[maxn],ans,tmp[maxn];
ll dis[maxn];
struct node{
	ll d;
	int u;
	bool operator<(const node &nd)const{return d>nd.d;}
};
priority_queue<node> pq; 
inline void add(int u,int v,int ww){
	to[++el]=v;nxt[el]=head[u];head[u]=el;w[el]=ww;
}
inline void add2(int u,int v){
	to2[++el2]=v;nxt2[el2]=head2[u];head2[u]=el2;deg[v]++;
}
int main(){
	n=read();m=read();s=read();
	FOR(i,1,m){
		int u=read(),v=read(),w=read();
		add(u,v,w);add(v,u,w);
	}
	FOR(i,1,n) dis[i]=1e18;
	pq.push((node){dis[s]=0,s});
	while(!pq.empty()){
		int u=pq.top().u;
		ll d=pq.top().d;
		pq.pop();
		if(dis[u]!=d) continue;
		for(int i=head[u];i;i=nxt[i]){
			int v=to[i];
			if(d+w[i]<dis[v]) pq.push((node){dis[v]=d+w[i],v});
		}
	}
	FOR(u,1,n) for(int i=head[u];i;i=nxt[i]){
		int v=to[i];
		if(dis[u]+w[i]==dis[v]) add2(u,v);
	}
	q[h=r=1]=s;
	FOR(i,1,n) tmp[i]=i;
	while(h<=r){
		int u=q[h++];
		if(tmp[u]!=-1 && tmp[u]!=s) id[u]=tmp[u];
		else id[u]=u;
		sz[id[u]]++;
		for(int i=head2[u];i;i=nxt2[i]){
			int v=to2[i];
			if(tmp[v]==v) tmp[v]=id[u];
			else if(tmp[v]!=id[u]) tmp[v]=-1;
			if(!--deg[v]) q[++r]=v;
		}
	}
	FOR(i,1,n) if(i!=s) ans=max(ans,sz[i]);
	printf("%d\n",ans);
}
```

---

## 作者：chenzida (赞：8)

前置知识：

1.最短路

2.支配树

支配树不会可以点[我](https://www.luogu.com.cn/blog/chenzidaCZD-648/zhi-pei-shu)

思路解析：

由于是影响，所以很自然的能想到支配树，如果我们把影响的点找到，那这题就做完了。

我们考虑进行一次 $dijkstra$，将每一个点到 $s$ 的最短路都求出来。

那么直接限制 $v$ 的点有哪些呢？那就是那些点 $u$ 满足 $dis_u+val_{u-v}=dis_v$。对于一个点 $x$，如果所有限制它的点 $y$ 都直接或者间接的使 $dis_y$ 出现了改变，那么 $dis_x$ 一定被改变。

所以我们只需一遍最短路求出单源最短路然后根据刚才的条件初始化出限制情况，然后使用支配树即可。

完整代码：

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int NR=3e5+10;
void Min(int& x,int y){x=min(x,y);}
void Max(int& x,int y){x=max(x,y);}
int n,m,s;
int in[NR];
struct Edge
{
	int to,nxt;
}e1[NR<<2],e2[NR];
int head1[NR],head2[NR];
int tot1=1,tot2=1;
void add1(int x,int y)
{
	e1[tot1].to=y;
	e1[tot1].nxt=head1[x];
	head1[x]=tot1++;
}
void add2(int x,int y)
{
	e2[tot2].to=y;
	e2[tot2].nxt=head2[x];
	head2[x]=tot2++;
}
int to[NR<<1],nxt[NR<<1],val[NR<<1];
int head[NR];
int tot=1;
void add(int x,int y,int z)
{
	to[tot]=y;
	nxt[tot]=head[x];
	val[tot]=z;
	head[x]=tot++;
}
struct Nd
{
	int x,d;
	bool operator <(const Nd& A)const
	{
		return d>A.d;
	}
};
Nd md(int x,int d){Nd tmp;tmp.x=x,tmp.d=d;return tmp;}
bool vis[NR];
int dis[NR];
void dijkstra()
{
	memset(vis,0,sizeof(vis));
	memset(dis,0x3f,sizeof(dis));
	priority_queue<Nd>q;
	q.push(md(s,0)),dis[s]=0;
	while(!q.empty())
	{
		int x=q.top().x;q.pop();
		if(vis[x])continue;vis[x]=1;
		for(int i=head[x];i;i=nxt[i])
		{
			int y=to[i];
			if(dis[y]>dis[x]+val[i])
			{
				dis[y]=dis[x]+val[i];
				q.push(md(y,dis[y]));
			}
		}
	}
}
void build()
{
	for(int x=1;x<=n;x++)
	{
		for(int i=head[x];i;i=nxt[i])
		{
			int y=to[i];
			if(dis[y]==dis[x]+val[i])
				add1(x,y),in[y]++;
		}
	}
}
int lg[NR];
int dep[NR],fa[NR];
int f[NR][20];
int LCA(int x,int y)
{
	if(dep[x]<dep[y])swap(x,y);
	while(dep[x]>dep[y])x=f[x][lg[dep[x]-dep[y]]-1];
	if(x==y)return x;
	for(int i=lg[dep[x]];i>=0;i--)if(f[x][i]!=f[y][i])
		x=f[x][i],y=f[y][i];
	return f[x][0];
}
int siz[NR];
void dfs(int x)
{
	siz[x]=1;
	for(int i=head2[x];i;i=e2[i].nxt)
	{
		int y=e2[i].to;
		dfs(y);siz[x]+=siz[y];
	}
}
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
signed main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	n=read(),m=read(),s=read();
	for(int i=1;i<=m;i++)
	{
		int x=read(),y=read(),z=read();
		add(x,y,z),add(y,x,z);
	}
	for(int i=1;i<=n;i++)lg[i]=lg[i-1]+((1<<lg[i-1])==i);
	dijkstra();build();queue<int>q;memset(fa,-1,sizeof(fa));
	for(int i=1;i<=n;i++)if(!in[i])q.push(i),fa[i]=0;
	while(!q.empty())
	{
		int x=q.front();q.pop();add2(fa[x],x);
		f[x][0]=fa[x],dep[x]=dep[fa[x]]+1;
		for(int i=1;i<=lg[dep[x]];i++)
			f[x][i]=f[f[x][i-1]][i-1];
		for(int i=head1[x];i;i=e1[i].nxt)
		{
			int y=e1[i].to;
			if(fa[y]==-1)fa[y]=x;
			else fa[y]=LCA(fa[y],x);
			if(!(--in[y]))q.push(y);
		}
	}
	dfs(s);int ans=0;
	for(int i=1;i<=n;i++)if(i!=s)
		Max(ans,siz[i]);
	printf("%d\n",ans);
	return 0;
}


---

## 作者：蒟蒻初音ミク (赞：3)

# 广告

[蒟蒻的blog](https://www.luogu.com.cn/blog/111990/)

# 正文

这里介绍一种不需要存储拓扑序的做法。

基本思路：

# 最短路径DAG+支配树+dfs求size

首先，最短路径一定是一个DAG（至少在边权>0的时候成立）

粗略的证明：因为如果存在环，且边权>0，那么一个点就有可能有两个长度不一样的最短路径到达它，而最短路径的长度只有一个，所以不成立。得证。

~~（好像有点不对。。。）~~

然后具体思路：

## 1、先来一个spfa，求出所有点的dis，然后判断每一条边是否在最短路径上。

```cpp
void spfa()
{
	while(!q.empty())q.pop();
	memset(dis,0x3f,sizeof(dis));
	q.push(s);dis[s]=0;vis[s]=1;
	while(!q.empty())
	{
		int u=q.front();q.pop();vis[u]=0;
		for(re ed *i=head[u];i;i=i->next)
		{
			int v=i->to;
			if(dis[v]>dis[u]+i->w)
			{
				dis[v]=dis[u]+i->w;
				if(!vis[v])q.push(v),vis[v]=1;
			}
		}
	}
}

void jiantu()
{
      for(re int u=1;u<=n;++u)
      {
          for(re ed *i=head[u];i;i=i->next)
          {
              int v=i->to;
              if(dis[u]!=infll&&dis[v]!=infll&&dis[u]+i->w==dis[v])
              {
                  adde2(u,v);++rudu[v];//建立最短路径DAG
              }
          }
      }
}
```


## 2、然后把在最短路径上的边建立DAG，然后搞一个支配树。

（注意，这里的支配树是前面支配后面，所以不需要建立反图）

```cpp
root=n+1;
for(re int i=1;i<=n;++i)
{
	if(!rudu[i]&&dis[i]!=infll)q.push(i),fa[i][0]=root;
	else fa[i][0]=-1;
}
while(!q.empty())
{
	int u=q.front();q.pop();deep[u]=deep[fa[u][0]]+1;
	for(re int i=1;(1<<i)<=deep[u];++i)fa[u][i]=fa[fa[u][i-1]][i-1];
	for(re ed *i=head2[u];i;i=i->next)
	{
		int v=i->to;
		if(fa[v][0]==-1)fa[v][0]=u;
		else fa[v][0]=lca(fa[v][0],u);
		--rudu[v];
		if(!rudu[v])q.push(v);
	}
//	puts("OK");
}
```
## 3、然后再把支配树建图，跑一遍dfs求出size。

```cpp
for(re int i=1;i<=n;++i)if(fa[i][0]!=-1)adde(i,fa[i][0],0),adde(fa[i][0],i,0);
inline void dfs(int x,int f)
{
	size[x]=1;int v;
	for(re ed *i=head[x];i;i=i->next)
	{
		v=i->to;
		if(v==f)continue;
		dfs(v,x);
		size[x]+=size[v];
	}
	if(x!=root&&x!=s)maxx=max(maxx,size[x]);
   //注意，这里起点和超级源点不能算
}
```
## 最后有一些细节：

1、不能算上起点和超级源点，因为超级源点不被任何点支配，也不支配任何点，起点如果删掉，最短路径都没了，还谈什么最短路径改变。。。。

2、倍增LCA要注意特判x和y在一条链上面，否则会wa。

最后总代码：

# code：

```cpp
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define re register
#define ll long long
#define N 200000
#define M 300000
#define inf 0x3f3f3f3f
#define infll 0x3f3f3f3f3f3f3f3fll

inline int read()
{
	char ch=getchar();
	int x=0,f=1;
	for(;ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<1)+(x<<3)+ch-'0';
	return x*f;
}

struct ed{
	int to,w;
	ed *next;
}*edge,*head[N+10],*head2[N+10];

int n,m,s,rudu[N+10],fa[N+10][40],deep[N+10];
ll dis[N+10];
queue<int>q;

inline int lca(int x,int y)
{
	if(deep[x]<deep[y])swap(x,y);
	int delta=deep[x]-deep[y];
	for(re int i=0;(1<<i)<=delta;++i)if((1<<i)&delta)x=fa[x][i];
	if(x==y)return x;
	for(re int i=18;i>=0;--i)
	{
		if(fa[x][i]!=fa[y][i])
		{
			x=fa[x][i];y=fa[y][i];
		}
	}
	return fa[x][0];
}

inline void adde(int u,int v,int w)
{
	edge=new ed;
	edge->to=v;
	edge->next=head[u];
	edge->w=w;
	head[u]=edge;
}

inline void adde2(int u,int v)
{
//	printf("u==%d v==%d\n",u,v);
	edge=new ed;
	edge->to=v;
	edge->next=head2[u];
	head2[u]=edge;
}

bool vis[N+10];

void spfa()
{
	while(!q.empty())q.pop();
	memset(dis,0x3f,sizeof(dis));
	q.push(s);dis[s]=0;vis[s]=1;
	while(!q.empty())
	{
		int u=q.front();q.pop();vis[u]=0;
		for(re ed *i=head[u];i;i=i->next)
		{
			int v=i->to;
			if(dis[v]>dis[u]+i->w)
			{
				dis[v]=dis[u]+i->w;
				if(!vis[v])q.push(v),vis[v]=1;
			}
		}
	}
}

int size[N+10],maxx,root;

inline void dfs(int x,int f)
{
	size[x]=1;int v;
	for(re ed *i=head[x];i;i=i->next)
	{
		v=i->to;
		if(v==f)continue;
		dfs(v,x);
		size[x]+=size[v];
	}
	if(x!=root&&x!=s)maxx=max(maxx,size[x]);
}

signed main()
{
	n=read(),m=read(),s=read();
	int a,b,c;
	for(re int i=1;i<=m;++i)
	{
		a=read(),b=read(),c=read();
		adde(a,b,c);adde(b,a,c);
	}
	spfa();
//	for(re int i=1;i<=n;++i)printf("%lld ",dis[i]);puts("");
//	exit(0);
	for(re int u=1;u<=n;++u)
	{
		for(re ed *i=head[u];i;i=i->next)
		{
			int v=i->to;
			if(dis[u]!=infll&&dis[v]!=infll&&dis[u]+i->w==dis[v])
			{
				adde2(u,v);++rudu[v];
			}
		}
	}
	memset(head,0,sizeof(head));
	while(!q.empty())q.pop();
	root=n+1;
	for(re int i=1;i<=n;++i)
	{
		if(!rudu[i]&&dis[i]!=infll)q.push(i),fa[i][0]=root;
		else fa[i][0]=-1;
	}
	while(!q.empty())
	{
		int u=q.front();q.pop();deep[u]=deep[fa[u][0]]+1;
		for(re int i=1;(1<<i)<=deep[u];++i)fa[u][i]=fa[fa[u][i-1]][i-1];
		for(re ed *i=head2[u];i;i=i->next)
		{
			int v=i->to;
			if(fa[v][0]==-1)fa[v][0]=u;
			else fa[v][0]=lca(fa[v][0],u);
			--rudu[v];
			if(!rudu[v])q.push(v);
		}
//		puts("OK");
	}
//	for(re int i=1;i<=n;++i)printf("%d ",deep[i]);puts("");
	for(re int i=1;i<=n;++i)if(fa[i][0]!=-1)adde(i,fa[i][0],0),adde(fa[i][0],i,0);
	dfs(root,0);
	printf("%d\n",maxx);
	return 0;
}
```


---

## 作者：zhengrunzhe (赞：2)

提供一个lct建树

dijktra跑最短路，建最短路树(dag)，然后跑支配树，获取最大的除s的子树大小

建树过程需要支持连接一个叶子，找lca，最后还要获取子树，倍增什么的没意思，当然选择大力lct

[动态lca](https://www.luogu.org/problem/SP8791)这里学

然后lct维护子树大小，开个$imagsize$表示虚子树大小，access进行了虚实链切换，原来的儿子变虚加上，新儿子变实减掉

```cpp
#include<queue>
#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
typedef long long ll;
typedef vector<int>vit;
typedef pair<int,int>pii;
typedef pair<ll,int>pli;
typedef vector<pii>vpii;
typedef priority_queue<pli,vector<pli>,greater<pli> >heap;
template<class type>inline const void read(type &in)
{
	in=0;char ch=getchar();
	while (ch<48||ch>57)ch=getchar();
	while (ch>47&&ch<58)in=(in<<3)+(in<<1)+(ch&15),ch=getchar();
}
const ll inf=0x7f7f7f7f7f7f7f7f;
const int N=2e5+10;
int n,m,s,ans;
vpii g[N];
ll dis[N];
bool vis[N];
int ind[N];
vit in[N],out[N];
inline const void addedge(int u,int v)
{
	in[v].push_back(u);ind[v]++;
	out[u].push_back(v);
}
inline const void dijkstra(int s)
{
	memset(dis,0x7f,sizeof(dis));
	heap q;q.push(make_pair(dis[s]=0,s));
	while (!q.empty())
	{
		int u=q.top().second,v;q.pop();
		if (vis[u])continue;vis[u]=1;
		for (vpii::iterator i=g[u].begin();i!=g[u].end();i++)
			if (dis[v=i->first]>dis[u]+i->second)
				q.push(make_pair(dis[v]=dis[u]+i->second,v));
	}
}
inline const void build()
{
	for (int i=1;i<=n;i++)
		for (vpii::iterator j=g[i].begin();j!=g[i].end();j++)
			if (dis[j->first]^inf&&dis[j->first]==dis[i]+j->second)
				addedge(i,j->first);
}
class Link_Cut_Tree
{
	private:
		struct tree
		{
			int fa,son[2],size,imagsize;
		}t[N];
		inline const bool identity(int p)
		{
			return t[t[p].fa].son[1]==p;
		}
		inline const bool nroot(int p)
		{
			return t[t[p].fa].son[0]==p||identity(p);
		}
		inline const void pushup(int p)
		{
			t[p].size=t[t[p].son[0]].size+t[t[p].son[1]].size+t[p].imagsize+1;
		}
		inline const void rotate(int p)
		{
			const bool f=identity(p);
			int fa=t[p].fa,gfa=t[fa].fa,q=t[p].son[f^1];
			if (nroot(fa))t[gfa].son[identity(fa)]=p;
			t[t[p].son[f^1]=fa].son[f]=q;
			t[t[t[q].fa=fa].fa=p].fa=gfa;
			pushup(fa);
		}
		inline const void splay(int p)
		{
			for (int fa;nroot(p);rotate(p))
				if (nroot(fa=t[p].fa))
					rotate(identity(p)^identity(fa)?p:fa);
			pushup(p);
		}
		inline const int access(int x)
		{
			int y=0;
			for (;x;x=t[y=x].fa)
				splay(x),
				t[x].imagsize+=t[t[x].son[1]].size,
				t[x].imagsize-=t[t[x].son[1]=y].size,
				pushup(x);
			return y;
		}
		inline const int findroot(int x)
		{
			access(x);splay(x);
			while (t[x].son[0])x=t[x].son[0];
			splay(x);return x;
		}
	public:
		inline const void link(int x,int y)
		{
			splay(x);
			t[x].fa=y;
			access(y);splay(y);
			t[y].son[1]=x;pushup(y);
		}
		inline const int lca(int x,int y)
		{
			if (findroot(x)^findroot(y))return 0;
			access(x);return access(y);
		}
		inline const int getsize(int x)
		{
			access(x);splay(x);return t[x].imagsize+1;
		}
}lct;
inline const void toposort(int s)
{
	queue<int>q;q.push(s);
	while (!q.empty())
	{
		int u=q.front(),lca=-1;q.pop();
		for (vit::iterator i=out[u].begin();i!=out[u].end();i++)
			if (!--ind[*i])q.push(*i);
		for (vit::iterator i=in[u].begin();lca&&i!=in[u].end();i++)
				if (~lca)lca=lct.lca(lca,*i);
				else lca=*i;
		if (~lca&&lca)lct.link(u,lca);
	}
}
int main()
{
	read(n);read(m);read(s);
	for (int u,v,w;m--;)
		read(u),read(v),read(w),
		g[u].push_back(make_pair(v,w)),
		g[v].push_back(make_pair(u,w));
	dijkstra(s);build();toposort(s);
	for (int i=1;i<=n;i++)if (i^s&&dis[i]^inf)ans=max(ans,lct.getsize(i));
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：shao0320 (赞：1)

#### 题目大意

- 给定一个 $n$ 个点，$m$ 条边的带权无向图，和起点 $s$。
- 选择一个点 $u$（$u \neq S$），使在图中删掉点 $u$ 后，有尽可能多的点到 $s$ 的最短距离改变。
- $1 \leq n \leq 2 \times 10^5$,$1 \leq m \leq 3 \times 10^5$，给出的图无重边无自环，**不**保证连通。

分析：

第一反应是这样子的：暴力删点+$dijkstra$，可以做到$O(N^2logM)$的复杂度。

正解是支配树。

考虑建出最短路图，这张图上任意一条边$(u,v,w)$都满足$dis_u+w=dis_v$，这样做的好处在于，可以用这幅图表示这些点之间最短路的影像关系，如果一个点所有的入点最短路全改变了，那么这个点的最短路肯定也被改变了。

这幅图另一个比较好的性质在于这是一个DAG，简单证明一下：如果不是一个DAG那么必然存在$n,n\geq3$个点构成的环，那么这显然是不满足三角形不等式的。而DAG上建支配树只需要拓扑排序+LCA即可。

建好支配树后$dfs$一遍查询每个点支配的点的个数即可。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define N 1000005
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n,m,s,v[N],w[N],head[N],nxt[N],cnt,dist[N],vis[N],fa[N][25],f[N],dep[N],siz[N],de[N];
int v1[N],head1[N],nxt1[N],cnt1;
int v2[N],head2[N],nxt2[N],cnt2;
void add(int a,int b,int c)
{
	v[++cnt]=b;
	w[cnt]=c;
	nxt[cnt]=head[a];
	head[a]=cnt;
}
void add1(int a,int b)
{
	v1[++cnt1]=b;
	nxt1[cnt1]=head1[a];
	head1[a]=cnt1;
}
void add2(int a,int b)
{
	v2[++cnt2]=b;
	nxt2[cnt2]=head2[a];
	head2[a]=cnt2;
}
void dij()
{
	priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >q;
	memset(dist,0x3f,sizeof(dist));
	q.push(make_pair(0,s));
	dist[s]=0;
	while(!q.empty())
	{
		int c=q.top().second;
		q.pop();
		if(vis[c])continue;
		vis[c]=1;
		for(int i=head[c];i;i=nxt[i])
		{
			if(dist[v[i]]>dist[c]+w[i])
			{
				dist[v[i]]=dist[c]+w[i];
				q.push(make_pair(dist[v[i]],v[i]));
			}
		}
	}
}
int lca(int x,int y)
{
	if(dep[x]<dep[y])swap(x,y);
	for(int i=20;i>=0;i--)
	{
		if(dep[fa[x][i]]>=dep[y])x=fa[x][i];
	}
	if(x==y)return x;
	for(int i=20;i>=0;i--)
	{
		if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
	}
	return fa[x][0];
}
void dfs(int x)
{
	siz[x]=1;
	for(int i=head2[x];i;i=nxt2[i])
	{
		dfs(v2[i]);
		siz[x]+=siz[v2[i]];
	}
}
int main()
{
	n=read();m=read();s=read();
	for(int i=1;i<=m;i++)
	{
		int x=read(),y=read(),z=read();
		add(x,y,z);add(y,x,z);
	}
	dij();
	for(int i=1;i<=n;i++)
	{
		for(int j=head[i];j;j=nxt[j])
		{
			if(dist[v[j]]==dist[i]+w[j])
			{
				add1(i,v[j]);
				de[v[j]]++;
			}
		}
	}
	memset(f,-1,sizeof(f));
	queue<int>q;
	for(int i=1;i<=n;i++)
	{
		if(!de[i])q.push(i),f[i]=0;
	}
	while(!q.empty())
	{
		int c=q.front();
		q.pop();
		add2(f[c],c);
		dep[c]=dep[f[c]]+1;fa[c][0]=f[c];
		for(int i=0;i<=19;i++)fa[c][i+1]=fa[fa[c][i]][i];
		for(int i=head1[c];i;i=nxt1[i])
		{
			if(f[v1[i]]==-1)f[v1[i]]=c;
			else f[v1[i]]=lca(f[v1[i]],c);
			--de[v1[i]];
			if(!de[v1[i]])q.push(v1[i]);
		}
	}
	dfs(0);
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		if(i!=s)
		{
			ans=max(ans,siz[i]);
		}
	}
	cout<<ans<<endl;
}
```



---

## 作者：VenusM1nT (赞：1)

灭绝树。从 $\text{S}$ 跑最短路，然后就用可以所有在最短路上的边建出一个最短路“树”。说是树，其实它也有可能是一个 $\text{DAG}$，显然，这张图上删去某些点就会对从 $\text{S}$ 到某些点的最短路产生影响，那么我们要求的就是删去后产生影响最多的那个点，显然，这个点影响的点数就是它**支配**的点数，于是我们在新的这个 $\text{DAG}$ 上跑支配树即可。由于这是一个 $\text{DAG}$，所以用 [`P2597 [ZJOI2012]灾难`](https://www.luogu.org/blog/Venus/solution-p2597) 的做法，拓扑排序+$\text{LCA}$ 求灭绝树即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define MAXN 200005
#define MAXM 300005
using namespace std;
struct Node
{
	int u;
	ll dis;
	bool operator < (const Node &x) const
	{
		return x.dis<dis;
	}
};
priority_queue <Node> q;
queue <int> que;
int cnt[2],fst[2][MAXN],nxt[2][MAXM<<1],to[2][MAXM<<1],w[MAXM<<1];
int n,m,S,fr[MAXM],tx[MAXM],cot[MAXM],top[MAXN],ind[MAXN],f[MAXN][25],dep[MAXN],siz[MAXN];
ll dis[MAXN];
bool vis[MAXN];
void AddEdge(int u,int v,int c,int id)
{
	to[id][++cnt[id]]=v;
	nxt[id][cnt[id]]=fst[id][u];
	fst[id][u]=cnt[id];
	w[cnt[id]]=c;
}
void Dijkstra(int x)
{
	memset(dis,30,sizeof(dis));
	dis[x]=0;
	q.push((Node){x,0});
	while(!q.empty())
	{
		Node now=q.top();
		q.pop();
		int u=now.u;
		ll d=now.dis;
		if(d!=dis[u]) continue;
		for(int i=fst[0][u];i;i=nxt[0][i])
		{
			int v=to[0][i];
			if(dis[v]>dis[u]+w[i])
			{
				dis[v]=dis[u]+w[i];
				q.push((Node){v,dis[v]});
			}
		}
	}
}
void TopoSort()
{
	que.push(S);
	int tot=0;
	while(!que.empty())
	{
		int u=que.front();
		que.pop();
		top[++tot]=u;
		for(int i=fst[0][u];i;i=nxt[0][i])
		{
			int v=to[0][i];
			ind[v]--;
			if(!ind[v]) que.push(v);
		}
	}
	n=tot;
}
int LCA(int x,int y)
{
	if(dep[x]>dep[y]) swap(x,y);
	for(int i=20;i>=0;i--) if(dep[f[y][i]]>=dep[x]) y=f[y][i];
	if(x==y) return x;
	for(int i=20;i>=0;i--)
	{
		if(f[x][i]!=f[y][i])
		{
			x=f[x][i];
			y=f[y][i];
		}
	}
	return f[x][0];
}
int main()
{
	scanf("%d %d %d",&n,&m,&S);
	for(int i=1;i<=m;i++)
	{
		int x,y,z;
		scanf("%d %d %d",&x,&y,&z);
		AddEdge(x,y,z,0);
		AddEdge(y,x,z,0);
		fr[i]=x;
		tx[i]=y;
		cot[i]=z;
	}
	Dijkstra(S);
	cnt[0]=0;
	memset(fst[0],0,sizeof(fst[0]));
	for(int i=1;i<=m;i++)
	{
		if(dis[fr[i]]>dis[tx[i]]) swap(fr[i],tx[i]);
		if(dis[fr[i]]+cot[i]==dis[tx[i]])
		{
			AddEdge(fr[i],tx[i],cot[i],0);
			AddEdge(tx[i],fr[i],cot[i],1);
			ind[tx[i]]++;
		}
	}
	TopoSort();
	for(int i=20;i>=0;i--) f[S][i]=S;
	for(int i=2;i<=n;i++)
	{
		int lca=to[1][fst[1][top[i]]];
		for(int j=fst[1][top[i]];j;j=nxt[1][j])
		{
			int v=to[1][j];
			lca=LCA(lca,v);
		}
		f[top[i]][0]=lca;
		dep[top[i]]=dep[lca]+1;
		for(int j=1;j<=20;j++) f[top[i]][j]=f[f[top[i]][j-1]][j-1];
	}
	for(int i=n;i>1;i--) siz[f[top[i]][0]]+=++siz[top[i]];
	int ans=0;
	for(int i=2;i<=n;i++) ans=max(ans,siz[top[i]]);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：liangzihao (赞：1)

最短路树+支配树。

先把$s$到其他点的最短路求出来，然后连成最短路树（其实是一个$DAG$），$s$到任何点的最短路都在树上。 

然后在这个$DAG$上建支配树，断掉某个点的答案就是它所在$dfs$树的子树上有多少个点能被它支配，直接用支配链转移即可。

代码：
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <queue>
#define LL long long

const int maxn=2e5+7;
const int maxe=3e5+7;
const LL inf=1e16+7;

using namespace std;

int n,m,s,x,y,cnt;
int ls[maxn],last[maxn],idom[maxn],sdom[maxn],fa[maxn];
int p[maxn],val[maxn],f[maxn],dfn[maxn],id[maxn];
vector <int> dom[maxn],pre[maxn];
int v[maxn];
LL dis[maxn],w;

struct edge{
    int x,y,next;
    LL w;
}e[maxe*2];

struct node{
    int y,next;
}g[maxe*2];

struct rec{
    int x;
    LL d;
};

priority_queue <rec> q;

bool operator <(rec x,rec y)
{
    return x.d>y.d;
}

void dij()
{
    for (int i=1;i<=n;i++) dis[i]=inf;
    dis[s]=0;
    q.push((rec){s,0});
    while (!q.empty())
    {
        rec u=q.top();
        q.pop();
        int x=u.x;
        if (v[x]) continue;
        v[x]=1;
        for (int j=last[x];j>0;j=e[j].next)
        {
            int y=e[j].y;
            if (dis[y]>dis[x]+e[j].w)
            {
                dis[y]=dis[x]+e[j].w;
                q.push((rec){y,dis[y]});
            }
        }
    }
}

void add(int x,int y)
{
    g[++cnt]=(node){y,ls[x]};
    ls[x]=cnt;
}

void dfs(int x)
{
    dfn[x]=++cnt;
    id[cnt]=x;
    for (int i=ls[x];i>0;i=g[i].next)
    {
        int y=g[i].y;
        pre[y].push_back(x);
        if (!dfn[y])
        {
            fa[y]=x;
            dfs(y);
        }
    }
}

int smin(int x,int y)
{
    if (dfn[x]<dfn[y]) return x;
    return y;
}

int get(int x)
{
    if (p[x]==x) return x;
    int y=get(p[x]);
    if (dfn[sdom[val[p[x]]]]<dfn[sdom[val[x]]]) val[x]=val[p[x]];
    p[x]=y;
    return y;
}

void DMT()
{
    for (int i=cnt;i>0;i--)
    {
        int x=id[i];
        if (!pre[x].empty())
        {
            for (int j=0;j<pre[x].size();j++)
            {
                int y=pre[x][j];
                if (dfn[y]<dfn[x]) sdom[x]=smin(sdom[x],y);
                else
                {
                    get(y);
                    sdom[x]=smin(sdom[x],sdom[val[y]]);
                }
            }
        }
        pre[x].clear();
        p[x]=fa[x];
        dom[sdom[x]].push_back(x);
        if (!dom[fa[x]].empty())
        {
            for (int j=0;j<dom[fa[x]].size();j++)
            {
                int y=dom[fa[x]][j];
                get(y);
                int d=val[y];
                if (dfn[sdom[d]]>=dfn[sdom[y]]) idom[y]=sdom[y];
                                           else idom[y]=d;
            }
            dom[fa[x]].clear();
        }
    }
    for (int i=1;i<=cnt;i++)
    {
        int x=id[i];
        if (idom[x]!=sdom[x]) idom[x]=idom[idom[x]];
    }
    for (int i=cnt;i>0;i--)
    {
        x=id[i];
        f[idom[x]]+=f[x];
    }
}

int main()
{
    scanf("%d%d%d",&n,&m,&s);		
    for (int i=1;i<=m;i++)
    {
        scanf("%d%d%lld",&x,&y,&w);
        e[i].x=x;
        e[i].y=y;
        e[i].w=w;
        e[i].next=last[x];
        last[x]=i;
        e[i+m].x=y;
        e[i+m].y=x;
        e[i+m].w=w;
        e[i+m].next=last[y];
        last[y]=i+m;
    }	
    dij();
    for (int i=1;i<=m*2;i++)
    {
        int x=e[i].x,y=e[i].y;
        if (dis[x]+e[i].w==dis[y]) add(x,y);
    }	
    cnt=0;	
    dfs(s);
    for (int i=1;i<=n;i++)
    {
        p[i]=val[i]=sdom[i]=i;
        f[i]=1;
    }	
    DMT();
    int ans=0;
    for (int i=2;i<=cnt;i++)
    {
        int x=id[i];
        ans=max(ans,f[x]);
    }
    printf("%d",ans);
}
```

---

## 作者：Illusory_dimes (赞：1)

### 题目描述
给定 $n$ 个点， $m$ 条边的带权无向图，一个起点 $s$ 。

在删掉一个点的情况下，使尽可能多的点到起点的最短距离被改变，求最多的点数。

$1\leq n \leq n\cdot 10^5$ ， $1\leq m\leq 3\cdot 10^5$

（保证无重边，无自环，但不保证连通）

### 前置芝士
支配树（ DAG ，但其实我写的一般有向图版）

不会出门左拐，当然也可以由此进[我的博客](https://www.luogu.com.cn/blog/N-pilot-S/solution-p5180)，[别人的严格证明](https://www.cnblogs.com/fenghaoran/p/dominator_tree.html)。

### solution
其实这篇题解会很短，因为只需要解决的是最短距离被改变 $\Longrightarrow$ 无法到达的转化。

应该会很自然的想到先把最短路求出来。

怎么办呢

如果从起点到某个点 $u$ 的最短路径上的另一个能直接到达 $u$ 的点 $v$ 被去掉，那么 $v$ 就可能影响 $u$ 的最短路径。（万一还有一条路径长度与之相等还不经过 $v$ 呢）

我们可能会想到将所有对 $u$ 有影响的点 $v$ 存下来，显然只会越搞越复杂。（我们的眼光是要停留在整张图上的呀！）

所以只好强行建边，暂时完成了问题的转化，接下来由怎么解决呢？？？

发现直接跑支配树**一不小心**就能解决刚刚的问题。

艾玛，弄它！

时间复杂度 $O(n\log_{2} n)$ ，但不管问题转化后是跑 DAG 还是跑一般有向图，速度都蛮快的。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+10,M=3e5+10;
int n,m,s,ans[N],toot,tot,Ans;
int fsst[N],nxxt[M<<1],too[M<<1];
ll vaal[M<<1],diis[N],zz[M];
int xx[M],yy[M];
int fst[N][3],nxt[M+M+N],to[M+M+N];
int dfn[N],ord[N],cnt,fth[N];
int idom[N],semi[N],uni[N],mn[N];
struct mdzz
{
	int id;ll dis;
	bool operator <(const mdzz &b) const
	{return dis>b.dis;}
};
priority_queue<mdzz> q;
inline ll read()
{
	ll s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*w;
}
inline void addd(int u,int v,ll w)
{
	nxxt[++toot]=fsst[u];
	too[toot]=v,vaal[toot]=w;
	fsst[u]=toot;
}
inline void add(int u,int v,int id)
{
	nxt[++tot]=fst[u][id];
	to[tot]=v,fst[u][id]=tot;
}
inline void dijkstra(int s)
{
	memset(diis,0x3f,sizeof(diis));
	diis[s]=0;
	q.push((mdzz){s,0});
	while(!q.empty())
	{
		mdzz id=q.top();q.pop();
		int u=id.id;
		ll ds=id.dis;
		if(ds!=diis[u])continue;
		for(int i=fsst[u];i;i=nxxt[i])
		{
			int v=too[i];
			if(diis[v]>diis[u]+vaal[i])
			{
				diis[v]=diis[u]+vaal[i];
				q.push((mdzz){v,diis[v]});
			}
		}
	}
}
inline void Tarjan(int u)
{
	ord[dfn[u]=++cnt]=u;
	for(int i=fst[u][0];i;i=nxt[i])
	{
		int v=to[i];
		if(!dfn[v])
		{
			fth[v]=u;
			Tarjan(v);
		}
	}
}
inline int uni_query(int u)
{
	if(u==uni[u])return u;
	int tmp=uni_query(uni[u]);
	if(dfn[semi[mn[u]]]>dfn[semi[mn[uni[u]]]])mn[u]=mn[uni[u]];
	return uni[u]=tmp;
}
inline void Lengauer_Tarjan(int s)
{
	Tarjan(s);
	for(int i=1;i<=n;++i)semi[i]=uni[i]=mn[i]=i;
	for(int id=cnt;id>=2;--id)
	{
		int u=ord[id];
		for(int i=fst[u][1];i;i=nxt[i])
		{
			int v=to[i];
			if(!dfn[v])continue;
			uni_query(v);
			if(dfn[semi[u]]>dfn[semi[mn[v]]])semi[u]=semi[mn[v]];
		}
		uni[u]=fth[u];
		add(semi[u],u,2);
		u=fth[u];
		for(int i=fst[u][2];i;i=nxt[i])
		{
			int v=to[i];
			uni_query(v);
			idom[v]=(u==semi[mn[v]]?u:mn[v]);
		}
		fst[u][2]=0;
	}
	for(int i=2;i<=cnt;++i)
	{
		int u=ord[i];
		if(idom[u]^semi[u])
		idom[u]=idom[idom[u]];
	}
}
int main()
{
	n=read(),m=read(),s=read();
	for(int i=1;i<=m;++i)
	{
		int x=read(),y=read();
		ll z=read();
		addd(x,y,z),addd(y,x,z);
		xx[i]=x,yy[i]=y,zz[i]=z;
	}
	dijkstra(s);
	for(int i=1;i<=m;++i)
	{
		if(diis[xx[i]]>diis[yy[i]])
		{
			int tt=xx[i];
			xx[i]=yy[i],yy[i]=tt;
		}
		if(diis[xx[i]]+zz[i]==diis[yy[i]])
		{
			add(xx[i],yy[i],0);
			add(yy[i],xx[i],1);
		}
	}
	Lengauer_Tarjan(s);
	for(int i=cnt;i>=2;--i)ans[idom[ord[i]]]+=(++ans[ord[i]]);
	++ans[s];
	for(int i=1;i<=n;++i)
	if(i!=s&&ans[i]>Ans)Ans=ans[i];
	printf("%d",Ans);
	return 0;
}
```
只求能帮助到几个人罢。。

---

## 作者：OIer_ACMer (赞：0)

~~小火箭嗖嗖嗖~~！

------------
这道题是一道模板题，本来不想写的，但是~~闲得慌~~觉得很有价值就来~~试试水~~挑战一下，顺便帮我和大家复习了一遍支配树的知识点。

------------
## 算法详解：
支配树是什么？什么是支配？对于一张有向图，**确定一个根**，如果根到节点 $x$ 的**每条路径都经过**节点 $y$，那么称 $y$ 是 $x$ 支配点。求出原图的一个 **dfs 树**，那么 $x$ 的**支配点一定在 $x$ 到根的链**上。如果每个点向自己**深度最深的支配点**连边，就构成了**支配树**。


------------
## 大致思路：
这道题我们先通过 Dijkstra 算法跑出最短路，然后就是运用深搜求出 dfs 树，同时，在求的过程中，要用 LCA 合并每一条链，并找出各个点的支配点，得到每个支配点的影响大小。最终，再用 $ans$ 数组找出 $siz$ 最大的支配点，得出结果。


------------
## 具体步骤：
1. 输入数据，记得由于题目中的图是**带权无向图**，那么就要建**双向边**。


2. 老惯例，跑 dij 算法，求出**每个点**（不是一整条）的最短路路径，但要注意的是，再次放入队列中的 $dis_i$ 值需要取负值（至于是为什么请读者自行思考），还有可以用优先队列优化时间复杂度。


3. 接着，就是用 dfs 建树，由于把这个地方用 STL 中的队列太过复杂，所以本人建议用**手写队列**，更加方便。


4. 这一步就比较关键了，由于一棵树是由很多条链组成的，因此我们就要用倍增 LCA 算法求出两个点的最近公共祖先，然后加以合并，并计算影响范围（也可以说叫大小）。


5. 最终，我们用 $ans$ 数组一一比较 $siz_i$ 的大小，输出结果~~完结撒花~~。


------------
## 代码如下：

```c++

#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 3e5 + 10, T = 19;
priority_queue<pair<int, int> > q;
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
struct node
{
    int to, next, val;
} edge[N * 2];
int n, m, s, tot, hed[N], dis[N], dep[N], v[N];
int head, tail, top[N], f[N][T + 1], siz[N];
void add(int x, int y, int z)
{
    edge[++tot].to = y;
    edge[tot].next = hed[x];
    edge[tot].val = z;
    hed[x] = tot;
    return;
}
void dij() // 垃圾的dij
{
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0;
    q.push(make_pair(0, s));
    while (!q.empty())
    {
        int x = q.top().second;
        q.pop();
        if (v[x])
        {
            continue;
        }
        v[x] = 1;
        for (int i = hed[x]; i; i = edge[i].next)
        {
            int y = edge[i].to;
            if (dis[x] + edge[i].val < dis[y])
            {
                dis[y] = dis[x] + edge[i].val;
                q.push(make_pair(-dis[y], y)); // 这地方一定不能写错
            }
        }
    }
    return;
}
int LCA(int x, int y) // 垃圾的倍增LCA
{
    if (dep[x] > dep[y])
    {
        swap(x, y);
    }
    for (int i = T; i >= 0; i--)
    {
        if (dep[f[y][i]] >= dep[x])
        {
            y = f[y][i];
        }
    }
    if (x == y)
    {
        return x;
    }
    for (int i = T; i >= 0; i--)
    {
        if (f[x][i] != f[y][i])
        {
            x = f[x][i], y = f[y][i];
        }
    }
    return f[x][0];
}
void build()
{
    head = 1;
    tail = 1;
    top[1] = s;
    memset(v, 0, sizeof(v));
    for (int x = 1; x <= n; x++)
    {
        for (int i = hed[x]; i; i = edge[i].next)
        {
            int y = edge[i].to;
            int val = edge[i].val;
            if (dis[x] + edge[i].val == dis[edge[i].to])
            {
                v[edge[i].to]++;
            }
        }
    }
    while (head <= tail) // 模拟队列
    {
        int x = top[head++];
        dep[x] = dep[f[x][0]] + 1;
        for (int i = 1; i <= T; i++)
        {
            f[x][i] = f[f[x][i - 1]][i - 1];
        }
        for (int i = hed[x]; i; i = edge[i].next)
        {
            int y = edge[i].to;
            if (dis[x] + edge[i].val != dis[y])
            {
                continue;
            }
            v[y]--;
            if (!f[y][0])
            {
                f[y][0] = x;
            }
            else
            {
                f[y][0] = LCA(f[y][0], x);
            }
            if (!v[y])
            {
                top[++tail] = y;
            }
        }
    }
    return;
}
signed main()
{
    n = read();
    m = read();
    s = read();
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        u = read();
        v = read();
        w = read();
        add(u, v, w);
        add(v, u, w);//建带权无向图一定是双向的，要存双向边
    }
    dij();
    build();
    int ans = 0;
    for (int i = tail; i > 1; i--)
    {
        siz[top[i]]++, siz[f[top[i]][0]] += siz[top[i]];
        ans = max(ans, siz[top[i]]);
    }
    cout << ans;
    return 0;
}

```

[AC记录](https://www.luogu.com.cn/record/120650829)

---

## 作者：Little09 (赞：0)

DAG 上的支配树简单题。以下是前置知识。

### 最短路图

对于一个带权有向图和起点 $s$，我们先从起点 $s$ 跑一遍单源最短路。然后对于每条有向边 $(x,y,z)$，若 $dis_y=dis_x+z$，那么就在新图上从 $x$ 向 $y$ 连边。形成的图就是最短路图。

最短路图的简单性质：

- 从 $s$ 到任意一点 $u$ 的任意一条最短路的每一条边一定存在在新图中。除此之外的其他边一定不存在。

- 最短路图是一个 DAG。

### DAG 上的支配树

可以求 DAG 上任意一点 $u$ 删除后，起点 $s$ 无法到达的点的个数。

具体请参考[[ZJOI2012]灾难](https://www.luogu.com.cn/problem/P2597)。



------------
对于这道题，我们发现：删掉点 $u$ 后到 $s$ 的最短距离改变的点的数量，等价于在最短路图上删掉点 $u$ 后 $s$ 无法到达的数量。

然后我们直接建出最短路图，在上面建支配树求解即可。注意，删除的不能是起点。

[我的代码写得比较麻烦](https://www.luogu.com.cn/paste/gaez9xum)，但其实思路还是很清晰的。

---

## 作者：Spasmodic (赞：0)

首先看到破坏最短路，可以想到建出最短路图后转化为破坏路径。

于是这就转化为了一个支配树问题，只要建出支配树，然后算出除根节点（即 $s$ 节点）外每个节点的子树大小的最大值即可。

由于最短路图是 DAG，所以我们可以拓扑排序后按拓扑序建树，父节点就是它的前驱节点的 LCA。

复杂度 $O(n\log n)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct IO_Tp {
    const static ll _I_Buffer_Size = 2 << 22;
    char _I_Buffer[_I_Buffer_Size], *_I_pos = _I_Buffer;

    const static ll _O_Buffer_Size = 2 << 22;
    char _O_Buffer[_O_Buffer_Size], *_O_pos = _O_Buffer;

    IO_Tp() { fread(_I_Buffer, 1, _I_Buffer_Size, stdin); }
    ~IO_Tp() { fwrite(_O_Buffer, 1, _O_pos - _O_Buffer, stdout); }

    IO_Tp &operator>>(ll &res) {
    	ll f=1;
        while (!isdigit(*_I_pos)&&(*_I_pos)!='-') ++_I_pos;
        if(*_I_pos=='-')f=-1,++_I_pos;
        res = *_I_pos++ - '0';
        while (isdigit(*_I_pos)) res = res * 10 + (*_I_pos++ - '0');
        res*=f;
        return *this;
    }

    IO_Tp &operator<<(ll n) {
    	if(n<0)*_O_pos++='-',n=-n;
        static char _buf[10];
        char *_pos = _buf;
        do
            *_pos++ = '0' + n % 10;
        while (n /= 10);
        while (_pos != _buf) *_O_pos++ = *--_pos;
        return *this;
    }

    IO_Tp &operator<<(char ch) {
        *_O_pos++ = ch;
        return *this;
    }
} IO;

const ll N=200005,INF=0x3f3f3f3f3f3f3f3f;
//支配树 
ll d[N],sz[N],f[N][20];
ll dis[N];
bool vst[N];
vector<ll>es[N],tree[N];
void add(ll u,ll v){
	tree[u].push_back(v);
	d[v]=d[u]+1,f[v][0]=u;
	for(ll i=1;i<20;i++)f[v][i]=f[f[v][i-1]][i-1];
}
ll LCA(ll x,ll y){
	if(d[x]<d[y])swap(x,y);
	for(ll i=19;i>=0;i--)if(d[f[x][i]]>=d[y])x=f[x][i];
	if(x==y)return x;
	for(ll i=19;i>=0;i--)if(f[x][i]!=f[y][i])x=f[x][i],y=f[y][i];
	return f[x][0];
}
void build(ll u){
	if(vst[u])return;
	vst[u]=1;
	ll fa=0;
	for(auto x:es[u])build(x);
	for(auto x:es[u])
		if(!fa)fa=x;
		else fa=LCA(fa,x);
	add(fa,u);
}
void dfs(ll u){
	sz[u]=(dis[u]!=INF);
	for(auto v:tree[u])if(v!=f[u][0])dfs(v),sz[u]+=sz[v];
}

//建图 
ll n,m,s;
struct edge{ll t,w;edge(ll t_,ll w_){t=t_,w=w_;}};
vector<edge>G[N];
struct node{ll id,d;bool operator<(const node&x)const{return d>x.d;}};
void dijkstra(ll s){
	priority_queue<node>q;
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0;
	q.push((node){s,0});
	for(node cur;!q.empty();){
		cur=q.top();q.pop();
		ll u=cur.id;
		if(cur.d>dis[u])continue;
		for(auto x:G[u])
			if(dis[x.t]>dis[u]+x.w)
				dis[x.t]=dis[u]+x.w,q.push((node){x.t,dis[x.t]});
	} 
}
int main(){
	IO>>n>>m>>s;
	//建图
	for(ll i=1,u,v,w;i<=m;i++)IO>>u>>v>>w,G[u].push_back(edge(v,w)),G[v].push_back(edge(u,w)); 
	dijkstra(s);
	for(ll u=1;u<=n;u++)
		for(auto v:G[u])
			if(dis[v.t]==dis[u]+v.w)
				es[v.t].push_back(u),d[v.t]++;
	//最小支配树 
	for(ll i=1;i<=n;i++)if(!d[i])es[i].push_back(n+1);
	for(ll i=1;i<=n;i++)if(!vst[i])build(i);
	dfs(n+1);
	ll ans=0;
	for(ll i=1;i<=n;i++)if(i!=s)ans=max(ans,sz[i]);
	IO<<ans<<'\n';
	return 0;
}
```

---

## 作者：Uniecho1 (赞：0)

嗯......我是做了P2597来的。没做P2579的推荐回去做一下。

问：这个题不是DAG怎么说？

答：观察题面，有这么几个特点：
	
    1.要求最短路
    2.只有正边

所以只用跑一个单源最短路，以最短路上的点搞出DAG就行了

然后就是裸的支配树......

```cpp
#include<bits/stdc++.h>
#define big long long
using namespace std;
const big maxn=2e5+5;
big N,M,S,dis[maxn],in[maxn],top[maxn],lg2[maxn]={-1},dep[maxn],fa[maxn][20],size[maxn],ans;
vector<big>G[maxn],W[maxn],G1[maxn],G2[maxn],G3[maxn];
void topsort(){
	big cnt=0;
	queue<big>q;
	for(big i=1;i<=N;i++)
		if(!in[i]&&dis[i]!=4557430888798830399ll)
			q.push(i);
	while(!q.empty()){
		big u=q.front();
		q.pop();
		top[++cnt]=u;
		for(big i=0;i<G1[u].size();i++){
			big v=G1[u][i];
			--in[v];
			if(!in[v])
				q.push(v);
		}
	}
}
big LCA(big u,big v){
	if(dep[u]<dep[v])swap(u,v);
	while(dep[u]>dep[v])
		u=fa[u][lg2[dep[u]-dep[v]]];
	if(u==v)return u;
	for(big k=lg2[dep[u]];k>=0;k--)
		if(fa[u][k]!=fa[v][k])
			u=fa[u][k],v=fa[v][k];
	return fa[u][0];
}
void dfs(big u){
	size[u]=1;
	for(big i=0;i<G3[u].size();i++){
		big v=G3[u][i];
		dfs(v);
		size[u]+=size[v];
	}
	if(u!=N+1&&u!=S)ans=max(ans,size[u]);
}
int main(){
	//freopen("in.txt","r",stdin);
	ios::sync_with_stdio(false);
	cin>>N>>M>>S;
	for(big i=1;i<=N;i++)
		lg2[i]=lg2[i>>1]+1;
	for(big i=1,u,v,w;i<=M;i++){
		cin>>u>>v>>w;
		G[u].push_back(v);
		W[u].push_back(w);
		G[v].push_back(u);
		W[v].push_back(w);
	}//第一张图：无向带权图 
	memset(dis,0x3f,sizeof(dis));
	queue<big>q;
	q.push(S);
	dis[S]=0;
	while(!q.empty()){
		big u=q.front();
		q.pop();
		for(big i=0;i<G[u].size();i++){
			big v=G[u][i],w=W[u][i];
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				q.push(v);
			}
		}
	}//跑一波最短路 
	for(big u=1;u<=N;u++){
		for(big i=0;i<G[u].size();i++){
			big v=G[u][i],w=W[u][i];
			if(dis[v]==dis[u]+w){
				G1[u].push_back(v);//大力做有向无环图 
				++in[v];
				G2[v].push_back(u);//大力做反图 
			}
		}
	}
	topsort();
	for(big i=1;i<=N;i++){
		if(!top[i])break;
		big u=top[i];
		if(!G2[u].size())
			G2[u].push_back(N+1);
		big x=G2[u][0];
		for(big j=1;j<G2[u].size();j++){
			big v=G2[u][j];
			x=LCA(x,v);
		}
		G3[x].push_back(u);
		dep[u]=dep[x]+1;
		fa[u][0]=x;
		for(big k=1;k<=lg2[dep[u]];k++)
			fa[u][k]=fa[fa[u][k-1]][k-1];
	}
	dfs(N+1);
	cout<<ans;
	return 0;
}
```


---

