# Beaver

## 题目描述

给定一个字符串s和n个字符串b，求s中最长的连续子串使得其中不包含任意b。

## 样例 #1

### 输入

```
Go_straight_along_this_street
5
str
long
tree
biginteger
ellipse
```

### 输出

```
12 4
```

## 样例 #2

### 输入

```
IhaveNoIdea
9
I
h
a
v
e
N
o
I
d
```

### 输出

```
0 0
```

## 样例 #3

### 输入

```
unagioisii
2
ioi
unagi
```

### 输出

```
5 5
```

# 题解

## 作者：Lily_White (赞：0)

我们首先在原串里找出所有的限制串，这可以使用字符串哈希在 $O(nk)$ 时间内完成，这儿 $n$ 是原串长度， $k$ 是限制的字符串个数。

接着对每个匹配段开始的位置记录**以这个点开始的限制的字符串中右端点最靠右的一个**。

接着倒序扫描，维护当前答案段的右端点，若它已经覆盖了一个限制串，把它改为这个限制串右侧端点下标 $-1$ 就好了。

如果不用字符串哈希那复杂度是 $O(nkL)$，$L$ 为 $b_i$ 长度，如果正常出题人的话肯定不会放过去的。

```cpp
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
#define repn(i, n) for (int i = 1; i <= (int)n; i++)
#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define repr(i, m, n) for (int i = (int)m; i <= (int)n; i++)
#define repd(i, m, n) for (int i = (int)m; i >= (int)n; i--)
#define ttt template <typename T>
#define chmax(a, b) a = max(a, b)
#define chmin(a, b) a = min(a, b)
#define eprintf(...) ;  // fprintf(stderr, __VA_ARGS__)
const int INF = 0x3f3f3f3f;
ttt inline T rd(T& x) {
  x = 0;
  T neg = 1;
  char c = 0;
  while (c < '0' || c > '9') {
    if (c == '-') neg = -1;
    c = getchar();
  }
  while (c >= '0' && c <= '9') {
    x = x * 10 + c - 48;
    c = getchar();
  }
  x *= neg;
  return x;
}
// -------- Item Get Border Line! -----------
// Don't forget to use long long if needed!
using ull = unsigned long long;
const int base = 13331;
struct Hasher {
  ull h[100010], p[100010];
  int n;
  void initHash(string& s) {
    n = s.length();
    if (s.front() != '%') s = "%" + s;
    p[0] = 1;
    repn(i, n) {
      h[i] = h[i - 1] * base + (s[i] - '0' + 1);
      p[i] = p[i - 1] * base;
    }
  }
  ull getRangeHash(int l, int r) { return h[r] - h[l - 1] * p[r - l + 1]; }
  ull getHash(void) { return getRangeHash(1, n); }
} H, h[11];
int n, k;
string b[11];
int len[11];
int rightEnd[100010];
int main() {
  string s;
  cin >> s;
  n = s.length();
  H.initHash(s);
  rd(k);
  repn(i, k) {
    cin >> b[i];
    len[i] = b[i].length();
    h[i].initHash(b[i]);
  }
  // find all matching positions
  memset(rightEnd, 0x3f, sizeof(rightEnd));
  repn(j, k) {
    repn(i, n) {
      if (i + len[j] - 1 > n) break;
      if (s[i] != b[j][1]) continue;
      eprintf("i = %d, %llu, %llu\n", i, H.getRangeHash(i, i + len[j] - 1),
              h[j].getHash());
      if (H.getRangeHash(i, i + len[j] - 1) == h[j].getHash()) {
        chmin(rightEnd[i], i + len[j] - 1);
      }
    }
  }
  // repn(i, n) sum[i] += sum[i - 1];
  // repn(i, n) {eprintf("%d ", rightEnd[i]);} eprintf("\n");
  int cur = n, ans = 0, ansi = 0;
  repd(i, n, 1) {
    if (rightEnd[i] <= cur) cur = rightEnd[i] - 1;
    if (cur - i + 1 >= ans) {
      ans = cur - i + 1;
      ansi = i - 1;
    }
  }
  printf("%d %d\n", ans, ansi);
}
```

---

