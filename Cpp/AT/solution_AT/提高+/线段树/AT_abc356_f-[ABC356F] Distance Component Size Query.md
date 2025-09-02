# [ABC356F] Distance Component Size Query

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc356/tasks/abc356_f

整数 $ K $ が与えられます。はじめ空である集合 $ S $ に対して、次の $ 2 $ 種類のクエリを順に $ Q $ 個処理してください。

- `1 x`：整数 $ x $ が与えられる。$ S $ に $ x $ が含まれているならば、$ S $ から $ x $ を取り除く。そうでないならば、$ S $ に $ x $ を追加する。
- `2 x`：$ S $ に含まれる整数 $ x $ が与えられる。$ S $ に含まれる数を頂点とし、差の絶対値が $ K $ 以下であるような数の間に辺を張ったグラフにおいて、$ x $ が属する連結成分の頂点数を出力する。

## 说明/提示

### 制約

- $ 1\ \leq\ Q\ \leq\ 2\times\ 10^5 $
- $ 0\ \leq\ K\ \leq\ 10^{18} $
- 各クエリにおいて、$ 1\leq\ x\ \leq\ 10^{18} $
- $ 2 $ 種類目のクエリにおいて与えられる $ x $ はその時点で $ S $ に含まれる。
- 入力は全て整数である。
 
### Sample Explanation 1

クエリの処理は次のように進行します。 - $ 1 $ 番目のクエリでは、$ S $ に $ 3 $ が追加され、$ S=\{3\} $ となります。 - $ 2 $ 番目のクエリでは、$ S $ に $ 10 $ が追加され、$ S=\{3,10\} $ となります。 - $ 3 $ 番目のクエリでは、$ 3,10 $ の $ 2 $ 頂点からなる辺のないグラフを考え、$ 3 $ が属する連結成分のサイズである $ 1 $ を出力します。 - $ 4 $ 番目のクエリでは、$ S $ に $ 7 $ が追加され、$ S=\{3,7,10\} $ となります。 - $ 5 $ 番目のクエリでは、$ 3,7,10 $ の $ 3 $ 頂点からなり、$ 3 $ と $ 7 $、$ 7 $ と $ 10 $ の間に辺のあるグラフを考え、$ 3 $ が属する連結成分のサイズである $ 3 $ を出力します。 - $ 6 $ 番目のクエリでは、$ S $ から $ 10 $ が削除され、$ S=\{3,7\} $ となります。 - $ 7 $ 番目のクエリでは、$ 3,7 $ の $ 2 $ 頂点からなり、$ 3 $ と $ 7 $ の間に辺のあるグラフを考え、$ 3 $ が属する連結成分のサイズである $ 2 $ を出力します。

## 样例 #1

### 输入

```
7 5
1 3
1 10
2 3
1 7
2 3
1 10
2 3```

### 输出

```
1
3
2```

## 样例 #2

### 输入

```
11 1000000000000000000
1 1
1 100
1 10000
1 1000000
1 100000000
1 10000000000
1 1000000000000
1 100000000000000
1 10000000000000000
1 1000000000000000000
2 1```

### 输出

```
10```

## 样例 #3

### 输入

```
8 0
1 1
1 2
2 1
1 1
1 2
1 1
1 2
2 1```

### 输出

```
1
1```

# 题解

## 作者：ran_qwq (赞：5)

显然，如果一条边中间跳过了某个点，肯定是不优的。所以我们只考虑相邻的边。

动态维护点集 $S$，和所有长度大于 $K$ 的相邻边集 $T$。

插入/删除时找到 $S$ 前驱和后继，对 $T$ 的变化不大，动态维护即可。

查询时找到 $x$ 在 $T$ 中的前驱和后继，求中间有多少个点在 $S$ 内。

这个相当于求排名（后继排名减去前驱排名），有很多种做法，如离散化+树状数组，权值线段树，平衡树等。我用的是离散化+树状数组。

时间复杂度 $O(n\log n)$。感觉这题写线段树分治挺蠢的，平白无故多一个 log。

细节挺多的，代码：

```cpp
int n,tot,OP[N]; ll m,X[N],a[N],d[N]; set<ll> S; set<pair<ll,ll>> T;
struct BIT {
	int c[N];
	il int lbt(int x) {return x&-x;}
	void upd(int x,int y) {for(;x<=tot;x+=lbt(x)) c[x]+=y;}
	int qry(int x) {int res=0; for(;x;x-=lbt(x)) res+=c[x]; return res;}
}TT;
void QwQ() {
	n=rd(),m=rdll();
	for(int i=1;i<=n;i++) OP[i]=rd(),X[i]=a[i]=d[i]=rdll();
	sort(a+1,a+1+n),tot=unique(a+1,a+1+n)-a-1;
	for(int i=1;i<=n;i++) {
		int op=OP[i]; ll x=X[i];
		if(op==1) {
			if(S.count(x)) {
				auto it=S.find(x); ll p,q;
				if(S.size()==1) S.erase(x); 
				else if(it==S.begin()) {q=*next(it),S.erase(x); if(q-x>m) T.erase({x,q});}
				else if(it==prev(S.end())) {p=*prev(it),S.erase(x); if(x-p>m) T.erase({p,x});}
				else {p=*prev(it),q=*next(it); S.erase(x); if(x-p>m) T.erase({p,x}); if(q-x>m) T.erase({x,q}); if(q-p>m) T.insert({p,q});}
				TT.upd(lb(a+1,a+1+tot,X[i])-a,-1);
			} else {
				auto it=S.lb(x); ll p,q;
				if(!S.size()) S.insert(x);
				else if(it==S.begin()) {q=*it,S.insert(x); if(q-x>m) T.insert({x,q});}
				else if(it==S.end()) {p=*prev(it),S.insert(x); if(x-p>m) T.insert({p,x});}
				else {p=*prev(it),q=*it,S.insert(x); if(x-p>m) T.insert({p,x}); if(q-x>m) T.insert({x,q}); if(q-p>m) T.erase({p,q});}
				TT.upd(lb(a+1,a+1+tot,X[i])-a,1);
			}
		} else {
			if(!T.size()) wr(S.size(),"\n");
			else {
				auto it=T.lb({x,0}); ll p,q;
				if(it==T.end()) p=prev(it)->sec,wr(TT.qry(tot)-TT.qry(lb(a+1,a+1+tot,p)-a)+1,"\n");
				else if(it==T.begin()) q=it->fir,wr(TT.qry(lb(a+1,a+1+tot,q)-a),"\n");
				else p=prev(it)->sec,q=it->fir,wr(TT.qry(lb(a+1,a+1+tot,q)-a)-TT.qry(lb(a+1,a+1+tot,p)-a)+1,"\n");
			}
		}
	}
}
```

---

## 作者：Genius_Star (赞：5)

### 思路：

简单题，首先肯定要将数据离散化。

然后使用线段树维护区间联通块的个数和区间数的个数。

询问时要找到尽可能靠左的和尽可能靠右的到 $x$ 的联通块的个数为 $1$ 的两个位置，二分即可。

时间复杂度为 $O(N \log^2 W)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
using namespace std;
typedef double db;
typedef long long ll;
const ll N=2e5+10;
mt19937 R(time(0));
inline ll Rand(ll l,ll r){
	if(l==r)
	  return l;
	return R()%(r-l+1)+l;
}
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
struct Node{
	ll L,R;
	ll ans;
	ll data;
}X[N<<2];
ll n,k,l,r,cnt;
ll op[N],x[N],a[N];
bool f[N];
Node merge(Node a,Node b){
	if(!a.data)
	  return b;
	if(!b.data)
	  return a;
	Node h;
	h.L=a.L,h.R=b.R;
	h.ans=a.ans+b.ans-(b.L-a.R<=k);
	h.data=a.data+b.data;
	return h;
}
void pushup(ll k){
	X[k]=merge(X[k<<1],X[k<<1|1]);
}
void update(ll k,ll l,ll r,ll i,ll v){
	if(l==i&&i==r){
		X[k].L=X[k].R=a[i];
		X[k].ans+=v;
		X[k].data+=v;
		return ;
	}
	ll mid=(l+r)>>1;
	if(i<=mid)
	  update(k<<1,l,mid,i,v);
	else
	  update(k<<1|1,mid+1,r,i,v);
	pushup(k);
}
Node query(ll k,ll l,ll r,ll L,ll R){
	if(l==L&&R==r)
	  return X[k];
	ll mid=(l+r)>>1;
	if(R<=mid)
	  return query(k<<1,l,mid,L,R);
	else if(L>mid)
	  return query(k<<1|1,mid+1,r,L,R);
	else
	  return merge(query(k<<1,l,mid,L,mid),query(k<<1|1,mid+1,r,mid+1,R));
}
int main(){
	n=read(),k=read(); 
	for(int i=1;i<=n;i++){
		op[i]=read(),x[i]=read();
		a[++cnt]=x[i];
	}
	sort(a+1,a+cnt+1);
	cnt=unique(a+1,a+cnt+1)-(a+1);
	for(int i=1;i<=n;i++){
		x[i]=lower_bound(a+1,a+cnt+1,x[i])-a;
		if(op[i]==1){
			if(f[x[i]])
			  update(1,1,cnt,x[i],-1);
			else
			  update(1,1,cnt,x[i],1);
			f[x[i]]^=1ll;
		}
		else{
			ll s1=0,s2=0;
			l=1,r=x[i];
			while(l<=r){
				ll mid=(l+r)>>1;
				auto t=query(1,1,cnt,mid,x[i]);
				if(t.ans==1){
					s1=t.data;
					r=mid-1;
				}
				else
				  l=mid+1;
			}
			l=x[i],r=cnt;
			while(l<=r){
				ll mid=(l+r)>>1;
				auto t=query(1,1,cnt,x[i],mid);
				if(t.ans==1){
					s2=t.data;
					l=mid+1;
				}
				else
				  r=mid-1;
			}	
			write(s1+s2-1);
			putchar('\n');
		}
	}
	return 0;
}
```

---

## 作者：GI录像机 (赞：4)

## 思路

本题难点在第二个操作上。容易发现，在一个连通块内的点肯定在一个连续区间内。

既然是维护区间，那么考虑权值线段树。每个结点存储该区间内的点数，该区间内的点是否连通，该区间最左边的点，该区间最右边的点（在后文分别称之为 $sum、ok、l、r$）。修改操作是很好维护的，和普通线段树一致。注意要判断有儿子为空的情况。

```cpp
void pushup(int pos) {
	a[pos].sum = a[a[pos].lson].sum + a[a[pos].rson].sum;
	a[pos].l = a[a[pos].lson].l, a[pos].r = a[a[pos].rson].r;
	if(!a[pos].l)a[pos].l = a[a[pos].rson].l;
	if(!a[pos].r)a[pos].r = a[a[pos].lson].r;
	a[pos].ok = a[a[pos].lson].ok && a[a[pos].rson].ok && (a[a[pos].rson].l - a[a[pos].lson].r <= k || !a[a[pos].rson].l || !a[a[pos].lson].r);
}
```


难在查询操作。我们需要通过一个点查询到一个区间，怎么做呢？

因为最终的区间肯定要包含 $x$，所以按照单点查询的规则往下找，直到找到第一个区间内点连通的结点，此时这个结点的所有后代都无需再找，直接返回。

但是不一定所有连通的点都恰好在这个结点内，我们可能会需要它以及它祖先的兄弟结点的一部分来凑成最终答案。

那么怎么知道哪些兄弟结点是我们需要的呢？兄弟结点中有答案一部分的前提条件是兄弟结点和自身的 $l、r$ 距离小于 $k$。如果小于 $k$，那么我们也知道了在兄弟结点内一个在答案里的点的位置。由于给出的约束条件具有传递性，我们可以寻找兄弟结点内包含其 $l$（或 $r$）的连通块，把这个子问题的答案加入最终答案，代码大概是这样（$L$ 代表的是 $x$）：

```cpp
if(L <= mid){
	ans = query(a[pos].lson, l, mid, L);
	if(a[a[pos].rson].l - ans.r <= k && a[a[pos].rson].l) {
		Node tmp = query(a[pos].rson, mid + 1, r, a[a[pos].rson].l);
		ans.sum += tmp.sum, ans.r = tmp.r;
	}
}
else {
	ans = query(a[pos].rson, mid + 1, r, L);
	if(ans.l - a[a[pos].lson].r <= k && a[a[pos].lson].r) {
		Node tmp = query(a[pos].lson, l, mid, a[a[pos].lson].r);
		ans.sum += tmp.sum, ans.l = tmp.l;
	}
}
```

值域过大，可以用离散化或者动态开点线段树，我选择的是后者。时间复杂度是 $O(Q\log V)$，其中 $V$ 为值域。

由于查询和普通的线段树不同，再来说一下时间复杂度。最后访问的 $ok=1$ 的区间只有 $\log$ 个，因为每次更换 $L$ 后当前 $ok$ 一定等于 $0$（否则其父亲的 $ok$ 已经等于 $1$，不会访问到，矛盾），区间大小至少折半。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read() {
	int f = 1, x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return f * x;
}
void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
const int N = 2e5 + 10, MOD = 1e9 + 7, INF = 0x3f3f3f3f;
int q = read(), k = read(), tot;
struct Node {
	int sum, l, r, lson, rson;
	bool ok;
} a[N << 6];
void pushup(int pos) {
	a[pos].sum = a[a[pos].lson].sum + a[a[pos].rson].sum;
	a[pos].l = a[a[pos].lson].l, a[pos].r = a[a[pos].rson].r;
	if (!a[pos].l)a[pos].l = a[a[pos].rson].l;
	if (!a[pos].r)a[pos].r = a[a[pos].lson].r;
	a[pos].ok = a[a[pos].lson].ok && a[a[pos].rson].ok && (a[a[pos].rson].l - a[a[pos].lson].r <= k || !a[a[pos].rson].l || !a[a[pos].lson].r);
}
void change(int pos, int l, int r, int L) {
	if (l == r) {
		if (a[pos].sum)a[pos].sum = a[pos].l = a[pos].r = 0;
		else a[pos].sum = 1, a[pos].l = a[pos].r = L;
		return;
	}
	int mid = (l + r) >> 1;
	if (!a[pos].lson) {
		a[pos].lson = ++tot;
		a[tot].ok = 1;
	}
	if (!a[pos].rson) {
		a[pos].rson = ++tot;
		a[tot].ok = 1;
	}
	if (L <= mid)change(a[pos].lson, l, mid, L);
	else change(a[pos].rson, mid + 1, r, L);
	pushup(pos);
}
Node query(int pos, int l, int r, int L) {
	if (a[pos].ok)return a[pos];
	int mid = (l + r) >> 1;
	if (!a[pos].lson) {
		a[pos].lson = ++tot;
		a[tot].ok = 1;
	}
	if (!a[pos].rson) {
		a[pos].rson = ++tot;
		a[tot].ok = 1;
	}
	Node ans;
	if (L <= mid) {
		ans = query(a[pos].lson, l, mid, L);
		if (a[a[pos].rson].l - ans.r <= k && a[a[pos].rson].l) {
			Node tmp = query(a[pos].rson, mid + 1, r, a[a[pos].rson].l);
			ans.sum += tmp.sum, ans.r = tmp.r;
		}
	} else {
		ans = query(a[pos].rson, mid + 1, r, L);
		if (ans.l - a[a[pos].lson].r <= k && a[a[pos].lson].r) {
			Node tmp = query(a[pos].lson, l, mid, a[a[pos].lson].r);
			ans.sum += tmp.sum, ans.l = tmp.l;
		}
	}
	return ans;
}
signed main() {
	//freopen(".in", "r", stdin);
	//freopen(".out", "w", stdout);
	a[++tot].ok = 1;
	while (q--) {
		int op = read(), x = read();
		if (op == 1)change(1, 1, 1e18, x);
		else {
			write(query(1, 1, 1e18, x).sum);
			putchar('\n');
		}
	}
	return 0;
}
```

---

## 作者：huanhuanonly (赞：4)

# ABC356F - Distance Component Size Query
---

## 前置知识

- FHQ-Treap
- 并查集

> 篇幅可能较长，但思路简单。

## 分析

根据题意，我们需要维护若干个集合，询问一个值所在的集合的大小（保证这个值一定存在某个集合中）~~，于是很容易想到了 **带权并查集**~~。

两种修改操作的大概实现方式：

- 添加一个元素 $value$ 的时候根据 $value$ 和前驱 $prev$ 以及后继 $next$ 的绝对值是否小于 $K$ 来选择如何合并集合。
  - 如果 $\vert{value-prev}\vert\le{K}$，插入 $value$ 到 $prev$ 所在的集合。
  - 如果 $\vert{next-value}\vert\le{K}$，插入 $value$ 到 $next$ 所在的集合。
  - 如果 $\vert{next-prev}\vert\le{K}$，插入 $value$ 到 $prev$ 所在的集合，并且与 $next$ 所在的集合合并。
- 删除一个元素 $value$ 的时候将 $value$ 所在的集合拆分成三个集合：$\{<value\},\{=value\},\{>value\}$，然后判断 $\{<value\}$ 的最大值（$value$ 的前驱）和 $\{>value\}$ 的最小值 （$value$ 的后继）的绝对值是否小于 $K$，小于 $K$ 则合并 $\{<value\}$ 和 $\{>value\}$，至于要被删除的 $value$，其实不需要真的删除，因为后面保证不会再用到（除非再添加回来）。

但是貌似并查集 **不能做拆分集合** 的操作，这时候怎么办呢？

我们发现拆分集合的操作和 FHQ-Treap 的 `split()` 函数很像，那是否能使用 FHQ-Treap 来 **替代实现** 并查集呢？是的！并查集的本质就是维护一个 $fa$ 数组，我们只要在 FHQ-Treap 的每个节点里维护它的父节点 $fa$，并在调用 `push_up()` 函数的时候更新它。

> 如此，一个 _支持拆分集合的并查集_ 就诞生啦！

## 具体做法

首先，我们编写一个 FHQ-Treap 的类：
```c++
class MultiTreap {...}
```

> 因为我们维护的是若干个集合，所以会有若干个根节点，相当于一个森林，也就是说这个类里维护了多棵 FHQ-Treap，但是我们 **并不需要维护根节点有哪些**（像并查集一样），因为后面只需要用到 `find_root()` 函数来查找某个值的根节点编号。

- 定义节点类型，注意值的范围（$1\le{value}\le{10^{18}}$）开 long long。
```c++
struct node
{
    int ls, rs;
    llong key, value;
    int size, fa;
};

std::vector<node> tree;
```

- 还需要维护每个值在 $tree$ 中的下标，主要用于 `find_root()` 函数快速查找值的位置并一直跳 $fa$ 找到根节点，FHQ-Treap 是无旋的，一个节点可以一直固定在一个位置，只需要在申请节点的时候记录一下就好了。
```c++
// [value] = (index in tree)
std::map<llong, int> log;
```

- 为一个新值申请一个新的节点，如果已经存在则使用原来的结点。
```c++
int apply_node(llong value)
{
    static std::mt19937 rng;

    int id;

    if (auto it = log.find(value); it != log.end())
    {
        id = it->second;
        tree[id].fa = tree[id].ls = tree[id].rs = 0;
    }
    else
    {
        tree.push_back({});
        id = tree.size() - 1;
        tree[id].key = rng();
        tree[id].value = value;
        log[value] = id;
    }

    tree[id].size = 1;

    return id;
}
```

- 合并左右子树信息，像线段树一样。
> 为什么需要 `tree[u].fa = 0` 呢？因为分裂后会出现新的根节点，被分裂出来的根节点的父节点还是指向它原来的父节点，所以它在调用 `push_up()` 函数更新左右结点的父节点时也需要将自己的父节点重置。
```c++
void push_up(int u)
{
    tree[u].size = tree[tree[u].ls].size + tree[tree[u].rs].size + 1;

    tree[u].fa = 0;

    if (tree[u].ls)
        tree[tree[u].ls].fa = u;

    if (tree[u].rs)
        tree[tree[u].rs].fa = u;
}
```

- 接下来就是一些类似并查集的操作，查找 $value$ 所属的集合的根节点编号。
```c++
// Return index of root of value in the tree
int find_root(llong value)
{
    int u = log[value];

    while (tree[u].fa)
        u = tree[u].fa;

    return u;
}
```

- 判断两个值是否在同一个集合中，一个很重要的操作，合并前一定要判断一下！！！否则会收到各种 **TLE**！
```c++
bool in_same_set(llong lv, llong rv)
{
    return find_root(lv) == find_root(rv);
}
```

- 插入一个值 $value$ 到 $set$ 所属的集合，`split()` 和 `merge()` 函数都是 FHQ-Treap 的两个基本操作。
```c++
// __nd is an index in the tree
void insert(int& rt, int nd)
{
    int x, y;
    split(rt, tree[nd].value, x, y);
    rt = merge(x, merge(nd, y));
}

// Insert a value into the set
void insert_to_set(llong set, llong value)
{
    int rt = find_root(set);
    insert(rt, log[value]);
}
```

- 将 $value$ 所属的集合拆分成三个集合：$\{<value\},\{=value\},\{>value\}$。
```c++
// Split a set into three sets: {<value}, {=value}, {>value}
void split_three_set(llong value)
{
    int rt = find_root(value);

    int x, y, z;
    split(rt, value - 1, x, y);
    split(y, value, y, z);
}
```

- 合并 $fst$ 和 $sst$ 所属的两个集合，两个集合中的值不可以相交，满足第一个集合的最大值小于等于第二个集合的最小值。
```c++
// The maximum value of the __fst set is less than or equal to the minimum value of the __sst set
void merge_two_set(llong fst, llong sst)
{
    merge(find_root(fst), find_root(sst));
}
```

- 获取 $value$ 所属的集合的大小，最后的答案就是输出这个。
```c++
int size(llong value)
{
    return tree[find_root(value)].size;
}
```

到这里这个 ~~**支持可拆分集合的并查集**~~ 就写完啦，合并两个不相交的集合会很快，合并两个相交的集合可能就需要一个个暴力分裂然后再插入。。。

我们还需要一个 _std::set_ 维护一个总集合 $S$，用于快速判断元素是否存在，以及快速查找前驱和后继。

运用并查集的思路后面的操作实现就很简单啦，直接跟着 _分析_ 部分的模拟就好啦。

需要注意的一些问题：

1. 添加一个元素到 $S$ 的时候，如果它的前驱和后继已经在一个集合里，只需要调用一次 `MultiTreap::insert_to_set()` 将值插入进集合，不要多次调用或者调用 `MultiTreap::merge_two_set()`，否则将收到 **RE** 或者 **TLE**。

2. 添加一个元素到 $S$ 的时候，如果它和前驱或者后继合并了其中一个，再合并另一个的时候需要调用 `MultiTreap::merge_two_set()` 并注意传参的顺序。

3. 合并前一定要判断是否已经在同一个集合。

## 完整代码

```c++
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>

using uint    = unsigned int;
using llong   = long long int;
using ullong  = unsigned long long int;
using ldouble = long double;

class MultiTreap
{
public:
    struct node
    {
        int ls, rs;
        llong key, value;
        int size, fa;
    };

private:
    std::vector<node> tree;

    // [value] = (index in tree)
    std::map<llong, int> log;

public:
    MultiTreap() : tree(1) { tree.reserve(2e5 + 1); }

    int apply_node(llong value)
    {
        static std::mt19937 rng;

        int id;

        if (auto it = log.find(value); it != log.end())
        {
            id = it->second;
            tree[id].fa = tree[id].ls = tree[id].rs = 0;
        }
        else
        {
            tree.push_back({});
            id = tree.size() - 1;
            tree[id].key = rng();
            tree[id].value = value;
            log[value] = id;
        }

        tree[id].size = 1;

        return id;
    }

    void push_up(int u)
    {
        tree[u].size = tree[tree[u].ls].size + tree[tree[u].rs].size + 1;

        tree[u].fa = 0;

        if (tree[u].ls)
            tree[tree[u].ls].fa = u;

        if (tree[u].rs)
            tree[tree[u].rs].fa = u;
    }

    void split(int u, llong value, int& rx, int& ry)
    {
        if (u == 0)
        {
            rx = ry = 0;
            return;
        }

        if (tree[u].value > value)
        {
            ry = u;
            split(tree[u].ls, value, rx, tree[u].ls);
        }
        else
        {
            rx = u;
            split(tree[u].rs, value, tree[u].rs, ry);
        }

        push_up(u);
    }

    int merge(int u, int v)
    {
        if (u == 0 or v == 0)
            return push_up(u + v), u + v;

        if (tree[u].key > tree[v].key)
        {
            tree[u].rs = merge(tree[u].rs, v);
            push_up(u);
            return u;
        }
        else
        {
            tree[v].ls = merge(u, tree[v].ls);
            push_up(v);
            return v;
        }
    }

    // Return index of root of value in the tree
    int find_root(llong value)
    {
        int u = log[value];

        while (tree[u].fa)
            u = tree[u].fa;

        return u;
    }

    // __nd is an index in the tree
    void insert(int& rt, int nd)
    {
        int x, y;
        split(rt, tree[nd].value, x, y);
        rt = merge(x, merge(nd, y));
    }

    // Split a set into three sets: {<value}, {=value}, {>value}
    void split_three_set(llong value)
    {
        int rt = find_root(value);

        int x, y, z;
        split(rt, value - 1, x, y);
        split(y, value, y, z);
    }

    // The maximum value of the __fst set is less than or equal to the minimum value of the __sst set
    void merge_two_set(llong fst, llong sst)
    {
        merge(find_root(fst), find_root(sst));
    }

    // Insert a value into the set
    void insert_to_set(llong set, llong value)
    {
        int rt = find_root(set);
        insert(rt, log[value]);
    }

    bool in_same_set(llong lv, llong rv)
    {
        return find_root(lv) == find_root(rv);
    }

    int size(llong value)
    {
        return tree[find_root(value)].size;
    }
};

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    llong q, k;
    std::cin >> q >> k;

    MultiTreap tree;
    std::set<llong> st;

    llong opt, x;

    while (q--)
    {
        std::cin >> opt >> x;

        if (opt == 1)
        {
            auto it = st.find(x);

            if (it != st.end())
            {
                tree.split_three_set(x);

                if (it != st.begin())
                {
                    auto pit = std::prev(it);
                    auto nit = std::next(it);

                    if (nit != st.end() and std::abs(*nit - *pit) <= k)
                    {
                        tree.merge_two_set(*pit, *nit);
                    }
                }

                st.erase(x);
            }
            else
            {
                it = st.insert(x).first;
                tree.apply_node(x);

                bool merged = false;

                if (auto nit = std::next(it); nit != st.end())
                {
                    if (std::abs(*nit - x) <= k)
                    {
                        tree.insert_to_set(*nit, x);
                        merged = true;
                    }
                }

                if (it != st.begin())
                {
                    auto pit = std::prev(it);

                    if (std::abs(*pit - x) <= k and tree.in_same_set(*pit, x) == false)
                    {
                        if (merged)
                            tree.merge_two_set(*pit, x);
                        else
                            tree.insert_to_set(*pit, x);
                    }
                }
            }
        }
        else // if opt == 2
        {
            std::cout << tree.size(x) << '\n';
        }
    }

    return 0;
}
```

[提交记录](https://atcoder.jp/contests/abc356/submissions/54663995) ExecTime: $242$ms。

---

## 作者：ilibilib (赞：2)

## ABC356F

### 分析：

询问一个数 $x$ 时，会向两边不断扩展直至出现长度大于等于 $k$ 不存在数字的段或到边界。

我们可以用 set 插入数字，然后插入数字时候找到它的前继与后继然后就可以维护出所有长度大于等于 $k$ 不存在数字的段的左端点。

用 set 维护左端点，询问时就能找到询问 $x$ 向两边扩展到的阻隔扩展的段的位置，也就是确定了左右端点，然后再进行区间询问。

最后用动态开点线段树实现区间求和就行了。

写得很急所以代码十分丑陋，但还是没能场切。

## code：

```cpp
#include<bits/stdc++.h>
#define int long long
#define ls (t[i].l)
#define rs (t[i].r)
#define IT set<int>::iterator
using namespace std;
const int N=1e18;
set<int>s,c;
struct xds{int l,r,sum;}t[10000000];int cnt=1,gen=1;
void push(int i){t[i].sum=t[ls].sum+t[rs].sum;}
int ask(int q,int w,int l,int r,int &i)
{
	if(!i) return 0;
	if(q<=l&&r<=w) return t[i].sum;
	int mid=(l+r)>>1,ans=0;
	if(q<=mid) ans+=ask(q,w,l,mid,ls);
	if(w>mid) ans+=ask(q,w,mid+1,r,rs);
	return ans;
}
void ins(int q,int k,int l,int r,int &i)
{
	if(!i) i=++cnt;
	if(q<=l&&l==r) {t[i].sum+=k;return;}
	int mid=(l+r)>>1;
	if(q<=mid) ins(q,k,l,mid,ls);
	else ins(q,k,mid+1,r,rs);
	push(i);
};
signed main()
{
    int n,Q,op,x,k;
    s.insert(-1);
    s.insert(N+1);
    c.insert(-1);
    c.insert(N+1);
    cin>>Q>>k;
    while(Q--)
    {
        cin>>op>>x;
        if(op==1)
        {
            IT it=s.find(x);
            if(it==s.end())
            {
                IT p=s.lower_bound(x),q;
                q=p;p--;
                if(*q-*p>k) c.erase(*p);
                if(*q-x>k) c.insert(x);
                if(x-*p>k) c.insert(*p);
                s.insert(x);
                ins(x+1,1,1,N+1,gen);
            }
            else
            {
                IT p=s.lower_bound(x),q;
                q=p;p--;q++;
                if(*q-x>k) c.erase(x);
                if(x-*p>k) c.erase(*p);
                if(*q-*p>k) c.insert(*p);
                s.erase(x);
                ins(x+1,-1,1,N+1,gen);
            }
            c.insert(-1);
            c.insert(N+1);
        }
        else
        {
            IT q=c.lower_bound(x),p=c.lower_bound(x);
            p--;
            if(*p+2>*q+1) {cout<<0<<'\n';continue;}
            cout<<ask(*p+2,*q+1,1,N+1,gen)<<'\n';
        }
    }
}
```

---

## 作者：Link_Cut_Y (赞：2)

怎么会有这么蠢的 ABC F，我胡一下。操作离线下来，预处理一下每个数出现的时间段。做线段树分治，同时维护并查集大小。从集合中加入和删除 $x$ 可以搞一个 `set`。这样是一个 $\log$。复杂度是线段树分治的两个 $\log$。

---

## 作者：wangshulin (赞：1)

# 前言
真的没人写纯 set 做法？
# 思路
发现每个连通块实际上就是排序后的数组的一段连续区间，所以考虑用一个 set 维护排序后的数组，一个 set 维护区间：
- 插入就考虑那些区间会合并。
- 删除就考虑所在区间是否会分裂。
- 查询麻烦一些，由于我们只知道一个区间的左右端点分别是哪两个数，不知道这两个数中间到底有多少个数，所以我们要额外对数进行离散化，装进一个树状数组中统计。

想完剩下就是大模拟。

时间复杂度 $O(n \log n)$。
# 代码

```cpp
#include<stdio.h>
#include<algorithm>
#include<map>
#include<set>
#define ll long long
const ll N=200010;
struct node{
	ll l,r;
	bool operator<(const node &o)const{
		return l<o.l;
	}
};
ll Q,k,cnt,opt[N],a[N],b[N],sum[N];
std::map<ll,ll> Hash;//用 map 进行哈希 
std::set<ll> s;//维护原数组 
std::set<node> t;//维护联通区间
//---------------树状数组
ll lowbit(ll x){
	return x&-x;
}
void add(ll pos,ll x){
	for(ll i=pos;i<=cnt;i+=lowbit(i)) sum[i]+=x;
}
ll ask(ll pos){
	ll t=0;
	for(ll i=pos;i;i-=lowbit(i)) t+=sum[i];
	return t;
}
//---------------树状数组
node findpos(ll x){//询问 x 所在的区间 
	auto T=t.upper_bound((node){x,x});
	if(T==t.begin()) return (node){-1,-1};//没找到 
	else{
		T--;
		if((*T).l<=x&&x<=(*T).r) return (*T);
		else return (node){-1,-1};//没找到 
	}
}
void Insert(ll x){
	if(s.empty()){ 
		t.insert((node){x,x});
	}else{
		node p=findpos(x);
		if(p.l==-1){//findpos(x) 没找到此包含 x 的区间会返回 {-1,-1} 
			if(s.upper_bound(x)==s.begin()){//没有比它小的 
				ll nxt=*s.upper_bound(x);//找到最小那个数 
				if(nxt-x<=k){
					node q=findpos(nxt);
					t.erase(q);
					t.insert((node){x,q.r});
				}else t.insert((node){x,x});//否则将 x 独立成区间
			}else if(s.upper_bound(x)==s.end()){//没有比它大的 
				ll lst=*(--s.lower_bound(x));//找到最大那个数 
				if(x-lst<=k){
					node q=findpos(lst);
					t.erase(q);
					t.insert((node){q.l,x});
				}else t.insert((node){x,x});
			}else{//中间
				ll lst=*(--s.lower_bound(x));//找到比 x 小的最后一个 
				ll nxt=*s.upper_bound(x);//找到比 x 大的第一个 
				node u=findpos(lst),o=findpos(nxt);
				if(nxt-x<=k&&x-lst<=k){//三个并起来 
					t.erase(u);
					t.erase(o);
					t.insert((node){u.l,o.r});
				}else if(nxt-x<=k){//并右边 
					t.erase(o);
					t.insert((node){x,o.r});
				}else if(x-lst<=k){//并左边 
					t.erase(u);
					t.insert((node){u.l,x});
				}else t.insert((node){x,x});//没得并 
			}
		}
	}
	s.insert(x);
	add(Hash[x],1);
}
void Delete(ll x){
	node p=findpos(x);
	if(x==p.l&&x==p.r) t.erase(p);//x 即是整个区间 
	else if(x==p.l){//x 是左端点 
		ll nxt=*s.upper_bound(x);
		t.erase(p);
		t.insert((node){nxt,p.r});
	}else if(x==p.r){//x 是右端点 
		ll lst=*(--s.lower_bound(x));
		t.erase(p);
		t.insert((node){p.l,lst});
	}else{//中间的 
		ll lst=*(--s.lower_bound(x));//找到比 x 小的最后一个 
		ll nxt=*s.upper_bound(x);//找到比 x 大的第一个 
		if(nxt-lst>k){//断开了 
			t.erase(p);
			t.insert((node){p.l,lst});
			t.insert((node){nxt,p.r});
		}
	}
	s.erase(x);
	add(Hash[x],-1);
}
ll Query(ll x){
	node p=findpos(x);
	return ask(Hash[p.r])-ask(Hash[p.l]-1); 
}
int main(){
	scanf("%lld%lld",&Q,&k);
	for(ll i=1;i<=Q;i++){
		scanf("%lld%lld",&opt[i],&a[i]);
		b[i]=a[i];
	}
	std::sort(b+1,b+Q+1);
	for(ll i=1;i<=Q;i++){
		if(!Hash[b[i]]) Hash[b[i]]=++cnt;//哈希 
	}
	for(ll i=1;i<=Q;i++){
		if(opt[i]==1){//时刻注意数组中没有重复的值
			if(s.find(a[i])==s.end()) Insert(a[i]);
			else Delete(a[i]);
		}else{
			printf("%lld\n",Query(a[i]));
		}
	}
	return 0;
}
```

---

## 作者：Sorato_ (赞：1)

# ABC356F Distance Component Size Query

## 题目大意

有 $q$ 次操作和一个无向图 $G$，以及一个常数 $k$。操作有两种：

- 给定 $x$，若 $x\in G$ 则从 $G$ 中删去 $x$，否则将 $x$ 插入 $G$，并将 $x$ 与所有 $y\in[x-k,x+k]\cap G$  连边。
- 给定 $x$，求 $G$ 中 $x$ 所在连通块的大小。

## Solve

若用一个有序集合 $S$ 维护 $G$ 中的点，并对其作差分，令差分后的集合为 $C$，每次操作 2 相当于查询 $C$ 中 $x$ 左侧第一个 $>k$ 的数的位置 $L$,以及 $x$ 右侧第一个 $>k$ 的数的位置 $R$，答案即为 $R-L$（$R$ 不计入区间，$L$ 计入）。

如何维护 $S$。

考虑把操作离线，离散化所有 $x$。然后以离散化后的 $x$ 为下标建立线段树，值为 $C$ 中 $x$ 对应的差值。即：若 $S$ 中 $x$ 位于 $p$，则线段树上以 $x$ 为下标的值为 $C_p$。

对于线段树上的每个节点 $[l,r]$，我们再记录 $mx$ 为 $[l,r]$ 上的最大值，$sum$ 为 $[l,r]$ 上有多少下标已被插入 $S$。

修改：

- 对于插入操作：先将 $x$ 插入 $S$，再查询 $S$ 中 $x$ 的位置 $p$，单点修改 $x$ 为 $S_p-S_{p-1}$，$S_{p+1}$ 为 ${S_{p+1}-x}$。
- 对于删除操作：查询 $S$ 中 $x$ 的位置 $p$，单点修改 $S_{p+1}$ 为 $S_{p+1}-S_{p-1}$。

查询：

考虑线段树二分，在查询 $[S_L,x]$ 的 $sum$ 时遍历到了节点 $[l,r]$：

1. 当 $r\leq L$ 时
   - 若 $mx\leq k$ 则直接结算，返回 $sum$。
   - 否则 若 $l=r$，说明此节点是 $S_L$，返回 $1$。
   - 否则 若右子树的 $mx>k$，则遍历右子树并返回查询结果，否则遍历左子树并返回 查询结果 + 右子树的 $sum$。
2. 否则 当 右子树与 $[S_L,x]$ 无交时，遍历左子树并返回查询结果。
3. 否则 先遍历右子树，然后查询右子树与 $[S_L,x]$ 的交区间的 $mx'$，若 $mx'\leq k$，则继续遍历左子树，否则直接返回。

查询 $(x,S_R)$ 时类似，但注意当 $l=r$ 时应返回 $0$。

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
int q,k,a[200010],x[200010],len;
bool op[200010],vis[200010];
set<int>s;
set<int>::iterator pre,nxt;
struct zzn
{
	int l,r,mx,sum;
	#define ls (p<<1)
	#define rs (p<<1|1)
	#define mid (t[p].l+t[p].r>>1)
}t[800010];
inline void upd(int p)
{
	t[p].mx=max(t[ls].mx,t[rs].mx);
	t[p].sum=t[ls].sum+t[rs].sum;
}
void build(int p,int l,int r)
{
	t[p].l=l;t[p].r=r;
	if(l==r)	return;
	build(ls,l,mid);build(rs,-~mid,r);
}
void change(int p,int x,int d)
{
	if(t[p].l==t[p].r)
	{
		t[p].mx=d;t[p].sum=1;
		return;
	}
	if(mid>=x)	change(ls,x,d);
	else	change(rs,x,d);
	upd(p);
}
void del(int p,int x)
{
	if(t[p].l==t[p].r)
	{
		t[p].mx=t[p].sum=0;
		return;
	}
	if(mid>=x)	del(ls,x);
	else	del(rs,x);
	upd(p);
}
int query(int p,int l,int r)
{
	if(t[p].l>=l&&t[p].r<=r)	return t[p].mx;
	int res=0;
	if(mid>=l)	res=max(res,query(ls,l,r));
	if(mid<r)	res=max(res,query(rs,l,r));
	return res;
}
int query1(int p,int r)
{
	if(t[p].r<=r)
	{
		if(t[p].mx<=k)	return t[p].sum;
		if(t[p].l==t[p].r)	return 1;
		return t[rs].mx<=k?t[rs].sum+query1(ls,r):query1(rs,r);
	}
	int res=0;
	if(mid<r)
	{
		res+=query1(rs,r);
		if(query(rs,t[rs].l,r)<=k)	res+=query1(ls,r);
	}
	else	res+=query1(ls,r);
	return res;
}
int query2(int p,int l)
{
	if(t[p].l>=l)
	{
		if(t[p].mx<=k)	return t[p].sum;
		if(t[p].l==t[p].r)	return 0;
		return t[ls].mx<=k?t[ls].sum+query2(rs,l):query2(ls,l);
	}
	int res=0;
	if(mid>=l)
	{
		res+=query2(ls,l);
		if(query(ls,l,t[ls].r)<=k)	res+=query2(rs,l);
	}
	else	res+=query2(rs,l);
	return res;
}
signed main()
{
	q=read();k=read();
	for(int i=1;i<=q;i=-~i)	op[i]=read()-1,a[i]=x[i]=read();
	sort(a+1,a+q+1);
	len=unique(a+1,a+q+1)-a-1;
	build(1,1,len);
	for(int i=1;i<=q;i=-~i)
	{
		x[i]=lower_bound(a+1,a+len+1,x[i])-a;
		if(op[i])	printf("%d\n",query1(1,x[i])+(x[i]==len?0:query2(1,x[i]+1)));
		else
		{
			s.insert(x[i]);
			auto p=s.find(x[i]);
			if(p!=s.begin())	{pre=--p;++p;}
			nxt=++p;--p;
			if(vis[x[i]])
			{
				del(1,x[i]);vis[x[i]]=0;
				if(nxt!=s.end())
					change(1,*nxt,p!=s.begin()?a[*nxt]-a[*pre]:0);//若x是第一个元素则单点修改为0，保证其<=k
				s.erase(p);
			}
			else
			{
				vis[x[i]]=1;
				change(1,x[i],p!=s.begin()?a[x[i]]-a[*pre]:0);
				if(nxt!=s.end())
					change(1,*nxt,a[*nxt]-a[x[i]]);
			}
		}
	}
	return 0;
}
```

---

## 作者：jr_zch (赞：1)

# Distance Component Size Query

第一眼看上去就觉得很板的数据结构题。

首先发现只需要求 $x$ 所在连通块的大小，所以对于建图而言，我们只需要把满足要求的相邻两个点进行连边就好了。

有加点和删点，我赛时没有想到开 set 对边去维护，那么要处理点，最好的办法就是把操作离线下来，然后线段树分治了。

把每一个点存在的时间段都加入进线段树里面，然后就是正常线段树分治模板了，用可撤销并查集维护图的连通性，set 查找一个点的前驱后继即可。

时间复杂度 $O(n \log_2 q \log_2 n)$。

## Code：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int maxn=2e5+7;
int q,k,tot,opt,x,top;
int f[maxn],siz[maxn];
struct prob{
	int u,v;
}s[maxn];
map<int,int> id,vis;
vector<int> g[maxn<<2],a[maxn];
set<int> now,del;
set<int>::iterator it;

int find(int x){
	while(f[x]!=x) x=f[x];
	return x; 
}

void merge(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx!=fy){
		if(siz[fx]>siz[fy]) swap(fx,fy);
		f[fx]=fy,siz[fy]+=siz[fx],s[++top]=(prob){fx,fy};
	}
	return ;
}

void update(int rt,int l,int r,int x,int y,int val){
	if(x<=l&&y>=r){
		g[rt].push_back(val);
		return ;
	}
	int mid=l+r>>1;
	if(x<=mid) update(rt<<1,l,mid,x,y,val);
	if(y>mid) update(rt<<1|1,mid+1,r,x,y,val);
	return ;
}

void query(int rt,int l,int r){
	int pre=top;
	for(int i=0;i<g[rt].size();i++){
		int c=g[rt][i];
		it=now.upper_bound(c);
		if(it!=now.end()&&abs(*it-c)<=k) merge(id[*it],id[c]);
		if(it!=now.begin()){
			it--;
			if(abs(*it-c)<=k) merge(id[*it],id[c]);
		}
		now.insert(c);
	}
	if(l==r){
		for(int i=0;i<a[l].size();i++){
			int c=a[l][i];
			printf("%lld\n",siz[find(id[c])]);
		}
		for(int i=0;i<g[rt].size();i++) now.erase(g[rt][i]);
		while(top>pre){
			int u=s[top].u,v=s[top].v;
			top--,f[u]=u,siz[v]-=siz[u];
		}
		return ;
	}
	int mid=l+r>>1;
	query(rt<<1,l,mid),query(rt<<1|1,mid+1,r);
	for(int i=0;i<g[rt].size();i++) now.erase(g[rt][i]);
	while(top>pre){
		int u=s[top].u,v=s[top].v;
		top--,f[u]=u,siz[v]-=siz[u];
	}
	return ;
}

signed main(){
	scanf("%lld%lld",&q,&k);
	for(int i=1;i<=q;i++){
		scanf("%lld%lld",&opt,&x);
		if(opt==1){
			if(!id[x]) id[x]=++tot;
			if(vis[x]) update(1,1,q,vis[x],i,x),vis[x]=0,del.erase(x);
			else vis[x]=i,del.insert(x);
		}else a[i].push_back(x);
	}
	for(it=del.begin();it!=del.end();it++) update(1,1,q,vis[*it],q,*it);
	for(int i=1;i<=tot;i++) f[i]=i,siz[i]=1;
	query(1,1,q);
	return 0;
}
```

---

## 作者：hhhqx (赞：0)

# 题解：AT_abc356_f [ABC356F] Distance Component Size Query

## 前言

~~纪念我场上 WA 8 发没调出来，最后发现是~~ `1e18` ~~的问题~~。

题目传送门：[[ABC356F] Distance Component Size Query](https://www.luogu.com.cn/problem/AT_abc356_f)。

不会线段树分治怎么办？？？那就用 set + 01-trie。

## 思路

一个联通块内的元素在值域上也是连续的，考虑维护一个联通快内的**最大值**，即值域上的右端点。

考虑用 set 维护，每次插入或删除的时候分类讨论一下就可以了。

插入 $x$：

- 对于小于 $x$ 的第一个数，如果它原本是某个块内的最大值，且与 $x$ 的差小于等于 $k$，则更新。

- 对于大于 $x$ 的第一个数，如果它与 $x$ 的差小于等于 $k$，则更新。

删除 $x$：

- 对于小于 $x$ 的第一个数，如果它与 $x$ 的差小于等于 $k$，且与大于 $x$ 的第一个数差大于 $k$，则更新。

- 如果 $x$ 是某个块内的最大值，则更新。

然后我们就可以应对每一次询问，得到所在块的左右端点。至于求区间和，可以利用 01-trie。

当然也可以用树状数组，但是 01-trie 无视值域范围，不用离散化……

提一嘴我的迷惑行为：我使用了类似 `(check() ? 1e18 : LL(x))` 的语句，后来同学告诉我 `1e18` 是 `double` 类型，然后三目运算符会强转相同类型，于是 `LL(x)` 变为了 `double` 类型，因为精度误差挂了。

如果你需要一个大值域的数据，这里有一个：

```
input:
10 10000000000000000
1 500000000769529139
1 500000000769529139
1 500000001877765912
1 500000000464945334
1 500000001502178942
2 500000001877765912
1 500000000464945334
2 500000001877765912
2 500000001502178942
2 500000001877765912
ans:
3
2
2
2
```

## Code

```cpp
#include <bits/stdc++.h>

using namespace std;
using LL = long long;

const int MAXN = 2e5 + 3;

int Q;
LL k;
set<LL> st, ans;
int tot = 1, eg[MAXN * 61][2], cnt[MAXN * 61];

void _Insert(LL x){
  int p = 1;
  for(LL i = 61; i >= 0; i--){
    int col = (x >> i) & 1;
    if(!eg[p][col]) eg[p][col] = ++tot;
    p = eg[p][col], cnt[p]++;
  }
}
void _Erase(LL x){
  int p = 1;
  for(LL i = 61; i >= 0; i--){
    int col = (x >> i) & 1;
    p = eg[p][col], cnt[p]--;
  }
  cnt[0] = 0;
}
LL _Query(LL x){
  LL ret = 0;
  int p = 1;
  x++;
  for(LL i = 61; i >= 0; i--){
    int col = (x >> i) & 1;
    if(col == 1) ret += cnt[eg[p][0]];
    p = eg[p][col];
  }
  return ret;
}

void Insert(LL x){
  auto it = st.lower_bound(x);
  if(it != st.begin() && ans.find(*prev(it)) != ans.end() && x - *prev(it) <= k){
    ans.erase(*prev(it));
  }

  it = st.lower_bound(x);
  if(it == st.end() || *it - x > k){
    ans.insert(x);
  }
  st.insert(x), _Insert(x);
}

void Erase(LL x){
  st.erase(x), _Erase(x);
  if(ans.find(x) != ans.end()) ans.erase(x);
  if(st.empty()) return;
   
  auto it = st.lower_bound(x);
  if(it != st.begin() && (it == st.end() || *it - *prev(it) > k)){
    ans.insert(*prev(it));
  }

}

LL Query(LL x){
  auto it = ans.lower_bound(x);
  LL r = (it == ans.end() ? LL(1e18) : *it);
  LL l = (it == ans.begin() ? 0 : *prev(it));
  return _Query(r) - _Query(l);
}

int main(){
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> Q >> k;
  while(Q--){
    LL op, x; cin >> op >> x;
    if(op == 1){
      if(st.find(x) == st.end()){
        Insert(x);
      }else{
        Erase(x);
      }
    }else{
      if(st.find(x) == st.end()){
        return 1;
      }
      /*
      cout << ans.size() << "\n";
      for(LL y : ans) cout << y << "\n";
      */
      cout << Query(x) << "\n";
    }
  }
  return 0;
}
/*
10 10000000000000000
1 500000000769529139
1 500000000769529139
1 500000001877765912
1 500000000464945334
1 500000001502178942
2 500000001877765912
1 500000000464945334
2 500000001877765912
2 500000001502178942
2 500000001877765912

3
2
2
2

*/
```

---

## 作者：Hope888 (赞：0)

明显可以分别二分往 $x$ 两边跳的答案。二分的 `Check` 可以通过区间询问差距的最大值是否超过 $k$ 来判断。


而对于区间的询问，使用线段树，先离线从小到大分配线段树每个叶子对应哪个数，修改结点时把线段树叶子上的布尔标记取反，难点就只剩 `pushup` 了。

```cpp
	node pushup(node x,node y)
	{
		node ans={x.tot+y.tot,0,0,0};
		if(x.tot==0||y.tot==0)//如果有一边没有节点，则直接用另一边
		{
			if(x.tot==0)ans.res=y.res;
			else if(y.tot==0)ans.res=x.res;
		}
		else ans.res=max(max(x.res,y.res),abs(x.rnum-y.lnum));//用两段答案和中间更新最大值
		if(x.tot==0)ans.lnum=y.lnum;
		else ans.lnum=x.lnum;
		if(y.tot==0)ans.rnum=x.rnum;
		else ans.rnum=y.rnum;
		return ans;
	}
```

# Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int q,k;
struct node
{
	int tot,res,lnum,rnum;
};
unordered_map<long long,int>id;
struct que
{
	int op,x,idx;
}t[N];
bool cmp1(que x,que y)
{
	return x.x<y.x;
}
bool cmp2(que x,que y)
{
	return x.idx<y.idx;
}
struct tree
{
	#define lson l,mid,num<<1
	#define rson mid+1,r,num<<1|1
	#define get_mid int mid=(l+r)>>1
	node a[N<<2];
	node pushup(node x,node y)
	{
		node ans={x.tot+y.tot,0,0,0};
		if(x.tot==0||y.tot==0)
		{
			if(x.tot==0)ans.res=y.res;
			else if(y.tot==0)ans.res=x.res;
		}
		else ans.res=max(max(x.res,y.res),abs(x.rnum-y.lnum));
		if(x.tot==0)ans.lnum=y.lnum;
		else ans.lnum=x.lnum;
		if(y.tot==0)ans.rnum=x.rnum;
		else ans.rnum=y.rnum;
		return ans;
	}
	void build(int l,int r,int num)
	{
		if(l==r)
		{
			a[num]={0,0,0,0};
			return;
		}
		get_mid;
		build(lson),build(rson);
		a[num]=pushup(a[num<<1],a[num<<1|1]);
	}
	void update(int pos,int x,int l,int r,int num)
	{
		if(l==r&&l==pos)
		{
			a[num]={!a[num].tot,0,x,x};
			return;
		}
		get_mid;
		if(pos<=mid)update(pos,x,lson);
		if(pos>mid)update(pos,x,rson);
		a[num]=pushup(a[num<<1],a[num<<1|1]);
	}
	node query(int L,int R,int l,int r,int num)
	{
		if(L<=l&&r<=R)return a[num];
		get_mid;
		if(L<=mid&&R>mid)return pushup(query(L,R,lson),query(L,R,rson));
		if(L<=mid)return query(L,R,lson);
		if(R>mid)return query(L,R,rson);
	}
}tr;
signed main()
{
	cin>>q>>k;
	int tot=0;
	for(int i=1;i<=q;i++)
	{
		cin>>t[i].op>>t[i].x;
		t[i].idx=i;
	}
	sort(t+1,t+1+q,cmp1);
	for(int i=1;i<=q;i++)
	{
		if(t[i].op==2)continue;
		if(!id.count(t[i].x))id[t[i].x]=++tot;
	}
	sort(t+1,t+1+q,cmp2);
	tr.build(1,tot,1);
	for(int i=1;i<=q;i++)
	{
		if(t[i].op==1)tr.update(id[t[i].x],t[i].x,1,tot,1);
		else
		{
			int ans1=0,ans2=0,l=id[t[i].x],r=tot;
			while(l<=r)
			{
				int mid=l+r>>1;
				node tt=tr.query(id[t[i].x],mid,1,tot,1);
				if(tt.res<=k)
				{
					ans1=tt.tot;
					l=mid+1;
				}
				else r=mid-1;
			}
			l=1,r=id[t[i].x];
			while(l<=r)
			{
				int mid=l+r>>1;
				node tt=tr.query(mid,id[t[i].x],1,tot,1);
				if(tt.res<=k)
				{
					ans2=tt.tot;
					r=mid-1;
				}
				else l=mid+1;
			}
			cout<<ans1+ans2-1<<endl;
		}
	}
}
```

---

## 作者：2020kanade (赞：0)

来个相对邪门的写法。

题中所有数轴上距离不超过 $k$ 的点之间连边，显然这东西在整个数轴上构成若干极大连续段也就是颜色段。

分析操作：加点时要么在一个颜色段外要么在某个颜色段上，后者容易处理（直接将该颜色段包含的点数加一即可），前者需要判断是否可以合并相邻的两个颜色段。

删点时，考虑其所在的颜色段，若其两个邻点仍满足距离不超过 $k$，直接将颜色段内点数减一即可；否则，需要进行颜色段分裂操作。

以上所有操作都涉及最多三个颜色段的修改，但是分裂时裸的颜色段均摊维护难以在可接受的时间复杂度内对分裂后每个颜色段内点数进行计算，需要联动权值树状数组/线段树或平衡树区间求和计算。

区间查询时直接定位询问点所在颜色段，返回其包含点数即可。

时间复杂度 $\Theta(n\log n)$，笔者使用一个 ```std::set``` 维护颜色段，一个 FHQ-Treap 处理求和，一个 ```std::set``` 直接维护数轴上点集，纯属个人习惯，可能有更简易的实现。

```cpp
//written by Amekawa_kanade
#include<bits/stdc++.h>
using namespace std;
void syncoff()//fuck you sync
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
}
#define endl '\n'
const int N=5e5+11;
using ll=long long;
using i128=__int128;
using ld=long double;
const ll JT=998244353;
const ll GEH=1e9+7;
const ll ZLH=1e9+9;
int t,n,m,q;ll k;
struct node
{
	ll l,r,sz;
	node(ll l,ll r):l(l),r(r),sz(1) {}
	node(ll l,ll r,ll sz):l(l),r(r),sz(sz) {}
	node(ll pos):l(pos),r(pos),sz(1) {}
	bool operator <(const node& a)const
	{
		return r<a.r;
	}
};
struct nd
{
	int ch[2],sz;ll r,val;
}cts[N];int cnt;mt19937 gen(time(0));
int nnd(ll val)
{
	++cnt;
	cts[cnt]={0,0,1,gen(),val};
	return cnt;
}
void up(int x)
{
	cts[x].sz=1;
	if(cts[x].ch[0]) cts[x].sz+=cts[cts[x].ch[0]].sz;
	if(cts[x].ch[1]) cts[x].sz+=cts[cts[x].ch[1]].sz;
}
int merge(int x,int y)
{
	if(!x||!y) return x?x:y;
	if(cts[x].r<cts[y].r)
	{
		cts[x].ch[1]=merge(cts[x].ch[1],y);up(x);return x;
	}
	else
	{
		cts[y].ch[0]=merge(x,cts[y].ch[0]);up(y);return y;
	}
}
using ip=pair<int,int>;
ip split(int x,ll k)
{
	if(!x) return {0,0};
	if(cts[x].val<=k)
	{
		ip u=split(cts[x].ch[1],k);
		cts[x].ch[1]=u.first,up(x);u.first=x;return u;
	}
	else
	{
		ip u=split(cts[x].ch[0],k);
		cts[x].ch[0]=u.second,up(x);u.second=x;return u;
	}
}
void treap_ins(int &x,ll val)
{
	auto t=split(x,val-1),p=split(t.second,val);
	if(!p.first) p.first=nnd(val);
	x=merge(t.first,merge(p.first,p.second));
}
void treap_del(int &x,ll val)
{
	auto t=split(x,val-1),p=split(t.second,val);
	if(p.first) p.first=0;
	x=merge(t.first,merge(p.first,p.second));
}
int treap_ask(int &x,ll l,ll r)
{
	auto t=split(x,l-1),p=split(t.second,r);
	int ret=0;if(p.first) ret=cts[p.first].sz;
	x=merge(t.first,merge(p.first,p.second));
	return ret;
}
set<node> s1;int trt;set<ll> s2;
using sit=set<node>::iterator;
sit ask(ll pos)
{
	auto x1=s1.lower_bound(node(pos));
	if(x1==s1.end()) return x1;
	if(!(x1->l<=pos&&pos<=x1->r)) return s1.end();
	return x1;
}
void ins(ll pos)
{
	if(s2.count(pos)) return;
	auto x1=ask(pos);treap_ins(trt,pos);
	if(x1!=s1.end()&&x1->l<=pos&&pos<=x1->r)
	{
		auto xx=*x1;++xx.sz;
		s1.erase(x1);s1.insert(xx);
	}
	else
	{
		auto x2=s2.lower_bound(pos),x3=x2;
		if(x2!=s2.begin()) --x2;
		if(x3!=s2.end())
		{
			if(x2==x3)
			{
				if((*x3)-pos<=k)
				{
					auto nnd=node(pos,ask(*x3)->r,ask(*x3)->sz+1);
					s1.erase(ask(*x3));s1.insert(nnd);
				}
				else s1.insert(node(pos,pos,1));
			}
			else
			{
				auto nnd=node(pos,pos,1);
				if(pos-(*x2)<=k) nnd.l=ask(*x2)->l,nnd.sz+=ask(*x2)->sz,s1.erase(ask(*x2));
				if((*x3)-pos<=k) nnd.r=ask(*x3)->r,nnd.sz+=ask(*x3)->sz,s1.erase(ask(*x3));
				s1.insert(nnd);
			}
		}
		else if(x2!=x3)
		{
			auto nnd=node(pos,pos,1);
			if(pos-(*x2)<=k) nnd.l=ask(*x2)->l,nnd.sz+=ask(*x2)->sz,s1.erase(ask(*x2));
			s1.insert(nnd);
		}
		else s1.insert(node(pos,pos,1));
	}
	s2.insert(pos);
}
void del(ll pos)
{
	if(!s2.count(pos)) return;
	auto x1=ask(pos);ll pl=x1->l,pr=x1->r,psz=x1->sz;
	treap_del(trt,pos);
	s1.erase(x1);
	auto x2=s2.lower_bound(pos),x3=x2;++x3;
	if(x2!=s2.begin()&&x3!=s2.end())
	{
		--x2;
		if((*x3)-(*x2)<=k)
		{
			 s1.insert(node(pl,pr,psz-1));
			 s2.erase(pos);return;
		}
	}
	x2=s2.lower_bound(pos),x3=x2;++x3;
	if(x2!=s2.begin())
	{
		--x2;
		if(pl<=(*x2)) s1.insert(node(pl,*x2,treap_ask(trt,pl,*x2)));
	}
	if(x3!=s2.end())
	{
		if((*x3)<=pr) s1.insert(node(*x3,pr,treap_ask(trt,*x3,pr)));
	}
	s2.erase(pos);
}
void solve()
{
	cin>>n>>k;
	int opt;ll val;
	for(int i=1;i<=n;++i)
	{
		cin>>opt>>val;
		if(opt==1)
		{
			if(s2.count(val)) del(val);
			else ins(val);
		}
		else
		{
			ll ans=ask(val)->sz;
			cout<<ans<<endl;
		}
	}
}
int main()
{
 	t=1;
    //cin>>t;
    while(t--) solve();
    return 0;
}

```

---

## 作者：Starrykiller (赞：0)

注意到每个元素会在**集合**中存活一段时间。套路地考虑**线段树分治**。

具体而言，我们利用线段树维护**时间轴**：
- 将每个元素加入到它存活的区间集合中；
    - 更为具体地说，我们在线段树的每个节点 $[l,r]$ 上维护一个 $\texttt{std::vector}$，代表在 $[l,r]$ 时刻我们要加入的元素。
- 查询时，按照时间顺序遍历线段树。
    - 进入一个节点时，将对应元素加入集合，并维护连通关系；
    - 到达叶子时（注意到查询只会在叶子上），直接查询；
    - 离开一个节点时，将修改全部撤销。

不难证明如此一定能够正确的回答每一个询问。

那么我们需要一个**可以维护连通性，并支持撤销**的数据结构。不难想到可撤销并查集（的带权版本）。

我们利用 $\texttt{std::set}$ 维护集合。插入一个元素时，我们检查它的前驱后继，如果差的绝对值不大于 $K$，我们就在并查集上合并这两个元素。

注意到 $x$ 可能很大，离散化即可。代码还是非常好写的。

时间复杂度 $\Theta(m\log^2 m)$。

[My submission](https://atcoder.jp/contests/abc356/submissions/54123290)。

---

