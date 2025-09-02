# Divide Candies

## 题目描述

Arkady and his friends love playing checkers on an $ n \times n $ field. The rows and the columns of the field are enumerated from $ 1 $ to $ n $ .

The friends have recently won a championship, so Arkady wants to please them with some candies. Remembering an old parable (but not its moral), Arkady wants to give to his friends one set of candies per each cell of the field: the set of candies for cell $ (i, j) $ will have exactly $ (i^2 + j^2) $ candies of unique type.

There are $ m $ friends who deserve the present. How many of these $ n \times n $ sets of candies can be split equally into $ m $ parts without cutting a candy into pieces? Note that each set has to be split independently since the types of candies in different sets are different.

## 说明/提示

In the first example, only the set for cell $ (3, 3) $ can be split equally ( $ 3^2 + 3^2 = 18 $ , which is divisible by $ m=3 $ ).

In the second example, the sets for the following cells can be divided equally:

- $ (1, 2) $ and $ (2, 1) $ , since $ 1^2 + 2^2 = 5 $ , which is divisible by $ 5 $ ;
- $ (1, 3) $ and $ (3, 1) $ ;
- $ (2, 4) $ and $ (4, 2) $ ;
- $ (2, 6) $ and $ (6, 2) $ ;
- $ (3, 4) $ and $ (4, 3) $ ;
- $ (3, 6) $ and $ (6, 3) $ ;
- $ (5, 5) $ .

In the third example, sets in all cells can be divided equally, since $ m = 1 $ .

## 样例 #1

### 输入

```
3 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
6 5
```

### 输出

```
13
```

## 样例 #3

### 输入

```
1000000000 1
```

### 输出

```
1000000000000000000
```

# 题解

## 作者：Sooke (赞：2)

### 题意

求 $\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}[i^2 + j^2\ |\ m]$。

### 解题思路

满足 $i^2 + j^2\ |\ m$，即满足 $i^2 \equiv m - j^2\ (mod\ m)$。

虽然 $n$ 很大，但 $m$ 很小，又因为 $i^2,\ j^2$ 在模 $m$ 意义下的余数不超过 $m$ 种，所以我们可以把含每种余数的数量记在桶里，之后合并计算。

不难发现，$i^2\ (mod\ m)$ 具有周期性，并且 $m$ 一定是其中一个周期。于是先枚举一个周期，把 $\lfloor \frac{n}{m} \rfloor$（周期数量）加到桶里。最后如果剩下一些没算过的部分，单独计算即可，其长度不超过 $m$。

### 代码实现

注意在合并时特判余数为 $0$ 的情况。

```cpp
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>

typedef long long lol;

const int maxN = 1005;

int n, m;
lol ans, cnt[maxN];

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) { cnt[i * i % m] += n / m; } // 加上周期长度.
    for (int i = n / m * m + 1; i <= n; i++) { cnt[1ll * i * i % m]++; } // 处理零散部分.
    for (int i = 0; i < m; i++) { ans += cnt[i] * cnt[i ? m - i : 0]; } // 合并计算.
    std::cout << ans << std::endl;
    return 0;
}
```

---

