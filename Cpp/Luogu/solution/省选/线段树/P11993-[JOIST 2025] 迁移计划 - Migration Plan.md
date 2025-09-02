# [JOIST 2025] 迁移计划 / Migration Plan

## 题目背景

本题测试点极大，评测时可能需要等待较长时间加载测试点。

## 题目描述




JOI 王国由编号从 $1$ 到 $N$ 的 $N$ 个城市组成。这些城市通过 $N − 1$ 条单向道路连接。具体来说，对于每个 $i = 2, 3, \ldots, N$，存在一条从城市 $i$ 通向城市 $P_i$ 的道路。此处保证 $1 \leq P_i < i$。

每个城市有一个定义好的危险等级。首都（城市 $1$）的危险等级为 $0$。对于城市 $i$（$2 \leq i \leq N$），其危险等级定义为从该城市到城市 $1$ 的路径中经过的道路数量。根据 JOI 王国的结构，从任意城市 $i$ 到城市 $1$ 的路径存在且唯一。

当前，城市 $i$（$1 \leq i \leq N$）居住着 $K_i$ 只海狸。JOI 王国的总统 Bitaro 计划实施海狸迁移计划。该计划将在 $Q$ 天内执行。在第 $j$ 天（$1 \leq j \leq Q$），以下三类事件之一会发生：

- 迁移：当时刻所有居住在危险等级为 $X_j$ 的城市的海狸会迁移到危险等级为 $Y_j$ 的城市，该城市需满足从当前城市出发沿道路行进可达。保证 $0 \leq Y_j < X_j$。根据 JOI 王国的结构，每只海狸的迁移目的地唯一确定。
- 迁入：由于王国外的迁入，城市 $A_j$ 的海狸数量增加 $L_j$。
- 调查： 调查当前时刻城市 $B_j$ 居住的海狸数量。

作为 Bitaro 的下属，你发现无需实地考察即可根据迁移计划信息计算出每次调查事件时的海狸数量。

给定 JOI 王国的结构、各城市当前的海狸数量及迁移计划详情，请编写程序计算每次调查事件的结果。


## 说明/提示


### 样例解释


#### 样例 $1$ 解释
初始时，城市 $1$, $2$, $3$, $4$ 分别有 $1$, $3$, $4$, $3$ 只海狸。这些城市的危险等级分别为 $0$, $1$, $1$, $2$。

- 第 $1$ 天发生调查事件。第一行输出 $1$，表示城市 $1$ 的海狸数量。
- 第 $2$ 天发生迁移事件。城市 $2$ 和 $3$ 的海狸全部迁移到城市 $1$。第 $2$ 天结束时，城市 $1$, $2$, $3$, $4$ 分别有 $8$, $0$, $0$, $3$ 只海狸。
- 第 $3$ 天发生调查事件。第二行输出 $8$。
- 第 $4$ 天发生调查事件。第三行输出 $0$。
- 第 $5$ 天发生迁移事件。城市 $4$ 的海狸全部迁移到城市 $2$。第 $5$ 天结束时，城市 $1$, $2$, $3$, $4$ 分别有 $8$, $3$, $0$, $0$ 只海狸。
- 第 $6$ 天发生调查事件。第四行输出 $3$。

该样例满足子任务 $2\sim 7$ 的限制。

#### 样例 $2$ 解释
初始时，城市 $1$, $2$, $3$ 分别有 $3$, $1$, $4$ 只海狸。这些城市的危险等级分别为 $0$, $1$, $1$。

- 第 $1$ 天发生迁入事件。城市 $2$ 的海狸数量增加 $5$。第 $1$ 天结束时，城市 $1$, $2$, $3$ 分别有 $3$, $6$, $4$ 只海狸。
- 第 $2$ 天发生迁移事件。无海狸迁移，因为不存在危险等级为 $2$ 的城市。
- 第 $3$ 天发生调查事件。第一行输出 $3$。
- 第 $4$ 天发生迁移事件。城市 $2$ 和 $3$ 的海狸全部迁移到城市 $1$。第 $4$ 天结束时，城市 $1$, $2$, $3$ 分别有 $13$, $0$, $0$ 只海狸。
- 第 $5$ 天发生调查事件。第二行输出 $13$。
- 第 $6$ 天发生调查事件。第三行输出 $0$。
后续事件类似发生，此处省略具体描述。

该样例满足子任务 $1\sim 3,7$ 的限制。


#### 样例 $3$ 解释

该样例满足子任务 $2,3,5,7$ 的限制。



### 数据范围
- $2 \leq N \leq 2\,000\,000$。
- $1 \leq P_i < i$（$2 \leq i \leq N$）。
- $0 \leq K_i \leq 100$（$1 \leq i \leq N$）。
- $1 \leq Q \leq 2\,000\,000$。
- $T_j$ 的取值为 $1$, $2$ 或 $3$（$1 \leq j \leq Q$）。
- 若 $T_j = 1$，则 $0 \leq Y_j < X_j \leq N − 1$（$1 \leq j \leq Q$）。
- 若 $T_j = 2$，则 $1 \leq A_j \leq N$，$1 \leq L_j \leq 100$（$1 \leq j \leq Q$）。
- 若 $T_j = 3$，则 $1 \leq B_j \leq N$（$1 \leq j \leq Q$）。
- 至少存在一个 $j$（$1 \leq j \leq Q$）满足 $T_j = 3$。
- 所有输入值为整数。

### 子任务
设城市最大危险等级为 $D$。

- $\text{Subtask 1 (4 pts)}$：$D = 1$。
- $\text{Subtask 2 (8 pts)}$：$N \leq 20$。
- $\text{Subtask 3 (13 pts)}$：$D \leq 20$。
- $\text{Subtask 4 (15 pts)}$：不存在 $T_j = 2$ 的查询，且最多有 $5$ 个 $T_j = 3$ 的查询。
- $\text{Subtask 5 (15 pts)}$：最多有 $5$ 个 $T_j = 3$ 的查询。
- $\text{Subtask 6 (27 pts)}$：不存在 $T_j = 2$ 的查询。
- $\text{Subtask 7 (18 pts)}$：无额外限制。


## 样例 #1

### 输入

```
4
1 1 2
1 3 4 3
6
3 1
1 1 0
3 1
3 2
1 2 1
3 2```

### 输出

```
1
8
0
3```

## 样例 #2

### 输入

```
3
1 1
3 1 4
11
2 2 5
1 2 0
3 1
1 1 0
3 1
3 2
2 3 4
3 3
1 1 0
3 3
3 1```

### 输出

```
3
13
0
4
0
17```

## 样例 #3

### 输入

```
7
1 2 1 3 3 2
5 2 8 9 4 0 5
10
1 3 1
2 4 10
3 2
1 6 3
1 2 0
3 1
3 4
2 5 6
3 5
3 3```

### 输出

```
6
18
19
6
0```

# 题解

## 作者：Aegleseeker_ (赞：6)

来一篇说人话的题解。

bfs 序转区间是没有前途的，因为线段树合并不能直接合并两段不等长的区间，所以不太能每个点都直接维护。

考虑一些智慧的东西。每次合并的时候不直接对位合并，而是直接把 $deep=x$ 的集合整个合并到 $deep=y$ 的集合上，这里直接把对位扔掉。

考虑查询的过程，实际上就是考虑那些子树内的修改，由于所有的修改都被你全提到当前 $deep$ 所对应的集合上了，所以问题转换成集合内子树贡献求和，直接下标 dfn 序，区间求和即可。

综上，每个深度维护一棵以 dfn 序为下标的线段树，合并操作直接线段树合并，修改操作单点改，单点查询直接求该点深度对应的那棵线段树的子树 dfn 区间和。

---

## 作者：Mirasycle (赞：4)

看到深度相关肯定会想到 bfs 序，每次就是把一段区间里面的数加到另一段区间里面。但是你会发现由于是比较整体的一个操作，所以你维护这个 bfs 序其实是没啥用的。所以考虑对于每个深度整体维护一个集合。

这样子每次就是集合合并累加的过程。考虑对于每个深度维护一个线段树，下标为 dfs 序，向上合并就使用线段树合并。然后对于单点查询就是直接对于该深度进行 dfs 序子树查询即可。

时间复杂度 $O(n+m)\log n$。


```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define fi first
#define se second
#define mp make_pair
using namespace std;
typedef long long ll;
const int maxn=2e6+10;
int rt[maxn],c[maxn],dep[maxn],n,m;
int dfn[maxn],sz[maxn],id[maxn],cnt=0;
vector<int> G[maxn];
struct SegmentTree{
	#define mid (l+r>>1)
	int val[maxn*32],ls[maxn*32],rs[maxn*32],tot=0;
	void pushup(int p){ val[p]=val[ls[p]]+val[rs[p]]; }
	void modify(int& p,int l,int r,int x,int v){
		if(!p) p=++tot;
		if(l==r){ val[p]+=v; return ; }
		if(x<=mid) modify(ls[p],l,mid,x,v);
		else modify(rs[p],mid+1,r,x,v);
		pushup(p);
	}
	int query(int p,int l,int r,int ql,int qr){
		if(!p) return 0; int res=0;
		if(ql<=l&&r<=qr) return val[p];
		if(ql<=mid) res+=query(ls[p],l,mid,ql,qr); 
		if(qr>mid) res+=query(rs[p],mid+1,r,ql,qr);
		return res;
	}
	int merge(int p,int q,int l,int r){
		if(!p||!q) return p+q;
		if(l==r){ val[p]+=val[q]; return p; }
		ls[p]=merge(ls[p],ls[q],l,mid);
		rs[p]=merge(rs[p],rs[q],mid+1,r);
		pushup(p); return p;
	}
}seg;
void dfs(int u){
	dfn[u]=++cnt; id[cnt]=u; sz[u]=1;
	for(auto v:G[u]){ 
		dep[v]=dep[u]+1; 
		dfs(v); sz[u]+=sz[v]; 
	}
}
int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n;
	for(int i=2;i<=n;i++){
		int fa; cin>>fa;
		G[fa].pb(i);
	}
	for(int i=1;i<=n;i++) cin>>c[i];
	dfs(1); cin>>m;
	for(int i=1;i<=n;i++)
		seg.modify(rt[dep[i]],1,n,dfn[i],c[i]);
	for(int i=1;i<=m;i++){
		int t; cin>>t;
		if(t==1){
			int X,Y; cin>>X>>Y;
			rt[Y]=seg.merge(rt[Y],rt[X],1,n);
			rt[X]=0;
		}else if(t==2){
			int A,L; cin>>A>>L;
			seg.modify(rt[dep[A]],1,n,dfn[A],L);
		}else{
			int B; cin>>B;
			cout<<seg.query(rt[dep[B]],1,n,dfn[B],dfn[B]+sz[B]-1)<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：Galois_Field_1048576 (赞：2)

为什么不用神奇伟大的 STL？

记录这个树的 Euler 遍历：$I_v = [l_v, r_v]$ 表示 $v$ 节点的区间，$D_v$ 表示 $v$ 节点的深度。对于每一个深度 $D_v = d$，保存一个集合
$$
S_d = \{ (l_v, k_v) : D_v = d \}.
$$
我们来考虑一下操作的转化。

* **迁移**操作：对于每个点 $u$，找到祖先 $a$（当且仅当 $I_u \subset I_a$），并将 $k_u$ 迁移到 $k_a$ 上。这实际上是两个集合的合并。
* **迁入**操作：将 $S_d$ 的对应位置修改。
* **调查**操作：查询 $S_{D_v}$ 的对应位置的 $k$-值。

我们采用一个懒计算的方式：对于迁移，采用启发式合并，得到一个多重集。对于调查，由于我们维护 `multiset`，所以可以逐一遍历，得到 $S_{D_v}$ 的对应真实 $k_v$ 值后将这些 $(l_v, k'_v)$ 全部删去，只保留真实的 $(l_v, k_v)$。

如果将 $(l, k)$ 对视为一个点，初始有 $n$ 个点，每一个调查加入一个点，因此最多 $n + q$ 个点；每个点只会被遍历一次，而启发式合并的复杂度是容易证明的，因此复杂度正确（两个 $\log$）。

```cpp
template <class Tp>
void merge(multiset<Tp> &S, multiset<Tp> &T) {
    if (S.size() < T.size()) swap(S, T);
    for (auto x : T) S.insert(x);
    T.clear();
}

int main() {
    int n;
    cin >> n;
    vector<int> p(n), dep(n, -1);
    vector<vector<int>> tr(n);
    for (int i : range(1, n)) cin >> p[i], p[i]--, tr[p[i]] += i;
    vector<i64> a(n);
    for (i64 &x : a) cin >> x;

    vector<int> l(n), r(n);
    int cur = 0;
    auto dfs = [&](auto &&slf, int x) -> void {
        l[x] = cur++, dep[x] = dep[p[x]] + 1;
        for (int y : tr[x]) slf(slf, y);
        r[x] = cur++;
    };
    dfs(dfs, 0);

    vector<multiset<array<i64, 2>>> S(n);
    for (int i : range(n)) S[dep[i]].insert({l[i], a[i]});

    int q;
    cin >> q;
    for (int _ : range(q)) {
        i64 op, x, y, cnt;
        cin >> op;
        if (op == 1)
            cin >> x >> y, merge(S[y], S[x]);
        else if (op == 2)
            cin >> x >> cnt, x--, S[dep[x]].insert({l[x], cnt});
        else {
            cin >> x, x--;
            i64 d = dep[x], ans = 0;
            auto lm = S[d].lower_bound({l[x], 0}), rm = S[d].upper_bound({r[x], 0});
            for (auto it = lm; it != rm; it = S[d].erase(it)) ans += (*it)[1];
            S[d].insert({l[x], ans});
            cout << ans << endl;
        }
    }
}
```

---

## 作者：__Cby___ (赞：2)

## 思路
发现用 bfs 序维护若干个区间迁移到若干个点上并不容易，而维护一个点可能从哪些点转移来是容易的。   
考虑一个比较智慧的做法，假设一个点迁移若干次后到达深度为 $x$ 的点 $y$，这个点是可以唯一确定的。而对于这个点 $y$，哪些点在若干次迁移后到达深度为 $x$ 的点是点 $y$ 也是好确定的，就是它的子树。  
然后就可以做了，我们对每个深度，维护每个点迁移到这个深度的数量，以 dfn 序为下标，方便子树查询。每次从深度 $a$ 迁移到深度 $b$ 就是把深度 $b$ 对应的线段树合并到深度 $a$ 上，然后清空。查询就是查这个点深度对应的线段树中这个点的子树和。迁入就是在这个点深度对应的线段树上单点加。   
看起来可能会有点绕，结合代码会比较好理解。  
## 代码
```cpp
#include <iostream>
#include <vector>
#define ll long long
#define R(a,b,c) for(ll a=b;a<=c;a++)
#define E(a,b,c) for(ll a=b;a>=c;a--)
using namespace std;
ll a[2000025];
vector<int> g[2000025];
ll dfn[2000025];
ll rnk[2000025];
ll fa[2000025];
ll cnt=0;
ll sz[2000025];
ll dep[2000025];
void dfs(ll u){
	dfn[u]=++cnt;
	rnk[cnt]=u;
	sz[u]=1;
	for(auto v:g[u]){
		if(v==fa[u])continue;
		fa[v]=u;
		dep[v]=dep[u]+1;
		dfs(v);
		sz[u]+=sz[v];
	}
}
ll cntt=0;
ll ls[2000025*32];
ll rs[2000025*32];
ll sum[2000025*32];
ll rt[2000025];
void ins(ll l,ll r,ll v,ll k,ll p){
	if(l==r){
		sum[p]+=k;
		return;
	}
	ll mid=l+r>>1;
	if(v<=mid){
		if(ls[p])ins(l,mid,v,k,ls[p]);
		else {
			ls[p]=++cntt;
			ins(l,mid,v,k,ls[p]);
		}
	}
	else{
		if(rs[p])ins(mid+1,r,v,k,rs[p]);
		else {
			rs[p]=++cntt;
			ins(mid+1,r,v,k,rs[p]);
		}
	}
	sum[p]=sum[ls[p]]+sum[rs[p]];
}
ll query(ll l,ll r,ll s,ll t,ll p){
	if(!p)return 0;
	if(s<=l&&r<=t)return sum[p];
	ll mid=l+r>>1;
	ll ss=0;
	if(s<=mid)ss+=query(l,mid,s,t,ls[p]);
	if(t>mid) ss+=query(mid+1,r,s,t,rs[p]);
	return ss;
}
ll merge(ll a,ll b,ll l,ll r){
    if (!a) return b;
    if (!b) return a;
    if (l == r) {
        sum[a]+=sum[b];
        return a;
    }
    ll mid = l+r>>1;
    ls[a] = merge(ls[a], ls[b], l, mid);
    rs[a] = merge(rs[a], rs[b], mid + 1, r);
    sum[a]=sum[ls[a]]+sum[rs[a]];
    return a;
} 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	ll n;
	cin>>n;
	R(i,2,n){
		ll f;
		cin>>f;
		g[i].push_back(f);
		g[f].push_back(i);
	}
	R(i,1,n)cin>>a[i];
	dep[1]=1;
	dfs(1);
	R(i,1,n)rt[i]=i;
	cntt=n+1;
	R(i,1,n){
		ins(1,n,dfn[i],a[i],rt[dep[i]]);
	} 
	ll q;
	cin>>q;
	while(q--){
		ll op;
		cin>>op;
		if(!(op-1)){
			ll x,y;
			cin>>y>>x;
			x++;
			y++;
//			cout<<query(1,n,2,3,3)<<"\n";
			rt[x]=merge(rt[x],rt[y],1,n);
			rt[y]=++cntt;
//			cout<<query(1,n,dfn[x],3,rt[x])<<"\n"; 
		} 
		if(!(op-2)){
			ll v,w;
			cin>>v>>w;
			ins(1,n,dfn[v],w,rt[dep[v]]);
		}
		if(!(op-3)){
			ll u;
			cin>>u;
			cout<<query(1,n,dfn[u],dfn[u]+sz[u]-1,rt[dep[u]])<<"\n";
		}
//		R(i,1,n)cout<<query(1,n,dfn[i],dfn[i],rt[dep[i]])<<" ";
//		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：FallingFYC_ (赞：1)

[P11993 [JOIST 2025] 迁移计划 / Migration Plan](https://www.luogu.com.cn/problem/P11993)

---

~~怎么题解区各位大佬都提到了 bfs 序？我是看见线段树合并的标签才进来的。~~

直接维护每个节点不好做，但我们注意到每次迁移都是将一种深度的节点合并到另一种深度的节点上，这和 [P3201 [HNOI2009] 梦幻布丁](https://www.luogu.com.cn/problem/P3201) 很像，我们不妨考虑与 P3201 相似的做法：对每种深度的节点建立一颗动态开点的权值线段树，维护区间和。迁移就是合并两颗线段树，迁入就是单点加，调查就是查询子树和。

因为要查询子树和，所以应以 dfs 序为下标，这样就转换成了区间和。

简单理解一下调查操作为什么是查询子树和：每次迁移都是将某些节点合并到它的一个祖先。而对于线段树合并来说，这些被合并的节点都会累加在它们祖先深度的那颗线段树上。所以调查它们的祖先时就查询祖先深度的那颗线段树上祖先的子树和即可。

---
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define REV(i,a,b) for(int i=(a);i>=(b);i--)
#define CLOSE_TIE ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define psbk push_back
#define mkp make_pair
#define endl '\n'
#define mid ((l+r)>>1)
#define outval(x) cout<<(#x)<<'='<<x<<endl;
#define outarr(a,be,ed)\
cout<<(#a)<<'=';\
FOR(i,be,ed)cout<<a[i]<<' ';\
cout<<endl;
const int N=2e6+5;
int n,q,dfn[N],dep[N],sz[N],tot,cnt,rt[N];
vector<int> e[N];
struct SegTree{
    int sum[N<<5],ls[N<<5],rs[N<<5];
    void push_up(int p){
        sum[p]=sum[ls[p]]+sum[rs[p]];
    }
    void update(int &p,int l,int r,int x,int k){
        if(!p) p=++cnt;
        if(l==r&&l==x){
            sum[p]+=k;
            return;
        }
        if(x<=mid) update(ls[p],l,mid,x,k);
        else update(rs[p],mid+1,r,x,k);
        push_up(p);
    }
    int merge(int a,int b,int l,int r){
        if(!a) return b;
        if(!b) return a;
        if(l==r){
            sum[a]+=sum[b];
            return a;
        }
        ls[a]=merge(ls[a],ls[b],l,mid);
        rs[a]=merge(rs[a],rs[b],mid+1,r);
        push_up(a);
        return a;
    }
    int query(int p,int l,int r,int x,int y){
        if(x<=l&&r<=y) return sum[p];
        int res=0;
        if(x<=mid) res+=query(ls[p],l,mid,x,y);
        if(y>mid) res+=query(rs[p],mid+1,r,x,y);
        return res;
    }
}t;
void dfs(int u,int fa){
    dfn[u]=++tot; dep[u]=dep[fa]+1; sz[u]=1;
    for(int v:e[u])
        if(v!=fa){
            dfs(v,u);
            sz[u]+=sz[v];
        }
    --dep[u];
}
signed main(){
    CLOSE_TIE
    cin>>n;
    FOR(i,2,n){
        int p;
        cin>>p;
        e[p].psbk(i);
        e[i].psbk(p);
    }
    dfs(1,0);
    FOR(i,1,n){
        int k;
        cin>>k;
        t.update(rt[dep[i]],1,n,dfn[i],k);
    }
    cin>>q;
    FOR(i,1,q){
        int op,x,y;
        cin>>op;
        if(op==1){
            cin>>x>>y;
            rt[y]=t.merge(rt[y],rt[x],1,n);
            rt[x]=0;
        }else if(op==2){
            cin>>x>>y;
            t.update(rt[dep[x]],1,n,dfn[x],y);
        }else{
            cin>>x;
            cout<<t.query(rt[dep[x]],1,n,dfn[x],dfn[x]+sz[x]-1)<<endl;
        }
    }
    return 0;
}
```

---

## 作者：Colinxu2020 (赞：1)

## 简要题意

给定一棵树，点有点权，支持把所有深度为 $x$ 的点的点权给到他深度为 $y$ 的父亲上和单点加，单点查三种操作。

## 题解

首先这个东西是和深度强相关的，因此最直接的想法是按 BFS 序去做，但仔细想一下发现第一个操作很难处理，因为每个数会去不同的目标位置，而这个是不好处理的。因为是 BFS 序也没办法用子树之类的性质不去找目标位置。

观察下这为什么是难的，因为找目标位置并合并是难的，于是考虑干脆不合并，就让他留在这里，只是把它从对 $x$ 这个深度的点有贡献改为对 $y$ 这个深度的点有贡献，对于查询再让查询去统计子树中对这个点的深度有贡献的点即可，但还有问题就是我们很难分辨哪些对于某一个深度有贡献，考虑按深度隔离，对于每个深度分别建立一颗动态开点线段树，我们需要实现合并、单点加和区间求和。线段树合并即可。

复杂度线性对数，注意空间一定要开够，线段树节点的左右端点不要放在结构体里，要在递归的时候带上。

## 代码

```cpp
#include<iostream>
#include<vector>
using namespace std;

#define ll long long
const int maxn=2e6+10;
int n,fa[maxn],dfn[maxn],lst[maxn],dep[maxn],tim,rt[maxn],treesz;
vector<int> grp[maxn];
struct{ ll sum; int ls,rs; } tree[maxn*50];

void dfs(int cur){
    dfn[cur]=++tim;
    for(auto x:grp[cur])dep[x]=dep[cur]+1,dfs(x);
    lst[cur]=tim;
}

void add(int& k, int l, int r, int p, int v){
    if(!k)k=++treesz;
    tree[k].sum+=v;
    if(l==r)return;
    int mid=(l+r)/2;
    if(p>mid)add(tree[k].rs,mid+1,r,p,v);
    else add(tree[k].ls,l,mid,p,v);
}
ll query(int k, int l, int r, int L, int R){
    if(L<=l&&r<=R)return tree[k].sum;
    if(!k)return 0;
    int mid=(l+r)/2; ll res=0;
    if(L<=mid)res+=query(tree[k].ls,l,mid,L,R);
    if(mid<R)res+=query(tree[k].rs,mid+1,r,L,R);
    return res;
}
int merge(int k1, int k2){
    if(!k1)return k2; if(!k2)return k1;
    int nw=++treesz; tree[nw].sum=tree[k1].sum+tree[k2].sum;
    tree[nw].ls=merge(tree[k1].ls,tree[k2].ls);
    tree[nw].rs=merge(tree[k1].rs,tree[k2].rs);
    return nw;
}



int main(){
    cin>>n;
    for(int i=2;i<=n;i++)cin>>fa[i],grp[fa[i]].push_back(i);
    dfs(1);
    for(int i=1;i<=n;i++){
        int v; cin>>v;
        add(rt[dep[i]],1,n,dfn[i],v);
    }
    int q; cin>>q;
    while(q--){
        int op; cin>>op;
        if(op==1){
            int s,t; cin>>s>>t;
            rt[t]=merge(rt[t],rt[s]);
            rt[s]=0;
        }else if(op==2){
            int p,v; cin>>p>>v;
            add(rt[dep[p]],1,n,dfn[p],v);
        }else{
            int p; cin>>p;
            cout<<query(rt[dep[p]],1,n,dfn[p],lst[p])<<endl;
        }
    }
}
```

---

