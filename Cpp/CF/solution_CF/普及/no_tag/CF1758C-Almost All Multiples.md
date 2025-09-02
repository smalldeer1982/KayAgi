# Almost All Multiples

## 题目描述

Given two integers $ n $ and $ x $ , a permutation $ ^{\dagger} $ $ p $ of length $ n $ is called funny if $ p_i $ is a multiple of $ i $ for all $ 1 \leq i \leq n - 1 $ , $ p_n = 1 $ , and $ p_1 = x $ .

Find the lexicographically minimal $ ^{\ddagger} $ funny permutation, or report that no such permutation exists.

 $ ^{\dagger} $ A permutation of length $ n $ is an array consisting of each of the integers from $ 1 $ to $ n $ exactly once.

 $ ^{\ddagger} $ Let $ a $ and $ b $ be permutations of length $ n $ . Then $ a $ is lexicographically smaller than $ b $ if in the first position $ i $ where $ a $ and $ b $ differ, $ a_i < b_i $ . A permutation is lexicographically minimal if it is lexicographically smaller than all other permutations.

## 说明/提示

In the first test case, the permutation $ [3,2,1] $ satisfies all the conditions: $ p_1=3 $ , $ p_3=1 $ , and:

- $ p_1=3 $ is a multiple of $ 1 $ .
- $ p_2=2 $ is a multiple of $ 2 $ .

In the second test case, the permutation $ [2,4,3,1] $ satisfies all the conditions: $ p_1=2 $ , $ p_4=1 $ , and:

- $ p_1=2 $ is a multiple of $ 1 $ .
- $ p_2=4 $ is a multiple of $ 2 $ .
- $ p_3=3 $ is a multiple of $ 3 $ .

We can show that these permutations are lexicographically minimal.

No such permutations exist in the third test case.

## 样例 #1

### 输入

```
3
3 3
4 2
5 4```

### 输出

```
3 2 1 
2 4 3 1 
-1```

# 题解

## 作者：atomic_int (赞：8)

## 题意：
给定 $n$ 和 $x$，用 $1$ ~ $n$ 组成一个排列 $p$，规定 $p_1=x,p_n=1$，并且对于对于 $p_2$ ~ $p_{n-1}$ 满足 $p_i$ 是 $i$ 的倍数。如果存在多个答案，输出字典序最小的答案。无解则输出 `-1`。  

## 分析：
显然可以发现，如果可以组成排列，那么 $n$ 是 $x$ 的倍数。所以如果 $n \bmod x \neq 0$ 那么无解。如果 $n \bmod x = 0$，先将 $p_x=n$，然后构成一个排列，$p_i=i \ (2 \leq i <n,i \neq x)$。此时构成的排列满足条件，但题目要求输出字典序最小，因此可以考虑把 $p_x$ 的值 $n$ 往后移。举例说明：
- 当 $n=8,x=2$ 时：  
首先我们构造的的排列为：$p[] = [2, 8, 3, 4, 5, 6, 7, 1]$ 此时可以发现，$p_x$ 和 $p_4$ 可以交换，因为 $p_x \bmod i=0$ 且 $p_4 \bmod x =0$，互换后为 $p[] = [2, 4, 3, 8, 5, 6, 7, 1]$，满足字典序最小。  

## 代码：
```cpp
#include <bits/stdc++.h>
#define int long long
#define ld long double
#define ri register int
#define inf64 0x7f7f7f7f
#define endl '\n'
#define SeeFloat(x) fixed << setprecision(x)
using namespace std;
inline void solve() {
    int n, x; cin >> n >> x;
    if (n % x) {
        cout << "-1\n";
        return ;
    }
    vector<int> p(n + 1);
    p[1] = x, p[x] = n, p[n] = 1;
    for (int i = 2; i < n; i ++) {
        if (i != x)   p[i] = i;
    }
    for (int i = x + 1; i < n; i ++) {
        if (!(p[i] % x) && !(n % i)) {
            swap(p[i], p[x]);
            x = i;
        }
    }
    for (int i = 1; i <= n; i ++) {
        cout << p[i] << " \n"[i == n];
    }
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
    int T; cin >> T;
    while (T --)    solve();
	return 0;
}
```

---

## 作者：Alex_Wei (赞：4)

挺奇妙的。

设 $x$ 的倍数有 $c$ 个，$p_1$ 占了一个，如果不是 $n$ 空出来，就无解了。因为只有 $c - 1$ 个 $x$ 的倍数，却要填入 $c$ 个位置。因此，当 $x\nmid n$ 时，无解。

从 $i\to p_i$ 连边。不是 $x$ 倍数的位置上，除了 $p_1$ 以外，其它位置都要满足 $p_i = i$，因为除了自环，一个环上必然有至少一个 $i$ 满足 $i\nmid p_i$。因为 $p_1 = x$，$p_n = 1$，所以唯一非自环形如 $n\to 1\to x\to \cdots \to n$，而除了 $n$ 以外，每个在环上的位置 $i$ 需要满足 $p_i$ 是 $i$ 的倍数，因此相当于找到字典序最小的链 $x\to a_1\to  \cdots \to n$，使得后一个数是前一个数的约数。贪心枚举倍数即可。

时间复杂度 $\mathcal{O}(n)$。[代码](https://codeforces.com/contest/1758/submission/184672381)。

---

## 作者：wheneveright (赞：2)

## 题意

给定 $n$ 和 $x$，求长度为 $n$ 的排列满足：
$p_1 = x,p_n = 1$，对于 $i \in [2, n - 1], i \mid p_i$，且字典序最小。

## 解析

给出一个贪心的做法：

首先有结论 $x \mid n$，这点自证不难，然后来看如何构造。

有个很简单的构造，$p_i = i$，特殊的：$p_1 = x, p_x = n, p_n = 1$。

这个答案在很多情况下都是对的，比如样例，但是当输入为 `8 2` 的话就是错的，所以考虑贪心的优化。

假设有 $p_y = y, y \in [x + 1, n - 1]$ 且 $x \mid y, y \mid n$ 那么将 $p_x, p_y$ 交换是一种更好的方式，因为 $y < n$ 且小的数放前面字典序更小，然后发现如果交换了后面还有类似的情况，从小到大枚举 $y$，然后与上一次交换的 $y$ 的位置作比较（第一次的值为 $x$）即可。

## 代码

```cpp
# include <bits/stdc++.h>
using namespace std;
 
const int maxn = 200005;
 
int T, n, x, a[maxn];
 
signed main () {
	ios :: sync_with_stdio (false);
	cin.tie (0); cout.tie (0);
	cin >> T;
	while (T--) {
		cin >> n >> x;
		if (n % x != 0) { puts ("-1"); continue ; }
		for (int i = 1; i <= n; i++) a[i] = i;
		a[1] = x; a[x] = n; a[n] = 1;
		for (int i = x + 1, las = x; i < n; i++)
			if (i % las == 0 && n % i == 0) { // 有更优的
				swap (a[las], a[i]);
				las = i;
			}
		for (int i = 1; i <= n; i++) printf ("%d ", a[i]);
		putchar (10);
	}
	return 0;
}
```

---

## 作者：loser_seele (赞：1)

部分内容参考了官方题解的证明。

首先 $ n \bmod k \neq 0 $ 的情况显然是无解的。

通过观察，发现最优的排列一定满足将某些元素左移位置，剩下的元素保持在原位，再观察这些被移动的元素，发现刚好满足 $ x \mid a_1 \mid a_2 \mid ... \mid a_n $，其中 $ a $ 代表被移动的元素构成的排列，并且一定是所有满足这个条件的排列里最长的。因此质因数分解 $ \frac{n}{x} $ 之后即可得到答案。

证明：

推论：对于任意一个长度大于 $ 1 $ 的环 $ c_i $，都存在至少一个 $ p_{c_i} $ 不能被 $ c_i $ 整除。

首先由于 $ p_{c_i}-c_i $ 的总和为 $ 0 $，而这个排列是长度大于 $ 1 $ 的环，所以必然存在 $ p_{c_i}-c_i < 0 $，也就是 $ p_{c_i} < c_i $，这样必然不能整除。

但原排列都已经被固定了，所以只能通过移动 $ p_n $ 的位置来打破这个限制。又因为要构造字典序最小的排列，因此我们需要最长的这样的链使得字典序最小。如果有多个这样的排列取前面的数最小的。于是质因数分解后排序，然后循环移动这个序列即可。

时间复杂度 $ \mathcal{O}(n) $，可以通过。

---

