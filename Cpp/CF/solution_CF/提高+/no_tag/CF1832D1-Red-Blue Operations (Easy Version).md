# Red-Blue Operations (Easy Version)

## 题目描述

The only difference between easy and hard versions is the maximum values of $ n $ and $ q $ .

You are given an array, consisting of $ n $ integers. Initially, all elements are red.

You can apply the following operation to the array multiple times. During the $ i $ -th operation, you select an element of the array; then:

- if the element is red, it increases by $ i $ and becomes blue;
- if the element is blue, it decreases by $ i $ and becomes red.

The operations are numbered from $ 1 $ , i. e. during the first operation some element is changed by $ 1 $ and so on.

You are asked $ q $ queries of the following form:

- given an integer $ k $ , what can the largest minimum in the array be if you apply exactly $ k $ operations to it?

Note that the operations don't affect the array between queries, all queries are asked on the initial array $ a $ .

## 样例 #1

### 输入

```
4 10
5 2 8 4
1 2 3 4 5 6 7 8 9 10```

### 输出

```
3 4 5 6 7 8 8 10 8 12```

## 样例 #2

### 输入

```
5 10
5 2 8 4 4
1 2 3 4 5 6 7 8 9 10```

### 输出

```
3 4 5 6 7 8 9 8 11 8```

## 样例 #3

### 输入

```
2 5
2 3
10 6 8 1 3```

### 输出

```
10 7 8 3 3```

# 题解

## 作者：sunkuangzheng (赞：13)

注：本文极大程度上参考官方题解。

我们分下列几种情况，由易到难地解决这道题目。

- $k \le n$ 时：

这种情况最为简单。因为操作次数极少，最优策略一定是让每一个数字都增加，且只操作一次。有一个误区是，大家可能会认为把所有的操作都放在数字最小值上面最优，但其实不然，以 $\{1,114514,1919810\}$ 为例，如果将所有操作都放在 $1$ 上，答案为 $3$。

$\{1\color{red}{+1}\color{blue}{-2}\color{red}+3\color{black},114514,1919810\}$

但如果这样操作，答案为 $4$。

$\{1\color{red}+3\color{black},114514\color{red}+2\color{black},1919810\color{red}+1\color{black}\}$

因此我们发现，最优解**一定**是从小到大地给原数组 $+k,k-1,...,2,1$。至此该部分结束。

- $k > n$ 时

$k > n$ 时，我们先总体分析思路。首先显而易见的是，**一定不可能有 $2$ 个以上的数字减小。** 因为如果有 $2$ 个以上的数字同时减小，我们可以把一个减操作移到另一个减小的位置上，使之成为加操作。这样这两个数字就会同时变大。

继续思考。首先我们可以将多次操作视为一个整体，例如先 $+x$，再 $-(x+1)$，以此类推，我们发现 $2x$ 次**连续**操作后某一位上的数字会恰好减小 $x$。既然无论如何都要减少，很明显减少的操作放得越靠前越优。因为这样会将加数较小的$1,2$ 之类的消掉，而留下加数较大的 $k-1,k$ 等。由此我们也可以得出，一个数字要想增加，需要奇数次操作。


下面我们继续分类。

1. $k \equiv n \pmod 2$ 时。

由 $k \equiv n \pmod 2$ 我们能得到什么？

答案：我们一定可以使每一个数字都增加，且这样一定是最优情况。

因为 $k$ 与 $n$ 关于 $2$ 同余，我们一定可以让每一个数字都进行奇数次操作。

2. $k \bmod 2 \ne n \bmod 2$ 时。

此时正好与上面的情况相反，一定会有一个数字不能增加，只能减小。

那么怎么求最后的值呢？在我们给每个数字增加完成后，剩余的操作只会让最小值变小。首先我们一定要先让原数组所有值变得一样，这样这段时间内最小值不变。设操作完（$+k,+k-1...$）的数组为 $a$，设 $s = \sum\limits^n_{i=1}a_i-mn$，其中 $mn = \min\limits^n_{i=1}a_i$。这样将 $s$ 减到 $0$ 的操作不会影响最小值，而剩余的操作次数是：$\dfrac{k-(n-(n+k) \bmod2) - s}{2}$。显而易见地，$(n+k) \bmod 2 = 0$ 等价于  $k \equiv n \pmod 2$。剩余的操作均摊到 $n$ 个数字的身上，最后的，剩余操作对答案的影响为 $\lceil\dfrac{\max(0,\dfrac{k-(n-(n+k) \bmod2) - s}{2})}{n}\rceil$。

对于 $\text{Easy version}$，我们使用 $O(q\cdot n \log n)$ 的算法如下：

先对原来的数组排序，然后特判 $k \le n$ 的情况。然后我们按照上面的思路，先对原数组进行增加操作，排序后算出每个数字与最小值的差，然后直接利用公式进行计算。

**【代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t,n,a[5005],tmp[5005],k,m;
signed main(){
	cin >> n >> m;
    for(int i = 1;i <= n;i ++) cin >> tmp[i];
	while(m --){
		for(int i = 1;i <= n;i ++) a[i] = tmp[i];
		cin >> k;
		int sum = 0;
		sort(a+1,a+n+1);
		if(k <= n){
			for(int i = 1;i <= k;i ++) a[i] += k - i + 1;
			sort(a+1,a+n+1);
			cout << a[1] << " "; 
			continue;
		}
		for(int i = 1;i <= n-1;i ++) a[i] += k - i + 1;
		if((n+k) % 2 == 0) a[n] += k - n + 1;
		sort(a+1,a+n+1);
		for(int i = 2;i <= n;i ++) sum += a[i] - a[1];
		double nn = n,kk = k;
		double f = max(0.0,(k - n + (n+k) % 2) * 0.5 - sum)/n;
		int x = ceil(f);
		cout << a[1] - x << " ";
	}
	return 0;
}
```

**【拓展】**

计算过程中，我们发现大量过程是重复的。因此考虑优化。具体请见 CF1832D2。

---

