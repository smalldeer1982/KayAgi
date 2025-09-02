# Marvolo Gaunt's Ring

## 题目描述

Professor Dumbledore is helping Harry destroy the Horcruxes. He went to Gaunt Shack as he suspected a Horcrux to be present there. He saw Marvolo Gaunt's Ring and identified it as a Horcrux. Although he destroyed it, he is still affected by its curse. Professor Snape is helping Dumbledore remove the curse. For this, he wants to give Dumbledore exactly $ x $ drops of the potion he made.

Value of $ x $ is calculated as maximum of $ p·a_{i}+q·a_{j}+r·a_{k} $ for given $ p,q,r $ and array $ a_{1},a_{2},...\ a_{n} $ such that $ 1<=i<=j<=k<=n $ . Help Snape find the value of $ x $ . Do note that the value of $ x $ may be negative.

## 说明/提示

In the first sample case, we can take $ i=j=k=5 $ , thus making the answer as $ 1·5+2·5+3·5=30 $ .

In second sample case, selecting $ i=j=1 $ and $ k=5 $ gives the answer $ 12 $ .

## 样例 #1

### 输入

```
5 1 2 3
1 2 3 4 5
```

### 输出

```
30
```

## 样例 #2

### 输入

```
5 1 2 -3
-1 -2 -3 -4 -5
```

### 输出

```
12
```

# 题解

## 作者：BoAn (赞：8)

先来看数据范围，$n≤10^5$，显然不可能 $O(n^2)$。

已经有人讲过区间最值了，我来一个 DP 思路的（以下的 $a_i$，$a_j$，$a_k$ 全部取自题意）。

$f_{x,1}$ 表示前 $x$ 个数中 $p×a_i$ 的最大值；

$f_{x,2}$ 表示前 $x$ 个数中 $p×a_i+q×a_j$ 的最大值；

$f_{x,3}$ 表示前 $x$ 个数中 $p×a_i+q×a_j+r×a_k$ 的最大值。

可以推出状态转移方程：

$f_{i,1}=\max(f_{i-1,1},p×a_i)$

$f_{i,2}=\max(f_{i-1,2},f_{i,1}+q×a_i)$

$f_{i,3}=\max(f_{i-1,3},f_{i,2}+r×a_i)$

为什么成立？

拿 $f_{x,1}->f_{x,2}$ 举例，对于 $a_x$，如果不取，显然什么变化也没有；如果取，也就是取 $a_j$ 为 $a_x$，结合 $f_{i,1}$ 的定义此时一定有 $i≤j=x$，符合要求。$f_{x,2}->f_{x,3}$ 同理。

每次遍历一遍数组，复杂度是 $O(n)$。

有两个点提醒：

1.考虑有负数的情况，这时候如果不特判，最大值为 $0$。

2.不开 long long 见祖宗。

```cpp
#include<iostream>
using namespace std;
long long n,p,q,r,a[100001],f[100001][4];
int main(){
    cin>>n>>p>>q>>r;
    for(int i=1;i<=n;i++)cin>>a[i];
    f[1][1]=a[1]*p; //如果有负数 
    for(int i=2;i<=n;i++)
		f[i][1]=max(f[i-1][1],a[i]*p);
	f[1][2]=f[1][1]+a[1]*q; //如果有负数 
    for(int i=2;i<=n;i++)
    	f[i][2]=max(f[i-1][2],f[i][1]+a[i]*q);
    f[1][3]=f[1][2]+a[1]*r; //如果有负数 
	for(int i=2;i<=n;i++)
    	f[i][3]=max(f[i-1][3],f[i][2]+a[i]*r);
    cout<<f[n][3];
    return 0;
}
```


---

## 作者：一扶苏一 (赞：4)

[其实点这里也不会获得更好的阅读体验](https://www.cnblogs.com/yifusuyi/p/10085164.html)

## Solution

考虑最暴力的方法，枚举 $i~,~j~,~k$ ，计算答案，时间复杂度$O(n^3)$

然后考虑如果枚举了其中两个值，剩下一个可以直接通过查询区间最值确定。例如，如果枚举了 $i~,~j$，则 $k$ 对应的最优解一定是 ( $k~>~0$ 时) $k~\times~\max_{s~=~j}^{n}~a_s$，（ $k~\leq~0$ 时） $k~\times~\min_{s~=~j}^{n}~a_s$。枚举其它两个元素同理。这样就可以用ST预处理区间最值，然后做到 $O(1)$ 查询，复杂度 $O(n\log n)-O(n^2)$ 。

考虑上述做法的缺陷在于枚举量还是太大，能否可以只枚举一个位置呢？我们发现如果枚举一个位置以后可以确定剩下两个区间，就可以只枚举一个位置。于是发现枚举 $j$ 符合要求。于是只枚举 $j$ 按照上面的方法求 $i~,~k$ 的对应答案。时间复杂度 $O(n\log n)~-~O(n)$

## Code

```cpp
#include <cmath>
#include <cstdio>
#include <algorithm>
#ifdef ONLINE_JUDGE
#define freopen(a, b, c)
#define putchar(o) \
puts("I am a cheater!")
#endif
#define rg register
#define ci const int
#define cl const long long

typedef long long int ll;

namespace IPT {
	const int L = 1000000;
	char buf[L], *front=buf, *end=buf;
	char GetChar() {
		if (front == end) {
			end = buf + fread(front = buf, 1, L, stdin);
			if (front == end) return -1;
		}
		return *(front++);
	}
}

template <typename T>
inline void qr(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch=IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = (x << 1) + (x << 3) + (ch ^ 48), ch = IPT::GetChar();
	if (lst == '-') x = -x;
}

template <typename T>
inline void ReadDb(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch = IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = x * 10 + (ch ^ 48), ch = IPT::GetChar();
	if (ch == '.') {
		ch = IPT::GetChar();
		double base = 1;
		while ((ch >= '0') && (ch <= '9')) x += (ch ^ 48) * ((base *= 0.1)), ch = IPT::GetChar();
	}
	if (lst == '-') x = -x;
}

namespace OPT {
	char buf[120];
}

template <typename T>
inline void qw(T x, const char aft, const bool pt) {
	if (x < 0) {x = -x, putchar('-');}
	rg int top=0;
	do {OPT::buf[++top] = x % 10 + '0';} while (x /= 10);
	while (top) putchar(OPT::buf[top--]);
	if (pt) putchar(aft);
}

const int maxn = 100010;
const ll INF = -1000000000ll;

int n;
int LOG[maxn];
ll p, q, r, ans = -3000000000000000010ll;
ll MU[maxn], ST[2][20][maxn];

ll ask(ci, ci, ci);

int main() {
	freopen("1.in", "r", stdin);
	qr(n); qr(p); qr(q); qr(r);
	for (rg int i = 1; i <= n; ++i) qr(MU[i]);
	for (rg int i = 0; (1 << i)  <= n; ++i) {
		LOG[1 << i] = i;
	}
	for (rg int i = 3; i <= n; ++i) if(!LOG[i]) LOG[i] = LOG[i - 1];
	for (rg int i = 0; i < 20; ++i)
		for (rg int j = 0; j < maxn; ++j)
			ST[1][i][j] = INF;
	for (rg int i = 0; i < 20; ++i)
		for (rg int j = 0; j < maxn; ++j)
			ST[0][i][j] = -INF;
	for (rg int i = 1; i <= n; ++i) ST[1][0][i] = ST[0][0][i] = MU[i];
	for (rg int i = 1; i < 20; ++i) {
		int len = (1 << i) - 1;
		for (rg int l = 1; l <= n; ++l) {
			int r = l + len; if (r > n) break;
			ST[0][i][l] = std::max(ST[0][i - 1][l], ST[0][i - 1][l + (1 << (i - 1))]);
			ST[1][i][l] = std::min(ST[1][i - 1][l], ST[1][i - 1][l + (1 << (i - 1))]);
		}
	}
	for (rg int i = 1; i <= n; ++i) {
		ans = std::max(q * MU[i] + p * ask(1, i, p < 0) + r * ask(i, n, r < 0), ans);
	}
	qw(ans, '\n', true);
	return 0;
}

ll ask(ci l, ci r, ci cur) {
	int len = r - l + 1;
	if (cur) return std::min(ST[1][LOG[len]][l], ST[1][LOG[len]][r - (1 << LOG[len]) + 1]);
	else return std::max(ST[0][LOG[len]][l], ST[0][LOG[len]][r - (1 << LOG[len]) + 1]);
}
```

## Summary

这次貌似也没啥好summary的……就是我好菜啊ST都调了半天

---

## 作者：Gaode_Sean (赞：3)

这里提供一个时间复杂度和空间复杂度均为 $O(n)$ 的做法，但不是 dp。

考虑枚举中间的数（即题目中的 $j$），$a_j \times q$ 即为定值，所以我们分别求 $a_i \times p$ 和 $a_k \times r$ 的最大值即可（此时 $1 \leq i \leq j$，$j \leq k \leq n$）。不难发现可以用前缀最大值（$a_i \times p$）与后缀最大值（$a_k \times r$）优化，这样可以做到 $O(n)$。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=1e5+1;
ll n,p,q,r,ans=-4e18,a[N],f[N],g[N];
int main()
{
	scanf("%lld%lld%lld%lld",&n,&p,&q,&r);
	for(ll i=1;i<=n;i++) scanf("%lld",&a[i]);
	f[1]=a[1]*p,g[n]=a[n]*r; 
	for(ll i=2;i<=n;i++) f[i]=max(f[i-1],a[i]*p);
	for(ll i=n-1;i>=1;i--) g[i]=max(g[i+1],a[i]*r);
	for(ll i=1;i<=n;i++) ans=max(ans,f[i]+a[i]*q+g[i]);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：JackWei (赞：2)

# 题意

------------

给 $n$ 个数，按顺序取三个 $a_i,a_j,a_k$ ，使 
  $p×a_i+q×a_j+r×a_k$ 最大。

注意 $1≤i≤j≤k≤n$ 。
# $O(n^3)$ 暴力解法


------------

for循环枚举 $a_i,a_j,a_k$ ，取 $max$ 。

或者是枚举 $a_i,a_j$ ，最后的 $a_k$ 取 $[j,n]$ 的最值，

如果 $r>0$ ， $a_k$ 取最大值；
反之， $a_k$ 取最小值。

这样显然会TLE的。

#  $O(n\log n)$ 解法


------------

在看看上面枚举两个数的算法，再想想可以只枚举一个数吗？

诶，好像可以诶！

我们枚举中间的 $a_j$ ，那么 $a_i$ 就是 $[1,j]$ 的最值， $a_k$ 是 $[j,n]$ 的最值。然后用ST算法或线段树，维护区间最值。（不会？戳这儿->[ST算法](https://www.jianshu.com/p/9a138ac52968)）

话不多说，上代码！

这里用的是ST算法，可以通过 $O(n\log n)$ 的时间复杂度作预处理后，在 $O(1)$ 的复杂度内查询区间最值。

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
using namespace std;

typedef long long ll;

const int N=100005;
const ll INF=9e18;

int n;
ll p,q,r;
ll a[N];
ll f[N][20][2]; //f[i][j][0]表示在子区间[i,i + 2^j - 1]的区间最大值，f[i][j][1]位最小值
int Log[N];
ll ans=-9e18;

void ST_prework()
{
	for(int i=1;(1<<i)<=n;i++) Log[1<<i]=i; //预处理log2(x)的值，方便查找
	for(int i=1;i<=n;i++) if(!Log[i]) Log[i]=Log[i-1];
	int t=Log[n]+1;
	for(int i=1;i<=n;i++) //初始化
		for(int j=1;j<=t;j++)
		{
			f[i][j][0]=-INF;
			f[i][j][1]=INF;
		}
	for(int i=1;i<=n;i++) f[i][0][0]=f[i][0][1]=a[i]; //赋初值
	for(int j=1;j<t;j++)
		for(int i=1;i<=n-(1<<j)+1;i++)
		{
			f[i][j][0]=max(f[i][j-1][0],f[i+(1<<(j-1))][j-1][0]);
			f[i][j][1]=min(f[i][j-1][1],f[i+(1<<(j-1))][j-1][1]); 
		}
}

long long ST_query(int l,int r,bool flag) //flag用于判断p/q/r大于0还是小于等于0
{
	int k=Log[r-l+1];
	if(flag) return max(f[l][k][0],f[r-(1<<k)+1][k][0]);
	return min(f[l][k][1],f[r-(1<<k)+1][k][1]);
}

int main()
{
	scanf("%d%lld%lld%lld",&n,&p,&q,&r);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	ST_prework();
	for(int i=1;i<=n;i++)
		ans=max(ans,q*a[i]+p*ST_query(1,i,p>0)+r*ST_query(i,n,r>0)); //取最大值
	printf("%lld\n",ans);
	return 0;
} 
```

# $O(n)$ 算法


------------

此时，我们换一种枚举思路，枚举到一个数 $a_x$ ，分别考虑：

当枚举到第 $x$ 个数时，

1. 当 $a_x$ 为 $a_i$ 时， $p×a_i$ 的最大值
2. 当 $a_x$ 为 $a_j$ 时， $p×a_i+q×a_j$ 的最大值
3. 当 $a_x$ 为 $a_k$ 时， $p×a_i+q×a_j+r×a_k$ 的最大值

考虑 $dp$ ，设 $dp[i][0/1/2]$ 表示枚举到第 $i$ 个数时，对应的三种情况的最大值，则发现，求出第一种情况的最大值时，再加上 $q×a_x$ 可以得到第二种情况的最大值，同理可以推出第三种情况的最大值，即：

$dp[i][0]=max(dp[i-1][0],p×a_i)$

$dp[i][1]=max(dp[i-1][1],dp[i][0]+q×a_i)$

$dp[i][2]=max(dp[i-1][2],dp[i][1]+r×a_i)$

由于$i$是递增的，所以存的最大值中取的 $i,j,k$ 一定满足   $i≤j≤k$ ，

所以最后答案为 $dp[n][2]$ 。

再观察，发现 $dp[i]$ 只与 $dp[i-1]$ 的值有关，所以直接压掉第一维，答案为 $dp[2]$ 。

时间复杂度为 $O(n)$ ，空间复杂度 $O(1)$ 。

```cpp
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;

typedef long long ll;

const ll INF=9e18;

int n;
int p,q,r;
ll dp[3];

int main()
{
	scanf("%d%d%d%d",&n,&p,&q,&r);
	dp[0]=dp[1]=dp[2]=-INF;
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		dp[0]=max(dp[0],(ll)x*p); //按顺序依次状态转移
		dp[1]=max(dp[1],dp[0]+(ll)x*q);
		dp[2]=max(dp[2],dp[1]+(ll)x*r);
	}
	printf("%lld\n",dp[2]);
	return 0;
}
```


---

## 作者：Fan_Tuan (赞：2)

# 题意
一个长度为n的序列，给定三个数 $p,q,r$，求序列中的三个数 $a_i,a_j,a_k$ 满足 $a_i\times p+a_j\times q+a_k\times r $的值最大。
# 思路
用线段树维护序列的最大值和最小值，枚举一遍 $a_j$ ，$q$与$a_j$相乘；当 $p\geqslant 0$ 时，求出区间 $[1 , j]$的最大值, 否则求出最小值， $p$与之相乘；当 $r\geqslant 0$ 时，求出区间 $[j , n]$的最大值, 否则求出最小值， $r$与之相乘，每次求出这三个乘积之和取$max$。
# 代码
```
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<iostream>
#include<string>
#define int long long
#define INF 3e18
using namespace std;

const int maxn = 1000005;
int n, p, q, r, a[maxn], sum = -INF;

struct node{
	int l, r, minn, maxx;
}tree[maxn << 2];

void pushup(int rt) {
	tree[rt].maxx = max(tree[rt << 1].maxx, tree[rt << 1 | 1].maxx);
	tree[rt].minn = min(tree[rt << 1].minn, tree[rt << 1 | 1].minn);
}

void build(int rt, int l, int r) {
	tree[rt].l = l;
	tree[rt].r = r;
	if (l == r) {
		tree[rt].maxx = tree[rt].minn = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(rt << 1, l, mid);
	build(rt << 1 | 1, mid + 1, r);
	pushup(rt);
}

int querymax(int rt, int L, int R) {
	int l = tree[rt].l;
	int r = tree[rt].r;
	if (l >= L && r <= R) return tree[rt].maxx;
	int mid = (l + r) >> 1, FT = -INF;
	if (mid >= L) FT = max(querymax(rt << 1, L, R), FT);
	if (mid < R) FT = max(querymax(rt << 1 | 1, L, R), FT);
	return FT;
}

int querymin(int rt, int L, int R) {
	int l = tree[rt].l;
	int r = tree[rt].r;
	if (l >= L && r <= R) return tree[rt].minn;
	int mid = (l + r) >> 1, FT = INF;
	if (mid >= L) FT = min(querymin(rt << 1, L, R), FT);
	if (mid < R) FT = min(querymin(rt << 1 | 1, L, R), FT);
	return FT;
}

signed main() {
	scanf("%lld%lld%lld%lld", &n, &p, &q, &r);
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	build(1, 1, n);
	for (int j = 1; j <= n; j++) {
		int ans1 = p < 0 ? querymin(1, 1, j) : querymax(1, 1, j);
		int ans2 = r < 0 ? querymin(1, j, n) : querymax(1, j, n);
		sum = max(sum, ans1 * p + a[j] * q + ans2 * r);
	}
	printf("%lld", sum);
	return 0;
}

```


---

## 作者：Nicrobot (赞：0)

我们考虑固定中间端点 $q$，这样就可以直接知道 $p,r$ 的范围分别是 $[1,q]$ 和 $[q,n]$ 。

考虑如何能取得最小？以 $p$ 为例，当 $p$ 为正数时显然取最大的最好，负数的时候若能取负数肯定取最小的那个，这样负负得正乘起来最大；没有负数时也应该取最小的那个，这样结果仍然更大。$p=0$ 不必考虑反正怎么乘就是 $0$。

这样我们将问题转化成：固定 $p$ ，求 $\max_{i=1}^p a_ i $ 或 $\min_{i=1}^p a_ i $ 以及  $\max_{i=p}^n a_ i $ 或 $\min_{i=p}^n a_ i $。

多次区间最值，需要使用线段树，ST 表吗？其实不用。我们发现维护的区间要么左端点为 $1$ 要么右端点为 $n$。设 $f(i)$ 表示前 $i$ 个数的最小值，则我们有 $f(1)=a_1 $ 并且 $\forall 2 \le i \le n,f(i)=\min(f(i-1),a_i)$ ，可以在 $O(n)$ 的时间内递推算出。类似地，我们设 $f'(i)$ 为 $[i,n]$ 的最小值，有 $f(n)=a_n $ 并且 $\forall 1 \le i < n,f(i)=\min(f(i+1),a_i)$。最大值同理。这样就在 $O(n)$ 的时间内维护了最大最小值。

然后照着方法算就行了。注意使用 `long long`。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int N = 1e5 + 10;

ll n, p, q, r, a[N];
ll mx1[N], mx2[N], mi1[N], mi2[N];
//[1,i]最大，[1,i] 最小，[i,n] 最大，[i,n] 最小。

int main() {
	cin >> n >> p >> q >> r;
	for (int i = 1; i <= n; i++)	
		cin >> a[i];
	//维护最值
	mx1[0] = mx2[n + 1] = -4e18;
	mi1[0] = mi2[n + 1] = 4e18;
	for (int i = 1; i <= n; i++) {
		mx1[i] = max(mx1[i - 1], a[i]);
		mi1[i] = min(mi1[i - 1], a[i]);
	}
	for (int i = n; i; i--) {
		mx2[i] = max(mx2[i + 1], a[i]);
		mi2[i] = min(mi2[i + 1], a[i]);
	}
    
	ll ans = -4e18; //注意要足够小。
	//枚举 q
	for (int i = 1 ; i <= n; i++) {
		ll x, y, z;
		x = p * ((p < 0) ? mi1[i] : mx1[i]); // p
		y = r * ((r < 0) ? mi2[i] : mx2[i]); // r
		z = q * a[i]; // q
		ans = max(ans, x + y + z); // 取最大
	}
	cout << ans << endl;
 	return 0;
} 


``

---

## 作者：123hh2 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF855B)

---

### 题目大意

给定三个数 $p$，$q$，$r$ $(- 10 ^ 9 \le p,q,r \le 10 ^ 9)$ ，和一个大小为 $n(1 \le n \le 10 ^ 5)$ 数组 $a$。

求找出三个数 $a_i$，$a_j$，$a_k$ $(1 \le i \le j \le k \le n,- 10 ^ 9 \le a_i \le 10 ^ 9)$ 使得 $p \times a_i + q \times a_j + r \times a_k$ 的值最大。

---

### 分析

考虑如何让 $p \times a_i + q \times a_j + r \times a_k$ 最大。

可以设一个状态为 $dp[i][j]$ 表示考虑数组第 $j$ 个数，给定的三个数的第 $i$ 个数的时候能取到的最大值，然后因为 $i,j,k$ 满足非严格递增，所以转移的时候需要考虑顺序，即先考虑第一个数，然后再考虑第二个数和第三个数。

那么状态转移方程就有了：

$dp[0][i]=\max(dp[0][i-1],p \times a[i])$

$dp[1][i]=\max(dp[1][i-1],\max(dp[0][i-1] + q \times a[i],dp[0][i] + q \times a[i]))$

$dp[2][i]=\max(dp[2][i-1],\max(dp[1][i-1] + r \times a[i],dp[1][i] + r \times a[i]))$

然后初始化 dp 数组为负无穷，顺序转移即可，复杂度为 $O(n)$，记得开 ```long long```！

---

### 代码

```cpp
//you have no way to return
#include<bits/stdc++.h>
// #include<Windows.h>
#define ri register
#define in inline
#define int long long
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();while(ch>'9'||ch<'0') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}return x*f;
}
void write(int x) {if(x<0) x=-x,putchar('-');if(x>9) write(x/10);putchar(x%10+'0');}
const int maxn=1e5+1;
int dp[3][maxn];
signed main()
{
	int n=read(),p=read(),q=read(),r=read();
	for(ri int i=0;i<=n;i++) for(ri int j=0;j<=2;j++) dp[j][i]=-8e18;
	for(ri int i=1;i<=n;i++)
	{
		int x=read();
		dp[0][i]=max(dp[0][i-1],p*x);
		dp[1][i]=max(dp[1][i-1],dp[0][i-1]+q*x);
		dp[1][i]=max(dp[1][i],dp[0][i]+q*x);
		dp[2][i]=max(dp[2][i-1],dp[1][i-1]+r*x);
		dp[2][i]=max(dp[2][i],dp[1][i]+r*x);
		// write(dp[0][i]),putchar(' '),write(dp[1][i]),putchar(' '),write(dp[2][i]),puts("");
	}
	write(dp[2][n]);
	return 0;
}
```

---

## 作者：Coros_Trusds (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15558877.html)

# 题目大意

给定 $n,p,q,r$，并且给出 $n$ 个数。

在这些数中找 $i,j,k(1\le i\le j\le k\le n)$，求出 $\max\{p\times a_i+q\times a_j+r\times a_k\}$。

# 题目分析

一道小清新 $\rm DP$ 题。

设 $dp[idx][0]$ 表示前 $idx$ 个数的 $\max\{p\times a_i\}(1\le i\le idx)$。

$dp[idx][1]$ 表示前 $idx$ 个数的 $\max\{p\times a_i+q\times a_j\}(1\le i\le j\le idx)$。

$dp[idx][2]$ 表示前 $idx$ 个数的 $\max\{p\times a_i+q\times a_j+r\times a_k\}(1\le i\le j\le k\le idx)$。

于是顺推即可：

$dp[idx][0]=\max\{dp[idx-1][0],p\times a_i\}$

$dp[idx][1]=\max\{dp[idx-1][1],dp[idx][0]+q\times a_i\}$

$dp[idx][2]=\max\{dp[idx-1][2],dp[idx][1]+r\times a_i\}$

初始化：

+ $dp[idx][0]=p\times a_1$

+ $dp[idx][1]=p\times a_1+q\times a_1$

+ $dp[idx][2]=p\times a_1+q\times a_1+r\times a_1$

最后答案就是 $dp[n][2]$。

时间复杂度为 $\operatorname{O}(N)$。

注意开 $\rm long~long$。

# 代码

```cpp
//2021/11/14

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <cstdio>

#include <climits>//need "INT_MAX","INT_MIN"

#define int long long

#define enter() putchar(10)

#define debug(c,que) cerr<<#c<<" = "<<c<<que

#define cek(c) puts(c)

#define blow(arr,st,ed,w) for(register int i=(st);i<=(ed);i++)cout<<arr[i]<<w;

#define speed_up() std::ios::sync_with_stdio(false)

namespace Newstd
{
	inline int read()
	{
		char c;
		bool flag=false;
		while((c=getchar())<'0' || c>'9')
		{
		    if(c=='-') flag=true;
		}
		int res=c-'0';
		while((c=getchar())>='0' && c<='9')
		{
		    res=(res<<3)+(res<<1)+c-'0';
		}
		return flag?-res:res;
	}
	inline void print(int x)
	{
		if(x<0)
		{
			putchar('-');x=-x;
		}
		if(x>9)
		{
			print(x/10);
		}
		putchar(x%10+'0');
	}
}

using namespace Newstd;

using namespace std;

const int ma=100005;

int a[ma];

int dp[ma][3];
/*
dp[i][0]:前 i 个数中取 p*a_i 最大值
dp[i][1]:前 i 个数中取 p*a_i+q*a_j 最大值
dp[i][2]:前 i 个数中取 p*a_i+q*a_j+r*a_k 最大值 
*/

int n,p,q,r;

#undef int

int main(void)
{
	#define int long long
	
	n=read(),p=read(),q=read(),r=read();
	
	for(register int i=1;i<=n;i++)
	{
		a[i]=read();
	}
	
	dp[1][0]=p*a[1];
	
	for(register int i=2;i<=n;i++)
	{
		dp[i][0]=max(dp[i-1][0],p*a[i]);
	}
	
	dp[1][1]=p*a[1]+q*a[1];
	
	for(register int i=2;i<=n;i++)
	{
		dp[i][1]=max(dp[i-1][1],dp[i][0]+q*a[i]);
	}
	
	dp[1][2]=p*a[1]+q*a[1]+r*a[1];
	
	for(register int i=2;i<=n;i++)
	{
		dp[i][2]=max(dp[i-1][2],dp[i][1]+r*a[i]);
	}
	
	printf("%lld\n",dp[n][2]);
	
	return 0;
}
```

---

