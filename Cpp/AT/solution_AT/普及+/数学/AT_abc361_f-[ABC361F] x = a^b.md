# [ABC361F] x = a^b

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc361/tasks/abc361_f

$ 1 $ 以上 $ N $ 以下の正整数 $ x $ であって、ある正整数 $ a $ と **$ 2 $ 以上の** 正整数 $ b $ を用いて $ x=a^b $ と表現できるものはいくつありますか？

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \le\ N\ \le\ 10^{18} $
 
### Sample Explanation 1

問題文中の条件を満たす整数は $ 1,4,8,9,16,25,27,32,36,49,64,81 $ の $ 12 $ 個です。

## 样例 #1

### 输入

```
99```

### 输出

```
12```

## 样例 #2

### 输入

```
1000000000000000000```

### 输出

```
1001003332```

# 题解

## 作者：DrAlfred (赞：14)

摘要：枚举，数学

[传送门：https://www.luogu.com.cn/problem/AT_abc361_f](https://www.luogu.com.cn/problem/AT_abc361_f)

## 题意

求在 $[1, n]$ 可被表示为 $a^b(b \ge 2)$ 的正整数 $x$ 的个数。

## 分析思路

撞 [P9118 [春季测试 2023] 幂次](https://www.luogu.com.cn/problem/P9118) 了，乐。

注意到 $a \le \sqrt[b]n$。当 $b \ge 3$ 时显然有 $a \le 10^6$，这是一个极其好的性质。这意味着我们可以在 $O(\sqrt[3]n \log n)$ 次枚举中得出所有 $b \ge 3$ 的 $x$ 的个数，且这个个数也在 $O(\sqrt[3]n \log n)$ 附近。于是我们可以使用 `std::unordered_set` 去重。

问题在于，当 $b = 2$ 时， $a \le 10^9$，显然不能枚举 $a$。注意到 $n$ 以内的完全平方数有 $\lfloor \sqrt n \rfloor$ 个，但问题在于这些数中有些可能已经被上一部分统计过了。于是我们在求解上一问的时候，对于完全平方数不放入即可即可。

最终答案为 $|S| + \lfloor \sqrt n \rfloor$，其中 $S = \{x | x = a^b, a \ge 1, b \ge 3, 1 \le x \le n\}$。时间复杂度 $O(\sqrt[3]n \log n)$，可以通过。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
inline bool isPerfectSquare(i64 x) {
    return (i64)sqrt(x) * (i64)sqrt(x) == x;
}
std::unordered_set<i64> s;
int main(int argc, char const *argv[]) {
    i64 n;
    scanf("%lld", &n);
    for (i64 i = 2; i <= 1e6; i++) {
        __int128 curr = i * i;
        while (curr <= n) {
            if (!isPerfectSquare(curr)) {
                s.insert(curr);
            }
            curr = curr * i;
        }
    }
    printf("%lu\n", s.size() + (size_t)sqrtl(n));
    return 0;
}

```

---

## 作者：流水行船CCD (赞：8)

这是一个较快的做法，目前洛谷仅需 1ms。

## 思路

首先 $a = 1$ 的情况非常特殊，此时无论 $b$ 取何值，$a^b$ 的值均为 $1$，特判一下，问题限制便缩小为 $2 \le a,b$。 

首先因为 $a^b$ 在 $a$ 不变的情况下大小是对数级别，最大的 $b$ 在 $a = 2$ 时取到，此时 $b$ 的值最大，仍只有 $\log_2 N$。这个时候我们就可以枚举每一个 $b$，对于每一个 $b$，**二分**的去求出一个最大的 $c$，使得 $c^b \le N$，此时所有 $2 \le a \le c$ 的 $a$ 都满足条件，就可以直接加入答案当中。

但是这样是有问题的，譬如 $2^6$，$4^3$ 和 $8^2$ 我们会统计三次贡献，但他们实际上是一样的。考虑什么样的情况下会计重，不难发现，如果当前的 $a$ 可以表示为 $p^q$，那么 $a^b$ 就会在 $(p^q)^b = p^{bq}$ 重新统计一边，于是统计答案时减去 $2 \le a \le c$ 中可以表示为 $p^q$ 的 $a$ 的个数即可。而这是一个子问题，用上述算法递归求解即可。

## 时间复杂度

- 快速幂：$O(\log_2 b) = O(\log_2 \log_2 N)$

- 二分：$O(\log_2 N)$

- 递归：每次 $a$ 的值至多变为 $\sqrt N$，设该递归函数为 $T(x)$，则 $T(x) = 60 \times T(\sqrt x) + O(\log_2 N \times \log_2 \log_2 N)$, 运用主方法，时间复杂度是接近 $O(\log_2 N \times \log_2 \log_2 N)$ 的。

## AC Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define REP(i, l, r) for (int i = l; i <= r; ++i)
#define PER(i, l, r) for (int i = l; i >= r; --i)
using namespace std;
namespace fast_IO{
//省略快读
}using namespace fast_IO;
#define int __int128
const int N = 2e5 + 7;
const int inf = LONG_LONG_MAX;
namespace nogf {
    ll n; int m;
    inline bool qpow(int a, int b, int m) {
        int Res = 1;
        while (b) {
            if (b % 2 == 1) Res *= a;
            if (Res > m) return false;
            if (b > 1) {
                a *= a;
                if (a > m) return false;
            }
            b /= 2;
        }
        return true;
    }
    inline int solve(ll n, int m) {// 2 <= num <= n,m 中 num 可以表示为 a^b 的 num 个数
        int L = 2, R = __lg(n), Ans = 0;
        REP(num, L, R) {
            int l = 2, r = m, Res = 1;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (qpow(mid, num, m)) l = mid + 1, Res = mid;
                else r = mid - 1;
            } 
            Ans += Res - (Res <= 3 ? 0 : solve(Res, Res)) - 1; //容斥
        } return Ans;
    }
    signed main() {
        ld >> n, m = n;
        jyt << solve(n, m) + 1 << '\n'; // 要加上 1^b 的个数
        return 0;
    }
} 
signed main() {
    nogf::main();
    return 0;
}	
```

---

## 作者：zhlzt (赞：6)

### 题解
显然 $10^{18}< 2^{60}$，当 $a=1$ 时只有一种可能，当 $a>1$ 时有 $1<b<60$，考虑暴力枚举 $b$。

对于 $b=2$ 的情况显然 $a$ 有 $\lfloor\sqrt[2]{n}\rfloor$ 种可能。

对于 $b=3$ 的情况显然 $a$ 有 $\lfloor\sqrt[3]{n}\rfloor$ 种可能。

以此类推。

发现对于 $b\ge 3$ 的情况可以暴力枚举，暴力判重，再判断是不是完全平方数即可。

代码中不知道为什么使用了二分求 $a$ 的上界，其实暴力枚举就行了。

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline bool check2(ll p){
	ll cur=sqrt(p);
	if(cur*cur==p) return 1;
	else return 0;
}
inline ll qkpow(ll n,ll a,ll p){
	ll ans=1ll%p; 
	while(p>0){
		if(p%2==1){
			if(n/ans<a) return -1;
			ans=ans*a;
		}
		p>>=1;
		if(p>0 and n/a<a) return -1;
		a=a*a;
	}
	return ans;
}
inline ll bs(ll n,ll a){
	ll l=2,r=n,ans=1;
	while(l<=r){
		ll mid=(l+r)>>1;
		ll cur=qkpow(n,mid,a);
		if(cur==-1) r=mid-1;
		else ans=mid,l=mid+1;
	}
	return ans;
}
unordered_map<ll,bool>vis;
int main(){
	ll n;scanf("%lld",&n);
	long long ans=0;
	for(int i=2;i<=60;i++){
		ll m=bs(n,i);
		if(i==2){ans+=m;continue;}
		for(int j=1;j<=m;j++){
			ll cur=qkpow(n,j,i);
			if(check2(cur)) continue;
			if(vis[cur]==1) continue;
			ans++; vis[cur]=1;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：nr0728 (赞：3)

### 前言

注意到这题是 [ABC193C](/problem/AT_abc193_c) 的加强版，$N$ 扩大到了 $10^{18}$，时间复杂度为 $\mathcal O(N^{\frac 1 2}+N^{\frac 1 3}+N^{\frac 1 4}+\cdots+1)$（详见 [ABC193C 题解](https://atcoder.jp/contests/abc193/editorial/820)）的做法显然会 TLE，所以我用 $\mathcal O(N^{\frac 1 3}+N^{\frac 1 4}+\cdots+1)$ 的 做法过了这道题。

### 思路

先看 ABC193C 的思路，对于每个 $1\sim \lfloor\sqrt n\rfloor$ 的数 $i$，枚举 $i^2,i^3,\cdots,i^{\lfloor\log_i n\rfloor}$（因为 $i^{\lfloor\log_i n\rfloor+1}$ 一定大于 $n$），然后把枚举到的数存进 `set`（自动去重）最后输出 `set` 大小即可。

---

对于本题，注意到 $i^2$ 的数刚好有 $\lfloor\sqrt n\rfloor$ 个。我们只需要处理剩下的数即可。

具体的，按照 ABC193C 的思路：对于每个 $1\sim \lfloor\sqrt[3]n\rfloor$ 的数 $i$，枚举 $i^3,\cdots,i^{\lfloor\log_i n\rfloor}$。**注意：为了避免算重，如果枚举到的数不是平方数，才能加进 `set`**，否则平方数会被算两次。最终答案即为 `set` 大小与 $\lfloor\sqrt n\rfloor$ 的和。

最后：注意要用 `sqrtl` 而不是 `sqrt`，否则会有精度误差。

时间复杂度 $\mathcal O(N^{\frac 1 3}+N^{\frac 1 4}+\cdots+1)$，[提交记录](https://atcoder.jp/contests/abc361/submissions/55302302)。

---

## 作者：qhr2023 (赞：2)

## 思路

分类讨论一下，任何数的偶次幂都可以转换成一个数的平方，而 $1$ 到 $n$ 的完全平方数有 $\sqrt{n}$ 个；对于奇次幂，我们只需要暴力枚举底数（只看三次方就够了），实现时用 $mp$ 做标记，以防算重，详情见代码。

## code 

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
map <ll, bool> mp;
ll cnt, n;
int main () {
	cin >> n;
	for (ll i=2; i*i*i<=n; i++) 
		for (ll t=i*i, m=2; t<=n/i; ) {
			t*=i, m++;
			if (!mp[t]) 
				cnt+=((ll)sqrtl(t)*sqrtl(t)!=t),
				mp[t]=1;
		}
	cout << (ll)sqrtl(n)+cnt;
	return 0;
}
```

---

## 作者：wly09 (赞：2)

容斥，比较板了。

一个很显然的事实是：$N$ 以内（含）能表示成 $x^k$ 形式的数共 $\left\lfloor\sqrt[k]{N}\right\rfloor$ 个。

于是我们可以直接统计，时间复杂度是 $\log N$ 的（upd: 这里把开根当成常数级了，实际上可能更高）。

可是，这样计算显然存在重复。

具体来说，我们统计过 $2$，显然不必统计 $4$，更进一步地，不必统计所有含平方因子的数。

接着，我们统计 $3$，注意到 $6$ 这时被统计了两次，需要减去一次。

显然我们可以容斥，注意要对一特判。

对于本题，容斥时需要考虑的数不超过 $60$，可以一一列举，但是实现起来不如暴力方便了。

不过，如果你知道莫比乌斯函数，这题就简单了：

$$
\mu(n)=
\begin{cases}
0,&\exist k\in\mathbb{N_{+}},n\mid k^2\\
(-1)^{\omega(n)},&\text{otherwise}
\end{cases}
$$

这里 $\omega(n)$ 表示 $n$ 的质因子数量。

我们发现它具有相当好的容斥特性，并且是积性函数，可以筛出来。

本题答案即为：

$$
1+\sum_{k=2}^{\infty}-\mu(k)\left\lfloor\sqrt[k]{N}-1\right\rfloor
$$

[AC 记录](https://atcoder.jp/contests/abc361/submissions/55331810)

另外，本题用 `pow` 开根会遇到精度问题，我被卡了好几发，最后使用牛顿迭代法过了。

---

## 作者：WHYMJJ (赞：2)

打暴力！！！！！！！

$x = a^2$ 这样的 $x$ 一共有 $\sqrt n$ 个。

只需要枚举 $x = a^b (b > 2)$的 $x$ 即可。

注意有些数既能变成 $x = a^2$ 也能变成 $x = a^b (b > 2)$
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
map<int,bool> vis;
int solve(){
	int ans = 0;
	for(int i = 2;i*i*i <= n; i++){
		int t = i*i;
		while(t <= n/i){
			t *= i;
			if(vis[t]) continue;
			vis[t] = 1; 
			if((int)(sqrt(t))*(int)(sqrt(t)) != t) ans++; 
		} 
	}
	return ans;
}
main(){
	cin >> n;
	cout << (int)(sqrtl(n))+solve();
	return 0;
}
```

---

## 作者：Starrykiller (赞：2)

简单题 & [原题](https://www.luogu.com.cn/problem/P9118)。看来还是有在进步的。

考虑 $b=2$ 怎么做。$\lfloor x^{\frac{1}{2}}\rfloor$。

考虑 $b=3$ 怎么做。$\lfloor x^{\frac{1}{3}}\rfloor$。

但是你发现会算重 $b=6$。减掉就可以了。

你发现这是什么？Möbius 函数！直接做就可以了。

由于 $1$ 在 $b$ 任意的时候都有贡献，所以我们先不考虑 $1$ 的贡献，最后再加回来。

由于 $\texttt{std::pow}$ 的精度可能不足，需要使用一些方式规避掉精度问题。

[代码](https://atcoder.jp/contests/abc361/submissions/55286796)。

---

## 作者：OldDriverTree (赞：1)

# Solution

令 $f(x)$ 表示 $2\sim n$ 中所有质因数的指数的 $\gcd$ 恰好为 $x$ 的数的个数，答案就等于 $\sum f(x)$。

这个 $f(x)$ 直接算不太好算，但是如果令 $g(x)$ 表示 $2\sim n$ 中所有质因数的指数都为 $x$ 的倍数的数的个数，这个 $g(x)$ 很好算，就为 $\lfloor\sqrt[x]n\rfloor-1$。

考虑莫比乌斯反演，$f(x)=\sum_{x\vert d}\mu(\frac dx)g(d)$。

由于 $g(x)>0$ 的 $x$ 最多不会超过 $\log_2 n$，所以这个东西时间复杂度显然是对的。

# Code
```c++
//when you use vector or deque,pay attention to the size of it.
//by OldDirverTree
#include<bits/stdc++.h>
#include<bits/extc++.h>
#include<atcoder/all>
#define P pair<int,int>
#define int long long
#define mid (l+r>>1)
using namespace std;
using namespace __gnu_pbds;
using namespace atcoder;
int n,ans,a[60],b[60],Mu[60];

int read() {
	int x=0; bool f=true; char c=0;
	while (!isdigit(c) ) f&=(c!='-'),c=getchar();
	while (isdigit(c) ) x=(x<<3)+(x<<1)+(c&15),c=getchar();
	return f?x:-x;
}
int mu(int x)
{
	int res=1;
	for (int i=2;i<=x/i;i++) if (!(x%i) )
	{ res=-res,x/=i; if (!(x%i) ) return 0; }
	if (x>1) res=-res;
	return res;
}
int power(int x,int y)
{
	int mul=1;
	while (y--) {
		if (mul>n/x) return n+1;
		mul*=x;
	}
	return mul;
}
int sqrt(int x)
{
	int l=1,r=1e9;
	while (l<=r) {
		if (power(mid,x)<=n) l=mid+1;
		else r=mid-1;
	}
	return r;
}
main()
{
	n=read();
	for (int i=2;i<60;i++) a[i]=sqrt(i)-1;
	for (int i=1;i<60;i++) Mu[i]=mu(i);
	for (int i=2;i<60;i++)
		for (int j=i;j<60;j+=i)
			ans+=Mu[j/i]*a[j];
	
	printf("%lld",ans+1);
	return 0;
}
```

---

## 作者：littlebug (赞：1)

## Solution

首先，$b=2$（合法的数可以表示成 $a^2$）的情况数为 $\lfloor \sqrt n \rfloor$ 个，而样例 #2 中 $\lfloor \sqrt{10^{18}} \rfloor = 10^9$，但是总数只有 $10^9 + 1003332$ 个，所以可以暴力枚举出 $b \neq 2$ 的答案个数，然后加上 $b=2$ 的个数即可。

需要注意的是，**不可以用快速幂**，因为 `long long` 的最大值大约是 $9 \times 10^{18}$，但 $n \le 10^{18}$，所以快速幂在计算过程中非常容易炸 `long long`。因为指数最大只有 $\log_2(10^{18}) \approx 59.7$，所以要直接累乘计算幂，在过程中用 `double` 判一下当前结果是否 $>n$ 就可以。

还有，**不可以用 `cmath` 里的 `sqrt`**，因为这样虽然可以过掉样例 #2，但是你会 [WA 一个点](https://atcoder.jp/contests/abc361/submissions/55377980)，只能手写个开方向下取整了。

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<set>
#define ll long long
#define il inline
using namespace std;
ll n;
set <ll> f;
il ll spow(ll a,ll b)
{
	ll ans=1;
	double safe;
	while(b--)
	{
		safe=ans*a;
		if(safe>n) return n+1;
		ans*=a;
	}
	return ans;
}
il ll sqrt_floor(ll x)
{
	ll l=0,r=1e9+5,mid;
	while(l+1<r)
	{
		mid=(l+r)>>1;
		if(mid*mid<=x)
			l=mid;
		else
			r=mid;
	}
	return l;
}
il void solve(ll b)
{
	ll a=2,sqr,pw=spow(a,b);
	while(pw<=n)
	{
		sqr=sqrt_floor(pw);
		if(sqr*sqr!=pw) f.insert(pw);
		++a;
		pw=spow(a,b);
	}
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n;
	for(ll i=3;i<=60;++i) //log2(1e19)约等于59.7
		solve(i);
	cout<<sqrt_floor(n)+f.size();
	return 0;
}
```

---

## 作者：Hughpig (赞：1)

当 $b=2$ 时，最多有 $\sqrt{10^{18}}=10^9$ 个 $x$，无法枚举。但是此时答案显然为 $\sqrt{N}$，直接计算即可。

而当 $b>2$ 时，最小为 $b=3$，此时有 $\sqrt[3]{10^{18}}=10^6$ 个 $x$，可以枚举。

发现当 $b$ 取到极大值时，唯一的 $a$ 的可行取值为 $a=1$，此时 $x=1$。显然 $b$ 取任意值时 $a$ 都可以取 $1$，然后 $x=1$。因此此时与已有答案重复，不必枚举。

因此需要枚举的上限为 $b=\lfloor\log_2 10^{18}\rfloor=59$。总枚举量约为 $10^6\times 59=5.9\times 10^7$，可以接受。

一个技术问题是，判断枚举到的 $x$ 是否重复。对于 $b>2$ 枚举的部分可以开一个 `map` 维护是否重复；对于 $b=2$ 计算枚举的 $x$ 是否是完全平方数，是的话那么就和 $b=2$ 有重复。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define INF LONG_LONG_MAX
#define up(l,r,i) for(int i=(l);(i)<=(r);++i)

ll n,ans;
map<ll,bool> vis;

ll ksm(ll a,ll b,ll p)
{
	ll ans=1%p;
	for(;b;b>>=1){
		if(b&1) ans=ans*a%p;
		a=a*a%p;
	}
	return ans;
}

ll check(ll x){
	return x*x<=n;
}

bool issqrt(ll x){
	ll qwq=sqrt(x);
	if(qwq*qwq==x||(qwq+1)*(qwq+1)==x)return 1;
	return 0;
}

ll lg(ll base,ll x){
	ll ret=0;
	while(x>=base)++ret,x/=base;
	return ret;
}

int main()
{
    cin>>n;
	up(2,cbrt(n),i){
		for(ll x=3,y;x<=lg(i,n);++x){
			y=ksm(i,x,INF);
			if(!issqrt(y)&&!vis[y]){
				vis[y]=1;
				++ans;
			}
		}
	}
	cout<<ans+(ll)sqrtl(n);
	return 0;
}
```

---

## 作者：Genius_Star (赞：1)

### 思路：

注意到平方数很多，但是我们可以用 $\sqrt{N}$ 快速统计，则剩下的是多次方的贡献。

注意到 $(10^6)^3=10^{18}$，则我们可以直接预处理出其它非平方数的贡献，其底数肯定在 $[2,10^6]$ 内，直接暴力预处理即可，注意需要排序和去重。

然后二分找到小于等于 $N$ 的个数即可。

---

## 作者：Binah_cyc (赞：1)

[题目传送门]( https://www.luogu.com.cn/problem/AT_abc361_f) 

## 题目分析
数据范围已经告诉我们，应当使用 $\sqrt{n}$ 以下的时间复杂度解题。

分类讨论，因为 $x^{2n} = (x^n)^2$ ，所以偶数次幂都可以转换成某一个数的平方。而 $1$ 到 $\sqrt{n}$ 的每一个数进行平方，都不超过 $n$ 。所以共有 $\sqrt{n}$ 个偶数次幂项。

接下来，考虑奇数次幂，就很暴力了。我们枚举每一个数，计算它的奇数次幂，并统计答案，这题就愉快的解决了。

细节：
- 记得对每个数做标记，防止重复。
- 开根记得使用 sqrtl。~~不会有人像我一样调了好几分钟吧~~
## Code

```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,cnt;
map<int,bool> a;//防止重复统计 
signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=2; i*i*i<=n; i++) //最多三次方,否则就超了 
	{
		int b=i*i; 
		while(b<=n/i)
		{
			b*=i;
			if(a[b]) continue;//重复 
			if((int)sqrtl(b)*(int)sqrtl(b)!=b) cnt++;//非完全平方数 
			a[b]=1;//标记,防止重复 
		}
	}
	cout<<(int)sqrtl(n)+cnt;//sqrt计算完全平方数,cnt计算非完全平方数  
	return 0;
}
```

---

## 作者：Pentiment (赞：0)

发现答案除了平方数以外个数很小，考虑枚举 $b>2$，记录不同的 $a^b$ 的个数，要特判 $a^b$ 是平方数的情况。

直接用 `sqrt` 函数会因为精度原因挂掉某些点，可以手动调整精度。

时间复杂度的分析较为困难，起码积分计算器没有给出一个长相正常的结果。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define lll __int128
int n;
unordered_set<int> s;
lll qpow(lll a, int b) {
	lll c = 1;
	while (b) {
		if (b & 1) c *= a;
		a *= a, b >>= 1;
	}
	return c;
}
int Sqrt(int n, int k) {
	int x = pow(n, 1.0 / k);
	while (qpow(x + 1, k) <= n) x++;
	while (qpow(x, k) > n) x--;
	return x;
}
signed main() {
	cin >> n;
	for (int i = 3; i <= __lg(n); i++) {
		if (!(i & 1)) continue;
		for (int j = 2, up = Sqrt(n, i), k, l; j <= up; j++) {
			k = qpow(j, i), l = Sqrt(k, 2);
			if (l * l != k) s.insert(k);
		}
	}
	cout << Sqrt(n, 2) + s.size() << endl;
}
```

---

## 作者：Redshift_Shine (赞：0)

## 6. x = a^b / [幂次](https://www.luogu.com.cn/problem/P9118)

相信你注意到了这个二级标题中的链接。

没错。

这是原题。还是 `NOI` 春季测试的题。

有一条性质。

尽管 $1\le n\le 10^{18}$，但 $\sum_{i=2}^{\sqrt[3]{n}}\log_i n$ 并不会太大。

于是，对于 $b\ge 3$ 的情况，直接暴力枚举。

对于 $b=2$ 的情况，其结果严格等于 $\lfloor\sqrt n\rfloor$。

发现不太好容斥。所以可以在处理 $b\ge 3$ 的情况时顺便检查枚举到了多少个完全平方数。

并且，在时间允许的情况下，一定要用 `sqrtl` 代替 `sqrt`。我因为这个吃了 $2$ 发罚时。**警钟撅烂**。

```c++
#include <iostream>
#include <set>
#include <cmath>
using namespace std;
const int N = 1e5 + 10;
using ll = __int128;
set<ll> mp;
ll n, sq, tmp;
void ff(ll x)
{
    tmp = sqrtl(x);
    if (tmp * tmp == x)
        sq++;
}
int main()
{
    scanf("%lld", &n);
    for (ll i = 2; i * i * i <= n; i++)
    {
        for (ll j = i * i * i; j <= n; j *= i)
        {
            if (mp.count(j))
                continue;
            ff(j);
            mp.insert(j);
        }
    }
    printf("%lld\n", (ll)(floor(sqrtl(n))) - sq + mp.size());
}
```

---

## 作者：1234567890sjx (赞：0)

最简单的一集。为 P9118 春测原题弱化版。即此题 $k=2$ 情况。

首先对于 $a^b$，若 $b\ge 3$ 则 $a$ 最大不会超过 $10^6$，可以直接暴力枚举。难点在于 $k=2$ 的情况。

考虑容斥。容易发现 $b=2$ 时答案为 $\lfloor\sqrt n\rfloor-R$。其中 $R$ 表示需要容斥的部分。即 $b>2$ 时成立且 $b=2$ 时也成立的数。因为 $b>2$ 即 $b\ge 3$ 的情况数量很少可以暴力枚举，所以在枚举 $b\ge 3$ 的时候直接算出来里面又多少个完全平方数，即为要容斥的数的数量 $R$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
map<int, int> mp;
int R, cnt;
void solve(int n, int k) {
    for (int i = 2; i * i * i <= n; ++i) {
        int t = i * i, m = 2;
        while (t <= n / i) {
            t *= i, m++;
            if (m < k || mp[t]) continue;
            else {
                if ((int)sqrtl(t) * sqrtl(t) == t) R++;
                cnt++, mp[t] = 1;
            }
        }
    }
}
signed main() {
    int n;
    cin >> n;
    solve(n, 2);
    cout << (int)sqrtl(n) - R + cnt << '\n';
}

```

---

## 作者：joe_zxq (赞：0)

# Part 1 - 题面翻译

求 $1$ 到 $N$ 之间有多少个正整数 $x$ 可以被表示为 $a^b$ 的形式，其中 $a$ 和 $b$ 是正整数，$b \ge 2$。

# Part 2 - 算法思路

~~ABC 又考了[原题](https://www.luogu.com.cn/problem/P9118)，而且卡精度，差评。~~

对于 $k \ge 3$，我们显然可以直接枚举。对于 $k=2$，有 $\sqrt{N}$ 个，但是这些数可能与 $k \le 3$ 的数重复了。于是我们可以在计算 $k \le 3$ 时标记有多少个完全平方数。设其数量为 $x$。那么 $k=2$ 的不重复数量就是 $\sqrt{N}-x$。再加上 $k \le 3$ 的数量就是最终的结果。

特别注意，该题卡精度，使用 `sqrt()` 会挂一个点，需要使用进度较高的 `sqrtl()`。

# Part 3 - 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll unsigned long long

ll n, ans, cnt;
map<ll, ll> vis;

bool sq(ll x) {
	return ((ll)sqrtl(x) * sqrtl(x) == x);
}

int main() {

	cin >> n;
	for (ll a = 2; a * a * a <= n; a++) {
		ll t = a * a;
		for (ll b = 2; ; b++) {
			if (n / a < t) {
				break;
			}
			t *= a;
			if (vis[t]) {
				continue;
			}
			ans++;
			if (sq(t)) {
				cnt++;
			}
			vis[t] = 1;
		}
	}
	cout << ans + (ll)sqrtl(n) - cnt;

	return 0;
}

```

---

## 作者：云裳 (赞：0)

**思路**

显然可以把符合要求的 $x$ 分为 $x=a^2$ 和 $x=a^b(b>2)$ 两类，而第一类就是 $\sqrt{n}$，且最多只有 $\sqrt{10^{18}}=10^9$ 个数。拿样例二的答案一减，发现第二类最多约有 $10^6$ 个数，那直接枚举 $a,b$ 就好了。

具体来说就是枚举 $a,b$，并且判断 $a^b$ 是不是完全平方数，如果不是的话就把他扔进一个 `set` 里去重，最后的答案就是 `set` 的大小再加上 $\sqrt{n}$。

**代码**

```cpp
#include<bits/stdc++.h>
#define up(i,l,r) for(ll i=l,END##i=r;i<=END##i;i++)
#define dn(i,l,r) for(int i=l,END##i=r;i>=END##i;i--)
typedef long long ll;
typedef double db;
using namespace std;
const ll INF=0x3f3f3f3f,p=1.005e18;
set<ll> s;
ll n;
namespace sol{
    ll read(){
        ll f=0,x=0;
        char c=getchar();
        while(c<'0'||c>'9') f|=c=='-',c=getchar();
        while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
        return f?-x:x;
    }
    void write(ll x){
        if(x<0) putchar('-'),x=-x;
        if(x>9) write(x/10);
        putchar(x%10+'0');
    }
    ll qpow(ll base,ll k){
      //这里不用二进制拆分会保险一点
    	ll f=1;
    	up(i,1,k){
    		f*=base;
    		if(f>=p) return p;//防止炸掉
		}
		return f;
	}
    void solve(){
		n=read();
		up(j,3,60){
			for(int i=2;i;i++){
				ll k=qpow(i,j);
				if(k>n) break;
				ll f=sqrtl(k);//注意要用sqrtl不然会炸
				if(f*f==k) continue;
			s.insert(k);
			}
		}
		write(s.size()+sqrtl(n));
    }
}
using namespace sol;
signed main(){
    solve();
    return 0;
}

```

---

## 作者：Liyunze123 (赞：0)

这道题要你求 $1$ 到 $n$ 中能表示成 $a^b$（$b \ge 2$）的数的个数。

首先，我们发现 $n \le 10^{18}$，最多就是二的六十几次方。枚举指数肯定是可以的，但底数最大到 $10^9$，肯定超时。

其实，设 $n$ 的立方根向下取整为 $k$，$n$ 的平方根向下取整为 $l$，那么 $k+1$ 至 $l$ 对答案的贡献都是 $1$。我们只要枚举底数 $2$ 到 $k$，枚举时，若底数 $i=p^q$（$q \ge 2$），跳过枚举，因为 $i^j$ 肯定在枚举 $p$ 时枚举过。枚举时，如果枚举到平方数且平方根 $>k$，答案不能加。否则答案加一。

最后还要加上 $l-k+1$，补上 $k+1$ 至 $l$ 所有数的贡献 $1$，再加上 $1$（$1=1^2$）。

上代码：
```
#include<bits/stdc++.h>
using namespace std;
long long n,ans;
int t[1000010];
int get(long long i){for(int w=1;w<=i;w++)if((long long)w*w*w>i)return w-1;else if((long long)w*w*w==i)return w;}
int main(){
	scanf("%lld",&n);
	int k=get(n);
	for(int w=2;w<=k;w++)for(long long x=(long long)w*w;x<=k;x*=w)t[x]=1;
	for(int w=2;w<=k;w++)if(!t[w])for(__int128 x=(long long)w*w,y=2;x<=n;x*=w,y++)if(!(y%2==0&&x>(long long)k*k))ans++;
	long long t=(long long)sqrt(n);
	if(t*t>n)t--;
	printf("%lld",ans+1+t-k);
	return 0;
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc361_f)

## 思路

在 $k\ge 3$ 的时候，我们可以直接枚举底数，并暴力不断做乘法来进行枚举。用一个 ``map`` 标记即可。每次找到一个数，计数器 $+1$。

在 $k=2$ 的时候，不难看出满足 $a^2=x\space(1\le x\le N)$ 这样的 $x$ 共有 $\lfloor\sqrt{N}\rfloor$ 个，但是由于在上文中枚举的时候已经找出了一些，所以在上文找的时候还要加一行判断：如果找到的这个数是完全平方数，那么**平方数的计数器 $+1$**。

- 优化：可以把 ``map`` 替换成复杂度更优的 ``unordered_map``。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,cnt,cntsq;
unordered_map<ll,bool>mp;
signed main(){
	cin>>n;
	for(ll i=2;i*i*i<=n;++i){
		ll k=i*i,m=2;
		while(k<=n/i){//如果换成 k*i<=n 会越界导致 TLE。
			k*=i;
			++m;
			if(m<2||mp[k])continue;//不满足要求或者找过了，退出。
			if((ll)sqrtl(k)*sqrtl(k)==k)++cntsq;//平方数计数。
			++cnt;//满足要求的数计数。
			mp[k]=1;
		}
	}
	cout<<(ll)sqrtl(n)+cnt-cntsq;
	return 0;
}
```

[AC 记录](https://atcoder.jp/contests/abc361/submissions/55306349)

---

## 作者：Milthm (赞：0)

你说得对，但是：

![](https://cdn.luogu.com.cn/upload/image_hosting/fptugn03.png)

所以感觉不如 B 题。

____

我们发现，$b=2$ 的情况的枚举次数是最多的，达到了 $\sqrt n$ 的量级，而如果只有 $b\ge 3$，我们发现这个量级是可以接受的，于是考虑分别计算。

首先，$b=2$ 的情况就是 $n$ 以内的平方数个数，也就是 $\lfloor \sqrt n\rfloor$。

然后考虑 $b\ge 3$，由样例二我们知道这些情况的总和除去完全平方数只有 $1003332$ 种，所以开 `map` 来去重不会炸。

然后在枚举的过程中，记得判断枚举的这个数是否是完全平方数，如果是的话就不能算在内。

这题最大的难点就是 `sqrt` 的精度可能会炸，所以你可以采用 `sqrtl` 或者二分。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
double eps=1e-9;
int n,cnt;
unordered_map<int,int>m;
__int128 qpow(int x,int y){
	__int128 ans=1;
	while(y){
		if(y&1)ans=ans*x;
		x=x*x;y>>=1;
	}
	return ans;
}
int Sqrt(int x){
	int l=1,r=sqrt(x)*2,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(mid*mid<=x)ans=mid,l=mid+1;
		else r=mid-1;
	}
	return ans;
}
signed main(){
	cin>>n;
	int ans=Sqrt(n);
	for(int i=3;i<=62;++i){
		for(int j=1;j<=n;++j){
			__int128 k=qpow(j,i);
			if(k>n)break;
			int r=Sqrt(k);
			if(r*r==k)continue;
			if(!m[k])m[k]=1,++ans;
		}
	}
	cout<<ans;
	return 0;
}
```

---

