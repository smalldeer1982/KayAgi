# Non-Decreasing Dilemma

## 题目描述

Alice has recently received an array $ a_1, a_2, \dots, a_n $ for her birthday! She is very proud of her array, and when she showed her friend Bob the array, he was very happy with her present too!

However, soon Bob became curious, and as any sane friend would do, asked Alice to perform $ q $ operations of two types on her array:

- $ 1 $ $ x $ $ y $ : update the element $ a_x $ to $ y $ (set $ a_x = y $ ).
- $ 2 $ $ l $ $ r $ : calculate how many non-decreasing subarrays exist within the subarray $ [a_l, a_{l+1}, \dots, a_r] $ . More formally, count the number of pairs of integers $ (p,q) $ such that $ l \le p \le q \le r $ and $ a_p \le a_{p+1} \le \dots \le a_{q-1} \le a_q $ .

Help Alice answer Bob's queries!

## 说明/提示

For the first query, $ l = 2 $ and $ r = 5 $ , and the non-decreasing subarrays $ [p,q] $ are $ [2,2] $ , $ [3,3] $ , $ [4,4] $ , $ [5,5] $ , $ [2,3] $ and $ [4,5] $ .

## 样例 #1

### 输入

```
5 6
3 1 4 1 5
2 2 5
2 1 3
1 4 4
2 2 5
1 2 6
2 2 5```

### 输出

```
6
4
10
7```

# 题解

## 作者：Akoasm_X (赞：7)

### 用类似区间最大子串和的方式维护答案



1. 考虑把一个序列分成两半，左侧 和 右侧 分别统计一次答案，然后考虑 左侧 和 右侧共同统计，递增序列一定连续，所以贡献统计需要用到 左侧的后缀 和 右侧的前缀

2. 记 $sum$ 为整个区间内的答案 ，$suml$ 和 $sumr$ 为从区间开头、末尾开始递增、递减的最长序列，例如 $[3,1,4,1,5]$ 中 $suml = 1$，$sumr = 2$，得到 $sum_x = sum_{ls} + sum_{rs} + sumr_{ls} * suml_{rs}$，条件是 左侧的右端点 小于等于 右侧的左端点

3. 所以需要记录区间的左右端点值，以及上文提到的 $sum,suml,sumr$，接下来考虑如何更新 $suml$ 和 $sumr$。以 $suml$ 为例，一定有 $suml_x \ge suml_{ls}$，考虑什么情况下有 $suml_x > suml_{ls}$ ，答案是 整个左区间 单调的情况下才可能发生 $suml_x = len_{ls} + suml_{rs}$，另记一个区间长度即可

代码如下
```cpp
#include<bits/stdc++.h>
#define mid ((l+r)>>1)
#define lson (x<<1),l,mid
#define rson (x<<1|1),mid+1,r
using namespace std;
typedef long long LL;
const int maxn = 2e5+20;
int n,m;
struct node{
	int lx,rx,len;
	LL sum,suml,sumr;
}Tree[maxn<<2];

inline int read(){
    int x = 0 , f = 1 ; char c = getchar() ;
    while( c < '0' || c > '9' ) { if( c == '-' ) f = -1 ; c = getchar() ; } 
    while( c >= '0' && c <= '9' ) { x = x * 10 + c - '0' ; c = getchar() ; } 
    return x * f ;
}

node pushup(node x,node y){
	node z;
	z.lx = x.lx ;z.rx = y.rx ;
	z.sum = x.sum + y.sum ;z.len = x.len + y.len ;
	if(x.rx<=y.lx){
		z.sum += 1ll * x.sumr * y.suml ;
		if(x.suml==x.len) z.suml = x.len + y.suml ;
		else z.suml = x.suml ;
		if(y.sumr==y.len) z.sumr = x.sumr + y.len ;
		else z.sumr = y.sumr ;
	}
	else z.suml = x.suml ,z.sumr = y.sumr ;
	return z; 
}

void build(int x,int l,int r){
	if(l==r){
		Tree[x].lx = Tree[x].rx = read();
		Tree[x].len = Tree[x].sum = Tree[x].suml = Tree[x].sumr = 1;
		return ; 
	}
	build(lson);build(rson);
	Tree[x] = pushup(Tree[x<<1],Tree[x<<1|1]);
}

void update(int x,int l,int r,int pos,int k){
	if(l==r){
		Tree[x].lx = Tree[x].rx = k;
		return ;
	}
	if(pos<=mid) update(lson,pos,k);
	else update(rson,pos,k);
	Tree[x] = pushup(Tree[x<<1],Tree[x<<1|1]);
}

node query(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R) return Tree[x];
	if(R<=mid) return query(lson,L,R);
	if(mid<L) return query(rson,L,R);
	return pushup(query(lson,L,R),query(rson,L,R));
}

int main(){
	n = read();m = read();
	build(1,1,n);
	for(int i=1;i<=m;i++){
		int op = read(),l = read(),r = read();
		if(op==1) update(1,1,n,l,r);
		else printf("%lld\n",query(1,1,n,l,r).sum);
	}
	return 0;
}
```


---

## 作者：Graphcity (赞：2)

### 题意简述

给定一个 $n$ 个数的序列 $a$ 和 $q$ 次询问，每次询问有两种类型：

- `1 x y`：将 $a_x$ 修改为 $y$。
- `2 l r`：询问 $a_l\sim a_r$ 之间的不下降子串数目。

### 思路

可以发现，整个序列可以被分为若干个不下降段。我们把每一段的末尾打上标记，那么如果 $a_i$ 被打上了标记，则必有 $a_i>a_{i+1}$。为了方便，我们把 $0$ 号位置和 $n$ 号位置也打上标记。

设 $w_i$ 为以 $a_i$ 为开头的不下降子串数目，$pos$ 为在 $i$ 后面（包括它自己）离它最近的标记位置，就有 $w_i=pos-i+1$。

对于单点修改操作，需要支持增加 / 删除 $x-1$ 或 $x$ 位置处的标记。

当一个位置 $x$ 增加标记时，设 $pre$ 为左边离它最近的标记位置，$pos$ 为右边离它最近的标记位置。根据 $w$ 数组的定义，就需要将 $w_{pre+1}\sim w_i$ 均减去 $pos-x$。删除同理，只需要增加 $pos-x$ 即可。

查询的时候，可以人为在 $r$ 位置添加一个标记，再统计 $\sum_{i=l}^rw_i$，最后删除 $r$ 位置的标记即可。

维护标记数组可以用 set 解决，$w$ 数组的区修区查可以使用线段树，时间复杂度 $O((n+q)\log n)$。

### 代码

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
#define Fo(i,a,b) for(int i=(a);i<(b);++i)
#define Ro(i,a,b) for(int i=(a);i>(b);--i)
#define ll long long
using namespace std;
const int Maxn=2e5;

inline int read()
{
    char ch=getchar();
    int f=1,x=0;
    while(ch>'9' || ch<'0')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,q,val[Maxn+5],num[Maxn+5];
ll t[Maxn*4+5],tag[Maxn*4+5];
set<int> st,st2; // 第一个从小到大,第二个从大到小
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)

inline void push_up(int p) {t[p]=t[ls(p)]+t[rs(p)];}
inline void f(int l,int r,int p,int k)
{t[p]+=1ll*(r-l+1)*k,tag[p]=tag[p]+k;}
inline void push_down(int l,int r,int p)
{
	int mid=(l+r)>>1;
	f(l,mid,ls(p),tag[p]),f(mid+1,r,rs(p),tag[p]);
	tag[p]=0; return;
}
inline void Build(int l,int r,int p)
{
	if(l==r) {t[p]=num[l]; return;}
	int mid=(l+r)>>1;
	Build(l,mid,ls(p)),Build(mid+1,r,rs(p)),push_up(p);
}
inline void Update(int nl,int nr,int l,int r,int p,int k)
{
	if(l<=nl && nr<=r)
	{
		t[p]+=1ll*k*(nr-nl+1),tag[p]=tag[p]+k;
		return;
	}
	push_down(nl,nr,p);
	int mid=(nl+nr)>>1;
	if(l<=mid) Update(nl,mid,l,r,ls(p),k);
	if(r>mid) Update(mid+1,nr,l,r,rs(p),k);
	push_up(p);
}
inline ll Count(int nl,int nr,int l,int r,int p)
{
	if(l<=nl && nr<=r) return t[p];
	push_down(nl,nr,p);
	int mid=(nl+nr)>>1; ll res=0;
	if(l<=mid) res+=Count(nl,mid,l,r,ls(p));
	if(r>mid) res+=Count(mid+1,nr,l,r,rs(p));
	push_up(p); return res;
}
inline void Add(int x) // 添加x位置标记
{
    int pos=*st.lower_bound(x),pre=-(*st2.lower_bound(-x))+1;
    Update(1,n,pre,x,1,x-pos);
    st.insert(x),st2.insert(-x);
}
inline void Del(int x)
{
    st.erase(x),st2.erase(-x);
    int pos=*st.lower_bound(x),pre=-(*st2.lower_bound(-x))+1;
    Update(1,n,pre,x,1,pos-x);
}

int main()
{
    n=read(),q=read();
    For(i,1,n) val[i]=read();
    For(i,1,n-1) if(val[i]>val[i+1]) st.insert(i),st2.insert(-i); 
    st.insert(0),st.insert(n),st2.insert(0),st2.insert(-n); // 注意这里不要漏掉
    For(i,1,n)
    {
        int pos=*st.lower_bound(i);
        num[i]=pos-i+1;
    }
    Build(1,n,1);
    while(q--)
    {
        int opt=read(),x=read(),y=read();
        if(opt==1)
        {
            int pre=val[x]; val[x]=y;
            if(val[x-1]<=pre && val[x-1]>val[x]) Add(x-1);
            if(val[x-1]>pre && val[x-1]<=val[x]) Del(x-1);
            if(pre<=val[x+1] && val[x]>val[x+1]) Add(x);
            if(pre>val[x+1] && val[x]<=val[x+1]) Del(x);
        }
        else
        {
            if(val[y]<=val[y+1]) Add(y);
            ll ans=Count(1,n,x,y,1);
            printf("%lld\n",ans);
            if(val[y]<=val[y+1]) Del(y);
        }
    }
    return 0;
}
```



---

## 作者：清烛 (赞：2)

## Description
单点修改序列，区间查询不降子段个数。

注意子段是连续的子段。

## Solution
考虑使用线段树维护一个区间内的答案。

发现，如果要合并左右两个子区间，则可能左边的极右子段会和右边的极左子段发生合并，这样子对答案产生的贡献为这两段长度之积（组合意义就是新产生的是跨越中点的子段，左端点能取的个数乘上右端点能取的个数）

所以，线段树内需要维护的信息就有不降子段个数，极左最长子段长度，极右最长子段长度。

当然，需要注意一下细节：如果一个区间一整个就是一个不降子段，向上合并时产生的极左/右子段长度就会跨越端点，注意合并即可。

答案上界会爆 `int`，详见代码。

## Implementation
```cpp
#include <cstdio>
#include <cctype>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

namespace fastIO {...} // namespace fastIO

using namespace fastIO;

typedef long long ll;

const int maxn = 2e5 + 5;

int val[maxn];

struct node {
    int l, r;
    ll ans, lenl, lenr;
    bool isone;
    node() {l = r = ans = lenl = lenr = 0; isone = 0;}
    il friend node operator+(const node &a, const node &b) {
        node ret;
        ret.ans = a.ans + b.ans;
        if (val[a.r] <= val[b.l]) ret.ans += a.lenr * b.lenl;
        ret.l = a.l, ret.r = b.r, ret.lenl = a.lenl, ret.lenr = b.lenr;
        if (a.isone && val[a.r] <= val[b.l]) ret.lenl += b.lenl;
        if (b.isone && val[a.r] <= val[b.l]) ret.lenr += a.lenr;
        ret.isone = a.isone && b.isone && (val[a.r] <= val[b.l]);
        return ret;
    }
} t[maxn << 2];

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

void build(int i, int j, int k) {
    t[k].l = i, t[k].r = j;
    if (i == j) {
        read(val[i]);
        t[k].lenl = t[k].lenr = t[k].isone = t[k].ans = 1;
        return;
    }
    build(i, M, L);
    build(M + 1, j, R);
    t[k] = t[L] + t[R];
    return;
}

void modify(int i, int j, int k, int x, int v) {
    if (i == j) {
        val[i] = v;
        t[k].lenl = t[k].lenr = t[k].isone = t[k].ans = 1;
        return;
    }
    if (x <= M) modify(i, M, L, x, v);
    else modify(M + 1, j, R, x, v);
    t[k] = t[L] + t[R];
    return;
}

node query(int i, int j, int k, int x, int y) {
    if (x <= i && y >= j) return t[k];
    if (y <= M) return query(i, M, L, x, y);
    if (x > M) return query(M + 1, j, R, x, y);
    return query(i, M, L, x, y) + query(M + 1, j, R, x, y);
}

int main() {
    int n, q; read(n), read(q);
    build(1, n, 1);
    while (q--) {
        int op, x, y;
        read(op), read(x), read(y);
        if (op == 1) modify(1, n, 1, x, y);
        else print(query(1, n, 1, x, y).ans), putchar('\n');
    }
    return output(), 0;
}
```

---

## 作者：KSToki (赞：2)

# 题目大意
给定长度为 $n$ 的序列，支持单点修改，区间查询不降子区间数量。
# 题目分析
~~唯一指定数据结构题~~。我们需要一个 $O(nlogn)$ 的算法来解决，而这种花里胡哨的东西树状数组不好维护，于是选择使用类似于 GSS 系列的线段树来维护，记录一个区间的答案数 $ans$、左端点为最左能扩展多少 $lans$、右端点为最右能扩展多少 $rans$。

考虑如何合并两个区间，基础转移就不说了，对于 $lans$，如果左区间能取满再判断考虑右区间，$rans$ 同理。对于 $ans$，类似于分治，左区间答案和右区间答案肯定是要加的，还需计算跨区间的，这时判断是否能跨区间，再利用之前维护的 $lans$ 和 $rans$ 就可以了。

总体来说是比较套路的，和板子的唯一区别就是对线段树合并区间的灵活处理。
# 代码
```cpp
#include<bits/stdc++.h>
#define YPC rubbish 
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define LL __int128
#define db double
using namespace std;
#define pb push_back
#define pii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first
#define se second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define chkmin(x,y) (x=min(x,y))
#define chkmax(x,y) (x=max(x,y))
#define inv(x) ksm(x,mod-2)
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
#define For(i,x,y) for(R int i=x;i<=y;++i)
#define For2(i,x,y,k) for(R int i=x;i<=y;i+=k)
#define Rof(i,x,y) for(R int i=x;i>=y;--i)
#define Rof2(i,x,y,k) for(R int i=x;i>=y;i-=k)
#define ForG(i,edge,x) for(auto i:edge[x])
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
struct tree
{
	int l,r,siz;
	ll lans,rans;
	ll ans;
}t[800001];
int n,q,a[200001],op,x,y;
tree merge(tree t1,tree t2)
{
	tree res;
	res.l=t1.l;
	res.r=t2.r;
	res.siz=t1.siz+t2.siz;
	if(t1.lans==t1.siz&&a[t1.r]<=a[t2.l])
		res.lans=t1.lans+t2.lans;
	else
		res.lans=t1.lans;
	if(t2.rans==t2.siz&&a[t1.r]<=a[t2.l])
		res.rans=t1.rans+t2.rans;
	else
		res.rans=t2.rans;
	res.ans=t1.ans+t2.ans+(a[t1.r]<=a[t2.l])*t1.rans*t2.lans;
	//printf("%d %d %d %lld %lld %lld\n",t1.l,t1.r,t1.siz,t1.lans,t1.rans,t1.ans);
	//printf("%d %d %d %lld %lld %lld\n",t2.l,t2.r,t2.siz,t2.lans,t2.rans,t2.ans);
	//printf("%d %d %d %lld %lld %lld\n",res.l,res.r,res.siz,res.lans,res.rans,res.ans);
	return res;
}
void build(int k,int l,int r)
{
	if(l==r)
	{
		t[k].l=t[k].r=l;
		t[k].siz=t[k].lans=t[k].rans=t[k].ans=1;
		a[l]=read();
		return;
	}
	int mid=(l+r)>>1;
	build(k<<1,l,mid);
	build((k<<1)|1,mid+1,r);
	t[k]=merge(t[k<<1],t[(k<<1)|1]);
}
void update(int k,int l,int r,int x,int v)
{
	if(l==r)
	{
		a[l]=v;
		return;
	}
	int mid=(l+r)>>1;
	if(mid>=x)
		update(k<<1,l,mid,x,v);
	else 
		update((k<<1)|1,mid+1,r,x,v);
	t[k]=merge(t[k<<1],t[(k<<1)|1]);
}
tree query(int k,int l,int r,int x,int y)
{
	if(l>=x&&r<=y)
		return t[k];
	int mid=(l+r)>>1;
	if(mid>=y)
		return query(k<<1,l,mid,x,y);
	if(mid+1<=x)
		return query((k<<1)|1,mid+1,r,x,y);
	return merge(query(k<<1,l,mid,x,y),query((k<<1)|1,mid+1,r,x,y));
}
int main()
{
	n=read();
	q=read();
	build(1,1,n);
	while(q--)
	{
		op=read();
		x=read();
		y=read();
		if(op==1)
			update(1,1,n,x,y);
		else 
			putll(query(1,1,n,x,y).ans);
	}
	return 0;
}

```

---

## 作者：unputdownable (赞：1)

## 题意简述

有一个长度为 $n$ 的数组 $a$，你需要支持以下两种操作：

- ``1 x y``：将 $a_x$ 修改为 $y$。
- ``2 l r``：求有多少个数对 $(p,q)$ 满足 $l \leq p \leq q \leq r$，且 $a_p \leq a_{p+1} \leq \cdots \leq a_{q-1} \leq a_{q}$。

## 题解

由于不会写平衡树，这里提供一种 set 加线段树的做法。（注：set 可以使用线段树上二分代替）

注意到对于 $(l,r)$ 区间中的一段长度为 $len$ 的极长不降子串能对答案造成 $\frac {(len+2)\times (len+1)} 2$ 的贡献，于是我们定义一个满足 $a_{i-1}>a_i$ 的 $i$ 为断点。

考虑把贡献拆到单点，对于 $i$，设 $i$ 之前最后一个断点在 $lst$，那么 $q=i$ 的数对 $(p,q)$ 就有 $i-lst+1$ 个。

注意对于查询时，$l$ 也要被算作一个断点，因为不能继续往前取了。

那么对于每次查询，只要插入一个断点 $l$，再查询 $i-lst+1$ 的区间和即可，最后删去断点 $l$。**若 $l$ 在数组中本身就是断点，注意不要误删**

由于答案只和断点有关，所以单修 $i$ 的时候只要检查 $i$ 和 $i+1$ 处有没有断点。 

上面的用线段树维护即可。

--------

最后考虑如何添加或删除断点。

首先把现有的所有断点插入到一个 set 中。

假设我要插入一个断点 $x$，查找出 $x$ 左右的第一个断点，记为 $s,t$。

那么原先对于 $[s,t-1]$ 的区间，贡献都是 $i-s+1$。

修改后对于 $[s,x-1]$ 的区间，贡献仍是 $i-s+1$，对于 $[x,t-1]$ 的区间，贡献变为 $i-x+1$。

因此，操作相当于对 $[x,t-1]$ 区间减去 $x-s$。

删去断点的操作同理，最终转化成对 $[x,t-1]$ 区间加上 $x-s$。

注意在 $1$ 处和 $n+1$ 处预设断点。

[**Code**](https://codeforces.com/contest/1567/submission/128039120)

---

## 作者：yzy1 (赞：1)

## 题目大意

单点修改，区间严格不降子区间计数。

## 简要做法

考虑分块，每个块内维护所有极大不降区间的两个端点。这样一个长度为 $L$ 的极大不降区间的对答案的贡献就为 $\sum_{i=1}^L i$。

对于单点修改，直接暴力重构整个块。

比较麻烦的是块与块之间的拼接，我们可以记录「最后一个遍历到的区间」是什么，然后在遍历到一个新块时判断这个块的第一个元素是否大于等于上一个块的最后一个元素，如果是则可以将这个块的第一个极大区间和「最后一个遍历到的区间」进行合并。

时间复杂度 $O(n+q\sqrt n)$，空间复杂度 $O(n)$。可以通过此题。

```cpp
int bl[N], lbl[N], rbl[N], a[N], sz, n, m, sum[N];
vector<pair<int, int>> vec[N];

int Sum(int x) { return x * (x + 1) / 2; }

void Up(int x) {
  int b = bl[x];
  vec[b].clear();
  vec[b].push_back({lbl[x], lbl[x]});
  rep (i, lbl[x] + 1, rbl[x]) {
    if (a[i - 1] <= a[i])
      ++vec[b].back().second;
    else
      vec[b].push_back({i, i});
  }
  sum[b] = 0;
  each (x, vec[b])
    sum[b] += Sum(x.second - x.first + 1);
}

void Init() {
  sz = max((ll)sqrt(n), 3ll);
  rep (i, 1, n) {
    bl[i] = (i - 1) / sz + 1;
    lbl[i] = (bl[i] - 1) * sz + 1;
    rbl[i] = min(bl[i] * sz, n);
  }
  ste(i, 1, n, sz) Up(i);
}

void Set(int p, int x) {
  a[p] = x;
  Up(p);
}

int Ask(int l, int r) {
  int res = 0;
  if (bl[l] == bl[r]) {
    vector<pair<int, int>> v;
    v.push_back({l, l});
    rep (i, l + 1, r) {
      if (a[i - 1] <= a[i])
        ++v.back().second;
      else
        v.push_back({i, i});
    }
    each (x, v)
      res += Sum(x.second - x.first + 1);
    return res;
  }
  res += Ask(l, rbl[l]);
  pair<int, int> lst = vec[bl[l]].back();
  up(lst.first, l);
  ste(i, lbl[l] + sz, rbl[r] - sz, sz) {
    int b = bl[i];
    res += sum[b];
    // 拼接
    if (a[lbl[i] - 1] <= a[lbl[i]]) {
      res -= Sum(vec[b][0].second - vec[b][0].first + 1);
      res -= Sum(lst.second - lst.first + 1);
      res += Sum(vec[b][0].second - lst.first + 1);
      up(lst.second, vec[b][0].second);
    }
    if (lst.second != rbl[i]) lst = vec[b].back();
  }
  if (a[lbl[r] - 1] <= a[lbl[r]]) {
    res -= Sum(min(r, vec[bl[r]][0].second) - vec[bl[r]][0].first + 1);
    res -= Sum(lst.second - lst.first + 1);
    res += Sum(min(r, vec[bl[r]][0].second) - lst.first + 1);
  }
  res += Ask(lbl[r], r);
  return res;
}
```





---

## 作者：云浅知处 (赞：1)

CF の憨憨数据结构题（

题意：你需要维护一个序列，支持以下两种操作：

- 单点修改
- 查询 $[l,r]$ 内有多少个单调不降的连续子区间。

考虑用线段树维护。由于只有单点修改，我们只需要思考如何合并两个区间的信息。

首先按照套路，我们把区间内的不降子段分为两种：

- 完全在左儿子内的
- 完全在右儿子内的
- 跨越区间中点的

对于前两种可以直接将左右儿子的答案加起来得到。

对于第三种，我们考虑对每个节点额外维护从区间 左/右 端点开始能够往 右/左 延伸且使得这一段一直单调不降的最大长度，稍加思考可以发现第三种子区间的个数就是把这两个数乘起来得到的值。

注意，由于区间中点两端的数的大小关系我们并不能确定，因此我们还需要维护每个节点的左右端点上的值来进行判断。

具体实现还有一些细节，看代码

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<vector>

#define int long long
#define lson(o) (o<<1)
#define rson(o) (o<<1|1)
const int MN=2e5+5;

using namespace std;

inline int read(){
    int x=0,f=1;char c=getchar();
    for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
    for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
    return x*f;
}

struct Node{
    int l,r,d,L,R;
    bool tag;
    Node(int ll,int rr,int dd,int LL,int RR,bool tt):l(ll),r(rr),d(dd),L(LL),R(RR),tag(tt){}
    Node(){}
};

int a[MN];

struct SegTree{

    Node d[MN<<2];

    inline Node merge(Node ls,Node rs){
        Node res;
        res.d=ls.d+rs.d;
        if(ls.R<=rs.L)res.d+=ls.r*rs.l;
        res.L=ls.L,res.R=rs.R,res.l=ls.l,res.r=rs.r;
        if(ls.tag&&ls.R<=rs.L)res.l+=rs.l;
        if(rs.tag&&ls.R<=rs.L)res.r+=ls.r;
        res.tag=(ls.tag&rs.tag&(ls.R<=rs.L));
        return res;
    }

    inline void build(int l,int r,int o){
        if(l==r){
            d[o]=Node(1,1,1,a[l],a[l],1);
            return ;
        }
        int mid=(l+r)>>1;
        build(l,mid,lson(o));
        build(mid+1,r,rson(o));
        d[o]=merge(d[lson(o)],d[rson(o)]);
    }

    inline void modify(int pos,int k,int ql,int qr,int o){
        if(ql==qr){d[o]=Node(1,1,1,k,k,1);return ;}
        int mid=(ql+qr)>>1;
        if(pos<=mid)modify(pos,k,ql,mid,lson(o));
        else modify(pos,k,mid+1,qr,rson(o));
        d[o]=merge(d[lson(o)],d[rson(o)]);
    }

    inline Node query(int l,int r,int ql,int qr,int o){
        if(l<=ql&&qr<=r)return d[o];
        int mid=(ql+qr)>>1;
        if(r<=mid)return query(l,r,ql,mid,lson(o));
        if(l>mid)return query(l,r,mid+1,qr,rson(o));
        return merge(query(l,r,ql,mid,lson(o)),query(l,r,mid+1,qr,rson(o)));
    }

}tree;

int n,q;

signed main(void){

    n=read(),q=read();
    for(int i=1;i<=n;i++)a[i]=read();

    tree.build(1,n,1);

    while(q--){
        int op=read(),x=read(),y=read();
        if(op==1)tree.modify(x,y,1,n,1);
        else cout<<tree.query(x,y,1,n,1).d<<endl;
    }

    return 0;
}
```

---

## 作者：zhangboju (赞：0)

### 题意简述

给定一个序列 $a_n$，要求支持如下操作：

```1 x y``` 表示将 $a_x$ 修改为 $y$

```2 l r``` 表示查询在 $[l,r]$ 内有多少个单调不降的子区间

### 具体思路

考虑只有单点修改和区间查询，我们或许可以考虑用线段树来维护这个操作。

首先发现对于序列中任意一个长度为 $len$ 的 **极大的** 单调不降子序列，它对答案的贡献就是 $\dfrac{len\times (len-1)}{2}$

这是我们做这个问题的基础。

而又考虑到线段树可以维护最长单调不降区间，具体做法是我们维护一个点的信息有：

1. 区间内最长单调不降区间长度

2. 区间内以区间右端点为结尾的最长单调不降区间长度

3. 区间内以区间左端点为开头的最长单调不降区间长度

在 ```pushup``` 的时候讨论一下，具体就是：

1. 区间内最长单调不降区间长度为左右儿子该信息的最大值和合并左右儿子产生的新贡献的最大值

2. 区间内以区间右端点为结尾的最长单调不降区间长度为右儿子该信息与合并左右儿子产生的新贡献的最大值

3. 区间内以区间左端点为结尾的最长单调不降区间长度为左儿子该信息与合并左右儿子产生的新贡献的最大值

太抽象了，具体可以看下面的代码：

```cpp
// maxx 区间内最长单调不降区间长度
// len1 区间内以区间左端点为开头的最长单调不降区间长度 
// len2 区间内以区间右端点为结尾的最长单调不降区间长度
void merge(node x,node y)// 合并两个相邻区间 
{
	node c;
	c.l=x.l,c.r=y.r;
	c.maxx=max(max(x.maxx,y.maxx),(a[x.r]<=a[y.l])*(x.len2+y.len1));
	c.len1=x.len1,c.len2=y.len2;
	if(y.len2==y.r-y.l+1&&a[x.r]<=a[y.l]) c.len2=x.len2+y.len2;
	if(x.len1==x.r-x.l+1&&a[x.r]<=a[y.l]) c.len1=x.len1+y.len1;
	return c;
}
void pushup(int u)
{
	tr[u]=merge(tr[u<<1],tr[u<<1|1]);
}
```
至此这道题解决了一大半。

我们只需要将维护的第一个信息改为 **区间内所有极大的最长单调不降子序列对答案的贡献即可**。

使用类似的方法在线段树上维护，时间复杂度 $O(n \log n)$

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
template <typename T> inline void read(T &x)
{
	x=0;short f=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	x*=f;return;
}
const int N=6e5+5;
#define ll long long
struct node{
	int l,r;
	ll sum;
	int len1,len2;
}tr[N*4];
int a[N];
node merge(node x,node y)
{
	node c;
	c.l=x.l,c.r=y.r;
	c.sum=x.sum+y.sum;
	if(a[x.r]<=a[y.l]) 
		c.sum=x.sum+y.sum-1ll*y.len1*(y.len1-1)/2-1ll*x.len2*(x.len2-1)/2+1ll*(y.len1+x.len2)*(y.len1+x.len2-1)/2;
	c.len1=x.len1,c.len2=y.len2;
	if(y.len2==y.r-y.l+1&&a[x.r]<=a[y.l]) c.len2=x.len2+y.len2;
	if(x.len1==x.r-x.l+1&&a[x.r]<=a[y.l]) c.len1=x.len1+y.len1;
	return c;
}
void pushup(int u)
{
	tr[u]=merge(tr[u<<1],tr[u<<1|1]);
}
void build(int u,int l,int r)
{
	tr[u].l=l,tr[u].r=r;
	if(l==r)
	{
		tr[u].sum=tr[u].len1=tr[u].len2=1;
		return;
	}
	int mid=l+r>>1;
	build(u<<1,l,mid),build(u<<1|1,mid+1,r);
	pushup(u);
}
void modify(int u,int pos)
{
	if(tr[u].l==tr[u].r) return;
	int mid=tr[u].l+tr[u].r>>1;
	if(pos<=mid) modify(u<<1,pos);
	else modify(u<<1|1,pos);
	pushup(u);
}
node query(int u,int l,int r)
{
	if(l<=tr[u].l&&tr[u].r<=r) return tr[u];
	int mid=tr[u].l+tr[u].r>>1;
	if(l<=mid&&r>mid) return merge(query(u<<1,l,r),query(u<<1|1,l,r));
	if(l<=mid) return query(u<<1,l,r);
	if(r>mid) return query(u<<1|1,l,r);
}
int n,m;
int main()
{
	read(n),read(m);
	for(int i=1;i<=n;++i) read(a[i]);
	build(1,1,n);
	while(m--)
	{
		int op,l,r;
		read(op),read(l),read(r);
		if(op==1) a[l]=r,modify(1,l);
		else printf("%lld\n",query(1,l,r).sum);
	}
	return 0;
}
```




---

## 作者：Jimmy2020 (赞：0)

## 题意

给定序列 $\{a\}$，支持一下两种操作：

1. 输入 $x,y$，将 $a_x$ 改为 $y$
2. 输入 $l,r$，求 $l,r$ 中有多少对 $(p,q)$ 满足 $a_p,a_{p+1},\cdots,a_q(l\leq p\leq q\leq r)$ 单调不降。

## 解法

考虑线段树：线段树每个节点维护以下信息：

- $l,r$：区间左右端点（闭区间）
- $lsum$：从左端点开始的最长单调不降区间长度
- $rsum$：以右端点结束的最长单调不降区间长度
- $dat$：区间中满足 $a_p,a_{p+1},\cdots,a_q$ 单调不降的 $(p,q)$ 个数 

接下来考虑标记更新的问题（记当前考虑到的节点为 $p$，要合并节点 $ls$，$rs$（$ls$ 在左，$rs$ 在右） 的信息）：

- $l,r$：很简单，此处略
- $lsum$：分情况讨论：若该节点维护的所有数满足单调不降，并且 $ls$ 的末尾小于等于 $rs$ 的开始（简单来讲，就是左节点能跟右节点拼起来，使得从左节点的最左端一直延伸到右节点的区间都满足单调不降）则 $lsum$ 等于左区间长度加上右区间 $lsum$；否则直接赋为左区间的 $lsum$
- $rsum$ 可用类似方法维护，具体看代码
- $dat$ 先考虑不跨区的区间，它的个数就等于左右节点的 $dat$ 之和；再考虑跨区的，显然需要满足左区间的右端点值小于等于右区间的左端点值。这时，由乘法原理，有 $ls.rsum \times rs.lsum$ 个区间。两种情况加起来即可。

（实现细节可以参考代码）

贴代码：
```cpp
#include <cstdio>
#define ls(p) p<<1
#define rs(p) p<<1|1

const int N = 200010;
typedef long long ll;

int a[N], n, m;

struct segment_tree{
    struct seg_Node{
        int l, r; ll lsum, rsum, dat;
        #define l(p) tree[p].l
        #define r(p) tree[p].r
        #define lsum(p) tree[p].lsum
        #define rsum(p) tree[p].rsum
        #define dat(p) tree[p].dat
        #define len(p) (r(p) - l(p) + 1)
    }tree[N<<2];
    void update(int p){
        dat(p) = dat(ls(p)) + dat(rs(p)); // 情况1
        ll k = a[l(rs(p))] >= a[r(ls(p))] ? lsum(rs(p)) * rsum(ls(p)) : 0; // 情况2
        dat(p) += k;
        lsum(p) = lsum(ls(p)) == len(ls(p)) && a[l(rs(p))] >= a[r(ls(p))] ? len(ls(p)) + lsum(rs(p)) : lsum(ls(p));
        rsum(p) = rsum(rs(p)) == len(rs(p)) && a[l(rs(p))] >= a[r(ls(p))] ? len(rs(p)) + rsum(ls(p)) : rsum(rs(p));
    }
    void build(int p, int l, int r){
        l(p) = l; r(p) = r;
        if(l == r){
            dat(p) = lsum(p) = rsum(p) = 1;
            return;
        }
        int mid = (l+r) >> 1;
        build(ls(p), l, mid);
        build(rs(p), mid+1, r);
        update(p);
    }
    seg_Node query(int p, int l, int r){ // 查询，需要把 [l,r] 分成的所有节点合并起来
        if(l <= l(p) && r >= r(p)) return tree[p];
        int x = (l(p) + r(p)) >> 1;
        if(r <= x) return query(ls(p), l, r);
        if(l > x) return query(rs(p), l, r);
        seg_Node ans, ql, qr;
        ql = query(ls(p), l, r), qr = query(rs(p), l, r);
        ans.lsum = ql.lsum == ql.r-ql.l+1 && a[qr.l] >= a[ql.r] ? ql.r-ql.l+1 + qr.lsum : ql.lsum;
        ans.rsum = qr.rsum == qr.r-qr.l+1 && a[qr.l] >= a[ql.r] ? qr.r-qr.l+1 + ql.rsum : qr.rsum;
        ans.r = qr.r; ans.l = ql.l;
        ans.dat = ql.dat + qr.dat + (a[qr.l] >= a[ql.r] ? ql.rsum * qr.lsum : 0);
        return ans;
    }
    ll querys(int l, int r){
         return query(1, l, r).dat;
    }
    void change(int p, int k, int y){ // 修改
        if(l(p) == r(p)) {
            a[k] = y;
            return;
        }
        int mid = (l(p) + r(p)) >> 1;
        if(k <= mid) change(ls(p), k, y);
        else change(rs(p), k, y);
        update(p);
    }
}T;

int x, y, opt;

int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    T.build(1, 1, n);
    while(m--){
        scanf("%d%d%d", &opt, &x, &y);
        if(opt == 1) T.change(1, x, y);
        else printf("%lld\n", T.querys(x, y));
    }
    return 0;
}
```

---

## 作者：Zxsoul (赞：0)

# CF1567E Non-Decreasing Dilemma

**题目简述**：在单点修改的情况下，求出区间单调不递减的区间个数。

**前言**

看[题解视频](https://www.youtube.com/watch?v=CIgm0HMJj3M)学到了关于线段树分段处理的方法，这很套路。

**思路**

首先显然的是这需要用数据结构去维护，其次我们发现维护的东西不是单一的某个最值，或者区间和，区间 GCD 之类的。要想知道区间满足要求的数量，我们一般有两种想法：

- 暴力求解，知道区间各个之间的情况。
- 分段处理，递归合并，注意点是合并时产生的组合贡献。

第二种就是此题线段树的做法，在视频主人介绍这是一种**基于正确的两端**，并且基于该连续性的情况下践行累加的一种分段线段树做法。感觉像分治，可修改的分治。

具体话：对于一个区间，我们维护三个值：$sum,lenl,lenr$ 分别对应区间个数，从左边第一个连续不递减的序列，和右边最后一个连续不递减的序列，直观的讲如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/muc854fr.png)

只要保证一个区间的 $lenl,lenr,sum$ 是正确的，考虑如何合并，合并时会发生左区间 $lenr$ 和右区间的 $lenl$ 是否可以合并，判断条件是俩区间的端点是否满足单调不减。合并时还有更新大区间的 $len1,lenr$ 基本都是看各自区间的另一部分是否可以拼到对方的尾部或者头部。然后就愉快的AC了。

```c
#include <iostream>
#include <cstdio>
#include <algorithm>
#define int long long
#define root 1,n,1
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
using namespace std;
const int B=2e5+10;
int n,v[B];
int read() {int x;scanf("%lld",&x);return x;}
int ark; 
int ans;
namespace Seg
{
	struct node
	{
		int l,r;
		int sum,lenl,lenr;
		node() {l=r=sum=lenl=lenr=0;}
		void init(int l_,int r_) {l=l_,r=r_,sum=1,lenl=lenr=1;}
	}z[B<<2];
	node operator + (const node &l, const node &r)
	{
		node p;
		p.l=l.l, p.r=r.r, p.sum=l.sum+r.sum;
		p.lenl=l.lenl, p.lenr=r.lenr;
		if (l.lenl==(l.r-l.l+1) && v[l.r]<=v[r.l]) p.lenl+=r.lenl;
		if (r.lenr==(r.r-r.l+1) && v[l.r]<=v[r.l]) p.lenr+=l.lenr;
		if (v[l.r]<=v[r.l]) p.sum+=l.lenr*r.lenl;
 		return p;	
	}
	void update(int rt) {z[rt]=z[rt<<1]+z[rt<<1|1];}
	void build(int l,int r,int rt)
	{
		if (l==r) {z[rt].init(l,r); return;}
		int m=l+r>>1;
		build(lson); build(rson);
		update(rt); 
	}
	void modify(int l,int r,int rt,int x,int w)
	{
		if (l==r) 
		{
			v[x]=w;
			return;
		}
		int m=l+r>>1;
		if (x<=m) modify(lson,x,w);
		else modify(rson,x,w);
		update(rt);
	}
	node query(int l,int r,int rt,int nowl,int nowr)
	{
 		if (nowl<=l && r<=nowr)	return z[rt];
		int m=l+r>>1;
		if (nowl<=m)
		{
			if (m<nowr) 
			{
				node s1=query(lson,nowl,nowr);
				node s2=query(rson,nowl,nowr);
				return s1+s2;
			}
			return query(lson,nowl,nowr); 
		}
		return query(rson,nowl,nowr);
	}
}
int q;
signed main()
{
	n=read(),q=read();
	for (int i=1;i<=n;i++) v[i]=read();
	Seg::build(root);
	for (int i=1;i<=q;i++)
	{
		int opt=read(),l=read(),r=read();
		if (opt==2)
		{
			Seg::node ans2=Seg::query(root,l,r);
			printf("%lld\n",ans2.sum);
		}
		else 
		{
			Seg::modify(root,l,r);
		} 
	}	
}
/*
5 6
3 1 4 1 5
2 2 5
2 1 3
1 4 4
2 2 5
1 2 6
2 2 5
*/
```

 



---

