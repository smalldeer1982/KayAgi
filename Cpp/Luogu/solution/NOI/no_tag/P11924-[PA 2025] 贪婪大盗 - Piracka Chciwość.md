# [PA 2025] 贪婪大盗 / Piracka Chciwość

## 题目背景


PA 2025 R4A.

$\textcolor{red}{\textbf{1G / 6s.}}$

## 题目描述

有 $n$ 名海盗，编号 $1\sim n$。海盗编号越小，他的地位越高。

每位海盗 $i$ 都有一个贪婪系数 $a_i$，为正整数。

他们获得了 $m$ 枚金币，现在要分金币。

分金币的方式如下：

- **船上**编号最小的海盗提出一个分赃方案，即为每个**船上**的海盗 $i$ 分配 $b_i$ 枚金币。这里，$\sum b_i=m$。
- 然后，所有**船上**的海盗（包括提出方案的海盗）对该分赃方案投票，选择支持或反对。  
	- 如果**至少 $50\%$** 的海盗支持方案，则金币按照提议的方式分配。
	- 否则，提出方案的海盗被**扔下船**（他不再参与接下来的讨论，也无法获得任何金币）。随后，由仍在船上的编号最小的海盗重复上述过程，直到确定一种分配方式为止。
    
    
每个海盗 $ i $ 选择支持该分赃方案，当且仅当，如果拒绝方案：

- 他最终会被扔下船（他提出自己的方案后会被否决）；
- 或者他在该方案中的收益 $ b_i $ 满足 $b_i \geq d_i + a_i$，其中 
  
  - $ d_i $ 是当前方案被否决后，该海盗最终获得的金币数；
  - $ a_i $ 是贪婪系数。

**所有海盗都知道所有其他海盗的贪婪系数**，每个人的策略都是固定的：

1. 如果提出方案的海盗无论如何都会被扔下船（不存在一个方案可接受）：
	- 该海盗提议自己独占所有金币，接受自己的命运，被扔下船。
2. 否则，存在至少一个可接受的方案。
	- 该海盗会选择提出其中一个方案（$0$ 金币也比被扔下船好）。
	- 在所有可接受的方案中，海盗会选择自己分得最多金币的方案；
	- 如果仍然有多个可接受方案，海盗更倾向于让编号较大的海盗获得更多金币。  
    
   		具体地说，编号为 $ i $ 的海盗，在所有可接受方案中，最小化编号 $ i+1 $ 的海盗所获金币数。
   		- 如果仍然有多个方案，则最小化编号 $ i+2 $ 的海盗所得金币数，依此类推。
   
求出最终每个海盗能够分得多少金币。

## 说明/提示


### 样例解释

- 样例解释 $1$：
 
 如果海盗 $1$ 被扔下船，那么海盗 $2$ 会独占所有金币（虽然海盗 $3$ 会投反对票，但是无济于事）。
    
因此，海盗 $1$ 无法说服海盗 $2$ 支持他的方案，除非他给海盗 $2$ 至少 $100 + 1 = 101$ 枚金币（这超出了总金币数）。 
        
从而，海盗 $1$ 选择转而说服海盗 $3$，即给他足够多的金币，使他愿意支持该方案。海盗 $1$ 需要至少给海盗 $3$ $56$ 枚金币。

所以最终方案为：$b_1=44$，$b_2=0$，$b_3=56$。

在该方案下，海盗 $1,3$ 投下反对票，海盗 $2$ 无力回天。

- 样例解释 $2$：

对于海盗 $1$，金币无论如何都不够分，所以他被扔下船。

海盗 $2$ 有两个选择：

1. 将 $1$ 枚金币给海盗 $3$；
2. 将 $1$ 枚金币给海盗 $4$。

按照规则，他选择方案 $2$。

- 样例解释 $3$：海盗 $1,2,5$ 支持海盗 $1$ 的方案，所以方案成功通过。

### 数据范围

- $1 \leq n \leq 5\times 10^4$；
- $1 \leq m \leq 5\times 10^6$；
- $1\le a_i\le 64$。


## 样例 #1

### 输入

```
3 100
28 1 56```

### 输出

```
44 0 56```

## 样例 #2

### 输入

```
5 1
1 1 1 1 1```

### 输出

```
-1 0 0 1 0```

## 样例 #3

### 输入

```
6 6
3 5 1 4 2 6```

### 输出

```
2 0 0 0 4 0```

# 题解

## 作者：lalaouye (赞：2)

首先 $\mathcal{O}(n^2\log n)$ 是简单的，直接从后往前按题意模拟即可。

注意到 $\max\{a_i\}$ 只有 $64$，我们能看出来什么呢？首先我以为是根据小差距去暴力维护某些东西，但我还是见的太少了。

我们发现每次只会选其中一半数给它投票，那么说明一次结果只有一般的人给了钱。那么说明给的钱最多也只有 $64$，因为下一个人完全可以选择另一半！这样我们就可以加速模拟过程了，我们需要每个数当前的钱数，然后用 $a_i$ 在分一次类，即设 $S_{i,j}$ 表示所有满足 $b_u=i,a_u=j$ 的 $u$ 组成的集合。

每次从小到大枚举 $k$，即给的钱数，然后将要给这么多钱的人更新，但是这题非常恶心，要求找到编号更大的，考虑使用动态开点线段树，那么我们在第一次总数超过所需数的 $k$ 通过二分的方式找到 $mid$ 使得当前所有编号大于等于 $mid$ 的数刚好凑够所需要的点数。

维护时需要线段树合并和线段树分裂，时间复杂度 $\mathcal{O}(na^2\log n)$，实际跑的挺快。

代码：


```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i (l); i <= (r); ++ i)
#define rrp(i, l, r) for (int i (r); i >= (l); -- i)
#define eb emplace_back
using namespace std;
#define pii pair <int, int>
#define inf 1000000000
#define ls (p << 1)
#define rs (ls | 1)
constexpr int N = 5e4 + 5, M = 1e6;
typedef long long ll;
typedef unsigned long long ull;
inline int rd () {
  int x = 0, f = 1;
  char ch = getchar ();
  while (! isdigit (ch)) {
    if (ch == '-') f = -1;
    ch = getchar ();
  }
  while (isdigit (ch)) {
    x = (x << 1) + (x << 3) + (ch ^ 48);
    ch = getchar ();
  }
  return x * f;
}
int n, m;
int a[N], b[N];
// vector <int> vc[65][65], die;
int rt[65][65], die[65];
int sum[N << 7], lc[N << 7], rc[N << 7], tot;
void psu (int p) {
  sum[p] = sum[lc[p]] + sum[rc[p]];
}
void upd (int &p, int l, int r, int x) {
  if (! p) p = ++ tot;
  if (l == r) return ++ sum[p], void ();
  int mid (l + r >> 1);
  if (x <= mid) upd (lc[p], l, mid, x);
  else upd (rc[p], mid + 1, r, x);
  psu (p);
}
void merge (int &x, int y) {
  if (! x || ! y) return void (x |= y);
  merge (lc[x], lc[y]);
  merge (rc[x], rc[y]);
  psu (x);
}
void split (int p1, int &p2, int l, int r, int x) {
  if (! p1) return ;
  if (l == r) return ;
  if (! p2) p2 = ++ tot;
  int mid (l + r >> 1);
  if (x <= mid) {
    swap (rc[p1], rc[p2]);
    split (lc[p1], lc[p2], l, mid, x);
  } else {
    split (rc[p1], rc[p2], mid + 1, r, x);
  }
  psu (p1), psu (p2);
}
int R[65];
int solve (int l, int r, int nd) {
  if (l == r) return l;
  int mid (l + r >> 1);
  int s (0);
  rep (i, 0, 64) s += sum[rc[R[i]]];
  if (s >= nd) {
    rep (i, 0, 64) R[i] = rc[R[i]];
    return solve (mid + 1, r, nd);
  }
  else {
    rep (i, 0, 64) R[i] = lc[R[i]];
    return solve (l, mid, nd - s);
  }
}
void dfs (int p, int l, int r, int k) {
  if (l == r && sum[p]) {
    return b[l] = k, void ();
  }
  int mid (l + r >> 1);
  if (sum[lc[p]]) dfs (lc[p], l, mid, k);
  if (sum[rc[p]]) dfs (rc[p], mid + 1, r, k); 
}
int32_t main () {
  // freopen ("1.in", "r", stdin);
  // freopen ("1.out", "w", stdout);
  n = rd (), m = rd ();
  rep (i, 1, n) a[i] = rd ();
  int nxt (n);
  rrp (i, 1, n - 1) {
    int len (n - i + 1);
    int cnt = 1;
    rep (i, 0, 64) cnt += sum[die[i]];
    if (cnt * 2 >= len) {
      rep (i, 1, 64) rep (j, 0, 64) {
        merge (rt[0][j], rt[i][j]); rt[i][j] = 0;
      } 
      upd (rt[0][a[nxt]], 1, n, nxt);
      rep (j, 1, 64) merge (rt[0][j], die[j]), die[j] = 0;
      b[i] = m; nxt = i;
    } else {
      int s1 (0);
      rep (k, 0, 64) {
        int now (0);
        if (b[nxt] + a[nxt] == k) ++ now;
        rep (j, 0, k) {
          now += sum[rt[j][k - j]];
        } 
        if ((cnt + now) * 2 < len) s1 += now * k, cnt += now;
        else {
          int ln = now;
          now = (len - cnt * 2 + 1) / 2;
          s1 += now * k; 
          cnt += now;
          if (s1 > m) break;
          int ret;
          if ((cnt + ln - now) * 2 <= len + 1) ret = nxt;
          else {
            memset (R, 0, sizeof R);
            rep (j, 0, k) R[j] = rt[j][k - j];
            ret = solve (1, n, now);
          }
          int tmp[65]; memset (tmp, 0, sizeof tmp);
          rep (i, 0, 64) {
            rep (j, 0, 64) {
              if (i + j > k) {
                merge (tmp[j], rt[i][j]); rt[i][j] = 0;
              } else {
                if (i + j == k) {
                  int lef (rt[i][j]);
                  int all = sum[lef];
                  rt[i][j] = 0;
                  split (lef, rt[i][j], 1, n, ret - 1);
                  assert (sum[lef] + sum[rt[i][j]] == all);
                  all = sum[tmp[j]] + sum[lef];
                  merge (tmp[j], lef);
                  assert (all == sum[tmp[j]]);
                }
              }              
            }
          }
          rrp (i, 0, 64) {
            rrp (j, 0, 64) {
              merge (rt[i + j][j], rt[i][j]);
              rt[i][j] = 0;
            }
          }
          rep (i, 0, 64) merge (rt[0][i], tmp[i]);
          if (a[nxt] + b[nxt] < k) upd (rt[a[nxt] + b[nxt]][a[nxt]], 1, n, nxt);
          else if (a[nxt] + b[nxt] == k && ret == nxt) upd (rt[a[nxt] + b[nxt]][a[nxt]], 1, n, nxt);
          else {
            upd (rt[0][a[nxt]], 1, n, nxt);
          }
          b[i] = m - s1;
          nxt = i;
          rep (i, 0, 64) merge (rt[0][i], die[i]), die[i] = 0;
          break;
        }
      }
      if (s1 > m) upd (die[a[i]], 1, n, i);
    }
  }
  rep (i, 1, 64) dfs (die[i], 1, n, -1);
  rep (i, 0, 64) rep (j, 0, 64) dfs (rt[i][j], 1, n, i);
  rep (i, 1, n) printf ("%d ", b[i]);
}
```

---

## 作者：WrongAnswer_90 (赞：2)

遗憾离场。看上去像个分析性质题，实际上比较暴力。

首先暴力从后向前模拟，维护 $f_i$ 表示当前想让这个人同意的话，需要分给他 $f_i$ 个金币。显然从小到大选，复杂度是 $\mathcal O(n^2\log n)$。

核心性质是每个人分得的钱数一定不会超过 $\max(a)$（记为 $w$）。证明就是在 $i\rightarrow i-1$ 的时候，令 $S_{i-1}=[i-1,n]\setminus S_i$ 一定合法。

所以用线段树维护集合 $A_{i,j}$ 表示如果当前想让他同意，需要花费 $i$ 个金币，贪婪值等于 $j$ 的点的位置集合。

处理到 $i$ 的时候，从小到大枚举金币数量，什么时候需要的总和大于 $m$ 了或者人数合法了就停下。然后很讨厌的限制是金币相同的话编号从大到小选，所以确定了给出的最大金币数 $k$ 后，$<k$ 的所有人都要选，然后所有 $=k$ 的人选的是一段后缀。所以在所有 $A_{k,\ast}$ 上同时进行一个线段树二分，即可找出需要的区间。

这样操作就是，对于不选的人，金币数全部归零，然后所有人的金币数都加上各自贪婪值。这里会发生若干合并和分裂，需要线段树合并和分裂实现。这样是 $\mathcal O(na^2\log n)$ 左右。

注意到一个人清零之后，金币数就一定是他自己贪婪值的倍数，所以对于还没被清零过的数暴力处理（一个人最多被暴力处理 $256/a$ 次），然后需要维护的线段树棵数是 $\mathcal O(a\log a)$ 级别的。这样复杂度可以优化到 $\mathcal O(n(a\log a+d(a)\log n))$，实际远远跑不满。

---

## 作者：Otomachi_Una_ (赞：0)

假设 $f_{i,j}$ 表示只考虑最后 $i$ 个海盗分赃，第 $j$ 个海盗分到的金币数量。如果被丢下水了就是 $-1$。考虑从 $f_{i+1}$ 转移到 $f_i$。

考虑计算 $g_j=\begin{cases}0&f_{i+1,j}=-1\\f_{i+1,j}+a_j&f_{i+1,j}\geq 0\end{cases}$，然后取 $g$ 的前 $\dfrac{n-i}{2}$ 小（$g$ 相同 $j$ 大的优先）满足其条件，其余的设为 $0$ 即可。

至此我们有了 $O(n^2\log n)$ 的做法。但是我们没有用上 $a_i\leq 64$ 这个条件。

我们感性理解一下，$f_{i,j}$（$j>i$）的值大部分不会太大，具体地不会超过 $64$。如果两个人 $p,q$ 满足 $f_{i,p}=f_{i,q}$ 且 $a_p=a_q$，那么他们的转移是非常类似的。

我们用线段树维护所有 $f,a$ 相等的等价类（这样的等价类数目是 $O(V\log V)$）的。然后每次转移对每个等价类而言，要么是整体都选上，此时 $f\leftarrow f+a$。要么是整体都不选，此时 $f\leftarrow 0$。要么是选了一个后缀，这时线段树分裂一下就行。

---

