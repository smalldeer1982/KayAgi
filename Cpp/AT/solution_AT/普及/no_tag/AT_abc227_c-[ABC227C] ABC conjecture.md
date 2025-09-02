# [ABC227C] ABC conjecture

## 题目描述

给出正整数 $ N $。

求 $ A\leq\ B\leq\ C $ 并且 $ ABC\leq\ N $ 的正整数对 $ (A,B,C) $ 的个数。

注意，在限制的条件下，保证答案小于 $ 2^{63}$。

## 说明/提示

条件

- $ 1\ \leq\ N\ \leq\ 10^{11} $
- $ N $是整数

样例解释 $1$：

满足条件的组有 $5$ 组：$(1,1,1),(1,1,2),(1,1,3),(1,1,4),(1,2,2)$。

## 样例 #1

### 输入

```
4```

### 输出

```
5```

## 样例 #2

### 输入

```
100```

### 输出

```
323```

## 样例 #3

### 输入

```
100000000000```

### 输出

```
5745290566750```

# 题解

## 作者：loser_seele (赞：3)

题意：求满足 $ A \leq B \leq C $ 且 $ A \times B \times C \leq N $ 的数对 $ (A,B,C) $ 的数量，$ N \leq 10^{11} $。

实际上这题是一个暴力枚举题。

首先因为 $ A \leq B $，所以 $ A \leq \sqrt{N} $，直接暴力枚举 $ A $ 到 $ \sqrt{N} $，然后再考虑 $ B $。

因为 $ A $ 已经确定，且 $ B \leq C $，所以 $ B $ 只需要在区间 $ [A,\sqrt{\frac{N}{A}}] $ 中枚举即可，那么满足条件的 $ C $ 的个数显然为 $ \frac{N}{A \times B}-B+1 $，然后直接累加答案即可。

这么做即可通过本题，但其精确时间复杂度其实并不好算。

于是考虑输出循环次数，发现当 $ N $ 较大时循环次数大约在 $ \mathcal{O}(N^{\frac{2}{3}}) $ 的数量级，于是时间复杂度为 $ \mathcal{O}(N^{\frac{2}{3}}) $，可以通过。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main()
{
	int n,ans=0;
	cin>>n;
	for(register int a1=1;a1<=sqrt(n);a1++)
	for(register int a2=a1;a2<=sqrt(n/a1);a2++)
	ans+=n/a1/a2-a2+1;
	cout<<ans;
}
```


---

