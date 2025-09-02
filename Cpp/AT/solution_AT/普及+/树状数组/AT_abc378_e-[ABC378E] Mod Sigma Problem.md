# [ABC378E] Mod Sigma Problem

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc378/tasks/abc378_e

You are given a sequence $A = (A_1, A_2, \dots, A_N)$ of $N$ non-negative integers, and a positive integer $M$.

Find the following value:

$$
 \sum_{1 \leq l \leq r \leq N} \left( \left(\sum_{l \leq i \leq r} A_i\right) \mathbin{\mathrm{mod}} M \right). 
$$

Here, $X \mathbin{\mathrm{mod}} M$ denotes the remainder when the non-negative integer $X$ is divided by $M$.

## 说明/提示

### 制約

### Constraints

-   $1 \leq N \leq 2 \times 10^5$
-   $1 \leq M \leq 2 \times 10^5$
-   $0 \leq A_i \leq 10^9$
 
### Sample Explanation 1

-   $A_1 \mathbin{\mathrm{mod}} M = 2$
-   $(A_1+A_2) \mathbin{\mathrm{mod}} M = 3$
-   $(A_1+A_2+A_3) \mathbin{\mathrm{mod}} M = 3$
-   $A_2 \mathbin{\mathrm{mod}} M = 1$
-   $(A_2+A_3) \mathbin{\mathrm{mod}} M = 1$
-   $A_3 \mathbin{\mathrm{mod}} M = 0$

The answer is the sum of these values, $10$. Note that the outer sum is not taken modulo $M$.

## 样例 #1

### 输入

```
3 4
2 5 0```

### 输出

```
10```

## 样例 #2

### 输入

```
10 100
320 578 244 604 145 839 156 857 556 400```

### 输出

```
2736```

# 题解

## 作者：fishing_cat (赞：9)

[传送门](https://atcoder.jp/contests/abc378/tasks/abc378_e)

### 具体做法

首先考虑前缀和，计 $qzh$ 表示给定串 $A$ 的前缀和取模后的值，也就是在组成答案的所有贡献串中以 $A_1$ 开头的串。

然后，将答案转化成可以用 $qzh$ 表示的形式，将取模运算忽略，先粗论计算：

$$\sum_{1 \le l \le r\le N} \left (  \sum_{l \le i \le r} A_i \right ) $$
$$= \sum_{1 \le i \le N}i \cdot qzh_i - \sum_{1 \le i \le N}(N - i) \cdot qzh_i$$
$$= \sum_{1 \le i \le N} (2i - N) \cdot qzh_i$$

当然这个式子是不对的，仅用来思路参考。因为 $qzh$ 的计算已经有过取模运算，所以在向上面一样统计不是以 $A_1$ 开头的串时，直接 $qzh$ 间的相互操作，会因为 $qzh$ 是取过一次模的缘故而出现负数，这显然就是不对的了。

注意到，单独非 $A_1$ 开头的串也是要取模的，所以对于负数数的值，实际贡献是在之前假了的式子上再加一个 $M$。对于最后的答案，现在就是要考虑要加多少个 $M$ 的事了。看回上一段，会发现每出现一次负数才会有一次加 $M$，而负数是因为出现了 $qzh_i > qzh_j(i \le j)$，所以次数就是 $qzh$ 序列的逆序对个数。[逆序对模板题](https://www.luogu.com.cn/problem/P1908)

计 $num$ 为 $qzh$ 序列的逆序对个数，得到：
$$\sum_{1 \le l \le r\le N} \left ( \left (  \sum_{l \le i \le r} A_i \right ) \bmod M \right )$$
$$= \sum_{1 \le i \le N} (2i - N) \cdot qzh_i + num \cdot M$$

然后就是 $O(N)$ 处理前面的一坨，$O(N \log N)$ 计算逆序对个数。

### code

[link](https://www.luogu.com.cn/record/186688959)

```cpp
#include<bits/stdc++.h>
#define ll long long
#define il inline
const ll N = 200100;
using namespace std;
/*快读省了*/
ll n, m, a[N], num, ans;
ll tr[N], rk[N];
struct node{ ll vel, it; } qzh[N];

il bool cmp(node a, node b) {
	if (a.vel == b.vel) 
		return a.it < b.it;
	return a.vel < b.vel;
}

il void add(ll x, ll k) {
	for (; x <= n; x += x&(-x)) tr[x] += k; 
}
il ll ask(ll x) {
	ll res = 0;
	for (; x; x -= x&(-x)) res += tr[x];
	return res;
}

int main() {
	read(n); read(m);
	for (int i = 1; i <= n; i++) {
		read(a[i]);
		qzh[i].vel = (qzh[i-1].vel + a[i]) % m; // 处理前缀和
		qzh[i].it = i;
	}
	for (int i = 1; i <= n; i++) // 计算前面那一坨
		ans += (2*i - n) * qzh[i].vel;
	
	sort(qzh+1, qzh+n+1, cmp);
	for (int i = 1; i <= n; i++) 
		rk[qzh[i].it] = i; // 离散化
	for (int i = 1; i <= n; i++) { // 树状数组处理 逆序对
		add(rk[i], 1);
		num += i - ask(rk[i]);
	}	
		
	printf("%lld", ans + num*m);
	return 0; // 完结撒花
}
```

---

## 作者：yzljy (赞：3)

[洛谷传送门](https://www.luogu.com.cn/problem/AT_abc378_e)  
[AT传送门](https://atcoder.jp/contests/abc378/tasks/abc378_e)

### 题意

给一个长为 $n$ 的数组 $a$，求其所有子段和对 $m$ 取模后的和。

$1 \le n \le 2 \times 10^{5}$  
$1 \le m \le 2 \times 10^{5}$  
$1 \le a_{i} \le 10^{9}$

### 思路

因为子段和可以转化为前缀和之差。  
所以我们可以先对 $a$ 数组做前缀和，记作 $pre$ 数组。

考虑枚举右端点，每次统计所有以右端点结尾的子段的答案和。  
先考虑暴力枚举左端点。设当前右端点为 $r$，左端点为 $l$。    
有这么两种情况：

 + $pre_{r}-pre_{l-1} \ge 0$，这种情况直接统计答案即可。
 + $pre_{r}-pre_{l-1} < 0$，这种情况值加上 $m$ 再统计即可。

时间复杂度 $O(n^{2})$，考虑优化。

现在我们实际上将 $a_{i}$ 的范围变成了 $0 \le a_{i} < m$，而上面两种情况，其实就是对值小于等于 $pre_{r}$ 的数统计一种答案，再对大于的统计另一种答案。  
那么我们可以用树状数组来优化这一过程。  

具体实现上：  
我们可以开两个值域树状数组，一个存储值的和，记作 $sum$，一个存储值的个数，记作 $cnt$。  
对于第一种情况，那就是 $cnt_{pre_{r}} * pre_{r} - sum_{pre_{r}}$，第二种情况是类似的，只是加上 $cnt_{pre_{r}} * m$。

时间复杂度 $O(n \log V)$

### 代码

```cpp
// Problem: E - Mod Sigma Problem
// Contest: AtCoder - AtCoder Beginner Contest 378
// URL: https://atcoder.jp/contests/abc378/tasks/abc378_e
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e5+10;
const int mod1=1e9+7;
const int mod2=998244353;
const int inf_int=0x7f7f7f7f;
const long long inf_long=0x7f7f7f7f7f7f7f7f;
const double eps=1e-9;
char Buf[1<<23],*P1=Buf,*P2=Buf;
#define getchar() (P1==P2&&(P2=(P1=Buf)+fread(Buf,1,1<<23,stdin),P1==P2)?EOF:*P1++)
template<typename type>
inline void read(type &x){
	x=0;
	bool f=false;
	char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=getchar();
	if(f) x=-x;
}
template<typename type,typename... args>
inline void read(type &x,args&... y){
	read(x),read(y...);
}

int n,m,ans,val[MAXN];

int lowbit(int u){
	return u&(-u);
}

struct node{
	int a[MAXN];
	void init(){
		for(int i=1;i<=2e5;i++) a[i]=0;
	}
	void update(int pos,int val){
		while(pos<=2e5){
			a[pos]+=val;
			pos+=lowbit(pos);
		}
	}
	int query(int pos){
		int res=0;
		while(pos){
			res+=a[pos];
			pos-=lowbit(pos);
		}
		return res;
	}
}t,cnt;


signed main(){
	read(n,m);t.init();cnt.init();
	for(int i=1;i<=n;i++) read(val[i]);
	for(int i=1;i<=n;i++) val[i]%=m;
	for(int i=1;i<=n;i++) val[i]=(val[i]+val[i-1])%m;
	t.update(1,1);cnt.update(1,1);
	for(int i=1;i<=n;i++){
		int z=val[i]+1;
		ans+=cnt.query(z)*(z)-t.query(z);
		ans+=(cnt.query(2e5)-cnt.query(z))*(m+z)-(t.query(2e5)-t.query(z));
		t.update(z,z);
		cnt.update(z,1);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：MLE_Automaton (赞：3)

第一次做出来 E，很激动。

# 题目分析

给定一个序列 $a$，求这个序列中的所有连续子序列的和模 $M$，它们相加起来的和，**注意这里不能把结果取模**。

我们先想想看把结果取模的 $O(n)$ 做法，无非就是累加前面的前缀和，相减，取模即可，这里给出一段代码，后面会进行修改：

```cpp
rep(i, 1, n) (a[i] += a[i - 1]) %= m;
rep(i, 1, n)
{
    ans += ((a[i] * i - s) % m + m) % m;
    s += a[i];
}
```

然后，我们知道 $(a - b)\bmod m$ 是等于 $a\bmod m - b\bmod m + m \bmod m$ 的（注意这个加 $m$，瓶颈就在这），然后可以把它拆分成两种情况：如果 $a\bmod m \ge b\bmod m$，那么 $(a - b)\bmod m$ 就等于 $a \bmod m- b\bmod m$，否则就等于 $a \bmod m- b\bmod m + m$。

知道了这个，就很好写了，可以使用树状数组维护在这之前有多少个前缀和模 $m$ 是大于这个前缀和的。

# Talk is cheap, show me the code.

因为树状数组下标是从 $1$ 起的，所以查询和更改时需要将下标加 $1$。

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define pre(i,a,b) for(int i=(a);i>=(b);i--)
#define INF 0x3f3f3f3f
#define llINF 0x3f3f3f3f3f3f3f3f
#define bigpq(type) priority_queue<type>
#define smpq(type) priority_queue<type,vector<type>,greater<type>>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

ll n, m, a[200005], tr[200005], ans, s;
void add(ll i, ll x)
{
    while (i <= m)
    {
        tr[i] += x;
        i += i & -i;
    }
}
ll sum(ll i)
{
    ll res = 0;
    while (i)
    {
        res += tr[i];
        i -= i & -i;
    }
    return res;
}
int main()
{
    scanf("%lld%lld", &n, &m);
    rep(i, 1, n) scanf("%lld", &a[i]), (a[i] += a[i - 1]) %= m;
    rep(i, 1, n)
    {
        ans += a[i] * i - s + (i - 1 - sum(a[i] + 1)) * m;
        add(a[i] + 1, 1); s += a[i];
    }
    printf("%lld", ans);
    return 0;
}
```

考完才发现就是逆序对个数板子，用归并排序应该也行。

---

## 作者：2huk (赞：3)

首先把区间长度 $\le 2$ 的提前计算好。接下来我们只计算长度 $\ge 3$ 的区间的答案。

考虑 CDQ 分治。

```cpp
void solve(int l, int r) {
  if (r - l + 1 <= 2) return;
  int mid = l + r >> 1;
  solve(l, mid), solve(mid, r);
  // work
}
```

考虑计算左端点在 $[l, mid-1]$，右端点在 $[mid+1,r]$ 的区间的答案。

我们处理出两个数组 $a,b$（$|a|=mid-l,|b|=r-mid$），其中 $a_i = \sum\limits_{j=mid-i+1}^i A_j$，$b_i = \sum\limits_{j=mid+1}^{mid+i} A_j$。即以 $mid$ 为右端点的每一段后缀的和，和以 $mid + 1$ 为左断点的每一段前缀的和。

那么答案显然为 $\sum_{i=1}^{|a|} \sum_{j=1}^{|b|} \Big((a_i+b_j) \bmod M\Big)$。

在计算这个答案前，不妨先将 $a, b$ 中的每个元素对 $M$ 取模。不难发现这并不影响上面答案的计算。

此时 $a_i,b_j < M$。那么必然也有 $a_i+b_j < 2M$。于是：

$$
(a_i + b_j) \bmod M = \begin{cases}
a_i+b_j & a_i+b_j < M \\
a_i+b_j-M & a_i+b_j \ge M
\end{cases}
$$

于是我们可以尝试统计有多少对 $(i, j)$ 满足 $a_i+b_j \ge M$。令其为 $k$。那么答案：

$$
\begin{aligned}
\sum_{i=1}^{|a|} \sum_{j=1}^{|b|} \Big((a_i+b_j) \bmod M\Big) &= \left(\sum_{i=1}^{|a|} \sum_{j=1}^{|b|} (a_i+b_j)\right) - kM \\
&= |b|\sum a_i + |a|\sum b_i - kM
\end{aligned}
$$

于是问题变成了求 $k$。

不妨枚举 $i$。问题变成了求有多少 $j$ 满足 $b_j \ge M - a_i$。我们可以提前对 $b$ 进行排序，然后二分找到最小的这样的 $j$。two-pointers 亦可。

复杂度两只 $\log$。一个是分治，一个是排序。

---

## 作者：卡卡卡卡卡卡 (赞：3)

感觉比 $F$ 难。
## 题解
将 $[1,i]$ 的 $A_i$ 区间模 $m$ 的和规定为 $sum_i$。

考虑到 $[2,i]$ 的 $A_i$ 区间和本质上其实是 $[1,i]$ 的 $sum_i$ 区间和减去 $sum_1$ 模上 $m$。

所以 $[j+1,i]$ 的 $A_i$ 区间和本质上其实是 $[1,i]$ 的 $sum_i$ 区间和减去 $sum_j$ 模上 $m$。

考虑分类讨论：
- 当 $sum_j < sum_i$ 直接减即可。
- 当 $sum_j \geq sum_i$ 时要由负变正，于是加上 $m$。直接减即可。

于是考虑权值线段树，将 $sum_i$ 插入树上，每次枚举 $i$ 表示由 $i$ 为左端点的区间的总和。

记住在枚举完 $i$ 时将 $sum_i$ 删掉，防止出现统计到左端点大于有端点的情况。

## code：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long h,w,k,ans,a[5000005],sum[5000005],tot=1;
struct node
{
	long long lc,rc,maxn;
}tr[50000005];
void insert(long long rt,long long l,long long r,long long p,long long val) 
{
    if(l==r)tr[rt].maxn+=val;
    else 
	{ 
        long long mid=l+r>>1;
        if(p<=mid)
        {
            if(tr[rt].lc==0)tot++,tr[rt].lc=tot;
            insert(tr[rt].lc,l,mid,p,val);
        }
        else 
        {
            if(tr[rt].rc==0)tot++,tr[rt].rc=tot;
            insert(tr[rt].rc,mid+1,r,p,val);
        }
        tr[rt].maxn=tr[tr[rt].lc].maxn+tr[tr[rt].rc].maxn;
    }
}
long long query(long long rt,long long L,long long R,long long l, long long r) 
{
    long long mid=l+r>>1;
    if(L<=l&&R>=r) return tr[rt].maxn;
    else if(L>r||l>R)return 0;
    else return query(tr[rt].lc,L,R,l,mid)+query(tr[rt].rc,L,R,mid+1,r);
}
int main()
{
	long long n,m;
	cin>>n>>m;
	for(long long i=1;i<=n;i++)
	{
		cin>>a[i];
		sum[i]=(sum[i-1]+a[i])%m;
		ans+=sum[i]%m;
		insert(1,0,m-1,sum[i]%m,1);
    } 
	long long tmp=0,res=0;
	res+=ans;
	for(long long i=1;i<=n;i++)
	{
		tmp+=a[i],tmp%=m;
		ans-=sum[i];
		insert(1,0,m-1,sum[i]%m,-1);
		long long q=query(1,0,tmp-1,0,m-1)*m;
		res+=q-tmp*(n-i)+ans;
	}
	cout<<res;
}
```

---

## 作者：qfy123 (赞：3)

# Solution
先推一下式子，记 $s_i$ 表示前 $i$ 项的和（$s_0 = 0$），则有：
$$ 原式 = \sum_{r=1}^n \sum_{l=1}^r (s_r - s_{l-1}) \bmod m$$
考虑如何去掉原式的 $\bmod \ m$。一开始，我们可以在处理前缀和数组的时候对前缀和的每一项都取模得到 $s^{'}_i$。根据减法取模公式：

$$\begin{aligned}(s_r - s_{l-1}) \bmod m &= s^{'}_r - s^{'}_{l-1} + [s^{'}_r - s^{'}_{l-1} < 0] \times m\end{aligned}$$
其中 $[s^{'}_r - s^{'}_{l-1} < 0]$ 表示中括号里条件为真的时候取值为 $1$，否则取值为 $0$。

钦定一个右端点，考虑这个右端点要加多少次 $m$。考虑加 $m$ 的条件 $s^{'}_r - s^{'}_{l-1} < 0$，稍微变形得到 $s^{'}_r < s^{'}_{l-1}$，又因为 $ r > l - 1$，不难发现，这就是[逆序对](https://www.luogu.com.cn/problem/P1908)的形式。所以，对于一个右端点，加 $m$ 的次数就是它所有的左端点与其形成逆序对的总数 $cnt_r$，这是典中典了，树状数组维护即可。

最后整理一下答案的式子：
$$\begin{aligned}原式 &= \sum_{r=1}^n \sum_{l=1}^r s^{'}_r - s^{'}_{l-1} + [s^{'}_r - s^{'}_{l-1} < 0] \times m \\ &= \sum_{r=1}^n(r \times s^{'}_r  - \sum_{l=1}^r s^{'}_{l-1} + cnt_r \times m)\end{aligned}$$

其中 $\sum_{l=1}^r s^{'}_{l-1}$ 可以用二次前缀和 $O(1)$ 地求，注意二次前缀和**不要取模**。
# Code

```cpp
#include<bits/stdc++.h>
#define int long long 
#define ull unsigned long long
#define ri register int
#define rep(i,j,k) for(ri i=(j);i<=(k);++i) 
#define per(i,j,k) for(ri i=(j);i>=(k);--i)
#define repl(i,j,k,l) for(ri i=(j);(k);i=(l))
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define pc(x) putchar(x)
#define fir first
#define se second 
#define MP pair<int,int>
#define PB push_back
#define lson p << 1
#define rson p << 1 | 1
using namespace std;
char BUFFER[100000],*P1(0),*P2(0);
#define gtc() (P1 == P2 && (P2 = (P1 = BUFFER) + fread(BUFFER,1,100000,stdin), P1 == P2) ? EOF : *P1++)
inline int R(){
    int x;char c;bool f = 0;
	while((c = gtc()) < '0') if(c == '-') f = 1;
	x = c ^ '0';
	while((c = gtc()) >= '0') x = (x << 3) + (x << 1) + (c ^ '0');
	return f?(~x + 1):x;
}
inline void O(int x){
    if(x < 0) pc('-'),x = -x;
    if(x < 10) pc(x + '0');
    else O(x / 10),pc(x % 10 + '0');
}
inline void out(int x,int type){
	if(type == 1) O(x),pc(' ');
	if(type == 2) O(x),pc('\n');
	if(type == 3) O(x);
}
inline void OI(){
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
}
const int N = 2e5 + 10;
int n, m, a[N], tr[N], s[N], ss[N];
int lowbit(int x){
	return x & (-x);
}
void mdf(int x, int v){
	++x;
	while(x <= N - 1){
		tr[x] += v;
		x += lowbit(x);
	}
}
int sum(int x){
	++x;
	int ret = 0;
	while(x){
		ret += tr[x];
		x -= lowbit(x);
	}
	return ret;
}
int qry(int l, int r){
	return sum(r) - sum(l - 1);
}
inline void solve(){
	n = R(), m = R();
	rep(i, 1, n) a[i] = R(), s[i] = (s[i - 1] + a[i]) % m;
	rep(i, 1, n) ss[i] = ss[i - 1] + s[i];
	int ans = 0;
	rep(i, 1, n){
		ans += i * s[i] - ss[i - 1] + qry(s[i] + 1, m) * m;
		mdf(s[i], 1);
	}
	out(ans, 2);
}
signed main(){
    // OI();
    int T = 1;
    // T = R();
//     
    // IOS;int T = 1;
    // cin >> T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：__ryp__ (赞：3)

本来不想打 ABC，unr 看了题，很快啊，一眼序列分治！刚好这几天写了一车序列分治板子，于是就整活写了。

题意是：对于所有子区间，求它的区间和模 $P$ 的加和。只对区间和取模，答案不取模。

首先有简单性质：对于两个小于 $P$ 的数，加起来也小于 $2P$。换句话说，把两个模后的数加起来，再取模，最多就减少一个 $P$。

考虑序列分治，那么区间和由在中点左边的后缀和和中点右边的前缀和组成。不妨把所有在中点右边的前缀和存起来，放到 `vector` 里并排序，然后枚举左端点确定后缀和。

由于刚才提到的性质，那么后缀和和前缀和凑成的区间和，要么已经小于 $P$，不再需要取模，要么最多只需要取模一次，也就是减掉一个 $P$。我们二分出第一个需要减去 $P$ 的位置，其左边的直接加起来，右边的加起来，然后减去右边的数量个 $P$。

复杂度 $O(n\log^2n)$。

p.s. 序列分治写起来比树状数组顺手，因此抢了个自己榜上首 A。整活成功。

[submission](https://atcoder.jp/contests/abc378/submissions/59371011)

---

## 作者：linjinkun (赞：2)

式子推导加树状数组区修单查加 ```map``` 的使用。建议评绿。

首先题目给的式子非常的复杂，考虑化简（式子中的 $sum$ 表示前缀和数组）。

$$
\sum_{1 \le l \le r}(\sum_{l \le i \le r}a_i) \bmod m
$$
$$
\sum_{1 \le l \le r}(sum_r-sum_{l-1}) \bmod m
$$
$$
\sum_{1 \le l \le r}(sum_r \bmod m-sum_{l-1} \bmod m+m) \bmod m
$$
推到这里，还是不好求，怎么办呢？

~~凉拌炒鸡蛋。~~

这个时候就要运用到我们的分类讨论了，首先为什么式子中要先加上 $m$ 再取模 $m$ 呢，这里我们先设 $t = sum_r \bmod m-sum_{l-1} \bmod m$，因为可能会出现 $t$ 是负数的情况，那么我们就要分 $t$ 为非负数和 $t$ 为负数的情况才有机会消掉这个烦人的加上 $m$，那么如果 $t$ 是非负数，那么 $t$ 一定小于 $m$，于是就不需要最后的加上 $m$ 再模上 $m$，就是 $sum_r \bmod m-sum_{l-1} \bmod m$，而当 $t$ 是负数时，那么最后的取模 $m$ 就没有任何用处，所以就是 $sum_r \bmod m-sum_{l-1} \bmod m+m$。那么我们就会发现当 $t$ 为非负数和负数的情况他们只相差一个 $m$，所以说，我们拿 $r$ 作右端点，寻找有多少个 $l$，满足 $1 \le l \le r$ 并且 $sum_{l-1}>sum_r$，这里把个数设为 $s$ ，先加上每个都有的 $sum_r \bmod m-sum_{l-1} \bmod m$，再加上 $s$ 个 $m$，完美结束。

再说一下，统计 $s$ 的值，可以使用树状数组，每输入一个数，就使 $[0,a_i-1]$ 这个区间统一加上 $1$，最后每次询问单点查即可。[想知道树状数组如何区间修改单点查询的，戳这里。](https://www.luogu.com.cn/problem/solution/P3368)

**注意事项：**

- 十年 OI 一场空，不开 long long 见祖宗。
- 三年 OI 一场空，树状数组下标从 $0$ 开始见祖宗。（也就是上面说的要统一给这些点和区间加上一，防止下标从 $0$ 开始死循环）
- 还有，由于 $a_i \le 10^9$，数组存不下，只能使用 ```STL``` 杀手，```map```。
- 最后，由于要给区间整体加上 $1$，所以区间右端点最大值变成了 $10^9+1$，而并非 $10^9$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//注意事项1 
const int N = 2e5+5;
const int maxx = 1e9+1;//注意事项4
int sum[N];//前缀和数组
int sum1[N];//这里上面没有特别说明，其实就是求 sum[r] mod m-sum[l-1] mod m 的总和（l-1 可能有多个），于是分开求，就变成了 (sum[r] mod m)*r-(sum[1]+sum[2]+sum[3]+...+sum[r-1])，所以说sum1数组就是前缀和数组的前缀和数组
map<int,int>mp;//注意事项3
signed main()
{
	int ans = 0;
	int n,mod;
	scanf("%lld %lld",&n,&mod);
	for(int i = 1;i<=n;i++)
	{
		int X;
		scanf("%lld",&X);
		sum[i] = (sum[i-1]+X)%mod;//这里要 mod m，因为本身求值就是要 mod m 的
		sum1[i] = sum1[i-1]+sum[i];//求前缀和数组的前缀和数组
		int x = sum[i]+1;//注意事项2，要加上1
		int cnt = 0;
		while(x)
		{
			if(mp.find(x)!=mp.end())
			{
				cnt+=mp[x];
			}
			x-=x&(-x);
		}//cnt就是上面说的s
		ans+=sum[i]*i-sum1[i-1]+cnt*mod;//求和
    	//开始区间加，此时区间为 [1,sum[i]+1]
		x = 1;
		while(x<=maxx)
		{
			mp[x]++;
			x+=x&(-x);
		}
		x = sum[i]+1;
		while(x<=maxx)
		{
			mp[x]--;
			x+=x&(-x);
		}
	}
	printf("%lld",ans);
	return 0;
}
```
求赞！

---

## 作者：dayz_break404 (赞：2)

发现如果只是单一地对于元素来分析答案，是很困难的。不仿从前缀和的角度去考虑答案，考虑枚举左端点 $i$，若当前的前缀和为 $sum_i$，那么如果右端点的前缀和值 $sum_j$ 大于等于 $sum_i$，那么对答案的贡献为 $sum_j-sum_i$；如果小于的话就有 $sum_j+m-sum_i$。相当于是要统计有多少个 $sum_j$ 小于 $sum_i$，用值域树状数组维护统计个数即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x*f;
}
#define ll long long
const int maxn=2e5+20;
ll n,m,a[maxn],sum,tree[maxn],ans;
struct BIT{
	inline int lowbit(int x){
		return x&(-x);
	}
	inline void add(int x,int k){
		for(int i=x;i<=m;i+=lowbit(i)) tree[i]+=k;
	}
	inline int query(int x){
		if(x<0) return 0;
		int ans=0;
		for(int i=x;i;i-=lowbit(i)) ans+=tree[i];
		return ans;
	}
}B;
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read()%m,a[i]=(a[i]+a[i-1])%m,sum+=a[i],B.add(a[i]+1,1);
	for(int i=1;i<=n;i++){
		ans+=sum+1ll*B.query(a[i-1])*m-a[i-1]*(n-i+1);
		B.add(a[i]+1,-1),sum-=a[i];
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：PineappleSummer (赞：2)

简单题。

首先可以对原序列做个前缀和，对于一个区间 $[j+1,i]$，这个区间的和为 $(s_i-s_{j})\bmod m$，考虑将括号拆掉。

- 若 $s_j\bmod m \le s_i\bmod m$，则 $(s_i-s_{j})\bmod m=s_i\bmod m-s_j\bmod m$，可以用 Fenwick Tree 维护一下 $s_j\bmod m$ 之和以及个数。

- 若 $s_j\bmod m > s_i\bmod m$，则 $(s_i-s_{j})\bmod m=s_i\bmod m-s_j\bmod m+m$，同样可以使用 Fenwick Tree 维护，与前一种情况不同的是要加上若干个 $m$。

特别的，需要特判 $s_i\bmod m=0$ 的情况，可以记一个 $tag$ 表示 $s_i\bmod m=0$ 的数量。

时间复杂度 $\mathcal O(n\log m)$。

[参考代码](https://atcoder.jp/contests/abc378/submissions/59430606)

---

## 作者：sherry_lover (赞：1)

# AT_abc378_e [ABC378E] Mod Sigma Problem 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_abc378_e)

## 思路

设 $s_i$ 表示 $\left( \sum\limits_{j=1}^iA_j \right) \mathbin{\mathrm{mod}} M$ 的值，那么原式就可以转化为 $\sum\limits_{1 \le l \le r \le n} (s_r-s_{l-1})$。

展开，得:
$$\sum\limits_{1 \le i \le n}\sum\limits_{0 \le j \le i-1} s_i-s_{j-1}$$

整理可得：
$$\sum\limits_{1 \le i \le n}\left(i \times s_i-\sum\limits_{0 \le j \le i-1} s_j \right)$$

考虑直接减会有什么后果，可以发现如果 $s_j > s_i$ 时就会减成负数，需要加上一个 $m$，用树状数组维护每个 $s_i$ 前有多少个 $s_j > s_i$，然后加上这么多个 $m$ 就行了。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,sum[200005];
long long ans,tot,c[200005];
int lowbit(int x)
{
	return x & -x;
}
void add(int x,int k)
{
  	while(x <= m)
  	{
    	c[x] += k;
    	x += lowbit(x);
  	}
}
long long getsum(int x)
{
  	long long ans = 0;
  	while(x > 0)
	{
   	 	ans += c[x];
    	x -= lowbit(x);
 	}
  	return ans;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for(int i = 1,x;i <= n;i++)
	{
		cin >> x;
		sum[i] = (sum[i-1]+x)%m;
	}
	for(int i = 1;i <= n;i++)
	{
		ans += 1ll*i*sum[i]-tot+(getsum(m)-getsum(sum[i]+1))*m;
		tot += sum[i];
		add(sum[i]+1,1);
	}
	cout << ans;
	return 0;
}
```

---

## 作者：ssine233 (赞：1)

令 $B_i = (\sum_{1 \le j \le i} A_j)\mod M $，则 $(\sum_{l \le i \le r} A_i) \equiv (B_r - B_{l-1}) \mod M $。

分两种情况讨论：

- $B_{l-1}\le B_r$：$(\sum_{l \le i \le r} A_i) \mod M = B_r - B_{l-1}$。
- $B_{l-1}\gt B_r$：$(\sum_{l \le i \le r} A_i) \mod M = M + B_r - B_{l-1}$。

直接用树状数组维护即可。

### 代码


```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const ll N = 2e5 + 10;
const ll M = 1e2 + 10;
ll n, a[N], b[N], f[N], f1[N], MOD, ans;

void upd(ll x, ll y) {
    for (ll i = x; i <= MOD; i += (i) & (-i))
        f[i] += y;
}

ll ask(ll x) {
    ll cn = 0;
    for (ll i = x; i; i -= (i) & (-i))
        cn += f[i];
    return cn;
}

void upd1(ll x) {
    for (ll i = x; i <= MOD; i += (i) & (-i))
        f1[i]++;
}

ll ask1(ll x) {
    ll cn = 0;
    for (ll i = x; i; i -= (i) & (-i))
        cn += f1[i];
    return cn;
}

int main() {
    scanf("%lld%lld", & n, & MOD);
    for (ll i = 1; i <= n; i++) scanf("%lld", & a[i]);
    for (ll i = 1; i <= n; i++) b[i] = b[i - 1] + a[i];
    for (ll i = 1; i <= n; i++) b[i] %= MOD;
    upd1(1);
    for (ll i = 1; i <= n; i++) {
        ll ct1 = ask1(b[i] + 1), ct2 = ask1(MOD) - ask1(b[i] + 1);
        ans += ct1 * b[i] - ask(b[i] + 1) + ct2 * (b[i] + MOD) - (ask(MOD) - ask(b[i] + 1));
        upd(b[i] + 1, b[i]);
        upd1(b[i] + 1);
    }
    printf("%lld", ans);
    return 0;
}
```

---

## 作者：ljy05 (赞：1)

题目让我们求

$$
\sum\limits_{1 \le l \le n} \sum\limits_{1 \le r \le l}\left( \left(\sum\limits_{l \le i \le r} A_i \right) \mod M \right)
$$

首先，求 $l$ 到 $r$ 中 $A_i$ 的和的部分可以使用前缀和改写。设 $sum$ 为 $A$ 的前缀和，$ssum$ 为 $sum$ 的前缀和，公式会变成这样：

$$
\begin{aligned}
ans &= \sum\limits_{1 \le l \le n} \sum\limits_{1 \le r \le l}\left( \left(sum_l - sum_{r-1} \right) \mod M \right)\\
&= \sum\limits_{1 \le l \le n} \left( \left(sum_l \times l - \sum\limits_{1 \le r \le l} sum_{r - 1} \right)\mod M  \right)\\
&= \sum\limits_{1 \le l \le n} \left( \left( \left(sum_l \times l \right) \mod M \right) - \left( ssum_{l - 1} \mod M \right) \right)
\end{aligned}
$$

上面的公式其实有一些问题，因为，举个例子，如果 $X < Y$，那么将 $(X - Y) \mod M$ 化为 $(X \mod M) + (Y \mod M)$ 时，它的值会变小 $M$。

我们需要将这变小的 $M$ 再加回去。对于每一个 $l$，有多少个 $r<l$ 且 $sum_r > sum_l$，就要将答案加多少个 $M$。这可以使用一个树状数组解决。

代码：
```cpp
#include<bits/stdc++.h>
#define ll unsigned long long
using namespace std;
ll a[200010],sum[200010],ssum[200010];
ll c[200010];//树状数组 
ll n,m;
ll ans;//答案 
ll sa;
int lb(int x){//lowbit
	return x&-x;
}
void mdf(int x,ll y){//modify
	for(int i=x;i<=m;i+=lb(i)) c[i]+=y;
}
ll qur(int x){//query
	ll res=0;
	for(int i=x;i>0;i-=lb(i)) res+=c[i];
	return res;
}
int main(){
	scanf("%llu%llu",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%llu",&a[i]);
		sum[i]=(a[i]+sum[i-1])%m;
		ssum[i]=ssum[i-1]+sum[i];
		ans+=sum[i]*i-ssum[i-1]+qur(m-sum[i]-1)*m;//关于这里的query的参数：我们要求大于sum[i]的数的个数，但是query会求小于等于它的。所以要倒着存，下面的modify的参数同理。 
		mdf(m-sum[i],1);
	}
	printf("%llu\n",ans);
	return 0;
}
```

---

## 作者：CCX_CoolMint (赞：1)

首先推一下式子：

我们令 $s_i=\displaystyle \sum_{k=1}^{i}a_k$，将区间和转化成前缀和相减。

$$ 	\begin{align*}
 	 	\displaystyle \sum_{l=1}^{N} \sum_{r=l}^{N} \left( \left ( \sum_{k=l}^{r} a_i \right ) \% M\right )
 	= & \displaystyle \sum_{l=1}^{N} \sum_{r=l}^{N} \left ( \left ( s_r-s_{l-1} \right ) \% M \right )\\
  	= & \displaystyle \sum_{l=1}^{N} \sum_{r=l}^{N} \left ( \left ( \left ( s_r \% M-s_{l-1} \%M \right )+M \right ) \% M \right )
	\end{align*} $$

我们发现这个 $mod$ 实在是令人恼火，所以我们将每个 $s_i$ 都取模以后，可以转化成下面这样：

$$(s_r-s_{l-1}) \% M =\begin{cases} s_r-s_{l-1},s_r \geqslant s_{l-1}\\ s_r-s_{l-1}+M,s_r<s_{l-1}\end{cases}$$

继续推式子，令 $pre_r$ 表示第 $r$ 位之前有多少个位置 $l$ 满足 $s_r<s_{l-1}$，然后我们固定右端点，再维护一个前缀和的前缀和（有点拗口），即 $S_i=\displaystyle\sum_{k=1}^i s_k$，则式子可以转化这样：

$$ 	\begin{align*}
 	 	\displaystyle \sum_{r=1}^{N} \sum_{l=1}^{r} \left ( \left ( s_r-s_{l-1} \right ) \% M \right )
 	= & \displaystyle \sum_{r=1}^{N} \left ( s_r*r-S_{r-1}+pre_r \times M   \right )
	\end{align*} $$

转化到这里就做完了。对于 $pre_i$ 我们可以用树状数组求出。时间复杂度 $O(M+N \log M)$.

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define lowbit(x) x&(-x)
ll n,m,a[1001000],tr[1001000],ans,sum,res;
void upd(ll i){while(i<=m) tr[i]++,i+=lowbit(i);}
ll query(ll i)
{
    ll res=0;
    while(i) res+=tr[i],i-=lowbit(i);
    return res;
}
int main()
{
    cin>>n>>m;
    upd(1);
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        sum+=a[i];
        ans+=sum%m*i+m*(i-query(sum%m+1))-res;
        upd(sum%m+1);
        res+=sum%m;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：Ratio_Y (赞：1)

## 思路

考虑将区间和用前缀和的差表示，那么答案就转化成了所有的前缀和之差的和。

考虑值域线段树，倒序插入前缀和，那么当前插入的前缀和的贡献即为当前线段树上所有点与其的差之和，线段树需要维护区间数量和区间和。简单分成 $\gt x$ 和 $\lt x$ 两种情况，对于 $\lt x$ 的加上一个模数即可，时间复杂度 $\mathcal{O(n\log n)}$。

注意处理边界问题，~~才没有因为这个吃罚时~~。

## 实现

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

inline int qr()
{
    char ch = getchar(); int x = 0, f = 1;
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 3) + (x << 1) + (ch ^ 48);
    return x * f;
}
#define qr qr()

const int Ratio = 0;
const int N = 2e5 + 5;
int n, mod;
ll a[N], ans, sum[N], v[N << 2], num[N << 2];

#define ls (rt << 1)
#define rs (rt << 1 | 1)
#define mid ((l + r) >> 1)
void pushup(int rt)
{
    v[rt] = v[ls] + v[rs];
    num[rt] = num[ls] + num[rs];
}
void upd(int rt, int l, int r, int x)
{
    if(l == r)
    {
        v[rt] += l;
        num[rt]++;
        return ;
    }
    if(x <= mid) upd(ls, l, mid, x);
    else upd(rs, mid + 1, r, x);
    pushup(rt);
}
ll q(int rt, int l, int r, int x, int y)
{
    if(x <= l && r <= y) return v[rt];
    ll res = 0;
    if(x <= mid) res += q(ls, l, mid, x, y);
    if(y > mid) res += q(rs, mid + 1, r, x, y);
    return res;
}
ll qn(int rt, int l, int r, int x, int y)
{
    if(x <= l && r <= y) return num[rt];
    ll res = 0;
    if(x <= mid) res += qn(ls, l, mid, x, y);
    if(y > mid) res += qn(rs, mid + 1, r, x, y);
    return res;
}
signed main()
{
    n = qr, mod = qr;
    for(int i = 1; i <= n; i++)
        a[i] = qr % mod, sum[i] = (sum[i - 1] + a[i]) % mod, ans += sum[i];

    for(int i = n; i; i--)
    {
        if(sum[i]) ans += q(1, 0, mod - 1, 0, sum[i] - 1) + (mod - sum[i]) * qn(1, 0, mod - 1, 0, sum[i] - 1);
        ans += q(1, 0, mod - 1, sum[i], mod - 1) - sum[i] * qn(1, 0, mod - 1, sum[i], mod - 1);
        upd(1, 0, mod - 1, sum[i]);
    }
    printf("%lld\n", ans);
    return Ratio;
}
```



---

完结撒花~

[$Welcome\ to\ my\ blog$](https://www.cnblogs.com/Ratio-Yinyue1007)

---

## 作者：A2_Zenith (赞：0)

挺厉害的一个题。

题目乍一眼看上去没有头绪 ~~（其实更可能是读错题了以为这是个傻子题）~~。

我们考虑对于 $0 \leq c \leq M-1$，对 $(\sum\limits_{i=l}^ra_i) \bmod M = c$ 的 $[l,r]$ 计数。

发现我们并不需要显式地维护这个 $\bmod M = c$ 的 $[l,r]$ 的数量。

我们不妨枚举我们子段的右端点 $r$，在右移 $r$ 的过程中把这个答案算了，与此同时维护 $cnt_x$ 表示 $a$ 的前缀和数组 $s_i(0 \leq i < r)$ 中有多少个数模 $M$ 为 $x$。

此时，对于 $j\leq s_r$，这些子段对答案产生了 $(s_r-j)cnt_j$ 的贡献。

对于 $j > s_r$，这些子段对答案产生了 $(s_r-j+M)cnt_j$ 的贡献。

注意到，我们要实时维护一个多重集，支持插入一个数，查询多重集内某个数出现的次数与某个数出现的次数乘这个数（对应 $cnt_x$ 与 $x \times cnt_x$），同时要支持询问对于数 $x$ 有多少个数大于它。使用树状数组即可。

代码中有比较详细的解释（可能吧）。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int lb(int x){return x&(-x);}
const int maxn=5e5+7;
int n,m;
int s[maxn];
int t1[maxn],t2[maxn];//t1 维护 cnt[x],t2 维护 cnt[x]*x。
inline void Add1(int x,int dt){
	for(int i=x;i<=m;i+=lb(i))t1[i]+=dt;
} 
inline void Add2(int x,int dt){
	for(int i=x;i<=m;i+=lb(i))t2[i]+=dt;
}
inline int Qry1(int x){
	int ans=0;
	for(int i=x;i;i-=lb(i))ans+=t1[i];
	return ans;
}
inline int Qry2(int x){
	int ans=0;
	for(int i=x;i;i-=lb(i))ans+=t2[i];
	return ans;
}
inline void Ins(int x){
	Add1(x,1);Add2(x,x);
}//往多重集中加数
inline int Chk1(){
	return Qry2(m);
}//注意到无论是j <= s[r] 还是 j > s[r],对于答案都有 -j*cnt[j] 的贡献，所以其实查的是全局的 j*cnt[j] 之和。
inline int Chk2(int x){
	return Qry1(m)-Qry1(x);
}//计算多重集中有多少个数大于 x，以计算 j > s[r] 时 M 的贡献。
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>s[i],(s[i]+=s[i-1])%=m;
	for(int i=0;i<=n;i++)s[i]++;
	Ins(s[0]);
	int ans=0;
	for(int i=1;i<=n;i++){
		ans=(ans+i*s[i]-Chk1()+Chk2(s[i])*m);
		Ins(s[i]);
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Your_Name (赞：0)

## 题意
求
$$
 \sum_{1 \leq l \leq r \leq N} \left( \left(\sum_{l \leq i \leq r} A_i\right) \mathbin{\mathrm{mod}} M \right). 
$$
## 题解
思路比较明显。

发现每段的和可以看做前缀和数组两数之差，那么原式就转化为：
$$
 \sum_{1 \leq l \leq r \leq N} \left( \left(sum_r-sum_{l-1}\right) \mathbin{\mathrm{mod}} M \right). 
$$
对于同一个 $r$，我们再把后面的式子拆开：
$$
(sum_r-sum_0)\bmod m+(sum_r-sum_1)\bmod m+...+(sum_r-sum_{r-1})\bmod m
$$
变形一下可得
$$
(sum_r \bmod m)\times r - \sum_{l=0}^{r-1}sum_l\bmod m
$$
但是有个问题：

我们来看这个式子：$(6-3)\bmod  4$。

如果我们把它拆开的话就是 $6\bmod 4 -3\bmod 4$。

发现他不等于原式，而要加一个 $4$，也就是模数。

进一步观察，发现在 $(a-b)\bmod m$ 时只有 $a \bmod m< b\bmod m$ 时才要加，所以我们用树状数组维护一下有几个大于它再加上这么多个 $m$ 即可。
## AC_Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 2e5 + 10;
LL n, m, sum[N], summ[N], ans, c[N];
LL lowbit(int x){
    return x & (- x);
}
void add(LL x, LL y){
    while(x <= m){
        c[x] += y;
        x += lowbit(x);
    }
}
LL ask(LL x){
    LL ans = 0;
    while(x){
        ans += c[x];
        x -= lowbit(x);
    }
    return ans;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    add(1, 1);//因为要减sum_0
    for(LL i = 1; i <= n; i ++){
        cin >> sum[i];
        sum[i] += sum[i - 1];//前缀和。
        ans += (sum[i] % m) * i - summ[i - 1] + (i - ask(sum[i] % m + 1)) * m;//上式。
        summ[i] = summ[i - 1] + sum[i] % m;//前面sum%m的和。
        add((sum[i] % m) + 1, 1);//树状数组不能为0所以加1。
    }
    cout << ans;
    return 0;
}
```
 _完结撒花_ 。

---

## 作者：zhouruoheng (赞：0)

要推一下式子：

设 $S_i = (A_1+A_2+\dots+A_i) \mathbin{\mathrm{mod}} M$，就有：

$$
 \sum_{1 \leq l \leq r \leq N} \left( \left(\sum_{l \leq i \leq r} A_i\right) \mathbin{\mathrm{mod}} M \right) = \sum_{1 \leq l \leq r \leq N} (S_r - S_{l-1}) \mathbin{\mathrm{mod}} M 
$$

然后因为 $0 \leq S_{l-1},S_r < M$，所以

$$
 (S_r - S_{l-1}) \mathbin{\mathrm{mod}} M = S_r - S_{l-1} + \begin{cases} 0 & (S_{l-1} \leq S_r) \\ M & (S_{l-1} > S_r)\end{cases} 
$$

这样就去掉了取模。

设 $X_r$ 为在 $S_0$ 到 $S_{r-1}$ 中大于 $S_r$ 的数的个数。所以：

$$
 \sum_{r=1}^n \sum_{l=1}^r (S_r - S_{l-1}) \mathbin{\mathrm{mod}} M = \sum_{r=1}^N \left( S_r \times r - \sum_{l=1}^r S_{l-1} + M \times X_r \right). 
$$

那么问题就是对于 $X_r$ 的维护，可以用权值线段数组，单调修改，区间查询。  
要注意 $S_i$ 可以等于 $0$，所以要么加上偏移量，要么特判一下。

``` cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <map>

using namespace std;
typedef long long ll;
const int N=2e5+5;
int n,m;
ll a[N],b[N],c[N];
int lowbit(int x) 
{
    return x&-x;
}
void add(int k,int x)
{
    if(!k) return ;
    for(int i=k;i<=m;i+=lowbit(i)) c[i]+=x;
}
ll query(int k)
{
    ll ret=0;
    for(int i=k;i;i-=lowbit(i)) ret+=c[i];
    return ret;
}
void solve()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i],b[i]=b[i-1]+a[i];
    for(int i=1;i<=n;i++) b[i]%=m;
    ll ans=0,s=0;
    for(int i=1;i<=n;i++)
    {
        ans+=b[i]*i-s+(query(m)-query(b[i]))*m;
        s+=b[i];
        add(b[i],1);
    }
    cout<<ans<<'\n';
}
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    #endif 
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    solve();
    return 0;
}


```

---

## 作者：_smart_stupid_ (赞：0)

[题目](https://atcoder.jp/contests/abc378/tasks/abc378_e)

题目简述：给定一个 $n, m$，一个数组 $a$，求 $\sum\limits_{l=1}^n\sum\limits_{r=l+1}^n((\sum\limits_{i=l}^ra_i) \mod m)$

它实际上是一个偏序问题。

首先，让我们用 $s_i$ 表示从 $a_1$ 到 $a_i$ 的和模上 $m$，问题转化为求这个：

$$
\sum\limits_{l=1}^n\sum\limits_{r=l+1}^n((s_r-s_{l-1})\mod m)
$$

我们发现：$s_i$ 是某个数模 $m$ 的结果，必然大于 $0$，小于 $m$。所以 $(s_r-s_{l-1})\mod m$ 要么为 $s_r-s_{l-1}$，要么为 $s_r-s_{l-1}+m$，取决于 $s_r$ 和 $s_{l-1}$ 的大小关系。

那么我们先求出这个：
$$
\sum\limits_{l=1}^n\sum\limits_{r=l+1}^ns_r-s_{l-1}
$$
然后对于每一个 $s_i$ 只要求出 **严格小于它** 的 $s_j$ 个数就可以快速求出到底上面这个式子少算了多少个 $m$ 了。

现在求的是这个：

对于每一个 $s_i$，求出 $j>i,s_j < s_i$ 的 $s_j$ 的个数。

于是问题就转化为了一个偏序问题。

## AC Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, a[200100];
long long ans;
struct node{
	int idx;
	long long val;
};
node sum[200100];
bool cmp(node a, node b) {
	return a.val < b.val;
}
int t[200100];
void add(int i, int x) {
	while (i <= n + 3) {
		t[i] += x;
		i += (i & -i);
	}
}
int get(int i) {
	int ans = 0;
	while (i) {
		ans += t[i];
		i -= (i & -i);
	}
	return ans;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		sum[i].val = (sum[i - 1].val + a[i]) % m;
		sum[i].idx = i;
	}
	long long s1 = 0;
	for (int i = n; i >= 0; i--) {
		s1 += sum[i + 1].val, ans += s1 - sum[i].val * (n - i);
	}
	sort(sum + 1, sum + n + 1, cmp);
	int last = 1;
	for (int i = 1; i <= n; i++) {
		if (sum[i].val > sum[i - 1].val) {
			while (last < i) {
				add(sum[last].idx, 1);
				last++;
			}
		}
		ans += (long long)(get(n) - get(sum[i].idx)) * m;
	}
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：Heldivis (赞：0)

## [ABC378E] Mod Sigma Problem

题意让求：
$$\sum_{1 \leq l \leq r \leq N} \left( \left(\sum_{l \leq i \leq r} A_i\right) \bmod M \right) $$

其中 $1\le N,M\le2\times10^5$。

考虑如果没有取模，一个区间的和是 $s_R-s_{L-1}$（其中 $s$ 是前缀和），将右端点为 $i$ 的区间统一计算，则答案为：

$$
\sum_{i=1}^{n}i\times s_i-S_i
$$

其中 $S_i$ 是前缀和的前缀和。

加上取模，区间和是 $(s_R-s_{L-1}+M)\bmod M$，考虑按 $s_R$ 和 $s_{L-1}$ 的大小分类讨论。

- $s_R\ge s_{L_R}$，答案为 $s_R-s_{L-1}$。
- $s_R\lt s_{L_R}$，答案为 $s_R-s_{L-1}+M$。

考虑将这两类分开维护，记类型一的个数为 $C_1$，和为 $S_1$；类型二的个数为 $C_2$，和为 $S_2$，答案为 $C_1\times s_i-S_1+S_2-C_2\times s_i$，由于每次的 $s_i$ 不同，使用数据结构维护前后缀的和、计数即可。时间复杂度 $O(n\log m)$。

代码：[赛时提交记录](https://atcoder.jp/contests/abc378/submissions/59371360)，记得开 `long long`。

---

## 作者：under_the_time (赞：0)

## 题意

> 给定一个长度为 $n$ 的序列 $a$，和一个正整数 $P$，求：
> $$
> \sum_{l=1}^n\sum_{r=l}^n\left(\left(\sum_{i=l}^r a_i\right)\bmod P\right)
> $$
> 注意取模操作**只发生在求区间和**而不是求区间和的和。
>
> $1\le P,n\le 2\times 10^5$，$0\le a_i\le 10^9$。

## 题意

若没有或全都取模，那么对于 $a_i$ 它被统计的次数即为 $i\times (n-i+1)\times a_i$，当然这个式子在本题中基本没有用。我们考虑对 $a$ 求一个前缀和，记为 $s$，那么式子可以变为：
$$
\sum_{l=1}^n\sum_{r=l}^n(\left(s_r-s_{l-1}\right)\bmod P)
$$
若我们对 $s_i$ 都提前对 $P$ 取模，那么显然有 $-P<s_r-s_{l-1}<P$，就有：
$$
(s_r-s_{l-1})\bmod P=\begin{cases}s_r-s_{l-1}&\text{ if }s_r-s_{l-1}\ge0\\s_r-s_{l-1}+P&\text{ if }s_r-s_{l-1}<0\end{cases}
$$


我们可以这样考虑：拿取模后的 $s$ 算 $\sum_{1\le l\le r\le n}s_r-s_{l-1}$，即把 $\bmod P$ 先去掉，然后再补上若干个 $+P$。前者我们对 $s$ 再求一个前缀和，记为 $s'$，那么前者可以转化为：
$$
\sum_{r=1}^n s_r\times r-s'_{r-1}
$$
由之前的推到可得，$s_r-s_{l-1}$ 需要加上一个 $P$ 当且仅当 $s_r-s_{l-1}<0$ 即 $s_r<s_{l-1}$，$l$ 最多取到 $r$，那么问题就变成了求 $s$ 逆序对的数量，权值树状数组即可，最后数量乘上 $P$ 加到上一个式子即为答案。注意取模后 $s_i\in[0,P-1]$ 所以放进树状数组时下标要加一。

## 代码

```cpp
// Problem: E - Mod Sigma Problem
// Contest: AtCoder - AtCoder Beginner Contest 378
// URL: https://atcoder.jp/contests/abc378/tasks/abc378_e
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Good luck to the code >w<
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define open(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout)
#define abs(x) (((x) > (0)) ? (x) : (-(x)))
#define lowbit(x) ((x) & (-(x)))
#define lson l, mid, rt << 1
#define rson mid + 1, r, rt << 1 | 1
#define BCNT __builtin_popcount
#define cost_time (1e3 * clock() / CLOCKS_PER_SEC)
mt19937 rnd(time(0));
const int maxn = 2e5 + 5;
int n, P; ll a[maxn];
namespace BIT {
	int b[maxn];
	void add(int x) {
		for (; x <= P; x += lowbit(x))
			b[x] ++;
	} int query(int x) {
		int res = 0;
		for (; x; x -= lowbit(x))
			res += b[x];
		return res;
	}
} using namespace BIT;
int main() {
	scanf("%d %d", &n, &P); ll ans = 0;
	for (int i = 1; i <= n; i ++)
		scanf("%lld", &a[i]), a[i] = (a[i - 1] + a[i]) % P;
	ll dt = 0;
	for (int i = 1; i <= n; i ++) 
		ans += a[i] * i - dt, dt += a[i];
	for (int i = 1; i <= n; i ++) {
		ans += 1ll * (query(P) - query(a[i] + 1)) * P;
		add(a[i] + 1);
	} printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Daniel_yao (赞：0)

发现可以拆贡献的方式：

 $$
 \sum\limits_{l=1}^n \sum\limits_{r=l}^n (\sum\limits_{l\le k\le r} a_k) \bmod m
 $$
 
然后算出 $a_i$ 的前缀和 $sum_i$。

$$
\begin{aligned}
&\sum\limits_{l=1}^n \sum\limits_{r=l}^n (sum_r-sum_{l-1}) \bmod m\\
&\sum\limits_{l=1}^n \sum\limits_{r=l}^n (sum_r\bmod m-sum_{l-1}\bmod m+[sum_r < sum_{l-1}] \times m)
&
\end{aligned}
$$

然后就很简单了，记录 $sum_i \bmod m$ 的后缀和 $s_i$，记录 $b_i$ 为所有 $>sum_{i-1}$ 的 $sum_j(j\ge i)$ 的个数。

前者 $O(n)$ 扫一遍，后者用树状数组 $O(n\log n)$ 统计即可。

最后答案为：$\sum\limits_{i=1}^n s_i - (n-i+1)\times (sum_{i-1}\bmod m)+b_{i-1}\times m$。

总时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,l,r) for(int i=l;i<=r;++i)
#define FOR(i,r,l) for(int i=r;i>=l;--i)

using namespace std;

const int N = 1e6 + 10;

int n, m, a[N], sum[N], s[N], ans, b[N], t[N];

int lb(int x) {
  return x & -x;
}

int qry(int x) {
  if(x <= 0) return 0;
  int res = 0;
  for (int i = x; i; i -= lb(i)) {
    res += t[i];
  }
  return res;
}

void add(int x, int k) {
  for (int i = x; i <= 2e5; i += lb(i)) {
    t[i] += k;
  }
  return ;
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> m;
  For(i,1,n) cin >> a[i], sum[i] = sum[i-1] + a[i];
  FOR(i,n,1) {
    add(sum[i] % m + 1, 1);
    b[i-1] = qry((sum[i-1] % m));
  }
  FOR(i,n,1) {
    s[i] = s[i+1] + sum[i] % m;
  }
  For(i,1,n) {
    int len = n - i + 1;
    ans += (s[i] - len * (sum[i-1] % m) + b[i-1] * m);
  }
  cout << ans << '\n';
  return 0;
}
```

---

## 作者：liuziqin (赞：0)

## 思路

由于 $m \le 2 \times 10^5$，因此时间复杂度可以和 $m$ 挂钩。

我们设 $S_i=(\sum_{j\le i}A_j)\mod m$，因此原式就可以表示为 
$$
\sum_{l=1}^n\sum_{r=l}^n((S_r-S_{l-1})\mod m)
$$ 
对这个式子变形可得 
$$
\sum_{i=1}^n(\sum_{j=1}^{i-1}((S_i-S_j)\mod m)+S_i)
$$ 
接下来对 $(S_i-S_j)\mod m$ 进行分类讨论。

如果 $S_i-S_j \ge 0$，则 $(S_i-S_j)\mod m=S_i-S_j$。

否则 $(S_i-S_j)\mod m=S_i-S_j+m$。

因此我们在统计答案时仅需加上 $\ge S_i$ 的所有 $S_j$ 少算的贡献即可，这可以用**线段树**进行维护。

## Code
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=200005;
struct segtree{
	int sum[N<<2];
	void pushup(int p){
		sum[p]=sum[p*2]+sum[p*2+1];
	}
	void add(int p,int l,int r,int x,int v){
		if(l==r){
			sum[p]+=v;
			return ;
		}
		int mid=(l+r)>>1;
		if(mid>=x)add(p*2,l,mid,x,v);
		else add(p*2+1,mid+1,r,x,v);
		pushup(p);
	}
	int query(int p,int l,int r,int x,int y){
		if(x>y)return 0;
		if(l>=x&&r<=y)return sum[p];
		int mid=(l+r)>>1,ans=0;
		if(mid>=x)ans+=query(p*2,l,mid,x,y);
		if(mid<y)ans+=query(p*2+1,mid+1,r,x,y);
		return ans;
	}
}st;//线段树
int n,mod;
int a[N],sum[N];
signed main(){
	cin>>n>>mod;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum[i]=(sum[i-1]+a[i])%mod;//预处理Si
	}
	int ans=0,val=0;
	for(int i=1;i<=n;i++){
		int cost=st.query(1,0,mod-1,sum[i]+1,mod-1);
		ans+=i*sum[i]-val+cost*mod;//计算贡献
		val+=sum[i];//求出所有的Sj的总和
		st.add(1,0,mod-1,sum[i],1);
	}
	cout<<ans<<"\n";//输出
	return 0;
}
```

---

## 作者：bryce (赞：0)

## [E - Mod Sigma Problem](https://atcoder.jp/contests/abc378/tasks/abc378_e)
### 思路
将题目要求的东西转化一下，转化为求以下的式子：

$$\sum\limits_{1\le l\le r\le n} (sum_r - sum_{l - 1})\mod m$$

其中 $sum_i$ 表示 $1$ 到 $i$ 之间的 $a_i$ 的和，即前缀和。

由于有一个模 $m$，不好做，尝试再转化一下：

$$\sum\limits_{1\le l\le r\le n} ((sum_r\mod m) - (sum_{l - 1}\mod m))$$

但是这一步的转化是错的，因为 $sum_r\mod m$ 可能比 $sum_{l - 1}\mod m$ 小，相减会出现负数，而原来的计算不会出现负数，这时答案要加上一个 $m$，所以对于一个 $r$，在 $0\le l - 1\lt r$ 中，大于 $sum_r\mod m$ 的 $sum_{l - 1}\mod m$ 计算时都要加上 $m$，用树状数组统计有多少个这样的 $l - 1$，记为 $X_r$，即为加上总的 $m$ 的个数。对每个 $sum_i$ 先对 $m$ 取模，于是式子变成这样：

$$\sum\limits_{1\le r\le n} (sum_r\times r - \sum\limits_{1\le l\le r} sum_{l - 1} + X_r\times m)$$

其中，$\sum\limits_{1\le l\le r} sum_{l - 1}$ 可以直接求，$X_r$ 用树状数组求。
### 代码
```cpp
#include<iostream>
#define int long long

using namespace std;

inline int read(){register int x = 0, f = 1;register char c = getchar();while (c < '0' || c > '9'){if (c == '-') f = -1;c = getchar();}while (c >= '0' && c <= '9'){x = (x << 1) + (x << 3) + (c ^ 48);c = getchar();}return x * f;}

const int N = 2e5 + 10;
int n, m, ans;
int a[N], sum[N];
int t[N];
int lowbit(int x){
    return x & -x;
}
void add(int x, int k){
    for (int i = x; i <= m; i += lowbit(i)) t[i] += k;
}
int query(int x){
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) res += t[i];
    return res;
}

signed main(){
    n = read(), m = read();
    for (int i = 1; i <= n; i++) a[i] = read();
    for (int i = 1; i <= n; i++) sum[i] = (sum[i - 1] + a[i]) % m;
    int res = 0;
    for (int i = 1; i <= n; i++){
        ans += sum[i] * i - res + m * (query(m) - query(sum[i] + 1));
        res += sum[i];
        add(sum[i] + 1, 1);
    }
    cout << ans;
    return 0;
}
```

---

## 作者：xixisuper (赞：0)

# AT_abc378_e [ABC378E] Mod Sigma Problem 题解

怎么都用树状数组做的，来一发不需要数据结构的做法。

## 思路

简化题意：

> 给定一个长度为 $n$ 的数列 $a$，定义某个区间的价值为**这个区间的和对 $m$ 取模后的结果**，你需要输出这个序列所有区间的**价值之和**。注意，**最终答案不需要对 $m$ 取模**。

注意到题目是对所有区间价值求和，而求所有区间价值之和有两个经典套路。其一是枚举右端点，然后把区间要维护的信息丢到左端点上，用数据结构去维护；其二是考虑分治，本题解采用分治算法。

对于某个数列来说，我们可以把整个数列分成两半部分 $[1,mid],[mid+1,n]$，对于任意一个区间来说，要么其完全在左半区间，要么其完全在右半区间，要么其跨过左右两半，不难发现我们只需要考虑跨左右两半的那些区间的贡献，剩下两种直接递归进行计算即可。

所以我们可以把我们需要统计的区间分成左右两半，一半是 $[l,mid]$，另一半是 $[mid+1,r]$。我们考虑预处理出所有的 $[mid+1,r]$ 的和对 $m$ 取模，并且从小到大排序。然后枚举左端点 $l$，不难发现左半区间和右半区间的和都是小于 $m$ 的，所以加在一起一定小于 $2m$，我们可以二分出加起来正好大于等于 $m$ 的那个位置，然后分别统计答案即可。

归到时间复杂度分析，由于计算时我们既要排序还要二分，所以单次统计是 $O(n\log n)$ 的时间复杂度，故递归时间复杂度满足如下式子：

$$
T(n)=2\times T\left(\frac{n}{2}\right)+O(n\log n)
$$

根据主定理分析，我们可以知道上述算法时间复杂度为 $O(n\log^2n)$，可以通过此题。

## 代码

```cpp
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const ll N=2e5+10;
ll n,m,a[N],ans,sum[N],erch[N];
void solve(ll L,ll R){
	if(L==R){
		ans+=a[L];
		return;
	}
	ll mid=(L+R)>>1;
	solve(L,mid);solve(mid+1,R);
	
	for(ll i=mid+1;i<=R;i++) sum[i]=0;
	sum[mid+1]=a[mid+1]%m;
	
	for(ll i=mid+2;i<=R;i++) sum[i]=(sum[i-1]+a[i])%m;
	sort(sum+mid+1,sum+R+1);
	
	erch[mid+1]=sum[mid+1];
	for(ll i=mid+2;i<=R;i++) erch[i]=erch[i-1]+sum[i];
	
	ll pre_sum=0;
	for(ll i=mid;i>=L;i--){
		pre_sum=(pre_sum+a[i])%m;
		ll pos=lower_bound(sum+mid+1,sum+R+1,m-pre_sum)-sum-1;
		ans+=erch[pos]+pre_sum*(pos-mid);
		ans+=erch[R]-erch[pos]+pre_sum*(R-pos)-(R-pos)*m;
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(ll i=1;i<=n;i++){
		cin>>a[i];
		a[i]%=m;
	}
	solve(1,n);
	cout<<ans;
	return 0;
} 
```

---

## 作者：Binah_cyc (赞：0)

提供一个十分麻烦的赛时做法。

变量声明：$sum$ 为前缀和数组，$ssum$ 为前缀和数组的前缀和数组，$msum$ 为 $\lfloor {sum \over m} \rfloor $ 的前缀和数组。

$$\begin{aligned}
 &\sum_{1 \leq l \leq r \leq n} \left( (\sum_{l \leq i \leq r} A_i) \bmod m \right)\\
 =&\sum_{1 \leq l \leq r \leq n} (sum_r-sum_{l-1}) \bmod m\\
 =&\sum_{1 \leq l \leq r \leq n} sum_r-sum_{l-1}-\lfloor {sum_r-sum_{l-1} \over m}\rfloor \times m\\
 =&\sum_{1 \leq l \leq r \leq n} (sum_r-sum_{l-1})-\sum_{1 \leq l \leq r \leq n} \lfloor {sum_r-sum_{l-1} \over m}\rfloor \times m\\
 =&\sum_{1 \leq l \leq n} (ssum_n- ssum_{l-1}-(n-l+1) \times sum_{l-1}) -\sum_{1 \leq l \leq r \leq n}  \lfloor {sum_r-sum_{l-1} \over m}\rfloor \times m
\end{aligned}$$

很明显，左边那一坨我们可以通过枚举 $l$ 以 $O(n)$ 的复杂度计算出来，因此计算重点放在了右面那一坨上面。

注意到 $\lfloor {a-b \over m} \rfloor= \lfloor {a \over m} \rfloor - \lfloor {b \over m} \rfloor - [a \bmod m < b \bmod m]$，其中方括号为艾弗森括号。

我们可以将右面的式子继续化简

$$\begin{aligned}
&\sum_{1 \leq l \leq n} (ssum_n- ssum_{l-1}-(n-l+1) \times sum_{l-1}) -\sum_{1 \leq l \leq r \leq n} \lfloor {sum_r-sum_{l-1} \over m}\rfloor \times m\\
=&\sum_{1 \leq l \leq n} (ssum_n- ssum_{l-1}-(n-l+1) \times sum_{l-1}) -\sum_{1 \leq l \leq r \leq n} \lfloor {sum_r \over m} \rfloor - \lfloor {sum_{l-1}\over m} \rfloor - [sum_r \bmod m < sum_{l-1} \bmod m]\\
=&\sum_{1 \leq l \leq n} (ssum_n- ssum_{l-1}-(n-l+1) \times sum_{l-1}) -\sum_{1 \leq l \leq r \leq n} (\lfloor {sum_r \over m} \rfloor - \lfloor {sum_{l-1}\over m} \rfloor )- \sum_{1 \leq l \leq r \leq n}  [sum_r \bmod m < sum_{l-1} \bmod m]\\
=&\sum_{1 \leq l \leq n} (ssum_n- ssum_{l-1}-(n-l+1) \times sum_{l-1}) -\sum_{1 \leq l \leq n} (msum_n-msum_{l-1}-(n-l+1)\times \lfloor {sum_{l-1}\over m}\rfloor)-\sum_{1 \leq l \leq r \leq n} [sum_r \bmod m < sum_{l-1} \bmod m]&\end{aligned} $$

至此，问题就转化为统计 $[l,n]$ 区间内小于 $sum_{l-1} \bmod m$  的值的个数了，可以使用主席树在线 $O(\log n)$ 的维护，总复杂度为 $O(n \log n)$，瓶颈在主席树。

代码：
```
// Problem: E - Mod Sigma Problem
// Contest: AtCoder - AtCoder Beginner Contest 378
// URL: https://atcoder.jp/contests/abc378/tasks/abc378_e
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Author: Binah_cyc

#include<bits/stdc++.h>
using namespace std;
constexpr int N=2e5+5;
#define int long long
int n,m,ans,a[N],sum[N],sumsum[N],summod[N];
int stot,root[N];
struct SegmentTree
{
	int ls,rs;
	int sum;
}t[N*20];
int make(){return ++stot;}
void pushup(int p){t[p].sum=t[t[p].ls].sum+t[t[p].rs].sum;}
int change(int tl,int tr,int l,int r,int p)
{
	int now=make();
	t[now]=t[p];
	if(l<=tl&&tr<=r) return t[now].sum++,now;
	int mid=(tl+tr)>>1;
	if(l<=mid) t[now].ls=change(tl,mid,l,r,t[p].ls);
	if(r>mid)  t[now].rs=change(mid+1,tr,l,r,t[p].rs);
	pushup(now);
	return now;
}
void ask(int tl,int tr,int p)
{
	if(!p) return ;
	cout<<tl<<' '<<tr<<' '<<t[p].sum<<endl;
	if(tl==tr) return ;
	int mid=(tl+tr)>>1;
	ask(tl,mid,t[p].ls),ask(mid+1,tr,t[p].rs);
}
int ask(int tl,int tr,int l,int r,int p)
{
	if(l>r) return 0;
	if(!p) return 0;
	if(l<=tl&&tr<=r) return t[p].sum;
	int mid=(tl+tr)>>1,cnt=0;
	if(l<=mid) cnt+=ask(tl,mid,l,r,t[p].ls);
	if(r>mid)  cnt+=ask(mid+1,tr,l,r,t[p].rs);
	return cnt;
}
int ask(int l,int r){return ask(0,n,0,l-1,root[r])-ask(0,n,0,l-1,root[l-1]);}
signed main(signed argc,char** argv)
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i],a[i]%=m,sum[i]=sum[i-1]+a[i];
	for(int i=1;i<=n;i++) sumsum[i]=sumsum[i-1]+sum[i],summod[i]=summod[i-1]+sum[i]/m;
	for(int i=1;i<=n;i++) root[i]=change(0,m-1,sum[i]%m,sum[i]%m,root[i-1]);
	for(int i=1;i<=n;i++)
	{
		int lst=ans;
		ans+=sumsum[n]-sumsum[i-1]-(n-i+1)*sum[i-1];
		ans-=m*(summod[n]-summod[i-1]-(n-i+1)*(sum[i-1]/m)-(ask(0,m-1,0,sum[i-1]%m-1,root[n])-ask(0,m-1,0,sum[i-1]%m-1,root[i-1])));
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：xiezheyuan (赞：0)

## 简要题意

给定一个长度为 $n$ 的序列 $a$，你需要求出所有区间的和对 $M$ 取模后的结果的和。注意最后一步不能取模。

$1\leq n\leq 2\times 10^5$。

## 思路

首先考虑我们让最后一步可以取模该怎么做，可以枚举区间的右端点 $i$，维护前缀和 $A_i$，则以 $i$ 为右端点的所有区间的和为：

$$
A_i\cdot i-\sum_{k=1}^{i-1}A_k
$$

直接算就好了，记得边加边取模。时间复杂度 $O(n)$。

考虑原问题我们怎么做，还是考虑每一个区间 $[l,r]$，那么它的和为 $A_r-A_{l-1}$。我们统计 $A$ 的时候取模，在最后累加的时候不取模是不行的，因为这样的减法可能减出负数，我们可以把所有 $A_{l-1}>A_r$ 的改成 $A_{r}-A_{l-1}+M$，容易发现这样就没有负数了。

现在我们需要维护一个数据结构，支持插入一个数，查询有多少个数比指定的一个数大（有多少个数比它大，就要补偿多少个 $M$），平衡树就可以维护。时间复杂度 $O(n\log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 5;
int n, m, a[N];
__gnu_pbds::tree<pair<int,int>, __gnu_pbds::null_type, less<pair<int,int>>, __gnu_pbds::rb_tree_tag,  __gnu_pbds::tree_order_statistics_node_update> t;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        a[i] = (a[i - 1] + a[i]) % m;
        // cerr << a[i] << ' ';
    }
    // cerr << '\n';
    int pre = 0, ans = 0;
    for(int i=1;i<=n;i++){
        int x = t.order_of_key({-a[i], 0});
        ans += (a[i] * i - pre + m * x);
        // cerr << a[i] * i << ' ' << pre << ' ' << m * x << '\n';
        pre += a[i];
        t.insert({-a[i], i});
    }
    cout << ans << '\n';
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：zcz0263 (赞：0)

## 题意
求 $\sum\limits_{l=1}^n \sum\limits_{r=l}^n \left( \left(\sum\limits_{i=l}^r A_i\right) \bmod M \right)$。
## 做法
考虑令 $s_i=\sum\limits_{j=1}^{i-1}a_i=s_{i-1}+a_i$，$S_i=\sum\limits_{j=1}^{i-1}(s_i\bmod M)=(S_{i-1}+s_i\bmod M)$，则题面式子可得：
$$\begin{aligned}
&=\sum\limits_{l=1}^n \sum\limits_{r=l}^n ((s_r-s_{l-1}) \bmod M)\\
&=\sum\limits_{r=1}^n \sum\limits_{l=0}^{r-1}((s_r-s_l) \bmod M )\\
&=\sum\limits_{r=1}^n \sum\limits_{l=0}^{r-1}((s_r\bmod M-s_l\bmod M)+[(s_r\bmod M-s_l\bmod M)<0]M)\\
&=\sum\limits_{r=1}^n ((s_r\bmod M-
\sum\limits_{l=0}^{r-1}(s_l\bmod M))+(\sum\limits_{l=0}^{r-1}[s_r\bmod M<s_l\bmod M])M)\\
&=\sum\limits_{r=1}^n ((s_r\bmod M-S_{r-1})+\sum\limits_{l=0}^{r-1}[s_r\bmod M<s_l\bmod M]M)\\
\end{aligned}$$
然后发现 $\sum\limits_{l=0}^{r-1}[s_r\bmod M<s_l\bmod M]$ 这个东西是个二维偏序，用权值树状数组维护即可做到 $O(n\log n)$。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define vi vector<int>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
int n,m,sum,ans;
#define N 200015
vi a(N),s(N),c1(N);
#define lowbit(p) ((p)&-(p))
void add(vi&c,int p,int x){
    for(p+=2;p<N;p+=lowbit(p)){
        c[p]+=x;
    }
}
int ask(vi&c,int p){
    int ret=0;
    for(p+=2;p;p-=lowbit(p)) ret+=c[p];
    return ret;
}
int ask(vi&c,int l,int r){
    if(r<l) return 0;
    if(l<0) return 0;
    if(r<0) return 0;
    return ask(c,r)-ask(c,l-1);
}
main(){
#ifdef LOCAL
    auto start=clock();
#endif
    ios::sync_with_stdio(0),cin.tie(nullptr);
    cin>>n>>m;
    rep(i,1,n){
        cin>>a[i];
        (s[i]=s[i-1]+a[i])%=m;
    }
    rep(r,1,n){
        int res=ask(c1,s[r]+1,N-3)*m;
        ans+=s[r]*r-sum+res;
        sum+=s[r];
        add(c1,s[r],1);
    }
    cout<<ans;
#ifdef LOCAL
    clog<<"\ntime: "<<clock()-start<<" ms\n";
#endif
}
```

---

