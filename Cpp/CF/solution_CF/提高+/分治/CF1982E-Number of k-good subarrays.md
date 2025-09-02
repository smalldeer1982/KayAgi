# Number of k-good subarrays

## 题目描述

Let $ bit(x) $ denote the number of ones in the binary representation of a non-negative integer $ x $ .

A subarray of an array is called  $ k $ -good if it consists only of numbers with no more than $ k $ ones in their binary representation, i.e., a subarray $ (l, r) $ of array $ a $ is good if for any $ i $ such that $ l \le i \le r $ condition $ bit(a_{i}) \le k $ is satisfied.

You are given an array $ a $ of length $ n $ , consisting of consecutive non-negative integers starting from $ 0 $ , i.e., $ a_{i} = i $ for $ 0 \le i \le n - 1 $ (in $ 0 $ -based indexing). You need to count the number of  $ k $ -good subarrays in this array.

As the answer can be very large, output it modulo $ 10^{9} + 7 $ .

## 说明/提示

For the first test case $ a = [0, 1, 2, 3, 4, 5] $ , $ k = 1 $ .

To find the answer, let's write all the numbers in binary representation:

 $ $$$a = [\color{green}{000}, \color{green}{001}, \color{green}{010}, \color{red}{011}, \color{green}{100}, \color{red}{101}] $ $ </p><p>From this, it can be seen that the numbers  $ 3 $  and  $ 5 $  have  $ 2 \\ge (k = 1) $  ones in their binary representation, so the answer should include all subarrays that do not contain either  $ 3 $  or  $ 5 $ , which are the subarrays (in  $ 0 $ -based indexing): ( $ 0 $ ,  $ 0 $ ), ( $ 0 $ ,  $ 1 $ ), ( $ 0 $ ,  $ 2 $ ), ( $ 1 $ ,  $ 1 $ ), ( $ 1 $ ,  $ 2 $ ), ( $ 2 $ ,  $ 2 $ ), ( $ 4 $ ,  $ 4$$$).

## 样例 #1

### 输入

```
10
6 1
16 2
1 1
3 1
31 3
14 1
1337 5
100000 20
795569939321040850 56
576460752303423268 59```

### 输出

```
7
35
1
6
155
8
7323
49965
741136395
66679884```

# 题解

## 作者：SFlyer (赞：21)

设 $sol(n,k)$ 为答案。（注意，是 $0\sim n-1$ 的！）那么，我们 $sol(n,k)$ 可以通过 $sol(mx,k)$ 和 $sol(n-mx,k-1)$ 算出来，其中 $mx$ 是小于 $n$ 的最大 $2$ 次幂。（很好理解，大于等于 $mx$ 的就会有一位固然是 $1$，就会是 $k-1$。）设 $mx=2^c$。

问题是怎么算。除了内部的，还有一个端点在左边一个端点在右边的。官方题解是维护了三个值，很复杂。有没有直接算的方法？

我们发现，如果 $c>k$，那么左边最后一个就会有大于 $k$ 个 $1$，没有贡献，所以必须 $c\le k$。这个时候左边所有的都满足，只需要计算右边的。右边的到了 $2^k-1$ 也不行，因为这样也超过了（当然要和长度取最小值）。所以我们算出了右边的贡献 $s=\min(2^c-1,n-2^c)$。那么，答案就要多加上 $s\cdot 2^c$。

直接记忆化搜索即可，复杂度是 $\mathcal{O}(k \log n)$ 的。代码非常短。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll mod = 1e9+7;

map<pair<ll,ll>,ll> mp;

ll sol(ll n,ll k){
	if (k==0 || n==1){
		return 1;
	}
	if (mp.count({n,k})){
		return mp[{n,k}];
	}
	ll c=0;
	while ((1ll<<c+1)<n){
		c++;
	}
	ll l=sol(1ll<<c,k),r=sol(n-(1ll<<c),k-1);
	ll ans=l+r;
	if (c<=k){
		ll s=min((1ll<<k)-1,n-(1ll<<c));
		ans+=s%mod*((1ll<<c)%mod)%mod;
	}
	mp[{n,k}]=ans%mod;
	return ans%mod;
}

void solve(){
	ll n,k;
	cin>>n>>k;
	cout<<sol(n,k)<<"\n";
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t;
	cin>>t;
	while (t--){
		solve();
	}
	return 0;
}
```

---

## 作者：yshpdyt (赞：10)

## 题意
给定一个长为 $n(n\le10^{18})$ 的数组满足 $a_i=i-1$，记 $bit(x)$ 表示 $x$ 的二进制中 $1$ 的数量，求满足 $\forall i \in[l,r]$，$bit(a_i)\le k$ 的区间数量，$k\le60$。

## Sol
喵喵题，被官方题解震撼到了。

考虑一个化简的题目：一个 $01$ 序列，求有多少个区间使得区间内全是 $1$。

对于这个问题，可以考虑分治解决，类似线段树合并区间一样，先分别统计左右区间的贡献，再统计跨过中点的贡献。

记 $f(l,r,k)$ 为一个函数，其返回值为区间 $[l,r]$ 内，$bit(a_i)\le k$ 的极长连续合法前缀长度 $lc$，极长连续合法后缀长度 $rc$，以及区间数量 $ans$。

定义 $f(l,r,k)=f(l,t,k)+f(t,r,k)$ ，意为合并两个区间的贡献。

直接分治的时间复杂度无法接受，考虑一种合法的划分区间方案。

接下来比较巧妙，我们记 $m$ 表示最大的 $2^m< n $，然后便有：
$$f(0,n-1,k)=f(0,2^m-1,k)+f(2^m,n-1,k)$$

注意到 $[2^m,n-1]$ 这段区间的数的二进制最高位都是 $m$，而我们要求最多只能有 $k$ 个二进制位为 $1$，去掉共同的最高位，便要求有 $k-1$ 个最高位。

于是乎:
$$f(0,n-1,k)=f(0,2^m-1,k)+f(0,n-2^m-1,k-1)$$

我们每次都可以把右边的函数按这样的方式展开，如同二进制分解一样，由于 $l=0$ 恒成立，不妨把区间变为长度，于是有：

$$f(n,k)=f(2^m,k)+f(n-2^m,k-1)$$

注意到如果取 $n$ 为 $2^{m+1}$，便有：

$$f(2^{m+1},k)=f(2^m,k)+f(2^m-1,k-1)$$

不妨记 $g(m,k)=f(2^m,k)$，便有递推式：

$$g(m,k)=g(m-1,k)+g(m-1,k-1)$$

我们可以通过动态规划的方法预处理出 $g(m,k)$ ，边界条件为 $g(i,0)=\{lc,rc,ans\}=\{1,0,1\}$，$g(0,i)=\{1,1,1\}$。

这部分的时间复杂度为 $O(k \log V )$。

递归便变成了：
$$f(n,k)=g(m,k)+f(n-2^m,k-1)$$

于是这道题就做完了，时间复杂度  $O(k \log V +T\log V)$。
##  Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 200005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=1e9+7;
const ll inf=1e18;
const double eps=1e-6;

struct node{
    ll l,r,ans,len;
    friend node operator+(const node &a,const node &b){
        node c={a.l%mod,b.r%mod,(a.ans+b.ans)%mod,(a.len+b.len)%mod};
        if(a.l==a.len)c.l=(a.l+b.l)%mod;
        if(b.r==b.len)c.r=(b.r+a.r)%mod;
        c.ans=(c.ans+(a.r*b.l)%mod)%mod;
        return c;
    }
}f[67][67];

node calc(ll n,ll k){
    if(n==0)return {0,0,0,0};
    if(k==0)return {1,0,1,n};
    ll t=0,x2=1;
    while(x2*2ll<=n)t++,x2<<=1;
    return f[t][k]+calc(n-x2,k-1);
}
void sol(){
    ll n,k;
    cin>>n>>k;
    cout<<calc(n,k).ans<<endl;
}
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    for(int i=0;i<=60;i++)f[0][i]={1,1,1,1};
    for(int i=1;i<=60;i++){
        f[i][0]={1,0,1,(1ll<<i)};
        for(int j=1;j<=60;j++){
            f[i][j]=f[i-1][j]+f[i-1][j-1];
        }
    }
    ll ttt;
    cin>>ttt;
    while(ttt--)sol();
    return 0;
}

```

---

## 作者：OtterZ (赞：2)

# 1.题意
给定整数 $n$，求出长为 $n$ 的数列 $a_i = i(0 \leq i < n)$ 的子序列数，使子序列中所有数二进制位不大于 $0$。
# 2.特殊情况动规
我们发现 $n = 2^m$ 的情况非常好算，可以用 `DP`，设 $dp_{i,j}$ 为 $n = 2^i$ 时二进制数最多正好为 $j$ 的子序列数，则:

$$
dp_{i,j} = dp_{i - 1,j} + dp_{i - 1,j - 1} +  \begin{cases}
  0 & j < i - 1 \\
  2 ^ {i - 1} \times(2 ^ {i - 1} - 1) & j = i - 1 \\
  2 ^ {i - 1} & j = i
\end{cases}
$$

另外 $dp_{i,i} = 2 ^ i$ 也是对的，这样我们会得到答案为 $\sum_{0 \leq j \leq k}dp_{m,j}$。
# 3.一般情况分治
每次当 $n < 2^m$ 时，若 $n \leq 2 ^ {m - 1}$,考虑缩小 $m$，否则分为两部分：

1. $0 \leq i < 2^{m - 1}$，结果同上；
2. $2 ^ {m - 1} \leq i < n$，与 $n' = n - 2 ^ {m - 1},k' = k - 1$ 的情况相同。
3. 当 $m - 1 \leq k$ 时记得加上 $2^{m - 1}\times (n - 2^{m + 1})$

这样我们就用 $\operatorname{O}(k\log n)$ 的方法切掉了这题。
# 4.代码
```
#include<cstdio>
using namespace std;
long long dp[69][69];
const int mod = 1e9 + 7;
void init(){
	dp[0][0] = 1;
	for(int i = 1; i <= 63; i ++){
		dp[i][0] = 1;
		for(int j = 1; j < i; j ++){
			dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1]) % mod;
		}
		dp[i][i] = 1ll * (1ll << i) % mod;
		dp[i][i - 1] = (dp[i][i - 1] + 1ll * (1ll << i - 1) % mod * ((1ll * (1ll << i - 1) - 1) % mod) % mod) % mod;
	}
}
long long srh(long long n,int s,int k){
	//printf("%lld %d %d\n",n,s,k);
	if(k < 0)
		return 0;
	if(k == 0 || n == 0)
		return 1;
	if(s == 0)
		return 1;
	long long ret = 0;
	if(n == (1ll << s) - 1){
		for(int i = 0; i <= k; i ++){
			//printf(" %d\n",dp[s - 1][i]);
			ret = (ret + dp[s][i]) % mod;
		}
	}
	else if(n >= (1ll << s - 1)){
		for(int i = 0; i <= k && i < s; i ++){
			ret = (ret + dp[s - 1][i]) % mod;
			if(i == s - 1){
				ret = (ret + 1ll * (1ll << s - 1) % mod * ((n - (1ll << s - 1) + 1) % mod) % mod) % mod;
			//printf(" %lld\n",1ll * (1ll << s - 1) % mod * ((n - (1ll << s - 1) + 1) % mod) % mod);
			}
		}
		ret = (ret + srh(n - (1ll << s - 1),s - 1,k - 1)) % mod;
	}
	else{
		ret = srh(n,s - 1,k);
	}
	//printf("%lld\n",ret);
	return ret;
}
int k,t;
long long n;
int main(){
	scanf("%d",&t);
	init();
	while(t--){
		scanf("%lld %d",&n,&k);
		printf("%d\n",srh(n - 1,63,k));
	}
	return 0;
}
```

---

## 作者：红黑树 (赞：2)

[可能更好的阅读体验](https://rbtr.ee/CF1982E)

## [题意](https://codeforces.com/contest/1982/problem/E)
给定 $n$ 和 $k$，生成一个长度为 $n$ 的数组 $a_i = i - 1$，如果一段区间 $\left[l, r\right]$ 是好的，仅当对于任意 $l \leq i \leq r$，都满足 $a_i$ 二进制表示中为 $1$ 的位的个数不超过 $k$。

找到 $a$ 中好的区间的个数，对 $10^9 + 7$ 取模。

$1 \leq n \leq 10^{18}, 1 \leq k \leq 60$

## 题解
我们对于一个区间维护以下变量。

* `tar` 表示此区间中有多少个好区间
* `l` 表示从区间左边数起，有多少个数的二进制表示中为 $1$ 的位的个数不超过 $k$。
* `r` 表示从区间右边数起，有多少个数的二进制表示中为 $1$ 的位的个数不超过 $k$。
* `len` 表示区间长度

这样，我们可以合并两个区间。`l`，`r` 和 `len` 的维护是简单的，`tar` 需要把两边相加，再加上跨两个区间的好区间个数 `l.r * r.l`。

```cpp
struct foo {
  tp l, r, tar, len;
  
  foo() = default;
  foo(tp l, tp r, tp t, tp len) : l(l), r(r), tar(t), len(len) {}
  
  foo operator+(foo o) {
    if (len == 0) return o;
    if (o.len == 0) return *this;
    tp bar = l, baz = o.r;
    if (l == len) bar += o.l;
    if (o.r == o.len) baz += r;
    return foo(bar, baz, (tar + o.tar + r % mod * (o.l % mod)) % mod, len + o.len);
  }
};
```

这样我们可以计算出 $n$ 为二的幂时的答案。

---
如果 $n$ 不是二的幂，我们断言可以用 $\mathcal O\left(\log n\right)$ 个长度为二的幂的区间拼出来。

考虑当前 $a$ 数组的二进制中最高有效位，一定是

$$0, 0, \ldots, 0, 1, 1, \ldots 1$$

，其中 $0$ 的个数为二的幂，且长度至少有一半。我们再考虑右边的 $1$。忽略最高位的 $1$，然后将 $k$ 减一，就是一个完全相同的子问题。

这样我们就用一个区间，将 $n$ 除以了 $2$。

最终时间复杂度为 $\mathcal O\left(k\log n\right)$。

## 代码
```cpp
/* Please submit with C++17! It's best to use C++20 or higher version.
 * No header file and no RBLIB (https://git.rbtr.ee/root/Template).
 * By Koicy (https://koicy.ly)
 * Email n@rbtr.ee
 * I've reached the end of my fantasy.

         __    __                             __         _
   _____/ /_  / /_________  ___              / /______  (_)______  __
  / ___/ __ \/ __/ ___/ _ \/ _ \   ______   / //_/ __ \/ / ___/ / / /
 / /  / /_/ / /_/ /  /  __/  __/  /_____/  / ,< / /_/ / / /__/ /_/ /
/_/  /_.___/\__/_/   \___/\___/           /_/|_|\____/_/\___/\__, /
                               SIGN                         /___*/
#ifndef XCODE
constexpr bool _CONSOLE = false;
#else
constexpr bool _CONSOLE = true;
#endif
#define __NO_MAIN__ false
#define __ENABLE_RBLIB__ true
constexpr bool _MTS = true, SPC_MTS = false;
constexpr char EFILE[] = "";
#define FULL(arg) arg.begin(), arg.end()
#define dor(i, s, e) for (tp i = s, $##i =(s)<(e)?1:-1,$e##i=e;i!=$e##i;i+=$##i)
#define gor(i, s,e)for(tp i=s,$##i=(s)<(e)?1:-1,$e##i=(e)+$##i;i!=$e##i;i+=$##i)

// :/

signed STRUGGLING([[maybe_unused]] unsigned long TEST_NUMBER) {
  constexpr tp mod = 1e9 + 7;
  struct foo {
    tp l, r, tar, len;
    
    foo() = default;
    foo(tp l, tp r, tp t, tp len) : l(l), r(r), tar(t), len(len) {}
    
    foo operator+(foo o) {
      if (len == 0) return o;
      if (o.len == 0) return *this;
      tp bar = l, baz = o.r;
      if (l == len) bar += o.l;
      if (o.r == o.len) baz += r;
      return foo(bar, baz, (tar + o.tar + r % mod * (o.l % mod)) % mod, len + o.len);
    }
  };
  tp n, k; bin >> n >> k;
  tp lg = 1;
  while ((ONE << lg) < n) ++lg;
  vector f(lg + 1, vector<foo>(k + 1));
  gor(i, 0, k) f[0][i] = foo(1, 1, 1, 1);
  gor(i, 1, lg) f[i][0] = foo(1, 0, 1, ONE << i);
  gor(i, 1, lg) {
    gor(j, 1, k) f[i][j] = f[i - 1][j] + f[i - 1][j - 1];
  }
  foo tar = foo(0, 0, 0, 0);
  gor(i, lg, 0) {
    if (n >> i & 1 && k >= 0) tar = tar + f[i][k--];
  }
  bin << tar.tar << '\n';
  return 0;
}

void MIST() {
}

// :\ */
```

---

## 作者：COsm0s (赞：1)

考虑 dp。

对于所有长度为 $k$ 的数，$p$ 为数中 $1$ 的个数，其答案为 $f(k,p)$ 满足 $f(k,p)=f(k-1,p)+f(k-1,p-1)$。

这里 $+$ 为一种合并，下文会解释。

这是因为一个二进制数其末位只会为 $0,1$。

当末位为 $0$ 时，减去末位的二进制数长度为 $k - 1$，而 $1$ 的个数仍为 $p$。

同理，当末位为 $1$ 时，长度为 $k - 1$，$1$ 的个数仍为 $p - 1$.

故而从这两个状态转移。

对于任意数 $x$，在 $p$ 位上为 $1$，则加上第 $p$ 位的贡献，即 $f(p,cur)$，而将 $cur$ 的贡献加上后，再 $cur-1\to cur$，使得下一次算贡献时将这次已经贡献过的 $1$ 去掉。

再回来看 $f(k,p)$ 的合并方式。

观察到题目中 $[l,r]$ 为一个连续区间，我们想到一个类似的东西：最大连续子序列。

在用线段树实现时，我们用 $lc,rc,len,sum,ans$ 表示左前缀最大答案，右前缀最大答案，区间长度，区间和和区间答案。

同理我们通过 $lc,rc,len,ans$ 表示左前缀最大答案，右前缀最大答案，区间长度，区间答案。

其 $lc,rc,len$ 的转移方式都与最大连续子序列一致，而 $ans$ 的计算方式有些许区别。

即左区间 $ans$，右区间 $ans$ 之和加上两者公共部分。

显然公共时区间左端点在左区间，右端点在右区间。

那么 $ans$ 即为左区间 $rc$ 与右区间 $lc$ 之积。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 60 + 5, base = 17, mod = 1e9 + 7;
struct node {
	int lc, rc, len, ans;
	node() {}
	node(int lc, int rc, int len, int ans) :
		lc(lc), rc(rc), len(len), ans(ans) {}
};
node operator + (const node& x, const node& y) {
	node c;
	c.len = x.len + y.len, c.len %= mod;
	c.lc = x.lc, c.rc = y.rc;
	if(x.lc == x.len) c.lc = x.len + y.lc;
	if(y.rc == y.len) c.rc = y.len + x.rc;
	c.lc %= mod, c.rc %= mod;
	c.ans = x.ans + y.ans + (x.rc * y.lc) % mod;
	c.ans %= mod;
	return c;
}
node f[N][N];
node calc(int x, int y) {
	if(y >= 0) return f[x][y];
	return node(0, 0, 1ll << x, 0);
}
void Solve() {
	int n, k;
	node ans = node(0, 0, 0, 0);
	cin >> n >> k;
	for(int i = 60, opt = k; i >= 0; i --) 
		if(n >> i & 1) ans = (ans + calc(i, opt)), ans.ans %= mod, opt --;
	cout << ans.ans << '\n';
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	int T = 1;
	cin >> T;
	for(int i = 0; i < N; i ++)
		f[0][i] = node(1, 1, 1, 1);
	for(int i = 1; i < N; i ++) {
		for(int j = 0; j < N; j ++) {
			f[i][j] = calc(i - 1, j) + calc(i - 1, j - 1);
		}
	}
	while (T --) {
		Solve();
	}
	return 0;
}
```

---

## 作者：TTpandaS (赞：1)

令 $f(l,r,k,0/1/2)$ 表示区间 $[l,r]$ 满足 $bit(i) \leq k$ 的最长前缀/最长后缀/对答案的贡献。

考虑如何合并两个区间 $[l,mid]$ 和 $[mid+1,r]$。

对于最长前缀，如果区间 $[l,mid]$ 的最长前缀为其整个区间，即 $f(l,mid,k,0)=mid-l+1$，那么需要将区间 $[mid+1,r]$ 的最长前缀包含进来，即 $f(l,r,k,0)=(mid-l+1)+f(mid+1,r,k,0)$。否则即为区间 $[l,mid]$ 的最长前缀，即 $f(l,r,k,0)=f(l,mid,k,0)$。

对于最长后缀，同理可得：如果 $f(mid+1,r,k,1)=r-mid$，那么 $f(l,r,k,1)=f(l,mid,k,1)+(r-mid)$。否则 $f(l,r,k,1)=f(mid+1,r,k,1)$。

对于对答案的贡献，有两边单独的贡献和包含 $mid$ 的贡献两部分组成。两边单独的贡献即为 $f(l,mid,k,2)+f(mid+1,r,k,2)$。包含 $mid$ 的贡献即区间 $[l,mid]$ 的后缀能与区间 $[mid+1,r]$ 的前缀能匹配的数量，即 $f(l,mid,k,1) \times f(mid+1,r,k,0)$。

考虑基于什么进行分治。对于这类二进制相关的题目，通常基于 lowbit 或 highbit 进行分治。

考虑基于 highbit 进行分治能带来什么性质。

对于区间 $[0,n-1]$，我们找到 $n$ 的 highbit $2^m$，那么 $f(0,n-1,k)=f(0,2^m-1,k)+f(2^m,n-1,k)$。（此处 `+` 表示将两个区间合并，下文同）

由于 $2^m$ 是 $n$ 的 highbit，对于区间 $[2^m,n-1]$，满足第 $m$ 位一定为 $1$，所以 $f(2^m,n-1,k)=f(0,n-2^m-1,k-1)$。

因此可以得到 $f(0,n-1,k)=f(0,2^m-1,k)+f(0,n-2^m-1,k-1)$，由于区间左端点此时都为 $0$，所以将第一维省略，可得 $f(n-1,k)=f(2^m-1,k)+f(n-2^m-1,k-1)$。

此时该式的时间复杂度仍然为 $O(n \log n)$，进一步考虑性质。

发现 $f(2^m-1,k)$ 这一部分与 $n$ 无关，可以进行预处理。可得 $f(2^m-1,k)=f(2^{m-1}-1,k)+f(2^{m-1}-1,k-1)$。

此时每次分治都能将区间变为二进制下数位的一部分，所以现在的时间复杂度为 $O(\log n)$，可以通过。

---

## 作者：KingPowers (赞：0)

首先注意到当 $n=2^p$ 的时候问题是简单的，令 $f(n,k)$ 表示 $[0,2^n)$ 内满足条件的区间个数，考虑 $f(n,k)$ 如何求得，发现可以由 $f(n-1,k)$ 和 $f(n-1,k-1)$ 合并过来，因为对于 $[2^{n-1},2^n)$ 以内的数除了限制了最高位为 $1$ 以外和 $[0,2^{n-1})$ 的情况是一样的。当然这个合并你需要多维护一些信息，因为是统计区间个数，所以合并时可能会新合并出一个连续段，需要记录下前缀和后缀的极长合法段长度。

对于原问题，考虑分治。令 $\text{solve}(n,k)$ 表示 $[0,n)$ 内的合法区间个数，我们沿用上面的思路，记 $x$ 为 $n$ 的 $\text{higbit}$，那么 $[0,x)$ 内的答案我们可以预处理上面的 $f$ 然后直接查表，而 $[x,n)$ 的部分同样相当于多限制了最高位为 $1$ 的子问题，调用 $\text{solve}(n-x,k-1)$ 即可。

因为我们分治每次只会单侧递归，而且问题规模至少减半，所以每次查询的复杂度为 $O(\log n)$。

代码里省略了个人的取模类。


```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i, a, b) for(int i = (a); i <= (b); i++)
#define Rof(i, a, b) for(int i = (a); i >= (b); i--)
#define deb(x) cerr << #x"=" << x << '\n';
using namespace std;
const int N = 5e5 + 5, mod = 1e9 + 7;
const mint inv2 = (mod + 1) / 2;
struct node{
	mint len, pre, suf, ans;
}f[65][65];  //f[i][j] [0,2^i) 内限制 <=k 的信息
node operator+(const node &a, const node &b){
	node res;
	res.len = a.len + b.len;
	res.ans = a.ans + b.ans;
	res.pre = a.pre; res.suf = b.suf;
	if(a.pre == a.len) res.pre += b.pre;
	if(b.suf == b.len) res.suf += a.suf;
	mint x = a.suf, y = b.pre, z = x + y;
	res.ans -= x * (x + 1) * inv2;
	res.ans -= y * (y + 1) * inv2;
	res.ans += z * (z + 1) * inv2;
	return res;
}
void init(){
	For(i, 0, 60){
		f[0][i] = {1, 1, 1, 1};
		f[i][0] = {1ll << i, 1, i == 0, 1};
	}
	For(i, 1, 60) For(j, 1, 60)
		f[i][j] = f[i - 1][j] + f[i - 1][j - 1];
}
node solve(int n, int k){
	if(n == 0) return {0, 0, 0, 0};
	if(k == 0) return {n, 1, 0, 1};
	int t = __lg(n), hbit = 1ll << t;
	return f[t][k] + solve(n - hbit, k - 1);
}
void Solve(){
	int n, k; cin >> n >> k;
	cout << solve(n, k).ans << '\n';
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	init(); int T; cin >> T;
	while(T--) Solve();
	return 0;
}
```

---

## 作者：Z1qqurat (赞：0)

唔，好神奇的题~

想到维护合法连续段，发现 $k$ 的限制像是一个可以划分的东西。考虑分治，$f(n,k)$ 把 $k$ 放下去，从 $2^m$ 劈开，其中 $m$ 是满足 $2^m<n$ 的最大 $m$。那么 $f(n,k)$ 的信息其实就可以用两个区间，$[0,2^m),[2^m,n)$ 拼起来。考虑到 $m$ 的特殊性质，$[2^m,n)$ 内的数在二进制第 $m$ 位上一定都是 $1$，所以就相当于 $f(n-2^m,k-1)$。所以可以用 $f(0,2^m),f(n-2^m,k-1)$ 凑出 $f(n,k)$ 的答案。

这时候想想 $f$ 应该记录下来那些信息呢？用两段区间的信息来更新 $f$，需要考虑到单独的贡献和拼起来的贡献，所以需要记录这一段区间内的答案 $ans$，如果拼起来会形成一段更长的可选区间的话也要记录，所以还要记录靠近区间左/右端点的最长合法段 $l,r$，合并的时候需要同时维护这三个信息，是不是很像维护连续段的“左中右”线段树来着~

但是这么想，复杂度还是 $\mathcal{O}(n)$。观察到每次裂出的两段中，左边的一段 $f(2^m,k)$ 很固定，因为 $f(2^m,k)$ 可以由 $f(2^{m-1},k),f(2^{m-1},k-1)$ 凑起来，所以如果把形如 $f(2^m,k)$ 的都记忆化下来，就可以做到只要右边一边的递归了，这样可以做到 $\mathcal{O}(\log n)$。实现中有一个技巧就是 `__builtin_clz` 可以用来求 $m$，具体可以看官解代码~

试图总结这个题的套路，但是发现我不太知道有啥规律，想了想可能还是得见多识广吧QwQ。

---

