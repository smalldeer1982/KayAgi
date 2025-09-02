# [ABC375F] Road Blocked

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc375/tasks/abc375_f

AtCoder国には $ 1 $ から $ N $ の番号がついた $ N $ 個の都市と、$ 1 $ から $ M $ の番号がついた $ M $ 本の道路があります。  
 道路 $ i $ は都市 $ A_i $ と都市 $ B_i $ を双方向に結び長さは $ C_i $ です。

$ Q $ 個のクエリが与えられるので順に処理してください。クエリは以下の $ 2 $ 種類のどちらかです。

- `1 i`：道路 $ i $ が通行止めとなる。
- `2 x y`：通行止めでない道路のみを通るときの都市 $ x $ から都市 $ y $ への最短距離を出力する。都市 $ x $ から都市 $ y $ に到達できないときは代わりに `-1` を出力する。
 
なお、$ 1 $ 種類目のクエリはテストケースごとに $ 300 $ 回以下であることが保証されます。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 300 $
- $ 0\ \leq\ M\ \leq\ \frac{N(N-1)}{2} $
- $ 1\leq\ A_i\ <\ B_i\ \leq\ N $
- $ (A_i,B_i) $ は相異なる
- $ 1\ \leq\ C_i\ \leq\ 10^9 $
- $ 1\ \leq\ Q\ \leq\ 2\times\ 10^5 $
- $ 1 $ 種類目のクエリにおいて、$ 1\leq\ i\ \leq\ M $
- $ 1 $ 種類目のクエリにおいて与えられる道路は、その時点で通行止めでない
- $ 1 $ 種類目のクエリは $ 300 $ 回以下である
- $ 2 $ 種類目のクエリにおいて、$ 1\leq\ x\ <\ y\ \leq\ N $
- 入力は全て整数である
 
### Sample Explanation 1

\- $ 1 $ 番目のクエリでは、都市 $ 1 $ から都市 $ 3 $ への最短距離である $ 10 $ を出力します。 - $ 2 $ 番目のクエリにより、道路 $ 2 $ が通行止めとなりました。 - $ 3 $ 番目のクエリでは、都市 $ 1 $ から都市 $ 3 $ への最短距離である $ 11 $ を出力します。 - $ 4 $ 番目のクエリにより、道路 $ 1 $ が通行止めとなりました。 - $ 5 $ 番目のクエリでは、都市 $ 1 $ から都市 $ 3 $ には到達できないので、`-1` を出力します。

## 样例 #1

### 输入

```
3 3 5
1 2 5
1 3 10
2 3 6
2 1 3
1 2
2 1 3
1 1
2 1 3```

### 输出

```
10
11
-1```

## 样例 #2

### 输入

```
4 6 6
2 3 1
2 4 1
3 4 1
1 2 1
1 3 1
1 4 1
1 4
1 5
1 6
2 1 2
2 1 3
2 1 4```

### 输出

```
-1
-1
-1```

# 题解

## 作者：cjh20090318 (赞：6)

非常模板的最短路题。

## 题意

$N$ 个点 $M$ 条边的无向图，第 $i$ 条边连接 $A_i$ 和 $B_i$，长度为 $C_i$。

你需要依次执行 $Q$ 次操作：

- `1 i`：断开第 $i$ 条边。
- `2 x y` 查询 $x$ 到 $y$ 的最短路径长度，如果无法到达输出 $-1$。

保证无重边自环，第 $1$ 种操作不超过 $300$ 次。

## 分析

断开边不好做，可以离线下来逆序处理操作，这样就从断边变成了加边。

查询的是全源最短路，先使用 Floyd 求出任意两点间的最短路径长度。

在加边 $(u,v)$ 的时候，枚举两个点 $i,j$，最短路径有 $3$ 种情况：

- $i,j$ 的最短路径不经过这条边。
- 从 $i$ 走到 $u$，经过 $(u,v)$ 边后再从 $v$ 走到 $j$。
- 从 $i$ 走到 $v$，经过 $(v,u)$ 边后再从 $u$ 走到 $j$。

因为第一种操作的数量不超过 $300$ 次，所以可以直接枚举两个端点取以上三种情况的最小值。

设 $Q_1$ 为第 $1$ 种操作次数，时间复杂度 $O(n^3 + Q_1n^2)$。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
int n,m,q;
struct Edge{
	int u,v,w;
}e[300*300];
bool ct[300*300];//标记哪些边被砍掉了。
LL d[305][305];
struct QUE{
	int op,x,y;
}Q[200005];
LL ans[200005];
void add(const int u,const int v,const LL&w){d[u][v]=min(d[u][v],w);}
int main(){
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=m;i++) scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
	for(int i=1;i<=q;i++){
		scanf("%d%d",&Q[i].op,&Q[i].x);
		if(Q[i].op==2) scanf("%d",&Q[i].y);
		else ct[Q[i].x]=1;//标记该边被断开。
	}
	memset(d,0x3f,sizeof d);//赋值无穷大。
	for(int i=1;i<=n;i++) d[i][i]=0;
	for(int i=1;i<=m;i++)if(!ct[i])
		add(e[i].u,e[i].v,e[i].w),add(e[i].v,e[i].u,e[i].w);/添加未被断开的边。
	for(int k=1;k<=n;k++)for(int i=1;i<=n;i++)for(int j=1;j<=n;j++) d[i][j]=min(d[i][j],d[i][k]+d[k][j]);//Floyd 求最短路，注意转移顺序 k,i,j。
	for(int _=q,i;_>0;--_){//从后往前逆序处理操作。
		if(Q[_].op==1){
			i=Q[_].x,add(e[i].u,e[i].v,e[i].w),add(e[i].v,e[i].u,e[i].w);
			for(int u=1;u<=n;u++)for(int v=1;v<=n;v++) d[u][v]=min({d[u][v],d[u][e[i].u]+e[i].w+d[e[i].v][v],d[u][e[i].v]+e[i].w+d[e[i].u][v]});//枚举端点，获得三种情况的最小值。
		}
		else ans[_]=d[Q[_].x][Q[_].y];//获得查询答案。
	}
	for(int _=1;_<=q;_++)if(Q[_].op==2) printf("%lld\n",ans[_]>=0x3f3f3f3f3f3f3f3fll?-1:ans[_]);//如果距离为无穷大即无法到达，输出 -1。
	return 0;
}
```

---

## 作者：xixisuper (赞：1)

# AT_abc375_f [ABC375F] Road Blocked 题解

鉴定为典题，参考[P1119 灾后重建](https://www.luogu.com.cn/problem/P1119)。

## 思路

注意到删边操作不好维护，所以我们考虑把所有操作反着进行，将删边操作转化为加边操作。然后就是经典的 floyd 做法了。

详细的说，我们在所有询问开始之前先跑一次 floyd，然后对于每个加边操作，只需要钦定新路径经过这条加的边进行转移即可，时间复杂度可以视为 $O(n^3)$，可以通过此题。

## 代码

```cpp
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const ll INF=2147483647;
const ll M=2e5+10;
const ll N=305;
struct node{ll u,v,w;}E[M];
struct ASK{ll id,u,v,ans;}ask[M];
bool vis[M];
ll n,m,Q,f[N][N];
int main(){
	cin>>n>>m>>Q;
	for(ll i=1;i<=m;i++){
		vis[i]=1;
		cin>>E[i].u>>E[i].v>>E[i].w;
	}
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=n;j++){
			if(i==j) f[i][j]=0;
			else f[i][j]=INF*INF;
		}
	}
	for(ll i=1;i<=Q;i++){
		cin>>ask[i].id;
		if(ask[i].id==1){
			cin>>ask[i].u;
			vis[ask[i].u]=0;
		}
		else cin>>ask[i].u>>ask[i].v;
	}
	for(ll i=1;i<=m;i++){
		if(!vis[i]) continue;
		f[E[i].u][E[i].v]=min(f[E[i].u][E[i].v],E[i].w);
		f[E[i].v][E[i].u]=min(f[E[i].v][E[i].u],E[i].w);
	}
	for(ll k=1;k<=n;k++){
		for(ll i=1;i<=n;i++){
			for(ll j=1;j<=n;j++){
				f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
			}
		}
	}
	for(ll i=Q;i>=1;i--){
		if(ask[i].id==1){
			ll II=ask[i].u;
			f[E[II].u][E[II].v]=min(f[E[II].u][E[II].v],E[II].w);
			f[E[II].v][E[II].u]=min(f[E[II].v][E[II].u],E[II].w);
			for(ll i=1;i<=n;i++){
				for(ll j=1;j<=n;j++){
					f[i][j]=min(f[i][j],f[i][E[II].u]+f[E[II].u][E[II].v]+f[E[II].v][j]);
					f[i][j]=min(f[i][j],f[i][E[II].v]+f[E[II].v][E[II].u]+f[E[II].u][j]);
				}
			}
		}
		else{
			if(f[ask[i].u][ask[i].v]==INF*INF) ask[i].ans=-1;
			else ask[i].ans=f[ask[i].u][ask[i].v];
		}
	}
	for(ll i=1;i<=Q;i++){
		if(ask[i].id==1) continue;
		else cout<<ask[i].ans<<"\n";
	}
	return 0;
}
```

---

## 作者：WhxStar2024 (赞：1)

## 本题思路：
这道题是一道 Floyd 的好题，我们知道他删边最多就只有三百次，那么我们就可以倒序处理，变删边为加边，然后一条一条处理。

我们就先给没有删的边去跑一个 Floyd 求两点之间的最短路，然后对于每一个加边，我们可以枚举两个点，然后两个点的距离就取为原来的距离与通过这条边的距离的最小值（分别到这条路的两个端点的距离加路长），查询就直接查即可。
## 本题代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct f{
	int l,r,k,id;
}a[4000005],q1[200005];
int dp[305][305];
bool cmp(f x,f y){return x.id>y.id;}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
	int n,m,q;cin>>n>>m>>q;
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) dp[i][j]=1e18,dp[i][i]=0;
	for(int i=1;i<=m;i++){cin>>a[i].l>>a[i].r>>a[i].k;a[i].id=q+1;}
	for(int i=1;i<=q;i++){
		int op,x,y;
		cin>>op>>x;
		if(op==2) cin>>y,q1[i].l=x,q1[i].r=y;
		else a[x].id=i;
	}
	sort(a+1,a+1+m,cmp);
	int l=1;
	while(a[l].id==q+1){
		dp[a[l].l][a[l].r]=min(dp[a[l].l][a[l].r],a[l].k);swap(a[l].l,a[l].r);
		dp[a[l].l][a[l].r]=min(dp[a[l].l][a[l].r],a[l].k);
		l++;
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j]);
			}
		}
	}
	for(int i=q;i>=1;i--){
		while(a[l].id==i){
			dp[a[l].l][a[l].r]=min(dp[a[l].l][a[l].r],a[l].k);swap(a[l].l,a[l].r);
			dp[a[l].l][a[l].r]=min(dp[a[l].l][a[l].r],a[l].k);
			for(int j=1;j<=n;j++){
				for(int k=1;k<=n;k++){
					dp[j][k]=min(dp[j][k],dp[j][a[l].l]+a[l].k+dp[a[l].r][k]);
					dp[j][k]=min(dp[j][k],dp[j][a[l].r]+a[l].k+dp[a[l].l][k]);
				}
			}
			l++;
		}
		if(q1[i].l!=0) q1[i].id=dp[q1[i].l][q1[i].r];
	}
	for(int i=1;i<=q;i++) if(q1[i].id!=0)if(q1[i].id!=1e18)cout<<q1[i].id<<'\n';
	else cout<<-1<<'\n';
	return 0;
}
```

---

## 作者：zengziqvan (赞：1)

首先直接删边肯定不好搞。

考虑时光倒流，倒着处理询问，问题转化成加边。

由于 $n\le 300$，直接全源最短路，一次查询 $\operatorname{O}(1)$。

考虑加边操作，即使加边操作个数只有 $\operatorname{O}(n)$ 级别，但每次加边暴力跑全源最短路总时间复杂度可以达到恐怖的 $\operatorname{O}(n^4)/\operatorname{O}(n^2\times m\log m)$ 显然不太行。

发现每次加边只会影响经过这条边的最短路。

设加的边端点分别为 $x,y$，边权为 $w$，则被更新的最短路一定经过 $x,y$ 至少一个点。

直接枚举两个被更新的点 $u,v$ 更新最短路即可。

从 $x,y$ 分别再次跑 Dijkstra，新的最短路即为 $\operatorname{dis}(u,v)=\min(\operatorname{dis}(u,v),\operatorname{dis}(u,x)+\operatorname{dis}(v,x),\operatorname{dis}(u,y)+\operatorname{dis}(v,y))$。

或者使用 Floyd，答案为 $dis_{u,v}=\min(dis_{u,v},dis_{u,x}+dis_{v,y}+w,dis_{u,y}+dis_{v,x}+w)$。

时间复杂度 $\operatorname{O}(n\times m\log m+q)/\operatorname{O}(n^3+q)$。

~~强烈推荐写 Floyd，代码短效率高，千万不要学我。~~

code：

Dijkstra 代码

```c++
const int N=2e5+10;
int n,m,q,tot,hed[310],vs[310],A[N],B[N],C[N],vis[N];
LL dis[310][310],f[310][310],ans[N];
struct Ak {
	int op,x,y;
}a[N];
struct edge {
	int nxt,to,val;
}e[N<<1];
void adde(int u,int v,int w) {
	e[++tot]={hed[u],v,w};
	hed[u]=tot;
}
priority_queue<pair<LL,int> >Q;
void bfs(int t) {
	while(Q.size()) Q.pop();
	FOR(i,1,n) dis[t][i]=1e18,vs[i]=0;
	dis[t][t]=0;
	Q.push({-dis[t][t],t});
	while(Q.size()) {
		int x=Q.top().se;Q.pop();
		if(vs[x]) continue;
		vs[x]=1;
		for(int i=hed[x];i;i=e[i].nxt) {
			int y=e[i].to;
			if(dis[t][y]>dis[t][x]+e[i].val) {
				dis[t][y]=dis[t][x]+e[i].val;
				Q.push({-dis[t][y],y});
			}
		}
	}
}
main() {
	cin>>n>>m>>q;
	FOR(i,1,m) A[i]=read(),B[i]=read(),C[i]=read();
	FOR(i,1,q) {
		a[i].op=read();
		if(a[i].op==1) {
			a[i].x=read();
			vis[a[i].x]=1;
		} else {
			a[i].x=read(),a[i].y=read();
		}
	}
	FOR(i,1,n) FOR(j,1,n) dis[i][j]=1e18;
	FOR(i,1,m) if(!vis[i]) {
		adde(A[i],B[i],C[i]);
		adde(B[i],A[i],C[i]);
	}
	FOR(i,1,n) bfs(i);
	ROF(i,q,1) {
		if(a[i].op==2) {
			ans[i]=dis[a[i].x][a[i].y];
			if(ans[i]==1e18) ans[i]=-1;
		} else {
			int x=a[i].x;
			adde(A[x],B[x],C[x]);
			adde(B[x],A[x],C[x]);
			bfs(A[x]);bfs(B[x]);
			FOR(i,1,n) FOR(j,1,n) cmin(dis[i][j],min(dis[A[x]][i]+dis[A[x]][j],dis[B[x]][i]+dis[B[x]][j]));
		}
	}
	FOR(i,1,q) if(a[i].op==2) cout<<ans[i]<<"\n";
	return 0;
}
```

---

## 作者：hjyowl (赞：1)

### 题目大意

给定一个无向带权图，每次有两种操作，一种是删除一条边，一种是查询两点之间的最短路。

### 思路

首先，删边是非常不好处理的，我们可以考虑这倒着处理，也就是把操作离线一下。

就按照修改完后的图不断去加边，按照最初的多源最短路数组，加一条边的话，只需要 $\Theta(n^2)$ 的时间复杂度来更新，这样的话就可以把时间复杂度控制在 $\Theta(n^3)$，答案需要倒着输出。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long N = 510;
long long a[N][N];
long long d[N][N];
struct query{
	long long op,x,y;
};
long long c[N][N];
int x[100010],y[100010],z[100010];
map<pair<long long,long long>,long long>mp;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	long long n,m,q;
	cin >> n >> m >> q;
	memset(a,0x3f,sizeof a);const long long inf = a[0][0];
	for (long long i = 1; i <= m; i ++ ){
		cin >> x[i] >> y[i] >> z[i];
		a[x[i]][y[i]] = z[i];
		a[y[i]][x[i]] = z[i];
	}
	for (int i = 1; i <= n; i ++ ){
		for (int j = 1; j <= n; j ++ ){
			d[i][j] = a[i][j];
		}
	}
	vector<query>vec;
	long long T = 1;
	while (q -- ){
		long long op;
		cin >> op;
		if (op == 1){
			int i;
			cin >> i;
			a[x[i]][y[i]] = a[y[i]][x[i]] = inf;
			c[x[i]][y[i]] ++ ;
			c[y[i]][x[i]] ++ ;
			vec.push_back({op,x[i],y[i]});
			T ++ ;
			vec.push_back({op,y[i],x[i]});
			T ++ ;
		}
		else{
			long long x,y;
			cin >> x >> y;
			vec.push_back({op,x,y});
			T ++ ;
		}
	}
	for (int i = 1; i <= n; i ++ ){
		a[i][i] = d[i][i] = 0;
	}
	for (long long k = 1; k <= n; k ++ ){
		for (long long i = 1; i <= n; i ++ ){
			for (long long j = 1; j <= n; j ++ ){
				a[i][j] = min(a[i][j],a[i][k] + a[k][j]);
			}
		}
	}
	vector<long long>ans;
	for (long long i = vec.size() - 1; i >= 0; i -- ){
		if (vec[i].op == 1){
			if (c[vec[i].x][vec[i].y] == 1){
				c[vec[i].x][vec[i].y] = 0;
				for (long long ii = 1; ii <= n; ii ++ ){
					for (long long jj = 1; jj <= n; jj ++ ){
						a[ii][jj] = min(a[ii][jj],a[ii][vec[i].x] + d[vec[i].x][vec[i].y] + a[vec[i].y][jj]);
					}
				}
			}
			else{
				c[vec[i].x][vec[i].y] -- ;
			}
		}
		else{
			if (a[vec[i].x][vec[i].y] == a[0][0]){
				ans.push_back(-1);
				continue;
			}
			ans.push_back(a[vec[i].x][vec[i].y]);
		}
	}
	reverse(ans.begin(),ans.end());
	for (long long i = 0 ; i < ans.size(); i ++ ){
		cout << ans[i] << "\n";
	}
	return 0;
} 
```

---

## 作者：2023lpx (赞：0)

## 思路

~~通常，我们都不会用 Floyd 去跑最短路，因为它太慢了。~~

~~但这次 Floyd 它复活了。~~

在最短路问题中，将删边问题逆序变为增边问题是非常常见的。

我们回顾一下 Floyd 的原理：

每次选择一个中转点，尝试更新其他点对的最短路。

加边时，我们就可以以这两个点为中转点，尝试更新其他点对的最短路。

题目给出删边（加边）只有 $300$ 次，$n$ 也很小，所以能过。

倒序输出即可。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,s;
int to[3001][3001];
int lo[300*300][5];
int q;
int cz[2000001][4];
int ans[2000001];
signed main(){
	scanf("%lld%lld%lld",&n,&m,&q);
	int u,v,w;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			to[i][j]=1e18;
		}
	}
	for(int i=1;i<=m;i++){
		scanf("%lld%lld%lld",&u,&v,&w);
		to[u][v]=w;
		to[v][u]=w;
		lo[i][0]=u;
		lo[i][1]=v;
		lo[i][2]=w;
	}
	int op;
	int x,y;
	for(int i=1;i<=q;i++){
		scanf("%lld",&op);
		if(op==1){
			scanf("%lld",&x);
			cz[i][0]=op;
			cz[i][1]=x;
			to[lo[x][0]][lo[x][1]]=1e18;
			to[lo[x][1]][lo[x][0]]=1e18;
		}
		if(op==2){
			scanf("%lld%lld",&x,&y);
			cz[i][0]=op;
			cz[i][1]=x;
			cz[i][2]=y;
			
		}
	}
	for(int k=1;k<=n;k++) {
		for(int x=1;x<=n;x++) {
			for(int y=1;y<=n;y++){
				to[x][y]=min(to[x][y],to[x][k]+to[k][y]);
			}
		}
	}
	int cnt=0;
	for(int i=q;i>=1;i--){
		if(cz[i][0]==1){
			to[lo[cz[i][1]][0]][lo[cz[i][1]][1]]=min(to[lo[cz[i][1]][0]][lo[cz[i][1]][1]],lo[cz[i][1]][2]);
			to[lo[cz[i][1]][1]][lo[cz[i][1]][0]]=min(to[lo[cz[i][1]][1]][lo[cz[i][1]][0]],lo[cz[i][1]][2]);
			int k;
			k=lo[cz[i][1]][0];
			for(int x=1;x<=n;x++){
				for(int y=1;y<=n;y++){
					to[x][y]=min(to[x][y],to[x][k]+to[k][y]);
				}
			}
			k=lo[cz[i][1]][1];
			for(int x=1;x<=n;x++){
				for(int y=1;y<=n;y++){
					to[x][y]=min(to[x][y],to[x][k]+to[k][y]);
				}
			}
		}
		else{
			cnt++;
			ans[cnt]=to[cz[i][1]][cz[i][2]];
		}
	}
	for(int i=cnt;i>=1;i--){
		printf("%lld\n",ans[i]>=1e18?-1ll:ans[i]);
	}
	return 0;
}
```

---

## 作者：Binah_cyc (赞：0)

经典 trick 题，考验对 trick 的积累与运用

删边是不好维护的，我们考虑使用**时光倒流**将删边转化为加边。

具体实现方法如下：

- 我们首先读入所有询问，将询问中封锁的道路提前封锁好，从已经封锁完的图上跑全源最短路，然后从最后一个操作倒序处理所有询问。设 $x$ 到 $y$ 的最短距离为 $dis_{x,y}$。
- 如果该操作为查询操作，直接 $O(1)$ 的回答即可。
- 如果该操作为封锁操作，那么我们需要在当前的图中加入这一条边，因为在这个操作之前，我们都还没有将其封锁我们设它连接 $u,v$，长度为 $val$。
  
  我们 $O(n^2)$ 的暴力扫描每一个点对 $(x,y)$，那么，这两个点现在的最短路有三种可能性：
  
  1. 还是原来的最短路，此时的距离为 $dis_{x,y}$。
  2. 从 $x$ 走到 $u$，再经过这一条边走到 $v$，最后从 $v$ 走到 $y$，距离为 $dis_{x,u}+val+dis_{v,y}$。
  3. 从 $x$ 走到 $v$，再经过这一条边走到 $u$，最后从 $u$ 走到 $y$，距离为 $dis_{x,v}+val+dis_{u,y}$。
  三种情况取最小值即可。

这个做法看起来很暴力，实际上跑的飞快。因为我们只会有 $300$ 次删除操作，与 $n$ 同级。总的时间复杂度为 $O(n^3+Q)$。

代码：
```c
// Problem: F - Road Blocked
// Contest: AtCoder - Panasonic Programming Contest 2024（AtCoder Beginner Contest 375）
// URL: https://atcoder.jp/contests/abc375/tasks/abc375_f
// Memory Limit: 1024 MB
// Time Limit: 2500 ms
// Author: Binah_cyc

#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,q,ans[200005];
struct Node{int x,y,val;};
vector<Node> edge;
bool vis[90005];
struct Ques{int id,x,y;}x[200005];
int dis[305][305];

signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m>>q;
	edge.push_back(Node{11,45,14});//下标从1开始
	for(int i=1,x,y,z;i<=m;i++) cin>>x>>y>>z,edge.push_back(Node{x,y,z});
	for(int i=1;i<=q;i++)
	{
		cin>>x[i].id;
		if(x[i].id==1) cin>>x[i].x,vis[x[i].x]=1;//标记被删除的边
		else cin>>x[i].x>>x[i].y;
	}
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if(i!=j) dis[i][j]=1e16;
	for(int i=1;i<=m;i++) if(!vis[i]) dis[edge[i].x][edge[i].y]=dis[edge[i].y][edge[i].x]=edge[i].val;
	for(int k=1;k<=n;k++) for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);//Floyd跑最短路
	for(int i=q;i>=1;i--)
	{
		if(x[i].id==1)//加边
		{
			if(dis[edge[x[i].x].x][edge[x[i].x].y]>edge[x[i].x].val)
			{
				dis[edge[x[i].x].x][edge[x[i].x].y]=edge[x[i].x].val;
				for(int t=1;t<=n;t++)
					for(int y=1;y<=n;y++)
					//分讨
						dis[t][y]=min({dis[t][y],dis[t][edge[x[i].x].x]+dis[edge[x[i].x].y][y]+edge[x[i].x].val,dis[t][edge[x[i].x].y]+dis[edge[x[i].x].x][y]+edge[x[i].x].val});
			}
		}
		else ans[i]=dis[x[i].x][x[i].y];
	}
	for(int i=1;i<=q;i++)
	{
		if(x[i].id==2)
		{
			if(ans[i]<=2000000000000) cout<<ans[i]<<'\n';
			else cout<<-1<<'\n';//判无法到达
		}
	}
	return 0;
}
```

---

## 作者：wly09 (赞：0)

> 给一张无向图，每次两种询问：
>
> + 删一条边；
> + 询问两点间最短路。

注意到数据范围，参考[灾后重建](https://www.luogu.com.cn/problem/P1119)，鉴定为 Floyd 典题。

将询问倒序考虑，去边变成加边。最初做一遍 Floyd（不会去看[模板](https://www.luogu.com.cn/problem/B3647)），复杂度 $O(n^3)$。

每次加边，枚举起点、终点，钦定必须经过加的边，更新答案即可，注意加的边是无向边，正反都要考虑。单次复杂度 $O(n^2)$，但是只需做 $300$ 次。

询问去查邻接矩阵，单次是 $O(1)$ 的。

[Code](https://atcoder.jp/contests/abc375/submissions/58720176)

---

## 作者：卡卡卡卡卡卡 (赞：0)

## 题解
发现 $N\leq 300$，直接 ``floyd`` 跑最短路。

删边不好弄就倒着加边，则路径答案的变化一定与两个端点 $A_i$,$B_i$ 有关，于是便枚举形如 $x \to A_i \to B_i \to y$ 的路径，设 $dis_{i,j}$ 是从 $i$ 到 $j$ 的最短路，则：
$$dis_{x,y}=\min (dis_{x,A_i}+w_{A_i,B_i}+dis_{B_i,y})$$
时间复杂度：$\mathcal O(N^2)$

总时间复杂度：$\mathcal O(N^3+TN^2+Q)$
## code：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long op[300005],l[300005],r[300005];
long long n,m,q,a[300005],b[300005],vis[300005],c[300005],ans[300005],dis[505][505];
signed main()
{
	cin>>n>>m>>q;
	memset(dis,0x3f,sizeof(dis));
	for(long long i=1;i<=n;i++) dis[i][i]=0;
	for(long long i=1;i<=m;i++) cin>>a[i]>>b[i]>>c[i];
	for(long long i=1;i<=q;i++) 
	{
		cin>>op[i]>>l[i];
		if(op[i]==2) cin>>r[i];
		else vis[l[i]]=1;
	}
	for(long long i=1;i<=m;i++) 
	{
		if(vis[i]) continue;
		dis[a[i]][b[i]]=min(dis[a[i]][b[i]],c[i]);
		dis[b[i]][a[i]]=min(dis[b[i]][a[i]],c[i]);
	}
	for (long long k=1;k<=n;k++)
		for(long long i=1;i<=n;i++)
			for(long long j=1;j<=n;j++)
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
	for(long long i=q;i>=1;i--) 
	{
		if (op[i]==1) 
		{
			for(long long x=1;x<=n;x++)
				for(long long y=1;y<=n;y++) 
				{
					dis[x][y]=min(dis[x][y],dis[x][a[l[i]]]+dis[b[l[i]]][y]+c[l[i]]);
					dis[x][y]=min(dis[x][y],dis[x][b[l[i]]]+dis[a[l[i]]][y]+c[l[i]]);
				}
		} 
		else ans[i]=dis[l[i]][r[i]];
	}
	for(long long i=1;i<=q;i++)
	{
		if(op[i]==2) 
		{
			if (ans[i]>=1e16) cout<<"-1\n";
			else cout<<ans[i]<<"\n";
		}
	}
}
```

---

