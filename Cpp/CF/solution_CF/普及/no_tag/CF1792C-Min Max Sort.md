# Min Max Sort

## 题目描述

对于一个排列，定义一次操作为：在排列中任选两个数字，将它们中的最大值插入至队尾，最小值插入至队首。

现在给定多个排列，问每个排列最少各需多少次操作才能变得严格递增。

## 样例 #1

### 输入

```
4
5
1 5 4 2 3
3
1 2 3
4
2 1 4 3
6
5 2 4 1 6 3```

### 输出

```
2
0
1
3```

# 题解

## 作者：XeCtera (赞：19)

UPD on 2023 / 2 / 14 : 做了一些小修正。

题目链接：[luogu](https://www.luogu.com.cn/problem/CF1792C) | [CF](https://codeforces.com/problemset/problem/1792/C)

$\bf Description$

给定一个 $1\sim n$ 的排列 $p$ 。  
每次操作可以从 $p$ 中选择两个数 $x,y$ ，然后将其中较小者移动至 $p$ 的开头，较大者移动至 $p$ 的结尾。  
要将 $p$ 变为升序 $1,2,\cdots,n$ ，求最小操作次数。

$t$ 组数据。  
$1\le t\le 10^4,1\le n,\sum n\le 2\times10^5.$

$\bf Solution$

正难则反。

分别位于首尾的 $1$ 和 $n$ 一定是在最后一次操作中归位的。  
类似地，$2$ 和 $n-1$ 一定是在倒数第二次操作中归位的。以此类推。

假设共操作 $k$ 次，则 $1\sim k$ 和 $n-k+1\sim n$ 都被归位，而中间的 $k+1\sim n-k$ 按原顺序排列。   

设元素 $i$ 的初始位置为 $pos_i$ 。  
那么 $k$ 次操作能将 $p$ 排序，当且仅当 $pos_{k+1}<pos_{k+2}<\cdots<pos_{n-k}$ 。

首先 $k_0=\lfloor\frac n2\rfloor$ 一定可行。  
如果 $k$ 可行，并且 $pos_k<pos_{k+1},~pos_{n-k}<pos_{n-k+1}$ ，那么 $k-1$ 也可行。  
从 $k_0$ 开始枚举，找到最小的 $k$ 即可。

时间复杂度 $O(\sum n)$ 。

$\bf Code$

```cpp
#include<stdio.h>

const int N=2e5+5;
int T,n,x,k,p[N];

int main() {
    scanf("%d",&T);
    while (T--) {
        scanf("%d",&n);
        for (int i=1; i<=n; ++i)
            scanf("%d",&x),p[x]=i;
        k=(n>>1);
        while (k&&p[k]<p[k+1]&&p[n-k+1]>p[n-k]) --k;
        printf("%d\n",k);
    }
    return 0;
}
```

---

## 作者：baiABC (赞：7)

容易发现，若序列本身有序，则无需操作，否则最后一次操作必移动 $1$ 和 $n$。

那么将原数列去掉 $1$ 和 $n$，数值边界变为 $2$ 和 $n-1$，所需操作数设为 $x$，则答案为 $x+1$，即为一个递归的过程。

我们无需真的删除这两个数，只需记录一个数组 $d$，$d_i$ 表示以数 $i$ 结尾的 最长的 数字连续的 上升子序列长度，则只需要一个 ``if`` 即可判断递归到这一步时数列是否有序。

于是我们就 $O(n)$ 地解决了这道题。

### Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
   ios::sync_with_stdio(0);
   int T = 1; cin >> T;
   while(T--)
   {
      int n; cin >> n;
      vector <int> p(n+1), d(n+1);
      for(int i = 1; i <= n; ++i) cin >> p[i];
      for(int i = 1; i <= n; ++i)
         d[p[i]] = d[p[i]-1]+1;
      int ans = 0;
      for(int i = n/2; i >= 1; --i)
         if(d[n+1-i] < (n+1-i)-i+1)
            ++ans;
      cout << ans << '\n';
   }
   return 0;
}
```

---

## 作者：yemuzhe (赞：5)

### 简化题意

- 给定一个长度为 $n$ 的排列 $p$。
- 你可以进行若干次（可以 $0$ 次）下面操作：
- - 首先选择两个不同的元素，记为 $x, y$，并将它们在 $p$ 中删除。
  - 在 $p$ 的开头插入 $\min \{x, y\}$，使其成为 $p$ 中第一个元素。
  - 在 $p$ 的最后插入 $\max \{x, y\}$，使其成为 $p$ 中最后一个元素。
- 你的目标是通过最少的操作次数使得 $p$ 变成升序的，即让 $p = [1, 2, 3, \ldots, n]$。
- 求这个最少的操作次数。

### 解题思路

观察到最后 $p = [1, 2, 3, \ldots, n]$，我们发现如果有至少 $1$ 次操作则最后一次操作选的两个数一定是 $1, n$，因为最后时第一个数是 $1$，最后一个数是 $n$。

并且容易证明选择重复的数一定不比不选重复的数更优。以此类推，如果有至少 $2$ 次操作则倒数第二次操作选的两个数一定是 $2, n - 1$，如果有至少 $3$ 次操作则倒数第三次操作选的两个数一定是 $3, n - 2$……如果有至少 $\big \lfloor \frac n 2 \big \rfloor$ 次操作则第一次操作为 $\big \lfloor \frac n 2 \big \rfloor, n - \big \lfloor \frac n 2 \big \rfloor + 1$。

例如样例的第四个字测试用例 $p = [5, 2, 4, 1, 6, 3]$ 则是先选择 $3, 4$ 使得 $p = [3, 5, 2, 1, 6, 4]$，再选择 $2, 5$ 使得 $p = [2, 3, 1, 6, 4, 5]$，最后选择 $1, 6$ 使得 $p = [1, 2, 3, 4, 5, 6]$，故答案为 $3$。如果 $n$ 为奇数则不用管中间数。

但有时候答案不会取到 $\big \lfloor \frac n 2 \big \rfloor$。例如 $p = [1, 3, 5, 6, 4, 2]$ 时，只要分别选择 $2, 5$ 和 $1, 6$ 即可，答案为 $2$；$p = [2, 6, 3, 1, 4, 5]$ 时，只要选择 $1, 6$ 即可，答案为$1$。

第一个例子是因为 $3, 4$ 已经排好顺序，不用再动；第二个例子是因为 $2, 3, 4, 5$ 已经排好顺序，不用再动。

记中间数 $m = \big \lfloor \frac {n +1} 2 \big \rfloor$。这启发我们找到一个最大的 $k$，若 $n$ 为奇数，则满足 $p _ {m - k}, p _ {m - k + 1}, \ldots p _ {m + k}$ 即最中间的 $2k + 1$ 个数已经排好顺序；若 $n$ 为偶数，则满足 $p _ {m - k + 1}, p _ {m - k + 2}, \ldots, p _ {m + k}$ 即最中间的 $2k$ 个数已经排好顺序。最终答案就是 $\big \lfloor \frac n 2 \big \rfloor - k$。

我们在找 $k$ 时可以采用二分答案，二分域 $\Big [0, \big \lfloor \frac n 2 \big \rfloor \Big]$。确定区间 $[l, r]$ 内几个数是否排好顺序的方法可以遍历一遍 $p$，若 $p _ i = l$ 则 $l$ 增加 $1$，最后查看 $l$ 是否大于 $r$ 即可。

时间复杂度：$\text O (n \log n)$。

### AC Code

```cpp
#include <cstdio>
#define N 200005
using namespace std;

int T, n, l, r, mid, a[N];

bool check (int x) // k = x 时中间的几个数是否已经排好序
{
    int l = (n + 1 >> 1) - x + (~n & 1), r = (n + 1 >> 1) + x;
    // 当 n 为奇数时，l = (n + 1) / 2 - x, r = (n + 1) / 2 + x
    // 当 n 为偶数时，l = (n + 1) / 2 - x + 1, r = (n + 1) / 2 + x
    for (int i = 1; i <= n; i ++) // 遍历数组
    {
        l += a[i] == l; // 如果 a[i] == l，则 l ++
    }
    return l > r; // 如果 l > r，则说明 l~r 这几个数都在数组中按顺序出现过，返回 true；否则返回 false
}

int main ()
{
    scanf ("%d", &T);
    while (T --)
    {
        scanf ("%d", &n);
        for (int i = 1; i <= n; i ++)
        {
            scanf ("%d", &a[i]);
        }
        l = 0, r = n >> 1; // 确定二分域
        while (l < r) // 开始二分
        {
            mid = l + r + 1 >> 1; // 中间数取 (l + r + 1) / 2，如果不加 1 可能会死循环
            if (check (mid)) // 如果 k = mid 可以
            {
                l = mid;
            }
            else
            {
                r = mid - 1;
            }
        }
        printf ("%d\n", (n >> 1) - l); // 答案为 n / 2 - k
    }
    return 0;
}
```

---

## 作者：L0vely_NaiL0ng (赞：3)

操作等价于选择 $2$ 个数，一个放到最前面，一个放到最后面，我们发现最终序列的一段前缀和一段后缀是通过操作得到的（可能为空也可能是整个序列），而中间的这一段元素是初始序列的（它们之间的相对顺序没有改变），如果假设这 $2$ 段前缀和后缀的长度分别为 $x$ 和 $y$，那么操作数为 $\max(x, y)$。

所以我们将问题转化为：给定一个排列，在排列中寻找一个子序列，使得子序列的元素为连续的自然数，假设为 $l \sim r$，那么操作数为 $\max(l - 1, n - r)$，我们枚举 $r$，$n - r$是固定的，相当于要使 $l$ 尽量小。

我们设 $dp_i$ 表示以 $a_i$ 为结尾且为连续自然数的子序列的最大长度，我们预处理一个数组 $b$，$b_i$ 表示元素 $i$ 在 $a$ 中的下标，即 $a_{b_i} = i$。

那么 $dp$ 数组的转移就很显然了：如果 $b_{a_i - 1} < i$，则有 $dp_i = dp_{b_{a_i - 1}} + 1$，否则 $dp_i = 1$（自己作为一个子序列），我们用 $\max(a_i - dp_i, n - a_i)$ 更新答案即可。

如果还有不懂看代码吧。

```
#include<bits/stdc++.h>
#define PII pair<int, int>
#define mid ((l + r) / 2)
using namespace std;
void read(int &x) {
	x = 0; int f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { 
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + ch - '0'; ch = getchar(); } 
	x *= f;
}
int T;
int n, a[200005], dp[200005], b[200005];
void solve() {
	read(n);
	for (int i = 1; i <= n; i++) {
		read(a[i]); b[a[i]] = i;
	}
	int res = n / 2 + 1;
	for (int i = 1; i <= n; i++) {
		if (b[a[i] - 1] < i) {
			dp[i] = dp[b[a[i] - 1]] + 1;
		} else dp[i] = 1;
		int x = max(n - a[i], a[i] - dp[i]);
		res = min(res, x);
	}
	cout << res << endl;
}
signed main() {
	read(T);
	while (T--) solve();
	return 0;
}
```

---

## 作者：ktq_cpp (赞：0)

## [Problem C](https://codeforces.com/contest/1792/problem/C)

我们先对于任意数据模拟一下，找出一个没有任何优化的方案。容易发现，假设数组大小为 $n$，则我们第 $a$ 次进行的是操作必定是 $(\lfloor\frac{n}{2}\rfloor-a+1,n-\lfloor\frac{n}{2}\rfloor+a)$ 进行，答案即为 $\lfloor\frac{n}{2}\rfloor$。

下面我们考虑优化，可以发现，如果对于第 $a$ 次操作的二元组，如果它是包含第 $a-1$ 次操作的二元组，且二元组内顺序正常，那么他就是合法的，我们要找从第一次操作开始最长的连续合法序列，这个是可以优化的。

[Code](https://codeforces.com/contest/1792/submission/190361956)

---

