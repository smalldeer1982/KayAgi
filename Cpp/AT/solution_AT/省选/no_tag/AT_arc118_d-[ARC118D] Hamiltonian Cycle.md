# [ARC118D] Hamiltonian Cycle

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc118/tasks/arc118_d

素数 $ P $ および正の整数 $ a,\ b $ が与えられます。 $ P $ 項からなる整数列 $ A\ =\ (A_1,\ A_2,\ \ldots,\ A_P) $ であって、次の条件をすべて満たすものが存在するかを判定してください。 存在する場合には、そのようなものをひとつ出力してください。

- $ 1\leq\ A_i\leq\ P\ -\ 1 $
- $ A_1\ =\ A_P\ =\ 1 $
- $ (A_1,\ A_2,\ \ldots,\ A_{P-1}) $ は、$ (1,\ 2,\ \ldots,\ P-1) $ を並べ替えたものである
- 任意の $ 2\leq\ i\leq\ P $ に対して、次のうち少なくともひとつが成り立つ：
  - $ A_{i}\ \equiv\ aA_{i-1}\pmod{P} $
  - $ A_{i-1}\ \equiv\ aA_{i}\pmod{P} $
  - $ A_{i}\ \equiv\ bA_{i-1}\pmod{P} $
  - $ A_{i-1}\ \equiv\ bA_{i}\pmod{P} $

## 说明/提示

### 制約

- $ 2\leq\ P\leq\ 10^5 $
- $ P $ は素数
- $ 1\leq\ a,\ b\ \leq\ P\ -\ 1 $

### Sample Explanation 1

$ P\ =\ 13 $ を法として、 - $ A_2\equiv\ 5A_1 $ - $ A_2\equiv\ 4A_3 $ - $ \vdots $ - $ A_{13}\equiv\ 4A_{12} $ が成り立ち、この整数列は条件を満たすことが確認できます。

## 样例 #1

### 输入

```
13 4 5```

### 输出

```
Yes
1 5 11 3 12 9 7 4 6 8 2 10 1```

## 样例 #2

### 输入

```
13 1 2```

### 输出

```
Yes
1 2 4 8 3 6 12 11 9 5 10 7 1```

## 样例 #3

### 输入

```
13 9 3```

### 输出

```
No```

## 样例 #4

### 输入

```
13 1 1```

### 输出

```
No```

# 题解

## 作者：DJRzjl (赞：5)

（很妙的构造，这里大致为概括翻译[官方题解](https://atcoder.jp/contests/arc118/editorial/1569)）

考虑记 $n$ 为 $a^i$ 在 $\bmod p$ 意义下**最短循环节长度**，即最小的满足 $a^n=1$ 的正整数 $n$。令 $H=\{a^i|i \in \mathbb{Z}\}$，再记 $m$ 为满足 $b^j\in H$ 时**最小正整数** $j$。

于是可以画出一个 $n\times m$ 的矩形 $G$，令第 $(i,j) \small (i\in[0,n),j\in[0,m))$ 格表示数 $a^i\cdot b^j$，可以证明当原问题有解时，所有形如 $X=a^xb^y\small (x,y\in\mathbb{N}) \bmod p$ 的整数在 $G$ 中**出现且恰好出现一次**。

下面给出证明：

1. 所有数**出现过**一次:

	不妨设某个数写做 $X=a^xb^y$，则 $y$ 一定可写作 $y=t\cdot m+r$，所以 $X=a^xb^y=a^x(b^m)^tb^r$，由于 $m$ 的定义满足 $b^m\in H$，所以 $(b^m)^t\in H$，必然存在 $i\in[1,n)$ 满足 $a^i=a^x(b^m)^t$，于是 $X=a^ib^r$，出现在 $G$ 中。

2. 所有数出现**不超过**一次：

	假设存在整数 $i_1,i_2\in[0,n)$，$j_1,j_2\in[0,m)$ 满足 $a^{i_1}b^{j_1}=a^{i_2}b^{j_2}$，要证明每个数出现且仅出现一次，即去证明此时 $i_1=i_2$ 且 $j_1=j_2$。
    
    一般地，不妨令 $j_1\le j_2$，有 $a^{i_1-i_2}=b^{j_2-j_1}$，由于 $j_2-j_1\in[0,m)$，那么 $b^{j_2-j_1} \in H$，由定义，$m$ 取不到更小的 $j_2-j_1$，仅当 $j_2-j_1=0$。现在已知 $j_1=j_2$，又有 $a^{i_1}=a^{i_2}$，$n$ 为最短循环节，故 $i_1=i_2$。
    
证毕。但这有啥用呢？

显然，当 $nm\neq p-1$ 时，有些数都不能用 $a^xb^y$ 表示，无解，下面仅考虑对 $nm=p-1$ 的情况尝试构造。

特判 $n=1$ 或 $m=1$，此时方案唯一，暴力判断即可。

其余序列的构造即为在这个 $n\times m$ 的矩形 $G$ 中找一条**哈密顿回路**。

由于 $p$ 为质数，$p=2$ 时 $n,m$ 一定等于 $1$ 判掉了，$p-1$ 一定为偶数，所以 $n,m$ 中至少有一个为偶数。

手玩不难发现一定有解，并可以得到如下几种构造：

![]( https://cdn.luogu.com.cn/upload/image_hosting/frms9vy7.png)

![]( https://cdn.luogu.com.cn/upload/image_hosting/zt7pffcq.png)

![]( https://cdn.luogu.com.cn/upload/image_hosting/lvt4abns.png)



---

## 作者：Rosabel (赞：3)

看到这个在模 $P$ 意义下剩余类上进行乘法的操作，想都不用想直接转换成 $Z_{P-1}$ 上进行加法操作。那么问题转换成构造一个长度为 $P$ 的数组 $b$，使得 $\forall i\in[1,P),b_i+\log A=b_{i+1}\ \text{or}\ b_i-\log A=b_{i+1}\ \text{or}\ b_i+\log B=b_{i+1}\ \text{or}\ b_i-\log B=b_{i+1}\ \text{mod}\ P$，$b_{1\dots P-1}$ 为 $[0,P-1)$ 的一种排列，且 $b_1=b_n=0$。

**【注：这里所有的 $\log$ 均为模原根意义下整数 $\log$ 值】**

先卡掉一些特殊情况。

特殊情况 $1$：$\gcd(\log A,\log B)>1$，显然取不到 $[0,P-1)$ 的每一个值，所以输出 $\texttt{No}$。

特殊情况 $2$：在不是特殊情况 $1$ 的情况下，$\log A=P-1\ \text{or}\ \log B=P-1$，即 $A$ 和 $B$ 中至少有一个是原根，那么将 $1$ 连续成 $P-1$ 遍就能得到答案序列了。

特殊情况 $3$：在既不是特殊情况 $1$ 也不是特殊情况 $2$ 的情况下，$\frac{P-1}{\log A}\nmid2\ \text{and}\ \frac{P-1}{\log B}\nmid2$，此时可以看做一笔画走完长宽均为奇数的网格，黑白染色可以得到长度显然不能为奇数，所以输出 $\texttt{No}$。

接下来即长宽中至少一个为偶数的情况了，那么这样显然能构造解：

![](https://cdn.luogu.com.cn/upload/image_hosting/rux2kwul.png)

[code](https://atcoder.jp/contests/arc118/submissions/57674883)

给珂爱的小妹妹轻轻点个赞吧 qwq

---

