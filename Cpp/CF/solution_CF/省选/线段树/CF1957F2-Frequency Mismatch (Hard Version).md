# Frequency Mismatch (Hard Version)

## 题目描述

This is the hard version of the problem. The difference between the two versions of this problem is the constraint on $ k $ . You can make hacks only if all versions of the problem are solved.

You are given an undirected tree of $ n $ nodes. Each node $ v $ has a value $ a_v $ written on it. You have to answer queries related to the tree.

You are given $ q $ queries. In each query, you are given $ 5 $ integers, $ u_1, v_1, u_2, v_2, k $ . Denote the count of nodes with value $ c $ on path $ u_1 \rightarrow v_1 $ with $ x_c $ , and the count of nodes with value $ c $ on path $ u_2 \rightarrow v_2 $ with $ y_c $ . If there are $ z $ such values of $ c $ such that $ x_c \neq y_c $ , output any $ \min(z, k) $ such values in any order.

## 说明/提示

For query $ 1 $ , the first path is $ 1 \rightarrow 2 \rightarrow 4 $ , coming across the multiset of values $ \{5, 2, 4\} $ . On the second path $ 4 \rightarrow 2 \rightarrow 5 $ , we have the multiset $ \{4, 2, 3\} $ . Two numbers — $ 3 $ and $ 5 $ occur a different number of times, hence we print them both.

In query $ 2 $ , there is no difference between the paths, hence we output $ 0 $ .

In query $ 3 $ , we have the same paths as query $ 1 $ , but we need to output only $ 1 $ value, hence we output $ 5 $ .

In query $ 4 $ , the first path is just the node $ 5 $ , resulting in the multiset $ \{3\} $ , and the second path $ 4 \rightarrow 2 \rightarrow 1 \rightarrow 3 $ gives $ \{4, 2, 5, 3\} $ . The numbers $ 5 $ , $ 2 $ and $ 4 $ occur a different number of times.

## 样例 #1

### 输入

```
5
5 2 3 4 3
1 2
1 3
2 4
2 5
4
1 4 4 5 3
2 3 2 3 1
1 4 4 5 1
5 5 4 3 10```

### 输出

```
2 3 5
0
1 5
3 5 2 4```

# 题解

## 作者：_LSA_ (赞：4)

## 题目大意
给你一棵 $n$ 个节点的树，每个点有点权，$q$ 次询问 $u_1,v_1,u_2,v_2,k$，要求输出 $k$ 个权值 $c$，使得 $c$ 在 $u_1$ 到 $v_1$ 以及 $u_2$ 到 $v_2$ 的出现次数不同。如果 $c$ 的个数小于 $k$，则全部输出。

## 题目分析
我们先给每个权值一个哈希值。

在树上建可持久化线段树，对于树上的每个点 $x$，维护根到点 $x$ 的每个权值的出现次数的哈希值。

然后对于每次查询，求出 $\text{lca}$ 后很容易就能维护出两条路径的哈希值的线段树。于是我们从两个根开始，比较当前节点的哈希值，如果一样说明这一段区间内所有权值的出现次数相同，直接 `return`；不一样则继续往左右子树走。当访问到叶子节点时还没 `return`，说明两条路经这个权值的出现次数不同，直接加入答案中即可。


当找到的答案数量等于 $k$ 时，也直接 `return` 并输出。

时间复杂度 $O(nk \log n)$

需要注意的是单哈希容易被 $\text{hack}$，建议多写几个哈希，~~或者也可以用一些奇奇怪怪的模数~~。

## 代码
```cpp
const int N = 1e5+10;
const ull P = 13131;
ull pw1[N],pw2[N],pw3[N];
int n,a[N],tot;
vector<int> v[N];
int root[N];
struct Segment{
	int lc,rc;
	ull val1,val2,val3;
}t[N<<5];
#define ls t[rt].lc
#define rs t[rt].rc
inline void push_up(int rt){
	t[rt].val1 = t[ls].val1+t[rs].val1;
	t[rt].val2 = t[ls].val2+t[rs].val2;
	t[rt].val3 = t[ls].val3+t[rs].val3;
}
int update(int rt,int l,int r,int pos){
	int u = ++tot;
	t[u] = t[rt];
	if(l == r){
		t[u].val1 += pw1[l];
		t[u].val2 += pw2[l];
		t[u].val3 += pw3[l];
		return u;
	}
	int mid = (l+r)>>1;
	if(pos <= mid) t[u].lc = update(t[u].lc,l,mid,pos);
	else 		   t[u].rc = update(t[u].rc,mid+1,r,pos);
	push_up(u);
	return u;
}
int fa[N][22],Lg,dep[N];
void dfs(int x,int fr){
	fa[x][0] = fr; dep[x] = dep[fr]+1;
	root[x] = update(root[fr],1,100000,a[x]);
	for(int i=1;i<=Lg;i++) fa[x][i] = fa[fa[x][i-1]][i-1];
	for(int y : v[x]){
		if(y == fr) continue;
		dfs(y,x);
	}
}
int lca(int x,int y){
	if(dep[x] < dep[y]) swap(x,y);
	for(int i=Lg;i>=0;i--)
		if(dep[fa[x][i]] >= dep[y]) x = fa[x][i];
	if(x == y) return x;
	for(int i=Lg;~i;i--)
		if(fa[x][i] != fa[y][i])
			x = fa[x][i],y = fa[y][i];
	return fa[x][0];
}
int k,ans[114514],cnt;
struct node{
	int x,y;
	int u,v;
	node lson(){return node{t[x].lc,t[y].lc,t[u].lc,t[v].lc};}
	node rson(){return node{t[x].rc,t[y].rc,t[u].rc,t[v].rc};}
	ull val1(){return t[x].val1+t[y].val1-t[u].val1-t[v].val1;}
	ull val2(){return t[x].val2+t[y].val2-t[u].val2-t[v].val2;}
	ull val3(){return t[x].val3+t[y].val3-t[u].val3-t[v].val3;}
};
void qry(node x,node y,int l,int r){
	if(cnt == k || (x.val1() == y.val1() && x.val2() == y.val2() && x.val3() == y.val3())) return ;
	if(l == r){ans[++cnt] = l; return ;}
	int mid = (l+r)>>1;
	qry(x.lson(),y.lson(),l,mid);
	qry(x.rson(),y.rson(),mid+1,r);
}
int main(){
	n = read();
	pw1[0] = pw2[0] = pw3[0] = 1; Lg = log(n)/log(2)+1;
	srand(time(0));
	for(int i=1;i<=100000;i++) pw1[i] = pw1[i-1]*P;
	for(int i=1;i<=100000;i++) pw2[i] = pw2[i-1]*131;
	for(int i=1;i<=100000;i++) pw3[i] = rand()*rand();
	for(int i=1;i<=n;i++) a[i] = read();
	for(int i=1;i<n;i++){
		int x = read(),y = read();
		v[x].push_back(y);
		v[y].push_back(x);
	}
	dfs(1,0);
	int Q = read();
	while(Q--){
		int x = read(),y = read(),xx = read(),yy = read();
		k = read(); cnt = 0;
		int d1 = lca(x,y),d2 = lca(xx,yy);
		node A = node{root[x],root[y],root[d1],root[fa[d1][0]]},
			 B = node{root[xx],root[yy],root[d2],root[fa[d2][0]]};
		qry(A,B,1,100000);
		printf("%d ",cnt);
		for(int i=1;i<=cnt;i++) printf("%d ",ans[i]);
		printf("\n");
	}
	return 0; 
}
```

---

## 作者：igAC (赞：2)

# $\text{Description}$

[洛谷 link](https://www.luogu.com.cn/problem/CF1957F2)

[CFink](https://codeforces.com/problemset/problem/1957/F2)

简要题意：

给定一棵树，每个节点都有一种颜色。

有 $q$ 次询问，每次给定 $u_1,v_1,u_2,v_2,k$。

记 $cnt_c$ 表示 $u_1$ 到 $v_1$ 的最短路径中 $c$ 颜色的数量，$cnt_c'$ 表示 $u_2$ 到 $v_1$ 的最短路径中 $c$ 颜色的数量。

输出 $\min(z,k)$ 个 $cnt_c \neq cnt_c'$ 的 $c$。

$z$ 表示 $cnt_c \neq cnt_c'$ 的 $c$ 的个数。

你可以以任意顺序输出任意满足上述条件的 $c$。

# $\text{Solution}$

主席树 + 哈希。

先考虑一个弱化版的问题：

>给定两个数组，求两个数组中出现次数不一样的颜色。

可以给每种颜色赋一个随机哈希值，若一个区间内颜色出现情况不同则区间哈希值之和也不同（在理想情况下）。

于是可以对这两个数组分别建立以颜色为下标的线段树，在上面二分寻找哈希值不同的颜色。

把以上解法推广到树上，因为要维护的是一条链的哈希值，于是考虑用主席树维护根到当前节点所有颜色的出现情况，每次询问维护 $x,y,lca,fa_{lca}$ 的线段树。

那维护这条链的线段树即为 $(1,u)+(1,v)-(1,lca)-(1,fa_{lca})$。

然后仿照对于数组的解法在线段树上二分找哈希值不同的区间，去里面找满足要求的颜色即可。

建议写双哈希或者多哈希，因为作者单哈希被 F2 卡了。

# $\text{Code}$

时间复杂度似乎是 $O(kq\log n)$ 的（？

```cpp
#include<bits/stdc++.h>
#define int unsigned long long//习惯不太好，轻喷
#define N 100005
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
mt19937 rng(time(NULL));
int n,q,a[N],head[N],tot,rt[N],idx;
int Size[N],deep[N],ind[N],pre[N],cnt;
int fa[N],top[N],son[N];
struct Edge{int to,nxt;}e[N<<1];
void add_edge(int x,int y){
	e[++tot].to=y;
	e[tot].nxt=head[x];
	head[x]=tot;
}
struct Data{
	int sum1,sum2;
	friend Data operator + (const Data &a,const Data &b){
		return (Data){a.sum1+b.sum1,a.sum2+b.sum2};
	}
	friend Data operator - (const Data &a,const Data &b){
		return (Data){a.sum1-b.sum1,a.sum2-b.sum2};
	}
	friend bool operator == (const Data &a,const Data &b){
		return (a.sum1==b.sum1 && a.sum2==b.sum2);
	}
	friend bool operator != (const Data &a,const Data &b){
		return !(a.sum1==b.sum1 && a.sum2==b.sum2);
	}
}hsh[N];//双哈希用结构体封装一下会更方便一点
struct Segment{
	int ls,rs;
	Data sum;
}node[N*50];
void modily(int &p,int q,int l,int r,int x){
	if(!p) p=++idx;
	node[p].sum=node[q].sum+hsh[x];
	if(l==r) return;
	int mid=(l+r)>>1;
	if(x<=mid) modily(node[p].ls,node[q].ls,l,mid,x),node[p].rs=node[q].rs;
	else node[p].ls=node[q].ls,modily(node[p].rs,node[q].rs,mid+1,r,x);
}
void dfs1(int x,int f){
	Size[x]=1,fa[x]=f;
	deep[x]=deep[fa[x]]+1;
	modily(rt[x],rt[f],1,100000,a[x]);
	for(int i=head[x];i;i=e[i].nxt){
		int y=e[i].to;
		if(y==f) continue;
		dfs1(y,x);
		Size[x]+=Size[y];
		if(!son[x] || Size[y]>Size[son[x]]) son[x]=y;
	}
}
void dfs2(int x,int Top){
	ind[x]=++cnt,pre[cnt]=x,top[x]=Top;
	if(son[x]) dfs2(son[x],Top);
	for(int i=head[x];i;i=e[i].nxt){
		int y=e[i].to;
		if(y==fa[x] || y==son[x]) continue;
		dfs2(y,y);
	}
}
int LCA(int x,int y){
	while(top[x]!=top[y]){
		if(deep[top[x]]<deep[top[y]]) swap(x,y);
		x=fa[top[x]];
	}
	return deep[x]<deep[y]?x:y;
}
void query(vector<int>&ans,int l,int r,int p1,int q1,int l1,int fl1,int p2,int q2,int l2,int fl2,int k){
	if(l==r){
		ans.push_back(l);
		return;
	}
	int mid=(l+r)>>1;
	if((int)ans.size()<k && (node[node[p1].ls].sum+node[node[q1].ls].sum-node[node[l1].ls].sum-node[node[fl1].ls].sum)!=(node[node[p2].ls].sum+node[node[q2].ls].sum-node[node[l2].ls].sum-node[node[fl2].ls].sum)) query(ans,l,mid,node[p1].ls,node[q1].ls,node[l1].ls,node[fl1].ls,node[p2].ls,node[q2].ls,node[l2].ls,node[fl2].ls,k);
	if((int)ans.size()<k && (node[node[p1].rs].sum+node[node[q1].rs].sum-node[node[l1].rs].sum-node[node[fl1].rs].sum)!=(node[node[p2].rs].sum+node[node[q2].rs].sum-node[node[l2].rs].sum-node[node[fl2].rs].sum)) query(ans,mid+1,r,node[p1].rs,node[q1].rs,node[l1].rs,node[fl1].rs,node[p2].rs,node[q2].rs,node[l2].rs,node[fl2].rs,k);
}
signed main(){
	srand(rng()),srand(rand()),srand(rand());
	n=read();
	for(int i=1;i<=100000;++i) hsh[i]=(Data){(int)rand()*rand()*rand(),(int)rand()*rand()};
	for(int i=1;i<=n;++i) a[i]=read();
	for(int i=1;i<n;++i){
		int x=read(),y=read();
		add_edge(x,y);
		add_edge(y,x);
	}
	dfs1(1,0),dfs2(1,1);
	q=read();
	while(q--){
		int u1=read(),v1=read(),u2=read(),v2=read(),k=read();
		int l1=LCA(u1,v1),l2=LCA(u2,v2);
		vector<int>ans;
		query(ans,1,100000,rt[u1],rt[v1],rt[l1],rt[fa[l1]],rt[u2],rt[v2],rt[l2],rt[fa[l2]],k);
		printf("%d ",ans.size());
		for(int c:ans) printf("%llu ",c);
		puts("");
	}
	return 0;
}
```

写了个树剖只为了求 lca，也是够唐的。

---

## 作者：xuyiyang (赞：1)

### Solution
发现 $k$ 很小，猜测询问是从路径上找 $k$ 个就返回的题。对于颜色次数，可以考虑用可持久化权值线段树维护。具体的，维护根到每个节点 $id$ 的线段树 $tr_{id}$，对于每次询问，在权值线段树上二分，若两路径的颜色集合完全相同，就返回。否则若左边不相同则走左边。右边不相同就走右边。找到 $k$ 个就返回即可。对于颜色集合，考虑对每个颜色随机赋权，令 $p = lca(u,v)$，用 $tr_u+tr_v-tr_p-tr_{fa_p}$ 来判断集合是否相等。时间复杂度 $\mathcal O(nk \log n)$。注意赋权用 `mt19937`。
### Code 
```cpp
const int N = 1e5 + 10;
typedef long long LL;

mt19937 Rand(time(0));
struct Node {
	int l, r;
	LL v;
} tr[N * 18 + N * 4];
int root[N];
int n, q, idx, a[N], fa[N];
vector<int> e[N];
LL w[N];
vector<int> id;
int mi[19][N], dfn[N], dn;

int build(int l, int r) {
	int p = ++ idx;
	if (l == r) return p;
	int mid = l + r >> 1;
	tr[p].l = build(l, mid), tr[p].r = build(mid + 1, r);
	return p;
}
int ins(int p, int l, int r, int x) {
	int q = ++ idx; tr[q] = tr[p];
	if (l == r) { tr[q].v += w[x]; return q; }
	int mid = l + r >> 1;
	if (x <= mid) tr[q].l = ins(tr[p].l, l, mid, x);
	else tr[q].r = ins(tr[p].r, mid + 1, r, x);
	tr[q].v = tr[tr[q].l].v + tr[tr[q].r].v; return q;
}
void dfs(int u) {
	root[u] = ins(root[fa[u]], 1, 1e5, a[u]);
	mi[0][dfn[u] = ++ dn] = fa[u];
	for (int v : e[u]) if (v != fa[u]) fa[v] = u, dfs(v);
}
int get(int x, int y) { return dfn[x] < dfn[y] ? x : y; }
int lca(int u, int v) {
	if (u == v) return u;
	if ((u = dfn[u]) > (v = dfn[v])) swap(u, v);
	int k = log(v - (u ++ )) / log(2);
	return get(mi[k][u], mi[k][v - (1 << k) + 1]);
}
struct nd { int a, b, c, d;	LL gv() { return tr[a].v + tr[b].v - tr[c].v - tr[d].v; } };
#define Lx nd{tr[x.a].l, tr[x.b].l, tr[x.c].l, tr[x.d].l}
#define Rx nd{tr[x.a].r, tr[x.b].r, tr[x.c].r, tr[x.d].r}
#define Ly nd{tr[y.a].l, tr[y.b].l, tr[y.c].l, tr[y.d].l}
#define Ry nd{tr[y.a].r, tr[y.b].r, tr[y.c].r, tr[y.d].r}
void find(nd x, nd y, int l, int r, int K) {
	if (id.size() == K || x.gv() == y.gv()) return ;
	if (l == r) return id.push_back(l), void();
	int mid = l + r >> 1;
	if (Lx.gv() != Ly.gv()) find(Lx, Ly, l, mid, K);
	if (Rx.gv() != Ry.gv()) find(Rx, Ry, mid + 1, r, K);
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++ ) scanf("%d", &a[i]);
	for (int i = 1; i <= 1e5; i ++ ) w[i] = Rand();
	for (int i = 1, u, v; i < n; i ++ ) {
		scanf("%d%d", &u, &v);
		e[u].push_back(v), e[v].push_back(u);
	} root[0] = build(1, 1e5); dfs(1);
	int t = log(n) / log(2) + 1;
	for (int i = 1; i < t; i ++ ) for (int j = 1; j + (1 << i) - 1 <= n; j ++ ) 
		mi[i][j] = get(mi[i - 1][j], mi[i - 1][j + (1 << (i - 1))]);
	scanf("%d", &q);
	while (q -- ) {
		int a, b, c, d, K; scanf("%d%d%d%d%d", &a, &b, &c, &d, &K); id.clear();
		nd x = {root[a], root[b], root[lca(a, b)], root[fa[lca(a, b)]]};
		nd y = {root[c], root[d], root[lca(c, d)], root[fa[lca(c, d)]]};
		find(x, y, 1, 1e5, K);
		printf("%d ", id.size()); for (int v : id) printf("%d ", v);
		puts("");
	} return 0;
}
```

---

## 作者：c1120241919 (赞：1)

### CF1957F

很水的一道 Div2 的 F 题。

#### easy version
先分析 easy version 怎么做，当两个路径长度不同时，根据鸽巢定理，一定能找到一个点，使得长的路径拥有，短的路径没有。

当两个路径长度不同时，当两个路径的元素集合不相同时一定有，不妨考虑怎么判断两个集合是否相同，常用方法是 Hash。

具体的：统计每个元素的出现个数，维护一个桶，将这个桶想象成一个 $k$ 进制数，用字符串 Hash 的方式即可 Hash。

可以用一个差分的方式进行维护，现在需要找到是哪个元素不同，不妨考虑分治，对于判定需要维护值域在 $[l,r]$ 内的 Hash 值，发现主席树很好维护。

于是可以在 $q\log_2n$ 时间内求解。

#### hard version 

对于 $k$ 较大，同样可以使用分治，其操作有点类似于小清新线段树，当找到 $k$ 个元素过后停止分治即可。

对于每找到一个元素复杂度为 $\log_2n$，总复杂度为 $qk\log_2 n$。

#### 代码：

https://codeforces.com/contest/1957/submission/258067978

---

## 作者：WRuperD (赞：0)

场上不会做？思维僵硬的老年选手是这样的。

首先肯定是可以搞一个权值线段树，对于每一个颜色赋一个随机权值，每次查询直接二分查找哪些位置不一样做下去。注意到 $k$ 很小，所以我们只需要找到 $k$ 个不一样的位置就直接结束二分就可以保证复杂度。

问题是如何每次快速地领出这样的一颗权值线段树（赛时卡在这里了）。往树剖想肯定没有前途。注意到这个信息满足交换律，所以其实可以直接可持久化线段树，维护每个节点到根节点的权值线段树。查询的时候就直接差分一下就好了。


```cpp
// Problem: Frequency Mismatch (Hard Version)
// URL: https://www.luogu.com.cn/problem/CF1957F2
// Writer: WRuperD
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
const long long inf = 1e18;
const int mininf = 1e9 + 7;
#define int long long
#define pb emplace_back
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void write(int x){if(x<0){x=~(x-1);putchar('-');}if(x>9)write(x/10);putchar(x%10+'0');}
#define put() putchar(' ')
#define endl puts("")

const int MAX = 2e5 + 10;
std::mt19937 Rnd(std::chrono::steady_clock::now().time_since_epoch().count());

int a[MAX];
int lsh[MAX];
int m;
int hsh[MAX];

int s[MAX * 30], ls[MAX * 30], rs[MAX * 30];

int psz;

vector <int> g[MAX];

int build(int l, int r){
	int x = ++psz;
	if(l == r)	return x;
	int mid = (l + r) >> 1;
	ls[x] = build(l, mid), rs[x] = build(mid + 1, r);
	return x;
}

int add(int l, int r, int pos, int val, int prex){
	int x = ++psz;
	s[x] = s[prex] + val, ls[x] = ls[prex], rs[x] = rs[prex];
	if(l == r)	return x;
	int mid = (l + r) >> 1; 
	if(pos <= mid)	ls[x] = add(l, mid, pos, val, ls[prex]);
	else rs[x] = add(mid + 1, r, pos, val, rs[prex]);
	return x;
}	

vector <int> query(int l, int r, int x1, int x2, int x3, int x4, int x5, int x6, int x7, int x8, int ned){
	// write(l), put(), write(r), endl;
	vector <int> re;
	re.clear();
	if(s[x1] + s[x2] - s[x3] - s[x4] == s[x5] + s[x6] - s[x7] - s[x8])	return re;
	if(l == r){
		re.pb(l);
		return re;
	}	
	int mid = (l + r) >> 1;
	re = query(l, mid, ls[x1], ls[x2], ls[x3], ls[x4], ls[x5], ls[x6], ls[x7], ls[x8], ned);
	if(re.size() < ned){
		vector <int> re2 = query(mid + 1, r, rs[x1], rs[x2], rs[x3], rs[x4], rs[x5], rs[x6], rs[x7], rs[x8], ned - re.size());
		for(int u : re2)	re.pb(u);
		return re;
	}
	return re;
}

int ver[MAX];

int Fa[MAX], top[MAX], siz[MAX], son[MAX], dep[MAX];

void dfs(int u, int fa){
	Fa[u] = fa;
	siz[u] = 1;
	dep[u] = dep[fa] + 1;
	ver[u] = add(1, m, a[u], hsh[a[u]], ver[fa]);
	for(int v : g[u]){
		if(v == fa)	continue;
		dfs(v, u);
		siz[u] += siz[v];
		if(siz[son[u]] < siz[v])	son[u] = v;
	}
}

void dfs2(int u, int topu){
	top[u] = topu;
	if(son[u])	dfs2(son[u], topu);
	for(int v : g[u]){
		if(v == Fa[u] or v == son[u])	continue;
		dfs2(v, v);
	}
}

inline int lca(int u, int v){
	while(top[u] != top[v]){
		if(dep[top[u]] < dep[top[v]])	swap(u, v);
		u = Fa[top[u]];
	}
	if(dep[u] < dep[v])	return u;
	return v;
}

void solve(){
	int n = read();
	for(int i = 1; i <= n; i++){
		a[i] = read();
		lsh[i] = a[i];
	}
	sort(lsh + 1, lsh + n + 1);
	m = unique(lsh + 1, lsh + n + 1) - lsh - 1;
	ver[0] = build(1, m);
	for(int i = 1; i <= m; i++)	hsh[i] = Rnd();
	for(int i = 1; i <= n; i++){
		a[i] = lower_bound(lsh + 1, lsh + m + 1, a[i]) - lsh;
	}
	for(int i = 1; i < n; i++){
		int u = read(), v = read();
		g[u].pb(v), g[v].pb(u);
	} 
	dfs(1, 0);
	dfs2(1, 1);
	int q = read();
	while(q--){
		int u = read(), v = read(), u2 = read(), v2 = read(), k = read();
		vector <int> ans = query(1, m, ver[u], ver[v], ver[lca(u, v)], ver[Fa[lca(u, v)]], ver[u2], ver[v2], ver[lca(u2, v2)], ver[Fa[lca(u2, v2)]], k);
		if(ans.size() == 0){
			puts("0");
		}else{
			write(ans.size()), put();
			for(int u : ans)	write(lsh[u]), put();
			endl;
		}
	}
}

signed main(){
	int t = 1;
	while(t--)	solve();
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

首先考虑对于两个集合怎么找出 $k$ 个出现次数不同的数，考虑以颜色为下标建立线段树，并对每种颜色附上权值做哈希，在线段树上不断二分，直到二分出 $k$ 个值不同的位置，这么做显然是 $O(k \log n)$ 的。

考虑如何快速刻画链上的出现次数信息，考虑用主席树维护每个点到根的路径上所有颜色的出现次数信息，查询时链上差分一下即可，时间复杂度 $O((n + q \times k) \log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
const int maxn = 1e5+114;
const int inf = 1e5;
const int mod[2]={998244353,1000000007};
struct Hash{
	int val[2];
	Hash(int v0=0,int v1=0){
		val[0]=v0,val[1]=v1;
	}
	Hash operator+(const Hash &x){
		return Hash((val[0]+x.val[0])%mod[0],(val[1]+x.val[1])%mod[1]);
	}	
	Hash operator-(const Hash &x){
		return Hash((val[0]+mod[0]-x.val[0])%mod[0],(val[1]+mod[1]-x.val[1])%mod[1]);
	}
	bool operator==(const Hash &x){
		return (val[0]==x.val[0])&(val[1]==x.val[1]);
	}
}e;
Hash wei[maxn];
Hash tr[maxn*50];
int ls[maxn*50],rs[maxn*50];
int a[maxn],tot;
int root[maxn];
void pushup(int cur){
	tr[cur]=tr[ls[cur]]+tr[rs[cur]];
}
void ins(int lst,int cur,int lt,int rt,int pos){
	if(lt==rt){
		tr[cur]=tr[lst]+wei[lt];
		return ;
	}
	int mid=(lt+rt)>>1;
	if(pos<=mid){
		rs[cur]=rs[lst];
		ls[cur]=++tot;
		ins(ls[lst],ls[cur],lt,mid,pos);
		pushup(cur);
	}else{
		ls[cur]=ls[lst];
		rs[cur]=++tot;
		ins(rs[lst],rs[cur],mid+1,rt,pos);
		pushup(cur);
	}
}
vector<int> E[maxn];
int son[maxn],sz[maxn],top[maxn],dep[maxn],father[maxn];
void dfs1(int u,int fa){
	root[u]=++tot;
	ins(root[fa],root[u],1,inf,a[u]);
	dep[u]=dep[fa]+1;
	father[u]=fa;
	sz[u]=1;
	for(int v:E[u]){
		if(v!=fa){
			dfs1(v,u);
			sz[u]+=sz[v];
			if(sz[v]>sz[son[u]]) son[u]=v;
		}
	}
}
void dfs2(int u,int fa,int tp){
	top[u]=tp;
	if(son[u]!=0) dfs2(son[u],u,tp);
	for(int v:E[u]){
		if(v!=fa&&v!=son[u]){
			dfs2(v,u,v);
		}
	}	
}
int LCA(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		u=father[top[u]];
	}
	if(dep[u]<dep[v]) swap(u,v);
	return v;
}
int n,q,k;
Hash val(int u,int l,int r){
	return (a[u]>=l&&a[u]<=r)?wei[a[u]]:e; 
}
int now;
vector<int> ans;
void query(int u1,int v1,int lca1,int u2,int v2,int lca2,int p1,int p2,int lt,int rt){
	if(lt==rt){
		ans.push_back(lt);
		now++;
		return ;
	}
	int mid=(lt+rt)>>1;
	if((tr[ls[u1]]+tr[ls[v1]]-tr[ls[lca1]]-tr[ls[lca1]]+val(p1,lt,mid))==(tr[ls[u2]]+tr[ls[v2]]-tr[ls[lca2]]-tr[ls[lca2]]+val(p2,lt,mid))){
		if((tr[rs[u1]]+tr[rs[v1]]-tr[rs[lca1]]-tr[rs[lca1]]+val(p1,mid+1,rt))==(tr[rs[u2]]+tr[rs[v2]]-tr[rs[lca2]]-tr[rs[lca2]]+val(p2,mid+1,rt))) return ;
		query(rs[u1],rs[v1],rs[lca1],rs[u2],rs[v2],rs[lca2],p1,p2,mid+1,rt);		
	}else{
		query(ls[u1],ls[v1],ls[lca1],ls[u2],ls[v2],ls[lca2],p1,p2,lt,mid);
		if(now==k) return ;
		if((tr[rs[u1]]+tr[rs[v1]]-tr[rs[lca1]]-tr[rs[lca1]]+val(p1,mid+1,rt))==(tr[rs[u2]]+tr[rs[v2]]-tr[rs[lca2]]-tr[rs[lca2]]+val(p2,mid+1,rt))) return ; 
		query(rs[u1],rs[v1],rs[lca1],rs[u2],rs[v2],rs[lca2],p1,p2,mid+1,rt);
	}
}
mt19937 rd(time(0));
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=inf;i++) wei[i]=Hash(rd()%mod[0],rd()%mod[1]);
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		E[u].push_back(v),E[v].push_back(u);
	}
	dfs1(1,0);
	dfs2(1,0,1);
	cin>>q;
	while(q--){
		ans.clear();
		now=0;
		int u1,v1,u2,v2;
		cin>>u1>>v1>>u2>>v2>>k;
		int lca1=LCA(u1,v1),lca2=LCA(u2,v2);
		query(root[u1],root[v1],root[lca1],root[u2],root[v2],root[lca2],lca1,lca2,1,inf);
		cout<<ans.size()<<' ';
		for(int x:ans) cout<<x<<' ';
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：strcmp (赞：0)

不妨先去想它的弱化版（CF1957F1，满足 $k = 1$）怎么做。

首先对于这种判断出现次数相同的题，肯定想到去考虑 hash。

想一下，我们怎么判断两个路径是否出现颜色都完全相同。

一看就是哈希的形式，我们对每个颜色随机一个权值出来，然后哈希值取它们的和之类的就好。（需要满足可减性）

树上主席树对于颜色维护 $1 \to u$ 的线段树，然后随便减减就能得到路径对应的线段树。

得到了两棵线段树，每次我们递归到一个区间内就可以 $\Theta(1)$ 的时间判断两个线段树区间是否完全相同。然后递归找最小的不同出现次数颜色即可。

然后你发现就算是强化版也有 $k \le 10$，我们每次不止递归一个区间就能顺带做完了。时间复杂度 $\Theta(nk\log n)$，可以通过。

随机和哈希，感觉应该是卡不掉的。

```cpp
#include <bits/stdc++.h>
#define X first
#define Y second
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define pb push_back
#define lb lower_bound
using namespace std;
using ld = long double;
typedef unsigned long long int ll;
using pii = pair<int, int>;
constexpr int maxn = 2e5 + 10, mx = 1e5, B = 217, mod = 1e9 + 7;
const ll inf = 1145141919810520L;
mt19937_64 rd(114514); 
struct edge { int to, nxt; } nd[maxn << 1]; int h[maxn], cnt = 0, a[maxn]; ll w[maxn];
inline void add(int u, int v) { nd[cnt].nxt = h[u], nd[cnt].to = v, h[u] = cnt++; }
struct Node { int l, r; ll s; } t[maxn * 22];
#define ls(x) (t[x].l)
#define rs(x) (t[x].r)
#define s(x) (t[x].s)
#define mid (l + r >> 1)
int rt[maxn], tot = 0, k, fa[maxn][20], d[maxn];
inline void up(int x) { s(x) = s(ls(x)) + s(rs(x)); }
void mdf(int l, int r, int u, int p, int& x) {
	x = ++tot; t[x] = t[p];
	if (l == r) return s(x) += w[l], void();
	u <= mid ? mdf(l, mid, u, ls(p), ls(x)) : mdf(mid + 1, r, u, rs(p), rs(x)); up(x);
} 
void dfs(int u, int f) {
	fa[u][0] = f; d[u] = d[f] + 1;
	for (int i = 1; i < 20; i++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
	mdf(1, mx, a[u], rt[f], rt[u]);
	for (int i = h[u]; ~i; i = nd[i].nxt) {
		int v = nd[i].to;
		if (v != f) dfs(v, u);
	}
}
inline int lca(int u, int v) {
	if (d[u] < d[v]) swap(u, v);
	for (int i = 0; i <= 19; i++) if (d[u] - d[v] >> i & 1) u = fa[u][i];
	if (u == v) return u;
	for (int i = 19; i >= 0; i--) if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}
vector<int> ans;
void qry(int l, int r, int u0, int v0, int l0, int lf0, int u1, int v1, int l1, int lf1) {
	if (ans.size() == k) return;
	if (s(u0) + s(v0) - s(l0) - s(lf0) == s(u1) + s(v1) - s(l1) - s(lf1)) return;
	if (l == r) return ans.pb(l);
	qry(l, mid, ls(u0), ls(v0), ls(l0), ls(lf0), ls(u1), ls(v1), ls(l1), ls(lf1));
	qry(mid + 1, r, rs(u0), rs(v0), rs(l0), rs(lf0), rs(u1), rs(v1), rs(l1), rs(lf1));
}
int n, q;
int main() {
	memset(h, -1, sizeof(h));
	for (int i = 1; i <= mx; i++) w[i] = rd();
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), add(u, v), add(v, u);
	dfs(1, 0); scanf("%d", &q);
	while (q--) {
		int u0, v0, u1, v1;
		scanf("%d%d%d%d%d", &u0, &v0, &u1, &v1, &k);
		int l0 = lca(u0, v0), l1 = lca(u1, v1); ans.clear();
		qry(1, mx, rt[u0], rt[v0], rt[l0], rt[fa[l0][0]], rt[u1], rt[v1], rt[l1], rt[fa[l1][0]]);
		printf("%d ", (int)ans.size());
		for (auto x : ans) printf("%d ", x); puts("");
	}
	return 0;
}
```

---

## 作者：未来姚班zyl (赞：0)

其实两个 version 没有区别，easy version 感觉是给赛时卡 E 没时间写 F 的人设计的，~~但你只需要像我一样果断跳 E 就可以在 F 上花费超长的时间~~。

## 题目大意

给定一颗点带权的数。设 $w(x,y,k)$ 表示 $x\rightarrow y$ 的路径上点权等于 $k$ 的点的个数。

多次询问给定 $x_1,y_1,x_2,y_2,k$，要求你找出尽量多但不超过 $k$ 个 $i$ 使得 $w(x_1,y_1,i)\neq w(x_2,y_2,i)$。输出这些 $i$。

$k\le 10$。

## 题目分析

板子题。

用主席树维护每个点与根节点的路径上的 $w(x,rt,i)$。要找到两条路径上不相等的位置，先树上差分提取路径，设 $lca$ 为 $x,y$ 在树上的 $lca$ ，则 $w(x,y,i)=w(x,rt,i)+w(y,rt,i)-w(lca,rt,i)-w(fa_{lca},rt,i)$。

我们每次找最小的 $i$，则相当于找两条路径的最长公共前缀，使用哈希与线段树上二分即可，注意这是 CF 题，一定要写双哈希。

复杂度 $O(qk\log^2 n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define L(x) xd[x].l
#define R(x) xd[x].r
#define mid (l+r>>1)
#define lc(x) L(x),l,mid
#define rc(x) R(x),mid+1,r
#define OK Ll<=l&&r<=Rr
#define Root 1,1,n
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N =1e5+5,M=4e6+5,inf=(1LL<<31)-1,mod=998244853;
const ll llf=1e18;
inline void add(int &a,int b){((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline int mul(int a,int b){return 1LL*a*b%mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline void red(int &a,int b){add(a,mod-b);}
inline int Red(int a,int b){return red(a,b),a;}
inline int qp(int a,int b){if(!b)return 1;int c=qp(a,b>>1);Mul(c,c);if(b&1)Mul(c,a);return c;}
inline int INV(int x){return qp(x,mod-2);}
const ui base=1333331;
const int bas=1145141;
int n,m,a[N],h[N],to[N<<1],nxt[N<<1],cnt;
ui p[N];
struct seg{
	int l,r,h;
	ui H;
}xd[N*30];
int tot,P[N],root[N];
inline void add_(int a,int b){
	to[++cnt]=b,nxt[cnt]=h[a],h[a]=cnt;
}
inline int modify(int x,int l,int r,int ps){
	xd[++tot]=xd[x];
	xd[tot].H+=p[ps],add(xd[tot].h,P[ps]);
	if(l==r)return tot;
	int nw=tot;
	ps<=mid?L(nw)=modify(lc(nw),ps):R(nw)=modify(rc(nw),ps);
	return nw;
}
inline bool cmp(int x,int y,int X,int Y,int a,int b,int A,int B){
	return xd[x].H+xd[y].H-xd[X].H-xd[Y].H==xd[a].H+xd[b].H-xd[A].H-xd[B].H&&Red(Add(xd[x].h,xd[y].h),Add(xd[X].h,xd[Y].h))==Red(Add(xd[a].h,xd[b].h),Add(xd[A].h,xd[B].h));
}
inline bool Cmp(int x,int y,int X,int Y,int a,int b,int A,int B,int l,int r,int Ll,int Rr){
	if(OK)return cmp(x,y,X,Y,a,b,A,B);
	if(Rr<=mid)return Cmp(L(x),L(y),L(X),L(Y),L(a),L(b),L(A),lc(B),Ll,Rr);
	if(Ll>mid)return Cmp(R(x),R(y),R(X),R(Y),R(a),R(b),R(A),rc(B),Ll,Rr);
	return Cmp(L(x),L(y),L(X),L(Y),L(a),L(b),L(A),lc(B),Ll,Rr)&Cmp(R(x),R(y),R(X),R(Y),R(a),R(b),R(A),rc(B),Ll,Rr);
}
inline int get(int x,int y,int X,int Y,int a,int b,int A,int B,int l,int r,int Ll){
	if(cmp(x,y,X,Y,a,b,A,B))return r;
	if(l==r)return l-1;
	if(Ll>mid)return get(R(x),R(y),R(X),R(Y),R(a),R(b),R(A),rc(B),Ll);
	if(Cmp(L(x),L(y),L(X),L(Y),L(a),L(b),L(A),lc(B),max(Ll,l),mid))return get(R(x),R(y),R(X),R(Y),R(a),R(b),R(A),rc(B),Ll);
	return get(L(x),L(y),L(X),L(Y),L(a),L(b),L(A),lc(B),Ll);
}
int top[N],dep[N],siz[N],f[N],son[N];
inline void dfs(int x,int fa){
	f[x]=fa,dep[x]=dep[fa]+1,siz[x]=1;
	e(x)if(y^fa)root[y]=modify(root[x],1,1e5,a[y]),dfs(y,x),siz[x]+=siz[y],son[x]=siz[y]>siz[son[x]]?y:son[x];
}
inline void Dfs(int x,int low){
	top[x]=low;
	if(son[x])Dfs(son[x],low);
	e(x)if(y^f[x]&&y^son[x])Dfs(y,y);
}
inline int lca(int x,int y){
	while(top[x]^top[y])dep[top[x]]>dep[top[y]]?x=f[top[x]]:y=f[top[y]];
	return dep[x]<dep[y]?x:y;
}
inline void Main(){
	n=read(),p[0]=1,P[0]=1;
	repn(i)a[i]=read();
	rep(i,1,1e5)p[i]=p[i-1]*base,P[i]=mul(P[i-1],bas);
	rep(i,2,n){
		int x=read(),y=read();
		add_(x,y),add_(y,x);
	}
	root[1]=modify(0,1,1e5,a[1]);
	dfs(1,0),Dfs(1,1);
	m=read();
	repm(o){
		int x=read(),y=read(),X=read(),Y=read(),k=read();
		int l=lca(x,y),r=lca(X,Y);
		vector<int>p;
		int ps=get(root[x],root[y],root[l],root[f[l]],root[X],root[Y],root[r],root[f[r]],1,1e5,1);
		while(ps<1e5&&(int)p.size()<k){
			p.pb(ps+1);
			ps+=2;
			if(ps>1e5)break;
			ps=get(root[x],root[y],root[l],root[f[l]],root[X],root[Y],root[r],root[f[r]],1,1e5,ps);
		} 
		cout <<(int)p.size()<<' ';
		for(auto y:p)cout <<y<<' ';
		cout <<'\n';
	}
}
signed main(){
	int T=1;
	while(T--)Main(); 
	return 0;
}
```

---

## 作者：huazai676 (赞：0)

[CodeforcesLink](https://codeforces.com/problemset/problem/1957/F2)

[LuoguLink](https://www.luogu.com.cn/problem/CF1957F2)

判断两个集合（多重集）是否相等可以用多重集哈希，具体哈希值可以是集合元素的算术和，平方和，异或和等等，为防止出题人卡，可以把每个元素映射到一个随机数上后再求哈希值。

这题要在两个集合间找出 $k$ 个数量不相等的权值。考虑在树上以 $a_i$ 为权值下标建主席树，节点存储子区间表示集合的哈希值，如果当前区间代表集合不相等，就递归到两个子区间继续找，找到 $k$ 个就直接结束。时间复杂度 $O(10n\log n)$。

这题随便找两个哈希函数就可以了。

[Code](https://codeforces.com/contest/1957/submission/257656658)

---

