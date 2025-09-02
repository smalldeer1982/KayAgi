# Number With The Given Amount Of Divisors

## 题目描述

Given the number $ n $ , find the smallest positive integer which has exactly $ n $ divisors. It is guaranteed that for the given $ n $ the answer will not exceed $ 10^{18} $ .

## 样例 #1

### 输入

```
4
```

### 输出

```
6
```

## 样例 #2

### 输入

```
6
```

### 输出

```
12
```

# 题解

## 作者：Plozia (赞：20)

Update 2022/2/3：感谢 @[aresword](https://www.luogu.com.cn/user/327683) 大佬的建议，对文章中一个不严谨但是能过题的地方进行修改。

---

宣传博客 $\to$ [link](https://blog.csdn.net/BWzhuzehao/article/details/113134249)

这是一道数学题。

前置知识：

对于一个数 $x$，我们可以将其唯一分解成 $p_1^{c_1} \times p_2^{c_2} \times ... \times p_k^{c_k}=\prod_{i=1}^{k}p_i^{c_i}$，其中 $p_i$ 为质数，即分解质因数。~~都来做这道题了这个肯定是会的吧~~

引理：

对于唯一分解 $x = \prod_{i=1}^{k}p_i^{c_i}$，$x$ 的因数个数为 $\prod_{i=1}^{k}(c_i+1)$。证明见文末。

那么这道题我们要怎么做呢？

这里要有贪心的思想。

对一个具有 $n$ 个因子的数来说，肯定是 $\text{2}$ 的个数越多越好对不对？当然我们可以举出反例，但是当因子个数不够的时候肯定是增加 $\text{2}$ 的个数是更优的。

那么这里有一个定理：

对于一个含有 $n$ 个正因子的最小数 $x = \prod_{i=1}^{k}p_i^{c_i}$，如果 $\forall i \in [1,k),p_i < p_{i+1}$，那么可以证明：

1. $p_1 = 2$
2. $p_{i+1}$ 是 $p_i$ 后面的第一个质数（即连续质数）
3. $\forall i \in [1,k),c_{i + 1} \leq c_i$

证明见文末。

考虑到我们现在不能确定是否一定是 $\text{2}$ 的个数越多越好，但是相对而言 $\text{2}$ 的个数越多越好，那么我们采用搜索解决。

首先题目保证答案不超过 $10^{18}$ ，而 $2^{64} > 10^{18}$，那么我们知道指数最多为 $\text{64}$。又因为从 $\text{2}$ 开始连续 $\text{16}$ 个质数相乘已经超过 $10^{18}$，那么我们只需要搜 $\text{16}$ 个质数，然后加上最优化剪枝以及一些特判即可。

**友情提醒：当搜索过程中的答案小于 $\text{0}$ 的时候说明此时答案爆 `long long` 了，此时需要停止搜索。**

这里添加一个说明：其实答案爆 `long long` 并不一定是答案小于 0，也可以大于 0，但是按照我的程序的逻辑答案爆 `long long` 和答案小于 0 互为充要条件，因此这么写是没问题的。

更正确的写法参考[判断C语言的算术运算越界问题 - dennis_fan - 博客园](https://www.cnblogs.com/dennisOne/archive/2012/11/13/2768416.html)。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 30;
int n, prime[MAXN] = {0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};
LL ans = 0x7f7f7f7f7f7f7f7f;

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

void dfs(LL now, int k, int last, int cnt)
{
	if (cnt > n) return ;
	if (now <= 0ll) return ;
	if (now > ans) return ;
	if (k > 16) return ;
	if (cnt == n) {ans = now; return ;}
	for (int i = 1; i <= last; ++i)
		dfs(now *= prime[k], k + 1, i, cnt * (i + 1));
}

int main()
{
	n = read();
	dfs(1ll, 1, 64, 1);
	printf("%lld\n", ans);
	return 0;
}
```

证明：

引理的证明：

考虑在 $x=\prod_{i=1}^{k}p_i^{c_i}$ 中，我们将 $p_i$ 看作 $k$ 个箱子，在每一个箱子中我们可以取出 $c_i+1$ 个数，分别为 $p_i^0,p_i^1,...,p_i^k$。

考虑到所有 $p_i$ 都是质数，因此不会有取出的数字重复。

由乘法原理，正因子个数为 $\prod_{i=1}^{k}(c_i+1)$。

定理的证明：

1. $p_1=2$。

这个其实很好想，毕竟如果我们把 $p_1$ 换成比 $\text{2}$ 更大的数字显然答案只会更劣。

2. $p_{i+1}$ 是 $p_i$ 后的第一个质数。

这个也很好证明。

对于一个确定的 $(c_i,c_{i+1})$，由于规定 $\forall i \in [1,k),p_i < p_{i+1}$，那么如果 “$p_{i+1}$ 是 $p_i$ 后的第一个质数” 不成立，那么 $p_{i+1}$ 只能变得更大，答案显然更劣。

3. $\forall i \in [1,k),c_{i + 1} \leq c_i$

由于 $p_i < p_{i+1}$，那么我们假设 $c_i < c_{i+1}$，这一段的答案为 $p_i^{c_i} \times p_{i+1}^{c_{i+1}}$。

如果我们交换指数，因子个数不变，答案为 $p_i^{c_{i+1}} \times p_{i+1}^{c_i}$。

此时根据前文所述，显然越大的指数要配越小的质数，那么 $c_i < c_{i+1}$ 的答案比 $c_{i+1} \leq c_i$ 更劣。

证毕。

---

## 作者：一扶苏一 (赞：13)

[传送门](https://www.luogu.org/problemnew/show/CF27E)

## Description

给定一个正整数$n$，输出最小的整数，满足这个整数有n个因子

## Input

一行一个整数$n$

## Output

一行一个整数，代表答案。

## Hint

$1~\leq~n~\leq~1000$。保证答案不超过$10^{18}$

## Solution

经典题。

#### 引理：

对于一个唯一分解式形如$x=p_1^{c_1}p_2^{c_2}p_3^{c^3}\cdots p_k^{c_k}$的数字$x$，则其因数个数为$\prod(c_i+1)$。

#### 证明：

考虑乘法原理，第$i$项的指数有$0~\sim~c_i$共$c_i+1$种方式，根据唯一分解定理的逆定理，每一项指数不同所得到的数是不同的。于是根据乘法原理，其因数个数为$\prod(c_i+1)$。

#### 证毕。

#### 定理：

考虑一个因数个数为$n$的最小整数$x$，则它的唯一分解式$x=p_1^{c_1}p_2^{c_2}p_3^{c^3}\cdots p_k^{c_k}$中，不妨设$p_1~<~p_2~<~p_3~<~\cdots~<~p_k$，则一定满足：$p_1=2$，且$\forall ~i~>~1$，$p_i$是大于$p_{i-1}$的第一个质数，同时$\forall~i~\in~[1,k)$，$c_i~\leq~c_{i+1}$。

#### 证明：

1、若$p$在质数表上不是连续的，不妨设$p_i~<~q~<p_{i+1}$，则将$p_{i+1}$替换为$q$，$x$会变小，因为$c_{i+1}$不变，根据引理，因数个数不变。于是替换为$q$答案更优，这与$x$是最小的有$n$个因子的数矛盾。

2、若$c_i$不是单调不升，不妨设$c_i~<~c_{i+1}$，则将两指数交换，$x$会变小。同上可证因数个数不变。于是交换后答案更优，这与$x$是最小的有$n$个因子的数矛盾。

#### 证毕。

于是发现答案的唯一分界式，$2$一定会出现且指数最大。考虑$2^{64}$已经大于$10^{18}$，所以指数最多为$64$。又发现前15个质数连乘的答案已经大于$10^{18}$，所以质数最多是15个。于是爆搜一下，分别进行一下可行性剪枝和最优性剪枝，即可通过本题。

#### Code

```cpp
#include<cstdio>
#ifdef ONLINE_JUDGE
#define putchar(a) \
puts("I am a cheater!")
#endif
#define rg register
#define ci const int
#define cl const long long

typedef long long int ll;

template <typename T>
inline void qr(T &x) {
	rg char ch=getchar(),lst=' ';
	while((ch > '9') || (ch < '0')) lst=ch,ch=getchar();
	while((ch >= '0') && (ch <= '9')) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	if(lst == '-') x=-x;
}

namespace IO {
	char buf[120];
}

template <typename T>
inline void qw(T x,const char aft,const bool pt) {
	if(x < 0) {x=-x,putchar('-');}
	rg int top=0;
	do {IO::buf[++top]=x%10+'0';} while(x/=10);
	while(top) putchar(IO::buf[top--]);
	if(pt) putchar(aft);
}

template <typename T>
inline T mmax(const T a,const T b) {return a > b ? a : b;}
template <typename T>
inline T mmin(const T a,const T b) {return a < b ? a : b;}
template <typename T>
inline T mabs(const T a) {return a < 0 ? -a : a;}

template <typename T>
inline void mswap(T &_a,T &_b) {
	T _temp=_a;_a=_b;_b=_temp;
}

const int prime[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53};

int n;
ll ans=1000000000000000001;

void dfs(ll,int,int,int);

int main() {
	qr(n);
	dfs(1ll,0,64,1);
	qw(ans,'\n',true);
	return 0;
}

void dfs(ll now,int cur,int p,int cnt) {
	if(cnt > n) return;
	if(now <= 0ll) return;
	if(now > ans) return;
	if(cur > 15) return;
	if(cnt == n) {ans=now;return;}
	for(int i=1;i<=p;++i) {
		dfs(now*=prime[cur],cur+1,i,cnt*(i+1));
	}
}
```

## Summary

对于一个唯一分解式形如$x=p_1^{c_1}p_2^{c_2}p_3^{c^3}\cdots p_k^{c_k}$的数字$x$，则其因数个数为$\prod(c_i+1)$。

---

## 作者：CrTsIr400 (赞：11)

## [Number With The Given Amount Of Divisors](https://www.luogu.com.cn/problem/CF27E)

翻了下题解，居然没有人用 DP 做？

---

输出最小的有 $n$ 个因子的整数。$n\le 1000$。

~~见 $O(1)$ 输入知打表~~。

---

考虑自然数分解 $N=\prod_{i=1}^m a_i^{b_i}$ 的式子，然后因子个数就是 $\prod(b_i+1)$。

于是我们的目标就是 $n=\prod(b_i+1)$ 的式子，显然取最小的几个质数 $a$ 就能构造最优解。

题目提示我们答案只会小于等于 $10^{18}$，所以处处有剪枝。搜索是一条道路，但是我用了更好想的方法。

---

设 $f[j][i]$ 为有 $i$ 个因子且用了前 $j$ 个质数的最小整数。

知道这个之后枚举次数转移：$f[j][i]\times p[j+1]^{k}\to f[j+1][i\times (k+1)]$，其中 $k\ge 1$，直到大于 $10^{18}$ 为止。

质数最多只用 $10$ 个，因为 $n$ 只有 $1000$。$i$ 也最多只有 $1000$。

于是我们就 $O(n\log n\log 10^{18})$ 地解决了这个问题，甚至可以求出对于所有 $[1,n]$ 的答案。

```cpp
#include<bits/stdc++.h>
#define fo(i,a,b) for(I i(a),_ed(b);i<=_ed;++i)
using namespace std;using I=int;using LL=long long;using V=void;
const I p[11]={1,2,3,5,7,11,13,17,19,23,29};
LL f[1010];I n;
I main(){ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	memset(f,0x3f,sizeof(f));
	f[1]=1;
	fo(j,0,9){for(I i=1000;i;--i){
		LL x=f[i];
		fo(k,1,63){
			if(1e18/p[j+1]<x)break;
			x*=p[j+1];
			if(i*(k+1)>n)break;
			f[i*(k+1)]=min(f[i*(k+1)],(LL)x);}}
	}
	printf("%lld\n",f[n]);
	return 0;}
```

后记：

![](https://cdn.luogu.com.cn/upload/image_hosting/j4ds5pcn.png)

这张图中标明 $10^{18}$ 范围内，有一个数 $897612484786617600$，它有 $103680$ 个约数。

理论上 $n$ 可以加强到 $10^5$（但是需要保证询问的 $n$ 的答案在 `long long` 范围内）。



---

## 作者：一只书虫仔 (赞：7)

水题（做过反素数 dfs 版的同学应该很块就会做这道题）

#### Description

> 求最小的拥有 $n$ 个因子的正整数。

#### Solution

设最小的拥有 $n$ 个因子的正整数为 $Q$，我们将其分解质因数：

$$Q=p_1^{a_1}p_2^{a_2}\cdots p_k^{a_k}$$

不难得知，有：

$$n=\prod\limits_{i=1}^k(a_i+1)$$

这个很好证吧，简单组合就行了。

接下来我们考虑分配 $n$ 给不同的质因子，考虑贪心，使质因子序列 $p_i=\{2,3,5,\cdots\}$，即连续质数序列，并以 $2$ 开头，指数序列要满足单调不升，即 $c_i\ge c_{i+1}$。

具体证明的话，对于质数序列，肯定越紧凑越好，否则答案会越来越大，对于指数序列，肯定更小的质数占比更大一些，否则答案也会越来越大（感性理解 qwq）。

具体操作 dfs 即可，指数最大不超过 $64$（$10^{18}<2^{64}$），质数序列最大值到 $53$ 即可（$2 \times 3 \times 5 \times 7 \times 11 \times 13 \times 17 \times 19 \times 23 \times 29 \times 31 \times 37 \times 41 \times 43 \times 47 \times 53> 10^{18}$），在加上大于答案就直接结束等剪枝就能水过去了。

最后要注意的一点是可能会爆 long long（WA on #19 呜呜）只要特判是否小于 $0$ 即可。

#### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

long long n;
long long prime[20] = {0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};
long long ans = 1000000000000000005;

void dfs (long long cur, long long cnt, long long p, long long k) {
	if (cur > ans) return;
	if (cur < 0) return;
	if (cnt > n) return;
	if (cnt == n) {
		ans = min(ans, cur);
		return;
	}
	if (p > 16) return;
	for (long long i = 1; i <= k; i++) {
		cur *= prime[p];
		dfs(cur, cnt * (i + 1), p + 1, i);
	}
}

// cur: 现在枚举到的这个数等于多少
// cnt: 因数个数
// p: 枚举到第 p 个质数
// k: 枚举到的第 p 个质数的指数为 k，同时框定了第 p + 1 个质数的指数上限

int main () {
	scanf("%lld", &n);
	dfs(1, 1, 1, 64);
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：Alarm5854 (赞：3)

这道题目的做法有很多种，但我这种做法貌似题解区都没有，所以我来讲述一下我的做法。

根据一个数 $x$ 分解后可表示为 $\prod p_i^{c_i}$，而 $p_i$ 有 $c_i+1$ 种选法，可得质因数个数为 $\prod (c_i+1)$。这样，问题就转化为已知 $\prod(c_i+1)$，求最小的 $x$，满足 $x=\prod p_i^{c_i}$。

先筛出 $n$ 以内的所有质数，然后对 $n$ 进行质因数分解，记录在一个数组里，如分解 $54$ 之后的数组为 $2,3,3,3$，分解完之后将数组从大到小排序，即此时数组变为 $3,3,3,2$。

结束了？不，没有结束。这样还不够，如因子数量为 $8$，如果单纯按上面的方法分解，那么得到的数组为 $2,2,2$，根据贪心思想，$x$ 应为 $2^1\times 3^1\times 5^1=30$，但实际上，$x$ 为 $2^3\times 3^1=24$ 时更优。所以，还要尝试一下分解之后的数组的最后元素能否合并到前面的元素，使答案更小，不要忘记在尝试更新答案的时候要将数组重新排序，并且要多次尝试能否使答案更小。

对了，还要注意细节：初始的答案可能会很大，以至于超出了 `long long` 所能储存的范围，这样答案会变为 $0$，所以要特判一下，把此时的答案改为极大值。

```cpp
#include<ctime>
#include<cctype>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
const ll N = 1e3 + 7;
inline ll read() {
	ll x = 0, f = 1; char c;
	while (!isdigit(c = getchar())) f -= (c == '-') * 2;
	while (isdigit(c)) x = x * 10 + f * (c - 48), c = getchar();
	return x;
}
ll n, ans, tot, cnt, p[N], v[N], m[37], t[37], s[37];
bool cmp(ll a, ll b) {return a > b;}
ll HgS(ll a, ll b) {ll res = 1; for (; b; b >>= 1, a = a * a) if (b & 1) res = res * a; return res;}
ll mul() {
	ll res = 1;
	sort(m + 1, m + cnt + 1, cmp);
	for (ll i = 1; i <= cnt; ++i) res *= HgS(p[i], m[i] - 1);
	return res;
}
int main() {
	n = read(), ans = 1;
	for (ll i = 2; i <= n; ++i) {//n很小，所以可用O(nloglogn)的复杂度筛质数
		if (!v[i]) p[++tot] = i;
		for (ll j = i; j * i <= n; ++j) v[i * j] = 1;
	}
	for (ll i = 1; i <= tot; ++i)
	while (!(n % p[i])) m[++cnt] = p[i], n /= p[i];
	ans = mul(); if (!ans) ans = 1e18;
	while (cnt > 1) {//每次尝试去掉最后一个数
		ll flg = 0;
		for (ll i = 1; i < cnt; ++i) {
			memcpy(s, m, sizeof(m));
			m[i] *= m[cnt], m[cnt--] = 0;
			ll res = mul(); if (!res) res = 1e18;
			if (res < ans) ans = res, flg = 1, memcpy(t, m, sizeof(m));
			memcpy(m, s, sizeof(m)), ++cnt;
		}
		if (!flg) break;//如果尝试失败，那么之后肯定是失败的，所以不必再循环了
		memcpy(m, t, sizeof(m)), --cnt;
	}
	printf("%lld", ans);
	return 0;
}
```

由于每成功分解一次，这个数就会至少除以 $2$，所以 $cnt$ 为 $\log n$ 级别，时间复杂度为 $O(n\log\log n+\log^3n)$，使用线性筛可优化为 $O(n+\log^3n)$，理论上比带剪枝的搜索效率高，但实际上可能会比它慢。



---

## 作者：出言不逊王子 (赞：2)

首先我们发现，对于一个正整数 $k=\prod_{i=1}^n p_i^{a_i}$，其中 $n$ 是 $k$ 的质因数个数，$p_i$ 是 $k$ 的质因数， $k$ 的因数个数是 $\prod_{i=1}^n (a_i+1)$。	

然后我们想到既然 $n$ 很小，小到这个 $\prod$ 最多只要算 $10$ 次，（因为 $2^{10}$ 大于 $1000$），所以我们可以用搜索的方式搜出答案。

我们每次搜索可以搜 $k$ 的质因数 $p_i$，算他要乘上去几个 $p_i$，则当前 $k$ 的因数个数就会**乘上** 我**给 $k$ 乘上**的 $p_i$ 的个数。

那么，搜到哪为止，要搜几个质数呢？

我们发现 $2^{64}$ 大于 $10^{18}$ ，又发现把前 $16$ 个质数相乘的乘积已经大于 $10^{18}$ ，所以对于每个质数，我们只要顶天搜到它的 $63$ 次方即可。

坑点：

- 如果当前的这个 $k$ 小于等于 $0$，说明它被直接自然溢出了，肯定大于 $10^{18}$，返回即可。
- 要考虑 $k$ 没有乘上 $p_i$ 的情况。**尤其留意这个！我 NOIP2021T2 的暴力就是错在这里！**

然后你写出来，会发现它在 $n$ 等于 $902$ 时超时了。

我们发现因数个数是一堆乘积的形式，所以如果当前我们给 $k$ 的因数个数乘上的“给 $k$ 乘上的 $p_i$ 的个数”不能整除 $n$，那么这个状态本身就是不合法的，可以剪枝。

代码：

```cpp
#include<bits/stdc++.h>
#define fs(i,x,y,z) for(int i=x;i<=y;i+=z)
#define ft(i,x,y,z) for(int i=x;i>=y;i+=z)
#define int long long
#define ull unsigned long long
#define db double
#define ms(a,b) memset(a,b,sizeof(a))
#define sz(a) sizeof(a)
using namespace std;
const int rw[]={-1,0,1,0,-1,1,-1,1},cl[]={0,1,0,-1,-1,1,1,-1};
const int N=100001,inf=0x3f3f3f3f;
inline int read(){
	int date=0,w=1;char c=0;
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){date=date*10+c-'0';c=getchar();}
	return date*w;
}
int n,k,ans=1e18,prms[31]={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53}; 
void dfs(int cur,int k,int cnts){//cur是当前的数，k是当前到了第几个质因子
	if(cur>ans||cur<1||k>16||cnts>n) return;//寄！ 
	if(cnts==n) return void(ans=min(ans,cur)); 
	dfs(cur,k+1,cnts);
	fs(i,1,63,1){
		cur*=prms[k];
		if(cur>ans||cur<1) break;
		if(n%(i+1)==0) dfs(cur,k+1,cnts*(i+1));
	}
}
signed main(){
	n=read();dfs(1,1,1);printf("%lld",ans);
	return 0;
}
```

---

## 作者：HoshiuZ (赞：2)

暴力居然水过去了。。。

容易发现，当一个数$m$为$n$个因子的最小数的话，将其质因数分解$m=\prod_{i=1}^kp_i^{a_i}$($p$递增)，若要保证其为最小，则$a$得要是不上升的，因为若后面的质因数的指数较大，指数移一部分到前面，这两个数的值后者较小，但因子个数是一样的。

所以据此dfs即可。
```cpp
#include<bits/stdc++.h>
#define ull unsigned long long

using namespace std;

int n;
ull ans=-1,prime[18]={1,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59};

void dfs(int k,ull num,int js,int pos) {
//	cout<<num<<" "<<js<<endl;
	if(!num) return ;
	if(js>n||pos>18) return ;
	if(js==n) {
		if(ans==-1) ans=num;
		else ans=min(ans,num);
	}
	ull t=num;
	for(int i=1;i<=k;i++) {
		t*=prime[pos];
		dfs(i,t,js*(i+1),pos+1);
	}
}
	
int main() {
	cin>>n;
	
	dfs(n-1,1,1,1);
	
	cout<<ans<<endl;
	
	return 0;
}
```


---

## 作者：AllanPan (赞：1)

## 一、分析
### 1. 一个正整数的正因子个数计算方法

为了解决这道题目，我们首先需要做的当然就是推导出如何计算一个给定正整数的正因子数目。为了达成这一点，我们首先需要知道这一点，即：

【**算数基本定理**】任何一个大于 $1$ 的自然数 $N$ ,如果 $N$ 不为质数，那么 $N$ 可以**唯一分解**成有限个质数的乘积 $N=P_1^{a_1}P_2^{a_2}P_3^{a_3}\cdots P_n^{a_n}$ ，这里 $P_1<P_2<P_3<\cdots <P_n$ 均为质数，其中指数 $a_i$ 是正整数。这样的分解称为 $N$ 的标准分解式。

[【想具体了解证明可以戳这里】](https://baike.baidu.com/item/%E7%AE%97%E6%9C%AF%E5%9F%BA%E6%9C%AC%E5%AE%9A%E7%90%86/10920095?fr=aladdin)

知道了算术基本定理的内容后，我们就可以把 $N$ 的正因子个数量化地表示出来了。由整除的性质，$N$ 的每个正因子均可以表示为 $P_1^{b_1}\cdots P_n^{b_n}$ 的形式，其中 $0\leq b_1 \leq a_1,\ldots 0\leq b_n \leq a_n$，也即每个指数 $b_i$ 有 $0,\ldots a_i$ 共计 $a_i+1$ 种选择方式。由乘法原理，这样的数共有
$$\prod_{i=1}^n (a_i+1)=(a_1+1)(a_2+1)\cdots(a_n+1)$$
个。反过来说，给定一个正整数 $N$ 的正因子个数，我们也可以利用上面的这个公式**反推回去**。

### 2. 如何保证结果最小？
我在拿到这个问题的时候，第一感觉就是：尽量让 $N$ 的**唯一分解式**中质数数量尽量多，否则相当于把重心放在了较小的质数上，结果也成几何形上升。

（如果上面这段话说得比较迷的话，我们举个例子：假定题目给定的数是 $100=2^2\cdot 5^2$ ，那么比起 $2^{99}$ 来说，我们如果把相应的指数幂转到其它素数上，例如 $2^{2^2-1}\cdot 3^{5^2-1}$ ，那结果便会小得多。）

#### 2.1 尽量让 $N$ 的**唯一分解式**中质数数量尽量多。

光多还是不够的，如果把最大指数放到一个较大的质数上，我们不妨调整一下，把它交换小一点的质数上，这样结果也会变小。于是得到结论：

#### 2.2 更大的指数幂放在较小的质数上。

于是我得到了第一份代码：

```cpp
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;
int divisor[101] = { 1 };


bool isPrime(int p) {
	if (p == 0 || p == 1)
		return false;
	else {
		for (int i = 2; i < p; i++) {
			if (p % i == 0)
				return false;
		}
		return true;
	}
} // 判断素数

long long power(int p, int a) {
	if (a == 1)
		return p;
	else {
		return power(p, a - 1) * p;
	}
} // 幂指数运算

int cur = 1;

void div(int n) {
	if (n == 1)
		divisor[cur] = 1;
	else {
		for (int i = n; i >= 2; i--) {
			if (isPrime(i) && n % i == 0) {
				divisor[cur] = i;
				cur++;
				div(n / i);
				break;
			}
		}
	}
} // 从大到小排列n的质因子


int main() {
	long long n, ans = 1;
	cin >> n;
	div(n);
	if (n == 1)
		ans = 1;
	} else {
		for (int i = 1; i <= 100; i++) {
			divisor[i]--;
		}
		int p = 2;
		for (int i = 1; i <= 100; i++) {
			while (!isPrime(p))
				p++;
			if (isPrime(p)) {
				if ((divisor[i]) == 0)
					break;
				else {
					ans *= power(p, divisor[i]);
				}
			}
			p++;
		}
	}
	cout << ans;

	return 0;
}
```
结果：`WA`。

根据评测系统的提示，我发现当 $n=8$ 时，我的程序输出结果与预期不一致，原来是调整出了问题。细心的同学可能会发现，当 $n=2^k$ 时，我们的调整方法是无效的，例如说 $n=8$ 的情况，根据原程序，它将会返回 $2\cdot3\cdot5=30$，但显然此时如果我们将 $8$ 拆成 $4\cdot 2$ 而非 $2\cdot 2\cdot 2$，那么此时输出的结果应该是 $2^3\cdot 3=24$（注意，这里仍不能完全把指数幂归到 $2$ 上面，否则就**调整过度了！**）

终于，我们可以得到完整 `AC` 代码，如下所示：

## 二、完整代码
```cpp
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;
int divisor[101] = { 1 };


bool isPrime(int p) {
	if (p == 0 || p == 1)
		return false;
	else {
		for (int i = 2; i < p; i++) {
			if (p % i == 0)
				return false;
		}
		return true;
	}
}

bool isTwopower(int n) {
	if (n == 2)
		return true;
	else {
		if (n % 2 != 0)
			return false;
		else {
			return isTwopower(n / 2);
		}
	}
} // 判断是否为2的幂

long long power(int p, int a) {
	if (a == 1)
		return p;
	else {
		return power(p, a - 1) * p;
	}
}

int cur = 1;

void div(int n) {
	if (n == 1)
		divisor[cur] = 1;
	else {
		for (int i = n; i >= 2; i--) {
			if (isPrime(i) && n % i == 0) {
				divisor[cur] = i;
				cur++;
				div(n / i);
				break;
			}
		}
	}
}


int main() {
	long long n, ans = 1;
	cin >> n;
	div(n);
	if (n == 1)
		ans = 1;
	else if (isTwopower(n) && n >= 8) {
		for (int i = 1; i <= 100; i++) {
			divisor[i]--;
		}
		ans *= 8;
		int p = 3;
		for (int i = 3; i <= 100; i++) {
			while (!isPrime(p))
				p++;
			if (isPrime(p)) {
				if ((divisor[i]) == 0)
					break;
				else {
					ans *= power(p, divisor[i]);
				}
			}
			p++;
		}
	} else {
		for (int i = 1; i <= 100; i++) {
			divisor[i]--;
		}
		int p = 2;
		for (int i = 1; i <= 100; i++) {
			while (!isPrime(p))
				p++;
			if (isPrime(p)) {
				if ((divisor[i]) == 0)
					break;
				else {
					ans *= power(p, divisor[i]);
				}
			}
			p++;
		}
	}
	cout << ans;

	return 0;
}
```

---

## 作者：FAQmother (赞：1)

DP方法

Mst数组表示用第i个素数之前有j个因数，用后还剩下需要消除的因数个数
f数组表示第i个素数用后使得剩下j个因数所需的答案log10之后的数
关于为什么要log10：因为约数定理是乘法，而乘法会比较麻烦，所以转成位数后用加法实现，这也是为什么lg和from数组要用double的原因

```cpp
#include<bits/stdc++.h> 
#define maxn 50010
#define int long long
#define mo 1000000000
using namespace std;
int zhi[20]={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53},n,mst[20][maxn];
double lg[20],f[20][maxn];
struct bignum
{
    int a[2300];
    bignum(int i=0)
    {
        memset(a,0,sizeof a);
        if(!i) return;
        a[0]=1;
        a[1]=i;
    }
    friend bignum operator *(bignum x,bignum y)
    {
        bignum z;
        for(int i=1;i<=x.a[0];i++)
        {
            int p=0;
            for(int j=1;j<=y.a[0];j++)
            {
                p+=x.a[i]*y.a[j]+z.a[i+j-1];
                z.a[i+j-1]=p%mo;
                p/=mo;
            }
            z.a[i+y.a[0]]=p;
        }
        z.a[0]=x.a[0]+y.a[0];
        while(z.a[0]&&!z.a[z.a[0]])
            z.a[0]--;
        return z;
    }
    void print()
    {
        printf("%lld",a[a[0]]);
        for(int i=a[0]-1;i>0;i--)
            printf("%09lld",a[i]);
        puts("");
    }
};
bignum power(int x,int y)
{
    bignum s=bignum(1),p=bignum(x);
    if(y==0) return s;
    for(;y;y/=2,p=p*p)
        if(y&1) s=s*p;
    return s;
}
void work(int i,int j,int k)
{
    if(f[i][k]<=f[i-1][j]+(j/k-1)*lg[i]) return;
    mst[i][k]=j;
    f[i][k]=f[i-1][j]+(j/k-1)*lg[i];
}
signed main()
{
    for(int i=1;i<17;i++)
        lg[i]=log10(zhi[i]);
    scanf("%d",&n);
    if(n==1)
    {
        puts("1");
        return 0;
    }
    for(int i=0;i<=16;i++)
        for(int j=1;j<=n;j++)
            f[i][j]=1e15;
    f[0][n]=1;
    for(int i=1;i<17;i++)
        for(int j=1;j<=n;j++)
        {
            if(n%j) continue;
            int k=1;
            for(;k*k<j;k++)
            {
                if(j%k) continue;
                work(i,j,k);
                work(i,j,j/k);
            }
            if(k*k==j) work(i,j,k);
        }
/*循环中i表示第i个素数，j表示未使用第i个素数前剩下的因数个数，k表示使用第i个素数后剩下的因数个数，即当前使用的实际是j/k-1个*/
    int j=1;
    bignum ans=bignum(1);
    for(int i=16;i;i--)
    {
        ans=ans*power(zhi[i],mst[i][j]/j-1);
        j=mst[i][j];
    }
    ans.print();
    return 0;
}
```


---

## 作者：Styx (赞：1)

首先需要一下约数个数和的公式  
假设该数为$x$

$x=\prod pi^{k_i}$

则

$f(x)=\prod (1+k_i)$

所以如果把$n$拆成若干个因数的乘积的形式以后，我们就可以知道每个数的幂次是多少，显然幂次分配的时候优先把大的分给小的质数

然后爆搜一下就可以了

如果担心爆longlong，可以把快速幂和答案存成double

代码如下:
```cpp
#include<bits/stdc++.h>
using namespace std;

int n;
int p[]={1,2,3,5,7,11,13,17,19,23,29,31,37,41,47},a[20];
long long ans=0x3f3f3f3f3f3f3f3f;

double kasumi(double a,long long b)
{
	double res=1;
	while(b)
	{
		if(b&1) res=res*a;
		a=a*a;
		b>>=1;
	}
	return res;
}

int dfs(int pos,int now)
{
	if(now==1)
	{
		double res=1;
		for(int i=1;i<=pos-1;i++)
		{
			res=res*kasumi(p[i],a[i]-1);
		}
		if(res<=1e18) ans=min(ans,(long long)res);
		return 0;
	}
	for(int i=now;i>=2;i--)
	{
		if(now%i==0) a[pos]=i,dfs(pos+1,now/i);
	}
}

int main()
{
	cin>>n;
	dfs(1,n);
	printf("%lld\n",ans);
}
```

---

## 作者：Composite_Function (赞：0)

# 前置芝士

**为书写方便，我们用 $d(n)$ 表示 $n$ 的因子数**

-----------

## 芝士1

$\forall n = \prod_{i = 1}^{m} p _ i ^ {q _ i} ~~ d(n) = \prod_{i = 1} ^ m (q _ i + 1)$ （其中 $p$ 为质数，$q$ 为素数）

证明如下：

设 $k = \prod_{i = 1}^{m} p _ i ^ {r _ i}  | n $ , 则 $\forall i ~~ r _ i \leq q _ i$

$\therefore \forall i ~~ r _ i$ 有 $(q _ i + 1)$ 个可能。

$\therefore k$ 有 $\prod _ {i = 1} ^ m(q _ i + 1)$ 个可能。

------------

## 芝士2

若 $d(k) = \prod_{i = 1}^{n} q _ i ~~ k = \prod_{i = 1}^{m} p _ i ^ {q _ i - 1}$ （$q$ 单调上升，$p$ 为素数）

要使 $k$ 取最小值，就得满足： $p _ 1 = 2 , \forall 1 \leq i \leq m-1 ~~ p _ {i + 1}$ 为 ${p _ i}$ 之后的最小素数。

------------

既然已经有了**前置芝士**的辅助，不会的人不妨再试试做一做这题。

------------

# 思路

继续想的话，发现只要将 $n$ **拆分**成个个数的**乘积**，然后**从大到小**依次排列，分别作为指数与作为**底数**的**从小到大的素数**做幂次运算，所得结果**相乘**，就是**所求整数**。取最小值即可。

很容易想到，这道题采用的是 $\texttt{dfs}$ 算法。再结合上**快速幂**，**素数预处理**就可以了以及**求因子**。看似代码很长，其实很简单，只不过使多个算法放在一起了。难得有如此简单的 $\texttt{CF}$ 模板蓝题出现，非常建议做一做。

------------

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int P[100],_N=0,n,ans=1e18,f[100],cnt;
int qpow(int _x,int _y){
    int ans=1;
    while(_y>0){
        if(_y&1) ans*=_x;
        _y>>=1,_x*=_x;
    }
    if(ans<=0) return 1e18;
    /*快速幂不用解释吧
    能做这种题的人还不会快速幂？

    这里说明一下上面那句话
    万一程序有漏洞出现了负数
    至少这一种情况肯定不会出现*/
    return ans;
}
bool judge(int _x){
    /*判素数，应该都会
    因为常数很小
    没必要写线性筛*/
    if(_x<2) return false;
    for(int i=2;i<=sqrt(_x);i++)
        if(_x%i==0) return false;
    return true;
}
void init(int _x){
    for(int i=1;i<=_x;i++)
        if(judge(i)) P[++_N]=i;
    P[_N+1]=1e9;//防出界
    for(int i=1;i<=n;i++)
        if(n%i==0) f[++cnt]=i;
    /*提前筛出 n 的因子*/
    return ;
}
void dfs(int now,int lst,int p,int num){
    if(num<0||num>ans||P[p]>53) return ;
    /*如果搜索出界了就立马结束
    看 init() 就明白了*/
    if(now==1){ans=min(ans,num); return ;}
    for(int i=1;i<=lst;i++)
        if(now%f[i]==0) dfs(now/f[i],i,p+1,num*qpow(P[p+1],f[i]-1));
}
signed main(){
    cin>>n;
    init(50);
    /*预处理出前几项素数
    因为因子数不会很多
    处理这么几个足够用*/
    dfs(n,cnt,0,1);
    cout<<ans<<endl;
    return 0;
}
```

------------

最后的最后——

千山万水总是情，给个点赞行不行

---

## 作者：D2T1 (赞：0)

[link](https://www.luogu.com.cn/problem/CF27E)

> 唯一分解定理：
> 对于正整数 $a$，可以分解为 $a=\prod\limits_{i=1}^k{p_i}^{c_i}(p_i\in\Bbb{P},c_i\in\Bbb{Z^+})$，即分解素因数。
> 
根据排列组合的乘法原理，若 $a$ 有 $n$ 个因数，则 $n=\prod\limits_{i=1}^k(c_i+1)$。
此时，最小的 $a$ 满足：

- $p_i$ 为第 $i$ 个质数（否则可以用更小的质数顶替 $p_i$，使 $a$ 更小）
- $c_{i-1}\leq c_i$（否则换过来，$a$ 能更小）

然后怎么办？搜啊。

因为 $2*3*5*7*11*...*53>10^{18}$，$p_i$ 只用搜到 $53$ 即可。
如果搜到的 $a$ 大于 $10^{18}$ 或者小于等于 $0$（后者必然是 `long long` 溢出了），直接剪掉。

不需要加什么额外的剪枝就能过了。

```cpp
//CF27E
#include <bits/stdc++.h>
using namespace std;

const int P[] = {1,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,51,53,100};
const long long mx = 1e18 + 1;
int n, fac[100], cnt;
long long ans = mx;

long long qp(long long a, long long b){//快速幂写多了感觉比写正常幂还快
	long long ans = 1;
	while(b){
		if(b&1) ans = ans * a;
		a = a * a, b >>= 1;
	}
	if(ans <= 0) return mx;
	return ans;
}
void dfs(int now, int lst, int prime, long long mul){
	if(mul < 0 || mul > mx || P[prime] > 53) return;
	if(now == 1){ ans = min(ans, mul); return; }
	for(int i = 1; i <= lst; ++ i)
		if(now%fac[i]==0) dfs(now/fac[i], i, prime+1, mul*qp(P[prime+1], fac[i]-1));
	return;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; ++ i) if(n%i == 0) fac[++cnt] = i;
	dfs(n, cnt, 0, 1);
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Xiao_mo (赞：0)


# Step1
## [题面](https://www.luogu.com.cn/problem/CF27E)
看到题面，发现数据范围很小，而且还限制了答案不超过 $10^{18}$ ，于是就想到了dfs剪枝。
# Step2
首先筛质数，筛20个差不多。
```cpp
for(int i=2;i<N;i++){
	if(!vis[i])pri[++m]=i;
	for(int j=1;j<=m&&i*pri[j]<N;j++){
		vis[i*pri[j]]=1;
		if(!(i%pri[j]))break;
	}
}
```
# Step3
设 $x=p_1^{a_1}p_2^{a_2}......p_{n-1}^{a_{n-1}}p_n^{a_n}$

所以 $x$ 的因子个数 $=(a_1+1)(a_2+1)......(a_{n-1}+1)(a_n+1)$

# Step4
考虑贪心。

首先 $p_i$ 代表第 $i$ 个质数。

所以 {$p_n$} 为单调增的序列。

当 $a_i=a_j,i<j$ ，此时让乘上一个 $p_i$ 显然优于乘上一个 $p_j$ 。

所以 {$a_n$} 为一个单调不上升的序列。

# Step5
dfs+剪枝。

首先开的 $long$ $long$ 。

1. 若答案小于 $0$ 或者大于 $10^{18}$ 则 return 。

2. 若目前的数已经比搜过的答案小则 return 。


```
inline void dfs(int s,int k,ll x){
	if(x<0||x>inf)return;
	if(x>minn)return;
	if(k==1){
		if(minn>x)minn=x;
		return;
	}
	double t=log(inf-x)/log(pri[s]);
	//t表示最多可以乘上的pri[s]的个数 
	for(int i=_min((int)t+1,k);i>1;i--){
		if(k%i==0)dfs(s+1,k/i,x*qpow(pri[s],i-1)); 
	}
}
```

# End

---

