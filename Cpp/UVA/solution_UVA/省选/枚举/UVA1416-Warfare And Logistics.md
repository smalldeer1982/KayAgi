# Warfare And Logistics

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=447&page=show_problem&problem=4162

[PDF](https://uva.onlinejudge.org/external/14/p1416.pdf)

# 题解

## 作者：maomao9173 (赞：4)

[更好的阅读体验点击这里。](https://www.cnblogs.com/maomao9173/p/10771157.html)

题目大意：

- 求图中两两点对最短距离之和

- 允许你删除一条边，让你最大化删除这个边之后的图中两两点对最短距离之和。

暴力：每次枚举删除哪条边，以每个点为源点做一次最短路，复杂度$O(NM^2logN)$。

**值得注意的是，$Dijkstra$的复杂度$O(NlogN)$是关于边而非点的**。

这个复杂度对于$n=100,m=1000$的数据难以接受。我们考虑对每个点建出其最短路树。容易想到，只有删除到这个点的最短路树上的边时，才需要再做一次$Dijkstra$。也就是说每个源点只需要做$n$次最短路，复杂度变成$O(N^2MlogN)$。

代码实现起来比较麻烦。。本弱调了整整一晚上。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define LL long long
const int N = 100 + 5;
const int M = 2000 + 5;
const int INF = 0x3f3f3f3f;

int n, m, l, kase, ban[M];

struct Graph {
	
	int cnt, head[N];
	
	struct Edge {int from, nxt, to, id, w;}e[M];
	
	void clear () {
		cnt = -1;
		for (int i = 1; i <= n; ++i) {
			head[i] = -1;
		}
	}
	
	void add_edge (int u, int v, int w) {
		++cnt; e[cnt] = (Edge) {u, head[u], v, cnt, w}; head[u] = cnt;
	}
	
	struct HeapNode {
		int u; LL d;
		bool operator < (HeapNode rhs) const {
			return d > rhs.d;
		}
	};
	
	priority_queue <HeapNode> pq;
	
	int done[N], _fa[N][N]; LL _dis[N][N]; 
	//dis[i][j] -> i to j
	//fa[i][j] -> i as source, j's father
	
	void dijkstra (int s) {
		kase = kase + 1;
		pq.push ((HeapNode) {s, 0});
		LL *dis = _dis[s]; int *fa = _fa[s];
		for (int i = 1; i <= n; ++i) {
			fa[i] = -1, dis[i] = i == s ? 0 : INF;
		}
		while (!pq.empty ()) {
			HeapNode now = pq.top (); pq.pop ();
			if (done[now.u] == kase) continue;
			for (int i = head[now.u]; ~i; i = e[i].nxt) {
				int v = e[i].to;
				if (ban[i]) continue;//禁用的边 -> 不用 
				if (dis[v] > dis[now.u] + e[i].w) {
					fa[v] = now.u;
					dis[v] = dis[now.u] + e[i].w;
					pq.push ((HeapNode) {v, dis[v]});
				}
			} 
			done[now.u] = kase;
		}
//		cout << "s = " << s << endl;
//		for (int i = 1; i <= n; ++i) {
//			cout << "dis[" << i << "] = " << dis[i] << endl;
//		}
	}
}G;

bool have[N][M]; int minw[N][N];

struct Tree {
	
	vector <int> Gr[N];
	
	int sz[N]; LL sum[N], dis[N];
	
	//sz[u] -> 点u的子树大小
	//sum[u] -> 点u到其子树里所有点的距离和
	
	void prep (int u) {
		sz[u] = 1; sum[u] = dis[u];
		for (int i = 0; i < (int)Gr[u].size (); ++i) {
			int v = Gr[u][i];
			prep (v);  
			sz[u] += sz[v];
			sum[u] += sum[v];
		}
	}
	
	void build (int s, LL *_dis, int *fa, int cmd) {
		for (int i = 1; i <= n; ++i) Gr[i].clear ();
		memcpy (dis, _dis, sizeof (dis));
		for (int i = 1; i <= n; ++i) {
			if (fa[i] != -1) {
				Gr[fa[i]].push_back (i);
				if (cmd == 1) {
					have[fa[i]][i] = true;
					have[i][fa[i]] = true;
				}
			}
		}
		prep (s);
//		for (int i = 1; i <= n; ++i) {
//			cout << "dis[" << i << "] = " << dis[i] << endl;
//			cout << "sum[" << i << "] = " << sum[i] << endl;
//		} 
	} 
	
	LL get_ans (int s, LL *_dis, int *fa, int cmd) {
		build (s, _dis, fa, cmd);
		return sum[s] + (n - sz[s]) * l;
	}
	
}tr[N];//tr[i] -> 点i的最短路树 

signed main () {
//	freopen ("data.in", "r", stdin);
//	freopen ("data.out", "w", stdout);
	while (cin >> n >> m >> l) {
		G.clear ();
		memset (have, 0, sizeof (have));
		memset (minw, 0x3f, sizeof (minw));
		for (int i = 1; i <= m; ++i) {
			static int u, v, w;
			cin >> u >> v >> w;
			G.add_edge (u, v, w);
			G.add_edge (v, u, w);
			minw[u][v] = min (minw[u][v], w);
			minw[v][u] = min (minw[v][u], w);
		}
		LL ans1 = 0, ans2 = 0;
		for (int s = 1; s <= n; ++s) {
			G.dijkstra (s);
			ans1 += tr[s].get_ans (s, G._dis[s], G._fa[s], 1);
			//存一下最初的have 
		}
		cout << ans1 << " ";
		for (int i = 0; i <= G.cnt; i += 2) {
			//每次枚举禁用一条边。
			LL res_now = 0;
			ban[i] = ban[i + 1] = true;//双向都要禁 
			for (int s = 1; s <= n; ++s) { //枚举删除之后每一棵最短路树的状况 
				int u = G.e[i].from, v = G.e[i].to, w = G.e[i].w;
				if (have[u][v] && w == minw[u][v]) G.dijkstra (s);
				res_now += tr[s].get_ans (s, G._dis[s], G._fa[s], 0);
			}
			ban[i] = ban[i + 1] = false;
			ans2 = max (ans2, res_now);
		}
		cout << ans2 << endl; 
	}
}
```

---

## 作者：wangbinfeng (赞：2)

[![](https://img.shields.io/badge/题目-UVA1416_Warfare_And_Logistics-green)
![](https://img.shields.io/badge/难度-省选/NOI−-purple)
![](https://img.shields.io/badge/考点-图论（最短路树）-blue)
![](https://img.shields.io/badge/题型-传统题-red)](https://www.luogu.com.cn/problem/UVA1416)
[![](https://img.shields.io/badge/作者-wangbinfeng(387009)-yellow)](https://www.luogu.com.cn/user/387009) 

------------

蓝书上的例题，题解里竟然没有相同的做法，用蓝书的方法写一篇题解。同时在这个时间点，也庆祝 luogu 博客的浴火重生，兼以测试 luogu 新的文章功能。

对于本题，如果只求 $c$，思路应该很容易能想到，Floyd 算法求多元最短路即可，时间复杂度为 $\Theta \left(n^3\right)$，代码略。考虑到堆优化的 Dijkstra 算法时间复杂度为 $\Theta \left(nm\log n\right)$，但常数大于 Floyd 算法，差别不大。

枚举删掉的边可以求得 $c'$，但时间复杂度明显过高（$\begin{cases}\Theta \left(n^3m\right) && \text{for} && Floyd  \\\Theta \left(nm^2\log n\right) &&\text{for}&& Dijkstra\end{cases}$）。显然无法接受。

考虑最短路树。在源点确定得情况下，只要最短路树不被破坏，那么起点到终点的最短路都不会发生改变。那么对于每个源点，需要删的边有且只有 $n-1$ 条，相比于每次枚举都删除 $m$ 条好了太多。对于 Dijkstra 算法，时间复杂度由 $\Theta \left(nm^2\log n\right)$ 优化到 $\Theta \left(n^2m\log n\right)$，就可以接受了。注意一下重边即可。

最后附一下样例，注意不需要且不应该输出 `Case #*`：
```
.in
4 6 1000
1 3 2
1 4 4
2 1 3
2 3 3
3 4 1
4 2 2
.out
28 38
```

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
class Edge{public:int from,to,dist;};
class HeapNode{
public:
	int d,u;
	bool operator<(const HeapNode& rhs)const{return d>rhs.d;}
};
template<size_t SZ>
class Dijkstra{
public:
	int n;
	vector<Edge> edges;
	vector<int>g[SZ];
	bitset<SZ> done;
	int d[SZ],p[SZ];//d 距离，p 当前弧
	priority_queue<HeapNode> q;
	void init(const int n){
		this->n=n;
		for(int i=0;i<=n;i++)g[i].clear();
		edges.clear();
	}
	void addEdge(const int from,const int to,const int dis){
		edges.push_back({from,to,dis});
		g[from].push_back(edges.size()-1);
	}
	void dijkstra(const int s){
		while(!q.empty())q.pop();
		memset(d,0x7f,sizeof(d));
		d[s]=0;
		done.reset();
		for(q.push((HeapNode){0,s});!q.empty();q.pop()){
			const HeapNode now=q.top();
			const int u=now.u;
			if(done[u])continue;
			done[u]=true;
			for(auto &i:g[u]){
				//cerr<<"[stderr]run here, the g[u][i] is "<<i<<", now u="<<u<<endl;
				Edge &e=edges[i];
				//cerr<<"[stderr]e.dist="<<e.dist<<", e.to="<<e.to<<", d[e.to]="<<d[e.to]<<", d[u]="<<d[u]<<endl;
				if(e.dist>0 && d[e.to]>d[u]+e.dist){
					d[e.to]=d[u]+e.dist;
					p[e.to]=i;
					q.push((HeapNode){d[e.to],e.to});
				}
			}
		} 
	}
	void show(){
#ifndef ONLINE_JUDGE
		cerr<<"******[stderr]showing start!******"<<endl;
		cerr<<n<<endl<<endl;
		for(auto i:edges)cerr<<'('<<i.from<<','<<i.to<<','<<i.dist<<") ";
		cerr<<endl<<endl;
		for(int i=0;i<=n;i++){
			cerr<<i<<": ";
			for(auto j:g[i])cerr<<j<<' ';
			cerr<<endl;
		}
		cerr<<endl;
		for(int i=0;i<n;i++)cerr<<done[i]<<' ';
		cerr<<endl<<endl;
		for(int i=0;i<n;i++)cerr<<d[i]<<' ';
		cerr<<endl<<endl;
		for(int i=0;i<n;i++)cerr<<p[i]<<' ';
		cerr<<endl<<endl;
		cerr<<"*******[stderr]showing end!*******"<<endl;
#endif
	}
};
const int maxn=109;
Dijkstra<maxn>solver;
vector<int>gr[maxn][maxn];
int n,m,l,idx[maxn][maxn],sum_single[maxn],c,c1;
bitset<maxn>used[maxn][maxn];
inline int compute_c(){
	int ans=0;
	for(int i=0;i<=n;i++)for(int j=0;j<=n;j++)used[i][j].reset();
	for(int src=0;src<n;src++){
		solver.dijkstra(src);
		//solver.show();
		sum_single[src]=0;
		for(int i=0;i<n;i++){
			if(i!=src)used[solver.edges[solver.p[i]].from][i][src]
				=used[i][solver.edges[solver.p[i]].from][src]=true;
			sum_single[src]+=(solver.d[i]>=0x3f3f3f3f?l:solver.d[i]);
		}
		ans+=sum_single[src];
	}
	return ans;
}
inline int compute_newc(const int a,const int b){
	int ans=0;
	for(int src=0;src<n;src++)
		if(!used[a][b][src])ans+=sum_single[src];
		else{
			solver.dijkstra(src);
			for(int i=0;i<n;i++)ans+=(solver.d[i]>=0x3f3f3f3f?l:solver.d[i]);
		}
	return ans;
}
signed main(){
	if(scanf("%d%d%d",&n,&m,&l)!=3)return 0;
	solver.init(n);
	for(int i=0;i<n;i++)for(int j=0;j<n;j++)gr[i][j].clear();
	for(int i=0,a,b,s;i<m;i++){
		scanf("%d%d%d",&a,&b,&s),a--,b--;
		gr[a][b].push_back(s),gr[b][a].push_back(s);
	}
	for(int i=0;i<n;i++)for(int j=i+1;j<n;j++)if(!gr[i][j].empty()){
		sort(gr[i][j].begin(),gr[i][j].end());
		solver.addEdge(i,j,gr[i][j][0]);
		idx[i][j]=solver.edges.size()-1;
		solver.addEdge(j,i,gr[i][j][0]);
		idx[j][i]=solver.edges.size()-1;
	}
	c=compute_c(),c1=-1;
	//solver.show();
	for(int i=0;i<n;i++)for(int j=i+1;j<n;j++)if(!gr[i][j].empty()){
		if(gr[i][j].size()==1)solver.edges[idx[i][j]].dist=solver.edges[idx[j][i]].dist=-1;
		else solver.edges[idx[i][j]].dist=solver.edges[idx[j][i]].dist=gr[i][j][1];
		c1=max(c1,compute_newc(i,j));
		solver.edges[idx[i][j]].dist=solver.edges[idx[j][i]].dist=gr[i][j][0];
	}
	printf("%d %d\n",c,c1);
	main(); 
}
```

---

## 作者：Legitimity (赞：2)

讲一种另类的做法。

第一问直接一遍 `floyd`。

第二问，首先考虑暴力，枚举删掉哪条边，然后作 `floyd`，时间复杂度是 $O(n^3m)$，无法接受。

然后考虑优化，在上述暴力中，我们发现其实有很多信息被浪费了，比如由边集 $\{1,2,3,5\}$
构成的图和由边集 $\{1,2,3,4\}$ 构成的图中，她们的交集 $\{1,2,3\}$ 其实是计算了两次的，这一部分的计算是没有必要的。

在考虑一下 `floyd` 的过程本质：其实是对于不完整图的逐步完整化：从一开始没有点，然后逐渐向其中加点（枚举 $k$），然后计算新加点的贡献。

那么就完全可以计算出边集 $\{1,2,3\}$ 的最短路信息后保存，分别枚举 $4$ 和 $5$ 这两条边产生的贡献，在$\{1,2,3\}$ 的最短路信息上修改。

什么算法时候干这样的事？分治，解决小问题后在小问题的基础上解决大问题。

设 $f(l,r)$ 表示由除 $[l,r]$ 外的边集构成的最短路信息，当 $f(l,r)$ 计算出来后，$f(l,mid)$ 只需要计算边 $[mid+1,r]$ 产生的贡献，在 $f(l,r)$ 的基础上修改就可以了；$f(mid+1,r)$ 同理。

主定理得出时间复杂度为 $O(n^2m\log m)$ ，可以接受；空间上因为需要保存每层的信息，所以空间复杂度为 $O(n^2\log m)$，可以接受。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define rg register
#define ll long long
#define inf 0x3f3f3f3f
#define djq 998244353
#define lowbit(x) (x&(-x))
inline void file(){
	freopen("P1341.in","r",stdin);
	freopen("P1341.ans","w",stdout);
}
char buf[1<<21],*p1=buf,*p2=buf;
inline int getc(){
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
	rg int ret=0,f=0;char ch=getc();
    while(!isdigit(ch)){if(ch==EOF)exit(0);if(ch=='-')f=1;ch=getc();}
    while(isdigit(ch)){ret=ret*10+ch-48;ch=getc();}
    return f?-ret:ret;
}
int n,m,u[1005],v[1005];
ll l,f[21][105][105],w[1005],ans1,ans2;
inline void init(const int _n,const int _l){
	ans1=ans2=0;
	for(rg int i=1;i<=_n;++i){
		for(rg int j=1;j<=_n;++j)
			f[0][i][j]=_l;
		f[0][i][i]=0;
	}
}
inline void update(int kase,int l,int r){
	memcpy(f[kase],f[kase-1],sizeof(f[kase]));
	for(rg int k=l;k<=r;++k)
		for(rg int i=1;i<=n;++i)
			for(rg int j=1;j<=n;++j)
				f[kase][i][j]=min(f[kase][i][j],
				min(f[kase][i][u[k]]+f[kase][v[k]][j]+w[k],
				f[kase][i][v[k]]+f[kase][u[k]][j]+w[k]));
}
void solve(int kase,int l,int r){
	if(l==r){
		rg ll now=0;
		for(rg int i=1;i<=n;++i)
			for(rg int j=1;j<=n;++j)
				now+=f[kase][i][j];
		ans2=max(ans2,now);
		return;
	}
	const int mid=l+r>>1;
	update(kase+1,l,mid);
	solve(kase+1,mid+1,r);
	update(kase+1,mid+1,r);
	solve(kase+1,l,mid);
}
signed main(){
//	file();
	while(1){
		n=read(),m=read(),l=read();
		init(n,l);
		for(rg int i=1;i<=m;++i)
			u[i]=read(),v[i]=read(),w[i]=read();
		update(1,1,m);
		for(rg int i=1;i<=n;++i)
			for(rg int j=1;j<=n;++j)
				ans1+=f[1][i][j];
		solve(0,1,m);
		printf("%lld %lld\n",ans1,ans2);
	}
	return 0;
}
//To the ocean it goes,reaching you through the rivers.
//Flowerworks  -mili                                
```

☆KIRA！

---

## 作者：览遍千秋 (赞：2)

这是一道假黑题

我们有一种很直观的做法

先跑一遍floyd，再枚举断掉的边，每条边再跑一遍floyd

AC大吉

```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 103
#define maxm 2003
int n,m,l,Head[maxn],Next[maxm],v[maxm],u[maxm];
long long w[maxm],tot;
long long dis[maxn][maxn];
long long c,p,ans;
long long int x,y,z;
template<typename Tp>
void read(Tp &x){
    x=0;char ch=0;int fh;
    while(ch!='-'&&(ch<'0'||ch>'9')) ch=getchar();
    if(ch=='-'){
        ch=getchar();fh=-1;
    }
    else fh=1;
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }
    x*=fh;
}
void floyd(){
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
}
int mian(){
//	freopen("UVA1416.in","r",stdin);
//	freopen("UVA1416.out","w",stdout);
    while(~scanf("%d%d%d",&n,&m,&l)){
        memset(dis,0x3f3f3f3f,sizeof(dis));c=0;tot=ans=0;memset(Next,0,sizeof(Next));memset(Head,0,sizeof(Head));
//		memset
        for(int i=1;i<=m;i++){
            read(x);read(y);read(z);
            u[++tot]=x,v[tot]=y,Next[tot]=Head[x],Head[x]=tot,w[tot]=z;
            u[++tot]=y,v[tot]=x,Next[tot]=Head[y],Head[y]=tot,w[tot]=z;
            dis[x][y]=dis[y][x]=min(dis[x][y],z);
        }
        for(int i=1;i<=n;i++)dis[i][i]=0;
        floyd();
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++){
                if(dis[i][j]==0x3f3f3f3f3f3f3f3fLL) c+=l;
                else c+=dis[i][j];
            }
        for(int i=1;i<=tot;i+=2){
            p=0;
//			long long r=dis[u[i]][v[i]];
            memset(dis,0x3f,sizeof(dis));
            for(register int j=1;j<=tot;j+=2){
                if(j==i) continue;
                dis[u[j]][v[j]]=dis[v[j]][u[j]]=min(dis[u[j]][v[j]],w[j]);
            }
            for(int i=1;i<=n;i++)dis[i][i]=0;
//			dis[u[i]][v[i]]=dis[v[i]][u[i]]=0x3f3f3f3f3f3f3f3fLL;
            floyd();
            for(int ii=1;ii<=n;ii++)
                for(int j=1;j<=n;j++){
                    if(dis[ii][j]!=0x3f3f3f3f3f3f3f3fLL) p+=dis[ii][j];
                    else p+=l;
                }
            ans=max(ans,p);

        }
        printf("%lld %lld\n",c,ans);
    }
    return 0;
}
```

---

## 作者：π酱 (赞：2)

- 题目大意
 1. 先求任意两点间的最短路径累加和，其中不连通的边权为L
 1. 删除任意一条边,求全局最短路径和的最大值。
 1. N<=100,M<=1000

- 思路

 1. 如果直接暴力，肯定会超时
 2. 有些边不在最短路上，删除之后对答案没有影响
 3. 所以，我们只要求出最短路树，穷举它的边，对删除每一条后的答案进行统计，其余的边的答案就是求出的最短路树的边权之和

- 代码
 ```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,m,l,head[105],p;
struct edge {
    int to,next;
    ll w;
} e[2005];
void addedge(int u,int v,ll w) {
    e[p].to=v;
    e[p].w=w;
    e[p].next=head[u];
    head[u]=p++;
    e[p].to=u;
    e[p].w=w;
    e[p].next=head[v];
    head[v]=p++;
}
ll disf[105],ontree[2005][105],dis[105],inq[105],pre[105];
ll spfa(int s,int del) {
    queue<int> q;
    memset(inq,0,sizeof(inq));
    memset(dis,127,sizeof(dis));
    q.push(s);
    dis[s]=0;
    inq[s]=1;
    memset(pre,-1,sizeof(pre));
    while(!q.empty()) {
        int u=q.front();
        q.pop();
        inq[u]=0;
        for(int i=head[u]; i!=-1; i=e[i].next) {
            int v=e[i].to;
            ll w=e[i].w;
            if((i==del)||((i^1)==del))continue;
            if(dis[v]>dis[u]+w) {
                dis[v]=dis[u]+w;
                pre[v]=i;
                if(!inq[v])q.push(v),inq[v]=1;
            }
        }
    }
    ll ans=0;
    for(int i=1; i<=n; i++)
        if(dis[i]<1e17)ans+=dis[i];
        else ans+=l*1LL;
    for(int i=1; i<=n; i++)
        if(pre[i]!=-1&&del==-1)ontree[pre[i]][s]=ontree[pre[i]^1][s]=1;
    return ans;
}
int main() {
    while(~scanf("%d%d%d",&n,&m,&l)) {
        ll ans1=0,ans2=0;
        memset(head,-1,sizeof(head));
        p=0;
        for(int i=1; i<=m; i++) {
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            addedge(u,v,w);
        }
        for(int i=1; i<=n; i++) {
            disf[i]=spfa(i,-1);
            ans1+=disf[i];
        }
        for(int j=0; j<p; j+=2) {
            ll tmp=0;
            for(int i=1; i<=n; i++)if(ontree[j][i])tmp+=spfa(i,j);
                else tmp+=disf[i];
            ans2=max(ans2,tmp);
        }
        cout<<ans1<<" "<<ans2<<endl;
    }
    return 0;
}
```

---

## 作者：Rmtsaikoda (赞：1)

首先——无前置知识。\
其次，只需要会求最短路和简单深搜即可。

本题中显然我们需要找到**一条删去后使所有点彼此的距离和最大的边**。\
那么我们可以猜想存在一个属性数值来决定某一条边符合此条件，然后我们开始分析一条边拥有的属性。

1. 一条边自带的费用。
2. 一条边在未删边的图中求完最短路后，每个点对这条边的使用次数。

看到这两条属性后我们可以发现：\
**一条删去后使所有点彼此的距离和最大的边**很可能是一条**费用小**（即使用成本小）的边，因为存在这条边可以使一条路径的成本变小。

不过一条边虽然费用小但使用次数并不多，那么或许删去它后所产生的最大化贡献还比不上“费用较大但**使用次数高**的边”。

OK，现在我们可以想到，当一条边**费用较低且使用次数较多**，那么删去它后所产生的最大化贡献很有可能是最大的。

为了使费用和使用次数结合成为一个决定边的属性值，设 $use$ 为使用次数，$wi$ 为费用，我们可以使用

$$λ= \frac{ use}{ wi}$$

由上可知 $λ$ 越大则它的最大化贡献非常有可能最大，所以我们只需要选 $λ$ 较大的几条边删除并进行比较它们间的最大化贡献便可得出答案。
#
以下是用深搜查使用次数，时间复杂度 $O(nm^2+nm\log m)$，最后检查了 $100$ 条边（本题 $50$ 条边就可过，最多可开到 $200$ 条以上）的结果：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long mx,dp[102][102],ans1,ans2,dis[102];
int n,m,l,tot,head[102],ed[101][101],sta[102],bh,ta[102][102][102],c[102][102],zx,top;
double xy[1001],cc[1001];
bool stb[102],vis[102];
struct node{
	int v,nt,w;
}a[3001],bi[1001];
void add(int u,int v,int w){
	a[++tot].v=v,a[tot].w=w,a[tot].nt=head[u],head[u]=tot;
}
void dps(int u,int li){
	stb[u]=1,sta[++top]=u;//点入栈 
	for(int p1=head[u];p1;p1=a[p1].nt)
		if(!stb[a[p1].v])
			if(li+a[p1].w<=dp[zx][a[p1].v]){
				for(int i=1;i<=top;i++)ta[zx][a[p1].v][i]=sta[i]; // 让当前最短路径上的点被记录 
				ta[zx][a[p1].v][top+1]=a[p1].v,dp[zx][a[p1].v]=li+a[p1].w,ta[zx][a[p1].v][0]=top+1;
				dps(a[p1].v,li+a[p1].w);
			}
	stb[u]=0,top--;//点出栈 
}
priority_queue< pair<int,int> >qu;
void bps(int u){//dijkstra 
	for(int i=1;i<=n;i++)dis[i]=1e9;
	for(int i=1;i<=n;i++)vis[i]=0;
	dis[u]=0;
	qu.push(make_pair(0,u));
	while(qu.size()){
		int x=qu.top().second;qu.pop();
		if(vis[x])continue;
		vis[x]=1;
		for(int p1=head[x];p1;p1=a[p1].nt)
			if(ed[x][a[p1].v]!=p1)
				if(dis[a[p1].v]>dis[x]+a[p1].w){
					dis[a[p1].v]=dis[x]+a[p1].w;
					qu.push(make_pair(-dis[a[p1].v],a[p1].v));
				}
	}
}
bool cmp(int x,int y){return xy[x]>xy[y];}
int main(){
	cin.tie(nullptr)->sync_with_stdio();
	while(cin>>n>>m>>l){
		ans1=ans2=mx=tot=0;
		for(int i=1;i<=2*m;i++)a[i]=(node){0,0,0};
		for(int i=1;i<=n;i++)head[i]=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				dp[i][j]=1e9,c[i][j]=0;
		for(int i=1,x,y,s;i<=m;i++){
			cin>>x>>y>>s;
			add(x,y,s),add(y,x,s);
			bi[i].v=x,bi[i].nt=y,bi[i].w=s,dp[x][y]=dp[y][x]=s;
		}
		for(int i=1;i<=n;i++){
			zx=i,dps(i,0),dp[i][i]=0;
			for(int j=1;j<=n;j++)
				if(dp[i][j]==1e9)ans1+=l;
				else ans1+=dp[i][j];
		}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				for(int k=2;k<=ta[i][j][0];k++)
					c[ta[i][j][k-1]][ta[i][j][k]]++,c[ta[i][j][k]][ta[i][j][k-1]]++;//计量边的使用次数
		for(int i=1;i<=m;cc[i]=i,i++)xy[i]=((double)c[bi[i].v][bi[i].nt]/bi[i].w);//计算当前边的（使用次数/费用） 
		sort(cc+1,cc+m+1,cmp);//使边的（使用次数/费用）降序 
		for(int i=1;i<=min(m,100);i++){//选（使用次数/费用）最大的N条边删并计算此时最短路和的最大值
			bh=cc[i],ans2=0;
			ed[bi[bh].v][bi[bh].nt]=(bh<<1)-1,ed[bi[bh].nt][bi[bh].v]=(bh<<1);
			for(int j=1;j<=n;j++){
				bps(j);
				for(int o=1;o<=n;o++)
					if(dis[o]==1e9)ans2+=l;
					else ans2+=dis[o];
			}
			if(mx<ans2)mx=ans2;
			ed[bi[bh].v][bi[bh].nt]=ed[bi[bh].nt][bi[bh].v]=0;
		}
		cout<<ans1<<" "<<mx<<endl;
	}
	return 0;
}
```
#
这时可以问一个问题：为什么不直接选 $λ$ 最大的边删去，而是要选前几十条边？

因为 $λ$ 虽然越大越好，但当某两条边**费用和使用次数非常接近**时，$λ$ 的大小是无法精确表达出这两条边中哪条边删去后最大化贡献最大的。

再有，显然上面这份代码最大的时间复杂度提升在深搜这一环——所以，当数据非常非常**刁钻且连边复杂**时，这份代码很可能撑不住。

于是，经过 @hehai 最短路构造最短路树疯狂地优化后，得到以下这份更快的代码，理论复杂度 $O(n^2m\log n)$：
```cpp
#pragma GCC optimize(2,"inline")
#include<queue>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
using ll =long long;
const ll inf = 0x3f3f3f3f3f3f3f3f;

priority_queue<pair<ll,int>> q;
int n,m,l,cnt=1,num,vis[101],rv[101],siz[101],pre[101],edge[2001],fa[103],tim[2001],head[101],ch[2001],nex[2001];
ll dis[101],line[2001],ans2,ans_,ans1;
bool tmp(int a,int b){return tim[a]*line[b]>tim[b]*line[a];}
void add(int a,int b,ll c){
	edge[++cnt]=b;
	line[cnt]=c;
	nex[cnt]=head[a];
	head[a]=ch[cnt]=cnt;
}
void dij(int s,int sign){
	memset(dis,0x3f,sizeof dis);
	memset(vis,0,sizeof vis);
	num=0;
	q.push({0,s});dis[s]=0;
	while(q.size()){
		s=q.top().second;q.pop();
		if(vis[s]) continue;
		vis[s]=++num,rv[num]=s,siz[s]=1;
		for(int i=head[s];i;i=nex[i])
			if(i!=sign&&i!=(sign^1))
				if((!vis[edge[i]])&&dis[edge[i]]>dis[s]+line[i]){
					dis[edge[i]]=dis[s]+line[i];
					fa[edge[i]]=s,pre[edge[i]]=i;
					q.push({-dis[edge[i]],edge[i]});
				}
	}
	if(sign) return ;
	for(int i=num;i;i--)
		tim[pre[rv[i]]]+=siz[rv[i]],tim[pre[rv[i]]^1]+=siz[rv[i]],siz[fa[rv[i]]]+=siz[rv[i]];
	memset(siz,0,sizeof siz);
	memset(pre,0,sizeof pre);
	memset(fa,0,sizeof fa);
	memset(rv,0,sizeof rv);
}
void slove(){
	ans1=ans2=ans_=0,cnt=1;
	for(int a,b,c,i=1;i<=m;add(a,b,c),add(b,a,c),i++)
		cin>>a>>b>>c;
	for(int i=1;i<=n;i++){
		dij(i,0);
		for(int j=1;j<=n;j++)
			if(dis[j]==inf)
				ans1+=l;
			else ans1+=dis[j];
	}
	sort(ch+2,ch+cnt+1,tmp);
	for(int i=2,g=1;g<=min(50,min(n,m));g++,i+=2){
		for(int j=1;j<=n;j++){
			dij(j,ch[i]);
			for(int k=1;k<=n;k++)
				if(dis[k]==inf)
					ans_+=l;
				else ans_+=dis[k];
		}
		ans2=max(ans2,ans_),ans_=0;
	}
	cout<<ans1<<' '<<ans2<<endl;
	cnt=1;
	memset(tim,0,sizeof tim);
	memset(nex,0,sizeof nex);
	memset(head,0,sizeof head);
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	while(cin>>n>>m>>l)
		slove();
	return 0;
}
```
![](https://cdn.luogu.com.cn/upload/image_hosting/qxdzbgpc.png)

这是在随机数据下的测评结果，可知优化后时间差异极大。洛谷提交后（只搜前 $40$ 条边）[第一份代码](https://www.luogu.com.cn/record/185543201) $380ms$ ，（只搜前 $40$ 条边）[第二份代码](https://www.luogu.com.cn/record/185541813) $200ms$ （另外， @Musity 的 [floyd 分治](https://www.luogu.com.cn/record/184064016)最快为 $310ms$）。

最后谈一下本题的hack数据构造，因为我们考虑的是

$$λ= \frac{ use}{ wi}$$

来判断删边，所以构造数据的难点来自对**变化连边情况**和**边权大小**后每条边 $λ$ 值的变化计量难度，包括此两份代码还可以上调删边数量来提高正确率。（但第一份代码可以提高连边情况的复杂程度来卡掉（不过还没试过，只是理论上猜想应该可以卡掉））

致谢[@hehai](https://www.luogu.com/user/849104)
、[@Musity](https://www.luogu.com/user/1042296)

——爱来自团队[bhis-students-destination](https://www.luogu.com.cn/team/69141#main)

---

## 作者：STARSczy (赞：1)

$2024.10.17$，最优解，题解以纪念。

第一问直接 floyd。

第二问考虑分治 floyd。类似线段树分治，定义函数 $f(l,r)$ 生成在所有边中去掉编号在 $l \sim r$ 的边所构成的邻接矩阵。每次从 $f(l,r)$ 复制一个新矩阵再加上新边，分别调用 $f(l,mid)$ 和 $f(mid+1,r)$。当加入一条边时，枚举 $u,v$，对于其原边于经过新边的路径取最小值，即设当前新边为 $u_i$ 到 $v_i$，边权为 $w_i$，有 $e_{i,j}=\min(e_{i,j},e_{i,u_i}+w_i+e_{v_i,i},e_{i,v_i}+w_i+e_{u_i,i})$。这样，因为 $f$ 函数总共会调用 $\log$ 级别层，所以每条边共会被加 $\Theta(\log m)$ 级别次，每次加边复杂度为 $n^2$，总时间复杂度为 $\Theta(n^2 m \log m)$。

注意：
- 无论何时，两个点之间若没有边一定要赋为一个很大的数，而不是赋值为 $L$。统计答案时特判即可为这个大数即可。
- 可能会有重边。
- UVA 多测，一定要用 while 来输入。记得清空。

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/rope>
#define rep(i,l,r) for(int i=(l),i##end=(r);i<=i##end;++i)
#define per(i,r,l) for(int i=(r),i##end=(l);i>=i##end;--i)
#define int long long
#define double long double
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define rbtree(way) tree<way,null_type,less<way>,rb_tree_tag,tree_order_statistics_node_update>
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;
const int maxn=1e6+10,maxm=1e2+10,mod=998244353,inf=1e18;
inline int ksm(int x,int k,int mod=mod){
	int ans=1;
	for(;k;k>>=1,x=x*x%mod) if(k&1) ans=ans*x%mod;
	return ans;
}

int n,m,k,ans,u[maxn],v[maxn],w[maxn],f[maxm][maxm][maxm];
void dfs(int l,int r,int dep){
	if(l==r){
		int tmp=0;
		rep(i,1,n) rep(j,1,n) tmp+=f[dep][i][j]==inf?k:f[dep][i][j];
		ans=max(ans,tmp);
		return;
	}
	int mid=l+r>>1;
	rep(i,1,n) rep(j,1,n) f[dep+1][i][j]=f[dep][i][j];
	rep(k,l,mid) rep(i,1,n) rep(j,1,n) f[dep+1][i][j]=min(f[dep+1][i][j],
		min(f[dep+1][i][u[k]]+f[dep+1][v[k]][j],f[dep+1][i][v[k]]+f[dep+1][u[k]][j])+w[k]);
	dfs(mid+1,r,dep+1);
	rep(i,1,n) rep(j,1,n) f[dep+1][i][j]=f[dep][i][j];
	rep(k,mid+1,r) rep(i,1,n) rep(j,1,n) f[dep+1][i][j]=min(f[dep+1][i][j],
		min(f[dep+1][i][u[k]]+f[dep+1][v[k]][j],f[dep+1][i][v[k]]+f[dep+1][u[k]][j])+w[k]);
	dfs(l,mid,dep+1);
}

signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	while(cin>>n>>m>>k){
		rep(i,1,n) rep(j,1,n) f[0][i][j]=f[1][i][j]=i==j?0:inf;
		rep(i,1,m) cin>>u[i]>>v[i]>>w[i],f[0][u[i]][v[i]]=f[0][v[i]][u[i]]=min(f[0][u[i]][v[i]],w[i]);
		rep(k,1,n) rep(i,1,n) rep(j,1,n) f[0][i][j]=min(f[0][i][j],f[0][i][k]+f[0][k][j]);
		rep(i,1,n) rep(j,1,n) ans+=f[0][i][j]==inf?k:f[0][i][j];
		cout<<ans<<' ',ans=0,dfs(1,m,1),cout<<ans<<'\n',ans=0;
//		return 0;
	}
	return 0;
}
```

---

## 作者：andyli (赞：1)

如果用$floyd$算法计算$c$，每尝试着删除一条边都要重新计算一次，时间复杂度为$O(n^3m)$，很难承受。如果用$n$次$Dijkstra$计算单源最短路，时间复杂度为$O(nm^2\log n)$。虽然看上去比$O(n^3m)$略好，但由于$floyd$算法的常数很小，实际运行时间差不多。这时候，最短路树派上用场了。因为在源点确定的情况下，只要最短路树不被破坏，起点到所有点的距离都不会发生改变。换句话说，只有删除最短路树上的$n-1$条边，最短路树才需要重新计算。这样，对于每个源点，最短只需要求n次而不是$m$次单源最短路，时间复杂度降为$O(n^2m\log n)$，可以承受。另外，本题有一个不容易发现的“陷阱”：如果有重边，删除一条边时2，应该用第二短的边代替。  
代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int INF = 1000000000, maxn = 105;

struct Edge
{
    int u, v, w;
    Edge(int u = 0, int v = 0, int w = 0) : u(u), v(v), w(w) {}
};

struct HeapNode
{
    int d, u;
    HeapNode(int d = 0, int u = 0) : d(d), u(u) {}
    bool operator<(const HeapNode& rhs) const { return d > rhs.d; }
};

struct Dijkstra
{
    int n, m;
    vector<Edge> edges;
    vector<int> G[maxn];
    bool vis[maxn];  // 是否已永久标号
    int d[maxn];     // s到各个点的距离
    int p[maxn];     // 最短路中的上一条弧

    void init(int n)
    {
        this->n = n;
        for (int i = 0; i < n; i++)
            G[i].clear();
        edges.clear();
    }

    void AddEdge(int u, int v, int w)
    {
        edges.emplace_back(u, v, w);
        m = edges.size();
        G[u].push_back(m - 1);
    }
    void dijkstra(int s)
    {
        priority_queue<HeapNode> q;
        for (int i = 0; i < n; i++)
            d[i] = INF;
        d[s] = 0;
        memset(vis, 0, sizeof(vis));
        q.emplace(0, s);
        while (!q.empty())
        {
            HeapNode x = q.top();
            q.pop();
            int u = x.u;
            if (vis[u])
                continue;
            vis[u] = true;
            for (size_t i = 0; i < G[u].size(); i++)
            {
                Edge& e = edges[G[u][i]];
                if (e.w > 0 && d[e.v] > d[u] + e.w)
                {  // 此处和模板不同，忽略了dist=-1的边。此为删除标记。根据题意和dijkstra算法的前提，正常的边dist>0
                    d[e.v] = d[u] + e.w;
                    p[e.v] = G[u][i];
                    q.emplace(d[e.v], e.v);
                }
            }
        }
    }
};

Dijkstra solver;
int n, m, L;
vector<int> gr[maxn][maxn];  // 两点之间的原始边权
bool used[maxn][maxn][maxn];  // used[src][a][b]表示源点为src的最短路树是否包含边a->b
int idx[maxn][maxn];  // idx[u][v]为边u->v在Dijkstra求解器中的编号
int sum_single[maxn];  // sum_single[src]表示源点为src的最短路树的所有d之和

int compute_c()
{
    int ans = 0;
    memset(used, 0, sizeof(used));
    for (int u = 0; u < n; u++)
    {
        solver.dijkstra(u);
        sum_single[u] = 0;
        for (int i = 0; i < n; i++)
        {
            if (i != u)
            {
                int fa = solver.edges[solver.p[i]].u;
                used[u][fa][i] = used[u][i][fa] = true;
            }
            sum_single[u] += (solver.d[i] == INF ? L : solver.d[i]);
        }
        ans += sum_single[u];
    }
    return ans;
}

int compute_newc(int a, int b)
{
    int ans = 0;
    for (int u = 0; u < n; u++)
        if (!used[u][a][b])
            ans += sum_single[u];
        else
        {
            solver.dijkstra(u);
            for (int i = 0; i < n; i++)
                ans += (solver.d[i] == INF ? L : solver.d[i]);
        }
    return ans;
}

int main()
{
    while (~scanf("%d%d%d", &n, &m, &L))
    {
        solver.init(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                gr[i][j].clear();
        for (int i = 0; i < m; i++)
        {
            int a, b, s;
            scanf("%d%d%d", &a, &b, &s);
            a--, b--;
            gr[a][b].push_back(s), gr[b][a].push_back(s);
        }
        // 构造网络
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (!gr[i][j].empty())
                {
                    sort(gr[i][j].begin(), gr[i][j].end());
                    solver.AddEdge(i, j, gr[i][j][0]);
                    idx[i][j] = solver.m - 1;
                    solver.AddEdge(j, i, gr[i][j][0]);
                    idx[j][i] = solver.m - 1;
                }

        int c = compute_c(), c2 = -1;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (!gr[i][j].empty())
                {
                    int &e1 = solver.edges[idx[i][j]].w,
                        &e2 = solver.edges[idx[j][i]].w;
                    if (gr[i][j].size() == 1)
                        e1 = e2 = -1;
                    else
                        e1 = e2 = gr[i][j][1];  // 第二短边
                    c2 = max(c2, compute_newc(i, j));
                    e1 = e2 = gr[i][j][0];  // 恢复
                }

        printf("%d %d\n", c, c2);
    }
    return 0;
}
```

---

## 作者：Sirkey (赞：0)

- Floyd 分治板子。

[或许更好的阅读体验](https://www.cnblogs.com/sirkey2119/articles/18472143)

首先考虑 Floyd 的本质，是通过一条边去松弛两点的距离。

那么我们做分治。

分治的递归数组，为 $solve(id,l,r)$ 表示，第 $id$ 层中，没有 $l \sim r$  这段区间的边得到的全局最短路。记录的 $f(id,i,j)$ 表示第 $id$ 层中的节点 $i$ 到 $j$ 的最短路径。

我们分治往下，加入 $l\sim mid$ 区间的边，再向 $mid+1 \sim r$ 的区间中向下分治。下传到底后回溯后向另一边继续分治。

$id$ 层数每次二分往下，一共 $\log n$ 层。每次需要回溯，所以记录 $id$ 和 $f$ 数组对应。$f$ 的空间复杂度也就是 $n^2\log n$。

向下传递到只有一个 $solve$ 的区间只有一个始我们就可以记录答案了。

更改 $f$ 数组时，要把需要的边加进去，这和普通的 Floyd 是一样的。

 时间复杂度是 $O(n^3\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define debug(x) cout<<#x<<"[:]"<<x,puts("");
#define FOR(i,a,b) for(ll i=(a); i<=(b); ++i)
#define ROF(i,a,b) for(ll i=(a); i>=(b); --i)
#define pb push_back
//
//
//
using namespace std;
inline ll read() {
	ll f = 0, t = 0;
	char c = getchar();
	while (!isdigit(c)) t |= (c == '-'), c = getchar();
	while (isdigit(c)) f = (f << 3) + (f << 1) + c - 48, c = getchar();
	return t ? -f : f;
}
void write(int x) {
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
const int MX = 1005;
int f[30][MX][MX];
struct Link {
	int x, y, w;
} h[MX * MX];
int n, m, L, C;
void push_down(int id, int l, int r) {
	FOR(i,1,n) FOR(j,1,n) f[id][i][j] = f[id - 1][i][j];
	FOR(k, l, r) FOR(i, 1, n) FOR(j, 1, n)
	f[id][i][j] = min(f[id][i][j], min(f[id][i][h[k].x] + f[id][h[k].y][j] + h[k].w, f[id][i][h[k].y] + f[id][h[k].x][j] + h[k].w));
}
int ans2 = 0;
#define mid (l+r>>1)
const int inf = 1e18;
void solve(int id, int l, int r) {
	if(l == r) {
		int sum = 0;
		FOR(i,1,n) FOR(j,1,n) {
			if(f[id][i][j] == inf) sum += L;
			else sum += f[id][i][j];
		}
		ans2 = max(ans2, sum);
		return;
	}
	push_down(id + 1, l ,mid);
	solve(id + 1, mid + 1, r);
	push_down(id + 1, mid + 1, r);
	solve(id + 1, l, mid);
}
signed main() {
	while(~scanf("%lld%lld%lld",&n,&m,&L)) {
		FOR(i, 1, n) FOR(j, 1, n) f[0][i][j] = inf;
		FOR(i, 1, n) f[0][i][i] = 0;
		FOR(i,1,m) {
			int x = read(), y = read(), w = read();
			h[i] = {x, y, w};
		}
		ans2 = 0;
		push_down(1, 1, m);
		int ans = 0;
		FOR(i,1,n) FOR(j,1,n) {
			if(f[1][i][j] == inf) ans += L;
			else ans += f[1][i][j];
		}
		solve(0, 1, m);
		cout<<ans<<" "<<ans2<<'\n';
	}
	return 0;
}
```

——end——

---

