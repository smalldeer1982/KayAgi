# 「JYLOI Round 1」常规

## 题目描述

LS 制定了 $n$ 项常规，其中第 $i$ 项常规制定的时间是 $a_i$。

对于第 $i$ 项常规，从第 $i$ 项常规的制定时间 $a_i$ 后的每 $k$ 秒，他都要做一次第 $i$ 项常规，他做一次常规的时间可以忽略不计。

现在 LS 想给你 $m$ 个询问，每个询问用一个区间 $[l_i, r_i]$ 来表示，问你在第 $l_i$ 到 $r_i$ 秒，他一共做了多少次常规。

## 说明/提示

### 样例 2 说明

解密后的询问分别为 [1, 5]、[4, 7]、[8, 10]、[9, 10]、[8, 8]、[12, 12]、[21, 31]、[28, 48]、[36, 65]、[55, 80]，因此可以得出答案。

____________

### 数据范围

对于 $100\%$ 的数据，满足 $type \in \{0, 1\}; 1 \leq n, m \leq 10^5; 0 \leq l_i \leq r_i \leq 10^9; 0 \leq a_i \leq 10^9; 1 \leq k, mod \leq 10^9$。

子任务 1（有 10 个测试点，每个测试点 1 分，共 10 分）：$type = 0; n, m, k \leq 10^3; r_i \leq 10^3$。

子任务 2（有 10 个测试点，每个测试点 1 分，共 10 分）：$type = 0; n, m \leq 10^3$。

子任务 3（有 2 个测试点，每个测试点 5 分，共 10 分）：$type = 0, r_i \leq 10^5,k = 1$。

子任务 4（共 20 分）：$type = 0, k \leq 10^5, r_i \leq 10^5$。

子任务 5（共 30 分）：$type = 0$。

子任务 6（共 20 分）：无特殊限制。

对于子任务 4、5、6，分别捆绑计分（即你需要通过一个子任务内的所有测试点才能够拿到这个子任务的分数），本题总共 50 个测试点、100 分。

## 题目来源

「JYLOI Round 1」 D

Idea / Solution / Data ：abcdeffa

## 样例 #1

### 输入

```
0
5 10 3
1 2 3 4 5
1 5
2 5
3 5
4 5
5 5
10 10
20 30
10 30
1 30
5 30```

### 输出

```
2
2
2
2
1
2
18
35
43
42```

## 样例 #2

### 输入

```
1
5 10 3 100
1 2 3 4 5
1 5
2 5
3 5
4 5
5 5
10 10
20 30
10 30
1 30
5 30```

### 输出

```
2
5
5
3
2
1
18
35
50
44```

# 题解

## 作者：未来姚班zyl (赞：2)

## 题目大意

给出常数 $k$ 与 $n$ 组信息，第 $i$ 组信息表示 $a_i+Bk$（$B$ 为正整数）上有一个点，$m$ 次询问区间 $[l_i,r_i]$ 内的点数，强制在线。

## 题目分析

查询转换为前缀思路往往会变得清晰，考虑如何求 $[1,x]$ 内的点数。

考虑将 $a_i$ 排序，二分到最后一个 $p$ 使得 $a_p<x$。则答案为：

$$\sum\limits_{1\le i\le p}\lfloor\frac{x-a_i}{k}\rfloor$$



暴力拆开式子，得到：

$$\frac{1}{k}\sum\limits_{1\le i\le p}x-a_i-(x-a_i)\bmod k$$

前两项可以维护前缀和 $O(1)$ 算，最后一项继续暴力拆：

$$(x-a_i)\bmod k=x\bmod k-a_i\bmod k+[x\bmod k<a_i\bmod k]k$$

新的前两项依旧可以 $O(1)$ 算，第三项相当于二维偏序，离散化并使用主席树即可，复杂度 $O((n+m)\log n)$。

**请仔细阅读强制在线的要求。**

```cpp
#include<bits/stdc++.h>
#define ll long long
#define L(x) xd[x].l
#define R(x) xd[x].r
#define mid (l+r>>1)
#define lc(x) L(x),l,mid
#define rc(x) R(x),mid+1,r
#define OK Ll<=l&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N =1e5+5,M=1e7+5;
bool ty=read();
int n=read(),m=read(),k=read(),md,a[N],lsh[N],b[N],ln,c[N],tot,ct[N],rt[N];
ll lastans,pr[N],pc[N];
int in(int i){
    int x=read();
    if(ty&&i>1)x=(lastans+x-1)%md+1;
    return x;
}
struct seg{
    int l,r,w;
}xd[M];
inline int modify(int &x,int X,int l,int r,int p){
    xd[++x]=xd[X],xd[x].w++;
    int nw=x;
    if(l==r)return x;
    p<=mid?L(nw)=modify(x,lc(X),p):R(nw)=modify(x,rc(X),p);
    return nw;
}
inline int query(int x,int l,int r,int Ll,int Rr){
    if(OK)return xd[x].w;
    if(Rr<=mid)return query(lc(x),Ll,Rr);
    if(Ll>mid)return query(rc(x),Ll,Rr);
    return query(lc(x),Ll,Rr)+query(rc(x),Ll,Rr);
}
int find(int x){
    int l=1,r=n,ans=0;
    while(l<=r)if(a[mid]<=x)ans=mid,l=mid+1;
    else r=mid-1;
    return ans;
}
int gt(int x){
    int l=1,r=ln,ans=ln+1;
    while(l<=r)if(b[mid]>x)ans=mid,r=mid-1;
    else l=mid+1;
    return ans;
}
ll calc(int x){
    int p=find(x);
    if(!p)return 0;
    ll ans=1LL*x*p-pr[p]-1LL*(x%k)*p+pc[p];
    int ps=gt(x%k);
    if(ps!=ln+1)ans-=1LL*k*query(rt[p],1,ln,ps,ln);
    return ans/k;
}
signed main(){
    if(ty)md=read();
    repn(i)a[i]=read();
    sort(a+1,a+n+1);
    repn(i)pr[i]=pr[i-1]+a[i],c[i]=lsh[i]=a[i]%k;
    sort(lsh+1,lsh+n+1),lsh[n+1]=-1;
    repn(i)if(lsh[i]^lsh[i+1])b[++ln]=lsh[i];
    repn(i)pc[i]=pc[i-1]+c[i],c[i]=lower_bound(b+1,b+ln+1,c[i])-b,rt[i]=modify(tot,rt[i-1],1,ln,c[i]);
    repm(i){
        int l=in(i),r=in(i);
        if(l>r)swap(l,r);
        lastans=calc(r)-calc(l-1),pf(lastans),putchar('\n');
    }
    return 0;
}
```


---

## 作者：CQ_Bab (赞：1)

# 前言
某个大佬之前做过这道题竟然推不出来柿子了，至于他是谁我只能说他还是太强了。
# 思路
首先通过观察可以发现答案可以为 $1\sim r$ 与 $1\sim l-1$ 的答案相减而求 $1\sim x$ 的答案的柿子为 $\sum \lfloor (x-a_i)\div k\rfloor$ 然后我们继续拆柿子可以发现答案为 $\frac{1}{k}\sum (x-a_i)-(x-a_i)\bmod k$ 所以我们发现前一个可以用前缀和处理然后后一个为 $\sum (x\bmod k-a_i\bmod k+k)\bmod k$ 我们发现只有 $x\bmod k<a_i\bmod k$ 时需要加 $k$ 所以我们只需要求出有多少个数大于 $x\bmod k$ 即可，直接主席树（注意上述的 $a_i$ 都要小于等于 $x$，所以需要先将 $a_i$ 排序然后在查询时二分）。
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
#define int long long
#define fire signed
#define il inline
const int bufsize = 230005;
char buf[bufsize], *f1, *f2;
#define getchar() (f1 == f2 && (f2 = buf + fread(f1 = buf, 1, bufsize, stdin)) == buf? EOF: *f1++)
il void in(int &x) {
    x = 0; char ch = getchar();
    int f = 1;
    while (ch < '0' || ch > '9') {if(ch=='-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
    x *= f;
}
int T=1;
int tp;
int n,m,k;
int mod;
const int N=1e5+10,M=1e9+10;
int a[N];
struct node{
	int l,r,cnt;
}tr[N<<5];
int rt[N],idx;
il void up(int x) {
	tr[x].cnt=tr[tr[x].l].cnt+tr[tr[x].r].cnt;
}
il int modify(int u,int l,int r,int k) {
	int p=++idx;
	tr[p]=tr[u];
	if(l==r) {
		tr[p].cnt++;
		return p;
	}
	int mid=l+r>>1;
	if(mid>=k) tr[p].l=modify(tr[p].l,l,mid,k);
	else tr[p].r=modify(tr[p].r,mid+1,r,k);
	up(p);
	return p;
}
il int Ans(int u,int l,int r,int k) {
	if(l==r) return tr[u].cnt;
	int mid=l+r>>1;
	if(mid>=k) return Ans(tr[u].l,l,mid,k);
	return tr[tr[u].l].cnt+Ans(tr[u].r,mid+1,r,k);
}
int sum[N],sum1[N];
il int get(int x) {
	if(x<a[1]+k) return false;
	int id=(lower_bound(a+1,a+1+n,x)-a)-1;
	int now=x*id-sum[id];
	int yu=x%k;
	now-=yu*id;
	now+=sum1[id];
	now-=k*(id-Ans(rt[id],0,k,yu));
	return now/k;
}
il void solve() {
	in(tp);
	in(n),in(m),in(k);
	if(tp) in(mod);
	rep(i,1,n) in(a[i]);
	sort(a+1,a+1+n);
	rep(i,1,n) {
		sum[i]=sum[i-1]+a[i];
		sum1[i]=sum1[i-1]+(a[i]%k);
		rt[i]=rt[i-1];
		rt[i]=modify(rt[i],0,k,a[i]%k);
	}
	int lst=false,cc=0;
	while(m--) {
		int l,r;
		cc++;
		in(l),in(r);
		if(tp&&cc!=1) {
			l=(l+lst-1)%mod+1,r=(r+lst-1)%mod+1;
			if(l>r) swap(l,r);
		}
		lst=get(r)-get(l-1);
		printf("%lld\n",lst);
	}
}
fire main() {
	while(T--) solve();
	return false;
}
```

---

## 作者：__stick (赞：1)

## 题意
给出常数 $k$，有 $n$ 个条件，表示 $a_i+xk$ 处有一个点（$x\ge 1,x\in Z$），多次询问区间中点的数量。

## 思路

首先差分，问题变成前缀问题，假设每次询问的端点是 $x$。

将 $a$ 排序，设最大的小于等于 $x$ 的位置为 $lim$。

然后答案就是:

$$
\sum_{i=1}^{lim}\left\lfloor\frac{x-a_i}{k}\right\rfloor
$$

将下取整分开：

$$
\left\lfloor\frac{a}{b}\right\rfloor=\frac{a}{b}-a\bmod b
$$

这个柿子显然，就不需要证明了。

然后求和项就可以拆开了：
$$
\sum_{i=1}^{lim}\left\lfloor\frac{x-a_i}{k}\right\rfloor=

k\sum_{i=1}^{lim}x-a_i-(x-a_i)\bmod k
$$

前面几个项都是容易的，看最后一个：

$$
(x-a_i)\bmod k=x\bmod k-a_i\bmod k +[a_i\bmod k>x\bmod k]\cdot k
$$

前面两项可以前缀和，最后一个就是二维数点，可以使用主席树做到在线，然后就做完了。

## code

```cpp
const int MAXN=2e5+10;
struct node{int l,r,w;}t[MAXN*60];
#define ls t[p].l
#define rs t[p].r
int tt;
void update(int& p,int l,int r,int qq)
{
    t[++tt]=t[p],p=tt,t[p].w++;
    if(l==r)return;int mid=(l+r)>>1;
    if(qq<=mid)update(ls,l,mid,qq);
    else update(rs,mid+1,r,qq);
}
int ask(int p,int l,int r,int ql,int qr)
{
    if(!p)return 0;
    if(ql<=l&&r<=qr)return t[p].w;
    int mid=(l+r)>>1;
    if(qr<=mid)return ask(ls,l,mid,ql,qr);
    else if(ql>mid)return ask(rs,mid+1,r,ql,qr);
    else return ask(ls,l,mid,ql,qr)+ask(rs,mid+1,r,ql,qr);
}
int rt[MAXN],a[MAXN];
ll sum[MAXN];
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);cout<<fixed<<setprecision(10);
	int tp;cin>>tp;
    int n,m,k;cin>>n>>m>>k;if(tp)cin>>mod;
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++)
    {
        update(rt[i]=rt[i-1],0,k,a[i]%k);
        sum[i]=sum[i-1]-1ll*a[i]+a[i]%k;
    }
    auto cal=[&](int b)->ll
    {
        int w=upper_bound(a+1,a+n+1,b)-a-1;
        ll ans=sum[w];
        ans+=1ll*b*w;
        ans-=1ll*(b%k)*w;
        ans-=1ll*k*ask(rt[w],0,k,b%k+1,k);
        return ans/k;
    };
    ll l,r;cin>>l>>r;
    ll la=cal(r)-cal(l-1);
    cout<<la<<'\n';
    for(int i=2;i<=m;i++)
    {
        cin>>l>>r;
        if(tp)l=(l+la-1)%mod+1,r=(r+la-1)%mod+1;
        if(l>r)swap(l,r);
        la=cal(r)-cal(l-1);
        cout<<la<<'\n';
    }
	return 0;
} 
```


---

## 作者：ivyjiao (赞：0)

$2025/02/07$，wxg 牢狮把这道题加进了【】。

话说这题是真难调，也可能是我太唐了。

答案显然可以表示为 $1\sim r$ 内的点减去 $1\sim l-1$ 的点。

那么答案就是：

$$\sum_{i=1}^{a_i<x} \lfloor\dfrac{x-a_i}{k}\rfloor$$

把 $k$ 拆出来：

$$\lfloor\dfrac 1 k\sum_{i=1}^{a_i<x} x-a_i-(x-a_i)\bmod k\rfloor$$

这个式子有四项，其中前三项都可以拿前缀和预处理 $O(1)$ 做，$a_i<x$ 可以拿排序加上二分做（注意特判 $0$）。

第四项接着拆，得到：

$$\sum_{i=1}^{a_i<x} (x\bmod k-a_i\bmod k+k)\bmod k$$

我们发现只有 $x\bmod k-a_i\bmod k<0$，即 $x\bmod k<a_i\bmod k$ 才要 $+k$，我们拿主席树求出有多少 $a_i\bmod k>x\bmod k$ 就行（求的东西不一样，不能直接粘板子！！！）。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define ls ch[u][0]
#define rs ch[u][1]
using namespace std;
const int N=3e6+1;
int type,n,m,k,p,x,y,a[N],sum[N],sum1[N],l,ch[N][2],b[N],rt[N],lst;
int clone(int u){
    ch[++l][0]=ls;
    ch[l][1]=rs;
    b[l]=b[u];
    return l;
}
int add(int u,int l,int r,int x){
    u=clone(u);
    if(l==r){
    	b[u]++;
    	return u;
    }
    int mid=l+r>>1;
    if(x<=mid) ls=add(ls,l,mid,x);
    else rs=add(rs,mid+1,r,x);
    b[u]=b[ls]+b[rs];
    return u;
}
int query(int u,int l,int r,int x){
    if(l==r) return b[u];
    int mid=l+r>>1;
    if(x<=mid) return query(ls,l,mid,x);
    else return b[ls]+query(rs,mid+1,r,x);
}
int get(int x){
	if(x<a[1]+k) return 0;
	int c=lower_bound(a+1,a+1+n,x)-a-1,cnt=c*x-sum[c];
	cnt-=x%k*c;
	cnt+=sum1[c];
	cnt-=k*(c-query(rt[c],0,k,x%k));
	return cnt/k;
}
signed main(){
	cin>>type>>n>>m>>k;
	if(type) cin>>p;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+1+n);
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+a[i];
        sum1[i]=sum1[i-1]+a[i]%k;
        rt[i]=add(rt[i-1],0,k,a[i]%k);
    }
    for(int i=1;i<=m;i++){
        cin>>x>>y;
        if(type&&i>1) x=(x+lst-1)%p+1,y=(y+lst-1)%p+1;
        if(x>y) swap(x,y);
        lst=get(y)-get(x-1);
        cout<<lst<<endl;
    }
}
```

---

## 作者：CQ_Bob (赞：0)

题解摘自[做题记录](https://www.luogu.com.cn/article/vd2a2tvg)。

怎么没人做。

## 分析

考虑差分。那么我们就需要维护出 $[1,x]$ 的答案。

记 $m$ 为最大的 $i$，使得 $a_i <x$。那么答案为：$\sum\limits_{i=1}^{m} \lfloor\frac{x-a_i}{k}\rfloor$。把式子拆开，有：$\sum\limits_{i=1}^{m} \frac{x-a_i-(x-a_i)\bmod k}{k}$。

那么现在只需要求 $\sum\limits_{i=1}^{m} -a_i-(x-a_i)\bmod k$。前者可以前缀和，后者可以写成：$-(x\bmod k-a_i \bmod k+k[x\bmod k < a_i \bmod k])$。

那么原问题就相当于是求：$\frac{1}{k} \times (mx-s_m-m(x\bmod k)+g_m-k\times \sum\limits_{i=1}^{m} [x\bmod k < a_i \bmod k])$。其中 $s_i$ 为 $a_i$ 的前缀和，$g_i$ 为 $a_i\bmod k$ 的前缀和。又因为 $x\bmod k$ 是定值，记 $b_i=a_i \bmod k$。那么就只需要求 $[1,m]$ 中 $b_i > x\bmod k$ 的数的数量了。使用主席树可以做到 $O(n\log V)$。

## 代码

```cpp
il void up(int u){
	tr[u].sum=tr[ls(u)].sum+tr[rs(u)].sum;
	return ;
}
il void modify(int &u,int l,int r,int x){
	tr[++idx]=tr[u],u=idx;
	if(l==r) return ++tr[u].sum,void(0);
	int mid=l+r>>1;
	if(x<=mid) modify(ls(u),l,mid,x);
	else modify(rs(u),mid+1,r,x);
	return up(u),void(0);
}
il int query(int u,int l,int r,int L,int R){
	if(L>R) return 0;
	if(l>=L&&r<=R) return tr[u].sum;
	int mid=l+r>>1,sum=0;
	if(L<=mid) sum+=query(ls(u),l,mid,L,R);
	if(mid< R) sum+=query(rs(u),mid+1,r,L,R);
	return sum;
}
il int work(int x){
	int sum=0;
	int l=1,r=n,w=-1;
	while(l<=r){
		int mid=l+r>>1;
		if(a[mid]<x) w=mid,l=mid+1;
		else r=mid-1;
	}
	if(w==-1) return 0;
	sum+=w*x-s[w]-w*(x%k)+g[w];
	int cnt=query(root[w],0,10000000001,x%k+1,10000000001);
	sum-=k*cnt;
	return sum/k;
}
```

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P6638)

# 前置知识

[可持久化线段树](https://oi-wiki.org/ds/persistent-seg/) | [前缀和 & 差分](https://oi-wiki.org/basic/prefix-sum/)

# 解法

进行差分，区间查询转化成前缀和相减。

先将 $\{ a \}$ 升序排序。

设当前询问的区间为 $[1,r]$，在 $\{ a \}$ 中找到一个最大的 $pos$ 使得 $a_{pos} \le r$，则 $[1,r]$ 中所做常规的次数为 $\sum\limits_{i=1}^{pos}\left\lfloor \dfrac{r-a_{i}}{k} \right\rfloor$。

考虑拆开向下取整，有 $\begin{aligned} &\sum\limits_{i=1}^{pos}\left\lfloor \dfrac{r-a_{i}}{k} \right\rfloor \\ &=\sum\limits_{i=1}^{pos} \dfrac{r-a_{i}-(r-a_{i}) \bmod k}{k} \\ &=\dfrac{1}{k} \times \sum\limits_{i=1}^{pos}r-a_{i}-(r-a_{i}) \bmod k \\ &=\dfrac{1}{k} \times (r \times pos-\sum\limits_{i=1}^{pos}a_{i}-\sum\limits_{i=1}^{pos}(r-a_{i}) \bmod k) \end{aligned}$。

难点在于怎么求 $\sum\limits_{i=1}^{pos}(r-a_{i}) \bmod k$。考虑按照取模运算的性质拆开并适当补上 $+k$，有 $\begin{aligned} (r-a_{i}) \bmod k=r \bmod k-a_{i} \bmod k+[r \bmod k<a_{i} \bmod k] \times k \end{aligned}$。

以 $a_{i} \bmod k$ 为权值建立一棵主席树然后主席树上查询 $[1,pos]$ 内满足 $a_{i} \bmod k \in (r \bmod k,k)$ 即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
ll a[100010],sum1[100010],sum2[100010];
struct PDS_SMT
{
	ll root[100010],rt_sum=0;
	struct SegmentTree
	{
		ll ls,rs,sum;
	}tree[100010<<5];
	#define lson(rt) tree[rt].ls
	#define rson(rt) tree[rt].rs
	ll build_rt()
	{
		rt_sum++;
		return rt_sum;
	}
	void update(ll pre,ll &rt,ll l,ll r,ll pos)
	{
		rt=build_rt();
		tree[rt]=tree[pre];
		tree[rt].sum++;
		if(l==r)
		{
			return;
		}
		ll mid=(l+r)/2;
		if(pos<=mid)
		{
			update(lson(pre),lson(rt),l,mid,pos);
		}
		else
		{
			update(rson(pre),rson(rt),mid+1,r,pos);
		}
	}
	ll query(ll rt,ll l,ll r,ll x,ll y)
	{
		if(x<=l&&r<=y)
		{
			return tree[rt].sum;
		}
		ll mid=(l+r)/2,ans=0;
		if(x<=mid)
		{
			ans+=query(lson(rt),l,mid,x,y);
		}
		if(y>mid)
		{
			ans+=query(rson(rt),mid+1,r,x,y);
		}
		return ans;
	}
}T;
ll ask(ll r,ll n,ll k)
{
	ll ans=0,pos=upper_bound(a+1,a+1+n,r)-a-1;
	ans+=r*pos;
	ans-=sum1[pos];
	ans-=(r%k)*pos;
	ans+=sum2[pos];
	ans-=T.query(T.root[pos],0,k-1,r%k+1,k-1)*k;
	return ans/k;
}
int main()
{
	ll type,n,m,k,mod,l,r,ans=0,i;
	cin>>type>>n>>m>>k;
	if(type==1)
	{
		cin>>mod;
	}
	for(i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+1+n);
	for(i=1;i<=n;i++)
	{
		sum1[i]=sum1[i-1]+a[i];
		sum2[i]=sum2[i-1]+a[i]%k;
		T.update(T.root[i-1],T.root[i],0,k-1,a[i]%k);
	}
	cin>>l>>r;
	ans=ask(r,n,k)-ask(l-1,n,k);
	cout<<ans<<endl;
	for(i=2;i<=m;i++)
	{
		cin>>l>>r;
		if(type==1)
		{
			l=(l+ans-1)%mod+1;
			r=(r+ans-1)%mod+1;
			if(l>r)
			{
				swap(l,r);
			}
		}
		ans=ask(r,n,k)-ask(l-1,n,k);
		cout<<ans<<endl;
	}
	return 0;
}
```

---

