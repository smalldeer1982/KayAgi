# Matrix Rank (Easy Version)

## 题目描述

这是该问题的简单版本。该问题的两个版本之间唯一的区别是 $k$ 的约束条件。只有在所有版本的问题都被解决后，你才能进行 hack。

给定整数 $n$、$p$ 和 $k$。保证 $p$ 是一个质数。

对于每个 $r$ 从 $0$ 到 $k$，求在模 $p$ 的整数域 $^\dagger$ 上，秩 $^\ddagger$ 恰好为 $r$ 的 $n \times n$ 矩阵 $A$ 的个数。由于答案很大，你只需要输出对 $998\,244\,353$ 取模后的结果。

$^\dagger$ [https://en.wikipedia.org/wiki/Field\_(mathematics)](https://en.wikipedia.org/wiki/Field_(mathematics))

$^\ddagger$ [https://en.wikipedia.org/wiki/Rank\_(linear\_algebra)](https://en.wikipedia.org/wiki/Rank_(linear_algebra))

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 2 3```

### 输出

```
1 49 294 168```

## 样例 #2

### 输入

```
1 51549919 2```

### 输出

```
1 51549918 0```

# 题解

## 作者：xuanxuan001 (赞：4)

~~掉出 IGM 祭！~~ 

真是个阴间场，~~但用来告别我的 2023 感觉倒还比较合适~~，希望 Hello 2024 不要也这样阴间了。

写一下赛时想到但没完全想到的做法，感觉不像 H2 做法那么 Ad-hoc，也不用 OEIS，~~也纪念一下双 log n=5000 没跑进跑 1s~~。

正文
-

前面还是一样，记 $F_{i,j}$ 表示一个 $i \times n$ 的矩阵的秩为 $j$ 的方案数（我不知道直接说 $i \times n$ 的秩是否严谨，~~但反正是那意思，后面可能也有很多类似的表述，意会一下就行了~~）。

那么考虑下一行，它有 $p^n$ 种选择方案，其中有 $p^j$ 种是不产生新的秩的，其他的会产生，于是有转移方程

$$
F_{i,j}=F_{i-1,j} \times p^j + F_{i-1,j-1} \times (p^n - p^{j-1})
$$

这时第二维只需要到 $k$，可以接受，但第一维到 $n$，显然是需要优化的。

一开始也想过正解的生成函数思路并推出了那个乘积形式的式子，但并没有想到该怎么优化，于是开始考虑其他思路。

这类 dp 当然是考虑转换成路径，那么两种转移就是横着向右走和向右上走，发现第二个转移的贡献是确定的 $\prod\limits_{i=0}^{r-1}(p^n - p^i)$，可以不考虑，主要难点在于第一个转移。

一些鲜花，其实之前我也是遇到过类似的问题的，但那时我觉得应该不可优化，没想到竟然还能在赛场上遇到并想出来，~~而且那时的我自己推出了这个转移式，感觉当时还是很牛的~~。

发现第一个转移的主要难点在于它的系数与它的“行数”（即前面进行第二个转移的次数）有关。

但是这个系数是 $p$ 的幂次，所以还是有转换的可能，既然是行数，那么可以考虑给这个横着的转移下面的每一行都放上一个 $p$。然后就可以考虑拆贡献，将“摆放”的 $p$ 按行考虑而不是列，也就是在每个第二类转移上计算贡献。

上面那段话可能有些抽象，其实如果说的简单一些就是将每个第一类转移 $p^j$ 的系数换到前面 $j$ 个第二类转移的系数上。这时一次第二类转移（即向右上走）的系数会乘上一个 $p^{(n-i)-(r-j)}$，后面的 $p^{-(r-j)}$，可以在最终的答案中直接乘上 $\dfrac 1{p^{{r(r-1)} \over 2}}$，将直接计算的第二类转移系数也提到最后计算，那么转移式就变成了

$$
F_{i,j} = F_{i-1,j} + p^{n-i} F_{i-1,j-1}
$$

那么这个式子就等价于在 $1,p,p^2,\cdots,p^{n-1}$ 中选择 $r$ 个的乘积和，不难发现这就是一个生成函数，它是

$$
[x^r]\prod\limits_{i=0}^{n-1}(p^ix + 1)
$$

然后我赛时推组合数求了个选 $r$ 个数的和的和，调出来后发现求错了，然后只剩十分钟直接摆了。。。

第二天早上吃早饭的时候又想了想那个式子，发现是个之前见过的套路。

设 $F(n) = \prod\limits_{i=0}^{n-1}(p^ix + 1)$，那么如果知道了 $F(a)$ 和 $F(b)$ 就可以直接得到 $F(a+b)$。

具体的，可以由 $F(B)$ 直接得到 $\dfrac{F(A+B)}{F(A)} = \prod\limits_{i=0}^{B-1}(p^{i+A}x + 1)$，方法就是将它的 $i$ 次项系数乘上 $p^{iA}$。

然后将这个东西与 $F(A)$ 相乘就能得到 $F(A+B)$ 了。

然后类似快速幂/龟速乘的做一下就行了。

得到这个系数后乘上一个可以直接递推得到的系数即可，这里再整理一下答案是：

$$
[x^r]F(n) \dfrac 1{p^{{r(r-1)} \over 2}} \prod\limits_{i=0}^{r-1}(p^n - p^i)
$$

求的时候只需要记录 $F(n) \bmod x^{k+1}$ 即可。

复杂度 $O(k^2\log n)$，不知道能不能过，但反正我每次快速幂求系数多个极小的 $\log$ 没跑过 test 3，感觉改了应该还是过不了。

发现模数是 $998244353$，所以可以用 NTT 优化卷积，最终复杂度 $O(k \log k \log n)$，实测 H1 最慢点跑 1170ms(C++14)。

感觉代码没(懒)啥(得)好(写)注释的，主要是看文字题解的推导，[所以就贴个记录得了](https://codeforces.com/contest/1916/submission/239762899)，不占地方了。

---

## 作者：wzy2021 (赞：4)

### 前言

这场比赛打得异常痛苦。
虽然场上 H1H2 会做，但是考场上太急了导致脑抽，然后就爆掉了。。。

### 题意

给定 $n$，$p$，$k$。要求：
求有多少个 $n\times n$ 的在 $\bmod p$ 意义下定义的矩阵，使得其秩为 $r$。
将 $r$ 从 $0$ 到 $k$ 分别输出答案，对 998244353 取模。

数据范围：$n \le 5\times10^{18}$，$k \le 5\times 10^5$，$0 \le p < 998244353$。

### 题解

容易想到 dp：$f_{i,r}$ 表示考虑前 $i$ 行的矩阵，秩为 $r$ 的数量。
显然有
$$
f_{i,r} = f_{i - 1,r} \times p^r + f_{i - 1, r - 1} \times (p^n - p^{r - 1})
$$
具体而言，分两种情况：

1. 当前秩不增加，那么这行一定是前面的行向量的组合，因为前面的秩 $r$，所以有 $2^r$ 种方法。
2. 当前秩增加，那么这行一定不是前面的行向量的组合，因为前面的秩为 $r - 1$，所以有 $p^n - p^{r - 1}$ 中选择方法。

那么这样就得到如上转移，最终答案是 $f_{n,0},\cdots,f_{n,k}$。

考虑如何快速求解 $f$ 数组。考虑将 $f$ 数组画在一个二维平面上，等价于：

每次可以从 $(i,r)$ 走到 $(i+1,r)$（称为平走），或者从 $(i,r)$ 走到 $(i + 1, r + 1)$，每次行走带着一定的贡献。

可以发现第 2 种转移一定只有 $r$ 个，且对答案的贡献是确定的，即：

$$
f_{i,r} = g_{r,i-r} \times \Pi_{j=1}^r (p^n - p^{j - 1})
$$

其中，走到 $f_{i,r}$ 需要进行 $i - r$ 次第 1 种转移，那么 $g_{i,r}$ 的意义就明确了。

所以 $g_{i,r}$ 就是在 $1$ 到 $i$ 层种进行若干次（可以为 0）平走，使得总平走的次数恰好为 $r$ 的总贡献，在第 $j$ 层平走的贡献是 $p^j$。
由于有恰好走 $r$ 步，所以考虑生成函数：$G_i(x) = \sum_{r\ge0} f_{i,r}x^r$，

从而可以写出 $G_i(x) = \sum_{j=0}^i \sum_{l\geq0}(p^jx)^l=\sum_{j=0}^i\tfrac{1}{1-p^jx}$，考虑：

$$
G_i(x) = \sum_{j=0}^i\dfrac{1}{1-p^jx}
$$

$$
G_i(px) = \sum_{j=0}^i\dfrac{1}{1-p^j(px)}=\sum_{j=0}^i\dfrac{1}{1-p^{j+1}x}
$$

所以有

$$
(1 - x)G_i(x) = (1 - p^{i+1}x)G_i(px)
$$

对比两边 $r$ 次方系数的：

$$
g_{i,r}- g_{i,r-1}=p^r\times g_{i,r}-p^{i+1}\times p^{r-1} \times g_{i,r-1}
$$

所以就可以得到递推公式：

$$
g_{i,r}=\dfrac{p^{i+r}-1}{p^r-1}\times g_{i,r-1}
$$

所以就得到了通项公式：

$$
g_{i,0}=1,g_{i,r}=\Pi_{j=1}^r\dfrac{p^{i+j}-1}{p^j-1}
$$

从而得到了快速求解 $f$ 的方法：

$$
f_{n,r} = \Pi_{j=1}^{n-r}\dfrac{p^{r+j}-1}{p^j-1} \times \Pi_{j=1}^r (p^n - p^{j - 1})
$$
考虑将 $r$ 从小到大计算，则后者可以直接算，前者考虑分子分母互相抵消后再计算。

然后这样就可以直接过 H1H2 了。

~~~cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

int rd() {
	int x = 0, f = 1;
	char ch = getchar();
	while (!('0' <= ch && ch <= '9')) {
		if (ch == '-') f = -1; ch = getchar();
	}
	while ('0' <= ch && ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar();
	}
	return x * f;
}

void wr(int x) {
	if (x < 0) putchar('-'), x = -x;
	if (x >= 10) wr(x / 10); putchar(x % 10 + '0');
}

const int N = 5e5 + 10;
const int mod = 998244353;

int ans[N];

int add (int x) {
	if (x >= mod) x -= mod; else if (x < 0) x += mod;
	return x;
}

int ksm (int x, int y = mod - 2) {
	int res = 1; x = add(x);
	while (y) {
//		cout << y << " " << res << endl;
		if (y & 1) res = 1ll * res * x % mod;
		x = 1ll * x * x % mod; y >>= 1;
	} return res;
}

signed main() {
	int n, p, k; n = rd(); p = rd(); k = rd();
	int res1 = 1, res2 = 1;
	for (int r = 0; r <= min(n,k); ++r) {
		ans[r] = 1ll * res1 * res2 % mod;
		res1 = 1ll * res1 * add(ksm(p, n) - ksm(p, r)) % mod;
		res2 = 1ll * res2 * ksm(ksm(p, r + 1) - 1) % mod * add(ksm(p, n - r) - 1) % mod;
	}
	for (int r = 0; r <= k; ++r) printf ("%d ", ans[r]);
	return 0;
}
~~~

话说，上面最后的式子是可以用找规律的？不清楚了。

---

## 作者：蒟蒻君HJT (赞：3)

整理一下比赛时的思路。No OEIS or google plz.

根据线性代数的知识我们知道一个矩阵的秩（rank）等于它的行空间的维数。接下来我们将从 $\bmod \ p$ 意义下的长为 $n$ 的行向量（下文简称向量）入手。

$\text{Lemma 1:}$ 所有不同的向量总共有 $p^n$ 种。

$\text{Lemma 2:}$ $d$ 维空间中的向量有 $p^d$ 种。


$\text{Lemma 3:}$ $d$ 维空间中选取一组基的方案数（考虑相对顺序）为 $\displaystyle \prod_{i=0}^{d-1}(p^d-p^i)$。

$\text{Lemma 4:}$ 所有向量中选取互相独立的 $d$ 个向量的方案数（考虑相对顺序）为 $\displaystyle \prod_{i=0}^{d-1}(p^n-p^i)$。

我们知道所有向量中选取互相独立的 $d$ 个向量会张出一个 $d$ 维的子空间。因此 $d$ 维的本质不同的子空间的数量为 $\displaystyle\frac{\displaystyle\prod_{i=0}^{d-1}(p^n-p^i)}{\displaystyle\prod_{i=0}^{d-1}(p^d-p^i)}$。

记 $\text{rank}(A)=i$ 的不同矩阵 $A$ 的数量为 $f_i$。

$\text{Lemma 5:}$ 假定已经强制所有行向量都在某个 $d$ 维的子空间中，则这样的矩阵共有 $p^{nd}$ 种。

考虑先令 $f_i\gets p^{ni}$，再容斥掉实际上 $\text{rank}(A)=0,1,\cdots i-1$ 的情况数量。

对于 $f_j(j<i)$ 中的每个矩阵，它被错误地计入到 $f_i$ 中的次数实际上就是固定一个 $j$ 维的子空间，选取一些额外的基向量后，能扩展到的本质不同的 $i$ 维的子空间的数量。这等价于在 $n-j$ 维的空间中能选出的 $i-j$ 维的子空间的数量，根据前文论述，应该是 $\displaystyle\frac{\displaystyle\prod_{k=0}^{i-j-1}(p^{n-j}-p^k)}{\displaystyle\prod_{k=0}^{i-j-1}(p^{i-j}-p^k)}$。

因此，得到 $f_i$ 的计算式：

$$f_i=p^{ni}-\sum_{j=0}^{i-1}f_j\times \displaystyle\frac{\displaystyle\prod_{k=0}^{i-j-1}(p^{n-j}-p^k)}{\displaystyle\prod_{k=0}^{i-j-1}(p^{i-j}-p^k)}$$

按照 $i$ 从小到大计算即可。需要预先递推处理 $g_{i,j}=\displaystyle\prod_{k=0}^{j}(p^i-p^k)$，其中 $i\in[0,k]\bigcup \ [n-k,n],j\in[0,k]$。精细实现的复杂度是 $\Theta(k^2)$ 的。

有没有数学哥能浇浇我怎么从这个递推式推出 $f_i$ 的通项阿？？？

---

## 作者：Acoipp (赞：3)

这是一篇不太正经的题解，用于纪念比赛最后一分钟被卡常的经历。

首先我们看到第一组样例输入 `3 2 3`，输出 `1 49 294 168`，于是我们把输出放到了 [OEIS](https://oeis.org/) 这个网站搜了一下，于是得出下面的结果：

> 在模 $2$ 的剩余系下的矩阵规格为 $n \times n$，并且矩阵的秩为 $k$ 的方案数。

其中 $f_{3,0}=1,f_{3,1}=49,f_{3,2}=294,f_{3,3}=168$，于是我们就可以用他给的公式：

$$
f_{n,k} = \prod_{j=0}^{k-1} \dfrac{(2^n-2^j)^2}{2^k-2^j}
$$

但是这只是 $p=2$ 时的情况，我们可以考虑 $p$ 大于 $2$ 的情况，根据第二组样例，合理猜测底数就是 $p$，于是公式变成了：

$$
f_{n,k} = \prod_{j=0}^{k-1} \dfrac{(p^n-p^j)^2}{p^k-p^j}
$$

我们就可以用这个公式在 $O(k^2 \log p)$ 时间内求解，至于具体的证明可以参考 CF 官方题解或者洛谷第一篇题解，写得都很好。

但是需要优化时间复杂度，首先，逆元必须直接算（我不会更优美的算法），然后 $p^i(0 \le i \le k)$ 以及 $p^n$ 都可以提前存下来。

这样的话这道题就做完了，代码如下，时间复杂度是小常的 $O(k^2 \log p)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mod 998244353
using namespace std;
ll n,p,k,i,j,ans,qmm[5005],qmmm;
inline ll qmi(ll a,ll b,ll p){
	ll res = 1%p,t=a;
	while(b){
		if(b&1) res=res*t%p;
		t=t*t%p;
		b>>=1;
	}
	return res;
}
int main(){
	cin>>n>>p>>k;
	qmm[0] = 1,qmmm = qmi(p,n,mod);
	for(i=1;i<=k;i++) qmm[i]=qmm[i-1]*p%mod;
	for(i=0;i<=k;i++){
		ans=1;
		for(j=0;j<i;j++){
			ans=ans*((qmmm-qmm[j]+mod)%mod*(qmmm-qmm[j]+mod)%mod*qmi((qmm[i]-qmm[j]+mod)%mod,mod-2,mod)%mod)%mod;
		}
		cout<<ans<<" ";
	}
	cout<<endl;
}
```

---

