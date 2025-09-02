# [ABC292Ex] Rating Estimator

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc292/tasks/abc292_h

あなたは $ N $ 個のコンテストに参加します。コンテストが開催される順にコンテスト $ 1 $, コンテスト $ 2 $, $ \dots $ コンテスト $ N $ と呼びます。  
 各コンテストに参加すると、コンテストごとに **パフォーマンス** という値が与えられます。コンテスト $ i $ で与えられるパフォーマンスを $ P_i $ とします。  
 また、あなたは **レーティング** という値を持っています。レーティングはコンテストでのパフォーマンスによって変化する値です。コンテストに参加する前のレーティングの値は $ 0 $ で、コンテスト $ n $ に出た後のレーティングの値は $ \frac{1}{n}\ \left(\sum_{i=1}^n\ P_i\ \right) $ に変化します。   
 ただし、あなたのレーティングが一度 $ B $ **以上** になると、それ以降はコンテストに参加してもレーティングは変動しなくなります。

あなたはコンテストに出る前に、それぞれのコンテストで得られるパフォーマンスを予測することにしました。はじめ、コンテスト $ i $ のパフォーマンスの予測値を $ a_i $ とします。クエリが $ Q $ 個与えられるので入力される順にすべて処理してください。

各クエリでは 2 個の整数 $ c,\ x $ が与えられます。あなたは、まずコンテスト $ c $ のパフォーマンスの予測値を $ x $ に変更します。(この変更は永続的です。) そして、あなたが $ N $ 個のコンテスト全てで現在の予測値通りのパフォーマンスを得られた場合の、全てのコンテストに参加した後のレーティングの値を答えてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 5\ \times\ 10^5 $
- $ 1\ \leq\ B\ \leq\ 10^9 $
- $ 1\ \leq\ Q\ \leq\ 10^5 $
- $ 0\ \leq\ a_i\ \leq\ 10^9 $
- $ 1\ \leq\ c\ \leq\ N $
- $ 0\ \leq\ x\ \leq\ 10^9 $
- 入力される値はすべて整数
 
### Sample Explanation 1

はじめ、$ (a_1,\ a_2,\ a_3,\ a_4,\ a_5)\ =\ (5,\ 1,\ 9,\ 3,\ 8) $ です。 1 番目のクエリによって $ a_4 $ が $ 9 $ に変更されて $ (a_1,\ a_2,\ a_3,\ a_4,\ a_5)\ =\ (5,\ 1,\ 9,\ 9,\ 8) $ となります。 このとき、コンテスト $ i $ でパフォーマンス $ a_i $ を取った場合のあなたのレーティングの推移は次の通りです。 - はじめ、レーティングは $ 0 $ です。 - コンテスト $ 1 $ が終了した時点でレーティングは $ 5\ /\ 1\ =\ 5 $ に変化します。 - コンテスト $ 2 $ が終了した時点でレーティングは $ (5\ +\ 1)\ /\ 2\ =\ 3 $ に変化します。 - コンテスト $ 3 $ が終了した時点でレーティングは $ (5\ +\ 1\ +\ 9)\ /\ 3\ =\ 5 $ に変化します。 - コンテスト $ 4 $ が終了した時点でレーティングは $ (5\ +\ 1\ +\ 9\ +\ 9)\ /\ 4\ =\ 6 $ に変化します。 - 以降、レーティングの値は変化しません。なぜならば、$ 4 $ 番目のコンテストが終了した時点でレーティングが $ B $ 以上の値になっているからです。 よって、全てのコンテストが終了した時点でのレーティングは $ 6 $ なので、1 行目にはこれを出力します。

## 样例 #1

### 输入

```
5 6 7
5 1 9 3 8
4 9
2 10
1 0
3 0
3 30
5 100
1 100```

### 输出

```
6.000000000000000
7.500000000000000
6.333333333333333
5.400000000000000
13.333333333333334
13.333333333333334
100.000000000000000```

# 题解

## 作者：EnofTaiPeople (赞：5)

形式化题意：

给定一个长度为 $n$ 的序列 $a_i$，参数 $B$，询问数 $q$；

每一次询问会对序列单点修改，你需要输出一个实数：
1. 如果不存在某一个前缀平均值不低于 $B$，则输出整体平均值；
2. 否则，输出第一个不低于 $B$ 的前缀平均值。

这道题被旁边的同学 D 爆了，因为难度相对于 Ex 的定位还是太低了。

如果你做不出来那么一定是被侮辱智商了。

- 将所有数减去 $B$，前缀平均值不低于 $B$ 变成前缀和非负，考虑如何维护前缀和；
- 发现只有单点修改，对于前缀和来说，就是进行了一次区间（后缀）加，然后我们需要找到第一次出现的非负数；
- 我们可以用线段树维护区间最大值，然后线段树上二分找到那个前缀。

于是时间复杂度 $O(q\log n)$，空间 $O(n)$：
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ld=long double;
#define ls x<<1
#define rs x<<1|1
using pr=pair<int,int>;
const int N=2e6+6;
int n,B,q,a[N];
ll sum1;
ll tg[N],mn[N],sf[N];
void build(int x,int l,int r){
    if(l==r){mn[x]=sf[l];return;}
    int md=l+r>>1;
    build(ls,l,md),build(rs,md+1,r);
    mn[x]=max(mn[ls],mn[rs]);
}
void ad(int x,ll d){tg[x]+=d,mn[x]+=d;}
void pd(int x){
    if(tg[x])ad(ls,tg[x]),ad(rs,tg[x]),tg[x]=0;
}
void add(int x,int l,int r,int L,int R,ll d){
    if(l>=L&&r<=R){ad(x,d);return;}
    int md=l+r>>1;pd(x);
    if(L<=md)add(ls,l,md,L,R,d);
    if(md<R)add(rs,md+1,r,L,R,d);
    mn[x]=max(mn[ls],mn[rs]);
}
ld ans;
void qry(int x,int l,int r){
    if(l==r){ans=ld(mn[x]+ll(B)*l)/l;return;}
    int md=l+r>>1;pd(x);
    if(mn[ls]>=0)return qry(ls,l,md);
    return qry(rs,md+1,r);
}
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>B>>q;
    int i,j,k,l,r,x,y;
    for(x=1;x<=n;++x)
        cin>>a[x],sum1+=a[x],sf[x]=sf[x-1]+a[x]-B;
    build(1,1,n);
    while(q--){
        cin>>x>>k,sum1+=k-a[x];
        add(1,1,n,x,n,k-a[x]);
        a[x]=k;
        if(mn[1]<0)printf("%.15Lf\n",ld(sum1)/n);
        else{
            qry(1,1,n);
            printf("%.15Lf\n",ans);
        }
    }return 0;
}
```

---

## 作者：_Kenma_ (赞：3)

# AT_abc292_ex 解题报告

## 前言

谨以此题纪念我首次独立想出的 abc ex。

虽然赛时过了一车人。

## 思路分析

带修，找首个关键点，看起来就很像线段树二分。

但是直接做答案没有单调性。

考虑推柿子：

$$\frac{1}{k} \sum_{i=1}^{k} p_i \ge b$$

做一点基本变换：

$$\sum_{i=1}^{k} p_i \ge b \cdot k$$

把 $b$ 移项：

$$\sum_{i=1}^{k} p_i-b \ge 0$$

发现直接维护 $q_i=\sum_{i=1}^{k} p_i-b$ 就行了。

线段树上记录 $q$ 的最大值，线段树二分找到第一个 $\ge 0$ 的位置。

主要注意在 $p$ 数组上的单点赋值，在 $q$ 数组上是区间加。类似地，区间查询变成了单点查。

总体复杂度 $O(n \log n)$。

感觉放 ex 还是偏简单了。

## 代码实现

```cpp

#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,b,x,k,a[500005],c[500005];
int val[1000005],tag[1000005],ls[1000005],rs[1000005],dcnt;
void pushup(int x){
	val[x]=max(val[ls[x]],val[rs[x]]);
}
void pushdown(int x){
	if(!tag[x]) return;
	tag[ls[x]]+=tag[x];
	tag[rs[x]]+=tag[x];
	val[ls[x]]+=tag[x];
	val[rs[x]]+=tag[x];
	tag[x]=0;
}
void build(int l,int r,int &x){
	x=++dcnt;
	if(l==r){
		val[x]=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,ls[x]);
	build(mid+1,r,rs[x]);
	pushup(x);
}
void modify(int l,int r,int ql,int qr,int k,int x){
	if(ql<=l && r<=qr){
		val[x]+=k;
		tag[x]+=k;
		return;
	}
	pushdown(x);
	int mid=(l+r)>>1;
	if(ql<=mid) modify(l,mid,ql,qr,k,ls[x]);
	if(qr>=mid+1) modify(mid+1,r,ql,qr,k,rs[x]);
	pushup(x); 
}
int query(int l,int r,int pos,int x){
	if(l==r) return val[x];
	pushdown(x);
	int mid=(l+r)>>1;
	if(pos<=mid) return query(l,mid,pos,ls[x]);
	else return query(mid+1,r,pos,rs[x]);
}
int find(int l,int r,int x){
	if(l==r) return l;
	pushdown(x);
	int mid=(l+r)>>1;
	if(val[ls[x]]>=0) return find(l,mid,ls[x]);
	else return find(mid+1,r,rs[x]);
}
signed main(){
	cin>>n>>b>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		c[i]=a[i];
		a[i]=a[i]-b;
	} 
	for(int i=1;i<=n;i++){
		a[i]+=a[i-1];
	}
	build(1,n,x);
	for(int i=1;i<=m;i++){
		cin>>x>>k;
		modify(1,n,x,n,k-c[x],1);
		c[x]=k;
		int pos=find(1,n,1);
		printf("%.10Lf\n",(long double)(query(1,n,pos,1))/(long double)(pos)+b);
	}
	return 0;
}

```

## 后记

感觉最近线段树二分的题做的有点少，手生了。

---

## 作者：Mr_Az (赞：2)

## Question 问题 [ABC292Ex Rating Estimator](https://www.luogu.com.cn/problem/AT_abc292_h)

### 题目大意：

给定一个长度为 $n$ 的序列 $\{a_i\}$，参数 $B$，询问数 $q$；

每一次单点修改后，输出你当前的 `rating`，其计算方法如下分两种情况讨论:

1. 如果不存在某一个前缀平均值不低于 $B$，则输出整体平均值；
2. 否则，输出第一个不低于 $B$ 的前缀平均值。

## Solution 线段树二分

对于这种维护平均值的题目，有一个方法就是我们将所有的数减去 $B$ 后，这个问题转移成为了寻找第一个**前缀和非负的区间**。考虑使用线段树维护前缀和。

最终的答案是最前的**非负前缀和**，线段树维护前缀最大即可。对于每一次的单点修改可以转化为区间修改，因为该点的影响只对其后的位置的前缀和有影响。

对于第一种情况，只需要在这之后通过线段树上二分找到该位置计算答案即可。

对于第二种情况，只需要维护当前的数组 $\{a_i\}$ 的总和即可。

判断这两种情况也只需要看 $[1,n]$ 中的最大值，具体看代码。

时间复杂度：$O(n \log n+q \log n)$，前者是建树的复杂度，后者是查询的复杂度。 

## Code 代码

```cpp
struct tree{
    int val,lazy;
    #define mx(p) t[p].val
    #define lazy(p) t[p].lazy
}t[N*8];
inline void update(int p){mx(p)=max(mx(ls),mx(rs));}
void build(int p,int l,int r){
    t[p]={0,0};
    if(l==r){mx(p)=sum[l];return ;}//维护前缀和
    int mid=l+r>>1;
    build(ls,l,mid);build(rs,mid+1,r);
    update(p);
}
void spread(int p){
    if(lazy(p)){
        int tt=lazy(p);
        lazy(ls)+=tt;lazy(rs)+=tt;
        mx(ls)+=tt;  mx(rs)+=tt;
        lazy(p)=0;
    }
    return ;
}
void change(int p,int l,int r,int L,int R,int k){//区间修改
    if(L<=l&&r<=R){mx(p)+=k;lazy(p)+=k;return ;}
    int mid=l+r>>1;
    spread(p);
    if(L<=mid) change(ls,l,mid,L,R,k);
    if(R>mid) change(rs,mid+1,r,L,R,k);
    update(p);
}
void ask(int p,int l,int r){
	if(l==r){ans=(1.0*mx(p)+l*b)/l;return ;}
	spread(p);
    int mid=l+r>>1;
	if(mx(ls)>=0) ask(ls,l,mid);//线段树上二分
	else ask(rs,mid+1,r);//线段树上二分
}
signed main(){
    read(n,b,q);
    for(rint i=1;i<=n;i++) read(a[i]),sum[i]=sum[i-1]+a[i]-b,res+=a[i];//处理前缀和
    build(1,1,n);
    while(q--){
        int c,x;read(c,x);res+=x-a[c];
        change(1,1,n,c,n,x-a[c]);//只需要向[c,n]的后缀加上修改的值
        a[c]=x;
		if(mx(1)<0) printf("%.15lf\n",1.0*res/n);//不存在非负区间，直接输出答案
		else{
			ask(1,1,n);
			printf("%.15lf\n",ans);
		}
    }
	return 0;
}
```

---

## 作者：六楼溜刘 (赞：2)

## 题意
- 给你一个序列 $a_1,a_2,\dots,a_n$，有 $q$ 个单点修改。
- 每次修改后输出第一个大于等于给定的 $B$ 的前缀平均数。
- 若不存在这样的一个前缀，输出整个序列的平均数。
- 精度要求 $10^{-9}$。

## 题解
首先不考虑修改。

假设答案为区间 $[1,k]$ 的平均数。

则有 $\dfrac{\sum_{i=1}^ka_i}{k}\ge B$。

即 $\sum_{i=1}^ka_i \ge B \times k$。

故 $\sum_{i=1}^ka_i - B \times k \ge 0$。

则 $\sum_{i=1}^k(a_i-B) \ge 0$。

自然地，这个问题就转化成了寻找 $\sum_{i=1}^k(a_i-B) \ge 0$，且最小化 $k$。

由于这道题又带修改又带查询，我们很自然地想到了万能的线段树。

对于区间 $Q=[L,R]$，我们维护一个区间最大前缀和 $M(Q)$。为了维护这个值，我们可以再维护区间和 $S(Q)$。假设 $Q$ 的左儿子是 $Q_1$，右儿子是 $Q_2$，就可以这样转移：

$$S(Q)=S(Q_1)+S(Q_2)$$

$$M(Q)=\max(M(Q_1),S(Q_1)+M(Q_2))$$

查询时，我们可以先判断 $M(Q_1)$ 是否大于零，若左儿子大于零那答案必定再左半边，否则只能在右半边找。在右半边找的时候，由于 $M$ 只维护了这个区间内的数据，没有考虑区间左侧的数据，我们可以传一个参数 $A$，即这个区间左侧所有数据的总和，判断的时候再仿照之前线段树上传的公式合并一下就行了。

初始化复杂度 $O(n \log n)$，每个操作复杂度 $O(\log n)$，共有 $q$ 个操作。总复杂度 $O(n \log n + q \log n)$，随便过。

## code
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define int long long 
using namespace std;
const int N=5e5+5;
int n,b,q,a[N];
struct SegmentTree{
	#define lson l,m,id<<1
	#define rson m+1,r,id<<1|1
private:
//防止 Dev-C++ 的代码补全跳一堆没用的东西，对性能完全没有影响。

	int premax[N<<2],prevoc[N<<2],querysum[N<<2];
//单点修改不需要懒标记。
	void PushUp(int id){
		querysum[id]=querysum[id<<1]+querysum[id<<1|1];
		if(premax[id<<1]>=querysum[id<<1]+premax[id<<1|1]){
			premax[id]=premax[id<<1];
			prevoc[id]=prevoc[id<<1];
		}else{
			premax[id]=premax[id<<1|1]+querysum[id<<1];
			prevoc[id]=prevoc[id<<1|1];
		}
	}
public:
	void Build(int *A,int l=1,int r=n,int id=1){
		if(l==r){
			querysum[id]=premax[id]=A[l];
			prevoc[id]=l;
			return;
		}
		int m=(l+r)>>1;
		Build(A,lson);
		Build(A,rson);
		PushUp(id);
	}
	void Update(int P,int X,int l=1,int r=n,int id=1){
		if(l==r){
			querysum[id]=premax[id]=X;
			prevoc[id]=l;
			return;
		}
		int m=(l+r)>>1;
		if(P<=m) Update(P,X,lson);
		else     Update(P,X,rson);
		PushUp(id);
	}
	pair<int,int> Search(int add=0,int l=1,int r=n,int id=1){
//由于要算平均数，我返回时多返回了区间右端点，读者可以自行尝试其他方法。
		if(l==r) return make_pair(add+premax[id],l);
		int m=(l+r)>>1;
		if(premax[id<<1]+add>=0) return Search(add,lson);
		return Search(add+querysum[id<<1],rson);
	}
}mt;
signed main(){
	scanf("%lld %lld %lld",&n,&b,&q);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		a[i]-=b;
	}
	mt.Build(a);
	while(q--){
		int c,x;scanf("%lld %lld",&c,&x);
		mt.Update(c,x-b);
		pair<int,int> ans=mt.Search();
		long double ans1=(long double)1*ans.first/ans.second+b;
//注意类型转换
		printf("%0.15Lf\n",ans1);
	}
}

```


---

## 作者：endswitch (赞：1)

首先可以把式子转换成 $pre_k - k\times B \ge 0$ 的形式，放进线段树里面，此时对于原序列的单点修改转换成后缀修改。

下面将 $pre_k - k\times B \ge 0$ 称为**偏差值**。

但是如果此时要查大于等于 $0$ 的数的下标是 $O(n)$ 的，因为其不满足单调性，无法二分。

此时有一个套路，对于一段原本不满足单调性的前缀取 $\max$，这个前缀 $\max$ 序列便满足单调性了。

于是可以线段树二分找到第一个下标 $pos$ 满足第 $pos$ 个偏差值大于等于 $0$。

对于原序列，额外用一个树状数组维护动态前缀和。

写得有点丑，是 $O(q\log^2n)$ 的。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 5e5 + 5; 
int n, B, Q, c, x, a[N], pre[N];

namespace SGT {
	#define mid (L + R) >> 1
	#define son p, L, R
	#define lson ls(p), L, (L + R) >> 1
	#define rson rs(p), ((L + R) >> 1) + 1, R
	
	struct Node {
		int mx, pls;
	} t[N << 2];
	
	inline int ls(int p) {
		return p << 1;
	}
	
	inline int rs(int p) {
		return p << 1 | 1;
	}
	
	inline void psup(int p) {
		t[p].mx = max(t[ls(p)].mx, t[rs(p)].mx);
		
		return ;
	}
	
	inline void modify(int x, int k, int p = 1, int L = 1, int R = n) {
		if(L == R) {
			t[p].mx = k;
			
			return ;
		}
		
		if(x <= mid) modify(x, k, lson);
		else modify(x, k, rson);
		
		psup(p);
	}
	
	inline void work(int p, int L, int R, int k) {
		t[p].mx += k;
		t[p].pls += k;
		
		return ;
	}
	
	inline void psd(int p, int L, int R) {
		if(! t[p].pls) return ;
		
		work(lson, t[p].pls), work(rson, t[p].pls);
		
		t[p].pls = 0;
		
		return ; 
	}
	
	inline void add(int l, int r, int k, int p = 1, int L = 1, int R = n) {
		if(l <= L && R <= r) {
			work(son, k);
			
			return ;
		}
		
		psd(son);
		
		if(l <= mid) add(l, r, k, lson);
		if(r > mid) add(l, r, k, rson);
		
		psup(p);
		
		return ;
	}
	
	inline int ask(int l, int r, int p = 1, int L = 1, int R = n) {
		int res = -1e18;
		
		if(l <= L && R <= r) return t[p].mx;
		
		psd(son);
		
		if(l <= mid) res = max(res, ask(l, r, lson));
		if(r > mid) res = max(res, ask(l, r, rson));
		
		return res;
	}
	
	inline int binary() {
		int l = 1, r = n, ans = n;
		
		while(l <= r) {
			int Mid = (l + r) >> 1;
			
			if(ask(1, Mid) >= 0) ans = Mid, r = Mid - 1;
			else l = Mid + 1;
		}
		
		return ans;
	}
	
	#undef mid
	#undef son
	#undef lson
	#undef rson
}

using namespace SGT;

namespace BIT {
	int t[N];
	
	inline int lowbit(int x) {
		return x & -x;
	}
	
	inline void Add(int x, int k) {
		for( ; x <= n ; x += lowbit(x))
			t[x] += k;
		
		return ;
	}
	
	inline int Query(int x) {
		int res = 0;
		
		for( ; x ; x -= lowbit(x))
			res += t[x];
		
		return res;
	}
}

using namespace BIT;

signed main() {
	ios_base :: sync_with_stdio(NULL);
	cin.tie(nullptr);
	cout.tie(nullptr);
	
	cin >> n >> B >> Q;
	for(int i = 1 ; i <= n ; ++ i)
		cin >> a[i], pre[i] = pre[i - 1] + a[i];
	
	for(int i = 1 ; i <= n ; ++ i)
		Add(i, a[i]), modify(i, pre[i] - i * B);
	
	while(Q --) {
		cin >> c >> x;
		
		add(c, n, x - a[c]);
		Add(c, x - a[c]);
		
		a[c] = x;
		
		int pos = binary();
		
		cout << fixed << setprecision(20) << (Query(pos) * 1.0 / pos * 1.0) << '\n';
	}
	
	return 0;
}
```

---

## 作者：PineappleSummer (赞：1)

简单 H 题。

简要题意：

给出 $n$ 个数 $a_i$ 和一个数 $B$，若存在一个数 $k$，使得 $\frac{1}{k}(\sum_{i=1}^ka_i) \ge B$，整个序列的价值为第一个不小于 $B$ 的 $\frac{1}{k}(\sum_{i=1}^ka_i)$。否则整个序列的价值为 $\frac{1}{n}(\sum_{i=1}^na_i)$。

需要支持单点修改，修改后要输出整个序列的价值。

$\frac{1}{k}(\sum_{i=1}^ka_i)$ 和 $B$ 的大小好像很难比较，考虑将 $a_i$ 减掉 $B$，加入线段树里。不存在一个前缀和大于 $0$ 时，答案为 $\frac{1}{n}(\sum_{i=1}^na_i)$，否则答案为前缀和第一次大于 $0$ 时的 $\frac{1}{k}(\sum_{i=1}^ka_i)$。

如何判断是否有一个前缀和大于 $0$ 呢？线段树中维护 $t_p$ 表示区间和，$mav_p$ 表示区间前缀最大值。上传标记时更新这两个标记即可。如果 $mav_1\ge 0$，就说明存在 $\frac{1}{k}(\sum_{i=1}^ka_i) \ge B$。

可以通过线段树上二分找到一个 $k$，使得 $\frac{1}{k}(\sum_{i=1}^k(a_i-B)) \ge 0$。具体实现细节可见代码。

时间复杂度是 $O(n\log n)$ 的。

一些注意事项：
- query 返回的应是两个值，一个是 $k$，另一个是 $\frac{1}{k}(\sum_{i=1}^k(a_i-B))$。
- query 函数中递归右子树时，$val$ 应该加上 $t_{ls}$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef long long LL;
typedef pair <int, int> pii;
const int N = 1e6 + 10;
int n, B, q;
int a[N];

namespace SegmentTree {
	int t[N << 2], mav[N << 2]; // mav 维护一个最大前缀和
	#define ls p << 1
	#define rs p << 1 | 1
	#define mid ((l + r) >> 1)
	void upd (int p) {
		t[p] = t[ls] + t[rs];
		mav[p] = max (mav[ls], t[ls] + mav[rs]);
	}
	void build (int p, int l, int r) {
		if (l == r) return mav[p] = t[p] = a[l] - B, void (0);
		build (ls, l, mid); build (rs, mid + 1, r); upd (p);
	}
	void modify (int p, int l, int r, int pos, int val) {
		if (l == r) return mav[p] = t[p] = val - B, void (0);
		if (pos <= mid) modify (ls, l, mid, pos, val);
		else modify (rs, mid + 1, r, pos, val); upd (p);
	}
	pii query (int p, int l, int r, int val) {
		if (l == r) return make_pair (t[p], l);
		if (mav[ls] + val >= 0) return query (ls, l, mid, val);
		else {
			pii pi = query (rs, mid + 1, r, val + t[ls]);
			return make_pair (t[ls] + pi.first, pi.second);
		}
	}
}
using namespace SegmentTree;

signed main ()
{
	scanf ("%lld %lld %lld", &n, &B, &q);
	for (int i = 1; i <= n; i++) scanf ("%lld", &a[i]);
	build (1, 1, n);
	while (q--) {
		int pos, val;
		scanf ("%lld %lld", &pos, &val);
		modify (1, 1, n, pos, val);
		pii p = query (1, 1, n, 0);
		printf ("%.15lf\n", (double) (p.first + B * p.second) * 1.0 / p.second * 1.0);
	}
	return 0;
}
```

[AC 记录](https://atcoder.jp/contests/abc292/submissions/55350541)

---

## 作者：ABookCD (赞：1)

[我的 ABC-292 全场题解](https://www.cnblogs.com/arizonayyds/articles/abc292.html)

### 简要题意

给定一个人 $n$ 场比赛的表现分 $a_i$，在第 $k$ 场比赛后 $(1 \le k \le n)$，他的 rating 变化为 $\frac{1}{n} \sum\limits_{1 \le j \le k} a_j$。

但是当一个人的 rating 达到 $B$ 的时候，它的 rating 就不再变化了。

给定 $q$ 个询问，每次询问给定两个数 $a_i$ 和 $x_i$，表示这个人第 $a_i$ 场比赛的表现分变成 $x_i$，求修改后他最终的 rating，操作可持久化。

$n \le 5\times 10^5,q \le 10^5$。



### Solution:

先推一下式子，考虑到什么时候 rating 才爆分。

$$
\begin{aligned}
&\frac{1}{k}\sum\limits_{1\le i \le k} a_i > B \\
\implies &\sum\limits_{1\le i \le k} a_i > Bk \\
\implies  & \sum\limits_{1\le i \le k} (a_i-B)> 0\\
\end{aligned}
$$

考虑构造一个数组 $\{b_n\}$，满足 $b_i=a_i-B(1\le i \le n)$，那么当 $b_i$ 的前缀和第一次大于 $0$ 时完成爆分。

直接用线段树维护区间里前缀和的最大值。

考虑查询的时候要线段树上二分找到第一次爆分，所以还要维护区间和。

线段树上二分的一些细节见代码。

### Code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct tree{
	int id,l,r,mx,sum,lazy;
}t[2000010];
int a[500010];
void pushup(int id){
	t[id].sum=t[id<<1].sum+t[id<<1|1].sum;
	t[id].mx=max(t[id<<1].mx,t[id<<1].sum+t[id<<1|1].mx);
}
void pushdown(int id){
	if(t[id].lazy!=0){
		t[id<<1].lazy=t[id<<1|1].lazy=t[id].lazy;
		t[id<<1].sum=t[id].lazy*(t[id<<1].r-t[id<<1].l+1);
		t[id<<1|1].sum=t[id].lazy*(t[id<<1|1].r-t[id<<1|1].l+1);
		t[id].lazy=0;
	}
}
void build(int id,int l,int r){
	t[id].l=l;
	t[id].r=r;
	t[id].sum=t[id].lazy=t[id].mx=0;
	if(l==r){
		t[id].sum=a[l];
		t[id].mx=a[l];
		return;
	}
	int  mid=(l+r)>>1;
	build(id<<1,l,mid);
	build(id<<1|1,mid+1,r);
	pushup(id);
}
void update(int id,int l,int r,int v){

	if(l<=t[id].l&&t[id].r<=r){
		t[id].sum=v*(t[id].r-t[id].l+1);
		t[id].lazy=v;
		t[id].mx=v*(t[id].r-t[id].l+1);
		return;
	}
	pushdown(id);
	int mid=(t[id].l+t[id].r)>>1;
	if(l<=mid) update(id<<1,l,r,v);
	if(r>mid) update(id<<1|1,l,r,v);
	pushup(id);
}
pair<int,int> query(int id,int l,int r,int sum){
//	cout<<id<<" "<<l<<" "<<r<<" "<<sum<<" "<<t[id].sum<<" "<<t[id<<1].mx<<endl;
	if(t[id].l==t[id].r){
		return {t[id].l,sum+t[id].mx};
	}
	pushdown(id);
	if(sum+t[id<<1].mx>=0){
		return query(id<<1,l,r,sum);
	}else{
		return query(id<<1|1,l,r,sum+t[id<<1].sum);
	}
}
signed main(){
	int n,b,q;
	cin>>n>>b>>q;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i]-=b;
	}
	build(1,1,n);
	while(q--){
		int op,x;
		cin>>op>>x;
		x-=b;
		update(1,op,op,x);
	//	return 0;
		pair<int,int> pr=query(1,1,n,0);
	//	cout<<pr.first<<" "<<pr.second<<endl;
		double ans=b+1.000000*pr.second/pr.first;
		cout<<fixed<<setprecision(10)<<ans<<endl;
	}
} 
```



---

## 作者：CrTsIr400 (赞：1)

## [ABC292 Ex-Rating Estimator](https://atcoder.jp/contests/abc292/tasks/abc292_h) 题解

题意：给出一个长度为 $N$ 的序列 $A$，设 $C_i$ 为 $\dfrac{\sum_{j=1}^i A_i}{i}$，如果这个 $C_i$ 大于等于 $B$ 的话，其后面的 $C$ 值也和 $C_i$ 一样。求 $C_n$。

思路：一开始没有什么套路，动态维护平均值没有什么很好的意见。

套路1：所以我们把整个 $A$ 序列减去 $B$，设 $A'_i=A_i-B$。

发现平均值大于 $B$，在对于 $A'$ 序列而言**就是这段前缀之和**大于 $0$。

于是考虑对 $A'$ 维护一个前缀和数组 $S$，而修改单点就是给其后一段区间加上一个值。

考虑如何查询：如果没有 $S_i>0$ 的情况，直接输出 $B+\dfrac{S_n}{n}$ 即可。

如果有，那么就需要维护这个数组里面最早出现的大于 $0$ 的数。这又怎么寻找呢？

套路2：我们线段树之中维护一个区间最大值，然后如果区间最大值小于 $0$ 即可跳过；根据这个规则进行剪枝。

为什么是区间最大值？因为这样的剪枝容易维护也容易统计。

所以，最终我们只需要单点查询，后缀加，根据区间最大值二分即可。时间复杂度 $O(m\log n)$。

```cpp
I cl,cr,cx,n,B,q,rt;
const I N=5e5+10,SN=1e6+10;
LL M[SN],A[SN],s[N];
I L[SN],R[SN],cnt,c[N];
void psd(I p){
	if(!A[p])return;
	M[L[p]]+=A[p];
	M[R[p]]+=A[p];
	A[L[p]]+=A[p];
	A[R[p]]+=A[p];
	A[p]=0;}
void psu(I p){
	M[p]=max(M[L[p]],M[R[p]]);}
void build(I&p,I l,I r){p=++cnt;
	if(l==r){M[p]=s[l];return;}
	I mid=l+r>>1;build(L[p],l,mid);build(R[p],mid+1,r);psu(p);}
void chg(I p,I l,I r){
	psd(p);
	if(cl<=l&&r<=cr){
		A[p]+=cx;
		M[p]+=cx;
		return;}
	I mid=l+r>>1;
	if(cl<=mid)chg(L[p],l,mid);
	if(mid<=cr)chg(R[p],mid+1,r);
	psu(p);}
LL ANSR=0;
void add(I p,I x){
	cl=p;cr=n;cx=(x-B-c[p]);c[p]+=cx;
	ANSR+=cx;
	chg(rt,1,n);}
LL ms=0;
I bsst(I p,I l,I r){
	psd(p);
	if(M[p]<0)return inf;
	if(l==r)return ms=M[p],l;
	I mid=l+r>>1,res=bsst(L[p],l,mid);
	if(res^inf)return res;
	return bsst(R[p],mid+1,r);}
long double gans(){
	I ans=bsst(rt,1,n);
	if(ans==inf)return B+1.0*ANSR/n;
	return B+1.0*ms/ans;}
I main(){
	in(n,B,q);
	for(I i=1;i<=n;++i)in(c[i]),c[i]-=B,s[i]=s[i-1]+c[i];
	ANSR=s[n];
	build(rt,1,n);
	for(I i=1,ci,xi;i<=q;++i){
		in(ci,xi);
		add(ci,xi);
		printf("%.10Lf\n",gans());}
	return 0;
}
```



---

## 作者：苏联小渣 (赞：1)

转化条件：找到第一个 $i$ 使得 $\dfrac{1}{i}(a_1+...+a_i) \ge B$

即 $S_i \ge i \times B$，其中 $S$ 为前缀和数组。

再转化为 $S_i-i \times B \ge 0$，其中左边的 $S_i$ 可以通过线段树进行维护。单点修改可以转化为单点加，单点加 $x$ 可以转化为后缀的前缀和数组加 $x$。

那么现在的任务是找到第一个 $\ge 0$ 的值对应的下标。维护区间最大值，线段树上二分查找即可。具体方法为，如果左子树最大值 $\ge 0$ 就走左子树，否则走右子树。

设位置为 $x$，答案就是 $\dfrac{S_x}{x}$。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define lc(x) x<<1
#define rc(x) x<<1|1
int n, B, q, pre, x, y, fir, a[500010], d[2000010], tag[2000010];
void pushup(int k){
	d[k] = max(d[lc(k)], d[rc(k)]);
}
void pushdown(int k, int l, int r){
	if (tag[k] != 0){
		int mid = l + r >> 1;
		tag[lc(k)] += tag[k];
		tag[rc(k)] += tag[k];
		d[lc(k)] += tag[k];
		d[rc(k)] += tag[k];
		tag[k] = 0;
	}
}
void modify(int k, int l, int r, int x, int y, int val){
	if (x <= l && r <= y){
		d[k] += val;
		tag[k] += val;
		return ;
	}
	pushdown(k, l, r);
	int mid = l + r >> 1;
	if (x <= mid) modify(lc(k), l, mid, x, y, val);
	if (y > mid) modify(rc(k), mid+1, r, x, y, val);
	pushup(k);
}
int query(int k, int l, int r){
	if (l == r) return l;
	int mid = l + r >> 1;
	pushdown(k, l, r);
	if (d[lc(k)] >= 0) return query(lc(k), l, mid);
	else if (d[rc(k)] >= 0) return query(rc(k), mid+1, r);
	return n;
}
int querysum(int k, int l, int r, int x){
	if (l == r) return d[k];
	int mid = l + r >> 1, ret = 0;
	pushdown(k, l, r);
	if (x <= mid) ret += querysum(lc(k), l, mid, x);
	else ret += querysum(rc(k), mid+1, r, x);
	return ret;
}
signed main(){
	scanf ("%lld%lld%lld", &n, &B, &q);
	for (int i=1; i<=n; i++){
		scanf ("%lld", &a[i]);
		pre += a[i];
		modify(1, 1, n, i, i, pre-B*i);
	}
	for (int i=1; i<=q; i++){
		scanf ("%lld%lld", &x, &y);
		modify(1, 1, n, x, n, y-a[x]);
		a[x] = y;
		fir = query(1, 1, n);
		printf ("%.9lf\n", (double)(querysum(1, 1, n, fir) + B*(fir)) / (double)(fir));
	}
	return 0;
}
```

---

## 作者：FReQuenter (赞：1)

发现是单点修改，区间查询。考虑线段树。

那么要维护什么：题目中有两个关键点，求平均值和一旦 Rating 大于 $B$ 就停止计算。

进行一个简单的转化：把所有数减去 $B$，最后答案加上 $B$（方便之后计算区间最大前缀和）。

这两个量分别依赖区间和与区间最大前缀和。前者可以通过区间和除以区间大小得到，后者可以二分一个点，以这个点为右端点的区间最大前缀和刚好是第一个最大前缀和大于 $0$ 的地方。

考虑如何维护这两个值：区间和就是普通的线段树，对于区间最大前缀和，我们考虑它是由两种情况产生：（1）左儿子区间的最大前缀和；（2）左儿子区间和加上右儿子区间最大前缀和。这两种构成方法取 $\max$ 即可。

综上，写出建树和单点查询代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define fi first
#define se second
#define MAXN 500005
#define lson(root) (root<<1)
#define rson(root) (root<<1|1)
using namespace std;
int n,b,q,a[MAXN],sum[MAXN<<2],maxn[MAXN<<2];
void pushup(int root){
	sum[root]=sum[lson(root)]+sum[rson(root)];
	if(maxn[lson(root)]>=sum[lson(root)]+maxn[rson(root)]) maxn[root]=maxn[lson(root)];
	else maxn[root]=maxn[rson(root)]+sum[lson(root)];
}
void build(int root,int l,int r){
	if(l==r) sum[root]=maxn[root]=a[l];
	else{
		int mid=(l+r)>>1;
		build(lson(root),l,mid);
		build(rson(root),mid+1,r);
		pushup(root);
	}
}
void update(int p,int v,int root,int l,int r){
	if(l==r) sum[root]=maxn[root]=v;
	else{
		int mid=(l+r)>>1;
		if(p<=mid) update(p,v,lson(root),l,mid);
		if(p>mid) update(p,v,rson(root),mid+1,r);
		pushup(root);
	}
}
```

那么如何查询？首先要找到第一个区间最大前缀和大于 $0$ 的位置，再计算该位置之前（包括该位置）的区间平均数并加上 $B$ 作为答案输出。第一步可以直接二分里面套线段树的查找，复杂度是 $n \log^2 n$（按道理是过不去的，可是不卡任何常数它还的过去了）同样也可以线段树上二分，省去一个 $\log$。查询函数可以返回两个量，区间和与区间长度从而计算答案。查询函数内，还要记录当前区间和，根据二分时是向左还是向右加上不同的值即可，思想和 pushup 函数类似。

查询代码及主函数（完整代码不放了，两部分拼起来就是）：

```cpp
pair<int,int> query(int add,int root,int l,int r){
	if(l==r) return {add+maxn[root],l};
	else{
		int mid=(l+r)>>1;
		if(maxn[lson(root)]+add>=0) return query(add,lson(root),l,mid);
		else return query(add+sum[lson(root)],rson(root),mid+1,r);
	}
}
signed main(){
	cin>>n>>b>>q;
	for(int i=1;i<=n;i++) cin>>a[i],a[i]-=b;
	build(1,1,n);
	while(q--){
		int c,x;
		cin>>c>>x;
		update(c,x-b,1,1,n);
		pair<int,int> ans=query(0,1,1,n);
		cout<<fixed<<setprecision(15)<<1.0*ans.fi/ans.se+1.0*b<<'\n';
	}
	return 0;
}
```

---

## 作者：lfxxx_ (赞：0)

- 明显，通过公式，我们可以知道，我们需要一个这样的点 $p$，使得 $\dfrac{1}{p}\sum_{i=1}^pa_i\ge B$ 并且 $p$ 之前没有满足这个条件的点。

- 我们通过移项，把公式转化成 $\sum_{i=1}^p(a_i-B)\ge0$，维护前缀和 $S_i=\sum_{j=1}^i(a_i-B)$，于是公式变为 $S_p\ge0$ 并且 $\max_{i=1}^{p-1}(S_i) < 0$。

- 之后就可以二分出 $p$，然后线段树判断了。

- 最终的答案就是 $\dfrac{S_p+Bp}{p}$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ldbl long double
using namespace std;
const int N=5e5+5,inf=1e18;
int a[N];
ldbl tr[N<<2],tag[N<<2];
void pushup(int p){tr[p]=max(tr[p<<1],tr[p<<1|1]);}
void addtag(int p,int pl,int pr,int d)
{
	tag[p]+=d;
	tr[p]+=d;
}
void pushdown(int p,int pl,int pr)
{
	int mid=(pl+pr)>>1;
	if(tag[p]!=0)
	{
		addtag(p<<1,pl,mid,tag[p]);
		addtag(p<<1|1,mid+1,pr,tag[p]);
		tag[p]=0;
	}
}
void update(int p,int pl,int pr,int L,int R,int d)
{
	if(R<pl||pr<L)
		return ;
	if(L<=pl&&pr<=R)
	{
		addtag(p,pl,pr,d);
		return ;
	}
	int mid=(pl+pr)>>1;
	pushdown(p,pl,pr);
	update(p<<1,pl,mid,L,R,d);
	update(p<<1|1,mid+1,pr,L,R,d);
	pushup(p);
}
int query(int p,int pl,int pr,int L,int R)
{
	if(R<pl||pr<L)
		return -inf;
	if(L<=pl&&pr<=R)
		return tr[p];
	int mid=(pl+pr)>>1;
	pushdown(p,pl,pr);
	return max(query(p<<1,pl,mid,L,R),query(p<<1|1,mid+1,pr,L,R));
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n,B,m,sum=0,val=0;
	cin>>n>>B>>m;
	for(int i=1;i<=n;++i)
	{
		cin>>a[i];
		val+=a[i]-B;
		sum+=a[i];
		update(1,1,n,i,i,val);
	}
	while(m--)
	{
		int x,k;
		cin>>x>>k;
		sum+=k-a[x];
		update(1,1,n,x,n,k-a[x]);
		a[x]=k;
		if(tr[1]<0)
		{
			cout<<fixed<<setprecision(9)<<sum*1.0/n<<'\n';
		}
		else
		{
			
		int l=0,r=n+1;
		while(l+1<r)
		{
			int mid=(l+r)>>1;
			if(query(1,1,n,1,mid)<0)
				l=mid;
			else
				r=mid; 
		}
//		cout<<r<<' '<<query(1,1,n,r,r)<<'\n';
		cout<<fixed<<setprecision(9)<<(1.0*query(1,1,n,r,r)+B*r)/r<<'\n';
		 } 
	}
}
```

---

## 作者：anonymous_Y (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc292_h?contestId=179083)

如果第 $i$ 场比赛你的成绩为 $p_i$，那你的 rating 在第 $k$ 场比赛后将会变为前 $k$ 场比赛成绩的平均值，也就是 $\frac{1}{k}(\sum^{k}_{i=1}p_i)$。
 
不难发现，每次改分数就是单点修改，而所谓的平均值就是区间求和。这让你想到了什么？——线段树。
 
同时这个区间有一个特点——都从头开始。这让我们又想到另外一个东西——前缀和。
 
 单点修改和区间求和这都很好操作，可是题目里面还有一个要求——“不过，如果在某场比赛后，你的 rating 大于等于一个值 $B$，它以后将不会在变化。”
 
也就是说，我们要找到第一个位置，平均数要大于等于 $B$ 并且这就是答案。最暴力的做法就是挨个扫过去。这显然不是最优的。
 
 
如果此时我们用数组 $c_i$ 记录位置 $1-i$ 平均数和 $B$ 的大小关系（大于 $B$ 为正，反之为负），那么我们现在的问题就转化为了求 $c$ 数组中第一个大于等于 $0$ 的位置。
 
这时候线段树就发挥了作用：我们用线段树记录区间最大值，如果该节点的左子树的 $\max$ 值小于 $0$，说明这部分都无法满足大于 $B$ 的条件，转向右子树继续搜索，右子树同理。
 
于是这样子，就可找到第一个位置，平均数大于等于 $B$ 的数。
 ```cpp
void ask(int l,int r,int p){
	if(l==r){
		ans=double(t[p].mx+b*l)/l;
		return ;
	}
	pushdown(p);
	int mid=(l+r)/2;
	if(t[p*2].mx>=0) return ask(t[p].l,mid,p*2);
	return ask(mid+1,t[p].r,p*2+1);
}
```
还有一点很重要的就是不要忘记开 `long long` 和 `double`。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=5e5+10;
struct node{
	int l,r;
	int mx,tag;
}t[maxn*4];
int a[maxn],n,m,b,c[maxn];
int x,y;
void pushup(int p){
	t[p].mx=max(t[p*2].mx,t[p*2+1].mx);
}
void pushdown(int p){
	if(t[p].tag){
		t[p*2].mx+=t[p].tag;
		t[p*2].tag+=t[p].tag;
		t[p*2+1].mx+=t[p].tag;
		t[p*2+1].tag+=t[p].tag;
		t[p].tag=0;
	}
}
void build(int l,int r,int p){
	t[p].l=l,t[p].r=r;
	if(l==r){
		t[p].mx=c[l];
		return ;
	}
	int mid=(l+r)/2;
	build(l,mid,p*2);
	build(mid+1,r,p*2+1);
	pushup(p);
}
void change(int l,int r,int p,int k){
	if(t[p].l>=l&&t[p].r<=r){
		t[p].mx+=k;
		t[p].tag+=k;
		return ;
	}
	pushdown(p);
	int mid=(t[p].l+t[p].r)/2;
	if(l<=mid) change(l,r,p*2,k);
	if(r>mid) change(l,r,p*2+1,k);
	pushup(p);
}
double ans,res;
void ask(int l,int r,int p){
	if(l==r){
		ans=double(t[p].mx+b*l)/l;
		return ;
	}
	pushdown(p);
	int mid=(l+r)/2;
	if(t[p*2].mx>=0) return ask(t[p].l,mid,p*2);
	return ask(mid+1,t[p].r,p*2+1);
}
signed main(){
	cin>>n>>b>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];res+=a[i];
		c[i]+=c[i-1]+a[i]-b;
	}
	build(1,n,1);
	while(m--){
		cin>>x>>y;
		change(x,n,1,y-a[x]);res+=y-a[x];
		a[x]=y;
		if(t[1].mx<0){//如果整个c数组都找不到大于零的，也就是没有办法满足大于B，这时候直接输出平均数QAQ
			printf("%.10lf\n",res*1.0/n);
		}
		else{
			ask(1,n,1);
			printf("%.10lf\n",ans);
		}
	}
	return 0;
}
```

---

## 作者：complete_binary_tree (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/AT_abc292_h)

题目要让我们求第一个 $\text{rating} \ge B$ 的位置，也就是 $\displaystyle \frac 1 i\sum_{j=1}^i p_i \le B$ 的最小 $i$。

我们发现这个式子可以化为 $B \cdot i - \sum_{j=1}^i p_i \le 0$。所以如果我们把第 $i$ 初始值设定为 $B \cdot i$，那么后面的操作就可以做减法。

发现在这个式子中数 $i$ 的改变只会影响 $[i,n]$ 区间的数。所以修改是区间修改，考虑线段树。查询要查询第一个小于等于 $0$ 的位置，考虑线段树上维护最小值，二分即可。

时间复杂度 $O(n \log n + q \log n)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;

int n, b, q, a[N];

struct tree { int l, r; long long mn, lz; };
struct st {
    tree t[N << 2];
    #define ls ( x << 1 )
    #define rs ( x << 1 | 1 )
    void build( int x, int l, int r ) {
        t[x].l = l, t[x].r = r;
        if( l == r ) {
            t[x].mn = 1ll * l * b;
            return ;
        }
        int mid = ( l + r ) >> 1;
        build( ls, l, mid ), build( rs, mid + 1, r );
        t[x].mn = min( t[ls].mn, t[rs].mn );
        return ;
    }
    void down( int x ) {
        long long lz = t[x].lz;t[x].lz = 0;
        t[ls].mn += lz, t[rs].mn += lz;
        t[ls].lz += lz, t[rs].lz += lz;
    }
    void add( int x, int l, int r, int y ) {
        if( t[x].l > r || t[x].r < l ) return ;
        if( t[x].l >= l && t[x].r <= r ) {
            t[x].lz += y, t[x].mn += y;
            return ;
        }
        down( x );
        add( ls, l, r, y ), add( rs, l, r, y );
        t[x].mn = min( t[ls].mn, t[rs].mn );
    }
    int query( int x ) {
        if( t[x].l == t[x].r ) return t[x].l;
        down( x );
        if( t[ls].mn <= 0 ) return query( ls );
        return query( rs );
    }
    long long find( int x, int pos ) {
        if( t[x].l == t[x].r ) return t[x].mn;
        int mid = ( t[x].l + t[x].r ) >> 1;
        down( x );
        if( pos <= mid ) return find( ls, pos );
        return find( rs, pos );
    }
} t1;

int main() {
    ios::sync_with_stdio( 0 ), cin.tie( 0 ), cout.tie( 0 );
    cin >> n >> b >> q;
    t1.build( 1, 1, n );
    for( int i = 1; i <= n; ++i ) {
        cin >> a[i];
        t1.add( 1, i, n, -a[i] );
    }
    while( q-- ) {
        int pos, x;
        cin >> pos >> x;
        t1.add( 1, pos, n, a[pos] - x );
        a[pos] = x;
        pos = t1.query( 1 );
        if( t1.find( 1, pos ) > 0 && pos < n ) pos++;
        cout << fixed << setprecision( 10 ) << ( 1.0 * ( 1.0 * pos * b - t1.find( 1, pos ) ) ) / pos << endl;
    }
    return 0;
}
```

---

## 作者：快斗游鹿 (赞：0)

## 思路

如果没有修改操作，原问题转化为找和大于等于 $B\times len$ 的一段区间 $[1,r]$，满足 $r$ 最小，如果没有就输出整个数列的平均数。因为左端点固定为 $1$，所以可以先对 $a$ 数列做前缀和。如果对其中每个数都减 $B$，那么实际上就是找一段前缀使得和为非负。用线段树维护区间 $\max$，查询时在线段树上二分即可。

注意到修改都是单点修改，直接改就可以了。

## 代码

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
struct tree{
	int l,r,mx,tag;
}t[N<<2];
int n,b,q,a[N],sum[N],p;
double ans;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
void pushup(int p){
	t[p].mx=max(t[p<<1].mx,t[p<<1|1].mx);
}
void build(int p,int l,int r){
	t[p].l=l;t[p].r=r;
	if(l==r){
		t[p].mx=sum[l];
		return;
	}
	int mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	pushup(p);
}
void spread(int p){
	t[p<<1].tag+=t[p].tag;
	t[p<<1|1].tag+=t[p].tag;
	t[p<<1].mx+=t[p].tag;
	t[p<<1|1].mx+=t[p].tag;
	t[p].tag=0;
}
void change(int p,int l,int r,int w){
	if(l<=t[p].l&&t[p].r<=r){
		t[p].mx+=w;t[p].tag+=w;return;
	}
	spread(p);
	int mid=(t[p].l+t[p].r)>>1;
	if(l<=mid)change(p<<1,l,r,w);
	if(r>mid)change(p<<1|1,l,r,w);
	pushup(p);
}
void ask(int p){
	if(t[p].l==t[p].r){
		ans=(double)(t[p].mx+t[p].l*b)/t[p].l;return;
	}
	spread(p);
	if(t[p<<1].mx>=0)ask(p<<1);
	else ask(p<<1|1);
	return; 
}
signed main(){
	n=read();b=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read(),sum[i]=sum[i-1]+a[i]-b;
	p=sum[n]+n*b;
	build(1,1,n);
	while(q--){
		int c,x;c=read();x=read();p=p-a[c]+x;
		change(1,c,n,x-a[c]);
		a[c]=x;
		if(t[1].mx<0)printf("%.15lf\n",(double)p/n);
		else{
			ask(1);printf("%.15lf\n",ans);
		}
	}
}

```


---

## 作者：JWRuixi (赞：0)

~~这绝对比 G 简单……~~

- 题意

给定 **rating** 计算公式 ${1\over n}\sum_{i=1}^np_i$，其中 $p_i$ 为第 $i$ 场比赛的 **performance**。规定若在某一次比赛后 **rating** 超过给定阈值 $B$，那么 **rating** 将不会在发生变化。

支持单点修改，每次修改后输出 $n$ 场比赛后的 **rating**。

- 分析

我们考虑最早在第 $k$ 次比赛后 **rating** 超过 $B$，由于 **rating** 是分数形式不好处理，不妨设 $f(k)=\sum_{i=1}^kp_i$，则可以转化成 $f(k)\ge kB$，即 $kB-f(k)\le0$。

考虑每次修改的过程实际上是对于 $i\in[x,n]$ 的 $f(i)$ 加上 $y-a_x$。那我们可以考虑维护 $kB-f(k)$，每次操作区间加 $a_x-y$，查询就是找到第一个 $\le0$ 的位置，线段树维护即可。

复杂度 $\mathcal O(n\log n)$。

- code

```cpp
#include <bits/stdc++.h>
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#define LL long long
#define double long double
#define int long long
#define writesp(x) write(x), putchar(' ')
#define writeln(x) write(x), putchar('\n')
#define FileIO(ch) freopen(ch".in", "r", stdin), freopen(ch".out", "w", stdout)
using namespace std;

namespace IO {
    char ibuf[(1 << 20) + 1], *iS, *iT;
#if ONLINE_JUDGE
#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
#else
#define gh() getchar()
#endif
    inline long long read() {
        char ch = gh();
        long long x = 0;
        bool t = 0;
        while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
        while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
        return t ? ~(x - 1) : x;
    }
    template <typename _Tp>
    inline void write(_Tp x) {
    	static char stk[64], *top = stk;
        if (x < 0) {
            x = ~(x - 1);
            putchar('-');
        }
        do *top++ = x % 10, x /= 10;
        while (x);
        while (top != stk) putchar((*--top) | 48);
    }
}

using IO::read;
using IO::write;

const int maxn(5e5 + 500);
int n, m, B, a[maxn], pre[maxn], sum;

namespace SGT {
	struct Node {
		int v, tg;
	} tr[maxn << 2];
#define ls (p << 1)
#define rs (p << 1 | 1)
	inline void pushup (int p) {
		tr[p].v = min(tr[ls].v, tr[rs].v);
	}
	inline void pushtg (int p, int v) {
		tr[p].v += v, tr[p].tg += v;
	}
	inline void pushdown (int p) {
		if (!tr[p].tg) return;
		pushtg(ls, tr[p].tg);
		pushtg(rs, tr[p].tg);
		tr[p].tg = 0;
	}
	inline void build (int l, int r, int p) {
		if (l == r) {
			tr[p].v = l * B - pre[l];
			return;
		}
		int mid = (l + r) >> 1;
		build(l, mid, ls);
		build(mid + 1, r, rs);
		pushup(p);
	}
	inline void upd (int s, int t, int l, int r, int p, int v) {
		if (s <= l && r <= t) return pushtg(p, v);
		pushdown(p);
		const int mid = (l + r) >> 1;
		if (s <= mid) upd(s, t, l, mid, ls, v);
		if (mid < t) upd(s, t, mid + 1, r, rs, v);
		pushup(p);
	}
	inline double qry (int l, int r, int p) {
		if (l == r) return (double)(l * B - tr[p].v) / l;
		pushdown(p);
		const int mid = (l + r) >> 1;
		if (tr[ls].v <= 0) return qry(l, mid, ls);
		else return qry(mid + 1, r, rs);
	}
}

signed main() {
	n = read(), B = read(), m = read();
	for (int i = 1; i <= n; i++) a[i] = read(), pre[i] = pre[i - 1] + a[i];
	sum = pre[n];
	SGT::build(1, n, 1);
	for (int i = 1, x, y; i <= m; i++) {
		x = read(), y = read();
		sum += (y - a[x]), SGT::upd(x, n, 1, n, 1, a[x] - y), a[x] = y;
		if (SGT::tr[1].v > 0) printf("%.10Lf\n", (double)(sum) / n);
		else printf("%.10Lf\n", SGT::qry(1, n, 1));
	}
}
// I love WHQ!
```

---

## 作者：ダ月 (赞：0)

### 题目分析：

结论 $1$，对于平均值大于等于 $B$ 的条件，我们只需要维护 $\begin{aligned}\sum_{i=1}^na_i-nB\ge 0\end{aligned}$ 即可。

证明：只用对 $\begin{aligned}\frac{1}{n}\sum_{i=1}^na_i\ge B\end{aligned}$ 移项变形即可。

我们先对原序列求前缀和 $s$，显然，如果对 $x$ 位置修改，那么 $s$ 序列上 $x$ 到 $n$ 的位置都要修改。所以，我们需要一个数据结构来维护区间修改。

我们需要一个数据结构来维护结论 $1$。官方采用的方法是线段树，这里我采用分块。每个块记录维护 $\max\{s_l-b\times l,s_{l+1}-b\times(l+1),\dots,s_{r}-b\times r\}$。其中 $l,r$ 是块内两个端点。

若修改范围盖过了这个块，那么只需要给这个块打上懒标记。

如果修改范围与这个块有标记，那么就下传懒标记，重构这个块。

至于查询，我们先暴力从左往右跳每个块，当查到某个块维护的最大值大于等于 $0$，那么就从左往右查询这个块内的每一个信息是否大于等于 $0$。

如果没有一个块维护的最大值大于 $0$，那么就输出 $\frac{s_n}{n}$ 即可。

### 代码如下：

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=5e5+10;
const int M=1e3+10;
ll B;
#define wh(x) ((x-1)/B)
struct node{ll mx,laz;}Block[M];
ll s[N],a[N];
int n,q;
ll b;
void change(int l,int r,ll z){
	if(wh(l)==wh(r)){
		for(int i=l;i<=r;i++)
			s[i]+=z;
		Block[wh(l)].mx=-1e18;
		for(int i=wh(l)*B+1;i<=min(int((wh(l)+1)*B),n);i++){
			s[i]+=Block[wh(l)].laz;
			Block[wh(l)].mx=max(Block[wh(l)].mx,s[i]-b*i);
		}Block[wh(l)].laz=0;
	}else{
		int L=l,R=r;
		while(wh(L)==wh(l)) L++;
		while(wh(R)==wh(r)) R--;
		for(int i=l;i<L;i++) s[i]+=z;
		for(int i=R+1;i<=r;i++) s[i]+=z;
		Block[wh(l)].mx=-1e18;Block[wh(r)].mx=-1e18;
		for(int i=wh(l)*B+1;i<=min(int((wh(l)+1)*B),n);i++){
			s[i]+=Block[wh(l)].laz;
			Block[wh(l)].mx=max(Block[wh(l)].mx,s[i]-b*i);
		}for(int i=wh(r)*B+1;i<=min(int((wh(r)+1)*B),n);i++){
			s[i]+=Block[wh(r)].laz;
			Block[wh(r)].mx=max(Block[wh(r)].mx,s[i]-b*i);
		}Block[wh(l)].laz=0;Block[wh(r)].laz=0;
		for(int i=wh(L);i<=wh(R);i++) Block[i].laz+=z;
	}
}
int main(){
	scanf("%d%lld%d",&n,&b,&q);B=500;
	for(int i=0;i<=wh(n);i++) Block[i].mx=-1e18;
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);s[i]=a[i]+s[i-1];
		Block[wh(i)].mx=max(Block[wh(i)].mx,s[i]-b*i);
	}
	while(q--){
		int x;ll y;scanf("%d%lld",&x,&y);
		change(x,n,y-a[x]);a[x]=y;
		bool flag=false;int pos=0;
		for(int i=0;i<=wh(n);i++)
			if(Block[i].mx+Block[i].laz>=0){
				flag=true;pos=i;
				break;
			}
		if(!flag){cout<<fixed<<setprecision(15)<<1.0*(s[n]+Block[wh(n)].laz)/n<<'\n';}
		else{
			for(int i=pos*B+1;i<=min(int((pos+1)*B),n);i++)
				if(s[i]+Block[pos].laz-i*b>=0){
					cout<<fixed<<setprecision(15)<<1.0*(s[i]+Block[pos].laz)/i<<'\n';
					break;
				}
		}
	}return 0;
}
```

时间复杂度：$O(n\sqrt n)$。

---

## 作者：_Wind_Leaves_ShaDow_ (赞：0)

比较简单的题。

平均分可以往总分去靠，两边同时乘以场数就会变成总分的比较。

若停止计算时是第 $i$ 场比赛，当且仅当对于任意 $j<i$，$\sum_{k=1}^{j}a_k<B\times j$ 且 $\sum_{k=1}^{i}a_k\ge B\times i$。

如果可以动态维护这个东西就能用线段树二分找出来第一个满足的位置。

上面的式子移项会得到 $\sum_{k=1}^ja_k-B\times j<0$ 和 $\sum_{k=1}^ia_k-B\times i\ge 0$，左边仍然很好维护，右边变成常数方便查找。

考虑维护 $c_i$ 表示 $\sum_{j=1}^{i}a_j-B\times i$ 的线段树，那么单点修改转为区间加，查询变为寻找第一个非负数的位置。

就做完了。感觉没有蓝，都是很典的 tricks。

```cpp
#include <bits/stdc++.h>
#define int long long
#define Rg register
#define Ri Rg int
#define Il inline
#define vec vector
#define pb push_back
#define fi first
#define se second
#define IT ::iterator

using namespace std;

typedef double db;
typedef pair<int,int> pii;
const int N=5e5,Inf=1e9;
const db eps=1e-8,pi=acos(-1.0);

int n,bb,Q,a[N+5],b[N+5];
int sg[(N<<2)+5],tg[(N<<2)+5];

Il void build(int l,int r,int p){
	sg[p]=b[l];
	if(l==r)return;int mid=(l+r)>>1;
	build(l,mid,p<<1),build(mid+1,r,p<<1|1);
	sg[p]=max(sg[p<<1],sg[p<<1|1]);
	return;
}

Il void pown(int p){
	sg[p<<1]+=tg[p],sg[p<<1|1]+=tg[p];
	tg[p<<1]+=tg[p],tg[p<<1|1]+=tg[p];
	tg[p]=0;return;
} 

Il void add(int ql,int qr,int l,int r,int p,int x){
	if(ql<=l&&r<=qr){sg[p]+=x,tg[p]+=x;return;}
	int mid=(l+r)>>1;pown(p);
	if(ql<=mid)add(ql,qr,l,mid,p<<1,x);
	if(qr>mid)add(ql,qr,mid+1,r,p<<1|1,x);
	sg[p]=max(sg[p<<1],sg[p<<1|1]);
	return;
}

Il db find(int l,int r,int p){
	if(l==r)return 1.0*(bb*l+sg[p])/l;
	int mid=(l+r)>>1;pown(p);
	return (sg[p<<1]>=0?find(l,mid,p<<1):find(mid+1,r,p<<1|1));
}

signed main(){
//	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	scanf("%lld%lld%lld",&n,&bb,&Q);
	for(Ri i=1,sm=0;i<=n;i++){
		scanf("%lld",&a[i]);sm+=a[i];
		b[i]=sm-bb*i;
	}
	build(1,n,1);
	while(Q--){
		int c,x;scanf("%lld%lld",&c,&x);add(c,n,1,n,1,x-a[c]);
		a[c]=x;printf("%.9f\n",find(1,n,1));
	}
	return 0;
}
```

---

