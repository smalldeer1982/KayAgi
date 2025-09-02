# [UTS 2024] Two Trees

## 题目描述

给定两棵相同的无向树 $G$ 和 $H$，每棵树包含 $n$ 个顶点。两棵树被称为相同，当且仅当对于所有顶点对 $(u,v)$，$G$ 中存在边 $(G_u,G_v)$ 当且仅当 $H$ 中存在边 $(H_u,H_v)$。

某些顶点可以通过无向边连接到另一棵树中的对应顶点。特别地，叶子顶点 $G_v$ 可以直接连接到顶点 $H_v$。如果叶子顶点 $G_v$ 直接连接到 $H_v$，则称顶点 $v$ 为**启用**状态，否则为**禁用**状态。

初始时，所有叶子顶点均为**禁用**状态。需要处理以下两种查询：

1. $1$ $v$ —— 切换顶点 $v$ 的状态（若当前为禁用则改为启用，反之亦然）；
2. $2$ $u$ $v$ —— 输出从顶点 $G_u$ 到顶点 $H_v$ 的最短路径长度。

## 说明/提示

设 $k$ 为第二类查询的数量。

- （$3$ 分）：$n \le 16$，$q \le 16$；
- （$3$ 分）：$n \le 16$，$q \le 2 \cdot 10^5$；
- （$2$ 分）：$n \le 2000$，$q \le 2 \cdot 10^5$，$k \le 5$；
- （$8$ 分）：$n \le 2000$，$q \le 2000$；
- （$9$ 分）：$n \le 2 \cdot 10^5$，$q \le 2 \cdot 10^5$，$k \le 5$；
- （$30$ 分）：$n \le 2 \cdot 10^5$，$q \le 2 \cdot 10^5$，且第二类查询后不会出现第一类查询；
- （$45$ 分）：无额外限制。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
7 11
1 2
2 3
1 4
2 5
4 6
4 7
1 6
1 3
2 1 6
2 1 2
1 7
2 5 4
2 6 3
1 6
1 3
1 5
2 6 3```

### 输出

```
2
3
5
4
6```

## 样例 #2

### 输入

```
3 2
1 2
1 3
1 3
2 1 2```

### 输出

```
3```

# 题解

## 作者：lzyqwq (赞：3)

[书接上回。](https://www.luogu.com.cn/article/ifvrxol3)

> - 给出 $n$ 个点的树。初始所有点都是白色，你要支持 $q$ 次操作：
>     - `1 u`：翻转 $u$ 的颜色。
>     - `2 u v`：记当前黑点集合为 $S$，求 $\min\limits_{x\in S}(\text{dis}(u,x)+\text{dis}(x,v))$。
> - $n,q\le 2\times 10^5$。

你谷首杀。

题中还保证了只会 `1 u` 只会操作叶子结点，但是我感觉这个条件没什么用。应该只是为了契合原题意。

以 $1$ 为根。记 $d_u$ 为 $u$ 的深度，$f_u$ 为 $u$ 的父亲结点，$T_u$ 为以 $u$ 为根的子树内的点构成的集合。那么查询的式子可以化成：

$$d_u+d_v+2\left(d_x-d_{\text{LCA}(u,x)}-d_{\text{LCA}(v,x)}\right)$$

显然只需要最小化括号里的式子。注意到这个 LCA 不是很好处理，所以最暴力的想法是考虑枚举 $\text{LCA}(u,x)$。

不妨认为 $d_u\ge d_v$。记 $[p_1=1,\dots,p_k=u],k=d_u+1$ 为 $1$ 到 $u$ 的路径。首先求出 $\text{LCA}(u,v)=p_a$，记枚举的 $\text{LCA}(u,x)=p_i$。有三种大情况。

**Case 1：$i\in [a+1,k]$。**

在这种情况下，$\text{LCA}(v,x)=\text{LCA}(u,v)$。查询的式子化成 $d_x-d_{p_i}-d_{p_a}$。

若 $i=k$，则只要求 $x\in T_u$。用 dfn 序刻画子树，求出这个范围内黑点深度的最小值即可。用线段树维护黑点的深度。

否则对于 $i\in [a+1,k)$，要求 $x\in T_{p_i}$ 且 $x\notin T_{p_{i+1}}$。考虑重链剖分，那么只有 $\mathcal{O}(\log n)$ 条重链。对于这些重链的底端的点单独用线段树求限制区域内黑点深度的最小值。对于剩余的 $p_i$，一定满足 $p_{i+1}$ 是 $p_i$ 的重儿子，考虑维护 $g_u$ 表示 $u$ 子树内且不在 $u$ 重儿子子树内的黑点的 $d_x-d_u$ 最小值。那么对于每一条重链要求除去其底端的点中 $g_{p_i}$ 的最小值。这个区域是重链的前缀，同样是一段连续的 dfn 区间，用线段树维护 $g_u$ 即可。

**Case 2：$i=a$。**

我一开始以为这种情况下同样有 $\text{LCA}(v,x)=\text{LCA}(u,v)$，但事实证明我是唐龙。

如果 $v\ne p_a$，那么此时要求 $x\in T_{p_a}$ 且 $x\notin T_{p_{a+1}}$。再记 $[m_1=1,\dots,m_t=v],t=d_v+1$ 表示 $1$ 到 $v$ 的路径。根据 $\text{LCA}$ 的性质有 $\forall\,i\in[1,a],p_i=m_i$。那么又有两种情况。

当 $x\in T_{m_{a+1}}$ 时，此时不满足 $\text{LCA}(v,x)=\text{LCA}(u,v)$，并且此时 $\text{LCA}(v,x)\in \{m_{a+1},\dots,m_t\}$。那么还需要类似 Case 1 那样在这个范围内考虑每一个点作为 $\text{LCA}(v,x)$。

否则就会满足 $\text{LCA}(v,x)=\text{LCA}(u,v)$，只需要求 $x\in T_{p_a}$ 且 $x\notin T_{p_{a+1}}$ 且 $x\notin T_{m_{a+1}}$ 范围内黑点深度的最小值。容易用 $\mathcal{O}(1)$ 个 dfn 区间的并表示这个区间，线段树查询即可。

如果 $v=p_a$，无论如何都会满足 $\text{LCA}(v,x)=\text{LCA}(u,v)$。此时只需要求 $x\in T_{p_a}$ 且 $x\notin T_{p_{a+1}}$ 范围内黑点深度的最小值，同样容易求出。

**Case 3：$i\in [1,a-1]$。**

此时 $\text{LCA}(v,x)=\text{LCA}(u,x)$。查询的式子变成 $d_x-2d_{p_i}$。

类似 Case 1，对于重链底端结点单独用线段树求出限制区域内黑点深度最小值。对于剩余的情况维护 $h_u$ 表示在 $u$ 子树内且不在 $u$ 重儿子子树内的黑点 $d_x-2d_u$ 的最小值，线段树维护 $h_u$，查询一段重链前缀的 $h_{p_i}$ 最小值。

接下来考虑带上修改，你发现对于 $u$ 的修改而言，只有 $1$ 到 $u$ 的路径上轻边连接的父亲结点会满足 $u$ 在其子树内且不在其重儿子内。这样的结点只有 $\mathcal{O}(\log n)$ 个，用维护黑点深度的线段树重新计算她们的 $g,h$ 值即可。

时间复杂度 $\mathcal{O}\left(q\log^2 n\right)$，空间复杂度 $\mathcal{O}(n)$。代码写的一坨。


```cpp
#include <bits/stdc++.h>
using namespace std; const int N = 200005, I = 5e8; vector<int> g[N];
int n, q, d[N], s[N], h[N], t[N], df[N], id, f[N], rv[N]; bool c[N];
struct SGT {
	int a[N << 2];
	int ls(int x) { return x << 1; } int rs(int x) { return x << 1 | 1; }
	void B(int x, int l, int r) {
		a[x] = I; if (l == r) return; int m = l + r >> 1;
		B(ls(x), l, m); B(rs(x), m + 1, r);
	}
	void U(int x, int l, int r, int k, int v) {
		if (l == r) return void(a[x] = v); int m = l + r >> 1;
		if (k <= m) U(ls(x), l, m, k, v); else U(rs(x), m + 1, r, k, v);
		a[x] = min(a[ls(x)], a[rs(x)]);
	}
	void U(int k, int v) { U(1, 1, n, k, v); }
	int Q(int x, int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) return a[x]; int m = l + r >> 1, t = I;
		if (ql <= m) t = Q(ls(x), l, m, ql, qr);
		if (qr > m) t = min(t, Q(rs(x), m + 1, r, ql, qr)); return t;
	}
	int Q(int l, int r) { return l > r ? I : Q(1, 1, n, l, r); }
} t1, t2, t3;
void d1(int u) {
	s[u] = 1;
	for (int v : g[u])
		if (v != f[u]) {
			d[v] = d[u] + 1; f[v] = u; d1(v);
			s[u] += s[v]; if (s[h[u]] < s[v]) h[u] = v;
		}
}
void d2(int u, int p) {
	t[u] = p; df[u] = ++id; rv[id] = u; if (h[u]) d2(h[u], p);
	for (int v : g[u]) if (v != f[u] && v != h[u]) d2(v, v);
}
int lca(int x, int y) {
	for (; t[x] != t[y]; x = f[t[x]]) if (d[t[x]] < d[t[y]]) swap(x, y);
	return d[x] < d[y] ? x : y;
}
void rmk(int x) {
	int k = (h[x] ? min(t1.Q(df[x], df[h[x]] - 1),
		                t1.Q(df[h[x]] + s[h[x]], df[x] + s[x] - 1))
				  : t1.Q(df[x], df[x] + s[x] - 1));
	t2.U(df[x], k - d[x]); t3.U(df[x], k - (d[x] << 1));
}
void U(int x) {
	t1.U(df[x], c[x] ? I : d[x]); c[x] ^= 1; rmk(x);
	for (; f[t[x]]; x = f[t[x]]) rmk(f[t[x]]);
}
int Q(int x, int y) {
	if (d[x] < d[y]) swap(x, y); int a = lca(x, y), k;
	auto F = [&](int v) {
		int r = t1.Q(df[v], df[v] + s[v] - 1) - d[v];
		for (;; v = f[t[v]]) {
			if (t[v] == t[a])
				return make_pair(rv[df[a] + 1],
				                 min(r, t2.Q(df[a] + 1, df[v] - 1)) - d[a]);
			r = min(r, t2.Q(df[t[v]], df[v] - 1));
			if (f[t[v]] != a)
		        r = min({r, min(t1.Q(df[f[t[v]]], df[t[v]] - 1),
				                t1.Q(df[t[v]] + s[t[v]],
								     df[f[t[v]]] + s[f[t[v]]] - 1)) -
			                d[f[t[v]]]});
			else return make_pair(t[v], r - d[a]);
		}
	};
	auto [i, j] = F(x); k = j;
	if (y != a) {
		auto [z, w] = F(y); k = min(k, w); if (df[i] > df[z]) swap(i, z);
		k = min(k, min({t1.Q(df[a], df[i] - 1),
	                	t1.Q(df[i] + s[i], df[z] - 1),
						t1.Q(df[z] + s[z], df[a] + s[a] - 1)}) - (d[a] << 1));
	} else k = min(k, min(t1.Q(df[a], df[i] - 1),
	                      t1.Q(df[i] + s[i], df[a] + s[a] - 1)) - (d[a] << 1));
	if (f[a]) k = min(k, min(t1.Q(df[a] + s[a], df[f[a]] + s[f[a]] - 1),
		                     t1.Q(df[f[a]], df[a] - 1)) - (d[f[a]] << 1));
	for (a = f[a]; a; a = f[t[a]]) {
		k = min(k, t3.Q(df[t[a]], df[a] - 1));
		if (f[t[a]])
			k = min(k, min(t1.Q(df[f[t[a]]], df[t[a]] - 1),
			               t1.Q(df[t[a]] + s[t[a]],
						        df[f[t[a]]] + s[f[t[a]]] - 1)) -
					   (d[f[t[a]]] << 1));
	}
	return k > N ? -1 : (k << 1) + d[x] + d[y];
}
int main() {
	scanf("%d%d", &n, &q);
	for (int i = 1, u, v; i < n; ++i)
		scanf("%d%d", &u, &v), g[u].emplace_back(v), g[v].emplace_back(u);
	d1(1); d2(1, 1); t1.B(1, 1, n); t2.B(1, 1, n); t3.B(1, 1, n);
	for (int o, x, y; q--;) {
		cin >> o >> x; if (o & 1) U(x); else cin >> y, printf("%d\n", Q(x, y));
	}
	return 0;
}
```

---

## 作者：dAniel_lele (赞：2)

首先考虑 $2$ 操作求距离一条链最近的黑点怎么算。取出链 LCA 设为 $l$，对于每个点维护向下最近的黑点距离 $dis_x$，那么距离链最近的黑点距离就是 $\min(\min_{x\in u\to l}dis_x,\min_{x\in v\to l}dis_x,\min_{x\in l\to 1}(dis_x+dep_l-dep_x))$，最后一项也就是 $\min_{x\in l\to 1}(dis_x-dep_x)+dep_l$。

于是我们实际上要维护 $dis_x$ 和 $dis_x-dep_x$，查询一条链所有点这两个值的 $\min$。考虑重链剖分，并改为维护 $dis_x$ 为轻子树中最近的黑点。假设我们要查询的链被剖成的重链上的一段是 $x\to y$（$x$ 较深），那么 $x\to y$ 中的 $dis_x$ 或 $dis_x-dep_x$ 可以直接统计。设重链底部为 $p$，考察 $p\to x$ 的答案，其中一个点 $q$ 带来的贡献是 $dis_q+dep_q-dep_x$（或 $dis_q-dep_x$）。于是我们额外维护 $dis_x+dep_x$ 即可。

接下来考虑修改，我们只需要在每次跳轻链的时候将 $dep_v-dep_x$ 贡献给 $dis_x$ 即可，可删堆维护之。总复杂度 $O(n\log^2n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
vector<int> vc[200005];
int siz[200005],hson[200005],ff[200005],dep[200005],n;
void dfs0(int now,int fa){
	ff[now]=fa,dep[now]=dep[fa]+1,siz[now]=1;
	for(auto v:vc[now]){
		if(v==fa) continue;
		dfs0(v,now);
		if(siz[v]>siz[hson[now]]) hson[now]=v;
		siz[now]+=siz[v];
	}
}
int top[200005],dfn[200005],ord[200005],cnt,ed[200005];
void dfs1(int now,int fa){
	dep[now]=dep[fa]+1;
	if(!top[now]) top[now]=now;
	dfn[now]=++cnt; ord[cnt]=now; ed[top[now]]=cnt;
	if(hson[now]) top[hson[now]]=top[now],dfs1(hson[now],now);
	for(auto v:vc[now]){
		if(v==fa||v==hson[now]) continue;
		dfs1(v,now);
	}
}
struct deletable_heap{
	priority_queue<int,vector<int>,greater<int>> add,del;
	void push(int i){
		add.push(i);
	}
	void pull(int i){
		del.push(i);
	}
	int top(){
		while(!del.empty()&&add.top()==del.top()) add.pop(),del.pop();
		if(!add.empty()) return add.top();
		return 1e9;
	}
}pq[200005];
struct sgt{
	int f[1000005],g[1000005],h[1000005];
	void pushup(int i){
		f[i]=min(f[i<<1],f[i<<1|1]);
		g[i]=min(g[i<<1],g[i<<1|1]);
		h[i]=min(h[i<<1],h[i<<1|1]);
	}
	void build(int i,int l,int r){
		if(l==r){
			f[i]=pq[ord[l]].top();
			g[i]=pq[ord[l]].top()-dep[ord[l]];
			h[i]=pq[ord[l]].top()+dep[ord[l]];
//			cout<<l<<" "<<ord[l]<<" "<<h[i]<<"add\n";
			return ;
		}
		build(i<<1,l,mid),build(i<<1|1,mid+1,r);
		pushup(i);
	}
	void change(int i,int l,int r,int pos){
		if(l==r){
			f[i]=pq[ord[l]].top();
			g[i]=pq[ord[l]].top()-dep[ord[l]];
			h[i]=pq[ord[l]].top()+dep[ord[l]];
//			cout<<l<<" "<<ord[l]<<" "<<h[i]<<"add\n";
			return ;
		}
		if(pos<=mid) change(i<<1,l,mid,pos);
		else change(i<<1|1,mid+1,r,pos);
		pushup(i);
	}
	int qryf(int i,int l,int r,int ql,int qr){
		if(ql>qr) return 1e9;
		if(ql<=l&&r<=qr) return f[i];
		if(qr<=mid) return qryf(i<<1,l,mid,ql,qr);
		if(ql>mid) return qryf(i<<1|1,mid+1,r,ql,qr);
		return min(qryf(i<<1,l,mid,ql,qr),qryf(i<<1|1,mid+1,r,ql,qr)); 
	}
	int qryg(int i,int l,int r,int ql,int qr){
		if(ql>qr) return 1e9;
		if(ql<=l&&r<=qr) return g[i];
		if(qr<=mid) return qryg(i<<1,l,mid,ql,qr);
		if(ql>mid) return qryg(i<<1|1,mid+1,r,ql,qr);
		return min(qryg(i<<1,l,mid,ql,qr),qryg(i<<1|1,mid+1,r,ql,qr)); 
	}
	int qryh(int i,int l,int r,int ql,int qr){
		if(ql>qr) return 1e9;
		if(ql<=l&&r<=qr) return h[i];
		if(qr<=mid) return qryh(i<<1,l,mid,ql,qr);
		if(ql>mid) return qryh(i<<1|1,mid+1,r,ql,qr);
		return min(qryh(i<<1,l,mid,ql,qr),qryh(i<<1|1,mid+1,r,ql,qr)); 
	}
}tree;
int sta[200005];
void add(int pos){
	int len=0;
	while(pos!=0){
		pq[pos].push(len);
		tree.change(1,1,n,dfn[pos]);
		len+=dep[pos]-dep[ff[top[pos]]];
		pos=ff[top[pos]];
	}
}
void del(int pos){
	int len=0;
	while(pos!=0){
		pq[pos].pull(len);
		tree.change(1,1,n,dfn[pos]);
		len+=dep[pos]-dep[ff[top[pos]]];
		pos=ff[top[pos]];
	}
}
int qry(int u,int v){
	int minv=1e18,qlen=0;
	//query u->v
	{
		while(top[u]!=top[v]){
			if(dep[top[u]]<dep[top[v]]) swap(u,v);
//			cout<<top[u]<<" "<<u<<" ";
			minv=min(minv,tree.qryf(1,1,n,dfn[top[u]],dfn[u]));
			minv=min(minv,tree.qryh(1,1,n,dfn[u],ed[top[u]])-dep[u]);
//			cout<<minv<<"\n";
			qlen+=dep[u]-dep[ff[top[u]]];
			u=ff[top[u]];
		}
		if(dep[u]>dep[v]) swap(u,v);
		qlen+=dep[v]-dep[u];
		minv=min(minv,tree.qryf(1,1,n,dfn[u],dfn[v]));
		minv=min(minv,tree.qryh(1,1,n,dfn[v],ed[top[u]])-dep[v]);
//		cout<<tree.qryf(1,1,n,dfn[v],ed[top[u]])<<" "<<tree.qryh(1,1,n,dfn[v],ed[top[u]])<<"  ";
//		cout<<minv<<"\n";
	}
	//query lca->1
	int len=0;
	while(u!=0){
		minv=min(minv,tree.qryg(1,1,n,dfn[top[u]],dfn[u])+dep[u]+len);
		minv=min(minv,tree.qryh(1,1,n,dfn[u],ed[top[u]])-dep[u]+len);
		len+=dep[u]-dep[ff[top[u]]];
		u=ff[top[u]];
	}
//	cout<<minv<<"\n";
	return minv*2+qlen;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int q; cin>>n>>q;
	for(int i=1;i<n;i++){
		int u,v; cin>>u>>v;
		vc[u].push_back(v);
		vc[v].push_back(u);
	}
	dfs0(1,0); dfs1(1,0); tree.build(1,1,n);
	while(q--){
		int opt; cin>>opt;
		if(opt==1){
			int x; cin>>x;
			if(sta[x]^1) add(x);
			else del(x);
			sta[x]^=1;
		}
		else{
			int u,v; cin>>u>>v;
			int ret=qry(u,v);
			if(ret>n*2) cout<<-1<<"\n";
			else cout<<ret<<"\n";
		}
	}
	return 0;
}
```

---

