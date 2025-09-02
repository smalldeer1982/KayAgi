# Bewitching Stargazer

## 题目描述

「我祈祷能拥有一颗透明的心，以及一双满含泪水的眼睛...」

—— 逃跑计划，《夜空中最亮的星》

Iris 仰望星空时，脑海中产生了一个有趣的问题。她希望你能帮忙解决这个问题，据说这样能引发一场流星雨。

夜空中有 $n$ 颗星星，排列成一行。Iris 拿着望远镜来观察这些星星。

最初，她观察整个区间 $[1, n]$，此时她的幸运值为 $0$。为了找到每个观察区间 $[l, r]$ 中的中间星星，Iris 开始了以下的递归过程：

- 首先，她计算中点位置 $m = \left\lfloor \frac{l+r}{2} \right\rfloor$。
- 如果区间长度（即 $r - l + 1$）是偶数，则她将该区间分成两个长度相等的子区间 $[l, m]$ 和 $[m+1, r]$，继续观察。
- 如果是奇数，则她会将望远镜对准第 $m$ 颗星星，幸运值增加 $m$；之后，如果 $l \neq r$，她会继续观察新产生的两个区间 $[l, m-1]$ 和 $[m+1, r]$。

Iris 有点懒，并以一个整数 $k$ 表示她的懒惰阈值：在观察过程中，任何长度严格小于 $k$ 的区间 $[l, r]$ 她都不会再继续观察。请你预测她最终的幸运值会是多少。

## 说明/提示

在第一个测试用例中，初始观察区间是 $[1, 7]$。由于该区间长度为奇数，Iris 聚焦于第 $4$ 颗星星，幸运值增加 $4$。然后她将观察区间分成 $[1, 3]$ 和 $[5, 7]$。$[1, 3]$ 再次是奇数，于是她观察第 $2$ 颗星星，幸运值再增 $2$。此后其被分为 $[1, 1]$ 和 $[3, 3]$，因其长度都小于 $2$，所以不再观察。区间 $[5, 7]$ 的过程类似，最终幸运值增加 $6$。所以最终的幸运值为 $4 + 2 + 6 = 12$。

在最后一个测试用例中，Iris 最终观察到了所有星星，其最终幸运值为 $1 + 2 + \cdots + 8\,765\,432 = 38\,416\,403\,456\,028$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
6
7 2
11 3
55 13
5801 6
8919 64
8765432 1```

### 输出

```
12
18
196
1975581
958900
38416403456028```

# 题解

## 作者：GoldenSTEVE7 (赞：4)

考虑分治。

对于一个区间 $[l,r]$，如果 $(r-l+1) < k$，那么这个区间就不用处理了，答案为 $0$。

接下来考虑 $(r-l+1) \ge k$ 的情况：

假设区间长度为偶数，那么将这个区间分割为 $[l,mid]$ 和 $[mid+1,r]$。首先递归计算 $[l,mid]$ 的答案。如果这个区间的答案为 $x$，共选出了 $y$ 个星星，那么显然右半边的答案为 $mid \times x + y$。如果区间长度为奇数，那么加上一个中间的数，即为这个区间的答案。

这样就可以做到单组时间复杂度 $O(\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef long long ll;
pair<int, int> solve1(ll l, ll r, ll k) {
	if((r-l+1) < k) return {0, 0};
	if((r-l+1) % 2) {
		pair<int, int> x = solve1(l, (l+r)/2-1, k);
		long long rgt_ans = ((r-l+1) / 2 + 1) * x.second + x.first;
		return {x.first + rgt_ans + (l+r)/2, x.second * 2 + 1};
	} else {
		pair<int, int> x = solve1(l, (l+r)/2, k);
		int rgt_ans = ((r-l+1) / 2) * x.second + x.first;
		return {x.first + rgt_ans, x.second * 2};
	}
}
signed main() {
	int t; cin >> t;
	while(t--) {
		int n, k; cin >> n >> k; cout << solve1(1, n, k).first << endl;
	} 
	return 0;
}
```

---

## 作者：Even_If (赞：3)

很好的一道规律题。

# $\texttt{Solution}$
开题，我们可以想到朴素的分治，代码如下：
```cpp
void solve(int l, int r) {
	int len = r - l + 1;

	int mid = (r - l) / 2 + l;

	if(len & 1) {
		ans += mid;

		solve(l, mid - 1), solve(mid + 1, r);
	}

	else {
		solve(l, mid), solve(mid + 1, r);
	}
}
```

T 到飞起。

那么怎么办？

我们看看第一组样例，取出的数应该是：
`2 4 6`。

可以发现，这是有对称性的， $2+6=2\times4$。

所以，以 mid 为界，对于右边取到的每一个数，都能在左边取到的数中找到一个，使得这两个数的和是两倍的 mid。
那么我们每次只需要递归左边，就可以用左边的和以及左边取到数的数量，求出右边的和（详见代码）。

这样，单次分治查询的复杂度就变成了 $O(\log{n})$。

# $\texttt{Code}$
```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

int tt;

int n, k;

pair <int, int> solve(int l, int r) { // pair.first 表示在该区间内取到的和，pair.second 表示在该区间内取到的数的数量。
	int len = r - l + 1;

	if(len < k) return make_pair(0, 0); 

	if(len & 1) {
		int mid = (r - l) / 2 + l;

		auto k = solve(1, mid - 1);

		return make_pair(k.first + mid * k.second + k.first + mid, k.second * 2 + 1ll); // 右边的和即为左边数的数量乘上 mid 再加上左边数的和。总共会取到数的数量是左边数的数量乘 2 再加上 1，因为还有mid。
	}

	else {
		int mid = (r - l) / 2 + l;

		auto k = solve(1, mid);

		return make_pair(k.first + mid * k.second + k.first, k.second * 2); // 大致与 len 为奇数时相同，只是没有 mid。
	}
}

signed main() {
	cin >> tt;

	while (tt --) {
		cin >> n >> k;

		int u = solve(1, n).first;

		cout << u << endl;
	}

    return 0;
}
```

---

## 作者：lalaji2010 (赞：3)

# CF2053C Bewitching Stargazer

## 分析

又是一道结论题。

由于两边在进行区间拆分的过程中是严格对称的，所以最终的答案显然是某个系数 $c$ 乘上中位数。

然后我们发现我们只需要一层一层模拟就好了，我们将 $n$ 不断除以二，设 $n$ 本身这一层为第 $0$ 层；如果第 $k$ 层的 $n$ 是奇数，令 $cnt$ 加上 $2^k$ 即可。

代码应该相当好懂，记得把 $n$ 的值先存一下，后面算中位数还要用到。

## AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
long long n,k;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>k;
		long long t=n;
		long long tmp=1;
		long long cnt=0;
		while(1){
			if(n<k){
				break;
			}
			if(n%2==1){
				cnt+=tmp;
			}
			n/=2;
			tmp*=2;
		}
		cout<<cnt*(1+t)/2<<"\n";
	}
	return 0;
}
```

---

## 作者：yvbf (赞：2)

![](bilibili:BV1WN6VYEEGs?t=819)

---

## 作者：ohjun (赞：1)

## 思路分析
可以发现对于一段区间的所有贡献点，就等于它对称的那个区间的贡献点的对称点。我们肯定不能去递归所有区间，所以考虑只向最左侧的那个区间递归（即左端点恒定为 $1$）。每次递归结束后返回在这段区间内贡献的总值和贡献点的数量，则右边这个对称的区间内每个贡献点都会额外做 $m + 1 - l$（右区间左端点与左区间的左端点的差值）的贡献。设左区间做的贡献值为 $v$，贡献点数为 $p$，那么左右区间的贡献总值就为 $v \cdot 2 + p \cdot (m + 1 - l)$。注意如果长度是奇数还要再加上 $m$，做贡献的点数也要加 $1$，区间长度小于 $k$ 就直接返回。时间复杂度 $O(\log{n})$。
## Code

```cpp
#include <bits/stdc++.h>
typedef long long ll;
typedef std::pair<ll, ll> pll;
int t, n, k;

pll solve(int r)
{
	if(r < k) return {0LL, 0LL};
	ll m = ((r + 1) >> 1);
	if(r & 1) 
	{
		pll now = solve(m - 1);
		return {(now.first << 1LL) + now.second * m + m, (now.second << 1LL) + 1LL};
	}
	else
	{
		pll now = solve(m);
		return {(now.first << 1LL) + now.second * m, (now.second << 1LL)};
	}
}

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cin >> t;
	while(t--)
	{
		std::cin >> n >> k;
		std::cout << solve(n).first << '\n';
	}
	return 0;
}
```

---

## 作者：yszkddzyh (赞：1)

递归。

记会对答案产生贡献的位置为**贡献位置**。

考虑现在递归到的区间：

若区间长度小于 $k$，返回。

若区间长度是偶数，则区间被分成左右两部分，而如果通过递归知道了左边的幸运值 $x$ 和左边贡献位置的数量 $y$，那么我们就能算出右边的幸运值，即 $x + y \times m$（$m$ 的含义与题目中相同），这相当于是把左边每个贡献位置向右平移了 $m$ 个单位，读者可以自己举几个例子验证。

若区间长度是奇数，则区间被分成左中右三部分。左右两部分与上同理，统计答案时带上中间的部分。

```cpp
#include <bits/stdc++.h>
#define pll pair <ll, ll>
#define mp make_pair
using namespace std;

typedef long long ll;
int T;
ll n, k;

pll solve(ll l, ll r){
//返回值是pll，first是幸运值，second是贡献位置的数量
	if(r - l + 1 < k) return mp(0, 0);
	ll mid = ((r - l) >> 1) + l, res = 0, cnt = 0;
	if((r - l + 1) % 2){
		res += mid;
		cnt++;
		pll tmp = solve(1, mid - 1);
		res += tmp.second * mid + tmp.first * 2;
		cnt += tmp.second * 2;
	}
	else{
		pll tmp = solve(1, mid);
		res += tmp.second * mid + tmp.first * 2;
		cnt += tmp.second * 2;
	}
	return mp(res, cnt);
}

int main(){

	ios :: sync_with_stdio(false);
	cin >> T;
	while(T--){
		cin >> n >> k;
		cout << solve(1, n).first << '\n';
	}

	return 0;
}

```

---

## 作者：GeYang (赞：0)

# 思路

因为主人公全程都在进行所谓的二分查找，所以整个过程可以说是完全对称的。

因此，最终答案一定是中值的倍数。

接下来模拟即可，从 $n$ 开始，每次除以二，如果是奇数就让层数加上 $2^k$，直至 $n<k$ 为止。

---

## 作者：lgx57 (赞：0)

赛时写了一个超级复杂的代码。

首先考虑直接暴力递归，但是这样的代码在最坏情况下是 $O(n)$ 的，所以我们可以考虑一下优化。

当我们递归时，我们需要分别计算左区间和右区间，但是我们其实可以只算出来其中的一个区间，然后推出另外一个区间。

下面分 $2$ 种情况考虑。

1. $2 \mid len$

设当前递归到的区间为 $[l,r]$。

我们记 $cnt$ 为 $[l,mid-1]$ 的答案，通过找规律可以发现，如果左区间有 $num$ 个数被统计了答案，那么右区间的答案为 $cnt+num(mid-l+1)$。向上传回统计数时为 $2num$。

2. $2 \nmid len$

设当前递归到的区间为 $[l,r]$。

我们记 $cnt$ 为 $[l,mid-1]$ 的答案，通过找规律可以发现，如果左区间有 $num$ 个数被统计了答案，那么右区间的答案为 $cnt+num(mid-l+1)$。向上传回统计数时为 $2num+1$。请注意这里是 $2num+1$，因为当前的 $mid$ 也被统计了。


```cpp
#include<bits/stdc++.h>
#define int long long
#define fi first
#define se second
#define pii pair<int,int>
#define endl '\n'
#define pb push_back
#define ls(p) ((p)<<1)
#define rs(p) ((p)<<1|1)
#define lowbit(x) ((x)&(-(x)))
#define abs(x) ((x)>0?(x):(-(x)))
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
using namespace std;
int n,k;
pii dfs(int l,int r){
	int len=r-l+1;
	int mid=(l+r)>>1;
	int ans=0;
	int tmp=0;
	if (len&1){
		ans+=mid;
		int nlen=mid-l;
		if (nlen<k) return {ans,1};
		pii cnt=dfs(l,mid-1);
		ans+=cnt.fi*2+(nlen+1)*cnt.se;
		tmp+=1+cnt.se*2;
	}
	else{
		int nlen=mid-l+1;
		if (nlen<k) return {0,0};
		pii cnt=dfs(l,mid);
		ans+=cnt.fi*2+nlen*cnt.se;
		tmp+=cnt.se*2;
	}
	return {ans,tmp};
}
void sol(){
	cin>>n>>k;
	cout<<dfs(1,n).fi<<endl;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int t;
	cin>>t;
	while (t--) sol();
	return 0;
}

```

---

## 作者：wfc284 (赞：0)

我们不妨直接递归模拟算答案。  
定义 $f(l, r)$ 表示左右端点为 $l,r$ 的答案。记 $mid \gets \lfloor \frac{l+r}{2} \rfloor$，于是：
$$ 
f(l, r) = \begin{cases}
  f(l, mid)+f(mid+1,r) & (r-l+1) \equiv 0 \pmod 2 \\
  f(l, mid-1) + f(mid+1, r) + mid & {\text {otherwise.}}
\end{cases}
$$
这样做显然会 T，考虑如何优化。我们注意到每次由 $mid$ 分割，左右两边是对称的。显然，$mid$ 右边所有取到的点都可以由左边平移得到。设区间长度是 $len$，这个平移量 $d$ 就是 $\lceil \frac{len}{2} \rceil$。设左（右）边取到了 $c$ 个点，故右边的答案就是左边的答案加上 $d \cdot c$。  

于是改写一下函数，将求解函数定义为 `pair` 型，`first` 存答案，`second` 存区间内能取到的个数，直接算就好了。

```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define Linf 0x3f3f3f3f3f3f3f3f
#define pii pair<int, int> 
#define all(v) v.begin(), v.end()
#define int long long
using namespace std;

//#define filename "xxx" 
#define FileOperations() freopen(filename".in", "r", stdin), freopen(filename".out", "w", stdout)


namespace Traveller {
	
	int n, k;
	pii operator + (pii a, pii b) { return pii(a.first + b.first, a.second + b.second); }
	pii solve(int n) {
		if(n < k) return pii(0, 0);
		pii res = solve(n/2);
		if(n & 1) return res + res + pii(res.second * (1+n >> 1) + (1+n >> 1), 1);
		return res + res + pii(res.second * (n >> 1), 0);
	}
	
	void main() {
		scanf("%lld%lld", &n, &k);
		printf("%lld\n", solve(n).first);
	}
}

signed main() {
	#ifdef filename
		FileOperations();
	#endif
	
	int _;
	cin >> _;
	while(_--) Traveller::main();
	return 0;
}


```

---

## 作者：Redshift_Shine (赞：0)

由题可知，从一个区间内分裂出的两个区间的长度一定相同。同时由分裂方式可知，对答案产生贡献的值的构型仅与该区间的长度有关。

也就是说，分裂出两个区间时，只需要计算其中一个区间的答案以及该区间内对答案产生贡献的数的个数然后平移过去就可以了。

时间复杂度 $O(\sum \log n)$。

```c++
// #define Redshift_Debug
#ifdef Redshift_Debug
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
#include <chrono>
#include <cstdio>

using namespace std;
const int N = 1e5 + 10;
using ll = long long;
ll n, k;
using pii = pair<ll, ll>;
void init_global()
{
}
void init_local()
{
	scanf("%lld%lld", &n, &k);
}
pii dfs(ll l, ll r)
{
	if (r - l + 1 < k)
		return {0, 0};
	ll mid = (l + r) >> 1;
	if ((r - l + 1) & 1 ^ 1)
	{
		auto [va, trm] = dfs(l, mid);
		return {va * 2 + trm * (mid + 1 - l), trm << 1};
	}
	auto [va, trm] = dfs(l, mid - 1);
	return {va * 2 + trm * (mid + 1 - l) + mid, trm << 1 | 1};
}
void run()
{
	printf("%lld\n", dfs(1, n).first);
}
int main()
{
#ifdef Redshift_Debug
	auto st = chrono::high_resolution_clock::now();
#endif
	int T = 1;
	scanf("%d", &T);
	init_global();
	while (T--)
	{
		init_local();
		run();
	}
#ifdef Redshift_Debug
	auto ed = chrono::high_resolution_clock::now();
	fprintf(stderr, "%.9lf\n", (ed - st).count() / 1e9);
#endif
}
```

---

## 作者：_lmh_ (赞：0)

归纳法易证同一层搜索的所有区间长度相等，记录左端点之和、区间个数，按题意模拟即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=100007;
ll T,n,k,ans,sum,cnt;
int main(){
	cin>>T;
	while(T--){
		cin>>n>>k;
		ans=0;sum=0;cnt=1;
		while(n>=k){
			if (n&1){
				ans+=sum+cnt*(n+1>>1);sum=sum*2+cnt*(n+1>>1);cnt<<=1;
			}
			else{
				sum=sum*2+cnt*(n/2);cnt<<=1;
			}
			n>>=1;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

