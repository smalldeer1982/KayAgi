# Flying Sort (Easy Version)

## 题目描述

This is an easy version of the problem. In this version, all numbers in the given array are distinct and the constraints on $ n $ are less than in the hard version of the problem.

You are given an array $ a $ of $ n $ integers (there are no equals elements in the array). You can perform the following operations on array elements:

1. choose any index $ i $ ( $ 1 \le i \le n $ ) and move the element $ a[i] $ to the begin of the array;
2. choose any index $ i $ ( $ 1 \le i \le n $ ) and move the element $ a[i] $ to the end of the array.

For example, if $ n = 5 $ , $ a = [4, 7, 2, 3, 9] $ , then the following sequence of operations can be performed:

- after performing the operation of the first type to the second element, the array $ a $ will become $ [7, 4, 2, 3, 9] $ ;
- after performing the operation of the second type to the second element, the array $ a $ will become $ [7, 2, 3, 9, 4] $ .

You can perform operations of any type any number of times in any order.

Find the minimum total number of operations of the first and second type that will make the $ a $ array sorted in non-decreasing order. In other words, what is the minimum number of operations that must be performed so the array satisfies the inequalities $ a[1] \le a[2] \le \ldots \le a[n] $ .

## 说明/提示

In the first test case, you first need to move 3, and then 2 to the beginning of the array. Therefore, the desired sequence of operations: $ [4, 7, 2, 3, 9] \rightarrow [3, 4, 7, 2, 9] \rightarrow [2, 3, 4, 7, 9] $ .

In the second test case, you need to move the 1 to the beginning of the array, and the 8 — to the end. Therefore, the desired sequence of operations: $ [3, 5, 8, 1, 7] \rightarrow [1, 3, 5, 8, 7] \rightarrow [1, 3, 5, 7, 8] $ .

In the third test case, the array is already sorted.

## 样例 #1

### 输入

```
4
5
4 7 2 3 9
5
3 5 8 1 7
5
1 4 5 7 12
4
0 2 1 3```

### 输出

```
2
2
0
2```

# 题解

## 作者：F_Mu (赞：5)

**题意**

给一个长度为$n$的数组，数组中的数互不相同，你可以有两种操作

+ 将某一个数放置在数组开头
+ 将某一个数放置在数组结尾

问最小操作多少次可以得到一个递增数列

**分析**

因为数组中的数很大，我们可以将其离散化然后操作，这样我们可以得到一个长度为$n$的排列，目的是得到一个从$1$到$n$的顺序排列

每个数最多操作一次，否则第一次可以不操作，那么我们就要找最多的不需要操作的数，如果不需要操作，则元素的位置不变，如果有这么一组不需要操作的数，我们可以发现，中间的数字是不能插进去的，所以这组数是相邻的数，那么问题就转换为找到数组内最长的相差为$1$的子序列，考虑用$DP$，$dp[i]$表示以数字$i$为结尾的最长子序列长度，则转移方程为
$$
dp[a[i]]=dp[a[i]-1]+1
$$
如果$a[i]-1$出现了，则这个数是$a[i]-1$的后缀，否则这个数是开头，即为$1$

```cpp
#pragma GCC optimize(3, "Ofast", "inline")

#include <bits/stdc++.h>

#define start ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define ll long long
//#define int ll
#define ls st<<1
#define rs st<<1|1
#define pii pair<int,int>
#define rep(z, x, y) for(int z=x;z<=y;++z)
#define com bool operator<(const node &b)
using namespace std;
mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
const int maxn = (ll) 3e3 + 5;
const int mod = 998244353;
const int inf = 0x3f3f3f3f;
int T = 1;
int a[maxn], b[maxn];
int dp[maxn];

void solve() {
    int n;
    cin >> n;
    map<int, int> mp;
    rep(i, 1, n)cin >> a[i], b[i] = a[i], mp[a[i]] = i, dp[i] = 0;
    sort(b + 1, b + n + 1);
    rep(i, 1, n)a[mp[b[i]]] = i;
    int maxx = 1;
    rep(i, 1, n) {
        dp[a[i]] = dp[a[i] - 1] + 1;
        maxx = max(maxx, dp[a[i]]);
    }
    cout << n - maxx << '\n';
}

signed main() {
    start;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
```



---

## 作者：_Kenma_ (赞：0)

# CF1367E 解题报告

## 前言

这个题怎么有一车经验。

## 思路分析

首先考虑离散化，使序列变成一个排列。

设 $n$ 为排列的长度。

然后不难发现答案之多为 $n-1$，构造就是把每个元素由大到小往前放。

考虑怎么缩小操作次数。

不难发现可以在排列中选择一段值域****连续递增****的****子序列****。

设选择的子序列值域区间为 $[l,r]$，那么可以把 $[1,l)$ 从大到小往前放，把 $(r,n]$ 从小到大往后放。

设最长的子序列长度为 $maxn$。

这样答案为 $n-maxn$。

不难发现，这样操作一定能得到一个最优解。

考虑怎样求这个子序列。

设 $f_{i}$ 表示子序列以 $a_i$ 结尾，那么转移为：

$$f_i=f_j+1,a_j+1=a_i$$

从左往右扫 $a_i$，记录 $a_i-1$ 的位置可以做到 $O(n)$。

## 代码实现

实现时我把 $a_i$ 放进了状态里，也是一样的。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,f[200005],a[200005],b[200005],ans,maxn;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			b[i]=a[i];
		}
		sort(b+1,b+1+n);
		int p=unique(b+1,b+1+n)-b-1;
		for(int i=1;i<=n;i++){
			a[i]=lower_bound(b+1,b+1+p,a[i])-b;
		}
		for(int i=1;i<=n;i++){
			f[a[i]]=f[a[i]-1]+1;
			maxn=max(maxn,f[a[i]]);
		}
		cout<<n-maxn<<'\n';
		for(int i=1;i<=n;i++){
			f[a[i]]=0;
		}
		maxn=0;
	}
	return 0;
}
```

---

## 作者：August_Light (赞：0)

# Flying Sort (Easy Version) 题解

[题目传送门](https://www.luogu.com.cn/problem/CF1367F1)

## 题意简述

给定一个由 $n$ 个正整数构成的序列 $a$（无重复数字），现在有两种操作：

1. 选取序列中的任意一项，将其放置于序列首位；

2. 选取序列中的任意一项，将其放置于序列末尾；

现需要将该序列变成一个单调递增序列，求最少的操作次数。

$1 \le n \le 3 \times 10^3, 0 \le a_i \le 10^9$。

## 前置知识

- 数列离散化
  - 模板题目：[B3694 数列离散化](https://www.luogu.com.cn/problem/B3694)

## 解法

先考虑一个更简单的情况：$a$ 是一个 $1$ 到 $n$ 的排列。（此时这题变成了一道站外原题，而那题中将这个序列称为 $p$，所以以下的说明中都使用 $p$）

考虑原序列中不动的，也就是不进行操作的数：

1. 这些数是原序列的一个子序列。
2. 这些数是连续的，且是单调递增的。

发现这是一个简单 DP。

设 $f_i$ 为以第 $i$ 个数结尾的最长的满足条件的子序列长度。

记录一个 $pos$ 数组为每个数在数列中的位置。

如果 $p_i-1$ 排在 $p_i$ 的前面，那么 $f_i=f_{pos_{p_i-1}}+1$。否则 $f_i=1$。

对所有的 $f_i$ 取 $\max$，就是整个序列中最长的满足条件的子序列长度。

```cpp
for (int i = 1; i <= n; i++)
    pos[p[i]] = i;
for (int i = 1; i <= n; i++) {
    f[i] = 1;
    if (pos[p[i] - 1] < i)
        f[i] += f[pos[p[i] - 1]];
    ans = max(ans, f[i]);
}
write(n - ans, '\n');
```

那么如果 $a$ 不是 $1$ 到 $n$ 的排列怎么办？离散化即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

// 省略快读快写的实现

const int MAXN = 3e3 + 100;
namespace Discrete { // 离散化
    int c[MAXN];
    void discrete(int n, int a[], int b[]) {
        for (int i = 1; i <= n; i++)
            c[i] = a[i];
        sort(c + 1, c + n + 1);
        int len = unique(c + 1, c + n + 1) - c - 1;
        for (int i = 1; i <= n; i++)
            b[i] = lower_bound(c + 1, c + len + 1, a[i]) - c;
    }
}
using Discrete::discrete;

int n, p[MAXN], f[MAXN], pos[MAXN], ans;
int a[MAXN];
int main() {
    int t = read(); while (t--) {
        ans = 0; // 多测不清空，亲人两行泪
        n = read();
        for (int i = 1; i <= n; i++)
            a[i] = read();
        discrete(n, a, p);
        for (int i = 1; i <= n; i++)
            pos[p[i]] = i;
        for (int i = 1; i <= n; i++) {
            f[i] = 1;
            if (pos[p[i] - 1] < i)
                f[i] += f[pos[p[i] - 1]];
            ans = max(ans, f[i]);
        }
        write(n - ans, '\n');
    }
    return 0;
}

```

---

## 作者：Mirasycle (赞：0)

其实我们发现答案下界是序列长度减去最长连续数字上升子序列（也就是要求子序列里面数字连续且上升）长度，能否达到呢？因为我们移动数字的顺序是可以自己选择的，所以我们可以选择大小适合的时候移动想要的元素，于是必然可以满足除了最长上升子序列外剩下数字可以在下界操作次数下完成，问题解决。

---

