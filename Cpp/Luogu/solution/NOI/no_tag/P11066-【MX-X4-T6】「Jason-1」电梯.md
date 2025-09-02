# 【MX-X4-T6】「Jason-1」电梯

## 题目背景

原题链接：<https://oier.team/problems/X4G>。

## 题目描述

一栋 $n$ 层的楼有 $m$ 部电梯，每部电梯有静止与运动两种状态。

初始时，第 $i$ 部电梯静止于第 $i$ 层。给定一个 $1 \sim m$ 的排列 $p$，你希望最终第 $i$ 部电梯位于 $p_i$ 层。

你可以进行以下两种操作：

- `0`：让时间向后运动一个时刻。
- `x`：其中 $x$ 为不超过 $n$ 的正整数。
	- 执行该操作时，需要满足：$x$ 层不存在静止的电梯；距离 $x$ 层距离最近的$^\dagger$ 静止的电梯存在且唯一。
	- 令 $y$ 为最近的静止的电梯编号，$z$ 为其位置。则电梯 $y$ **立刻**变为运动的电梯，并在 $\lvert x - z\rvert$ 时刻后的**所有操作前**到达楼层 $x$ 并变为静止的电梯。

$^\dagger$：位于 $a$ 层的一部电梯与楼层 $x$ 的距离为 $\lvert a - x\rvert$。

**注意：你需要保证，任何时刻不存在两个静止的电梯位于同一楼层。**

对于每组数据，有一个评分参数 $o$，你需要构造出总操作次数不超过 $o$ 的方案才能通过该组数据。

本题使用**自定义校验器**检验你的答案是否正确，因此若有多种满足条件的方案，你只需要输出**任意一种**。

## 说明/提示

**【样例解释 #1】**

该样例满足子任务 2 的限制。

对于第一组数据的第一组询问，不需要操作。

对于第一组数据的第二组询问：

| 操作 | 时刻 | 电梯 $1$ 位置 | 电梯 $2$ 位置 |
| :----------: | :----------: | :----------: | :----------: |
| 初始状态 | $0$ | $1$ | $2$ |
| $3$ | $0$ | $1$ | 运动 |
| $4$ | $0$ | 运动 | 运动 |
| $0$ | $1$ | 运动 | $3$ |
| $0$ | $2$ | 运动 | $3$ |
| $1$ | $2$ | 运动 | 运动 |
| $0$ | $3$ | $4$ | 运动 |
| $2$ | $3$ | 运动 | 运动 |
| $0$ | $4$ | 运动 | $1$ |
| $0$ | $5$ | $2$ | $1$ |

**【样例解释 #2】**

该样例满足子任务 7 的限制。

**【数据范围】**

**本题采用捆绑测试。**

| 子任务 | $n \le$ | $m =$ | $o = $ | 分值 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| 1 | $3$ | $2$ | $7$ | $7$ |
| 2 | $100$ | $\lfloor \frac{n}{2} \rfloor$ | $2\times(m+n)$ | $11$ |
| 3 | $40$ | $n-1$ | $3 \times n^3$ | $17$ |
| 4 | $200$ | $n-1$ | $5 \times n^2$ | $19$ |
| 5 | $4000$ | $n-1$ | $50 \times n$ | $17$ |
| 6 | $5 \times 10^{4}$ | $n-1$ | $6 \times n$ | $16$ |
| 7 | $5 \times 10^{4}$ | $n-1$ | $5 \times n$ | $13$ |

对于所有数据，$1 \le T \le 20$，$2 \le m < n \le 5 \times 10^{4}$，保证 $n, m, o$ 同时满足上述某个子任务的限制，$p$ 为 $1 \sim m$ 的排列，$1 \le Q \le 2\times 10^6$，$\sum o Q \le 2 \times 10^6$。

## 样例 #1

### 输入

```
2
2 4 2 12
1 2
2 1
1 10 5 30
5 4 3 2 1```

### 输出

```
0

9
3 4 0 0 1 0 2 0 0
16
6 6 6 6 6 0 1 0 2 0 3 0 4 0 5 0```

## 样例 #2

### 输入

```
1
1 6 5 30
5 4 3 2 1
```

### 输出

```
16
6 6 6 6 6 0 1 0 2 0 3 0 4 0 5 0```

# 题解

## 作者：irris (赞：9)

> 构造 / 排序

$*3200$，$8.5$。

---

不讲解 $n = 3$，$m = 2$ 和 $m = \lfloor \frac n2 \rfloor$ 的部分分了。红色字体表示花费的操作次数。

---

考虑 **模仿 Subtask 2** 进行操作。

令 $n \gets n - 1$ 表示要排序的电梯个数。再取 $m = \lfloor n / 2\rfloor$，我们把过程分为两个部分：

1. 将 $p_{1\dots m}$、$p_{(m+1)\dots n}$ 分别排序；
2. 归并 $p_{1\dots m}$、$p_{(m+1)\dots n}$。

## Step 1

我们将 $p_{(m+1)\dots n}$ 先集体向右平移 $1$（$\color{red}n - m$），随后将 $p_{1\dots m}$ 移动到 $p_{(n - m + 1)\dots n}$（$\color{red}m$），并且 **让移动后的部分整体有序**。

随后时刻向前移动（$\color{red}1$）。然后将所有向右平移的同理向左平移（$\color{red}n - m$），但是这里可能会出现一些情况，如果 $n$ 是偶数，那么你可能需要将 $m + 1$ 位置的电梯（如果此时已经停靠，即 $m \to m + 1$）先向左移动 $1$，再向右移动 $1$（$\color{red}2[2 \mid n]$），容易证明这不会带来任何撞机影响。

随后你最多需要让时间推移 $n$ 次，这部分的总代价即为 $\color{red}3n - m + 1 + 2[2 \mid n]$。

## Step 2

这个时候我们相当于归并排序的过程，这个过程性质最良好的一集就是 $[1, b]$ 的数复位 **只需要右移**（其中 $b = n - m$），而 $[b + 1, n]$ 的数复位 **只需要左移**。设位置 $i$ 的数需要到达的位置为 $p_i$。

如法炮制地，我们先将右侧的所有数向右平移 $1$，然后将左侧的所有数直接往右送到对应位置。随后时刻流逝 $1$（$\color{red}n - T + 1$）。

这样之后，只有可能 $p_i \leq i + 1$ 的数依然阻碍右侧的数，所以我们在上一步初始不去平移它们，而在这一个时刻将它们向右平移 $1$（$\color{red}T$），这样就不会在向左的路径上形成阻碍了。于是我们可以把右侧的数直接送到对应位置。再在下一个时刻把它们向左平移 $1$ 即可（$\color{red}n - b + T$）。最坏情况这里需要额外经过 $n + 1 - b$ 个时刻，因此总代价为 $\color{red}3n + T - 2b + 2 = n + 2m + T + 2$，其中 $T_{\max} = b - 1 = n - m - 1$，故总代价最大值为 $\color{red}2n + m - 1$。

## Step 2.1

你可能会好奇为什么这个时候 $T_{\max} = b - 1$ 而不是 $T_{\max} = b$。

事实上，$T = b$ 的时候上述做法会出现一个小问题：在这个「所以我们在上一步初始不去平移它们，而在这一个时刻将它们向右平移 $1$」一步时，我们要平移 $b$ 到位置 $b + 1$，然而位置 $b + 2$ 存在一个电梯！这个时候你就会爆炸。

然而若 $T = b$，这个时候左侧的所有 $p_i \in \{i, i + 1\}$，这是极为特殊的，如果我们要复位这样的排列，只需要将第 $b + 1$ 台电梯插入 $[1, b]$ 中的某个空隙即可，那么相当于给定 $[L, R]\ (L < R)$，我们将这个区间里的电梯循环右移。

考虑这个问题我们如何做，下面直接给出过程：

- 对于 $i$ 从 $n$ 到 $R$，指令：将电梯从位置 $i$ 移到位置 $i + 1$。
- 对于 $i$ 从 $R - 1$ 到 $L$，指令：将电梯从位置 $i$ 移到位置 $i + 2$。
- 时间流逝。
- 对于 $i$ 从 $L - 1$ 到 $1$，指令：将电梯从位置 $i$ 移到位置 $i + 1$。
- 将电梯从位置 $R + 1$ 移到位置 $L$。
- 时间流逝。
- 对于 $i$ 从 $L$ 到 $2$，指令：将电梯从位置 $i$ 移到位置 $i - 1$。
- 对于 $i$ 从 $L + 2$ 到 $n + 1$，指令：将电梯从位置 $i$ 移到位置 $i - 1$。
- 时间流逝 $R - L$ 次。

计算总代价，有 $n + 1 + 1 + 1 + L - 1 + n - L + R - L = \color{red}2n + 2 + R - L$，其中我们得到 $R = b + 1$，$L \in [1, b]$，故代价最大值为 $\color{red}2n + b + 2 = 3n - m + 2$。

---

对上述两件事情求和，最大的总代价和为 $\color{red}3n - m + 1 + 2[2 \mid n] + \max(2n + m - 1, 3n - m + 2) =  \begin{cases} 5n + 4, n = 2k + 1\\ 5n + 5, n = 2k + 2\end{cases}$。

然而我们的 $n$ 实际上被减少了 $1$，因此完全可以采用 $o = 5n$ 的限制（恰好卡进去！！！111）。

---

## 作者：EuphoricStar (赞：3)

先特判 $m = 2$：$p_1 = 1$ 时不用操作，否则操作序列为 `3 3 0 1 0 2 0`。

称 $p_i \le i$ 的点为左移点，$p_i > i$ 的点为右移点。

设左移点有 $c$ 个，左移点的 $i - p_i$ 最大值为 $dl$，右移点的 $p_i - i$ 最大值为 $dr$。

考虑这样一种置换做法。先从右往左扫，若当前点为左移点就往右移一格，否则直接移动到目标位置。这部分需要 $m$ 步。

然后经过一时刻，从左往右扫每个左移点，将其移动到目标位置。这部分需要 $c + 1$ 步。

然后经过若干个时刻使得每个点都到达了目标位置。这部分需要 $\max(dl + 1, dr - 1)$ 步。

总步数即 $m + c + 1 + \max(dl + 1, dr - 1)$。最劣的情况是 $c = m - 1$ 且最右边的点要移动到最左边，这时候的总步数是 $3m$。

但是当存在 $p_i = i + 1$ 的右移点时上述做法会出问题（称这样的右移点为关键点），因为过了过了一时刻后可能有右移点已经到了目标位置然后挡住了左移点。

考虑如果我们能进行一些交换使得所有关键点都被清除，就可以用上面的做法。

因为最后一个点一定不是关键点，所以当 $m$ 是奇数时可以忽略最后一个点。这样可以假定 $m$ 是偶数。

如果我们能把这 $m$ 个点两两配对，对于每一对若存在关键点就交换，那么进行这样的置换后关键点会全部被消除。

再特判初始的 $m = 3$：若 $2$ 为关键点则将 $1$ 移动至 $3$，$2$ 移动至 $1$，$3$ 移动至 $2$；否则若 $1$ 为关键点则将 $1$ 移动至 $2$，$2$ 移动至 $1$。

然后若 $m \equiv 0 \pmod 4$，直接对于每个 $i \equiv 0 \pmod 4$ 令 $i$ 和 $i + 2$ 配对即可。否则对于最后 $6$ 个数需要让 $i$ 和 $i + 3$ 配对。

用上述置换做法置换后，全部关键点都被清除。

这部分最劣的情况是 $m \equiv 4 \pmod 2$ 且只有 $m - 3$ 和 $m$ 需要交换，这时候的步数为 $2m + 4$。

那么总步数 $\le 5m + 4 < 5n$，可以通过。

```cpp
#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define uint unsigned
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<ll, ll> pii;

const int maxn = 50050;

int n, m, a[maxn], b[maxn], ans[maxn * 5];

void solve() {
	for (int i = 1; i <= m; ++i) {
		scanf("%d", &a[i]);
	}
	if (m == 2) {
		puts(a[1] == 1 ? "0" : "7\n3 3 0 1 0 2 0");
		return;
	}
	int tot = 0;
	if (m == 3) {
		int a1 = a[1], a2 = a[2], a3 = a[3];
		if (a[2] == 3) {
			a[3] = a1;
			a[1] = a2;
			a[2] = a3;
			ans[++tot] = 4;
			ans[++tot] = 3;
			ans[++tot] = 3;
			ans[++tot] = 0;
			ans[++tot] = 1;
			ans[++tot] = 2;
			ans[++tot] = 0;
			ans[++tot] = 0;
		} else if (a[1] == 2) {
			a[1] = a2;
			a[2] = a1;
			ans[++tot] = 4;
			ans[++tot] = 3;
			ans[++tot] = 3;
			ans[++tot] = 0;
			ans[++tot] = 1;
			ans[++tot] = 0;
			ans[++tot] = 2;
			ans[++tot] = 3;
			ans[++tot] = 0;
		}
	} else {
		for (int i = 1; i <= m; ++i) {
			b[i] = i;
		}
		for (int i = 1; i + 3 <= m - (m & 1); i += 4) {
			if (i + 5 == m - (m & 1)) {
				for (int j = 0; j < 3; ++j) {
					if (a[i + j] == i + j + 1 || a[i + j + 3] == i + j + 4) {
						swap(a[i + j], a[i + j + 3]);
						swap(b[i + j], b[i + j + 3]);
					}
				}
				break;
			}
			for (int j = 0; j < 2; ++j) {
				if (a[i + j] == i + j + 1 || a[i + j + 2] == i + j + 3) {
					swap(a[i + j], a[i + j + 2]);
					swap(b[i + j], b[i + j + 2]);
				}
			}
		}
		int dl = 0, dr = 0;
		for (int i = m; i; --i) {
			if (b[i] <= i) {
				dl = max(dl, i - b[i]);
				ans[++tot] = i + 1;
			} else {
				dr = max(dr, b[i] - i);
				ans[++tot] = b[i];
			}
		}
		ans[++tot] = 0;
		for (int i = 1; i <= m; ++i) {
			if (b[i] <= i) {
				ans[++tot] = b[i];
			}
		}
		for (int _ = 0; _ < max(dl + 1, dr - 1); ++_) {
			ans[++tot] = 0;
		}
	}
	int dl = 0, dr = 0;
	for (int i = m; i; --i) {
		if (a[i] <= i) {
			dl = max(dl, i - a[i]);
			ans[++tot] = i + 1;
		} else {
			dr = max(dr, a[i] - i);
			ans[++tot] = a[i];
		}
	}
	ans[++tot] = 0;
	for (int i = 1; i <= m; ++i) {
		if (a[i] <= i) {
			ans[++tot] = a[i];
		}
	}
	for (int _ = 0; _ < max(dl + 1, dr - 1); ++_) {
		ans[++tot] = 0;
	}
	printf("%d\n", tot);
	for (int i = 1; i <= tot; ++i) {
		printf("%d%c", ans[i], " \n"[i == tot]);
	}
}

int main() {
	int T = 1, Q;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d%*d", &Q, &n, &m);
		while (Q--) {
			solve();
		}
	}
	return 0;
}

```

---

## 作者：gcx114514 (赞：3)

一道有意思的题，感谢 [jason_sun](https://www.luogu.com.cn/user/399762) 为解法提供的思路。

首先对于第一个子任务，我们可以直接打表。

对于第二个子任务，我们发现每次询问至少有 $m$ 个连续的后缀是空的，那么我们考虑先在这些空的位置上将电梯按照相对顺序排列好。那么我们在 $0$ 直接从右往左扫一遍进行操作，后面等他们到位后在移动过来即可，这样第一遍扫和移动均要 $m$ 次操作，然后每次移动的最远距离是 $n$，所以最多会等待 $2n$ 的时间，满足要求。

对于后面的子任务，我们考虑将电梯分类，分成**左移点**（即 $a_i< i$）和**右移点**（即 $a_i\geq i$）。

假设我们先不考虑存在只需要向左移动一步的点（下面称为**关键点**），那么我们可以进行如下操作：

1. 在 $0$ 时刻从左往右扫，让左移点直接移动到其目的地，让右移点向左移动一步。可以证明当扫到第 $i$ 个点时其左侧的所有点都在运动。（一共需要花费 $m$ 步）。
2. 让时间流逝 $1$。（花费 $1$ 步）。
3. 从右向左扫，让所有右移点移动到目的地，因为没有**关键点**，所以可以证明不会产生冲突。（最多花费 $m$ 步）。
4. 等待所有点到达目的地。（最多花费 $n$ 步）。

那现在的问题在于如何消除**关键点**了。

首先我们可以发现在哪层没有电梯是不会影响上述操作的，那么我们先让其移动到最左侧，在移动过程中进行处理。

现在每个点都向右移动了一步，那么就是说如果 $a_i=i$ 就说明在最后他是一共**关键点**。我们对序列相邻的两个数进行分组，如果 $m$ 是奇数那么最后一组有三个元素（要特殊讨论）。

如果在一组中存在关键点，那么我们交换这两个点即可。就是说对于一组 $i,i+1,i+2$，其中 $i,i+1$ 是一组，$i+2$ 是空楼层，那么我们进行这样操作 $i+2,i+2,0,i+1$，手动模拟一下发现这个时候两台电梯还在运行中，那为什么不让他们移动到终点呢？因为我们要保证对一组操作时前一组不会影响电梯的选择，就要使前一组在运行中。

这样我们从右向左扫一遍挨个处理即可。

现在讨论一下最后三个元素的情况，因为三个元素的排列顺序只有 $6$ 中，那么我们直接打表这六种情况，因为要消除关键点所以每种情况有 $3$ 个限制，判断并选择适合的情况即可（同时要保证进行下一组之前要都在运行）。

现在我们来分析一下处理所需要花费的步数：

通过打表我们知道三个元素交换最多需要 $7$ 步，然后对于前面最多 $\frac m2$ 组中，最坏情况下需要 $2m$ 次操作，那么这里需要的总操作次数最多是 $2m+2$ 步。之所以 $+2$ 是因为后面三个数要 $+1$，而且最后第一组完成后要等待时间移动 $1$ 来让所有电梯归位。

那么最后的总步数是 $2m+2+m+1+n+m=5n-1$，可以满足条件。

```cpp
#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb emplace_back
#define ll long long
#define mk make_pair
#define reaD read
#define raed read
#define haed head
#define cotu cout
#define se second
#define fi first
#define itn int
//#define mid ((l+r)>>1)
//#define rs now<<1|1
//#define ls now<<1
using namespace std;
bool Mst;
const int Max=2e5+10;
const int mod=998244353;
const int inf=1e9+10;

inline int read(){
	int res=0,v=1;
	char c=getchar();
	while(c<'0'||c>'9'){v=(c=='-'?-1:1);c=getchar();}
	while(c>='0'&&c<='9'){res=(res<<3)+(res<<1)+(c^48);c=getchar();}
	return res*v;
}

int n,m,a[Max],o,b[Max];
int num=0;
void work(int opt=0){
	int now=n;
	if(m&1){//分讨 
		if(a[now-1]!=now-1&&a[now-2]!=now-2&&a[now-3]!=now-3){  
			//1 2 3
			if(!opt)num+=3;
			else cout << now << ' '<< now-1 << ' ' << now-2 << ' ';
			a[now]=a[now-1];a[now-1]=a[now-2];a[now-2]=a[now-3];a[now-3]=0;
		}else if(a[now-3]!=now-3&&a[now-1]!=now-2&&a[now-2]!=now-1){
			//1 3 2
			if(!opt)num+=5;
			else cout << now << ' ' << now << ' ' << "0 " << now-1 << ' ' << now-2 << ' ';
			a[now]=a[now-2];a[now-1]=a[now-1];a[now-2]=a[now-3];a[now-3]=0;
		}else if(a[now-2]!=now-3&&a[now-3]!=now-2&&a[now-1]!=now-1){
			//2 1 3
			if(!opt)num+=5;
			else cout << now << ' ' << now-1 << ' ' << now-1 << ' ' << "0 " << now-2 << ' ';
			a[now]=a[now-1];a[now-1]=a[now-3];a[now-2]=a[now-2];a[now-3]=0;
 		}else if(a[now-2]!=now-3&&a[now-1]!=now-2&&a[now-3]!=now-1){
 			//2 3 1
 			if(!opt)num+=7;
 			else cout << now << ' ' << now-1 << ' ' << now << ' ' << "0 0 " << now-2 << ' ' << now-1<< ' ';
			a[now]=a[now-3];a[now-1]=a[now-1];a[now-2]=a[now-2];a[now-3]=0;
		}else if(a[now-1]!=now-3&&a[now-3]!=now-2&&a[now-2]!=now-1){
			//3 1 2
			if(!opt)num+=6;
			else cout << now << ' ' << now << ' ' << now-1 << " 0 " << now-2 << ' ';
			int z=a[now-1];a[now]=a[now-2];a[now-1]=a[now-3];a[now-2]=z;a[now-3]=0;
		}else {
			//3 2 1
			if(!opt)num+=7;
			else cout << now << ' ' << now << ' ' << now << " 0 " << now-2 << " 0 " << ' ' << now-1 << ' ';
			int z=a[now-1];a[now]=a[now-3];a[now-1]=a[now-2];a[now-2]=z;a[now-3]=0;
		}
		now-=3; 
	}
	for(;now>1;now-=2){
		if(a[now-1]==now-1||a[now-2]==now-2){
			if(opt){//交换 
				cout << now << ' ' << now << " 0 "<< now-1 << ' ';
			}else{
				num+=4;
			}
			a[now]=a[now-2];a[now-2]=0;
		}else{
			if(opt){
				cout << now << ' ' << now-1 << ' ';
			}else num+=2;
			a[now]=a[now-1];a[now-1]=a[now-2];a[now-2]=0;
		}
	}
	if(opt)cout << "0 ";else num++;
	int val=0;
	for(int i=2;i<=n;++i){
		if(a[i]<i){
			val=max(i-a[i]-1,val);
			if(opt)cout << a[i] << ' ';
			else ++num;
		}else{
			if(opt)cout << i-1 << ' ';
			else ++num;
		}
	}
	if(opt)cout << "0 ";else num++;
	for(int i=n;i>=2;--i){
		if(a[i]>=i){
			val=max(val,a[i]-i+1);
			if(opt)cout << a[i] << ' ';
			else ++num;
		}
	}
	num+=val;
	if(opt){
		for(int i=1;i<=val;++i)cout << "0 ";
	}
} 

namespace Sub1{
	
	
	void main(){
		if(a[1]==1){
			cout << "0\n\n";
		}else{
			cout << "7\n3 3 0 1 0 2 0\n";
		}
	}
	
}

namespace Sub2{
	int res=0;
	int ys[Max];
	void main(){
		cout << 2*(n+m) << "\n";
		for(int i=m;i>=1;--i){
			cout << a[i]+m << ' ';
		}
		for(int i=1;i<=n;++i)cout << "0 ";
		for(int i=1;i<=m;++i)cout << i << ' ';
		for(int i=1;i<=n;++i)cout << "0 ";
		cout << '\n';
	}
}


bool Med;
signed main(){
	int T=read();
	while(T--){
		int q=read();n=read();m=read();o=read();
		while(q--){
			for(int i=1;i<=m;++i)b[i]=a[i]=read();
			if(m==2){
				Sub1::main();
				continue;
			}
			if(m==n/2){
				Sub2::main();
				continue;
			}
			num=0;work();
			cout << num << "\n";
			for(int i=1;i<=m;++i)a[i]=b[i];
			work(1);
		}
	}

	cerr<< "Time: "<<clock()/1000.0 << "s\n";
	cerr<< "Memory: " << (&Mst-&Med)/1000000.0 << "MB\n";
	return 0;
}
/*

*/

```

---

