# Non-triangular Triplets

## 题目描述

[problemUrl]: https://atcoder.jp/contests/nikkei2019-2-qual/tasks/nikkei2019_2_qual_e

正の整数 $ N $ 及び $ K $ が与えられます。

以下の条件をみたすように、$ 3N $ 個の整数 $ K,K+1,...,K+3N-1 $ を $ 3 $ 整数からなる $ N $ 個の組 $ (a_1,b_1,c_1),...,(a_N,b_N,c_N) $ に分割することが可能かを判定して下さい。$ K,K+1,...,K+3N-1 $ のうちどの整数も、$ N $ 個の組のうちちょうど $ 1 $ 個に現れなければなりません。

- $ 1 $ 以上 $ N $ 以下のすべての整数 $ i $ に対して $ a_i\ +\ b_i\ \leqq\ c_i $ が成り立つ。

また、可能な場合はそのような分割を $ 1 $ つ構成してください。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ ≦\ 10^5 $
- $ 1\ ≦\ K\ ≦\ 10^9 $

## 样例 #1

### 输入

```
1 1```

### 输出

```
1 2 3```

## 样例 #2

### 输入

```
3 3```

### 输出

```
-1```

# 题解

## 作者：AC_love (赞：1)

首先容易想到 $c$ 一定是后面 $n$ 个数，而 $a, b$ 则分别取前面 $2n$ 个数。

为啥？因为如果把后 $n$ 个数放在不等号前面，而把前 $2n$ 个数放在不等号后面，则我们把它们交换一下一定仍然成立。

接下来考虑如何构造一组解。

首先，我们肯定希望相等的式子越多越好。

我们先选上第 $2n$ 个数和第 $3n$ 个数分别放在不等式左右，然后找一找等于 $n$ 的位置。

令等于 $n$ 的位置为 $x$，则我们从 $x$ 往右走，这样构成三元组：

$(x, 2n, 3n)$

$(x + 1, 2n - 2, 3n - 1)$

$(x + 2, 2n - 4, 3n - 2)$

$(x + 3, 2n - 6, 3n - 3)$

以此类推。

令这样的三元组有 $k + 1$ 个，则最后一个是：

$(x + k, 2n - 2k, 3n - k)$

然后我们从 $2n - 1$ 开始，有：

$(?, 2n - 1, 3n - k - 1)$

每次选一个当前可选的最大的数即可。

[code](https://atcoder.jp/contests/nikkei2019-2-qual/submissions/59720874)

---

## 作者：dd_d (赞：1)

[更好的阅读体验](https://www.cnblogs.com/dd-d/p/16268231.html)  
### Sol  
首先我们钦定 $c_i=2 \times n -1 + i + k$。  
然后考虑下面一种构造方案。  
然后对于 $i \leq \left \lfloor \frac{n}{2} \right \rfloor$，$a_i=k-1+2 \times i$，$b_i=k+n+ (n \ and \ 1)-i+1$。  
对于 $i > \left \lfloor \frac{n}{2} \right \rfloor$，记 $x=i - \left \lfloor \frac{n}{2} \right \rfloor$，$a_i=k + 2 \times (x-1)$，$b_i=k + 2 \times n  - x$。  
对于这样的构造方式，实质上是 $a_i=a_{i-1}+ 2$，$b_i=b_{i-1}-1$，所以只要第一组成立那么便有解。  
把第一组的式子拆出来就是 $k \leq \left \lceil \frac{n}{2} \right \rceil$。可以证明当不满足这一条件时原题无解。  
然后假设原问题有解，那么  
$$ a_i+b_i \leq c_i$$
$$ \sum a_i+b_i \leq \sum c_i$$
$$ \sum a_i+b_i + c_i \leq \sum 2 \times c_i$$
$$ \frac{3 \times n \times (3 \times n-1)}{2} + 3 \times n \times k \leq \sum 2 \times c_i$$  
又有  
$$\sum c_i \leq \sum_{i=2n}^{3n-1} i+k$$  
拆一下式子  
$$\sum c_i \leq \frac{n \times (5 \times n-1)}{2} +n \times k$$  
综上  
$$ \frac{3 \times n \times (3 \times n-1)}{2} +3 \times n \times (3 \times n-1) + 2 \times n \times k $$  
然后拆出来就是  
$$ 2 \times k \leq n+1$$

---

