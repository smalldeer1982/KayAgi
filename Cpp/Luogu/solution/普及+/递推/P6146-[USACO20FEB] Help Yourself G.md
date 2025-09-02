# [USACO20FEB] Help Yourself G

## 题目描述

在一个数轴上有 $N$ 条线段，第 $i$ 条线段覆盖了从 $l_i$ 到 $r_i$ 的所有实数（包含 $l_i$ 和 $r_i$）。

定义若干条线段的**并**为一个包含了所有被至少一个线段覆盖的点的集合。

定义若干条线段的**复杂度**为这些线段的并形成的连通块的数目。

现在 Bessie 想要求出给定 $N$ 条线段的所有子集（共有 $2^N$ 个）的复杂度之和对 $10^9+7$ 取模的结果。

你也许猜到了，你需要帮 Bessie 解决这个问题。但不幸的是，你猜错了！在这道题中你就是 Bessie，而且没有人来帮助你。一切就靠你自己了！

## 说明/提示

### 样例解释

所有非空子集的复杂度如下所示（显然空集的复杂度为零）：
$$
\{[1,6]\} \implies 1, \{[2,3]\} \implies 1, \{[4,5]\} \implies 1
$$

$$
\{[1,6],[2,3]\} \implies 1, \{[1,6],[4,5]\} \implies 1, \{[2,3],[4,5]\} \implies 2
$$

$$
\{[1,6],[2,3],[4,5]\} \implies 1
$$

故答案为 $1+1+1+1+1+2+1=8$。

### 子任务

- 测试点 $2 \sim 3$ 满足 $N \leq 16$；
- 测试点 $4 \sim 7$ 满足 $N \leq 1000$；
- 测试点 $8 \sim 12$ 没有特殊限制。

## 样例 #1

### 输入

```
3
1 6
2 3
4 5```

### 输出

```
8```

# 题解

## 作者：StudyingFather (赞：48)

先将所有线段按左端点升序排序。

设 $f_i$ 表示前 $i$ 条线段的所有子集的复杂度之和。

如果我们新添加了一条线段，复杂度会怎样变化呢？

1. 不选这条线段。

这种情况下，复杂度没有变化，不包含这条线段的子集的复杂度仍然为 $f_i$。

2. 选这条线段。

复杂度分两部分：原来的复杂度（这部分不会因为新选一条线段而减少，因为线段已经按左端点排好顺序了）和新增加的复杂度（这条线段可能不与已有线段形成连通块）。

原来的复杂度仍然为 $f_i$，而选这条线段可能会让部分子集的复杂度 +1。

如果之前的线段中有 $x$ 条线段不与当前线段相交，则选这 $x$ 条线段的一个子集加上当前线段可以让复杂度在原来子集的复杂度基础上 +1。

根据集合的知识，新增加的复杂度就是 $2^x$。

从而得到递推式：$f_i=f_{i-1}+(f_{i-1}+2^x)=2f_{i-1}+2^x$。

现在的问题就是计算 $x$。

容易看出，设第 $i$ 条线段的左端点为 $l_i$，右端点为 $r_i$，则 $x$ 等于右端点小于 $l_i$ 的线段数量。

我们可以利用前缀和技巧来预处理所有 $x$ 的值。

```cpp
#include <iostream>
#include <algorithm>
#define MOD 1000000007
using namespace std;
struct seg
{
 int l,r;
}a[100005];
int s[200005];
long long f[100005];
bool cmp(const seg&a,const seg&b)
{
 return a.l<b.l;
}
long long fpow(long long x,long long y)
{
 long long ans=1;
 while(y)
 {
  if(y&1)ans=ans*x%MOD;
  x=x*x%MOD;
  y>>=1;
 }
 return ans;
}
int main()
{
 int n;
 cin>>n;
 for(int i=1;i<=n;i++)
 {
  cin>>a[i].l>>a[i].r;
  s[a[i].r]++;
 }
 sort(a+1,a+n+1,cmp);
 for(int i=1;i<=2*n;i++)
  s[i]+=s[i-1];
 for(int i=1;i<=n;i++)
  f[i]=(2*f[i-1]+fpow(2,s[a[i].l-1]))%MOD;
 cout<<f[n]<<endl;
 return 0;
}
```

---

## 作者：LTb_ (赞：12)

[更好的阅读](https://lycltb.github.io/post/solution-usaco-2020feb-gold-help-yourself/)
### 先放结论

首先把线段按左端点升序排序

我们设$sum_i$为坐标小于等于i的**右端点**个数

$dp_i$为考虑到第$i$条线段时的答案

则递推式为$dp_i=2dp_{i-1}+2^{sum_{l_i-1}}$

答案为$dp_n$

### 证明？

当我们从$dp_{i-1}$转移到$dp_i$的时候，新增了一条线段$i$，我们可以选或不选它，这样总复杂度$\times2$。

不选线段$i$的那部分没什么好说的，那我们考虑选了线段$i$之后发生的变化。

由“不与线段$i$相交的线段且编号小于$i$的线段”组成的子集在加上线段$i$之后复杂度+1

这样的子集一共有$2^{\text{不与线段i相交的线段且编号小于i的线段的个数}}$个。（这样其实包括了单独选一个线段$i$在内了）

我们发现“不与线段$i$相交的线段且编号小于$i$的线段的个数”其实就是$sum_{l_i-1}$（$l_i$是线段$i$的左端点坐标）。

感性理解一下就是有$sum_{l_i-1}$条线段在坐标$l_i-1$之前结束了。

### 代码

更没什么好说的了

```cpp
#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;
#define int long long
const int MAXN=200005;
const int MOD=1e9+7;
int n;
pair<int,int> a[MAXN];
int l[MAXN],r[MAXN];
int tmp[MAXN];
int sum[MAXN];
int dp[MAXN];

inline int pow(int x,int y){
	int ans=1;
	while (y>0){
		if (y%2==0){
			x*=x;
			x%=MOD;
			y/=2;
		}
		ans*=x;
		ans%=MOD;
		y--;
	}
	return ans;
}

signed main()

{
	freopen("help.in","r",stdin);
	freopen("help.out","w",stdout);
	cin>>n;
	for (int i=1;i<=n;i++)
		cin>>a[i].first>>a[i].second;

	sort(a+1,a+1+n);

	for (int i=1;i<=n;i++){
		l[i]=a[i].first;
		r[i]=a[i].second;
		tmp[r[i]]++;
	}

	for (int i=1;i<=MAXN-5;i++)
		sum[i]=sum[i-1]+tmp[i];

	for (int i=1;i<=n;i++)
		dp[i]=(dp[i-1]*2ll+pow(2ll,sum[l[i]-1]))%MOD;
	
	cout<<dp[n]<<endl;
	return 0;
}
```



---

## 作者：Tarsal (赞：7)

最开始看到这题是有点懵的。

后面突然发现好像确实是个sb题。

数据范围 $10^5$ 我们显然不可能去枚举子集。

那么这个时候就要用经典套路了。

直接考虑每条线段可以产生什么贡献。

然后你发现每条线段对子集的贡献是一定的。

那么就你需要确定一个顺序，然后依次加线段，算贡献就行了。

那么，这个顺序应该怎么定?

按左端点排序即可。

接下来我们每条线段加进去后只考虑和前面的区间产生的贡献。

再考虑新加一条线段的贡献是什么。

- 不选这条线段

那么这样的贡献就为 $0$.

- 选这条线段

这条线段会使得部分子集的复杂度上升，我们只要找出和这条线段不想加的数的个数就行了。

然后加一的数量就是 $2^x$。

对于那些复杂度不上升的以及复杂度上升的原始部分之和就是 $f_{i-1}$

那么转移就很明显了，别忘了加上 $f_{i-1}$

因为要继承上一状态贡献。

那么得出递推式： $f_i = f_{i - 1} \times 2 + 2^x$

接下来就只要求出 $x$ 就行了。

这个 $x$ 也很好维护，直接用前缀和维护一下有哪些线段的右端点比当前的左端点更小就行了。

那么，代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ls (x << 1)
#define rs (x << 1 | 1)
#define mid ((l + r) >> 1)
#define int long long
#define Rep(x, a, b) for(int x = a; x <= b; ++ x)
#define Dep(x, a, b) for(int x = a; x >= b; -- x)
#define Next(i, x) for(int i = head[x]; i ; i = e[i].nxt)
int read() {
    char c = getchar(); int x = 0, f = 1;
    while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
const int maxn = 2e5 + 10;
const int XRZ = 1e9 + 7;
struct node { int l, r; } e[maxn];
int f[maxn], sum[maxn];
int qpow(int x, int y) {
	int base = x, ans = 1;
	while(y) {
		if(y & 1) ans = (ans * base) % XRZ;
		base = (base * base) % XRZ; y >>= 1;
	} return ans;
} int cmp(node x, node y) { return x.l < y.l;}
signed main() { int n = read();
	Rep(i, 1, n) e[i].l = read(), e[i].r = read(), sum[e[i].r] ++;
	Rep(i, 1, n * 2) sum[i] += sum[i - 1];
	sort(e + 1, e + n + 1, cmp);
	Rep(i, 1, n) f[i] = (f[i - 1] * 2 % XRZ + qpow(2, sum[e[i].l - 1])) % XRZ;//, printf("%d %d\n", i, f[i]);
	printf("%lld", f[n]);
	return 0;
}	
```

---

## 作者：7KByte (赞：4)

这里提供一个不同的方法。


对于每一个线段$[l_i,r_i]$，当它对答案产生贡献时，当且仅当不存在另一个区间$[l_j,r_j]$使得$l_j<l_i<r_j$。

因为只要有区间$j$存在，只可能是$j$产生贡献

所以我们统计每一个线段，有多少线段不能与它共存，设有$S$个，那么它对答案的贡献为$2^{N-S-1}$

如何求出$S$呢，我们首先将所有区间按$l$排序，然后对于$r$维护一棵线段树即可


```cpp
#include<bits/stdc++.h>
#define N 200005
#define rep(I,A,B) for(int I=A;I<=B;I++)
using namespace std;
int n;
struct pt{
	int l,r;
	bool operator<(const pt o)const{
		return l<o.l;
	}
}u[N];
struct node{
	int l,r,add,sum;
}a[N<<2];
#define L a[x].l
#define R a[x].r
#define ls (x<<1)
#define rs (ls|1)
#define A a[x].add
#define S a[x].sum
void build(int x,int l,int r){
	L=l;R=r;A=0;S=0;
	if(l==r)return;
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
}
void updata(int x){
	S=A+max(a[ls].sum,a[rs].sum);
}
void change(int x,int l,int r,int val){
	if(L>=l&&R<=r)A+=val,S+=val;
	else{
		int mid=(L+R)>>1;
		if(mid>=l)change(ls,l,r,val);
		if(mid<r)change(rs,l,r,val);
		updata(x);
	}
}
int ask(int x,int l,int r,int val){
	if(L>=l&&R<=r)return S+val;
	int mid=(L+R)>>1,ret=0;
	val+=A;
	if(mid>=l)ret=max(ret,ask(ls,l,r,val));
	if(mid<r)ret=max(ret,ask(rs,l,r,val));
	return ret;
}
typedef long long ll;
#define P 1000000007LL
ll Pow(ll x,ll y){
	ll now=1;
	for(;y;y>>=1,x=(x*x)%P)if(y&1)now=(now*x)%P;
	return now;
}
ll ans=0;
int main(){
	scanf("%d",&n);
	rep(i,1,n)scanf("%d%d",&u[i].l,&u[i].r);
	sort(u+1,u+n+1);
	build(1,1,n<<1);
	rep(i,1,n){
		ans=(ans+Pow(2,n-ask(1,u[i].l,n<<1,0)-1))%P;
		change(1,u[i].l,u[i].r,1);
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：RemiliaScar1et (赞：3)

简单计数题。

考虑将线段一条一条加入集合中。

由于这是一个无序集，所以我们加入的顺序没有影响，可以选择对我们最有利的方式加：将所有线段**按左端点从小到大排序，然后从左到右加入集合**，累加每条线段对答案的贡献。

为什么这样较优？因为这样加入时，我们**只需要考虑左端点与之前加入的线段的右端点相交的情况**，而不用考虑右端点与之前加入的线段左端点相交的情况。

下面设 $f(i)$ 为**加入了前 $i$ 条线段的集合的复杂度和**。

寻找最后一个不同点：集合中的一个子集对于第 $i$ 条线段，我们可以选或不选。

- 不选：
	
    那么我们实际能拿来拼凑子集的线段和上一个状态一样，即答案为 $f(i-1)$ 。

- 选：

	原有的子集复杂度 $f(i-1)$ 仍然在。
	
   考虑在原有的集合中加入这条线段。
   
	此时，当前线段与之前线段如果没有交点，那么这个子集的复杂度就会 $+1$。
    
   所以我们要做的是统计出之前的线段中有多少小于当前线段，设这个数为 $k$，答案就是 $2^k$。
   
   权值线段树刚好能满足我们的需要。
   
   我们每次统计完当前状态后，将当前线段的右端点插入权值线段树。每次查询查询区间 $[1,L_i]$ 即可。
   
综上，状态转移方程：

$$f(i)=2\times f(i-1)+2^k$$

 $k$ 使用权值线段树维护。
 
时间复杂度 $O(n\log n)$

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;

const int N=2e5+10,mod=1e9+7;

int f[N];
PII arr[N];
int tree[N<<2];

#define lnode node<<1
#define rnode node<<1|1
#define DEFMID int mid=(start+end)>>1

void push_up(int node)
{tree[node]=tree[lnode]+tree[rnode];}

void insert(int node,int start,int end,int val)
{
	if(start==end)
	{
		tree[node]++;
		return ;
	}
	DEFMID;
	if(val<=mid) insert(lnode,start,mid,val);
	else insert(rnode,mid+1,end,val);
	push_up(node);
}

int query(int node,int start,int end,int l,int r)
{
	if(end<l||start>r) return 0;
	if(l<=start&&end<=r) return tree[node];
	DEFMID;
	int sum=0;
	if(l<=mid) sum+=query(lnode,start,mid,l,r);
	if(r>mid) sum+=query(rnode,mid+1,end,l,r);
	return sum;
}

#undef lnode 
#undef rnode 
#undef DEFMID

int fpow(int x)
{
	ll res=1,a=2;
	while(x)
	{
		if(x&1) res=res*a%mod,res%=mod;
		a=a*a%mod,a%=mod;
		x>>=1;
	}
	return (res%mod+mod)%mod;
}

#define L first
#define R second

int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&arr[i].L,&arr[i].R);
	sort(arr+1,arr+1+n);//排序
	for(int i=1;i<=n;i++)
	{
		int x=query(1,1,n<<1,1,arr[i].L-1);
		f[i]=((2*f[i-1])%mod+fpow(x))%mod;
		insert(1,1,n<<1,arr[i].R);
	}
	printf("%d",f[n]%mod);
	return 0;
}
```

---

## 作者：一只书虫仔 (赞：2)

#### Description

> 给定 $n$ 条线段 $[l_i,r_i]$，每次对于一条线段可以选或不选，求形成的 $2^n$ 种选择情况形成的连通块个数之和。

#### Solution

为了方便计算，先按照 $l_i$ 升序排序。

考虑动态规划。

设 $dp_i$ 为截止到第 $i$ 条边的答案，因为答案算总和所以没必要升维，直接加到一维上即可。

考虑两种情况：

- 不选第 $i$ 条线段，那么对答案的贡献即为 $dp_{i-1}$。
- 选第 $i$ 条线段，那么在 $dp_{i-1}$ 的基础上还要加上新形成的连通块，如果有前面的线段 $[l_j,r_j]$ 满足 $l_i \le r_j \le r_i$，那么他们将合并为同一条线段，不会产生新的连通块。又因为按照 $l_i$ 升序排序，所以计算有多少个线段 $[l_j,r_j]$ 满足 $r_j<l_i$ 即可。但是直接暴力这样复杂度可能较高，所以不如采用桶排的方式，定义 $cnt[i]$ 为有多少个满足 $r_j<l_i$ 的线段，那么这条线段对答案的贡献即为 $dp[i-1]+2^{cnt[i]}$。

这个 $cnt[i]$ 可以搞成一个通排记录 $r_i$ 个数的前缀和。

#### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

struct line {long long l, r;} a[100086];
bool fjrakioi (line x, line y) {return x.l < y.l;}

long long box[200086];
long long cnt[200086];
long long dp[100086];
long long Mod = 1e9 + 7;

long long binpow (long long b, long long p, long long k) {
	b %= k;
	long long res = 1;
	while (p > 0) {
		if (p & 1)
			res = res * b % k;
		b = b * b % k;
		p >>= 1;
	}
	return res;
}

int main () {
	long long n;
	scanf("%lld", &n);
	for (long long i = 1; i <= n; i++) scanf("%lld%lld", &a[i].l, &a[i].r);
	sort(a + 1, a + n + 1, fjrakioi);
	for (long long i = 1; i <= n; i++) box[a[i].r]++;
	for (long long i = 1; i <= 2 * n; i++) cnt[i] = cnt[i - 1] + box[i];
	for (long long i = 1; i <= n; i++) {
		dp[i] += dp[i - 1];
		dp[i] %= Mod;
		dp[i] += (dp[i - 1] + binpow(2, cnt[a[i].l - 1], Mod));
		dp[i] %= Mod;
	}
	printf("%lld", dp[n]);
	return 0;
}
```

---

## 作者：yc20170111 (赞：2)

# \[ 动态规划·线段树优化 \]
显然，这个题目和集合有关。
手推一下，可以发现：对区间左端点从小到大排序，枚举加入第 $i$ 个区间，可以发现贡献可用如下公式计算： 
$$
贡献=2^{i-1-x}
$$
其中，$x$ 表示第 $i$ 个区间被 $x$ 个区间覆盖。答案即为所有贡献的求和。

考虑当前加入第 $i$ 个集合，可以先将前面的 $2^{i-1}$ 个集合 copy 一份，在一份的 $2^{i-1}$ 个集合后面都加上当前集合。如果将 $i-1$ 集合的选与不选情况看作一个 $01$ 串，则只有前面覆盖第 $i$ 个区间的 $x$ 个都没有出现（对应 $01$ 串位置为 $0$ ）时，当前区间 $i$ 有贡献。此时剩下 $i-1-x$ 个集合都有出现和不出现两种状态，因此新增的贡献为 $2^{i-1-x}$ 。 

如果暴力枚举 $i$ 之前的所有点，算法的复杂度就有 $n^2$ ，显然过不了。因此，考虑用数据结构维护。

问题转化为：求 $[l_i,r_i]$ 区间内被覆盖最多的区间。很容易想到用线段树维护区间最大线段覆盖。

AC 代码
```cpp
#include<algorithm>
#include<cstdio>
#define N 100010
#define LL long long
#define MOD (LL)(1e9+7)
#define Max(a,b) (a>b?a:b)
using namespace std;

LL n;
struct RANGE{LL l,r;}a[N];
struct TREE{LL mx,tag;}t[N<<3];

bool cmp(RANGE x,RANGE y){return x.l<y.l;}
void pushdown(LL o){
	if(!t[o].tag)return ;
	t[o<<1].mx+=t[o].tag;
	t[o<<1].tag+=t[o].tag;
	t[o<<1|1].mx+=t[o].tag;
	t[o<<1|1].tag+=t[o].tag;
	t[o].tag=0;
}
LL query(LL o,LL lf,LL rt,LL ll,LL rr){
	if(rt<ll||lf>rr){
		return 0;
	}else if(lf>=ll&&rt<=rr){
		return t[o].mx;
	}else{
		LL mid=(lf+rt)>>1; pushdown(o);
		LL v1=query(o<<1,lf,mid,ll,rr);
		LL v2=query(o<<1|1,mid+1,rt,ll,rr);
		return Max(v1,v2);
	}
}
void modify(LL o,LL lf,LL rt,LL ll,LL rr,LL k){
	if(rt<ll||lf>rr){
		return ;
	}else if(lf>=ll&&rt<=rr){
		t[o].mx+=k; t[o].tag+=k;
	}else{
		LL mid=(lf+rt)>>1; pushdown(o);
		modify(o<<1,lf,mid,ll,rr,k);
		modify(o<<1|1,mid+1,rt,ll,rr,k);
		
		t[o].mx=Max(t[o<<1].mx,t[o<<1|1].mx);
	}
}
LL POW(LL x,LL y){
	LL sum=x,ans=1;
	while(y){
		if(y&1)ans=(ans*sum)%MOD;
		y>>=1; sum=(sum*sum)%MOD;
	} return ans;
}
int main(){
	scanf("%lld",&n);
	for(LL i=1;i<=n;++i)
		scanf("%lld%lld",&a[i].l,&a[i].r);
	sort(a+1,a+1+n,cmp);
	
	LL ans=0;
	for(LL i=1;i<=n;++i){
		ans=((ans<<1)%MOD+POW(2,i-1-query(1,1,n*2,a[i].l,a[i].r)))%MOD;
		modify(1,1,n*2,a[i].l,a[i].r,1); // 线段树维护交集 
	}
	printf("%lld\n",ans);
}
```

---

## 作者：Durancer (赞：2)

### 前置知识

- 组合数学

- 递推

### 思路：

1、按照左端点 $l$ 排序。

2、考虑从左往右依次求贡献，并设置转移方程

设 $f_i$ 表示前 $i$ 条线段的子集的复杂度之和。

接下来考虑贡献：

一共可以分为两类，一种是没有第 $i$ 条线段时的贡献，那么肯定是 $f_{i-1}$ 了，再考虑有了第 $i$ 条线段的贡献，又是分为两类，一类是如果一个方案中，出现了和 $i$ 线段相交的的线段，那么贡献是不会改变的，所以还是有一个 $f_{i-1}$ ，继续想 ，在前面加的第 $2$ 个 $f_{i-1}$ 中一定会有一些方案是没有与第 $i$ 条线段接触的，那么这个时候就寻找与 $i$ 不相交的线段个数。

得出来的贡献就是：

$$C_{x}^0+C_{x}^1+C_{x}^2+\cdots+C_{x}^x=2^x$$

最后的出来的状态转移方程即为：

$$f_{i}=f_{i-1}+f_{i-1}+2^x$$

3、预处理

对于求 $x$ 的准确值，直接前缀和预处理线段右端点的位置在 $i$ 之前的个数 $s_i$  即可。

```cpp

#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#define int long long 
using namespace std;
const int N=1e5+9;
const int mod=1e9+7;
struct node{
	int l;
	int r;
}a[N];
int n,ans; 
int f[N];
int s[2*N]; 
int read()
{
	int f=1,x=0;
	char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=(x<<1)+(x<<3)+(s^'0');s=getchar();}
	return f*x;
}
bool cmp(node x,node y)
{
	if(x.l!=y.l)
		return x.l<y.l;
	else return x.r<y.r;
}
int quick(int x,int p)
{
	int ret=1;
	while(p)
	{
		if(p&1) ret=ret*x%mod;
		x=x*x%mod;
		p>>=1; 
	}
	return ret;
}
void DP()
{
	for(int i=1;i<=n;i++)
	{
		int x=s[a[i].l-1];
		f[i]=(f[i]+f[i-1])%mod;
		f[i]=(f[i]+f[i-1])%mod;
		f[i]=(f[i]+quick(2,x))%mod;
	}
}
signed main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		a[i].l=read();
		a[i].r=read();
	}
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++)
		s[a[i].r]++;
	for(int i=1;i<=2*n;i++)
		s[i]=(s[i]+s[i-1])%mod;
	DP();
	printf("%lld\n",f[n]);
	return 0; 
}

---

## 作者：koreyoshi_lemon (赞：1)

为明确划分已求解部分和未求解部分的轮廓，我们对这些线段按左端点进行排序，这是动态规划的一个思想。

排序之后，就只需要将这些线段按顺序逐渐加入已求解的部分，也就是说，只需要计算出每一条线段对答案的贡献，就完成的求解。

一条线段对答案的贡献可以分为两种：

1. 不使用这一条线段，显然此时直接继承上一次的答案即可

2. 重点在于使用这一条线段。如果加入这一条线段，对于和它有重合部分的线段集合，无论怎么选都会和新线段形成一个等大的并，也就是说**对于有重合线段的集合，新线段对连通块数量没有影响**。而对与它没有重合的线段集合，任意一个子集都不与新线段重合，都是两个连通块，也就是说，**没有重合的线段集合的子集数量，就是新线段对答案的贡献**。

至此，我们可以写出到第 $i$ 条线段时的复杂度之和：

$f_i=f_{i-1}+(f_{i-1}+S)=2f_{i-1}+S$

其中 $S$ 表示内个子集的数量。

这时，排序的作用就显现出来了。我们只要统计有几个右端点小于新线段的左端点，就能算出与新线段无重合的线段集合的大小。具体就是，开一个桶存储每一个位置作为右端点的次数，再求一次前缀和即可。

知道了集合大小，如何求子集数量呢？题目告诉我们，大小为 $N$ 的集合，有 $2^N$ 个子集（含 $\varnothing$）。这是为什么呢？

子集可以认为是从原集合中选取了一些元素。所以大小为 $1$ 的子集数量就是 $C_N^1$，大小为 $2$  的子集数量是 $C_N^2$，以此类推。所以子集的总数就是：


$C_N^1+C_N^2+...+C_N^N=\sum\limits_{i=0}^N C_N^i$

逆用二项式定理：

$\sum\limits_{i=0}^N C_N^i=\sum\limits_{i=0}^N C_N^i \cdot 1=(1+1)^N=2^N$

从而得证。

有了思路，代码也就很容易了。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+7;
const int mod=1e9+7;
struct line{int l,r;}a[N];
int f[N],s[N];
int n,tmp[N];
inline bool cmp(line x,line y){return x.l<y.l;}
inline void istmp(int k)	{
	tmp[0]=1;
	for(int i=1;i<=k;i++)	{
		tmp[i]=tmp[i-1]<<1;
		tmp[i]%=mod;
	}
	return;
}
inline int Qpow(int k){return tmp[k];}
signed main(void)
{
	scanf("%lld",&n);
	istmp(n<<1);
	for(int i=1;i<=n;i++)	{
		scanf("%lld%lld",&a[i].l,&a[i].r);
		s[a[i].r]++;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n<<1;i++)  //注意是 N<<1 ,题目规定 1<=l,r<=2N 
		s[i]+=s[i-1];
	for(int i=1;i<=n;i++)	{
		f[i]=2*f[i-1]+Qpow(s[a[i].l-1]);
		f[i]%=mod;
	}
	printf("%lld\n",f[n]);
	return 0;
}
```

我这里选择预处理处 $2^k$，算是一个小优化。

如果数据进一步加强，我们可以使用基数排序，桶排序等非比较排序结合预处理，复杂度可以降到 $O(n)$ ，来通过 $10^7$ 规模的数据。

---

## 作者：chen_qian (赞：1)

最近开始刷usaco的题，写一发题解

T1 [Timeline](https://www.luogu.com.cn/problem/P6145)

**Analysis**：比较简单的题目，首先对于每一个时间 $i$ 发生的时间至少都在$s_i$之后，所以把启始时间就赋值为$s_i$,再之后，对于每一个限制条件$(a,b,x)$为翻译出准确的信息，都要在$a$时间确定之后在推知对于$b$的限制，这样的后效性处理就让人自然而然地想到拓扑排序。

所以对于每一个$(a,b,x)$，在$a$向$b$连长为$x$的一条边，然后进行拓扑排序，更新事件能发生的最小时间。

```
#include<bits/stdc++.h>
#define N 100005 
using namespace std;
int n,m,c;
int ans[N],in[N];
int head[N],idx;
struct edge{
	int w,v,next;
}e[N];
void add(int u,int v,int w){
	e[++idx].v=v;
	e[idx].w=w;
	e[idx].next=head[u];
	head[u]=idx;
}
int main(){
	freopen("timeline.in","r",stdin);
	freopen("timeline.out","w",stdout);
	scanf("%d%d%d",&n,&m,&c);
	for(int i=1;i<=n;i++) scanf("%d",&ans[i]);
	for(int i=1;i<=c;i++){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
		in[y]++;
	}
	queue<int> q;
	for(int i=1;i<=n;i++)
		if(!in[i]) q.push(i); 
	
	while(!q.empty()){
		int x=q.front();
		q.pop();
		for(int i=head[x];i;i=e[i].next){
			int y=e[i].v;
			ans[y]=max(ans[y],ans[x]+e[i].w);
			in[y]--;
			if(!in[y]) q.push(y);
		}
	}
	for(int i=1;i<=n;i++) cout<<ans[i]<<endl;
	return 0;
}
```
T2 [Help Yourself](https://www.luogu.com.cn/problem/P6146)

**Analysis**：在这里，枚举每一个集合显然不现实，所以我们考虑每一条线段能够对答案产生的贡献。

此时我们令$f[x]$为前$x$个条线段的答案总和，当我们把$x+1$条线段加入时，当它与之前的所有集合连起来时，如果有可以与其连起来的集合，那么这条这些集合产生的贡献其实和没加入是是一样的，对于无法连起来的集合，在它们本身可以产生贡献的同时，新加入的线段和可以额为产生$1$的
的贡献，假设有$m$个这样的线段那么这些线段产生的集合数就有$2^m$所以一共的贡献就为$f[x+1]=f[x]*2+2^m$

```cpp
#include<bits/stdc++.h>
#define N 100005
#define mod 1000000007
#define ll long long 
using namespace std;
int n;
struct node{
	int l,r;
}a[N]; 
bool cmp(node x,node y){
	return x.l<y.l;
}
ll f[N];
int t[2*N];
int qpow(int x){
	ll ans=1,b=2;
	while(x){
		if(x&1) ans=(ans*b)%mod;
		b=(b*b)%mod;
		x>>=1;
	}
	return ans%mod;
}
int main(){
	freopen("help.in","r",stdin);
	freopen("help.out","w",stdout); 
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d",&a[i].l,&a[i].r),t[a[i].r]++;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=2*n;i++) t[i]+=t[i-1];
	for(int i=1;i<=n;i++){
		f[i]=(2*f[i-1]+qpow(t[a[i].l-1]))%mod;
	}
	cout<<f[n]<<endl;
	return 0;
}
```
T3 [Delegtion](https://www.luogu.com.cn/problem/P6147)

与2018年NOIP的某题相似，不再赘述。

```
#include<bits/stdc++.h>
#define N 100005
using namespace std;
int n,head[N],idx;
struct edge{
	int v,next;
}e[2*N];
void add(int u,int v){
	e[++idx].v=v;
	e[idx].next=head[u];
	head[u]=idx;
}
int ans[N],f[N];
vector<int> s[N];
int dfs(int x,int lim,int fa){
	for(int i=head[x];i;i=e[i].next){
		int y=e[i].v;
		if(y==fa) continue;
		int u=dfs(y,lim,x);
		if(u==-1) return -1;
		if(u+1==lim) continue;
		s[x].push_back(u+1);
	} 
	sort(s[x].begin(),s[x].end());
	int l=0,r=s[x].size()-1,ret=0;
	while(l<r){
		if(s[x][l]+s[x][r]==lim) l++,r--;
		else if(ret){
			return -1;
		}
		else if(s[x][l]+s[x][r]>lim) ret=s[x][r],r--;
		else ret=s[x][l],l++;
	}
	if(l>r){
		return ret;
	}
	else if(ret) return -1;
	return s[x][l];
}
int check(int x){
	for(int i=1;i<=n;i++) s[i].clear();
	if(dfs(1,x,0)!=-1) return 1;
	else return 0; 
}
int main(){
	freopen("deleg.in","r",stdin);
	freopen("deleg.out","w",stdout); 
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	dfs(1,3,0);
	for(int i=1;i<n;i++){
		if((n-1)%i==0) ans[i]=check(i);
		else ans[i]=0;
	}
	for(int i=1;i<n;i++) cout<<ans[i];
	return 0;
}
```


---

## 作者：Lates (赞：0)

先把所有线段按左端点排序。

考虑 $f[i]$ 为排序后前 $i$ 条线段的复杂度总和

当我们考虑完前 $i-1$ 的线段，此时要选择加不加入第 $i$ 个线段。

当不加这条时，$f[i]$ 不变,则 $f[i]=f[i-1]$

当加这条时，首先要把 $f[i-1]$ 加上，因为 $f[i]$ 只会因为当前线段增加。有两种情况：与前面的线段相交或不相交。

当相交时，多出来了 $2^{tot}$ 个集合的 1 复杂度的贡献，$tot$ 指 $1-(i-1)$ 的与第 $i$ 条不相交的线段。

由于开始把线段按左端点排序，所以当一个线段的右端点小于线段$i$ 的左端点，则两线段不相交。

此时可以维护一个 $2\times 10^5$ 的树状数组统计

则方程为 $f[i]=f[i-1]+f[i-1]+2^{tot}$


```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read(){
	register int x=0,f=0,ch=getchar();
	while('0'>ch||ch>'9')f^=ch=='-',ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^'0'),ch=getchar();
	return f?-x:x;
}
const int MAX=1e5+5,P=1e9+7,D=2e5+5;
int n;struct L{int l,r;}e[MAX];
inline bool cmp(L a,L b){return a.l<b.l;};
inline int qpow(int x,int p){
	register int res=1;
	for(;p;p>>=1,x=1ll*x*x%P)if(p&1)res=1ll*res*x%P;
	return res;
}
int C[D],f[MAX];
inline void add(int x){
	for(;x<=D-5;x+=(x&-x))++C[x];
}
inline int sum(int x){
	register int res=0;
	for(;x;x-=(x&-x))res+=C[x];
	return res;
}
signed main(){
	n=read();
	for(register int i=1;i<=n;++i)e[i]=(L){read(),read()};
	sort(e+1,e+1+n,cmp);
	for(register int i=1,x;i<=n;++i){
		x=sum(e[i].l-1);
		f[i]=(f[i-1]*2%P+qpow(2,x))%P;
		add(e[i].r);
	}
	printf("%d\n",f[n]);
	return 0;
}


```


---

## 作者：issue_is_fw (赞：0)



考虑单独一条线段$a$的贡献

如果选的子集中没有线段和$a$相交,贡献毫无疑问是$1$

若有$k$条线段和$a$相交,所有的$k$条贡献是$1$

这样非常不好计算,所以我们规定如果多条线段相交,贡献是左端点最左的线段

那么可以得到,如果$a$对答案有贡献

不会存在一条直线满足$l_i<l_a<r_i$,其余线段都可以

如何计算??按照左端点排序,对右端点维护线段树即可

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5+10;
const int mod = 1e9+7;
#define mid (l+r>>1)
#define ls (rt<<1)
#define rs (rt<<1|1)
#define lson ls,l,mid
#define rson rs,mid+1,r
struct point{
	int l,r;
	bool operator < (const point&tmp )	const{ return l<tmp.l; }
}a[maxn];
int sumn[maxn<<2],fac[maxn],n;
int ask(int rt,int l,int r,int L,int R)
{
	if( L<=l&&R>=r )	return sumn[rt];
	if( L>r||R<l )	return 0;
	return ask(lson,L,R)+ask(rson,L,R);
}
void insert(int rt,int l,int r,int k)
{
	if( l==r&&l==k ){ sumn[rt]=1; return; }
	if( l>k||r<k )	return;
	insert(lson,k); insert(rson,k);
	sumn[rt] = sumn[ls]+sumn[rs];
}
int main()
{
	fac[0] = 1;
	for(int i=1;i<=100000;i++)	fac[i] = fac[i-1]*2%mod;
	cin >> n;
	for(int i=1;i<=n;i++)	cin >> a[i].l >> a[i].r;
	sort( a+1,a+1+n );
	int ans = 0;
	for(int i=1;i<=n;i++)
	{
		int x = fac[n-1-ask(1,1,2*n,a[i].l+1,2*n)];
		ans = ( ans+x )%mod;
		insert( 1,1,2*n,a[i].r );
	}
	cout << ans;
}
```

---

