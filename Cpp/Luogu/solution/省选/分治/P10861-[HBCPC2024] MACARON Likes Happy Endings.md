# [HBCPC2024] MACARON Likes Happy Endings

## 题目描述

MACARON 要读一本书，这本书包含 $n$ 章，第 $i$ 章有 $a_i$ 个字符。
MACARON 想在接下来的 $k$ 天内读完这本书。
每天，他要么从未读的第一章开始读若干章，要么就休息（不读书），但他必须在 $k$ 天内完成阅读。

MACARON 享受他的阅读时间，并喜欢圆满的结局，所以他不希望在这些日子里太过悲伤。
他有一个不吉利的数字 $d$，因为他认为数字 $d$ 会导致不好的结局。
我们用一个悲伤值来量化他每天的心情。
在第 $i$ 天，如果他阅读，假设他读了从 $L_i$ 到 $R_i$ 的章节。
这一天的悲伤值是满足 $L_i\leq l\leq r\leq R_i$ 且 $\bigoplus_{i=l}^r a_i=d$ 的区间 $[l, r]$ 的数量。
这里的 $\oplus$ 表示按位异或运算符。
如果他不读书，则悲伤值为 0。

MACARON 想安排他的阅读计划，以最小化 $k$ 天内悲伤值的总和。
你能帮他找到最小值吗？

## 说明/提示

以下是一个最优的阅读计划：

- 第一天，休息，悲伤值为 0；
- 第二天，阅读第 1 章到第 3 章，悲伤值为 0；
- 第三天，阅读第 4 章到第 7 章，悲伤值为 2；
- 第四天，阅读第 8 章到第 10 章，悲伤值为 1。（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
10 4 5
1 2 3 4 5 5 6 5 4 3```

### 输出

```
3```

# 题解

## 作者：_Wind_Leaves_ShaDow_ (赞：2)

社贡快掉没了来写篇题解/kk。

### 题意

你需要把一个序列分成至多 $k$ 段，定义每一段 $[l,r]$ 的花费为其中数对 $(x,y)$ 的个数，满足 $x\le y$ 且 $\bigoplus_{i=x}^y a_i=d$。其中 $d$ 是给定的常数。

问最小花费。$n\le10^5,d,a_i\le10^6,k\le20$。

### 题解

设 $f_{i,j}$ 表示前 $i$ 个数分成 $j$ 段最小花费。转移为 $f_{i,j}=min\{f_{k-1,j-1}+w(k,i)\}$。其中 $w(k,i)$ 即为 $[k,i]$ 分为一段的花费。

观察发现这个式子很能够决策单调性优化，可以证明其 $w(k,i)$ 满足四边形不等式。如果需要的话证明在代码后面。

然后很好做了，分治每一层得到答案，这里不多赘述。

思考一下没有什么数据结构支持快速得到 $w$ 的值，于是自然而然地想到类似莫队移动指针的维护方式。移动指针的复杂度是 $O(n\log n)$ 的，证明考虑刻画指针移动路径，每一层指针只会在候选区间进行线性次数的移动，而分治一共是 $\log$ 层。

考虑令位置 $i$ 的前缀异或和为 $s_i$，则一次查询变成询问 $l\le x\le y\le r$ 且 $s_{x-1}\oplus s_y=d$ 的 $(x,y)$ 个数。这个很容易统计出来，开两个桶记录 $s_{x-1}$ 的集合和 $s_y$ 的集合。注意移动指针时的删除添加顺序。

于是做完了，一共有 $k$ 层每层做一次分治，复杂度 $O(kn\log n)$。

没有仔细想，但是感觉如果 $k$ 大一点是不是可以套上 wqs 二分做到 $O(n\log n\log V)$？

注意到 $d\le 10^6$ 不代表桶的上界是 $10^6$。

### 代码

```cpp
#include <bits/stdc++.h>
#define lint __int128
#define int long long
#define fi first 
#define se second
#define Rg register
#define Ri Rg int
#define Il inline
#define vec vector
#define pb push_back
#define IT ::iterator
#define p_que priority_queue

using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> pii;
const int N=1e5,M=(1<<20),Inf=1e18;
const db eps=1e-9,pi=acos(-1.0);

Il int read(){
    int x=0,f=1;char ch=getchar();
    for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;
    for(;'0'<=ch&&ch<='9';ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
    return x*f;
}

Il void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+48);
    return;
}

int n,m,K,a[N+5],dp[N+5][25],lp=1,rp=0,ans=0,gl[M+5],gr[M+5];

Il void adl(int p){gr[a[p]]++;ans+=gr[K^a[p-1]];gl[a[p-1]]++;return;}

Il void del(int p){ans-=gr[K^a[p-1]];gr[a[p]]--;gl[a[p-1]]--;return;}

Il void adr(int p){gl[a[p-1]]++;ans+=gl[K^a[p]];gr[a[p]]++;return;}

Il void der(int p){ans-=gl[K^a[p]];gl[a[p-1]]--;gr[a[p]]--;return;}

Il int qur(int l,int r){
	while(lp>l)adl(--lp);
	while(lp<l)del(lp++);
	while(rp<r)adr(++rp);
	while(rp>r)der(rp--);
	return ans;
}

Il void solve(int l,int r,int zl,int zr,int ly){
	int mid=(l+r)>>1,p=zl;if(l>r||zl>zr)return;
	dp[mid][ly]=Inf;
	for(Ri i=zl;i<=min(mid,zr);i++){
		int tmp=dp[i-1][ly-1]+qur(i,mid);
		if(tmp<dp[mid][ly])dp[mid][ly]=tmp,p=i;
	}
	solve(l,mid-1,zl,p,ly),solve(mid+1,r,p,zr,ly); 
	return;
}

signed main(){
    n=read(),m=read(),K=read();for(Ri i=1;i<=n;i++)a[i]=read();
    for(Ri i=1;i<=n;i++)a[i]^=a[i-1],dp[i][0]=Inf;
    for(Ri i=1;i<=m;i++)solve(1,n,1,n,i);
    ans=Inf;for(Ri i=1;i<=m;i++)ans=min(ans,dp[n][i]);
    cout<<ans;
	return 0;
}
```

### 证明满足四边形不等式

设有 $a<b<c<d$。

我们的权值函数统计的是类似一种合法点对的答案，考虑对应到坐标系中，$w(a,b)$ 统计的实际上就是以 $(a,a),(b,b)$ 为对角线的矩形中合法点对数（这里除对角线上每个点对会被算两次，但是并不影响证明）。

于是将 $w(a,d)+w(b,c),w(a,c)+w(b,d)$ 对应到坐标系，发现前者比后者多覆盖了以 $(a,c),(b,d)$ 和 $(c,a),(d,b)$ 为对角线的两个小矩形。

显然就有 $w(a,c)+w(b,d)\le w(a,d)+w(b,c)$，得证。

---

## 作者：Richard_Whr (赞：2)

状态设计很套路，$f_{j,i}$ 表示已经划分了 $j$ 段，到 $i$ 的最小代价。

转移也很简单，枚举最后一段选什么：

$$f_{j,i}=\min\limits_{k=0}^{i-1}f_{j-1,k}+w(k+1,i)$$

$w(l,r)$ 表示区间内子区间异或值为 $d$ 的数量，形式化就是：

$w(l,r)=\sum\limits_{j=l-1}^{r-1}\sum\limits_{i=j+1}^{r}[s_j \oplus s_i=d]$

先不管怎么快速求这个东西，因为能快速求也没用，这个 dp 现在是 $O(n^2m)$ 的。

考虑优化，搜索一下只有决策单调性了。

考虑证明 $w$ 函数满足四边形不等式即相交优于包含： 

$$w(a,c)+w(b,d) \le w(b,c)+w(a,d),\forall a < b < c < d$$

考虑将合法的 $(i,j),s_i \oplus s_j = d$ 点对拍到坐标系上，那么一次查询实际上是查询矩形区域内点对数量，基本等价于面积。

看回到刚刚那个不等式，发现相交的面积比包含的面积少了左下角和右上角两部分，因此一定更优，四边形不等式成立。

这下只要能快速求 $w$ 这个函数，就能通过分治决策单调性，做到 $O(n\log n)$，具体实现不再赘述，如有需要可以看 [CF833B The Bakery](https://www.luogu.com.cn/problem/CF833B)。

上面这个题还可以给你第二个启发是用类似莫队的方法维护函数增量求解。

由于每次移动指针的时候右端点固定，只移动左端点，次数与分治区间长度同阶。

分治到下一层的时候两个端点都会最多移动当前区间长度，也和分治区间长度同阶。

复杂度正确，至于具体怎么做就简单了，开个桶记录每种值出现次数即可。

总复杂度 $O(n \log n \times m)$ 可过。

用 wqs 二分是否 $m$ 可以更大？？感觉有点凸性。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10,V=2e6+10,Inf=1e12;
int f[N],g[N];
int buc[V];
int a[N],s[N];
int n,m,d;
int L=1,R=0;
int res;

inline void add(int i)
{
	res+=buc[s[i]^d];
	buc[s[i]]++;
}

inline void del(int i)
{
	buc[s[i]]--;
	res-=buc[s[i]^d];
}

inline int W(int l,int r)
{
	while(R<r) add(++R);
	while(L>l) add(--L);
	while(R>r) del(R--);
	while(L<l) del(L++);
	return res;
}

inline void solve(int l,int r,int L,int R)
{
	if(l>r || L>R) return;
	int i=l+r>>1,opt=L,minv=Inf;
	for(int j=L;j<=min(i-1,R);j++)
	{
		int v=g[j]+W(j,i);
		if(v<minv) minv=v,opt=j;
	}
	f[i]=minv;
	solve(l,i-1,L,opt),solve(i+1,r,opt,R);
}

signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	
	cin>>n>>m>>d;
	for(int i=1;i<=n;i++) cin>>a[i],s[i]=s[i-1]^a[i];
		
	memset(f,0x3f,sizeof f),f[0]=0;
	
	int res=Inf;
	for(int i=1;i<=m;i++)
	{
		memcpy(g,f,sizeof f),memset(f,0x3f,sizeof f);
		solve(1,n,0,n-1);
		res=min(res,f[n]);
	}
	
	cout<<res<<"\n";
	
	return 0; 
}
```

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/P10861)

**题目大意**

> 给定 $n,k,d$ 以及 $a_1\sim a_n$，定义一个区间 $[L,R]$ 的权值为 $a_i$ 异或和恰好为 $d$ 的子区间个数。
>
> 将 $1\sim n$ 分成 $\le k$ 段，最小化每段区间权值和。
>
> 数据范围：$n\le 10^5,k\le 20,a_i\le 10^6$。

**思路分析**

先考虑如何算一个区间的权值，可以考虑莫队，维护 $[L-1,R]$ 中每种前缀异或和出现的次数。

原问题显然考虑 dp，每次维护 $k\to k+1$ 过程的转移，显然题目中的权值函数满足四边形不等式，因此转移有决策单调性。

用分治优化 dp 过程，计算区间权值用类似莫队的方法移动指针，可以分析出每次分治时指针的移动总量是 $\mathcal O(n\log n)$ 级别的。

时间复杂度 $\mathcal O(nk\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=1e5+5,MAXV=1<<20;
int a[MAXN],X,cnt[MAXV];
ll f[MAXN],g[MAXN],w=0;
void ins(int z) { w+=cnt[z^X],++cnt[z]; }
void ers(int z) { --cnt[z],w-=cnt[z^X]; }
ll qry(int ql,int qr) {
	static int l=1,r=0;
	while(l>ql) ins(a[--l]);
	while(r<qr) ins(a[++r]);
	while(r>qr) ers(a[r--]);
	while(l<ql) ers(a[l++]);
	return w;
}
void DP(int l,int r,int L,int R) {
	if(l>r) return ;
	int x=(l+r)>>1,p=L;
	f[x]=g[p]+qry(p,x);
	for(int i=L+1;i<=R&&i<=x;++i) {
		ll v=g[i]+qry(i,x);
		if(v<f[x]) f[x]=v,p=i;
	}
	DP(l,x-1,L,p),DP(x+1,r,p,R);
}
signed main() {
	int n,k;
	scanf("%d%d%d",&n,&k,&X);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]),a[i]^=a[i-1];
	memset(f,0x3f,sizeof(f)),f[0]=0;
	for(int o=1;o<=k;++o) {
		memcpy(g,f,sizeof(g));
		memset(f,0x3f,sizeof(f));
		DP(0,n,0,n);
	}
	printf("%lld\n",f[n]);
	return 0;
}
```

---

## 作者：Diaоsi (赞：1)

[MACARON Likes Happy Endings](https://www.luogu.com.cn/problem/P10861)

首先能写出一个暴力的 DP，设 $f_{i,j}$ 表示前 $i$ 个位置分了 $j$ 段所需要的最小代价，有转移：

$$
f_{i,j}\leftarrow\min_{p=0}^{i-1}\left\{f_{p,j-1}+w(p+1,i)\right\}
$$

$w(l,r)$ 表示区间 $[l,r]$ 内有多少个子区间满足其所有元素的异或和为 $d$。

通常这类 DP 都考虑利用决策单调性进行优化，关键在于证明：

$$
w(l,r)+w(l+1,r+1)\leq w(l+1,r)+w(l,r+1)
$$

注意到等式右边会多考虑子区间 $[l,r+1]$，而其余的子区间都与左边一一对应，所以右边的值一定不小于左边。$\ \Box$

所以这个 DP 方程具有决策单调性。具体地说，固定 $k$ ，设 $f_{i,k}$ 由 $f_{p_i,k-1}$ 转移而来，则 $p_i$ 单调不降。

考虑整体二分，设 $solve(k,l,r,L,R)$ 表示当前进行 $f_{k-1}\rightarrow f_k$ 的转移，已知 $f_{[l,r],k}$ 的决策点在 $[L,R]$ 内，对 $f_{[l,r],k}$ 进行求解的函数。

设 $mid=\dfrac{l+r}{2}$，考虑暴力求出 $f_{mid,k}$ 的答案，$w$ 函数用类似于莫队的指针移动进行增量维护，时间复杂度 $\mathcal{O}(R-L+1)$，得到决策点 $p$。


由决策单调性可知，$f_{[l,mid],k}$ 的决策点一定在 $[L,p]$ 中，另一半同理。于是整个问题被划分成两个子问题 $solve(k,l,mid,L,p)$ 和 $solve(k,mid+1,r,p,R)$。

由于分治最多有 $\mathcal{O}(\log n)$ 层，而每层指针移动次数是均摊 $\mathcal{O}(n)$ 的，所以单次分治的时间复杂度为 $\mathcal{O}(n\log n)$。

转移总共有 $k$ 层，故总时间复杂度为 $\mathcal{O}(nk\log n)$。


```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=100010,M=2000010;
const ll INF=0x3f3f3f3f3f3f3f3f;
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
inline void swap(int &x,int &y){x^=y^=x^=y;}
int n,k,d,ql=1,qr,s[N],t[M]={1};
ll res,f[N][21];
ll calc(int tl,int tr){
	while(ql<tl)--t[s[ql-1]],res-=t[s[ql-1]^d],ql++;
	while(qr>tr)--t[s[qr]],res-=t[s[qr]^d],qr--;
	while(ql>tl)--ql,res+=t[s[ql-1]^d],++t[s[ql-1]];
	while(qr<tr)++qr,res+=t[s[qr]^d],++t[s[qr]];
	return res;
}
void solve(int x,int l,int r,int ls,int rs){
	int mid=(l+r)>>1,p=rs;f[mid][x]=INF;
	for(int i=max(1,ls);i<=min(mid,rs);i++){
		ll val=f[i-1][x-1]+calc(i,mid);
		if(val<f[mid][x])f[mid][x]=val,p=i;
	}
	if(l>=r)return;
	solve(x,l,mid,ls,p);
	solve(x,mid+1,r,p,rs);
}
int main(){
	scanf("%d%d%d",&n,&k,&d);
	for(int i=1;i<=n;i++){
		scanf("%d",&s[i]);
		s[i]^=s[i-1];
		f[i][0]=INF;
	}
	for(int i=1;i<=k;i++)solve(i,1,n,1,n);
	printf("%lld\n",f[n][k]);
	return 0;
}
```

---

## 作者：_Ch1F4N_ (赞：0)

首先存在一个显然的 $O(n^2 k)$ 做法，不妨 $dp_{i,j}$ 表示考虑 $[1,i]$ 划分为 $j$ 段的最小代价，转移就是 $dp_{i,j} = \max(dp_{k,j-1}+w(k+1,i))$，其中 $w(i,j)$ 表示 $[i,j]$ 内异或和为 $d$ 的区间数，由于这是一个矩形内合法点对的形式，满足四边形不等式，故 $dp$ 数组存在决策单调性，考虑分治优化，转移过程用类似莫队的双指针维护 $w$ 的值即可做到 $O(n \times k \log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int inf = 1e18;
const int maxn = (1<<20);
int n,k;
int a[maxn];
int pre[maxn];
int Lcnt[maxn],Rcnt[maxn];
int lt,rt;
int w;
int d;
int dp[maxn],g[maxn];
void solve(int l,int r,int L,int R){
    if(l>r) return ;
    int mid=(l+r)>>1;
    int p=L;
    int minv=inf;
    while(lt>L){
        lt--;
        Lcnt[pre[lt-1]]++;
        Rcnt[pre[lt]]++;        
        w+=Rcnt[pre[lt-1]^d];
    }
    while(rt<mid){
        rt++;
        Rcnt[pre[rt]]++;
        Lcnt[pre[rt-1]]++;        
        w+=Lcnt[pre[rt]^d];
    }
    while(lt<L){
        w-=Rcnt[pre[lt-1]^d];
        Lcnt[pre[lt-1]]--;
        Rcnt[pre[lt]]--;
        lt++;
    }    
    while(rt>mid){
        w-=Lcnt[pre[rt]^d];
        Rcnt[pre[rt]]--;
        Lcnt[pre[rt-1]]--;
        rt--;
    }
    for(int i=L;i<=min(mid,R);i++){
        while(lt<i){
            w-=Rcnt[pre[lt-1]^d];
            Lcnt[pre[lt-1]]--;
            Rcnt[pre[lt]]--;
            lt++;
        }
        if(dp[i-1]+w<minv){
            minv=dp[i-1]+w;
            p=i;
        }
    }
    g[mid]=minv;
    solve(l,mid-1,L,p);
    solve(mid+1,r,p,R);
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>k>>d;
    for(int i=1;i<=n;i++) cin>>a[i],pre[i]=pre[i-1]^a[i];
    for(int i=1;i<=n;i++) dp[i]=inf;
    for(int i=1;i<=k;i++){
        memset(Lcnt,0,sizeof(Lcnt));
        memset(Rcnt,0,sizeof(Rcnt));
        w=0;
        lt=1,rt=0;
        solve(1,n,1,n);
        for(int j=1;j<=n;j++) dp[j]=g[j]; 
    }
    cout<<dp[n]<<'\n';
    return 0;
}
```

---

