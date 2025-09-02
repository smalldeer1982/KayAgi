# Light Bulbs (Easy Version)

## 题目描述

The easy and hard versions of this problem differ only in the constraints on $ n $ . In the easy version, the sum of values of $ n^2 $ over all test cases does not exceed $ 10^6 $ . Furthermore, $ n $ does not exceed $ 1000 $ in each test case.

There are $ 2n $ light bulbs arranged in a row. Each light bulb has a color from $ 1 $ to $ n $ (exactly two light bulbs for each color).

Initially, all light bulbs are turned off. You choose a set of light bulbs $ S $ that you initially turn on. After that, you can perform the following operations in any order any number of times:

- choose two light bulbs $ i $ and $ j $ of the same color, exactly one of which is on, and turn on the second one;
- choose three light bulbs $ i, j, k $ , such that both light bulbs $ i $ and $ k $ are on and have the same color, and the light bulb $ j $ is between them ( $ i < j < k $ ), and turn on the light bulb $ j $ .

You want to choose a set of light bulbs $ S $ that you initially turn on in such a way that by performing the described operations, you can ensure that all light bulbs are turned on.

Calculate two numbers:

- the minimum size of the set $ S $ that you initially turn on;
- the number of sets $ S $ of minimum size (taken modulo $ 998244353 $ ).

## 样例 #1

### 输入

```
4
2
2 2 1 1
2
1 2 2 1
2
1 2 1 2
5
3 4 4 5 3 1 1 5 2 2```

### 输出

```
2 4
1 2
1 4
2 8```

# 题解

## 作者：Eibon (赞：3)

对样例进行分析，不难发现，可以将区间分成一块块，每一块由一些相交的相同数字对构成。

当两个数字对区间包含时，小的区间显然不必要点亮。

否则当它们相交时，点亮其中任何一个即可，相当于将整个块点亮。

即，最后块的数量即为第一个答案。

判断一个数是否出现偶数次，可以使用异或哈希。

考虑如何统计答案二。

不妨开一个 map，记录最后一个某哈希值 $cur_{i}$ 出现的位置 $lst_{cur_{i}}$。

对每一个前缀异或哈希和为 $0$，即块的端点 $i$，我们从它的下一个点 $i+1$ 即 $j$ 开始跳，每次跳到 $lst_{cur_{j}}+1$，即下一个区间相交的位置，跳到 $cur_{j}$ 为 $0$ 即块的另一个端点停止。可以避免算到中间异或和为 $0$ 的块，因为中间跳得到的 $cur_{j}$ 都不等于 $0$。

这样，我们把每一个闭区间的贡献乘一起，就可以得到第二问的答案。


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=4e5+5;
const int mod=998244353;
int T=1,n,ans1,ans2;
int w[maxn],cur[maxn];
map<int,int>lst;
mt19937_64 rnd(random_device{}());
int get()
{
	int x=0;
	while(!x){
		x=rnd();
	}
	return x;
}
int Add(int x,int y){return ((x+y)%mod+mod)%mod;}
int Mul(int x,int y){return x*y%mod;}
void solve()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		w[i]=get();
	}
	lst.clear();
	ans1=0;ans2=1;
	for(int i=1;i<=2*n;i++){
		int x;
		scanf("%lld",&x);
		cur[i]=cur[i-1]^w[x];
		lst[cur[i]]=i;
		if(!cur[i]){
			ans1++;
		}
	}
	for(int i=0;i<2*n;i++){
		if(cur[i]){
			continue;
		}
		int j=i+1,res=1;
		while(cur[j]){
			j=lst[cur[j]]+1;
			res++;
		}
		ans2=Mul(ans2,res);
	}
	printf("%lld %lld\n",ans1,ans2);
}
signed main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	scanf("%lld",&T);
	while(T--){
		solve();
	}
	return 0;
}
//dyyyyds
```

---

## 作者：Erica_N_Contina (赞：2)

## 思路

需要注意的点：对于序列 `1 2 3 2 1 3` 只需要 $1$ 次操作。我们点亮一个 $1$，那么其会将两个 $1$ 里面的 `2 3 2` 都点亮。点亮了 $3$ 就代表着最右边的 $3$ 也被点亮了。

---

我们考虑一种特殊的序列，其满足序列中的每个数字的个数都是偶数。我们称之为**偶数序列**。如果一个偶数序列不能拆分成多个子偶数序列，那么我们称这个偶数序列为**最小偶数序列**。

那么最小偶数序列的性质是什么呢？

我们发现，一个最小偶数序列中只需要点亮一盏灯就可以让其他灯点亮。这个很好证明，发现无法举出反例，特别是很多反例无法满足**最小**。

可是一个最小偶数序列中的那个被点亮的灯也不是随便选的，它要满足一定的限制。

考虑以下定义：我们在上面定义的最小偶数序列仅仅是在“并列”层面进行了限制，但是没有在“嵌套”层面做出限制。事实上，一个最小偶数序列中可能包含另一个最小偶数序列（`1 2 2 1` 就是一个很好的例证）。所以我们在划分序列时，我们会吧 `1 2 2 1` 看出是一个最小偶数序列。但我们很显然可以发现中间的两个 $2$ 是不可能成为被点亮的灯的。

我们将序列划分后产生的最小偶数序列中，对于每个最小偶数序列，如果其内还包含了又一个或者多个最小偶数序列，那么我们将这些被包含的序列称为**最小偶数子序列**。那么结合上面的说明，我们在选择一个最小偶数序列中被点亮的那个灯时，不可以选择最小偶数子序列中的灯。

---

根据题目的要求，序列一定可以划分成若干个最小偶数序列，又因为不可能出现无解的情况，所以将序列划分为最小偶数序列的方法是最优的方法。

对于求最小可能的 $S$ 集合大小，我们只需要求出序列中有几个最小偶数序列即可。

对于求出情况数，我们可以使用乘法原理，但是要先剔除每个最小偶数序列中的最小偶数子序列中的灯。

## 实现

那么我们怎么样划分最小偶数序列呢？偶数的性质是什么呢？

对于简单版，我们全都暴力即可通过。

这里提一下困难版的做法：
我们可以想到，用 $res=0$ 异或偶数次的一个数字 $x$，结果还是 $0$。我们利用这个性质，对序列中的每一个数字的值分配一个独一无二的数字 $h_i$（即值相同，其 $h_i$ 也相同），从前往后扫描一遍即可。

对于剔除每个最小偶数序列中的最小偶数子序列中的灯，我们先抽离出每一个最小偶数序列。然后考虑对于一个最小偶数序列，我们从前往后按上面的方法扫描，并且记录一个桶。如果当前 $res$ 在桶中有值 $id$，那么 $id\sim i$（$i$ 是当前 $res$ 所在的位置）就是一个最小偶数子序列。

---

代码就不放了，和官方题解很像。



---

## 作者：huangrenheluogu (赞：1)

注：原文中是打开灯，翻译中是给数染色，本篇题解采用原文的说法。

取法显然是贪心的，求出每一个灯打开之后，最长能延伸到哪一盏灯，然后从后面继续选择。

选一盏，另一盏就会亮。接着，这个区间中的每一盏都会亮。接着，这个区间的每一盏都会让与其对应的亮起来，一直到没有办法传递。

显然，相对位置满足 `A B A B` 型的灯是等效的。只要我打开这 $4$ 盏灯的任意一盏，那么这 $4$ 盏灯就会全亮。

而等效是满足传递性的。比如 `B A B C A C`，`A` 和 `B` 等效；`B` 和 `C` 等效，那么打开这 $6$ 盏灯中的任意一盏，这 $6$ 盏灯都会亮。

注意，`A B B A` 不是等效的，因为打开 `B`，`A` 不会亮。

那么，只要两盏灯中间灯个数是奇数的互相等效。用并查集维护。

显然，等效是可以传到最右边的（感性理解，如果从 `A` 开始传，那么右边的 `A` 必然被包裹），所以原串被分成若干个等效的块。

方案总数就是从等效的块中任取一个即可。

代码容易实现，复杂度 $O(n^2)$。

[code](https://codeforces.com/contest/1914/submission/239079972)。

---

## 作者：Fubaogege (赞：1)

## 题目大意及题解
对集合 $S$ 进行初始染色，只需要遵循以下两条规则就行：

- 如果一个数被染色了，则另一个相同的数也会被染色。
- 如果某两个相同的数被染色了，那么它们之间所有数都会被染色。

求出：

- 你要求出最小可能的 $S$ 集合大小使得所有数都被染色，并且求出有多少 $S$ 满足其大小到达最小。
- 结果对 $998244353$ 取模。

简化：我们只需按题目要求求出 $S$ 就行。

- 你可以标注一些点，要求每个点都可以由被标记的点达到。
- 使用扩展排序。
- 对一个区间加边，优化建边。

完结撒花。

---

