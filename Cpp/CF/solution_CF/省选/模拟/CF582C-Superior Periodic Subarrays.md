# Superior Periodic Subarrays

## 题目描述

You are given an infinite periodic array $ a_{0},a_{1},...,a_{n-1},... $ with the period of length $ n $ . Formally, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF582C/aa44e9dfb7106bc0c4afdc0035ceead70e7d91ec.png). A periodic subarray $ (l,s) $ ( $ 0<=l&lt;n $ , $ 1<=s&lt;n $ ) of array $ a $ is an infinite periodic array with a period of length $ s $ that is a subsegment of array $ a $ , starting with position $ l $ .

A periodic subarray $ (l,s) $ is superior, if when attaching it to the array $ a $ , starting from index $ l $ , any element of the subarray is larger than or equal to the corresponding element of array $ a $ . An example of attaching is given on the figure (top — infinite array $ a $ , bottom — its periodic subarray $ (l,s) $ ):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF582C/3459142ae634f6d125367238083d1b99f717b1ba.png)Find the number of distinct pairs $ (l,s) $ , corresponding to the superior periodic arrays.

## 说明/提示

In the first sample the superior subarrays are (0, 1) and (3, 2).

Subarray (0, 1) is superior, as $ a_{0}>=a_{0},a_{0}>=a_{1},a_{0}>=a_{2},a_{0}>=a_{3},a_{0}>=a_{0},... $

Subarray (3, 2) is superior $ a_{3}>=a_{3},a_{0}>=a_{0},a_{3}>=a_{1},a_{0}>=a_{2},a_{3}>=a_{3},... $

In the third sample any pair of $ (l,s) $ corresponds to a superior subarray as all the elements of an array are distinct.

## 样例 #1

### 输入

```
4
7 1 2 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2
2 1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
3
1 1 1
```

### 输出

```
6
```

# 题解

## 作者：Elma_ (赞：0)

考虑什么样的 $a_i$ 能够出现在所选的数列中。显然其需要满足：
$$a_i \geq a_{(ks+i)\%n}$$

其中 $k$ 是一个大于 $0$ 的整数。而 $(ks+i)\%n$ 可以表示成 $ks+tn+i$ 的形式，其中 $t$ 是一个大于等于 $0$ 的整数。通过小学奥数知识可以知道， $ks+tn$ 可以表示成 $l \gcd(s, n)$ 的形式（其中 $l$ 为任意正整数），因此 $a_i$ 需要满足的条件即为：

$$a_i \geq a_{l\gcd(s,n)+i}$$

考虑把原数列按照间隔 $gcd(s,n)$ 个数分成若干组，那么 $a_i$ 能够出现在所选的数列中当且权当 $a_i$ 是这一组数中最大的一个。考虑枚举 $gcd(s,n)$，设这个数为 $d$，显然 $d|n$。然后对于每一个 $a_i$，若它是它所在的组中最大的数，就将其设为 $1$，否则将其设为 $0$，如此处理后我们就得到了一个 $01$ 数列。

然后设 $f_i$ 为以 $i$ 为结尾的最长 $1$ 连续段的长度，这个可以通过一个十分简单的 dp 求出。然后枚举长度，设 $cnt_i$ 为 $[1,i]$ 中有多少个 $s$ 满足 $gcd(s,n)$ 等于所枚举的 $d$（即为合法的长度个数），那么对于一个 $f_i$，其对于答案的贡献即为 $cnt_{f_i}$。

然而直接算的话发现是会超时的，这也是这个题最魔法的地方，因为求 $\gcd$ 的时候带一个 $\log$，如果求 $\gcd$ 的次数过多或者数过大的话就会超时。可以预处理 $\gcd$，或者也可以把枚举 $s$ 改为枚举 $\lfloor \frac{s}{d} \rfloor$，然后判断 $gcd(\lfloor \frac{s}{d} \rfloor,\lfloor \frac{n}{d} \rfloor)$ 是否等于 $1$，这样就减小了求 $\gcd$ 的数的范围。还要注意因为它是一个循环数组，因此计算时要将 $a$ 拉成两倍。时间复杂度为 $(d(n)\times n)$，其中 $d(n)$ 表示 $n$ 的因数个数。

```cpp
#include <set>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <algorithm>
#define pii pair<int, int>
#define mp make_pair
#define int long long
using namespace std;
 
inline int read() {
	int x = 0, w = 1;char ch = getchar();
	while (ch > '9' || ch < '0') { if (ch == '-')w = -1;ch = getchar(); }
	while (ch >= '0' && ch <= '9')x = x * 10 + ch - '0', ch = getchar();
	return x * w;
}
inline void write(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
 
const int maxn = 1e6 + 5;
const int mod = 998244353;
const int inf = 0x3f3f3f3f3f3f3f;
 
inline int min(int x, int y) { return x < y ? x : y; }
inline int max(int x, int y) { return x > y ? x : y; }

int n, ans, a[maxn], f[maxn], g[maxn], cnt[maxn];
bool buc[maxn];

inline int gcd(int a, int b) {
    return !b ? a : gcd(b, a % b);
}

signed main(void) {
    n = read();
    for (int i = 1;i <= n;i++) a[i] = read(), a[i + n] = a[i];
    for (int d = 1;d < n;d++) {
        if (n % d == 0) {
            memset(buc, 0, sizeof(buc));
            for (int k = 0;k < d;k++) {
                g[k] = 0;
                for (int i = k;i < (n << 1);i += d) g[k] = max(g[k], a[i]);
                for (int i = k;i < (n << 1);i += d) if (g[k] == a[i]) buc[i] = 1;
            }
            f[0] = buc[0];
            for (int i = 1;i < (n << 1);i++) {
                if (buc[i]) f[i] = f[i - 1] + 1; else f[i] = 0;
                f[i] = min(f[i], n - 1);
            }
            cnt[0] = 0;
            for (int i = 1;i < (n / d);i++) cnt[i] = cnt[i - 1] + (gcd(i, n / d) == 1);
            for (int i = n;i < (n << 1);i++) ans += cnt[f[i] / d];
        }
    }
    printf("%lld\n", ans);
    return 0;
}
```


---

