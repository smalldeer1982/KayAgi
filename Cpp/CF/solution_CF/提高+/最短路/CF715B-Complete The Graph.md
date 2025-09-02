# Complete The Graph

## 题目描述

ZS the Coder has drawn an undirected graph of $ n $ vertices numbered from $ 0 $ to $ n-1 $ and $ m $ edges between them. Each edge of the graph is weighted, each weight is a positive integer.

The next day, ZS the Coder realized that some of the weights were erased! So he wants to reassign positive integer weight to each of the edges which weights were erased, so that the length of the shortest path between vertices $ s $ and $ t $ in the resulting graph is exactly $ L $ . Can you help him?

## 说明/提示

Here's how the graph in the first sample case looks like :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715B/c442fd279761bfa74ef367b518cede1e1fa97983.png)In the first sample case, there is only one missing edge weight. Placing the weight of $ 8 $ gives a shortest path from $ 0 $ to $ 4 $ of length $ 13 $ .

In the second sample case, there is only a single edge. Clearly, the only way is to replace the missing weight with $ 123456789 $ .

In the last sample case, there is no weights to assign but the length of the shortest path doesn't match the required value, so the answer is "NO".

## 样例 #1

### 输入

```
5 5 13 0 4
0 1 5
2 1 2
3 2 3
1 4 0
4 3 4
```

### 输出

```
YES
0 1 5
2 1 2
3 2 3
1 4 8
4 3 4
```

## 样例 #2

### 输入

```
2 1 123456789 0 1
0 1 0
```

### 输出

```
YES
0 1 123456789
```

## 样例 #3

### 输入

```
2 1 999999999 1 0
0 1 1000000000
```

### 输出

```
NO
```

# 题解

## 作者：Spasmodic (赞：23)

好像神仙们都是两次 dijkstra，提供一个二分的做法。

若不连通或者未知边权全部取最小值时 $s\to t$ 的最短路还是大于 $l$，无解。

假设未知边编号分别为 $1,2,\dots,e$。考虑初始时所有边 $i$ 权值为 $x_i=1$，然后重复 $x_1+=1,x_2+=1,…,x_e+=1,x_1+=1,x_2+=1$,… 的操作直到无穷，那么每次最短路的长度至多增加 $1$。

对操作序列二分，总复杂度 $O(m\log n\log(ml))$。

注意二分完了以后还要再判断一下是否无解，否则判不了已经存在一条路径小于 $l$ 的情况。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=1005,M=10005,INF=0x3f3f3f3f3f3f3f3f;
ll n,m,L,s,t,tot,hd[N],a[M],b[M],e;
struct edge{ll t,w,nxt;}es[M<<1];
ll U[M],V[M],W[M];
void add(ll u,ll v,ll w){es[++tot]=(edge){v,w,hd[u]};hd[u]=tot;}
ll d[N];
struct node{ll id,d;bool operator<(const node&x)const{return d>x.d;}};
void dijkstra(ll s){
	priority_queue<node>q;
	memset(d,0x3f,sizeof(d));
	q.push((node){s,0});d[s]=0;
	for(node cur;!q.empty();){
		cur=q.top();q.pop();
		ll u=cur.id;
		if(cur.d>d[u])continue;
		for(ll i=hd[u];i;i=es[i].nxt)
			if(d[es[i].t]>d[u]+es[i].w)
				d[es[i].t]=d[u]+es[i].w,q.push((node){es[i].t,d[es[i].t]});
	}
}
inline ll calc(ll x,ll i){
	ll tms=x/e;
	x-=tms*e;
	if(x>=i)tms++;
	return tms+1;
}
bool ok(ll x){
	for(ll i=1;i<=e;i++)es[a[i]-1].w=es[a[i]].w=calc(x,i);
	dijkstra(s);
	if(d[t]>=L)return 1;
	return 0;
}
int main(){
	scanf("%lld%lld%lld%lld%lld",&n,&m,&L,&s,&t);
	for(ll i=1,u,v,w;i<=m;i++){
		scanf("%lld%lld%lld",&u,&v,&w);
		U[i]=u,V[i]=v,W[i]=w;
		if(!w)a[++e]=tot+2,b[e]=i,w++;
		add(u,v,w),add(v,u,w);
	}
	dijkstra(s);
	if(d[t]==INF||d[t]>L)return puts("NO"),0;
	ll l=0,r=L*m,ans=1;
	while(l<=r){
		ll mid=l+r>>1;
		if(ok(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	if(!ok(ans))return puts("NO"),0;
	puts("YES");
	for(ll i=1;i<=e;i++)W[b[i]]=calc(ans,i);
	for(ll i=1;i<=m;i++)printf("%lld %lld %lld\n",U[i],V[i],W[i]);
	return 0;
}
```

---

## 作者：zhenliu (赞：9)

## **题目简述**
- （渣翻）一个无向图包含从$0$到 $n$-$1$ 的$n$个顶点以及$m$个边，图的每个边都有正整数权值。但一些边权被清除了！因此要重新分配正整数边权给每一个边权被清除的边，以使得顶点$s,t$之间的最短路径的长度是$L$。

- 第一行输入 $n,m,L,s,t$ 分别表示图的点数，边数，修改后的最短路径长度和最短路的起点和终点。

- 接下来m行每行输入$u,v,w$。$u,v$表示边的两个端点，w表示该边权值。如果w=0则表示该边边权被消除了。

- 确保没有重边。

- 输出$“NO”$如果无法使最短路长度为L。
如果可以则第一行输出$“YES”$。
接下来的$m$行应包含修改后图形的边。每行应该包含三个整数$u_i$，$v_i$和$w_i$。未被清除的边权值必须保持不变，而新的边权可以是不超过$10^{18}$的任何正整数。

- 输出中边的顺序无关紧要。$s,t$间最短路长度必须等于$L$。

- 如果有多个解决方案，请输出其中任何一个。

## **思路（两遍dj）**
**1.** 先将所有被消为 $0$ 的边权改为 $1$,跑一边 $dj$,如果 $dis[t]\gt L$则无解。因为每条边必须要有大于等于 $1$ 的边权。赋为 $1$ 超 $L$ 就没办法了。

**2.** 第一遍$dj$的最短路数组为 $dis[][0]$,第二遍为 $dis[][1]$。记 $dif=L-dist[t][0]$，即与 $L$ 相差多少。

**3.** 第二遍跑 $dj$ 时，对于任意 $x\rightarrow y$,如果满足 $dis[x][1]+w<dis[y][0]+dif$，

那么更新 $w=dis[y][0]+dif-dis[x][1]$，这样就能使更新后的最短路长度为 $L$。


------------


**注：**

1.蒟蒻 zhenliu一开始没想明白为什么更新 $w$ 就能使更新后的最短路长度为 $L$。

机房大佬一言点会：“因为你**每个满足这个条件的**都更新，那么最短路肯定最后就是 $L$了呗！如果这样都不是 $L$那就输出 $NO$呗！”

2.这题不用堆优化就能过，虽然我用了。。。


------------


## **code（有注释版）**
```c
#include<bits/stdc++.h>
#define RI register int
using namespace std;
typedef pair<int,int> PII;
const int maxn=10002,maxm=20002;
int head[maxn],to[maxm],nxt[maxm],len[maxm],vis[maxn],zero[maxm],from[maxm],dis[maxn][2];
int n,m,L,s,t,u,v,w,dif,tot=1;
priority_queue<PII,vector<PII>,greater<PII> >que;
template<typename T> void Read(T &t){
	t=0;char c;int f=1;
	while((c=getchar())<'0'||c>'9')if(c=='-')f=-1;
	while(c>='0'&&c<='9')(t*=10)+=c-'0',c=getchar();
	t*=f;
}
void add_edge(int x,int y,int w,int z){
	to[++tot]=y;
	zero[tot]=z; 
	nxt[tot]=head[x];
	len[tot]=w+z;
	from[tot]=x;
	head[x]=tot;
}
void dijkstra(int k){
	memset(vis,0,sizeof(vis));
	for(RI i=0;i<n;i++){//是0到n-1啊…… 
		dis[i][k]=0x3f3f3f3f;
	}
	dis[s][k]=0;
	que.push(make_pair(0,s));
	while(!que.empty()){
		int x=que.top().second;
		que.pop();
		if(vis[x])continue;
		vis[x]=1; 
		for(RI i=head[x];i;i=nxt[i]){
			int y=to[i];
			if(k==1){//第二遍dj特殊处理 
				if(zero[i]&&dis[x][1]+len[i]<dis[y][0]+dif)
					len[i^1]=len[i]=dis[y][0]+dif-dis[x][1];
			}
			if(dis[y][k]>dis[x][k]+len[i]){
				dis[y][k]=dis[x][k]+len[i];
				que.push(make_pair(dis[y][k],y));
			}
		}
	} 
}
int main(){
	Read(n);
	Read(m);
	Read(L);
	Read(s);
	Read(t);
	for(RI i=1;i<=m;++i){
		Read(u);
		Read(v);
		Read(w);
		add_edge(u,v,w,!w);//!w判断w是否为0，为0则传入1 ，方便后面dj判断zero数组来判断初始边权是否为0 
		add_edge(v,u,w,!w); 
	}
	dijkstra(0);//第一次正常的dijkstra  
	if(dis[t][0]>L){//因为每条边必须有权值，如果边权赋为1都超L了，那么无解 
		puts("NO");
		return 0;
	}
	dif=L-dis[t][0];//difference表示与L差多少 
	dijkstra(1);//第二次尝试加权值为L的dijkstra
	if(dis[t][1]!=L){
		puts("NO");
	} 
	else{
		puts("YES");
		for(RI i=2;i<=tot;i+=2){
			printf("%d %d %d\n",from[i],to[i],len[i]);//输出端点和权值，因为是无向图，所以i每次+2 
		}
	}
	return 0;
}
```


------------

[无注释清爽版code](https://www.luogu.com.cn/paste/ueq7netd)

 ##### 第一次提交题解，有错误欢迎大佬们在评论区提出！！
 

------------


**TAHANKS FOR WATCHING**





---

## 作者：Saber_Master (赞：8)


[CF715B Complete The Graph](https://www.luogu.com.cn/problem/CF715B)

我们用$dis[i][j]$表示到点$i$经过$j$条零边的最短路，然后找到最小的$j$使得$dis[T][j]+j<=L$并将这条路径给赋值搞成$L$，然后将其它零边赋值$L$即可.

容易证明这个策略是正确的

```cpp

const ll N=1.5e3+3, M=2e5+4;

ll head[M], to[M<<1], next[M<<1], tot=1, c[M<<1];
inline void add(ll x, ll y, ll z){
	to[++tot]=y; next[tot]=head[x]; head[x]=tot; c[tot]=z;
}
inline void Link(ll x, ll y, ll z){
	add(x, y, z); add(y, x, z);
}

ll n, m;
ll L, S, T;

ll dis[N][N], pre[N][N];

bool vis[N*N];
//queue<pair<ll, ll> >q;
priority_queue<pair<ll, ll>, vector<pair<ll, ll> > ,greater<pair<ll, ll> > > q;
inline void dijkstra(){
	for (R ll i=1; i<=n; i++)
		for (R ll j=0; j<n; j++) dis[i][j]=inf;
	dis[S][0]=0;
	q.push(make_pair(0, (S-1)*n+1));
	while(!q.empty())
    {
        ll now=q.top().second;q.pop();
        ll x=(now-1)/n+1, y=(now-1)%n;
        if(vis[now]) continue; vis[now]=true;
        for (R ll i=head[x], ver; i; i=next[i]){
        	ver=to[i];
        	ll ny=y+(c[i]==0), id=(ver-1)*n+ny+1;
        	if (dis[ver][ny]>dis[x][y]+c[i]){
        		dis[ver][ny]=dis[x][y]+c[i];
        		q.push(make_pair(dis[ver][ny], id));
        		pre[ver][ny]=i;
			}
		}
    }
}

bool flag;
inline void dfs(ll x, ll y, ll D){
	ll i=pre[x][y];
	if (x==S) return;
	if (c[i]==0){
		--y;
		if (!flag){
			flag=true;
			c[i]=c[i^1]=D;
		}else c[i]=c[i^1]=1;
	}
	dfs(to[i^1], y, D);
}

inline bool solve(){
	if (dis[T][0]<L) return false;
	if (dis[T][0]==L) return true;
	for (R ll i=1; i<n; i++)
		if (dis[T][i]+i<=L) return dfs(T, i, L-dis[T][i]-i+1), true;
	return false;
}

int main(){
	read(n); read(m); read(L); read(S); read(T); ++S; ++T;
	for (R ll i=1, x, y, z; i<=m; i++){
		read(x); read(y); read(z);
		++x; ++y;
		Link(x, y, z);
	}
//	spfa();
	dijkstra();
	if (!solve()) return puts("NO"), 0;
	puts("YES");
	for (R ll i=2; i<=tot; i+=2){
		if (!c[i]) c[i]=L;
		writesp(to[i^1]-1); writesp(to[i]-1); writeln(c[i]);
	}
	return 0;
}
```

---

## 作者：Zimo_666 (赞：6)

## [CF715B] Complete The Graph

### Description

给 $n$ 点 $m$ 边，要求你修改 $m$ 条边中边权为 $0$ 的边， 使满足 $S\to T$ 的最短路长度是 $L$，且输出答案的时候边为 $0$ 的边的权值必须在 $[1,1\times 10^{18}]$ 内。

### Solution

我们考虑一个暴力做法，即首先我们把边权不为 $0$ 的边的编号存进一个 vector 内，考虑仅在图中存边权不为 $0$ 的边。而后我们跑 $S\to T$ 的最短路极为 $dis_t$，我们考虑加边对这样一个 $dis_t$ 的影响，即只会使得 $dis_t$ 变小或不变。而后我们考虑若 $dis_t<L$ 则显然不合法输出 `NO`，若 $dis_t=L$ 则我们不希望边权为 $0$ 的边对这张已经合法的图有任何影响，则所有边权为 $0$ 的边权值改为极大值即可。

而后我们考虑 $dis_t>L$ 的情况。首先，若最短路变化了那么证明从 $S$ 到 $T$ 的最短路经过该边，于是我们可以通过以下方式来使得最短路恰好等于 $L$。

而后我们考虑不断枚举边权为 $0$ 的并且把其边权设为 $1$ 并加入图中，这样可以使得最短路尽可能短（此时尽可能短直到 $dis_t<L$ 时考虑修改权值，并不代表一直使最短路尽可能短，换言之这样的策略是找到一条**关键边**使得 $S$ 到 $T$ 的最短路恰好满足情况），那么我们考虑对于每次枚举跑一次最短路，若此时 $dis_t<L$，那么显然这种情况是不合法的，我们考虑把它补到 $L-dis_t$。此时恰好使得当前图合法，因而其他没枚举到的边不需要不能影响该图的最短路，因而和上面一样赋值为极大值即可。

这种贪心的思路足够通过本题。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
const int N=5e4+7;
vector<pair<int,int> > G[N];
vector<int> vec;
int dis[N<<2];
bool _vis[N<<2];
int n,m;
int u[N],v[N],w[N];
const int inf=1e18;
int p,l,s,t;

struct node{
	int dis,id;
	friend bool operator < (node a,node b){
		return a.dis>b.dis;
	}
};

void Dj(int s){
	memset(_vis,0,sizeof _vis);
	priority_queue<node> q;
	memset(dis,0x3f,sizeof dis);
	dis[s]=0;
	q.push({0,s});
	while(!q.empty()){
		int u=q.top().id;
		q.pop();
		if(_vis[u]) continue;
		_vis[u]=1;
		for(auto i:G[u]){
			int k=i.first,w=i.second;
			if(dis[k]>dis[u]+w){
				dis[k]=dis[u]+w;
				q.push({dis[k],k});
			}
		}
	}
}

void print()
{
	puts("YES");
	for(int i=1;i<=m;i++){
		if(!w[i]){
			if(i<p)
			printf("%lld %lld %lld\n",u[i],v[i],1ll);
			if(i==p)
			printf("%lld %lld %lld\n",u[i],v[i],l-dis[t]+1);
			if(i>p)
			printf("%lld %lld %lld\n",u[i],v[i],inf);
		}
		else printf("%lld %lld %lld\n",u[i],v[i],w[i]);
	}
}

signed main(){
  scanf("%lld%lld%lld%lld%lld",&n,&m,&l,&s,&t);
  for(int i=1;i<=m;i++){
    scanf("%lld%lld%lld",&u[i],&v[i],&w[i]);
    if(!w[i]){vec.push_back(i);continue;}
    G[u[i]].push_back(make_pair(v[i],w[i]));G[v[i]].push_back(make_pair(u[i],w[i]));
  }
  Dj(s);
//  printf("dis[t]=%d\n",dis[t]);
  if(dis[t]<l) return printf("NO\n"),0;
  if(dis[t]==l){
    printf("YES\n");
    for(int i=1;i<=m;i++){
      printf("%lld %lld %lld\n",u[i],v[i],w[i]==0?inf:w[i]);
    }
    return 0;
  }
  for(int i:vec){
    G[u[i]].push_back(make_pair(v[i],1));
    G[v[i]].push_back(make_pair(u[i],1));
    Dj(s);
		if(dis[t]>l) continue;
		p=i;
		print();
		return 0;
  }
  puts("NO");
  return 0;
}
```



---

## 作者：cjlak1o1 (赞：3)

~~麻了麻了，写了好久。~~

#### 一. $n$ 次 dijkstra

由于可能存在很多 $0$ 边，所以只把最短路上的 $0$ 边修改值是不对的，所以打算跑 $n$ 次最短路求解。显然，它挂了。

#### 二. 一次 dijkstra

第一次找到最短路，然后把该路径上的 $0$ 边改为正确值，其他的全部赋值为极大值。但是仍然可能会出现两条路共用 $0$ 边的情况，所以它又挂了。

#### 三. 两次 dijkstra

- 第一遍将所有的 $0$ 边赋值为 $1$，跑一遍 dijsktra，判断最短路是否大于 $l$，大于则无解。

- 第二遍跑出最短路。并且反过来 dfs 将会与其他的路共用的 $0$ 边赋上与 $l$ 差的平均值。

然后很好，很快我就发现这样仍然不能阻挡最短路可能更换。于是它又双叒叕挂了......

#### 四. 两次 dijkstra

请教大佬后，终于明白了做法。

- 第一遍将所有的 $0$ 边赋值为 $1$，跑一遍 dijsktra，判断是否无解，记录 $diss$ 为最短路长度和 $l$ 的差值。

- 第二遍跑最短路，为确保最短路为 $l$，每次遇到 $0$ 边时，若此时最短路小于 $dis[v][0]+diss$，那么将每条路至少上涨至 $l$，又保证有情况存在，最后判断 $dis[t][1]$ 是否为 $l$ 后输出即可。

代码就不放了，其他巨佬的码风好看多了。

**蒟蒻拙见，请指教。**

---

## 作者：SmallTownKid (赞：3)

可能是最慢的做法，但最好理解。

首先明白一个性质：如果新加这条边后最短距离变化了，说明这条边一定用到了。

我们先不考虑 $0$ 边，用所有有边权的边建图，跑最短路，如果此时最短距离小于 $L$ ，那么一定无解。$0$ 边的数值不会增加此时的最短距离，不经过就可以了。

如果此时最短距离等于 $L$ ，直接把 $0$ 边全设为无穷大就行了，当做没有。

如果此时最短距离大于 $L$，那么考虑贪心，不断加入 $0$ 边并且将 $0$ 边的边权设为 $1$ ，这样可以使得最短距离尽可能短。但如果加入了一条边权为 $1$ 的边后最短距离小于了 $L$ 怎么办呢？就把这条边的值增大 $(L-dis[t])$ ，也就是少出来的把它补上就行。剩下没加入的 $0$ 边看作不存在，赋无穷大即可。

时间复杂度 $O(k*mlogn)$ ，$k$ 为常数。

```
#include<bits/stdc++.h>
#define int long long
const int INF=1e18;
using namespace std;
int n,m,L,s,t,idx,p;
int head[10010],u[10010],v[10010],w[10010];
int dis[10010],vis[10010];
struct node{
	int nxt,to,w;
}edge[200010];
vector<int> g;
void add(int u,int v,int w)
{
	edge[++idx].nxt=head[u];
	edge[idx].to=v;
	edge[idx].w=w;
	head[u]=idx;
}
void dijkstra(int s)
{
	for(int i=0;i<=n;i++)
	{
		dis[i]=INF;
		vis[i]=0;
	}
	priority_queue< pair<int,int> > q;
	q.push(make_pair(0,s));
	dis[s]=0;
	while(q.size())
	{
		int x=q.top().second;
		q.pop();
		if(vis[x])
		continue;
		vis[x]=1;
		for(int i=head[x];i;i=edge[i].nxt)
		{
			int y=edge[i].to;
			if(dis[x]+edge[i].w<dis[y])
			{
				dis[y]=dis[x]+edge[i].w;
				q.push(make_pair(-dis[y],y));
			}
		}
	}
}
void print()
{
	puts("YES");
	for(int i=1;i<=m;i++)
	{
		if(w[i]==0)
		{
			if(i<p)
			printf("%lld %lld %d\n",u[i],v[i],1);
			if(i==p)
			printf("%lld %lld %lld\n",u[i],v[i],L-dis[t]+1);
			if(i>p)
			printf("%lld %lld %lld\n",u[i],v[i],INF);
		}
		else printf("%lld %lld %lld\n",u[i],v[i],w[i]);
	}
}
signed main()
{
	cin>>n>>m>>L>>s>>t;
	for(int i=1;i<=m;i++)
	{
		scanf("%lld%lld%lld",&u[i],&v[i],&w[i]);
		if(w[i]==0)
		{
			g.push_back(i);//边标号 
			continue;
		}
		add(u[i],v[i],w[i]);
		add(v[i],u[i],w[i]);
	}
	dijkstra(s);
	if(dis[t]<L)
	{
		puts("NO");
		return 0;
	}
	if(dis[t]==L)
	{
		puts("YES");
		for(int i=1;i<=m;i++)
		{
			if(!w[i])
			printf("%lld %lld %lld\n",u[i],v[i],INF);
			else printf("%lld %lld %lld\n",u[i],v[i],w[i]);
		} 
		return 0;
	}
	if(dis[t]>L)//
	{
		for(int i=0;i<g.size();i++)
		{
			add(u[g[i]],v[g[i]],1);//加1边
			add(v[g[i]],u[g[i]],1);
			dijkstra(s);
			if(dis[t]>L)
			continue;
			if(dis[t]<=L)
			{
				p=g[i];//这是第几条边 
				print();
				return 0;
			}
		}
	}
	puts("NO");
	return 0;
}

---

## 作者：phmaprostrate (赞：2)

## 题意
给定 $n$ 个点 $m$ 条边的无向图，请你修改其中边权为 $0$ 的边，使得 $s$ 到 $t$ 的最短路径长为 $l$ 其中边权范围为 $1 \le w \le 10^{18}$.
## 分析
首先，建边的顺序明显对答案没有影响，我们就可以先把边权不为 $0$ 的边建出来，跑一遍最短路。然后，再进行分类讨论。设 $d[i]$ 为 $s$ 到 $i$ 的最短路径长度。 

1. $d[t] < l$ 此情况必定无解，因为在不建边权为 $0$ 的边的情况下，这个点可以到达，那建完边权为 $0$ 的边后，依然可以到达，且仍小于 $l$.这是建边权为 $0$ 的边只能将最短路减小，所以一定无解。

2. $d[t] == l$ 必定有解，同样的 $t$ 一定在没建边权为 $0$ 之前的路径中，只需要把边权为 $0$ 的设为正无穷即可。

3. $d[t] == INF$ 相当于 $d[t] > l$ 与第四种情况一起考虑。

4. $d[t] > l$ 考虑每次加一条边，因为一次性全加上，就不知道图的情况，无法赋边权。每次建一条边权为 $0$ 的边，把边权赋为 $1$ ，跑最短路，发现如果 $d[t] < l$ 了，说明这条边在通往 $t$ 的路径上，就把边权重新赋为 $l - d[t] + 1$ 这样跑到这个点就恰好为 $l$ 了。剩下的边赋为正无穷即可。

最后要注意，开始是从 $0$ 号点开始的，先把编号加 $1$ 输出时再减去即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 10;
const int INF = 1e18 + 1;
int n,m,l,s,t;
int id[N],cnt = 0;
struct node {
	int from,to,w;
} a[N];
struct ndoe {
	int to,next,w;
} tr[N];
int h[N],k = 0;
int d[N],vis[N],in[N];
queue<int> q;
void add(int from,int to,int w) {
	tr[++k].to = to;
	tr[k].next = h[from];
	tr[k].w = w;
	h[from] = k;
}
void spfa() {
	for(int i = 1 ; i <= n ; i ++) d[i] = INF,vis[i] = false,in[i] = 0;
	q.push(s),d[s] = 0,vis[s] = true;
	while(!q.empty()) {
		int u = q.front();
		q.pop(),vis[u] = false;
		for(int i = h[u] ; ~i ; i = tr[i].next) {
			int y = tr[i].to;
			if(d[y] > d[u] + tr[i].w) {
				d[y] = d[u] + tr[i].w;
				if(!vis[y]) {
					vis[y] = true;
					q.push(y);
					if(++ in[y] > N) return;
				}
			}
		}
	}
}
signed main() {
	memset(h,-1,sizeof(h));
	cin >> n >> m >> l >> s >> t;
	s++,t++;
	for(int i = 1 ; i <= m ; i ++) cin >> a[i].from >> a[i].to  >> a[i].w,a[i].from++,a[i].to++;
	for(int i = 1 ; i <= m ; i ++) {
		if(a[i].w == 0) {
			id[++cnt] = i;
		} else add(a[i].from,a[i].to,a[i].w),add(a[i].to,a[i].from,a[i].w);
	}
	spfa();
	if(d[t] < l) {
		cout << "No";
		return 0;
	} else if(d[t] == l) {
		cout << "Yes"<<endl;
		for(int i = 1 ; i <= m ; i ++) {
			cout << a[i].from - 1<<" "<< a[i].to - 1<<" ";
			if(a[i].w == 0) cout << INF - 1 << endl;
			else cout << a[i].w << endl;
		}
		return 0;
	} else if(d[t] > l) {
		for(int i = 1 ; i <= cnt ; i ++) {
			a[id[i]].w = 1;
			add(a[id[i]].from,a[id[i]].to,1),add(a[id[i]].to,a[id[i]].from,1);
			spfa();
			if(d[t] > l) continue;
			if(d[t] <= l) {
				cout << "Yes"<<endl;
				a[id[i]].w =  l - d[t] + 1;
				for(int i = 1 ; i <= m ; i ++) {
					cout << a[i].from - 1<<" " <<a[i].to - 1 <<" ";
					if(a[i].w == 0) cout <<INF - 1 << endl;
					else cout << a[i].w << endl;
				}
				return 0;
			}

		}
	}

	cout << "No";
	return 0;
}
```


---

## 作者：phmaprostrate (赞：0)

## 题意
给定 $n$ 个点 $m$ 条边的无向图，请你修改其中边权为 $0$ 的边，使得 $s$ 到 $t$ 的最短路径长为 $l$ 其中边权范围为 $1 \le w \le 10^{18}$.
## 分析
首先，建边的顺序明显对答案没有影响，我们就可以先把边权不为 $0$ 的边建出来，跑一遍最短路。然后，再进行分类讨论。设 $d[i]$ 为 $s$ 到 $i$ 的最短路径长度。 

1. $d[t] < l$ 此情况必定无解，因为在不建边权为 $0$ 的边的情况下，这个点可以到达，那建完边权为 $0$ 的边后，依然可以到达，且仍小于 $l$.这是建边权为 $0$ 的边只能将最短路减小，所以一定无解。

2. $d[t] == l$ 必定有解，同样的 $t$ 一定在没建边权为 $0$ 之前的路径中，只需要把边权为 $0$ 的设为正无穷即可。

3. $d[t] == INF$ 相当于 $d[t] > l$ 与第四种情况一起考虑。

4. $d[t] > l$ 考虑每次加一条边，因为一次性全加上，就不知道图的情况，无法赋边权。每次建一条边权为 $0$ 的边，把边权赋为 $1$ ，跑最短路，发现如果 $d[t] < l$ 了，说明这条边在通往 $t$ 的路径上，就把边权重新赋为 $l - d[t] + 1$ 这样跑到这个点就恰好为 $l$ 了。剩下的边赋为正无穷即可。

最后要注意，开始是从 $0$ 号点开始的，先把编号加 $1$ 输出时再减去即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 10;
const int INF = 1e18 + 1;
int n,m,l,s,t;
int id[N],cnt = 0;
struct node {
	int from,to,w;
} a[N];
struct ndoe {
	int to,next,w;
} tr[N];
int h[N],k = 0;
int d[N],vis[N],in[N];
queue<int> q;
void add(int from,int to,int w) {
	tr[++k].to = to;
	tr[k].next = h[from];
	tr[k].w = w;
	h[from] = k;
}
void spfa() {
	for(int i = 1 ; i <= n ; i ++) d[i] = INF,vis[i] = false,in[i] = 0;
	q.push(s),d[s] = 0,vis[s] = true;
	while(!q.empty()) {
		int u = q.front();
		q.pop(),vis[u] = false;
		for(int i = h[u] ; ~i ; i = tr[i].next) {
			int y = tr[i].to;
			if(d[y] > d[u] + tr[i].w) {
				d[y] = d[u] + tr[i].w;
				if(!vis[y]) {
					vis[y] = true;
					q.push(y);
					if(++ in[y] > N) return;
				}
			}
		}
	}
}
signed main() {
	memset(h,-1,sizeof(h));
	cin >> n >> m >> l >> s >> t;
	s++,t++;
	for(int i = 1 ; i <= m ; i ++) cin >> a[i].from >> a[i].to  >> a[i].w,a[i].from++,a[i].to++;
	for(int i = 1 ; i <= m ; i ++) {
		if(a[i].w == 0) {
			id[++cnt] = i;
		} else add(a[i].from,a[i].to,a[i].w),add(a[i].to,a[i].from,a[i].w);
	}
	spfa();
	if(d[t] < l) {
		cout << "No";
		return 0;
	} else if(d[t] == l) {
		cout << "Yes"<<endl;
		for(int i = 1 ; i <= m ; i ++) {
			cout << a[i].from - 1<<" "<< a[i].to - 1<<" ";
			if(a[i].w == 0) cout << INF - 1 << endl;
			else cout << a[i].w << endl;
		}
		return 0;
	} else if(d[t] > l) {
		for(int i = 1 ; i <= cnt ; i ++) {
			a[id[i]].w = 1;
			add(a[id[i]].from,a[id[i]].to,1),add(a[id[i]].to,a[id[i]].from,1);
			spfa();
			if(d[t] > l) continue;
			if(d[t] <= l) {
				cout << "Yes"<<endl;
				a[id[i]].w =  l - d[t] + 1;
				for(int i = 1 ; i <= m ; i ++) {
					cout << a[i].from - 1<<" " <<a[i].to - 1 <<" ";
					if(a[i].w == 0) cout <<INF - 1 << endl;
					else cout << a[i].w << endl;
				}
				return 0;
			}

		}
	}

	cout << "No";
	return 0;
}
```


---

## 作者：nofind (赞：0)

题意:https://www.luogu.org/problem/CF715B

因为边权[1,1e18],因此先将所有未赋值的边权调为1,跑一边最短路,如果dis[t]>L则无解,因为加边权不可能使最短路变小

记录diff=L-dis[t],记第二遍最短路的数组为diss,考虑使得更新diss[t]的diss[x]=dis[x]+diff,这样就可以更新出diss[t]=L

于是考虑使得所有的点x,diss[x]=dis[x]+diff

于是对于x->y这条边,如果dis[y]+diff>diss[x]+w（这是为了让边权不为负数）,w=dis[y]+diif-diss[x],这样如果更新,diss[y]=dis[y]+diff

总结:

对于限制最短路为多少的问题:考虑更新它的点

code:
```
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define mp make_pair
#define fir first
#define sec second
const int maxn=1010;
const int maxm=10010;
int n,m,L,S,T,cnt,diff;
int head[maxn],u[maxm],v[maxm],w[maxm],dis[maxn],diss[maxn];
bool check[maxm],vis[maxn];
struct edge
{
    int to,nxt,id;
}e[maxm<<1];
inline int read()
{
    char c=getchar();int res=0,f=1;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9')res=res*10+c-'0',c=getchar();
    return res*f;
}
inline void add(int u,int v,int id)
{
    e[++cnt].nxt=head[u];
    head[u]=cnt;
    e[cnt].to=v;
    e[cnt].id=id;
}
inline void spfa1()
{
	memset(dis,0x3f,sizeof(dis));
	queue<int>q;
	q.push(S);dis[S]=0;vis[S]=1;
	while(!q.empty())
	{
		int x=q.front();q.pop();vis[x]=0;
		for(int i=head[x];i;i=e[i].nxt)
		{
			int y=e[i].to;
			if(dis[y]>dis[x]+w[e[i].id])
			{
				dis[y]=dis[x]+w[e[i].id];
				if(!vis[y])vis[y]=1,q.push(y);
			}
		}
	}
}
inline void spfa2()
{
	memset(diss,0x3f,sizeof(diss));
	queue<int>q;
	diss[S]=0;q.push(S);vis[S]=1;
	while(!q.empty())
	{
		int x=q.front();q.pop();vis[x]=0;
		for(int i=head[x];i;i=e[i].nxt)
		{
			int y=e[i].to;
			if(check[e[i].id]&&dis[y]+diff>diss[x]+w[e[i].id])w[e[i].id]=dis[y]+diff-diss[x];
			if(diss[y]>diss[x]+w[e[i].id])
			{
				diss[y]=diss[x]+w[e[i].id];
				if(!vis[y])vis[y]=1,q.push(y);
			}
		}
	}
}
int main()
{
    n=read(),m=read();L=read(),S=read(),T=read();
    for(int i=1;i<=m;i++)
    {
        u[i]=read(),v[i]=read(),w[i]=read();
    	if(!w[i])w[i]=1,check[i]=1;
	    add(u[i],v[i],i);add(v[i],u[i],i);
    }   
	spfa1();
	if(dis[T]>L){puts("NO");return 0;}
	diff=L-dis[T];
	spfa2();
	if(diss[T]!=L){puts("NO");return 0;}
	else 
	{
		puts("YES");
		for(int i=1;i<=m;i++)printf("%d %d %d\n",u[i],v[i],w[i]);
	}
	return 0;
}
```




---

## 作者：liuyifan (赞：0)

## 两次Dijstra
### 1.思路
首先把所有未赋值的边初始化为1，然后第一次dijkstra求出每个点到s的最短路长度，如果dist[t]>L则无解，否则记下dist[t]与L的差值need，然后第二次dijkstra，对于未赋值的边(u,v)，如果能够用dist2[u]+这条边权来更新dist2[v]，那么就可以把这条边的权值赋为原dist[v]+need-dist2[u]，使得更新后的dist2[v]=dist[v]+need。最后判断dist[t]的值是否为L 
### 2.复杂度
时间复杂度O(n*(logn+logm))
### 3.完整代码
```cpp
//本程序有反复制处理,思路正确,但复制不能AC
// luogu-judger-enable-o2
#include<bits/stdc++.h>
#define reg register 
#define ll long long
#define y1 liuifan_y1 
#define inf 0x3f3f3f3f
#define iinf 0x3f3f3f3f3f3f3f3f 
#define data liuyifan_data 
#define next liuyifan_next 
#define ture true 
#define flase false 
#define lowbit(x) x&(-x)
using namespace std;
int a[10005],b[10005],vv[10005],to[20005],next[20005],e[20005],f[1005],dis[1005],diss[1005],u[1005],v[10005],n,m,l,s,t,tot,nexted;
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
//pair是一种特殊的结构体,由两个元素first,second组成
//注意本行中的空格写法,不加空格会CE
inline void add(reg int x,reg int y,reg int z)//新建一条从X到Y长度为Z的边
{
    to[++tot]=y;
	e[tot]=z;
	next[tot]=f[x];
	f[x]=tot;
}//前向星加边
inline void dijkstra()//第一次Dijstra
{
    for(reg int i=0;i<n;i++)dis[i]=inf,u[i]=1;
    dis[s]=0;
	q.push(pair<int,int>(0,s));
    while(!q.empty())
    {
        reg int x=q.top().second;
        q.pop();
        if(!u[x])continue;
        u[x]=0;
        for(reg int i=f[x];i;i=next[i])
        if(dis[x]+vv[e[i]]<dis[to[i]])
        {
            dis[to[i]]=dis[x]+vv[e[i]];
            q.push(pair<int,int>(dis[to[i]],to[i]));
        }
    }
}
inline void dijkstra2()//第二次Dijstra
{
    for(reg int i=0;i<n;i++)diss[i]=inf,u[i]=1;
    diss[s]=0;
	q.push(pair<int,int>(0,s));
    while(!q.empty())
    {
        reg int x=q.top().second;
        q.pop();
        if(!u[x])continue;
        u[x]=0;
        for(reg int i=f[x];i;i=next[i])
        {
            if(v[e[i]]&&diss[x]+vv[e[i]]<dis[to[i]]+nexted)vv[e[i]]=dis[to[i]]+nexted-diss[x];//松弛操作
            if (diss[x]+vv[e[i]]<diss[to[i]])
            {
                diss[to[i]]=diss[x]+vv[e[i]];
                q.push(pair<int,int>(diss[to[i]],to[i]));
            }
        }
    }
}
//对Dijstra算法不熟悉的同学可以参照P3371和P4779的有关题解
//本题的数据范围不需要堆优化,O(n^2)可以了
int main()
{
    scanf("%d%d%d%d%d",&n,&m,&l,&s,&t);
    for(reg int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&a[i],&b[i],&vv[i]);
        if(!vv[i])v[i]=vv[i]=1;
        add(a[i],b[i],i);
		add(b[i],a[i],i);//建边
    }
    dijkstra();//第一次Dijstra
    if(dis[t]>l)return puts("N0"),0;//不满足,直接退出程序
    //逗号表达式的返回值以最后一个表达式为准
    nexted=l-dis[t];
    dijkstra2();//第二次Dijstra
    if(diss[t]!=l)puts("N0");//不满足
    else
    {
        puts("YE5");
        for(reg int i=1;i<=m;i++)printf("%d %d %d\n",a[i],b[i],vv[i]);
    }//输出对应边长
    return 0;//结束程序
}
```

---

