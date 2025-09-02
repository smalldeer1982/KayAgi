# [USACO09OPEN] Hide and Seek S

## 题目描述

Bessie is playing hide and seek (a game in which a number of players hide and a single player (the seeker) attempts to find them after which various penalties and rewards are assessed; much fun usually ensues).

She is trying to figure out in which of N (2 <= N <= 20,000) barns conveniently numbered 1..N she should hide. She knows that FJ (the seeker) starts out in barn 1. All the barns are connected by M (1 <= M <= 50,000) bidirectional paths with endpoints A\_i and B\_i (1 <= A\_i <= N; 1 <= B\_i <= N; A\_i != B\_i); it is possible to reach any barn from any other through the paths.

Bessie decides that it will be safest to hide in the barn that has the greatest distance from barn 1 (the distance between two barns is the smallest number of paths that one must traverse to get from one to the other). Help Bessie figure out the best barn in which to hide.

奶牛贝西和农夫约翰（FJ）玩捉迷藏，现在有N个谷仓，FJ开始在第一个谷仓，贝西为了不让FJ找到她，当然要藏在距离第一个谷仓最远的那个谷仓了。现在告诉你N个谷仓，和M个两两谷仓间的“无向边”。每两个仓谷间当然会有最短路径，现在要求距离第一个谷仓（FJ那里）最远的谷仓是哪个（所谓最远就是距离第一个谷仓最大的最短路径）？如有多个则输出编号最小的。以及求这最远距离是多少，和有几个这样的谷仓距离第一个谷仓那么远。


## 说明/提示

The farm layout is as follows:

 ![](https://cdn.luogu.com.cn/upload/pic/2815.png) 

Barns 4, 5, and 6 are all a distance of 2 from barn 1. We choose barn 4 because it has the smallest index.



这里谷仓4，5，6距离1号谷仓都是2，但是4编号最小所以输出4.因此最远距离是2且有3个谷仓，依次输出：2和3。 

感谢 wjcwinmt 的贡献翻译


## 样例 #1

### 输入

```
6 7 
3 6 
4 3 
3 2 
1 3 
1 2 
2 4 
5 2 
```

### 输出

```
4 2 3 
```

# 题解

## 作者：Eason_AC (赞：8)

## Update
- $\texttt{2020.9.13}$ 重新修改了一些格式和 $\texttt{LaTeX}$ 方面的问题，并修改了一些措辞，删除了一些废话。

## Content
给定一个有 $n$ 个点、$m$ 条边（每条边边权为 $1$）的无向图，求从 $1$ 号点到所有点的距离中：

- 最长最短路径长度最大的点的编号。
- 最长最短路径的长度。
- 有多少个点离 $1$ 号点的距离为最长最短路径的长度。

**数据范围：$2\leqslant n\leqslant 50000,1\leqslant m\leqslant 50000$。**
## Solution
可以发现这里每个边的边权是 $1$，所以先直接跑跑最短路就行了。
### Part 1 Dijkstra+堆优化
下面的代码展示的是堆优化+ $\texttt{dijkstra}$ 的过程，具体思路可以自己画个图加深理解：

```cpp
void dj() {
	memset(dis, 0x3f, sizeof(dis));
	dis[1] = 0;
	q.push(make_pair(0, 1));
	while(!q.empty()) {
		int x = q.top().second;
		q.pop();
		if(vis[x])	continue;
		vis[x] = 1;
		for(int i = h[x]; i; i = e[i].nxt) {
			int v = e[i].to, z = e[i].v;
			if(dis[v] > dis[x] + z) {
				dis[v] = dis[x] + z;
				q.push(make_pair(-dis[v], v));
			}
		}
	}
}
```

多说几句写堆优化+ $\texttt{dijkstra}$要注意的：

1. 一定要记得将 $dis$ 数组赋初值为 0x3f3f3f！（至于 vis 数组随便，因为它本来的初值都是0）
2. 不要直接用 ``memset(dis,0x3f3f3f3f,sizeof(dis))``！因为 memset 是按字节赋值的，不然你的程序会炸掉。
3. 判断是否遍历该点的时候一定要将之前未标记的点标记为 $1$！不然您的 while 循环会一直循环下去！

### Part 2 正解
好了，说了这么多，接下来要讲的是处理最大最短路径的问题。

其实最大最短路径的处理也很简单，首先遍历一遍找出最大最短路径的距离，再遍历看有这个最大最短路径的点的编号是多少，最后统计出这个最大最短路径的数量就可以了，完全暴力。

## Code
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <cmath>
#include <iostream>
#include <queue>
using namespace std;

int n, m, a, b, h[100007], cnt, dis[100007], vis[100007];
struct edge {
	int v, to, nxt;
}e[100007];
priority_queue<pair<int, int> > q;
void a_e(int u, int v) {
	e[++cnt] = (edge){1, v, h[u]}; h[u] = cnt;
	e[++cnt] = (edge){1, u, h[v]}; h[v] = cnt;
}
void dj() {
	memset(dis, 0x3f, sizeof(dis));
	dis[1] = 0;
	q.push(make_pair(0, 1));
	while(!q.empty()) {
		int x = q.top().second;
		q.pop();
		if(vis[x])	continue;
		vis[x] = 1;
		for(int i = h[x]; i; i = e[i].nxt) {
			int v = e[i].to, z = e[i].v;
			if(dis[v] > dis[x] + z) {
				dis[v] = dis[x] + z;
				q.push(make_pair(-dis[v], v));
			}
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; ++i) {
		scanf("%d%d", &a, &b);
		a_e(a, b);
	}
	dj();
	int maxi = 0, ans = 0;
	for(int i = 1; i <= n; ++i)
		maxi = max(maxi, dis[i]);
	for(int i = 1; i <= n; ++i)
		if(dis[i] == maxi) {
			printf("%d", i);
			break;
		}
	printf(" %d", maxi);
	for(int i = 1; i <= n; ++i)
		if(dis[i] == maxi)	ans++;
	printf(" %d", ans);
	return 0;
}
```

---

## 作者：zengxr (赞：6)

## 思路：
把边权值看成1，然后跑一遍最短路就好了
（这里用的是堆优化dijkstra）
## 代码：
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
void dijkstra()//最短路
{
  priority_queue<node>q;
  for(int i=1;i<=n;i++)
    dist[i]=9999999999;
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
  read(n),read(m);
	//read(s);
	s=1;
  int x,y,z;
  for(int i=1;i<=m;i++)
    read(x),read(y),put(x,y,1),put(y,x,1);
  dijkstra();

	int l=0;
	int ans=0;
	int cnt=0;
	for(int i = 1 ; i <= n ; i++){
  //统计答案
		if(dist[i] > l){
				l = dist[i];
				ans = i;
				cnt = 1;
		}
		else if(dist[i] == l)
				cnt++;
}
 printf("%d %d %d ",ans,l,cnt);

}

```


---

## 作者：peterwuyihong (赞：4)

# 震惊啊，为什么没人谁水SPFA？？！
跑一遍最短路再对答案$dis$数组处理即可
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,y;
int ver[100010],Next[100010],head[20010],tot=1;
bool v[100010];
int d[100010];
int q[111111],l=1,r;
void add(int x,int y)
{
	ver[++tot]=y;
	Next[tot]=head[x];
	head[x]=tot;
}
void SPFA()
{
	q[++r]=1;
	memset(d,0x3f,sizeof d);
	d[1]=0;
	while(l<=r)
	{
		int x=q[l++];
		v[x]=0;
		for(int i=head[x];i;i=Next[i])
		{
			int y=ver[i];
			if(d[y]>d[x]+1)
			{
				d[y]=d[x]+1;
				if(!v[y])q[++r]=y,v[y]=1;
			}
		}
	}
}
int main()
{
	scanf("%d",&n);
	scanf("%d",&m);
	while(m--)
	{
		scanf("%d %d",&x,&y);
		add(x,y);
		add(y,x);
	}
	SPFA();
	int ans1=0,ans2=0,ans3=0;
//	for(int i=1;i<=n;i++)
//	printf("%d ",d[i]);puts("");
	for(int i=1;i<=n;i++)
	ans1=max(ans1,d[i]);
	for(int i=1;i<=n;i++)
	if(d[i]==ans1)
	{
		if(!ans2)
		ans2=i;
		ans3++;
	}
	printf("%d %d %d",ans2,ans1,ans3);
}
```


---

## 作者：99NL (赞：4)

# 敲黑板
   我的博客地址
   
   [酸酸的笔记](https://www.luogu.org/blog/99NL/)

##  关于这道题目

  题目大意是询问我们从源点到哪个点的最短距离最长。
  
  ~~所以第一眼会被看成二分+spfa~~
  
  但是仔细分析的话，不难发现这些边权值都是一定的（即权值为1），所以咳咳，一种奇怪的bfs写法就孕育而生了。
  
##   算法流程

1.初始化所有点到源点的距离为n-1,然后用bfs对队头的所有出边进行遍历，用一个数组记录距离，当某个节点被第一次拓展到的时候，此时的距离就是源点到这个点的最短距离QAQ。

2.结束完第一步之后，剩下的就简单了，用一个max2记录最长距离。

3.最后for一遍找最长距离的点数。

完结撒花~~~~~

对了，对于这种USACO的题目，以下代码会得到十分的辛苦分，因为第一组数据都是样例。。。。（貌似是签到分？？）

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
cout<<"4 2 3";
	return 0;
}
```
下面是正解代码+注释

```cpp
#include <bits/stdc++.h>

using namespace std;
int n,m,step1=0;
struct node{
int to;
int last1;
int next1;
}map1[100005];//邻接表存图

int max1[20005];//距离源点的距离
bool vis[20005];//是否被扩展过

void add(int x,int y)
{
   map1[++step1].to=y;
   map1[step1].next1=map1[x].last1;
   map1[x].last1=step1;
}//添加一条边 
void bfs()//bfs大法好 
{
queue <pair<int,int> > q;//第一关键字是当前队头的序号，第二关键字是距离源点的距离 
q.push(make_pair(1,0));//先将源点入队 
max1[1]=0;
for (int a=2;a<=n;a++)
   max1[a]=n-1;//初始化
while (!q.empty())
{
   int d=q.front().second;
   int i=q.front().first;
   q.pop();
   vis[i]=1;
   for (int j=map1[i].last1;j;j=map1[j].next1)
   {
   	   if (vis[map1[j].to])//关键：每一个点只被扩展一次 
         continue;
      else
      {
      	 vis[map1[j].to]=1;
   	     max1[map1[j].to]=d+1;
         q.push(make_pair(map1[j].to,d+1));
      }
   }
}
}
int main() {
cin>>n>>m;
int x1,x2;
for (int a=1;a<=m;a++)
{
   cin>>x1>>x2;
   add(x1,x2);
   add(x2,x1);
}//由于是无向边所以要添加两次 
bfs();
int max2=0;
int s=0;
for (int a=2;a<=n;a++)
   if (max1[a]>max2)
   {
      s=a;
      max2=max1[a];
   }
int k=0;
cout<<s<<" "<<max2;//先输出距离最长最小点的序号和长度 
for (int a=2;a<=n;a++)
{
   if (max1[a]==max2)
      k++;
}
cout<<" "<<k;//输出最长距离的点的个数

    return 0;
}
```
跑的最慢的点只有28ms，快的飞起。。。

---

## 作者：Fuko_Ibuki (赞：4)

这个题的边权都为1,用不上最短路.考虑直接bfs,用一个结构体node记录现在到了那个点以及已经走的步数.那么可以先bfs一遍求出最短路,再bfs一遍求出符合最短路的点的数目以及这些点中编号最小的那一个.

我上来第一遍打这个的时候没有pop,然后队首永远是1,还卡了我10分钟.
```cpp
#include<bits/stdc++.h>
#define nico puts("niconiconi!")
namespace chtholly{
typedef long long ll;
#define rel register ll
#define rec register char
#define re0 register int
#define gc getchar
#define pc putchar
#define p32 pc(' ')
#define pl puts("")
inline int read(){
  re0 x=0,f=1;rec c=gc();
  for (;!isdigit(c);c=gc()) f^=c=='-';
  for (;isdigit(c);c=gc()) x=x*10+c-'0';
  return x*(f?1:-1);
  }
inline void read(ll &x){
  x=0;re0 f=1;rec c=gc();
  for (;!isdigit(c);c=gc()) f^=c=='-';
  for (;isdigit(c);c=gc()) x=x*10+c-'0';
  x*=f?1:-1;
  }
inline int write(int x){
  if (!x) return pc(48);
  if (x<0) pc('-'),x=-x;
  re0 bit[20],i,p=0;
  for (;x;x/=10) bit[++p]=x%10;
  for (i=p;i;--i) pc(bit[i]+48);
  }
inline char fuhao(){
  rec c=gc();
  for (;isspace(c);c=gc());
  return c;
  }
}
using namespace chtholly;//读入和输出优化
using namespace std;
#define to first//走到的点
#define step second//已经走的步数
typedef pair<int,int> node;//用一个pair代替结构体
const int karen=1e5;//听说范围要开大,开了1e5
int n=read(),m=read();
vector<int> lj[karen|10];
int p=n,ans,da,vis[karen|10];
//注意这三个变量分别是符合条件序号最小的点的编号,符合最长路径的点的数量,最长的路径.
void bfs()
{
queue<node> q;//队列
q.push(node(1,0));//把1放进去,并标识1已经走过了.
vis[1]=1;
for (;!q.empty();)
  {
  node u=q.front();q.pop();
  da=u.step;//为什么可以直接把step赋值给da呢?因为是bfs,显然最少的步数一定是递增的.
  for (int i:lj[u.to]) if (!vis[i])
    vis[i]=1,q.push(node(i,u.step+1));
  }//求出了最长的路径
q.push(node(1,0)),memset(vis,0,sizeof vis);
for (vis[1]=1;!q.empty();)//重复操作再来一遍
  {
  node u=q.front();q.pop();
  if (u.step==da) ++ans,p=min(p,u.to);//找到最短的路径等于大的所有点,并取其中的最小值.
  for (int i:lj[u.to]) if (!vis[i]) 
    vis[i]=1,q.push(node(i,u.step+1));
  }
}

int main()
{
for (;m--;)
  {
  re0 u=read(),v=read();
  lj[u].push_back(v);
  lj[v].push_back(u);
  }
bfs();
write(p),p32,write(da),p32,write(ans);//最后注意输出的顺序.
}//Thank you!
```

---

## 作者：LB_tq (赞：3)

# **Dijkstra+堆优化**

这道题可以使用最短路做，由于边权为一，也可以当做BFS.但是看数据范围，可以当做一道练习堆优化Dijkstra的模板。

pair在优先队列中默认按照第一维升序排序，所以top为距离最长的点；而我们要求最短路，所以要把边权的相反数插入队列

还有，由于正反都要存边，所以存边数组要开到2*m以上，不然会RE。。。
```


#include<iostream>
#include<cstdio>
#include<queue>//使用STL可以降低码量
#include<algorithm>
using namespace std;
struct node{
	int v;
	int t;
}w[100010];//node结构体存储图中的边
priority_queue<pair<int,int> >p;//pair的第一维存储边权，第二维存储边的序号(STL优先队列)
(pair在优先队列中默认以第一维升序，所以每次插入边权相反数取top,top是队首)
int dis[100010],n,s=0,m;//dis[i]存储从第一个点到第i个点的距离,s表示总边数
int vis[100010],f[100010];//f[]存储邻接表，vis[i]表示第i个点是否已经求得最短路
void add(int x,int y){
	s++;//边数
	w[s].v=y;
	w[s].t=f[x];
	f[x]=s;
}//由于点数限制，使用邻接表存图
void dijkstra(){
	dis[1]=0;
	p.push(make_pair(0,1));//插入第一个点
	int d,x;
	while(!p.empty()){
		d=p.top().second;
		p.pop();
		if(vis[d]!=0)
			continue;//如果已经求得最短路，则continue
		vis[d]=1;//标记
		for(int i=f[d];i!=0;i=w[i].t){
			x=w[i].v;
			if(dis[x]>dis[d]+1){
				dis[x]=dis[d]+1;
				p.push(make_pair(-dis[x],x));//插入相反数
			}//边权为一
		}
	}
}
int main(){
	cin>>n>>m;
	int u,v;
	for(int i=1;i<=m;i++){
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}//由于是无向图，所以正反都建边
	for(int i=1;i<=n;i++)
		dis[i]=0x3fffffff;//赋初值
	dijkstra();
	int x,y=-1,z=0;
	for(int i=1;i<=n;i++){
//		cout<<dis[i]<<" ";
		if(dis[i]==y)
			z++;
		if(dis[i]>y){
			x=i;
			y=dis[i];
			z=1;
		}//更新答案
	}
//	cout<<endl;
	cout<<x<<" "<<y<<" "<<z;
	return 0;
}
```


---

## 作者：Leaved_ (赞：1)

# 裸的单源最短路

标签 SPFA ？

~~不是死了吗~~

堆优化 dij
and
pair+链式前向星专属福利

双倍经验: [P3371](https://www.luogu.org/problem/P3371)、[P4779](https://www.luogu.org/problem/P4779)

我用了一个 pq 来存答案，解释在代码里

Code：
```cpp
#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define f(i,a,b) for(int (i)=(a);i<=(b);++i)
#define mk(a,b) make_pair((a),(b))
#define P pair<ll,ll>
#define s(x) scanf("%lld",&(x))
#define p(x) prllf("%lld ",(x))
#define fi first
#define se second

//define优化  -> 实际是手懒  

struct Node {
	ll to,next,disv;
}e[200010];

ll h[200010],n,m,tot;
ll dis[200010];

bool used[200010];

priority_queue <P,vector<P>,greater<P> > q;

void add_edge(ll u,ll v,ll w) {
	++tot;
	e[tot].to=v;
	e[tot].next=h[u];
	e[tot].disv=w;
	h[u]=tot;
}
//链式前向星存图 

void input() {
	s(n);s(m);
	f(i,1,m) {
		ll u,v;
		s(u);s(v);
		//把边权看做是 1 
		add_edge(u,v,1);
		add_edge(v,u,1);
		//这里要注意的是题目中说的是双向边，所以连两次 
	}
}

void Dijkstra() {
	memset(dis,0x3f,sizeof(dis));
	dis[1]=0;
	//初始化 and memset一定要初始化为 0x3f 
	q.push(mk(0,1));
	//make_pair 入队 
	while(!q.empty()) {
		ll u=q.top().se;
		q.pop();
		if(used[u]) continue;//如果已经更新过就不在更新 
		used[u]=true;
		for(ll i=h[u];i;i=e[i].next) {
			ll v=e[i].to;
			if(dis[v]>dis[u]+e[i].disv) {
				dis[v]=dis[u]+e[i].disv;//更新 
				q.push(mk(dis[v],v));//make_pair 入队 
			}
		}
	}
}

void output() {
	Dijkstra();
	priority_queue <ll,vector<ll>,greater<ll> >pq;//存答案 
	ll maxn=-INT_MAX;//最大值 
	f(i,1,n){
		if(dis[i]>maxn) maxn=dis[i];//更新maxn 
	}
	f(i,1,n) {
		if(dis[i]==maxn) pq.push(i);//输出最小点的编号 
	}
	ll now=pq.top();//最小点的编号 
	ll siz=pq.size();//点的个数 
	ll disv1=dis[now];//距离 
	cout<<now<<" "<<disv1<<" "<<siz<<endl;//输出 
}

int main() {
	input();
	output();
	//干净整洁的 int main() 
	return 0;
}
```


---

## 作者：清平乐 (赞：1)

### dij+priority_queue（没话说）
其实就是个裸题。。。

主要是介绍一个好东西
#### typedef pair<int,int>p;
这个东东很好用

相当于定义了一个结构体p；

p里有两个成员p.first和p.second，都是int型；

在优先队列中默认按照第一个成员排序，即q.first.


```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m,u,v,k=1,ans,place,cnt;
int head[20000+5],d[20000+5],in[20000+5];//in用来记录入度，万一有去不到的谷仓会对结果产生影响（虽然好像没有）
bool visit[20000+5];
typedef pair<int,int>p;//这是个好东西
priority_queue<p,vector<p>,greater<p> >q;

struct graph{
	int v,next;
}e[50000*2+5];

void input(int u,int v)
{
	e[k].next=head[u];
	e[k].v=v;
	head[u]=k++;
	in[v]++;
	return;//前向星
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		input(u,v);
		input(v,u);//无向图双向存
	}
	memset(d,0x3f,sizeof(d));
	d[1]=0;
	q.push(make_pair(0,1));
	while(!q.empty())
	{
		int now=q.top().second;
		q.pop();
		if(visit[now]) continue;
		visit[now]=true;
		for(int i=head[now];i!=0;i=e[i].next)
			if(d[e[i].v]>d[now]+1)
			{
				d[e[i].v]=d[now]+1;
				q.push(make_pair(d[e[i].v],e[i].v));
			}
	}	
	for(int i=2;i<=n;i++)
		if(d[i]>ans&&in[i]!=0)//in的作用在这里体现（没用）
		{
			ans=d[i];
			place=i;
		}
	for(int i=1;i<=n;i++)
		if(d[i]==ans) cnt++;
	printf("%d %d %d\n",place,ans,cnt);
	return 0;
}
```


---

## 作者：光阴且含笑 (赞：1)

~~好一头可爱的奶牛~~

首先读题，本题求的是最短路径的最大值，而不是最长路径~~我还在想着啥算法能求最长路~~，这不就很简单了嘛.Dijkstra跑一遍，求出FJ所在的一号谷仓到各个谷仓的最短路，然后遍历一遍求出最短路的最大值，再从n到1遍历一遍求出最小编号以及总数

AC代码如下：


```cpp
#include<bits/stdc++.h>
using namespace std;
struct Edge{
	int next;
	int to;
	int dis;
}edge[100005];
priority_queue<pair<int,int> > q;  //堆优化
int n,m,x,y,cnt=0,ans=0,id,dist=0;
int head[100005],d[20005],vis[20005];
void add(int from,int to,int dis){  //链式前向星存图
	edge[++cnt].next=head[from];
	edge[cnt].to=to;
	edge[cnt].dis=dis;
	head[from]=cnt;
}
void Dijkstra(){
	d[1]=0;
	q.push(make_pair(0,1));
	while(!q.empty()){
		int a=q.top().second;
		q.pop();
		if(vis[a]) continue;
		vis[a]=1;
		for(int i=head[a];i;i=edge[i].next)
			if(d[edge[i].to]>d[a]+edge[a].dis){
				d[edge[i].to]=d[a]+edge[a].dis;
				q.push(make_pair(-d[edge[i].to],edge[i].to));  //利用相反数把大根堆变为小根堆
			}
	}
	for(int i=1;i<=n;i++) dist=max(dist,d[i]);
	for(int i=n;i>=1;i--)
		if(d[i]==dist) ans++,id=i;
}
int main(){
	memset(vis,0,sizeof(vis));
	memset(d,0x3f,sizeof(d));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){  //输入，存边
		scanf("%d%d",&x,&y);
		add(x,y,1),add(y,x,1);
	}
	Dijkstra();
	printf("%d %d %d",id,dist,ans);
	return 0;
}
```


---

## 作者：HDWR (赞：1)

题意：

让你求这张图的最短路的最大值$\text{weight}$、最短路径长度为$\text{weight}$的**编号最小的**点，和最短路径长度为 $\text{weight}$ 一共有多少个点

方法：

对于前两个数，直接跑一遍 $\text{Dijkstra}$，扫一遍 $\text{dis}$ 数组并更新最大值就行了。

对于第三个数，我们开一个`map<int, int> mp`记录一下当前最短路径出现的次数，最后输出即可

跑的还挺快的 只有91ms

```cpp
/* -- Basic Headers -- */
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <queue>
#include <map>

/* -- Defined Functions -- */
#define For(a,x,y) for (int a = x; a <= y; ++a)
#define Forw(a,x,y) for (int a = x; a < y; ++a)
#define Bak(a,y,x) for (int a = y; a >= x; --a)

namespace FastIO {
    inline int getint() {
        int s = 0, x = 1;
        char ch = getchar();
        while (!isdigit(ch)) {
            if (ch == '-') x = -1;
            ch = getchar();
        }
        while (isdigit(ch)) {
            s = s * 10 + ch - '0';
            ch = getchar();
        }
        return s * x;
    }
    inline void __basic_putint(int x) {
        if (x < 0) {
            x = -x;
            putchar('-');
        }
        if (x >= 10) __basic_putint(x / 10);
        putchar(x % 10 + '0');
    }
    
    inline void putint(int x, char external) {
        __basic_putint(x);
        putchar(external);
    }
}

namespace Solution {
    const int MAXN = 20000 + 10;
    const int MAXM = 50000 + 10;
    
    struct Node {
        int nweight, now;
        
        Node() { nweight = now = 0; }
        
        bool operator < (const Node &that) const {
            return nweight > that.nweight;
        }
        // 并不想用pair，于是自己写了个出来
    };
    
    struct Edge {
        int now, weight, next;
    } edge[MAXM * 2]; // 双向边
    
    std::map<int, int> mp;
    
    int n, m, head[MAXN], dis[MAXN], cnt, ans, w = -233;
    
    inline void addEdge(int prev, int next, int weight) {
        edge[++cnt].now = next;
        edge[cnt].weight = weight;
        edge[cnt].next = head[prev];
        head[prev] = cnt;
    }
    
    inline Node NewNode(int nowWeight, int now) {
        Node tmp;
        tmp.nweight = nowWeight;
        tmp.now = now;
        return tmp;
    }
    // 并不想用构造函数
    
    inline void SPFA() {
    	// 看似是 SPFA，实则是 Dijkstra
        memset(dis, 0x7f, sizeof(dis));
        std::priority_queue<Node> q;
        q.push(NewNode(0, 1));
        dis[1] = 0;
        while (!q.empty()) {
            Node NowNode = q.top();
            q.pop();
            int now = NowNode.now;
            for (int e = head[now]; e; e = edge[e].next) {
                int to = edge[e].now;
                if (dis[to] > dis[now] + edge[e].weight) {
                    dis[to] = dis[now] + edge[e].weight;
                    q.push(NewNode(dis[to], to));
                }
            }
        }
    }
}

signed main() {
    using namespace Solution;
    using FastIO::getint;
    n = getint();
    m = getint();
    For (i, 1, m) {
        int prev = getint();
        int next = getint();
        int weight = 1;
        addEdge(prev, next, weight);
        addEdge(next, prev, weight);
    }
    SPFA();
    for (int i = 1; i <= n; ++i) {
        if (dis[i] == 0x7f7f7f7f) continue;
        ++mp[dis[i]];
        // 让对应的路径长度出现次数 + 1
        if (dis[i] > w) {
            w = dis[i];
            ans = i;
            // 更新答案
        }
    }
    printf("%d %d %d\n", ans, w, mp[w]);
    // ans 为点编号，w 为对应路径长度， 
    // mp[w] 为对应路径长度出现次数
    return 0;
}

```


---

## 作者：杨铠远 (赞：1)

###### 来水一篇堆优化迪杰斯特拉
```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
using namespace std;
const int N=7000;
inline int read()
{
	int res=0;
	char ch;
	while(isspace(ch=getchar()));
	do res=res*10+ch-'0';
	while(isdigit(ch=getchar()));
	return res;
}
const int inf=99999999;
int n,m,s,t,tot,x,y,d;
int dis[N];
struct pp{
	int to,nxt,dis,from;
}a[N<<2];
int head[N<<2];
inline void add(int u,int v,int di)
{
	a[++tot].nxt=head[u];
	head[u]=tot;
	a[tot].to=v;
	a[tot].dis=di;
	a[tot].from=u;
}

struct node{
	int u,d;
	bool operator<(const node&bb)const{
		return d>bb.d;
	}
};
inline void dij()
{
	for(int i=1;i<=n;i++)dis[i]=inf;
	dis[s]=0;
	priority_queue<node>q;
	q.push(node{s,0});
	while(!q.empty())
	{
		node aa=q.top();q.pop();
		int u=aa.u,d=aa.d;
		if(d!=dis[u])continue;
		for(int i=head[u];i;i=a[i].nxt)
		{
			int v=a[i].to;
			int w=a[i].dis;
			if(dis[u]+w<dis[v])
			{
				dis[v]=dis[u]+w;
				q.push((node){v,dis[v]
				});
			}
		}
	}
}
int main()
{
	n=read();m=read();s=read();t=read();
	while(m--){
		x=read();y=read();d=read();
		add(x,y,d);
		add(y,x,d);
	}
	dij();
	cout<<dis[t]<<endl;
	return 0;
}
```
先自己理解
有不懂的可以私信哟

---

## 作者：Law_Aias (赞：1)

# 一道SPFA的板子题

### 很简单的一道题，但不知道楼上楼下的题解怎么这么麻烦！！！


# 很暴力的思路：

建一张无向图，跑一边SPFA，再判断一下点权值的大小就完了

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>

#define maxn 52000
#define M 100010

using namespace std;

queue<int> q;

int t,n,m,ans,l,cnt;
int dis[maxn],head[maxn],f[maxn];
bool book[M];

struct edge{
	int to;
	int from;
	int data;
}e[maxn * 2 + 1];//无向图有双向边，所以要开两倍再加1

inline void add(int x,int y,int z){
	e[++t].from = y;
	e[t].to = head[x];
	e[t].data = z;
	head[x] = t;
}

inline void spfa(){
	memset(dis,0x3f3f3f,sizeof(dis));
	q.push(1);
	dis[1] = 0;
	while(!q.empty()){
		int u = q.front();
		q.pop();
		book[u] = 0;
		for(int i = head[u] ; i ; i = e[i].to){
			int v = e[i].from,w = e[i].data;
			if(dis[v] > dis[u] + w){
				dis[v] = dis[u] + w;
				f[v] = u;
				if(!book[v]){
					q.push(v);
					book[v] = 1;
				}
			}
		}
	}
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1 ; i <= m ; i++ ){
		int a,b;
		scanf("%d%d",&a,&b);
		add(a,b,1); add(b,a,1);//因为是无向图，所以建两次图
	}
	spfa();
	for(int i = 1 ; i <= n ; i++){
		if(dis[i] > l){
			l = dis[i];
			ans = i;
			cnt = 1;
		}
		else if(dis[i] == l)
			cnt++;
	}
	printf("%d %d %d ",ans,l,cnt);
	return 0;
}
```

~~## 哎！这道USACO的题居然不卡SPFA（逃~~

---

## 作者：熊崇文 (赞：0)

SPFA? 当然可以。

## 当然，你可以去[我的博客园](https://www.cnblogs.com/xiongchongwen/p/11857605.html)看（博客园中有无注释版的cpp）。

**SPFA适用范围：**

给定的图存在负权边（尽管这题没有负权边），这时类似Dijkstra等算法便没有了用武之地，而Bellman-Ford算法的复杂度又过高，SPFA算法便派上用场了。 我们约定有向加权图G不存在负权回路，即最短路径一定存在。当然，我们可以在执行该算法前做一次拓扑排序，以判断是否存在负权回路，但这不是我们讨论的重点。

**算法思想：**

我们用数组d记录每个结点的最短路径估计值，用邻接表来存储图G。我们采取的方法是动态逼近法：设立一个先进先出的队列用来保存待优化的结点，优化时每次取出队首结点u，并且用u点当前的最短路径估计值对离开u点所指向的结点v进行松弛操作，如果v点的最短路径估计值有所调整，且v点不在当前的队列中，就将v点放入队尾。这样不断从队列中取出结点来进行松弛操作，直至队列空为止。

**解释**在代码中。

那么，代码:

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<queue>
using namespace std;
int n,m,tot;
int head[20006],ver[500006],edge[500006],next[500006],d[20006];
queue<int> q;
bool v[20006];
int maxx=-2147483647,sum,where;
int read(){//快读
	int a=0,b=1;
	char ch=getchar();
	while((ch<'0'||ch>'9')&&(ch!='-')){
		ch=getchar();
	}
	if(ch=='-'){
		b=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		a=a*10+ch-'0';
		ch=getchar();
	}
	return a*b;
}
void add(int x,int y,int z){//建边
	ver[++tot]=y;
	edge[tot]=z;
	next[tot]=head[x];
	head[x]=tot;
}
void spfa(){
	memset(d,0x3f,sizeof(d));// dist数组
	memset(v,0,sizeof(v));// 是否在队列中
	d[1]=0;
	v[1]=1;
	q.push(1);
	while(q.size()){// 取出队头
		int x=q.front();
		q.pop();
		v[x]=0;// 扫描所有出边
		for(int i=head[x];i;i=next[i]){
			int y=ver[i],z=edge[i];
			if(d[y]>d[x]+z){// 更新，把新的二元组插入堆
				d[y]=d[x]+z;
				if(!v[y]){
					q.push(y);
					v[y]=1;
				}
			}
		}
	}
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=m;i++){// 构建邻接表
		int x,y;
		x=read(),y=read();
		// 无向图正反都需要建边
		add(x,y,1);// 假定距离为1
		add(y,x,1);// 假定距离为1
	}
	spfa();// 求单源最短路径
	for(int i=1;i<=n;i++){
		if(d[i]>maxx){// 查找最远距离
			maxx=d[i];
			where=i;// 记录最小的的一个位置
		}
	}
	printf("%d %d ",where,maxx);// 输出位置和最大值
	for(int i=1;i<=n;i++){// 统计与maxx距离相等的点的个数
		if(d[i]==maxx){
			sum++;
		}
	}
	printf("%d",sum);// 输出个数
	return 0;
}

```



---

## 作者：Caicz (赞：0)

### 最短路的模板题
拿到一道题，我们先看数据范围 **n<=20000,m<=50000**

很显然，Floyd O(n²)和 Bell-man O（mn） 算法绝对会超时，那么选择接只剩下 SPFA 和 Dij 了，但是 Dij 必须写优化，那么就选择了简单直接的 SPFA

```cpp
#include<bits/stdc++.h>
using namespace std;
struct eage{
	int v,last,w;
}e[100005];//图是无向图，所以数组开双倍
int k=1,head[20005];
int n,m,d[20005],vis[20005],ans1,ans2,ans3;

void add(int u,int v,int w)
{
	e[k].last=head[u];
	e[k].w=w;
	e[k].v=v;
	head[u]=k++;
}
```
这上面就是标准的链表存图
```
int main()
{
	cin>>n>>m;
	memset(head,-1,sizeof(head));
	memset(d,0x3f,sizeof(d));
```
初始化
```
	for(int i=1;i<=m;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		add(a,b,1);
		add(b,a,1);
	}
	queue<int>q;
	q.push(1);
	d[1]=0;
	vis[1]=true;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		vis[u]=false;
		for(int i=head[u];i!=-1;i=e[i].last)
		{
			int v=e[i].v,w=e[i].w;
			if(d[v]>d[u]+w)
			{
				d[v]=d[u]+w;
				q.push(v);
			}
		}
	}
```
上面就是标准的SPFA模板，但是这里少打了某些东西（但是还是AK了，数据有点水2333）
```
	for(int i=1;i<=n;i++)
		if(d[i]>ans2)
		{
			ans2=d[i];
			ans1=i;
		}
	for(int i=1;i<=n;i++)
	{
		if(d[i]==ans2)
			ans3++;
	}
	cout<<ans1<<" "<<ans2<<" "<<ans3<<endl;
	return 0;
}
```
输出注意一下不是一般最短路问题的输出

---

## 作者：asuldb (赞：0)

```cpp
//dijkstra+heap
//看没人dij赶快水一发 
//也没什么好说的了，就是上版子好了 
//这里采用的是优先队列和pair，毕竟手写堆或重载运算符对我这个蒟蒻不太友好 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#pragma GCC optimize(3)
using namespace std;
#define maxw 50000*2//无向图前向星开两倍 
#define maxn 20001
#define re register
#define inf 99999999
struct node
{
    int u,v,w,nxt;
}edge[maxw];
int n,m,num=1;
bool f[maxn];
int d[maxn],head[maxn];
typedef pair<int,int> pii;//一个pair，用来放从源点到指定点的距离和指定点
priority_queue<pii,vector<pii>,greater<pii> > q;// 一个小根堆 
inline void read(int &x)
{
    char c=getchar();
    x=0;
    while(c<'0'||c>'9') c=getchar();
    while(c>='0'&&c<='9')
    {
        x=x*10+c-48;
        c=getchar();
    }
}
inline void add_edge(int x,int y,int z)
{
    edge[num].u=x;
    edge[num].v=y;
    edge[num].w=z;
    edge[num].nxt=head[x];
    head[x]=num;
    num++;
}
inline void dijkstra(int s)
{
    for(re int i=1;i<=n;i++)
      d[i]=inf;
    d[s]=0;
    q.push(make_pair(d[s],s));//make_pair(x,y),生成pair对象入队 
    while(!q.empty())
    {
        pii mind=q.top();
        q.pop();
        int k=mind.second;
        if(f[k]) continue;
        else
        {
            f[k]=true;
            for(re int i=head[k];i!=-1;i=edge[i].nxt)
            if(d[edge[i].v]>edge[i].w+d[k])
            {
                d[edge[i].v]=edge[i].w+d[k];//松弛操作 
                q.push(make_pair(d[edge[i].v],edge[i].v));//新状态入队 
            }
        }
    }
}
int main()
{
    read(n);
    read(m);
    for(re int i=1;i<=n;i++)
      head[i]=-1;
    int xx,yy;
    for(re int i=1;i<=m;i++)
    {
        read(xx);
        read(yy);
        add_edge(xx,yy,1);
        add_edge(yy,xx,1);
    }
    dijkstra(1);
    int ans=-1,point;
    for(re int i=1;i<=n;i++)
     if(ans<d[i])
     {
         point=i;
         ans=d[i];
     }
    int tot=0;
    for(re int i=1;i<=n;i++)
    if(d[i]==ans) tot++;
    cout<<point<<" "<<ans<<" "<<tot<<endl;
    return 0;
}
```

---

## 作者：zy小可爱ღ (赞：0)

典型的最短路，而且只要再加一点点操作，就能得到答案

所以可以直接套模板

具体看程序：：：





```cpp
#include<cstdio>
#include<queue>//队列专属头文件
#include<algorithm>
using namespace std;
const int N=100005;
int a[N];
int n,m,l,sum,ans;
int d1[N],t[N],head1[N],next1[N],w1[N],adj1[N],k1;
bool f1[N];
queue<int> q1;//比较喜欢定义全局变量
void add(int u,int v){//加边操作，因为每条边权值为1，就不用第三个变量了
    next1[++k1]=head1[u];
    head1[u]=k1;
    w1[k1]=1;//如果不是1，就把一换成变量t（自己定义）
    adj1[k1]=v;
}
void spfa(int s,int e){//SPFA,最短路模板
    for(int i=1;i<=n;i++)
        d1[i]=1<<30;//赋无限大
    d1[s] =0;
    q1.push(s);
    f1[s]=true ;
    while(!q1.empty()){
        int top1=q1.front() ;
        q1.pop() ;//出队
        f1[top1]=false;
        for(int j=head1[top1];j!=0;j=next1[j]){
            if(d1[adj1[j]]>d1[top1]+w1[j]){//松弛操作
                t[adj1[j]]++;
                d1[adj1[j]]=d1[top1]+w1[j] ;
                if(!f1[adj1[j]]){
                    q1.push(adj1[j]);
                    f1[adj1[j]]=true;
                }
            }    
        }            
    }
}
int main(){
    //freopen("hideseek.in","r",stdin);
    //freopen("hideseek.out","w",stdout);不要在意。。。
    scanf("%d%d",&n,&m);//读入
    for(int i=1;i<=m;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        add(x,y);
        add(y,x);//加边操作，因为是无向图，要加两次
    }
    spfa(1,n);//调用
    for(int i=1;i<=n;i++){
        if(d1[i]>l){//如果出现了比现在大的点，就交换
            l=d1[i];
            ans=i;
            sum=1;
        }
        else{
            if(d1[i]==l){//一样就加
                sum++;
            }
        }
    }
    printf("%d %d %d\n",ans,l,sum);//输出
    return 0;
}
不用数组模拟队列其实蛮麻烦的，我也只是套用模板，懒得改了，比才是现场写还是要写自己有把握的
```

---

## 作者：weige233 (赞：0)

##SPFA算法题解，主要在输出上，简单的最短路

###贴贴贴题解

```cpp
#include<bits/stdc++.h> //万能表头大法好ovo 
using namespace std;
int dui[100001],dis[100001],h[100001],head=1,tail=1,num=0,maxxxx=0,maxx=0,maxxx=0;
bool b[100001];
struct pre
{
    int x;
    int y;
    int w;
}a[100001];
void add(int u,int v,int l)
{
    a[++num].y=v;    
    a[num].w=l;
    a[num].x=h[u];
    h[u]=num;
}
int main()
{
    int n,m,l1,l2,k,l;
    cin>>n>>m;
    for(int i=1; i<=m; i++)
     {
         cin>>l1>>l2;
         add(l1,l2,1);
         add(l2,l1,1); //双向路 
     }
    for(int i=1; i<=n; i++)
     dis[i]=0xfffff; //定义无限大 
    memset(b,0,sizeof(b));   
    dis[1]=0; b[1]=1; dui[tail++]=1; //队列初始化 
    while(head<tail)   
    {
        k=dui[head++]; 
        b[k]=0;       //出队 
        for(int i=h[k]; i; i=a[i].x)    
         {
             l=a[i].y;
             if(dis[k]+a[i].w<dis[l])    
              {                           //松弛大法 
                  dis[l]=dis[k]+a[i].w;
                  if(!b[l])
                  {
                      b[l]=1;
                      dui[tail++]=l;    //进队 
                  }
              }
         }
    }
    for(int i=n; i>=1; i--)
     if(dis[i]>=maxxxx)    //判断**距离最远**的谷仓
     {
      maxxxx=dis[i];   //记录**最远距离** 
      maxx=i;       //记录**编号** 
     } 
    for(int i=1; i<=n; i++) 
     if(dis[i]==maxxxx)  //判断有多少距离相同 
      maxxx++;
    cout<<maxx<<" "<<maxxxx<<" "<<maxxx; 
}
```

---

## 作者：winmt (赞：0)

我来发第一个题解吧。

这题的话，倒着跑一遍边权为1的SPFA（dij+heap也OK），然后一直不断更新题目要求的那三个值就AC了，裸最短路啊～

【C++ Code】


```cpp
#include<cstdio>
#include<cstring>
using namespace std;
struct edge{
    int to,next,v;
}e[200001];
int head[50001];
int dis[50001];
int q[500001];
bool mrk[50001];
int n,m,cnt,t,w=1,mx=0,rep,num;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
inline void ins(int u,int v,int w)
{
    e[++cnt].v=w;
    e[cnt].to=v;
    e[cnt].next=head[u];
    head[u]=cnt;
}
inline void insert(int u,int v,int w)
{
    ins(u,v,w);
    ins(v,u,w);
}
inline void spfa()
{
    memset(dis,127/3,sizeof(dis));
    q[1]=1;dis[1]=0;mrk[1]=1;
    while (t<w)
    {
        int now=q[++t];
        for (int i=head[now];i;i=e[i].next)
          if (dis[e[i].to]>dis[now]+e[i].v)
          {
              dis[e[i].to]=dis[now]+e[i].v;
              if (!mrk[e[i].to])
              {
                  q[++w]=e[i].to;
                  mrk[e[i].to]=1;
              }
          }
        mrk[now]=0;
    }
}
int main()
{
    n=read();
    m=read();
    for (int i=1;i<=m;i++)
      {
          int x=read(),y=read();
          insert(x,y,1);
      }
    spfa();
    for (int i=n;i>=2;i--)
    {
        if (dis[i]>mx)
        {
            mx=dis[i];
            num=i;
            rep=1;
        }else
        if (dis[i]==mx)
        {
            num=i;
            rep++;
        }
    }
    printf("%d %d %d\n",num,mx,rep);
    return 0;
}
```

---

## 作者：kfhkx (赞：0)

看到没有pascal，就来一波吧~

其实这题就是来练习最短路的

p党想看最短路板子朝这里看哦~

跑一遍最短路，统计一下答案就行了

所以刚开始为了方便，打了个裸的dijkstra

P2951.pas
------------
```pascal
var
        n,m,i,j,tot,v,minn,head,x,y,ans,bns,cns:longint;
        he,ne,t,w,dis:array[0..1000000] of longint;
        p:array[0..1000000] of boolean;
procedure link(x,y:longint);
begin
        inc(tot);
        ne[tot]:=he[x];
        he[x]:=tot;
        t[tot]:=y;
        w[tot]:=1;
end;
begin
        readln(n,m);
        for i:=1 to m do begin
                read(x,y);
                link(x,y);
                link(y,x);
        end;
        for i:=2 to n do dis[i]:=maxlongint;
        head:=1;
        while not p[head] do begin
                p[head]:=true;
                v:=he[head];
                while v>0 do begin
                        if (not p[t[v]]) and (dis[t[v]]>dis[head]+w[v]) then
                         dis[t[v]]:=dis[head]+w[v];
                        v:=ne[v];
                end;
                minn:=maxlongint;
                for i:=1 to n do if (not p[i]) and (minn>dis[i]) then begin
                        minn:=dis[i];
                        head:=i;
                end;
        end;
        for i:=n downto 1 do begin
                if ans<=dis[i] then begin
                        ans:=dis[i];
                        bns:=i;
                end;
        end;
        for i:=1 to n do if dis[i]=ans then inc(cns);
        write(bns,' ',ans,' ',cns);
end.
```
结果t了两个点

所以我就老实的打了个堆优化的dijkstra上去

P2951（1）.pas
```pascal
var
        n,m,s,i,tot,bj,v,x,y,z,head:longint;
        ans,bns,cns:int64;
        he,ne,t,w,cj,num:array[0..4000010] of longint;
        dis,heap:array[0..4000010] of int64;
function max(x,y:int64):int64;
begin
        if x>y then exit(x) else exit(y);
end;
procedure swap(var x,y:int64);
var
        t:int64;
begin
        t:=x;
        x:=y;
        y:=t;
end;
procedure swap1(var x,y:longint);
var
        t:longint;
begin
        t:=x;
        x:=y;
        y:=t;
end;
procedure link(x,y,z:longint);
begin
        inc(tot);
        ne[tot]:=he[x];
        he[x]:=tot;
        t[tot]:=y;
        w[tot]:=z;
end;
procedure insert(a,x:longint);
var
        i:longint;
begin
        if cj[x]<>0 then begin
                heap[cj[x]]:=a;
                i:=cj[x];
        end else begin
                inc(heap[0]);
                heap[heap[0]]:=a;
                num[heap[0]]:=x;
                i:=heap[0];
                cj[x]:=heap[0];
        end;
        while (i>>1>0) and (heap[i]<heap[i>>1]) do begin
                swap1(cj[num[i]],cj[num[i>>1]]);
                swap(heap[i],heap[i>>1]);
                swap1(num[i],num[i>>1]);
                i:=i>>1;
        end;
end;
procedure del;
var
        mid,i:longint;
begin
        cj[num[1]]:=0;
        heap[1]:=heap[heap[0]];
        num[1]:=num[heap[0]];
        dec(heap[0]);
        i:=1;
        if (heap[i<<1]<heap[i<<1+1]) or (i=heap[0]) then mid:=i<<1 else mid:=i<<1+1;
        while (mid<=heap[0]) and (heap[mid]<heap[i]) do begin
                swap1(cj[num[i]],cj[num[mid]]);
                swap(heap[i],heap[mid]);
                swap1(num[i],num[mid]);
                i:=mid;
                if (heap[i<<1]<heap[i<<1+1]) or (i<<1=heap[0]) then mid:=i<<1 else mid:=i<<1+1;
        end;
end;
begin
        readln(n,m);
        for i:=1 to m do begin
                readln(x,y);
                link(x,y,1);
                link(y,x,1);
        end;
        for i:=1 to n do dis[i]:=maxlongint;
        dis[1]:=0;
        head:=1;
        heap[0]:=1;
        heap[1]:=0;
        num[1]:=1;
        while heap[0]<>0 do begin
                v:=he[head];
                while v<>0 do begin
                        if dis[t[v]]>dis[head]+w[v] then begin
                                dis[t[v]]:=dis[head]+w[v];
                                ans:=max(dis[t[v]],ans);
                                insert(dis[t[v]],t[v]);
                        end;
                        v:=ne[v];
                end;
                del;
                head:=num[1];
        end;
         for i:=1 to n do if dis[i]=ans then begin
                inc(cns);
                if bj=0 then begin
                        bns:=i;
                        bj:=1;
                end;
        end;
        write(bns,' ',ans,' ',cns);
end.
```
72ms

但后来发现裸的spfa竟然可以过，所以又打了个裸的spfa

P2951（2）.pas
```pascal
var
        n,m,i,v,x,y,bj,tot,ans,bns,cns,head,tail:longint;
        he,ne,t,w,dis,q:array[0..4000000] of longint;
function max(x,y:longint):longint;
begin
        if x>y then exit(x) else exit(y);
end;
procedure link(x,y:longint);
begin
        inc(tot);
        ne[tot]:=he[x];
        he[x]:=tot;
        t[tot]:=y;
        w[tot]:=1;
end;
begin
        readln(n,m);
        for i:=1 to m do begin
                read(x,y);
                link(x,y);
                link(y,x);
        end;
        for i:=2 to n do dis[i]:=maxlongint;
        tail:=1;
        q[1]:=1;
        repeat
                inc(head);
                v:=he[q[head]];
                while v>0 do begin
                        if dis[t[v]]>dis[q[head]]+w[v] then begin
                                dis[t[v]]:=dis[q[head]]+w[v];
                                ans:=max(ans,dis[t[v]]);
                                inc(tail);
                                q[tail]:=t[v];
                        end;
                        v:=ne[v];

                end;
        until head>tail;
        for i:=1 to n do begin
                if dis[i]=ans then begin
                        inc(cns);
                        if bj=0 then begin
                                bns:=i;
                                bj:=1;
                        end;
                end;
        end;
        write(bns,' ',ans,' ',cns);
end.
```
79ms


---

