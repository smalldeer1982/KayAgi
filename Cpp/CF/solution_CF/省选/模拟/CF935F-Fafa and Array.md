# Fafa and Array

## 题目描述

Fafa has an array $ A $ of $ n $ positive integers, the function $ f(A) $ is defined as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF935F/dc9a0a0772798ba9fb8b149f527b509b8571b93b.png). He wants to do $ q $ queries of two types:

- $ 1lrx $ — find the maximum possible value of $ f(A) $ , if $ x $ is to be added to one element in the range $ [l,r] $ . You can choose to which element to add $ x $ .
- $ 2lrx $ — increase all the elements in the range $ [l,r] $ by value $ x $ .

Note that queries of type $ 1 $ don't affect the array elements.

## 样例 #1

### 输入

```
5
1 1 1 1 1
5
1 2 4 1
2 2 3 1
2 4 4 2
2 3 4 1
1 3 3 2
```

### 输出

```
2
8
```

## 样例 #2

### 输入

```
5
1 2 3 4 5
4
1 2 4 2
2 2 4 1
2 3 4 1
1 2 4 2
```

### 输出

```
6
10
```

# 题解

## 作者：Kelin (赞：3)

题意:

给出一个序列$A$ ,定义函数$f(A)=\sum_{i=1}^{n-1}|a_i-a_{i+1}|$ 

给出两种操作:

$1.l$  $r$  $x$ ,在区间$[l,r]$ 内找一个位置,使得把这个位置的值加上$x$ 后,$f(A)$ 最大,求这个最大值

$2.l$  $r$  $x$ ,把区间$[l,r]$ 加上$x$ 

$n\le10^5,q\le10^5,x_i\le10^9$ 

----
记$ans=f(A)$

考虑$a_i+x$与$a_{i-1},a_{i+1}$的大小关系

#### 一:$a_i+x\lt a_{i-1},a_i+x\lt a_{i+1}$

$\Delta=-2x$

#### 二:$a_{i-1}\lt a_i+x\lt a_{i+1}$

$\Delta=(|(a_i+x)-a_{i+1}|+|a_{i-1}-(a_i+x)|)-(|a_i-a_{i+1}|+|a_{i-1}-a_i|)$

$=-x+|a_i-a_{i-1}+x|+|a_i-a_{i-1}|\le 0$

#### 三:$a_{i-1}\le a_i+x,a_{i+1}\le a_i+x$

再考虑$a_i$与$a_{i-1},a_{i+1}$的大小关系

①:$a_{i-1}\le a_i,a_{i+1}\le a_i,\Delta=2*x$

②:$a_{i-1}\le a_i\lt a_{i+1},\Delta=2*x-2*(a_{i+1}-a_i)$

③:$a_i\lt a_{i-1},a_i\lt a_{i+1},\Delta=2*x-2*[(a_{i-1}-a_i)+(a_{i+1}-a_i)]$

显然只有第三种情况是可能对答案贡献是正的

所以我们可以考虑用线段树维护$min\{max(0,a_{i-1}-a_i)+max(0,a_{i+1}-a_i)\}$

区间修改,考虑差分,令$a_i=a_{i+1}-a_i$

那么我们就是维护$min\{max(0,-a_{i-1})+max(0,a_i)\}$

注意特判一下$l=1$,$r=n$的情况

那么有没有$\Delta$一定是负数的情况呢?

有,当$l=r$时,我们只能修改这个值,所以可能出现负贡献,特判一下就好了
```
#include<bits/stdc++.h>
#define fp(i,a,b) for(register int i=a,I=b+1;i<I;++i)
#define fd(i,a,b) for(register int i=a,I=b-1;i>I;--i)
#define go(u) for(register int i=fi[u],v=e[i].to;i;v=e[i=e[i].nx].to)
#define file(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
template<class T>inline bool cmin(T&a,const T&b){return a>b?a=b,1:0;}
using namespace std;
char ss[1<<17],*A=ss,*B=ss;
inline char gc(){return A==B&&(B=(A=ss)+fread(ss,1,1<<17,stdin),A==B)?-1:*A++;}
template<class T>inline void sd(T&x){
    char c;T y=1;while(c=gc(),(c<48||57<c)&&c!=-1)if(c==45)y=-1;x=c-48;
    while(c=gc(),47<c&&c<58)x=x*10+c-48;x*=y;
}
char sr[1<<21],z[20];int C=-1,Z;
inline void Ot(){fwrite(sr,1,C+1,stdout),C=-1;}
template<class T>inline void we(T x){
    if(C>1<<20)Ot();if(x<0)sr[++C]=45,x=-x;
    while(z[++Z]=x%10+48,x/=10);
    while(sr[++C]=z[Z],--Z);sr[++C]='\n';
}
const int N=1e5+5;
const long long inf=1e18;
typedef long long ll;
int n,m;ll ans,a[N],tr[N<<2];
#define lc p<<1
#define rc p<<1|1
inline void up(int p){tr[p]=min(tr[lc],tr[rc]);}
void build(int p,int L,int R){
    if(L==R){
        if(L>1)tr[p]=max(0ll,a[L])+max(0ll,-a[L-1]);
        ans+=abs(a[L]);return;
    }int mid=(L+R)>>1;
    build(lc,L,mid),build(rc,mid+1,R);
    up(p);
}
void mdy(int p,int L,int R,int x,int w){
    if(L==R){
        ans+=abs(a[L]+w)-abs(a[L]),a[L]+=w;
        if(x>1)tr[p]=max(0ll,-a[L-1])+max(0ll,a[L]);
        if(w&&x<n-1)mdy(1,1,n-1,x+1,0);return;
    }int mid=(L+R)>>1;
    if(x<=mid)mdy(lc,L,mid,x,w);
    else mdy(rc,mid+1,R,x,w);up(p);
}
ll qry(int p,int L,int R,int a,int b){
    if(a<=L&&R<=b)return tr[p];
    int mid=(L+R)>>1;
    if(b<=mid)return qry(lc,L,mid,a,b);
    if(a>mid)return qry(rc,mid+1,R,a,b);
    return min(qry(lc,L,mid,a,b),qry(rc,mid+1,R,a,b));
}
int main(){
    #ifndef ONLINE_JUDGE
        file("s");
    #endif
    sd(n);int op,l,r,x;
    fp(i,1,n)sd(a[i]);
    fp(i,1,n)a[i]=a[i+1]-a[i];
    build(1,1,n-1);sd(m);
    while(m--){
    	sd(op),sd(l),sd(r),sd(x);
    	if(op==1){
    		if(l==r){
    			if(l==1)we(ans-abs(a[l])+abs(a[l]-x));
    			else if(l==n)we(ans-abs(a[l-1])+abs(a[l-1]+x));
    			else we(ans-abs(a[l-1])-abs(a[l])+abs(a[l-1]+x)+abs(a[l]-x));
    		}else{
    			ll tp=2*(x-qry(1,1,n-1,l>1?l:2,r));
    			if(l==1)cmax(tp,-abs(a[l])+abs(a[l]-x));
    			if(r==n)cmax(tp,-abs(a[r-1])+abs(a[r-1]+x));
    			we(ans+max(0ll,tp));
    		}
    	}else{
    		l>1?mdy(1,1,n-1,l-1,x):void();
    		r<n?mdy(1,1,n-1,r,-x):void();
    	}
    }
return Ot(),0;
}
```


---

## 作者：DPair (赞：1)

## 思路
首先我们考虑计算贡献而不是真实值，我们把整个序列的答案算出来之后加上贡献就是这次询问的答案了，显然一个点的贡献可以 $O(1)$ 求。

于是我们考虑先 $O(1)$ 处理掉 $i=1, i=n$ 的特殊情况，那么一个点 $i$ 加上一个数之后只会影响到 $(i-1, i), (i, i + 1)$ 这两组关系。

不难发现这道题当中，一个位置加上一个数之后最多产生三种贡献：

1. 若 $a_i\ge a_{i-1}$ 且 $a_i \ge a_{i+1}$ ，那么加上 $x$ 之后能产生贡献的最大值 $2x$ ，直接输出即可。
2. 若 $a_i< a_{i-1}$ 且 $a_i < a_{i+1}$ 不难发现若这种情况出现次数大于 $1$ ，那么情况 $1$ 显然存在，故直接记录它的出现位置然后 $O(1)$ 判断贡献即可。
3. 以上两种情况以外的情况，即当前数大于等于一边然后小于另一边，我们设 **比当前数大的那一边的权值** 为 $t$ ，那么加上 $x$ 之后产生的贡献为 $\max(0, 2(x-t))$ ，因此取出区间内 $t$ 最小值即可。

然后不难发现区间加时，只有 $l, r$ 两个点的相对关系发生了变化。

那么直接修改 $l, r$ 即可，等于说要实现的就是区间最小值和 01序列的区间或 。

这个线段树随便搞搞就行了，然而我这个 \*\* 写了个序列分块（（

代码还是放一下吧。

## 瑇码
```cpp
//在黑暗中闪耀的银河啊，化作希望之光寄于吾仆之身！光之化身，于此降临！
#pragma GCC optimize(2, 3, "Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define rep(i,s,t) for(int i=(s);i<=(t);++i)
#define per(i,t,s) for(int i=(t);i>=(s);--i)
#define REP(i,s,t) for(int i=(s);i<(t);++i)
#define PER(i,t,s) for(int i=(t);i>(s);--i)
#define elif else if
const double pi = 3.141592653589793238462643383279;
namespace MyMinMax{
template <typename T>
inline T mn(const T x, const T y) {return x < y ? x : y;}
template <typename T>
inline T mx(const T x, const T y) {return x > y ? x : y;}
template <typename T>
inline bool chmin(T &x, const T y) {return (x > y) && ((x = y), 1);}
template <typename T>
inline bool chmax(T &x, const T y) {return (x < y) && ((x = y), 1);}
template <typename T, typename ...Args>
inline T mx(const T x, const Args ...args) {return mx(x, mx(args...));}
template <typename T, typename ...Args>
inline T mn(const T x, const Args ...args) {return mn(x, mn(args...));}
}
using namespace MyMinMax;

// 省略了不重要的快读

typedef long long LL;
const int INF = 0x3f3f3f3f;
const LL INFll = 0x3f3f3f3f3f3f3f3fll;
/* My Code begins here */

const int MAXN = 1e5 + 5;
LL tot = 0; int n, m;
const int block = 355, B = MAXN / block + 5;
int bel[MAXN], lst[B];
LL tag[B], a[MAXN], con[MAXN];
const int lim = 500;
template <typename T>
inline T jdz(T x){return x < 0? -x : x;}
inline LL val(int p){return a[p] + tag[bel[p]];}
bool d[B];//同时大于等于两边
LL o[B];//只小于一边的最小距离
int p[B];//同时小于两边的位置
inline void build(int x) {
    if(x == 1 || x == bel[n]) return ;
    const int l = lst[x - 1], r = lst[x];
    d[x] = 0; p[x] = 0; o[x] = INFll; REP(i, l, r) {
        const bool ck1 = val(i) >= val(i - 1), ck2 = val(i) >= val(i + 1);
        
        if(ck1 && ck2) return d[x] = 1, void();
        elif(ck1 || ck2) chmin(o[x], ck1? val(i + 1) - val(i) : val(i - 1) - val(i));
        else p[x] = i;
    }
}

signed main(){
    read(n); read(a + 1, a + n + 1);
    rep(i, 1, n) bel[i] = (i - 1) / block + 1;
    rep(i, 0, bel[n]) lst[i] = mn(n, i * block) + 1;

    REP(i, 1, n) tot += jdz(a[i] - a[i + 1]);

    REP(i, 2, bel[n]) build(i);
    read(m); while(m --) { int opt, l, r; LL x; read(opt, l, r, x); const int L = bel[l], R = bel[r];
        if(opt == 1) {
            LL ans = -INFll;
            if(l == 1) chmax(ans, jdz(val(1) + x - val(2)) - jdz(val(1) - val(2))), ++ l;
            if(r == n) chmax(ans, jdz(val(n) + x - val(n - 1)) - jdz(val(n) - val(n - 1))), -- r;
            
            if(r - l <= lim) {
                rep(i, l, r) {
                    const LL ll = val(i - 1), mm = val(i), rr = val(i + 1);
                    chmax(ans, jdz(mm + x - ll) + jdz(mm + x - rr) - jdz(mm - ll) - jdz(mm - rr));
                } 
            } else {
                REP(i, l, lst[L]) {
                    const LL ll = val(i - 1), mm = val(i), rr = val(i + 1);
                    chmax(ans, jdz(mm + x - ll) + jdz(mm + x - rr) - jdz(mm - ll) - jdz(mm - rr));
                }
                rep(i, lst[R - 1], r) {
                    const LL ll = val(i - 1), mm = val(i), rr = val(i + 1);
                    chmax(ans, jdz(mm + x - ll) + jdz(mm + x - rr) - jdz(mm - ll) - jdz(mm - rr));
                }

                REP(i, L + 1, R) {
                    if(d[i]) {ans = (x << 1); break; }
                    if(o[i] ^ INFll) chmax(ans, (x - o[i]) > 0? ((x - o[i]) << 1) : 0);
                    if(!p[i]) continue;
                    const LL ll = val(p[i] - 1), mm = val(p[i]), rr = val(p[i] + 1);
                    chmax(ans, jdz(mm + x - ll) + jdz(mm + x - rr) - jdz(mm - ll) - jdz(mm - rr));
                } 
            } print(ans + tot);
        } else {
            if(l > 1) tot -= jdz(val(l) - val(l - 1));
            if(r < n) tot -= jdz(val(r) - val(r + 1));
            if(L == R) { rep(i, l, r) a[i] += x; build(L); }
            else {
                REP(i, l, lst[L]) a[i] += x;
                rep(i, lst[R - 1], r) a[i] += x;
                REP(i, L + 1, R) tag[i] += x;
                build(L); build(R);
            }
            if(l > 1) tot += jdz(val(l) - val(l - 1));
            if(r < n) tot += jdz(val(r) - val(r + 1));
        }
    }
}
```

---

## 作者：Caro23333 (赞：1)

考虑对于某一个位置$i$，如果我们在$a_i$上加上$x$，答案会如何变化：

- $1<x<n:\ |a_i-a_{i-1}+x|+|a_{i+1}-a_i-x|-|a_i-a_{i-1}|-|a_{i+1}-a_i|$

- $x=1:\ |a_1-a_2+x|-|a_1-a_2|$

- $x=n:\ |a_n-a_{n-1}+x|-|a_n-a_{n-1}|$

不难发现它们都是分段函数的形式，所以我们只要维护这些分段函数，然后支持查询对于某一个自变量$x$的最大值就可以了。

直接维护分段函数似乎比较困难，但是观察到事实上$1<x<n$的情况是三条斜率分别为$-2,0,2$的直线组成的凸包，$x=1$或$n$的情况是斜率为$-1,1$的直线组成的凸包。这意味着对于一个分段函数在某点求值，相当于对若干条直线求值然后取$\max$。由于可能的斜率只有$5$种，只要在线段树上维护每种斜率的最大截距即可，其中截距可以利用点斜式来转化计算。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#define inf (1ll<<62) 

using namespace std;
typedef long long ll;
const int MAXN = 100005;
inline int readint()
{
	int res = 0;
	char c = 0;
	while(!isdigit(c))
	    c = getchar();
	while(isdigit(c))
	    res = res*10+c-'0', c = getchar();
	return res;
}
int n,q;
ll a[MAXN]; 
struct Line
{
	ll k,b;
	Line(ll x = 0, ll y = 0, ll m = 0)
	    { k = m, b = y-m*x; }
	bool operator<(const Line t) const
	    { return b<t.b; }
};
inline ll calc(Line a, int x)
    { return a.k*x+a.b; } 
struct Node
{
	ll lazy,num;
	Line l[6];
}t[MAXN<<2];
inline void pushdown(int id)
{
	t[id<<1].lazy += t[id].lazy;
	t[id<<1|1].lazy += t[id].lazy;
	t[id].lazy = 0;
}
inline void pushup(int id)
{
	for(int i = 1; i<=5; i++)
	    t[id].l[i] = max(t[id<<1].l[i],t[id<<1|1].l[i]);
}
inline void build(int id, int l)
{
	if(l==1||l==n)
    {
        ll f = l==1?a[1]-a[2]:a[n]-a[n-1];
        t[id].l[1] = Line(0,-inf,-2);
        t[id].l[2] = Line(-f,-abs(f),-1);
        t[id].l[3] = Line(0,-inf,0);
        t[id].l[4] = Line(-f,-abs(f),1);
	    t[id].l[5] = Line(0,-inf,2);
	}
	else
	{
        //if(l==3)
            //cout << "build " << a[l-1] << " " << a[l] << " " << a[l+1] << endl;
	    ll f1 = a[l]-a[l-1], f2 = a[l+1]-a[l];
	    ll left = min(-f1,f2), right = max(-f1,f2);
	    t[id].l[1] = Line(left,abs(f1+f2)-abs(f1)-abs(f2),-2);
	    t[id].l[2] = Line(0,-inf,-1);
	    t[id].l[3] = Line(0,abs(f1+f2)-abs(f1)-abs(f2),0);
	    t[id].l[4] = Line(0,-inf,1);
		t[id].l[5] = Line(right,abs(f1+f2)-abs(f1)-abs(f2),2); 
	}
}
inline void buildTree(int id, int l, int r)
{
	t[id].lazy = 0;
	if(l==r)
	{
        t[id].num = a[l], build(id,l);
		return;
	}
	int mid = (l+r)>>1;
	buildTree(id<<1,l,mid), buildTree(id<<1|1,mid+1,r);
	pushup(id); 
}
inline void add(int id, int ql, int qr, int l, int r, ll d)
{
	if(ql==l&&qr==r)
	{
        t[id].lazy += d;
        return;
	}
	pushdown(id);
	int mid = (ql+qr)>>1;
	if(r<=mid)
	    add(id<<1,ql,mid,l,r,d);
	else if(l>mid)
	    add(id<<1|1,mid+1,qr,l,r,d);
	else
	    add(id<<1,ql,mid,l,mid,d), add(id<<1|1,mid+1,qr,mid+1,r,d);
	pushup(id);
}
inline ll queryVal(int id, int ql, int qr, int pos)
{
	if(ql==pos&&qr==pos)
	    return t[id].num+t[id].lazy;
	pushdown(id);
	int mid = (ql+qr)>>1;
	if(pos<=mid)
	    return queryVal(id<<1,ql,mid,pos);
	else
	    return queryVal(id<<1|1,mid+1,qr,pos); 
}
inline void rebuild(int id, int ql, int qr, int pos)
{
	if(ql==pos&&qr==pos)
	{
		a[pos] = queryVal(1,1,n,pos); 
        if(pos>1)
            a[pos-1] = queryVal(1,1,n,pos-1);
        if(pos<n)
            a[pos+1] = queryVal(1,1,n,pos+1);
		build(id,pos);
		return; 
	}
	pushdown(id);
	int mid = (ql+qr)>>1;
	if(pos<=mid)
	    rebuild(id<<1,ql,mid,pos);
	else
	    rebuild(id<<1|1,mid+1,qr,pos);
    pushup(id);
}
inline ll query(int id, int ql, int qr, int l, int r, int x)
{
	if(ql==l&&qr==r)
    {
        ll res = -inf;
        for(int i = 1; i<=5; i++)
            res = max(res,calc(t[id].l[i],x));
        return res;
	}
    pushdown(id);
    int mid = (ql+qr)>>1;
    if(r<=mid)
        return query(id<<1,ql,mid,l,r,x);
    else if(l>mid)
        return query(id<<1|1,mid+1,qr,l,r,x);
    else
        return max(query(id<<1,ql,mid,l,mid,x),query(id<<1|1,mid+1,qr,mid+1,r,x));
}

int main()
{
	n = readint();
	ll now = 0;
	for(int i = 1; i<=n; i++)
	    a[i] = readint(), now += i>1?abs(a[i]-a[i-1]):0;
	buildTree(1,1,n);
	q = readint();
	int op,l,r,x;
	while(q--)
	{
        op = readint(), l = readint(), r = readint(), x = readint();
        if(op==1)
            printf("%lld\n",query(1,1,n,l,r,x)+now);
        else
        {
            if(l>1)
                now += abs(a[l]-a[l-1]+x)-abs(a[l]-a[l-1]);
            if(r<n)
                now += abs(a[r]-a[r+1]+x)-abs(a[r]-a[r+1]);
            add(1,1,n,l,r,x);
            rebuild(1,1,n,l), rebuild(1,1,n,r);
            if(l>1)
                rebuild(1,1,n,l-1);
            if(r<n)
			    rebuild(1,1,n,r+1); 
		}
	}
	return 0;
}

```


---

