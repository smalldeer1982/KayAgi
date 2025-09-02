# [USACO18FEB] Cow Gymnasts P

## 题目描述

厌倦了农场生活的奶牛们卖掉了所有的财产，加入了一个巡回马戏团。到目前为止，奶牛们被分配了一些简单的表演：杂耍火炬、走钢丝、骑独轮车——没有什么是一头灵巧的奶牛无法应付的。然而，马戏团团长希望为他们的下一场演出创造一个更加戏剧性的表演。

新表演的舞台布局包括 $N$ 个平台，排列成一个圆圈。在每个平台上，必须有 $1$ 到 $N$ 头奶牛堆叠成一摞，奶牛一头叠在另一头上面。当团长发出信号时，所有的堆叠必须同时顺时针倒下，使得堆叠底部的奶牛不动，她上面的奶牛移动一个平台顺时针，再上面的奶牛移动两个平台顺时针，依此类推。作为技艺高超的体操运动员，奶牛们知道她们在技术方面不会有任何问题。各个奶牛堆叠在倒下时不会相互“干扰”，因此每头奶牛都会落在目标平台上。所有落在平台上的奶牛会形成一个新的堆叠，这个堆叠不会倒下。

团长认为，如果堆叠倒下后，每个平台上的新堆叠包含的奶牛数量与原始堆叠相同，那么这个表演将特别戏剧化。我们称满足这一条件的堆叠大小为“魔法”配置。请帮助奶牛们计算魔法配置的数量。由于这个数字可能非常大，请计算其对 $10^9 + 7$ 取模的结果。

如果两个配置在任何平台上分配的奶牛数量不同，则认为它们是不同的配置。

## 说明/提示

对于 $N = 4$，有效的配置是 $(1,1,1,1)$、$(2,2,2,2)$、$(3,3,3,3)$、$(4,4,4,4)$、$(2,3,2,3)$ 和 $(3,2,3,2)$。

题目来源：Dhruv Rohatgi

## 样例 #1

### 输入

```
4```

### 输出

```
6```

# 题解

## 作者：Tsawke (赞：6)

# [LG-P4270 [USACO18FEB]Cow Gymnasts P](https://www.luogu.com.cn/problem/P4270)  Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.monkey-hyx.tech?t=LG-P4270-Solution)

前面的几个性质的思路参考自 [这篇Blog](https://www.luogu.com.cn/blog/hazard-echo/solution-p4270)，主要是对一些我觉得难以理解的地方重写一下，以及对最后结论及实现进行**更详细的证明**。

### 题面

存在 $ n $ 个平台环形排列，每个平台可以放置 $ [1, n] $ 头奶牛，每次操作时，对于第 $ i $ 层的奶牛，会顺时针移动 $ i - 1 $ 个平台并落下，求有多少种排列能使无论多少次操作每个平台的奶牛数都不改变。

$ 1 \le n \le 10^{12} $。

对于样例，有 $ (1, 1, 1, 1), (2, 2, 2, 2), (3, 3, 3, 3), (4, 4, 4, 4), (2, 3, 2, 3), (3, 2, 3, 2) $。

### Solution

一道纯粹的人类智慧题。。。

然后我们这里定义的循环周期并不是一般圆周运动绕一圈的操作次数，而是一头原来在第 $ i $ 层且最高为 $ \xi $ 层的牛再次到第 $ i $ 层且最高为 $ \xi $ 层所需要的旋转次数。也就是对于一个合法的排列，两个同一高度平台之间的距离即为平台内所有牛的循环周期。

首先对于**符合条件的排列**，有好几个奇怪的性质：

1. 对于第 $ i $ 层的奶牛，只能是从其他平台第 $ i $ 层的奶牛平移过来，而不可以是从更高层的奶牛掉下来。

证明：因为是符合条件的排列，我们假设序列中最高的层数为 $ m $，那么一定是前面的 $ m - 1 $ 个平台各自给这个平台贡献一头奶牛，因为如果有往前数第 $ m $ 个的贡献，那么那个平台至少要有 $ m + 1 $ 头奶牛，矛盾。如果在前 $ m - 1 $ 里有至少任意一个没有贡献，那么当前这个台子奶牛就会少至少一个，也矛盾，所以简单想一下刚才的过程，前面第一个贡献当前的第 $ 2 $ 层，第二个贡献第 $ 3 $ 层，$ \cdots $，第 $ m - 1 $ 个贡献当前的第 $ m $ 层，而第 $ m - 1 $ 个能移动 $ m - 1 $ 那么其长度也就必须至少为 $ m $，然后以此类推即可证明所有层数都是由对应层数平移过来的，得证。

2. 对于第 $ i $ 层奶牛的循环周期（定义参考伊始）是 $ i $ 的约数。

证明：显然某一时刻第 $ i $ 层的某头奶牛一定是这层的周期为 $ T_i $ 的奶牛移动 $ k $ 次到达的，即 $ i = kT_i $，得证。

3. 第 $ i - 1 $ 层奶牛循环周期是第 $ i $ 层奶牛循环周期的约数。

证明：考虑由性质一，第 $ i $ 层的奶牛一定还会到第 $ i $ 层，而到达的位置的第 $ i $ 层已经跑了，所以一定是有 $ i - 1 $ 层的奶牛一直垫着它走的，否则便会掉到小于 $ i $ 的位置了，所以下层的周期一定是上层的约数，即 $ T_{i - 1} \mid T_i $，得证。

4. 任意两个平台之间的奶牛数量差不超过 $ 1 $。

证明：由性质二不难得出 $ T_i \mid i, T_{i + 1} \mid i + 1 $，由性质三不难得出 $ T_{i} \mid T_{i + 1} $，又 $ \gcd(i, i + 1) = 1 $，那么显然 $ \gcd(T_i, T_{i + 1}) = 1 $，两数互质，前者又是后者的约数，所以显然前者为 $ 1 $，所以 $ T_1 = T_2 = \cdots = T_{n - 1} = 1 $。所以对于某个层数最高为 $ i $ 的，每次位移的距离是 $ i - 1 $，周期又为 $ 1 $，那么每隔 $ i - 1 $ 个就是相同的层数，这东西不难想到就是任意两者之间差不超过 $ 1 $.

以此我们便可以得出结论：
$$
ans = 2 - n + \sum_{i = 1}^{n - 1}2^{\gcd(n, i)}
$$
证明：首先枚举层数最小的平台有 $ i $ 层，不难想到对于最小平台有 $ i $ 层时，循环周期一定是 $ i $ 的约数，且一共有 $ n $ 个平台，那么循环周期也一定为 $ n $ 的约数，以此不难想到，此时**最大的**循环周期为 $ \gcd(n, i) $，此时我们举个 $ n = 6, i = 3, \gcd = 3 $ 的例子：

![Oops! The image is blocked! Please visit my own website to observe the image! 图片被墙了，请通过文章头的跳转链接访问！](http://monkey-hyx.tech/Images/Blog/2022_11_09_1.png)

此时根据我们前面的性质一定有标号相同的点值相同，那么此时 $ 2^{\gcd(n, i)} $ 就代表着枚举 $ A, B, C $ 是否为 $ i $，但是此时如果三个值均非 $ i $ 的话，最小值便不能保证为 $ i $，此时还需要对此次的贡献 $ -1 $。

然后此时我们还要考虑，为什么仅枚举是否为 $ i $ 就可以不重不漏了，考虑如钦定 $ A = i $ 时，且钦定 $ B $ 不为 $ i $，则 $ B $ 一定为 $ i + 1 $ 或 $ i - 1 $，后者则最小值会变化，不合法，所以如果不是 $ i $ 那么一定是 $ i + 1 $。所以此时如果还钦定 $ C $ 不是 $ i $，那么它要么是 $ i + 1 $ 要么是 $ i + 2 $，而 $ C $ 与下一个 $ A $ 相连，$ i + 2 $ 和 $ i $ 的差大于 $ 1 $ 了，也不合法。当然我们考虑 $ i + 2 = 5 $，由性质二，发现 $ 3 \nmid 5 $，也不合法，所以仍然为 $ i + 1 $。那么对于这个例子，显然一个数要么是 $ i $ 要么不是，不是的时候数也唯一确定，故可以如此枚举。

随便举几个例子可以发现这个结论似乎正确，那么我们现在尝试严谨一点地去证明，有结论，对于所有非 $ i $ 的点的值一定均为 $ i + 1 $。

首先考虑如果有非 $ i $ 的点，那么一定至少要有一个 $ i + 1 $，这个从我们之前的证明即可得出，因为差最大为 $ 1 $，又不可以是 $ i - 1 $。此时如果后面的值是 $ i + 2 $，那么显然此时 $ T_{i + 1} \ge 2 $，并且此时因为存在 $ i + 2 $，那么最大值一定不是 $ i + 1 $，所以从性质四的证明过程可以得到 $ T_{i + 1} = 1 $，显然矛盾。而如果所有非 $ i $ 均为 $ i + 1 $，那么 $ i + 1 $ 即为最大值，观察性质发现有且仅有最大值是可以不符合恒等于 $ 1 $ 的条件的，所以这样才是合法的。故得证。

所以换一个说法理解，我们枚举的便为此处是 $ i $ 还是 $ i + 1 $，且不能均为 $ i + 1 $，此时贡献为 $ 2^{\gcd(n, i)} - 1 $，考虑如果 $ i = n $，那么不存在 $ i + 1 $ 了，此时需要特判，不难想到最小为 $ n $ 最大为 $ n $ 那么全是 $ n $ 则为唯一的方案，如此最终答案便为：
$$
\begin{aligned}
ans
	&=\sum_{i = 1}^{n - 1}(2^{\gcd(n, i)} - 1) + 1 \\
	&=2 - n + \sum_{i = 1}^{n - 1}2^{\gcd(n, i)} \\
	&=2 - n - 2^n + \sum_{i = 1}^{n}2^{\gcd(n, i)}
\end{aligned}
$$
然后发现数据范围这个柿子肯定过不去，于是考虑优化，继续推柿子：
$$
\begin{aligned}
\sum_{i = 1}^{n}2^{\gcd(n, i)}
	&= \sum_{j = 1}^n 2^j \sum_{i = 1}^{n}[\gcd(n, i) = j] \\
	&= \sum_{j = 1}^n 2^j \sum_{i = 1}^{n}[j \mid i \land j \mid n \land \gcd(\dfrac{n}{j}, \dfrac{i}{j}) = 1] \\
	&= \sum_{j = 1}^n (2^j \times \varphi(\dfrac{n}{j}) \times [j \mid n]) \\
	&= \sum_{j \mid n} (2^j \times \varphi(\dfrac{n}{j})) \\
	&= \sum_{j \mid n} (2^{\frac{n}{j}} \times \varphi(j))
\end{aligned}
$$

这个式子应该是可以继续推下去直到严格 $ O(\sqrt{n}\log n) $ 的，但是没必要，到目前这个形式就已经可以通过精细实现打倒这个复杂度了。我们发现如果无脑枚举，找因数是 $ O(\sqrt{n}) $ 的，每个因数求欧拉函数也是 $ O(\sqrt{n}) $ 的，最后会退化成 $ O(n) $，线性筛之类的更不行了，如果可以的话或许 Min25筛 之类的科技可以 $ O(n^{\frac{2}{3}}) $ 实现，刚好能过，不过 duck 不必。

显然我们可以通过分解质因数求欧拉函数，具体地，令 $ p_i $ 为质数且 $ c_i \neq 0 $，如果有：
$$
n = \prod_{i = 1}^k p_i^{c^i}
$$
那么：
$$
\varphi(n) = n \times \prod_{i = 1}^k \dfrac{p_i - 1}{p_i}
$$
然后我们答案式子枚举的是 $ n $ 的因子，显然可以通过枚举其所有质因子不重不漏地凑出来所有的因子，于是写个朴素搜索，暴力枚举每个因子有多少个，以及当前的乘积，和存在的质因子的乘积等等，如此便可以 $ O(1) $ 求出每个需要的欧拉函数，复杂度为因数个数，即 $ O(\sqrt{n}) $，然后剩下的 $ \log $ 复杂度是因为求 $ 2^j $ 的时候快速幂的复杂度，理论上用左移会更优，但是可能爆 `long long`。然后过程中是需要先让 $ n \div \prod p_i $ 然后再乘 $ \prod p_i - 1 $，否则会爆 `long long`，当然像我一样直接用 `__int128_t` 可以直接忽略这些问题。

至此此题解决，还是很精妙的。

### Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/extc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;
using namespace __gnu_pbds;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

#define MOD (ll)(1e9 + 7)

template< typename T = int >
inline T read(void);

ll N;
int tot(0);
pair < ll, int > fact[1100000];
int cur[1100000];
__int128_t ans(0);

__int128_t qpow(ll a, ll b){
    __int128_t ret(1), mul(a);
    while(b){
        if(b & 1)ret = ret * mul % MOD;
        b >>= 1;
        mul = mul * mul % MOD;
    }return ret;
}

void dfs(int p = 1, ll base = 1, __int128_t phi = 1, __int128_t div = 1){
    if(p > tot){
        phi *= base, phi /= div, phi %= MOD;
        ans = (ans + phi * qpow(2, N / base) % MOD) % MOD;
        return;
    }
    dfs(p + 1, base, phi, div);
    phi *= fact[p].first - 1;
    div *= fact[p].first;
    for(int i = 1; i <= fact[p].second; ++i)
        base *= fact[p].first, dfs(p + 1, base, phi, div);
}

int main(){
    N = read < ll >();
    ll tmp(N); ll cur(2), cnt(0);
    while(tmp > 1){
        if(cur * cur > tmp)break;
        while(tmp % cur == 0)tmp /= cur, ++cnt;
        if(cnt)fact[++tot] = {cur, cnt}, cnt = 0;
        ++cur;
    }if(tmp > 1)fact[++tot] = {tmp, 1};
    dfs();
    ans = ((((ans + 2 - N) % MOD) - qpow(2, N)) % MOD + MOD) % MOD;
    printf("%lld\n", (ll)ans);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    short flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2022_11_09 初稿

---

## 作者：hhhhhhazard (赞：6)

#      _想要却不可得，你奈人生何_  

这题考场写炸.zip，瞎搞出答案？？？然后精度爆炸...参考了一下[题解](https://blog.csdn.net/qq_42101694/article/details/95073581)
#### **预备知识：** φ(x) = **$x\frac{(p1-1)(p2-1)...(pi-1)}{p1p2..pi}$** 
**题意：** 给定 $n$ 个平台，每个平台可以放置 $1...n$ 个奶牛，对于层数为 $i$ 的奶牛，每次会顺时针移动 **（i-1）** 个单位到其他平台。然后落下，问有多少种排列方式，使得不管怎么移动，每个平台的奶牛数都不变

#### 结论一：对于每个层数的奶牛，只能从其他平台相同层数的奶牛平移过来，不能从层数较高的奶牛落下得到。

**证明：** 假设平台中层数最高为$M$，每次移动时，在这个平台前面$M-1$个的平台，每个都会贡献一头奶牛，如果存在落下的情况的话，那么在前面第$M$个的平台有存在落下的情况，那么这个平台的层数就会大于$M$，所以我们可以得到最高层的奶牛是从其他相同层数的奶牛平移过来。并且最高层的奶牛不会小落，因为这样会导致这个平台的奶牛层数就不是最高的了，所以最高层的奶牛对下面几层的奶牛无影响。依次类推，可以得到结论。

#### 结论二：第i层的奶牛的循环周期是i的约数

**证明：** 依题意，每层的奶牛都是循环的，对于某个平台层数为$i$的奶牛，肯定是从一个周期为$T$的奶牛移动$k$次得到（等价于$i=kT$）结论得证

#### 结论三：第$i-1$层的奶牛的循环周期是第$i$层奶牛循环周期的约数
**证明：** 对于一个平台第$i$层的奶牛，显然奶牛不能飞，不能悬空，所以下面一定要有一头奶牛垫着。然后**感性理解**一下... _~~滑稽~~_ 

#### 结论四：任意两个平台上的奶牛数量之差不超过一
**证明：** 对于两个相邻层的奶牛，周期分别为$T_{i}$和$T_{i+1}$(i为层数)，由结论二、三可得，$T_{i}$为$i$的约数，$T_{i+1}$为$i+1$的约数，$gcd(i,i+1)=1$，所以$gcd(T_{i},T_{i+1})=1$，又因为$T_{i}$为$T_{i+1}$的约数。所以我们可以得到$T_{i}=1$，所以除了最高的一层，周期都为$1$

#### 结论五： $ans = 2-n + \sum_{m=1}^{n-1}\ 2^{gcd(m,n)}$
**证明**：这里的$m$意为最矮的台子有$m$只奶牛（$m∈[1,n-1]$），层数为$m-1$，由结论一二可得，循环周期为$n$和$m$的约数，所以最大的循环周期为 **gcd（n, m)** ，同时可以找到 **gcd（n, m)** 组，每组可以取或不取，共有 $2^{gcd(m,n)}$种情况，但是不能全部取，这个时候不满足最矮的有$m$头牛。当$m=n$时全部不取，此时方案数为$1$。所以我们可以得到一个式子  $ans = 1+ \sum_{m=1}^{n-1}\ (2^{gcd(m,n)}-1)$化简一下就是我们结论五

#### 优化
我们可以观察一下$n<=10^{12}$所以直接暴力肯定会超的，于是我们就考虑一下优化，可以参考一下[Longge的问题](https://www.cnblogs.com/PinkRabbit/p/8278728.html)，里面的题解可以参考一下~~科学养锁~~，我们假设一下**gcd（n, m） = n/g** ，我们的**洗个马**就可以化简成$ \sum_{g|n}^{n}\ (2^{n/g}*φ(g))$然后**搜一搜**~~wjh的搜索天下第一~~就可以卡过去了，然后精度方面，在最后的答案因为**n**是有可能比我们的模数大的，所以我们要
```cpp
	ans = (ans + 2 - N) % mod;
	if (ans < 0)
		ans += mod;
```
而不是
```cpp
	ans = (ans + 2 - N + mod) % mod;
```
然后你就考崩了...下面是代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const ll mod = 1e9 + 7;
ll ans, N, n;
vector <ll> q;
vector <int> cnt;

inline ll ksm(ll a, ll p) {
	ll rt = 1;
	while (p) {
		if (p&1)
			rt = rt  * a % mod;
		a =  a * a % mod;
		p>>=1;
	}
	return rt;
}

void dfs(int num, ll g, ll m1, ll m2) {
	if (num == q.size()) {
		if (g == 1)
			return;
		ans+=ksm(2,N/g)*(g/m2%mod*m1%mod)%mod;
		ans%=mod;
		return;
	}
	dfs(num+1, g, m1, m2);
	m1 = m1 * (q[num] - 1) % mod;
	m2 = m2 * q[num];
	for (int i = 1; i <= cnt[num]; i++) {
		g = g * q[num];
		dfs(num+1, g, m1, m2);
	}
}

int main() {
	cin >> N;
	n = N;
	for (ll i = 2; i * i <= n; i++)
		if (n % i == 0) {
			int tot = 0;
			q.push_back(i);
			while (n % i==0) {
				n /= i;
				tot++;
			}
			cnt.push_back(tot);
		}
	if (n > 1) {
		q.push_back(n);
		cnt.push_back(1);
	}
	dfs(0, 1, 1, 1);
	ans = (ans + 2 - N) % mod;
	if (ans < 0)
		ans += mod;
	cout << ans;
	return 0;
}
```


---

## 作者：DengDuck (赞：2)

第一篇题解有些地方讲得不是很好，我根据其参考的原文重新写一篇吧。

这题比较巧妙的思考方式是分层考虑，我们考虑每一行独立分析。

首先我们定义移动 $i$ 个平台的那一层叫第 $i$ 层，也就是从下往上第 $i+1$ 只。

为啥呢？因为每一行都是独立的，我们考虑最高的平台，要是转换之后不变，那么其高度不变，为了让奶牛落在这个位置，前面必然也有一个最高的平台来给其贡献（不可能更高，我们前面假设了）。其他的层数情况类似。

进一步地，我们发现每一层应该都是循环节，由于第 $i$ 层会移动 $i$ 个平台，所以最大循环层应该是 $\gcd(i,n)$。

考虑层与层之间的关系，显然第 $i-1$ 层为了”托起“第 $i$ 层，所以其循环节必然是第 $i$ 层循环节的约数。

我们发现循环节是 $i$ 的约数，考虑下面一层 $i-1$，显然 $\gcd(i-1,i)=1$，所以第 $i-1$ 层循环节为 $1$，进一步地，除了最高层，其他层都是满的。

因此我们枚举最高层即可，对于每种最高层 $m$，循环节内显然有 $2^{\gcd(m,n)}-1$ 种方案，也就是咋选都行了，但是不能都选，不然这种情况已经被认为是 $m+1$ 层不选，而 $m$ 层不能这么认为，所以整体答案要加一。
$$
1+\sum_{i=1}^{n-1}(2^{\gcd(i,n)}-1)
$$
你可以化简一下：
$$
2-n+\sum_{i=1}^{n-1}2^{\gcd(i,n)}
$$
右边的式子可以利用欧拉函数计算，这个技巧比较经典，不多赘述。
$$
\sum_{i|n}2^{\dfrac n i}\varphi(i)
$$
考虑枚举因数，在这个过程中会枚举到每一种质因子，可将欧拉函数一并算出。

我们可以计算一下时间复杂度，枚举因数的时间复杂度大概是 $\mathcal O(\sqrt n\log n)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL mod=998244353;
const LL N=1e6+5;
LL n,ans,cnt[N][2],tot;
LL ksm(LL x,LL y)
{
	LL ans=1;
	while(y)
	{
		if(y&1)ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans;
}
void dfs(LL x,LL t,LL phi)
{
	if(x>tot)
	{
		if(t==n)return;
		ans=(ans+ksm(2,t)*phi%mod)%mod;
		return;
	}
	dfs(x+1,t,phi);
	phi*=(cnt[x][0]-1);
	for(int i=1;i<=cnt[x][1];i++)
	{
		t/=cnt[x][0];
		dfs(x+1,t,phi);
		phi*=cnt[x][0];
	}
}
int main()
{
	scanf("%lld",&n);
	LL t=n;
	for(LL i=2;i*i<=t;i++)
	{
		if(t%i==0)
		{
			LL b=0;
			while(t%i==0)
			{
				t/=i;
				b++;
			}
			cnt[++tot][0]=i,cnt[tot][1]=b;			
		}

	}
	if(t!=1)
	{
		cnt[++tot][0]=t,cnt[tot][1]=1;
	}
	dfs(1,n,1);
	ans=(ans-n+2)%mod;
	ans=(ans%mod+mod)%mod;
	printf("%lld",ans);
}
```



---

## 作者：ddwqwq (赞：2)

我太菜了，不会做，于是从网上找到一篇[题解](https://blog.csdn.net/icefox_zhx/article/details/79440365)。但是这篇题解中的结论没有证明，我在这里给它补上证明。  
  
首先说明接下来使用的符号。$(x,y)$表示$x$和$y$的最大公约数，$x$%$y$表示$x$除$y$的最小非负余数。令$a_{i},i\in\left [1,N  \right ]$表示第$i$堆牛的数量。  
  
首先放出两个结论：  
结论1：对任意$i,j\in\left [1,N  \right ]$,$|a_i-a_j|\leqslant1$  
结论2：令$m$表示$a_i$中的最小值，则对任意$i,j$满足$i\equiv j(mod\: (m,N)))$，$a_i=a_j$  
  
结论1的证明：  
设$M$为$a_i$中的最大值，已知$M\in[1,N]$。$p$为任意整数使得$a_p=M$。令$t_i= (p-i)$%$N+1$，那么$$a_{t_i}> i,i\in[1,M-1]$$。显然，对于任意$j$满足$j\equiv p(mod M-1),a_j=M$。  
由$a_{t_i}> i,i\in[1,M-1]$推知，对于任意$j\in[1,M-m]$,$a_{t_j}\geqslant M-j$。所以$a$的第$(p-M-1)$%$N+1$项大于等于$M-1$。又推出$a_{t_2}$大于等于$M-1$。到了这里，很显然可以用数学归纳法对$t$进行归纳，推出，对于任意$i\in[1,N]$,$a_i\geqslant M-1$，即$m\geqslant M-1$。所以结论1成立。  
~~LATEX太难弄了，所以把证明补充完整就留作习题。。~~  
  
有了结论1，再证明结论2就十分容易了。显然，只要证明结论2适用于任意$i$使得$a_i=M$即可。设$a_i=M$。  
此前已经证明$$a_i=a_{(i+km)\%N}=M$$，$k$是一个变量。$$km\: mod \: N$$等价于$$ (m,N)\frac{km}{(m,N)}\: mod\: N$$因为$(\frac{m}{(m,N)},N)=1$，所以上式等价于$$ k(m,N)\: mod\: N$$(k和$\frac{km}{(m,N)}$都遍历$N$的完全剩余系)。这就证明了$a_{i+k(m,N)}=M$对任意$k$成立，也就证明了结论2。  
就这样吧，接下来的做法可以参考我在开头给出的链接。

---

## 作者：封禁用户 (赞：1)

#### 思路

我们考虑 $n$ 个台子上的牛最少的一个台子上有 $m$ 只，记这个台子为 $i$，则对于所有 $j \equiv i\pmod j \equiv i\pmod g$，$g=\gcd(N,m)g=\gcd(N,m)$，台子 $j$ 上的牛也必为 $m$ 只。其余台子上的牛最多 $m+1$ 只，且具有周期性，即以 $g$ 为周期。

因此对于最少的牛数为 $m(m < n)$ 的情况，我们一共有 $2 ^  {\gcd(N,m)} -1$ 种方案。当 $m=n$ 时，只有 $1$ 种方案。

### Code


```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define inf 0x3f3f3f3f
#define N 100010
#define mod 1000000007
inline ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return x*f;
}
ll n,ans=0;
vector<ll>p;
vector<int>e;
inline int ksm(int base,ll k){
    int res=1;
    for(;k;k>>=1,base=(ll)base*base%mod)
        if(k&1) res=(ll)res*base%mod;return res;
}
void dfs(int cnt,ll g,ll mul1,ll mul2){//mul1--(pi-1)*(pj-1) mul2--(pi)*(pj)
    if(cnt==p.size()){
        if(g==1) return;
        ans+=(ll)ksm(2,n/g)*(g/mul2%mod*mul1%mod)%mod;ans%=mod;return;
    }dfs(cnt+1,g,mul1,mul2);mul1=mul1*(p[cnt]-1)%mod;mul2*=p[cnt];
    for(int i=1;i<=e[cnt];++i)
        g*=p[cnt],dfs(cnt+1,g,mul1,mul2);
}
int main(){
    n=read();ll x=n;
    for(int i=2;(ll)i*i<=n;++i){
        if(x%i) continue;p.push_back(i);int tot=0;
        while(x%i==0) x/=i,tot++;
        e.push_back(tot);
    }if(x>1) p.push_back(x),e.push_back(1);
    dfs(0,1,1,1);
    ans=(ans+1-(n-1))%mod;if(ans<0) ans+=mod;
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：i207M (赞：1)

这道题...说难不难，说简单，也很难想到。

假设我们填的数字的最小值是m，那么我们最多有$\gcd(n,m)$个轨道可以独立选择，原因是：

设$a[i]=m$，那么$a[i-m]=m$一定成立（这里的数组下标是循环的），否则，考虑$a[i-m]$的第m+1头牛，他会移动到i。

通过类似的分析，我们可以得到，在每个轨道，只能填m或m+1。

以i-1为例，若i-1的数字$>m+1$，那么他就会贡献到$a[i+m]$，这样就会影响$a[i]$，所以不可能。对于$j\in[i-g+1,i-1]$的情况同理。

```cpp
LL p[100]; int c[100],cntp;
LL d[100000]; int cntd;
unordered_map<LL,int>phi;
void dfs(int x,LL n,LL ph)
{
	if(x>cntp)
	{
		d[++cntd]=n;
		phi[n]=ph%md;
		return;
	}
	dfs(x+1,n,ph);
	dfs(x+1,n*=p[x],ph*=p[x]-1);
	for(ri i=2; i<=c[x]; ++i) dfs(x+1,n*=p[x],ph*=p[x]);
}
void divi(LL x)
{
	for(ri i=2; (LL)i*i<=x; ++i)
		if(x%i==0)
		{
			p[++cntp]=i;
			while(x%i==0) ++c[cntp],x/=i;
		}
	if(x>1) p[++cntp]=x,c[cntp]=1;
	dfs(1,1,1);
}
LL n;
signed main()
{
#ifdef M207
	freopen("in.in","r",stdin);
	// freopen("ot.out","w",stdout);
#endif
	in(n);
	divi(n);
	int ans=0;
	for(ri i=1; i<=cntd; ++i) inc(ans,mul(qpow(2,d[i]%(md-1)),phi[n/d[i]]));
	ans=add(ans,2,md-qpow(2,n%(md-1)),md-n%md);
	out(ans);
	return 0;
}
```


---

## 作者：MiniLong (赞：0)

##### P4270

[题目链接](https://www.luogu.com.cn/problem/P4270)

观察到每层是独立的（即每层的不会在操作后跑到其他层），所以肯定是成循环结构。由于第 $i$ 层的会往前跑 $i$ 步，所以循环节大小应该是 $\gcd(i,n)$ 的因数。并且，第 $i-1$  层的循环节肯定是第 $i$ 层循环节的因数（因为每次有第 $i$ 层的时候第 $i-1$ 层必须有）。所以有 $d_{i-1} | d_i,d_i|i,d_{i-1} |i-1,d_i,d_{i-1}|n$。又因为 $\gcd(i,i-1)=1,d_i|i,d_{i-1}|i-1$。所以 $d_{i-1}=1$（所以符合要求的序列最多只有两种数 $(m-1),m$）。令最高层为 $m$，那么枚举 $m$，这时循环节为 $\gcd(m,n)$ 的因数，也就是说，这 $\gcd(m,n)$ 随便怎么放，那么有 $2^{\gcd(m,n)}$ 种选择，去掉全部放 $m$ 的，答案就是 $1+\sum\limits_{i=1}^{n-1}(2^{\gcd(i,n)}-1)=-n+2+\sum\limits_{i=1}^{n-1}2^{\gcd(i,n)}=-n+2-2^n + \sum\limits_{d|n}2^d \varphi(\dfrac{n}{d})$。设 $d = \prod {p_i}^{e_i}$，则 $ans = -n+2-2^n + \sum\limits_{d | n} 2^{\frac{n}{d}} (d\prod \dfrac{p_{i}-1}{p_i})$。复杂度 $\Theta(\sqrt{n} \log{n})$。

---

