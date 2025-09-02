# [EC Final 2022] Aqre

## 题目描述

给定一个 $n \times m$ 矩阵，你需要用 $0$ 和 $1$ 填充它，使得满足以下条件：

- 不能有**四个**连续的水平或垂直单元格填有相同的数字。
- 填有 $1$ 的单元格形成一个连通区域。（如果它们共享一个边，则两个单元格是相邻的。如果对于每对单元格，可以找到一条完全位于该区域内的连接两个单元格的路径，并且每一步只能从一个单元格移动到相邻的单元格，则一组单元格被称为连通的。）

请构造一个满足上述条件且具有尽可能多的 $1$ 的矩阵。输出 $1$ 的最大数量以及该矩阵。

## 样例 #1

### 输入

```
3
2 2
3 4
3 8
```

### 输出

```
4
11
11
9
1110
1110
1110
18
11101110
10111011
11011011
```

# 题解

## 作者：Jsxts_ (赞：2)

首先特判 $n,m\le 3$。

其次是其中一个 $\le 3$（假设为 $n$）：

- $n=2$：形如

```
11101110
10111011
```

- $n=3$：形如

```
1110111011
1011101110
1110111011
```

接下来是一般情况。我们猜测（？答案一定在每个 $4\times 4$ 矩形里同构，并满足矩形内为 $4$ 个不同行、列的点。

一种比较暴力的手段为枚举 $4\times 4$ 矩形的所有方案，并 check 每种是否合法（连通）。

不过通过若干手玩，可以发现答案的构成会有以下形式：

```
0111
1101
1011
1110

1110
1011
1101
0111

1101
1110
1011
0111

1110
1101
0111
1011
```

将所有答案排个序即可。注意其中第 $3,4$ 种分别在 $m\equiv0\pmod 4,n\equiv0\pmod 4$ 时不合法。

```cpp
#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef long long ll;
const int inf = 1e9;
const ll INF = 1e15;
const int N = 1e3;
inline int read() {
	int s = 0,f = 1;char ch = getchar();
	while (!isdigit(ch)) f = ch == '-' ? -1 : 1, ch = getchar();
	while (isdigit(ch)) s = (s << 3) + (s << 1) + ch - '0', ch = getchar();
	return s*f;
}
const int mod = 998244353;
int getmod(int x) {
	return x - (x >= mod) * mod;
}
int qpow(int a,int b) {
	int res = 1;
	while (b) {
		if (b & 1) res = 1ll * res * a % mod;
		b >>= 1, a = 1ll * a * a % mod;
	}
	return res;
}
int id[10];
struct node {
	int ct;
	int a[N + 10][N + 10];
}a[6];
int cmp(int x,int y) {
	return a[x].ct < a[y].ct;
}
int main() {
	int T = read();
	while (T -- ) {
		int n = read(),m = read();
		a[0].ct = n * m;
		a[1].ct = a[2].ct = a[3].ct = a[4].ct = a[5].ct = 0;
		for (int i = 1;i <= n;i ++ )
			for (int j = 1;j <= m;j ++ ) a[0].a[i][j] = a[1].a[i][j] = a[2].a[i][j] = a[3].a[i][j] = a[4].a[i][j] = a[5].a[i][j] = 1;
		if (n <= 3 && m > 3) {
			for (int i = 4;i <= m;i += 4) a[0].a[1][i] = a[0].a[3][i] = 0, a[0].ct --, a[0].ct -= n == 3;
			for (int i = 2;i <= m;i += 4) a[0].a[2][i] = 0, a[0].ct --;
		}
		else if (m <= 3 && n > 3) {
			for (int i = 4;i <= n;i += 4) a[0].a[i][1] = a[0].a[i][3] = 0, a[0].ct --, a[0].ct -= m == 3;
			for (int i = 2;i <= n;i += 4) a[0].a[i][2] = 0, a[0].ct --;
		}
		else {
			a[3].ct = a[4].ct = a[5].ct = n * m;
		}
		if (n > 3 && m > 3) {
			for (int i = 1;i <= n;i += 4)
				for (int j = 4;j <= m;j += 4)
					a[0].a[i][j] = 0, a[0].ct --;
			for (int i = 2;i <= n;i += 4)
				for (int j = 2;j <= m;j += 4)
					a[0].a[i][j] = 0, a[0].ct --;
			for (int i = 3;i <= n;i += 4)
				for (int j = 3;j <= m;j += 4)
					a[0].a[i][j] = 0, a[0].ct --;
			for (int i = 4;i <= n;i += 4)
				for (int j = 1;j <= m;j += 4)
					a[0].a[i][j] = 0, a[0].ct --;

			for (int i = 1;i <= n;i += 4)
				for (int j = 1;j <= m;j += 4)
					a[3].a[i][j] = 0, a[3].ct --;
			for (int i = 2;i <= n;i += 4)
				for (int j = 3;j <= m;j += 4)
					a[3].a[i][j] = 0, a[3].ct --;
			for (int i = 3;i <= n;i += 4)
				for (int j = 2;j <= m;j += 4)
					a[3].a[i][j] = 0, a[3].ct --;
			for (int i = 4;i <= n;i += 4)
				for (int j = 4;j <= m;j += 4)
					a[3].a[i][j] = 0, a[3].ct --;

			if (m % 4 != 0) {
				a[1].ct = n * m;
				for (int i = 1;i <= n;i += 4)
					for (int j = 3;j <= m;j += 4)
						a[1].a[i][j] = 0, a[1].ct --;
				for (int i = 2;i <= n;i += 4)
					for (int j = 4;j <= m;j += 4)
						a[1].a[i][j] = 0, a[1].ct --;
				for (int i = 3;i <= n;i += 4)
					for (int j = 2;j <= m;j += 4)
						a[1].a[i][j] = 0, a[1].ct --;
				for (int i = 4;i <= n;i += 4)
					for (int j = 1;j <= m;j += 4)
						a[1].a[i][j] = 0, a[1].ct --;
			}
			if (n % 4 != 0) {
				a[2].ct = n * m;
				for (int i = 1;i <= n;i += 4)
					for (int j = 4;j <= m;j += 4)
						a[2].a[i][j] = 0, a[2].ct --;
				for (int i = 2;i <= n;i += 4)
					for (int j = 3;j <= m;j += 4)
						a[2].a[i][j] = 0, a[2].ct --;
				for (int i = 3;i <= n;i += 4)
					for (int j = 1;j <= m;j += 4)
						a[2].a[i][j] = 0, a[2].ct --;
				for (int i = 4;i <= n;i += 4)
					for (int j = 2;j <= m;j += 4)
						a[2].a[i][j] = 0, a[2].ct --;
			}
		}
		for (int i = 0;i < 4;i ++ ) id[i] = i;
		sort(id,id+4,cmp);
		printf("%d\n",a[id[3]].ct);
		for (int i = 1;i <= n;i ++ ,puts(""))
			for (int j = 1;j <= m;j ++ )
				putchar(a[id[3]].a[i][j] + '0');
	}
	return 0;
}
```

---

## 作者：enucai (赞：1)

对于 $\min(n,m)\le 3$ 的，特判一下。

否则一定是有一些 $4\times 4$ 的 pattern 贴图而成的。

然后你爆搜一下 $[5,8]\times [5,8]$ 所有大小的答案，把 pattern 打下来，就做完了。

[贵校是构造王国吗？](https://qoj.ac/submission/296959)

---

## 作者：Rain_chr (赞：0)

打表题，首先得写一个搜索，加上最优性减枝之后 $7\times 7$ 矩阵可以在 3s 内跑出。

特判 $\min(n,m)\le 3$，因为此时有行或者列没有限制。

对于 $4|n,m$ 的矩阵我们打表，发现可以由初始的 $4\times 4$ 矩阵复制多次得到。于是可以做出以下猜测：

> 对于 $n,m\ge 4$ 的矩阵，一定满足对于任意 $(x,y)$，$a_{x,y}=a_{x\bmod 4,y\bmod 4}$

严谨证明不会，但是可以考虑结合打表说明。

对于 $4\times 4$ 的最优方案打表，可以发现最优答案的矩阵每一行每一列恰好有一个 $0$。对于任意 $n,m$ 中的 $4\times 4$ 矩阵，这显然已经达到了我们能够构造的上界，因为如果一行或一列全是 $1$ 那么已经不合法了。

所以重复 $4\times 4$ 的矩阵可以使得答案达到了可以构造的上界，我们现在只需要说明重复这种矩阵能够保证 $1$ 是连通的，并且矩阵之间不会产生连续四个 $1$。

首先对于初始的合法 $4\times 4$ 矩阵，其必然是连通的。由于我们这样复制的答案可以使得连续四个数中至少有三个 $1$，所以每一个 $1$ 都会与其他的 $1$ 连通。

同时重复会使得 $0$ 的位置永远满足对于任意 $4\times 4$ 的矩阵，矩阵每一行每一列恰好有一个 $0$，所以永远不会出现连续四个 $1$。

所以这样复制就能达到答案上界并且满足限制。

---

