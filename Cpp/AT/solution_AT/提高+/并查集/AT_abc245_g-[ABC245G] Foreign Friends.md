# [ABC245G] Foreign Friends

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc245/tasks/abc245_g

$ N $ 人の人と $ K $ 個の国があり、それぞれ 人 $ 1 $, 人 $ 2 $, $ \ldots $, 人 $ N $ および国 $ 1 $, 国 $ 2 $, $ \ldots $, 国 $ K $ と番号が付いています。 それぞれの人はちょうど $ 1 $ つの国に属しており、人 $ i $ は国 $ A_i $ に属しています。 また、$ L $ 人の人気者がおり、具体的には人 $ B_1 $, 人 $ B_2 $, $ \ldots $, 人 $ B_L $ が人気者です。 最初、$ N $ 人のうちどの $ 2 $ 人も友達ではありません。

神様である高橋君は、$ M $ 個の $ 2 $ 人組のペアについて、コストを支払うことで互いに友達にすることができます。 具体的には $ 1\leq\ i\leq\ M $ について、コスト $ C_i $ を支払うことで人 $ U_i $ と人 $ V_i $ を互いに友達にすることができます。

ここで、各 $ 1\leq\ i\leq\ N $ について、次の問題を解いてください。

> 高橋君は、人 $ i $ を、人 $ i $ の属する国とは異なる国に属する人気者と間接的に友達にすることは可能か？ 可能ならば、それを達成するのに必要なコストの総和の最小値を求めよ。 ただし、人 $ s $ と人 $ t $ が間接的に友達であるとは、ある非負整数 $ n $ と人の列 $ (u_0,\ u_1,\ \ldots\ ,\ u_n) $ が存在し, $ u_0=s $, $ u_n=t $ かつ $ 0\leq\ i\ <\ n $ について、人 $ u_i $ と 人 $ u_{i+1} $ が互いに友達であることをさす。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 10^5 $
- $ 1\ \leq\ K\ \leq\ 10^5 $
- $ 1\ \leq\ L\ \leq\ N $
- $ 1\ \leq\ A_i\ \leq\ K $
- $ 1\ \leq\ B_1\ <\ B_2\ <\ \cdots\ <\ B_L\leq\ N $
- $ 1\leq\ C_i\leq\ 10^9 $
- $ 1\leq\ U_i\ <\ V_i\leq\ N $
- $ i\ \neq\ j $ ならば $ (U_i,\ V_i)\neq\ (U_j,V_j) $
- 入力は全て整数である。

### Sample Explanation 1

人 $ 1 $, 人 $ 2 $, 人 $ 3 $, 人 $ 4 $ はそれぞれ国 $ 1 $, 国 $ 1 $, 国 $ 2 $, 国 $ 2 $ に属しており、人気者は人 $ 2 $, 人 $ 3 $ の $ 2 $ 名です。このとき、 - 人 $ 1 $ と異なる国に属する人気者は人 $ 3 $ のみです。人 $ 1 $ と 人 $ 3 $ を間接的に友達にするには、それぞれコスト $ 15,30 $ を払って人 $ 1 $ と人 $ 2 $, 人 $ 2 $ と人 $ 3 $ を友達にした時がかかるコストが最小で、このとき $ 15+30=45 $ となります。 - 人 $ 2 $ と異なる国に属する人気者は人 $ 3 $ のみです。コスト $ 30 $ を払って人 $ 2 $ と人 $ 3 $ を友達にした時が最小となります。 - 人 $ 3 $ と異なる国に属する人気者は人 $ 2 $ のみです。コスト $ 30 $ を払って人 $ 2 $ と人 $ 3 $ を友達にした時が最小となります。 - 人 $ 4 $ と異なる国に属する人気者は人 $ 2 $ のみです。人 $ 4 $ と 人 $ 2 $ を間接的に友達にするには、それぞれコスト $ 15,10 $ を払って人 $ 1 $ と人 $ 2 $, 人 $ 1 $ と人 $ 4 $ を友達にした時がかかるコストが最小で、このとき $ 15+10=25 $ となります。

### Sample Explanation 2

人 $ 1 $ にとって自身は間接的な友達といえますが、異なる国に属していないため、 「異なる国に属する人気者」の条件をみたす相手はいないことに注意してください。

## 样例 #1

### 输入

```
4 4 2 2
1 1 2 2
2 3
1 2 15
2 3 30
3 4 40
1 4 10```

### 输出

```
45 30 30 25```

## 样例 #2

### 输入

```
3 1 3 1
1 2 3
1
1 2 1000000000```

### 输出

```
-1 1000000000 -1```

# 题解

## 作者：tanyulin (赞：7)

似乎是经典套路？
先不考虑颜色限制，那么就直接把 $l$ 个关键点当作起点跑多源最短路就行了。

现在考虑颜色限制，有一种暴力的想法是枚举所有颜色，只把这种颜色的点当作起点，然后跑`dijkstra`，然后更新颜色不为这个的终点。
发现这样终点就被更新了很多次，考虑优化。

考虑枚举颜色的每个二进制位，把所有特殊点这一位上颜色是 $1$ 的加入起点，跑最短路，更新所有终点中这一位上颜色是 $0$ 的终点，然后倒过来，把所有特殊点这一位上颜色是 $0$ 的加入起点，跑最短路，更新所有终点中这一位上颜色是 $1$ 的终点。

由于两个颜色不同一定至少有一个二进制位不同，因此上述算法可以保证所有终点都被颜色不同的起点更新到。
复杂度 $\mathcal{O}(m\log n\log k)$。

---

## 作者：DegChuZm (赞：6)

### 鲜花
vp 的时候看了，觉得是神仙图论，没做。

结果订正的时候发现跟某道最近才做过的 [题](https://www.luogu.com.cn/problem/P5304) 很像，遂秒之。

四舍五入订正了道原。

滚回来写 tj 了。

### sol
先不考虑特殊点，假设所有点都是特殊点该如何去做。

有一个非常暴力的做法，直接全源最短路。

那怎么优化呢。

枚举颜色的二进制位，对于第 $i$ 位为 $1$ 的放到起点点集，建立一个超级源点 $S$，从 $S$ 向起点点集里的点都连一条长度为 $0$ 的边，然后从 $S$ 开始跑最短路，更新不在起点点集里的点的答案。

$i$ 位为 $0$ 的同理。

对于特殊点的处理也很好做，就是在起点点集里的都只能是特殊点就一定保证是合法解了。

这是 $\log^2$ 的。

PS: 请注意扫完 $i$ 位为 $1$ 时再扫一遍为 $0$ 的，笔者就这样寄了一发

### code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,t,k,l,head[200001],col[200001],x,y,cnt,b[200001],vis[200001],st[200001],ed[200001],dis[2000001],ans[200001],z,S,D;
struct dcz{
	int nex,to,val;
}a[40000001];
void add(int x,int y,int z){
	a[++cnt].nex=head[x];
	a[cnt].to=y;
	a[cnt].val=z;
	head[x]=cnt;
}
struct sbdcz{
	int u,d;
	bool operator<(const sbdcz & jjrt)const{
		return jjrt.d<d;
	}
};
priority_queue<sbdcz> q;
void dij(int o){
	memset(dis,0x3f,sizeof dis);
	dis[o]=0;
	q.push({o,0});
	while(q.size()){
		sbdcz xx=q.top();
		q.pop();
		int u=xx.u;
		int d=xx.d;
		if(dis[u]!=d) continue;
		for(int i=head[u];i;i=a[i].nex){
			int v=a[i].to,w=a[i].val;
			if(dis[v]>dis[u]+w) dis[v]=dis[u]+w,q.push({v,dis[v]});
		}
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m>>k>>l;
	cnt=0;
	for(int i=1;i<=n;i++){
		cin>>col[i];
	}
	for(int i=1;i<=l;i++){
		cin>>x;
		vis[x]=1;
	}
	for(int i=1;i<=m;i++){
		cin>>x>>y>>z;
		add(x,y,z);
		add(y,x,z);
	}
	for(int i=1;i<=n;i++){
		ans[i]=0x3f3f3f3f3f3f3f3f;
	}
	S=n+1;
	for(int i=0;i<=20;i++){
		int tot=0,ptt=0;
		for(int j=1;j<=n;j++){
			if(vis[j]&&(col[j]>>i&1)) st[++ptt]=j;
			else if(!(col[j]>>i&1)) ed[++tot]=j;
		}
		for(int j=1;j<=ptt;j++){
			add(S,st[j],0);
		}
		dij(S);
		for(int j=1;j<=tot;j++){
			ans[ed[j]]=min(ans[ed[j]],dis[ed[j]]);
		}
		S++;
		tot=0,ptt=0;
		for(int j=1;j<=n;j++){
			if(vis[j]&&(!(col[j]>>i&1))) st[++ptt]=j;
			else if((col[j]>>i&1)) ed[++tot]=j;
		}
		for(int j=1;j<=ptt;j++){
			add(S,st[j],0);
		}
		dij(S);
		for(int j=1;j<=tot;j++){
			ans[ed[j]]=min(ans[ed[j]],dis[ed[j]]);
		}
		S++;
	}
	for(int i=1;i<=n;i++){
		if(ans[i]==0x3f3f3f3f3f3f3f3f) cout<<-1<<' ';
		else cout<<ans[i]<<' ';
	}
	return 0;
}
```

---

## 作者：Moyou (赞：3)

# [ABC245G] Foreign Friends 题解

## 想法

考虑所有颜色相同的弱化版。

这种情况下，只需要把所有特殊点都推入队列之后跑多源 Dijkstra 即可。

## 思路

正解与上述做法大致相同。

如果有颜色限制，那么可以考虑这个神仙思路：

把所有特殊点的颜色用二进制表示，对于每一位，这一位是 $0$ 的特殊点作为源点跑 Dijkstra，只更新这一位是 $1$ 的点，对于这一位是 $1$ 的特殊点同理，这样就对每一个特殊点统计了它与这一位颜色不同的点的距离。

这样一定可以迭代找到最短的距离，因为如果存在一个这样的路径，那么当前点和路径端点的颜色的二进制表示一定有一位不相同，因此它们的距离已经被统计过了，所以上述算法一定能够找到最优解。

时间复杂度：$O(m\log m\log k)$。

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#define int long long
#define x first
#define y second
using namespace std;
using PII = pair<int, int>;
const int N = 2e5 + 10;

int n, m, k, l, c[N], dist[N], f[N];
vector<PII> g[N];
vector<int> sp;
bool st[N];

priority_queue<PII, vector<PII>, greater<PII> > heap;
void dijkstra(int x, int o) {
	memset(st, 0, sizeof st);
	while(heap.size()) {
		int t = heap.top().y; heap.pop();
		if(st[t]) continue;
		st[t] = 1;
		for(auto v : g[t]) {
			if(dist[v.x] > dist[t] + v.y) {
				dist[v.x] = dist[t] + v.y;
				if((c[v.x] >> x & 1) == o) f[v.x] = min(f[v.x], dist[v.x]);
				heap.push({dist[v.x], v.x});
			}
		}
	}
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> m >> k >> l;
	for(int i = 1; i <= n; i ++) cin >> c[i];
	for(int i = 1, x; i <= l; i ++) cin >> x, sp.push_back(x);
	for(int i = 1, a, b, c; i <= m; i ++) {
		cin >> a >> b >> c;
		g[a].push_back({b, c}), g[b].push_back({a, c});
	}
	memset(f, 0x3f, sizeof f);
	for(int i = 0; i <= 17; i ++) {
		while(heap.size()) heap.pop();
		memset(dist, 0x3f, sizeof dist);
		for(int u : sp) if(c[u] >> i & 1) heap.push({0, u}), dist[u] = 0;
		dijkstra(i, 0);
		while(heap.size()) heap.pop();
		memset(dist, 0x3f, sizeof dist);
		for(int u : sp) if((c[u] >> i & 1) == 0) heap.push({0, u}), dist[u] = 0;
		dijkstra(i, 1);
	}
	for(int i = 1; i <= n; i ++) {
		if(f[i] <= 4e18) cout << f[i] << ' ';
		else cout << -1 << ' ';
	}
	
	return 0;
}
```



---

## 作者：CarroT1212 (赞：2)

+ 关键词：最短路，二进制

如果之前没见过这个套路的话应该挺难想的。

直接枚举从哪个颜色的点开始然后全部扔进队里跑多源最短路是会死的。那怎么保证颜色不重呢？

发现你只需要让起终点的颜色不一样就够了，不需要知道它们到底怎么不一样。

所以考虑用最少的次数把所有不同颜色的情况覆盖掉。这肯定至少有个 $\log$，那就枚举二进制位跑。令起终点的颜色的二进制位表示下枚举的这一位不同，那么分两层再跑最短路即可，两层分别表示从一个颜色编号在枚举的二进制位上是 $0/1$ 的起始位置出发的最短路。

这是显然可以覆盖所有不同的情况的。$O(m\log n\log k)$。

```cpp
ll n,m,k,l,a[N],b[N],dis[N][2],vis[N][2],ans[N];
vector<pll > e[N];
int main() {
	memset(ans,20,sizeof(ans));
	scanf("%lld%lld%lld%lld",&n,&m,&k,&l);
	for (ll i=1;i<=n;i++) scanf("%lld",&a[i]);
	for (ll i=1;i<=l;i++) scanf("%lld",&b[i]);
	for (ll i=1,x,y,z;i<=m;i++) scanf("%lld%lld%lld",&x,&y,&z),e[x].pb({y,z}),e[y].pb({x,z});
	for (ll i=0;i<31;i++) {
		memset(dis,20,sizeof(dis)),memset(vis,0,sizeof(vis));
		priority_queue<pair<ll,pll > > q;
		for (ll j=1;j<=l;j++) q.push({dis[b[j]][a[b[j]]>>i&1]=0,{b[j],a[b[j]]>>i&1}});
		while (!q.empty()) {
			ll p=q.top().second.first,pp=q.top().second.second;
			q.pop();
			if (vis[p][pp]) continue;
			vis[p][pp]=1;
			if (pp!=(a[p]>>i&1)) ans[p]=min(ans[p],dis[p][pp]);
			for (pll j:e[p]) if (dis[j.first][pp]>dis[p][pp]+j.second)
				q.push({-(dis[j.first][pp]=dis[p][pp]+j.second),{j.first,pp}});
		}
	}
	for (ll i=1;i<=n;i++) cout<<(ans[i]>J?-1:ans[i])<<" ";
	return 0;
}
```

---

## 作者：cool_milo (赞：2)

这题被 [bot](https://www.luogu.com.cn/user/370005) 秒了 /bx 

来一发单 $\log$ 题解。

如果没有颜色限制，那么问题等价于多源最短路。

现在规定集合内的点必须由集合外的点更新而来，根据经典套路我们可以考虑记录最短路 $s1$ 和**起点与最短路的起点不在同一集合内的最短路** $s2$ 。可以发现这两者中间必然有一个是答案。  
这样跑一遍多源 dijkstra ，每次弹出一个堆顶元素。如果它是最短路，那么就记录下来，如果它和当前最短路所属集合不同，那么也记录下来。我们发现如果一条路径是 $s2$ ，那么它经过的所有点中，它要么是 $s1$ ，要么是 $s2$ ，那么正确性也没问题了。

最后注意一个细节，在更新 $s2$ 的时候，不能把 $s2_j < nowdis + w_{i,j}$ 作为入队的依据，而是只要目标点没有被标记为被到达过两次，都应该入队。而 $s2$ 应该在出队的时候再更新。这是因为你当前以为可以当做 $s2$ 的路径，会因为和 $s1$ 所属集合相同而被淘汰，可是 $s2$ 的长度已经被错误地更新了。

容易发现每个点只会更新周围的点两次，复杂度 $\Theta((n + m) \log m)$

代码改来改去了很多次，有点混乱，这里就不放了。

---

## 作者：STDLIRUIZHE (赞：1)

先考虑放宽限制，假设没有颜色限制。

那么我们就相当于以这些特殊点跑一遍最短路即可。

考虑加上颜色限制。

比较暴力的方法是，我们可以枚举当前是哪个特殊点。

然后，以这个点为起点，跑一遍最短路，更新一下跟他国家编号不一样的点。

时间复杂度 $\mathcal O(nL)$，妥妥爆炸。

我们发现，每一次只有一个国家里面的点是没有被更新的。

考虑是否要求 $k$ 最短路？不太可能，因为第 $k$ 个可能还是这个国家的，~~还因为这是一道蓝题~~。

但是因为考虑到要求的是编号不同即可。

这样就告诉我们，如果将编号拆成二进制，那么总有一位是不相同的。

于是，我们就可以枚举这个不相同的位置。可以令特殊点这一位是 $0$，那么更新的时候就要求 $a_i$ 的这一位是 $1$；

反之，可以令特殊点这一位是 $0$，则 $a_i$ 这一位就是 $1$，跑最短路即可。

因为只会有 $\log k$ 位，再加上跑最短路的时间复杂度，则最终时间复杂度为 $\mathcal O(m \log n \log k)$，能过。

这其实也是一个套路，叫做二进制拆分。但不过如果真的是第一次做，那么有很大概率是真的做不出来的，除非时间够多。

代码：

```cpp
#include<bits/stdc++.h>
#define x0 x_0
#define x1 x_1
#define y0 y_0
#define y1 y_1
#define yn y_n
#define j0 j_0
#define j1 j_1
#define k0 k_0
#define k1 k_1
#define d0 d_0
#define d1 d_1
#define LL long long
#define LD long double
#define ZPB push_back
#define ZPF push_front
#define US unsigned
using namespace std;
struct node{
	int v;
	LL w;
	bool operator < (const node &o)const{return w>o.w;}
};
vector<node> G[100010];
const LL LLmex=1e18;
LL dis[100010],ans[100010];
int n,m,k,l,a[100010],b[100010],c[100010];
priority_queue<node> q;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>k>>l;
	for(int i=1;i<=n;++i) cin>>a[i],ans[i]=LLmex;
	for(int i=1;i<=l;++i) cin>>b[i];
	for(int i=1;i<=m;++i){
		int u,v,w;
		cin>>u>>v>>w,G[u].ZPB({v,w}),G[v].ZPB({u,w});
	}
	for(int i=1;i<=k;i<<=1){
		int cnt=0;
		for(int j=1;j<=l;++j)
			if(!(a[b[j]]&i)) c[++cnt]=b[j];
		for(int j=1;j<=n;++j) dis[j]=LLmex;
		for(int j=1;j<=cnt;++j) dis[c[j]]=0,q.push({c[j],0});
		while(q.size()){
			node dt=q.top();
			q.pop();
			int x=dt.v;
			if(dis[x]<dt.w) continue;
			for(int i=0;i<(int)G[x].size();++i){
				int u=G[x][i].v;
				LL w=G[x][i].w;
				if(dis[u]>dis[x]+w) dis[u]=dis[x]+w,q.push({u,dis[u]});
			}
		}
		for(int j=1;j<=n;++j)
			if(a[j]&i) ans[j]=min(ans[j],dis[j]);
		cnt=0;
		for(int j=1;j<=l;++j)
			if(a[b[j]]&i) c[++cnt]=b[j];
		for(int j=1;j<=n;++j) dis[j]=LLmex;
		for(int j=1;j<=cnt;++j) dis[c[j]]=0,q.push({c[j],0});
		while(q.size()){
			node dt=q.top();
			q.pop();
			int x=dt.v;
			if(dis[x]<dt.w) continue;
			for(int i=0;i<(int)G[x].size();++i){
				int u=G[x][i].v;
				LL w=G[x][i].w;
				if(dis[u]>dis[x]+w) dis[u]=dis[x]+w,q.push({u,dis[u]});
			}
		}
		for(int j=1;j<=n;++j)
			if(!(a[j]&i)) ans[j]=min(ans[j],dis[j]);
	}
	for(int i=1;i<=n;++i){
		if(ans[i]==LLmex) cout<<"-1 ";
		else cout<<ans[i]<<" ";
	}
	cout<<"\n";
	return 0;
}
```

---

## 作者：run_away (赞：1)

## 题意

一张 $n$ 个点，$m$ 条边的图，每个点都有给定的颜色 $col_i$。给定 $l$ 个点作为“特殊点” ，求出每个点到最近的颜色不同“特殊点” 的距离。

## 分析

学校里定时训练的 abc 套题，赛时直接跳了。

赛后看，结果是一个套路题。

枚举的二进制位，类似 [旅行者](https://www.luogu.com.cn/problem/P5304)，然后比对 $col_i$ 二进制当前位的数字，在跑最短路时更新答案。

注意每一位都要跑两次最短路，一次以所有当前位为 $0$ 的做起点；一次以当前位为 $1$ 的做起点。

具体实现可以看代码（做这个题的人应该看得懂吧）。

因为枚举二进制，所以用 dijkstra 跑最短路时间复杂度有两个 $\log$，是 $O(m\log n\log k)$。

## Code

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
#define dbg(x) cout<<#x<<": "<<x<<"\n"
inline ll read(){ll x=0,f=1;char c=getchar();while(c<48||c>57){if(c==45)f=0;c=getchar();}while(c>47&&c<58)x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?x:-x;}
const ll mod=1e9+7,maxn=2e5+5,maxt=505;
ll n,m,k,l,col[maxn],ans[maxn],dis[maxn],vis[maxn];
vector<ll>ts;
vector<pair<ll,ll> >son[maxn];
priority_queue<pair<ll,ll>,vector<pair<ll,ll> >,greater<pair<ll,ll> > >q;
inline void dijkstra(ll s,ll val){
    memset(vis,0,sizeof(vis));
    while(!q.empty()){
        ll u=q.top().second;q.pop();
        if(vis[u])continue;
        vis[u]=1;
        for(auto to:son[u]){
            ll v=to.first,d=to.second;
            if(dis[u]+d<dis[v]){
                dis[v]=dis[u]+d;
                if((col[v]>>s&1)==val)ans[v]=min(ans[v],dis[v]);
                q.push({dis[v],v});
            }
        }
    }
}
inline void solve(){
    n=read(),m=read(),k=read(),l=read();
    for(ll i=1;i<=n;++i)col[i]=read();
    for(ll i=1;i<=l;++i){
        ts.push_back(read());
    }
    for(ll i=1;i<=m;++i){
        ll u=read(),v=read(),w=read();
        son[u].push_back({v,w});
        son[v].push_back({u,w});
    }
    memset(ans,0x3f,sizeof(ans));
    for(ll i=0;i<=17;++i){
        while(!q.empty())q.pop();
        memset(dis,0x3f,sizeof(dis));
        for(auto u:ts){
            if(col[u]>>i&1)q.push({0,u}),dis[u]=0;
        }
        dijkstra(i,0);
        while(!q.empty())q.pop();
        memset(dis,0x3f,sizeof(dis));
        for(auto u:ts){
            if((col[u]>>i&1)==0)q.push({0,u}),dis[u]=0;
        }
        dijkstra(i,1);
    }
    for(ll i=1;i<=n;++i){
        if(ans[i]>=1e14)printf("-1 ");
        else printf("%lld ",ans[i]);
    }
}
signed main(){
    ll t=1;
    while(t--){
        solve();
    }
    return 0;
}
```

---

## 作者：Sorato_ (赞：0)

# ABC245G Foreign Friends 题解

回顾一下二进制分组。

## 题目大意

给定一张 $N$ 个点 $M$ 条边的无向图，及 $L$ 个特殊点。每个点有颜色 $C_i$。求每个点到离他最近的与他颜色不同特殊点的距离。

## Solve

两个点颜色不同，等价于他们的颜色在二进制下至少有一位不同。

所以我们考虑把所有点按颜色二进制分组。枚举位数 $x$，把颜色第 $x$ 位上是 $1$ 的和是 $0$ 的点分为两组。

跑两次多源最短路，第一次把第 $x$ 位上是 $1$ 的那一组里的特殊点作为源点去跑，然后用求得的最短路去更新第 $x$ 位上是 $0$ 的那一组里的点的答案。

第二次反过来，把第 $x$ 位上是 $0$ 的特殊点作为源点，更新 $1$ 组的答案。

多源最短路也可以用超级源点代替。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	short f=1;
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')	{if(c=='-')	f=-1;c=getchar();}
	while(c>='0'&&c<='9')	x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
const int N=1e5+10,inf=1e18;
int n,m,dis[N],k,l,a[N],ans[N];
typedef pair<int,int> PII;
vector<PII>e[N];
priority_queue<PII,vector<PII>,greater<PII>>q;
inline void dij(int s)
{
	for(int i=1;i<=n;i=-~i)	dis[i]=inf;
	q.push({dis[s]=0,s});
	while(!q.empty())
	{
		int u=q.top().second,d=q.top().first;q.pop();
		if(d>dis[u])	continue;
		for(PII i:e[u])
			if(dis[i.first]>d+i.second)
				q.push({dis[i.first]=d+i.second,i.first});
	}
}
bool tag[N];
inline void solve(int x,bool op)
{
	e[0].clear();
	for(int i=1;i<=n;i=-~i)
		if((a[i]>>x&1)==op&&tag[i])	e[0].push_back({i,0});
	dij(0);
	for(int i=1;i<=n;i=-~i)
		if((a[i]>>x&1)^op)	ans[i]=min(ans[i],dis[i]);
}
signed main()
{
	n=read();m=read();k=read();l=read();
	for(int i=1;i<=n;i=-~i)	a[i]=read(),ans[i]=inf;
	for(int i=1;i<=l;i=-~i)	tag[read()]=1;
	for(int i=1,u,v,w;i<=m;i=-~i)
		u=read(),v=read(),w=read(),
		e[u].push_back({v,w}),e[v].push_back({u,w});
	for(int i=0;i<20;i=-~i)	solve(i,0),solve(i,1);
	for(int i=1;i<=n;i=-~i)
		printf("%lld ",ans[i]<inf?ans[i]:-1);
	return 0;
}
```

---

## 作者：Take_A_Single_6 (赞：0)

很典的拆位，但是很神奇的运用。  
先不考虑颜色限制，是一个关键点最短路，考虑堆优化的意义，直接把关键点全部塞进优先队列就可以求得一个点到最近的关键点的最短距离。  
对于颜色限制，发现 $1\le k \le 10^5$，显然每种颜色跑一遍最短路会超时。这种方法在维护不同的颜色时所使用的信息太多了，复杂度为 $O(km\log n)$。  
显然，只要一个二进制位不同，两个数就不相同。那么我们直接对颜色拆位，关键点颜色此位为 $1$ 的入队，更新此位为 $0$ 的点。**注意，还需要反过来跑一遍，否则会漏掉情况。** 复杂度$O(m\log n\log k)$，可以通过本题。  
```cpp
#include<bits/stdc++.h>
#define int long long
#define db double
#define maxn 1000005
#define mod 1000000007
#define fir first
#define sec second
#define pr pair<int,int>
#define mk make_pair
#define inf 10000000000000000
using namespace std;
inline int read()
{
    int SS=0,WW=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
	{
        if(ch=='-')WW=-1;
        ch = getchar();
    }
    while(ch>='0'&&ch<='9')
	{
        SS=(SS<<1)+(SS<<3)+(ch^48);
        ch=getchar();
    }
    return SS*WW;
}
inline void write(int XX)
{
    if(XX<0)putchar('-'),XX=-XX;
    if(XX>9)write(XX/10);
    putchar(XX% 10 + '0');
}
struct edge
{
	int to,val,nxt;
}e[maxn];
int n,m,k,l,a[maxn],c[maxn],cnt,head[maxn],dis[maxn],ans[maxn];
bool vis[maxn];
void add(int x,int y,int z)
{
	e[++cnt].to=y;
	e[cnt].val=z;
	e[cnt].nxt=head[x];
	head[x]=cnt;
}
priority_queue<pr,vector<pr >,greater<pr > >q;
void dij()
{
	int u,w;
	while(q.size())
	{
		u=q.top().sec,q.pop();
		if(vis[u])continue;
		vis[u]=1;
		for(int i=head[u];i;i=e[i].nxt)
		{
			int v=e[i].to;
			if(dis[v]>dis[u]+e[i].val)dis[v]=dis[u]+e[i].val,q.push(mk(dis[u]+e[i].val,v));
		}
	}
}//最短路板子
signed main()
{
	int x,y,z;
	n=read(),m=read(),k=read(),l=read();
	for(int i=1;i<=n;i++)c[i]=read(),ans[i]=inf;
	for(int i=1;i<=l;i++)a[i]=read();
	for(int i=1;i<=m;i++)x=read(),y=read(),z=read(),add(x,y,z),add(y,x,z);
	for(int i=0;i<=20;i++)
	{
		for(int j=1;j<=n;j++)dis[j]=inf,vis[j]=0;//初始化
		for(int j=1;j<=l;j++)if((c[a[j]]>>i)&1)q.push(mk(0,a[j])),dis[a[j]]=0;//入该位为1的
		dij();
		for(int j=1;j<=n;j++)if(((c[j]>>i)&1)==0)ans[j]=min(ans[j],dis[j]);//更新该位为0的
	}
	for(int i=0;i<=20;i++)//反过来跑一遍
	{
		for(int j=1;j<=n;j++)dis[j]=inf,vis[j]=0;
		for(int j=1;j<=l;j++)if(((c[a[j]]>>i)&1)==0)q.push(mk(0,a[j])),dis[a[j]]=0;
		dij();
		for(int j=1;j<=n;j++)if((c[j]>>i)&1)ans[j]=min(ans[j],dis[j]);
	}
	for(int i=1;i<=n;i++)write(ans[i]==inf?-1:ans[i]),putchar(' ');//是否能被关键点更新到
	return 0;
}
```

---

