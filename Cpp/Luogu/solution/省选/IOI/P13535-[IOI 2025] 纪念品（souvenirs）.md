# [IOI 2025] 纪念品（souvenirs）

## 题目背景

不要 $\texttt{\#include "souvenirs.h"}$。

你需要在文件头加入以下内容，并**使用 $\texttt{\textcolor{red}{C++\,20}}$ 提交**：

```cpp
#include <utility>
#include <vector>
std::pair<std::vector<int>, long long> transaction(long long M);
```

## 题目描述

Amaru 在一家国外商店购买纪念品。商店有 $N$ **种**纪念品，而且每种纪念品有无限多件现货。

每种纪念品都有一个固定的价格：第 $i$ 种（$0 \leq i < N$）纪念品的价格为 $P[i]$ 枚硬币，其中 $P[i]$ 是一个正整数。

Amaru 知道纪念品种类是按价格降序排列的，而且所有纪念品的价格互不相同。具体来说，$P[0] > P[1] > \cdots > P[N-1] > 0$。此外，他还知道 $P[0]$ 的值。不幸的是，Amaru 没有其他纪念品的价格信息。

为了购买纪念品，Amaru 会与卖家进行若干次交易。

每次交易由以下步骤组成：

1. Amaru 向卖家支付一定数量（正数）的硬币。
1. 卖家将这些硬币堆放在商店后台的桌子上，因此 Amaru 无法看到这些硬币。
1. 卖家按顺序依次处理每种纪念品 $0, 1, \ldots, N-1$。每种纪念品在每次交易中被处理**恰好一次**。
    * 当处理第 $i$ 种纪念品时，如果当前硬币堆中的硬币数量至少为 $P[i]$，则
        * 卖家从硬币堆中移除 $P[i]$ 枚硬币；
        * 卖家将一件第 $i$ 种纪念品放在桌子上。
4. 卖家将剩余的所有硬币和桌子上的纪念品交给 Amaru。

注意，在每次交易开始前，桌上没有任何硬币或纪念品。

你的任务是指导 Amaru 进行若干次交易，使得：

* 在每次交易中，他购买**至少一件**纪念品；
* 总体上他**恰好**购买了 $i$ 件第 $i$ 种纪念品，其中 $0 \leq i < N$。注意，这意味着 Amaru 不应购买第 $0$ 种纪念品。

Amaru 不需要最小化交易次数，而且拥有无限量的硬币供应。

### 实现细节

你需要实现以下函数。

```
void buy_souvenirs(int N, long long P0)
```

* $N$：纪念品的种数。
* $P0$：$P[0]$ 的值。
* 对每个测试用例，该函数恰被调用一次。

上述函数可以调用以下函数，来指导 Amaru 进行交易：

```
std::pair<std::vector<int>, long long> transaction(long long M)
```

* $M$：Amaru 支付给卖家的硬币数量。
* 该函数返回一对元素。第一个元素是数组 $L$，包含按顺序排列的已购买的纪念品种类。第二个元素是整数 $R$，表示交易后卖家返还给 Amaru 的硬币数量。
* 要求 $P[0] > M \geq P[N-1]$。条件 $P[0] > M$ 确保 Amaru 不购买第 $0$ 种纪念品，而条件 $M \geq P[N-1]$ 确保他至少购买一件纪念品。如果这些条件未被满足，你将收到 `Output isn't correct: Invalid argument`。注意，与 $P[0]$ 不同，$P[N-1]$ 的值未在输入中提供。
* 对每个测试用例，该函数最多被调用 $5000$ 次。

评测程序的行为是**非自适应的**。
这意味着在调用 `buy_souvenirs` 前，价格序列 $P$ 是固定的。

## 说明/提示

### 例子

考虑以下函数调用。

```
buy_souvenirs(3, 4)
```

共有 $N = 3$ 种纪念品，且 $P[0] = 4$。观察到只有三种可能的价格序列 $P$：$[4, 3, 2]$，$[4, 3, 1]$ 和 $[4, 2, 1]$。

假设 `buy_souvenirs` 调用 `transaction(2)`，且函数返回 $([2], 1)$，表示 Amaru 购买了一件第 $2$ 种纪念品，而且卖家返还了 $1$ 枚硬币。通过观察，我们可以推断出 $P = [4, 3, 1]$，因为：

* 对于 $P = [4, 3, 2]$，`transaction(2)` 会返回 $([2], 0)$。
* 对于 $P = [4, 2, 1]$，`transaction(2)` 会返回 $([1], 0)$。

然后 `buy_souvenirs` 可以调用 `transaction(3)` 返回 $([1], 0)$，表示 Amaru 购买了一件第 $1$ 种纪念品，而卖家返还了 $0$ 枚硬币。到目前为止，Amaru 购买了一件第 $1$ 种纪念品和一件第 $2$ 种纪念品。

最后，`buy_souvenirs` 可以调用 `transaction(1)` 返回 $([2], 0)$，表示 Amaru 购买了一件第 $2$ 种纪念品。注意，这里也可以调用 `transaction(2)`。至此，Amaru 共购买了一件第 $1$ 种纪念品和两件第 $2$ 种纪念品，符合要求。

### 约束条件

* $2 \leq N \leq 100$
* 对每个满足 $0 \leq i < N$ 的 $i$，有 $1 \leq P[i] \leq 10^{15}$ 。
* 对每个满足 $0 \leq i < N - 1$ 的 $i$，有 $P[i] > P[i+1]$ 。

### 子任务

| 子任务 | 分数 | 额外的约束条件 |
| :-----: | :----: | ---------------------- |
| 1 | $4$ | $N = 2$
| 2 | $3$ | 对每个满足 $0 \leq i < N$ 的 $i$，有 $P[i] = N - i$。
| 3 | $14$ | 对每个满足 $0 \leq i < N - 1$ 的 $i$，有 $P[i] \leq P[i+1] + 2$。
| 4 | $18$ | $N = 3$
| 5 | $28$ |  对每个满足 $0 \leq i < N-2$ 的 $i$，有 $P[i+1] + P[i+2] \leq P[i]$。对每个满足 $0 \leq i < N-1$ 的 $i$，有 $P[i] \leq 2 \cdot P[i+1]$。
| 6 | $33$ | 没有额外的约束条件。

## 样例 #1

### 输入

```
3
4 3 1```

### 输出

```
0 1 2```

# 题解

## 作者：_jimmywang_ (赞：6)

秒赤，好玩。

很神秘的题意，交互但是目标不是得到某个值而是完成一个目标，第一次见。

我们先把交互库返回的东西处理一下，我们想要返回的几样商品的价值和，而不是剩下的钱。我们记返回值为 `[a,b,c,...],x`，方括号里的是商品集合，$x$ 是它们的价值和。

首先我们发现询问 $\ge P[0]$ 的值是不合法的，不然 $P[0]$ 就买了；过于小的值也是很危险的，毕竟你不知道 $P[n-1]$ 是什么，万一小于它你就买不到东西，也是不合法的。那么第一步我们能干什么？唯一安全的值应该是 $P[0]-1$。

知道了这个后，我们来手玩一下小数据，比如 $n=3$。

第一步问 $P[0]-1$，会有两种情况：

- 返回 `[1] x`。这下我们直接知道 $P[1]=x$，接着问一次 $P[1]-1$ 就能知道 $P[2]$ 了。
- 返回 `[1,2] x`。这该怎么办！1 号商品已经没有剩余购买次数了，下一步只能买一个 2。这意味着我必须找出一个 $x'\in[P[2],P[1])$ 来询问。容易发现 $x'=\lfloor\frac{x}{2}\rfloor$ 满足条件。

这下 $n=3$ 就解决了，拼盘 39pts 到手。

这个过程中，有几个点很有启发性：

1. 找出一个 $x'\in[P[2],P[1])$ 来询问：如果我们能够对每个 $i\in[1,n-1]$，都找到一个 $x\in [P[i],P[i-1])$ 询问一次，这样获得的信息会构成一组 $n-1$ 元线性方程组，而且是满秩的（因为这样一次询问，$i$ 商品一定会被买，且只有 $\ge i$ 的商品可能会被买，因此是对角线全为 1 的上三角），可以直接消元得到每一个 $P[i]$。而且如果对于每个 $[P[i],P[i-1])$ **恰好**询问一次，一定能满足 $i$ 被买了 $\le i$ 次，不够的在解出 $P[i]$ 后补上即可。
2. $x'=\lfloor\frac{x}{2}\rfloor$ 满足条件：这提示我们使用上次询问的商品的平均价格来进行下次询问。因为这个平均一定会落在最大值和最小值之间，至少是安全的。

3. 知道 $P[i]$ 的值后，$x'=P[i]-1$ 一定属于 $[P[i+1],P[i])$，可以直接用。

有了这些前提后，我们定义一个求解函数 $f(S,x)$ ，其中 $S$ 是一个商品编号集，$x$ 是 $S$ 中商品的价值和（这个信息是由一次向交互库询问得来的）。这个函数做的事情是，求出 $\ge \min(S)$ 的所有商品的具体价值。

记 $\min(S)=m$，那么显然这个 $(S,x)$ 是上一次询问了一个 $x'\in[P[m],P[m-1])$ 得来的。为了满足每个 $[P[i],P[i-1])$ **恰好**询问一次，我们需要保证 $m$ 只会作为 $\min(S)$ 出现一次。这个记忆化一下就好。

具体做法是：

1. 每次进入这个函数，所有已知商品价格的 $i$ 一定形成一段后缀（这个是函数本身的进行过程保证的）。我们不断检查 $\max(S)$ 的价格是否已经确定，如果是，就删除 $\max(S)$ 并相应的更新 $x$。（这一步其实是在消元）
2. （如果此时 $|S|>1$）基于启发点 (2)，求出剩余物品的平均价格 $avr=\lfloor\frac{x}{|S|}\rfloor$ 并进行一次询问。注意此时 $\min(S)$ 和 $\max(S)$ 之间的所有值我们应该都不知道，相应的所有 $[P[i+1],P[i])$ 也都没有被询问过，所以进行这个询问是合理的。询问完以后递归处理。
3. 重复 1，2 两步直到 $|S|=1$。此时容易发现 $\min(S)$ 应该仍然是 $m$，这个时候显然 $P[m]=x$。由启发点 (3)，此时我们获得了 $x-1\in[P[m+1],P[m])$，如果 $m+1$ 没有被处理过，那么询问一次 $x-1$ 并递归处理。


最开始询问一次 $P[0]-1$ 并调用即可。

最后显然可能有物品没买够的，既然我们已经求出所有物品的价格，询问 $P[i]$ 就能恰好买一个 $i$，补上即可。

最后补一句，容易发现这个 5000 次交互是假的。每次至少得买一个，总共最多买 $1+2+\dots+99=4950$ 次，根本不怕这个次数上限。

---

## 作者：Genius_Star (赞：3)

### 思路：

大神题。

考虑递归，我们令 $p = \operatorname{dfs}(w, now)$ 表示此时已知下标 $\ge now$ 的所有值时最多用 $w$ 的价钱可以知道下标 $\ge p$ 的值；初始使用 $\operatorname{dfs}(P_0 - 1, n)$。

对于一个 $\operatorname{dfs}(w, now)$ 来说，首先调用 $\operatorname{transaction}(w)$，得到一个购买子序列 $A$（设 $st = A_0$），此时显然可以得到这个子序列的价值之和 $sum$，考虑这个子序列的平均数 $-1$，显然此时不可能买到 $st$（这里 $-1$ 是为了防止 $|A| = 1$ 时再次买到）。

然后考虑子问题用 $\operatorname{dfs}(\frac{sum - 1}{|A|}, now)$ 去更新现在的 $now$，此时考虑 $A$ 后面所有大于等于 $now$ 的位置，用 $sum$ 减去其的贡献，重新找平均数 $-1$ 的价格进行调用递归，不断逼近，直到 $now \le st$。

显然最终会先递归到 $st$ 等于 $n - 1$ 的情况（因为当 $|A| = 1$ 且 $st$ 不等于 $n - 1$ 时会使用 $P_{st} - 1$ 的价格去买，继续往下）；同理，这会始终保证 $cnt_i \le i$，因为对于一个 $st$，其递归的下一个 $st$ 一定比它小，所以对于一个 $i$ 来说，只有 $st \le i$ 的 $st$ 可能会买到它，且每个 $i$ 只会作为一次 $st$。

最后你已经求出了 $P$，补全 $i - cnt_i$ 次 $P_i$ 即可。

### 完整代码：

```cpp
#include <utility>
#include <vector>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fi first
#define se second
std::pair<std::vector<int>, long long> transaction(long long M);
const int N = 105;
ll val[N];
int cnt[N];
inline int dfs(ll w, int now){
	auto t = transaction(w);
	auto A = t.fi;
	ll r = t.se;
	w -= r;
	for(auto v : A)
	  ++cnt[v];
	while(A.back() >= now){
		w -= val[A.back()];
		A.pop_back();
	}
	while(A.front() + 1 < now){
		now = dfs((w - 1) / A.size(), now);
		while(A.back() >= now){
			w -= val[A.back()];
			A.pop_back();
		}
	}
	val[A.front()] = w;
	return A.front();
}
void buy_souvenirs(int N, long long P0){
	dfs(P0 - 1, N);
	for(int i = 1; i < N; ++i){
		while(cnt[i] < i){
			++cnt[i];
			transaction(val[i]);
		}
	}
}
```

**注意：这是在某交互大神帮助下完成的该题，并非独立做出。**

---

## 作者：晴空一鹤 (赞：3)

好题好题，比去年尼罗河船运有趣多了。

有一个非常好的策略是让前 $n-1$ 次"买的价值最高的东西在物品序列里的次序"从 $1$ 到 $n-1$ 都出现一次。

因为这样你就能得到 $n-1$ 个线性无关的方程（最高项都不一样当然线性无关了），直接解就能得到 $p$ 数组，然后你都知道每个东西多少钱了，随便买买就能满足要求了。

怎么做呢。

开局选一个 $p_0-1$ 防止买不到东西，接下来我们看看买到了几个东西。

如果只买到了一个东西，那我们就下一次买这个东西价值减 $1$。

如果买到了多个东西，我们下一次就买这堆东西价值的平均数。

容易发现，除非是只买到了 $p_{n-1}$，否则我们每次买的价值最高东西在物品序列里的次序是递增的，这同样也保证了这些操作后第 $i$ 个物品不可能买到超过 $i$ 次。

于是我们得到了 $p_{n-1}$。

接下来，我们引入一个概念——最长已知后缀。顾名思义，就是最长的每个物品价值都被我们知道的后缀。

我们称第 $i$ 个物品是好的，当且仅当之前买的次数中"买的价值最高的东西在物品序列里的次序"里出现过 $i$。那么我们找到最长已知后缀前的最后一个好物品，我们拿出那一次买的东西的序列，把这个序列里出现在最长已知后缀里的东西减掉。那么此时有两种情况：

如果只剩一个东西，下一次就买这个东西价值减 $1$。

如果剩了多个东西，我们下一次就买这堆东西价值的平均数。

那么我们下一次"买的价值最高的东西在物品序列里的次序"必然介于这个好的东西的次序和最长已知后缀之间，那它之前一定没有被作为最高位买过。因此我们还需要补全的"买的价值最高的东西在物品序列里的次序"减少了 $1$。

这样重复直到达到开头的目标就行了。~~我们就这样做做做做做，一记可爱构造，直接把这道题给过掉了，对它的打击比线段树维护矩乘板子还大。~~

---

## 作者：_lmh_ (赞：3)

下文中 $n=N-1$。

一次操作给了我们一条 $\{X_i\}$ 必须满足的关系式，解方程就可以得到所有 $X_i$。所以肯定是尝试解出所有 $X_i$，然后每次花 $X_i$ 的价格购买纪念品 $i$ 直到数量足够。

当 $X_{n}=1$ 时，任意一次（结果未知的）操作都有不小的可能会买进一个纪念品。但是一共只允许买 $n$ 个，所以肯定要在 $n$ 步之内完成求解——这是个很强的限制，因为询问次数的下界也是 $n$。

第一次肯定是买 $X_0-1$（买别的也没啥区别）。此时必定买进了一个 $X_1$。

不妨假设 $n>1$。如果只买到了一个 $X_1$ 那就成功规约到了一个子问题，但是如果买进了更多的数，例如，花费了 $k$ 元买入 $a_1=1,a_2,\cdots,a_c$，就需要解方程。

此时我们发现，由于 $X_i$ 互不相同，必定有 $X_1>\frac{k-1}{c}$。如果 $c>1$，必定有 $X_{a_c}\le \frac{k-1}{c}$。

此时第二步的操作可以是买入 $[\frac{k-1}{c}]$。

总之，必定存在一种方案使得下一步买入的最小编号更大，这样递推下去，总有一次买到了恰好一个 $X_n$。

**这启发我们从后往前求解，每次从之前得到的一个方程开始，进行一次最小编号更大的询问。**

具体地，尝试做出 $n$ 次询问，并将其排序，使得第 $i$ 个询问中买入的纪念品最小编号恰为 $i$。

将输入视为一次询问：第 $0$ 次询问得到 $X_0=P_0$，最小编号为 $0$。

维护变量 $m$ 代表 $m\le p\le n$ 中所有 $X_p$ 已经完成求解。每当这个后缀向左扩展的时候，对前面的所有方程进行暴力消元。

首先向左尽可能扩展。现在 $m-1$ 这个位置一定没有方程（否则可以向左再走一步）。

找出前面第一个方程，设其为：$X_{a_1}+X_{a_2}+\cdots+X_{a_c}=k$，有 $\max a_i<m$（这一部分已经完成了消元）。

如果 $c=1$，直接询问 $k-1$ 即可。此时得到的最小编号必定为 $a_1+1$。

否则，根据前面的推导，$X_{a_c}\le \frac{k-1}{c}$，同时 $X_{a_1}>\frac{k-1}{c}$。如果进行一次询问 $[\frac{k-1}{c}]$，得到的最小编号必定在 $[a_1+1,a_c]$ 之间。

由于 $[a_1+1,m-1]$ 之间没有询问，不管得到什么结果都可以接受。

这样就可以用 $n$ 次询问求出 $\{X_i\}$。对于任意一个 $i$，可能包含 $X_i$ 的方程只有 $1\sim i$，所以它至多买到了 $i$ 个——因此这个算法不会在中途爆掉。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,m,a[107][107],w[107],cnt[107],t[107];
void buy_souvenirs(int N,ll P0){
	n=N-1;m=N;
	w[0]=P0;cnt[0]=1;
	a[0][0]=1;
	for (int i=1;i<=n;++i) t[i]=i;
	while(m){
		int p=m-1;
		while(!a[p][p]) --p;
		ll k=(w[p]-1)/cnt[p];
		auto P=transaction(k);
		auto vec=P.first;k-=P.second;
		assert(vec.size()&&cnt[vec[0]]==0);
		cnt[vec[0]]=vec.size();
		w[vec[0]]=k;
		for (auto x:vec){a[vec[0]][x]=1;--t[x];}
		for (int i=n;i;--i) if (cnt[i]==1){
			for (int j=i-1;j;--j) if (a[j][i]){
				a[j][i]=0;w[j]-=w[i];--cnt[j];
			}
		}
		while(m&&cnt[m-1]==1) --m;
	}
	for (int i=1;i<=n;++i) while(t[i]--) transaction(w[i]);
}
```

---

## 作者：RainySoul (赞：2)

感觉是个好题哦。

不难发现就算一次操作只买一个的函数调用次数是 $\frac{(0+99)\times 100}{2}=4950$，所以 $5000$ 的操作次数限制是假的。可以尝试通过某些操作将整个 $P$ 序列求出来之后从小到大补齐。

一次询问相当于查出来一个方程 $P_{a_1}+P_{a_2}+\cdots +P_{a_k} = sum$。首先考虑一次查询怎么查一定不会似，需要保证查询值 $P_{a_k}\le X<P_{a_1}$，稳妥的取法是直接取 $X=\lfloor\frac{sum}{x}\rfloor$。不过注意当一个方程是 $P_{a_1}=sum$ 的时候要查 $sum-1$。

每次查询得到的 $a_1$ 相比于上次的必定后移，于是我们重复上面操作可以得到 $P_{n-1}$。然后很自然地想能否从后往前一个一个还原。现在假设我们求得 $P_{n-1}$，考虑如何还原 $P_{n-2}$。首先肯定是将 $P_{n-1}$ 带入到已知方程里面暴力消元，如果我们有一个以 $P_{n-2}$ 为开头的方程那么就可以求得 $P_{n-2}$，如果没有的话就从现在所有方程里面找出来 $a_1$ 最大的那个，由我们之前的操作方法每次操作 $a_1$ 必定后移，可以将这个序列不断操作直到这个 $a_1$ 为 $n-2$，然后求得了 $P_{n-2}$。仿照 $P_{n-2}$ 的方式可以得到 $P_{n-3}$，然后一路推到 $P_{1}$。

考虑这样操作的合法性，每个位置只会被作为一个方程的开头，这样即使在最坏情况下也满足 $P_i$ 被购买次数 $\le i$。

AC code：

```cpp
#include <utility>
#include <vector>
using namespace std;
const int N=110;
std::pair<std::vector<int>, long long> transaction(long long M);
long long p[N],cnt[N];
struct zyx{
    vector<int> a;
    long long sum=0,vis=0;
};
vector<zyx> v;
void solve(int n){
    for(int i=n-1;i>=1;i--)
        while(cnt[i]<i)transaction(p[i]),cnt[i]++;
    return;
}
void buy_souvenirs(int n,long long P0){
    p[0]=P0;
    auto temp=transaction(p[0]-1);
    for(int i=0;i<(int)temp.first.size();i++)cnt[temp.first[i]]++;
    v.push_back((zyx){temp.first,p[0]-1-temp.second,0});
    for(int i=n-1;i>0;i--){
        if(p[i])continue;
        while(1){
            int flag=0;
            for(int j=0;j<(int)v.size();j++){
                for(int k=v[j].a.size()-1;k>=0;k--){
                    if(p[v[j].a[k]])v[j].vis=0,v[j].sum-=p[v[j].a[k]],v[j].a.pop_back();
                    else break;
                }
            }
            for(int j=0;j<(int)v.size();j++){
                if(v[j].sum==0)continue;
                if(v[j].a[0]==i){
                    p[i]=v[j].sum,flag=1,v[j].vis=1;
                    break;
                }
            } 
            if(flag==1)break;
            for(int j=v.size()-1;j>=0;j--){
                if(v[j].a.size()==0||v[j].sum==0||v[j].vis==1)continue;
                if(v[j].a.size()==1){
                    p[v[j].a[0]]=v[j].sum;
                    auto temp=transaction(v[j].sum-1);
                    long long SUM=v[j].sum-1-temp.second;
                    for(int k=0;k<(int)temp.first.size();k++)cnt[temp.first[k]]++;
                    for(int k=(int)temp.first.size()-1;k>=0;k--){
                        int now=temp.first[k];
                        if(p[now]){
                            SUM-=p[now];
                            temp.first.pop_back();
                        }
                        else break;
                    }
                    v.push_back((zyx){temp.first,SUM,0}),v[j].sum=0,v[j].a.pop_back();
                    break;
                }
                auto temp=transaction(v[j].sum/(int)v[j].a.size());
                long long SUM=v[j].sum/(int)v[j].a.size()-temp.second;
                for(int k=0;k<(int)temp.first.size();k++)cnt[temp.first[k]]++;
                for(int k=(int)temp.first.size()-1;k>=0;k--){
                    int now=temp.first[k];
                    if(p[now]){
                        SUM-=p[now];
                        temp.first.pop_back();
                    }
                    else break;
                }
                v[j].vis=1,v.push_back((zyx){temp.first,SUM,0});
                break;
            }
        }
    }
    solve(n);
}
```

你是不是以为主播没有每次把 $a_1$ 最大的方程拎出来操作？其实直接从后往前扫可以保证所有方程的 $a_1$ 是单调递增的。

莫名其妙地在速度上遥遥领先拿下最优解。

---

## 作者：_Ch1F4N_ (赞：1)

什么传奇脑电波题。

首先第一次询问肯定只能问 $P_0-1$，然后会问出一个形如 $P_1+P_{l_1}+P_{l_2}+\dots+P_{l_k}=c$ 的信息，然后发现 $1$ 不能再选了，为了防止选 $1$ 考虑想办法把 $P_1$ 问出来，但是发现想直接问出来貌似很难。

于是退而求其次一下，找一个一定不会再选 $1$ 的方案问一下，发现 $\left\lfloor\frac{c}{k+1}\right\rfloor$ 就是一个一定不会再选 $1$ 但是至少会选一个的方案（因为 $\left\lfloor\frac{c}{k+1}\right\rfloor \geq P_{l_k}$），然后又会问出一堆东西，然后咋办？

镇定思考一下，发现想要构造出刚好让每个物品次数直接达标的方案很难，所以尝试在物品 $i$ 被选不超过 $i$ 次的前提下把 $P_i$ 问出来。然后再一个个地把次数叠满。

现在接着考虑怎么问出 $P_1$，当问了 $\left\lfloor\frac{c}{k+1}\right\rfloor$ 了之后，得到了 $P_{r_1}+P_{r_2}+\dots+P_{r_m}=z$ 的信息，其中 $r_1 > 1$。而我们希望把 $P_{l_1},\dots,P_{l_k}$ 全部问出来，这样就能推出 $P_1$ 了。

为了拆解问题，不妨假装我们已经构造出了一个非常厉害的策略，对于 $P_{r_1}+P_{r_2}+\dots+P_{r_m}=z$ 递归之后得到了所有 $j \geq r_1$ 的 $P_j$，由于 $1 < r_1 \leq l_k$（因为 $\left\lfloor\frac{c}{k+1}\right\rfloor \geq P_{l_k}$）所以会确定 $l_1,l_2,\dots,l_k$ 的一个非空后缀的 $P$ 值，于是你可以得到新的信息为：$P_1+P_{l_1}+\dots+P_{l_k'}=c'$，其中 $k'<k$，仿照上面的过程继续问下去，最后就可以确定 $P_1$ 的值。

把 $P_1$ 推广到 $P_L$，发现在前面假设的策略存在的前提下实现了一个对于 $L,R$ 在知道了所有 $j>R$ 的 $P_j$ 后可以问出所有 $L \leq i \leq R$ 的 $P_i$ 的策略，这个策略刚好是满足假设要求的，并且发现在询问过程中一个点 $i$ 最多在处理点 $j \in [1,i)$ 时被问到，而总次数不会超过 $\sum_{i=1}^{99} i = 5000$，那么这个题就做完了。

```cpp
#include<bits/stdc++.h>
#include "souvenirs.h"
using namespace std;
#define ll long long
const int maxn = 114;
ll cst[maxn];
int cnt[maxn];
int n;
void solve(int l,int r,ll tp,pair<vector<int>, long long> res){
    for(int x:res.first) cnt[x]++;
    ll y=tp-res.second;
    if(res.first.size()==1){
        cst[l]=y;
        if(l!=r) solve(l+1,r,cst[l]-1,transaction(cst[l]-1));
    }else{
        while(res.first.back()>r) y-=cst[res.first.back()],res.first.pop_back();
        int u=r;
        while(res.first.size()>1){
            ll ntp=y/res.first.size();
            pair<vector<int>, long long> nres=transaction(ntp);
            solve(nres.first[0],u,ntp,nres);
            u=nres.first[0]-1;
            while(res.first.back()>u) y-=cst[res.first.back()],res.first.pop_back();
        }
        cst[l]=y;
        if(l!=u) solve(l+1,u,cst[l]-1,transaction(cst[l]-1));
    }
}
void buy_souvenirs(int N, long long P0){
    n=N;
    solve(1,n-1,P0-1,transaction(P0-1));
    for(int i=1;i<n;i++){
        while(cnt[i]<i) transaction(cst[i]),cnt[i]++;
    }
}
```

---

## 作者：Mirasycle (赞：1)

有意思的题目。但是不难，因为这题的约束太强了，导致你在每种情况下基本只能进行一种操作（有一些可能合法但是显然无意义的操作就不去考虑了），所以顺着这个模拟就可以 AC 了！

记 $co_i$ 表示 $i$ 的价格。`solve(i,M)` 表示已知 $co_{i-1}> c\ge co_i$ 的情况下求解 $co_i$，并且会递归求出所有 $co_1,co_2\dots co_i$。这个函数带记忆化功能，也就是求解过的 $co_i$ 被调用了会跳过。下文的除法默认下取整。

你会发现初始为了去求 $co_1$ 只能询问 $P_0-1$，也就是 ${\rm solve}(1,P_0-1)$。

假设返回了 $\{id_1,id_2\dots id_m\}$，并且通过询问和返回的钱数我们知道了 $\sum co_{id_i}=C$。这个时候 $id_1$ 已经不能再询问了，而我们必须保证不能问到空的，这两个条件很强，所以我们应该去寻找一个介于 $co_{id_m}$ 到 $co_{id_1}$ 之间的数。由于和一定，且 $co$ 单调递减，所以 $co_{id_1}>\dfrac{C}{m}>co_{id_m}$。

于是直接询问 $\dfrac{C}{m}$ 会得到一个以原序列中的某个数字 $id_i$ 开头的序列。调用 ${\rm solve}(id_i,\dfrac{C}{m})$ 之后，我们可以求出 $co_{id_i},co_{id_{i+1}}\dots co_{id_m}$。

于是可以将上述问题 $\{id_1,id_2\dots id_m\}$ 缩小到 $\{id_1,id_2\dots id_{m'}\}$，其中 $m'=i-1$。不断执行这个过程，我们就可以得到 $co_{id_1}$ 了，也就完成了 $\rm {solve}(co_{id_1})$ 的任务。这样子就可以解出所有的 $co_i$ 了。

下面分析使用购买次数的问题，要求购买 $i$ 的次数为 $i$，我们不怕买少了，因为可以最后求出所有的 $co_i$ 之后再补。由于 $i$ 最多在求解 $co_1,co_2\dots co_i$ 的时候每次各购买一个，所以不会买多。

这个问题就完美解决了。

```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef vector<int> vi;
const int maxn=110;
int n,cnt[maxn]; ll co[maxn];
pair<vi,ll> transaction(ll M);
void to(ll M);
void calc(pair<vi,ll> vec,ll M){
	vi id=vec.fi,tmp;  M-=vec.se;
	for(auto z:id)
		if(co[z]) M-=co[z];
		else tmp.pb(z);
	id.clear(); for(auto z:tmp) id.pb(z);
	while(id.size()>1){
		to(M/id.size());
		while(co[id.back()]) M-=co[id.back()],id.pop_back();
	}
	co[id.front()]=M;
}
void solve(int pos,ll M,pair<vi,ll> vec){
	for(auto id:vec.fi) cnt[id]--;
	if(!co[pos]) calc(vec,M);
	while(co[pos+1]&&pos+1<=n) pos++;
	if(pos<n) to(co[pos]-1);
}
void to(ll M){
	pair<vi,ll> res=transaction(M);
	solve(res.fi.front(),M,res);
}
void buy_souvenirs(int N,ll P0){
	memset(co,0,sizeof(co));
	for(int i=1;i<=N-1;i++) cnt[i]=i;
	n=N-1; to(P0-1);
	for(int i=1;i<=n;i++)
		while(cnt[i]--) transaction(co[i]);
}
```

---

## 作者：IvanZhang2009 (赞：1)

容易发现我们需要让每个物品（除了第 $0$ 个）都作为第一个买的一次（即每个 $[p_i,p_{i-1})$ 里都询问一个数）。这样子每个数的次数都不会超标。其实可以做到找到每个 $p$。

考虑我们一开始只能问 $p_0-1$。我们发现如果一个询问可以得到一个物品的价格是很舒服的。我们定义 `solve(i)` 表示我们得到了 $p_i$，然后求出 $p_{i+1,\dots,n-1}$。这样如果我们询问直接得到了某个值就递归到后缀的子问题，然后可以把这个后缀删掉。

如果一开始得到的是多个物品的价值之和呢？可以发现我们能猜的只有平均价，因为要保证猜的价格不超过最大值，又要高于最小值。我们每次不妨每次找到所有未解决的询问里的最靠右的一个，如果它只有一个数，那就把这个后缀删掉，更新其他询问的信息；否则你就猜平均数，这样可以保证新加入的这个询问在当前的最后一个询问和最后一个没删的数之间，显然是不会和之前重复的。

重复这个过程一定可以结束。最后已经得到了所有物品的价格，把剩下的次数补上即可。

```cpp
#include "souvenirs.h"
#include<bits/stdc++.h>
using namespace std;
#define MOD         998244353
#define ll         long long
#define pii         pair<int,int>
#define all(v)      v.begin(),v.end()
#define pb          push_back
#define REP(i,b,e)  for(int i=(b);i<(int)(e);++i)
#define over(x)     {cout<<(x)<<endl;return;}
#define lowbit(x)   ((x)&(-(x)))
#define cntbit(x)   __builtin_popcount(x)
#define deal(v)     sort(all(v));v.erase(unique(v.begin(),v.end()),v.end())
#define lbound(v,x) lower_bound(all(v),x)-v.begin()
int n;
int cnt[105];
ll val[105];
deque<int>dq[105];
ll cost[105];
ll ask(ll x,int y){
	//(2z+y-1)*y/2<=x
	return (x*2/y+1-y)/2;
}
void clear_(){
	REP(i,0,n)if(dq[i].size()&&dq[i].back()==n-1)dq[i].pop_back(),cost[i]-=val[n-1];
	--n;
}
void solve(int x){
	if(x==n-1)return;
	auto [t,c]=transaction(val[x]-1);
	++x;
	for(auto i:t)++cnt[i];
	cost[x]=val[x-1]-1-c;
	for(auto i:t)if(val[i]==-1)dq[x].pb(i);
	else cost[x]-=val[i];
	while(x<n){
		int lst=x;
		REP(i,x,n)if(dq[i].size()&&val[lst]==-1)lst=i;
		if(dq[lst].size()==1){
			val[lst]=cost[lst];
			solve(lst);
			clear_();
			continue;
		}
		ll p=ask(cost[lst],dq[lst].size());
		auto [t,c]=transaction(p);
		int y=t[0];
		cost[y]=p-c;
		for(auto i:t)++cnt[i];
		for(auto i:t)if(val[i]==-1)dq[y].pb(i);
		else cost[y]-=val[i];
	}
}
void buy_souvenirs(int N, ll lst) {
	n=N;
	REP(i,0,n)cnt[i]=0,cost[i]=-1,val[i]=-1,dq[i].clear();
	val[0]=lst;
	solve(0);
	REP(i,0,N){
		while(cnt[i]<i)transaction(val[i]),++cnt[i];
	}
}

```

---

