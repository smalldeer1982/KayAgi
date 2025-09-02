# Effects of Anti Pimples

## 题目描述

Chaneka has an array $ [a_1,a_2,\ldots,a_n] $ . Initially, all elements are white. Chaneka will choose one or more different indices and colour the elements at those chosen indices black. Then, she will choose all white elements whose indices are multiples of the index of at least one black element and colour those elements green. After that, her score is the maximum value of $ a_i $ out of all black and green elements.

There are $ 2^n-1 $ ways for Chaneka to choose the black indices. Find the sum of scores for all possible ways Chaneka can choose the black indices. Since the answer can be very big, print the answer modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example, below are the $ 15 $ possible ways to choose the black indices:

- Index $ 1 $ is black. Indices $ 2 $ , $ 3 $ , and $ 4 $ are green. Maximum value among them is $ 19 $ .
- Index $ 2 $ is black. Index $ 4 $ is green. Maximum value among them is $ 14 $ .
- Index $ 3 $ is black. Maximum value among them is $ 19 $ .
- Index $ 4 $ is black. Maximum value among them is $ 9 $ .
- Indices $ 1 $ and $ 2 $ are black. Indices $ 3 $ and $ 4 $ are green. Maximum value among them is $ 19 $ .
- Indices $ 1 $ and $ 3 $ are black. Indices $ 2 $ and $ 4 $ are green. Maximum value among them is $ 19 $ .
- Indices $ 1 $ and $ 4 $ are black. Indices $ 2 $ and $ 3 $ are green. Maximum value among them is $ 19 $ .
- Indices $ 2 $ and $ 3 $ are black. Index $ 4 $ is green. Maximum value among them is $ 19 $ .
- Indices $ 2 $ and $ 4 $ are black. Maximum value among them is $ 14 $ .
- Indices $ 3 $ and $ 4 $ are black. Maximum value among them is $ 19 $ .
- Indices $ 1 $ , $ 2 $ , and $ 3 $ are black. Index $ 4 $ is green. Maximum value among them is $ 19 $ .
- Indices $ 1 $ , $ 2 $ , and $ 4 $ are black. Index $ 3 $ is green. Maximum value among them is $ 19 $ .
- Indices $ 1 $ , $ 3 $ , and $ 4 $ are black. Index $ 2 $ is green. Maximum value among them is $ 19 $ .
- Indices $ 2 $ , $ 3 $ , and $ 4 $ are black. Maximum value among them is $ 19 $ .
- Indices $ 1 $ , $ 2 $ , $ 3 $ , and $ 4 $ are black. Maximum value among them is $ 19 $ .

The total sum is $ 19+14+19+9+19+19+19+19+14+19+19+19+19+19+19 = 265 $ .

## 样例 #1

### 输入

```
4
19 14 19 9```

### 输出

```
265```

## 样例 #2

### 输入

```
1
0```

### 输出

```
0```

## 样例 #3

### 输入

```
15
90000 9000 99000 900 90900 9900 99900 90 90090 9090 99090 990 90990 9990 99990```

### 输出

```
266012571```

# 题解

## 作者：definieren (赞：19)

考虑分别计算每个 $a_i$ 对答案的贡献。

可以发现，如果你在 $a_i$ 这个位置染了黑色，所有 $i$ 的倍数的位置都会染上绿色，这部分对最大值的贡献就是 $\max_{i \cdot j \le n} a_{i\cdot j}$。所以可以对每个 $a_i$ 重新赋值为 $\max_{i \cdot j \le n} a_{i \cdot j}$。

然后问题就转化为了求 $a$ 的所有子序列的最大值之和。

所以可以对 $a$ 升序排序，然后 $a_i$ 对答案的贡献就是 $a_i \times 2^{i - 1}$。

时间复杂度 $O(n \ln n)$。



```cpp
const int MAXN = 1e5 + 9;
int n, a[MAXN], pw[MAXN];
int ans = 0;

int main() {
	n = Read<int>();
	for (int i = 1; i <= n; i ++) a[i] = Read<int>();
	for (int i = 1; i <= n; i ++)
		for (int j = i; j <= n; j += i)
			cmax(a[i], a[j]);
	sort(a + 1, a + n + 1), pw[0] = 1;
	for (int i = 1; i <= n; i ++) pw[i] = add(pw[i - 1], pw[i - 1]);
	for (int i = 1; i <= n; i ++) cadd(ans, int(1ll * a[i] * pw[i - 1] % MOD));
	Write(ans, '\n'); Flush();
	return 0;
}

```



---

## 作者：lwx20211103 (赞：11)

本题解相对将讲得更详细，争取让大多数人都能明白。

## 题意

给你一个数组 $a$，下标是 $1$ 至 $n$，每次可以选择任意多个下标（不能不选）进行操作（为了直观，下标设为 $i$，对应的数字设为 $a[i]$）。在每一次操作中，获得一个数字 $m$，它的值是这样的：

取 $i$ 的所有倍数，即 $i \times 1,i \times 2 \cdots i \times \lfloor \frac{n}{i} \rfloor$，这些数字统一记为 $j$，$m$ 的值就是 $\max(a[i],a[j])$，即为这些数字中最大的，因为可以选多个 $i$，每个 $i$ 对应的 $j$ 都要进行计算，来最终的值。

最后，答案就是在每一次选择中，各个 $m$ 之和。

如果还不明白可以看样例解释。

## 分析

既然提到选择，那应该跟组合脱不了干系。

首先一个定理：一个大小为 $n$ 的没有重复数字的集合的非空子集个数是 $2^n - 1$。所以，题目的操作所产生的集合数量就是 $2^n - 1$。

我们可以发现，如果其中如果选择了**对应位是最大值的下标**，那么无论其他，结果一定是最大值。一次往下，选择了次大值的下标，结果一定是次大值。

我们可以考虑预处理每一个下标 $i$，看它以及的所有倍数下标 $j$ 所能产生的最大值是多少。

预处理完之后，下一步该如何做？我们先看看，所有含最大值的子集有多少个，答案是 $2^{n - 1}$ 个。以下是推理：

含某一个数字的子集个数，我们可以看作是总的子集个数减去不含那个数字的子集个数。不含那个数，集合大小就是 $n - 1$，子集个数为 $2^{n - 1} - 1$。

那么，个数就是 $(2^{n} - 1) - (2^{n - 1} - 1) = 2^{n - 1}$，证毕。

以此类推，次大值的子集个数，因为最大值选过，我们把含它的所有子集排除，此时集合大小就变成了 $n - 1$，含次大值的子集个数相应地变成了 $2^{n - 2}$。

所以，排序一下预处理后每个下标的最大值，再根据每一位乘上所对应的个数就可以了。

瓶颈在于预处理和排序，时间复杂度 $\Theta(n\log n)$。

## 代码

会有一些注释来解释细节。

```cpp
// Problem: D. Effects of Anti Pimples
// Contest: Codeforces - Codeforces Round 902 (Div. 2, based on COMPFEST 15 - Final Round)
// URL: https://codeforces.com/contest/1877/problem/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define p_b push_back
#define ft first
#define nd second
#define pii pair<int, int>
#define pll pair<long long, long long>

using namespace std;

typedef long long ll;

const ll mod = 998244353;
ll nums[114514], maxsum[114514];

ll qpow(ll a, ll b) //快速幂模板，用于求a ^ b % mod，这里不多讲。
{
	ll res = 1;
	while (b)
	{
		if (b & 1)
			res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}

bool cmp(ll a, ll b) {return a > b;}//用于排序

int main()
{
	ll ans = 0;
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> nums[i];
	for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j += i)//求倍数 
			maxsum[i] = max(maxsum[i], nums[j]);
    //预处理每个下标所对应的最大值，可看上面，这里复杂度是 nlogn的。
	sort(maxsum + 1, maxsum + 1 + n, cmp);降序排序
	for (int i = n - 1; i >= 0; i--)
	{
		ans = (ans + qpow(2, i) * maxsum[n - i]) % mod;//n - i 为实际的数组下标。
	}
	cout << ans;
	return 0;
}

```


---

## 作者：aCssen (赞：5)

### Solution
首先，预处理 $f_i$ 表示只选了 $i$ 这个位置的价值，处理方法枚举倍数，时间复杂度 $\mathcal{O}(n \log n)$。

然后，我们将 $f$ 从小到大排序。

则答案为 $\sum_{i=1}^n 2^{i-1}f_i$。

因为一个序列的价值是其中数的最大值，所以每个序列中只要包含一个能取到最大值的数，这个序列的价值就是最大值，所以最大的 $f_i$ 对答案的贡献为 $f_i \times 2^{n-1}$，即所有集合中包含 $i$ 的集合，而 次大的 $f_j$ 对答案的贡献为 $f_j \times 2^{n-2}$，即所有集合中包含 $j$ 且不包含 $i$ 的集合，其余同理。

建议配合样例解释理解。
### Code
```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#define int long long
using namespace std;
const int maxn=1e5+5;
const int MOD=998244353;
int f[maxn],a[maxn],n;
long long p[maxn],ans;
void solve(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j+=i)
			f[i]=max(f[i],a[j]);
	p[0]=1;
	for(int i=1;i<=n;i++)
		p[i]=(p[i-1]*2)%MOD; 
	sort(f+1,f+n+1);
	for(int i=n;i>=1;i--)
		ans=(ans+(f[i]*p[i-1])%MOD)%MOD; 
	printf("%lld\n",ans);
}
signed main(){
	int t=1;
	while(t--) solve();
	return 0;
}
```

---

## 作者：LCat90 (赞：3)

很套路地想到确定最大值然后计算它的贡献次数。

所以想到从大到小排序，对于当前 $x$。都有使之能被选的下标 $id$，即它的因数。从大到小处理的好处就是，如果之前的数已经用了一个因数 $r$，那么它的贡献只能是之前的 $x'$，不能是当前的数 $x$。那么我们可以打标记，保证这个数一定是被选的最大值。

所以我们 $\sqrt n$ 地枚举出下标 $id$ 的因数，找出**满足约束的合法因数个数**，设为 $m$。

想一下怎么计算方案，发现是一个排列组合。对于这 $m$ 个因数，任意选 $1$ 个就可以使 $a_{id}$ 成为最大值，也即 $m$ 个数中任意选，只要不是空集。故有 $2^m-1$ 种选法。然后其它数呢？除了之前有约束的（已经被选过的，设有 $p$ 个）不能选，其它随便选。即 $2^{n-p-m}$，乘起来然乘 $a_i$ 加给答案。

考虑重复的问题，如果重复那么就说明一个集合所构成的数集对应的最大值不唯一，显然矛盾，故不会有重复。

时间复杂度是 $O(n\sqrt n)$。代码中用了 ``map``，但可以不用。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 4e5 + 5, Mod = 998244353;
int T, n, ans; bool vis[N];
struct node {
	int x, id;
	friend bool operator < (node a, node b) {
		return a.x > b.x;
	}
} p[N];
map <int, int > f;
int qkpow(int a, int b) {
	if(b == 0) return 1;
	if(b & 1) return a * qkpow(a, b - 1) % Mod; 
	int t = qkpow(a, b >> 1);
	return t * t % Mod;
}

void solve() {
	cin >> n;
	for(int i = 1;i <= n; ++i) cin >> p[i].x, p[i].id = i;
	sort(p + 1, p + n + 1); int m = n;
	for(int i = 1;i <= n; ++i) { // 在前面选的最大值 
		int num = 0; 
		for(int j = 1;j * j <= p[i].id; ++j) {
			if(j * j == p[i].id and vis[j]) continue ;
			else if(j * j == p[i].id) {
				num ++;
				vis[j] = 1;
			}
			if(p[i].id % j == 0) {
				num += (!vis[j]) + (!vis[p[i].id / j]);
				vis[p[i].id / j] = vis[j] = 1;
			}
		}
		ans += p[i].x * ((qkpow(2, num) - 1 + Mod) % Mod) % Mod * (qkpow(2, m - num)) % Mod;
		m -= num;
		ans %= Mod;
	}
	cout << ans;
}
signed main() {
	solve();
	return 0;
}
```

---

## 作者：xlpg0713 (赞：1)

## 题意：
你有一个长为 $n$ 的序列 $a(1\le n\le 10^5)$。现在你可以在序列中可重地选若干个下标，这个位置和下标的倍数的位置也会被选。获得的价值是选出的位置上数的最大值，不能不选。你显然有 $2^n-1$ 种选法，现在请你求出这些选法的价值总和，模 $998244353$。

## 思路：
我们并不关心一个位置上的数是什么，而应关心选了这个数后被选的数中最大的，这部分我们显然可以暴力扫一遍预处理出来，复杂度是 $\sum_{i-1}^n\frac{n}{i}=O(n\log n)$。

现在我们来考虑元素之间的贡献，考虑选了一个数，这次选择的价值由它来贡献当且仅当选了之后大于它的数一个都没有被选，而小于等于它的是可以随便选的。因此我们对预处理出来的结果排个序，设排序后的数组为 $b$。则答案 $res=\sum_{i-1}^nb_i\times 2^{i-1}$ 算一下发现刚好 $2^n-1$ 种，是正确的。

扫一遍是 $O(n)$ 排序是 $O(n\log n)$。总体就是 $O(n\log n)$ 的。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 998244353;
int t, n, a[100005], mx[100005];
signed main(){
    ios::sync_with_stdio(false);
    cin >> n; int res = 0;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++)
        for(int j = i; j <= n; j += i) mx[i] = max(mx[i], a[j]);
    sort(mx + 1, mx + n + 1);
    for(int i = 1, bas = 1; i <= n; i++, bas = bas * 2 % mod)
        res = (res + bas * mx[i]) % mod;
    cout<< res << '\n';
}
```

---

## 作者：escapist404 (赞：1)

给定长为 $n$ 的序列 $a$。

你可以选出整数集合 $\{x \mid 1 \le x \le n\}$ 的一个非空子集 $S$，令整数集合 $T = \{k \cdot x \mid x \in S, k \ge 1, k \cdot x \le n\}$。

定义一个选出 $S$ 的方案的分数为 $\max_{i \in T} a_i$。

求所有选出 $S$ 的方案的分数之和。

$1 \le n \le {10^5}$，$0 \le a_i \le {10^5}$。

---

考虑计算每个数的贡献。

注意到：对一个下标 $i$ 来说，只要其约数有一个选了，下标 $i$ 就必须选。但是我们不能选择比 $a_i$ 大的因数。

对于别的比 $a_i$ 小的数，可以随便选；对于比 $a_i$ 大的数（以及这些数对应的下标）就必须不选。

我们从大到小计算贡献：设 $F$ 为 $i$ 的约数集合，$G$ 为比 $a_i$ 大的数的下标 $j$（及其约数）的集合，则 $a_i$ 的贡献为 $a_i \times (2^{\mid F \mid - \mid F \cap G \mid} - 1) \times 2 ^ {\mid F \cup G \mid}$。

如何维护 $G$？每处理完一个数，就令 $G \gets F \cup G$。

预处理 $2^i$ 可以做到 $O(n^{\frac{3}{2}})$。

---

```cpp
#include <bits/stdc++.h>

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);

  int n;
  std::cin >> n;

  using i64 = long long;
  std::vector<i64> pow(n + 1);
  pow[0] = 1;
  const i64 p = 998'244'353;
  for (int i = 1; i <= n; ++i) {
    pow[i] = pow[i - 1] * 2ll % p;
  }

  auto find_factor = [](int x) {
    std::vector<int> factor = {1};
    for (int i = 2; i * i <= x; ++i) {
      if (x % i == 0) {
        factor.push_back(i);
        if (x / i != i) factor.push_back(x / i);
      }
    }
    if (x != 1) factor.push_back(x);
    return factor;
  };

  std::vector<std::pair<int, int>> a(n);
  int count = 0;
  for (auto& [id, val] : a) std::cin >> val, id = ++count;

  std::sort(a.begin(), a.end(),
            [](std::pair<int, int> x, std::pair<int, int> y) {
              if (x.second != y.second)
                return x.second > y.second;
              else
                return x.first < y.first;
            });

  std::vector<bool> chosen(n + 1);
  count = 0;

  i64 answer = 0;
  for (auto [id, val] : a) {
    auto factor = find_factor(id);
    int disable = 0;
    for (auto i : factor) {
      if (chosen[i]) disable++;
    }
    (answer += (pow[factor.size() - disable] - 1) *
               (pow[n - factor.size() + disable - count]) % p * val % p) %= p;
    for (auto i : factor) {
      if (chosen[i] == false) {
        ++count;
        chosen[i] = true;
      }
    }
  }

  std::cout << answer << '\n';

  return 0;
}
```

---

## 作者：Aleph_Drawer (赞：0)

首先，直接按照题目中所描述的方法进行统计的时间复杂度明显难以承受。此时一个比较基础经典却非常有效的技巧是：改变统计方式，改成对于每一个数计算它对答案的贡献。

考虑一个数 $a_i$ 怎样的情况下才能计入贡献。对于一种染色方式，假设 $a_i$ 造成了贡献，显然的，我们要保证大于 $a_i$ 的数的颜色都是白色的，其次，如果有枚举顺序的话，我们要保证**先枚举到的等于** $a_i$ 的数的颜色也是白色的。

这启示我们先对 $a_i$ 值排序，并从大到小去枚举。对于 $i$，不妨记录若 $a_i$ 要造成贡献哪些数不能被染成黑色，这些点显然包括了枚举顺序在它前面的所有的数的位置及其下标的因数位置。假设此类数集合为 $S$。接下来枚举 $i$ 的因数 $j$。如果 $j$ 已经被记录不能被染色，就不计入贡献中。否则就计入贡献，假设此类计入贡献的数集合为 $T$。此时，只要这些数中的任何一个或多个被染色，那么 $a_i$ 就会被染色。

那么 $a_i$ 的贡献明显是 $a_i(2^{n - |S|} - 2^{n - |S| - |T|})$。答案就是将这些贡献加起来。别忘了每次算完贡献之后要将 $T$ 中的点全部归到 $S$ 中。

时间复杂度是 $O(n \log{n})$ 的。

我的代码写的比较烂。

```c++
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll N = 1e5 + 105, MOD = 998244353;

ll n, a[N], p2[N], cnt, ans;
bool tag[N];
ll rng[N];

bool cmp(ll x, ll y) {
	return a[x] > a[y];
}

int main() {
	scanf("%lld", &n);
	p2[0] = 1;
	for(ll i = 1; i <= n; i++)
		scanf("%lld", &a[i]), p2[i] = p2[i - 1] * 2ll % MOD, rng[i] = i;
	stable_sort(rng + 1, rng + n + 1, cmp);
	ll cnt = 0, tmp = 0; // cnt := |S|, tmp := |T|
	for(ll i = 1; i <= n; i++) {
		ll pos = rng[i];
		if(tag[pos])
			continue;
		for(ll j = 1; j * j <= pos; j++) {
			if(!(pos % j)) {
				if(!tag[j]) {
					tmp++;
					tag[j] = 1;
				}
				if(!tag[pos / j]) {
					tmp++;
					tag[pos / j] = 1;
				}
			}
		}
		ans += (p2[n - cnt] - p2[n - cnt - tmp]) * a[pos] % MOD;
		cnt += tmp;
		tmp = 0;
		ans %= MOD;
	}
	printf("%lld\n", (ans % MOD + MOD) % MOD);
	return 0;
}
```

---

## 作者：accgj_ (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF1876B)



------------
题目大意：给定一个序列，选若干个下标，然后给答案加上这些下标的元素与下标是这些下标任意一个的倍数的元素中的最大值，求所有选法的总答案。



------------
转换一下，对于每一个元素，当它作为答案时，选的下标不能包含有比它大的元素的下标的因数，即对于元素从大到小考虑，每次分解因数，算出有多少个因数是比它大的元素没有的，再减去一个也不选的答案，就是该数的贡献，时间复杂度 $O(n\sqrt n)$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long mod=998244353;
inline long long ksm(long long a,long long k)
{
	long long ret=1;
	while(k)
	{
		if(k&1)ret=ret*a%mod;
		a=a*a%mod;k>>=1;
	}
	return ret;
}
int n;
struct asd
{
	long long a,id;
}a[1000001];
bool cmp(asd qw,asd qe){return qw.a>qe.a;}
long long p[1000001];
bool isp[1000001];
set<long long> s;
int main()
{
	for(int i=2;i<=100000;i++)
	{
		if(!isp[i])
		{
			p[++p[0]]=i;
		}
		for(int j=1;j<=p[0] and p[j]*i<=100000;j++)
		{
			isp[p[j]*i]=1;
			if(i%p[j]==0)break;
		}
	}
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i].a),a[i].id=i;
	sort(a+1,a+1+n,cmp);
	long long ans=0;
	for(int i=1;i<=n;i++)
	{
		long long a1=0,a2=a[i].a;//a1至少选一个
		for(int j=1;j*j<=a[i].id;j++)
		{
			if(a[i].id%j==0)
			{
				if(s.count(j)==0)
				{
					s.insert(j);
					a1++;
				}
				if(j*j==a[i].id)break;
				if(s.count(a[i].id/j)==0)
				{
					s.insert(a[i].id/j);
					a1++;
				}
			}
		}
		long long a3=n-(int)s.size();//a3可以都不选
		ans=(ans+(ksm(2,a1)-1)*ksm(2,a3)%mod*a2%mod)%mod;
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：anjack_511 (赞：0)

## 题意

给定一个数组 $[a_1,a_2,a_3.\cdots,a_n]$，一开始所有元素都为白色。你可以选定其中的至少一个元素涂成黑色，共有 $2^n - 1$ 种涂法。此时对于所有黑色元素 $a_i$ , 下标为 $i$ 的倍数的所有白色元素都将变成绿色。此时数组中所有黑色和绿色元素的**最大值**记为此种涂法的分数。

问对于所有 $a^n - 1$ 种涂法，每种涂法的分数之和为多少？

## 题解

我们考虑涂一个黑色元素 $a_i$，记所有下标为 $i$ 倍数的元素最大值为 $a_{imax}$。所有包含涂 $a_i$ 的方法共有 $2^{n-1}$ 种。但是这些方案中还可能涂了其他的黑色元素 $a_j$，使得 $a_{jmax} > a_{imax}$，所以计算 $a_i$ 的贡献中还要剔除掉这些分数比 $a_{imax}$ 大的方案数。

所以我们可以反着考虑，计算分数为 $a_i$ 时的贡献。先将数组从大到小排序。$a_i$ 作为方案的分数当且仅当 $i$ 是某个黑色元素的下标倍数，所以我们枚举 $i$ 的所有因数 $k$。如果 $k$ 之前被更大的 $a_j$ 枚举过，那么涂 $a_k$ 的方案的分数肯定是 $a_j$，不能记到分数为 $a_i$ 的贡献里。如果 $k$ 未被枚举过，那么此时 **分数为 $a_i$ 且涂了 $a_k$ 的方案** 的贡献为 **所有包含 $a_k$ 且不包含枚举过的数的方案数** 乘  $a_i$（包含枚举过的数的方案，之前记过更大的分数）。

开一个标记数组标记枚举过的因数。将 $a$ 数组从大到小排序。逐个考虑每一个 $a_i$ 的所有因数，同时记录此时 $1$ 至 $n$ 中还未被标记的数的个数 $t$：

1. 统计未被标记的因数个数 $b$，并标记这些因数。

2. 记录 $a_i$ 的贡献为 $c_{a_i} = a_i\sum\limits_{j = 1}^{b}2^{t-j}$，再将 $t$ 减 $b$。

**所有包含 $a_k$ 且不包含枚举过的数的方案数** 即为其中的 $2^{t - j}$。这是因为此时还未标记的数还有 $t - j$ 个，而真子集一共有 $2^{t - j}$ 种。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MAXN 100010
#define MOD 998244353
#define REP(a, b, i) for(int i = (a); i <= (b); i++)

ll dn[MAXN];
bool vis[MAXN];
int n;

struct Ai{
    int ind;
    ll num;
}ai[MAXN];

bool cmp(Ai x, Ai y)
{
    return x.num > y.num;
}

void calc2n() // 预处理 2 的幂
{
    dn[0] = 1;
    REP(1, n, i)
        dn[i] = ((dn[i - 1] << 1) + MOD) % MOD;
}

ll factor(ll i) //找因数
{
    int cnt = 0;
    for(ll k = 1; k * k <= i; k++){
        if(i % k == 0){
            if(!vis[k]) vis[k] = 1, cnt++;
            if(!vis[i / k]) vis[i / k] = 1, cnt++;
        }
    }
    return cnt;
}

ll cntsum(ll lf, ll ct) // 计算第 2 步中的求和
{
    ll ans = 0;
    for(ll i = 1; i <= ct; i++)
        ans = (ans + dn[lf - i]) % MOD;
    return ans;
}

void work() 
{
    sort(ai + 1, ai + 1 + n, cmp);
    ll lft = n, res = 0; // lft 为尚未标记的数的个数
    for(int i = 1; i <= n; i++){
        ll k = factor(ai[i].ind);
        res = (res + cntsum(lft, k) * ai[i].num % MOD) % MOD;
        lft -= k;
    }
    cout << res;    
}

int main()
{
    cin >> n;
    calc2n();
    REP(1, n, i){
        ai[i].ind = i;
        cin >> ai[i].num;
    }
    work();
    return 0;
}
```


---

## 作者：WilliamFranklin (赞：0)

这道题很简单，就是数学求贡献。

### 主要思路

因为如果选了这一个数，那么所有满足下标是这个数下标的倍数的数都会选。

首先，暴力求出每一个位置 $i$ 所有满足是 $i$ 倍数的 $j$ 中 $a$ 的最大值 $b_i$。

我用程序算了，$10^5$ 大概是运行 $1166750$ 次。

很明显，不会超时。

然后考虑 $b_i$ 何时会产生贡献。很容易就会想到，其实就是一开始不要选 $b$ 比 $b_i$ 的位置。

那么我们就找出所有满足 $b$ 小于等于 $b_i$ 的数量 $cnt$（注意：不包含 $i$）。

然后，我们考虑，这个 $b_i$ 的贡献就是 $C_{cnt}^{0} + C_{cnt}^{1} + \cdots + C_{cnt}^{cnt - 1} + C_{cnt}^{cnt}$，然后我们又知道这个式子等于 $2^{cnt}$，所以用快速幂，我们就可以求出这个 $b_i$ 的贡献。

因为考虑重复的情况，我们将 $j < i$ 的部分只要 $b_j \le b_i$ 的就计入 $cnt$，$j > i$ 的部分只有 $b_j < b_i$ 才能计入 $cnt$。直接用树状数组维护即可。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define mp(Tx, Ty) make_pair(Tx, Ty)
#define For(Ti, Ta, Tb) for(auto Ti = (Ta); Ti <= (Tb); Ti++)
#define Dec(Ti, Ta, Tb) for(auto Ti = (Ta); Ti >= (Tb); Ti--)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define range(Tx) begin(Tx),end(Tx) 
const int N = 1e5 + 5, mod = 998244353;
int n;
long long a[N];
long long tr[N];
long long cnt[N];
int lowbit(int x) {
	return x & -x;
}
void add(int x) {
	for (int i = x; i < N; i += lowbit(i)) tr[i]++;
}
long long sum(int x) {
	long long res = 0;
	for (int i = x; i; i -= lowbit(i)) res += tr[i];
	return res;
}
long long quickpow(long long a, long long b) {
	long long res = 1;
	while (b) {
		if (b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1; 
	}
	return res;
}
int main() {
	cin.tie(nullptr)->sync_with_stdio(false); 
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j += i) {
			a[i] = max(a[i], a[j]);
		}
	}
	for (int i = 1; i <= n; i++) {
		cnt[i] += sum(a[i]);
		add(a[i] + 1);
	}
	memset(tr, 0, sizeof(tr));
	Dec(i, n, 1) {
		cnt[i] += sum(a[i] + 1);
		add(a[i] + 1);
	}
	long long ans = 0;
	For(i, 1, n) {
		ans = (ans + a[i] * quickpow(2, cnt[i]) % mod) % mod;
	}
	cout << ans;
	return 0;
} 
```

### 谢谢观看

---

## 作者：recollect_i (赞：0)

从大往小枚举所有数，设它下标的因数中没有标记点有 $x$ 个，其它没有标记的点有 $y$ 个，则它出现的次数为 $(2^x-1)2^y$，然后标记所有它下标的因数。

预处理所有数的因数并用 vector 存，时间复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
 
#define x first
#define y second
 
using namespace std;
 
typedef pair<int, int> PII;
typedef long long LL;
 
const int N = 1e5 + 5, P = 998244353;
 
int n;
PII x[N];
bool st[N];
vector<int> d[N];
LL p[N];
 
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++ ) scanf("%d", &x[i].x), x[i].y = i;
	
	sort(x + 1, x + n + 1);
	reverse(x + 1, x + n + 1);
	for(int i = 1; i <= n; i ++ )
		for(int j = i; j <= n; j += i)
			d[j].push_back(i);
	
	p[0] = 1;
	for(int i = 1; i <= n; i ++ ) p[i] = p[i - 1] * 2 % P;
	
	int cnt = n;
	LL res = 0;
	for(int t = 1; t <= n; t ++ )
	{
		int i = x[t].y;
		if(!st[i])
		{
			LL f = 1;
			for(auto j : d[i])
				if(!st[j])
				{
					st[j] = 1;
					f = f * 2 % P;
					cnt -- ;
				}
			f = (f - 1 + P) % P * p[cnt] % P;
//			printf("!%d %lld\n", i, f);
			res = (res + f * x[t].x) % P;
		}
	}
	
	printf("%lld\n", res);
	return 0;
}
```

---

