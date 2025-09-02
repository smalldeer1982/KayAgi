# [ABC262Ex] Max Limited Sequence

## 题目描述

### 题目大意
求满足以下条件的长度为 $N$ 的序列 $A=(A_1,A_2,\cdots A_N)$ 有多少种：
+ $\forall i \in[1,N],0\leq A_i\leq M$
+ $\forall i \in[1,Q],\max \limits_{L_i\leq j\leq R_i}A_j=X_i$

## 样例 #1

### 输入

```
3 3 2
1 2 2
2 3 3```

### 输出

```
5```

## 样例 #2

### 输入

```
1 1 1
1 1 1```

### 输出

```
1```

## 样例 #3

### 输入

```
6 40000000 3
1 4 30000000
2 6 20000000
3 5 10000000```

### 输出

```
135282163```

# 题解

## 作者：Graphcity (赞：21)

首先可以使用各种数据结构得出每一个下标对应的值域上界。我们对每一种值域上界所在的位置分别进行 DP。

对于一个上界 $x$，我们显然只关心填的数是 $<x$ 还是 $=x$。我们用 0 表示 $<x$，1 表示 $=x$。对于这个值域上的限制 $[l,r]$，表示 $[l,r]$ 范围内至少有一个为 1。

不妨设 $f_{i,j}$ 表示考虑到前 $i$ 个位置，最后一个 1 填在位置 $j$ 的方案数。转移有三种：

1. $f_{i-1,j}\to f_{i,i}$，表示位置 $i$ 为 1。

2. $f_{i-1,j}\times x\to f_{i,j}$，表示位置 $i$ 为 0。

3. 对于限制 $[l,i]$，将所有 $f_{i,j}\ (j<l)$ 赋值为 0。

发现只需要单点赋值为全局和，全局乘，前缀清空这三种操作。可以直接维护全局和 $sum$，全局乘法标记 $tag$ 和被清空的最长前缀 $len$ 即可做到线性。

总时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=4e5,Mod=998244353;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
inline int Pow(int x,int y)
{
    int res=1;
    while(y)
    {
        if(y&1) res=1ll*res*x%Mod;
        x=1ll*x*x%Mod,y>>=1;
    }
    return res;
}

int n,m,q,s,ans=1,val[Maxn+5],f[Maxn+5];
int tot,idx[Maxn+5]; map<int,int> mp;
struct Seg{int l,r,x;} h[Maxn+5];
vector<int> w[Maxn+5],v[Maxn+5],g[Maxn+5];
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)

inline int Get(int x)
{
    if(!mp[x]) {idx[++tot]=x; return mp[x]=tot;}
    else return mp[x];
}
inline int Solve(int x)
{
    int sum=1,tag=1,it=0; s=v[x].size();
    For(i,0,s) w[i].clear();
    for(auto id:g[x])
    {
        int l=h[id].l,r=h[id].r;
        l=lower_bound(v[x].begin(),v[x].end(),l)-v[x].begin()+1;
        r=upper_bound(v[x].begin(),v[x].end(),r)-v[x].begin();
        if(l>r) return 0;
        w[r].push_back(l);
    }
    For(i,0,s) f[i]=0; f[0]=1,x=idx[x];
    For(i,1,s)
    {
        int mx=-1; for(auto j:w[i]) mx=max(mx,j);
        tag=1ll*tag*x%Mod;
        f[i]=1ll*sum*Pow(tag,Mod-2)%Mod;
        sum=(1ll*sum*x+1ll*f[i]*tag)%Mod;
        while(it<mx) sum=(sum-1ll*f[it]*tag%Mod+Mod)%Mod,it++;
    }
    return sum;
}
inline void GetVal()
{
    set<int> st;
    For(i,1,n) val[i]=m+1,st.insert(i);
    sort(h+1,h+q+1,[](Seg a,Seg b){return a.x<b.x;});
    For(i,1,q) g[Get(h[i].x)].push_back(i);
    For(i,1,q)
    {
        int l=h[i].l,r=h[i].r,x=h[i].x;
        for(auto it=st.lower_bound(l);it!=st.end() && *it<=r;it=st.erase(it))
            val[*it]=x;
    }
    For(i,1,n) v[Get(val[i])].push_back(i);
}

int main()
{
    n=read(),m=read(),q=read(),Get(m+1);
    For(i,1,q) {int l=read(),r=read(),x=read(); h[i]=(Seg){l,r,x};}
    GetVal();
    For(i,1,tot)
    {
        if(idx[i]!=m+1) ans=1ll*ans*Solve(i)%Mod;
        else ans=1ll*ans*Pow(m+1,v[i].size())%Mod;
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：MuelsyseU (赞：10)

[题意](https://www.luogu.com.cn/problem/AT_abc262_h)：

给定 $m$ 个限制 $(l_i,r_i,p_i)$ 及 $n,k$，求满足以下条件的长度为 $n$ 的不同序列 $a=(a_1,a_2,\cdots,a_n)$ 的数目。

1. $\forall i \in[1,n],0\leq a_i\leq k$

2. $\forall i \in[1,m],\max \limits_{j\in[l_i, r_i]}a_j=p_i$

同 [P4229](https://www.luogu.com.cn/problem/P4229)，但数据更强，目测只允许 $O(m\log m)$ 或类似复杂度通过。

----

考虑将条件 2 中每个限制拆分为：

- $\exists j\in[l_i,r_i],a_j=p_i$
- $\forall j\in[l_i,r_i],a_j\le p_i$

即任意位置 $j$ 的取值最多不能超过覆盖它的各个限制中 $p$ 的最小值 $c_j=\min_{i\in[1,m],j\in[l_i,r_i]}p_i$，同时对于每个限制，至少有一个位置取到 $p_i$；因此，取到 $p_i$ 的位置 $j$ 一定满足 $p_i=a_j$。

对位置离散化后，利用线段树及标记永久化进行简单的区间取 $\min$ 操作，则最后对于限制 $i$， $c_j=p_i$ 的位置 $j$ 才有可能取值 $[0,p_i]$，而该限制覆盖的其它显然只能取到 $[0,q]$，且一定有 $q<p$，故 $a_j\le p_i$，即这些位置并不影响该限制的满足性。

综上所述，我们可以对 $p$ 离散化，把覆盖后结果为 $x$ 的部分单独取出并进行 DP，求出满足 $p_i=x$ 的所有限制的方案数。所有 $x$ 的方案数之积即为答案。

此处细节：

1. 如果有 $d$ 个位置不被任何限制覆盖，这些位置方案数为 $(k+1)^d$。
2. 如果一个限制 $i$ 满足 $\forall j\in[l_i,r_i],c_j < p_i$，则总方案数为 $0$。线段树维护 $c_j$ 区间最大值即可。

---
将所有 $c_j=x$ 的位置及 $l,r$ 离散化后作为一个序列 $a'=(a'_1,a'_2,\cdots.a'_t)$ 集中考虑。注意有些位置离散化后是一个长度大于 $1$ 的连续段，设其长度为 $v_i$。

现在考虑如何在 $O(t\log t)$ 时间内解决以下 DP 问题：

> 给定 $m$ 个限制 $(l'_i,r'_i)$ 及 $x$，求满足以下条件的序列个数：

- $\forall i \in[1,t],\max \limits_{j\in[l'_i, r'_i]}a'_j=x$

不妨设 $f_{i}$ 为分配前 $i$ 位的方案数，$g_{i,j}$ 为分配前 $i$ 位，使得满足 $a'_k=x$ 的最大的 $k$ 等于 $j$ 的方案数。

显然如果第 $i$ 位并非必须取 $x$，$\forall j \in [1,i],g_{i,j}=x^{v_i}g_{i-1,j}$。这个操作可以用线段树区间乘完成。

如果第 $i$ 位取 $x$，即 $g_{i,i} = ((x+1)^{v_i} - x^{v_i})f_{i-1}$。

如果不取，考虑若存在部分区间最后一个覆盖的位置为 $i$，那么设这些区间左端点的最大值为 $h_i$，则 $[h_i,i]$ 至少需取一个 $x$。所以 $\forall j \in [1,h_i-1],g_{i,j} = 0$。线段树维护区间推平即可。

综上所述，$f_i=g_{i,i}+x^{v_i}\sum^{i-1}_{j=h_i}g_{i,j}$。区间和也可用线段树维护。

此处细节：

1. 需取模，计算可能出现负数。
2. 离散化后序列相邻两项在原序列不一定连续。

目标：$f_t$。答案：$(k+1)^d\prod_{x\in p}f_t$。时间复杂度 $O(m\log m)$，空间线性。

---

```cpp
#include <bits/stdc++.h>
#define maxm 400005
#define inf 0x3f3f3f3f
#define ad(i, j) i = (i % mod + j % mod + mod) % mod
#define mu(i, j) i = (i * j) % mod
#define ls(p) (p << 1)
#define rs(p) ((p << 1) + 1)
using namespace std;

const int mod = 998244353;
int n, m, k, num, nx, nf, b[maxm], bx[maxm];
int c[maxm];
struct Query {
    int l, r, x;
} a[maxm];
vector<int> q[maxm], v[maxm];
inline bool cmp(int i, int j) { return a[i].r == a[j].r ? a[i].l > a[j].l : a[i].r < a[j].r; }
long long ans, f[maxm], g[maxm];
// Basic
inline int len(int x) { return (x & 1) ? (b[(x >> 1) + 1] - b[x >> 1] - 1) : 1; }
inline int qpow(int x, int p) {
    if (!p) return 1;
    long long tx = qpow(x, p >> 1);
    return (p & 1) ? (tx * tx % mod * x % mod) : (tx * tx % mod);
}
// BIT
namespace Seg {
struct SegTree {
    long long sum, mul, cov;
} t[maxm * 4];
void build(int p, int l, int r) {
    t[p] = {g[l], 1, -1};
    if (l < r) {
        int mid = (l + r) >> 1;
        build(ls(p), l, mid), build(rs(p), mid + 1, r);
        t[p].sum = (t[ls(p)].sum + t[rs(p)].sum) % mod;
    }
}
inline void spread(int p) {
    if (~t[p].cov) {
        t[ls(p)].sum = t[ls(p)].cov = t[rs(p)].sum = t[rs(p)].cov = t[p].cov;
        t[ls(p)].mul = t[rs(p)].mul = 1;
        t[p].cov = -1;
    }
    if (t[p].mul > 1) {
        mu(t[ls(p)].sum, t[p].mul), mu(t[rs(p)].sum, t[p].mul);
        mu(t[ls(p)].mul, t[p].mul), mu(t[rs(p)].mul, t[p].mul);
        t[p].mul = 1;
    }
}
void change(int p, int pl, int pr, int l, int r, int x, int tg = 0) {
    if (l > r) return;
    if (pl >= l && pr <= r) {
        if (tg) t[p].mul = 1, t[p].sum = t[p].cov = x;
        else mu(t[p].mul, x), mu(t[p].sum, x);
    } else {
        spread(p);
        int mid = (pl + pr) >> 1;
        if (l <= mid) change(ls(p), pl, mid, l, r, x, tg);
        if (r > mid) change(rs(p), mid + 1, pr, l, r, x, tg);
        t[p].sum = (t[ls(p)].sum + t[rs(p)].sum) % mod;
    }
}
long long ask(int p, int pl, int pr, int l, int r) {
    if (l > r) return 0;
    else if (pl >= l && pr <= r) return t[p].sum;
    spread(p);
    int mid = (pl + pr) >> 1;
    long long ans = 0;
    if (l <= mid) ad(ans, ask(ls(p), pl, mid, l, r));
    if (r > mid) ad(ans, ask(rs(p), mid + 1, pr, l, r));
    return ans;
}
};
namespace Mn {
int ma[maxm * 4], tg[maxm * 4];
inline void init() { memset(tg, 0x3f, sizeof(tg)); }
void cover(int p, int pl, int pr, int l, int r, int x) {
    if (pl >= l && pr <= r) tg[p] = min(tg[p], x);
    else {
        int mid = (pl + pr) >> 1;
        if (l <= mid) cover(ls(p), pl, mid, l, r, x);
        if (r > mid) cover(rs(p), mid + 1, pr, l, r, x);
    }
}
void dfs(int p, int l, int r, int x) {
    int mid = (l + r) >> 1;
    x = min(x, tg[p]);
    if (l == r) c[l] = x, ma[p] = len(l) ? x : 0;
    else dfs(ls(p), l, mid, x), dfs(rs(p), mid + 1, r, x), ma[p] = max(ma[ls(p)], ma[rs(p)]);
}
int ask(int p, int pl, int pr, int l, int r) {
    if (pl >= l && pr <= r) return ma[p];
    int mid = (pl + pr) >> 1, ans = 0;
    if (l <= mid) ans = max(ans, ask(ls(p), pl, mid, l, r));
    if (r > mid) ans = max(ans, ask(rs(p), mid + 1, pr, l, r));
    return ans;
}
};
signed main() {
    ans = 1, num = nx = 0;
    scanf("%d%d%d", &n, &k, &m), ++k;
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d%d", &a[i].l, &a[i].r, &a[i].x), ++a[i].x;
        b[++num] = a[i].l, b[++num] = a[i].r, bx[++nx] = a[i].x;
    }
    sort(b + 1, b + 1 + num), num = unique(b + 1, b + 1 + num) - b - 1;
    sort(bx + 1, bx + 1 + nx), nx = unique(bx + 1, bx + 1 + nx) - bx - 1;
    b[num + 1] = n + 1, n = num * 2 + 1;
    Mn::init();
    for (int i = 1; i <= m; ++i) {
        a[i].l = (lower_bound(b + 1, b + 1 + num, a[i].l) - b) << 1;
        a[i].r = (lower_bound(b + 1, b + 1 + num, a[i].r) - b) << 1;
        a[i].x = lower_bound(bx + 1, bx + 1 + nx, a[i].x) - bx;
        q[a[i].x].push_back(i);
        Mn::cover(1, 1, n, a[i].l, a[i].r, a[i].x);
    }
    Mn::dfs(1, 1, n, inf);
    // 3 m log m
    for (int i = 1; i <= m; ++i)
        if (Mn::ask(1, 1, n, a[i].l, a[i].r) < a[i].x) {
            puts("0");
            return 0;
        }
    for (int i = 1; i <= n; ++i)
        if (c[i] < inf && len(i)) v[c[i]].push_back(i);
        else if (len(i)) mu(ans, qpow(k, len(i)));
    for (int x = 1; x <= nx; ++x) {
        nf = v[x].size();
        for (int i = 1; i <= nf; ++i) f[i] = g[i] = 0;
        sort(q[x].begin(), q[x].end(), cmp);
        Seg::build(1, 1, nf);
        int p = -1;
        f[0] = 1;
        for (int i = 1; i <= nf; ++i) {
            int ln = len(v[x][i - 1]);
            long long t = f[i - 1] * ((qpow(bx[x], ln) - qpow(bx[x] - 1, ln) + mod) % mod) % mod;
            int nxt = i < nf ? v[x][i] : inf, l = 0;
            while (p < int(q[x].size() - 1) && a[q[x][p + 1]].r < nxt) ++p, l = max(l, a[q[x][p]].l);
            if (l) {
                auto lp = lower_bound(v[x].begin(), v[x].end(), l);
                l = lp - v[x].begin() + 1;
            }
            if (!l) f[i] = f[i - 1] * qpow(bx[x], ln) % mod;
            else {
                f[i] = (t + Seg::ask(1, 1, nf, l, i - 1) * qpow(bx[x] - 1, ln) % mod) % mod;
                Seg::change(1, 1, nf, 1, l - 1, 0, 1);
            
            }
            Seg::change(1, 1, nf, i, i, t, 1);
            Seg::change(1, 1, nf, 1, i - 1, qpow(bx[x] - 1, ln));
        }
        mu(ans, f[nf]);
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：Coffee_zzz (赞：5)

首先，我们可以用线段树求出每个位置 $i$ 的值域上界 $v_i$。具体而言，我们有：

$$
v_i=\min_{l_j \le i \le r_j} x_j
$$

接下来，我们分别对于每一个值域上界 $w$ 进行动态规划。

我们拎出所有满足 $v_i=w$ 的位置 $i$，设这些位置分别为 $c_1,c_2,\cdots,c_s$。

同时，我们也拎出所有满足 $x_i=w$ 的限制 $i$，设这些限制分别为 $d_1,d_2,\cdots,d_t$。

显然我们只关心我们拎出的每个位置所填的值是否是 $w$，所以我们可以定义 $f_{i,j}$ 表示当前考虑到第 $c_i$ 位且上一个所填的值为 $w$ 的位置为 $c_j$ 的方案数。

初始化 $f_{0,0}=1$。为了方便，我们认为 $c_0=0$，$c_{s+1}=n+1$。

先不考虑限制，尝试转移：

$$
\begin{aligned}
&f_{i,i}=\sum_{j=0}^{i-1} f_{i-1,j}\\
&f_{i,j}=f_{i-1,j} \times w
\end{aligned}
$$

注意到，此时每个限制相当于要求 $[l_{d_j},r_{d_j}]$ 中有至少一个位置的值为 $w$，所以只需要在 $c_i \le r_{d_j} \lt c_{i+1}$ 时将所有满足 $k \lt l_{d_j}$ 的 $f_{i,k}$ 的值赋为 $0$ 即可。

我们可以用线段树维护 $f$ 数组，只需要支持单点修改、区间乘、区间求和即可。此时的方案数即为 $\sum\limits_{i=0}^s f_{s,i}$。

最终的答案即为每个值域上界的方案数之积，注意每个没有被限制覆盖的位置的贡献均为 $m+1$。

时间复杂度 $\mathcal O(n\log n)$。

```c++
#include <bits/stdc++.h>

#define ll long long
#define i128 __int128
#define endl '\n'
#define pb push_back
#define pii pair<int,int>
#define fi first
#define se second
#define vei vector<int>
#define pq priority_queue
#define yes puts("yes")
#define no puts("no")
#define Yes puts("Yes")
#define No puts("No")
#define YES puts("YES")
#define NO puts("NO")
#define In(x) freopen(x".in","r",stdin)
#define Out(x) freopen(x".out","w",stdout)
#define File(x) (In(x),Out(x))
using namespace std;
const int N=2e5+5,inf=1e9,mod=998244353;
int n,m,q,l[N],r[N],x[N],v[N],mi[N<<2],c[N],d[N],s,t,w,val[N<<2],tag[N<<2],ans=1;
pii a[N],b[N];
void work(int g,int l,int r,int x,int y,int k){
	if(x<=l&&r<=y){
		mi[g]=min(mi[g],k);
		return;
	}
	if(r<x||y<l) return;
	int m=(l+r)>>1;
	work(g<<1,l,m,x,y,k);
	work(g<<1|1,m+1,r,x,y,k);
}
void search(int g,int l,int r,int k){
	k=min(mi[g],k);
	if(l==r){
		v[l]=k;
		return;
	}
	int m=(l+r)>>1;
	search(g<<1,l,m,k);
	search(g<<1|1,m+1,r,k);
}
int add(int a,int b){
	return a+b>=mod?a+b-mod:a+b;
}
int mul(int a,int b){
	return 1ll*a*b%mod;
}
void upd(int g){
	val[g]=add(val[g<<1],val[g<<1|1]);
}
void down(int g){
	tag[g<<1]=mul(tag[g<<1],tag[g]);
	tag[g<<1|1]=mul(tag[g<<1|1],tag[g]);
	val[g<<1]=mul(val[g<<1],tag[g]);
	val[g<<1|1]=mul(val[g<<1|1],tag[g]);
	tag[g]=1;
}
void build(int g,int l,int r){
	val[g]=0;
	tag[g]=1;
	if(l==r) return;
	int m=(l+r)>>1;
	build(g<<1,l,m);
	build(g<<1|1,m+1,r);
}
void modify(int g,int l,int r,int x,int k){
	if(l==x&&r==x){
		val[g]=k;
		return;
	}
	if(r<x||x<l) return;
	down(g);
	int m=(l+r)>>1;
	modify(g<<1,l,m,x,k);
	modify(g<<1|1,m+1,r,x,k);
	upd(g);
}
void times(int g,int l,int r,int x,int y,int k){
	if(x<=l&&r<=y){
		tag[g]=mul(tag[g],k);
		val[g]=mul(val[g],k);
		return;
	}
	if(r<x||y<l) return;
	down(g);
	int m=(l+r)>>1;
	times(g<<1,l,m,x,y,k);
	times(g<<1|1,m+1,r,x,y,k);
	upd(g);
}
int ask(int g,int l,int r,int x,int y){
	if(x<=l&&r<=y) return val[g];
	if(r<x||y<l) return 0;
	down(g);
	int m=(l+r)>>1;
	return add(ask(g<<1,l,m,x,y),ask(g<<1|1,m+1,r,x,y));
}
bool cmp(int a,int b){
	return r[a]<r[b];
}
void dp(){
	sort(c+1,c+1+s);
	sort(d+1,d+1+t,cmp);
	c[s+1]=n+1;
	build(1,0,s);
	for(int i=0,j=1;i<=s;i++){
		if(i==0) modify(1,0,s,0,1);
		else{
			int sum=ask(1,0,s,0,i-1);
			modify(1,0,s,i,sum);
			times(1,0,s,0,i-1,w);
		}
		while(j<=t&&c[i]<=r[d[j]]&&r[d[j]]<c[i+1]){
			int pos=lower_bound(c,c+1+s,l[d[j]])-c-1;
			times(1,0,s,0,pos,0);
			j++;
		}
	}
	int sum=ask(1,0,s,0,s);
	ans=mul(ans,sum);
}
void solve(){
	cin>>n>>m>>q;
	for(int i=1;i<=q;i++) cin>>l[i]>>r[i]>>x[i];
	memset(mi,0x3f,sizeof mi);
	for(int i=1;i<=q;i++) work(1,1,n,l[i],r[i],x[i]);
	search(1,1,n,inf);
	for(int i=1;i<=n;i++) a[i].fi=v[i],a[i].se=i;
	for(int i=1;i<=q;i++) b[i].fi=x[i],b[i].se=i;
	sort(a+1,a+1+n);
	sort(b+1,b+1+q);
	for(int i=1,j=1;j<=q;){
		s=0,t=0,w=b[j].fi;
		while(a[i].fi==w) c[++s]=a[i++].se;
		while(b[j].fi==w) d[++t]=b[j++].se;
		dp();
	}
	for(int i=1;i<=n;i++) if(v[i]==inf) ans=mul(ans,m+1);
	cout<<ans<<endl;
}
signed main(){
	ios::sync_with_stdio(0);
	signed T=1;
//	cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：teylnol_evteyl (赞：4)

考虑一个弱化版：给定 $m$ 个区间 $[l_i,r_i]$，且 $\bigcup[l_i,r_i]=[1,n]$，求长度为 $n$ 的满足 $\max\limits_{i=l_i}\limits^{r_i}=X$ 的非负整数序列数量。

首先将区间按左端点有小到大排序，然后去掉所有包含其它区间的区间，因为如果包含的区间满足条件，则它一定也满足条件。

设 $f_{i,j}$ 表示考虑前 $i$ 个点和 $r_i\leq i$ 的区间，最后一个值为 $X$ 的点是 $j$ 的方案数，对于第 $i$ 个点，决策有选 $X$ 和不选 $X$ 两种：

- 如果选 $x$，则 $\forall j<i,f_{i,i}\gets f_{i,i}+f_{i-1,j}$。
- 如果不选 $x$，则 $\forall j<i,f_{i,j}\gets f_{i,j}+Xf_{i-1,j}$。
- 同时，设 $L_i$ 表示 $r_j=i$ 的 $l_j$（不存在则为 $0$），则 $\forall j<L_i,f_{i,j}\gets0$。

可以用一个支持单点加、区间乘、区间求和的线段树实现。

然后回到原问题。把区间按权值排序有小到大、权值相同的按左端点排序，对于一个区间，权值较小的区间包含的位置一定不会使他的最大值满足条件，所以可以找出当前权值最小的区间，找到一个连续段的区间使得它们权值相同且并集是一个区间，跑上面的算法，并把最后答案乘上跑出的答案，最后把它们包含的点删除。可以用并查集和树状数组实现删除和查询在删除后区间实际包含的位置。

时间复杂度 $O(n\log n)$。

记得根据需求开 long long。

[code](https://www.luogu.com.cn/paste/j7tjxoh0)。

---

## 作者：hgckythgcfhk (赞：3)

先说句闲话，这个题为什么要写线段树呢

我们挖掘一下区间最大值的性质：

1. 如果一个区间被另一个最大值更小的区间包含，显然无解。

2. 如果一个区间被另一个最大值更大的区间包含，把这段区间扣掉不会影响剩下的部分。

3. 不交区间互不影响。

题意转化一下，给定若干个区间，第 $i$ 个区间的所有数小于等于 $x_i$，且这个区间内有至少一个数等于 $x_i$。

这样，我们把区间最值这一个条件拆成了两个条件，看似更麻烦了，但我们发现这两个条件是比较容易 ```dp``` 的。

对于区间相关的问题，显然我们只喜欢相离的情况，无论是包含还是相交但不包含都不是什么好东西，目前，相交但不包含的情况大家可以试试刻画一下性质，发现并不是很好描述，通过上面的性质，我们发现包含的性质比较好描述，目前我们已经讨论了两种情况，现在思路很明确，我们需要讨论一下最大值相等的包含关系的区间。

上面我们已经完成了题意的转化，我们发现，对于两个相互包含的区间 $[l1,r1],[l2,r2],l1\le l2\le r2\le r1$，可以拆出 $4$ 个 条件，设区间最大值为 $x$。

1. 在区间 $[l1,r1]$ 中有一个数等于 $x$。
2. 区间 $[l1,r1]$ 的所有数小于等于 $x$。
3. 在区间 $[l2,r2]$ 中有一个数等于 $x$。
4. 区间 $[l2,r2]$ 的所有数小于等于 $x$。

我们发现，条件 $1$ 和 $3$ 有依赖关系，条件 $3$ 是条件 $1$ 的一个必要不充分条件，也就是说，只要满足了条件 $3$ 就一定满足条件 $1$，这个正确性非常显然。

同理，满足条件 $2$ 时也满足条件 $4$，于是，我们就可以把 $4$ 个条件合并成 $2$ 个，于是，我们重新定义一下区间是个什么东西，在原有定义的同时，给其增加一个控制范围，这样，对于所有最大值相同的区间，我们干掉了所有外层的大区间。

上面根据性质 $1$ 我们可以判断无解，根据性质 $2$，我们发现先处理最大值小的区间然后把这些区间扣掉并不影响最终结果，性质 $3$ 是句废话，没什么用，但它能启发我们往区间问题的一个思路上想，这个思路是最近刚刚学到的，我放到最后。

于是，做法就有了，按最大值升序处理所有区间，对每个最大值相同的区间计数，然后把这些区间扣掉，现在我们转化为了 $3$ 个更弱的问题。

1. 怎么处理没被任何区间覆盖的位置。
2. 对于所有最大值相同的区间怎么计数。
3. 怎么扣掉区间。

发现第一个问题是非常简单的组合数学基础问题，直接数有多少个位置没被任何区间覆盖然后把答案乘上 $(m+1)^{cnt}$ 就行，注意读题，序列里是**非负整数**，而不是**正整数**，我因为这个问题调了半天样例没过。

上面我们说过了，拆这两个条件方便 ```dp```，而且问题转化到这一步也没法继续转化了，就是一个长得非常像计数 ```dp``` 的问题。

直接设状态不说怎么想到的不太道德，所以我先解释一下这里设状态的时候我是怎么想的，重新描述一下这个子问题：

>
>给定若干个区间的覆盖区域为 $[l_i,r_i]$，控制范围为 $[L_i,R_i]$，对于每个区间，必须覆盖一个位置 $p$ 使得 $a_p=x$，对于每个区间控制范围的并，不存在一个位置 $p$ 使得 $a_p>x$，保证控制范围的并为整个序列，且每个区间能控制其覆盖区域，求方案数。

对于形如区间内“必须有”这种限制，而且是计数题，我们不太好直接用 $0/1$ 表示是否出现过，尤其是计数题，上一次出现的位置很重要，所以这个东西一定要记下来。

于是，我们设：$dp_{i,j}$ 表示到第 $i$ 个位置，上一个等于 $x$ 的数出现的位置为 $j$ 的方案数，最后的答案是 $\sum dp_{n,i}$。

发现 $i$ 这一维可以压掉，重新定义并解释状态，考虑到第 $i$ 个位置，强制这个位置的数必须等于 $x$ 的方案数，这样看起来就比较线性了，考虑转移，设上一个等于 $x$ 的位置为 $j$：

$$dp_i=\sum{dp_j}\times x^{dis(i,j)}$$

注意，这里不一定是 $i-j$，因为我们可能扣掉了一些子区间。

考虑前缀和优化：

$$s_i=s_{last}\times x+dp_i$$

则有：

$$dp_i=s_{last}$$

注意，我们只能转移的位置不是任意的，有些位置不能转移，显然如果一个位置能转移，它后面一定能转移，设最后一个能转移的位置为 $lim_i$ 如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/cve156rt.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/sktxq67d.png)

不难发现，$lim_i$ 就是最后一个不覆盖该位置的区间的左端点，理解一下这件事情，覆盖该位置的区间都没有必要再选一个位置使其等于 $x$，不覆盖的不选不合法，也就是说上一个等于 $x$ 的位置不能比上一个 $i$ 贡献不到的区间更早。

我知道这里我讲的不够清楚，如果你看不懂的话其实是因为不会写，但大体思路是有了，具体细节看程序，这题确实不太好写，细节很多，先理解思路就行。

最后就是扣区间的问题了，扣区间等于扣区间**控制**的所有位置，注意，不是覆盖的位置，控制和覆盖的区别见上面我临时的定义。

对于一个单点，我听别人说的写法是用链表，但感觉这个写法容易把时间复杂度写假，所以推荐一种好写的写法，用一个类似并查集的东西，$f_i$ 表示每个位置向右第一个没被删的位置，如果这个位置没被删那就是这个位置本身，注意这并不完全是并查集，这个东西不支持按秩合并，正常的并查集每个节点不仅可以让自己的父亲成为自己的兄弟，而且还能让自己的父亲成为自己的儿子，但这里不能倒反天罡，否则虽然可以用一个靠左一点的位置表示这一堆被删掉的位置和右边一个没删的位置，但无法找到下一个位置，你可以多维护一个信息使其做到严格的均摊 $O(1)$，但这个题好像不太能卡到 $\log n$，我目前没造出这样的数据，~~而且这并不影响过了这个题~~。

整个算法流程呼之欲出，按最大值对区间排序，然后对于每个最大值的区间扔到 ```solve``` 里面，```dp``` 计算这些区间的方案数，删掉这些区间的所有位置，最后统计剩余位置的答案与前面的答案相乘。

由于值域非常小，注意到 $2^{16}=65536$，而 $2\times 65536\le maxn$ 且 $65536^2>10^9$，所以排序是线性的，暂且认为这个类似并查集的东西是 $O(1)$ 的，所以最后时间复杂度 $O(n)$，时间复杂度的瓶颈在于这个类似并查集的东西，如果你愿意麻烦一点那就真的线性了。

具体的写法看程序，这个题我调了一整天和好多空闲时间，细节实在太多，所以打算重写一遍详细注释版的，以此更好的研究那些难调的细节，由于打算写详细的注释，所以题解写的比较简略而且没说细节，请见谅。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int register unsigned
#define vint basic_string<unsigned>
constexpr unsigned p=998244353,N=1e6;
struct A{
	unsigned l,r,x;
}a[N],b[N];
unsigned pos[N],dp[N],pw[N],c[N],lim[N],f[N];
vint t[1<<16];unsigned id=0,cnt,ans=1,n,m,q;
inline unsigned fd(const int x){return x==f[x]?x:f[x]=fd(f[x]);}
void SORT(){if(cnt<=128)sort(pos,pos+cnt+1);
	else{//防止 x 互不相同
	for(int i=1;i<=cnt;++i)t[pos[i]&0x1ff]+=i;
	for(int i=0;i<512;++i)for(const int&j:t[i])c[++id]=pos[j];
	cnt=0;for(int i=0;i<512;++i)t[i]=vint();
	for(int i=1;i<=id;++i)t[ c [i]>>9]+=i;
	for(int i=0;i<512;++i)for(const int&j:t[i])pos[++cnt]=c[j];
	id=0;for(int i=0;i<512;++i)t[i]=vint();}id=0;
	
	for(int i=0;i<cnt;++i)if(pos[i]^pos[i+1])c[++id]=pos[i+1];//去重，我的写法会有重复，有的没有
	for(int i=1;i<=id;++i)pos[i]=c[i];cnt=id;id=0;
	if(cnt==1)cout<<0,exit(0);//只加入 n+1 这一个点，说明前面的删点操作把这个最大值的所有区间扣掉了
	//不写会 WA on test_01 我调了很长时间，这里相当于一个区间被另一个最大值更小的区间包含
}
void solve(const int l,const int r){
	const int x=a[l].x;
	cnt=0;
	for(int i=l;i<=r;++i){
		for(int j=fd(a[i].l);j<=a[i].r;)
		pos[++cnt]=j,f[j]=fd(j+1),j=f[j];//一边加一遍删，否则时间复杂度 n^2
	}pos[++cnt]=n+1;SORT();//跟 AT 提交记录里学的好写法，加一个点避免处理边界
	for(int i=1;i<=cnt;++i)pw[i]=1ll*pw[i-1]*x%p;
	for(int i=l,j=1;i<=r;++i){
		while(pos[j+1]<=a[i].r)++j;a[i].r=pos[j];}
		//最后一个小于 r 的位置
	for(int i=l;i<=r;++i)//每个右端点只留一个左端点，这也是删大区间的一步
		lim[a[i].r]=max(a[i].l,lim[a[i].r]);
		//后面所有的下标我都直接用这个位置的真实位置，每个真实位置只会用
		//不超过一次，可以避免清空导致的额外码量和落下写挂
	int s=1,j=0;//j 是一个指针，不断移动指针避免二分导致时间复杂度写假
	for(int i=1;i<=cnt;++i){//对于右端点不同的包含，显然小区间右端点小
		dp[pos[i]]=s;
		s=(1ll*s*x%p+dp[pos[i]])%p;
		while(pos[j]<lim[pos[i]]){//当到大区间右端点时不进这里，而 s 加了一个
			s=(s-1ll*dp[pos[j]]*pw[i-j]%p+p)%p;//从lim[i]-1 到 i-1
			++j;//可以转移，根据定义后面的 (i-1)-(j-1)=i-j 个小于 x 任选
		}
	}ans=1ll*ans*dp[n+1]%p;//dp[n+1]=s[pos[cnt]]，也就是后面能转移的所有
	//位置为最后一个等于 x 的位置的和。
}
signed main(){ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	freopen("1.in","r",stdin),freopen("1.out","w",stdout);
	cin>>n>>m>>q;pw[0]=1;
	for(int i=1;i<=n+1;++i)f[i]=i;//必须到 n+1 否则 RE
	for(int i=1;i<=q;++i)cin>>a[i].l>>a[i].r>>a[i].x;

/*-------------------------------------------------------------*/
//2. 按右端点升序
	for(int i=1;i<=q;++i)t[a[i].r&0xffff]+=i;
	for(int i=0;i<=0xffff;++i)for(int&j:t[i])b[++id]=a[j];
	id=0;for(int i=0;i<=0xffff;++i)t[i]=vint();
	for(int i=1;i<=q;++i)t[b[i].r>>16]+=i;
	for(int i=0;i<=0xffff;++i)for(int&j:t[i])a[++id]=b[j];
	id=0;for(int i=0;i<=0xffff;++i)t[i]=vint();
/*-------------------------------------------------------------*/
//注意，不能按左端点，因为我们 dp 的过程中要扔掉大区间，对于端点相同的区间
//无法确定那个更大，我的写法求 lim 的时候会对左端点取 max，这个与写法有关。
/*-------------------------------------------------------------*/
//1. 按最大值升序
	for(int i=1;i<=q;++i)t[a[i].x&0xffff]+=i;
	for(int i=0;i<=0xffff;++i)for(int&j:t[i])b[++id]=a[j];
	id=0;for(int i=0;i<=0xffff;++i)t[i]=vint();
	for(int i=1;i<=q;++i)t[b[i].x>>16]+=i;
	for(int i=0;i<=0xffff;++i)for(int&j:t[i])a[++id]=b[j];
	id=0;for(int i=0;i<=0xffff;++i)t[i]=vint();
/*-------------------------------------------------------------*/
	dp[0]=1;
	for(int l=1,r=1;r<=q;l=r+1,r=l){
		while(a[l].x==a[r+1].x)++r;
		solve(l,r);
	}for(int i=1;i<=n;++i)if(fd(i)==i)
	ans=1ll*(m+1)*ans%p;cout<<ans;
  system("./1"),system("diff 1.out 1.ans");
}
```
这次没有大串的宏定义，主要是为了把程序放上，这题主要难在细节太多。

对上面程序的一个说明，```dp``` 值存在真实位置而不是 $pos$ 中的位置可以不用清空，这个方法是正确的，因为除了 $n+1$ 以外每个点最多被删一次，也最多存一个值，而 $n+1$ 每次会被直接覆盖掉，有人问过我这个问题，所以这里单独说一下。

---

## 作者：苏联小渣 (赞：2)

首先容易想到求出每个位置的值域上界，不妨记为 $b_i$。这个相当于区间取 min 最后对所有单点求值，离线下来扫描线，对于 $(l,r,x)$，在 $l$ 处加入 $x$，在 $r+1$ 处删去 $x$，用 multiset 之类的数据结构维护当前存在的数，然后每个单点查询最小值即可。

对于一个限制 $(l,r,x)$，此时有 $\forall i \in [l,r],b_i \le x$，且不难发现对于所有 $b_i<x$ 的 $i$，它们无论怎么填都不可能成为最大值 $x$，所以我们先不用管。那么我们只需要考虑那些满足 $b_i=x$ 的 $i$。若这个位置填的数 $<x$，那么对限制没有影响；若填的数 $=x$，就满足了这个限制。不难发现不同的 $x$ 是相互独立的，这启示我们可以对于每个值 $x$，把所有满足 $b_i=x$ 的位置和等于 $x$ 的限制单独拿出来，求出方案数再乘起来。

设当前考虑到 $x$，我们把所有 $b_i=x$ 拿出来形成了一个新序列，并且拿出所有限制 $(l,r,x)$。若一个位置填的数为 $x$，则把这个位置标记为 $1$，现在限制转化为，区间 $[l,r]$ 中至少有一个 $1$。于是我们要计数的对象就转化成了，给定一个序列，每个位置可以填 $0$ 或 $1$，其中填 $0$ 对应 $x$ 种方案，填 $1$ 对应 $1$ 种方案，要满足若干个限制，形如区间 $[l,r]$ 中至少有一个 $1$，求方案数。

这是一个很经典的 dp，甚至和 CSP-S 2024 T2 几乎一样。设 $f_i$ 表示最后一个 $1$ 位置在 $i$ 位置的方案数，那么容易得到上一个 $1$ 的位置应该是一段区间 $[l,i-1]$，这个区间容易维护得到。那么有转移：

$$f_i=\sum _{j \ge l} f_j \times x^{i-j-1}$$

把式子拆开：

$$f_i=x^{i-1} \sum _{j \ge l} \dfrac{f_j}{x^j}$$

显然逆元存在，所以维护一个 $\dfrac{f_j}{x^j}$ 的前缀和，转移就很容易了，并不用线段树之类的数据结构。最后把所有不同的 $x$ 的方案数乘起来即可，时间复杂度 $O(n \log n)$。

注意一些细节：

- 如果有一些位置没有限制，那么方案数是 $m+1$，注意乘上；

- 若某个值 $x$ 没有对应的位置但是有限制，那么无解。

还有其他一些细节写着写着就会发现了。代码其实很好写。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
int n, m, q, cnt, tot, ans=1, a[200010], c[200010], mxl[200010], rev[200010], f[200010], pre[200010], vis[200010];
struct node{
	int l, r, x;
}b[200010];
struct Add{
	int x, op;
};
struct segment{
	int l, r;
};
vector <Add> ad[200010];
multiset <int> s;
map <int, int> mp;
map <int, int> :: iterator it;
vector <int> pos[200010];
vector <segment> lim[200010];
const int mo = 998244353;
int power(int x, int y){
	int ret = 1;
	while (y){
		if (y&1) ret = 1LL * ret * x % mo;
		x = 1LL * x * x % mo;
		y >>= 1;
	}
	return ret;
}
int main(){
	scanf ("%d%d%d", &n, &m, &q);
	for (int i=1; i<=n; i++) a[i] = m;
	mp[m] = 1;
	for (int i=1; i<=q; i++){
		scanf ("%d%d%d", &b[i].l, &b[i].r, &b[i].x);
		ad[b[i].l].push_back((Add){b[i].x, 1});
		ad[b[i].r+1].push_back((Add){b[i].x, -1});
		mp[b[i].x] = 1;
	}
	for (it=mp.begin(); it!=mp.end(); it++){
		it->second = ++cnt;
		rev[cnt] = it->first;
	}
	for (int i=1; i<=n; i++){
		for (int j=0; j<ad[i].size(); j++){
			int x = ad[i][j].x, op = ad[i][j].op;
			if (op == 1) s.insert(x);
			else s.erase(s.find(x));
		}
		if (!s.empty()) a[i] = *(s.begin());
	}
	for (int i=1; i<=n; i++){
		pos[mp[a[i]]].push_back(i);
	}
	for (int i=1; i<=q; i++){
		lim[mp[b[i].x]].push_back((segment){b[i].l, b[i].r});
	}
	for (int i=1; i<=cnt; i++){
		if (!pos[i].size()){
			if (lim[i].size()) return puts ("0"), 0;
			continue;
		}
		if (!lim[i].size()) continue;
		tot = 0;
		int val = rev[i], tmp = 0;
		for (int j=0; j<pos[i].size(); j++){
			c[++tot] = pos[i][j];
			mxl[tot] = pre[tot] = f[tot] = 0;
			vis[c[tot]] = 1;
		}
		for (int j=0; j<lim[i].size(); j++){
			int l = lim[i][j].l, r = lim[i][j].r;
			l = lower_bound(c+1, c+tot+1, l) - c;
			r = upper_bound(c+1, c+tot+1, r) - c - 1;
			if (l > r) return puts ("0"), 0;
			tmp = max(tmp, l);
			mxl[r] = max(mxl[r], l);
		}
		int nowl = 0, pw = 1, ret = 0;
		pre[0] = 1;
		for (int j=1; j<=tot; j++){
			if (nowl) f[j] = 1LL*(pre[j-1]-pre[nowl-1]+mo)%mo * pw % mo;
			else f[j] = 1LL*pre[j-1]*pw % mo;
			pw = 1LL * pw * val % mo;
			pre[j] = (pre[j-1] + 1LL*f[j]*power(pw, mo-2) % mo) % mo;
			if (j >= tmp) ret = (ret + 1LL*f[j]*power(val, tot-j)%mo) % mo;
			nowl = max(nowl, mxl[j]);
		}
		ans = 1LL * ans * ret % mo;
	}
	for (int i=1; i<=n; i++){
		if (!vis[i]) ans = 1LL * ans * (a[i]+1) % mo;
	}
	printf ("%d\n", ans);
	return 0;
}
```

---

## 作者：Little09 (赞：2)

某位歌姬的故事。

首先假设 $mx_i$ 表示第 $i$ 个位置最大能取到多少，我们可以用并查集或线段树维护出 $mx$。现在有一个关键性质：不同的 $mx$ 之间独立。

考虑一个区间 $[l,r]$ 以及限制 $w$，首先肯定有这个区间内所有位置的 $mx_i\le w$，若 $mx_i<w$，那么这个位置一定取不到 $w$，也就是条件变成了在这个区间内满足 $mx_i=w$ 的点必须至少一个满足 $a_i=w$。

所以我们只要枚举每个 $mx$ 的值，拎出所有 $mx$ 相等的位置和对应的区间限制算答案，最后再乘起来即可。（没有被任何区间覆盖的需要单独讨论）

问题转化成：有若干个点和若干个区间，要求这些点满足 $a_i\le mx$，且每个区间内至少有一个点的 $a_i=mx$，求方案数。

注意到包含其他区间的区间是没用的，把它们扔掉后剩下的区间排序一定满足随着左端点增加右端点也增加。考虑 $dp_i$ 表示目前做到第 $i$ 个点，要求第 $i$ 个点必须满足 $a_i=mx$，并且 $i$ 之前的区间都满足限制的方案数。考虑 $dp_i$ 可以从 $dp_k$ 转移过来的条件是找到 $i$ 前面最后一个与 $i$ 无交的区间，$k$ 不能小于这个区间的左端点。也就是 $k$ 是一段区间，可以算出来。

转移的时候把式子列出来，大概形如：

$$dp_i=\sum_kdp_k\times mx^{i-k-1}$$

$mx$ 有逆元的话就可以前缀和优化，特判 $mx=0$。

时间复杂度是线性对数，瓶颈在于一开始的并查集和快速幂。代码写的有点丑，而且是按照 某位歌姬的故事 改的，所以还把下标离散化了，更难写。

---

## 作者：DaiRuiChen007 (赞：2)

# ABC262Ex 题解



[Problem Link](https://www.luogu.com.cn/problem/AT_abc262_h)



## 题目大意

> 对于一个长度为 $n$ 的序列 $a_1,a_2,\dots,a_n$，每个元素的值域为 $[1,m]$，$q$ 组限制形如 $\max\limits_{i=l}^r\{a_i\}=w$。求有多少合法的 $a_1\sim a_n$。
>
> 数据范围：$n,q\le 2\times 10^5$。



## 思路分析

考虑从小往大枚举 $w$，对于 $w$ 相同的区间一起处理，处理之前删掉那些被 $w$ 更小区间覆盖的位置，因为这些位置已经被考虑过了，它们无论怎么取值也不影响答案。

离散化值域，只保留需要考虑的点（即被覆盖的线段最小 $w$ 即为当前枚举的 $w$ 的点），重编号线段，设为左闭右开区间，并删除含有包含关系的线段，然后根据左端点升序排序。

考虑最朴素的容斥：枚举线段集合 $S$，设这些线段的交为 $T$，那么这个集合对答案的贡献为 $(-1)^{|S|}\times (w-1)^{|T|}\times w^{k-|T|}$，$k$ 为这一步剩下的点数。

考虑设计一个 dp 维护这个带权和，根据左端点从小到大枚举线段，设 $dp_{i}$ 表示选择 $i$ 在线段集合中时，前 $i$ 条线段覆盖位置的带权和，考虑上一条翻转线段 $j$ 与 $i$ 的关系得到：
$$
dp_{i}=-\sum_{R_j\ge L_i} dp_j\times (w-1)^{R_i-R_j}-\sum_{R_j<L_i} dp_{j}\times w^{L_i-R_j}\times (w-1)^{R_i-L_i}
$$
注意到我们只需要把 $dp_j\times (w-1)^{-R_j}$ 和 $dp_j\times w^{-R_j}$ 用树状数组维护在 $R_j$ 处即可快速转移，最终答案为 $\sum dp_i\times w^{k-R_i}$。

注意特殊处理 $w=0$ 的情况，此时当 $R_j=L_i$ 时，若将其归类为第二种情况则会错误地将 $w^{L_i-R_j}$ 算成 $0$，把这种情况放到第一种中处理即可。

时间复杂度 $\mathcal O((n+q)\log n)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e5+5,MOD=998244353;
inline int ksm(int a,int b=MOD-2,int p=MOD) {
    int ret=1;
    while(b) ret=(b&1?ret*a%p:ret),a=a*a%p,b=b>>1;
    return ret;
}
int n,V,m;
class FenwickTree {
    private:
        int tree[MAXN];
        vector <array<int,2>> ers;
    public:
        inline void Modify(int x,int v) {
            ers.push_back({x,v});
            for(;x<=n+1;x+=x&-x) tree[x]=(tree[x]+v)%MOD;
        }
        inline int Query(int x) {
            int ans=0;
            for(;x;x-=x&-x) ans=(ans+tree[x])%MOD;
            return ans;
        }
        inline void Clear() {
            for(auto I:ers) Modify(I[0],MOD-I[1]);
            ers.clear();
        }
}    F0,F1;
int dp[MAXN],L[MAXN],R[MAXN],f[MAXN];
signed main() {
    scanf("%lld%lld%lld",&n,&V,&m),++V;
    set <int> idx;
    map <int,vector<array<int,2>>> Sects;
    for(int i=1,l,r,x;i<=m;++i) scanf("%lld%lld%lld",&l,&r,&x),Sects[++x].push_back({l,++r});
    for(int i=1;i<=n+1;++i) idx.insert(i);
    int ans=1; 
    for(auto I:Sects) {
        int v=I.first,k=0;
        for(auto u:I.second) ++k,L[k]=u[0],R[k]=u[1];
        R[0]=1;
        set <int> Q;
        Q.insert(n+1);
        for(int i=1;i<=k;++i) {
            auto iL=idx.lower_bound(L[i]),iR=idx.lower_bound(R[i]);
            for(auto it=iL;it!=iR;++it) Q.insert(*it);
            idx.erase(iL,iR);
        }
        int tot=0,sum=0;
        for(int i:Q) f[i]=++tot;
        vector <array<int,2>> tmp,tmp2;
        for(int i=1;i<=k;++i) {
            L[i]=*Q.lower_bound(L[i]);
            R[i]=*Q.lower_bound(R[i]);
            L[i]=f[L[i]],R[i]=f[R[i]];
            tmp.push_back({L[i],R[i]});
        }
        sort(tmp.begin(),tmp.end(),[&](auto u,auto v){
            return u[0]==v[0]?u[1]<v[1]:u[0]>v[0];
        });
        int minR=tot+1;
        for(auto x:tmp) if(x[1]<minR) tmp2.push_back(x),minR=x[1];
        sort(tmp2.begin(),tmp2.end(),[&](auto u,auto v){ return u[1]<v[1]; });
        k=0;
        for(auto x:tmp2) ++k,L[k]=x[0],R[k]=x[1];
        int i0=ksm(v-1),i1=ksm(v);
        dp[0]=1,F0.Modify(1,i0),F1.Modify(1,i1);
        for(int i=1;i<=k;++i) {
            dp[i]=ksm(v-1,R[i])*(F0.Query(n)+MOD-F0.Query(L[i]-1))%MOD;
            dp[i]=(dp[i]+ksm(v-1,R[i]-L[i])*ksm(v,L[i])%MOD*F1.Query(L[i]-1)%MOD)%MOD;
            dp[i]=(MOD-dp[i])%MOD;
            F0.Modify(R[i],dp[i]*ksm(i0,R[i])%MOD);
            F1.Modify(R[i],dp[i]*ksm(i1,R[i])%MOD);
        }
        for(int i=0;i<=k;++i) sum=(sum+dp[i]*ksm(v,tot-R[i])%MOD)%MOD;
        F0.Clear(),F1.Clear();
        ans=ans*sum%MOD;
    }
    ans=ans*ksm(V,idx.size()-1)%MOD;
    printf("%lld\n",ans);
    return 0;
}

```

---

## 作者：Mirasycle (赞：1)

经典的区间约束题，和 [CF1327F](https://www.luogu.com.cn/problem/CF1327F) 很像。

我们可以对于每个位置求出它在所有约束下能填到的最大值，这一步可以扫描所有位置然后用一个堆来维护当前能取到的最大值（也就是对于所有对当前产生影响的约束最大值取 $\min$）。

然后我们可以发现一个性质，对于一个 $\max a_i=val$ 的限制，只有可能依靠那些上界为 $val$ 的位置来达成，因为上界小于 $val$ 的肯定不能填 $val$；上界大于 $val$ 的所在位置不在 $\max a_i=val$ 的限制的范围内，否则上界就会缩小为 $val$。

于是我们扫描值域，对于每种取值 $v$ 直接把所涉及的位置抽出来 dp 一下。

设 $dp_{i,j}$ 表示当前到了 $i$ 位置，上一次满足 $a_k=v$ 的位置为 $j$ 的方案数。

如果填入 $a_i=v$，那么 $dp_{i,i}\gets dp_{i-1,j}$。

如果 $a_i\neq v$，那么 $dp_{i,j}\gets dp_{i-1,j}\times v$。

对于每个限制 $[l,r]$，如果扫描到了 $r$ 位置，那么所有 $j<l$ 的位置都不合法，直接设置为 $0$ 即可。

于是我们只需要维护一个整体 dp，每次进行后缀 $\times v$，前缀设 $0$ 还有后缀添加一个全局和的点，可以用线段树维护或者打一个全局标记即可。

时间复杂度 $O(n\log n)$。


```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define fi first
#define se second
#define mp make_pair
using namespace std;
typedef long long ll;
const int maxn=2e5+10;
const int mod=998244353;
void add(int &x,int y){ x=x+y>=mod?x+y-mod:x+y; }
void sub(int &x,int y){ x=x<y?x-y+mod:x-y; }
void chkmax(int &x,int y){ x=x>y?x:y; }
void chkmin(int &x,int y){ x=x<y?x:y; }
struct limit{
	int l,r,x;
	bool operator < (const limit &rhs) const {
		if(x==rhs.x) return l!=rhs.l?l<rhs.l:r<rhs.r;
		else return (x<rhs.x); 
	}
}lim[maxn];
vector<int> ad[maxn],del[maxn],vec[maxn],vec2[maxn]; set<limit> s;
int val[maxn],mx[maxn],dp[maxn],c[maxn],tot=0,n,m,q,ans; 
int qpow(int x,int k){
	int res=1;
	for(;k;k>>=1){
		if(k&1) res=1ll*res*x%mod;
		x=1ll*x*x%mod;
	}
	return res;
}
int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n>>m>>q; ans=1;
	for(int i=1;i<=q;i++){
		cin>>lim[i].l>>lim[i].r>>lim[i].x; val[++tot]=lim[i].x;
		ad[lim[i].l].pb(i); del[lim[i].r+1].pb(i);
	}
	sort(val+1,val+1+tot); tot=unique(val+1,val+1+tot)-val-1; val[++tot]=m+1;
	for(int i=1;i<=q;i++) lim[i].x=lower_bound(val+1,val+1+tot,lim[i].x)-val,vec2[lim[i].x].pb(i); 
	for(int i=1;i<=n;i++){
		for(auto z:ad[i]) s.insert(lim[z]);
		for(auto z:del[i]) s.erase(lim[z]);
		if(!s.size()) vec[tot].pb(i);
		else{ limit z=*s.begin(); vec[z.x].pb(i); }
	}
	forpb(i); }
	}(int i=1;i<=tot;i++){
		if(i==tot){ ans=1ll*ans*qpow(m+1,vec[i].size())%mod; continue; };
		int cnt=0; for(auto v:vec[i]) c[++cnt]=v;
		for(auto z:vec2[i]){
			int L=lower_bound(c+1,c+1+cnt,lim[z].l)-c;
			int R=upper_bound(c+1,c+1+cnt,lim[z].r)-c-1;
			if(L>R){ cout<<"0"; return 0; }
			chkmax(mx[R],L);
		}
		int mul=1,len=0,sum=1; dp[0]=1;
		for(int j=1;j<=cnt;j++){
			mul=1ll*mul*val[i]%mod;
			dp[j]=1ll*sum*qpow(mul,mod-2)%mod;
			sum=(1ll*sum*val[i]%mod+1ll*dp[j]*mul%mod)%mod;
			while(len<mx[j]) sub(sum,1ll*dp[len]*mul%mod),len++;
		}
		for(int j=0;j<=cnt;j++) mx[j]=dp[j]=0; ans=1ll*ans*sum%mod;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：zifanwang (赞：1)

首先容易确定每个位置的上界，接下来考虑对每种上界分别求方案数，再乘起来。

对每一种上界将其对应的位置提出来，由于是区间 $\max$，只需要关注每个位置的值是否到达这个上界 $x$。枚举一个前缀，考虑维护 $f_i$ 表示最后一个达到上界位置为 $i$，确定完这个前缀中所有数的方案数。考虑确定当前枚举到的数 $p$：

1. $<x$，则将所有 $f_i\leftarrow f_i\cdot x$。
2. $=x$，则将 $f_p\leftarrow f_p+\sum f_i$

接下来只需要处理掉区间的限制，对于一个右端点为 $p$ 的区间 $[l,p]$，此时 $\forall i<l,f_i\leftarrow 0$ 即可，时间复杂度 $\mathcal O(n\log n)$，线段树或者双指针都可以实现。

参考代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define mxn 200003
#define md 998244353
#define pb push_back
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define rept(i,a,b) for(int i=(a);i<(b);++i)
#define drep(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
struct node{
	int l,r,x;
}d[mxn];
int n,m,q,a[mxn],c[mxn];
vector<int>p[mxn],s1[mxn],s2[mxn];
vector<node>as[mxn];
multiset<int>s;
ll ans=1,t[mxn<<2],f[mxn<<2];
void build(int p,int l,int r){
	t[p]=!l,f[p]=1;
	if(l==r)return;
	int mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
}
inline void tag(int p,ll x){
	t[p]=t[p]*x%md,f[p]=f[p]*x%md;
}
inline void push_down(int p){
	if(f[p]!=1){
		tag(p<<1,f[p]),tag(p<<1|1,f[p]);
		f[p]=1;
	}
}
void add(int p,int x,int y,int l,int r){
	t[p]=(t[p]+y)%md;
	if(l==r)return;
	int mid=(l+r)>>1;
	push_down(p);
	if(x<=mid)add(p<<1,x,y,l,mid);
	else add(p<<1|1,x,y,mid+1,r);
}
void upd(int p,int l,int r,int L,int R){
	if(l<=L&&R<=r){t[p]=f[p]=0;return;}
	int mid=(L+R)>>1;
	push_down(p);
	if(l<=mid)upd(p<<1,l,r,L,mid);
	if(r>mid)upd(p<<1|1,l,r,mid+1,R);
	t[p]=(t[p<<1]+t[p<<1|1])%md;
}
void solve(int x){
	rept(i,0,p[x].size())c[i]=-1;
	for(node i:as[x]){
		int l=lower_bound(p[x].begin(),p[x].end(),i.l)-p[x].begin(),r=upper_bound(p[x].begin(),p[x].end(),i.r)-p[x].begin()-1;
		if(l>r){
			puts("0");
			exit(0);
		}
		c[r]=max(c[r],l);
	}
	build(1,0,p[x].size());
	rept(i,0,p[x].size()){
		ll s=t[1];tag(1,a[x]);
		add(1,i+1,s,0,p[x].size());
		if(c[i]>=0)upd(1,0,c[i],0,p[x].size());
	}
	ans=ans*t[1]%md;
}
signed main(){
	scanf("%d%d%d",&n,&m,&q);
	for(int i=0,l,r,x;i<q;++i){
		scanf("%d%d%d",&l,&r,&x);
		s1[l].pb(x),s2[r+1].pb(x);
		d[i]={l,r,x};
		a[i]=x;
	}
	a[q]=m;sort(a,a+q+1);
	rep(i,1,n){
		for(int j:s1[i])s.insert(j);
		for(int j:s2[i])s.erase(s.find(j));
		int mx=s.size()?*s.begin():m;
		p[lower_bound(a,a+q+1,mx)-a].pb(i);
	}
	rept(i,0,q)as[lower_bound(a,a+q+1,d[i].x)-a].pb(d[i]);
	rep(i,0,q)if(as[i].size()||p[i].size())solve(i);
	cout<<ans;
	return 0;
}
```

---

## 作者：Purslane (赞：1)

# Solution

想容斥的这辈子有了。

把 $\max_{i=l}^r a_i=X$ 的限制弱化为 $a_i \le X$ 对 $l \le i \le r$ 恒成立。

这样每个位置得到上界 $u_i$。对于每个位置而言，它只有**取到上界**和**没取到上界**两种情况。（如果取不到上界，那么不会对任何区间产生影响，不做区分）

对于限制 $(l,r,x)$，只有 $l \le i \le r$ 且 $u_i=x$ 的 $i$ 对它是有用的，所以我们对于 $x$ 分别考虑。

问题变为：每个数取 $0$ 和 $1$ 有不同权值，我们希望 $l$ 到 $r$ 中**至少有一个 $1$**，问权值积的和。

这时候只需要按顺序 $\rm DP$，记录**最近的 $1$ 的位置**。

具体而言，设 $f_{i,j}$ 表示最近的 $1$ 距离是 $j$。假设右端点为 $i$ 的左端点最近为 $l$。

如果 $i$ 放 $1$，则 $f_{i-1,k}$ 都可以加到 $f_{i,i}$ 上。

否则，先将 $f_{i-1,*}$ 整体平移至 $f_{i,*}$，并且区间乘 $x$。但如果 $j < l$，则 $f_{i,j}$ 要清空。

因此问题变为：单点修改，区间乘，区间赋值。

其实不全是，一个位置被清空之后，它不可能有值了；而当 $x \neq 0$ 时，所有乘的数都是 $\neq 0$ 的，我们可以直接维护线性序列。

复杂度 $O(q \log q)$。

```cpp
#include<bits/stdc++.h>
#define int long long 
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10,MOD=998244353;
int n,m,q,l[MAXN],r[MAXN],x[MAXN],tot,lsh[MAXN],pre[MAXN],lim[MAXN],ans=1,dp[MAXN];
int qpow(int base,int p) {
	int ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;	
	}
	return ans;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m>>q;
	set<int> pos;
	ffor(i,1,n) pos.insert(i);
	map<int,vector<int>> mp;
	ffor(i,1,q) cin>>l[i]>>r[i]>>x[i],mp[x[i]].push_back(i);
	for(auto pr:mp) {
		if(pr.first==0) continue ;
		auto vc=pr.second;
		tot=0;
		for(auto id:vc) {
			while(1) {
				auto it=pos.lower_bound(l[id]);
				if(it==pos.end()||*it>r[id]) break ;
				lsh[++tot]=*it,pos.erase(it);
			}
		}
		sort(lsh+1,lsh+tot+1);
		ffor(i,1,tot) lim[i]=0;
		for(auto i:vc) {
			l[i]=lower_bound(lsh+1,lsh+tot+1,l[i])-lsh;
			r[i]=upper_bound(lsh+1,lsh+tot+1,r[i])-lsh-1;
			if(l[i]>r[i]) return cout<<0,0;	
			lim[r[i]]=max(lim[r[i]],l[i]);
		}
		int sum=1,tag=1,pos=0;
		dp[0]=1;
		ffor(i,1,tot) {
			tag=tag*pr.first%MOD,dp[i]=sum*qpow(tag,MOD-2)%MOD;
			sum=sum*(pr.first+1)%MOD;
			while(lim[i]&&pos<lim[i]) sum=(sum-dp[pos]*tag)%MOD,pos++;
		}
		ans=ans*sum%MOD;
	}
	for(auto id:pos) ans=ans*(m+1)%MOD;
	cout<<(ans%MOD+MOD)%MOD;
	
	return 0;
}
```

---

## 作者：EuphoricStar (赞：1)

先将 $m$ 和所有 $X_i$ 加 $1$，转化为下界为 $1$ 的问题。

考虑 $q$ 条限制即要求 $\forall j \in [L_i, R_i], A_j \le X_i$ 且 $\exists j \in [L_i, R_i], A_j = X_i$。于是我们又可以得到每个位置的一个上界 $B_j = \min\limits_{L_i \le j \le R_i} X_i$。一个很重要的观察是，$B_j \le X_i$，所以取到 $X_i$ 的位置，只可能是 $B_j = X_i$ 的位置。

于是我们每次将 $B_j = X_i = k$ 的所有位置和限制单独拎出来计数，最后根据乘法原理，全部乘起来就是最终答案。现在问题变成了，有 $t$ 个位置 $1 \sim t$，对 $A_{1 \sim t}$ 计数，满足 $A_i \le m$，且给定若干条限制 $[L_j, R_j]$，需要满足 $\exists i \in [L_j, R_j], A_i = m$。

考虑设计一个类似 [Edu DP Contest W Intervals](https://www.luogu.com.cn/problem/AT_dp_w) 的 dp，$f_{i, j}$ 表示填完 $[1, i]$，离 $i$ 最近的 $j$ 使得 $A_j = m$，并且满足所有右端点在 $i$ 之前的限制的方案数。我们可以对于每个位置预处理一个 $g_i = \max\limits_{R_j = i} L_j$ 表示 dp 到 $i$ 时上一个 $A_j = m$ 的 $j$ 必须 $\ge i$。有转移：

- $\forall j \le g_i, f_{i, j} \gets f_{i - 1, j} \times (m - 1)$，表示 $A_i$ 可以填 $1 \sim m - 1$ 的所有数，不必填 $m$，因为已经满足以 $i$ 为右端点的所有区间的需求了；
- $f_{i, i} \gets \sum\limits_{j = 0}^{i - 1} f_{i - 1, j}$，表示 $A_i = m$，前面可以任意填。

直接暴力 dp 复杂度 $O(n^2)$，已经可以通过 [P4229 某位歌姬的故事](https://www.luogu.com.cn/problem/P4229)了。这个东西显然也可以线段树优化的，每次转移相当于单点修改，区间乘、区间清空、查询整体和，而区间清空又可以转化成区间乘 $0$，于是我们只需要维护支持单点修改、区间乘、查询整体和的数据结构即可，可以使用线段树。

时间复杂度 $O((n + q) \log (n + q))$。

[code](https://atcoder.jp/contests/abc262/submissions/42941995)

---

## 作者：xxxxxzy (赞：0)

题目看起来还是很典，还是不会。

容易确定每个点的上界，拿个线段树做一下区间取 $\min$ 就好。

考虑对每个上界 $x$ 做离散化后的 dp，有三种转移：

1. $dp_{i-1,j} \to dp_{i,i}$，代表第 $i$ 位选到上界。
2. $dp_{i-1,j} \times x \to dp_{i,j}$，代表第 $i$ 位任意选。
3. $dp_{i,j} := 0(j<L_i)$，代表满足区间必须要有一个 $x$ 的限制。

这个东西只需要维护全局加，全局乘，前缀赋值为 $0$，拿个指针扫一遍最大前缀外加打两个 tag 就行。

值得注意的是，对于一个限制 $(l,r,0)$，应该直接把 $a_{l \to r}$ 赋值为 $0$，不参与 dp。

---

