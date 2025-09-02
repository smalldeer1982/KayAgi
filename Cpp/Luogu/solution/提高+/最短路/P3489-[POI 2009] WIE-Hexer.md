# [POI 2009] WIE-Hexer

## 题目描述

Byteasar 成为了一名猎魔人——一个征服怪物的人。

目前他要返回他的家乡 Byteburg。可惜回家的路要经过一个充满野兽的土地。幸运的是，当地居民被迫与怪物斗争了几个世纪，已经掌握了锻造的艺术——他们现在能够制造出对抗野兽非常有效的特殊剑。

Byteasar 所经过的土地相当广阔：那里有许多城镇，许多道路连接着它们。

这些道路不会在城镇外交叉（主要是因为其中一些是地下通道）。

Byteasar 已经收集了关于这片土地的所有实用信息（所有猎魔人都喜欢知道这些事情）。

他知道在每条路上可能遇到的怪物种类，以及他需要多少时间才能走完这条路。

他还知道在哪些村庄有铁匠，以及他们制作的剑对哪些种类的怪物有效。

Byteasar 想尽快回到 Byteburg。

作为一个猎魔人，他对自己不知道最佳路线感到相当羞愧，而且他目前身上没有剑。

帮助他找到到 Byteburg 的最短路径，以便每当他可能遇到某种怪物时，他之前就有机会获得一把合适的剑来对抗野兽。

你不需要担心剑的数量或重量——每个猎魔人都像牛一样强壮，所以他可以携带（几乎）无限数量的装备，特别是剑。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
6 7 4 2
2 1 2
3 2 1 3
1 2 2 0
2 3 9 0
1 4 2 1 2
2 5 3 0
4 5 5 2 2 3
4 6 18 0
5 6 3 2 1 2
```

### 输出

```
24
```

# 题解

## 作者：小塘空明 (赞：8)

先%下楼上的分层图2333

观察数据，发现p<=13,n<=200，所有我们很明显可以将状态保存下来。

设d[i][j]表示当前到达i，状态为j所需要的最短时间。

根据dijkstra的性质，n第一次被取出时就是答案。

在实际运算中，我们保存一个三元组(t,x,s);

t为当前的值，x为当前的点，s为走到当前的点所能铸的剑的状态，将s或上当前点铁匠能铸的剑的值，进行合法的转移即可。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<cstring>
#include<cmath>
#include<queue>
using namespace std;
const int N=2e2+10,M=3e3+10,inf=1e9;
int n,m,k,p,tot,a[N],d[N][N*50],vis[N][N*50];
int head[N],next[M*2],ver[M*2],edge[M*2],cost[M*2];
priority_queue<pair<pair<int,int>,int> >q;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
inline void add(int x,int y,int z,int c){
	ver[++tot]=y;edge[tot]=z;cost[tot]=c;next[tot]=head[x];head[x]=tot;
}
inline int dijkstra(){
	for(int i=1;i<=n;i++){
		for(int j=0;j<(1<<p);j++) d[i][j]=inf;
	}
	d[1][0]=0;q.push(make_pair(make_pair(0,1),0));
	while(q.size()){
		int t=-q.top().first.first,x=q.top().first.second,s=q.top().second;q.pop();
		if(x==n) return t; 
		if(vis[x][s]) continue;
		vis[x][s]=1;s|=a[x];
		for(int i=head[x];i;i=next[i]){
			int y=ver[i],z=edge[i],c=cost[i];
			if((s|c)!=s) continue;
			if(d[y][s]>t+edge[i]){
				d[y][s]=t+edge[i];
				q.push(make_pair(make_pair(-d[y][s],y),s));
			}
		}
	}
	return -1;
}
int main(){
	n=read();m=read();p=read();k=read();
	for(int i=1;i<=k;i++){
		int w=read(),q=read();
		for(int j=1;j<=q;j++){
			int x=read();a[w]|=1<<(x-1);
		}
	}
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read(),s=read(),c=0;
		for(int j=1;j<=s;j++){
			int v=read();c|=1<<(v-1);
		}
		add(x,y,z,c);add(y,x,z,c);
	}
	printf("%d\n",dijkstra());
	return 0;
}
```

---

## 作者：0x3F (赞：5)

首先 $p$ 很小，考虑状压。

跑 $\text{Dijskra}$，但是注意搜索时的每一个状态（也就是放在优先队列里的元素）要维护三个值：

- 目前所在的点。
- 到起点的距离。
- 当前剑的集合。

每一个点的每一条出边也要维护三个信息：

- 边的终点。
- 边的长度。
- 边上的妖怪的集合。

而且 $dis$ 数组也要开两维！

因为到达同一个点而获得不同种类的剑，所要走的距离显然是不同的。

枚举每一条出边，如果边上的妖怪集合是当前剑的集合的子集，就可以入队，并得到终点上的所有剑。

否则不能放行，因为你砍不死路上的所有妖怪。

另外注意，在起点时自动获得起点的剑，而不是轻装上阵。

时间复杂度为 $\mathcal{O}(2^p(n+m)\log n)$ 即 $\mathcal{O}(\texttt{能过})$。

还有由于是三元组，所以要写结构体，还要重载运算符。

~~顺便吐槽一下某些题解中的 `pair<pair<int,int>,int>`~~

见代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, p, k;
int x, y, z, c, t;
int arr[210];
int dis[210][8192];
struct node {
	int x;
	int d;
	int t;
};
bool operator < (node a, node b) {
	return a.d > b.d;
}
vector<node> G[210];
priority_queue<node> Q;
int main() {
	cin >> n >> m >> p >> k;
	while (k--) {
		cin >> x >> c;
		while (c--) {
			cin >> t;
			arr[x] |= (1<<(t-1));
		}
	}
	while (m--) {
		cin >> x >> y >> z >> c;
		k = 0;
		while (c--) {
			cin >> t;
			k |= (1<<(t-1));
		}
		G[x].push_back((node){y, z, k});
		G[y].push_back((node){x, z, k});
	}
	memset(dis, 0x3F, sizeof(dis));
	Q.push((node){1, 0, arr[1]});
	while (!Q.empty()) {
		node N = Q.top();
		Q.pop();
		int X = N.x;
		int D = N.d;
		int T = N.t;
		if (dis[X][T] <= D) continue;
		dis[X][T] = D;
		if (X == n) {
			cout << D << endl;
			return 0;
		}
		for (int i = 0; i < G[X].size(); i++) {
			if ((T | G[X][i].t) == T) Q.push((node){G[X][i].x, D + G[X][i].d, T | arr[G[X][i].x]});
		}
	}
	cout << -1 << endl;
	return 0;
}
```

$$\tiny\color{white}{\texttt{顺带一提 , AC 520 祭}}$$

---

## 作者：大菜鸡fks (赞：4)

这题非常暴力的想法就是分层最短路。 堆优化会跑的快一点。

```cpp
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#include<vector>
#define mp(x,y,z) (make_pair(make_pair(x,y),z))  
using namespace std;
const int INF=1e9,N=205,M=6005;
struct edge{
	int link,next,val,st;
}e[M];
int tot,head[N],n,m,p,k,S[N];
inline void add_edge(int u,int v,int w,int st){
	e[++tot]=(edge){v,head[u],w,st}; head[u]=tot;
}
inline void insert(int u,int v,int w,int st){
	add_edge(u,v,w,st);
	add_edge(v,u,w,st); 
}
inline void init(){
	scanf("%d%d%d%d",&n,&m,&p,&k);
	for (int i=1;i<=k;i++){
		int u,v,s; scanf("%d%d",&u,&s);
		for (int j=1;j<=s;j++){
			scanf("%d",&v);
			S[u]|=1<<v-1;
		}
	}
	for (int i=1;i<=m;i++){
		int u,v,w,s,st;
		scanf("%d%d%d%d",&u,&v,&w,&s);
		st=0;
		for (int j=1;j<=s;j++){
			int id;
			scanf("%d",&id);
			st|=1<<id-1; 
		}
		insert(u,v,w,st);
	}
}
int dis[N][1<<13];
bool vis[N][1<<13];
priority_queue<pair<pair<int,int>,int>,vector<pair<pair<int,int>,int> >,greater<pair<pair<int,int>,int> > >heap; 
inline int dijkstra(){
	memset(dis,127,sizeof(dis));
	dis[1][0]=0; heap.push(mp(0,1,0));
	while (!heap.empty()){
		int s=heap.top().first.first;
		int u=heap.top().first.second;
		int st=heap.top().second;
		heap.pop();
		if (u==n) return s;
		if (vis[u][st]) continue;
		vis[u][st]=1; st|=S[u];
		for (int i=head[u];i;i=e[i].next){
			int v=e[i].link;
			if ((e[i].st|st)!=st) continue;
			if (dis[v][st]>s+e[i].val){
				dis[v][st]=s+e[i].val;
				heap.push(mp(dis[v][st],v,st)); 
			}
		}
	}
	return -1;
}
inline void solve(){
	printf("%d\n",dijkstra());
}
int main(){
	init();
	solve();
	return 0;
}
```

---

## 作者：VioletIsMyLove (赞：3)

首先一读题就会发现这是一道最短路的题目，但是对于是否能走这条路很难去处理，但是仔细读题之后我们会发现小怪兽的种类很少！

这就很nice,果断状压处理，只要你剑的种类包含了这条路上所有的小怪兽，你就直接卡卡卡过去了，但如果没有的话硬闯你就看不到明天的太阳了。。。


Code:

```cpp
#include<bits/stdc++.h>
#define maxn 205
#define maxe 6005
#define maxp 8200
using namespace std;
int n,m,p,k,tot,a[maxn],lnk[maxn],w[2][maxe],son[maxe],nxt[maxe],dis[maxp][maxn],hep_size;
struct ZS{
	int x,id,s;
	bool operator<(const ZS B)const{return x<B.x;}
}hep[maxe];
bool vis[maxp][maxn];
inline int read(){
	int ret=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
	return ret;
}
void add_e(int x,int y,int z,int c){son[++tot]=y;w[0][tot]=z;w[1][tot]=c;nxt[tot]=lnk[x];lnk[x]=tot;}
void put(int x,int id,int s){
	hep[++hep_size]=(ZS){x,id,s};int son=hep_size;
	while (son!=1&&hep[son]<hep[son>>1]) swap(hep[son],hep[son>>1]),son>>=1;
}
ZS get(){
	ZS now=hep[1];int fa=1,son;hep[1]=hep[hep_size--];
	while (fa<<1<=hep_size){
		if ((fa<<1|1)>hep_size||hep[fa<<1]<hep[fa<<1|1]) son=fa<<1;else son=fa<<1|1;
		if (hep[son]<hep[fa]) swap(hep[son],hep[fa]),fa=son;else break;
	}
	return now;
}
int DIJ_HEAP(int x){
	memset(dis,63,sizeof(dis));
	memset(vis,0,sizeof vis);
	put(dis[a[x]][x]=0,x,a[x]);
	while (hep_size){
		ZS now=get();
		if (vis[now.s][now.id]) continue;
		if (now.id==n) return now.x;
		vis[now.s][now.id]=1;
		for (int j=lnk[now.id];j;j=nxt[j]){
			if ((now.s|w[1][j])!=now.s) continue;
			int s=now.s|a[son[j]];
			if (dis[now.s][now.id]+w[0][j]>=dis[s][son[j]]) continue;
			put(dis[s][son[j]]=dis[now.s][now.id]+w[0][j],son[j],s);
		}
	}
	return -1;
}
int main(){
	n=read(),m=read(),p=read(),k=read();
	for (int i=1;i<=k;i++){
		int x=read(),t=read();
		while (t--) a[x]|=1<<read()-1;
	}
	for (int i=1;i<=m;i++){
		int x=read(),y=read(),z=read(),t=read(),c=0;
		while (t--) c|=1<<read()-1;
		add_e(x,y,z,c),add_e(y,x,z,c);
	}
	printf("%d\n",DIJ_HEAP(1));
	return 0;
}
```


---

## 作者：_Yoimiya_ (赞：2)

- 前置知识：动态规划+ Dijkstra （ STL 优先队列优化）或 SPFA +位运算  


- 题面 _(来自于网络)_

  大陆上有$n$个村庄，$m$条双向道路，$p$种怪物，$k$个铁匠，每个铁匠会居住在一个村庄里，你到了那个村庄后可以让他给你打造剑，每个铁匠打造的剑都可以对付一些特定种类的怪物，每条道路上都可能出现一些特定种类的怪物，每条道路都有一个通过所需要的时间，现在要从$1$走到$n$，初始的时候你没有剑，要求在经过一条道路的时候，对于任意一种可能出现在这条道路上的的怪物，你都有已经有至少一把剑可以对付他，求从$1$走到$n$的最短时间（打造剑不需要时间）。  

  第一行正整数 $n, m, p, k$ ($1$ ≤ $n$ ≤ $200$, $0$ ≤ $m$ ≤ $3000$, $1$ ≤ $p$ ≤ $13$, $0$ ≤ $k$ ≤ $n$). 分别表示点数，边数，剑/怪物的型号数，铁匠数。 接下来k行描述铁匠，格式如下： 所在点编号$w$，所能锻造的剑种类数$q$，升序给出$q$个$1$到$p$的不同的整数表示型号。接下来$m$行描述边： 连接的顶点 $x$ , $y$，通过需要的时间$t$ ，路上的怪物数$s$，$s$个单调上升的$1$到$p$整数表示怪物型号。


- 很明显是一道最短路的题，仅仅是加了怪兽这样一个东西。
  
- 考虑保存怪物在每条边上的状态（有没有），一开始想用 bitset ,发现不用用，直接整数位运算。将怪兽的状态根据二进制位上的$1$和$0$来保存。要判断是否要求的剑都有了，可以用  
  ```cpp
  if((edge[i].mans|mans)!=mans) continue
  ```  
  来判断,即看当前所拥有的剑能不能砍完路上的怪物，若没有办法砍完怪物，就证明路径不合法。
  
   感觉没什么很难的点，跑迪杰斯特拉时注意一下更新，保证路径合法就好了。
    
- 算法时间复杂度是 $O$($n$ $\log$ $n$)（即 dj 的时间复杂度）。

- 以下是带注释的 AC 代码（轻微卡常）
```cpp
#include<bits/stdc++.h>
using namespace std;
const int Max_Cont(2e2+10);
const int Max_Way(3e3);
const int Max_Mans(1<<13|1);//考虑保存13个怪兽的二进制状态
int n,m,p,k;
int f[Max_Cont][Max_Mans];//最短路数组 
bool vis[Max_Cont][Max_Mans];
int can[Max_Cont];//每个铁匠做的剑能砍哪些怪物 
inline int read(){//日常快读 
	register int X(0); bool flag(1); char ch(getchar());
	while(ch<'0'||ch>'9') {if(ch=='-') flag=0; ch=getchar();}
	while(ch>='0'&&ch<='9') {X=(X<<1)+(X<<3)+ch-'0'; ch=getchar();}
	if(flag) return X;return ~(X-1);
}
struct node{
    int to,val,mans,next;
};node edge[Max_Way<<1|1];
int head[Max_Way<<1|1],tot;
inline void add(int u,int v,int w,int mans){
    edge[++tot].to=v;edge[tot].val=w;edge[tot].mans=mans;edge[tot].next=head[u];head[u]=tot;
}
#define make_pair_three(a,b,c) make_pair(make_pair(a,b),c)//方便起见，学习他人用了宏定义 
#define fa(tmp) (1<<(tmp-1))//标记怪物 
priority_queue<pair<pair<int,int>,int>,vector<pair<pair<int,int>,int> >,greater<pair<pair<int,int>,int> > >heap;
inline int dijkstra() {//STL优先队列优化迪杰斯特拉 
    memset(f,0x3f,sizeof f);
    memset(vis,0,sizeof vis);
    f[1][can[1]]=0;heap.push(make_pair_three(0,1,can[1]));
    while(!heap.empty()){
        int x((heap.top().first).second);//点 
        int kn(heap.top().second);heap.pop();//能砍什么怪物 
        if(vis[x][kn]) continue;vis[x][kn]=true;
        for(int i(head[x]);i!=0;i=edge[i].next) {
            int j(edge[i].to),w(edge[i].val),st(edge[i].mans);
            if((kn&st)!=st) continue;//砍不了路上的怪物 
            int nexkn(kn|can[j]);
            if(f[j][nexkn]>f[x][kn]+w) {//更新 
                f[j][nexkn]=f[x][kn]+w;
                heap.push(make_pair_three(f[j][nexkn],j,nexkn));
            }
        }
    }
    int ans(0x3f3f3f3f),bfd(1<<p);
    for(int i(0);i<bfd;++i) ans=min(ans,f[n][i]); 
    if(ans==0x3f3f3f3f) return -1;
    return ans;
}
signed main() {
    n=read();m=read();p=read();k=read();
    for(int i(1);i<=k;++i){
    	int cont(read()),knife(read());
    	for(int j(1);j<=knife;++j) can[cont]|=fa(read());//标记能砍的怪物 
		/*铁匠居住的城镇的数量，
		他的剑能有效对付的不同种类的怪物的数量，
		以及怪物本身的种类（以递增的顺序）。*/ 
	}
    for(int i(1);i<=m;++i){
    	int u(read()),v(read()),t(read()),s(read()),manster(0);
        for(int j(1);j<=s;++j)manster|=fa(read());//保存怪物的状态 
        add(u,v,t,manster);add(v,u,t,manster);//注意是无向边 
    }
    printf("%d",dijkstra());
    return 0;
}
```

---

## 作者：pocafup (赞：2)

神仙题%%%

其实这道题的状压还是挺明显的,主要是比较多变化

1.转移

转移是假设目前的 $bits | 路上的bits == bits$, 那么我们认为这条路上的怪都有相应的剑应付

方程: $dist[to][bits | sword[go]] =  max(dist[to][bits | sword[go], dist[now][bits] + dis);$

2.起点

**记住,起点不是 $dist[1][0]$!!!.**

起点是 $dist[1][sword[1]]$ ,就这个点卡了我一天

3.输入

输入的方法是每次将bits设为0,每输入一次就将bits|=1<<输入

**注意是双向边**

4.答案

答案就是到达点n的距离,可以用堆优化

代码

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
#define pp pair<int,int>
#define f first
#define s second
const int MAXN = 505;
const int BD = 14;
int n,m,k,p,head[MAXN], tot = 0;
struct Edge{
  int to,dis, bits;
};
int bit_on[MAXN];
int dist[MAXN][1<<BD], ans = 1e9;
vector<Edge> adj[MAXN];
bool inq[MAXN];
bool vis[MAXN][BD];
inline void dij(int source){
  memset(dist,0x3f3f,sizeof(dist));
  dist[source][bit_on[source]] = 0;
  priority_queue<pair<int,pp> > q; q.push(make_pair(0,make_pair(source,bit_on[source])));//堆优化
  while(!q.empty()){
    int qf = q.top().s.f,qs = q.top().s.s, curr = q.top().f;q.pop();
    if (qf==n){ans = min(ans,-curr);break;}
    for (Edge v : adj[qf]){
      if((qs|v.bits)!=qs)continue;
      int goes = qs|bit_on[v.to];
      if (dist[v.to][goes]>dist[qf][qs]+v.dis){
        dist[v.to][goes]=dist[qf][qs]+v.dis;
        q.push(make_pair(-dist[v.to][goes],make_pair(v.to,goes)));//转移方法
      }
    }
  }
  cout << ((ans==1e9) ? -1 : ans);
}
int main(){
  cin >> n >> m >> p >> k;
  for (int i=0;i<k;i++){
    int a,b; cin >> a >> b;
    for (int j=0;j<b;j++){
      int c; cin >> c;
      bit_on[a]|= 1<<(c-1);//输入
    }
  }
  for (int i=0;i<m;i++){
    int a,b,c,d, bit = 0; cin >> a >> b >> c>> d;
    for (int j=0;j<d;j++) {
      int e; cin >> e;
      bit|=1<<(e-1);
    }
    adj[a].push_back((Edge){b,c,bit});
    adj[b].push_back((Edge){a,c,bit});
	//建边
  }
  dij(1);
}
```


---

## 作者：_Wind_Leaves_ShaDow_ (赞：1)

嗯……一开始不信邪打了个 bfs……

要记录的很显然是当前位置、花的时间和拥有的剑的类型。其中剑的类型看到 $p\leq13$ 就知道是要状压。然后因为有边权所以用优先队列实现广搜。

```cpp
#include <bits/stdc++.h>
#define int long long
#define db double
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

using namespace std;
const int N=205,M=1e5+10,INF=1e14;

inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return x*f;
}

int n,m,pn,K,g[N];
int ide=0,hd[N],ed[M],nxt[M],vl[M],rq[M];

inline void Add(int x,int y,int val,int req){
	ide++;
	ed[ide]=y;
	nxt[ide]=hd[x];
	vl[ide]=val;
	rq[ide]=req;
	hd[x]=ide;
	return;
}

struct Node{
	int ps,stp,gt;
	inline bool operator <(const Node &stmp)const{
		return stp>stmp.stp;
	}
};
priority_queue<Node>q;
map<pair<pair<int,int>,int>,bool>vis;//这里用结构体会 WA，不知道为什么

inline int bfs(){
	if(!hd[n]&&n!=1)return -1;
	q.push({1,0,g[1]});
	vis[{{1,0},g[1]}]=1;
	while(!q.empty()){
		int fp=q.top().ps,fs=q.top().stp,fg=q.top().gt;
		q.pop();
		if(fp==n)return fs;
		for(int i=hd[fp];i;i=nxt[i]){
			if((fg&rq[i])==rq[i]&&!vis[{{ed[i],fs+vl[i]},(fg|g[ed[i]])}]){
				q.push({ed[i],fs+vl[i],fg|g[ed[i]]});
				vis[{{ed[i],fs+vl[i]},(fg|g[ed[i]])}]=1;
			}
		}
	}
	return -1;
}//标准广搜

signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	n=read();m=read();pn=read();K=read();
	for(int i=1;i<=K;i++){
		int pos,knd,tmp;
		pos=read();knd=read();
		for(int j=1;j<=knd;j++){
			tmp=read();
			g[pos]|=(1<<(tmp-1));
		}
	}
	for(int i=1;i<=m;i++){
		int x,y,tm,knd,tmp,req=0;
		x=read();y=read();tm=read();knd=read();
		for(int j=1;j<=knd;j++){
			tmp=read();
			req|=(1<<(tmp-1));
		}
		Add(x,y,tm,req);
		Add(y,x,tm,req);//双向边
	}
	cout<<bfs();
	return 0; 
}
```

[结果](https://www.luogu.com.cn/record/119934713)……

为什么会超时？

发现这种广搜很容易被出题人卡。比如如果你到不了 $n$ 点，然后前面是 $n-1$ 的完全图；或者能到 $n$ 点，但是到 $n$ 的 $dis$ 是跑前面的完全图还大……在这种毒瘤数据下，我们的代码不超时就怪了。~~万恶出题人。~~

所以考虑进行优化。

观察可以发现，这个 bfs 的复杂度取决于 $vis$ 数组的大小。也就是说我们可以把 $vis$ 数组多余的部分去掉。**哪里多余了？**

发现这一题的特点是 **能够重复经过点**，因为这种情况下可能 **获得不同的剑**，但是 **我们在拥有了剑后，就不应该再走这一条路了**，也就是说我们 **在拥有了同样的剑后，再重复到达一个点是无用的**，所以我们的 $vis$ 数组只需要记录 **到达的点和拥有的剑**。

然后 [自信一发](https://www.luogu.com.cn/record/119982893)……

为什么 WA 了？

发现在 **加进广搜队列时** 就已经判了重，此时可能会 **冲掉后面的最优解**。

所以把判重提到前面就好。

[发现了什么？](https://www.luogu.com.cn/record/119982953)

给代码：$\color{white}\text{唔……要变成……Dijkstra 的形状啦……！}$

```cpp
#include <bits/stdc++.h>
#define int long long
#define db double
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

using namespace std;
const int N=205,M=1e5+10,INF=1e14;

inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return x*f;
}

int n,m,pn,K,g[N];
int ide=0,hd[N],ed[M],nxt[M],vl[M],rq[M];

inline void Add(int x,int y,int val,int req){
	ide++;
	ed[ide]=y;
	nxt[ide]=hd[x];
	vl[ide]=val;
	rq[ide]=req;
	hd[x]=ide;
	return;
}

struct Node{
	int ps,stp,gt;
	inline bool operator <(const Node &stmp)const{
		return stp>stmp.stp;
	}
};
priority_queue<Node>q;
map<pair<int,int>,bool>vis;

inline int bfs(){
	q.push({1,0,g[1]});
	while(!q.empty()){
		int fp=q.top().ps,fs=q.top().stp,fg=q.top().gt;
		q.pop();
		if(fp==n)return fs;
		if(vis[{fp,fg}])continue;
		vis[{fp,fg}]=1;//把这个调到前面来
		for(int i=hd[fp];i;i=nxt[i]){
			int e=ed[i];
			if((fg&rq[i])!=rq[i]||vis[{e,fg|g[e]}])continue;
			q.push({e,fs+vl[i],fg|g[e]});
		}
	}
	return -1;
}

signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	n=read();m=read();pn=read();K=read();
	for(int i=1;i<=K;i++){
		int pos,knd,tmp;
		pos=read();knd=read();
		for(int j=1;j<=knd;j++){
			tmp=read();
			g[pos]|=(1<<(tmp-1));
		}
	}
	for(int i=1;i<=m;i++){
		int x,y,tm,knd,tmp,req=0;
		x=read();y=read();tm=read();knd=read();
		for(int j=1;j<=knd;j++){
			tmp=read();
			req|=(1<<(tmp-1));
		}
		Add(x,y,tm,req);
		Add(y,x,tm,req);
	}
	cout<<bfs();
	return 0; 
}
```

~~所以说最后还是写了 Dijkstra……~~

---

## 作者：BreakPlus (赞：1)

算法：最短路

有的时候，我们在求最短路时，题目有一些恼人的对最短路径的要求，比如在本题，有怪兽这么个东东。在这种情况下，我们考虑给 ``dis`` 数组加一维度，是不是很像做动态规划时的技巧？比如在本题，我们可以将当前可以应对的怪兽的二进制状态当作一个维度加到 ``dis`` 里面去。

代码细节：每一条边要记录两个值，一个是经过天数，另一个是需要应对的怪兽的二进制状态；跑 ``Dijkstra`` 的时候，优先队列里要存三个变量：当前最短路值，当前村庄，当前可应对怪兽的二进制状态，也就是说需要用到 ``pair<pair<int,int>,int>``；还要注意当前可应对状态不包含枚举的那条边的需应对状态则忽略这条边。

代码有点长，将近 $2 \text{KB}$，如下：

```cpp
#include<cstdio>
#include<iostream>
#include<queue>
using namespace std;
const int maxn=2e2+10,maxm=3e3+10,maxs=(1<<14);
int n,m,p,k,w,q,tmp,u,v,t; int dis[maxn][maxs]; bool vis[maxn][maxs];
int kill[maxn];
struct Edge{
    int to,day,ms,next;
}edge[maxm<<1];
int head[maxm<<1],tot;
void add(int u,int v,int day,int ms){
    tot++;
    edge[tot].to=v;
    edge[tot].day=day;
    edge[tot].ms=ms;
    edge[tot].next=head[u];
    head[u]=tot;
}
#define P pair<pair<int,int>,int>
#define mkp(a,b,c) make_pair(make_pair(a,b),c)
priority_queue<P,vector<P>,greater<P> >q1;
int Dijkstra(){
    for(register int i=1;i<=n;i++)
        for(register int j=0;j<(1<<p);j++) dis[i][j]=2e9,vis[i][j]=false;
    dis[1][kill[1]]=0; q1.push(mkp(0,1,kill[1]));
    while(!q1.empty()){
        int x=q1.top().first.second; int sta=q1.top().second; q1.pop();
        if(vis[x][sta]) continue;
        vis[x][sta]=true;
        for(register int i=head[x];i;i=edge[i].next){
            int tmp=edge[i].to,d=edge[i].day,st=edge[i].ms;
            if((sta&st)!=st) continue;
            int new_sta=sta|kill[tmp];
            if(dis[tmp][new_sta]>dis[x][sta]+d){
                dis[tmp][new_sta]=dis[x][sta]+d;
                if(!vis[tmp][new_sta]) q1.push(mkp(dis[tmp][new_sta],tmp,new_sta));
            }
        }
    }
    int answer=2e9;
    for(register int i=0;i<(1<<p);i++)
        if(dis[n][i]<answer) answer=dis[n][i];
    if(answer==2e9) return -1;
    return answer;
}
int main(){
    scanf("%d%d%d%d",&n,&m,&p,&k);
    for(register int i=1;i<=k;i++){
        scanf("%d%d",&w,&q);
        for(register int j=1;j<=q;j++){
            scanf("%d",&tmp);
            kill[w]|=(1<<(tmp-1));
        }
    }
    for(register int i=1;i<=m;i++){
        scanf("%d%d%d",&u,&v,&t);
        int s,tot=0; scanf("%d",&s);
        for(register int j=1;j<=s;j++){
            scanf("%d",&tmp);
            tot=tot|(1<<(tmp-1));
        }
        add(u,v,t,tot); add(v,u,t,tot);
    }
    printf("%d\n",Dijkstra());
    return 0;
}
```

---

## 作者：david0911 (赞：0)

## 题意

给出一张无向图，边有边权和一些限制，经过一个点可以解除某些限制，求点 $1$ 到点 $n$ 的最短路。

## 做法

首先考虑边没有限制的情况，可以发现是一个单源最短路，可以选择使用 Dijkstra 算法。

但是直接使用 Dijkstra 算法会出现一个问题：Dijkstra 算法中每个点只会向外进行一次松弛操作，之后就不再经过这个点。而根据题意，考虑一条边 $(u,v)$，从点 $u$ 走到点 $v$ 后，可以解除的限制增加了，回到 $u$ 点后或许可以松弛新的节点。

综上，我们考虑对 Dijkstra 做一定修改，使其支持“往回走”的操作。

可以发现，一个点 $u$ 可以往回走，当且仅当走到点 $u$ 后可以解除的限制增加了。

所以有了对 Dijkstra 算法修改的思路：对于同一个点，若走到此处时可解除的限制不同，视作走到了不同的点。

观察到题目中 $p$ 的范围很小，可以状态压缩，用一个二进制数表示限制。

考虑当前走到了节点 $i$，并且可以解除的限制在状态压缩后为 $s$，记 $dis_{i,s}$ 表示从点 $1$ 走到点 $i$ 状态为 $s$ 的最短路。相应的，记 $vis_{i,s}$ 表示在点 $i$ 状态为 $s$ 时是否向外进行过松弛操作。

这样对 Dijkstra 算法进行修改后便可以运行出正确答案。

## 细节

- 判断当前状态是否满足边的限制，可以对二者进行位运算中的或操作，在将结果与当前状态比较是否相等。

- 根据 Dijkstra 算法的思想，第一次到达点 $n$ 时的最短路便是答案，直接输出即可。

**AC Code**

```cpp
#include<bits/stdc++.h>

using namespace std;

const int maxn=210,maxm=3010;
int n,m,p,k,tot,head[maxn],d[maxn],dis[maxn][maxn*50];
bool vis[maxn][maxn*50];
struct edge{
	int v,w,f,nxt;
}e[maxm<<1];
struct node{
	int di,now,l;
	bool operator<(const node &a) const {
		return di<a.di;
	}
};
priority_queue<node> q;

int Dijkstra(){
	for(int i=1;i<=n;++i){
		for(int j=0;j<=(1<<p)-1;++j)
		dis[i][j]=1e9;
	}
	dis[1][d[1]]=0;
	q.push((node){0,1,d[1]});
	while(!q.empty()){
		node tmp=q.top();
		q.pop();
		int u=tmp.now,l=tmp.l;
		if(u==n) return dis[u][l];
		if(vis[u][l]) continue;
		vis[u][l]=true;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].v,f=e[i].f;
			if((l|f)!=l) continue;			
			if(dis[v][(l|d[v])]>dis[u][l]+e[i].w){
				dis[v][(l|d[v])]=dis[u][l]+e[i].w;
				q.push((node){-dis[v][(l|d[v])],v,l|d[v]});
			}
		}
	}
	return -1;
}

inline void add(int u,int v,int w,int f){
	e[++tot].v=v;
	e[tot].w=w;
	e[tot].f=f;
	e[tot].nxt=head[u];
	head[u]=tot;
}

int main(){
	scanf("%d%d%d%d",&n,&m,&p,&k);
	for(int i=1,w,q,r;i<=k;++i){
		scanf("%d%d",&w,&q);
		for(int j=1;j<=q;++j){
			scanf("%d",&r);
			d[w]|=(1<<(r-1));
		}
	}
	for(int i=1,v,w,t,s,u;i<=m;++i){
		scanf("%d%d%d%d",&v,&w,&t,&s);
		int ff=0;
		for(int j=1;j<=s;++j){
			scanf("%d",&u);
			ff|=(1<<(u-1));
		}
		add(v,w,t,ff);
		add(w,v,t,ff);
	}
	printf("%d\n",Dijkstra());
	return 0;
}
```

---

## 作者：aaaaaaaawsl (赞：0)

### 题目大意

无向图，某些点有多个剑，某些边有多个怪，不考虑剑的消耗，打怪时长，从起点走到终点的最小时间。

------------

### 解法

状压 + 最短路。

可以说是很板的一道最短路题。考虑将剑的种类用二进制储存在点的信息上，将怪物的种类用二进制储存在边的信息上，然后跑最短路。在进行转移前判断走没走过这个点和能不能打过这个怪。其他的模板都一样。

------

### 提醒

- 有可能有多群剑在同一个点上，所以在最开始处理状态的时候要用或而不是加。

- 如果你在状压的时候直接将种类左移，那么总状态数要多开一位。

- 最后枚举答案要从 $0$ 开始。



------------

### 代码

```cpp

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>

using namespace std;

const int N = 2e2 + 10;
const int M = 6e3 + 10;
const int Mo = (1 << 14) + 1;

int read() {
	register int x = 0, f = 1; register char ch = getchar();
	for(; ch > '9' || ch < '0'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return x * f;
}

int n, m, p, k;
int arr[N];
int ans = 0x3f3f3f3f;

int e[M], head[M], Next[M], idx, Mon[M], val[M];
void add(int a, int b, int c, int d) {
	e[++ idx] = b; Next[idx] = head[a]; head[a] = idx; val[idx] = c; Mon[idx] = d;
}

struct node{
	int dis, pos, arr;
	inline bool operator < (const node &a) const{
		return a.dis < dis;
	}
};

int f[N][Mo]; 
priority_queue<node, vector<node>> heap;
int vis[N][Mo];

void dij(){
	memset(f, 63, sizeof f);
	memset(vis, 0, sizeof vis);
	f[1][arr[1]] = 0; heap.push({0, 1, arr[1]});
	while(!heap.empty()) {
		node now = heap.top(); heap.pop();
		if(vis[now.pos][now.arr]) continue;
		vis[now.pos][now.arr] = 1;
		for(int i = head[now.pos]; i; i = Next[i]){
			int j = e[i], w = val[i], m = Mon[i];
			if((now.arr | m) != now.arr) continue;
			if(f[j][now.arr | arr[j]] > f[now.pos][now.arr] + w) {
				f[j][now.arr | arr[j]] = f[now.pos][now.arr] + w;
				heap.push(node{f[j][now.arr | arr[j]], j, (now.arr | arr[j])});
			}
		}
	}
	int g = 0;
	for(int i = 0; i < Mo; ++ i){
		ans = min(ans, f[n][i]);
		if(vis[n][i]) g = 1;
	}
	if(g == 0) puts("-1");
	else printf("%d", ans);
	exit(0);
}

signed main(){
	n = read(); m = read(); p = read(); k = read();
	for(int i = 1; i <= k; ++ i){
		int w = read(), q = read();
		for(int j = 1; j <= q; ++ j) arr[w] |= (1 << (read() - 1));
	}
	for(int i = 1; i <= m; ++ i) {
		int x = read(), y = read(), t = read(), s = read();
		int mo = 0ll;
		for(int j = 1; j <= s; ++ j) mo |= (1 << (read() - 1));
		add(x, y, t, mo); add(y, x, t, mo);
	}
	dij();
	return 0;
}

```

---

