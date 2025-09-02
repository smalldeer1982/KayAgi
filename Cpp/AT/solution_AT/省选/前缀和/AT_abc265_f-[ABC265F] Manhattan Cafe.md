# [ABC265F] Manhattan Cafe

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc265/tasks/abc265_f

$ N $ 次元空間上の $ 2 $ 点 $ x=(x_1,\ x_2,\ \dots,\ x_N) $, $ y\ =\ (y_1,\ y_2,\ \dots,\ y_N) $ のマンハッタン距離 $ d(x,y) $ は次の式で定義されます。

$ \displaystyle\ d(x,y)=\sum_{i=1}^n\ \vert\ x_i\ -\ y_i\ \vert $ 

また、座標成分 $ x_1,\ x_2,\ \dots,\ x_N $ がすべて整数であるような点 $ x=(x_1,\ x_2,\ \dots,\ x_N) $ を格子点と呼びます。

$ N $ 次元空間上の格子点 $ p=(p_1,\ p_2,\ \dots,\ p_N) $, $ q\ =\ (q_1,\ q_2,\ \dots,\ q_N) $ が与えられます。  
$ d(p,r)\ \leq\ D $ かつ $ d(q,r)\ \leq\ D $ であるような格子点 $ r $ としてあり得るものは全部で何個ありますか？答えを $ 998244353 $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100 $
- $ 0\ \leq\ D\ \leq\ 1000 $
- $ -1000\ \leq\ p_i,\ q_i\ \leq\ 1000 $
- 入力される値はすべて整数

### Sample Explanation 1

$ N=1 $ の場合は $ 1 $ 次元空間、すなわち数直線上の点に関する問題になります。 条件を満たす点は $ -2,-1,0,1,2,3,4,5 $ の $ 8 $ 個です。

## 样例 #1

### 输入

```
1 5
0
3```

### 输出

```
8```

## 样例 #2

### 输入

```
3 10
2 6 5
2 1 2```

### 输出

```
632```

## 样例 #3

### 输入

```
10 100
3 1 4 1 5 9 2 6 5 3
2 7 1 8 2 8 1 8 2 8```

### 输出

```
145428186```

# 题解

## 作者：2020luke (赞：11)

# [[ABC265F] Manhattan Cafe](https://www.luogu.com.cn/problem/AT_abc265_f) 题解

upd in 2024/3/17 感谢由 [DengDuck](https://www.luogu.com.cn/user/501947) 大佬指出的笔误，现已修改。

## 思路解析

很有思维难度的一道题。思路是 dp，$f_{i,j,k}$ 表示已经计算了 $i$ 维，距离点 $p$ 的距离为 $j$，距离点 $q$ 的距离为 $k$ 时的整点 $r$ 个数，由此可见我们的每一维都可以从上一维推出来，因为计算高维度的两点之间的曼哈顿距离就是它们在每一维上的坐标差的总和，所以可以得出 $f_{i,j,k}\gets f_{i,j-\Delta j,k-\Delta k}$，这里的 $\Delta$ 是指对于每一个 $r$，它和 $p$ 和 $q$ 在当前这一维上的坐标差，其实也就是 $f_{i,j,k}\gets\sum\limits_{r}f_{i-1,j-\left|r_{i}-p_{i}\right|,k-\left|r_{i}-q_{i}\right|}$。

由此可见我们需要分类讨论在这一维上 $r$ 和 $p$ 和 $q$ 之间的位置关系，拆绝对值可得：

- $q_{i}\leq p_{i},q_{i}\leq r_{i}\leq p_{i}$ 时，$f_{i,j,k}\gets f_{i-1,j,k-s}+f_{i-1,j-1,k-s+1}+\dots+f_{i-1,j-s,k}$。
- $q_{i}\leq p_{i},r_{i}<q_{i}$ 时，$f_{i,j,k}\gets f_{i-1,j-1,k-s-1}+f_{i-1,j-2,k-s-2}+\dots$。
- $q_{i}\leq p_{i},r_{i}>p_{i}$ 时，$f_{i,j,k}\gets f_{i-1,j-s-1,k-1}+f_{i-1,j-s-2,k-2}+\dots$。


这里的 $s$ 代表的是 $\left|p_{i}-q_{i}\right|$，也就是 $p_{i}$ 和 $q_{i}$ 之间的区间长度。


如果你能想到这一步，非常好，你已经获得了一个 $O(nd^3)$ 的程序，代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
const ll N = 110, D = 1010, mod = 998244353;
ll n, d;
ll p[N], q[N];
ll f[N][2 * D][D], sum[2 * D][D], sum2[2 * D][D];
int main() {
	cin >> n >> d;
	for(int i = 1; i <= n; i++) {
		cin >> p[i];
	}
	for(int i = 1; i <= n; i++) {
		cin >> q[i];
	}
	f[0][0][0] = 1;
	for(int i = 1; i <= n; i++) {
		ll s = abs(p[i] - q[i]);
		for(int j = 0; j <= 2 * d; j++) {
			for(int k = 0; k <= d; k++) {
				f[i][j][k] = 0;
				for(int l = 0; l <= s; l++) {
					if(j - l >= 0 && k - s + l >= 0) {
						f[i][j][k] += f[i - 1][j - l][k - s + l];
						f[i][j][k] %= mod;
					}
				}
				for(int l = 1; j - l >= 0 && k - s - l >= 0; l++) {
					if(j - l >= 0 && k - s - l >= 0) {
						f[i][j][k] += f[i - 1][j - l][k - s - l];
						f[i][j][k] %= mod;
					}
				}
				for(int l = 1; j - s - l >= 0 && k - l >= 0; l++) {
					if(j - s - l >= 0 && k - l >= 0) {
						f[i][j][k] += f[i - 1][j - s - l][k - l];
						f[i][j][k] %= mod;
					}
				}
			}
		}
	}
	ll ans = 0;
	for(ll j = 0; j <= d; j++) {
		for(ll k = 0; k <= d; k++) {
			if(abs(j - k) <= d) {
				ans += f[n][j][k];
				ans %= mod;
			}
		}
	}
	cout << ans;
	return 0;
}
```

但很遗憾此题数据为 $n\leq100,d\leq1000$ 无法通过。可是我们发现每一次的 $f_{i,j,k}$ 的累加都是成对角线形状累加的，于是便可想到使用前缀和进行优化：

- 对于第一种情况：由于 $j,k$ 是互补的，可见这种情况的对角线是一条垂直于主对角线的对角线，可以用一个 $sum_{j,k}$ 表示 $j,k$ 所存在的这条对角线从 $f_{i-1,0,k+j}$ 一直累加到 $f_{i-1,j,k}$ 的值。**但是需要注意**我们只选取对角线中结尾为 $j,k$ 且长度最长为 $s$，因为只有这些情况的取值是符合这种情况分类讨论的判断条件的。**以及**如果对角线的两端小于 $0$，也就是两端不存在，我们就特判两端是否存在，只统计剩余的存在的部分（我就是因为这里卡了一晚上。

- 对于第二和第三种情况：由于 $j-k$ 是不变的，可见它们所经过的对角线是一条平行于主对角线的对角线，可以用一个 $sum2_{j,k}$ 表示从这条对角线的开头累加到 $f_{i-1,j,k}$ 的值。


## code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
const ll N = 110, D = 1010, mod = 998244353;
ll n, d;
ll p[N], q[N];
ll f[N][2 * D][D], sum[2 * D][2 * D], sum2[2 * D][2 * D];
int main() {
	cin >> n >> d;
	for(ll i = 1; i <= n; i++) {
		cin >> p[i];
	}
	for(ll i = 1; i <= n; i++) {
		cin >> q[i];
	}
	f[0][0][0] = 1;
	for(int i = 1; i <= n; i++) {
		memset(sum, 0, sizeof(sum));	//别忘了清空数组
		memset(sum2, 0, sizeof(sum2));
		for(ll j = 0; j <= d; j++) {
			for(ll k = 0; k <= d; k++) {
				if(j - 1 >= 0) {
					sum[j][k] += sum[j - 1][k + 1];
					sum[j][k] %= mod;	//记得取模
				}
				sum[j][k] += f[i - 1][j][k];
				sum[j][k] %= mod;
				if(j - 1 >= 0 && k - 1 >= 0) {
					sum2[j][k] += sum2[j - 1][k - 1];
					sum2[j][k] %= mod;
				}
				sum2[j][k] += f[i - 1][j][k];
				sum2[j][k] %= mod;
			}
		}
		ll s = abs(p[i] - q[i]);
		for(ll j = 0; j <= d; j++) {
			for(ll k = 0; k <= d; k++) {
				f[i][j][k] = 0;
				if(k - s >= 0) {	//细节特判
					if(j - s >= 0) {
						f[i][j][k] += (sum[j][k - s] - sum[j - s][k] + f[i - 1][j - s][k]) % mod;
					}
					else {
						f[i][j][k] += (sum[j][k - s] - sum[0][k - s + j] + f[i - 1][0][k - s + j]) % mod;
					}
				}
				else {
					if(j - s >= 0) {
						f[i][j][k] += (sum[j - s + k][0] - sum[j - s][k] + f[i - 1][j - s][k]) % mod;
					}
					else {
						f[i][j][k] += (sum[j - s + k][0] - sum[0][k - s + j] + f[i - 1][0][k - s + j]) % mod;
					}
				}
				f[i][j][k] %= mod;
				if(j - 1 >= 0 && k - s - 1 >= 0) {
					f[i][j][k] += sum2[j - 1][k - s - 1];
					f[i][j][k] %= mod;
				}
				if(j - s - 1 >= 0 && k - 1 >= 0) {
					f[i][j][k] += sum2[j - s - 1][k - 1];
					f[i][j][k] %= mod;
				}
			}
		}
	}
	ll ans = 0;
	for(ll j = 0; j <= d; j++) {
		for(ll k = 0; k <= d; k++) {
			ans += f[n][j][k];
			ans %= mod;
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Expert_Dream (赞：9)

[博客园](https://www.cnblogs.com/gsczl71/p/17880643.html)。

考虑 Dp，可以先设 $dp_{i,j,k}$ 为前 $i$ 维，$r$ 到 $p$ 所累积的距离为 $j$，$r$ 到 $q$ 累计的距离是 $k$。于是 $dp_{i,j,k}$ 从 $dp_{i-1,j-|r_i-p_i|,k-|r_i-q_i|}$ 转移来。

因为有绝对值，所以得要进行分类讨论。具体情况如下。

放上这张图片:

![](https://cdn.luogu.com.cn/upload/image_hosting/opivu6po.png)

注：图片中的文字均有在下文提及。主要还是为了展现教练的灵魂画图。

设：$x = |p_i - q_i|$。 

不妨先对正常的情况尽心分类讨论一下。

- 第一种情况：$r_i$ 在 $p_i$ 与 $q_i$ 中间。$dp_{i,j,k} = dp_{i-1,j,k-x} + \cdots + dp_{i-1,j-x,k}$。
- 第二种情况：$r$ 在 $q_i$ 和 $p_i$ 的左边。$dp_{i,j,k} = dp_{i-1,j-1,k-x-1} + dp_{i-1,j-2,k-x-2} + \cdots$。
- 第三种情况：$r$ 在 $q_i$ 和 $p_i$ 的右边。$dp_{i,j,k} = dp_{i-1,j-x-1,k-1} + dp_{i-1,j-x-2,k-2} + \cdots$。

但这是一个 $O(n D^3)$ 的暴力，无法通过。所以考虑如何优化这个 Dp，想到前缀和优化。

还是像刚才一样，分类讨论前缀和，因为情况的不一样，我们会发现第二第三种情况其实比较类似的，所以我们可以分成两个前缀和来写。

- 第一种前缀和：包含着上述暴力中的第一种情况。由于我们发现 $j+k$ 一直是一个数，显然这是一个反着的对角线，可以抽象的理解就是从右上角连向左下角，说白了，就是主对角线的垂直对角线。$qzh_{j,k}$ 来表示 $dp_{i-1,0,k+j} + \cdots + dp_{i-1,j,k}$ 这条对角线，记录他的累加和，到最后状态转移计算中直接调用就可以咯。

- 第二种前缀和：包含着上述暴力中的第二和第三种情况。由于 $j-k$ 是不变的，所以是一条平行于主对角线的线，可以理解为第一种前缀和的垂直的线段。那么我们显然需要再开一个前缀和数组来记录，毕竟方向都是不一样的，怎么能够共用呢！于是，定义：$qzh2_{j,k}$ 从这一条线开始连到 $dp_{i-1,j,k}$ 的值。**第二种情况**中：$dp_{i-1,s,0}$ 开始，**第三种情况**中：$dp_{i-1,0,s}$ 开始。~~这只不过是更加严谨的说法罢了~~。

所以呢？

做完了，只需要在状态转移的时候压缩掉一个 $O(D)$ 的时间复杂度。

我认为吧，其实前缀和的优化并不是特别难，说白了就相当于预处理一些东西而已，但是这种解法确实也是难想，只不过是教练带着才做出来。实际上这一题的难度还是有的！

[link](https://atcoder.jp/contests/abc265/submissions/48731137)。




---

## 作者：EuphoricStar (赞：8)

考虑 dp，$f_{i, j, k}$ 表示考虑到第 $i$ 维，$\sum\limits_{x = 1}^i |p_x - r_x| = j, \sum\limits_{x = 1}^i |q_x - r_x| = k$ 的方案数。转移是容易的，枚举 $r_i$ 即可，$f_{i, j, k} = \sum\limits_r f_{i - 1, j - |p_i - r|, k - |q_i - r|}$。

复杂度 $O(nD^3)$，无法接受，考虑**下标拆绝对值后前缀和优化**。简单讨论一下就行。以 $p_i \le q_i$ 的情况为例：

1. $r_i < p_i$，$f_{i, j, k}$ 能从 $\cdots, f_{i - 1, j - 2, k - q_i + p_i - 2}, f_{i - 1, j - 1, k - q_i + p_i - 1}$ 转移；
2. $p_i \le r_i \le q_i$，$f_{i, j, k}$ 能从 $f_{i - 1, j, k - q_i + p_i}, f_{i - 1, j - 1, k - q_i + p_i + 1}, \cdots, f_{i - 1, j - q_i + p_i, k}$ 转移；
3. $r_i > q_i$，$f_{i, j, k}$ 能从 $f_{i - 1, j - b_i + a_i - 1, k - 1}, f_{i - 1, j - b_i + a_i - 2, k - 2}, \cdots$ 转移。

也就是说我们只要维护对角线前缀和就好了。

要注意下标越界的问题。对于第 $1, 3$ 种情况，能转移的是一段前缀或后缀，只要特判下标是否越界即可；对于第 $2$ 种情况，因为能转移的是一段区间，如果下标为负，就要找到第一个 $0$ 开始转移。

想清楚了写起来挺快的，不存在难写的问题。注意一些细节问题即可，比如符号写反，或者没取模等等，别像我一样有一处漏了取模然后傻傻调试 20min 就行。

时间复杂度 $O(nD^2)$，可以通过。

[code](https://atcoder.jp/contests/abc265/submissions/42222964)

---

## 作者：wind_boy (赞：5)

题解区好像都是 $O(nd^2)$ 的做法，我来发个 $O(n^2d)$ 的做法。

首先我们不妨令 $p$ 为 $p-q$，$q$ 为原点，并将 $p$ 的每一维取绝对值。

然后，我们发现，$|p_i-r_i|+|q_i-r_i|\geq |p_i-q_i|$，因此 $d(p,r)+d(q,r)\geq d(p,q)$. 又由于 $d(p,r)\leq D,d(q,r)\leq D$，因此答案不为 $0$ 当且仅当 $d(p,q)\leq 2D$。

接下来，我们把 dp 分为两部分：处理 $r_i\in[0,p_i]$ 的点 $i$ 和处理 $r_i\not\in[0,p_i]$ 的点 $i$。

对于第一部分，我们先钦定 $r_i\in[-1,p_i+1]$。设 $f_{i,j,k}$ 表示处理完前 $i$ 维，且 $\sum_{x=1}^i\min(p_x,\max(0,r_x))=j$，且满足 $r_x\not\in[0,p_x]$ 的点有 $k$ 个的方案数。转移：枚举 $x$，$f_{i,j,k}\to f_{i+1,j+\min(p_i,\max(0,x)),k+[x\not\in[0,p_i]]}$。转移可以用前缀和优化。由于 $d(p,q)\leq 2D$，因此时间复杂度 $O(n^2d)$。

对于第二部分，枚举 $j,k$（含义同上）。我们考虑将满足 $r_x\not\in[0,p_x]$ 的这 $k$ 个点“扩展”。由于每扩展一次，$d(p,r)$ 和 $d(q,r)$ 都会加 $1$，因此它们最多只能扩展 $x=d-\min(j,(\sum_i p_i)-j)$ 次。于是现在问题变成，求有多少长为 $k$ 的数列，满足它们的和 $\leq x$。对于这个问题，直接背包即可 $O(nd)$。

总时间复杂度 $O(n^2d)$。

[code](https://atcoder.jp/contests/abc265/submissions/48986005)

upd：修改了一处笔误

---

## 作者：Tsawke (赞：4)

# [[ABC265F] Manhattan Cafe](https://www.luogu.com.cn/problem/AT_abc265_f) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC265F)

## 题面

在 $ n $ 维空间中存在 $ p, q $ 两点，求有多少个整点满足到 $ p, q $ 的曼哈顿距离均不大于 $ d $。

## Solution

细节巨多的 DP。

首先有一个较为显然的 $ \texttt{3D1D} $ 的 $ O(nd^3) $ 的做法，即令 $ dp(i, j, k) $ 表示考虑前 $ i $ 维到 $ p $ 曼哈顿距离为 $ j $，到 $ q $ 曼哈顿距离为 $ k $ 的方案数，然后这个东西 $ O(d) $ 的转移较为显然，即枚举 $ i $ 维的坐标，令其为 $ x $ 则转移为：
$$
dp(i, j, k) = \sum_x dp(i, j - \lvert x - p_i \rvert, k - \lvert x - q_i \rvert) \times [\lvert x - p_i \rvert \le d \land \lvert x - q_i \rvert \le d]
$$
然后这个东西实际上是可以通过类似前缀和的东西转移的，但是是类似对角线前缀和的，比较复杂细节巨多，所以这里参考以下机房大佬 @sssmzy 的做法。

考虑将状态修改为 $ dp(i, j, k) $ 表示考虑前 $ i $ 维，到 $ p $ 和 $ q $ 的曼哈顿距离和为 $ j $，到 $ p $ 的曼哈顿距离为 $ k $。

这个时候考虑两种可能性，对于某次枚举的位置 $ x $，若满足 $ p_i \le x \le q_i \lor q_i \le x \le p_i $，也就是说 $ x $ 在 $ p, q $ 之间，那么 $ j $ 这一维是从 $ j - \lvert p_i - q_i \rvert $ 转移而来，而 $ k $ 从 $ k $ 到 $ k - \lvert p_i - q_i \rvert $ 这段区间转移而来，那么即可以用前缀和转移。

考虑对于 $ x $ 在 $ p, q $ 之外的情况，那么对于每个 $ x \leftarrow x + 1 \lor x \leftarrow x - 1 $，显然存在 $ j \leftarrow j + 2, k \leftarrow j + 1 $。所以我们只需要再维护一个前缀和 $ sum_2(j, k) = sum_2(j - 2, k - 1) + dp(j, k) $ 即可。

具体来说，维护一个 $ sum $ 和 $ sum_2 $，意义同上。同时因为空间问题我们需要把第一维滚动掉。具体的转移即若 $ j \lt \lvert p_i - q_i \rvert $ 那么 $ dp(j, k) = 0 $。否则令 $ dis = \lvert p_i - q_i \rvert $，即为：
$$
dp(j, k) = sum(j - dis, k) - sum(j - dis, k - dis - 1) + sum_2(j - dis - 2, k - 1) + sum_2(j - dis - 2, k - dis - 1)
$$
转移的意义即为在 $ p, q $ 中间和分别在 $ p, q $ 的两侧。

于是每次处理完 DP 后清空并重新维护 $ sum, sum_2 $ 即可。

最终复杂度为 $ O(nd^2) $，可以通过。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

#define MOD (998244353ll)

template < typename T = int >
inline T read(void);

int N, D;
int P[110], Q[110];
ll dp[2100][1100];
ll sum[2100][1100];
ll sum2[2100][1100];
ll ans(0);

int main(){
    N = read(), D = read();
    for(int i = 1; i <= N; ++i)P[i] = read();
    for(int i = 1; i <= N; ++i)Q[i] = read();
    dp[0][0] = 1;
    for(int j = 0; j <= D * 2; ++j)
        for(int k = 0; k <= D; ++k)
            sum[j][k] = ((k - 1 >= 0 ? sum[j][k - 1] : 0) + dp[j][k]) % MOD,
            sum2[j][k] = ((j - 2 >= 0 && k - 1 >= 0 ? sum2[j - 2][k - 1] : 0) + dp[j][k]) % MOD;
    for(int i = 1; i <= N; ++i){
        for(int j = 0; j <= D * 2; ++j)
            for(int k = 0; k <= D; ++k){
                int dis = abs(P[i] - Q[i]);
                dp[j][k] = j >= dis
                    ?
                        ((sum[j - dis][k] - (k - dis - 1 >= 0 ? sum[j - dis][k - dis - 1] : 0) + MOD) % MOD +
                        (j - dis - 2 >= 0 && k - 1 >= 0 ? sum2[j - dis - 2][k - 1] % MOD : 0) +
                        (j - dis - 2 >= 0 && k - dis - 1 >= 0 ? sum2[j - dis - 2][k - dis - 1] % MOD : 0)) % MOD
                    : 0;
            }
        memset(sum, 0, sizeof sum), memset(sum2, 0, sizeof sum2);
        for(int j = 0; j <= D * 2; ++j)
            for(int k = 0; k <= D; ++k)
                sum[j][k] = ((k - 1 >= 0 ? sum[j][k - 1] : 0) + dp[j][k]) % MOD,
                sum2[j][k] = ((j - 2 >= 0 && k - 1 >= 0 ? sum2[j - 2][k - 1] : 0) + dp[j][k]) % MOD;
    }
    for(int j = 0; j <= D * 2; ++j)for(int k = 0; k <= min(j, D); ++k)
        if(j - k <= D) (ans += dp[j][k]) %= MOD;
    printf("%lld\n", ans);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2023_01_05 初稿

---

## 作者：harmis_yz (赞：3)

## 分析

模拟赛签到题。

定义状态函数 $f_{i,j,k}$ 表示前 $i$ 维中，选出来坐标后 $d(p,r)=j,d(q,r)=k$ 的方案数。则有转移方程：$f_{i,j,k} = \sum\limits_{\min(j-|p_i-x|,k-|q_i-x|)\ge 0}^{}f_{i-1,j-|p_i-x|,k-|q_i-x|}$

复杂度是 $O(nd^3)$ 的。猜测能够优化掉枚举 $x$。

将 $x$ 分成 $3$ 类：

1. $x \le\min(p_i,q_i)$。
2. $\min(p_i,q_i) < x < \max(p_i,q_i)$。
3. $x \ge \max(p_i,q_i)$。

$1,3$ 两种情况比较一眼。拿第 $1$ 种情况来说，有：$f_{i,j,k}=f_{i,j,k}+\sum\limits_{\min(j-p_i+x,k-q_i+x)\ge 0} f_{i-1,j-p_i+x,k-q_i+x}$。

把条件里的 $x$ 提出来，得到 $x$ 的范围是：$-\min(j-p_i,k-q_i) \le x \le \min(p_i,q_i)$。然后就能够通过前缀和优化掉了。第 $3$ 种情况同理，$x$ 的范围是：$\max(p_i,q_i) \le x \le \min(j+p_i,k+q_i)$。

对于第 $2$ 种情况，又分出两种小情况：

1. $p_i \ge q_i$。
2. $p_i <q_i$。

第 $1$ 种小情况，可以把条件写成 $\min(j-p_i+x,k+q_i-x)\ge 0$。通过不等式得到 $x$ 的范围是：$\max(\min(p_i,q_i)+1,p_i-j) \le x \le \min(\max(p_i,q_i)-1,q_i+k)$。然后也是一个类似于前缀和的优化（第 $1$ 维加第 $2$ 维减）。第 $2$ 种小情况同理，$x$ 的范围是：$\max(\min(p_i,q_i)+1,q_i-k) \le x \le \min(\max(p_i,q_i)-1,p_i+j)$。这个可以通过一个第 $1$ 维减第 $2$ 维加的东西优化。

观察到 $f_{i,j,k}$ 只与 $f_{i-1,j',k'}$ 有关，可以把 $i$ 这一维压掉。时间复杂度 $O(nd^2)$，空间复杂度 $O(d^2)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define pii pair<int,int>
#define x first
#define y second
#define gc getchar()
#define rd read()
#define debug() puts("------------")

namespace yzqwq{
	il int read(){
		int x=0,f=1;char ch=gc;
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=gc;}
		while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=gc;
		return x*f;
	}
	il int qmi(int a,int b,int p){
		int ans=1;
		while(b){
			if(b&1) ans=ans*a%p;
			a=a*a%p,b>>=1;
		}
		return ans;
	}
	il auto max(auto a,auto b){return (a>b?a:b);}
	il auto min(auto a,auto b){return (a<b?a:b);}
	il int gcd(int a,int b){
		if(!b) return a;
		return gcd(b,a%b);
	}
	il int lcm(int a,int b){
		return a/gcd(a,b)*b;
	}
	il void exgcd(int a,int b,int &x,int &y){
		if(!b) return x=1,y=0,void(0);
		exgcd(b,a%b,x,y);
		int t=x;
		x=y,y=t-a/b*x;
		return ;
	}
	mt19937 rnd(time(0));
}
using namespace yzqwq;

const int N=105,M=1005,md=998244353;
int w=1,n,d,p[N],q[N];
int f[2][M][M],s1[2][M][M],s2[2][M][M],s3[2][M][M];

il void solve(){
	n=rd,d=rd;
	f[0][0][0]=1;
	for(re int i=0;i<=d;++i) s1[0][i][i]=1;
	for(re int i=0;i<=0;++i){
		for(re int j=0;j<=d;++j)
		for(re int k=d;k>=0;--k){
			s2[i][j][k]=f[i][j][k];
			if(j>0&&k<d) s2[i][j][k]=(s2[i][j][k]+s2[i][j-1][k+1])%md;
		}
		for(re int j=d;j>=0;--j)
		for(re int k=0;k<=d;++k){
			s3[i][j][k]=f[i][j][k];
			if(k>0&&j<d) s3[i][j][k]=(s3[i][j][k]+s3[i][j+1][k-1])%md;
		}
	}
	
	for(re int i=1;i<=n;++i) p[i]=rd;
	for(re int i=1;i<=n;++i) q[i]=rd;
	for(re int i=1;i<=n;++i,w^=1){
		for(re int j=0;j<=d;++j)
		for(re int k=0;k<=d;++k){
			f[w][j][k]=0;
			//1:x<=min(p[i],q[i]) ok
			//2:x>=max(p[i],q[i]) ok
			//3:min(p[i],q[i])<x<max(p[i],q[i])
			
			int Min=min(p[i],q[i]),Max=max(p[i],q[i])+(p[i]==q[i]);
			int minn1=-1*min(j-p[i],k-q[i]),minn2=min(j+p[i],k+q[i]);
			if(Min>=minn1) f[w][j][k]=(f[w][j][k]+s1[w^1][j-p[i]+Min][k-q[i]+Min])%md;
			if(Max<=minn2) f[w][j][k]=(f[w][j][k]+s1[w^1][j+p[i]-Max][k+q[i]-Max])%md;		
			
			//1:p[i]>=q[i]
			//2:p[i]< q[i]
			
			if(p[i]>=q[i]){
				//q[i]<x<p[i]+s
				//min(j-p[i]+x,k+q[i]-x)>=0
				//x>=p[i]-j,x<=k+q[i]
				Min=max(Min+1,p[i]-j);
				Max=min(Max-1,q[i]+k);
				if(Min<=Max){
					int a1=j-p[i]+Max,a2=k+q[i]-Max;
					int b1=j-p[i]+Min,b2=k+q[i]-Min;
					--b1,++b2;
					f[w][j][k]=(f[w][j][k]+((s2[w^1][a1][a2]-s2[w^1][b1][b2])%md+md)%md)%md;
				}
			}
			else{
				//p[i]<x<q[i]+s
				//min(k-q[i]+x,j+p[i]-x)>=0
				//x>=q[i]-k,x<=j+p[i]
				Min=max(Min+1,q[i]-k);
				Max=min(Max-1,p[i]+j);
				if(Min<=Max){
					int a2=k-q[i]+Max,a1=j+p[i]-Max;
					int b2=k-q[i]+Min,b1=j+p[i]-Min;
					--b2,++b1;
					f[w][j][k]=(f[w][j][k]+((s3[w^1][a1][a2]-s3[w^1][b1][b2])%md+md)%md)%md;
				}
			}
			s1[w][j][k]=f[w][j][k];
			if(j>0&&k>0) s1[w][j][k]=(s1[w][j][k]+s1[w][j-1][k-1])%md;
		}
		for(re int j=0;j<=d;++j)
		for(re int k=d;k>=0;--k){
			s2[w][j][k]=f[w][j][k];
			if(j>0&&k<d) s2[w][j][k]=(s2[w][j][k]+s2[w][j-1][k+1])%md;
		}
		for(re int j=d;j>=0;--j)
		for(re int k=0;k<=d;++k){
			s3[w][j][k]=f[w][j][k];
			if(k>0&&j<d) s3[w][j][k]=(s3[w][j][k]+s3[w][j+1][k-1])%md;
		}
	}
	int ans=0;
	for(re int i=0;i<=d;++i)
	for(re int j=0;j<=d;++j)
		ans=(ans+f[w^1][i][j])%md;
	printf("%lld\n",ans);
	return ;
}

signed main(){
//	freopen("dis.in","r",stdin);
//	freopen("dis.out","w",stdout);
	int t=1;while(t--)
	solve();
	return 0;
}
```

---

