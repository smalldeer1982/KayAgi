# Mr. Kitayuta's Technology

## 题目描述

Shuseki Kingdom在创新和技术方面是世界领先的国家。在Shuseki Kingdom中有编号1到n的n个城市。
Kitayuta先生的研究使Shuseki Kingdom会在两个城市之间建造传送管道。连接两个城市的传送管道是单向的，即从城市x到城市y的传送管道不能用来从城市y前往城市x。由于每个城市内的交通极为发达，因此如果从城市x到城市y的传送管道和从城市y到城市z的传送管道都已建造好，人们就可以直接从城市x前往城市z。
Kitayuta先生同时也是一个政客。他认为有m对“重要城市对”(ai,bi) ( 1<=i<=m )之间的交通很重要。他计划建造传送管道时，要使得对于每对“重要城市对”(ai,bi)，都可以通过使用一个或多个传送管道，从城市ai前往城市bi。请你计算出，最少需要建造几条传送管道，才能满足Kitayuta先生的需求。到目前为止，还没有建造任何传送管道，城市之间也没有任何其他有效的交通工具。

## 说明/提示

对于第一个样例，构建管道的最佳方法之一如下图所示：
![](https://cdn.luogu.org/upload/vjudge_pic/CF505D/41d1e53a1057dea3b2f50b9af3dc7c7c17995877.png)
对于第二个样例，构建管道的最佳方法之一如下图所示：
![](https://cdn.luogu.org/upload/vjudge_pic/CF505D/3fd4624f001628b234de5055b8104860cf1c833c.png)

## 样例 #1

### 输入

```
4 5
1 2
1 3
1 4
2 3
2 4
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4 6
1 2
1 4
2 3
2 4
3 2
3 4
```

### 输出

```
4
```

# 题解

## 作者：Cheng_yf (赞：9)

对于一个没有环的联通块,可以用拓扑序排成一个链 用tot-1条边.因为,联通tot个点至少需要tot-1条边,所以这是最优的

对于一个有环的连通块,可以排成一个环,用tot条边.因为,对于这个连通块中的环,已经不能用个数-1条边满足条件,所以个数条边是最优的

对于判环,可以采用并查集和topsort

```cpp
#include<bits/stdc++.h>
#define maxn 100005
#define maxm 100005
using namespace std;
struct edge{int to,nxt;}e[maxm];
int head[maxn],cnte,n,m;
void adde(int u,int v){e[++cnte]=(edge){v,head[u]};head[u]=cnte;}
int fa[maxn];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void merge(int x,int y){if((x=find(x))^(y=find(y))) fa[x]=y;}
queue<int>q;
int vis[maxn],in[maxn];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) fa[i]=i;
	while(m--){
		int u,v;scanf("%d%d",&u,&v);
		adde(u,v);merge(u,v);in[v]++;
	}int ans=n;
	for(int i=1;i<=n;i++) fa[i]=find(i),ans-=vis[fa[i]]==0,vis[fa[i]]=1;
	for(int i=1;i<=n;i++) if(!in[i]) q.push(i);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;in[v]--;
			if(!in[v]) q.push(v);
		}
	}
	for(int i=1;i<=n;i++) if(in[i]) ans+=vis[fa[i]],vis[fa[i]]=0;
	return printf("%d\n",ans),0;
}

```


---

## 作者：a___ (赞：6)

先按照题意建有向图。  

显然，不同联通块之间不需要连边。  

考虑同一联通块内，发现有两种情况。  

1. 原图是一个 DAG   
	显然我们可以按拓扑序连成一条链，这样每个点前面的点一定在它前面。需要 $n-1$ 条边。显然不存在更优解（没有环，$n-1$）。  
    
2. 原图包含强联通分量   
	我们可以把所有点按任意顺序连成一个环，这样可以保证任意两点两两可达。需要 $n$ 条边。显然不存在更优解（考虑至少需要有环，那么一定有大于 $n-1$ 条边）。   

所以我们的答案是 总点数-DAG数=总点数-联通快数+含环图数。   

首先总点数题目给出了，是 $n$ 个。   

然后我们可以建双向边 dfs 染色求出连通块数。   

然后我们在有向图上 dfs 判该连通块是否含环，具体地，通过标记，判断是否在到达该点的路径上经过该点来实现。每到一个点将其标记置为 1，离开时置为 0。  

代码（不到 20 行，不到 600B，适合图论初学者练习）：    
```cpp
#include<bits/stdc++.h>
const int N=1e5+10;
int n,m,col[N],cnt;
bool flg[N],vis[N],isk[N];
std::vector<int>g[N],g1[N];
void dfs1(int u){col[u]=cnt;for(auto v:g1[u])if(!col[v])dfs1(v);}
void dfs(int u){vis[u]=isk[u]=1;for(auto v:g[u])if(!vis[v])dfs(v);else flg[col[v]]|=isk[v];isk[u]=0;}
int main()
{
	int i,x,y;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++)scanf("%d%d",&x,&y),g[x].push_back(y),
	g1[x].push_back(y),g1[y].push_back(x);
	for(i=1;i<=n;i++)if(!col[i])++cnt,dfs1(i);
	for(i=1;i<=n;i++)if(!vis[i])dfs(i);
	for(i=1,y=n-cnt;i<=cnt;i++)y+=flg[i];
	printf("%d\n",y);
	return 0;
}
```

---

## 作者：Reimu_ (赞：3)

**说在前头**

蒟蒻第一次写题解，求求管理员大大过了吧谢谢！


------------


先按照题意建立有向图。

然后思路上我们要把有向图抽象成树。

因为题目要求给出最少有几条边，而树的边数是最少的。

构建出树后，简化成只有一个叶子节点（像一条链一样）。

可以看出，如果无环，为 $n-1$，像是样例一：

![](https://pic.imgdb.cn/item/64e48060661c6c8e54c1597c.png)

我们可以把它抽象成这样。

![](https://pic.imgdb.cn/item/64e4822c661c6c8e54c21f85.png)

如果有环，为 $n$，像是样例二：

![](https://pic.imgdb.cn/item/64e48060661c6c8e54c15970.png)

我们可以把它抽象成这样。

![](https://pic.imgdb.cn/item/64e4822c661c6c8e54c21f97.png)

实现就是先用拓扑跑一遍，是环输出 $n$，不是环输出 $n-1$。

```cpp
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int maxn = 1e5 + 5;
int head[maxn],rd[maxn],fa[maxn];
int n,cnt=0,m,ans;
bool vis[maxn],ins[maxn],dsu[maxn];
queue<int> q;
struct edge
{
	int to,nxt;
}e[maxn];

int find(int x)
{
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void add(int u,int v)
{
	e[++cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
	rd[v]++;
}

int main()
{
	int a,b;
	cin >> n;
	cin >> m;
	for(int i = 1; i <= n; i++)
		fa[i] = i;
	for(int i = 1; i <= m; i++)
	{
		cin >> a;
		cin >> b;
		add(a,b);
		if(!vis[a]) 
		{
			vis[a] = true;
			ans++;
		}
		if(!vis[b])
		{
			vis[b] = true;
			ans++;
		}
		int fx = find(a);
		int fy = find(b);
		if(fx != fy)
			fa[fy] = fx;
	}
	for(int i = 1; i <= n; i++)
		if(!rd[i])
		{
			q.push(i);
			ins[i] = true;
		}
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		for(int i = head[u]; i; i = e[i].nxt)
		{
			int v = e[i].to;
			if(--rd[v] == 0) q.push(v),ins[v]=true;
		}
	}
	for(int i = 1; i <= n; i++)
		if(vis[i] && !ins[i] && !dsu[find(i)])
			dsu[find(i)] = true;	
	for(int i = 1; i <= n; i++)
		if(vis[i] && find(i) == i && !dsu[i])
			ans--;
	cout << ans; 
	return 0;
}
```


---

## 作者：CaoSheng_zzz (赞：2)

### 思路
------
这道题的思路其实是根据样例图片来的。

首先第一张：

![](https://cdn.luogu.org/upload/vjudge_pic/CF505D/41d1e53a1057dea3b2f50b9af3dc7c7c17995877.png)

这张图片可以得知 $ n $ 个点没有环的时候最少需要 $ n - 1 $ 个点。

再看第二张：

![](https://cdn.luogu.org/upload/vjudge_pic/CF505D/3fd4624f001628b234de5055b8104860cf1c833c.png)

这个图确实很难思考，但稍微思考一下如果我们把**含有一个**强连通分量的图变成一整个强连通图。

![](https://cdn.luogu.com.cn/upload/image_hosting/z9eu0377.png?x-oss-process=image/resize,m_lfit,h_850,w_1125)

这个图的边数不就变成 $ n $ 了吗？

来推一下为什么这样最小：

因为强连通块需要的边数为 $ n $ 把他所在的图变成一个强连通图之后就是最小的了因为这个图中所有点都能互相到达了且只需要点的个数条边。

所以边数的数量就是含有强连通块的数量的图的点数之和，加上，没有含有强连通块的图的点数数量没有含有强连通块的图的数量。

因为每一个没有强连通分量需要点数个数 $ -1 $ 条边而含有强连通分量的图需要点数个数条边，因此我们可以得出最少需要的边数总点数的数量减去没有强连通分量图的数量。

这些问题解决了的话基本就好了，强连通块的数量就用 tarjan 求就行了。

AC 代码：

```cpp
#include <bits/stdc++.h>
#include <map>
#include <bitset>
#define ll long long
#define prt printf
#define sc(ppt) scanf("%d" , &ppt)
using namespace std;
 
const int maxn = 1e5 + 1;
map<int , map<int , int>> G; // map来去重边 
int ans1 , ans2 , n , m , bj = 0; //题目需要 
int U[maxn] , V[maxn] , Cnt = 0 , cnt = 0 , H[maxn] , h[maxn]; //链式前向星 
int vis_d[maxn] ; // dfs
int sum , deep = 0 , top = 0 , dfn[maxn] , low[maxn] , vis[maxn] , stk[maxn] , color[maxn] , num[maxn]; // tarjan
struct edge{
	int next , to;
}e[maxn],e_d[maxn];
 
void add_edge(int u , int v){
	++cnt;
	e[cnt].next = h[u];
	e[cnt].to = v;
	h[u] = cnt;
} //tarjan 
 
void add(int u , int v){
	++Cnt;
	e_d[Cnt].next = H[u];
	e_d[Cnt].to = v;
	H[u] = Cnt;
} //缩点后 
 
void tarjan(int u){
	dfn[u] = ++deep , low[u] = deep , vis[u] = 1 , stk[++top] = u;
	for(int i=h[u] ; i ; i=e[i].next){
		int v = e[i].to;
		if(!dfn[v]){
			tarjan(v);
			low[u] = min(low[u] , low[v]);
		}
		else{
			if(vis[v]) low[u] = min(low[u] , dfn[v]);
		}
	}
	if(low[u] == dfn[u]){
		++sum;
		int v;
		do{
			v=stk[top--];
			vis[v] = false;
			color[v]=sum;
			num[sum]++;
		}while(u != v);
	}
} //板子 
 
void dfs(int u){
	vis_d[u] = 1;
	if(num[u] >= 2 && bj == 0){
		++ ans1;
		bj = 1;
	} //判断是否有强联通分量 
	for(int i=H[u] ; i ; i=e_d[i].next){
		int v = e_d[i].to;
		if(vis_d[v] != 1){
			dfs(v);
		}
	}
} //判断树 
 
signed main(){
	sc(n) ; sc(m) ;
	for(int i=1 ; i<=m ; i++){
		int u , v;
		sc(u) ; sc(v) ;
		U[i] = u;
		V[i] = v;
		add_edge(u , v);
	}
	for(int i=1 ; i<=n ; i++) if(!dfn[i]) tarjan(i);
	for(int i=1 ; i<=m ; i++){
		if(G[color[U[i]]][color[V[i]]] == 1 || color[U[i]] == color[V[i]]) continue;
		add(color[U[i]] , color[V[i]]);
		add(color[V[i]] , color[U[i]]);
		G[color[U[i]]][color[V[i]]] = 1;
	} //存双边变成树
	for(int i=1 ; i<=sum ; i++) {
		if(!vis_d[i]){
			bj = 0;
			++ans2, dfs(i);
		}
	} // 看有几棵树 
	prt("%d" , n - ans2 + ans1); // 数的数量 - 含有强连通树的数量就是没有强联通树的数量
	return 0;
}
```

---

## 作者：liujiaxi123456 (赞：0)

#### 题意：
$n$ 个点，给定 $m$ 对点对 $(u_i, v_i)$，求构造一个有向图满足任意 $u_i$ 能到达 $v_i$，求最小边数。
#### 思路：
**\*有向图连通性**：
- 考虑 DAG 贡献。
- 考虑环贡献。
- 考虑 DAG 和环之间的影响。

发现环直接全连起来就行了，需要 $sz$ 条边。

DAG 可以按照拓扑序构造成一条链，需要 $sz-1$ 条边。

考虑环和 DAG 的贡献能否分开处理：
- 发现环多的一条边的作用在于**让环剩下的边的总信息可以被环上每一个点都接收到**。
- 而**环去掉一条边后就是 DAG**。
- 所以 **DAG 加上一条边就是环**。
- 所以，当同时有两个环以上时，不需要添加两条以上的边来让每一个环共用信息。
- 而是应该只添加一条边来让整个连通块共用信息。

所以，对于每一个连通块，如果连通块里面有环，需要 $sz$，否则需要 $sz-1$。
#### Code：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn = 1e5+5;

namespace EDGE {
	int sz, head[Maxn];
	struct Edge { int next, to; } edge[Maxn];
	inline void Add_edge(int u, int v) {
		edge[++sz] = {head[u], v};
		head[u] = sz;
	}
} using namespace EDGE;

namespace Josh_zmf {
	
	int N, M, bel[Maxn], deg[Maxn], fa[Maxn], size[Maxn];
	vector <int> have[Maxn]; 

	inline int find(int u) { return fa[u]==u ?u :find(fa[u]); }

	inline bool check(int x) { // 检查连通块 x 是否有环
		static queue <int> q;
		for(int u: have[x])	if(!deg[u])	q.push(u);
		if(q.empty())	return 1;
		// printf("x:%d, have.size:%d\n", x, (int)have[x].size());
		while(!q.empty()) {
			int u = q.front(); q.pop();
			for(int i=head[u], v; i; i=edge[i].next) {
				v = edge[i].to;
				if(!(--deg[v]))	q.push(v);
			}
		}
		// for(int u: have[x])	printf("deg[%d]:%d\n", u, deg[u]);
		for(int u: have[x])	if(deg[u])	return 1;
		return 0;
	}

	inline int main() {
		cin>> N>> M;
		for(int i=1; i<=N; i++)	fa[i] = i, size[i] = 1;
		for(int i=1, u, v; i<=M; i++) {
			cin>> u>> v, Add_edge(u, v), deg[v]++;
			u = find(u), v = find(v);
			if(u == v)	continue;
			if(size[u] < size[v])	swap(u, v);
			size[u] += size[v], fa[v] = u;
		}
		int cnt = 0;
		for(int i=1; i<=N; i++) {
			if(!bel[find(i)])	bel[find(i)] = ++cnt;
			have[bel[find(i)]].push_back(i);
		}
		int ans = 0;
		for(int i=1; i<=cnt; i++) {
			ans += (check(i) ?(int)have[i].size() :(int)have[i].size()-1);
		}
		cout<< ans;
		return 0;
	}

}

int main() {
	Josh_zmf::main();
	return 0;
}
```

---

## 作者：XYZ303 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF505D)
# 题目大意
一共有 $n$ 个点，给定 $m$ 条**有向边（不保证所有点连通）**，求最少需要建多少条有向边使得各个点能按照给定的有向边到达其他点。
# 解题思路
首先我们先把给出的边建成多个图，比如这个样例。

![](https://cdn.luogu.com.cn/upload/image_hosting/ewyramli.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

对于最右边这种图，它和最左边那种图最大的区别就是它有**强连通分量**，但我们不管它有几条边都可以直接把它变成一个**环**，这样所有点都可以相互到达，需要边数 $=$ 节点数。

对于最左边这种**无环图**，我们都可以把它变成**一棵树**（如下图，这里读者可以自己证一下），需要边数 $=$ 节点数 $-1$。

![](https://cdn.luogu.com.cn/upload/image_hosting/0p7yi2yr.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

但是我们还要注意，**图与图之间不需要连边**，所以答案要减去图的个数。

综上，设图的数量为 $m1$，有环图的数量为 $m2$，则 $ans=n-m1+m2$。

# AC代码
~~（崩溃，调了两天）~~
```
#include<bits/stdc++.h>

using namespace std;

struct str{
	int to,next;
}t[1000005];

int n,m; //记录总点数和边数
int m1; //记录图的数量
int m2; //记录有环图的数量
int dis; //记录图中是否有强连通分量
int d[100005],h[100005],l[100005],num[100005],vis[100005],team[100005],x,y,ans,cnt,point;

map<int,map<int,int>> mp;

stack<int> s;

void add(int a,int b){
	cnt++;
	t[cnt].to = b;
	t[cnt].next = h[a];
	h[a] = cnt;
}

//这里别学我，脑子抽了写个塔尖来判断强连通分量，读者可以直接用dfs判断是否有返祖现象，如果有则说明有强连通分量
void tj(int a){ //模版塔尖
	s.push(a);
	vis[a] = 1;
	point++;
	d[a] = l[a] = point;
	int b;
	for(int i=h[a];i;i=t[i].next){
		b = t[i].to;
		if(d[b] == 0){
			tj(b);
			l[a] = min(l[a],l[b]);
		}
		else if(vis[b] == 1){
			l[a] = min(l[a],d[b]);
		}
	}
	if(d[a] == l[a]){
		ans++;
		do{
			b = s.top();
			s.pop();
			vis[b] = 0;
			team[b] = ans;
			num[ans]++;
		}while(a != b);
	}
	if(num[ans] > 1){ //如果里面点的个数大于一，这说明为强连通分量
		dis = 1;
	}
}

int main(){
	
	ios::sync_with_stdio();
	cin.tie(0);
	cout.tie(0);
	
	cin >> n >> m;
	for(int i=1;i<=m;i++){
		cin >> x >> y;
		add(x,y); //建图
	}
	for(int i=1;i<=n;i++){
		if(d[i] == 0){ //如果没有被访问过
			m1++; //图的数量加一
			dis = 0;
			tj(i);
			if(dis == 1){ //如果有强连通分量
				m2++; //有环图的数量加一
			}
		}
	}
	cout << n - m1 + m2; //根据公式输出
	
	return 0;
}
```
管理人大人辛苦了，谢谢！

---

## 作者：Empty_Dream (赞：0)

## 题意

给你 $n$ 个城市和 $m$ 对**有向**关系 $u_i,v_i$。

求构造一个有向图使得所有 $u_i$ 能到达 $v_i$ 所需最少点数。

## 分析

首先我们要明确一个结论：

> 一个有向图如果是强连通的，那么边数必定小于等于点数。

很好理解，如果把所有点串成一个环，那肯定是强连通的。

考虑题目要求。首先强连通图肯定满足；更少一点，比如说如果这些点连上边后能变成一棵树，并且满足条件，当然这也是最小的（得保证这些点联通）。

现在问题就转化成了原图能不能变成一棵树。成为一棵树的必要条件就是不能有环，有环就相当于我是我自己的父亲，肯定不满足（带回原题中，如果有环，那么肯定需要比一棵树需要的边数多至少一个，肯定没有强连通图优）。剩下的一定满足吗？由拓扑排序（类似[这题](https://www.luogu.com.cn/problem/AT_abc223_d)）可以得到唯一的拓扑序，也就是满足答案的建边顺序。

这里对拓扑排序不做过多赘述，之后是细节：

- 这里分很多个连通块，要对每个连通块进行判断。
- 对于维护连通块大小（也就是点数），不能用 dfs（可能有一些点遍历不到）可以用并查集来维护每一个连通块。
- 对于求最后的贡献，可以直接统计有多少个连通块满足可以构成一棵树，减去它们就好了。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m;
int vis[100005], fa[100005], ind[100005], d[100005];
vector<int> g[100005];
map<int, int> mp;

int find(int x){//用并查集维护连通块
	return (x == fa[x] ? x : fa[x] = find(fa[x]));
}

void merge(int x, int y){
	fa[find(y)] = find(x);
}

void tuopu(){//拓扑
	queue<int> q;
	for(int i = 1; i <= n; i++){
		if(ind[i] == 0) q.push(i), vis[i] = 1;
	}
	while(!q.empty()){
		int u = q.front(); q.pop();
		for(int i = 0; i < g[u].size(); i++){
            int v = g[u][i];
			ind[v]--;
			if(ind[v] == 0){
				q.push(v);
				vis[v] = vis[u] + 1;
			}
		}
	}
}

int main(){
	cin >> n >> m;
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1, u, v; i <= m; i++){
		cin >> u >> v;
		g[u].push_back(v);
        ind[v]++;
		merge(u, v);
	}
    tuopu();
    for(int i = 1; i <= n; i++) {
		if(vis[i] == 0) d[find(i)] = true;//不在拓扑序里面，肯定有环
	}
	for(int i = 1; i <= n; i++){
        if(!d[find(i)]) mp[find(i)] = 1;//如果这个连通块中没有环，记录减1的次数
    }
	cout << n - mp.size();//减去能构成树的
	return 0;
}
```

---

## 作者：majoego (赞：0)

紫题。

首先我们发现先答案最多为 $n-1$。如果答案是 $n-1$ 那么图是一个树，因此可以连通。

我们可以先将 $ans = n - 1$，然后对答案做减法，我们将每对 $(u,v)$ 需要在一个集合内的用并查集维护起来。然后记录一下，知道有 $x$ 个不同的并查集，然后用 $ans$ 减去 $x-1$，也就是每一个集合之间最少的通道，他们通道减去就完事了。

我们也可以将一开始 $ans=n$，然后处理完之后 $ans$ 减去 $x$ 即可，会方便一些。

然后呢，如果对于一个连通块内有环，那么必定不是一棵树了，它的边数就不再是点数 $-1$ 了，而是点数，所以说，如果是环的情况，我们要再让 $ans$ 加一。

判环可以使用 topo。

[link](https://codeforces.com/contest/505/submission/254015440)。

---

## 作者：AlicX (赞：0)

## Solution 

一道几乎把做法刻在脸上的题。

观察样例就可以得出一个显然的也很重要的性质：对于一个无环图，用拓扑序的方式连接即可，只需要用 $x-1$ 条边，$x$ 为这个图的点数；对于一个有环图，也只需要 $x$ 条边即可。

然后用并查集找出一共有多少个连通块，假设为 $cnt1$，再用拓扑图找出其中有多少个有环图，假设为 $cnt2$，答案就是 $n-cnt1+cnt2$。

```cpp
#include<bits/stdc++.h>
//#define int long long
#define x first
#define y second 
#define il inline 
#define db double
#define low(x) x&-x 
#define pb(x) push_back(x) 
#define debug() puts("-------")  
using namespace std;
typedef pair<int,int> pii;
typedef pair<int,pii> PII; 
const int N=1e5+10,INF=1e9+7;  
int n,m; 
int d[N]; 
int p[N]; 
bool st[N]; 
bool vis[N]; 
int h[N],idx=0; 
struct Node{
	int to,ne; 
}e[N<<1]; 
struct Mind{ 
	il bool operator<(Mind &Cyan)const{ } 
}; 
il int read(){ 
	int x=0,f=1; char c=getchar();
	while(c<'0'||c>'9'){ if(c=='-') f=-1; c=getchar(); }
	while(c>='0'&&c<='9'){ x=(x<<3)+(x<<1)+c-48; c=getchar(); }
	return x*f;
} 
il void add(int u,int v){
	e[idx].to=v,e[idx].ne=h[u],h[u]=idx++; 
} 
il int find(int x){ 
	if(p[x]!=x) p[x]=find(p[x]); 
	return p[x]; 
} 
il void work(){ 
	queue<int> q; 
	for(int i=1;i<=n;i++) if(!d[i]) q.push(i); 
	while(!q.empty()){ 
		int u=q.front(); 
		st[u]=true; q.pop(); 
		for(int i=h[u];i!=-1;i=e[i].ne){ 
			int to=e[i].to; 
			if(!(--d[to])) q.push(to); 
		} 
	} 
} 
signed main(){ 
	memset(h,-1,sizeof h); 
	n=read(),m=read(); int ans=n; 
	for(int i=1;i<=n;i++) p[i]=i; 
	for(int i=1,u,v;i<=m;i++){ 
		u=read(),v=read(); 
		add(u,v),d[v]++; 
		int pa=find(u),pb=find(v);  
		if(pa!=pb) p[pa]=pb; 
	} for(int i=1;i<=n;i++) if(!vis[find(i)]) ans--,vis[find(i)]=true; 
	work(); memset(vis,false,sizeof vis); 
	for(int i=1;i<=n;i++) if(!st[i]&&!vis[find(i)]) ans++,vis[find(i)]=true; 
	printf("%d\n",ans); 
	return 0; 
} /* */ 
```


---

