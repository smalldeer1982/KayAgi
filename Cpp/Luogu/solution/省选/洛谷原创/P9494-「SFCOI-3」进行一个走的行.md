# 「SFCOI-3」进行一个走的行

## 题目背景

**公告：注意存在 $l_i > r_i$ 的情况，此时操作无效。**

------------

小 L 热衷于行走。

## 题目描述

小 L 来到了一处景点，他想要在这里的主干道上行走。

主干道上有若干关键点，他可以将其抽象为一个长为 $n$ 的序列 $a$，每个 $a_i$ 都是一个三元组，可以表示为 $(l_i, r_i, v_i)$，其具体含义形如：

- 若 $r_i = -1$，表示一个需要买票进入的景点，票价为 $l_i$ 代币，游览完成后他会得到 $v_i$ 的愉悦值。
- 若 $r_i \neq -1$，表示一个礼品派发点，若他持有的代币面值之和 $x$ 满足 $l_i \leq x \leq r_i$，他可以领取一份礼品，并会得到 $v_i$ 的愉悦值。

他打算在这条主干道上行走 $m$ 次，每次他给出了行走起点 $l$ 和终点 $r$，一开始他持有的代币面值之和为 $x$，初始愉悦值为 $0$。

他将从 $l$ 开始向右依次经过 $i \in [l, r]$，他会做如下操作：

- 若 $r_i = -1$，如果他持有的代币在支付完当前景点门票费用后还有剩余，他会游览这个景点。
- 若 $r_i \neq -1$，如果可以，他会领取一份礼品。

请你帮他快速求出每次行走结束后他的愉悦值。

## 说明/提示

**本题开启捆绑测试。**

- Subtask 1（10 pts）：$1 \leq n, m \leq 5 \times 10^3$。
- Subtask 2（10 pts）：$r_i \neq -1$。
- Subtask 3（20 pts）：$r_i = -1$。
- Subtask 4（10 pts）：$1 \leq n, m \leq 7.5 \times 10^4$，性质 A。
- Subtask 5（20 pts）：$1 \leq n, m \leq 7.5 \times 10^4$。
- Subtask 6（10 pts）：数据在范围内随机生成，性质 B。
- Subtask 7（20 pts）：无特殊限制。

性质 A：$1 \leq l_i \leq 7.5 \times 10^4$，$r_i = -1$ 或 $1 \leq r_i \leq 7.5 \times 10^4$，$1 \leq x \leq 7.5 \times 10^4$。

性质 B：$r_i = -1$ 时 $1 \leq l_i \leq 2 \times 10^5$。

对于 $100\%$ 的数据：

- $1 \leq n, m \leq 2 \times 10^5$。
- $1 \leq l_i \leq 10^9$，$r_i = -1$ 或 $1 \leq r_i \leq 10^9$。
- $1 \leq v_i \leq 10^9$。
- $1 \leq l \leq r \leq n$，$1 \leq x \leq 10^9$。

## 样例 #1

### 输入

```
4 10
1 1 4
5 -1 4
1 9 19
8 -1 10
1 1 11
2 2 4
3 3 5
4 4 14
1 2 1
2 3 9
3 4 1
1 3 9
2 4 8
1 4 10```

### 输出

```
0
0
19
10
4
23
19
23
23
23```

# 题解

## 作者：STARSczy (赞：15)

突进 3 秒，最优解，题解以纪念。

先定一个大的框架。容易想到离线后差分，然后再用平衡树扫一遍，对于每次行走，在 $l_i$ 位置加入，在 $r_i+1$ 位置删去，最后再输出答案。

当平衡树扫到位置 $i$：
- 若 $r_i\not=-1$，把平衡树分裂成三段，中间那一段是 $[l_i,r_i]$，中间一段打上懒标记即可。

- 若 $r_i=-1$，把平衡树分裂成 $[0,l_i]$ 和 $(l_i,inf)$ 两段，把 $(l_i,inf)$ 一段减去 $l_i$，此时使用交织区间平衡树合并，单次是可以均摊到 $\log n \log V$ 的（[参考1](https://codeforces.com/blog/entry/108601)，[参考2](https://www.luogu.com.cn/article/p4ejw9j6)）。

故总时间复杂度为 $n \log n \log V$。但实际表现很像 $n \log n$。

听别人说码风有点差，代码就放云剪贴板了，也算一种防抄袭吧。[链接](https://www.luogu.com.cn/paste/rjz8bl4k)。目前最优解，应该是最短的代码（有压行，但保证每行长度不超过 100 字节）。

---

## 作者：EnofTaiPeople (赞：11)

首先发现本题每次在每次行走时都形如一个分段函数，但这个分段函数还有一个权值维，就不知道怎么维护了。

所以可以尝试将已知权值放在一起维护，像扫描线一样，将所有询问在 $l$ 处插入，在 $r$ 处删除（并以当前权值获得答案），每次只需要相应修改值域区间即可。

形如 $>l$ 的数 $-l$ 的操作适用[倍增分块](https://www.luogu.com.cn/blog/502410/multi-seg-block-p7447)，即将 $[2^k,2^{k+1})$ 视为一块，每次将大块直接打标记，将会掉块的取出；等块将合法值取出暴力减，并且这些必定变块。

显然每个数最多变块 $O(\log V)$ 次，可以接受。

考虑动态维护有序值域区间，这个用平衡树维护就可以了，因为 Splay 是相对灵活的，所以我使用了 Splay，总时间复杂度 $O((n+m)\log n\log V)$，空间 $O(n+m)$：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,M=1e9+7;
using ll=long long;
int n,m,sta[N];
struct dat{int l,r,v;}d[N];
vector<int>ad[N],dl[N];
int L[N],R[N],kt;
int t[N][2],f[N],rt[42];
#define ls t[x][0]
#define rs t[x][1]
#define tp(x) (t[f[x]][1]==x)
#define in(x) (t[f[x]][0]==x||tp(x))
int stk[N],tp;
ll t1[N],t2[N],w[N],v[N];
void ad1(int x,ll d){t1[x]+=d,v[x]-=d;}
void ad2(int x,ll d){t2[x]+=d,w[x]+=d;}
int Ik(int d){
	// cerr<<d<<endl;
	for(int i=kt;i;--i)
		if(d>=L[i])return i;
	assert(0);
	return -1e9;
}
void pd(int x){
	if(t1[x]){
		if(ls)ad1(ls,t1[x]);
		if(rs)ad1(rs,t1[x]);
	}if(t2[x]){
		if(ls)ad2(ls,t2[x]);
		if(rs)ad2(rs,t2[x]);
	}t1[x]=t2[x]=0;
}
void ppd(int x){
	if(in(x))ppd(f[x]);pd(x);
}
void rot(int x){
	int y=f[x],k=tp(x),w=t[x][!k];
	t[f[w]=t[x][!k]=y][k]=w;
	if(in(y))t[f[y]][tp(y)]=x;
	f[x]=f[y],f[y]=x;
}
void splay(int x){ppd(x);
	for(int y=f[x];in(x);rot(x),y=f[x])
		if(in(y))rot(tp(x)^tp(y)?x:y);
}
void ins(int &x,int p){
	if(!x){x=p;return;}
	int k=v[p]>=v[x];pd(x);
	ins(t[x][k],p),f[t[x][k]]=x;
}
void spt(int x,int &L,int &R,int k){//<=k to L
	L=R=0;if(!x)return;
	int mst=0;
	while(1){pd(x);
		if(v[x]<=k){
			mst=x;
			if(rs)x=rs;
			else break;
		}else if(ls)x=ls;
		else break;
	}splay(x);
	if(mst){
		x=mst,splay(x);
		L=x,f[R=rs]=0,rs=0;
	}else L=0,R=x;
}
void Add(int x){int k=Ik(v[x]);ins(rt[k],x),splay(x),rt[k]=x;}
void dfs(int x){
	pd(x);
	if(ls)dfs(ls);
	if(rs)dfs(rs);
	f[x]=ls=rs=0;
	stk[++tp]=x;
}
void PPD(int x){
	if(x){
		pd(x);
		if(ls)PPD(ls);
		if(rs)PPD(rs);
	}
}
void add1(int lm,int vl){
	int l,r,k;tp=0;
	for(k=1;k<=kt;++k)
		if(R[k]>lm&&rt[k])
			if(L[k]<=lm){
				spt(rt[k],rt[k],r,lm);
				ad1(r,lm),ad2(r,vl);
				if(r)dfs(r);
			}else{
				ad1(rt[k],lm),ad2(rt[k],vl);
				spt(rt[k],l,rt[k],L[k]-1);
				if(l)dfs(l);
			}
	while(stk[tp])Add(stk[tp--]);
}
int mg(int x,int y){
	if(!x||!y)return x|y;
	while(rs)x=rs;
	splay(x),f[rs=y]=x;return x;
}
void add2(int lm,int vl){
	int l,r,k;
	for(k=1;k<=kt;++k)
		if(L[k]<lm&&rt[k])
			if(R[k]>=lm){
				spt(rt[k],l,r,lm-1);
	// printf("l:%d r:%d\n",l,r);
	// for(int x=1;x<=m;++x)
	// 	if(sta[x])printf("x:%d v:%d w:%lld ls:%d rs:%d f:%d\n",x,v[x],w[x],ls,rs,f[x]);
				if(l)ad2(l,vl);
				rt[k]=mg(l,r);
			}else ad2(rt[k],vl);
}
int main(){
	ios::sync_with_stdio(false);
	int i,j,k,l,r,x,y,lm,vl;
	cin>>n>>m;
	for(i=1;i<=n;++i)
		cin>>d[i].l>>d[i].r>>d[i].v;
	for(i=1;i<=m;++i){
		cin>>l>>r>>v[i];
		ad[l].push_back(i);
		dl[r].push_back(i);
	}
	for(l=kt=0;l<=M;l=r+1){
		r=min(3ll*(l+1),1ll*M),++kt;
		L[kt]=l,R[kt]=r;
	}
	for(i=1;i<=n;++i){
		for(int x:ad[i])Add(x),sta[x]=1;
		if(d[i].r==-1)add1(d[i].l,d[i].v);
		else add2(d[i].l,-d[i].v),add2(d[i].r+1,d[i].v);
		for(int x:dl[i]){
			splay(x);
			f[ls]=f[rs]=0;
			k=Ik(v[x]);
			rt[k]=mg(ls,rs);
		}
		// PPD(rt[1]),PPD(rt[2]);
		// exit(0);
	}
	for(i=1;i<=m;++i)
		printf("%lld\n",w[i]);
	return 0;
}
```

---

## 作者：Leasier (赞：9)

### Subtask 1
暴力模拟题意即可。时间复杂度为 $O(nm)$。
### Subtask 2
考虑差分，将询问 $Q(l, r, x)$ 转化为 $Q(1, r, x + sum_{l - 1}) - Q(1, l - 1, x + sum_{l - 1})$，其中 $sum_i = \displaystyle\sum_{j = 1}^i [r_j = -1] l_j$。

把所有前缀询问的 $x$ 抓出来离散化，BIT 维护区间加、单点求值即可。时间复杂度为 $O((n + m) \log m)$。
### Subtask 3
依然差分，现在我们只需要考虑处理前缀问题。

考虑一个比较暴力的做法：

- 维护一棵 Treap，每个节点上记录到达 $1$ 前代币数量为 $x$ 时现在代币数量为 $y$，当前愉悦值为 $z$。
- 每遇到一个 $(l_i, v_i)$，首先把整个 Treap 拿来 split 成 $[1, l_i], (l_i, 2l_i], (2l_i, +\infty)$ 三段。
- 给第三段打上其 $y$ 减去 $l_i$ 的标记，给第二、三段打上其 $z$ 加上 $v_i$ 的标记。
- 暴力取出第二段中的数，给其 $y$ 减去 $l_i$ 后插入第一段。
- 合并第一、三段。

下面我们来证明它的时间复杂度是正确的：

- 在某一次操作 $l_i$ 中，只有 $x \in (l_i, 2l_i]$ 者可能对时间复杂度产生比一般平衡树操作多的贡献。
- 而 $x - l_i \leq \frac{x}{2}$，则每产生一次这样的贡献后 $x$ 大小至少减半。
- 设 $w = 10^9$，则任意 $x$ 至多产生 $O(\log w)$ 次贡献。

时间复杂度为 $O(n \log m + m \log m \log w)$。
### Subtask 4
~~可能有依赖值域的做法，但是我不太清楚。~~
### Subtask 5
如果没想到差分，可以考虑分块维护 Subtask 7 的做法。离线下来逐块处理即可。

设块长为 $S$，则时间复杂度为 $O(mS + n \log m + \frac{nm \log m \log w}{S})$，取 $S = \sqrt{n \log m \log w}$ 取最优时间复杂度为 $O(m \sqrt{n \log m \log w} + n \log m)$。
### Subtask 6
~~可能有依赖随机性的做法，但是我不太清楚。~~
### Subtask 7
在 Subtask 3 的基础上加上区间加操作即可。

时间复杂度同 Subtask 3，为 $O(n \log m + m \log m \log w)$。

代码：
```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

typedef long long ll;

typedef struct Query_tag {
	int id;
	int r;
	ll x;
	int type;
	Query_tag(){}
	Query_tag(int id_, int r_, ll x_, int type_){
		id = id_;
		r = r_;
		x = x_;
		type = type_;
	}
} Query;

typedef struct {
	int father;
	int ls;
	int rs;
	ll sub;
	ll add;
	ll real_val;
	ll sum;
	int heap_val;
} Node;

int root, id = 0;
int l[200007], r[200007], v[200007], anc[200007];
ll sum[200007], a[200007], ans[200007];
Query query[400007];
Node tree[200007];

bool operator <(const Query a, const Query b){
	return a.r < b.r;
}

inline int read(){
	int sign = 1, ans = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		if (ch == '-') sign = -sign;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return sign * ans;
}

inline void pushdown(int x){
	int ls = tree[x].ls, rs = tree[x].rs;
	if (tree[x].sub != 0){
		tree[ls].sub += tree[x].sub;
		tree[rs].sub += tree[x].sub;
		tree[ls].real_val -= tree[x].sub;
		tree[rs].real_val -= tree[x].sub;
		tree[x].sub = 0;
	}
	if (tree[x].add != 0){
		tree[ls].add += tree[x].add;
		tree[rs].add += tree[x].add;
		tree[ls].sum += tree[x].add;
		tree[rs].sum += tree[x].add;
		tree[x].add = 0;
	}
}

inline void update(int x){
	int ls = tree[x].ls, rs = tree[x].rs;
	if (ls != 0) tree[ls].father = x;
	if (rs != 0) tree[rs].father = x;
}

void split(int x, int &y, int &z, ll val){
	if (x == 0){
		y = z = 0;
		return;
	}
	pushdown(x);
	if (tree[x].real_val <= val){
		y = x;
		split(tree[x].rs, tree[x].rs, z, val);
	} else {
		z = x;
		split(tree[x].ls, y, tree[x].ls, val);
	}
	update(x);
}

inline int new_node(ll x){
	int ans = ++id;
	tree[ans].real_val = x;
	tree[ans].heap_val = rand();
	return ans;
}

int merge(int x, int y){
	if (x == 0) return y;
	if (y == 0) return x;
	pushdown(x);
	pushdown(y);
	if (tree[x].heap_val < tree[y].heap_val){
		tree[x].rs = merge(tree[x].rs, y);
		update(x);
		return x;
	}
	tree[y].ls = merge(x, tree[y].ls);
	update(y);
	return y;
}

inline void insert1(ll x){
	int y, z;
	split(root, y, z, x);
	root = merge(y, merge(new_node(x), z));
	tree[root].father = 0;
}

inline void insert2(int &root, int x){
	int y, z;
	split(root, y, z, tree[x].real_val);
	root = merge(y, merge(x, z));
	tree[root].father = 0;
}

void dfs(int &root, int x){
	if (x == 0) return;
	pushdown(x);
	dfs(root, tree[x].ls);
	dfs(root, tree[x].rs);
	tree[x].father = tree[x].ls = tree[x].rs = 0;
	insert2(root, x);
}

inline void process(int x, int y){
	int u, v, w;
	split(root, u, v, x);
	tree[v].sub += x;
	tree[v].real_val -= x;
	tree[v].add += y;
	tree[v].sum += y;
	split(v, v, w, x);
	dfs(u, v);
	root = merge(u, w);
}

inline void add(int l, int r, int x){
	int y, z, w;
	split(root, y, z, l - 1);
	split(z, z, w, r);
	tree[z].add += x;
	tree[z].sum += x;
	root = merge(y, merge(z, w));
}

inline ll get_val(int x){
	int cnt = 0;
	for (register int i = x; i != 0; i = tree[i].father){
		anc[++cnt] = i;
	}
	for (register int i = cnt; i >= 1; i--){
		pushdown(anc[i]);
	}
	return tree[x].sum;
}

int main(){
	int n = read(), m = read(), k, q = 0;
	for (register int i = 1; i <= n; i++){
		l[i] = read();
		r[i] = read();
		v[i] = read();
		if (r[i] == -1){
			sum[i] = sum[i - 1] + l[i];
		} else {
			sum[i] = sum[i - 1];
		}
	}
	for (register int i = 1; i <= m; i++){
		int l = read(), r = read(), x = read();
		ll x_ = x + sum[l - 1];
		a[i] = x_;
		query[++q] = Query(i, r, x_, 1);
		if (l > 1) query[++q] = Query(i, l - 1, x_, -1);
	}
	sort(a + 1, a + m + 1);
	k = unique(a + 1, a + m + 1) - a - 1;
	for (register int i = 1; i <= k; i++){
		insert1(a[i]);
	}
	for (register int i = 1; i <= q; i++){
		query[i].x = lower_bound(a + 1, a + k + 1, query[i].x) - a;
	}
	sort(query + 1, query + q + 1);
	for (register int i = 1, j = 1; i <= n; i++){
		if (r[i] == -1){
			process(l[i], v[i]);
		} else {
			add(l[i], r[i], v[i]);
		}
		while (j <= q && query[j].r == i){
			ans[query[j].id] += query[j].type * get_val(query[j].x);
			j++;
		}
	}
	for (register int i = 1; i <= m; i++){
		cout << ans[i] << endl;
	}
	return 0;
}
```

---

## 作者：_AyachiNene (赞：3)

平衡树合并做法。[前置知识](https://www.luogu.com.cn/article/p4ejw9j6)。
# 思路：
关于差分部分其他题解已经讲得很清楚了，这里就主要讲一下维护部分。首先离散化一下，只有 $n$ 个初始的钱数是有意义的，容易想到用一个扫描线维护到每一个位置钱数为 $x$ 的愉悦值，发现就是两个操作：

1. $r_i=-1$，把当前钱数大于 $l_i$ 的位置钱数减去 $l_i$，并把愉悦值加上 $v_i$。
2. $r_i\ne-1$，把当前钱数在 $l_i$ 到 $r_i$ 的位置愉悦值加上 $v_i$。

总结一下就是把一段值域上的数平移，区间加，感觉是很可以用平衡树做的。按钱数建出平衡树，把愉悦值作为权值，区间加不必多说，打标记就行，考虑怎么做到值域平移。有一个明显的想法就是把一段区间提出来，把这一段区间每个点的键值减去 $l_i$。这个操作看着是无法实现的，但用上平衡树合并就可以实现。这个操作看着不行的主要原因是因为改了键值后平衡树的内部结构会变，但注意到是把提出区间的一整棵树的键值都减去一个相同数，所以内部结构不会变，可以直接打上标记，结合平衡树合并，在合并过程中就改完了。还有就是一些细节问题，因为是按当前的钱数维护的，查询时要查最初值，所以最开时插入时记下在哪个点，查询时直接插就行。还有一个关于平衡树合并的细节，**就是键值不能相同**，不然势能是假的，具体的，可以用个二元组把编号也记进去。

# Code：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
namespace IO
{
	char buff[1<<21],*p1=buff,*p2=buff;
	char getch(){return p1==p2&&(p2=((p1=buff)+fread(buff,1,1<<21,stdin)),p1==p2)?EOF:*p1++;}
	template<typename T>void read(T &x){char ch=getch();int fl=1;x=0;while(ch>'9'||ch<'0'){if(ch=='-')fl=-1;ch=getch();}while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getch();}x*=fl;}
	template<typename T>void read_s(T &x){char ch=getch();while(ch<'a'||ch>'z')ch=getch();while(ch>='a'&&ch<='z'){x+=ch;ch=getch();}}
	template<typename T,typename ...Args>void read(T &x,Args& ...args){read(x);read(args...);}
	char obuf[1<<21],*p3=obuf;
	void putch(char ch) {if(p3-obuf<(1<<21))*p3++=ch;else fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=ch;}
	char ch[100];
	template<typename T>void write(T x) {if(!x)return putch('0');if(x<0)putch('-'),x*=-1;int top=0;while(x)ch[++top]=x%10+48,x/=10;while(top)putch(ch[top]),top--;}
	template<typename T,typename ...Args>void write(T x,Args ...args) {write(x);write(args...);}
	void put(string s){for(int i=0;i<s.size();i++)putch(s[i]);}
	void flush(){fwrite(obuf,p3-obuf,1,stdout);}
}
using namespace IO;
int n,m;
namespace Nene
{
	struct fhqt
	{
		int l,r,f,rnd;
		ll key,tagk,val,tagv;
	}t[1000005];
	int root,cnt;
	inline int New(ll k){t[++cnt]=(fhqt){0,0,0,rand(),k,0,0,0};return cnt;}
	inline void pushk(int p,ll v){t[p].tagk+=v;t[p].key+=v;}
	inline void pushv(int p,ll v){t[p].tagv+=v;t[p].val+=v;}
	inline void update(int p)
	{
		if(t[p].l) t[t[p].l].f=p;
		if(t[p].r) t[t[p].r].f=p;
	}
	inline void down(int p)
	{
		if(t[p].tagk)
		{
			if(t[p].l) pushk(t[p].l,t[p].tagk);
			if(t[p].r) pushk(t[p].r,t[p].tagk);
			t[p].tagk=0;
		}
		if(t[p].tagv)
		{
			if(t[p].l) pushv(t[p].l,t[p].tagv);
			if(t[p].r) pushv(t[p].r,t[p].tagv);
			t[p].tagv=0;
		}
	}
	int merge(int x,int y)
	{
		if(!x||!y) return x|y;
		down(x),down(y);
		if(t[x].rnd<t[y].rnd) return t[x].r=merge(t[x].r,y),update(x),x;
		return t[y].l=merge(x,t[y].l),update(y),y;
	}
	void split(int p,pair<ll,ll>v,int &x,int &y)
	{
		if(!p) return x=y=0,void();
		down(p);
		if((pair<ll,ll>){t[p].key,p}<=v) x=p,split(t[p].r,v,t[p].r,y);
		else y=p,split(t[p].l,v,x,t[p].l);
		update(p);
	}
	int merget(int x,int y)
	{
		if(!x||!y) return x|y;
		down(x),down(y);
		if(t[x].rnd>t[y].rnd) swap(x,y);
		int a,b;
		split(y,{t[x].key,x},a,b);
		t[x].l=merget(t[x].l,a);t[x].r=merget(t[x].r,b);
		update(x);return x;
	}
	int pos[1000005],stk[1000005],top;
	inline ll query(int p)
	{
		p=pos[p];
		for(int i=p;i;i=t[i].f) stk[++top]=i;
		while(top) down(stk[top--]);
		return t[p].val;
	}
	inline void insert(ll k,ll i)
	{
		int a,b;split(root,{k,cnt+1},a,b);
		pos[i]=cnt+1;
		root=merge(a,merge(New(k),b));
	}
}using namespace Nene;
struct que{int op,id;};
vector<que>q[1000005];
ll sum[1000005];
int l[1000005],r[1000005],v[1000005];
ll ans[1000005];
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n,m);
	for(int i=1;i<=n;i++) read(l[i],r[i],v[i]),sum[i]=sum[i-1]+(r[i]==-1?1:0)*l[i];
	for(int i=1;i<=m;i++)
	{
		ll l,r,x;read(l,r,x);
		x+=sum[l-1];insert(x,i);
		q[l-1].push_back((que){-1,i});q[r].push_back((que){1,i});
	}
	for(int i=1;i<=n;i++)
	{
		if(r[i]==-1)
		{
			int a,b;split(root,{l[i],n+1},a,b);
			pushv(b,v[i]);pushk(b,-l[i]);
			root=merget(a,b);
		}
		else if(l[i]<=r[i])
		{
			int a,b,c;split(root,{r[i],n+1},b,c);split(b,{l[i]-1,n+1},a,b);
			pushv(b,v[i]);
			root=merge(a,merge(b,c));
		}
		for(int j=0;j<q[i].size();j++) ans[q[i][j].id]+=q[i][j].op*query(q[i][j].id);
	}
	for(int i=1;i<=m;i++) write(ans[i]),putch('\n');
	flush();
	return 0;
}
```

---

## 作者：lfxxx (赞：1)

这个询问显然是有可差分性的，把走区间 $[1,l-1]$ 产生的代币消耗 $y$ 计算出来，那么答案显然等于 $q(1,r,x+y) - q(1,l-1,x+y)$。

那么考虑依次加入所有操作。

不难发现两类操作的本质是全局大于 $x$ 的数减去 $x$ 与区间加。

我们可以这么做：

每次全局大于 $x$ 的数减去 $x$ 时，将剩余代币按值域分裂成 $[1,l-1]$ $[l,2 \times l - 1]$ $[2 \times l,top]$ 三个部分，显然可以第一部分和第二部分可以直接打标记，中间这个部分因为打完标记之后值域会与第一个部分相交，所以考虑暴力取出所有数暴力修改。

下面说说复杂度：

假若一个数被暴力修改，那么它满足 $l \leq x < 2 \times l$，修改后它减少了 $l$ 或者说它至少减少了一半，因此一个数最多被暴力修改 $\log w$ 次。

用 FHQtreap 维护上述操作即可做到 $O(n \log n \log w)$。

需要注意的是我们将一个数暴力插入新的平衡树时需要重新赋一个随机权值以保证没有把这个数原来所在平衡树的结构（树高）复制过来。

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define ls(cur) treap[cur].ls
#define rs(cur) treap[cur].rs
#define tag1(cur) treap[cur].tag1
#define tag2(cur) treap[cur].tag2
namespace IO{
	const int SIZE=1<<21;
	static char ibuf[SIZE],obuf[SIZE],*iS,*iT,*oS=obuf,*oT=oS+SIZE-1;
    int qr;
    char qu[55],c;
    bool f;
	#define getchar() (IO::iS==IO::iT?(IO::iT=(IO::iS=IO::ibuf)+fread(IO::ibuf,1,IO::SIZE,stdin),(IO::iS==IO::iT?EOF:*IO::iS++)):*IO::iS++)
	#define putchar(x) *IO::oS++=x,IO::oS==IO::oT?flush():0
	#define flush() fwrite(IO::obuf,1,IO::oS-IO::obuf,stdout),IO::oS=IO::obuf
	#define puts(x) IO::Puts(x)
	template<typename T>
    inline void read(T&x){
    	for(f=1,c=getchar();c<48||c>57;c=getchar())f^=c=='-';
    	for(x=0;c<=57&&c>=48;c=getchar()) x=(x<<1)+(x<<3)+(c&15); 
    	x=f?x:-x;
    }
    template<typename T>
    inline void write(T x){
        if(!x) putchar(48); if(x<0) putchar('-'),x=-x;
        while(x) qu[++qr]=x%10^48,x/=10;
        while(qr) putchar(qu[qr--]);
    }
    inline void Puts(const char*s){
    	for(int i=0;s[i];i++)
			putchar(s[i]);
		putchar('\n');
	}
	struct Flusher_{~Flusher_(){flush();}}io_flusher_;
}
using IO::read;
using IO::write;
using namespace std;
const int maxn = 2e5+114;
int tot,rt;
struct Node_treap{
	int val;//随机权值
	int ls,rs;
	long long a,b,c;//(a,b,c) 初始代币数量为 a 当前代币数量为 b 获得的愉悦值为 c 
	long long tag1;//子树加 
	long long tag2;//子树下标减 
	int fa;//父亲节点 
}treap[maxn];
__gnu_pbds::gp_hash_table <long long,int> chifan;
long long answer[maxn];
inline int clone(long long a,long long b,long long c){
	treap[++tot].a=a,treap[tot].b=b,treap[tot].c=c;
	treap[tot].val=rand();
	treap[tot].fa=0;
	chifan[a]=tot; 
	return tot;	
}
inline void pushdown(int cur){
	if(ls(cur)!=0) treap[ls(cur)].c+=tag1(cur),treap[ls(cur)].tag1+=tag1(cur),treap[ls(cur)].b-=tag2(cur),treap[ls(cur)].tag2+=tag2(cur);
	if(rs(cur)!=0) treap[rs(cur)].c+=tag1(cur),treap[rs(cur)].tag1+=tag1(cur),treap[rs(cur)].b-=tag2(cur),treap[rs(cur)].tag2+=tag2(cur);
	treap[cur].tag1=treap[cur].tag2=0;
}
inline int merge(int x,int y){
	pushdown(x);
	pushdown(y);
    if (!x||!y) return x+y;
    if (treap[x].val<treap[y].val){
        treap[x].rs=merge(treap[x].rs,y);
        treap[rs(x)].fa=x;
        return x;
    }
    else{
        treap[y].ls=merge(x,treap[y].ls);
        treap[ls(y)].fa=y;
        return y;
    }
}
inline void split(int cur,long long x,int &l,int &r){
	pushdown(cur);
	if(cur==0){
		l=r=0;
		return ;
	}
	if(treap[cur].b>x){
		r=cur;
		split(treap[cur].ls,x,l,treap[cur].ls);
		treap[ls(cur)].fa=cur;
	}
	else{
		l=cur;
		split(treap[cur].rs,x,treap[cur].rs,r);
		treap[rs(cur)].fa=cur;
	}
}
inline void insert(int &cur,long long a,long long b,long long c){
	int x=0,y=0,z=0;
	y=clone(a,b,c);
	split(cur,b,x,z);
	cur=merge(x,merge(y,z));
	treap[cur].fa=0;
}
inline void add(int l,int r,long long v){
	int x=0,y=0,z=0;
	split(rt,l-1,x,y);
	split(y,r,y,z);
	treap[y].c+=v;
	treap[y].tag1+=v;
	rt=merge(x,merge(y,z));
	treap[rt].fa=0;
}
inline void cost(long long l,long long v){
	int x=0,y=0,z=0;
	split(rt,l,x,y);
	split(y,2*l,y,z);
	treap[z].c+=v;
	treap[z].tag1+=v;
	treap[z].b-=l;
	treap[z].tag2+=l;
	queue<int> q;
	q.push(y); 
	while(q.size()>0){
		int s=q.front();
		q.pop();
		if(s==0) continue;
		pushdown(s);
		if(treap[s].ls!=0) q.push(treap[s].ls);
		if(treap[s].rs!=0) q.push(treap[s].rs);
		treap[s].b-=l,treap[s].c+=v;
		treap[s].fa=treap[s].ls=treap[s].rs=0;
		treap[s].val=rand();
		int f=0,g=0;
		split(x,treap[s].b,f,g);
		x=merge(f,merge(s,g));
	} 
	rt=merge(x,z);
	treap[rt].fa=0;
}
inline long long query(long long x){
	int now=chifan[x];
	int res=now;
	stack<int> s;
	while(now!=0){
		s.push(now);
		now=treap[now].fa;
	} 
	while(s.size()>0){
		pushdown(s.top());
		s.pop();
	}
	return treap[res].c;
}
struct Node{
	long long k,id,op;
};
vector<Node> q[maxn];
struct node{
	int l,r;
	long long v;
};
node A[maxn];
long long pre[maxn];
int n,m;
signed main(){
	srand(time(0));
	read(n);
	read(m);
	for(int i=1;i<=n;++i){
		int l,r;
		long long v;
		read(l);
		read(r);
		read(v);
		pre[i]=pre[i-1];
		if(r==-1) pre[i]+=l;
		A[i]=node{l,r,v};
	} 
	for(int i=1;i<=m;++i){
		int l,r;
		long long x;
		read(l);
		read(r);
		read(x);
		q[l-1].push_back(Node{x+pre[l-1],i*1ll,-1*1ll});
		q[r].push_back(Node{x+pre[l-1],i*1ll,1*1ll});
		if(chifan[x+pre[l-1]]==0){
			insert(rt,x+pre[l-1],x+pre[l-1],0);
		}
	}
	for(int i=1;i<=n;++i){
		if(A[i].r==-1){
			cost(A[i].l,A[i].v);
		}
		else{
			add(A[i].l,A[i].r,A[i].v);
		}
		for(int j=0;j<q[i].size();++j){
			answer[q[i][j].id]+=q[i][j].op*query(q[i][j].k);
		}
	}
	for(int i=1;i<=m;++i) write(answer[i]),putchar('\n');
}
```

---

