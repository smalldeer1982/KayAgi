# Ball Sorting

## 题目描述

There are $ n $ colorful balls arranged in a row. The balls are painted in $ n $ distinct colors, denoted by numbers from $ 1 $ to $ n $ . The $ i $ -th ball from the left is painted in color $ c_i $ . You want to reorder the balls so that the $ i $ -th ball from the left has color $ i $ . Additionally, you have $ k \ge 1 $ balls of color $ 0 $ that you can use in the reordering process.

Due to the strange properties of the balls, they can be reordered only by performing the following operations:

1. Place a ball of color $ 0 $ anywhere in the sequence (between any two consecutive balls, before the leftmost ball or after the rightmost ball) while keeping the relative order of other balls. You can perform this operation no more than $ k $ times, because you have only $ k $ balls of color $ 0 $ .
2. Choose any ball of non-zero color such that at least one of the balls adjacent to him has color $ 0 $ , and move that ball (of non-zero color) anywhere in the sequence (between any two consecutive balls, before the leftmost ball or after the rightmost ball) while keeping the relative order of other balls. You can perform this operation as many times as you want, but for each operation you should pay $ 1 $ coin.

You can perform these operations in any order. After the last operation, all balls of color $ 0 $ magically disappear, leaving a sequence of $ n $ balls of non-zero colors.

What is the minimum amount of coins you should spend on the operations of the second type, so that the $ i $ -th ball from the left has color $ i $ for all $ i $ from $ 1 $ to $ n $ after the disappearance of all balls of color zero? It can be shown that under the constraints of the problem, it is always possible to reorder the balls in the required way.

Solve the problem for all $ k $ from $ 1 $ to $ n $ .

## 说明/提示

In the first test case there are $ n = 6 $ balls. The colors of the balls from left to right are $ [\, 2, 3, 1, 4, 6, 5 \,] $ .

Let's suppose $ k = 1 $ . One of the ways to reorder the balls in the required way for $ 3 $ coins:

 $ [\, 2, 3, 1, 4, 6, 5 \,] $ $ \xrightarrow{\, 1 \,} $ $ [\, 2, 3, 1, 4, \color{red}{0}, 6, 5 \,] $ $ \xrightarrow{\, 2 \,} $ $ [\, 2, 3, \color{blue}{4}, 1, 0, 6, 5 \,] $ $ \xrightarrow{\, 2 \,} $ $ [\, \color{blue}{1}, 2, 3, 4, 0, 6, 5 \,] $ $ \xrightarrow{\, 2\,} $ $ [\, 1, 2, 3, 4, 0, 5, \color{blue}{6} \,] $

The number above the arrow is the operation type. Balls inserted on the operations of the first type are highlighted red; balls moved on the operations of second type are highlighted blue.

It can be shown that for $ k = 1 $ it is impossible to rearrange balls in correct order for less than $ 3 $ coins.

Let's suppose $ k = 2 $ . One of the ways to reorder the balls in the required way for $ 2 $ coins:

 $ [\, 2, 3, 1, 4, 6, 5 \,] $ $ \xrightarrow{\, 1 \,} $ $ [\, 2, 3, 1, 4, 6, \color{red}{0}, 5\,] $ $ \xrightarrow{\, 2 \,} $ $ [\, 2, 3, 1, 4, 0, 5, \color{blue}{6}\,] $ $ \xrightarrow{\, 1 \,} $ $ [\, 2, 3, \color{red}{0}, 1, 4, 0, 5, 6 \,] $ $ \xrightarrow{\, 2 \,} $ $ [\, \color{blue}{1}, 2, 3, 0, 4, 0, 5, 6\,] $

Note that this sequence of operations is also correct for $ k $ greater than $ 2 $ .

It can be shown that for $ k $ from $ 2 $ to $ 6 $ it is impossible to rearrange balls in correct order for less than $ 2 $ coins.

In the second test case the balls are already placed in the correct order, so answers for all $ k $ are equal to $ 0 $ .

## 样例 #1

### 输入

```
3
6
2 3 1 4 6 5
3
1 2 3
11
7 3 4 6 8 9 10 2 5 11 1```

### 输出

```
3 2 2 2 2 2 
0 0 0 
10 5 4 4 4 4 4 4 4 4 4```

# 题解

## 作者：ningago (赞：13)

考虑这样一种策略：保留一个原序列的上升子序列。称子序列中的点为选定点。

那么所有非选定点都要借助 $0$ 被移动到相应的位置上。

容易发现这种策略 $0$ 的最小个数为：极长非选定点连续段的个数。

不难发现这样可以涵盖所有可能的最优策略。

所有记 $dp_{i,k}$ 表示 $i$ 是一个选定点，$[1,i]$ 内有（至多） $k$ 个极长非选定点连续段，最小的代价。

枚举上一个选定点即可 $O(n)$ 转移。

$k$ 的答案即为 $dp_{n,k}$ 或 $dp_{i,k-1}+n-i$。

复杂度 $O(n^3)$。

https://codeforces.com/contest/1839/submission/208388024

---

## 作者：Hisaishi_Kanade (赞：10)

我们可以发现，由于这些 $0$ 最终会消失，那么我们每次移动就可以将 $c_i$ 移动到它最终应该在的位置而不需要移动它第二次。

那么换句话说，原问题等价于最少需要移动多少个 $c_i>0$ 的球。我们反过来，最多能有多少个球原地不动。

不考虑其他球，这些球的编号必然是单调上升的，否则因为他们本身无序而又不会变化相对位置，结果必然是无序的。

由此我们设计一个 dp，$f_{i}$ 表示前 $i$ 个求处理完所能保留的最大球数，我们会发现，我们必然要找到某个 $j<i$，使得 $a_j<a_i$，从它转移 $f_i\gets \min\{f_j+1\}$。

对着他观察，不难发现，对于 $(j,i)$ 这个区间内的 $a$，他们可以使用同一个 $0$ 号球清除，例如我们可以钦定一个球打到 $i$ 与 $i-1$ 之间，然后依次把球打出去，实际上随意位置都可以。

原题需要 $n$ 次求解，那么我们增加一维 $f_{i,j}$ 表示用了 $i$ 个 $0$ 号球，处理前 $j$ 个的最大保留。

特殊的，当 $a_{i-1}<a_i$ 时，可以有转移 $f_{i,j}=f_{i,j-1}+1$，因为显然地，我们没必要在这里浪费一个 $0$ 号球。

那么转移 $f_{i,j}\gets \min\{f_{i-1,k}+1\}\mid a_k<a_i$。

这个东西是 $tn^3$ 的，我们发现其实相当于维护单点修改区间最大值，这个用线段树维护是简单的。我们每次在求解 $f_{i,j}$ 时将 $f_{i-1,j-1}$ 加入线段树。

然而线段树的常数太大不足以体现我们 $n^2\log n$ 的优越性，由于只需要前缀，那么我们直接树状数组，这样我们以 15ms 达到了最优解。

对于每次的询问，答案是 $\min(n-f_{i,n},\min\{j-f_{i-1,j}+n-j\})$，是指 $[1,j]$ 有一些保留，价值最少为 $j-f_{i,j}$，而 $(j,n]$ 的，则用一个球莽掉；或者是保留下 $n$ 即 $f_{i,n}$。

代码其实也挺简洁的？

```cpp
// LUOGU_RID: 120169400
#include <bits/stdc++.h>
#define rep(i, l, r) for(i=l;i<=r;++i)
using namespace std;
int t, n, j, i;
const int N=505;
int a[N], f[N][N], tr[N];
void upd(int x, int k)
{
	while(x<=n)
	{
		tr[x]=max(tr[x], k);
		x+=x&-x;
	}
}
inline int query(int x)
{
	static int ret; ret=0;
	while(x)
	{
		ret=max(ret, tr[x]);
		x-=x&-x;
	}
	return ret;
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		rep(i, 1, n) scanf("%d",a+i);
		rep(i, 0, n) rep(j, 0, n) f[i][j]=0;
		rep(j, 1, n) if(a[j]>a[j-1]) f[0][j]=f[0][j-1]+1; else break;
		rep(i, 1, n)
		{
			rep(j, 1, n)
			{
				if(j!=1) upd(a[j-1],f[i-1][j-1]);
				if(a[j]>a[j-1]) f[i][j]=f[i][j-1]+1;
				f[i][j]=max(f[i][j], query(a[j])+1);
			}
			int ret=n-f[i][n];
			rep(j, 1, n) ret=min(ret, j-f[i-1][j]+n-j);
			memset(tr, 0, sizeof tr);
			printf("%d ",ret);
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：elbissoPtImaerD (赞：1)

第一个的 observation 是放入 $0$ 球后，存在最优策略使得每个非零球至多被移动一次。

证明是：对于一个非零球，除非其不动，否则我们一定会将其一次移动到最终位置上。

那么让花费最少相当于让位置不变的非零球尽可能多。

考虑这些非零球应该具备何种性质。

由于他们相对位置不变，那么他们必然是单调上升的。

而 $0$ 球的放入策略自然是考虑在每个需要移动的非零球的极长段中放入恰好一个 $0$ 球。

自然考虑 dp：设 $f_{i,j}$ 表示考虑了最后一个位置不变的非零球是 $i$，要放入 $j$ 个 $0$ 球时的最少移动次数。

自然有转移：$f_{i,j} \min\limits_{i>k,a_i>a_k} \{f_{k,j-1} + i-k-1\}$。

复杂度 $\mathcal{O(\sum n^3)}$。

值得一提的细节是第 $1/n$ 个球未必位置不变。

[$\color{green}{\checkmark}$](https://codeforces.com/contest/1839/submission/232965630)。

---

