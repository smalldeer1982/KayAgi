# Yash And Trees

## 题目描述

Yash loves playing with trees and gets especially excited when they have something to do with prime numbers. On his 20th birthday he was granted with a rooted tree of $ n $ nodes to answer queries on. Hearing of prime numbers on trees, Yash gets too intoxicated with excitement and asks you to help out and answer queries on trees for him. Tree is rooted at node $ 1 $ . Each node $ i $ has some value $ a_{i} $ associated with it. Also, integer $ m $ is given.

There are queries of two types:

1. for given node $ v $ and integer value $ x $ , increase all $ a_{i} $ in the subtree of node $ v $ by value $ x $
2. for given node $ v $ , find the number of prime numbers $ p $ less than $ m $ , for which there exists a node $ u $ in the subtree of $ v $ and a non-negative integer value $ k $ , such that $ a_{u}=p+m·k $ .

## 样例 #1

### 输入

```
8 20
3 7 9 8 4 11 7 3
1 2
1 3
3 4
4 5
4 6
4 7
5 8
4
2 1
1 1 1
2 5
2 4
```

### 输出

```
3
1
1
```

## 样例 #2

### 输入

```
5 10
8 7 5 1 0
1 2
2 3
1 5
2 4
3
1 1 0
1 1 2
2 2
```

### 输出

```
2
```

# 题解

## 作者：Pengzt (赞：3)

[CF633G](https://www.luogu.com.cn/problem/CF633G)

简单题。

先看到子树加和子树质数个数和，果断转换为 ```dfs``` 序进行处理。

既然有区间求和，考虑线段树。

若对于每一个节点维护一个 $cnt$ 数组，用二进制数 $x$ 来表示，即当 $cnt_i = 1$ 时第 $i$ 位为 $1$。设当前节点为 $u$，左右子节点分别为 $ls$ 和 $rs$。发现 $x_u = x_{ls} | x_{rs}$。统计时，就是区间的所有 $x$ 的按位或值 $res$ 与质数数组所表示的二进制数 $pr$ 的按位与后 $1$ 的个数。然后考虑更改，令 $v$ 为加的数，易得 ```x_u = (x_u << v & full) | (x_u >> (m - v))```，其中 $full = 2^m - 1$，是防止溢出用的。

都到这一步了，不会还有人不知道怎么优化吧。

既然是二进制的数，显然用 ```bitset``` 进行优化。就让 $cnt$ 数组变成 ```bitset``` 就行了。

时间复杂度：$\mathcal{O}(\dfrac{nm\log n}{w})$

[评测记录](https://www.luogu.com.cn/record/111943534)

---

## 作者：small_john (赞：2)

## 思路

首先，操作是在树上的，并且还是子树，众所周知子树的 dfs 序是连续的，所以直接把树拍到序列上做。

然后又区间加、区间查询，容易想到用线段树去维护。

发现质数这个限制没有啥好做转化的，但是模数不变，值域还不大。考虑直接对每个线段树上的节点记录对应区间出现了哪些数，而在模意义下区间加在值域上是循环右移。

暴力做的时间复杂度 $O(nm\log n)$，而这个只有大概 $10^9$ 的量级，套个 bitset 优化即可。

查询完区间里有哪些数过后，把结果和最开始筛出来的质数按位且起来输出其一的个数即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

template<typename T> inline void read(T &x)
{
	x = 0;
	T f = 1;char ch = getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			f = -1,ch = getchar();
			break;
		}
		ch = getchar();
	}
	while(ch>='0'&&ch<='9')
		x = (x<<3)+(x<<1)+ch-48,ch = getchar();
	x*=f;
}
template<typename T = int> inline T read()
{
	T x;read(x);return x;
}
template<typename T> void write(T x)
{
    if(x<0) x = -x,putchar('-');
    if(x>9) write(x/10);
    putchar(x%10+48);
}
template<typename T> inline void writen(T x)
{
    write(x);
    putchar(10);
}
const int N = 1e5+5,M = 1e3+10; 
int n,m,q,a[N],dfn[N],sz[N],pre[N],idx,p[M],cnt;
vector<int> g[N];
bitset<M> s0,vis;
struct node{
	bitset<M> val;
	int tag; 
}t[N<<2];
void dfs(int u,int fa)
{
	dfn[u] = ++idx,pre[idx] = u,sz[u] = 1;
	for(auto v:g[u])
	{
		if(v==fa) continue;
		dfs(v,u);
		sz[u]+=sz[v];
	}
}
#define ls (k<<1)
#define rs (k<<1|1)
inline void pushup(int k){t[k].val = t[ls].val|t[rs].val;}                                     
inline void add(int k,int v){v%=m,(t[k].tag+=v)%=m,t[k].val = (t[k].val<<v)|(t[k].val>>(m-v));}
inline void down(int k)
{
	if(t[k].tag)
	{
		add(ls,t[k].tag),add(rs,t[k].tag);
		t[k].tag = 0; 
	}
}
void build(int k,int l,int r)
{
	t[k].tag = 0;
	if(l==r) return t[k].val[a[pre[l]]] = 1,void();
	int mid = (l+r)/2;
	build(ls,l,mid),build(rs,mid+1,r);
	pushup(k);
}
void change(int k,int l,int r,int x,int y,int v)
{
	if(l>y||r<x) return;
	if(l>=x&&r<=y) return add(k,v);
	int mid = (l+r)/2;
	down(k);
	change(ls,l,mid,x,y,v),change(rs,mid+1,r,x,y,v);
	pushup(k);
}
bitset<M> ask(int k,int l,int r,int x,int y)
{
	if(l>y||r<x) return s0;
	if(l>=x&r<=y) return t[k].val;
	int mid = (l+r)/2;
	down(k);
	return ask(ls,l,mid,x,y)|ask(rs,mid+1,r,x,y);
}
#undef ls
#undef rs
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n),read(m);
	for(int i = 1;i<=n;i++)
		read(a[i]),a[i]%=m;
	for(int i = 1,u,v;i<n;i++)
		read(u),read(v),g[u].push_back(v),g[v].push_back(u);
	dfs(1,0);
	build(1,1,n);
	s0.reset();
	vis.reset();
	vis[0] = vis[1] = 1;
	for(int i = 2;i<m;i++)
	{
		if(!vis[i]) p[++cnt] = i;
		for(int j = 1;j<=cnt&&i*p[j]<m;j++)
		{
			vis[i*p[j]] = 1;
			if(i%p[j]==0) break;
		}
	}
	vis.reset();
	for(int i = 1;i<=cnt;i++)
		vis[p[i]] = 1;
	read(q);
	while(q--)
	{
		int op,x,v;
		read(op),read(x);
		if(op==1) read(v),change(1,1,n,dfn[x],dfn[x]+sz[x]-1,v);
		else
		{
			auto res = ask(1,1,n,dfn[x],dfn[x]+sz[x]-1);
			res&=vis;
			writen(res.count());
		}
	}
	return 0;
}
```

---

## 作者：Kingna (赞：1)

学校的模拟赛题，当时没补，现在回头看直接秒了。


首先可以知道：可以将子树通过 dfn 序转化为序列。

有一个思路是：维护大约 $200$ 个树状数组来存储每个质数在区间中出现次数。复杂度 $O(200\times n\log n)$。由于当时模拟赛数据较水，直接过了。

换一个思路，有一个限制：$m\leq 1000$，这意味着我们完全可以将区间内开一个大小为 $1000$ 的数组代表这个数是否出现。可以用线段树维护这类信息， `push_up` 时只需要将左子树维护的数组和右子树维护的数组或起来。区间加上一个数 $x$ 相当于平移 $x$ 单位，并且超出 $m$ 范围的要循环移位。

复杂度 $O(nm\log n)$。肯定过不去。甚至还不如之前做法。

但是我们发现：我们数组维护的全是 01 信息，可以用 bitset 来代替。`push_up` 直接 `tree[p].s = (tree[ls].s | tree[rs].s)`，区间加直接 `tree[p].s = (((tree[p].s) >> (m - x)) | (tree[p].s << x))`。

复杂度 $O(\dfrac{nm\log n}{32})$。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ls p << 1
#define rs p << 1 | 1
#define int long long
const int N = 3e5 + 5;

int n, m, q, a[N], din[N], dout[N], idx, vis[N], vv[N];
vector<int> G[N];

void dfs(int u, int fa) {
	din[u] = ++idx;
	for (auto v : G[u]) {
		if (v == fa) continue;
		dfs(v, u);
	}
	dout[u] = idx;
}

struct edge {
	int l, r, lazy;
	bitset<1005> s;
}tree[N * 4];

int check(int x) {
	if (x == 1 || x == 0) return 0;
	if (x == 2) return 1;
	for (int i = 2; i <= x / i; i++) {
		if (x % i == 0) return 0;
	}
	return 1;
}

void push_up(int p) {
	tree[p].s = (tree[ls].s | tree[rs].s);
}

void down(int p, int x) {
	tree[p].lazy += x; tree[p].lazy %= m;
	tree[p].s = (((tree[p].s) >> (m - x)) | (tree[p].s << x));
}

void push_down(int p) {
	if (tree[p].lazy) {
		tree[p].lazy %= m;
		down(ls, tree[p].lazy); down(rs, tree[p].lazy);
		tree[p].lazy = 0;
	}
}

void build(int p, int l, int r) {
	tree[p].l = l, tree[p].r = r;
	if (l == r) {
		tree[p].s.set(vv[l], 1);
		return; 
	}
	int mid = (l + r) >> 1;
	build(ls, l, mid);
	build(rs, mid + 1, r);
	push_up(p);
}

void modify(int p, int l, int r, int v) {
	if (l <= tree[p].l && tree[p].r <= r) {
		tree[p].s = (((tree[p].s) >> (m - v)) | (tree[p].s << v));
		tree[p].lazy += v; tree[p].lazy %= m;
		return;
	}
	push_down(p);
	int mid = (tree[p].l + tree[p].r) >> 1;
	if (l <= mid) modify(ls, l, r, v);
	if (r > mid) modify(rs, l, r, v);
	push_up(p);
}

bitset<1005> ans;
void query(int p, int l, int r) {
	if (l <= tree[p].l && tree[p].r <= r) {
		ans |= tree[p].s;
//		cout << tree[p].s << endl;
		return;
	}
	push_down(p);
	int mid = (tree[p].l + tree[p].r) >> 1;
	if (l <= mid) query(ls, l, r);
	if (r > mid) query(rs, l, r);
}

signed main() {
//	freopen("CF633G.in", "r", stdin);
//	freopen("2.out", "w",stdout);
	for (int i = 0; i <= 1000; i++) vis[i] = check(i);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i], a[i] %= m;
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1, 0);
	for (int i = 1; i <= n; i++) vv[din[i]] = a[i];
	build(1, 1, idx);
	cin >> q;
	while (q--) {
		int op, x, v;
		cin >> op >> x;
		if (op == 1) {
			cin >> v;
			modify(1, din[x], dout[x], v % m);
		}
		else {
			ans.reset();
			query(1, din[x], dout[x]);
			int res = 0;
			for (int i = 1; i < m; i++) {
				if (ans[i] && vis[i]) res++; 
			}
			cout << res << endl;
		}
	} 
}
```

---

## 作者：MornStar (赞：1)

# CF633G Yash And Trees 题解
## 题面
[CF633G](https://www.luogu.com.cn/problem/CF633G)

## sol

非常好线段树练手题。

非常好 bitset 练手题。

所以我分块（挨打）。

首先发现 $m\le1000$，所以可以先把质数都筛出来。

其次发现操作在树上进行，所以用 dfn 序将数拍成序列。

然后块长这样：

```cpp
struct Block{
	int l,r,tag;
	bitset<1005>ans;
	void get(){
		ans=0;
		for(int i=l;i<=r;i++)	ans[(b[i]+tag)%m]=1;
	}
}block[350];
```

tag 表示这个块整体被加上的数的和模 $m$。

ans 是块内的数去重后的桶。

接下来就是很模板化的区间加，但是对于更新整块，可以使用 bitset 的移位操作。

```block[i].ans=((block[i].ans<<val)&S)|(block[i].ans>>(m-val))```其中 $S$ 为全集，防止溢出。

```cpp
void change(int l,int r,int val){
	val%=m;
	if(in_block[l]==in_block[r]){
		for(int i=l;i<=r;i++)	b[i]=(b[i]+val)%m;
		block[in_block[l]].get();
	}else{
		for(int i=l;i<=block[in_block[l]].r;i++)	b[i]=(b[i]+val)%m;
		for(int i=block[in_block[r]].l;i<=r;i++)	b[i]=(b[i]+val)%m;
		block[in_block[l]].get();
		block[in_block[r]].get();	
		for(int i=in_block[l]+1;i<=in_block[r]-1;i++)	block[i].ans=((block[i].ans<<val)&S)|(block[i].ans>>(m-val)),block[i].tag=(block[i].tag+val)%m;
	}
}
```

查询就用另一个 bitset 与出区间内去重后的数，与质数集与一下，再 count() 就可以了。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,q,a[100005],dfn[100005],siz[100005],b[100005],cnt;
int block_len,block_num,in_block[100005];
int pr[200],num;
bitset<1005>f,S;
vector<int>e[100005];
void get_f(){
	for(int i=2;i<=1000;i++)	f[i]=1;
	for(int i=2;i<=1000;i++){
		if(f[i])	pr[++num]=i;
		for(int j=1;j<=num&&pr[j]*i<=1000;j++){
			f[pr[j]*i]=0;
			if(i%pr[j]==0)	break;
		}
	}
}
struct Block{
	int l,r,tag;
	bitset<1005>ans;
	void get(){
		ans=0;
		for(int i=l;i<=r;i++)	ans[(b[i]+tag)%m]=1;
	}
}block[350];
void dfs(int x,int fa){
	dfn[x]=++cnt,siz[x]=1;
	for(auto it:e[x]){
		if(it!=fa){
			dfs(it,x);
			siz[x]+=siz[it];
		}
	}
}
void change(int l,int r,int val){
	val%=m;
	if(in_block[l]==in_block[r]){
		for(int i=l;i<=r;i++)	b[i]=(b[i]+val)%m;
		block[in_block[l]].get();
	}else{
		for(int i=l;i<=block[in_block[l]].r;i++)	b[i]=(b[i]+val)%m;
		for(int i=block[in_block[r]].l;i<=r;i++)	b[i]=(b[i]+val)%m;
		block[in_block[l]].get();
		block[in_block[r]].get();	
		for(int i=in_block[l]+1;i<=in_block[r]-1;i++)	block[i].ans=((block[i].ans<<val)&S)|(block[i].ans>>(m-val)),block[i].tag=(block[i].tag+val)%m;
	}
}
int query(int l,int r){
	bitset<1005>ans=0;
	if(in_block[l]==in_block[r]){
		for(int i=l;i<=r;i++)	ans[(b[i]+block[in_block[l]].tag)%m]=1;
	}else{
		for(int i=l;i<=block[in_block[l]].r;i++)	ans[(b[i]+block[in_block[l]].tag)%m]=1;
		for(int i=block[in_block[r]].l;i<=r;i++)	ans[(b[i]+block[in_block[r]].tag)%m]=1;
		for(int i=in_block[l]+1;i<=in_block[r]-1;i++)	ans|=block[i].ans;
	}
	return (ans&f).count();
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	get_f();
	cin>>n>>m;
	for(int i=1;i<=n;i++)	cin>>a[i],a[i]%=m;
	for(int i=0;i<m;i++) S[i]=1;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)	b[dfn[i]]=a[i];
	block_len=sqrt(n);
	for(int i=1;i<=n;i+=block_len){
		block_num++;
		block[block_num].l=i,block[block_num].r=min(n,i+block_len-1);
		for(int j=i;j<=block[block_num].r;j++)	in_block[j]=block_num;
		block[block_num].get();
	}
	cin>>q;
	for(int i=1,opt,rt,val;i<=q;i++){
		cin>>opt>>rt;
		if(opt==1){
			cin>>val;
			change(dfn[rt],dfn[rt]+siz[rt]-1,val);
		}else	cout<<query(dfn[rt],dfn[rt]+siz[rt]-1)<<"\n";
	}
}
```

时间复杂度 $O(\frac{nm\sqrt{n}}{w})$，超两秒喜提最劣解。


---

## 作者：Arghariza (赞：1)

简单题。

先把树拍扁成序列，在 dfn 序上区间修改区间查询。

由于时限 4s，我们可以整点怪的，比如 `bitset`。

把区间内的数有/没有表示成 $01$ 序列，考虑到区间加取模相当于区间内的数全部**循环右移**，用 `bitset` 可以做到 $O(\frac m \omega)$。

然后用线段树维护这个序列就行了，查询的时候和质数的 `bitset` 与一下，复杂度 $O\left(\dfrac{nm\log n}{\omega}\right)$。跑得飞快。

```cpp
#include <bits/stdc++.h>
using namespace std;

namespace vbzIO {
	char ibuf[(1 << 20) + 1], *iS, *iT;
	#if ONLINE_JUDGE
	#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
	#else
	#define gh() getchar()
	#endif
	#define rd read
	#define wr write
	#define pc putchar
	#define pi pair<int, int>
	#define mp make_pair
	#define fi first
	#define se second
	#define pb push_back
	#define ins insert
	#define era erase
	inline int read () {
		char ch = gh();
		int x = 0;
		bool t = 0;
		while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
		return t ? ~(x - 1) : x;
	}
	inline void write(int x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}
using vbzIO::read;
using vbzIO::write;

const int N = 1e5 + 100;
const int M = 1e3 + 100;
int n, m, q, dfc, tot, pr[M], a[N], id[N], p[N], sz[N], tg[N << 2];
vector<int> g[N];
bitset<M> tr[N << 2], vis, S;

void dfs(int u, int fa) {
	p[id[u] = ++dfc] = u, sz[u] = 1;
	for (int v : g[u]) {
		if (v == fa) continue;
		dfs(v, u), sz[u] += sz[v];
	}
}

#define ls x << 1
#define rs x << 1 | 1
#define mid ((l + r) >> 1)
void pushup(int x) { tr[x] = tr[ls] | tr[rs]; }
void pushtg(int x, int c) {
	c %= m, tg[x] = (tg[x] + c) % m;
	tr[x] = (tr[x] >> (m - c)) | ((tr[x] << c) & S);
}

void pushdown(int x) {
	if (!tg[x]) return;
	pushtg(ls, tg[x]), pushtg(rs, tg[x]);
	tg[x] = 0;
}

void build(int l, int r, int x) {
	if (l == r) return tr[x][a[p[l]]] = 1, void();
	build(l, mid, ls), build(mid + 1, r, rs), pushup(x);
}

void add(int l, int r, int s, int t, int c, int x) {
	if (s <= l && r <= t) return pushtg(x, c);
	pushdown(x);
	if (s <= mid) add(l, mid, s, t, c, ls);
	if (t > mid) add(mid + 1, r, s, t, c, rs);
	pushup(x);
}

auto qry(int l, int r, int s, int t, int x) {
	if (s <= l && r <= t) return tr[x];
	pushdown(x);
	if (s > mid) return qry(mid + 1, r, s, t, rs);
	else if (t <= mid) return qry(l, mid, s, t, ls);
	else return qry(l, mid, s, t, ls) | qry(mid + 1, r, s, t, rs);
}

int main() {
	n = rd(), m = rd();
	for (int i = 1; i <= n; i++) a[i] = rd() % m;
	for (int i = 1, u, v; i <= n - 1; i++) {
		u = rd(), v = rd();
		g[u].pb(v), g[v].pb(u);
	}
	dfs(1, 0), build(1, n, 1);
	vis.set(), vis[1] = vis[0] = 0;
	for (int i = 2; i <= m; i++) {
		if (vis[i]) pr[++tot] = i;
		for (int j = 1; j <= tot && i * pr[j] <= m; j++) {
			vis[i * pr[j]] = 0;
			if (i % pr[j] == 0) break;
		}
	}
	for (int i = 0; i <= m - 1; i++) S[i] = 1;
	q = rd();
	while (q--) {
		int op = rd(), u = rd();
		if (op == 1) {
			int v = rd();
			add(1, n, id[u], id[u] + sz[u] - 1, v % m, 1);
		} else wr((qry(1, n, id[u], id[u] + sz[u] - 1, 1) & vis).count()), puts("");
	}
	
	return 0;
}

```

---

## 作者：Erina (赞：1)

## CF633G

一道恶心的dfn线段树题目.

题意简介: 两种操作, 第一个是区间加法, 第二个是区间取余之后数**不同的**质数个数.

看起来很奇怪, 但是通过经验, 每一次遇见一个奇怪的题, 先看数据范围里面最小的数: $m(m\leqslant1000)$, 也就是膜数. 膜数很小, 不妨先把树拍平, 然后建一颗线段树, 每个节点存一个大小为$m$的线段树, 记录里面膜$m$不同的数有多少个. 然后所有的操作就很清晰了.

放上丑陋的代码

```cpp
#include<iostream>
#include<bitset>
#include<queue>
#define mid ((l+r)>>1)
using namespace std;
int n, m, q;
int arr[100005];
bitset<1005>full;// 全部为1, 去掉左移时产生的越界的1
bitset<1005>tree[400005];// 线段树
int tag[400005];// lazy_tag
vector<int>road[100005];// 存图
int id[100005], dfn[100005], las[100005], cnt;// 拍平整棵树
void dfs(int x, int pa) {// 拍平整棵树
	id[++cnt] = x; dfn[x] = cnt;
	for (int it : road[x])if (it != pa)dfs(it, x);
	las[x] = cnt;
}
void push_up(int id) {
	tree[id] = tree[id << 1] | tree[id << 1 | 1];
}
void operate(int id, int v) {// 加法操作, 并且取余
	tag[id] += v; if (tag[id] >= m)tag[id] -= m;
	tree[id] = ((tree[id] << v) & full) | (tree[id] >> (m - v));
}
void push_down(int id) { if (tag[id])operate(id << 1, tag[id]), operate(id << 1 | 1, tag[id]), tag[id] = 0; }
void build(int l, int r, int id) {
	if (l == r) {
		tree[id].reset();
		tree[id].set(arr[::id[l]]);
		return;
	}
	build(l, mid, id << 1), build(mid + 1, r, id << 1 | 1), push_up(id);
}
void shift(int l, int r, int s, int t, int v, int id) {// 区间加法
	if (r<s || l>t)return;
	if (s <= l && r <= t)operate(id, v);
	else push_down(id), shift(l, mid, s, t, v, id << 1), shift(mid + 1, r, s, t, v, id << 1 | 1), push_up(id);
}
bitset<1005>ans, prime;
void query(int l, int r, int s, int t, int id) {// (我的)标准线段树写法......
	if (r<s || l>t)return;
	if (s <= l && r <= t)ans |= tree[id];
	else push_down(id), query(l, mid, s, t, id << 1), query(mid + 1, r, s, t, id << 1 | 1), push_up(id);
}
int main() {
	cin >> n >> m;
	for (int i = 0; i < m; i++)full.set(i);
	for (int i = 1; i <= n; i++)cin >> arr[i], arr[i] %= m;
	for (int i = 1; i < n; i++) {
		int l, r;
		cin >> l >> r;
		road[l].emplace_back(r);
		road[r].emplace_back(l);
	}
	cin >> q;
	dfs(1, 0);
	build(1, n, 1);
	for (int i = 2; i < m; i++)prime.set(i);
	for (int i = 2; i < m; i++)
		if (prime[i])
			for (int u = (i << 1); u <= m; u += i)
				prime.reset(u);// 处理质数的bitset
	for (int i = 1; i <= q; i++) {
		int op;
		cin >> op;
		if (op == 1) {
			int x, q;
			cin >> x >> q;
			q %= m;
			shift(1, n, dfn[x], las[x], q, 1);
		}
		else {
			int x;
			cin >> x;
			ans.reset();
			query(1, n, dfn[x], las[x], 1);
			cout << (ans & prime).count() << endl;// bitset的count()函数处理一的数量.
		}
	}
}
```


---

## 作者：ybc2026lhy (赞：0)

又是一个难度虚高的无思维难度题。

树上子树操作直接搞 dfs 序下来，那么 $u$ 的子树区间在 dfs 序上对应 $[dfn_u,dfn_u+siz_u-1]$。

问题转变为区间操作，注意到 $m$ 很小，而我们只关心有多少种并不关心具体数量，所以直接对线段树上每个结点开一个 bitset 即可。

区间加就相当于这个区间的 bitset 集体左移，注意还有最左边的一部分位要移到最右边。

这里口胡一下 bitset 的区间清 0 的操作，比如要将后 len 位清零就先右移 len 位再左移回来即可。

在外面预处理一个质数的 bitset，那么答案为区间的 bitset 或起来，然后再与上质数的 bitset，答案就是 1 的个数。

复杂度 $\frac{(nm)\log n}{w}$。实测跑得不慢，只用了 1.2s。

---

## 作者：orz_z (赞：0)



用 `dfs` 序把树拍成区间，转化为区间问题。

建线段树，维护区间 `bitset` 表示一个取模后的数是否在区间内出现过。

答案即为区间的 `bitset` $\&$ 质数集的 `bitset` 得到的 `bitset` 中 $1$ 的个数。

时间复杂度 $\mathcal O(\frac{nm\log n}{\omega})$。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

inline ll read()
{
	ll x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9')
	{
		if (c == '-')
			f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
		x = x * 10ll + c - '0', c = getchar();
	return x * f;
}

const int _ = 1e5 + 10;

int n, m, q, a[_];

bitset<1005> full, tr[_ << 2], ans, pr;

int lz[_ << 2];

int id[_], dfn[_], ed[_], cnt;

vector<int> d[_];

void dfs(int u, int fa)
{
	id[++cnt] = u, dfn[u] = cnt;
	for(int v : d[u]) if(v != fa) dfs(v, u);
	ed[u] = cnt;
}

void pushup(int o)
{
	tr[o] = tr[o << 1] | tr[o << 1 | 1];
}

void tag(int o, int v)
{
	lz[o] += v;
	if(lz[o] >= m) lz[o] -= m;
	tr[o] = ((tr[o] << v) & full) | (tr[o] >> (m - v));
}

void pushdown(int o)
{
	if(lz[o])
		tag(o << 1, lz[o]), tag(o << 1 | 1, lz[o]), lz[o] = 0;
}

void build(int o, int l, int r)
{
	if(l == r)
	{
		tr[o].reset();
		tr[o].set(a[id[l]]);
		return;
	}
	int mid = (l + r) >> 1;
	build(o << 1, l, mid), build(o << 1 | 1, mid + 1, r);
	pushup(o);
}

void update(int o, int l, int r, int L, int R, int v)
{
	if(r < L || l > R) return;
	if(L <= l && r <= R) return tag(o, v), void();
	pushdown(o);
	int mid = (l + r) >> 1;
	if(L <= mid)
		update(o << 1, l, mid, L, R, v);
	if(R > mid)
		update(o << 1 | 1, mid + 1, r, L, R, v);
	pushup(o);
}

void query(int o, int l, int r, int L, int R)
{
	if(r < L || l > R) return;
	if(L <= l && r <= R) return ans |= tr[o], void();
	pushdown(o);
	int mid = (l + r) >> 1;
	if(L <= mid) query(o << 1, l, mid, L, R);
	if(R > mid) query(o << 1 | 1, mid + 1, r, L, R);
	pushup(o);
}

signed main()
{
	n = read(), m = read();
	for(int i = 0; i < m; ++i) full.set(i);
	for(int i = 1; i <= n; ++i) a[i] = read() % m;
	for(int i = 1, u, v; i < n; ++i)
	{
		u = read(), v = read();
		d[u].push_back(v);
		d[v].push_back(u);
	}
	q = read();
	dfs(1, 0);
	build(1, 1, n);
	for(int i = 2; i < m; ++i) pr.set(i);
	for(int i = 2; i < m; ++i)
		if(pr[i])
			for(int j = i * 2; j <= m; j += i)
				pr.reset(j);
	int op, x, y;
	while(q--)
	{
		op = read();
		if(op == 1)
		{
			x = read(), y = read() % m;
			update(1, 1, n, dfn[x], ed[x], y);
		}
		else
		{
			x = read();
			ans.reset();
			query(1, 1, n, dfn[x], ed[x]);
			cout << (ans & pr).count() << "\n";
		}
	}
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

`bitset` 和线段树融合。

## 思路

考虑先把树跑一遍 dfs 序扔到序列上操作。这样会方便许多。问题变成区间修改（统一加）区间查询。

容易发现 $m$ 不大，可以记录一段区间内有没有这个数，需要使用 `bitset` 去操作。

对于加法操作，实际上就是 `<<` 操作，在线段树上需要使用一个 `lazytag` 来维护，维护的时候每次先取出 `bitset` 的前 `lazytag` 位（操作时候就是右移长度减去 `lazytag` 位），然后将剩余位向左移 `lazytag` 位或起来即可，本质上是模拟一个循环。

剩下来就是经典线段树，或许你需要注意一下常数。

细节还可以，复杂度 $O(\dfrac{nm\log n}{w})$，可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
#define s(i,j) ((i-1)*m+j)
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
const int mod=1e9+7;
vector<int> vc[100005];
int a[100005];
int cnt,ind[100005],outd[100005],num[100005];
void dfs(int now,int fa){
	ind[now]=++cnt;
	num[cnt]=a[now];
	for(auto v:vc[now]) if(v!=fa) dfs(v,now);
	outd[now]=cnt;
}
int m;
struct sgt{
	bitset<1000> f[400005],ept;
	int lzt[400005];
	void pushdown(int i){
		f[i*2]=((f[i*2]>>(m-lzt[i]))|(f[i*2]<<lzt[i]));
		(lzt[i*2]+=lzt[i])%=m;
		f[i*2+1]=((f[i*2+1]>>(m-lzt[i]))|(f[i*2+1]<<lzt[i]));
		(lzt[i*2+1]+=lzt[i])%=m;
		lzt[i]=0;
	}
	void build(int i,int l,int r){
		if(l==r){
			f[i].set(num[l]);
			return ;
		}
		build(i*2,l,mid),build(i*2+1,mid+1,r);
		f[i]=f[i*2]|f[i*2+1];
	}
	void change(int i,int l,int r,int ql,int qr,int cg){
		if(ql<=l&&r<=qr){
			f[i]=((f[i]>>(m-cg))|(f[i]<<cg));
			(lzt[i]+=cg)%=m;
			return ;
		}
		pushdown(i);
		if(ql<=mid) change(i*2,l,mid,ql,qr,cg);
		if(qr>mid) change(i*2+1,mid+1,r,ql,qr,cg);
		f[i]=f[i*2]|f[i*2+1];
	}
	bitset<1000> qry(int i,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr) return f[i];
		if(ql>r||qr<l) return ept;
		pushdown(i);
		return qry(i*2,l,mid,ql,qr)|qry(i*2+1,mid+1,r,ql,qr);
	}
}tree;
int prm[100005],tot;
bool isp(int n){
	for(int i=2;i*i<=n;i++) if(n%i==0) return false;
	return true;
}
signed main(){
	int n;
	cin>>n>>m;
	for(int i=2;i<m;i++) if(isp(i)) prm[++tot]=i;
	for(int i=1;i<=n;i++) cin>>a[i],a[i]%=m;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		vc[u].push_back(v);
		vc[v].push_back(u);
	}
	dfs(1,0);
	tree.build(1,1,n);
	int q;
	cin>>q;
	while(q--){
		int opt;
		cin>>opt;
		if(opt==1){
			int u,v;
			cin>>u>>v; v%=m;
			tree.change(1,1,n,ind[u],outd[u],v);
		}
		else{
			int u;
			cin>>u;
			auto v=tree.qry(1,1,n,ind[u],outd[u]);
			int ans=0;
			for(int i=1;i<=tot;i++){
				ans+=v[prm[i]];
			}
			cout<<ans<<endl;
		}
	}
	return 0;
}
```

---

## 作者：_SeeleVollerei_ (赞：0)

又是一个难度虚高的无思维难度题。

树上子树操作直接搞 dfs 序下来，那么 u 的子树区间在 dfs 序上对应 $[dfn_u,dfn_u+siz_u-1]$。

问题转变为区间操作，注意到 m 很小，而我们只关心有多少种并不关心具体数量，所以直接对线段树上每个结点开一个 bitset 即可。

区间加就相当于这个区间的 bitset 集体左移，注意还有最左边的一部分位要移到最右边。

这里口胡一下 bitset 的区间清 0 的操作，比如要将后 len 位清零就先右移 len 位再左移回来即可。

在外面预处理一个质数的 bitset，那么答案为区间的 bitset 或起来，然后再与上质数的 bitset，答案就是 1 的个数。

复杂度 $O(\frac{nm\log n}{w})$。实测跑得不慢，只用了 1.2s。

https://codeforces.com/contest/633/submission/167127754

---

## 作者：Xdik (赞：0)

因为这道题是在树上的，所以我们很套路地先 dfs 一次 ，这样一颗子树上的结点的 $dfn$ 就在一起了，对子树的操作就转化为对区间的操作，但是怎么数区间内出现了哪些数呢？因为是对区间加了 $x$ 后再 $mod$ $m$ 所以相当于是将这个区间原本有的数整体向右移了 $x$ 位，然后再将超过了 $m$ 这个范围的数重新接到最前面去，因为我们只需要知道出现了哪些数而不用知道这些数出现了多少次，且注意到题面中的 $m\leq 1000$ ，范围比较小 所以我们就可以用一个只记录这个数是否出现过且十分方便移动的东西 : **bitset**  ~~然而我当时不会用导致考场爆零~~ 这样，我们添加操作就十分简单了，只需要对这个区间的 bitset 整体向左移 $x$ 位，再将后面的 $x$ 位移到前面来就可以了(具体就是将原来的 bitset 左移 $x$ 位再或上原来的 bitset 右移 $(m-x)$ 位 )，那么统计答案的时候就将整个区间的 bitset 全部或起来，在最开始的时候创造一个 bitset 来记录哪些是质数，最后再将这两个 bitset 与起来，一的数量就是最终的答案，对于维护区间，我一开始是想写分块的，后面感觉不够快就改成了线段树，时间复杂度显然是能够通过本题的

AC Code：

```cpp

#include <bits/stdc++.h>
#define ing long long
#pragma GCC optimeze(3)
#pragma GCC optimeze(2)
using namespace std;
const int N = 2e5 + 5;
int read() {
    int x = 0, flag = 1;
    char ch = 0;
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            flag = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 1) + (x << 3) + ch - '0';
        ch = getchar();
    }
    return x * flag;
}
int n, a[N], ver[N * 2], head[N], ne[N * 2], dfn[N], rk[N], cnt, tot, siz[N], m, q, sum = 0;
bool vis[1005];
bitset<1000> tr[N * 4], help, jb;
int b[N * 4];
void add(int x, int y) { ver[++tot] = y, ne[tot] = head[x], head[x] = tot; }
void dfs(int t, int f) {
    dfn[t] = ++cnt;
    rk[cnt] = t;
    siz[t] = 1;
    for (int i = head[t]; i; i = ne[i]) {
        int to = ver[i];
        if (to == f)
            continue;
        dfs(to, t);
        siz[t] += siz[to];
    }
}
void pushdown(int p) {
    tr[p * 2] = ((tr[p * 2] >> (m - b[p])) | (tr[p * 2] << b[p]));
    b[p * 2] += b[p];
    b[p * 2] %= m;
    tr[p * 2 + 1] = ((tr[p * 2 + 1] >> (m - b[p])) | (tr[p * 2 + 1] << b[p]));
    b[p * 2 + 1] += b[p];
    b[p * 2 + 1] %= m;
    b[p] = 0;
}
void pushup(int p) { tr[p] = tr[p * 2] | tr[p * 2 + 1]; }
void build(int p, int l, int r) {
    if (l == r) {
        tr[p][a[rk[l]] % m] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(p * 2, l, mid);
    build(p * 2 + 1, mid + 1, r);
    pushup(p);
}
void change(int l, int r, int x, int p, int s, int t) {
    if (s >= l && t <= r) {
        tr[p] = ((tr[p] >> (m - x)) | (tr[p] << x));
        b[p] += x;
        b[p] %= m;
        return;
    }
    int mid = (s + t) >> 1;
    pushdown(p);
    if (mid >= l)
        change(l, r, x, p * 2, s, mid);
    if (mid < r)
        change(l, r, x, p * 2 + 1, mid + 1, t);
    pushup(p);
}
bitset<1000> qu(int l, int r, int p, int s, int t) {
    if (s >= l && t <= r)
        return tr[p];
    int mid = (s + t) >> 1;
    pushdown(p);
    bitset<1000> ans = help;
    if (mid >= l)
        ans |= qu(l, r, p * 2, s, mid);
    if (mid < r)
        ans |= qu(l, r, p * 2 + 1, mid + 1, t);
    return ans;
}
signed main() {
    n = read(), m = read();
    vis[1] = 1;
    for (int i = 2; i < m; i++) {
        if (!vis[i]) {
            sum++;
            jb[i] = 1;
            for (int j = 2; j * i < m; j++) {
                vis[j * i] = 1;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        a[i] = read();
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        u = read(), v = read();
        add(u, v);
        add(v, u);
    }
    dfs(1, 0);
    build(1, 1, n);
    q = read();
    while (q--) {
        int opt, v, x;
        opt = read();
        if (opt == 1) {
            v = read(), x = read();
            x %= m;
            change(dfn[v], dfn[v] + siz[v] - 1, x, 1, 1, n);
        } else {
            v = read();
            cout << (qu(dfn[v], dfn[v] + siz[v] - 1, 1, 1, n) & jb).count() << endl;
        }
    }
    return 0;
}

---

