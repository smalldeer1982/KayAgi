# [CERC2013] Magical GCD

## 题目描述

一个非空正整数序列的“神奇 GCD”定义为其长度与所有元素的最大公约数的乘积。

给定一个序列 $(a_1, \ldots , a_n)$，找出其所有连续子序列中可能的最大“神奇 GCD”。

## 说明/提示

时间限制：8000 毫秒，内存限制：1048576 kB。

Central Europe Regional Contest (CERC) 2013。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
1
5
30 60 20 20 20
```

### 输出

```
80
```

# 题解

## 作者：Lynkcat (赞：9)

关于这一类问题存在一个离线的预处理时间复杂度为 $O(n \log v)$ 的解，但是我找到的大部分关于这个做法的解释都没有解释清楚复杂度。

我们从左往右枚举右端点 $r$，由于对于不同的左端点 $l$，最多只有 $\log v $ 个本质不同的区间 gcd。维护一个二元 vector $(l,v)$ 表示当前右端点为 $r$ 的时候的左端点为 $l$ 的 gcd 值为 $v$。考虑扩展 $r\rightarrow r+1$，我们发现会新增一个左端点 $r+1$，然后我们再次扫描所有二元组，把老的 $v$ 和 $a_{r+1}$ 取 gcd，相同的直接合并。

乍一看，这个做法的复杂度是 $O(n \log^2 v)$ 的，因为要取 $O(n\log v)$ 次 gcd。但是实际上我们发现每个左端点对复杂度的贡献最多为 $\log$，也就是说有效的取 $gcd$ 递归层数不超过 $O(2n \log v)$ 次，所以复杂度是 $O(n\log v)$ 的。

```c++
// Lynkcat.
// Problem: P7009 [CERC2013] Magical GCD
// URL: https://www.luogu.com.cn/problem/P7009#submit
// Memory Limit: 1024 MB
// Time Limit: 8000 ms
// -----------------------------------------------
//The Hunting Party - Keys To The Kingdom
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false)
#define ll long long
#define mp make_pair
#define pa pair < int,int >
#define fi first
#define se second
#define inf 1e18
#define mod 998244353
#define int ll
#define N 1000005
using namespace std;
inline char gc(){static char buf[1000000],*p1=buf,*p2=buf;return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;}
// #define gc getchar
inline ll read(){char c=gc();ll su=0,f=1;for (;c<'0'||c>'9';c=gc()) if (c=='-') f=-1;for (;c>='0'&&c<='9';c=gc()) su=su*10+c-'0';return su*f;}
inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll x){write(x),putchar(' ');}
inline void writeln(ll x){write(x);putchar('\n');}
int a[N],mx;
int n,q;
int b[N],ls[N],nx[N];
int ans;
void ers(int x)
{
	ls[nx[x]]=ls[x];
	nx[ls[x]]=nx[x];
}
void Bella()
{
	n=read();
	for (int i=1;i<=n;i++) a[i]=read();
	nx[0]=n;
	ls[n]=0;
	b[n]=a[n];
	nx[n]=n+1;
	ans=a[n];
	for (int i=n-1;i>=1;i--)
	{
		int x=nx[0];
		b[i]=a[i];
		ls[i]=0;
		nx[i]=x;
		ls[x]=i;
		nx[0]=i;
		int now=i;
		while (now!=n+1)
		{
			b[now]=__gcd(a[i],b[now]);
			if (b[now]==b[ls[now]])
			{
				ers(ls[now]);
			}
			now=nx[now];
		}
		now=nx[0];
		int lst=i-1;
		int nowx=0;
		while (now!=n+1)
		{
			ans=max(ans,(now-i+1)*b[now]);
			lst=now;
			now=nx[now];
		}
	}
	writeln(ans);
}
signed main()
{
	int T=read();
	while (T--)
	{
		Bella();
	}
}
/*
*/
```

---

## 作者：Cyber_Tree (赞：6)

~~贡献分掉光了来水篇题解。。。~~

提供一种~~小清新~~分治写法。

发现这道题和前几天做的[一道题](https://www.luogu.com.cn/problem/P4435)很像，但是题解中貌似并没有类似的做法。。。

### 题意

给定序列 $a$ ，求 $\max_{l\le r} (r-l+1) \gcd(a_l, a_{l+1}, ..., a_{r-1}, a_r)$ 。  

### 题解

乍一看这个 $\gcd$ 貌似很难搞，因此考虑从 $\gcd$ 的性质入手。  
$\gcd$ 是可合并的，即一个区间的 $\gcd$ 可以通过两个子区间的 $\gcd$ 合并得到。  
一个区间的前缀 $\gcd$ 至多只有 $\log a$ 种取值，因为每次新加入一个数 ，$\gcd$ 要么不变，要么至少变为原来的 $\frac{1}{2}$ 。

有了这两个性质，这个问题便可以分治解决了。  
要求区间 $[l, r]$ 的最大值，只要分别求区间 $[l, mid]$ ， $[mid+1, r]$ 以及横跨 $mid$ 的区间的最大值即可。  
考虑如何求解横跨 $mid$ 的区间的答案，不难想到先求出左子区间的后缀 $\gcd$ 和右子区间前缀 $\gcd$ ，根据上文所述，这些 $\gcd$ 一共只有 $\log a$ 种取值，于是可以记录每种取值的位置，暴力 $O(\log^2 a)$ 合并，最后再根据两个子区间的前后缀 $\gcd$ 求得当前区间的前后缀 $\gcd$ ，用于下一次的更新。

于是此题得解。  
时间复杂度大概为 $O(n \log a \log n)$ ，但是时间复杂度并不严格，因为在分治树靠上的几层，处理每一层的复杂度是 $O(\log^2 a)$ 的，而在分治树靠下的几层中，处理每一层的复杂的是 $O(n \log a)$ 的。  
~~时限 8s 保证了这种做法的时间复杂度是 O(能过)。。~~  

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
const int N=1e5+10;
inline ll read(){
	ll f=1, x=0; char ch=getchar();
	while(!isdigit(ch)) { if(ch=='-') f=-1; ch=getchar(); }
	while(isdigit(ch)) { x=x*10+ch-48; ch=getchar(); }
	return f*x;
}
int T, n;
ll a[N], ans;
vector<pair<ll, int> > pre, suf;
ll gcd(ll n, ll m) { return !n ? m : gcd(m%n, n); }
void solve(int l, int r){
	if(l==r){
		ans=max(ans, a[l]);
		pre.clear(), pre.push_back(make_pair(a[l], l));
		suf.clear(), suf.push_back(make_pair(a[l], l));
		return;
	}
	int mid=(l+r)>>1;
	solve(l, mid);
	vector<pair<ll, int> > prel=pre, sufl=suf;
	solve(mid+1, r);
	vector<pair<ll, int> > prer=pre, sufr=suf;
	pre=prel, suf=sufr;
	for(pair<ll, int> v : prer){
		if(v.fi%pre.back().fi==0) pre.back().se=v.se;
		else pre.push_back(make_pair(gcd(v.fi, pre.back().fi), v.se));
	}
	for(pair<ll, int> v : sufl){
		if(v.fi%suf.back().fi==0) suf.back().se=v.se;
		else suf.push_back(make_pair(gcd(v.fi, suf.back().fi), v.se));
	}
	for(pair<ll, int> i : sufl) for(pair<ll, int> j : prer)
		ans=max(ans, gcd(i.fi, j.fi)*(j.se-i.se+1));
}
signed main(void){
	T=read();
	while(T--){
		n=read(); ans=0;
		for(int i=1; i<=n; ++i) a[i]=read();
		solve(1, n);
		printf("%lld\n", ans);
	}
	return 0;
}
```

### 瞎扯

~~使用这种做法，此题甚至可以变成用线段树维护前后缀 gcd ，单点修改区间查询的毒瘤数据结构卡常题。。。（貌似也不是特别毒瘤？。。总之时间复杂度爆炸且常数巨大。。。）~~

---

## 作者：Remake_ (赞：6)

看到区间$\gcd$，你想到了什么呢？

没错，st表！因为$\gcd$函数显然满足可合并性质。

所以我们先预处理出st表以便我们能在$O(1)$的时间内求出区间$\gcd$。

对于每一个$\gcd$值的话显然是序列越长越好，我们知道对于每个左端点$l$，以及当前的$\gcd$，显然每个$l\leq r\leq n$，$\gcd\limits_{i=l}^{r}i$是关于$r$单调的，所以我们可以二分查找到一个$r'$使得$r'$为最大的满足$\gcd\limits_{i=l}^{r'}i=$当前的$\gcd$的数，接着用$(r'-l+1)\times$当前$\gcd$更新最大值，然后更新$l'=r'+1$，$\gcd'=\gcd\limits_{i=l}^{r'+1}i$一直迭代下去就没了，~~有数论分块内味了~~。

需要注意的是左端点不一定是$1$，所以左端点实际上要从$1$枚举到$n$。。。

看上去这个东西复杂度是假的，但是：
>长度$n$的序列的所有子序列的最大公约数，最多有$\log n$个。

所以此程序的复杂度为枚举左端点的$O(n)\times$所有子序列的最大公约数个数$O(\log n)\times$二分查找复杂度$O(\log n)=O(n\log^2 n)$

然后发现是多测，突然慌了。

然后发现时限$8.00s$，突然稳了。

蒟蒻的垃圾代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, T;
long long gcd[100001][21], maxx;
long long gcdqj(int l, int r)
{
    int p = log2(r - l + 1);
    return __gcd(gcd[l][p], gcd[r - (1 << p) + 1][p]);
}
int search(int i, int l, int r, long long value)
{
    while (r - l > 1)
    {
        int mid = (l + r) / 2;
        if (gcdqj(i, mid) == value)
            l = mid;
        else
            r = mid - 1;
    }
    if (gcdqj(i, r) == value)
        return r;
    return l;
}
int main()
{
    cin >> T;
    while (T--)
    {
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> gcd[i][0];
        for (int i = 1; i <= 20; i++)
            for (int j = 1; j + (1 << i) - 1 <= n; j++)
                gcd[j][i] = __gcd(gcd[j][i - 1], gcd[j + (1 << i - 1)][i - 1]);
        maxx = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int l = i, r = 0; l <= n; l = r + 1)
            {
                r = search(i, l, n, gcdqj(i, l));
                maxx = max(maxx, (r - i + 1) * gcdqj(i, l));
            }
        }
        cout << maxx << endl;
    }
}
```


---

## 作者：ListenSnow (赞：3)

[原题链接](https://www.luogu.com.cn/problem/P7009)

## 题意

有 $T$ 组询问，每次给出 $n$ 个数 $a_i$。  

你需要找到这个数组的一个子序列（要求编号连续），使得该序列中所有数的最大公约数和序列长度的乘积最大，并输出这个最大值。

#### 数据范围

$1 \leq n \leq 10^5,1 \leq a_i \leq 10^{12}$。

## 思路

参考了[这篇博客](https://www.luogu.com.cn/blog/redegg/solution-p5502)。

对于原序列的一个子区间，如果固左端点 $l$ 不断往右延伸，设当前区间的最大公约数为 $g$，现在要把元素 $x$ 扩展进来，新区间的最大公约数要么还是 $g$,要么就至少减少一半（根据 gcd 的性质），那么区间的 gcd 就至多更新 $\log a_l$。

因为题目所求的是最大值，那么对于 gcd 相同的区间，肯定会选择长度最长的区间。那么就可以从前往后枚举 $a_i$，用一个队列记录这些不同的左端点，同时用 $a_i$ 去更新这些左端点，并同时更新答案。

## code：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int N=1e5+10;
#define LL long long
queue<int>q,r;
int n;LL a[N],res;
LL gcd(LL a,LL b){return b==0?a:gcd(b,a%b);}
int main()
{
	int T;scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);res=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%lld",&a[i]);LL last=0;res=max(res,a[i]);
			while(!q.empty())
			{
				int x=q.front();q.pop();a[x]=gcd(a[x],a[i]);//x就是最小的满足区间[x,i]的gcd为a[x]的左端点 
				res=max(res,a[x]*(i-x+1));
				if(a[x]==a[last]) continue;//一些左端点就可以合并掉 
				r.push(x);last=x;
			}
			while(!r.empty())
			{
				q.push(r.front());
				r.pop();
			}
			if(a[last]!=a[i]) q.push(i);//i也可以作为一个新的左端点 
	 	}
		printf("%lld\n",res);
		while(!q.empty()) q.pop();
	}
	return 0;
}
```


---

## 作者：_Vix_ (赞：2)

[原题链接](https://www.luogu.com.cn/problem/P7009)

[双倍经验](https://www.luogu.com.cn/problem/P5502)

## 分析
区间 $\gcd$ 具有可合并性，因此用 ST 表 $O(n \log n \log V)$ （$V$ 是值域）预处理，可以做到 $O(1)$ 查询区间 $\gcd$。

如果区间左端点固定，那么区间 $\gcd$ 的取值只有 $\log_2V$ 种，因为区间右端点每扩展一个数，加入一个数后 $\gcd$ 要么不变要么变为原来的 $\dfrac{1}{2}$。用类似数论分块的做法再加上每次二分找右端点，即可做到最坏 $O(Tn \log n \log V)$。

## Code

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 1e5 + 10, M = 20;
int n, lg[N];
ll g[N][M];

inline ll query(int l, int r) {
	int k = lg[r - l + 1];
	return __gcd(g[l][k], g[r - (1 << k) + 1][k]);
}

inline int find(int pos, int s) {
	int l = s, r = n;
	while (l < r) {
		int mid = l + r + 1 >> 1;
		if (query(pos, mid) == query(pos, s)) l = mid;
		else r = mid - 1;
	}
	return l;
}

void solve() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", &g[i][0]);
	for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
	for (int j = 1; j < 19; j++)
		for (int i = 1; i + (1 << j) - 1 <= n; i++)
			g[i][j] = __gcd(g[i][j - 1], g[i + (1 << j - 1)][j - 1]);
	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int l = i, r; l <= n; l = r + 1) {
			r = find(i, l);
			ans = max(ans, query(i, l) * (r - i + 1));
		}
	}
	printf("%lld\n", ans);
}

int main() {
	int T; scanf("%d", &T);
	while (T--) solve();
	return 0;
}
```


---

## 作者：CmsMartin (赞：1)

[更好的阅读体验](http://cmsblog.top/archives/cerc2013magicalgcd)

## 题目描述

[题目传送门](https://www.luogu.com.cn/problem/P7009)

## 思路

考虑分治。

要求 $[l,r]$ 的答案，之需求下面三部分答案的最大值（set $mid = \frac{l+r}{2}$）：

+ $[l, mid]$ 的答案；

+ $[mid+1,r]$ 的答案；

+ ${a\in[l,mid], b \in [mid+1,r]},[a,b]$ 的答案最大值。

这样前两者可以递归解决，考虑如何解决最后一个。

**经典结论：一个序列的前缀（后缀）$\gcd$ 最多有 $\log n$ 种取值。**

那么我们可以预处理 $[l,mid]$ 的每个不同的后缀 $\gcd$ 的下标的最小值，$[mid+1,r]$ 的每个不同的前缀 $\gcd$ 的下标的最大值。然后只需要枚举即可。

时间复杂度为 $\Theta(n \log n) + \Theta(\log^2 n) = \Theta(n \log n)$

设 $T(n)$ 为时间复杂度。

$$
T(n) = 2{T(\frac{n}{2})}+ \Theta(n \log n)
$$

根据 master 定理，$T(n) = \Theta(n \log^2 n)$

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

namespace io {
	const int SIZE = (1 << 21) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55]; int f, qr;
	// getchar
	#define gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
	// print the remaining part
	inline void flush () {
		fwrite (obuf, 1, oS - obuf, stdout);
		oS = obuf;
	}
	// putchar
	inline void putc (char x) {
		*oS ++ = x;
		if (oS == oT) flush ();
	}
	// input a signed integer
	template <class I>
	inline void read (I &x) {
		for (f = 1, c = gc(); c < '0' || c > '9'; c = gc()) if (c == '-') f = -1;
		for (x = 0; c <= '9' && c >= '0'; c = gc()) x = x * 10 + (c & 15); x *= f;
	}
	// print a signed integer
	template <class I>
	inline void print (I x) {
		if (!x) putc ('0'); if (x < 0) putc ('-'), x = -x;
		while (x) qu[++ qr] = x % 10 + '0',  x /= 10;
		while (qr) putc (qu[qr --]);
	}
	struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
}
using io :: read;
using io :: putc;
using io :: print;

const int MAXN = 1e5 + 10;
typedef long long ll;

int T, n;
ll a[MAXN];
vector<pair<ll, int> > p1, p2;

ll Solve(int l, int r) {
	if (l == r) return a[l];
	if (l > r) return 0;
	int mid = l + r >> 1;
	ll res1 = Solve(l, mid), res2 = Solve(mid + 1, r), res3 = 0;
	p1.clear(); p2.clear();
	
	ll tmp1 = a[mid], tmp2;
	for (int i = mid - 1; i >= l; i--) {
		tmp2 = __gcd(tmp1, a[i]);
		if (tmp2 != tmp1) {
			p1.push_back({tmp1, i + 1});
			tmp1 = tmp2;
		}
	}
	p1.push_back({tmp1, l});
	
	tmp1 = a[mid + 1];
	for (int i = mid + 2; i <= r; i++) {
		tmp2 = __gcd(tmp1, a[i]);
		if (tmp2 != tmp1) {
			p2.push_back({tmp1, i - 1});
			tmp1 = tmp2;
		}
	}
	p2.push_back({tmp1, r});
	
	for (auto i : p1) {
		for (auto j : p2) {
			res3 = max(res3, __gcd(i.first, j.first) * (ll)(j.second - i.second + 1));
		}
	}
	return max({res1, res2, res3});
}

int main () {
	read(T);
	while (T--) {
		read(n);
		for (int i = 1; i <= n; i++) read(a[i]);
		print(Solve(1, n));
		putc('\n');
	}
	return 0;
}
```

---

## 作者：happybob (赞：1)

容易发现的是，当左端点 $l$ 确定时，$r \in [l,n]$，那么 $\gcd \limits_{i=l}^r a_i$ 的不同数量是 $O(\log V)$ 的级别。

原因是，每次 $\gcd$ 减少，总有一个质因数的次数降低，降低 $O(\log V)$ 次就会变成 $1$。

于是我们枚举左端点，然后二分 $O(\log V)$ 次右端点，用 ST 表可以做到单次询问 $O(\log V)$ 处理区间 $\gcd$，复杂度 $O(n \log^2 V \log n)$。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <climits>
#include <numeric>
using namespace std;

const int N = 1e5 + 5;

long long ans = 0LL;
int n;
long long a[N];

long long f[N][31];
int LG2[N];

void Init()
{
	for (int i = 1; i <= n; i++)
	{
		f[i][0] = a[i];
	}
	for (int j = 1; j <= LG2[n]; j++)
	{
		for (int i = 1; i + (1 << j) - 1 <= n; i++)
		{
			f[i][j] = gcd(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
		}
	}
}

long long query(int l, int r)
{
	int s = LG2[r - l + 1];
	return gcd(f[l][s], f[r - (1 << s) + 1][s]);
}

int main()
{
	LG2[1] = 0;
	for (int i = 2; i < N; i++) LG2[i] = LG2[i / 2] + 1;
	int t;
	scanf("%d", &t);
	while (t--)
	{
		ans = 0LL;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		Init();
		for (int i = 1; i <= n; i++)
		{
			long long nowv = a[i];
			int nowl = i;
			while (true)
			{
				int l = nowl, r = n, place = -1;
				while (l <= r)
				{
					int mid = (l + r) >> 1;
					long long g = query(i, mid);
					if (g == nowv)
					{
						ans = max(ans, g * (1LL * mid - i + 1));
						place = mid;
					}
					if (g >= nowv)
					{
						l = mid + 1;
					}
					else
					{
						r = mid - 1;
					}
				}
				if (place == -1 || place == n) break;
				nowv = query(i, place + 1);
				nowl = place + 1;
			}
		}
		printf("%lld\n", ans);
	}
	
	return 0;
}
```


---

## 作者：linxuanrui (赞：1)

### 题目大意

求 $\max\limits_{i=1}^n \max\limits_{j=i+1}^n (r-l+1)\times \gcd\limits_{k=l}^r a_k$。

### 题目分析

别的题解都把 st 表解释的不错了，这里就讲一讲为什么能用 st 表和二分。

首先，我们要知道 gcd 的几个性质：

$$
\begin{matrix}
\gcd(a,b,c)=\gcd(gcd(a,b),\gcd(b,c))\\
\gcd\limits_{i=x}^{y}a_i\ge \gcd\limits_{i=x}^{y+z}a_i,\text{其中 }z\ge0 
\end{matrix}
$$

而 st 表的大概原理可参考下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/nk4akfqn.png)
（图有点丑，请不要吐槽）

其实我们就相当于是知道 $\gcd\limits_{i=a}^c a_i$ 和 $\gcd\limits_{i=b}^d a_i$，求 $\gcd\limits_{i=a}^d a_i$。

$$
\begin{matrix}
\because \gcd\limits_{i=a}^c a_i = \gcd(\gcd\limits_{i=a}^b a_i,\gcd\limits_{i=b}^c a_i),\gcd\limits_{i=b}^d a_i = \gcd(\gcd\limits_{i=b}^c a_i,\gcd\limits_{i=c}^d a_i)\\
\therefore \gcd(\gcd\limits_{i=a}^c a_i,\gcd\limits_{i=b}^d a_i)=\gcd(\gcd\limits_{i=a}^b a_i,\gcd\limits_{i=b}^c a_i,\gcd\limits_{i=b}^c a_i,\gcd\limits_{i=c}^d a_i)=\gcd\limits_{i=a}^d a_i
\end{matrix}
$$

关于 st 表就讲到这，接下来讲二分。

对于 $\gcd$ 值相同的一段，**长度越长结果越大**，而且由上面的性质二，**$\gcd$ 值满足单调性**，所以可以二分。

### 代码

记得要开 `long long`！

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
int T,n,gcd[100001][20],lg[100001],maxx = -0x3f3f3f3f;
int get(int l,int r) {
    int t = lg[r - l + 1];
    return __gcd(gcd[l][t],gcd[r - (1 << t) + 1][t]);
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    for(int z = 1;z <= T;z++) {
        cin >> n;
        lg[0] = -1;
        for(int i = 1; i <= n; i++) {
            cin >> gcd[i][0];
            lg[i] = lg[i >> 1] + 1;
        }
        for(int j = 1; j <= lg[n]; j++) {
            for(int i = 1; i + (1 << j) - 1 <= n; i++) {
                gcd[i][j] = __gcd(gcd[i][j - 1],gcd[i + (1 << (j - 1))][j - 1]);
            }
        }
        for(int i = 1; i <= n; i++) {
            int j = i,l,r,ans = 0;
            while(j <= n) {
                l = j,r = n + 1;
                int x = get(i,j);
                while(r - l > 1) {
                    int mid = (l + r) >> 1;
                    if(get(i,mid) == x)l = mid,ans = l;
                    else r = mid;
                }
                maxx = max(x * (l - i + 1),maxx);
                j = r + 1;
            }
        }
        cout << maxx << endl;
		maxx = -0x3f3f3f3f;
    }
}
```

---

## 作者：peterwuyihong (赞：1)

题意：$1\le n\le 10^5,1\le a_i\le 10^{12}$，给一个数组 $a_{[1,n]}$，求 

$$\max_{1\le l\le r\le n}(r-l+1)\gcd_{i=l}^ra_i$$

我们看到 $\gcd$,感到非常兴奋，因为这个玩意儿可以使用 ST 表乱搞查询。

于是我们获得了 $O(1)$ 查询。

我们枚举每个端点，往后二分找到区间 $\gcd$ 值不同的最后的位置，更新答案即可。

为什么这样复杂度是正确的呢？因为可以考虑到一个变换，就是 $x\rightarrow x/lpf_x$，$x$ 代表最小质因子，变换 $O(\log)$ 次必然变成了 $1$。

于是我们得到了一个 $O(n)$ 乘上不知道几个 $\log$  的算法，反正顶多三个，靠信仰跑吧。

被这个二分恶心了一会儿，草。

```cpp
#define int long long
#define maxn 100010
int n;
int f[maxn][19];
int lg[maxn];
int GCD(int l,int r){
	int k=lg[r-l+1];
	return __gcd(f[l][k],f[r-(1<<k)+1][k]);
}
int ans,T;
signed main(){
#ifndef ONLINE_JUDGE
	freopen("testdata.in","r",stdin);
#endif
for(cin>>T;T;T--){
	cin>>n;
	ans=0;
	lg[0]=-1;
	for(int i=1;i<=n;i++)cin>>f[i][0],lg[i]=lg[i>>1]+1;
	for(int j=1;j<=lg[n];j++)
	for(int i=1;i<=n-(1<<j)+1;i++)
	f[i][j]=__gcd(f[i][j-1],f[i+(1<<(j-1))][j-1]);
	for(int i=1;i<=n;i++){
		int o=f[i][0];
		ans=max(ans,o);
		int lstl=i;
		while(1){
			int l,r=n,mid;
			l=lstl;
			while(l<=r){
				mid=(l+r)>>1;
				if(GCD(i,mid)==o)l=mid+1;
				else r=mid-1;
			}
			ans=max(ans,o*(l-i));
			if(l==n+1)break;
			lstl=l;
			o=GCD(i,l);
		}
	}
	cout<<ans<<endl;
}
#ifndef ONLINE_JUDGE
	cerr<<endl<<(double)clock()/CLOCKS_PER_SEC;
#endif
}
```
附一个[双倍经验]()

---

## 作者：FjswYuzu (赞：1)

说起来这个题还想出训练赛结果发现是原题来着。。。

首先能够得到 $\gcd$ 的一些性质。
  
1. $\gcd(a_1,a_2,\dots,a_p) \geq \gcd(a_1,a_2,\dots,a_{p+1})$，即新加入一个数的 $\gcd$ 一定小于等于之前的 $\gcd$；   
2. 对于前缀 $\gcd$，每次发生改变，至少变到原来的 $\dfrac{1}{2}$，即取值最多有 $O(\log a_i)$ 个。

好了所以说我们可以直接开一个队列暴力维护一下 $\gcd$，枚举右端点然后然后可以直接枚举队列里面的 $\gcd$，维护两个信息，及能够延伸到的最长的 $\gcd$ 与位置，算一下贡献。$\gcd$ 用 `map` 判重才是 $O(\log n)$ 级别。时间复杂度 $O(n \log^2 n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
struct Factor{
	LL pos,val;
	Factor(LL P=0,LL V=0){pos=P,val=V;}//位置 与 gcd 值
};
LL gcd(LL a,LL b){return !b?a:gcd(b,a%b);}
LL n,a[100005];
map<LL,bool> mp;
int main(){
	LL T;
	scanf("%lld",&T);
	while(T-->0)
	{
		queue<Factor> Q;
		scanf("%lld",&n);
		LL ans=n;
		for(LL i=1;i<=n;++i)	scanf("%lld",&a[i]),ans=max(ans,a[i]);
		for(LL i=1;i<=n;++i)
		{
			mp.clear();
			queue<Factor> det;
			while(!Q.empty())
			{
				Factor lyc=Q.front();
				Q.pop();
				lyc.val=gcd(lyc.val,a[i]);
				ans=max(ans,lyc.val*(i-lyc.pos+1));
				if(lyc.val!=1 && !mp[lyc.val])	det.push(lyc),mp[lyc.val]=true;//每次加入一个数，更新一下 gcd。如果重复或者是 1 了就算了吧
			}
			while(!det.empty())	Q.push(det.front()),det.pop();
			if(a[i]!=a[i-1])	Q.push(Factor(i,a[i]));//反装回去
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：walk_out_study (赞：0)

### 思路
题意很明确了。

从暴力开始，枚举每个区间，起点终点各一维，很明显超时了。

对于每个以 $i$ 为开始，$j$ 为结尾的区间，定义区间最大公约数为 $f(i,j)$，可能存在开头相同，结尾为 $j+1$，但是 $f(i,j)=f(i,j+1)$ 的情况，此时答案只与 $j$ 有关。

问题便转化为如何求最大的 $j$，观察数据特点可得出一个结论：

在区间开头为 $i$ 时，$f(i,j)$ 是不上升的，也就意味着有单调性。序列长度增加，最大公约数是不可能增加的。

这样直接二分，找到最大的 $j$，更新答案。此时 $f(i,j+1)$ 的值变小，我们再找满足 $f(i,j_1)=g(i,j+1)$ 的，循环往复，直到 $j_{num}>n$。

-----
通过 st 表求区间 $\gcd$ 的特性来维护 $f(i,j)$。

### 代码
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
long long aans,st[100001][21];
int T,n,tmp,log[100001];
void init()
{
	for(int i=1;i<=n;i++) 
		cin>>st[i][0];
	for(int len=1;len<=20;len++)
		for(int i=1;i+(1<<len)-1<=n;i++)
			st[i][len]=__gcd(st[i][len-1],st[i+(1<<(len-1))][len-1]);
}
long long ans(int l,int r)
{
	int len=log[r-l+1];
	return __gcd(st[l][len],st[r-(1<<len)+1][len]);
}
signed main() {
	cin>>T;
	for(int i=2;i<=100000;i++)
		log[i]=log[i>>1]+1;
	while(T--)
	{
		cin>>n;
		init();
		for(int s=1;s<=n;s++)
		{
			tmp=s;
			//tmp为新 j 的开始 
			while(tmp<=n)
			{
				long long gcd=ans(s,tmp);//求f(i,j)
				int l=tmp-1,r=n+1;//二分设两个取不到的值
				while(l+1<r)
				{ 
					int mid=l+r>>1;
					if(gcd==ans(s,mid))
						l=mid,aans=max(aans,gcd*(mid-s+1LL));
					else
						r=mid;
				}
				tmp=r;
			}
		}
		cout<<aans<<"\n";
		aans=0;
	}
	return 0;
}
```

---

## 作者：wcyQwQ (赞：0)

对于一个值域为 $V$ 的序列，他后缀 $\gcd$ 中不同的值只有 $O(\log V)$ 个，因为每次加入一个数，$\gcd$ 要么不变，要么至少减半。那么就很简单了。我们设现在考虑右端点为 $x$ 时的答案。那么我们维护序列 $a_1, \ldots a_x$ 后缀 $\gcd$ 每一个连续段的左端点，我们开一个链表，每一个节点存一个二元组 $(i, j)$，分别表示这个位置的下标和目前为止的后缀 $\gcd$。我们首先遍历链表，使 $j \gets \gcd(j, a_x)$，然后把重复元素删掉，最后加入二元组 $(x, a_x)$，并更新答案。时间复杂度 $O(n\log V)$。[Code](https://loj.ac/s/1816992)

---

## 作者：wangyibo201026 (赞：0)

## $\text{solution}$

感觉分治的题目也很好啊 qwq。

就是你考虑一个区间 $[l, r]$ 里的子区间有几种情况，设 $mid = \frac{l + r}{2}$：

- 左右端点全在 $[l, mid]$ 中。
- 左右端点全在 $[mid + 1, r]$ 中。
- 左右端点跨 $mid$。

对于前两种情况我们可以分治去做。我们考虑第三种情况怎么解决。

我们发现，可以左右端点从 $mid$ 开始，$j$ 依次加一，然后 $i$ 寻找最大公约数等于原来的扩展就行了，显然证明这个贪心是正确的。对于左端点也要依次扩展。

然后这个的复杂度非常妙啊，假设 $\gcd$ 的复杂度为 $z = \log_2V$，$V$ 为值域，那么明显我们在扩展的时候需要用到这个 $z$，由于一共有 $\log_2 n$ 层，每层的长度都是 $n$，所以复杂度为：$O(zn\log_2n)$，复杂度不大。

---

## 作者：_Spectator_ (赞：0)

[可能更好的食用体验](/blog/523641/P7009) $|$ 
[题目传送门](/problem/P7009) $|$ 
[我的其他题解](/blog/523641/#type=题解-New)

------------

${\large\color{#00CD00}\text{思路}}$

看到区间 $\gcd$，不难想到可以使用 [ST 表](/problem/P3865) 实现 $O(1)$ 查询。但是，如果分别枚举左右端点仍然会超时。这时可以举个例子，看看以下这组数据：

$\begin{array}{|c|c|c|c|c|c|c|c|c|} \hline
a_i & 30 & 60 & 20 & 20 & 10 & 5 & 3 & 1 \\ \hline
\gcd a_{1\sim i} & 30 & 30 & 10 & 10 & 10 & 5 & 1 & 1 \\ \hline
\end{array}$

可以发现，$\gcd a_{1\sim i}$ 中有很多连续一段的数是相等的。对于这些相等的最大公约数，显然取其最右端可以使答案最大。又因为其满足单调性，因此可以使用**二分**来找到这一段的最右端。这样就使得右端点的枚举次数大大降低。

另外还需注意，区间的左端点不一定是 $1$，因此还需枚举一遍左端点。

关于时间复杂度：设 $a_i$ 的因数个数之和为 $k$，则时间复杂度为 $O(nk\log k)$，可以通过此题。

------------

${\large\color{#00CD00}\text{代码}}$

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=1e5+5;
ll T,n,ans;
ll f[maxn][30],lg[maxn]={-1}; //记得要开long long
ll query(int l,int r) //查询[l,r]区间内的最大公约数
{
	ll s=lg[r-l+1];
	return __gcd(f[l][s],f[r-(1<<s)+1][s]);
}
int main()
{
	for(cin>>T;T--;)
	{
		cin>>n;ans=0;
		for(int i=1;i<=n;i++)
		{
			cin>>f[i][0];
			lg[i]=lg[i/2]+1;
		}
		for(int j=1;j<=lg[n];j++) //ST表
			for(int i=1;i+(1<<j)-1<=n;i++)
				f[i][j]=__gcd(f[i][j-1],f[i+(1<<j-1)][j-1]);
		for(int i=1;i<=n;i++) //枚举左端点i
		{
			int j=i; //j为右端点
			while(j<=n)
			{
				ll l=j-1,r=n+1,x=query(i,j);
				while(l+1<r) //使用二分找到与当前最大公约数相等的最右端，注意l,r的初值
				{
					ll mid=(l+r)/2;
					if(query(i,mid)==x)l=mid;
					else r=mid;
				}
				ans=max(ans,x*(l-i+1)),j=r;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：UperFicial (赞：0)

[传送门](https://www.luogu.com.cn/problem/P7009)。

同步发表于我的 [$\texttt{cnblog}$](https://www.cnblogs.com/UperFicial/p/16124800.html)。

### $\texttt{Description}$

给定长度为 $n$ 的正整数序列 $a$。

求 $\max_{1\le l\le r\le n}\{\gcd_{l\le j\le r}\{a_j\}\times (r-l+1)\}$。

$1\le n\le 10^5$，$1\le a_i\le 10^{12}$。

### $\texttt{Solution}$

考虑 $\texttt{CDQ}$ 分治。

但问题在于 $\gcd$ 的值从左往右是单调不升的，$r-l+1$ 的值是上升的。没法快速维护这个东西。

然后聪明的你发现了 $\texttt{key conclusion}$：

> 一个前缀的 $\gcd$ 最多有 $\log$ 种取值。

简单证明一下：

> 右端点向右移动后，新的前缀 $\gcd$ 一定会变小，并且新的 $\gcd$ 会被原来的 $\gcd$ 整除，所以新的 $\gcd$ 一定不大于原来 $\gcd$ 的一半。

然后维护对于每一个值相同的前缀 $\gcd$，维护右边界即可。

代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<ctime>
#include<cstdlib>
#include<climits>
#include<queue>
#include<vector>
using namespace std;
typedef long long ll;
inline ll read()
{
	ll s=0,w=1;
	char ch=getchar();
	while(ch<'0' or ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' and ch<='9')s=s*10+(ch-'0'),ch=getchar();
	return s*w;
}
const int INF=1e9+10;
template<typename T>
inline T Max(T x,T y){return x>y?x:y;}
inline int Min(int x,int y){return x<y?x:y;}
inline void Swap(int&x,int&y){int t=x;x=y;y=t;return;}
inline int Abs(int x){return x>0?x:-x;}
inline ll gcd(ll x,ll y){return y==0?x:gcd(y,x%y);}
const int MAXN(1e5+10);
int n;
ll a[MAXN];
ll pre[MAXN],suf[MAXN];
int pos[MAXN];
inline ll CDQ(int l,int r)
{
	if(l==r) return a[l];
	int mid=(l+r)>>1,tot(0);
	ll ans=Max(CDQ(l,mid),CDQ(mid+1,r));
	suf[mid]=a[mid],pre[mid+1]=a[mid+1];
	for(register int i=mid-1;i>=l;i--) suf[i]=gcd(suf[i+1],a[i]);
	for(register int i=mid+2;i<=r;i++) pre[i]=gcd(pre[i-1],a[i]);
	for(register int i=mid+2;i<=r;i++)
		if(pre[i]!=pre[i-1]) pos[++tot]=i-1;
	pos[++tot]=r;
	for(register int i=l;i<=mid;i++)
		for(register int j=1;j<=tot;j++)
			ans=Max(ans,gcd(suf[i],pre[pos[j]])*1ll*(pos[j]-i+1));
	return ans;
}
inline void solve()
{
	scanf("%d",&n);
	for(register int i=1;i<=n;i++) a[i]=read();
	printf("%lld\n",CDQ(1,n));
	return;
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--) solve();
}
```

$$\texttt{The End.by UF}$$

---

## 作者：Leasier (赞：0)

前置芝士：[ST 表](https://oi-wiki.org/ds/sparse-table/)

显然区间 gcd 的值在一定范围内不变，考虑对于所有左端点和 gcd 相同的区间，只取符合条件的最右边的端点。在固定左端点和 gcd 的前提下，右端点可通过二分 + ST 表在 $O(\log^2 n)$ 的时间复杂度内求出。

于是很容易想出一个暴力做法：枚举区间左端点，从左向右依次二分直到 $n$。

事实上，这样做的时间复杂度是正确的，为 $O(Tn \log^3 n)$（虽然看上去不太能通过这道题，但二分总次数和 gcd 的时间复杂度不可能卡满）。

证明：考虑一个区间内的 $a_i$ 和枚举到它之前的 gcd 值 $d$，跨过 $i$ 后存在如下两种情况：

1. $\gcd(d, a_i) = d$

此时显然不会增加时间复杂度。

2. $\gcd(d, a_i) < d$

此时显然会增加 $O(\log^2 n)$ 的时间复杂度。但考虑到 $\gcd(d, a_i) \mid d$，此时 $d$ 至少减少为原来的 $\frac{1}{2}$。由于 $d$ 减到 $1$ 后就不会再减小，减小总次数最多为 $\lfloor \log_2 n \rfloor$ 次。

综上，对于每个区间左端点，时间复杂度为 $O(\log^3 n)$，进而可证得上文所述的总时间复杂度。

代码：
```cpp
#include <stdio.h>
#include <math.h>

typedef long long ll;

ll a[100007], st[100007][17];

ll gcd(ll a, ll b){
	return b == 0 ? a : gcd(b, a % b);
}

inline void init(int n){
	int m = log2(n);
	for (register int i = 1; i <= n; i++){
		st[i][0] = a[i];
	}
	for (register int i = 1; i <= m; i++){
		int id = i - 1, t1 = n - (1 << i) + 1, t2 = 1 << id;
		for (register int j = 1; j <= t1; j++){
			st[j][i] = gcd(st[j][id], st[j + t2][id]);
		}
	}
}

inline ll get_gcd(int l, int r){
	int t = log2(r - l + 1);
	return gcd(st[l][t], st[r - (1 << t) + 1][t]);
}

inline ll max(ll a, ll b){
	return a > b ? a : b;
}

int main(){
	int t;
	scanf("%d", &t);
	for (register int i = 1; i <= t; i++){
		int n;
		ll ans = 0;
		scanf("%d", &n);
		for (register int j = 1; j <= n; j++){
			scanf("%lld", &a[j]);
		}
		init(n);
		for (register int j = 1; j <= n; j++){
			int k = j;
			for (register ll x = a[j]; k <= n; x = get_gcd(j, k)){
				int l = k, r = n, pos = n;
				while (l <= r){
					int mid = (l + r) >> 1;
					if (get_gcd(j, mid) == x){
						l = mid + 1;
						pos = mid;
					} else {
						r = mid - 1;
					}
				}
				ans = max(ans, x * (pos - j + 1));
				k = l + 1;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

