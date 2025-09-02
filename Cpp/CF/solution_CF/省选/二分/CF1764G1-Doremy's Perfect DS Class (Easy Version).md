# Doremy's Perfect DS Class (Easy Version)

## 题目描述

The only difference between this problem and the other two versions is the maximum number of queries. In this version, you are allowed to ask at most $ \mathbf{30} $ queries. You can make hacks only if all versions of the problem are solved.

This is an interactive problem.

"Everybody! Doremy's Perfect Data Structure Class is about to start! Come and do your best if you want to have as much IQ as me!" In today's Data Structure class, Doremy is teaching everyone a powerful data structure — Doremy tree! Now she gives you a quiz to prove that you are paying attention in class.

Given an array $ a $ of length $ m $ , Doremy tree supports the query $ Q(l,r,k) $ , where $ 1 \leq l \leq r \leq m $ and $ 1 \leq k \leq m $ , which returns the number of distinct integers in the array $ \left[\lfloor\frac{a_l}{k} \rfloor, \lfloor\frac{a_{l+1}}{k} \rfloor, \ldots, \lfloor\frac{a_r}{k} \rfloor\right] $ .

Doremy has a secret permutation $ p $ of integers from $ 1 $ to $ n $ . You can make queries, in one query, you give $ 3 $ integers $ l,r,k $ ( $ 1 \leq l \leq r \leq n $ , $ 1 \leq k \leq n $ ) and receive the value of $ Q(l,r,k) $ for the array $ p $ . Can you find the index $ y $ ( $ 1 \leq y \leq n $ ) such that $ p_y=1 $ in at most $ \mathbf{30} $ queries?

Note that the permutation $ p $ is fixed before any queries are made.

## 说明/提示

The permutation in the example is $ [3,5,2,1,4] $ .

The input and output for example illustrate possible interaction on that test (empty lines are inserted only for clarity).

In this interaction process:

- For the first query, $ \lfloor\frac{3}{4}\rfloor=0,\lfloor\frac{5}{4}\rfloor=1,\lfloor\frac{2}{4}\rfloor=0 $ , so the answer is $ 2 $ .
- For the second query, $ \lfloor\frac{2}{3}\rfloor=0,\lfloor\frac{1}{3}\rfloor=0,\lfloor\frac{4}{3}\rfloor=1 $ , so the answer is still $ 2 $ .
- For the third query, $ \lfloor\frac{2}{5}\rfloor=0,\lfloor\frac{1}{5}\rfloor=0 $ , so the answer is $ 1 $ .
- For the fourth query, $ \lfloor\frac{2}{2}\rfloor=1,\lfloor\frac{1}{2}\rfloor=0,\lfloor\frac{4}{2}\rfloor=2 $ , so the answer is $ 3 $ .

The correct answer is got after $ 4 $ queries, so this process will be judged correct.

## 样例 #1

### 输入

```
5

2

2

1

3```

### 输出

```
? 1 3 4

? 3 5 3

? 3 4 5

? 3 5 2

! 4```

# 题解

## 作者：feecle6418 (赞：19)

这题思考过程很有启发性。

如果看到题直接想，询问能提供什么信息？就做死了。因为询问根本没法提供有价值的“信息”。

换种方式思考，如果要求的不是 1 的位置而是其它数的位置能不能做？询问 $n$ 的位置是可做的，因为它是唯一一个除以 $n$ 下取整是 1 的数，那一个区间 $[l,r]$ 包含 $n$ 且长度不是 1 的话，询问 $[l,r,n]$ 得到的结果就是 2，否则就是 1，据此可以二分找出答案。

那为何 $n$ 的位置如此容易寻找？是因为 $n$ 具有，“是唯一一个除以 $n$ 下取整是 1 的数”这个性质。因此，我们自然想，1 有没有什么与下取整有关的唯一性呢？

思考到这里，再经过一些尝试，就不难得出本题最重要的观察：1 是唯一一个除以 $2$ 下取整是 0 的数（称之为 1 的性质）。这意味着，无论哪个 $[2,n]$ 的子集 $S$，加入 1 后得到 $T$，$S$ 中的数除以二下取整得到  $U$，$T$ 中的数除以二下取整得到  $V$，**一定**有 $|V|=|U|+1$。

很遗憾，$n$ 是偶数时，$n$ 也具有上面这个性质。不过根据刚才的讨论，很容易区分 1 和 $n$，因此我们已经找到一个很可做的切入点，只需要据此编一个做法。

设 $Q(l,r,k)$ 为询问 $[l,r],k$ 得到的答案。设 $x$ 的位置是 $q_x$。则不难发现，上述观察等价于，$Q(1,q_1-1,2)+1=Q( 1,q_1,2),Q(q_1,n,2)=Q(q_1+1,n,2)+1$。这是因为 $\{x|q_x\in [1,q_1-1]\cup [q_1+1,n]\}=[2,n]$。

因此，设 $a_i=Q(1,i,2)-Q(1,i-1,2),b_i=Q(i,n,2)-Q(i+1,n,2)$，若 $p_i$ 没有 1 的性质，则 $a_i,b_i$ 中有一个为 1，有一个为 0。否则，$a_i,b_i$ 均为 1。而我们可以用 $O(1)$ 次询问得到 $a,b$ 的区间和。因此，容易二分出满足 1 的性质的位置了。如果事先找出 $n$ 的位置，再根据 $n$ 的位置找出另一个满足 1 的性质的位置，需要 $3\log n$ 次询问，可以通过 G1。G2,G3 的优化在此略去。

本题思考过程给我们的启发是，当看不出题目的操作有什么直接用处时，可以从所求入手，思考为什么能求出题目要求的。

---

## 作者：xiaolilsq (赞：4)

# 题解 CF1764G Doremy's Perfect DS Class (Extra)

注：下面内容包含了 easy version 的题解。

### 题意

交互库有一个 $1\sim n$ 的排列 $p$，你每次可以想交互库给定三个整数 $l,r,k(1\le l\le r\le n,1\le k\le n)$，交互库会返回 $\lfloor p_l/k\rfloor,\lfloor p_{l+1}/k\rfloor,\dots,\lfloor p_r/k\rfloor$ 中不同数的个数。你需要在 $\lceil 2n\log_2n\rceil$ 次询问内**确定整个数组**。

$3\le n\le 1024$。

### 题解

可以先尝试着确定一些简单的值，不难发现 $n$ 的值很容易从 $k=n-1$ 的情况下二分出来得到位置，于是一种朴素的想法就是依次找到 $n,n-1,\dots,1$ 这些数的位置。但是这样想下来会发现完全无法操作，因为在二分求解 $x$ 的位置时候很有可能要把大于 $x$ 的这些数全部排除在外，排除掉这些数可能就会分割出很多区间，操作次数很难优于 $O(n^2)$。

找最大的数不好我们可以尝试找一下最小的数 $1$，这也是原题三个 version 的要求。要找 $1$ 想到可以让 $k=2$ ，于是发现 $k=2$ 相当于 $(2,3),(4,5),(6,7),...$ 这些数对匹配，然后通过一些简单计算相当于查询区间匹配数量。

当 $n$ 为奇数的时候，$1$ 是唯一一个单出来没有其它匹配的数。考虑二分 $[l,r]$，确定 $1$ 是在 $m=\lfloor(l+r)/2\rfloor$ 的左边还是右边。可以分别查询 $[1,m]$ 和 $[m+1,n]$ 两个区间，总匹配数量我们是知道的，而匹配对要么只在左边要么只在邮编要么跨越两边，由此两边不断消去匹配对直到唯一一个区间剩下的一个数就是 $1$ 了。

而 $n$ 为偶数的时候，$n$ 和 $1$ 都是单出来的，不过前面我们可以简单找到 $n$ 的位置，所以很好区分 $n$ 和 $1$，我们便实现了不超过 $\lceil3\log_2 n\rceil$ 次找到 $1$ ，而三个 version 也只是在进行没有太大意义的常数优化罢了。

找到了 $1$ 之后考虑依次确定 $2,3,\dots,n$ 吗？容易发现比从大到小确定更难了。既然按照**数字大小**依次确定没有戏了，不妨考虑按照**相对位置**尝试一下。如果 $1$ 在位置 $x$，那么位置 $x-1$ 的数字突然发现变得意外地好求了！因为只要通过两个数绑在一起除以 $k$ 下取整，就可以判断是小于 $k$ 还是大于等于 $k$ 了。然后考虑 $x-2$ 的位置，和 $1$ 不是相邻的有点不太好处理，而想到 $x-3$ 后面就更加困难了，所以我们需要一个**更加具有普适性的思路**来依次确定这些数字。

考虑和 $1$ 相邻我们究竟用到了什么性质，就是除以 $k(k\ge 2)$ 下取整后 $1$ 必然会变成 $0$，然后我们相当于就只是在判断这个数除以 $k$ 是不是也是变成 $0$ 罢了。由此启发我们这样的一个思路，如果已经求出来了 $x,x-1,\dots,x-t+1$ 这些位置的数，现在要求 $p_{x-t}$。然后我们二分了一个 $k(k\ge 2)$，我们可以找到 $x-t$ 后面第一个小于 $m$ 的位置 $x-s$，这个位置一定存在因为 $p_x<k$，由此我们知道 $\lfloor p_{x-s}/k\rfloor=0$，接着我们需要判断的是是否有 $\lfloor p_{x-t}/k\rfloor=0$，而我们知道 $\forall x-t<i<x-s,\lfloor p_i/k\rfloor\ne 0$，所以我们就可以查询 $[x-t,x-s-1]$ 和 $[x-t,x-s]$ 两个区间进行比较得到 $p_{x-t}$ 与 $k$ 的相对大小。这样我们可以通过 $\lceil 2\log_2n\rceil$ 次操作找到一个与 $x$ 不相邻的位置的值，而相邻的可以 $\lceil\log_2n\rceil$ 确定。

综上，我们便可以 $\lceil2n\log_2n\rceil$ 次操作找到整个数组，当然这个可以卡得更紧，因为所有数字互不相同二分的时候可以操作，不过没有必要了。



---

## 作者：FLAMEs_ (赞：2)

做了半天的交互题，感觉做完之后整个人升华了。

前言：这类题目似乎需要很好的“和出题人对上脑电波”，不然什么也想不到。而且，遇到这类向下取整相关的题目时，应当考虑 $k = 2$ 或者 $k = n$ 的情况，从这种特殊情况为突破口去思考题目。

以下用 $Q(l,r,k)$ 表示向交互库发起一组形如 ```? l r k``` 的询问。

## G1 做法

**我们能从交互操作中得到什么信息？**

发现 $k = 1,3\sim n - 1$ 时没有什么优异的性质。同时，我们发现：

- $k = n$ 时，除了 $\lfloor\frac{n}{k}\rfloor$ 的值为 $1$ 以外，其他所有的值均为 $0$。

- $k = 2$ 时，$1$ 对应的值为 $0$，只出现一次。当 $n$ 为奇数时，剩下的值每个都出现两次；当 $n$ 为偶数时，$n$ 对应的 $\lfloor\frac{n}{2}\rfloor$ 也只出现了一次。



$k = 2$ 时，可以考虑变换交互库给出的贡献：

令 $x=Q(l,r,2)$，则区间中**仅出现一次**的值的个数为 $2\times x-(r-l+1)$。

与前文中提到的 $k = 2$ 的性质相对应。

由此可以得出如下做法：

- 当 $n$ 为奇数时，考虑对于一个位置 $p$，有：
当 $l=Q(1,p,2),r=Q(p+1,n,2)$ 时，$|r-l|=1$。

对应的含义即为 $1$ 在左边还是在右边。此时直接进行二分，二分 $p$ 的位置即可，只需要 $2\log n=20$ 次即可完成。

- 当 $n$ 为偶数时，考虑对于一个位置 $p$，有：当 $l=Q(1,p,2),r=Q(p+1,n,2)$ 时，$l=r$ 或 $|r-l|=2$。

当 $l=r$ 时，我们发现，这种情况是由于不确定 $1$ 和 $n$ 的相对位置导致的。因此，我们可以在寻找答案前先用 $\log n$ 次找到 $n$ 所在的位置，具体每次只需要查询 $Q(1,p,n)$ 即可。知道 $n$ 的位置之后，$1$ 的位置自然在另一侧，可以继续二分；

当 $|r-l|=2$ 时，与 $|r-l|=1$ 一类情况相同，可以直接二分。

次数为 $2\log n +\log n=3\log n = 30$，足以通过 G1。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, L, R, Ans, Npos;
int Ask(int L, int R, int p) {
	cout << "? " << L << " " << R << " " << p << endl;
	int x; cin >> x; return x;
}
int main() {
	cin >> n;
	if(n & 1) {
		L = 1, R = n;
		while(L <= R) {
			int mid = (L + R) >> 1;
			if(mid == n) {
				Ans = n;
				break;
			}
			int Lval = Ask(1, mid, 2); Lval = 2 * Lval - mid;
			int Rval = Ask(mid + 1, n, 2); Rval = 2 * Rval - (n - mid);
			if(Lval < Rval) L = mid + 1;
			else R = mid - 1, Ans = mid;
		}
		cout << "! " << Ans;
		return 0;
	}
	L = 1, R = n;
	while(L <= R) {
		int mid = (L + R) >> 1;
		if(mid == 1) {
			Npos = 1;
			break;
		}
		if(mid == n) {
			Npos = n;
			break;
		}
		int Lval = Ask(1, mid, n);
		if(Lval == 1) L = mid + 1;
		else R = mid - 1, Npos = mid;
	}
	L = 1, R = n;
	while(L <= R) {
		int mid = (L + R) >> 1;
		if(mid == n) {
			Ans = n;
			break;
		}
		int Lval = Ask(1, mid, 2); Lval = 2 * Lval - mid;
		int Rval = Ask(mid + 1, n, 2); Rval = 2 * Rval - (n - mid);
		if(Lval == Rval + 2) R = mid - 1, Ans = mid;
		else if(Lval + 2 == Rval) L = mid + 1;
		else {
			if(Npos <= mid) L = mid + 1;
			else R = mid - 1, Ans = mid;
		}
	}
	cout << "! " << Ans;
	return 0;
}
```

[戳我看 G2 题解](https://www.luogu.com.cn/blog/gggggggghost/CF1764G2)

---

## 作者：Dream_poetry (赞：1)

### 思路：
首先令 $k = 2$，然后如果 $n$ 是奇数，显然此时只有 $1$ 自己一个人一组。

显而易见的，我们可以对于每个位置 $i$，查询 $[1, i − 1]$ 和 $[1, i]$ 的答案，如果答案一样，那这个位置肯定不是 $1$。

如果不一样，我们再查一下 $[i, n]$ 和 $[i + 1, n]$。由于 $1$ 不会和左右任意一个人配对，不难发现如果这两种情况都不一样，那这里一定是 $1$，这样我们就做到了 $2n − 2$ 次查询。

#### 进行优化。

如果我们查询一个区间 $[l, r]$，那么得到的答案自然是 $len-$ 配对数字都在区间内的对数，因此我们自然也能得到这个区间的未配对数。

这个时候发现，对于第 $i$ 个位置，如果我们查询 $[1, i]$ 和 $[i + 1, n]$，由于这两个区间内没配对的数字要么是 $1$，要么会和另一个区间中的数字配对，因此这两个区间中，未配对数多的那个一定包含 $1$。

这样就可以通过 $k$ 不断向下二分，最后只需要 $20$ 步操作就可以解决 $n$ 是奇数的情况。

太棒了，所以然后呢？


#### 再考虑 $n$ 是偶数的情况。

这个时候 $1$ 和 $n$ 都没人配对，我们需要找到 $n$ 并将它去掉。

注意到 $k$ 可以取别的数，我们如果只是让 $k = 2$ 未免有些弱，而且看上去也区分不了 $1$ 和 $n$，而不难发现，令 $k = n$ 就可以找到 $n$ 在哪里，于是可以先找 $n$ 再找 $1$，需要 $40$ 步。

显然无法接受。

#### 再优化。

令 $k = 2$，查询 $[1, i]$ 和 $[i + 1, n]$，发现此时会有两种情况: 

1. 左右两边未配对数量相差 $2$，这个时候 $1$ 和 $n$ 一定都在较大的那边，直接递归处理。

2. 左右两边未配对数量相等，这个时候一定 $1$ 在一边，$n$ 在另一边，可以通过查询 $k = n$ 判断哪边是 n。

所以只需要 $21$ 次，好耶。

这样我们就可以通过此题了，同时也可以通过 G2，但是要解决 G3 还需要一些神奇的优化，这里就不赘述了。

---

## 作者：樱雪喵 (赞：1)

## G1

考虑 $1$ 和其他的数有什么不同点。我们令询问的 $k=2$，那么只有 $1$ 的值是 $0$，其余都不是。这看起来并没有什么用，因为我们只能知道不同的数的个数。

但是真的没有用吗？可以发现，若 $k=2$，则所有数下取整后是两两配对的，$\lfloor\frac{2}{2}\rfloor=\lfloor\frac{3}{2}\rfloor,\lfloor\frac{4}{2}\rfloor=\lfloor\frac{5}{2}\rfloor,\dots$。当 $n$ 为奇数时，只有 $1$ 是单出来的；$n$ 为偶数时，$1$ 和 $n$ 两个数都是单出来的。

先考虑奇数的情况怎么做。

对于一个区间 $[l,r]$，若 $\text{query}(l,r,2)=x$，可以得到 $[l,r]$ 中有 $2x-(r-l+1)$ 个数字没有被配对。所以假设我们找了一个分界点 $mid$，并求出 $[1,mid]$ 中有 $L$ 个没配对，$[mid+1,n]$ 中有 $R$ 个没配对。那么如果同一组的数分到了一边一个，它们可以互相消掉，只有 $1$ 是无论如何都无法被配对的。

这就是说，若 $L<R$，$1$ 就在 $[mid+1,n]$ 中；否则 $1$ 在 $[1,mid]$ 中。那么我们可以二分这个 $mid$ 的位置，求出答案，询问次数 $2\log n\le 20$。

再考虑 $n$ 是偶数的情况。

现在，我们同样询问得到了 $L$ 和 $R$ 的值。分类讨论 $1$ 和 $n$ 的位置情况：

- 如果都在左侧，应该是 $L=R+2$；
- 如果都在右侧，应该是 $R=L+2$；
- 如果一左一右，$L=R$。

发现在一左一右的情况下，我们没法判断哪一边是 $1$。

但仔细思考一下，发现 $n$ 的位置是好找的：令 $k=n$，这样只有 $n$ 的答案是 $1$，其他都是 $0$。因此可以在一开始先二分找出 $n$ 的位置，就能知道 $L=R$ 时 $1$ 在哪边了。

找 $n$ 的位置只需要询问一边，所以总询问次数是 $3\log n\le 30$。

---

## 作者：Iam1789 (赞：1)

一文三投，赢！

完整文章：[Link](https://www.luogu.com.cn/blog/Iam1789/solution-cf1764g)
## 正文
先考虑 $n$ 为奇数，考虑 $k=2$ 时，按 $\lfloor \frac{a}{k} \rfloor$ 的值将 $1$ 到 $n$ 分组，则有大漂亮性质：$1$ 所在的组大小为 $1$，其它组大小皆为 $2$。

考虑判断 $1$ 的位置 $y$ 是否 $\leq \text{mid}$。对于所有大小为 $2$ 的组，设其两个元素的位置全 $\leq \text{mid}$ 的有 $x$ 对，全 $> \text{mid}$ 的有 $y$ 对，剩下的有 $z$ 对。询问 $(1,\text{mid},2)$ 和 $(\text{mid}+1,r,2)$，设结果分别为 $b,c$，有如下方程组：

$$ \begin{cases}  x+y+z=\lfloor\frac{n}{2} \rfloor+1\ \\x+z=b \\ y+z=c\end{cases}$$

方程组足以解出 $x,y,z$。

$a_1,\cdots,a_{\text{mid}}$ 中有 $2x+z$ 个不为 $1$ 的元素，如果 $2x+z=\text{mid}$，则 $1$ 的位置 $>\text{mid}$，否则 $\leq \text{mid}$。

考虑二分 $\text{mid}$，最劣询问次数为 $2\lceil\log n\rceil$。

接着考虑 $n$ 为偶数。与 $n$ 为奇数不同的是，除了 $1$ 之外，$n$ 所在的组大小为 $1$。因此在判断的时候，可能同时出现 $2x+z\neq \text{mid}$ 和 $2y+z \neq n-\text{mid}$ 的情况。此时 $1$ 与 $n$ 分别在 $\text{mid}$ 的两边。如何判断哪边是 $n$ 呢？如果 $\text{mid} >1$，我们询问 $(1,\text{mid},n)$，否则询问 $(\text{mid}+1,n,n)$。如果结果为 $2$，则说明 $n$ 在对应区域，将其排除。最劣情况下询问次数为 $3\lceil\log n\rceil$，当 $n=1024$ 时为 $30$ 次，可以通过第一个子任务。


---

## 作者：honglan0301 (赞：1)

[-> CF官方题解](https://codeforces.com/blog/entry/109468)
## 题意简述
交互题。有一个排列 $p_1,...,p_n$, 你需要在 $30$ 次以内的询问后找出 $1$ 的位置。每一次询问输出 $?\ l\ r\ k$, 表示询问 $\lfloor {p_l\over k} \rfloor,...,\lfloor {p_{r}\over k} \rfloor$ 中有多少个不同的数。

## 题目分析
首先发现 $k=1$ 的询问是一点用都没有的，不用考虑。而 $k\geq2$ 时，$\lfloor {1\over k}\rfloor$ 总是 $0$, 为了让 $1$ 与其它数区分开，我们考虑进行 $k=2$ 的询问，因为这样能让其它数除以 $k$ 下取整后不为 $0$。

当 $n$ 为奇数时，除了 $1$ 以外的所有数除以 $2$ 下取整后总是两两配对。因此当我们把 $p$ 分成两段分别询问时，两段中除 $1$ 以外的未配对数的数量总是相等，所以 $1$ 就应该在未配对数较多的一段中。采用二分的方法，最多询问 $2\times\log(1024)=20$ 次，满足本题要求（甚至满足了 G3 的要求）。

而当 $n$ 为偶数时，有 $1$ 与 $n$ 两个数没有配对，因此当询问的两段中未配对数相等时就很不好处理。但我们发现 $n$ 有个更特殊的性质，只有 $\lfloor {n\over n} \rfloor$ 为 $1$, 因此只需要在这时进行一次 $k=n$ 的询问就能找到 $1$ 的位置了。同样用二分，最多询问 $3\times\log(1024)=30$ 次，满足本题要求。

在 $k=n$ 的询问里，要注意不能询问长度为 $1$ 的一段，否则起不到判断的作用，记得特判。  

进一步的优化请看 G2 和 G3 的题解。

## 代码
```cpp
#include <iostream>
#include <ctime>
#include <cstdio>
#include <cmath>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
#include <map>
#include <stdlib.h>
using namespace std;
int n;
inline int read()
{
	int now=0,nev=1; char c=getchar();
	while(c<'0' || c>'9') { if(c=='-') nev=-1; c=getchar();}
	while(c>='0' && c<='9') { now=(now<<1)+(now<<3)+(c&15); c=getchar(); }
	return now*nev;
}
int ask(int l,int r,int k)
{
	printf("? %d %d %d\n",l,r,k);
	fflush(stdout);
	return read();
}
void putans(int x)
{
	printf("! %d\n",x);
	fflush(stdout);
}
bool check1(int x)
{
	int a=ask(1,x,2);
	int b=0;
	if(x+1<=n)
	{
		b=ask(x+1,n,2);
	}
	int c=x-2*(x-a);
	int d=(n-x)-2*((n-x)-b);
	if(c>d)
	{
		return 1;
	}
	return 0;
}
void solve1()//n为奇数 
{
	int l=1,r=n;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(check1(mid))
		{
			r=mid;
		}
		else
		{
			l=mid+1;
		}
	}
	putans(l);
}
bool check2(int x)
{
	int a=ask(1,x,2);
	int b=0;
	if(x+1<=n)
	{
		b=ask(x+1,n,2);
	}
	int c=x-2*(x-a);
	int d=(n-x)-2*((n-x)-b);
	if(c>d)
	{
		return 1;
	}
	else if(c<d)
	{
		return 0;
	}
	else//两段未配对的数数量相等 
	{
		int e=0;
		if(x>1)//放在出现ask(1,1,n)的无效情况 
		{
			e=ask(1,x,n);
		}
		else
		{
			e=3-ask(x+1,n,n);
		}
		if(e==2)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
}
void solve2()//n为偶数 
{
	int l=1,r=n;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(check2(mid))
		{
			r=mid;
		}
		else
		{
			l=mid+1;
		}
	}
	putans(l);
}
int main()
{
	n=read();
	if(n%2==1)
	{
		solve1();
	}
	else
	{
		solve2();
	}
}
```

---

## 作者：OoXiao_QioO (赞：0)

在下文，我们令“两个数配对”表示这两个数相等。不直接用“两个数相等”是因为可能有歧义，需要读者自己注意。

不难发现这个下取整对于 $n$ 的奇偶性有影响，所以我们要分类讨论。

* 若 $n$ 是奇数

第一反应是令 $k=2$。此时只有 $1$ 自己是一组，其他连续两个数都是同一个值。

那么我们可以对于每个位置 $i$，查询 $[1,i-1]$ 和 $[1,i]$ 的答案。如果这两个区间答案一样，那么这个位置肯定不是 $1$；如果不一样，再查询 $[i,n]$ 和 $[i+1,n]$。因为 $1$ 不会和左右任意一个数配对，因此若这两种情况都不一样，那么这个位置肯定就是 $1$，此时询问次数就是 $2n-2$ 次。

考虑优化，若查询一个区间 $[l,r]$，那么答案数就是 $len-x$，其中 $x$ 是配对数字都在区间内的对数。所以我们也能得出这个区间的未配对数。

更进一步地，发现对于位置 $i$，如果查询 $[1,i]$ 和 $[i+1,n]$，由于这两个区间内未配对的数字要么是 $1$，要么会和另一个区间中的数字配对，因此这两个区间中未配对数多的那个区间一定包含 $1$。

这样就可以通过 $k$ 不断向下二分，最后只需要 $20$ 步操作就可以解决 $n$ 是奇数的情况。

* 若 $n$ 是偶数

此时 $1$ 和 $n$ 都没有点可以配对，那么我们需要找到 $n$ 并把他消除掉，那么找 $1$ 就变得简单了。

注意到 $k$ 可以取除了 $2$ 的数，通过手玩样例发现，令 $k=n$ 可以找到 $n$ 在那里，那么可以先找到 $n$ 再找 $1$，此时需要 $40$ 步。也就是找两次 $20$ 步。

可是若 $k$ 一直取 $n$，优化的前景不大，那么继续考虑 $k$ 的取值。

继续优化，还是令 $k=2$，查询 $[1,i]$ 和 $[i+1,n]$，我们发现此时有两种情况：

1. 左右两边未配对的数量相差 $2$，这时候 $1$ 和 $n$ 一定都在较大的那边，直接递归求解即可。

2. 左右两边未配对数量相等，此时肯定 $1$ 和 $n$ 各在一边，再查询一次 $k=n$，就知道了 $n$ 再哪里。

至于为什么有这两种情况请读着自己思考。



---



奇偶两种情况结合一下即可。

---

## 作者：OtoriEmu (赞：0)

因为自己思考的时候没有独立做出 G3，所以只写 G2 的题解。

事实上这场 E 浪费太多时间去考虑 corner case 了，能早点看到这题就可以上分了。

---

简单观察范围，G1 的范围是 $3\log n$ 次，G2 的范围是 $2\log n+1$ 次询问。

为什么非要我们找 $1$ 不可呢？事实上向下取整是一个很好的提示。一个直观的想法是每次查询，$k=2$。这个想法的来源在哪儿呢？首先 $k=1$ 的查询显然是浪费，同时发现 $k \geq 2$ 的时候 $\lfloor \frac{1}{k} \rfloor = 0$。如果 $\lfloor \frac{c}{k} \rfloor = 0$ 的 $c$ 可以唯一确定就很不错了，此时 $k=2$（不考虑采取 $k$ 更大的分治结构是因为如果为 $\lfloor \frac{c}{k} \rfloor = 0$ 太多，区分他们的成本太大，并且我们仍然需要 $k$ 更小的询问）。

此时可以按 $\lfloor \frac{c}{2} \rfloor$ 分类。容易发现一类的大小要么是 $2$ 要么是 $1$，并且类与类的区别只有大小的区别，我们只需要找到大小为 $1$ 的那类的位置。这里有一个对 G1 来说无关紧要的问题是，大小为 $1$ 的可能有两类（$0$ 和 $\frac{n}{2}$，此时 $n$ 为偶数）。对于 G1 来说可以先令 $k=n$，通过二分找到 $n$ 的位置并排除。

对于 G1 还剩下 $2 \log n$ 次询问。这是显然的一个二分的结构，每层二分查询两次。假设我们确定 $1$ 在区间 $[l,r]$ 内，对于中点 $p$，将序列分成大小为 $p$ 和 $n-p$ 的两段。在去除 $n$ 之后查询左右两边还没有配对的数的数量（当然这并不是查询的实际意义，当然算是比较简单的，令 $c$ 的值为 `query(l,r,2)` 的结果，则没配对的数的数量为 $2c-r+l-1$）。因为 $1$ 必然无法配对，所以没有配对的数更多的一半存在 $1$。这部分的查询次数为 $2 \log n$。

因为没有 $3 \log n$ 次询问的代码，可以先自己思考得到 G2 的方法，或者移步 [G2 的题解](https://www.luogu.com.cn/blog/340163/solution-cf1764g2)。

---

