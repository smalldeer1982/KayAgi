# Birthday

## 题目描述

Vitaly 送给 Maxim $n$ 个数 $1, 2, \ldots, n$ 作为他 $16$ 岁生日的礼物。Maxim 在庆祝时厌倦了玩桌游，于是决定用这些数字来玩。在每一步操作中，Maxim 可以从手中的数字中选择两个数 $x$ 和 $y$，将它们移除，并加入两个数 $x + y$ 和 $|x - y|$。他希望经过若干步操作后，所有数字都相等，并且这些数字的和最小。

请你帮助 Maxim 找到一种方案。Maxim 的朋友们不想等太久，所以方案中的操作步数不能超过 $20n$。保证在给定的限制下，如果存在可行解，则一定存在一种方案能使所有数字相等、和最小，并且操作步数不超过 $20n$。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
2
3```

### 输出

```
-1
3
1 3
2 2
4 0```

# 题解

## 作者：小粉兔 (赞：11)

在博客园食用更佳：[https://www.cnblogs.com/PinkRabbit/p/CF1637.html](https://www.cnblogs.com/PinkRabbit/p/CF1637.html)。

**【题意简述】**

你拥有 $1, 2, \ldots, n$ 这 $n$ 个整数。

对于每次操作，你可以选择你拥有的两个数 $x, y$，删除这两个数，并加入 $x + y$ 与 $|x - y|$。

你需要在 $20 \cdot n$ 次操作内使这 $n$ 个整数全部相等，并且在此基础上最小化这 $n$ 个整数的和。

如果可以实现目标，你需要构造方案，否则报告之。

**【题解】**

首先写个暴力跑一下 $n = 3, 4, 5, 6, 7, 8, 9, \ldots$ 的情况，可以猜测最后需要将 $n$ 个数全部变为大于等于 $n$ 的最小的 $2$ 的次幂（$n = 2$ 时无解除外）。

这个结论的证明也很简单，考虑任意一个奇素数 $p$，考虑拥有的整数对 $p$ 取模后的值，可以发现每次操作不可能将不同时为 $0$ 的两个整数变为两个 $0$。于是最终所有数都必须变为 $2$ 的次幂，接下来的构造显示了总是可以达到大于等于 $n$ 的最小的 $2$ 的次幂。

首先，如果 $n$ 本身就是 $2$ 的次幂，将 $n$ 减去 $1$，显然与原问题等价。接下来假设 $n$ 不是 $2$ 的次幂，并令 $x = 2^{\lceil \log_2 n \rceil}$ 为大于等于 $n$ 的最小的 $2$ 的次幂。

首先一个很自然的想法是尽量将 $i$ 与 $x - i$ 配对，得到 $x$ 和 $| 2 i - x |$。比如：

- $\{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 \}$ 变为  
  $\{ 1, 2, 3, {\color{red} {2, 4, 6, 8}}, 8, {\color{blue} {16, 16, 16, 16}} \}$。

于是，已得到的 $x$ 不需要处理，而剩下的数分为三个部分：

1. $1, 2, \ldots, x - n - 1$；
2. $2, 4, \ldots, 2 \left( n - \frac{x}{2} \right)$；
3. 一个落单的 $\frac{x}{2}$。

其中第 2 部分可以看作 $1, 2, \ldots, n - \frac{x}{2}$ 全体乘以 $2$，并且最终需要达到 $x / 2$（也被除以了 $2$）。

当 $n$ 足够大时，第 1, 2 部分均至少有一部分的大小 $\ge 3$，可以递归。对于大小 $\le 2$ 的部分，需要和落单的 $\frac{x}{2}$ 一起处理。

在递归后，需要将已得到的整数批量操作到 $x$（因为可能会得到 $x / 2^i$），例如当 $n = 12$ 的时候，递归 $\{ 1, 2, 3 \}$ 得到 $\{ 4, 4, 4 \}$ 后就需要将它们操作到 $16$（具体操作是简单的）。

我们对于 $3 \le n \le 7$ 的部分打表，对于 $n \ge 9$ 的部分，考虑至少进行了一次递归，这意味着最后一步操作必然为选取了 $0$ 和 $x$ 得到两个 $x$，我们可以撤回最后一步操作，并得到一个 $0$，有了 $0$ 就意味着我们可以进行倍增：

- $(0, a) \to (a, a)$；
- $(a, a) \to (0, 2 a)$。

于是我们将可能落单的 $1, 2, 4, \frac{x}{2}$ 都倍增至 $x$，最后补上操作 $(0, x)$ 即可。

代码实现中直接将递归过程定义为生成删去最后一步操作的操作序列，方便讨论。

时间复杂度为 $\mathcal O(n \log n)$，操作次数可以控制在 $\mathcal O(n \log n)$ 级别。

**【AC 代码】**

```cpp
#include <cstdio>
#include <algorithm>
#include <vector>
#include <array>
#include <bit>

#define F(i, a, b) for(int i = a; i <= (b); ++i)

void Solve();

int main() {
	int tests = 1;
	scanf("%d", &tests);
	while (tests--)
		Solve();
	return 0;
}

std::vector<std::array<int, 2>> ans;
inline void add(int x, int y, int k) {
	ans.push_back({x * k, y * k});
}
inline void expp(int n, int x, int k) {
	while (n != x)
		add(0, n, k),
		add(n, n, k),
		n *= 2;
}

std::vector<std::array<int, 2>> pans[8] = {
	{},
	{},
	{},
	{{1, 3}, {2, 2}},
	{{1, 3}, {2, 2}},
	{{1, 2}, {1, 3}, {2, 4}, {2, 6}, {4, 4}, {3, 5}, {0, 2}, {2, 2}, {0, 4}, {4, 4}},
	{{1, 2}, {1, 3}, {2, 4}, {2, 6}, {4, 4}, {3, 5}, {2, 6}, {0, 4}, {4, 4}},
	{{1, 2}, {3, 5}, {2, 6}, {4, 4}, {1, 0}, {1, 3}, {1, 7}, {2, 6}, {4, 4}}
};

void Solve(int n, int x, int k) {
	if (n == x) {
		Solve(n - 1, x, k);
		return ;
	}
	if (n <= x / 2) {
		Solve(n, x / 2, k);
		F(i, 1, n - 1)
			expp(x / 2, x, k);
		return ;
	}
	if (n <= 7) {
		for (auto [a, b] : pans[n])
			add(a, b, k);
		return ;
	}
	F(i, x / 2 + 1, n)
		add(x - i, i, k);
	// [1 ~ x-n-1], x/2,  k
	// [1 ~ n-x/2], x/2, 2k
	int n1 = x - n - 1;
	int n2 = n - x / 2;
	if (n1 >= 3) {
		Solve(n1, x / 2, k);
		F(i, 1, n1 - 1)
			expp(x / 2, x, k);
	}
	if (n2 >= 3) Solve(n2, x / 2, 2 * k);
	expp(x / 2, x, k);
	if (n1 <= 2)
		F(i, 1, n1)
			expp(i, x, k);
	if (n2 <= 2)
		F(i, 1, n2)
			expp(i, x / 2, 2 * k);
	if (n1 >= 3 && n2 >= 3)
		add(0, x, k);
}

int n;

void Solve() {
	scanf("%d", &n);
	if (n == 2)
		return puts("-1"), void();
	int x = std::bit_ceil((unsigned)n);
	if (n <= 7) {
		ans = pans[n];
	} else {
		ans.clear();
		Solve(n, x, 1);
	}
	add(0, x, 1);
	printf("%d\n", (int)ans.size());
	for (auto [a, b] : ans)
		printf("%d %d\n", a, b);
}
```

---

## 作者：Alex_Wei (赞：8)

> CF1637G Birthday

关键性质：最终得到的相同的数不含奇质因子。因为若 $p\nmid x \lor p\nmid y$，则必然 $p\nmid x +y \lor p\nmid |x - y|$。存在 $1$ 不被任何奇质因子整除，得证。

若存在 $0$，我们可以将任意数乘以 $2$：$(0, x)\to (x, x)\to (0, 2x)$，因此考虑先将所有数变为 $2$ 的幂，再通过上述操作全部变为不小于 $n$ 的最小的 $2$ 的幂。考虑递归构造 $\mathrm{solve}(n)$：将 $1\sim n$ 变为 $2$ 的幂。

- 若 $n \leq 2$，则已经满足条件，返回。
- 否则，若 $n$ 是 $2$ 的幂，则递归 $\mathrm{solve}(n - 1)$。
- 否则，设 $p = 2 ^ {\lceil\log_2 n\rceil}$，执行 $(p - 1, p + 1), (p - 2, p + 2),\cdots, (2p - n, n)$。没有被执行的数为 $1\sim 2p - n - 1$ 和 $p$，后者已经是 $2$ 的幂，故执行 $\mathrm{solve}(2p - n - 1)$。上述操作得到了若干 $2p$ 和 $2, 4,\sim 2n - 2p$，前者已经是 $2$ 的幂，故执行 $\mathrm{solve}(n - p)$，再将所有操作的数乘以 $2$。

不难发现 $\mathrm{solve}(n)$ 可以满足我们的要求。接下来，当 $n = 2$ 时，我们无法凑出 $0$，故无解。否则，根据 **鸽笼原理**，必然存在两个 **小于** $n$ 的 $2$ 的幂 $(2 ^ r, 2 ^ r)$。执行 $(2 ^ r, 2 ^ r)$ 即可得到 $0$ 和 $2 ^ {r + 1}$，后者不超过答案。通过不断地利用 $0$ 把每个数乘以 $2$，我们最终得到了一个 $0$ 和 $n - 1$ 个不小于 $n$ 的最小的 $2$ 的幂 $ans$。执行 $(0, ans)$ 即可。

$\mathrm{solve}(n)$ 部分的操作数量不超过 $n\log n$，后半部分操作数量也不超过 $n\log n$。实际表现非常好，可以接受。[代码](https://codeforces.com/contest/1637/submission/146188011)。

构数题优先考虑 $2$ 的幂，通过逆推操作观察性质。

---

## 作者：Purslane (赞：2)

# Solution

首先你要有一个清晰的目标，也就是知道你的构造目标是什么。这个可以通过简单的打表发现最终是最小的 $\ge n$ 的 $2$ 的幂，证明也非常容易，这里不细说了。

设 $2^{k-1} < n \le 2^k$，我们尝试把每个数都变成 $2^k$。设这个过程叫做 $solve(n)$。

当 $n=2^k$，考虑执行 $solve(n-1)$。

否则考虑配对，使得有尽量多的 $x+y$ 恰好等于 $2^k$。

这是啥呢，也就是 $(2^{k-1},n]$ 和 $[2^k-n,2^{k-1})$ 发生了配对。

有一个很头疼的问题，你发现剩下了 $2^{k-1}$，破坏了问题的完整性。

所以我们先把问题弱化为，每个数都变成了 $2$ 的幂。

发现这很能做，可以直接变成 $solve(2^k-n-1)$ 和 $solve(n-2^{k-1})$。

最后你会得到若干 $2$ 的幂。我们先抵消掉相同的数，花费 $n$。然后容易使用 $2 \lceil \log n \rceil$ 次操作将所有数都变成 $0$ 或目标 $2^k$。最后再用 $n$ 次操作全部变为 $2^k$。

而打表计算 $solve$ 的调用次数，得出在本题的数据范围内最多用 $n$ 次。使用数学归纳法容易证明。

因此，我们在至多 $3n+2 \lceil \log n\rceil$ 次操作内解决了本题。在本题的数据范围下上界为 $2.2608n$。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
int T,n;
map<int,int> cnt;
vector<pair<int,int>> ans;
void solve(int n,int mul) {
	if(n<=2) {
		ffor(i,1,n) cnt[i*mul]++;
		return ;
	}
	int k=0;
	while((1<<k)<n) k++;
	if((1<<k)==n) return solve(n-1,mul),cnt[n*mul]++,void();
	cnt[(1<<k-1)*mul]++;
	ffor(i,(1<<k-1)+1,n) ans.push_back({i*mul,((1<<k)-i)*mul}),cnt[(1<<k)*mul]++;
	solve((1<<k)-n-1,mul);
	solve(n-(1<<k-1),mul<<1);
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) {
		cin>>n;
		if(n==2) {cout<<-1<<'\n';continue ;} 
		ans.clear(),cnt.clear(),solve(n,1);
		ffor(i,0,20) if((1<<i)<n) {
			int s=cnt[1<<i];
			ffor(j,1,s/2) ans.push_back({(1<<i),(1<<i)}),cnt[1<<i]-=2,cnt[1<<i+1]++,cnt[0]++;
		}
		ffor(i,0,20) if((1<<i)<n) {
			while(cnt[(1<<i)]>=2) {
				ans.push_back({1<<i,1<<i});
				cnt[(1<<i)]-=2,cnt[0]++,cnt[(1<<i+1)]++;
			}
			if(cnt[1<<i]) {
				ans.push_back({1<<i,0});
				ans.push_back({1<<i,1<<i});
				cnt[(1<<i)]--,cnt[(1<<i+1)]++;
			}
		}
		int K=0;
		while((1<<K)<n) K++;
		ffor(i,1,cnt[0]) ans.push_back({0,(1<<K)});
		cout<<ans.size()<<'\n';
		for(auto pr:ans) cout<<pr.first<<' '<<pr.second<<'\n';
	}
	return 0;
}
```

平心而论这道题是真的简单，只要发现最终的取值就能做完。不过这题也有一个挺有用的思想：我们设计一个“函数”solve，并且弄明白他能干什么事情，这样方便递归处理子问题。

---

## 作者：yllcm (赞：2)

纪念自己过的第一道 *3000。

写个搜索可以发现最小的答案是 $2^{\lceil\log n\rceil}$，另外我们考虑操作 $(x,y)\to (x-y,x+y)\to (2x,2y)$，所以我们可以考虑先把所有的数变成 $2$ 的幂次的形式。

自然可以考虑把问题归到更小的规模。对于 $n$，可以尝试尽可能把数配对成 $2^{\lceil\log n\rceil}$，即对于任意 $2^{\lceil\log n\rceil-1}<x\leq n$，操作 $(x,2^{\lceil\log n\rceil}-x)$。此时我们会剩下一个偶数数列和一个正整数列。只需要把偶数数列全体除以 $2$ 即可得到两个更小的子问题。容易证明它们的规模都是小于 $O(\frac{n}{2})$ 的。

最后考虑如何把这些 $2$ 的幂次转化成同一个数。容易发现如果把指数做差，问题完全等价于对于一个序列 $a$，每次选择序列中的两个元素并把它们同时 $-1$，目标是将 $a$ 全变成 $0$。$\sum _i a_i$ 为偶数的情况是容易处理的。对于奇数的情况，可以造出一个 $0$ 并重复执行 $(0,x)\to (x,x)\to(0,2x)$。最后处理所有 $0$ 即可。

操作复杂度大概是 $O(n\log n)$ 的，不过这玩意神奇地跑到了 $2n\sim 3n$ 级别。

https://codeforces.com/contest/1637/submission/148414304

---

## 作者：Aigony (赞：1)

https://www.cnblogs.com/ying-xue/p/2023jixunluanbu.html

Tags: \*3000, constructive algorithms, greedy, math.

对小数据打表，会发现一个神奇结论：最后这 $n$ 个数都变成了第一个大于等于 $n$ 的 $2$ 的正整数次幂。设这个数为 $k$。

考虑对这个神奇现象作出解释。我们发现，对于除 $2$ 以外的质数 $p$，它是一个奇数。那么如果 $x,y$ 中有一个 $\bmod\ p$ 不为 $0$，怎么操作都不能让它们为 $0$。那么最后的得数也就只能是 $2$ 的幂了。

考虑构造答案。

发现如果序列里有 $0$，倍增一个数的操作是容易构造的：$(0,x)\to (x,x)\to (0,2x)$。也就是说我们只要搞出一个 $0$，且剩下的数都是 $2$ 的幂，就做完了。

首先贪心地将所有 $i$ 和 $k-i$ 配对操作，我们发现序列分成了三部分：
- $1,2,\dots,x$，这一段因为太小而配不上对；
- $2,4,\dots,y$，这一段是所有配对得到的差；
- 一个 $\frac{k}{2}$，因为它也配不上对；
- 若干个 $k$，这是所有配对得到的和。

前两部分都是一个子问题，可以贪心地把它们继续配成若干 $\frac{k}{2}$，再把剩下的配成 $\frac{k}{4}$，以此类推。

具体地，我们维护两个集合 $s,t$：$s$ 表示要配对的集合，$t$ 表示配对失败的集合。

每次从 $s$ 中取出最大的数，检查它能否与集合内凑成 $2^x$ 的形式，能则操作，不能则把它扔进 $t$。每次在 $s$ 中加入操作产生的新数时，检查 $t$ 里面有没有数因为这个新数而变得能配对，有则将该数移回 $s$。

最后处理 $t$ 里剩下的 $0$，操作若干次 $(0,k)$ 即可。

```cpp
const int N=5e4+5;
int T,n,k;
multiset<int> s,t;
typedef pair<int,int> pir;
vector<pir> ans;
il void ins(int x)
{
    if(x==k) return;
    s.insert(x);
    for(int i=1;i<=k;i<<=1) if(t.find(i-x)!=t.end()) 
        s.insert(i-x),t.erase(t.find(i-x));
}
il void opt(int x,int y)
{
    s.erase(s.find(y)); ans.push_back(pir(x,y));
    ins(x+y),ins(abs(x-y));
}
void solve()
{
    n=read();
    if(n==2) {printf("-1\n");return;}
    s.clear(),t.clear(),ans.clear();
    k=1; while(k<n) k<<=1;
    for(int i=1;i<=n;i++) if(i<k) s.insert(i);
    while(!s.empty())
    {
        auto it=prev(s.end());
        int x=*it; s.erase(it); int flag=0;
        for(int i=1;i<=k;i<<=1) if(s.find(i-x)!=s.end()) {opt(x,i-x),flag=1;break;} 
        if(!flag) t.insert(x);
    }
    while(!t.empty()) ans.push_back(pir(k,0)),t.erase(t.find(0));
    printf("%d\n",(int)ans.size());
    for(auto [x,y]:ans) printf("%d %d\n",x,y);
}
int main() {T=read();while(T--) solve(); return 0;}
```

---

## 作者：LingerFeng (赞：1)

### 前言

此篇文章着重于代码实现而非证明，如果需要明白为什么最终答案一定是大于等于 $n$ 的第一个 $2$ 的正整数幂次可以看小粉兔的题解。

那么现在请记住这个结论：最终所有数一定都是大于等于 $n$ 的第一个 $2$ 的正整数幂次。

### 构造

令 $x$ 为大于等于 $n$ 的第一个 $2$ 的正整数幂次。

定义一个 $Merge$ 函数。

```
Dot Merge(int a,int b,int op)
{
	ans.push_back(Dot(a*op,b*op));
	return Dot(abs(a-b),a+b);
}
```

返回值为一对数字，参数为进行操作的 $2$ 个数字和倍数参数 $op$（在后面介绍）。

每次调用这个函数都要把操作过程记录下来，因为最后要输出操作过程。

#### 简单情况

若现在只剩下 $0$ 和 $2$ 的正整数幂次，如何构造使得所有数都变成 $x$？

对于一个 $2$ 的正整数幂次 $a$，先执行操作 $(0,a)$ 可以得到 $(a,a)$，再执行操作 $(a,a)$ 可以得到 $(0,2a)$，即 $a$ 变成了 $2a$。

由于所有数全都是 $2$ 的幂次，所以经过上述操作很多次后所有数依然为 $2$ 的幂次。每个数可以通过不超过 $\log_2 x$ 次操作变成 $x$，所以操作次数不会太多。

最后执行操作 $(0,x)$ 即可将 $0$ 变为 $x$，达到目标。

此部分代码：

```
for(int i=1;i<x;i++)
{
	while(Cnt[i])
	{
		Merge(0,i,1);
		Merge(i,i,1);
		Cnt[i]--;
		Cnt[2*i]++;
	}
}
Merge(x,0,1);
```

其中 $Cnt_i$ 表示 $i$ 有多少个。

#### 普遍情况

考虑将 $1$ 至 $n$ 的所有非 $2$ 正整数幂次的数通过操作变为 $2$ 的正整数幂次。暂时没有通用方案能够 $O(n)$ 构造完成的，考虑**尽可能多**的凑出 $2$ 的正整数幂次。

在考虑构造的时候发现很奇妙的性质是，如果以小于 $n$ 的最大 $2$ 的正整数幂次作为中轴，向外等距离的两个数字操作一次可以产生 $1$ 个 $x$ 和一段从 $2$ 开始的连续的偶数，且剩下的数为从 $1$ 开始的连续自然数。

举例：

```
n=13
{1,2,3,4,5,6,7,8,9,10,11,12,13}
x=16
中轴：8
配对(7,9)(6,10)(5,11)(4,12)(3,13)
得到：
{16,16,16,16,16}
{2,4,6,8,10}
{1,2}
{8}
```

由上可得若按照这样方式分组将会得到 $4$ 组，分别为：

* 全 $x$ 组，有 $n-\frac{x}{2}$ 个 $x$。
* 连续偶数组：为 $1$ 至 $n-\frac{x}{2}$ 的整数同时乘了个 $2$。
* 连续自然数组：从 $1$ 至 $x-n-1$。
* 中轴：$\frac{x}{2}$

发现这个东西可以递归处理。

如何处理连续偶数组？事实上是一样的，不过 $Merge$ 的时候的倍数参数要乘以 $2$。

具体实现需要在递归函数里传一个当前倍数参数就好。

注：

* 递归到 $n\leq2$ 时则已经全是 $2$ 的正整数幂次，则直接返回。

* 递归到 $n$ 为 $2$ 的正整数幂次时不需要考虑 $n$，直接考虑 $n-1$。

具体代码如下：

```
void Solve(int N,int op)
{
	if(N<=2)
	{
		return;
	}
	if((N&(N-1))==0)
	{
		Solve(N-1,op);
		return;
	}
	int Mid=0;
	while((1<<Mid+1)<N)
	Mid++;
	Mid=(1<<Mid);
	for(int i=1;Mid+i<=N;i++)
	{
		Merge(Mid+i,Mid-i,op);
	}
	Solve(2*Mid-N-1,op);
	Solve(N-Mid,op*2);
}
```

执行完 $Solve$ 函数后，模拟一遍 $Merge$ 的过程即可得到简单情况。

再按照简单情况的构造方法处理即可。



---

## 作者：dottle (赞：1)

前置知识：gyh20 的题解。

考虑另一种实现方式，设最终所有数等于 $res$。每一次从不等于 $res$ 的数中找出最大的 $x$ 使得存在 $y+x=2^k$，对 $(x,y)$ 进行操作。

这个做法的正确性与递归做法的相同：

- 对于将 $2^{k}$  变成 $res$ 的过程，显然可以达成。 
- 对于将两个数匹配起来的过程，两个做法的每次找的数是相同的。

考虑具体如何实现：拿一个优先队列维护当前的所有数，每次取出最大的，再枚举 $k$，看 $2^k-x$ 是否存在，若至少存在一个就直接操作；若不存在则将 $x$ 暂时放到一个数组 $del$ 里面，代表它暂时无法操作，每次向优先队列中加入新的数的时候，检查 $del$ 中是否存在能与新数匹配的数，若存在就将其放回优先队列。

```cpp
#include<bits/stdc++.h>
const int N=500005;
using namespace std;

int cnt[N],nd[N],res;
priority_queue<int> q;
vector<pair<int,int>> ans;

void ins(int k){
	q.push(k);
	cnt[k]++;
	for(int i=res;i>=k&&i;i>>=1)
		if(nd[i-k])nd[i-k]--,ins(i-k);
}

void solve(){
	ans.clear();
	int n;cin>>n;
	if(n==2){
		cout<<-1<<endl;
		return ;
	}
	res=1;
	while(res<n)res<<=1;
	for(int i=n;i>=1;i--)
		cnt[i]=1,q.push(i);
	for(int i=n+1;i<=res;i++)
		cnt[i]=0;
	while(q.size()){
		int t=q.top();q.pop();
		if(!cnt[t]||t==res)continue;
		cnt[t]--;
		if(t==0){
			cnt[res]++;
			ans.push_back({0,res});
			continue;
		} 
		int fl=0;
		for(int i=res;i>=t;i>>=1){
			int r=i-t;
			if(cnt[r]){
				cnt[r]--;
				ans.push_back({t,r});
				ins(i),ins(abs(t-r));
				fl=1;
				break;
			} 
		}
		if(!fl)nd[t]++;
	}
	cout<<ans.size()<<endl;
	for(auto x:ans)
		cout<<x.first<<' '<<x.second<<'\n';
}

main(){
	int _T=1;cin>>_T;
	while(_T--)solve();
}

```

---

## 作者：tzc_wk (赞：1)

首先特判 $n=2$ 的情况。

注意到样例给的 $n$ 很小，这意味着当 $n$ 比较大时可能会有一些不错的性质待挖掘，因此考虑先来手玩一下 $n=4$ 的情况。发现不论你怎么选，最终得到的四个数都是 $2$ 的整数次幂，因此我们做出猜想：最终的得到的 $n$ 个数都是 $\ge n$ 且最小的 $2$ 的整数次幂 $N$。

这是为什么呢？可以发现，如果一次操作后，$x,y$ 都包含同一个奇因子，那么操作前这两个数也包含这个奇因子，也就是说，如果最后得到的数不是 $2$ 的幂，那么考虑取出这个数的一个奇因子 $f$，可以得到最一开始的 $n$ 个数都是 $f$ 的倍数，当 $f>1$ 时显然不成立。

接下来考虑构造。我们将此题分成两个部分：先构造出若干个 $2$ 的整数次幂，再将这若干个 $2$ 的整数次幂都变为 $N$。对于前一部分，我们考虑递归函数 `solve(n, k)` 表示将 $2^k,2·2^k,3·2^k,\cdots,n·2^k$ 都变为 $2$ 的整数次幂的过程，如果 $n$ 是 $2$ 的整数次幂那么递归 `solve(n - 1, k)`，否则我们找出 $\le n$ 且最大的 $2$ 的整数次幂 $n_0$，对于 $i\in[1,n-n_0]$，依次将 $(n_0+i)·2^k,(n_0-i)·2^k$ 配对，这样可以得到 $2^{k+1}\sim(n-n_0)·2^{k+1}$，而剩余的数恰好是 $2^k\sim(2n_0-n-1)·2^k$，递归下去即可。

接下来考虑问题的第二部分，由 $n$​ 个 $2$​ 的幂构造出 $n$​ 个 $N$​，考虑从小到大枚举每个 $2$​ 的幂 $2^k$​，如果有超过两个 $2^k$​ 就对它们进行一次操作得到 $2^{k+1}$​ 和 $0$​，否则如果此时序列中有 $0$​，就进行一遍 $2^k$​ 与 $0$​ 得到两个 $2^k$​ 再操作，否则就对 $2^k$​ 与 $2^{k+1}$ 进行一次操作得到 $3·2^k$ 与 $2^k$，再进行一次操作可以得到 $2^{k+1}$ 与 $2^{k+2}$。

题目允许操作次数的上界是 $20n$，但是此算法在实际表现中操作次数大约在 $3n$ 左右，有没有好鸽鸽教教我证一下这个算法操作次数的上界啊/dk

赛时通过代码：

```cpp
#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/hash_policy.hpp>
// #include <ext/pb_ds/priority_queue.hpp>
using namespace std;
// using namespace __gnu_pbds;
#define fi first
#define se second
#define fill0(a) memset(a, 0, sizeof(a))
#define fill1(a) memset(a, -1, sizeof(a))
#define fillbig(a) memset(a, 63, sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define mt make_tuple
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
template <typename T1, typename T2> void chkmin(T1 &x, T2 y){
	if (x > y) x = y;
}
template <typename T1, typename T2> void chkmax(T1 &x, T2 y){
	if (x < y) x = y;
}
typedef pair<int, int> pii;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef long double ld;
#ifdef FASTIO
namespace fastio {
	#define FILE_SIZE 1 << 23
	char rbuf[FILE_SIZE], *p1 = rbuf, *p2 = rbuf, wbuf[FILE_SIZE], *p3 = wbuf;
	inline char getc() {
		return p1 == p2 && (p2 = (p1 = rbuf) + fread(rbuf, 1, FILE_SIZE, stdin), p1 == p2) ? -1: *p1++;
	}
	inline void putc(char x) {(*p3++ = x);}
	template <typename T> void read(T &x) {
		x = 0; char c = getc(); T neg = 0;
		while (!isdigit(c)) neg |= !(c ^ '-'), c = getc();
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getc();
		if (neg) x = (~x) + 1;
	}
	template <typename T> void recursive_print(T x) {
		if (!x) return;
		recursive_print (x / 10);
		putc (x % 10 ^ 48);
	}
	template <typename T> void print(T x) {
		if (!x) putc('0');
		if (x < 0) putc('-'), x = -x;
		recursive_print(x);
	}
	template <typename T> void print(T x,char c) {print(x); putc(c);}
	void readstr(char *s) {
		char c = getc();
		while (c <= 32 || c >= 127) c = getc();
		while (c > 32 && c < 127) s[0] = c, s++, c = getc();
		(*s) = 0;
	}
	void printstr(string s) {
		for (int i = 0; i < s.size(); i++) putc(s[i]);
	}
	void printstr(char *s) {
		int len = strlen(s);
		for (int i = 0; i < len; i++) putc(s[i]);
	}
	void print_final() {fwrite(wbuf, 1, p3 - wbuf, stdout);}
}
using namespace fastio;
#endif
int lg[65538], cnt[19];
vector<pii> res;
void work(int n, int coef) {
	if (!n) return;
	if (n == 1) return cnt[lg[coef]]++, void();
	int N = 1, cur = 0; while ((N << 1) <= n) N <<= 1, cur++;
	if (N == n) return cnt[lg[N * coef]]++, work(n - 1, coef), void();
	cnt[lg[N * coef]]++;
	for (int i = N + 1; i <= n; i++) {
		res.pb(mp(i * coef, (N - (i - N)) * coef));
		cnt[lg[N * 2 * coef]]++;
	}
	work(n - N, coef * 2); work(N - (n - N) - 1, coef);
}
int main() {
	for (int i = 1; i <= 16; i++) lg[1 << i] = i;
	int qu; scanf("%d", &qu);
	while (qu--) {
		int n; scanf("%d", &n); res.clear();
		if (n == 2) {puts("-1"); continue;}
		fill0(cnt); work(n, 1); int cnt0 = 0;
		int lg = 1;
		while ((1 << lg) < n) ++lg; --lg;
//		printf("! %d\n", res.size());
//		for (int j = 0; j <= lg + 1; j++) printf("%d ", cnt[j]); printf("\n");
		for (int j = 0; j <= lg - 1; j++) {
			while (cnt[j] >= 2) {
				cnt0++; cnt[j + 1]++; res.pb(mp(1 << j, 1 << j));
				cnt[j] -= 2;
			}
			if (cnt[j]) {
				res.pb(mp(1 << j, 1 << j + 1));
				res.pb(mp((1 << j), (1 << j + 1) + (1 << j)));
				cnt[j]--; cnt[j + 2]++;
			}
		}
		while (cnt[lg] >= 2) {
			res.pb(mp(1 << lg, 1 << lg));
			cnt[lg] -= 2; cnt0++; cnt[lg + 1]++;
		}
		if (cnt[lg]) {
			res.pb(mp(1 << lg, 0));
			res.pb(mp(1 << lg, 1 << lg));
			cnt[lg] = 0;
		}
		for (int i = 1; i <= cnt0; i++) res.pb(mp(1 << lg + 1, 0));
		printf("%d\n", res.size());
		for (pii p : res) printf("%d %d\n", p.fi, p.se);
	}
	return 0;
}
```

---

## 作者：EnofTaiPeople (赞：0)

发现构造题最优化特别不好做，数据范围不太像 dp 最优解，所以直接打表找规律，发现那个最小整数就是 $2^{\lceil\log_2n\rceil}$。

我们希望将所有数字都变成 $2^k$ 就好了，因为只需要和 $0$ 操作两次就能翻倍。

思考再三，发现最好使用一类递归构造的形式，具体地，我们对一个大小为 $m$ 的数字集合 $G(m,k)=\{x2^k,x=1,\cdots,m\}$，显然初始阶段为 $G(n,0)$。

考虑操作集合 $S(m,k)$，设 $P=2^{\lfloor\log_2m\rfloor}$，考虑将 $(P-i)2^k,(P+i)2^k$ 的数字进行操作，会得到许多 $P2^{k+1}$（合法数字），以及集合 $S(m-P,k+1),S(2P-m-1,k)$，然后递归下去，这里的复杂度是 $O(n)$ 的，因为每一次操作都有新的数字成为合法数字。

然后找出一个重复出现的 $2^k$，选出两个操作，得出 $0$，使用 $0$ 把其他数字全部变成 $2^{\lceil\log_2n\rceil}$，再将自己变成 $2^{\lceil\log_2n\rceil}$，只需要任选一个数操作一次即可。

这里的操作次数也是 $O(n)$ 的，因为初始的数字就已经足够大了，实际上对于 $10^5$ 以内的 $n$，操作次数最多为 $3.82n$，可以通过。

---

## 作者：yxzy4615 (赞：0)

## 题意

你有 $1,2,3\dots n$ 这 $n$ 个整数。

定义一次操作为：将其中两个数 $x,y$ 变成 $x+y,|x-y|$ 。

你需要在 $20n$ 次操作内将所有数变为相等的数。

若有，则输出操作数与方案，否则输出 $-1$。

数据范围： $2 \le n,\sum n \le 5 \times 10^4$

## 题解

首先，这个“相等的数”是什么？

很多题解也说过了，这里不再赘述。
 
记 $x=2^{\left\lceil\log_2n\right\rceil}$，这个就是我们要找的数。

然后将 $1,2,3\dots n$ 分成四部分。

第一部分：
$(n,x-n),(n-1,x-n+1)\dots(\frac{x}{2}+1,\frac{x}{2}-1)$

对这一部分操作后：

$(2n-x,x),(2n-x-2,x-n-1)\dots(2,x)$

将剩下的不为 $x$ 的数提出来，得到第二部分：

$2(n-\frac{x}{2}),2(n-1-\frac{x}{2})\dots 4,2$

这一部分等同于 $1,2,3\dots n-\frac{x}{2}$ 全部变为 $\frac{x}{2}$。这是一个子问题，可以直接处理。

接下来将原序列剩下的数取出来，分成第三部分和第四部分：

第三部分： $1,2\dots x-n-1$ 变为 $x$。这一部分也是一个子问题。

剩下一个孤单的 $\frac{x}{2}$ 变为 $x$，这个单独处理即可。

于是我们就得到了一种构造方案。

这里给出构造的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
void write(int x){
	if(x>=10) write(x/10);
	putchar(48+x%10);
}
vector<pair<int,int> >ans,s[10]={{},{},{},
	{{1, 3}, {2, 2}},
	{{1, 3}, {2, 2}},
	{{1, 2}, {1, 3}, {2, 4}, {2, 6}, {4, 4}, {3, 5}, {0, 2}, {2, 2}, {0, 4}, {4, 4}},
	{{1, 2}, {1, 3}, {2, 4}, {2, 6}, {4, 4}, {3, 5}, {2, 6}, {0, 4}, {4, 4}},
	{{1, 2}, {3, 5}, {2, 6}, {4, 4}, {1, 0}, {1, 3}, {1, 7}, {2, 6}, {4, 4}}
};
void dfs(int x,int p,int pw){
    if(x==p) return dfs(x-1,p,pw);//处理2^k
    if(x<=p/2){
	dfs(x,p/2,pw);p>>=1;
	for(int i=1;i<=x-1;i++){
	    ans.push_back(make_pair(0,p*pw));
	    ans.push_back(make_pair(p*pw,p*pw));
	}
	return;
    }//降次
    if(x<=2) return ;
    if(x<=7){
    for(int i=0;i<(int)s[x].size();i++)
    	ans.push_back(make_pair(s[x][i].first*pw,s[x][i].second*pw));
	return ;
    }
    for(int i=p/2+1;i<=x;i++) ans.push_back(make_pair((p-i)*pw,i*pw));
    int nl=p-x-1,nr=x-p/2;
    if(nl>=3){
	dfs(nl,p/2,pw);p>>=1;
	for(int i=1;i<=nl-1;i++){
	    ans.push_back(make_pair(0,p*pw));
	    ans.push_back(make_pair(p*pw,p*pw));
	}
	p<<=1;
    }
    if(nr>=3) dfs(nr,p/2,pw*2);
    p>>=1;
    ans.push_back(make_pair(0,p*pw));
    ans.push_back(make_pair(p*pw,p*pw));
    p<<=1;
    if(nl<=2&&nl){
	for(int i=1;i<p;i*=2){
	    ans.push_back(make_pair(0,i*pw));
	    ans.push_back(make_pair(i*pw,i*pw));
	}
	if(nl==2){
	    for(int i=2;i<p;i*=2){
		ans.push_back(make_pair(0,i*pw));
		ans.push_back(make_pair(i*pw,i*pw));
	    }
	}
    }
    if(nr<=2&&nr){
	p>>=1;pw<<=1;
	for(int i=1;i<p;i*=2){
	    ans.push_back(make_pair(0,i*pw));
	    ans.push_back(make_pair(i*pw,i*pw));
	}
	if(nr==2){
	    for(int i=2;i<p;i*=2){
		ans.push_back(make_pair(0,i*pw));
		ans.push_back(make_pair(i*pw,i*pw));
	    }
	}
	p<<=1;
    }
    if(nl>=3&&nr>=3) ans.push_back(make_pair(0,pw*p));
}
int n,t;
int main(){
    scanf("%d",&t);
    while(t--){
	scanf("%d",&n);
	if(n==2){
	    puts("-1");
	    continue;
	}
	int x=1;
	while(x<n) x<<=1;
	if(n>7) dfs(n,x,1);
	else ans=s[n];
	ans.push_back(make_pair(0,x));
	printf("%d\n",(int)ans.size());
	for(int i=0;i<(int)ans.size();i++)
	    write(ans[i].first),putchar(' '),write(ans[i].second),putchar('\n');
	ans.clear();
    }
    return 0;
}
```

**但是！！！** 这种方案的上限步数是什么？？？

当我们将数据范围内的所有解跑出来，发现步数在 $7n$ 以内。

于是，根据写法的递归形式，我写了一个 $\text{dp}$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e8;
int g[N+10];//g[i]表示i对应的x=2^ceil(log2(i))
long long f[N+10];//表示步数减一，便于维护
inline long long dp(int x,int y){
    return 2ll*(y-g[x])*(x-(x>2))+f[x];//前面用于降次
}
int main(){
    for(int i=1,t=0;i<=N;i++){
        if(i>(1<<t)) t++;
        g[i]=t; 
    }
    f[1]=0;f[2]=f[3]=f[4]=2,f[5]=10,f[6]=f[7]=9;
    for(int i=8,j,nl,nr;i<=N;i++){
        j=g[i];
        if((1<<j)==i){
            f[i]=f[i-1];
            continue;
        }
        nl=(1<<j)-i-1,nr=i-(1<<(j-1));
        f[i]=2+nr+dp(nl,j)+dp(nr,j-1)+(nl>=3&&nr>=3);
    }
    double ans=0;
    for(int i=3;i<=N;i++) ans=max(ans,(f[i]+1.0)/i);
    cout<<ans<<endl;
    return 0;
}
```
结果发现，这玩意在 $1 \times 10^8$ 时还是不到 $7n$。~~这是什么鬼？？~~

我们考虑对于一个 $x$，求出其不包含迭代步数的比值。根据geogebra得出在 $2.6$ 以下，且在 $\min(nl,nr)$ 较小时，比值大致较小，差不多在 $1.5$ 或 $2$ 左右。

也就是说，若 $nl,nr$ 答案近似于 $k_ln,k_rn$，可以推出，平均 $f(x)\approx  \dfrac{k_l}{2}+\dfrac{k_r}{4}+2$，（因为在中间差不多是边上的两倍，$nl\approx x,nr\approx \frac{x}{2}$）当这个值最大时，其权值和近似于$7$。

所以操作上限为 $7n$ 左右。

### 鸣谢
感谢小粉兔大佬的思路，本文解法基于其题解分析。

---

## 作者：gyh20 (赞：0)

首先，题目需要我们剩下的数值全相同且最小，我们先考虑这个值是什么。

考虑逆变换，将最终剩的两个数 $x,y$ 变为 $\dfrac{x+y}{2}$ 和 $\dfrac{x-y}2$，可以发现，若 $x,y$ 都是奇质数 $p$ 的倍数，那么变化后的两个数都是 $p$ 的倍数，不可能最终还原为 $1\sim n$。

令 $k$ 为最小的满足 $2^k\geq n$ 的整数，我们可以通过构造说明最终一定可以取到所有数 $=2^k$。

考虑将过程分成两部分，先将所有数变成 $2^a$ 的形式，再造出一个 $0$，之后倍增（进行操作 $(0,x)$ 然后进行 $(x,x)$ 可以得到 $(0,2x)$。

前一部分可以考虑一个递归的方法，令 $F(n)$ 表示构造 $1\sim n$ 这 $n$ 个数使得全部变成 $2^a$。

那么我们先找到最大的 $k$ 满足 $2^k<n$ ，再将 $[2^k+1,n]$ 之间的数其关于 $2^k$ 对称的位置做操作。

于是剩余两部分，其中一部分是一个前缀，另一部分是一个 $2,4,6,8\dots$ 形态的，也可以看成一个前缀，（$2$ 的次幂乘 $2$ 依然是 $2$ 的次幂）。于是整个就可以递归下去了。

造 $0$ 可以直接用两个相同的数造，容易发现 $n>3$ 时这样的数必定存在。

递归的总操作次数是 $n$ 次（每次操作会减少一个非 $2^n$），后一半倍增显然不超过 $n\log n$，实际操作远低于 $20n$。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
const int M=998244353;
inline void add(re int &x,re int y){(x+=y)>=M?x-=M:x;}
inline int Mod(re int x){return x>=M?x-M:x;}
inline int ksm(re int x,re int y){
	re int s=1;
	while(y){
		if(y&1)s=1ll*s*x%M;
		x=1ll*x*x%M,y>>=1;
	}
	return s;
}
int t,n,a[1000002],ans,num[100002],nn[100002];
char s[1000002];
vector<int>ansa,ansb;
inline void Do(re int x,re int y){
	assert(nn[x]),--nn[x];
	assert(nn[y]),--nn[y];
	++nn[x+y],++nn[abs(x-y)];
	ansa.push_back(x),ansb.push_back(y);
}
inline void solve(vector<int>A){
	if(!A.size())return;
	if(A.size()==1){
		++num[A[0]];
		return;
	}
	if(A.size()==2){
		++num[A[0]],++num[A[1]];
		return;
	}
	re int pos;
	for(re int i=A.size()-1;~i;--i)if((A[i]&(-A[i]))==A[i]){pos=i;break;}
	if(pos==A.size()-1){
		++num[A[pos]];
		A.pop_back(),solve(A);
		return;
	}
	vector<int>B;++num[A[pos]];
	for(re int i=A.size()-1;i>pos;--i)Do(A[i],A[pos-(i-pos)]),B.push_back(A[i]-A[pos-(i-pos)]),++num[A[pos]<<1];
	reverse(B.begin(),B.end());
	solve(B);
	re int xx=A.size();
	for(re int i=0;i<(xx-1-pos)*2;++i)A.pop_back();A.pop_back();
	solve(A);
}
inline void Out(){
	printf("%u\n",ansa.size());
	for(re int i=0;i<ansa.size();++i)printf("%d %d\n",ansa[i],ansb[i]);
	ansa.clear(),ansb.clear();
}
int main(){
	t=read();
	while(t--){
		n=read();
		if(n==2){
			puts("-1");
			continue;
		}
		vector<int>A;
		for(re int i=1;i<=n;++i)A.push_back(i),num[i]=0;
		re int m=1;
		while(m<n)m<<=1;
		fill(num,num+m+1,0);
		for(re int i=0;i<=m;++i)nn[i]=0;
		for(re int i=1;i<=n;++i)nn[i]=1;
		solve(A);
		for(re int i=1;i<=m;++i)if(num[i])assert(nn[i]==num[i]);
		for(re int i=1;i<m;++i)
			if(num[i]>1){
				Do(i,i),num[i]-=2,++num[0],++num[i<<1];
				break;
			}
		for(re int i=1;i<m;++i)
			for(re int j=1;j<=num[i];++j){
				re int x=i;
				while(x!=m)Do(0,x),Do(x,x),x<<=1;
			}
			Do(0,m);
		Out();
	}
}


```


---

