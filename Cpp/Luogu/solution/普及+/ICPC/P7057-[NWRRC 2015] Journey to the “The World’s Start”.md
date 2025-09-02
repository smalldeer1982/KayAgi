# [NWRRC 2015] Journey to the “The World’s Start”

## 题目描述

Jerry Prince 是一名四年级学生，他去 New-Lodnon 参观最受欢迎的游乐园 "The World's Start"。

他到达的机场就在地铁线的第一站旁边。这条地铁线有 $n$ 个站点，"The World's Start" 位于最后一个站点。New-Lodnon 的地铁非常快，所以你可以假设从一个站到下一个站只需要一分钟。

Jerry 需要一张地铁通行卡才能使用地铁。每张通行卡都有一个范围 $r$ 和一个价格 $p$。使用范围为 $r$ 的通行卡，Jerry 一次最多可以旅行 $r$ 个站。因此，如果 Jerry 在第 $i$ 个站进入地铁，他应该在从 $i - r$ 到 $i + r$ 的某个站点下车。需要 $d_{i}$ 分钟才能在第 $i$ 个站点下车并重新进入地铁。在第一站进入或最后一站下车不需要时间。

Jerry 不是很富有，但他有一些空闲时间，所以他决定购买最便宜的通行卡，使他能够在不超过 $t$ 分钟的时间内从第一站旅行到最后一站。

## 说明/提示

时间限制：2 秒，内存限制：256 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4 4
1 2 3
1 4
```

### 输出

```
2
```

# 题解

## 作者：Your_Name (赞：2)

## 题解
首先，考虑一个事实，即当一个 $r$ 满足条件时，那么比他大的所有车票也一定满足条件。证明显然，因为大的票本来就严格包含小的票，即可以当小的用且所用时间可能更优。由此，单调性有了，那么就可以二分了。

然后，题目说可以往回走，其实显然是不优的，于是我们设计一个显然的 dp。

设 $f_i$ 表示经过前面 $i - 1$ 个星球到 $i$ 这个星球的最小花费。

转移：
$$
f_i=d_i+\min_{j=\max(0,i-x)}^{i-1}f_j
$$
发现本质上还是滑动窗口，直接单调队列解决。

注意，他会把 $n$ 个星球都走一遍，时间最少也要 $n-1$，所以我们一开始把他减掉就行。 
## AC_Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 5e4 + 10;
LL n, a[N], w[N], t, ans = 1e18, f[N];
deque<LL>q;
bool check(LL x){
    q.clear();
    q.push_back(1);
    for(LL i = 2; i <= n; i ++){
        while(!q.empty() && q.front() < i - x)q.pop_front();
        f[i] = f[q.front()] + w[i];
        while(!q.empty() && f[q.back()] >= f[i])q.pop_back();
        q.push_back(i);
    }
    return f[n] <= t;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> t;
    t -= n - 1;
    for(LL i = 1; i < n; i ++){
        cin >> a[i];
    }
    for(LL i = 2; i < n; i ++){
        cin >> w[i];
    }
    LL l = 1, r = n - 1, mid;
    while(l < r){
        mid = l + r >> 1;
        if(check(mid))r = mid;
        else l = mid + 1;
    }//二分第一个满足条件的
    for(LL i = l; i < n; i ++){
        ans = min(ans, a[i]);
    }//后面都满足条件
    cout << ans;
    return 0;
}
```
 _完结撒花。_

---

## 作者：AFewSuns (赞：2)

upd 2023.12.28：修改了一处代码错误。

---

线段树优化 dp。

### 题目大意

你要从第 $1$ 个点坐地铁到第 $n$ 个点，有 $n-1$ 张车票，每一张车票的乘车范围为 $r_i=i$，并且有价格 $p_i$。乘车范围 $r_i$ 表示你能从 $i$ 点坐到 $[i-r_i,i+r_i]$ 内的点下车（不越界），然后再上车。

在第 $i$ 个点下车的所花时间是 $d_i$，第 $1$ 和 $n$ 个点下车不花时间，从一个点坐到另一个点需要 $1$ 单位时间（如果 $1$ 坐到 $4$，需要 $3$ 单位时间）。你需要在 $t$ 时间内到达 $n$，且**只能用一种车票**（**可以用无数次**），求车票费用最小值。

例如样例就是选择了 $r_i=2$ 的车票，然后 $1 \rightarrow 2 \rightarrow 4$ 即可。

### 题目分析

如果要从 $1$ 坐到 $n$，则无论如何都要 $n-1$ 单位时间，所以先让 $t$ 减去 $n-1$。

有个很明显的单调性，就是如果 $r_k$ 这个范围的车票可行，那么 $[r_k,n-1]$ 范围的车票都可行。

所以只用找出来最小满足条件的 $r_k$，那么 $[r_k,n-1]$ 都可行，答案便是 $\displaystyle\min_{i=k}^{n-1}{p_i}$。

这个东西可以用二分找，现在的关键便是如何求第 $k$ 张车票的最短时间。

假设目前用的是第 $k$ 张车票，范围是 $r_k=k$。

首先我只能坐地铁到后面的点，不然肯定不优。

然后开始想各种各样的贪心，发现都是错的（有兴趣的可以试一下能不能做）。于是开始想如何 dp。

设 $f_i$ 为在 $i$ 点下车的答案（最小值）。

根据前面的条件， $f_i=\displaystyle\min_{j=\max(1,i-k)}^{i-1}f_j+d_i$，然后 $f_n$ 即为所求。

如果我们暴力求解，这样时间是 $O(n^2)$ 的，带上二分变成了 $O(n^2\log n)$，会 T 掉。

观察式子，极其简单，只有一个区间求 $\min$，用线段树优化一下就行了。

时间复杂度 $O(n\log ^2n)$。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define LC x<<1
#define RC x<<1|1
using namespace std;
ll n,t,p[50050],d[50050],f[50050],tree[200020],ans=8e18;
void pushup(ll x){
	tree[x]=min(tree[LC],tree[RC]);
}
void mdf(ll x,ll l,ll r,ll pos,ll v){
	if(l==r){
		tree[x]=v;
		return;
	}
	ll mid=(l+r)>>1;
	if(pos<=mid) mdf(LC,l,mid,pos,v);
	else mdf(RC,mid+1,r,pos,v);
	pushup(x);
}
ll query(ll x,ll l,ll r,ll ql,ll qr){
	if(ql<=l&&r<=qr) return tree[x];
	ll mid=(l+r)>>1,res=8e18;
	if(ql<=mid) res=min(res,query(LC,l,mid,ql,qr));
	if(mid<qr) res=min(res,query(RC,mid+1,r,ql,qr));
	return res;
}
bool chk(ll k){
	for(ll i=2;i<=n;i++){
		f[i]=query(1,1,n,max(1ll,i-k),i-1)+d[i];
		mdf(1,1,n,i,f[i]);
	}
	return f[n]<=t;
}
int main(){
	scanf("%lld %lld",&n,&t);
	t-=n-1;
	for(ll i=1;i<n;i++) scanf("%lld",&p[i]);
	for(ll i=2;i<n;i++) scanf("%lld",&d[i]);
	ll l=1,r=n-1;
	while(l<r){
		ll mid=(l+r)>>1;
		if(chk(mid)) r=mid;
		else l=mid+1;
	}
	for(ll i=l;i<n;i++) ans=min(ans,p[i]);
	printf("%lld",ans);
}
```

---

## 作者：G1yu (赞：0)

## [P7057](https://www.luogu.com.cn/problem/P7057) 题解

### 题意

题意很简单，但是翻译不好。一共有 $n$ 个地铁站和 $n-1$  张地铁票，第 $i$ 张地铁票有价格 $p_i$ 和范围 $r_i(r_i = i)$。购买后能无限次地使用。假设你当前在 $k$ 站，每一次使用能让你到 $[k-r_i,k+r_i]$ 这个区间内的任意一站，从一个车站坐到另一个车站需要花费 $1$ 的时间，每一次在 $i+1$ 号车站换乘需要耗费 $d_i$ 的时间（在 $1$ 号车站和 $n$ 闹车站下车不耗时），使用过地铁票后，只有换乘后才能再次使用地铁票。问在从 $1$ 号地铁站坐到 $n$ 号地铁站总耗时不超过 $t$ 的情况下，**只能买一种车票**，求车票费用最小值。

###  思路

我们注意到，如果使用第 $k$ 张车票有一种路径符合要求，那么后面的 $i\sim n-1$ 张车票都能走出这条路径，都符合要求，答案是 $\min \limits^{n-1}_{i=k}p_i$ 。我们先不考虑价格，先求出来 $k$ 值。我们设使用第 $i$ 张车票走玩全程需要的时间为 $T_i$，不难得出，当 $r_i\le r_j$ 时，一定有 $T_i \ge T_j$ ，满足单调性。有了单调性，就能二分答案求出 $k$。

我们设到第 $i$ 站下车的最短时间为 $f_i$，我们有:
$$
f_i = \min\limits^{i-1}_{j=\max(1,i-k)} f_j+d_i
$$
 注意：$i-k$ 可能为负数所以与 $1$ 取更大的。

注意到我们只需要 $[\max(1,i-k),i-1]$ 的最小值即可，考虑线段树维护最小值，每处理完一个$f_i$ 就用其更新线段树。详细可看代码

### code

```cpp
#include<bits/stdc++.h>
#define ls num<<1
#define rs num<<1|1
#define mid ((l+r)>>1)
using namespace std;
const int N = 1e7+4;
typedef long long ll;
ll n,t;
ll p[N],d[N];
ll mn[N];
ll f[N];
void push_up(int num){
    mn[num] = min(mn[ls],mn[rs]);
}
void upd(int num,int l,int r,int tar,int v){
    if(tar<l||tar>r) return;
    if(l==r){mn[num]=v;return;}
    upd(ls,l,mid,tar,v);
    upd(rs,mid+1,r,tar,v);
    push_up(num);
}
ll query(int num,int l,int r,int L,int R){
    if(R<l||r<L) return 2e9;
    if(L<=l&&r<=R) return mn[num];
    return min(query(ls,l,mid,L,R),query(rs,mid+1,r,L,R));
} //线段树维护区间最小值

bool check(int x){
    for(int i=2;i<=n;i++){
        f[i]=query(1,1,n,max(1,i-x),i-1)+d[i];
		upd(1,1,n,i,f[i]);
    }
    return f[n] <= t;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin>>n>>t;t-=n-1;//注意：每走一个点都会消耗一分钟，我们的f[]是不包含这个的，所以一开始就要减去。
    for(int i=1;i<n;i++){
        cin>>p[i];
    }
    for(int i=2;i<n;i++){ 
        cin>>d[i];
    }
    int l=1,r=n-1;
    while(l<r){
        if(check(mid)) r= mid;
        else l =mid+1;       
    }
    ll ans = 2e9;
    for(int i=l;i<n;i++){
        ans = min(ans,p[i]);
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：Mason123456 (赞：0)

建议看讨论区的翻译。

### Sol

先不考虑价格，因为满足价格最小即可。

首先，如果第 $k$ 张票可以到达终点，那么必然满足所有 $ \ge k$ 的票都可以买。

> 证明：因为第 $k$ 张票可以买，所有 $\ge k$ 的票都可以在和第 $k$ 张票一样的位置下车，所以所有 $\ge k$ 的票都可以买。
>
> 证毕。

于是我们可以二分 $k$。

***

再来看如何检查 $k$ 可不可以买。

首先，我们发现，使用旅行卡时，往左坐车肯定是不优的。

> 证明：如果往左坐车是更优的，那么直接在上一站往左坐车的位置下车，可以更优。此时都是往右坐的。
>
> 证毕。

于是我们都往右坐车。假如要坐到第 $i$ 个位置，那么发现能到做一次车就到 $i$ 的位置是一段区间 $[i - k, i - 1]$，那么设计转移方程。令 $f_i$ 表示到 $i$ 位置的最小时间。于是有：
$$
f_i = \min_{j = i - k}^{i - 1} f_j + d_i
$$
及加上在 $i$ 换乘的时间。

由于区间长度是定的，所以可以用滑动窗口解决。当然也可以用线段树优化。

***

于是二分完 $k$ 后，取所有 $j \ge k$ 的 $p_j$（即价格）的最小值即可。

### 滑动窗口

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e4 + 5;
int n, t;
int p[N], d[N];
int que[N], hh = 1, tt = 0;
ll f[N];

bool check(int k){
	hh = 1, tt = 0;
	que[++tt] = 1;
	for(int i = 2;i <= n;i++){
		while(hh <= tt && que[hh] < i - k)	hh++;
		f[i] = f[que[hh]] + d[i];
		while(hh <= tt && f[que[tt]] >= f[i])	tt--;
		que[++tt] = i;
	}
	return f[n] <= t;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>n>>t;
	for(int i = 1;i < n;i++){
		cin>>p[i];
	}
	for(int i = 2;i < n;i++){
		cin>>d[i];
	}
	t -= n - 1;
	int l = 1, r = n - 1, ans = 0;
	while(l <= r){
		int mid = (l + r) >> 1;
		if(check(mid))	r = mid - 1, ans = mid;
		else	l = mid + 1;
	}
	int minn = p[ans];
	for(int i = ans;i < n;i++)	minn = min(minn, p[i]);
	cout<<minn<<"\n";
}
```

---

## 作者：_Flame_ (赞：0)

### solution

先让 $t$ 减去 $n-1$。

发现一个显然的性质，如果长度为 $r_i$ 的车票可行，那么比他大的都可以。

二分转化问题，如何求第 $x$ 张车票的最小时间。

设 $dp_i$ 为在 $i$ 点下车的最小时间。假设现在在用第 $x$ 张车票，明显有转移 $dp_i=\min\limits_{j=i-x}^{i-1}dp_j+d_i$。

区间求最小值，直接线段树优化。

注意转移的时候 $j$ 的范围下界要和 $1$ 取较大值。

---

## 作者：Hisaishi_Kanade (赞：0)

你假设已经找到了对于一张 $r_i=k$ 的票的最快路径？

那么对于 $r_j=k^\prime>k$ 显然由于 $i+k\le i+k^\prime$，他也可以复刻这条路径。所以根据这个结论，我们可以求出某个最小的 $r_i$ 使得其在 $t$ 时间内完成，答案是 $\min\limits_{j=i}^n p_j$。

考虑如何确定 $r=k$ 时的最小时间，这个则是比较简单的了。

一个明显正确的贪心是你不会往回跳。例如 $x\to y\to z(y<x<z)$，你这样不如 $x\to z$ 省事。所以在车上显然是花掉 $n-1$ 时间。

所以可以设计一个 dp，$f(i)$ 表示到达第 $i$ 点的时候下车的最小花费时间。

不难推出 $f(i)=d_i+\min\limits_{j=\max(i-k,1)}^{i-1} f(j)$。

这种东西单调队列维护就好了，复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for(i=l; i<=r; ++i)
#define req(i, r, l) for(i=r; i>=l; --i)
using namespace std;
using ll=long long;
static const int Buf_size=1<<25;
static char _c; static int _x;
static const signed int base_10=10, zero(48), nine(57), flag_signed(45);
static char buf[Buf_size], *p1=buf, *p2=buf;
#define digit() (zero<=_c&&_c<=nine)
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,Buf_size,stdin),p1==p2)?EOF:*p1++)
inline int read(){_x=0;_c=getchar();while(!digit()){_c=getchar();}while(digit()){_x=_x*10+(_c^zero);_c=getchar();}return _x;}
const int N=3e5+5, inf=2e9;
const ll illf=1e18;
int a[N], q[N], d[N], p[N]; ll f[N];
int l, r, res, ans, mid;
int qt, n, i, j, k, t;
inline const bool check(int k)
{
	int l, r;
	q[l=r=1]=1; f[1]=0;
	rep(i, 2, n)
	{
		while(l<=r && q[l]<i-k) ++l;
		f[i]=f[q[l]]+d[i];
		while(l<=r && f[q[r]]>f[i]) --r; q[++r]=i;
	}
	return f[n]<=t;
}
int main()
{
	n=read(); t=read(); t-=n-1;
	rep(i, 1, n-1) p[i]=read(); rep(i, 2, n-1) d[i]=read();
	l=1; r=n-1; while(l<=r)
	{
		mid=l+r>>1; if(check(mid)) ans=mid, r=mid-1;
		else l=mid+1;
	}
	res=inf; rep(i, ans, n-1) res=min(res, p[i]);
	printf("%d\n", res);
}
```

---

