# Missile Silos

## 题目描述

A country called Berland consists of $ n $ cities, numbered with integer numbers from $ 1 $ to $ n $ . Some of them are connected by bidirectional roads. Each road has some length. There is a path from each city to any other one by these roads. According to some Super Duper Documents, Berland is protected by the Super Duper Missiles. The exact position of the Super Duper Secret Missile Silos is kept secret but Bob managed to get hold of the information. That information says that all silos are located exactly at a distance $ l $ from the capital. The capital is located in the city with number $ s $ .

The documents give the formal definition: the Super Duper Secret Missile Silo is located at some place (which is either city or a point on a road) if and only if the shortest distance from this place to the capital along the roads of the country equals exactly $ l $ .

Bob wants to know how many missile silos are located in Berland to sell the information then to enemy spies. Help Bob.

## 说明/提示

In the first sample the silos are located in cities $ 3 $ and $ 4 $ and on road $ (1,3) $ at a distance $ 2 $ from city $ 1 $ (correspondingly, at a distance $ 1 $ from city $ 3 $ ).

In the second sample one missile silo is located right in the middle of the road $ (1,2) $ . Two more silos are on the road $ (4,5) $ at a distance $ 3 $ from city $ 4 $ in the direction to city $ 5 $ and at a distance $ 3 $ from city $ 5 $ to city $ 4 $ .

## 样例 #1

### 输入

```
4 6 1
1 2 1
1 3 3
2 3 1
2 4 1
3 4 1
1 4 2
2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5 6 3
3 1 1
3 2 1
3 4 1
3 5 1
1 2 6
4 5 8
4
```

### 输出

```
3
```

# 题解

## 作者：npqenqpve (赞：5)

### 思路：
天真的想法是把每条边上都建上 $w-1$ 个点然后跑最短路
但是边权总和很大，显然不能这么做。

考虑对原图求单源最短路，记 $s$ 到 $u$ 的最短路为 $d_u$，可以直接统计在点上的答案。

考虑如何统计在边上的答案，显然每条边至多有 $2$ 个。

记这个边的两端是 $u$，$v$，那么分类讨论从 $u$ 走过去还是从 $v$ 走过去，假设从 $u$ 走，显然需要往边里走 $l-d_u$，那么这个位置走到 $v$ 再走到 $s$ 的距离是 $w-l+d_u+d_v$，判断是否大于 $l$ 即可。

注意考虑边上只有一个点的情况，也就是往那边走都是 $l$。 

### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node
{
	int to,v;
	bool operator<(const node &o) const
	{
		return v>o.v;
	}
};
int x[(int)(1e5+10)],y[(int)(1e5+10)],w[(int)(1e5+10)];
int dis[(int)(1e5+10)],n,s,m;
vector<node>edge[(int)(1e5+10)];
priority_queue<node>q;
bool v[(int)(1e5+10)];
signed main()
{
	cin>>n>>m>>s;
	for(int i=1;i<=n;i++) dis[i]=INT_MAX;
	for(int i=1;i<=m;i++)
	{
		int u,v,d;cin>>u>>v>>d;
		x[i]=u,y[i]=v,w[i]=d;
		edge[u].push_back((node){v,d});
		edge[v].push_back((node){u,d});
	}
	dis[s]=0;
	q.push((node){s,0});
	while(q.size())
	{
		int u=q.top().to;
		q.pop();
		if(v[u]) continue;
		v[u]=1;
		for(int i=0;i<edge[u].size();i++)
		{
			if(dis[edge[u][i].to]>dis[u]+edge[u][i].v)
			{
				dis[edge[u][i].to]=dis[u]+edge[u][i].v;
				q.push((node){edge[u][i].to,dis[edge[u][i].to]});
			}
		}
	}
	int cnt=0,l;
	cin>>l;
	for(int i=1;i<=n;i++)
	{
		cnt+=(dis[i]==l);
	}
	for(int i=1;i<=m;i++)
	{
		if(dis[x[i]]+w[i]-l+dis[y[i]]==l&&dis[y[i]]<l&&dis[x[i]]<l)
		{
//			cout<<"case 1: "<<i<<"\n";
			cnt++;
			continue;
		}
		if(dis[x[i]]+w[i]-l+dis[y[i]]>l&&dis[x[i]]<l)
		{
//			cout<<"case 2: "<<i<<"\n";
			cnt++;
		}
		if(dis[x[i]]+w[i]-l+dis[y[i]]>l&&dis[y[i]]<l)
		{
//			cout<<"case 3: "<<i<<"\n";
			cnt++;
		}
	}
	cout<<cnt<<"\n";
}
```

---

## 作者：Weak_Konjak (赞：3)

# 还没有人发布题解


## 不如我来发布一篇？

------------


## 题意分析

一开始，我没仔细看题，就以为是一道模板题，先跑单源最短路，再依次判断点到$s$的距离。


**但是，这个位置可以在一个结点上**，**也可以在一条边的中间**。


所以不能直接套模板。。。

## 算法分析

我想的，是先$Dijkstra$求最短路，再统计点的个数

### 如何统计？？

先统计在点上的秘密基地，再统计边上的秘密基地

点上的简单，直接$dis[i]==k$

那边上的呢？

先枚举所有边$edge[i]$，设两端点为$u,v$

如果从点s出发，走最短距离距离k，经过了点u，最后到达了$edge[i]$上的秘密基地 $t$

那么，点$t$到点$u$的距离为$(k-dis[u]),$
则$t$到$v$的距离为$(w[u->v]-(k-dis[u])) =  (w[ u->v]-k+dis[u])$。

于是从s出发经过v的距离为(dis[v]+w[ u->v]-k+dis[u])

由于经过u是最短距离，所以会有$:$
$(dis[v]+w[ u->v]-k+dis[u])>= (w[ u->v]-k+dis[u])$

当等于时，意味着会将这个答案重复多一次，所以要判重

## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
struct point{
	long long u,d;
};
bool operator <(point a,point b){
	return a.d>b.d;
}
priority_queue<int,vector<point> > q;
long long n,head[2000001],to[2000001],nxt[2000001],m,tot,start,end,w[2000001],dis[2000001],k;
bool visit[2000001];
void add(int from,int t,int ti){//链式前向星
	to[++tot]=t;
	nxt[tot]=head[from];
	head[from]=tot;
	w[tot]=ti;
}
int main()
{

	cin>>n>>m>>start;
	for(int i=1;i<=m;i++){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
		add(y,x,z);
	}
	cin>>k;
    
    
	for(int i=0;i<=n;i++) dis[i]=0x3f3f3f3f;
	dis[start]=0;
	q.push((point){start,0});
	while(q.size())
	{
		int u=q.top().u,d=q.top().d;q.pop();
		if(d!=dis[u]) continue;
		for(int i=head[u];i;i=nxt[i]){
			int v=to[i];
			if(dis[v]>dis[u]+w[i]){
				dis[v]=dis[u]+w[i];
				q.push((point){v,dis[v]});
			}
		}
	}
    
    
	int ans=0;
	for(int i=1;i<=n;i++) if(dis[i]==k) ans++;
	for(int i=1;i<=n;i++){
		int u=i;
		for(int j=head[i];j;j=nxt[j]){
			int v=to[j];
			if(k>dis[u]){
				if(k-dis[u]<w[j]){
					if(dis[v]+w[j]-k+dis[u]>k) ans++;
					if((dis[v]+w[j]-k+dis[u]==k)&&(!visit[(j+1)/2])) ans++,visit[(j+1)/2]=1;
              //由于是无向图，每条边存入两次
				}
			}
		}
	}
	cout<<ans;
}

```


---

## 作者：Li_Yichen (赞：2)

首先用单源最短路跑出来从 $s$ 点出发的距离，设从 $s$ 为起点到 $i$ 的距离为 $dis_{i}$。那么我们分类讨论。首先，如果秘密基地落在点上，那么 $dis_{i} = k$，直接统计即可。其次，当秘密基地落在线段上时，分为三种情况，设在线段上满足条件的点为 $p$，线段的两端点为 $u$ 和 $v$。第一种，当 $p$ 为线段上的中点。第二种，只能从 $u$ 点到达 $p$ 点。第三种，同理只能从 $v$ 点到达 $p$ 点。以上情况点 $p$ 都唯一，分类讨论计数即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s;
int k;
int head[1000005],dis[1000005],vis[1000005];
int u[1000005],v[1000005],l[1000005];
int cnt;
int ans;
struct edge{
	int to,next,dis;
}e[1000005];
struct node{
	int dis,pos;
	bool operator <(const node &x)const{
		return x.dis < dis;
	}
};
void add(int u,int v,int l){
	cnt++;
	e[cnt].dis = l;
	e[cnt].to = v;
	e[cnt].next = head[u];
	head[u] = cnt;
} 
void dijkstra(){
	priority_queue<node> q;
	dis[s] = 0;
	q.push((node){0,s});
	while(!q.empty()){
		node now=q.top();
		q.pop();
		int x=now.pos;
		if(vis[x]) continue;
		vis[x] = 1;
		for(int i=head[x];i;i=e[i].next){
			int y=e[i].to;
			if(dis[y] > dis[x] + e[i].dis){
				dis[y] = dis[x] + e[i].dis;
				if(!vis[y]) q.push((node){dis[y],y});
			}
		}
	}
}
int main(){
	memset(dis,0x3f,sizeof(dis));
	cin >> n >> m >> s;
	for(int i=1;i<=m;i++){
		int a,b,c;
		cin >> a >> b >> c;
		add(a,b,c);
		add(b,a,c);
		u[i] = a;
		v[i] = b;
		l[i] = c;
	}
	dijkstra();
	cin >> k;
	for(int i=1;i<=n;i++){
		if(dis[i] == k) ans ++;//如果刚好在点上
	}
	for(int i=1;i<=m;i++){
		int x = u[i],y = v[i];
		if(k - dis[x] + k - dis[y] == l[i] && dis[x] < k && dis[y] < k) ans ++;
		if(k - dis[x] + k - dis[y] < l[i] && k > dis[x] && k < dis[x] + l[i]) ans ++;
		if(k - dis[x] + k - dis[y] < l[i] && k > dis[y] && k < dis[y] + l[i]) ans ++;
	}
	cout << ans;
	return 0;
} 
```

---

## 作者：Islauso (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF144D)

# 思路

这道题其实就是一道最短路，建图后先跑一遍 Dijkstra ，然后分几种情况进行判断即可，在点上很好判断，直接看这个点的$dis$值是否等于$l$就可以了，但在边上的情况却不是很好想，这里分三种情况来讨论（注：下文中“满足条件”指的是满足从首都到仓库的距离为$l$的条件）

**情况一**

![](https://cdn.jsdelivr.net/gh/xiao-lin52/image-upload/20200726111012.png)

（~~图画得丑点不要在意~~）

在这种情况下，$L_{u,c}+L_{v,c}=L_{u,v}$，也就是说不论是经过$u$点到$c$还是经过$v$点到$c$，这个点$c$都是唯一的，因此在这种情况下可以推出：
$$
l-dis_u+l-dis_v=w_{u,v}
$$
其中$l$就是题面中给定的那个，$w_{u,v}$则是从$u$到$v$的边权

**情况二**

![](https://cdn.jsdelivr.net/gh/xiao-lin52/image-upload/20200726111208.png)

这种情况是指$c$点不唯一，且$c$只有通过$u$到达才能满足条件，此时，设这条边上另一点满足条件的为$c'$，即$c'$只有通过$v$点到达才能满足条件，此时，$c'$有两种情况，一种是在$c$点左边，一种是在$c$点右边，但由于$c$点通过$u$点到达已经是最短距离，如果$c'$还要在$c$点的左边，那么$c'$的最短路径就不是通过$v$到达，而是通过$u$到达，而由于$c$才是满足条件的那个点，所以$c'$就不满足条件。因此，$c'$应该在$c$点的右边，此时可以得出式子：
$$
l-dis_u+l-dis_v<w_{u,v}
$$
**情况三**

这种情况其实与第二种类似，但$c$点是通过$v$到达才满足条件，相当于把上面那张图的$u$和$v$换了个位置，因此不再赘述，式子和上面那个是一样的，但需要注意的是，这种情况不能与第二种情况一起判断，即只要满足这个式子就直接把答案加$2$，因为有可能$u$或$v$正好就满足条件，此时虽然不是第一种情况，但这条边上还是只有一个点，而如果像上面那样的话，就会多算一个

另外还有一点，就是要判断这个点在不在这条边上，这个比较简单，首先看起点的距离是否小于$l$，再看通过这条边到达终点的距离是否大于$l$就行了，式子是这样的：
$$
dis_u<l,dis_u+w_{u,v}>l
$$
把这一点理清楚后，代码其实就很简单了

对了，还有一点，由于数据范围比较大，所以普通的 Dijkstra 会 T ，要加上堆优化才行

# 代码

```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
#define mp(a,b) make_pair(a,b)
#define inf 0x3f3f3f3f
#define MAXN 100005
using namespace std;
struct Edge
{
	int next;
	int to;
	int w;
};
Edge edge[2*MAXN];
priority_queue< pii,vector<pii>,greater<pii> > q;
int n,m,s,l,ans,cnt,head[MAXN],dis[MAXN],b[MAXN],u[MAXN],v[MAXN],c[MAXN];
void add_edge(int u,int v,int c)
{
	cnt++;
	edge[cnt].next=head[u];
	edge[cnt].to=v;
	edge[cnt].w=c;
	head[u]=cnt;
}
int main()
{
	memset(dis,inf,sizeof(dis));
	scanf("%d%d%d",&n,&m,&s);
	for(int i=1; i<=m; i++)
	{
		scanf("%d%d%d",&u[i],&v[i],&c[i]);
		add_edge(u[i],v[i],c[i]);//无向图记得要建两条边
		add_edge(v[i],u[i],c[i]);
	}
	scanf("%d",&l);
	dis[s]=0;
	q.push(mp(0,s));
	while(q.size())//堆优化Dijkstra
	{
		int u=q.top().second;
		q.pop();
		if(b[u])
			continue;
		b[u]=1;
		for(int i=head[u]; i; i=edge[i].next)
		{
			int v=edge[i].to,c=edge[i].w;
			if(dis[v]>dis[u]+c&&!b[v])
			{
				dis[v]=dis[u]+c;
				q.push(mp(dis[v],v));
			}
		}
	}
	for(int i=1; i<=n; i++)//统计满足情况的点的数量
		if(dis[i]==l)
			ans++;
	for(int i=1;i<=m;i++)//统计满足条件的边上的点的数量
	{
		if(l-dis[u[i]]+l-dis[v[i]]==c[i]&&dis[u[i]]<l&&dis[v[i]]<l)//第一种情况
			ans++;
		if(l-dis[u[i]]+l-dis[v[i]]<c[i]&&l>dis[u[i]]&&l<dis[u[i]]+c[i])//第二种情况
			ans++;
		if(l-dis[u[i]]+l-dis[v[i]]<c[i]&&l>dis[v[i]]&&l<dis[v[i]]+c[i])//第三种情况
			ans++;
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Light_Star_RPmax_AFO (赞：1)

# CF144D Missile Silos 题解

### Part - 0 前言

[传送门](https://www.luogu.com.cn/problem/CF144D)

## Part - 1 思路分析

单源最短路径问题，用 dijkstra 效率较高，然后我们可以把每一个点的最短距离满足条件的统计答案。

当然，这道题不是那么简单，观察发现，在一条线段上，最多只会有两个满足条件的点。

令边的两边为 $u, v$，长度为 $d$。

- 情况一

	当 $u, v$ 到其线段上某一满足条件的点的距离相等时，也就是 $dis_{s,u} + dis_{s, v} + d = k + k$。
    
- 情况二
	
   当与 $u, v$ 距离为 $k$ 有可能在线段上，怎么判断呢？$dis_{s,u} + dis_{s, v} + d > k + k$ 时才有可能，然后我们就可以判断是否有 $dis_{u} + x = k$ 或者 $dis_{v} + x = k$。
   
# AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read(){
  int f = 1,x = 0;
  char ch = getchar();
  while(!isdigit(ch)){
	if(ch == '-')f = -1;
  	ch = getchar();
  }
  while(isdigit(ch)){
  	x = (x << 1) + (x << 3) + (ch ^ 48);
  	ch = getchar();
  }
  return x * f;
}
inline void print(int x){
  if(x > 9)print(x / 10);
  putchar(x % 10 + '0');
}

struct edge{
	int to, dis, next;
}e[200010];
struct dot{
	int u, d;
	bool operator < (const dot &a) const{return a.d < d;} 
};
int tot, head[100010];

inline void add(int from, int to, int dis){
	e[++tot] = edge{to, dis, head[from]};
	head[from] = tot;
	return ;
}

int u[100010], v[100010], d[100010];
int n, m, s;
int dis[100010];
bitset<100010> vis;

void dijkstar(){
	priority_queue<dot> q;
	for(int i = 1; i <= n; i++){
		dis[i] = 1e9;
	}
	dis[s] = 0;
	q.push(dot{s, 0});
	while(!q.empty()){
		int now = q.top().u; q.pop();
		if(vis[now])continue;
		vis[now] = 1;
		for(int i = head[now]; i; i = e[i].next){
			int to = e[i].to, d = e[i].dis;
			if(dis[to] > dis[now] + d){
				dis[to] = dis[now] + d;
				q.push(dot{to, dis[to]});
			}
		}
	}
}
signed main(){
	n = read(), m = read(), s = read();
	for(int i = 1; i <= m; i++){
		u[i] = read(), v[i] = read(), d[i] = read();
		add(u[i], v[i], d[i]);
		add(v[i], u[i], d[i]);
	}
	dijkstar();
	int ans = 0, k = read();
	for(int i = 1; i <= n; i++){
		ans += (dis[i] == k);
	}
	for(int i = 1; i <= m; i++){
		if(dis[u[i]] + d[i] + dis[v[i]] == k + k && dis[u[i]] < k && dis[v[i]] < k){
			ans++;
		}else if(dis[u[i]] + d[i] + dis[v[i]] > k + k){
			ans += (dis[u[i]] < k) + (dis[v[i]] < k);
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Chengjintian (赞：1)

考察点：最短路，图论，分类讨论

索引
>
>思路 Part 1
>
>代码 Part 2

Part 0 题意
---------
给定一张无向连通图，问到 $s$ 点的最短距离为 $k$ 的点和在一条边上的点的数量。

Part 1 思路
------------
我们先考虑一个简单的问题：问有多少到 $s$ 的点的距离为 $k$ 的点。此时跑一遍 Dijkstra，预处理出每一个点到 $s$ 的距离，扫一遍有多少个点到 $s$ 的最短距离为 $k$。

显然题目不会让我们这么轻松A掉ta，符合要求的点还可以在边上，怎么办呢？

我们先思考一下一条边上的点，到 $s$ 的最短距离会是多少。

![图片](https://cdn.luogu.com.cn/upload/image_hosting/hkrit3i0.png)

如上图，一条边连着点 $u$ 和 $v$，$u$ 到 $s$ 的距离是 $x$；$v$ 到 $s$ 的距离是 $y$。

在这条边上的点到 $u$ 的距离是 $z$，到 $v$ 的距离是 $w-z$（$w$ 是边的长度）。此时这个点到 $s$ 的路径可以且只可以经过 $u$ 或 $v$，所以这个点到 $s$ 的距离 $l=\min(x+z,y+w-z)$，我们要使 $l=k$，且点到 $s$ 的最短路径经过 $u$，则

>$z=k-x$ 且 $x+z\le y+w-z$ 且 $z>0$。

于是我们枚举点 $u$，枚举其连着的边，计算其对应的 $z$，看看 $z$ 是否满足上述要求，满足则 $ans++$。

值得注意的，相信读者看到了 $z$ 要满足的条件 $2$ 中的不等式含等号，当两边取等时，表示边上的点到 $s$ 的最短路径既可以经过 $u$，也可以经过 $v$。也就是说原本符合条件的两个点重合了。

枚举到 $u$ 时，这个点让 $ans$ 加了一次，枚举到 $v$ 时，它又让 $ans$ 加了一次，于是我们对这个点所在的边打上标记，让其在枚举到 $u$ 时，$ans++$，枚举到 $v$ 时，被认出来是重点，就不加啦。

这里笔者为了省事，用 二维 unordered_map 对边打上了标记。~~大家不要学我噢。~~

Part 2 代码
-----------------
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m,s,k;
ll ans;
ll dis[(ll)1e5+15];//dis 表示点到 s 的距离 
struct node{
	ll id;
	ll w;
};
vector<node>d[(ll)1e5+15];
typedef pair<ll,ll> a;
void dj(ll sta){//Dijkstra求最短路 
	fill(dis+1,dis+n+1,INT_MAX);
	dis[sta]=0;
	priority_queue<a,vector<a>,greater<a> >que;
	que.push((a){sta,0});
	while(!que.empty()){
		ll u=que.top().first;
		ll w=que.top().second;
		que.pop();
		for(int i=0;i<d[u].size();i++){
			if(dis[d[u][i].id]>dis[u]+d[u][i].w){
				dis[d[u][i].id]=dis[u]+d[u][i].w;
				que.push((a){d[u][i].id,dis[d[u][i].id]});
			}
		}
	}
}
unordered_map<ll,unordered_map<ll,bool>>mp;//点 u,v 所连边上是否有符合要求的重点 
int main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);//关闭同步流，让 cin,cout 速度变快。用了它就不能用其他输入输出方式了。 
	cin>>n>>m>>s;
	for(int i=1;i<=m;i++){
		ll u,v,w;
		cin>>u>>v>>w;
		d[u].push_back((node){v,w});
		d[v].push_back((node){u,w});//vector双向建边 
	}
	dj(s);
	cin>>k;
	for(int i=1;i<=n;i++){//枚举 u 
		ll to=dis[i];//to表示到 s 的距离 
		if(to>k)continue;
		if(to==k){
			ans++;
			continue;
		}
		for(int j=0;j<d[i].size();j++){//枚举 v 
			ll son_to=dis[d[i][j].id];//v 到 s 的距离 
			ll ww=d[i][j].w;// ww 是边长 
			ll z=k-to;
			ll z2=ww-z;
			if(z>ww or z2==0)continue;
			if(to+z<son_to+z2 or (to+z==son_to+z2 and !mp[i][d[i][j].id])){//如果取等，看看是否被标记 
				ans++;
				if(to+z==son_to+z2)mp[d[i][j].id][i]=true;
			}
		}
	}
	cout<<ans;
	return 0;
}
```




---

## 作者：Furina_Saikou (赞：0)

~~关于优先队列排序反了调了我一个小时这件事。~~

# 思路

先跑一遍最短路，然后枚举点看最短路是否恰好等于 $k$，再枚举每条边，怎么判断一条边是否有合法的点呢？

假设一条边的端点分别为 $u$ 和 $v$，分别以这两个端点为起点判断，比如对于 $u$ 如果满足 $dis_u<k \land dis_u+w_i>k$ 和 $dis_v\ge k \lor w_i+dis_u-k+dis_v\ge k$ 就能算入答案。

我们分开看，$dis_u<k \land dis_u+w_i>k$ 意思就是看 $k$ 是否在这条边上，$dis_v\ge k\lor w_i+dis_u-k+dis_v\ge k$ 则是判断 $u$ 到 $k$ 是否是最短路线，$w_i+dis_u-k+dis_v$ 表示经过 $v$ 点时 $k$ 到 $s$ 的最短路径，如果这条路径比经过 $u$ 的这条短，那这个位置就不合法。

注意，有可能某条边上的一个位置被他的两个端点同时计算，为了避免重复，计算 $v$ 时和计算 $u$ 时不同，将大于等于改为严格大于。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1919810;
int n,m,s,k,head[N],id,from[N],to[N],ne[N],w[N],dis[N],vis[N],ans;
inline void add(int x,int y,int z)
{
	to[++id]=y,from[id]=x,w[id]=z,ne[id]=head[x],head[x]=id;
}
void dijkstra()
{
	memset(dis,0x3f,sizeof dis);
	priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >q;
	q.push(make_pair(0,s));
	dis[s]=0;
	while(!q.empty())
	{
		int u=q.top().second,d=q.top().first;
		q.pop();
		if(vis[u])continue;
		vis[u]=1;
		for(int i=head[u],v=to[i];i;i=ne[i],v=to[i])
		{
			if(dis[v]<=d+w[i])continue;
			dis[v]=d+w[i];
			q.push(make_pair(dis[v],v));
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(dis[i]==k)
		{
			ans++;
		}
	}
	for(int i=1;i<=2*m;i+=2)
	{
		int u=from[i],v=to[i];
		if(dis[u]<k&&dis[u]+w[i]>k&&(dis[v]>=k||w[i]+dis[u]-k+dis[v]>=k))
		{
			ans++;
		}
		if(dis[v]<k&&dis[v]+w[i]>k&&(dis[u]>=k||w[i]+dis[v]-k+dis[u]>k))
		{
			ans++;
		}
	}
}
signed main()
{
	cin>>n>>m>>s;
	for(int i=1,x,y,z;i<=m;i++)
	{
		cin>>x>>y>>z;
		add(x,y,z),add(y,x,z);
	}
	cin>>k;
	dijkstra();
	cout<<ans;
	return 0;
}
```

---

## 作者：RioFutaba (赞：0)

## 解法
一眼看过去以为是最短路模板，仔细读题之后才发现这位置能在边上。 

首先考虑在满足要求（即 $s$ 到它的距离为 $l$）的位置在点上的情况。显而易见，直接以 $s$ 为源点跑一个单源最短路求出 $s$ 到其他点的距离即可。

那么在边上的呢？

($dis_i$ 表示 $s \rightarrow i$ 的最短距离)


对于当前从 $u$ 到 $v$，权值为 $w$ 的边，如下图，答案有两种可能。第一种是从 $s$ 走到 $u$ 再走到边上的 $p_1$，另一种则是从 $s$ 走到 $v$ 再走到边上的 $p_2$。

![](https://cdn.luogu.com.cn/upload/image_hosting/f2im18t0.png)

依题意，$x+dis_u=l$，$y+dis_v=l$。


如果 $dis_u+x \le dis_v+w-x$ 并且 $0<x<w$，那么 $p_1$ 满足要求。

如果 $dis_v+y \le dis_u+w-y$ 并且 $0<y<w$，那么 $p_2$ 满足要求。

需要注意的是，$p_1$ 和 $p_2$ 可能重合。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn=1e5+5,maxm=2e5+5,INF=0x3f3f3f3f;
int n,m,s,l;
int head[maxm],to[maxm],val[maxm],ne[maxm],tot;
int dis[maxn],ans;
struct node{
	int p,d;
	bool operator<(const node &o)const{return d>o.d;}
};
struct edge{int u,v,w;};
void add(int u,int v,int w){
	to[++tot]=v;
	val[tot]=w;
	ne[tot]=head[u];
	head[u]=tot;
}
vector<edge> e;
void dij(int s){
	memset(dis,INF,sizeof(dis));
	priority_queue<node> q;
	dis[s]=0;
	q.push({s,0});
	while(!q.empty()){
		node P=q.top();
		q.pop();
		int u=P.p,w=P.d;
		for(int i=head[u];i;i=ne[i]){
			int v=to[i];
			if(w+val[i]<dis[v]){
				dis[v]=w+val[i];
				q.push({v,dis[v]});
			}
		}
	}
	for(int i=1;i<=n;i++) if(dis[i]==l) ans++;//在点上
}
int main(){
	cin >> n >> m >> s;
	for(int i=1,u,v,w;i<=m;i++){
		cin >> u >> v >> w;
		add(u,v,w);
		add(v,u,w);
		e.push_back({u,v,w});
	}
	cin >> l;
	dij(s);
	for(int i=0;i<e.size();i++){
		int u=e[i].u,v=e[i].v,w=e[i].w;
		int a=dis[u],b=dis[v];
		int x=l-a,y=l-b;
		int f=0;//记录这个边上有多少个答案
		if(x>0 && x<w)
			if(b+w-x>=l) f++;
		if(y>0 && y<w)
			if(a+w-y>=l) f++;
		if(x+y==w) f=min(f,1);//如果重合就要算少一个
		ans+=f;
	}
	cout << ans << endl;
	return 0;
}
```

---

