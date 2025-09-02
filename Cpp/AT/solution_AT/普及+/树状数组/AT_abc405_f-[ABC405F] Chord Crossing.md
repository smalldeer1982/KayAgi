# [ABC405F] Chord Crossing

## 题目描述

在一个圆上等距分布着 $2N$ 个点，顺时针编号为 $1,2,\cdots,2N$。$2N$ 顺时针方向的下一个点是 $1$。

接下来圆上出现了 $M$ 条线段，第 $i$ 条线段的两个端点分别为 $A_i$ 和 $B_i$，并且**这两个端点的编号是偶数**。保证不会有两条线段共享一个端点。

接下来你要回答 $Q$ 个询问，每次询问给出**两个奇数** $C_j,D_j$，你要回答如果圆上新增了一条线段，两个端点分别是 $C_j,D_j$，那么这条新线段会和原有的 $M$ 条线段中的多少条相交。

## 说明/提示

**样例 1 解释**

如下图：

![](https://img.atcoder.jp/abc405/7f9b7b9c988c95df92d0a5919a865fcc.png)

黑点表示圆上的 $2N$ 个点，蓝线为 $M$ 条线段，第 $i$ 条称线段 $i$；红线表示询问，第 $i$ 个对应的线段称询问 $i$。

- 第一次询问中，和询问 $1$ 相交的线段为线段 $1$；
- 第二次询问中，和询问 $2$ 相交的线段有线段 $1,2$；
- 第三次询问中，没有线段和询问 $3$ 相交。

By @[chenxi2009](/user/1020063)

## 样例 #1

### 输入

```
4 2
2 4
6 8
3
1 3
3 7
1 5```

### 输出

```
1
2
0```

## 样例 #2

### 输入

```
20 7
24 34
26 28
18 38
2 14
8 12
30 32
20 22
10
7 29
31 39
9 21
19 29
15 21
11 39
17 21
15 31
5 25
25 31```

### 输出

```
3
3
4
1
2
2
2
3
3
1```

# 题解

## 作者：_anll_ (赞：24)

不会 e 但会这道，嘻嘻。

## 思路
要与 $(l,r)$ 这样的虚线产生交点，那么实线的两端应该分开在 $[l+1,r-1]$ 和 $[1,l-1],[r+1,n]$。理论上来说在前者或后者中查找另一个都可以，但是后者有两个区间不太好做，所以我们做前者。

具体地，对于每条实线的 $(a,b)$，我们都在 $a$ 上打 $b$ 的标记，再在 $b$ 上打 $a$ 的标记，即 $num_a=b,num_b=a$。因为每个点都至多会成为一条实线的端点，所以不必担心重复。于是问题转换成对于 $(l,r)$，查询区间 $[l+1,r-1]$ 中，有多少 $i$ 满足 $1\le num_i \le l-1$ 或 $r+1\le num_i \le n$。

于是转换成主席树板子，[附 AC 记录](https://atcoder.jp/contests/abc405/submissions/65720254)。

## 代码
```cpp
#include<iostream>
#include<algorithm>
#define lc(p) tr[p].son[0]
#define rc(p) tr[p].son[1]
#define mid (tr[p].l+tr[p].r)/2
using namespace std;
const int N=4e5+5;
struct L{int l,r;}lin[N];
struct Tr{int l,r,sum,son[2];}tr[N*32];
int n,m,q,tid,px[N],num[N],rt[N];
void build(int l,int r,int p){
	tr[p]={l,r};if(l==r) return;
	lc(p)=++tid;build(l,mid,lc(p));
	rc(p)=++tid;build(mid+1,r,rc(p));
}
void pushup(int p,int l=0,int r=0){
	tr[p].sum=tr[lc(p)].sum+tr[rc(p)].sum;
}
void update(int a,int p,int lp){
	tr[p]=tr[lp];
	if(tr[p].l==tr[p].r)
		return void(tr[p].sum+=1);
	if(a<=mid){
		lc(p)=++tid;
        update(a,lc(p),lc(lp));
	}
	else{
		rc(p)=++tid;
        update(a,rc(p),rc(lp));
	}
	pushup(p);
}
int Find_min(int p,int lp,int k){
	if(tr[p].r<=k) return tr[p].sum-tr[lp].sum;
	if(mid<k) return Find_min(lc(p),lc(lp),k)+Find_min(rc(p),rc(lp),k);
	return Find_min(lc(p),lc(lp),k);
}
int Find_max(int p,int lp,int k){
	if(tr[p].l>=k) return tr[p].sum-tr[lp].sum;
	if(mid>=k) return Find_max(lc(p),lc(lp),k)+Find_max(rc(p),rc(lp),k);
	return Find_max(rc(p),rc(lp),k);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;int l,r;
	for(int i=1;i<=m;i++){
		cin>>l>>r;lin[i]={l,r};
		px[i]=l,px[i+m]=r;
	}
	sort(px+1,px+1+2*m);
	int len=unique(px+1,px+1+2*m)-px-1;
	for(int i=1;i<=m;i++){
		lin[i].l=lower_bound(px+1,px+1+len,lin[i].l)-px;
		lin[i].r=lower_bound(px+1,px+1+len,lin[i].r)-px;
		num[lin[i].l]=lin[i].r,num[lin[i].r]=lin[i].l;
	}
	rt[0]=++tid;build(1,len,1);
	for(int i=1;i<=len;i++){
		rt[i]=++tid;update(num[i],rt[i],rt[i-1]);
	}
	cin>>q;
	while(q--){
		cin>>l>>r;
		l=lower_bound(px+1,px+1+len,l)-px;
		r=lower_bound(px+1,px+1+len,r)-px-1;
		int an1=0,an2=0;
		if(l-1>0) an1=Find_min(rt[r],rt[l-1],l-1);
		if(r+1<=len) an2=Find_max(rt[r],rt[l-1],r+1);
		cout<<an1+an2<<endl;
	}
	return 0;
} 
```

---

## 作者：_Weslie_ (赞：1)

赛时发明离线二位数点？

## Solution AT_abc405_f

### Idea

首先转化：两条线段 $(a,b)$（其中 $a<b$）和 $(c,d)$（其中 $c<d$）相交的充要条件是 $a<c<b<d$ 或 $c<a<d<b$。

在线在我的认知水平中是不可做。我们试试离线。当然应该也有更高级的做法支持在线，但是没有离线简单就是了。

接下来设 $al_i$ 和 $ar_i$ 为第 $i$ 条询问线段的左端点和右端点，$bl_i$ 和 $br_i$ 为第 $i$ 条原始线段的左右端点。

先考虑 $al<bl<ar<br$。

首先对原线段数组 $b$ 和询问数组 $a$ 排序。怎么排序呢？我们尝试按照右端点从大到小排序（左端点任意，为了方便我们也从小到大）。所以这时 $r$ 是单减的。

双指针 $i$ 枚举 $a$，$j$ 枚举 $b$，保证 $br_j>ar_i$。不难发现 $i$ 和 $j$ 都单调不降。

对每一个枚举到的 $b$ 区间，我们在 $bl$ 上记录答案。

接下来我们只需要求 $[al_i,ar_i]$ 区间的标记和，它就是满足 $al<bl<ar$ 的个数。再加之 $br>ar$，则条件符合。单点加区间和，这个树状数组就能办。不用写线段树。

还有另外一种情况：$bl<al<br<ar$。

也差不多。我们把 $a$ 和 $b$ 都按照左端点从小到大排序，双指针 $i$ 和 $j$ 分别枚举 $a$ 和 $b$，保证 $bl_{j}<al_{i}$。然后在 $br_j$ 上标记答案，求 $[al_{i},ar_i]$ 的区间和。

最后因为离线，记录一个 $id$，保证输出答案顺序正确。

### Code

```
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
struct node{
    int l,r,id;
}a[N],b[N];
vector<int>g[N*10];
int pos[N*10];
int tr[N*10],n,m;
int lowbit(int x){
    return x&(-x);
}
void add(int now,int x){
    while(now<N*10){
        tr[now]+=x;
        now+=lowbit(now);
    }
}
int query(int now){
    int res=0;
    while(now){
        res+=tr[now];
        now-=lowbit(now);
    }
    return res;
}
bool cmp1(node _,node __){
    if(_.r>__.r)return 1;
    if(_.r==__.r&&_.l>__.l)return 1;
    return 0;
}
bool cmp2(node _,node __){
    if(_.l<__.l)return 1;
    if(_.l==__.l&&_.r<__.r)return 1;
    return 0;
}
int ans[N],p;
int main(){
    scanf("%d%d",&n,&p);
    for(int i=1,l,r;i<=p;i++){
        scanf("%d%d",&b[i].l,&b[i].r);
    }
    sort(b+1,b+p+1,cmp1);
    scanf("%d",&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&a[i].l,&a[i].r);
        a[i].id=i;
    }
    sort(a+1,a+m+1,cmp1);
    int cnt=0;
    for(int i=1,j=0;i<=m;i++){
        while(j<p&&b[1+j].r>=a[i].r){
            j++;
            add(b[j].l,1);
        }
        ans[a[i].id]+=query(a[i].r)-query(a[i].l);
    }
    sort(a+1,a+m+1,cmp2);
    sort(b+1,b+p+1,cmp2);
    for(int i=1;i<=n*2;i++)tr[i]=0;
    for(int i=1,j=0;i<=m;i++){
        while(j<p&&b[j+1].l<=a[i].l){
            j++;
            add(b[j].r,1);
        }
        ans[a[i].id]+=query(a[i].r)-query(a[i].l);
    }
    for(int i=1;i<=m;i++)printf("%d\n",ans[i]);
}
```

---

## 作者：littlebug (赞：1)

## Solution

注意到 $c_j,d_j$ 一定不会与 $a_i,b_i$ 重合，所以问题可以转化为给定 $m$ 条线段，每次询问求在区间 $[c_j,d_j]$ 内有几条线段**仅有一个端点**在区间内。

考虑先把所有在区间内部的端点个数算出来，然后再减去被区间包含的线段的端点。

显然区间内部的端点个数用前缀和就能 $\mathcal O(n)$ 算出来。

注意到一个线段被区间包含当且仅当 $a_i > l_j , b_i < r_j$，很好想到枚举一个端点，另一个用个什么东西区维护。具体地，可以先把询问离线下来并排序，按照 $a_i$ 从右到左枚举每条线段，每次处理 $a_i < l_j < a_{i-1}$ 的区间，这样只需要知道 $<r_i$ 的 $b_i$ 个数即可，显然可以 BIT 维护前缀和 $\mathcal O(n \log n)$ 做。

总复杂度是 $\mathcal O(n \log n)$。

## Code

```cpp
int n,m,c[N<<1],dif[N<<1],Q;
pii a[M];
struct query{int l,r,id;} q[M];
int ans[M];

struct __BIT
{
    int v[N<<1];
    il void upd(int pos,int k) {for(int i=pos;i<=(n<<1|1);v[i]+=k,i+=(i&-i));}
    il int q(int pos) {int res=0; for(int i=pos;i;res+=v[i],i-=(i&-i)); return res;}
    il void clear() {rep(i,0,n+1) v[i]=0;}
} tr;

il void solve()
{
    read(n,m),_::r(a,m);
    sort(a+1,a+m+1);
    
    rep(i,1,m) ++dif[a[i].st],++dif[a[i].nd];
    int _s=0;
    rep(i,1,n<<1) _s+=dif[i],c[i]=_s;

    read(Q); rep(i,1,Q) read(q[i].l,q[i].r),q[i].id=i,ans[i]=c[q[i].r]-c[q[i].l-1];
    sort(q+1,q+Q+1,[](const auto a,const auto b){return a.l<b.l;});

    a[m+1].st=inf;
    int pos=Q;
    rpe(i,m,1)
    {
        while(pos>=1 && a[i].st+1<=q[pos].l && q[pos].l<=a[i+1].st-1) ans[q[pos].id]-=tr.q(q[pos].r)<<1,--pos;
        tr.upd(a[i].nd,1);
    }
    while(pos>=1) ans[q[pos].id]-=tr.q(q[pos].r)<<1,--pos;

    rep(i,1,Q) write(ans[i],'\n');
}
```

---

华风夏韵，洛水天依！

---

## 作者：Crazyouth (赞：1)

## 分析

前面一位题解老哥怎么是主席树，这题我写的二位数点。

我们有 $a_i<b_i$，$c_j<d_j$，所以两个线段相交等价于 $a_i$ 在 $[c_j,d_j]$ 但是 $b_i$ 不在或者反过来，那么我们把每个 $[a_i,b_i]$ 看做一个点，询问就是 $[c_j,d_j]\times [1,c_j]$ 矩形和 $[c_j,d_j]\times [d_j,2n]$ 矩形，这样一来差分一下就变成很普通的二维数点了，具体的可以看代码。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,t[2000010];
struct point
{
	int x,y;
}p[200010];
map<pair<int,pair<int,int>>,int> mp;
struct query
{
	int p,q,id; 
}qry[200010];
struct rquery
{
	int x,ya,yb;
}rqry[600010];
void upd(int k,int c)
{
	while(k<=n)
	{
		t[k]+=c;
		k+=k&-k;
	}
}
int qsum(int k)
{
	int ret=0;
	while(k)
	{
		ret+=t[k];
		k-=k&-k;
	}
	return ret;
}
int main()
{
	int m;
	cin>>n>>m;
	n<<=1;
	for(int i=1;i<=m;i++)
	{
		cin>>p[i].x>>p[i].y;
		if(p[i].x>p[i].y) swap(p[i].x,p[i].y);
	}
	sort(p+1,p+m+1,[](point i,point j){return i.x<j.x;});
	int q,cnt=0;
	cin>>q;
	for(int i=1;i<=q;i++)
	{
		cin>>qry[i].p>>qry[i].q;
		qry[i].id=i;
		if(qry[i].p>qry[i].q) swap(qry[i].p,qry[i].q);
		rqry[++cnt]={qry[i].q,qry[i].q,n};
		rqry[++cnt]={qry[i].p,qry[i].q,n};
		rqry[++cnt]={qry[i].p,qry[i].p,qry[i].q};
	}
	sort(rqry+1,rqry+cnt+1,[](rquery i,rquery j){return i.x<j.x;});
	int pt=1;
	for(int i=1;i<=cnt;i++)
	{
		while(pt<=m&&p[pt].x<=rqry[i].x)
		{
			upd(p[pt].y,1);
			pt++;
		}
		mp[{rqry[i].x,{rqry[i].ya,rqry[i].yb}}]=qsum(rqry[i].yb)-qsum(rqry[i].ya);
	}
	for(int i=1;i<=q;i++) cout<<mp[{qry[i].q,{qry[i].q,n}}]-mp[{qry[i].p,{qry[i].q,n}}]+mp[{qry[i].p,{qry[i].p,qry[i].q}}]<<'\n';
}

---

## 作者：Jenny_yu (赞：0)

题外话，因为做过类似题目又轻视了数据范围，赛时用莫队导致超过了时限。当然如果数据范围再小一点的话莫队也是很好的做法。

本题考虑使用树状数组。

对于一条线段，如果它的左端点或右端点在某一线段内，但两端点并不同时出现在这条线段内，则两个线段相交。

拆环为链，从左到右处理。将 $M$ 条线按左端点排序，每条线段的右端点加入树状数组。

先不考虑两端点同时出现在某一条线段内的情况。设某条要查询线段区间为 $[l,r]$，处理到 $l$ 的时候，对答案有贡献的为在 $l$ 右侧的树状数组种的右端点，因为其左端点一定小于 $l$。对于 $r$ 同理。

现在考虑两端点同时出现在某一条线段内的情况。在处理到 $l$ 的时候，对于 $r$ 右侧的树状数组内的右端点是非合法情况，可以顺便处理掉。因为处理到 $l$ 和 $r$ 时这些非合法情况都算进去了，因此要减去两次。


```cpp
#include <bits/stdc++.h>
using namespace std;
struct dat{
	int y,z,id;
};
vector<dat> v[2000010];
int tr[2000010],que[200010];
int n,m;
void add(int x,int y){
	for(; x <= 2 * n; x += (x & -x))tr[x] += y;
}
int sum(int x){
	int res = 0;
	for(; x; x -= (x & -x))res += tr[x];
	return res;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1; i <= m; i++){
		int x,y;
		scanf("%d%d",&x,&y);
		v[x].push_back({y,0,0});
	}
	int q;
	scanf("%d",&q);
	for(int i = 1; i <= q; i++){
		int x,y;
		scanf("%d%d",&x,&y);
		v[x].push_back({x,1,i});
		v[x].push_back({y,-2,i});
		v[y].push_back({y,1,i});
	}
	int tot = 0;
	for(int i = 1; i <= 2 * n; i++){
		if(i % 2){
			for(int j = 0; j < v[i].size(); j++){
				int y = v[i][j].y,z = v[i][j].z,id = v[i][j].id;
				que[id] += z * (tot - sum(y));
				//tot是已经加入的总点数，sum(y)是在y左侧的点数，tot-sum(y)就是在y右侧的点数。
			}
		}else{
			for(int j = 0; j < v[i].size(); j++){
				int y = v[i][j].y,z = v[i][j].z,id = v[i][j].id;
				tot++;
				add(y,1);
			}
		}
	}
	for(int i = 1; i <= q; i++){
		printf("%d\n",que[i]);
	}
	return 0;
}
```

---

## 作者：cwd2023 (赞：0)

### AT_abc405_f 题解


---


by cwd2023


---

首先，经典地，拆环成链。不难发现，如果一条虚线与一条实线相交，那么在链上他们对应的两条线段相交。

但当两条线段重合时要注意，它们在环上是不相交的，不能计入答案。

所以可以通过树状数组快速求左端点在原始线段两个端点左边，右端点在其两个端点右边的线段数量，最后减去二倍的特殊情况数量。具体看代码。


---


### code
#### 注释版
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#ifndef Debug
#define debug
#endif
ll n,m,q,cur;//cur是原是线段总数
struct N{
    ll en,op,id;//op是计入答案的次数
};
vector<N>e[2000010];
ll ans[200010],tr[2000010];
inline void add(ll x,ll k){
    for(;x<=n;x+=(x&(-x)))tr[x]+=k;
}
inline ll ask(ll x,ll y=0){
    for(;x>0;x-=(x&(-x)))y+=tr[x];
    return y;
}
int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin>>n>>m,n*=2;
    for(ll i=1,x,y;i<=m;i++)
        cin>>x>>y,e[x].push_back({y,0,0});
    cin>>q;
    for(ll i=1,x,y;i<=q;i++){
        cin>>x>>y;
        e[x].push_back({x,1,i});
        e[y].push_back({y,1,i});
        e[x].push_back({y,-2,i});//特殊情况减2次
    }
    for(ll i=1;i<=n;i++){//按左端点先后顺序插入vector
        if(i&1)
            for(auto k:e[i])
                ans[k.id]+=(cur-ask(k.en))*k.op;
//总数减去树状数组中查出的右端点在原始线段右端点右边的线段数。
        else for(auto k:e[i])add(k.en,1),cur++;
    }
    for(ll i=1;i<=q;i++)cout<<ans[i]<<"\n";
    return 0;
}

```

#### 无注释
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#ifndef Debug
#define debug
#endif
ll n,m,q,cur;
struct N{
    ll en,op,id;
};
vector<N>e[2000010];
ll ans[200010],tr[2000010];
inline void add(ll x,ll k){
    for(;x<=n;x+=(x&(-x)))tr[x]+=k;
}
inline ll ask(ll x,ll y=0){
    for(;x>0;x-=(x&(-x)))y+=tr[x];
    return y;
}
int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin>>n>>m,n*=2;
    for(ll i=1,x,y;i<=m;i++)
        cin>>x>>y,e[x].push_back({y,0,0});
    cin>>q;
    for(ll i=1,x,y;i<=q;i++){
        cin>>x>>y;
        e[x].push_back({x,1,i});
        e[y].push_back({y,1,i});
        e[x].push_back({y,-2,i});
    }
    for(ll i=1;i<=n;i++){
        if(i&1)
            for(auto k:e[i])
                ans[k.id]+=(cur-ask(k.en))*k.op;
        else for(auto k:e[i])add(k.en,1),cur++;
        
    }
    for(ll i=1;i<=q;i++)cout<<ans[i]<<"\n";
    return 0;
}
```
最后，希望本篇题解对你有所帮助，感谢观看。

**望管理员通过！**

---

## 作者：fanminghao000 (赞：0)

## 题解

两线产生交点的充要条件是一线两端点分居另一线分割成的两段圆弧上，形式化地，设偶数连线 $x$ 与奇数连线 $y$ 相交，即：

$$
c_y<a_x<d_y<b_x \space \texttt{或}\space a_x<c_y<b_x<d_y
$$

如果固定住偶数连线 $x$，则某一条奇数连线的起点 $c_y<a_x$，若终点 $d_y \in (a_x,b_x)$ 则产生一次贡献。同理可以转化第二个式子：若起点 $a_x<c_y<b_x$，则 $d_y \in (b_x,2n)$ 时产生一次贡献。

考虑将查询离线，让查询的奇数连线以 $c_i$ 为关键字排序。

如何查询？可以用类似扫描线的方法维护。对于式 1，看作每段 $(a_x,b_x)$ 的值为 1，式 2 则看作 $(b_x,2n)$ 的值为 1，则直接查询 $t_{d_i}$ 的值即可。因此是区间修改、单点查询，用线段树 / 树状数组 + 差分维护即可。如果用树状数组 + 差分的话，修改如下：

$$
i=0:t_{a_x}+=1,t_{b_x+1}-=1
\\
i=a_x:t_{a_x}-=1,t_{b_x+1}+=2
\\
i=b_x:t_{b_x+1}-=1
$$

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m,q;
vector<pair<int,int> > a[2000100];
map<pair<int,int> ,int> mp;
vector<pair<int,int> > b,b1;
int t[2000100];
int lowbit(int x){return x&-x;}
void add(int x,int val){for(;x<=n*2;x+=lowbit(x))t[x]+=val;}
int query(int x){int ret=0;for(;x;x-=lowbit(x))ret+=t[x];return ret;}
int main(){
  ios::sync_with_stdio(0);
  cin>>n>>m;
  for(int i=1;i<=m;i++){
    int u,v;cin>>u>>v;
    a[u].emplace_back(v+1,2);  
    a[u].emplace_back(u,-1);
    a[v+1].emplace_back(v+1,-1);//记录修改值和位置，备用
    add(u,1),add(v+1,-1);
  }
  cin>>q;
  for(int i=1;i<=q;i++){
    int c,d;cin>>c>>d;
    b.push_back(make_pair(c,d));
    b1.push_back(make_pair(c,d));
  }
  sort(b.begin(),b.end());
  int lst=0;
  for(auto [c,d]:b){
    while(lst<=c){//扫描线修改
      for(auto [pos,val]:a[lst]) add(pos,val);
      lst++;
    }
    mp[make_pair(c,d)]=query(d);//统计答案
  }
  for(int i=1;i<=q;i++) cout<<mp[b1[i-1]]<<endl;
  return 0;
}
```

---

