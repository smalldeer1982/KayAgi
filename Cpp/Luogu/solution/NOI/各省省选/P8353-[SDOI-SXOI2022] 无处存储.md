# [SDOI/SXOI2022] 无处存储

## 题目背景

滥用本题评测将封号。请注意本题非同寻常的时空限制和数据点个数。

## 题目描述

小 Ω 想出一个数据结构题，于是它先造了一棵点有点权的树：

给定一棵大小为 $n$ 的树，编号 $1$ 到 $n$，第 $i \in [2,n]$  个点的父节点记作 $f_i \in [1, i-1]$。另外，每个点 $i$ 有一个点权 $a_i$，初始点权由输入确定，具体方式见输入格式。

在数据结构题里面，需要有对应的修改和查询的操作，而树上最简单的两种非平凡操作当然是链加、链求和了。

因此你需要支持以下两种操作：

`0 x y v`：将树上从 $x$ 到 $y$ 的简单路径上的点的权值增加 $v$；

`1 x y`：求树上从 $x$ 到 $y$ 的简单路径上的点的权值和；

出完之后小 Ω 拿给小 N 看，小 N 表示：

……这也太简单了，这不是轻重链剖分模板题吗？！！

小 Ω 于是想到在刚刚接触 OI 的时候了解到的时间换空间的原理，因此他决定本题的空间限制为 **64 MB**。

## 说明/提示

样例 2 ~ 样例 15 数据见下方下载链接。

以上各组样例数据中，每组数据的数据范围符合其输入的子任务编号对应的子任务的数据范围及性质（输入的子任务编号为 0 时除外），并且为了避免可能的常数问题，保证下发样例（子任务编号为 0 时除外）与最终评测所用的该子任务的测试点的数据生成方式强度相同。

| 子任务编号 | 测试点分值 |    $n \leq$     |    $q \leq $    | 树的形态 | 特殊性质 |
| :--------: | :--------: | :-------------: | :-------------: | :------: | :------: |
|     1      |     2      |     $3000$      |     $3000$      |    C     |    W     |
|     2      |     2      | $7 \times 10^6$ | $5 \times 10^4$ |    A     |    W     |
|     3      |     2      | $1 \times 10^6$ | $5 \times 10^4$ |    B     |    Y     |
|     4      |     2      | $2 \times 10^6$ | $5 \times 10^4$ |    B     |    Y     |
|     5      |     2      | $3 \times 10^6$ | $5 \times 10^4$ |    B     |    Y     |
|     6      |     2      | $4 \times 10^6$ | $5 \times 10^4$ |    B     |    Y     |
|     7      |     2      | $5 \times 10^6$ | $5 \times 10^4$ |    B     |    Y     |
|     8      |     2      | $6 \times 10^6$ | $5 \times 10^4$ |    B     |    Y     |
|     9      |     3      | $7 \times 10^6$ | $5 \times 10^4$ |    B     |    Y     |
|     10     |     2      | $1 \times 10^6$ | $5 \times 10^4$ |    B     |    W     |
|     11     |     2      | $2 \times 10^6$ | $5 \times 10^4$ |    B     |    W     |
|     12     |     2      | $3 \times 10^6$ | $5 \times 10^4$ |    B     |    W     |
|     13     |     2      | $4 \times 10^6$ | $5 \times 10^4$ |    B     |    W     |
|     14     |     2      | $5 \times 10^6$ | $5 \times 10^4$ |    B     |    W     |
|     15     |     2      | $6 \times 10^6$ | $5 \times 10^4$ |    B     |    W     |
|     16     |     3      | $7 \times 10^6$ | $5 \times 10^4$ |    B     |    W     |
|     17     |     2      | $1 \times 10^6$ | $5 \times 10^4$ |    C     |    X     |
|     18     |     2      | $2 \times 10^6$ | $5 \times 10^4$ |    C     |    X     |
|     19     |     2      | $3 \times 10^6$ | $5 \times 10^4$ |    C     |    X     |
|     20     |     2      | $4 \times 10^6$ | $5 \times 10^4$ |    C     |    X     |
|     21     |     2      | $5 \times 10^6$ | $5 \times 10^4$ |    C     |    X     |
|     22     |     2      | $6 \times 10^6$ | $5 \times 10^4$ |    C     |    X     |
|     23     |     3      | $7 \times 10^6$ | $5 \times 10^4$ |    C     |    X     |
|     24     |     2      | $1 \times 10^6$ | $5 \times 10^4$ |    C     |    Y     |
|     25     |     2      | $2 \times 10^6$ | $5 \times 10^4$ |    C     |    Y     |
|     26     |     2      | $3 \times 10^6$ | $5 \times 10^4$ |    C     |    Y     |
|     27     |     2      | $4 \times 10^6$ | $5 \times 10^4$ |    C     |    Y     |
|     28     |     2      | $5 \times 10^6$ | $5 \times 10^4$ |    C     |    Y     |
|     29     |     2      | $6 \times 10^6$ | $5 \times 10^4$ |    C     |    Y     |
|     30     |     3      | $7 \times 10^6$ | $5 \times 10^4$ |    C     |    Y     |
|     31     |     2      | $1 \times 10^6$ | $5 \times 10^4$ |    C     |    Z     |
|     32     |     2      | $2 \times 10^6$ | $5 \times 10^4$ |    C     |    Z     |
|     33     |     2      | $3 \times 10^6$ | $5 \times 10^4$ |    C     |    Z     |
|     34     |     2      | $4 \times 10^6$ | $5 \times 10^4$ |    C     |    Z     |
|     35     |     2      | $5 \times 10^6$ | $5 \times 10^4$ |    C     |    Z     |
|     36     |     2      | $6 \times 10^6$ | $5 \times 10^4$ |    C     |    Z     |
|     37     |     3      | $7 \times 10^6$ | $5 \times 10^4$ |    C     |    Z     |
|     38     |     3      | $1 \times 10^6$ | $5 \times 10^4$ |    C     |    W     |
|     39     |     3      | $2 \times 10^6$ | $5 \times 10^4$ |    C     |    W     |
|     40     |     3      | $3 \times 10^6$ | $5 \times 10^4$ |    C     |    W     |
|     41     |     3      | $4 \times 10^6$ | $5 \times 10^4$ |    C     |    W     |
|     42     |     3      | $5 \times 10^6$ | $5 \times 10^4$ |    C     |    W     |
|     43     |     3      | $6 \times 10^6$ | $5 \times 10^4$ |    C     |    W     |
|     44     |     3      | $7 \times 10^6$ | $5 \times 10^4$ |    C     |    W     |


上表“树的形态”一栏中，$\texttt{A}$ 代表 $\forall i \in [2,n]$，$f_i$ 在 $[1,i-1]$ 中均匀随机生成；$\texttt{B}$ 代表 $\forall i \in [2,n]$，$f_i=i-1$；$\texttt{C}$ 代表树的形态无特殊限制。

上表“特殊性质”一栏中，$\texttt{X}$ 代表没有修改操作；$\texttt{Y}$ 代表对于每次修改操作 $x=y$；$\texttt{Z}$ 代表每次询问操作 $x=y$；$\texttt{W}$ 代表无特殊性质。

对于 $100\%$ 的数据，$1 \leq n \leq 7 \times 10^6,1 \leq q \leq 5 \times 10^4,1 \leq f_i<i,1 \leq x,y \leq n,0 \leq A,B,C,a_0,v \leq 10^9$。

**【提示】**

关于空间限制的提示与警告：

1. 程序本身可能占用约 2~4MB 的空间（例如包含的 libc 库），请避免使用的空间与空间限制过于接近。
2. 下发的快速输入模板占用约 1MB 空间，将其中的参数 `S` 调大可以减少对 `fread` 的调用次数（从而加快一点速度），但也会占用更多的空间。如有必要，您可以自由的调整 `S` 的大小，或者使用自己的输入方式。
3. 需要注意的是，递归调用本身尽管没有显式地占用很多空间，但递归过程中的递归栈仍然可能占用内存（可以简单的理解为程序底层需要记录递归过程的参数和返回值）。例如，传入一个 `int` 类参数、返回值为 `int` 的递归函数递归调用 100 次可能产生等同于定义 200 个 `int` 的空间开销（具体比例系数与编译器实现和优化有关）。由于评测时的“空间限制”实际上是程序运行过程中的内存占用的峰值，因此过深的递归可能导致 MLE。因此请谨慎的使用递归，除非您能确保您的递归深度不会过大。
4. 由于计算机系统向文件输出的底层实现相关的某些原因（例如在内存中缓存输出），输出本身可能会占用一定空间。对本题的输出规模而言，您可以认为这部分占用的空间不会超过 1MB；但是某些调试输出（例如使用 `cerr` 或者向 `stderr` 输出）可能会产生额外的空间开销（尽管它们本身不会出现在输出文件中，从而不会影响评测的比对结果），因此请确保最终提交的文件不包含过多的调试输出。
5. 因以上原因超出空间限制的一律后果自负。

本题输入量较大，您可能需要采用高效的输入方式以免因输入效率而超时。出于公平起见，在此提供一份快速输入模板（用法参考下发文件的 fast_input.cpp）。关于该快速输出模板的说明：

1. 下发的快速输入模板占用约 1MB 空间。参数 `S` 越大，速度越快，但占用空间越高，请根据您的实际情况谨慎的确定 `S` 以获得最佳的时空平衡。
2. 请确保代码中无变量、函数、命名空间等名为 `INPUT_SPACE` 或者 `inn` 以避免命名冲突，否则会导致无法通过编译。同理，某些形如 `#define gc getchar()` 的语句可能会导致和 `INPUT_SPACE` 的内部命名冲突。若发生此类编译错误，您需要更改这些冲突的命名。
3. 对于本模板，建议从文件进行输入。从键盘输入，可能会产生无法终止的情形，此时需要在输入末尾手动输入作用等同于文件终止符的字符（该字符不能和输入的数字字符直接相邻，建议在新的一行）。例如，在 Windows 下，这个字符是 `Ctrl+Z`。
4. 对 C 和 C++ 选手，该模板分别需要包含 `stdio.h` 和 `cstdio`（或者 `bits/stdc++.h`）头文件。
5. 出于效率和码长的考虑，`inn()` 函数仅能用于输入一个无符号 32 位整数类型。

为演示快速输入模板的使用和产生权值的方式，提供一样例程序，见下发文件的 sample.cpp。

## 样例 #1

### 输入

```
0 10 10 935995202 406705156 7034169 418665824
1 1 1 1 1 1 1 7 2
0 10 3 781084039
1 7 5
0 897574 897583 833116301
1 897583 897572
0 886189 886179 123805569
1 886182 886190
1 145142 145136
1 854537 854538
1 896515 896525
0 879409 879412 746499584```

### 输出

```
2925376046
3681387943
4240586487
2878147072
2350755335
731736886```

# 题解

## 作者：yzy1 (赞：122)

> 「另，这题和树剖一分钱关系都没有。」——出题人。

注意：本题解做法使用 **树剖**。~~且该做法无法在大部分 OJ 上评测。但理论上考试本地评测时可通过。且允许在考场使用。~~

**Upd. 5/27:** 感谢 @liuzhangfeiabc，目前已找到一种可以在洛谷和 LOJ 通过的方式。

## Subtask $\bf 1$

暴力即可。用一个数组存点权，另一个数组存父亲，每次修改时暴力跳父亲修改。

## Subtask $\bf 2$

该点满足特殊性质：点 $i$ 的父亲均从 $1\sim i-1$ 中均匀随机产生。

可以证得这样生成的树以 $1$ 为根的期望高度是 $O(\log n)$ 的。具体证明过程可以参考 [EI 的证明](https://blog.csdn.net/EI_Captain/article/details/109910307)。

由于树高期望 $O(\log n)$，所以链长也期望 $O(\log n)$。故该测试点仍可暴力。

## Subtask $\bf 3 \sim 16$

该点满足特殊性质：树退化为链。

链上的区间加区间和可以用多种数据结构维护。但是此处由于内存卡的较紧，仅能开下两个长度为 $n$ 的 $32$ 位整形数组。所以这里使用额外空间 $O(\sqrt n)$ 的分块维护。

## Subtask $\bm{{n \le 3 \times 10^6}}$

树上问题的一种维护方式就是树剖。轻重链剖分的大众写法需要开 `fa`、`sz`、`dep`、`hson`、`top`、`dfn` 六个数组。本题中显然无法开下。考虑将每个数组用于多种用途。我们发现，`sz`、`hson`、`top` 三个数组可共用一个数组。且由于题目保证 $f_i < i$，深搜的过程可以直接用 `for` 加上一个 `bitset` 代替。同时由于 $f_i < i$，即已经确定拓扑序，`dep` 数组是无必要存在的。跳链时只需要比较链顶的 `dfn` 即可。

树剖完成后同样用分块维护。空间是 $4n+O(\sqrt n)$ 级别的。

## Subtask $\bm{{n \le 4 \times 10^6}}$

如果你做过 [MCOI R4A](/problem/P7347)，你可能会知道一个时间换空间的方法。可以参考 [该题解](https://www.luogu.com.cn/blog/yzy1/solution-p7347) 中的「优化 A」部分。

我们发现 Subtask ${n \le 3 \times 10^6}$ 做法中的 `fa`、`top`、`dfn` 三个数组值域全是 $O(n)$。可以使用 23 个 bit 来存一个 int。这样就可以通过该 Subtask 了。

分块块长为 $800$ 时，空间约为 $(4n+3\times\frac{23}{8}n+2\times \frac{n}{800})\text{ B}$。

## Subtask $\bm{{n \le 6 \times 10^6}}$

树剖的三个辅助数组还是太多了，能改成两个吗？

当然可以。我们发现，树剖在跳链的过程中，对于一个是某个节点的重儿子的节点只会从它跳到链顶，否则只会从它跳到它的父亲。考虑把 `fa` 和 `top` 存到一起，使用 `bitset` 存储每个点是否是一条链的链顶。然后我们就可以少开一个数组而通过该 Subtask 了！

分块块长为 $800$ 时，空间约为 $(4n+2\times\frac{23}{8}n+\frac{n}{8}+2\times \frac{n}{800})\text{ B}$。

## Subtask $\bm{{n \le 7 \times 10^6}}$

把 $n=7\times 10^6$ 带入上面式子，得到内存约 $69300000\text{ B}$，就差一点了！

观察题目中的这个强制在线形式，发现所有输入会异或答案对 $2^{20}$ 取模后的结果。考虑只存 $a$ 数组的低 $21$ 位，然后像 Subtask ${n \le 4 \times 10^6}$ 那样做。

可以发现此时内存可以开下了。但是我们只有答案的低 $20$ 位能做些什么呢？

注意此时我们可以得到所有解密后的询问，并以 $O(q)$ 的空间复杂度把它们存储下来。我们可以直接询问离线，把虚树建出来，然后重新在虚树上跑一遍树剖就行。

问题来了，`fa` 数组已经不存在了，如何还原树的形态呢？

如果是在 OJ 上测评，且 OJ 允许操作文件指针，则可以使用 ` fseek(stdin,0,SEEK_SET);` 让文件指针回到文件开头重新读取。如果是在本地，使用文件输入输出，我们可以直接 `fclose` 把文件关了后重新 `freopen` 打开再读一遍。

做完第一遍后，记录解密后的数据，并且把内存池整个清空，重新分配内存，重新再做第二遍。

该做法在 Arch Linux 上的 LemonLime 0.3.3 测试，编译器为 G++ 11.3.0，编译选项 `-std=c++11 -O2`，评测机 CPU 为 Intel i5-8259U。经测试程序运行内存为 $62.8\text{ MB}$。可以通过。

[代码参考](https://loj.ac/s/1470623)（包含最终解法和题解中说明的大部分 Subtask 的暴力解法）。

---

## 作者：Anita_Hailey (赞：24)


## [SDOI2022] 无处储存

### 题意

给你一棵树，让你可以链加，链求和，

满足 $n\le 7\times 10^6,q\le 5\times 10^4$

4s,64MB

### 题解

非常的离谱，空间只给到 64 MB。

想要用树剖来解决的话，根本不可能因为你三个 $N$ 长度的数组就爆炸了，然而你必然有个数组是要存父亲，还有个数组要存权值，所以你不能再开一个数组了。

也就是说，我们只能开什么 $O(\sqrt N)$ 长度的数组，很离谱。

甚至不能对于这树进行一遍 dfs。

我们考虑对于这个树进行树分块，首先洒下来 $\sqrt N$ 个点，这样每个节点对于它上面的一个关键点距离期望为 $O(\sqrt N)$，之后建立这个关键点的虚树，然后把树上每个节点到他父亲的链就是我们要维护的，总共有 $O(\sqrt N)$ 条，然后每次就是从两个节点开始跳，然后分类讨论一下两个点开始不在链上的情况就可以了就可以了。因为有些节点可能我们下面没有选关键点（没办法，空间不够）。

感觉写起来很难受，但是说着很轻松？离谱。

```cpp
// Siriqwq
#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::vector;
using std::copy;
using std::reverse;
using std::sort;
using std::get;
using std::unique;
using std::swap;
using std::array;
using std::cerr;
using std::function;
using std::map;
using std::set;
using std::pair;
using std::mt19937;
using std::make_pair;
using std::tuple;
using std::make_tuple;
using std::uniform_int_distribution;
using ll = long long;
namespace qwq {
	mt19937 eng;
	void init(int Seed) {return eng.seed(Seed);}
	int rnd(int l = 1, int r = 1000000000) {return uniform_int_distribution<int> (l, r)(eng);}
}
template<typename T>
inline void chkmin(T &x, T y) {if (x > y) x = y;}
template<typename T>
inline void chkmax(T &x, T y) {if (x < y) x = y;}
template<typename T>
inline T min(const T &x, const T &y) {return x < y ? x : y;}
template<typename T>
inline T max(const T &x, const T &y) {return x > y ? x : y;}
char buf[100000], *buff = buf + 100000;
#define gc() ((buff == buf + 100000 ? (fread(buf, 1, 100000, stdin), buff = buf) : 0), *(buff++))
template<typename T>
inline void read(T &x) {
	x = 0;
	bool f = 0;
	char ch = gc();
	while (!isdigit(ch)) f = ch == '-', ch = gc();
	while (isdigit(ch)) x = x * 10 + ch - '0', ch = gc();
	if (f) x = -x;
}
template<typename T, typename ...Arg>
inline void read(T &x, Arg &... y) {
	read(x);
	read(y...);
}
#define O(x) cerr << #x << " : " << x << '\n'
const double Pi = acos(-1);
const int MAXN = 7e6 + 10, MOD = 998244353, inv2 = (MOD + 1) / 2, I32_INF = 0x3f3f3f3f, MAXK = 1e4 + 10;
const long long I64_INF = 0x3f3f3f3f3f3f3f3f;
auto Ksm = [] (int x, int y) -> int {
	if (y < 0) {
		y %= MOD - 1;
		y += MOD - 1;
	}
	int ret = 1;
	for (; y; y /= 2, x = (long long) x * x % MOD) if (y & 1) ret = (long long) ret * x % MOD;
	return ret;
};
auto Mod = [] (int x) -> int {
	if (x >= MOD) return x - MOD;
	else if (x < 0) return x + MOD;
	else return x;
};
template<const int N_num, const int M_num>
struct Graph {
	int H[N_num];
	struct Edge {int to, lac;} e[M_num];
	inline void add_edge(int x, int y) {e[*H] = {y, H[x]};H[x] = (*H)++;}
	inline void init() {memset(H, -1, sizeof H);*H = 0;}
};
#define go(x, y) for (int i = x.H[y], v; (v = x.e[i].to) && ~i; i = x.e[i].lac)
inline int ls(int k) {return k << 1;}
inline int rs(int k) {return k << 1 | 1;}
using ui = unsigned int;
struct Node {
	int id, fa, dep, lst;
	ui sum, tag, sz;
} g[MAXK];
int id, N, Q, fa[MAXN], k;
// t1 表示是否在虚树上，t2表示是不是虚树上的关键点
std::bitset<MAXN> t1, t2;
ui A, B, C, a0, a[MAXN];
void add(int u) {
	if (a[u] & 2) return;
	a[u] |= 2;
	g[++k].id = u;
}
// x 这个点, ax 这个树第一次在虚树上的点，bx，这条链的管辖点。
inline void pre(int x, int &ax, int &bx) {
	for (ax = x; !t1.test(ax); ax = fa[ax]);
	if (t2.test(ax)) {
		for (bx = 1; bx <= k; ++bx) if (g[bx].id == ax) break;
	}
	else {
		int tmp = 0;
		for (bx = ax; !t2.test(bx); bx = fa[bx]) tmp = bx;
		for (bx = 1; bx <= k; ++bx) if (g[bx].lst == tmp) break;
	}
}
ui qry(int x, int y) {
	ui ans = 0;
	int ax, ay, bx, by;
	pre(x, ax, bx);
	pre(y, ay, by);
	if (g[bx].dep > g[by].dep) {
		// 确保 by 深度大于 bx
		swap(x, y);
		swap(bx, by);
		swap(ax, ay);
	}
	// 走到之前就凉了
	if (ax == ay) {
		int d1 = 0, d2 = 0, nw;
		for (nw = x; nw != ax; nw = fa[nw]) ++d1;
		for (nw = y; nw != ay; nw = fa[nw]) ++d2;
		while (d1 > d2) ans += a[x], x = fa[x], --d1;
		while (d2 > d1) ans += a[y], y = fa[y], --d2;
		for (; x != y; x = fa[x], y = fa[y]) ans += a[x] + a[y];
		ans += a[x];
		if (x == ax) ans += g[bx].tag;
		return ans;
	}
	// 分别走到主分支
	for (; x != ax; x = fa[x]) ans += a[x];
	for (; y != ay; y = fa[y]) ans += a[y];
	ax = g[g[bx].fa].id;
	ay = g[g[by].fa].id;
	// 如果一个链上
	if (bx == by) {
		int d1 = 0, d2 = 0, tp;
		for (tp = x; tp != ax; tp = fa[tp]) ++d1;
		for (tp = y; tp != ay; tp = fa[tp]) ++d2;
		for (; d1 > d2; x = fa[x], --d1) ans += a[x] + g[bx].tag;
		for (; d2 > d1; y = fa[y], --d2) ans += a[y] + g[by].tag;
		return ans + g[bx].tag + a[x];
	}
	for (; y != ay; y = fa[y]) ans += a[y] + g[by].tag;
	by = g[by].fa;
	for (; g[bx].dep < g[by].dep; by = g[by].fa) ans += g[by].sum;
	// ax 如果直接就是 y 的祖先了. 
	if (bx == by) {
		y = g[by].id;
		for (y = g[by].id; y != x; y = fa[y]) ans += a[y] + g[by].tag;
		return ans + a[x] + g[bx].tag;
	}
	// lca 是关键点
	for (; x != ax; x = fa[x]) ans += a[x] + g[bx].tag;
	bx = g[bx].fa;
	for (; g[by].dep > g[bx].dep; by = g[by].fa) ans += g[by].sum;
	for (; bx != by; bx = g[bx].fa, by = g[by].fa) ans += g[bx].sum + g[by].sum;
	return ans + a[g[bx].id] + g[bx].tag;
}
void mfy(int x, int y, ui ad) {
	int ax, ay, bx, by;
	pre(x, ax, bx);
	pre(y, ay, by);
	if (g[bx].dep > g[by].dep) {
		// 确保 by 深度大于 bx
		swap(x, y);
		swap(bx, by);
		swap(ax, ay);
	}
	// 走到之前就凉了
	if (ax == ay) {
		int d1 = 0, d2 = 0, nw;
		for (nw = x; nw != ax; nw = fa[nw]) ++d1;
		for (nw = y; nw != ay; nw = fa[nw]) ++d2;
		while (d1 > d2) a[x] += ad, x = fa[x], --d1;
		while (d2 > d1) a[y] += ad, y = fa[y], --d2;
		for (; x != y; x = fa[x], y = fa[y]) a[x] += ad, a[y] += ad;
		a[x] += ad;
		if (x == ax) g[bx].sum += ad;
		return;
	}
	// 分别走到主分支
	for (; x != ax; x = fa[x]) a[x] += ad;
	for (; y != ay; y = fa[y]) a[y] += ad;
	ax = g[g[bx].fa].id;
	ay = g[g[by].fa].id;
	// 如果一个链上
	if (bx == by) {
		int d1 = 0, d2 = 0, tp;
		for (tp = x; tp != ax; tp = fa[tp]) ++d1;
		for (tp = y; tp != ay; tp = fa[tp]) ++d2;
		for (; d1 > d2; --d1, x = fa[x]) {
			a[x] += ad;
			g[bx].sum += ad;
		}
		for (; d2 > d1; --d2, y = fa[y]) {
			a[y] += ad;
			g[by].sum += ad;
		}
		g[bx].sum += ad;
		a[x] += ad;
		return;
	}
	for (; y != ay; y = fa[y]) a[y] += ad, g[by].sum += ad;
	by = g[by].fa;
	for (; g[bx].dep < g[by].dep; by = g[by].fa) g[by].sum += ad * g[by].sz, g[by].tag += ad;
	// ax 如果直接就是 y 的祖先了. 
	if (bx == by) {
		y = g[by].id;
		for (y = g[by].id; y != x; y = fa[y]) a[y] += ad, g[by].sum += ad;
		a[x] += ad;
		g[bx].sum += ad;
		return;
	}
	// lca 是关键点
	for (; x != ax; x = fa[x]) a[x] += ad, g[bx].sum += ad;
	bx = g[bx].fa;
	for (; g[by].dep > g[bx].dep; by = g[by].fa) g[by].sum += g[by].sz * ad, g[by].tag += ad;
	for (; bx != by; bx = g[bx].fa, by = g[by].fa) {
		g[bx].sum += ad * g[bx].sz, g[bx].tag += ad;
		g[by].sum += ad * g[by].sz, g[by].tag += ad;
	}
	a[g[bx].id] += ad;
	g[bx].sum += ad;
}
int main() {
	// freopen("P8353.in", "r", stdin);
	// freopen("P8353.out", "w", stdout);
	// std::ios::sync_with_stdio(0);
	// cout << std::fixed << std::setprecision(8);
	// cin.tie(0);
	// cout.tie(0);
	qwq::init(20050112);
	read(id, N, Q, A, B, C, a0);
	for (int i = 2; i <= N; ++i) read(fa[i]);
	// 建立虚树，先设置关键点
	add(1);
	for (int i = sqrt(N); i; --i) add(qwq::rnd(1, N));
	a[1] |= 1;
	for (int i = 2, u; i <= k; ++i) {
		for (u = g[i].id; !(a[u] & 1); u = fa[u]) a[u] |= 1;
		add(u);
	}
	// 考虑处理 t1,t2
	memset(a, 0, sizeof a);
	for (int i = 1; i <= k; ++i) {
		t1.set(g[i].id);
		t2.set(g[i].id);
		a[g[i].id] = i;
	}
	// 求出虚树上的父亲
	for (int i = 2; i <= k; ++i) {
		int v = g[i].id, u = fa[v];
		for (; !a[u]; u = fa[u]) {
			v = u;
			t1.set(u);
		}
		g[i].fa = a[u];
		g[i].lst = v;
	}
	// 读入 a 数组
	memset(a, 0, sizeof a);
	a[0] = a0;
	for (int i = 1; i <= N; ++i) a[i] = A * a[i - 1] * a[i - 1] + B * a[i - 1] + C;
	a[0] = 0;
	// 预处理每个点到他父亲关键点的
	g[1].sum = a[g[1].sz = 1];
	for (int i = 2, u, v; i <= k; ++i) {
		u = g[i].id;
		v = g[g[i].fa].id;
		g[i].sum = a[u];
		g[i].sz = 1;
		for (u = fa[u]; u != v; u = fa[u]) g[i].sum += a[u], ++g[i].sz;
	}
	g[1].dep = 1;
	for (int i = 2, u, v; i <= k; ++i) {
		int o = 0;
		for (u = i; !g[u].dep; u = g[u].fa) ++o;
		for (v = i; v != u; v = g[v].fa) g[v].dep = g[u].dep + o--;
	}
	// return 0;
	ui lstans = 0, w;
	for (int opt, u, v; Q--; ) {
		read(opt, u, v);
		u ^= lstans;
		v ^= lstans;
		// O(Q);
		if (opt == 0) {
			read(w);
			mfy(u, v, w ^ lstans);
		} else {
			printf("%u\n", lstans = qry(u, v));
			lstans &= (1 << 20) - 1;
		}
	}
	// cout << (-3 / 2);
	cerr << ((double) clock() / CLOCKS_PER_SEC) << '\n';
	return (0-0);
}
```

---

## 作者：Renshey (赞：15)

#### 题解

不难想到树分块。在树上随机选择 $\sqrt n$ 个点构建出虚树后，每个点期望向上跳 $O(\sqrt n)$ 步就能到达一个虚树上的点。

构建虚树不能采用 dfs 序 + lca 的传统方法，注意到只需要求一次虚树，因此可以暴力。从每个点暴力往上跳并打标记，碰到标记过的点就加入虚树并停止，这样每个点只会被标记一次，可以用 bitset 处理，效率 $O(n)$。以下用关键点表示虚树上的点，标记点表示虚树的边经过的所有点。

考虑如何处理修改和询问，为了方便可以拆成四条，这一步需要求 lca。拆成四条后每条最开始非标记点的部分可以暴力，在虚树上遇到非关键点之前的一段需要找到这一段底部的关键点然后暴力重构，剩下的段可以整体标记/查询。因此需要支持以下函数：

```cpp
int find (int u);
int dep (int u);
int lca (int u, int v);
```

其中 `find(u)` 表示求出 $u$ 所在的虚树的一段边的底部的关键点，`dep(u)` 表示求出 $u$ 的深度，`lca(u,v)` 表示求出 $u$ 和 $v$ 的 lca。

对于 `find(u)`，首先可以暴力跳到 $u$ 上方的第一个关键点与跳到关键点之前的一步，然后可以对于每个关键点预处理经过每个儿子走到的下一个关键点的位置，这部分可以用 unordered_map 维护，单次查询 $O(\sqrt n)$。

对于 `dep(u)`，可以暴力跳到 $u$ 上方第一个关键点，预处理每个关键点的深度即可快速计算，单次查询 $O(\sqrt n)$。

对于 `lca(u, v)`，设 $x,y$ 分别为 $u,v$ 上方第一个标记点。若 $x=y$，可以暴力跳 $u,v$ 找到 lca；若 $x\ne y$，那么显然有 $x,y$ 的 lca 即为 $u,v$ 的 lca，于是只需要考虑 $u,v$ 都是标记点的情况。利用之前的 `find` 函数可以找到 $u,v$ 对应的两个点 $a,b$，画图可知，当 $a,b$ 没有祖先关系时，$u,v$ 的 lca 即为 $a,b$ 的 lca，否则 $u,v$ 的 lca 即为两个点中深度较低的点。因此暴力跳虚树找到 $a,b$ 的 lca 后即可快速判断，单次查询 $O(\sqrt n)$。

综上，时间复杂度 $O(n+q\sqrt n)$，空间复杂度 $2n+\frac{n}{\omega}+O(\sqrt n)$。

#### 代码

```cpp
#include <bits/stdc++.h>
#define Getchar() p1 == p2 and (p2 = (p1 = Inf) + fread(Inf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++
#define Putchar(c) p3 == p4 and (fwrite(Ouf, 1, 1 << 21, stdout), p3 = Ouf), *p3++ = c
char Inf[1 << 21], Ouf[1 << 21], *p1, *p2, *p3 = Ouf, *p4 = Ouf + (1 << 21);
inline unsigned int read (void)
{
	unsigned int x = 0; char c = Getchar();
	while (c < '0' or c > '9') c = Getchar();
	while (c >= '0' and c <= '9') x = x * 10 + c - 48, c = Getchar();
	return x;
}
inline void write (unsigned int x)
{
	if (x >= 10) write(x / 10), x %= 10;
	Putchar(x ^ 48);
}
const int maxn = 7000000 + 10;
int n, m, q, fa[maxn], p[6000], anc[6000], dep[6000];
unsigned int A, B, C, a[maxn], sum[6000], add[6000];
std::bitset<maxn> vis, tag; std::unordered_map<int, int> nxt[6000];
inline int Dep (int u)
{
	int d = 0;
	for (; !vis[u]; u = fa[u]) d++;
	return d + dep[std::lower_bound(p + 1, p + m + 1, u) - p];
}
inline int find (int u)
{
	while (!vis[fa[u]]) u = fa[u];
	return nxt[std::lower_bound(p + 1, p + m + 1, fa[u]) - p][u];
}
inline void upd (int u, unsigned int w)
{
	if (!u) return;
	for (; !tag[u]; u = fa[u]) a[u] += w;
	if (!vis[u])
	{
		int x = find(u), y = anc[x];
		for (int v = p[x]; v != p[y]; v = fa[v]) a[v] += add[x];
		for (int v = u; v != p[y]; v = fa[v]) a[v] += w, sum[x] += w;
		add[x] = 0; u = p[y];
	}
	for (u = std::lower_bound(p + 1, p + m + 1, u) - p; u; u = anc[u]) sum[u] += w * (dep[u] - dep[anc[u]]), add[u] += w;
}
inline unsigned int ask (int u)
{
	if (!u) return 0;
	unsigned int res = 0;
	for (; !tag[u]; u = fa[u]) res += a[u];
	if (!vis[u])
	{
		int x = find(u), y = anc[x];
		for (int v = p[x]; v != p[y]; v = fa[v]) a[v] += add[x];
		for (int v = u; v != p[y]; v = fa[v]) res += a[v];
		add[x] = 0; u = p[y];
	}
	for (u = std::lower_bound(p + 1, p + m + 1, u) - p; u; u = anc[u]) res += sum[u];
	return res;
}
inline int LCA (int u, int v)
{
	while (u != v) dep[u] < dep[v] ? v = anc[v] : u = anc[u];
	return u;
}
inline int lca (int u, int v)
{
	int x = u, y = v, depu = Dep(u), depv = Dep(v);
	while (!tag[x]) x = fa[x];
	while (!tag[y]) y = fa[y];
	if (x == y)
	{
		while (u != v) depu < depv ? (v = fa[v], depv--) : (u = fa[u], depu--);
		return u;
	}
	u = x; x = vis[x] ? std::lower_bound(p + 1, p + m + 1, x) - p : find(x);
	v = y; y = vis[y] ? std::lower_bound(p + 1, p + m + 1, y) - p : find(y);
	if (x == y) return Dep(u) < Dep(v) ? u : v;
	int z = LCA(x, y);
	if (z == x) return u;
	if (z == y) return v;
	return p[z];
}
inline void upd (int u, int v, unsigned int w)
{
	if (u == v) {upd(u, w); upd(fa[u], -w); return;}
	int x = lca(u, v);
	if (x == u) {upd(v, w); upd(fa[u], -w); return;}
	if (x == v) {upd(u, w); upd(fa[v], -w); return;}
	upd(u, w); upd(v, w); upd(x, -w); upd(fa[x], -w);
}
inline unsigned int ask (int u, int v)
{
	if (u == v) return ask(u) - ask(fa[u]);
	int x = lca(u, v);
	if (x == u) return ask(v) - ask(fa[u]);
	if (x == v) return ask(u) - ask(fa[v]);
	return ask(u) + ask(v) - ask(x) - ask(fa[x]);
}
signed main ()
{
	read(); n = read(); q = read();
	A = read(); B = read(); C = read(); a[0] = read();
	for (int i = 1; i <= n; i++) a[i] = A * a[i - 1] * a[i - 1] + B * a[i - 1] + C;
	for (int i = 2; i <= n; i++) fa[i] = read();
	srand(time(NULL)); p[1] = 1; m = sqrt(n);
	for (int i = 2; i <= m; i++) p[i] = rand() % n + 1;
	std::sort(p + 1, p + m + 1); m = std::unique(p + 1, p + m + 1) - p - 1;
	for (int i = 1; i <= m; i++) vis[p[i]] = 1;
	tag[1] = 1;
	for (int i = 1, u; i <= m; i++)
	{
		for (u = p[i]; !tag[u]; u = fa[u]) tag[u] = 1;
		if (!vis[u]) p[++m] = u, vis[u] = 1;
	}
	std::sort(p + 1, p + m + 1); sum[1] = a[1]; dep[1] = 1;
	for (int i = 2, lst; i <= m; i++)
	{
		sum[i] = a[p[i]]; dep[i] = 1;
		for (anc[i] = fa[p[i]], lst = p[i]; !vis[anc[i]]; lst = anc[i], anc[i] = fa[anc[i]]) sum[i] += a[anc[i]], dep[i]++;
		anc[i] = std::lower_bound(p + 1, p + m + 1, anc[i]) - p; dep[i] += dep[anc[i]]; nxt[anc[i]][lst] = i;
	}
	for (int op, u, v, w, ans = 0; q--; )
	{
		op = read(); u = read() ^ ans; v = read() ^ ans;
		if (!op) w = read() ^ ans, upd(u, v, w);
		else write(ans = ask(u, v)), Putchar('\n'), ans &= (1 << 20) - 1;
	}
	fwrite(Ouf, 1, p3 - Ouf, stdout); fflush(stdout);
	return 0;
}
```

---

## 作者：critnos (赞：14)

提供一个异常好写的写法，只写了 2.81k，目前洛谷最短。

说句闲话其实是本题的正解应该是 $O(q\log n)$ 的，但是这题写什么乱七八糟的东西都能过。

大体思路应该是[这个](https://www.luogu.com.cn/blog/203623/yi-zhong-jian-yi-shu-fen-kuai)，不再复述。

但上面的构造方法需要较多空间，使用随机撒点的方法优化空间常数。

按编号大小从小到大加入关键点。用一个 bitset $vis$ 表示虚树边对应原树中的点。加入 $x$ 时枚举其祖先。如果存在祖先 $p$ 使得 $p$ 在虚树边上，那么该边在此处分叉。将 $p$ 加入虚树点集。

之后每次操作直接跳到祖先中第一个关键点。然后在虚树结构上跳即可。

实际上，可以撒 $\dfrac n K$ 个点，$K$ 为全局平衡二叉树的空间常数（应该要更大一些）。然后直接在虚树结构上跑这个东西。在优化空间常数的前提下，时间复杂度仍然为 $O(q\log n)$。

**下面是关键，实现细节与坑点：**

实际上，直接这样实现是很难写的。

对 $x\to y$ 的操作，差分成 $x\to 1,y\to 1,lca\to 1,f_{lca} \to 1$。

这个就很好写。考虑求 $lca$。

一种很古老的方法是，先将两个节点跳到同一深度，再一起往上跳。这里可以二分一起向上跳的距离。

那么要求 kth 祖先。这个就很好写了。

Q1：怎么求某个点所属的散块？

对于虚树上每条边 $x\to y$，在边上求出 $p$ 使得 $f_p=y$，建立映射 $p\to x$。直接把这个点向上跳到第一个关键点，记录从哪个儿子跳上来即可。

Q2：如果某个点不属于虚树边上，散块怎么处理？

跳到某个点 $x$ 满足这个点在虚树边上（$vis_x=1$），对于后面的散点，这些点就属于 $x$ 所属的散块了。

Q3：关键点数？

我也不知道，但是我知道我随机标记了 $4\times 10^3$ 个关键点，就是说可能有重复。

Q4：这鬼东西怎么跑过去的？？

$O(q\sqrt {n\log n})$ 加上巨大常数能过，我也很震撼。（而且几乎没有调关键点数）

**虚树空间开两倍。倍两开间空树虚**

```cpp
#include<bits/stdc++.h>
#define Misaka namespace
#define Mikoto std
#define u unsigned
using Misaka Mikoto;
const int mxn=7e6+5;
const int BLOCK=4e3;
bitset<mxn> vis,que,vis2;
u a[mxn];
int f[mxn];
int n,cnt;
int t[BLOCK*2+5],dep[BLOCK*2+5],id[BLOCK*2+5];
u tag[BLOCK*2+5],sum[BLOCK*2+5];
unordered_map<int,int> mp,mp2;
u read()
{
	u s=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s;
}
void add(int x)
{
	id[a[x]=++cnt]=x;
	for(;!vis[x];x=f[x]) vis[x]=1;
	if(!a[x]) id[a[x]=++cnt]=x;
}
struct pir
{
	int lst,top;
	u sum;
};
pir find(int x)
{
	int lst=x;
	u s=a[x];
	for(x=f[x];!vis[x];x=f[x]) s+=a[lst=x];
	return {lst,x,s};
}
void init(u A,u B,u C,u a0)
{
	int i,j;
	a[1]=id[1]=vis[1]=cnt=1,dep[0]=-1;
	for(i=0;i<BLOCK;i++)
		que[rand()%n+1]=1;
	for(i=2;i<=n;i++)
		if(que[i])
			add(i);
	vis2=vis,vis.reset();
	a[1]=0;
	for(i=2;i<=n;i++)
		a[i]=a[f[i]]+1;
	for(i=1;i<=cnt;i++)
		dep[i]=a[id[i]],vis[id[i]]=1,mp[id[i]]=i;
	a[0]=a0;
	for(i=1;i<=n;i++)
		a[i]=A*a[i-1]*a[i-1]+B*a[i-1]+C;
	sum[1]=a[1];
	for(i=2;i<=cnt;i++)
	{
		pir tp=find(id[i]);
		mp2[tp.lst]=i,sum[i]=tp.sum,t[i]=mp[tp.top];
	}
}
struct res
{
	int dep,bel;
};
res asktop(int x)
{
	if(x==1) return res({0,1});
	int lst=x,s=1;
	for(x=f[x];!vis[x];x=f[x]) lst=x,s++;
	return res({s+dep[mp[x]],mp2.find(lst)==mp2.end()?0:mp2[lst]});
}
int askkth(int x,int k)
{
	for(;k&&!vis[x];k--) x=f[x];
	if(!k) return x;
	for(x=mp[x];k>=dep[x]-dep[t[x]];x=t[x]) k-=dep[x]-dep[t[x]];
	for(x=id[x];k;k--) x=f[x];
	return x;
}
u ask(int x)
{
	if(!x) return 0;
	u s=0;
	int bel=0;
	for(;!vis[x];x=f[x]) 
	{
		if(!bel&&vis2[x]) bel=asktop(x).bel;
		s+=a[x]+tag[bel];
	}
	for(x=mp[x];x;x=t[x]) s+=sum[x];
	return s;
}
void add(int x,u v)
{
	if(!x) return;
	int bel=0;
	for(;!vis[x];x=f[x]) 
	{
		if(!bel&&vis2[x]) bel=asktop(x).bel;
		a[x]+=v,sum[bel]+=v;
	}
	for(x=mp[x];x;x=t[x]) 
		sum[x]+=(dep[x]-dep[t[x]])*v,tag[x]+=v;
}
int asklca(int x,int y)
{
	res bx=asktop(x),by=asktop(y);
	if(bx.dep<by.dep) swap(x,y),swap(bx,by);
	int cx=askkth(x,bx.dep-by.dep),i,dep=0;
	if(cx==y) return y;
	for(i=1<<22;i;i>>=1)
		dep+=i*(dep+i<=by.dep&&askkth(cx,dep+i)!=askkth(y,dep+i));
	return askkth(y,dep+1);
}
u ask(int x,int y)
{
	int lca=asklca(x,y);
	return ask(x)+ask(y)-ask(lca)-ask(f[lca]);
}
void add(int x,int y,u v)
{
	int lca=asklca(x,y);
	add(x,v),add(y,v),add(lca,-v),add(f[lca],-v);
}
int main()
{
	srand(time(0));
	read(),n=read();
	int i,j,q=read(),opt,x,y;
	u A=read(),B=read(),C=read(),a0=read(),last=0;
	for(i=2;i<=n;i++)
		f[i]=read();
	init(A,B,C,a0);
	while(q--)
	{
		last&=(1<<20)-1,opt=read(),x=read()^last,y=read()^last;
		if(opt) printf("%u\n",last=ask(x,y));
		else add(x,y,read()^last);
	}
}
```


---

## 作者：EnofTaiPeople (赞：8)

### Part1 前言
当我发现我写不动“暴力写挂”了，这是一大树上数据结构的终结。

众所周知，根号半 $\log$ 一般都不是正解，所以严格根号是有必要的，这道题可以称之为树分块维护修改的模板。

### Part2 基于随机的树分块

也就是随机撒点建虚树，这样的方式是可行的，期望复杂度为 $O(n+q\sqrt n)$。

但我觉得在这道题目卡空间的同时还能使用严格复杂度是更有趣的。

### Part3 基于子树大小的树分块

就是在搜索时，如果一个节点有一个以上的子树内有关键点，或者除去关键点子树之后的大小超过了 $\sqrt n$ 就将该子树设为关键点，这样能保证分成的块数和大小均不超过 $\sqrt n$，当然这道题为了防止栈空间过大，需要使用非递归形式，注意到这里将节点权值和子树大小共用了同一个数组，所以不会超过只能开两个 $O(n)$ 的 `int` 的限制。

我们需要保证根节点为关键点，认为每一个关键点一直往上走，直到碰到关键点为止，这样的一个路径上的点为一个块，块的深度就是该块上方的块数。

考虑两个节点不断将块更深的跳到块顶，可以在 $O(\sqrt n)$ 的时间内找到两个节点的 LCA，这时，修改和询问都可以差分成根到某节点路径上的修改或询问。

### Part4 细节

首先，这道题只能开两个 $O(n)$ 的数组，即父亲和单点权值，在解码权值之前，要将关键点先求出。

求 LCA 当两个点同块时，可以借鉴 `access` 求 LCA 的方法，就是将一个点往上跳跳父亲，标记，另一个点往上跳，碰到的第一个点就是答案。

### Part5 后记

其实只要你会树分块那么这道题就是签到题了，因为就是模板，只是卡掉了高空间常数做法而已，[LOJ 上的 AC 记录](https://loj.ac/s/1708442)。

---

## 作者：chenbs (赞：7)

本蒟蒻完全不会虚树什么的，于是树链剖分水过了此题。

题意简述：给定一颗树，需要链加、链求和，然后空间只有 $64$ MB。

# 一、思路

首先树剖六个数组肯定要爆炸，考虑共用多个数组。观察之后，我们发现只需要三个数组就够了（具体方案看下面）。然而，$3 \times (7 \times 10^6 \times 4) \div 1024 \div 1024 \approx 80$，还是不够。

观察到值域比较小，可以使用 $20$ 或 $23$ 位的变量数组储存。（实际编写时，可以使用 $24$ 位变量数组，这样每个变量正好是 $3$ 个字节，保证了一定的速度）$3 \times (7 \times 10^6 \times 3) \div 1024 \div 1024 \approx 60$，成功开下。

这样又引发了一个新问题，$a$ 的值域是 $2^{32}$，无法存入。我一开始卡了很久，后来看了大佬的才知道，可以先做低位的树剖，把询问解密出来再**离线**。

此时，我们发现并不是整个 `fa/top` 数组都有用，最多 $q \log n$ 个有用。可以只储存有用的部分，然后加一个二分查找。这样 `fa/top` 数组就被压缩了，我们成功拥有足够的空间开下整个 `a` 数组。（其实，你如果把 `dfn` 压缩掉也可以，但是 `dfn` 用得更多，会微微影响速度。）

还有，线段树什么的肯定开不下，就弄个分块吧。

总时间复杂度：$O(q \times \log n \times \sqrt n) \approx 3 \times 10^9$，但由于分块常数很小，还是可以过的。

# 二、实现

![](https://cdn.luogu.com.cn/upload/image_hosting/kliy2uqo.png)

第一步：读入 `fa`，遍历一遍，算出 `sz` 和 `hson`。`sz` 数组光荣退休。

第二步：根据 `hson`，算出 `istop`（`bitset`）。

第三步：对于每个链顶，向下处理出 `dfn`，并且把 `fa` 和 `top` 存一起（链顶存 `fa`，否则存 `top`）`hson` 数组也光荣退休。

第四步：开低 $24$ 位的 `a` 数组，跑一遍树剖，求出解密后的询问。算出 `vis`（`bitset`），即哪些点要用到 `fa/top`。

第五步：旧的 `a` 扔掉。处理出需要的 `fa/top`。

第六步：记录完整的数组 `a`，跑一遍树剖，结束。



最多使用了 $63.35$ MB 内存，非常可以了。其实还有一点优化空间。[提交记录链接在这里](https://www.luogu.com.cn/record/177908811)。

本代码封装了 $1$ 位和 $24$ 位的数组，并重载了 `[]` 运算符。

注：`fa` 和 `top` 指针相同，分开写是为了方便识别。

~~码风可能不好，不喜勿喷。~~

```cpp
#include<bits/stdc++.h>
using namespace std;

namespace INPUT_SPACE {
	const int S=(1<<18)+5;
	char B[S],*H,*T;
	inline int gc() {
		if(H==T) T=(H=B)+fread(B, 1, S, stdin);
		return (H==T)?EOF:*H++;
	}
	inline unsigned int inn() {
		unsigned int x, ch;
		while((ch=gc())<48);
		x=ch^48;
		while((ch=gc())>47) x=x*10+(ch^48);
		return x;
	}
} using INPUT_SPACE::inn;

unsigned char mem[64750015];

namespace containers {
	struct u1arr { // 添加：O(1) 获取：O(1)
		void *pos;
		struct reference {
			unsigned char *i;
			int j;
			void operator = (int val) {
				if(((*i >> j) & 1) != val)  *i ^= (1<<j);
			}
			operator const int () {
				return (*i >> j) & 1;
			}
		};
		inline reference operator [](int i) {
			return {(unsigned char*)pos + (i>>3), i&7};
		}
	};
	struct u24arr { // 添加：O(1) 获取：O(1)
		void *pos;
		struct reference {
			unsigned *i;
			void operator = (int val) {
				(*i &= 0xFF000000u) ^= val & 0x00FFFFFFu;
			}
			void operator += (int val) {
				*this = *this + val;
			}
			operator const int () {
				return ((*i) & 0x00FFFFFFu);
			}
		};
		inline reference operator [](int i) {
			return {(unsigned*)(pos + i * 3)};
		}
	};
	struct u24arr_compress { // 添加：O(1) 获取：O(logn)
		u24arr base;
		int n=0;
		void add(int id, int val) { // 要求：必须有序地加入
			base[n<<1]=id, base[n<<1|1]=val, ++n;
		}
		inline const int operator [](int id) {
			int l=0, r=n-1;
			while(l <= r) {
				int mid = l+r>>1;
				if(base[mid<<1] < id) l=mid+1;
				else if(base[mid<<1] > id) r=mid-1;
				else return base[mid<<1|1];
			}
			return -1;
		}
	};
};



containers::u1arr istop, vis;
containers::u24arr fa, sz, hson, dfn, top, a24;
containers::u24arr_compress fac, topc;

int ti;
unsigned *a;
#define get_top(x) (istop[x] ? x : top[x])
#define get_top_c(x) (istop[x] ? x : topc[x])
struct Q {
	unsigned t, x, y, v;
} qs[50001];
unsigned bt[7000], bs[7000]; // tag，sum，分块空间很小可以忽略不计
// 24 位和 32 位，需要写两个版本。可以用 template 节约码量
template<typename T> void bladd(int x, int y, unsigned v, T &a) {
	// 块长 1024，方便算，询问同理
	int xb=x>>10, yb=y>>10;
	if(xb==yb) {
		for(int i=x; i<=y; i++) a[i]+=v;
		bs[xb]+=v*(y-x+1);
	} else {
		for(int i=x; i<((xb+1)<<10); i++) a[i]+=v;
		bs[xb]+=v*(1024-(x&1023));
		for(int i=xb+1; i<yb; i++) bt[i]+=v, bs[i]+=v<<10;
		for(int i=(yb<<10); i<=y; i++) a[i]+=v;
		bs[yb]+=v*((y&1023)+1);
	}
}
template<typename T> unsigned blquery(int x, int y, T &a) {
	int xb=x>>10, yb=y>>10;
	unsigned ans=0;
	if(xb==yb) {
		for(int i=x; i<=y; i++) ans+=a[i];
		ans+=bt[xb]*(y-x+1);
	} else {
		for(int i=x; i<((xb+1)<<10); i++) ans+=a[i];
		ans+=bt[xb]*(1024-(x&1023));
		for(int i=xb+1; i<yb; i++) ans+=bs[i];
		for(int i=(yb<<10); i<=y; i++) ans+=a[i];
		ans+=bt[yb]*((y&1023)+1);
	}
	return ans;
}
void add24(int x, int y, unsigned v) {
	while(vis[x]=1, vis[y]=1 /* fa/top 被使用了 */, get_top(x) != get_top(y)) {
		if(dfn[x] < dfn[y]) swap(x, y);
		int tx = get_top(x);
		vis[tx]=1; // fa/top 被使用了
		bladd(dfn[tx], dfn[x], v, a24), x=fa[tx];
	}
	if(dfn[x] > dfn[y]) swap(x, y);
	bladd(dfn[x], dfn[y], v, a24);
}
unsigned query24(int x, int y) {
	unsigned ans=0;
	while(vis[x]=1, vis[y]=1 /* fa/top 被使用了 */, get_top(x) != get_top(y)) {
		if(dfn[x] < dfn[y]) swap(x, y);
		int tx = get_top(x);
		vis[tx]=1; // fa/top 被使用了
		ans+=blquery(dfn[tx], dfn[x], a24), x=fa[tx];
	}
	if(dfn[x] > dfn[y]) swap(x, y);
	ans+=blquery(dfn[x], dfn[y], a24);
	return ans;
}
void add(int x, int y, unsigned v) {
	while(get_top_c(x) != get_top_c(y)) {
		if(dfn[x] < dfn[y]) swap(x, y);
		int tx = get_top_c(x);
		bladd(dfn[tx], dfn[x], v, a), x=fac[tx];
	}
	if(dfn[x] > dfn[y]) swap(x, y);
	bladd(dfn[x], dfn[y], v, a);
}
unsigned query(int x, int y) {
	unsigned ans=0;
	while(get_top_c(x) != get_top_c(y)) {
		if(dfn[x] < dfn[y]) swap(x, y);
		int tx = get_top_c(x);
		ans+=blquery(dfn[tx], dfn[x], a), x=fac[tx];
	}
	if(dfn[x] > dfn[y]) swap(x, y);
	ans+=blquery(dfn[x], dfn[y], a);
	return ans;
}
int main() {
	int subtask_id=inn(), n=inn(), q=inn();
	unsigned int A=inn(), B=inn(), C=inn(), a0=inn();
	// 1
	sz.pos=mem, fa.pos=mem+21000003, hson.pos=mem+42000006;
	fa[1]=1;
	for(int i=2; i<=n; i++) fa[i]=inn();
	for(int i=2; i<=n; i++) sz[i]=1;
	for(int i=n; i>=2; i--) sz[fa[i]]+=sz[i];
	for(int i=n; i>=2; i--) if(sz[i] > sz[hson[fa[i]]]) hson[fa[i]] = i;
	// 2
	istop.pos=mem+63000009;
	istop[1]=1;
	for(int i=2; i<=n; i++) if(hson[fa[i]]!=i) istop[i]=1;
	// 3
	dfn.pos=mem, top.pos=mem+21000003;
	for(int i=1; i<=n; i++) {
		if(istop[i]) {
			for(int j=i; j; j=hson[j]) {
				if(i!=j) top[j]=i;
				dfn[j] = ti++;
			}
		}
	}
	// 4
	unsigned long long k=a0;
	a24.pos=mem+42000006, vis.pos=mem+63875012;
	for(int i=1; i<=n; i++) k=A*k*k+B*k+C, a24[dfn[i]]=k, bs[dfn[i]>>10]+=k;
	unsigned last_ans=0;
	for(int i=1; i<=q; i++) {
		unsigned t=inn(), P=last_ans&((1<<20)-1), x=inn()^P, y=inn()^P;
		if(t==0) {
			unsigned int v=inn()^P;
			qs[i] = {t, x, y, v};
			add24(x, y, v);
		} else {
			qs[i] = {t, x, y, 0};
			last_ans=query24(x, y);
		}
	}
	// 5
	fac.base.pos=topc.base.pos=mem+49000006;
	for(int i=1; i<=n; i++) if(vis[i]) fac.add(i, fa[i]);
	topc.n=fac.n;
	// 6
	k=a0, a=(unsigned*)(mem+21000003);
	for(int i=0; i<=(n>>10); i++) bs[i]=0;
	for(int i=0; i<=(n>>10); i++) bt[i]=0;
	for(int i=1; i<=n; i++) k=A*k*k+B*k+C, a[dfn[i]]=k, bs[dfn[i]>>10]+=k; // 重新生成权值
	for(int i=1; i<=q; i++) {
		if(qs[i].t==0) add(qs[i].x, qs[i].y, qs[i].v);
		else printf("%u\n", query(qs[i].x, qs[i].y));
	}
	return 0;
}
```

---

## 作者：cmk666 (赞：7)

[题目传送门](/problem/P8353)

提供一种不需要邪道（如 `fseek` 等）的树剖做法。

首先，树剖需要两个 dfs 预处理出父亲、子树大小、重儿子、深度、dfs 序和链顶。

显然，不能同时存下 $6$ 个数组是一个大问题。但如何 dfs 也是一个难点：你不可能把所有儿子存到 `vector` 里面正常遍历。

注意到题目中保证 $fa_i<i$，这条性质十分有用。

首先，树剖的第一遍 dfs 可以直接倒着枚举，得到重儿子；第二遍 dfs 直接正着枚举，先遍历重儿子，得到 dfn 序。

同时，上面所提到的性质，保证了我们不需要存深度，直接比较就行了。

但这样还是要存 $3$ 个数组，看起来还是不够。

观察到所有数的值域都是 $[1,n]$，可以用 `int24` 进行存储，压掉 $\dfrac14$ 的空间，就存的下了。

这样还有一个问题：点权是 $32$ 位的，两个 `int24` 加上一个 `unsigned` 还是开不下。

然而，强制在线的 $lastans$ 只有低 $20$ 位有用，我们可以先只做低 $20$ 位，这样可以知道树剖需要用到哪些点的 $fa$。注意做的时候要用分块，因为剩下的空间不足以使用线段树等数据结构。

需要用到 $fa$ 的点数是 $O(q\log n)$ 的，可以把它们单独存起来，用不到的 $fa$ 扔掉。这样就有足够的空间开下点权了，直接做就行。

手写内存池，最终空间 $62.8$ MB。[提交记录](//loj.ac/s/1721217)。

---

## 作者：FunnyCreatress (赞：3)

突然发现没投题解，事实上这是一年多以前写的了，理论上全方面吊打现有的所有做法。

problemprovidercreep。

注：以下空间以 `int` 为单位。

众所周知，线段树有一种空间优化思想叫底层分块，考虑将其上树。

令 $m=O(\sqrt{nq})$，在树上随机撒 $m$ 个点建虚树，我们知道每个点到最近关键点的距离期望是 $O(\dfrac nm)$ 的。由于给出了一个拓扑序，所以可以通过倒着扫两遍再拿两个 `bitset` 辅助做到 $\dfrac{2n}w+O(m)$ 空间的额外开销。

然后一条路径就可以拆成边角部分的 $O(\dfrac nm)$ 个点+虚树上的一条路径，用平衡树存边角部分，并且用全局平衡二叉树维护虚树链加链求和可以做到 $O(m)$ 的额外空间开销。存父亲可以压个位做到 $\dfrac{n\log n}w$ 空间，于是我们做到了 $\dfrac{n(\log n+2)}w+O(\sqrt{nq})$ 空间，$O(\sqrt{nq}\log n)$ 时间。

如何找到虚树上的链确实是个问题，这个可以先无脑往上跳到第一个关键点，然后判一下这两个关键点的位置关系就行。这一步几乎没有空间开销，因为可以直接利用做树剖时得到的信息。

但是这个做法没有考虑初值。不过我们注意到权值的特殊生成方式，于是可以加上一个分段打表，合适选取 $B$ 可以做到 $n\Big(\dfrac{\log n+2}w+\dfrac 1B\Big)+O(\sqrt{nq})$ 空间，$O\big(\sqrt{nq}(\log n+B)\big)$ 时间。

其实我们还有一个空间理论更优的做法。

考虑把有用的点拉出来建虚树就解决了，但这样需要查询一个点所在的虚链是哪一条，这个由于没法存只能暴力跳父亲，然后这样出题人就可以轻松把你卡掉。

但如果我们用前面那个做法，先随 $O(q)$ 个点建虚树呢？

我们发现，找所在虚链的复杂度变成期望 $O(\dfrac nq)$ 了。用 LCT 大力维护虚树，加入点时暴力重构有用部分，用分段打表加速查权值，就可以做到 $n\Big(\dfrac{\log n+2}w+\dfrac 1B\Big)+O(q)$ 空间，$O(nB+q\log n)$ 时间了。

因为退役了所以没有代码，有兴趣的可以尝试实现一下。。。

---

## 作者：orz_z (赞：3)

### P8353 [SDOI/SXOI2022] 无处存储

树路径加值路径求和，强制在线。

$n \leq 7\times 10^6$，$q \leq 5\times 10^4$，时限 $5\text{s}$，空限 $64\text{MB}$。

##### sol

看空间限制，$\mathcal O(n)$ 大小的数组最多只能开两个。

首先排除线段树做法，树状数组做法三个 $\mathcal O(n)$，也不行。

考虑分块，时空 $\mathcal O(\sqrt n)$。

既然用了分块，那么就要彻彻底底，排除所有 $\mathcal O(\log n)$ 做法，考虑树分块。

随机撒点，建虚树，分类讨论跳关键点间的块链即可。

时间复杂度 $\mathcal O(q\sqrt n)$，空间复杂度 $\mathcal O(2n+\sqrt n)$。

代码不给了。

---

