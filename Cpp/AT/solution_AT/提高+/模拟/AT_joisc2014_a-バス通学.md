# バス通学

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joisc2014/tasks/joisc2014_a



# 题解

## 作者：Bitter_Tea (赞：7)

基本思路是$dfs$+**贪心**

我们先把边存起来，然后进行按照到站时间从大到小排序
这样我们进行建边时，最后建的边的到站时间就是最早的，也就是我们先搜索到的边是最优的。

如果$t$越大，那么可能的$ans$也就越大。


于是乎，我们按照从小到大的顺序对询问进行排序。

然后进行搜索，我们不需要搜已经搜索过的边，因为如果用原来的边时间一定会更小，所以我们每次更改每个点指向的边，来保证每个边只搜索一次。


总体复杂度是$O(M)$，因为每个边只走一次。

$Code$
```cpp
#include<cstdio>
#include<algorithm>
const int N=100005;
using namespace std;
struct D {
	int x,y,t1,t2;
	bool operator < (const D&a) const 
	{return t2>a.t2;}
} a[N*3];
struct Q {
	int x,t;
	bool operator <(const Q&a) const 
	{return t<a.t;}
} c[N];
struct E {
	int nxt,to,t1,t2;
} e[N*6];
int fir[N],tot;
int ans[N],d[N];
int n,m,q;
void add(int x,int y,int t1,int t2) 
{
	e[++tot].nxt=fir[x];
	e[tot].to=y;
	fir[x]=tot;
	e[tot].t1=t1;
	e[tot].t2=t2;
}
void dfs(int x,int t) 
{
	d[x]=max(d[x],t);
	for(int i=fir[x]; i; i=e[i].nxt) 
	{
		int p=e[i].to;
		if(t<e[i].t2) return;
		fir[x]=i;
		dfs(p,e[i].t1);
	}
	fir[x]=0;//关键
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=m; i++) 
	scanf("%d%d%d%d",&a[i].x,&a[i].y,&a[i].t1,&a[i].t2) ;
	sort(a+1,a+m+1);
	for(int i=1; i<=m; i++) 
	add(a[i].y,a[i].x,a[i].t1,a[i].t2);
	scanf("%d",&q);
	for(int i=1; i<=q; i++) 
	scanf("%d",&c[i].t),c[i].x=i;
	sort(c+1,c+q+1);
	fir[1]=0;
	d[1]=-1;
	for(int i=1; i<=q; i++) 
	{
		dfs(n,c[i].t);
		ans[c[i].x]=d[1];
	}
	for(int i=1; i<=q; i++) 
	printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：buowen123 (赞：5)

看到大量询问和极强的单调性，想到整体二分。

用函数 $solve(ql,qr,tl,tr)$ 表示已知第 $ql \sim qr$ 个询问的答案都在 $tl \sim tr$ 之间，要解决这些询问。

二分起始时间 $mid$，跑出到 $n$ 的最短时间 $d$。将要求的到达时间 $<d$ 的询问放在一边，$\ge d$ 的放在另一边，分治处理即可。边界条件就是 $tl=tr$。

那怎么跑出最短路呢？可以利用类似 SPFA 的思想，同样使用队列维护需要松驰的点。不难证明这是正确的：一条边只会松弛一次，因为多次松弛没有意义。

注意特判 $-1$。认为 $n,m,q$ 同阶，则时间复杂度 $O(n\log V+n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 3, maxm = 3e5 + 3, maxt = 86400000 + 3;
int n, m, q;
struct node {
	int to;
	ll a, b;
};
struct query {
	ll t;
	int id;
} h[maxn];
bool operator < (const node &x, const node &y) {
	return x.a > y.a;
}
bool operator < (const query &x, const query &y) {
	return x.t > y.t;
}
vector <node> p[maxn];
int sum[maxn], cnt[maxn];
ll ans[maxn], dis[maxn];
bool vis[maxn];
void get_dis(int mid) {
	memset(cnt, 0, sizeof cnt);
	memset(vis, 0, sizeof vis);
	memset(dis, 0x3f, sizeof dis);
	dis[1] = mid;
	queue <int> q;
	q.push(1);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		if (sum[u] == 0) continue;
		while (cnt[u] + 1 <= sum[u] && p[u][cnt[u]].a >= dis[u]) {
			int v = p[u][cnt[u]].to;
			ll w = p[u][cnt[u]].b;
			dis[v] = min(dis[v], w);
			cnt[u]++;
			q.push(v);
		}
	}
}
void solve(int ql, int qr, ll tl, ll tr) {
	if (ql > qr || tl > tr) return;
	if (tl == tr) {
		for (int i = ql; i <= qr; i++) {
			ans[h[i].id] = tl;
		}
		return;
	} 
	ll mid = (tl + tr + 1) >> 1;
	get_dis(mid);
	int qk = 0;
	for (int i = qr; i >= ql; i--) {
		if (dis[n] > h[i].t) qk = i;
	}
	if (qk == ql) solve(ql, qr, tl, mid - 1);
	else if (qk == 0) solve(ql, qr, mid, tr);
	else solve(ql, qk - 1, mid, tr), solve(qk, qr, tl, mid - 1);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int x, y;
		ll a, b;
		cin >> x >> y >> a >> b;
		p[x].push_back((node) {y, a, b});
	}
	for (int i = 1; i <= n; i++) {
		sort(p[i].begin(), p[i].end());
		sum[i] = p[i].size();
	}
	cin >> q;
	for (int i = 1; i <= q; i++) {
		cin >> h[i].t;
		h[i].id = i;
	}
	sort(h + 1, h + q + 1);
	solve(1, q, 0, maxt);
	get_dis(0);
	for (int i = 1; i <= q; i++) {
		int t = h[i].t;
		if (dis[n] > t) ans[h[i].id] = -1;
	}
	for (int i = 1; i <= q; i++) {
		cout << ans[i] << '\n';
	}
	return 0;
} 
```

---

## 作者：鱼跃于渊 (赞：4)

考场上搓出了一个比较诡异的做法，结果咕到了半个月后才来写题解。  

## 做法  

这是一个纯粹的图论做法，最短路使用 spfa 实现。  

首先如果我们直接建图，对于每个询问跑最短路，那么外面要套一层二分，比较麻烦。  
于是想到建反图，也就是把 $(u,v,a,b)$ 变成 $(v,u,b,a)$，然后对于每个 $l_i$ 跑一次最短路即可，答案就是 $dis_1$。  
但这样效率太低，过不了。  

观察样例可以得出一个结论，在一段时间内的询问，它们的答案实际上是相同的。  
也就是说我们对询问的时间画出一个数轴，上面的答案是一段一段的。  
可以发现，这些分界点实际上就是每条边的 $b$，于是我们把每条边按 $b$ 从小到大进行排序。  
我们把边依次加入图中，每加入一次，就跑一遍最短路，这样就可以记录下来每个分界点对应的答案了。  
至于询问，我们二分这个询问处于哪两个分界点之间，它的答案就是前面那个分界点的答案。  

但是这样做会 T，我们考虑如何优化。  
首先可以发现，肯定有一大段的答案为 $-1$，于是我们最开始先二分出答案为 $-1$ 的最大分界点，然后从这一点开始加边跑最短路。  
其次呢，我们注意到只有 $u=n$ 的情况下才需要跑最短路，原因显然。  
考虑如果 $n$ 的出边没有改变，则它到各点的 $dis_u$ 没有变化，那么新加入的边自然就不会产生什么影响。 


这个做法的时间复杂度相当诡异，不知道能不能被卡，反正能过。  

## 代码
下面是考场代码，写的有些丑，还请见谅。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define per(i,a,b) for(int i=(a);i<=(b);i++)
#define rep(i,b,a) for(int i=(b);i>=(a);i--)
const int N=1e5+5,M=3e5+5;
struct edge{int u,v,a,b;}ed[M];
int n,m,que,upl;
int vis[N],dis[N];
int tot,tub[M],ans[M];
queue <int> q;
vector <edge> e[N];
void spfa(int st,int mid){
	dis[st]=mid;
	q.push(st);
	while(!q.empty()){
		int u=q.front();q.pop();
		vis[u]=0;
		for(auto x:e[u]){
			if(dis[u]>=x.a&&dis[x.v]<x.b){
				dis[x.v]=x.b;
				if(!vis[x.v]){
					vis[x.v]=1;
					q.push(x.v);
				}
			}
		}
	}
}
bool check(int mid){
	per(i,1,n) e[i].clear();
	fill(dis+1,dis+n+1,-1);
	per(i,1,m){
		if(ed[i].a>mid) break;
		e[ed[i].u].push_back(ed[i]);
	}
	spfa(n,mid);
	return dis[1]!=-1;
}
int binary(){
	int l=0,r=ed[m].a,mid,res=0;
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid)){
			r=mid-1;res=mid;
		}
		else l=mid+1;
	}
	return res;
}
void solve(){
	sort(ed+1,ed+m+1,[](const edge &x,const edge &y){
		return x.a<y.a;
	});
	upl=binary();
	per(i,1,m) if(ed[i].a>=upl&&ed[i].a!=tub[tot])
		tub[++tot]=ed[i].a;
	per(i,1,n) e[i].clear();
	fill(dis+1,dis+n+1,-1);
	per(i,1,m) if(ed[i].a<upl)
		e[ed[i].u].push_back(ed[i]);
	spfa(n,upl);
	ans[0]=dis[1];
	per(i,1,m) if(ed[i].a>=upl){
		e[ed[i].u].push_back(ed[i]);
		if(ed[i].u==n) spfa(n,ed[i].a);
		ans[upper_bound(tub,tub+tot+1,ed[i].a)-tub-1]=dis[1];
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
//	freopen("tp.in","r",stdin);
//	freopen("tp.out","w",stdout);
	cin>>n>>m;
	for(int i=1,u,v,a,b;i<=m;i++){
		cin>>u>>v>>a>>b;
		ed[i]={v,u,b,a};
	}
	solve();
	cin>>que;
	for(int i=1,l;i<=que;i++){
		cin>>l;
		cout<<ans[upper_bound(tub,tub+tot+1,l)-tub-1]<<'\n';
	}
	return 0;
}
```

---

## 作者：qfpjm (赞：3)

# 题解

- 看到最晚，我们可以考虑贪心或二分，但这题贪心比较好想。

- 我们考虑反向搜索，从 $n$ 出发求出到每个点最长但不迟到的时间，记为 $d_i$，最终答案为 $d_1$。

- 这题重点在实现。我们将询问按时间倒排，这样可以使我们先搜索到的边是最优的。对于询问，我们离线，顺排，因为较小的 $d_i$ 可以用来更新更大的 $d_i$。每次我们访问完一条边就直接 `pop_back`，保证每条边只走一次，通过上述的询问顺排，我们可以保证答案可以被更新，这样保证时间复杂度为 $O(m)$。

# 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

struct node
{
	int a, b, x, y;	
}a[500005];

struct node2
{
	int l, idx;
}qt[500005];

struct node3
{
	int v, x, y;
};

int n, m, q, dis[500005], ans[500005];
vector<node3> G[500005];

bool cmp(node x, node y)
{
	return x.y > y.y;
}

bool cmp2(node2 x, node2 y)
{
	return x.l < y.l;
}

void dfs(int u, int t)
{
	dis[u] = max(dis[u], t);
	for (int i = G[u].size() - 1 ; i >= 0 ; i --)
	{
		int v = G[u][i].v;
		if (t >= G[u][i].y)
		{
			dfs(v, G[u][i].x);
			G[u].pop_back();
		}
	}
}

int main()
{
	cin >> n >> m;
	for (int i = 1 ; i <= m ; i ++)
	{
		cin >> a[i].a >> a[i].b >> a[i].x >> a[i].y;
	}
	sort(a + 1, a + 1 + m, cmp);
	for (int i = 1 ; i <= m ; i ++)
	{
		node3 s;
		s.v = a[i].a;
		s.x = a[i].x;
		s.y = a[i].y;
		G[a[i].b].push_back(s);
	}
	cin >> q;
	for (int i = 1 ; i <= q ; i ++)
	{
		cin >> qt[i].l;
		qt[i].idx = i;
	}
	sort(qt + 1, qt + 1 + q, cmp2);
	dis[1] = -1;
	for (int i = 1 ; i <= q ; i ++)
	{
		dfs(n, qt[i].l);
		ans[qt[i].idx] = dis[1];
	}
	for (int i = 1 ; i <= q ; i ++)
	{
		cout << ans[i] << endl;
	}
}
```


---

## 作者：N2MENT (赞：2)

[blog](https://www.cnblogs.com/0x0620AF/articles/JOISC2014A.html)

猫猫大失败。

知州所中，我是个三百。模拟赛 T1，口湖线段树，空间开小，遂卒。

首先注意到每一条边只会走一次，那么按照起点开始时间排序之后，走过的边一定是它的子序列。

于是我们对每个点开一个线段树，表示要在这个时刻之前到达这个点最晚要什么时候出发。直接更新即可，最后查询在 $n$ 号点的线段树上查。

```cpp
//        No mind to think.
//
//        No will to break.
//
//        No voice to cry suffering.
//
//        Born of God and Void.
//
//        You shall seal the blinding light that plagues their dreams.
//
//        You are the Vessel.
//
//        You are the Hollow Knight.
#ifdef N2
#define _GLIBCXX_DEBUG
#define LOG(...) fprintf(stderr, __VA_ARGS__)
#else 
#define LOG(...)
#endif
#define syncoff ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
const int maxm = 3e5 + 10;
const int maxl = maxm * 50;
const int rinf = 9e7;
template<typename _Tp> constexpr inline void Getmin(_Tp &x, _Tp y) {if(x > y) x = y;}
template<typename _Tp> constexpr inline void Getmax(_Tp &x, _Tp y) {if(x < y) x = y;}
class SegTree {//does not support range query
public:
    static int tr[maxl], lc[maxl], rc[maxl], cnt;
    int rt;
    int __new() {
        cnt++;
        tr[cnt] = -1;
        return cnt; 
    }
    void __modify(int &k, int l, int r, int L, int R, int val) {
        if(!k) k = __new();
        if(L <= l && r <= R) {
            Getmax(tr[k], val);
            return;
        }
        int mid = (l + r) >> 1;
        if(L <= mid) __modify(lc[k], l, mid, L, R, val);
        if(R > mid) __modify(rc[k], mid + 1, r, L, R, val);
    }
    void modify(int L, int R, int val) {__modify(rt, 0, rinf, L, R, val);}
    void __query(int k, int l, int r, int addr, int& res) {
        if(!k) return;
        Getmax(res, tr[k]);
        if(l == r) return;
        int mid = (l + r) >> 1;
        if(addr <= mid) __query(lc[k], l, mid, addr, res);
        else __query(rc[k], mid + 1, r, addr, res);
    }
    int query(int addr) {
        int res = -1;
        __query(rt, 0, rinf, addr, res);
        return res;
    }
}sgt[maxn];
int SegTree::tr[maxl], SegTree::lc[maxl], SegTree::rc[maxl], SegTree::cnt = 0;
class Edge {
public:
    int u, v, a, b;
    Edge() = default;
    Edge(int u, int v, int a, int b) : u(u), v(v), a(a), b(b) {}
};
vector<Edge> e;
int n, m, q;
int main() {
    syncoff;
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int u, v, a, b;
        cin >> u >> v >> a >> b;
        if(v == 1) continue;
        e.emplace_back(u, v, a, b);
    }
    sort(e.begin(), e.end(), [](Edge a, Edge b){return a.a < b.a;});
    for(auto cur : e) {
        // LOG("%d %d %d %d\n", cur.u, cur.v, cur.a, cur.b);
        if(cur.u == 1) {
            sgt[cur.v].modify(cur.b, rinf, cur.a);
            continue;
        }
        int x = sgt[cur.u].query(cur.a);
        sgt[cur.v].modify(cur.b, rinf, x);
    }
    // for(int i = 1; i <= n; i++) {
    //     for(int j = 0; j <= 10; j++) {
    //         LOG("%d ", sgt[i].query(j));
    //     }
    //     LOG("\n");
    // }
    cin >> q;
    while(q--) {
        int l;
        cin >> l;
        cout << sgt[n].query(l) << '\n';
    }
}
```

---

## 作者：NXYorz (赞：2)

[题目链接](https://www.luogu.com.cn/problem/AT1217)

$Dp$

考虑$f(i,j)$表示在时间 $j$ 之后到达 $i$ 的最大代价。 特别的， 如果 $i$ 等于 $1$， 那么 $f(i,j)$等于其出发时间。 那么如果某一公交车 $C$ 出发点是 $a$， 终点是 $b$， 此时 $\max{f(b,k)}  < \max{f(a,j)}$其中 $j$ 小于等于 $C$ 的出发时间 $x$， 而且 $k$ 小于等于 $C$ 的到站时间 $y$ 那么就更新 $f(b,y)=f(a,j)$。

基于朴素的做法， 我们可以优化。

类似于单调队列的思想， 如果每一次到达终点 $b$ 的时间都比上一辆到达 $b$ 的车晚， 于是按 $y$ 排序， 我们就只需要比较他们的 $f(b,y)$即可。 如果新的大于老的， 进队。 否则不进队。 这样就保证了在这个队列里越往后越大。

维护到站时间， 查询的时候二分即可。

```cpp
#include<cstdio>
#include<algorithm>
#include<map>
#include<vector>
using namespace std;
const int N = 1e5 + 1;
const int M = 3e5 + 1;
int n,m,qu;
struct NOo {
	int a,b,x,y;
	bool operator < (const NOo b) const {
		return y < b.y;
	}
} ru[M];
vector < pair<int , int> > vec[N];
int check(int op , int d) {
	int l = 0;
	int r =vec[op].size();
	int ans = -1;
	while(l < r) {
		int mid = l + r >> 1;
		if(vec[op][mid].first <= d) {
			ans = mid;
			l = mid + 1;
		} else r = mid;
	} return ans;
} int ques(int d) {
	int l = 0;
	int r = vec[n].size();
	int ans = -1;
	while(l < r) {
		int mid = l + r >> 1;
		if(vec[n][mid].first > d) r = mid;
		else {
			ans = mid;
			l = mid + 1;
		}
	} return ans == -1 ? ans : vec[n][ans].second;
} void work() {
	int li;
	scanf("%d",&li);
	printf("%d\n",ques(li));
} int main() {
//	freopen("bus.in","r",stdin);
//	freopen("bus.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i = 1 ; i <= m ; i++) {
		scanf("%d%d%d%d",&ru[i].a ,&ru[i].b ,&ru[i].x ,&ru[i].y);
		if(ru[i].a == 1)
			vec[1].push_back(pair<int , int> {0 , ru[i].x});
	}
	for(int i = 2 ; i <= n ; i++)
		vec[i].push_back(pair<int , int> {0 , -1});
	sort(ru + 1 , ru + 1 + m);
	for(int i = 1 ; i <= m ; i++) {
		if(ru[i].a == 1) {
			if(ru[i].x >= vec[ru[i].b][vec[ru[i].b].size() - 1].second)
				vec[ru[i].b].push_back(pair<int , int> {ru[i].y , ru[i].x});
			continue;
		} int loc = check(ru[i].a , ru[i].x);
		int d1 = vec[ru[i].b][vec[ru[i].b].size() - 1].second;
		int d2 = vec[ru[i].a][loc].second;
		if(d1 <= d2)
			vec[ru[i].b].push_back(pair<int , int> {ru[i].y , d2});
	} scanf("%d",&qu);
	for(int i = 1 ; i <= qu ; i++)
		work();
	return 0;
}
```

$Update:$抱歉抱歉公式坏了没看见，修改了一下公式qwq

---

## 作者：Starlight_Glimmer (赞：1)

博客食用效果更佳https://www.cnblogs.com/lyttt/p/14003299.html

[题目链接](https://www.luogu.com.cn/problem/AT1217)

#### 题目翻译

##### 题面

大学生$JOI$君要坐公交车上学。他的家和学校都在$IOI$市内，他住在$1$号结点，大学在$N$号结点。

$IOI$市有$M$辆公交车，每辆公交车每天只开一次，从特定的时刻在某个站点出发，在特定的时刻到达某个站点，不能在中途上下车，且时间跨度不会超过一天。

$JOI$每天要换乘巴士去学校，他换乘的时间可以忽略不计，即：如果要乘坐在$time_i$时刻从$pos_i$站点出发的公交车，那么他只需要在$time_i$时刻之前（包含这个时刻）到达站点$pos _i$。他可以重复走过一个车站。

$JOI$要去学校上$Q$天课，每天上课的时间各不相同，现在他想知道，他每天最晚什么时候从家里出发不会迟到。

##### 输入

第一行包括两个整数$N,M$

接下来$M$行，每行$4$个整数，$A_i,B_i,X_i,Y_i$表示第$i$辆公交车在时刻$X_i$从站点$A_i$出发，在时刻$Y_i$到达$B_i$。时刻是从午夜零点开始经过了多少毫秒（这个没啥用吧）。

下一行包括一个整数$Q$，表示上学的天数

接下来$Q$行，每行一个整数$L_j$表示第$j$天必须要在时刻$L_j$之前到校。



##### 输出

$Q$行，$Q$个整数，表示答案，如果不能按时到校，输出$-1$

##### 数据范围

$2<=N<=100000$

$1<=M<=300000$

$0<=X_i<Y_i<24*60*60*1000$

$1<=Q<=100000$

$0<=L_i<24*60*60*1000$



##### 样例

###### 输入1

```
5 6
1 2 10 25
1 2 12 30
2 5 26 50
1 5 5 20
1 4 30 40
4 5 50 70
4
10
30
60
100

```

###### 输出1

```
-1
5
10
30
```

###### 输出2

```
3 8
1 2 1 5
1 3 0 1
1 3 2 8
2 3 2 3
2 3 3 4
2 3 4 5
2 3 5 6
2 3 6 7
6
3
4
5
6
7
8
```

###### 输出2

```
0
0
0
1
1
2
```






#### 题目解析

##### 法一：贪心乱搞

由于我太菜了，不能像其他大佬那样很快地想到递推什么的，于是上来先乱搞。

贪心地想，我们先走到达时间小的边不容易迟到。

而显然$L$越大，条件越宽松，所以把询问从小到大处理。

由于我们要求的东西是$1$的时间，这个不方便搜索，所以从$n$出发。

设$d[i]$表示为了不迟到，从$n$出发到达$i$的最晚时间，那么答案就是$d[1]$

更新答案的时候，沿着边走，记录下到达这个点的最大时间是多少，和这个点公交车的到达时间比较，如果公交车到得比我要求的最大时间还要晚，那就不能走这条边了。

之前把询问从小到大排序，可以发现前面$L$较小求出来的$d[i]$可以用来更新$L$更大时的$d[i]$，你想，之前上学时间早的时候的出发时间肯定不会比上学时间晚的时间更晚，即正确性是有保障的，只是可能不会那么优秀，所以取$max$就好了。

所以一条边只会经过一次，之前用这条边更新了的答案在$d[i]$里面，后面可以直接用，不用再走一遍这条边，复杂度是$O(M)$。



##### 法二：dp递推

发现啥时候到校和坐的最后一辆公交车息息相关。

设$f[i]$表示坐第$i$辆公交车最晚几点出发，$g[i]$表示到达第$i$个点最晚几点出发

将所有公交车拆成出发和到达，按时间从小到大排序，$f,g$相互更新：

出发：用$g$更新$f$，相当于统计答案：到校的最晚时间等价于坐上最后那辆公交车的最晚时间。如果这辆公交车的起点是$1$，那么坐上这辆车的最晚时间就是$f[i]=t[i]$，否则坐上这辆车的最晚时间取决于到达起点的允许最晚出发时间，也就是$f[i]=g[u[i]]$。

到达：用$f$更新$g$：$g[v[i]]=max(g[v[i]],f[i])$，如果可以坐上车$i$，那么在$f[i]$出发也可以到达$g[v[i]]$

由于是按照时间从小到大排序，如果大于$t[i]$的$g[u[i]]$对答案不会产生影响——这个时候$g[u[i]]$还没有更新到那么大，$g[u[i]]$要么比$t[i]$小，要么没有值（无解，因为不可能从起点飞到$u[i]$来吧）

询问和出发的处理方式是一样的，询问的答案就是对应的$f$

有个小细节：排序时，如果时间一样，先到达，再出发，因为一样的时间，可以到达之后在马上接着出发。



------

#### ►Code View Ver.1

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
#define LL long long
#define N 100005
#define M 300005
#define DEL 100000
#define INF 0x3f3f3f3f
int rd()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1; c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48); c=getchar();}
	return f*x;
}
/*
实际上是L时刻从n出发 求到达1的最晚时刻(也就是在路上花费时间最小
把询问从小到大处理 显然L大的边答案会更大 
而且一个更大的L的答案可以用小的L产生的答案更新 所以每条边只会走1次 
d[i]表示从n出发 到达i的最大时刻 
*/ 
int n,m;
int d[N],ans[N];
struct node{
	int v,x,y;
};
vector<node>G[N]; 
struct P{
	int a,b,x,y;
}p[M];
struct Node{
	int id,L;
}query[N];
bool cmp(P l,P r)
{
	return l.y>r.y;
	//先搜到到站时间小的边 到站时间越靠前 越容易合法(不迟到 
	//而我不会删除vector第一个元素 只知道popback qwq 
}
bool cmp2(Node l,Node r)
{
	return l.L<r.L;
}
void dfs(int u,int t)
{//可以到达u的最晚时间为t 
	d[u]=max(d[u],t);
	for(int i=G[u].size()-1;i>=0;i--)
	{
		int v=G[u][i].v;
		if(t<G[u][i].y) return ;//最晚时间都比到达时间早 那肯定会迟到 
		dfs(v,G[u][i].x);
		G[u].pop_back();
	}
}
int main()
{
	n=rd(),m=rd();
	for(int i=1;i<=m;i++)
		p[i].a=rd(),p[i].b=rd(),p[i].x=rd(),p[i].y=rd();
	sort(p+1,p+m+1,cmp);
	for(int i=1;i<=m;i++)
	{
		node t;
		t.v=p[i].a,t.x=p[i].x,t.y=p[i].y;
		G[p[i].b].push_back(t);
	}
	int Q=rd();
	for(int i=1;i<=Q;i++)
		query[i].L=rd(),query[i].id=i;
	sort(query+1,query+Q+1,cmp2);
	d[1]=-1;
	for(int i=1;i<=Q;i++)
	{
		dfs(n,query[i].L);
		ans[query[i].id]=d[1];
	}
	for(int i=1;i<=Q;i++)
		printf("%d\n",ans[i]);
	return 0;
}
```

#### ►Code View Ver.2

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
#define LL long long
#define N 100005
#define M 300005
#define INF 0x3f3f3f3f
int rd()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1; c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48); c=getchar();}
	return f*x;
}
int n,m;
int f[M<<1]/*询问也在这*/,g[N];
struct node{
	int x,t,id,typ;
};
vector<node>query;
bool cmp(node p,node q)
{
	if(p.t==q.t)/*之前这里双等号写成了等号 调好久*/ 
		return p.typ>q.typ;//到达在出发前面 
	return p.t<q.t;
}
int main()
{
	n=rd(),m=rd();
	for(int i=1;i<=m;i++)
	{
		int u=rd(),v=rd(),x=rd(),y=rd();
		node tmp;tmp.x=u,tmp.t=x,tmp.id=i,tmp.typ=0;
		query.push_back(tmp);
		tmp.x=v,tmp.t=y,tmp.typ=1;
		query.push_back(tmp);
	}
	int Q=rd();
	for(int i=1;i<=Q;i++)
	{
		int L=rd();
		node tmp;
		tmp.x=n,tmp.t=L,tmp.id=m+i,tmp.typ=0;
		query.push_back(tmp);
	}
	sort(query.begin(),query.end(),cmp);
	memset(g,-1,sizeof(g));
	for(int i=0;i<query.size();i++)
	{
		int x=query[i].x,id=query[i].id;
		if(query[i].typ==0)
		{//出发 
			if(x==1) f[id]=query[i].t;
			else f[id]=g[x];
		}
		else//到达 
			g[x]=max(g[x],f[id]);
	}
	for(int i=1;i<=Q;i++)
		printf("%d\n",f[m+i]);
	return 0;
} 
```


---

## 作者：LinuF (赞：0)

### 思路
这个题要查询 $n$ 在不同时刻之前到达，从一出发的晚时间，这显然是有单调性的，要求越晚到达肯定能够越晚出发。考虑到每个点，其实每个点都有这样的性质。

我们考虑去维护**到达每个点的最晚时间**，以及**对应的最晚从一出发的时间**。

考虑按照路线的 $Y$ 排序，这样的好处是：对于每一个 $A$ 在 $Y$ 之前到达 $A$ 的转移都结束了。考虑直接二分从 $X$ 向 $Y$ 转移。

最后查询答案也就是二分查询 $n$，找到到达 $n$ 的最晚时间对应的最晚从一出发的时间。

### 坑点

每次二分找到答案后，要向 $B$ 后方插入的时候记得也应当和末尾比较以保证正确性。

### 代码

```cpp
#include <bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
template<typename types>
inline void read(types &x){
    x = 0; char c = getchar(); int f = 1;
    while (!isdigit(c)){ if (c == '-') f = -1; c = getchar(); }
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    x *= f; return;
}
inline void read(){}
template<typename types, typename... Args>
void read(types &x, Args&... args){
    read(x), read(args...);
    return;
}
template<typename types>
void write(types x){
    if (x < 0) putchar('-'), x = -x;
    types k = x / 10;
    if (k) write(k);
    putchar(x - k * 10 + '0');
    return;
}
const int N=6e5+5;
int n,m;
struct Edge{
    int a,b,x,y;
}e[N];
int cmp(Edge p1,Edge p2){
    return p1.y<p2.y;
}
vector<pii> v[N];
int calc(int id,int last){
    if(!v[id].size()) return -1;    
    int l=0,r=v[id].size()-1;
    while(l<r){
        int mid=(l+r+1)>>1;
        if(v[id][mid].fi<=last){
            l=mid;
        }
        else r=mid-1;
    }
    if(v[id][l].fi>last) return -1;
    return v[id][l].se;
} 
void solve(){
    read(n,m);
    for(int i=1;i<=m;i++){
        read(e[i].a);read(e[i].b);read(e[i].x);read(e[i].y);
    }
    sort(e+1,e+m+1,cmp);
    for(int i=1;i<=m;i++){
        if(e[i].a==1){
            if(v[e[i].b].size()==0) v[e[i].b].push_back({e[i].y,e[i].x});
            else if(e[i].x>v[e[i].b].back().se) v[e[i].b].push_back({e[i].y,e[i].x});
            continue;
        }
        int t=calc(e[i].a,e[i].x);
        if(t!=-1){
            if(v[e[i].b].size()==0) v[e[i].b].push_back({e[i].y,t});
            else if(t>v[e[i].b].back().se) v[e[i].b].push_back({e[i].y,t});
        }
    }
    int q;
    read(q);
    while(q--){
        int x;
        read(x);
        write(calc(n,x));puts("");
    }
}
int main(){
    solve();
    return 0;
}

```


---

## 作者：EuphoricStar (赞：0)

考虑把边按到达时间排序，然后从前往后扫并做一个 dp。

设 $f_u$ 表示 $1$ 到达 $u$ 的**最晚出发时间**。那么对于一条边 $(u, v, a, b)$：

- 若 $u = 1$，则 $f_v = \max(f_v, x)$；
- 否则 $f_v = \max(f_v, f'_u)$，$f'_u$ 为只考虑到达时间 $\le x$ 的边时 $f_u$ 的值。

可持久化数组用主席树维护，复杂度 $O((n + m + q) \log (n + m + q))$。

询问可以离线或在线回答。

[code](https://loj.ac/s/1922390)

---

## 作者：sinsop90 (赞：0)

模拟赛 T1，结果写错两个字符，还过了大样例，绑包后直接 $0$ 分起飞。

注意到很好的性质是你从 $1$ 走到 $n$ 的 $X_i$ 是单调递增的，因此我们考虑将边按照 $X_i$ 从小到大排序，并依次加入图中。

设 $g_i$ 代表能使用第 $i$ 条边的最晚出发时间，则在加入这条边的时候我们能利用之前已求出的 $g_j$ 求出 $g_i$。

具体地，$g_i = \max_{B_j=A_i,Y_j \leq X_i}g_j$，特别地，当 $u_i = 1$，则 $g_i = A_i$。

这部分可以将每一个点的入边按 $Y$ 排序，对每个点动态开点线段树，完成单点修改与区间查 $\max$ 的操作。

具体见实现，注意区间求 $\max$ 的初值要赋为 $-1$，不然你会像我的模拟赛一样保龄。

气死我了！

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 5;
int rt[maxn], id[maxn], pas[maxn], n, m, X, T, pre[maxn], cnt;
struct node {
	int u, v, l, r, id;
}g[maxn];
struct Seg {
	int ls, rs, val;
}tr[maxn * 32];
vector<node> vec[maxn];
void pushup(int p) {
	if(!tr[p].ls && !tr[p].rs) return;
	if(!tr[p].ls) tr[p].val = tr[tr[p].rs].val;
	else if(!tr[p].rs) tr[p].val = tr[tr[p].ls].val;
	else tr[p].val = max(tr[tr[p].ls].val, tr[tr[p].rs].val);
}
int update(int p, int l, int r, int nl, int k) {
	if(!p) p = ++ cnt;
	if(l == r) {
		tr[p].val = k;
		return p;
	}
	int mid = (l + r) >> 1;
	if(nl <= mid) tr[p].ls = update(tr[p].ls, l, mid, nl, k);
	else tr[p].rs = update(tr[p].rs, mid + 1, r, nl, k);
	pushup(p);
	return p;
}
int query(int p, int l, int r, int nl, int nr) {
	if(!p) return -1;
	if(nl <= l && r <= nr) return tr[p].val;
	int mid = (l + r) >> 1, res = -1; 
	if(nl <= mid) res = max(res, query(tr[p].ls, l, mid, nl, nr));
	if(nr > mid) res = max(res, query(tr[p].rs, mid + 1, r, nl, nr));
	return res;
}
void solve() {
	cin >> X;
	int l = 0, r = vec[n].size() - 1, res = -1;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(vec[n][mid].r <= X) res = mid, l = mid + 1;
		else r = mid - 1; 
	}
	if(res == -1) cout << -1 << '\n';
	else cout << pre[res] << '\n';
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for(int i = 1, u, v, l, r;i <= m;i++) {
		cin >> u >> v >> l >> r;
		g[i] = {u, v, l, r, i};
		vec[v].push_back({u, v, l, r, i});
	}
	for(int i = 1;i <= n;i++) {
		sort(vec[i].begin(), vec[i].end(), [](node a, node b) {return a.r < b.r;});
		for(int j = 0;j < vec[i].size();j++) {
			id[vec[i][j].id] = j;
		}
	}
	sort(g + 1, g + 1 + m, [](node a, node b) {return a.l < b.l;});
	for(int i = 1;i <= m;i++) {
		if(g[i].u == 1) {
			pas[g[i].id] = g[i].l;
		}
		else {
			int l = 0, r = vec[g[i].u].size() - 1, res = -1;
			while(l <= r) {
				int mid = (l + r) >> 1;
				if(vec[g[i].u][mid].r <= g[i].l) res = mid, l = mid + 1;
				else r = mid - 1;
			}
			if(res == -1) pas[g[i].id] = -1;
			else pas[g[i].id] = query(rt[g[i].u], 0, vec[g[i].u].size() - 1, 0, res);
		}
		rt[g[i].v] = update(rt[g[i].v], 0, vec[g[i].v].size() - 1, id[g[i].id], pas[g[i].id]);
	}
	pre[0] = pas[vec[n][0].id];
	for(int i = 1;i < vec[n].size();i++) pre[i] = max(pre[i - 1], pas[vec[n][i].id]);
	cin >> T;
	while(T --) solve();
}
```


---

## 作者：Basori_Tiara (赞：0)

考虑这个题有一个特殊的地方就是一条边如果用他松弛过了一次那么后续一定不会再拿他松弛了，原因很简单，因为你经过一条边后的结束时间被锁定了。

于是你考虑我们要最晚出发，不如把整张图逆转（包括时间），问题变成从 $n$ 出发到 $1$ 的最短路长度。

然后再离线询问，每次相当于是把从 $n$ 的出发时间卸下来，然后直接枚举边看有没有新的能走的边就可以了，时间复杂度是 $O(m\log n)$ 的，瓶颈在排序。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,q;
struct node{
   int v,a,b;
   bool friend operator < (const node &a,const node &b){
      return a.a>b.a;
   }
};
vector<node> ljb[100005];
int dis[100005];
int pos[100005];
int ans[100005];
struct qry{
   int cur,id;
   bool friend operator < (const qry &a,const qry &b){
      return a.cur>b.cur;
   }
}query[100005];
void solve(){
   queue<int> q;
   q.push(n);
   while(!q.empty()){
      int cur=q.front();
      q.pop();
      for(int i=pos[cur];i<ljb[cur].size();i++){
         int v=ljb[cur][i].v;
         if(ljb[cur][i].a<dis[cur]){
            break;
         }
         pos[cur]++;
         if(dis[v]>ljb[cur][i].b){
            dis[v]=ljb[cur][i].b;
            q.push(v);
         }
      }
   }
   return;
}
signed main(){
   scanf("%d%d",&n,&m);
   for(int i=1;i<=m;i++){
      int u,v,a,b;
      scanf("%d%d%d%d",&u,&v,&a,&b);
      ljb[v].push_back(node{u,100000000-b,100000000-a});
   }
   for(int i=1;i<=n;i++){
      sort(ljb[i].begin(),ljb[i].end());
   }
   scanf("%d",&q);
   for(int i=1;i<=q;i++){
      query[i].id=i;
      scanf("%d",&query[i].cur);
      query[i].cur=100000000-query[i].cur;
   }
   sort(query+1,query+1+q);
   for(int i=1;i<=n;i++){
      dis[i]=2e9;
   }
   for(int i=1;i<=q;i++){
      // printf("Start %d\n",i);
      dis[n]=query[i].cur;
      solve();
      if(dis[1]==2000000000){
         ans[query[i].id]=-1;
      }
      else{
         ans[query[i].id]=100000000-dis[1];
      }
   }
   for(int i=1;i<=q;i++){
      printf("%d\n",ans[i]);
   }
   return 0;
}

```

---

## 作者：dsidsi (赞：0)

考虑每次的答案只与最后一次搭乘的巴士有关。所以需要算出搭乘第$i$趟巴士的最晚出发时间$g_i$。同时算出到达$j$点的最晚出发时间$f_j$。用类似最短路的方法相互更新$g$和$f$即可：

首先将巴士按出发排序。用队列中到达时间小于本次出发时间的巴士更新$f$。然后用$min(e[i].s,f[e[i].a])$更新本次巴士的$g$值。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 100005, Inf = 1 << 30;

int n, m, k;
int f[maxn], g[maxn * 3], ans[maxn];

struct edge {
	int u, v, x, y;
	bool operator < (const edge &a) const {
		return x < a.x;
	}
} e[maxn * 3];

priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
pair<int, int> p[maxn * 3], qry[maxn];
int cnt;

inline int gi()
{
	char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	int sum = 0;
	while ('0' <= c && c <= '9') sum = sum * 10 + c - 48, c = getchar();
	return sum;
}

int main()
{
	freopen("bus.in", "r", stdin);
	freopen("bus.out", "w", stdout);
	
	n = gi(); m = gi();
	for (int i = 1; i <= m; ++i) e[i] = (edge) {gi(), gi(), gi(), gi()};
	sort(e + 1, e + m + 1);

	fill(f + 1, f + n + 1, -1); f[1] = Inf;
	pair<int, int> t;
	for (int i = 1; i <= m; ++i) {
		while (!q.empty() && q.top().first <= e[i].x) {
			t = q.top(); q.pop();
			f[e[t.second].v] = max(f[e[t.second].v], g[t.second]);
		}
		g[i] = min(e[i].x, f[e[i].u]);
		q.push(make_pair(e[i].y, i));
		if (e[i].v == n) p[++cnt] = make_pair(e[i].y, g[i]);
	}

	k = gi();
	for (int i = 1; i <= k; ++i) qry[i] = make_pair(gi(), i);
	sort(qry + 1, qry + k + 1);
	sort(p + 1, p + cnt + 1);
	for (int i = 1, j = 1, Max = -1; i <= k; ++i) {
		while (j <= cnt && p[j].first <= qry[i].first) Max = max(Max, p[j].second), ++j;
		ans[qry[i].second] = Max;
	}

	for (int i = 1; i <= k; ++i) printf("%d\n", ans[i]);
	
	return 0;
}
```

---

## 作者：PCCP (赞：0)

## 思路

看到要求可行的最晚时间，以及大量询问。不难想到整体二分，但是二分要怎么去快速求出最晚可行时间，或者说是有向图的连通性我并没有想到怎么做。

图论似乎也不怎么搭边，那只能先想暴力，再看看有没有什么性质。

暴力要正向遍历不好更新答案，二分还多带 $ \log_2{T} $，但是如果反向建图，就可以直接遍历求每个点最晚抵达时刻。

比较好想到的是，对于某个询问，如果一条边的抵达时刻大于截止时刻，那是没有贡献的。这样可以减少我们遍历的边的数量，但对于暴力做法有点小优化。

然后推敲一下样例，可以发现：只要存在至少一条合法路径，随着时间的推移，在某个时刻答案由无解变为非严格单增的。这是比较显然的，那如果我们把询问离线排序，是否可以更快呢？

然而我们该遍历的边还是要遍历，并没有更快。考虑能否让每一条边只遍历一次，发现因为答案是按时间递增顺序单增的，所以每次遍历的边集一定包含于下一次遍历的边集，而且一条边更新了起始点的答案后已经没有作用，那就完全可以踢掉，不需要再遍历。

但是这个实现有些需要注意的。比如说在遍历下一个节点前要把这条边删掉，不然在给定时刻区间内，两条边可能互达又给你遍历回来了。还有，因为每次遍历都是贪心取最优解，剩下的非法路径一定是更劣，所以两不同时刻内的最优路径不可能重合，每次只要从根节点出发看能不能更新即可。

之前有的题解说时间复杂度是线性的。虽然遍历是 $ O(m) $ 的，但是要给边排序，所以时间复杂度：$ O(m\log_2{m}) $。

## 代码：

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>
#include<queue>
#include<stack>
#include<list>
#include<set>
using namespace std;
typedef pair<int,int> PII;
const int N=1e5+10;
const int M=3e5+10;
const int INF=1e9;
int n,m,q,dist[N],ans[N];
PII que[N];
struct edge{
	int a,b,x,y;
}e[M];
bool cmp(edge x,edge y){
	if(x.y==y.y)
		return x.x<y.x;
	return x.y<y.y;
}
vector<int> sov[N];
void dfs(int x){
	for(int i=1;i<=N;i++){
		if(sov[x].empty()||e[sov[x].back()].y>dist[x])
			break;
		int v=e[sov[x].back()].a;
		dist[v]=max(dist[v],e[sov[x].back()].x);
		sov[x].pop_back();
		dfs(v);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d%d",&e[i].a,&e[i].b,&e[i].x,&e[i].y);
	sort(e+1,e+m+1,cmp);
	for(int i=m;i>=1;i--)
		sov[e[i].b].push_back(i);
	scanf("%d",&q);
	for(int i=1;i<=q;i++){
		scanf("%d",&que[i].first);
		que[i].second=i;
	}
	sort(que+1,que+q+1);
	for(int i=1;i<n;i++)
		dist[i]=-INF;
	for(int i=1;i<=q;i++){
		dist[n]=que[i].first;
		dfs(n);
		ans[que[i].second]=dist[1];
	}
	for(int i=1;i<=q;i++){
		if(ans[i]<0)
			puts("-1");
		else
			printf("%d\n",ans[i]);
	}
}
```

---

