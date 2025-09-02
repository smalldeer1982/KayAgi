# No Monotone Triples

## 题目描述

Given a sequence of integers $ a $ of length $ n $ , a tuple $ (i,j,k) $ is called monotone triples if

- $ 1 \le i<j<k\le n $ ;
- $ a_i \le a_j \le a_k $ or $ a_i \ge a_j \ge a_k $ is satisfied.

For example, $ a=[5,3,4,5] $ , then $ (2,3,4) $ is monotone triples for sequence $ a $ while $ (1,3,4) $ is not.

Bob is given a sequence of integers $ a $ of length $ n $ in a math exam. The exams itself contains questions of form $ L, R $ , for each of them he is asked to find any subsequence $ b $ with size greater than $ 2 $ (i.e. $ |b| \ge 3 $ ) of sequence $ a_L, a_{L+1},\ldots, a_{R} $ .

Recall that an sequence $ b $ is a subsequence of sequence $ a $ if $ b $ can be obtained by deletion of several (possibly zero, or all) elements.

However, he hates monotone stuff, and he wants to find a subsequence free from monotone triples. Besides, he wants to find one subsequence with the largest length among all subsequences free from monotone triples for every query.

Please help Bob find out subsequences meeting the above constraints.

## 说明/提示

For the first query, the given sequence itself is monotone triples free.

For the second query, it can be shown that there is no subsequence $ b $ with length greater than $ 2 $ such that $ b $ is monotone triples free.

## 样例 #1

### 输入

```
6 2
3 1 4 1 5 9
1 3
4 6```

### 输出

```
3
1 2 3 
0```

# 题解

## 作者：Tweetuzki (赞：7)

### 题意

给出一个长度为 $n ~ (3 \le n \le 2 \cdot 10 ^ 5)$ 的序列 $a$，$q ~ (1 \le q \le 2 \cdot 10 ^ 5)$ 次询问，每次询问给出一段区间 $[l, r]$，需要找到 $[a_l, a_{l + 1}, \ldots, a_r]$ 中最长的一个子序列 $b$，满足 $b$ 中的最长不下降子序列和最长不上升子序列的长度都不超过 $3$。

### 题解

首先有一个结论，$b$ 的长度不能超过 $4$。

证明不难，假设 $b$ 的长度为 $5$，我们求它的最长下降子序列长度，不妨设为 $l$。

- 当 $l \ge 3$ 时，不满足条件。
- 当 $l \le 2$ 时，根据 [Dilworth 定理](https://www.luogu.com.cn/problem/P1020)，最少不下降子序列划分数等于最长下降子序列长度，那么说明存在一个不下降子序列长度 $\ge 3$。也不满足条件。

因此假设不成立，结论得证。

开始着手解决问题。

为了处理多组询问，我们考虑这样一种方法：

- 预处理时，我们对每一个 $1 \sim n$ 之间的 $i$，维护当它作为 $b_1$ 时，最近的 $b_3$（或 $b_4$）需要在哪里。

- 对于每组询问，我们只需要在 $[l, r]$ 中找到最小值和最小值位置，判断一下最小值是否 $\le r$ 即可知道是否存在这样的 $b$。

我们对 $b$ 的长度为 $3$ 和 $4$ 分类讨论。

#### b 的长度为 3

存在一个长度为 $3$ 的 $b$，只需要序列 $a$ 在 $[l, r]$ 中不单调。

对每一个位置 $i$ 处理出它前面第一个不同于 $a_i$ 的位置 $pre_i$，它后面第一个不同于 $a_i$ 的位置 $nxt_i$，如果有 $(a_i - a_{pre_i})(a_i - a_{nxt_i}) \gt 0$，则存在一个长度为 $3$ 的 $b$ $\{a_{pre_i}, a_i, a_{nxt_i}\}$。

在 $b_1 = pre_i$ 上记录一个可能的 $b_3 = nxt_i$，ST 表维护区间最小值和最小值位置即可。

#### b 的长度为 4

存在一个长度为 $4$ 的 $b$，需要满足 $b_1, b_4$ 既不是 $b$ 中的最大值，也不是 $b$ 中的最小值。

从后往前维护一个单调不降的单调栈 $stk_1$ 和一个单调不升的单调栈 $stk_2$。这表示的意义是，做到第 $i$ 个位置时，$stk_1$ 中的元素是可能成为 $b$ 中最大值的位置，$stk_2$ 中的元素是可能成为 $b$ 中最小值的位置。

为了使 $b_1, b_4$ 不成为 $b$ 中的最大或最小值，可推断出 $b_4$ 需要满足以下条件：

- $b_4$ 既不在 $stk_1$ 中，也不在 $stk_2$ 中。
- 在 $b_4$ 之前，存在一个 $x$，满足 $x$ 在 $stk_1$ 中且 $a_x \neq a_i$，存在一个 $y$，满足 $y$ 在 $stk_2$ 中且 $a_y \neq a_i$。

也就是找到 $stk_1$ 中第一个严格大于 $a_i$ 的位置 $gt$ 和 $stk_2$ 中第一个严格小于 $a_i$ 的位置 $lt$，然后在 $(\max(gt, lt), n]$ 中找到既不在 $stk_1$ 中也不在 $stk_2$ 中的最小位置，这就是符合条件的最小 $b_4$。

这个东西可以用 $\texttt{std::set}$ 进行维护。

最后同样的，得到了每个 $b_1$ 对应的最近 $b_4$，用 ST 表维护一下最小值和最小值位置即可。

如果 $b$ 的长度为 $3$ 为 $4$ 都不满足，那就是 $0$ 了。

时间复杂度 $\mathcal{O}(n \log n + q)$。

代码：

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <set>

const int MaxN = 200000, MaxLog = 18;

int N, M, Q;
int A[MaxN + 5];
int PreDif[MaxN + 5], NxtDif[MaxN + 5];
int Stk1[MaxN + 5], Tp1, Stk2[MaxN + 5], Tp2;
int MinJ[MaxN + 5], Nx1[MaxN + 5], Nx2[MaxN + 5];
int Buc[MaxN + 5], Pop1[MaxN + 5], Pop2[MaxN + 5];
int X[MaxN + 5], R[MaxN + 5];
int St[MaxLog + 2][MaxN + 5], St2[MaxLog + 2][MaxN + 5];
std::set<int> S;

void init() {
  scanf("%d %d", &N, &Q);
  for (int i = 1; i <= N; ++i) scanf("%d", &A[i]);
  for (int i = 1; i <= N; ++i) {
    if (A[i - 1] != A[i]) PreDif[i] = i - 1;
    else PreDif[i] = PreDif[i - 1];
  }
  for (int i = N; i >= 1; --i) {
    if (A[i + 1] != A[i]) NxtDif[i] = i + 1;
    else NxtDif[i] = NxtDif[i + 1];
  }
  R[0] = N + 1;
  for (int i = 1; i <= N; ++i) {
    if (PreDif[i] == 0 || NxtDif[i] == N + 1) continue;
    if (1LL * (A[i] - A[PreDif[i]]) * (A[i] - A[NxtDif[i]]) > 0) {
      M++;
      X[M] = i, R[M] = NxtDif[i];
      if (R[M] < R[St2[0][PreDif[i]]]) St2[0][PreDif[i]] = M;
    }
  }
}

inline int gt(int x) {
  int lbound = 1, rbound = Tp1, ans = N + 1;
  while (lbound <= rbound) {
    int mid = (lbound + rbound) >> 1;
    if (A[Stk1[mid]] > x) {
      ans = Stk1[mid];
      lbound = mid + 1;
    } else rbound = mid - 1;
  }
  return ans;
}

inline int lt(int x) {
  int lbound = 1, rbound = Tp2, ans = N + 1;
  while (lbound <= rbound) {
    int mid = (lbound + rbound) >> 1;
    if (A[Stk2[mid]] < x) {
      ans = Stk2[mid];
      lbound = mid + 1;
    } else rbound = mid - 1;
  }
  return ans;
}

inline int query(int l, int r) {
  int k = 31 - __builtin_clz(r - l + 1);
  int ls = St[k][l], rs = St[k][r - (1 << k) + 1];
  if (MinJ[ls] <= MinJ[rs]) return ls;
  else return rs;
}

inline int query2(int l, int r) {
  int k = 31 - __builtin_clz(r - l + 1);
  int ls = St2[k][l], rs = St2[k][r - (1 << k) + 1];
  if (R[ls] <= R[rs]) return ls;
  else return rs;
}

void solve() {
  S.insert(N + 1);
  for (int i = N; i >= 1; --i) {
    while (Tp1 > 0 && A[Stk1[Tp1]] < A[i]) {
      Buc[Stk1[Tp1]]--;
      Pop1[Stk1[Tp1]] = i;
      if (Buc[Stk1[Tp1]] == 0) S.insert(Stk1[Tp1]);
      Tp1--;
    }
    Stk1[++Tp1] = i, Buc[i]++;
    while (Tp2 > 0 && A[Stk2[Tp2]] > A[i]) {
      Buc[Stk2[Tp2]]--;
      Pop2[Stk2[Tp2]] = i;
      if (Buc[Stk2[Tp2]] == 0) S.insert(Stk2[Tp2]);
      Tp2--;
    }
    Stk2[++Tp2] = i, Buc[i]++;
    Nx1[i] = gt(A[i]), Nx2[i] = lt(A[i]);
    MinJ[i] = *(S.lower_bound(std::max(Nx1[i], Nx2[i])));
  }
  for (int i = 1; i <= N; ++i) St[0][i] = i;
  for (int i = 1; (1 << i) <= N; ++i)
    for (int j = 1; j + (1 << i) - 1 <= N; ++j) {
      int ls = St[i - 1][j], rs = St[i - 1][j + (1 << (i - 1))];
      if (MinJ[ls] <= MinJ[rs]) St[i][j] = ls;
      else St[i][j] = rs;
      ls = St2[i - 1][j], rs = St2[i - 1][j + (1 << (i - 1))];
      if (R[ls] <= R[rs]) St2[i][j] = ls;
      else St2[i][j] = rs;
    }
  for (int q = 1; q <= Q; ++q) {
    int l, r;
    scanf("%d %d", &l, &r);
    int minpos = query(l, r);
    if (MinJ[minpos] <= r) {
      int x = Pop1[MinJ[minpos]], y = Pop2[MinJ[minpos]];
      if (A[minpos] < A[MinJ[minpos]]) y = Nx2[minpos];
      else x = Nx1[minpos];
      printf("%d\n", 4);
      printf("%d %d %d %d\n", minpos, std::min(x, y), std::max(x, y), MinJ[minpos]);
    } else {
      int k = query2(l, r);
      if (R[k] <= r) {
        printf("%d\n", 3);
        printf("%d %d %d\n", PreDif[X[k]], X[k], R[k]);
      } else printf("%d\n\n", 0);
    }
  }
}

int main() {
  init();
  solve();
  return 0;
}
```



---

## 作者：Alex_Wei (赞：4)

Upd on 2022.9.17：修改题解。

> [CF1332G No Monotone Triples](https://www.luogu.com.cn/problem/CF1332G)

好题。

首先根据 Dilworth 定理证明长度只能是 $3$ 或 $4$。

对于长度为 $3$ 的，考虑一个值相同的极长连续段 $[l + 1, r]$，若它是关于与它相邻的两个位置的极值点，那么 $(l, l + 1, r + 1)$ 合法。维护 $lst_i$ 表示从 $i$ 开始第一个这样的 $l$，$rt_i$ 表示 $i$ 下一个与它不同的后继的位置，查询时检查是否有 $rt_{lst_l + 1} + 1 \leq r$，则 $(lst_l, lst_l + 1, rt_{lst_l + 1})$ 为一个合法答案。时间复杂度线性。

对于长度为 $4$ 的，必然是 $b_2, b_3$ 取极值，$b_1, b_4$ 落在值域中间且不等于极值。考虑从后往前枚举每个位置 $p$ 并维护从 $p$ 开始 **非严格** 前缀最小值和最大值的单调栈，那么只有落在单调栈里面的元素才会成为极值。例如，若 $p < i < j$ 且 $a_i < a_j < a_p$，那么显然是 $a_i$ 更适合做最小值。对于最大值同理。

核心观察：作为 $b_4$ 的位置 $p_4$ 一定不会落在单调栈内，因为单调栈内是前缀最大值或前缀最小值。同时，如果 $p_4$ 没有落在单调栈内，则考虑 $p_4$ 落在最大值和最小值单调栈内的前驱位置 $u, v$，则必然有 $a_u > a_{p_4}$ 且 $a_v < a_{p_4}$，否则 $p_4$ 成为某个单调栈内的元素。

考虑 set 维护所有不在单调栈内的位置 $S$，每次只要查两个单调栈第一个不等于 $a_p$ 的位置 $mnp$ 和 $mxp$ 的较大值在 $S$ 中的后继 $q$，那么当 $p_1 = p$ 时，$p_4$ 最小的合法取值即 $q$，$p_2, p_3$ 的合法取值也可以在栈内二分最后一个在 $q$ 之前的位置得到。$mnp$ 和 $mxp$ 同样可以栈内二分或递推预处理。

至于回答询问，既然已经对每个 $p$ 求得 $p_1 = p$ 时 $p_4$ 最小的合法取值 $c_p$，离线扫描线或对 $c_i$ 建线段树均可。

时间复杂度 $\mathcal{O}(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define TIME 1e3 * clock() / CLOCKS_PER_SEC
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ull = unsigned long long;
inline ll read() {
  ll x = 0, sgn = 0;
  char s = getchar();
  while(!isdigit(s)) sgn |= s == '-', s = getchar();
  while(isdigit(s)) x = x * 10 + s - '0', s = getchar();
  return sgn ? -x : x;
}
inline void print(int x) {
  if(x < 0) return putchar('-'), print(-x);
  if(x >= 10) print(x / 10);
  putchar(x % 10 + '0');
}
bool Mbe;
constexpr int N = 2e5 + 5;
int n, q, a[N], in[N], lst[N], rt[N];
set<int> exist;
set<pii> query;
struct stack {
  int tp, stc[N];
  bool empty() {return !tp;}
  int top() {return stc[tp];}
  void pop() {
    int val = stc[tp--];
    if(!--in[val]) exist.insert(val);
  }
  void push(int val) {
    stc[++tp] = val;
    if(!in[val]++) exist.erase(val);
  }
  int binary(int val) {
    if(a[stc[1]] == a[val]) return n;
    int l = 1, r = tp;
    while(l < r) {
      int m = l + r + 2 >> 1;
      if(a[stc[m]] == a[val]) r = m - 1;
      else l = m;
    }
    return stc[l];
  }
  int pref(int val) {
    int l = 1, r = tp;
    while(l < r) {
      int m = l + r >> 1;
      if(stc[m] < val) r = m;
      else l = m + 1;
    }
    return stc[l];
  }
} mn, mx;
vector<int> ans[N];
vector<pii> buc[N];
bool Med;
int main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  cin >> n >> q, lst[n + 1] = rt[n + 1] = n + 1;
  for(int i = 1; i <= n; i++) a[i] = read();
  for(int i = n; i; i--) {
    exist.insert(i);
    rt[i] = a[i] == a[i + 1] ? rt[i + 1] : i + 1;
    if(rt[i + 1] <= n && 1ll * (a[i + 1] - a[i]) * (a[i + 1] - a[rt[i + 1]]) > 0) lst[i] = i;
    else lst[i] = lst[i + 1];
  }
  exist.insert(n + 1);
  for(int i = 1; i <= q; i++) {
    int l = read(), r = read();
    if(lst[l] <= n && rt[lst[l] + 1] <= r) {
      ans[i].push_back(lst[l]);
      ans[i].push_back(lst[l] + 1);
      ans[i].push_back(rt[lst[l] + 1]);
    }
    if(r - l + 1 >= 4) {
      buc[r - 3].push_back({i, r});
      buc[l - 1].push_back({-i, r});
    }
  }
  for(int i = n; i; i--) {
    while(!mx.empty() && a[i] > a[mx.top()]) mx.pop();
    while(!mn.empty() && a[i] < a[mn.top()]) mn.pop();
    mx.push(i), mn.push(i);
    for(pii it : buc[i]) {
      int id = abs(it.first), r = it.second;
      if(it.first < 0) {
        auto pt = query.find({r, id});
        if(pt != query.end()) query.erase(pt);
      }
      else query.insert({r, id});
    }
    if(!query.empty()) {
      int pos = *exist.upper_bound(max(mn.binary(i), mx.binary(i)));
      if(pos > n) continue;
      while(!query.empty()) {
        auto pt = --query.end();
        if(pt->first >= pos) {
          int id = pt->second;
          ans[id].clear();
          ans[id].push_back(i);
          ans[id].push_back(mn.pref(pos));
          ans[id].push_back(mx.pref(pos));
          ans[id].push_back(pos);
          query.erase(pt);
        }
        else break;
      }
    }
  }
  for(int i = 1; i <= q; i++) {
    if(ans[i].size()) {
      putchar(ans[i].size() + '0'), putchar('\n');
      sort(ans[i].begin(), ans[i].end());
      for(int it : ans[i]) print(it), putchar(' ');
    }
    else putchar('0');
    putchar('\n');
  }
  cerr << TIME << " ms\n";
  return 0;
}
/*
2022/9/16
author: Alex_Wei
start coding at 22:43
finish debugging at 23:46
*/
```

---

## 作者：Erine (赞：1)

*3100？*2100！

**首先答案序列不能很长**、跑一个长为 $5$ 的全排列发现根本就没有合法的，所以有解的话答案要么是 $3$ 要么是 $4$。如果答案是 $4$，那么这个子序列的大小关系长的形如这个样子：

```
2 1 4 3
2 4 1 3
3 1 4 2
3 4 1 2
```

**可以看出，只要最大最小值不在两侧，就是合法的。我们把这样的区间叫做“好区间”，其余的称作“坏区间”。**

这意味着，如果给出的区间最小值最大值都不在两侧，直接选择左端点右端点和两个最值即可。

如果其中一个或者两个在两侧，那么我们将在一侧的删除，得到长度 $-1$ 或 $-2$ 的区间，进行递归，得到 $\Theta(qn)$ 做法。

考虑这个递归实际上是在干什么：更本质地，我们是找了一个子区间，使其是个“好区间”，并且**以这个子区间的答案为答案**。

我们不难发现，我们可以用 $\Theta(n)$ 个信息描述所有“坏区间”，也就是枚举每个点，钦定这个点是区间的一端且会取到最值，那么区间的另一端必定是区间，可二分得出。

记 $lst_i$ 为极小的位置 $p$ 满足 $\forall p\le l\le i$，都有 $[l,i]$ 是“坏区间”，$nxt_i$ 为极大的 $q$ 满足 $\forall i\le r\le q$，都有 $[i,r]$ 是“坏区间”，则一个区间 $[l,r]$ 成为“好区间”有充要条件：

- $l<lst_r$
- $r>nxt_l$

同时，本题只需要问出一个合法区间而非计数，故对于成包含关系的区间，只需保留更小的即可。那么对于一个 $l$，即可找到最小的 $r$ 满足上述条件，可使用 set 维护之。

得到 $n$ 个关键点对 $(l,r)$ 之后，直接使用主席树维护（事实上选择一个你喜欢的数据结构也可以，无需这么麻烦），第 $i$ 个版本储存所有 $l\le i$ 的 $r$，维护每个 $r$ 最后一次被更新的时间戳（即对应其最大的 $l$），等价于主席树上单点修改和维护区间最大值及位置。至于询问，只需在第 $r$ 个版本上查询区间 $[l,r]$，得到的时间戳若 $\ge l$ 则答案为 $4$，同时可以得到一对好区间。

答案为 $3$ 的情况，注意到如果相邻两数不相同，有用的点对一定形如 $(i,i+1,i+2)$。若存在相同则查找下一个不相同的即可。这部分比较简单。

直接实现总时间复杂度为 $\Theta(n\log n)$。代码比较冗长。

---

2025.05.12 upd: 此处提出上述做法的一个线性改进。仅为口胡，代码没写。如果哪里正确性寄了那我也只能摆了。

首先考虑找 $lst_i,nxt_i$ 部分，这部分完全等价于找每个点前后第一个大于或小于自己的数，可以单调栈线性解决。

接下来需要对“找关键区间”这一步进行优化，直接做似乎是不好优化到线性的。我们需要如下性质：

> 如果存在两个“关键区间”有包含关系，则将更大的删掉正确性仍有保证。
> 
> 证明：如果在一次询问中回答了大区间，那么小区间同样能成为答案。

于是，我们可以将“关键区间”进行缩减，得到一个左端点递增时，右端点也对应递增的“关键区间”集合。

那么，在将 $i$ 从大往小扫以寻找以 $i$ 为左端点的关键区间时，我们实际上并不需要考虑上一个找到的关键区间右侧的点作为右端点，因为即使找到这样的区间也一定没用。其次，如果所有 $i$ 都能恰好找到对应的关键区间使得这样找到的集合已经不存在包含关系，那么我们是可以直接对右端点维护一个指针的，这样这个指针只会从右往左移动 $\Theta(n)$ 次。

问题在于，我们无法保证对于每个点 $i$ 都能恰好在对应区间里找到一个右端点，那么每次暴力扫过去很有可能导致我们并没有更新指针位置，反而反复进行无用的操作，复杂度错误。注意到，我们只需要知道需要查找的区间内存不存在合法的右端点——有，则暴力向后查找，复杂度即双指针线性，正确；没有，则跳过当前 $i$。

于是问题被我们形式化为这样：

> 维护长为 $n$ 的 $01$ 序列，每次将一个 $0$ 改为 $1$，或给定一个区间判断区间和是否为 $0$。要求线性。提前知道所有修改的时间和位置，但是对于询问强制在线。

做一个转化，将 $01$ 序列更改为正整数序列，每个位置是这里从 $0$ 变成 $1$ 的时间戳。我们惊喜地发现，询问就变成了区间 rmq 问题。选择你喜欢的一种 $\Theta(n)-\Theta(1)$ rmq 算法维护即可。

至于回答原题中的询问，比较简单。由于保证了右端点随左端点递增，则每次查询 $\ge l$ 的最小的关键区间即可。答案为 $3$ 的情况同理。

综上，原问题等价于区间 rmq 问题，可做到线性。

---

## 作者：cike_bilibili (赞：0)

## 题意

给定一个序列，多次询问一个区间，要在区间内找到一个最长的子序列，使得这个子序列中没有一个长度为 $3$ 的子序列是不增的或不降的，输出这个最长子序列的长度和下标，不存在则输出 $0$。

## 思路

### 引理

长度为 $n^2 +1$ 的序列中，一定存在长度为 $n+1$ 的不增或不降序列。

### 证明

假设不存在长度为 $n+1$ 的不降子序列。

我们设 $f_i$ 表示由 $a_i$ 开头的最长不降子序列的长度，由假设知，$\forall i \in [1,n^2 +1],f_i \in [1,n]$，所以根据鸽巢原理，一定存在 $n+1$ 个不同的 $i$，$f_i$ 相等。

考虑这些不同的 $n+1$ 个 $i$，不妨记为 $i_1,i_2,\cdots ,i_{n+1}$，如果 $\exists x<y,a_{i_x} \le a_{i_y}$，那么一定有 $f_{i_x} > f_{i_y} $，矛盾，所以一定有 $a_{i_1} > a_{i_2} > \cdots > a_{i_{n+1}}$，则存在一个长度为 $n+1$ 的不升序列，得证。



---

于是我们知道了序列长度大于等于 $5$ 时，一定不合法，所以答案一定在 $0,3,4$ 之中。

如果答案为 $0$，则序列单调不升或不降。

如果答案为 $4$，我们考虑答案的样子，将其离散化后我们发现只要最值在中间两项，左右两项在最值中间就行了，设答案序列为 $b$，我们从右往左扫描线，枚举 $b_1$，由于 $b_2,b_3$ 一定一个大于 $b_1$ 一个小于 $b_1$，所以我们维护一个严格递增的单调栈和严格递减的单调栈，并在递增的单调栈中二分到第一个大于 $b_1$ 的值，在递减的单调栈中二分到第一个小于 $b_1$ 的值，即为 $k_1,k_2$，并在 $[\max\{k1,k2\}+1,n]$ 中找到第一个不在单调栈中的元素 $b_4$，易知这个元素一定能在两个单调栈中找到合法 $b_2,b_3$。

否则答案为 $3$，我们记录每一个位置前一个不一样值的下标和后一个不一样值的下标，判断是不是山谷或山峰，在区间内找到这样的山峰就行了。

---

## 作者：mango2011 (赞：0)

就当是 5k 的大代码了。思路还挺好的，但是但是，这个代码确实是有点恶心了。

观察到题目没有告诉我们如果 $|b|$ 的和很长怎么办，所以猜测不会太长，~~否则全部放最长的一组就 T 掉了~~。

+ $|b|=3$，那么有可能是 $b_1=b_3$ 且 $b_1\not=b_2$，否则两两不同。相对大小关系只有可能是 $132$ 或 $213$ 或 $231$ 或 $312$。这是容易处理的。可以通过枚举 $2$ 的位置，贪心求出 $1/3$ 的位置，因为它们是独立的。这一部分 $O(n\log n)$。
+ $|b|=4$，这个时候任意两个位置都不相等，这是显然的。相对大小关系是 $2143$ 或 $2413$ 或 $3142$ 或 $3412$。这相当于两边的数大小关系处于中间，又等价于两侧的数至少有一个比它大，至少有一个比它小。对于 $i$，维护 $x_i$ 表示 $i$ 右侧第一个大于 $i$、小于 $i$ 的位置中较大的那个；$y_i$ 为左侧的。那么，就必须要满足 $x_i\le j$ 且 $i\le y_j$（$i<j$）。并且容易发现 $a_i=a_j$ 显然是不优的，所以可以排除这种情况。考虑固定 $j$，那么可以按照 $x_i$ 从小到大的顺序把这些下标扔进一个集合，支持查询就好了（对于一个 $j$，只有最大的 $i$ 是有意义的）。所以，这里的复杂度也是 $O(n\log n)$。
+ $|b|\ge5$，手搓一下，容易发现这是不可能的。

综上，我们在 $O(n\log n+q)$ 的时间复杂度内解决了问题。代码太长了，就扔一个提交记录。

[提交记录](https://codeforces.com/contest/1332/submission/316490187)

---

## 作者：tzc_wk (赞：0)

[Codeforces 题目传送门](https://codeforces.com/contest/1332/problem/G) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF1332G)

首先~~打表~~即可发现对于任意长度 $\ge 5$ 的序列总存在一个 Monotone triple，证明~~不会~~实在不行直接 $5^5$ 枚举相对位置大小都可以发现，因此答案要么是 $0$，要么是 $3$，要么是 $4$，我们考虑对三种情况分别分类讨论，即检查区间内是否存在长度为 $3$ 的 Monotone triple free 的子序列，再检查区间内是否存在长度为 $4$ 的 Monotone triple free 的子序列，这样即可确定答案。

因此我们可以大致将题目分为两个部分：

### 1. 检验区间中是否存在长度为 $3$ 的 Monotone triple free 的子序列

首先显然三个位置 $i,j,k(i<j<k)$ 能够构成 Monotone triple free 的序列当且仅当中间位置的值**严格小于**边上两个数的值，或者中间位置的值**严格大于**边上两个数的值。

考虑枚举中间位置 $p$，我们贪心地想，我们希望这三个位置都在区间 $[l,r]$ 中，因此边上两个位置肯定离中间位置越紧凑越好，因此我们可以先预处理出四个数组：$mxl_i$ 表示在 $i$ 前面且大于 $a_i$ 的离 $i$ 最近的位置，$mxr_i$ 表示在 $i$ 后面且大于 $a_i$ 的离 $i$ 最近的位置，$mnl_i,mnr_i$ 也可以类似地定义，单调栈可以求出。那么对于以 $p$ 为中心的长度为 $3$ 的序列，$(mnl_p,p,mnr_p),(mxl_p,p,mxr_p)$ 必然都是的 Monotone triple free 的序列，并且这两个序列分别是上述两种情况中最紧凑的序列——如果它们都不能包含在 $[l,r]$ 中那么所有以 $p$ 为中心的长度为 $3$ 的 Monotone triple free 序列肯定都不能包含在 $[l,r]$ 中了。

因此题目转化为，是否 $\exists p\in[l,r]$ 满足 $mnl_p\ge l,mnr_p\le r$ 或者 $mxl_p\ge l,mxr_p\le r$。考虑一个离线做法，我们将所有询问都挂在 $l$ 处，然后开一个指针 $i$ 从右到左扫描，再建立一棵线段树，每次当指针从 $i+1$ 变到 $i$ 时都枚举所有 $mnl_p=i$ 的 $p$ 并用 $mnr_p$ 更新线段树上 $p$ 位置上的值，$mxl$ 也同理，回答询问时只需检验线段树上 $[l,r]$ 位置上的最小值是否 $\le r$ 即可，输出方案只需再记录一个取到最小值的位置再稍微分下类即可。

时间复杂度 $n\log n$

### 2. 检验区间中是否存在长度为 $4$ 的 Monotone triple free 的子序列

这个看起来有亿点点棘手，因此我们先来挖掘下性质，对于一个长度为 $4$ 的序列而言，如果它的最大值不唯一那肯定不合法——如果这两个最大值有一个在中间两个位置就肯定存在一个三元组满足左边两个数或右边两个数相同，否则不论中间两个数大小关系如何也都会存在 monotone triple。因此这四个数只能有唯一的最大值和最小值，而如果这唯一的最大值/最小值在两边，不妨以最大值在第一个位置为例，如果后三个数存在逆序对那这个最大值与这个逆序对就存在 monotone triple，否则这三个数就构成了 monotone triple，因此四个数构成 Monotone triple free 序列的充要条件是：存在唯一的最大/小值，并且最大/小值分别在第二、三个位置。

我们考虑固定第一、四个位置 $i,l$，那么我们肯定会选择区间 $(i,l)$ 的最大值&最小值作为第二、三个位置，即存在合法的序列当且仅当区间 $(i,l)$ 的最大值 $>\max(a_i,a_l)$，且最小值 $<\min(a_i,a_l)$，直接枚举肯定行不通。我们考虑预处理 $r3_i$ 表示最小的 $r$ 满足 $(i,r]$ 最大值 $>a_i$ 且最小值 $<a_i$，$l3_i$ 表示最大的 $l$ 满足 $[l,i)$ 最大值 $>a_i$ 且最小值 $<a_i$，这个可以二分+ST 表，也可以直接调用上面求出的 $mnl_i,mnr_i,mxl_i,mxr_i$，那么当我们固定住 $i$ 之后，合法的 $l$ 必须 $>r3_i$，并且 $l3_l>i$。

我们再求出 $r4_i$ 表示最小的 $l$ 满足 $l>r3_i,l3_l>i$，这个可以通过对 $l3$ 数组建 ST 表之后二分求出，那么 $i,r4_i$ 恰好分别对应一个长度为 $4$ 的 Monotone triple free 序列的 $i,l$，并且这肯定是以 $i$ 为第一个元素的最后一个位置下标最小的合法序列，因此对于每个询问我们需检验是否存在一个 $i\in[l,r]$ 满足 $r4_i\le r$，这个可以再对 $r4$ 建 ST 表求出。最后输出方案可以维护一个取到最小值的位置求出边上两个元素，再根据这两个位置之间最大值、最小值的位置求出中间两个元素。

时间复杂度 $n\log n$。

~~那么问题就来了，为什么求长度为 $3$ 的序列时离线了，求长度为 $4$ 的序列时反而没有离线呢~~

```cpp
const int MAXN=2e5;
const int LOG_N=17;
const int INF=0x3f3f3f3f;
int n,qu,a[MAXN+5],L[MAXN+5],R[MAXN+5];
vector<pii> ql[MAXN+5];
int mnl[MAXN+5],mxl[MAXN+5],mnr[MAXN+5],mxr[MAXN+5];
namespace solve3{
	vector<pii> pl[MAXN+5];
	tuple<int,int,int> ans[MAXN+5];
	struct node{int l,r;pii val;} s[MAXN*4+5];
	pii merge(pii x,pii y){
		pii ret;ret.fi=min(x.fi,y.fi);
		if(ret.fi==x.fi) ret.se=x.se;
		else ret.se=y.se;
		return ret;
	}
	void pushup(int k){s[k].val=merge(s[k<<1].val,s[k<<1|1].val);}
	void build(int k,int l,int r){
		s[k].l=l;s[k].r=r;if(l==r){s[k].val=mp(INF,l);return;}
		int mid=l+r>>1;build(k<<1,l,mid);build(k<<1|1,mid+1,r);pushup(k);
	}
	void modify(int k,int x,int v){
		if(s[k].l==s[k].r) return chkmin(s[k].val.fi,v),void();
		int mid=s[k].l+s[k].r>>1;
		(x<=mid)?modify(k<<1,x,v):modify(k<<1|1,x,v);
		pushup(k);
	}
	pii query(int k,int l,int r){
		if(l<=s[k].l&&s[k].r<=r) return s[k].val;
		int mid=s[k].l+s[k].r>>1;
		if(r<=mid) return query(k<<1,l,r);
		else if(l>mid) return query(k<<1|1,l,r);
		else return merge(query(k<<1,l,mid),query(k<<1|1,mid+1,r));
	}
	void solve(){
		build(1,1,n);
		for(int i=1;i<=n;i++) pl[mxl[i]].pb(mp(i,mxr[i]));
		for(int i=1;i<=n;i++) pl[mnl[i]].pb(mp(i,mnr[i]));
//		for(int i=1;i<=n;i++) printf("%d %d %d %d\n",mnl[i],mxl[i],mnr[i],mxr[i]);
		for(int i=n;i;i--){
			for(pii p:pl[i]) modify(1,p.fi,p.se);
			for(pii p:ql[i]){
				int x=p.fi,id=p.se;
				pii mn=query(1,i,x);
				if(mn.fi<=x){
					int pos=mn.se;
					if(mnl[pos]>=i&&mnr[pos]<=x) ans[id]=make_tuple(mnl[pos],pos,mnr[pos]);
					if(mxl[pos]>=i&&mxr[pos]<=x) ans[id]=make_tuple(mxl[pos],pos,mxr[pos]);
				}
			}
		}
	}
}
namespace solve4{
	template<typename T> struct st_table{
		T v[MAXN+5][LOG_N+2];int op;
		void build(){
			for(int i=1;i<=LOG_N;i++) for(int j=1;j+(1<<i)-1<=n;j++)
				v[j][i]=(op)?max(v[j][i-1],v[j+(1<<i-1)][i-1]):min(v[j][i-1],v[j+(1<<i-1)][i-1]);
		}
		T query(int l,int r){
			int k=31-__builtin_clz(r-l+1);
			return (op)?max(v[l][k],v[r-(1<<k)+1][k]):min(v[l][k],v[r-(1<<k)+1][k]);
		}
	};
	st_table<int> st3;
	st_table<pii> mn,mx,st4;
	int l3[MAXN+5],r3[MAXN+5],r4[MAXN+5];
	tuple<int,int,int,int> ans[MAXN+5];
	void solve(){
		mx.op=st3.op=1;
		for(int i=1;i<=n;i++) mn.v[i][0]=mx.v[i][0]=mp(a[i],i);
		mn.build();mx.build();
		for(int i=1;i<=n;i++){
			r3[i]=max(mxr[i],mnr[i]);
			l3[i]=min(mxl[i],mnl[i]);
			st3.v[i][0]=l3[i];
		} st3.build();
		for(int i=1;i<=n;i++){
			int l=r3[i]+1,r=n,p=n+1;
			while(l<=r){
				int mid=l+r>>1;
				if(st3.query(r3[i]+1,mid)>i) p=mid,r=mid-1;
				else l=mid+1;
			} r4[i]=p;st4.v[i][0]=mp(r4[i],i);
//			printf("%d\n",r4[i]);
		} st4.build();
		for(int i=1;i<=qu;i++){
			pii p=st4.query(L[i],R[i]);
//			printf("%d\n",p.fi);
			if(p.fi<=R[i]){
				int i1=p.se,i4=p.fi;
				int i2=mn.query(i1,i4).se,i3=mx.query(i1,i4).se;
				if(i2>i3) i2^=i3^=i2^=i3;
//				printf("%d %d %d %d\n",i1,i2,i3,i4);
				ans[i]=make_tuple(i1,i2,i3,i4);
			}
		}
	}
}
int main(){
	scanf("%d%d",&n,&qu);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	stack<int> stk;
	for(int i=1;i<=n;i++){
		while(!stk.empty()&&a[stk.top()]<=a[i]) stk.pop();
		mxl[i]=((stk.empty())?0:stk.top());stk.push(i);
	} while(!stk.empty()) stk.pop();
	for(int i=1;i<=n;i++){
		while(!stk.empty()&&a[stk.top()]>=a[i]) stk.pop();
		mnl[i]=((stk.empty())?0:stk.top());stk.push(i);
	} while(!stk.empty()) stk.pop();
	for(int i=n;i;i--){
		while(!stk.empty()&&a[stk.top()]<=a[i]) stk.pop();
		mxr[i]=((stk.empty())?n+1:stk.top());stk.push(i);
	} while(!stk.empty()) stk.pop();
	for(int i=n;i;i--){
		while(!stk.empty()&&a[stk.top()]>=a[i]) stk.pop();
		mnr[i]=((stk.empty())?n+1:stk.top());stk.push(i);
	} while(!stk.empty()) stk.pop();
	for(int i=1;i<=qu;i++) scanf("%d%d",&L[i],&R[i]),ql[L[i]].pb(mp(R[i],i));
	solve3::solve();solve4::solve();
	for(int i=1;i<=qu;i++){
		if(!get<0>(solve3::ans[i])) printf("0\n");
		else if(!get<0>(solve4::ans[i]))
			printf("3\n%d %d %d\n",get<0>(solve3::ans[i]),get<1>(solve3::ans[i]),get<2>(solve3::ans[i]));
		else printf("4\n%d %d %d %d\n",get<0>(solve4::ans[i]),get<1>(solve4::ans[i]),get<2>(solve4::ans[i]),get<3>(solve4::ans[i]));
	}
	return 0;
}
```



---

