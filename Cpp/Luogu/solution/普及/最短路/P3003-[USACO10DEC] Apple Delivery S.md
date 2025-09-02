# [USACO10DEC] Apple Delivery S

## 题目描述

Bessie has two crisp red apples to deliver to two of her friends in the herd. Of course, she travels the C (1 <= C <= 200,000)

cowpaths which are arranged as the usual graph which connects P (1 <= P <= 100,000) pastures conveniently numbered from 1..P: no cowpath leads from a pasture to itself, cowpaths are bidirectional, each cowpath has an associated distance, and, best of all, it is always possible to get from any pasture to any other pasture. Each cowpath connects two differing pastures P1\_i (1 <= P1\_i <= P) and P2\_i (1 <= P2\_i <= P) with a distance between them of D\_i. The sum of all the distances D\_i does not exceed 2,000,000,000.

What is the minimum total distance Bessie must travel to deliver both apples by starting at pasture PB (1 <= PB <= P) and visiting pastures PA1 (1 <= PA1 <= P) and PA2 (1 <= PA2 <= P) in any order. All three of these pastures are distinct, of course.

Consider this map of bracketed pasture numbers and cowpaths with distances:

```cpp
               3        2       2
           [1]-----[2]------[3]-----[4]
             \     / \              /
             7\   /4  \3           /2
               \ /     \          /
               [5]-----[6]------[7]
                    1       2
```
If Bessie starts at pasture [5] and delivers apples to pastures [1] and [4], her best path is:

5 -> 6-> 7 -> 4\* -> 3 -> 2 -> 1\*

with a total distance of 12.

## 样例 #1

### 输入

```
9 7 5 1 4 
5 1 7 
6 7 2 
4 7 2 
5 6 1 
5 2 4 
4 3 2 
1 2 3 
3 2 2 
2 6 3 
```

### 输出

```
12 
```

# 题解

## 作者：Star1_3st (赞：11)

本来这是道裸题，显然最短路一定是$min(dis[s][a],dis[s][b])+dis[a][b]$。开始我思维混乱，一直在想从起点跑到$a$后是否跑回起点再去$b$点会更快？但我及时醒悟了，从$a$到起点再到$b$点如果最短，自然也会包括在$a,b$的最短路径里，无需额外判断。所以要求的就是上面那个东西，对每个询问两次最短路就够了。

但是这题稍微卡了一下SPFA，SPFA应该只有70分~~为什么我有80~~，所以并不是真的那么模板。dijkstra好，但我懒得打。故介绍一个十分简单，但许多人并不知道的优化。

SLF：松弛操作时优化入队，代码：

```cpp
if(b.size()&&dis[edge[i].to]<dis[b.front()])
	b.push_front(edge[i].to);
else
	b.push_back(edge[i].to);
```


优先选择dis值更小的点进行操作，显然算法可以跑得更快。

![](https://cdn.luogu.com.cn/upload/image_hosting/56c4t4ou.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

优化挺明显。

还有个lll优化：每次将入队结点距离和队内距离平均值比较，如果更大则插入至队尾。据说本题卡了，我没打。

正权图还是要用dijkstra，SPFA太好卡了。

最后注意一点：在帮大佬改代码时总出现奇怪的CPU报错，但感觉却和我的AC代码什么区别也没有，于是把我交了的代码拷下来又跑了一遍，发现昨天好好的代码发生了同样的错误……真不知道我是怎么A的。其实是在进行SLF优化时未判断队列是否为空就直接访问$b.front()$，RE与否全靠运气……在访问前加个判断就好了。

下面是代码。在提交的基础上修复了上面的问题。

```cpp
#include<bits/stdc++.h>
struct node
{
	int from,to,dis,next;
}edge[400001];
int n,m,num,head[200001],dis[200001],book[200001];
std::deque<int> b;
void add(int u,int v,int w)
{
	edge[++num].from=u;
	edge[num].to=v;
	edge[num].dis=w;
	edge[num].next=head[u];
	head[u]=num;
	return;
}

int spfa(int s,int t)
{
	memset(book,0,sizeof(book));
	memset(dis,0x7f,sizeof(dis));
	b.push_front(s);
	book[s]=1;
	dis[s]=0;
	while(b.size())
	{
		int x=b.front();
		b.pop_front();
		book[x]=0;
		for(int i=head[x];i;i=edge[i].next)
			if(dis[edge[i].to]>dis[x]+edge[i].dis)
			{
				dis[edge[i].to]=dis[x]+edge[i].dis;
				if(!book[edge[i].to])
				{
					book[edge[i].to]=1;
					if(b.size()&&dis[edge[i].to]<dis[b.front()])
						b.push_front(edge[i].to);
					else
						b.push_back(edge[i].to);
				}
			}
	}

	return dis[t];
}

int main()
{
	int s,a,b;
	scanf("%d%d%d%d%d",&m,&n,&s,&a,&b);
	for(int i=1;i<=m;i++)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
		add(v,u,w);
	}
	
	printf("%d",std::min(spfa(s,a),spfa(s,b))+spfa(a,b));
	return 0;
}
```





---

## 作者：流逝丶 (赞：9)

首先不难看出这是最短路

然后一个起点，两个终点。

从起点跑一边dij，比较到两个终点的距离，选小的那个，再以其中一个终点为起点，跑dij，ans加上到另一个终点的距离，就是最终结果。

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
struct node{
    int to,nxt,dis;
}e[400010];
struct edge{
    int val,nm;
    bool operator < (const edge &x) const {
        return val > x.val;
    }
};
priority_queue<edge> dij;
int head[100001],in[100001],d[100001];
int cnt;
int n,m,s1,s2,s3;
inline int read(){
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=s*10+ch-'0';ch=getchar();}
	return s*w;
}
inline void add(int from,int to,int dis){
    e[++cnt]=(node){to,head[from],dis};
    head[from]=cnt;
}
inline void di(int s){
    for(int i=1;i<=n;++i)d[i]=2147483647;
    memset(in,0,sizeof(in));
	dij.push((edge){0,s});
    d[s]=0;
    while(!dij.empty()){
        int t=dij.top().nm;
        dij.pop();
        if(in[t])continue;
        in[t]=1;
        for(int i=head[t];i!=0;i=e[i].nxt){
            if(!in[e[i].to]&&d[t]+e[i].dis<d[e[i].to]){
                d[e[i].to]=d[t]+e[i].dis;
                dij.push((edge){d[e[i].to],e[i].to});
            }	
        }
    }
}
int main(){
    scanf("%d%d%d%d%d",&m,&n,&s1,&s2,&s3);
    int x,y,z;
    for(int i=1;i<=m;++i){
        scanf("%d%d%d",&x,&y,&z);
        add(x,y,z);add(y,x,z);
    }
    di(s1);
    int ans=min(d[s2],d[s3]);
    di(s2);
    ans+=d[s3];
    printf("%d",ans);
    return 0;
}
```


---

## 作者：_jimmywang_ (赞：6)

~~一道会最短路就能（基本上）做出的题啊，建议改成黄题~~

### 进入正题：

首先，我们知道，我们有两个目标点。那只有两种情况了：要么先去第一个，要么先去第二个。

所以，用$Dijkstra$跑一遍以$PB$ 为起点的最短路，再跑一遍以 $PA$_$1$为起点的最短路，求出$min(dis[PB][PA1],dis[PB][PA2])+dis[PA1][PA2]$就行了~

代码：

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll inf=2147483647;
inline ll r()
{
    char c=getchar();ll x=0,f=1;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
ll n,m,ss,s1,s2;
ll dis[1000010];
ll head[1000010];
struct edge{
	ll u,v,w,nx;
}e[1000010];
struct node{
	ll w,now;
	inline bool operator <(const node &x)const{
		return w>x.w;
	}
};
ll tot;
bool vis[100010];
void add(ll u,ll v,ll w){
	ll i=++tot;
	e[i].u=u;
	e[i].v=v;
	e[i].w=w;
	e[i].nx=head[u];
	head[u]=i;
}
priority_queue<node> q;
ll s_to_1,s_to_2,_to_2;
int main() {
	m=r(),n=r(),ss=r(),s1=r(),s2=r();
	for(int i=1;i<=n;i++)dis[i]=inf;
	for(int i=1;i<=m;i++){
		ll u=r(),v=r(),w=r();
		add(u,v,w);
		add(v,u,w);
	}
	dis[ss]=0;
	q.push((node){0,ss});
	while(!q.empty()){
		ll u=q.top().now;
		q.pop();
		if(vis[u])continue;
		vis[u]=1;
		for(int i=head[u];i;i=e[i].nx){
			ll v=e[i].v;
			if(dis[v]>dis[u]+e[i].w){
				dis[v]=dis[u]+e[i].w;
				q.push((node){dis[v],v});
			}
		}
	}
	s_to_1=dis[s1];
	s_to_2=dis[s2];
	memset(dis,0,sizeof(dis));
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++)dis[i]=inf;
	dis[s1]=0;
	q.push((node){0,s1});
	while(!q.empty()){
		ll u=q.top().now;
		q.pop();
		if(vis[u])continue;
		vis[u]=1;
		for(int i=head[u];i;i=e[i].nx){
			ll v=e[i].v;
			if(dis[v]>dis[u]+e[i].w){
				dis[v]=dis[u]+e[i].w;
				q.push((node){dis[v],v});
			}
		}
	}
	_to_2=dis[s2];
	printf("%lld",min(s_to_1,s_to_2)+_to_2);
	return 0;
}
```


---

## 作者：JK_LOVER (赞：6)

最短路的模板题：
分析：

目标点必须到

目标点的距离一定

就有以下方式：

- 走第一个再走第二个

- 走第二个再走第一个

~~（这不显而易见吗）~~

ans = min(dist[点1]，dist[点2])+dist[点2到点1]

解决：
1. 求出源点到2个目标点的距离

1. 目标点之间的距离 

![](https://cdn.luogu.com.cn/upload/image_hosting/8o6klwzp.png)

这是样例的最短路径


这题卡SPFA，但是
~~（他还没有死）~~
还可以优化

主要思路是与头元素的dist值比较，大了就插后面，否则插前面

这样可以走一个较优的一条路

上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 100010;
int head[N<<2],cnt = 0,n,m,to_1,to_2,from,dist[N];
bool vis[N];
struct EDGE{
	int next;
	int to;
	int w;
}edge[N<<2];
deque<int> q;
void add(int x,int y,int w)
{
	cnt++;
	edge[cnt].next = head[x];
	edge[cnt].to = y;
	edge[cnt].w = w;
	head[x] = cnt;
}
void SPFA(int s)
{
	memset(dist,0x3f,sizeof(dist));
	memset(vis,false,sizeof(vis));
	dist[s] = 0;
	q.push_back(s);
	while(!q.empty())
	{
		int x = q.front();
		q.pop_front();
		vis[x] = false;
		for(int i = head[x];i;i = edge[i].next)
		{
			int y = edge[i].to;
			if(edge[i].w<dist[y]-dist[x])
			{
				dist[y] = dist[x] + edge[i].w;
				if(vis[y]) continue;

				q.push_back(y);
				vis[y]=true;
			}
		}
	}
}
int main()
{
//	freopen("1.in","r",stdin);
	cin>>m>>n>>from>>to_1>>to_2;
	for(int i = 1;i <= m;i++)
	{
		int a,b,c;
		cin>>a>>b>>c;
		add(a,b,c);
		add(b,a,c);
	}
	int ans = 0;
	SPFA(from);
	ans = min(dist[to_1],dist[to_2]);
	SPFA(to_1);
	cout<<ans+dist[to_2]<<endl;
	return 0;
}
```


居然dijkstra算法还是要慢一些

![](https://cdn.luogu.com.cn/upload/image_hosting/9ix3xt5t.png)

这里把dij的代码发一下

```cpp
#include<iostream>
#include<cmath>
#include<cstring>
#include<queue>
using namespace std;
const int N = 100010;
int head[N<<2],cnt = 0,n,m,to_1,to_2,from,dist[N];
bool vis[N];
struct EDGE{
	int next;
	int to;
	int w;
}edge[N<<2];
struct node{
	int pos;
	int dist;
	bool operator <(const node& S)const{
	return dist>S.dist;
	}
};
priority_queue<node> q;
void add(int x,int y,int w)
{
	cnt++;
	edge[cnt].next = head[x];
	edge[cnt].to = y;
	edge[cnt].w = w;
	head[x] = cnt;
}
void dj(int s)
{
	memset(dist,0x3f,sizeof(dist));
	memset(vis,false,sizeof(vis));
	dist[s] = 0;
	q.push((node){s,dist[s]});
	while(!q.empty())
	{
		int x = q.top().pos;
		q.pop();
		if(vis[x]) continue;
		vis[x] = true;
		for(int i = head[x];i;i = edge[i].next)
		{
			int y = edge[i].to;
			if(edge[i].w<dist[y]-dist[x])
			{
				dist[y] = dist[x] + edge[i].w;
				q.push((node){y,dist[y]});
			}
		}
	}
}
int main()
{
//	freopen("1.in","r",stdin);
	cin>>m>>n>>from>>to_1>>to_2;
	for(int i = 1;i <= m;i++)
	{
		int a,b,c;
		cin>>a>>b>>c;
		add(a,b,c);
		add(b,a,c);
	}
	int ans = 0;
	dj(from);
	ans = min(dist[to_1],dist[to_2]);
	dj(to_1);
	cout<<ans+dist[to_2]<<endl;
	return 0;
}
```


如有不懂私聊QwQ



---

## 作者：玫葵之蝶 (赞：4)

首先，这题思路很清晰，因为只有两条路，s->1->2或s->2->1，因此分别用1和2做两遍SPFA，取较小的一个就好了。

这题值得注意的是时间，很多人是70分，你一定是用的裸的SPFA，因为我就是这么干的，然后3个TLE，怎么办呢？这时就要用到SPFA的优化了，哔（不要问我为什么），有请SLF出场！

SLF（Small Label First），意思就是小的在前，具体就是：假设要进队的点是t，队首元素是f，那么如果d[t]< d[f]，就把t放队首，否则放队尾。

此时肯定有人问，怎么放队首呢？办法还是出自c++的STl，c++强大的STl中有一个双端队列deque，头尾都可以加元素，这样问题就解决了。它的原理应该和dijkstra是一(bu)样(tong)的。

貌似还有一个优化更好，叫LLL，Large Label Last，可以自行百度，我不多做介绍。

SLF可以优化15%~20%，LLL可以优化50%，自己看情况使用（不过此题SLF就过了）。

下来贴代码：( 希望各位大佬可以来看看我的博客：<http://blog.csdn.net/stone41123/article/details/74157231> )

```cpp
#include<bits/stdc++.h>
#define inf 2100000000
using namespace std;
struct edge{
    int to,next,w;
}e[400001];
int m,n,s,a,b,tot=0;
int d[100001];
int head[100001];
int in[100001];
void addedge(int x,int y,int l){
    tot++;
    e[tot].to=y;
    e[tot].w=l;
    e[tot].next=head[x];
    head[x]=tot;
}
deque<int> q;
void spfa(int st){
    memset(in,0,sizeof(in));
    memset(d,127,sizeof(d));
    d[st]=0;
    in[st]=1;
    q.push_front(st);
    while(!q.empty()){
        int k=q.front();
        q.pop_front();
        in[k]=0;
        for(int i=head[k];i!=0;i=e[i].next){
            if(d[k]+e[i].w<d[e[i].to]){
                d[e[i].to]=d[k]+e[i].w;
                if(!in[e[i].to]){
                    if(!q.empty()&&d[e[i].to]<d[q.front()]){
                        q.push_front(e[i].to);
                    }
                    else{
                        q.push_back(e[i].to);
                    }
                }
            }
        }
    }
}
int main(){
    cin>>m>>n>>s>>a>>b;
    for(int i=1;i<=m;i++){
        int x,y,l;
        scanf("%d %d %d",&x,&y,&l);
        addedge(x,y,l);
        addedge(y,x,l);
    }
    int ans1=0;
    int ans2=0;
    spfa(a);
    ans1+=d[b]+d[s];
    spfa(b);
    ans2+=d[a]+d[s];
    int ans=min(ans1,ans2);
    cout<<ans;
    return 0;
}
```

---

## 作者：Sober_Clever (赞：4)

题目传送门：		[P3003 [USACO10DEC]苹果交货Apple Delivery](https://www.luogu.org/problemnew/show/P3003)

记原点为s，两个终点分别为t1、t2

分别以s、t1、t2跑一遍dij，记下s~t1、s~t2和t1~t2的距离

最后答案即为min(d[s][t1],d[s][t2])+d[t1][t2])
（先t1后t2,或者先t2后t1）

注意是总边数在前，总点数在前~~（害死人了）~~
```cpp
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=100000 + 3;
const int MAXM=200000 + 3;
//快读
int read()
{
	int  x=0,w=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') w=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}
	return x*w;	
}

struct Edge
{
	int to,next,w;
}e[MAXM*2];
int head[MAXN]={0},cnt=0; 
inline void add(int u,int v,int w)
{
	e[++cnt].to=v,e[cnt].w=w,e[cnt].next=head[u],head[u]=cnt;	
}

int n,m,d[MAXN],vis[MAXN]={0};
void dij(int s)
{
	memset(vis,0,sizeof(vis));
	memset(d,127,sizeof(d));
	priority_queue<pair<int,int> > Q;
	d[s]=0,Q.push(make_pair(-d[s],s));
	while(!Q.empty())
	{
		int u=Q.top().second;
		Q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(int i=head[u];i;i=e[i].next)
		{
			int v=e[i].to;
			if(d[v]>d[u]+e[i].w)
			{
				d[v]=d[u]+e[i].w;
				Q.push(make_pair(-d[v],v));
			}
		}
	}
}

int main()
{
	m=read(),n=read();
	int s=read(),t1=read(),t2=read();

	for(int i=1;i<=m;i++)
	{
		int u=read(),v=read(),w=read();
		add(u,v,w);
		add(v,u,w);
	}
	int g[3][3];//0表示s、1表示t1、2表示t2
   //用g记下三点相互之间的距离
	dij(s);
	g[0][1]=d[t1],g[0][2]=d[t2];
	dij(t1);
	g[1][0]=d[s],g[1][2]=d[t2];
	int ans;
	
	ans=min(g[0][1],g[0][2])+g[1][2];
	printf("%d\n",ans);
	return 0;	
} 
```


---

## 作者：Hammer_cwz_77 (赞：3)

这道题很好做，直接套slf优化的模板，跑两次取最小值，就好了，本人先开始把slf和lll优化一起加了进去，但是由于lll被常数卡爆了，卡到指数级去了，然后怎么优化都会T掉第二个点，如果用lll优化会T掉4个点（本人亲手实验），用slf可以A掉，而且很快。直接上代码吧。





```cpp
#include<algorithm>
#include <iostream>
#include  <cstdlib>
#include  <cstring>
#include  <climits>
#include   <cstdio>
#include   <string>
#include    <cmath>
#include    <stack>
#include    <queue>
#include    <deque>
using namespace std;
const int gg=450000;
const int INF=1e9;
int head[gg];
struct node
{
    int next;
    int w;
    int to;
} a[gg];
int dis[gg];
bool vis[gg];
int c,p,pb,pa1,pa2,cnt;
int ans;
int ans2;
int sum,tot;
int rans;
inline void add(int i,int j,int w)
{
    a[++cnt].to=j;
    a[cnt].next=head[i];
    a[cnt].w=w;
    head[i]=cnt;
}
inline void spfa(int s)
{
    deque<int>q;
    memset(vis,false,sizeof(vis));
    memset(dis,0x7f,sizeof(dis));
    dis[s]=0;
    vis[s]=true;
    q.push_back(s);
    while(!q.empty())
    {
        int u=q.front();
        q.pop_front();
        vis[u]=false;
        for(register int i=head[u]; i; i=a[i].next)
        {
            int v=a[i].to;
            if(dis[v]>dis[u]+a[i].w)
            {
                dis[v]=dis[u]+a[i].w;
                if(!vis[v])
                {
                    vis[v]=true;
                    if(q.empty()||dis[v]>dis[q.front()])
                    {
                        q.push_back(v);
                    }
                    else
                        q.push_front(v);
                }
            }
        }
    }
}
int main()
{
    scanf("%d%d%d%d%d",&c,&p,&pb,&pa1,&pa2);
    for(register int i=1; i<=c; i++)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        add(x,y,z);
        add(y,x,z);
    }
    spfa(pa1);
    ans+=dis[pa2]+dis[pb];
    spfa(pa2);
    ans2+=dis[pa1]+dis[pb];
    rans=min(ans,ans2);
    printf("%d\n",rans);
    return 0;
}
```

---

## 作者：huangrenheluogu (赞：2)

蒟蒻的第二篇题解，如有错误请指出。

这道题目拿到最优解有一点难度，但是其实是一道模板题。

按照题意，我们发现，本质就是从固定的点开始进行最短路搜索，单源最短路径，我们很快就想到了用 `Dijskra` 来解决这个问题。

可能有些大佬经过精密的计算可以发现用两次 `Dijskra` 来解决问题，但是其实用三次 `Dijskra` 就可以过。

首先需要邻接表的代码：
```cpp
inline void add(long long x,long long y,long long z){
	w[++tot]=z;
	son[tot]=y;
	nxt[tot]=fir[x];
	fir[x]=tot;
}
```


先上 `Dijskra` 的模板代码：
```cpp
inline void Dijstra(long long s,long long opt){
	memset(vis,false,sizeof(vis));
	dis[opt][s]=0;
	cnt=0;
	while(!q.empty()) q.pop();
	q.push((data){0,s});
	while(cnt<p&&!q.empty()){
		tem1=q.top().dis,tem2=q.top().num;
		q.pop();
		if(vis[tem2]) continue ;
		vis[tem2]=true ;
		for(long long i=fir[tem2];i;i=nxt[i]){
			if(vis[son[i]]) continue ;
			if(dis[opt][son[i]]>tem1+w[i]){
				dis[opt][son[i]]=tem1+w[i];
				q.push((data){dis[opt][son[i]],son[i]});
			}
		}
	}
}
```
这里我加上了堆优化，可以加快速度。

结尾我们加上三次 `Dijskra`，就可以圆满解决问题了。

我用了一个 `opt` 来储存次数，那么我们就可以直接调用了，这样直接调用三次 `Dijskra` 就解决问题了。

最后给大家完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long tem1,tem2,cnt,c,p,pb,pa1,pa2,x,y,z,fir[500005],nxt[500005],son[500005],w[500005],tot,dis[5][200005];
struct data{
	long long dis,num;
	friend bool operator > (data x,data y){
		return x.dis>y.dis;
	}
};
priority_queue<data, vector<data >, greater<data > > q;
bool vis[200005];
inline void read(long long &res){
	res=0;long long f=1;char ch=getchar();
	while('0'>ch||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while('0'<=ch&&ch<='9'){
		res=(res<<1)+(res<<3)+(ch^48);
		ch=getchar();
	}
	res=res*f;
}
inline void put(long long x){
	if(x<0) putchar('-'),x=-x;
	if(x>=10) put(x/10);
	putchar((x%10)^48);
}
inline void add(long long x,long long y,long long z){
	w[++tot]=z;
	son[tot]=y;
	nxt[tot]=fir[x];
	fir[x]=tot;
}
inline void Dijstra(long long s,long long opt){
	memset(vis,false,sizeof(vis));
	dis[opt][s]=0;
	cnt=0;
	while(!q.empty()) q.pop();
	q.push((data){0,s});
	while(cnt<p&&!q.empty()){
		tem1=q.top().dis,tem2=q.top().num;
		q.pop();
		if(vis[tem2]) continue ;
		vis[tem2]=true ;
		for(long long i=fir[tem2];i;i=nxt[i]){
			if(vis[son[i]]) continue ;
			if(dis[opt][son[i]]>tem1+w[i]){
				dis[opt][son[i]]=tem1+w[i];
				q.push((data){dis[opt][son[i]],son[i]});
			}
		}
	}
}
inline long long min(long long x,long long y){
	return x<y?x:y;
}
int main(){
	memset(dis,127,sizeof(dis));
	read(c),read(p),read(pb),read(pa1),read(pa2);
	for(long long i=1;i<=c;i++){
		read(x),read(y),read(z);
		add(x,y,z);
		add(y,x,z);
	}
	Dijstra(pb,0),Dijstra(pa1,1),Dijstra(pa2,2);
	put(min(dis[0][pa1]+dis[1][pa2],dis[0][pa2]+dis[2][pa1]));
	return 0;
}
```


---

## 作者：_JF_ (赞：2)

## P3003 [USACO10DEC]Apple Delivery S 题解

前置知识： [dijkstra 堆优化](https://oiwiki.com/graph/shortest-path/)


和他的模板： [单源最短路径（标准版](https://www.luogu.com.cn/problem/P4779)

题目大意：

给一个图，注意边是**双向**的，然后给出 $s1,s2,s3$ ,其中 $s1$ 是起点。然后要求$ s1$ 到 $s2$ 加上 $s2$ 到 $s3$ 和 $s1$ 到 $s3$ 加上 $s2$ 到 $s3$  哪一个更小。

就是：

 $ans=min(dis[s1][s2]+dis[s2][s3],dis[s1][s3]+dis[s2][s3])$

所以上述式子可以转换为：

$ans=min(dis[s1][s2],dis[s1][s3])+dis[s2]+[s3]$

（这里为了方便理解才把 $dis$ 写成二维数组的形式，在代码中是已经确定起点了的。）

最后需要注意 $m$ 和 $n$ 的输入顺序。

所以代码便是：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =4000;
const int INF =1e6+10;
#define int long long
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >q;
struct node
{
	int w,to,next;
}e[INF];
long long n,m,cnt,head[INF],dis[INF],s1,s2,s3;
bool vis[INF];
void add(int u,int v,int w)
{
	e[++cnt].to=v;
	e[cnt].w=w;
	e[cnt].next=head[u];
	head[u]=cnt;
}
void dijkstra(int x)
{
	memset(vis,0,sizeof(vis));
	memset(dis,127,sizeof(dis));
	q.push(make_pair(0,x));
	dis[x]=0;
	while(!q.empty())
	{
		int now=q.top().second;
		q.pop();
		if(vis[now])
			continue;
		vis[now]=1;
		for(int i=head[now];i;i=e[i].next)
			if(dis[now]+e[i].w<dis[e[i].to])
			{
				dis[e[i].to]=dis[now]+e[i].w;
				q.push(make_pair(dis[e[i].to],e[i].to));
			}
	}
}
signed main()
{
	cin>>m>>n>>s1>>s2>>s3;
	for(int i=1;i<=m;i++)
	{
		int u,v,w;
		cin>>u>>v>>w;
		add(u,v,w);
		add(v,u,w);
	}
	dijkstra(s1);
	int minn=min(dis[s2],dis[s3]);
	dijkstra(s2);
	minn+=dis[s3];
	cout<<minn<<endl;
}
```


---

## 作者：Kalium (赞：2)

# P3003 [USACO10DEC]Apple Delivery S题解

## 前言：

生日前发了个题解，顺带写了两题 P2006，P1227，当做自己的生日礼物了。

## 题意：

n 个点，m 条边，1 个起点，2 个终点，求从起点开始，要求经过两个终点的最短路。

## 思路：

这有蓝题？这题怕不是比 [P6833](https://www.luogu.com.cn/problem/P6833) 还简单？

思路在你化简完题意后就很清晰了，用 dijkstra，只要求 $\min(dis_{s, f1} + dis_{f1, f2}, dis_{s, f2} + dis_{f2, f1})$ 即可。

那么由于这个是无向图，所以 $dis_{f1, f2}$ 与 $dis_{f2, f1}$ 是等价的。

即 $ans = \min(dis_{s, f1}, dis_{s, f2}) + dis_{f1, f2}$。

跑最短路去吧。

## 细节：

1.n 和 m 别输入反了，血泪教训！！！

2.注意要堆优化。

## 代码：

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>

#define inf 0x3f3f3f3f

using namespace std;

const int N = 1e5 + 7;
const int M = 2e5 + 7;

struct Edge {
	int to, next, w;
} edge[M << 1];

int head[N], cnt;

int n, m, s, f1, f2;

struct node {
	int x, id;
};

struct HEAP {
	node heap[N << 2 | 1];
	int sz;
	
	inline bool empty() {
		return sz == 0;
	}
	
	inline node top() {
		return heap[1];
	}
	
	inline void push(node a) {
		int now = ++ sz;
		
		heap[now].x = a.x, heap[now].id = a.id;
		
		while (now != 1) {
			int fa = now >> 1;
			
			if (heap[fa].x > heap[now].x)
				swap(heap[fa], heap[now]);
			else break;
			
			now = fa;
		} 
		
		return ;
	}
	
	inline void pop() {
		swap(heap[1], heap[sz]);
		
		sz --;
		
		int now = 1;
		
		while (now << 1 <= sz) {
			int son = now << 1;
			
			if (son + 1 <= sz && heap[son].x > heap[son + 1].x) son ++;
			
			if (heap[son].x < heap[now].x)
				swap(heap[son], heap[now]);
			else break;
			
			now = son;
		}
		
		return ;
	} 
} Heap;

int dis[N];

bool flag[N];

int ans;

inline int mina(int a, int b) {
	if (a < b)
		return a;
	return b;
}

inline void addedge(int u, int v, int w) {
	edge[++ cnt] = (Edge){v, head[u], w};
	head[u] = cnt;
}

inline void dijkstra(int b) {
	memset(dis, inf, sizeof(dis));
	memset(flag, 0, sizeof(flag));
	
	dis[b] = 0;
	
	Heap.push((node) {dis[b], b});
	
	while (! Heap.empty()) {
		int k = Heap.top().id;
		
		Heap.pop();
		
		if (flag[k]) continue;
		
		flag[k] = 1;
		
		for (int i = head[k]; ~i; i = edge[i].next) {
			int v = edge[i].to;
			
			if (dis[v] > dis[k] + edge[i].w) {
				dis[v] = dis[k] + edge[i].w;
				Heap.push((node) {dis[v], v});
			}
		}
	}
	
	/*cout << b << endl;
    for (int i = 1; i <= n; i ++)
    	cout << dis[i] << " ";
    cout << endl;*/
}

int main() {
	memset(head, -1, sizeof(head));
	
	scanf("%d %d %d %d %d", &m, &n, &s, &f1, &f2);
	
	for (int i = 1; i <= m; i ++) {
		int u, v, w;
		
		scanf("%d %d %d", &u, &v, &w);
		
		addedge(u, v, w);
		addedge(v, u, w); 
	}
	
	dijkstra(f1);
	
	ans += dis[f2];
	
	dijkstra(s);
	
	ans += mina(dis[f1], dis[f2]);
	
	printf("%d\n", ans);
	
	return 0;
}
```

## 后记：

1.建议这题评黄色。

2.skyyyr同学：

生日快乐，请你继续加油，争取在明年拿到 TG1=。

明年，你就高一了，别让我们失望。

$Atlantis.$

---

## 作者：wangsz12 (赞：2)

没人写dijkstra的嘛。。。
思路都是一样的
### 比起spfa来说不需要特别的优化（spfa得用slf或者lll）
~~我觉得还是挺易懂的~~
```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
const int N=100001;
const int M=200001;
const int INF=0x7fffffff/2;

struct Edge{
    int to,next;
    int dis;
}edge[M*2];

struct Node{
    int node,dis;
    bool operator<(const Node &a) const{
        return dis>a.dis;
    }
};

int n,m,s,t1,t2;
int head[N];
int edge_num;
int dis[N];
bool done[N];
priority_queue<Node> q;

inline void Read(int &x){
    x=0;char c=getchar();int flag=1;
    while (c==' '||c=='\r'||c=='\n') c=getchar();
    if (c=='-') flag=-1;
        else x=c-48;
    while (isdigit(c=getchar())) x=x*10+c-48;
    x*=flag;
}

inline void Add_Edge(int from,int to,int dis){
    edge_num++;
    edge[edge_num].to=to;
    edge[edge_num].dis=dis;
    edge[edge_num].next=head[from];
    head[from]=edge_num;
}

void Dijkstra(int start){
    for (int i=1;i<=n;i++) dis[i]=INF;
    memset(done,0,sizeof done);
    dis[start]=0;
    q.push((Node){start,dis[start]});
    while (!q.empty()){
        Node x=q.top();q.pop();
        int u=x.node;
        if (done[u]) continue;
        done[u]=true;
        for (int i=head[u];i;i=edge[i].next){
            int to=edge[i].to;
            if (dis[to]>dis[u]+edge[i].dis){
                dis[to]=dis[u]+edge[i].dis;
                q.push((Node){to,dis[to]});
            }
        }
    }
}

int main(){
    Read(m);Read(n);Read(s);Read(t1);Read(t2);
    int x,y,d;
    for (int i=1;i<=m;i++){
        Read(x);Read(y);Read(d);
        Add_Edge(x,y,d);
        Add_Edge(y,x,d);
    }
    int ans1,ans2;
    Dijkstra(t1);
    ans1=dis[s]+dis[t2];
    Dijkstra(t2);
    ans2=dis[s]+dis[t1];
    printf("%d\n",min(ans1,ans2));
    return 0;
}
```

---

## 作者：FutureThx (赞：1)

为啥智颓总是给我推恶评呢……

---

### 题目大意

给出一个 $P$ 个节点， $C$ 条边的图，要求一条最短路径从 $PB$ 出发，路径上必须经过 $PA_1$ 与 $PA_2$ 两个节点。

### 题目解析

一道最短路的板题，这里用的堆优 + Dij，只需要求 $dis(PA_1,PA_2) + min(dis(PB,PA_1),dis(PB,PA_2))$  即可。

因为显然只有先走第一个再从第一个走第二个或者反过来这两种走法，那么代码也就很好写了。

### 代码

```cpp
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
#define MAX_N 100010
const int inf = 0x3f3f3f3f;
struct graph{
    vector<int> next;
    vector<int> nextw;
}node[MAX_N];
int dis[MAX_N],n,m,s;
bool vis[MAX_N];
void dijkstra(int v){
    priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
    q.push(make_pair(0,v));
    for(int i = 1;i <= n;i++)
       dis[i] = inf,vis[i] = 0;
    dis[v] = 0;
    while(!q.empty()){
        int u = q.top().second;
        q.pop();
        if(vis[u] == 1) 
           continue;
        vis[u] = 1;
        for(int i = 0;i < node[u].next.size();i++){
            if(dis[node[u].next[i]] > dis[u] + node[u].nextw[i]){
                dis[node[u].next[i]] = dis[u] + node[u].nextw[i];
                q.push(make_pair(dis[node[u].next[i]],node[u].next[i]));
            }
        }
    }
}
int main(){
    int a,b;
    cin >> m >> n >> s >> a >> b;
    for(int i = 1;i <= m;i++){
        int x,y,z;
        cin >> x >> y >> z;
        node[x].next.push_back(y);
        node[x].nextw.push_back(z);
        node[y].next.push_back(x);
        node[y].nextw.push_back(z);
    }
    dijkstra(a);
    int ans = dis[b];
    dijkstra(s);
    cout << ans + min(dis[a],dis[b]) << endl;
    return 0;
}
```


---

## 作者：黄汝鹏 (赞：1)

对于这道题，最好的方法是

# Dij+堆优化+分类讨论

首先，我们来分析一下题目，小牛~~妖~~要到达两个牧场，问最短路是多少。如果直接用裸的dij会TLE，所以这道题应该用dij+堆优化，我们所熟悉的最短路一般只有一个目标节点，这题有两个目标，我们可以总结出

p1:出发点

p2:目标1

p3:目标2

则可以推出三种路线

1.p1->p2

2.p2->p3

3.p1->p3

综上，我们可以跑两遍dij一次从p1出发，h[1][2]表示p1->p2,h[1][3]表示p1->p3,第二次从p2出发，h[2][3]表示p2->p3，最后在取h[1][2],h[1][3]的最小值再加上h[2][3]，还要记住数组开大点！

思路如上

来到代码部分
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
#include<iomanip>
#include<bits/stdc++.h>
using namespace std;
int const maxn=200000+10;
int n,m,num,v[maxn],p1,p2,p3;
int h[5][5];
long long d[maxn],head[maxn*2],a,b,c,ans;
priority_queue<pair<int,int> > q;
struct Edge
{
	int to,next;
	long long cost;
}edge[maxn*2];
void add_edge(int from,int to,long long cost)
{
	num++;
	edge[num].to=to;
	edge[num].cost=cost;
	edge[num].next=head[from];
	head[from]=num;
}
void dijkstra(int s)
{
	memset(d,0x3f,sizeof(d));
	memset(v,0,sizeof(v));
	d[s]=0;
	q.push(make_pair(0,s));
	while(q.size())
	{
		int u=q.top().second;
		q.pop();
		if(v[u]) continue;
		v[u]=1;
		for(int i=head[u];i;i=edge[i].next)
		{
			int to=edge[i].to;
			int cost=edge[i].cost;
			if(d[to]>d[u]+cost)
			{
				d[to]=d[u]+cost;
				q.push(make_pair(-d[to],to));
			}
		}
	}
}
int main()
{
	cin>>m>>n>>p1>>p2>>p3;
	for(int i=1;i<=m;i++)
	{
		scanf("%lld%lld%lld",&a,&b,&c);
		add_edge(a,b,c);
		add_edge(b,a,c);
	}
	//1:p1,2:p2,3:p3
	dijkstra(p1);
	h[1][2]=d[p2];
	h[1][3]=d[p3];
	dijkstra(p2);
	h[2][1]=d[p1];
	h[2][3]=d[p3];
	ans=min(h[1][2],h[1][3])+h[2][3];
	printf("%lld",ans);
	return 0;
}
```
题解到这里来到了尾声，最后本人提供一道思路差不多的题目，是这道题的升级版，也用dij加堆优化，附上连接(更多优质题解敬请关注个人博客[个人博客](https://www.luogu.org/blog/173239/))

[P4943 密室](https://www.luogu.org/problem/P4943)

望管理大大通过

---

## 作者：Enterpr1se (赞：0)

不知道第多少篇最短路题解了……  


------------
现在看到这种题可以直接无脑 Dijkstra 了，毕竟在这种没有负环的题里 SPFA 没啥好处 ~~，掘墓鞭尸也不太道德啊~~。  


------------
大部分同学对 Dijkstra 敬而远之的主要原因是运算符重载部分的问题，以下是运算符重载的代码：
```cpp
bool operator < (const node &that) const {
	return dis>/*这里就是大于号*/that.dis;
}
```
------------
补充一下为什么这里需要进行运算符重载，以及为什么重载运算符代码中的第 2 行使用了大于号：  
此处的 Dijkstra 使用了优先队列，而优先队列默认从大到小排序（最大的元素最先出队）并使用小于号 `<` 进行比较，因此我们需要重载这个运算符（结构体没有自带的比较方式），并且为了实现 Dijkstra“数值较小的元素先出队”的操作，我们需要将这个运算符反过来。  
事实上还有两种写法：  
### 强迫症方法
首先正常重载一个大于号：
```cpp
bool operator > (const node &that) const {
	return dis>that.dis;
}
```  
然后开优先队列的时候这么写：  
```cpp
priority_queue<node,vector<node>,greater<node> >;
```
就行了，效果一样（使用了优先队列的另一种排序方式）。  
我称其为强迫症方法，因为此处的大于号是真正意义上的“大于”。
### `pair` 写法
STL 大法好。关于这种写法可以自己去查文档。

------------

接下来是题目的主体：  
+ 显然，题目中 Bessie 走过的路径可以概括为两段（PB 到 PA1/PA2 和 PA1/PA2 到 PA2/PA1）  
+ 最优秀方案中 Bessie 需要走过的距离为  
$$\min [\textrm{dist(PB, PA1)},\textrm{dist(PB, PA2)}] + \textrm{dist(PA1, PA2)}$$
$\color{silver}\tiny\text{*由于是无向图，PA1 和 PA2 的距离只需要求一次，不存在两个方向距离不同的问题}$    
+ 其中 $\min$ 中的两项可以用任意单源最短路算法（不考虑复杂度情况下，本题中使用 Dijkstra）一次求出，PA1 和 PA2 的距离也可以如此得出

知道了这些，就可以直接上代码了：  
$\color{silver}\tiny\text{*楼主还是推荐大家自己写写，毕竟这题实在是太水了……}$   
```cpp
//Luogu-P3003
//Luogu @Enterpr1se (Userid 363523)
//@_Qijia(Userid 363524) AK IOI!
#include<cstdio>
#include<cstring>
#include<queue>
#define regint register int
#define regshort register short
#define _Qijia using
#define AK namespace
#define IOI std
_Qijia AK IOI;
int p,c,pb,pa1,pa2,ecnt,last[100005],ans1,dist[100005],flag[100005],u,v,w;
int min(int a,int b){
	return a<b?a:b;
}
struct node{//Dijkstra 所使用的结构体 
	int id,dis;
	bool operator < (const node &that) const {
		return dis>that.dis;
	}
};
struct edge{//链式前向星
	int to,val,prev;
} fig[400005];
inline void add(int s,int e,int v){//链式前向星（加边） 
	++ecnt;
	fig[ecnt]={e,v,last[s]};
	last[s]=ecnt;
	++ecnt;
	fig[ecnt]={s,v,last[e]};
	last[e]=ecnt;
	return;
}
inline void Dijkstra(int stt/*起点*/){//Dijkstra 模板
	//开变量，初始化 
	node curr,targ;
	priority_queue<node> qu;
	memset(flag,false,sizeof(flag));
	memset(dist,0x3f,sizeof(dist));
	dist[stt]=0;
	qu.push({stt,0});
	
	while(qu.size()){
		curr=qu.top();
		qu.pop();
		flag[curr.id]=true;//注意 Dijkstra 是出队打标记（SPFA 是进队打） 
		for(regint i=last[curr.id];i;i=fig[i].prev){
			targ={fig[i].to,dist[curr.id]+fig[i].val};
			if(flag[targ.id]) continue;
			if(dist[targ.id]>targ.dis){
				dist[targ.id]=targ.dis;
				qu.push(targ);
			}
		}	
	}
	return;
}
int main(){
	scanf("%d%d%d%d%d",&c,&p,&pb,&pa1,&pa2);
	for(regint i=1;i<=c;++i)
		scanf("%d%d%d",&u,&v,&w),add(u,v,w);
	Dijkstra(pb);//以 PB 为起点做单源最短路 
	if(dist[pa1]<dist[pa2]){//若 PA1 更近，Ln64 
		ans1=dist[pa1];//保存 PB 到 PA1 的距离 
		Dijkstra(pa1);//以 PA1 为起点做单源最短路（求 PA1 和 PA2 之间的距离） 
		printf("%d",ans1+dist[pa2]);
	}
	else{//若 PA2 更近 
		ans1=dist[pa2];//保存 PB 到 PA2 的距离 
		Dijkstra(pa2);//以 PA2 为起点做单源最短路（求 PA2 和 PA1 之间的距离）
		printf("%d",ans1+dist[pa1]);
	}//Ln73
	return 0;
}
```  
补充说明：  
由于在求出 PB 到 PA1/PA2 中近者的距离后要求的只是 PA1 和 PA2 之间的距离（无向图，PA1 到 PA2 的距离和 PA2 到 PA1 的距离始终相等），本程序的 Ln64 到 Ln73 部分还有另一种写法：  
```cpp
ans1=min(dist[pa1],dist[pa2]);
Dijkstra(pa1);
printf("%d",ans1+dist[pa2]);
```  
（这种做法明显更简洁，但是可能会逼死强迫症  
$\mathtt{Thanks}\text{ }\mathtt{for}\text{ }\mathtt{reading.}\text{ }$

---

## 作者：斜揽残箫 (赞：0)

## Description

一个 $n$ 个顶点，$m$ 条边的图，从 $s$ 点出发，到 $A,B$ 两点，求从 $s \to A \to B$ 小还是 $s \to B \to A$ 小。

$1 \leq n \leq 10 ^ 5,1 \leq m \leq 2 \times 10 ^ 5$。

话说这个题目是恶评吧，跑几遍最短路就出来了。

这边建议你写 $Dijkstra$，不要像我一样用 $spfa$ 被卡了，还加了个优化才过。

## Solution

首先分别求出 $s \to A$，$s \to B$，$A \to B$，$B \to A$ 的最短路。

分别设为 $M_1,M_2,M_3,M_4$。

之后判断 $M_1 + M_3$ 和 $M_2 + M_4$ 取小的那个就可以了，输出答案即可。

可能变量与代码中的不相同。

## Code

```cpp
#include <cstdio>
#include <cmath>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#define INF 0x3f3f3f3f
using namespace std;
const int Maxk = 400050;
int n,m,s,e1,e2;
int M1,M2,M3,M4,M5;
struct Node{
  int to,dis;
};
int w[Maxk],f[Maxk];
vector <Node> e[Maxk];
deque <int> qp;
inline int read()
{
	int s = 0, f = 0;char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
	return f ? -s : s;
}
void spfa(int x)
{
  while(qp.size()) qp.pop_front();
  memset(w,INF,sizeof w);
  memset(f,0,sizeof f);
  qp.push_front(x);
  f[x] = 1;
  w[x] = 0;
  while(!qp.empty()) {
    int now = qp.front();
    qp.pop_front();
    f[now] = 0;
    for(int i = 0;i < e[now].size();i ++) {
      int y = e[now][i].to;
      if(w[y] > w[now] + e[now][i].dis) {
        w[y] = w[now] + e[now][i].dis;
        if(!f[y]) {
          f[y] = 1;
          if(qp.empty()) {
            qp.push_front(y);
            continue;
          }
          int num = qp.front();
          if(w[y] < w[num]) qp.push_front(y);
          else qp.push_back(y);
        }
      }
    }
  }
  return;
}
signed main()
{
  scanf("%d%d%d%d%d",&m,&n,&s,&e1,&e2);
  for(int i = 1;i <= m;i ++) {
    int x = read(),y = read(),z = read();
    e[x].push_back((Node){y,z});
    e[y].push_back((Node){x,z});
  }
  spfa(s);
  M1 = w[e1],M2 = w[e2];
  spfa(e1);
  M3 = w[e2];
  spfa(e2);
  M4 = w[e1];
  int Ans = 0;
  //cout << M1 << " " << M2 << " " << M3 << " " << M4 << endl;
  Ans = (M1 + M3 < M2 + M4 ? M1 + M3 : M2 + M4);
  cout << Ans << endl;
  return 0;  
}


```

---

## 作者：BreakPlus (赞：0)

## $\text{Solution of Dijkstra algorithm} $

本题是一个裸的 ``Dijkstra`` 模板。今天来给大家讲讲 ``Dijkstra`` 算法。

可以说，``Dijkstra`` 是 ``SPFA`` 算法的优化。每次在队列中，取 $ dis_x$ 中最小的那个 $x$ 进行搜索，我们可以使用优先队列进行优化。

为了减少代码量，我们派上了好东西——``pair<int,int>`` 。它可以存储两个数值，并且两个 ``pair`` 相比较的时候比较第一关键字。我们可以把 $dis_x$ 放在前，$x$ 放在后，这样方便极了。

设 $\operatorname{DIS}(sta,fin)$ 表示从 $sta$ 到 $fin$ 的最短路径和，那么答案为：

$\min \{ \operatorname{DIS}(PB,PA1)+\operatorname{DIS}(PA_1,PA_2),\operatorname{DIS}(PB,PA2)+\operatorname{DIS}(PA_2,PA_1)\}$

Code:

```cpp
#include<cstdio>
#include<queue>
#include<iostream>
#include<cstring>
using namespace std;

typedef long long ll;
typedef pair<int,int> P;
#define maxn 200010
#define mkp(a,b) make_pair(a,b)
int m,n,u,v,w,st,st1,st2;
struct Edge{
    int to,w,next;
}edge[maxn<<1];
int head[maxn<<1],tot;
void add(int u,int v,int w){
    tot++;
    edge[tot].to=v;
    edge[tot].w=w;
    edge[tot].next=head[u];
    head[u]=tot;
}
int dis[maxn],vis[maxn];
int DIS(int sta,int fin){
    priority_queue<P,vector<P>,greater<P> >q;
    q.push(mkp(0,sta));
    memset(dis,0x3f,sizeof(dis)); memset(vis,0,sizeof(vis)); dis[sta]=0;
    while(!q.empty()){
        int x=q.top().second;
        q.pop();
        if(vis[x]) continue; vis[x]=1;
        for(register int i=head[x];i;i=edge[i].next){
            int tmp=edge[i].to,val=edge[i].w;
            if(dis[tmp]>dis[x]+val){
                dis[tmp]=dis[x]+val;
                if(!vis[tmp]) q.push(mkp(dis[tmp],tmp));
            }
        }
    }
    return dis[fin];
}
int minn(int a,int b){return a<b?a:b;}
int main(){
    scanf("%d%d%d%d%d",&m,&n,&st,&st1,&st2);
    for(register int i=1;i<=m;i++){
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w); add(v,u,w);
    }
    printf("%d\n",minn(DIS(st,st1)+DIS(st1,st2),DIS(st,st2)+DIS(st2,st1)));
    return 0;
}
```

---

## 作者：傅思维666 (赞：0)

## 题目大意：

给定一张图，和起始点，终点1终点2，问经过两个终点的路径和最短是多少。
## 题解：
裸的最短路问题不讲了。

这道题如果用裸的SPFA做会TLE，所以要加优化。

如果有像20分钟之前的我一样对SPFA算法优化一无所知的人，请移步我的一篇博客：

[优化SPFA基础知识传送门](https://www.cnblogs.com/fusiwei/p/11289019.html)

但是光知道怎么优化是不够的，我们还要就这个题想一想怎么写。

首先，这个题的源点不再是一，所以SPFA的时候要传参数。

其次，最后统计答案的时候要比较一下。

最后，拍一遍SPFA模板（SLF LLL优化版都可以）（本蒟蒻比较喜欢SLF），AC。

注意双向边的问题。

CODE:

```c++
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
int m,n,s,t1,t2;
int tot,to[400001],val[400001],nxt[400001],head[100001];
int dist[100001],v[100001];
void add(int x,int y,int z)
{
    to[++tot]=y;
    val[tot]=z;
    nxt[tot]=head[x];
    head[x]=tot;
}
void spfa(int start)
{
    memset(v,0,sizeof(v));
    memset(dist,0x3f,sizeof(dist));
    deque<int> q;
    dist[start]=0;
    v[start]=1;
    q.push_front(start);
    while(!q.empty())
    {
        int x=q.front();
        q.pop_front();
        v[x]=0;
        for(int i=head[x];i;i=nxt[i])
        {
            int y=to[i];
            if(dist[x]+val[i]<dist[y])
            {
                dist[y]=dist[x]+val[i];
                if(!v[y])
                {
                    if(!q.empty() && dist[y]<dist[q.front()])
                        q.push_front(y);
                    else
                        q.push_back(y);
                    v[y]=1;
                }
            }
        }
    }
}
int main()
{
    scanf("%d%d%d%d%d",&m,&n,&s,&t1,&t2);
    for(int i=1;i<=m;i++)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        add(x,y,z);
        add(y,x,z);
    }
    int ans1=0;
    int ans2=0;
    spfa(t1);
    ans1+=dist[t2]+dist[s];
    spfa(t2);
    ans2+=dist[t1]+dist[s];
    int ans=min(ans1,ans2);
    printf("%d",ans);
    return 0;
}
```



---

## 作者：老咸鱼了 (赞：0)

这题用SPFA会被卡要优化，建议用dijstra堆优化，我头一次交SPFA有两个点TLE了。因为题目说的从起点送2个苹果到PA_1和PA_2两个点，所以我们只需要跑一次起点的和一次PA_1或者PA_2点的，因为图示双向的，所以PA_1到PA_2和PA_2到PA_1的距离是相等的。
这里附上两张图理解![首先选择起点到两个苹果中最短的那个](http://ae01.alicdn.com/kf/HTB1thDXa1L2gK0jSZPh761hvXXad.png)

因为右边的1+2+2<左边的7所以我们选择先送去4

![因为图是双向的，所以我们从1到4的距离和从4到1的距离是一样的](http://ae01.alicdn.com/kf/HTB1WwTca4D1gK0jSZFK763JrVXaI.png)

图是双向的，我们很容易就可以看出来从1到4的距离和从4到1的距离是一样的，所以我们跑第二次的时候起点是PA_1或者PA_2都行，终点是另一个就行了。
如果不会dijstra堆优化的建议先去做[P4779 【模板】单源最短路径（标准版）](https://www.luogu.org/problemnew/show/P4779)

下面附上我的AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,e1,e2,cnt,dis[500050],dis1[500050],head[500050];
int ans;
bool vis[500050];
struct f{
	int to,next,dis;
}a[500050];
inline void add(int u,int v,int d)
{
	cnt++;
	a[cnt].to=v;
	a[cnt].dis=d;
	a[cnt].next=head[u];
	head[u]=cnt;
}
struct node{
	int dis,p;
	bool operator < (const node &x)const
	{
		return x.dis<dis;
	}
};
void spfa(int f)
{
	memset(vis,false,sizeof(vis));
	priority_queue<node>q;
	q.push((node){0,f});
	dis[f]=0;
	while(!q.empty())
	{
		node temp=q.top();
		q.pop();
		int u=temp.p;
		if(vis[u])
		continue;
		vis[u]=true;
		for(int i=head[u];i;i=a[i].next)
		{
			int t=a[i].to;
			if(dis[t]>a[i].dis+dis[u])
			{
				dis[t]=a[i].dis+dis[u];
				if(!vis[t])
				{
					q.push((node){dis[t],t});
				}
			}
		}
	}
}
int main()
{
	scanf("%d%d%d%d%d",&m,&n,&s,&e1,&e2);
	for(int i=1;i<=m;i++)
	{
		int u,v,d;
		scanf("%d%d%d",&u,&v,&d);
		add(u,v,d);
		add(v,u,d);
	}
	for(int i=1;i<=n;i++)
	{
		dis[i]=0x7fffffff;
	}
	spfa(s);
	ans+=min(dis[e1],dis[e2]);
	for(int i=1;i<=n;i++)
	{
		dis[i]=0x7fffffff;
	}
	spfa(e1);
	ans+=dis[e2];
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Zekrom (赞：0)

主要思路：  
两遍dijk  
1.第一次，求出s点到各个点的最短路  
2.第二次，求出e1点或e2点到其他点的最短路  
答案就是两个点的最小值  
提供一种记录各个d值的方法：即d数组跑最短路，di记录i点到其他点最短路  
这样就避免了写三遍dijk   
上代码   
```
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
#define N 100010
#define M 400010 
using namespace std;
int ans,n,m,d[N],d3[N],d1[N],d2[N],B,E,P,tot,head[N],s,e1,e2;
bool vis[N];
struct Edge{
	int v,next,val;
}edge[M];
inline int read(){
	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();
	}while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();
	}return x*f;
}
inline void add(int x,int y,int z){edge[++tot].v=y;edge[tot].next=head[x];edge[tot].val=z;head[x]=tot;}
void dijk(int s){
	priority_queue<pair<int,int> >q;
	memset(d,0x3f,sizeof(d));memset(vis,0,sizeof(vis));
	q.push(make_pair(0,s));d[s]=0;
	while(q.size()){
		int u=q.top().second;q.pop();
		if(vis[u])continue;vis[u]=1;
		for(int i=head[u];i;i=edge[i].next){
			int v=edge[i].v,z=edge[i].val;
			if(d[v]>d[u]+z){
				d[v]=d[u]+z;
				q.push(make_pair(-d[v],v)); 
			}
		}
	}
}
int main()
{
	m=read(),n=read(),s=read(),e1=read(),e2=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		add(x,y,z);add(y,x,z);
	} 
	dijk(s);for(int i=1;i<=n;i++)d1[i]=d[i];
	dijk(e1);for(int i=1;i<=n;i++)d2[i]=d[i];
	ans=min(d1[e1]+d2[e2],d1[e2]+d2[e2]);
	printf("%d\n",ans);
	return 0;
}


---

## 作者：zengxr (赞：0)

## 两遍堆优化dijkstra就好了

```cpp
#include<bits/stdc++.h>
using namespace std;
int pre[800001],now[800001],son[800001],dist[800001],V[800001],tot;
bool vis[800001];
int n,m,s;
void read(int &x) {
	char ch; bool ok;
	for(ok=0,ch=getchar(); !isdigit(ch); ch=getchar()) if(ch=='-') ok=1;
	for(x=0; isdigit(ch); x=x*10+ch-'0',ch=getchar()); if(ok) x=-x;
}
struct node{
    int dis;
    int pos;
    bool operator <( const node &x )const
    {
      return x.dis < dis;
    }
};
void put(int x,int y,int z)
{
  pre[++tot]=now[x];
  now[x]=tot;
  son[tot]=y;
  V[tot]=z;
}
void dijkstra()//堆优化
{
	memset(vis,0,sizeof(vis));
  priority_queue<node>q;
  for(int i=1;i<=n;i++)
    dist[i]=99999999;
  dist[s]=0;
  q.push((node){dist[s],s});
  while(!q.empty())
  {
    node temp=q.top();
    q.pop();
    int x=temp.pos;
    int d=temp.dis;
    if(vis[x])
    continue;
    vis[x]=1;
    for(int i=now[x];i;i=pre[i])
    {
      int y=son[i];
      if(dist[y]>dist[x]+V[i])
      {
        dist[y]=dist[x]+V[i];
        if(!vis[y])
        q.push((node){dist[y],y});
      }
    }
  }
}
int main()
{
	int t1,t2;
  read(m),read(n),read(s);
	read(t1),read(t2);
	int top=s;
  int x,y,z;
  for(int i=1;i<=m;i++)
    read(x),read(y),read(z),put(x,y,z),put(y,x,z);
		int ans1,ans2;
		s=t1;
     dijkstra();
     ans1=dist[top]+dist[t2];//算答案两遍，因为要取最优值
		 s=t2;
     dijkstra();
     ans2=dist[top]+dist[t1];
     printf("%d\n",min(ans1,ans2));//比较，输出

}

```


---

## 作者：VenusM1nT (赞：0)

这道题又双叒叕卡Spfa……

什么SLF、LLL的我都不会啊……

在这无尽的SpfaTLE中，唯有堆优化Dij神速的代码还有一丝温暖……

做法很简单……跑三次最短路，然后看看是pb-pa1-pa2短还是pb-pa2-pa1短即可

先给出Spfa的TLE（80 2773ms）代码

```cpp
#include<bits/stdc++.h>
using namespace std;
queue <int> q;
int cnt,fst[100005],nxt[400005],to[400005],w[400005];
int n,m,dis[100005][3],pb,pa1,pa2;
bool inq[100005];
void AddEdge(int u,int v,int c)
{
	to[++cnt]=v;
	nxt[cnt]=fst[u];
	fst[u]=cnt;
	w[cnt]=c;
}
void Spfa(int x,int id)
{
	q.push(x);
	dis[x][id]=0;
	inq[x]=1;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		inq[u]=0;
		for(int i=fst[u];i;i=nxt[i])
		{
			int v=to[i];
			if(dis[v][id]>dis[u][id]+w[i])
			{
				dis[v][id]=dis[u][id]+w[i];
				if(!inq[v])
				{
					q.push(v);
					inq[v]=1;
				}
			}
		}
	}
}
int main()
{
	memset(dis,60,sizeof(dis));
	scanf("%d %d %d %d %d",&m,&n,&pb,&pa1,&pa2);
	for(int i=1;i<=m;i++)
	{
		int x,y,z;
		scanf("%d %d %d",&x,&y,&z);
		AddEdge(x,y,z);
		AddEdge(y,x,z);
	}
	Spfa(pb,0);
	Spfa(pa1,1);
	Spfa(pa2,2);
	int tmp1=dis[pa1][0]+dis[pa2][1],tmp2=dis[pa2][0]+dis[pa1][2];
	printf("%d\n",min(tmp1,tmp2));
	return 0;
}
```

然后是堆优化Dij的AC（100 417ms）代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct Node
{
	int u,dis;
	bool operator < (const Node &x) const
	{
		return x.dis<dis;
	}
};
int cnt,fst[100005],nxt[400005],to[400005],w[400005];
int n,m,dis[100005][3],pb,pa1,pa2;
priority_queue <Node> q;
void AddEdge(int u,int v,int c)
{
	to[++cnt]=v;
	nxt[cnt]=fst[u];
	fst[u]=cnt;
	w[cnt]=c;
}
void Spfa(int x,int id)
{
	dis[x][id]=0;
	q.push((Node){x,0});
	while(!q.empty())
	{
		Node now=q.top();
		q.pop();
		int u=now.u,d=now.dis;
		if(d!=dis[u][id]) continue;
		for(int i=fst[u];i;i=nxt[i])
		{
			int v=to[i];
			if(dis[v][id]>dis[u][id]+w[i])
			{
				dis[v][id]=dis[u][id]+w[i];
				q.push((Node){v,dis[v][id]});
			}
		}
	}
}
int main()
{
	memset(dis,60,sizeof(dis));
	scanf("%d %d %d %d %d",&m,&n,&pb,&pa1,&pa2);
	for(int i=1;i<=m;i++)
	{
		int x,y,z;
		scanf("%d %d %d",&x,&y,&z);
		AddEdge(x,y,z);
		AddEdge(y,x,z);
	}
	Spfa(pb,0);
	Spfa(pa1,1);
	Spfa(pa2,2);
	int tmp1=dis[pa1][0]+dis[pa2][1],tmp2=dis[pa2][0]+dis[pa1][2];
	printf("%d\n",min(tmp1,tmp2));
	return 0;
}
```

最后

## 关于Spfa

### ·它死了 

（其实这题没有卡SLF和LLL已经是万幸了233）

---

## 作者：OIerAlbedo (赞：0)

# 题意
问一条最短路径，满足从 $ PB $ 出发，同时经过 $ PA_1 $ 与 $ PA_2 $。
# 基本思路
首先，我们知道路径一定是先到 $ PA_1 $ 再到 $ PA_2 $，或先到 $ PA_2 $ 再到 $ PA_1 $ 的，因为如果你不这么走，走的其他路是没有用处的，题目中要求最短，这样就不满足最短，也许有人会问，可以先回去，但是这样相对于直接从 $ PA_1 $ 到 $ PA_2 $ 或从 $ PA_2 $ 到 $ PA_1 $ 只会更长，不会更短。
# 实现
这就是最短路的板子题了，从我们从 $ PB $ ， $ PA_1 $ ， $ PA_2 $ 出发各跑一次最短路，就可以求出两条路径的值，在取较小值输出即可。
# 注意事项
这题 $ \text{Pascal} $ 基本不可用 $ \text{SPFA} $ 过，建议使用 $ \text{Dijkstra+} $堆优化。
# 代码
```pascal
Uses Math;
var hs,s,f1,f2,n,m,len:Longint;
    Used : array[0..100001] of Boolean;
    d : array[0..100001] of Longint;
    v,l,head,w:array[0..400001] of longint;
    h,ih:array[0..100001] of longint;
Procedure Swap(var o,o2: longint);
var buf:longint;
begin
 buf:=o; o:=o2; o2:=buf;
end;
procedure addvertex(a , b, c :longint);
begin
 inc(len);
 v[len]:=b;
 l[len]:=head[a];
 w[len]:=c;
 head[a]:=len;
end;
procedure Siftdown;
var cur,x:longint;
begin
 cur:=1;
 While cur shl 1<=hs do begin
 	x:=cur;
 	if (cur shl 1<=hs) and (d[h[x]] > d[h[cur shl 1]]) then x:=cur shl 1;
 	 if ((cur shl 1) + 1 <=hs) and (d[h[x]] > d[h[(cur shl 1) + 1]]) then
 	   x:=(cur shl 1) + 1;
 	  if cur = x then break else begin
 	  	Swap(ih[h[cur]],ih[h[x]]);
 	  	Swap(h[cur],h[x]);
 	  	cur:=x;
 	  end;
 end;
end;
Function getmin : longint;
begin
 If (hs <=0) or (d[h[1]] = maxlongint) then
  getmin:=-1 else begin
  	getmin:=h[1];
  	ih[h[1]]:=-1;
  	h[1]:=h[hs];
  	ih[h[1]]:=1;
  	h[hs]:=0;
  	dec(hs);
  	Siftdown;
  end;
end;
Procedure Siftup(x : Longint);
begin
 While  ( x > 1 ) and (d[h[x]] < d[h[x shr 1]]) do begin
 	Swap(ih[h[x]], ih[h[x shr 1]]);
 	Swap(h[x], h[x shr 1]);
 	x:=x shr 1;
 end;
end;
Function Dist ( a , b:longint) : longint;
var i,j:longint;
begin
 hs:=n;
 For i:=1 to n do begin
 	used[i]:=false;
 	d[i]:=MaxLongint;
 	ih[i]:=i;
 	h[i]:=i;
 end;
 Swap(h[a],h[1]);
 Swap(ih[a] , ih[1]);
 d[a]:=0;
 While Not Used[b] do begin
 	i:=GetMin;
 	if i = -1 then Break else begin
 		Used[i]:=true;
 		j:=head[i];
 		While j > 0 do begin
 		   If (Not Used[v[j]]) and (d[i] + w[j] < d[v[j]]) then begin
 		   	d[v[j]]:=d[i] + w[j];
 		   	Siftup(ih[v[j]]);
 		   end;
 		 j:=l[j];
 		end;
 	end;
 end;
 dist:=d[b];
end;
Function Path1 : longint;
begin
 Path1:= Dist(s, f1) + dist(f1, f2);
end;
Function Path2 : longint;
begin
 Path2:= Dist(s, f2) + Dist( f2 , f1 );
end;
Procedure reading;
var a,b,c,i:longint;
begin
 readln(m,n,s,f1,f2); len:=0;
 For i:=1 to m do begin
  readln(a,b,c);
  addvertex(a,b,c);
  addvertex(b,a,c);
 end;
 writeln(Min( Path1, Path2 ));
end;
begin
  reading;
end.    
```


---

