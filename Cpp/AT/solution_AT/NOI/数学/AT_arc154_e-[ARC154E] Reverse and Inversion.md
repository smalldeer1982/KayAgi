# [ARC154E] Reverse and Inversion

## 题目描述

对于 $ (1,2,\dots,N) $ 的一个排列 $ Q=(Q_1,Q_2,\dots,Q_N) $，定义如下的值为 $ f(Q) $：

> 对于所有满足 $ 1\leq i $ 且 $ Q_i > Q_j $ 的整数对 $ (i,j) $，将所有 $ j-i $ 的和记为 $ f(Q) $。

给定 $ (1,2,\dots,N) $ 的一个排列 $ P=(P_1,P_2,\dots,P_N) $。

你需要重复以下操作 $ M $ 次：

- 选择满足 $ 1\leq i\leq j\leq N $ 的一组整数 $ (i,j) $。将 $ P_i,P_{i+1},\dots,P_j $ 反转。更具体地说，将 $ P_i,P_{i+1},\dots,P_j $ 的值同时替换为 $ P_j,P_{j-1},\dots,P_i $。

操作的选择方式共有 $ \left(\frac{N(N+1)}{2}\right)^M $ 种。对于所有这些操作结束后的 $ f(P) $，你需要求它们的总和，并对 $ 998244353 $ 取模。

## 说明/提示

### 限制条件

- $ 1\leq N,M\leq 2\times 10^5 $
- $ (P_1,P_2,\dots,P_N) $ 是 $ (1,2,\dots,N) $ 的一个排列。

### 样例解释 1

所有可能的操作如下，共有 $ 3 $ 种：

- 选择 $ (i,j)=(1,1) $。此时 $ P=(1,2) $，$ f(P)=0 $。
- 选择 $ (i,j)=(1,2) $。此时 $ P=(2,1) $，$ f(P)=1 $。
- 选择 $ (i,j)=(2,2) $。此时 $ P=(1,2) $，$ f(P)=0 $。

因此，答案为 $ 0+1+0=1 $。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 1
1 2```

### 输出

```
1```

## 样例 #2

### 输入

```
3 2
3 2 1```

### 输出

```
90```

## 样例 #3

### 输入

```
10 2023
5 8 1 9 3 10 4 7 2 6```

### 输出

```
543960046```

# 题解

## 作者：vegetable_king (赞：26)

在[博客](https://yjh965.github.io/post/arc154e-reverse-and-inversion-ti-jie/)食用更佳。

神奇的计数题。

首先考虑 $f(p)$ 的本质是什么。

$$\begin{aligned}
f(p) &= \sum_{1 \le i < j \le n,p_i > p_j} j - i\\
&= \sum_{1 \le i < j \le n,p_i > p_j} j - \sum_{1 \le i < j \le n,p_i > p_j} i\\
&= \sum_{i = 1}^n i\sum_{j = 1}^{i - 1}[p_i < p_j] - \sum_{i = 1}^n i\sum_{j = i + 1}^n [p_i > p_j]\\
&= \sum_{i = 1}^n i\left(\sum_{j = 1}^{i - 1}[p_i < p_j] - \sum_{j = i + 1}^n [p_i > p_j]\right)\\
\end{aligned}$$

这样，我们就成功的把 $j - i$ 拆成了 $i$ 和 $j$ 分别的贡献。然后，设 $g(i) = \sum_{j = 1}^{i - 1}[p_i < p_j] - \sum_{j = i + 1}^n [p_i > p_j]$，则 $f(p) = \sum_{i = 1}^n i \times g(i)$。

$$\begin{aligned}
g(i) &= \sum_{j = 1}^i[p_i < p_j] - \sum_{j = i + 1}^n [p_i\ge p_j]\\
&= i - \sum_{j = 1}^i[p_i \ge p_j] - \sum_{j = i + 1}^n [p_i \ge p_j]\\
&= i - \sum_{j = 1}^n[p_i \ge p_j]\\
&= i - p_i\\
\end{aligned}$$

我们就得出了 $f(p) = \sum_{i = 1}^n i(i - p_i)$ 的结论。

然后，我们就只需要求出初始在位置 $i$ 的元素操作 $m$ 次后到达的位置的期望 $s_i$，则答案为 $\binom{n + 1}2^m\sum_{i = 1}^n i^2 - s_i \times p_i$。

这个东西看着很棘手，怎么办呢？我们考虑继续挖掘性质。

我们考虑一个点 $i$。通过一次操作把它挪到点 $j$ 的方案数显然是 $\min(i, n - i + 1, j, n - j + 1)$，所以我们可以发现，把 $i$ 挪到 $j$ 的概率和挪到 $n - j + 1$ 的概率是一样的。

于是，无论一个点处在何位置，它受到操作影响之后，期望位置就会变为 $\frac{n + 1}2$。

所以一个点 $i$ 如果没被任何操作包含（概率为 $q = (1 - \frac{2i(n - i + 1)}{n(n+1)})^m$），它的期望位置就是 $i$；如果它被任意一个操作包含（概率为 $1 - q$），它的期望位置就是 $\frac{n + 1}2$。把两个综合一下，得到 $s_i = qi + (1 - q)\frac{n + 1}2$。

每个 $s_i$ 都可以 $O(\log m)$ 算，总时间复杂度为 $O(n \log m)$。

---

## 作者：luogubot (赞：14)

对于排列 $q$，定义 $f(q)=\sum_{i<j,q_i>q_j}(j-i)$。给定排列 $p_{1\cdots n}$ 以及 $m$，执行 $m$ 次以下操作：

- 随机选择 $1\leq i\leq j\leq n$，翻转 $p_{i\cdots j}$。

对于 $\left(\frac{n(n+1)}{2}\right)^m$ 种可能操作，求最终的 $f(p)$ 之和 $\bmod 998244353$ 的值。

$n,m\leq 2\times 10^5$。

#### 如何求 $f(p)$

定义 $q_i$ 为 $p$ 的逆排列，注意 $q$ 和 $p$ 的对称性。

对于值为 $i$ 来拆贡献：$\sum_{i}(\sum_{j<i\land q_i<q_j}1-\sum_{j>i\land q_i>q_j}1)\times q_i$。交换 $i$ 与前一个元素，讨论得无论前一个数与它的大小关系，括号里的值总会减少 1。同样地，交换其与后一个元素，括号里的值总会增加 1。对于 $p_i=q_i=i$ 时，括号里的值是 0，则最终 $f(p)=\sum (q_i-i)q_i=\sum(i-p_i)i=\sum i^2-i\times p_i$。

#### 如何求 $\sum i\times p_i$

求出期望之后乘可能数就是和。于是转而求 $\sum i\times p_i$ 的期望，对称为 $\sum i\times q_i$，不妨求 $\sum i\times E(q_i)$，即每个 $p_x=i$ 的最终位置的期望。接下来是一个重要观察：

> 若 $x$ 被操作到且翻转到 $y$，则一定有同样概率的 $x$ 被翻转到了 $n-y+1$。

这是因为，$x$ 翻转到 $y$ 的方案数为 $\min\{x,n-x+1,y,n-y+1\}$，则翻转到 $n-y+1$ 显然方案数相同。也就是如果被某次操作包括，其对应位置的期望值一定是 $\frac{y+n-y+1}{2}=\frac{n+1}{2}$，与 $x$ 无关。

不妨设 $p=\frac{\binom{x}{2}+\binom{n-x+1}{2}}{\binom{n+1}{2}}$，即一次操作**不**包括位置 $x$ 的概率。则如果 $m$ 次操作里至少有一次包含了位置 $x$，则最终它的位置期望是 $\frac{n+1}{2}$。则初始位置为 $x$ 最终位置期望为 $p^m\times x+(1-p^m)\times \frac{n+1}{2}$。

至此，可以以 1log 的复杂度内计算出 $E(\sum i\times p_i)$，进而求出所需的和。

---

## 作者：tzc_wk (赞：7)

只要你发现是诈骗题就好办了。不要像我那样傻傻地瞪一个小时然后才发现那俩 sigma 里的东西相减是有性质的。

先考虑计算单个 $f(p)$，一眼的树状数组……吗？考虑最终答案式子里 $i$ 的系数：$\sum\limits_{j<i}[p_j>p_i]-\sum\limits_{j>i}[p_j<p_i]$，因为 $\sum\limits_{j<i}[p_j>p_i]+\sum\limits_{j<i}[p_j<p_i]=i-1$，$\sum\limits_{j<i}[p_j<p_i]+\sum\limits_{j>i}[p_j<p_i]=p_i-1$，所以两者相减可以得到 $\sum\limits_{j<i}[p_j>p_i]-\sum\limits_{j>i}[p_j<p_i]=i-p_i$。于是 $f(p)=\sum\limits_{i=1}^n(i^2-ip_i)$。

$\sum i^2$ 是定值。考虑计算 $E(\sum ip_i)$。发现一个很重要的性质：对于一个当前在位置 $i$ 的数，只要下一次操作区间包含 $i$，那么 $\forall j$，下一步操作到达 $j$ 的概率和到达 $n-j+1$ 的概率是完全相同的。也就是说考虑一个位置 $i$ 上的数 $p_i$，如果其被操作至少一次，那么最终 $p_i$ 所在位置的期望值就是 $\dfrac{n+1}{2}$，因此最终 $p_i$ 位置的期望值可以容易算出。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5;
const int MOD=998244353;
const int INV2=MOD+1>>1;
int qpow(int x,int e){int ret=1;for(;e;e>>=1,x=1ll*x*x%MOD)if(e&1)ret=1ll*ret*x%MOD;return ret;}
int n,m,p[MAXN+5],res;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&p[i]);
	for(int i=1;i<=n;i++){
		int p0=1ll*(1ll*i*(i-1)/2+1ll*(n-i)*(n-i+1)/2)%MOD*qpow(1ll*n*(n+1)/2%MOD,MOD-2)%MOD;
		res=(res+1ll*i*i)%MOD;
		res=(res-(1ll*qpow(p0,m)*p[i]%MOD*i+1ll*(1-qpow(p0,m)+MOD)*p[i]%MOD*(n+1)%MOD*INV2)%MOD+MOD)%MOD;
	}printf("%d\n",1ll*res*qpow(1ll*n*(n+1)/2%MOD,m)%MOD);
	return 0;
}
```


---

## 作者：OIerBoy (赞：6)

# Update :2023.8.28修改一处笔误
这是一道很妙的计数题，考试的时候没想到。

这道题我们首先会想到去化简一下式子 $\sum\limits_{i<j,p_i>p_j}(j-i)$，这很明显是要求逆序对，但是这个 $(j-i)$ 就对我们来说有点棘手，所以很容易想到去将 $i,j$ 拆开分别计算贡献：$\sum\limits_{i<j,p_i>p_j}j-\sum\limits_{i<j,p_i>p_j}i$。

拆开之后我们就需要有一个主次关系，即以 $i$ 或者 $j$ 的视角来继续化简式子，这里我们以 $i$ 的视角入手，我们需要找到 $i$ 前面比 $p_i$ 大的，以及后面比 $p_i$ 小的差：

$$\begin{aligned}&\sum\limits_{i=1}^ni\sum\limits_{j=1}^{i-1}[p_i<p_j]-\sum\limits_{i=1}^ni\sum\limits_{j=i+1}^n[p_i>p_j]\\ = & \sum\limits_{i=1}^ni\left(\sum\limits_{j=1}^{i-1}[p_i<p_j]-\sum\limits_{j=i+1}^n[p_i>p_j]\right)\end{aligned}$$

好了，现在我们已经将 $j-i$ 的贡献拆开计算了，但是由于 $[p_i<p_j]$ 和 $[p_i>p_j]$ 的符号方向不同，我们也只能分开计算，如何才能将符号统一呢。很简单，只需要将 $\sum\limits_{j=1}^i[p_i<p_j]$ 旋转一下。

$$\begin{aligned}& \sum\limits_{i=1}^ni\left(\sum\limits_{j=1}^{i-1}[p_i<p_j]-\sum\limits_{j=i+1}^n[p_i>p_j]\right)\\=& \sum\limits_{i=1}^ni\left(\sum\limits_{j=1}^i[p_i<p_j]-\sum\limits_{j=i+1}^n[p_i\ge p_j]\right)\\= & \sum\limits_{i=1}^ni\left(\left(i-\sum\limits_{j=1}^i[p_i>p_j]\right)-\sum\limits_{j=i+1}^n[p_i>p_j]\right)\\= &\sum\limits_{i=1}^ni\left(i-\sum\limits_{j=1}^n[p_i>p_j]\right)\end{aligned}$$

由于题目说了 $p$ 是一个 $1\sim n$ 的排列，那么比 $p_i$ 小于等于的数有多少个能，当然是 $p_i$ 个啦。这样我们就得到：

$$\begin{aligned} &\sum\limits_{i<j,p_i>p_j}(j-i)\\=& \sum\limits_{i=1}^ni(i-p_i)\\=& \sum\limits_{i=1}^ni^2-p_i\times i\end{aligned}$$

这里 $i^2$ 是好处理的，但是 $p_i\times i$ 不好处理，因为 $p_i$ 的位置是不断在变化的。我们为了更好的处理就定义 $w_i$ 表示 $p_i$ 的最终所在位置，即 $\sum\limits_{i=1}^ni^2-p_i\times w_i$。

但由于 $m\le 2\times 10^5$，是没法暴力处理。因此需要用一个操作：将求和改为求期望位置。这个操作的意义感觉是由下文结果体现的。

我们考虑翻转操作的本质是什么。假设对于 $i$ 位置的值，若要将其翻转到 $j$。考虑有多少种操作可行

显然，翻转的中心就是 $\dfrac{i+j}{2}$。

- 当 $i<j$ 时，方案数为 $\min(i,n-j+1)$。
- 当 $i>j$ 时，方案数为 $\min(j,n-i+1)$。

由于分类讨论显然很烦，所以我们就要尝试将它们合并。可以发现，当 $i<j$ 时，$n-i+1>n-j+1$，而 $i>j$ 同理，所以两种情况是可以合并在一起为 $\min(i,n-i+1,j,n-j+1)$ 的。然后，我们就会发现把 $i$ 翻转到 $j$ 的概率与翻转到 $n-j+1$ 的概率是相等的，那么它的总贡献就是 $n-j+1+j=n+1$ 平均期望位置就是 $\dfrac{n+1}{2}$,这样我们就将 $i,j$ 的贡献给成功剔除了，而如果 $i$ 没有进行翻转，则期望位置就是 $i$，不妨设 $k=\dfrac{C_{i}^2+C_{n-i+1}^2}{C_{n+1}^2}$，即一次操作不包括位置 $x$ 的概率。

这样 $w_i$ 的期望值我们就可以算出来了：
$$w_i=k^m\times i+(1+k^m)\times \frac{n+1}{2}$$

这样这道题我们就做出来了，时间复杂度为 $O(n\log m)$，可以通过，它唯一的复杂度瓶颈就在于快速幂。

感谢 @[Populus_euphratica](https://www.luogu.com.cn/user/754919) 和 @[MoriyaSuwako](https://www.luogu.com.cn/user/590600) 指出错误

---

## 作者：Isharmla (赞：2)

好题。

不妨先考虑一下 $f(p)$ 怎么搞。通过题面我们可以知道，$f(p)=\sum_{i \lt j} [P_i \gt P_j](j - i)$。我们不妨考虑先拆拆拆，我们直接将 $i$ 和 $j$ 分离开来。然后你再搞搞，可以得到一个式子。
$$\sum_{i=1} i\times(\sum_{j=1}^{i-1}[p_i\lt p_j]-\sum_{j=i+1}^n[p_i\gt p_j])$$ 
相等于就是对 $i$ 来说，单独计算一下他的贡献。先看第一个括号里面第一个求和式子，在存在 $p_i \lt p_j$ 的时候，因为 $i\gt j$ 所以对答案是 $i-j$ 的贡献，在只看 $i$ 的情况下，他的贡献是正的。然后看第二个式子在存在 $p_i\gt p_j$ 的时候，贡献计算的是 $j-i$ 的情况，只看 $i$ 的情况下，他的贡献是负的，所以这个式子本质上就是让我们直接用正贡献减去负贡献。这个式子的问题在哪里？问题在于我们要求 $p_i \lt p_j$ 和 $p_i \gt p_j$，这其实是非常恶心的，所以我们需要想办法把他们同号。

我们把目光看向题目，看看有没有什么性质还没有发觉。很快，我们注意到 $p$ 是一个排列，在这一题中，这是一个很棒的性质，我们知道了有多少个数比 $p_i$ 小了！我们就可以把 $p_i\lt p_j$ 修改了。我们直接容斥出 $p_i \lt p_j$ 即可。式子再一次修改。
$$\sum_{i=1} i \times (i-\sum_{j=1}^{i}[p_i\gt p_j]-\sum_{j=i+1}^n[p_i\gt p_j]))$$ 

我们合并式子。
$$f(p)=\sum_{i=1}i\times (i-p_i)$$

问题是什么，问题在于 $i^2$ 是一个定值，但是 $i\times p_i$ 不是一个定值。我们再次转换，我们考虑 $p$ 变换后的最终位置 $s$，得到 $i^2-p_is_i$。

此时存在有一个很妙的做法，我们直接把求和改成求期望位置。这样我们的位置就很好搞了。我们考虑从 $i$ 翻转到 $j$ 有多少种方法，注意此时的 $i$ 和 $j$ **并不存在位置关系**，只是**随手的两个位置**。旋转 $i$ 和 $j$ 的情况下，旋转点一定只会存在一个 $\frac{i+j}{2}$。我们考虑有多少种旋转方法，考虑 $i\lt j$ 和 $i \gt j$ 两种情况，显然答案方案数就是 $2\times \min(i,j,n-i+1,n-j+1)$。考虑之后的位置，我们从 $i$ 翻转到了 $n-j+1$。也就是说，期望位置就是 $\frac{n+1}{2}$。

我们直接通过求出不被包含的概率，由此搞出 $s$。带入 $i^2-p_is_i$ 即可。

---

## 作者：Filberte (赞：1)

先考虑对于一个固定的排列 $p$，如何求 $f(p)$ 的值。对于每个位置 $i$，其贡献献肯定是 $i$ 的若干倍。尝试写出它的系数：
$$
\sum\limits_{j < i}[p_j > p_i] - \sum\limits_{j > i}[p_j < p_i]
$$
有两个显然的结论：
$$
\sum\limits_{j < i}[p_j > p_i] + \sum\limits_{j < i}[p_j < p_i] = i - 1\\
\sum\limits_{j < i}[p_j < p_i] +\sum\limits_{j > i}[p_j < p_i] = p_i - 1
$$
两式相减，可得：
$$
\sum\limits_{j < i}[p_j > p_i] - \sum\limits_{j > i}[p_j < p_i] = i - p_i
$$
由此位置 $i$ 的贡献为 $i(i-p_i)$，有： 
$$
f(p) = \sum\limits_{i = 1}^n (i^2 - ip_i) = \dfrac{n(n+1)(2n+1)}{6} - \sum\limits_{i = 1}^n ip_i
$$
原题要求的是所有 $k = (\dfrac{n(n+1)}{2})^m$ 中可能情况的 $f$ 的和，先计算期望，最后乘上 $k$ 即可。我们需要对每个 $p_i$ 求出其最终位置的期望值。

接下来是一个重要观察：若 $p_i$ 原本在位置 $x$ 被操作过且到达位置 $y$，则其有等概率到达位置 $n - y + 1$。这是因为欲使 $x$ 到达位置 $y$，必定以 $\dfrac{x + y}{2}$ 为翻转中心，一共有 $\min\{x,n - y + 1,y,n - x + 1\}$ 种可选择的区间，把 $y$ 换成 $n - y + 1$ 后不会改变区间个数。由此一个位置 $x$ 只要被操作过，最终的期望位置就是 $\dfrac{n + 1}{2}$。

所以对于一个位置 $x$ 而言，其最终的期望位置只与是否有操作包含它有关。若其留在原地，要求每个操作都不包含它，概率为$p_{stay} =(1- \dfrac{2x(n - x + 1)}{n(n+1)})^m$，对最终期望位置的贡献为 $x\cdot p_{stay}$；否则至少有一个操作包含它，对最终期望位置的贡献为 $\dfrac{n+1}{2}(1 - p_{stay})$。

根据上式计算答案即可。	

```c++
#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int N = 2e5 + 100;
const int mod = 998244353, iv2 = (mod + 1) / 2;
int n, m, ans;
int ksm(int a, int b = mod - 2){
    int r = 1;
    while(b){
        if(b & 1) r = r * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return r;
}
int S1, S2;
int32_t main(){
    cin >> n >> m;
    int al = n * (n + 1) / 2 % mod, ival = ksm(al);
    for(int x = 1, p;x <= n;x++){
        cin >> p;
        int nc = ksm((1 - x * (n - x + 1) % mod * ival % mod + mod) % mod, m);
        int p1 = x * nc % mod;
        int p2 = (n + 1) * iv2 % mod * (1 - nc + mod) % mod;
        S1 = (S1 + x * x) % mod;
        S2 = (S2 + (p1 + p2) * p) % mod;
    }
    ans = (S1 - S2 + mod) * ksm(al, m) % mod;
    cout << ans << endl;
}
```

---

## 作者：s4CRIF1CbUbbL3AtIAly (赞：1)

因为直接求和不太好算，所以先考虑期望如何计算。

我们考虑 $f(P)$ 的计算方法：

$$\begin{array}{rcl}
f(P)&=&\sum\limits_{i<j}[P_i>P_j](j-i)\\
&=&(\sum\limits_{i<j,P_i>P_j}j)-(\sum\limits_{i<j,P_i>P_j}i)\\
&=&(\sum\limits_i\sum\limits_{j<i}[P_i<P_j])-(\sum\limits_i\sum\limits_{j>i}[P_i>P_j])\\
&=&\sum\limits_ii(\sum\limits_{j<i}[P_i<P_j]-\sum\limits_{j>i}[P_i>P_j])\\
&=&\sum\limits_ii(i-\sum\limits_{j\le i}[P_i\ge P_j]-\sum\limits_{j>i}[P_i>P_j])\\
&=&\sum\limits_ii(i-P_i)\\
&=&(\sum\limits_ii^2)-(\sum\limits_iiP_i)
\end{array}$$

因此，我们想要知道 $E(f(P))$ 就只需要知道 $E(\sum iP_i)$。

对于一个位置 $i$，它在一次操作后换到 $j$ 的方案数为 $\min(i,j,n-i+1,n-j+1)$。容易发现这是对称的，也就是说如果这个位置被翻转的区间包含，那么它的期望位置就变为了 $\dfrac{n+1}2$。

一次操作不包含位置 $i$ 的概率 $p=\dfrac{x(x-1)+(n-x)(n-x+1)}{n(n+1)}$。

经过上面的分析，经过一次操作后期望位置要么不变要么变为 $\dfrac{n+1}2$，而只要 $m$ 次中任意一次操作区间包含 $i$ 那么它的期望位置就会变为 $\dfrac{n+1}2$，因此初始位置为 $i$ 的数最终期望位置为 $p^mx+(1-p^m)\cdot\dfrac{n+1}2$。

$E(\sum iP_i)=E(\sum i\times pos_i)=\sum i\times E(pos_i)$，所以直接将每个位置操作后的期望位置乘上对应的值再整体相加即可得到 $E(\sum iP_i)$，再用 $\sum i^2$ 相减可以得到 $E(f(P))$，最后乘上总方案数 $(\dfrac{n(n+1)}2)^m$ 即可。

代码比较丑陋。

```cpp
void __SOLVE__(){
	cin>>n>>m;
	for(ll i=1;i<=n;i++)cin>>a[i];
	ll ans=0,s=0;
	for(ll i=1;i<=n;i++)(ans+=i*i%mod)%=mod;
	for(ll i=1;i<=n;i++){
		ll p=(i*(i-1)%mod+(n-i)*(n-i+1)%mod)%mod*qpow(n*(n+1)%mod,mod-2)%mod;
		ll tmp=(qpow(p,m)*i%mod+(1+mod-qpow(p,m))*(n+1)%mod*((mod+1)/2)%mod)%mod;
		s=(s+tmp*a[i]%mod)%mod;
	}
	(ans+=mod-s)%=mod;
	cout<<ans*qpow(1ll*n*(n+1)/2,m)%mod<<"\n";
}
```

---

## 作者：DaiRuiChen007 (赞：1)

# ARC154E 题解

[Problem Link](https://www.luogu.com.cn/problem/AT_arc154_e)

**题目大意**

> 给定一个 $1\sim n$ 的排列 $p$，$m$ 次操作，每次随机一对 $1\le l\le r\le n$ 并翻转 $p_l\sim p_r$。
>
> 对于最终的每个排列 $q_1\sim q_n$，计算 $\sum_{i<j} [q_i>q_j](j-i)$。
>
> 数据范围：$n,m\le 2\times 10^5$。

**思路分析**

考虑计算每个 $i$ 对答案贡献的系数，容易发现这就是：
$$
\begin{aligned}
\sum_{j<i}[q_j>q_i]-\sum_{i<j} [q_i>q_j]
&=(i-1)-\sum_{j<i}[q_j<q_i]-\sum_{i<j} [q_i>q_j]\\
&=(i-1)-(q_i-1)=i-q_i
\end{aligned}
$$
因此答案就是 $\sum i^2-i\times q_i$，第一部分很好统计，我们只需要对于每个 $p_i$ 求出其最终所在位置的期望。

可以发现对于每个 $i$，一次操作后使得 $i\to j$ 的方案数与使得 $i\to n-j+1$ 的方案数是相等的。

因此对于每个 $i$，有 $\left(1-\dfrac{i(n-i)}{n(n+1)/2}\right)^m$ 的概率留在原地，剩下的情况所在位置的期望是 $\dfrac{n+1}2$。

那么就可以快速计算每个 $p_i$ 最终位置的期望。

时间复杂度 $\mathcal O(n\log P)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=2e5+5,MOD=998244353,i2=(MOD+1)/2;
ll ksm(ll a,ll b=MOD-2,ll p=MOD) {
	ll ret=1;
	for(;b;a=a*a%p,b=b>>1) if(b&1) ret=ret*a%p;
	return ret;
}
int n,m,p[MAXN];
signed main() {
	scanf("%d%d",&n,&m);
	ll ans=0,tot=1ll*n*(n+1)/2%MOD;
	for(int i=1;i<=n;++i) {
		scanf("%d",&p[i]);
		ll pr=ksm((1+MOD-1ll*i*(n-i+1)%MOD*ksm(tot)%MOD)%MOD,m);
		ans=(ans+1ll*i*i%MOD)%MOD;
		ans=(ans+MOD-1ll*pr*i%MOD*p[i]%MOD)%MOD;
		ans=(ans+MOD-1ll*(n+1)*i2%MOD*(1+MOD-pr)%MOD*p[i]%MOD)%MOD;
	}
	ans=ans*ksm(tot,m)%MOD;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：ducati (赞：1)

去年一月随手切了，今年二月啥也不会，怎么这么菜呢？

## Description

[洛谷传送门](https://www.luogu.com.cn/problem/AT_arc154_e)

[AT 传送门](https://atcoder.jp/contests/arc154/tasks/arc154_e)

## Solution

令 $P(i) = \sum_{j = 1} ^ {i - 1} [p_j > p_i]$，$Q(i) = \sum_{j = i + 1} ^ n [p_i > p_j]$，则 $f(p) = \sum_{i = 1} ^n i (P(i) - Q(i))$。 

将每个 $(i, p_i)$ 看做二维平面上的点，则 $P(i)$ 为 $(i, p_i)$ 左上方的点数，$Q(i)$ 为 $(i, p_i)$ 右下方的点数。而左上方点数 $-$ 右下方点数 $=$ 左侧点数 $-$ 下方点数 $= (i - 1) - (p_i - 1) = i - p_i$，因此 $f(p) = \sum_{i = 1} ^n i(i - p_i)$。

考虑求 $f(p)$ 的期望。令 $occ(x)$ 为 $x$ 最终位置的下标，则有 $E(f(p)) = E\left(\sum_{i = 1} ^n i^2\right) - \sum_{i = 1}^n p_i E(occ(p_i))$，转化为求所有 $E(occ(p_i))$。

注意到，若某次操作区间包含 $p_i$，则 $p_i$ 最终期望下标为 $\frac {n + 1} {2}$。这是因为，$\forall u, v$，$p_u$ 经过一次操作后移动到 $v$ 和 $n - v + 1$ 的概率均等，具有对称性。此外，每次操作均不含 $p_i$ 也有可能，需要特判。

时间复杂度 $O(n)$。

## Summary

- 首先必须发现，$f(p)$ 具有简洁的表达式，与具体逆序对无关。
  - 可以考虑数形结合，将 $(i, p_i)$ 视作二维平面上的点，并借助割补法得到 $P(i) - Q(i)$ 的表达式。
  - **启发**：若式子中含有 $[p_i > p_j]$ 等与逆序对 / 顺序对有关的信息，或许能简化将此条件去掉。
- 其次需要注意到对称性，以便计算 $occ$。
  - **启发**：在一类计算最终位置下标期望的题型中，若在满足特定条件的基础上，对于对称的位置 $i, j$，最终移动到 $i, j$ 的概率均等，那么这是一个相当强的性质。

## Code

```cpp
// Submission Time: 2023-01-23 09:40:13
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,mod=998244353,inv2=(mod+1)/2;

int read(){
    int s=0,w=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if (ch=='-')  w=-w;ch=getchar();}
    while (ch>='0'&&ch<='9'){s=(s<<1)+(s<<3)+(ch^'0');ch=getchar();}
    return s*w;
}
int n,m,ep,res,a[N],F[N];
int Down(int x){return(x>mod)?(x-mod):x;}
int quick_power(int x,int y){
	int res=1;
	for (;y;y=y>>1,x=(x*x)%mod){
		if (y&1)  res=(res*x)%mod;
	}
	return res;
}
signed main(){
	n=read(),m=read(),ep=(n+1)*inv2%mod;
	for (int i=1;i<=n;i++)  a[i]=read();
	for (int i=1;i<=n;i++)  F[i]=Down(F[i-1]+i),res=(res+i*i)%mod;
	for (int i=1,dt=quick_power(F[n],mod-2);i<=n;i++){
		int prob=quick_power((F[i-1]+F[n-i])*dt%mod,m);
		int contrib=(prob*i+(mod+1-prob)*ep)%mod;
		res=(res-contrib*a[i])%mod;
	}
	cout<<(res+mod)*quick_power(F[n],m)%mod,exit(0);
}
```



---

## 作者：RedreamMer (赞：1)

刚开始看错题了，注意一对逆序对 $(i, j)$ 的贡献是 $j - i$。
  
  那么我们要计算的就是
  
  $$
  \sum_{i = 1} ^ n \sum_{j = 1} ^ n [j < i \land a_j > a_i]i - [j > i \land a_j < a_i]i
  $$
  
  对于每一个 $i$，发现我们要计算的后面的一大串和式加起来其实是一个定值，具体来说，对于任意排列 $a_i$，$i$ 左侧大于 $a_i$ 的数的个数减去右侧小于 $a_i$ 数的个数为 $i - a_i$，通过交换左右两侧的数不难证明。
  
  也就是说，我们要求
  
  $$
  \sum_{i = 1} ^ n i(i - a_i)
  $$
  
  也就是求每个位置 $i$ 的数经过 $m$ 次变换到位置 $j$ 产生的贡献，直接做是 $\mathcal O(n ^ 3 \log m)$ 的，但是（打表）发现对于一排的系数是富有规律的，似乎是对称的（除了个别位置）。
  
  解释这个规律，对于位置为 $i$ 的数，若至少离开 $i$ 一次，那么最后到达 $j$ 的方案数一定和到达 $n + 1 - j$ 的方案数相同，只需要讨论方案的最后一步有效操作即可，假设是从 $i \to j$，那么方案数是 $\min(\min(i, n - i + 1), \min(j, n - j + 1))$，而 $i \to n + 1 - j$ 的式子也是这个式子，因此方案数是相同的，系数也自然左右对称。
  
  因此在我们计算过程中，系数相同的两部分可以合并起来一起计算，具体来说
  
$$
\sum_{x = 1} ^ n \sum_{i = 1} ^ n -E_{value\_x\_to\_i} ix
$$
$$
= \sum_{x = 1} ^ n \frac {\sum_{i = 1} ^ n -E_{value\_x\_to\_i} (n + 1) x} 2
$$
$$
= \frac {\sum_{x = 1} ^ n (n + 1) x \sum_{i = 1} ^ n -E_{value\_x\_to\_i}} 2
$$
  
  发现我们只需要对一排的系数求和，那么就是求权值 $x$ 至少移动一次的方案数，这很容易实现。
  
  前面漏掉的就是每个位置的数一步不动的贡献，这直接算就好了。
  
  最后时间复杂度 $\mathcal O(n \log m)$。

---

## 作者：Re_Star (赞：0)

[题面](https://www.luogu.com.cn/problem/AT_arc154_e)

[更好的阅读体验](https://www.cnblogs.com/Re-Star/p/18802784)

题目要求的就是对于每种操作方案得到的排列中，所有逆序对位置之差的和。

首先我们考虑对于一个确定的排列 $p$,它对答案的贡献如何表示，对于第 $i$ 位，每有一个 $j<i$ 且 $p_j>p_i$ 时会产生 $i$ 的贡献，同时每有一个 $j>i$ 且 $p_j<p_i$ 时会产生 $-i$ 的贡献，于是我们令第 $i$ 位贡献为 $f(i)$，那么 $f(i)$ 可以表示为：
$$
\begin{aligned}
f(i)&=i(\sum\limits_{j=1}^i[p_j>p_i]-\sum\limits_{j=i+1}^n[p_j\le p_i])\\
&=i(i-\sum\limits_{j=1}^i[p_j\le p_i]-\sum\limits_{j=i+1}^n[p_j\le p_i])\\
&=i(i-\sum\limits_{j=1}^n[p_j\le p_i])\\
&=i^i-i\times p_i
\end{aligned}
$$
现在我们考虑如何统计所有方案的权值和，这里我们可以求 $\sum_{i=1}^ni^2-i\times p_i$ 的期望值，然后再乘上方案数。这里前面的 $i^2$ 求和是一个定值，因为无论排列如何变化，最终 $1$ 至 $n$ 都会占满 $1$ 至 $n$ 的位置。所以要求的就是 $\sum_{i=1}^ni^2-\sum_{i=1}^n iE(p'_i)$ 

关键在于求位置的期望值，看起来似乎很困难，但是细想一下，位置 $i$ 如果被操作区间覆盖了，经过这一次操作到 $j$ 的方案数应该是多少。

- 如果 $j>i$ 有 $\min(i,n-j+1)$ 种方案。
- 如果 $j<i$ 有 $\min(j,n-i+1)$ 种方案。
   我们把两种情况合并一下，得到方案数为 $\min(i,j,n-i+1,n-j+1)$。所以 $i$ 经过一次操作到 $n-j+1$ 的方案数是一样的，也就相当于概率是一样的。所以对于任何一个位置，当它被操作区间覆盖时，最终位置的期望值都是$\frac n2$，而不被覆盖时就会留在原地。现在就很好求了，位置 $i$ 不被覆盖的概率为 $1-\frac{2i(n-i+1)}{n(n+1)}$,那么 $m$ 次操作都不被覆盖的概率就是 $q=(1-\frac{2i(n-i+1)}{n(n+1)})^m$，则 $E(p_i)=iq+\frac n2(1-q)$ ，这道题就做完了。
  
code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=2e5+5,mod=998244353;
ll n,m,ans;
inline ll rd()
{
	char c;ll f=1;
	while(!isdigit(c=getchar())) if(c=='-')f=-1;
	ll x=c-'0';
	while(isdigit(c=getchar())) x=x*10+(c^48);
	return x*f;
}
ll qp(ll x,ll y)
{
	ll res=1;
	while(y)
	{
		if(y&1) (res*=x)%=mod;
		(x*=x)%=mod,y>>=1;
	}
	return res;
}
ll S(ll i)
{
	ll p=2*i*(n-i+1)%mod*qp(n*(n+1)%mod,mod-2)%mod;ll p0=qp(1-p+mod,m);
	return (p0*i%mod+(1-p0+mod)*(n+1)%mod*qp(2,mod-2)%mod)%mod;
}
int main() 
{
	n=rd(),m=rd();
	for(ll i=1;i<=n;i++) (ans+=(i*i%mod-S(i)*rd()%mod+mod)%mod)%=mod;
	cout<<ans*qp((n+1)*n/2%mod,m)%mod;
	return 0;
}
```

---

## 作者：Aiopr_2378 (赞：0)

### 解题思路

先考虑给定的一个排列 $A=a_1,a_2,\cdots,a_n$ 的贡献：

$$
\begin{aligned}
f(A)&=\sum_{i=1}^n\sum\limits_{j=i+1}^n [a_i>a_j](j-i) \\
&=\sum_{i=1}^n\sum\limits_{j=i+1}^n[a_i>a_j]j-\sum_{i=1}^n\sum\limits_{j=i+1}^n[a_i>a_j]i \\
&=\sum\limits_{i=1}^n i \sum\limits_{j=1}^{i-1}[a_i<a_j]-\sum_{i=1}^n i\sum_{j=i+1}^n[a_i>a_j] \\
&=\sum_{i=1}^ni\left( \sum_{j=1}^{i-1}[a_i<a_j]-\sum_{j=i+1}^n[a_i>a_j]\right) \\
&=\sum_{i=1}^n i \left(i-\sum_{j=1}^i[a_i\ge a_j]+\sum_{j=i+1}^n[a_i>a_j]\right) \\
&=\sum_{i=1}^n i \left( i-\sum_{j=1}^n[a_i\ge a_j]\right) \\
&=\sum_{i=1}^n i \left(i-a_i\right)
\end{aligned}
$$

则对于最终的每一种形成的排列 $A$，计算 $f(A)=\sum_{i=1}^n i^2-\sum_{i=1}^n ia_i$ 即可。我们只关心 $\sum_{i=1}^n ia_i$ 怎么求解。因为最终形成的共有 $T=\left(\frac{n(n+1)}2 \right)^m$ 种排列，不能一一计算，遂考虑初始排列的每个 $a_i$ 的最终位置的期望，最后乘上次数 $T$ 即可。

先考虑只经过一次操作，一个在 $x$ 号位置上的数 $a_x$ 最终可能会变到哪个位置。

若这次操作不包含 $x$ 号位置，则此次操作的概率为

$$
p=\dfrac{x(x-1)+(n-x)(n-x+1)}{n(n+1)}
$$

，并且这次操作之后还在位置 $x$。

若这次操作包含 $x$ 号位置，则此次操作的概率为 $1-p$，接下来分析它去往每个位置的期望。设这次操作之后它会变换到位置 $y$，分别考虑 $y$ 与 $x$ 的相对位置（谁前谁后），则满足这个限制的操作方案数为 $\min\{x,n-y+1,y,n-x+1\}$。不难发现，将 $x$ 变换到 $y$ 与变换到 $n-y+1$ 的操作方案数是一样的。那么这次操作之后它的期望变换位置就是 $\frac{n+1} 2$。

分析完上述两种情况，不难得出 $m$ 次操作之后位置 $x$ 的数最后的期望位置为

$$
E_x=p^mx+(1-p^m)\frac{n+1} 2
$$

则答案为

$$
\sum f(A)=\left(\frac{n(n+1)} 2\right)^m\left(\sum_{i=1}^n i^2-\sum_{i=1}^nE_ia_i\right)
$$

算上快速幂与逆元的复杂度，总时间复杂度为 $O(n\log n)$。

### 参考代码

```cpp
#include<iostream>
using namespace std;
#define MAXN 200005
#define mod 998244353
typedef long long ll;
ll n,m,a[MAXN],E[MAXN],P[MAXN],ans;
ll qpow(ll a,ll b){
    ll w=1;
    a%=mod;
    while(b){
        if(b&1) w=w*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return w;
}
inline ll inv(ll x){return qpow(x,mod-2);}
int main(){
    ios::sync_with_stdio(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(ll x=1;x<=n;x++){
        P[x]=(x*(x-1)+(n-x)*(n-x+1))%mod*inv(n*(n+1))%mod;
    }
    for(ll x=1;x<=n;x++){
        E[x]=(qpow(P[x],m)*x+(1ll-qpow(P[x],m)+mod)*(n+1)%mod*inv(2))%mod;
    }
    ll T=qpow(n*(n+1)/2%mod,m);
    for(ll i=1;i<=n;i++) ans=(ans+i*i)%mod;
    ans=ans*T%mod;
    for(ll i=1;i<=n;i++) ans=(ans-E[i]*a[i]%mod*T)%mod;
    ans=(ans%mod+mod)%mod;
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：masonpop (赞：0)

神仙题。

先化总和为期望，然后考虑对于确定的排列，如何求其权值 $f(p)$。

看上去是个数据结构，实际上是个诈骗东西。你考虑 $i$ 的系数为 $\sum\limits_{j<i}[p_j>p_i]-\sum\limits_{j>i}[p_j<p_i]$。实际上这个东西是可以算出来的，恰好等于 $i-p_i$。如果你将已知的恒等式全列出来不难得到证明。

那么期望就是 $\sum\limits_{i=1}^n(i^2-ip_i)$。前者是定值，考虑求 $\sum\limits_{i=1}^niE(p_i)$。注意到关键性质：**如果 $i$ 被操作至少一次，则 $E(p_i)$ 必为 $\dfrac{n+1}{2}$**。

考虑证明。假设你由位置 $i$ 翻到了 $j$，不妨设 $j\le i$。考虑两种情况：

① 若 $n-j+1\ge i$，那么翻到位置 $j$ 和 $n-j+1$ 的概率分别为 $\min(i,j)$ 和 $\min(j,n-i+1)$，不难发现均等于 $j$。

② 若 $n-j+1<i$。此时两部分概率分别为 $\min(j,n-i+1)$ 和 $\min(n-j+1,n-i+1)$，两者均等于 $n-i+1$。

（之前这部分证明考虑不周，感谢管理提醒）

那么就可以直接计算了。[代码](https://www.luogu.com.cn/record/139511585)。

---

## 作者：AtomAlpaca (赞：0)

## 题意

给定 $n,m$ 两个正整数和一个 $n$ 的排列 $P$。重复进行如下操作 $m$ 次：

- 选定 $1\le i\le j\le n$，并将 $P_i,P_{i+1},..,P_j$ 翻转。

对于所有 $(\frac{n(n+1)}{2})^m$ 种方案，计算 $\sum_{i<j}[P_i>P_j](j-i)$ 的值的和。

集训讲题推荐题目，感觉很厉害。

## 题解
首先对所有方案统计有点吓人，我们不妨先假设已知最后的 $P$ 从 $\sum_{i<j}[P_i>P_j](j-i)$ 这个式子入手。

首先我们考虑对于每个位置 $i$ 计算它的贡献。那么有：
$$
ans_i = i(\sum_{j=1}^{i-1}{[P_j > P_i]} - \sum_{j = i + 1}^{n}{[P_j < P_i]})
$$

然后我们考虑这样两个式子：

$$
\begin{aligned} 
\sum_{j=1}^{i - 1}{[P_j > P_i]} + \sum_{j = i + 1}^{n}{[P_j > P_i]} &= n - P_i
\\
\sum_{j=i+1}^{n}{[P_j < P_i]} + \sum_{j=i+1}^{n}{[P_j > P_i]} &= n - i
\end{aligned} 
$$

两式相减恰好是上述式子的右侧，也就是得到 $ans_i=i^2 - iP_i$，故 $ans = \sum_{i=1}^{n}{i^2} - \sum_{i=1}^{n}{iP_i}$。

我们不妨求上述式子的期望。首先可以先把 $i^2$ 分离出来，只处理后面。求某个位置的期望值比较困难，我们不妨求 $P_i$ 最后所在位置的期望。

对于 $i < j$，一次操作后 $i$ 到达 $j$ 的方案数是 $\min(i, n - j + 1)$。比较直观地证一下：

$$1 \dots i \dots \frac{i+j}{2} \dots j \dots n$$

我们考虑从对称中心往两边拓展，那么得到的有效区间个数就是 $i, j$ 分别到两边到距离到最小值。

那么我们考虑把它写成 $\min(i, j, n - i + 1, n - j + 1)$ 的形式，就把它推广到了 $i > j$ 的情况。这时我们发现，把 $i$ 换到 $j$ 和换到和它对称的 $n - j + 1$ 的方案是一样到，因此我们得到 $i$ 经过交换后到位置期望是 $\dfrac{n+1}{2}$，也就是序列的中心。

考虑 $i$ 被交换走的概率，应该是 $\left(1 - \dfrac{\tbinom{i}{2}+\tbinom{n-i+2}{2}}{\tbinom{n+1}{2}}\right)^m$。我们令其为 $K$。则 $i$ 位置的期望就是 $K\dfrac{n+1}{2}+(1-K)i$。因此答案为 $ans = \sum_{i=1}^{n}{i^2} - P_i\sum_{i=1}^{n}{K\dfrac{n+1}{2}+(1-K)i}$。直接求解即可，复杂度 $O(n\log n)$，瓶颈在求逆元。

## 代码

```c++
#include <bits/stdc++.h> 

typedef long long ll;
const int MOD = 998244353;
const int MAX = 2e5 + 5;

ll n, m, ans;
ll p[MAX], frc[MAX], ifrc[MAX], inv[MAX];

ll qp(ll a, ll x) { ll res = 1; for (; x; a = a * a % MOD, x >>= 1) { if (x & 1) { res = res * a % MOD; } } return res; }
ll C(ll x, ll y) { return frc[x] * ifrc[y] % MOD * ifrc[x - y] % MOD; }
void init(int x)
{
  frc[0] = ifrc[0] = inv[0] = 1;
  for (int i = 1; i <= x; ++i) { frc[i] = frc[i - 1] * i % MOD; } ifrc[x] = qp(frc[x], MOD - 2);
  for (int i = x - 1; i >= 1; --i) { ifrc[i] = ifrc[i + 1] * (i + 1) % MOD; }
  for (int i = 1; i <= x; ++i) { inv[i] = ifrc[i] * frc[i - 1]; }
}

int main()
{
  scanf("%lld%lld", &n, &m); init(MAX - 3);
  for (int i = 1; i <= n; ++i) { scanf("%lld", &p[i]); }
  for (int i = 1; i <= n; ++i)
  {
    ll P = qp((C(n - i + 1, 2) + C(i, 2)) % MOD * qp(C(n + 1, 2), MOD - 2) % MOD, m);
    ll q = (1ll * i * P % MOD + (n + 1) * inv[2] % MOD * (1 - P + MOD) % MOD) % MOD;
    ans = (ans + 1ll * i * i % MOD - q * p[i] % MOD + MOD) % MOD;
  //  printf("%lld", ans);
  }
  printf("%lld", ans * qp(C(n + 1, 2), m) % MOD);
}
```



---

