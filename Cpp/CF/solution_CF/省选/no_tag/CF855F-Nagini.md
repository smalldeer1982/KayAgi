# Nagini

## 题目描述

有 $10^5$ 个集合，编号从 $1$ 到 $10^5$。每一个集合内初始没有元素。你需要支持两个操作：

`1 l r k`：在编号在 $[l,r)$ 的集合中加入元素 $k$（$1 \le l < r \leq 10^5 , k \in [-10^9,0) \cup (0 , 10^9]$）。

`2 l r`：询问编号在 $[l,r)$ 内的集合的权值和（$1 \le l < r \leq 10^5$）。

一个集合的权值定义为：如果集合中同时存在 $>0$ 的元素和 $<0$ 的元素，则其权值为最小的 $>0$ 的元素和最大的 $<0$ 的元素的绝对值的和，否则为 $0$。

## 样例 #1

### 输入

```
3
1 1 10 10
1 2 4 -7
2 1 10
```

### 输出

```
34
```

## 样例 #2

### 输入

```
7
1 2 3 5
1 1 10 10
1 4 5 -5
2 4 8
1 1 10 -10
2 4 8
2 1 10
```

### 输出

```
15
75
170
```

# 题解

## 作者：zhouyixian (赞：7)

既然 $q\leq 5e4$ 当然是 $O(nq)$ 直接过啊。

开玩笑的，不过暴力确实能过。

下面介绍复杂度正确的方法：Segment Tree Beats

CF 上官方题解好像是 $O(n\sqrt n\log n)$ 的分块，不过这题完全可以用吉司机线段树过。

[更板子的题](https://vjudge.net/problem/HDU-5306)

[板子题](https://www.luogu.com.cn/problem/P6242)

如果没学过吉司机线段树的话可以去上面两道题学学（会第一题就可以做这道题了），以下假定大家都会了。

此题要求我们干这两件事：

+ 区间添加元素

+ 区间求贡献和

首先我们开两颗线段树，分别维护正数和负数绝对值的最小值。

区间加元素相当于区间取 $\min$ ，常规操作。

问题是我们不能直接维护区间和，因为只有正或负数的集合是没有贡献的。

我的想法是再开两颗线段树统计有贡献的集合。

在某个集合从无贡献到有贡献时，就把它的信息搬到统计答案的线段树里，最后在这颗线段树里统计答案即可。

至于如何判断某个集合从无贡献到有贡献，可以用一个很暴力的方法：开两个 set 存储没有正数或负数的集合编号，在某个区间插数时遍历 set 中在此区间内的所有集合并删除，如果正负都被删了就统计信息即可。

一个集合只会被删除两次，所以这样做不影响复杂度。

实现细节看代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10,INF=1e9+10;

struct node{
	int mx,tag,cnt,sec;
	long long sum;
};
int L,R,n=1e5,q;

struct SegTree{
#define ls (rt<<1)
#define rs ((rt<<1)|1)
#define middef int mid=(l+r)>>1

node t[N];

void push_up(int rt){
	t[rt].sum=t[ls].sum+t[rs].sum;
	int u=ls,v=rs;
	if(t[u].mx==t[v].mx){
		t[rt].mx=t[v].mx;
		t[rt].cnt=t[u].cnt+t[v].cnt;
		t[rt].sec=max(t[u].sec,t[v].sec);
	}else{
		if(t[u].mx>t[v].mx)swap(u,v);
		t[rt].sec=max(t[u].mx,t[v].sec);
		t[rt].mx=t[v].mx,t[rt].cnt=t[v].cnt;
	}
}

void update(int rt,int v){
	if(v<t[rt].mx){
		t[rt].sum+=1ll*(v-t[rt].mx)*t[rt].cnt;		
		t[rt].mx=t[rt].tag=v;
	}
}

void push_down(int rt){
	if(~t[rt].tag){
		update(ls,t[rt].tag);
		update(rs,t[rt].tag);
		t[rt].tag=-1;
	}
}

void build(int l=1,int r=n,int rt=1){
	t[rt].tag=-1;
	if(l==r){
		t[rt].sum=t[rt].mx=INF;
		t[rt].cnt=1;
		return;
	}
	middef;
	build(l,mid,ls),build(mid+1,r,rs);
	push_up(rt);
}

void minimize(int v,int l=1,int r=n,int rt=1){	
	if(l>R||r<L||v>=t[rt].mx)return;	
	if((L<=l&&r<=R)&&(t[rt].sec<v))return update(rt,v);	
	push_down(rt);
	middef;
	minimize(v,l,mid,ls);
	minimize(v,mid+1,r,rs);
	push_up(rt);
}//区间取 min

void modify(int pos,int v,int l=1,int r=n,int rt=1){
	if(l==r){
		t[rt].mx=t[rt].sum=v;
		t[rt].cnt=1;
		return;
	}
	middef;
	push_down(rt);
	if(pos<=mid)modify(pos,v,l,mid,ls);
	else modify(pos,v,mid+1,r,rs);
	push_up(rt);
}//单点修改

int get_val(int pos,int l=1,int r=n,int rt=1){
	if(l==r)return t[rt].sum;
	middef;
	push_down(rt);
	if(pos<=mid)return get_val(pos,l,mid,ls);
	return get_val(pos,mid+1,r,rs);
}//单点查询

long long get_sum(int l=1,int r=n,int rt=1){
	if(l>R||r<L)return 0;
	if(L<=l&&r<=R)return t[rt].sum;
	push_down(rt);
	middef;
	long long ret=get_sum(l,mid,ls)+get_sum(mid+1,r,rs);
	push_up(rt);
	return ret;
}

}pos_ans,neg_ans,pos_all,neg_all;
//吉司机线段树板子。

set<int> pos_p,neg_p;
int cnt[N];

inline void modify(SegTree &all,SegTree &ans,set<int> &pos,int v){
	all.minimize(v);
	ans.minimize(v);
	for(auto it=pos.lower_bound(L);*it<=R;it=pos.erase(it)){
		cnt[*it]++;
        //统计被删除次数，达到二说明有正有负。
		if(cnt[*it]==2){
			pos_ans.modify(*it,pos_all.get_val(*it));
			neg_ans.modify(*it,neg_all.get_val(*it));
            //把对应点的值搬过去
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>q;
	for(int i=1;i<=n;++i)pos_p.insert(i),neg_p.insert(i);
	pos_all.build();
	neg_all.build();
    //统计答案的线段树不需要初始化，因为它的值是之后逐个插入的。
	for(int i=1;i<=q;++i){
		int op,v;
		cin>>op>>L>>R;
		R--;
		if(op==1){
			cin>>v;
			if(v<0) modify(neg_all,neg_ans,neg_p,-v);
			else modify(pos_all,pos_ans,pos_p,v);
		}else cout<<pos_ans.get_sum()+neg_ans.get_sum()<<endl;
	}
}
```

---

## 作者：ty_mxzhn (赞：1)

区间取 $\min$ 求区间和，一看就是吉司机线段树（Segment Tree Beats）

但是有一些小问题：如果一个位置没有出现某个符号的贡献，则答案为 $0$。这个需要特殊处理。

具体的来说，我们每次暴力的找出区间加数以后，两种符号都存在的新位置，并把他们加入答案。这一部分如果使用 set 维护可以容易做到 $O(n \log n)$。

对于一个新加入的数，他相当于只是突然被算入了答案，该怎么维护就怎么维护。例子：比如说维护子树和类比就是维护有效子树和。

---

## 作者：Luzhuoyuan (赞：1)

来点答辩分块震撼。

Links: [[Codeforces]](http://codeforces.com/problemset/problem/855/F) [[Luogu]](https://www.luogu.com.cn/problem/CF855F)

### 题意

有 $10^5$ 个集合，初始均为空。有 $q$ 个操作，每个操作为以下之一：

- `1 l r k`：向编号在 $[l,r)$ 中的集合加入元素 $k$；
- `2 l r`：查询编号在 $[l,r)$ 中的集合的权值和。

其中，若一个集合中同时存在编号为整数和负数的元素，则其权值定义为最小正数与最大负数之差；否则为 $0$。

- $1\le q\le 5\cdot 10^4$；
- $1\le l<r\le 10^5$；
- $1\le |k|\le 10^9$。

### 思路

数据范围较小，考虑进行分块，设块长为 $B$，集合个数为 $n=10^5$。

对于每个位置，我们记录它的集合的最小正数和最大负数；对于每个块，我们记录该块的权值之和以及整块覆盖的懒标记（即覆盖整个块的最小正数、最大负数），同时对每个块开两个 `map` 作为该块中每个集合的最小正数、最大负数的桶。为了维护权值为 $0$ 的集合，我们再维护两个 `set` 表示不存在正数、不存在负数的集合的标号。我们要求一个集合在同时有正数和负数元素时才计入所在块的 `map` 中。之后我们遵循以下流程：

#### 修改操作

首先，在 $k$ 值对应的 `set` 中二分并遍历每个在操作区间中且不存在与 $k$ 同类（正负性相同）的集合，用 $k$ 更新其状态，并将其从 `set` 中删除。如果更新完后这个集合里有正有负，那么用这个集合更新它所在块的 `map` 和总权值，注意更新前要先用块上的懒标记更新这个集合。这部分的总复杂度为 $O((n+q)\log n)$。

接着，对散块下传标记暴力修改，复杂度 $O(B\log n)$；对于每个整块，若 $k$ 为正数，遍历 `map` 中大于 $k$ 的元素，这部分元素最终都会被更新为 $k$，我们记录这部分元素的个数并删除这些元素，再加入相等个数的 $k$ 即可，$k$ 为负数同理。考虑复杂度，每次修改会为 `map` 制造 $O(\frac n B)$ 个新元素，每个元素会被移除至多一次，所以总复杂度为 $O(\frac{qn\log n}B)$。

#### 查询操作

散块下传暴力求解，遍历每个整块将权值求和即可。复杂度 $O(B\log n+\frac n B)$。

总复杂度 $O(n\log n+q\log n(B+\frac n B))$，取 $B=\sqrt n$，得复杂度 $O(n\log n+q\sqrt n\log n)$。

### 代码

代码中为了实现方便，记录正数的 `map`（`pm`）中的键值为实际值的相反数。

```cpp
#include<bits/stdc++.h>
#define int long long
#define pb push_back
using namespace std;
const int N=1e5+5,M=320,V=1e5,B=316;
int _,op,l,r,x,lb,rb,bl[M],br[M],a[M],ps[N],ng[N],bp[M],bn[M];
//各数组分别代表：块的端点；块的权值；集合的正/负数；块的正/负标记。
set<int> sp,sn;
//没有正/负数的集合
map<int,int> pm[M],nm[M];
//每个块正/负数的桶
inline void wk(int p){
	int b=(p-1)/B;
	if(bp[b])ps[p]=min(ps[p],bp[b]);
	if(bn[b])ng[p]=max(ng[p],bn[b]);
	pm[b][-ps[p]]++,nm[b][ng[p]]++,a[b]+=ps[p]-ng[p];
}
inline void psd(int b){
	for(int i=bl[b];i<=br[b];i++){if(bp[b])ps[i]=min(ps[i],bp[b]);if(bn[b])ng[i]=max(ng[i],bn[b]);}
	bp[b]=bn[b]=0;
}
inline void upd(int l,int r){
	int b=(l-1)/B;psd(b);
	for(int i=l;i<=r;i++){if(x>0&&x<ps[i])ps[i]=x;if(x<0&&x>ng[i])ng[i]=x;}
	a[b]=0;pm[b].clear(),nm[b].clear();
	for(int i=bl[b];i<=br[b];i++)if(ps[i]&&ng[i])a[b]+=ps[i]-ng[i],pm[b][-ps[i]]++,nm[b][ng[i]]++;
}
inline int qry(int l,int r){
	int b=(l-1)/B,v=0;psd(b);
	for(int i=l;i<=r;i++)if(ps[i]&&ng[i])v+=ps[i]-ng[i];
	return v;
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	cin>>_;for(int i=1;i<=V;i++)sp.insert(i),sn.insert(i);
	for(int i=0;i<=B;i++)bl[i]=i*B+1,br[i]=min(V,(i+1)*B);
	while(_--){
		cin>>op>>l>>r,r--;lb=(l-1)/B,rb=(r-1)/B;
		if(op==1){
			cin>>x;
			if(x>0){
				for(auto i=sp.lower_bound(l);i!=sp.end()&&*i<=r;i++){ps[*i]=x;if(ng[*i])wk(*i);}
				sp.erase(sp.lower_bound(l),sp.upper_bound(r));
			}else{
				for(auto i=sn.lower_bound(l);i!=sn.end()&&*i<=r;i++){ng[*i]=x;if(ps[*i])wk(*i);}
				sn.erase(sn.lower_bound(l),sn.upper_bound(r));
			}if(lb==rb){upd(l,r);continue;}
			upd(l,br[lb]),upd(bl[rb],r);
			for(int i=lb+1;i<rb;i++){
				int cnt=0;
				if(x>0){
					if(!bp[i]||x<bp[i])bp[i]=x;
					for(auto j:pm[i]){if(j.first>=-x)break;cnt+=j.second,a[i]+=j.first*j.second;}
					if(cnt)pm[i].erase(pm[i].begin(),pm[i].lower_bound(-x)),pm[i][-x]+=cnt,a[i]+=x*cnt;
				}else{
					if(!bn[i]||x>bn[i])bn[i]=x;
					for(auto j:nm[i]){if(j.first>=x)break;cnt+=j.second,a[i]+=j.first*j.second;}
					if(cnt)nm[i].erase(nm[i].begin(),nm[i].lower_bound(x)),nm[i][x]+=cnt,a[i]-=x*cnt;
				}
			}
		}else{
			if(lb==rb){cout<<qry(l,r)<<'\n';continue;}
			int ans=qry(l,br[lb])+qry(bl[rb],r);
			for(int i=lb+1;i<rb;i++)ans+=a[i];
			cout<<ans<<'\n';
		}
	}
	return 0;
}
```

（逃

---

## 作者：Felix72 (赞：1)

使用两棵吉司机线段树代表正负数，做到区间最值和区间求和。

与模板题不同的是，当前位置有异号数时，这个数的贡献才生效。于是收到扫描线的启发，我们对每个数点增设标记，分别维护子树和、最大值个数以及有效子树和、有效最大值个数，当一棵子树生效时，将标记同步即可。

```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x & (-x))
using namespace std;
const int N = 100010, maxn = 100010;
int n;
struct SGT
{
	int rt, idx;
	struct SGTnode
	{
		int ls, rs;
		long long mx, sx, fnx, rnx, tn, fsum, rsum, tc;
		#define ls(x) tr[x].ls
		#define rs(x) tr[x].rs
		#define mx(x) tr[x].mx
		#define sx(x) tr[x].sx
		#define fnx(x) tr[x].fnx
		#define rnx(x) tr[x].rnx
		#define tn(x) tr[x].tn
		#define fsum(x) tr[x].fsum
		#define rsum(x) tr[x].rsum
		#define tc(x) tr[x].tc
	}tr[N * 2];
	inline void pushup(int now)
	{
		fsum(now) = fsum(ls(now)) + fsum(rs(now));
		rsum(now) = rsum(ls(now)) + rsum(rs(now));
		if(mx(ls(now)) == mx(rs(now)))
		{
			mx(now) = mx(ls(now));
			sx(now) = max(sx(ls(now)), sx(rs(now)));
			fnx(now) = fnx(ls(now)) + fnx(rs(now));
			rnx(now) = rnx(ls(now)) + rnx(rs(now));
		}
		if(mx(ls(now)) > mx(rs(now)))
		{
			mx(now) = mx(ls(now));
			sx(now) = max(sx(ls(now)), mx(rs(now)));
			fnx(now) = fnx(ls(now));
			rnx(now) = rnx(ls(now));
		}
		if(mx(ls(now)) < mx(rs(now)))
		{
			mx(now) = mx(rs(now));
			sx(now) = max(mx(ls(now)), sx(rs(now)));
			fnx(now) = fnx(rs(now));
			rnx(now) = rnx(rs(now));
		}
	}
	inline void push_min(int now, int tg)
	{
		if(mx(now) <= tg) return ;
		if(mx(now) < 2e9)
		{
			fsum(now) -= mx(now) * fnx(now);
			rsum(now) -= mx(now) * rnx(now);
		}
		fsum(now) += tg * fnx(now);
		rsum(now) += tg * rnx(now);
		mx(now) = tg; tn(now) = tg;
	}
	inline void push_cover(int now)
	{
		rsum(now) = fsum(now);
		rnx(now) = fnx(now);
		tc(now) = true;
	}
	inline void pushdown(int now)
	{
		if(tc(now))
		{
			push_cover(ls(now));
			push_cover(rs(now));
		}
		if(tn(now) != 2e9)
		{
			push_min(ls(now), tn(now));
			push_min(rs(now), tn(now));
		}
		tn(now) = 2e9; tc(now) = false;
	}
	inline void build(int &now, int l, int r)
	{
		now = ++idx; tn(now) = 2e9;
		if(l == r)
		{
			mx(now) = 2e9 + 1, sx(now) = -2e9 - 1;
			fnx(now) = 1; rnx(now) = 0;
			fsum(now) = 0; rsum(now) = 0;
			return ;
		}
		int mid = (l + r) >> 1;
		build(ls(now), l, mid), build(rs(now), mid + 1, r);
		pushup(now);
	}
	inline void insert(int now, int l, int r, int L, int R, int num)
	{
		if(mx(now) <= num) return ;
		if(L <= l && r <= R && sx(now) < num) {push_min(now, num); return ;}
		pushdown(now); int mid = (l + r) >> 1;
		if(L <= mid) insert(ls(now), l, mid, L, R, num);
		if(mid < R) insert(rs(now), mid + 1, r, L, R, num);
		pushup(now);
//		cout << now << " " << l << " " << r << " " << fsum(now) << " " << rsum(now) << " " << mx(now) << " " << sx(now) << '\n';
	}
	inline void cover(int now, int l, int r, int L, int R)
	{
		if(L <= l && r <= R) {push_cover(now); return ;}
		pushdown(now); int mid = (l + r) >> 1;
		if(L <= mid) cover(ls(now), l, mid, L, R);
		if(mid < R) cover(rs(now), mid + 1, r, L, R);
		pushup(now);
	}
	inline long long ask(int now, int l, int r, int L, int R)
	{
		if(L <= l && r <= R) return rsum(now);
		pushdown(now); int mid = (l + r) >> 1; long long ans = 0;
		if(L <= mid) ans += ask(ls(now), l, mid, L, R);
		if(mid < R) ans += ask(rs(now), mid + 1, r, L, R);
		return ans;
	}
}T[2];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	T[0].build(T[0].rt, 1, maxn);
	T[1].build(T[1].rt, 1, maxn);
	for(int i = 1; i <= n; ++i)
	{
		int opt, l, r, num;
		cin >> opt >> l >> r;
//		cout << "D " << i << '\n';
		if(opt == 1)
		{
			cin >> num;
			if(num > 0)
			{
				T[0].insert(T[0].rt, 1, maxn, l, r - 1, num);
				T[1].cover(T[1].rt, 1, maxn, l, r - 1);
			}
			else
			{
				num = -num;
				T[1].insert(T[1].rt, 1, maxn, l, r - 1, num);
				T[0].cover(T[0].rt, 1, maxn, l, r - 1);
			}
		}
		else
		{
			long long n1 = T[0].ask(T[0].rt, 1, maxn, l, r - 1);
			long long n2 = T[1].ask(T[1].rt, 1, maxn, l, r - 1);
			cout << n1 + n2 << '\n';
		}
	}
	return 0;
}
/*

*/
```

---

## 作者：cosf (赞：0)

提供一个非常抽象的做法。

我们可以把题目理解为，维护两个序列，初始均为全 $+\infty$，每次对某个序列的区间进行 $\min$ 操作，查询则是对两序列都不为 $+\infty$ 的位置进行求和。

假设不考虑自己为 $+\infty$ 的情况（即是否贡献只和另一序列有关），则可以开两个吉司机线段树。若当前对自己的区间操作，则在两棵线段树上都进行 $\min$ 操作；若当前对对方的区间操作，则在第二棵线段树上进行赋值为 $0$ 的操作（可以理解为对 $0$ 取 $\min$），则两树的差就是答案了。

但问题是，对方不为 $+\infty$，自己为 $+\infty$ 的位置都会给答案贡献一个不该有的 $+\infty$ 值。

于是有个策略：注意到答案不大于 $2 \times 10^{14}$ 次方，所以我们可以将 $+\infty$ 设为 $2^{50}$，算完区间和再二进制与上一个 $2^{50} - 1$ 即可。

```cpp
#include <iostream>
#include <limits>
using namespace std;

#define MAXN 100005

using ll = long long;

constexpr ll INF = 1ll << 50;
#define ANI(x) ((x) & (INF - 1))

struct SegTree // 吉司机常规操作
{
    struct Tree
    {
        ll mx, se;
        int cnt;
        ll sum;
        ll tm;
    } t[MAXN << 2];

#define ls (p << 1)
#define rs (p << 1 | 1)

    void pushup(int p)
    {
        t[p].sum = t[ls].sum + t[rs].sum;
        if (t[ls].mx == t[rs].mx)
        {
            t[p].mx = t[ls].mx;
            t[p].cnt = t[ls].cnt + t[rs].cnt;
            t[p].se = max(t[ls].se, t[rs].se);
        }
        else if (t[ls].mx > t[rs].mx)
        {
            t[p].mx = t[ls].mx;
            t[p].cnt = t[ls].cnt;
            t[p].se = max(t[ls].se, t[rs].mx);
        }
        else
        {
            t[p].mx = t[rs].mx;
            t[p].cnt = t[rs].cnt;
            t[p].se = max(t[ls].mx, t[rs].se);
        }
    }

    void pushtag(int p, int tm)
    {
        if (t[p].mx <= tm)
        {
            return;
        }
        t[p].sum -= 1ll * (t[p].mx - tm) * t[p].cnt;
        t[p].tm = t[p].mx = tm;
    }

    void pushdown(int p)
    {
        if (t[p].tm != INF)
        {
            pushtag(ls, t[p].tm);
            pushtag(rs, t[p].tm);
            t[p].tm = INF;
        }
    }

    void build(int p, int l, int r)
    {
        if (l == r)
        {
            t[p] = {INF, -INF, 1, INF, INF};
            return;
        }
        t[p].tm = INF;
        int mid = (l + r) >> 1;
        build(ls, l, mid);
        build(rs, mid + 1, r);
        pushup(p);
    }

    void rmin(int p, int l, int r, int ql, int qr, int tm)
    {
        if (t[p].mx <= tm)
        {
            return;
        }
        if (ql <= l && r <= qr && t[p].se < tm)
        {
            t[p].sum -= 1ll * (t[p].mx - tm) * t[p].cnt;
            t[p].mx = t[p].tm = tm;
            return;
        }
        pushdown(p);
        int mid = (l + r) >> 1;
        if (mid >= ql)
        {
            rmin(ls, l, mid, ql, qr, tm);
        }
        if (mid < qr)
        {
            rmin(rs, mid + 1, r, ql, qr, tm);
        }
        pushup(p);
    }

    ll sum(int p, int l, int r, int ql, int qr)
    {
        if (ql <= l && r <= qr)
        {
            return t[p].sum;
        }
        pushdown(p);
        int mid = (l + r) >> 1;
        ll res = 0;
        if (mid >= ql)
        {
            res += sum(ls, l, mid, ql, qr);
        }
        if (mid < qr)
        {
            res += sum(rs, mid + 1, r, ql, qr);
        }
        return res;
    }

} ta[2], tb[2];

int n;

int main()
{
    n = 100000;
    ta[0].build(1, 1, n);
    ta[1].build(1, 1, n);
    tb[0].build(1, 1, n);
    tb[1].build(1, 1, n);
    int q;
    cin >> q;
    while (q--)
    {
        int o, l, r, k;
        cin >> o >> l >> r;
        r--;
        if (o == 1)
        {
            cin >> k;
            if (k > 0)
            {
                ta[0].rmin(1, 1, n, l, r, k);
                ta[1].rmin(1, 1, n, l, r, k);
                tb[1].rmin(1, 1, n, l, r, 0);
            }
            else
            {
                tb[0].rmin(1, 1, n, l, r, -k);
                tb[1].rmin(1, 1, n, l, r, -k);
                ta[1].rmin(1, 1, n, l, r, 0);
            }
        }
        else
        {
            cout << ANI(ta[0].sum(1, 1, n, l, r) - ta[1].sum(1, 1, n, l, r) + tb[0].sum(1, 1, n, l, r) - tb[1].sum(1, 1, n, l, r)) << endl;
        }
    }
    return 0;
}
```

---

