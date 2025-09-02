# Reindeer Games

## 题目描述

There are $ n $ reindeer at the North Pole, all battling for the highest spot on the "Top Reindeer" leaderboard on the front page of CodeNorses (a popular competitive reindeer gaming website). Interestingly, the "Top Reindeer" title is just a measure of upvotes and has nothing to do with their skill level in the reindeer games, but they still give it the utmost importance.

Currently, the $ i $ -th reindeer has a score of $ a_i $ . You would like to influence the leaderboard with some operations. In an operation, you can choose a reindeer, and either increase or decrease his score by $ 1 $ unit. Negative scores are allowed.

You have $ m $ requirements for the resulting scores. Each requirement is given by an ordered pair $ (u, v) $ , meaning that after all operations, the score of reindeer $ u $ must be less than or equal to the score of reindeer $ v $ .

Your task is to perform the minimum number of operations so that all requirements will be satisfied.

## 样例 #1

### 输入

```
7 6
3 1 4 9 2 5 6
1 2
2 3
3 4
4 5
5 6
6 7```

### 输出

```
1 1 4 4 4 5 6```

## 样例 #2

### 输入

```
4 6
6 5 8 2
3 1
4 1
3 2
1 2
2 3
3 1```

### 输出

```
6 6 6 2```

## 样例 #3

### 输入

```
10 18
214 204 195 182 180 176 176 172 169 167
1 2
3 2
4 2
5 2
6 2
7 2
8 2
9 2
10 2
6 1
6 2
6 3
6 4
6 5
6 7
6 8
6 9
6 10```

### 输出

```
204 204 195 182 180 167 176 172 169 167```

# 题解

## 作者：Jsxts_ (赞：2)

看到数据范围比较小，考虑转化成线性规划标准型后用单纯形求解。

那么将对每个数加多少和减多少拆成两个变量，限制转换为：

$$a_i+x_i-x'_i\le a_j+x_j-x'_{j}$$
$$x_i-x'_i-x_j+x'_j\le a_j- a_i$$

套用单纯形模板求即可。直接做会 TLE，在 pivot 函数加一个优化就可以过了。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int inf = 1e9;
const ll INF = 1e15;
const int N = 1e3;
const double eps = 1e-6;
inline int read() {
	int s = 0,f = 1;char ch = getchar();
	while (!isdigit(ch)) f = ch == '-' ? -1 : 1, ch = getchar();
	while (isdigit(ch)) s = (s << 3) + (s << 1) + ch - '0', ch = getchar();
	return s*f;
}

ll ans[N * 4 + 10];
struct Simplex {
	double A[N * 2 + 10][N * 2 + 10];
	int id[N * 4 + 10],n,m;
	void pivot(int r,int c) {
		swap(id[r + n],id[c]);
		double t = A[r][c];
		A[r][c] = 1;
		for (int i = 0;i <= n;i ++ ) A[r][i] /= t; 
		vector<int> vc;
		for (int i = 0;i <= n;i ++ ) if (fabs(A[r][i]) > eps) vc.push_back(i);
		for (int i = 0;i <= m;i ++ ) {
			if (abs(A[i][c]) > eps && i != r) {
				t = A[i][c], A[i][c] = 0;
				for (int j : vc) A[i][j] -= t * A[r][j];
			}
		}
	}
	void init() {
		for (int i = 1;i <= n;i ++ ) id[i] = i;
		while (1) {
			int r = 0,c = 0;
			for (int i = 1;i <= m;i ++ )
				if (A[i][c] < -eps && (!r || rand() & 1)) r = i;
			if (!r) return;
			for (int i = 1;i <= n;i ++ )
				if (A[r][i] < -eps && (!c || rand() & 1)) c = i;
			if (!c) {
				puts("-1");
				exit(0);
			}
			pivot(r,c);
		}
	}
	void simplex() {
		while (1) {
			int r = 0,c = 0;
			double mx = eps;
			for (int i = 1;i <= n;i ++ )
				if (A[0][i] > mx) c = i, mx = A[0][i];
			if (!c) return;
			double mn = INF;
			for (int i = 1;i <= m;i ++ )
				if (A[i][c] > eps && A[i][0] / A[i][c] < mn)
					r = i, mn = A[i][0] / A[i][c];
			if (!r) puts("Unbounded"), exit(0);
			pivot(r,c);
		}
	}
	void get_p() {
		for (int i = 1;i <= m;i ++ ) ans[id[i + n]] = ll(A[i][0] + 0.5);
	}
	// n 变量数 m 限制数 
	//A[0][i]:标准形中的 c[i]
	//A[i][j]:标准形中的 a[i][j]
	//A[i][0]:原为标准形中的 b[j]，经过算法后变为标准形中的 x[j]（即解） 
	//-A[0][0]:max z
	//注意此代码处理的限制为Σa[i][j]*x[j]<=b[i] 而非 = 
	//调用init()初始化，若所有 x[i] = 0 是一组可行解就不用初始化
	//调用simplex()进行算法 
	//调用get_project()得出方案 
	//注意数组开多少要自己调下 
}S;
int a[N + 10];
int main() {
	int n = read(),m;S.n = n * 2;
	m = S.m = read();
	for (int i = 1;i <= n;i ++ ) a[i] = read();
	for (int i = 1;i <= 2 * n;i ++ ) S.A[0][i] = -1;
	for (int i = 1;i <= m;i ++ ) {
		int x = read(),y = read();
		S.A[i][x + n] = -1, S.A[i][x] = 1;
		S.A[i][y + n] = 1, S.A[i][y] = -1;
		S.A[i][0] = a[y] - a[x];
	}
	S.init(), S.simplex(), S.get_p();
	for (int i = 1;i <= n;i ++ ) printf("%lld ",ans[i] - ans[i + n] + a[i]);
	return 0;
}
```


---

## 作者：Purslane (赞：0)

# Solution

保序回归的 $L_1$ 问题，不带权。

> 保序回归问题：给定一组**正**权值 $w_i$ 和基准量 $y_i$，以及正整数 $k$，求出一组 $z$ 使得 $\sum w_i | z_i - y_i | ^k$ 最小，且 $z$ 满足一些形如 $z_{u_i} \le z_{v_i}$ 的非严格偏序限制。当 $k=1$ 的时候，称为 $L_1$ 问题。

在 $2018$ 年国家集训队论文《浅谈保序回归问题》中，提出了一种使用整体二分解决此类问题的方法：

如果存在开区间 $(a,b)$ 使得 $\forall i,y_i \notin (a,b)$，且最优解 $z^s$ 也满足 $\forall i,z_i^s \neq (a,b)$，那么加上额外限制：$z_i \in \{a,b\}$，得到新的一组解 $z^t$，则 $z^s_i \le a$ 的充要条件是 $z^t_i=a$。

而处理 $z_u \in \{a,b\}$ 是经典的**最大权闭合子图**模型，可以使用网络流解决。

注意到最优解必有 $z_i \in \{y_1,y_2,\dots,y_n\}$，因此可以将 $y$ 离散化后整体二分。划分后两个子集互不影响，可以当做新问题继续做下去。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1000+10,MAXM=1000+10;
int n,m,res[MAXN],a[MAXN],k,lsh[MAXN];
namespace FLOW {
	struct Edge {
		int to,nxt,w;
	}edge[MAXN*10];
	int s,t,tot,hd[MAXN],cur[MAXN],dis[MAXN];
	void init(vector<int>& vc) {
		tot=1;
		for(auto id:vc) hd[id]=cur[id]=0;
		s=0,t=n+1,hd[s]=hd[t]=0;
		return ;	
	}
	void add_edge(int u,int v,int w) {
		edge[++tot]={v,hd[u],w},hd[u]=tot;
		edge[++tot]={u,hd[v],0},hd[v]=tot;
		return ;	
	}
	int bfs(vector<int>& vc) {
		for(auto id:vc) dis[id]=-1;
		dis[s]=dis[t]=-1;
		queue<int> q;
		dis[s]=0,q.push(s);
		while(!q.empty()) {
			int u=q.front(); q.pop();
			cur[u]=hd[u];
			for(int i=hd[u];i;i=edge[i].nxt) {
				int to=edge[i].to,w=edge[i].w;
				if(!w||dis[to]!=-1) continue ;
				dis[to]=dis[u]+1,q.push(to);
			}
		}
		return dis[t]!=-1;
	}
	int dinic(int u,int mx) {
		if(u==t) return mx;
		int res=0;
		for(int i=cur[u];i;i=edge[i].nxt,cur[u]=i) {
			int to=edge[i].to,w=edge[i].w;
			if(dis[to]!=dis[u]+1||!w) continue ;
			int tans=dinic(to,min(mx,w));
			if(tans) {
				edge[i].w-=tans,edge[i^1].w+=tans,res+=tans,mx-=tans;
				if(!mx) break ;	
			}
			else dis[to]=-1;
		}
		return res;
	}
	int vis[MAXN];
	void dfs(int u) {
		if(vis[u]) return ;
		vis[u]=1;
		for(int i=hd[u];i;i=edge[i].nxt) {
			int to=edge[i].to,w=edge[i].w;
			if(!w) continue ;
			dfs(to);
		}
		return ;
	}
	void get_cut(vector<int>& vc) {
		for(auto id:vc) vis[id]=0;
		vis[s]=vis[t]=0,dfs(s);
		return ;
	}
}
int flg[MAXN];
vector<int> G[MAXN];
void solve(int l,int r,vector<int> vc) {
	if(l==r) {
		for(auto id:vc) res[id]=lsh[l];
		return ;
	}
	if(vc.empty()) return ;
	int mid=l+r>>1;
	FLOW::init(vc);
	for(auto id:vc) if(a[id]>lsh[mid]) FLOW::add_edge(0,id,1); else FLOW::add_edge(id,n+1,1);
	for(auto id:vc) flg[id]=1;
	for(auto u:vc) for(auto v:G[u]) if(flg[v]) FLOW::add_edge(u,v,1000000000);
	for(auto id:vc) flg[id]=0;
	while(FLOW::bfs(vc)) while(FLOW::dinic(0,1000000000));
	FLOW::get_cut(vc);
	vector<int> L,R;
	for(auto id:vc) if(FLOW::vis[id]) R.push_back(id); else L.push_back(id);
	solve(l,mid,L),solve(mid+1,r,R);
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,1,n) cin>>a[i],lsh[++k]=a[i];
	ffor(i,1,m) {int u,v;cin>>u>>v,G[u].push_back(v);}
	sort(lsh+1,lsh+k+1),k=unique(lsh+1,lsh+k+1)-lsh-1;
	vector<int> vc;
	ffor(i,1,n) vc.push_back(i);
	solve(1,k,vc);
	ffor(i,1,n) cout<<res[i]<<' ';
	return 0;
}
```

---

## 作者：Leasier (赞：0)

保序回归入门题。感谢 [rqoi031](https://www.luogu.com.cn/user/515947) 对我的帮助。

~~虽然但是，这道题的正解好像本来不是这样（~~

------------

我们来把原问题抽象一下：

- 给定一个长为 $n$ 的序列 $a$，满足 $1 \leq a_i \leq 10^9$。
- 有一个长为 $n$ 的序列 $b$，满足 $-10^{15} \leq b_i \leq 10^{15}$。
- 给定 $m$ 条要求，每条形如 $b_u \leq b_v$。
- 构造任意一个 $b$，使得 $\displaystyle\sum_{i = 1}^n f_i(b_i)$ 最小，其中 $f_i(x) = |x - a_i|$。

接下来给出论文中的如下结论（证明略去）：

- 若求和的单项是凸函数（如这里的 $f_i(x)$ 关于 $x$ 下凸），给出值域区间 $[l, r]$，令 $b'_i = \min(\max(b_i, l), r)$，则强制 $b_i \in [l, r]$ 时的最优解为 $b'_i$。

显然最优解中 $b_i$ 为整数，考虑钦定一个 $mid$，现在我们想要把 $\leq mid, > mid$ 者分开。

不妨把值域限定在 $[mid, mid + 1]$，则 $b_u \leq b_v$ 相当于当 $b_u = mid + 1$，$b_v = mid + 1$。

又因为只有两种选择，不妨把这个东西抽象成最大权闭合子图的模型：

- 点 $i$ 权值为 $f(a_i, mid + 1) - f(a_i, mid)$。
- 选了 $u$ 必须选 $v$。
- 让选了的点的权值和最小。

于是整体二分 + 最大流即可。时间复杂度为 $O(\text{Acceptable})$。

代码：
```cpp
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef long long ll;

typedef struct {
	int nxt;
	int end;
	ll dis;
} Edge;

int cnt;
int a[1007], u[1007], v[1007], head[1007], dis_cnt[1007], dis[1007], cur_edge[1007];
ll ans[1007];
bool vis[1007];
Edge edge[4007];
queue<int> q;

inline void init1(int n){
	cnt = 1;
	for (register int i = 0; i <= n; i++){
		head[i] = dis_cnt[i] = 0;
		dis[i] = 0x7fffffff;
		vis[i] = false;
	}
}

inline void init2(int n){
	for (register int i = 0; i <= n; i++){
		cur_edge[i] = head[i];
	}
}

inline ll calc(int x, ll k){
	return llabs(k - a[x]);
}

inline void add_edge(int start, int end, ll dis){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].end = end;
	edge[cnt].dis = dis;
}

inline void bfs(int start){
	dis[start] = 0;
	q.push(start);
	while (!q.empty()){
		int cur = q.front(), dis_i = dis[cur] + 1;
		q.pop();
		dis_cnt[dis[cur]]++;
		for (register int i = head[cur]; i != 0; i = edge[i].nxt){
			int x = edge[i].end;
			if (dis[x] == 0x7fffffff){
				dis[x] = dis_i;
				q.push(x);
			}
		}
	}
}

ll dfs1(int u, ll flow, int start, int end, int n){
	if (u == end) return flow;
	ll ans = 0;
	for (register int i = cur_edge[u]; i != 0; i = edge[i].nxt){
		cur_edge[u] = i;
		if (edge[i].dis != 0){
			int x = edge[i].end;
			if (dis[u] == dis[x] + 1){
				ll t = dfs1(x, min(flow - ans, edge[i].dis), start, end, n);
				edge[i].dis -= t;
				edge[i ^ 1].dis += t;
				ans += t;
				if (ans == flow) return ans;
			}
		}
	}
	cur_edge[u] = head[u];
	if (--dis_cnt[dis[u]] == 0) dis[start] = n;
	dis_cnt[++dis[u]]++;
	return ans;
}

inline ll isap(int start, int end, int n){
	ll ans = 0;
	bfs(end);
	while (dis[start] < n) ans += dfs1(start, 0x7fffffffffffffffll, start, end, n);
	return ans;
}

void dfs2(int u){
	vis[u] = true;
	for (register int i = head[u]; i != 0; i = edge[i].nxt){
		if (edge[i].dis != 0){
			int x = edge[i].end;
			if (!vis[x]) dfs2(x);
		}
	}
}

void solve(int n, int m, ll l, ll r, vector<int> vec){
	if (vec.empty()) return;
	int size = vec.size();
	if (l == r){
		for (register int i = 0; i < size; i++){
			ans[vec[i]] = l;
		}
		return;
	}
	int end = n + 1;
	ll mid = (l + r) >> 1;
	vector<int> v1, v2;
	init1(end);
	for (register int i = 0; i < size; i++){
		ll val = calc(vec[i], mid + 1) - calc(vec[i], mid);
		if (val > 0){
			add_edge(0, vec[i], val);
			add_edge(vec[i], 0, 0);
		} else if (val < 0){
			add_edge(vec[i], end, -val);
			add_edge(end, vec[i], 0);
		}
	}
	for (register int i = 1; i <= m; i++){
		add_edge(v[i], u[i], 0x7fffffffffffffffll);
		add_edge(u[i], v[i], 0);
	}
	init2(end);
	isap(0, end, end + 1);
	dfs2(0);
	for (register int i = 0; i < size; i++){
		if (vis[vec[i]]){
			v1.push_back(vec[i]);
		} else {
			v2.push_back(vec[i]);
		}
	}
	solve(n, m, l, mid, v1);
	solve(n, m, mid + 1, r, v2);
}

int main(){
	int n, m;
	vector<int> vec;
	cin >> n >> m;
	for (register int i = 1; i <= n; i++){
		cin >> a[i];
		vec.push_back(i);
	}
	for (register int i = 1; i <= m; i++){
		cin >> u[i] >> v[i];
	}
	solve(n, m, -1e15, 1e15, vec);
	for (register int i = 1; i <= n; i++){
		cout << ans[i] << " ";
	}
	return 0;
}
```

---

## 作者：IdnadRev (赞：0)

板子题，为啥没人写题解啊。

## 题意

有 $n$ 只驯鹿，每只驯鹿有一个得分 $a_i$。给定一个关系图，$a$ 向 $b$ 连边等价于 $a$ 最后的得分要比 $b$ 小，你可以进行若干次操作，每次给一只驯鹿的得分加减一，求满足需求的最小操作次数。

$2\leqslant n\leqslant 1000,1\leqslant m\leqslant 1000,1\leqslant a_i\leqslant 10^9$

## 分析

保序回归。 

我们对所有驯鹿的得分整体二分，不妨设我们目前确定了点集 $S$ 的得分在 $[l,r]$ 内，考虑怎么判断哪些点得分大于 $mid$。

根据论文中的结论可以知道最后的方案中大于 $mid$ 的点等于点权在 $[mid,mid+1]$ 内跑出的方案中大于 $mid$ 的点。

转化成只有两种点权取值，这是经典的最大闭合子图模型，我们跑一边网络流即可求出方案。

时间复杂度 $O(n^2m\log n)$。

## 代码
```
#include<stdio.h>
#include<queue>
#include<algorithm>
#include<string.h>
#define int long long
#define inf 10000000000000000
using namespace std;
const int maxn=1005,maxm=6005;
int n,m,s,t,e=1,flg,ans;
int start[maxn],to[maxm],then[maxm],limit[maxm],dep[maxn],vis[maxn],a[maxn],xx[maxn],yy[maxn],id[maxn],b[maxn],g[maxn][maxn],d[maxn];
queue<int>q;
inline void add(int x,int y,int z) {
	then[++e]=start[x],start[x]=e,to[e]=y,limit[e]=z;
}
inline void addedge(int x,int y,int z) {
	add(x,y,z),add(y,x,0);
}
inline int cmp(int a,int b) {
	return d[a]<d[b];
}
int bfs(int s,int t) {
	for(int i=1; i<=t; i++)
		dep[i]=inf,vis[i]=0;
	dep[s]=0,vis[s]=1,q.push(s);
	while(!q.empty()) {
		int x=q.front();
		vis[x]=0,q.pop();
		for(int i=start[x]; i; i=then[i]) {
			int y=to[i];
			if(limit[i]&&dep[y]>=dep[x]+1) {
				dep[y]=dep[x]+1;
				if(vis[y]==0)
					vis[y]=1,q.push(y);
			}
		}
	}
	return dep[t]!=inf;
}
int dfs(int x,int flw,int t) {
	if(x==t) {
		flg=1,ans+=flw;
		return flw;
	}
	int rest=flw;
	for(int i=start[x]; i; i=then[i]) {
		int y=to[i];
		if(limit[i]&&dep[y]==dep[x]+1) {
			int newflw=dfs(y,min(limit[i],rest),t);
			if(newflw) {
				rest-=newflw,limit[i]-=newflw,limit[i^1]+=newflw;
				if(rest==0)
					break;
			} else dep[y]=0;
		}
	}
	return flw-rest;
}
int Dinic(int s,int t) {
	ans=0;
	while(bfs(s,t))
		for(flg=1; flg;)
			flg=0,dfs(s,inf,t);
	return ans;
}
void solve(int l,int r,int L,int R) {
	if(L>R)
		return ;
	if(l==r) {
		for(int i=L; i<=R; i++)
			b[id[i]]=l;
		return ;
	}
	int mid=(l+r)>>1;
	e=1,memset(start,0,sizeof(start));
	for(int i=L; i<=R; i++)
		for(int j=L; j<=R; j++)
			if(g[id[i]][id[j]])
				addedge(i,j,inf);
	for(int i=L; i<=R; i++) {
		int p=abs(a[id[i]]-mid-1),q=abs(a[id[i]]-mid);
		if(p>=q)
			addedge(s,i,p-q);
		else addedge(i,t,q-p);
	}
	Dinic(s,t);
	for(int i=L; i<=R; i++)
		d[id[i]]=dep[i];
	sort(id+L,id+1+R,cmp);
	int pos=R;
	for(int i=L; i<=R; i++)
		if(d[id[i]]==inf) {
			pos=i-1;
			break;
		}
	solve(l,mid,L,pos),solve(mid+1,r,pos+1,R);
}
signed main() {
	scanf("%lld%lld",&n,&m),s=n+1,t=s+1;
	for(int i=1; i<=n; i++)
		scanf("%lld",&a[i]),id[i]=i;
	for(int i=1,x,y; i<=m; i++)
		scanf("%lld%lld",&x,&y),g[y][x]=1;
	solve(-1e15,1e15,1,n);
	for(int i=1; i<=n; i++)
		printf("%lld%c",b[i],i==n? '\n':' ');
	return 0;
}
```

---

