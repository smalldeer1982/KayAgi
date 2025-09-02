# Place Your Ad Here

## 题目描述

有 $n$ 个广告和 $m$ 个电视台，第 $i$ 个广告只能在时间段 $\left[l_i,r_i\right]$ 播放，第 $j$ 个电视台会在时间段 $\left[a_j,b_j\right]$ 播出，并且有 $c_j$ 个人收看。

选择第 $x$ 个广告和第 $y$ 个电视台的收益为 $\left(v-u\right)\times c_y$，其中 $\left[u,v\right]$ 为 $\left[l_x,r_x\right]$ 和 $\left[a_y,b_y\right]$ 的交集。

求最大收益。

## 样例 #1

### 输入

```
2 3
7 9
1 4
2 8 2
0 4 1
8 9 3
```

### 输出

```
4
2 1
```

## 样例 #2

### 输入

```
1 1
0 0
1 1 10
```

### 输出

```
0
```

# 题解

## 作者：Tony102 (赞：3)

[Link](https://www.luogu.com.cn/problem/CF542A)

[My Blog](https://tony102.com/archives/125/)


## Description

给定 $n$ 个区间（第一类区间）和另外 $m$ 个区间（第二类区间）（这 $m$ 个区间每个单位长度有一个权值 $c_i$），现在要在 $n$ 个区间和 $m$ 个区间中各选一个区间，使得选出来的第一个区间和选出来的第二个区间的交乘以第二个区间的 $c_i$ 最大。

注意，假如选出来的第一个区间是 $[l, r]$，第二个区间是 $[x, y]$ 且 $[l,r] \cap [x,y] \neq \emptyset$，若交的部分为 $[a, b]$ ，则这一段的贡献为 $(b-a) \times c_i$

## Sol

首先可以想到对第一类区间按照左端点为第一关键字升序排序，若第一关键字相等则按照以右端点为第二关键字降序排序。

加入一个区间被另一个区间完全包含，则该区间显然可以略过。

对于每一个第一类区间 $[l_i, r_i]$ ，我们可以通过两次二分查出：1. 左端点 $\geq l_i$ 的区间 2. 右端点 $\leq r_i$ 的区间。从这两类区间中分别二分出在边界的那个第二类区间，与答案取 $\max$

但是注意到，存在一种情况，当前这个区间可能完全被某一个第二类区间包含，这个时候我们只需要把所有的第一类区间插入进一棵线段树，只需要找出左右端点在范围内的最大区间长度即可。

要输出第一类和第二类区间的编号，线段树要记录取最长的区间的编号。稍微注意一下即可。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair < LL, int > PLI;
const int SIZE = 3e5 + 5;

int n, m, N;

struct node {
    int l, r, c, idx;
    bool operator < (const node &a) const {
        return l == a.l ? r > a.r : l < a.l;
    }
    LL operator & (const node &a) const {
        if (l <= a.l && r >= a.r) return a.r - a.l;
        if (l >= a.l && r <= a.r) return r - l;
        return std::max(0, std::min(r, a.r) - std::max(l, a.l));
    }
} a[SIZE], b[SIZE], c[SIZE];

namespace GTR {
	const int bufl = 1 << 15;
	char buf[bufl], *s = buf, *t = buf;
	inline int fetch() {
		if (s == t) { t = (s = buf) + fread(buf, 1, bufl, stdin); if (s == t) return EOF; }
		return *s++;
	}
	inline int read() {
		int a = 0, b = 1, c = fetch();
		while (c < 48 || c > 57) b ^= c == '-', c = fetch();
		while (c >= 48 && c <= 57) a = (a << 1) + (a << 3) + c - 48, c = fetch();
		return b ? a : -a;
	}
} using GTR::read;

namespace segmentTree {
    PLI len[SIZE << 2];
    #define lson(p) (p << 1)
    #define rson(p) (p << 1 | 1)
    
    void pushUp(int p) {
        PLI ans = len[lson(p)];
        if (len[rson(p)].second > ans.second) ans = len[rson(p)];
        len[p] = ans;
    }

    void build(int p, int l, int r) {
        if (l == r) return len[p] = (PLI) {a[l].idx, 1ll * a[l].r - a[l].l}, void();
        int mid = (l + r) / 2;
        build(lson(p), l, mid), build(rson(p), mid + 1, r);
        pushUp(p);
    }
    PLI query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return len[p];
        int mid = (l + r) >> 1; PLI ans = (PLI) {0, 0};
        if (ql <= mid) {
            PLI res = query(lson(p), l, mid, ql, qr);
            if (res.second > ans.second) ans = res;
        }
        if (qr > mid) {
            PLI res = query(rson(p), mid + 1, r, ql, qr);
            if (res.second > ans.second) ans = res;
        }
        return ans;
    }
} using segmentTree::build; using segmentTree::query;

int main() {
    // freopen("code.in", "r", stdin);
    n = read(), m = read();
    for (int i = 1; i <= n; ++ i) c[i].l = read(), c[i].r = read(), c[i].idx = i;
    for (int i = 1; i <= m; ++ i) b[i].l = read(), b[i].r = read(), b[i].c = read();
    std::sort(c + 1, c + n + 1);
    for (int i = 1; i <= n; ++ i) a[i] = c[i];
    N = 1;
    for (int i = 2; i <= n; ++ i) {
        if (a[i].r > a[N].r) a[++ N] = a[i];
    }
    build(1, 1, N); LL ans = -1e18; int ansl = 0, ansr = 0;
    for (int i = 1; i <= m; ++ i) {
        int l = 1, r = N, mid;
        while (l < r) {
            mid = (l + r) / 2;
            if (l == mid) break;
            if (a[mid].l < b[i].l) l = mid;
            else r = mid;
        }
        LL res = 1ll * (b[i] & a[l]) * b[i].c;
        if (ans < res) ans = res, ansl = a[l].idx, ansr = i;
        // ans = std::max(ans, 1ll * (b[i] & a[l]) * b[i].c);
        int L = l + 1, R; l = 1, r = N, mid;
        while (l < r) {
            mid = (l + r) / 2;
            if (a[mid].r > b[i].r) r = mid;
            else l = mid + 1;
        }
        R = r - 1;
        res = 1ll * (b[i] & a[r]) * b[i].c;
        if (ans < res) ans = res, ansl = a[r].idx, ansr = i;
        if (R >= L) {
            PLI tmp = query(1, 1, N, L, R);
            res = 1ll * tmp.second * b[i].c;
            if (ans < res) ans = res, ansl = tmp.first, ansr = i;
        }
    }
    if (ans <= 0) puts("0");
    else printf("%lld\n%d %d\n", ans, ansl, ansr);
    return 0;
}
```


---

## 作者：WaterSun (赞：2)

[更好的阅读体验](https://www.cnblogs.com/WaterSun/p/18413114)

# 思路

首先因为电视台比广告多一个信息，所以通常来说枚举电视台是更有前途的。

因此枚举每一个电视台，考虑所有广告的贡献。对于一个电视台，$c_i$ 是定值，也就是找到所有广告与电视台所表示区间交得最多的那一个。

假设枚举的电视台控制了 $[L,R]$ 区间，则广告 $[l,r]$ 会有三种方式对 $[L,R]$ 有交：

1. $L \leq l \leq r \leq R$。
2. $l \leq L \leq r \leq R$。
3. $L \leq l \leq R \leq r$。

特别的，在这里我们把 $l \leq L \leq R \leq r$ 归于第二种或者第三种均可。

对于第二、三种情况太平凡了。定义 $Min_i$ 表示所有右端点为 $i$ 的广告最左的左端点的位置；$Max_i$ 表示所有左端点为 $i$ 的广告最右的右端点位置。

第二种情况，因为 $l \leq L$ 我们只关心右端点能最远拓展到哪里，因此查询 $[1,L - 1]$ 区间 $Max_i$ 的最大值；第三种情况同理，查询 $[R + 1,n]$ 区间 $Min_i$ 的最小值。

第一种情况比较复杂。由于广告被电视台完全包含，因此我们只需要关心广告能取到的最长的长度。

不妨将电视台右端点从大到小排序，好处是可以每一次将右端点超出区间的广告直接弹出集合。然后发现现在在集合中的广告只有左端点的限制了，直接上线段树即可。

对于二三两种情况，维护最值可以用线段树，也可以用 ST 表但是空间上要精细实现。

代码细节较多。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define fst first
#define snd second
#define ll long long
#define chmin(a,b) (a = min(a,b))
#define chmax(a,b) (a = max(a,b))

using namespace std;

typedef pair<int,int> pii;
const int N = 8e5 + 10,inf = 1e9 + 10;
int n,m,lg[N];
ll ans; int id1,id2;
pii arr[N],Min[N],Max[N];
vector<int> pt;
vector<pii> str[N];
set<pii> stl[N];

struct sec{
    int l,r,k,id;
}Q[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

struct seg{
    #define ls(u) (u << 1)
    #define rs(u) (u << 1 | 1)

    struct node{
        int l,r;
        pii Min,Max;
    }tr[N << 2];

    inline void calc(int u,int x){
        if (stl[x].empty()) tr[u].Max = {-inf,-inf};
        else{
            pii it = *prev(stl[x].end());
            tr[u].Max = {pt[it.fst - 1] - pt[x - 1],it.snd};
        }
    }

    inline void pushup(int u){
        tr[u].Min = min(tr[ls(u)].Min,tr[rs(u)].Min);
        tr[u].Max = max(tr[ls(u)].Max,tr[rs(u)].Max);
    }

    inline void build(int u,int l,int r,int op){
        tr[u] = {l,r,{inf,inf},{-inf,-inf}};
        if (l == r){
            if (!op) calc(u,l);
            else{
                tr[u].Min = Min[l]; tr[u].Max = Max[l];
            }
            return;
        }
        int mid = l + r >> 1;
        build(ls(u),l,mid,op); build(rs(u),mid + 1,r,op);
        pushup(u);
    }

    inline void modify(int u,int x){
        if (tr[u].l == tr[u].r) return calc(u,x);
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid) modify(ls(u),x);
        else modify(rs(u),x);
        pushup(u);
    }

    inline pii querymax(int u,int l,int r){
        if (l <= tr[u].l && tr[u].r <= r) return tr[u].Max;
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid && r > mid) return max(querymax(ls(u),l,r),querymax(rs(u),l,r));
        else if (l <= mid) return querymax(ls(u),l,r);
        else return querymax(rs(u),l,r);
    }

    inline pii querymin(int u,int l,int r){
        if (l <= tr[u].l && tr[u].r <= r) return tr[u].Min;
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid && r > mid) return min(querymin(ls(u),l,r),querymin(rs(u),l,r));
        else if (l <= mid) return querymin(ls(u),l,r);
        else return querymin(rs(u),l,r);
    }

    #undef ls
    #undef rs
}VT,ST;

#define find(x) (lower_bound(pt.begin(),pt.end(),x) - pt.begin() + 1)

inline void del(int x){
    for (auto it:str[x]){
        stl[it.fst].erase({x,it.snd});
        ST.modify(1,it.fst);
    }
}

signed main(){
    n = read(),m = read();
    for (re int i = 1,l,r;i <= n;i++){
        l = read(),r = read();
        arr[i] = {l,r};
        pt.push_back(l); pt.push_back(r);
    }
    for (re int i = 1,l,r,k;i <= m;i++){
        l = read(),r = read(),k = read();
        Q[i] = {l,r,k,i};
        pt.push_back(l); pt.push_back(r);
    }
    sort(pt.begin(),pt.end());
    pt.erase(unique(pt.begin(),pt.end()),pt.end());
    const int sz = pt.size();
    fill(Max + 1,Max + sz + 1,make_pair(-inf,-inf));
    fill(Min + 1,Min + sz + 1,make_pair(inf,inf));
    for (re int i = 2;i <= sz;i++) lg[i] = lg[i >> 1] + 1;
    for (re int i = 1;i <= n;i++) arr[i] = {find(arr[i].fst),find(arr[i].snd)};
    for (re int i = 1;i <= m;i++) Q[i] = {find(Q[i].l),find(Q[i].r),Q[i].k,Q[i].id};
    for (re int i = 1;i <= n;i++){
        stl[arr[i].fst].insert({arr[i].snd,i});
        str[arr[i].snd].push_back({arr[i].fst,i});
        chmax(Max[arr[i].fst],make_pair(arr[i].snd,i));
        chmin(Min[arr[i].snd],make_pair(arr[i].fst,i));
    }
    VT.build(1,1,sz,1); ST.build(1,1,sz,0);
    sort(Q + 1,Q + m + 1,[](const sec &a,const sec &b){
        return a.r > b.r;
    });
    for (re int i = Q[1].r + 1;i <= sz;i++) del(i);
    for (re int i = 1;i <= m;i++){
        pii tmpl = {-inf,-inf},tmpr = {-inf,-inf};
        if (Q[i].l > 1){
            pii L = VT.querymax(1,1,Q[i].l - 1);
            if (L.fst >= Q[i].l){
                chmin(L.fst,Q[i].r);
                int len = pt[L.fst - 1] - pt[Q[i].l - 1];
                tmpl = {len,L.snd};
            }
        }
        if (Q[i].r < sz){
            pii R = VT.querymin(1,Q[i].r + 1,sz);
            if (R.fst <= Q[i].r){
                chmax(R.fst,Q[i].l);
                int len = pt[Q[i].r - 1] - pt[R.fst - 1];
                tmpr = {len,R.snd};
            }
        }
        pii tmp = max({tmpl,tmpr,ST.querymax(1,Q[i].l,Q[i].r)});
        if (tmp.fst > 0){
            ll res = 1ll * tmp.fst * Q[i].k;
            if (ans < res){
                ans = res;
                id1 = tmp.snd; id2 = Q[i].id;
            }
        }
        for (re int j = Q[i + 1].r + 1;j <= Q[i].r;j++) del(j);
    }
    printf("%lld\n",ans);
    if (ans) printf("%d %d",id1,id2);
    return 0;
}
```

---

## 作者：qinhuanmma (赞：2)

这种最值问题，一般都是定一求一，即枚举一维，剩下的维度用数据结构维护。  
这里显然不能枚举广告那一维，因为电视台这边还带个权值，难以维护，因此将相对复杂的信息交给 `for` 循环，枚举每个电视台，问题转化为求 **与给定区间** $[bl,br]$ **交集最大的区间** $[al,ar]$。
直接做不是很好做，考虑分类讨论：  
1. $ar_i \ge br$，对于这类广告区间，不难看出交集区间右端点一定为 $br$，因此贡献为 $br-\max(bl,\min\limits_{ar_i \ge br}(al_i))$，将 $a$，$b$ 分别按 $r$ 排序，维护一个后缀 $al$ 最小值即可。用双指针倒着扫一遍可以做到 $O(n)$。  
2. $ar_i<br,al_i \ge bl$，对于这类广告区间，贡献即为区间长度。由于已经按 $r$ 排序并双指针了，扫到当前的 $[bl,br]$ 时只记录了$ar_i<br$ 的区间的信息，因此只用考虑 $al_i>bl$ 这一个限制，用一个区间 $\text{ckmax}$，单点查值的线段树维护即可。
3. $ar_i<br,al_i<bl$，对于这类广告区间，交集的左端点一定是 $bl$，类比情况一，对 $l$ 排序正着做一遍双指针即可。  

时间复杂度：$O(n\log n)$，常数较小（？）。  
注意题目中的区间长度不是 $r-l+1$ 而是 $r-l$。  
code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 200010, INF = 1e9 + 10;
namespace cza{
	int n, m;
	int root;
	struct range{
		int l, r, c, id;
		bool friend operator < (const range &a, const range &b){
			return a. r < b. r;
		}
	}a[N], b[N];
	bool cmp(range a, range b){
		return a. l < b. l;
	}
	long long ans = 0;
	struct node{
		int ls, rs, maxx;
	};
	struct Segment_Tree{
		node t[N * 40];
		int tcnt;
		void upd(int &p, int l, int r, int nl, int nr, int v){
			if(nr < nl) return ;
			if(!p) p = ++tcnt, t[p]. maxx = -INF, t[p]. ls = 0, t[p]. rs = 0;
			if(nl <= l and r <= nr){
				t[p]. maxx = max(t[p]. maxx, v);
				return ;
			}
			int mid = (l + r) >> 1;
			if(nl <= mid) upd(t[p]. ls, l, mid, nl, nr, v);
			if(mid < nr) upd(t[p]. rs, mid + 1, r, nl, nr, v);
		}
		int find(int p, int l, int r, int x, int ret){
			if(!p) return ret;
			ret = max(ret, t[p]. maxx);
			if(l == r) return ret;
			int mid = (l + r) >> 1;
			if(x <= mid) return find(t[p]. ls, l, mid, x, ret);
			else return find(t[p]. rs, mid + 1, r, x, ret);
		}
	}t;
	int main(){
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++){
			scanf("%d%d", &a[i]. l, &a[i]. r); 
			a[i]. l++, a[i]. r++;
			a[i]. id = i;
		}
		for(int i = 1; i <= m; i++){
			scanf("%d%d%d", &b[i]. l, &b[i]. r, &b[i]. c);
			b[i]. l++, b[i]. r++;
			b[i]. id = i;
		}
		sort(a + 1, a + 1 + n);
		sort(b + 1, b + 1 + m);
		int pos = n;
		int minl = INF;
		int bestb = -1;
		for(int i = m; i >= 1; i--){
			while(pos and a[pos]. r >= b[i]. r){
				minl = min(a[pos]. l, minl);
				pos--;
			}
			long long ck = 1ll * b[i]. c * (b[i]. r - max(b[i]. l, minl));
			if(ck > ans){
				ans = ck;
				bestb = b[i]. id;
			}
		}//情况一 
		pos = 1;
		for(int i = 1; i <= m; i++){
			while(pos <= n and a[pos]. r < b[i]. r){
				t. upd(root, 1, INF, 1, a[pos]. l - 1, a[pos]. r - a[pos]. l);
				pos++;
			}
			long long ck = 1ll * b[i]. c * t. find(root, 1, INF, b[i]. l, -INF);
			if(ck > ans){
				ans = ck;
				bestb = b[i]. id;
			}
		}//情况二 
		pos = 1;
		sort(a + 1, a + 1 + n, cmp);
		sort(b + 1, b + 1 + m, cmp);
		int maxr = -1;
		for(int i = 1; i <= m; i++){
			while(pos <= n and a[pos]. l < b[i]. l){
				maxr = max(a[pos]. r, maxr);
				pos++;
			}
			long long ck = 1ll * b[i]. c * (min(maxr, b[i]. r) - b[i]. l);
			if(ck > ans){
				ans = ck;
				bestb = b[i]. id;
			}
		}//情况三 
		printf("%lld\n", ans);
		if(!ans) return 0;
		for(int i = 1; i <= m; i++){
			if(b[i]. id == bestb){
				bestb = i;
				break;
			}
		} 
		ans /= b[bestb]. c;
		int besta = -1;
		for(int i = 1; i <= n; i++){
			if((min(a[i]. r, b[bestb]. r) - max(a[i]. l, b[bestb]. l)) == ans){
				besta = a[i]. id;
			}
		}
		printf("%d %d", besta, b[bestb]. id); //为什么还要输出方案啊qwq 
		return 0;
	}
}
signed main(){
	return cza::main();
}
```

---

## 作者：skylee (赞：2)

# [CF542A]Place Your Ad Here
## 题目大意：
有$n(n\le2\times10^5)$个广告和$m(m\le2\times10^5)$个电视台，第$i$个广告只能在$[l_i,r_i]$内播放，第$j$个电视台会在时间段$[a_j,b_j]$播出，并且有$c_j$个人收看。选择第$x$个广告和第$y$个电视台的收益为$(v-u)c_y$，其中$[u,v]=[l_x,r_x]\cap[a_y,b_y]$。

从中选取一个广告和一个电视台，使收益最大。求最大收益，并输出任意一种方案。

## 思路：
将广告拆成两个端点排序，将电视台按照右端点排序。

枚举每个电视台$[l,r]$，若一个广告只有左端点在$r$前，那么我们只关心最左的左端点；若一个广告左右端点均在$[l,r]$内，那么我们只关心其长度；若一个广告左端点在$l$前，右端点在$[l,r]$内，那么我们只关心其右端点的位置。

对于第一种情况，用`set`维护即可；后两种情况只需用线段树维护区间最大值。

时间复杂度$\mathcal O(n\log n)$。

## 源代码：
```cpp
#include<set>
#include<cstdio>
#include<cctype>
#include<algorithm>
inline int getint() {
	register char ch;
	while(!isdigit(ch=getchar()));
	register int x=ch^'0';
	while(isdigit(ch=getchar())) x=(((x<<2)+x)<<1)+(ch^'0');
	return x;
}
typedef long long int64;
struct Node {
	int p,id;
	bool operator < (const Node &rhs) const {
		return p<rhs.p;
	}
};
struct Seg {
	int l,r,w,id;
	bool operator < (const Seg &rhs) const {
		return r<rhs.r;
	}
};
const int N=2e5+1,K=8e5+1;
Node a[N],b[N];
Seg c[N];
int rnk[N],tmp[K];
class SegmentTree {
	#define _left <<1
	#define _right <<1|1
	#define mid ((b+e)>>1)
	private:
		std::pair<int,int> val[K<<2];
		void push_up(const int &p) {
			val[p]=std::max(val[p _left],val[p _right]);
		}
	public:
		void modify(const int &p,const int &b,const int &e,const int &x,const std::pair<int,int> &v) {
			if(b==e) {
				val[p]=std::max(val[p],v);
				return;
			}
			if(x<=mid) modify(p _left,b,mid,x,v);
			if(x>mid) modify(p _right,mid+1,e,x,v);
			push_up(p);
		}
		std::pair<int,int> query(const int &p,const int &b,const int &e,const int &l,const int &r) const {
			if(b==l&&e==r) return val[p];
			std::pair<int,int> ret(0,0);
			if(l<=mid) ret=std::max(ret,query(p _left,b,mid,l,std::min(mid,r)));
			if(r>mid) ret=std::max(ret,query(p _right,mid+1,e,std::max(mid+1,l),r));
			return ret;
		}
	#undef _left
	#undef _right
	#undef mid
};
SegmentTree t1,t2;
std::set<std::pair<int,int> > set;
int main() {
	const int n=getint(),m=getint();
	int tot=0;
	for(register int i=1;i<=n;i++) {
		const int l=getint(),r=getint();
		a[i]=(Node){l,i};
		b[i]=(Node){r,i};
		tmp[++tot]=l;
		tmp[++tot]=r;
	}
	for(register int i=1;i<=m;i++) {
		tmp[++tot]=c[i].l=getint();
		tmp[++tot]=c[i].r=getint();
		c[i].w=getint();
		c[i].id=i;
	}
	std::sort(&tmp[1],&tmp[tot]+1);
	for(register int i=1;i<=n;i++) {
		a[i].p=std::lower_bound(&tmp[1],&tmp[tot]+1,a[i].p)-tmp;
		b[i].p=std::lower_bound(&tmp[1],&tmp[tot]+1,b[i].p)-tmp;
	}
	for(register int i=1;i<=m;i++) {
		c[i].l=std::lower_bound(&tmp[1],&tmp[tot]+1,c[i].l)-tmp;
		c[i].r=std::lower_bound(&tmp[1],&tmp[tot]+1,c[i].r)-tmp;
	}
	std::sort(&a[1],&a[n]+1);
	std::sort(&b[1],&b[n]+1);
	std::sort(&c[1],&c[m]+1);
	for(register int i=1;i<=n;i++) {
		rnk[a[i].id]=i;
	}
	int64 ans=0;
	int x,y;
	for(register int i=1,j=1,k=1;i<=m;i++) {
		for(;j<=n&&a[j].p<=c[i].r;j++) {
			set.insert(std::make_pair(tmp[a[j].p],a[j].id));
		}
		for(;k<=n&&b[k].p<=c[i].r;k++) {
			const int j=rnk[b[k].id];
			set.erase({tmp[a[j].p],a[j].id});
			t1.modify(1,1,tot,a[j].p,{tmp[b[k].p]-tmp[a[j].p],a[j].id});
			t2.modify(1,1,tot,a[j].p,{tmp[b[k].p],a[j].id});
		}
		//-: ad
		//=: tv
		int len=0,z=0;
		if(!set.empty()) {
			//  ------
			//======
			const int t=tmp[c[i].r]-std::max(tmp[c[i].l],set.begin()->first);
			if(t>len) {
				len=t;
				z=set.begin()->second;
			}
		}
		{
			//  --
			//======
			const auto p=t1.query(1,1,tot,c[i].l,c[i].r);
			if(p.first>len) {
				len=p.first;
				z=p.second;
			}
		}
		{
			//------
			//  ======
			const auto p=t2.query(1,1,tot,1,c[i].l);
			if(p.first-tmp[c[i].l]>len) {
				len=p.first-tmp[c[i].l];
				z=p.second;
			}
		}
		if(1ll*len*c[i].w>ans) {
			ans=1ll*len*c[i].w;
			x=z,y=c[i].id;
		}
	}
	printf("%lld\n",ans);
	if(ans) printf("%d %d\n",x,y);
	return 0;
}
```

---

## 作者：mrsrz (赞：1)

我们考虑一个电视台$a$，分如下几类：

1. 广告和电视台的公共部分为$[L_a,x]$，即左边相交于左端点，右边在线段中间。这种情况，我们可以建一棵前缀主席树，把左端点在$1\sim i$内的右端点存到线段树上。然后查询相应左端点中最右边的那个，即为最优选法。
2. 广告和电视台的公共部分为$[x,R_a]$，即右边相交于右端点，左边在线段中间。按上一种情况的方法倒着讨论即可。
3. 广告的电视台的公共部分为$[L_a,R_a]$，即电视台完全被包含。由于情况1是选取左端点在$L_a$左边的、最右边的线段，所以这种情况也一定被考虑进去了，计算贡献时对$R_a$取较小值即可。
4. 广告的电视台的公共部分为$[x,y]$，即广告完全被包含。这个不好考虑。我们换个思路：把电视台按左端点建主席树，每次在相应右端点处插入其人数$c$的值。然后就是取完全覆盖它的且$c$最大的一个即可。

所以主席树做三遍即可。由于空间问题，只能开一棵主席树的节点，所以每次做完一遍后再建下一遍的主席树。

由于需要输出方案，所以主席树中需要多维护一个编号。我直接将两个关键字压成一个long long计算。

而且只有256MB，主席树不能开太大。

时间复杂度$O((n+m)\log n)$。

## Code：
```cpp
#include<cstdio>
#include<cctype>
#include<algorithm>
#include<vector>
#define N 200005
#define M 800005
typedef long long LL;
const int base=(1<<18)-1;
struct istream{
    char buf[23333333],*s;
    inline istream(){
        buf[fread(s=buf,1,23333330,stdin)]='\n';
        fclose(stdin);
    }
    inline istream&operator>>(int&d){
        for(d=0;!isdigit(*s);++s);
        while(isdigit(*s))
        d=d*10+(*s++^'0');
        return*this;
    }
}cin;
int ls[M*16],rs[M*16],rt[M],node;
LL mx[M*16];
int adL[N],adR[N],qL[N],qR[N],qC[N],n,m,x,y;
std::vector<int>vec,id[M];
LL ans=0;
void add(int&o,int l,int r,const int&pos,const LL&ins){
    const int pre=o;
    o=++node;ls[o]=ls[pre],rs[o]=rs[pre];
    if(l==r)mx[o]=ins;else{
        const int mid=l+r>>1;
        if(pos<=mid)add(ls[o],l,mid,pos,ins);else
        add(rs[o],mid+1,r,pos,ins);
        mx[o]=std::max(mx[ls[o]],mx[rs[o]]);
    }
}
LL query(const int&o,int l,int r,const int&L){
    if(!o)return 0;
    if(L<=l)return mx[o];
    const int mid=l+r>>1;
    if(L<=mid)return std::max(query(ls[o],l,mid,L),mx[rs[o]]);else
    return query(rs[o],mid+1,r,L);
}
void add2(int&o,int l,int r,const int&pos,const LL&ins){
    const int pre=o;
    o=++node;ls[o]=ls[pre],rs[o]=rs[pre];
    if(l==r)mx[o]=ins;else{
        const int mid=l+r>>1;
        if(pos<=mid)add2(ls[o],l,mid,pos,ins);else
        add2(rs[o],mid+1,r,pos,ins);
        mx[o]=std::min(mx[ls[o]],mx[rs[o]]);
    }
}
LL query2(const int&o,int l,int r,const int&R){
    if(!o)return 1e18;
    if(r<R)return mx[o];
    const int mid=l+r>>1;
    if(mid<R)return std::min(query2(rs[o],mid+1,r,R),mx[ls[o]]);else
    return query2(ls[o],l,mid,R);
}
void add3(int&o,int l,int r,const int&pos,const LL&C){
    const int pre=o;
    o=++node;ls[o]=ls[pre],rs[o]=rs[pre];
    if(l==r)mx[o]=std::max(mx[pre],C);else{
        const int mid=l+r>>1;
        if(pos<=mid)add3(ls[o],l,mid,pos,C);else
        add3(rs[o],mid+1,r,pos,C);
        mx[o]=std::max(mx[ls[o]],mx[rs[o]]);
    }
}
int main(){
    vec.push_back(-1);
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        cin>>adL[i]>>adR[i];
        vec.push_back(adL[i]),vec.push_back(adR[i]);
    }
    for(int i=1;i<=m;++i){
        cin>>qL[i]>>qR[i]>>qC[i];
        vec.push_back(qL[i]),vec.push_back(qR[i]);
    }
    std::sort(vec.begin(),vec.end());
    vec.erase(std::unique(vec.begin(),vec.end()),vec.end());
    for(int i=1;i<=n;++i){
        adL[i]=std::lower_bound(vec.begin(),vec.end(),adL[i])-vec.begin();
        adR[i]=std::lower_bound(vec.begin(),vec.end(),adR[i])-vec.begin();
        id[adL[i]].push_back(i);
    }
    for(int i=1;i<=m;++i){
        qL[i]=std::lower_bound(vec.begin(),vec.end(),qL[i])-vec.begin();
        qR[i]=std::lower_bound(vec.begin(),vec.end(),qR[i])-vec.begin();
    }
    const int S=vec.size();
    for(int i=1;i<=S;++i){
        rt[i]=rt[i-1];
        for(int j=id[i].size()-1;~j;--j)
        add(rt[i],1,S,adR[id[i][j]],(LL)adR[id[i][j]]<<18|id[i][j]);
    }
    for(int i=1;i<=m;++i){
        LL right=query(rt[qL[i]],1,S,qL[i]);
        if(right>>18>qR[i])right=(right&base)|((LL)qR[i]<<18);
        if(right>>18>qL[i]){
        	const LL val=(LL)(vec[right>>18]-vec[qL[i]])*qC[i];
        	if(ans<val)ans=val,x=right&base,y=i;
        }
    }
    node=0;
    *mx=1e18;
    for(int i=1;i<=S;++i)id[i].clear(),rt[i]=0;
    for(int i=1;i<=n;++i)id[adR[i]].push_back(i);
    for(int i=S;i;--i){
        rt[i]=rt[i+1];
        for(int j=id[i].size()-1;~j;--j)
        add2(rt[i],1,S,adL[id[i][j]],(LL)adL[id[i][j]]<<18|id[i][j]);
    }
    for(int i=1;i<=m;++i){
        LL left=query2(rt[qR[i]],1,S,qR[i]);
        if(left>>18<qL[i])left=(left&base)|((LL)qL[i]<<18);
        if(left>>18<qR[i]){
        	const LL val=(LL)(vec[qR[i]]-vec[left>>18])*qC[i];
        	if(ans<val)ans=val,x=left&base,y=i;
        }
    }
    *mx=node=0;
    for(int i=1;i<=S;++i)id[i].clear(),rt[i]=0;
    for(int i=1;i<=m;++i)id[qL[i]].push_back(i);
    for(int i=1;i<=S;++i){
        rt[i]=rt[i-1];
        for(int j=id[i].size()-1;~j;--j)
        add3(rt[i],1,S,qR[id[i][j]],(LL)qC[id[i][j]]<<18|id[i][j]);
    }
    for(int i=1;i<=n;++i){
        const LL mx=query(rt[adL[i]],1,S,adR[i]);
        const LL val=(mx>>18)*(vec[adR[i]]-vec[adL[i]]);
        if(ans<val)ans=val,x=i,y=mx&base;
    }
    if(ans)
    printf("%lld\n%d %d\n",ans,x,y);else puts("0");
    return 0;
}
```

---

## 作者：ifffer_2137 (赞：0)

~~太好了做的每道 ds 都写成一坨还大常数。~~
### 题意
给定若干条线段 $a_i$，和若干条带权线段 $b_i$，在 $a_i$ 和 $b_i$ 中各选一条价值是线段交的长度乘上 $b_i$ 的权值，求最大值。
### 分析
对于每个 $b_i$ 求个最大交就好了。

为了方便处理，我们考虑把 $a_i$ 分为被 $b_i$ 包含和不被 $b_i$ 包含的。

然后先做后者，找出右端点比 $b_i$ 大的最小左端点，左端点比 $b_i$ 小的最大右端点，你只需拿这两条取交。然后你发现离散化以后右/左端点插入左/右端点直接在里查区间 $\min$ 和 $\max$ 就可以了。

考虑前者，右端点排序后上个扫描线，two pointer 扫右端点的时候用 sgt 维护当前每个左端点上挂着的最长线段，区间 $\max$ 即可。

然后你发现两个部分共用一棵 sgt 就好了，时间复杂度 $O(n\log n)$。
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define inf 4e18
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
inline void getmn(int &x,int y){if(y<x)x=y;}
inline void getmx(int &x,int y){if(y>x)x=y;}
mt19937 rnd(time(NULL));
const int maxn=2e5+5;
int n,m;
int ans;
int X,Y;
struct node{
	int id;
	int l,r,c;
	node(){id=l=r=c=0;}
	bool operator < (const node &b) const{return r<b.r;}
}a[maxn],b[maxn];
int t[maxn<<2],tt;
int cap[maxn];
class Segment_Tree{
#define ls (o<<1)
#define rs (o<<1|1)
private:
	int mn[maxn<<4],mx[maxn<<4];
	void pushup(int o){mn[o]=min(mn[ls],mn[rs]),mx[o]=max(mx[ls],mx[rs]);}
public:
	void build(int o,int l,int r){
		mn[o]=inf,mx[o]=-inf;if(l==r) return;
		int m=(l+r)>>1;
		build(ls,l,m),build(rs,m+1,r);
	}
	void update(int o,int l,int r,int x,int k){
		if(l==r) return getmn(mn[o],k),getmx(mx[o],k),void();
		int m=(l+r)>>1;
		if(x<=m) update(ls,l,m,x,k);
		else update(rs,m+1,r,x,k);
		pushup(o);
	}
	int querymn(int o,int l,int r,int x,int y){
		if(x<=l&&r<=y) return mn[o];
		int m=(l+r)>>1,res=inf;
		if(x<=m) getmn(res,querymn(ls,l,m,x,y));
		if(y>m) getmn(res,querymn(rs,m+1,r,x,y));
		return res;
	}
	int querymx(int o,int l,int r,int x,int y){
		if(x<=l&&r<=y) return mx[o];
		int m=(l+r)>>1,res=0;
		if(x<=m) getmx(res,querymx(ls,l,m,x,y));
		if(y>m) getmx(res,querymx(rs,m+1,r,x,y));
		return res;
	}
#undef ls
#undef rs
}sgt;
signed main(){
	#ifndef ONLINE_JUDGE
	freopen("data.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	cin.tie(0),cout.tie(0);
	n=read(),m=read();
	for(int i=1;i<=n;i++) t[++tt]=a[i].l=read(),t[++tt]=a[i].r=read(),a[i].id=i;
	for(int i=1;i<=m;i++) t[++tt]=b[i].l=read(),t[++tt]=b[i].r=read(),b[i].c=read(),b[i].id=i;
	sort(t+1,t+tt+1),tt=unique(t+1,t+tt+1)-t-1;
	for(int i=1;i<=n;i++){
		a[i].l=lower_bound(t+1,t+tt+1,a[i].l)-t;
		a[i].r=lower_bound(t+1,t+tt+1,a[i].r)-t;
	}
	for(int i=1;i<=m;i++){
		b[i].l=lower_bound(t+1,t+tt+1,b[i].l)-t;
		b[i].r=lower_bound(t+1,t+tt+1,b[i].r)-t;
	}
	sgt.build(1,1,tt);
	for(int i=1;i<=n;i++) sgt.update(1,1,tt,a[i].r,a[i].l);
	for(int i=1;i<=m;i++){
		int p=sgt.querymn(1,1,tt,b[i].r,tt);
		if(p==inf) continue;
		getmx(p,b[i].l);
		getmx(cap[i],t[b[i].r]-t[p]);
	}
	sgt.build(1,1,tt);
	for(int i=1;i<=n;i++) sgt.update(1,1,tt,a[i].l,a[i].r);
	for(int i=1;i<=m;i++){
		int p=sgt.querymx(1,1,tt,1,b[i].l);
		if(p==-inf) continue;
		getmn(p,b[i].r);
		getmx(cap[i],t[p]-t[b[i].l]);
	}
	sgt.build(1,1,tt);
	sort(a+1,a+n+1,[&](node x,node y){return x.r<y.r;});
	sort(b+1,b+m+1,[&](node x,node y){return x.r<y.r;});
	for(int i=1,ch=0;i<=m;i++){
		while(ch<n&&a[ch+1].r<=b[i].r){
			++ch;
			sgt.update(1,1,tt,a[ch].l,t[a[ch].r]-t[a[ch].l]);
		}
		getmx(cap[b[i].id],sgt.querymx(1,1,tt,b[i].l,b[i].r));
	}
	for(int i=1;i<=m;i++){
		if(cap[b[i].id]*b[i].c>ans){
			ans=cap[b[i].id]*b[i].c;
			Y=i;
		}
	}
	if(ans==0){
		cout<<ans<<'\n';
		return 0;
	}
	for(int i=1;i<=n;i++){
		int l=max(t[a[i].l],t[b[Y].l]),r=min(t[a[i].r],t[b[Y].r]);
		if(r-l==cap[b[Y].id]) X=a[i].id;
	}
	Y=b[Y].id;
	cout<<ans<<'\n';
	cout<<X<<' '<<Y<<'\n';
	// cerr<<1.0*clock()/CLOCKS_PER_SEC<<'\n';
	return 0;
}
```

---

## 作者：phil071128 (赞：0)

**Place Your Ad Here**

Duel 随机做到的，感觉没有紫吧，思路很好想但是一点细节调了很久。

因为电视台多一个信息，所以显然先枚举电视台。

那么我们对广告和电视台都右端点排序，我们下文称广告为 $a$，电视台为 $b$。双指针一下即可时刻维护右端点小于等于 $b$ 的所有 $a$。

那么 $a,b$ 相交，可以具体分为三类：

- $a$ 的右端点在 $b$ 的右端点左侧：
  - $a$ 的左端点在 $b$ 的左端点左侧；
  - $a$ 的左端点在 $b$ 的左端点右侧。
- $a$ 的右端点在 $b$ 的右端点右侧。

自然地想到以左端点为线段树下标，维护区间最大值。

对于第一类，维护 $a$ 的右端点 $r$。答案为区间最大值减去 $b$ 的左端点。

对于第二类，维护 $a$ 的区间长度 $r-l$。

对于第三类，最值线段树不方便撤销，但是我们可以用个 `set` 维护，关键字依然为右端点，每次取最小的。



```
#include <bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int read(){
	char c=getchar();int h=0,tag=1;
	while(!isdigit(c)) tag=(c=='-'?-1:1),c=getchar();
	while(isdigit(c)) h=(h<<1)+(h<<3)+(c^48),c=getchar();
	return h*tag;
}
void fil(){
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
}
const int N=6e5+500;
struct node{
	int a,b,c;
}vid[N];
struct tree{
	#define ls(x) (x<<1)
	#define rs(x) (x<<1|1)
	#define mid ((l+r)>>1)
	int t[N*4];
	void push_up(int p) {
		t[p]=max(t[ls(p)],t[rs(p)]);
	}
	void upd(int p,int l,int r,int x,int k) {
		if(l==r) return t[p]=max(t[p],k),void();
		if(x<=mid) upd(ls(p),l,mid,x,k);
		else upd(rs(p),mid+1,r,x,k);
		push_up(p);
	}
	int query(int p,int l,int r,int nl,int nr) {
		if(nl>nr) return 0;
		if(nl<=l&&r<=nr) {
			return t[p];
		}
		int ans=0;
		if(nl<=mid) ans=max(ans,query(ls(p),l,mid,nl,nr));
		if(mid<nr) ans=max(ans,query(rs(p),mid+1,r,nl,nr));
		return ans;
	}
}t1,t2;
int bb[N*4],p1[N],p2[N];
pii adv[N],d[N]; 
signed main(){
	//fil();
	int n=read(),m=read(),tot=0;
	for(int i=1;i<=n;i++) {
		int l=read()+1,r=read()+1;
		adv[i]=pii(l,r);
		bb[++tot]=l;bb[++tot]=r;
		p1[i]=i;
		d[i]=pii(l,r);
	}
	for(int i=1;i<=m;i++) {
		int a=read()+1,b=read()+1,c=read();
		vid[i]=node{a,b,c};
		bb[++tot]=a,bb[++tot]=b;
		p2[i]=i;
	}
	sort(bb+1,bb+1+tot);sort(p2+1,p2+1+m,[](int a,int b){
		return vid[a].b<vid[b].b;
	});tot=unique(bb+1,bb+1+tot)-bb-1;
	sort(vid+1,vid+1+m,[](node x,node y) {
		return x.b<y.b;
	});sort(adv,adv+1+n,[](pii a,pii b){
		return a.se<b.se;
	});int idx=0,ans=0,tagans=0;
	set<pii>st;
	for(int i=1;i<=n;i++) st.insert(adv[i]);
	for(int i=1;i<=m;i++) {
		while((idx+1<=n)&&(adv[idx+1].se<=vid[i].b)) {
			idx++;
			int tmp=lower_bound(bb+1,bb+1+tot,adv[idx].fi)-bb;
			t1.upd(1,1,tot,tmp,adv[idx].se);
			t2.upd(1,1,tot,tmp,adv[idx].se-adv[idx].fi);
			st.erase(adv[idx]);
		}
		int tmp1=lower_bound(bb+1,bb+1+tot,vid[i].a)-bb,tmp2=lower_bound(bb+1,bb+1+tot,vid[i].b)-bb;
		int len1=t1.query(1,1,tot,1,tmp1)-vid[i].a;
		int len2=t2.query(1,1,tot,tmp1+1,tmp2);
		int len3=vid[i].b-max((*(st.begin())).fi,vid[i].a);
		if(st.size()==0) len3=0;
		int tmp=vid[i].c*max(len1,max(len2,len3));
		if(tmp>ans) {
			ans=tmp;
			tagans=i;
		}
	}
	cout<<ans<<'\n';
	if(ans==0) return 0 ;
	int a=vid[tagans].a,b=vid[tagans].b,c=vid[tagans].c;
	for(int i=1;i<=n;i++) {
		int l=d[i].fi,r=d[i].se;
		if((min(r,b)-max(l,a))*c==ans) {
			cout<<i<<" "<<p2[tagans]<<"\n";
			return 0;
		}
	}
	return 0;
}
```cpp

---

## 作者：wwwwwza (赞：0)

一眼分块。

将广告按开始时间从小到大排序，然后分块。

枚举每个电视台的最大收益，设现在枚举的这个电视台播出时间为 $l$ 和 $r$，这个块中广告的播出时间最小为 $a$，最大为 $b$，结束时间最大为 $c$。

- $a\leq l < b$ 或 $a\leq r < b$。

这一块不好直接计算，所以暴力枚举，因为这种含交界点的块只有两个。

- $b\leq l$。

在这一块中所有广告的开始时间都小于等于电视台的播出时间，所以预处理出其广告的结束时间的最大值。

- $c\ge r$。

暴力枚举，枚举完退出循环，因为其中有一个广告的结束时间已经大于等于 $r$ 了，后面的广告的开始时间不会比这个广告小，所以后面的广告不会对答案产生贡献。

- $c< r$。

电视台的播出时间包含了广告的播放时间，预处理这一段广告时长的最大值。


```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
const int M=447;
const int inf=1e5;
int n,m;
struct node{
	int a,b,c;
}p[N],q[N];
bool cmp(node x,node y){
	return x.a<y.a;
}
int len(int x1,int y1,int x2,int y2){
	return max(min(y1,y2)-max(x1,x2),0);
}
int V,L[N],R[N];
struct block{
	int maxr,mx;
}bl[M+5];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&p[i].a,&p[i].b);
		p[i].c=i;
	}
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&q[i].a,&q[i].b,&q[i].c);
	}
	sort(p+1,p+1+n,cmp);
	V=(n-1)/M+1;
	for(int i=1;i<=V;i++){
		L[i]=R[i-1]+1;
		R[i]=i*M;
	}
	R[V]=n;
	for(int i=1;i<=V;i++){
		for(int j=L[i];j<=R[i];j++){
			bl[i].maxr=max(bl[i].maxr,p[j].b);
			bl[i].mx=max(bl[i].mx,p[j].b-p[j].a);
		}
	}
	long long ans=0,maxn=0,posx=0,posy=0;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=V;j++){
			if(p[L[j]].a>q[i].b)break;
			if(p[L[j]].a<=q[i].a&&p[R[j]].a>q[i].a){
				for(int k=L[j];k<=R[j];k++){
					ans=max(ans,1ll*len(p[k].a,p[k].b,q[i].a,q[i].b)*q[i].c);
				}
			}else if(p[L[j]].a<=q[i].b&&p[R[j]].a>q[i].b){
				for(int k=L[j];k<=R[j];k++){
					ans=max(ans,1ll*len(p[k].a,p[k].b,q[i].a,q[i].b)*q[i].c);
				}
			}else if(p[R[j]].a<=q[i].a){
				ans=max(ans,1ll*(min(bl[j].maxr,q[i].b)-q[i].a)*q[i].c);
			}else{
				if(bl[j].maxr>=q[i].b){
					for(int k=L[j];k<=R[j];k++){
						ans=max(ans,1ll*len(p[k].a,p[k].b,q[i].a,q[i].b)*q[i].c);
					}
					break;
				}else{
					ans=max(ans,1ll*bl[j].mx*q[i].c);
				}
			}
		}
		if(maxn<ans){
			maxn=ans;
			posy=i;
		}
	}
	for(int i=1;i<=n;i++){
		long long res=1ll*len(p[i].a,p[i].b,q[posy].a,q[posy].b)*q[posy].c;
		if(res==ans)posx=p[i].c;
	}
	if(ans!=0)printf("%lld\n%lld %lld",ans,posx,posy);
	else printf("0");
	return 0;
}

```

---

## 作者：Purslane (赞：0)

# Solution

显然枚举电视台更靠谱。

广告和他有三种位置关系：

1. 广告包含在电视台的运行时间内部，交就是广告的时间。
2. 广告的开始时间早于电视台的开始时间，需要求出这样的广告的结束时间的最大值。
3. 广告的结束时间晚于电视台的结束时间，需要求出这样的广告的开始时间的最小值。

如果广告完全包含电视台，那么实际上 $2$ 和 $3$ 都会统计一遍，不过貌似没关系。

$1$ 用扫描线，$2$ 和 $3$ 直接求前缀和。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=8e5+10;
int n,m,tot,ans,lsh[MAXN],l[MAXN],r[MAXN],a[MAXN],b[MAXN],c[MAXN];
vector<int> upd[MAXN],qr[MAXN]; 
pair<int,int> tans;
pair<int,int> pre[MAXN],suf[MAXN];
#define lson (k<<1)
#define rson (k<<1|1)
#define mid (l+r>>1)
pair<int,int> mx[MAXN<<2];
void update(int k,int l,int r,int pos,pair<int,int> v) {
	mx[k]=max(mx[k],v);
	if(l==r) return ;
	if(pos<=mid) update(lson,l,mid,pos,v);
	else update(rson,mid+1,r,pos,v);
	return ;
}
pair<int,int> query(int k,int l,int r,int x,int y) {
	if(x<=l&&r<=y) return mx[k];
	if(y<=mid) return query(lson,l,mid,x,y);
	if(x>mid) return query(rson,mid+1,r,x,y);
	return max(query(lson,l,mid,x,y),query(rson,mid+1,r,x,y));	
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,1,n) cin>>l[i]>>r[i],lsh[++tot]=l[i],lsh[++tot]=r[i];
	ffor(i,1,m) cin>>a[i]>>b[i]>>c[i],lsh[++tot]=a[i],lsh[++tot]=b[i];
	sort(lsh+1,lsh+tot+1),tot=unique(lsh+1,lsh+tot+1)-lsh-1;
	ffor(i,1,n) l[i]=lower_bound(lsh+1,lsh+tot+1,l[i])-lsh,r[i]=lower_bound(lsh+1,lsh+tot+1,r[i])-lsh;
	ffor(i,1,m) a[i]=lower_bound(lsh+1,lsh+tot+1,a[i])-lsh,b[i]=lower_bound(lsh+1,lsh+tot+1,b[i])-lsh;
	ffor(i,1,n) upd[r[i]].push_back(i);
	ffor(i,1,m) qr[b[i]].push_back(i);
	ffor(i,1,tot) {
		for(auto id:upd[i]) update(1,1,tot,l[id],{lsh[r[id]]-lsh[l[id]],id});
		for(auto id:qr[i]) {
			auto pr=query(1,1,tot,a[id],b[id]);
			if(pr.first*c[id]>ans) ans=pr.first*c[id],tans={pr.second,id};
		}
	}
	memset(suf,0x3f,sizeof(suf));
	ffor(i,1,n) pre[l[i]]=max(pre[l[i]],{r[i],i}),suf[r[i]]=min(suf[r[i]],{l[i],i});
	ffor(i,1,tot) pre[i]=max(pre[i],pre[i-1]);
	roff(i,tot,1) suf[i]=min(suf[i],suf[i+1]);
	ffor(i,1,m) {
		if(pre[a[i]].first>=1&&pre[a[i]].first<=tot) if(min(lsh[b[i]]-lsh[a[i]],lsh[pre[a[i]].first]-lsh[a[i]])*c[i]>ans) ans=min(lsh[b[i]]-lsh[a[i]],lsh[pre[a[i]].first]-lsh[a[i]])*c[i],tans={pre[a[i]].second,i};
		if(suf[b[i]].first>=1&&suf[b[i]].first<=tot) if(min(lsh[b[i]]-lsh[a[i]],lsh[b[i]]-lsh[suf[b[i]].first])*c[i]>ans) ans=min(lsh[b[i]]-lsh[a[i]],lsh[b[i]]-lsh[suf[b[i]].first])*c[i],tans={suf[b[i]].second,i};
	}
	cout<<ans<<'\n';
	if(ans) cout<<tans.first<<' '<<tans.second;
	return 0;
}
```

---

## 作者：ty_mxzhn (赞：0)

由于 $c_j$ 是一个常数，而 $l_i,r_i$ 贡献却是 $1$，所以考虑枚举 $j$。

两种贡献。

# $b_j \le r_i$

这一部分的贡献只取决于选取的 $l_i$ 大小，按 $r$ 降序排序后求所有 $b_j<r_i$ 中最小的 $l_i$ 贡献答案即可。

注意如果 $a_j>r_i$ 要特判一下。

# $b_j > r_i$

这一部分贡献有一个限制是 $b_j > r_i$，所以按 $r$ 升序排序然后求所有满足条件的 $i$ 的贡献。此处再次分讨。

### $a_j \le l_i$

答案是 $r_i-l_i$。在树状数组上取个后缀 $\max$ 容易维护。

### $a_j > l_i$

答案是 $r_i-a_j$。在树状数组上取个前缀 $\max$ 容易维护。

---

