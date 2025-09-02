# Maximum And Queries (hard version)

## 题目描述

This is the hard version of the problem. The only difference between the two versions is the constraint on $ n $ and $ q $ , the memory and time limits. You can make hacks only if all versions of the problem are solved.

Theofanis really likes to play with the bits of numbers. He has an array $ a $ of size $ n $ and an integer $ k $ . He can make at most $ k $ operations in the array. In each operation, he picks a single element and increases it by $ 1 $ .

He found the maximum [bitwise AND](https://en.wikipedia.org/wiki/Bitwise_operation#AND) that array $ a $ can have after at most $ k $ operations.

Theofanis has put a lot of work into finding this value and was very happy with his result. Unfortunately, Adaś, being the evil person that he is, decided to bully him by repeatedly changing the value of $ k $ .

Help Theofanis by calculating the maximum possible [bitwise AND](https://en.wikipedia.org/wiki/Bitwise_operation#AND) for $ q $ different values of $ k $ . Note that queries are independent.

## 说明/提示

In the first test case, in the first query, we add $ 1 $ in the first and last elements of the array.

Thus, the array becomes $ [2,3,7,6] $ with bitwise AND equal to $ 2 $ .

In the second test case, in the first query, we add $ 1 $ in the first element, $ 5 $ in the second, and $ 3 $ in the third and now all the elements are equal to $ 5 $ .

## 样例 #1

### 输入

```
4 2
1 3 7 5
2
10```

### 输出

```
2
6```

## 样例 #2

### 输入

```
3 5
4 0 2
9
8
17
1
3```

### 输出

```
5
4
7
0
1```

## 样例 #3

### 输入

```
1 2
10
5
2318381298321```

### 输出

```
15
2318381298331```

# 题解

## 作者：MaxBlazeResFire (赞：19)

这个题很会创人啊。经典 $\rm D$ 难于 $\rm E$。

首先一眼贪心，设当前正在确定答案第 $i$ 位为 $0$ 还是 $1$。而所有数可以分为 $2$ 类，第一类数是在之前因为 $ans$ 的变化被迫与其贴齐，那么它的低 $i$ 位必然全部为 $0$，造成的代价为 $2^i$；第二类数则是之前完全没有变过，也即 $ans$ 是其高位的子集，如果这类数一共有 $f_i$ 个，其低 $i$ 位总和为 $g_i$，那么代价就是 $f_i\times 2^i-g_i$。

瓶颈在于求出每次贪心的 $f$ 和 $g$。注意到这类数需要满足高位在 $ans$ 对应的位置上有，而在第 $i$ 位上没有。预处理的时候枚举 $i$，针对那些第 $i$ 位为 $0$ 的数，处理出数列 $\displaystyle A_i=\sum_{i\subseteq j}1,B_i=\sum_{i\subseteq j}v_j$，其中 $v_j$ 是 $a_j$ 低 $i$ 位的值。这个东西直接高维后缀和就好。

复杂度 $O(V\log^2V+q\log V)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 1200005

int n,q,a[MAXN],f[20][MAXN],g[20][MAXN];

signed main(){
	scanf("%lld%lld",&n,&q); int S = 0;
	for( int i = 1 ; i <= n ; i ++ ) scanf("%lld",&a[i]),S += ( 1 << 20 ) - a[i];
	for( int p = 19 ; p >= 0 ; p -- ){
		for( int j = 1 ; j <= n ; j ++ ) if( !( a[j] >> p & 1 ) ) f[p][a[j]] ++,g[p][a[j]] += a[j] & ( ( 1 << p ) - 1 );
		for( int k = 0 ; k <= 19 ; k ++ )
			for( int i = MAXN - 5 ; i >= 0 ; i -- )
				if( i & ( 1 << k ) ) f[p][i - ( 1 << k )] += f[p][i],g[p][i - ( 1 << k )] += g[p][i];
	}
	for( int i = 1 ; i <= q ; i ++ ){
		int k; scanf("%lld",&k);
		if( k >= S ){ printf("%lld\n",( 1 << 20 ) + ( k - S ) / n ); continue; }
		int res = 0,cat = 0;
		for( int p = 19 ; p >= 0 ; p -- ){
			int cost = cat * ( 1 << p ) + f[p][res] * ( 1 << p ) - g[p][res];
			if( k >= cost ) cat += f[p][res],res += 1 << p,k -= cost;
		}
		printf("%lld\n",res);
	}
	return 0;
}
```

---

## 作者：蒟蒻君HJT (赞：7)

建议先看 [easy version 的题解](https://www.luogu.com.cn/blog/hokarikanae/cf1903d1-maximum-and-queries-easy-version-ti-xie)。

$nq$ 变大了很多，不能再暴力求解。不过每次询问按位贪心的过程是可以有的（并且也少不了），于是考虑优化掉每次贪心都要遍历所有数而消耗的 $\Theta(n)$ 的复杂度。

注意到一个性质：当一个数被更新到拥有 $2^i$ 这一位之后，它的更低位目前一定都是 $0$。也就是说，后面遍历到更低位，希望它能有这个更低位 $2^j (j < i)$ 时，这个数消耗的代价为 $2^j$，是个相对确定的值。
x
另外你在做 easy version 的时候可能会发现 $a_i$ 的范围异常的小（不大于 $10^6 < 2^{20}$）这一点在 easy version 里似乎并没有用到。

由此可以想到根据答案的最高位 $2^w$ 进行讨论。对每个询问求出答案的最高位是简单的，预处理每一位的代价即可。

如果 $w\geq 20$，所有数经过第一次变换后，都变成了 $2^w$，设剩下的操作次数为 $c$，那么最终答案为 $2^w + \displaystyle\lfloor \frac{c}{n}\rfloor$。

如果 $w\leq 19$，接下来我们按位贪心。假设目前答案为 $ans$，我们现在在贪的位是 $2^i$，剩余的操作次数为 $c$，那么我们现在需要知道的就是要把所有数都变得有 $ans + 2^i$ 中所有的位的最小代价是否不大于 $c$。考虑 $ans$ 到 $ans + 2^i$ 的增量。发生的变化有两类：第一类数 $x$，它在之前已经发生过变化，即 $x \& ans < ans$，那么本次操作它的代价为 $2^i$，需要在此前的贪心过程中维护这样的数的个数 $fik$。另一种产生代价的数 $y$ 满足 $y \& ans = ans$，但 $y \& (ans + 2^i) < (ans + 2^i)$ 即 $y$ 有 $ans$ 的所有位但没有 $2^i$ 这一位。设这样的数的个数为 $f$，总和为 $g$，根据 easy version 的贪心结论，这类数的总代价为 $f\times 2^i - g$。

以上总代价为 $fik\times 2^i + f\times 2^i - g$。怎么求出 $f$ 和 $g$？发现符合要求的数满足“某一位必须不存在，这一位之前的指定的若干位必须存在”，预处理时可以枚举不存在的位，剩下的是半个 FMT-or，即超集求和。注意到贪到 $2^i$ 可以加入 $ans$ 的时候，要更新剩余的操作次数和 $fik$。

启发：看到奇怪的数据范围一定要深入思考为什么是这样。~~如果赛后发现没什么道理的话就喷出题人。~~

[for reference only.](https://codeforces.com/contest/1903/submission/235188787)

---

## 作者：Little09 (赞：5)

单 $\log$ 做法。

首先观察到如果最终答案大于等于 $2^{20}$，那么所有数都必须加到至少 $2^{20}$，因此我们把所有数先加到 $2^{20}$ 后，所有数都是相等的，所以最终答案就是 $\lfloor\frac{k-sum}n\rfloor+2^{20}$，其中 $sum$ 为把所有数都加到 $2^{20}$ 的代价。

重点在最终答案小于 $2^{20}$ 的部分，此时我们需要对每个 $0\sim 2^{20}-1$ 的数计算出最小的 $k$ 即可。那就先考虑暴力一点的做法，考虑最后需要满足 AND 结果为 $x$ 时（也可以是 $x$ 的超集），对一个 $a_i$ 需要操作多少次，经过一些简单的观察可以得到：我们先找到最高的位 $p$ 满足 $x$ 该位是 $1$ 且 $a_i$ 该位是 $0$，此时答案即为 $x$ 第 $p$ 位及以后的部分减去 $a_i$ 第 $p$ 位及以后的部分。

我们可以把两部分拆开算。对于和 $x$ 相关的部分，我们对每个 $x$ 尝试统计，也就是依次扫描 $x$ 的所有 $1$，那么贡献在某个 $1$ 的情况就是某个 $a_i$ 满足前面的 $1$ 对应的都是 $1$ 且这个 $1$ 对应的是 $0$，这我们可以对 $a_i$ 做一个 FWT 得到这样的数的个数，从而统计贡献。对于和 $a_i$ 相关的部分，也可以类似地用该形式统计贡献，也就是每个 $a_i$ 会贡献给一定要求的 $x$，而这个要求就是 FWT 的形式，然后简单算一些贡献即可。

复杂度 $O((q+V)\log V)$。但不知道为什么要跑 1s。

```cpp
const int N=1200005,U=(1<<20)-1;
int n,m; 
int a[N];
ll b[N],d[N],c[N];

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n >> m;
	rep(i,1,n) cin >> a[i];
	ll sum=0;
	rep(i,1,n)
	{
		d[a[i]]++;
		int bas=0;
		sum+=(1<<20)-a[i];
		per(k,19,0)
		{
			if (a[i]&(1<<k)) 
			{
				a[i]^=(1<<k);
				continue;
			}
			b[bas]+=(1<<k)-a[i];
			bas|=(1<<k);
			b[bas]-=(1<<k)-a[i];
		}
	}
	rep(k,0,19) rep(i,0,U) if (i&(1<<k)) b[i]+=b[i^(1<<k)];
	rep(k,0,19) rep(i,0,U) if (i&(1<<k)) d[i^(1<<k)]+=d[i];
	rep(i,0,U) c[U^i]=b[i];
	rep(i,0,U)
	{
		int bas=0;
		per(k,19,0)
		{
			if (i&(1<<k))
			{
				ll s=d[bas];
				bas|=1<<k;
				s-=d[bas];
				c[i]+=s*(i&((1<<k)-1));
			}
		}
	}
	per(i,U-1,0) chkmin(c[i],c[i+1]);
	while (m--)
	{
		ll k;
		cin >> k;
		if (k>=sum) cout << (k-sum)/n+(1<<20) << endl;
		else 
		{
			int ans=upper_bound(c,c+U+1,k)-c-1;
			cout << ans << endl;
		}
	}
	return 0;
}
```


---

## 作者：happybob (赞：0)

很好想的一个题吧。

二进制有关的问题，考虑从高到低贪心。问题转化为给定 $x$，问使所有数按位与到达 $x$ 的至少操作次数。

考虑每个数 $a_i$ 到达 $x$ 的操作次数。考虑找到高到低第一个二进制位使得 $x$ 这一位是 $1$，而 $a_i$ 这一位是 $0$。然后操作次数应该为 $x$ 和 $a_i$ 在 $i$ 之后的二进制位的值相减。这个东西是容易刻画的。具体来说枚举这个位 $i$，对于 $i$ 左前本质等价于限制了一段前缀，且限制是一个超集状物，对于每一段二进制前缀做一个高维后缀和就对了。复杂度 $O(n \log^2 V)$。


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#include <vector>
#include <array>
using namespace std;

using ll = long long;

const int N = (1 << 20), M = 21;

int n, q;
ll k, sum;
array<array<ll, N>, M> s2;
array<int, N> a;
array<array<int, N>, M> c;

inline ll query(ll x)
{
	int s = 0;
	for (int i = 60; i >= 0; i--)
	{
		ll nv = x & ((1ll << (i + 1)) - 1);
		if (nv ^ x)
		{
			s = i + 1;
			break;
		}
	}
	if (x > (ll)1e6)
	{
		if ((__int128_t)x * n > LLONG_MAX) return LLONG_MAX;
		return 1ll * x * n - sum;
	}
	ll ret = 0ll;
	int S = 0;
	for (int i = 20; i >= 1; i--)
	{
		S |= (1 << i) * ((x >> i) & 1);
		if ((x >> (i - 1)) & 1)
		{
			int nx = x & ((1 << i) - 1);
			int cnt = c[i][S];
			ret = ret + 1ll * nx * cnt - s2[i][S];
		}
	}
	return ret;
}

void fwt(auto& a, int l, int r)
{
	if (l >= r) return;
	int mid = l + r >> 1;
	fwt(a, l, mid);
	fwt(a, mid + 1, r);
	int j = mid + 1;
	for (int i = l; i <= mid; i++) a[i] = a[i] + a[j++];
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> q;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		sum += a[i];
	}
	for (int j = 20; j >= 1; j--)
	{
		for (int i = 1; i <= n; i++)
		{
			if (!((a[i] >> (j - 1)) & 1))
			{
				c[j][(a[i] >> j) << j]++;
				s2[j][(a[i] >> j) << j] += (a[i] & ((1 << j) - 1));
			}
		}
		fwt(c[j], 0, (1 << 20) - 1);
		fwt(s2[j], 0, (1 << 20) - 1);
	}
	while (q--)
	{
		cin >> k;
		ll ans = 0ll;
		for (int i = 60; i >= 0; i--)
		{
			if (query(ans | (1ll << i)) <= k) ans |= (1ll << i);
		}
		cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：xzy090626 (赞：0)

首先延续 D1 的贪心思维，但是这道题要求我们对每一位的决策不能像原来一样 $O(n)$ 解决了。

还是一样从高位到低位贪心地考虑。设当前在考虑第 $x$ 位，也就是说这一位如果取 $1$ 带来的贡献为 $2^x$。那我们要算的就是让每一个数的这一位都变成 $1$ 的代价。假设之前已经选择取过一些更高的位了，那么对于每个数，当前这一位的情况只有两种：
- 之前为了使得某个更高位取到 $1$，将这一位（及更低位）加到了 $0$；
- 对于之前取 $1$ 的高位，这个数在这些高位上均已经为 $1$ 了，也就是说不需要为它们改变这一位（及更低位）；那么这一位显然保持为原来的状态。

对于每种情况，我们分别考虑代价；
- 显然这种情况的代价是固定的，因为我们已经知道这一位为 $0$ 了；假设这样的数有 $m$ 个，那么代价就为 $m\times 2^x$。（因为更低位保持为 $0$ 是我们确定的）
- 这些数显然有 $(n-m)$ 个，但是需要计算这一位原本为 $0$ 的个数。每个数的贡献为 $2^x - a_i \bmod 2^x$。

那么如何计算每种情况的个数呢？

- 对于第一种情况，也就是说，需要确定每个数是不是为了在 $x$ 这一位取到 $1$ 而将低位全部置 $0$ 了。这一步可以先找出这一位为 $0$ 的数的个数来算。
- 对于第二种情况，类似地算贡献。

注意到我们的维护操作是将**在某一位**具有某些特点（为 $0$ 或 $1$）的数之和进行赋值操作。那么我们可以高位前缀和（SOS dp）预处理一下，复杂度是 $O(W\log^2 W)$，$W$ 是值域。每次询问按照这样的贪心策略即可。于是处理询问的复杂度就是 $O(q\log W)$。

---

