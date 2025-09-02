# Vasily the Bear and Painting Square

## 题目描述

Vasily the bear has two favorite integers $ n $ and $ k $ and a pencil. Besides, he's got $ k $ jars with different water color paints. All jars are numbered in some manner from $ 1 $ to $ k $ , inclusive. The jar number $ i $ contains the paint of the $ i $ -th color.

Initially the bear took a pencil and drew four segments on the coordinate plane. All of them end at point $ (0,0) $ . They begin at: $ (0,2^{n}) $ , $ (0,-2^{n}) $ , $ (2^{n},0) $ , $ (-2^{n},0) $ . Then for each $ i=1,2,...,n $ , the bear drew two squares. The first square has the following vertex coordinates: $ (2^{i},0) $ , $ (-2^{i},0) $ , $ (0,-2^{i}) $ , $ (0,2^{i}) $ . The second square has the following vertex coordinates: $ (-2^{i-1},-2^{i-1}) $ , $ (-2^{i-1},2^{i-1}) $ , $ (2^{i-1},-2^{i-1}) $ , $ (2^{i-1},2^{i-1}) $ . After that, the bear drew another square: $ (1,0) $ , $ (-1,0) $ , $ (0,-1) $ , $ (0,1) $ . All points mentioned above form the set of points $ A $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF336E/181ebcd986175c2f3adb2eae120adaf1e5f14854.png)

The sample of the final picture at $ n=0 $

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF336E/e6cc4ea6655f30f4cc22f6f5a70b90a16e22032c.png)

The sample of the final picture at $ n=2 $

The bear decided to paint the resulting picture in $ k $ moves. The $ i $ -th move consists of the following stages:

1. The bear chooses 3 distinct points in set $ А $ so that any pair of the chosen points has a segment on the picture between them. The chosen points and segments mark the area that mustn't contain any previously painted points.
2. The bear paints the area bounded by the chosen points and segments the $ i $ -th color.

Note that after the $ k $ -th move some parts of the picture can stay unpainted.

The bear asked you to calculate, how many distinct ways there are to paint his picture. A way to paint the picture is a sequence of three-element sets of points he chose on each step. Two sequences are considered distinct if there is such number $ i $ ( $ 1<=i<=k) $ , that the $ i $ -th members of these sequences do not coincide as sets. As the sought number can be rather large, you only need to calculate the remainder after dividing it by number $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 样例 #1

### 输入

```
0 0
```

### 输出

```
1
```

## 样例 #2

### 输入

```
0 1
```

### 输出

```
8
```

## 样例 #3

### 输入

```
0 2
```

### 输出

```
32
```

## 样例 #4

### 输入

```
1 1
```

### 输出

```
32
```

# 题解

## 作者：Alex_Wei (赞：4)

### *[CF336E Vasily the Bear and Painting Square](https://www.luogu.com.cn/problem/CF336E)

挺酷的题目。

不区分颜色，求出选择 $k$ 个三角形的方案数，再乘以 $k!$。

三角形只有这四种：

- 大小为 $1$ 且不经过原点的小三角形。
- 大小为 $2$ 且不经过原点的小三角形。
- 以原点为顶点的大三角形。
- 两个以原点为顶点的大三角形拼起来的经过原点的大三角形。

设 $f_{n, k}$ 表示答案。前两类三角形在 $f_n\to f_{n + 1}$ 时关于 $f_n$ 是独立的，但后两类不是。对于第三类三角形，它要求 $f_n$ 的对应的象限没有被选中任何三角形。对于第四类三角形，它要求 $f_n$ 的对应的两个象限没有被选中任何三角形。

记录 $S$ 表示每个象限是否被选中三角形即可。

时间复杂度 $\mathcal{O}(nk)$。

[代码](https://codeforces.com/contest/336/submission/210629569) 使用了一种完全不同的做法：设 $f_{p, n, k}$ 表示 $p$ 个连续的象限的答案，根据实际意义转移。为了防止枚举大三角形时复杂的分类讨论，设 $g_{p, n, k}$ 表示 $p$ 个连续的象限，且没有选 $n$ 阶大三角形的答案。有一种情况的转移需要背包，时间复杂度 $\mathcal{O}(nk ^ 2)$。

---

## 作者：fade_away (赞：2)

## Solution

~~小清新~~ dp 。

题目其实相当于在原图中取 $k$ 个不重叠的三角形，然后把方案数乘上 $k!$ 就是答案。

我们发现 $n$ 的图和 $n+1$ 的图相似，因此考虑一层一层 dp ，相当于去枚举和当前最外层相交但不包含更外层的三角形（注意把斜和正两个正方形作为一层，最内层只有一个斜正方形）。

然后我们发现每一次取三角形有如下几种：

- 取单独一个小三角形。
- 取斜正方形角上两个小三角形拼接的三角形。
- 取一个象限的大三角形。
- 取两个象限的大三角形。

于是我们可以把状态表示为 $f_{x,y,p}$ 表示从内向外 $0..x$ 层，取 $y$ 个三角形， $p$ 中象限被当成大三角形取过。

然后就可以 $dp$ 了。

## Code

本题实现上可能比较麻烦，这里采用记忆化搜索，并且把 $p$ 压缩为 $0...5$ 表示有哪些像限存活（有 6 个是因为 2 个象限时有两种情况，切一个点和切一条边两种）。

然后我们又把 dp 分成三个阶段，分别来做前两种转移，第三种转移，第四种转移，详见代码。

于是时间复杂度变为 $O(nk)$。

```cpp
int C[15][15], f[205][205][6][3];

int g[6] = {0, 0, 1, 0, 2, 4};
int T1[6][6] = {{1}, {1, 1}, {1, 2, 1}, {1, 2, 0, 1}, {1, 3, 2, 1, 1}, {1, 4, 4, 2, 4, 1}};
int T2[6][6] = {{1}, {0, 1}, {1, 0, 1}, {0, 0, 0, 1}, {0, 2, 0, 0, 1}, {2, 0, 4, 0, 0, 1}};

int upd(int x, int y) { return x + y >= mods ? x + y - mods : x + y; }
int get(int x) { return x - (x > 2); }
int dfs(int x, int y, int p, int q) {
	if (y < 0 || y > get(p) * x * 3 + get(p)) return 0;
	if (f[x][y][p][q] != -1) return f[x][y][p][q];
	int &ans = f[x][y][p][q]; 
	ans = 0;

	if (x == 0 && q == 0) return ans = (y == 0);
	if (q == 0)
		for (int t = 0; t <= g[p] ; ++ t)
			for (int i = 0; i <= get(p) * 3 - t * 2; ++ i) 
				ans = upd(ans, 1ll * dfs(x - 1, y - t - i, p, 2) * C[g[p]][t] % mods * C[get(p) * 3 - t * 2][i] % mods);

	if (q == 1)
		for (int i = 0; i <= p ; ++ i) 
			if (T1[p][i]) ans = upd(ans, 1ll * dfs(x, y - (get(p) - get(i)), i, 0) * T1[p][i] % mods);

	if (q == 2)
		for (int i = 0; i <= p ; ++ i) 
			if (T2[p][i]) ans = upd(ans, 1ll * dfs(x, y - ((get(p) - get(i)) / 2), i, 1) * T2[p][i] % mods);

	return ans;
}
signed main() {
#ifndef ONLINE_JUDGE
	freopen("a.in", "r", stdin);
#endif
	int n, K;
	read(n), read(K);
	for (int i = 0; i <= 12 ; ++ i) C[i][0] = C[i][i] = 1;
	for (int i = 1; i <= 12 ; ++ i)
		for (int j = 1; j < i ; ++ j) C[i][j] = upd(C[i - 1][j], C[i - 1][j - 1]);
	memset(f, -1, sizeof f);

	int ans = dfs(n, K, 5, 2);
	for (int i = 1; i <= K ; ++ i) ans = 1ll * ans * i % mods;
	print(ans);
	return 0;
}
```




---

