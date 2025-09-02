# [ARC106F] Figures

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc106/tasks/arc106_f

高橋君はフィギュアを組み立てようとしています。このフィギュアは、 $ N $ 個の部品(部品 $ 1 $ , 部品 $ 2 $ , ..., 部品 $ N $ )と、 $ N-1 $ 個の接続用部品から成ります。部品同士は区別が出来ますが、接続用部品同士は区別が出来ません。

部品 $ i $ には、$ d_i $ 個の接続用部品を挿す穴(穴 $ 1 $ , 穴 $ 2 $ , ..., 穴 $ d_i $ )が空いています。各部品の穴同士は区別が出来ます。 各接続用部品は、 $ 2 $ 個の部品の穴に挿し込まれ、それら $ 2 $ 個の部品を接続します。 $ 1 $ つの穴に複数の接続用部品を挿し込むことは出来ません。

以下の性質を満たすフィギュアのことを、完成形と呼びます。

- $ N-1 $ 個の接続用部品が全て部品の接続に使われている。
- 部品を頂点とし、 接続用部品で接続された部品に対応する頂点組に辺が存在する $ N $ 頂点 $ N-1 $ 辺の無向グラフを考えた際に、このグラフは連結である。

$ 2 $ つの完成形について、全ての穴の組についてその $ 2 $ つを接続する接続用部品が存在するか否かが一致するとき、$ 2 $ つの完成形が同じであると見なします。

完成形が何種類あるかを答えてください。 ただし、答えは非常に大きくなることがあるので、 $ 998244353 $ で割った余りを出力してください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ d_i\ <\ 998244353 $

### Sample Explanation 1

例えば、部品 $ 1 $ の穴 $ 1 $ と部品 $ 3 $ の穴 $ 3 $ を接続し、部品 $ 2 $ の穴 $ 1 $ と部品 $ 3 $ の穴 $ 1 $ を接続したフィギュアは、完成形として認められます。

## 样例 #1

### 输入

```
3
1 1 3```

### 输出

```
6```

## 样例 #2

### 输入

```
3
1 1 1```

### 输出

```
0```

## 样例 #3

### 输入

```
6
7 3 5 10 6 4```

### 输出

```
389183858```

## 样例 #4

### 输入

```
9
425656 453453 4320 1231 9582 54336 31435436 14342 423543```

### 输出

```
667877982```

# 题解

## 作者：joke3579 (赞：16)

## $\text{Solution 1}$ 生成法计数

官方题解采用的方法。

首先可以发现只有当 $\sum d_i \ge 2(n - 1)$ 时有解。

随后考虑如何生成所有可能的方案。我们称一个联通的子图为一个分量，最开始有 $n$ 个分量。
最开始在每个分量上选取一个特殊点。随后按如下方式操作：

- 将分量数量减小到 $2$。
 1. 选择一个非特殊点 $a$。
 2. 选择一个不与点 $a$ 位于同一分量中的特殊点 $b$。
 3. 连接 $a,b$。新分量的特殊点是其中一个距离 $a,b$ 最近的可连边的点。
- 连接最后的两个分量上的特殊点。

最开始选择特殊点的方案数是 $\prod_{i=1}^n d_i$。记 $S = \sum_{i=1}^n d_i$，第 $i$ 次选择时非特殊点数量为 $(S - n - (i-1))$ 个，能连接的联通块数是 $(n - i)$ 个，自然导出了方案数
$$\prod_{i=1}^n d_i\times \prod_{i=1}^{n-2} (n - i) (S - n - (i - 1)) = \prod_{i=1}^n d_i\times  (n - 1)!\times \prod_{i=0}^{n-3} (S - n - i) $$

考虑生成方式，我们发现同一棵树会以不同的加边顺序在答案中被统计 $(n-1)!$ 次，因此最终答案为
$$\prod_{i=1}^n d_i\times \prod_{i=0}^{n-3} (S - n - i) $$

## $\text{Solution 2}$ 生成函数

首先固定每个点 $i$ 在最终生成的树中的度数 $r_i$。

由 prufer 序列导出结论，一棵满足上述度数条件的树的计数是
$$\frac{(n - 2)!}{ \prod_{i=1}^n (r_i - 1)! }$$

证明考虑计数 prufer 序列，元素 $i$ 在其中出现了 $r_i - 1$ 次。

每个点在连接时是有序的，因此在度数固定为 $r$ 的情况下，贡献是
$$\frac{(n - 2)!}{ \prod_{i=1}^n (r_i - 1)! }\times \prod_{i=1}^n A_{d_i}^{r_i} $$

可以发现 $\sum r_i = 2(n - 1)$。因此不妨从卷积的角度入手，枚举 $r_i$ 的取值。

发现 $(n - 2)!$ 是所有可能都会贡献的，因此只需要生成剩余部分即可。

设 $F_i(x)$ 为点 $i$ 对答案的贡献的生成函数，有

$$\begin{aligned}

F_i(x) &= \sum_{k=0}^{\infty} \frac{A_{d_i}^k}{(k - 1)!}x^k
\\ & = \sum_{k=0}^{\infty} \binom{d_i} k k \ x^k
\\ & =  d_i \sum_{k=1}^{\infty} \binom{d_i - 1} {k - 1}\ x^k
\\ & = d_i x \sum_{k=0}^{\infty} \binom{d_i - 1} {k} \ x^k
\\ & = d_i x (1 + x)^{d_i - 1}
\end{aligned}$$

可以写出答案
$$\begin{aligned}
& (n - 2)!\times [x^{2(n-1)}] \prod_{i=1}^nF_i(x)
\\ = \ & (n - 2)!\times [x^{2(n-1)}] \prod_{i=1}^n d_i x (1 + x)^{d_i - 1}
\\ = \ & (n - 2)!\times\prod_{i=1}^n d_i  \times [x^{n - 2}] \prod_{i=1}^n  (1 + x)^{d_i - 1}
\end{aligned}$$

记 $S = \sum_{i=1}^n d_i$，有

$$\begin{aligned}
& (n - 2)!\times\prod_{i=1}^n d_i  \times [x^{n - 2}] \prod_{i=1}^n  (1 + x)^{d_i - 1}
\\ = \ & (n - 2)!\times\prod_{i=1}^n d_i  \times [x^{n - 2}] (1 + x)^{S - n}
\\ = \ & (n - 2)!\times\prod_{i=1}^n d_i  \times \binom{S - n}{n-2}
\\ = \ & \prod_{i=1}^n d_i \times (S - n)^{\underline{n - 2}}
\\ = \ & \prod_{i=1}^n d_i\times \prod_{i=0}^{n-3} (S - n - i)
\end{aligned}$$

两种做法得到了相同的答案。
总时间复杂度为 $O(n)$。

个人认为 $\text{Solution 2}$ 更简单易懂一些。

$\text{code : }$

```cpp
#include <bits/stdc++.h>
using namespace std; 
#define rep(i,s,t) for (register int i = (s), i##_ = (t) + 1; i < i##_; ++ i)
const int mod = 998244353;
int n, prod = 1, sum, tmp;
signed main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n; 
    rep(i,1,n) {
        cin >> tmp; 
        prod = 1ll * prod * tmp % mod, sum += tmp;
        if (sum >= mod) sum -= mod;
    }
    rep(i,0,n-3) prod = 1ll * prod * (sum - n - i) % mod;
    cout << prod << '\n';
}
```

---

## 作者：Pengzt (赞：10)

# Figures

[题目链接](https://www.luogu.com.cn/problem/AT_arc106_f)。[cnblogs](https://www.cnblogs.com/Pengzt/p/17746088.html)。[luogu](https://www.luogu.com.cn/article/mgfzu3tq)。

#### Problem

有 $N$ 个点，每个点有 $d_i$ 个**互不相同、可被区分**的孔，每次可以选择两个不同点，连接两个未被连接过的孔，有多少种方案使得最后形成一棵树。合法方案中可以不把孔填满。

#### Sol

模拟赛题。

由于除根节点外每个点只有一个父亲节点，考虑从这里入手。

给每个点指定一个特殊点，让这个特殊点连向它的父亲节点的非特殊点。此时只有根节点没有特殊点，可随便指定一个特殊点，因为是无根树，且根节点最后是会与某个节点留下来的。指定特殊点的方案数易知：$\prod \limits_{i = 1}^{n} d_i$。

令 $S = \sum d_i$，因为每个点是由特殊点连向非特殊点，又不能重复经过点，故需再乘上 $\prod \limits_{i = 0}^{n - 3}(S - n - i)$。

所以最后的答案为 $\prod d_i \times\prod(S - n - i)$。

时间复杂度线性。

上面的做法可能不是很好想到？下面是一个套路的代数推导的做法：

记第 $i$ 个点有 $c_i$ 个孔。$\binom{n}{a_1, a_2, a_3, \cdots, a_m}$ 表示多重集组合数。$a^{\underline b}$ 表示 $a$ 的 $b$ 次下降幂，即 $\frac{a!}{(a - b)!}$。

若知道度数序列 $d$，则方案数为 $\binom{n - 2}{d_1 - 1, d_2 - 1, \cdots, d_n - 1} \times \prod c_i^{\underline{d_i}}$。

于是最后的方案数为：
$$
\sum\limits_{|d| = n, \sum d_i = 2n - 2, \forall i\in[1, n], d_i > 0} \binom{n - 2}{d_1 - 1, d_2 - 1, \cdots, d_n - 1} \prod\limits_{i = 1}^{n} c_i^{\underline{d_i}}
$$
然后就是正常的推式子：
$$
(n - 2)! \times\sum\limits_{|d| = n, \sum d_i' = n - 2, \forall i\in[1, n], d_i \ge 0} \prod \frac{c_i!}{d_i'!\times (c_i - d_i' - 1)!} \\
= (n - 2)! \times (\prod c_i) \times \sum\limits_{|d| = n, \sum d_i' = n - 2, \forall i\in[1, n], d_i \ge 0} \prod \binom{c_i - 1}{d_i'}
$$
发现后面的那部分其实就是多元情况的范德蒙德卷积，记 $S = \sum (c_i - 1)$，：为
$$
(n - 2)! \times (\prod c_i) \times \binom{S - n}{n - 2} \\
(S - n)^{\underline{n - 2}} \times \prod c_i
$$


Update on 25.02.24：增加代数推导的做法。

#### Code

```cpp
#include<bits/stdc++.h>
#define ios ios::sync_with_stdio(0); cin.tie(0);
#define pb push_back
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int inf = 1e9, infi32 = 2147483647, mod = 998244353;
const ll INF = 1e18;

const int N = 2e5 + 10;
int n;
int d[N];

int main () {
	ios
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> d[i];
	int sum = 0, ans = 1;
	for (int i = 1; i <= n; i++) sum = (sum + d[i]) % mod, ans = 1ll * ans * d[i] % mod;
	for (int i = sum - n * 2 + 3; i <= sum - n; i++) ans = 1ll * ans * (i + mod) % mod;
	cout << ans << "\n";
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：6)

# ARC106F 题解



## 题目大意

> 有 $n$ 个点，每个点有 $a_i$ 个孔，每次可以选择两个不同点，连接两个未被连接过的孔，有多少中方案使得最后形成一棵树，答案对 $998244353$ 取模。
>
> 数据范围：$n\le 2\times 10^5$。



## 思路分析

首先，根据 Prufer 序列的结论，我们枚举每个点的度数 $d_i$，对应的生成树应该有 $\dfrac{(n-2)!}{\prod(d_i-1)!}$ 个，而对于每个点，把边连到孔上的方案数有 $a_i^{\underline{d_i}}=\dfrac{a_i!}{(a_i-d_i)!}$ 种，那么我们得到答案的表达式：
$$
\begin{aligned}
\mathrm{Answer}
&=\sum_{\sum d_i=2n-2}\dfrac{(n-2)!}{\prod(d_i-1)!}\times \prod\dfrac{a_i!}{(a_i-d_i)!}\\
&=\sum_{\sum d_i=2n-2}\dfrac{(n-2)!}{\prod(d_i-1)!}\times \dfrac{\prod a_i!}{\prod(a_i-d_i)!}
\end{aligned}
$$
注意到分子非常有潜力写成组合数的形式，于是稍作变形得到：
$$
\begin{aligned}
\mathrm{Answer}
&=\sum_{\sum d_i=2n-2}\dfrac{(n-2)!}{\prod(d_i-1)!}\times \dfrac{\prod a_i!}{\prod(a_i-d_i)!}\\
&=(n-2)!\times\dfrac{\prod a_i!}{\prod(a_i-1)!}\times\sum_{\sum d_i=2n-2} \prod \dfrac{(a_i-1)!}{(d_i-1)!(a_i-d_i)!}\\
&=(n-2)!\times\prod a_i\times\sum_{\sum d_i=2n-2} \prod \binom{a_i-1}{d_i-1}
\end{aligned}
$$
注意到 $d_i-1\in[0,a_i-1]$，因此最后那个求和号里的东西可以看成一个多元范德蒙德卷积，记 $\sum a_i=S$，那么得到：
$$
\begin{aligned}
\mathrm{Answer}
&=(n-2)!\times\prod a_i\times\sum_{\sum d_i=2n-2} \prod \binom{a_i-1}{d_i-1}\\
&=(n-2)!\times\prod a_i\times\binom{S-n}{n-2}\\
&=\prod a_i\times(S-n)^{\underline{n-2}}
\end{aligned}
$$
判断 $S\ge 2n-2$ 后暴力计算即可。

时间复杂度 $\mathcal O(n)$。



## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e5+1,MOD=998244353;
int a[MAXN];
signed main() {
	int n,sum=0,ans=1;
	scanf("%lld",&n);
	for(int i=1;i<=n;++i) scanf("%lld",&a[i]),sum+=a[i];
	if(sum<2*n-2) { puts("0"); return 0; }
	for(int i=0;i<n-2;++i) ans=(sum-n-i)%MOD*ans%MOD;
	for(int i=1;i<=n;++i) ans=ans*a[i]%MOD;
	printf("%lld\n",ans);
}
```



---

## 作者：EuphoricStar (赞：4)

晚自习的时候胡出来的做法（（（

首先你会发现题目等价于求 $\sum\limits_{(\sum\limits_{i=1}^n a_i) = 2(n-1) \land \forall i \in [1,n], 1 \le a_i \le d_i} \prod\limits_{i=1}^n \dfrac{d_i!}{(d_i - a_i)!}$。翻译一下就是枚举每个点的度数 $a_i$（一个结论是当度数总和 $= 2(n-1)$ 并且每个点的度数都为正整数时一定能构造出合法的树），然后乘上对应的有序选择点内的洞的方案。

你会发现如果固定 $a_i$，这个东西的组合意义是把 $\sum\limits_{i=1}^n d_i$ 个数分成 $n$ 组每组 $d_i$ 个数，再在每组有序选出 $a_i$ 个数。$a_i \ge 1$ 比较烦，不妨整体减 $1$，也就是一开始每组先选一个数，这样就变成了 $a_i \ge 0$。然后就发现可以把组合并起来考虑，即答案为先在每组中选一个数再在 $\sum\limits_{i=1}^n (d_i - 1)$ 个数内有序选择 $\sum\limits_{i=1}^n (a_i - 1) = n - 2$ 个数的方案数，即 $(\prod\limits_{i=1}^n d_i) \dfrac{(\sum\limits_{i=1}^n (d_i - 1))!}{(n-2)!}$，这个东西可以 $O(n)$ 计算。

[code](https://atcoder.jp/contests/arc106/submissions/40727091)

---

## 作者：win114514 (赞：3)

生成函数大法好。

### 思路

考虑 prufer 序列。

如果 $n$ 个点的度数确定，那么生成树个数为：

$$
\frac{(n-2)!}{\prod (d_i-1)!}
$$

那么在此题中，$n$ 个点的度数确定，那么方案数为：

$$
\frac{(n-2)!}{\prod (d_i-1)!}\prod\frac{a_i!}{(a_i-d_i)!}
$$

其中，$\sum d_i=2\times n-2$。

容易发现这是一个卷积形式。

我们可以将每一个点的贡献拿出来，即 $\frac{a_i!}{(a_i-d_i)!(d_i-1)!}$。

那么可以设生成函数：

$$
f_i(x)=\sum_{j=1}\frac{a_i!x^j}{(a_i-j)!(j-1)!}
$$

有：

$$
\begin{align}
f_i(x)&=\sum_{j=1}\frac{a_i!x^j}{(a_i-j)!(j-1)!}\\
&=x\sum_{j=0}a_i!\frac{x^j}{(a_i-j+1)!j!}\\
&=x\sum_{j=0}a_i\frac{x^j(a_i-1)!}{(a_i-j+1)!j!}\\
&=x\sum_{j=0}a_ix^j\binom{a_i-1}{j}\\
&=a_ix\sum_{j=0}x^j\binom{a_i-1}{j}\\
&=a_ix(1+x)^{a_i-1}
\end{align}
$$

我们要求的是：

$$
\begin{align}
(n-2)![x^{2\times n-2}]\prod_{i=1}^n a_ix(1+x)^{a_i-1}
\end{align}
$$

这东西也可以推一下：

$$
\begin{align}
&=(n-2)![x^{2\times n-2}]\prod_{i=1}^n a_ix(1+x)^{a_i-1}\\
&=(n-2)![x^{n-2}]\prod_{i=1}^n a_i(1+x)^{a_i-1}\\
&=(n-2)!\prod_{i=1}^n a_i\times [x^{n-2}](1+x)^{\sum a_i-n}\\
&=(n-2)!\prod_{i=1}^n a_i\times \binom{\sum a_i-n}{n-2}\\
&=\prod_{i=1}^n a_i\times \prod_{i=0}^{n-3} (\sum a_i-n-i)\\
\end{align}
$$

时间复杂度：$O(n)$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int mod = 998244353;

int n, m, s;
int a[200010];

signed main() {
  cin >> n, s = 1;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= n; i++) (m += a[i]) %= mod;
  for (int i = 1; i <= n; i++) (s *= a[i]) %= mod;
  for (int i = 0; i <= n - 3; i++) (s *= (m - n - i)) %= mod;
  cout << (s + mod) % mod << "\n";
}
```

---

## 作者：tzl_Dedicatus545 (赞：3)

第一次自己独自做出来 ARC 的 F 啊，纪念一下。

其实一开始看错题了，然后有一个 $\prod \frac{1}{d_i}$ 一直消不掉诶，然后自闭开题解才发现这个孔是互不相同的，翻译没翻译出来，不过去掉这个积之后我的式子就是答案了。。。

数树题肯定一眼 Prufer 序列，根据 Prufer 序列的结论，我们肯定要枚举最终每个点的度数 $d_i$，这可以组成

$$\dfrac{(n-2)!}{\prod (d_i-1)!}$$

个树，然后你还要乘上一个选孔的方案，就是 $\prod \dfrac{a_i!}{(a_i-d_i)!}$。

所以答案为：

$$\dfrac{(n-2)!}{\prod (d_i-1)!}\prod \dfrac{a_i!}{(a_i-d_i)!}$$

$$=(n-2)!\prod \dfrac{a_i!}{(a_i-d_i)!(d_i-1)!}$$
$$=(n-2)!\prod a_i\prod \dfrac{a_i!}{(a_i-d_i)!(d_i-1)!}$$

$$=(n-2)!\prod a_i\prod \dbinom{a_i-1}{d_i-1}$$

根据多元范德蒙德（证明考虑组合意义）

$$=(n-2)!\prod a_i \dbinom{\sum (a_i-1)}{n-2}$$

这是因为 $\sum d_i=2n-2$

然后就做完了

---

## 作者：Purslane (赞：2)

# Solution

考虑 Prufer 序列，其中 $1$ 是根（枚举了树的形态）

假设每个数在长度为 $n-2$ 的 Prufer 序列中出现了 $t_i$ 次，则它的度数是 $t_i+1$。

因此对于给定的一组 $t$，答案就是：

$$
\dfrac{(n-2)!}{\prod_{i=1}^n t_i!} \times \prod_{i=1}^n d_i^{\underline{t_i+1}}
$$

考虑把两个乘积合并，得到一个

$$
\dfrac{d_i!}{(d_i-t_i-1)! \times t_i!}
= d_i \binom{d_i-1}{t_i}
$$

因此设 $S = \sum_{i=1}^n d_i-1$，则答案为：

$$
(n-2)! \times \binom{S}{n-2} \times \prod_{i=1}^n d_i = S^{\underline{n-2}} \prod_{i=1}^n d_i
$$

可以 $O(n)$ 算，代码很短：

```cpp
#include<bits/stdc++.h>
#define int long long 
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
using namespace std;
const int MAXN=2e5+10,MOD=998244353;
int n,ans=1,a,sum;
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) cin>>a,sum=(sum+a-1)%MOD,ans=ans*a%MOD;
	ffor(i,0,n-3) ans=ans*(sum-i)%MOD;
	cout<<ans;
	return 0;
}
```

---

## 作者：ReTF (赞：2)

设点 $i$ 的度数为 $d_i$，则其在生成树的 Prufer 序列中出现 $d_i-1$ 次。

则 Prufer 序列有 $\dbinom{n-2}{d_1-1,d_2-1,\dots,d_n-1}$ 种可能性。

因为往 $i$ 上连 $d_i$ 条边有 $\dbinom{a_i}{d_i}d_i!$ 种方式，所以答案是

$$\begin{aligned}
&\sum_{\sum d_i=2n-2}\dbinom{n-2}{d_1-1,\dots,d_n-1}\times \prod \dbinom{a_i}{d_i}d_i!\\
=&\sum_{\sum e_i=n-2}\dbinom{n-2}{e_1,\dots,e_n}\times \prod \dfrac{a_i!}{(a_i-e_i-1)!}\\
=&\sum_{\sum e_i=n-2}(n-2)!\times \prod \dfrac{a_i!}{(a_i-e_i-1)!\times e_i!}\\
=&\sum_{\sum e_i=n-2}(n-2)!\times \prod a_i\dbinom{a_i-1}{e_i}\\
=&\left(\prod a_i\right)\times (n-2)!\times \dbinom{\sum a_i-n}{n-2}\\
=&\left(\prod a_i\right)\times \left(\sum a_i-n\right)^{\underline{n-2}}\\
\end{aligned}$$

可以直接 $O(n)$ 算。

```cpp
#include"iostream"
using namespace std;
int n,S,A=1,m=998244353;
int main(){
	cin>>n;
	for(int i=0,t;i<n;i++)cin>>t,A=1ll*A*t%m,S=(S+t-1)%m;
	for(int i=0;i<n-2;i++)A=1ll*A*(S-i+m)%m;
	cout<<A;
}
```

---

## 作者：Fido_Puppy (赞：2)

题目传送门：[[ARC106F] Figures](https://www.luogu.com.cn/problem/AT_arc106_f)

> 组合意义天地灭，代数推导保平安。——tiger0133

## 思路

考虑 prufer 序列，我们假设第 $i$ 个点的在 prufer 序列上出现的次数为 $d_i$，则可以写出答案：

$$\sum_{\sum d_i = n - 2} {n - 2 \choose d_1, d_2, \cdots, d_n} \times \prod_{i = 1} ^ n {a_i} ^ {\underline{d_i + 1}}$$

由于每个点中的 $a_i$ 个孔互不相同，我们考虑使用 EGF 来计数，所以答案可以写作：

$$\left[ \dfrac{x ^ {n - 2}}{(n - 2)!} \right] \prod_{i = 1} ^ n \sum_{j = 0} ^ {\infty} {a_i} ^ {\underline{j + 1}} \times \dfrac{x ^ j}{j!}$$

$$= \left[ \dfrac{x ^ {n - 2}}{(n - 2)!} \right] \prod_{i = 1} ^ n \sum_{j = 0} ^ {\infty} \dfrac{a_i ! \times x ^ j}{(a_i - j - 1)! \times j!}$$

$$= \left[ \dfrac{x ^ {n - 2}}{(n - 2)!} \right] \prod_{i = 1} ^ n a_i \times \sum_{j = 0} ^ {\infty} \dfrac{(a_i - 1)! \times x ^ j}{(a_i - j - 1)! \times j!}$$

$$= \left[ \dfrac{x ^ {n - 2}}{(n - 2)!} \right] \prod_{i = 1} ^ n a_i \times \sum_{j = 0} ^ {\infty} {a_i - 1 \choose j} x ^ j$$

根据二项式定理：

$$\left[ \dfrac{x ^ {n - 2}}{(n - 2)!} \right] \prod_{i = 1} ^ n a_i \times \sum_{j = 0} ^ {\infty} {a_i - 1 \choose j} x ^ j$$

$$= \left[ \dfrac{x ^ {n - 2}}{(n - 2)!} \right] \prod_{i = 1} ^ n a_i \times {(x + 1)} ^ {a_i - 1}$$

$$= \left[ \dfrac{x ^ {n - 2}}{(n - 2)!} \right] {(x + 1)} ^ {\sum (a_i - 1)} \times \prod_{i = 1} ^ n a_i$$

根据二项式定理，生成函数第 $n - 2$ 项的系数为：

$${\sum_{i = 1}^n (a_i - 1) \choose n - 2}$$

所以答案为：

$${\sum_{i = 1}^n (a_i - 1) \choose n - 2} \times (n - 2)! \times \prod_{i = 1}^n a_i$$

$$= {\left(\sum_{i = 1}^n (a_i - 1)\right)} ^ {\underline{n - 2}} \times \prod_{i = 1} ^ n a_i$$

---

## 作者：jiayixuan1205 (赞：1)

## 题解：AT_arc106_f [ARC106F] Figures
不会生成函数，呜呜/ll。

还是 $\text{prufer}$ 序列。首先我们思考直接拿 $n$ 个点建树的式子，应该是 $\dfrac{(n-2)!}{\prod(d_i-1)!}$，但是我们还需要选孔，所以要再乘上一个 $\prod \dfrac{a_i!}{(a_i-d_i)!}$ 然后把他们乘起来就是答案，现在是神秘的化简环节：
$$(n-2)! \prod \dfrac{a_i!}{(a_i-d_i)!(d_i-1)!}$$
$$(n-2)! \prod a_i \dfrac{(a_i-1)!}{(a_i-d_i)!(d_i-1)!}$$
$$(n-2)! \prod a_i \times \prod \binom{d_i-1}{a_i-1}$$
$$(n-2)! \prod a_i \times  \binom{\sum d_i-n}{\sum a_i-n}$$
$$(n-2)! \prod a_i \times  \binom{n-2}{\sum a_i-n}$$
请别忘记计算组合数 $C_n^m$ 复杂度只和 $m$ 有关，然后直接算就可以了。
### 代码展示
```cpp
#include<bits/stdc++.h>
#define int long long 

using namespace std;

const int mod = 998244353;
const int N = 2e5+10;
int sum=0;
int n,a[N];

inline int qpow(int a,int b)
{
    int res=1;
    while(b)
    {
        if(b&1) res=res*a%mod;
        a=a*a%mod;
        b=b/2;
    }
    return res;
}

inline int C(int n,int m)
{
    int res=1;
    for(int i=n;i>=n-m+1;i--) res=res*i%mod;
    int tmp=1;
    for(int i=1;i<=m;i++) tmp=tmp*i%mod;
    tmp=qpow(tmp,mod-2);
    return res*tmp%mod;
}

signed main()
{
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) {cin>>a[i];sum=(sum+a[i])%mod;}
    int ans=1;
    for(int i=1;i<=n;i++) ans=(ans*a[i])%mod;
    for(int i=1;i<=n-2;i++) ans=ans*i%mod;
    cout<<ans*C(sum-n,n-2)%mod<<'\n';
    return 0;
}
```

---

## 作者：shinkuu (赞：1)

记录一下自己第一次用 GF 推式子。

翻译一下就是这颗树每个点的度数 $m\le a_u$，并且要额外乘上 $a_u^{\underline m}$ 的权值，求所有树的权值之和。

由于是 $deg_u$ 的限制，所以考虑 prufer 序列。考虑枚举每个点的度数为 $deg_u$，变成 prufer 序列，则有 $ans=(n-2)!\sum\limits_{\sum deg_i=n\times2-2}\prod\limits_i\frac{a_i^{\underline{dep_i}}}{(deg_i-1)!}=(n-2)!\sum\limits_{\sum deg_i=n\times2-2}\prod\limits_i\binom{a_i}{deg_i}deg_i$。可以背包 dp $O(n^2)$ 解决。

但是 $O(n^2)$ 显然不够，不过背包很难优化。此时想到 GF（但是我一道 GF 都没做过是怎么想到的？？？）。设 $F_i(x)$ 为第 $i$ 个点对应的 GF，则有：

$$F_i(x)=\sum_{j}\binom{a_i}{j}jx^j$$

$$=\sum_j\frac{a_i!}{(a_i-j)!j!}jx^j$$

$$=\sum_j\frac{a_i!}{(a_i-j)!(j-1)!}x^j$$

$$=a_i\sum_j\frac{(a_i-1)!}{(a_i-j)!(j-1)!}x^j$$

$$=a_i\sum_j\binom{a_i-1}{j-1}x^j$$

注意到此时 $j-1$ 比较不好看，于是我们默认给每个点分配一个度数（事实上这也是必须要的），则限制变成 $\sum deg_i=n-2$，上式变成 $a_i\sum_j\binom{a_i-1}{j}x^j$。

要求的即为 $[x^{n-2}]\prod_iF_i(x)$。

将 $F_i(x)$ 转为封闭形式即为 $F_i(x)=m(1+x)^{m-1}$。

则 $\prod_iF_i(x)=(\prod a_i)(1+x)^{\sum a_i-n}$。

再转回形式幂级数为 $\prod_iF_i(x)=(\prod a_i)\sum\limits_{j}\binom{\sum a_i-n}{j}$。

则 $ans=(n-2)!(\prod a_i)\binom{\sum a_i-n}{n-2}$。$O(n)$ 解决。

code：

```cpp
int n,m,a[N];
il int qpow(int x,int y){
	int ret=1;
	while(y){
		if(y&1){
			ret=1ll*ret*x%mod;
		}
		x=1ll*x*x%mod,y>>=1;
	}
	return ret;
}
il int binom(ll x,int y){
	if(x<0||y<0||x<y){
		return 0;
	}
	int a=1,b=1;
	for(ll i=x;i>=x-y+1;i--){
		a=1ll*a*(i%mod)%mod;
	}
	rep(i,1,y){
		b=1ll*b*i%mod;
	}
	return 1ll*a*qpow(b,mod-2)%mod;
}
void Yorushika(){
	read(n);
	int x=1;ll y=-n;
	rep(i,1,n){
		read(a[i]);
		x=1ll*x*a[i]%mod;
		y+=a[i];
	}
	int ans=1ll*x*binom(y,n-2)%mod;
	rep(i,1,n-2){
		ans=1ll*ans*i%mod;
	}
	printf("%d\n",ans);
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
  ```

---

## 作者：BreakPlus (赞：1)

+ 考虑 Prufer 序列的经典结论：假设已经钦定每个点的度数 $d_i$，如果不考虑选择孔，则方案数为 $\dfrac{(n-2)!}{\prod (d_i-1)!}$。

+ 再计算已经给出树的形态时，选择孔的方案数：

+ 每次加入一条边 $u,v$，则答案乘以 $a_u \times a_v$，并执行 $a_u-1 \to a_u$，$a_v-1 \to a_v$。

+ 盯着一个点看它的贡献，发现形式非常简单，就是 $\dfrac{a_i!}{(a_i -d_i)!}$。

+ 答案就是 $\sum \limits_{\{d\}} \frac{(n-2)!}{\prod (d_i-1)!}\prod\limits_{i}\frac{a_i!}{(a_i -d_i)!}$。

+ 化简可得 $(n-2)!\prod a_i \times \sum \limits_{\{d\}}\prod\limits_{i}\frac{(a_i-1)!}{(a_i -d_i)!(d_i-1)!}$。搞成这个形式是因为最后面是组合数，那么右边一大坨就是一个大型 Vandermonde 卷积。

+ 即为 $(n-2)!\prod a_i \dbinom{\sum (a_i-1)}{n-2}$。可以自行化简。

---

## 作者：Yansuan_HCl (赞：1)

如果知道了树的形态，可以求有多少种选择孔的方案数：

$$\prod a_i^{\underline{d_i}}$$

。枚举所有度数序列，把度数序列生成树，有

$$
\begin{aligned}
\sum_{\sum d = 2n - 2}\left( \prod a_i^{\underline{d_i}} \right) \left( \frac{(n-2)!}{\prod (d_i-1)}\right)


&= (n-2)!\sum_{\sum d = 2n -2}\prod \frac{a_i !}{(a_i-d_i)!(d_i-1)!}

\\
&=(n-2)! \sum_{\sum d = 2n -2}\prod\binom{a_i-1}{d_i-1}a_i

\\
&=(n-2)! \left( \prod a_i \right) \left( \sum_{\sum d = 2n -2}\prod\binom{a_i-1}{d_i-1} \right)

\end{aligned}
$$

，运用范德蒙德卷积有

$$
(n-2)!\left( \prod a_i \right) \binom{\sum a_i - n}{2n - 2 - n}
$$

，可以 $O(n)$ 计算。

---

## 作者：Feyn (赞：1)

写在前面的话：由于本人非常菜，本篇题解可能有疏漏甚至谬误之处，请大佬轻喷。

题意：有 $m$ 个点，每个点有 $d_i$ 个接口，每个接口两两不同，一个接口只能连一条边。求生成树的方案数。

首先根据 prufer 序列的经典结论会发现树的形态应该是 $\sum\limits_{r}\dfrac{(m-2)!}{\prod(r_i-1)!}$，其中 $r$ 是每个点在生成树上的度数。然后乘上接口的方案会得到：
$$
\begin{aligned}
&\sum\limits_{r}\dfrac{(m-2)!}{\prod(r_i-1)!}\prod\limits_{i}A_{d_i}^{r_i}\\
=&\sum\limits_{r}(m-2)!\prod\limits_{i}\frac{A_{d_i}^{r_i}}{(r_i-1)!}
\end{aligned}
$$
发现前半部分是定的，求后面那一堆的生成函数如下：
$$
\begin{aligned}
F_i(x)=&\sum\limits_{k=1}\frac{A_{d_i}^{k}}{(k-1)!}x^k\\
=&\sum\limits_{k=1}\frac{d_i!}{(d_i-k)!(k-1)!}x^k\\
=&d_i\sum\limits_{k=1}\frac{(d_i-1)!}{(d_i-k)!(k-1)!}x^k\\
=&d_i\sum\limits_{k=1}\binom{d_i-1}{k-1}x^k\\
=&d_ix\sum\limits_{k=0}\binom{d_i-1}{k}x^{k}\\
=&d_ix(1+x)^{d_i-1}
\end{aligned}
$$
然后答案就是：
$$
\begin{aligned}
&(m-2)!\prod\limits_{i=1}F_{i}(x)\\
=&(m-2)!\prod\limits_{i=1}d_ix(1+x)^{d_i-1}\\
=&((m-2)!x^{m}\prod\limits_{i}d_i)(1+x)^{\sum d_i-m}
\end{aligned}
$$
中 $2(m-1)$ 次项的系数。分析一下，前面一堆已经定下来了，而且由于有个 $x^m$，问题转化成求 $(1+x)^{\sum d_i-m}$ 的 $m-2$ 次项系数。显然答案等于 $\binom{-m+\sum d_i}{m-2}$，暴力计算即可。最后再乘上前面的 $(m-2)!\prod\limits_{i}d_i$ 即可得到答案，复杂度显然线性。

代码：

```cpp
#include<bits/stdc++.h>
//#define feyn
#define int long long
using namespace std;
const int mod=998244353;
inline void read(int &wh){
	wh=0;char w=getchar();int f=1;
	while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
	while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
	wh*=f;return;
}

int m,sum,in,ans=1;

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
	#endif
	
	read(m);
	for(int i=1;i<=m;i++)read(in),sum+=in,ans=ans*in%mod;
	if(sum<(m-1)*2)return puts("0"),0;sum%=mod;
	for(int i=0;i<=m-3;i++)ans=ans*(sum-m-i)%mod;
	printf("%lld\n",ans);
	
	return 0;
}
```

---

## 作者：Petit_Souris (赞：0)

首先观察到可以枚举度数序列并计算，答案即为：

$$\sum\limits_{\forall i,1\le d_i\le min(a_i,n-1),\sum d_i=2n-2}(\prod\limits_{i=1}^{n}\binom{a_i}{d_i}d_i!\frac{1}{(d_i-1)!})(n-2)!$$

意义：对于一个度数序列，每个点需要选出 $d_i$ 个孔并指定顺序，最后是一个 prufer 序列计数。

这样有一个简单的 $\mathcal O(n^3)$ dp 做法。我们尝试用生成函数优化这个计算过程：设 $F_i(x)=\sum\limits_{k=1}^{a_i}\binom{a_i}{k}kx^k$，那么答案即为 $(n-2)![x^{2n-2}]\prod F_i(x)$。

化简一下 $F$：使用吸收恒等式得到 $F_i(x)=a_i\sum\limits_{k=1}^{a_i-1}\binom{a_i-1}{k-1}x^k=xa_i(1+x)^{a_i-1}$，这些东西乘起来之后形如 $x^{n}C(1+x)^m$，其中 $C,m$ 容易计算得到。最后的系数只需要用二项式定理展开即可。时间复杂度 $\mathcal O(n)$。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll N=4e5+9,Mod=998244353,V=4e5;
ll n,a[N],cur,fac[N],ifac[N],res=1;
ll pw(ll x,ll p){
	ll res=1;
	while(p){
		if(p&1)res=res*x%Mod;
		x=x*x%Mod,p>>=1;
	}
	return res;
}
ll C(ll x,ll y){
	if(x<y||y<0)return 0;
	return fac[x]*ifac[y]%Mod*ifac[x-y]%Mod;
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
	n=read();
	rep(i,1,n)a[i]=read();
	ll mxd=0;
	rep(i,1,n)mxd+=min(n-1,a[i]);
	if(mxd<2*n-2)return puts("0"),0;
	fac[0]=1;
	rep(i,1,V)fac[i]=fac[i-1]*i%Mod;
	ifac[V]=pw(fac[V],Mod-2);
	per(i,V-1,0)ifac[i]=ifac[i+1]*(i+1)%Mod;
	ll s=0;
	rep(i,1,n)s+=a[i]-1,res=res*a[i]%Mod;
	//(1+x)^s [x^(n-2)]
	per(i,s,s-(n-2)+1)res=res*(i%Mod)%Mod;
	write(res);
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

## 作者：User_Unauthorized (赞：0)

## 题意

给定 $N$ 个带有若干洞的节点，其中第 $i$ 个点上有 $d_i$ 个洞。

先可以在两个不同的节点的洞之间连边，一个洞最多连一条边，求使得最终形成的图是一棵树的方案数，对 $998244353$ 取模。

洞之间相互区分，两个方案不同当且仅当存在一条边在两个方案中的连的洞不同。

- $2 \le N \le 2 \times 10^5$
- $1 \le d_i < 998244353$

## 题解

首先设 $S = \sum d_i$，那么首先考虑 $S \ge 2 \left(N - 1\right)$ 的情况，即一定有解的情况。

考虑组成一棵树的过程，可以从每个节点的父边入手，考虑对于每个节点，钦定一个特殊洞，使得其连向父亲节点。

那么我们每次操作可以转化为选择一个特殊洞，再选择一个非特殊洞，使得其相连。

可以发现每次操作后联通块数量一定会减少，在仅剩 $2$ 个联通块时我们可以使其两个特殊洞相连，进而确定方案。因此我们只需要操作 $N - 2$ 次。

考虑如何计算方案数。首先钦定特殊洞的方案数显然为 $\prod d_i$。对于第 $i$ 次选择，我们可以从 $N - i + 1$ 个特殊洞中选择一个，从 $S - N - i + 1$ 个非特殊洞中选择一个，因此方案数为 $\left(N - i + 1\right) \times \left(S - N - i + 1\right)$。

因此可以得出总方案数：

$$\prod d_i \times \prod\limits_{i = 1}^{N - 2} \left(N - i + 1\right) \times \left(S - N - i + 1\right)$$

即

$$\prod d_i \times \prod\limits_{i = 0}^{N - 3} \left(S - N - i\right) \times N^{\underline{N - 2}}$$

发现每个节点被选择的顺序是不影响最终的方案的，但是被计算了多次，考虑除去这个影响。

因此最终答案为：

$$\prod d_i \times \prod\limits_{i = 0}^{N - 3} \left(S - N - i\right)$$

可以发现，若 $S < 2 \left(N - 1\right)$，那么上式的值一定为 $0$，于实际相符，因此直接计算上式的值即可。

## Code

```cpp
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

namespace MODINT {
    constexpr valueType MOD = 998244353;

    template<typename T1, typename T2, typename T3 = valueType>
    void Inc(T1 &a, T2 b, const T3 &mod = MOD) {
        a = a + b;

        if (a >= mod)
            a -= mod;
    }

    template<typename T1, typename T2, typename T3 = valueType>
    void Dec(T1 &a, T2 b, const T3 &mod = MOD) {
        a = a - b;

        if (a < 0)
            a += mod;
    }

    template<typename T1, typename T2, typename T3 = valueType>
    T1 sum(T1 a, T2 b, const T3 &mod = MOD) {
        return a + b >= mod ? a + b - mod : a + b;
    }

    template<typename T1, typename T2, typename T3 = valueType>
    T1 sub(T1 a, T2 b, const T3 &mod = MOD) {
        return a - b < 0 ? a - b + mod : a - b;
    }

    template<typename T1, typename T2, typename T3 = valueType>
    T1 mul(T1 a, T2 b, const T3 &mod = MOD) {
        return (long long) a * b % mod;
    }

    template<typename T1, typename T2, typename T3 = valueType>
    void Mul(T1 &a, T2 b, const T3 &mod = MOD) {
        a = (long long) a * b % mod;
    }

    template<typename T1, typename T2, typename T3 = valueType>
    T1 pow(T1 a, T2 b, const T3 &mod = MOD) {
        T1 result = 1;

        while (b > 0) {
            if (b & 1)
                Mul(result, a, mod);

            Mul(a, a, mod);
            b = b >> 1;
        }

        return result;
    }

    constexpr valueType Inv2 = (MOD + 1) / 2;
}// namespace MODINT

using namespace MODINT;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType N;

    std::cin >> N;

    valueType ans = 1, S = 0;

    ValueVector D(N);

    for (auto &iter : D) {
        std::cin >> iter;

        Mul(ans, iter);

        Inc(S, iter);
    }

    for (valueType i = 0; i <= N - 3; ++i)
        Mul(ans, sub(S, N + i));

    std::cout << ans << std::endl;

    return 0;
}
```

---

