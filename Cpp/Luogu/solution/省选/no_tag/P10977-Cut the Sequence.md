# Cut the Sequence

## 题目描述

给定一个长度为 $N$ 的整数序列 $\{a_N\}$，你需要将这个序列划分成若干部分，满足每一部分都是原序列的一个连续子序列，且每个部分的整数之和均不超过 $M$。你的任务是求出在所有合法的划分方式中，每一部分的最大值之和的最小值。

## 说明/提示

样例解释：

将序列划分为三个部分：$\{2,2,2\},\{8,1,8\},\{2,1\}$，此时每一部分的最大值之和为 $2+8+2=12$。可以证明，不存在更优的方案。

## 样例 #1

### 输入

```
8 17
2 2 2 8 1 8 2 1```

### 输出

```
12```

# 题解

## 作者：CJZJC (赞：35)

[题目传送门](https://www.luogu.com.cn/problem/P10977)

## 分析

看到这种题就可以想到动态规划，先设状态：$f_i$ 表示考虑前 $i$ 个数，所需要的最小代价。

发现 $f_i$ 可以从所有 $i$ 以前的状态加后一段区间转移过来，于是可以列出状态转移方程：

$$f_i = \min_{j = i - 1}^{s_i - s_j \leq m}(f_j + \max_{k = j + 1}^i\{a_k\})$$

其中 $j$ 是上一个区间的右端点，$s$ 数组为前缀和数组。

不难发现每次转移 $f_i$ 的复杂度是 $O(N)$ 的，总复杂度为 $O(N^2)$，无法通过此题。

考虑将 $f_i$ 的转移过程进行优化。

由题目的性质，可以发现 $f_i$ 有单调不降的性质，基于这一点，我们可以在转移时：

如果 $a_j \leq a_{j+1}$。

则 $\max_{k = j}^i\{a_k\} = \max_{k = j + 1}^i\{a_k\}$。

则 $f_{j-1} + \max_{k = j}^i\{a_k\} \leq f_j + \max_{k = j + 1}^i\{a_k\}$。

基于这一点，可以转移过来的状态就可以用单调队列来存储了，并且用 `multiset` 来确定最优状态。

## 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define N 100010
int n, m, a[N], s[N], f[N], l, r, q[N << 2];
multiset<int> S;
signed main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        if (a[i] > m) //如果有大于m的数，肯定无解，直接输出-1。
        {
            cout << -1;
            return 0;
        }
        s[i] = s[i - 1] + a[i];
    }
    l = 1;
    r = 0;
    for (int i = 1; i <= n; i++)
    {
        while (l <= r && s[i] - s[q[l]] > m) //如果当前区间和大于m，直接舍去。
        {
            S.erase(f[q[l]] + a[q[l + 1]]); //这里要加的是a[q[l+1]]，因为这是当前区间的最大值。
            l++;
        }
        while (l <= r && a[q[r]] < a[i]) //如果前面的数比当前数小，就会算错当前区间最大值，所以这里要提前弹出这些数。
        {
            S.erase(f[q[r - 1]] + a[q[r]]);
            r--;
        }
        if (l <= r) //如果弹完后，单调队列中还有元素，就可以加入以当前值作为最大值的答案。
        {
            S.insert(f[q[r]] + a[i]);
        }
        q[++r] = i;
        int L = 0, R = i - 1, c;
        while (L <= R) //这里求出距当前位置最远的区间左端点使区间的和小于等于m，为的是避免S中没有元素导致无法更新答案。
        {
            int mid = (L + R) >> 1;
            if (s[i] - s[mid] > m)
            {
                L = mid + 1;
            }
            else
            {
                c = mid;
                R = mid - 1;
            }
        }
        f[i] = f[c] + a[q[l]]; //这种情况下的最大值为a[q[l]]。
        if (S.size())
        {
            f[i] = min(f[i], *S.begin()); //如果S中有元素，就用S中最小的元素更新答案。
        }
    }
    cout << f[n];
}
```

## 小结

这种题目比较简单，其实通过挖掘题目性质就可以做出来，希望读者以后再做类似的题时也能做出来。

---

## 作者：zhouruoheng (赞：16)

# Cut the Sequence

[P10977 Cut the Sequence](https://www.luogu.com.cn/problem/P10977) 

## 前言

单调队列优化 dp 的好题，思维难度大细节多。因为觉得自己看不懂其他题解，在看完 y 总的讲解后豁然开朗，所以写这篇题解来巩固一下。包括完整的细节分析和思考过程，或许很多大佬都不需要 qwq。叠甲完毕，下面开始正文。

## 分析

先考虑无解的情况，将单个元素分成段，每段的和最小，如果还是大于 $m$ 肯定无解。所以当存在 $a_i > m$ 时，输出 $-1$。

### 状态表示

题意和给出的信息都很简单，看 $n$ 的范围判断大致是 $O(n)$ 或者 $O(n\log(n))$ 的算法。因为要满足限制且最优化答案，不难想到动态规划来解决。第一维显然是考虑前 $i$ 个数，通过复杂度分析判断不能存在第二维，实际上也并不需要。所以，设 $f_i$ 表示只考虑前 $i$ 个数划分成若干段，每段的和不超过 $m$ 的最小代价，代价为每一段的最大值之和。

### 状态转移

考虑 $f_i$ 的集合划分依据，显然是最后一段的长度，设上一个状态为 $f_j$，最后一段就是 $[j+1,i]$，其中 $0 \le j \le i-1$，而且要满足限制，所以 $\sum_{k=j+1}^{i} a_k \le m$，最后一段产生的贡献为 $\max_{k=j+1}^{i} a_k$。状态转移方程即为：

$$
    f_i=\min_{0 \le j \le i-1 \land \sum_{k=j+1}^{i} a_k \le m} (f_j+\max_{k=j+1}^{i} a_k)
$$

### 优化

上面这个方程显然是 $O(n^2)$ 的，不足以通过此题。看式子好像也没啥能转化的，考虑一些性质来优化。

首先注意到 $f$ 是单调不减的，也就是说 $f_{i-1} \le f_i$，简单证明下：

设最后一段的贡献为 $a_{max}$，考虑在末尾加上 $a_i$。  
* 若 $a_i$ 加入最后一段，
  * $a_i > a_{max}$ 时，有 $f_i=f_{i-1}-a_{max}+a_i$。
  * $a_i \le a_{max}$ 时，有 $f_i=f_{i-1}$。
* 若 $a_i$ 自己新开一段，有 $f_i=f_{i-1}+a_i$。

因为序列中的数大于等于 $0$，所以有 $f_{i-1} \le f_i$，即 $f$ 单调不减。

蓝书上的话：

> DP 转移优化的指导思想就是及时排除不可能的决策，保持候选集合的高度有效性和秩序性。

所以不妨设 $j$ 为转移的最优决策，考虑其满足什么样的性质。

$$
    f_i=\min(f_j+a_{max})
$$

![](https://cdn.luogu.com.cn/upload/image_hosting/x6cdzbkz.png)

设最后一段的贡献为 $a_{max}$，设 $k_0$ 为满足 $\sum_{k=j+1}^{i} a_k \le m$ 的最小的 $j$。$a_{max_1}$ 为 $[k_0,i]$ 的最大值，下标为 $k_1$。次大值为 $a_{max_2}$，下标为 $k_2$。所以：
$$
    \max_{k=k_0+1}^{i} a_k=a_{max_1}=a_{k_1}
$$
$$
    \max_{k=k_1+1}^{i} a_k=a_{max_2}=a_{k_2}
$$
$$
    \max_{k=k_2+1}^{i} a_k=a_{max_3}=a_{k_3}
$$
$$
    \dots
$$



* 当 $k_0 \le j < k_1$ 时，$a_{max}=a_{max_1}$，$f_j$ 最小值肯定是在 $j=k_0$ 时，所以最优的 $j$ 为 $k_0$。
* 当 $k_1 \le j < k_2$ 时，$a_{max}=a_{max_2}$，最优的 $j$ 为 $k_1$。
* 当 $k_2 \le j < k_3$ 时，$a_{max}=a_{max_3}$，最优的 $j$ 为 $k_2$。

所以最优决策 $j$ 为 $k_0,k_1,k_2,\dots$

所以 $j$ 要成为最优决策，除了要满足 $\sum_{k=j+1}^{i} a_k \le m$ 外，还要满足下面条件之一：

1. 取 $k_0$ 时，$k_0$ 为满足 $\sum_{k=j+1}^{i} a_k \le m$ 的最小的 $j$。
2. 取 $k_1,k_2,k_3,\dots$ 时，满足 $a_j=\max_{k=j}^{i} a_k$。

情况 $1$，只需要用双指针求 $k_0$。

情况 $2$，可以用单调队列维护 $k_1,k_2,\dots$，只需要保证 $a_j$ 单调递减。可是有一个问题，$f_j+a_{max}$ 在单调队列中并不一定是单调的，所以要用其他东西维护，要支持加入元素，删除元素，求最小值，可以用平衡树，当然不用自己写，可以用 set，但是值可能有重复，所以使用 multiset。$k_p$ 为队列中的元素，能产生的贡献为 $f_{k_p}+a_{k_{p+1}}$

有一个细节，只有当单调队列中的元素大于一时，才能出现第二种情况，思考一下就能理解。

时间复杂度瓶颈主要在于 multiset 的操作，时间复杂度为 $O(n\log(n))$。

代码还是很好写的。

## code

``` cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <map>
#include <set>
using namespace std;
typedef long long ll;
const int N=1e5+5;
int n;
ll m;
ll a[N],f[N];
int q[N];
multiset<ll> st;
void solve()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
        cin>>a[i];
		if(a[i]>m) //无解的情况
		{
			cout<<"-1\n";
			return ;
		}
	}
	int l=1,r=0;
	ll sum=0;
	for(int i=1,j=1;i<=n;i++)
	{
		sum+=a[i];
		while(sum>m) 
		{
			sum-=a[j++];
			while(l<=r&&q[l]<j) 
			{
				if(l<r) st.erase(f[q[l]]+a[q[l+1]]);
				l++;
			}
		}
		while(l<=r&&a[q[r]]<=a[i]) 
		{
			if(l<r) st.erase(f[q[r-1]]+a[q[r]]);
			r--;
		}
		q[++r]=i;
		if(l<r) st.insert(f[q[r-1]]+a[q[r]]);
		f[i]=f[j-1]+a[q[l]];//处理后j=k0+1
		if(st.size()) f[i]=min(f[i],*st.begin());
	}
	cout<<f[n]<<'\n';
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	#endif 
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	solve();
	return 0;
}
```

## 后记

思维量大，但是代码简单。利用题目性质进行优化 dp。考虑最优决策满足的条件。双指针和单调队列维护。multiset 维护单调队列贡献。

求审核大大通过 qwq。

---

## 作者：minVan (赞：14)

**解题思路**

考虑线性 dp。

首先如果存在 $a_i>m$，那肯定不满足条件，输出 $-1$。

设 $f_i$ 表示前 $i$ 个数分成若干段，然后每段最大数之和，其中每段内的整数之和不超过 $m$。

$f_i$ 肯定是由 $f_j$（$1\le j<i$）转移过来的，也就是前 $j$ 个数分好后再加上 $(j,i]$ 这一段，所以 $(j,i]$ 这一段需要满足 $\sum\limits_{k=j+1}^{i}a_k\le m$，所以 $j$ 就可以从 $i-1$ 到 $1$ 倒序枚举。

继而有转移方程：

$$
f_i=\min_{j\in S}\left\{ f_j+\max_{k=j+1}^i\left\{a_k\right\}\right\}
$$

其中
$$
S=\left\{j\mid \sum_{k=j+1}^ia_k\le m\right\}
$$

时间复杂度为 $\mathcal{O}(n^2)$，但由于数据太水可以卡过。

Update：现在过不了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n, m, a[N], f[N];
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> m;
  for(int i = 1; i <= n; i++) {
    cin >> a[i];
    if(a[i] > m) { return cout << -1, 0; }
  }
  memset(f, 0x3f, sizeof(f));
  f[0] = 0, f[1] = a[1];
  for(int i = 2; i <= n; i++) {
    int maxi = -1, sum = 0;
    for(int j = i - 1; j >= 0 && sum + a[j + 1] <= m; j--) {
      sum += a[j + 1];
      maxi = max(maxi, a[j + 1]);
      f[i] = min(f[i], f[j] + maxi);
    }
  }
  cout << f[n];
  return 0;
}
```

接着讲正解，单调队列优化 dp。

区间和可以用前缀和处理。

注意到 $j$ 最小的时候满足 $\sum\limits_{k=j+1}^ia_k\le m$，也就是说 $\sum\limits_{k=j}^ia_k>m$，这个数可以单独处理，而 $t=\max\limits_{k=j+1}^i\left\{a_k\right\}$ 可以通过单调队列存一个单调递减的最大值数列，但因为最后答案 $f_j+t$ 不具有单调性，所以需要再存一个小根堆，建议用 `multiset`，因为每次删除时优先队列不好删除。

时间复杂度为 $\mathcal{O}(n\log_2n)$。

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n, m, a[N], sum[N], f[N];
deque<int> dq;
multiset<int> s;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> m;
  bool flag = 0;
  for(int i = 1; i <= n; i++) {
    cin >> a[i];
    flag |= (a[i] > m);
    sum[i] = sum[i - 1] + a[i];
  }
  if(flag) { return cout << "-1", 0; }
  int p = 0;
  for(int i = 1; i <= n; i++) {
    while(sum[i] - sum[p] > m) { ++p; }
    while(!dq.empty() && dq.front() <= p) {
      int tmp = dq.front();
      dq.pop_front();
      if(!dq.empty()) { s.erase(f[tmp] + a[dq.front()]); }
    }
    while(!dq.empty() && a[dq.back()] <= a[i]) {
      int tmp = dq.back();
      dq.pop_back();
      if(!dq.empty()) { s.erase(f[dq.back()] + a[tmp]); }
    }
    int tmp = (!dq.empty() ? dq.back() : 0);
    dq.push_back(i);
    f[i] = f[p] + a[dq.front()];
    if(dq.size() > 1) {
      s.insert(f[tmp] + a[i]);
      f[i] = min(f[i], *s.begin());
    }
  }
  cout << f[n];
  return 0;
}
```

---

## 作者：Iniaugoty (赞：8)

### [P10977 Cut the Sequence](/problem/P10977)

一个写了 2K 的线段树优化 DP，DS 学傻。

我们先不考虑段内和不超过 $m$ 的限制。

设 $dp _ i$ 表示将前 $i$ 个划分为若干段的最小答案，则有转移 $dp _ {i} = \min _ {j = 1} ^ {i} \left( dp _ {j - 1} + \max _ {k = j} ^ {i} a _ k \right)$。直接做复杂度是平方的。

注意到后半部分是一个后缀 $\max$ 状物。

我们需要动态地维护以 $i$ 为结尾的 $a$ 的后缀 $\max$。设 $b _ j = \max _ {k= j} ^ i a _ k$。

由于 $b$ 的单调不增性，在 $i - 1$ 的基础上末尾加 $a _ i$ 的时候，可以（通过维护 $b$ 的区间 $\min$）线段树上二分得到一个最小的 $p$ 使得 $b _ p \le a _ i$，那么这次操作对 $b$ 的影响即对 $[p, i]$ 区间赋值为 $a _ i$。

那如何转移。考虑在上面那坨线段树上，同时维护一个区间 $dp _ {i - 1} + b _ i$ 的 $\min$。注意到 $dp$ 是单调不减的，当区间赋值时 $b$ 全部相同，于是 $[l, r]$ 的这个东西的 $\min$ 即为 $dp _ {l - 1} + b _ l$。

若加上段内和不超过 $m$ 的限制，过程中用双指针维护决策点 $j$ 的下界，同时利用这个下界特判无解。

时间复杂度是优秀的线性对数，不比很多人的单调队列 + `multiset` 劣哦，~~当然常数另说~~。

```cpp
#include <bits/stdc++.h>
#define F(i, a, b) for(int i = (a); i <= (b); ++i)
#define dF(i, a, b) for(int i = (a); i >= (b); --i)

using namespace std;
typedef long long LL;
typedef unsigned long long ull;
typedef unsigned uint;
const int N = 1e5 + 5;
const LL inf = 1e18;

int n, m, a[N]; LL s[N], dp[N];

LL t[N << 2]; int mn[N << 2], tag[N << 2];
void Maketag(int u, int l, int r, int k)
  { t[u] = dp[l - 1] + k, mn[u] = tag[u] = k; }
void Pushdown(int u, int l, int r) {
  int mid = l + r >> 1;
  if (tag[u] >= 0)
    Maketag(u << 1, l, mid, tag[u]),
    Maketag(u << 1 | 1, mid + 1, r, tag[u]),
    tag[u] = -1;
}
void Pushup(int u) {
  t[u] = min(t[u << 1], t[u << 1 | 1]),
  mn[u] = min(mn[u << 1], mn[u << 1 | 1]);
}
void Update(int L, int R, int k, int l, int r, int u) {
  if (L <= l && r <= R) return Maketag(u, l, r, k);
  Pushdown(u, l, r); int mid = l + r >> 1;
  if (L <= mid) Update(L, R, k, l, mid, u << 1);
  if (R > mid) Update(L, R, k, mid + 1, r, u << 1 | 1);
  Pushup(u);
}
int Search(int x, int l, int r, int u) {
  if (l == r) return l;
  Pushdown(u, l, r); int mid = l + r >> 1;
  if (mn[u << 1] <= x) return Search(x, l, mid, u << 1);
  else return Search(x, mid + 1, r, u << 1 | 1);
}
LL Query(int L, int R, int l, int r, int u) {
  if (L <= l && r <= R) return t[u];
  Pushdown(u, l, r); int mid = l + r >> 1; LL res = inf;
  if (L <= mid) res = min(res, Query(L, R, l, mid, u << 1));
  if (R > mid) res = min(res, Query(L, R, mid + 1, r, u << 1 | 1));
  return res;
}

int main() {
//   freopen("zyq.in", "r", stdin);
//   freopen("zyq.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> m;
  F(i, 1, n) cin >> a[i];
  F(i, 1, n) s[i] = s[i - 1] + a[i];
  F(i, 1, n << 2) tag[i] = -1;
  for (int l = 1, i = 1; i <= n; ++i) {
    while (l <= i && s[i] - s[l - 1] > m) ++l;
    if (l > i) { return cout << "-1", 0; }
    int p = Search(a[i], 1, n, 1);
    Update(p, i, a[i], 1, n, 1);
    dp[i] = Query(l, i, 1, n, 1);
  }
  cout << dp[n] << "\n";
  return 0;
}
```

---

## 作者：xAlec (赞：4)

[传送门](https://www.luogu.com.cn/problem/P10977)

## solution

记 $dp_i$ 表示前 $i$ 个已经分好段，有状态转移：$dp_i = dp_{j - 1} + \displaystyle\max_{k=j}^{i}\{a_k\}$，满足 $\displaystyle\sum^i_{k=j}{a_k} \leq m$ 前提下，复杂度 $O(n^2)$，无法接受。

考虑优化，从单调性先入手，对于一个不变的 $i$，当 $j$ 单增时，$\displaystyle\max_{k=j}^{i}\{a_k\}$ 单调不增，$dp_{j-1}$ 单调不减，在我们枚举到 $i$ 时，$dp_{j-1}$ 并不会对转移产生影响。

考虑 $a_i$ 对区间的影响，每次找到 $a_{pos} > a_i$，其中 $pos \in [1,i)$，显然可以发现对于 $\displaystyle\max_{k=j}^{i}\{a_k\}(j > pos) \rightarrow a_i$，考虑线段树维护这个操作，同时维护 $dp_i$ 的转移。

需要进行的操作如下：

- 当前 $j$ 的 $dp_{j-1}$，单点修改。
- 上文提到的操作，区间修改。
- $dp_i$ 的转移，同时区间查询最小值。

每次二分找到满足条件的区间右端点的后继 $ptr$，查询区间即为 $[ptr + 1,i]$，最终答案 $dp_{n}$，完结撒花！

## code
```cpp
#include <cstdio>
#include <ctype.h>
#include <cstring>
#include <algorithm>
#define int long long

using namespace std;
template <typename T>
inline void read(T &x){
    T res = 0,f = 1;
    char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') f = -1;ch = getchar();}
    while(isdigit(ch)){res = (res << 1) + (res << 3) + (ch ^ 48);ch = getchar();}
    x = res * f;
}

const int maxn = 1e5 + 10,inf = 1e18;
int n,m,a[maxn],st[maxn],top,apr[maxn],dp[maxn],sum[maxn];
struct node{int l,r,Answer,lazy,dp;}tree[maxn << 4];

void pushup(int rt){
    tree[rt].Answer = min(tree[rt << 1].Answer,tree[rt << 1 | 1].Answer);
    tree[rt].dp = min(tree[rt << 1].dp,tree[rt << 1 | 1].dp);
}

void pushdown(int rt){
    if(tree[rt].lazy != inf){
        tree[rt << 1].Answer = tree[rt << 1].dp + tree[rt].lazy;
        // cout << tree[rt << 1].Answer << " " << tree[rt << 1].dp << " " << tree[rt].lazy << endl;
        tree[rt << 1 | 1].Answer = tree[rt << 1 | 1].dp + tree[rt].lazy;
        tree[rt << 1].lazy = tree[rt << 1 | 1].lazy = tree[rt].lazy;
        tree[rt].lazy = inf;
    }
}

void Build(int l,int r,int rt){
    tree[rt].l = l,tree[rt].r = r;
    if(l == r){
        tree[rt].Answer = tree[rt].dp = tree[rt].lazy = inf;
        return;
    }
    int mid = l + r >> 1;
    Build(l,mid,rt << 1);
    Build(mid + 1,r,rt << 1 | 1);
    pushup(rt);
}

void Update(int ql,int qr,int rt,int tag){
    int l = tree[rt].l,r = tree[rt].r;
    if(ql <= l && qr >= r)
    {
        tree[rt].Answer = tree[rt].dp + tag;
        tree[rt].lazy = tag;
        return;
    }
    pushdown(rt);
    int mid = l + r >> 1;
    if(ql <= mid)
        Update(ql,qr,rt << 1,tag);
    if(qr > mid)
        Update(ql,qr,rt << 1 | 1,tag);
    pushup(rt);
}

void Modify(int pos,int rt){
    int l = tree[rt].l,r = tree[rt].r;
    if(l == r){
        tree[rt].Answer = inf;
        tree[rt].dp = dp[pos - 1];
        return;
    }
    int mid = l + r >> 1;
    pushdown(rt);
    if(pos <= mid)
        Modify(pos,rt << 1);
    else
        Modify(pos,rt << 1 | 1);
    pushup(rt);
}

int query(int ql,int qr,int rt){
    int l = tree[rt].l,r = tree[rt].r;
    if(ql <= l && qr >= r)
        return tree[rt].Answer;
    pushdown(rt);
    int mid = l + r >> 1,val = inf;
    if(ql <= mid)
        val = min(val,query(ql,qr,rt << 1));
    if(qr > mid)
        val = min(val,query(ql,qr,rt << 1 | 1));
    return val;
}

inline void init(){
    read(n),read(m);
    for(int i = 1;i <= n;i ++) {
        read(a[i]),sum[i] = sum[i - 1] + a[i];
        if(a[i] > m){
            printf("-1\n");
            exit(0);
        }
    }
    st[++ top] = 1;
    for(int i = 2;i <= n;i ++){
        while(top && a[st[top]] < a[i]) top --;
        if(top) apr[i] = st[top];
        st[++ top] = i;
    }
    // 预处理 a[pos] > a[i]
    Build(1,n,1);
}

inline void Solve(){
    int Answer = inf;
    bool flagAns = 1;
    for(int i = 1;i <= n;i ++){
        Modify(i,1);
        if(apr[i] < i) Update(apr[i] + 1,i,1,a[i]);
        int ptr = lower_bound(sum,sum + i + 1,sum[i] - m) - sum;//  二分找到满足条件的下标
        if(ptr < i) dp[i] = query(ptr + 1,i,1);
        else{// 没有满足的无解
            flagAns = 0;
            break;
        }
    }
    if(!flagAns)
        printf("-1\n");
    else
        printf("%lld\n",dp[n]);
}

signed main(){
    init();
    Solve();
    return 0;
}
```

---

## 作者：zzzyyyyhhhhh (赞：3)

奇怪的做法。

设当前位置为 $i$，$f_i$ 表示最后一个连续段结尾为 $i$ 的最小答案，开 $10^6$ 个 `multiset` 维护对于每个 $k$,$\displaystyle\max_j^i=k$ 的所有 $f_j$。新加入一个值 $p$ 时将所有 $k<p$ 的 $k$ 的 `multiset` 合并到 $p$ 的 `multiset` 启发式合并即可，此外还要开一个 `multiset` 计入对于每个有值的 $k$ 的 $k+\texttt{k 集合中最小值}$ 的值，最小值来更新 $i$ 的答案，同时还要开一个 `set` 维护所有有元素的 $k$ 集合。

说的我自己都晕了，还是看代码吧。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e6+100;
int n,m,a[N],f[N],mx[20][N],sum[N];
multiset<int> s[N],se;
set<int> ss;
inline void insert(int mx,int v)
{
	ss.insert(mx);
	if(s[mx].empty())
	{
		se.insert(v+mx);
	}
	else
	{
		if(v<(*s[mx].begin()))
		{
			se.erase(se.find(mx+(*s[mx].begin())));
			se.insert(v+mx);
		}
	}
	s[mx].insert(v);
}
inline void ea(int mx,int v)
{
	se.erase(se.find((*s[mx].begin())+mx));
	s[mx].erase(s[mx].find(v));
	if(s[mx].empty())ss.erase(mx);
	else se.insert((*s[mx].begin())+mx);
}
inline void uni(int x,int y)//x->y
{
	ss.erase(x);
	if(!s[y].empty())se.erase(se.find((*s[y].begin())+y));
	se.erase(se.find((*s[x].begin())+x));
	if(s[x].size()>s[y].size())swap(s[x],s[y]);
	for(auto i:s[x])s[y].insert(i);
	s[x].clear();
	se.insert((*s[y].begin())+y);
}
inline int get(int l,int r)
{
	if(l>r)return 0;
	int lg=__lg(r-l+1);
	return max(mx[lg][l],mx[lg][r-(1<<lg)+1]);
}
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i],mx[0][i]=a[i];
	for(int i=1;i<=n;i++)
	{
		sum[i]=sum[i-1]+a[i];
		if(a[i]>m)
		{
			cout<<"-1";
			return 0;
		}
	}
	int lg=__lg(n+1);
	for(int i=1;i<=lg;i++)
		for(int j=0;j<=n;j++)
			mx[i][j]=max(mx[i-1][j],mx[i-1][j+(1<<(i-1))]);
	int l=0;
	insert(0,0);
	for(int i=1;i<=n;i++)
	{
		while(sum[i]-sum[l]>m)ea(get(l+1,i-1),f[l]),l++;
		if((*ss.begin())<a[i])
		{
			ss.insert(a[i]);
			while((*ss.begin())<a[i])
				uni((*ss.begin()),a[i]);
		}
		f[i]=(*se.begin());
		insert(a[i+1],f[i]);
	}
	cout<<f[n];
}
```

---

## 作者：Barewalk (赞：3)

[P10977 Cut the Sequence](https://www.luogu.com.cn/problem/P10977)

### Preface

本题解从正面更详细易懂的讲解了单调队列优化的原理。

顺手膜拜一下[隔壁](https://www.luogu.com.cn/problem/P1295)写出 $O(n)$ 算法的大佬，真的 tql！本蒟蒻怎么都想不明白这个算法的正确性，本来想写个用一个双端队列代替两个单调栈的写法，结果阳历美国。。

### Solution

首先判断无解的情况。由于序列元素非负，所以每一段整数和最小就是自己本身。那么若存在 $a_i > m$，无解。

很容易想到动态规划。设计状态 $dp_i$ 表示前 $i$ 个数的最小贡献，决策为 $i$ 所在的最后一段的长度。转移方程很好想：

$$dp_i = \min_{0 \le j < i \wedge \sum_{k = j + 1}^{i}a_k \le m}\{dp_j +\max_{j < k \le i}\{a_k\}\}$$

初始化 $dp_0 = 0$，其余为极大值。

```cpp
dp[0] = 0;
for (int i = 1; i <= n; ++ i) {
    dp[i] = 0x7f7f7f7f;
    ll sum = 0, maxx = 0;
    for (int j = i; j; -- j) {
        sum += a[j], maxx = max(maxx, a[j]);
        if (sum > m) break;
        dp[i] = min(dp[i], dp[j - 1] + maxx);
    }
}
```

由于转移是 $O(n)$ 的，所总复杂度为 $O(n ^ 2)$，无法通过本题，考虑继续优化。

原状态已经够简洁，不太好优化，因此考虑优化决策。单看转移方程，单调性并不明显，于是需要我们来分析最优决策可能具有的性质，也就是本题的难点。

我们先假设一个可行的决策 $j$。可知转移过程包含的贡献有：

$dp_j + \max_{j < k \le i}\{a_k\}$ 与 $dp_{j + 1} + \max\limits_{j + 1 < k \le i}\{a_k\}$。

很容易想到 $dp$ 数组是单调不降的。那么决策 $j$ 如果不会更劣，需满足 $a_{j + 1} \le \max\limits_{j + 1 < k \le i}\{a_k\}$。

以此类推，那么最优决策肯定在满足 $a_j = \max\limits_{j \le k \le i}\{a_k\}$ 的 $j$ 中。简单说明一下：

模拟一下上述过程。如果不满足的话，$j - 1$ 会比 $j$ 更优，一直减到满足或 $j$ 是满足 $\sum_{k = j + 1}^{i}\{a_k\} \le m$ 的最小决策为止。

于是，我们维护一个**决策点 $j$ 单调递增，$a_j$ 单调递减**的队列 $q$。

那么队列里某一决策 $j$ 可以提供的贡献就是 $dp_{q_j} + a_{q_{j + 1}}$。

特别的，可能最优的贡献还存在 $dp_{j_0 - 1} + a_{q_1}$，$j_0$ 为满足 $\sum_{k = j_0}^{i}\{a_k\} \le m$ 的最小决策。

因为队列中元素的贡献并不是单调的，我们不能直观的找出队列中贡献最大的元素。于是我们用平衡树维护，这也是贡献非单调的一般做法。

当然，我们不需要手写平衡树。由于可能存在重复元素，直接用 STL 里的 multiset 即可。

Tips：十年 OI 一场空，不开_________见祖宗！

### Codetime

```cpp
#include <iostream>
#include <set>
#define maxN 100100
#define ll long long
using namespace std;
int read() {
    int x = 0, w = 1; char ch = getchar();
    while (ch < '0' || ch > '9') {w = ch == '-' ? -1 : 1; ch = getchar();}
    while (ch >= '0' && ch <= '9') {x = x * 10 + ch - 48; ch = getchar();}
    return x * w;
}
int n, m, a[maxN];
int q[maxN], head = 1, tail;
ll dp[maxN], sum; 
multiset<ll> S;
int main() {
    cin >> n >> m;
    int j0 = 1;
    for (int i = 1; i <= n; ++ i) {
        sum += a[i] = read();
        if (a[i] > m) return puts("-1"), 0;
        while (sum > m) sum -= a[j0 ++];    // 维护 j0
        while (head <= tail && q[head] < j0) {  // 排除队首过期元素
            if (head < tail) S.erase(dp[q[head]] + a[q[head + 1]]);
            head ++;
        }
        while (head <= tail && a[i] > a[q[tail]]) { // 插入新元素并维护队尾单调性
            if (head < tail) S.erase(dp[q[tail - 1]] + a[q[tail]]);
            tail --;
        }
        q[++ tail] = i;
        if (head < tail) S.insert(dp[q[tail - 1]] + a[i]);
        // 用两种可能最优的贡献取最小值更新
        dp[i] = dp[j0 - 1] + a[q[head]];
        if (S.size()) dp[i] = min(dp[i], *S.begin());
    }
    cout << dp[n] << '\n';
    return 0;
}
```

由于每个点至多被添加或删除一次，所以 set 查找最小值的复杂度是 $O(\log n)$，总复杂度为 $O(n\log n)$。完结撒花！

---

## 作者：I_will_AKIOI (赞：3)

看到区间和 $\le m$，先前缀和维护，记作 $s_i$，那么维护 $s_i-s_j\le m$ 的时候就可以直接双指针维护一个指针 $p$，表示最小的 $j$ 使得 $s_i-s_j\le m$。

接着想到 dp，设 $f_i$ 表示把区间 $[1,i]$ 划分完毕的最小花费。那么枚举上一个转移的点，保证 $s_i-s_j\le m$ 就可以转移。转移方程为 $f_i=\min_{j=1\land s_i-s_j\le m}^{i-1} \Big(f_j+\max_{k=j+1}^{i}a_k\Big)$。

考虑优化。动态维护转移方程里的 $\max_{k=j+1}^{i}a_k$。发现是后缀最大值，如何维护呢？

假设 $n=5,a=\{2,5,3,1,4\}$。此时我们枚举到了 $i=5$，需要把 $a_5$ 加进来并维护后缀最大值，加进来之前，也就是 $i=4$ 时，后缀最大值 $b=\{5,5,3,1\}$，把 $a_5$ 加入之后，由于 $b_3<a_5,b_4<a_5$，所以 $b_3$ 和 $b_4$ 被 $a_5$ 顶替了，后缀最大值变为 $\{5,5,4,4,4\}$。

发现了吗？加入 $a_i$ 之后，假设在 $i$ 之前且离 $i$ 最近且大于 $a_i$ 的数的下标为 $pre_i$，那么下标为 $k\in[pre_i+1,i]$ 的后缀最大值会被赋值为 $a_i$。

$pre_i$ 显然可以单调栈维护，区间赋值采用线段树维护，线段树需要维护两个序列 $f_i$ 和 $maxx_i$ 和 $\min\{f_i+maxx_i\}$。需要支持如下操作。

+ 单点赋值，求出 $f_i$ 之后更新线段树信息时需要。

+ 区间赋值 $maxx_i$，更新后缀最大值时需要。

+ 区间查询 $\min\{f_i+maxx_i\}$，转移时需要。

然后上一个区间赋值的懒标记，但是发现懒标记下传之时，我们无法更新 $\min\{f_i+maxx_i\}$，因此还需要维护一个 $minn_i$ 表示当前区间 $f_i$ 的最小值，于是本题就做完了。

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 100005
using namespace std;
struct Data{int l,r,minn1,minn2,tag;}t[N*4];
int n,m,pos,len,a[N],sum[N],f[N],s[N];
void pushup(int k)
{
	t[k].minn1=min(t[k*2].minn1,t[k*2+1].minn1);
	t[k].minn2=min(t[k*2].minn2,t[k*2+1].minn2);
	return;
}
void maketag(int k,int x)
{
	t[k].minn2=t[k].minn1+x;
	t[k].tag=x;
	return;
}
void pushdown(int k)
{
	if(t[k].tag==-1) return;
	maketag(k*2,t[k].tag);
	maketag(k*2+1,t[k].tag);
	t[k].tag=-1;
	return;
}
void build(int k,int l,int r)
{
	t[k].l=l,t[k].r=r;
	t[k].minn1=0,t[k].minn2=f[l];
	t[k].tag=-1;
	if(l==r) return;
	int mid=l+r>>1;
	build(k*2,l,mid);
	build(k*2+1,mid+1,r);
	pushup(k);
	return;
}
void update1(int k,int l,int r,int x)
{
	if(l<=t[k].l&&t[k].r<=r) {maketag(k,x);return;}
	pushdown(k);
	int mid=t[k].l+t[k].r>>1;
	if(l<=mid) update1(k*2,l,r,x);
	if(r>mid) update1(k*2+1,l,r,x);
	pushup(k);
	return;
}
void update2(int k,int pos,int x,int y)
{
	if(t[k].l==pos&&t[k].r==pos)
	{
		t[k].minn1=x;
		t[k].minn2=x+y;
		return;
	}
	pushdown(k);
	int mid=t[k].l+t[k].r>>1;
	if(pos<=mid) update2(k*2,pos,x,y);
	if(pos>mid) update2(k*2+1,pos,x,y);
	pushup(k);
	return;
}
int query(int k,int l,int r)
{
	if(l<=t[k].l&&t[k].r<=r) return t[k].minn2;
	pushdown(k);
	int mid=t[k].l+t[k].r>>1,res=1e18;
	if(l<=mid) res=min(res,query(k*2,l,r));
	if(r>mid) res=min(res,query(k*2+1,l,r));
	return res;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		sum[i]=sum[i-1]+a[i];
		if(a[i]>m) {cout<<-1;return 0;}
	}
	for(int i=1;i<=n;i++) f[i]=1e18;
	build(1,0,n);
	for(int i=1;i<=n;i++)
	{
		while(sum[i]-sum[pos]>m) pos++;
		while(len&&a[s[len]]<a[i]) len--;
		update1(1,s[len],i-1,a[i]);
		f[i]=query(1,pos,i-1);
		update2(1,i,f[i],0);
		s[++len]=i;
	}
	cout<<f[n];
	return 0;
}
```

---

## 作者：Super_Cube (赞：3)

# Solution

设 $dp_i$ 表示前 $i$ 个数能划分出最小的最大值和，$s_i$ 为序列 $a$ 的前缀和数组。转移比较好想，枚举上一次分段位置：$dp_i=\displaystyle\min_{j\in[1,i],s_i-s_{j-1}\le m}dp_{j-1}+\max_{k=j}^i a_k$。时间复杂度 $O(n^2)$，无法通过。

```cpp
#include<bits/stdc++.h>
long long dp[100005];
int a[100005];
int n,m;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;scanf("%d",&a[i++]));
	memset(dp+1,63,n<<3);
	for(int i=1,j,s,v;i<=n;++i){
		int id;
		for(j=i,s=0,v=0;j;--j){
			if((s+=a[j])>m)break;
			v=std::max(v,a[j]);
			if(dp[i]>dp[j-1]+v)
				dp[i]=dp[j-1]+v,id=j;
		}
	}
	if(dp[n]==0x3f3f3f3f3f3f3f3f)dp[n]=-1;
	printf("%lld",dp[n]);
	return 0;
}
```

考虑每次从 $i-1$ 到 $i$ 会改变些什么？设 $l$ 表示从 $i$ 开始往左第一个不小于 $a_i$ 的位置。那么 $(l,i]$ 这一段的转移中 $\max$ 部分都会变为 $a_i$，其余位置的转移方程不变。

$l$ 可用单调栈找到，区间加区间最小值可用线段树维护。

时间复杂度：$O(n\log n)$。

# Code

```cpp
#include<bits/stdc++.h>
typedef long long ll;
struct segment{
	int l,r;
	ll val,tag;
}t[400005];
void build(int p,int l,int r){
	t[p].l=l;t[p].r=r;
	if(l==r)return t[p].val=l==1?0:0x3f3f3f3f3f3f3f3f,void();
	int mid=l+r>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
}
inline void add(int p,ll x){
	t[p].val+=x;t[p].tag+=x;
}
inline void tag_down(int p){
	if(t[p].tag)
		add(p<<1,t[p].tag),add(p<<1|1,t[p].tag),t[p].tag=0;
}
void add(int p,int l,int r,int x){
	if(t[p].l>=l&&t[p].r<=r)return add(p,x);
	tag_down(p);
	int mid=t[p].l+t[p].r>>1;
	if(l<=mid)add(p<<1,l,r,x);
	if(r>mid)add(p<<1|1,l,r,x);
	t[p].val=std::min(t[p<<1].val,t[p<<1|1].val);
}
void modify(int p,int x,ll y){
	t[p].val=std::min(t[p].val,y);
	if(t[p].l==t[p].r)return;
	tag_down(p);
	modify(p<<1|(x>(t[p].l+t[p].r>>1)),x,y);
}
ll ask(int p,int l,int r){
	if(t[p].l>=l&&t[p].r<=r)return t[p].val;
	tag_down(p);
	int mid=t[p].l+t[p].r>>1;
	if(r<=mid)return ask(p<<1,l,r);
	if(l>mid)return ask(p<<1|1,l,r);
	return std::min(ask(p<<1,l,mid),ask(p<<1|1,mid+1,r));
}
int S[100005],top;
int a[100005];
ll s[100005];
int n,m;
ll ans;
int main(){
	scanf("%d%d",&n,&m);
	build(1,1,n+1);
	for(int i=1,j=1;i<=n;++i){
		scanf("%d",&a[i]);
		s[i]=s[i-1]+a[i];
		while(s[i]-s[j-1]>m)++j;
		while(top&&a[S[top]]<a[i]){
			add(1,S[top-1]+1,S[top],-a[S[top]]);
			--top;
		}
		add(1,S[top]+1,i,a[i]);
		S[++top]=i;
		modify(1,i+1,ask(1,j,i));
	}
	ans=ask(1,n+1,n+1);
	if(ans==0x3f3f3f3f3f3f3f3f)ans=-1;
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：_zuoqingyuan (赞：3)

好像是很经典的数据结构优化 dp。

# 思路分析

设 $dp_i$ 表示将前 $i$ 个数切成若干段的最小代价，显然可以列出转移方程。

$$dp_i=\min_{0\le j<i}\{dp_j+\max_{j<k\le i}a_k\}$$

其中 $dp_0=0$，时间复杂度 $O(n^2)$，~~然后就不会了~~。

蒟蒻做不出紫题很正常吧，打开[讨论区](https://www.luogu.com.cn/discuss/937823)发现这题是个数据结构优化 dp。

大部分的数据结构优化 dp 都可以用线段树解决，我们利用扫描线的思想，维护一个指针从左往右扫，维护决策集合，并计算 dp 值。

假如说当前扫到了位置 $i$，此时线段树的第 $j$ 个位置上存储了 $dp_i$ 从 $dp_j$ 转移的值，即 $dp_j+\max_{k=j+1}^{i}a_k$。我们先不考虑这个值如何维护，如果此时这个值已经维护好，我们就只需要知道 $i$ 可以从那些位置 $j$ 转移，然后线段树上查询区间最大值即可。

求出 $a$ 的前缀和 $S$，因为 $a$ 非负，所以 $S$ 单调不减，$[j,i]$ 之间的和不大于 $L$ 可以写成 $S_i-S_{j-1}\le L$，移项可得 $S_{j-1}\ge S_i-L$，可以二分查找出第一个 $p$ 满足上式，然后查找线段树上 $[p+1,i-1]$ 这一段的最大值直接转移即可。

现在问题是如何快速维护 $dp_j+\max_{k=j+1}^{i}a_k$，令 $A_j=dp_i,B_j=\max_{k=j+1}^{i}a_k$，假如说此时指针从 $(i-1)$ 移动到 $i$，此时线段树上的各个位置还都只是维护 $A_j+\max_{k=j+1}^{i-1}a_k$，新加入一个 $a_i$，可能会更新 $B_j$。所以我们要完成这样一个数据结构：

- 单点更新 $A_i$。

- 令一个区间的 $B_i \gets \max\{B_i,c\}$。

- 查询区间 $\max\{A_i+B_i\}$。

如果您精通 STB，那么这个问题大概是可以直接解决，但是太过复杂。

我们发现实现的难点在于操作二，这引发我们的进一步思考。众所周知：前缀的最大值单调不减，我们找到 $i$ 之前的第一个 $l$ 满足 $a_l\ge a_i$，则：

- $\forall 0\le j\le l,\max\{B_j,a_i\}=B_j$。

- $\forall l< j<i,\max\{B_j,a_i\}=a_i$。

实际相当于把 $j\in[l+1,i-1]$ 的所有 $B_j$ 赋值成了 $a_i$。这样转化完后，就好做多了，我们在线段树每个节点上维护当前区间最小的 $A_j+B_j$，最小的 $A_j$。

对于 $A_i$ 的单点修改直接做，对于区间 $[l,r]$ 赋值为 $a_i$，我们打上懒标记，并用 $\min\{A_j\}+a_i$ 更新最小的 $A_j+B_j$（区间推平后，所有 $B_j$ 均相等）。

对于每个数之前第一个不大于它的数，可以用单调栈实现，时间复杂度 $O(n)$；线段树时间复杂度 $O(n\log n)$。


```cpp
#include <iostream>
#include <cstdio>
using namespace std;
typedef long long ll;
const ll N=1e5+10,inf=1e18;
struct sgt{
	ll mn[N<<2],tag[N<<2],dp[N<<2];
	void push_up(int p){
		mn[p]=min(mn[p<<1],mn[p<<1|1]);
		dp[p]=min(dp[p<<1],dp[p<<1|1]);
		return;
	}
	void push_down(int p){
		if(!tag[p])return;
		tag[p<<1]=tag[p<<1|1]=tag[p];
		mn[p<<1]=tag[p]+dp[p<<1];
		mn[p<<1|1]=tag[p]+dp[p<<1|1];
		tag[p]=0;return;
	}
	void change_dp(int p,int l,int r,int x,ll v){
		if(l==r)return dp[p]=mn[p]=v,void();
		int mid=(l+r)>>1;push_down(p);
		if(x<=mid)change_dp(p<<1,l,mid,x,v);
		if(x>mid)change_dp(p<<1|1,mid+1,r,x,v);
		push_up(p);return;
	}
	void change_v(int p,int l,int r,int L,int R,ll v){
		if(L<=l&&r<=R){
			tag[p]=v,mn[p]=dp[p]+v;
		}else{
			int mid=(l+r)>>1;push_down(p);
			if(L<=mid)change_v(p<<1,l,mid,L,R,v);
			if(R>mid)change_v(p<<1|1,mid+1,r,L,R,v);
			push_up(p);
		}
		return;
	}
	ll ask(int p,int l,int r,int L,int R){
		if(L<=l&&r<=R)return mn[p];
		int mid=(l+r)>>1;ll cnt=inf;
		push_down(p);
		if(L<=mid)cnt=min(cnt,ask(p<<1,l,mid,L,R));
		if(R>mid)cnt=min(cnt,ask(p<<1|1,mid+1,r,L,R));
		push_up(p);return cnt;
	}
}tr;
ll n,L,h[N],w[N],lst[N],stk[N],top,dp[N];
int main(){
	scanf("%lld %lld",&n,&L);
	for(int i=1;i<=n;i++){
		scanf("%lld",h+i);
		w[i]=h[i]+w[i-1];
	}
	h[0]=inf;
	for(int i=n;i>=0;i--){
		while(top&&h[stk[top]]<=h[i])lst[stk[top--]]=i;
		stk[++top]=i;
	}
	tr.change_dp(1,0,n,0,0); 
	for(int i=1;i<=n;i++){
		tr.change_v(1,0,n,lst[i],i-1,h[i]);
		int p=lower_bound(w,w+i,w[i]-L)-w;
		dp[i]=tr.ask(1,0,n,p,i-1);
		tr.change_dp(1,0,n,i,dp[i]);
	}
	printf("%lld\n",dp[n]);
	return 0;
} 
```

如有错误，请指出。

---

## 作者：YangRuibin (赞：2)

提供一个代码奇短的 $O(n \sqrt m)$ 极小常数的做法。
# 原始想法

暴力转移方程读了题就会：
$$$
f_i=\max_{0\le j\le i-1} (f_j + maxnum_{j+1,i})
$$$
进一步观察发现当 $i$ 一定，$maxnum_{j,i}$ 随 $j$ 的增大而减小，而 $f_j$ 随之增大（非严格单调）。

因此，我们可以用单调队列的思想维护 $maxnum_{j+1,i}$，又因为对于同一个 $maxnum$，$f_j$ 越靠前答案越优，所以我们可以对一类 $maxnum$，即单调队列中的同一个元素记录当前的 $f$ 下标和值。要知道 $f_i$，只需要知道队列中的最优决策点即可。

需要怎么维护这个最优决策？

答案是——**暴力**！

# 时间复杂度分析

首先，不同的 $a_i$ 最多有 $n$ 种；其次，我们注意到 $m$ 值域在 $2\times 10^9$ 级别，与 $a_i$ 值域规模相差不大（对于本算法而言）。

根据我们的算法，相同的 $maxnum$ 被记录为一个点，而队列中的 $maxnum$ 总和不可能超过 $m$。

因此任何时刻队列中的点数不可能超过 $2\times \sqrt m$，这随 $m$ 的增大而增大。

又因为点数达到峰值的次数在 $n\div \sqrt m$ 级别，随 $m$ 的增大而减小。**并且 $m$ 稍大一点,它的值就回变得很小。比如当 $m$ 在 $1\times 10^8$ 左右，这个值在 $10$ 左右。**

所以总复杂度并非 $O(n^2)$，而是在 $O(n \sqrt m)$ 级别。同时，上述两者不会同时取上限（因为增减性不同），并且在极端数据下（比如 $a_i$ 从 $n$ 递减）队列中的 $sum$ 也**不是每次从 $1$ 开始加**，所以常数至多为 $0.25$。所以最坏也就跑 $3\times 10^8$ 左右（本地 $2$ 秒，评测机会更快）。~~再加上 Luogu 评测机的神速~~，就可以 [AC](https://www.luogu.com.cn/record/205020936)。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+5;
int n,m,a[N],f[N];
int qmx[N],qid[N],qf[N],ql=1,qr=0;
signed main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)scanf("%lld",a+i);
	for(int i=1,lst=0,sum=0;i<=n;i++)
	{
		sum+=a[i];
		while(sum-a[lst]>m)sum-=a[lst++];
		
		while(ql<=qr&&qid[ql]<=lst)
		{
			if((ql==qr&&qid[ql]<i)||qid[ql]+1<qid[ql+1])qf[ql]=f[qid[ql]],qid[ql]++;
			else ql++;
		}
		
		int tmp=0;
		while(ql<=qr&&qmx[qr]<=a[i])tmp=qid[qr],qr--;
		++qr,qmx[qr]=a[i];
		if(!tmp)tmp=i;
		qid[qr]=tmp,qf[qr]=f[tmp-1];
		
		int now=1ll<<60;
		for(int j=ql;j<=qr;j++)now=min(now,qf[j]+qmx[j]);
		f[i]=now;
	}
	printf("%lld",f[n]);
	return 0;
}
```

# 写在后面

本方法的发现纯属意外，因为我一开始也想写线段树，但一些细节总想不明白。当我尝试地提交暴力，并惊奇地发现只跑了几十毫秒时才开始思考这个做法的时间复杂度。这更告诉了我，做题有时要一点点来，想不懂了就敲敲代码，在敲的过程中，也许会灵光一现，想出属于自己的正解。

---

## 作者：CommandSR (赞：1)

## 题意简述

给定一个长度为 $N$ 的整数序列 $a_1, a_2, \dots, a_N$ 和一个整数 $M$。要求将序列划分为若干连续的子序列，使得每个部分的和不超过 $M$。在所有合法的划分方式中，求每一部分的最大值之和的最小值。如果无法划分则输出 $-1$。

## 基本思路

考虑 DP，设 $f_i$ 为到第 $i$ 个数最大值之和的最小值，则有状态转移方程 $f_i = \min{f_j + \max_{k=j+1}^{i} a_k}$，其中满足 $s_i-s_j \leq m$。其中 $\max_{k=j+1}^{i} a_k$ 可以 ST 表优化，总时间复杂度 $O(n^2)$。

于是可以写出如下代码：

```cpp
int main() {
	n = rd(), M = rd(); F(i, 1, n) a[i] = rd(), s[i] = s[i-1]+a[i];
	Initst();
	F(i, 1, n) f[i] = inf;
	f[0] = 0;
	F(i, 1, n)
		F(j, 0, i-1)
			if (s[i]-s[j] <= M) f[i] = min(f[i], f[j] + Qmax(j+1, i));
	cout << f[n] << '\n';
	return 0;
}
```

实测 88pts。

考虑优化，因为有前缀和的条件所以不能单调队列，转移方程决定了不能斜率优化，考虑数据结构。

方程小改一下 $j$ 的端点问题变为 $f_i = \min{f_{j-1} + \max_{k=j}^{i} a_k}$，其中满足 $s_i-s_{j-1} \leq m$。

$\max_{k=j}^{i} a_k$ 可以动态维护，令 $M = \max_{k=j}^{i} a_k$，当新加入一个值 $a_i$ 时，先在线段树上二分找到一个最小的 $p$ 满足 $seg_p \leq a_i$，那么可以将 $[p, i]$ 这个区间的 $M$ 值全部修改为 $a_i$。

考虑状态转移，$f_i = \min{f_{j-1} + M}$，所以在线段树上再维护一个值 $V = f_{j-1} + M$ 的最小值，利用双指针优化，每一次在区间 $[l, i]$ 找一个最小的 $V$ 进行转移即可。


## AC Code

```cpp
#include <bits/stdc++.h>
#define F(i, a, b) for (int i = a; i <= b; ++i)
#define _F(i, a, b) for (int i = a; i >= b; --i)
#define ll long long
#define lc(rt) (rt<<1)
#define rc(rt) (rt<<1|1)
using namespace std;
ll rd() {
	ll p = 0, f = 1; char ch = getchar();
	while (ch>'9' || ch<'0') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch>='0' && ch<='9') p = p*10+ch-'0', ch = getchar();
	return p * f;
}
const ll N = 2e5 + 5, inf = 1e18;
ll n, M, a[N], s[N], f[N];
namespace Segment_tree {
	struct segNode {ll mn, val, lzy;} seg[N<<2];
	void Pushup(ll rt) {
		seg[rt].mn = min(seg[lc(rt)].mn, seg[rc(rt)].mn);
		seg[rt].val = min(seg[lc(rt)].val, seg[rc(rt)].val);
	}
	void Cov(ll rt, ll l, ll k) {
		seg[rt].mn = seg[rt].lzy = k, seg[rt].val = f[l-1] + k;
	}
	void Pushdown(ll rt, ll l, ll r) {
		ll mid = (l + r) >> 1;
		if (seg[rt].lzy != -1) {
			Cov(lc(rt), l, seg[rt].lzy), Cov(rc(rt), mid+1, seg[rt].lzy);
			seg[rt].lzy = -1;
		}
	}
	void Modify(ll L, ll R, ll x, ll rt, ll l, ll r) {
		if (l >= L && r <= R) {Cov(rt, l, x); return ;}
		ll mid = (l + r) >> 1;
		Pushdown(rt, l, r);
		if (L <= mid) Modify(L, R, x, lc(rt), l, mid);
		if (R > mid) Modify(L, R, x, rc(rt), mid+1, r);
		Pushup(rt);
	}
	ll Query(ll L, ll R, ll rt, ll l, ll r) {
		if (l >= L && r <= R) return seg[rt].val;
		if (l > R || r < L) return inf;
		ll mid = (l + r) >> 1;
		Pushdown(rt, l, r);
		return min(Query(L, R, lc(rt), l, mid), Query(L, R, rc(rt), mid+1, r));
	}
	ll Search(ll x, ll rt, ll l, ll r) {
		if (l == r) return l;
        Pushdown(rt, l, r);
        ll mid = (l + r) >> 1;
        if (seg[lc(rt)].mn <= x) return Search(x, lc(rt), l, mid);
        else return Search(x, rc(rt), mid+1, r);
	}
}
using namespace Segment_tree;
int main() {
	n = rd(), M = rd(); F(i, 1, n) a[i] = rd(), s[i] = s[i-1]+a[i];
	F(i, 1, (n << 2)) seg[i].lzy = -1;
	int l = 1;
	F(i, 1, n) {
		while (l <= i && s[i]-s[l-1] > M) ++l;
		if (l > i) {cout << -1; return 0;}
		ll p = Search(a[i], 1, 1, n);
		Modify(p, i, a[i], 1, 1, n);
		f[i] = Query(l, i, 1, 1, n);
	}
	cout << f[n] << '\n';
	return 0;
}
```

---

## 作者：freoepn (赞：1)

因为只能取连续段，很自然的能够联想到动态规划，设 $dp_i$ 表示将前 $i$ 个数都分好组所需的最小代价，可以得到转移方程 $dp_i = dp_j + \max_{k-j}^{k \leq i} a_i$，其中 $j$ 满足 $sum_i - sum _ {j-1} \leq M$，可以通过二分求出 $j$ 的范围，再用线段树求出最值，但是后面的 $\max$ 值是变化的，需要用单调栈求出第一个大于自己的数后线段树修改，注意细节即可。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long 
int n, L;
const int kMaxN = 100005;
int tr[4 * kMaxN], tag[4 * kMaxN], trr[4 * kMaxN], a[kMaxN], b[kMaxN];
void pushup(int x) {
  tr[x] = min(tr[x << 1], tr[x << 1 | 1]);
  trr[x] = min(trr[x << 1],trr[x<<1|1]);
}
void pushdown(int x) {
  if (!tag[x]) return;
  tag[x << 1] = tag[x << 1 | 1]  = tag[x];
  tr[x << 1] = trr[x<<1] + tag[x] ,  tr[x << 1 | 1] = trr[x << 1 | 1] + tag[x] ;
  tag[x] = 0;
}
void update(int x, int l, int r, int y, int z) {
  if (l == r) {
    trr[x] += z;
    return;
  }
  pushdown(x);
  int mid = (l + r) >> 1;
  if (y <= mid) {
    update(x << 1, l, mid, y, z);
  } else {
    update(x << 1 | 1, mid+1, r, y, z);
  }
  pushup(x);
}
void change(int x, int l, int r, int ql, int qr, int y) {
  if (ql <= l && r <= qr) {
    tag[x] = y;
    tr[x] = trr[x] + tag[x];
    return;
  }
  pushdown(x);
  int mid = (l + r) >> 1;
  if (ql <= mid) {
    change(x << 1, l, mid, ql, qr, y);
  }
  if (qr > mid) {
    change(x << 1 | 1, mid + 1, r, ql, qr, y);
  }
  pushup(x);
}
int query(int x,int l,int r,int ql,int qr){
  if (ql <= l && r <= qr) {
    return tr[x];
  }
  pushdown(x);
  int mid = (l + r) >> 1;
  int maxn = 1e18;
  if (ql <= mid) {
     maxn = min(maxn,query(x << 1, l, mid, ql, qr));
  }
  if (qr > mid) {
    maxn = min(maxn,query(x << 1 | 1, mid + 1, r, ql, qr));
  }
  pushup(x);
  return maxn;
}
int dp[kMaxN];
int sum[kMaxN];
int pre[kMaxN];
signed main() {
  cin >> n >> L;
  stack<pair<int, int> > s;
  s.push(make_pair(1e18, 0));
  for (int i = 1; i <= n; i++) {
    cin >> b[i];
    if(b[i] > L){
      cout << "-1";
      return 0;
    }
    a[i] = b[i];
    sum[i] = sum[i - 1] + a[i];
    while (s.top().first <= b[i]) {
      s.pop();
    }
    pre[i] = s.top().second;
    s.push(make_pair(b[i], i));
  }
  for (int i = 1; i <= n; i++) {
    change(1, 0, n, pre[i], i - 1, b[i]);
  // cout << pre[i]<< " "<< i-1 << " "<< b[i]<< '\n';
    int l = 1, r = i;
    while (l <= r) {
      int mid = (l + r) >> 1;
      if (sum[i] - sum[mid - 1] <= L) {
        r = mid - 1;
      } else {
        l = mid + 1;
      }
    }
   // cout << r << ":"<< i-1 << '\n';
    dp[i] = query(1,0,n,r,i-1);
    update(1,0,n,i,dp[i]);
  //  cout << i << " " << dp[i]<< '\n';
  }
  cout << dp[n];
}
```

---

## 作者：bianshiyang (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P10977)

# 分析
考虑本题解法，首先答案不具有单调性所以二分行不通（并不是所有的最大值最小化都可以用二分），且划分的区间数以及每段区间最大值出现的位置不易得知，故几乎无法使用贪心算法求解。发现如果只考虑最后一段划分的区间，那么其最值只与区间首尾有关，而与前面部分的划分无关，满足最优子结构的性质，考虑使用动态规划进行求解。

定义 $f_i$ 表示划分完前 $i$ 个数后每一部分的最大整数之和的最小值，以最后一段为划分依据，考虑转移：

$f_i=\min_{0\le j<i\wedge \sum_{k=j+1}^ia_k\le m}(f_j+\max_{k=j+1}^ia_k)$

发现 $\max$ 求解时可以在扫描的时候用一个变量 $O(1)$ 维护。所以 DP 的复杂度为 $O(n^2)$，此题无法通过，考虑优化。

我们可以尝试及时排除不必要的决策，首先考虑一个决策 $j$ 何时可能成为最优决策。不难发现 $f_i$ 呈现单调递增的趋势，即多加进来一个数，答案只会变大或者不变，否则可以用 $f_i$ 的划分方式更新 $f_{i-1}$ 使其减小。所以发现如果 $j$ 从 $i-1$ 向前枚举，若 $\sum_{k=j+1}^ia_k\le m$ 条件满足且 $\max_{k=j+1}^ia_k$ 不变的话（上界已经确定，所以最大值要么增大要么不变），那么答案将会变小，也就是说取前面的 $j$ 一定更优，就可以排除很多决策了。

所以对于每一个 $i$，我们向前找到第一个满足 $a_j>a_i$ 的 $j$，这个那么 $j+1$ 到 $i-1$ 的所有决策就都可以排除，而如果此时 $j$ 不满足条件 $\sum_{k=j+1}^ia_k\le m$，那么我们向前找到第一个不满足条件的 $j$ 作为决策，也就是把 $j+1$ 到 $i$ 这一段划分出来。手上有蓝书的同学就会发现我们利用单调性推导出了书中 $j$ 需要至少满足一项的两个条件（而非先猜后证）：

1. $a_j=\max_{k=j}^ia_k$，即 $j$ 是第一个满足 $a_j>a_i$ 的。
2. $\sum_{k=j+1}^ia_k> m$，即 $j$ 是第一个不满足 $\sum_{k=j+1}^ia_k\le m$ 的。

所以我们可以利用单调队列维护所有可能成为最优解的决策点 $j$，即一个决策点 $j$ 单调递增，数值 $a_j$ 单调递减的队列。而 $f_j+\max_{k=j+1}^ia_k$ 和 $a_j$ 的单调性却没有关系，所以可以额外维护一个 `multiset` 来做到和单调队列一起删除，插入元素，每次取第一个迭代器就可以快速转移，时间复杂度 $O(n\log n)$。

# 代码实现

此题代码有很多细节，有些部分借鉴闫总代码，不好理解的结合代码一起看吧：

1. 如何快速找到第一个不满足 $\sum_{k=j+1}^ia_k\le m$ 的 $j$ 呢，二分显然可以。但是双指针可以更快，因为 $i$ 递增的时候 $j$ 一定递增，所以我们用一个变量统计总和即可，并且每次及时删除单调队列中不符合的 $j$。
2. $f_j+\max_{k=j+1}^ia_k$ 如何快速计算呢，首先利用 ST 表可以完成，但是如果我们仔细挖掘单调队列的性质就会发现某一项的 $\max_{k=j+1}^ia_k$ 就是后一项的 $a$ 值。证明也很简单，不妨假设当前项为 $j$ ，下一项为 $k$ ，首先由于单调递减所以 $a_k=\max_{l=k}^{i}$，其次由于决策单调递增所以 $k>j$ 且 $j$ 到 $k-1$ 之间的 $a$ 值因为比 $a_k$ 小而被踢出单调队列，所以 $f_j+\max_{l=j+1}^ia_l=f_j+a_k$。
3. 虽然每一个决策 $j$ 都对应一个 $f_j+\max_{k=j+1}^ia_k$，但是根据第二条可知，每一项的最大值要依赖后一项，也就是说出了单调队列最后一项以外都可以求出对应的 $f_j+\max_{k=j+1}^ia_k$。而最后一项每次都由新插入的 $i$ 来更新即没插入 $i$ 前的最后一项在插入 $i$ 后就变成了倒数第二项可以更新。而此时有人会疑惑 $i$ 又无法更新，但是这样的担心是不必要的，因为 $i$ 无法更新 $f_i$，而下一轮中若 $i$ 还存在在单调队列中则会以相同的方式来更新。同理删除元素时第一次删除的即队尾不更新 `multiset`。

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+100;
int n,a[N],l=1,r,q[N];
ll m,dp[N],sum;
multiset<ll> st;

void shan(ll x)
{
	if(st.find(x)==st.end()) return;//相当于是在这里判断元素存不存在了
	st.erase(st.find(x));
}

int main()
{
	scanf("%d%lld",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if(a[i]>m)//不合法的情况
		{
			printf("-1\n");
			return 0;
		}
	}
	for(int i=1,j=0;i<=n;i++)//j就是第一个不满足和小于等于m的位置，详见1
	{
		sum+=a[i];//j+1到i这一段的和
		while(sum>m) sum-=a[++j];
		while(l<=r&&q[l]<j) shan(dp[q[l]]+a[q[l+1]]),l++;//及时排除不合法的决策
		while(l<=r&&a[q[r]]<=a[i]) shan(dp[q[r-1]]+a[q[r]]),r--;//不满足单调性，这里用r-1就是因为最后一项不删，详见3
		if(l<=r) st.insert(dp[q[r]]+a[i]);//队尾用i来更新，详见3
		q[++r]=i;
		dp[i]=dp[j]+a[q[l]];//可能的决策2
		if(st.size()) dp[i]=min(dp[i],*st.begin());//可能的决策1
	}
	printf("%lld\n",dp[n]);
	return 0;
}
```
完结撒花！！！

---

## 作者：Eric998 (赞：1)

发现一个转移方程：$\displaystyle dp_i=\min_{j=L_i}^i(dp_j+\max_{k=j+1}^i a_k)$，其中 $L_i$ 方便求出。

考虑优化，发现这个东西可以被拆成两部分。$i$ 向右移动的过程中 $dp_i$ 好搞，$\displaystyle\max_i^j$ 每扫到一个数都会进行一次区间推平，这是不好做的。

只考虑这一部分，发现每次推平至多产生一个新的连续段。把区间推平变成对每个覆盖到的连续段单独区间加一下就做完了。

---

## 作者：五年长久 (赞：1)

[题目](https://www.luogu.com.cn/problem/P10977)  
## 1. 题面分析
这道题首先要明确其做法，肯定是 DP 没问题，因为这很符合 DP 的无后效性等原则，其转态转移方程想想也不难出来哈。  
$$f(i)=\min_{j=i-1}^{\sum_{k=j}^{i}a\le m}(f(j-1)+\max_{k=j}^{i}f)$$  
也就是说，以第$j$个元素为分界点，这个元素之前划分不需要管，已经算好了，就是 $f(j)$，而 $[j,i]$ 则划分为一组，累加其最大值即可，然后对于所有合法的 $j$（也就是范围合法，$\sum_{k=j}^ia\le m$）取最小即可。代码：
```c++
//exam name:P10977 Cut the Sequence
#include <iostream>
#include <cstring>
#include <cstdio>
#define int long long 
using namespace std;
const int MAXN=100005;
const int INF=0x3f3f3f3f3f3f3f3f;
int f[MAXN];//当前位置最小最大和 
int sum[MAXN];//前缀和 
int n,m;
signed main(){
	memset(f,0x3f,sizeof(f));
	cin>>n>>m;
	f[0]=0;
	for(int i=1,x;i<=n;i++){
		cin>>x;
		sum[i]=sum[i-1]+x; 
		//朴素的方法：向前找合法位置
		int maxn=0;
		for(int j=i;j>=1;j--){
			maxn=max(maxn,sum[j]-sum[j-1]);
			if(sum[i]-sum[j-1]<=m){//合法
				f[i]=min(f[i],f[j-1]+maxn); 
			} else{
				break;
			}
		} 
	}
	cout<<f[n];
	return 0;
} 
```
很惊人的是，除了 HACK 数据没过以外，其他的数据都过了，而且获得了满分的好成绩（~突然不清楚优化的意义了QAQ~）。主要原因也很简单，数据比较水，加上在第二重循环进行了优化，导致很多次循环都被剪了，使得这道紫题异常简单……  
当然，我们英名的管理员增加了一个 HACK 数据，鼓舞了我们写题的热情，这里由衷膜拜 [xiezheyuan](https://www.luogu.com.cn/user/413065) 大佬，这里给出他编写 python 出 HACK，供各位参考。
```python
#by xiezheyuan
import random

n = int(1e5)
m = int(2 ** 31 - 1)
a = []
for i in range(1, int(9e4)):
    a.append(random.randint(1, 10))
for i in range(int(9e4), int(1e5)):
    a.append(random.randint(1, int(1e6)))
print(n, m)
print(*a)
```

##  优化考虑  
那么，我们考虑优化。如果对我们的初代代码加一个调试，在每次生成完 $f(i)$ 后输出，那么你会得到
 $$f(1)\le f(2)\le f(3)\le ...\le f(n)$$ 
这其实很好理解，对于一个数，加入到序列中，要么就加入一个已有的区间并且要么不对总体产生影响要么变成这个区间的最大值参与计算，而且只会越来越大，那么自然引出了**单调队列**，DP 好基友。    
考虑建一个单调递减的队列，每次来一个值把它加入队列，并把没用的尾巴去掉，同时，如果队头和当前数字所在位置在序列中所构成的区间内的和已经大于了 $m$，则队头已经失去了它的价值，此时果断丢弃。然后，我们遇到了极大的麻烦，就是无论怎样，都得不出理想的解。  
然而，只有简单的单调队列是远远不够的，你会在这上面卡很久，那么这时候还需要一点挖掘。也就是说，当前算出来的值不一定是当前最优，但是也许是后面某一步最优，这时候一个数算完的数据不要丢，用一个**堆**存起来，存什么？存这个解的大小、由下标为几的数推出来的以及这个数编号多少（第二个可以理解为下标的下标，就是第三个的下标）。讲的很乱，因为现在的几篇题解对于这件事都没有很好的讲，我一个蒟蒻来讲，更讲不清楚了 QAQ。  
如果套用官方解释，那么我上面的表述就写成：
$$ 设 j_0 满足 a_{j_0} > \max_{k>{j_0}}{a_k} ， 那么 f_i 一定从某个 f_{j_0}+\max_{k>{j_0}}{a_k} 转移而来$$
~~小声BB：还不如我口头表达得清楚呢……~~   
总之，我觉得好神奇，如果有大佬能解释清楚可以评论我，我来改掉，毕竟这是题眼啊，结果没一篇题解讲这事，我会代表所有 OIer 感谢能讲清楚这件事的大佬膜拜的。
## 分段讲解
重点的代码包括以下几段。  
### 单调队列维护
这里呢选择了手写单调队列，反正也不难，而且用起来自由。
```c++
while(front<tail&&sum[i]-sum[q[front]-1]>m){//队头不合法，出队
  book[q[front]]=true;
  front++; 
}
while(front<tail&&a[q[tail-1]]<a[i]){//当前位置更高，要更新
  tail--; 
  book[q[tail]]=true;
}
...
q[tail++]=i;
```
### 解的维护
解的维护就要靠 ``priority_queue`` 了，毕竟要取最优解嘛，然后解的计算啊什么的都包含在这个代码段里了。
```c++
#include <queue>
...
struct node{
	int value,j,k;
	bool operator < (const node &next) const{
		return value>next.value;
	}
};
priority_queue<node> p;
...
if(front<tail){
  p.push((node){f[q[tail-1]]+a[i],i,q[tail-1]});
}else{
  p.push((node){a[i],i,0});
}
...
while(sum[i]-sum[flag-1]>m){
  flag++;
}
while(!p.empty()&&(book[p.top().j]||sum[i]-sum[p.top().k-1]>m)){
  p.pop();	
}
f[i]=f[flag-1]+a[q[front]];
if(!p.empty()){
  f[i]=min(f[i],p.top().value);
}
```
这一段很不好理解，所以代码要更加仔细研究一下，但是我的代码也丑陋无比……将就着看吧……
## 高清有码
然后就是~喜闻乐见~的代码啦。哎，从下午 6:00 肝到半夜 1:00，脑子停止服务了 QAQ。只要我会的部分有比较思维性的都注释了，不会的我也没办法……
```c++
//exam name:P10977 Cut the Sequence
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#define int long long 
using namespace std;
const int MAXN=100005;
const int INF=0x3f3f3f3f3f3f3f3f;
struct node{
	int value,j,k;
	bool operator < (const node &next) const{
		return value>next.value;
	}
};
priority_queue<node> p;
bool book[MAXN];
int a[MAXN];
int f[MAXN];//当前位置最小最大和 
int sum[MAXN];//前缀和 
int q[MAXN];//介于本题的单调队列太好实现了，所以手写
int front,tail; 
int n,m;
int flag=1;
signed main(){
	memset(f,0x3f,sizeof(f));
	if(f[0]!=INF){//调错
		puts("error!");
		return 114514; 
	}
	cin>>n>>m;
	f[0]=0;
	front=1,tail=1;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum[i]=sum[i-1]+a[i];
		while(front<tail&&sum[i]-sum[q[front]-1]>m){//队头不合法，出队
			book[q[front]]=true;
			front++; 
		}
		while(front<tail&&a[q[tail-1]]<a[i]){//当前位置更高，要更新
			tail--; 
			book[q[tail]]=true;
		}
		if(front<tail){
			p.push((node){f[q[tail-1]]+a[i],i,q[tail-1]});
		}else{
			p.push((node){a[i],i,0});
		}
		q[tail++]=i;
		while(sum[i]-sum[flag-1]>m){
			flag++;
		}
		while(!p.empty()&&(book[p.top().j]||sum[i]-sum[p.top().k-1]>m)){
			p.pop();	
		}
		f[i]=f[flag-1]+a[q[front]];
		if(!p.empty()){
			f[i]=min(f[i],p.top().value);
		}
//		cout<<f[i]<<" ";
	}
//	puts("");
	if(f[n]==INF){
		cout<<-1;
	}else{
		cout<<f[n];
	}
	return 0;
} 
```
## 写在后面
其实这个代码有问题，就是判定 -1 的时候，这么写不一定对，但是，测试点没测 -1 的，建议加强，建议加强，再重复一次，**建议加强！**  
这是我这个蒟蒻第一次写题解，写得不好，希望大家多多包涵，批判性的看，主要是和本题其他大佬的题解相互对应着看，互为补充。

----
完结撒花！
----

---

## 作者：Unnamed114514 (赞：0)

考虑钦定最大值进行转移。

对于 $i$，我们首先求出 $l_i,r_i$ 表示 $i$ 作为最大值的极长区间，同时求出 $p_i$ 表示 $i$ 作为右端点能扩展到最左边的位置 $p_i$，显然 $p_i$ 随 $i$ 增大而增大，单调队列+双指针容易得到 $O(n)$。

容易想到区间能往左扩就往左扩，那么我们从 $i$ 有转移：

若 $p_j\le i$ 那么 $f_{j}\gets\min\{f_j,f_{\max\{p_j-1,l_i-1\}+a_i}\}$

因为我们钦定了最大值为 $a_i$，所以我们不能延伸到 $[1,l_i-1]$，$p_j\le i$ 是因为只有这样 $j$ 才能扩展到 $i$ 才能进行转移。

注意到 $[i,r_i]$ 中 $j$ 随着 $j$ 增大，$p_j$ 增大，一共有 $3$ 段，第一段 $p_j\le l_i$，第二段 $l_i<p_j\le i$，第三段 $p_j>i$，我们显然可以二分出每个段的端点。

对于第一段，转移为 $f_j\gets\min\{f_j,f_{l_i-1}+a_i\}$，这个东西等价于区间取 $\max$ 单点查询，线段树维护即可。

对于第二段，转移为 $f_j\gets\min\{f_j,f_{p_j-1}+a_i\}$，注意到此时有 $a_i=\max\limits_{k=p_j}^j a_k$，因此转移实际上就是选择 $[p_j,j]$ 的转移，单独转移一下即可。

对于第三段，无法转移。

容易发现只有第一段需要维护，所以只需要二分出第一段的端点即可。

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define ls p<<1
#define rs p<<1|1
using namespace std;
const int N=3e5+5;
int n,m,a[N],s[N],L[N],R[N],p[N],f[N],t[N<<2],g[N];
stack<int> S;
multiset<int> st;
void update(int p,int l,int r,int ql,int qr,int w){
	if(ql<=l&&r<=qr){
		t[p]=min(t[p],w);
		return;
	}
	int mid=l+r>>1;
	if(ql<=mid) update(ls,l,mid,ql,qr,w);
	if(mid<qr) update(rs,mid+1,r,ql,qr,w);
}
int ask(int p,int l,int r,int pos){
	if(l==r) return t[p];
	int mid=l+r>>1;
	if(pos<=mid) return min(t[p],ask(ls,l,mid,pos));
	return min(t[p],ask(rs,mid+1,r,pos));
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i) cin>>a[i],s[i]=s[i-1]+a[i];
	for(int i=1;i<=n;++i){
		p[i]=p[i-1];
		if(i==1) p[i]=1;
		st.emplace(a[i]);
		while(s[i]-s[p[i]-1]>m) st.erase(st.lower_bound(a[p[i]])),++p[i];
		g[i]=(*(--st.end()));
	}
	for(int i=1;i<=n;++i){
		while(S.size()&&a[S.top()]<=a[i]) R[S.top()]=i-1,S.pop();
		S.emplace(i);
	}
	while(S.size()) R[S.top()]=n,S.pop();
	for(int i=n;i;--i){
		while(S.size()&&a[S.top()]<a[i]) L[S.top()]=i+1,S.pop();
		S.emplace(i);
	}
	while(S.size()) L[S.top()]=n,S.pop();
	memset(f,0x3f,sizeof(f));
	memset(t,0x3f,sizeof(t));
	f[0]=0;
	for(int i=1;i<=n;++i){
		if(p[i]<=L[i]){
			int l=i,r=R[i];
			while(l<r){
				int mid=l+r+1>>1;
				if(p[mid]<=L[i]) l=mid;
				else r=mid-1; 
			}
			update(1,1,n,i,r,f[L[i]-1]+a[i]);
		}
		f[i]=min(ask(1,1,n,i),f[p[i]-1]+g[i]);
	}
	cout<<f[n]<<endl;
	return 0;
}
```

---

## 作者：xiao7_Mr_10_ (赞：0)

题目有点过于幽默了，代码交到原题上改也不改就能过。

原题链接：[P1295 \[TJOI2011\] 书架](https://www.luogu.com.cn/problem/P1295)

这是一个较为简单的分段 dp。具体而言，有 $f_i=\min_{j=1}^{i}(f_{j-1}+\max_{k=j}^{i} a_k)$。

显然我们可以考虑数据结构优化，配合扫描线，用线段树维护最小值转移。发现唯一难点在于最大值，可以直接从 $i$ 后面修改满足最大值为 $a_i$ 的区间段即可。转移的时候可以二分查找合法转移点区间。

时间复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+5,inf=1e18;
struct Point{
	int val,minn;
	Point operator+(const Point &x)const{
		Point ans;
		ans.val=min(val,x.val);
		ans.minn=min(minn,x.minn);
		return ans;
	}
}c[N<<2];int tag[N<<2];
void updata(int x){
	c[x]=c[x<<1]+c[x<<1|1];
}
void build(int x,int l,int r){
	tag[x]=inf;
	if(l==r){
		c[x]=(Point){inf,inf};
		return;
	}int mid=(l+r)>>1;
	build(x<<1,l,mid),build(x<<1|1,mid+1,r),updata(x);
}
void pushdown(int x,int y){
	tag[x]=y,c[x].val=c[x].minn+y;
}
void down(int x){
	if(tag[x]==inf)return;
	pushdown(x<<1,tag[x]),pushdown(x<<1|1,tag[x]);
	tag[x]=inf;
}
void change(int x,int l,int r,int s,int t,int k){
	if(s>t)return;
	if(l>=s&&r<=t){
		pushdown(x,k);
		return;
	}int mid=(l+r)>>1;down(x);
	if(s<=mid)change(x<<1,l,mid,s,t,k);
	if(t>mid)change(x<<1|1,mid+1,r,s,t,k);updata(x);
}int f[N];
void xg(int x,int l,int r,int s){
	if(l==r){
		c[x].val=inf,c[x].minn=f[l-1];
		return;
	}int mid=(l+r)>>1;down(x);
	if(s<=mid)xg(x<<1,l,mid,s);
	else xg(x<<1|1,mid+1,r,s);updata(x);
}
Point query(int x,int l,int r,int s,int t){
	if(l>=s&&r<=t)return c[x];int mid=(l+r)>>1;down(x);
	if(s>mid)return query(x<<1|1,mid+1,r,s,t);
	else{
		if(t<=mid)return query(x<<1,l,mid,s,t);
		return query(x<<1,l,mid,s,t)+query(x<<1|1,mid+1,r,s,t);
	}
}
int n,m,a[N],sum[N],st[N],L[N],top;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin >> n >> m;
	for(int i = 1;i <= n;i++)cin >> a[i],sum[i]=sum[i-1]+a[i];
	st[++top]=1;
	for(int i = 2;i <= n;i++){
		while(top&&a[st[top]]<a[i])top--;
		if(top)L[i]=st[top];st[++top]=i;
	}
	build(1,1,n);
	for(int i = 1;i <= n;i++){
		xg(1,1,n,i);
		int l =lower_bound(sum,sum + i + 1,sum[i] - m) - sum;
		if(l==i){
			cout << "-1";
			return 0; 
		} //cout << i << " " << l << "\n";
		change(1,1,n,L[i]+1,i,a[i]);
		//[l,i-1]这个区间
		f[i]=query(1,1,n,l+1,i).val;
		
	}cout << f[n];
	return 0;
}
//f[i]=min(f[j-1]+calc(j,i))
//注意到这个东西可以扫描线，做完了
 
```

---

## 作者：KinNa_Sky (赞：0)

线段树优化 dp

设 $f_i$ 表示只考虑前 $i$ 个数且 $i$ 作为一段结尾的最小代价。  
显然有转移
$$
f_i = \min_{\substack{j < i\\ sum_i - sum_j \le m}}(f_j + \max_{j < k \le i} a_k)
$$

对于一段区间的代价，由于在转移 $i$ 时是后缀最小值形式，容易想到用单调栈维护每一段区间的代价，这样可以用线段树区间加减方便维护。  
还算比较典的 trick。

```cpp
while (Top && a[i] > a[Sta[Top]]) {
	upd(Sta[Top - 1] + 1, Sta[Top], -a[Sta[Top]]);
	--Top;
}
upd(Sta[Top] + 1, i, a[i]); Sta[++Top] = i;
```

---

对于区间和的限制：前缀和后可以直接二分找，毕竟已经带了线段树的一个 $\log$，复杂度不是瓶颈；当然也可以双指针。

```cpp
int get(int i) {
	int l = 1, r = i, res = i;
	while (l <= r) {
		int mid = l + r >> 1;
		if (sum[i] - sum[mid - 1] <= m)
			res = mid, r = mid - 1;
		else l = mid + 1;
	}
	return res;
}

// ---
// or

	static int l = 1;
	while (sum[i] - sum[l - 1] > m) ++l;
```

---

为了方便与单调栈维护的最值区间相对应，dp 值 $f_i$ 在线段树上存到了 $i + 1$ 的位置。  
意思是当 $(j, i)$ 能划分为一段区间，这段区间的代价是 $\max_{j \le k \le i} a_k$，其应从 $f_{j - 1}$ 转移。  
错位存储是为了，左端点是 $j$ 的区间代价造成影响恰好落到 $j$ 上；合法的最小区间左端点是 $l$，恰好询问 $(l, i)$ 的转移值。

[Code](https://www.luogu.com.cn/paste/zvfmd1lr) or [云剪切板站](https://www.luogu.me/paste/zvfmd1lr)

---

## 作者：WoXitao (赞：0)

## Cut the Sequence 题解

题意：

给定一个长度为 $N$ 的整数序列 $a$，你需要将这个序列切分成若干部分，每一部分都是原序列的一个连续子序列。

1. 每部分必须满足部分内的整数之和不超过给定的整数 $M$。
2. 找到一种切分方式，使得每一部分的**最大整数**之和最小化。

解答：（建议画图理解）

首先对于序列 $a$ 进行前缀和得到 $sum$，对于条件 $1$ 就转换成了对于每个序列的区间 $[l,r]$ 使其满足 $sum_{r}-sum_{l-1}\le M$ 。

设计序列 $f$，$f_i$ 表示只考虑前 $i$ 位的答案，可以得到转移：

$f_i=\min^{sum_i-sum_j\le M}_{j=i-1}(f_j+\max^{i}_{k=j+1}a_k)$ 

可以发现 $f_i\le f_{i+1}$ 

所以如果对于 一个点 $i$ 和一个点 $j$ 如果在 $[j+1,i]$ 中的所有数均比 $a_i$ 小，那么最优决策点只能在 $j$ 之前。我们发现，最优决策点只能在比 $a_i$ 大的数的前一个位置。

我们只需要维护一个 $a_i$ 单调降的队列，并且维护所有 $a_i$ 对应的第一个比 $a_i$ 大的数 $j$ 的 $f_{j-1}+a_i$  （因为比 $j$ 大的位置 $k$ 的数已经在放入 $j$ 时更新过了），每次使用队列中这个的最小值跟新现在的 $f_i$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int f[200005],a[200005],sum[200005],n,m,q[200005];
multiset<int>Q;
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum[i]=sum[i-1]+a[i];
		if(a[i]>m){
			cout<<-1<<endl;
			return 0;
		}
	}
	int l=1,r=0;
	for(int i=1;i<=n;i++){
		while(l<=r&&sum[i]-sum[q[l]]>m){
			Q.erase(f[q[l]]+a[q[l+1]]);
			l++;
		}
		while(l<=r&&a[q[r]]<a[i]){
			Q.erase(f[q[r-1]]+a[q[r]]);
			r--;
		}
		if(l<=r) Q.insert(f[q[r]]+a[i]);
		q[++r]=i;
		int L=0,R=i-1,p;
		while(L<=R){
			int mid=(L+R)>>1;
			if(sum[i]-sum[mid]>m) L=mid+1;
			else p=mid,R=mid-1;
		}
		f[i]=f[p]+a[q[l]];
		if(Q.size()) f[i]=min(f[i],*Q.begin());
	}
	cout<<f[n];
	return 0;
}
```

---

## 作者：是青白呀 (赞：0)

颜色段均摊优化 dp。

朴素的 dp 形如 $f_i$ 表示考虑到前 $i$ 个位置的答案。双指针求出 $pre_i$ 表示右端点为 $i$ 时，左端点最靠前能到哪个位置，则有 $f_i=\min_{j=pre_i}^i f_{j-1}+\max_{x=j}^i a_x$。复杂度 $O(n^2)$。

不难发现对于任意 $x<y$ 都有 $f_x\leq f_y$，于是对于满足 $\max_{x=j}^i a_x$ 相等的极长连续段 $[l,r]$，我们可以直接选择 $l$ 进行转移。

考虑用双端队列维护所有段，按照下标顺序排序，每次新加入一个值的时候，会更新队尾的若干段的最大值。我们将这些段弹出并合并成同一段，同时更新段的答案；同时我们需要对队首的、左端点小于 $pre_i$ 的段进行更新。注意到 $pre$ 单调递增，则所有段进入队列的次数均摊 $O(1)$，另开一个 multiset 维护每一段的答案即可。

总复杂度 $O(n\log n)$，瓶颈是 multiset 维护当前最小 dp 值。

```cpp
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define ls(x) (x<<1)
#define rs(x) ((x<<1)|1)
#define mp make_pair
#define sec second
#define fir first
#define pii pair<int,int>
#define lowbit(i) i&-i
#define int long long
#define double long double
#define qingbai 666
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N=1e5+5,M=6,S=(1<<15)+5,inf=(ll)8e18+7,mo=998244353;
const double eps=1e-8;
void read(int &p){
	int x=0,w=1;
	char ch=0;
	while(!isdigit(ch)){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	p=x*w;
}
int n,m,a[N],f[N];
multiset<int>val;
struct node{
    int le,ri,val;
};
deque<node>q;
void dels(node x){
    int nwv=x.val+f[x.le-1];
    val.erase(val.find(nwv));
}
void adds(node x){
    int nwv=x.val+f[x.le-1];
    val.insert(nwv);
}
int sum[N];
signed main(){
    read(n),read(m);
    rep(i,1,n)
        read(a[i]),sum[i]=sum[i-1]+a[i];
    int targ=1;
    rep(i,1,n){
        int nl=i;
        while(!q.empty()&&q.back().val<=a[i])
            dels(q.back()),nl=q.back().le,q.pop_back();
        q.push_back((node){nl,i,a[i]}),adds(q.back());
        while(targ<=i&&sum[i]-sum[targ-1]>m)
            targ++;
        if(targ>i){
            puts("-1");
            return 0;
        }
        while(!q.empty()&&q.front().le<targ){
            node x=q.front();
            q.pop_front();
            dels(x),x.le++;
            if(x.le>x.ri)continue;
            adds(x),q.push_front(x);
        }
        f[i]=*val.begin();
    }
    printf("%lld\n",f[n]);
    return 0;
}
```

---

## 作者：tony0530 (赞：0)

真的，是一道 dp 好题。

考虑最朴素的 dp，定义 $f_i$ 为考虑前 $i$ 个数的答案，最朴素的转移方程是：

$f_i = \underset{j=i-1，s_i - s_j \le m}{\min} f_j + \underset{j+1\le k \le i}{\max}a_k$。

这显然不能过，因为时间复杂度是 $O(n^2)$，我们可以将他进行优化：

因为若 $a_j < a_{j + 1}$，则 $f_{j - 1} + \underset{j \le k \le i}{\max}a_k < f_{j} + \underset{j + 1\le k \le i}{\max}a_k$，反之亦然，所以，我们用单调队列来存储，用 multiset 来维护就好了。

### 代码

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 1e5 + 10;

int n, m;
int a[N], s[N], f[N];
int q[N << 2];
multiset<int> S;

signed main()
{
    cin >> n >> m;
    for(int i = 1 ; i <= n ; i ++ )
    {
        cin >> a[i];
        if(a[i] > m)
        {
            cout << -1;
            return 0;
        }
        s[i] = s[i - 1] + a[i];
    }
    int l = 1, r = 0;
    for(int i = 1 ; i <= n ; i ++ )
    {
        while(l <= r && s[i] - s[q[l]] > m) S.erase(f[q[l]] + a[q[l + 1]]), l ++ ;
        while(l <= r && a[q[r]] < a[i]) S.erase(f[q[r - 1]] + a[q[r]]), r -- ;
        if(l <= r) S.insert(f[q[r]] + a[i]);
}
```

---

