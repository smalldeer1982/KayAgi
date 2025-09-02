# [AGC032A] Limited Insertion

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc032/tasks/agc032_a

すぬけ君は空の数列 $ a $ を持っています。

すぬけ君は $ a $ に対して $ N $ 回操作を行います。

$ i $ 回目の操作では $ 1\ \leq\ j\ \leq\ i $ を満たす整数 $ j $ を選び、$ a $ の先頭から $ j $ 番目に $ j $ を挿入することができます。

長さ $ N $ の数列 $ b $ が与えられます。$ N $ 回の操作後に $ a $ が $ b $ と一致することがあるかどうかを判定し、可能ならばそれを達成する操作手順の一例を示してください。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 1\ \leq\ N\ \leq\ 100 $
- $ 1\ \leq\ b_i\ \leq\ N $

### Sample Explanation 1

\- 各操作後、$ a $ は以下のように変化します。 - $ 1 $ 回目の操作後:$ (1) $ - $ 2 $ 回目の操作後:$ (1,1) $ - $ 3 $ 回目の操作後:$ (1,2,1) $

### Sample Explanation 2

\- 数列の先頭に $ 2 $ を挿入することはできないため、達成不可能です。

## 样例 #1

### 输入

```
3
1 2 1```

### 输出

```
1
1
2```

## 样例 #2

### 输入

```
2
2 2```

### 输出

```
-1```

## 样例 #3

### 输入

```
9
1 1 1 2 2 1 2 3 2```

### 输出

```
1
2
2
3
1
2
2
1
1```

# 题解

## 作者：火车司机 (赞：3)

## 简要分析

大小为 $x$ 一定会放在位置 $x$ 上，所以我们可以考虑倒推整个过程

每次从后往前找到第一个满足 $a[x]==x$ 的，将其存到答案中，然后暴力将其后面的所有往前一位

因为是从后往前找到的第一个，所以必然不会影响到之后的答案

如果找不到符合条件的数，那么就输出无解

因为整个过程是倒推的，所以最后答案也要反过来输出

时间复杂度为 $O(n^2)$

## 完整代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define ri register int
#define N 105
using namespace std;
int n, a[N], ans[N];
template <typename T>
inline void read(T &x)
{
	register T f = 0, c = getchar();
	for (; c < 48 || 57 < c; c = getchar())
		if (c == '-')
			f = 1;
	for (x = 0; 48 <= c && c <= 57; c = getchar())
		x = (x << 3) + (x << 1) + (c & 15);
	if (f)
		x = ~(--x);
}
template <typename T>
inline void print(T x)
{
	if (x < 0)
		putchar('-'), x = ~(--x);
	if (x > 9)
		print(x / 10);
	putchar(x % 10 | 48);
}
signed main()
{
	read(n);
	for (ri i = 1; i <= n; ++i)
		read(a[i]);
	for (ri i = n, f; i; --i)
	{
		f = 1;
		for (ri j = i; j && f; --j)
			if (a[j] == j)
				ans[i] = j, f = 0;
		if (f)
		{
			puts("-1");
			return 0;
		}
		for (ri j = ans[i]; j < i; ++j)
			a[j] = a[j + 1];
	}
	for (ri i = 1; i <= n; ++i)
		print(ans[i]), puts("");
	return 0;
}
```


---

## 作者：约瑟夫用脑玩 (赞：3)

可以给 $n$ 多加四个 0 现场。

## 题意

初始有一个空序列，对它进行 $n$ 次操作，第 $i$ 次在满足 $1\le j\le i$ 的位置 $j$ 处插入一个数 $j$ ，求一种方案使最后的序列为给定的序列 $b$。

$1\le b_i\le n\le100$

## 题解

我们发现插入一个数只会把其他数往后顶，而不会往前走，于是先判断是否有数比它位置还大，有的话一定无解，即 $b_i>i$。

那么现在 $\forall i,b_i\le i$，如果找不到 $b_i=i$ 显然无解，因为最后一个插入的一定有 $b_x=x$。

如果说 $b_i=i$，那么一定是刚好插在这里，我们倒序考虑，选大的 $b_x=x$ 倒着插入，并把它从 $b$ 中删除。

如果选了一个 $b_y=y<b_x=x$ 倒着插，那么 $b_x\to b_{x-1}=x>x-1$ 无解，我们这么做方案一定唯一。

暴力模拟上述过程 $O(n^2)$，显然一点都不优雅，考虑时刻维护 $b_i-i$ 的最小值。

我们要做的就是每次找到并删除最后一个 0，并把后缀减 1，可以用线段树上二分实现，$O(n\log{n})$。

我比较离谱，用的是 ZKW线段树，其实和线段树没啥区别，[代码](https://www.luogu.com.cn/paste/fnrmboje)。

---

## 作者：o51gHaboTei1 (赞：1)

#### A

随便做。考虑倒着做。

显然我们贪心地构造一个点的势能是距离它被删的位置的距离，我们每次从后往前扫，每次找到第一个合法的位置直接删，找不到输出无解即可。

从后往前找到第一个数，对于还在它后面但当前态不合法的节点的势能一定不为 $0$，所以让它们减小是最好的，而如果一次删除可能会使得许多不合法节点的势能为 $0$，从大往小删也让他们之间内部不影响；而对于找到数前面的数删它不影响前面数的势能，所以这样贪心是对的。


```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 1e2 + 5;
int n,b[Len];
int main()
{
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i ++) scanf("%d",&b[i]);
	int len = n;vector<int> psy;
	while(len)
	{
		int pos = -1;
		for(int i = 1 ; i <= len ; i ++) if(b[i] == i) pos = i;
		if(pos == -1)
		{
			puts("-1");
			exit(0);
		}
		psy.push_back(pos);
		for(int i = pos ; i < len ; i ++) b[i] = b[i + 1];
		len --; 
	}
	reverse(psy.begin() , psy.end());
	for(int i = 0 ; i < psy.size() ; i ++) printf("%d\n",psy[i]);
	return 0;
}
```


---

