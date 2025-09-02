# Hamming Triples

## 题目描述

Little Chris is having a nightmare. Even in dreams all he thinks about is math.

Chris dreams about $ m $ binary strings of length $ n $ , indexed with numbers from 1 to $ m $ . The most horrifying part is that the bits of each string are ordered in either ascending or descending order. For example, Chris could be dreaming about the following 4 strings of length 5:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF406E/2bc92794d57f524d37633fb25d36a0e9463e28fd.png)The Hamming distance $ H(a,b) $ between two strings $ a $ and $ b $ of length $ n $ is the number of positions at which the corresponding symbols are different.

Сhris thinks that each three strings with different indices constitute a single triple. Chris's delusion is that he will wake up only if he counts the number of such string triples $ a $ , $ b $ , $ c $ that the sum $ H(a,b)+H(b,c)+H(c,a) $ is maximal among all the string triples constructed from the dreamed strings.

Help Chris wake up from this nightmare!

## 样例 #1

### 输入

```
5 4
0 3
0 5
1 4
1 5
```

### 输出

```
3
```

## 样例 #2

### 输入

```
10 4
1 5
0 5
0 5
1 5
```

### 输出

```
4
```

# 题解

## 作者：Aleph_Drawer (赞：2)

这道题目的转化是很妙的，颇有 Atcoder 的风范了。

### 1 题意简述

给你 $m$ 个长度为 $n$ 的不上升或者是不下降的 $01$ 序列。若用 $H(x,y)$ 表示序列 $x$ 与序列 $y$ 的不同数字数量，则在 $H(a,b) + H(b,c) + H(a,c), a < b < c$ 最大的情况下，求方案数。

### 2 题解

首先我们不难想到将这个 $01$ 序列进行排序以及编号。观察到如果进行特定顺序的排序，那么我们可以做到相邻的序列的 $H$ 只相差 $1$。

具体的，假设 $n = 3$，那么我将其排序如下：

$$
000, 001, 011, 111, 110, 100
$$

接下来，我们按照输入对它进行编号，以 $001, 011, 110$ 为例，就编号为 $2,3,5$。

此时 $H(a,b)$ 就可以很方便的表示了。这样，我们便可以挖掘更多的性质。

我们不妨用偏几何的方法来表示。我们可以在一个正 $2n$ 边形上面研究性质。

不难发现应该有两种情况。

首先是第一种：所有的点都集中在一个长度不超过 $n$ 的区间当中。

那么此时可以找到这些点的两个“端点”。如果我们设这两个端点的值为 $a,b$，那么 $2H(a,b)$ 就是能够达到的最大值。方案数是比较好求的，我们假设有 $x$ 个 $a$，$y$ 个 $b$，那么方案数就是

$$
(m-x-y)xy + \dfrac {x(x-1)y + y(y - 1)x}2
$$

其中，前半部分是选择 $a,b$ 然后再选择中间的一个其他值的方案数，而另外部分则是选择两个 $a$ 一个 $b$ 和两个 $b$ 一个 $a$ 的方案数。

然后是第二种：就是其他的情况。

这种情况下，最大值是 $2n$。你可以在正多边形上画出一个类似于三角形的东西，这个东西是横跨所有节点的，所以最大值是 $2n$。

这种情况下的求值也好办：我们对这三个点没有太大的要求，只要他们不同时在一个长度小于 $n$ 的区间里面即可。

所以我们再次运用组合数知识。我们将所有可能的选取方法，减去选取三个同时在一个长度小于 $n$ 的区间的方法。

可以使用双指针扫描一遍 $O(m)$ 的解决。

$$
C_m^3 - \sum_i C_{[l_i,r_i]}^3
$$

由于两种讨论方法都只需要 $O(m)$ 的扫描时间，而排序需要的时间是 $O(m \log m)$。

所以时间复杂度是 $O(m \log m)$。

不过还请特别注意一个细节，在某些实现方式下，当所有序列的值全部一样时，会进入死循环，这时需要特殊判断。

### 3 代码

```c++
#include<bits/stdc++.h>

typedef long long ll;

const ll N = 1e5 + 105;

ll n, m, a[N], s[N], f[N];

ll dist(ll x, ll y) {
    if(x <= y)
        return y - x;
    else
        return (n << 1ll) - x + y;
}

int main() {
    scanf("%lld%lld", &n, &m);
    for(ll i = 1; i <= m; i++) {
        scanf("%lld%lld", &s[i], &f[i]);
        if(!s[i]) a[i] = n - f[i] + 1;
        else a[i] = (n << 1ll) - f[i] + 1;
    }
    std::stable_sort(a + 1, a + m + 1);
    ll ins = 0;
    for(ll i = 1; i < m; i++) {
        if(dist(a[i], a[i + 1]) >= n) {
            ins = i;
            break;
        }
    }
    if(dist(a[m], a[1]) >= n) ins = m;

    if(!ins) {
        ll r = 1, res = (m - 2) * (m - 1) * m / 6ll;
        for(ll i = 1; i <= m; i++) {
            while(dist(a[i], a[r % m + 1]) < n) {
                r++;
                if(r > 4 * m) {
                    printf("%lld\n", (m - 2) * (m - 1) * m / 6ll);
                    return 0; //这是最后所说的特别判断
                }
            }
            res -= ((r - i) * ((r - i) - 1ll)) >> 1ll;
        }
        printf("%lld\n", res);
    }
    else {
        ll stp = ins % m + 1, edp = ins, stl = 0, str = 0;
        for(ll i = stp; i != edp; i = i % m + 1) {
            if(a[i] == a[stp]) stl++;
        }
        for(ll i = edp; i != stp; i = (i == 1 ? m : i - 1)) {
            if(a[i] == a[edp]) str++;
        }
        printf("%lld\n", stl * str * (m - stl - str) + (stl * (stl - 1) >> 1ll) * str + (str * (str - 1) >> 1ll) * stl);
    }
    return 0;
}
```

---

