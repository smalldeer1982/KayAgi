# Missing Subarray Sum

## 题目描述

There is a hidden array $ a $ of $ n $ positive integers. You know that $ a $ is a palindrome, or in other words, for all $ 1 \le i \le n $ , $ a_i = a_{n + 1 - i} $ . You are given the sums of all but one of its distinct subarrays, in arbitrary order. The subarray whose sum is not given can be any of the $ \frac{n(n+1)}{2} $ distinct subarrays of $ a $ .

Recover any possible palindrome $ a $ . The input is chosen such that there is always at least one array $ a $ that satisfies the conditions.

An array $ b $ is a subarray of $ a $ if $ b $ can be obtained from $ a $ by the deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end.

## 说明/提示

For the first example case, the subarrays of $ a = [1, 2, 1] $ are:

- $ [1] $ with sum $ 1 $ ,
- $ [2] $ with sum $ 2 $ ,
- $ [1] $ with sum $ 1 $ ,
- $ [1, 2] $ with sum $ 3 $ ,
- $ [2, 1] $ with sum $ 3 $ ,
- $ [1, 2, 1] $ with sum $ 4 $ .

 So the full list of subarray sums is $ 1, 1, 2, 3, 3, 4 $ , and the sum that is missing from the input list is $ 3 $ .For the second example case, the missing subarray sum is $ 4 $ , for the subarray $ [2, 2] $ .

For the third example case, the missing subarray sum is $ 13 $ , because there are two subarrays with sum $ 13 $ ( $ [3, 5, 5] $ and $ [5, 5, 3] $ ) but $ 13 $ only occurs once in the input.

## 样例 #1

### 输入

```
7
3
1 2 3 4 1
4
18 2 11 9 7 11 7 2 9
4
5 10 5 16 3 3 13 8 8
4
8 10 4 6 4 20 14 14 6
5
1 2 3 4 5 4 3 2 1 1 2 3 2 1
5
1 1 2 2 2 3 3 3 3 4 5 5 6 8
3
500000000 1000000000 500000000 500000000 1000000000```

### 输出

```
1 2 1 
7 2 2 7 
3 5 5 3 
6 4 4 6 
1 1 1 1 1 
2 1 2 1 2 
500000000 500000000 500000000```

# 题解

## 作者：Exp10re (赞：7)

神题啊。

## 解题思路

考虑当得到所有 $\frac {n(n+1)} {2}$ 个子段和时如何还原原序列。

记 $S$ 表示所有子段和的值形成的集合。

我们有两种方案：

### Case 1

由于原序列是一个回文串，故某个子段和的值在所有子段和中出现奇数次当且仅当其为某个**中间段**（即，若该段为 $[L,R]$，则有 $n-R+1=L,n-L+1=R$）。

将所有中间段排序后差分可以得到 $a_{2,\cdots,n-1}$，接下来用**次大值**减去 $a_{2,\cdots,n-1}$ 的和可以得到 $a_1$ 以及 $a_n$。

该种方法的好处是：**你不需要得知 $a$ 中所有数的和的确切数值**，仅靠其他数就可以还原序列。

但一个必须条件是：**你必须得知除 $a$ 中所有数的和之外的所有子段和**。

### Case 2

显然，最大值为 $a$ 中所有数的和，记为 $maxn_1$，次大值为 $a$ 中所有数的和减去 $a_1$，记为 $maxn_2$，根据这两个可以推理出 $a_1$ 和 $a_n$。

得知这两个值之后我们可以得知 $a_{2,\cdots,n-1}$ 的和。删去 $S$ 中的 $maxn_1,maxn_2$ 以及 $a_{2,\cdots,n-1}$ 的和之后，剩余所有值都必定是 $a_{1,\cdots,n-2}$ 或 $a_{3,\cdots,n}$ 的某个子段的和，故此时 $S$ 中最大值即为 $a_{1,\cdots,n-2}$，由此我们可以推理出 $a_2,a_{n-1}$。

得知这些值之后我们可以发现：排除所有已知子段的和后，所有非最长前缀（或后缀）的子段一定是最长前缀（或后缀）的某一个子段。

故每得到一个新的 $a$ 中的值，我们删掉 $S$ 中当前已知的子段的和后，$S$ 中的最大值即为最长前缀（后缀）的值，这之后又可以得到一个新的 $a$ 中的值。如此往复直到得到 $a$ 中所有值。

该种方法的好处是：**你不需要得知除了所有前缀（后缀）的和之外所有数的确切数值**，仅靠所有前缀（后缀）的和就可以还原序列。

但一个必须条件是：**你必须得知 $a$ 中所有数的和**。

---

接下来考虑删除一个值会对这两种方案产生什么影响：

- 删掉了 $a$ 中所有数的和。  
  Case 2 不能用了，但是可以使用 Case 1 的做法。
- 删掉了其他随便什么数。
  Case 1 不能用了，但是可以使用 Case 2 的做法，原因是每一个前缀（后缀）的和都会出现至少两遍，删掉一个根本没有影响。

两种方法的时间复杂度都是 $O(n^2 \log n)$ 规模的，可以通过。

---

## 作者：sunkuangzheng (赞：7)

$\textbf{CF1965D *2900}$

> - 有一个数组 $a$，保证它是回文的。你将得到其 $\dfrac{n(n+1)}{2}-1$ 个不同子区间的和 $s_i$（即有一个你不知道），请还原数组 $a$。
> - $1 \le n \le 10^3,1 \le s_i \le 10^9$。

考虑如果我们知道其所有 $\dfrac{n(n+1)}{2}$ 个子区间的和怎么做。

- 做法一。

考虑子区间和中出现奇数次的数字，它们对应的区间一定是跨过序列中点，且两边长度相等的。那么我们将它们从小到大排序，设序列中点为 $i,j (i \le j)$，则我们可以得到区间 $[i,j],[i-1,j+1],[i-2,j+2],\ldots,[1,n]$ 的和，差分后可以还原数组 $a$。

- 做法二。

考虑子区间和中的最大值和次大值，它们一定分别对应区间 $[1,n],[1,n-1]$，那么我们可以得到 $a_1,a_n$，进而得到 $[2,n-1]$ 的和。将上述区间和从集合里删去后，最大值一定是 $[1,n-2]$，那么我们可以推出 $a_2,a_{n-1}$，进而得到 $[3,n-2]$ 的和。注意到所有区间和可能大于 $[1,n-3]$ 的区间和我们都知道，那把它们全都删掉后最大值即为 $[1,n-3]$，依次推下去就可以还原数组 $a$。

那么现在考虑有一个元素缺失该怎么做。

- 给定集合中最大值出现 $2$ 次。

这种情况缺失的子区间和是 $[1,n]$，我们采用做法一，可以得到 $a_2,a_3,\ldots,a_{n-1}$ 的值。由于此时最大值是 $[1,n-1]$，我们也容易得到 $a_1,a_n$。

- 给定集合中最大值出现 $1$ 次。

这种情况直接采用做法二即可，只要 $[1,n]$ 的区间和不缺失就不会影响做法二。

总复杂度 $\mathcal O(n^2 \log n)$，可以通过。[赛时 AC 代码](https://codeforces.com/contest/1966/submission/258458683)。

---

## 作者：Nova_NightWind0311 (赞：2)

### 前言

和 MO 同学一起讨论得到的做法，发现想法撞了官方题解，于是对着官方题解进行了一些改进。

现在相当于官方题解的翻译，同时有一些做法上的思考。

### 题解

精妙构造。

考虑如果所有的和都给出来的应该怎么还原序列。会发现，只有处于回文位置的和 $[l,n-l+1]$ 会在所有部分和中出现奇数次。我们把出现这些和拿出来排序，差分一下就可以还原。

现在少了一个和，自然考虑找到这个缺失的和。仍然考察出现了奇数次的和，原本应该有 $\left\lceil\dfrac{n}{2}\right\rceil$ 个，现在应该有 $\left\lceil\dfrac{n}{2}\right\rceil \pm 1$ 个。

**Case 1**：现在有 $\left\lceil\dfrac{n}{2}\right\rceil - 1$ 个和出现奇数次，那么缺失的应该是一个回文位置的和 $[l,r]$。如果我们把这些和看成一个序列的所有回文和，那么可以构造出一个长度为 $n-2$ 的序列 $b$。

序列 $b$ 和原序列 $a$ 的差别在于，$b$ 中的某一项是 $a$ 中两项的和，因为我们差分构造 $b$ 的过程中跳过了那个缺失的回文和 $[l,r]$。我们算出 $b$ 的所有部分和 $S_b$，与给出的 $a$ 的部分和 $S_a$ 进行比对，那么 $S_b$ 缺失的和应该是所有某个端点为 $l$ 或 $r$ 的部分和。这些和中最大的是 $[1,r]$，同时也是 $[l,n-l+1]$。

我们找到这个最大值，设为 $x$，另外记 $b$ 总和为 $y$。那么我们让 $[1,r]$ 和 $[l,n-l+1]$ 拼起来，再减去每个数各一次，就得到了缺失的区间和 $[l,r]$。所以，缺失的和就是 $2x-y$。

**Case 2**：现在有 $\left\lceil\dfrac{n}{2}\right\rceil + 1$ 个和出现奇数次，那么缺失的应该是一个非回文位置的和 $[l,r]$。为了简洁，在这里先忽略一些 Corner Case。我们仍然把这些和看作一个序列的所有回文和，那么可以构造出一个长度为 $n+2$ 的序列 $b$。

序列 $b$ 和原序列 $a$ 的差别在于，$b$ 中的两项之和是 $a$ 中的一项。因为我们差分构造 $b$ 的过程中把一个不是回文和的 $[l,r]$ 认为成了回文和，从而需要合并两个 $b_i$ 才能得到真正的 $a$。延续刚才的思路，算出 $b$ 的所有部分和 $S_b$ 与给出的 $S_a$ 进行 diff，那么 $a$ 中压根不存在的和应该是在 $b$ 中包含多出来的这一项的和。这些和中最大的是 $[1,r]$，同时也是 $[l,n-l+1]$。用同样的手法可以得到，缺失的和也是 $2x-y$。

这里因为多出来的和是不确定的，为了能够保证构造出 $b$，需要特判一些情况：

- 观察到所有回文和应该是同奇偶的，所以如果这 $\left\lceil\dfrac{n}{2}\right\rceil + 1$ 个和存在不同奇偶性的数，那么与其他数奇偶性不同的那个和就是要找的缺失的和。

得到了这个和，我们更新一下出现奇数次的和，提出来再差分回去就可以还原 $a$ 了。

时间复杂度 $\mathcal{O}(n^2 \log n)$。

这个题的核心想法在于，我们想要找出缺失的和是什么。考虑到，无论少还是多这一个，对整个序列的影响其实不是很大。我们要想办法在缺失一项的情况下找到和原序列的差别，这就自然引出了构造出 $b$ 之后对两个部分和进行 diff 的操作。比对之后得到的东西又具有很好的性质，自然就可以往后进行了。

再次感叹于 MO 同学的强大。

---

## 作者：Felix72 (赞：0)

将给定的集合描述为 $\{(num_i, cnt_i)\}$ 的形式，表示一个数和其出现次数。如果 $\sum_{i} [cnt_i \bmod 2 = 1] = \lfloor \frac{n}{2} \rfloor$，那么我们知道所有以原串中心为中心的子串和，可以直接算出答案。

如果不是的话，那么一定有些关于此类子串的信息被隐去。如果最大值仅有一个，说明原串的和未被隐去，则可知 $s_{1, n}$。而 $s_{1, n - 1}$ 和 $s_{2, n}$ 相等且至少留下了一个，则可以找出 $s_{1, n}$ 之外的最大值作为 $s_{1, n - 1}$ 和 $s_{2, n}$。此时序列两端的数已经知道。再删去 $s_{1, n - 1}, s_{2, n - 1}, s_{2, n}$，此时的最大值一定是 $f_{1, n - 2} = f_{3, n}$……如法炮制找出每个 $s_{1, i} = s_{n - i + 1, n}$ 即可。

若隐去的就是原数列和，那么剩下的以原数列中心为轴的子串都知道了，答案还是可以直接出来。

```cpp
/* Good Game, Well Play. */
#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
using namespace std;

const int N = 1010;
int T, n, s[N], f[N][N];
multiset < int > con; map < int, int > mp; 
inline void sol()
{
	cin >> n; con.clear(); mp.clear();
	for(int i = 1, x; i < n * (n + 1) / 2; ++i)
		cin >> x, con.insert(x), ++mp[x];
	if(con.count(*con.rbegin()) == 1)
	{
		f[1][1] = *con.rbegin();
		con.erase(prev(con.end()));
		for(int i = 2; i <= n; ++i)
		{
			f[1][i] = *con.rbegin();
			con.erase(prev(con.end()));
			for(int j = 2; j < i; ++j)
			{
				if(i + j > n + 1) continue;
				f[j][i] = f[j][i - 1] + (f[1][i] - f[1][i - 1]);
				if(con.find(f[j][i]) != con.end()) con.erase(con.find(f[j][i]));
			}
			for(int j = 1; j <= i; ++j)
			{
				if(i + j > n + 1) continue;
				if(j == 1) f[i][j] = f[1][i];
				else f[i][j] = f[i][j - 1] + (f[1][j] - f[1][j - 1]);
				if(con.find(f[i][j]) != con.end()) con.erase(con.find(f[i][j]));
			}
		}
		for(int i = 1; i <= n; ++i) cout << f[i][n + 1 - i] << " "; cout << '\n';
	}
	else
	{
		vector < int > rec;
		for(pair < int, int > pii : mp)
			if(pii.second & 1)
				rec.push_back(pii.first);
		cout << *con.rbegin() - rec.back() << " ";
		for(int i = (int)rec.size() - 1; i >= 0; --i)
		{
			if(i) cout << (rec[i] - rec[i - 1]) / 2 << " ";
			else if(n & 1) cout << rec[i] << " ";
			else cout << rec[i] / 2 << " " << rec[i] / 2 << " ";
		}
		for(int i = 1; i < (int)rec.size(); ++i) cout << (rec[i] - rec[i - 1]) / 2 << '\n';
		cout << *con.rbegin() - rec.back() << '\n';
	}
}

int main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> T;
	while(T--) sol();
	return 0;
}
/*

*/
```

---

