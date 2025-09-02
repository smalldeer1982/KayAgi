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

## 作者：_anll_ (赞：39)

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

## 作者：cwd2023 (赞：5)

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

## 作者：_Weslie_ (赞：4)

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

## 作者：xuanfeng101 (赞：3)

## 思路
首先，我们需要分析两条直线相交的条件，由于题目给的是一个圆环，那么我们可以将圆环拆开来考虑，变成一条 $1$ 到 $2n$ 的数轴，那么两条直线相交不难发现就是两条直线**相交但不包含**，那么也就是说我们需要找到有多少满足 $1 \le a \le c$ 并且 $c \le b \le d$ 或者 $c \le a \le d$ 并且 $d \le b \le 2n$, 对于这种约束条件我们应该可以想到**二维数点**这一离线利器。

![](https://cdn.luogu.com.cn/upload/image_hosting/wmedl6oa.png)

如图，询问为红色正方形，那么可以转换为蓝 $-$ 绿 $-$ 橙 $+$ 黄色部分，这样就可以将询问拆成四个部分每次查询四次有多少个点在由 $(x, y) $ 与坐标原点组成的矩形内。

那么我们可以先按 $x$ 坐标排序，按**先修改再插叙**并且**边修改边查询**的策略对于 $y$ 轴建立一颗**权值树状数组**维护有多少点**小于等于**当前点纵坐标, 对于询问就查询到对应答案的贡献中对于点对就执行修改操作。

## 时间复杂度
$O((n + m)\log (n + m))$

## Code

```cpp
#include <bits/stdc++.h> 
using namespace std;
const int N = 2e6 + 10; //注意要开双倍N
int n, m;
int ans[N], s[N];
struct Node
{
	int x, y, id, k;
	bool operator< (const Node &w) const 
	{
		if (x == w.x) return id < w.id;
		return x < w.x;
	}
};
vector<Node> vec;

int lowbit(int x)
{
	return x & -x;
}

void add(int x, int k)
{
	for (int i = x; i < N; i += lowbit(i)) s[i] += k;
}

int ask(int x)
{
	int res = 0;
	for (int i = x; i; i -= lowbit(i)) res += s[i];
	return res;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	n *= 2;
	for (int i = 1; i <= m; i ++ )
	{
		int a, b;
		cin >> a >> b;
		vec.push_back({a, b, -1, 1});
	}
	cin >> m;
	for (int i = 1; i <= m; i ++ )
	{
		int a, b;
		cin >> a >> b;
		vec.push_back({a, b, i, 1});
		if (a - 1) vec.push_back({a, a - 1, i, -1});
		vec.push_back({b, n, i, 1});
		if (a - 1) vec.push_back({a - 1, n, i, -1});
		if (b - 1) vec.push_back({b, b - 1, i, - 1});
		if (a - 1 && b - 1) vec.push_back({a - 1, b - 1, i, 1});
	}
	sort(vec.begin(), vec.end());
	for (auto [x, y, id, k] : vec)
	{
		if (id == -1) add(y, k);
		else ans[id] += ask(y) * k;
	}
	for (int i = 1; i <= m; i ++ ) cout << ans[i] << endl;
	return 0;
} 
```

---

## 作者：yhy2024 (赞：3)

考虑两条直线相交的必要条件。

设两条直线的两个端点分别是 $[l_1,r_1],[l_2,r_2]$，想象一下，如果有一条直线一个端点被另一条直线的端点包含如：$l_1<l_2<r_1$，另一个端点如果不被包含：$r_2<l_1$ 或 $r_2>r_1$ 那么这两条直线交。

于是得到两条直线直线相交的条件是：$l_1<l_2<r_1<r_2$ 或 $r_2<l_1<l_2<r_1$。

做一个扫描线离线二维数点即可，这部分很典，不说了。

离线二维数点模版：[link](https://www.luogu.com.cn/problem/P10814)。

```cpp
#include<bits/stdc++.h>
#define N 2000005 
#define rd read()
using namespace std;
int n,m,x,y,ans[N];
vector<int>v[N];
struct Node{int l,r,id,f;};
vector<Node>q[N];
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9')
		x=x*10+ch-'0',ch=getchar();
	return x*f;
}
struct{
	int tr[N];
	inline int lowbit(int x){return x&-x;}
	inline void add(int x,int v){for(int i=x;i<=n;i+=lowbit(i)) tr[i]+=v;}
	inline int Ask(int x){int res=0;for(int i=x;i>0;i-=lowbit(i)) res+=tr[i];return res;}
	inline int ask(int l,int r){return Ask(r)-Ask(l-1);}
}T;
signed main(){
	n=rd*2,m=rd;
	for(int i=1;i<=m;i++){
		x=rd,y=rd;
		v[x].push_back(y),v[y].push_back(x);
	}
	m=rd;
	for(int i=1;i<=m;i++){
		x=rd,y=rd;
		q[x-1].push_back({y+1,n,i,-1});
		q[x-1].push_back({1,x-1,i,-1});
		q[y].push_back({y+1,n,i,1});
		q[y].push_back({1,x-1,i,1});
	}
	for(int i=1;i<=n;i++){
		for(int j:v[i]) T.add(j,1);
		for(auto [l,r,id,f]:q[i]) ans[id]+=T.ask(l,r)*f;
	}
	for(int i=1;i<=m;i++) cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：Dtw_ (赞：3)

## Solution
### 主席树
考虑这个问题的实质是什么？

就是数

$$l\leq l'\leq r \leq r'$$

或者

$$l'\leq l\leq r' \leq r$$

的个数。

那么考虑把询问和操作弄到一块，先按 $l$ 排序，这样就解决了第一个不等式，然后由于 $l$ 是有序的，那么我们可以二分找到最后一个位置满足他的 $l'\leq r$ 然后就解决了第 $2$ 个不等式，最后我们只需要查询一段区间有多少 $r'\ge r$ 即可。

我们注意到是查询一段区间，那么可以直接用主席树在值域上维护和，然后就做完了。

对于第二个大式子同理，按照 $r$ 排序即可。
## Code
```cpp
#include <bits/stdc++.h>

using namespace std;

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int N = 1e6 + 10, inf = 0x3f3f3f3f;

int n, q, m, rt[N], cnt, A[N];
vector<int> v[N << 1];

struct node { int x, y, opt, id; } a[N];

struct SEG_T {
    struct Node {
        int l, r, x;
        #define l(o) tr[o].l
        #define r(o) tr[o].r
    } tr[N * 24];

    #define mid (l + r) / 2

    void build(int &rt, int l, int r)
    {
        rt = ++cnt; tr[rt].x = 0;
        if (l == r) return;
        build(l(rt), l, mid);
        build(r(rt), mid + 1, r);
    }

    void update(int &rt, int u, int l, int r, int p)
    {
        rt = ++cnt; tr[rt] = tr[u]; tr[rt].x++;
        if (l == r) return;
        if (p <= mid) update(l(rt), l(u), l, mid, p);
        else update(r(rt), r(u), mid + 1, r, p);
    }

    int query(int rt, int u, int l, int r, int sp, int ep)
    {
        int x = tr[rt].x - tr[u].x;
        if (sp <= l && r <= ep) return x;
        int res = 0;
        if (sp <= mid) res += query(l(rt), l(u), l, mid, sp, ep);
        if (ep > mid) res += query(r(rt), r(u), mid + 1, r, sp, ep);
        return res;
    }

    #undef l(o)
    #undef r(o)
    #undef mid
} T[2];

int main()
{
    fst
    cin >> n >> m; n *= 2;
    int p = m;
    for (int i = 1; i <= m; i++) cin >> a[i].x >> a[i].y;
    int q; cin >> q;
    for (int i = 1; i <= q; i++) {
        p++;
        cin >> a[p].x >> a[p].y;
        a[p].id = i; a[p].opt = 1;
    }
    sort (a + 1, a + p + 1, [] (node x, node y) { return x.x < y.x; });
    for (int i = 1; i <= p; i++) {
        rt[i] = rt[i - 1];
        if (!a[i].opt) T[0].update(rt[i], rt[i - 1], 1, n, a[i].y);
    }
    for (int i = 1; i <= p; i++) {
        if (a[i].opt) {
            int ans = 0;
            int l = i, r = p, res = 0;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (a[mid].x <= a[i].y) l = (res = mid) + 1;
                else r = mid - 1;
            }
            if (res) ans = T[0].query(rt[res], rt[i], 1, n, a[i].y, n);
            A[a[i].id] = ans;
        }
    }
    memset(rt, 0, sizeof rt);
    sort (a + 1, a + p + 1, [] (node x, node y) { return x.y < y.y; });
    for (int i = 1; i <= p; i++) {
        rt[i] = rt[i - 1];
        if (!a[i].opt) T[1].update(rt[i], rt[i - 1], 1, n, a[i].x);
    }
    for (int i = 1; i <= p; i++) {
        if (a[i].opt) {
            int ans = 0;
            int l = 1, r = i, res = 0;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (a[mid].y >= a[i].x) r = (res = mid) - 1;
                else l = mid + 1;
            }
            if (res) ans = T[1].query(rt[i - 1], rt[res - 1], 1, n, 1, a[i].x);
            A[a[i].id] += ans;
        }
    }
    for (int i = 1; i <= q; i++) cout << A[i] << "\n"; 
    return 0;
}

```
### 小容斥
还是考虑那两个式子，实际上就是有其中一个端点在 $l,r$ 之间，然后另一个在外头。

那么我们可以进行一个小容斥，加上其中一个端点在 $l,r$ 内的，然后减掉两个端点都在 $l,r$ 内的即可。

我们可以开两颗树状数组，对第一个我们直接查询区间和即可，对于第二个我们可以对于 $l$ 排序，然乎倒着扫，当我们扫到初始线段的 $l'$ 时我们把他的 $r$ 加入到第二棵树状数组种，此时我们的 $l \ge l'$ 然后查询 $l,r$ 内的和，这样如果 $l\ge l' \land r'\leq r$ 的点就会被减掉。
### 扫描线
考虑那个式子：

$$l\leq l'\leq r \leq r'$$

$$l'\leq l\leq r' \leq r$$

对于第一个式子，我们可以对 $r$ 排序，扫描 $r$ 这一维然后把对应的 $l$ 加入，然后就只需要查询 $[l,r]$ 内左端点的个数和即可。

第二个式子同理。

---

## 作者：Jenny_yu (赞：3)

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

## 作者：wpl123456wpl (赞：2)

# Chord Crossing

## 题意

在一个圆上画出 $2N$ 个等分点，按顺时针顺序分别编号为 $1,2,...,2N$。现在有 $M$ 条线段，第 $i$ 条线段连接 $A_i$, $B_i$ $(1 < A_i < B_i < 2N)$ 这两个偶数点。保证没有任意两条线段存在交点。有 $Q$ 次询问，第 $j$ 个询问给定两个奇数点 $C_j$, $D_j$, $(1 < C_j < D_j < 2N)$。请问在原来的 $M$ 条线段当中有多少条线段与 $(C_j, D_j)$ 这条线段存在交点?

## 思路

**把圆拆开，变成数轴问题，离线询问**。

对于每个询问 $(C_j, D_j)$，就变成了求有多少条线
 $(A_i, B_i)$ 满足其中一个端点在区间 $(C_j, D_j)$ 内，另一个不在该区间内。线段交叉只可能是以下**两种情况**之一:

- 一个 $i$ 区间左端点在区间 $j$ 内。
- 一个 $i$ 区间右端点在区间 $j$ 内。

两种情况可以选择分开处理，**想办法去掉一个属性**。

### 引入与算法选择

我们这**只对第二种情况**进行讨论:

首先我们想让区间 $i$ 的右端点位于区间 $j$ 内，左端点位置一定小于右端点，而我们不想让区间 $i$ 的左端点位于区间 $j$ 内，所以我们先要保证区间 $i$ 的左端点的位置小于区间 $j$ 的左端点，**所以我们可以排序加双指针**。

**右端点继续维护**，很明显是求区间 $j$ 的 $l$ 到 $r$ 之间的区间 $i$ 的右端点个数，$O(M)$ 更新前缀，$O(Q)$ 次查询前缀，这就是很明显的线段树或树状数组。时间复杂度为 $O(M \log M + Q \log Q)$。

## 代码展示


```cpp
#include<bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 1e6 + 5;

int n, m, q, ans[N];

struct Tree{
    int c[2 * N], len;
    void init(int s){
        len = s;
        fill(c + 1, c + len + 1, 0);
    }
    void update(int p, int x){
        for(; p <= len; p += p & -p){
            c[p] += x;
        }
    }
    int query(int p){
        int res = 0;
        for(; p >= 1; p -= p & -p){
            res += c[p];
        }
        return res;
    }
}tree;

struct node{
    int l, r, id;
}a[N], b[N];

bool cmp(const node &ad, const node &bd){
    return ad.l < bd.l;
}

bool cmp2(const node &ad, const node &bd){
    return ad.r > bd.r;
}

int main(){
    //ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        cin >> a[i].l >> a[i].r;
        a[i].id = 0;
    }
    sort(a + 1, a + m + 1, cmp);
    cin >> q;
    for(int i = 1; i <= q; i++){
        cin >> b[i].l >> b[i].r;
        b[i].id = i;
    }
    sort(b + 1, b + q + 1, cmp);
    tree.init(2 * n);
    for(int i = 1, l = 1; i <= q; i++){
        while(l <= m && a[l].l < b[i].l){
            tree.update(a[l].r, 1), l++;
        }
        ans[b[i].id] += tree.query(b[i].r) - tree.query(b[i].l - 1);
    }
    sort(a + 1, a + m + 1, cmp2);
    sort(b + 1, b + q + 1, cmp2);
    tree.init(2 * n);
    for(int i = 1, l = 1; i <= q; i++){
        while(l <= m && a[l].r > b[i].r){
            tree.update(a[l].l, 1), l++;
        }
        ans[b[i].id] += tree.query(b[i].r) - tree.query(b[i].l - 1);
    }
    for(int i = 1; i <= q; i++){
        cout << ans[i] << '\n';
    }
    return 0;
}

```

---

## 作者：2012_Zhang_ (赞：2)

## 思路解析
首先我们需要知道我们要求什么，我们不妨转化题意，  
我们要求的就是对于每个 $C_i,D_i$，找出一个点在区间  $[C_i,D_i]$，另一个点在区间 $[1,C_i]$ 或 $[D_i,n]$ 的线的数量。  
我们设 $qry(l,x,y)$ 左端点在区间 $[1,l]$ 右端点在 $[x,y]$ 的线的数量。  
我们就可以把答案拆成   
$$
    ans_i=qry(D_i,D_i,n)-qry(C_i,D_i,n)+qry(C_i,C_i,D_i)
$$  
这样我们可以使用树状数组，并且维护每个询问的左端点单调性以求出每个答案。  

代码奉上
## AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=5e6;
int a[maxn],b[maxn],c[maxn],n,m,q,res[maxn],tot;
struct lines{int a,b;}line[maxn];
struct asks{int l,x,y,tp,id;}qry[maxn];
bool cmp(lines a,lines b){return a.a<b.a;}
bool cmp2(asks a,asks b){return a.l<b.l;}
int lb(int x){return x&-x;}
void add(int x){for(int i=x;i<=n;i+=lb(i)) c[i]++;}
int ask(int x){
    int ans=0;
    for(int i=x;i>0;i-=lb(i)) ans+=c[i];
    return ans;
}
signed main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++) cin>>line[i].a>>line[i].b;
    sort(line+1,line+m+1,cmp);
    n*=2;
    cin>>q;
    for(int i=1;i<=q;i++){
        cin>>a[i]>>b[i];
        qry[++tot].l=b[i],qry[tot].x=b[i],qry[tot].y=n;
        qry[tot].tp=1,qry[tot].id=i;
        qry[++tot].l=a[i],qry[tot].x=b[i],qry[tot].y=n;
        qry[tot].tp=-1,qry[tot].id=i;
        qry[++tot].l=a[i],qry[tot].x=a[i],qry[tot].y=b[i];
        qry[tot].tp=1,qry[tot].id=i;
    }
    sort(qry+1,qry+tot+1,cmp2);
    int id=1;
    for(int i=1;i<=tot;i++){
        while(line[id].a<=qry[i].l&&id<=m){add(line[id].b); id++;}
        res[qry[i].id]+=qry[i].tp*(ask(qry[i].y)-ask(qry[i].x-1));
    }
    for(int i=1;i<=q;i++) cout<<res[i]<<endl;
}

---

## 作者：fanminghao000 (赞：1)

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

