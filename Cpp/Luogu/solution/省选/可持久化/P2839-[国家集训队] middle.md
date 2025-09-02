# [国家集训队] middle

## 题目描述

一个长度为 $n$ 的序列 $a$，设其排过序之后为 $b$，其中位数定义为 $b_{n/2}$，其中 $a,b$ 从 $0$ 开始标号，除法下取整。

给你一个长度为 $n$ 的序列 $s$。

回答 $Q$ 个这样的询问：$s$ 的左端点在 $[a,b]$ 之间，右端点在 $[c,d]$ 之间的子区间中，最大的中位数。

其中 $a<b<c<d$。

位置也从 $0$ 开始标号。

我会使用一些方式强制你在线。


## 说明/提示

对于 $5\%$ 的数据，$n,Q \leq 100$；

对于另 $25\%$ 的数据，$n \leq 2000$；

对于 $100\%$ 的数据，$1\leq n \leq 20000$，$1\leq Q \leq 25000$，$1\leq a_i\leq 10 ^ 9$。

## 样例 #1

### 输入

```
5
170337785
271451044
22430280
969056313
206452321
3
3 1 0 2
2 3 1 4
3 1 4 0```

### 输出

```
271451044
271451044
969056313```

# 题解

## 作者：Cyhlnj (赞：65)

# Sol
丽洁姐的题目还是棒棒的

考虑二分答案

$Check?$
把小于它的设为$-1$，大于等于它的设为$1$

$[a, b]$求一个最大后缀子段和
$[c, d]$求一个最大前缀子段和
$[b+1, c-1]$求一个和

加起来如果大于等于$0$，那么满足要求
且这个数还可以变大，否则就只能缩小

每个数开一个线段树来做，空间开不下，用主席树即可

那么问题来了
**会不会二分的答案不在这个区间内呢？**
显然是不会的，如果区间外有个数满足要求，那么区间内一定会有个数大于等于它，显然区间内的那个数最优，而且也是满足要求的

那么做完了

```cpp
# include <bits/stdc++.h>
# define RG register
# define IL inline
# define Fill(a, b) memset(a, b, sizeof(a))
using namespace std;
typedef long long ll;
const int _(1e5 + 5);

IL int Input(){
    RG int x = 0, z = 1; RG char c = getchar();
    for(; c < '0' || c > '9'; c = getchar()) z = c == '-' ? -1 : 1;
    for(; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
    return x * z;
}

int rt[_], a[_], n, tot, q[4], id[_];
struct Mx{
	int lmax, rmax, sum, mx;

	IL void Init(){
		lmax = rmax = -_, sum = 0;
	}
} Ans;
struct HJT{
	int ls, rs;
	Mx v;
} T[_ * 20];

IL Mx Merge(RG Mx A, RG Mx B){
	RG Mx C;
	C.lmax = max(A.lmax, A.sum + B.lmax);
	C.rmax = max(B.rmax, A.rmax + B.sum);
	C.sum = A.sum + B.sum;
	return C;
}

IL void Build(RG int &x, RG int l, RG int r){
	x = ++tot;
	T[x].v.lmax = T[x].v.rmax = T[x].v.sum = r - l + 1;
	if(l == r) return;
	RG int mid = (l + r) >> 1;
	Build(T[x].ls, l, mid), Build(T[x].rs, mid + 1, r);
}


IL void Modify(RG int &x, RG int l, RG int r, RG int p){
	T[++tot] = T[x], x = tot;
	if(l == r){
		T[x].v.lmax = T[x].v.rmax = T[x].v.sum = -1;
		return;
	}
	RG int mid = (l + r) >> 1;
	if(p <= mid) Modify(T[x].ls, l, mid, p);
	else Modify(T[x].rs, mid + 1, r, p);
	T[x].v = Merge(T[T[x].ls].v, T[T[x].rs].v);
}

IL void Query(RG int x, RG int l, RG int r, RG int L, RG int R){
	if(L <= l && R >= r){
		Ans = Merge(Ans, T[x].v);
		return;
	}
	RG int mid = (l + r) >> 1;
	if(L <= mid) Query(T[x].ls, l, mid, L, R);
	if(R > mid) Query(T[x].rs, mid + 1, r, L, R);
}

IL int Check(RG int mid){
	RG int val = 0;
	if(q[1] + 1 <= q[2] - 1) Ans.Init(), Query(rt[mid], 1, n, q[1] + 1, q[2] - 1), val += Ans.sum;
	Ans.Init(), Query(rt[mid], 1, n, q[0], q[1]), val += Ans.rmax;
	Ans.Init(), Query(rt[mid], 1, n, q[2], q[3]), val += Ans.lmax;
	return val >= 0;
}

IL int Cmp(RG int x, RG int y){
	return a[x] < a[y];
}

int main(RG int argc, RG char* argv[]){
	n = Input(), Build(rt[1], 1, n), T[0].v.Init();
	for(RG int i = 1; i <= n; ++i) a[i] = Input(), id[i] = i;
	sort(id + 1, id + n + 1, Cmp);
	for(RG int i = 2; i <= n; ++i) rt[i] = rt[i - 1], Modify(rt[i], 1, n, id[i - 1]);
	for(RG int Q = Input(), ans = 0; Q; --Q){
		for(RG int i = 0; i < 4; ++i) q[i] = (Input() + ans) % n + 1;
		sort(q, q + 4);
		RG int l = 1, r = n;
		while(l <= r){
			RG int mid = (l + r) >> 1;
			if(Check(mid)) ans = a[id[mid]], l = mid + 1;
			else r = mid - 1;
		}
		printf("%d\n", ans);
	}
    return 0;
}

```


---

## 作者：sherlock55341 (赞：42)

居然没人写题解，竟然轮到了本蒟蒻来偷偷写一篇跑的巨慢的辣鸡题解  
这题真是DSM  
本题的想法很值得借鉴  
寻找中位数用二分来实现  
中途优化用主席树来实现  
难道这就是传说中的二分套主席树  
惊了  
## 二分+主席树  
考虑将区间内的数字进行一些处理，  
当我们尝试x是否是中位数时，将大于等于x的数置成1，其余的数置成-1，  
显然当区间和大于等于0时$\le$中位数，否则就是$\ge$中位数  
根据这一想法，我们可以二分查找中位数  
但是这样单次处理的复杂度是$O(n)$的  
查询一次就是$O(nlog_2{n})$的，不gg才奇怪  
考虑用主席树进行预处理  
将每个数二分时的1/-1序列处理出来  
显然将数组排序后可以直接继承前缀信息  
使用时复杂度为$O(log_2{n})$
单词查询复杂度$P(log_2^{2}{n})$优越了不少  
总的复杂度$O(nlog_2{n}+Qlog_2^{2}{n})$显然可以解决这道题  
## 对于$[a,b],[c,d]$的端点选择问题  
我们希望得到的中位数越大越好，也就是区间和越大越好  
$[b+1,c-1]$的和是必须取的，$[a,b]$应取右最大连续子序列，  
$[c,d]$应取左最大连续子序列  
就可以尽可能是区间和最大
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#define N 20010
#define MAXN 1000010
#define inf (1<<29)
using namespace std;
inline char nc(){
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
inline void read(int &x)
{
    int s=0,w=1;
    char c=nc();
    while(!isdigit(c)){if(c=='-')w=-1;c=nc();}
    while(isdigit(c)){s=(s<<3)+(s<<1)+c-'0';c=nc();}
    x=s*w;
}
inline void write(int x)
{
    if(x<0)x=-x,putchar('-');
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
struct node
{
    int lmax,rmax,ls,rs,sum;
}t[MAXN];
int cnt,Root[N];
inline void push_up(int root)
{
    t[root].sum=t[t[root].ls].sum+t[t[root].rs].sum;
    t[root].lmax=max(t[t[root].ls].lmax,t[t[root].rs].lmax+t[t[root].ls].sum);
    t[root].rmax=max(t[t[root].rs].rmax,t[t[root].ls].rmax+t[t[root].rs].sum);
}
int build(int l,int r)
{
    int root=++cnt;
    if(l==r)
    {
        t[root].lmax=t[root].rmax=t[root].sum=1;
        return root;
    }
    int mid=(l+r)>>1;
    t[root].ls=build(l,mid);
    t[root].rs=build(mid+1,r);
    push_up(root);
    return root;
}
void insert(int &root,int lastroot,int l,int r,int x,int y)
{
    root=++cnt;
    t[root]=t[lastroot];
    if(l==r)
    {
        t[root].lmax=t[root].rmax=t[root].sum=y;
        return ;
    }
    int mid=(l+r)>>1;
    if(x<=mid)t[root].rs=t[lastroot].rs,insert(t[root].ls,t[lastroot].ls,l,mid,x,y);
    else t[root].ls=t[lastroot].ls,insert(t[root].rs,t[lastroot].rs,mid+1,r,x,y);
    push_up(root);
}
int query_sum(int root,int l,int r,int left,int right)
{
    if(l>=left&&r<=right)return t[root].sum;
    int mid=(l+r)>>1;
    if(right<=mid)return query_sum(t[root].ls,l,mid,left,right);
    else if(left>=mid+1)return query_sum(t[root].rs,mid+1,r,left,right);
    else return query_sum(t[root].ls,l,mid,left,mid)+query_sum(t[root].rs,mid+1,r,mid+1,right);
}
int query_lmax(int root,int l,int r,int left,int right)
{
    if(l>=left&&r<=right)return t[root].lmax;
    int mid=(l+r)>>1;
    if(right<=mid)return query_lmax(t[root].ls,l,mid,left,right);
    else if(left>=mid+1)return query_lmax(t[root].rs,mid+1,r,left,right);
    else return max(query_lmax(t[root].ls,l,mid,left,mid),query_sum(t[root].ls,l,mid,left,mid)+query_lmax(t[root].rs,mid+1,r,mid+1,right));
}
int query_rmax(int root,int l,int r,int left,int right)
{
    if(l>=left&&r<=right)return t[root].rmax;
    int mid=(l+r)>>1;
    if(right<=mid)return query_rmax(t[root].ls,l,mid,left,right);
    else if(left>=mid+1)return query_rmax(t[root].rs,mid+1,r,left,right);
    else return max(query_rmax(t[root].rs,mid+1,r,mid+1,right),query_sum(t[root].rs,mid+1,r,mid+1,right)+query_rmax(t[root].ls,l,mid,left,mid));
}
int n,Q;
int q[4];
inline bool check(int k,int a,int b,int c,int d)
{
    int sum=0;
    if(c-1>=b+1)sum+=query_sum(Root[k],1,n,b+1,c-1);
    sum+=query_rmax(Root[k],1,n,a,b);
    sum+=query_lmax(Root[k],1,n,c,d);
    return sum>=0;
}
struct fafa
{
    int pos,x;
}a[N];
inline bool cmp(const fafa &a,const fafa &b)
{
    return a.x<b.x;
}
int pre;
int main()
{
    read(n);
    for(register int i=1;i<=n;i++)
    {
        read(a[i].x);
        a[i].pos=i;
    }
    sort(a+1,a+n+1,cmp);
    Root[1]=build(1,n);
    for(register int i=2;i<=n+1;i++)
        insert(Root[i],Root[i-1],1,n,a[i-1].pos,-1);
    read(Q);
    while(Q--)
    {
        read(q[0]),read(q[1]),read(q[2]),read(q[3]);
        for(register int i=0;i<4;i++)q[i]=(q[i]+pre)%n;
        sort(q,q+4);
        int l=1,r=n,ans;
        while(l<=r)
        {
            int mid=(l+r)>>1;
            if(check(mid,q[0]+1,q[1]+1,q[2]+1,q[3]+1))l=mid+1,ans=mid;
            else r=mid-1;
        }
        write(a[ans].x),putchar(10),pre=a[ans].x;
    }
}

```

---

## 作者：skydogli (赞：30)

好牛逼的1道题,思路真心不好想

先二分答案$mid$,看到中位数这个东西可以比较容易想到把区间中大于等于$mid$的取1,小于$mid$的取-1,如果区间之和大于等于0(看题,虽然是向下取整但是序号从0开始,其实就是从1开始,向上取整,所以等于0也可以),那么这个区间的中位数就大于等于$mid$.这个东西我们可以用线段树维护,同时也很好维护区间最大前缀和以及区间最大后缀和,统计方式为:

设$suf[x]$为当前区间的最大前缀,$Ls$为左区间,$Rs$为右区间,处理完左右儿子之后:

$$suf[x]=max(suf[Ls],sum[Ls]+suf[Rs])$$
这样我们就能保证$suf$是连着区间开头且是最大的

区间最大后缀$pre[x]$同理:

$$pre[x]=max(pre[Rs],sum[Rs]+pre[Ls])$$

有什么用呢?对于每次询问$a,b,c,d$,$[b,c]$的区间是肯定包含在内的,所以我们要在线段树中查询区间$[b,c]$的和
以及$[a,b-1]$的最大后缀和,$[c+1,d]$的最大前缀和,这样就能组成1个连续的区间,若该区间大于等于0,那么$mid$就合法了.

有没有可能二分出的答案不在区间中呢?不可能,因为假设我们当前的$mid$符合条件但是区间中没有,那么把$mid$增大为区间中出现过的1个更大的数,必定也符合条件,所以最后的答案肯定在区间中出现过.

但是这只是第一步.接下来要解决怎么把区间中的数变成0和1,如果每二分一次都进行该操作,那么复杂度就是单次$O(n)$,每次查询的复杂度就是$O(n\log_2n)$,还不如直接sort呢

于是我们继续思考,一个数$a_i$的贡献由-1变成1是在什么时候呢?只有当$mid$从比$a_i$大变成比$a_i$小的时候,那么我们每次把$mid$增大,只会对$a_i=mid$的位置造成影响,$mid$从最小的$a_i$增大到比最大的$a_i$还大时,每个数的贡献都只会改变1次,其它部分都可以共用.

看到共用,我们就可以想到主席树了,于是我们把所有可能的mid的情况一起先建1棵主席树,那么每个$mid$计算区间和的复杂度就只需要$log_2n$了,所以总时间复杂度$O(n\log_2^2n)$,空间复杂度$O(n\log_2n)$


### 代码
```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
#define MN 20005
#define Ls Tree[x].ls
#define Rs Tree[x].rs
#define getchar() (p1==p2 and (p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<23],*p1=buf,*p2=buf;
inline int read(){
	int a=0;char c=getchar();
	while(c>57 or c<48)c=getchar();
	while(47<c and c<58){
		a=a*10+c-48;
		c=getchar();
	}
	return a;
}//快读
struct tree{
	int sum,pre,suf,ls,rs;
}Tree[MN<<6|1];
//主席树
int v[MN],q[4],n,m,cnt,N,root[MN],a[MN];
//v用于离散化,a用于输入
vector<int>num[MN];//记录每种数出现的位置
int low_bnd(int x){
	int l=1,r=N+1;
	while(l+1<r){
		int mid=(l+r)>>1;
		if(v[mid]>x)r=mid;
			else l=mid;
	}
	return l;
}//手动二分
void change(int &x,int l,int r,int loc,int v){
	Tree[++cnt]=Tree[x];x=cnt;
	if(l==r&&loc==l){Tree[x].sum=v;if(v>0)Tree[x].pre=Tree[x].suf=v;return;}
	if(l>loc||r<loc)return;
	int mid=(l+r)>>1;
	change(Ls,l,mid,loc,v);change(Rs,mid+1,r,loc,v);
	Tree[x].sum=Tree[Ls].sum+Tree[Rs].sum;
	Tree[x].suf=max(Tree[Ls].suf,Tree[Ls].sum+Tree[Rs].suf);
	Tree[x].pre=max(Tree[Rs].pre,Tree[Rs].sum+Tree[Ls].pre);
}//维护区间和,区间最大前缀和,区间最大啊后缀和
int asksum(int x,int l,int r,int b,int e){
	if(b<=l&r<=e)return Tree[x].sum;
	if(b>r||e<l)return 0;
	int mid=(l+r)>>1;
	return asksum(Ls,l,mid,b,e)+asksum(Rs,mid+1,r,b,e);
}//求区间和
int asksuf(int x,int l,int r,int b,int e){
	if(b<=l&&r<=e) return Tree[x].suf;
	if(b>r||e<l)return 0;
	int mid=(l+r)>>1;
	return max(asksum(Ls,l,mid,b,e)+asksuf(Rs,mid+1,r,b,e),asksuf(Ls,l,mid,b,e));
}//求最大前缀
int askpre(int x,int l,int r,int b,int e){
	if(b<=l&&r<=e)return Tree[x].pre;
	if(b>r||e<l)return 0;
	int mid=(l+r)>>1;
	return max(askpre(Ls,l,mid,b,e)+asksum(Rs,mid+1,r,b,e),askpre(Rs,mid+1,r,b,e));
}//求最大后缀
int main(){
	n=read();
	for(int i=1;i<=n;++i){v[i]=a[i]=read();}
	m=read();
	sort(v+1,v+1+n);
	N=unique(v+1,v+1+n)-1-v;
	for(int i=1;i<=n;++i){
		a[i]=low_bnd(a[i]);
		num[a[i]].push_back(i);
	}//离散化,记录各个数字的位置
	for(int i=1;i<=n;++i)change(root[N+1],1,n,i,-1);
	for(int i=N;i;--i){
		root[i]=root[i+1];
		for(int j=0;j<num[i].size();++j){
			change(root[i],1,n,num[i][j],1);
		}
	}
    //建树,不一定是单次O(logn),但是肯定是均摊O(nlogn)的
	int ans=0,a,b,c,d;
	for(int i=1;i<=m;++i){
		a=read();b=read();c=read();d=read();
		q[0]=(a+ans)%n;q[1]=(b+ans)%n;q[2]=(c+ans)%n;q[3]=(d+ans)%n;
		sort(q,q+4);
		a=q[0]+1;b=q[1]+1;c=q[2]+1;d=q[3]+1;
        //
		int l=1,r=N+1;
		while(l+1<r){
			int mid=(l+r)>>1;
			int midans=asksum(root[mid],1,n,b,c);
			int lans=askpre(root[mid],1,n,a,b-1);
			int rans=asksuf(root[mid],1,n,c+1,d);
			if(midans+lans+rans>=0) l=mid;
				else r=mid;
		}
        //二分
		ans=v[l];
		printf("%d\n",v[l]);
	}
	return 0;
} 
```

---

## 作者：ButterflyDew (赞：17)

主席树的想法感觉挺妙的，但是这题数据范围这么小，直接分块草过去不就好了吗

二分是要二分的，把$<x$置$-1$，$\ge x$的置$1$，于是我们需要取一个$\ge 0$的区间

对询问$a,b,c,d$，其中$[b,c]$是必选的,$[a,b-1]$取后缀最大和，$[c+1,d]$取前缀最大和

我们直接分块，对每个块的每个答案$x$维护一个块内和，前缀最大和和后缀最大和就可以了

然后询问的时候暴力跳块就好了

复杂度$O(n\sqrt n+n\sqrt n \log n)$

------

**Code:**

```cpp
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cstring>
#include <algorithm>
const int N=30010;
using std::min;
using std::max;
template <class T>
void read(T &x)
{
	x=0;char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
}
int yuul[200][N],yuur[200][N],bee[200][N],belong[N];
int a[N],b[N],L[200],R[200],qry[5],n,m,q;
int cal(int l,int r,int x)
{
	int lp=belong[l],rp=belong[r],ret=0;
	if(rp-lp<=1)
    {
        for(int i=l;i<=r;i++) ret+=a[i]<x?-1:1;
        return ret;
    }
	for(int i=l;i<=R[lp];i++) ret+=a[i]<x?-1:1;
	for(int i=L[rp];i<=r;i++) ret+=a[i]<x?-1:1;
	for(int i=lp+1;i<rp;i++) ret+=bee[i][x];
	return ret;
}
int rig(int l,int r,int x)
{
	if(l>r) return 0;
	int lp=belong[l],rp=belong[r],sum=0,mx=0;
	if(rp-lp<=1)
	{
		for(int i=l;i<=r;i++)
		{
			sum+=a[i]<x?-1:1;
			mx=max(mx,sum);
		}
		return mx;
	}
	for(int i=l;i<=R[lp];i++)
	{
		sum+=a[i]<x?-1:1;
		mx=max(mx,sum);
	}
	for(int i=lp+1;i<rp;i++)
	{
		mx=max(mx,sum+yuul[i][x]);
		sum+=bee[i][x];
	}
	for(int i=L[rp];i<=r;i++)
	{
		sum+=a[i]<x?-1:1;
		mx=max(mx,sum);
	}
	return mx;
}
int lef(int l,int r,int x)
{
	if(l>r) return 0;
	int lp=belong[l],rp=belong[r],sum=0,mx=0;
	if(rp-lp<=1)
	{
		for(int i=r;i>=l;i--)
		{
			sum+=a[i]<x?-1:1;
			mx=max(sum,mx);
		}
		return mx;
	}
	for(int i=r;i>=L[rp];i--)
	{
		sum+=a[i]<x?-1:1;
		mx=max(sum,mx);
	}
	for(int i=rp-1;i>lp;i--)
	{
		mx=max(mx,sum+yuur[i][x]);
		sum+=bee[i][x];
	}
	for(int i=R[lp];i>=l;i--)
	{
		sum+=a[i]<x?-1:1;
		mx=max(sum,mx);
	}
	return mx;
}
bool check(int a,int b,int c,int d,int x)
{
	return lef(a,b-1,x)+cal(b,c,x)+rig(c+1,d,x)>=0;
}
int query(int a,int b,int c,int d)
{
	int l=1,r=m;
	while(l<r)
	{
		int mid=l+r+1>>1;
		if(check(a,b,c,d,mid)) l=mid;
		else r=mid-1;
	}
	return l;
}
int main()
{
    memset(bee,-0x3f,sizeof bee);
    memset(yuul,-0x3f,sizeof yuul);
    memset(yuur,-0x3f,sizeof yuur);
	read(n);
	for(int i=1;i<=n;i++) read(a[i]),b[i]=a[i];
	std::sort(b+1,b+1+n);
	m=std::unique(b+1,b+1+n)-b-1;
	for(int i=1;i<=n;i++) a[i]=std::lower_bound(b+1,b+1+m,a[i])-b;
	int B=sqrt(n)+1,T=(n-1)/B+1;
	for(int i=1;i<=T;i++)
	{
		L[i]=R[i-1]+1,R[i]=min(L[i]+B-1,n);
		for(int j=L[i];j<=R[i];j++)
		{
			belong[j]=i;
			int sum=0,mx=0,x=a[j];
			for(int k=L[i];k<=R[i];k++)
			{
				sum+=a[k]<x?-1:1;
				mx=max(mx,sum);
			}
			yuul[i][x]=mx;
			sum=0,mx=0;
			for(int k=R[i];k>=L[i];k--)
			{
				sum+=a[k]<x?-1:1;
				mx=max(mx,sum);
			}
			yuur[i][x]=mx;
			bee[i][x]=sum;
		}
		bee[i][m+1]=yuul[i][m+1]=yuur[i][m+1]=-B;
		for(int j=m;j;j--)
		{
			bee[i][j]=max(bee[i][j],bee[i][j+1]);
			yuul[i][j]=max(yuul[i][j],yuul[i][j+1]);
			yuur[i][j]=max(yuur[i][j],yuur[i][j+1]);
		}
	}
	read(q);
	for(int las=0,i=1;i<=q;i++)
	{
		for(int j=1;j<=4;j++)
		{
			read(qry[j]);
			qry[j]=(qry[j]+las)%n+1;
		}
		std::sort(qry+1,qry+5);
		printf("%d\n",las=b[query(qry[1],qry[2],qry[3],qry[4])]);
	}
	return 0;
}
```

---

## 作者：localhost (赞：10)

可以先考虑离散化

离散话后是$1～n$

一般要求中位数可以:

二分中位数$x$

将区间中$<x$的赋值为$-1$,$\ge x$的赋值为$-1$

若区间和为$0$,那么$x$就是中位数

题目是要求左端点在$[a,b]$，右端点在$[c,d]$的序列的最大中位数

区间$[b+1,c-1]$是必选的

我们可以求$[a,b]$的最大后缀和$[c,d]$的最大前缀

如果这三个部分的和大于零，那么当前二分的值是合法的

~~这个一看就可以用线段树维护~~

---

我们再来考虑$x$变成$x+1$会有什么变化：

1. 原来$<x$的还是$-1$
2. 原来$>x$的还是$1$
3. 原来$=x$变成$-1$

所以我们只需修改值为$x$的位置(可以先用链表或$vector$存下所有值为$x$的位置)

其实从小到大排序后按顺序更改就完事了

数离散化后的大小不超过$n$

我们可以先预处理出所有$x$(中位数)对应的线段树

可是空间不够啊

这时候主席树就派上用场了

下面是简洁的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 20011
int n,la=0;
struct node{
    int v,p;
    bool operator<(node x){return v<x.v;}
}b[N];
int ls[N*15],rs[N*15],rt[N],s[N*15],lm[N*15],rm[N*15],sz=0;
void pu(int x){
    s[x]=s[ls[x]]+s[rs[x]];
    lm[x]=max(lm[ls[x]],s[ls[x]]+lm[rs[x]]);
    rm[x]=max(rm[rs[x]],s[rs[x]]+rm[ls[x]]);
}
void build(int l,int r,int &x){
    x=++sz;
    if(l==r){
        s[x]=lm[x]=rm[x]=1;
        return;
    }
    int m=(l+r)>>1;
    build(l,m,ls[x]);build(m+1,r,rs[x]);
    pu(x);
}
void upd(int l,int r,int p,int &x,int pre){
    if(!x)x=++sz;
    if(l==r){
        s[x]=lm[x]=rm[x]=-1;
        return;
    }
    int m=(l+r)>>1;
    if(p<=m)upd(l,m,p,ls[x],ls[pre]),rs[x]=rs[pre];
    else upd(m+1,r,p,rs[x],rs[pre]),ls[x]=ls[pre];
    pu(x);
}
int qs(int L,int R,int l,int r,int x){
    if(L<=l&&r<=R)return s[x];
    int m=(l+r)>>1;
    if(L<=m&&R>m)return qs(L,R,l,m,ls[x])+qs(L,R,m+1,r,rs[x]);
    else if(L<=m)return qs(L,R,l,m,ls[x]);
    else return qs(L,R,m+1,r,rs[x]);
}
struct tr{int s,lm,rm;};
tr operator+(tr x,tr y){
    tr ans;
    ans.s=x.s+y.s;
    ans.lm=max(x.lm,x.s+y.lm);
    ans.rm=max(y.rm,y.s+x.rm);
    return ans;
}
tr qm(int L,int R,int l,int r,int x){
    if(L<=l&&r<=R)return tr{s[x],lm[x],rm[x]};
    int m=(l+r)>>1;
    if(L<=m&&R>m)return qm(L,R,l,m,ls[x])+qm(L,R,m+1,r,rs[x]);
    else if(L<=m)return qm(L,R,l,m,ls[x]);
    else return qm(L,R,m+1,r,rs[x]);
}
void work(){
    int A,B,C,D,q[4];
    scanf("%d%d%d%d",q+0,q+1,q+2,q+3);
    q[0]=(q[0]+la)%n+1;
    q[1]=(q[1]+la)%n+1;
    q[2]=(q[2]+la)%n+1;
    q[3]=(q[3]+la)%n+1;
    sort(q,q+4);
    A=q[0],B=q[1],C=q[2],D=q[3];
    int l=1,r=n,ans;
    while(l<=r){
        int m=(l+r)>>1,tot=0;
        if(B+1<=C-1)tot=qs(B+1,C-1,1,n,rt[m]);
        tot+=qm(A,B,1,n,rt[m]).rm+qm(C,D,1,n,rt[m]).lm;
        if(tot>=0)ans=m,l=m+1;
        else r=m-1;
    }
    printf("%d\n",la=b[ans].v);
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i)scanf("%d",&b[i]),b[i].p=i;
    sort(b+1,b+n+1);
    build(1,n,rt[1]);
    for(int i=2;i<=n;++i)
        upd(1,n,b[i-1].p,rt[i],rt[i-1]);
    int q;scanf("%d",&q);
    while(q--)work();
}
```

---

## 作者：EternalEpic (赞：10)

（调整完格式后，第三次提交。望请批准！）

前置知识：主席树，二分答案，线段树合并左右最大子段和思想。

不会主席树的，跳转：[P3834 【模板】主席树](https://www.luogu.org/problemnew/show/P3834)

不会线段树合并左右最大子段和的，可以去做：[P3792 大母神](https://www.luogu.org/problemnew/show/P3792)

ps：两到紫题再加一个二分就是集训队黑题惹（雾）

看到大家的码风都清奇俊秀（有的用下划线当变量，有的不打空格在压行），我来提供一份比较正常的题解。

看到区间中位数，老司机一般都会想到用二分，num >= mid设1，
num < mid设-1。如果区间和大于0，l = mid + 1 否则 r = mid - 1

但此题，区间不固定（大雾）。我们该如何处理呢？

我们可以重新考虑一下check函数。

以(前区间rmax + 后区间lmax + 必选区间[b + 1, c - 1]的tot 是否>= 0)来判断

Check函数:

```cpp
inline bool check(int id, int A, int B, int C, int D)
{
    int ret = 0;
    if (B + 2 <= C) ret += pst.query(root[id], 1, n, B + 1, C - 1).tot;
    ret += pst.query(root[id], 1, n, A, B).rmax;
    ret += pst.query(root[id], 1, n, C, D).lmax;
    return ret >= 0;
}
```

为什么要这样做，必选区间不说，剩下两区间要是1尽可能多所以如此check了。

而lmax，rmax，和tot就要用主席树维护啦。


```cpp
//Program written by Liu Zhaozhou ~~~
#include <bits/stdc++.h>
#include <algorithm>
#include <queue>
#include <set>
#include <vector>
#include <deque>
#include <string>

#define lowbit(x) x & -x

#pragma GCC optimize(3)

using namespace std;

using namespace std;

namespace Base {
    inline char gc(void)
    {
        static char buf[100000], *p1 = buf, *p2 = buf;
        return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
    }
    
    #define gc() getchar()
        
    template <class T> inline void read(T &x)
    {
        T flag = (T) 1; x = 0; static char ch = gc();
        for (; !isdigit(ch); ch = gc()) if (ch == '-') flag = -1;
        for (; isdigit(ch); ch = gc()) x = x * 10 + ch - 48;
        if (ch == '.') {
            T dgt = 0.1;
            for (ch = gc(); isdigit(ch); ch = gc())
                x = x + dgt * (ch - 48), dgt *= 0.1;
        } x *= flag; return;
    }
    
    template <class T> inline void write(T x) {
        if (x < 0) putchar('-'), x = -x;
        register T y = 1; int len = 1;
        for (; y <= x / 10; y *= 10) ++len;
        for (; len; --len, x %= y, y /= 10) putchar(x / y + 48);
    }
    
    template <class T> inline void writeln(T x) {write(x); puts("");}
    template <class T> inline void writeln(T x, char c) {write(x); putchar(c);}
    template <class T> inline void writeln(char c, T x) {putchar(c); write(x);}
    
    template <class T> inline void chkmax(T &x, const T y) {x > y ? x = x : x = y;}
    template <class T> inline void chkmin(T &x, const T y) {x < y ? x = x : x = y;}
    
    typedef long long ll;
    typedef unsigned long long ull;
    typedef double ld;
    
    #define Ms(arr, opt) memset(arr, opt, sizeof(arr))
    #define Mp(x, y) make_pair(x, y)
    
    inline void file(string str) {
        freopen((str + ".in").c_str(), "r", stdin);
        freopen((str + ".out").c_str(), "w", stdout);
    }
}

using namespace Base;

enum {
    Maxn = 20005
};

int n, cnt, m, lastans, q[4], root[Maxn];
struct State {
public:
    int id, num;
    inline bool operator < (const State&x) const{
        return num < x.num;
    }
} a[Maxn << 2 | 1];

class Info {
public:
    int tot, lmax, rmax;
    inline Info operator + (const Info&opt)
    const {
        return (Info) {
            tot + opt.tot,
            max(lmax, tot + opt.lmax),
            max(opt.rmax, opt.tot + rmax)
        };
    }
    inline void Init(int _t, int _l, int _r) {
    	tot = _t, lmax = _l, rmax = _r;
	}
};
class Node {
public:
    int ls, rs; Info sum;
} t[Maxn * 40 + 5];

class PST {
public:
    inline void pushup(int pos) {
        t[pos].sum = t[t[pos].ls].sum + t[t[pos].rs].sum;
    }
    
    inline void build(int &u, int l, int r) {
        int tmp = u; u = ++cnt; t[u] = t[tmp];
    	if (l == r) {t[u].sum.Init(1, 1, 1); return;}
    	int mid = l + r >> 1;
    	build(t[u].ls, l, mid),
    	build(t[u].rs, mid + 1, r);
    	pushup(u);
    }
    
    inline void modify(int &u, int l, int r, int x) {
    	int tmp = u; u = ++cnt; t[u] = t[tmp];
    	if (l == r) {t[u].sum.Init(-1, -1, -1); return;}
    	int mid = l + r >> 1;
    	if (x <= mid) modify(t[u].ls, l, mid, x);
    	else modify(t[u].rs, mid + 1, r, x);
    	pushup(u);
    }
    
    inline Info query(int u, int l, int r, int L, int R) {
    	if (L <= l && r <= R) return t[u].sum;
    	int mid = l + r >> 1;
    	if (R <= mid) return query(t[u].ls, l, mid, L, R);
    	else if (mid < L) return query(t[u].rs, mid + 1, r, L, R);
    	else return query(t[u].ls, l, mid, L, mid)
         + query(t[u].rs, mid + 1, r, mid + 1, R);
    }
} pst;

inline bool check(int id, int A, int B, int C, int D)
{
    int ret = 0;
    if (B + 2 <= C) ret += pst.query(root[id], 1, n, B + 1, C - 1).tot;
    ret += pst.query(root[id], 1, n, A, B).rmax;
    ret += pst.query(root[id], 1, n, C, D).lmax;
    return ret >= 0;
}

signed main(void) {
    //file("PST");
    read(n);
    for (int i = 1; i <= n; i++)
        read(a[i].num), a[i].id = i;
        
    sort(a + 1, a + n + 1);
    pst.build(root[1], 1, n);
    for (int i = 2; i <= n; i++)
        root[i] = root[i - 1],
        pst.modify(root[i], 1, n, a[i - 1].id);
    
    read(m);
    while (m--) {
        for(int i = 0; i < 4; i++)
            read(q[i]), q[i] = (q[i] + lastans) % n + 1;
        sort(q, q + 4); 
        
        int l = 1, r = n, mid, ans;
        while(l <= r){
            mid = l + r >> 1;
            if (check(mid, q[0], q[1], q[2], q[3]))
                ans = mid, l = mid + 1;
            else r = mid - 1;
        }
        writeln(lastans = a[ans].num);
    }
    return 0;
}
/**/


```

谢谢兹磁！


---

## 作者：lcjqwq (赞：7)

### Description
给你一个序列，每次询问给出四个数 $a,b,c,d$，求所有区间 $[l,r]$ 满足 $l \in [a,b], r \in [c,d]$ 的中位数的最大值。强制在线

$n \leq 20000, Q \leq 25000,a_i \leq 10^9$

### Solution

考虑二分答案。假设现在二分出来的是 $x$ ，那么把 $\ge x$ 的位置设成 $1$ ，$< x$ 的设为 $-1$ 。那么一个区间的中位数 $\ge x$ 等价于这个区间的和 $\ge 0$

如何处理题目给的左右端点的限制？

可以发现 $[l,r]$ 必然包含 $[b+1,c-1]$ (如果 $b+1 \leq c+1$ 的话）所以 $[l, r]$ 的和必然包含 $[b+1, c-1]$ 的和

显然让 $[l,r]$ 的和最大的方案是取 $[a,b]$ 的最大右段和 和 $[c,d]$ 的最大左段和

这些都可以用线段树维护。但这样需要每个数都开一颗线段树，空间爆炸。

把数组排序，这样每个数的线段树显然只是由前一个数的线段树把一个点的权值从 $1$ 改为 $-1$ 。可以使用主席树的思想（貌似就是主席树

然后就做完了。复杂度 $O(m \log^2 n)$ 

### Code
[看代码戳这里](https://acfunction.github.io/2019/01/20/BZOJ2653/)

---

## 作者：Itst (赞：4)

#### 第一篇黑题题解有些小激动，题解有点啰嗦大佬勿喷qwq
## 这道题对于加深对主席树的理解（而不是只停留在静态区间第K大上）有很大的帮助！！！
#### $30pts$做法：
#### 枚举左右端点并维护中位数，可以使用对顶堆或者区间第K大形式的主席树
#### 复杂度都是$O(n^2Qlog_2n)$，加一些玄学卡常或许可以多过一两个测试点
#### 期望得分30，实际得分0-30不等？
### $100pts$正解：
### 观察$100 \%$的数据规模，$n,Q$的规模都达到了$2 \times 10^4,O(nQ)$的做法都比较吃力，所以考虑使用log数据结构进行维护获得$O(Qlog_2n)$或者$O(Qlog_2^2n)$的算法。
### 故考虑到使用线段树进行维护，同时使用二分的方式寻找每个询问的答案，
### 其中check的内容就是寻找是否有满足该询问条件的区间，在其中（大于等于当前二分的数的数字个数）要大于等于（小于当前二分的数的数字个数）。~~（断句略奇怪）~~
### 不妨将大于等于当前二分的数的数字的权值设为1，小于当前二分的数的数字的权值设为-1，check的内容就等价于询问
### $max(\sum_{i=x}^y w_i) \geq 0 (x \in {[a , b]} , y \in{[c , d]})$
### 是否成立。
### 所以想到对于每个数字建立一个线段树存储权值，在每一次二分询问时求出对应线段树中$x \in {[a , b]} , y \in{[c , d]},\sum_{i=b+1}^{c-1} w_i + max(\sum_{i=x}^b w_i)+max(max(\sum_{i=c}^y w_i))$是否大于0，刚好这三个式子对应区间和、区间最大后缀、区间最大前缀，可以使用线段树解决。
### 然后会发现空间爆炸，然后发现排完序后从第$i$个线段树到第$i+1$个线段树只有一个点权值从$1$变为$-1$，然后就可以用主席树进行维护，然后就可以happy地切掉这道题了
### 时间复杂度为$O(Qlog_2^2n)$，符合本题数据范围
### 接下来的代码奇丑无比，下面的很多dalao比我写得好多了qwq
```
#include<bits/stdc++.h>
#define MAXN 100002
using namespace std;
inline int read(){
    int a = 0;
    bool f = 0;
    char c = getchar();
    while(!isdigit(c)){
        if(c == '-')
            f = 1;
        c = getchar();
    }
    while(isdigit(c)){
        a = (a << 3) + (a << 1) + (c ^ '0');
        c = getchar();
    }
    return f ? -a : a;
}
char output[12];
inline void print(int x){
    int dirN = 11;
    if(x == 0)
    	fwrite("0" , sizeof(char) , 1 , stdout);
    else{
    	if(x < 0){
    		x = -x;
    		fwrite("-" , sizeof(char) , 1 , stdout);
        }
        while(x){
       	    output[--dirN] = x % 10 + 48;
    	    x /= 10;
    	}
    	fwrite(output + dirN , 1 , strlen(output + dirN) , stdout);
    }
    fwrite("\n" , 1 , 1 , stdout);
}
struct node{
    int sum , lMax , rMax , l , r;
}Tree[22 * MAXN];
struct sortNum{//用于排序
    int ind , num;
    bool operator <(sortNum a){
        return num < a.num;
    }
}sorted[MAXN];
int num[MAXN] , root[MAXN];
int N , cntNode = 1 , rMax , rSum , lMax , lSum;

inline int max(int a , int b){
    return a > b ? a : b;
}

inline void swap(int &a , int &b){
    int t = a;
    a = b;
    b = t;
}

//初始化一个所有叶子结点权值都为1的线段树
void init(int dir , int l , int r){
    Tree[dir].sum = Tree[dir].lMax = Tree[dir].rMax = r - l + 1;
    if(l != r){
        init(Tree[dir].l = ++cntNode , l , l + r >> 1);
        init(Tree[dir].r = ++cntNode , (l + r >> 1) + 1 , r);
    }
}

inline void pushup(int dir){
    Tree[dir].lMax = max(Tree[Tree[dir].l].lMax , Tree[Tree[dir].l].sum + Tree[Tree[dir].r].lMax);
    Tree[dir].rMax = max(Tree[Tree[dir].r].rMax , Tree[Tree[dir].r].sum + Tree[Tree[dir].l].rMax);
    Tree[dir].sum = Tree[Tree[dir].l].sum + Tree[Tree[dir].r].sum;
}

//更新版本
void update(int now , int last , int l , int r , int dir){
    if(l == r){
        Tree[now].lMax = Tree[now].rMax = 0;
        Tree[now].sum = -1;
    }
    else{
        if(dir > l + r >> 1){
            Tree[now].l = Tree[last].l;
            update(Tree[now].r = ++cntNode , Tree[last].r , (l + r >> 1) + 1 , r , dir);
        }
        else{
            Tree[now].r = Tree[last].r;
            update(Tree[now].l = ++cntNode , Tree[last].l , l , l + r >> 1 , dir);
        }
        pushup(now);
    }
}

//区间和
int findSum(int dir , int l , int r , int L , int R){
    if(L >= l && R <= r)
        return Tree[dir].sum;
    int sum = 0;
    if(l <= L + R >> 1)
        sum += findSum(Tree[dir].l , l , r , L , L + R >> 1);
    if(r > R + L >> 1)
        sum += findSum(Tree[dir].r , l , r , (L + R >> 1) + 1 , R);
    return sum;
}

//区间最大后缀
void findRightMax(int dir , int l , int r , int L , int R){
    if(L >= l && R <= r){
        rMax = max(rMax , Tree[dir].rMax + rSum);
        rSum += Tree[dir].sum;
        return;
    }
    if(r > L + R >> 1)
        findRightMax(Tree[dir].r , l , r , (L + R >> 1) + 1 , R);
    if(l <= L + R >> 1)
        findRightMax(Tree[dir].l , l , r , L , L + R >> 1);
}

//区间最大前缀
void findLeftMax(int dir , int l , int r , int L , int R){
    if(L >= l && R <= r){
        lMax = max(lMax , Tree[dir].lMax + lSum);
        lSum += Tree[dir].sum;
        return;
    }
    if(l <= L + R >> 1)
        findLeftMax(Tree[dir].l , l , r , L , L + R >> 1);
    if(r > L + R >> 1)
        findLeftMax(Tree[dir].r , l , r , (L + R >> 1) + 1 , R);
}

//二分check
//为了方便处理这里的代码与上面的公式稍有不同
inline bool check(int mid , int a , int b , int c , int d){
    lSum = rSum = 0;
    lMax = rMax = -1;
    findRightMax(root[mid] , a , b - 1 , 1 , N);
    findLeftMax(root[mid] , c + 1 , d , 1 , N);
    return findSum(root[mid] , b , c , 1 , N) + lMax + rMax >= 0;
}

int main(){
    N = read();
    long long lastans = 0;
    for(int i = 1 ; i <= N ; i++)
        num[sorted[i].ind = i] = sorted[i].num = read();
    init(root[1] = 1 , 1 , N);
    sort(sorted + 1 , sorted + N + 1);
    for(int i = 1 ; i <= N ; i++)
        update(root[i + 1] = ++cntNode , root[i] , 1 , N , sorted[i].ind); 
    for(int Q = read() ; Q ; Q--){
        int a = (read() + lastans) % N + 1 , b = (read() + lastans) % N + 1 , c = (read() + lastans) % N + 1 , d = (read() + lastans) % N + 1;
        if(a > b)
            swap(a , b);
        if(a > c)
            swap(a , c);
        if(a > d)
            swap(a , d);
        if(b > c)
            swap(b , c);
        if(b > d)
            swap(b , d);
        if(c > d)
            swap(c , d);
        int l = 1 , r = N;
        while(l < r){
            int mid = l + r + 1 >> 1;
            if(check(mid , a , b , c , d))
                l = mid;
            else
                r = mid - 1;
        }
        printf("%d\n" , lastans = sorted[l].num);
    }
    return 0;
}
```
### ~~话说模拟赛考这个，题解中赫然写上了“防AK题”我也是很mengbi的~~

---

## 作者：hychyc (赞：4)

题意：给你一个长度为n的序列s。

回答Q个这样的询问：s的左端点在[a,b]之间,右端点在[c,d]之间的子序列中，最大的中位数。
强制在线。

思路：首先考虑二分答案，判断可行的方法则是看是否大于他的数可以比小于他的数多。则考虑对于[b+1, c-1]直接求出来，对于[a, b]求最大的大的减小的后缀，[c, d]求最大前缀，可以建线段树维护。对于每一个数建一个线段树，则空间爆了,考虑使用主席树维护

做法：对于第i颗主席树，则是小于 i 的都是-1，大于等于i的是1，查询的时候二分答案查询在排名i的这颗主席树上是否能选出序列使得和大于等于0

https://www.luogu.org/problemnew/show/P2839

```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define MAXN 20050
using namespace std;
inline int read(){
    int f = 1, ret = 0; char ch = getchar();
    while(ch < '0' || ch > '9') if(ch == '-') f = -1, ch = getchar();
    while(ch >= '0' && ch <= '9') ret = ret*10+int(ch-'0'), ch = getchar();
    return ret*f;
}
void print(int x){
    if(x < 10) putchar(x+'0');
    else{
        print(x/10);
        putchar(x%10+'0');
    }
}
int n, cnt, Q, lastans, q[4], root[MAXN];
struct node1{
    int id, num;
    bool operator < (const node1 &x) const{
        return num < x.num;
    }
    node1(){}
    node1(int _id, int _num){
        id = _id, num = _num;
    }
}a[MAXN<<2];
struct data{
    int lmax, rmax, tot;
};
struct node{
    int ls, rs;
    data d;
}t[MAXN<<6];
data merge(data a, data b){
    data ret;
    ret.tot = a.tot + b.tot;
    ret.lmax = max(a.lmax, a.tot + b.lmax);
    ret.rmax = max(b.rmax, b.tot + a.rmax);
    return ret;
}
void build(int &u, int l, int r){
    int tmp = u; u = ++cnt; t[u] = t[tmp];
    if(l == r) {t[u].d.tot = t[u].d.lmax = t[u].d.rmax = 1; return;}
    int mid = (l+r)>>1;
    build(t[u].ls, l, mid);
    build(t[u].rs, mid+1, r);
    t[u].d = merge(t[t[u].ls].d, t[t[u].rs].d);
}
void update(int &u, int l, int r, int x){
    int tmp = u; u = ++cnt; t[u] = t[tmp];
    if(l == r){t[u].d.tot = t[u].d.lmax = t[u].d.rmax = -1; return;}
    int mid = (l+r)>>1;
    if(x <= mid) update(t[u].ls, l, mid, x);
    else update(t[u].rs, mid+1, r, x);
    t[u].d = merge(t[t[u].ls].d, t[t[u].rs].d);
}
data query(int u, int l, int r, int tl, int tr){
    if(tl <= l && r <= tr) return t[u].d;
    int mid = (l+r)>>1;
    if(tr <= mid) return query(t[u].ls, l, mid, tl, tr);
    if(mid < tl) return query(t[u].rs, mid+1, r, tl, tr);
    else return merge(query(t[u].ls, l, mid, tl, tr), query(t[u].rs, mid+1, r, tl, tr));
}
bool check(int id, int l1, int r1, int l2, int r2){
    int ret = 0;
    if(r1+1 <= l2-1) ret += query(root[id], 1, n, r1+1, l2-1).tot;
    ret += query(root[id], 1, n, l1, r1).rmax;
    ret += query(root[id], 1, n, l2, r2).lmax;
    //printf("%d %d\n", id, ret);
    return ret>=0;
}
/*
输入格式：
第一行序列长度n。
接下来n行按顺序给出a中的数。
接下来一行Q
然后Q行每行a,b,c,d，我们令上个询问的答案是x(如果这是第一个询问则x=0)。
令数组q={(a+x)%n,(b+x)%n,(c+x)%n,(d+x)%n}。

将q从小到大排序之后，令真正的要询问的a=q[0],b=q[1],c=q[2],d=q[3]。
n<=20000,Q<=25000*/
int main(){
    //freopen("1.in", "r", stdin);
    //freopen("1.out", "w", stdout);
    scanf("%d", &n);
    //n = read();
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i].num); a[i].id = i;
        //a[i] = node1(i, read());
    }
    sort(a+1, a+n+1);
    build(root[1], 1, n);
    for(int i = 2; i <= n; i++) root[i] = root[i-1], update(root[i], 1, n, a[i-1].id);
    scanf("%d", &Q);//Q = read();
    while(Q--){
        for(int i = 0; i < 4; i++) scanf("%d", &q[i]), q[i] = (q[i]+lastans)%n;//q[i] = (read()+lastans)%n;
        sort(q, q+4); for(int i = 0; i < 4; i++) q[i]++;
        int l = 1, r = n, mid, ans;
        while(l <= r){
            mid = (l+r)>>1;
            if(check(mid, q[0], q[1], q[2], q[3])) ans = mid, l = mid+1;
            else r = mid-1;
        }
        printf("%d\n", lastans = a[ans].num);
        //print(lastans = a[ans].num); putchar('\n'); 
    }
    return 0;
}
```

---

## 作者：nofind (赞：3)

题意：https://www.luogu.org/problem/P2839

假设是找区间中位数(即$a=b$,$c=d$的情况):

二分答案$mid$,将$>mid$的数置为$-1$,小于等于$mid$的数置为$1$,查询区间和,$>=0$说明众数$>=mid$,反之则众数小于$mid$

但是对每一个值开一个线段树是不可能的,发现x和x+1(离散化后)的线段树指有等于x的位置不同(x+1的是-1,x的是1),可以用主席树解决

考虑有了限制怎么做

要求是最大的中位数,那么对于二分的值,求出的区间和越大越好,对每个区间记录最大前缀$lmax$,最大后缀$rmax$和区间和$sum$,查询是取$[a,b-1]$的$rmax$,$[b,c]$的$sum$,$[c+1,d]$的$lmax$即可

code:
```
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
#define lc(p) (seg[p].lc)
#define rc(p) (seg[p].rc)
#define sum(p) (seg[p].sum)
#define lmax(p) (seg[p].lmax)
#define rmax(p) (seg[p].rmax)
const int maxn=20010;
int n,m,tot,lastans,aa,bb,cc,dd;;
int a[maxn],b[maxn],root[maxn];
vector<int>pos[maxn];
struct Seg
{
	int lc,rc;
	int sum,lmax,rmax;
}seg[maxn*60];
inline bool	cmp(int x,int y){return a[x]<a[y];}
inline void	up(int p)
{
	sum(p)=sum(lc(p))+sum(rc(p));
	lmax(p)=max(lmax(lc(p)),sum(lc(p))+lmax(rc(p)));
	rmax(p)=max(rmax(rc(p)),sum(rc(p))+rmax(lc(p)));
}
void build(int &p,int l,int r)
{
	p=++tot;
	if(l==r){sum(p)=lmax(p)=rmax(p)=-1;return;}
	int mid=(l+r)>>1;
	build(lc(p),l,mid);build(rc(p),mid+1,r);
	up(p);
}
void insert(int pre,int &p,int L,int R,int pos)
{
	if(!p)p=++tot;
	if(L==R){sum(p)=lmax(p)=rmax(p)=1;return;}
	int mid=(L+R)>>1;
	if(pos<=mid)rc(p)=rc(pre),insert(lc(pre),lc(p),L,mid,pos);
	else lc(p)=lc(pre),insert(rc(pre),rc(p),mid+1,R,pos);
	up(p);
}
Seg query(int p,int L,int R,int l,int r)
{
	if(L>=l&&R<=r)return seg[p];
	int mid=(L+R)>>1;
	if(l>mid)return query(rc(p),mid+1,R,l,r);
	else if(r<=mid)return query(lc(p),L,mid,l,r);
	else 
	{
		Seg ans,lson=query(lc(p),L,mid,l,r),rson=query(rc(p),mid+1,R,l,r);
		ans.sum=(lson.sum+rson.sum);
		ans.lmax=max(lson.lmax,lson.sum+rson.lmax);
		ans.rmax=max(rson.rmax,rson.sum+lson.rmax);
		return ans; 	
	}
}
inline bool check(int mid)
{
	//printf("test::%d %d %d %d %d\n",aa,bb,cc,dd,b[mid]);
	int res=0;Seg ans;
	ans=query(root[mid],1,n,aa,bb);res+=ans.rmax;
	//printf("rmax::%d ",ans.rmax);
	if(bb+1<=cc-1)ans=query(root[mid],1,n,bb+1,cc-1),res+=ans.sum;
	ans=query(root[mid],1,n,cc,dd);res+=ans.lmax;
	//printf("lmax::%d \n",ans.lmax);
	return res>=0;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),b[i]=i;
	sort(b+1,b+n+1,cmp);//int cnt=unique(b+1,b+cnt+1)-(b+1);
	build(root[n+1],1,n);
	for(int i=n;i;i--)insert(root[i+1],root[i],1,n,b[i]);
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d%d",&aa,&bb,&cc,&dd);
		aa=(aa+lastans)%n+1;bb=(bb+lastans)%n+1;
		cc=(cc+lastans)%n+1;dd=(dd+lastans)%n+1;
		int tmp[5]={0,aa,bb,cc,dd};
		sort(tmp+1,tmp+4+1);
		aa=tmp[1],bb=tmp[2],cc=tmp[3],dd=tmp[4];
		int l=1,r=n,ans;
		while(l<=r)
		{
			//puts("!!");
			int mid=(l+r)>>1;
			if(check(mid))ans=mid,l=mid+1;
			else r=mid-1;
		}
		printf("%d\n",lastans=a[b[ans]]);
	}
	return 0;
}
```


---

## 作者：mrclr (赞：3)

有谁能想到这题会用到主席树呢（~~某大佬：“我”~~）？（不愧是WJMZBMR出的题）

首先考虑如果区间是固定的话，中位数该怎么求。
没错，二分。如果大于当前二分值$mid$的数比小于$mid$的数多，说明$mid$还可以再变大，向右二分；否则向左二分。

如果我们把小于$mid$的数都标记成$-1$，大于的标记成$1$，那么只用判断这个区间的和是否$\geqslant 0$就行了。

但现在区间不固定。首先$[b + 1, c - 1]$是一定要选的。对于$[a, b]$和$[c, d]$，因为要让中位数尽量大，所以应该选$[a, b]$的最大后缀和以及$[c, d]$的最大前缀和。

主要思路就是这些，但单次查询的复杂度是$O(n \log{n})$的，过不了。得想办法优化。

如果对每一个二分的值建一棵区间线段树（这里的二分在序列中的值中进行就行，而不是$1$到$1e9$，所以只用建$n$棵），把小于他的都标记成$1$，大于标记成$-1$，那么每一次查询就能达到$O(\log ^ 2{n})$了。

但是很显然这样空间开不下，而且预处理复杂度过高。所以现在得想办法减少预处理的时间。

如果把序列中的数排一个序，会发现对于相邻的两个不一样的数（因为数字可能有重），建的线段树只有一处不一样，而这一处不一样只会导致线段树中的一条链改变。所以我们只要单独把这条链提建出来就行了。

然后就会发现这其实就是一棵主席树呀。

于是这题就写完了。
```c++
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<vector>
#include<stack>
#include<queue>
using namespace std;
#define enter puts("") 
#define space putchar(' ')
#define Mem(a, x) memset(a, x, sizeof(a))
#define rg register
typedef long long ll;
typedef double db;
const int INF = 0x3f3f3f3f;
const db eps = 1e-8;
const int maxn = 2e4 + 5;
const int maxt = 2e6 + 5;
inline ll read()
{
  ll ans = 0;
  char ch = getchar(), last = ' ';
  while(!isdigit(ch)) {last = ch; ch = getchar();}
  while(isdigit(ch)) {ans = (ans << 1) + (ans << 3) + ch - '0'; ch = getchar();}
  if(last == '-') ans = -ans;
  return ans;
}
inline void write(ll x)
{
  if(x < 0) x = -x, putchar('-');
  if(x >= 10) write(x / 10);
  putchar(x % 10 + '0');
}

int n, _n, m, a[maxn], b[maxn], q[4];
vector<int> v[maxn];

struct Tree
{
  int ls, rs;
  int sum, lmax, rmax;
}t[maxt];
int root[maxn], cnt = 0;
void pushup(int now)
{
  t[now].sum = t[t[now].ls].sum + t[t[now].rs].sum;
  t[now].lmax = max(t[t[now].ls].lmax, t[t[now].ls].sum + t[t[now].rs].lmax);
  t[now].rmax = max(t[t[now].rs].rmax, t[t[now].rs].sum + t[t[now].ls].rmax);
}
void build(int& now, int l, int r)
{
  if(!now) now = ++cnt;
  if(l == r) {t[now].sum = t[now].lmax = t[now].rmax = 1; return;}
  int mid = (l + r) >> 1;
  build(t[now].ls, l, mid);
  build(t[now].rs, mid + 1, r);
  pushup(now);
}
void insert(int old, int& now, int l, int r, int id)
{
  t[now = ++cnt] = t[old];
  if(l == r) {t[now].sum = t[now].lmax = t[now].rmax = -1; return;}
  int mid = (l + r) >> 1;
  if(id <= mid) insert(t[old].ls, t[now].ls, l, mid, id);
  else insert(t[old].rs, t[now].rs, mid + 1, r, id);
  pushup(now);
}
int querySum(int now, int l, int r, int L, int R)
{
  if(R < L) return 0;
  if(l == L && r == R) return t[now].sum;
  int mid = (l + r) >> 1;
  if(R <= mid) return querySum(t[now].ls, l, mid, L, R);
  else if(L > mid) return querySum(t[now].rs, mid + 1, r, L, R);
  else return querySum(t[now].ls, l, mid, L, mid) + querySum(t[now].rs, mid + 1, r, mid + 1, R);
}
int queryL(int now, int l, int r, int L, int R)
{
  if(l == L && r == R) return t[now].lmax;
  int mid = (l + r) >> 1;
  if(R <= mid) return queryL(t[now].ls, l, mid, L, R);
  else if(L > mid) return queryL(t[now].rs, mid + 1, r, L, R);
  else
    {
      int ret1 = queryL(t[now].ls, l, mid, L, mid);
      int ret2 = querySum(t[now].ls, l, mid, L, mid) + queryL(t[now].rs, mid + 1, r, mid + 1, R);
      return max(ret1, ret2);
    }
}
int queryR(int now, int l, int r, int L, int R)
{
  if(l == L && r == R) return t[now].rmax;
  int mid = (l + r) >> 1;
  if(R <= mid) return queryR(t[now].ls, l, mid, L, R);
  else if(L > mid) return queryR(t[now].rs, mid + 1, r, L, R);
  else
    {
      int ret1 = queryR(t[now].rs, mid + 1, r, mid + 1, R);
      int ret2 = querySum(t[now].rs, mid + 1, r, mid + 1, R) + queryR(t[now].ls, l, mid, L, mid);
      return max(ret1, ret2);
    }
}

bool judge(int x)
{
  int ans1 = querySum(root[x], 1, n, q[1] + 1, q[2] - 1);
  int ans2 = queryR(root[x], 1, n, q[0], q[1]);
  int ans3 = queryL(root[x], 1, n, q[2], q[3]);
  return ans1 + ans2 + ans3 >= 0;
}
int solve()
{
  int L = 1, R = _n;
  while(L < R)
    {
      int mid = (L + R + 1) >> 1;
      if(judge(mid)) L = mid;
      else R = mid - 1;
    }
  return L;
}

int main()
{
  n = read();
  build(root[0], 1, n);
  for(int i = 1; i <= n; ++i) a[i] = b[i] = read();
  sort(b + 1, b + n + 1);
  _n = unique(b + 1, b + n + 1) - b - 1;
  for(int i = 1; i <= n; ++i)
    {
      a[i] = lower_bound(b + 1, b + _n + 1, a[i]) - b;
      v[a[i]].push_back(i);
    }
  for(int i = 1; i <= _n; ++i)
    {
      root[i] = root[i - 1];
      for(int j = 0; j < (int)v[i - 1].size(); ++j)
	insert(root[i], root[i], 1, n, v[i - 1][j]);
    }
  m = read();
  for(int i = 1, ans = 0; i <= m; ++i)
    {
      for(int j = 0; j < 4; ++j) q[j] = read();
      for(int j = 0; j < 4; ++j) q[j] = (q[j] + ans) % n + 1;
      sort(q, q + 4);
      ans = b[solve()];
      write(ans), enter;
    }
  return 0;
}
```

---

## 作者：徐致远 (赞：0)

[本蒟蒻的Blog](https://www.chnxuzhiyuan.cn/2019/03/29/%E3%80%8C%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F%E3%80%8Dmiddle-Solution/)

丽洁姐的题目，不错不错。


### 题解

这题还是挺好玩的。

首先可以二分枚举答案。设当前枚举到的答案为$mid$，那么就把大于等于当前答案的数标为1，小于的标为-1。如果两个端点分别在指定区间内的加和最大的区间的加和大于等于0，那么当前二分到的值可以再大一些，否则就应该小一些。

由于最后的区间必然包括$[b+1,c-1]$，所以需要求出区间$[a,b]$的最大后缀和以及区间$[c,d]$的最大前缀和。

先对原序列离散化，这样最后可能二分到的答案就只剩下$n$个。然以后对于每一个可能二分到的答案，将以它为基准构造出的由1和-1组成的序列预处理出来，用线段树就可以维护一个区间的加和、最大前缀和、最大后缀和。但是这样复杂度是爆炸的。所以可以先排序，然后由于每次按顺序修改基准数只会将一个位置的值由1改为-1，所以用主席树维护就好了。

原序列中可能有相同元数字，注意细节即可。

### 代码

```cpp
#include<map>
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=20005,LOG=16;
int n,Q,cnt,A[maxn],id[maxn],q[10],ans;map<int,int> CR;
inline int read()
{
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9'){ret=ret*10+ch-'0';ch=getchar();}
	return ret*f;
}
struct ChairmanTree
{
	int tot,R[maxn];
	struct Node{int L,R,Sum,FMS,BMS;}Tree[maxn*2*LOG];
	inline void PushUp(int rt)
	{
		Tree[rt].Sum=Tree[Tree[rt].L].Sum+Tree[Tree[rt].R].Sum;
		Tree[rt].FMS=max(Tree[Tree[rt].L].FMS,Tree[Tree[rt].L].Sum+Tree[Tree[rt].R].FMS);
		Tree[rt].BMS=max(Tree[Tree[rt].R].BMS,Tree[Tree[rt].R].Sum+Tree[Tree[rt].L].BMS);
	}
	inline int New(){return ++tot;}
	void Build(int rt,int L=1,int R=n)
	{
		if(L==R){Tree[rt].Sum=Tree[rt].FMS=Tree[rt].BMS=1;return;}
		Tree[rt].L=New();
		Tree[rt].R=New();
		int M=(L+R)>>1;
		Build(Tree[rt].L,L,M);
		Build(Tree[rt].R,M+1,R);
		PushUp(rt);
	}
	void Update(int rt,int pre,int p,int L=1,int R=n)
	{
		if(L==R){Tree[rt].Sum=Tree[rt].FMS=Tree[rt].BMS=-1;return;}
		Tree[rt]=Tree[pre];
		int M=(L+R)>>1;
		if(p<=M)
		{
			Tree[rt].L=New();
			Update(Tree[rt].L,Tree[pre].L,p,L,M);
		}
		if(M<p)
		{
			Tree[rt].R=New();
			Update(Tree[rt].R,Tree[pre].R,p,M+1,R);
		}
		PushUp(rt);
	}
	Node Query(int rt,int LL,int RR,int L=1,int R=n)
	{
		if(LL>RR){return (Node){0,0,0,0,0};}
		if(LL<=L&&R<=RR) return Tree[rt];
		int M=(L+R)>>1;Node IL,IR,ret;
		if(LL<=M) IL=Query(Tree[rt].L,LL,RR,L,M);
		if(M<RR) IR=Query(Tree[rt].R,LL,RR,M+1,R);
		if(LL<=M&&M>=RR) return IL;
		if(LL>M&&M<RR) return IR;
		ret.Sum=IL.Sum+IR.Sum;
		ret.FMS=max(IL.FMS,IL.Sum+IR.FMS);
		ret.BMS=max(IR.BMS,IR.Sum+IL.BMS);
		return ret;
	}
}CT;
inline bool cmp(int x,int y){return A[x]<A[y];}
inline void Solve(int a,int b,int c,int d)
{
	int L=1,R=n,mid;
	while(L<=R)
	{
		mid=(L+R)>>1;
		ChairmanTree::Node IL=CT.Query(CT.R[CR[A[id[mid]]]],a,b),IM=CT.Query(CT.R[CR[A[id[mid]]]],b+1,c-1),IR=CT.Query(CT.R[CR[A[id[mid]]]],c,d);
		IL.BMS+IM.Sum+IR.FMS>=0?L=mid+1:R=mid-1;
	}
	ans=A[id[R]];
	printf("%d\n",ans);
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++) A[i]=read();
	for(int i=1;i<=n;i++) id[i]=i;
	sort(id+1,id+1+n,cmp);
	CT.R[1]=CT.New();CT.Build(1);CR[A[id[1]]]=1;
	for(int i=2;i<=n;i++)
	{
		CT.R[i]=CT.New();
		if(!CR[A[id[i]]]) CR[A[id[i]]]=i;
		CT.Update(CT.R[i],CT.R[i-1],id[i-1]);
	}
	Q=read();
	while(Q--)
	{
		q[1]=(read()+ans)%n+1;q[2]=(read()+ans)%n+1;q[3]=(read()+ans)%n+1;q[4]=(read()+ans)%n+1;
		sort(q+1,q+1+4);
		Solve(q[1],q[2],q[3],q[4]);
	}
	return 0;
}
```



---

## 作者：xudaxia (赞：0)

### [国家集训队]middle  
二分答案想到了，然后小于的为-1，大于等于的为1，中间一块加上，一个最大前缀，一个最大后缀的套路也知道，然后就不会了。    
~~听说是陈立杰出的题~~    
然后该怎么办？上主席树，我们一个初步的想法是每一个权值，都建一颗1和-1的普通线段树上面维护区间和，区间最大前缀，最大后缀。然后我们发现，相邻两个权值的线段树，很相近，只有一个权值的点不一样，只需要改$logn$个节点，然后就是主席树了。那么假如一个权值有很多点该怎么办。只需要一个一个插入，然后以最后一次插入完成后的根作为这个权值的根就行了。  
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;
const int N=20100;
vector<int> vec[N];
int n,m,a[N],b[N],ans,root[N],num,q[6];
int sum[N*20],ml[N*20],mr[N*20],tot,ch[N*20][2];
int read(){
    int sum=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){sum=sum*10+ch-'0';ch=getchar();}
    return sum*f;
}
void update(int now){
    sum[now]=sum[ch[now][0]]+sum[ch[now][1]];
    ml[now]=max(ml[ch[now][0]]+sum[ch[now][1]],ml[ch[now][1]]);
    mr[now]=max(mr[ch[now][1]]+sum[ch[now][0]],mr[ch[now][0]]);
}
void build(int l,int r,int &now){
    if(now==0)now=++tot;
    if(l==r){
        sum[now]=ml[now]=mr[now]=1;
        return ;
    }
    int mid=(l+r)>>1;
    build(l,mid,ch[now][0]);
    build(mid+1,r,ch[now][1]);
    update(now);
}
void add(int l,int r,int x,int pre,int &now){
    now=++tot;
    if(l==r){sum[now]=ml[now]=mr[now]=-1;return;}
    ch[now][0]=ch[pre][0];
    ch[now][1]=ch[pre][1];
    int mid=(l+r)>>1;
    if(x>mid)add(mid+1,r,x,ch[pre][1],ch[now][1]);
    else add(l,mid,x,ch[pre][0],ch[now][0]);
    update(now);
}
int check(int l,int r,int L,int R,int now){
    if(L>R)return 0;
    if(l==L&&r==R){
        return sum[now];
    }
    int mid=(l+r)>>1;
    if(L>mid)return check(mid+1,r,L,R,ch[now][1]);
    else if(R<=mid)return check(l,mid,L,R,ch[now][0]);
    else return check(l,mid,L,mid,ch[now][0])+check(mid+1,r,mid+1,R,ch[now][1]); 
}
int check_L(int l,int r,int L,int R,int now){
    if(l==L&&r==R)return ml[now];
    int mid=(l+r)>>1;
    if(L>mid)return check_L(mid+1,r,L,R,ch[now][1]);
    else if(R<=mid)return check_L(l,mid,L,R,ch[now][0]);
    else{
        int tmp1=check_L(mid+1,r,mid+1,R,ch[now][1]);
        int tmp2=check(mid+1,r,mid+1,R,ch[now][1])+check_L(l,mid,L,mid,ch[now][0]);
        return max(tmp1,tmp2);
    }
}
int check_R(int l,int r,int L,int R,int now){
    if(l==L&&r==R)return mr[now];
    int mid=(l+r)>>1;
    if(L>mid)return check_R(mid+1,r,L,R,ch[now][1]);
    else if(R<=mid)return check_R(l,mid,L,R,ch[now][0]);
    else{
        int tmp1=check_R(l,mid,L,mid,ch[now][0]);
        int tmp2=check(l,mid,L,mid,ch[now][0])+check_R(mid+1,r,mid+1,R,ch[now][1]);
        return max(tmp1,tmp2);
    }
}
bool judge(int x){
    int tmp1=check(1,n,q[2]+1,q[3]-1,root[x]);
    int tmp2=check_L(1,n,q[1],q[2],root[x]);
    int tmp3=check_R(1,n,q[3],q[4],root[x]);
    if(tmp1+tmp2+tmp3>=0)return true;
    else return false; 
}
int work(){
    int l=1,r=num,tmp;
    while(l<=r){
        int mid=(l+r)>>1;
        if(judge(mid)){
            tmp=mid;
            l=mid+1;
        }
        else r=mid-1;
    }
    return tmp;
}
int main(){
    n=read();
    for(int i=1;i<=n;i++)a[i]=read(),b[i]=a[i];
    sort(b+1,b+1+n);
    num=unique(b+1,b+1+n)-b-1;
    build(1,n,root[0]);
    for(int i=1;i<=n;i++){
        a[i]=lower_bound(b+1,b+1+num,a[i])-b;
        vec[a[i]].push_back(i);
    }
    for(int i=1;i<=num;i++){
        root[i]=root[i-1];
        if(vec[i-1].size())for(int j=0;j<vec[i-1].size();j++)
            add(1,n,vec[i-1][j],root[i],root[i]);
    }
    m=read();
    while(m--){
        q[1]=(read()+ans)%n+1,q[2]=(read()+ans)%n+1,q[3]=(read()+ans)%n+1,q[4]=(read()+ans)%n+1;
    //	q[1]=read(),q[2]=read(),q[3]=read(),q[4]=read();
        sort(q+1,q+1+4);
        ans=work();
        printf("%d\n",b[ans]);
        ans=b[ans];
    }
    return 0;
}
```

---

