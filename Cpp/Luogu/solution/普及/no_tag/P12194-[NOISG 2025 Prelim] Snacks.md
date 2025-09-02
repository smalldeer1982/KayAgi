# [NOISG 2025 Prelim] Snacks

## 题目描述

Shor 小鸭已经准备了 $n$ 个小吃盘子，准备一边看电影一边享用！第 $i$ 个盘子最初装有一个美味值为 $a[i]$ 的小吃。

你需要处理 $q$ 个查询。在第 $j$ 个查询中，Shor 将按顺序执行以下两个操作：

1. 吃掉所有美味值在 $l[j]$ 到 $r[j]$（包含）之间的小吃。
2. 然后，将每一个被吃掉的小吃替换为一个美味值为 $x[j]$ 的新小吃。

在处理任何查询之前，以及每次处理完查询之后，Shor 都希望你确定所有盘子中小吃的美味值总和。

形式化地说，给定一个长度为 $n$ 的数组 $a$，你必须处理 $q$ 个查询。在处理所有查询之前，打印 $a$ 中所有元素的总和。在第 $j$ 个查询中，将所有满足 $l[j] \leq a[i] \leq r[j]$ 的元素 $a[i]$ 更新为 $x[j]$，然后打印更新后的 $a$ 中所有元素的总和。


## 说明/提示

### 子任务

对于所有测试用例，输入将满足以下约束条件：

- $1 \leq n \leq 200\,000$
- $0 \leq q \leq 200\,000$
- $0 \leq a[i] \leq 10^9$ 对于所有 $1 \leq i \leq n$
- $0 \leq x[j] \leq 10^9$ 对于所有 $1 \leq j \leq q$
- $0 \leq l[j] \leq r[j] \leq 10^9$ 对于所有 $1 \leq j \leq q$

你的程序将在满足以下特殊性质的输入数据上进行测试：

| 子任务 | 分值 | 特殊性质 |
| :-: | :-: | :-: |
| $0$ | $0$ | 样例 |
| $1$ | $5$ | $q = 0$ |
| $2$ | $12$ | $n, q \leq 2000$ |
| $3$ | $21$ | $l[j] = r[j] \leq 200\,000$ 且 $a[i], x[j] \leq 200\,000$ |
| $4$ | $13$ | $l[j] = r[j]$ |
| $5$ | $16$ | $x[j] = 0$ |
| $6$ | $33$ | 无 |

### 样例 1 解释

此样例适用于子任务 $2, 3, 4, 6$。

### 样例 2 解释

此样例适用于子任务 $2, 5, 6$。

### 样例 3 解释

此样例适用于子任务 $2, 6$。

在所有查询之前，数组 $a$ 为 $[7, 72, 727, 123, 321, 9]$，总和为 $1259$。

第一次查询后，数组 $a$ 变为 $[10, 72, 727, 123, 321, 10]$，总和为 $1263$。

第二次查询后，数组 $a$ 变为 $[727, 727, 727, 123, 321, 727]$，总和为 $3352$。

第三次查询后，数组 $a$ 变为 $[727, 727, 727, 30, 321, 727]$，总和为 $3259$。

第四次查询后，数组 $a$ 变为 $[99, 99, 99, 30, 99, 99]$，总和为 $525$。

第五次查询后，数组 $a$ 变为 $[99, 99, 99, 30, 99, 99]$，总和为 $525$。


## 样例 #1

### 输入

```
5 3
1 6 2 4 6
6 6 3
2 2 3
3 3 5```

### 输出

```
19
13
14
20```

## 样例 #2

### 输入

```
6 4
929 121 5 3 919 72
1 133 0
70 79 0
900 999 0
1 1000 0```

### 输出

```
2049
1848
1848
0
0```

## 样例 #3

### 输入

```
6 5
7 72 727 123 321 9
7 9 10
10 72 727
111 222 30
123 727 99
111 222 333```

### 输出

```
1259
1263
3352
3259
525
525```

# 题解

## 作者：seika27 (赞：12)

### 思路
这是一道非常有趣的题目，可以用很多种方法解决。

我在这里提供一种 ```FHQ-treap``` 的做法。

我们发现这道题只有一种操作，就是将一个序列 $A$ 中所有的 $l\leq A_i \leq r$ 全部改为 $k$。

那么我们将这个操作分为三部分。

第一步在我们的 ```FHQ-treap``` 上分裂出 $x<l$，$l\leq x\leq r$，$r<x$ 这三部分。这一步非常简单，是基本操作，同时，我们令分裂出来三部分的根节点分别为 $sx$，$sy$，$sz$。

第二步合并 $sx$ 和 $sz$，这一步相当与删除了 $sy$。

第三步，往我们的 ```FHQ-treap``` 中塞入 $siz_{sy}$ 个 $k$。我们知道，原本 ```FHQ-treap``` 中，同一个数是不会在同一个节点的。但是在这里，我们考虑给每个节点多一个 $cnt$ 值。表示这个节点拥有 $cnt$ 个值为 $val$的数字。

既然如此，在 ```push_up``` 中 $siz$ 的更新就会变成 $siz_x=siz_
{ls}+siz_{rs}+cnt_x$。

既然是统计和，所以维护 $sum$ 是显然的。

接下来我们探讨一个问题，我们根据 $l$ 和 $r$ 进行分裂，最后却插入的是 $k$。会不会打破左小右大的规则呢。

答案是不会，这里关键就在于我们是先把 $sx$ 和 $sz$ 合并了，然后在合并完的 ```FHQ-treap``` 上重新做了一次普通的插入操作。这样我们就不用担心会出现上文所述的问题了。

代码不是很好，请见谅。

### code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,q;
const int N=7e5+5;
struct fhqarr{int ls,rs,val,cnt,rnd,siz,sum;};
struct fhqtreap
{
	fhqarr b[N];
	int tot;
	int rt;
	int sx,sy,sz;
	inline int newnode(int x,int res)
	{
		b[++tot].val=x;
		b[tot].cnt=res;
		b[tot].sum=x*res;
		b[tot].rnd=rand();
		b[tot].siz=res;
		return tot;
	}
	inline void up(int x)
	{
		b[x].siz=b[b[x].ls].siz+b[b[x].rs].siz+b[x].cnt;
		b[x].sum=b[b[x].ls].sum+b[b[x].rs].sum+b[x].cnt*b[x].val;
		return;
	}
	void split(int x,int k,int &u,int &v)
	{
		if(!x){u=v=0;return;}
		if(b[x].val<=k)u=x,split(b[x].rs,k,b[x].rs,v);
		else v=x,split(b[x].ls,k,u,b[x].ls);
		up(x);
	}
	int merge(int x,int y)
	{
		if(!x||!y)return x+y;
		if(b[x].rnd<b[y].rnd)
		{
			b[x].rs=merge(b[x].rs,y);
			up(x);
			return x;
		}
		else 
		{
			b[y].ls=merge(x,b[y].ls);
			up(y);
			return y;
		}
	}
	inline void insert(int v,int p)
	{
		split(rt,v,sx,sy);
		rt=merge(merge(sx,newnode(v,p)),sy);
		return;
	}
	inline void update(int l,int r,int k)
	{
		split(rt,r,sx,sz);
		split(sx,l-1,sx,sy);
		int slv=b[sy].siz;
		rt=merge(sx,sz);
		insert(k,slv);
		return;
	}
}momoka;
signed main()
{
	srand(time(0));
	ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>q;
	for(int i=1,x;i<=n;++i)cin>>x,momoka.insert(x,1);
	cout<<momoka.b[momoka.rt].sum<<'\n';
	while(q--)
	{
		int l,r,k;
		cin>>l>>r>>k;
		momoka.update(l,r,k);
		cout<<momoka.b[momoka.rt].sum<<'\n';
	}
	return 0;
}
```

---

## 作者：shuqiang (赞：4)

这题如果用好 STL 其实并不难。

观察到修改只与数值有关，与数字所在位置无关，考虑存每个数字出现的次数，用一个 set 套 pair 即可，显然，修改不会增加数字的种数，所以这个结构最多会被修改 $n+q$ 次，时间复杂度 $\mathcal{O}(n+q \log (n+q))$，可以通过。


```cpp
#include<iostream>
#include<set>

using namespace std;
typedef long long ll;

int n, q, x, l, r; ll ans = 0;
set<pair<int, int> > st;

int main(){
	cin >> n >> q;
	for(int i = 1; i <= n; i++){
		cin >> x;
		auto it = st.lower_bound({x, 0});
		if(it == st.end() || (*it).first != x){
			st.insert({x, 1});
		}
		else{
			int ft = (*it).first, sc = (*it).second;
			st.erase(it);
			st.insert({ft, sc+1});
		}
		ans += x;
	}
	cout << ans << '\n';
	while(q--){
		cin >> l >> r >> x;
		auto it = st.lower_bound({l, 0}); ll w = 0;
		while(1){
			if(it == st.end() || (*it).first > r) break;
			w += (*it).second;
			ans -= (ll)(*it).first * (*it).second;
			st.erase(it);
			it = st.lower_bound({l, 0});
		}
		it = st.lower_bound({x, 0});
		if(it == st.end() || (*it).first != x){
			st.insert({x, w});
		}
		else{
			int ft = (*it).first, sc = (*it).second;
			st.erase(it);
			st.insert({ft, sc+w});
		}
		ans += (ll)x * w;
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：OIer_Tan (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P12194)

为啥手写数据结构，直接 `std::map` 不香吗。

## 思路

容易发现，数字的总数量不会变得太多（其实也不会变），而每次更改的全都是排序后连续的一段数，容易想到直接用 `std::map` 记每种数的个数，然后每次在 `std::map` 上删掉一段数并计数量，最后再将 $x$ 加入 `std::map` 中并更改总和即可。

## 代码

```cpp
#include <bits/stdc++.h>

#ifndef CRT
#define endl '\n'
#endif

using namespace std ;

typedef long long ll ;
typedef unsigned long long ull ;
typedef long double ld ;

const ll N = 200005 ;

ll n , q ;

ll a[ N] ;

map <ll,ll> s ;

int main ()
{
#if not defined ( CRCC ) and not defined ( ONLINE_JUDGE )
	freopen ( ".in" , "r" , stdin ) ;
	freopen ( ".out" , "w" , stdout ) ;
#endif
	ios::sync_with_stdio ( 0 ) ;
	cin.tie ( 0 ) ;
	cout.tie ( 0 ) ;
	cin >> n >> q ;
	ll sum = 0 ;
	for ( ll i = 1 ; i <= n ; i++ )
	{
		cin >> a [i] ;
	}
	for ( ll i = 1 ; i <= n ; i ++ )
	{
		sum += a [i] ;
		s [a [i]] ++ ;
	}
	cout << sum << endl ;
	while ( q -- )
	{
		ll l , r , x ;
		cin >> l >> r >> x ;
		auto it = s.lower_bound ( l ) ;
		ll cnt = 0 ;
		while ( it != s.end () && it -> first <= r )
		{
			cnt += it -> second ;
			sum -= it -> first * it -> second ;
			it = s.erase ( it ) ;
		}
		s [x] += cnt ;
		sum += cnt * x ;
		cout << sum << endl ;
	}
	return 0 ;
}
```

---

## 作者：bbbzzx (赞：3)

# FHQ-Treap
看到机房大佬全在写权值线段树，但是很难调，有人干脆调不出来放弃了，于是笔者突发奇想用刚学的 FHQ-Treap，可能是笔者思维不够，有点小题大做了，跑的也很慢。

看题目，发现有个权值区间操作，即把 $\forall l \leq a_i \leq r$ 都改为 $x$，这个刚好可以用 FHQ 的权值分裂来解决，至于求和，我们再在树上维护一个和数组，pushup 的时候更新即可。

# Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define inf 1e18
#define gc getchar
#define pc putchar
#define rg register
#define LB lower_bound
#define UB upper_bound
#define PII pair<int, int> 
#define PDI pair<double, int>
#define fi first
#define se second
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using db=long double;
using ll=long long;
using ull=unsigned long long;
using namespace std;
namespace IO{
	inline int read(){
		int x=0,f=1;
		char ch=gc();
		while(!isdigit(ch)){
			if(ch=='-')	f=-f;
			ch=gc();
		}
		while(isdigit(ch)) x=(x<<3)+(x<<1)+ch-'0',ch=gc();
		return x*f;
	}
	inline void write(int x){
		if(x<0) pc('-'),x=-x;
		if(x>9)	write(x/10);
		pc(x%10+'0');
	}
}
using namespace IO;
const int N=1e6+10;
struct FHQ{
	#define ls(i) tree[i][0]
	#define rs(i) tree[i][1]
	int root,tot,tree[N][2],size[N];
	int val[N],pri[N],cnt[N],sum[N];
	inline int newnode(int x, int num){
		int u=++tot;
		pri[u]=rand();
		val[u]=x,size[u]=num,ls(u)=rs(u)=0;
		cnt[u]=num,sum[u]=val[u]*cnt[u];
		return u;
	}
	inline void pushup(int u){
		size[u]=size[ls(u)]+size[rs(u)]+cnt[u];
		sum[u]=sum[ls(u)]+sum[rs(u)]+val[u]*cnt[u];
	}
	inline void split(int u, int x, int &L, int &R){
		if(!u){L=R=0;return;}
		if(val[u]<=x){L=u;split(rs(u),x,rs(u),R);}
		else{R=u;split(ls(u),x,L,ls(u));}
		pushup(u);
	}
	inline int _merge(int L, int R){
		if(!L||!R) return L+R;
		if(pri[L]<pri[R]){
			rs(L)=_merge(rs(L),R);
			pushup(L);return L;
		}else{
			ls(R)=_merge(L,ls(R));
			pushup(R);return R;
		}
	}
	inline void insert(int w, int num){
		int L,R;
		split(root,w,L,R);
		int u=newnode(w,num);
		int tmp=_merge(L,u);
		root=_merge(tmp,R);
	}
	inline void solve(int l, int r, int x){
		int L,R,p;
		split(root,r,L,R);
		split(L,l-1,L,p);//权值分裂 
		int tmp=size[p];
		root=_merge(L,R);
		insert(x,tmp);//重新插入 x 
		write(sum[root]);puts("");
	}
}T;
int n,q,a[N],tot;
signed main(){
	srand(20100102);
	n=read(),q=read();
	for(rg int i=1;i<=n;i++) a[i]=read(),T.insert(a[i],1);
	write(T.sum[T.root]);puts("");
	while(q--){
		int l=read(),r=read(),x=read();
		T.solve(l,r,x);
	}
	return 0;
}
```

开 2e5 不知道为啥 RE 了，然后就随手开了个 1e6。

PS：为啥要评黄啊？
$$End$$

---

## 作者：wangyanjing (赞：2)

PS：记录一下自己的做法。
# Think
已知：
- 每一个小吃只会被删掉 $1$ 次。
- 每一个操作只会新增一种之前没出现的数 $x_i$。
 
考虑维护每个数出现次数。

单点操作最多 $(n + q)$ 次。

所以，基于这道题的性质，我们可以每次找到区间中需要修改的数的位置，再单点修改就可以了。

把 $a,l,r,x$ 一起离散化。

记：在 $[l_i,r_i]$ 中出现最多的次数为 $cnt$。

依次执行以下操作即可（$cnt = 0$ 时停止）：
- 找到 $cnt$ 及 出现 $cnt$ 次的数 $w$。
- 删掉所有的 $w$。
# Solution
开一棵线段树，维护值域中每个数的在 $a$ 中的出现次数，支持：
- 查询 $[l_i,r_i]$ 中出现最多次的数，以及这个数的出现次数。
- 修改一个数的出现次数。

即：单点修改，区间查最大值的线段树。

在统计答案即可。

注意：各个数组的空间，别开小了qwq。

# Code 

```cpp
#include<cstdio>
#include<algorithm>
#define ll long long
const ll N = 2e5+5;
ll a[N],l[N],r[N],x[N],cnt[N<<2],tmp[N<<2];
struct Info{
	ll Max,Pos;
	inline bool operator > (const Info x)const{
		return Max > x.Max;
	}
};
inline Info max(Info a,Info b){return a>b?a:b;}
struct Segment_Tree{
	struct Tree{
		ll lson,rson;
		Info data;
	}tree[N<<3];
	ll root,total = 0;
	inline void push_up(ll rt){
		tree[rt].data = max(tree[tree[rt].lson].data,tree[tree[rt].rson].data);
	}
	inline void build(ll &rt,ll l,ll r){
		rt = ++total;
		if(l == r) return ;
		ll mid = l + r >> 1;
		build(tree[rt].lson,l,mid);
		build(tree[rt].rson,mid+1,r);
	}
	inline void Update(ll rt,ll treeL,ll treeR,ll pos,Info val){
		if(treeL == treeR) return void(tree[rt].data = val);
		ll mid = treeL + treeR >> 1;
		if(pos<=mid) Update(tree[rt].lson,treeL,mid,pos,val);
		else Update(tree[rt].rson,mid+1,treeR,pos,val);
		push_up(rt);
	}
	inline Info Ask(ll rt,ll treeL,ll treeR,ll askL,ll askR){
		if(askL <= treeL && treeR <= askR) return tree[rt].data;
		ll mid = treeL + treeR >> 1;
		if(askR<=mid) return Ask(tree[rt].lson,treeL,mid,askL,askR);
		if(askL>mid) return Ask(tree[rt].rson,mid+1,treeR,askL,askR);
		return max(Ask(tree[rt].lson,treeL,mid,askL,askR),Ask(tree[rt].rson,mid+1,treeR,askL,askR));
	}
}T;
int main(){
	ll n,q,len = 0;
	std::scanf("%lld %lld",&n,&q); 
	for(ll i = 1;i<=n;++i){
		std::scanf("%lld",a+i);
		tmp[++len] = a[i];
	}
	for(ll i = 1;i<=q;++i){
		std::scanf("%lld %lld %lld",l+i,r+i,x+i);
		tmp[++len] = l[i];
		tmp[++len] = r[i];
		tmp[++len] = x[i];
	}
	std::sort(tmp+1,tmp+len+1);
	len = std::unique(tmp+1,tmp+len+1)-tmp-1;
	ll Sum = 0;
	for(ll i = 1;i<=n;++i){
		Sum += a[i];
		a[i] = std::lower_bound(tmp+1,tmp+len+1,a[i]) - tmp;
		++cnt[a[i]];
	}
	for(ll i = 1;i<=q;++i){
		l[i] = std::lower_bound(tmp+1,tmp+len+1,l[i]) - tmp;
		r[i] = std::lower_bound(tmp+1,tmp+len+1,r[i]) - tmp;
		x[i] = std::lower_bound(tmp+1,tmp+len+1,x[i]) - tmp;
	}
	T.build(T.root,1,len);
	for(ll i = 1;i<=len;++i)
		if(cnt[i]) T.Update(T.root,1,len,i,(Info){cnt[i],i});
	std::printf("%lld\n",Sum);
	for(ll i = 1;i<=q;++i){
		Info ans = T.Ask(T.root,1,len,l[i],r[i]); 
		ll Xcnt = 0;
		while(ans.Max){
			Sum += (tmp[x[i]] - tmp[ans.Pos]) * ans.Max;
			Xcnt += ans.Max;
			T.Update(T.root,1,len,ans.Pos,(Info){0,0});
			ans = T.Ask(T.root,1,len,l[i],r[i]);
		} 
		Xcnt += T.Ask(T.root,1,len,x[i],x[i]).Max;
		T.Update(T.root,1,len,x[i],(Info){Xcnt,x[i]});
		std::printf("%lld\n",Sum);
	}
	return 0;
}

```
时间复杂度：$O((n+q) \log n)$。

---

## 作者：StarTwinkleTwinkle (赞：2)

## [NOISG 2025 Prelim] Snacks

### Problem
你有一个长度为 $n$ 的序列 $a$，你要进行 $q$ 次操作，在操作前输出 $a$ 序列中所有数的和，然后将所有 $l \leq a_i \leq r$ 的 $a_i$ 改为 $x$。


### Solution

考虑维护每个值的出现次数和用一个 set 维护当前的值的集合，注意到 $q$ 次询问后最多增加 $q$ 个新的值，且原来删去的会永远删去，所以直接做均摊复杂度是对的，时间复杂度为 $O(q \log n)$，可以通过本题。


### Code

```cpp
#include <bits/stdc++.h>
#define int long long
int n, q;
int v[200005], ans;
std::unordered_map<int, int> mp;
std::set<int> se;
int32_t main() {
	std::cin >> n >> q;
	se.insert(1e18); 
	for(int i = 1; i <= n; i++){
		std::cin >> v[i];
		mp[v[i]]++;
		se.insert(v[i]);
		ans = ans + v[i]; 
	}
	std::cout << ans << '\n';
	while(q--){
		int num = 0, l, r, x;
		std::cin >> l >> r >> x;
		l = *se.lower_bound(l);
		while(l <= r){
			int L = *se.lower_bound(l);
			if(L <= r){
			    num = num + mp[L];
			    ans = ans - mp[L] * L;
			    se.erase(L);
			    mp[L] = 0;
			    l = L + 1;
			}
			else break; 
        }
        se.insert(x);
        mp[x] = mp[x] + num;
        ans = ans + x * num;
        std::cout << ans << '\n';
	}
}
```

---

## 作者：Invisible_H (赞：2)

# P12194 [NOISG 2025 Prelim] Snacks 题解

提供无脑的解法。

对于每次操作我们需要将一定值域内的数都变为一个数。

果断使用离散化+值域线段树。

每次操作就是将值域线段树内 $l$ 到 $r$ 的全部修改为 $0$ ，再把 $x$ 的数量加上删去数的数量即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long MX=500000;
const __int128 MO=1e20;
struct node{
	long long lc,rc;
	__int128 sum,lazy;
}tree[MX<<1];
long long root,cnt;
inline void update(long long now){
	tree[now].sum=tree[tree[now].lc].sum+tree[tree[now].rc].sum;
}
inline void add_node(long long now,long long lt,long long rt,__int128 val){
	tree[now].sum=(rt-lt+1)*val;
	tree[now].lazy=val;
}
inline void pushdown(long long now,long long lt,long long rt){
	if(tree[now].lazy!=-1){
		long long mid=(lt+rt-1)>>1;
		add_node(tree[now].lc,lt,mid,tree[now].lazy);
		add_node(tree[now].rc,mid+1,rt,tree[now].lazy);
		tree[now].lazy=-1;
	}
}
void add(long long &now,long long lt,long long rt,long long l,long long r,__int128 val){
	if(lt>r||rt<l)  return ;
	if(!now)  now=++cnt,tree[now].lazy=-1;
	if(l<=lt&&rt<=r)  return add_node(now,lt,rt,val);
	long long mid=(lt+rt-1)>>1;pushdown(now,lt,rt);
	add(tree[now].lc,lt,mid,l,r,val),add(tree[now].rc,mid+1,rt,l,r,val);
	return update(now);
}

__int128 cy(long long now,long long lt,long long rt,long long l,long long r){
	if(lt>r||rt<l)  return 0;
	if(l<=lt&&rt<=r)  return tree[now].sum;
	long long mid=(lt+rt-1)>>1;pushdown(now,lt,rt);
	return cy(tree[now].lc,lt,mid,l,r)+cy(tree[now].rc,mid+1,rt,l,r);
}

long long mid[MX*10],len;
long long input[MX],n;
long long L[MX],R[MX],X[MX],q;
void li(){
	for(long long i=1;i<=n;i++)  mid[i]=input[i];
	for(long long i=1;i<=q;i++)  mid[i+n]=L[i];
	for(long long i=1;i<=q;i++)  mid[i+n+q]=R[i];
	for(long long i=1;i<=q;i++)  mid[i+n+q+q]=X[i];
	sort(mid+1,mid+1+n+q+q+q);
	len=unique(mid+1,mid+1+n+q+q+q)-mid-1;
	for(long long i=1;i<=n;i++)  input[i]=lower_bound(mid+1,mid+1+len,input[i])-mid;
	for(long long i=1;i<=q;i++)  L[i]=lower_bound(mid+1,mid+1+len,L[i])-mid;
	for(long long i=1;i<=q;i++)  R[i]=lower_bound(mid+1,mid+1+len,R[i])-mid;
	for(long long i=1;i<=q;i++)  X[i]=lower_bound(mid+1,mid+1+len,X[i])-mid;
	for(long long i=1;i<=len;i++)  add(root,1,len,i,i,0);
}
signed main(){
	scanf("%lld%lld",&n,&q);
	for(long long i=1;i<=n;i++)  scanf("%lld",input+i);
	for(long long i=1;i<=q;i++)  scanf("%lld%lld%lld",L+i,R+i,X+i);
	li();
	for(long long i=1;i<=n;i++)  add(root,1,len,input[i],input[i],MO+cy(root,1,len,input[i],input[i])+mid[input[i]]);
	printf("%lld\n",(long long)(cy(root,1,len,1,len)%MO));
	for(long long i=1;i<=q;i++){
		__int128 sum=cy(root,1,len,L[i],R[i])/MO;
		add(root,1,len,L[i],R[i],0);
		add(root,1,len,X[i],X[i],cy(root,1,len,X[i],X[i])+MO*sum+sum*mid[X[i]]);
		printf("%lld\n",(long long)(cy(root,1,len,1,len)%MO));	
	}
	return 0;
}
```

---

## 作者：langmouren (赞：1)

# FHQ Treap
## 题目分析

本题进行了三种操作：

- 删除一个权值区间内的所有值。
- 插入 $k$ 个相同的值 $x$。
- 输出整体的和。

很显然，第一种操作可以通过 FHQ Treap 进行分裂后再合并完成。复杂度 $O(\log n)$。

第二种操作可以通过输出根节点维护的 $sum$ 来实现。

但是，第二种操作如果使用单点插入的话，会使得复杂度过大，为 $O(k \log n)$。考虑最坏情况，即当 $k=n$ 时，整体复杂度为 $O(n^2 \log n)$，这个复杂度显然不能接受。

因此，我们考虑额外维护一些信息。

## 具体分析

对于每个节点，我们维护以下信息：

- $rnd$：用来维护 FHQ Treap 的性质。
- $sz$：当前节点及其子树的大小。
- $val$：当前节点的权值。
- $cnt$：当前节点所维护的权值的数量。
- $sum$：当前节点机器子树的权值之和。

因此，我们定义函数 `clone()` 用来新建节点：

::::info[代码实现]
```cpp
int clone(int k,int cnt){
    int tmp=++tot;
    tre[tmp].sz=cnt;
    tre[tmp].val=k;
    tre[tmp].rnd=rand();
    tre[tmp].cnt=cnt;
    tre[tmp].sum=k*cnt;
    return tmp;
}
```
::::

然后 pushup 时维护 $sz$ 和 $sum$：

::::info[代码实现]
```cpp
void pushup(int p){
    int left=tre[p].left,right=tre[p].right;

    tre[p].sz=tre[left].sz+tre[right].sz+tre[p].cnt;
    tre[p].sum=tre[left].sum+tre[right].sum+tre[p].cnt*tre[p].val;
}
```
::::

插入时，如果原本没有这个权值，就直接新建节点；如果有，就把新的贡献统计进去：

::::info[代码实现]
```cpp
void insert(int k,int cnt){
    int x,y,z;
    
    split(root,x,y,k);
    split(x,x,z,k-1);
    if(z){
        tre[z].cnt+=cnt;
        tre[z].sz += cnt;      // 多了这行
        tre[z].sum += k * cnt;
    }else z=clone(k,cnt);
    root=merge(merge(x,z),y);
}
```
::::

## 代码实现
::::info[完整代码]
```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long

const int MN=4e5+10;
struct Tre{
    int left,right;
    int sz,val,rnd,sum,cnt;
}tre[MN];
int n,q,tot,root;

int clone(int k,int cnt){
    int tmp=++tot;
    tre[tmp].sz=cnt;
    tre[tmp].val=k;
    tre[tmp].rnd=rand();
    tre[tmp].cnt=cnt;
    tre[tmp].sum=k*cnt;
    return tmp;
}

void pushup(int p){
    int left=tre[p].left,right=tre[p].right;

    tre[p].sz=tre[left].sz+tre[right].sz+tre[p].cnt;
    tre[p].sum=tre[left].sum+tre[right].sum+tre[p].cnt*tre[p].val;
}

void split(int p,int &x,int &y,int k){
    if(!p){
        x=y=0;
        return;
    }

    if(tre[p].val<=k){
        x=p;
        split(tre[p].right,tre[p].right,y,k);
    }else{
        y=p;
        split(tre[p].left,x,tre[p].left,k);
    }
    pushup(p);
}

int merge(int x,int y){
    if(!x || !y) return x+y;

    if(tre[x].rnd<tre[y].rnd){
        tre[x].right=merge(tre[x].right,y);
        pushup(x);
        return x;
    }else{
        tre[y].left=merge(x,tre[y].left);
        pushup(y);
        return y;
    }
}

void insert(int k,int cnt){
    int x,y,z;
    
    split(root,x,y,k);
    split(x,x,z,k-1);
    if(z){
        tre[z].cnt+=cnt;
        tre[z].sz += cnt;
        tre[z].sum += k * cnt;
    }else z=clone(k,cnt);
    root=merge(merge(x,z),y);
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    srand(time(0));
    cin>>n>>q;

    for(int i=1;i<=n;i++){
        int tmp;
        cin>>tmp;
        insert(tmp,1);
    }

    cout<<tre[root].sum<<"\n";

    for(int i=1;i<=q;i++){
        int l,r,k,x,y,z;
        cin>>l>>r>>k;

        split(root,x,y,r);
        split(x,x,z,l-1);

        root=merge(x,y);

        insert(k,tre[z].sz);

        cout<<tre[root].sum<<"\n";
    }
    return 0;
}
```
::::

---

## 作者：TangyixiaoQAQ (赞：1)

# 题目简析

给定长度为 $n$ 的序列，$q$ 次询问，把在 $[l,r]$ 内的元素覆盖为 $x$。

求最初的和每次询问时元素之和。

# 思路解析

## 动态开点权值线段树

对于在区间的操作容易想到线段树，线段树支持区间查询、区间清零和单点更新。

用动态开点权值线段树维护值域上的元素个数和总和。


时间复杂度 $O(q \log V)$，其中 $V$ 是值域范围（$0 \le V \le10^9$），可以考虑离散化。

## 平衡树（FHQ-Treap）

使用 FHQ-Treap 维护值域。每个节点存储一个值 $val$，该值出现的次数 $cnt$，子树总和 $sum$，子树总节点数 $tot$。

对于每个查询：

- 分裂出值在 $[l, r]$ 范围内的节点。

- 删除这部分，合并剩余部分。

- 计算被删除的节点数 $cnt$ 和总和 $sum$。

- 插入 $cnt$ 个新值 $x$。

时间复杂度 $O((n + q) \log n )$。

## STL


使用 **`std::map`** 存储每个值及其出现次数，维护值域到出现次数的映射，这样我们可以快速查找、删除和插入值。

使用 `lower_bound` 和 `upper_bound` 快速查找。


时间复杂度 $ O((n + q) \log n)$。

## 珂朵莉树

珂朵莉树特别适合有大量区间赋值操作，只需要考虑如何维护和就可以了。

直接操作值域点，利用 `std::set` 定位值域范围，合并相同值节点，这样，就可以 AC 了。

详见 [OI WIKI 上的珂朵莉树](https://oi-wiki.org/misc/odt)。

时间复杂度 $O((n + q) \log D)$，其中 $D \le n + q$，$D$ 为不同值的数量。
# 代码实现


**动态开点权值线段树**实现：

```cpp
#pragma G++ optimize("O3", "unroll-loops", "omit-frame-pointer", "inline")
#include <bits/stdc++.h>
using namespace std;
const int MAXV = 1000000000;
const int MAXNODE = 20000000;
struct Node {
    int lson, rson;
    long long sum;
    long long cnt;
    bool zero;
} tree[MAXNODE + 10];
int root, tot;

void push_up(int p) {
    tree[p].cnt = 0;
    tree[p].sum = 0;
    if (tree[p].lson) {
        tree[p].cnt += tree[tree[p].lson].cnt;
        tree[p].sum += tree[tree[p].lson].sum;
    }
    if (tree[p].rson) {
        tree[p].cnt += tree[tree[p].rson].cnt;
        tree[p].sum += tree[tree[p].rson].sum;
    }
}

void push_down(int p) {
    if (tree[p].zero) {
        if (tree[p].lson) {
            int ls = tree[p].lson;
            tree[ls].cnt = 0;
            tree[ls].sum = 0;
            tree[ls].zero = true;
        }
        if (tree[p].rson) {
            int rs = tree[p].rson;
            tree[rs].cnt = 0;
            tree[rs].sum = 0;
            tree[rs].zero = true;
        }
        tree[p].zero = false;
    }
}

void update_point(int& p, int l, int r, int pos, long long delta_cnt) {
    if (delta_cnt == 0)
        return;
    if (!p) {
        p = ++tot;
        tree[p].lson = tree[p].rson = 0;
        tree[p].sum = 0;
        tree[p].cnt = 0;
        tree[p].zero = false;
    }
    if (l == r) {
        tree[p].cnt += delta_cnt;
        tree[p].sum = tree[p].cnt * (long long)l;
        return;
    }
    push_down(p);
    int mid = (l + (long long)r) >> 1;
    if (pos <= mid) {
        update_point(tree[p].lson, l, mid, pos, delta_cnt);
    } else {
        update_point(tree[p].rson, mid + 1, r, pos, delta_cnt);
    }
    push_up(p);
}

void update_zero(int& p, int l, int r, int ql, int qr) {
    if (!p || tree[p].cnt == 0)
        return;
    if (ql <= l && r <= qr) {
        tree[p].cnt = 0;
        tree[p].sum = 0;
        tree[p].zero = true;
        return;
    }
    push_down(p);
    int mid = (l + (long long)r) >> 1;
    if (ql <= mid) {
        update_zero(tree[p].lson, l, mid, ql, qr);
    }
    if (qr > mid) {
        update_zero(tree[p].rson, mid + 1, r, ql, qr);
    }
    push_up(p);
}

pair<long long, long long> query(int p, int l, int r, int ql, int qr) {
    if (!p || tree[p].cnt == 0) {
        return {0, 0};
    }
    if (ql <= l && r <= qr) {
        return {tree[p].sum, tree[p].cnt};
    }
    push_down(p);
    int mid = (l + (long long)r) >> 1;
    pair<long long, long long> res = {0, 0};
    if (ql <= mid) {
        auto left_res = query(tree[p].lson, l, mid, ql, qr);
        res.first += left_res.first;
        res.second += left_res.second;
    }
    if (qr > mid) {
        auto right_res = query(tree[p].rson, mid + 1, r, ql, qr);
        res.first += right_res.first;
        res.second += right_res.second;
    }
    return res;
}
long long a[(int)(2e5 + 1)];
int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    long long total = 0;
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
        total += a[i];
    }

    root = 0;
    tot = 0;
    for (int i = 0; i < n; i++) {
        update_point(root, 0, MAXV, a[i], 1);
    }

    printf("%lld\n", total);

    for (int j = 0; j < q; j++) {
        long long l, r, x;
        scanf("%lld %lld %lld", &l, &r, &x);
        auto res = query(root, 0, MAXV, l, r);
        long long remove_sum = res.first;
        long long remove_cnt = res.second;

        update_zero(root, 0, MAXV, l, r);
        if (remove_cnt > 0) {
            update_point(root, 0, MAXV, x, remove_cnt);
        }

        total = total - remove_sum + x * remove_cnt;
        printf("%lld\n", total);
    }

    return 0;
}
```

**FHQ-Treap** 实现：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 400010; // 最大节点数

struct Node {
    int l, r;       // 左右子节点索引
    ll val;         // 节点存储的值
    ll cnt;         // 该值出现的次数
    ll sum;         // 子树值总和（值×出现次数）
    ll tot;         // 子树节点出现次数总和
    int rnd;        // 随机优先级
} tree[MAXN];

int idx = 0;        // 节点池索引
int root = 0;       // 树根

// 创建新节点
int new_node(ll val, ll cnt) {
    if (cnt == 0) return 0;
    idx++;
    tree[idx].l = tree[idx].r = 0;
    tree[idx].val = val;
    tree[idx].cnt = cnt;
    tree[idx].sum = val * cnt;
    tree[idx].tot = cnt;
    tree[idx].rnd = rand();
    return idx;
}

// 更新节点信息
void push_up(int id) {
    if (!id) return;
    Node &t = tree[id];
    t.tot = tree[t.l].tot + tree[t.r].tot + t.cnt;
    t.sum = tree[t.l].sum + tree[t.r].sum + t.val * t.cnt;
}

// 按值分裂：将树id分裂为<=k的树x和>k的树y
void split(int id, ll k, int &x, int &y) {
    if (!id) {
        x = y = 0;
        return;
    }
    if (tree[id].val <= k) {
        x = id;
        split(tree[id].r, k, tree[id].r, y);
        push_up(x);
    } else {
        y = id;
        split(tree[id].l, k, x, tree[id].l);
        push_up(y);
    }
}

// 合并两棵树x和y（x的所有值<=y的所有值）
int merge(int x, int y) {
    if (!x || !y) return x | y;
    if (tree[x].rnd < tree[y].rnd) {
        tree[x].r = merge(tree[x].r, y);
        push_up(x);
        return x;
    } else {
        tree[y].l = merge(x, tree[y].l);
        push_up(y);
        return y;
    }
}

// 插入cnt个值为val的节点
void insert(ll val, ll cnt) {
    if (cnt == 0) return;
    int x, y, z;
    z = 0;
    split(root, val, x, y);      // 分裂为<=val和>val
    split(x, val - 1, x, z);    // 将<=val的再分裂为<val和=val
    if (z) {
        tree[z].cnt += cnt;
        tree[z].sum += val * cnt;
        tree[z].tot += cnt;
        push_up(z); // 更新节点z
    } else {
        z = new_node(val, cnt);
    }
    root = merge(merge(x, z), y); // 合并三部分
}

int main() {
    srand(time(0)); // 初始化随机种子
    int n, q;
    scanf("%d%d", &n, &q);
    root = idx = 0;

    // 读入初始数组
    for (int i = 0; i < n; i++) {
        ll a_val;
        scanf("%lld", &a_val);
        insert(a_val, 1); // 插入每个值
    }

    // 输出初始总和
    printf("%lld\n", tree[root].sum);

    // 处理每个查询
    for (int i = 0; i < q; i++) {
        ll l, r, x_val;
        scanf("%lld%lld%lld", &l, &r, &x_val);
        int left, mid, right, mid_right;

        // 第一次分裂：按l-1分裂
        split(root, l - 1, left, mid_right);
        // 第二次分裂：按r分裂
        split(mid_right, r, mid, right);

        // 合并左部分和右部分（删除中间部分）
        root = merge(left, right);

        ll del_cnt = 0, del_sum = 0;
        if (mid) {
            del_cnt = tree[mid].tot; // 被删除的节点数
            del_sum = tree[mid].sum; // 被删除节点的总和
        }

        // 插入新值
        insert(x_val, del_cnt);

        // 输出当前总和
        printf("%lld\n", tree[root].sum);
    }

    return 0;
}
```
**`std::map`** 实现

```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    map<ll, ll> m; // 值 -> 出现次数
    ll total_sum = 0;

    // 读入初始数组
    for (int i = 0; i < n; i++) {
        ll a_val;
        cin >> a_val;
        m[a_val]++; // 计数
        total_sum += a_val;
    }

    // 输出初始总和
    cout << total_sum << '\n';

    for (int i = 0; i < q; i++) {
        ll l, r, x;
        cin >> l >> r >> x;

        // 找到第一个大于等于 l 的节点
        auto it = m.lower_bound(l);
        ll cnt_total = 0; // 记录被删除的元素总数

        // 遍历区间 [l, r] 内的节点
        while (it != m.end() && it->first <= r) {
            // 记录当前节点的值和出现次数
            ll num = it->first;
            ll cnt = it->second;
            cnt_total += cnt;
            total_sum -= num * cnt; // 从总和中减去贡献
            
            // 删除当前节点，并获取下一个节点的迭代器
            it = m.erase(it);
        }

        // 如果存在被删除的元素，则将它们替换为 x
        if (cnt_total > 0) {
            m[x] += cnt_total; // 增加 x 的出现次数
            total_sum += x * cnt_total; // 更新总和
        }

        // 输出当前总和
        cout << total_sum << '\n';
    }

    return 0;
}
```
**珂朵莉树**实现：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// 节点结构体：表示值域区间 [v, v]
struct Node {
    ll v;           // 元素值
    mutable ll cnt; // 该值出现的次数
    
    Node(ll v, ll cnt) : v(v), cnt(cnt) {}
    
    // 按值排序
    bool operator<(const Node& rhs) const {
        return v < rhs.v;
    }
};

class ChthollyTree {
private:
    set<Node> s;    // 存储所有值域节点
    ll total_sum;   // 当前总和

public:
    ChthollyTree() : total_sum(0) {}
    
    // 添加初始元素
    void add_element(ll value) {
        auto it = s.find(Node(value, 0));
        if (it != s.end()) {
            it->cnt++;
        } else {
            s.insert(Node(value, 1));
        }
        total_sum += value;
    }
    
    // 处理查询
    void query(ll l, ll r, ll x) {
        // 找到第一个 ≥ l 的节点
        auto it = s.lower_bound(Node(l, 0));
        vector<set<Node>::iterator> to_remove;
        ll cnt_total = 0;
        ll sum_remove = 0;
        
        // 收集要删除的节点（迭代器）
        while (it != s.end() && it->v <= r) {
            cnt_total += it->cnt;
            sum_remove += it->v * it->cnt;
            to_remove.push_back(it);
            it++;
        }
        
        // 删除节点
        for (auto iter : to_remove) {
            s.erase(iter);
        }
        
        // 更新总和
        total_sum = total_sum - sum_remove + x * cnt_total;
        
        // 插入新值
        if (cnt_total > 0) {
            auto it_x = s.find(Node(x, 0));
            if (it_x != s.end()) {
                it_x->cnt += cnt_total;
            } else {
                s.insert(Node(x, cnt_total));
            }
        }
    }
    
    // 获取当前总和
    ll get_sum() const {
        return total_sum;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n, q;
    cin >> n >> q;
    ChthollyTree ct;
    
    // 读入初始数组
    for (int i = 0; i < n; i++) {
        ll a_val;
        cin >> a_val;
        ct.add_element(a_val);
    }
    
    // 输出初始总和
    cout << ct.get_sum() << '\n';
    
    // 处理查询
    for (int i = 0; i < q; i++) {
        ll l, r, x;
        cin >> l >> r >> x;
        ct.query(l, r, x);
        cout << ct.get_sum() << '\n';
    }
    
    return 0;
}
```

# 后记

1. ~~其实我都只在维护桶。~~

2. 笑点解析：实际消耗时间 STL < 珂朵莉树 < FHQ-Treap <= 动态开点权值线段树。

---

## 作者：粥2414 (赞：1)

# 题目描述
维护一个序列，支持查询序列和，查询值域在 $[l,r]$ 的数的数量并替换为数 $x$。
# 思路
这题一眼看是平衡树模板题，题解区还有其他巨佬用权值线段树写的，按理应该评蓝，不知道为啥评黄。

我选择了较为好写的 FHQ-treap，它是一种基于随机化和分裂合并的平衡树，感兴趣的读者可以自行上网查询资料学习。

由于需要同时加入很多个数，所以平衡树的一个节点需要存储多个元素而非一个元素。

平衡树中维护子树元素个数，子树美味值和即可。

查询时输出根节点存储的美味值即可。

清除时同时返回清除元素个数，方便加入。

加入时如果存在值与加入值相同的节点，则无需新建节点，直接更新其元素数即可。否则需要新建节点。
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define ll long long
#define ld long double
#define dd double
//char buf[1<<23],*p1=buf,*p2=buf;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<23,stdin),p1==p2)?EOF:*p1++)
inline ll read() {
	ll x = 0, f = 1;
	char ch;
	while (((ch = getchar()) < 48 || ch > 57)&&ch!=EOF)if (ch == '-')f = -1;
	while (ch >= 48 && ch <= 57)x = x * 10 + ch - 48, ch = getchar();
	return x * f;
}
char __sta[1009], __len;
inline void write(ll x,ll bo) {
	if (x < 0)putchar('-'), x = -x;
	do __sta[++__len] = x % 10 + 48, x /= 10;
	while (x);
	while (__len)putchar(__sta[__len--]);
	if(bo==3)return;
	putchar(bo ? '\n' : ' ');
}
const ll N=2000009;
ll n,q;
struct FHQ{
	ll v,sum;
	ll cnt;
	ll ccnt;
	ll p;
	ll ls,rs;
}tr[N];
ll tcnt;
ll root;
inline void pu(ll id){
	tr[id].sum=tr[tr[id].ls].sum+tr[tr[id].rs].sum+tr[id].cnt*tr[id].v;
	tr[id].ccnt=tr[tr[id].ls].ccnt+tr[tr[id].rs].ccnt+tr[id].cnt;
}
inline ll new_node(ll v,ll cnt){
	tr[++tcnt].p=rand();
	tr[tcnt].v=v;
	tr[tcnt].sum=cnt*v;
	tr[tcnt].cnt=tr[tcnt].ccnt=cnt;
	tr[tcnt].p=rand();
	tr[tcnt].ls=tr[tcnt].rs=0;
	return tcnt;
}
void fen(ll id,ll v,ll &l,ll &r){
	if(!id){
		l=r=0;
		return;
	}
	if(tr[id].v<v){
		l=id;
		fen(tr[id].rs,v,tr[id].rs,r);
	}else{
		r=id;
		fen(tr[id].ls,v,l,tr[id].ls);
	}
	pu(id);
}
ll he(ll u,ll v){
	if(!u||!v)return u+v;
	if(tr[u].p<tr[v].p){
		tr[u].rs=he(tr[u].rs,v);
		pu(u);
		return u;
	}else{
		tr[v].ls=he(u,tr[v].ls);
		pu(v);
		return v;
	}
}
ll clear(ll l,ll r){
	ll u,m,v;
	fen(root,l,u,v);
	fen(v,r+1,m,v);
	root=he(u,v);
	return tr[m].ccnt;
}
void add(ll cnt,ll x){
	ll u,v,m;
	fen(root,x,u,v);
	fen(v,x+1,m,v);
	if(tr[m].cnt!=0)tr[m].cnt+=cnt,tr[m].sum=tr[m].cnt*tr[m].v,tr[m].ccnt+=cnt;
	else m=new_node(x,cnt);
	root=he(he(u,m),v);
}
int main(){
	n=read(),q=read();
	for(int i=1;i<=n;i++){
		add(1,read());
	}
	write(tr[root].sum,1);
	for(int i=1;i<=q;i++){
		ll l=read(),r=read(),x=read();
		add(clear(l,r),x);
		write(tr[root].sum,1);
//		for(int i=1;i<=tcnt;i++){
//			cout<<i<<' '<<tr[i].v<<' '<<tr[i].cnt<<' '<<tr[i].sum<<' '<<tr[i].ls<<' '<<tr[i].rs<<endl;
//		}
//		cout<<endl;
	}
	return 0;
}
```

---

## 作者：粥2414 (赞：1)

UPD：更正代码错误，增加了对算法的说明。
# 题目描述
维护一个序列，支持查询序列和，查询值域在 $[l,r]$ 的数的数量并替换为数 $x$。
# 思路
这题一眼看是权值线段树模板题，题解区还有其他巨佬用平衡树写的，按理应该评蓝，不知道为啥评黄。

~~如果你不会权值线段树，那么你可以去学。（废话）~~

所谓权值线段树，其实就是线段树维护桶。如果会线段树，那么权值线段树也不难。不会的读者可以 自行上网查询资料学习。

具体就是离散化加上权值线段树的板子。权值线段树维护区间和以及区间元素个数。清除操作利用懒标记实现，替换操作可以在清除的同时查询被删除的数的个数，然后一起加入即可。

查询序列和直接输出根节点存储的区间和即可。
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define ll long long
#define ld long double
inline ll read() {
	int x = 0, f = 1;
	char ch;
	while (((ch = getchar()) < 48 || ch > 57)&&ch!=EOF)if (ch == '-')f = -1;
	while (ch >= 48 && ch <= 57)x = x * 10 + ch - 48, ch = getchar();
	return x * f;
}
char __sta[1009], __len;
inline void write(ll x, bool bo) {
	if (x < 0)putchar('-'), x = -x;
	do __sta[++__len] = x % 10 + 48, x /= 10;
	while (x);
	while (__len)putchar(__sta[__len--]);
	putchar(bo ? '\n' : ' ');
}
const ll N=2000009;
ll n,q;
ll a[N],x[N],l[N],r[N];
ll li[N*4],licnt;
struct TREE{
	ll cnt,sum;
	bool clear;
}tr[N*10];
inline void pu(ll id){
	tr[id].sum=tr[id*2].sum+tr[id*2+1].sum;
	tr[id].cnt=tr[id*2].cnt+tr[id*2+1].cnt;
}
inline void pd(ll id){
	if(tr[id].clear){
		tr[id].clear=0;
		tr[id*2].clear=tr[id*2+1].clear=1;
		tr[id*2].sum=tr[id*2+1].sum=tr[id*2].cnt=tr[id*2+1].cnt=0;
	}
}
void add(ll id,ll l,ll r,ll v,ll cnt){
	if(v<l||v>r)return;
	if(l==r){
		tr[id].cnt+=cnt;
		tr[id].sum+=li[l]*cnt;
		return;
	}
	pd(id);
	ll mid=(l+r)/2;
	add(id*2,l,mid,v,cnt),add(id*2+1,mid+1,r,v,cnt);
	pu(id);
}
ll clear(ll id,ll l,ll r,ll ql,ll qr){
	if(ql>r||l>qr)return 0;
	if(ql<=l&&r<=qr){
		ll ans=tr[id].cnt;
		tr[id].sum=tr[id].cnt=0;
		tr[id].clear=1;
		return ans;
	}
	pd(id);
	ll mid=(l+r)/2;
	ll ans=clear(id*2,l,mid,ql,qr)+clear(id*2+1,mid+1,r,ql,qr);
	pu(id);
	return ans;
}
int main(){
	n=read(),q=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		li[++licnt]=a[i];
	}
	for(int i=1;i<=q;i++){
		l[i]=read(),r[i]=read(),x[i]=read();
		li[++licnt]=l[i],li[++licnt]=r[i],li[++licnt]=x[i];
	}
	sort(li+1,li+licnt+1);
	licnt=unique(li+1,li+licnt+1)-li-1;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(li+1,li+licnt+1,a[i])-li;
		add(1,1,licnt,a[i],1);
	}
	write(tr[1].sum,1);
	for(int i=1;i<=q;i++){
		l[i]=lower_bound(li+1,li+licnt+1,l[i])-li;
		r[i]=lower_bound(li+1,li+licnt+1,r[i])-li;
		x[i]=lower_bound(li+1,li+licnt+1,x[i])-li;
		ll cnt=clear(1,1,licnt,l[i],r[i]);
		add(1,1,licnt,x[i],cnt);
		write(tr[1].sum,1);
	}
	return 0;
}
```

---

## 作者：ZSB00000 (赞：0)

## 珂朵莉树解法

### 算法简介
珂朵莉树（Chtholly Tree）是一种基于 `std::set` 维护值相同区间的数据结构，适用于区间推平操作。在本题中，我们使用**权值珂朵莉树**（本质是桶的扩展）实现高效操作。

[详细算法介绍参考 OI Wiki](https://oi-wiki.org/misc/odt/)

### 解法分析
#### 如何设计
每个节点包含三个参数 $(l, r, val)$，表示值域 $[l, r]$ 内的元素共有 $val$ 个。维护以下核心组件：
1. `set<tree>` 存储区间节点。
2. `total` 记录当前所有元素和。
3. 值域范围 $[0, 10^9 + 1]$。

#### 操作实现
1. **推平操作 `assign(l, r, 0)`**：
   - 删除 $[l, r]$ 区间内所有节点。
   - 计算被删除元素数 $w = \sum (r_i - l_i + 1) \times val_i$。
   - 更新总和：$total \gets total - \sum \left( \frac{(l_i + r_i) \times (r_i - l_i + 1)}{2} \times val_i \right)$。
   - 在 $x$ 处添加 $w$ 个元素（通过 `add(x, w)`）。

2. **单点加操作 `add(x, w)`**：
   - 定位值 $x$ 所在区间。
   - 更新节点值 $val \gets val + w$。
   - 更新总和：$total \gets total + w \times x$。

#### 复杂度证明
- `split` 操作均摊 $O(\log n)$。
- `assign` 操作均摊 $O(\log n)$。
- 总时间复杂度 $O(n \log n)$。

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, q;
long long a[(int)3e5 + 5];
constexpr int maxx = 1e9 + 1;
class _ctholly
{
	private:
		int n;
		long long total;
		struct tree
		{
			int l, r;
			mutable long long x;
			tree(int ll, int rr, long long xx): l(ll), r(rr), x(xx) {}
			bool operator<(const tree &a)const
			{
				return l < a.l;
			}
		};
		set<tree>ctholly;
		auto split(int x)
		{
			auto it = ctholly.lower_bound(tree(x, 0, 0));
			if (it != ctholly.end() && it->l == x)return it;
			--it;
			int l = it->l, r = it->r, w = it->x;
			ctholly.erase(it);
			ctholly.insert(tree(l, x - 1, w));
			return ctholly.insert(tree(x, r, w)).first;
		}
	public:
		_ctholly(int nn): n(nn)
		{
			total=0;
			ctholly.insert(tree(0, maxx, 0));
		}
		long long assign(int l, int r, long long x)
		{
			long long ans = 0;
			auto rr = split(r + 1), ll = split(l);
			for (auto i = ll; i != rr; i++)
			{
				total-=(1ll * (i->r + i->l) * (i->r - i->l + 1) >> 1) * 1ll * i->x;
				ans += i->x;
				/*
				这里的ans计算的是有多少个糕点被吃掉了。
				total可以这样计算，是因为每个区间内都是一个等差数列，其首项是l,末项是r，项数就是r-l+1，又因为每个糕点都有x个，所以再乘上x即可。
				*/
			}
			ctholly.erase(ll, rr);
			ctholly.insert(tree(l, r, x));
			return ans;
		}
		void add(int pos, long long x)
		{
			auto rr = split(pos + 1), ll = split(pos);
			for (auto i = ll; i != rr; i++)
			{
				i->x += x;
			}
			total+=x*pos;
			//实现total的单点修改
		}
		long long get_sum()const
		{
			return total;
		}
};
class IO//快读快写
{
	private:
		static constexpr int buf_size = 1 << 20;
		char *p1_in, *p2_in;
		char in_buf[buf_size], out_buf[buf_size];
		char *p_out;
		FILE *out, *in;
	public:
		IO(FILE *IN = stdin, FILE *Out = stdout) :
			p1_in(in_buf), p2_in(in_buf), p_out(out_buf), out(Out), in(IN) {}
		~IO()
		{
			flush();
		}
		char gc()
		{
			if (p1_in == p2_in)
			{
				p2_in = (p1_in = in_buf) + fread(in_buf, 1, buf_size, in);
				if (p1_in == p2_in)return EOF;
			}
			return *p1_in++;
		}
		template<typename T>
		void read(T &x)
		{
			x = 0;
			char c = gc();
			int f = 1;
			while (!isdigit(c))
			{
				f = (c == '-' ? -1 : 1), c = gc();
			}
			while (isdigit(c))
			{
				x = x * 10 + (c - '0'), c = gc();
			}
			x = x * f;
		}
		void flush()
		{
			fwrite(out_buf, 1, p_out - out_buf, out);
			p_out = out_buf;
		}
		void pc(char c)
		{
			if (p_out - out_buf == buf_size)flush();
			*p_out++ = c;
		}
		template<typename T>
		void write(T x)
		{
			if (x < 0)pc('-'), x = -x;
			char stack[100];
			int top = 0;
			do stack[top++] = x % 10;
			while (x /= 10);
			while (top--)pc(stack[top] + '0');
		}
};
IO _read;
signed main()
{
	_read.read(n), _read.read(q);
	_ctholly ctholly(n);
	for (int i = 1; i <= n; i++)
	{
		_read.read(a[i]);
	}
	for (int i = 1; i <= n; i++)
	{
		ctholly.add(a[i], 1);
	}
	_read.write(ctholly.get_sum()), _read.pc('\n');
	for (int i = 1; i <= q; i++)
	{
		int l, r, x;
		_read.read(l), _read.read(r), _read.read(x);
		ctholly.add(x, ctholly.assign(l, r, 0));
		_read.write(ctholly.get_sum()), _read.pc('\n');
	}
	return 0;
}

---

## 作者：yanxu_cn (赞：0)

本题是 STL 好练习题，标签诚不欺人。

提供一个非常简单的 `map` 做法。

这题甚至不需要珂朵莉树（因为这题只关心值的大小而并不关心顺序），所以直接用 `map` 统计数目即可。容易注意到复杂度是 $O(q\log n)$ 并且跑不满的。

然后开好 `long long` 即可，注意中间会有计算过程也会爆 `int`，爆有符号整数在谷上是不会 RE 的，只会 WA，望周知。

贴代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(0),cin.tie(0);
    int n,q;
    cin>>n>>q;
    map<int,int>mp;
    long long ans=0;
    for(int i=1;i<=n;i++)
    {
        int t;
        cin>>t;
        mp[t]++;
        ans+=t;
    }
    cout<<ans<<'\n';
    q++;
    while(--q)
    {
        int l,r,x;
        cin>>l>>r>>x;
        int cnt=0;
        auto lp=mp.lower_bound(l),rp=mp.upper_bound(r);
        for(auto tp=lp;rp!=tp;tp++)
        cnt+=tp->second,ans-=static_cast<long long>(tp->first)*tp->second;
        mp.erase(move(lp),move(rp));
        mp[x]+=cnt;
        ans+=(long long)cnt*x;
        cout<<ans<<'\n';
    }
    return 0;
}
```

---

## 作者：lzt415 (赞：0)

## 笔因
居然调这么一个水绿调了这么久，记录一下这个齿孺。
## 前言
其实这题挺无脑的，一看就是权值线段树，看完题面我都没想到其他东西能做，可能是我太菜了。
## 思路
我们发现这道题只有两个操作，即把值在 $l$ 和 $r$ 间的数全部删掉，然后将值为 $x$ 的数的个数增加等量的数量。这其实挺明显用权值线段树维护的，而且要离散化。~~但是细节有点恶心心~~。

如下：（只是指我犯的，不代表大家，勿喷）

1. 输出所有元素的总和，但我二话没说写了个元素个数之和。这个应该都没错，只能说我太蒟了。
2. 这个我觉得可能有一点易错，就是这个 $x_j$ 也要放进离散化数组里，因为这个数可能是原来没有的，所以要先全部把数据读入在统一处理做题。
3. 注意有时候行与行的位置不能放反，有时候有后效性，改变了原先的值，比如计算满足条件的 $a_i$ 的个数时。
## code
其实本人的马蜂挺好的，只不过这次的码不小心写的有点随性。

凑合地看吧。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e6+10;
int a[N],t[N],tag[N],n,q,b[N],cnt,tot,l[N],r[N],x[N],sum[N];
void change(int k,int l,int r,int p,int val,int w)
{
	if(l==r) {t[k]+=val;sum[k]+=w;return;}
	if(tag[k]) 
	{
		t[k*2]=sum[k*2]=t[k*2+1]=sum[k*2+1]=0;
		tag[k*2]=tag[k*2+1]=1;
		tag[k]=0;
	}	
	int mid=(l+r)/2;
	if(p<=mid) change(k*2,l,mid,p,val,w);
	else change(k*2+1,mid+1,r,p,val,w);
	t[k]=t[k*2]+t[k*2+1];
	sum[k]=sum[k*2]+sum[k*2+1];
}
void update(int k,int l,int r,int x,int y)
{
	if(x<=l&&r<=y) {t[k]=sum[k]=0,tag[k]=1;return;}
	if(tag[k]) 
	{
		t[k*2]=sum[k*2]=t[k*2+1]=sum[k*2+1]=0;
		tag[k*2]=tag[k*2+1]=1;
		tag[k]=0;
	}	
	int mid=(l+r)/2;
	if(x<=mid) update(k*2,l,mid,x,y);
	if(y>=mid+1) update(k*2+1,mid+1,r,x,y);	
	t[k]=t[k*2]+t[k*2+1];
	sum[k]=sum[k*2]+sum[k*2+1];
}
int query(int k,int l,int r,int x,int y)
{
	if(x<=l&&r<=y) return t[k];
	if(tag[k]) 
	{
		t[k*2]=sum[k*2]=t[k*2+1]=sum[k*2+1]=0;
		tag[k*2]=tag[k*2+1]=1;
		tag[k]=0;
	}
	int mid=(l+r)/2,res=0;
	if(x<=mid) res+=query(k*2,l,mid,x,y);
	if(y>=mid+1) res+=query(k*2+1,mid+1,r,x,y);
	t[k]=t[k*2]+t[k*2+1];
	sum[k]=sum[k*2]+sum[k*2+1];
	return res;
}
int _(int k,int l,int r,int x,int y)
{
	if(x<=l&&r<=y) return sum[k];
	if(tag[k]) 
	{
		t[k*2]=sum[k*2]=t[k*2+1]=sum[k*2+1]=0;
		tag[k*2]=tag[k*2+1]=1;
		tag[k]=0;
	}
	int mid=(l+r)/2,res=0;
	if(x<=mid) res+=_(k*2,l,mid,x,y);
	if(y>=mid+1) res+=_(k*2+1,mid+1,r,x,y);
	t[k]=t[k*2]+t[k*2+1];
	sum[k]=sum[k*2]+sum[k*2+1];
	return res;	
}
signed main()
{
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i],b[++tot]=a[i];
	for(int i=1;i<=q;i++)
	{
		cin>>l[i]>>r[i]>>x[i];
		b[++tot]=l[i],b[++tot]=r[i],b[++tot]=x[i];
	}
	sort(b+1,b+tot+1);
	int m=unique(b+1,b+tot+1)-b-1;
	for(int i=1;i<=n;i++)
	{
		int t=lower_bound(b+1,b+m+1,a[i])-b;
		change(1,1,m,t,1*a[i],1);
	}
	cout<<t[1]<<endl;
	for(int i=1;i<=q;i++)
	{
		int L=lower_bound(b+1,b+m+1,l[i])-b;
		int R=lower_bound(b+1,b+m+1,r[i])-b;
		int cnt=_(1,1,m,L,R);
		update(1,1,m,L,R);
		int X=lower_bound(b+1,b+m+1,x[i])-b;
		change(1,1,m,X,cnt*x[i],cnt);
		cout<<query(1,1,m,1,m)<<endl;
	}
	
	return 0;
}
```
额，$long$ $long$ 是个好氡锡。

---

## 作者：txy120607 (赞：0)

题解
# 引言
正在刷水题的我，点进这道黄题，看了眼题解。笑死根本没听过大佬的 FHQ-treap。但碰巧刚学了离散化，可以考虑用 map 做出该题。
# 前置知识
本部分为 map 的介绍，掌握 map 的可以跳过。

map 是 STL 容器的一种，使用时需要包含`<map>`头文件。
map 使用红黑树——一种自平衡的二叉搜索树实现，这使得它拥有插入、搜索、删除均 $O(\log n)$ 的较高性能，但因此也有不低的内存占用。
map 的功能包括但不限于：有序键值存储、**区间键范围操作**、**词频统计**和离散化。本题解使用了 map 的词频统计功能和区间键范围操作功能。
map 的基本操作：
1. 创建：类似 vector，但是尖括号内需要两个类型，分别是键类型与值类型。
```cpp
map<string, string> NewMap;
```

2. 键值存储与修改：直接使用 `[]`，与数组类似。
```cpp
NewMap["name"] = "Txy120607";
NewMap["password"] = "********";
cout << "User : " << NewMap["name"] << \
" password : " << NewMap["password"] << endl;
```

3. 删除键：与 vector 类似，使用 erase，会返回擦除后有效的同位迭代器。由于 erase 需要传入迭代器，所以通常使用 Erase-Remove 惯用法擦除一个键值，即先用 find 找出迭代器，再擦除键值。
```cpp
map<string, string>::iterator it = \
NewMap.erase(NewMap.find("User"));
 //it仅展示返回值为迭代器，没有额外影响
NewMap.erase(NewMap.find("password"));
```
4. 词频统计：以词为键，再次遇到时对应的键加一。
```cpp
map<string, int> cipin;
int n;
cin >> n;
while (n--) {
    string g;
    cin >> g;
    cipin[g]++;
}
for (auto t : cipin) {
    cout << t.first << " " << t.second << endl;
}

//输入8
//1 2 3 4 3 2 1 0
//输出0 1
//1 2
//2 2
//3 2
//4 1
//由此也可以证明map是有序存储

```
5. 区间键操作：来到核心部分，区间操作通常使用 erase 返回的迭代器实现，通过 while 循环配合 erase 处理所有符合要求的键值。能实现得益于 map 是有序存储。重点注意迭代器是指针，需要解引用。还需要判断是否已经到达末尾。
```cpp
//删除所有键在5 至 20间的键值对
map<int, int> NewMap;
NewMap[3] = 4;
NewMap[4] = 5;
NewMap[5] = 12345;
NewMap[7] = 1234567;
NewMap[21] = 22;
auto it = NewMap.find(5);
while ((*it).first <= 20 && it != NewMap.end()) {
    it = NewMap.erase(it);
}
cout << NewMap.size();
//输出3
```
附注：区间键操作通常配合词频统计，实现区间修改的功能。
# 正文
使用 map 的词频统计功能，配合区间键操作，就可以实现题目要求。  
同时通过添加一个 sum 来记录当前美味值之和，可以避免 $$O(n)$$ 时间复杂度的统计操作，仅需更改时顺便修改。

# Code：

```cpp
#include <iostream>
#include <map>

#define Code using
#define by namespace
#define Txy120607 std;

Code by Txy120607
#define int long long //十年OI一场空，不开long long见祖宗！

map<int, int> snake; //好像不太对，但能用就行
int n, q, sum;
signed main() {
    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        //处理初始数据
        int s;
        cin >> s;
        snake[s]++;
        sum += s;
    }

    cout << sum << "\n"; // 输出初始总和

    while (q--) {
        int l, r, x;
        cin >> l >> r >> x;
        map<int, int>::iterator it = snake.lower_bound(l); //二分查找第一个最低美味值snake, map<int, int>::iterator是一个pair类型指针，毕竟Map用pair存储键
        int cnt = 0; //统计被替换的数量

        // 处理所有在 [l, r] 范围内的元素
        while (it != snake.end() && it->first <= r) {
            //去除旧元素
            cnt += it->second;
            sum -= it->first * it->second;
            it = snake.erase(it);
        }

        // 添加新元素并更新总和
        snake[x] += cnt;
        sum += cnt * x;
        cout << sum << "\n";
    }

	return 0;
}
```
**注意是 `lower_bound` 不是 `find`，`find` 只是查找符合要求的键，若不存在就会返回指向末尾的指针！！！**  
~~轻松~~并非轻松 AC。

# 总结
map 是一个高效的有序键值存储工具，掌握并善用 map 这类的 STL 工具可以有奇效，就像我在 CSP-J 组中用数学方法做 DP 题一样，编程是很灵活的。

---

## 作者：jackzhangcn2013 (赞：0)

# 题目大意

有一个长度为 $n$ 的序列。
有 $q$ 次查询，每次查询将输入 $l,r,x$，你需要将值在 $\left[l,r\right]$ 内的所有数字都变为 $x$。

# 解法

我们可以使用 STL。

在这里，我们采用 `map` 来记录每个值有多少数。

于是，对于每次查询，我们将范围内的元素删除，再将 $x$ 和对应的数量加入 `map`。

# 时间复杂度

很明显，每次修改不会增加数的总数，所以 `map` 最多只会修改 $q+n$ 次，时间复杂度为 $O((q+n)\log{n})$，可以通过本题

# 代码

```cpp
#include <bits/stdc++.h>
#define int long long
const int N = 1e5 + 5;
const int Mod = 1e9 + 7;
using namespace std;
int n, q;
map<int, int> mp;
signed main()
{
    int sum = 0;
    cin >> n >> q;
    while (n--)
    {
        int x;
        cin >> x;
        mp[x]++;
        sum += x;
    }
    cout << sum << endl;
    while (q--)
    {
        int l, r, x;
        cin >> l >> r >> x;
        auto it = mp.lower_bound(l);
        int cnt = 0;
        while (it != mp.end() && it->first <= r)
        {
            cnt += it->second;
            sum += (x - it->first) * it->second;
            it = mp.erase(it);
        }
        mp[x] += cnt;
        cout << sum << endl;
    }
    return 0;
}
```

---

## 作者：Tairitempest (赞：0)

## [NOISG 2025 Prelim] Snacks

如果我们不会观察性质：

考虑到这个东西可以用离散化搭配权值线段树，只要存储所有数列中原有的值和后面会加进来的值，然后建树，存储数字数量和数字总和。我们接下来要做的就是区间推平，单点修改，查询全局三个事情。

只需要一开始单点修改所有的值，每次操作执行一次区间推平和单点修改，再去查询全局就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MAXN 200010
ll n,q,a[MAXN],x[MAXN<<1];
ll L[MAXN],R[MAXN],X[MAXN];

struct T{
    ll l,r,sum,cnt,tag;
} t[MAXN<<4];

void build(ll l,ll r,ll id){
    t[id].l=l;t[id].r=r;
    t[id].tag=1;
    if(l==r) return;
    ll mid=(l+r)/2;
    build(l,mid,id*2);
    build(mid+1,r,id*2+1);
}

void push(ll id){
	if(t[id].tag==0&&t[id].l!=t[id].r){
		t[id*2].sum=t[id*2+1].sum=0;
		t[id*2].cnt=t[id*2+1].cnt=0;
		t[id*2].tag=t[id*2+1].tag=0;
	}
	t[id].tag=1;
}

ll del(ll l,ll r,ll id){
	if(r<x[t[id].l]||x[t[id].r]<l) return 0;
	else if(l<=x[t[id].l]&&x[t[id].r]<=r){
		ll cnt=t[id].cnt;
		t[id].sum=t[id].cnt=t[id].tag=0;
		return cnt;
	}else{
		push(id);
    	ll mid=(t[id].l+t[id].r)/2;
		ll cnt=0;
		if(l<=x[mid]) cnt+=del(l,r,id*2);
		if(r>x[mid]) cnt+=del(l,r,id*2+1);
		t[id].sum=t[id*2].sum+t[id*2+1].sum;
		t[id].cnt=t[id*2].cnt+t[id*2+1].cnt;
		return cnt;
	}
}

void insert(ll id,ll p,ll k){
	if(t[id].l==t[id].r){
		t[id].cnt+=k;
		t[id].sum+=p*k;
	}else{
		push(id);
    	ll mid=(t[id].l+t[id].r)/2;
		if(p<=x[mid]) insert(id*2,p,k);
		else insert(id*2+1,p,k);
		t[id].sum=t[id*2].sum+t[id*2+1].sum;
		t[id].cnt=t[id*2].cnt+t[id*2+1].cnt;
	}
}

int main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        x[i]=a[i];
    }
    for(int i=1;i<=q;i++){
    	cin>>L[i]>>R[i]>>X[i];
    	x[i+n]=X[i];
	}
	sort(x+1,x+n+q+1);
    ll len=unique(x+1,x+n+q+1)-x-1;
	build(1,len,1);
	for(int i=1;i<=n;i++)
		insert(1,a[i],1);
	cout<<t[1].sum<<endl;
	for(int i=1;i<=q;i++){
		insert(1,X[i],del(L[i],R[i],1));
		cout<<t[1].sum<<endl;
	}
	return 0;
}
```

---

## 作者：I_LOVE_FG (赞：0)

## solution

诶这题怎么是黄？果然我只会数据结构。赛时写了个线段树。那就展示一下这个丑陋的做法吧。

看完题一眼权值线段树。所谓权值线段树并没有这么高级，其实就是把线段树当桶用，然后可以查询区间 $[l,r]$ 里面总共有几个数。

于是想到维护一棵有区间值的和以及区间内数的总数，支持区间赋 $0$，单点修改的权值线段树就好了。对于操作 $1$ 直接调用区间赋 $0$ 操作，对于操作 $2$ 直接单点修改即可。

注意区间赋 $0$ 时应该记录下被覆盖掉的数有多少个，以得到在单点修改的时候应加的权值（实际上就是记录吃掉的小吃的个数）。

数据范围有点大那就离散化一下。离散化之后要记录离散化后的数对应的原数是多少，否则线段树内记录的区间和都是乘了离散化后的权值，而这样是不对的。

然后赛时 #112 出锅了导致直接卡了 30min。

## code

```cpp
#include<bits/stdc++.h>

#define int long long

namespace IO {
	inline int read() {
		int ret = 0, f = 1;char ch = getchar();
		while (ch < '0' || ch > '9') {
			if (ch == '-') f = -f;
			ch = getchar();
		} 
		while (ch >= '0' && ch <= '9') {
			ret = (ret << 1) + (ret << 3) + (ch ^ 48);
			ch = getchar();
		}
		return ret * f;
	}
	void write(int x) {
		if (x < 0) putchar('-'), x = -x;
		if (x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}

using namespace IO;
using namespace std;
typedef long long ll;

const int maxn = 5e5 + 5;

int a[maxn << 2], sum[maxn * 4], L[maxn * 4], R[maxn * 4], lazy[maxn * 4], num[maxn << 2];
int n, m;

int X[maxn << 2], Y[maxn << 2], Val[maxn << 2], u[maxn << 2], tot, t[maxn << 2], b[maxn << 2];

int len(int x) {
	return R[x] - L[x] + 1;
}

void pushup(int x) {
	sum[x] = sum[x << 1] + sum[x << 1 | 1];
	num[x] = num[x << 1] + num[x << 1 | 1];
}

void pushdown(int x) {
	if (lazy[x]) {
		lazy[x << 1] = lazy[x << 1 | 1] = 1;
		sum[x << 1] = sum[x << 1 | 1] = 0;
		num[x << 1] = num[x << 1 | 1] = 0;
		lazy[x] = 0;
	}
}

void build(int l, int r, int x) {
	L[x] = l, R[x] = r;
	if (l == r) {
		sum[x] = b[l] * t[l];
		num[x] = t[l];
//		cout << l << ' ' << sum[x] << ' ' << num[x] << '\n';
		return;
	}
	int mid = l + ((r - l) >> 1);
	build(l, mid, x << 1);
	build(mid + 1, r, x << 1 | 1);
	pushup(x);
}

void update(int pos, int d, int x) {
	if (L[x] == R[x] && R[x] == pos) {
		sum[x] += b[pos] * d;num[x] += d;
		return;
	}
	pushdown(x);
	int mid = L[x] + ((R[x] - L[x]) >> 1);
	if (pos <= mid) update(pos, d, x << 1);
	else update(pos, d, x << 1 | 1);
	pushup(x);
}

int update_ze(int l, int r, int x) {
	int ans = 0;
	if (L[x] >= l && R[x] <= r) {
		lazy[x] = 1;ans = num[x];
//		cout << ans << "nailong\n";
		sum[x] = 0;num[x] = 0;
		return ans;
	}
	pushdown(x);
	int mid = L[x] + R[x] >> 1;
	if (l <= mid) ans += update_ze(l, r, x << 1);
	if (r > mid) ans += update_ze(l, r, x << 1 | 1);
	pushup(x); 
	return ans;
}

signed main() {
	n = read(), m = read();
	for (int i = 1;i <= n;i++) a[i] = read(), u[++tot] = a[i];
	
	for (int i = 1;i <= m;i++) X[i] = read(), Y[i] = read(), Val[i] = read(), u[++tot] = X[i], u[++tot] = Y[i], u[++tot] = Val[i];
	
	sort(u + 1, u + 1 + tot);
	tot = unique(u + 1, u + 1 + tot) - u - 1;
	
	int mi;
	for (int i = 1;i <= n;i++) {
		mi = a[i];
		a[i] = lower_bound(u + 1, u + tot + 1, a[i]) - u;b[a[i]] = mi;
		t[a[i]]++;
	}
	for (int i = 1;i <= m;i++) {
		mi = X[i];
		X[i] = lower_bound(u + 1, u + tot + 1, X[i]) - u;b[X[i]] = mi;mi = Y[i];
		Y[i] = lower_bound(u + 1, u + tot + 1, Y[i]) - u;b[Y[i]] = mi;mi = Val[i];
		Val[i] = lower_bound(u + 1, u + tot + 1, Val[i]) - u;b[Val[i]] = mi;
	}
	
//	for (int i = 1;i <= n;i++) cout << a[i] << ' ';
//	putchar(10);
//	for (int i = 1;i <= m;i++) cout << X[i] << ' ' << Y[i] << ' ' << Val[i] << '\n';
//	
//	for (int i = 1;i <= n;i++) cout << b[a[i]] << ' ';
//	putchar(10);
//	for (int i = 1;i <= m;i++) cout << b[X[i]] << ' ' << b[Y[i]] << ' ' << b[Val[i]] << '\n'; 
	
	build(1, tot, 1);
	write(sum[1]), putchar(10);
	
	for (int i = 1;i <= m;i++) {
		int x = X[i], y = Y[i], k = Val[i], Num = update_ze(x, y, 1);//cout << Num << "nailong\n";
		update(k, Num, 1);
		write(sum[1]), putchar(10);
	}
	return 0;
} 
```

---

