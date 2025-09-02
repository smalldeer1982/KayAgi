# [ABC284G] Only Once

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc284/tasks/abc284_g

$ 1 $ 以上 $ N $ 以下の整数からなる長さ $ N $ の数列 $ A\ =\ (A_1,A_2,\dots,A_N) $ および整数 $ i\ (1\leq\ i\ \leq\ N) $ に対して、 長さ $ 10^{100} $ の数列 $ B_i=(B_{i,1},B_{i,2},\dots,B_{i,10^{100}}) $ を以下のように定義します。

- $ B_{i,1}=i $
- $ B_{i,j+1}=A_{B_{i,j}}\ (1\leq\ j\ <\ 10^{100}) $
 
また、$ S_i $ を「数列 $ B_i $ のなかでちょうど $ 1 $ 度だけ出てくる数の種類数」と定義します。 より厳密には、$ S_i $ は「$ B_{i,j}=k $ を満たす $ j\ (1\leq\ j\leq\ 10^{100}) $ がちょうど $ 1 $ つであるような $ k $ の数」です。

整数 $ N $ が与えられます。数列 $ A $ として考えられるものは $ N^N $ 通りありますが、それら全てに対して $ \displaystyle\ \sum_{i=1}^{N}\ S_i $ を求め、 その総和を $ M $ で割った余りを答えてください。

## 说明/提示

### 制約

- $ 1\leq\ N\ \leq\ 2\times\ 10^5 $
- $ 10^8\leq\ M\ \leq\ 10^9 $
- $ N,M $ は整数
 
### Sample Explanation 1

例として、$ A=(2,3,3,4) $ の場合を考えます。 - $ i=1 $ のとき : $ B_1=(1,2,3,3,3,\dots) $ となるから、$ 1 $ 度だけ出てくる数は $ 1,2 $ の $ 2 $ つで、$ S_1=2 $ - $ i=2 $ のとき : $ B_2=(2,3,3,3,\dots) $ となるから、$ 1 $ 度だけ出てくる数は $ 2 $ のみで、$ S_2=1 $ - $ i=3 $ のとき : $ B_3=(3,3,3,\dots) $ となるから、$ 1 $ 度だけ出てくる数は存在せず、$ S_3=0 $ - $ i=4 $ のとき : $ B_4=(4,4,4,\dots) $ となるから、$ 1 $ 度だけ出てくる数は存在せず、$ S_4=0 $ よって、$ \displaystyle\ \sum_{i=1}^{N}\ S_i=2+1+0+0=3 $ です。 他の $ 255 $ 通りの $ A $ に対しても同様に $ \displaystyle\ \sum_{i=1}^{N}\ S_i $ を計算したうえで、 $ 256 $ 通り全ての総和をとると $ 624 $ になります。

### Sample Explanation 3

総和を $ M $ で割った余りを出力してください。

## 样例 #1

### 输入

```
4 100000000```

### 输出

```
624```

## 样例 #2

### 输入

```
7 1000000000```

### 输出

```
5817084```

## 样例 #3

### 输入

```
2023 998244353```

### 输出

```
737481389```

## 样例 #4

### 输入

```
100000 353442899```

### 输出

```
271798911```

# 题解

## 作者：Kreado (赞：6)

[题目传送门](https://atcoder.jp/contests/abc284/tasks/abc284_g)。

#### 思路

整理过完题目后，也就是叫我们求

$$\sum_A \sum_{i=1}^n S_i$$

对于每个 $i$，$A$ 对答案的贡献是一定的，也就是

$$\sum_i^{n}(\sum_A S_i)$$

对于每个 $A_i$，每次前进最终都会在一个环中，此时再重复前进就没有贡献了。

实际上，可以转化为图形问题，如下。

![](https://img.atcoder.jp/abc284/199e8fdd8dc9892d24830f1fd889ea9a.png)

很明显，这是一个内向基环树森林，环旁边的顶点贡献就是顶点到环的距离 $d$，但我们仍然没有把所有点算进答案，考虑枚举环的大小 $s$，它的贡献就是 $A_{n-1}^{s-d-1}$，对于其他点，他们可以是任意符合要求的数，答案贡献也就是 $n^{n-d-s}$。

对此，可以列出以下式子

$$\sum_{d=0}^{n-1}A_{n-1}^d\sum_{s=1}^{n-d}A_{n-d-1}^{s-1}n^{n-d-s}$$

关于 $d$ 的式子我们无法再化简了，所以考虑后面的式子，令 $f(d)=\sum_{s=1}^{n-d}A_{n-d-1}^{s-1}n^{n-d-s}$

如果我们直接把 $A$ 化开，也就是


$$f(d)=\sum_{s=1}^{n-d}\frac{(n-d-1)}{(n-d-s)!}\times n^{n-d-s}$$

接下来不管怎样化都要用到逆元了，但是不保证 $m$ 是质数，因此，我放弃继续推这个式子了。

再次回到原式，可以得到

$$f(d-1)=\sum_{s=1}^{n-d+1}A_{n-d}^{s-1}n^{n-d-s+1}$$

对于以后的化简，我们可以直接将 $s=1$ 的情况算出来，也就是

$$\begin{aligned}f(d-1)&=n^{n-d}+\sum_{s=2}^{n-d+1}A_{n-d}^{s-1}n^{n-d-s+1}\\&=n^{n-d}+(n-d)\sum_{s=2}^{n-d+1}A_{n-d-1}^{s-2}n^{n-d-s+1}\\&=n^{n-d}+(n-d)\sum_{s=1}^{n-d}A_{n-d-1}^{s-1}n^{n-d-s}\\&=n^{n-d}+(n-d)f(d)\end{aligned}$$

对于 $f(n)$ 的情况，显然是 $0$，递推式就没了。

最终式子就是

$$ans=n\sum_{d=0}^{n-1}A_{n-1}^df(d)$$

这个可以 $O(n)$ 算出。

#### 贴贴代码

```cpp
#include<bits/stdc++.h>
#define ll long long
const ll Maxn=2e5+7; 
ll n,m,ans,f[Maxn],p=1,k=1;
int main(){
    scanf("%lld%lld",&n,&m);
    for(ll i=n-1;i>=1;i--) f[i]=(f[i+1]*(n-i-1)+p)%m,p=p*n%m;
    for(ll i=1;i<=n;i++) k=k*(n-i)%m,ans=(ans+k*f[i]%m*i)%m;
    printf("%lld",ans*n%m);
    YOU AK NOI AND CTSC
}
```

话说前 $6$ 题的代码没有一个超过 $1k$ 的，hh。

---

## 作者：zac2010 (赞：5)

### 题目大意

给你一个 $N$，让你求所有长度为 $N$ 的所有数字都在 $1 \to n$ 的范围内的 $A$ 数组他们的贡献之和。

我们设 $A_i$ 的贡献为 $S_i$。那么这时我们还有一个 $B$ 数组，对于每个 $B_{i,j}$，有 $1 \leq i \leq n$ 且 $1 \leq j \leq 10^{100}$，且 $B_i = (B_{i,1},B_{i,2}, B_{i,3}, ... ,B_{i,10^{100}})$。

 $B$ 数组构造方式：

* $B_{i,1}=i$。
* $B_{i,j+1}=A_{B_{i,j}}(1 \leq j < 10^{100})$。

然后呢，对于每个 $S_i$，他等于 $B_i$ 中恰好只出现一次的数字个数。

所以当前的 $A$ 数组的答案就是 $S_i$ 之和，而最终答案要累加所有可行的 $A$。输出时对答案取模 $M$。

### 思路

多半题目第一步常见的是发现性质加模型转换。那我们思考这道题目中有什么性质呢？

首先我们发现答案的每一行有对称性，所以我们只要算出一行再乘以 $N$ 即可。

对于每一行，又该怎么算呢？这时候能发现如果我们把长度抽象成 $N$ 个点， $A$ 数组抽象成 $N$ 条边（$i$ 连向 $A_i$），$B_{i,1}=i$ 其实就是第 $i$ 行起点为 $i$，那么有良好的性质——因为一个点只有向着 $A_i$ 连边，所以只连出去了一条边，而这也就保证了我们从某个点开始走的话路上没有分叉，只能一条走到底，这也就意味着，如果走上了一个环，就再也走不出去了，那就说明路径上 **至多只有一个环**。

同样，你也会很快发现因为每个点都有连出去的边，所以永远都走不完，利用鸽巢原理可以证明，而当走到第 $N+1$ 个点时，必定有重复，而有重复就必定有环——**至少有一个环**。

把两个结论结合一下，那就是： **有且仅有一个环** 。

如果还不够清晰，可以借助下图理解：

![](https://cdn.luogu.com.cn/upload/image_hosting/l8trvbl3.png)

好了，接下来的就很简单了。我们设对于 $b_i$，从 $B_{i,l+1}$ 开始出现重复，其与 $B_{i,p}$ 重复了，其中 $p<l$，那么这时我们恰好出现一次的节点数是 $p-1$。原因非常简单，那就是因为从 $p$ 那个位置开始重复，意味着 $B_i$ 的 $1 \sim p-1$ 的位置不可能再遍历到了，而后面会一直循环遍历。

接下来就直接给出式子（我们枚举 $l$）：
$$
A_{n-1}^{l-1}N^{N-l}\sum_{p=1}^l(p-1)=A_{n-1}^{l-1}*N^{N-l}*{l(l-1) \over 2}
$$

其中上面的 $A_{n-1}^{l-1}$ 表示 $n-1$ 个点中选 $l-1$ 个（因为起点也算在 $l$ 个点内，且另外 $l-1$ 个点不得与起点重复）。而 $N^{N-l}$ 是因为第 $l+1$ 个位置与第 $p$ 个位置重复了，所以总共出现了 $l$ 种不同的数字，而另外 $n-l$ 中数字的 $A$ 数组值可以使 $1 \sim N$，因为他们对答案没有任何影响。然后那个 $\sum_{p=1}^l(p-1)$ 即枚举 $p$（与 $l+1$ 位置重复的点），那么答案是 $p-1$，累加求和。而第一步化成第二步用到了等差数列求和。

所以我们只需要枚举 $l$ 把 $A_{n-1}^{l-1}\times N^{N-l}\times {l(l-1) \over 2}$ 这个玩意儿求和即可。

最后提醒：记得取模 $M$ 。

### 代码

```cpp
#include <bits/stdc++.h>
#define L(i, a, b) for(int i = a; i <= b; i++)
#define R(i, a, b) for(int i = a; i >= b; i--)
using namespace std;
const int N = 1e6 + 10;
int n, m, a = 1, ans, pn[N];
int main(){
	scanf("%d%d", &n, &m);
	pn[0] = 1;
	L(i, 1, n){
		pn[i] = 1ll * pn[i - 1] * n % m;//预处理n的i次方
	}
	L(l, 1, n){
		ans = (ans + 1ll * a * pn[n - l] % m * (1ll * l * (l - 1) / 2 % m) % m) % m;//按照上面的公式累加进答案
		a = 1ll * a * (n - l) % m;//算组合数
	}
	printf("%lld\n", 1ll * ans * n % m);//有n行，所以乘n
	return 0;
} 
```


---

## 作者：hyman00 (赞：4)

# ABC284G 题解

## 考场思路

注：这个思路是 **错误** 的。

当时想的是对 $i\rightarrow A_i$ 建边，得到一个内向基环树森林，然后子树 `dp`？

显然 `dp` 还要套背包，或许可以做，但是时间至少 $O(n^2)$ 直接炸掉。

## 正解

重点：$n$ 个数是 **对称** 的，所以只需要计算 $S_1\times n$。

发现 $B_1$ 应该是先出现唯一的 $x$ 个数，然后重复出现 $y$ 个数。

要统计的就是 $x$ 的和。

考虑枚举 $k=x+y$。

- 先选出前 $k$ 个数，应用乘法原理就是 $(n-1)\times(n-2)\times\dots\times(n-k+1)$；
- 再分配其他的数的 $A_i$，即 $n^{n-k}$；
- 在上面都选好以后，对于每一个 $0\le x\lt k$，都有唯一一种分配 $A_{B_{k}}$ 的方式对答案贡献是 $x$。

乘起来就是 $(n-1)\times(n-2)\times\dots\times(n-k+1)\times n^{n-k}\times \frac{k(k-1)}{2}$。

注意模数不是质数所不可以用阶乘逆元算，但是可以对前半部分直接累乘，后半部分快速幂或预处理。

记得最后乘 $n$！

看实现方法，时空复杂度是 $O(n)$ 或 $O(n\log n)$，可以解决此题。

## 代码

```c++
int n,p;
int qp(int a,int b){
	int c=1;
	while(b){
		if(b&1)(c*=a)%=p;
		(a*=a)%=p;b>>=1;
	}
	re c;
}
void run(){
	cin>>n>>p;
	int ans=0,cur=1;
	rept(i,1,n+1){
		(cur*=n-i+1)%=p;
		(ans+=(i*(i-1)/2)%p*cur%p*qp(n,n-i)%p)%=p;
	}
	cout<<ans*n%p<<"\n";
}
```

## 背景

当时老师叫我们打 abc，只做最后两题，想了一整场 g 都没做出来（

---

## 作者：Un1quAIoid (赞：3)

**传送门：[G - Only Once](https://atcoder.jp/contests/abc284/tasks/abc284_g)**

---------------------

**题意：**

给定 $n$，对于一个长度为 $n$，值域为 $n$ 的序列 $A$，我们按如下方法构造无限序列 $B_i(1 \le i \le n)$：

- $B_{i,1} = i$
- $B_{i,j} = A_{B_{i,j-1}}(j > 1)$

记 $S_i$ 为 $B_i$ 中只出现了一次的元素的个数，定义序列 $A$ 的价值为 $\sum_{i=1}^n S_i$，现在请求出所有 $n^n$ 个可能的序列 $A$ 的价值之和对 $M$ 取模的结果。

$n \le 2 \times 10^5, 10^8 \le M \le 10^9$.

------------------------

这是不同于官方题解的~~麻烦不知道多少倍的~~邪道解法。

对于任意 $1 \le i \le n$，我们从 $i$ 向 $A_i$ 连一条有向边，不难发现每个点有且仅有一条出边，整张图形成一个内向基环树森林（记为 $\mathcal{T}$）。

先来考虑怎样计算单个 $\mathcal{T}$ 的价值，观察序列 $B_i$ 的构造方式不难发现 $B_i$ 即为从点 $i$ 出发，沿着出边一直走下去经过的点形成的序列，$S_i$ 即为从点 $i$ 出发进入环之前经过的点的数量，$\sum_{i=1}^n S_i$ 就是每个**不在环上**的点被经过的次数，也即其子树大小，不妨简记为 $\sum_{i=1}^{n} siz_i$。

接下来就可以大力列式子了：

$$
\begin{aligned}
&\sum_{\mathcal{T}}\sum_{i=1}^n siz_i \\
= &\sum_{\mathcal{T}}\sum_{i=1}^n i\sum_{j=1}^{n} [siz_j=i] \\
= &\sum_{i=1}^n i \sum_{\mathcal{T}}\sum_{j=1}^{n} [siz_j=i] \\
= &\sum_{i=1}^n i \binom{n}{i} i^{i-1} (n-i)^{n-i+1}
\end{aligned}
$$

解释一下最后一步，$\binom{n}{i}$ 为选出来组成这个大小为 $i$ 的子树的点的方案数，$i^{i-1}$ 为该树的形态数，即为 $i$ 个点的有标号有根树的数量（证明见[Prufer 序列](https://oi-wiki.org/graph/prufer/)），而剩下的点加上根节点这总共 $n-i+1$ 个点每个点都能向剩下的 $n-i$ 个点随意连边，所以最后要乘上 $(n-i)^{n-i+1}$。

如果模数是个大质数，那么这题已经做完了，但关键是模数**可能为合数**，导致 $n!$ 的逆元不存在，从而没法求 $\binom{n}{i}$。解决办法是借鉴扩展卢卡斯定理的思想，考虑将模数质因数分解成 $\sum p_i^{k_i}$，单独求出在模 $p_i^{k_i}$ 意义下的答案，最后使用中国剩余定理合并出答案，简单说一下如何在模 $p^k$ 意义下求 $\binom{n}{m}$：

$$
\begin{aligned}
&\binom{n}{m} \\
= &\dfrac{n!}{m!(n-m)!} \\
= &\dfrac{\dfrac{n!}{p^x}}{\dfrac{m!}{p^y} \dfrac{(n-m)!}{p^z}} p^{x-y-z}
\end{aligned}
$$

其中 $x$ 是最大的满足 $p^x | n!$ 的整数，$y,z$ 同理，其实就是将分子和分母中的质因数 $p$ 单独拿出来算，这样分母就和模数互质，可以求逆元了，我们可以直接在 $O(n)$ 的时间内预处理出来 $\dfrac{i!}{p^{x_i}}(1 \le i \le n)$，总复杂度即为 $O(nt + n \log n)$，其中 $t$ 为模数的不同的质因数的数量，最大为 $9$，~~这不和官方做法复杂度一样吗~~。

代码：
```cpp
//邪道解法
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)
#define eb emplace_back
#define pb push_back
#define mp make_pair
using namespace std;

typedef long long ll;
const int N = 2e5+5;

int n, M, cnt, ans;
int num[10][N];
ll fac[10][N], ifac[10][N], ppow[10][101], c[10], tmp[N];

pair<int, int> fctr[10];

inline int qpow(int a, int b, int Mod) {
    ll base = a, ans = 1;
    while (b) {
        if (b & 1) ans = ans * base % Mod;
        base = base * base % Mod;
        b >>= 1;
    }
    return ans;
}

void init() {
    int t = M;
    for (int i = 2; i * i <= t; i++) if (t % i == 0) {
        fctr[++cnt] = mp(i, 1);
        ppow[cnt][0] = 1;
        int tt = 0;
        while (t % i == 0) ppow[cnt][++tt] = (fctr[cnt].second *= i), t /= i;
    }
    if (t != 1) fctr[++cnt] = mp(t, t), ppow[cnt][0] = 1;

    for (int i = 1; i <= cnt; i++) {
        auto [p, pw] = fctr[i];
        c[i] = M / pw * qpow(M / pw, pw / p * (p - 1) - 1, pw);

        fac[i][0] = 1;
        for (int j = 1; j <= n; j++) {
            tmp[j] = (j % p ? j : tmp[j / p]);
            fac[i][j] = fac[i][j - 1] * tmp[j] % pw;
            num[i][j] = num[i][j / p] + j / p;
        }

        ifac[i][n] = qpow(fac[i][n], pw / p * (p - 1) - 1, pw);
        for (int j = n; j; j--) ifac[i][j - 1] = ifac[i][j] * tmp[j] % pw;
    }
}

ll C(int n, int m) {
    ll ret = 0;
    for (int i = 1; i <= cnt; i++) {
        int pw = fctr[i].second;
        ll a = fac[i][n] * ifac[i][m] % pw * ifac[i][n - m] % pw * ppow[i][min(num[i][n] - num[i][m] - num[i][n - m], 100)] % pw;
        ret = (ret + c[i] * a) % M;
    }
    return ret;
}

int main() {
    scanf("%d%d", &n, &M);

    init();

    for (int i = 1; i < n; i++) ans = (ans + C(n, i) * qpow(i, i, M) % M * qpow(n - i, n - i + 1, M)) % M;

    printf("%d", ans);
    return 0;
}
```

---

## 作者：donaldqian (赞：1)

显然可以 $(i,a_i)$ 连边然后转化成基环树森林上每个点到环的距离和。然后可以发现如果直接暴力是 $n^{n+1}$ 的，所以一眼数学题。

我们考虑在所有可能的 $a$ 序列中，到环距离为 $d$ 的点造成的贡献。假如我们令其为 $f(d)$，那么显然有 $ans=\sum\limits_{d=0}^{n-1}f(d)$。那么组合数学。

首先考虑起点，可能有 $n$ 个。其次考虑起点到环的这条链，因为不能连向起点，所以有 $A_{n-1}^d$ 种。接下来考虑这个环，设环长为 $s$。那么环上的最后一个点连边已经固定，而且不能选已经定了的 $d+1$ 个点，所以是 $A_{n-d-1}^{s-1}$。最后考虑其他的 $n-d-s$ 个点，它们想指向谁都行，所以再乘以 $n^{n-d-s}$。那么 $f(d)=d\times n\times A_{n-1}^d\times \sum\limits_{s=1}^{n-d}(A_{n-d-1}^{s-1}\times n^{n-d-s})$

这时候稍微预处理一下就可以做到 $\varTheta(n^2)$。我们希望加速后一个求和。

令 $g(d)=\sum\limits_{s=1}^{n-d}(A_{n-d-1}^{s-1}\times n^{n-d-s})$。如果你比较聪慧应该可以看出 $g(d-1)$ 可以从 $g(d)$ 递推得出。实际上，
$$
g(d-1)=\sum\limits_{s=1}^{n-d+1}(A_{n-d}^{s-1}\times n^{n-d-s+1})\\= \sum\limits_{s=2}^{n-d+1}(A_{n-d}^{s-1}\times n^{n-d-s+1})+n^{n-d}\\= \sum\limits_{s=1}^{n-d}(A_{n-d}^s\times n^{n-d-s})+n^{n-d}
$$
观察到，
$$
A_{n-d}^s=(n-d)\times (n-d-1)\dots(n-d-s+2)\times (n-d-s+1)\\ A_{n-d-1}^{s-1}=\ \ \ \ \ \ \ \ \ \ \ \ \ \ (n-d-1)\dots(n-d-s+2)\times (n-d-s+1)\\ \therefore A_{n-d}^s=(n-d)\times A_{n-d-1}^{s-1}
$$
代入上式可得
$$
g(d-1)=n^{n-d}+(n-d)\times \sum\limits_{s=1}^{n-d}(A_{n-d-1}^{s-1}\times n^{n-d-s})\\= n^{n-d}+(n-d)\times g(d)
$$
也即
$$
g(d)=n^{n-d-1}+(n-d-1)\times g(d+1)
$$
可以做到 $\varTheta(1)$ 递推。总时间复杂度 $\varTheta(n)$。

说一下细节。由于模数不一定是素数所以不能预处理阶乘的逆元，但可以直接预处理 $A_{n-1}^d$。初值 $g(n)=0$。

[代码](https://atcoder.jp/contests/abc284/submissions/59754222)。

---

## 作者：DaiRuiChen007 (赞：1)

# ABC284G 题解



## 思路分析

考虑在所有的 $(a_i,i)$ 之间连边，我们能够得到一棵基环树，而 $s_i$ 事实上就是 $i$ 到基环树中环的距离。

我们可以把 $s_i$ 理解为一条长度为 $s_i$ 的链接一个环，考虑拆贡献，对于每个 $1\sim n$ 的 $k$，我们统计有多少种情况使得图中有一个恰好长度为 $k$ 的链。

首先确定长度为 $k$ 的链，我们先从 $n$ 个数里任选 $k$ 个，然后对其进行排列，得到这一步的方案数为 $\binom nk\times  k!$ 种。

而在确定了链之后，我们要在链的后面接一个环，假设其长度为 $j$，我们同样在剩下的 $n-k$ 个数里任选 $j$ 个然后进行排列，不过注意到不同的点与链相连算不同的方案，因此此处的排列方案数为 $j\times(j-1)!$ 种，总方案数为 $\binom {n-k}j\times j!$。

而剩下的 $n-k-l$ 个点随意选择连接的节点，方案数 $n^{n-k-l}$。

因此我们得到答案的表达式：
$$
\begin{aligned}
\text{answer}
&=\sum_{k=0}^n k\times\binom nk\times k!\times\sum_{j=1}^{n-k} \binom{n-k}j\times j!\times n^{n-k-j}\\
&=\sum_{k=0}^n\sum_{j=1}^{n-k} k\times\binom nk\times k!\times\binom{n-k}j\times j!\times n^{n-k-j}\\
&=\sum_{k=0}^n\sum_{j=1}^{n-k}k\times\dfrac{n!}{k!\times(n-k!)}\times k!\times\dfrac{(n-k)!}{j!(n-k-j)!}\times j!\times n^{n-k-j}\\
&=\sum_{(j+k)=1}^n\sum_{k=0}^{(j+k)-1}  k\times \dfrac{n!}{(n-j-k)!}\times n^{n-j-k}\\
&=\sum_{i=1}^n \dfrac{n!}{(n-i)!}\times n^{n-i}\times\sum_{k=0}^{i-1}k\\
&=\sum_{i=1}^n\dfrac{n!}{(n-i)!}\times n^{n-i}\times \dfrac{i\times(i-1)}2
\end{aligned}
$$
其中在化简的过程中我们令 $i=j+k$ 方便表达。

注意到 $\dfrac{n!}{(n-i)!}$ 可以在递推预处理得到，因此时间复杂度为 $\Theta(n\log n)$，$\Theta(\log n)$ 为快速幂复杂度。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e5+1;
int f[MAXN];
inline int ksm(int a,int b,int m) {
	int ret=1;
	while(b) {
		if(b&1) ret=ret*a%m;
		a=a*a%m;
		b=b>>1;
	}
	return ret;
}
signed main() {
	int n,mod,ans=0;
	scanf("%lld%lld",&n,&mod);
	f[n]=1;
	for(int i=n;i>=1;--i) f[i-1]=f[i]*i%mod;
	for(int k=1;k<=n;++k) ans=(ans+k*(k-1)/2%mod*ksm(n,n-k,mod)%mod*f[n-k]%mod)%mod;
	printf("%lld\n",ans);
}
```



---

## 作者：SunsetSamsara (赞：0)

## ABC284G Only Once

### 题意

给定 $n, p$，求 $n$ 个点的内向基环森林的所有点深度和的和模 $p$。每个点的深度定义为这个点到当前基环树上环的距离。

$n \le 2\times 10^5, 10^8 \le p \le 10^9$

### 标签

数学，思维

### 做法

由于对称性，每个点对答案的贡献都是相同的，所以只需对点 $n$ 进行考虑。

发现一个点的方案数只需考虑两个值 $(a, b)$，其中 $a$ 表示点 $n$ 到当前基环树上环的距离，$b$ 表示环的大小。在这样的情况下，将整个基环森林分为三部分：点 $n$ 到环的链（不计环上的那个点），环上的点，除了环与链的其他点。方案数就是三个部分方案数的乘积，分开进行考虑。

+ 点 $n$ 到环的链。这条链长度为 $a$，除去最后一个点固定为点 $n$，相当于带顺序地在 $n - 1$ 个点中选出 $a - 1$ 个点，有 $A_{n - 1}^a$ 种方案。

+ 环上的点。断开环从点 $n$ 到环的链上的点到其前驱的边，变为一段序列。发现每一个合法序列都对应一个合法的环，所以这部分方案数就相当于在链取剩下的 $n - a$ 个点中再有序地取出 $b$ 个点，有 $A_{n - a}^b$ 种方案。

+ 剩余的点。剩余 $n - a - b$ 个点，每个点向 $1$ 到 $n$ 的任意一个点连边，有 $n^{n - a - b}$ 种方案。

所以给定一组 $(a, b)$ 有 $A_{n - 1}^a A_{n - a}^b n^{n - a - b}$ 种方案，点 $n$ 对答案的贡献就是 $\sum\limits_{a\ge 1}a\sum\limits_{b \ge 1}A_{n - 1}^a A_{n - a}^b n^{n - a - b}$ 种方案。

化简这个式子：

$$
\begin{aligned}
\sum\limits_{a\ge 1}a\sum\limits_{b \ge 1}A_{n - 1}^a A_{n - a}^b n^{n - a - b} &= \sum\limits_{a\ge 1}a\sum\limits_{b \ge 1}\frac{(n-1)!}{(n-a)!} \frac{(n-a)!}{(n-a-b)!} n^{n - a - b}\\
&= \sum\limits_{a\ge 1}a\sum\limits_{b \ge 1}\frac{(n-1)!}{(n-a-b)!} n^{n - a - b}\\
&= \sum\limits_{a\ge 1}a\sum\limits_{b \ge 1}\frac{(n-1)!}{(n-a-b)!} n^{n - a - b}\\
&= \sum\limits_{a\ge 1}a\sum\limits_{t \le n - a - 1}\frac{(n-1)!}{t!} n^t
\end{aligned}
$$

$n$ 个点对答案的贡献都相同，所以答案就是：

$$
n \sum\limits_{a\ge 1}a\sum\limits_{t \le n - a - 1}\frac{(n-1)!}{t!} n^t = \sum\limits_{a\ge 1}a\sum\limits_{t \le n - a - 1}\frac{n!}{t!} n^t
$$

对于每一个 $i$ 预处理 $\sum\limits_{t \le i}\frac{n!}{t!} n^t$，枚举 $a$ 即得答案。

### 代码

[提交记录](https://atcoder.jp/contests/abc284/submissions/47422326)

---

## 作者：joke3579 (赞：0)

## $\text{Statement}$

对于一个长度为 $n$、其中元素取值为 $[1,n]$ 内整数的序列 $A = (A_1, A_2, \dots, A_n)$，以及一个整数 $i(1\le i \le n)$，我们按如下方式定义一个长度为 $10^{100}$ 的序列 $B_i = (B_{i, 1}, B_{i, 2}, \dots, B_{i, 10^{100}})$：

- $B_{i, 1} = i$。
- $B_{i, j + 1} = A_{B_{i, j}} (1 \le j < 10^{100})$。

此外，我们定义 $S_i$ 为 $B_i$ 中只出现一次的整数的数量。定义一个序列的贡献为 $\sum_{i=1}^n S_i$。

给定正整数 $n, m$，你需要求出总共 $n^n$ 种可能的序列的贡献之和模 $m$ 的值。

$1\le n \le 2\times 10^5,\ 10^8 \le m\le 10^9$。

## $\text{Solution}$

由于答案具有对称性，任意 $S_i$ 的贡献等于 $S_1$，接下来我们只需要讨论 $S_1$。下文中简记 $B_{1, i}$ 为 $B_i$。

我们令 $k$ 为一种可能中满足前 $i$ 个元素彼此不同的最大的 $i$，随后来分别对确定的 $k$ 计数种类数。 

我们已经确定了 $B_1 = 1$，这样就需要从 $n-1$ 个彼此不同的元素中选 $k-1$ 个，也就有 $A(n-1, k-1)$ 种可能性。关注 $B_{k + 1}$，可以发现其必定与前 $k$ 个中的一个元素相同。假设 $B_p = B_{k + 1} (1\le p \le k)$，则我们可以发现，$B_p$ 到 $B_k$ 的子序列定会无限循环下去。  
因此，只有 $B_1$ 到 $B_{p-1}$ 对应的子序列是只在 $B$ 中出现一次的序列，对答案的贡献即为 $p-1$。对所有可能的子序列贡献求和得到这一部分对答案的贡献 $\sum_{p=1}^k (p - 1) = p(p-1)/2$。

现在固定 $B_1$ 到 $B_{k + 1}$ 段的序列，考虑有多少 $A$ 满足当前的条件。由于 $B_i$ 固定等价于 $A_{B_{i-1}}$ 被确定，可以发现 $A_{B_1}, A_{B_2}, \dots, A_{B_k}$ 都是已经确定了的，因此 $A$ 中没有确定的元素还有 $n - k$ 个。  
因此对 $k$ 的答案即为

$$A(n-1, k-1)\times n^{n-k}\times \frac{p(p-1)}2 $$

对 $1\le k\le n$ 求和即可得到 $S_1$。总时间复杂度 $O(n)$。

[Submission](https://atcoder.jp/contests/abc284/submissions/37849720).

---

