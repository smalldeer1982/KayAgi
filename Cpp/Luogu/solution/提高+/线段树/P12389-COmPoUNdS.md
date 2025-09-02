# COmPoUNdS

## 题目背景

小 S 因为某些原因对区间加区间取模情有独钟，他造了一些这样的题但是基本上都不会做。有一天小 S 误食了一点冰红茶突然灵感迸发把所有题都秒了，于是趁着药效他随便选了一道题造了数据，然而药效过了后他也不知道怎么做了，所以请你帮他写一下标程，事成送你一瓶冰红茶。

## 题目描述

给定正整数 $n,k,q$ 和一个长度为 $n$ 的序列 $a$，$q$ 次操作或询问：
- `1 l r c`，对于每个 $i\in[l,r]$，令 $a_i\gets(a_i+c)\bmod k$。
- `2 l1 r1 l2 r2`，判断 $a$ 的两个长度相同的子段 $a_{l_1\cdots r_1},a_{l_2\cdots r_2}$ 是否相等。

## 说明/提示

**本题采用捆绑测试及子任务依赖。**

| 子任务编号 | 分值 | 特殊限制 | 依赖子任务 | 时间限制 |
| :---: | :---: | :---: | :---: | :---: |
| $1$ | $10$ | $n,q\le 10^3$ | | $\text{1.5 s}$
| $2$ | $20$ | $k=2$ | | $\text{2.5 s}$
| $3$ | $20$ | $n\le10^5$ | $1$ | $\text{1.5 s}$
| $4$ | $50$ | 无特殊限制 | $1,2,3$ | $\text{2.5 s}$
 
对于全部数据，$1\le n,q\le 10^6$，$2\le k\le 10^6$，$0\le a_i,c<k$，对于 2 操作 $r_1-l_1=r_2-l_2$。

## 样例 #1

### 输入

```
6 3 6
0 1 2 0 1 2
2 1 2 1 2
2 1 2 4 5
2 1 2 5 6
1 1 2 1
2 1 2 4 5
2 1 2 5 6```

### 输出

```
Yes
Yes
No
No
Yes```

# 题解

## 作者：_Yonder_ (赞：18)

很好玩的一道题。

发现这个加操作很恶心，可以考虑差分。

如果没有取模的话就可以直接做了，但是有。如果你不是将相邻两数的差取绝对值来做，那么修改的中间部分可能会出现差的正负发生变化然后寄了。于是考虑取绝对值，然后手模几组发现是对的，考虑证明。

假设相邻的两个数分别是 $x,x+d$ 或 $x,x+d-p$，现在我们要证明这不可能同时成立：

考虑反证法，有：

$$x+d<p\land x+d-p\ge0$$

则：

$$x<p-d\land p-d\le x$$

矛盾，故两式不可能同时成立，于是这题我们就可以用线段树维护哈希切掉了。

---

## 作者：rizynvu (赞：9)

官方题解是不是有点幽默了。

考虑这个区间加的操作：$\forall i\in [l, r], a_i\leftarrow (a_i + c)\bmod k$。  
此时会发现 $\forall i\in (l, r], (a_i - a_{i - 1})\bmod k$ 的值依然不会变。  
即模意义下差分值依然只有 $l, r + 1$ 会有变化。

此时再考虑这个判相等，其实可以根据差分拆成两个条件：
- $a_{l_1} = a_{l_2}$。
- $\forall i\in [1, r_1 - l_1], (a_{l_1 + i} - a_{l_1 + i - 1})\bmod k = (a_{l_2 + i} - a_{l_2 + i - 1})\bmod k$。

于是可以对条件 1 上一个树状数组（维护不带取模，最后 check 再取模）。  
对于条件 2 上一个单点改区间查 hash 值的线段树即可（是不是树状数组还更好写来着）。

时间复杂度 $\mathcal{O}(n + q\log n)$。

```cpp
#include<bits/stdc++.h>

using u64 = unsigned long long;
constexpr u64 p = 13331, mod = 998244853;

constexpr int maxn = 1e6 + 10;
int n, K, q;

struct info_ {
    u64 sum, pw;
    inline info_(u64 sum_ = 0, u64 pw_ = 1) : sum(sum_), pw(pw_) {}
    inline info_ operator + (const info_ &oth) const {
        return info_((sum + pw * oth.sum) % mod, pw * oth.pw % mod);
    }
} tr[maxn * 4];

int a[maxn];
inline void build(int k = 1, int l = 1, int r = n) {
    if (l == r) {
        tr[k] = info_((a[l] - a[l - 1] + K) % K, p);
        return ;
    }
    int mid = l + r >> 1;
    build(k << 1, l, mid), build(k << 1 | 1, mid + 1, r);
    tr[k] = tr[k << 1] + tr[k << 1 | 1];
}
inline void update(int x, int y, int k = 1, int l = 1, int r = n) {
    if (l == r) {
        tr[k].sum = (tr[k].sum + y) % K;
        return ;
    }
    int mid = l + r >> 1;
    if (x <= mid) update(x, y, k << 1, l, mid);
    else update(x, y, k << 1 | 1, mid + 1, r);
    tr[k] = tr[k << 1] + tr[k << 1 | 1];
}
inline info_ query(int x, int y, int k = 1, int l = 1, int r = n) {
    if (x <= l && r <= y) return tr[k];
    int mid = l + r >> 1;
    if (y <= mid) return query(x, y, k << 1, l, mid);
    if (mid < x) return query(x, y, k << 1 | 1, mid + 1, r);
    return query(x, y, k << 1, l, mid) + query(x, y, k << 1 | 1, mid + 1, r);
}

u64 sum[maxn];
inline void add(int x, int y) {
    for (; x <= n; x += x & -x) sum[x] += y;
}
inline u64 qry(int x) {
    u64 y = 0;
    for (; x >= 1; x -= x & -x) y += sum[x];
    return y;
}

int main() {
    scanf("%d%d%d", &n, &K, &q);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);

    build();
    for (int i = 1; i <= n; i++) {
        sum[i] += (u64)a[i] - a[i - 1];
        if (i + (i & -i) <= n) {
            sum[i + (i & -i)] += sum[i];
        }
    }

    for (int i = 1; i <= q; i++) {
        int op;
        scanf("%d", &op);

        if (op == 1) {
            int l, r, c;
            scanf("%d%d%d", &l, &r, &c);

            update(l, c), add(l, c);
            if (r < n) update(r + 1, K - c), add(r + 1, -c);
        } else {
            int l1, r1, l2, r2;
            scanf("%d%d%d%d", &l1, &r1, &l2, &r2);

            if (qry(l1) % K != qry(l2) % K) {
                puts("No");
            } else if (l1 < r1 && query(l1 + 1, r1).sum != query(l2 + 1, r2).sum) {
                puts("No");
            } else {
                puts("Yes");
            }
        }
    }

    return 0;
}

```

---

## 作者：jijidawang (赞：8)

首先找一个素数 $p$ 使得存在 $\omega$ 使得 $\omega^k\equiv 1\pmod p$（如果 $k\mid(p-1)$，$g$ 是 $p$ 的原根，则一组解是 $\omega\equiv g^{(p-1)/k}\pmod p$）。接下来可以在 $\mathbb F_p$ 上操作。

那么把序列中的每个数 $x$ 换成 $\omega^x$，这样 1 操作就变成区间乘 $\omega^c$，2 操作仍然是判断子段相等。写一个支持区间乘、求区间 Hash 值的线段树即可。

时间复杂度 $O(n+q\log n)$。

---

## 作者：CQ_Bab (赞：3)

# 前言
写完退役前的最后一篇题解。
# 思路
首先如果我们不考虑要取模的话怎么做，那么明显就是一个差分加哈希就做完了，但是这道题有取模又怎么做呢。我们考虑沿用上面的那个思路，发现也是对的，至于证明也很简单，假设我们第 $i$ 个数为 $x$ 它的差分值为 $y$ 这里是 $b_i=(a_{i+1}-a_{i})\bmod k$ 那么我们如果在下一个会不同当且仅当我们将一个负数取模之后成了正数正好与差分是正数的值相等了，则有 $a_{i+1}=x+y$，$a1_{i+1}=x+(k-y)$ 这里分别表示两个区间中的第 $i+1$ 个数，而我们又发现如果这样的情况存在那么一定有 $\max(a_{i+1},a1_{i+1})-\min(a_{i+1},a1_{i+1})=k$ 但是又因为 $1<a_i<k$ 那么差值最多为 $k-1$ 所以这样的情况不存在。

那么就考虑维护一个动态 hash 的线段树即可，每次修改为区间加和单点改，查询只用查询第一个位置的值和区间 hash 即可。
# 代码
```cpp
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace std;
#define pb push_back
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define fire signed
#define il inline
template<class T> il void print(T x) {
	if(x<0) printf("-"),x=-x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
template<class T> il void in(T &x) {
    x = 0; char ch = getchar();
    while (ch < '0' || ch > '9') {ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
}
int T=1;
int n,q;
const int N=1e6+10,ba=131,mod=1e9+7;
int a[N],k;
int jc[N];
struct node{
	int l,r;
	int tag,v,has;
}tr[N<<2];
void up(int x) {
	tr[x].has=(1ll*tr[x<<1].has*jc[tr[x<<1|1].r-tr[x<<1|1].l+1]%mod+tr[x<<1|1].has)%mod;
}
int b[N];
void build(int u,int l,int r) {
	tr[u]={l,r};
	if(tr[u].l==tr[u].r) {
		tr[u].v=a[l];
		tr[u].has=b[l];
		return;
	}
	int mid=l+r>>1;
	build(u<<1,l,mid);
	build(u<<1|1,mid+1,r);
	up(u);
}
void down(int x) {
	if(tr[x].tag) {
		tr[x<<1].tag=(tr[x].tag+tr[x<<1].tag)%k;
		tr[x<<1|1].tag=(tr[x].tag+tr[x<<1|1].tag)%k;
		tr[x<<1].v=(tr[x<<1].v+tr[x].tag)%k;
		tr[x<<1|1].v=(tr[x<<1|1].v+tr[x].tag)%k;
		tr[x].tag=false;
	}
} 
void modify(int u,int l,int r,int x) {
	if(tr[u].l>=l&&tr[u].r<=r) {
		tr[u].v=(tr[u].v+x)%k;
		tr[u].tag=(tr[u].tag+x)%k;
		return;
	}
	int mid=tr[u].l+tr[u].r>>1;
	down(u);
	if(mid>=l) modify(u<<1,l,r,x);
	if(mid<r) modify(u<<1|1,l,r,x);
}
void modify1(int u,int k,int x) {
	if(tr[u].l==tr[u].r) {
		tr[u].has=k;
		return;
	}
	int mid=tr[u].l+tr[u].r>>1;
	if(mid>=x) modify1(u<<1,k,x);
	else modify1(u<<1|1,k,x);
	up(u);
}
pair<int,int> Ans1(int u,int l,int r) {
	if(tr[u].l>=l&&tr[u].r<=r) {
		return {tr[u].has,tr[u].r-tr[u].l+1};
	}
	int mid=tr[u].l+tr[u].r>>1;
	pair<int,int> ans={0,0};
	if(mid>=l) ans=Ans1(u<<1,l,r);
	if(mid<r) {
		pair<int,int> res=Ans1(u<<1|1,l,r);
		ans.first=1ll*ans.first*jc[res.second]%mod;
		ans.first=(res.first+ans.first)%mod;
		ans.second+=res.second;
	}
	return ans;
}
int Ans(int u,int x) {
	if(tr[u].l==tr[u].r) {
		return tr[u].v;
	}
	down(u);
	int mid=tr[u].l+tr[u].r>>1;
	if(mid>=x) return Ans(u<<1,x);
	return Ans(u<<1|1,x);
}
void solve() {
	in(n),in(k),in(q);
	jc[0]=1;
	rep(i,1,n) jc[i]=1ll*jc[i-1]*ba%mod;
	rep(i,1,n) in(a[i]);
	rep1(i,n-1,1) b[i]=((a[i+1]-a[i])%k+k)%k;
	build(1,1,n);
	while(q--) {
		int opt;
		in(opt);
		if(opt==1) {
			int l,r,c;
			in(l),in(r),in(c);
			modify(1,l,r,c);
			if(r!=n){
				int nx=Ans(1,r+1),nowr=Ans(1,r);
				nx=(nx-nowr+k)%k;
				modify1(1,nx,r);
			}
			if(l!=1) {
				int pr=Ans(1,l-1),nowl=Ans(1,l);
				pr=(nowl-pr+k)%k;
				modify1(1,pr,l-1);
			}
		}else {
			int l1,r1,l2,r2;
			in(l1),in(r1),in(l2),in(r2);
			if(l1==l2&&r1==r2) {
				puts("Yes");
				continue;
			}
			if(r1-l1==0) {
				if(Ans(1,l1)==Ans(1,l2)) {
					puts("Yes");
				}else puts("No");
				continue;
			}
			if(Ans(1,l1)!=Ans(1,l2)) {
				puts("No");
				continue; 
			}
			int kk=Ans1(1,l1,r1-1).first,kk1=Ans1(1,l2,r2-1).first;
			if(kk!=kk1) puts("No");
			else puts("Yes");
		}
	}
}
fire main() {
	while(T--) {
		solve();
	}
	return false;
}
```

---

## 作者：LastKismet (赞：1)

# 思路
判断子段相等，不难想到哈希。

同时区间操作，不难想到差分。

所以就是哈希维护差分序列。

然而发现题目中有取模操作，直觉上感觉会影响区间修改差分的正确性。然而，事实上，除了修改两端差分值在取模意义下仍然是不变的。

这很显然，对于两个相邻点就算一个点越过模数而另一个点没有，如果右侧点越过模数被取模，新右侧点被取模前的值等价于新左侧点的值加原差分值，最后答案统一取模效果一样；如果左侧点越过模数被取模，不难发现在取模意义下原来那个负差分值的正模数就是新的差分值，不变。

然后就没什么了，线段树维护区间和和区间哈希值即可。

对于判断，首先通过差分区间和得到两个段首元素，然后看两段的差分序列是否相等即可。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef __int128 i128;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<int,ll> pil;
typedef pair<ll,int> pli;
template<typename T> using vec=vector<T>;
template<typename T> using grheap=priority_queue<T>;
template<typename T> using lrheap=priority_queue<T,vector<T>,greater<T>>;
#define fir first
#define sec second
#define pub push_back
#define pob pop_back
#define puf push_front
#define pof pop_front
#define chmax(a,b) a=max(a,b)
#define chmin(a,b) a=min(a,b)
#define rep(i,x,y) for(int i=(x);i<=(y);i++)
#define per(i,x,y) for(int i=(x);i>=(y);i--)
#define repl(i,x,y) for(int i=(x);i<(y);i++)
#define file(f) freopen(#f".in","r",stdin);freopen(#f".out","w",stdout);

struct mint {
	int x,mod;
	inline mint(int o=0,int p=998244353) {x=o;mod=p;}
	inline mint & operator=(ll o){return x=o%mod,(x+=mod)>=mod&&(x-=mod),*this;}
	inline mint & operator+=(mint o){return (x+=o.x)>=mod&&(x-=mod),*this;}
	inline mint & operator-=(mint o){return (x-=o.x)<0&&(x+=mod),*this;}
	inline mint & operator*=(mint o){return x=(ll)x*o.x%mod,*this;}
	inline mint & operator^=(ll b){mint res(1);for(;b;b>>=1,*this*=*this)if(b&1)res*=*this;return x=res.x,*this;}
	inline mint & operator^=(mint o){return *this^=o.x;}
	inline mint & operator/=(mint o){return *this*=(o^=(mod-2));}
	inline mint & operator++(){return *this+=1;}
	inline mint & operator--(){return *this-=1;}
	inline mint operator++(int o){mint res=*this;return *this+=1,res;}
	inline mint operator--(int o){mint res=*this;return *this-=1,res;}
	friend inline mint operator+(mint a,mint b){return a+=b;}
	friend inline mint operator-(mint a,mint b){return a-=b;}
	friend inline mint operator*(mint a,mint b){return a*=b;}
	friend inline mint operator/(mint a,mint b){return a/=b;}
	friend inline mint operator^(mint a,ll b){return a^=b;}
	friend inline mint operator^(mint a,mint b){return a^=b;}
	friend inline bool operator<(mint a,mint b){return a.x<b.x;}
	friend inline bool operator>(mint a,mint b){return a.x>b.x;}
	friend inline bool operator<=(mint a,mint b){return a.x<=b.x;}
	friend inline bool operator>=(mint a,mint b){return a.x>=b.x;}
	friend inline bool operator==(mint a,mint b){return a.x==b.x;}
	friend inline istream & operator>>(istream &in,mint &o){ll x;return in>>x,o=x,in;}
	friend inline ostream & operator<<(ostream &ot,mint o){return ot<<o.x,ot;}
};

const int inf=0x3f3f3f3f;
const ll INF=0x3f3f3f3f3f3f3f3f;

const int N=1e6+5;

int n,k,q;
int a[N];
mint bas[N];

struct segment{
	mint cf[N<<2],dat[N<<2];
	void update(int x,int l,int r){
		int m=l+r>>1;
		dat[x]=dat[x<<1]*bas[r-m]+dat[x<<1|1];
		cf[x]=cf[x<<1]+cf[x<<1|1];
	}
	void build(int x=1,int l=1,int r=n){
		cf[x].mod=k;
		if(l==r)return dat[x]=(cf[x]=a[l]-a[l-1]).x,void();
		int m=l+r>>1;
		build(x<<1,l,m);
		build(x<<1|1,m+1,r);
		update(x,l,r);
	}
	void add(int k,int v,int x=1,int l=1,int r=n){
		if(l==r)return dat[x]=(cf[x]+=v).x,void();
		int m=l+r>>1;
		if(k<=m)add(k,v,x<<1,l,m);
		else add(k,v,x<<1|1,m+1,r);
		update(x,l,r);
	}
	mint querycf(int lq,int rq,int x=1,int l=1,int r=n){
		if(lq<=l&&r<=rq)return cf[x];
		int m=l+r>>1;
		mint res(0,k);
		if(lq<=m)res+=querycf(lq,rq,x<<1,l,m);
		if(m<rq)res+=querycf(lq,rq,x<<1|1,m+1,r);
		return res;
	}
	mint querydat(int lq,int rq,int x=1,int l=1,int r=n){
		if(lq<=l&&r<=rq)return dat[x];
		int m=l+r>>1;
		if(rq<=m)return querydat(lq,rq,x<<1,l,m);
		if(m<lq)return querydat(lq,rq,x<<1|1,m+1,r);
		return querydat(lq,m,x<<1,l,m)*bas[rq-m]+querydat(m+1,rq,x<<1|1,m+1,r);
	}
}seg;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>k>>q;
	bas[0]=1;
	rep(i,1,n)bas[i]=bas[i-1]*131;
	rep(i,1,n)cin>>a[i];
	seg.build();
	int op,l,r,c,l1,r1,l2,r2;
	rep(i,1,q){
		cin>>op;
		if(op==1){
			cin>>l>>r>>c;
			seg.add(l,c);
			if(r<n)seg.add(r+1,k-c);
		}else{
			cin>>l1>>r1>>l2>>r2;
			if(seg.querycf(1,l1)==seg.querycf(1,l2)&&(!(r1-l1)||seg.querydat(l1+1,r1)==seg.querydat(l2+1,r2)))cout<<"Yes\n";
			else cout<<"No\n";
		}
	}
	return 0;
}
```

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P12389)

# 前置知识

[前缀和 & 差分](https://oi-wiki.org/basic/prefix-sum/) | [线段树基础](https://oi-wiki.org/ds/seg/)

# 解法

修改只有区间加操作，套路性地想到维护差分数组的哈希值来将区间修改简化至单点修改，同时维护端点处的原值用于判相等。

具体地，设 $b$ 为 $a$ 的差分数组，则 $a_{l_{1} \dots r_{1}},a_{l_{2} \dots r_{2}}$ 完全相等当且仅当 $a_{l_{1}}=a_{l_{2}}$ 且 $b_{l_{1}+1 \dots r_{1}},b_{l_{2}+1 \dots r_{2}}$ 完全相等。

前者是一个区间加单点查的形式，后者是一个单点加区间查询的形式，可以使用线段树维护。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
const int mod=1000003579,base=13331;
int jc[1000010],a[1000010],p;
struct SMT
{
	struct SegmentTree
	{
		int lazy,hsh,len;
	}tree[4000010];
	#define lson(rt) (rt<<1)
	#define rson(rt) (rt<<1|1)
	void pushup(int rt)
	{
		tree[rt].hsh=(1ll*tree[lson(rt)].hsh*jc[tree[rson(rt)].len]%mod+tree[rson(rt)].hsh)%mod;
	}
	void build(int rt,int l,int r)
	{
		tree[rt].len=r-l+1;
		if(l==r)  
		{
			tree[rt].lazy=a[l];
			tree[rt].hsh=(a[l]-a[l-1]+p)%p;
			return;
		}
		int mid=(l+r)/2;
		build(lson(rt),l,mid);  build(rson(rt),mid+1,r);
		pushup(rt);
	}
	void update1(int rt,int l,int r,int pos,int val)
	{
		if(l==r)
		{
			tree[rt].hsh=(tree[rt].hsh+val)%p;
			return;
		}
		int mid=(l+r)/2;
		if(pos<=mid)  update1(lson(rt),l,mid,pos,val);
		else  update1(rson(rt),mid+1,r,pos,val);
		pushup(rt);
	}
	void update2(int rt,int l,int r,int x,int y,int val)
	{
		if(x<=l&&r<=y)
		{
			tree[rt].lazy=(tree[rt].lazy+val)%p;
			return;
		}
		int mid=(l+r)/2;
		if(x<=mid)  update2(lson(rt),l,mid,x,y,val);
		if(y>mid)  update2(rson(rt),mid+1,r,x,y,val);
	}
	int query1(int rt,int l,int r,int pos)
	{
		if(l==r)  return tree[rt].lazy;
		int mid=(l+r)/2;
		if(pos<=mid)  return (query1(lson(rt),l,mid,pos)+tree[rt].lazy)%p;
		else  return (query1(rson(rt),mid+1,r,pos)+tree[rt].lazy)%p;
	}
	pair<int,int> query2(int rt,int l,int r,int x,int y)
	{
		if(x<=l&&r<=y)  return make_pair(tree[rt].hsh,tree[rt].len);
		int mid=(l+r)/2;
		if(y<=mid)  return query2(lson(rt),l,mid,x,y);
		if(x>mid)  return query2(rson(rt),mid+1,r,x,y);
		pair<int,int>p=query2(lson(rt),l,mid,x,y);
		pair<int,int>q=query2(rson(rt),mid+1,r,x,y);
		return make_pair((1ll*p.first*jc[q.second]%mod+q.first)%mod,p.second+q.second);
	}
}T;
int main()
{
// #define Isaac
#ifdef Isaac
	freopen("in.in","r",stdin);
	freopen("out.out","w",stdout);
#endif
	int n,m,pd,l1,r1,l2,r2,x,i;
	scanf("%d%d%d",&n,&p,&m);  jc[0]=1;
	for(i=1;i<=n;i++) 
	{
		scanf("%d",&a[i]);
		jc[i]=1ll*jc[i-1]*base%mod;
	}
	T.build(1,1,n);
	for(i=1;i<=m;i++)
	{
		scanf("%d%d%d",&pd,&l1,&r1);
		if(pd==1)
		{
			scanf("%d",&x);
			T.update1(1,1,n,l1,x);
			if(r1+1<=n)  T.update1(1,1,n,r1+1,(p-x)%p);
			T.update2(1,1,n,l1,r1,x);
		}
		else
		{
			scanf("%d%d",&l2,&r2);
			if(T.query1(1,1,n,l1)==T.query1(1,1,n,l2))
			{
				if(r1>l1)
				{
					if(T.query2(1,1,n,l1+1,r1).first==T.query2(1,1,n,l2+1,r2).first)  printf("Yes\n");
					else  printf("No\n");
				}
				else  printf("Yes\n");
			}
			else  printf("No\n");
		}
	}
	return 0;
}
```

---

