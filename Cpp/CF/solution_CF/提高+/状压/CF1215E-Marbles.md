# Marbles

## 题目描述

## 题目大意

有 n $ (n \le 4 * 10^5) $ 个珠子 ， 第$i$个珠子颜色是$ c_i (c_i \le 20)$ , 每次操作把**相邻**的两个珠子交换。现在要把相同颜色的珠子排列在相连的一段，问至少要多少次操作 。

## 样例 #1

### 输入

```
7
3 4 2 3 4 2 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5
20 1 14 10 2
```

### 输出

```
0
```

## 样例 #3

### 输入

```
13
5 5 4 4 3 5 7 6 5 4 4 6 5
```

### 输出

```
21
```

# 题解

## 作者：Sooke (赞：25)

### 简要题意

称序列 $a_1\ \dots\ a_n$ 连续的，当且仅当如果 $a_l = a_r$ ，那么 $\forall\ i \in [l,\,r],\ a_i = a_l = a_r$ 。

给定序列，求最少交换相邻元素多少次使得序列连续。

---

### 解题思路

我们发现，“冒泡排序”能使得序列连续，尽管不是最优答案，但是在排序的意义下，交换次数已经最少了。

即有一个引理：

> 将一个序列排序最少交换相邻元素的次数等于该序列的逆序对数。

粗略证明：

> 每次交换两个相邻的逆序对都会使得逆序对减一，逆序对等于零时排序结束。

但是我们要让序列连续，而不是排序，怎么办？

其实本质相同，无非给 $20$ 种数，每种数赋一个互不相同的权值，按照权值排序而已。

联立数据范围，我们想到状压。

设 $f[i]$ 表示已选的数的状态集合（注意，每选择一个数，意味着给其赋一个比之前选的数都大，比之后选的数都小的权值），**集合中的数**权值逆序对的最小值。

有点难理解，假设有一个序列 $3,\,2,\,1,\,1$ ，$f[3] = f[(011)_2] \text{（集合中有数 1, 2）} = 0$ ，注意 $f[3] \neq 2$ ，因为只要给数 $1$ 赋权值 $2$ ，给数 $2$ 赋权值 $1$ ，数 $3$ 不在集合里不管，权值构成的序列应是 $*,\,1,\,1,\,2$ ，没有逆序对，故 $f[3] = 0$ 。

重点来了——转移，为求 $f[i]$ ，从 $i$ 表示的集合中枚举一个数 $u$ ，表示 $u$ 是新选的数，$j$ 为剔除 $u$ 后的集合。

枚举出 $u$ 之后，再从集合 $j$ 中枚举 $v$ ，根据上述，$v$ 比 $u$ 先选，所以在序列中，每一个 $l < r,\,a_l = u,\,a_r = v$ 都构成一个逆序对，当然我们不可能在枚举 $u,\,v$ 之后直接计算这个对吧！$1 \le u,\,v \le 20$ ，肯定会重复直接计算多次，不如预处理 $w[u][v]$ 表示有多少 $(l,\,r)$ 满足 $l < r,\,a_l = u,\,a_r = v$ 吧！这样求出 $sum = \sum\limits_{v \in j}w[u][v]$ ，$f[i] = \max(f[i],\,f[j] + sum)$ 就完成了 $i$ 中枚举 $u$ 的转移！

最简单粗暴的：预处理时，枚举 $u,\,v$ ，然后只留下 $a_i = u,\,a_i = v$ ，然后 $O(n)$ 扫过去计数器统计，时间复杂度是 $O(n \times 20 \times 20)$ ，稍微有点卡。

考虑去掉一个 $20$ ，只扫一遍，统计 $cnt[u]$ 表示扫到现在 $a_i = u$ 的个数，如果当前 $a_i = v$ ，枚举 $u$ ，令 $w[u][v]$ 加上 $cnt[u]$ 即可。

时间复杂度 $O(2^{20} \times 20 \times 20 + n \times 20)$ ，实际会跑得更快 。

---

### 代码实现

要开 $\text{long long}$ 哦！

```cpp
#include <bits/stdc++.h>

inline int read() {
    char c; int x; for (c = getchar(); !isdigit(c); c = getchar());
    for (x = 0; isdigit(c); c = getchar()) { x = x * 10 + c - '0'; } return x;
}

const int N = 20, M = 5e5 + 5, A = 1 << N;

int n, m, all, a[M], cnt[N];
long long w[N][N], f[A];

int main() {
    n = 20; m = read(); all = 1 << n;
    for (int i = 0; i < m; i++) {
        a[i] = read(); a[i]--; cnt[a[i]]++;
        for (int j = 0; j < n; j++) {
            w[j][a[i]] += cnt[j];
        }
    }
    for (int i = 1, j; i < all; i++) {
        f[i] = 1e18;
        for (int u = 0; u < n; u++) {
            if (1 << u & i) {
                j = 1 << u ^ i;
                long long sum = 0;
                for (int v = 0; v < n; v++) {
                    if (1 << v & j) { sum += w[u][v]; }
                } f[i] = std::min(f[i], f[j] + sum);
            }
        }
    }
    printf("%I64d\n", f[all - 1]);
    return 0;
}
```

---

## 作者：Gu_Pigeon (赞：7)

### 前置知识：

- 状态压缩DP
- 逆序对（或许不用）

## 原题：

> Monocarp has arranged $n$ colored marbles in a row. The color of the $i$-th marble is $a_i$. Monocarp likes ordered things, so he wants to rearrange marbles in such a way that all marbles of the same color form a contiguos segment (and there is only one such segment for each color).
>
> In other words, Monocarp wants to rearrange marbles so that, for every color $j$, if the leftmost marble of color $j$ is $l$-th in the row, and the rightmost marble of this color has position $r$ in the row, then every marble from $l$ to $r$ has color $j$.
>
> To achieve his goal, Monocarp can do the following operation any number of times: choose two neighbouring marbles, and swap them.
>
> You have to calculate the minimum number of operations Monocarp has to perform to rearrange the marbles. Note that the order of segments of marbles having equal color does not matter, it is only required that, for every color, all the marbles of this color form exactly one contiguous segment.
>
> ### Input
>
> The first line contains one integer $n$ $(2 \le n \le 4 \cdot 10^5)$ — the number of marbles.
>
> The second line contains an integer sequence $a_1, a_2, \dots, a_n$ $(1 \le a_i \le 20)$, where $a_i$ is the color of the $i$-th marble.
>
> ### Output
>
> Print the minimum number of operations Monocarp has to perform to achieve his goal.

## 题意：

给一个长度为n的序列，求出最少交换相邻数字的次数，使得相同的数字在一条连续的线段中。

其中$2 \le n \le 4 \cdot 10^5$, 对于其中每个数字$(1 \le a_i \le 20)$

束手无策？一脸懵逼？~~赛场上我也是这样~~

如果稍稍修改一下题目要求呢？

"如果题目要求最终的颜色要从小到大排序就好了，这样就只用求逆序对了……"

$\textit{\textsf{That's it!}}$

所以我们只需要：

## 枚举每一个数字完成交换后的位置

时间复杂度 $\text O(a!)$，妥妥 $ \small\color{#052242}\textsf{TLE} $

所以：

| | $ \tiny\textsf{bang} $ | |
|-|:-:|-|
| 我该怎么 | 办 | 呢 |

我们考虑将每一种数字按最终答案里的顺序，向左挪动，直至到达其在最终答案的位置，在该过程中，显然会形成一个**前半部分已经“排序”完毕而后半部分需要解决的序列**

而我们只需要使得后半部分的待解决序列中的数字转移到已解决序列中，就可以解决这一个子问题，转移到一个新的状态

所以，我们换一个状态枚举：**数字 $a_i$ 是否已经“排序”**

用0来表示该数字还未处理，1表示已经有序。

然后，就是正解的登场时间：

# $\textbf{状压DP}$

用一个二进制数 `i` 来表示状态，则有转移方程：

`f[i] = f[i - (1 << j)] + ` 所有数值为 `j` 的位置转移到前半部分需要跨过的其他数字个数

那么到此这题~~就结束了~~还有一个问题：如何求出上式的

> 所有数值为 `j` 的位置转移到前半部分需要跨过的其他数字个数

呢？

预处理就好咯。。。

用数组 `pr[20][20]` 记录某一种值的所有数字的左边有多少个另一种数字

有点绕……其实 `pr[x][y]` 记录了所有的数对 `(i, j)` ，使得 `i > j` 且 `a[i] == x && a[j] == y` 的个数，可以结合代码理解一下……

那么将一类数字挪到左半部分，只需要跨过右半部分的数字就可以了。

那么**真正的**状态转移方程如下：

`f[i] = f[i - (1 << j)] + sigma(pr[j][k]) `，其中 `k` 要满足状态 `i` 的第 `k` 位为 `0`

那么，本题也就算是通过了。~~又双叒叕AC了一道灰题，真开心~~

$\large\textit{Code Below}$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 524288
#define int long long //反正都要开ll，不如直接define（
long long f[1 << 20], pr[30][30], n, a[N], mp[30], tot, cnt[30];

signed main()
{
	scanf("%lld", &n);
	memset(mp, -1, sizeof mp);
	for (int i = 1; i <= n; i++) 
	{
		scanf("%lld", a + i);
		if (!~mp[a[i]]) mp[a[i]] = tot++;
	}//在实际的实现中，我使用了映射，使数字范围从零开始，方便dp
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < tot; j++) 
			pr[mp[a[i]]][j] += cnt[j];
		cnt[mp[a[i]]]++;
	}//通过奇（xia）怪（gao）方式计算出pr数组
	memset(f, 0x3f, sizeof f);//初始化dp数组
	f[0] = 0;//边界条件
	for (int i = 1; i < 1 << tot; i++)
	{
		for (int j = 0; j < tot; j++)
		{
			if ((i >> j) & 1)
			{
				int tmp = 0;
				for (int k = 0; k < tot; k++)
					if (!((i >> k) & 1) && j != k) tmp += pr[j][k];
				f[i] = min(f[i], f[i ^ (1 << j)] + tmp);//上述转移方程
			}
		}
	}
	printf("%lld", f[(1 << tot) - 1]);//最终答案即为所有数字都进入左半部分
}
```

> 首次通过了题目 [Marbles](/problem/CF1215E) ，恭喜你！（


---

## 作者：Link_Cut_Y (赞：3)

首先众所周知，将一个序列排序所需的最小交换次数就是它的逆序对个数。

那么将一个序列变成几个连续段怎么办呢？一种方法是将它每个元素重新定权，然后求逆序对个数。

所以这道题最简单的方法就是直接 $O(n !)$ 枚举每个数的新权，然后 $O(n \log n)$ 求遍逆序对。这样复杂度 $O(V! \times n \log n)$，明显不可过。

考虑优化。首先考虑如何快速地求出逆序对。可以假设有这样一个序列：

$1\ 2\ 2\ 1\ 1\ 3\ 2\ 1$

可以考虑从小到大加入这些数。比如先加入了 $1$，然后加入 $2$，序列中变成了这样：

$1\ 2\ 2\ 1\ 1\ \ \ 2\ 1$

可以发现，新增的逆序对个数就是每个 $2$ 后面 $1$ 的个数的和。插入 $3$ 时同理，增加的逆序对个数就是每个 $3$ 后面 $1, 2$ 的个数和。

所以可以提前处理出每个数后面比他小的个数，然后按照上面的方法一个一个插入点就可以了。

那么考虑这道题。我们可以由小到大赋权。假设现在要赋的权为 $i$，前 $i - 1$ 的权已经定完了。假设前 $i - 1$ 的权分别覆盖了原本权值为 $a_1, a_2 \cdots a_{i - 1}$ 的点。那么将权值 $i$ 赋给权值为 $a_j$ 号点，新增的答案就是权值等于 $a_j$ 的每个位置后面权值为 $a_0, a_1 \cdots a_{i - 1}$ 的权值和的和。

这个插入权值怎么搞呢？可以使用状压 dp 的思路：设 $f_{i}$ 表示已经将状态为 $i$ 的点定权了，目前的逆序对个数。$i$ 中某位为 $1$ 表示该权值已经被定权，反之未被定权。每次转移的时候，枚举定新权的是那个，然后看一下增加的逆序对个数就可以了。

时间复杂度 $O(V ^ 2 2 ^ V)$。

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#define int long long

using namespace std;

const int N = 400010;

int n, m;
int a[N];
int bin[22];
int s[N][22], S[22][22];
int f[1 << 22];

signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; i ++ )
		scanf("%lld", &a[i]);
	for (int i = 1; i <= n; i ++ )
		bin[a[i]] ++ ;
	for (int i = 1; i <= 20; i ++ )
		if (bin[i]) bin[i] = m ++ ;
	for (int i = 1; i <= n; i ++ )
		a[i] = bin[a[i]];
	for (int i = n - 1; i >= 1; i -- )
		for (int j = 0; j < m; j ++ )
			s[i][j] = s[i + 1][j] + (a[i + 1] == j);
	for (int i = 1; i <= n; i ++ )
		for (int j = 0; j < m; j ++ )
			S[a[i]][j] += s[i][j];
	memset(f, 0x3f, sizeof f);
	f[0] = 0;
	for (int s = 0; s < 1 << m; s ++ )
		for (int i = 0; i < m; i ++ )
			if (!((s >> i) & 1)) {
				int cnt = 0;
				for (int j = 0; j < m; j ++ )
					if ((s >> j) & 1)
						cnt += S[i][j];
				f[s | (1 << i)] = min(f[s | (1 << i)], f[s] + cnt);
			}
	printf("%lld\n", f[(1 << m) - 1]);
	return 0;
}
```

---

## 作者：x义x (赞：3)

首先，众所周知，把一个序列变为不降所需要的相邻元素交换次数就是这个序列的逆序对数。这题显然与这个结论有关。

那么这题要我们干的是什么呢？就是按颜色变为不降，只不过颜色的大小顺序我们可以任意指定而已。比如样例1指定的就是$3<4<2$，样例2指定的就是$20<1<14<10<2$。

看到颜色数最多20，显然是状压DP。定义$f[s]$是$s$对应的颜色的大小顺序已经安排好了的最小逆序对数。

假设已经安排好$k_1<k_2<\dots<k_m$，我们选择一个在$s$中没出现过的$k_{m+1}$。那么新的状态就要加上$(k_1,k_{m+1})$之间的，满足$i<j,a_i=k_1,a_j=k_2$的$(i,j)$对数。这个预处理一下就好了。

代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

int N,A[400005];
int cnt[25];
ll B[25][25];
ll f[2000005];

int main(){
	scanf("%d",&N);
	for(int i=1;i<=N;i++){
		scanf("%d",&A[i]);
		for(int j=1;j<=20;j++)
			B[j][A[i]]+=cnt[j];
		cnt[A[i]]++;
	}
	memset(f,63,sizeof(f));
	f[0]=0;
	for(int s=0;s<(1<<20);s++)
	for(int i=1;i<=20;i++)if(!((s>>(i-1))&1)){
		ll tmp=0;
		for(int j=1;j<=20;j++)if((s>>(j-1))&1)
			tmp+=B[j][i];
		f[s|(1<<(i-1))]=min(f[s|(1<<(i-1))],f[s]+tmp);
	}
	printf("%I64d\n",f[(1<<20)-1]);
	
	return 0;
}

```


---

## 作者：CYJian (赞：3)

注意到 $a_i$ 很小, 所以我们可以考虑给 $a_i$ 重新编号后, 将 $a_i$ 按照新的编号排序, 枚举完这些情况后最小的逆序对数就是我们想要的答案了...

但是这样是 $20!$ 的.不能接受. 考虑状压dp: 设状态 $f[s]$ 表示编号集合为 $s$ 的集合内的数还没给新编号的时候最小的逆序对数. (这里考虑从小到大给编号)

那么如果这个时候我们想要给 $i$ 编号, 那么这时候 $s$ 里头的还没有被编号的数就会对 $i$ 有逆序对个数的贡献. 所以我们就预处理一个 $g[i][s]$ 表示 $s$ 这个集合还没有被编号的时候, 给 $i$ 编号会多出来的逆序对的个数.

然后我们就发现相当于是求: 对于每一个为 $i$ 的数的位置, 求前面有多少个数属于 $s$ 这个集合. 考虑如果我们知道了对于每一个为 $i$ 的数的位置, 前面有多少个数是 $j$ , 那么这就是一个集合或卷积的事情了...写一个 $FMT$ 就完事了...

求每一个为 $i$ 的数的位置, 前面有多少个数是 $j$, 这个就边读入边搞就完事了...

下面是代码...(主要看main函数, 除去冗杂的东西最后的代码不超过20行...)

```cpp
#include <bits/stdc++.h>

using namespace std;

#define FILE(Name) freopen(Name".in", "r", stdin), freopen(Name".out", "w", stdout)

namespace io {
	const int SIZE = (1 << 21) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55]; int f, qr;
	#define gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
	inline void flush () {
		fwrite (obuf, 1, oS - obuf, stdout);
		oS = obuf;
	}
	inline void pc (char x) {
		*oS ++ = x;
		if (oS == oT) flush ();
	}
	inline void gtc (char &x) {
		x = gc();
	}
	template <class I>
	inline void gi (I &x) {
		for (f = 1, c = gc(); c < '0' || c > '9'; c = gc()) if (c == '-') f = -1;
		for (x = 0; c <= '9' && c >= '0'; c = gc()) x = x * 10 + (c & 15); x *= f;
	}
	template <class I>
	inline void print (I x) {
		if (!x) pc ('0'); if (x < 0) pc ('-'), x = -x;
		while (x) qu[++ qr] = x % 10 + '0',  x /= 10;
		while (qr) pc (qu[qr --]);
	}
	struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
}
using io :: gi;
using io :: gtc;
using io :: print;
using io :: pc;

template<typename T>
inline void chkmin(T&a, T b) { a = a < b ? a : b; }

typedef long long ll;
typedef double db;

const int MAXN = 400100;

ll f[1 << 20 | 1];
ll g[20][1 << 20 | 1];
int S[MAXN + 1][20];

int main() {
#ifndef ONLINE_JUDGE
	FILE("e");
#endif
	int n; gi(n);
	for(int i = 1; i <= n; i++) {
		int a; gi(a); --a;
		for(int j = 0; j < 20; j++)
			S[i][j] = S[i - 1][j] + (a == j);
		for(int j = 0; j < 20; j++)
			if(a != j)
				g[a][1 << j] += S[i][j];
	} int S = 1 << 20;
	for(int i = 0; i < 20; i++)
		for(int j = 0; j < 20; j++)
			for(int k = 0; k < S; k++) if(k & (1 << j))
				g[i][k] += g[i][k ^ (1 << j)];
	memset(f, 127, sizeof(f));
	f[S - 1] = 0;
	for(int i = S - 1; i >= 0; --i) 
		for(int j = 0; j < 20; j++) if(i & (1 << j))
			chkmin(f[i ^ (1 << j)], f[i] + g[j][i]);
	print(f[0]); pc('\n');
	return 0;
}
```

---

## 作者：bloodstalk (赞：2)

首先有一个结论：**将一个序列排序最少交换相邻元素的次数等于该序列的逆序对数**。这个证明可以看 Sooke 神的题解，这里就不再详细说明。

那我们就是根据这个来往下推。我们观察这个结论，它给出的最终状态是一个**排序好的状态**，而我们的目标，只要是**连续**就可以了。

由此，我们想到，可以给原序列的每种颜色赋成一个新的颜色，拿两种颜色举例，这是原序列：

$$
1 \ 2 \ 2 \ 1 \ 2 \ 1
$$

我们赋给它们新的颜色，因为一共就两种颜色，所以 $1$ 变成 $2$，$2$ 变成 $1$：

$$
2 \ 1 \ 1 \ 2 \ 1 \ 2
$$

然后我们对于这两种情况取 $\min$ 就可以了。颜色数往上同理。到了这一步，我们就有了一个很朴素的想法，$O(m!)$ 地枚举排列，赋值，这里 $m$ 是颜色数，但是 $m\leq 20$，不能通过。而又因为这个取值范围，我们可以想到状压。

我们把每种颜色压入状态，设 $f_i$ 表示当前状态为 $i$ 的最小值，其中如果 二进制下 $j$ 这一位为 $1$，那么就说明 $a_j$ 已经被赋值上了一个新的权值。因为我们要统计逆序对，所以我们应是从小到大进行赋权的。

那么我们考虑该怎么转移，我们找到一个二进制下为 $0$ 的位置 $i$，假设我们之前已经把 $1\sim k-1$ 赋值给了 $k-1$ 个位置，我们设这 $k-1$ 个位置为 $p_1,p_2,p_{k-1}$。那么这次转移新产生的贡献就是 $\displaystyle \sum_{j=1}^{p-1} S(i,p_j)$，其中 $S(i,j)$ 表示的是颜色 $j$ 会对 $i$ 产生多少类似于逆序对的贡献，举个例子，当前这个是原序列：

$$
1 \ 3 \ 1 \ 2 \ 3 \ 2 \ 1
$$

我们选择将 $3$ 赋权成颜色 $1$，$2$ 不变，那么新序列就是

$$
0 \ 1 \ 0 \ 2 \ 1 \ 2 \ 0
$$

其中 $0$ 表示还没赋权，那么现在我们把 $1$ 赋权成 $3$，那么此时产生的贡献就是 $S(1,2) + S(1,3) = 4 + 3 = 7$，我们回到原序列看看是怎么来的，以 $S(1,2)$ 举例：第一个 $1$ 后面有两个 $2$，第二个 $1$ 后面也是两个 $2$，第三个 $1$ 后面没有 $2$，那么 $S(1,2)$ 就是 $2+2=4$，其实它就是做了一个**对于每个颜色 $1$，都统计一下它后面有几个 $2$，然后再把这些贡献加起来的过程**。而到了新赋权的序列中，这个 $S(1,2)$ 就刚好是当 $1$ 赋权为 $3$，$2$ 不变的时候，产生的逆序对数量，于是，我们就可以在 $O(m)$ 的时间内统计贡献了。

接下来就是如何预处理 $S(i,j)$ 了，首先你可以预处理一个 $s(i,j)$，表示从 $i$ 往后颜色 $j$ 有多少，就是做了一个后缀和，这是 $O(nm)$ 的。然后再通过 $s(i,j)$ 推出 $S(i,j)$：假设当前位置的颜色是 $a_i$，那么 $S(a_i,j)$ 就会加上 $s(i,j)$ 的贡献，同理，这也是 $O(nm)$ 的，然后状压的过程是 $O(2^m \times m \times m)$ 的，$4s$ 足够跑过去了。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define ll long long
#define next nxt
#define re register
#define il inline
const int N = 4e5 + 5;
const int M = 1 << 21;
using namespace std;
int max(int x,int y){return x > y ? x : y;}
int min(int x,int y){return x < y ? x : y;}

int n,m;
int a[N],b[25];
int f[M],s[N][25],S[25][25];

il int read()
{
	int f=0,s=0;
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f |= (ch=='-');
	for(; isdigit(ch);ch=getchar()) s = (s<<1) + (s<<3) + (ch^48);
	return f ? -s : s;
}

signed main()
{
	n = read();
	for(re int i=1;i<=n;i++) a[i] = read(),b[a[i]]++;
	for(re int i=1;i<=20;i++) if(b[i]) b[i] = m++;//离散化
	for(re int i=1;i<=n;i++) a[i] = b[a[i]];
	for(re int i=n-1;i>=1;i--)
		for(re int j=0;j<m;j++)//s[i][j]表示从i往后颜色j有多少
			s[i][j] = s[i+1][j] + (a[i+1] == j);
	for(re int i=1;i<=n;i++)
		for(re int j=0;j<m;j++)//S[i][j]表示颜色为j会对i产生多少类似于逆序对的贡献
			S[a[i]][j] += s[i][j];
	memset(f , 0x3f , sizeof f);
	f[0] = 0;
	for(re int s=0;s<(1<<m);s++)
		for(re int i=0;i<m;i++)
			if(!(s & (1<<i)))
			{
				int cnt = 0;
				for(re int j=0;j<m;j++)
					if(s & (1<<j)) cnt += S[i][j];//用到了我们预处理的东西
				f[s|(1<<i)] = min(f[s|(1<<i)],f[s]+cnt);
			}
	cout << f[(1<<m)-1];
	return 0;
}
```


---

## 作者：xixiup (赞：2)

## 思路分享

我们可以发现，这道题 $m$ 特别小，只有 $20$，所以我们可以考虑使用状压 $DP$。

又因为每次只能交换相邻的两个，所以我们可以考虑逆序对。但是不是只要求相同颜色的相邻就行了么？所以我们就可以请出状压 $DP$。

设 $DP_s$ 为当前状态为 $s$ 时的最优方案。举个例子，$dp_{10}=dp_{(01010)_2}$，就表示前 $2$ 个位置放的是 $2$ 与 $4$。

然后我们就可以根据题意列出状态转移方程：
$$
\boxed{dp_s=\max(dp_s,dp_{s1}+sum)}
$$
其中 $s1$ 就是 $s$ 在某一位 $1$ 上变成 $0$，$sum$ 则是对于更改的这一位 $i$，$s$ 的所有为 $1$ 的位置 $j$ 的 $\sum pd_{i,j}$ 其中 $pd_{i,j}$ 为序列中所有的有 $j$ 在 $i$ 前面的对数。

然后我们就可以 $DP$ 处理了。

最后放个部分代码：

```cpp
for(int s=1;s<(1<<m);s++){
	for(int i=0;i<m;i++){
		if(((s>>i)&1)==1){
			int s1=s-(1<<i),sum=0;
			for(int j=0;j<m;j++){
				if(((s1>>j)&1)==1){
					sum+=pd[i+1][j+1];
				}
			}
			dp[s]=min(dp[s],dp[s1]+sum);
		}
	} 
}
```


---

## 作者：xukuan (赞：2)

状态压缩动态规划

**状态：**

$f_i$中状态i表示二进制为1的数已经被移到了最左边

**重复子问题:**

对于数列S，让数字i完成的最小费用是重复的

**最优子结构：**

对于数列S，让数字i完成的最小费用取到最优

**无后效性：**

对于数列S，让数字i完成的最小费用与之前的取法无关

**状态转移方程：**

有点小坑。

显然无法直接转移，设置一些东西来辅助转移

$b_{a_i,b_j}=\sum_{i=1,j=1}^{i<=n,j<=n} a_i<a_j$

设$s=(1<<(i-1))|(1<<(j-1))$

$g_{t,j}=\sum_{t=s}^{t<(1<<20)} a_{i,j}$

可以发现，g数组表示在状态i下，最后移的一个数字是j的最小步数

其中$t=s$,每次变换$t=(t+1)|s$

现在就可以转移了：

$f_i=min f_{i xor (1<<(j-1))}+g_{i,j}$,满足$i&(1<<(j-1))!=0$

**喜闻乐见代码系列：**

```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

const ll INF=1ll<<60;
ll n,a[30][30],g[1<<20][22],f[1<<20];
vector<ll> q[30];

inline ll read(){
	ll x=0,tmp=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') tmp=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return tmp*x;
}

inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	ll y=10,len=1;
	while(y<=x){
		y=(y<<3)+(y<<1);
		len++;
	}
	while(len--){
		y/=10;
		putchar(x/y+48);
		x%=y;
	}
}

int main(){
	n=read();
	for(ll i=1; i<=n; i++) q[read()].push_back(i);
	for(ll i=1; i<=20; i++){
		for(ll j=1; j<=20; j++){
			if(i==j) continue;
			for(ll k=0,l=0; k<q[i].size(); k++){
				for(; l<q[j].size()&&q[i][k]>q[j][l]; l++);
				a[i][j]+=l;
			}
			ll s=(1<<(i-1))|(1<<(j-1));
			for(ll t=s; t<(1<<20); t=(t+1)|s) g[t][j]+=a[i][j];
		}
	}
	for(ll i=1; i<(1<<20); i++){
		f[i]=INF;
		for(ll j=1; j<=20; j++){
			if(i&(1<<(j-1))) f[i]=min(f[i],f[i^(1<<(j-1))]+g[i][j]);
		}
	}
	cout<<f[(1<<20)-1]<<endl;
	return 0;
}
```

---

## 作者：XuYueming (赞：1)

## 前言

题目链接：[Codeforces](https://codeforces.com/problemset/problem/1215/E)；[洛谷](https://www.luogu.com.cn/problem/CF1215E)。

[更好的食用体验](https://www.cnblogs.com/XuYueming/p/18397622)。

## 题意简述

给定长度为 $n$ 的序列 $a$，你可以交换相邻元素，请问最少交换多少次使得序列连续，即对于每种颜色，其在序列中出现的位置都是连续一段。

$m = \max \{ a_i \} \leq 20$，$n \leq 4 \times 10 ^ 5$。

## 题目分析

对于“连续的序列”，不放看做我们给每种颜色钦定了一个优先级，然后按照优先级排了一个序。想到一个定理，将一个序列排序最少交换相邻元素的次数等于该序列的逆序对数。证明很简单，考虑冒泡排序的过程，我们每次交换相邻的逆序对，能够减少一对逆序对，而逆序对为 $0$ 的时候，序列有序。由于每次操作做多使逆序对减少 $1$，所以操作次数至少是逆序对个数，而我们有证明了按照冒泡排序的方式，一定存在一种方式达到这个下限，所以得证。

看到数据范围，很容易想到状压 DP。记 $f_{S}$ 表示只考虑集合 $S$ 中的颜色，使得其连续的最小交换次数。最后答案就是 $f_{\{i\}_{i = 1}^m}$。边界 $f_{\varnothing} = 0$。

考虑由 $f_{S \setminus \{ x \}}$ 转移到 $f_{S}$。此时 $x$ 为 $S$ 中我们钦定优先级最大的颜色，即我们需要让所有颜色为 $x$ 的数交换到 $S \setminus \{x \}$ 的右边。对于每一个 $a_i = x$ 的 $i$，交换它的次数等于它的逆序对数，即有多少个 $a_j \in S \setminus \{ x \} \land j > i$。这个预处理 $w_{u, v}$ 表示为了让颜色 $u$ 全部到 $v$ 的右边的交换次数即可。那么转移即为 $f_{S} = \min \Big \{ f_{S \setminus \{x\}} + \sum \limits _{y\in S \setminus \{x\}} w_{x, y} \Big\}$。

时间复杂度 $\Theta(m 3^m + nm)$，可以预处理优化掉转移的 $\sum$，时间复杂度：$\Theta(m 2^m + 3^m + nm)$。

## 代码

```cpp
#include <cstdio>
#include <iostream>
using namespace std;

const int N = 400010;
const int K = 20;

int n, k = 20, val[N];
int cnt[K], p[1 << K];
long long yzh[K][1 << K], dp[1 << K];

inline int lowbit(int x) {
    return x & -x;
}

signed main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &val[i]), --val[i];
		++cnt[val[i]];
		for (int j = 0; j < k; ++j)
			yzh[j][1 << val[i]] += cnt[j];
	}
    for (int i = 0; i < k; ++i) {
        p[1 << i] = i;
        for (int st = 1; st < 1 << k; ++st)
            yzh[i][st] = yzh[i][st ^ lowbit(st)] + yzh[i][lowbit(st)];
    }
	for (int st = 1; st < 1 << k; ++st) {
		dp[st] = 0x3f3f3f3f3f3f3f3f;
        for (int S = st; S; S &= S - 1) {
            int i = lowbit(S);
            dp[st] = min(dp[st], dp[st ^ i] + yzh[p[i]][st ^ i]);
        }
	}
	printf("%lld", dp[(1 << k) - 1]);
	return 0;
}
```

---

## 作者：NBest (赞：1)

# 思路
看到这道题是统计相邻交换之后操作次数，我第一反应就是求逆序对。

考虑最淳朴的暴力做法，枚举颜色之前的大小顺序关系，然后每次做一次求逆序对，复杂度 $O(n\log n |c|!)$ ($|c|$ 表示颜色种类数)。

但是光是 $20!$ 都有 $2,432,902,008,176,640,000$ 的大小，再乘上本来就已经卡到 $10^7$ 的 $n\log n$，跑 $7,000,000$ 个世纪都不一定跑的完。

发现这个巨大的复杂度是因为我们考虑了所有颜色之前的顺序关系，因此我们不需要考虑全部颜色之间的关系，只需要关注颜色两两之间的关系。我们不难发现把所有颜色块合并之后，两个颜色之间的位置关系是唯一的，即对于不同颜色 $i,j$，合并之后所有颜色为 $i$ 的要么全部在颜色为 $j$ 的左侧，要么全部在右侧 ~~不是废话吗~~。

所以我们考虑预处理颜色两两之间的关系造成的贡献，然后两两之间统计答案，这个过程的复杂度为 $O(n|c|^2)$。

令 $w[i][j]$ 表示在**去掉其他所有颜色**的情况下，颜色 $i$ 全部移动到颜色 $j$ 左侧对答案的最少贡献。

这个时候我们只需要一个颜色一个颜色的加，把这个颜色的块全部放到左边（右边也行），然后在新加一块之前，我们只需要计算这个颜色与前面所有颜色之间的贡献和再加上前面的所有颜色对答案的贡献即可。

发现前面答案最优推出后面的答案也最优，并且状态数很少，考虑状压 dp。

我们令 $f[S]$ 表示已插入状态为 $S$ 时对答案的最小贡献，那么我们可以得到以下转移：

$f[S]=min(f[S-i]+\sum \limits_{j\in S,j!=i}w[j][i]) \ (i\in S)$。

$\sum \limits_{j\in S,j!=i}w[j][i]$ 是复杂度瓶颈，可以通过 $O(|c|^2)$ 预处理 $sum[i]$ 解决。

总复杂度 $O(2^{|c|}|c|^2+|c|^2n)$，虽然有点卡，但是常数优化以后在 CodeForces 少爷机上也能在 $1s$ 内跑完。

结合代码理解可能会更简单哦~
## $Code$
```cpp
int n,a[400005],b[22][400005];//b[c][i],表示i前面有多少个颜色为c的珠子
ll w[22][22],f[1<<20],sum[22];
int main(){
    n=read();
    memset(f,0x3f,sizeof(f));
    for(int i=1;i<=n;i++){
        a[i]=read();
        b[a[i]][i]++;
        for(int j=1;j<=20;j++){
            b[j][i]+=b[j][i-1];//前缀和优化
        }
    }
    for(int l=1;l<=20;l++){
        f[1<<l-1]=0;
        for(int r=1;r<l;r++){//两边一起加，常数减半
            for(int i=1;i<=n;i++){
                if(a[i]==l)w[l][r]+=b[r][i];
                else if(a[i]==r)w[r][l]+=b[l][i];
            }
        }
    }
    for(int s=3;s<(1<<20);s++){
        if(__builtin_popcount(s)<2)continue;
        for(int i=1;i<=20;i++){
            if(!(s&(1<<i-1)))continue;
            for(int j=1;j<i;j++){//细节两边一起加，常数砍半
                if(!(s&(1<<j-1)))continue;
                sum[i]+=w[j][i];
                sum[j]+=w[i][j];
            }
        }
        for(int i=1;i<=20;i++){
            if(!(s&(1<<i-1)))continue;
            f[s]=min(f[s^(1<<i-1)]+sum[i],f[s]);
            sum[i]=0;
        }
    }
    cout<<f[(1<<20)-1];
}
```

---

## 作者：Aurora_Borealis_ (赞：1)

首先不难发现数据范围中 $c_i \leq 20$ 不太正常，看到 $20$ 进一步想到以颜色为状态进行子集状压 dp。

同时，题中“交换相邻数字”不难想到冒泡排序求逆序对的思想，于是题面可以转化为：

> 对于每种颜色设计一个整数作为“代号”，求逆序对，最优安排时的逆序对即为答案。

于是设 $f_i$ ，$i$ 为一个 $20$ 位的二进制数，第 $i$ 位为 $1$ 代表已经安排代号，$0$ 相反，对于枚举的每一个 $i$，枚举 $i$ 中的颜色 $j$，代表最新取的颜色，再枚举颜色 $k$，满足 $k$ 在 $i$ 中出现且 $k \neq j$，求一下 $k$ 所有点与 $j$ 所有点的逆序对总和 $sum$，所有 $k$ 的 $sum$ 之和即为转移代价。

$sum$ 可以预处理。

code:

```
#include<bits/stdc++.h>
#define ull unsigned long long
#define ll long long
#define pb push_back
#define pii pair<int,int>
#define vi vector<int>
#define imp map<int,int>
using namespace std;
const int N=400005,M=25;
int n,a[N];
ll f[1<<21],cnt[M][M];

int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=20;i++){
		for(int j=1;j<=20;j++){
			ll t=0;
			for(int k=1;k<=n;k++){
				if(a[k]==j){
					t++;
				}else if(a[k]==i){
					cnt[i][j]+=t;
				}
			}
		}
	}
	memset(f,0x3F,sizeof(f));
	f[0]=0;
	for(int i=1;i<(1<<20);i++){
		for(int j=1;j<=20;j++){
			if(i&(1<<(j-1))){
				ll sum=0;
				for(int k=1;k<=20;k++){
					if(i&(1<<(k-1))&&k!=j){
						sum+=cnt[k][j];
					}
				}
				f[i]=min(f[i],f[i-(1<<(j-1))]+sum);
			} 
		} 
	}
	cout<<f[(1<<20)-1]<<endl;
	return 0;
}

```


---

## 作者：RockyYue (赞：0)

#### 1215E

给定 $a_{1\dots n}$，每次操作为交换相邻两位，求至少多少次操作可以使将相同值的位排列成一段，其中 $n\le 4\times 10^5,1\le a_i\le 18$（原题为 $20$，稍有改动）。

#### Sol

- 一个引理是将一个序列每次交换相邻两位，交换到其有序的最少步数是其逆序对数，本题中考虑对每种数重标号，再计算逆序对数。
- 朴素方法是 $O(V!)$ 重新排列，你发现若两个排列后缀相同，则前缀中数比后缀大这部分对逆序对贡献相同，后缀亦相同，于是只需要前缀内部逆序对数最小的，设 $f_S$ 为将所有 $a_i\in S$ 的数提出来做操作的最小操作次数。
- 则转移为，$f_{S}=\min_{x\in S}\{f_{T=S-\{x\}}+\sum_{a_i\in T,a_j=x}[i>j]\}$，记 $b_{i,j}$ 为数 $i$ 序列中位置在数 $j$ 前面的对数，可以 $O(2^VV^2)$。

---

## 作者：Erica_N_Contina (赞：0)

我们先考虑怎么样可以写暴力。

### 暴力与引入

$O(k!n\log n)$

我们发现将原来的数组排序，也是一种合法的情况，那么假如说这道题要我们求的是，我们对一个数组排序，求交换次数，我们应该怎么做？

很明显，我们应该求它的逆序对。

好了，那么我们可以开始考虑本题的暴力。我们是否可以考虑对颜色进行重标号，然后再考虑上面的流程？

是可以的。我们可以枚举全排列 $p$，将颜色i重新标号为 $p_i$ 后统计当前标号方案下的逆序对数量。对所有排列都求出逆序对数量后，我们取最小值即可。

### 正解

$O(k^22^k+nk)$

我们考虑如果本题枚举全排列，那么就有 $O(k!)$ 的复杂度了，肯定是无法通过的，所以我们就考虑通过一种“搜索”来“枚举出”所有排列情况。

那么是什么搜索呢？状态压缩 dp！

我们可以定义$ $ $f_i$ 为考虑插入了 $i$ 集合中的颜色后的逆序对数量（即在原数组只考虑属于 $i$ 的颜色的项目时的逆序对数量），其中 $i$ 是状态压缩的。我们定义转移为：

- 枚举一个新要插入到集合中的颜色 $u$，规定一个颜色的重编号就是它是第几个插入到集合 $i$ 中的。那么这样我们就可以考虑到所有的重编号情况。

- 转移时，我们先枚举一个以及计算出 $f_i$ 的集合 $i$，再考虑不在集合 $i$ 中的颜色 $u$，考虑将 $u$ 插入后的贡献。为了计算贡献，我们就要枚举在 $i$ 中的颜色 $v$，考虑每个 $v$ 对 $u$ 的贡献，然后把这些贡献加起来。

- 我们发现，$v$ 对 $u$ 的贡献，就是在原数组中，有多少个 $(i,j)$ 满足 $i<j,a_i=u,a_j=v$。因为 $v$ 是在 $i$ 中的，$u$ 是我们要新插入 $i$ 的，所以重编号之后 $u$ 的编号大于 $v$ 的编号。为了优化贡献的计算过程，我们要预处理出 $w_{u,v}$ 表示上述的贡献。

为了计算 $w_{u,v}$，我们只需要枚举每一个 $u$，然后扫一遍 $a$ 数组，统计当前指针 $i$ 扫描过的 $u$ 的数量 $cntu$，在 $a_i≠u$ 时，将 $w_{u,a_i}$ 加上 $cntu$ 即可。



```C++
#include <bits/stdc++.h>
#include <queue>
using namespace std;

#define rep(i, l, r) for (int i = l, END##i = r; i <= END##i; ++i)
#define per(i, r, l) for (int i = r, END##i = l; i >= END##i; --i)
#define pb push_back
#define mp make_pair
#define int long long
#define pii pair<int, int>
#define ps second
#define pf first
#define ull unsigned long long

#define itn int
// #define inr int
// #define mian main
// #define iont int

#define rd read()
int read() {
    int xx = 0, ff = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            ff = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') xx = xx * 10 + (ch - '0'), ch = getchar();
    return xx * ff;
}
void write(int out) {
    if (out < 0)
        putchar('-'), out = -out;
    if (out > 9)
        write(out / 10);
    putchar(out % 10 + '0');
}

#define ell dbg('\n')
const char el = '\n';
const bool enable_dbg = 1;
template <typename T, typename... Args>
void dbg(T s, Args... args) {
    if constexpr (enable_dbg) {
        if (1)
            cerr << ' ';
        cerr << s;
        if constexpr (sizeof...(Args))
            dbg(args...);
    }
}


const int N = 2e6 + 5;
const int INF = 1e18;
const int M = 1e7;
const int MOD = 1e9 + 7;

bool FLA;

itn n, K;
int f[N];
int w[22][22];
int cnt[N];
itn ans = INF;
int a[N];

bool FLB;


void solve() {
    cerr << ((&FLB) - (&FLA)) / 1024.0 / 1024.0 << " Mib" << endl;
    n = rd, K = rd;

    for (int i = 1; i <= n; i++) {
        a[i] = rd - 1;
    }

    for (itn u = 0; u < K; u++) {
        // (u,v)
        itn cntu = 0;
        for (int i = 1; i <= n; i++) {
            if (a[i] == u)
                cntu++;
            else
                w[u][a[i]] += cntu;
        }
    }

    //	cdbg(w[2][3]);

    memset(f, 0x3f3f, sizeof f);
    f[0] = 0;

    for (int i = 1; i < (1 << K); i++) {
        for (int u = 0; u < K; u++) {
            if (!(i & (1 << u)))
                continue;
            int res = 0;
            int j = i ^ (1 << u);

            for (itn v = 0; v < K; v++) {
                if (!(j & (1 << v)))
                    continue;
                res += w[u][v];
            }
            f[i] = min(f[i], f[j] + res);
        }
    }

    write(f[(1 << K) - 1]);
    puts("");
}

signed main() {
    freopen("box.in", "r", stdin);
    freopen("box.out", "w", stdout);

    int T = 1;
    while (T--) {
        solve();
    }
    return 0;
}
```

---

## 作者：crashed (赞：0)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.org/problem/CF1215E)看题目。
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;~~其实就是暴力。~~  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;由于最终状态相同颜色的珠子是连续一段，所以我们可以把相同颜色的珠子“缩”起来。这样结果就可以表示为颜色的一个全排列。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;于是我们就可以想到枚举结果的排列方式。设颜色有$m$种，由于$m\le 20$，所以我们就把状态压缩一下，顺便用$DP$求解：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$DP(S)$：将$S$里面的颜色从最左边开始，连续的颜色排成一段的最小移动步数。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;然后我们考虑如何转移：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$\displaystyle DP(S)=\min_{i\in S}\left(DP(S\backslash i)+c(S\backslash i,i)\right)$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;其中$c(S,i)$表示已安排好的元素集合为$S$，第$i$种元素接成后面的连续一段的最小步数。（满足$S\cap i=\emptyset$）  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;显然，问题变成了如何高效地求出$c$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;由于$S$里面的元素已经被成段地从左端点开始排在了一起，所以我们可以把这个序列划成两个部分；一个是已经排好了的，在左侧；一个是乱序的，在右侧。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;那么对于乱序的序列来说，我们需要做的就是把第$i$种颜色从乱序的序列的左端点开始排成一段。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;考虑贪心计算这个答案。我们发现，只要这一段中原来石头的相对位置不变，那么这样的排放方法就是最优的。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;（相对位置可以理解为，给每个石子编号，号码就是它原来的下标；我们排出来新的一段中的编号从左到右是递增的）  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;设$id_i$为第$i$个位置的石头在颜色$a_i$的一段中应排的的位置。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;有了这些东西之后，$c$的一部分就比较好计算了。可以得到：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$\displaystyle c(\emptyset,i)=\sum_{j=1}^n(j-id_j)[a_j=i]$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;考虑$S$不为空集的情况。由于我们是在乱序的序列中排序的，那么这个序列中$S$里面的颜色的珠子都没有了。设：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$\displaystyle s(j,i)=\sum_{k=1}^i[a_k=j]$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;相当于对于每个$i(i\not\in S)$，它在乱序序列中的位置就是$i-\sum_{j\in S}s(j,i-1)[j\not=a_i]$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;注意！现在，我们已经知道了乱序序列的每个元素的位置。那么我们就可以直接算出来$c(S,i)$了：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$\displaystyle c(S,i)=\sum_{j=1}^n(j-\left(\sum_{k\in S}s(k,j-1)[k\not=a_j]\right)-id_j)[a_j=i]$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;对于每个颜色$i$，预处理$\sum_{j=1}^n(j-id_j)[a_j=i]$;对于每两个颜色$i$和$j$（$i\not=j$），预处理$\sum_{k=1}^ns(j,k-1)[a_k=i]$，然后对于任意的$c$就可以用$O(m)$的时间预处理出来。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;然后就可以开始$DP$了。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;这个算法的时间是$O(m^22^m)$，看着比较慢，跑着非常快。  
# 代码
```cpp
#include <cstdio>

typedef long long LL;

const LL INF = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 4e5 + 5, MAXA = 25, MAXSIZ = ( 1 << 20 ) + 5;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s < '0' || '9' < s ){ f = 1; if( s == '-' ) f = -1; s = getchar(); }
	while( '0' <= s && s <= '9' ) { x = ( x << 3 ) + ( x << 1 ) + s - '0', s = getchar(); }
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ), x = -x; }
	if( 9 < x ) write( x / 10 );
	putchar( x % 10 + '0' );
}

template<typename _T>
_T ABS( const _T a )
{
	return a < 0 ? -a : a;
}

template<typename _T>
_T MIN( const _T a, const _T b )
{
	return a < b ? a : b;
}

LL DP[MAXSIZ];
LL ps[MAXA][MAXN], change[MAXA][MAXA], cost[MAXA], t[MAXA];
int usable[MAXA], pos[MAXA];
int a[MAXN], nxt[MAXN];
int N, tot;
bool appear[MAXA];

signed main()
{
	read( N );
	for( int i = 1 ; i <= N ; i ++ )
		read( a[i] ), appear[a[i]] = true;
	for( int i = 1 ; i <= 20 ; t[i] = 0, i ++ ) 	
		if( appear[i] )
			usable[++tot] = i, pos[i] = tot;
	for( int i = 1 ; i <= N ; i ++ )
		ps[pos[a[i]]][i] ++, cost[pos[a[i]]] += i - ( t[pos[a[i]]] ++ ) - 1;
	for( int i = 1 ; i <= N ; i ++ )
		for( int j = 1 ; j <= tot ; j ++ )
			ps[j][i] += ps[j][i - 1];
	for( int i = 1 ; i <= N ; i ++ )
		for( int j = 1 ; j <= tot ; j ++ )
			if( a[i] ^ usable[j] )
				change[pos[a[i]]][j] += ps[j][i - 1];
	int up = 1 << tot, pr;
	LL c; 
	DP[0] = 0;
	for( int S = 1 ; S < up ; S ++ )
	{
		DP[S] = INF;
		for( int i = 1 ; i <= tot ; i ++ )
			if( S & ( 1 << ( i - 1 ) ) )
			{
				c = cost[i];
				pr = S ^ ( 1 << ( i - 1 ) );
				for( int j = 1 ; j <= tot ; j ++ )
					if( pr & ( 1 << ( j - 1 ) ) )
						c -= change[i][j];
				DP[S] = MIN( DP[S], DP[pr] + c );
			}
	}
	write( DP[up - 1] ), putchar( '\n' );
	return 0;
}
```

---

