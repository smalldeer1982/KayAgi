# Communication Towers

## 题目描述

There are $ n $ communication towers, numbered from $ 1 $ to $ n $ , and $ m $ bidirectional wires between them. Each tower has a certain set of frequencies that it accepts, the $ i $ -th of them accepts frequencies from $ l_i $ to $ r_i $ .

Let's say that a tower $ b $ is accessible from a tower $ a $ , if there exists a frequency $ x $ and a sequence of towers $ a=v_1, v_2, \dots, v_k=b $ , where consecutive towers in the sequence are directly connected by a wire, and each of them accepts frequency $ x $ . Note that accessibility is not transitive, i. e if $ b $ is accessible from $ a $ and $ c $ is accessible from $ b $ , then $ c $ may not be accessible from $ a $ .

Your task is to determine the towers that are accessible from the $ 1 $ -st tower.

## 样例 #1

### 输入

```
6 5
3 5
1 2
2 4
2 3
3 3
4 6
1 3
6 1
3 5
3 6
2 3```

### 输出

```
1 3 5 6```

## 样例 #2

### 输入

```
3 1
2 3
1 4
1 1
1 3```

### 输出

```
1```

## 样例 #3

### 输入

```
5 5
1 3
2 3
2 2
3 5
2 4
1 2
2 3
3 4
4 1
4 5```

### 输出

```
1 2 3 4 5```

# 题解

## 作者：有趣的问题 (赞：6)

### 题目分析

看到这种“只在一段时间出现”的问题，很容易想到线段树分治。而维护连通性显然可以用并查集，为了在线段树上实现撤销操作要用按秩合并不带路径压缩的并查集。但是怎么确定是否和 $1$ 连通呢？我们在叶子节点处理这一信息。考虑在叶子节点处我们给 $1$ 在并查集上的根一个标记，在并查集撤销的时候下传标记，这样就能找到彼时所有满足题意的点了。但还有一点细节：并查集在合并的时候可能某一边已经有标记了，这时候需要减去已有的标记避免后面加上的时候造成混淆。

### 代码

```c++
#include <bits/stdc++.h>
#define int long long
#define lid (id<<1)
#define rid (id<<1|1)
#define mid ((tr[id].l+tr[id].r)>>1) 
using namespace std;
int n,m,top=2e5,L[200005],R[200005],fa[200005],dep[200005],tp,teg[200005];
struct tree{
	int l,r;
	vector<pair<int,int> > e;
}tr[800005];
void build(int id,int l,int r){
	tr[id].l=l,tr[id].r=r;
	if(l==r)return;
	build(lid,l,mid),build(rid,mid+1,r);
}
void modify(int id,int l,int r,int u,int v){
	if(tr[id].l==l&&tr[id].r==r){
		tr[id].e.push_back(make_pair(u,v));
		return;
	}
	if(r<=mid)modify(lid,l,r,u,v);
	else if(l>mid)modify(rid,l,r,u,v);
	else modify(lid,l,mid,u,v),modify(rid,mid+1,r,u,v);
}
int find(int x){
	if(x==fa[x])return x;
	return find(fa[x]);
}
struct node{
	int u,v,su,sv;
}stk[400005];
void merge(int u,int v){
	if(find(u)==find(v))return;
	u=find(u),v=find(v);
	if(dep[u]>dep[v])swap(u,v);
	stk[++tp]=node{u,v,dep[u],dep[v]};
	teg[u]-=teg[v],fa[u]=v,dep[v]+=dep[u]==dep[v];
}
void redo(node k){
	fa[k.u]=k.u,dep[k.v]=k.sv;teg[k.u]+=teg[k.v];
}
void dfs(int id){
	int pre=tp;
	for(int i=0;i<tr[id].e.size();i++){
		merge(tr[id].e[i].first,tr[id].e[i].second);
	}
	if(tr[id].l==tr[id].r)teg[find(1)]++;
	else dfs(lid),dfs(rid);
	while(tp!=pre)redo(stk[tp--]);
}
signed main(){
	cin>>n>>m;build(1,1,top);
	for(int i=1;i<=n;i++)scanf("%lld%lld",&L[i],&R[i]);
	for(int i=1;i<=m;i++){
		int u,v;scanf("%lld%lld",&u,&v);
		int ll=max(L[u],L[v]),rr=min(R[u],R[v]);
		if(ll<=rr)modify(1,ll,rr,u,v);
	}
	for(int i=1;i<=n;i++)fa[i]=i;
	dfs(1);
	for(int i=1;i<=n;i++){
		if(teg[i])cout<<i<<' ';
	}
	return 0;
}

```



---

## 作者：Walrus (赞：2)

对于某些边在一段时间内出现的问题，一般采用线段树分治的方法，线段树分治一般在可撤销并查集的基础上实现。

这题比较巧妙，其实是线段树分治板子加上一个小技巧。

注意到有「$i$ 和 1 连通」的要求，发现在叶子节点时，不借助其它东西无法完成答案统计。

这个时候有一个小技巧：引入标记数组。

我们引入 $tag_i$ 表示点 $i$ 对应集合的根曾经是否与点 1 连通。

发现在并查集合并和撤销时可以非常容易地维护 $tag$ 信息。

具体地，在 $Merge$ 时，假设有操作 $fa_x=y$，则要保证 $x$ 的 $tag$ 信息不发生变化，就要考虑如何维护此时的 $tag_x$。

发现如果将 $x$ 和 $y$ 合并时，由于二者之前位于不同集合，而现在 $y$ 为 $x$ 所在集合的根。故将 $tag_x$ 减去 $tag_y$ 后，二者信息可正确维护。

在线段树上 $ask$ 时，到叶子节点时，将节点 $1$ 此时所在集合根的 $tag$ 加上 $1$。

同样的，在 $Undo$ 时，将 $tag_x$ 做相反操作，即将 $tag_x$ 加上 $tag_y$。

最后若某个点的 $tag$ 大于 0 则此点在某时刻与 1 相连通。

时间复杂度为正常的线段树分治复杂度 $O(M \log^2N)$。

**线段树分治时尤其注意并查集数组的大小**。可以像我一样开 2e6，怎么都不会 RE。

顺带一提，本题给的是**点**的出现时间，故连边时注意左右区间，可以参考代码实现。

```cpp
#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++i)
#define pb push_back
#define PII pair<int, int>

using namespace std;
const int N = 2e6 + 5;
int n, m, k, u[N], v[N], l[N], r[N], ans[N], tag[N];
vector<PII> e[N * 2];//没必要再乘2了

struct Union {
	int fa[N], siz[N];
	stack<PII> st;

	void init() {
		rep(i, 1, n) fa[i] = i, siz[i] = 1;
	}

	int get(int x) {
		return x == fa[x] ? x : get(fa[x]);
	}

	void merge(int x, int y) {
		x = get(x), y = get(y);
		if(x == y) return;
		if(siz[x] > siz[y]) swap(x, y);
		st.push({x, y});
		fa[x] = y, siz[y] += siz[x];
		tag[x] -= tag[y];
	}


	void undo(int last) {
		while(st.size() > last) {
			int x = st.top().first, y = st.top().second;
			st.pop();
			fa[x] = x, siz[y] -= siz[x];
			tag[x] += tag[y];
		}
	}

} DSU;

stack<PII> T;

struct SegmentTree {
#define ls (p << 1)
#define rs (p << 1 | 1)
#define mid (l + r >> 1)

	void upd(int p, int l, int r, int L, int R, int u, int v) {
		if(L > r || l > R) return;
		if(L <= l && r <= R)
			return e[p].pb({u, v}), void();
		upd(ls, l, mid, L, R, u, v), upd(rs, mid + 1, r, L, R, u, v);
	}

	void ask(int p, int l, int r) {
		int S = DSU.st.size();
		for(auto ed : e[p]) {
			int x = ed.first, y = ed.second;
			DSU.merge(x, y);
		}
		if(l == r) ++tag[DSU.get(1)];
		else ask(ls, l, mid), ask(rs, mid + 1, r);
		DSU.undo(S);
	}
} SGT;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr), cout.tie(nullptr);

	int mx = 0;


	cin >> n >> m;
	DSU.init();
	rep(i, 1, n) cin >> l[i] >> r[i], mx = max(mx, r[i]);
	rep(i, 1, m) cin >> u[i] >> v[i];
	rep(i, 1, m) SGT.upd(1, 0, mx, max(l[u[i]], l[v[i]]), min(r[u[i]], r[v[i]]), u[i], v[i]);

	SGT.ask(1, 0, mx);
	rep(i, 1, n) if(tag[i]) cout << i << ' ';

}

```

---

## 作者：MornStar (赞：1)

## CF1814F Communication Towers 题解

[宣传自己写的线段树分治博客。](https://www.luogu.com.cn/article/8wdkvd1x)

看见一个点只在某段时间出现，果断线段树分治。

通过可撤销并查集维护连通性。

这里涉及到一个新问题，也是线段树分治的一个 trick：标记维护。

注意到需要给 $1$ 所在的树上的每个结点打上标记，这并不好办。

考虑只给树的根结点增加标记。在撤销操作（其实也是分裂子树）时下传标记。
![](https://cdn.luogu.com.cn/upload/image_hosting/6wrkhye3.png)

但这样会出现一种情况，一个子树后来连接上带有标记的根（但这个根现在不与 $1$ 相连），则会导致新的子树也被统计进入答案。

考虑一个解决方法，在连接时减去根的标记，撤销时加上。
![](https://cdn.luogu.com.cn/upload/image_hosting/bobtkhqs.png)

这样，只要根结点的标记在途中没有变化，就不会多下传。

```cpp
//merge
del_tmp merge(int x,int y){
  int X=find(x),Y=find(y);
  if(X==Y)	return{0,0};
  if(d[X]>d[Y])	swap(X,Y);
  del_tmp ret={X,d[X]==d[Y]};
  d[Y]+=(d[X]==d[Y]),tag[X]-=tag[Y],fa[X]=Y;
  return ret;
}
```
```cpp
//delete
while(st.tp>tp){
  del_tmp tmp=st.top();st.pop();
  if(!tmp.num)	continue;
  dsu.tag[tmp.num]+=dsu.tag[dsu.fa[tmp.num]];
  dsu.d[dsu.fa[tmp.num]]-=tmp.d;
  dsu.fa[tmp.num]=tmp.num;
}
```

下传标记的问题至此完美解决，剩的就是普通线段树分治的操作了。

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,m,mx,l[N],r[N],ans=0x3f3f3f3f;
template<typename T,int siz> struct my_stack{
	T st[siz];
	int tp=0;
	void push(T x){st[++tp]=x;}
	void pop(){
		if(!tp)	cerr<<"THE STACK IS EMPTY!\n";
		else	tp--;
	}
	T top(){
		if(!tp)	cerr<<"THE STACK IS EMPTY!\n";
		else	return st[tp];
	}
	void clear(){tp=0;}
	bool empty(){return !tp;}
};
struct del_tmp{int num,d;};
template<int N>struct DSU{
	int fa[N],tag[N],d[N];
	void clear(int n){for(int i=1;i<=n;i++)	fa[i]=i,tag[i]=0,d[i]=1;}
	int find(int x){return (fa[x]==x?x:find(fa[x]));}
	del_tmp merge(int x,int y){
		int X=find(x),Y=find(y);
		if(X==Y)	return{0,0};
		if(d[X]>d[Y])	swap(X,Y);
		del_tmp ret={X,d[X]==d[Y]};
		d[Y]+=(d[X]==d[Y]),tag[X]-=tag[Y],fa[X]=Y;
		return ret;
	}
	bool same(int x,int y){return find(x)==find(y);}
};
struct edge{int u,v;};
struct segment_tree{
	DSU<N> dsu;
	my_stack<del_tmp,N<<1>st;
	segment_tree(){dsu.clear(N-1);}
	struct segment_tree_node{vector<edge>v;}t[N<<2];
	inline int ls(int x){return x<<1;};
	inline int rs(int x){return x<<1|1;};
#define mid ((l+r)>>1)
	void change(int p,int l,int r,int re_l,int re_r,edge val){
		if(re_l<=l&&r<=re_r)	return t[p].v.push_back(val),void();
		else{
			if(re_l<=mid)	change(ls(p),l,mid,re_l,re_r,val);
			if(mid<re_r)	change(rs(p),mid+1,r,re_l,re_r,val);
		}
	}
	void query(int p,int l,int r){
		//		cerr<<p<<" "<<l<<" "<<r<<"\n";
		int tp=st.tp;
		for(auto it:t[p].v)	st.push(dsu.merge(it.u,it.v));
		if(l==r)	dsu.tag[dsu.find(1)]++;
		else	query(ls(p),l,mid),query(rs(p),mid+1,r);
		while(st.tp>tp){
			del_tmp tmp=st.top();st.pop();
			if(!tmp.num)	continue;
			dsu.tag[tmp.num]+=dsu.tag[dsu.fa[tmp.num]];
			dsu.d[dsu.fa[tmp.num]]-=tmp.d;
			dsu.fa[tmp.num]=tmp.num;
		}
	}
}T;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=n;i++)	cin>>l[i]>>r[i],mx=max(mx,r[i]);
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		if(max(l[u],l[v])<=min(r[u],r[v]))	T.change(1,1,mx,max(l[u],l[v]),min(r[u],r[v]),{u,v});
	}
	T.query(1,1,mx);
	for(int i=1;i<=n;i++){
		if(T.dsu.tag[i])	cout<<i<<" ";
	}
}
```

时间复杂度 $O(m\log{n}\log{R_{imax}})$。

---

## 作者：shinkuu (赞：1)

挺巧妙的题。

首先可以根据每个点出现时间知道每条边出现时间。然后就是一个 SGT 分治了……吗？发现如果对于每个时刻记录此时有哪些点和 $1$ 联通，每次都要 $O(n)$ 的时间扫一遍，这样肯定是不行的。

那么怎么办呢？于是考虑在并查集合并一次的时候判断合并中的两个点中的一个是否与 $1$ 联通，然后传递答案。

说来简单，但是怎么实现这一过程呢？作者一开始想的是，对于线段树的每一棵子树搜一遍，然后清空。这样做的复杂度似乎是 $O(n\log^2n)$ 的，但是不太好写。

然后参考题解，学到了一种相当巧妙的做法。就是对于每个点记录当前累计在多少个叶子节点被记录，打上一个标记，每次并查集撤销的时候传递标记，合并的时候取消标记。具体参考代码理解。

code：

```cpp
int n,m,k=2e5,top,st[N][2],c[N],pd[N],L[N],R[N];
mt19937 rnd(time(0));
struct DSU{
	int fa[N];
	int find(int x){return fa[x]?find(fa[x]):x;}
	il void merge(int x,int y){
		x=find(x),y=find(y);
		if(x==y)return;
		if(c[x]<c[y])swap(x,y);
		pd[x]-=pd[y];
		fa[x]=y,st[++top][0]=x,st[top][1]=y;
	}
}D;
struct SGT{
	int tot,head[N<<2];
	struct node{int u,v,nxt;}e[M];
	il void add(int u,int v,int o){e[++tot]={u,v,head[o]},head[o]=tot;}
	void update(int l,int r,int o,int x,int y,int u,int v){
		if(x>y)return;
		if(l>=x&&r<=y)return add(u,v,o);
		int mid=(l+r)>>1;
		if(x<=mid)update(l,mid,o<<1,x,y,u,v);
		if(y>mid)update(mid+1,r,o<<1|1,x,y,u,v);
	}
	void solve(int l,int r,int o){
		int tmp=top;
		go(i,o)D.merge(e[i].u,e[i].v);
		if(l==r){
			pd[D.find(1)]++;
			while(top>tmp){
				int u=st[top][0],v=st[top--][1];
				pd[u]+=pd[v],D.fa[u]=0;
			}
			return;
		}
		int mid=(l+r)>>1;
		solve(l,mid,o<<1),solve(mid+1,r,o<<1|1);
		while(top>tmp){
			int u=st[top][0],v=st[top--][1];
			pd[u]+=pd[v],D.fa[u]=0;
		}
	}
}T;
void Yorushika(){
	scanf("%d%d",&n,&m);
	rep(i,1,n)scanf("%d%d",&L[i],&R[i]),c[i]=rnd();
	rep(i,1,m){
		int u,v;scanf("%d%d",&u,&v);
		T.update(1,k,1,max(L[u],L[v]),min(R[u],R[v]),u,v);
	}
	T.solve(1,k,1);
	rep(i,1,n)if(pd[i])printf("%d ",i);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：iChen (赞：1)

巨佬们怎么都打的线段树分治？！

## 一种很清奇的思路：树状 DP

（虽然这是个图，但感觉叫它树状也没啥问题）

或者说这个算法是 DFS。

我们先看一下下面这个样例：

![](https://cdn.luogu.com.cn/upload/image_hosting/8u077b1p.png)

每个圆圈里的数字代表编号，下面的中括号代表工作频率。

重审题意，要求只要在某一频率下一个点能和 $1$ 联通，那么就属于答案。

那么我们就可以从点 $1$ 开始，带着点 $1$ 的频率来 DFS。

比如说，我们来到了 $2$ 号点，发现 $2$ 号点在 $[3,5]$ 的频率下可以工作。

那么我们取点 $1$ 和点 $2$ 共同包含的频率：$[3,5]$。表示在频率 $[3,5]$ 下点 $1$ 和点 $2$ 可以连通。

再从点 $2$ 以 $[3,5]$ 的频率往外 DFS，直到到某个点没有共同覆盖的频率，这时候停止。途中经过的点就都算作答案。

再从点 $1$ 向点 $4$ 拓展，取到共同覆盖频率 $[2,8]$ 。

大体思路是这样，但我们需要考虑出口和剪枝。

比如我们从点 $1$ 走点 $4$ 来到了点 $2$，频率为 $[3,4]$，但是我们之前已经从点 $2$ 以 $[3,5]$ 的频率往外搜索过了，$[3,4]$ 包含在了 $[3,5]$ 里面，再往下搜是没有意义的，所以剪枝掉。

但我们如果以 $[4,8]$ 的频率来到了点 $2$，此时这段频率不全覆盖在之前的 $[3,5]$ 中，所以我们以 $[6,8]$ 的频率往下搜索尝试得到新答案。

到这里思路就已经结束了，理论可行，上代码：

## Code
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 2e5 + 5, M = N << 1;
int n, m;
bool ans[N];
vector <int> road[N];
vector <pair <int, int>> once[N];

inline pair <int, int> get (int p, pair <int, int> x) {
	x.first = max(x.first, once[p][0].first),
	x.second = min(x.second, once[p][0].second);
	for (int i = 1; i < once[p].size(); i ++) {
		pair <int, int> th = once[p][i];
		if (th.first <= x.first and th.second >= x.second) return {-1, 0};
		else if (th.first > x.second or th.second < x.first) continue;
		else if (x.first < th.first and x.second <= th.second) {
			x.second = th.first - 1;
		}
		else if (th.first <= x.first and th.second < x.second) {
			x.first = th.second + 1;
		}
	}
	return x;
}

void dfs (int p, int Jn, pair <int, int> now) {
	pair <int, int> g = get(p, now);
	if (g.first == -1) return;
	if (g.first > g.second) return;
	once[p].push_back(g);
	ans[p] = 1;
	for (int i = 0; i < road[p].size(); i ++) {
		if (road[p][i] != Jn) dfs(road[p][i], p, g);
	}
}

int main () {
	cin >> n >> m;
	int u, v;
	for (int i = 1; i <= n; i ++) {
		cin >> u >> v;
		once[i].push_back({u, v});
	}
	for (int i = 1; i <= m; i ++) {
		cin >> u >> v;
		road[u].push_back(v);
		road[v].push_back(u);
	}
	dfs(1, 0, once[1][0]);
	for (int i = 1; i <= n; i ++) {
		if (ans[i]) cout << i << ' ';
	}
	return 0;
}
```

---

## 作者：bluewindde (赞：0)

注意到联考考了 [CF687D](https://www.luogu.com.cn/problem/CF687D)，直接想到线段树分治 + 可撤销并查集。

考虑维护连通性，一种方法是线段树分治到叶子时枚举并查集中与 $1$ 连通的点并打上标记，显然这样时间复杂度是错的。

对上述操作打懒标记，在并查集撤销时下放标记，标记 $w_u$ 的含义是对于以 $u$ 为根的并查集内的点，存在 $w_u$ 个频率使得该频率下这个点与 $1$ 连通。

考虑合并 $f_v = u$，为了撤销时保证 $w_v$ 正确，需要容斥 $w_v \leftarrow w_v - w_u$。

注意线段树分治从区间 $[1, V]$ 开始，$V = 2 \cdot 10^5$ 是值域。

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int V = 2e5;

int n, m;
int lb[200005];
int rb[200005];
struct edge {
    int u, v, l, r;
} e[400005];

int f[200005];
int siz[200005];
int w[200005];
int sta[200005], tail;
static inline int find(int x) { return f[x] == x ? x : find(f[x]); }
static inline void merge(int u, int v) {
    int uu = find(u), vv = find(v);
    if (uu == vv)
        return;
    if (siz[uu] < siz[vv])
        swap(uu, vv);
    sta[++tail] = vv;
    f[vv] = uu;
    w[vv] -= w[uu];
    siz[uu] += siz[vv];
}
static inline void undo() {
    int v = sta[tail--];
    int u = find(v);
    siz[u] -= siz[v];
    w[v] += w[u];
    f[v] = v;
}

vector<int> d[800005];
static inline void update(int l, int r, int s, int t, int c, int p) {
    if (l <= s && r >= t) {
        d[p].push_back(c);
        return;
    }
    int mid = (s + t) >> 1;
    if (l <= mid)
        update(l, r, s, mid, c, p << 1);
    if (r > mid)
        update(l, r, mid + 1, t, c, p << 1 | 1);
}
static inline void dfs(int s, int t, int p) {
    int tp = tail;
    for (auto id : d[p])
        merge(e[id].u, e[id].v);
    if (s == t) {
        ++w[find(1)];
        while (tail > tp)
            undo();
        return;
    }
    int mid = (s + t) >> 1;
    dfs(s, mid, p << 1);
    dfs(mid + 1, t, p << 1 | 1);
    while (tail > tp)
        undo();
}

static inline void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> lb[i] >> rb[i];
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        int l = max(lb[u], lb[v]), r = min(rb[u], rb[v]);
        e[i] = {u, v, l, r};
        update(l, r, 1, V, i, 1);
    }
    for (int i = 1; i <= n; ++i) {
        f[i] = i;
        siz[i] = 1;
    }
    dfs(1, V, 1);
    for (int i = 1; i <= n; ++i)
        if (w[i])
            cout << i << ' ';
    cout << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    cout.flush();
    return 0;
}
```

---

## 作者：RDFZchenyy (赞：0)

### 题意简述

给定一张无向图，$n$ 点 $m$ 边。

每个点 $i$ 给定区间 $[l_i,r_i]$，我们称两个点能到，当且仅当存在一个路径使得经过的点的区间交非空，求从 $1$ 号点能到的点的集合。

### 提示

#### 提示 #1

区间限制在边好还是在点好？

#### 解答 #1

在边好，这样可以将原题转化为每条边在一些时间存在，判定 $1$ 号点是否在某个时刻可达 $i$ 号点。

#### 提示 #2

维护联通块必然需要使用并查集。

怎么快速维护出每一时刻的并查集状态？

#### 解答 #2

可撤销并查集和在时间上做线段树分治即可。

### 解法分析

按照提示 #1 与提示 #2，我们将限制放在边上，并做线段树分治。

现在问题转化为，是否存在一个时刻，使得 $1$ 号点和 $i$ 号点联通？

**（以上与其他题解做法大致相同）**

接下来我们考虑**直接存储**全部时刻的信息，接着再判断。

据此题目转化为，找到一种算法，支持合并连通块，基本支持查询某一时刻的并查集状态。

用可持久化左偏树（可并堆）来维护小根堆可以实现这样的操作。

当完成全部的操作后，我们自全部根向下下放是否某一时刻根为 $1$ 的标记，这样在线性时间内判断。

综合复杂度 $O(m\log^2 n)$，可以通过本题。

另注：使用随机堆亦可通过本题。

### 参考代码

```cpp
// ...
void add(int id,int l,int r,int tl,int tr,int val){
    if(tl<=l&&r<=tr) seg[id].push_back(val);
    else{
        int mid=(l+r)>>1;
        if(!(tl>mid)) add((id<<1),l,mid,tl,tr,val);
        if(!(tr<=mid)) add((id<<1)|1,mid+1,r,tl,tr,val);
    }
    return;
}

void solve(int id,int l,int r){
    for(int i:seg[id]){
        int x=u[i],y=v[i];
        int fx=find(x),fy=find(y);
        if(fx==fy) su[++tp]=-1,sv[tp]=-1;
        else{
            su[++tp]=(sz[fx]>=sz[fy])?fx:fy;
            sv[tp]=fx+fy-su[tp];
            fa[sv[tp]]=su[tp],sz[su[tp]]+=sz[sv[tp]];
            sid[tp]=rt[su[tp]];
            rt[su[tp]]=merge(rt[su[tp]],rt[sv[tp]]);
            rtv.push_back(rt[su[tp]]);
        } 
    }
    if(l!=r){
        int mid=(l+r)>>1;
        solve((id<<1),l,mid);
        solve((id<<1)|1,mid+1,r);
    }
    for(int i:seg[id]){
        if(su[tp]+1) sz[su[tp]]-=sz[sv[tp]],fa[sv[tp]]=sv[tp],rt[su[tp]]=sid[tp];
        --tp;
    }
    return;
}

void dfs(int u,int dis){
    if((t[u].val==1&&dis)||(!u)) return;
    ans[t[u].val]=1; t[u].val=1; 
    dfs(t[u].ch[0],dis+1),dfs(t[u].ch[1],dis+1);
    return;
}

int main(){
    // ...
    for(int i=1;i<=m;i++){
        // ...
        if(std::max(vl[u[i]],vl[v[i]])>std::min(vr[u[i]],vr[v[i]])) continue;
        add(1,1,f,std::max(vl[u[i]],vl[v[i]]),std::min(vr[u[i]],vr[v[i]]),i);
    }
    for(int i=1;i<=n;i++) fa[i]=i,sz[i]=1,rt[i]=nnode(i),rtv.push_back(rt[i]);
    solve(1,1,f);
    for(int i:rtv){
        if(t[i].val!=1) continue;
        dfs(i,0);
    }
    for(int i=1;i<=n;i++) if(ans[i]) std::cout<<i<<' ';
    std::cout<<'\n';

    return 0;
}
```

---

## 作者：wujingfey (赞：0)

# 题面

给定一个 $n$ 个点 $m$ 条边的无向图，其中每个点会在 $[l,r]$ 这段时间出现。输出**哪些点能在某个时间 $x$ 和 $1$ 联通**。

# 题解

要解决这道题，你需要一些前置知识：

1. 线段树分治。
2. 可撤销并查集。

为了更好理解本题，还需要用到**差分思想**。那么正文开始。

------

看到**点在一个时间段出现**这个条件，首先联想到线段树分治。在线段树分治模板中，是**边在一段时间内出现又消失**，本题是点，但为了方便我们可以强制转化成边——在读入边的时候，这条边的存在时间就是**两个点出现时间的交集**。

现在我们知道了每条边的出现时间，然后**在时间轴建立线段树**，然后把边挂在树上跑板子。

这道题是紫的地方是**如何判断点是否与 $1$ 联通**？这时候可以用差分的思想来理解。

搜到叶子节点后，暴力对**所有与 $1$ 相连的点**是可行，但不优秀的。于是有个很妙的方法，就是**在 $1$ 所在的可撤销并查集的根节点的 $tag$ 直接 $+1$ 即可**。如此，在之后撤销操作的时候，就会把影响 push_down 给儿子们。

但有个 bug，就是在合并 $x,y$ 的时候，如果 $y$ 的子树已经被影响，但 $x$ 的子树没有。直接合并 $x$ 本来没有被影响，但未来分裂后可能也会得到 $y$ 的影响。

例如：

```
合并前：tag[y]=1,tag[x]=0
合并后：tag[y]=1,tag[x]=0
分裂后：tag[y]=1,tag[x]=1
```
这时候 $x$ 无端多出来 $y$ 的影响。所以**在合并 $x,y$ 的时候，给 $x$ 减去 $y$ 的影响**。

**在本质上，我的 $tag[y]$ 只是给当前 $y$ 的子树 $+1$，所以不该被影响的地方，我在根节点上差分 $-1$，这样求前缀和后就可以保证正确性了**。

# CODE:
```
#include<bits/stdc++.h>
using namespace std;
const int N=4e5+5;
int n,m,cnt,tmx;
struct NODE{
	int l,r;
}a[N];
struct EDGE{
	int x,y,s,t;
}e[N];
struct TREE{
	int l,r;
	vector<int> v;
}tr[N<<2];
void build(int p,int l,int r){
	tr[p].l=l, tr[p].r=r;
	tr[p].v.clear();
	if(l==r) return;
	int mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
}
void ins(int p,int l,int r,int i){
	if(l<=tr[p].l && tr[p].r<=r){
		tr[p].v.push_back(i);
		return;
	}
	int mid=(tr[p].l+tr[p].r)>>1;
	if(l<=mid) ins(p<<1,l,r,i);
	if(mid<r) ins(p<<1|1,l,r,i);
}
int fa[N],tag[N],high[N],tp;
struct ST{
	int x,y,f;
}st[N];
int find(int x){
	if(fa[x]==x) return x;
	return find(fa[x]);
}
void merge(int x,int y){
	x=find(x),y=find(y);
	if(x==y) return;
	if(high[x]>high[y]) swap(x,y);
	fa[x]=y;
	st[++tp]={x,y,(high[x]==high[y])};
	if(high[x]==high[y]) high[y]++;
	tag[x]-=tag[y];//树上差分 
}
void solve(int p){
	int nw=tp;
	for(auto i:tr[p].v){
		int x=e[i].x, y=e[i].y;
		merge(x,y);
	}
	if(tr[p].l==tr[p].r){//叶子 
		int x=find(1);
		tag[x]++;
	}else{
		solve(p<<1);
		solve(p<<1|1);
	}
	while(tp>nw){
		high[st[tp].y]-=st[tp].f;
		fa[st[tp].x]=st[tp].x;
		tag[st[tp].x]+=tag[st[tp].y];
		tp--;
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i].l>>a[i].r;
		tmx=max(tmx,a[i].r);
		fa[i]=i, high[i]=1;
	}
	for(int i=1;i<=m;i++){
		int x,y; cin>>x>>y;
		if(x>y) swap(x,y);
		if(a[x].l<a[y].l){//点时间段->边时间段 
			if(a[y].l<=a[x].r) e[++cnt]={x,y,a[y].l,min(a[x].r,a[y].r)};
			if(a[y].l>a[x].r) continue;
		}else{
			if(a[y].r>=a[x].l) e[++cnt]={x,y,a[x].l,min(a[x].r,a[y].r)};
			if(a[y].r<a[x].l) continue;
		}
	}
	build(1,1,tmx+10);//时间上届稍微开大点，防止暴毙 
	for(int i=1;i<=cnt;i++){
		ins(1,e[i].s,e[i].t,i);//插入边 
	}
	solve(1);
	for(int i=1;i<=n;i++){
		if(tag[i]) cout<<i<<'\n';
	}
	return 0;
}
```

---

## 作者：Graphcity (赞：0)

注意到「在一段时间出现」以及「 $i$ 跟 1 连通」这两个条件，容易想到线段树分治 + 可撤销并查集。

在线段树分治的过程中，我们给每个点设一个权值，并用一个点到对应并查集所在根的路径权值和来刻画它是否曾经与 1 连通。

合并 $x,y$ 时，假设我们要让 $fa_x=y$，那么就需要让 $h_x\gets h_x-h_y$ 以保证 $x$ 的子树内权值不发生变化。

在线段树分治的叶子处（也就是每个时间点处），让结点 1 所在并查集的根结点 $h$ 值加上 1。

在撤销边 $(x,y)$ 使，假设原来的 $fa_x=y$，注意到撤销边并不改变点的权值，所有需要让 $h_x\gets h_x+h_y$。

总时间复杂度 $O(m\log^2 n)$。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e5;

int n,m,vis[Maxn+5],fa[Maxn+5],h[Maxn+5],siz[Maxn+5];
inline int Find(int x) {return fa[x]==x?x:Find(fa[x]);}
vector<int> v[Maxn+5],t[Maxn*4+5]; stack<int> st;
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)

inline void Modify(int nl,int nr,int l,int r,int p,int k)
{
    if(l<=nl && nr<=r) {t[p].push_back(k); return;}
    int mid=(nl+nr)>>1;
    if(l<=mid) Modify(nl,mid,l,r,ls(p),k);
    if(r>mid) Modify(mid+1,nr,l,r,rs(p),k);
}
inline void Merge(int x,int y)
{
    x=Find(x),y=Find(y); if(x==y) return; if(siz[x]>siz[y]) swap(x,y);
    fa[x]=y,siz[y]+=siz[x],h[x]-=h[y],st.push(x);
}
inline void Del()
{
    int x=st.top(),y=fa[x]; st.pop();
    fa[x]=x,siz[y]-=siz[x],h[x]+=h[y];
}
inline void Add(int x) {vis[x]++; for(auto y:v[x]) if(vis[y]) Merge(x,y);}
inline void dfs(int l,int r,int p)
{
    int mid=(l+r)>>1,tmp=st.size();
    for(auto i:t[p]) Add(i);
    if(l==r) h[Find(1)]++; else dfs(l,mid,ls(p)),dfs(mid+1,r,rs(p));
    for(auto i:t[p]) vis[i]--;
    while(st.size()>tmp) Del();
}

int main()
{
    cin>>n>>m;
    For(i,1,n) {int l,r; cin>>l>>r; Modify(1,Maxn,l,r,1,i);}
    For(i,1,m)
    {
        int a,b; cin>>a>>b;
        v[a].push_back(b),v[b].push_back(a);
    }
    For(i,1,n) fa[i]=i,siz[i]=1; dfs(1,Maxn,1);
    For(i,1,n) if(h[i]>0) printf("%d ",i); printf("\n");
    return 0;
}
```

---

