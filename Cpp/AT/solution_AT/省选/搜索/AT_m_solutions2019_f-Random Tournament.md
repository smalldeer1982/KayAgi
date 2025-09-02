# Random Tournament

## 题目描述

[problemUrl]: https://atcoder.jp/contests/m-solutions2019/tasks/m_solutions2019_f

$ N $ 人の参加するじゃんけん大会を行います。 参加者は人 $ 1 $, 人 $ 2 $, $ \ldots $, 人 $ N $ と呼ばれます。 どの $ 2 $ 人についてもその $ 2 $ 人がじゃんけんをしたときにどちらが勝利するかが事前に決まっています。 この情報は正の整数 $ A_{i,j} $ ( $ 1\ \leq\ j\ <\ i\ \leq\ N $ ) によって表され、

- $ A_{i,j}\ =\ 0 $ のとき、人 $ i $ は人 $ j $ に負けること
- $ A_{i,j}\ =\ 1 $ のとき、人 $ i $ は人 $ j $ に勝つこと

をそれぞれ表します。

大会は次のようにして行われます。

- $ N $ 人の参加者を人 $ 1 $, 人 $ 2 $, $ \ldots $, 人 $ N $ の順に横一列に並べる。
- 列で連続している $ 2 $ 人をランダムに選んで、その $ 2 $ 人で試合を行い、負けた人を列から外す。 これを $ N-1 $ 回繰り返し、最後に残った $ 1 $ 人を優勝者とする。

優勝する可能性のある人の人数を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2000 $
- $ A_{i,j} $ は $ 0 $ または $ 1 $

### Sample Explanation 1

人 $ 1 $ は人 $ 2 $ に勝ち、人 $ 2 $ は人 $ 3 $ に勝ち、人 $ 3 $ は人 $ 1 $ に勝ちます。 最初に人 $ 1 $ と人 $ 2 $ が試合をすると人 $ 3 $ が優勝し、 最初に人 $ 2 $ と人 $ 3 $ が試合をすると人 $ 1 $ が優勝します。

## 样例 #1

### 输入

```
3
0
10```

### 输出

```
2```

## 样例 #2

### 输入

```
6
0
11
111
1111
11001```

### 输出

```
3```

# 题解

## 作者：wurzang (赞：1)

设 $L_{i,j}$ 表示 $i$ 是否秒杀区间 $[i,j]$ ， $R_{i,j}$ 表示 $j$ 是否秒杀区间 $[i,j]$，其中 $i<j$

就有

$$L_{i,j}=\max\limits_{i < pos \leq j}\{ L_{pos,j} \  \&  \ R_{i+1,pos} \ \& \ a_{i,pos} \} $$

$$
R_{i,j} = \max\limits_{i \leq pos < j} \{ L_{pos,j-1} \ \& \ R_{i,pos} \ \& \ a_{j,pos}  \}
$$


答案即为 $\sum_{i=1}^n [L_{i,n} \& R_{1,i}]$

可以通过定义 $L_{i,j}=0,R_{i,j}=0 \ (i > j)$ 的方式来让这个 $pos$ 的取值范围达到 $1 \sim n$

然后发现这个式子其实可以通过 `bitset` 来优化，只是 $L_{i,j}$ 的定义需要反一下，改成 $L_{j,i}$ 表示 $i$ 是否秒杀区间 $[i,j]$ 即可。


时间复杂度 $\mathcal{O(\frac{n^3}{w})}$

[code](https://atcoder.jp/contests/m-solutions2019/submissions/16969807)

---

## 作者：清烛 (赞：0)

[更好的阅读体验](https://blog.imyangty.com/sol-msolutions2019f/)。

~~更详细的一篇题解。这题其实挺经典的为什么洛谷上交的人不多啊/kk~~

## Description

给定一张竞赛图，$i\to j$ 有连边表示 $i$ 能打败 $j$。将 $1,2,\cdots,n$ 排成一排，每次可以选相邻两个人干架留下胜者，问最后有多少人可能赢。

ZR 加强版要求输出方案。

## Solution

可以设计出一个比较 naive 的 dp：$f_{i, j, k}$ 表示 $[i, j]$ 中 $k$ 能否胜出。然后这个东西可以 $O(n^4)$ 或者 $O(n^5)$ 随便转移一下，无法通过。

然后考虑优化状态：发现我们没有必要设计出这一个多余的 $k$，因为 $k$ 能在 $[l, r]$ 中胜出当且仅当 $k$ 能赢了 $[l, k -1] $ 中的人且能赢 $[k + 1, r]$ 中的人。两边的这些人是独立的，所以可以设计出一个 $f_{i, j, 0/1}$ 表示 $i/j$ 能否赢 $[i, j]$ 中的所有人。状态瞬间变为 $O(n^2)$ 级别。

下面为了好看一点，我们令 $L_{i, j}$ 为上文的 $f_{i, j, 0}$，$R_{i, j}$ 为上文的 $f_{i, j ,1}$。

于是转移就来了：

$$
\begin{aligned}
L_{i, j} &= \max_{i < k \le j}\{L_{k, j}\land R_{i + 1, k}\land a_{i, k}\}\\
R_{i, j} &= \max_{i < k \le j}\{L_{k, j - 1}\land R_{i, k}\land a_{j, k}\}
\end{aligned}
$$

这个是 $O(n^3)$ 的。然后呢所有的 dp 状态都是 `bool` 型的，`bitset` 碾过去复杂度就是 $O\left(\dfrac{n^3}{w}\right)$ 的，可以通过此题。

## Implementation

实现的时候需要注意一下 $L_{i, j}$ 的定义需要改一下， 改成 $L_{j, i}$ 表示 $i$ 能否赢 $[i, j]$ 中的所有人。

```cpp
#include <iostream>
#include <bitset>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;
const int maxn = 2005;
bitset<maxn> L[maxn], R[maxn], a[maxn];
int n;

int main() {
    cin >> n;
    FOR(i, 1, n) {
        FOR(j, 1, i - 1) {
            char ch; cin >> ch;
            if (ch == '1') a[i][j] = 1;
            a[j][i] = a[i][j] ^ 1;
        }
    }

    FOR(i, 1, n) L[i][i] = R[i][i] = 1;
    FOR(len, 2, n) {
        FOR(i, 1, n - len + 1) {
            int j = i + len - 1;
            L[j][i] = (L[j] & R[i + 1] & a[i]).count() > 0;
            R[i][j] = (L[j - 1] & R[i] & a[j]).count() > 0;
        }
    }
    int ans = 0;
    FOR(i, 1, n) ans += (L[n][i] & R[1][i]);
    cout << ans << endl;
    return 0;
}
```



---

