# Bear and Polynomials

## 题目描述

Limak is a little polar bear. He doesn't have many toys and thus he often plays with polynomials.

He considers a polynomial valid if its degree is $ n $ and its coefficients are integers not exceeding $ k $ by the absolute value. More formally:

Let $ a_{0},a_{1},...,a_{n} $ denote the coefficients, so ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF639C/b2e2221d8fc8543b45bad8022a862376e8bf8aaa.png). Then, a polynomial $ P(x) $ is valid if all the following conditions are satisfied:

- $ a_{i} $ is integer for every $ i $ ;
- $ |a_{i}|<=k $ for every $ i $ ;
- $ a_{n}≠0 $ .

Limak has recently got a valid polynomial $ P $ with coefficients $ a_{0},a_{1},a_{2},...,a_{n} $ . He noticed that $ P(2)≠0 $ and he wants to change it. He is going to change one coefficient to get a valid polynomial $ Q $ of degree $ n $ that $ Q(2)=0 $ . Count the number of ways to do so. You should count two ways as a distinct if coefficients of target polynoms differ.

## 说明/提示

In the first sample, we are given a polynomial $ P(x)=10-9x-3x^{2}+5x^{3} $ .

Limak can change one coefficient in three ways:

1. He can set $ a_{0}=-10 $ . Then he would get $ Q(x)=-10-9x-3x^{2}+5x^{3} $ and indeed $ Q(2)=-10-18-12+40=0 $ .
2. Or he can set $ a_{2}=-8 $ . Then $ Q(x)=10-9x-8x^{2}+5x^{3} $ and indeed $ Q(2)=10-18-32+40=0 $ .
3. Or he can set $ a_{1}=-19 $ . Then $ Q(x)=10-19x-3x^{2}+5x^{3} $ and indeed $ Q(2)=10-38-12+40=0 $ .

In the second sample, we are given the same polynomial. This time though, $ k $ is equal to $ 12 $ instead of $ 10^{9} $ . Two first of ways listed above are still valid but in the third way we would get $ |a_{1}|&gt;k $ what is not allowed. Thus, the answer is $ 2 $ this time.

## 样例 #1

### 输入

```
3 1000000000
10 -9 -3 5
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 12
10 -9 -3 5
```

### 输出

```
2
```

## 样例 #3

### 输入

```
2 20
14 -7 19
```

### 输出

```
0
```

# 题解

## 作者：BYR_KKK (赞：0)

一种对所有 $P(x)$ 均适用，思维难度不高，带 $\log$ 的做法。

先枚举所有项，判断能否改变这个项，此时其它项就已经确定了，设和为 $s$，枚举到的这个项为 $a_i2^i$。则实际上就是判断 $a_i2^i+s=0$ 这个方程有无解。如果值域很小的话直接解，问题在于值域很大。考虑对其哈希，那么就是判断 $a_i2^i\equiv -s(\pmod P)$ 这个方程的解。移项，得到 $a_i\equiv -s+2^{-i}$，因此这个同余方程的解的形式是好判断的。注意我们只关心其 $\le k$ 的解，因此我们选取一个 $>k$ 的 $P$ 即可。同时注意负数解。

时间复杂度 $O(n\log V)$，我写的三模。

[代码](https://codeforces.com/contest/639/submission/287442904)

---

## 作者：樱雪喵 (赞：0)

## Description

定义一个多项式合法，当且仅当它满足：

- 系数是整数
- 任意项系数的绝对值小于等于 $k$
- 最高次项系数不为 $0$


给你一个 $n$ 次多项式 $P(x)=\sum\limits_{i=0}^n a_i x^i$，保证其合法且 $P(2)\neq 0$。

现在你可以改变 $P(x)$ 其中一项的系数，设新得到的多项式为 $Q(x)$。要求 $Q(x)$ 合法，且 $Q(2)=0$。求可能得到多少种不同的 $Q(x)$。

## Solution

发现我们只关心 $P(2)$ 和 $Q(2)$，不妨直接把 $2$ 代入原式，$P(2)=\sum\limits_{i=0}^n a_i 2^i$。

这个形式长得像个二进制，那么我们就把每个 $a_i\notin [0,1]$ 的系数向后进位，转换为一个二进制数。令 $P(2)=\sum\limits_{i=0}^{n+1} b_i 2_i$，其中除 $b_{n+1}$ 外的 $b_i$ 均为 $0$ 或 $1$。

那么只改一个系数 $a_i$ 使之变合法，即当前的 $P(2)$ 是 $2^i$ 的倍数。这在二进制下等价于 $<i$ 的 $b_j$ 均为 $0$。

找到第一个 $b_i\neq 0$ 的位置，从这里开始依次考虑答案，维护 $P(2)$ 是它的几倍。如果倍数已经 $>2k$ 就 `break` 掉即可。

```cpp
#define int long long
const int N=3e5+5;
int n,k,a[N],y[N];
signed main()
{
    n=read(),k=read();
    for(int i=0;i<=n;i++) a[i]=y[i]=read();
    for(int i=0;i<=n;i++)
    {
        if(a[i]>0) a[i+1]+=a[i]/2,a[i]=a[i]%2;
        else 
        {
            if(a[i]%2) a[i+1]+=a[i]/2-1,a[i]=1;
            else a[i+1]+=a[i]/2,a[i]=0;
        }
    }
    int st=n;
    for(int i=0;i<=n;i++) if(a[i]) {st=i;break;}
    int now=0;
    for(int i=n+1;i>st;i--) 
    {
        now=(now<<1)+a[i];
        if(abs(now)>2*k) break;
    }
    int ans=0;
    for(int i=st;i>=0;i--)
    {
        if(abs(now)>2*k) break;
        now=(now<<1)+a[i];
        if(abs(y[i]-now)<=k&&(i!=n||y[i]!=now)) ans++;
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

