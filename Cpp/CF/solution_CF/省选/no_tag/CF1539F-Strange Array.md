# Strange Array

## 题目描述

Vasya has an array of $ n $ integers $ a_1, a_2, \ldots, a_n $ . Vasya thinks that all numbers in his array are strange for some reason. To calculate how strange the $ i $ -th number is, Vasya created the following algorithm.

He chooses a subsegment $ a_l, a_{l+1}, \ldots, a_r $ , such that $ 1 \le l \le i \le r \le n $ , sort its elements in increasing order in his head (he can arrange equal elements arbitrary). After that he finds the center of the segment. The center of a segment is the element at position $ (l + r) / 2 $ , if the length of the segment is odd, and at position $ (l + r + 1) / 2 $ otherwise. Now Vasya finds the element that was at position $ i $ before the sorting, and calculates the distance between its current position and the center of the subsegment (the distance between the elements with indices $ j $ and $ k $ is $ |j - k| $ ).

The strangeness of the number at position $ i $ is the maximum distance among all suitable choices of $ l $ and $ r $ .

Vasya wants to calculate the strangeness of each number in his array. Help him to do it.

## 说明/提示

In the first example:

1. For the first position we choose the segment from $ 1 $ to $ 5 $ . After sorting, it looks like $ [1, 2, 3, 4, 5] $ , the center is $ 3 $ . The distance from the center to $ 5 $ is $ 2 $ .
2. For the second position we choose the segment from $ 2 $ to $ 4 $ .
3. For the third position we choose the segment from $ 3 $ to $ 5 $ .
4. For the fourth position we choose the segment from $ 1 $ to $ 4 $ . After sorting, it looks like $ [2, 3, 4, 5] $ , the center is $ 4 $ . The distance from the center to $ 2 $ is $ 2 $ .
5. For the fifth position we choose the segment from $ 1 $ to $ 5 $ .

## 样例 #1

### 输入

```
5
5 4 3 2 1```

### 输出

```
2 1 1 2 2```

## 样例 #2

### 输入

```
7
3 6 5 6 2 1 3```

### 输出

```
2 3 1 3 2 3 1```

# 题解

## 作者：滑不拉稽 (赞：7)

题意：给定一个序列，需要求出序列中每个元素的奇怪值。$a_i$ 的奇怪值定义为选取任意一个区间，将区间里的数升序排序后 $a_i$ 的新位置和该区间中位数下标距离的最大值。(若区间长度为偶数，中位数的下标为 $\frac{l+r+1}{2}$ )。

首先考虑如果区间已经确定，且已经升序排序后如何求距离。

令 $a_{mid}$ 表示中位数， $a_x$ 表示排序后的新下标，$a_l,a_m,a_r$ 表示  $\le a_x,=a_x,>a_x$ 的数的个数。下图是 $a_x > a_{mid}$ 的情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/jkdebim9.png)

显然 $dis=\frac{a_l+a_m+a_r}{2}-a_r=\lfloor\frac{a_l+a_m-a_r}{2}\rfloor$ .

同理若 $a_x<a_{mid}$ ，则有 $dis=\lfloor \frac{a_r+a_m-a_l+1}{2} \rfloor$ .

也就是说只要知道 $a_l,a_m,a_r$ ，无需排序也能确定距离。接下来就是中位数的老套路了：

新开一个数组 $b$ ,将 $\le a_x$ 的数的位置赋值为$1$ ，$>a_x$ 的数的位置赋值为 $-1$ 。那么 $\sum^{r} _ {i=l} b_i-1=(a_l+a_m)\times 1 + (a_r)\times (-1)=dis\times2 $ ，前面减$1$是要除去 $a_x$ 本身。即 $dis=\frac{\sum^{r} _ {i=l} b_i-1}{2}$ 。

接下来考虑求 $\sum^{r} _ {i=l} b_i$ ，拆成两份也就是  $\sum_{i=l}^{x}b_i+\sum_{i=x}^{r}b_i-1$ ，然后发现 $\sum_{i=l}^{x}b_i$  就是维护整个 $1\sim x$ 的最大后缀，$\sum_{i=x}^{r}b_i$ 就是维护整个    $x\sim n$ 的最大前缀。

所以只用套区间合并线段树的模板就好。

另外，对于另一种 $a_x<a_{mid}$ 的情况还有一种取巧的方法：只用把 $a$ 数组整个翻转再把每个元素变为相反数就变成 $a_x<a_{mid}$ 的情况了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define fre(x) freopen(#x".in","r",stdin);freopen(#x".out","w",stdout)
#define int long long
#define re register int
#define inf 0x7fffffffffffffff
#define Pair pair<int,int>
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return f==1?x:-x;
}
const int N=2e5+10;
struct Seg{
    int l,r,lm,rm,sum;
    #define l(x) tree[x].l
    #define r(x) tree[x].r
    #define lm(x) tree[x].lm
    #define rm(x) tree[x].rm
    #define sum(x) tree[x].sum
}tree[N<<2];
inline void pushup(int p)
{
    sum(p)=sum(p<<1)+sum(p<<1|1);
    lm(p)=max(lm(p<<1),sum(p<<1)+lm(p<<1|1));
    rm(p)=max(rm(p<<1|1),sum(p<<1|1)+rm(p<<1));
}
void build(int p,int l,int r)
{
    l(p)=l;r(p)=r;
    if(l==r)return sum(p)=lm(p)=rm(p)=-1,void();
    int mid=(l+r)>>1;
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
    pushup(p);
}
void change(int p,int pos,int x)
{
    if(l(p)==r(p))return sum(p)=lm(p)=rm(p)=x,void();
    int mid=(l(p)+r(p))>>1;
    if(pos<=mid)change(p<<1,pos,x);
    else change(p<<1|1,pos,x);
    pushup(p);
}
Seg query(int p,int l,int r)
{
    if(r(p)<l || r<l(p))return {0,0,0,0,0};
    if(l<=l(p) && r>=r(p))return tree[p];
    Seg a=query(p<<1,l,r),b=query(p<<1|1,l,r);
    return {min(a.l,b.l),max(a.r,b.r),max(a.lm,a.sum+b.lm),max(b.rm,b.sum+a.rm),a.sum+b.sum};
}
int n,ans[N];
struct node{int x,id;}a[N];
bool cmp(node a,node b){return a.x<b.x;}
void calc(int flag)
{
    build(1,1,n);
    for(re i=1;i<=n;++i)
    {
        int j=i;
        while(j<n && a[j+1].x==a[i].x)++j;
        for(re k=i;k<=j;++k) change(1,a[k].id,1);
        for(re k=i;k<=j;++k)
        {
            Seg p=query(1,1,a[k].id),q=query(1,a[k].id,n);
            ans[a[k].id]=max(ans[a[k].id],p.rm+q.lm-1-!flag);
        }
        i=j;
    }
}
signed main()
{
    n=read();
    for(re i=1;i<=n;++i)
        a[i].x=read(),a[i].id=i;
    sort(a+1,a+n+1,cmp);
    calc(0);
    for(re i=1;i<=n/2;++i) swap(a[i],a[n-i+1]);
    for(re i=1;i<=n;++i) a[i].x=-a[i].x;
    calc(1);
    for(re i=1;i<=n;++i) 
        printf("%lld ",ans[i]/2);
    return 0;
}
```






---

## 作者：lory1608 (赞：5)

### CF1539F Strange Array题解

一道比较套路的数据结构题。

与中位数相关不难想到选择一个数 $x$ ，将大于 $x$ 的数设为 $1$ ，小于等于 $x$ 的数设为 $0$ 或 $-1$ 。

为了简化问题的讨论，我们在下述分析中假设所有元素的值互不相同。

对于值从小到大考虑，当考虑到元素 $a_i$ 时将 $\ge a_i$ 的数的位置标为 $1$ ，$<a_i$ 的位置标为 $-1$ ，为了使得 $a_i$ 离中位数的位置尽可能远，分以下两种情况讨论。

- $a_i$ 比中位数小，那么我们希望 $>a_i$ 的数 $-$ $\leq a_i$ 的数尽量多。那么，我们就需要找出一段**包含 $i$ 的权值尽量大的区间。**
- 同理，但$a_i$ 比中位数小，那么我们希望 $>a_i$ 的数 $-$ $\leq a_i$ 的数尽量少。那么，我们就需要找出一段**包含 $i$ 的权值尽量小的区间。**

上述过程可以用线段树维护前缀和并在线段树上二分实现。

对于 $a_i$ 值相同的情况，只是对于设 $1$ 和 $-1$ 的细节需要注意，要让 $1$ 尽量多时，将相同的元素谁为 $1$ ，否则谁为 $-1$ 。

如果对细节不清楚可以看代码。

```cpp
#include<bits/stdc++.h>
#define FOR(i,a,b) for(int i=a;i<=b;++i)
#define PII pair<int,int>
#define ll long long
#define pb push_back
#define sz(x) (int)(x.size())
#define gc getchar()
using namespace std;
inline int gi()
{
	int x=0,f=1;
	char ch=gc;
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=gc;}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=gc;}
	return (f==1)?x:-x;
}
inline int max(int a,int b){return a>b?a:b;}
inline int min(int a,int b){return a<b?a:b;}
const int maxn=2e5+5;
int n,a[maxn];
vector<int>v[maxn];
struct segmentree
{
	#define ls u<<1
	#define rs u<<1|1
	static const int maxn=8e5+105;
	int minv[maxn],maxv[maxn],tag[maxn],pos1[maxn],pos2[maxn];///prefix_sum
	inline void build(int u,int l,int r)
	{
		tag[u]=0,pos1[u]=0,pos2[u]=0;
		if(l==r)return pos1[u]=l,pos2[u]=l,maxv[u]=minv[u]=l,void();
		int mid=(l+r)>>1;
		build(ls,l,mid),build(rs,mid+1,r);
		pushup(u);
	}
	inline void pushdown(int u,int l,int r)
	{
		if(tag[u])
		{
			tag[ls]+=tag[u];tag[rs]+=tag[u];
			maxv[ls]+=tag[u];maxv[rs]+=tag[u];
			minv[ls]+=tag[u];minv[rs]+=tag[u];
			tag[u]=0;
		}
	}
	inline void pushup(int u)
	{
		if(minv[ls]<minv[rs])minv[u]=minv[ls],pos1[u]=pos1[ls];
		else minv[u]=minv[rs],pos1[u]=pos1[rs];
		if(maxv[ls]>maxv[rs])maxv[u]=maxv[ls],pos2[u]=pos2[ls];
		else maxv[u]=maxv[rs],pos2[u]=pos2[rs];
	}
	inline void update(int u,int l,int r,int x,int y,int v)
	{
		if(x<=l&&y>=r)return maxv[u]+=v,minv[u]+=v,tag[u]+=v,void();
		int mid=(l+r)>>1;
		pushdown(u,l,r);
		if(x<=mid)update(ls,l,mid,x,y,v);
		if(y>mid)update(rs,mid+1,r,x,y,v);
		pushup(u);
	}
	inline pair<int,int> query1(int u,int l,int r,int x,int y)
	{
		if(x<=l&&y>=r)return pair<int,int>(minv[u],pos1[u]);
		pushdown(u,l,r);
		int mid=(l+r)>>1;
		if(y<=mid)return query1(ls,l,mid,x,y);
		if(x>mid)return query1(rs,mid+1,r,x,y);
		return min(query1(ls,l,mid,x,y),query1(rs,mid+1,r,x,y));
	}
	inline pair<int,int> query2(int u,int l,int r,int x,int y)
	{
		if(x<=l&&y>=r)return pair<int,int>(maxv[u],pos2[u]);
		pushdown(u,l,r);
		int mid=(l+r)>>1;
		if(y<=mid)return query2(ls,l,mid,x,y);
		if(x>mid)return query2(rs,mid+1,r,x,y);
		return max(query2(ls,l,mid,x,y),query2(rs,mid+1,r,x,y));
	}
	#undef ls
	#undef rs
}tree;
inline void input()
{
	n=gi();
	FOR(i,1,n)a[i]=gi(),v[a[i]].pb(i);
}
int ans[maxn],id[maxn];
inline void solve()
{
	FOR(i,1,n)id[i]=i;
	sort(id+1,id+n+1,[](int x,int y){return a[x]<a[y];});
	tree.build(1,0,n);
	FOR(i,1,n)///-1
	{
		int x=id[i];
		if(a[id[i]]!=a[id[i-1]])for(int x:v[a[id[i]]])tree.update(1,0,n,x,n,-2);
		tree.update(1,0,n,x,n,2);
		auto lp=tree.query2(1,0,n,0,x-1),rp=tree.query1(1,0,n,x,n);
		//int len=rp.second-lp.second+1;
		int val=rp.first-lp.first;
		assert(val<=1);
		ans[x]=max(ans[x],(-val+1)/2);
		tree.update(1,0,n,x,n,-2);
	}
	tree.build(1,0,n);
	FOR(i,1,n)///1
	{
		int x=id[i];
		if(a[id[i]]!=a[id[i-1]]&&i!=1)for(int x:v[a[id[i-1]]])tree.update(1,0,n,x,n,-2);
		tree.update(1,0,n,x,n,-2);
		auto lp=tree.query1(1,0,n,0,x-1),rp=tree.query2(1,0,n,x,n);
		//int len=rp.second-lp.second+1;
		int val=rp.first-lp.first;
		assert(val>=-1);
		ans[x]=max(ans[x],(val+2)/2);
		tree.update(1,0,n,x,n,2);
	}
	FOR(i,1,n)printf("%d ",ans[i]);
	puts("");
}
int main()
{
    input();
    solve();
	return 0;
}
```



---

## 作者：gdf_yhm (赞：4)

[CF1539F](https://www.luogu.com.cn/problem/CF1539F)

### 思路

中位数相关，考虑 $a_j>a_i$ 的 $j$ 设为 $1$，$a_j<a_i$ 的 $j$ 设为 $-1$，做前缀和。问题是 $a_j=a_i$ 时可以任意排列。

- $a_i>a_{mid}$，$a_j=a_i$ 的 $j$ 放在 $i$ 前，设为 $-1$。此时 $-1$ 数量多于 $1$。$ans=\max \sum [a_j\leq a_i] -\lceil \frac{l+r}{2} \rceil=\frac{-\min (sum_r-sum_{l-1})-1}{2}$。

- 否则，$a_j=a_i$ 的 $j$ 放在 $i$ 后，设为 $1$。此时 $1$ 数量多于 $-1$。$ans=\max \sum [a_j\geq a_i] -\lceil \frac{l+r}{2} \rceil=\frac{\max (sum_r-sum_{l-1})}{2}$。

具体系数可以带入数推。现在要动态维护 $\max (sum_r-sum_{l-1})$。可以按 $a_i$ 从小往大加入。初始时 $sum_i=i$，当 $a_i$ 改为 $-1$ 时，线段树维护区间 $[i,n]$ 减 $2$。$\max (sum_r-sum_{l-1})=\max_{j=i}^{n}sum_j-\min_{j=1}^{i}sum_{j-1}$。查询区间最值。min 同理。

### code

```cpp
int n,a[maxn];
struct sgt{
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
	int mn[maxn<<2],mx[maxn<<2],tag[maxn<<2];
	void push(int nd){
		mn[ls]+=tag[nd],mx[ls]+=tag[nd],tag[ls]+=tag[nd];
		mn[rs]+=tag[nd],mx[rs]+=tag[nd],tag[rs]+=tag[nd];
		tag[nd]=0;
	}
	void updata(int nd,int l,int r,int ql,int qr,int w){
		if(l>=ql&&r<=qr){
			mn[nd]+=w,mx[nd]+=w,tag[nd]+=w;
			return ;
		}
		if(tag[nd])push(nd);
		if(ql<=mid)updata(ls,l,mid,ql,qr,w);
		if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
		mn[nd]=min(mn[ls],mn[rs]),mx[nd]=max(mx[ls],mx[rs]);
	}
	int qmn(int nd,int l,int r,int ql,int qr){
		if(l>=ql&&r<=qr)return mn[nd];
		if(tag[nd])push(nd);
		if(qr<=mid)return qmn(ls,l,mid,ql,qr);
		if(ql>mid)return qmn(rs,mid+1,r,ql,qr);
		return min(qmn(ls,l,mid,ql,qr),qmn(rs,mid+1,r,ql,qr));
	}
	int qmx(int nd,int l,int r,int ql,int qr){
		if(l>=ql&&r<=qr)return mx[nd];
		if(tag[nd])push(nd);
		if(qr<=mid)return qmx(ls,l,mid,ql,qr);
		if(ql>mid)return qmx(rs,mid+1,r,ql,qr);
		return max(qmx(ls,l,mid,ql,qr),qmx(rs,mid+1,r,ql,qr));
	}
}s;
vector<int> pos[maxn];	
int ans[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read(),pos[a[i]].push_back(i);
		s.updata(1,0,n,i,n,1);
	}
	for(int i=1;i<=n;i++)if(pos[i].size()){
		for(int j:pos[i]){
//			cout<<j<<" "<<s.qmx(1,0,n,j,n)-s.qmn(1,0,n,0,j-1)<<" ";
			ans[j]=max(ans[j],(s.qmx(1,0,n,j,n)-s.qmn(1,0,n,0,j-1))/2);
		}
		for(int j:pos[i])s.updata(1,0,n,j,n,-2);
		for(int j:pos[i]){
//			cout<<j<<" "<<-(s.qmn(1,0,n,j,n)-s.qmx(1,0,n,0,j-1))<<"\n";
			ans[j]=max(ans[j],(-(s.qmn(1,0,n,j,n)-s.qmx(1,0,n,0,j-1))-1)/2);
		}
	}
	for(int i=1;i<=n;i++)printf("%lld ",ans[i]);
}
```


---

## 作者：AxDea (赞：4)

对于线段 $[l, r]$ ，按照题目定义，其中心在该线段中的排名为 $\left\lceil\dfrac{r - l + 2}{2}\right\rceil$ 。

现在从每一个元素为出发点考虑，可以发现，需要一个可以快速获得的左方或右方的信息。

首先，一个任意元素的排名自然转化为一个区间内比这个元素内比它小的数的个数。

对于当前元素 $a_i$ ，设 $l_l$ 表示在区间 $[l, i]$ 中**严格**小于 $a_i$ 的元素个数，$l_r$ 表示在区间 $[i, r]$ 中**严格**小于 $a_i$ 的元素个数，$L_l$ 表示在区间 $[l, i]$ 中小于等于 $a_i$ 的元素个数，$L_r$ 表示在区间 $[i + 1, r]$ 中小于等于 $a_i$ 的元素个数。

由于相等的值可以任意摆放，所以答案必定是 $\max\{L_l + L_r - \left\lceil\dfrac{r - l + 2}{2}\right\rceil, \left\lceil\dfrac{r - l + 2}{2}\right\rceil -l_l - l_r - 1\}$ 。

由于 $- \lceil r\rceil = \lfloor -r \rfloor (r > 0)$ ，所以上式可以拆成：
$$
\max\left\{\left\lfloor\dfrac{2L_l + l + 2L_r - r - 2}{2}\right\rfloor, \left\lceil\dfrac{-2l_l - l - 2l_r + r}{2}\right\rceil\right\}
$$
然后就是对于每个 $i$ 最大化 $2L_l + l$ ，$2L_r - r$ ，$-2l_l - l$ ，$-2l_r + r$ 。

先对原数组排序，这样保证了小的 $a_i$ 对大的 $a_i$ 做贡献。

以处理 $2L_l + l$ 时为例，先考虑建立一颗线段树，线段树中下标为 $i$ 的地方初始值为 $i$ 。

因为相等的元素互相影响，所以对于相等的元素整体处理，先整体修改，再整体查询。（注意在处理 $l_l$ 或 $l_r$ 时，要先查询，再修改。）

首先，若当前元素为 $j$ ，且有 $k \ge j\ (a_k \ge a_j)$ ，那么对于这个 $k$ 的 $L_l(1 \le l \le j)$ 贡献为 $2$ ，线段树上区间加。

但是当 $k < j$ 时，这样修改就不对了。

但是换一个角度，当 $k < j$ 时，这样修改时，$j$ 对于所有 $L_l(1 \le l\le k)$ 的贡献是一样的，所以差分一下就好了。

答案就是（（线段树上 $[1, k]$ 中的最大值）减去（（线段树上下标为 $k + 1$ 的值） 减去 （ $k + 1$ ）））。

其他情况都比较类似，具体见代码，时间复杂度 $\mathcal O (n\log n)$ 。

```cpp
#include <bits/stdc++.h>
#define forn(i,s,t) for(register int i=(s); i<=(t); ++i)
#define form(i,s,t) for(register int i=(s); i>=(t); --i)
#define rep(i,s,t) for(register int i=(s); i<(t); ++i)
using namespace std;
typedef long long i64;
const int N = 2e5 + 3;
template<typename T>
inline T Max(T A, T B) {return A > B ? A : B;}
int zz[N], rt, n;
class SegTree {
public:
	int val[N << 1], L[N << 1], R[N << 1], tag[N << 1], sl;
	inline void push_up(int p) {
		val[p] = Max(val[L[p]], val[R[p]]);
	}
	inline void Opt(int p, int k) {
		val[p] += k, tag[p] += k;
	}
	inline void push_down(int p) {
		Opt(L[p], tag[p]), Opt(R[p], tag[p]), tag[p] = 0;
	}
	void Bld(int& p, int l, int r) {
		p = ++sl, tag[p] = 0;
		if(l == r) return val[p] = zz[l], void();
		int mid = l + r >> 1;
		Bld(L[p], l, mid), Bld(R[p], mid + 1, r);
		push_up(p);
	}
	void Upd(int p, int l, int r, int nl, int nr, int k) {
		if(l == nl && nr == r) return Opt(p, k);
		int mid = nl + nr >> 1;
		(tag[p]) && (push_down(p), 0);
		if(r <= mid) Upd(L[p], l, r, nl, mid, k);
		else if(l > mid) Upd(R[p], l, r, mid + 1, nr, k);
		else Upd(L[p], l, mid, nl, mid, k), Upd(R[p], mid + 1, r, mid + 1, nr, k);
		push_up(p);
	}
	int Qry(int p, int l, int r, int nl, int nr) {
		if(l == nl && nr == r) return val[p];
		int mid = nl + nr >> 1;
		(tag[p]) && (push_down(p), 0);
		if(r <= mid) return Qry(L[p], l, r, nl, mid);
		else if(l > mid) return Qry(R[p], l, r, mid + 1, nr);
		else return Max(Qry(L[p], l, mid, nl, mid), Qry(R[p], mid + 1, r, mid + 1, nr));
	}
}T; // 区间加, 区间 max 
int a[N], Ll[N], Lr[N], Rl[N], Rr[N], id[N];
// Ll 表示 2L_l + l, Lr 表示 2Lr - r, Rl 表示 -2l_l - l, Rr 表示 -2l_r + r
inline bool cmp(int A, int B) {return a[A] < a[B];}
int main() {
	scanf("%d", &n);
	forn(i,1,n) scanf("%d", a + i), zz[i] = id[i] = i;
	sort(id + 1, id + n + 1, cmp);
	T.sl = 0, T.Bld(rt, 1, n);
	forn(i,1,n) {
		int j = i;
		do T.Upd(rt, 1, id[j], 1, n, 2), ++j;
		while(a[id[j]] == a[id[i]]);
		rep(k,i,j) Ll[id[k]] = T.Qry(rt, 1, id[k], 1, n) - 
					((id[k] < n) ? (T.Qry(rt, id[k] + 1, id[k] + 1, 1, n) - id[k] - 1) : 0);
		i = j - 1;
	}
	T.sl = 0, T.Bld(rt, 1, n);
	forn(i,1,n) {
		int j = i;
		do Rr[id[j]] = T.Qry(rt, id[j], n, 1, n) -
						(T.Qry(rt, id[j], id[j], 1, n) - id[j]), ++j;
		while(a[id[j]] == a[id[i]]);
		rep(k,i,j) T.Upd(rt, id[k], n, 1, n, -2);
		i = j - 1;
	}
	forn(i,1,n) zz[i] = -i;
	T.sl = 0, T.Bld(rt, 1, n);
	forn(i,1,n) {
		int j = i;
		do T.Upd(rt, id[j], n, 1, n, 2), ++j;
		while(a[id[j]] == a[id[i]]);
		rep(k,i,j) Lr[id[k]] = T.Qry(rt, id[k], n, 1, n) - (T.Qry(rt, id[k], id[k], 1, n) + id[k]);
		i = j - 1;
	}
	T.sl = 0, T.Bld(rt, 1, n);
	forn(i,1,n) {
		int j = i;
		do Rl[id[j]] = T.Qry(rt, 1, id[j], 1, n) - 
						(T.Qry(rt, id[j], id[j], 1, n) + id[j]), ++j;
		while(a[id[j]] == a[id[i]]);
		rep(k,i,j) T.Upd(rt, 1, id[k], 1, n, -2);
		i = j - 1;
	}
	forn(i,1,n) printf("%d%c", Max(Ll[i] + Lr[i] - 2, Rl[i] + Rr[i] + 1) >> 1, " \n"[i == n]);
	return 0;
}
```

~~标算比这个不知道高到哪里去了~~

---

## 作者：Tx_Lcy (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1539F)

## 思路

应该算是比较简单的 $\verb!2600!$，思路很一眼。不过代码写的很阴间。

假如我们当前枚举的数是 $a_i$，我们把大于 $a_i$ 的数视为 $1$，小于 $a_i$ 的数视为 $-1$，等于 $a_i$ 的数可以视情况而定。

不难发现题目就是要求某一段包含 $a_i$ 的区间 $(l,r)$ 使得区间和的绝对值最大。

看到绝对值我们就要分类讨论：

+ 区间 $(l,r)$ 的和是正数

  那么和越大越好，于是我们把等于 $a_i$ 的数视为 $1$，当然它自己只能是 $0$，然后再从 $i$ 开始往左往右分别找一段区间和最大的连续区间，这个可以动态维护前缀和实现。
  
+ 区间 $(l,r)$ 的和是负数

  同理，和越小越好，于是我们把等于 $a_i$ 的数视为 $-1$，然后与上面的做法相同。
  
这样这道题就做完了，不过有很多小细节，还需要维护两颗线段树（一颗正数，一颗负数），每一颗线段树还需要维护两个值（一个前缀和，一个后缀和，不过也可以只维护一个前缀和），我的写法比较无脑，但是需要 $\rm 3.9k$，不过有很多都是复制粘贴的。

## 码

```cpp
//A tree without skin will surely die.
//A man without face will be alive
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mid ((l+r)>>1)
#define sqr(x) ((x)*(x))
#define all(x) (x).begin(),(x).end()
#define Tim ((double)clock()/CLOCKS_PER_SEC)
#define lowbit(x) (x&-x)
int const N=2e5+10;
int a[N],b[N],ans[N];
vector<int>c[N];
struct Segment_Tree{
	#define ls (x<<1)
	#define rs (x<<1|1)
	int c1[N<<2],c2[N<<2];
	int lazy1[N<<2],lazy2[N<<2];
	inline void pushdown(int x){
		c1[ls]+=lazy1[x];
		c1[rs]+=lazy1[x];
		lazy1[ls]+=lazy1[x];
		lazy1[rs]+=lazy1[x];
		lazy1[x]=0;
		c2[ls]+=lazy2[x];
		c2[rs]+=lazy2[x];
		lazy2[ls]+=lazy2[x];
		lazy2[rs]+=lazy2[x];
		lazy2[x]=0;
	}
	inline void update(int x,int l,int r,int ll,int rr,int v1,int v2){
		if (ll<=l && r<=rr){
			c1[x]+=v1,c2[x]+=v2;
			lazy1[x]+=v1,lazy2[x]+=v2;
			return;
		}
		pushdown(x);
		if (ll<=mid) update(ls,l,mid,ll,rr,v1,v2);
		if (mid<rr) update(rs,mid+1,r,ll,rr,v1,v2);
		c1[x]=max(c1[ls],c1[rs]);
		c2[x]=max(c2[ls],c2[rs]);
	}
	inline pair<int,int> query(int x,int l,int r,int ll,int rr){
		if (ll<=l && r<=rr) return {c1[x],c2[x]};
		pushdown(x);
		int res1=-LLONG_MAX,res2=-LLONG_MAX;
		if (ll<=mid){
			auto val=query(ls,l,mid,ll,rr);
			res1=max(res1,val.first);
			res2=max(res2,val.second);
		}
		if (mid<rr){
			auto val=query(rs,mid+1,r,ll,rr);
			res1=max(res1,val.first);
			res2=max(res2,val.second);
		}
		return {res1,res2};
	}
}T1;
struct Sublime_Tree{
	#define ls (x<<1)
	#define rs (x<<1|1)
	int c1[N<<2],c2[N<<2];
	int lazy1[N<<2],lazy2[N<<2];
	inline void pushdown(int x){
		c1[ls]+=lazy1[x];
		c1[rs]+=lazy1[x];
		lazy1[ls]+=lazy1[x];
		lazy1[rs]+=lazy1[x];
		lazy1[x]=0;
		c2[ls]+=lazy2[x];
		c2[rs]+=lazy2[x];
		lazy2[ls]+=lazy2[x];
		lazy2[rs]+=lazy2[x];
		lazy2[x]=0;
	}
	inline void update(int x,int l,int r,int ll,int rr,int v1,int v2){
		if (ll<=l && r<=rr){
			c1[x]+=v1,c2[x]+=v2;
			lazy1[x]+=v1,lazy2[x]+=v2;
			return;
		}
		pushdown(x);
		if (ll<=mid) update(ls,l,mid,ll,rr,v1,v2);
		if (mid<rr) update(rs,mid+1,r,ll,rr,v1,v2);
		c1[x]=min(c1[ls],c1[rs]);
		c2[x]=min(c2[ls],c2[rs]);
	}
	inline pair<int,int> query(int x,int l,int r,int ll,int rr){
		if (ll<=l && r<=rr) return {c1[x],c2[x]};
		pushdown(x);
		int res1=LLONG_MAX,res2=LLONG_MAX;
		if (ll<=mid){
			auto val=query(ls,l,mid,ll,rr);
			res1=min(res1,val.first);
			res2=min(res2,val.second);
		}
		if (mid<rr){
			auto val=query(rs,mid+1,r,ll,rr);
			res1=min(res1,val.first);
			res2=min(res2,val.second);
		}
		return {res1,res2};
	}
}T2;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n;cin>>n;
	for (int i=1;i<=n;++i) cin>>a[i],b[i]=a[i],c[a[i]].push_back(i);
	sort(b+1,b+n+1);int l=unique(b+1,b+n+1)-b-1;
	for (int i=1;i<=n;++i)
		T1.update(1,1,n,i,n,1,0),T1.update(1,1,n,1,i,0,1);
	for (int i=1;i<=n;++i)
		T2.update(1,1,n,i,n,1,0),T2.update(1,1,n,1,i,0,1);
	for (int i=1;i<=l;++i){
		int res=0;
		for (auto j:c[b[i]]){
			int maxr=T1.query(1,1,n,j,n).first-T1.query(1,1,n,j,j).first;
			int minl=T1.query(1,1,n,1,j).second-T1.query(1,1,n,j,j).second;
			ans[j]=max(ans[j],(abs(maxr+minl)+1)/2);
		}
		for (auto j:c[b[i]])
			T1.update(1,1,n,j,n,-2,0),
			T1.update(1,1,n,1,j,0,-2),
			T2.update(1,1,n,j,n,-2,0),
			T2.update(1,1,n,1,j,0,-2);
		for (auto j:c[b[i]]){
			int maxr=T2.query(1,1,n,j,n).first-T2.query(1,1,n,j,j).first;
			int minl=T2.query(1,1,n,1,j).second-T2.query(1,1,n,j,j).second;
			ans[j]=max(ans[j],abs(maxr+minl)/2);
		}
	}
	for (int i=1;i<=n;++i) cout<<ans[i]<<' ';
	cout<<'\n';
	return 0;
}
```

---

## 作者：Raisetsu41 (赞：1)

[link](https://www.luogu.com.cn/problem/C1539F)   
又一道跟中位数有关的题。   
老套路依次考虑每一位，对当前位考虑，若比当前位大则定为 $1$，若比当前位小则定为 $-1$ 。   
目标是使这个数离区间内的中位数比较远。   
可以分情况讨论
- 如果 $a_i \ge M_e$，则要让 大于 $a_i$ 的数的个数 减 小于 $a_i$ 的数的个数 最大。
- 如果 $a_i \le M_e$，则要让 小于 $a_i$ 的数的个数 减 大于 $a_i$ 的数的个数 最大。   
因为已经把权值转化成了 $1/-1$ 。所以上面的做差可以变成求和。   
这就可以做了。

---

