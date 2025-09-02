# Valuable Paper

## 题目描述

The pandemic is upon us, and the world is in shortage of the most important resource: toilet paper. As one of the best prepared nations for this crisis, BubbleLand promised to help all other world nations with this valuable resource. To do that, the country will send airplanes to other countries carrying toilet paper.

In BubbleLand, there are $ N $ toilet paper factories, and $ N $ airports. Because of how much it takes to build a road, and of course legal issues, every factory must send paper to only one airport, and every airport can only take toilet paper from one factory.

Also, a road can't be built between all airport-factory pairs, again because of legal issues. Every possible road has number $ d $ given, number of days it takes to build that road.

Your job is to choose $ N $ factory-airport pairs, such that if the country starts building all roads at the same time, it takes the least amount of days to complete them.

## 样例 #1

### 输入

```
3 5
1 2 1
2 3 2
3 3 3
2 1 4
2 2 5```

### 输出

```
4```

# 题解

## 作者：lijinghui (赞：5)

# CF1423B 题解

题解貌似都是网络流和 Dinic 的方法，对于一个蒟蒻这些还是太难了，所以我用了一种新奇的方法。

## 小题面
给你两个大小为 $n$ 的点集，在 $m$ 条边中选 $n$ 条边，使得每个点连且仅连一条边，问选取的边中边权最大值最小是多少，如无解，输出 $-1$。

## 小方法
首先如果我们可以很容易看出本体符合单调性，即可用二分答案加 check 去找到答案。

而若当前二分到的边权为 $w$，那么边权小于等于 $w$ 的边都能进入候选集合，为此我们可以将边按边权进行排序。

check 时，可以想到直接进行建图。因每个连通块间互不影响，可以将连通块分开考虑。在每个连通块中，若其中开始就给定的两个集合中的存在在该连通块中的节点个数不同，则必定无法满足题目要求，这部分可以用并查集进行实现。（后面步骤均基于这条）

如果该连通块本身就为包含一个环（由所有节点组成），可以邻点成对连接即可。若本身不是一个环，那么必定存在连边仅为 $1$ 的点，而仅连一条边的点的选取方案是一定的，所以我们每次将选取方案确定的点按方案取出，进行一个删边删点操作，若一点唯一搭配的点已被其他选过则必定无解。所有操作结束后，剩下的必定是个环，而必定有解。

那么本题便简单的做完了。

## 小代码
```cpp
#include<bits/stdc++.h>//码风不好，请见谅
using namespace std;
#define endl '\n'
#define ll long long
const int N=2e5+10;
struct EDGE
{
	int x,y,d;
}edge[N];
int book[N],du[N],n,m,fa[N],s[N],t[N];
bool cmp(EDGE a,EDGE b)
{
	return a.d<b.d;
}
int find(int x)
{
	if(fa[x]==x)return x;
	else return fa[x]=find(fa[x]);
}
vector<int>v[N];
bool check(int f)
{
	for(int i=1;i<=(n<<1);i++)//初始化+清空
	{
		s[i]=t[i]=0;
		book[i]=0;
		fa[i]=i;
		v[i].clear();
	}
	for(int i=1;i<=f;i++)//建图
	{
		v[edge[i].x].push_back(edge[i].y+n);
		v[edge[i].y+n].push_back(edge[i].x);
		fa[find(edge[i].x)]=find(edge[i].y+n);//并查集
	}
	queue<int>q;
	for(int i=1;i<=n;i++)//为下面的删边初始化
	{
		if(v[i].size()==1)
		{
			q.push(i);
		}
		if(v[i+n].size()==1)
		{
			q.push(i+n);
		}
		du[i]=v[i].size();
		du[i+n]=v[i+n].size();
	}
	while(!q.empty())//删边
	{
		int u=q.front(),k=0;
		q.pop();
		if(book[u])continue;
		for(int i=0;i<v[u].size();i++)
		{
			int vv=v[u][i];
			if(!book[vv])
			{
				du[vv]--;
				k=vv;
				break;
			}
		}
		if(!k)continue;
		book[u]=1;
		book[k]=1;
		u=k;
		for(int i=0;i<v[u].size();i++)
		{
			int vv=v[u][i];
			du[vv]--;
			if(du[vv]==1)
			{
				q.push(vv);
			}
		}
	}
	for(int i=1;i<=(n<<1);i++)
	{
		if(!(book[i]|du[i]))
		{
			return 0;
		}
	}
	for(int i=1;i<=n;i++)
	{
		s[find(i)]++;
	}
	for(int i=1+n;i<=n+n;i++)
	{
		t[find(i)]++;
	}
	for(int i=1;i<=(n<<1);i++)
	{
		if(s[i]!=t[i])return 0;
	}
	return 1;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(NULL);cout.tie(NULL);
	cin>>n>>m;
	for(int i=1;i<=m;i++)cin>>edge[i].x>>edge[i].y>>edge[i].d;
	sort(edge+1,edge+m+1,cmp);//排序
	int l=1,r=m,ans=-1;//二分
	while(l<=r)
	{
		int mid=l+r>>1;
		if(check(mid))
		{
			r=mid-1;
			ans=edge[mid].d;
		}
		else l=mid+1;
	}
	cout<<ans;
	return 0;
}
```
**~~希望看完本篇题解才A的人给个赞，谢谢~~**

---

## 作者：Fido_Puppy (赞：4)

$$\texttt{Description}$$

[Valuable Paper](https://www.luogu.com.cn/problem/CF1423B)

如果无法修好是要输出 `-1` 的，似乎翻译中没有提到。

$$\texttt{Solution}$$

发现最终时间是所有修路时间的最大值，最小化最大值，容易想到二分答案。

考虑如何判断是否能使最终修路时间 $\le mid$。

首先把所有修路时间 $\le mid$ 的路拎出来，然后就只需要判断能否找出 $n$ 条路，使得 $n$ 个厕纸工厂和 $n$ 个机场匹配。

可以发现这是一张二分图，只需要求出二分图最大匹配，并且判断是否与 $n$ 相等即可。

求二分图最大匹配我这里用的是 $\text{Dinic}$ 算法，需要加上**当前弧优化**才能过。

时间复杂度约为 $\Theta(m \sqrt n \log V)$。

$$\texttt{Code}$$

```cpp
#include <bits/stdc++.h>

// #define debug

int main() {
    std :: ios_base :: sync_with_stdio(false);
    std :: cin.tie(nullptr);

    #ifndef debug
        std :: istream &fin = std :: cin;
        std :: ostream &fout = std :: cout;
    #endif
    #ifdef debug
        std :: ifstream fin("code.in");
        std :: ofstream fout("code.out");
    #endif

    int n, m;
    fin >> n >> m;

    std :: vector <int> u(m + 5), v(m + 5), t(m + 5);
    
    for (int i = 1; i <= m; ++i) {
        fin >> u[i] >> v[i] >> t[i];
    }

    class node {
        public:
            int to, nxt, flow;
    };
    std :: vector <node> e(m * 2 + n * 4 + 5);
    std :: vector <int> head(n * 2 + 5);
    int tot;

    auto add = [&] (int u, int v, int w) -> void {
        e[ ++tot ] = (node){v, head[u], w};
        head[u] = tot;
        e[ ++tot ] = (node){u, head[v], 0};
        head[v] = tot;
    };

    std :: vector <bool> vis(n * 2 + 5);
    std :: vector <int> d(n * 2 + 5), cur(n * 2 + 5);
    std :: queue <int> q;

    auto bfs = [&] () {
        std :: fill(vis.begin(), vis.end(), false);
        std :: fill(d.begin(), d.end(), 0);
        vis[0] = true; q.push(0); cur[0] = head[0];
        while (!q.empty()) {
            int x = q.front(); q.pop();
            for (int i = head[x]; i; i = e[i].nxt) {
                int v = e[i].to;
                if (e[i].flow && !vis[v]) {
                    vis[v] = true;
                    d[v] = d[x] + 1;
                    cur[v] = head[v];
                    q.push(v);
                }
            }
        }
        return vis[ n * 2 + 1 ];
    };

    auto dfs = [&] (auto &self, int now, int MaxFlow) {
        if (now == n * 2 + 1) return MaxFlow;
        if (!MaxFlow) return 0;
        int sum = 0;
        for (int i = cur[now]; i; i = e[i].nxt) {
            int v = e[i].to; cur[now] = i;
            if (d[v] == d[now] + 1 && e[i].flow) {
                int Flow = self(self, v, std :: min(MaxFlow, e[i].flow));
                e[i].flow -= Flow;
                e[ i ^ 1 ].flow += Flow;
                sum += Flow;
                MaxFlow -= Flow;
                if (!MaxFlow) break;
            }
        }
        return sum;
    };

    auto dinic = [&] () {
        int ans = 0;
        while (bfs()) {
            ans += dfs(dfs, 0, std :: numeric_limits <int> :: max());
        }
        return ans;
    };

    auto check = [&] (int mid) {
        tot = 1;
        std :: fill(head.begin(), head.end(), 0);
        for (int i = 1; i <= m; ++i) {
            if (t[i] <= mid) {
                add(u[i], v[i] + n, 1);
            }
        }
        for (int i = 1; i <= n; ++i) {
            add(0, i, 1);
            add(i + n, n * 2 + 1, 1);
        }
        int ans = dinic();
        return (ans == n);
    };

    if (!check(std :: numeric_limits <int> :: max())) {
        return fout << "-1\n", 0;
    }

    int l = 0, r = 1e9;
    while (l < r) {
        int mid = (l + r) / 2;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }

    fout << r << '\n';

    return 0;
}
```

$$\texttt{Thanks for watching!}$$

---

## 作者：MiRaciss (赞：3)

首先我们可以转化一下题意：

## 题意

有一个点数为 $n$ 的点集 $V_1$， 一个点数为 $n$ 的点集 $V_2$ ,一个边数为 $m$ 的边集 $E$ 使得 $\forall\left( {u,v}\right)\in E ,u\in V_1 ,v\in V_2$ 且每条边的有一个长度为 $a_i$ 的权值 ，现在可以任意选择 $E$ 集里的边组成一个新的边集 $E_1$ ， 当 $E_1$ 满足该边集的边能够使得 两个点集 的完备匹配数量为 n 时，我们就称 $E_1$ 是满足条件的。对于每一个 $E_1$，我们定义它的贡献为其中边权最大的那条边，现在求最少贡献。

## 题解

通过转换后的题意可以发现，我们要求的是 最大的最小 ，且贡献有单调性所以，考虑二分答案那么现在问题就转换成了 存在性问题 ，设现在二分的答案为 x ，我们只需要将边权小于 x 的边放进 $E_1$ 跑网络流即可

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll INF=0x7f7f7f7f;

struct zz{
	int u;
	ll w;
	int id;
	zz(int U,ll W,int ID){
		u=U,w=W,id=ID;
	}
};
vector<zz> v[20005];

void Add(int x,int y,int z){
	int idx=v[x].size();
	int idy=v[y].size();
	v[x].push_back(zz(y,z,idy));
	v[y].push_back(zz(x,0,idx));
}

int n,m,s,t,Max=0;
int dist[20005];
int be[20005];

struct Dinic{
	bool BFS(){
		bool f=0;
		memset(dist,-1,sizeof dist);
		queue<int> q;q.push(s);
		dist[s]=0,be[s]=0;
		while(q.size()){
			int x=q.front();q.pop();
			for(int i=0;i<v[x].size();i++){
				int y=v[x][i].u;
				ll w=v[x][i].w;
				if(!w||dist[y]!=-1) continue;
				q.push(y),be[y]=0,dist[y]=dist[x]+1;
				if(y==t) f=1;
			}
		}
		return f;
	}
	ll DFS(int x,ll sum){
		if(x==t||!sum) return sum;
		ll ans=0;
		for(int i=be[x];i<v[x].size()&&sum!=ans;i++){
			be[x]=i;
			int y=v[x][i].u;
			ll w=v[x][i].w;
			if(!w||dist[y]!=dist[x]+1) continue;
			int now=DFS(y,min(sum-ans,w));
			if(!now) dist[y]=0;		 
			v[x][i].w-=now,v[y][v[x][i].id].w+=now;
			ans+=now; 
		}
		return ans;
	}
	ll dinic(){
		ll ans=0;
		while(BFS()){
			ll now=0;
			while(now=DFS(s,INF)) ans+=now;
		}
		return ans;
	}
}T;

struct ss{
	int u;ll w;
};
vector<ss> V[20005]; 

bool Check(ll val){
	for(int i=s;i<=t;i++) v[i].clear();
	for(int i=1;i<=n;i++) Add(s,i,1),Add(i+n,t,1);
	for(int x=1;x<=n;x++){
		for(int i=0;i<V[x].size();i++){
			int y=V[x][i].u;ll w=V[x][i].w;
			if(val>=w) Add(x,y,1);
		}
	}
	return T.dinic()==n;
}

int main(){
	cin>>n>>m;
	s=0,t=n+n+1;
	for(int i=1,x,y,z;i<=m;i++)
		scanf("%d%d%d",&x,&y,&z),V[x].push_back((ss){y+n,z}),Max=max(Max,z);
	
	int l=1,r=Max,ans=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(Check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	cout<<ans<<endl;
	return 0;
} 

```




---

## 作者：LEE114514 (赞：2)

## 思路

要在让有对应的工厂尽可能多的情况下花费时间尽可能少？**~~我知道！是最小费用最大流！秒了！~~**

当然，这是错误的。所有路线同时工作而非先后，意味着耗时不是 $d_i+d_j+d_k+\cdots$，而是 $\max\{d_i,d_j,d_k,\cdots\}$。费用流算法不是用来解决这种问题的。所以，我们考虑最大流判定二分。

算法流程大致上就是二分最大时间，然后跑网络流算法查看只经过小于等于给定时间的边最大流是否为 $n$。在这里我们使用 Dinic 算法，由于原图是单位容量图，可以证明单次 Dinic 复杂度为 $O(n \min(n^\frac{1}{2},m^\frac{2}{3}))$。

不过，此题对常数要求较高。因为答案必然是题目中出现过的时间或无解，所以我们只需二分在离散化后时间数组中的下标。

## Code

```cpp
#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;
const int maxn=2e4+5;
const int maxm=3e5+5;
struct Edge{
	int to,Next,w,c;
}G[maxm];
int head[maxn],cur[maxn],cnt=1;
void add(int u,int v,int w,int c){
	G[++cnt]=Edge{v,head[u],w,c};
	head[u]=cnt;
}
void ADD(int u,int v,int w,int c){
	add(u,v,w,c);
	add(v,u,0,c);
}
int dep[maxn];
int u,v,w;
queue<int> q;
int L,R,MID;
int n,m,s,t;
bool BFS(int st,int ed){
	memcpy(cur,head,(sizeof(int))*(n+n+2));
// 	memset(dep,0,sizeof dep);
    fill(dep,dep+n+n+2,0);
	q.push(st);
	dep[st]=1;
	while(!q.empty()){
		u=q.front();
		q.pop();
		for(int i=head[u];i;i=G[i].Next){
			v=G[i].to;
			if(G[i].w<=0||G[i].c>MID||dep[v]) continue;
			dep[v]=dep[u]+1;
			q.push(v);
		}
	}
	return dep[ed];
}
int dfs(int u,int flow){
	if(u==t) return flow;
	int res=0;
	for(int &i=cur[u];i&&flow;i=G[i].Next){
		int v=G[i].to;
		int w=G[i].w;
		if(w<=0||dep[v]!=dep[u]+1||G[i].c>MID) continue;
		int tmp=dfs(v,min(flow,w));
		G[i].w-=tmp;
		G[i^1].w+=tmp;
		flow-=tmp;
		res+=tmp;
	}
	return res;
}
int res;
void Dinic(){
	res=0;
	while(BFS(s,t)) res+=dfs(s,INT_MAX);
}
int b[100005],len;
int main(){
	scanf("%d%d",&n,&m);
	s=0,t=n+n+1;
	for(int i=1;i<=n;++i) ADD(s,i,1,0),ADD(i+n,t,1,0);
	for(int i=1;i<=m;++i){
		scanf("%d%d%d",&u,&v,&w);
		ADD(u,v+n,1,w);
		b[i]=w;
	}
	sort(b+1,b+m+1);
	len=unique(b+1,b+m+1)-(b+1);
	for(int i=3;i<=cnt;i+=2) G[i].c=G[i-1].c=lower_bound(b+1,b+len+1,G[i].c)-b;
	L=1,R=len;
	while(L<=R){
		MID=(L+R)>>1;
		for(int i=3;i<=cnt;i+=2){//这个for是把所有反边流量还给正边
			G[i-1].w+=G[i].w;
			G[i].w=0;
		}//此处有一个优化，可以把边按照时间排序并且只处理时间小于等于上一次 MID 的边
		Dinic();
		if(res==n) R=MID-1;
		else L=MID+1;
	}
	printf("%d",(L==len+1)?(-1):b[L]);
}
```

---

## 作者：ql12345 (赞：2)

# 二分+最大流板子

### [题面](https://codeforces.com/contest/1424/problem/B)

### Solution：

先把样例放这：

![](https://cdn.luogu.com.cn/upload/image_hosting/vvbd039c.png)

建图：

工厂看成右边点，机场左边点，源点向工厂连边权为0的边，因为要代表每个工厂只能匹配一个机场，所以这条边的容量应为1，每个机场向汇点连边权为0的边，同理。机场跟工厂之间连边，以天数为边权

**注意：** 正常网络流的建图以上说的“边权”应该是“容量”，但这里的“边权”是要额外记录的“边权”，这在最大流+二分的模型中常见，在一般最大流中不会被用到

本题很容易想成费用流（我好菜），但题中要求的是最大值不是和，所以不是求满流下的最小费用，于是就想到了二分最大值

我们二分答案，check的时候扫描连好的所有的正向边，如果边权为0，代表是源汇点连的边，将容量赋为1，残余网络里容量为0。如果边权为正数，将如果边权大于mid，这条边不能选，容量赋为0，否则，容量为1，同样记得更新残余网络

然后Dinic看最大流是否满流即可！（如果满流代表选天数少于等于mid的边是可以的，反之不可以）

### Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100010,M=5000010,INF=1e18;
int n,m,S,T,head[N],tot=1,q[N],d[N],cur[N];
struct E{int ver,nxt,ww,w;}e[M];
inline void add_e(int u,int v,int w){e[++tot]=(E){v,head[u],0,w},head[u]=tot;}
inline void add(int u,int v,int w){add_e(u,v,w);add_e(v,u,0);}
bool bfs(){
	int hh=0,tt=0;
	memset(d,-1,sizeof d);
	q[0]=S,d[S]=0,cur[S]=head[S];
	while(hh<=tt){
		int x=q[hh++];
		for(int i=head[x];i;i=e[i].nxt){
			int y=e[i].ver,z=e[i].w;
			if(d[y]==-1&&z){
				d[y]=d[x]+1;
				cur[y]=head[y];
				if(y==T)return 1;
				q[++tt]=y;
			}
		} 
	}
	return 0;
}
int find(int u,int limit){
	if(u==T)return limit;
	int flow=0;
	for(int i=cur[u];i&&flow<limit;i=e[i].nxt){
		int y=e[i].ver,z=e[i].w;
		cur[u]=i;
		if(d[y]==d[u]+1&&z){
			int t=find(y,min(z,limit-flow));
			if(!t)d[y]=-1;
			e[i].w-=t,e[i^1].w+=t,flow+=t;
		}
	}
	return flow;
}
int Dinic(){
	int r=0,flow;
	while(bfs())while(flow=find(S,INF))r+=flow;
	return r;
}
bool check(int mid){
	for(int i=2;i<=tot;i+=2)
		if(e[i].ww>0&&e[i].ww<=mid){
			e[i].w=1;
			e[i^1].w=0;
		}
		else if(e[i].ww>0)e[i].w=0,e[i^1].w=0;
		else if(e[i].ww==0)e[i].w=1,e[i^1].w=0;
	int res=Dinic();
	return (res>=n);
}
signed main(){
	cin>>n>>m;S=n*2+1,T=S+1;
	for(int i=1;i<=n;++i)add(S,i,1);
	for(int i=1;i<=n;++i)add(i+n,T,1);
	for(int i=1,u,v,w;i<=m;++i){
		cin>>u>>v>>w;
		add(u,v+n,w);e[tot].ww=e[tot^1].ww=w;
	}
	int L=0,R=1e9;
	while(L<R){
		int mid=(L+R)>>1;
		if(check(mid))R=mid;else L=mid+1;
	}
	if(L==1e9)return cout<<-1<<endl,0;
	cout<<L<<endl;
	return 0;
}
```

---

## 作者：EuphoricStar (赞：1)

## 题外话

第一眼：*1900 的 flow 题？

第二眼：这评分挺合理的

## 思路

注意到题中说的是 **“这些路同时开始修”**，所以可以发现答案具有单调性。我们二分一个 $x$，则题目转化为：

> 有 $N$ 个工厂和 $N$ 个机场，从 $M$ 条给定的边中选择 $N$ 条修建，使得每个工厂都能且仅能与一个机场连边。每条边的用时为 $d_i$，最大边的用时不能超过 $x$。

可以看出这是一个很明显的**二分图**模型。建立源点 $S$ 和汇点 $T$，$S$ 向所有工厂连流量为 $1$ 的边，所有机场向 $T$ 连流量为 $1$ 的边，给定的 $M$ 条边中，$d_i > x$ 的边舍去，其余对应连流量为 $1$ 的边。跑一遍 Dinic，判断是否满流即可。

Dinic 跑二分图的复杂度是 $O(N^{\frac{1}{2}}M)$，所以总的时间复杂度为 $O(N^{\frac{1}{2}}M \log d)$。

## 代码

[code](https://pastebin.ubuntu.com/p/FHd5HGfjSW/)

---

