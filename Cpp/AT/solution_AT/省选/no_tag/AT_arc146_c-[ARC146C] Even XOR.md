# [ARC146C] Even XOR

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc146/tasks/arc146_c

$ 0 $ 以上 $ 2^N $ 未満の非負整数からなる集合 $ S $ のうち、以下の条件を満たすものの個数を $ 998244353 $ で割ったあまりを出力してください。

- $ S $ の空でない部分集合 $ T $ は以下のどちらかを満たす。
  - $ T $ の要素数が奇数
  - $ T $ の全要素の $ \mathrm{XOR} $ が $ 0 $ でない
 
 $ \mathrm{XOR} $ とは  非負整数 $ A,\ B $ のビット単位 $ \mathrm{XOR} $ 、$ A\ \oplus\ B $ は、以下のように定義されます。

- $ A\ \oplus\ B $ を二進表記した際の $ 2^k $ ($ k\ \geq\ 0 $) の位の数は、$ A,\ B $ を二進表記した際の $ 2^k $ の位の数のうち一方のみが $ 1 $ であれば $ 1 $、そうでなければ $ 0 $ である。
 
 例えば、$ 3\ \oplus\ 5\ =\ 6 $ となります (二進表記すると: $ 011\ \oplus\ 101\ =\ 110 $)。  
 一般に $ k $ 個の整数 $ p_1,\ p_2,\ p_3,\ \dots,\ p_k $ のビット単位 $ \mathrm{XOR} $ は $ (\dots\ ((p_1\ \oplus\ p_2)\ \oplus\ p_3)\ \oplus\ \dots\ \oplus\ p_k) $ と定義され、これは $ p_1,\ p_2,\ p_3,\ \dots\ p_k $ の順番によらないことが証明できます。

## 说明/提示

### 制約

- $ 1\ \le\ N\ \le\ 2\ \times\ 10^5 $
- 入力は全て整数である。

### Sample Explanation 1

$ \lbrace\ 0,2,3\ \rbrace $ や $ \lbrace\ 1\ \rbrace $ や $ \lbrace\ \rbrace $ は条件を満たします。 $ \lbrace\ 0,1,2,3\ \rbrace $ は条件を満たしません。 なぜなら、$ \lbrace\ 0,1,2,3\ \rbrace $ は部分集合 $ \lbrace\ 0,1,2,3\ \rbrace $ が要素数が偶数であり、全要素の $ \mathrm{XOR} $ が $ 0 $ であるからです。

## 样例 #1

### 输入

```
2```

### 输出

```
15```

## 样例 #2

### 输入

```
146```

### 输出

```
743874490```

# 题解

## 作者：joke3579 (赞：13)

考虑向已经满足条件的集合中加入元素得到新的集合。设 $f_i$ 为大小为 $i$ 的满足条件的集合。根据定义有 $f_0 = 1,\ f_1 = 2^n$。

设一个满足条件的集合为 $S$，$S$ 的一个大小为奇数的子集为 $T$，$T$ 内元素的异或和为 $x$。如果我们将 $x$ 加入了集合 $S$ 得到 $S'$，则 $T\cup \{x\} \subseteq S'$，而 $2\mid |T\cup \{x\} |$，因此 $S'$ 不满足条件。
由此可以看到，对于一个满足条件的集合 $S$，向其中加入任意一个奇大小子集的异或和会使得其不再满足条件。同时，由于 $S$ 是满足条件的集合，任意两个奇大小子集的异或和都不同，因为反之可以取这两个子集中只出现过一次的元素作为一个偶大小子集，而这个子集的异或和为 $0$。

因此我们可以发现，大小为 $i$ 的集合可以加入 $[\text{总元素数量}] - [\text{大小为 i 的集合中奇大小子集的数量}] = 2^n - 2^{i-1}$ 种互不相同的元素得到大小为 $i + 1$ 的集合。而每个 $i + 1$ 大小集合通过此方法都被计数了 $i + 1$ 次，因此有转移
$$f_{i+1} = \frac 1{i+1} \left(f_{i} \times (2^n - 2^{i-1})\right)$$

预处理 $2$ 的幂次与逆元后复杂度为 $O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std; 
#define rep(i,s,t) for (register int i = (s), i##_ = (t) + 1; i < i##_; ++ i)
const int N = 2e5 + 10, mod = 998244353;
int n, f[N], inv[N], pw[N], ans;
signed main() {
    cin >> n; 
    pw[0] = 1; rep(i,1,n + 1) { pw[i] = (pw[i - 1] << 1); if (pw[i] >= mod) pw[i] -= mod; }
    f[0] = 1; f[1] = pw[n];
    inv[0] = inv[1] = 1; rep(i,2,n+1) inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
    rep(i,2,n + 1) f[i] = 1ll * f[i - 1] * (pw[n] - pw[i - 2] + mod) % mod * inv[i] % mod;
    rep(i,0,n + 1) { ans += f[i]; if (ans >= mod) ans -= mod; };
    cout << ans << '\n';
}
```

---

## 作者：Phartial (赞：9)

首先条件可以转化为 不存在元素个数为偶数的子集的异或和为 $0$。

接着可以进一步转化为 不存在元素个数奇偶性相同的两个子集（不相同）的异或和相等。

那么我们就有了一个推论：不存在元素个数 $>n+1$ 的满足条件的集合。

证明：由于一个集合的奇子集和偶子集数量都为 $2^{x-1}$（$x$ 为集合元素个数），如果存在元素个数 $>n+1$ 的集合 $S$，那么它的偶子集（或奇子集）的数量为 $2^{|S|-1}>2^n$，根据鸽巢原理，肯定会有两个元素个数奇偶性相同的子集的异或和相同，不符合条件，矛盾。

由于元素个数变成了 $O(n)$ 级别，这似乎在提示我们写一个元素个数相关的算法。

设 $f_i$ 表示大小为 $i$ 的符合条件的集合个数。

考虑如果我们知道了 $f_i$，怎么递推出 $f_{i+1}$。

首先自然的想法就是统计第 $i+1$ 个数有几种填法。

不难发现，如果第 $i+1$ 个数填了一个数不合法，那么它必定是和前 $i$ 个数组成的集合的某个奇子集的异或和相同。而由于奇子集的异或和两两不同，所以第 $i+1$ 个数的填法数量刚好为 $2^n-2^{i-1}$。最后，由于这是有顺序的，所以结果要乘上 $\frac{1}{i+1}$。

答案即为 $\sum f_i$。

---

## 作者：jijidawang (赞：9)

发现很多人都在发这题题解，那么我来复读一下 APJ 做法凑个热闹 .

APJifengc 第一小定理：
> 满足其所有非空子集的异或和不为 $0$ 的集合 $S\subseteq\{0,1,2,3,\cdots,2^n-1\}$ 的数量为
> $$\sum_{i=0}^n\dfrac1{i!}\prod_{j=1}^i(2^n-2^{j-1})$$

证明：见 [各种小定理](https://www.cnblogs.com/CDOI-24374/p/16531615.html#apjifengc-%E7%AC%AC%E4%B8%80%E5%B0%8F%E5%AE%9A%E7%90%86) .

这样就解决了没有奇数限制的问题 .

有限制的也差不多，注意到如果两个大小为奇数的集合 $A,B$ 异或和相等，则 $A\oplus B$ 是一个大小为偶数的异或和为 $0$ 的集合，不符题意，于是所有大小为奇数的集合异或和均不同 .

于是根据 APJifengc 第一小定理的类似推导即可得到答案就是
$$\sum_{i=0}^n\dfrac1{i!}\prod_{j=1}^i(2^n-2^{j-2})$$
corner case 省略 .

APJ 的另一个推法是考虑对于序列 $\{a\}$ 构造基底 $a_1\oplus a_2,a_1\oplus a_3,a_1\oplus a_4,\cdots$，这样显然是一组合法解 .

于是第 $i$ 步的时候有 $i-1$ 个数，也就有 $i-2$ 个基底，这样就表明把 APJifengc 第一小定理的 $2^n-2^{j-1}$ 改成 $2^n-2^{j-2}$ 即可，完整式子同上 .

Classical 做法见 Official Editorial .

---

## 作者：APJifengc (赞：7)

提供一种从线性代数角度去考虑的做法。

可能会有很多线性代数的名词，如果没有线性代数基础~~建议现在买本线性代数教材看一遍~~ 可以看一看别的题解的做法。

-----------------

我们首先考虑没有集合大小限制怎么做：也就是求任意非空子集的异或和都不等于 $0$ 的集合数。

由任意子集异或和，我们可以想到线性基，而线性基的本质实际上就是若干个基底张成的一个线性空间。任意非空子集异或和不等于 $0$ 就相当于这个集合与线性基的基底组成的集合是相等的。

基底需要满足的条件就是线性无关。假如现在基底的集合大小为 $i$，那么这些基底张成的线性空间中包含 $2^i$ 个向量，而这些向量显然不能选，那么可以选的向量就有 $2^n-2^i$ 个。那么如果基底集合大小为 $k$，选择基底的总方案数就是 $\displaystyle \prod_{i=1}^k \left(2^n-2^{i-1}\right)$。

注意到这时候选择的基底是有顺序的，而集合是无序的，那么我们给方案书乘一个 $\frac{1}{k!}$ 即可。最终的答案就是 $\displaystyle \sum_{i=0}^n \frac{1}{k!}\prod_{i=1}^k \left(2^n-2^{i-1}\right)$。

现在我们考虑这道题：任意大小为偶数的子集的异或和不等于 $0$。

我们先考虑任意大小为偶数的子集有什么性质：发现任意两个偶数大小的子集的对称差也是偶数大小。那么就可以发现，大小为偶数的子集所组成的数也可以构成一个原线性空间的线性子空间。

那么我们考虑构造这个线性子空间的一组基底。一种简单的构造方式是 $\{a_1 \oplus a_2, a_1 \oplus a_3, \cdots, a_1 \oplus a_n\}$。不难发现这组基底可以表示出所有集合大小为偶数的数。那么我们现在问题就和没有限制的一样了，只不过 $i$ 个数张成的线性空间的向量数变成了 $2^{i-1}$，而第一个数的选择没有限制。那么式子相应的改变一下即可。最终答案就是 $\displaystyle \sum_{i=0}^{n+1} \frac{1}{k!}\prod_{i=1}^k f_i,f_i=\begin{cases}2^n&(i=1)\\2^n-2^{i-2}&(i>1)\end{cases}$。

---

## 作者：Acoipp (赞：2)

直接做不太好入手，可以考虑集合的大小。

容易发现合法的 $S$ 的大小不会超过 $n+1$，如果超过，它的偶数子集的数量就至少是 $2^{|S|-1} \ge 2^{n+1}$，而一共只有 $2^n$ 个值，至少有两个值相同，选择这两个集合合并，大小依然是偶数，并且异或和为 $0$。

如果设 $f_i$ 表示大小为 $i$ 的合法集合有多少个，那么 $f_0=1,f_1=2^n$。

考虑转移，每次添加一个数进去，我们考虑能够添加的充要条件是什么。

如果这个数等于原来大小为奇数的集合的异或和，那么显然不行，否则一定可以，证明显然。

而且对于任意一个合法的 $S$，它的两个不同奇数大小的子集的异或和都不相同，如果相同，我们可以合并这两个集合，把重复出现的元素去掉，合并后的集合就是偶数大小的，并且异或和为 $0$。

于是加入一个元素的个数就是 $2^n-2^{i-1}$，前面是总的元素个数，后面是大小为 $i$ 的集合中奇数子集的数量，可以由组合恒等式推出来：

$$
\sum_{i=0}^{\lfloor \frac {n-1}{2} \rfloor} C_{n}^{2i+1}=2^{n-1}
$$

于是转移方程就是 $f_i \gets f_{i-1} \times (2^n-2^{i-1})$。

但是最后我们算的是排列数量，所以每个 $f_i$ 要除上 $i!$，或者转移的时候就除一个 $i$。

代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 200005
#define mod 998244353
using namespace std;
ll n,f[N],qmi[N],i,j,inv[N],ans;
int main(){
//	freopen("numgame.in","r",stdin);
//	freopen("numgame.out","w",stdout);
	ios::sync_with_stdio(false);
	cin>>n;
	inv[0] = inv[1] = 1,qmi[0] = 1;
	for(i=1;i<=n+1;i++) qmi[i] = qmi[i-1]*2%mod;
	for(i=2;i<=n+1;i++) inv[i] = inv[mod%i]*(mod-mod/i)%mod;
	f[0]=1,f[1]=qmi[n];
	for(i=2;i<=n+1;i++) f[i]=f[i-1]*inv[i]%mod*(qmi[n]-qmi[i-2]+mod)%mod;
	for(i=0;i<=n+1;i++) ans=(ans+f[i])%mod;
	cout<<ans<<endl;
	return 0;
} 
```

---

## 作者：bikuhiku (赞：2)


很抱歉翻译时把 $\subseteq$ 写成了 $\in$，我谢罪）

没想到那时候就看了，懒得现在才切。

考虑到 $S$ 合法，当且仅当不存在一个子集 $T$，使得 $\left\lvert T \right\rvert = 2k(k \in \mathbb{N}^{*})$ 且 $\operatorname{XOR}_{i \in T} i = 0$。

我们考虑 `dp`。

设 $\operatorname{dp}_i$ 为有多少个大小为 $i$ 的合法集合。

则有 $\operatorname{dp}_0 = 1$（只有空集本身合法）

接下来考虑每加入一个元素时，如何使原先的集合 $S$ 依然合法。

显然我们需要使 $S$ 的任意大小为奇数的子集 $T$ 加入元素后异或和不为 $0$。这意味着新加入的元素 $x$ 不能等于 $T$ 的异或和。

发现一个合法集合 $S$ 中大小为奇数的子集的异或和各不相同。证明也很简单，因为如果存在这样两个集合 $T,U$，满足 $T,U \subseteq S$，$\lvert T\rvert,\lvert U\rvert$ 均为奇数且 $\operatorname{XOR}_{i \in T} i \operatorname{xor}\operatorname{XOR}_{i \in U} i = 0$，则 $V = T \cup U$ 满足 $V \in S$，$\lvert V \rvert$ 为偶数且 $\operatorname{XOR}_{i \in V}i = 0$，与 $S$ 为合法集合相悖。

所以 $x$ 有 $\sum\limits_{i = 0}^{\left\lvert \frac{\lvert S \rvert - 1}{2} \right\rvert} \binom{\lvert S \rvert}{2i+1}$ 种不可取的值，即 $2^{\lvert S \rvert-1}$ 种。

所以转移就是 $\operatorname{dp}_i \gets \frac{\operatorname{dp}_{i-1} \times (2^N-2^{i-2})}{i}$。

发现实际上 $i$ 超过 $N+2$ 之后 $dp_{i}$ 就一直为 $0$ 了，所以时间复杂度 $\mathcal{O}(N)$。


---

## 作者：analysis (赞：0)

要计算集合 $S \in \{0,1,2,\ldots,2^N-1\}$ 的个数，满足 $S$ 的所有偶数大小的子集异或和非 $0$。

如果没有偶数大小的限制，显然就是序列线性无关，即序列的秩为序列本身。

直接 $O(n)$ 计数即可，注意序列无序。

$$
1 + \sum_{i=1}^{2^n}\frac{1}{i!}\prod_{j=0}^{i-1}(2^n-2^i)
$$

但问题在于题目只关注偶序列。

对于这种特殊限制问题，我们考虑特殊构造一组秩来表示。

我们考虑先不用 $a_1$，当某次选择只选了奇数个时我们再加入 $a_1$。

于是构造方案就很明显了，即：

$$
\{a_1 \oplus a_2,a_1 \oplus a_3,\cdots,a_1 \oplus a_n\}
$$

这个序列可以对应全体偶数子集。

于是答案就是让这个序列线性无关。

所以得到答案：

$$
1 + \sum_{i=1}^{2^n}\frac{1}{i!}\prod_{j=1}^{i}f_j,f_i=\begin{cases}2^n &&& n=1 \\ 2^n - 2^{i-1} &&& otherwises\end{cases}
$$

```cpp
#include<bits/stdc++.h>
#define int long long
const int mod = 998244353;
using namespace std;
int n,ans = 1,tmp = 1;
int fpow(int a,int b=mod-2)
{
    int r = 1;
    while(b)
    {
        if(b & 1)r = r * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return r;
}
signed main()
{
    cin >> n;
    int pwn = fpow(2,n),pwi=fpow(2);
    for(int i=1;i<=n+1;i++)
    {
        if(i == 1)
        {
            tmp = tmp * pwn % mod;
        }
        else
        {
            pwi = pwi * 2 % mod;
            tmp = tmp * (pwn - pwi + mod) % mod;
            tmp = tmp * fpow(i) % mod;
        }
        ans = (ans + tmp) % mod;
    }
    cout<<ans;
}
```

---

## 作者：User_Unauthorized (赞：0)

我们按增量法去考虑方案数，即考虑在一个合法集合的基础上添加哪些元素可以继续得到一个合法集合。

假设我们现在存在一个合法集合 $S$，设集合 $T \subseteq S$ 且满足 $\left\lvert T \right\rvert$ 为奇数，设 $X = \bigoplus\limits_{x \in T} x$。那么显然 $X$ 不能被添加进 $S$ 集合。同时我们有 $X \notin S \lor \left\lvert T \right\rvert = 1$，否则集合 $T \setminus \left\{X \right\}$ 的大小为偶数，同时异或和为 $0$，与 $S$ 为合法集合的事实冲突。

因此我们在 $S$ 集合的基础上可以添加的元素为 $2^N - \left\lvert\left\{X \mid \bigoplus\limits_{x \in T} x, T \subseteq S \land \left\lvert T \right\rvert \text{is odd.}\right\}\right\rvert$，即所有可能值除去所有大小为奇数的子集的异或和的集合。同时可以发现，由于所有大小为 $1$ 的子集 $T$ 的异或和集合等于 $S$ 集合，因此无需考虑集合元素不可重复的要求。

我们下面考虑如何计算 $\left\lvert\left\{X \mid \bigoplus\limits_{x \in T} x, T \subseteq S \land \left\lvert T \right\rvert \text{is odd.}\right\}\right\rvert$，我们尝试证明对于任意两个满足大小为奇数的子集 $T_1, T_2$，其元素异或和不同。考虑使用反证法，若存在两个大小为奇数的子集 $T_1, T_2$ 满足 $\bigoplus\limits_{x \in T_1} x = \bigoplus\limits_{x \in T_2} x$，那么集合 $T_1 \cup T_2$ 的元素异或和为 $0$ 且集合大小为 $\left\lvert T_1 \right\rvert + \left\lvert T_2 \right\rvert - \left\lvert T_1 \cap T_2 \right\rvert$，不难发现其值为偶数，这与 $S$ 为合法集合冲突，进而命题成立。

因此我们可以得出 $\left\lvert\left\{X \mid \bigoplus\limits_{x \in T} x, T \subseteq S \land \left\lvert T \right\rvert \text{is odd.}\right\}\right\rvert$ 的值实际上为 $S$ 中奇数子集的数量，根据二项式定理可以得出其值为 $2^{\left\lvert S \right\rvert - 2}$，不难发现当 $\left\lvert S \right\rvert = N + 2$ 时不能加入的元素数量为 $2^N$，即可以加入的元素数量为 $0$，因此集合大小上界为 $\mathcal{O}(N)$ 级别，考虑以集合大小为状态进行递推。

具体的，设 $f_i$ 表示大小为 $i$ 的合法集合数量，边界状态为 $f_0 = 1, f_1 = 2^N$，对于 $i \ge 2$，我们有转移：

$$f_i = \frac{f_{i - 1} \times \left(2^N - 2^{i - 2}\right)}{i}$$

其中除去 $i$ 是为了保证集合的无序性。

复杂度为 $\mathcal{O}(N)$。

---

## 作者：Judgelight (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_arc146_c)

---

首先考虑一个 $k$ 个元素的集合有 $2^{k-1}$ 次方个奇数大小的集合和 $2^{k-1}$ 个偶数大小的集合，这个的证明可以通过组合得出。

考虑条件等价于不能有两个偶数大小的集合相等（可以为空），所以偶数大小的集合的异或值都不能相等，即最多 $2^{n}$ 个，那么集合大小最大就是 $n+1$。

设 $f_i$ 表示 $i$ 个元素的满足条件的集合数量，考虑 $f_0=1,f_1=2^n$，我们考虑只要加入一个元素的时候它不与任意奇数集合的异或和相等即可，所以 $f_i=(2^n-2^{i-2})f_{i-1}$。注意最后考虑算的是集合的排列，所以每个 $f_i$ 需要除一个 $i!$。

---

## 作者：szydxf (赞：0)

注意到题目要求是是 $S$ 的长度为奇数子集异或和互不相同，并且 $S⊆\{0,1,2,...,2^n-1\}$，可得当 $|S|>n+1$ 时，是没有贡献的。

证明：当 $|s|= n+k,k\ge2$ 时若有贡献，则 $S$ 要有 $2^{n+k-1}$ 个异或和不同的奇数子集。而由题目得，每个子集的异或和取值范围是 $[0,2^n-1]$，两者显然矛盾。

设 $f_i$ 为大小为 $i$ 的合法集合个数，则显然$f_0=1,ans=\sum^{n+1}_{i=0} f_i$。

$f_i$ 如何转移到 $f_{i+1}$？考虑剩还有多少种元素，与大小为 $i$ 的子集组合，即 $\frac 1 {i+1} \times f_i  (2^n - 2^{i-1}) \rightarrow f_{i+1}$。

值得注意的是，集合是无序的，所以每一步转移要乘上 $\frac 1 {i+1}$。[code](https://atcoder.jp/contests/arc146/tasks/arc146_c)

---

