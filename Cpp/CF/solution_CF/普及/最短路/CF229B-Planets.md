# Planets

## 题目描述

## 题面
在宇宙里有 $n$  个星球，分别编号为 $1,2,...,n$  。Jack现在在 $1$  号星球上，他要去 $n$  号星球。已知一些星球之间有双向的传送通道，Jack可以通过这些传送通道移动。每次传送需要一些时间，在不同的星球之间传送也可能需要不同时间。

当有其他人在使用这个星球的传送通道时，Jack无法离开这个星球。比如，如果有人在 $t$  时刻使用通道，那Jack只能在 $t+1$  时刻离开（如果t+1时刻没有人在使用通道）。

现在，Jack想请你计算他最早可以在哪个时刻到达 $n$  号星球。Jack在0时刻出发。

## 样例 #1

### 输入

```
4 6
1 2 2
1 3 3
1 4 8
2 3 4
2 4 5
3 4 3
0
1 3
2 3 4
0
```

### 输出

```
7
```

## 样例 #2

### 输入

```
3 1
1 2 3
0
1 3
0
```

### 输出

```
-1
```

# 题解

## 作者：雨季 (赞：6)

# 题解
很裸的最短路，按照题目要求，应该排队的时候排队即可。  
**注意**：  
① $INF$ 赋值 $1e9$ 不够大，可以赋 $2e9$。    
② 计算所需要等待的时间时 `d=dis[x];while(mp[x][d]) d++;`要放在循环的外面，不然会TLE。。。  

# 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#include<queue>
using namespace std;
inline int read() {
	int t=0,w=1;
	char ch=0;
	while(!isdigit(ch)) {if(ch=='-') w=-1;ch=getchar();}
	while(isdigit(ch)) t=(t<<1)+(t<<3)+ch-'0',ch=getchar();
	return t*w;
}
#define N 100005

int n,m;
map<int,bool>mp[N];

struct node {
	int v,c,nex;
}e[N<<1];
int tot,h[N];
void add(int u,int v,int c) {
	e[++tot].v=v,e[tot].c=c,e[tot].nex=h[u],h[u]=tot;
}

int dis[N];
bool vis[N];
deque<int>q;
void spfa() {
	for(int i=1;i<=n;++i) dis[i]=2e9;
	q.push_back(1);
	dis[1]=0;
	int x,xx,d;
	while(!q.empty()) {
		x=q.front();
		q.pop_front();
		vis[x]=0;
		d=dis[x];
		while(mp[x][d]) d++;
		for(int i=h[x];i;i=e[i].nex) {
			xx=e[i].v;
			if(dis[xx]>d+e[i].c) {
				dis[xx]=d+e[i].c;
				if(!vis[xx]) {
					vis[xx]=1;
					if(q.empty()||dis[xx]>dis[q.front()]) q.push_back(xx);
					else q.push_front(xx);
				}
			}
		}
	}
}

int main()
{
	n=read(),m=read();
	int u,v,c;
	for(int i=1;i<=m;++i) u=read(),v=read(),c=read(),add(u,v,c),add(v,u,c);
	for(int i=1;i<=n;++i) {
		c=read();
		for(int j=1;j<=c;++j) u=read(),mp[i][u]=1;
	}
	spfa();
	if(dis[n]==2e9) printf("-1\n");
	else printf("%d\n",dis[n]);
	return 0;
}
```

---

## 作者：wangyibo201026 (赞：4)

## 题意

给你一个图，有 $n$ 个点 $m$ 边，对于每个点 $i$ 都有 $k_i$ 个限制，因此在某些时候连向 $i$ 的边就不能使用。请问你 $1$ 到 $n$ 的最短路。

## 思路

直接 SPFA + map 水过。

我们可以这样想，在每个点中如果有限制的话，那么我们在 SPFA 的时候就可以一次一次判断当前是否能够松弛，如果能，就松弛，如果不能，就直接最短路 $+ 1$。因此，伪代码如下:

```cpp
while(如果不能行){
  跳到下一个时间
}
  ......
```

那么，问题就在我们如何判断行不行。

这时，依靠输入格式和数据范围，我们自然可以想到 vector，依靠查找一个元素在不在序列中，我们又自然想到了 lower_bound。

所以，我们可以利用 map 来解决这两个问题合并的问题（友情提示：map 常数过大，所以，你知道的）。

我们定义一个 map 数组，用来标记第 $i$ 个点不能用的所有时刻，如下（$N$ 表示点的个数）：

```cpp
map<int, bool> book[N];
......
```

这样，上面那个问题就可以轻松解决，这里代码片段就不给了。

## 问题

那么，这里给出一点可能出错的问题。有人的代码片段可能是这么写的：

```cpp
while(book[点][dis[点]]){
  dis[点]++;
}
```

其中点代表我们从队列中取出来的点。

这里的错误连样例都检查不出来，所以提一下。

为什么不对，因为最短路的修改是基于连出去的点，而从队列中取出来的点是已经经过松弛的点了，但是你现在又修改了，所以才会不对。

## 代码

代码来咯：

```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

inline int read() {     // 卡常的快读
	int x = 0, f = 1;
  char ch = getchar();
	while(ch < '0' || ch > '9'){
    if(ch == '-'){
      f = -1;
    }
    ch = getchar();
  }
	while(ch >= '0' && ch <= '9'){
    x = x * 10 + ch - 48;
    ch = getchar();
  }
	return x * f;
}

const int N = 3e5 + 5;

map<int, bool> book[N];

int n, m, s;
int dis[N];
bool vis[N];

int tot, head[N];

struct node{
	int to, w, next;
}edges[N];

void add(int u, int v, int w){
	tot++;
	edges[tot].to = v;
	edges[tot].w = w;
	edges[tot].next = head[u];
	head[u] = tot;
}

void SPFA(int s){
	queue<int> q;
	for(int i = 1; i <= n; i++){
		dis[i] = 1e18;    // 这里要设大一点
	}
	dis[s] = 0;
	q.push(s);
	vis[s] = true;
	while(!q.empty()){
		int x = q.front();
		q.pop();
		vis[x] = false;
		int tmp = dis[x];
		while(book[x][tmp]){   // 进行判断
			tmp++;     // 注意这里要新建一个变量 ++
		}
		for(int i = head[x]; i; i = edges[i].next){	
			if(tmp + edges[i].w < dis[edges[i].to]){
				dis[edges[i].to] = tmp + edges[i].w;
				if(!vis[edges[i].to]){
					q.push(edges[i].to);    // 普通的 SPFA
					vis[edges[i].to] = true;
				}
			}
		}
	}
}

signed main(){
	n = read(), m = read();
	for(int i = 1; i <= m; i++){
		int u, v, w;
		u = read();
		v = read();
		w = read();
		add(u, v, w);
		add(v, u, w);
	}
	for(int i = 1; i <= n; i++){
		int k;
		k = read();
		for(int j = 1; j <= k; j++){
			int t;
			t = read();
			book[i][t] = true;   // 进行标记
		}
	}
	SPFA(1);
	cout << (dis[n] == 1e18 ? -1 : dis[n]);  // 记住这里要输出 -1
	return 0;
} 
```

---

## 作者：FreeTimeLove (赞：4)

这几乎是一个最短路裸题。这里提供一个**不用** map/set 的 Dijkstra 做法。

我们直接跑最短路，用 $dis$ 数组维护到达一个点的时间。每次取一个点 $u$ 松弛时，取出 $dis_u$，计算当到达时间为 $dis_u$ 时的出发时间 $w$。用  $ed_i.w$（边长）$+w$ 与 $dis_v$ 进行比较，如果 $w+ed_i.w<dis_v$ 就进行更新。最后如果 $dis_n<INF$（可以抵达），输出 $dis_n$，否则输出 $-1$ 即可。

至于如何计算出发时间：

我们开 $n$ 个 vector 数组 $t_{1-n}$，数组 $t_i$ 存储点 $i$ **不能**出发的时间（如果用二维数组会 **MLE**），每个 $t_i$最后再压入一个 $INF$ 。

在查询函数中二分查找 $t_u$ 中第一个**大于等于**  $dis_u$ 的时间 $t'$，如果 $t'>dis_u$ 说明当前可以出发，返回 $dis_u$ ；

否则（$t'=dis_u$）依次向后找相邻两个不能起飞的时间 $t_{u,now}$ 和 $t_{u,now+1}$ 之间是否有间隔，如果有间隔就返回 $t_{u,now}+1$（间隔中的最小值)。

因为最后一个数 $t_{u,k_u}$ 一定小于等于 $1e9$，与 $INF$ 之间一定有间隔 ，所以返回值一定是小于等于 $t_{u,k_u}+1$ 的。

### AC code:

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#define ll long long
using namespace std;
const int N=3e5+5;
int INF=0x3f3f3f3f;
int n,m,u,v,w,tot;
int nd[N],dis[N],bk[N],k[N];
vector<int>t[N];
struct edge{
	int v,w,nxt;
}ed[N];
void add(int u,int v,int w){
	ed[++tot]={v,w,nd[u]};
	nd[u]=tot;
}
struct node{
	int dis,u;
	bool operator <(const node &x)const{
		return x.dis<dis;
	}
};
int qry(int u,int ti){//出发时间 
	int l=1,r=k[u]+1,mid;
	if(l==r)return ti;//没有 不能出发的点，当前可以出发
	while(l<r){//二分 
		mid=(l+r)>>1;
		if(t[u][mid]<ti)
			l=mid+1;
		else
			r=mid;
	}
	if(t[u][l]>ti)return ti;//当前可以出发
	while(l++<=k[u])
		if(t[u][l-1]+1<t[u][l])//有间隔，能出发
			return t[u][l-1]+1;
}
void Dij(){
	priority_queue<node>que;
	memset(dis,0x3f,sizeof(dis));
	dis[1]=0;
	que.push({dis[1],1});
	while(!que.empty()){
		u=que.top().u;
		w=que.top().dis;
		que.pop();
		if(bk[u])continue;
		bk[u]=1;
		w=qry(u,w);//到达时间->出发时间 
		for(int i=nd[u];i;i=ed[i].nxt){
			v=ed[i].v;
			if(dis[v]>w+ed[i].w){
				dis[v]=w+ed[i].w;
				if(bk[v]==0)
					que.push({dis[v],v});
			}
		}
	}
}
int main(){
	cin>>n>>m;
	for(int i=0;i<m;i++){
		cin>>u>>v>>w;
		add(u,v,w);
		add(v,u,w);
	}
	for(int i=1;i<=n;i++){
		cin>>k[i];
		t[i].push_back(0);//给t[i][0]，让之后的赋值从t[i][1]开始 
		for(int j=1;j<=k[i];j++){
			cin>>w;
			t[i].push_back(w);
		}
		t[i].push_back(INF);
		//最后补一个无穷大保证出发时间在（t[i][l],INF)之间
	}
	Dij();
	cout<<(dis[n]==INF?-1:dis[n])<<endl;
	return 0;
}
```
### The End.

---

## 作者：ljk_Elaina (赞：4)

这是一道有关最短路的题。

是一道标准的 Dijkstra。加上一点点预处理。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define f first
#define se second
#define mp make_pair
typedef pair<int,int> pii;
const int N=1e5+7;
const int maxtime=1.5e9;  //1e9不够

int n,m,a,b,wei,k,t;
vector<pii>ed[N];  //用来记录边
priority_queue<pii>q;  //优先队列
set<int>s[N];  //set用来记录等待的人
int dist[N];  //dist记录最短路

int main(){
	scanf("%d%d",&n,&m);  //输入
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&a,&b,&wei);
		ed[a].pb(mp(b,wei));  //记录到vector中
		ed[b].pb(mp(a,wei));
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&k);
		for(int j=0;j<k;j++){
			scanf("%d",&t);
			s[i].insert(t);  //把等待的人加到set中去
		}
	}
	for(int i=1;i<=n;i++) dist[i]=maxtime;
	dist[1]=0;  //到自己的距离为零
	q.push(mp(1,0));  //把第一个点压入队列
	while(!q.empty()){
		int cur=q.top().f;  //取出队首
		int w=-q.top().se;
		q.pop();  //弹出队首
		if(dist[cur]!=w) continue;  //如果松弛过，跳过
		while(s[cur].count(w)) w++;  //如果有人，加加（等待）
		for(int i=0;i<ed[cur].size();i++){ //枚举可以到达的点
			int to=ed[cur][i].f;
			int w1=ed[cur][i].se;
			if(dist[to]>w+w1){  //如果可以松弛这个点
				dist[to]=w+w1;  //就松弛它
				q.push(mp(to,-dist[to]));  //并把它压入队列
			}
		}
	}
	if(dist[n]==maxtime) printf("-1\n");  //如果没有被松弛
    //说明到达不了
	else printf("%d\n",dist[n]);  //输出距离
	return 0;
}
```

maxtime用1e9不够，至少1e9+1e5。否则……

代码中有一行（if(dist[cur]!=w) continue;）如果不写，可能会TLE

优先队列是一个大根堆。可以用来排序（从大到小）。不管插入还是弹出都只要log n的时间。而且不用每一步都sort一遍（很快很方便）。

因为优先队列弹出大的，所以我们把负的压进队列可以使绝对值小的先出队。

如果忘写负号，不会WA，但会TLE

因为不管怎样，每个点都会被松弛

但这样那些权值小的点会排在最后，于是就跪了……


![](http://chuantu.biz/t6/255/1520997722x-1566638267.gif)

~~我什么都不知道……~~

当然，也可以使优先队列弹出小的。如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

priority_queue<int,vector<int>,greater<int> >q;

int main(){
	int x;
    cin>>x;
    for(int i=0;i<x;i++){
    	int a;
        cin>>a;
        q.push(a);
    }
    while(!q.empty()){
		cout<<q.top()<<" ";
        q.pop();
    }
    return 0;
}
```

greater把优先队列的大小比较交换了一下（**"greater<int> >"中间有空格，否则会报错！**）。


------------

#### 如果怕错了，可以用set。

```
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define f first
#define se second
#define mp make_pair
typedef pair<int,int> pii;
const int INF=2e9;
const int N=1e5+5;
int dist[N];
vector<int>z[N];
vector<pii>edge[N];
set<pii>q;
int n,m,from,to,w,x,kk;

int main() {	
	scanf("%d%d",&n,&m);
	for(int i=1; i<=m; i++) {
		scanf("%d%d%d",&from,&to,&w);
		edge[from].pb(mp(to,w));
		edge[to].pb(mp(from,w));
	}
	for(int i=1; i<=n; i++) {
		scanf("%d",&kk);
		for(int j=0; j<kk; j++) {
			scanf("%d",&x);
			z[i].pb(x);
		}
	}
	for(int i=1; i<=n; i++) dist[i]=INF;
	dist[1]=0;
	q.insert(mp(0,1));
	while(!q.empty()) {
		int k=q.begin()->second;
		q.erase(q.begin());
		int cur=dist[k];
		for(int i=0; i<z[k].size(); i++) if(z[k][i]==cur) cur++;
		for(int i=0; i<edge[k].size(); i++) {
			if(dist[edge[k][i].f]>cur+edge[k][i].se) {
				q.erase(mp(dist[edge[k][i].f],edge[k][i].f));
				dist[edge[k][i].f]=cur+edge[k][i].se;
				q.insert(mp(dist[edge[k][i].f],edge[k][i].f));
			}
		}
	}
	printf("%d\n",dist[n]==INF?-1:dist[n]);
	return 0;
}
```

其实与priority_queue没多大区别。

---

## 作者：_Fontainebleau_ (赞：2)

一道最短路，与模板不同的是这里多了一个判断条件：

**当有其他人在使用这个星球的传送通道时，Jack无法离开这个星球。**

最开始想到开一个二维数组存当前星球的传送门使用情况。

```cpp
#include<bits/stdc++.h>
#define FOR(i,j,k)  for(int i=(j);i<=(k);i++)
using namespace std;
int n,m,cnt,Time;
int dis[100001];
bool inq[100001];
int h[100001],t[100001],nxt[100001],val[100001];
int used[100001][1001];
int f,e,q[1000001];
inline int read()
{
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
inline void addedge(int a,int b,int c)
{
	t[++cnt]=b,val[cnt]=c,nxt[cnt]=h[a],h[a]=cnt;
}
inline bool check(int Time,int planet)
{
    int i=0;
	while(used[planet][++i]!=0)
	{
		if(used[planet][i]==Time)	return true;
		if(used[planet][i]>Time)	return false;
	}
	return false;
}
int main()
{
	n=read(),m=read();
	memset(dis,-1,sizeof(dis));
    memset(h,0,sizeof(h));
    memset(inq,false,sizeof(inq));
	for(int i=1;i<=m;i++)
	{
		int u=read(),v=read(),w=read();
		addedge(u,v,w),addedge(v,u,w);
	}
	for(int i=1;i<=n;i++)
	{
		int tmp=read();
		for(int j=1;j<=tmp;j++)
			used[i][j]=read();
	}
	inq[1]=true,dis[1]=0,q[1]=1,f=e=1;
	while(f<=e)
	{
		int u=q[f++];
     		Time=dis[u];
      		while(check(Time,u))    Time++;
		for(int p=h[u];p;p=nxt[p])
		{
            int v=t[p],c=val[p];
			if(dis[v]==-1||dis[v]>=Time+c)
			{
                    dis[v]=Time+c;
                    if(!inq[v])	inq[v]=true,q[++e]=v;
            }
		}
		inq[u]=false;
	}
	printf("%d\n",dis[n]);
	return 0;
}
```


然后发现开不下，直接 $MLE$。

于是想到 $STL$ 的 $map$。

第一次写成这个样子，没过 $#4$。

```cpp
#include<bits/stdc++.h>
#define FOR(i,j,k)  for(int i=(j);i<=(k);i++)
using namespace std;
int n,m,cnt;
int dis[100001];
bool inq[100001];
int h[100001],t[100001],nxt[200001],val[200001];
int f,e,q[10000001];
map<int,int> s[100001];
inline int read()
{
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
inline void addedge(int a,int b,int c)
{
	t[++cnt]=b,val[cnt]=c,nxt[cnt]=h[a],h[a]=cnt;
}
inline bool check(int Time,int planet)
{
    int i=0;
	while(s[planet][++i]!=0)
	{
		if(s[planet][i]==Time)	return true;
		if(s[planet][i]>Time)	return false;
	}
	return false;
}
int main()
{
	n=read(),m=read();
	memset(dis,-1,sizeof(dis));
    memset(h,0,sizeof(h));
	for(int i=1;i<=m;i++)
	{
		int u=read(),v=read(),w=read();
		addedge(u,v,w),addedge(v,u,w);
	}
	for(int i=1;i<=n;i++)
	{
		int tmp=read();
		for(int j=1;j<=tmp;j++)
			s[i][j]=read();
	}
	inq[1]=true,dis[1]=0,q[1]=1,f=e=1;
	while(f<=e)
	{
		int u=q[f++];
        int Time=dis[u];
        while(check(Time,u))    Time++;
		for(int p=h[u];p;p=nxt[p])
		{
            int v=t[p],c=val[p];
			if(dis[v]==-1||dis[v]>=Time+c)
			{
                    dis[v]=Time+c;
                    if(!inq[v])	inq[v]=true,q[++e]=v;
            }
		}
		inq[u]=false;
	}
	printf("%d\n",dis[n]);
	return 0;
}
```
再换一种方法，把 $map$ 改成 $bool$ 就过了

中间 $t$ 数组开错大小一直没过。

```cpp
#include<bits/stdc++.h>
#define FOR(i,j,k)  for(int i=(j);i<=(k);i++)
using namespace std;
int n,m,cnt;
int dis[100001];
bool inq[100001];
int h[100001],t[200001],nxt[200001],val[200001];
int f,e,q[10000001];
map<int,bool> s[100001];
inline int read()
{
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
inline void addedge(int a,int b,int c)
{
	t[++cnt]=b,val[cnt]=c,nxt[cnt]=h[a],h[a]=cnt;
}
int main()
{
	n=read(),m=read();
	memset(dis,-1,sizeof(dis));
    memset(h,0,sizeof(h));
	for(int i=1;i<=m;i++)
	{
		int u=read(),v=read(),w=read();
		addedge(u,v,w),addedge(v,u,w);
	}
	for(int i=1;i<=n;i++)
	{
		int tmp=read(),x;
		for(int j=1;j<=tmp;j++)
			x=read(),s[i][x]=true;
	}
	inq[1]=true,dis[1]=0,q[1]=1,f=e=1;
	while(f<=e)
	{
		int u=q[f++];
    	int Time=dis[u];
      while(s[u][Time]==true)    Time++;//唯一要注意的点
		for(int p=h[u];p;p=nxt[p])
		{
            int v=t[p],c=val[p];
			if(dis[v]==-1||dis[v]>=Time+c)
			{
                    dis[v]=Time+c;
                    if(!inq[v])	inq[v]=true,q[++e]=v;
            }
		}
		inq[u]=false;
	}
	printf("%d\n",dis[n]);
	return 0;
}
```
用的是 $SPFA$

---

## 作者：lzyqwq (赞：1)

# 题目分析
这题不过就是在最短路的板子上加一点东西，其实可以用字典（下文称为 map，因为~~这样方便码字~~这是它的类型名称）。

本来正常的最短路代码（我用的堆优化 Dijkstra）应该是这样（为了方便讲述，我把前面全局数组、结构体的代码都放上来了）：
```cpp
//全局定义，n和m还有其它一些七七八八的由于是单个变量，也不需要全局使用，所以就开主函数里面当成局部用了。数组开全局是因为自带初始化方便
int dis[100005];//存最短路
bool vis[100005];//是否访问过
struct edge
{
    int x,s;
};//x是这条边到的点，s是边权
vector<edge>g[100005];
struct node
{
    int x,s;
    bool operator<(const node&a)const
    {
        return s>a.s;
    }
};//x是点，s是当前到x的最短路
priority_queue<node>pq;

//堆优化Dijkstra
memset(dis,0x7f,sizeof(dis));//注意，这边由于一条边就有10^9我就没有用0x3f而是0x7f
dis[1]=0;//到起点为0
pq.push(node{1,0});//起点入队
while(pq.size())//跑最短路
{
    node t=pq.top();//取出当前距离最短的点
    pq.pop();
    int a=t.x,b=t.s;
    if(vis[a])//走过就跳过
    {
        continue;
    }
    vis[a]=1;//访问过
    for(int i=0;i<g[a].size();i++)//枚举所有边
    {
        edge f=g[a][i];//存边
        int x=f.x,y=f.s;//取出点和权值
        if(b+y<dis[x])//如果从当前点到达时间更少就更新并入队
        {
            dis[x]=b+y;
            pq.push(node{x,b+y});
        }
    }
}
```
但是现在其他人也会使用传送器，这很讨厌。那么我们首先想最简单粗暴的方法，用 $vt[i][j]$ 表示点 $i$ 在 $j$ 的时刻有没有他人使用传送器，有则标记为 $1$。可是 $i$ 最大可以到 $10^5$，$j$ 最大可以到 $10^9$，数组肯定会爆。而由于不是每个时刻都有他人要使用，所以这样开会很浪费。所以我们考虑用 map（还不会使用 map 的 OIer 们可以去看我博客里的[ STL 字典](https://www.luogu.com.cn/blog/juruo-lzy/post-zai-lai-yi-ge-stl-di-zi-dian)。

map 较数组（都叫 $v$）而言，优势在于：同是标记 $a$ 这个数，数组要使用 $v[1...a]$ 这么多单位的空间，而 map 只需要使用 $v[a]$ 这么一个单位的空间。

我们定义一个 map：
```cpp
map<pair<int,int>,bool>vt;//这边由于有点、时间两个量，所以我使用了pair，当然也可以开结构体，不过我懒。pair中前面那个int表示点编号，后面那个int表示时刻。上面解释过范围了，这里int就够。还不会用pair的OIer们可以自己去网上找这个STL的用法，我博客里暂时没写
```
前面读边的时候还是正常双向建边，只不过读每个点的传送器使用情况时需要这样写（变量名略跟题目中有不同）：
```cpp
for(int i=1;i<=n;i++)
{
    int x;//这个点的传送器有x个时刻被他人使用
    scanf("%d",&x);
    for(int j=1;j<=x;j++)
    {
        int s;//这个点的传送器第s个时刻被他人使用
        scanf("%d",&s);
        vt[make_pair(i,s)]=1;//打标记，表示点i在s的时刻有他人使用传送器
    }
}
```
然后在刚才的最短路板子里，加一段如下的代码，这段代码加在当前点枚举所有边扩展新点之前。

```cpp
for(int i=t.s;;i++)//从当前最短时刻开始枚举
{
    if(!vt[make_pair(a,i)])//如果这个时刻没有他人使用传送器
    {
        b=i;//b原来是之前的最短路，更新后表示最少在b的时刻使用传送器
        break;
    }
}
```
然后其它不变，我们就能使用最朴 ~~（花里）~~ 素 ~~（胡哨）~~ 的做法通过这题了。
# AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int dis[100005];//存最短路
bool vis[100005];//是否访问过
struct edge
{
    int x,s;
};//x是这条边到的点，s是边权
vector<edge>g[100005];//图，用向量存（本质上是邻接表）
struct node
{
    int x,s;
    bool operator<(const node&a)const
    {
        return s>a.s;
    }
};//x是点，s是当前到x的最短路
priority_queue<node>pq;//堆
map<pair<int,int>,bool>vt;//这边由于有点、时间两个量，所以我使用了pair，当然也可以开结构体，不过我懒。pair中前面那个int表示点编号，后面那个int表示时刻。上面解释过范围了，这里int就够。还不会用pair的OIer们可以自己去网上找这个STL的用法，我博客里暂时没写
int main()
{
    memset(dis,0x7f,sizeof(dis));//注意，这边由于一条边就有10^9我就没有用0x3f而是0x7f
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        g[u].push_back(edge{v,w});//双向建边
        g[v].push_back(edge{u,w});
    }
    for(int i=1;i<=n;i++)
    {
        int x;//这个点的传送器有x个时刻被他人使用
        scanf("%d",&x);
        for(int j=1;j<=x;j++)
        {
            int s;//这个点的传送器第s个时刻被他人使用
            scanf("%d",&s);
            vt[make_pair(i,s)]=1;//打标记，表示点i在s的时刻有他人使用传送器
        }
    }
    dis[1]=0;//到起点最短路是0
    pq.push(node{1,0});//起点入队
    while(pq.size())//跑最短路
    {
        node t=pq.top();//取出当前距离最短的点
        pq.pop();
        int a=t.x;
        if(vis[a])//走过就跳过
        {
            continue;
        }
        vis[a]=1;//访问过了
        int b;//最少在b的时刻使用传送器
        for(int i=t.s;;i++)//从小到大枚举最小时刻，这样找到第一个就可以跳出循环，省时间
        {
            if(!vt[make_pair(a,i)])//这个时刻当前点无他人使用传送器
            {
                b=i;//把最小时刻赋给b
                break;//跳出
            }
        }
        for(int i=0;i<g[a].size();i++)//枚举当前点连接的所有边
        {
            edge f=g[a][i];//暂存一下
            int x=f.x,y=f.s;//取出到达的点、权值
            if(b+y<dis[x])//如果这样路更短
            {
                dis[x]=b+y;//更新
                pq.push(node{x,b+y});//当前最短路入队
            }
        }
    }
    if(vis[n])//如果访问过能到达
    {
        printf("%d\n",dis[n]);//输出最短距离
    }
    else//否则输出-1
    {
        puts("-1");
    }
    return 0;
}
```
完结撒花！跪求过审 orz

---

## 作者：Prurite (赞：1)

## 思路
一道（近乎）裸的最短路。SPFA直接做，只需要在从每个点向外拓展的时候注意当前时间有无他人在使用，如果有就等1时刻（time++）再判断。可以用两个队列维护（维护当前的点和到达这个点的时间）。

注意这个题有一个坑点：某些测试点的答案十分接近int上限（但是也不需要long long），处理的时候注意INF的值以及避免溢出。

## 代码
```cpp
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

const int MAXN=1e5+1, MAXM=MAXN<<1, INF=2e9;
struct edge { int to, w, next; } e[MAXM<<1];
int firste[MAXN], eindex;
inline void addedge( int a, int b, int l )
{ e[++eindex]=(edge) { b, l, firste[a] }, firste[a]=eindex; }

int dis[MAXN];
int n, m;
vector<int> isusing[MAXN];

inline void reset( );
inline void read( );
inline int SPFA( int begin, int end );

int main( )
{
    while( scanf( "%d %d", &n, &m )!=-1 )
    {
        reset( );
        read( );
        printf( "%d\n", SPFA( 1, n ) ); //直接SPFA就好
    }
    return 0;
}

inline void reset( )
{
    for ( register int i=0; i<=n; i++ )
        firste[i]=dis[i]=0, isusing[i].clear();
    eindex=0;
}

inline void read( )
{
    for ( int i=1; i<=m; i++ )
    {
        int a, b, t;
        scanf( "%d %d %d", &a, &b, &t );
        addedge( a, b, t ), addedge( b, a, t );
    }
    for ( int i=1; i<=n; i++ )
    {
        int use;
        scanf( "%d", &use );
        for ( int j=1; j<=use; j++ )
        {
            int t;
            scanf( "%d", &t );
            isusing[i].push_back(t);
        }
    }
    return;
}

queue<int> q, qt; //分别记录节点和到达这个节点的时间 
bool inqueue[MAXN];
inline int SPFA( int begin, int end )
{
    queue<int> q1; q=qt=q1;
    for ( register int i=0; i<=n; i++ )
        inqueue[i]=0, dis[i]=INF;
    q.push( begin ), qt.push( 0 ), inqueue[begin]=1;
    dis[begin]=0;
    
    while ( !q.empty( ) )
    {
        int now=q.front( ), nowt=qt.front( );
        q.pop( ), qt.pop( ), inqueue[now]=0;
        for ( register int i=0; i<isusing[now].size( ); i++ )
            if ( isusing[now][i]==nowt )
                nowt++; //如果当前到达的时候有其他人在用就等1时刻再出发
        for ( int i=firste[now]; i!=0; i=e[i].next )
        {
            int to=e[i].to;
            if ( dis[to]>nowt+e[i].w )
            {
                dis[to]=nowt+e[i].w;
                q.push( to ), qt.push( dis[to] ), inqueue[to]=1;
            } //常规SPFA更新，更新的时候顺手更新到达该点时间即可
        }
    }
    
    if ( dis[end]==INF )
        return -1;
    else
        return dis[end];
}
```
[提交记录 用时: 7192ms / 内存: 12372KB](https://www.luogu.org/recordnew/show/6634172)

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

我们可以用一个堆优化的 [Dijkstra 算法](https://baike.baidu.com/item/%E8%BF%AA%E5%85%8B%E6%96%AF%E7%89%B9%E6%8B%89%E7%AE%97%E6%B3%95/23665989?fromtitle=Dijkstra%E7%AE%97%E6%B3%95&fromid=215612&fr=aladdin)解决此题。

首先是一系列普通的操作，到了输入通道占用情况的时候，就要用集合 `set` 维护。

当你走到某个点，此时通道正在被占用，就用花费时间自增来模拟等待。

设 $s[i]$ 为 $i$ 点占用情况的集合，$dis[i]$ 为从 $1$ 点走到 $i$ 点的最短距离，$u$ 是当前点，$t$ 是当前花费时间，$v$ 是该条边终点，$w$ 是该条边距离。

模拟等待可以写成：

```
while(s[u].count(t))++t;
```

注意松弛操作要写在等待后，并且要这样写：

```
if(t+w<dis[v])...
```

而不是：

```
if(dis[u]+w<dis[v])...
```

### 2 代码与记录

```cpp
#include<cstdio>
#include<queue>
#include<set>
using namespace std;
#define max_n 100000
#define max_m 200000
#define inf 0x3f3f3f3f
int n;
int m;
struct E{
	int v,w,nx;
}e[max_m+2];
int ei=0;
int fir[max_n+2];
set<int>s[max_n+2];
int dis[max_n+2];
struct W{
	int u,t;
	bool operator<(const W &a)const{
		return a.t<t;
	}
};
priority_queue<W>q;
W fro;
inline void addedge(int u,int v,int w){
	++ei; e[ei].v=v; e[ei].w=w; e[ei].nx=fir[u]; fir[u]=ei;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF0229B_1.in","r",stdin);
	freopen("CF0229B_1.out","w",stdout);
	#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)fir[i]=0;
	for(int i=1,u,v,w;i<=m;++i){
		scanf("%d%d%d",&u,&v,&w);
		addedge(u,v,w);
		addedge(v,u,w);
	}
	for(int i=1,k,t;i<=n;++i){
		scanf("%d",&k);
		for(int j=1;j<=k;++j){
			scanf("%d",&t);
			s[i].insert(t);
		}
	}
	dis[1]=0;
	for(int i=2;i<=n;++i)dis[i]=inf;
	q.push((W){1,0});
	while(!q.empty()){
		fro=q.top();
		q.pop();
		if(dis[fro.u]!=fro.t)continue;
		while(s[fro.u].count(fro.t))++fro.t;
		for(int i=fir[fro.u],v;i;i=e[i].nx){
			v=e[i].v;
			if(fro.t+e[i].w<dis[v]){
				dis[v]=fro.t+e[i].w;
				q.push((W){v,dis[v]});
			}
		}
	}
	if(dis[n]==inf)printf("-1\n");
	else printf("%d\n",dis[n]);
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/57400343)

By **dengziyue**

---

## 作者：wfycsw (赞：0)

- ## 一道标准的最短路亚模板题
之所以是亚模板题，是因为它与模板有些不同——**多了些与时间和地点有关的限制**

当然，这并不难实现。

看到n<=10^5&&sum{$k_i$},我一开始觉得用$map$可以卡过，便有了如下代码：
```cpp
#include<bits/stdc++.h>
#define RI register int
#define s second 
#define f first
#define du pair<int,int>
#define ru(x,y) q.push((du){-y,x})
using namespace std;
const int N=1e5+2;
const int da=2147483647;
struct wu{
	int n,t,s;
}a[N<<1];
int f[N],h[N],p;bool b[N];
map<bool,map<int,int> >vis;
priority_queue<du>q;
inline void add(int u,int v,int s){
	p=-~p;a[p].s=s;
	a[p].t=v;a[p].n=h[u];
	h[u]=p;
}
int main(){
	RI n,m,u,s,v,x;
	scanf("%d%d",&n,&m);
	for(RI i=1;i<=m;i=-~i){
		scanf("%d%d%d",&u,&v,&s);
		add(u,v,s);add(v,u,s);
	}
	for(RI i=1;i<=n;i=-~i){
		scanf("%d",&s);
		for(RI j=1;j<=s;j=-~j){
			scanf("%d",&u);
			vis[i][u]=1;
		}
		f[i]=da;
	}
	ru(1,0);f[1]=0;
	while(q.size()){
		u=q.top().s;x=-q.top().f;
		q.pop();
		if(b[u]) continue;
		b[u]=1;
		while(vis[u][x]) x=-~x;//判断是否有人
		for(RI i=h[u];i;i=a[i].n){
			v=a[i].t;s=a[i].s;
			if(f[v]>x+s)
				f[v]=x+s,ru(v,f[v]);
		}
	}
	if(f[n]==da) printf("-1");
	else printf("%d",f[n]);
	return 0;
}
```

然而，这并不能过，我便考虑了另一种黑科技——$set$。接着套上$ Dijkstra$模板。

```cpp
#include<bits/stdc++.h>
#define RI register int
#define is(x,y) q[x].insert(y)
#define co(x,y) q[x].count(y)
using namespace std;
const int N=1e5+2;
const int da=2147483647;
struct wu{
	int n,t,s;
}a[N<<1];
int f[N],h[N],p,d[5000002][2];bool b[N];
set<int>q[N];
inline void add(int u,int v,int s){
	p=-~p;a[p].s=s;
	a[p].t=v;a[p].n=h[u];
	h[u]=p;
}
int main(){
	RI n,m,u,s,v,x;
	scanf("%d%d",&n,&m);
	for(RI i=1;i<=m;i=-~i){
		scanf("%d%d%d",&u,&v,&s);
		add(u,v,s);add(v,u,s);
	}
	for(RI i=1;i<=n;i=-~i){
		scanf("%d",&s);
		for(RI j=1;j<=s;j=-~j){
			scanf("%d",&u);
			is(i,u);
		}
		f[i]=da;
	}
	f[1]=0;d[1][0]=1;
	for(RI t=1,w=1;t<=w;t=-~t){
		u=d[t][0];x=d[t][1];b[u]=0;
		while(co(u,x)) x=-~x; //判断是否有人
		for(RI i=h[u];i;i=a[i].n){
			v=a[i].t;s=a[i].s;
			if(f[v]>s+x){
				f[v]=s+x;
				d[++w][0]=v;d[w][1]=f[v];			
			}
		}
	}
	if(f[n]==da) printf("-1");
	else printf("%d",f[n]);
	return 0;
}
```
结果竟轻松水过。

同样，也可以用$spfa$跑一遍。
```cpp
#include<bits/stdc++.h>
#define RI register int
#define s second 
#define f first
#define is(x,y) d[x].insert(y)
#define co(x,y) d[x].count(y)
#define du pair<int,int>
#define ru(x,y) q.push((du){-y,x})
using namespace std;
const int N=1e5+2;
const int da=2147483647;
struct wu{
	int n,t,s;
}a[N<<1];
int f[N],h[N],p;bool b[N];
set<int>d[N];
priority_queue<du>q;
inline void add(int u,int v,int s){
	p=-~p;a[p].s=s;
	a[p].t=v;a[p].n=h[u];
	h[u]=p;
}
int main(){
	RI n,m,u,s,v,x;
	scanf("%d%d",&n,&m);
	for(RI i=1;i<=m;i=-~i){
		scanf("%d%d%d",&u,&v,&s);
		add(u,v,s);add(v,u,s);
	}
	for(RI i=1;i<=n;i=-~i){
		scanf("%d",&s);
		for(RI j=1;j<=s;j=-~j){
			scanf("%d",&u);
			is(i,u);
		}
		f[i]=da;
	}
	ru(1,0);f[1]=0;
	while(q.size()){
		u=q.top().s;x=-q.top().f;
		q.pop();
		if(b[u]) continue;
		b[u]=1;
		while(co(u,x)) x=-~x;//判断是否有人
		for(RI i=h[u];i;i=a[i].n){
			v=a[i].t;s=a[i].s;
			if(f[v]>x+s)
				f[v]=x+s,ru(v,f[v]);
		}
	}
	if(f[n]==da) printf("-1");
	else printf("%d",f[n]);
	return 0;
}
```
完结。

---

## 作者：__Hacheylight__ (赞：0)

题意：

小J（jack）要从1穿越到n。星球之间有一些双向通道，小J可以通过这些通道到达n。

但是有一些~~霸道~~的穿越者也要穿越。

当小J和穿越者同时要从S到T时，他必须要等待该穿越者出发才能出发，花费一秒。

如果有多个穿越者，那么必须等这些穿越者全部出发，小J才能出发

问最短要多久才能到达n

分析：

一看就是一个最短路模板题。我们就想怎么处理等待。

我们能够出发的时间是该点之后第一个没有被标记有穿越者来的那个点。

于是就暴力往后找。

可能时间复杂度有Bug，但是在CF下过了。速度也不慢。

最短路是写Dijkstra的。

如果要提高效率，可以再set中进行二分查找。这样很快。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std ;

#define rep(i, a, b) for (int (i) = (a); (i) <= (b); (i)++)
#define Rep(i, a, b) for (int (i) = (a) - 1; (i) < (b); (i)++)
#define REP(i, a, b) for (int (i) = (a); (i) >= (b); (i)--)
#define clr(a) memset(a, 0, sizeof(a))
#define Sort(a, len, cmp) sort(a + 1, a + len + 1, cmp)
#define ass(a, sum) memset(a, sum, sizeof(a))

#define ls ((rt) << 1)
#define rs ((rt) << 1 | 1)
#define lowbit(x) (x & -x)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define endl '\n'
#define ENDL cout << endl
#define SZ(x) ((int)x.size())

typedef long long ll ;
typedef unsigned long long ull ;
typedef vector <int> Vi ;
typedef pair <int, int> Pii ;
typedef pair <ll, ll> Pll ;
typedef map <int, int> mii ;
typedef map <string, int> msi ;
typedef map <ll, ll> mll ;

const int N = 100010 ;
const double eps = 1e-8 ;
const int iinf = INT_MAX ;
const ll linf = 2e18 ;
const double dinf = 1e30 ;
const int MOD = 1000000007 ;

int n, m, top = 1 ;
set <int> s[N] ;
int dis[N], head[N] ;

struct edge {
    int to, nxt, w ;
} e[N << 1] ;

void add(int a, int b, int w) {
    e[++top] = (edge) {b, head[a], w} ;
    head[a] = top ;
}

struct node {
    int x, len ;
    bool operator < (const node &a) const {
        return len > a.len ;
    }
};

void dij() {
    priority_queue <node> q ;
    for (int i = 1; i <= n; i++) dis[i] = iinf ;
    dis[1] = 0 ;
    q.push((node) {1, 0}) ;
    while (!q.empty()) {
        node now = q.top() ;
        q.pop() ;
        int tim = now.len ;
        while (s[now.x].count(tim)) tim++ ;
        if (dis[now.x] != now.len) continue ;
        for (int i = head[now.x]; i; i = e[i].nxt) {
            int to = e[i].to ;
            if (dis[to] > tim + e[i].w) {
                dis[to] = tim + e[i].w ;
                q.push((node) {to, dis[to]}) ;
            }
        }
    }
}

signed main(){
    scanf("%d%d", &n, &m) ;
    for (int i = 1; i <= m; i++) {
        int x, y, z ;
        scanf("%d%d%d", &x, &y, &z) ;
        add(x, y, z) ;
        add(y, x, z) ;
    }
    for (int i = 1; i <= n; i++) {
        int sum, x ;
        scanf("%d", &sum) ;
        while (sum--) scanf("%d", &x), s[i].insert(x) ;
    }
    dij() ;
    if (dis[n] == iinf) cout << -1 << endl ;
    else cout << dis[n] << endl ;
    return 0 ;
}
```


---

