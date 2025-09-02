# [ABC156F] Modularness

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc156/tasks/abc156_f

長さ $ k $ の数列 $ d_0,d_1,...,d_{k\ -\ 1} $ があります。

以下のクエリ $ q $ 個を順に処理してください。

- $ i $ 番目のクエリは $ 3 $ つの整数 $ n_i,x_i,m_i $ からなる。 長さ $ n_i $ の数列 $ a_0,a_1,...,a_{n_i\ -\ 1} $ を、 \\\[ \\begin{aligned} a\_j = \\begin{cases} x\_i &amp; ( j = 0 ) \\\\ a\_{j - 1} + d\_{(j - 1)~\\textrm{mod}~k} &amp; ( 0 &lt; j \\leq n\_i - 1 ) \\end{cases}\\end{aligned} \\\] と定める。 $ (a_j~\textrm{mod}~m_i)\ <\ (a_{j\ +\ 1}~\textrm{mod}~m_i) $ であるような、$ j~(0\ \leq\ j\ <\ n_i\ -\ 1) $ の個数を出力する。

ここで $ 2 $ つの整数 $ y,\ z~(z\ >\ 0) $ について、$ (y~\textrm{mod}~z) $ は $ y $ を $ z $ で割った余りを表します。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 1\ \leq\ k,\ q\ \leq\ 5000 $
- $ 0\ \leq\ d_i\ \leq\ 10^9 $
- $ 2\ \leq\ n_i\ \leq\ 10^9 $
- $ 0\ \leq\ x_i\ \leq\ 10^9 $
- $ 2\ \leq\ m_i\ \leq\ 10^9 $

### Sample Explanation 1

$ 1 $ つ目のクエリについて、問題文で示した数列 {$ a_j $} は $ 3,6,7,11,14 $ になります。 - $ (a_0~\textrm{mod}~2)\ >\ (a_1~\textrm{mod}~2) $ - $ (a_1~\textrm{mod}~2)\ <\ (a_2~\textrm{mod}~2) $ - $ (a_2~\textrm{mod}~2)\ =\ (a_3~\textrm{mod}~2) $ - $ (a_3~\textrm{mod}~2)\ >\ (a_4~\textrm{mod}~2) $ であるため、このクエリに対する答えは $ 1 $ です。

## 样例 #1

### 输入

```
3 1
3 1 4
5 3 2```

### 输出

```
1```

## 样例 #2

### 输入

```
7 3
27 18 28 18 28 46 1000000000
1000000000 1 7
1000000000 2 10
1000000000 3 12```

### 输出

```
224489796
214285714
559523809```

# 题解

## 作者：StudyingFather (赞：14)

正着做似乎不太好办，我们考虑反面情况：即统计 $a_i \bmod m = a_{i+1} \bmod m$ 和 $a_i \bmod m \gt a_{i+1} \bmod m$ 这两种情况的数量。

首先我们做个预处理：将所有的 $d$ 都对 $m$ 取模，容易发现这个操作对结果没有影响。

接下来我们开始统计。

- $a_i \bmod m=a_{i+1} \bmod m$

容易发现只有 $d_{i \bmod k}=0$ 时满足条件。

- $a_i \bmod m \gt a_{i+1} \bmod m$

因为我们将所有 $d$ 都取模了，相当于我们现在进行的是 $m$ 进制运算。

这种情况下可以理解为在 $m$ 进制下发生了进位操作。

一次进位只可能使前一位的值恰好增加 $1$，因此我们只需要统计发生了多少次进位即可。

上面两个操作利用本题的周期性都可以在 $O(k)$ 时间内解决。从而总时间复杂度为 $O(qk)$。

```cpp
// Problem : F - Modularness
// Contest : AtCoder Beginner Contest 156
// URL : https://atcoder.jp/contests/abc156/tasks/abc156_f
// Author : StudyingFather
// Site : https://studyingfather.com
// Memory Limit : 1024 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <iostream>
using namespace std;
int d[5005],nd[5005];
long long ds[5005];
int main()
{
 int k,q;
 cin>>k>>q;
 for(int i=1;i<=k;i++)
  cin>>d[i];
 while(q--)
 {
  int n,x,m,cnt=0,ans;
  long long sum;
  cin>>n>>x>>m;
  n--;
  ans=n;
  for(int i=1;i<=k;i++)
  {
   nd[i]=d[i]%m;
   ds[i]=ds[i-1]+nd[i];
   cnt+=(nd[i]==0);
  }
  ans-=n/k*cnt;
  sum=x+n/k*ds[k]+ds[n%k];
  for(int i=1;i<=n%k;i++)
   ans-=(nd[i]==0);
  ans-=sum/m-x/m;
  cout<<ans<<endl;
 }
 return 0;
}
```

---

