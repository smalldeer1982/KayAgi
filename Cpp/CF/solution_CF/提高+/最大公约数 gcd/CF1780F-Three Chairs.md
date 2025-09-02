# Three Chairs

## 题目描述

One day Kira found $ n $ friends from Morioh and decided to gather them around a table to have a peaceful conversation. The height of friend $ i $ is equal to $ a_i $ . It so happened that the height of each of the friends is unique.

Unfortunately, there were only $ 3 $ chairs in Kira's house, and obviously, it will not be possible to seat all friends! So, Kira has to invite only $ 3 $ of his friends.

But everything is not so simple! If the heights of the lowest and the tallest of the invited friends are not coprime, then the friends will play tricks on each other, which will greatly anger Kira.

Kira became interested, how many ways are there to choose $ 3 $ of his friends so that they don't play tricks? Two ways are considered different if there is a friend invited in one way, but not in the other.

Formally, if Kira invites friends $ i $ , $ j $ , and $ k $ , then the following should be true: $ \gcd(\min(a_i, a_j, a_k), \max(a_i, a_j, a_k)) = 1 $ , where $ \gcd(x, y) $ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of the numbers $ x $ and $ y $ .

Kira is not very strong in computer science, so he asks you to count the number of ways to invide friends.

## 说明/提示

In the first example, only one way is suitable: invite friends $ 1 $ , $ 2 $ , and $ 3 $ . Here $ 1 < 2 < 3 $ , and the numbers $ 1 $ and $ 3 $ are coprime.

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
1```

## 样例 #2

### 输入

```
4
1 6 2 3```

### 输出

```
3```

## 样例 #3

### 输入

```
4
16 4 8 2```

### 输出

```
0```

## 样例 #4

### 输入

```
10
10 1 6 7 9 8 4 3 5 2```

### 输出

```
77```

# 题解

## 作者：Fido_Puppy (赞：11)

这里是一篇比较离谱的暴力题解。

题目传送门：[Three Chairs](https://www.luogu.com.cn/problem/CF1780F)

我们首先把 $a$ 数组从小到大排序，然后问题就变成了求三元组 $(i, j, k)$（$i < j < k$，$\gcd(a_i, a_k) = 1$） 的个数。

考虑枚举 $j$，然后每次就是求有多少对二元组 $(i, j)$ 满足 $i < j$，$k > j$，$\gcd(a_i, a_k) = 1$。

可以考虑每次把 $j$ 往右移一位，考虑对数 $now$ 会发生什么变化。

如果我们设 $pre_i$ 表示第 $i$ 个数之前与 $a_i$ 互质的数的个数，$suc_i$ 表示第 $i$ 个数之后与 $a_i$ 互质的数的个数。

明显每次从 $j - 1$ 变成 $j$，$now$ 就要加上 $suc_{j - 1} - pre_j$。

然后问题就变成了如何求 $pre_i$ 和 $suc_i$，这里以 $pre_i$ 为例，$suc_i$ 同理。

我们可以考虑直接容斥，由于 $a_i \le 3 \times 10 ^ 5$，而 $2 \times 3 \times 5 \times 7 \times 11 \times 13 \times 17 > 3 \times 10 ^ 5$，所以 $a_i$ 的不同的质因子个数最多只有 $6$ 个。

所以我们开一个桶 $cnt$，$cnt(x)$ 表示当前多少数能够被 $x$ 整除，假设 $a_i = p_1 ^ {k_1} \times p_2 ^ {k_2} \times \cdots \times p_m ^ {k_m}$。

设 $S = \{p_1, p_2, \cdots, p_m\}$

$$pre_i = \sum_{T \subseteq S} (-1)^{|T|} \times cnt(\prod_{x \in T} x)$$

然后实现好一点就可以过了，时间复杂度 $\Theta(n \sqrt n + 2 ^ 6 \times n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
int n, a[300005];
int cnt[300005], pre[300005], suc[300005], mul[ 1 << 6 ];
int main() {
	#ifndef ONLINE_JUDGE
	freopen("code.in", "r", stdin);
	#endif
	ios :: sync_with_stdio(0), cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	sort(a + 1, a + n + 1);
	memset(cnt, 0, sizeof(cnt));
	for (int i = 1; i <= n; ++i) {
		int now = a[i];
		vector <int> fac;
		for (int j = 2; j * j <= now; ++j) {
			if (now % j == 0) {
				fac.push_back(j);
				while (now % j == 0) now /= j;
			}
		}
		if (now > 1) fac.push_back(now);
		int m = fac.size(), ans = cnt[1];
		mul[0] = 1, ++cnt[1];
		for (int s = 1; s < 1 << m; ++s) {
			int t = __builtin_ctz(s), b = __builtin_popcount(s);
			mul[s] = mul[ s ^ 1 << t ] * fac[t];
			if (b & 1) ans -= cnt[ mul[s] ];
			else ans += cnt[ mul[s] ];
			++cnt[ mul[s] ];
		}
		pre[i] = ans; 
	}
	memset(cnt, 0, sizeof(cnt));
	for (int i = n; i; --i) {
		int now = a[i];
		vector <int> fac;
		for (int j = 2; j * j <= now; ++j) {
			if (now % j == 0) {
				fac.push_back(j);
				while (now % j == 0) now /= j;
			}
		}
		if (now > 1) fac.push_back(now);
		int m = fac.size(), ans = cnt[1];
		mul[0] = 1, ++cnt[1];
		for (int s = 1; s < 1 << m; ++s) {
			int t = __builtin_ctz(s), b = __builtin_popcount(s);
			mul[s] = mul[ s ^ 1 << t ] * fac[t];
			if (b & 1) ans -= cnt[ mul[s] ];
			else ans += cnt[ mul[s] ];
			++cnt[ mul[s] ];
		}
		suc[i] = ans; 
	}
	i64 ans = 0, now = 0;
	for (int i = 2; i < n; ++i) {
		now += suc[ i - 1 ] - pre[i];
		ans += now;
	}
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：王熙文 (赞：5)

这篇题解提供一个不需要莫比乌斯反演的调和级数复杂度的解法。

## 思路

首先对于这种问题，有一个经典套路，是设 $dp_i$ 表示 $\gcd=i$ 时的个数，转移方式是倒序枚举，先求出来 $i | \gcd$ 时的答案，之后减去 $\sum_{j=2} dp_{ij}$。这样就可以把问题转化成了求 $i| \gcd$ 时的方案数。

这样的好处是，一旦 $i | \max$ 且 $i|\min$，那么这个三元组便满足。

假设确定了 $\max$ 和 $\min$，求个前缀和 $cnt_i$，则中间的那个数的选择方案有 $cnt_{\max-1}-cnt_{\min}$。

因此把所有 $i | a_j$ 的所有 $a_j$ 提出来，排序，设新组成的数组为 $b_1,b_2,\cdots,b_m$，则现在要求的是：

$$\sum_{i=1}^m \sum_{j=i+1}^m cnt_{b_j-1}-cnt_{b_i}$$

这个式子可以通过计算贡献变成：

$$\sum_{i=1}^m cnt_{b_i-1}\cdot (i-1) + cnt_{b_i}\cdot (m-i)$$

这样就可以在 $\mathcal O\left(\dfrac{W}{i}\right)$（其中 $W$ 是 $a$ 的值域）的时间求出 $dp_i$，总的复杂度为调和级数。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n; int a[300010];
bool vis[300010];
int cnt[300010];
int tot,b[300010];
int dp[300010];
signed main()
{
	cin>>n;
	for(int i=1; i<=n; ++i) cin>>a[i],vis[a[i]]=1,cnt[a[i]]=1;
	for(int i=1; i<=3e5; ++i) cnt[i]+=cnt[i-1];
	for(int i=3e5; i>=1; --i)
	{
		int sum=0; tot=0;
		for(int j=i; j<=3e5; j+=i)
		{
			if(vis[j]) b[++tot]=j;
		}
		for(int j=1; j<=tot; ++j) sum+=cnt[b[j]-1]*(j-1)-cnt[b[j]]*(tot-j);
		dp[i]=sum;
		for(int j=i*2; j<=3e5; j+=i) dp[i]-=dp[j];
	}
	cout<<dp[1];
	return 0;
}
```

---

## 作者：hejianxing (赞：3)

[题目(cf)](https://codeforces.com/problemset/problem/1780/F)

[题目(luogu)](https://www.luogu.com.cn/problem/CF1780F)

第一篇过审的题解！

# 题目大意
给定长度为 $n(3\le n\le 3\times 10^5)$ 的数组 $a(1\le a_i\le 3\times 10^5)$，其中的元素互不相同。问有多少三元组满足最大数与最小数互质。两个三元组不同当且仅当存在数 $x$ 出现在三元组 $A$ 中而不出现在三元组 $B$ 中。

# 题解
容易发现数组 $a$ 的顺序对答案没有影响。为了方便统计答案，我们人为地给它安排顺序，也就是对 $a$ 数组排序。

显然，当确定了三元组中最大值和最小值后，中间值可以随意选，只需要满足它位于最大最小值之间。也就是说，当最大值为 $a_i$ 而最小值为 $a_j$（显然 $j<i$）时，中间值有 $i-j-1$ 种取值。

易得

$$ans=\sum\limits_{gcd(a_i,a_j)=1,j<i}(i-j-1)$$

对于每个 $i$ 考虑其贡献，有

$$
ans=\sum\limits_{i=1}^{n}\sum\limits_{gcd(a_i,a_j)}(i - j - 1)
$$

$$
=\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{i-1}(i - j - 1)[gcd(a_i, a_j)=1]
$$

以下是莫反技巧推导。

$$
ans=\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{i-1}(i - j - 1)[gcd(a_i, a_j)=1]
$$

$$=\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{i-1}(i - j - 1)\sum\limits_{k|gcd(a_i, a_j)}\mu(k)
$$

考虑将 $\mu$ 提到最前面，变换枚举对象，枚举 $d=gcd(a_i,a_j)$。

$$
ans=\sum\limits_{d=1}^{a_n}\mu(d)\sum\limits_{d|a_i}\sum\limits_{d|a_j,j<i}(i-j-1)
$$

考虑分离 $i$ 和 $j$.

$$
ans=\sum\limits_{d=1}^{a_n}\mu(d)\sum\limits_{d|a_i}\left(\sum\limits_{d|a_j,j<i}(i-1)-\sum\limits_{d|a_j,j<i}j\right)
$$

整理出容易解决的式子：

$$
ans=\sum\limits_{d=1}^{a_n}\mu(d)\sum\limits_{d|a_i}\left((i-1)\sum\limits_{j=1}^{i-1}[d|a_j]-\sum\limits_{d|a_j,j<i}j\right)
$$

$\mu(d)$ 可以欧拉筛线性预处理。

对于 $d$ 和 $a_i$，可以直接枚举，时间复杂度为 $O(n+\dfrac n 2+\dfrac n 3+\cdots+\dfrac n n)=O(n\times (1+\dfrac 1 2+\dfrac 1 3+\cdots+\dfrac n n))=O(n\ln n)$.

关于 $j$ 的项，可以在枚举 $i$ 的过程中累加统计，因为 $j$ 必定小于 $i$，也就是说之前其实已经遍历过 $j$ 了。具体见代码。

总的时间复杂度是 $O(n\ln n)$.

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 300005;
int n, a[N], mu[N], pri[N], cnt = 0, vis[N], b[N];
LL ans = 0;
void init() {
    mu[1] = 1;
    for (int i = 2; i < N; i++) {
        if (!vis[i]) pri[++cnt] = i, mu[i] = -1;
        for (int j = 1; j <= cnt && i * pri[j] < N; j++) {
            vis[i * pri[j]] = 1;
            if (i % pri[j] == 0) break;
            mu[i * pri[j]] = -mu[i];
        }
    }
}
int main() {
    init();//莫比乌斯函数线性筛
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) b[a[i]] = i;//b[i]表示值为i的元素在数组中出现的位置
    for (int d = 1; d <= a[n]; d++) {//枚举d
        LL sum = 0, s1 = 0, s2 = 0;//sum统计后面的一大串式子，s1统计前i-1个数有多少出现在数组中且整除d，s2统计出现在数组中且整除d的元素的位置（下标）和
        for (int i = d; i <= a[n]; i += d)//枚举值，值在数组中的位置是b[i]
            if (b[i])//数组中有i这个数
                sum += 1ll * (b[i] - 1) * s1 - s2, s1++, s2 += b[i];//维护
        ans += sum * mu[d];
    }
    printf("%lld", ans);
    return 0;
}
```

# END


---

## 作者：vicky2048_2 (赞：2)

## $\text{Part 0. Description}$

给定长度为 $n$ 的正整数序列 $a$，序列元素互不相同，问有多少个由序列 $a$ 的元素组成的三元组 $(a_i,a_j,a_k)$ 满足该条件：

- 三个元素的最大值与三个元素的最小值互质。

## $\text{Part 1. Analysis}$

### $\text{Part 1.0 暴力}$

看完题目我们很快就能得到 $O(n^3)$ 的做法：

1. 将序列 $a$ 从小到大排序。
1. $ans=\sum\limits_{i=1}^{n}\sum\limits_{j=1,j\neq i}^{n}\sum\limits_{k=1,k\neq i,k\neq j}^{n} [\gcd(a_k,a_i)=1]$ 

### $\text{Part 1.1 问题转化}$

我们将三元组 $(a_i,a_j,a_k)$ 的最大最小值分别表示为 $a_{\max}$ 和 $a_{\min}$。

容易看出一个三元组 $(a_{\min},a_k,a_{\max})$ 是否合法，仅与它的 $a_{\min}$ 和 $a_{\max}$ 有关，而中间的 $a_k$ 只需要保证 $a_{\min}<a_k<a_{\max}$ 即可。

因为我们已经将序列 $a$ 从小到大排了序，所以条件 $a_{\min}<a_k<a_{\max}$ 可转化为 $\min<k<\max$，即用下标的大小关系表示数值的大小关系。

也就是说对于每一对满足 $a_i<a_j$ 的序列元素组 $(a_{i},a_{j})$，当我们将 $a_i,a_j$ 分别作为一个三元组的最大最小值时，三元组 $(a_{\min}[a_{\min}=a_{i}],a_k,a_{max}[a_{\max}=a_j])$ 对我们最终要求得的合法三元组个数的贡献为（三元组中的 $a_k$ 不定）：

1. $\gcd(a_{\min},a_{\max})=1$：三元组 $(a_{\min}[a_{\min}=a_{i}],a_k,a_{\max}[a_{\max}=a_j])$ 对答案的贡献就是满足 $a_{\min}<a_k<a_{\max}$ 的 $a_k$ 的个数。

- 我们在上面分析过了，满足 $a_{\min}<a_k<a_{\max}$ 实际上就相当于满足 $\min<k<\max$，故我们可得：

合法三元组 $(a_{\min}[a_{\min}=a_{i}],a_k,a_{\max}[a_{\max}=a_j])$ 的数量

$=$ 满足 $\text{}a_{\min}<a_k<a_{\max}$ 的 $a_k$ 的个数

$=$ 满足 $\min<k<\max$ 的$ k$ 的个数

$=\max-\min-1$

注意，上面的式子是在满足 $\gcd(a_{\min},a_{\max})=1$ 的前提下得到的。

2. $\gcd(a_{\min},a_{\max})\neq 1$：则合法三元组个数为 $0$。

分析到这里我们发现问题可以转化为枚举每一对满足 $a_i<a_j$ 的序列元素组 $(a_{i},a_{j})$，也就是枚举每个三元组的 $a_{\min}$ 和 $a_{\max}$，然后计算三元组 $(a_{\min},a_k,a_{\max})$ 对我们最终要求得的合法三元组个数的贡献（三元组中的 $a_k$ 不定），故我们得到：

$$ans=\sum\limits_{i=1}^{n}\sum_{j=i+1}^{n}(j-i-1)[\gcd(a_i,a_j)=1]$$

直接求解上式的时间复杂度为 $O(n^2)$，仍然无法通过此题，于是我们考虑继续优化。
### $\text{Part 1.2 式子转化}$

这里有一个前置知识 QwQ：莫比乌斯函数（符号为 $\mu$ ）。

对于其定义，这里直接放图。

![](https://cdn.luogu.com.cn/upload/image_hosting/edewt6tj.png)

不太了解莫比乌斯函数的话可以去 [cmd 爷 の blog](https://www.luogu.com.cn/blog/command-block/mu-bi-wu-si-fan-yan-ji-ji-ying-yong) 那里学习一下噢。~~（看完题解再去学啊喂！）~~

这里有一个关于莫比乌斯函数的性质需要我们了解一下：

$$\sum\limits_{d|n}\mu(d)=[n=1]$$

要证明的话，直接理解函数定义 $+$ 分类讨论就可以啦，这里不作过多阐述。

由莫比乌斯函数的这个性质我们得到一个转化式子的新思路：

- 将 $[\gcd(a_i,a_j)=1]$ 转化为 $\sum\limits_{d|a_i,d|a_j}\mu(d)$。

~~实际上这也是一个比较常见的套路呐。~~

那么此时 $\text{Part 1.1}$ 中推导出来的式子我们就可以继续进行转化啦！

$$ans=\sum\limits_{i=1}^{n}\sum_{j=i+1}^{n}(j-i-1)[\gcd(a_i,a_j)=1]$$
$$=\sum\limits_{i=1}^{n}\sum_{j=i+1}^{n}(j-i-1)\sum\limits_{d|a_i,d|a_j}\mu(d)$$

通过交换求和符号我们可得：

$$ans=\sum\limits_{d=1}^n\mu(d)\sum\limits_{i=1}^{n}\sum\limits_{j=i+1}^{n}(j-i-1)[d|a_i][d|a_j]$$


不难发现，在和式的 $\sum\limits_{i=1}^{n}\sum\limits_{j=i+1}^{n}(j-i-1)[d|a_i][d|a_j]$ 的部分中我们大量地重复枚举了 $d$ 的倍数，于是我们考虑继续在这里进行优化。

在枚举 $d$ 的时候，我们考虑弄一个 $num$ 数组将所有小于等于 $a$ 数组中的最大值的 $d$ 的倍数存储下来。

即 $num=\{ d,2d,\cdots,k\cdot d\}(k\cdot d \leq n)$。

显然有 $num$ 序列中的元素个数为 $k$，且 $k=\left\lfloor\dfrac{n}{d}\right\rfloor$。

此时我们可以继续推出新的式子：

$$ans=\sum\limits_{d=1}^n\mu(d)\sum\limits_{i=1}^{n}\sum\limits_{j=i+1}^{n}(j-i-1)[d|a_i][d|a_j]$$
$$=\sum\limits_{d=1}^n\mu(d)\sum\limits_{i=1}^{k}\sum\limits_{j=i+1}^{k}num_j-num_i-1$$

此时我们可以将和式的 $num_j-num_i-1$ 拆解为 $num_j-num_i$ 和 $-1$ 两部分来计算：


1. 我们先计算 $-1$ 部分的总值。

当 $i=1$ 时， $\sum\limits_{j=i+1}^{k}(-1)=-(k-1)$ ;

当 $i=2$ 时， $\sum\limits_{j=i+1}^{k}(-1)=-(k-2)$ ;

$\dots\dots$

当 $i=k$ 时， $\sum\limits_{j=i+1}^{k}(-1)=0$。

显然有和式 $\sum\limits_{i=1}^{k}\sum\limits_{j=i+1}^{k}(-1)=-[(k-1)+(k-2)+\cdots+-0]$，即为项数为 $k$ 公差为 $1$ 的等差数列求和然后再取负数，故我们直接用求和公式就可以直接算出 $-1$ 的总值：

$$\sum\limits_{i=1}^{k}\sum\limits_{j=i+1}^{k}(-1)=-\dfrac{k\cdot(k-1)}{2}$$

2. 接着我们计算 $num_j-num_i$ 部分的值：

~~根据套路~~我们发现 $\sum\limits_{i=1}^{k}\sum\limits_{j=i+1}^{k}num_j-num_i$ 的求值其实就是求取 $1\leq x\leq k$ 范围内的每一个 $num_x$ 的贡献。

于是我们将 $num_j-num_i$ 分为 $num_j$ 和 $-num_i$ 两部分来求解：

2.1 $num_x$ 作为 $num_j$ 被累加时：

- 当 $num_x$ 作为原式中的 $num_j$ 被累加时，当且仅当和式 $\sum\limits_{i=1}^{k}$ 满足 $i\leq x-1$ 时，和式 $\sum\limits_{j=i+1}^{k}$ 才会对 $num_x$ 的累加有一次贡献。

- 易得 $num_x$ 会作为 $num_j$ 被累加 $x-1$ 次。

2.2 $num_x$ 作为 $num_i$ 被**减去**时：

~~应该不会有人已经忘记了原来的和式中 $num_i$ 的系数为 $-1$ 吧。 QwQ~~

- 对于 $i=x$，第二个和式的 $j$ 的取值范围就是 $x+1\sim k$，也就是说 $num_x$ 会被**减去** $k-x$ 次。

- 则 $num_x$ 会作为 $num_i$ 被计算 $-(k-x)$ 即 $x-k$ 次。

最后我们得到 $num_x$ 作为 $num_i$ 和 $num_j$ 被计算之后总的贡献就是：

$$num_x\cdot[(x-1)+(x-k)]$$
$$=num_x\cdot(2x-k-1)$$

此时我们再重新看回到我们的式子推导：

$$ans=\sum\limits_{i=1}^{n}\sum_{j=i+1}^{n}(j-i-1)[\gcd(a_i,a_j)=1]$$
$$=\sum\limits_{i=1}^{n}\sum_{j=i+1}^{n}(j-i-1)\sum\limits_{d|a_i,d|a_j}\mu(d)$$
$$=\sum\limits_{d=1}^n\mu(d)\sum\limits_{i=1}^{n}\sum\limits_{j=i+1}^{n}(j-i-1)[d|a_i][d|a_j]$$

弄一个 $num$ 数组将所有小于等于 $a$ 中的最大值的 $d$ 的倍数存储下来，其元素个数为 $k$：

$$=\sum\limits_{d=1}^n\mu(d)\sum\limits_{i=1}^{k}\sum\limits_{j=i+1}^{k}num_j-num_i-1$$

计算 $1\sim k$ 中的每一个 $num$ 的贡献以及 $-1$ 的贡献：

$$ans=\sum\limits_{d=1}^n\mu(d)\sum\limits_{i=1}^{k}\sum\limits_{j=i+1}^{k}num_j-num_i-1$$
$$=\sum\limits_{d=1}^n\mu(d) \left[-\dfrac{k\cdot(k-1)}{2}+\sum\limits_{x=1}^{k}num_x\cdot(2x-k-1)\right]$$

$\mu$ 的值直接线性筛 $O(n)$ 预处理就可以了。 QwQ

此时求解答案的时间复杂度为 $O(n\log n)$。

## $\text{Part 2. Code}$
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int M=300005;
int n,a[M],ans,mu[M],f[M],num[M];
bool bo[M];
vector<int>pri;
void pre();
signed main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
        scanf("%lld",&a[i]);
    sort(a+1,a+1+n);
    for(int i=1;i<=n;i++) f[a[i]]=i;
    pre();
    for(int i=1;i<=a[n];i++){
        if(!mu[i]) continue;
        int k=0,sum;
        for(int j=i;j<=a[n];j+=i){
            if(f[j]) num[++k]=f[j];
        }
        sum=-(k-1)*k>>1;
        for(int j=1;j<=k;j++)
            sum+=num[j]*(j+j-k-1);
        ans+=mu[i]*sum;
    }
    printf("%lld",ans);
    return 0;
}

void pre(){
    mu[1]=1; int ss=0;
    for(int i=2;i<=M-4;i++){
        if(!bo[i]) mu[i]=-1,++ss,pri.push_back(i);
        for(int j=0;j<ss&&i*pri[j]<=M-4;j++){
            bo[i*pri[j]]=1;
            if(!(i%pri[j])) break;
            mu[i*pri[j]]=-mu[i];
        }
    }
}
```


---

## 作者：DaiRuiChen007 (赞：1)

# CF1780F 题解



## 思路分析

看到 $\gcd(\max\{a_i,a_j,a_k\},\min\{a_i,a_j,a_k\})=1$ 第一时间想到反演。

发现对形如 $d\mid \gcd(\max\{a_i,a_j,a_k\},\min\{a_i,a_j,a_k\})$ 这样的 $(i,j,k)$ 进行计数很好做：

我们只需要先对 $a_i$ 排序，再把所有 $d\mid a_i$ 的 $i$ 按顺序加入序列 $\{k_i\}$，然后在 $\{k_i\}$ 中任选两个做 $\min,\max$，然后枚举中间数即可，即统计 $\{k_i\}$中所有 $k_i>k_j$ 的 $k_i-k_j-1$ 之和。

那么我们记 $f(d)$ 表示所有满足 $\gcd(\max\{a_i,a_j,a_k\},\min\{a_i,a_j,a_k\})=d$ 的 $(i,j,k)$ 的数量，$g(d)$ 表示所有满足 $d\mid \gcd(\max\{a_i,a_j,a_k\},\min\{a_i,a_j,a_k\})$ 的 $(i,j,k)$ 的数量。

进行对 $f,g$ 莫比乌斯反演：$g(n)=\sum_{n\mid d} f(d)\implies
f(n)=\sum_{n\mid d} g(d)\times \mu\left(\dfrac dn\right)$。

而我们要求的就是 $f(1)$ 的值，按照上述过程计算即可，注意实现的常数。

时间复杂度 $\Theta(n\sqrt w)$，其中 $w$ 是 $a_i$ 的值域。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define ll long long
#pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,avx2")
using namespace std;
const int MAXN=3e5+1;
int a[MAXN],mu[MAXN],n;
ll ans,sum[MAXN];
int cnt[MAXN];
bool mark[MAXN];
vector <int> primes;
inline void solve(int p,int x) {
	if(mu[p]==0) return ;
	ans+=(ll)mu[p]*(ll)((ll)(x-1)*(ll)cnt[p]-sum[p]);
	sum[p]+=(ll)x,++cnt[p];
}
signed main() {
	for(int i=1;i<MAXN;++i) mu[i]=1;
	for(int i=2;i<MAXN;++i) {
		if(!mark[i]) mu[i]=-1,primes.push_back(i);
		for(int p:primes) {
			if(i*p>=MAXN) break;
			mark[i*p]=true,mu[i*p]=-mu[i];
			if(i%p==0) {
				mu[i*p]=0;
				break;
			}
		}
	}
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	for(int i=1;i<=n;++i) {
		for(int j=1;j*j<=a[i];++j) {
			if(a[i]%j==0) {
				solve(j,i);
				if(j*j!=a[i]) solve(a[i]/j,i);
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```



---

## 作者：HBWH_zzz (赞：0)

# [CF1780F Three Chairs](https://codeforces.com/problemset/problem/1780/F)

>给定 $n$ 个互异的数 $a_i\in[1,3\times 10^5]$，求满足 $\gcd(\min(a_i,a_j,a_k),\max(a_i,a_j,a_k))=1$ 的无序数对 $(i,j,k)$ 的数量。$n\leq 3\times 10^5$。

赛时的假做法改进了一下。（好像和官方做法不太一样）

考虑答案为 $\binom{n}{3}-\sum_{i,j,k}[\gcd(\min(a_i,a_j,a_k),\max(a_i,a_j,a_k))\neq1]$，尝试枚举最大值最小值：（用 $S_i$ 来代指值域在 $[1,i]$ 中的数的个数）

$$
\sum_{i,j,k}[\gcd(\min(a_i,a_j,a_k),\max(a_i,a_j,a_k))\neq1]
$$

$$
=\sum_{1\leq i\leq j\leq 3\times 10^5}[\gcd(i,j)\neq 1\And i\in a\And j\in a](S_{j-1}-S_{i})
$$

$$
=\sum_{g=2}^n\sum_{i=1}^{\lfloor\frac{n}{g}\rfloor}\sum_{j=i+1}^{\lfloor\frac{n}{g}\rfloor}[\gcd(i,j)=1\And ig\in a \And jg\in a](S_{jg-1}-S_{ig})
$$

$$
=\sum_{g=2}^n-\mu(g)\sum_{i=1}^{\lfloor\frac{n}{g}\rfloor}[ig\in a]\left((\sum_{j=1}^{i-1}[jg\in a]S_{ig-1})-(\sum_{j=i+1}^{\lfloor\frac{n}{g}\rfloor}[jg\in a]S_{ig})\right)
$$

到这一步事情就非常好解决了，直接暴力枚举 $g$，像埃式筛那样一次性找出所有合法的 $ig$，这样是 $O(n\log n)$ 的，十分简单！[代码自取](https://codeforces.com/contest/1780/submission/190631893)。

---

## 作者：chroneZ (赞：0)

给定数列 $\{ a_n \}$，求无序三元组 $(i, j, k)$ 的数量，满足 $\gcd(\min(a_i, a_j, a_k), \max(a_i, a_j, a_k)) = 1$，$n \leq 3 \cdot 10^5, a_i \leq 3 \cdot 10 ^ 5$ 且 $a_i$ 互不相同。

---

记 $[~]$ 为艾佛森括号，$V = \max(a_i), e_i = [i \in \{a_n\}],s_i = \sum \limits_{j = 1} ^ i e_j$。

考虑枚举 $(a_i, a_j, a_k)$ 中的最小值与最大值，记最大值为 $i$，最小值为 $j$，则第三个数值有 $\sum \limits_{x = j + 1} ^ {i - 1} e_x = s_{i - 1} - s_j$ 种方案。容易得到如下结果。
$$
Ans = \sum \limits_{i = 2} ^ {V} [e_i = 1]\sum \limits_{j = 1} ^ {i - 1} [e_j = 1][\gcd(i, j) = 1](s_{i - 1} - s_j)
$$
对 $[\gcd(i, j) = 1]$ 作莫比乌斯反演，得
$$
\begin{aligned}
Ans &= \sum \limits_{i = 2} ^ {V} [e_i = 1]\sum \limits_{j = 1} ^ {i - 1} [e_j = 1](s_{i - 1} - s_j) \sum \limits_{d | i, d | j} \mu(d) \\

&= \sum \limits_{d = 1} ^ V \mu(d) \sum \limits_{i = 1} ^ {\lfloor \frac{V}{d} \rfloor} [e_{di} = 1]\sum \limits_{j = 1} ^ {i - 1} [e_{dj} = 1](s_{di - 1} - s_{dj})\\

&= \sum \limits_{d = 1} ^ V \mu(d) \sum \limits_{i = 1} ^ {\lfloor \frac{V}{d} \rfloor} [e_{di} = 1]( s_{di - 1} (\sum \limits_{j = 1} ^ {i - 1} e_{dj}) - \sum \limits_{j = 1} ^ {i - 1} [e_{dj} = 1] s_{dj})
\end{aligned}
$$

$\sum \limits_{j = 1} ^ {i - 1} e_{dj}, \sum \limits_{j = 1} ^ {i - 1} [e_{dj} = 1] s_{dj}$ 都可以随 $i$ 的枚举递推，故由调和级数知计算该式的时间复杂度为 $\mathcal{O}(n \log n)$，可以通过本题。

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
constexpr int V = 3e5 + 10;
vector<int> pr, mu(V), vis(V);
void sieve(){
	mu[1] = 1;
	for(int i = 2; i < V; i++){
		if(!vis[i]) mu[i] = -1, pr.push_back(i);
		for(int j = 0; j < pr.size() && pr[j] * i < V; j++){
			vis[pr[j] * i] = 1;
			if(i % pr[j] == 0) break;
			mu[pr[j] * i] = -mu[i];
		}
	}
}
// 线性筛计算 mu 函数
void solve(){
	int n; cin >> n;
	vector<int> a(n), s(V, 0), exist(V, 0);
	for(int i = 0; i < n; i++)
		cin >> a[i], s[a[i]]++, exist[a[i]] = 1;
	for(int i = 1; i < V; i++) s[i] += s[i - 1];
	
	i64 ans = 0;
	for(int d = 1; d < V; d++){
		i64 r = 0, A = 0, e = 0;
		for(int i = 1; i * d < V; i++){
			if(!exist[i * d]) continue;
			r += 1LL * s[i * d - 1] * e - A;
			A += s[i * d]; e++;
			// e 与 A 分别对应题解中递推的两部分式子
		}
		ans += mu[d] * r;
	}
	cout << ans << "\n";
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	sieve();
	solve();	
}
```

> 笔者为数不多的场切 2F 题，以此纪念


---

