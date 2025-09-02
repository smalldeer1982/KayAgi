# [IOI 2007] sails 船帆

## 题目描述

让我们来建造一艘新的海盗船。船上有 N个旗杆，每根旗杆被分成单位长度的小节。旗杆的长度等于它被分成的小节的数目。每根旗杆上会挂一些帆，每张帆正好占据旗杆上的一个小节。在一根旗杆上的帆可以任意排布在不同的小节中，但是每个小节上至多能挂一张帆。

在风中，帆的不同排布方式会产生不同的推动力。靠近船头的帆比它后面的相同高度上的帆获得的推动力少，换句话说，靠近船头的帆的推动力由于受它后面相同高度的帆的影响而打了折扣。对于任意一张帆，它的推动力折扣等于在它后面并且和它在同一高度的帆的数目。

所有帆的任意一种位置组合的推动力折扣总和等于在该位置下所有帆的推动力折扣的总和。

![](https://cdn.luogu.com.cn/upload/pic/20670.png )

这条船上有6个旗杆，从前（图上的左边）到后的高度分别是3，5，4，2，4和3。图中所示的帆的位置组合的总推动力折扣是10。上图给出了每张帆自己的推动力折扣。

给定N个旗杆的高度和每个旗杆上挂的帆的数目，写一个程序求出所有位置组合中的可能达到的最小的总推动力折扣。 

## 说明/提示

这个样例数据和上页中图示的样例相同。

在 25 分的测试数据中，帆的不同位置组合的总数目不超过 $1,000,000$ 。

## 样例 #1

### 输入

```
6 
3 2 
5 3 
4 1 
2 1 
4 3 
3 2 ```

### 输出

```
10```

# 题解

## 作者：Diaоsi (赞：12)

[[IOI2007] sails 船帆](https://www.luogu.com.cn/problem/P4647)

>怎么大家写的都是线段树/平衡树，一个树状数组不就可以搞定了么...

提供一个 $\mathcal{O(n\log n)}$ 的树状数组做法。

首先将 $h_i$ 按照升序排序，按顺序考虑每个柱子，在高度 $1 \sim h_i$ 中找到旗帜数量最少的 $k$ 个高度放上 $k$ 面旗，因为 $h_i$ 越大可选择的位置就越多，所以将 $h_i$ 越大的放在后面考虑才能保证答案最小。

设 $s_i$ 表示高度 $i$ 上有 $s_i$ 面旗帜，维护 $s_i$ 单调不升，这样每次找的旗帜数量最少的 $k$ 个高度就对应了 $s_i$ 上的某段区间，不难发现这段区间就是 $[h_i-k_i+1,h_i]$ 。

但是这样会出现一个问题，如果直接更新 $[h_i-k_i+1,h_i]$ 上的值，会破坏 $s_i$ 序列的单调性（ $\exists \varepsilon ,\varepsilon < h_i-k_i+1,s_{\varepsilon}=s_{h_i-k_i+1}$ ），由于一个高度只能放一面旗帜，所以破坏单调性的只会是 $[h_i-k_i+1,h_i]$ 的一段前缀，考虑将这段前缀前移。

令 $l,r$ 表示 $s_{h_i-k_i+1}$ 出现范围的左端点和右端点，转化为修改 $[l,l+r-(h-k+1)]$ 和 $[r+1,h]$ 两段区间，既维护了单调性，又满足了贪心的条件。

考虑用树状数组维护 $s_i$ ，区间修改转化为差分数组上的单点修改，单点求值转化为前缀求和，由于 $s_i$ 单调不降，$l,r$ 可以在树状数组上通过倍增求出。

具体地说，设树状数组为 $c$ ，维护的序列是 $a$ ，由于树状数组的性质，$c[x]$ 保存的信息是 $\sum_{i=x-\text{lowbit}(x)+1}^xa_i$ ，区间的长度是二的整数次幂，而在树状数组上求和的过程则类似于对某个数进行二进制拆分。

设 $\text{pos}$ 表示最后一个满足 $s_{\text{pos}}>s_{h_i-k_i+1}$ 的位置，令 $\text{sum}$ 模拟在树状数组上求和。

以 $l$ 的求值为例，初始时 $\text{pos}=0,\text{sum}=0$ ，从 $\log h_i$ 到 $0$ 倒序考虑每一个数 $p$ ，若满足 $\text{pos}+2^p \leq h_i$ 且 $\text{sum}+c[\text{pos}+2^p]>s_{h_i-k_i+1}$ ，则更新 $\text{pos}$ 和 $\text{sum}$ 的值，让 $\text{pos}$ 前进 $2^p$ 步，最后 $l$ 就是 $\text{pos}+1$ 。

同理， $r$ 也可以通过同样的办法求出，相比在树状数组上二分，倍增将复杂度降至单次 $\mathcal{O(\log n)}$ 。

最后求出每个 $s_i$ ，计算 $\sum\dfrac{1}{2}s_i(s_i-1)$ 求得答案。

总时间复杂度为 $\mathcal{O(n\log n)}$ ，由于树状数组常数较小，在没有特意卡常和精细实现的情况下都能跑到最优解（261ms），吊打一众线段树/平衡树写法（码量也是最小的）。

```Code:```
```cpp
#include<bits/stdc++.h>
typedef long long LL;
typedef long double LD;
using namespace std;
const LL N=100010,M=1000010,INF=0x3f3f3f3f;
inline LL max(LL x,LL y){return x>y?x:y;}
inline LL min(LL x,LL y){return x<y?x:y;}
inline void swap(LL &x,LL &y){x^=y^=x^=y;}
LL n,w,ans,c[N];
struct node{LL h,k;}a[N];
bool cmp(node a,node b){return a.h<b.h;}
void add(LL x,LL y){
	for(;x<N;x+=x&-x)c[x]+=y;
}
LL ask(LL x){
	LL res=0;
	for(;x;x-=x&-x)res+=c[x];
	return res;
}
void upd(LL l,LL r,LL d){
	if(l>r)return;
	add(l,d),add(r+1,-d);
}
int main(){
	scanf("%lld",&n);
	for(LL i=1;i<=n;i++)
		scanf("%lld%lld",&a[i].h,&a[i].k);
	sort(a+1,a+n+1,cmp);
	for(LL i=1;i<=n;i++){
		int h=a[i].h,k=a[i].k;
		LL val=ask(h-k+1),l=0,r=0;
		for(LL j=17,sum=0;j>=0;j--)
			if(l+(1<<j)<=h&&sum+c[l+(1<<j)]>val)sum+=c[l+(1<<j)],l+=(1<<j);
		for(LL j=17,sum=0;j>=0;j--)
			if(r+(1<<j)<=h&&sum+c[r+(1<<j)]>=val)sum+=c[r+(1<<j)],r+=(1<<j);
		l=max(l+1,1);r=min(r,h);w=max(w,h);
		upd(r+1,h,1),upd(l,l+r-(h-k+1),1);
	}
	for(LL i=1;i<=w;i++){
		LL p=ask(i);
		ans+=p*(p-1)>>1;
	}
	printf("%lld\n",ans);
	return 0;
}
```





---

## 作者：pigstd (赞：10)

讲一个详细的选段树方法。

我们令 $S_i$ 表示高度 $i$ 中有 $S_i$ 个船帆，那么答案就是 $\sum\limits_{i=1}^n{\dfrac {Si \times (S_i - 1)}{2}}$。

很容易想到一个正确的贪心：每次都给 $S_i$ 最小的值加上船帆，即让 $S_i$ 的分部尽量均衡。

显然这个和杆的顺序没有排序，那么我们先把每个杆子对 $h_i$ 排序。每次我们都需要在 $1 - h_i$ 中找到前 $k_i$ 小的 $S_i$ 并对他们 $+1$，然而这样的时间复杂度是过不去的。

每次找最小是很麻烦的，我们考虑直接让 $S_i$ 降序。举个例子：当 $\{ S \} =\{ 5,4,3,3,3,2,1 \}$，$h_i = 7$，$k_i=3$ 的时候，$\{ S' \} =\{ 5,4,4,3,3,3,2 \}$ ，与原来相比，只有两段内容改变了。

那么具体的操作是这样的：对于每个 $h$ 与 $k$，先找出 $S_{h-k+1}$ 的值 $p$，再找到 $p$ 出现的范围 $l,r$（即 $S_{l-1} \ne S_l = S_{l + 1} = … = S_{r} \ne S_{r+1}$），那么显然，只要让 $[r+1,h]$ 与 $[l,l + k -h +r-1]$ 这两段都 $+1$ 就可以了。

然后用线段树维护即可。

[code](https://www.luogu.com.cn/paste/c7dkaxlw)。

---

## 作者：Cyhlnj (赞：9)

帆的顺序对答案没有影响，如果一个高度有 $x$ 个，那么对答案的贡献就是 $\frac{x(x-1)}{2}$

帆的高度没有什么性质不好操作，那么我们考虑把其高度从小到大排序

这样就好贪心了，相当于每次可以使得高度增高，要选出最小的 $k$ 个高度使得其个数 $+1$

每次给前 $k$ 个 $+1$ 只会改变前 $k$ 个的最大值和 $k$ 个之外的大小关系

直接弄个平衡树删除再插入就好了，$fhqtreap$ 可能好写得多

```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;

namespace IO {
    const int maxn(1 << 21 | 1);

    char ibuf[maxn], *iS, *iT, c;
    int f;

    inline char Getc() {
        return iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, maxn, stdin), (iS == iT ? EOF : *iS++)) : *iS++;
    }

    template <class Int> inline void In(Int &x) {
        for (f = 1, c = Getc(); c < '0' || c > '9'; c = Getc()) f = c == '-' ? -1 : 1;
        for (x = 0; c >= '0' && c <= '9'; c = Getc()) x = (x << 1) + (x << 3) + (c ^ 48);
        x *= f;
    }
}

using IO :: In;

const int maxn(1e5 + 5);

int n, tag[maxn], ls[maxn], rs[maxn], sz[maxn], val[maxn], fix[maxn], rt, tot;
ll ans;

struct Sail {
	int h, k;

	inline bool operator <(Sail b) const {
		return h < b.h;
	}
} sl[maxn];

inline void Pushdown(int x) {
	if (!tag[x]) return;
	if (ls[x]) val[ls[x]] += tag[x], tag[ls[x]] += tag[x];
	if (rs[x]) val[rs[x]] += tag[x], tag[rs[x]] += tag[x];
	tag[x] = 0;
}

inline void Update(int x) {
	sz[x] = sz[ls[x]] + sz[rs[x]] + 1;
}

int Build(int l, int r) {
	if (l > r) return 0;
	int x = ++tot, mid = (l + r) >> 1;
	fix[x] = rand(), val[x] = 0;
	ls[x] = Build(l, mid - 1), rs[x] = Build(mid + 1, r);
	return Update(x), x;
}

void Split_sz(int x, int k, int &l, int &r) {
	if (!x) l = r = 0;
	else {
		Pushdown(x);
		if (sz[ls[x]] + 1 <= k) l = x, Split_sz(rs[x], k - sz[ls[x]] - 1, rs[x], r), Update(l);
		else r = x, Split_sz(ls[x], k, l, ls[x]), Update(r);
	}
}

void Split_val(int x, int k, int &l, int &r) {
	if (!x) l = r = 0;
	else {
		Pushdown(x);
		if (val[x] <= k) l = x, Split_val(rs[x], k, rs[x], r), Update(l);
		else r = x, Split_val(ls[x], k, l, ls[x]), Update(r);
	}
}

inline int Max(int x) {
	while (rs[x]) Pushdown(x), x = rs[x];
	return val[x];
}

int Merge(int x, int y) {
	if (!x || !y) return x | y;
	Pushdown(x), Pushdown(y);
	if (fix[x] > fix[y]) {
		rs[x] = Merge(rs[x], y);
		return Update(x), x;
	}
	else {
		ls[y] = Merge(x, ls[y]);
		return Update(y), y;
	}
}

void Dfs(int x) {
	if (!x) return;
	Pushdown(x);
	if (val[x]) ans += 1LL * val[x] * (val[x] - 1) >> 1;
	Dfs(ls[x]), Dfs(rs[x]);
}

int main() {
	srand(time(NULL)), In(n);
	for (int i = 1; i <= n; ++i) In(sl[i].h), In(sl[i].k);
	sort(sl + 1, sl + n + 1), rt = Build(1, sl[1].h);
	for (int i = 1, x, y, z; i <= n; ++i) {
		while (tot < sl[i].h) fix[++tot] = rand(), sz[tot] = 1, rt = Merge(tot, rt);
		Split_sz(rt, sl[i].k, x, y), ++val[x], ++tag[x];
		int mx = Max(x);
		Split_val(x, mx - 1, x, z), x = Merge(x, y);
		Split_val(x, mx, x, y), rt = Merge(Merge(x, z), y);
	}
	Dfs(rt), printf("%lld\n", ans);
    return 0;
}

```

---

## 作者：nosta (赞：6)

[更好的阅读体验](https://www.cnblogs.com/nosta/p/10557737.html)

显然答案与杆的顺序无关（按每个高度考虑）。

从高到低考虑杆，设此时的状态为$S$，$S[i]$是高度$i$的帆的数目，初始全为$0$，当前杆的高度为$h$，杆上需要放置的帆的数目为$k$，贪心地，假设两个高度的同等宜选，优先选择更高的；帆尽量放置在$S[i]=0(i\le h)$的高度上，若还有剩余，设剩下$t(t\le k)$个，则放置在除去以选择的高度以外，$S[i](i\le h)$前$t$小的位置。

整理一下，每次选出$S[1\cdots h]$中前$k$小的（相同大小选下标较大的）高度放置帆。

```xml
{5,3} 0 0 1 1 1  +0
{4,3} 1 1 2 1 1  +1
{4,1} 1 2 2 1 1  +1
{3,2} 2 2 3 1 1  +3
{3,2} 3 3 3 1 1  +4
{2,1} 3 4 3 1 1  +3
```

但是此时$S$似乎不好维护。。考虑将过程倒过来，从低到高考虑杆，（$S$一开始为空集，其余定义相同），假设两个高度同等宜选，优先选择更低的，其余大致相同。即每次选出$S[1\cdots h]$中前$k$小的（相同大小选下标较小的）高度放置帆。

```xml
{2,1} 1 0        +0
{3,2} 1 1 1      +0
{3,2} 2 2 1      +2
{4,1} 2 2 1 1    +0
{4,3} 3 2 2 2    +4
{5,3} 3 3 3 2 1  +4
```

这样用平衡树维护$S$（初始大小为0，每次长度变化时补0节点），每次查询全局前$k$小然后整体加一即可。（省去了下标范围的约束）。~~进一步可发现，连下标都不用维护了~~ 

---

巧妙的分割线

观察各个时态的$S$，发现它总是一个单调不增的序列，把某时态的$S$中相同且相邻分成一块，如图，蓝色方框表示将选出前$k$小的位置，注意被完全覆盖的块的高度可以直接区间+1，而割开的块区间+1的范围是反过来的，显然这样的块最多一块，于是可以上线段树来维护。

![pic](http://images.cnblogs.com/cnblogs_com/nosta/1423307/o_10557737.png)

答案也不用每步累加，设$S[i]$表示最终状态上高度为$i$的帆的数目，显然总答案是$\sum_i\frac{S[i](S[i]-1)}2$，这与因为从本文第一句照应。

```cpp
#include <bits/stdc++.h>
#define LL long long 
const int N=1e5+10;

namespace sgt {
	struct sgtNode {
		int mx,mn,add;
	} t[N<<2];
#define ls (x<<1)
#define rs (x<<1|1)
	void update(int x) {
		t[x].mx=std::max(t[ls].mx,t[rs].mx);
		t[x].mn=std::min(t[ls].mn,t[rs].mn);
	}
	void pushr(int x,int add) {t[x].mn+=add,t[x].mx+=add,t[x].add+=add;}
	void pushdown(int x) {
		if(t[x].add) pushr(ls,t[x].add),pushr(rs,t[x].add),t[x].add=0;
	}
	LL calc(int x,int l,int r) {
		if(l==r) return 1LL*t[x].mx*(t[x].mx-1)/2;
		int mid=(l+r)>>1; pushdown(x);
		return calc(ls,l,mid)+calc(rs,mid+1,r);
	}
	void build(int x,int l,int r) {
		t[x].mn=+1e9,t[x].mx=-1e9;
		if(l==r) return; int mid=(l+r)>>1;
		build(ls,l,mid); build(rs,mid+1,r);
	}
	void insert(int x,int l,int r,int p) {
		if(l==r) return void(t[x].mx=t[x].mn=0);
		int mid=(l+r)>>1; pushdown(x);
		if(p<=mid) insert(ls,l,mid,p);
		else insert(rs,mid+1,r,p);
		update(x);
	}
	void modify(int x,int l,int r,int L,int R) {
		if(L>R) return;
		if(L<=l&&r<=R) return pushr(x,1);
		int mid=(l+r)>>1; pushdown(x);
		if(L<=mid) modify(ls,l,mid,L,R);
		if(mid<R) modify(rs,mid+1,r,L,R);
		update(x);
	}
	int getVal(int x,int l,int r,int p) {
		if(t[x].mn==t[x].mx) return t[x].mn; 
		int mid=(l+r)>>1; pushdown(x);
		if(p<=mid) return getVal(ls,l,mid,p);
		else return getVal(rs,mid+1,r,p); 
	}
	int getRangeL(int x,int l,int r,int w) {
		if(l==r) return l;
		int mid=(l+r)>>1; pushdown(x);
		if(t[ls].mn<=w) return getRangeL(ls,l,mid,w);
		else return getRangeL(rs,mid+1,r,w);
	}
	int getRangeR(int x,int l,int r,int w) {
		if(l==r) return l;
		int mid=(l+r)>>1; pushdown(x);
		if(t[rs].mx>=w) return getRangeR(rs,mid+1,r,w);
		else return getRangeR(ls,l,mid,w);
	}
}

int n,m;
std::pair<int,int> a[N];

int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) {
		scanf("%d%d",&a[i].first,&a[i].second);
		m=std::max(m,a[i].first);
	}
	std::sort(a+1,a+n+1);
	sgt::build(1,1,m);
	for(int i=1,R=0; i<=n; ++i) {
		while(R<a[i].first) sgt::insert(1,1,m,++R);
		int pos=R-a[i].second+1; //被割开的位置 
		int val=sgt::getVal(1,1,m,pos);
		int rgl=sgt::getRangeL(1,1,m,val);
		int rgr=sgt::getRangeR(1,1,m,val);
		
//		std::cout<<val<<' '<<rgl<<' '<<rgr<<std::endl;
		
		sgt::modify(1,1,m,rgr+1,R);
		sgt::modify(1,1,m,rgl,rgl+a[i].second-(R-rgr)-1);
	}
	printf("%lld\n",sgt::calc(1,1,m));
	return 0; 
} 
```

---

## 作者：LJC00118 (赞：6)

https://www.luogu.org/problemnew/show/P4647

首先发现答案与顺序无关，令 $ x_i $ 表示高度为 $ i $ 的那一行帆的个数，第 $ i $ 行对答案的贡献为 $ \frac{x_i * (x_i - 1)}{2} $

先把旗杆按照高度从小到大排序，有一个显然的贪心是每次选择能放的地方帆最少的一行放一个帆，最少的一行放一个帆对答案的贡献一定最小，而后面的旗杆高度更高，能选择放帆的地方更多，这样可以保证答案最小（可以感性理解一下

那么我们的做法就出来了，对于旗杆 $ i $ 选择当前能放帆的最少的 $ k_i $ 行，放上帆，这个操作用平衡树实现，将原序列前 $ k $ 小拿出，加上 $ 1 $ 后放回去，这个时候可能会使平衡树的性质被打破，如 $ 0 $ $ 0 $ 将第一个数加 $ 1 $ 再放回去就变成了 $ 1 $ $ 0 $，所以对于分裂出来的前 $ k $ 小中的最大值还要再次分裂，如 $ 0 $ $ 1 $ $ 1 $ $ 1 $ $ 2 $ 前 $ 3 $ 小要加 $ 1 $，先分裂成 $ 0 $ $ 1 $ $ 1 $ 和 $ 1 $ $ 2 $，然后分裂成 $ 0 $ ，$ 1 $ $ 1 $ 和 $ 1 $ $ 2 $，区间加后放回原序列，先变成 $ 1 $ {这里放原来的 $ 1 $ $ 1 $ } $ 2 $，然后变成 {这里放原来的 $ 0 $} $ 1 $ {这里放原来的 $ 1 $ $ 1 $ } $ 2 $，即 $ 0 $ $ 1 $ $ 1 $ $ 1 $ $ 2 $，可以使用 splay 实现

```cpp
#include <bits/stdc++.h>
#define Fast_cin ios::sync_with_stdio(false), cin.tie(0);
#define rep(i, a, b) for(register int i = a; i <= b; i++)
#define per(i, a, b) for(register int i = a; i >= b; i--)
#define DEBUG(x) cerr << "DEBUG" << x << " >>> " << endl;
using namespace std;

typedef unsigned long long ull;
typedef pair <int, int> pii;
typedef long long ll;

template <typename _T>
inline void read(_T &f) {
    f = 0; _T fu = 1; char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') fu = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }
    f *= fu;
}

template <typename T>
void print(T x) {
    if(x < 0) putchar('-'), x = -x;
    if(x < 10) putchar(x + 48);
    else print(x / 10), putchar(x % 10 + 48);
}

template <typename T>
void print(T x, char t) {
    print(x); putchar(t);
}

template <typename T>
struct hash_map_t {
    vector <T> v, val, nxt;
    vector <int> head;
    int mod, tot, lastv;
    T lastans;
    bool have_ans;

    hash_map_t (int md = 0) {
        head.clear(); v.clear(); val.clear(); nxt.clear(); tot = 0; mod = md;
        nxt.resize(1); v.resize(1); val.resize(1); head.resize(mod);
        have_ans = 0;
    }

    bool count(int x) {
        int u = x % mod;
        for(register int i = head[u]; i; i = nxt[i]) {
            if(v[i] == x) {
                have_ans = 1;
                lastv = x;
                lastans = val[i];
                return 1;
            }
        }
        return 0;
    }

    void ins(int x, int y) {
        int u = x % mod;
        nxt.push_back(head[u]); head[u] = ++tot;
        v.push_back(x); val.push_back(y);
    }

    int qry(int x) {
        if(have_ans && lastv == x) return lastans;
        count(x);
        return lastans;
    }
};

const int N = 1e5 + 5;

struct ele {
    int h, gs;
    bool operator < (const ele A) const { return h < A.h; }
} a[N];

int ch[N][2], val[N], tag[N], siz[N], n, root;

inline void update(int u) { siz[u] = siz[ch[u][0]] + siz[ch[u][1]] + 1; }

inline void add_tag(int u, int x) { if(u <= 100000) val[u] += x; tag[u] += x; }

inline void pushdown(int u) {
    if(tag[u]) {
        if(ch[u][0]) add_tag(ch[u][0], tag[u]);
        if(ch[u][1]) add_tag(ch[u][1], tag[u]);
        tag[u] = 0;
    }
}

inline void rotate(int &u, int d) {
    int tmp = ch[u][d];
    ch[u][d] = ch[tmp][d ^ 1];
    ch[tmp][d ^ 1] = u;
    update(u); update(tmp);
    u = tmp;
}

void splay(int &u, int k) {
    pushdown(u);
    int ltree = siz[ch[u][0]];
    if(ltree + 1 == k) return;
    int d = k > ltree;
    pushdown(ch[u][d]);
    int k2 = d ? k - ltree - 1 : k;
    int ltree2 = siz[ch[ch[u][d]][0]];
    if(ltree2 + 1 != k2) {
        int d2 = k2 > ltree2;
        splay(ch[ch[u][d]][d2], d2 ? k2 - ltree2 - 1 : k2);
        if(d == d2) rotate(u, d); else rotate(ch[u][d], d2);
    }
    rotate(u, d);
}

int find(int u, int x) {
    pushdown(u);
    if(!u) return 0;
    if(x > val[u]) return siz[ch[u][0]] + 1 + find(ch[u][1], x);
    return find(ch[u][0], x);
}

void insert(int &u, int x, int y) {
    splay(u, x + 1); splay(ch[u][0], x);
    ch[ch[u][0]][1] = y; update(ch[u][0]); update(u);
}

ll ans;
void dfs(int u) {
    if(!u) return;
    pushdown(u);
    dfs(ch[u][0]);
    if(u <= 100000) ans += 1ll * val[u] * (val[u] - 1) / 2;
    dfs(ch[u][1]);
}

int main() {
    read(n);
    for(register int i = 1; i <= n; i++) read(a[i].h), read(a[i].gs);
    sort(a + 1, a + n + 1); int now = 1; root = 1;
    ch[root][0] = 100001; ch[root][1] = 100002;
    val[100001] = -1; val[100002] = 100002;
    update(100001); update(100002); update(root);
    for(register int i = 1; i <= n; i++) {
        while(now < a[i].h) {
            ++now; update(now);
            insert(root, 1, now);
        }
        splay(root, a[i].gs + 2); splay(ch[root][0], a[i].gs + 1);
        int left = find(ch[root][0], val[ch[root][0]]), v = val[ch[root][0]], l = ch[root][0];
        ch[root][0] = 0; update(root);
        int right = find(root, v + 1);
        if(!right) {
            add_tag(l, 1);
            ch[root][0] = l;
            update(root);
        } else {
            // fprintf(stderr, "left = %d\n", left);
            splay(l, left + 1);
            int ll = ch[l][0]; ch[l][0] = 0; update(l);
            add_tag(ll, 1); add_tag(l, 1);
            insert(root, right, l);
            splay(root, 1); ch[root][0] = ll; update(root);
        }
    }
    dfs(root);
    cout << ans << endl;
    return 0;
}
```

---

## 作者：Yang818 (赞：5)

看了一眼提交记录，好多神犇用线段树和平衡树写出来几 KB 的代码，但是本蒟蒻写不动，只好在这里分享一下这篇 1KB 都没有的代码。
## 传送门
[这里](https://www.luogu.com.cn/problem/P4647)

## 分析
首先，第一反应肯定是贪心， ~~总归不能是搜索吧~~，贪心决策是每次挂在旗数最少的一层，尽量往上挂。但一个一个贪心肯定会超时，需要用数据结构来优化。

不难发现，旗杆的先后顺序是没有关系的，只要每一根上的旗的数量固定，谁先谁后是不影响结果的。

好，那我们现在需要一个什么样的数据结构？

对于数组 $t$ 每一次新读入一个 $h_i$ 和 $k_i$ 我们先要找到在高度 $1 \sim h_i$ 中找到旗帜数量最少的 $k_i$ 个高度然后把这 $k_i$ 个值都加 $1$.

很多人试了试会觉得这个序列有可能是单调递减的，但其实没有那么简单，看个例子：

$t_i$ 表示第 $i$ 层放了多少旗子，如下所示：

![1](https://cdn.luogu.com.cn/upload/image_hosting/yjsrs2xx.png)

现在如果进来了一个 $h_i=16\ k_i=8$ 序列就会变成：

![2](https://cdn.luogu.com.cn/upload/image_hosting/t8jwvo1d.png)


结果发现单调性被破坏掉了，所以不能这样去维护。

所以现在这个问题就在如何维护单调性。再看刚刚那个例子，我们想要的是：

![3](https://cdn.luogu.com.cn/upload/image_hosting/3n9a9pra.png)

就是后面 5 个 6 影响了连续性。那我们加的时候不要加后 5 个 5，改成加前面 5 个 5 不就可以了吗？

所以总结一下

![示例](https://cdn.luogu.com.cn/upload/image_hosting/1h80sm0d.png)

假如要修改 $h_i-k_i+1 \sim h_i$ 这个区间（图中红色标出来的）：

我们需要转换成：找到第一次出现 $t_{h_i-k_i+1}$ 这个数的位置。然后往后长度为 $r-h_i+k_i$ 的区间（第一段蓝色区间）把它加 $1$。然后再将 $r+1 \sim h_i$ 这个区间（第二段蓝色区间）加 $1$。

就是一个区间修改操作，可以用差分来优化，然后再用树状数组求前缀和。问题是如何找出 $l$ 和 $r$。这边就要用到树状数组的一个技巧。因为树状数组有一个 lowbit 的特性，所以可以天然的进行二分。

~~所以说：07 年的题目就像 07 年的房价一样简单。~~

## 超短的代码

```cpp
#include<bits/stdc++.h>	
using namespace std;
int n,maxh=1<<17,t[(1<<17)+5];
long long ans;
struct node{
    int h,k;
}a[100005];
void modify(int i,int delta){
    for(;i<=maxh;i+=i&-i) t[i]+=delta;
}
int query(int i){
    int sum=0;
    for(;i;i-=i&-i) sum+=t[i];
    return sum;
}
int find(int x){ //二分 
    int pos=0;
    for(int i=maxh;i;i>>=1){
        int j=pos+i;
        if(j<=maxh && t[j]>=x){
            pos=j;
            x-=t[j];
        }
    }
    return pos;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i].h>>a[i].k;
    sort(a+1,a+n+1,[](node x,node y){return x.h<y.h;});
    for(int i=1;i<=n;i++){
        int pos=a[i].h-a[i].k+1;
        int val=query(pos);
        int l=find(val+1)+1;
        int r=(val==0)?a[i].h:find(val);
        modify(l,+1);   modify(l+r-pos+1,-1);
        modify(r+1,+1); modify(a[i].h+1,-1);
    }
    for(int i=1;i<=a[n].h;i++){
        long long s=query(i);
        ans+=s*(s-1)/2;
    }
    cout<<ans<<endl;
}
```






---

## 作者：__Hacheylight__ (赞：4)


题意：

有一艘船，船上有 $n$ 个旗杆，每个旗杆上有 $h_i$ 个小节。每根旗杆上会挂 $k_i$ 张帆

每个小节最多挂一个帆。在风中，帆的不同排布方式会产生不同的推动力

对于任意一张帆，他的推动力折扣等于再它后面并且和它在同一高度的帆的数目

所有帆的任意一种位置组合的推动力折扣和等于在该位置下所有帆的推动力折扣的和

求所有位置组合最小的推动力折扣和

显然有一种贪心方案：

设每个位置上的旗子数量为 $s_i$，那么按照旗杆长度从小到大排序

每次贪心的找到可行的位置中，旗子数量最少的 $k$ 个放旗子即可（即 $s_i+1$)

最后 $\sum\limits_{i}\frac{s_i(s_i-1)}{2}$ 就是答案了。

时间复杂度 $O(\sum\limits_{i=1}^nh_i)$

时间复杂度不行，如何优化？

按照 $s_i$ 维护一个排序后的数列，相当于每次给区间加 $1$

区间加 $1$ 可能使得区间不再有序！

原来的 $s_i:~[1,1,1,1,3]$

$[1,3]$ 加 $1$ 后的数列应为： $[1,2,2,2,3]$

实际上也是区间加法！我们只要找到之后第一个比之前这个数大的即可

可以利用线段树优化，时间复杂度 $O(n~log~n)$

```cpp
#include <map>
#include <set>
#include <ctime>
#include <queue>
#include <stack>
#include <cmath>
#include <vector>
#include <bitset>
#include <cstdio>
#include <cctype>
#include <string>
#include <numeric>
#include <cstring>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std ;
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define per(i, a, b) for (int i = (a); i >= (b); i--)
#define loop(s, v, it) for (s::iterator it = v.begin(); it != v.end(); it++)
#define cont(i, x) for (int i = head[x]; i; i = e[i].nxt)
#define clr(a) memset(a, 0, sizeof(a))
#define ass(a, sum) memset(a, sum, sizeof(a))
#define lowbit(x) (x & -x)
#define all(x) x.begin(), x.end()
#define ub upper_bound
#define lb lower_bound
#define pq priority_queue
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define iv inline void
#define enter cout << endl
#define siz(x) ((int)x.size())
#define file(x) freopen(#x".in", "r", stdin),freopen(#x".out", "w", stdout)
typedef long long ll ;
typedef unsigned long long ull ;
typedef pair <int, int> pii ;
typedef vector <int> vi ;
typedef vector <pii> vii ;
typedef queue <int> qi ;
typedef queue <pii> qii ;
typedef set <int> si ;
typedef map <int, int> mii ;
typedef map <string, int> msi ;
const int N = 100010 ;
const int INF = 0x3f3f3f3f ;
const int iinf = 1 << 30 ;
const ll linf = 2e18 ;
const int MOD = 1000000007 ;
const double eps = 1e-7 ;
void print(int x) { cout << x << endl ; exit(0) ; }
void PRINT(string x) { cout << x << endl ; exit(0) ; }
void douout(double x){ printf("%lf\n", x + 0.0000000001) ; }

int n, m ;

struct node {
	int h, s ;
} a[N] ;

bool cmp(node a, node b) {
	return a.h < b.h ;
}

struct Seg {
	int l, r, mn, mx, tag ;
	#define ls(x) x << 1
	#define rs(x) x << 1 | 1
	#define l(x) tr[x].l
	#define r(x) tr[x].r
	#define tag(x) tr[x].tag
	#define mn(x) tr[x].mn
	#define mx(x) tr[x].mx
} tr[N << 2] ;

void pushup(int x) {
	mn(x) = min(mn(ls(x)), mn(rs(x))) ;
	mx(x) = max(mx(ls(x)), mx(rs(x))) ;
}

void pushdown(int x) {
	if (tag(x)) {
		tag(ls(x)) += tag(x) ;
		tag(rs(x)) += tag(x) ;
		mn(ls(x)) += tag(x) ;
		mn(rs(x)) += tag(x) ;
		mx(ls(x)) += tag(x) ;
		mx(rs(x)) += tag(x) ;
		tag(x) = 0 ;
	}
}

void build(int x, int l, int r) {
	l(x) = l, r(x) = r ;
	if (l == r) return ;
	int mid = (l(x) + r(x)) >> 1 ;
	build(ls(x), l, mid) ;
	build(rs(x), mid + 1, r) ;
	pushup(x) ;
}

void modify(int x, int l, int r) {
	if (l <= l(x) && r(x) <= r) {
		tag(x)++ ; mx(x)++ ; mn(x)++ ;
		return ;
	}
	pushdown(x) ;
	int mid = (l(x) + r(x)) >> 1 ;
	if (l <= mid) modify(ls(x), l, r) ;
	if (mid < r) modify(rs(x), l, r) ;
	pushup(x) ;
}

int qmid(int x, int c) {
	if (l(x) == r(x)) return mn(x) ;
	pushdown(x) ;
	int mid = (l(x) + r(x)) >> 1 ;
	if (c <= mid) return qmid(ls(x), c) ;
	else return qmid(rs(x), c) ;
}

int ql(int x, int c) {
	if (l(x) == r(x)) return l(x) ;
	pushdown(x) ;
	if (mn(ls(x)) <= c) return ql(ls(x), c) ;
	else return ql(rs(x), c) ;
}

int qr(int x, int c) {
	if (l(x) == r(x)) return l(x) ;
	pushdown(x) ;
	if (mx(rs(x)) >= c) return qr(rs(x), c) ;
	else return qr(ls(x), c) ;
}

int query(int x) {
	if (l(x) == r(x)) return mn(x) * (mn(x) - 1) / 2 ;
	pushdown(x) ;
	return query(ls(x)) + query(rs(x)) ;
}

signed main(){
	scanf("%lld", &n) ;
	rep(i, 1, n) {
		scanf("%lld%lld", &a[i].h, &a[i].s) ;
		m = max(m, a[i].h) ;
	}
	sort(a + 1, a + n + 1, cmp) ;
	build(1, 1, m) ;
	rep(i, 1, n) {
		int res = qmid(1, a[i].h - a[i].s + 1) ;
		int L = ql(1, res), R = qr(1, res) ;
		if (R < a[i].h) {
			int len = a[i].h - R ;
			modify(1, R + 1, a[i].h) ;
			modify(1, L, L + a[i].s - len - 1) ;
		} else {
			modify(1, L, L + a[i].s - 1) ;
		}
	}
	printf("%lld\n", query(1)) ;
	return 0 ;
}

/*
写代码时请注意：
	1.ll？数组大小，边界？数据范围？
	2.精度？
	3.特判？
	4.至少做一些
思考提醒：
	1.最大值最小->二分？
	2.可以贪心么？不行dp可以么
	3.可以优化么
	4.维护区间用什么数据结构？
	5.统计方案是用dp？模了么？
	6.逆向思维？
*/

```



---

## 作者：JWRuixi (赞：2)

~~/bx ???~~

### 题意

给定 $n$ 根桅杆，每根桅杆高 $h_i$，要在上面挂 $k_i$ 个帆。定义一个帆对答案的贡献为：和它同高度，且在它前面的帆的数量。

$n \le 10^5$，提交地址：<https://www.luogu.com.cn/problem/P4647>。

### 分析

考虑对于一个高度写出它对答案的贡献，设有 $c_i$ 个帆，则贡献为 $\dfrac{c_i(c_i - 1)}{2}$。由此不难发现答案与桅杆的顺序无关；同时，均值不等式可以告诉我们，答案的最有策略是将帆平均的分配（即 $2, 4$ 劣于 $3, 3$）。

考虑限制成包含关系，从小到大排序，依次考虑。假设考虑到 $i$，由于平均原则，可以对于高度 $1 \sim h_i$ 的位置，直接取帆数量前 $k_i$ 小的放置，然后将这些位置 $+1$。

这显然可以用平衡树维护，时间复杂度 $\mathcal O(n\log n)$。

### Code

代码：<https://paste.ubuntu.com/p/swfhycY4XG/>。

---

## 作者：Rorschachindark (赞：2)

# sails 船帆
[题目传送门](https://www.luogu.com.cn/problem/P4647)
## 思路
其实并不难，也不知道luogu怎么评到黑题的，或许是恶意评分吧

首先建立模型。我们可以发现，桅杆的排列并不影响结果，因为对于每一层如果有$x$个旗子，那么产生的贡献就是$\frac{x\times (x-1)}{2}$

好，既然没有影响，为了方便我们就可以按桅杆的高度从小到大排序了

有一个比较$\text {naive}$的贪心就是，对于当前的桅杆，假如我们可以放$k$个旗子，那么，一定选的是那些放的旗子最少的$k$层（可以看看上面那个式子）

那么，我们转换一下，你想象成有$h$个柱子，你每次可以选最矮的$k$根柱子使得它们的高度加1

那我们如何实现呢？不难想到用平衡树，然后就是一个文艺平衡树和普通平衡树的板子了，我用的非旋Treap实现，比较好实现

具体实现可以看看代码
## $\text {Code}$

```cpp
#include <bits/stdc++.h>
using namespace std;

#define Int register int
#define ll long long
#define MAXN 100005

int n,rt,tot;
int ls[MAXN],rs[MAXN],key[MAXN],val[MAXN],tag[MAXN],size[MAXN];

void Pushup (int x)
{
	size[x] = size[ls[x]] + size[rs[x]] + 1;
}

void Pushdown (int x)
{
	if (!tag[x]) return ;
	if (ls[x]) val[ls[x]] += tag[x],tag[ls[x]] += tag[x];
	if (rs[x]) val[rs[x]] += tag[x],tag[rs[x]] += tag[x];
	tag[x] = 0;
}

int build (int l,int r)
{
	if (l > r) return 0;
	int k = ++ tot;
	val[k] = 0,key[k] = rand (),size[k] = 1;
	int mid = (l + r) >> 1;
	ls[k] = build (l,mid - 1),rs[k] = build (mid + 1,r);
	return Pushup (k),k;
}

void Split (int rt,int k,int &x,int &y)
{
	if (!rt) return x = y = 0,void ();
	Pushdown (rt);
	if (val[rt] <= k) x = rt,Split (rs[rt],k,rs[rt],y);
	else y = rt,Split (ls[rt],k,x,ls[rt]);
	Pushup (rt);
}

void Split_sz (int rt,int k,int &x,int &y)
{
	if (!rt) return x = y = 0,void ();
	Pushdown (rt);
	if (size[ls[rt]] + 1 <= k) x = rt,Split_sz (rs[rt],k - size[ls[rt]] - 1,rs[rt],y);
	else y = rt,Split_sz (ls[rt],k,x,ls[rt]);
	Pushup (rt);
}

int Merge (int x,int y)
{
	if (!x || !y) return x + y;
	Pushdown (x),Pushdown (y);
	if (key[x] < key[y]) return rs[x] = Merge (rs[x],y),Pushup (x),x;
	else return ls[y] = Merge (x,ls[y]),Pushup (y),y;
}

int Getmax (int x)
{
	while (rs[x]) Pushdown (x),x = rs[x];
	return val[x];
}

struct Node
{
	int h,k;
	bool operator < (const Node &p)const
	{
		return h < p.h;
	}
}a[MAXN];

ll Ans;

void dfs (int x)
{
	if (!x) return ;
	if (val[x]) Ans += 1ll * val[x] * (val[x] - 1) >> 1;
	Pushdown (x);
	dfs (ls[x]),dfs (rs[x]);
}

template <typename T> inline void read (T &t){t = 0;char c = getchar();int f = 1;while (c < '0' || c > '9'){if (c == '-') f = -f;c = getchar();}while (c >= '0' && c <= '9'){t = (t << 3) + (t << 1) + c - '0';c = getchar();} t *= f;}
template <typename T,typename ... Args> inline void read (T &t,Args&... args){read (t);read (args...);}
template <typename T> inline void write (T x){if (x < 0){x = -x;putchar ('-');}if (x > 9) write (x / 10);putchar (x % 10 + '0');}

signed main()
{
	read (n);
	srand (time (0));
	for (Int i = 1;i <= n;++ i) read (a[i].h,a[i].k);
	sort (a + 1,a + n + 1);
	rt = build (1,a[1].h);
	for (Int i = 1;i <= n;++ i)
	{
		while (tot < a[i].h) key[++ tot] = rand (),size[tot] = 1,rt = Merge (tot,rt);
		int x,y,z;
		Split_sz (rt,a[i].k,x,y);
		++ val[x],++ tag[x];
		int Max = Getmax (x);
		Split (x,Max - 1,x,z),x = Merge (x,y);
		Split (x,Max,x,y),rt = Merge (Merge (x,z),y);
	}
	dfs (rt);
	write (Ans),putchar ('\n');
	return 0;
}
```

---

## 作者：_AIR (赞：1)

一个显而易见的性质是：最终答案与船杆排序顺序无关，就不证明了。

明白了这一点后，我们就可以先对 $h$ 按照从小到大的顺序进行排序。

将 $h_i$ 小的杆放在前面，后面的杆就有更多的选择余地。

接下来考虑如何放置帆。

令 $T_i$ 表示 $i$ 高度上的船帆个数。

则最终答案 $Ans=\sum_{i=1}^{maxh}\frac{T_i\times(T_i-1)}{2}$，其中 $maxh$ 表示杆子的最大高度。

由于平方级的增长是一级大于一级的，所以我们不难想到均摊所有 $T_i$，使所有 $T_i$ 尽量接近的贪心方法，这显然也是正确的。

但是问题是，应该如何维护 $T$ 序列中的前 $k$ 小值呢？如果是单纯扫描，会TLE到飞起。

考虑优化，将 $T$ 从大到小排序，那我们的操作就相当于给队尾的某些值不停 $+1$ ，但这样子可能会破坏掉 $T$ 序列的单调性。

结合一组数据观察，设 $ T={\{6,6,5,4,4,3,3,3,2,2}\} $，当前的 $k_i=4$ 。

那么操作后的序列就是 $ T={\{6,6,5,4,4,4,4,3,3,3}\} $，观察后发现，实际被修改的只有两个区间。

令 $[L,R]$ 表示 $T$ 中第 $h_i-k_i+1$ 大的值所被包含（即出现）的区间。

那么更改的区间就是 $[L,L+R+k_i-h_i-1]$ 和 $[R+1,h_i]$ 。

直接上线段树维护即可，最后统计答案。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define N 100005
int n;
struct node
{
    int h,k;
}a[N];
bool cmp(node x,node y)
{
    return x.h<y.h;
}
struct tree
{
    int maxn[N<<2];
    int minn[N<<2];
    int tag[N<<2];
    int ll,rr;
    inline void pushup(int rt)
    {
        maxn[rt]=max(maxn[rt<<1],maxn[rt<<1|1]);
        minn[rt]=min(minn[rt<<1],minn[rt<<1|1]);
        return ;
    }
    inline void pushdown(int rt)
    {
        if(tag[rt]>0)
        {
            tag[rt<<1]+=tag[rt];
            tag[rt<<1|1]+=tag[rt];
            maxn[rt<<1]+=tag[rt];
            minn[rt<<1]+=tag[rt];
            maxn[rt<<1|1]+=tag[rt];
            minn[rt<<1|1]+=tag[rt];
            tag[rt]=0;
        }
    }
    inline void update(int rt,int l,int r,int L,int R,int x)
    {
        if(l>R||r<L)return ;
        if(L<=l&&r<=R)
        {
            maxn[rt]+=x;
            minn[rt]+=x;
            tag[rt]+=x;
            return ;
        }
        pushdown(rt);
        int mid=(l+r)>>1;
        update(rt<<1,l,mid,L,R,x);
        update(rt<<1|1,mid+1,r,L,R,x);
        pushup(rt);
        return ;
    }
    inline int query_val(int rt,int l,int r,int pos)
    {
        if(l>pos||r<pos)return 0;
        if(l==r&&l==pos)return minn[rt];
        pushdown(rt);
        int mid=(l+r)>>1;
        return query_val(rt<<1,l,mid,pos)+query_val(rt<<1|1,mid+1,r,pos);
    }
    inline void query_lr(int rt,int l,int r,int p)
    {
        if(minn[rt]>p)return ;
        if(maxn[rt]<p)return ;
        if(maxn[rt]==p)ll=min(l,ll);
        if(minn[rt]==p)rr=max(r,rr);
        if(minn[rt]==p&&maxn[rt]==p)return ;
        pushdown(rt);
        int mid=(l+r)>>1;
        query_lr(rt<<1,l,mid,p);
        query_lr(rt<<1|1,mid+1,r,p);
        return ;
    }
}tr;
signed main()
{
    scanf("%lld",&n);
    int maxh=-1;
    for(int i=1;i<=n;i++)
    {
        scanf("%lld%lld",&a[i].h,&a[i].k);
        maxh=max(maxh,a[i].h);
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++)
    {
        int p=tr.query_val(1,1,maxh,a[i].h-a[i].k+1);
        tr.ll=LONG_LONG_MAX;
        tr.rr=LONG_LONG_MIN;
        tr.query_lr(1,1,maxh,p);
        tr.ll=max(tr.ll,1ll);
        tr.rr=min(tr.rr,a[i].h);
        tr.update(1,1,maxh,tr.rr+1,a[i].h,1);
        tr.update(1,1,maxh,tr.ll,tr.ll+tr.rr+a[i].k-a[i].h-1,1);
    }
    int ans=0;
    for(int i=1;i<=maxh;i++)
    {
        int now=tr.query_val(1,1,maxh,i);
        // printf("%lld\n",now);
        ans+=now*(now-1)/2;
    }
    printf("%lld\n",ans);
}
```

---

