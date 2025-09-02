# [NOISG 2023 Finals] Curtains

## 题目描述

兔子 Benson 正要在飞机上组织表演！

Benson 有 $n$ 个舞台，由 $1\sim n$ 编号。他有 $m$ 个幕布，由 $1\sim m$ 编号。

幕布可以下降——第 $i$ 个幕布下降后，它会遮挡住编号在 $[l_i,r_i]$ 内的舞台。

Benson 将组织 $q$ 次演出，由 $1\sim q$ 编号。第 $i$ 场演出需要使用编号在 $[s_j,e_j]$ 内的舞台。对于每场演出，Benson 想知道，是否能下降某些幕布，**恰好**遮住表演所需的舞台。

**形式化地**：重新定义区间 $[x,y]$ 只包含当中的整点，即表示集合 $\{x,x+1,\cdots,y\}$。给定 $m$ 个区间 $[l_i,r_i]$，每次询问给定区间 $[s_j,e_j]$，查询是否能选择一些区间，使它们的并恰好为 $[s_j,e_j]$。

## 说明/提示

#### 数据范围

| Subtask | 分值 | 特殊限制 |
| :-----------: | :-----------: | :-----------: |
| $0$ | $0$ | 样例 |
| $1$ | $3$ | $n,m,q\leq 200$ |
| $2$ | $6$ | $n,m,q\leq 2000$ |
| $3$ | $15$ | $n\leq 2000$ |
| $4$ | $20$ | $s_j=1$ |
| $5$ | $36$ | $n,m,q\leq 10^5$ |
| $6$ | $20$ | 无 |

对于 $100\%$ 的数据：

- $1\leq n,m,q\leq 5\times 10^5$
- $1\leq l_i\leq r_i\leq n$
- $1\leq s_j\leq e_j\leq n$

注：由于洛谷限制，数据不完全按照原题分配子任务。

## 样例 #1

### 输入

```
6 2 3
1 2
3 4
1 3
1 4
1 5
```

### 输出

```
NO
YES
NO
```

## 样例 #2

### 输入

```
10 10 10
6 9
6 7
1 6
10 10
5 9
3 9
2 10
5 7
9 10
5 10
7 8
4 7
1 6
2 7
3 9
7 7
2 9
4 9
6 6
5 7
```

### 输出

```
NO
NO
YES
NO
YES
NO
NO
NO
NO
YES
```

# 题解

## 作者：Purslane (赞：7)

# Solution

给个 $O((n+q) \log^2 n)$ 的做法，不需要任何思考，而且运行时间只是单 $\log$ 的两倍。

考虑扫描线，对于 $l=n,n-1,\cdots,1$，维护每个 $r \ge l$，用 $[l,r]$ 内包含的连续段能覆盖的最长的连续后缀长度，设为 $a_r$。我们只需要询问 $a_r=l$ 是否成立。

现在考虑一个 $[l,x]$ 的新线段。对于 $r \ge x$ 且 $a_r \le x+1$，都可以有 $a_r \leftarrow l$。

发现这个形式和区间取 $\min$ 非常像，所以可以直接上线段树势能，复杂度 $O(n \log^2 n)$。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
#define lson (k<<1)
#define rson (k<<1|1)
#define mid (l+r>>1)
using namespace std;
const int MAXN=5e5+10;
int n,m,q,ans[MAXN],tag[MAXN<<2];
vector<int> seg[MAXN];
vector<pair<int,int>> qr[MAXN];
struct INFO {int mn,smn;}t[MAXN<<2];
inline int calc(const int a,const int b,const int c,const int d) {if(a==b) return min(c,d);if(a<b) return min(b,c);return min(a,d);	}
INFO operator +(INFO A,INFO B) {return {min(A.mn,B.mn),calc(A.mn,B.mn,A.smn,B.smn)};}
void assign(int k,int tg) {
	tag[k]=tg,t[k].mn=tg;
	return ;
}
void push_down(int k,int l,int r) {
	if(tag[k]!=-1) {
		int flg1=0,flg2=0;
		if(t[lson].mn<=t[rson].mn) flg1=1;
		if(t[rson].mn<=t[lson].mn) flg2=1;
		if(flg1) assign(lson,tag[k]);
		if(flg2) assign(rson,tag[k]);
	}
	return tag[k]=-1,void();
}
void update(int k,int l,int r,int x,int y,int v,int nv) {
	if(t[k].mn>v) return ;
	if(x<=l&&r<=y) {
		if(t[k].smn>v) return assign(k,nv),void();
		push_down(k,l,r);
		update(lson,l,mid,x,y,v,nv);
		update(rson,mid+1,r,x,y,v,nv);
		return t[k]=t[lson]+t[rson],void();	
	}
	push_down(k,l,r);
	if(x<=mid) update(lson,l,mid,x,y,v,nv);
	if(y>mid) update(rson,mid+1,r,x,y,v,nv);
	return t[k]=t[lson]+t[rson],void();
}
void build(int k,int l,int r) {
	tag[k]=-1;
	if(l==r) return t[k]={l+1,n+100},void();
	build(lson,l,mid),build(rson,mid+1,r);
	return t[k]=t[lson]+t[rson],void();	
}
int query(int k,int l,int r,int pos) {
	if(l==r) return t[k].mn;
	push_down(k,l,r);
	if(pos<=mid) return query(lson,l,mid,pos);
	return query(rson,mid+1,r,pos);	
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m>>q;
	ffor(i,1,m) {
		int l,r;
		cin>>l>>r,seg[l].push_back(r);	
	}
	ffor(i,1,q) {
		int s,e;
		cin>>s>>e,qr[s].push_back({e,i});	
	}
	build(1,1,n);
	roff(i,n,1) {
		for(auto id:seg[i]) update(1,1,n,id,n,id+1,i);
		for(auto pr:qr[i]) if(query(1,1,n,pr.first)==i) ans[pr.second]=1;
	}
	ffor(i,1,q) if(ans[i]) cout<<"YES\n";
	else cout<<"NO\n";
	return 0;
}
```

---

## 作者：StayAlone (赞：6)

下文中对“线段”和“区间”不作区分。

查询区间 $[s, e]$ 时，显然会选择所有 $l_i\geq s\land r_i\leq e$ 的线段，只需判断它们是否填满区间。

显然离线，将给定区间和查询区间均按照右端点排序，只插入 $r_i\leq e$ 的区间，这样第二个条件就消掉了。

考虑在线段树上，第 $x$ 个叶子结点维护：使用 $l_i\geq x$ 的区间，最远能“紧凑地”拼到什么哪个位置，记为 $rpos_x$。即，$rpos_x$ 是最大的 $p$，满足 $[x, p]$ 被所选区间的并包含。

查询时，单点查 $rpos$ 即可。考虑区间修改。

插入线段 $[l, r]$，则是对 $x\in [1, l]$，且 $rpos_x\geq l - 1$ 的位置，做 $rpos_x\gets r$。乍一看很难做，但我们惊奇地发现，直接做懒标记就是可以合并的！

具体地，设懒标记 $|l, r|$ 表示，对区间内 $rpos_x\geq l - 1$ 的位置，做 $rpos_x\gets r$。

假设现有标记 $|l_1, r_1|$，要添加标记 $|l_2,r_2|$，考虑合并标记。注意，由于前面离线排序的存在，始终有 $r_2\geq r_1$。

- 若 $r_1\geq l_2 - 1$，分讨一下发现新标记就是 $|\min\{l_1, l_2\}, r_2|$。
- 否则，不更新标记。原因是由于标记 $|l_1,r_1|$ 的存在，区间中 $rpos_x\leq r_1$，那么此刻 $|l_2,r_2|$ 标记就不可能有效；又因为新的 $r_q\geq r_2$，不会存在需要 $|l_2,r_2|$ 为“桥梁”连接的标记。

时间复杂度 $\mathcal O(n+(m+q)\log n)$，简单操作一下应该能去掉 $n$。

[AC record](https://www.luogu.com.cn/record/197489166)

```cpp
int n, m, q, ans[MAXN];
vector <pii> seg;

struct node {
	int l, r, id;
	
	il bool operator < (const node &p) const {
		return r < p.r;
	}
} a[MAXN];

il pii operator + (pii &x, pii &y) {
	if (x.snd >= y.fst - 1) return mp(min(x.fst, y.fst), y.snd);
	return x;
}

il void operator += (pii &x, pii &y) {
	x = x + y;
}

struct setr {
	pii tag[MAXN << 2];
	
	il void pushdown(int x) {
		tag[ls(x)] += tag[x]; tag[rs(x)] += tag[x];
		tag[x] = {inf, inf};
	}
	
	il void build(int x, int l, int r) {
		tag[x] = {inf, inf};
		if (l == r) return tag[x] = {l - 1, l - 1}, void();
		int mid = l + r >> 1;
		build(ls(x), l, mid); build(rs(x), mid + 1, r);
	}
	
	il void upd(int x, int l, int r, int ql, int qr, pii tg) {
		if (l > qr || r < ql) return;
		if (l >= ql && r <= qr) return tag[x] += tg, void();
		int mid = l + r >> 1; pushdown(x);
		upd(ls(x), l, mid, ql, qr, tg); upd(rs(x), mid + 1, r, ql, qr, tg);
	}
	
	il int query(int x, int l, int r, int k) {
		if (l == r) return tag[x].snd;
		int mid = l + r >> 1; pushdown(x);
		return k <= mid ? query(ls(x), l, mid, k) : query(rs(x), mid + 1, r, k);
	}
} T;

int main() {
	read(n, m, q); int l, r;
	while (m--) read(l, r), seg.eb(l, r);
	sort(begin(seg), end(seg), [&](const pii &x, const pii &y) {return x.snd > y.snd;});
	rep1(i, 1, q) read(a[i].l, a[i].r), a[i].id = i;
	sort(a + 1, a + 1 + q); T.build(1, 1, n);
	rep1(i, 1, q) {
		while (seg.size() && seg.back().snd <= a[i].r) {
			auto [l, r] = seg.back(); seg.pop_back();
			T.upd(1, 1, n, 1, l, {l, r});
		} ans[a[i].id] = T.query(1, 1, n, a[i].l) >= a[i].r;
	}
	rep1(i, 1, q) puts(ans[i] ? "YES" : "NO");
	return 0;
}
```

---

## 作者：ddxrS_loves_zxr (赞：5)

考虑如何判断一个区间 $[s_j,e_j]$ 是否能够被并出来。

考虑对于每个位置 $x$ 维护一个值 $f_x$，表示满足 $l_i\le x\le r_i\le e_j$ 的区间 $[l_i,r_i]$ 中最大的 $l_i$。

那么显然，若 $s_j\le\min_{k=s_j}^{e_j}f_k$（实际上是等于），那么区间 $[s_j,e_j]$ 就可以被并出来。

于是考虑离线下来扫描线，枚举询问区间的右端点 $R$，每次加入 $r_i=R$ 的区间，将区间 $[l_i,r_i]$ 中的 $f$ 与 $l_i$ 取 max。每次询问只需要求区间 $[s_j,e_j]$ 中 $f$ 的最小值即可。

时间复杂度 $O(n+(m+q)\log n)$。

```cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 5e5 + 5;
int n, m, q, ans[N];
int tr[N << 2], tag[N << 2];
void pushdown(int p) {
    tr[p << 1] = max(tr[p << 1], tag[p]), tr[p << 1 | 1] = max(tr[p << 1 | 1], tag[p]);
    tag[p << 1] = max(tag[p << 1], tag[p]), tag[p << 1 | 1] = max(tag[p << 1 | 1], tag[p]);
    tag[p] = 0;
}
void change(int p, int l, int r, int ql, int qr, int x) {
    int mid = l + r >> 1;
    if(ql <= l && r <= qr) return tr[p] = max(tr[p], x), tag[p] = max(tag[p], x), void();
    pushdown(p);
    if(ql <= mid) change(p << 1, l, mid, ql, qr, x);
    if(mid < qr) change(p << 1 | 1, mid + 1, r, ql, qr, x);
    tr[p] = min(tr[p << 1], tr[p << 1 | 1]);
}
int query(int p, int l, int r, int ql, int qr) {
    int mid = l + r >> 1;
    if(ql <= l && r <= qr) return tr[p];
    pushdown(p);
    if(qr <= mid) return query(p << 1, l, mid, ql, qr);
    else if(mid < ql) return query(p << 1 | 1, mid + 1, r, ql, qr);
    else return min(query(p << 1, l, mid, ql, qr), query(p << 1 | 1, mid + 1, r, ql, qr));
}
vector<int> vec[N];
vector<pair<int, int> > que[N];
int main() {
#ifdef ddxrS
    freopen("sample.in", "r", stdin);
    freopen("sample.out", "w", stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin>>n>>m>>q;
    for(int i = 1, l, r; i <= m; i++) cin>>l>>r, vec[r].push_back(l);
    for(int i = 1, l, r; i <= q; i++) cin>>l>>r, que[r].push_back({l, i});
    for(int i = 1; i <= n; i++) {
        for(auto p : vec[i]) change(1, 1, n, p, i, p);
        for(auto p : que[i]) ans[p.second] = (query(1, 1, n, p.first, i) >= p.first);
    }
    for(int i = 1; i <= q; i++) cout<<(ans[i] ? "YES" : "NO")<<'\n';
    return 0;
}
```

---

## 作者：Reunite (赞：4)

学习了一下高妙的单 $\log$ 做法。

考虑扫描线，扫描右端点，考虑依次加入线段和询问。我们维护 $R_i$ 为使用 $l_x\ge i$ 的线段当前 $[i,R_i]$ 能被完全覆盖，那么询问只需要单点查询。考虑线段树，注意不需要信息可并性，只需要快速更新即可。

加入线段 $[l,r]$，对 $R_i$ 的影响即为对 $R_i\ge l-1$ 且 $i\le l_i$ 的 $i$，$R_i\leftarrow r$。考虑维护二元懒惰标记 $(lf,rt)$，表示要对区间内所有 $R_i\ge lf$ 的 $R_i\leftarrow rt$。现在问题在与合并懒惰标记，我们分情况讨论合并 $(lf,rt),(ll,rr)$：

- $rt\ge ll$ 此时显然可以直接合并，因为在第一个标记下传后 $R_i$ 一定合法，即变为 $(\min(lf,ll),rr)$。

- $rt<ll$ 此时一定不可以合并，因为中间会出现断层，那考虑被舍弃的 $(ll,rr)$ 后面会不会有用了，答案是否定的，因为这个断层一直存在，直到某一次后面重新满足 $rt\ge ll'$，但是因为 $r$ 的单调性以及线段树结构上祖先信息一定比子孙新，可以发现这个标记一定是不需要的。

然后就做完了，直接维护上述标记即可，注意初始化的一些细节。复杂度 $O((m+q)\log n)$。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

int n,m,q;
int ans[500005];
vector <int> g[500005];
vector <pair <int,int>> p[500005];

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

int lf[2000005];
int rt[2000005];

inline void down(int u,int l,int r){if(rt[u]>=l) lf[u]=min(lf[u],l),rt[u]=r;}

inline void pushdown(int u){
	down(u<<1,lf[u],rt[u]);
	down(u<<1|1,lf[u],rt[u]);
	lf[u]=rt[u]=1e9;
	return ;
}

inline void build(int u,int l,int r){
	lf[u]=rt[u]=1e9;
	if(l==r){lf[u]=rt[u]=l-1;return ;}
	int mid=(l+r)>>1;
	build(u<<1,l,mid);
	build(u<<1|1,mid+1,r);
	return ;
}

inline void upd(int u,int l,int r,int L,int R,int ll,int rr){
	if(L<=l&&r<=R){down(u,ll,rr);return ;}
	int mid=(l+r)>>1;
	pushdown(u);
	if(L<=mid) upd(u<<1,l,mid,L,R,ll,rr);
	if(R>mid) upd(u<<1|1,mid+1,r,L,R,ll,rr);
	return ;
}

inline int qry(int u,int l,int r,int k){
	if(l==r) return rt[u];
	int mid=(l+r)>>1;
	pushdown(u);
	if(k<=mid) return qry(u<<1,l,mid,k);
	else return qry(u<<1|1,mid+1,r,k);
}

int main(){
	in(n),in(m),in(q);
	for(int i=1;i<=m;i++){
		int l,r;
		in(l),in(r);
		g[r].emplace_back(l);
	}
	for(int i=1;i<=q;i++){
		int l,r;
		in(l),in(r);
		p[r].push_back({l,i});
	}
	build(1,1,n);
	for(int i=1;i<=n;i++){
		for(int l:g[i]) upd(1,1,n,1,l,l-1,i);
		for(auto tmp:p[i]) ans[tmp.second]=(qry(1,1,n,tmp.first)==i);
	}
	for(int i=1;i<=q;i++) puts(ans[i]?"YES":"NO");

	return 0;
}
```

---

## 作者：Zelotz (赞：2)

扫描线，对于一个右端点 $e$，考虑判断区间 $[s,e]$ 是否合法。

先把所有幕布右端点 $r\le e$ 的幕布都加入。 

若存在一组幕布子集，其并集恰好等于 $[s,e]$，则：

- **完全覆盖**：任意 $x\in[s,e]$，都被选中幕布中的至少一个区间覆盖。
-  **不越界**：所选的每个幕布 $[l_i,r_i]$ 都必须满足 $s\le l_i\le r_i\le e$，否则会“多遮”到 $[s,e]$ 之外。  

容易发现，满足这两个条件的幕布子集能覆盖区间 $[s,e]$ 是充分且必要的。

对于每个点 $x$ 维护覆盖它的线段中最靠右的左端点 $f_x$，即 满足 $l_i\le x \le r_i$ 中最大的 $l_i$。其初始值为 $0$。

对于询问 $[s,e]$，只要对于所有 $x\in [s,e]$，都有 $f_x \ge s$ 则满足了**不越界**，都有 $f_x \neq 0$ 则满足了**完全覆盖**，所以只需要满足 $\min_{x=s}^e f_x \ge s$ 即可。而此时的幕布子集恰好覆盖了 $[s,e]$，所以实际上 $\min_{x=s}^e f_x = s$。

```
const int N = 5e5 + 5;
int n, m, q;
int tag[N << 2], tr[N << 2];
#define ls (id << 1)
#define rs (id << 1 | 1)
#define mid (l + r >> 1)
void pd(int id) {
    tag[ls] = max(tag[ls], tag[id]);
    tag[rs] = max(tag[rs], tag[id]);
    tr[ls] = max(tr[ls], tag[id]);
    tr[rs] = max(tr[rs], tag[id]);
    tag[id] = 0;
}
void mdf(int l, int r, int x, int y, int k, int id) {
    if (l > y || r < x) return ;
    if (l >= x && r <= y) {
        tag[id] = max(tag[id], k);
        tr[id] = max(tr[id], k);
        return ;
    }
    pd(id);
    mdf(l, mid, x, y, k, ls), mdf(mid + 1, r, x, y, k, rs);
    tr[id] = min(tr[ls], tr[rs]);
}
int qry(int l, int r, int x, int y, int id) {
    if (l > y || r < x) return 2e9;
    if (l >= x && r <= y) return tr[id];
    pd(id);
    return min(qry(l, mid, x, y, ls), qry(mid + 1, r, x, y, rs));
}
vector<int> add[N];
vector<PII> ask[N];
bool ans[N];
signed main() {
    cin >> n >> m >> q;
    R(i, 1, m) {
        int l, r; cin >> l >> r;
        add[r].push_back(l);
    }
    R(i, 1, q) {
        int l, r; cin >> l >> r;
        ask[r].push_back({l, i});
    }
    R(i, 1, n) {
        for (int l : add[i]) {
            mdf(1, n, l, i, l, 1);
        }
        for (auto [l, id] : ask[i]) {
            int r = qry(1, n, l, i, 1);
            if (l == r) {
                ans[id] = 1;
            } 
        }
    }
    R(i, 1, q) {
        cout << (ans[i] ? "YES" : "NO") << '\n';
    }
    return 0;
}
```

---

## 作者：ax_by_c (赞：2)

NOI 模拟赛 T1，用时约 40min。

下文称 $L=s,R=e$。

考虑一个暴力：一开始 $p=L-1$，每次 $p\rightarrow \max_{l\le p+1,r\le R} r$，最后判断 $p=R$。

观察这个算法，考虑对右端点扫描线，就不用管 $r\le R$ 的限制了。

考虑对每个 $L$ 记录最后的 $p$，记为 $a_L$。

那么 $[l,r]$ 相当于对 $1\le i\le l,l-1\le a_i$ 执行 $a_i\leftarrow\max(a_i,r)$。

找不到什么好的性质了，所以考虑直接用数据结构解决。相当于每次给前缀中 $\ge x$ 的数与 $y$ 取 max，保证 $x<y$，$y$ 不降。

由于 $y$ 不降所以可以直接看成赋值。考虑类似 beats 的东西，线段树每个节点维护区间最大值，次大值和最大值赋值标记。每次暴力递归到只有最大值 $\ge x$，然后打标记即可。

但是萌新真的没学过 beats 不会算复杂度，只知道 2log 顶天了。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace ax_by_c{
typedef pair<int,int> pii;
const int N=5e5+5;
int n,m,q;
vector<int>ls[N];
vector<pii>qs[N];
bool ans[N];
struct DS1{
    struct node{
        int mx,se,tag;
    }tr[N*4];
    void pu(int u){
        tr[u].mx=max(tr[u<<1].mx,tr[u<<1|1].mx);
        tr[u].se=-1;
        if(tr[u<<1].mx!=tr[u].mx)tr[u].se=max(tr[u].se,tr[u<<1].mx);
        else tr[u].se=max(tr[u].se,tr[u<<1].se);
        if(tr[u<<1|1].mx!=tr[u].mx)tr[u].se=max(tr[u].se,tr[u<<1|1].mx);
        else tr[u].se=max(tr[u].se,tr[u<<1|1].se);
    }
    void pd_(int u,int x){
        if(x==-1)return ;
        tr[u].mx=x;
        tr[u].tag=x;
    }
    void pd(int u){
        bool x1=0,x2=0;
        if(tr[u<<1].mx>=tr[u<<1|1].mx)x1=1;
        if(tr[u<<1|1].mx>=tr[u<<1].mx)x2=1;
        if(x1)pd_(u<<1,tr[u].tag);
        if(x2)pd_(u<<1|1,tr[u].tag);
        tr[u].tag=-1;
    }
    void bld(int u,int l,int r){
        tr[u].tag=-1;
        if(l==r){
            tr[u].mx=l-1;
            tr[u].se=-1;
            return ;
        }
        int mid=l+((r-l)>>1);
        bld(u<<1,l,mid);
        bld(u<<1|1,mid+1,r);
        pu(u);
    }
    void upd(int u,int l,int r,int ql,int qr,int x,int y){
        if(ql<=l&&r<=qr){
            if(tr[u].mx<x)return ;
            if(tr[u].se<x){
                pd_(u,y);
                return ;
            }
            pd(u);
            int mid=l+((r-l)>>1);
            upd(u<<1,l,mid,ql,qr,x,y);
            upd(u<<1|1,mid+1,r,ql,qr,x,y);
            pu(u);
            return ;
        }
        pd(u);
        int mid=l+((r-l)>>1);
        if(ql<=mid)upd(u<<1,l,mid,ql,qr,x,y);
        if(mid+1<=qr)upd(u<<1|1,mid+1,r,ql,qr,x,y);
        pu(u);
    }
    int Q(int u,int l,int r,int p){
        if(l==r)return tr[u].mx;
        pd(u);
        int mid=l+((r-l)>>1);
        if(p<=mid)return Q(u<<1,l,mid,p);
        else return Q(u<<1|1,mid+1,r,p);
    }
}tr;
void main(){
    scanf("%d %d %d",&n,&m,&q);
    for(int i=1,l,r;i<=m;i++){
        scanf("%d %d",&l,&r);
        ls[r].push_back(l);
    }
    for(int i=1,l,r;i<=q;i++){
        scanf("%d %d",&l,&r);
        qs[r].push_back({l,i});
    }
    tr.bld(1,1,n);
    for(int r=1;r<=n;r++){
        for(auto l:ls[r])tr.upd(1,1,n,1,l,l-1,r);
        for(auto it:qs[r])if(tr.Q(1,1,n,it.first)==r)ans[it.second]=1;
    }
    for(int i=1;i<=q;i++){
        if(ans[i])puts("YES");
        else puts("NO");
    }
}
}
int main(){
    ax_by_c::main();
    return 0;
}
```

---

## 作者：_Mortis_ (赞：1)

[P11536 [NOISG 2023 Finals] Curtains](https://www.luogu.com.cn/problem/P11536)

首先想到离线，将询问按 $ e $ 排序。

处理到某个 $ e_i $ 时只加入 $ r_j \le e_i $ 的区间。

能将 $ [s_i,e_i] $ 恰好覆盖的充要条件是区间内每个数都能被某个 $ [l_j,r_j] $ 覆盖，且其中所有 $ l_j $ 满足 $ l_j \ge s_i $。

令 $ f_x = \max \limits _{l_j \le x \le r_j \le e_i} \{ l_j \}$，则当且仅当 $ \min \limits _{s_i \le x \le e_i} {f_x} = s_i $ 时，能将 $ [s_i,e_i] $ 恰好覆盖。

加入区间 $ [l_j,r_j] $ 时，将 $ [l_j,r_j] $ 中的所有 $ f $ 与 $ l_j $ 取最大值。用线段树维护。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=5e5+10;
struct node{
	int l,r,lz,Min;
}T[N<<2];
struct Q{
	int s,id;
};
void push_up(int p){
	T[p].Min=min(T[p<<1].Min,T[p<<1|1].Min);
}
void build(int p,int l,int r){
	T[p].l=l,T[p].r=r;
	if(l==r)return;
	int mid=l+r>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
}
void push_down(int p){
	T[p<<1].lz=max(T[p<<1].lz,T[p].lz);
	T[p<<1|1].lz=max(T[p<<1|1].lz,T[p].lz);
	T[p<<1].Min=max(T[p<<1].Min,T[p].lz);
	T[p<<1|1].Min=max(T[p<<1|1].Min,T[p].lz);
	T[p].lz=0;
}
void update(int p,int l,int r,int v){
	if(T[p].r<l||T[p].l>r)return;
	if(l<=T[p].l&&T[p].r<=r){
		T[p].Min=max(T[p].Min,v);
		T[p].lz=max(T[p].lz,v);
		return ;
	}
	push_down(p);
	update(p<<1,l,r,v);
	update(p<<1|1,l,r,v);
	push_up(p);
}
int query(int p,int l,int r){
	if(T[p].r<l||T[p].l>r)return 0x3f3f3f3f;
	if(l<=T[p].l&&T[p].r<=r)return T[p].Min;
	return min(query(p<<1,l,r),query(p<<1|1,l,r));
}
int n,m,q;
bool ans[N];
vector<int>L[N];
vector<Q>qry[N];
int main(){
	scanf("%d%d%d",&n,&m,&q);
	for(int l,r;m--;){
		scanf("%d%d",&l,&r);
		L[r].push_back(l);
	}
	for(int s,e,i=1;i<=q;i++){
		scanf("%d%d",&s,&e);
		qry[e].push_back(Q{s,i});
	}
	build(1,1,n);
	for(int i=1;i<=n;i++){
		for(int l:L[i])update(1,l,i,l);
		for(Q x:qry[i])ans[x.id]=(query(1,x.s,i)==x.s);
	}
	for(int i=1;i<=q;i++)puts(ans[i]?"YES":"NO");
	return 0;
}
```

---

## 作者：XZhuRen (赞：0)

首先容易想到扫描线。

询问对于当前点做左端点，有哪些点做右端点是合理合法的。

由于只有单点查询，所以每个标记都可以下传到底。

发现在右端点新加一条线段 $[l,r]$ 的结果为：

还可以取到版本在 $[l-1,r)$ 内所有版本答案在区间 $[1,l)$ 上的并。

反向思维：

维护每个点最后在哪个版本被取到。

则：维护 $\max$ 代表这个点当前可以完美覆盖的最右点 $R$（初始为 $i-1$）。

每次对 $[1,l)$ 部分，$R\le (l-1)$ 的 $R$ 全修改成 $i$。

由于不存在什么维护的信息，所以维护标记就行了。

这里维护 $\max$ 只是为了方便查询。

Code：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
//首先容易想到扫描线。
//询问对于当前点做左端点，有哪些点做右端点是合理合法的。
//由于只有单点查询，所以每个标记都可以下传到底。
//发现在右端点新加一条线段[l,r]的结果为：
//还可以取到版本在[l-1,r)内所有版本答案在区间[1,l)上的并。
//反向思维：
//维护每个点最后在哪个版本被取到
//则：
//维护max代表这个点当前可以完美覆盖的最右点R（初始为i-1）
//每次对(1-(l-1))部分，>=l-1的R全干成i
//由于不存在什么维护的信息，所以维护标记就行了
//这里维护max只是为了方便查询
#define mkp make_pair
struct Node{
	int l,r;
	int max;
	bool istg=0;
	pair<int,int>tag;
}t[N*4];
#define ls (o<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
void ontag(int o,pair<int,int>tg){
	if(t[o].max<tg.first){t[o].istg=0;return;}//打不了
	t[o].max=tg.second;t[o].tag=tg;t[o].istg=1;
}
void update(int o,pair<int,int>tg){
	if(!t[o].istg){ontag(o,tg);return;}//打标记
	if(tg.first<=t[o].tag.second)ontag(o,t[o].tag=mkp(min(tg.first,t[o].tag.first),tg.second));//合并标记
}
void pushdown(int o){
	if(!t[o].istg)return;
	update(ls,t[o].tag);
	update(rs,t[o].tag);
	t[o].istg=0;//删除这个sb标记
}
void pushup(int o){t[o].max=max(t[ls].max,t[rs].max);}
void build(int o,int l,int r){
	t[o]=(Node){l,r,(r-1),0};
	if(l==r)return;
	build(ls,l,mid),build(rs,mid+1,r);
}
void mdf(int o,int lt,int rt,pair<int,int>tg){
	int l=t[o].l,r=t[o].r;
	if(l>=lt&&r<=rt){update(o,tg);return;}
	pushdown(o);
	if(lt<=mid)mdf(ls,lt,rt,tg);
	if(rt>mid)mdf(rs,lt,rt,tg);
	pushup(o);
}
bool query(int o,int pos,int RT){
	int l=t[o].l,r=t[o].r;
	if(l==r)return t[o].max==RT;
	pushdown(o);
	return query(pos<=mid?ls:rs,pos,RT);
	pushup(o);
}
struct Seg{
	int l,r;
	int id;//id==0：加线段
};
vector<Seg>qs[N];
int n,m,q;
void init(){
	scanf("%d%d%d",&n,&m,&q);
	int l,r;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&l,&r);
		qs[r].push_back((Seg){l,r,0});
	}
	for(int i=1;i<=q;i++){
		scanf("%d%d",&l,&r);
		qs[r].push_back((Seg){l,r,i});
	}
}
bool Ans[N];
void work(){
	build(1,1,n);
	for(int i=1;i<=n;i++){
		for(auto s:qs[i]){
			if(!s.id){
				mdf(1,1,s.l,mkp(s.l-1,i));
			}else{
				Ans[s.id]=query(1,s.l,i);
			}
		}
	}
	for(int i=1;i<=q;i++){
		Ans[i]?printf("YES\n"):printf("NO\n");
	}
}
int main(){
	init();
	work();
	return 0;
}
```

---

