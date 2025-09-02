# Multitest Generator

## 题目描述

Let's call an array $ b_1, b_2, \ldots, b_m $ a test if $ b_1 = m - 1 $ .

Let's call an array $ b_1, b_2, \ldots, b_m $ a multitest if the array $ b_2, b_3, \ldots, b_m $ can be split into $ b_1 $ non-empty subarrays so that each of these subarrays is a test. Note that each element of the array must be included in exactly one subarray, and the subarrays must consist of consecutive elements.

Let's define the function $ f $ from the array $ b_1, b_2, \ldots, b_m $ as the minimum number of operations of the form "Replace any $ b_i $ with any non-negative integer $ x $ ", which needs to be done so that the array $ b_1, b_2, \ldots, b_m $ becomes a multitest.

You are given an array of positive integers $ a_1, a_2, \ldots, a_n $ . For each $ i $ from $ 1 $ to $ n - 1 $ , find $ f([a_i, a_{i+1}, \ldots, a_n]) $ .

Below are some examples of tests and multitests.

- Tests: $ [\underline{1}, 5] $ , $ [\underline{2}, 2, 2] $ , $ [\underline{3}, 4, 1, 1] $ , $ [\underline{5}, 0, 0, 0, 0, 0] $ , $ [\underline{7}, 1, 2, 3, 4, 5, 6, 7] $ , $ [\underline{0}] $ . These arrays are tests since their first element (underlined) is equal to the length of the array minus one.
- Multitests: $ [1, \underline{\underline{1}, 1}] $ , $ [2, \underline{\underline{3}, 0, 0, 1}, \underline{\underline{1}, 12}] $ , $ [3, \underline{\underline{2}, 2, 7}, \underline{\underline{1}, 1}, \underline{\underline{3}, 4, 4, 4}] $ , $ [4, \underline{\underline{0}}, \underline{\underline{3}, 1, 7, 9}, \underline{\underline{4}, 2, 0, 0, 9}, \underline{\underline{1}, 777}] $ . Underlined are the subarrays after the split, and double underlined are the first elements of each subarray.

## 说明/提示

In the first test case of the first test the array $ [1, 2, 1, 7] $ is a multitest since the array $ [2, 1, 7] $ is a test. The array $ [2, 1, 7] $ is not a multitest, but after replacing the first number with $ 1 $ , an array $ [1, 1, 7] $ is obtained, which is a multitest. The array $ [1, 7] $ is also not a multitest, but the array $ [1, 0] $ is, so $ f([1, 7]) = 1 $ .

In the second test case of first test, for $ i = 2 $ , $ f([a_i, a_{i+1}, \ldots, a_n]) = f([1, 3, 1, 2, 1, 1]) = 1 $ , since the array itself is not a multitest, but after replacing the second element with $ 4 $ you get multitest.

In the third test case of first test, for $ i = 1 $ , $ f([a_i, a_{i+1}, \ldots, a_n]) = f([2, 7, 1, 1]) = 1 $ , since the array itself is not a multitest, but after replacing the second element with $ 0 $ you get multitest.

The second test is an array composed of all the numbers of the first test. Therefore $ f([a_1, a_2, \ldots, a_n]) $ naturally equals to $ 0 $ .

## 样例 #1

### 输入

```
3
4
1 2 1 7
7
3 1 3 1 2 1 1
4
2 7 1 1```

### 输出

```
0 1 1 
0 1 1 0 1 1 
1 1 1```

## 样例 #2

### 输入

```
1
19
3 4 1 2 1 7 7 3 1 3 1 2 1 1 4 2 7 1 1```

### 输出

```
0 0 1 1 1 1 1 1 1 0 1 0 1 0 2 1 1 1```

# 题解

## 作者：bmatrix (赞：16)

[题面](https://www.luogu.com.cn/problem/CF1798E)

看到要求每一位的答案，首先考虑倒着扫，因为加数一般都比删数好做。

对于任意长为 $m$ 的的序列 $\{b\}$，我们都可以通过将 $b_1$ 改成 $1$，将 $b_2$ 改成 $m-2$ 使得 $\{b\}$ 成为一个 multitest，因此操作数不会超过 $2$。

现在讨论答案的三种情况：

- 答案为 $0$：$\{b\}$ 已经是一个 multitest 了。
- 答案为 $1$：$\{b\}$ 可以通过一次修改变成一个 multitest。
- 答案为 $2$：排除了前两种之后的情况。

对于一个位置 $i$，它的后缀能构成一个 multitest 的充要条件是：$i+1$ 的后缀能构成若干个 test，且 $a_i$ 的值等于 $i+1$ 的后缀构成的 test 数。

设 $f_i$ 表示 $i$ 的后缀能构成的 test 的个数，不难得出转移方程如下：
$$f_i=\begin{cases}
    1,\qquad i+a_i=n\\
    0,\qquad i+a_i>n\>\operatorname{or}\>f_{i+a_i+1}=0\\
    f_{i+a_i+1}+1,\qquad \text{otherwise}
\end{cases}$$

$\{f\}$ 可以 $\Theta(n)$ 求出。第 $i$ 位答案为 $0$ 的充要条件就是 $f_{i+1}\neq 0$ 且 $a_i=f_{i+1}$。

如果答案不为 $0$，考虑两种情况：

1. $f_{i+1}\neq 0$，但是 $a_i\neq f_{i+1}$。
2. $f_{i+1}=0$。

对于第一种情况，令 $a_i\leftarrow f_{i+1}$ 即可，操作数为 $1$。

对于第二种情况，如果想要答案为 $1$，显然需要对 $i+1$ 的后缀中的某一个数进行修改，使修改后 $i+1$ 的后缀能构成 $a_i$ 个 test。

设 $g_i$ 表示在 $i$ 的后缀中进行一次修改后，能得到的最多 test 数。

这个修改有两种情况：

1. 修改 $a_i$。这意味着我们可以随意改变第一个 test 的长度，也就是这第一个 test 可以接在后面的任意一个状态的前面，这种情况能得到的最大值为 $\max\limits_{j=i+1}^nf_j+1$。
2. 不修改 $a_i$。因为 $a_{i+1}$ 到 $a_{i+a_i}$ 之间的数会被 $a_i$ 所在的 test 所包含，所以只有修改 $i+a_i+1$ 的后缀中的某个数才能有贡献。因此这种情况能得到的最大值为 $g_{i+a_i+1}+1$。

后缀最大值可以边做边求，因此 $\{g\}$ 也可以 $\Theta(n)$ 求出。那么“对 $i+1$ 的后缀中的某一个数进行修改后，$i+1$ 的后缀能构成 $a_i$ 个 test”的充要条件就是 $g_{i+1}\ge a_i$。

之所以这里是大于等于号，是因为如果能修改 $a_p$ 形成 $x$ 个 test，那一定可以通过“让 $a_p$ 更大，覆盖掉下一个 test”或“让上一个 test 的第一个元素更大，覆盖掉 $a_p$ 所在的 test”，形成 $x-1$ 个 test。

剩下的情况答案就是 $2$ 了。

时间复杂度显然 $\Theta(n)$。

[赛时 AC 记录](https://codeforces.com/contest/1798/submission/199300713)。

---

## 作者：banned_gutongxing (赞：3)

## 思路

很简单，先上一个引理。

引理：最后更改次数一定不会超过 2 次。\
证明：分别更改每一个 multitest 的第一个和第二个，改为 0 和总长度 -2，就能使 multitest 合法。

由引理，我们分别来看每一种答案：

1. 需要改 0 次：此时只需要判断一下原来的 multitest 是否合法就行。
2. 需要改 1 次：这个情况很麻烦。待会我们单独考虑
3. 需要改 2 次：当其他的两种情况都不符合时，我们输出 2。

我们来分析一下修改一次的情况。

只可能是两种情况：
+ 改第一个。此时只需要看一下后面自己分段是否成立。
+ 改后面的某一个。此时只要后面修改一次最大的段数多于现在的段数，那么只需要修改一次就能合法。

设计状态：$f_{i}$ 表示已经处理完 $i\sim n$，不修改的可分段数。

相应的，$g_i$ 表示已经处理完 $i\sim n$，修改 1 次的最大可分段数。

状态转移方程式：
$$f_i=f_{i+a_i+1}+1$$
$$g_i=\max\{g_{i+a_i+1}+1,\max_{k\in[i+1,n]}f_k,1\}$$

时间复杂度 $O(n)$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+10;
const int INF = 0x3f3f3f3f;
int T,n,a[MAXN],f[MAXN],g[MAXN],ans[MAXN];
signed main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i = 1;i<=n;i++){
			scanf("%d",a+i);
		}
		for(int i = 1;i<=n+1;i++){
			f[i] = -0x3f3f3f3f;
			g[i] = 1;
		}
		if(a[n]==0) f[n] = 0;
		ans[n] = !(a[n]=(f[n+1]=0));
		g[n+1] = 0;
		int maxn = f[n];
		for(int i = n-1;i>=1;i--){
			if(i+a[i]+1<=n+1) f[i] = f[i+a[i]+1]+1;
			if(i+a[i]+1<=n+1) g[i] = g[i+a[i]+1]+1;
			g[i] = max(g[i],maxn+1);maxn = max(maxn,f[i]);
			if(f[i+1]>0){
				if(f[i+1]==a[i]) ans[i] = 0;
				else ans[i] = 1;
			}else{
				if(g[i+1]>=a[i]) ans[i] = 1;
				else ans[i] = 2;
			}
		}
		for(int i = 1;i<n;i++){
			printf("%d ",ans[i]);
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：3)

# 题意

定义：

- 一个长度为 $n$ 的序列 $a$ 是一个 test 当且仅当 $a_1=n-1$。

- 一个长度为 $n$ 的序列 $a$ 是一个 multitest 的当且仅当能够将 $a_2,a_3,\cdots,a_n$ 划分成 $a_1$ 个连续段，使得每个连续段都是一个 test。

给定长度为 $n$ 的序列 $a$，求对于 $i$ 从 $1$ 到 $n-1$，以 $i$ 开始的后缀至少修改几个值才能够成为 multitest。

# 思路

对于任意一个长度为 $n$ 的字符串 $s$，要使 $s$ 变为 multitest，最多只需要让 $s_1 = 1$，$s_2 = n-2$，即修改 $2$ 次。

所以可能答案只能为 $0,1,2$。

- 对于 $a_{i+1} \sim a_n$ 只能修改 $0$ 次的情况：

   - 定义 $g_j$ 为不修改，将 $a_j \sim a_n$ 划分为若干个连续 test 的数量。无法完成即为 $0$。
   - 显然，当 $g_{j+a_j+1}$ 不为 $0$ 时，$g_j = g_{j+a_j+1} + 1$。
   - 转移：$g_i = \begin{cases}
     g_{j+a_j+1} &\text{if } g_{j+a_j+1} \ne 0 \\
     0 &\text{if }g_{i+1} = 0
     \end{cases}$。
   - 对于 $ans_i$，如果 $g_{i+1} = a_i$，那表示正好可以将 $a_{i+1} \sim a_n$ 划分为 $a_i$ 个 test，答案为 $0$。如果 $g_{i+1} \ne a_i$，答案即为 $1$。
   - 即：
   
$$ans_i = \begin{cases}
   0 &\text{if } g_{i+1} = a_i \\
   1 &\text{if }g_{i+1} \ne a_i
\end{cases}$$

- 对于 $a_{i+1} \sim a_n$ 只能修改 $1$ 次的情况：

   - 对于 $ans_i$，存在两种：第一种是改 $a_i$，第二种是不改 $a_i$。
   - 在 $a_{i+1} \sim a_n$ 我们一定会改一次，但是后面可能有多少个 test 是不确定的，我们就不知道能不能使后面凑出 $a_i$ 个 test。
   - 所以我们 dp 的内容就是究竟以自己开头时能构成多少 test。
   - 我们观察 $g$ 数组的构成方式：
   ![](https://cdn.luogu.com.cn/upload/image_hosting/g5h4pg3l.png)
   
   - 箭头表示从哪里转移。
   - 我们观察 $a_{14}$：
   
   ![](https://cdn.luogu.com.cn/upload/image_hosting/hffvuuas.png)
   - 很明显，此时如果它想要构成连续的 test，又只能修改 $1$ 次，那它就得改自己的值，让它连上一个不需要修改就能形成连续 test 段的数字，即这里的 $a_{15}$，$a_{18}$ 和 $a_{20}$。
   
   ![](https://cdn.luogu.com.cn/upload/image_hosting/08b3egx3.png)
   - 注意到，对于这一个点 $j$ 能产生 test 的数量范围，就是 $1$ 到这一个点后面 $g_k$ 的最大值加一。证明：因为存在一个最大值 $maxn$ 时，就一定会有比最大值正好小一的 $g_k$，因为这个最大值就是从 $g_k$ 转移来的。依次递推，就一定会存在大小为 $1 \sim maxn$ 的 $g_k$。只需要将这个点和 $k$ 点连起来，也就是将 $a_j$ 修改为 $k-j-1$。
   - 所以我们定义：定义 $f_j$ 为修改 $1$ 次，将 $a_j \sim a_n$ 划分为若干个连续 test 的上限。
   - 转移：
     $$f_j = \max (f_{j+a_j+1},maxn_j)$$
   - 其中，
     $$maxn_j = \max (maxn_{j+1},g_j)$$
   - 对于 $ans_i$，如果 $f_{i+1} \ge a_i$，那表示正好可以将 $a_{i+1} \sim a_n$ 划分为 $a_i$ 个 test，答案为 $1$。如果 $f_{i+1} < a_i$，答案即为 $2$。
   - 即：
   
     $$ans_i = \begin{cases}
       1 &\text{if } f_{i+1} \ge a_i \\
      2 &\text{if } f_{i+1} < a_i
     \end{cases}$$

最后只需要输出 $ans_i$ 即可。

注意，转移的时候不要转移到 $n+1$ 之后的位置，但是可以从 $n+1$ 转移。

---

## 作者：RockyYue (赞：2)

### 题意

给定序列 $a_{1...n}$，对于每个后缀 $a_{[i,n]}(1\le i\le n)$，求至少修改其中多少个值使得 $a_{[i+1,n]}$ 可以划分为 $a_i$ 个子段使得每个子段的第一位为子段长度 $-1$。

其中 $1\le n,a_i\le 3\times 10^5$

### 解法

首先若修改 $a_i=1,a_{i+1}=n-1-i$，一定是可行的，故答案不超过 $2$。

对于答案为 $0$ 的情况， 我们设 $f_i$ 为 $a_{[i,n]}$ 可以划分为的子段的个数，若不可以则为 $-inf$，则有 $f_i=f_{i+a_i+1}+1$，若 $f_{i+1}=i$ 则答案为 $0$。

接下来我们只需要考虑答案为 $1$ 的情况，设要修改 $a_p$。

1. $p=i$

   那么 $a_{[i+1,n]}$ 一定是可以划分为若干段的，但是总段数不为 $i$，即 $f_{i+1}\neq -inf$ 且 $f_{i+1}\neq i$；

2. $p\neq i$

   我们设 $g_i$ 为 $a_{i...n}$ 经过一次修改可以划分为的最多的子段个数，那么只要 $g_{i+1}\ge a_i$ 即为可行，因为如果可以变成多于 $a_i$ 段，就可以将 $a_p$ 加上后面一段的长度来达到减少子段个数的效果。考虑求 $g_i$，有 $g_i=\max \{g_{i+a_i+1},\max_{i+1\le j\le n}\{f_j\} \}+1$。预处理 $f$ 后缀 $\max$ 即可。

若均不符合以上情况，则答案为 $2$。

---

## 作者：Loser_Syx (赞：1)

发现对于每个 $i$ 而言，有一种答案一定可行：$a_i=1,a_{i+1}=n-i-1$。故答案最多为 $2$。

答案为 $0$ 也是简单的，若定义 $f_i$ 为当前 $i+1$ 开始划分的 test 个数，则 $f_{i} = f_{i+1+a_{i+1}}+1$。注意下标超过时设为 $-\infty$。

显然 $f_i = a_i$ 时答案为 $0$。

考虑答案是 $1$ 的情况，我们只会进行两种修改，下面分类讨论。

- 修改 $a_i$

  则要求 $f_i$ 不为负无穷，即 $i+1$ 能一路形成 test 直到 $n$ 结束。

- 修改 $i+1 \sim n$ 的一个 multitest 的 test 的数

  发现一定答案构成一定是形如 $[i+1 \sim x] + 1 + [y+1 \sim n]$，其中 $[l,r]$ 表示这一段作为合法的 multitest 由几个 test 组成。

  考虑再定义 $g_i$ 上述答案的最大值，则我们发现 $g_i$ 可以由 $\max_{j=i+1}^n f_j$ 转移而来，即为形如 $1 + [y+1 \sim n]$ 的形式。

  还有种可能就是在 $[i+1 \sim x]$ 这段转移，那么显然可以在之前的 $g_i$ 上接一段，可以这么做当且仅当 $i+1$ 可以有一个 test。

其他情况就是答案为 $2$。至此 $O(n)$ 结束。

[code](https://codeforces.com/contest/1798/submission/288912743)。

---

## 作者：Hisaishi_Kanade (赞：1)

你先从构造的角度考虑，你怎么把一个序列改成 `multitest`。

+ 如果本来就是那就不需要改了。
+ 不难想到不如对于 $[i, n]$，我钦定 $[i+1,n]$ 即为 `test`，这样最多改一下 $a_i, a_{i+1}$ 两个数。
+ 由于上面第二条的结论，所以最后一种情况是只需要一步。如何构造？若 $[i+1,n]$ 已经形成了 $m$ 个 `test`，则直接改 $a_i$，否则如何做？

设 $p_i$ 表示 $[i, n]$ 形成的 `test` 数量。不能形成则为 $-\infty$。

如果 $p_{i+1}=-\infty$，为了一次操作完成，则考虑修改一下某个 $a_j(i<j\le n)$，使得其成为 `test`。

设 $q_i$ 表示能够一次将 $[i,n]$ 变成的 `test` 数量最大是多少。

+ 如果我们考虑修改 $a_i$ 的值，则 $q_i\gets \max\{p_{j}+1\}$；

+ 如果修改某个 $a_j$，则因为只有一次操作，$a_i$ 必须是 `test` 的某个开头，所以 $q_i\gets q_{i+a_i+1}+1$。

对于 $q_i$，考虑到你只是修改了某个 $a_j$，使得 $[j,j+a_j^\prime+1]$ 变成 `test`，如果将 $a_j^\prime$ 扩大囊括了下一个 `test`，则可以也是一次操作做到 $q_i-1$，同理，如果不修改 $a_j$，而是修改前一个 `test` 的左端点……不难得出，$q_i$ 其实也代表了 $[1,q_i]$ 的 `test` 数都能做出来。

好接下来分讨一下。

+ 如果 $q_{i+1}=a_i$，答案为 $0$；
+ 如果 $q_{i+1}\ge a_i$，则可以通过修改某个 $a_j$ 完成，答案为 $1$；
+ 如果 $p_{i+1}\not =-\infty$，则可以通过修改 $a_i$ 完成，答案为 $1$；
+ 否则直接修改 $a_i$ 和 $a_{i+1}$，答案为 $2$。

```cpp 
#include <bits/stdc++.h>
#define rep(i, l, r) for(i=l; i<=r; ++i)
#define req(i, r, l) for(i=r; i>=l; --i)
using namespace std;
int t, i, n; const int N=3e5+5, inf=-1e9; int a[N], f[N], g[N], suf[N];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n); rep(i, 1, n) scanf("%d", a+i); rep(i, 1, n) suf[i]=f[i]=g[i]=inf;
		f[n+1]=g[n+1]=suf[n+1]=0; req(i, n, 2)
		{
			if(i+a[i]<=n) {if(f[i+a[i]+1]!=inf) f[i]=f[i+a[i]+1]+1; g[i]=g[i+a[i]+1]+1;}
			g[i]=max(g[i], suf[i+1]+1); suf[i]=max(suf[i+1], f[i]);
//			printf("%d %d %d\n", f[i], g[i], suf[i]);
		}
		rep(i, 1, n-1)
		{
			if(f[i+1]==a[i]) printf("0 ");
			else if(f[i+1]!=inf || g[i+1]>=a[i]) printf("1 ");
			else printf("2 ");
		} puts("");
	}
}
```

---

## 作者：florrygg (赞：0)

# CF1798E Multitest Generator 题解

[题面](https://www.luogu.com.cn/problem/CF1798E)

## 思路

这是一道**诈骗**题，如果你有脑子的话你就会发现（我看了好久）其实一个长度为 $n$ 的连续段最多改成 $1,n-2,\large\cdots$ 就是一个 multitest 了，所以一个连续段最多该两次。

对于判断 0 次我们可以直接倒着 dp 。

$$
\large
dp_i=
\begin{cases}
dp_{i+a_i+1} &  i+a_i+1\le n\\
10^9 & i+a_i+1>n
\end{cases}
$$

再维护一个 dp2。

$$
\large
dp2_i=\max((\max^{j=i+1}_{n} dp2_j)+1,dp2_{i+1})
$$

对于判断 1 次可以分两种情况讨论：

1. $dp_{i+1}<10^9$ 只需要让 $a_i=dp_{i+1}$ 即可。
2. $dp_{i+1}\ge 10^9$ 只要 $dp2_{i+1}\ge a_i$ 即可。

## code

```cp
#include <bits/stdc++.h>
using namespace std;
#define il inline
#define re register
#define endl '\n'

const int maxn=3e5+1;
int t,n,a[maxn],dp[maxn],dp2[maxn];
int ans[maxn],maxx[maxn];

signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		for(int i=n;i>=1;i--)
		{
			if(i+a[i]+1>n+1)
			{
				dp[i]=1e9;
			}
			else
			{
				dp[i]=dp[i+a[i]+1]+1;
			}
			if(dp[i]<1e9)
			{
				maxx[i]=max(maxx[i+1],dp[i]);
			}
			else
			{
				maxx[i]=maxx[i+1];
			}
			dp2[i]=max(maxx[i],dp2[i+a[i]+1])+1;
		}
		for(int i=n-1;i>=1;i--)
		{
			if(dp[i+1]==a[i])
			{
				ans[i]=0;
			}
			else if(dp[i+1]<1e9)
			{
				ans[i]=1;
			}
			else if(dp2[i+1]>=a[i])
			{
				ans[i]=1;
			}
			else
			{
				ans[i]=2;
			}
		}
		for(int i=1;i<n;i++)
		{
			cout<<ans[i]<<' ';
		}
		cout<<endl;
		for(int i=1;i<=n;i++)
		{
			dp[i]=0;
			maxx[i]=0;
			dp2[i]=0;
		}
	}
	return 0;
}
```

---

## 作者：紊莫 (赞：0)

没有想出来，记录一下。



------------


没想出来的原因：没有注意到题目的答案至多为 $2$，也就是把 $a_i,a_{i+1}$ 改掉，一定能满足题意，于是可以分类讨论。

首先，答案为 $0$ 的情况。显然是对于一个点 $i$，后面正好有 $a_i-1$ 个 ``test``。那么我们可以动态规划求出每个点后面的 ``test`` 个数。

定义 $f_i$ 为到 $i$ 为止的 ``test`` 个数。$f_i \leftarrow f_{i+a_i+1}+1$，当然，对于直接和末尾连起来的需要特判。

然后，考虑答案为 $1$。两种情况，一种是把 $a_i$ 改成 $f_{i+1}$，或者在 $a_{i},a_{i+1},\dots,a_{n}$ 中改一个数，将其改成大于等于 $a_i$ 即可。

第一种简单，考虑动态规划求解第二种。定义 $g_i$ 为后 $i$ 个数字中至多改一次能得到的最多的 ``test`` 数量。

为了求解这个，我们还需要对 $f$ 做一个后缀最大值，记为 $h$。$g_i \leftarrow \max \left \{ g_{i+a_i+1},h_{i+1} \right \}+1$，对应的决策是不修改 $a_i$，或修改。

剩余情况均为 $2$。

---

## 作者：User_Unauthorized (赞：0)

## 题意
定义一个序列 $b_1, b_2, b_3, \cdots, b_m$ 为 $\texttt{test}$ 当且仅当 $b_1 = m - 1$。

定义一个序列 $b_1, b_2, b_3, \cdots, b_m$ 为 $\texttt{multitest}$ 当且仅当该序列可以划分为 $b_1$ 段子串，且每段子串均为一个 $\texttt{test}$。

现给定一个长度为 $n$ 的正整数序列 $a_1, a_2, a_3, \cdots, a_n$，对于所有的 $i \in \left[1, n\right)$，求出使原序列的后缀 $a_i, a_{i + 1}, \cdots, a_n$ 为 $\texttt{multitest}$ 的最小修改次数（每次修改可以更改一个元素，不可以删减元素）。

（$1 \le n \le 3 \times 10^5$）。

## 题解

首先考虑一个性质

> 对于任意序列，均可以通过 $2$ 次更改使其成为 $\texttt{multitest}$。

假设我们有任意序列 $b_1, b_2, b_3, \cdots, b_m$，执行操作 $b_1 \leftarrow 1, b_2 \leftarrow m - 2$ 即可使其成为 $\texttt{multitest}$。

那么我们只需要考虑当前序列能否通过小于 $2$ 次操作使其变为 $\texttt{multitest}$。

首先考虑 $0$ 次操作，即当前序列原始就是一个 $\texttt{multitest}$。

记 $f_i$ 表示 $i$ 的后缀能构成的连续合法 $\texttt{test}$ 的个数，可以得出转移方程如下：

$$f_i = \begin{cases}
1 & i + a_i + 1 = n + 1 \\
0 & i + a_i + 1 > n + 1 \lor f_{i + a_i + 1} = 0\\
f_{i + a_i + 1} + 1 & \text{otherwise}
\end{cases}$$

可以发现 $f$ 的值可以 $\mathcal{O}(n)$ 求出。第 $i$ 位的答案为 $0$ 的充要条件为 $f_{i + 1} = a_i$。

接下来考虑 $1$ 次操作，如果 $i + 1$ 的后缀可以形成合法的若干 $\texttt{test}$ 即 $f_{i + 1} > 0$，那么直接执行更改 $a_i \leftarrow f_{i + 1}$ 即可。

如果 $i + 1$ 的后缀无法形成合法的 $\texttt{test}$，那么考虑在该后缀中进行更改。可以发现一个性质

> 如果一个序列可以通过 $1$ 次更改形成 $k$ 个合法 $\texttt{test}$，那么其一定可以通过 $1$ 次更改形成 $k^{\prime} \le k$ 个 $\texttt{test}$。

考虑改变原始更改方案。设在该方案中改变了 $a_t$ 的值，在此之后的若干 $\texttt{test}$ 的首位元素下标为 $c_1, c_2, \cdots$，其中 $a_t = c_0$，那么我们只需要执行 $a_t \leftarrow c_{k - k^{\prime}} - 1$ 即可。若在此之后的 $\texttt{test}$ 数量小于 $k - k^{\prime}$，那么我们更改从后往前数第 $k - k^{\prime} + 1$ 个 $\texttt{test}$ 的首位元素即可。

所以我们只需要求出在 $i$ 的后缀中通过 $1$ 次更改可以形成的最多合法 $\texttt{test}$ 数量 $g_i$ 即可判定。若 $a_i \le g_{i + 1}$，那么结合上文性质可得第 $i$ 位的答案为 $1$。

下面考虑如何求出 $g_i$ 的值，考虑两种转移

- 改变 $a_i$ 的值，那么因为可以任意更改当前 $\texttt{test}$ 的长度即下一个 $\texttt{test}$ 的首位元素且之后不能再次执行更改，所以在所有的可能首位元素中取 $f$ 最大值即可，此时 $\displaystyle g_i = \max\limits_{j = i + 1}^{n + 1} f_{j} + 1$；
- 不改变 $a_i$ 的值，那么下一个 $\texttt{test}$ 的首位元素为 $i + a_i + 1$，且之后可以进行更改，故从 $g_{i + a_i + 1}$ 转移即可，即 $g_i = g_{i + a_i + 1}$。

两种情况取最大值即可推出 $g_i$ 的值，利用后缀最大值优化即可以 $\mathcal{O}(n)$ 的复杂度处理 $f, g$ 两个数组的值。

## Code

```cpp
//Codeforces - 1798E
#include <bits/stdc++.h>

typedef int valueType;
typedef std::vector<valueType> ValueVector;

constexpr valueType MIN = INT_MIN >> 2;

int main() {
    valueType T;

    std::cin >> T;

    for (valueType testcase = 0; testcase < T; ++testcase) {
        valueType N;

        std::cin >> N;

        ValueVector source(N + 2), next(N + 2, N + 2), F(N + 2, MIN), G(N + 2, MIN), maxF(N + 2, MIN);

        for (valueType i = 1; i <= N; ++i) {
            std::cin >> source[i];
            next[i] = i + source[i] + 1;
        }

        maxF[N + 1] = F[N + 1] = G[N + 1] = 0;

        for (valueType i = N; i > 1; --i) {
            if (next[i] <= N + 1)
                F[i] = F[next[i]] + 1;

            G[i] = maxF[i + 1] + 1;

            if (next[i] <= N + 1)
                G[i] = std::max({G[i], G[next[i]] + 1});

            maxF[i] = std::max(maxF[i + 1], F[i]);
        }

        for (valueType i = 1; i < N; ++i) {
            if (source[i] == F[i + 1]) {
                std::cout << 0 << ' ';
            } else if (F[i + 1] > 0 || G[i + 1] >= source[i]) {
                std::cout << 1 << ' ';
            } else {
                std::cout << 2 << ' ';
            }
        }

        std::cout << '\n';
    }

    std::cout << std::flush;

    return 0;
}
```

---

## 作者：masonpop (赞：0)

简单 dp。

显然将一个序列划分成若干个 test 的方案是唯一的。

首先不难发现，将一个长度为 $n$ 的序列 $a_1,a_2,\cdots,a_n$ 改为 multitest 最多需要两次操作，因为可以直接令 $a_1=1$，$a_2=n-2$ 即可满足要求。接下来只需要考虑小于两次操作是否能满足要求。

首先考虑不修改，即本身是 multiset。这是个很裸的 dp，设 $f_i$ 表示能将位置 $i$ 的后缀划分成多少个 test。转移是显然的，直接试图用 $f_{i+a_i+1}+1$ 更新答案，分讨一下 $i+a_i+1$ 的范围即可。最后检查 $f_{i+1}$ 是否等于 $a_i$。

再考虑修改一次的情况。容易发现，对于位置 $i$ 的后缀，如果 $f_{i+1}\ne 0$，那么直接将 $a_i$ 修改成 $f_{i+1}$ 就行。

否则，就只能考虑对 $i+1$ 的后缀进行修改。注意到关键性质：**如果一段序列能通过一次修改形成 $t$ 个 test，则也能通过一次修改形成 $r$ 个 test，其中 $r\le t$**。可以感性理解一下，显然有效的修改是修改某一个位置使其成为段首，那么，我们也可以通过改变修改的位置“合并”相邻两段。

那么，只需记录最大段数即可。设 $g_i$ 表示位置 $i$ 的后缀通过一次修改所能达到的最大段数。分类讨论是否修改 $a_i$。若不修改，则这一段的长度仍然是 $a_i+1$，贡献即为 $g_{i+a_i+1}+1$。否则，就意味着这一段的长度可以任意伸缩，贡献为 $\max\limits_{j=i+1}^nf_j$。维护 $f$ 数组的后缀最大值即可做到 $O(n)$。[代码](https://codeforces.com/contest/1798/submission/219900284)。

---

