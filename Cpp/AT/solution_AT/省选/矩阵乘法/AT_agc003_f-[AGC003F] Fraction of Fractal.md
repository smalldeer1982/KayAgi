# [AGC003F] Fraction of Fractal

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc003/tasks/agc003_f

高橋君はお母さんからグリッドをもらいました。このグリッドは縦 $ H $ マス×横 $ W $ マスからなり、各マスは黒か白で塗られています。 黒いマス全体は、縦横にひとつながりになっています。

このグリッドの $ i $ 行 $ j $ 列 $ (1\ ≦\ i\ ≦\ H,\ 1\ ≦\ j\ ≦\ W) $ のマスの情報は、縦横に並んだ文字 $ s_{ij} $ であらわされ、 $ s_{ij} $ が `#` のときこのマスが黒く、 `.` のとき白く塗られていることを表します。少なくともひとつのマスが黒く塗られています。

レベル $ 0 $ のフラクタルとは黒いマスひとつからなる $ 1\ ×\ 1 $ のグリッドであり、 レベル $ k+1 $ のフラクタルとは、レベル $ k $ のフラクタルを、お母さんからもらったグリッドの全ての黒いマスに相当する位置に並べ、白いマスに相当する位置は白いマスで埋めたものを指します。

お母さんからもらったグリッドの情報と整数 $ K $ が与えられるので、レベル $ K $ のフラクタルに黒いマスからなる連結成分がいくつあるかを $ 10^9+7 $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- $ 1\ ≦\ H,W\ ≦\ 1000 $
- $ 0\ ≦\ K\ ≦\ 10^{18} $
- $ s_{ij} $ は `#` か `.` のいずれかである。
- `#` のマス全体は縦横に連結である。
- `#` のマスは少なくともひとつ存在する。

### Sample Explanation 1

この入力例で作られるフラクタルは、以下のようなものです。この黒マスからなる連結成分の数は $ 20 $ なので、$ 20 $ を出力します。 ``` .............#............. ............###............ ............#.#............ ..........#..#..#.......... .........#########......... .........#.##.##.#......... ..........#.....#.......... .........###...###......... .........#.#...#.#......... ....#........#........#.... ...###......###......###... ...#.#......#.#......#.#... .#..#..#..#..#..#..#..#..#. ########################### #.##.##.##.##.##.##.##.##.# .#.....#..#.....#..#.....#. ###...######...######...### #.#...#.##.#...#.##.#...#.# ....#.................#.... ...###...............###... ...#.#...............#.#... .#..#..#...........#..#..#. #########.........######### #.##.##.#.........#.##.##.# .#.....#...........#.....#. ###...###.........###...### #.#...#.#.........#.#...#.# ```

## 样例 #1

### 输入

```
3 3 3
.#.
###
#.#```

### 输出

```
20```

## 样例 #2

### 输入

```
3 3 3
###
#.#
###```

### 输出

```
1```

## 样例 #3

### 输入

```
11 15 1000000000000000000
.....#.........
....###........
....####.......
...######......
...#######.....
..##.###.##....
..##########...
.###.....####..
.####...######.
###############
#.##..##..##..#```

### 输出

```
301811921```

# 题解

## 作者：CYJian (赞：20)

## AGC003F

这题。。一开始没看到「保证黑格四连通」，自闭了很久。。

然后发现有这个条件之后好办很多了。

首先有了这个条件，我们就可以分三种情况讨论：

1. 这个东西上下拼接、左右拼接都可以拼成一个联通块：显然答案是 $1$
2. 这个东西上下拼接、左右拼接都不可以拼成一个联通块：显然答案是 $c^{k-1}$，其中 $c$ 为图中黑点个数。
3. 这个东西 上下拼接 或者 左右拼接 能拼成一个联通块（仅满足一个条件）：

这里问题就稍稍复杂一些了。

首先发现两个问题是等价的，所以这里只讨论左右拼接联通的情况：

我们先观察样例一的二级分形图：（已经手动分块）

![](https://cdn.luogu.com.cn/upload/image_hosting/pd8grhjm.png)

容易发现，联通块个数可以简单的表示为：原图的 黑点个数 - 左右相邻两个都是黑格的对数。

然后我们把这个图当成原图，再放入一开始给出的图中，得到的新图的联通块个数也可以用上面这个表达式表示！

然后我们就发现，答案就是：$k-1$ 级分形图中 黑点的个数 - 左右相邻两个都是黑格的对数。

黑点的个数很好求，就是 $c^{k-1}$。但是 相邻两个都是黑点的对数 比较难求。

我们考虑继续观察上图，不难发现，在每个块里头，都会有原图的 相邻黑点对数 的贡献。然后在边界上也会多出一些贡献。多出来的贡献恰好是 相邻黑点对数 $\times$ 左右拼接边界上相邻黑点对数。

然后这样子我们就可以得到新图的 相邻黑点对数 了。

但是现在又多了一个麻烦：左右拼接边界上的相邻黑点对数怎么算？

我们发现，只有可能在原来 左右拼接边界相邻的行 代表的一串图的边界才可能有贡献。所以这个点对数就等于原图的这个点对数的平方。

如果我们设 $a$ 为 相邻黑点对数， $b$ 为 左右拼接边界相邻的黑点对数，$c$ 为黑格数，那么上面的关系恰好可以写成矩阵连乘的形式：

$$ \begin{bmatrix} c & a\\ 0 & b \end{bmatrix}^{k-1}$$

然后写个矩阵快速幂就好了。

${\rm Code}$：

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int __SIZE = 1 << 18;
char ibuf[__SIZE], *iS, *iT;

#define ge (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, __SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++)
#define ri read_int()
#define rl read_ll()
#define FILE(s) freopen(s"in", "r", stdin), freopen(s"out", "w", stdout)

template<typename T>
inline void read(T &x) {
	char ch, t = 0; x = 0;
	while(!isdigit(ch = ge)) t |= ch == '-';
	while(isdigit(ch)) x = x * 10 + (ch ^ 48), ch = ge;
	x = t ? -x : x;
}
inline int read_int() { int x; return read(x), x; }
inline ll read_ll() { ll x; return read(x), x; }

template<typename T>
inline void chkmin(T&a, T b) { a = a < b ? a : b; }

const int mod = 1e9 + 7;

int s[1010][1010];

struct Node {
	int a, b, c;

	Node() {}
	Node(int a, int b, int c):a(a), b(b), c(c) {}

	friend Node operator * (Node a, Node b) {
		Node c;
		c.a = 1LL * a.a * b.a % mod;
		c.b = (1LL * a.a * b.b + 1LL * a.b * b.c) % mod;
		c.c = 1LL * a.c * b.c % mod;
		return c;
	}
};

inline Node ksm(Node a, ll k) {
	Node s(1, 0, 1);
	while(k) {
		if(k & 1) s = s * a;
		a = a * a, k >>= 1;
	} return s;
}

inline int fsp(int x, ll k) {
	int s = 1;
	while(k) {
		if(k & 1) s = 1LL * s * x % mod;
		x = 1LL * x * x % mod, k >>= 1;
	}
	return s;
}

int main() {
#ifdef LOCAL
	FILE("");
#endif
	int n = ri, m = ri; ll k = rl;
	if(!k) return puts("1"), 0;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++) {
			char c = ge;
			while(c != '.' && c != '#') c = ge;
			s[i][j] = c == '#';
		}
	int ud = 0, lr = 0, c = 0, UD = 0, LR = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++) {
			c += s[i][j];
			if(i == 1) UD += s[1][j] && s[n][j];
			else ud += s[i][j] && s[i - 1][j];
			if(j == 1) LR += s[i][1] && s[i][m];
			else lr += s[i][j] && s[i][j - 1];
		}
	if(!UD && !LR) printf("%d\n", fsp(c, k - 1));
	else if(UD && LR) puts("1");
	else {
		Node f;
		if(UD) f = ksm(Node(c, ud, UD), k - 1);
		else f = ksm(Node(c, lr, LR), k - 1);
		printf("%d\n", (f.a - f.b + mod) % mod);
	}
	return 0;
}
```

upd: 感谢 M_sea 神仙提出一点小问题，已修改

---

## 作者：ez_lcw (赞：11)

先说一下下文会用到的定义或称呼的意思：

- 称单位分形为题目给出的 $1$ 级分形。

- 称一种分形左右联通，则说明将两个这种分形左右放在一起时，至少有一个连通块是跨越这两个分形的。

	设一种分形的左右联通个数 $side_0$ 表示，当两个这种分形左右放在一起时，所贡献的连通块个数，即有多少个连通块是跨越左右两个分形的。显然，当一种分形左右不连通时，$side_0=0$。
    
   设一种分形的 $tot_0$ 表示有多少组黑色单元格是左右相邻的。
   
   比如下图中，这个分形是左右联通的，且 $side_0=2$，$tot_0=9$。
   
   ![](https://cdn.luogu.com.cn/upload/image_hosting/6m8krc53.png)
   
- 同理定义：一种分形的上下联通个数 $side_1$ 和 $tot_1$。

- 设单位分形中的黑色单元格数为 $cnt$，如上面那张图的 $cnt=16$。

看到 $k\leq10^{18}$ 容易想到这题是结论或者快速幂，想了一会发现了以下的两个结论：

- 如果单位分形的 $side_0$ 或 $side_1$ 都大于 $0$，即单位分形上下和左右都联通，那么 $k$ 级的联通块数肯定是 $1$。

- 如果单位分形的 $side_0$ 或 $side_1$ 都等于 $0$，即单位分形上下和左右都不联通，那么 $k$ 级的联通块数肯定是 $cnt^{k-1}$。

那么剩下的情况只有单位分形左右联通或者上下联通了。

这两种情况是类似的，现在只拿左右联通的情况来讨论：

考虑设计 $dp$，然后用矩阵快速幂来优化。

设 $ans_i$ 表示 $i$ 级分形时的答案，$s_i$ 表示 $i$ 级分形的 $side_0$，$uside_0$ 表示单位分形左右拼接之后相邻的黑块对数。

容易得到状态转移方程：

$$
\begin{aligned}
ans_i&=\underbrace{cnt\times ans_{i-1}}_{\text{上一级分形复制 $cnt$ 遍}}-\underbrace{tot\times s_{i-1}}_{\text{减去多出来的连通块个数}}\\
s_i&=s_{i-1}\times uside_0
\end{aligned}
$$

更详细的解释自己画个图就好了。

然后就可以用 $ans_1$、$s_1$ 设计初始矩阵，用 $cnt$、$tot$、$uside$ 设计转移矩阵，最后矩阵快速幂得到 $ans_k$。

由于矩阵的大小是常数级别的，所以总时间复杂度 $O(\log k)$。

代码如下：

```cpp
#include<bits/stdc++.h>

#define N 1010
#define ll long long
#define mod 1000000007

using namespace std;

struct Matrix
{
	ll a[3][3];
	Matrix(){memset(a,0,sizeof(a));}
	void init(){a[1][1]=a[2][2]=1;}
}st,trans;

Matrix operator * (Matrix a,Matrix b)
{
	Matrix c;
	for(int i=1;i<=2;i++)
		for(int j=1;j<=2;j++)
			for(int k=1;k<=2;k++)
				c.a[i][j]=((c.a[i][j]+a.a[i][k]*b.a[k][j])%mod+mod)%mod;
	return c;
}

Matrix poww(Matrix a,ll b)
{
	Matrix ans;
	ans.init();
	while(b)
	{
		if(b&1) ans=ans*a;
		a=a*a;
		b>>=1;
	}
	return ans;
}

int n,m;
int cnt,tot[2],uside[2];//0左右相连，1上下相连 
char s[N][N];
bool tag;
ll k;

ll fastpow(ll a,ll b)
{
	ll ans=1;
	while(b)
	{
		if(b&1) ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}

int main()
{
	scanf("%d%d%lld",&n,&m,&k);
	for(int i=1;i<=n;i++)
		scanf("%s",s[i]+1);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(s[i][j]=='#')
			{
				cnt++;
				if(j>1) tot[0]+=(s[i][j-1]=='#');
				if(i>1) tot[1]+=(s[i-1][j]=='#');
			}
		}
	}
	for(int i=1;i<=n;i++) uside[0]+=(s[i][1]=='#'&&s[i][m]=='#');
	for(int i=1;i<=m;i++) uside[1]+=(s[1][i]=='#'&&s[n][i]=='#');
	if(uside[0]&&uside[1])
	{
		puts("1");
		return 0;
	}
	if(!uside[0]&&!uside[1])
	{
		printf("%lld\n",fastpow(cnt,k-1));
		return 0;
	}
	tag=uside[1];
	st.a[1][1]=1;
	st.a[1][2]=1;
	trans.a[1][1]=cnt;
	trans.a[2][1]=-tot[tag];
	trans.a[2][2]=uside[tag];
	Matrix ans=st*poww(trans,k-1);
	printf("%lld\n",ans.a[1][1]);
	return 0;
}
/*
....#....
...###...
...#.#...
.#..#..#.
#########
#.##.##.#
.#.....#.
###...###
#.#...#.#
*/
```

---

## 作者：zhiyangfan (赞：6)

推销博客：[qwq](https://www.luogu.com.cn/blog/i-am-zhiyangfan/atcoder-grand-contest-003-bu-ti-zong-jie)
### 题意
给出一个 $H\times W$ 的网格图，每一格都是黑色或白色，所有的黑色是格子是四连通的，也就是说只横平竖直的移动可以使任意黑色格子之间相互到达。本题中， $\rm fractals$ 分形的定义如下：

- $0$ 级分形是一个 $1\times 1$ 的网格，其中唯一的格子为黑色。
- $k+1$ 级分形是由 $H\times W$ 个 $k$ 级分形大小的网格图组成的，如果在题目中给出的网格图中，对应的位置为黑色，则该位置放上 $k$ 级分形，如果为白色，则该位置全部格子都是白色。

给出整数 $k$ ，求 $k$ 级分形中，黑色格子的连通块个数，答案对 $10^9+7$ 取模。( $1\le H,W\le1000,0\le k\le10^{18}$ ，给出的网格图中至少有一个黑色格子)

### 题解
我们称一个网格是水平连通的，当它存在一行使得这一行最左边和最右边的的格子均为黑色，称一个网格是竖直连通的当它存在一列使得这一列最上边和最下边的格子均为黑色。那当一个网格既水平连通又竖直连通，显然不管 $k$ 等于多少，所有的黑色格子一定是全部连通的，所以这种情况下答案一定是 $1$ 。当一个网格既不水平连通也不竖直连通，则每当分形等级增长时，连通块个数都会乘以 $a$ ，其中 $a$ 是题目给出的网格图中黑色格子的数量，所以答案为 $a^{k-1}$ 。

而对于只水平连通或者只竖直连通的情况，就比较复杂了。不失一般性，我们假设这个网格是水平连通的，但不竖直连通。对于在每个 $k-1$ 级分形中的黑色格子，我们要放一个题目中给定的网格图（分形定义的另一种表述方法），这样黑色格子的连通块个数就会 $+1$ 。但如果 $k-1$ 级分形中有两个黑色格子水平相邻的话，这两个格子对应的网格就会在同一个连通块内了。所以答案就是 $a-b$ ，其中 $a$ 是题目给出的网格图中黑色格子的数量，$b$ 是水平相邻的黑色格子对数。

但注意到 $k$ 非常大，加上这个递推的形式，可以想到列出  $\rm dp$ 式子，然后用矩阵快速幂来优化一下。我们设 $f_i$ 表示 $i$ 级分形的答案，$s_i$ 表示 $i$ 级分形最左列和最右列的连通块个数。则 $f_i=af_i-bs_{i-1}$ ，$s_i=cs_{i-1}$ （其中 $a$ 是题目给出的网格图中黑色格子的数量，$b$ 是水平相邻的黑色格子对数，$c$ 是满足最左端和最右端均为黑色的行数）。根据这个状态转移方程，我们有 $\begin{pmatrix}a&-b\\0&c\end{pmatrix}\begin{pmatrix}f_i\\s_i\end{pmatrix}=\begin{pmatrix}f_{i+1}\\s_{i+1}\end{pmatrix}$ ，所以最终答案就是 $\begin{pmatrix}f_k\\s_k\end{pmatrix}=\begin{pmatrix}a&-b\\0&c\end{pmatrix}^{k-1}\begin{pmatrix}f_1\\s_1\end{pmatrix}$ ，其中 $f_1=s_1=1$ 。

对于只竖直连通的情况，只需要把所有定义倒转一下就好，最终时间复杂度为统计的 $\mathcal{O}(HW)$ ，加上计算的 $\mathcal{O}(\log k)$ ，即 $\mathcal{O}(\log k+HW)$

```cpp
#include <cstdio>
const int N = 1e3 + 10, mod = 1e9 + 7;
typedef long long ll;
struct Matrix
{
    int n, m; ll a[4][4];
    Matrix operator*(const Matrix& X)
    {
        Matrix ret;
        ret.n = n; ret.m = X.m;
        for (int i = 1; i <= ret.n; ++i)
            for (int j = 1; j <= ret.m; ++j)
                ret.a[i][j] = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= X.m; ++j)
                for (int k = 1; k <= m; ++k)
                    ret.a[i][j] = 
                    ((ret.a[i][j] + a[i][k] * X.a[k][j] % mod)
                    % mod + mod) % mod;
        return ret;
    }
}A, B, I;
Matrix fpow(Matrix A, ll k)
{
    Matrix ret = I;
    while (k)
    {
        if (k & 1) ret = ret * A;
        A = A * A;
        k >>= 1;
    }
    return ret;
}
int fpow(int a, ll k)
{
    int ret = 1;
    while (k)
    {
        if (k & 1) ret = 1ll * ret * a % mod;
        a = 1ll * a * a % mod;
        k >>= 1;
    }
    return ret;
}
//0:vertically connected, 1:horizontally connected
char mp[N][N]; int a, b[2], c[2];
inline void init(int tag)
{
    A.n = A.m = I.n = I.m = 2;
    I.a[1][1] = I.a[2][2] = 1;
    A.a[1][1] = a; A.a[1][2] = -b[tag];
    A.a[2][1] = 0; A.a[2][2] = c[tag];
    B.n = 2; B.m = 1;
    B.a[1][1] = B.a[2][1] = 1;
}
int main()
{
    int n, m; ll k; scanf("%d%d%lld", &n, &m, &k);
    for (int i = 1; i <= n; ++i)
        scanf("%s", mp[i] + 1);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (mp[i][j] == '#')
            {
                ++a;
                if (j > 1) b[0] += (mp[i][j - 1] == '#');
                if (i > 1) b[1] += (mp[i - 1][j] == '#');
            }
    for (int i = 1; i <= n; ++i)
        c[0] += (mp[i][1] == '#' && mp[i][m] == '#');
    for (int i = 1; i <= m; ++i)
        c[1] += (mp[1][i] == '#' && mp[n][i] == '#');
    //vertically connected and horizontally connected
    if (c[0] && c[1]) { printf("1\n"); return 0; }
    //not vertically connected and not horizontally connected
    if (!c[0] && !c[1])
    { printf("%d\n", fpow(a, k - 1)); return 0; }
    //tag = 1 if c[1]>0, 0 if c[1]=0
    int tag = !!c[1]; init(tag);
    B = fpow(A, k - 1) * B;
    printf("%lld\n", B.a[1][1]);
    return 0;
}
```

---

## 作者：灰鹤在此 (赞：6)

题意：给定一个联通的图案，我们称之为 $1$ 级图案，然后每增加 $1$ 级每一个 # 都会被替换成上一级的图案，然后长宽放大原来的长宽倍，问有多少个联通块。

我们对于三种情况进行讨论：

1. 如果一个图案有下一级时使得上下和左右都可以连接的块，那么它的下一级的联通块个数一定是 $1$。

2. 如果一个图案下一级时都没有使得上下和左右可以连接的块，那么它的下一级的联通块个数就是：$\text{块的个数}^{k-1}$。

3. 只有上下或左右有使下一级可以连接的块：

设 $n$ 为长，$m$ 为宽，$cnt$ 为原图形黑块的数量。

首先分析一下第一个样例，我们发现从 $1$ 开始，答案可以被我们分解成：$1->1\times6-2^1=4->4\times6-2^2=20->20\times6-2^3=112->112\times6-2^4=656$……

然后我们观察一下第一个样例它的图案，发现如果这个图形某一行最左边是 # 且最右边是 #,那么之后的拓展图案中这几个地方也是连在一起的，如果一边有而另一边没有，那么拓展图案中这几个地方一定是分开的。

所以我们得出了一条结论：联通块的个数和下一级时使得上下或左右可以连接的块的个数有关系。

于是我们用 ```up_down_connect``` 来代表下一级时使得上下可以连接的块的个数，用 ```left_right_connect``` 来代表下一级时使得左右可以连接的块的个数。

如果这个图案中有块左右相邻且有下一级时使得左右可以连接的块，那么它扩大一级之后横向必定还是联通的。否则横向将会增加 $(\text{所有的块数}-\text{上下相邻且有下一级时使得上下可以连接的块的个数})$。我们考虑上下的时候和左右一样。

所以联通块的个数和下一级时使得上下或左右可以连接的块的个数以及左右或上下相邻的块的个数有关。

我们设上下相邻的块的个数为 ```up_down_next```，左右相邻的块的个数为 ```left_right_next```。

比如样例 $1$ 中：
```
.#.
###
#.#
```
它的 ```up_down_connect``` 是 $0$，```left_right_connect``` 是 $2$，```up_down_next``` 是 $3$，```left_right_next``` 是 $2$，总块数是 $6$，联通块个数为 $1$。

$2$ 级图案是：
```
....#....
...###...
...#.#...
.#..#..#.
#########
#.##.##.#
.#.....#.
###...###
#.#...#.#
```
它的 ```up_down_connect``` 是 $0$，```left_right_connect``` 是 $4$，```up_down_next``` 是 $18$，```left_right_next``` 是 $16$，总块数是 $36$，联通块个数为 $4$。

于是我们可以推出每一级每一个量之间的转化公式：

- $up\_down\_connext_i=up\_down\_connext_{i-1}\times up\_down\_connext_1$

分析一下就会发现下一级 $up\_down\_connext$ 会翻倍，而且翻的是它的原式次数倍。

- $left\_right\_connext_i=left\_right\_connext_{i-1}\times left\_right\_connext_1$

同理。

- 左右可拼接的情况：$ans_i=ans_{i-1}\times cnt-left\_right\_next_1\times left\_right\_connect_{i-1}$

本应生成的联通块个数减去又连在一起的联通块个数。

而又连在一起的联通块个数可以看成原来这个图案左右相邻的地方，每一个地方都有 $left\_right\_connect_{i-1}$ 块合并了。

- 上下可拼接的情况：$ans_i=ans_{i-1}\times cnt-up\_down\_next_1\times up\_down\_connect_{i-1}$

同理。

**通项形式：**

- $ans_i=ans_{i-1}\times cnt-next_1\times connect_{i-1}$

- $connect_i=connect_{i-1}\times connect_1$

因为 $k\le 10^{18}$，而且这个递推式子是线性的，不难想到用矩阵快速幂。

接下来就是构造矩阵快速幂，我们把要算的东西放在里面：$\begin{bmatrix}ans_n\\connect_n\end{bmatrix}$。

然后我们根据我们的公式来构造矩阵快速幂：

$$\begin{bmatrix}ans_n\\connect_n\end{bmatrix}=\begin{bmatrix}a&b\\c&d\end{bmatrix}\begin{bmatrix}ans_{n-1}\\connect_{n-1}\end{bmatrix}$$

所以我们要构造的矩阵快速幂就是：$\begin{bmatrix}cnt&-next_1\\0&connect_1\end{bmatrix}$。

于是这个东西可以用矩阵快速幂来实现。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MaxN=1e3+5;
const long long mod=1e9+7;
template<typename T>
inline T qpow(T x,long long y){
	T res=1;
	while(y){
		if(y&1){
			res=res*x%mod;
		}
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
template<typename T>
inline T Plus(T x){
	if(x>=0){
		return x<mod?x:x-mod;
	}
	return x+mod;
}
template<typename T>
inline T mul(T x,T y){
	return x*y%mod;
}
struct Matrix{
	long long a[3][3];
	Matrix(){
		memset(a,0,sizeof(a));
	}
	inline void init(){
		for(int i=1;i<=2;i++){
			a[i][i]=1;
		}
	}
	long long * const operator [] (int n){
		return a[n];
	}
	friend Matrix operator * (Matrix a,Matrix b){
		Matrix c;
		for(int i=1;i<=2;i++){
			for(int j=1;j<=2;j++){
				for(int k=1;k<=2;k++){
					c[i][j]=Plus(c[i][j]+mul(a[i][k],b[k][j]));
				}
			}
		}
		return c;
	}
	Matrix & operator *= (Matrix x){
		return *this=*this*x;
	}
	Matrix qpow(long long y){
		Matrix res;
		res.init();
		while(y){
			if(y&1){
				res*=*this;
			}
			*this*=*this;
			y>>=1;
		}
		return res;
	}
}a,b;
long long n,m,k,left_right_connect,up_down_connect,left_right_next,up_down_next,cnt;
char s[MaxN][MaxN];
int main(){
	scanf("%lld%lld%lld",&n,&m,&k);
	for(int i=1;i<=n;i++){
		scanf("%s",s[i]+1);
		left_right_connect+=(s[i][1]==s[i][m]&&s[i][1]=='#');
		for(int j=1;j<=m;j++){
			if(s[i][j]=='#'){
				cnt++;
				left_right_next+=(s[i][j-1]=='#');
				up_down_next+=(s[i-1][j]=='#');
			}
		}
	}
	for(int i=1;i<=m;i++){
		up_down_connect+=(s[1][i]==s[n][i]&&s[1][i]=='#');
	}
	if(left_right_connect&&up_down_connect){
		puts("1");
	}else if(!left_right_connect&&!up_down_connect){
		printf("%lld\n",qpow(cnt,k-1));
	}else{
		a[1][1]=a[2][1]=1;
		b[1][1]=cnt;
		if(up_down_connect){
			b[1][2]=-up_down_next;
			b[2][2]=up_down_connect;
		}else{
			b[1][2]=-left_right_next;
			b[2][2]=left_right_connect;
		}
		a=b.qpow(k-1)*a;
		printf("%lld\n",a[1][1]);
	}
	return 0;
}
```

---

## 作者：Lucky_Xiang (赞：5)

# 题目

[AGC003F](https://www.luogu.com.cn/problem/AT_agc003_f)

# 思路

先定义一些东西，方便讲解。

- 假如两个 $1$ 级分形按照**左右拼接**能够组成一个连通块，则它们是**左右连通**的。

- 假如两个 $1$ 级分形按照**上下拼接**能够组成一个连通块，则它们是**上下连通**的。

- 设在 $k$ 级分形中：
	
   1. 有 $x_k$ 个格子是黑色的。

	2. 有 $t_k$ 对**左右相邻**的格子同时为黑色。

	3. 有 $f_k$ 行的**最左端**和**最右端**都是黑色。

## 分形

将一个 $n-1$ 级分形变换为 $n$ 级分形，有以下两种方法：

1. 将 $n-1$ 级分形视为一个整体，并按照 $1$ 级分形的形状**摆放**。这种方法不适合分析这道题。

2. 将 $n-1$ 级分形的每一个黑色方格**替换**为 $1$ 级分形。下文将用这种方法分析。

## 特判

若 $K\le1$，则答案为 $1$。

假如给定的 $1$ 级分形既不是**左右连通**又不是**上下连通**，则最终答案是 $x^{K-1}_1$。

假如给定的 $1$ 级分形既是**左右连通**又是**上下连通**，则最终答案是 $1$。

## 正题

对于剩下的情况，不妨假设该 $1$ 级分形只满足**左右连通**。

在将 $n$ 级分形的每一个黑色方格**替换**为 $1$ 级分形的过程中，因为题目保证 $1$ 级分形连通，所以 $n+1$ 级分形的连通块的数量为 $x_{n}-t_{n}$。那么，只要能够求出 $x_{K-1}$ 和 $t_{K-1}$，题目就做完了。

发现只靠 $x$ 和 $t$ 还不能维护这些信息。不妨一起维护 $f$。

那么可以列出式子：

- $x_n=x_{n-1}x_1$

- $t_n=x_{n-1}t_1+t_{n-1}f_1$

- $f_n=f_{n-1}f_1$

把 $x,t,f$ 压进矩阵，用矩阵快速幂维护即可。

$$\begin{bmatrix} x_{n-1}&t_{n-1} \\ 0&f_{n-1} \end{bmatrix} \times \begin{bmatrix} x_1&t_1 \\ 0&f_1 \end{bmatrix}=\begin{bmatrix} x_n&t_n \\ 0&f_n \end{bmatrix}$$

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mn=1010;
const int mod=1000000007;
int n,m;
LL K;
char s[mn][mn];
int x,f,t;
int cnt1,cnt2;
void init()
{
    f=cnt1+cnt2;
    if(cnt1)
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<m;j++)t+=(s[i][j]=='#' && s[i][j+1]=='#');
        }
    }
    if(cnt2)
    {
        for(int i=1;i<n;i++)
        {
            for(int j=1;j<=m;j++)t+=(s[i][j]=='#' && s[i+1][j]=='#');
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)x+=(s[i][j]=='#');
    }
}
struct MATRIX
{
    LL a[2][2];
};
MATRIX A,B;
MATRIX operator *(const MATRIX &A,const MATRIX &B)
{
    MATRIX C;
    memset(C.a,0,sizeof(C.a));
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<2;j++)
        {
            for(int k=0;k<2;k++)
            {
                C.a[i][j]+=A.a[i][k]*B.a[k][j]%mod;
                C.a[i][j]%=mod;
            }
        }
    }
    return C;
}
LL solve()
{
    K-=2;
    A.a[0][0]=x; A.a[0][1]=t; A.a[1][1]=f;
    B=A;
    while(K)
    {
        if(K&1)B=B*A;
        A=A*A;
        K>>=1;
    }
    return (B.a[0][0]-B.a[0][1]+mod)%mod;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin>>n>>m>>K;
    for(int i=1;i<=n;i++)cin>>(s[i]+1);
    for(int i=1;i<=n;i++)cnt1+=(s[i][1]=='#' && s[i][m]=='#');
    for(int i=1;i<=m;i++)cnt2+=(s[1][i]=='#' && s[n][i]=='#');
    if(K<=1 || (cnt1 && cnt2))
    {
        cout<<1<<endl;
        return 0;
    }
    init();
    cout<<solve()<<endl;
    return 0;
}
```

---

## 作者：zhylj (赞：4)

这是一个没有矩阵乘法的做法。

记给定图形中 ``#`` 的数量为 $b$，注意到若给定图形上下拼起来连通，左右拼起来也连通，那么连通块数为 $b^{k-1}$（特判 $k=0$ 的情况）。若都不连通，则连通块数为 $1$。

比较棘手的情况是上下、左右之一连通。不难通过旋转矩形把情况都转化为左右连通。

注意到在只有左右连通时，所有的连通块必然都形如若干个 $1$ 级分形连成的链，且所有相邻的一级分形都有着相同的公共边数，不妨记为 $e_m$，再记所有有公共边的**左右**格子对的个数为 $e_o$，假如我们能求出最 $k-1$ 层分形有着公共边的左右格子对的个数 $e_f$，那么 $k$ 层分形用于连接相邻的 $1$ 级分形的边数就为 $e_f$，于是连通块就相比完全不连通减少了 $e_f$ 个，即答案为 $b^{k-1}-e_f$。

我们只需考虑 $e_f$ 如何求得，考虑最终分形中的一个格子是怎么来的：在每一层分形中选择一个格子展开。于是一对相邻格子在每一层分形的位置关系必然依次形如：同一个下一层分形、相邻的下一层分形、相邻的下一层分形的边界处。

枚举在哪一层进入了不同的下一层分形，即可得到：
$$
e_f = \sum_{i=0}^{k-2} b^ie_oe_m^{k-i-2}
$$
不难发现是一个等比数列，可以直接计算，时间复杂度 $\mathcal O(\log k)$。

```
const int N = 1e3 + 5, MOD = 1e9 + 7;

int QPow(int a, ll b) {
	int ret = 1, bas = (a % MOD + MOD) % MOD;
	for(; b; b >>= 1, bas = 1LL * bas * bas % MOD)
		if(b & 1) ret = 1LL * ret * bas % MOD;
	return ret;
}

int H, W, b; ll k;
char s[N][N];

int S(int p, ll k) {
	if(p == 1) return k % MOD;
	return 1LL * (QPow(p, k + 1) - 1 + MOD) * QPow(p - 1, MOD - 2) % MOD;
}
int Solve() {
	int e_o = 0, e_m = 0, e_f, ret;
	for(int i = 1; i <= H; ++i) {
		if(s[i][1] == '#' && s[i][W] == '#') ++e_m;
		for(int j = 1; j < W; ++j)
			if(s[i][j] == '#' && s[i][j + 1] == '#') ++e_o;
	}
	e_f = S(1LL * b * QPow(e_m, MOD - 2) % MOD, k - 2);
	e_f = 1LL * e_f * e_o % MOD * QPow(e_m, k - 2) % MOD;
	ret = (QPow(b, k - 1) - e_f + MOD) % MOD;
	return ret;
}

int main() {
	rd(H, W, k);
	for(int i = 1; i <= H; ++i) {
		scanf("%s", s[i] + 1);
		for(int j = 1; j <= W; ++j)
			if(s[i][j] == '#') ++b;
	}
	bool up_dn = false, lf_rt = false;
	for(int i = 1; i <= W; ++i)
		if(s[1][i] == '#' && s[H][i] == '#')
			up_dn = true;
	for(int i = 1; i <= H; ++i)
		if(s[i][1] == '#' && s[i][W] == '#')
			lf_rt = true;
	if((up_dn && lf_rt) || (k <= 1)) {
		printf("1\n");
		return 0;
	}
	if(!up_dn && !lf_rt) {
		printf("%d\n", QPow(b, k - 1));
		return 0;
	}
	if(up_dn) {
		for(int i = 1; i <= std::max(H, W); ++i)
			for(int j = 1; j <= i; ++j)
				std::swap(s[i][j], s[j][i]);
		std::swap(H, W);
	}
	printf("%d\n", Solve());
	return 0;
}
```



---

## 作者：lzqy_ (赞：2)

呃呃呃找回点信心，远古场还是比较简单的。

主要记录思考过程。

发现问题的瓶颈在于将 `#` 扩展成一个基准矩形 $T$ 后的联通情况，而这本质上是一个将 $T$ 看作各点的四连通，只是不一定四个方向都连通。

观察到一个很好的性质，**即 $\forall x>1$，$x$ 级分形图的四联通状态是相同的，且上下连通状态和左右连通状态分别相同**（以下称为纵向连通和横向连通）。

进一步发现，若横纵都不连通，答案为 $c_1^{k-1}$，其中 $c_1$ 表示 `#` 数量；若横纵都连通，答案为 $1$。因此只用考虑横向连通的情况即可（纵向连通等价）。而横向连通，纵向不连通意味着行与行之间是独立的，于是我们成功把问题降维了。

考虑变成一维之后怎么做。此时每一行被分成了多个连通块（形如 `###.....#...##.#`）。如果假设每一行首尾元素**不同时**为 `#`（防止多个行并列产生影响），那么答案即为 $c_2c_1^{k-2}$，其中 $c_2$ 表示每行连通块个数之和。这个式子也很好理解，即上一层分形图的每一个 `#` 都会生长成 $c_2$ 个连通块且互不影响。

关键在于首尾元素同时为 `#` 的情况。观察到这种情况下，目前层的连通块个数和上一层的连通块个数紧密相关，此时直接写出表达式是困难的。因此，考虑刻画递推式统一表达两种情况（首尾不同时为 `#` 的表达式显然也可以写成递推式）。

设 $f_{i,0}$ 表示 $i$ 层分形图的 `#` 个数，$f_{i,1}$ 表示 $i$ 层分形图每行连通块个数之和，则有递推式：

$$\begin{cases}f_{i,0}=c_1f_{i-1,0}\\f_{i,1}=(c_2-c_3)f_{i-1,0}+c_3f_{i-1,1}\end{cases}$$

其中 $c_3$ 表示首尾同时为 `#` 的行数。

$f_{i,0}$ 就是首尾不同时为 `#` 的递推，$f_{i,1}$ 就是先考虑 $(c_2-c_3)$ 个连通块的贡献（等价于首尾不同时为 `#`），然后再加上首尾同时为 `#` 的额外贡献。

矩阵快速幂转移即可。时间复杂度 $O(n^2+\log k)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define il inline
using namespace std;
const int mod=1e9+7;
const int maxn=1010;
il int read(){
	int x=0;
	char c=getchar();
	for(;c!='#'&&c!='.';c=getchar());
	return c=='#';
}
il void ad(int &x,int y){if((x+=y)>=mod)x-=mod;}
il void de(int &x,int y){if((x-=y)<0)x+=mod;}
il void mul(int &x,int y){x=1ll*x*y%mod;}
struct Matrix{
	int a[2][2];
	il Matrix operator *(Matrix x){
		Matrix y;
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++){
				y.a[i][j]=0;
				for(int k=0;k<2;k++)
					ad(y.a[i][j],1ll*a[i][k]*x.a[k][j]%mod);
			}
		return y;
	}
	il void init(){a[0][1]=a[1][0]=0,a[0][0]=a[1][1]=1;}
}M,Beg;
il int fpow(int n,ll m,int x=1){
	for(;m;m>>=1,n=1ll*n*n%mod)
		if(m&1) x=1ll*x*n%mod;
	return x;
}
il Matrix qpow(Matrix n,ll m){
	Matrix x; x.init();
	for(;m;m>>=1,n=n*n)
		if(m&1) x=x*n;
	return x;
}
int n,m,c1,c2,c3,ans;
int b[maxn][maxn];
int a[maxn][maxn];
ll k;
int main(){
	scanf("%d%d%lld",&n,&m,&k);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			a[i][j]=read();
//	for(int i=1;i<=n;i++,printf("\n"))
//		for(int j=1;j<=m;j++)
//			printf("%d ",a[i][j]);
	bool f1=0,f2=0;
	for(int j=1;j<=m;j++) f1|=(a[1][j]&&a[n][j]);
	for(int i=1;i<=n;i++) f2|=(a[i][1]&&a[i][m]);
	if(k<=1||(f1&&f2)) return printf("1\n"),0;
	if(!f1&&!f2){
		int cn=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				cn+=a[i][j];
		printf("%d\n",fpow(cn,k-1));
		return 0;	 
	}
	if(f1){
//		puts("in"); 
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				b[j][i]=a[i][j];
		swap(n,m);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				a[i][j]=b[i][j];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			while(j<=m&&!a[i][j]) j++;
			if(a[i][j]) c2++;
			while(j<=m&&a[i][j]) c1++,j++;	
		}
//		printf("!!!!%d,%d\n",a[i][1],a[i][m]);
		if(a[i][1]&&a[i][m]) c3++;
	}
//	printf("(%d,%d,%d)\n",c1,c2,c3);
	Beg.a[0][0]=Beg.a[0][1]=1;
	M.a[0][0]=c1,M.a[1][0]=0;
	M.a[0][1]=c2-c3,M.a[1][1]=c3;
	Beg=Beg*qpow(M,k-1);
	printf("%d\n",Beg.a[0][1]);
	return 0;
}
```

---

## 作者：tzc_wk (赞：2)

[Atcoder 题面传送门](https://atcoder.jp/contests/agc002/tasks/agc002_f) & [洛谷题面传送门](https://www.luogu.com.cn/problem/AT2000)

Yet another AGC F，然鹅这次就没能自己想出来了……

首先需注意到题目中有一个条件叫做“黑格子组成的连通块是四联通的”，这意味着我们将所有黑格都替换为题目中 $H\times W$ 的标准型之后，黑格（标准型）内部是不会对连通块个数产生贡献的，产生贡献的只可能是黑格与黑格之间的边不产生连通块。如果我们记 $G_{\text{h}}$ 两个标准型横着拼在一起得到的 $H\times 2W$ 的图形，$G_{\text{v}}$ 为两个标准型竖着拼在一起得到的 $2H\times W$ 的图形，那么稍微分析一下即可得到以下性质：

- 如果 $G_{\text{h}},G_{\text{v}}$ 中都只有一个连通块，那么最终得到的 $k$ 级分形也只有一个连通块。因为对于原来的标准型中的相邻两个黑格，由于 $G_{\text{h}},G_{\text{v}}$ 连通，所以将这两个黑格分别替换为标准型后，这两个黑格所表示的连通块依旧连通，又因为这个标准型本来就是连通图，所以进行一次迭代（将黑格替换为标准型）后，该图中所有黑格表示的标准型都是连通的，也就是说该标准型的二级分形为连通图。又 $\because G_{\text{h}}$ 连通，仿照上述推理过程可知 $G_{\text{h}}$ 进行一次迭代后之后，所得的分形仍是连通图，即将该标准型的二级分形左右拼接后，可以得到连通形，$G_{\text{v}}$ 也同理，如此归纳下去即可证明。
- 如果 $G_{\text{h}},G_{\text{v}}$ 中都有两个连通块，那么最终得到的 $k$ 级分形中有 $\text{标准型中黑格个数}^{k-1}$ 个黑格，这个好办，$G_{\text{h}},G_{\text{v}}$ 都有两个连通块，这意味着对于标准型中的任意两个相连的黑格，将它们分别替换为标准型后，彼此之间互不连通，也就是每个黑格各自成一个连通块，记原来的标准型中黑格个数为 $C$，那么根据之前的推论，二级分形中有 $C$ 个连通块，$C^2$ 个黑格，三级分形中有 $C^2$ 个连通块，$C^3$ 个黑格，以此类推。

比较棘手的是 $G_{\text{h}},G_{\text{v}}$ 刚好一个连通，一个不连通的情况。不妨设 $G_{\text{h}}$ 连通，$G_{\text{v}}$ 不连通。我们考虑探究一次迭代会对连通块个数产生什么影响。我们考虑使用一个并查集的思想，不妨假设所有黑格替换为的分形都单独成一个连通块，然后将能并的并起来，显然两个黑格表示的连通块能够并起来当且仅当它们左右相邻，而显然左右相邻的格子不会组成环，也就是说每次合并都是合法的，这样减少的连通块个数就是左右相邻的黑格个数，故一次迭代之后连通块的个数，就等于黑格个数减去左右相邻的黑格个数。

考虑怎样计算这个东西，设 $a_k$ 为 $k$ 级分形中左右相邻的黑格个数，$b_k$ 为 $k$ 级分形中的黑格个数，那么显然可以推出 $b$ 的递推式 $b_{k+1}=b_kb_1$，但是推出 $a$ 的递推式还有些困难。考虑将 $k$ 级分形替换为 $k+1$ 级分形后，左右相邻的黑格的来头，显然它可能是一个黑格替换为一个标准型分形后，内部出现左右相邻的黑格，这部分我们是可以计算的，为 $b_ka_1$，也有可能是本身左右相邻的黑格替换为标准型后，边界上出现左右相邻的黑格，我们发现这东西无法直接表示，那就设一下呗。再设 $c_k$ 为 $k$ 级分形中左右拼接的边界上左右相邻的黑格个数，设完之后这东西就很好表示了，为 $a_kc_1$，即 $a_{k+1}=b_ka_1+a_kc_1$。最后考虑 $c$ 的递推式，显然边界上相邻只可能是原来边界上相邻的黑格被替换为标准型后，每对相邻的黑格新多出 $c_1$ 对出来，即 $c_{k+1}=c_kc_1$。

最后看下数据范围……$10^{18}$，还有这么多递推式，那显然矩阵快速幂咯。稍微推推即可得到 $\begin{bmatrix}b_k&a_k\\0&c_k\end{bmatrix}\times\begin{bmatrix}b_1&a_1\\0&c_1\end{bmatrix}=\begin{bmatrix}b_{k+1}&a_{k+1}\\0&c_{k+1}\end{bmatrix}$，即 $\begin{bmatrix}b_k&a_k\\0&c_k\end{bmatrix}=\begin{bmatrix}b_1&a_1\\0&c_1\end{bmatrix}^k$，快速幂即可。

```cpp
const int MAXN=1e3;
const int MOD=1e9+7;
int n,m;ll k;
char s[MAXN+5][MAXN+5];
int qpow(int x,ll e){
	int ret=1;
	for(;e;e>>=1,x=1ll*x*x%MOD) if(e&1) ret=1ll*ret*x%MOD;
	return ret;
}
struct mat{
	ll a[2][2];
	mat(){memset(a,0,sizeof(a));}
	mat operator *(const mat &rhs){
		mat ret;
		for(int i=0;i<2;i++) for(int j=0;j<2;j++)
			for(int k=0;k<2;k++) ret.a[i][j]+=a[i][k]*rhs.a[k][j];
		for(int i=0;i<2;i++) for(int j=0;j<2;j++) ret.a[i][j]%=MOD;
		return ret;
	}
};
int main(){
	scanf("%d%d%lld",&n,&m,&k);if(!k) return puts("1"),0;
	for(int i=1;i<=n;i++) scanf("%s",s[i]+1);
	int ud_bor=0,lr_bor=0,ud_ins=0,lr_ins=0,cnt=0;
	for(int i=1;i<=m;i++) ud_bor+=(s[1][i]=='#'&&s[n][i]=='#');
	for(int i=1;i<=n;i++) lr_bor+=(s[i][1]=='#'&&s[i][m]=='#');
	for(int i=1;i<n;i++) for(int j=1;j<=m;j++) ud_ins+=(s[i][j]=='#'&&s[i+1][j]=='#');
	for(int i=1;i<=n;i++) for(int j=1;j<m;j++) lr_ins+=(s[i][j]=='#'&&s[i][j+1]=='#');
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cnt+=(s[i][j]=='#');
//	printf("%d %d %d %d %d\n",ud_bor,lr_bor,ud_ins,lr_ins,cnt);
	if(!ud_bor&&!lr_bor) printf("%d\n",qpow(cnt,k-1));
	else if(ud_bor&&lr_bor) printf("1\n");
	else{
		mat trs,res;res.a[0][0]=res.a[1][1]=1;--k;
		if(ud_bor) trs.a[0][0]=cnt,trs.a[0][1]=ud_ins,trs.a[1][1]=ud_bor;
		else trs.a[0][0]=cnt,trs.a[0][1]=lr_ins,trs.a[1][1]=lr_bor;
		for(;k;k>>=1,trs=trs*trs) if(k&1) res=res*trs;
		printf("%d\n",(res.a[0][0]-res.a[0][1]+MOD)%MOD);
	}
	return 0;
}
```



---

## 作者：翼德天尊 (赞：1)

>  It is possible to traverse from any black cell to any other black cell by just visiting black cells.

一定要好好读题啊啊啊，$0$ 级分形内一定只有一个联通块！！！

感觉应该是一道很经典的分形题目。

首先要明确的一点是，如果 $k$ 级分形中某一行的最左边和最右边都是黑色格子，那么在 $k+1$ 级分形中这两边本不相连的黑色联通块就可能会变得连通，我们可以定义该分形是【左右连通】的；同理，如果某一列的最上边和最下边都是黑色格子，我们定义该分形是【上下连通】的。

设 $1$ 级分形中黑色格子的个数为 $cnt$ 个，让我们来考虑两种简单的情况：

- 如果 $1$ 级分形既不【左右连通】也不【上下连通】，那么 $k$ 级分形中的连通块个数为 $cnt^{k-1}$。

- 如果 $1$ 级分形既【左右连通】又【上下连通】，那么 $k$ 级分形中的连通块个数一定为 $1$。

这两种情况的答案是显而易见的。

那么剩下的就只有【左右连通】和【上下连通】占其一的情况了。

两者处理方式相似，我们拿【左右连通】举例，注意此时已经含有【上下不连通】的隐含条件了。即对于大于 $1$ 级的分形，每一分形行都是独立的。

我们设初始左右连通的连通块数为 $tot$，初始左右连通的行数为 $cmt$，$k$ 级分形之后左右连通的块数为 $s_k$，则显然有： 
$$
s_1=tot\\
s_k=s_{k-1}\times cmt
$$
这很显然，由于每一分形行独立，对于原来左右连通的每一个连通块，在新一级分形中都会变成 $cmt$ 个连通块。

那么我们设 $k$ 级分形之后黑色连通块的个数为 $ans_k$，则每一次分形显然都会将原来的连通块个数复制 $cnt$ 份之后砍掉左右连通减去的块数。设 $1$ 级分形中左右相邻的黑色格子个数为 $pnt$，则有：
$$
ans_k=ans_{k-1}\times cnt-s_{k-1}\times pnt
$$
注意到 $k$ 很大，于是我们将这些变量写进一个矩阵，快速转移即可。

> **tips：分形的题目可以考虑以分形级别作为 dp 阶段进行转移。**

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1005;
const int mod=1e9+7;
int n,m;
ll k,cnt,tot1,tot2,cmt; 
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};
char ma[N][N],ma2[N][N];
bool vis[N][N],flag1,flag2;
struct node{
	ll a[2][2];
	node(){
		memset(a,0,sizeof(a));
	}
	void init(){
		a[0][0]=cnt,a[0][1]=0;
		a[1][0]=-tot2,a[1][1]=cmt;
	}
	void init2(){
		a[0][0]=a[1][1]=1;
		a[0][1]=a[1][0]=0;
	}
}S,Z;
node operator *(const node&x,const node&y){
	node z;
	for (int k=0;k<2;k++)
		for (int i=0;i<2;i++)
			for (int j=0;j<2;j++)
				z.a[i][j]=(z.a[i][j]+x.a[i][k]*y.a[k][j]%mod)%mod;
	return z;
}
ll read(){
	ll w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*f;
}  
void dfs1(int x,int y){
	vis[x][y]=1;
	for (int i=0;i<4;i++){
		int xx=x+dx[i],yy=y+dy[i];
		if (yy>m) yy-=m;
		if (yy<1) yy+=m;
		if (xx>=1&&xx<=n&&!vis[xx][yy]&&ma[xx][yy]=='#')
			dfs1(xx,yy);
	}
}
void dfs2(int x,int y){
	vis[x][y]=1;
	for (int i=0;i<4;i++){
		int xx=x+dx[i],yy=y+dy[i];
		if (xx>=1&&xx<=n&&yy>=1&&yy<=m&&!vis[xx][yy]&&ma[xx][yy]=='#')
			dfs2(xx,yy);
	}
}
//左右连通块数，相邻黑格子数，黑色格子数
ll ksm_s(ll x,ll y){
	ll ans=1;x%=mod;
	while (y){
		if (y&1) ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans;
}
node ksm(node x,ll y){
	node ans;
	ans.init2();
	while (y){
		if (y&1) ans=ans*x;
		x=x*x;
		y>>=1;
	}
	return S*ans;
}
int main(){
	n=read(),m=read(),k=read();
	for (int i=1;i<=n;i++)
		scanf("%s",ma[i]+1);
	for (int i=1;i<=n;i++)
		if (ma[i][1]=='#'&&ma[i][m]=='#') flag1=1;
	for (int i=1;i<=m;i++)
		if (ma[1][i]=='#'&&ma[n][i]=='#') flag2=1;		
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			if (ma[i][j]=='#') ++cnt;
	if (!flag1&&!flag2){
		cout<<ksm_s(cnt,k-1)<<'\n';
		return 0;
	}else if (flag1&&flag2){
		puts("1");
		return 0;
	}else if (!flag1&&flag2){
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
				ma2[m-j+1][i]=ma[i][j];
		swap(n,m);
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
				ma[i][j]=ma2[i][j];
	}
	for (int i=1;i<=n;i++)
		for (int j=1;j<m;j++)
			if (ma[i][j]=='#'&&ma[i][j+1]=='#') ++tot2;
	for (int i=1;i<=n;i++)
		if (ma[i][1]=='#'&&!vis[i][1]) dfs1(i,1),++tot1;
	for (int i=1;i<=n;i++)
		if (ma[i][1]=='#'&&ma[i][m]=='#') ++cmt;
	memset(vis,0,sizeof(vis));
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			if (ma[i][j]=='#'&&!vis[i][j]) dfs2(i,j),++S.a[0][0];
	S.a[0][1]=tot1;
	Z.init();
//	cout<<S.a[0][0]<<" "<<S.a[0][1]<<"\n";
//	cout<<Z.a[0][0]<<" "<<Z.a[0][1]<<"\n"<<Z.a[1][0]<<" "<<Z.a[1][1]<<'\n';
	S=ksm(Z,k-1);
	cout<<(S.a[0][0]+mod)%mod<<'\n';
	return 0;
}

```

---

## 作者：ezoixx130 (赞：1)

### 题目链接：

[AGC003F](https://agc003.contest.atcoder.jp/tasks/agc003_f)

### 题意：

给你一个n*m的网格，一个k，每个格子要么就是黑的要么就是白的，要让你求如果用这个图形构成k阶分形，求联通块数量。

### 题解：

一看这个k的范围，$10^{18}$，就肯定是矩阵乘法的题了，可惜场上没有推出来。

首先如果这个图形与四周不连通，那么答案就一定是$cnt^{k-1}$，其中$cnt$为黑点个数。

如果这个图形上接下是联通的，左接右也是联通的，那么答案就一定是$1$，因为最后的分形一定联通。

那么剩下的情况就只有上边和下边联通，左边和右边联通两种情况之一了。

那么我们就只需求出$cnt$，$a$，$b$，其中$a$表示多少个黑点满足在这行与它相邻的下一个点也是黑的，$b$表示有多少行是连通的。

构造的矩阵长这样：$\begin{bmatrix}cnt &a \\ 0 & b \end{bmatrix}$

用快速幂求$A=\begin{bmatrix}cnt &a \\ 0 & b \end{bmatrix}^{k-1}$，答案就是$A[1][1]-A[1][2]$。

代码：

```
#include <bits/stdc++.h>
using namespace std;
 
#define mod 1000000007
 
int n,m,cnt,flag1,flag2,s1,s2;
long long k;
char s[2001][2001];
 
long long quickpow(long long base,long long to)
{
	if(to<=0)return 1;
	if(to==1)return base;
	long long mid=quickpow(base,to>>1);
	if(to&1)return mid*mid%mod*base%mod;
	else return mid*mid%mod;
}
 
struct Matrix{
	long long a[3][3];
	Matrix(){memset(a,0,sizeof(a));}
	Matrix operator*(Matrix &m)
	{
		Matrix ans;
		for(int i=1;i<=2;++i)
			for(int j=1;j<=2;++j)
				for(int k=1;k<=2;++k)
					ans.a[i][j]=(ans.a[i][j]+a[i][k]*m.a[k][j]%mod)%mod;
		return ans;
	}
};
 
int main()
{
	scanf("%d%d%lld",&n,&m,&k);
	for(int i=1; i<=n; ++i)
		scanf("%s",s[i]+1);
	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=m; ++j)
			if(s[i][j]=='#')
			{
				++cnt;
				s1+=s[i][j-1]=='#';
				s2+=s[i-1][j]=='#';
			}
		if(s[i][1]=='#' && s[i][m]=='#')++flag1;
	}
	for(int i=1;i<=m;++i)if(s[1][i]=='#' && s[n][i]=='#')++flag2;
	if(flag1 && flag2)
	{
		puts("1");
		return 0;
	}
	if(!flag1 && !flag2)
	{
		printf("%lld\n",quickpow(cnt,k-1));
		return 0;
	}
	if(!flag1)swap(flag1,flag2),swap(s1,s2);
	Matrix A;
	A.a[1][1]=cnt;
	A.a[2][1]=s1;
	A.a[2][2]=flag1;
	--k;
	Matrix ANS;
	ANS.a[1][1]=ANS.a[2][2]=1;
	while(k)
	{
		if(k&1)ANS=ANS*A;
		A=A*A;
		k>>=1;
	}
	printf("%lld\n",(ANS.a[1][1]-ANS.a[2][1]+mod)%mod);
}
```

---

## 作者：ezoiLZH (赞：1)

## 题解：
一看 $K=10^8$ 肯定是log级别的算法，一下想到矩阵快速幂。

首先，一个网格的上面和下面，左边和右边都连通，那么不管怎么分它都是连通的，所以答案是 $1$。

如果一个网格上面和下面，左边和右边都不连通，那么不管怎么分都是不连通的，所以答案是 $x^{k-1}$，$x$ 为黑块总个数。

剩下就是行连通，列不连通了。（不然转一下就好了）

x[k] 表示 k 级分型有多少个黑块。
y[k] 表示 k 级分型有多少个黑块满足这行的下一个也是黑块。
z[k] 表示 k 级分型有多少行是连通的。

**手推可得：**
$x[k]=x[k-1]^2$
$y[k]=x[k-1]y[k-1]+z[k-1]y[k-1]$
$z[k]=z[k-1]^2$

**构造矩阵：**

  $$ \left [ \begin{matrix}
   x & y \\
   0 & z 
  \end{matrix}\right ] $$
求这个矩阵的 $k-1$ 次方，答案为 $x-y$。

## CODE：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

#define mod 1000000007
int n,m;
char s[1005][1005],tmp[1005][1005];
long long k;
struct Matrix{
	long long mat[5][5];
	Matrix(){memset(mat,0,sizeof(mat));}
	Matrix operator*(const Matrix &b)const{
		Matrix c;
		for(int i=1;i<=2;i++)
		for(int j=1;j<=2;j++){
			for(int k=1;k<=2;k++)
				c.mat[i][j]+=mat[i][k]*b.mat[k][j];
			c.mat[i][j]%=mod;
		}
		return c;
	}
	Matrix operator^(long long x)const{
		Matrix a(*this),ans;
		for(int i=1;i<=2;i++)ans.mat[i][i]=1;
		while(x){
			if(x&1)ans=ans*a;
			x>>=1,a=a*a;
		}
		return ans;
	}
}mat;

int qpow(int x,long long y){
	int ans=1;
	while(y){
		if(y&1)ans=1LL*ans*x%mod;
		y>>=1,x=1LL*x*x%mod;
	}
	return ans;
}

bool check(){
	for(int i=1;i<=n;i++)
		if(s[i][1]=='#'&&s[i][m]=='#')return true;
	return false;
}

void turn(){
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
		tmp[m-j+1][i]=s[i][j];
	swap(n,m);
	memcpy(s,tmp,sizeof(s));
}

int main(){
	scanf("%d%d%lld",&n,&m,&k);
	int x=0,y=0,z=0;
	for(int i=1;i<=n;i++){
		scanf("%s",s[i]+1);
		for(int j=1;j<=m;j++)x+=s[i][j]=='#';
	}	
	bool a=check(),b=(turn(),check());turn();
	if(a&&b)return printf("1"),0;
	else if(!a&&!b)return printf("%d",qpow(x,k-1)),0;
	else if(b)turn();
	for(int i=1;i<=n;i++)
		z+=s[i][1]=='#'&&s[i][m]=='#';
	for(int i=1;i<=n;i++)
	for(int j=1;j<m;j++)y+=s[i][j]=='#'&&s[i][j+1]=='#';
	mat.mat[1][1]=x,mat.mat[1][2]=y,mat.mat[2][2]=z;
	mat=mat^(k-1);
	printf("%lld",(mat.mat[1][1]-mat.mat[1][2]+mod)%mod);
}
```

---

