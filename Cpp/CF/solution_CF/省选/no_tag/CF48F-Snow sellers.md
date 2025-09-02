# Snow sellers

## 题目描述

Berland的新年庆祝活动持续了$n$天。只有今年冬天是无雪的，所以冬季庆典的组织者不得不购买人造雪。在Berland有很多卖人造雪的公司。第$i$个公司每天生产$w_{i}$立方米的雪。第二天，雪融化了，公司又要生产$w_{i}$立方米的雪。在活动期间公司的产品打折，所以雪的价格每天都在下降。第一天，第$i$个公司生产的所有雪的总价为$c_{i}$ bourles（当地的一种货币）。接下来的每一天价格将会降低$a_{i}$ bourles,即第二天的价格为$c_{i}-a_{i}$ bourles,第三天则为$c_{i}-2a_{i}$ bourles,以此类推。众所周知，对于一家公司来说，它卖的雪的价格永远是正数。现在你需要帮助活动主办方制定购买雪的方案，以便每天恰好购买$W$立方米的雪。这样就没有必要买下所有公司生产的所有雪了。如果你在某一天从第$i$家公司买了$n_{i}$立方米的雪($0 \leq n_{i} \leq w_{i}$，注意$n_{i}$不一定是整数！），总价为$s_{i}$ bourles时，那么每立方米的雪的价格是$n_{i}s_{i}/w_{i}$ bourles。在不同的日子里，人们可以从不同的公司买雪。你需要花尽可能少的钱来完成雪的购买。保证所有公司生产的雪都足够多。

## 样例 #1

### 输入

```
2 3 10
4 4 4
5 5 8
1 2 5
```

### 输出

```
22.000000000000000
```

## 样例 #2

### 输入

```
100 2 1000000000
999999998 999999999
1000000000 1000000000
1 1
```

### 输出

```
99999995149.999995249999991
```

# 题解

## 作者：tder (赞：1)

> 于 2024-08-28 修正一处笔误，并优化格式。

令 $f_{i,j}=c_j-i\times a_j$，试对于每个 $1\le i\le n$，在 $m$ 个单价为 $\frac{f_{i,j}}{w_j}$ 且总量为 $w_j$ 的物品中，购买 $c_j$ 份第 $j$ 个物品，使得 $\sum c_j\ge W$ 且 $\sum\frac{f_{i,j}}{w_j}\cdot c_j$ 最小。 

---

考虑朴素贪心做法，将 $1\le i\le n$ 作为单独的问题分开处理。

尽可能多买 $\frac{f_{i,j}}{w_j}$ 小的物品，显然可以排序，再依题意模拟即可。

时间复杂度 $\mathcal{O}(n\cdot m\log m)$，超时。

考虑优化，参考快排思想与二分，维护二元组序列 $d=\{(x=\frac{f_{i,j}}{w_j},y=w_j)\}$。

记当前区间为 $[l,r]$ 且 $p=\frac{l+r}2$，每次所有满足 $x_{d_k}<x_{d_p}$ 的元素放在 $d_p$ 左侧，而将所有 $x_{d_k}>x_{d_p}$ 的元素放在 $d_p$ 右侧。那么，若 $\sum\limits_{k=1}^{p}y_{d_k}>W$ 则有 $r\leftarrow p-1$，反之若 $\sum\limits_{k=1}^{p}y_{d_k}<W$ 则 $l\leftarrow p+1$。特别的，若 $\sum\limits_{k=1}^{p}y_{d_k}=W$ 或 $l>r$ 说明找到了答案。可累计答案使得计算 $\sum\limits_{k=1}^{p}y_{d_k}$ 的均摊复杂度为 $\mathcal{O}(m)$。

上述过程用 STL 中的 `nth_element()` 函数即可 $\mathcal{O}(m)$ 实现。

时间复杂度 $\mathcal{O}(n\cdot m)$。

---

## 作者：complete_binary_tree (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/CF48F)

首先一个最简单的思路就是每次对 $\displaystyle\frac{c}{w}$ 进行排序，然后暴力贪心。可是它的时间复杂度是 $O(nm \log m)$ 的，肯定过不去。

考虑进行优化。我们发现，排序那部分耗费的复杂度是最大的，而且做的无用功也最多。我们可以对排序进行缩减，变成“半个快速排序”。

我们发现，可以像快排一样找出中间值 $mid$，然后将比 $mid$ 小的值放左边，比 $mid$ 大的放右边。

统计左边（包括中间）的重量和 $w$，如果 $W > w$，那么肯定在右边，往右递归，同时 $W$ 要减去 $w$；否则往左递归，答案加上左半边的价格总和。

最后肯定会留下一个位置，这个位置是被半包含（也可能全包含）的。把剩下的 $W$ 乘上它的单价，然后再加上上面统计的答案就是最终答案。

中间值 $mid$ 可以用 `nth_element()` 函数 $O(n)$ 求出，并且它还可以顺便把比 $mid$ 小的值放左边，比 $mid$ 大的放右边。使用方法：

`nth_element( a + l, a + mid, a + r + 1, <cmp> )`

从 `a + l` 位置到 `a + r` 位置找出 `mid-th` 个数并置于 `a + mid`，把比 `a + mid` 小的数放左边，比 `a + mid` 大的数放右边。

这个函数是 $O(m)$ 的，所以这种“半个快速排序”做法的复杂度是 $O(m)$ 的，于是总复杂度 $O(nm)$。

然而，我们发现了致命的问题：精度不够！

`double` 只能保证不到 $18$ 位的精度，而 `long double` 没有确切规定其精度，~~这时候就要用上 `__float128` 了~~ 而 `__float128` 由于运算太慢直接 $\text{TLE}$。

所以我们要祭出分离大法——让整数和小数分离。

统计答案的时候，前半部分只会产生整数的贡献，所以加到整数中；只有最后一步会产生整数+小数的贡献，所以分开加。

小数加着加着可能会超过 $1$，这时就要分摊给整数。

小数部分使用 `long double`，整数部分使用 `long long`，输出的时候先输出整数部分，小数部分按小数快写的方法输出即可。

这题看着时限 $10\text{s}$，实际上只有 $5\text s$。因为这题是远古题，后来 $\text{CodeForces}$ 升级了服务器，性能增强了，所以这题要算两倍的时间。（感觉有点不严谨）

代码：（$9315\text{ms}$ 极限卡过）

```cpp
#include<bits/stdc++.h>
using namespace std;

const int M = 5e5 + 5;

typedef long double ld;
typedef long long ll;

struct node{ int w, c; ld f; } tmp[M];

bool cmp( node x, node y ){ return x.f < y.f; }

int n, m, W, w[M], c[M], a[M];

namespace FastIO{
    char OutputDevide = ' ';
    template<typename T>inline void read(T& x){T f=1;x = 0;char ch = getchar();while(ch<'0'||ch >'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-48,ch=getchar();x*=f;}
    template<typename T,typename ... Args>inline void read(T& x,Args& ...args){read(x),read(args...);}
    template<typename T>inline void write(T x){if(x<0){putchar('-'),write(-x);return;}if(x/10)write(x/10);putchar(x%10+48);}
    template<typename T,typename ... Args>inline void write(T x,Args ...args){write(x),putchar(OutputDevide),write(args...);}
};
using FastIO::read, FastIO::write;

ld ans = 0;

void solve(){
    ll ans = 0; ld ans2 = 0;
    for( int i = 1; i <= n; ++i ){
        for( int j = 1; j <= m; ++j )
            tmp[j] = { w[j], c[j], (ld) c[j] / w[j] }, c[j] -= a[j];
        int l = 1, r = m;
        ll sumw = W;
        while( l < r ){
            int mid = ( l + r ) >> 1;
            nth_element( tmp + l, tmp + mid, tmp + r + 1, cmp );
            ll a = 0, _w = 0;
            for( int i = l; i <= mid; ++i ) a += tmp[i].c, _w += tmp[i].w;
            if( _w > sumw ) r = mid;
            else{
                l = mid + 1;
                sumw -= _w;
                ans += a;
            }
        }
        ld lstans = (ld)sumw * tmp[l].f;
        ans += (ll)lstans, ans2 += lstans - (ll)lstans;
        if( ans2 >= 1.0 ) ans += (ll)ans2, ans2 -= (ll)ans2;
    }
    printf( "%lld.", ans );
    for( int i = 1; i <= 10; ++i ){
        ans2 = ans2 * 10;
        printf( "%d", (int)ans2 );
        ans2 -= (int) ans2;
    }
}

int main(){
    read( n, m, W );
    for( int i = 1; i <= m; ++i ) read( w[i] );
    for( int i = 1; i <= m; ++i ) read( c[i] );
    for( int i = 1; i <= m; ++i ) read( a[i] );
    solve();
    getchar();//最后一行，防止退出
    return 0;
}
```

---

## 作者：hellolin (赞：0)

# CF48F Snow sellers 题解

前往 [博客暂时关闭] 可能获得更好阅读体验。

@[liaiyang](https://www.luogu.com.cn/user/783170)：了不起，你们卡常人。

首先这题有一个 naive 的策略，既然雪可以按比例购买，直接分别排序后贪心。复杂度 $O(nm\log m)$。

``` cpp
for (int j = 1; j <= n; ++j) {
  for (int i = 1; i <= m; ++i)
    p[i].f = (long double) p[i].c / p[i].w; // 雪的单价，正实数，按这个排序
  sort(&p[1], &p[m + 1]);
  int cnt = w;
  for (int i = 1; i <= m; ++i) {
    if (cnt >= p[i].w) {
      cnt -= p[i].w;
      ans += p[i].c;
    } else {
      ans += p[i].f * cnt;
      cnt = 0;
    }
    if (!cnt) break;
  }
  for (int i = 1; i <= m; ++i)
    p[i].c -= p[i].a;
}
```

那这样你会发现样例都过不了，题目要求 $10^{-9}$ 的误差。这时可以把 `long double` 都换成 `__float128` 并手写输出，这里不贴代码了。

结果是 TLE on #17，说明我们需要继续优化时间复杂度（`__float128` 太慢了）。

~~（当然这里不考虑桶排之类的排序，毕竟你要排实数）~~

注意到我们排序后实际上只使用了一部分数值较小的数据，说明这个排序是非必要的。

这个时候我们可以联想到 `std::nth_element`，但他是找第 $n$ 大元素的，怎么办呢？考虑一下快速排序的过程，每次选择一个基准点，比它小的在左边，比它大的在右边。[而 `std::nth_element` 正是干了这件事](https://zh.cppreference.com/w/cpp/algorithm/nth_element)，在基准点（第 $n$ 大元素）左边都小于基准点右边的。

这时我们使用类似二分的过程，每次令 $\mathrm{mid}$ 为基准点，进行一次上述操作，此时较小数据都在 $l$ 到 $\mathrm{mid}$ 之间。这时 check 一下后继续二分即可。

那有的同学可能有疑问，`std::nth_element` 是线性的，二分是 $\log m$ 的，你这不还是 $O(nm\log m)$ 吗？

有以下证明：

$$
\begin{aligned}
T(n)&=n+T(\frac{n}{2})\\
&=n+\frac{n}{2}+\frac{n}{4}+\frac{n}{8}+\dotsb\\
&=n\cdot (1+\frac{1}{2}+\frac{1}{4}+\frac{1}{8}+\dotsb)\\
&=2n\ ^{[1]}
\end{aligned}
$$

$^{[1]}$：参见 [几何级数](https://zh.wikipedia.org/wiki/%E5%B9%BE%E4%BD%95%E7%B4%9A%E6%95%B8)。

所以总复杂度为 $O(nm)$，足以通过此题。答案最好要整数小数分离一下。

``` cpp
namespace hellolin {
static constexpr int N = 105, M = 5e5 + 5;
int n, m, w;
int64 ans, req;
long double fl_ans;
struct company {
  int w, c, a;
  long double f;
} p[M];
int num[M];
void main() {
  io.input(n, m, w);
  for (int i = 1; i <= m; ++i)
    io.input(p[i].w);
  for (int i = 1; i <= m; ++i)
    io.input(p[i].c);
  for (int i = 1; i <= m; ++i)
    io.input(p[i].a);
  for (int j = 1; j <= n; ++j) {
    for (int i = 1; i <= m; ++i) {
      p[i].f = (long double) p[i].c / p[i].w;
      num[i] = i;
    }
    int l = 1, r = m;
    req = w;
    while (l < r) {
      int mid = (l + r) >> 1;
      nth_element(&num[l], &num[mid], &num[r + 1], [&](const int &x, const int &y) { return p[x].f < p[y].f; });
      int64 pri = 0, cnt = 0;
      for (int i = l; i <= mid; ++i) {
        cnt += p[num[i]].w;
        pri += p[num[i]].c;
      }
      if (cnt <= req) {
        l = mid + 1;
        req -= cnt;
        ans += pri;
      } else
        r = mid;
    }
    long double rst = req * p[num[l]].f;
    ans += (int64) rst;
    fl_ans += rst - (int64) rst;
    for (int i = 1; i <= m; ++i)
      p[i].c -= p[i].a;
  }
  ans += (int64) fl_ans;
  fl_ans -= (int64) fl_ans;
  io.write(ans, '.');
  for (int i = 1; i <= 12; ++i) {
    fl_ans *= 10;
    io.write((int) fl_ans);
    fl_ans -= (int) fl_ans;
  }
}
} // namespace hellolin
```

---

