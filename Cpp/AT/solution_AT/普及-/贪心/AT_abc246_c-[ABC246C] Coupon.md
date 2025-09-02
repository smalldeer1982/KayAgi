# [ABC246C] Coupon

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc246/tasks/abc246_c

$ N $ 個の商品があります。$ i\ =\ 1,\ 2,\ \ldots,\ N $ について、$ i $ 番目の商品の値段は $ A_i $ 円です。

高橋君は $ K $ 枚のクーポンを持っています。  
 $ 1 $ 枚のクーポンは $ 1 $ つの商品に対して使用することができ、$ 1 $ つの商品に対してはクーポンを何枚でも（ $ 0 $ 枚でもよい）使用することができます。 値段が $ a $ 円の商品に対して $ k $ 枚のクーポンを使用すると、その商品を $ \max\lbrace\ a\ -\ kX,\ 0\rbrace $ 円で買うことができます。

高橋君がすべての商品を買うために支払う合計金額の最小値を出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ K,\ X\ \leq\ 10^9 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- 入力はすべて整数

### Sample Explanation 1

$ 1 $ 番目の商品に対してクーポン $ 1 $ 枚、$ 3 $ 番目の商品に対してクーポン $ 1 $ 枚、$ 5 $ 番目の商品に対してクーポン $ 2 $ 枚を使用すると、 - $ 1 $ 番目の商品を $ \max\lbrace\ A_1-X,\ 0\ \rbrace\ =\ 1 $ 円で買うことができ、 - $ 2 $ 番目の商品を $ \max\lbrace\ A_2,\ 0\ \rbrace\ =\ 3 $ 円で買うことができ、 - $ 3 $ 番目の商品を $ \max\lbrace\ A_3-X,\ 0\ \rbrace\ =\ 3 $ 円で買うことができ、 - $ 4 $ 番目の商品を $ \max\lbrace\ A_4,\ 0\ \rbrace\ =\ 5 $ 円で買うことができ、 - $ 5 $ 番目の商品を $ \max\lbrace\ A_5-2X,\ 0\ \rbrace\ =\ 0 $ 円で買うことができます。 よって、すべての商品を $ 1\ +\ 3\ +\ 3\ +\ 5\ +\ 0\ =\ 12 $ 円で買うことができ、これが最小です。

## 样例 #1

### 输入

```
5 4 7
8 3 10 5 13```

### 输出

```
12```

## 样例 #2

### 输入

```
5 100 7
8 3 10 5 13```

### 输出

```
0```

## 样例 #3

### 输入

```
20 815 60
2066 3193 2325 4030 3725 1669 1969 763 1653 159 5311 5341 4671 2374 4513 285 810 742 2981 202```

### 输出

```
112```

# 题解

## 作者：Tsawke (赞：0)

# [ABC246C Coupon](https://www.luogu.com.cn/problem/AT_abc246_c) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.monkey-hyx.tech?t=ABC246C)

## 题面

$ n $ 个物品第 $ i $ 个价格为 $ a_i $，有 $ k $ 张 $ x $ 元优惠券，可以叠加，但不能分裂开使用，求全部购买的最少花费。

## Solution

在还有优惠券的前提下，对于所有 $ a_i \ge x $ 一直使用优惠券直到 $ a_i \lt x $，然后降序排序用剩余的 $ k $ 个券贪心地把前 $ k $ 个抵消，后面的求和即为答案。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/extc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;
using namespace __gnu_pbds;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

template<typename T = int>
inline T read(void);

int a[210000];

int main(){
    int N = read(), K = read(), X = read();
    for(int i = 1; i <= N; ++i){a[i] = read();while(K && a[i] >= X)--K, a[i] -= X;}
    sort(a + 1, a + N + 1, greater < int >());
    ll ans(0);
    for(int i = K + 1; i <= N; ++i)ans += a[i];
    printf("%lld\n", ans);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template<typename T>
inline T read(void){
    T ret(0);
    short flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2022_10_21 初稿

---

