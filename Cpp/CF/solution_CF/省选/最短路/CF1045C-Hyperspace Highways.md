# Hyperspace Highways

## 题目描述

在一个未指明的太阳系中，有 $N$ 个行星。一家太空政府公司最近雇佣了太空承包商来建造 $M$ 条双向 Hyperspace™ 高速公路，每条高速公路连接两个不同的行星。主要目标是确保每个行星都可以通过 Hyperspace™ 高速公路到达其他任意行星，这一目标已经完全实现。不幸的是，许多太空承包商在公司太空董事会中有朋友和亲戚，所以公司决定不仅仅满足于连接所有行星。

为了让花费大量太空资金建造 Hyperspace™ 高速公路显得合理，他们决定对 Hyperspace™ 高速公路网络施加一条严格的规则：每当存在一条可以经过若干行星并回到起点且不重复经过任何行星的路径时，行程中的任意一对行星都必须直接通过一条 Hyperspace™ 高速公路相连。换句话说，每一个简单环上的行星集合都必须构成一个完全子图。

你正在设计一款 Hyperspace™ 导航应用，你面临的关键技术问题是：从行星 $A$ 到行星 $B$ 至少需要经过多少条 Hyperspace™ 高速公路。由于这个问题对 Bubble Cup 来说太简单了，这里有一个更难的任务：你的程序需要对 $Q$ 对行星进行上述查询。

## 说明/提示

第二个样例中的图如下：![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1045C/f8c9e6912b7629574b4563bbb808bc905c89fbb2.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5 7 2
1 2
1 3
1 4
2 3
2 4
3 4
1 5
1 4
2 5
```

### 输出

```
1
2
```

## 样例 #2

### 输入

```
8 11 4
1 2
2 3
3 4
4 5
1 3
1 6
3 5
3 7
4 7
5 7
6 8
1 5
2 4
6 7
3 8
```

### 输出

```
2
2
3
3
```

# 题解

## 作者：mrsrz (赞：4)

由于题目保证存在环则一定是一个完全子图，所以一个点双连通分量中的任意两个点的距离为$1$。

缩点双，建圆方树，可知两个距离为$1$的点，重建后必然隔了一个方点。所以直接求两点在圆方树上距离，然后除以$2$即可。

## Code：
```cpp
#include<algorithm>
#include<iostream>
#include<vector>
#include<stack>
#define N 250005
using namespace std;
int n,m,q,low[N],dfn[N],idx=0;
vector<int>G[N];
namespace tree{
	vector<int>G[N];
	int n,F[17][N],dep[N];
	inline void addedge(int u,int v){G[u].push_back(v),G[v].push_back(u);}
	void dfs(int now){
		for(int i:G[now])
		if(i!=F[0][now])F[0][i]=now,dep[i]=dep[now]+1,dfs(i);
	}
	void init(){
		for(int j=1;j<17;++j)
		for(int i=1;i<=n;++i)F[j][i]=F[j-1][F[j-1][i]];
	}
	inline int LCA(int x,int y){
		if(dep[x]<dep[y])swap(x,y);
		for(int i=16;~i;--i)if(dep[F[i][x]]>=dep[y])x=F[i][x];
		if(x==y)return x;
		for(int i=16;~i;--i)if(F[i][x]!=F[i][y])x=F[i][x],y=F[i][y];
		return F[0][x];
	}
	inline int dis(int a,int b){return dep[a]+dep[b]-(dep[LCA(a,b)]<<1)>>1;}
}
stack<int>sta;
void tar(int now){
	sta.push(now);
	dfn[now]=low[now]=++idx;
	for(int i:G[now])if(!dfn[i]){
		tar(i);
		low[now]=min(low[now],low[i]);
		if(low[i]>=dfn[now]){
			const int id=++tree::n;
			tree::addedge(now,id);
			int v;
			do{
				v=sta.top();
				sta.pop();
				tree::addedge(id,v);
			}while(v!=i);
		}
	}else low[now]=min(low[now],dfn[i]);
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>q;
	tree::n=n;
	while(m--){
		int u,v;
		cin>>u>>v;
		G[u].push_back(v),G[v].push_back(u);
	}
	for(int i=1;i<=n;++i)if(!dfn[i])tar(i),tree::dfs(i);
	tree::init();
	while(q--){
		int u,v;
		cin>>u>>v;
		cout<<tree::dis(u,v)<<'\n'; 
	}
	return 0;
}
```

---

## 作者：hdkk (赞：2)

蒟蒻不会圆方树，来一发不需要圆方树的题解。

我们建出原图的 bfs 搜索树，发现所有非树边连接的都是两个兄弟节点。

证明考虑反证：如果点 $u$ 存在一条非树边连接点 $v$，且点 $v$ 不是点 $u$ 兄弟，则这两个点在一个环上，即在一个完全子图上，那么要么 $v$ 是 $u$ 的父亲，要么 $v$ 和 $u$ 同时被搜索到，是 $u$ 兄弟，与条件不符。

非树边对最短路影响很小，我们只需略微修改倍增求 lca 的过程即可求出最短路：若倍增最后点 $u$ 和点 $v$ 在同一子图内，则存在长度为 $1$ 的路径，否则还需走到 lca。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int anc[100005][20],head[100005],num,bl[100005],n,m;
int dep[100005];
struct edge{
	int to,next;
}g[1000005];
void addd(int u,int v)
{
	num++;
	g[num].to=v;
	g[num].next=head[u];
	head[u]=num;
}
void bfs()
{
	queue<int> q;
	q.push(1);
	dep[1]=1;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int i=1;i<=19;i++)
			anc[u][i]=anc[anc[u][i-1]][i-1];
		for(int i=head[u];i;i=g[i].next)
		{
			int v=g[i].to;
			if(v==anc[u][0]) continue;
			if(!dep[v])
			{
				dep[v]=dep[u]+1;
				q.push(v);
				anc[v][0]=u;
			}
			else
				bl[v]=bl[u];
		}
	}
}
int lca(int u,int v)
{
	if(dep[u]>dep[v]) swap(u,v);
	int res=0;
	for(int i=19;i>=0;i--){
		if(dep[anc[v][i]]>=dep[u])
		{
			v=anc[v][i];
			res+=(1<<i);
		}
	}
	if(u==v) return res;
	for(int i=19;i>=0;i--)
	{
		if(anc[u][i]!=anc[v][i])
		{
			res+=(1<<(i+1));
			u=anc[u][i];
			v=anc[v][i];
		}
	}
	if(bl[u]==bl[v])
		return res+1;
	return res+2;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int k;
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++) bl[i]=i; 
	int u,v;
	for(int i=1;i<=m;i++)
	{
		cin>>u>>v;
		addd(u,v);
		addd(v,u);
	}
	bfs();
	for(int i=1;i<=k;i++){
		cin>>u>>v;
		cout<<lca(u,v)<<endl;
	}
}
```

---

## 作者：Magus (赞：1)

一眼题，不难发现可以用圆方树解决。

因为环一定是完全子图，所以点双中任意两点的距离一定为 $1$。

将每个点双缩成一个点，建圆方树，那么点双中任意两点的距离在圆方树上就变成了 $2$，所以最后的答案即为两点在圆方树上距离除以 $2$，用 LCA 求距离即可。

这个有 `cin` 的代码交上去会 T，请使用 `scanf` 或超级快读。

```cpp
#include<bits/stdc++.h>
#define I using
#define AK namespace
#define CSPS2025 std
I AK CSPS2025;
const int maxn=1e6+10,maxm=1e3+10,maxqwq=1e1+11,mod=998244353;
int t,n,m,u,v,x,y,z,tot,cnt,tag,num,ans,arr[maxn],dfn[maxn],low[maxn],vis[maxn],dep[maxn],color[maxn],fa[maxn][maxqwq];
stack<int>s;
vector<int>g[maxn],cst[maxn];
void tarjan(int u)
{
	dfn[u]=low[u]=++cnt;
	s.push(u);
	for(auto v:g[u])
	{
		if(!dfn[v])
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
			if(low[v]==dfn[u])
			{
				num++;
				cst[num].push_back(u);
				cst[u].push_back(num);
				while(s.top()!=v)
				{
					cst[num].push_back(s.top());
					cst[s.top()].push_back(num);
					s.pop();
				}
				cst[num].push_back(v);
				cst[v].push_back(num);
				s.pop();
			}
		}
		else
		{
			low[u]=min(low[u],dfn[v]);
		}
	}
	return;
} 
void dfs(int u,int f)
{
	dep[u]=dep[f]+1,fa[u][0]=f;
	for(int i=1;(1<<i)<=dep[u];i++)
	{
		fa[u][i]=fa[fa[u][i-1]][i-1];
	}
	for(auto v:cst[u])
	{
		if(v==f)
		{
			continue;
		}
		dfs(v,u);
	}
}
int lca(int x,int y)
{
	if(dep[x]<dep[y])
	{
		swap(x,y);
	}
	int d=dep[x]-dep[y];
	for(int i=19;i>=0;i--)
	{
	 	if(d&(1<<i))
		{
			x=fa[x][i];
		}
	}
	if(x==y)
	{
		return x;
	}
	for(int i=19;i>=0;i--)
	{
		if(fa[x][i]!=fa[y][i])
		{
			x=fa[x][i],y=fa[y][i];
		}
	}
	return fa[x][0];
}
int dis(int u,int v)
{
	return (dep[u]+dep[v]-(dep[lca(u,v)]<<1))>>1;
}
signed main()
{
	cin>>n>>m>>t;
	for(int i=1;i<=m;i++)
	{
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	num=n;
	tarjan(1);
	dfs(1,0);
	while(t--)
	{
		cin>>u>>v;
		cout<<dis(u,v)<<"\n";
	}
	return 0;
}
```

---

## 作者：_JF_ (赞：1)

[CF1045C Hyperspace Highways](https://www.luogu.com.cn/problem/CF1045C)

观察到，在本题的限制下，一个环里面任意两点的距离为 $1$，也就是说，我们经过这个环的代价为 $1$。

思考到发现一个环我们是可以简化的。

然后我们考虑园方树，把这个图拍到树上面去，我们把方点连出去的边权也定义为 $1$，这样我们就表示了经过环的情况，（最后算答案的时候需要除以 $2$）。

然后题目就变成询问树上任意两点之间的距离，直接求最近公共祖先即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
int dfn[N],dep[N],low[N],tot,n,m,t,cnt,fa[N][20];
vector<int> G[N],g[N];
stack<int> sta;
void Tarjan(int u){
	dfn[u]=low[u]=++tot,sta.push(u);
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i],now;
		if(!dfn[v]){
			Tarjan(v),low[u]=min(low[u],low[v]);
			if(low[v]>=dfn[u]){
				cnt++;
				do{
					now=sta.top();G[cnt].push_back(now),G[now].push_back(cnt);sta.pop();
				}while(now!=v);
				G[u].push_back(cnt),G[cnt].push_back(u);
			}
		}
		else	low[u]=min(low[u],dfn[v]);
	}
}
void dfs(int u,int fath){
	dep[u]=dep[fath]+1,fa[u][0]=fath;
	for(int i=1;(1<<i)<=dep[u];i++)	fa[u][i]=fa[fa[u][i-1]][i-1];
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(v==fath)	continue;
		dfs(v,u);
	}
}
int LCA(int x,int y){
	if(dep[x]<dep[y])	swap(x,y);
	int d=dep[x]-dep[y];
	for(int i=19;i>=0;i--)	if(d&(1<<i))	x=fa[x][i];
	if(x==y)	return x;
	for(int i=19;i>=0;i--)	if(fa[x][i]!=fa[y][i])	x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
int main(){
	scanf("%d%d%d",&n,&m,&t);
	for(int i=1,u,v;i<=m;i++)	scanf("%d%d",&u,&v),g[u].push_back(v),g[v].push_back(u);
	cnt=n,Tarjan(1),dfs(1,0);
	while(t--){
		int u,v;
		scanf("%d%d",&u,&v);
		printf("%d\n",((dep[u]+dep[v]-2*dep[LCA(u,v)])/2));
	}
	return 0;
}
```

---

## 作者：lahlah (赞：1)

[CF1045C Hyperspace Highways](https://www.luogu.com.cn/problem/CF1045C)

**题目大意**  
给一张 $n$个点 $m$条边的图,保证若有一个环，一定是完全子图,多次询两个点之间的最短路径长度。  

**题解**  
如果会**圆方树**的可以一眼看出来答案就是圆方树上距离 $/2$  
因为两个点之间一定隔了一个方点

为什么可以这么转换？  
挺显然的吧，因为如果是从完全子图一端到另一端，必然要经过一条边，然而这刚好对应圆方树上方点的两条边，一个点也是完全子图，然后就没了。

什么你不会建圆方树？？？  
要建圆方树首先要会**点双连通分量**  
**点双连通分量：** 图中任意两不同点之间都有至少两条点不重复的路径。  
还有一个好理解很多的定义：**不存在割点的图**  
两个点一条边的情况是特殊情况，这里不过多讨论点双  
然后对于原图的每一个点对应一个圆点，每个点双对应一个方点  
一个点双里的圆点全部连向那个方点  
形成一个菊花子图  
（图选自WC课件）  
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020112718363877.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM4OTQ0MTYz,size_16,color_FFFFFF,t_70)

显然每条边都会连向一个圆点和一个方点  
那么如何建圆方树呢？？？  

像tarjan一样搞就行了   
具体看代码吧  
code：
```cpp
#include<bits/stdc++.h>
#define N 1000005
using namespace std;
struct edge {
	int v, nxt;
} e[N << 1];
int p[N], eid;
void init() {
	memset(p, -1, sizeof p);
	eid = 0;
}
void insert(int u, int v) {
	e[eid].v = v;
	e[eid].nxt = p[u];
	p[u] = eid ++;
}
int n, m, low[N], dfn[N], tot, sta[N], sz, bel[N], insta[N], top, dep[N];
vector<int> g[N];
void add(int u, int v) {
	g[u].push_back(v), g[v].push_back(u);
}
void dfs(int u) {
	low[u] = dfn[u] = ++ tot;
	sta[++ top] = u; insta[u] = 1;
	for(int i = p[u]; i + 1; i = e[i].nxt) {
		int v = e[i].v;
		if(!dfn[v]) {
			dfs(v), low[u] = min(low[u], low[v]);
			if(low[v] >= dfn[u]) { //如果low[v]大于dfn[u]，说明断掉u这个点后下面的点和上面不连通，这是割点，所以下面是个点双 
					++ sz;
					add(u, sz);//注意要把 u 也和 方点连边 
					while(sta[top] != v) add(sta[top], sz), bel[sta[top]] = sz, insta[sta[top --]] = 0;
					add(sta[top], sz), bel[sta[top]] = sz, insta[sta[top --]] = 0;//把点双里一直到 v 的点全部连向方点 ，因为 u 可能属于多个点双，所以不弹出 u 
			}
		}
		else low[u] = min(low[u], dfn[v]);//像tarjan一样求low 
	}
}
int fa[N][22], q;
void dfss(int u) {
	for(int i = 0; i < g[u].size(); i ++) {
		int v = g[u][i];
		if(v == fa[u][0]) continue;
		dep[v] = dep[u] + 1;
		fa[v][0] = u;
		dfss(v); 
	}
}
int LCA(int x, int y) {
	if(dep[x] < dep[y]) swap(x, y);
	for(int i = 19; i >= 0; i --) if(dep[fa[x][i]] >= dep[y]) x = fa[x][i];
	if(x == y) return x;
	for(int i = 19; i >= 0; i --) if(fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
	return fa[x][0];	
}//求两点距离用的 
int main() {
	init();
	scanf("%d%d%d", &n, &m, &q);
	sz = n;
	for(int i = 1; i <= m; i ++) {
		int u, v;
		scanf("%d%d", &u, &v);
		insert(u, v);
		insert(v, u);
	}
	for(int i = 1; i <= n; i ++) if(!dfn[i]) dfs(i), dfss(i);
	for(int j = 1; j <= 19; j ++)
		for(int i = 1; i <= sz; i ++)
			fa[i][j] = fa[fa[i][j - 1]][j - 1];
	while(q --) {
		int x, y;
		scanf("%d%d", &x, &y);
		int lca = LCA(x, y);
		printf("%d\n", (dep[x] + dep[y] - 2 * dep[lca]) >> 1);//答案就是两点距离 / 2 
	}
	return 0;
}
```


---

## 作者：include13_fAKe (赞：1)

考虑建圆方树，容易发现原来相邻的两点之间都隔了一个方点。所以此时最短路的长度乘以了 $2$。

> 证明：~~（被打回来写的）~~
>
> 因为有环就必须是完全子图，所以环上任意两点距离均为 $1$，用方点间隔后距离变为 $2$。
>
> 任意两个不都在环上的、有边直接连接的点都是一个点双连通分量，原来的距离为 $1$，用方点间隔后变为 $2$。
>
> 图示：![](https://cdn.luogu.com.cn/upload/image_hosting/yzlfr1h6.png)（处理前）
>
> ![](https://cdn.luogu.com.cn/upload/image_hosting/c6tpg2t1.png)（处理后）

然后倍增求 LCA 的深度即可。

建议使用手写快读、scanf 和 printf 或关闭同步流，否则会被卡。我用的是第三种。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N=5*114514;
int n,m,q;
vector<int> g[N],h[N];
int dfn[N],low[N],idx;
int stk[N],idx2;
int dcc_id;
vector<int> dcc[N];
void dfs(int u){
//	cout<<u<<endl;
	dfn[u]=low[u]=++idx;
	stk[++idx2]=u;
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(!dfn[v]){
			dfs(v);
			low[u]=min(low[v],low[u]);
			if(low[v]>=dfn[u]){
				int now=stk[idx2];
				dcc_id++;
				do{
					dcc[dcc_id].push_back(now),idx2--,now=stk[idx2];
				}while(stk[idx2+1]!=v);
				dcc[dcc_id].push_back(u);
			}
		}
		else	low[u]=min(dfn[v],low[u]);
	}
}
int dep[N];
int fa[N][22];
void hdfs(int u){
	for(int i=0;i<h[u].size();i++){
		int v=h[u][i];
		if(fa[u][0]==v)	continue;
		fa[v][0]=u;
		for(int j=1;j<=20;j++){
			fa[v][j]=fa[fa[v][j-1]][j-1];
		}
		dep[v]=dep[u]+1;
		hdfs(v);
	}
}
int LCA(int u,int v){
	if(dep[u]<dep[v])	swap(u,v);
	for(int i=20;i>=0;i--){
		if(dep[fa[u][i]]>=dep[v])	u=fa[u][i];
	}
	if(u==v)	return u;
	for(int i=20;i>=0;i--){
		if(fa[u][i]!=fa[v][i])	u=fa[u][i],v=fa[v][i];
	}
	return fa[u][0];
}
signed main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin>>n>>m>>q,dcc_id=n;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		g[u].push_back(v),g[v].push_back(u);
	}
	dfs(1);
//	cout<<dcc_id-n<<endl;
//	for(int i=n+1;i<=dcc_id;i++){
//		cout<<dcc[i].size()<<' ';
//		for(int j=0;j<dcc[i].size();j++){
//			cout<<dcc[i][j]<<' ';
//		}
//		cout<<endl;
//	}
	for(int i=n+1;i<=dcc_id;i++){
		for(int j=0;j<dcc[i].size();j++){
			int u=i,v=dcc[i][j];
			h[u].push_back(v),h[v].push_back(u);
		}
	}
	hdfs(1);
	while(q--){
		int u,v;
		cin>>u>>v;
		int w=LCA(u,v);
		cout<<(dep[u]+dep[v]-2*dep[w])/2<<endl;
	}
	cout<<endl;
	return 0;
}
```

---

## 作者：Priestess_SLG (赞：0)

#### 007. Hyperspace Highways

简单的。图为 semi-仙人掌，即把仙人掌中的环变为了连通子图。但是做法仍然是相似的。还是建立圆方树，这里把一个连通子图建立一个方点作为辅助，然后该子图中所有的点向这个方点连一条边权为 $1$ 的边，两个圆点之间连边权为 $2$ 的边。

此时得到了一个带权树，对于每一组询问 $a,b$，可以提前处理倍增数组然后直接倍增处理两点之间唯一路径的长度，将这个长度除以 $2$ 即为答案。时间复杂度为 $O(n\log n)$，可以通过。

[CF 题就直接放提交记录啦！](https://codeforces.com/contest/1045/submission/311356629)

---

## 作者：Hoks (赞：0)

## 前言
比较一眼的题？但是怎么又是 $1045$ 场。

摘自 [杂题选做](https://www.luogu.com.cn/training/518105)。
## 思路分析
多次询问两点最短路径长度，感觉只有在树上才是可做的。

那么怎么把一张图变成树。

考虑大力圆方树给图重构。

因为题目条件，所以环内点两两距离都是 $1$，这样边权的问题就不用担心了。

圆方树有了后考虑怎么询问答案。

因为对于每一对原本有边的圆点，在圆方树中都恰好有一个方点把他们隔开，所以答案刚好翻倍了。

输出的时候除以 $2$ 的行了。总的就是一个圆方树板子套树剖板子。
## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10,INF=0x3f3f3f3f3f3f3f3f,mod=1e9+7;
int n,m,k,q,dt,tot,low[N],s[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
namespace tree_decomposition
{
    int fa[N],son[N],si[N],dep[N];
    int top[N],id[N],dfn[N],cnt;vector<int>e[N],g[N];
	inline void clear(int n)
	{
		memset(son,0,sizeof son);
		cnt=0;for(int i=1;i<=n;i++) e[i].clear();
	}
    inline void add(int u,int v,vector<int>e[]){e[u].emplace_back(v),e[v].emplace_back(u);}
    inline void dfs1(int u,int ff)
    {
        fa[u]=ff,si[u]=1,dep[u]=dep[ff]+1;
        for(auto v:e[u])
        {
            if(v==ff) continue;
            dfs1(v,u);si[u]+=si[v];
            if(si[son[u]]<si[v]) son[u]=v;
        }
    }
    inline void dfs2(int u,int topf)
    {
        top[u]=topf;
        dfn[u]=++cnt,id[cnt]=u;
        if(son[u]) dfs2(son[u],topf);
        for(auto v:e[u])
        {
            if(v==fa[u]||v==son[u]) continue;
            dfs2(v,v);
        }
    }
    inline int LCA(int x,int y)
    {
        while(top[x]!=top[y])
        {
            if(dep[top[x]]<dep[top[y]]) swap(x,y);
            x=fa[top[x]];
        }
        return dep[x]<dep[y]?x:y;
    }
    inline int dis(int x,int y){return dep[x]+dep[y]-(dep[LCA(x,y)]<<1);}
}
using namespace tree_decomposition;
inline void tarjan(int u)
{
    s[++dt]=u;dfn[u]=low[u]=++tot;
    for(int i:g[u])
        if(!dfn[i])
        {
            tarjan(i);low[u]=min(low[u],low[i]);
            if(low[i]>=dfn[u])
            {
                int x=++k,v;add(u,x,e);
                do v=s[dt--],add(x,v,e);while(v!=i);
            }
        }else low[u]=min(low[u],dfn[i]);
}
inline void solve()
{
    n=k=read(),m=read(),q=read();for(int i=1,u;i<=m;i++) u=read(),add(u,read(),g);
    for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i),dfs1(i,0),dfs2(i,i);
    for(int i=1,l;i<=q;i++) l=read(),print(dis(l,read())>>1),put('\n');
}
signed main()
{
    int T=1;while(T--) solve();
    genshin:;flush();return 0;
}
```

---

## 作者：gyyyyx (赞：0)

根据题目可知一个点双中的任意两点的距离恒定为 $1$。

那么我们如果到达点双中的一点可以只走 $1$ 的距离就到达点双中的另外一个节点。

考虑建圆方树。

此时我们从一个圆点走到方点再走到另一个圆点则代表我们走过了一个点双，在圆方树上花费 $2$ 的距离，在原树中花费 $1$ 的距离。

因此答案就是圆方树上两点距离的一半。

代码：

```cpp
#include<bits/stdc++.h>
#define N 100005
#define M 500005
using namespace std;
int n,m,q;
struct Edge{
	int nxt,to;
	Edge(int a=0,int b=0):nxt(a),to(b){}
};
struct Edge e[M<<1];
int head[N],cnt;
inline void AddEdge(int x,int y){
	e[++cnt]=Edge(head[x],y);head[x]=cnt;
}
int tot,idx,dfn[N],low[N];
stack <int> st;
int fa[N<<1][20],dep[N<<1];
vector <int> T[N<<1];
void Tarjan(int u){
	dfn[u]=low[u]=++idx;st.push(u);
	for(int i(head[u]);i;i=e[i].nxt){
		int v(e[i].to);
		if(!dfn[v]){
			Tarjan(v);
			low[u]=min(low[u],low[v]);
			if(low[v]==dfn[u]){
				++tot;
				while(1){
					int x(st.top());st.pop();
					T[tot].push_back(x);fa[x][0]=tot;
					if(x==v) break;
				}
				T[u].push_back(tot);fa[tot][0]=u;
			}
		}
		else low[u]=min(low[u],dfn[v]);
	}
}
void DFS(int u){
	for(int i(1);i<=18;++i) fa[u][i]=fa[fa[u][i-1]][i-1];
	for(int i(0);i<T[u].size();++i)
	{int v(T[u][i]);dep[v]=dep[u]+1;DFS(v);}
}
inline int LCA(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i(18);~i;--i)
		if(dep[fa[x][i]]>=dep[y])
			x=fa[x][i];
	if(x==y) return x;
	for(int i(18);~i;--i)
		if(fa[x][i]^fa[y][i])
			x=fa[x][i],
			y=fa[y][i];
	return fa[x][0];
} 
int main(){
	scanf("%d%d%d",&n,&m,&q);
	for(int i(1);i<=m;++i){
		int u,v;scanf("%d%d",&u,&v);
		AddEdge(u,v);AddEdge(v,u);
	}
	tot=n;Tarjan(1);DFS(1);
	while(q--){
		int u,v;scanf("%d%d",&u,&v);
		printf("%d\n",dep[u]+dep[v]-(dep[LCA(u,v)]<<1)>>1);
	}
	return 0;
}
```

---

