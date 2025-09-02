# New Year Shopping

## 题目描述

有 $n$ 种商品，第 $i$ 种商品的价格是 $c_i$ ，购买后可以增加 $h_i$ 的快乐指数，将于第 $t_i$ 天上市。商品的保质期为 $p$ 天，过期后不能再购买，即第 $i$ 种商品只能在第 $t_i$ 天到第 $t_i+p-1$ 天之间购买，每种商品只能购买一次。

有 $q$ 个询问，每次给定两个整数 $a,b$ ，求在第 $a$ 天去购物，最多使用 $b$ 元的情况下可以得到的最大快乐指数。询问之间互不干扰。

## 说明/提示

$1\le n\le 4\times 10^3, 1\le p \le 10^4$

$1\le c_i,h_i \le 4\times 10^3, 1\le t_i \le 10^4$

$1\le q \le 2\times 10^4,1\le a \le 2\times 10^4, 1\le b \le 4\times 10^3$

## 样例 #1

### 输入

```
4 4
2 3 2
3 5 1
4 7 2
11 15 5
4
1 3
2 5
2 6
5 14
```

### 输出

```
5
8
10
18
```

## 样例 #2

### 输入

```
5 4
3 2 1
7 4 4
2 1 2
6 3 5
3 2 2
10
1 5
2 5
4 8
4 9
4 10
5 8
5 9
5 10
8 4
7 9
```

### 输出

```
2
3
5
5
6
4
5
6
0
4
```

# 题解

## 作者：foreverlasting (赞：13)

[题解同步发表在我的博客里哦](https://foreverlasting1202.github.io/)

动态规划。

神题。如果直接$DP$的话我们必须要每次重新做背包，这样显然复杂度升天。我们考虑这个询问能表示成什么。

由于每个物品在架上的时间长度是一样的，所以每次询问的区间就是$[a_i-p,a_i]$，即上架时间在这段区间内的所有物品。

这样就有点办法了。我们将整个时间轴（长度$L=20000$）平均分成$\frac {L}{p}$份，每份长度为$p$。我们令这样平均分的区间的端点称为关键点，这样的话每次询问必然能包含一个关键点。

于是我们以每个关键点为中心，分别向两边做长度为$p$的$01$背包。

这里的复杂度是$O(\frac {L}{p}\ast p\ast b_i)=O(L\ast b_i)$。

那么每次询问，以通过的关键点为中心，我们只要枚举分配给左边区间的金钱数量和右边区间的金钱数量，然后合并一下就可以了。

code:
```cpp
//2019.2.20 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define eps 1e-10
inline int read() {
    res s=0;
    bool w=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') {
        if(ch=='-')w=1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return w?-s:s;
}
inline void _swap(res &x,res &y) {
    x^=y^=x^=y;
}
inline int _abs(const res &x) {
    return x>0?x:-x;
}
inline int _max(const res &x,const res &y) {
    return x>y?x:y;
}
inline int _min(const res &x,const res &y) {
    return x<y?x:y;
}
const int N=4e3;
const int M=2e4;
namespace MAIN {
    int n,p;
    typedef pair<int,int> Pair;
#define mp make_pair
#define fi first
#define se second
    vector<Pair> T[M+10];
#define pb push_back
    struct P{
        int dp[N+10];
    }a[N*2+10];
    int cnt;
    int L[M+10],R[M+10];
    inline void operator +=(P &a,const Pair &x){
        for(res i=N;i>=x.fi;i--)a.dp[i]=_max(a.dp[i],a.dp[i-x.fi]+x.se);
    }
    inline void MAIN(){
        n=read(),p=read();
        for(res i=1;i<=n;i++){
            res c=read(),h=read(),t=read();
            T[t].pb(mp(c,h));
        }
        for(res i=1;i<=M;i+=p){
            for(res j=0;j<p&&i+j<=M;j++){
                if(j)R[i+j]=R[i+j-1];
                if(T[i+j].size()){
                    a[++cnt]=a[R[i+j]],R[i+j]=cnt;
                    for(res k=0,sz=T[i+j].size();k<sz;k++)a[cnt]+=T[i+j][k];
                }
            }
            for(res j=1;j<p&&i-j>0;j++){
                if(j>1)L[i-j]=L[i-j+1];
                if(T[i-j].size()){
                    a[++cnt]=a[L[i-j]],L[i-j]=cnt;
                    for(res k=0,sz=T[i-j].size();k<sz;k++)a[cnt]+=T[i-j][k];
                }
            }
        }
        res Q=read();
        while(Q--){
            res A=read(),B=read(),ans=0;
            for(res i=0;i<=B;i++)ans=_max(ans,a[A-p+1>0?L[A-p+1]:0].dp[i]+a[R[A]].dp[B-i]);
            printf("%d\n",ans);
        }
    }
}
int main() {
    MAIN::MAIN();
    return 0;
}
```

---

## 作者：EnofTaiPeople (赞：8)

将物品和查询看作01背包的正常操作，发现物品只在一段区间上出现，容易联想到线段树分治。

即对于每一个物品在区间上查询，线段树上每一个节点保存这些物品，向下深搜时扫过去，将节点的每一个物品加进来，保存每个节点的状态，就很方便撤销了。

时间复杂度：$O(nb\log_2t)$

核心代码：
```cpp
void build(int x=1,int l=1,int r=B,int dep=1){
    int md=l+r>>1,a=x<<1;d[x]=dep;
    if(l<r)build(a,l,md,dep+1),build(a|1,md+1,r,dep+1);
}
pr at;
void ins(int L,int R,int x=1,int l=1,int r=B){
    if(l>=L&&r<=R){th[x].push_back(at);return;}
    int md=l+r>>1,a=x<<1;
    if(L<=md)ins(L,R,a,l,md);
    if(md<R)ins(L,R,a|1,md+1,r);
}
void sol(int x=1,int l=1,int r=B){
    // cerr<<"start:"<<d[x]<<endl;
    memcpy(f[d[x]],f[d[x]-1],sizeof(f[d[x]]));
    for(auto p:th[x]){
        for(int i=C;i>=p.first;--i)
            f[d[x]][i]=max(f[d[x]][i],f[d[x]][i-p.first]+p.second);
    }
    if(l<r){
        int md=l+r>>1,a=x<<1;
        sol(a,l,md),sol(a|1,md+1,r);
    }else{
        for(int i=1;i<=C;++i)f[d[x]][i]=max(f[d[x]][i],f[d[x]][i-1]);
        // cerr<<"RT"<<endl;
        for(auto p:nd[l])ans[p.second]=f[d[x]][p.first];
    }
}
int main(){
    read(n,p),build();
    int i,x,y,z;
    for(i=1;i<=n;++i){
        read(x,y,z);at=pr(x,y);
        ins(z,min(z+p-1,B));
    }read(m);
    for(i=1;i<=m;++i)
        read(x,y),nd[x].push_back(pr(y,i));
    for(i=1,sol();i<=m;++i)
        printf("%d\n",ans[i]);
    return 0;
}//test for luogu
```

---

## 作者：xgzc (赞：3)

给个不要脑子的做法。

因为这道题是物品会存在一段时间，对每个时间点求出 $0/1$ 背包的值。然后 $n$ 和背包大小都是 $4000$ 级别，于是考虑线段树分治。

也就是将所有物品丢到线段树上去，dfs 一遍整棵树，将覆盖当前区间的所有物品全部加到 $0/1$ 背包里面去，这样就可以在任意时间点得到 $0/1$ 背包的 dp 数组，回溯的时候撤销当前操作即可。

时间复杂度 $\mathcal O(n^2 \log p)$。

代码见我的 [$\texttt{blog}$](https://www.cnblogs.com/cj-xxz/p/12763336.html)

---

## 作者：ppp204 (赞：2)

可能不是很详细，勿喷！

> 做法: DP+分块思想/双栈

这道题是一个很经典的**可删除**背包问题(区间背包)

这道题可以用双栈写，但是我不会……

%了~~烤面筋~~CalVinJin大爷的分块……

首先我们普通的区间背包肯定是每次清空整个背包，然后DP，这样做显然不能拿到高分。

然后我们可以思考一下，可不可以将每k个时间做为一块，进行分块？

我们考虑这个点向右p个时间所能包含到的所有信息，然后做背包dp(搞前缀与后缀)。

接着对于每次询问，找能够影响到这次询问的最早时间与最晚时间

如果他们所处于同一块内的话，此时要与x所在的块进行比较。如果两者在同一个块内，说明右端点所处时间$\le$x,直接拿右端点的前缀背包去计算即可，否则就用左端点的后缀背包

因为三者在同一个k块内情况下，我们如果用了左端点的前缀背包，我们可能会**导致在x后面的信息也被算入**，而如果三者不在同一块内，我们选择右端点的后前缀背包可能会把左端点前面的信息也算入。

再看左右端点不在同一块内的方案，因为我找的左端点是lower\_bound a-k+1,右端点是upper\_bound a -1,所以这两个块肯定是**连在一起的**，因此我们直接分开空间进行DP即可。

#### Code:

```cpp
#include<bits/stdc++.h>
#define re register
#define rep(i,a,b) for(re int i=a,i##end=b; i<=i##end; i++)
#define drep(i,a,b) for(re int i=a,i##end=b; i>=i##end; i--)
#define repp(i,a,b) for(re int i=a,i##end=b; i<i##end; i++)
#define drepp(i,a,b) for(re int i=a,i##end=b; i>i##end; i--)
#define Erep(i,x) for(int i=head[x]; i; i=Edge[i].nxt)
#define lowbit(x) (x&-x)
#define debug(x) cerr<<#x<<" = "<<x<<endl
#define coint const int 
#define ms(x,a) memset(x,a,sizeof x)
#define PII pair<int,int>
#define fi first
#define se second
#define CM cerr<<(&S2-&S1)/1024./1024.<<"MB"<<endl
typedef long long ll;
using namespace std;
template<class T>inline T rd(){
    static bool neg;static char ch;static T x;
    for(neg=0,ch=0; ch>'9'||ch<'0'; neg|=(ch=='-'),ch=getchar());
    for(x=0; ch>='0'&&ch<='9'; x=(x<<1)+(x<<3)+(ch^'0'),ch=getchar());
    return neg?-x:x;
}
template<class T>inline T Max(const T &x, const T &y) { return x>y?x:y; }
template<class T>inline T Min(const T &x, const T &y) { return x<y?x:y; }
 
bool S1;
coint N=4000+5,MX1=4000+5;
 
int n,q,p;
int B[N];
 
struct student{
    int c,h,t;
    inline void read() { c=rd<int>(),h=rd<int>(),t=rd<int>(); return; }
}A[N];
 
inline bool cmp1(const student &x, const student &y) { return x.t<y.t; }
 
struct DP{
    int sum[MX1];
    void Union(const student &stu){
        drep(i,MX1-5,stu.c) sum[i]=Max(sum[i],sum[i-stu.c]+stu.h);
        return;
    }
}dp1[N],dp2[N];
 
bool S2;
 
int main(){
//  CM;
//  freopen("yummyin","r",stdin);
//  freopen("yummy.out","w",stdout);
    n=rd<int>(); p=rd<int>();
    rep(i,1,n) A[i].read();
    sort(A+1,A+n+1,cmp1);
    rep(i,1,n) B[i]=A[i].t;//,printf("%d%c",B[i]," \n"[i==n]);
    int st=0,ed=1;
    rep(block,1,1e9){
        if(block*p-1<A[ed].t) continue;
        st=ed;
        while(ed<n && A[ed+1].t<=block*p-1) ed++;
        rep(i,st,ed){
            if(i>st) dp1[i]=dp1[i-1];
            dp1[i].Union(A[i]);
        }
        drep(i,ed,st){
            if(i<ed) dp2[i]=dp2[i+1];
            dp2[i].Union(A[i]);
        }
        ed++;
        if(ed>n) break;
    }
    int q=rd<int>();
    rep(i,1,q){
        int a=rd<int>(),b=rd<int>();
        int lft=lower_bound(B+1,B+n+1,a-p+1)-B,rgt=upper_bound(B+1,B+n+1,a)-B-1;
        if(lft>rgt) { printf("0\n"); continue; }
        int Lft=A[lft].t/p,Rgt=A[rgt].t/p,now=a/p;
        if(Lft==Rgt){ //同一块内
            if(Lft==now) printf("%d\n",dp1[rgt].sum[b]);
            else printf("%d\n",dp2[lft].sum[b]);
        }else{ //不同块内
            int ans=0;
            rep(cost,0,b) ans=Max(ans,dp2[lft].sum[cost]+dp1[rgt].sum[b-cost]);
            printf("%d\n",ans);
        }
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：1)

### 题目传送门

[洛谷](https://www.luogu.com.cn/problem/CF500F)

[CF](https://codeforces.com/problemset/problem/500/F)

### 分析

这题的框架是一个 $0/1$ 背包，但每个物品都有一段存在时间。

我们可以以时间为轴，进行线段树分治。

我们把每个物品的存在时间存到线段树上，把询问存到线段树的叶子节点上，然后把线段树 dfs 一遍，每到一个节点进行一下 $0/1$ 背包 DP，到叶子结点时回答所有询问。

时间复杂度：$O(T \log T \times m)$，其中 $T$ 是最大时间。

### 代码：

```cpp
// LUOGU_RID: 103987670
#include <bits/stdc++.h>
using namespace std;
template<typename T>inline void read(register T &x)
{
	register T p = 1,num = 0;
	char c = getchar();
	while(c < '0'||c > '9')
	{
		if(c == '-') p = -p;
		c = getchar();
	}
	while('0' <= c&&c <= '9')
	{
		num = (num<<3)+(num<<1)+(c^48);
		c = getchar();
	}
	x = p * num;
}
template<typename T>inline void write(register T x)
{
	if(x < 0) putchar('-'),x = -x;
	if(x > 9) write(x/10);
	putchar(x%10+48);
}
#define D(i,a,b) for(register int i=a;i>=b;--i)
#define F(i,a,b) for(register int i=a;i<=b;++i)
#define ll long long
#define pii pair<int,int>
#define N 20010
#define M 4010
int ans[N],dp[20][M];
vector<pii> s[N];
struct Seg
{
	#define mid (l+r)/2
	#define ls u<<1
	#define rs u<<1|1
	vector<pii> g[N<<2];
	void update(int u,int l,int r,int x,int y,pii t)
	{
		if(x <= l&&r <= y) 
		{
			g[u].push_back(t);
			return;	
		}	
		if(x <= mid) update(ls,l,mid,x,y,t);
		if(y > mid) update(rs,mid+1,r,x,y,t);
	}	
	void solve(int u,int l,int r,int dep)
	{
		memcpy(dp[dep],dp[dep-1],sizeof(dp[dep]));
		for(auto p:g[u])
			D(i,4000,p.first)
				dp[dep][i] = max(dp[dep][i],dp[dep][i-p.first]+p.second);	
		if(l == r) 
		{
			for(auto p:s[l]) ans[p.first] = dp[dep][p.second];
			return;
		}
		solve(ls,l,mid,dep+1);
		solve(rs,mid+1,r,dep+1);
	}
}tree;
int n,p,q;
int main()
{
	read(n),read(p);
	while(n--)
	{
		int c,h,t;
		read(c),read(h),read(t);
		tree.update(1,1,20000,t,t+p-1,(pii){c,h});		
	}
	read(q);
	F(i,1,q)
	{
		int x,m;
		read(x),read(m);
		s[x].push_back((pii){i,m});
	}
	tree.solve(1,1,20000,1);
	F(i,1,q) write(ans[i]),putchar('\n');
	return 0;
}
```

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

不难发现，这是一个 01DP 问题，但是可以认为带修。而且问题的 DP 式子中含有 $\max$，不可减。

但是我们注意到每一个商品的影响都只在一段时间内出现，这启示我们思考线段树分治。每一个区间继承上一个区间的答案，只增不减。

事实上，这样做的时间复杂度是 $O(Bn\log T)$ 的。其中 $B$ 是 $b$ 的最大值 $4000$，$T$ 是涉及到的时间的最大值，偷点懒的话是 $2\times10^4$。时间复杂度没有炸。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
struct IO {
#define mxsz (1 << 21)
	char buf[mxsz], * p1, * p2;
	char pbuf[mxsz], * pp;
	IO() : p1(buf), p2(buf), pp(pbuf) {}
	~IO() { fwrite(pbuf, 1, pp - pbuf, stdout); }
	inline char gc() {
		if (p1 == p2) p2 = (p1 = buf) + fread(buf, 1, mxsz, stdin);
		return p1 == p2 ? ' ' : *p1++;
	}
#ifndef sipt
	inline int read() {
		int r = 0; char c = gc(); while (c < '0' || c>'9') c = gc();
		while (c >= '0' && c <= '9') r = r * 10 + (c ^ 48), c = gc();
		return r;
	}
#else
	inline int read() {
		int r = 0; char c = gc(); bool rev = 0;
		while (c < '0' || c>'9') rev |= (c == '-'), c = gc();
		while (c >= '0' && c <= '9') r = r * 10 + (c ^ 48), c = gc();
		return rev ? ~r + 1 : r;
	}
#endif
	inline void push(const char& c) {
		if (pp - pbuf == mxsz) fwrite(pbuf, 1, mxsz, stdout), pp = pbuf;
		*pp++ = c;
	}
	inline void write(int x) {
		static char sta[22]; int top = 0;
		do sta[top++] = x % 10, x /= 10; while (x);
		while (top) push(sta[--top] ^ 48);
	}
	inline void write(int x, char opc) {
#ifdef sopt
		if (x < 0) push('-'), x = ~x + 1;
#endif
		write(x), push(opc);
	}
} io;
int ans[20005], dp[18][4005], n, m, k;
struct oper {
	int l, r;
	oper(int l = 0, int r = 0) :l(l), r(r) {}
}; vector<oper> q[20005];
struct seg_tree{
	struct node { int l, r; vector<oper>op; }re[20005 << 2];
	inline void build(int l, int r, int p) {
		re[p].l = l; re[p].r = r;
		if (l == r) return;
		build((l + r >> 1) + 1, r, p << 1 | 1);
		build(l, (l + r >> 1), p << 1);
	}
	inline void ins(int cl, int cr, oper cv, int p) {
		if (cl <= re[p].l && re[p].r <= cr) 
			return void(re[p].op.emplace_back(cv));
		if (cl <= re[p << 1].r) ins(cl, cr, cv, p << 1);
		if (cr > re[p << 1].r) ins(cl, cr, cv, p << 1 | 1);
	}
	inline void dfs(int p, int d){
		memcpy(dp[d], dp[d - 1], sizeof dp[d]);
		for (const oper& p : re[p].op)
			for (int i = 4000; i >= p.l; --i)
			dp[d][i] = max(dp[d][i], dp[d][i - p.l] + p.r);
		if (re[p].l == re[p].r)
			for (const oper& p : q[re[p].l]) ans[p.l] = dp[d][p.r];
		else dfs(p << 1, d + 1), dfs(p << 1 | 1, d + 1);
	}
}sgt;
signed main(){
	ios::sync_with_stdio(0);
	n = io.read(); m = io.read();
	sgt.build(1, 2e4, 1);
	for (int i = 1, v, l, r; i <= n; ++i)
		v = io.read(), l = io.read(), r = io.read(),
		sgt.ins(r, r + m - 1, oper(v, l), 1);
	k = io.read();
	for (int i = 1, p, v; i <= k; ++i)
		p = io.read(), v = io.read(),
		q[p].emplace_back(i, v);
	sgt.dfs(1, 1);
	for (int i = 1; i <= k; ++i) io.write(ans[i], '\n');
}
```

---

## 作者：Jsxts_ (赞：0)

区间背包，猫树分治板题。

考虑离线后将每个询问 $[ql,qr]$ 存到猫树对应的区间上（即最大的满足 $ql,qr$ 在 $mid$ 两侧的区间），然后进行分治，对于右侧处理出每个前缀的背包数组，然后向左扫得到另一个背包，将得到的两个背包进行合并即可。注意合并时是枚举其中一边取 $i$ 个，另一边取 $\le b-i$ 个，所以要对之前的背包数组取前缀 $\max$。

$l=r$ 的时候要特殊处理一下。

时间复杂度 $O((n+q+t)v\log t)$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 4e3;
const int M = 2e4;
const int T = 1e4;
const int inf = 1e9;
const ll INF = 1e18;
int read() {
	int s = 0,f = 1;char ch = getchar();
	while (!isdigit(ch)) f = ch == '-'? -1 : 1, ch = getchar();
	while(isdigit(ch)) s = s * 10 + ch - '0', ch = getchar();
	return s * f;
}
int n,p,q;
vector<pair<int,int> > vc[M + 10];
struct node {
	int id,w,l,r;
};
vector<node> qu[M + 10],qu2[M + 10];
int find(int l,int r,int ql,int qr) {
	if (l == r) return l;
	int mid = l + r >> 1;
	if (ql <= mid && mid < qr) return mid;
	else if (ql > mid) return find(mid + 1,r,ql,qr);
	else return find(l,mid,ql,qr);
}
int cmp(node x,node y) {
	return x.l > y.l;
}
int ans[M + 10],f[T + 10][N + 10],g[N + 10];
void solve(int l,int r) {
	if (l == r) return;
	int mid = l + r >> 1;
	solve(l,mid), solve(mid + 1,r);
	if (!qu[mid].size()) return;
	for (int i = mid + 1;i <= r;i ++ ) {
		for (int j = 0;j <= N;j ++ ) f[i - mid][j] = f[i - mid - 1][j];
		for (auto v : vc[i])
			for (int j = N;j >= v.second;j -- )
				f[i - mid][j] = max(f[i - mid][j],f[i - mid][j - v.second] + v.first);
	}
	for (int i = mid + 1;i <= r;i ++ ) 
		for (int j = 1;j <= N;j ++ ) f[i - mid][j] = max(f[i - mid][j - 1],f[i - mid][j]);
	sort(qu[mid].begin(),qu[mid].end(),cmp);
	int p = 0;
	memset(g,-0x3f,sizeof g);
	g[0] = 0;
	for (int i = mid;i >= l;i -- ) {
		for (auto v : vc[i])
			for (int j = N;j >= v.second;j -- )
				g[j] = max(g[j],g[j - v.second] + v.first);
		for (;p < qu[mid].size() && qu[mid][p].l == i;p ++ ) {
			node t = qu[mid][p];
			for (int j = 0;j <= t.w;j ++ )
				ans[t.id] = max(ans[t.id],g[j] + f[t.r - mid][t.w - j]);
		}
	}
}
int main() {
	n = read(), p = read();
	for (int i = 1;i <= n;i ++ ) {
		int c = read(),h = read(),t = read();
		vc[t].push_back({h,c});
	}
	q = read();
	for (int i = 1;i <= q;i ++ ) {
		int a = read(),b = read();
		if (max(a - p + 1,1) == min(a,T)) {
			qu2[min(a,T)].push_back({i,b,0,0});
			continue;
		}
		if (max(a - p + 1,1) > min(a,T)) continue;
		qu[find(1,T,max(a - p + 1,1),min(a,T))].push_back({i,b,max(a - p + 1,1),min(a,T)});
	}
	memset(f[0],-0x3f,sizeof f[0]);
	f[0][0] = 0;
	solve(1,T);
	for (int i = 1;i <= T;i ++ ) {
		memset(g,-0x3f,sizeof g);
		g[0] = 0;
		for (auto v : vc[i])
			for (int j = N;j >= v.second;j -- )
				g[j] = max(g[j],g[j - v.second] + v.first);
		for (auto v : qu2[i])
			for(int j = 0;j <= v.w;j ++ ) ans[v.id] = max(ans[v.id],g[j]);
	}
	for (int i = 1;i <= q;i ++ ) printf("%d\n",ans[i]);
	return 0;
}
```


---

