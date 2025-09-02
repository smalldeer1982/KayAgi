# Cards Partition

## 题目描述

[DJ Genki vs Gram - Einherjar Joker](https://soundcloud.com/leon-hwang-368077289/einherjar-joker-dj-genki-vs-gram)

⠀



You have some cards. An integer between $ 1 $ and $ n $ is written on each card: specifically, for each $ i $ from $ 1 $ to $ n $ , you have $ a_i $ cards which have the number $ i $ written on them.

There is also a shop which contains unlimited cards of each type. You have $ k $ coins, so you can buy at most $ k $ new cards in total, and the cards you buy can contain any integer between $ \mathbf{1} $ and $ \mathbf{n} $ , inclusive.

After buying the new cards, you must partition all your cards into decks, according to the following rules:

- all the decks must have the same size;
- there are no pairs of cards with the same value in the same deck.

Find the maximum possible size of a deck after buying cards and partitioning them optimally.

## 说明/提示

In the first test case, you can buy one card with the number $ 1 $ , and your cards become $ [1, 1, 1, 1, 2, 2, 3, 3] $ . You can partition them into the decks $ [1, 2], [1, 2], [1, 3], [1, 3] $ : they all have size $ 2 $ , and they all contain distinct values. You can show that you cannot get a partition with decks of size greater than $ 2 $ , so the answer is $ 2 $ .

In the second test case, you can buy two cards with the number $ 1 $ and one card with the number $ 3 $ , and your cards become $ [1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 4, 4, 5, 5, 5, 5] $ , which can be partitioned into $ [1, 2, 3], [1, 2, 4], [1, 2, 5], [1, 2, 5], [2, 3, 5], [2, 4, 5] $ . You can show that you cannot get a partition with decks of size greater than $ 3 $ , so the answer is $ 3 $ .

## 样例 #1

### 输入

```
9
3 1
3 2 2
5 4
2 6 1 2 4
2 100
1410065408 10000000000
10 8
7 4 6 6 9 3 10 2 8 7
2 12
2 2
2 70
0 1
1 0
1
3 0
2 1 2
3 1
0 3 3```

### 输出

```
2
3
1
7
2
2
1
1
2```

# 题解

## 作者：Super_Cube (赞：7)

# Solution

题意：牌的类型为 $1\sim n$，现在已有 $a_i$ 张牌 $i$，且可以获得至多 $k$ 张任意牌。现在要将这些牌分为若干堆，要求每堆牌数量相等且每堆牌内不存在相同的牌，希望最大化牌堆大小。

记 $v=\max a_i$，$s=\sum a_i$。设最终牌堆大小为 $x$。

先考虑 $k=0$ 的情况，此时无任意牌。只有当 $x\mid s$ 且 $v\le\dfrac{s}{x}$ 时才能满足条件。原因？首先整除肯定是必要的，于是共有 $\dfrac{s}{x}$ 个牌堆，而同一牌堆中不能有相同牌，所以需要牌堆数不小于众数出现次数。

再来考虑原问题，也就是可以给 $s$ 加上一个 $[0,k]$ 的整数。套用上面的结论，得到 $x$ 符合要求的条件为 $\begin{cases}s+k\ge vx & s<vx\\(x-s\bmod x)\bmod x\le k & s\ge vx\end{cases}$，于是从大到小枚举 $x$ 逐一判断即可。

# Code
```cpp
#include<bits/stdc++.h>
int T,n;
long long m,a,v,s;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%lld",&n,&m);
		s=v=0;
		for(int i=1;i<=n;++i)
			scanf("%lld",&a),v=std::max(v,a),s+=a;
		for(int i=n;i;--i)
			if((s<v*i&&s+m>=v*i)||(s>=v*i&&(i-s%i)%i<=m))
				printf("%d\n",i),i=1;
	}
	return 0;
}
```

---

## 作者：chenxi2009 (赞：1)

## 思路
先要明确一点：有 $n$ 种卡牌，一组中不能有同类牌，所以答案，即牌组大小，最大为 $n$。$\sum n\le2\times10^5$，可以枚举。问题在于怎么检测一个牌组大小是否可行。

令 $x$ 为可能的牌组大小，首先牌的数量必须有可能整除 $x$，即 $[\sum a_i,\sum a_i+k]$ 中是否有 $x$ 的倍数，可以转换为 $\left\lfloor\frac{\sum a_i+k}{x}\right\rfloor\times x\ge\sum a_i$ 判断。其次在合法的前提下最大的牌组数量得大于 $\max a_i$，即 $\left\lfloor\frac{\sum a_i+k}{x}\right\rfloor\ge\max a_i$。可以证明满足上述条件时，一定有合法方案，具体构造方法：\
买卡之前先把所有的牌分成若干组，每组大小 $\le x$，不必均分，要求不重；然后通过买卡补足每一组的大小到 $x$ 就行了，由于答案 $\le n$，买卡是一定可以买到不重的卡的。

没有了，时间复杂度 $O(\sum n)$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,ans;
long long a[300000],k,sum,mx;
int main(){
	scanf("%d",&T);
	while(T --){
		sum = mx = 0;
		scanf("%d%lld",&n,&k);
		for(int i = 1;i <= n;i ++) scanf("%lld",&a[i]);
		for(int i = 1;i <= n;i ++) sum += a[i],mx = max(mx,a[i]);
		for(int i = 1;i <= n;i ++) if((sum + k) / i * i >= sum && (sum + k) / i >= mx) ans = i;//后面遇到的大的合法答案会覆盖小的答案
		printf("%d\n",ans);
	}
	return 0;
}
```

---

