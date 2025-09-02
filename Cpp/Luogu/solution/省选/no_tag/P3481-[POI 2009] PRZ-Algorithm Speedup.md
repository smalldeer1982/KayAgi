# [POI 2009] PRZ-Algorithm Speedup

## 题目描述

由于行为不端，Byteasar 被要求计算一个神秘且棘手的布尔值函数 $F(x,y)$，该函数定义在一对正整数序列 $x=(x_1,x_2,\cdots,x_n)$ 和 $y=(y_1,y_2,\cdots,y_n)$ 上，如下所示：

- 布尔函数 $F(x, y)$
- 如果 $W(x)
eq W(y)$ 则返回 $0$
- 否则如果 $|W(x)|=|W(y)|=1$ 则返回 $1$
- 否则返回 $F(p(x), p(y)) \wedge F(s(x), s(y))$。

其中：

- $W(x)$ 表示序列 $x$ 的成员集合（元素的顺序和重复无关紧要），
- $p(x)$ 表示序列 $x$ 的最长前缀（任意长度的初始部分），使得 $W(x)
eq W(p(x))$，
- $s(x)$ 表示序列 $x$ 的最长后缀（任意长度的末尾部分），使得 $W(x)
eq W(s(x))$，
- $\wedge$ 表示逻辑与，1 表示真，0 表示假，$|z|$ 表示集合 $z$ 的基数。

例如，对于序列 $x=(2,3,7,2,7,4,7,2,4)$，我们有：$W(x)=\{2,3,4,7\}$，$p(x)=(2,3,7,2,7)$，$s(x)=(7,2,7,4,7,2,4)$。对于非常大的数据，直接从定义计算函数 $F$ 的值的程序速度太慢。因此，你需要尽可能快地进行这些计算。

编写一个程序，从标准输入读取若干对序列 $(x,y)$，并在标准输出中打印每个输入对的 $F(x,y)$ 值。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
2
4 5
3 1 2 1
1 3 1 2 1
7 7
1 1 2 1 2 1 3
1 1 2 1 3 1 3
```

### 输出

```
0
1
```

# 题解

## 作者：kczno1 (赞：7)

用p(l,r)表示区间[l,r]的最长前缀的右端点，

s(l,r)表示后缀的左端点。

用hash(l,r)表示区间[l,r]的状态。

那么hash(l,r)必须包含hash(l,p(l,r)),hash(s(l,r),r),以及W(l,r)。

考虑到hash(s(l,r),r)已经包含W(s(l,r),r)的状态，

我们只用新加入(s(l,r),r)少掉的那个状态即可。

假设包含x个元素。

那么p(l,r)就是以l为左端点，包含了x-1个元素且右边是第x个元素的右端点。

s(l,r)同理。

所以就可以dp了。

由于数字范围是[1,100],所以最多只有n\*100个状态。

再滚动数组优化空间即可。


---

## 作者：JCY_ (赞：3)

[更好的阅读体验](https://www.cnblogs.com/JCY-std/p/17815520.html)

# 题目描述

你需要计算一个函数 $F(x, y)$，其中 $x, y$ 是两个正整数序列。

```cpp
bool F(std::vector<int> x, std::vector<int> y) {
  if (W(x).size() != W(y).size()) return false;
  if (W(x).size() == 1) return true;
  return F(p(x), p(y)) && F(s(x), s(y));
}
```

$W(x)$ 表示序列 $x$ 的不同元素组成的集合。

$p(x)$ 表示序列 $x$ 的最长前缀满足 $W(p(x)) \neq W(x)$。

$s(x)$ 表示序列 $x$ 的最长后缀满足 $W(s(x)) \neq W(x)$。

# 输入格式

第一行一个正整数 $T$ 表示数据组数。

对于每组数据：

第一行两个正整数 $n, m$ 分别表示序列 $x$ 的长度和序列 $y$ 的长度。

第二行 $n$ 个正整数，其中第 $i$ 个表示 $x_i$。

第三行 $m$ 个正整数，其中第 $i$ 个表示 $y_i$。

# 输出格式

输出 $T$ 行，对于每组数据，若 $F(x, y)$ 为真输出 $1$，否则输出 $0$。

# 数据范围

$1 \le T \le 13$，$1 \le n, m \le 10^5$，$1 \le x_i, y_i \le 100$。

# 题解

下文中用 $x[l.. r]$ 表示序列 $x$ 的第 $l$ 个元素到第 $r$ 个元素组成的子串。

考察 $x, y$ 中的哪些子串会在计算 $F(x, y)$ 的过程中会被遍历到。

以 $x$ 为例，被遍历到的子串 $x[l.. r]$ 必然满足 $(l = 1 \lor x_{l - 1} \not \in x[l.. r]) \land (r = n \lor x_{r + 1} \not \in x[l.. r])$。

容易发现当 $|W(x[l..r])|$ 固定时，只有不超过 $n$ 个子串会被遍历到，因此总子串个数不超过 $n \max x_i$。

> 当 $|W(x[l..r])|$ 固定时，枚举 $r$，不难发现只有至多一个 $l$ 满足 $l = 1 \lor x_{l - 1} \not \in x[l..r]$，因此有不超过 $n$ 个会被遍历到的子串。

不难对 $|W(x)|$ 归纳证明 $F(x, y) \land F(y, z) \rightarrow F(x, z)$，因此 $F$ 代表一个等价关系。

[kczno1 的题解](https://www.luogu.com.cn/blog/kczno1/solution-p3481) 就此给出了哈希的思路：

既然是等价关系，考虑设计哈希函数 $h(x)$，使得 $F(x, y) \approx [h(x) = h(y)]$。

$h(x)$ 需要包含 $h(p(x)), h(s(x)), W(x)$ 这三个信息。由于 $h(s(x))$ 已经包含了 $W(s(x))$，因此 $h(x)$ 所需要包含的 $W(x)$ 可以简化为大小为 $1$ 的集合 $W(x) - W(s(x))$。

按 $|W(x[l..r])|$ 从小到大转移，该算法可以做到时间复杂度 $O(n \max x_i)$。

但毛估估一下这相当于哈希一个长度为指数级的序列，正确率堪忧，也确实无法通过。

[POI 官解](https://www.oi.edu.pl/static/attachment/20110704/oi16.pdf) 的做法类似后缀数组的倍增求法，对 $x, y$ 可能遍历到的子串按照 $W$ 分层从小到大进行正整数哈希。

这个做法基于每一层的哈希函数的求解只会依赖上一层的哈希函数的事实。

$h(x[l..r])$ 相当于正整数三元组 $(h(p(x)), h(s(x)), W(x) - W(s(x)))$，我们把同层的 $x, y$ 的子串对应的三元组取出，用基数排序进行离散化，把三元组变为正整数。

时间复杂度 $O(n \max x_i)$，并且没有正确率问题。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using i128 = __int128;
using u128 = unsigned __int128;
template <typename T>
void chkmax(T &x, const T &y) {
  if (x < y) x = y;
}
template <typename T>
void chkmin(T &x, const T &y) {
  if (y < x) x = y;
}
constexpr int MAXN = 1e5 + 10, MAXVAL = 105;
int n[2], a[2][MAXN], dpl[2][2][MAXN], dpr[2][2][MAXN], p, sz, tp;
tuple<int, int, int, int *, int *> stk[MAXN * 2];
void ins(int t, int k) {
  static int cnt[MAXVAL], num;
  num = 0;
  memset(cnt, 0, sizeof(cnt));
  for (int i = 1, j = 1; i <= n[t]; ++i) {
    num += !(cnt[a[t][i]]++);
    while (num > k) num -= !(--cnt[a[t][j++]]);
    if (num == k && (i == n[t] || !cnt[a[t][i + 1]])) {
      stk[++tp] = {dpr[!p][t][j], dpl[!p][t][i], 0, &dpr[p][t][j],
                   &dpl[p][t][i]};
      while (num == k) num -= !(--cnt[a[t][j++]]);
      get<2>(stk[tp]) = a[t][j - 1];
    }
  }
}
void rsort() {
  static int buc[MAXN * 2], ord[MAXN * 2], tord[MAXN * 2];
  fill(buc + 1, buc + MAXVAL, 0);
  for (int i = 1; i <= tp; ++i) ++buc[get<2>(stk[i])];
  for (int i = 2; i < MAXVAL; ++i) buc[i] += buc[i - 1];
  for (int i = 1; i <= tp; ++i) ord[buc[get<2>(stk[i])]--] = i;
  fill(buc + 1, buc + sz + 1, 0);
  for (int i = 1; i <= tp; ++i) ++buc[get<1>(stk[i])];
  for (int i = 2; i <= sz; ++i) buc[i] += buc[i - 1];
  for (int i = tp; i >= 1; --i) tord[buc[get<1>(stk[ord[i]])]--] = ord[i];
  fill(buc + 1, buc + sz + 1, 0);
  for (int i = 1; i <= tp; ++i) ++buc[get<0>(stk[i])];
  for (int i = 2; i <= sz; ++i) buc[i] += buc[i - 1];
  for (int i = tp; i >= 1; --i) ord[buc[get<0>(stk[tord[i]])]--] = tord[i];
  *get<3>(stk[ord[1]]) = *get<4>(stk[ord[1]]) = sz = 1;
  for (int i = 2; i <= tp; ++i) {
    *get<3>(stk[ord[i]]) = *get<4>(stk[ord[i]]) =
        (get<0>(stk[ord[i]]) == get<0>(stk[ord[i - 1]]) &&
                 get<1>(stk[ord[i]]) == get<1>(stk[ord[i - 1]]) &&
                 get<2>(stk[ord[i]]) == get<2>(stk[ord[i - 1]])
             ? sz
             : ++sz);
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int cas;
  cin >> cas;
  while (cas--) {
    cin >> n[0] >> n[1];
    static int cnt[2][MAXVAL];
    memset(cnt, 0, sizeof(cnt));
    for (int t = 0; t < 2; ++t) {
      for (int i = 1; i <= n[t]; ++i) {
        cin >> a[t][i];
        ++cnt[t][a[t][i]];
      }
    }
    if (!equal(cnt[0], cnt[0] + MAXVAL, cnt[1],
               [](int x, int y) { return (bool)x == (bool)y; })) {
      cout << "0\n";
      continue;
    }
    int num = count_if(cnt[0], cnt[0] + MAXVAL, [](int x) { return x; });
    if (num == 1) {
      cout << "1\n";
      continue;
    }
    for (int t = 0; t < 2; ++t) {
      copy(a[t] + 1, a[t] + n[t] + 1, dpl[0][t] + 1);
      copy(a[t] + 1, a[t] + n[t] + 1, dpr[0][t] + 1);
    }
    sz = MAXVAL - 1;
    p = 0;
    for (int k = 2; k <= num; ++k) {
      p ^= 1;
      tp = 0;
      ins(0, k);
      ins(1, k);
      memset(dpl[p], 0, sizeof(dpl[p]));
      memset(dpr[p], 0, sizeof(dpr[p]));
      rsort();
    }
    cout << (dpr[p][0][1] == dpr[p][1][1]) << "\n";
  }
  return 0;
}
/*
g++ PRZ.cpp -o PRZ -std=c++14 -O2 -Wall -Wextra -Wshadow -g
-fsanitize=address,undefined
*/
```

---

