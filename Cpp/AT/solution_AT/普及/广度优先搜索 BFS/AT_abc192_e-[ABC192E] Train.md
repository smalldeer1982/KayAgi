# [ABC192E] Train

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc192/tasks/abc192_e

AtCoder国には $ 1 $ から $ N $ の番号がついた $ N $ 個の都市と、$ 1 $ から $ M $ の番号がついた $ M $ 本の鉄道があります。

鉄道 $ i $ は都市 $ A_i $ と都市 $ B_i $ の間を結んでおり、時刻が $ K_i $ の倍数になる毎に、双方の都市からそれぞれ他方の都市への列車が発車します。この列車は出発から到着までに $ T_i $ の時間がかかります。

あなたはいま都市 $ X $ にいます。時刻 $ 0 $ またはそれ以降に都市 $ X $ を発車する列車に乗って移動を開始するとき、都市 $ Y $ には最速でいつたどり着けるか求めてください。都市 $ Y $ にたどり着くことが出来ない場合はそのことを報告してください。  
 ただし、乗り換えにかかる時間は無視できるため、どの都市においても、あなたの乗っている列車の到着時刻と同時に発車する別の列車に乗り換えることが可能であるとします。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 0\ \leq\ M\ \leq\ 10^5 $
- $ 1\ \leq\ X,Y\ \leq\ N $
- $ X\ \neq\ Y $
- $ 1\ \leq\ A_i,B_i\ \leq\ N $
- $ A_i\ \neq\ B_i $
- $ 1\ \leq\ T_i\ \leq\ 10^9 $
- $ 1\ \leq\ K_i\ \leq\ 10^9 $
- 入力は全て整数

### Sample Explanation 1

まず、時刻 $ 0 $ に鉄道 $ 1 $ に乗って、都市 $ 1 $ から都市 $ 2 $ へ移動します。都市 $ 2 $ には時刻 $ 2 $ に到着します。 その後、時刻 $ 4 $ に鉄道 $ 2 $ に乗って、都市 $ 2 $ から都市 $ 3 $ へ移動します。都市 $ 3 $ には時刻 $ 7 $ に到着します。 これより早く都市 $ 3 $ に着く方法はありません。

### Sample Explanation 2

まず、時刻 $ 0 $ に鉄道 $ 2 $ に乗って、都市 $ 3 $ から都市 $ 2 $ へ移動します。都市 $ 2 $ には時刻 $ 3 $ に到着します。 その後、時刻 $ 3 $ に鉄道 $ 1 $ に乗って、都市 $ 2 $ から都市 $ 1 $ へ移動します。都市 $ 1 $ には時刻 $ 5 $ に到着します。

## 样例 #1

### 输入

```
3 2 1 3
1 2 2 3
2 3 3 4```

### 输出

```
7```

## 样例 #2

### 输入

```
3 2 3 1
1 2 2 3
2 3 3 4```

### 输出

```
5```

## 样例 #3

### 输入

```
3 0 3 1```

### 输出

```
-1```

## 样例 #4

### 输入

```
9 14 6 7
3 1 4 1
5 9 2 6
5 3 5 8
9 7 9 3
2 3 8 4
6 2 6 4
3 8 3 2
7 9 5 2
8 4 1 9
7 1 6 9
3 9 9 3
7 5 1 5
8 2 9 7
4 9 4 4```

### 输出

```
26```

# 题解

## 作者：Z_AuTwT (赞：4)

看到这种问题，无非就是 DP 或者搜索。

先看 DP，好像没法很轻松的求解，那我们就用搜索。

## 思路：

有一个很明了的思路，就是先跑 dfs，然后用记忆化搜索剪枝。

当我们打完后，一交，发现第一个数据都过不了。

转而又想，可不可以转化为 bfs 呢？

显然是可以的。转化之后，我们就可以过掉第一个测试点。

还需要剪枝！

深入想一下，我们可以将 bfs 中的队列换成优先队列，来让多余的状态尽可能多的被记忆化搜索剪掉。但是，优化到这里还不够，第二个测试点还是过不了。

再想一下，虽然有一些被记忆化剪掉了，但还是有很多冗余状态，我们可以用一个数组来记录当时这个点对应的最小时间，如果当前搜索到的这个点已经超过了最小时间，那么即使这个数改变了其他数到最后也会被比它更小的代替，所以还不如不搜。

## 代码：
```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
struct node{
	int v,k,T;
};
vector<node> V[100010];//存图
int dp[100010];//记录最小时间
void bfs(int s){
	priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > que;//类似于Dij
	que.push(make_pair(0,s));
	while(!que.empty()){
		auto now=que.top();
		que.pop();
		if(now.first>dp[now.second]) continue;//大于了当前最小时间
		for(auto ed:V[now.second]){//遍历出边
			int sj=dp[now.second];
			if(sj%ed.k!=0){
				sj=(sj/ed.k+1)*ed.k;
			}
			if(dp[ed.v]>sj+ed.T){//可以更新
				dp[ed.v]=sj+ed.T;
				que.push(make_pair(dp[ed.v],ed.v));
			}
		}
	}
}
signed main(){
	int n,m,s,t;
	cin>>n>>m>>s>>t;
	for(int i=1;i<=m;i++){//存边
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		V[a].push_back({b,d,c});
		V[b].push_back({a,d,c});
	}
	for(int i=1;i<=n;i++) dp[i]=9e18;//一定要赋long long极大值
	dp[s]=0;
	bfs(s);
	if(dp[t]==9e18) cout<<"-1";
	else cout<<dp[t];
}
```

---

## 作者：xuchuhan (赞：3)

## 前言

赛时用了 SPFA 求最短路。~~结果，关于 SPFA，他死了。~~

## 思路

就是最短路板子，只是松弛操作有些变化。

最短路模板的松弛操作如下：$dis_v=dis_u+w_{u,v}$。其中 $w_{u,v}$ 表示 $u \rightarrow v$ 的边的长度。

而这道题的松弛操作即为：$dis_v=dis_u+w_{u,v}+W(u,k)$。其中 $W(u,k)$ 表示当到达 $u$ 点时，当前列车在时间为 $k$ 的倍数时发车，还需要在站台等待多久。

其余就是，最好别用 SPFA。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,m,X,Y;
struct edge{
	int id,val,t;
};
struct node{
	int id,val;
	bool operator<(const node&x)const{
		return val>x.val;
	}
};
vector<edge>v[N];
int dis[N];
bool vis[N];
void Dijkstra(int st){
	priority_queue<node>q;
	memset(dis,0x3f,sizeof(dis));
	dis[st]=0;
	q.push({st,0});
	while(!q.empty()){
		int tx=q.top().id;
		q.pop();
		if(vis[tx])
			continue;
		vis[tx]=1;
		for(int i=0;i<v[tx].size();i++){
			int to=v[tx][i].id,tim=v[tx][i].t;
			int w=v[tx][i].val+((tim-dis[tx]%tim)%tim);//从u->v的总花费时间
			if(dis[to]>dis[tx]+w){
				dis[to]=dis[tx]+w;
				q.push({to,dis[to]});
			}
		}
	}
}
signed main(){
	cin>>n>>m>>X>>Y;
	for(int i=1;i<=m;i++){
		int x,y,t,k;
		cin>>x>>y>>t>>k;
		v[x].push_back({y,t,k});
		v[y].push_back({x,t,k});
	}
	Dijkstra(X);
	if(dis[Y]>1e18)//到不了
		cout<<-1;
	else
		cout<<dis[Y];
	return 0;
}
```

---

## 作者：__Creeper__ (赞：1)

## 思路

这是一道单源最短路，考虑 Dijkstra 算法。

我们从 $dis_{u}$ 转移到 $dis_{v}$，$u$ 到 $v$ 的车出发至到达需要花 $w$ 的时间，并且等待时间是 $k$ 的倍数。

如果到达 $u$ 时间 $dis_{u}$ 不是 $k$ 的倍数则需要等待到 $k$ 的倍数，即：

$$
dis_{v} = \min ( dis_{v}, k \times ⌈\frac{dis_{u}}{k}⌉ + w )
$$

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
#define pii pair<int, int>
using namespace std;

const int N = 1e5 + 5;
int n, m, s, t, dis[N];
bitset<N> vis;
struct node { int v, w, k; };
vector<node> G[N];
struct qwq
{
	int u, d;
	bool operator < ( const qwq &o ) const
	{
		return o.d < d;
	}
};
priority_queue<qwq> q;

void dij ()
{
	for ( int i = 1; i <= n; i++ ) dis[i] = 1e18;
	dis[s] = 0;
	q.push ( {s, 0} );
	while ( !q.empty() )
	{
		qwq u = q.top();
		q.pop();
		if ( vis[u.u] ) continue;
		vis[u.u] = 1;
		for ( int i = 0; i < G[u.u].size(); i++ )
		{
			int v = G[u.u][i].v, w = G[u.u][i].w, k = G[u.u][i].k;
			if ( dis[v] > w + ( ( dis[u.u] + k - 1 ) / k ) * k )
			{
				dis[v] = w + ( ( dis[u.u] + k - 1 ) / k ) * k;
				q.push ( {v, dis[v]} );
			}
		}
	}
}

void solve()
{
	cin >> n >> m >> s >> t;
	for ( int i = 1; i <= m; i++ )
	{
		int u, v, w, k;
		cin >> u >> v >> w >> k;
		G[u].push_back ( node{v, w, k} );
		G[v].push_back ( node{u, w, k} );
	}
	dij ();
	if ( dis[t] == 1e18 ) cout << "-1\n";
	else cout << dis[t];
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T = 1;
//	cin >> T;
	while ( T-- ) solve();
	return 0;
}
```

---

## 作者：Tachibana27 (赞：1)

最短路模板水题，但这个小蒟蒻赛时没写出来，，，


------------

没有负边权，考虑堆优化 Dijkstra。可以发现，如果我们希望坐第 $i$ 号列车就必须要当前时间为 $K_i$ 的倍数，如果早来了就需要等待，直到列车来临。所以，我们等待列车的时间为：

$$(k-dis[x]\bmod k)\bmod k$$

自然地，Dijkstra 的松弛操作就是：

```cpp
if(dis[y]>dis[x]+e[i].w+(e[i].k-dis[x]%e[i].k)%e[i].k){
	dis[y]=dis[x]+e[i].w+(e[i].k-dis[x]%e[i].k)%e[i].k;
	q.push({dis[y],y});
}

```

在**开完 long long 后**这个小蒟蒻自信的交了一发。

然后，然后这个蒟蒻在 [#5](https://www.luogu.com.cn/record/145417202) WA 了。

敲个警钟，long long 对应的最大值不是 0x3f ~~这种错误估计只有我会犯了。~~

下面给出完整代码：

```cpp
%:include<bits/stdc++.h>
#define int long long
inline int read()<%
	int s=0;
	int w=1;
	char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar())
    	if(ch=='-')
			w=-1;
	for(;ch>='0' and ch<='9';ch=getchar())
		s=s*10+ch-'0';
	return s*w;
%>

void write(int x)<%
	if(x<0)<%
   		putchar('-');
   		x=-x;
	%>
	if(x>9)
    	write(x/10);
	putchar(x%10+'0');
	return;
%>//快读快写自行掠过
class ed{
	public:
		int u;
		int v;
		int w;
		int k;
}e[6000086];
int head[6000086];
int dis[6000086];
bool vis[6000086];
int point;
void add(int u,int v,int w,int k){
	e[++point]={v,head[u],w,k};
	head[u]=point;
}
int n,m;
int s,t;
std::priority_queue<std::pair<int,int> >q;
void dij(int s){
	for(int i=1;i<=n;i++)
		dis[i]=1145141919810114;//其实这个就是极大值，但是memset里的0x7f好像和memset外的不太一样
	memset(vis,false,sizeof vis);
	dis[s]=0;
	q.push({0,s});
	while(!q.empty()){
		int x=q.top().second;
		q.pop();
		if(vis[x])
			continue;
		vis[x]=true;
		for(int i=head[x];i;i=e[i].v){
			int y=e[i].u;
			if(dis[y]>dis[x]+e[i].w+(e[i].k-dis[x]%e[i].k)%e[i].k){
				dis[y]=dis[x]+e[i].w+(e[i].k-dis[x]%e[i].k)%e[i].k;//不一样的松弛
				q.push({-dis[y],y});
			}
		}
	}
}//模板堆优化dijkstra
signed main()<%
  	//freopen(".in","r",stdin);
  	//freopen(".out","w",stdout);
	n=read();
	m=read();
	s=read();
	t=read();
	while(m--){
		int u,v,t,k;
		u=read();
		v=read();
		t=read();
		k=read();
		add(u,v,t,k);
		add(v,u,t,k);
	}
	dij(s);
	write(dis[t]==1145141919810114?-1:dis[t]);//不要忘记输出-1
  	return 0;//撒花
%>
```

---

## 作者：Down_syndrome (赞：1)

## 思路
这类题目已经比较老套了。首先先到一个点肯定会比晚到一个点更优，因为即使没有车来，也可以在原地等，所以可以直接跑一遍堆优化迪杰斯特拉，只是需要加上等待的时间。那如何算等待时间呢?对于时间 $t$，$k$ 时通行，我们可以用 $k$ 减去 $t$ 模 $k$ 的值算出等待时间，同时记得要再模一次 $k$，因为 $t$ 正好是 $k$ 的倍数的时候不需要等待。因此有如下式子。
$$wait=(K_i-dis_u \bmod K_i) \bmod K_i$$
$$dis_v=\min(dis_v,dis_u+wait+T_i)$$
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
const int M=2e5+5;
int n,m,x,y,a,b,c,d,cnt,to[M],val[M],vall[M],nxt[M],h[N],dis[N],vis[N];
struct node{
	int num,dis;
	bool operator<(const node &x)const{
		return x.dis<dis;
	}
};
priority_queue<node> q;
void save(int a,int b,int c,int d){
	to[++cnt]=b;
	val[cnt]=c;
	vall[cnt]=d;
	nxt[cnt]=h[a];
	h[a]=cnt;
}
int wait(int x,int t){return (t-x%t)%t;} 
void dijkstra(){
	memset(dis,0x7f,sizeof(dis));
	dis[x]=0;
	q.push((node){x,0});
	while(!q.empty()){
		node now=q.top();
		q.pop();
		if(vis[now.num]) continue;
		vis[now.num]=1;
		for(int i=h[now.num];i;i=nxt[i]){
			if(dis[to[i]]>dis[now.num]+wait(dis[now.num],vall[i])+val[i]){
				dis[to[i]]=dis[now.num]+wait(dis[now.num],vall[i])+val[i];
				q.push((node){to[i],dis[to[i]]});
			}
		}
	}
}
signed main(){
	scanf("%lld%lld%lld%lld",&n,&m,&x,&y);
	for(int i=1;i<=m;i++){
		scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
		save(a,b,c,d);
		save(b,a,c,d);
	}
	dijkstra();
	if(dis[y]<=1e18) printf("%lld",dis[y]);
	else printf("-1");
	return 0;
}
```


---

## 作者：YangXiaopei (赞：1)

## 前言:

纪念模拟赛写寄写篇题解。

## Solution:

最短路板子题，只需在每次松弛时将贡献加上一个等待时间即可。

我们设已走 $x$ 分钟，每 $y$ 分钟发一次车。

等待时间即为 $(y - x \bmod y) \bmod y$。

提示，最后时间可能大于 $10^9$，所以 `memset` 要写到 `0x7f`，最后判断要判到 $10^{18}$。

## Code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, m, s, t, dis[100005];
bool vis[100005];
struct node{
	int v, w, k;
	bool operator < (const node x) const{
		return w > x.w;
	}
};
struct edge{
	int v, w;
	bool operator < (const edge x) const{
		return w > x.w;
	}
};
vector<node> g[100005];
void dijkstra(){
	memset(dis, 0x7f, sizeof(dis));
	priority_queue<edge> q;
	dis[s] = 0;
	q.push({s, 0});
	while(!q.empty()){
		int x = q.top().v;
		q.pop();
		if(vis[x]){
			continue;
		}
		vis[x] = 1;
		for(auto i : g[x]){
			int y = (dis[x] % i.k);
			if(y == 0){
				y = 0;
			}
			else{
				y = i.k - y;
			}
			if(dis[i.v] > dis[x] + i.w + y){
				dis[i.v] = dis[x] + i.w + y;
				q.push({i.v, dis[i.v]});
			}
		}
	}
}
signed main(){
	cin >> n >> m >> s >> t;
	while(m--){
		int u, v, w, k;
		cin >> u >> v >> w >> k;
		g[u].push_back({v, w, k});
		g[v].push_back({u, w, k});
	}
	dijkstra();
	if(dis[t] > 1e18){//就在这写寄。
		cout << -1;
	}
	else{
		cout << dis[t];
	}
	return 0;
}
```

---

## 作者：RioFutaba (赞：0)

# 思路

这是一道最短路题。  
用 Dijkstra 即可。

但是因为有一个等车出发的过程，所以在松弛上有变化。

假设当前用了 $s$ 时间从 $X$ 走到一个点，并且要通过第 $i$ 条边走到另一个点。那么等车的时间为 $(K_i-(s \mod K_i)) \mod K_i$。在松弛的时候加上这个时间即可。

代码：  
```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long 
const int maxn=1e5+5,maxm=2e5+5;
const ll INF=2e14;
int n,m,x,y;
int head[maxm],ne[maxm],to[maxm],tot;
ll t[maxm],k[maxm],dis[maxm];
bool vis[maxn];
struct node{
	int p;//点编号
	ll d;//x->p的距离
	bool operator<(const node &o)const{return d>o.d;}//小根堆
};
void add(int u,int v,ll a,ll b){
	to[++tot]=v;
	t[tot]=a;
	k[tot]=b;
	ne[tot]=head[u];
	head[u]=tot;
}//链式前向星建图
ll dij(){
	for(int i=1;i<=n;i++) dis[i]=INF;
	dis[x]=0;
	priority_queue<node> q;
	q.push({x,0});
	while(!q.empty()){
		int u=q.top().p;
		q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(int i=head[u];i;i=ne[i]){
			int v=to[i];
			ll tm=(k[i]-dis[u]%k[i])%k[i];//等待时间
			if(dis[u]+t[i]+tm<dis[v]){
				dis[v]=dis[u]+t[i]+tm;
				q.push({v,dis[v]});
			}
		}
	}
	if(dis[y]==INF) return -1;//走不到
	return dis[y];
}
int main(){
	scanf("%d%d%d%d",&n,&m,&x,&y);
	for(int i=1,u,v;i<=m;i++){
		ll a,b;
		scanf("%d%d%lld%lld",&u,&v,&a,&b);
		add(u,v,a,b);
		add(v,u,a,b);//双向边
	}
	printf("%lld\n",dij());
	return 0;
}
```

---

## 作者：_QyGyQ_ (赞：0)

一道最短路。与单源最短路板子的唯一不同点就是松弛操作需要改一下。单源最短路板子是对两点间的距离与当前求出的最短距离进行比较，完成松弛。而这道题中，要松弛的不仅仅是两点间的距离，还要加上到达当前点时，列车在 $k$ 的倍数的时间发车需要等待的时间。具体的松弛代码如下：
```cpp
int W=to.w+((to.time-dis[id]%to.time)%to.time);
if(dis[to.to]>dis[id]+W){
	dis[to.to]=dis[id]+W;
	if(!v[to.to]) q.push({dis[to.to],to.to});
}
```
其他的就和模板没什么区别了。
```cpp
#include<bits/stdc++.h>
#define int long long
#define lc(p) (p<<1)
#define rc(p) (p<<1|1)
#define debug puts("-----------")
#define endl puts("")
#define re register
#define in inline
using namespace std;
const int N=1e6+7;

char *p1,*p2,buf[N];
#define nc() (p1==p2 && (p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
in int read(){
    int x=0,f=1;
    char ch=nc();
    while(ch<48||ch>57){
        if(ch=='-') f=-1;
        ch=nc();
    }
    while(ch>=48&&ch<=57) x=x*10+ch-48,ch=nc();
   	return x*f;
}

struct edge{
	int to,w;
	int time;
};
vector<edge>G[N];
struct node{
	int dist,id;
	bool operator <(const node &x) const{
		return x.dist<dist;
	}
};
priority_queue<node>q;
int v[N];
int dis[N],s;
in void dijkstra(){
	dis[s]=0;
	q.push({0,s});
	while(!q.empty()){
		node front=q.top();
		q.pop();
		int id=front.id;
		int w=front.dist;
		if(v[id]) continue;
		v[id]=true;
		for(auto to:G[id]){
			int W=to.w+((to.time-dis[id]%to.time)%to.time);
			if(dis[to.to]>dis[id]+W){
				dis[to.to]=dis[id]+W;
				if(!v[to.to]) q.push({dis[to.to],to.to});
			}
		}
	}
}
signed main(){
	int n=read(),m=read();
	s=read();
	int ed=read();
	for(re int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		int k=read();
		G[u].push_back({v,w,k});
		G[v].push_back({u,w,k});
	}
	for(re int i=1;i<=n;i++){
		dis[i]=1e18;
	}
	dijkstra();
	if(dis[ed]==1e18) dis[ed]=-1;
	printf("%lld",dis[ed]);
	return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

应该是[P9751 [CSP-J 2023] 旅游巴士](https://www.luogu.com.cn/problem/P9751)的弱化版。

注意到是单元最短路问题，考虑 dijkstra 算法。

本题的边有一个需要在 $k$ 的倍数出发的时间限制，则状态转移应为：

$$dis_v = \min(dis_v,k \lceil \frac{dis_u}{k}\rceil + w)$$

即找到下一个离 $dis_u$ 更近的 $k$ 的倍数。

时间复杂度为 $O(N \log N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
using namespace std;
typedef long long ll;
typedef double db;
const ll N=1e5+10,INF=1e15; 
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
struct Node{
	ll u;
	ll data;
	bool operator<(const Node&rhs)const{
		return rhs.data<data;
	}
};
ll n,m,x,y;
ll dis[N];
bool f[N];
vector<pair<ll,pair<ll,ll>>> E[N];
priority_queue<Node> Q;
void add(ll u,ll v,ll w,ll k){
	E[u].push_back({v,{w,k}});
	E[v].push_back({u,{w,k}});
}
void dijkstra(ll s){
	Q.push({s,0});
	dis[s]=0;
	while(!Q.empty()){
		ll u=Q.top().u;
		Q.pop();
		if(f[u])
		  continue;
		f[u]=1;
		for(auto t:E[u]){
			ll v=t.first,w=t.second.first,k=t.second.second;
			if(dis[v]>((dis[u]+k-1)/k)*k+w){
				dis[v]=((dis[u]+k-1)/k)*k+w;
				Q.push({v,dis[v]});
			}
		}
	}
}
int main(){
	n=read(),m=read(),x=read(),y=read();
	for(int u,v,w,k,i=1;i<=m;i++){
		u=read(),v=read(),w=read(),k=read();
		add(u,v,w,k);
	}
	for(int i=1;i<=n;i++)
	  dis[i]=INF;
	dijkstra(x);
	if(dis[y]==INF)
	  puts("-1");
	else
	  write(dis[y]);
	return 0;
}
```

---

## 作者：__Cby___ (赞：0)

## 思路
鉴定为最短路模板。   
唯一不同的是我们的松弛操作。假设我们是从 $t$ 转移到 $v$，保存最短时间的数组为 $dis$，$u$ 到 $v$ 的车出发至到达需要花 $r$ 的时间。我们有如下转移式子：  
$$dis_v = dis_t + (k - dis_t \bmod k) \bmod k + r$$
注意 $dis$ 数组的初始值要赋 `long long` 范围内的**较大值**（并且两个较大值相加不能超过 `long long` 范围）。
## 代码
```cpp
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#define int long long
using namespace std;
struct node {
	int u, w;
	int k;
};
struct pdn {
	int u, d;
	bool operator >(const pdn& a) const {
		return d > a.d;
	}
};
vector<node> a[200025];
priority_queue<pdn, vector<pdn>, greater<pdn>> q;
int dis[200025];
bool vis[200025];
int n, m;
int dijkstra(int s) {
	for (int i = 1; i <= n; i++) {
		dis[i] = 999999999999999999;
	}
	dis[s] = 0;
	q.push({ s,0 });
	while (!q.empty()) {
		int t = q.top().u;
		q.pop();
		if (vis[t])continue;
		vis[t] = 1;
		for (auto &i : a[t]) {
			int v = i.u, r = i.w;
			int k = i.k;
			if (dis[v] > dis[t] + (k - dis[t] % k) % k + r) {
				dis[v] = dis[t] + (k - dis[t] % k) % k + r;
				q.push({ v,dis[v] });
			}
		}
	}
	return 0;
}
signed main() {
	int X, Y;
	cin >> n >> m >> X >> Y;
	for (int i = 0; i < m; i++) {
		int x, y, z, k;
		cin >> x >> y >> z >> k;
		a[x].push_back({ y,z,k });
		a[y].push_back({ x,z,k });
	}
	dijkstra(X);
	if (dis[Y] >= 999999999999999999)dis[Y] = -1;
	cout << dis[Y] << endl;
	return 0;
}
```

---

## 作者：_ChongYun_ (赞：0)

比较基础的一道图论题。

# 题意

给你一个无向图，有 $n$ 个点，$m$ 条边。

对于每条边，边权为 $T_i$，需要时间是 $K_i$ 的倍数才能走这条边。

问从起点到终点的最短时间是多少。

# 解析

考虑使用单源最短路算法 Dijkstra，但这道题加入了一个倍数要求。

对于两个邻接点 $u$ 和 $v$，考虑算出从点 $u$ 转移到点 $v$ 的等待时间。

而等待时间就是当前时间与最近的 $K_i$ 的倍数的差值。

等待时间再加上本身就需要的边权，就是从点 $u$ 到点 $v$ 的时间。

具体代码如下：

```cpp
if(dis[y]>dis[x]+(w[i].wt-dis[x]%w[i].wt)%w[i].wt+w[i].val){
	dis[y]=dis[x]+(w[i].wt-dis[x]%w[i].wt)%w[i].wt+w[i].val;
	q.push(make_pair(dis[y],y));
}
```

~~其他没啥了，都是模板吧。~~

# 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,st,ed;
struct node{
	int to,nxt,val,wt;
}w[1145114];
int h[1145114],cnt=0;
void Link(int x,int y,int val,int wt){
	++cnt;
	w[cnt].to=y;
	w[cnt].nxt=h[x];
	w[cnt].val=val;
	w[cnt].wt=wt;
	h[x]=cnt;
	return ;
}
int dis[1145114];
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
void dijkstra(int st){
	for(int i=1;i<=n;i++) dis[i]=LLONG_MAX;
	dis[st]=0;
	q.push(make_pair(0,st));
	while(!q.empty()){
		int x=q.top().second,xx=q.top().first;
		q.pop();
		if(xx!=dis[x]) continue;
		for(int i=h[x];i!=0;i=w[i].nxt){
			int y=w[i].to;
			if(dis[y]>dis[x]+(w[i].wt-dis[x]%w[i].wt)%w[i].wt+w[i].val){
				dis[y]=dis[x]+(w[i].wt-dis[x]%w[i].wt)%w[i].wt+w[i].val;
				q.push(make_pair(dis[y],y));
			}
		}
	} 
	return ;
}
signed main(){
	cin>>n>>m>>st>>ed;
	for(int i=1;i<=m;i++){
		int u,v,w,z;
		cin>>u>>v>>w>>z;
		Link(u,v,w,z);
		Link(v,u,w,z);
	}
	dijkstra(st);
	cout<<(dis[ed]==LLONG_MAX?-1:dis[ed])<<endl;
	return 0;
}
```


---

## 作者：minVan (赞：0)

**解题思路**

约等于板子题，套上普通的 dijkstra 算法，然后对于一条边 $(u, v, w, k)$ 的最短路更新条件改为：

$$d_v>w+k\left\lceil\dfrac{d_u}{k}\right\rceil$$

后面的指的是 $d_u$ 加上等待下一班车的时间。

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 5;
struct node {
  int v, w, k;
};
struct Node {
  int l, r;
  bool operator < (const Node &x) const {
    return r > x.r;
  }
};
vector<node> e[N];
int n, m, x, y, dis[N];
bool vis[N];
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> m >> x >> y;
  while(m--) {
    int a, b, t, k;
    cin >> a >> b >> t >> k;
    e[a].push_back({b, t, k});
    e[b].push_back({a, t, k});
  }
  memset(dis, 0x3f, sizeof(dis));
  dis[x] = 0;
  priority_queue<Node> pq;
  pq.push({x, 0});
  while(!pq.empty()) {
    int tmp = pq.top().l, tim = pq.top().r;
    pq.pop();
    if(vis[tmp]) {
      continue;
    }
    vis[tmp] = 1;
    for(auto i : e[tmp]) {
      int v = i.v, w = i.w, k = i.k;
      if(dis[v] > w + (int)(ceil(tim * 1.0 / k * 1.0)) * k) {
        dis[v] = w + (int)(ceil(tim * 1.0 / k * 1.0)) * k;
        pq.push({v, dis[v]});
      }
    }
  }
  if(dis[y] == dis[0]) {
    cout << "-1";
  } else {
    cout << dis[y];
  }
  return 0;
}

```

---

## 作者：CQ_Bob (赞：0)

## 分析

模板题。

跑一个最短路就行了。定义 $\mathit{dis}_{i}$ 表示从 $x$ 出发到达 $i$ 时的最早时间。那么经过 $u \to v$ 这条边时，到 $v$ 的最早时间就是 $\mathit{dis}_u+(k_i-(\mathit{dis}_{u}\bmod k_i))\bmod k_i +t_i$。

## 代码

[Link](https://atcoder.jp/contests/abc192/submissions/47172626).

---

## 作者：loser_seele (赞：0)

看到这类套路题，一般先考虑两点之间的情况怎么做。

于是问题转化为：假设从 $ A $ 出发的时刻为 $ T $，且 $ A,B $ 两点间的边权为 $ W $，时间间隔为 $ K $，那么从 $ A $ 到 $ B $ 的时刻最早是多少。

显然最优策略是等到能出发的最早时刻之后直接跑路，答案即为 $ \lceil \frac{T}{K} \rceil + W $。

用朴素 Dijkstra 即可解决，时间复杂度同 Dijkstra。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,m,u,v;
struct edge
{
	int to,dis,k;
};
vector<edge> edg[100005];
queue<int> wk;
int d[100005];
signed main()
{
	cin>>n>>m>>u>>v;
	long long t1,t2,t3,t4;
	for(int i=1;i<=m;i++)
	{
		cin>>t1>>t2>>t3>>t4;
		edg[t1].push_back({t2,t3,t4});
		edg[t2].push_back({t1,t3,t4});
	}
	for(int i=1;i<=n;i++)
	d[i]=-1;
	d[u]=0;
	wk.push(u);
	wk.push(0);
	int s;
	while(!wk.empty())
	{
		s=wk.front();
		wk.pop();
		if(wk.front()!=d[s])
		{
			wk.pop();
			continue;
		}
		wk.pop();
		for(auto x:edg[s])
		{
			if(d[x.to]==-1||d[x.to]>d[s]-(d[s]+x.k-1)%x.k+x.k-1+x.dis)
			{
				d[x.to]=d[s]-(d[s]+x.k-1)%x.k+x.k-1+x.dis;
				wk.push(x.to);
				wk.push(d[x.to]);
			}
		}
	}
	cout<<d[v];
}
```


---

## 作者：huyangmu (赞：0)

这道题是求点 $x$ 到点 $y$ 的最短时间，很明显的 dijkstra 板子题。

dijkstra 算法是一个用来计算从一个顶点到其余各顶点的最短路径算法，解决的是有权图中的最短路问题。

其核心步骤是从起点开始，采用贪心算法的策略，每次遍历到起点距离最近且未访问过的顶点的邻接顶点，直到扩展到终点为止。

操作过程要用 $dis$ 数组来保存每个点和起点的最短距离，$vis$ 数组记录每个点是否被访问过。

在贪心过程中，$dis_{x}$ 是否更新取决于 $dis_{y} + w$ 是否小于原来的 $dis_{x}$，其中 $x$ 和 $y$ 是两个相邻的点，$w$ 为从 $x$ 到 $y$ 这条边的权值。

但这道题要求只有当前时刻为 $k_{i}$ 的倍数才能走，所以松弛操作要改一下，可以分是 $k_{i}$ 倍数和不是 $k_{i}$ 倍数两种情况讨论。

所以松弛操作的代码如下

```cpp
	int x = G[tmp.v][i].v, t = G[tmp.v][i].t;
			int y = G[tmp.v][i].w, w;
			if (dis[tmp.v] % t == 0) w = dis[tmp.v];
			else if (dis[tmp.v] % t != 0) w = (dis[tmp.v] / t + 1) * t; 
			if (dis[x] > w + y){
				dis[x] = w + y;
				q.push(node{x, dis[x], -1});
			}
```

### AC Code

```cpp

#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int N = 1e5 + 5;
int n, m, s, t, dis[N];
bool vis[N];
struct node{
	int v, w, t;
	bool operator < (const node &a) const{
		return w > a.w;
	}
};
vector<node> G[N];
void Dijkstra (){
	memset (dis, 0x3f, sizeof(dis));
	priority_queue<node> q;
	dis[s] = 0;
	q.push(node{s, 0, -1});
	while (!q.empty()){
		node tmp = q.top(); q.pop();
		if (vis[tmp.v]) continue;
		vis[tmp.v] = 1;
		for (int i = 0; i < G[tmp.v].size(); ++i){
			int x = G[tmp.v][i].v, t = G[tmp.v][i].t;
			int y = G[tmp.v][i].w, w;
			if (dis[tmp.v] % t == 0) w = dis[tmp.v];
			else if (dis[tmp.v] % t != 0) w = (dis[tmp.v] / t + 1) * t; 
			if (dis[x] > w + y){
				dis[x] = w + y;
				q.push(node{x, dis[x], -1});
			}
		}
	}
}
signed main (){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin >> n >> m >> s >> t;
	for (int i = 1; i <= m; ++i){
		int u, v, w, t;
		cin >> u >> v >> w >> t;
		G[u].push_back(node{v, w, t});
		G[v].push_back(node{u, w, t});
	} 
	Dijkstra();
	if (dis[t] > 1e18) cout << -1 << '\n';
	else cout << dis[t] << '\n';
	return 0;
}

---

