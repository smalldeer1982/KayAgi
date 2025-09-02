# Jzzhu and Cities

## 题目描述

Jzzhu is the president of country A. There are $ n $ cities numbered from $ 1 $ to $ n $ in his country. City $ 1 $ is the capital of A. Also there are $ m $ roads connecting the cities. One can go from city $ u_{i} $ to $ v_{i} $ (and vise versa) using the $ i $ -th road, the length of this road is $ x_{i} $ . Finally, there are $ k $ train routes in the country. One can use the $ i $ -th train route to go from capital of the country to city $ s_{i} $ (and vise versa), the length of this route is $ y_{i} $ .

Jzzhu doesn't want to waste the money of the country, so he is going to close some of the train routes. Please tell Jzzhu the maximum number of the train routes which can be closed under the following condition: the length of the shortest path from every city to the capital mustn't change.

## 样例 #1

### 输入

```
5 5 3
1 2 1
2 3 2
1 3 3
3 4 4
1 5 5
3 5
4 5
5 5
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 2 3
1 2 2
2 1 3
2 1
2 2
2 3
```

### 输出

```
2
```

# 题解

## 作者：雄鹰展翅 (赞：11)

题目中的小细节：一定要先存所有边再判断

思路：存图后判断最短路是否唯一。

判断最短路是否唯一的方法：
 - 若特殊边长度大于$dis[v]$，删除。
 - 若特殊边长度等于$dis[v]$，若到v的最短路不止一条，删除，同时最短路数量-1。
 - 在求最短路时更新v的最短路数量。
 
代码：
 
```cpp
#include<iostream>
#include<string.h> 
#include<queue>
#define pa pair<int,int>
#define N 1000005
#define M 5000005
using namespace std;

int n,m,k,S=1,m0,ans;
int dis[N],h[N],a[N][3],cnt[N];
bool vis[N];
struct edge{
	int next,to,w;
}e[M];
priority_queue< pa,vector<pa>,greater<pa> > q;

void ins(int u,int v,int w){
	e[++m0]=(edge){h[u],v,w};h[u]=m0;
}

void dijkstra(int s){
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0,q.push(make_pair(0,s));
	
	while(!q.empty()){
		int u=q.top().second; q.pop();
		if(vis[u]) continue; vis[u]=1;
		for(int i=h[u];i;i=e[i].next){
			int v=e[i].to;
			if(dis[v]==dis[u]+e[i].w) cnt[v]++;
			if(dis[v]>dis[u]+e[i].w){
				dis[v]=dis[u]+e[i].w;
				cnt[v]=1;
				q.push(make_pair(dis[v],v));
			}
		} 
	} 
	
}

int main(){
	int i,u,v,w;
	cin>>n>>m>>k;
	for(i=1;i<=m;i++) cin>>u>>v>>w,ins(u,v,w),ins(v,u,w);
	for(i=1;i<=k;i++){
		cin>>a[i][1]>>a[i][2];
		v=a[i][1],w=a[i][2];
		ins(1,v,w),ins(v,1,w);
	}
	
	dijkstra(S);
	for(i=1;i<=k;i++){
		v=a[i][1],w=a[i][2];
		if(dis[v]<w) ans++;
		if(dis[v]==w)
			if(cnt[v]>1) ans++,cnt[v]--;
	}

	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：ahawzlc (赞：8)

这是一道最短路的题，而且貌似有 SPFA 之死嫌疑。

~~SPFA 已死，Dijkstra 当道！~~

------------

就这道题来说，先存好原图，再将这些特殊边读入。在读入过程中，做一下处理，将单源最短路取一个$\min{dis[v],value}$ ,同时记录有多少条特殊边重复，并把这些点存起来，加入堆中。

这些重复的特殊边不起作用应当很好理解。

然后跑一遍 Dijkstra ，记录一下这些特殊边有多少个被 hank 掉（指被其他方式更换掉 TA 的最短路地位）。注意，这里**不是增加答案数**，而是记录下这个边是否被**更替掉**。（笔者曾因为这个调了不少时间 QAQ 。

在最短路中再加一个处理，因为我们只要确定这条边没用，那么对于这个点的最短路就无须连续更新，所以可以将堆顶跳出（亲测可以防止 MLE ）。

最后 for 一遍上面记录的点，如果连向这个点的特殊边被 hank 掉 那么就增加答案数。

因为用到堆优化 Dijkstra ，所以本人用了 pair 操作，不懂的[出门右转](https://blog.csdn.net/sevenjoin/article/details/81937695)不谢。（借用了某大佬的 pair 整理笔记，在这里 sto TA orz）

好的，下面是代码：

``` cpp
#include<bits/stdc++.h>
#define pi pair<int,int>
#define mp make_pair
#define F first
#define S second
#define re register
using namespace std;

int n,m,k,dis[100005],sum,ans;
bool vis[100005],ud[600005];
priority_queue< pi > q;
vector<int> v;
int h[100005],cnt;

struct node {//链式前向星存边
	int to,nxt,cost;
} b[600005];

void add(int x,int y,int z) {//加边操作
	b[++cnt].nxt=h[x];
	b[cnt].to=y;
	b[cnt].cost=z;
	h[x]=cnt;
}

inline int read() {//快读
	int sum=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		sum=(sum<<3)+(sum<<1)+ch-'0';
		ch=getchar();
	}
	return sum*w;
}

int main() {
	n=read();
	m=read();
	k=read();
	for(re int i=1; i<=m; ++i) {
		int a,b,c;
		a=read();
		b=read();
		c=read();
		add(a,b,c);
		add(b,a,c);
	}
	memset(dis,0x3f,sizeof(dis));
	for(re int i=1; i<=k; ++i) {
		int v,c;
		v=read();
		c=read();
		if(dis[v]!=0x3f3f3f3f) ++ans;//记录重复边
		dis[v]=min(dis[v],c);
	}
	for(int i=1; i<=n; i++) {
		if(dis[i]!=0x3f3f3f3f) {
			v.push_back(i);
			q.push(mp(-dis[i],i));
		}
	}
	dis[1]=0;
	vis[1]=1;
	q.push(mp(0,1));
	while(q.size()) {
		pi u=q.top();
		q.pop();
		vis[u.S]=1;
		for(re int i=h[u.S]; i; i=b[i].nxt) {
			int v=b[i].to,cost=b[i].cost;
			if(dis[v]>=dis[u.S]+cost) {
				dis[v]=dis[u.S]+cost;
				ud[v]=1;//记录被hank掉的边
				q.push(mp(-dis[v],v));
			}
		}
		while(q.size()&&vis[q.top().S]) q.pop();//跳出堆顶操作
	}
	for(re int i=0; i<v.size(); i++) {
		if(ud[v[i]]) ++ans;//二次更新答案数
	}
	printf("%d",ans);
	return 0;
}

```

---

## 作者：Ganshuaige (赞：6)

Jzzhu and Cities

//

一道最短路+思维题

//

思路：
读入K条路

因为这K条路是直接与源点联通

所以

如果dis[v]>w 就将v入队

并且标记一个book[v]

表示这个点v是与源点相连的铁路

进行松弛操作时

如果这个dis[v]>dis[u]+w

就将book[v]标记为0

表示走铁路并不是最优解

最后扫一遍点看book[v]是否为真

若为真就将ans++

输出k-ans就是答案

```cpp
#include<queue>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#define INF 0x3f3f3f3f3f3f3f

const int Maxn = 1e5+10;
using namespace std;

int cnt;
int head[Maxn];

vector <pair<int ,int > > E[Maxn];

int n,m,k;
bool vis[Maxn];
long long dis[Maxn];
bool book[Maxn];
queue <int> q;


int main(){
//	freopen("railway.in","r",stdin);
//	freopen("railway.out","w",stdout);
	int u,v,w;
	memset(vis,0,sizeof(vis));
	memset(head,-1,sizeof(head));
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++)
		dis[i]=INF;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&u,&v,&w);
		E[u].push_back(make_pair(v,w));
        E[v].push_back(make_pair(u,w));
	}
	q.push(1);
	dis[1]=0;
	vis[1]=1;
	for(int i=1;i<=k;i++){
		scanf("%d%d",&v,&w);
		if(w<dis[v]){
			dis[v]=w;
			vis[v]=1;
			book[v]=1;
			q.push(v);
		}
	}
	while(!q.empty()){
		int u=q.front();
		q.pop();
		vis[u]=0;
		for(int i=0;i<E[u].size();i++){
			int v=E[u][i].first;
            int w=E[u][i].second;
			if(dis[v]>=dis[u]+w){
				dis[v]=dis[u]+w;
				book[v]=0;
				if(!vis[v]){
					vis[v]=1;
					q.push(v);
				}
			}
		}
	}
	int ans = 0;
	for(int i=1;i<=n;i++)
		if(book[i])
			ans++;
	printf("%d",k-ans);
	return 0;
}//666
```



---

## 作者：__newbie__ (赞：3)

## 前言
Dijkstra&最短路计数

## 题意
$n$ 个点，$m$ 条带权边（即公路）的无向图，另外还有 $k$ 条特殊边（即铁路），每条边连接$1$和$i$。

问最多可以删除这 $k$ 条边中的多少条，使得每个点到 $1$ 的最短距离不变。

## 解题思路
跑一遍 Dijkstra，顺带记录下最短路的数量。对于每条铁路，如果长度大于求得的最短路直接为答案贡献 $1$，如果长度等于求得的最短路且路径不唯一则为答案贡献 $1$。**特别注意，由于可能有重边，如果最短路径不唯一，一定要删掉这条铁路。**

## 完整代码
```cpp
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using Pll = pair<ll, ll>;

const ll kmaxn = 1e5 + 5, inf = 1e18;
ll n, m, k, b, e, v, ans = 0, dis[kmaxn], tot[kmaxn];

struct node {
  ll id, d;
  bool operator<(const node &r) const {
    return d > r.d;
  }
};

struct way{
  ll e, v;
} wayt[kmaxn];

vector<way> city[kmaxn];
priority_queue<node> q;

void add(ll a, ll b, ll c) {
  city[a].push_back({b, c});
  city[b].push_back({a, c});
}

void Dijkstra() {
  fill(dis + 1, dis + n + 1, inf);
  for (q.push({1, 0}); !q.empty(); ){
    node top = q.top();
    q.pop();
    if (dis[top.id] == top.d) {
      tot[top.id]++;
    }
    if (dis[top.id] > top.d) {
      tot[top.id] = 1;
      dis[top.id] = top.d;
      for (way i : city[top.id]) {
        q.push({i.e, top.d + i.v});
      }
    }
  }
}

int main() {
  cin >> n >> m >> k;
  for (int i = 1; i <= m; i++) {
    cin >> b >> e >> v;
    add(b, e, v);
  }
  for (int i = 1; i <= k; i++) {
    cin >> wayt[i].e >> wayt[i].v;
    add(1, wayt[i].e, wayt[i].v);
  }
  Dijkstra();
  for (int i = 1; i <= k; i++) {
    if (dis[wayt[i].e] < wayt[i].v) {
      ans++;
    }
    if (dis[wayt[i].e] == wayt[i].v && tot[wayt[i].e] > 1) {
      tot[wayt[i].e]--, ans++;
    }
  }
  cout << ans;
  return 0;
}
```


---

## 作者：Zi_Gao (赞：2)

## 前言

为什么大家写的这么麻烦。。。

## 正文

### 0x00 问题分析

要删去尽量多的边就要保留最少的边，那么要尽量少使用特殊边去松弛最短路。这里分类讨论一下：

1. 当前用于尝试松弛的边是特殊边

- $dis_u+w<dis_v$ 时，必须使用这个边松弛，否则无法保证正确答案。

- otherwise，不使用这个边。

2. 当前用于尝试松弛的边不是特殊边

- $dis_u+w<dis_v$ 时，必须使用这个边松弛，而且更优（用的特殊边更少）。

- $dis_u+w=dis_v$ 时，用这个边替换掉之前的边。

- otherwise，不使用这个边。

那么我们在堆内用多关键字排序：第一关键字——路径长度；第二关键字——边的类型。然后记录来时的边，最后统计即可。

### 0x01 代码实现

AC CODE

```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<bitset>
// #define ONLINE_JUDGE
#define INPUT_DATA_TYPE int
#define OUTPUT_DATA_TYPE int
INPUT_DATA_TYPE read(){register INPUT_DATA_TYPE x=0;register char f=0,c=getchar();while(c<'0'||'9'<c)f=(c=='-'),c=getchar();while('0'<=c&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();return f?-x:x;}void print(OUTPUT_DATA_TYPE x){register char s[20];register int i=0;if(x<0){x=-x;putchar('-');}if(x==0){putchar('0');return;}while(x){s[i++]=x%10;x/=10;}while(i){putchar(s[--i]+'0');}return;}

struct EDGE{
    int to,type;
    long long w;
    bool operator < (const EDGE another) const{//多关键字
        return w==another.w?type>another.type:w>another.w;
    }
};

std::vector<EDGE> e[100010];
std::priority_queue<EDGE> Q;
void addEdge(int u,int v,int w,int type){e[u].push_back((EDGE){v,type,w});return;}
long long dis[100010];
int from[100010];
std::bitset<100010> vis;

int main(){
	#ifndef ONLINE_JUDGE
	freopen("name.in", "r", stdin);
	freopen("name.out", "w", stdout);
	#endif

    register int i,u,v,res=0;
    register long long w;
    int n=read();
    int m=read();
    int k=read();
    for(i=0;i<m;++i){
        u=read();
        v=read();
        w=read();
        addEdge(u,v,w,0);
        addEdge(v,u,w,0);
    }

    for(i=0;i<k;++i){
        u=1;
        v=read();
        w=read();
        addEdge(u,v,w,1);
        addEdge(v,u,w,1);
    }

    memset(dis,0x3f,sizeof(dis));
    dis[1]=0;
    Q.push((EDGE){1,0,0});

    while(!Q.empty()){
        u=Q.top().to;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(auto edge:e[u]){
            v=edge.to;
            w=edge.w;
            if((dis[u]+w<dis[v])){//分类讨论 - 必须使用
                from[v]=edge.type;
                dis[v]=dis[u]+w;
                Q.push((EDGE){v,edge.type,dis[v]});
            }else if((dis[u]+w==dis[v]&&edge.type==0))//进行替换
                from[v]=edge.type;
        }
    }

    for(i=1;i<=n;++i) res+=from[i];//统计

    print(k-res);

	#ifndef ONLINE_JUDGE
	fclose(stdin);
	fclose(stdout);
	#endif
    return 0;
}
```

## 后记

用我的做法，实际上这个题加强成任意特殊边都行。

---

## 作者：神光qwq (赞：2)

[题目链接](https://www.luogu.com.cn/problem/CF449B)

## 思维历程

观察数据范围，可以知道应该使用堆优化的 dijkstra 来寻找最短路。

首先我们应当在把所有边都加入的情况下跑一遍最短路，而后对特殊边进行处理。

由于特殊边是从起点直接连接，若最短路小于特殊边长度，就说明这条特殊边可以被删去，等于时如果有可以不经过这条边的路径则也可以删去。

**但是，还有一个问题。**

一条特殊边（视为 $A$）的删除是否会影响到另一条特殊边（视为 $B$）的最短路呢？

易知，$A$ 必然不是最短路，那么对于 $B$ 的最短路来说，如果要经过 $A$ 的起点，必然存在比选择 $A$ 更优的路径，如果不经过，那么显然不会有任何影响。

## 思路总结

跑一遍最短路，同时对于最短路的条数进行计数（当特殊边等于最短路，但同时有其他走法时，这条特殊边也是能删去的），最后对 $dis$ 数组判断，若小于对应的 $y$ 直接计入答案，若等于且 $tot$ 记录路径不止一条，则也计入答案并更新 $tot$ 数组。

~~本人拙见，如有差错，请赐教。~~

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define void inline void
using namespace std;
const ll N=6e5+10,inf=1e18;
ll n,m,k,ans=0,s[N],y[N],dis[N],tot[N],vis[N];
ll cnt=0,h[N],nxt[N<<1],to[N<<1],val[N<<1];
struct node{
	ll u,d;
	inline bool operator < (const node &r) const {return d>r.d;}
};
priority_queue<node>q;
inline ll read(){
	char ch=getchar();ll res=0,f=1;
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') res=res*10+ch-'0',ch=getchar();
	return res*f;
}
void add(ll u,ll v,ll w){
	nxt[++cnt]=h[u],to[cnt]=v,val[cnt]=w,h[u]=cnt;
}
void dj(){
	for(ll i=1;i<=n;i++) dis[i]=inf;
	q.push((node){1,0}),dis[1]=0;
	while(!q.empty()){
		node top=q.top();q.pop();
		ll x=top.u,d=top.d;
		if(vis[x]) continue;
		vis[x]=1;
		for(ll i=h[x];i;i=nxt[i]){
			ll v=to[i],w=val[i];
			if(dis[x]+w==dis[v]) tot[v]++;
			if(dis[x]+w<dis[v]) dis[v]=dis[x]+w,q.push((node){v,dis[v]}),tot[v]=1;
		}
	}
}
int main(){
	n=read(),m=read(),k=read();
	for(ll i=1;i<=m;i++){
		ll u=read(),v=read(),w=read();
		add(u,v,w),add(v,u,w);
	}
	for(ll i=1;i<=k;i++){
		s[i]=read(),y[i]=read();
		add(1,s[i],y[i]),add(s[i],1,y[i]);
	}
	dj();
	for(ll i=1;i<=k;i++){
		if(dis[s[i]]<y[i]) ans++;
		if(dis[s[i]]==y[i]&&tot[s[i]]>1) tot[s[i]]--,ans++; 
	}
	printf("%lld\n",ans);
	return 0;
}

```


---

## 作者：0xFF (赞：2)

#### 题目大意


------------
给定一个 $n$ 个点，$m$ 条边的无向图，再给定 $k$ 条特殊边连接 $1$ ~ $i$ 这两点，问可以删去几条边使得 $1$ ~ $i$ 这两点间的最短路径不变，即这条特殊边对于最短路径无影响。

#### 思路分析


------------
跑一遍最短路，记录 $1$ 到 $i$ 的最短路径长度为 $dis_i$，讨论如下情况：

- 如果这条特殊边长度大于 $dis_i$，说明这个特殊边不起作用，删去即可。
- 如果这条特殊边长度等于 $dis_i$并且从 $1$ ~ $i$ 的最短路路径不止一条，那么这条特殊边也能删去。

#### 代码实现


------------
```cpp
#include<iostream>
#include<cstring> 
#include<queue>
#define N 1000005
#define M 5000005
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
	for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
	return x*f;
}
int n,m,k,tot,ans;
int dis[N],head[N],a[N][3],cnt[N];
bool vis[N];
struct node{
	int next,to,w;
}edge[M];
priority_queue< pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;

void addedge(int a,int b,int c){
	edge[++tot].to = b;
	edge[tot].w = c;
	edge[tot].next = head[a];
	head[a] = tot;
}

void dijkstra(int s){
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0;
	q.push(make_pair(0,s));
	while(!q.empty()){
		int u=q.top().second; 
		q.pop();
		if(vis[u]) continue; 
		vis[u]=1;
		for(int i=head[u];i;i=edge[i].next){
			int v = edge[i].to;
			if(dis[v] == dis[u] + edge[i].w) cnt[v]++;
			if(dis[v] > dis[u] + edge[i].w){
				dis[v] = dis[u] + edge[i].w;
				cnt[v] = 1;
				q.push(make_pair(dis[v],v));
			}
		} 
	} 
	
}

signed main(){
	int u,v,w;
	n = read(),m = read(),k = read();
	for(int i=1;i<=m;i++){
		u = read(),v = read(),w = read();
		addedge(u,v,w),addedge(v,u,w);
	} 
	for(int i=1;i<=k;i++){
		a[i][1] = read() , a[i][2] = read();
		v = a[i][1],w = a[i][2];
		addedge(1,v,w),addedge(v,1,w);
	}
	dijkstra(1);
	for(int i=1;i<=k;i++){
		v = a[i][1] , w = a[i][2];
		if(dis[v] < w) ans++;
		if(dis[v] == w){
			if(cnt[v] > 1){
				ans++ , cnt[v]--;
			} 
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Mooncrying (赞：1)

# CF449B Jzzhu and Cities 题解

弱弱地 A 掉这道题之后，看了看没限制题解数目，就发一篇题解庆祝一下吧。
~~（顺便涨估值）~~

### [传送门在这儿](https://www.luogu.com.cn/problem/CF449B)

题目大意翻译已经很清晰了，这里不多赘述了。

为了后面的讲述方便，请允许我姑且将最后插入的 $k$ 条边说成是 K 边。

一个我理解起来比较容易的想法就是：

- 把所有边都存在图里，然后跑一遍 Dijkstra，在更新最短路的过程中看**是否有节点的最短路权值受到 K 边的影响** ，如果有就把这条 K 边标记，同时把该节点标记。

- 如果发现能代替被标记 K 边的更小的非 K 边，就删除标记。

- 有多条 K 边能够影响结果时，取其中的一条即可。

- 最后统计所有没被标记的所有 K 边的数目，输出结果。

然后就没了。

我们直接看代码吧：

```
#include<stdio.h>
#include<vector>
#include<queue>
#include<deque>
using namespace std;
#define ll long long
template <typename T> void read(T &x)
{
	int f=1;x=0;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	x*=f;
}
template <typename T,typename... Args> void read(T &first,Args&...args)
{
	read(first);read(args...);
} //快读
const int N=1e5+10;
struct edge
{
	int to,id;ll w; //注：id 表示边的编号
};vector<edge> vt[N];
//我这里用的是 vector 存图，纯属个人习惯，习惯用前向星的同学可以去食用别的题解
struct Node
{
	int to;ll w;
	bool operator <(const Node &x) const
	{return w>x.w;} //重载运算符，把大根堆变成小根堆
};
priority_queue<Node> q;
int n,m,k,cnt,f[N],ans;ll d[N];
bool vis[N],flag[N];
// vis 数组表示该点是否在已求集合里
// flag 数组用于 K 边是否会影响节点的最短路
//f 数组用来表示节点目前受哪条 K 边的影响最短路发生了改变，如果没有则为 0
int main()
{
	read(n,m,k);cnt=k;
	for(int i=1;i<=m;++i)
	{
		int u,v;ll w;
		read(u,v,w);
		vt[u].push_back((edge){v,++cnt,w});
		vt[v].push_back((edge){u,cnt,w});
	}
	for(int i=1;i<=k;++i)
	{
		int v;ll w;
		read(v,w);
		vt[1].push_back((edge){v,i,w});
		vt[v].push_back((edge){1,i,w});
	} //建边存图
	for(int i=1;i<=n;++i) d[i]=1e16;
	d[1]=0;
	q.push((Node){1,0});
	while(!q.empty())
	{
		int u=q.top().to;
		q.pop();
		if(vis[u]) continue;
		vis[u]=1;f[u]=0;
		int l=vt[u].size();
		for(int p=0;p<l;++p)
		{
			int v=vt[u][p].to;
			ll w=vt[u][p].w;
			int id=vt[u][p].id;
           //两种情况
			if(f[v]>0)
			{
				if(d[v]>=d[u]+w)
				{
					d[v]=d[u]+w;
					if(id>k) flag[f[v]]=0,f[v]=0;
					q.push((Node){v,d[v]});
				} 
			} //如果当前存在一条 K 边影响结果，我们在更新 dis 的时候，只要有一条权值小于等于 K 边权值的边即可代替 K 边
			else
			{
				if(d[v]>d[u]+w)
				{
					d[v]=d[u]+w;
					if(id<=k) f[v]=id,flag[id]=1;
					q.push((Node){v,d[v]});
				}
			} //如果不存在 K 边就正常更新，如果有一条 K 边权值 + d[u] < d[v]，那么这条 K 边就会影响结果，我们把它标记
		}
	} // Dijkstra 跑最短路
	for(int i=1;i<=k;++i) 
		if(!flag[i]) ans++;
	printf("%d\n",ans); //统计答案，输出
	return 0; //完结撒花
}


```

---

## 作者：Bot_wxt1221 (赞：0)

## 题目简述

有一张边带权的无向图，边分成两种，第一种无特殊限制，第二种边有一个端点在 $1$ 号节点，问至多可以删多少条边可以使原图从 $1$ 到所有点的最短路长度不变。

## 分析

很容易注意到需要跑单源最短路，由于题目中要求的是使最短路不变的情况，所以考虑是否可以在最短路过程中 DP 转移下功夫，很明显需要优先从第一种边转移，于是在转移的过程中注意一下转移过去的值相等时如何更新即可，因为最短路的转移过程没有后效性，所以这样转移是正确的。

最后统计没有进行 DP 转移的边的数量即可。

## 代码实现

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#define int long long
inline int read();
int fir[100005];
int nxt[800005];
int v[800005];
int w[800005];
int knd[800005];
int now=0;
bool vised[100005];
class node{
    public:
        int x,y;
        node(int xx,int yy){
            x=xx;
            y=yy;
        }
};
bool operator < (node a,node b){
    return a.y>b.y;
}
std::priority_queue<node>qu;
int from[100005];
int dp[100005];
int used[800005];
void add(int xx,int yy,int zz,int kk){
    now++;
    knd[now]=kk;
    v[now]=yy;
    w[now]=zz;
    nxt[now]=fir[xx];
    fir[xx]=now;
    return ;
}
signed main(){
	#ifdef ONLINE_JUDGE
	#else
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
	#endif
    int n=read(),m,k;
    m=read();
    k=read();
    for(int i=1;i<=n;i++){
        fir[i]=-1;
        dp[i]=0x3f3f3f3f3f3f3f3fll;
    }
    for(int i=1;i<=m;i++){
        int xx=read(),yy,zz;
        yy=read();
        zz=read();
        add(xx,yy,zz,0);
        add(yy,xx,zz,0);
    }
    for(int i=1;i<=k;i++){
        int s=read();
        int y=read();
        add(1,s,y,1);
        add(s,1,y,1);
    }
    dp[1]=0;
    qu.push(node(1,0));
    while(qu.size()>0){
        node noww=qu.top();
        qu.pop();
        int now=noww.x;
        if(vised[now]){
            continue;
        }
        vised[now]=1;
        for(int i=fir[now];i!=-1;i=nxt[i]){
            if(dp[now]+w[i]<dp[v[i]]){
                dp[v[i]]=dp[now]+w[i];
                used[from[v[i]]]=0;
                used[i]=1;
                from[v[i]]=i;
                if(!vised[v[i]])
                    qu.push(node(v[i],dp[v[i]]));
            }else if(dp[now]+w[i]==dp[v[i]]&&knd[from[v[i]]]==1){
                used[from[v[i]]]=0;
                used[i]=1;
                from[v[i]]=i;
            }
        }
    }
    int ans=0;
    for(int i=m*2+1;i<=m*2+k*2;i+=2){
        if(!used[i]&&!used[i+1]){
            ans++;
        }
    }
    printf("%lld",ans);
	return 0;
}
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){
		c=='-'?f=-1:1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+(c^48);
		c=getchar();
	}
	return f*x;
}
/*
Anything about this program:
Type:

Description:

Example:
	1:
		In:

		Out:
More:

*/

```

---

## 作者：Nine_Suns (赞：0)

提供一个不用最短路计数的方法~~因为我不会~~。

由于是无向图，dijkstra 处理出 $1$ 到其他点的最短路，构造出最短路网，由于全是正权边，容易证明这是一个 DAG。

将最多删多少条特殊边转换为最少保留多少特殊边，然后在这个 DAG 上做一遍拓扑排序，按照拓扑序让每个点依次更新它连向的点，如果这条边不是特殊边，就对出点打上标记，当一个点要更新其他点时，如果它仍没有标记，说明此时不存在一条从 $1$ 到它的最短路，将 $cnt$ 加 $1$ 即可。

答案即为 $k-cnt$。

```cpp
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;
const int N = 1e5+5, M = 4e5+5;
typedef long long ll;
typedef pair <ll, int> pli;
int n, m, k, hd[N], ver[M<<1], nxt[M<<1], w[M<<1], idx, d[N], vis[N];
ll dis[N];
vector <pli> e[N];
inline void add (int x, int y, int v) {
	w[++idx] = v;
	ver[idx] = y;
	nxt[idx] = hd[x];
	hd[x] = idx;
}
void dijkstra (int s) {
	priority_queue <pli, vector <pli>, greater <pli> > q;
	memset(dis, 0x3f, sizeof(dis));
	dis[s] = 0; q.push(mp(0, s)); 
	while (q.size()) {
		int t = q.top().second; q.pop();
		if (vis[t]) continue;
		vis[t] = 1;
		for (int i = hd[t];i;i = nxt[i]) {
			int y = ver[i];
			if (dis[y] > dis[t]+w[i]) {
				dis[y] = dis[t]+w[i];
				q.push(mp(dis[y], y));
			}
		}
	}
}

void build () {
	for (int i = 1;i <= n;i++) {
		for (int j = hd[i];j;j = nxt[j]) {
			int y = ver[j];
			if (dis[y] == dis[i]+w[j]) {
				e[i].pb(mp(j > 2*m, y));
				d[y]++;
			}
		}
	}
}
int calc () {
	int res = 0; build(); memset(vis, 0, sizeof(vis));
	queue <int> q;
	for (int i = 1;i <= n;i++) if (!d[i]) q.push(i), vis[i] = 1;
	while (q.size()) {
		int t = q.front(); q.pop();
		if (!vis[t]) res++;
		for (auto i : e[t]) {
			if (!i.first) vis[i.second] = 1;
			d[i.second]--;
			if (!d[i.second]) q.push(i.second);
		}
	}
	return res;
}

int main () {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n >> m >> k;
	for (int i = 1;i <= m;i++) {
		int x, y, c; cin >> x >> y >> c;
		add(x, y, c); add(y, x, c);
	}
	for (int i = 1;i <= k;i++) {
		int y, c; cin >> y >> c;
		add(1, y, c); add(y, 1, c);
	}
//	cout << endl;
	dijkstra(1);
	cout << k-calc();
	return 0;
}
```


---

## 作者：james1BadCreeper (赞：0)

将图搞出来之后跑最短路。如果从起点直达这个点的长度大于到它的最短路，那么删了它没有影响；小于是不可能的；等于呢？

考虑一下，一种是走这个直达路径是得到这个最短路的唯一方式，那么必定不能删。如果不是，则可以删，而且走到这个点的最短路方案数就会减一。然后依次判断所有直达路径即可。

套一个最短路计数就可以解决。

```cpp
#include <bits/stdc++.h>
#define i64 long long
#define pii pair<int, int>
using namespace std;
const int M = 1000000; 

int n, m, k, s[100005], y[100005], cnt[100005]; 
i64 d[100005]; bool v[100005]; 
vector<pii> G[100005]; 
void Dijkstra(void) {
    #define pli pair<i64, int> 
    priority_queue<pli, vector<pli>, greater<pli>> q; 
    memset(d, 0x3f, sizeof d); q.emplace(d[1] = 0, 1); cnt[1] = 1; 
    while (!q.empty()) {
        int u = q.top().second; q.pop(); 
        if (v[u]) continue; v[u] = 1; 
        for (auto [v, w] : G[u]) {
            if (d[v] > d[u] + w) q.emplace(d[v] = d[u] + w, v), cnt[v] = cnt[u]; 
            else if (d[v] == d[u] + w) cnt[v] = min(cnt[v] + cnt[u], M); 
        }
    }
}

int main(void) {
    scanf("%d%d%d", &n, &m, &k); 	
    while (m--) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w); 
        G[u].emplace_back(v, w); G[v].emplace_back(u, w); 
    } 
    for (int i = 1; i <= k; ++i) {
        scanf("%d%d", s + i, y + i); 
        G[1].emplace_back(s[i], y[i]); G[s[i]].emplace_back(1, y[i]); 
    }
    Dijkstra(); int ans = 0; 
    for (int i = 1; i <= k; ++i) {
        if (d[s[i]] < y[i]) ++ans; 
        else if (d[s[i]] == y[i]) {
            if (cnt[s[i]] > 1) ++ans, --cnt[s[i]];
        }
    } printf("%d\n", ans); 
    return 0; 
}
```

---

## 作者：wind_whisper (赞：0)

## $\text{Description}$
$n$ 个点，$m$ 条带权边的无向图，另外还有 $k$ 条特殊边，每条边连接 $1$ 和 $i$ 。 问最多可以删除这$k$ 条边中的多少条，使得每个点到$1$ 的最短距离不变.  
## $\text{Solution}$
我的做法是开两个堆，一个堆是 Dijkstra 正常用的堆，第二个堆存所有特殊边，优先从 dij 的堆转移即可.  
题解的方法是直接维护最短路的条数，感觉更加直观.  
## $\text{Solution}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
//#define double long double
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=3e5+100;
const int mod=1e9+7;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}
int n,m,k;
struct node{
  int to,nxt,w;
}p[N<<1];
int fi[N],cnt;
inline void addline(int x,int y,int w){
  p[++cnt]=(node){y,fi[x],w};fi[x]=cnt;
  return;
}
struct edge{
  int id,val;
  bool operator < (const edge y)const{return val>y.val;}
};
priority_queue<edge>Q;
#define pr pair<ll,int>
#define mkp make_pair
priority_queue<pr,vector<pr>,greater<pr> >q;
ll dis[N];
bool vis[N];
int ans;
void dij(){
  memset(dis,0x3f,sizeof(dis));
  q.push(mkp(0,1));dis[1]=0;
  while(!q.empty()||!Q.empty()){
    int now;
    if(q.empty()||(!Q.empty()&&Q.top().val<q.top().first)){
      now=Q.top().id;int val=Q.top().val;Q.pop();
      if(vis[now]) continue;
      assert(dis[now]>val);
      dis[now]=val;++ans;
    }
    else{now=q.top().second;q.pop();if(vis[now]) continue;}
    vis[now]=1;
    for(int i=fi[now];~i;i=p[i].nxt){
      int to=p[i].to;
      if(dis[to]>dis[now]+p[i].w){
	dis[to]=dis[now]+p[i].w;
	q.push(mkp(dis[to],to));
      }
    }    
  }
  return;
}
int main(){
  #ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  memset(fi,-1,sizeof(fi));
  n=read();m=read();k=read();
  for(int i=1;i<=m;i++){
    int x=read(),y=read(),w=read();
    addline(x,y,w);addline(y,x,w);
  }
  for(int i=1;i<=k;i++){
    edge o={(int)read(),(int)read()};Q.push(o);
  }
  dij();
  printf("%d\n",k-ans);
  return 0;
}
/*
3 3
tsy
*/

```


---

