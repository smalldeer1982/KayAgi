# [ARC056C] 部門分け

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc056/tasks/arc056_c

高橋くんのいる会社は$ N $人の社員からなる。社員$ i $と社員$ j $の間には、信頼度$ w_{i,j} $が定まっている。 おかげ様で会社はぐんぐん成長したため、$ N $人をいくつかの部門に分けることになった。ここで、部門分けのスコアを、(部門の数)\*$ K $-(異なる部門に属する$ 2 $人の間の信頼度の総和)と定める。 スコアの最大値を求めるプログラムを書いてください。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ ≦\ 17 $
- $ i≠j $ のとき、 $ 1\ ≦\ w_{i,j}\ ≦\ 10^6 $
- $ w_{i,i}\ =\ 0 $
- $ w_{i,j}=w_{j,i} $
- $ 1\ ≦\ K\ ≦\ 10^6 $
- 入力はすべて整数である

### 部分点

- $ N\ ≦\ 9 $ を満たすテストケース全てに正解した場合、部分点として$ 40 $点が与えられる。
- $ N\ ≦\ 15 $ を満たすテストケース全てに正解した場合、部分点として追加で$ 40 $点が与えられる。

### Sample Explanation 1

社員$ 1 $と$ 3 $で$ 1 $つの部門、社員$ 2 $で$ 1 $つの部門を作ると、 部門の数は$ 2 $つ、異なる部門の間の$ 2 $人の信頼度の総和は$ 2 $なので、$ 2*3-2=4 $となる。 スコアを$ 4 $より大きくする方法はない。

## 样例 #1

### 输入

```
3 3
0 1 5
1 0 1
5 1 0```

### 输出

```
4```

## 样例 #2

### 输入

```
4 8
0 2 3 5
2 0 1 2
3 1 0 8
5 2 8 0```

### 输出

```
11```

## 样例 #3

### 输入

```
5 10
0 10 1 2 1
10 0 1 2 1
1 1 0 6 7
2 2 6 0 8
1 1 7 8 0```

### 输出

```
12```

# 题解

## 作者：lky1433223 (赞：0)

# AT1919部門分け
## 推销我的博客
[四叶草&#127808;koala](https://www.cnblogs.com/Shiina-Rikka/p/11574974.html)


#### 异世界传送门：
[洛谷AT1919](https://www.luogu.org/problem/AT1919)

[ATcoder056C](https://arc056.contest.atcoder.jp/tasks/arc056_c)

[官方题解](http://arc056.contest.atcoder.jp/data/arc/056/editorial.pdf)

[本题解来自](http://mayokoex.hatenablog.com/entry/2016/06/26/004935)


## 题面

高橋くんのいる会社は $N$ 人の社員からなる。社員 $i$ と社員 $j$ の間には、信頼度 $w_{i, j}$ 
​が定まっている。 おかげ様で会社はぐんぐん成長したため、 $N$ 人をいくつかの部門に分けることになった。ここで、部門分けのスコアを、(部門の数)* $K$ - (異なる部門に属する 2 人の間の信頼度の総和)と定める。 スコアの最大値を求めるプログラムを書いてください。
$(n \leq 17)$

##### 一句话题意

$n$个人分组，不同组的人之间会产生代价，使 **$组数 * K - 总代价$** 最大化。

## 这题咋做

考虑到这个题人数很少，我们可以进行状压。
状态$f[S]$表示选择了 $S$集合时 的状态最大值，从它的子集进行转移，则

$ f[S] = max(f[S], K + f[S'] + $ 新加入的人与子集中的人产生的代价$)$

但是如果每次转移的时候$n^2$计算新加入的人与子集中的人产生的代价，复杂度是不允许的。

但是我们可以计算该集合内部每个人互相的代价，而他与另一个集合人产生的代价即为两个集合并集的代价减去两个集合内部的代价。

> 设集合$A, B, C = A \cup B $ 

>$ f[A, B$之间$] = f[C] - f[A] - f[B] $

这样我们可以通过$O(2^n)$预处理各子集内部代价，转移时O(1)计算。由于枚举子集$O(3^n)$, 故整体复杂度$O(3^n)$, $3^{17} = 129, 140, 163$, 可以通过此题。

## 放代码

``` cpp
#include <bits/stdc++.h>
namespace fdata
{
inline char nextchar()
{
    static const int BS = 1 << 21;
    static char buf[BS], *st, *ed;
    if (st == ed)
        ed = buf + fread(st = buf, 1, BS, stdin);
    return st == ed ? -1 : *st++;
}
#ifdef lky233
#define nextchar getchar
#endif
template <typename T>
inline T poread()
{
    T ret = 0;
    char ch;
    while (!isdigit(ch = nextchar()))
        ;

    do
        ret = ret * 10 + ch - '0';
    while (isdigit(ch = nextchar()));
    return ret;
}
template <typename Y>
inline void poread(Y &ret)
{
    ret = 0;
    char ch;
    while (!isdigit(ch = nextchar()))
        ;

    do
        ret = ret * 10 + ch - '0';
    while (isdigit(ch = nextchar()));
}
#undef nextcar
} // namespace fdata
using fdata::poread;
using namespace std;
const int MAXN = 18;
const long long INF = 1ll << 55;
long long w[MAXN][MAXN];
long long memo[1 << MAXN];
long long f[1 << MAXN];
int n;
long long k;
int main()
{
#ifdef lky233
    freopen("testdata.in", "r", stdin);
    freopen("testdata.out", "w", stdout);
#endif
    poread(n);
    poread(k);
    for (register int i = 0; i < n; ++i)
        for (register int j = 0; j < n; ++j)
            poread(w[i][j]);
    for (register int s = 0; s < (1 << n); ++s)
    {
        for (register int i = 0; i < n; ++i)
        {
            for (register int j = i + 1; j < n; ++j)
            {
                register int si = ((s >> i) & 1);
                register int sj = ((s >> j) & 1);
                if (si & sj)
                    memo[s] += w[i][j];
            }
        }
    }
    for (register int i = 0; i <= (1 << n); ++i)
    {
        for (register int j = i; j; j = (j - 1) & i)
        {
            f[i] = max(f[i], k + f[i ^ j] - memo[i] + memo[j] + memo[i ^ j]);
        }
    }
    cout << f[(1 << n) - 1] << endl;
}
```

#### 还有一个小插曲

原题解枚举子集是这么写的

``` cpp
for (register int i = 0; i <= (1 << n); ++i)
    {
        register int j = i;
        do
        {
        } while (j != i);
    }
```


至于$j$ $!=$ $i$ 为啥能够成功结束循环，当$i = -1 $时，它的~~二次元~~二进制表示是$11111111...$，$j$&$i$ 恰好为 $j$, 因此成功结束循环。


###### 本篇题解到此结束，ありがとうございます。



---

