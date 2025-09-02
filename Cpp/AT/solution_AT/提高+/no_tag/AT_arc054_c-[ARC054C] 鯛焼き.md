# [ARC054C] 鯛焼き

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc054/tasks/arc054_c

高橋君の家にはタイヤが $ N $ 個と木が $ N $ 本あります。高橋君は、これらを一つずつ組み合わせて鯛焼きを $ N $ 個作ることにしました。

タイヤと木の組には相性があり、相性のいいタイヤと木の組み合わせでのみおいしい鯛焼きを作ることができます。 高橋君はおいしい鯛焼きしか食べないので、作る $ N $ 個の鯛焼きすべてが、相性のいいタイヤと木の組み合わせでできている必要があります。

高橋君はこの条件を満たすように鯛焼きを作る方法が何通りあるのかが気になりましたが、これはとても数えられそうにないことに気付きました。

そこで高橋君は、その方法の数の偶奇だけを求めることにしました。

高橋君は、すべてのタイヤと木のペアについて、そのペアの相性がいいかどうかを表あらわす表 $ (S_{ij}) $ を持っています。この表は $ N $ 行 $ N $ 列からなり、$ i $ 行 $ j $ 列の要素が $ 1 $ のとき $ i $ 番目のタイヤと $ j $ 番目の木の相性がいいことを、 $ 0 $ のとき悪いことを表します。 高橋君に代わって、すべての鯛焼きをおいしくするような組み合わせ方の数の偶奇を求めてください。 ただし、 $ 2 $ つの組み合わせ方が異なるとは、あるタイヤが存在し、そのタイヤが別の木と組み合わせられて鯛焼きが作られていることを指します。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ ≦\ 200 $
- $ S_{ij}=0 $ もしくは $ S_{ij}=1\ (1\ ≦\ i,j\ ≦\ N) $

### Sample Explanation 1

$ 2 $ 通りの組み合わせ方があります。

### Sample Explanation 2

$ 3 $ 通りの組み合わせ方があります。

### Sample Explanation 3

$ 0 $ 通りの組み合わせ方があります。

## 样例 #1

### 输入

```
3
110
101
011```

### 输出

```
Even```

## 样例 #2

### 输入

```
3
110
111
011```

### 输出

```
Odd```

## 样例 #3

### 输入

```
2
00
00```

### 输出

```
Even```

## 样例 #4

### 输入

```
12
000000100000
011111111111
000000100000
000111111100
100100000100
100111111100
100100000100
100111111100
100100000100
100111111100
100000000000
111111111111```

### 输出

```
Even```

# 题解

## 作者：Phobia (赞：0)

观察到本题实质是在求

$$\sum\limits_{j_1j_2\cdots j_n}S_{1j_1}S_{2j_2}\cdots S_{nj_n}\bmod 2$$

的值。

注意到这个式子与矩阵行列式

$$\sum\limits_{j_1j_2\cdots j_n}\left(-1\right)^{\pi\left(j_1j_2\cdots j_n\right)}S_{1j_1}S_{2j_2}\cdots S_{nj_n}$$

十分相似，又有

$$-1\equiv 1\pmod 2$$

所以

$$
\begin{aligned}
\sum\limits_{j_1j_2\cdots j_n}S_{1j_1}S_{2j_2}\cdots S_{nj_n}
&\equiv\sum\limits_{j_1j_2\cdots j_n}\left(-1\right)^{\pi\left(j_1j_2\cdots j_n\right)}S_{1j_1}S_{2j_2}\cdots S_{nj_n}&\pmod 2\\
&\equiv \det S&\pmod 2
\end{aligned}
$$

高斯消元求解行列式即可，使用 bitset 优化可以做到 $O\left(\frac{n^3}{w}\right)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 205;

int n;

char s[maxn];

bitset<maxn> m[maxn];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
	{
		scanf("%s", s + 1);
		for (int j = 1; j <= n; ++j)
			m[i][j] = s[j] & 1;
	}
	for (int i = 1; i <= n; ++i)
	{
		if (!m[i][i])
		{
			for (int j = i + 1; j <= n; ++j)
			{
				if (m[j][i])
				{
					swap(m[i], m[j]);
					break;
				}
			}
		}
		if (!m[i][i])
		{	
			puts("Even");
			return 0;
		}
		for (int j = i + 1; j <= n; ++j)
		{
			if (m[j][i])
				m[j] ^= m[i];
		}
	}
	puts("Odd");
	return 0;
}
```

---

