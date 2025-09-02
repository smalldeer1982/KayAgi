# Smaller-Suffix-Free Sequences

## 题目描述

[problemUrl]: https://atcoder.jp/contests/ddcc2020-final/tasks/ddcc2020_final_c

数列 $ T\ =\ (T_1,\ \ldots,\ T_L) $ が smaller-suffix-free であるとは、 $ i\ =\ 2,\ 3,\ \ldots,\ L $ 全てについて、 数列 $ (T_i,\ T_{i+1},\ \ldots,\ T_L) $ が 辞書順で $ T $ よりも大きいことを指します。 たとえば $ (5) $ や $ (1,\ 1,\ 2,\ 3) $ はsmaller-suffix-freeであり、$ (3,\ 2,\ 1) $ や $ (2,\ 2) $ は smaller-suffix-free ではありません。

長さ $ N $ の数列 $ A\ =\ (A_1,\ \ldots,\ A_N) $ が与えられます。 各 $ i\ =\ 1,\ \ldots,\ N $ について、$ (A_i,\ A_{i+1},\ \ldots,\ A_j) $ が smaller-suffix-free であるような最大の $ j $ を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 2\ \times\ 10^5\ (1\ \leq\ i\ \leq\ N) $

### Sample Explanation 1

$ A_1 $ から始まる smaller-suffix-free である 最長の連続する部分列は $ (A_1)\ =\ (3) $ です。したがって $ 1 $ 行目には $ 1 $ を出力します。 同様に、$ (A_2),\ (A_3,\ A_4,\ A_5,\ A_6),\ (A_4,\ A_5,\ A_6),\ (A_5,\ A_6),\ (A_6) $ がそれぞれ $ A_i\ (2\ \leq\ i\ \leq\ 6) $ から始まる smaller-suffix-free である最長の連続する部分列です。

## 样例 #1

### 输入

```
6
3 2 1 1 2 3```

### 输出

```
1
2
6
6
6
6```

## 样例 #2

### 输入

```
3
10 10 10```

### 输出

```
1
2
3```

# 题解

## 作者：Aegleseeker_ (赞：1)

Lyndon 串好像是个挺有用的东西，不过这里用不到。

仔细考虑一下 Lyndon 串的定义本质上是什么。

**性质 $1$：若一个串是 Lyndon 串，则求出该串的后缀数组后，满足 $rk_1=1$。**

**性质 $2$：若两字符串 $a,b$ 满足 $a<b$，则 $a+x<b<x$，其中小于指字典序，加法指字符串的拼接。**

证明略。我认为你既然开了这道题，这两个性质对你来说也不难理解。

接下来怎么做呢？利用性质 $2$，我们可以把题目中「后缀的前缀的后缀」当成「后缀」，此时不难发现第 $3$ 条性质。

**性质 $3$：一个后缀 $i$ 的某个前缀 $[i,j]$ 是 Lyndon 串，当且仅当 $rk_i=\min\limits_{k=i}^j rk_k$。**

于是问题就变得简单了，我们可以考虑用 st 表维护 rk 数组，直接二分出最大的 $j$，或者使用单调栈维护。

复杂度单 $\log$。

submission：https://atcoder.jp/contests/ddcc2020-final/submissions/65732836

---

## 作者：sunkuangzheng (赞：0)

$\textbf{AT\_ddcc2020\_final\_c }$

> - 给定字符串 $s$，对于每个后缀求一个最长的前缀使其是 Lyndon 串 $^\dagger$。
> - $^\dagger$ 一个字符串 $s$ 是 Lyndon 串当且仅当它的字典序严格小于其所有后缀。
> - $1 \le |s| \le 2 \cdot 10^5$，字符集大小 $2 \cdot 10^5$。


先对原串后缀排序。考虑对于 $i$ 开头的后缀，如果存在一个 $j$ 满足 $rk_j < rk_i$，那么如果将前缀的右端点 $r$ 取在 $j$ 后面，$j$ 开头的后缀一定小于 $i$ 开头的后缀的字典序。

我们合理猜测对于每个 $i$ 答案 $r$ 会取到第一个 $rk_j < rk_i$ 的 $j$ 前面。必要性上面已经阐述，下面证明其充分性：

> - 考虑对于区间 $[l,r]$ 和 $k \in [l,r]$，$rk_k > rk_l$ 且 $s[k,r] < s[l,r]$ 的条件是什么：我们必须有 $\operatorname{LCP}(suf_l,suf_k) \ge r - k+1$。
> - 由于 $rk_{r+1} < rk_l$，$\operatorname{LCP}(suf_l,suf_k) \ge r - k+1$ 且 $rk_k > rk_l$ 不可能成立。故把 $r$ 取到 $j-1$ 可以得到合法 Lyndon 串。

单调栈求解即可，使用 SA-IS 时间复杂度线性。

```cpp
#include <bits/stdc++.h>
#include <atcoder/string>
using namespace std;
const int N = 2e5+5;
int st[N],tp,rk[N],n,ans[N];
int main(){
    cin >> n; vector<int> a(n),_sa;
    for(int &x : a) cin >> x;
    _sa = atcoder::suffix_array(a);
    for(int i = 1;i <= n;i ++) rk[_sa[i-1] + 1] = i;
    st[++tp] = n + 1;
    for(int i = n;i >= 1;i --){
        while(rk[i] < rk[st[tp]]) tp --;
        ans[i] = st[tp] - 1,st[++tp] = i;
    }for(int i = 1;i <= n;i ++) cout << ans[i] << "\n";
}
```

---

