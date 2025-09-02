# [JOI 2024 Final] 礼物交换 / Gift Exchange

## 题目描述

JOI 学园有 $N$ 名学生，每个学生都有一个从 $1$ 到 $N$ 的编号。

JOI 学园计划近期举办一个礼物交换会。每个学生都要准备一份礼物带到会场，学生 $i\ (1 \leq i \leq N)$ 带来的礼物的价值是 $A_{i}$ 。学生们都不喜欢收到比自己带来的礼物价值低很多的礼物，具体来说，学生 $i$ 如果收到价值低于 $B_{i}$ 的礼物，就会感到不满。保证 $B_{i}<A_{i}$。

不过，并不是所有 $N$ 名学生都会真的参加礼物交换会。JOI 学园的校长 K 正在考虑 $Q$ 种可能参加礼物交换会的学生组合，第 $j\ (1 \leq j \leq Q)$ 种组合由 $R_{j}-L_{j}+1$ 名学生 $L_{j}, L_{j}+1, \ldots, R_{j}$ 组成。

对于一个由 $2$ 人以上的学生组成的组合，如果他们可以在组内互换礼物，而不会有人收到自己带来的礼物或者不满意的礼物，那么这个组合就是可行的。准确地说，由 $m$ 名 $(m \geq 2)$ 学生 $p_{1}, p_{2}, \ldots, p_{m}$ 组成的组合是可行的，当且仅当存在一个由 $p_{1}, p_{2}, \ldots, p_{m}$ 重新排列得到的数列 $q_{1}, q_{2}, \ldots, q_{m}$，这里 $q_{k}\ (1 \leq k \leq m)$ 表示给学生 $p_{k}$ 送礼物的学生的编号，满足以下的条件：

- 对于所有的 $k\ (1 \leq k \leq m)$ ，$p_{k} \neq q_{k}$。
- 对于所有的 $k\ (1 \leq k \leq m)$ ，$A_{q_{k}} \geq B_{p_{k}}$。

校长 K 想要让礼物交换会成功的，所以他想要知道这 $Q$ 个组合中，哪些是可行的。

给定学生的信息和组合的信息，对于每个组合，判断它是否是可行的，并编写一个程序来输出结果。

## 说明/提示

**样例解释**

第一个组合是由 2 名学生 3,4 组成的。如果学生 3 收到学生 4 的礼物，学生 4 收到学生 3 的礼物，那么由于 $A_{3} \geq B_{4} 且 A_{4} \geq B_{3}$ ，所以两个学生都不会不满。因此，这个组合是可行的，所以在第一行输出 Yes。

第二个组合是由 3 名学生 1,2,3 组成的。由于 $A_{1}<B_{2}$ 且 $A_{3}<B_{2}$ ，所以学生 2 不管收到学生 1 还是学生 3 的礼物，都会感到不满。因此，这个组合不是可行的，所以在第二行输出 No。

第三个组合是由 4 名学生 1,2,3,4 组成的。例如，如果学生 1 收到学生 2 的礼物，学生 2 收到学生 4 的礼物，学生 3 收到学生 1 的礼物，学生 4 收到学生 3 的礼物，那么没有人会不满。因此，这个组合是可行的，所以在第三行输出 Yes。

这个样例满足子任务 1,2,4,7,8 的限制。

**数据范围**

对于所有输入数据，满足：

- $2 \leq N \leq 5\times 10^5$
- $1 \leq B_{i}<A_{i} \leq 2N\ (1 \leq i \leq N)$
- $A_{1}, B_{1}, A_{2}, B_{2}, \ldots, A_{N}, B_{N}$ 各不相同
- $1 \leq Q \leq 2\times 10^5$
- $1 \leq L_{j}<R_{j} \leq N\ (1 \leq j \leq Q)$

详细子任务附加限制及分值如下表所示。

|子任务|	附加限制|	分值|
|:-:|:-:|:-:|
|1|	$N \leq 10, Q \leq 10$|	4
|2|	$N \leq 18, Q \leq 10$|	5
|3|	$N \leq 10^5, A_{1} \geq 2 N-2, B_{1}=1, Q=1, L_{1}=1, R_{1}=N$|	10
|4|	$N \leq 10^5, Q \leq 10$|	31
|5|	$N \leq 10^5, A_{i}<A_{i+1}, B_{i}<B_{i+1}\ (1 \leq i \leq N-1)$|	8
|6|	$N \leq 10^5, A_{i}<A_{i+1}\ (1 \leq i \leq N-1)$|	12
|7|	$N \leq 10^5$|	18
|8|	无附加限制	|12

## 样例 #1

### 输入

```
4
3 8 5 7
2 6 1 4
3
3 4
1 3
1 4```

### 输出

```
Yes
No
Yes```

# 题解

## 作者：Perta (赞：5)

考虑什么样的区间是合法的。

题目很二分图。不妨将 $A$ 看成左部点，$B$ 看成右部点。每次询问的区间 $[l,r]$ 中，对于所有 $i\in[l,r]$，$A_i$ 向所有满足 $j\in[l,i)\cup(i,r],A_i>B_j$ 的 $B_j$ 连边，答案等价于是否有完美匹配。

将 $A$ 与 $B$ 放在一起从小到大排序，若最后排出来的形式为 $\underbrace{BABABBA\dots}_{k个A,k个B}B_xA_x\dots$ 必然无解。每个 $A_i$ 对一个前缀里的所有 $B$ 连边然后删掉边 $(A_i,B_i)$。根据 hall 定理，这 $k$ 个 $A$ 与 $A_x$ 的邻集大小为 $k<k+1$，则不存在完美匹配。

发现好像构造不出来其他的无解形式了，尝试归纳上述情况：存在 $i$ 满足 $B_i,A_i$ 相邻且 $B_i$ 之前的 $A$ 与 $B$ 数量相等。

由于 $B_i<A_i$，则排序之后的形式必然是一个合法的括号匹配，不考虑删边，始终有 $\lvert S\rvert\leq\lvert T\rvert$（$T$ 为 $S$ 的邻集）；删除 $(A_i,B_i)$ 后，有 $\lvert S\rvert\leq\lvert T\rvert-1$，当且仅当在上述情况时取等。

***

有了结论后，实现是简单的。

将第 $i$ 个学生看成区间 $[B_i,A_i]$，结论等价于存在一个区间与其他区间的交集为空。预处理 $L_i,R_i$ 分别表示 $i$ 左边最近的与 $i$ 有交的区间， $i$ 右边最近的与 $i$ 有交的区间（不存在则分别为极小/极大值），合法要求 $\forall i\in[l,r],[l,r]\notin(L_i,R_i)$。

求 $L_i,R_i$ 是区间覆盖求极值，判合法可以离线扫描线，时间复杂度 $O((N+Q)\log N)$。

[Code](https://www.luogu.com.cn/paste/t6o9e3sn)

---

## 作者：是青白呀 (赞：4)

首先二分图匹配的模型是显然的。我们对于一个 $A_i$，将其向所有满足 $B_j\leq A_i$ 且 $i\neq j$ 的 $B_j$ 连边，然后对每个询问做最大匹配即可。

考虑怎样才会不合法。利用霍尔定理，合法的充要条件是任意大小为 $k$ 的 $B$ 集合的邻域大小都不能小于 $k$。这里可以先考虑一些极端情况：对于 $A$ 最大的 $x$，若不存在一个 $A_i>B_x$，则 $x$ 无法收到礼物，一定不合法。也即，若我们把 $[B_i,A_i]$ 看作一条线段，则需要保证最大的那一条线段与其它线段有交。

考虑扩展这一结论：有合法解的条件是任意线段都与其它线段有交。这里的必要性比较容易证明：假设线段 $[A_i,B_i]$ 与其它线段无交，则拿出坐标小于等于这个线段的所有线段（含其本身）的集合 $S$，考虑任意 $x\in S$ 对应的 $B$ 处点集的邻域，由于自己不和自己连边，显然有邻域大小为 $|S|<|S|+1$，故一定不存在完美匹配。

接下来考虑这个结论的充分性：对于任意一个 $B$ 集合，取出 $B_x$ 最小的那一个 $x$，则 $B_x$ 一定向集合内的其它元素的 $A$ 部有连边，则邻域大小至少为 $|B|-1$。又因为一定存在线段与 $[B_x,A_x]$ 相交，不妨假设 $[B_y,A_y]$ 与其相交，讨论相交情况：

1. 若 $B_y\leq B_x$，则 $y$ 一定不在当前 $B$ 集合内。由于相交一定有 $A_y\geq B_x$，即 $B_x$ 一定与 $A_y$ 相连，可给邻域额外贡献 $1$，合法。
2. 若 $B_y\geq B_x$，由于相交，一定有 $B_y\leq A_x$，此时 $B_x$ 一定与 $A_y$ 相连。讨论下面两种情况：
   - 若 $y\in B$，则 $B_y$ 一定连边向 $A_x$，可给邻域额外贡献 $1$，合法。
   - 若 $y\notin B$，则 $A_y$ 可给邻域额外贡献 $1$，合法。

根据霍尔定理，任意一个 $B$ 集合的邻域大小都至少为 $|B|$，故存在完美匹配。充分性得证。

于是可以预处理求出 $L_i$ 表示每个线段标号左侧首个与 $i$ 相交的标号。从左往右扫一遍，等价于区间覆盖，求区间最大值。$R_i$ 同理。

最终就变成每次询问给定一个 $l,r$，不合法的情况即为存在一个 $i$ 满足 $L_i<l\leq i\leq r<R_i$，即有若干左上角在 $(L_i+1,i)$，右下角在 $(i,R_i-1)$ 位置的矩形，每次询问判断点 $(l,r)$ 是否被某个矩形覆盖，是则不合法，输出 `No`，离线后扫描线即可。

---

## 作者：ningago (赞：2)

先看 $l=1,r=n$ 怎么做，建出一个二分图，每个左点 $i$ 向 $B_i\leq A_j$ 的右点 $j'$ 连边，并且 $i$ 不能连 $i'$。`Yes` 的条件即为存在完美匹配。

这个图有一个很强的性质：若 $A_j>A_i$ 则必然存在 $i\to j'$。

（这里暂时把序列按 $A$ 排序）

使用哈儿定理 $\forall S,|N(S)|\geq |S|$。由于上述性质的存在，考虑钦定 $S$ 中 $A$ 的最小值取到了 $A_i$，那么 $j>i$ 的共 $n-i$ 个 $j'$ 一定会存在于 $N(S)$ 内。那么可以默认 $i+1\sim n$ 都存在于 $S$ 中。

判定条件变为：$\forall i$，$B_i\leq A_{i-1}$（能往前匹配）或 $\exist j>i,B_j\leq A_i$（能被匹配）。即可 $O(n)$ 解决。

回到原问题。考虑对于每个点 $i$（这里不排序了），求出 $L_i$ 表示最大的 $j=L_i\leq i$ 能满足上述判定条件，$R_i$ 同理。

可以用一个区间修改区间 $\max/\min$ 的线段树求出。

那么一个询问不合法当且仅当存在 $L_i<l\leq i\leq r<R_i$，二维数点即可。

复杂度 $O(n\log n)$。

```cpp

#define N 1000010
int n, m, a[N], b[N], l_[N], r_[N], L[N], R[N];
std::function <int(int, int)> F; int epsil;
struct Tree
{
	int lazy, mx;
	void push(int z) { lazy = z; mx = lazy; }
}tr[N << 2];
#define lson k << 1
#define rson k << 1 | 1
#define ls lson, l, mid
#define rs rson, mid + 1, r
#define root 1, 1, n + n
void pushup(int k) { tr[k].mx = F(tr[lson].mx, tr[rson].mx); }

void pushdown(int k) { if(tr[k].lazy) { tr[lson].push(tr[k].lazy), tr[rson].push(tr[k].lazy), tr[k].lazy = 0; } }
void build(int k, int l, int r)
{
	tr[k].lazy = 0; tr[k].mx = epsil;
	if(l == r) return;
	int mid = (l + r) >> 1; build(ls); build(rs);
}
void change(int k, int l, int r, int ql, int qr, int z)
{
	if(ql <= l && r <= qr) return tr[k].push(z);
	int mid = (l + r) >> 1; pushdown(k);
	if(ql <= mid) change(ls, ql, qr, z);
	if(mid < qr)  change(rs, ql, qr, z);
	pushup(k);
}

int query(int k, int l, int r, int ql, int qr)
{
	if(ql <= l && r <= qr) return tr[k].mx;
	int mid = (l + r) >> 1, res = epsil; pushdown(k);
	if(ql <= mid) res = F(res, query(ls, ql, qr));
	if(mid < qr)  res = F(res, query(rs, ql, qr));
	return res;
}

namespace BIT
{
	int tr[N];
	void ins(int x, int z) { for(; x <= n; x += x & (-x)) tr[x] += z; }
	int query(int x) { int res = 0; for(; x; x -= x & (-x)) res += tr[x]; return res; }
} // namespace BIT

std::vector <pii> nvec[N], qvec[N];
int ans[N];

void solve()
{
	n = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	for(int i = 1; i <= n; i++) b[i] = read();
	m = read();
	for(int i = 1; i <= m; i++) l_[i] = read(), r_[i] = read();
	F = [&](int x, int y) -> int { return x < y ? x : y; };
	epsil = n + 1; build(root);
	for(int i = n; i >= 1; i--)
	{
		R[i] = query(root, b[i], a[i]);
		change(root, b[i], a[i], i);
	}
	F = [&](int x, int y) -> int { return x > y ? x : y; };
	epsil = 0; build(root);
	for(int i = 1; i <= n; i++)
	{
		L[i] = query(root, b[i], a[i]);
		change(root, b[i], a[i], i);
	}
	for(int i = 1; i <= n; i++)
	{
		nvec[L[i] + 1].push_back(mkp(i, 1));
		nvec[L[i] + 1].push_back(mkp(R[i], -1));
		nvec[i + 1].push_back(mkp(i, -1));
		nvec[i + 1].push_back(mkp(R[i], 1));
	}
	for(int i = 1; i <= m; i++) qvec[l_[i]].push_back(mkp(r_[i], i));
	for(int i = 1; i <= n; i++)
	{
		for(pii t : nvec[i]) BIT::ins(t.fi, t.se);
		for(pii t : qvec[i])
			ans[t.se] = !BIT::query(t.fi);
	}
	for(int i = 1; i <= m; i++) 
	{
		if(ans[i]) printf("Yes\n");
		else printf("No\n");
	}
}
```

---

## 作者：ax_by_c (赞：0)

记第 $i$ 个人给第 $p_i$ 个人礼物。

考虑直接构造方案，当两个人的 $[B,A]$ 有交时令他们连边，一开始 $p_i=i$。

对于每个连通块，将其内部的人按 $B$ 排序，那么从小到大扫的时候第一个人之外的人前面都存在至少一个人和他有交。

证明：若存在一个人和前面的人无交，因为 $B$ 单调，所以后面的人与前面的人也无交，与连通矛盾。证毕。

那么可以直接让这两个人的 $p$ 互换，显然是合法的。唯一不合法的就是这个连通块里面只有一个人，因为前面需要配完且他不能和后面配，所以这种情况确实是不合法的。

于是原问题变为了判断区间 $[l,r]$ 中是否所有 $[B,A]$ 都与另外至少一个 $[B,A]$ 有交。

考虑先用值域线段树求出每个 $[B_i,A_i]$ 左边和右边第一个与它有交的 $l_i,r_i$，那么合法等价于 $\nexists l_x<l\le x\le r<r_x$。

考虑每个 $x$ 的限制：$\forall r\in[x,r_x),l\not\in(l_x,x]$。相当于在二维平面内限制了一个矩形中的点不合法。

于是扫描线即可，时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
#define per(i,r,l) for(int i=(r);i>=(l);i--)
#define repll(i,l,r) for(ll i=(l);i<=(r);i++)
#define perll(i,r,l) for(ll i=(r);i>=(l);i--)
#define pb push_back
#define ins insert
#define clr clear
using namespace std; 
namespace ax_by_c{
typedef long long ll;
typedef pair<int,int> pii;
const int intinf=1e9;
const int N=1e6+5;
struct DS1{
	struct node{
		int mx,z;
	}tr[N*4];
	void pu(int u){
		tr[u].mx=max(tr[u<<1].mx,tr[u<<1|1].mx);
	}
	void pd_(int u,int z){
		tr[u].mx=max(tr[u].mx,z);
		tr[u].z=max(tr[u].z,z);
	}
	void pd(int u){
		pd_(u<<1,tr[u].z);
		pd_(u<<1|1,tr[u].z);
		tr[u].z=-intinf;
	}
	void bld(int u,int l,int r){
		tr[u].z=-intinf;
		if(l==r){
			tr[u].mx=-intinf;
			return ;
		}
		int mid=l+((r-l)>>1);
		bld(u<<1,l,mid);
		bld(u<<1|1,mid+1,r);
		pu(u);
	}
	void upd(int u,int l,int r,int ql,int qr,int z){
		if(ql<=l&&r<=qr){
			pd_(u,z);
			return ;
		}
		pd(u);
		int mid=l+((r-l)>>1);
		if(ql<=mid)upd(u<<1,l,mid,ql,qr,z);
		if(mid+1<=qr)upd(u<<1|1,mid+1,r,ql,qr,z);
		pu(u);
	}
	int Q(int u,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr)return tr[u].mx;
		pd(u);
		int res=-intinf,mid=l+((r-l)>>1);
		if(ql<=mid)res=max(res,Q(u<<1,l,mid,ql,qr));
		if(mid+1<=qr)res=max(res,Q(u<<1|1,mid+1,r,ql,qr));
		return res;
	}
}tr;
struct BIT{
	int lb(int x){
		return x&(-x);
	}
	int n,tr[N];
	void clr(int n_){
		n=n_;
		rep(i,1,n)tr[i]=0;
	}
	void Add(int i,int x){
		for(;i<=n;i+=lb(i))tr[i]+=x;
	}
	void upd(int l,int r,int x){
		Add(l,x),Add(r+1,-x);
	}
	int q(int i){
		int r=0;
		for(;i;i-=lb(i))r+=tr[i];
		return r;
	}
}tr_;
int n,q,L[N],R[N];
int l[N],r[N];
vector<int>ad[N],rm[N];
vector<pii>qs[N];
bool ans[N];
void slv(int _csid,int _csi){
	scanf("%d",&n);
	rep(i,1,n)scanf("%d",&R[i]);
	rep(i,1,n)scanf("%d",&L[i]);
	tr.bld(1,1,n*2);
	rep(i,1,n){
		l[i]=max(0,tr.Q(1,1,n*2,L[i],R[i]));
		tr.upd(1,1,n*2,L[i],R[i],i);
	}
	tr.bld(1,1,n*2);
	per(i,n,1){
		r[i]=min(n+1,-tr.Q(1,1,n*2,L[i],R[i]));
		tr.upd(1,1,n*2,L[i],R[i],-i);
	}
	rep(i,1,n)ad[i].pb(i),rm[r[i]].pb(i);
	scanf("%d",&q);
	rep(i,1,q){
		int l,r;
		scanf("%d %d",&l,&r);
		qs[r].pb({l,i});
	}
	tr_.clr(n);
	rep(i,1,n){
		for(auto x:ad[i])tr_.upd(l[x]+1,x,1);
		for(auto x:rm[i])tr_.upd(l[x]+1,x,-1);
		for(auto it:qs[i])ans[it.second]=!tr_.q(it.first);
	}
	rep(i,1,q){
		if(ans[i])puts("Yes");
		else puts("No");
	}
}
void main(){
//	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int T=1,csid=0;
//	scanf("%d",&csid);
//	scanf("%d",&T);
	rep(i,1,T)slv(csid,i);
}
}
int main(){
	string __name="";
	if(__name!=""){
		freopen((__name+".in").c_str(),"r",stdin);
		freopen((__name+".out").c_str(),"w",stdout);
	}
	ax_by_c::main();
	return 0;
}
```

---

## 作者：takanashi_mifuru (赞：0)

mmp，模拟赛进场把 T2 秒了，不会 T1？

哇这个匹配看着就 hall 定理，容易发现只有前缀有用，因为一个点的排名意味着这个点至少能够拿下所有比他矮的人的椅子，hall 定理是求并，如果有人能把他椅子坐了，那就圆满了，如果没有，就需要这个人去坐别人椅子。

我们把这个条件写下来，别人把第 $i$ 个人椅子坐了，也就是存在 $j$ 使得 $b_i<a_j<a_i$，他坐别人椅子，也就是存在 $k$ 使得 $b_k<a_i<a_k$，考虑求出左边和右边第一个满足这样条件的位置（扫几遍就行），对于第 $i$ 个点，我们认为左边第一个是 $L$，右边第一个是 $R$ 就行了。

然后考虑怎么判定区间是否合法，容易发现对于一个点，只要满足包含其 $L$ 或包含其 $R$，他就一定能凑够椅子然后满足 hall 定理的条件，换句话说只要存在一个 $L_i,R_i$ 满足在这个 $i$ 在询问区间内且 $[L,R]$ 严格包含询问区间，他就寄了。

怎么求嘞，树套树，两个 log，非常垃圾，考虑离线询问，排序双指针消掉 $R$，丢到线段树上消掉 $i$，问题就是 $L$ 的限制，我们只关心可行性问题，所以只需要求出区间的 $L$ 的最小值符不符合条件就行了。

时间复杂度 $O(n\log n)$，还算好写。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[500005];
int b[500005];
int L[500005],R[500005];
int rnka[1000005];
struct node{
    int lt,rt,id;
    bool friend operator < (const node &a,const node &b){
        return a.rt>b.rt;
    }
}Q[500005],A[500005];
class SegMaxTree{
    public:
    int Tree[1000005<<2];
    void pushup(int cur){
        Tree[cur]=max(Tree[cur<<1],Tree[cur<<1|1]);
        return;
    }
    void build(int cur,int lt,int rt){
        if(lt==rt){
            Tree[cur]=0;
            return;
        }
        int mid=lt+rt>>1;
        build(cur<<1,lt,mid);
        build(cur<<1|1,mid+1,rt);
        pushup(cur);
        return;
    }
    void update(int cur,int lt,int rt,int Q,int val){
        if(lt>Q||rt<Q)return;
        if(lt==rt){
            Tree[cur]=val;
            return;
        }
        int mid=lt+rt>>1;
        update(cur<<1,lt,mid,Q,val);
        update(cur<<1|1,mid+1,rt,Q,val);
        pushup(cur);
        return;
    }
    int query(int cur,int lt,int rt,int qx,int qy){
        if(lt>qy||rt<qx)return 0;
        if(lt>=qx&&rt<=qy)return Tree[cur];
        int mid=lt+rt>>1;
        return max(query(cur<<1,lt,mid,qx,qy),query(cur<<1|1,mid+1,rt,qx,qy));
    }
}Pmax;
class SegMinTree{
    public:
    int Tree[1000005<<2];
    void pushup(int cur){
        Tree[cur]=min(Tree[cur<<1],Tree[cur<<1|1]);
        return;
    }
    void build(int cur,int lt,int rt){
        if(lt==rt){
            Tree[cur]=n+1;
            return;
        }
        int mid=lt+rt>>1;
        build(cur<<1,lt,mid);
        build(cur<<1|1,mid+1,rt);
        pushup(cur);
        return;
    }
    void update(int cur,int lt,int rt,int Q,int val){
        if(lt>Q||rt<Q)return;
        if(lt==rt){
            Tree[cur]=val;
            return;
        }
        int mid=lt+rt>>1;
        update(cur<<1,lt,mid,Q,val);
        update(cur<<1|1,mid+1,rt,Q,val);
        pushup(cur);
        return;
    }
    int query(int cur,int lt,int rt,int qx,int qy){
        if(lt>qy||rt<qx)return n+1;
        if(lt>=qx&&rt<=qy)return Tree[cur];
        int mid=lt+rt>>1;
        return min(query(cur<<1,lt,mid,qx,qy),query(cur<<1|1,mid+1,rt,qx,qy));
    }
}Pmin;
class SegSumTree{
    public:
    int Tree[1000005<<2];
    void pushup(int cur){
        Tree[cur]=Tree[cur<<1]+Tree[cur<<1|1];
        return;
    }
    void build(int cur,int lt,int rt){
        if(lt==rt){
            Tree[cur]=0;
            return;
        }
        int mid=lt+rt>>1;
        build(cur<<1,lt,mid);
        build(cur<<1|1,mid+1,rt);
        pushup(cur);
        return;
    }
    void update(int cur,int lt,int rt,int Q,int val){
        if(lt>Q||rt<Q)return;
        if(lt==rt){
            Tree[cur]=val;
            return;
        }
        int mid=lt+rt>>1;
        update(cur<<1,lt,mid,Q,val);
        update(cur<<1|1,mid+1,rt,Q,val);
        pushup(cur);
        return;
    }
    void updR(int cur,int lt,int rt,int qx,int qy,int val){
        if(!Tree[cur])return;
        if(rt<qx||lt>qy)return;
        if(lt==rt){
            R[rnka[lt]]=min(R[rnka[lt]],val);
            Tree[cur]=0;
            return;
        }
        int mid=lt+rt>>1;
        updR(cur<<1,lt,mid,qx,qy,val);
        updR(cur<<1|1,mid+1,rt,qx,qy,val);
        pushup(cur);
    }
    void updL(int cur,int lt,int rt,int qx,int qy,int val){
        if(!Tree[cur])return;
        if(rt<qx||lt>qy)return;
        if(lt==rt){
            L[rnka[lt]]=max(L[rnka[lt]],val);
            Tree[cur]=0;
            return;
        }
        int mid=lt+rt>>1;
        updL(cur<<1,lt,mid,qx,qy,val);
        updL(cur<<1|1,mid+1,rt,qx,qy,val);
        pushup(cur);
    }
}Psum;
bool ans[500005];
int main(){
    // freopen("b.in","r",stdin);
    // freopen("b.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        rnka[a[i]]=i;
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&b[i]);
    }
    for(int i=1;i<=n;i++){
        L[i]=0,R[i]=n+1;
    }
    Pmax.build(1,1,n*2);
    for(int i=1;i<=n;i++){
        L[i]=max(Pmax.query(1,1,n*2,b[i],a[i]),L[i]);
        Pmax.update(1,1,n*2,a[i],i);
    }
    Pmin.build(1,1,n*2);
    for(int i=n;i>=1;i--){
        R[i]=min(Pmin.query(1,1,n*2,b[i],a[i]),R[i]);
        Pmin.update(1,1,n*2,a[i],i);
    }
    Psum.build(1,1,n*2);
    for(int i=1;i<=n;i++){
        Psum.updR(1,1,n*2,b[i],a[i],i);
        Psum.update(1,1,n*2,a[i],1);
    }
    Psum.build(1,1,n*2);
    for(int i=n;i>=1;i--){
        Psum.updL(1,1,n*2,b[i],a[i],i);
        Psum.update(1,1,n*2,a[i],1);
    }
    int q;
    scanf("%d",&q);
    for(int i=1;i<=q;i++){
        int lt,rt;
        scanf("%d%d",&lt,&rt);
        Q[i]=node{lt,rt,i};
    }
    for(int i=1;i<=n;i++){
        A[i]=node{L[i],R[i],i};
    }
    sort(Q+1,Q+1+q);
    sort(A+1,A+1+n);
    int pos=1;
    Pmin.build(1,1,n);
    for(int i=1;i<=q;i++){
        while(pos<=n&&A[pos].rt>Q[i].rt){
            Pmin.update(1,1,n,A[pos].id,A[pos].lt);
            pos++;
        }
        if(Pmin.query(1,1,n,Q[i].lt,Q[i].rt)<Q[i].lt)ans[Q[i].id]=false;
        else ans[Q[i].id]=true;
    }
    for(int i=1;i<=q;i++){
        if(ans[i]){
            puts("Yes");
        }
        else{
            puts("No");
        }
    }
    return 0;
}

```

---

