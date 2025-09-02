# Matrix Problem

## 题目描述

给定一个由 $n$ 行 $m$ 列组成的矩阵 $a$，矩阵中的每个元素均为 $0$ 或 $1$。

你可以进行如下操作任意次（也可以不进行）：选择矩阵中的一个元素，将其替换为 $0$ 或 $1$。

同时给定两个数组 $A$ 和 $B$，长度分别为 $n$ 和 $m$。在所有操作结束后，矩阵需要满足以下条件：

1. 对于每个 $i \in [1, n]$，第 $i$ 行中 $1$ 的个数恰好为 $A_i$。
2. 对于每个 $j \in [1, m]$，第 $j$ 列中 $1$ 的个数恰好为 $B_j$。

请计算你最少需要进行多少次操作。如果无法满足条件，输出 $-1$。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 3
0 0 0
0 0 0
0 0 0
1 1 1
1 1 1```

### 输出

```
3```

## 样例 #2

### 输入

```
3 3
1 1 1
1 1 1
1 1 1
3 2 1
1 2 3```

### 输出

```
3```

## 样例 #3

### 输入

```
2 2
0 0
0 0
1 2
0 1```

### 输出

```
-1```

# 题解

## 作者：蒟蒻君HJT (赞：5)

先尝试判断无解：$\displaystyle\sum A_i\neq \sum B_j$ 是必然无解的。但是这不充分。

仅仅判断是否有解不依赖给定的矩阵 $a_{i,j}$，如果我们从全 $0$ 矩阵出发的话，会发现把 $0$ 翻转成 $1$ 的操作类似于二分图多重匹配：左部点 $n$ 个表示行，右部点 $m$ 个表示列，左右任意两点间存在一条待匹配边。$(i_{left},j_{right})$ 选入匹配，表示令 $a_{i,j}\leftarrow 1$。每个点的匹配次数的限制是恰好 $A_i$ 或 $B_j$ 次。问题转化成了匹配的可行性判断。

好，现在我们会判是否有解了，但是怎么求出最少的翻转次数呢？不妨先把所有 $1$ 都翻转为 $0$，令基础答案 $pans$ 为原本 $1$ 的个数。之后每条待匹配边都带权，$a_{i,j}$ 为 $0$ 的话 $(i_{left},j_{right})$ 权值设为 $1$，表示要翻转 $1$ 次；$a_{i,j}$ 为 $1$ 的话 $(i_{left},j_{right})$ 权值设为 $-1$，相当于翻回来。容易想到添加源汇点后，用最小费用最大流求解。

但这样有个问题：负环导致死循环。注意到我们最后选出的匹配边总数是确定的 $\displaystyle\sum A_i$，因此我们再令 $pans \leftarrow pans-\displaystyle\sum A_i$，并令匹配边的权值都加上 $1$ 就行了。用 Dijkstra 增广的理论复杂度是 $\Theta(n^2m^2(\log n+\log m))$，实际跑不满。

[for reference only.](https://codeforces.com/contest/1913/submission/237895076)

---

## 作者：MiniLong (赞：3)

无解条件是 $\sum a_i \neq \sum b_i$。

然后看到 $n,m\le 50$，加上是网格匹配，很容易想到网络流。那么对每个格子 $c_{i,j}$，如果 $c_{i,j}=0$，就连接边 $i \to j,w=1$ 表示这个格子放 $1$ 要花费一个代价；如果 $c_{i,j}=1$，就连 $i \to j,w=0$，表示不用花费。然后 $s \to i,w=a_i$，$j \to t,w=b_j$。但是最后跑出来的费用是不对的，因为有些原本是 $1$ 但没用上的点。如果这些点本来就不用翻转还不被用，那么在这个地方填 $1$ 也不可能有更优的答案，所以遍历残量网络，把所有 $c_{i,j}=1$ 但是没用到的边数加上，就是最终的答案了。

---

## 作者：Sunny郭 (赞：2)

一道很典的费用流题目。

首先考虑一个弱化版问题：当格子全为 0 时怎么分配 1。

可以直接对于每个行和每条列连流量为 1 的边，超源向每行连此行需要 1 的个数，每列向超汇连需要 1 的个数，然后直接最大流即可。

那么考虑转化原问题，先把所有 1 置为 0。再按照上面的方法填，每次改代价为 1，所以要给每条边一个 1 的代价跑费用流。

但是注意到原本为 1 的格子填 1 不花费代价，而我们计算了进去，所以考虑强制先选这些 1 的，所以给边设个 -1 的费用然后跑最小费用流即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 107, inf = 2e9;
int i, j, k, n, m, uid, res, s, t, x, E = 1, fb, fa, fl;
int H[N], L[N], h[N], e[N], v[N], u[N], a[N], b[N], z[N];
struct Yoi {
	int a, b, c, w, n;
} d[N * N];
void init() {
	s = ++uid, t = ++uid;
	for(i=1; i<=n; i++) H[i] = ++uid;
	for(i=1; i<=m; i++) L[i] = ++uid;
}
void add(int a, int b, int c, int w=1) {
	d[++E] = {a, b, +c, w, h[a]}, h[a] = E;
	d[++E] = {b, a, -c, 0, h[b]}, h[b] = E;
}
queue<int> q;
int bfs() {
	memset(v, 0x3f, sizeof v);
	memset(z, 0, sizeof z);
	v[s] = 0, q.push(s), z[s] = 1;
	int a, b, i, c;
	while(q.size()) {
		a = q.front(), q.pop(); u[a] = 0;
		for(i=e[a]=h[a]; i; i=d[i].n) {
			b = d[i].b, c = d[i].c;
			if(d[i].w && v[a] + c < v[b]) {
				v[b] = v[a] + c;
				z[b] = z[a] + 1;
				if(!u[b]) u[b] = 1, q.push(b);
			}
		}
	}
	return z[t];
}
int dfs(int a, int w) {
	if(a == t) return w;
	int i, b, c, s, f;
	for(int &i=e[a]; i; i=d[i].n) {
		b = d[i].b, c = d[i].c, f = min(d[i].w, w);
		if(f && z[b] == z[a] + 1 && v[a]+c == v[b] && (s=dfs(b, f))) {
			d[i].w -= s, d[i^1].w += s;
			return s;
		}
	}
	return 0;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m; init();
	for(i=1; i<=n; i++) for(j=1; j<=m; j++) {
		cin >> x; res += x;
		add(H[i], L[j], x ? -1 : 1);
	}
	for(i=1; i<=n; i++) cin >> a[i], fa += a[i];
	for(i=1; i<=m; i++) cin >> b[i], fb += b[i];
	for(i=1; i<=n; i++) add(s, H[i], 0, a[i]);
	for(i=1; i<=m; i++) add(L[i], t, 0, b[i]);
	while(bfs()) while(k=dfs(s, inf)) res += k * v[t], fl += k;
	cout << (fa == fl && fl == fb ? res : -1) << "\n";
	return 0;
}

```

---

## 作者：ollo (赞：1)

# 题意

给定一个 $n \times m$ 的矩阵和 $n+m$ 条限制，第 $A_i$ 表示第 $i$ 行必须恰好有 $A_i$ 个 $1$，$B_j$ 表示第 $j$ 列必须恰好有 $B_j$ 个 $1$。一次操作定义为改变一个点的值，问满足要求的最小操作次数。

# 思路

如果矩阵全为 $0$ 这就是最大流的典题，将 $(i, j, 1)$ 视作连接第 $i$ 行第 $j$ 列的边，然后将行连向超级源点，流量为 $A_i$；将列连向超级汇点，流量为 $B_j$。最后跑完最大流之后判断流量是否为 $\sum B_j$ 即可。

但是现在我们的矩阵并不是全为 $0$，不妨将所有 $1$ 改为 $0$，但这样显然不一定最优。所以我们需要引入反悔操作，流量的模型已经有了，我们可以把它放到边权上。

具体来说，定义 $(i, j, 1, 1/-1)$ 视作连接第 $i$ 行第 $j$ 列的边，当且仅当 $[i,j]$ 为 $1$ 时边权为 $-1$。那么现在改变一个原本就为 $1$ 的点时就相当于撤销了初始时在这个点的附 $0$ 操作。最后答案就是最小费用。最后用最大流和行列上的约束之和分别判无解即可。

# code
```cpp
#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

template<class T> inline void read(T &n){
    n = 0;
    bool _f = 0; char _c = getchar();
    while(_c < '0' || '9' < _c) {if(_c == '-') _f = 1; _c = getchar();}
    while('0' <= _c && _c <= '9') n = n * 10 + _c - '0', _c = getchar();
    if(_f) n = -n;
}

const int M = 100, N = 1e5 + 10, inf = 114514191981021470;

struct S{
	int nxt, to, flow, w;
}e[N * 2];
int head[N], tot = 1;
int n, m, s, t;
long long maxflow, ans;
void add(int u, int v, int f, int w){
	e[++tot].nxt = head[u];e[tot].to = v;e[tot].flow = f;e[tot].w = w;head[u] = tot;
	e[++tot].nxt = head[v];e[tot].to = u;e[tot].flow = 0;e[tot].w = -w;head[v] = tot;
}
bool vis[N];
int dis[N], flow[N], to[N];
bool spfa(){
	memset(vis, 0, sizeof(vis));
	memset(flow, 0x7f, sizeof(flow));
	memset(dis, 0x7f, sizeof(dis));
	queue<int> q;q.push(s);vis[s] = 1;dis[s] = 0;
	while(!q.empty()){
		int u = q.front();q.pop();vis[u] = 0;
		for(int i = head[u]; i; i = e[i].nxt){
			int v = e[i].to, f = e[i].flow, w = e[i].w;
			if(f > 0 && dis[u] + w < dis[v]){
//				if(vis[v]) continue;
				dis[v] = dis[u] + w;flow[v] = min(flow[u], f);to[v] = i;
				if(vis[v] == 0){q.push(v);vis[v] = 1;}
			}
		}
	}
	return dis[t] < 0x7f7f7f7f;
}
void EK(){
	int u = t;
	while(u != s){
		int l = to[u];
		e[l].flow -= flow[t];e[l ^ 1].flow += flow[t];u = e[l ^ 1].to;
	}
	maxflow += flow[t];ans += flow[t] * dis[t];return ;
}

char c[M][M];
int A[M], B[M];

signed main(){
	read(n);read(m);
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			cin >> c[i][j];
		}
	}
	for(int i = 1; i <= n; i++) cin >> A[i];
	for(int i = 1; i <= m; i++) cin >> B[i];
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			if(c[i][j] == '0') add(i, n + j, 1, 1), add(n + j, i, 0, -1);
			else{
				add(n + j, i, 1, 1), add(i, n + j, 0, -1);A[i]--;B[j]--;
			}
		}
	}
	s = n + m + 1;t = n + m + 2;
	int sum1 = 0, sum2 = 0;
	for(int i = 1; i <= n; i++){
		if(A[i] > 0){
			add(s, i, A[i], 0);add(i, s, 0, 0);
			sum1 += A[i];
		}
		else{
			add(i, t, -A[i], 0);add(t, i, 0, 0);
			sum2 -= A[i];
		}
	}
	for(int i = 1; i <= m; i++){
		if(B[i] > 0){
			add(n + i, t, B[i], 0);add(t, n + i, 0, 0);
			sum2 += B[i];
		}
		else{
			add(s, n + i, -B[i], 0);add(n + i, s, 0, 0);
			sum1 -= B[i];
		}
	}
	if(sum1 != sum2){cout << "-1\n";return 0;}
	while(spfa()) EK();
	if(maxflow != sum1){cout << "-1\n";return 0;}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Drimpossible (赞：1)

## 题意：
给定一个 $n \times m$ 的零一矩阵，花费 $1$ 的代价可以翻转一个位置的值，求至少要多少代价使得最后第 $i$ 行恰好有 $a_i$ 个 $1$，第 $j$ 列恰好有 $b_j$ 个 $1$，或报告无解。
## 思路：
首先观察这个数据范围，以及是在一个矩阵里进行操作的问题，我们考虑网络流。

接下来思考如何建模。首先有一个很显然但是错误的建模方式：把每行和每列看成一个点，源点向行 $i$ 连一条流量为 $a_i$ 费用为 $0$ 的边，列 $j$ 向汇点连一条流量为 $b_j$ 的边，当 $c_{i,j}$ 为 $1$ 的时候就建一条 $i$ 到 $j$ 流量为 $1$ 费用为 $0$ 的边，$c_{i,j}$ 为 $0$ 就把费用改成 $1$，然后跑一遍费用流。

看起来好像很对是不是？但是你一测样例发现第二个样例输出了 $0$，仔细思考一下你会发现，由于你矩阵中 $1$ 的费用是永远小于 $0$ 的费用的，所以在跑的时候会优先选 $1$ 的边去流，就算流满了也不会选 $0$。所以最后求出来的答案是“不小于”的代价而不是“恰好”。

但是它过了第一个样例，这启发我们正解应该不会差太多。我们考虑如何把选 $0$ 的情况加入统计，发现可以在最开始的时候先把所有数变成 $0$，然后再考虑把一些数变成 $1$。于是正解就出来了，先把所有数变成 $0$ 的代价累加进答案，然后对于矩阵中的每个 $1$ 的代价就是 $-1$，$0$ 的代价就是 $1$。

跑费用流即可，无解的情况就是源点或者汇点直接相连的边没有流满。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=205,M=2009421;
const int inf=0x7f7f7f7f7f7f7f7f;
int n,m,S,T;
struct edge{
	int v,w,d,nxt;
}e[M];
int head[N],cnt=1;
void adde(int u,int v,int w,int d){
	e[++cnt]={v,w,d,head[u]},head[u]=cnt;
	e[++cnt]={u,0,-d,head[v]},head[v]=cnt;
}
queue<int>q;
int pre[N],dis[N],vis[N],flow[N];
bool spfa(){
	while(!q.empty())q.pop();
	memset(dis,0x7f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	q.push(S),vis[S]=1,dis[S]=0;
	flow[S]=inf,pre[T]=-1;
	while(!q.empty()){
		int u=q.front();q.pop();
		vis[u]=0;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].v,w=e[i].w,d=e[i].d;
			if(w<=0)continue;
			if(dis[v]>dis[u]+d){
				dis[v]=dis[u]+d;
				flow[v]=min(flow[u],w);
				pre[v]=i;
				if(!vis[v])
					q.push(v),
					vis[v]=1;
			}
		}
	}
	return dis[T]!=inf;
}
int mxflow=0,mncost=0;
void Edmonds_Karp(){//EK+spfa求费用流
	while(spfa()){
		int u=T;
		while(u!=S){
			int i=pre[u];
			e[i].w-=flow[T];
			e[i^1].w+=flow[T];
			u=e[i^1].v;
		}
		mxflow+=flow[T];
		mncost+=flow[T]*dis[T];
	}
}
int c[N][N],a[N],b[N];
signed main(){
	cin>>n>>m,S=n+m+1,T=n+m+2;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			int x;cin>>x,mncost+=x;//先累加所有数变成0
			adde(i,j+n,1,x==1?-1:1);//1变成1就要把原来累加的代价去掉
		}
	for(int i=1;i<=n;i++){
		int x;cin>>x;
		adde(S,i,x,0);
	}
	for(int i=1;i<=m;i++){
		int x;cin>>x;
		adde(i+n,T,x,0);
	}
	Edmonds_Karp();
	for(int i=head[S];i;i=e[i].nxt){
		int w=e[i].w;
		if(w>0)return puts("-1"),0;
	}
	for(int i=head[T];i;i=e[i].nxt){
		int w=e[i^1].w;
		if(w>0)return puts("-1"),0;
	}
	cout<<mncost;
	return 0;
}
```


---

## 作者：wosile (赞：1)

vp 的时候被我秒掉的水 E。

实际上这道题可以直接连接代表行的点和代表列的点。我展现了一种完全劣化且更加复杂的思路，仅作为我赛时思路的记录。
 
首先这个题一看就是个很复杂没法贪心没法 dp 的规划题，考虑网络流。如果是往一个全 $0$ 矩阵上填 $1$，考虑把一个格子拆成 $\text{in}$ 和 $\text{out}$ 两个点，按照 $\text{源点}\rightarrow\text{代表行的点}\rightarrow\text{in} \rightarrow \text{out} \rightarrow \text{代表列的点} \rightarrow \text{汇点}$ 的样子建图很容易可以求出一种方案。特别地，对于 $(i,j)$ 的 $\text{in} \rightarrow \text{out}$ 的边，容量为 $1$，有流量表示 $a_{i,j}=1$，否则表示 $a_{i,j}=0$。
 
这题不是全 $0$ 矩阵，还要求最小操作次数，考虑最小费用最大流。建图方法和上面一样，考虑费用怎么加，能使得产生一点费用当且仅当 $[(i,j) \text{ 对应的 in->out 边有流量}]\not=a_{i,j}$。显然，我们可以设 $a_{i,j}=0$ 的边的费用为 $1$（流过之后即需要更改），$a_{i,j}=1$ 的边的费用为 $-1$（流过之后即不需要更改），并在最后给答案加上 $\sum a_{i,j}$ 来校准 $a_{i,j}=1$ 的格子的费用。其他边的费用取 $0$ 就好了。

比较简单的网络流题，时间复杂度 $O(n^3m^3)$，但是因为是网络流所以随便过。


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define inf 0x3f3f3f3f
struct edge{
	int to,cap,rev,cost;
	edge(){}
	edge(int t_,int c_,int r_,int o_):to(t_),cap(c_),rev(r_),cost(o_){}
};
vector<edge>G[10005];
int T;
inline void clear(){
	for(int i=0;i<=T;i++)G[i].clear();
}
int dis[10005],inq[10005];
queue<int>q;
void add(int u,int v,int w,int c){
	// printf("add %d %d %d\n",u,v,w);
	G[u].push_back(edge(v,w,G[v].size(),c));
	G[v].push_back(edge(u,0,G[u].size()-1,-c));
}//
int n,m;
inline int id(int x,int y){
	return (x-1)*m+y;
}
int mc=0,mf=0;
edge from[10005];
bool spfa(){
	memset(dis,0x3f,sizeof(dis));
	memset(inq,0,sizeof(inq));
	while(!q.empty())q.pop();
	q.push(0);
	dis[0]=0;
	while(!q.empty()){
		int f=q.front();
		q.pop();
		inq[f]=0;
		for(int i=0;i<(int)G[f].size();i++){
			edge e=G[f][i];
			if(!e.cap)continue;
			if(dis[e.to]>dis[f]+e.cost){
				dis[e.to]=dis[f]+e.cost;
				if(!inq[e.to]){
					q.push(e.to);
					inq[e.to]=1;
				}
				from[e.to]=edge(f,0,i,0);
			}
		}
	}
	return dis[T]<inf;
}
void update(){
	int mn=inf;
	int cur=T;
	while(cur>0){
		edge e=from[cur];
		mn=min(G[e.to][e.rev].cap,mn);
		cur=e.to;
	}
	cur=T;
	while(cur>0){
		edge e=from[cur];
		G[e.to][e.rev].cap-=mn;
		G[cur][G[e.to][e.rev].rev].cap+=mn;
		cur=e.to;
	}
	mf+=mn;
	mc+=mn*dis[T];
}
int main(){
	scanf("%d%d",&n,&m);
	int sum=0;
	T=2*n*m+n+m+1;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
		int x;
		scanf("%d",&x);
		sum+=x;
		add(id(i,j)*2-1,id(i,j)*2,1,(x==1?-1:1));
		add(2*n*m+i,id(i,j)*2-1,1,0);
		add(id(i,j)*2,2*n*m+n+j,1,0);
	}
	int suma=0;
	for(int i=1;i<=n;i++){
		int x;
		scanf("%d",&x);
		suma+=x;
		add(0,2*n*m+i,x,0);
	}
	int sumb=0;
	for(int i=1;i<=m;i++){
		int x;
		scanf("%d",&x);
		sumb+=x;
		add(2*n*m+n+i,T,x,0);
	}
	if(suma!=sumb){
		printf("-1");
		return 0;
	}
	while(spfa())update();
	if(mf!=suma)printf("-1");
	else printf("%d",sum+mc);
	return 0;
}
//quod erat demonstrandum
```

---

## 作者：Shunpower (赞：0)

我真是一点不会网络流。。。。。。。

------------

显然是网络流。

考虑我们怎么表示一个点 $(i,j)$ 被选了，容易想到应该费用流一下，流过一条边表示选择一个点翻转，费用为 $1$。

考虑这产生的影响，就是 $a_i\gets a_i\pm 1,b_j\gets b_j\pm 1$。容易想到需要建两排点表示每一行、每一列。此时我们不能把两类点都往汇点上连，否则一个点的贡献需要 $2$ 的满流才能表示，这样的要求不符合网络流的性质。所以我们应该把一种限制拆到源点上，表现为限制流量为 $a_i$ 或 $b_i$。

不妨把行限制拆到源点上，源点 $S$ 向 $i$ 连容量为 $a_i$，费用为 $0$ 的边表示一行需要 $a_i$ 个 $1$，$i'$ 向汇点 $T$ 连容量为 $b_i$，费用为 $0$ 的边表示一列需要 $b_i$ 个 $1$。这样在判掉 $\sum a\ne \sum b$ 的无解后，只要满流 $\sum a=\sum b$ 就意味着合法解。

考虑怎么连接 $i,i'$。显然对于一个点 $(i,j)$，我们应当连接 $i\to j'$，流这条边，也就是选这个点，就可以让源点到 $i$ 和 $j'$ 到汇点的流量都 $+1$，表示这一行一列多了一个 $1$。

问题是费用。这样做我们不好计算翻转一次 $1\to 0$ 的费用。不妨先把所有 $1$ 翻过来，这样 $1\to 0$ 费用就为 $0$，但 $1\to 1$ 就需要费用 $-1$ 表示翻回去。这样跑费用流，最后给最小费用加一个 $\sum c$ 就可以了。

实现时注意判无解需要判 $\sum a=\sum b$、判满流和判费用负圈。

```cpp
int n,m;
int c[55][55];
int a[55],b[55];
int S,T;
int head[N],nxt[N],to[N],wgt[N],cst[N],flow[N];
int dth[N],dep[N],now[N];
int cnt[N];
bool vis[N];
int tot=1;
int cost;
int suma,sumb,sumc;
void add(int u,int v,int w,int c){
    tot++;
    nxt[tot]=head[u];
    head[u]=tot;
    to[tot]=v,wgt[tot]=w,cst[tot]=c;
    tot++;
    nxt[tot]=head[v];
    head[v]=tot;
    to[tot]=u,wgt[tot]=0,cst[tot]=-c;
}
bool spfa(){
    fr1(i,S,T) dth[i]=0,dep[i]=1e9,cnt[i]=0;
    dep[S]=0,dth[S]=1;
    queue <int> q;
    q.push(S);
    vis[S]=1;
    while(!q.empty()){
        int x=q.front();
        q.pop();
        vis[x]=0;
        if(cnt[x]==n) cout<<"-1\n",exit(0);
        for(int i=head[x];~i;i=nxt[i]){
            int y=to[i];
            if(flow[i]<wgt[i]&&dep[y]>dep[x]+cst[i]){
                dth[y]=dth[x]+1;
                dep[y]=dep[x]+cst[i];
                if(!vis[y]) q.push(y),vis[y]=1,cnt[y]++;
            }
        }
    }
    return dep[T]!=1e9;
}
int dfs(int x,int fl){
    if(x==T) return fl;
    vis[x]=1;
    int used=0;
    for(int i=now[x];~i;i=nxt[i]){
        now[x]=i;
        int y=to[i];
        if(dth[y]==dth[x]+1&&!vis[y]&&dep[y]==dep[x]+cst[i]&&flow[i]<wgt[i]){
            int d=dfs(y,min(fl-used,wgt[i]-flow[i]));
            if(d){
                used+=d;
                cost+=d*cst[i];
                flow[i]+=d;
                flow[i^1]-=d;
            }
        }
    }
    vis[x]=0;
    return used;
}
int main(){
#ifdef Shun
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
#endif
    memset(head,-1,sizeof head);
    ios::sync_with_stdio(false);
    cin>>n>>m;
    fr1(i,1,n) fr1(j,1,m) cin>>c[i][j],sumc+=c[i][j];
    fr1(i,1,n) cin>>a[i],suma+=a[i];
    fr1(i,1,m) cin>>b[i],sumb+=b[i];
    if(suma!=sumb) return cout<<"-1\n",0;
    S=0,T=n+m+1;
    fr1(i,1,n) add(S,i,a[i],0);
    fr1(i,1,n){
        fr1(j,1,m){
            if(c[i][j]) add(i,n+j,1,-1);
            else add(i,n+j,1,1);
        }
    }
    fr1(i,1,m) add(n+i,T,b[i],0);
    int ans=0;
    while(spfa()){
        fr1(i,S,T) now[i]=head[i];
        ans+=dfs(S,inf);
    }
    if(ans!=suma) return cout<<"-1\n",0;
    cout<<cost+sumc<<'\n';
    ET;
}
//ALL FOR Zhang Junhao.
```

---

## 作者：subcrip (赞：0)

另一种不需要处理负权的建图方法。

假设第 $i$ 行用图中节点 $l_i$ 表示，而第 $j$ 列用 $r_j$ 表示。用边 $(l_i,r_j)$ 或者 $(r_j,l_i)$ 表示一个格子的变化。当 $a_{ij}=1$ 时，连一条边 $(l_i,r_j)$；当 $a_{ij}=0$ 时，连一条边 $(r_j,l_i)$。容量和费用都是 $1$。

这样建图之后，我们发现使对应行列的值减少的那些边一定是形如 $(r_j,l_i)$ 的，而使得对应行列的值增加的边是 $(l_i,r_j)$。所以我们考虑让源点 $S$ 向 $r_j$ 提供这些列中**多余的值**，也就是 $\max(0,\sum_i a_{ij}-B_j)$，这些多余值经过 $(r_j,l_i)$ 之后再通过 $l_i$ 流到汇点 $T$。同理让 $S$ 向 $l_i$ 提供这些行中**缺少的值**，这些值通过 $r_j$ 流到 $T$。

这样建图之后，跑最小费用最大流，产生满足条件的解当且仅当流满。此时输出费用就是答案。

```cpp
void solve() {
    read(int, n, m);
    vector a(n, vector<int>(m));
    vector<int> suml(n), sumr(m);
    for (int i = 0;  i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
            suml[i] += a[i][j];
            sumr[j] += a[i][j];
        }
    }

    readvec(int, l, n);
    readvec(int, r, m);

    mcmf net(n + m + 2);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == 0) {
                net.add_edge(i, n + j, 1, 1);
            } else {
                net.add_edge(n + j, i, 1, 1);
            }
        }
    }

    int s = n + m, t = n + m + 1;
    int target = 0;

    for (int i = 0; i < n; ++i) {
        if (l[i] > suml[i]) {
            net.add_edge(s, i, l[i] - suml[i], 0);
            target += l[i] - suml[i];
        } else {
            net.add_edge(i, t, suml[i] - l[i], 0);
        }
    }

    for (int i = 0; i < m; ++i) {
        if (r[i] > sumr[i]) {
            net.add_edge(n + i, t, r[i] - sumr[i], 0);
        } else {
            net.add_edge(s, n + i, sumr[i] - r[i], 0);
            target += sumr[i] - r[i];
        }
    }

    auto [flow, cost] = net.run(s, t);

    if (flow == target) {
        cout << cost << '\n';
    } else {
        cout << -1 << '\n';
    }
}
```

---

## 作者：ダ月 (赞：0)

一眼丁真费用流。

首先，$\sum a_i\ne \sum b_i$ 肯定无解。

我们将每一行和每一列抽象各出一个结点，变成了一个二分图。（左边为行，右边为列。）套路的，将点权转换为边权，我们将每个结点拆成两个点，这两个点之间边的流量为 $a_i$（列的结点为 $b_i$），其中费用为 $0$。我们一共有了四排点。

接下来最左边的所有点连一个超级源点，最右边那一排点连一个超级汇点。这些边的流量为 $+\infty$，费用为 $0$。

接下来第二列点和第三列点之间要连上一些边，记第二列第 $i$ 个点为 $L_i$，第三列第 $j$ 个点为 $R_j$（$i\in[1,n]$，$j\in[1,m]$）。记题面中的矩阵为 $M$。如果 $M_{i,j}$ 为 $0$，那么 $L_i$ 向 $R_j$ 连一条流量为 $1$，费用为 $1$ 的点；否则，若 $M_{i,j}=1$，连一条流量为 $1$，费用为 $0$ 的点。

跑一遍 Dinic，我们 check 一下流是否等于 $\sum a_i$。然后在残余网络中第二列和第三列之间的边是否流过，就能得到答案。具体地，在**残余网络**中，如果 $L_i$ 到 $R_j$ 的当前流量为 $0$，那么如果 $M_{i,j}=0$，那么说明这个点要反转。如果 $L_i$ 到 $R_j$ 当前流量为 $1$ 且 $M_{i,j}=1$，那么说明当前这个点也要转。

然后，就做完了。

```
struct costDinic{
	const ll inf=0x3f3f3f3f3f3f3f3f;
	struct node{int y,nxt;ll val,c;}E[N<<1];
	int H[N],cnt;
	void add(int x,int y,ll z,ll c){E[++cnt]={y,H[x],z,c};H[x]=cnt;}
	void Add(int x,int y,ll z,ll c){add(x,y,z,c);add(y,x,0,-c);}
	int dep[N],cur[N];ll dis[N];
	int S,T,n;ll C;
	bool vis[N];
	void init(int _S,int _T,int _n){
		S=_S;T=_T;n=_n;
		for(int i=1;i<=n;i++)H[i]=0;
		cnt=1;C=0;
		memset(vis,0,sizeof(vis));
	}
	bool SPFA(){
		memset(dis,0x3f,sizeof(dis));
		std::queue<int>q;q.push(S);
		dis[S]=0;vis[S]=true;
		while(!q.empty()){
			auto x=q.front();q.pop();vis[x]=false;
			for(int i=H[x];i;i=E[i].nxt){
				auto y=E[i].y;
				if(E[i].val&&dis[x]+E[i].c<dis[y]){
					dis[y]=dis[x]+E[i].c;
					if(!vis[y])q.push(y),vis[y]=true;
				}
			}
		}return dis[T]!=inf;
	}
	ll dfs(int x,ll mf){
		if(x==T)return mf;ll ans=0;vis[x]=true;
		for(int &i=cur[x];i&&ans<mf;i=E[i].nxt){
			auto y=E[i].y;
			if(!vis[y]&&E[i].val&&dis[y]==dis[x]+E[i].c){
				ll f=dfs(y,std::min(E[i].val,mf-ans));
				if(f)C+=f*E[i].c,E[i].val-=f,E[i^1].val+=f,ans+=f;
			}
		}vis[x]=false;
		return ans;
	}
	std::pair<ll,ll>Dinic(){
		ll ans=0,x;
		while(SPFA()){
			memcpy(cur,H,sizeof(cur));
			while(x=dfs(S,inf))ans+=x;
		}
		return mpr(ans,C);
	}
}E;
void solve(){
	//don't forget to open long long
	int n,m;IO::cin>>n>>m;int L=n*m;
	//auto get=[&](int x,int y)->{return (x-1)*m+y;};
	ve<ve<int>>v(n+1,ve<int>(m+1));
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)IO::cin>>v[i][j];
	ve<ll>A(n),B(m);IO::cin>>A>>B;
	ll s=accumulate(all(A),0ll);
	mpre(A);mpre(B);int sz=n*2+m*2+2;
	ll S=sz-1,T=sz;
	E.init(S,T,sz);
	if(s!=accumulate(all(B),0ll))return IO::cout<<"-1",void();
	for(int i=1;i<=n;i++)E.Add(i,i+n,A[i],0);
	for(int i=1;i<=m;i++)E.Add(i+n*2,i+m+n*2,B[i],0);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			E.Add(i+n,j+n*2,1,!v[i][j]);
	for(int i=1;i<=n;i++)E.Add(S,i,E.inf,0);
	for(int i=1;i<=m;i++)E.Add(i+m+n*2,T,E.inf,0);
	auto V=E.Dinic();ll ans=0;
	if(V.first!=s)return IO::cout<<-1<<'\n',void();
	for(int i=1;i<=n;i++){
		for(int j=E.H[i+n];j;j=E.E[j].nxt){
			int y=E.E[j].y;
			if(y>=n*2+1&&y<=n*2+m){
				if(v[i][y-n*2]){
					if(E.E[j].val)
						ans++;
				}else{
					if(!E.E[j].val)
						ans++;
				}
			}
		}
	}
	IO::cout<<ans<<'\n';
}
```


---

## 作者：EuphoricStar (赞：0)

考虑费用流，对于每一行建两个点 $i_0, i_1$，分别代表这一行的所有 $0, 1$。同样每一列建两个点 $j_0, j_1$。源点分别向 $i_0, i_1$ 连流量为这一行要求的 $0$ 或 $1$ 的个数，费用为 $0$。同理连汇点。

对于一对 $(i, j)$，我们有两种选择，让一个流量从 $i_0 \to j_0$ 或从 $i_1 \to j_1$。前者在 $a_{i, j} = 1$ 时产生 $1$ 的费用，后者在 $a_{i, j} = 0$ 时产生 $1$ 的费用。

跑最小费用最大流，若不满流就无解，否则答案就是最小费用。

[code](https://codeforces.com/problemset/submission/1913/238216637)

---

