# チーム分け

## 题目描述

[problemUrl]: https://atcoder.jp/contests/mujin-pc-2018/tasks/mujin_pc_2018_f

$ N $ 人を、それぞれの人がただ $ 1 $ つのチームに属するようにチーム分けを行います。

しかし、人によっては多くの人が属するチームに属したくないと考えています。

この条件は $ N $ 要素からなる整数列 $ a $ で表され、$ i $ 番目の人は $ a_{i} $ 人以下から成るチームに配属されることになります。

チーム分けをするに当たってこのようなチーム分けは何通り考えられるのかを計算したくなりました。答えは非常に大きくなることがあるので、$ 998244353 $ で割ったあまりを出力してください。ただし、$ 2 $ つのチーム分けが異なるとは、ある $ 2 $ 人が存在して、片方のチーム分けでは同じチームに属するがもう片方のチーム分けでは違うチームに属する、という場合を表します。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 1000 $
- $ 1\ \leq\ a_i\ \leq\ N $
- 入力は全て整数である

### Sample Explanation 1

$ 1 $ 人をチーム分けする方法は $ 1 $ 通りです。

### Sample Explanation 2

条件を満たすチーム分けは、$ ((1),(2),(3)),\ ((1,2),(3)),\ ((1,3),(2)),\ ((2,3),(1)) $ の $ 4 $ 通りです。

## 样例 #1

### 输入

```
1
1```

### 输出

```
1```

## 样例 #2

### 输入

```
3
3 3 2```

### 输出

```
4```

## 样例 #3

### 输入

```
10
3 1 4 1 5 9 2 6 3 10```

### 输出

```
1869```

# 题解

## 作者：L0vely_NaiL0ng (赞：1)

educational 的题。

对 $a$ 从大到小排序，对于每个组在 $a$ 最小即限制最严格的那个地方确定整个组，设 $f_{i, j}$ 表示考虑前 $i$ 个人，还有 $j$ 个人没有分配组的方案，转移要枚举 $k \in [1, a_i]$ 表示 $i$ 所在的组的人数，$O(n^3)$。

进一步优化，倒着枚举 $i$，在 $i$ 时确定所有大小为 $i$ 的组，设 $f_{i, j}$ 表示考虑完大小 $\ge i$ 的组，还有 $j$ 个人没有分配组的方案，转移要枚举大小为 $i$ 的组有几组，这样就是 $O(n^2 \log n)$ 了。

#### 收获

**延迟计算的思想。**

$O(n^3)$

```
	cin >> n;
	For (i, 1, n) cin >> a[i];
	sort(a + 1, a + n + 1, [&](int x, int y) {
		return x > y;
	});
	For (i, 0, n) {
		c[i][0] = 1;
		For (j, 1, i) {
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
		}
	}
	f[0][0] = 1;
	For (i, 1, n) {
		For (j, 0, i) {
			f[i][j] = f[i - 1][j - 1];
			For (k, 1, min(n + 1 - j, a[i])) (f[i][j] += f[i - 1][j + (k - 1)] * c[j + k - 1][k - 1]) %= mod;
		}
	}
	cout << f[n][0];
```

$O(n^2 \log n)$。

```
	cin >> n; fac[0] = ifac[0] = 1;
	f[n + 1][0] = 1;
	For (i, 1, n) fac[i] = fac[i - 1] * i % mod, ifac[i] = ksm(fac[i], mod - 2, mod) % mod;
	For (i, 1, n) {
		int x; cin >> x; cnt[x] ++;
	}
	rep (i, n + 1, 2) {
		For (j, 0, n) {
			if (!f[i][j]) continue;
			(f[i - 1][j + cnt[i - 1]] += f[i][j]) %= mod;
			int x = j + cnt[i - 1], y = i - 1;
			for (int k = y, v = ifac[y]; k <= x; k += y, v = v * ifac[y] % mod) (f[i - 1][x - k] += f[i][j] * fac[x] % mod * ifac[x - k] % mod * ifac[k / y] % mod * v % mod) %= mod;
		}
	}
	cout << f[1][0];
```

---

## 作者：lalaouye (赞：1)

水一发题解吧。

注意到在一个组中考虑限制的话只用关心最小的 $a_i$ 就行了，那么我们考虑对 $a$ 排个序，从后往前 dp，设 $f_{i,j}$ 表示考虑到第 $i$ 个人且前面有 $j$ 个人没有匹配，转移是简单的：

$$f_{i-1,j+1}\leftarrow f_{i,j}$$

$$f_{i-1,j-k}\leftarrow f_{i,j}\times \binom{j}{k}[k\le a_i]$$

然后注意到 $\mathcal{O}(n^3)$ 也是能过的，就不用继续优化了。

---

## 作者：VainSylphid (赞：1)

非常巧妙的一道计数题。

## 题意

将 $N$ 个人分配到恰好一支队伍中，要求第 $i$ 个人被分到的队伍大小不超过 $a_i$。求分配方案对 $998244353$ 取模的结果。两个分配方案被认为是不一样的，当且仅当存在两个人，在一个分配方案中被分在同一支队伍，而在另一个分配方案中被分在不同队伍。

## 思路

发现对于一个限制为 $a_i$ 的人，如果他没有加入一个人数为 $a_i$ 的队伍，就和限制为 $a_i-1$ 的人没有任何区别，所以我们考虑按队伍人数从大到小确定。

对于大小为 $s$ 的队伍，成员的限制 $a_i$ 都必须大于等于 $s$。而对于大小为 $s - 1$ 的队伍，除了原来限制就等于 $s-1$ 的人，还多了一些没有加入大小为 $s$ 的队伍且限制大于等于 $s$ 的人。方案数和有多少大小为 $s$ 的队伍，以及限制大于等于 $s$ 而且没有加入人数比 $s$ 更大的队伍的人数有关。

记 $f_{i,j}$ 等于已经组好了所有大小大于等于 $i$ 的队伍，且还有 $j$ 个限制大于等于 $i$ 的人的方案数。记 $cnt_i$ 等于限制为 $i$ 的人数。

考虑枚举大小为 $i$ 的队伍的个数被动转移。设当前枚举到大小为 $i$ 的队伍有 $k$ 个，则方案数为 $\displaystyle\frac{\prod_{l=1}^{k}{\tbinom{j-(l-1)\times i}{i}f_{i-1,j-l\times i+cnt_{i-1}}}}{k!}$。注意，由于队伍是无序的，需要除以 $k$ 个队伍的全排列 $k!$。

上面的式子可以通过预处理阶乘和阶乘逆元 $O(1)$ 计算组合数和前缀和优化，对于每个 $f_{i,j}$ 可以做到 $O(\frac{j}{i})$ 计算，所以总时间复杂度是 $O(n^2\log n)$ 的。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod = 998244353;
ll n,x,a[1005],fac[1005],dv[1005],dp[1005][1005];
ll ksm(ll a,ll b,ll p)
{
	ll ret = 1;a %= p;
	while(b)
	{
		if(b & 1)
		    ret = ret * a % p;
		a = a * a % p,b >>= 1;
	}
	return ret;
}
void init()
{
	fac[0] = dv[0] = 1;
	for(ll i = 1;i <= 1001;i++)
	    fac[i] = fac[i - 1] * i % mod;
	dv[1001] = ksm(fac[1001],mod - 2,mod);
	for(ll i = 1000;i > 0;i--)
	    dv[i] = dv[i + 1] * (i + 1) % mod;
}
ll C(ll a,ll b)
{
	if(a < b)
	    return 0;
	return fac[a] * dv[b] % mod * dv[a - b] % mod;
}
ll solve(ll cur,ll val)
{
	if(cur == 1)
	    return 1;
	if(dp[cur][val])
	    return dp[cur][val];
	ll cnt = 1;
	for(ll i = 0;i * cur <= val;i++)
	{
		dp[cur][val] = (dp[cur][val] + solve(cur - 1,val - i * cur + a[cur - 1]) * cnt % mod * dv[i] % mod) % mod;
		cnt = cnt * C(val - i * cur,cur) % mod;
	}
	return dp[cur][val];
}
int main()
{
	scanf("%lld",&n),init();
	for(ll i = 1;i <= n;i++)
	    scanf("%lld",&x),a[x]++;
	printf("%lld",solve(n,a[n]));
    return 0;
}
```

---

