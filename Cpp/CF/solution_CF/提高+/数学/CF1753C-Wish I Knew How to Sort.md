# Wish I Knew How to Sort

## 题目描述

You are given a binary array $ a $ (all elements of the array are $ 0 $ or $ 1 $ ) of length $ n $ . You wish to sort this array, but unfortunately, your algorithms teacher forgot to teach you sorting algorithms. You perform the following operations until $ a $ is sorted:

1. Choose two random indices $ i $ and $ j $ such that $ i < j $ . Indices are chosen equally probable among all pairs of indices $ (i, j) $ such that $ 1 \le i < j \le n $ .
2. If $ a_i > a_j $ , then swap elements $ a_i $ and $ a_j $ .

What is the [expected number](https://en.wikipedia.org/wiki/Expected_value) of such operations you will perform before the array becomes sorted?

It can be shown that the answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 \pmod{998\,244\,353} $ . Output the integer equal to $ p \cdot q^{-1} \bmod 998\,244\,353 $ . In other words, output such an integer $ x $ that $ 0 \le x < 998\,244\,353 $ and $ x \cdot q \equiv p \pmod{998\,244\,353} $ .

## 说明/提示

Consider the first test case. If the pair of indices $ (2, 3) $ will be chosen, these elements will be swapped and array will become sorted. Otherwise, if one of pairs $ (1, 2) $ or $ (1, 3) $ will be selected, nothing will happen. So, the probability that the array will become sorted after one operation is $ \frac{1}{3} $ , the probability that the array will become sorted after two operations is $ \frac{2}{3} \cdot \frac{1}{3} $ , the probability that the array will become sorted after three operations is $ \frac{2}{3} \cdot \frac{2}{3} \cdot \frac{1}{3} $ and so on. The expected number of operations is $ \sum \limits_{i=1}^{\infty} \left(\frac{2}{3} \right)^{i - 1} \cdot \frac{1}{3} \cdot i = 3 $ .

In the second test case the array is already sorted so the expected number of operations is zero.

In the third test case the expected number of operations equals to $ \frac{75}{4} $ so the answer is $ 75 \cdot 4^{-1} \equiv 249\,561\,107 \pmod {998\,244\,353} $ .

## 样例 #1

### 输入

```
3
3
0 1 0
5
0 0 1 1 1
6
1 1 1 0 0 1```

### 输出

```
3
0
249561107```

# 题解

## 作者：Alex_Wei (赞：11)

Wish I knew how I can come up with the solution.

这题把我送走了。

注意到最终态形如前面 $cnt_0$ 个位置（称为前缀）上是 $0$，后面 $cnt_1$ 个位置（称为后缀）上是 $1$。

改变前缀上 $0$ 的个数的交换，必然形如选择前缀上的 $1$ 和后缀上的 $0$ 交换。设当前前缀上 $1$ 的个数为 $x$，则后缀上 $0$ 的个数必然为 $x$，共有 $x ^ 2$ 对选择后可以将 $x$ 减去 $1$ 的 $(i, j)$。因此，每步操作令 $x$ 减 $1$ 的概率为 $\dfrac {x ^ 2} {\binom n 2}$。

综上，设初始前缀上 $1$ 的个数为 $x$，则答案为 $\dbinom n 2 \sum\limits_{i = 1} ^ x \dfrac 1 {x ^ 2}$。时间复杂度 $\mathcal{O}(n\log n)$ 或 $\mathcal{O}(n)$。[代码](https://codeforces.com/contest/1753/submission/177648937)。

---

## 作者：MusicBox (赞：10)

### 题意描述

给你一个 $01$ 串，每次可以选择两个数字，当 $a_i > a_j$ 时进行交换，**反之不交换**，无论交不交换都计入次数，让你求使得该串有序（从小到大）的期望次数。

### 思路

我们将串中数字 $0$ 个数记为 $\operatorname{cnt}$ 。

观察题意发现，我们只需要将前 $\operatorname{cnt}$ 个数字全部交换成 $0$ 即可，且前 $\operatorname{cnt}$ 个数字已经出现了 $\operatorname{w}$ 个 $0$ 时，无论如何交换，都不会使得情况更劣（即不会出现 $0$ 的个数变少的情况，原因见题意加粗部分）。

我们用 $f_i$ 表示前 $\operatorname{cnt}$ 个数字中有 $i$ 个数字为 $0$ 的期望。

那么，问题就转化成了使得前 $\operatorname{cnt}$ 个数字中多一个 $0$ (当前已有 $i-1$ 个 $0$ )，期望的选择次数是多少？

我们知道，所有可能的交换方案数为：$C_n^2$ ，而只有前 $\operatorname{cnt}$ 个数中的 $1$ 和后 $n-\operatorname{cnt}+1$ 个数中的 $0$ 交换有意义。所以答案是 $\frac{C_n^2}{(\operatorname{cnt}-i+1)^2}$。

那么 $f$ 数组的转移方程就是：

$$
f_i=f_{i-1}+\frac{C_n^2}{(\operatorname{cnt}-i+1)^2}
$$

### code:
```cpp
/*
    Author : TLE_Automaton && hhdxgd && JRXGD && hwd-gd
    Right Output ! & Accepted !
*/

#include <bits/stdc++.h>
#define int long long
#define modn 998244353
using namespace std;

int T;
const int L = 2e5 + 5;
int t, n, k, x, y, z, ans, cnt, fr, a[L];

int f[L];

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch))
		f = (ch == '-' ? -1 : f), ch = getchar();
	while (isdigit(ch))
		x = (x << 3) + (x << 1) + (ch - '0'), ch = getchar();
	return x * f;
}

int qpow(int n, int m) {
	int ans = 1;
	while (m) {
		if (m & 1) {
			ans *= n;
			ans %= modn;
		}
		n *= n;
		n %= modn;
		m >>= 1;
	}
	return ans;
}

signed main() {
	T = read();
	while (T--) {
		cnt = 0, fr = 0;
		n = read();
		for (int i = 1; i <= n; i++) {
			a[i] = read();
			if (!a[i])
				cnt++;
		}
		for (int i = 1; i <= cnt; i++) {
			if (!a[i])
				fr++;
		}
		f[fr] = 0;
		for (int i = fr + 1; i <= cnt; i++) {
			f[i] = f[i - 1] + ((n * (n - 1) / 2) % modn) * qpow((cnt - i + 1) * (cnt - i + 1), modn - 2) % modn;
			f[i] %= modn;
		}
		cout << f[cnt] << endl;
	}
	return 0;
}

```

---

## 作者：lxzy_ (赞：10)

~~写篇题解纪念一下这道因为赛时打 mc 而不够时间写的题~~

最终单调不降的目标序列肯定是 ```00...00111...111```，交换过程就是以中间的 $0$ 和 $1$ 为分界线，左边的 $1$ 全部移动到右边，右边的 $0$ 全部移动到左边，根据期望线性性质，我们可以单独考虑每一次操作，最后将每次操作的期望值加起来即可。

设当前分界线左边有 $i$ 个 $1$，则分界线右边会有 $i$ 个 $0$，交换一次左边的 $1$ 和右边的 $0$ 的概率为：

$$\frac{i^2}{\binom{n}{2}}$$

而期望是概率的倒数，因此最终我们要求的便是：

$$\sum\limits_{i=1}^k \frac{\binom{n}{2}}{i^2}$$

其中 $k$ 是一开始分界线左边的 $1$ 数量（右边的 $0$ 数量）

然后就完力（喜）

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+50;
const ll mod=998244353;
int n,a[N],cnt,k,t;
ll Pow(ll a,ll b)
{
	ll ans=1ll,base=a%mod;
	while(b){
		if(b&1) ans*=base,ans%=mod;
		base*=base,base%=mod;
		b>>=1;
	}
	return ans;
}
void Wish()
{
	cnt=0,k=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]),cnt+=(a[i]==0);//计算分界线
	for(int i=1;i<=cnt;i++){
		if(a[i]) k++;
	}
	ll ans=0;
	for(int i=1;i<=k;i++){//计算答案
		ans+=1ll*n*(n-1)%mod*Pow(2ll*i*i,mod-2)%mod;
		ans%=mod;
	}
	printf("%lld\n",ans);
}
int main()
{
	scanf("%d",&t);
	while(t--) Wish();
	return 0;
}
```

---

## 作者：wyr_ (赞：8)

首先，因为这个数组只包含 $0$ 和 $1$，所以它排序后一定是一段连续的 $0$ 和一段连续的 $1$。

具体地，设给定数组有 $p$ 个 $0$ 和 $(n-p)$ 个 $1$，那么排序后数组下标区间 $[1,p]$ 的值是 $0$，$[p+1,n]$ 的值是 $1$。

那么，数组没排好序当且仅当 $\exists i \in [1,p], a_i=1$。形象地说，就是存在一个 $1$ 越过下标 $p$ 和 $p+1$ 之间的分界线，出现在分界线左边。

由此想到，可以把当前下标区间 $[1,p]$ 中 $1$ 的个数记作状态。可以发现，如果现在的状态为 $k$，那么经过一步操作之后的状态是 $k$ 或 $k-1$。可以发现，从状态 $k$ 转移到状态 $k-1$ 的概率**与当前数组中数字的具体排列无关**。所以，**排序的期望操作次数也和数组中数字的具体排列无关**，只与下标区间 $[1,p]$ 中 $1$ 的个数有关。

具体地，若当前状态为 $k$，转移到状态 $k-1$ 当且仅当选中的下标 $(i,j)$ 满足 $i\in [1,p],j\in [p+1,n],a_i=1,a_j=0$。此时下标 $[p+1,n]$ 中有 $k$ 个 $0$，那么这样选择的方案数是 $k^2$。所以，从状态 $k$ 转移到状态 $k-1$ 的概率为 $\frac{k^2}{\frac{n(n-1)}{2}}$。

设 $f_k$ 表示状态 $k$ 到达状态 $0$ 的期望操作次数。根据上面计算的概率，可以得到

$$ f_k=\frac{2k^2}{n(n-1)}f_{k-1}+(1-\frac{2k^2}{n(n-1)})f_k+1 $$

该式等价于

$$ f_k=f_{k-1}+\frac{n(n-1)}{2k^2} $$

显然 $f_0=0$。设给定初始数组中下标 $[1,p]$ 中 $1$ 的个数为 $m$，那么答案就是 $f_m$。展开递推式，答案为
$$ \sum_{i=1}^{m}{\frac{n(n-1)}{2i^2}} $$

这个式子可以直接计算。

---

## 作者：william555 (赞：4)

看到每次如果 $(a_i,a_j)$ 是逆序对就交换，然后往逆序对方向想，那么你就错了！

要设出好的 dp 状态，要满足一下条件：

1. 可以轻易地反应起始和目标状态。
2. 可以轻易转移。

于是想要设出优秀的状态，先从分析目标的性质开始：

它有序，首先可以想到其逆序对数量为 $0$，结果发现从逆序对角度思考无法轻易转移：每次减少的逆序对个数与 $(i,j)$ 的取值有关。

就只能从其他方向思考：假设一共有 $m$ 个 0，那么最后就要前 $m$ 个全是 $0$，后 $n-m$ 个全是 $1$。然后操作的过程就是前 $m$ 个中的 $1$ 逐渐减少到 $0$。

令 $f_i$ 为前 $m$ 个中还有 $i$ 个 $1$ 的期望步数，只有每次操作当选出前面的一个 $1$ 和后面的一个 $0$，才会使前面的 $1$ 的个数减少，这样进行一次有效的操作的期望步数为 $ \frac {C_n^2} {i^2} $ ，所以   
$$f_i =f_{i+1}+\frac {C_n^2} {i^2}$$
设起始时前 $m$ 个中有 $k$ 个 $1$，dp 赋初值就为：$f_k=0$，然后从后往前递推。

整理一下，最后的答案就为：
$$ \sum _{i=1}^k \frac {C_n^2} {i^2}$$

```c++
#include<bits/stdc++.h>
using namespace std;
inline int in(){
	int x;
	scanf("%d",&x);
	return x;
}
const int N=2e5+5,mod=998244353;
inline int add(int a,int b){return a+b>=mod?a+b-mod:a+b;}
inline int mul(int a,int b){return (long long)a*b%mod;}
inline int qpow(int a,int b){
	int c=1;
	for(;b;b>>=1,a=mul(a,a))if(b&1)c=mul(c,a);
	return c;
}
int n,m,k,a[N];
void solve(){
	n=in(),m=k=0;
	int all=1ll*n*(n-1)/2%mod;
	for(int i=1;i<=n;i++)a[i]=in(),m+=a[i]==0;
	for(int i=1;i<=m;i++)k+=a[i];
	int ans=0;
	for(int i=1;i<=k;i++)ans=add(ans,qpow(mul(i,i),mod-2));
	ans=mul(ans,all);
	printf("%d\n",ans);
}
int main(){
	int t=in();
	while(t--)solve();
	return 0;
}
```

---

## 作者：demonlover923 (赞：3)

没有什么想法，先考虑想最优化问题来观察性质，最优的会是最左边的 $1$ 去换最右边的 $0$，虽然这并没有什么鬼用，但是我们发现，有一些 $1$ 和 $0$ 是交换是对最优方案做负贡献的，进一步的，我们发现，令全局有 $a$ 个 $0$，那么，只有移动前 $a$ 个里面的 $1$ 和后面 $n-a$ 个 $1$ 里面的 $0$，才有用，而移动这两边内部的 $1$ 和 $0$ 改变前 $a$ 个里面 $1$ 的个数，换句话说即使交换了内部的 $1$ 和 $0$ 之后，对最优策略的交换次数没用作用。

这启发我们只关注前面 $a$ 个中 $1$ 的个数，进一步的，容易发现前 $a$ 个中的 $1$ 是独立的，所以我们可以由此来得到答案的式子，前面还有 $i$ 个 $1$ 时，取有效操作的概率为 $\dfrac{i^2}{\binom{n}{2}}$，期望即为 $\dfrac{\binom{n}{2}}{i^2}$，故答案即为 $\sum\limits_{i=1}^{a}{\dfrac{\binom{n}{2}}{i^2}}$，不计求逆元时间复杂度为 $\mathcal{O}(n)$。

```cpp
int main() {
	read(n);
	int cnt = 0;ans = 0;
	for (int i = 1;i <= n;++i)read(a[i]),cnt += (a[i] == 0);
	int c = 0;
	for (int i = 1;i <= cnt;++i)if (a[i] == 1)++c;
	for (int i = 1;i <= c;++i)ans = (ans+1ll*n*(n-1)/2%mod*power(1ll*i*i%mod,mod-2)%mod)%mod;
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Polaris_Australis_ (赞：2)

[题目传送门（洛谷）](https://www.luogu.com.cn/problem/CF1753C)

[题目传送门（codeforces）](https://codeforces.com/problemset/problem/1753/C)

设 $cnt1$ 表示序列中 $1$ 的个数，$cnt2$ 表示不在数列的后 $cnt1$ 个元素中的 $1$ 的个数（也就是不在正确位置的 $1$ 的个数）。容易发现，交换操作只有对于不在正确位置的 $1$ 和不在正确位置的 $0$ 交换才会对答案有贡献，并且不在正确的位置的 $1$ 的个数就会减少 $1$。于是设 $dp_{i,j}$ 表示长度为 $i$ 的序列有 $j$ 个不合法 $1$ 的期望步数，转移显然：

$$
\begin{aligned}
dp_{i,j}
&=\sum\limits_{i=1}^{+\infty}(1-\frac{i^2}{\frac{(n-1)\times n}{2}})^{i-1}\times\frac{i^2}{\frac{(n-1)\times n}{2}}\times(i+dp_{i,j-1})
\end{aligned}
$$

设 $x=\frac{i^2}{\frac{(n-1)\times n}{2}}$，继续推导：

$$
\begin{aligned}
dp_{i,j}
&=\sum\limits_{k=1}^{+\infty}(1-x)^{k-1}\times x\times(k+dp_{i,j-1})\\
&=x\times\sum\limits_{k=1}^{+\infty}(1-x)^{k-1}\times k + x\times dp_{i,j-1}\times\sum\limits_{k=1}^{+\infty}(1-x)^{k-1}
\end{aligned}
$$

$$
S=x\times\sum\limits_{k=1}^{+\infty}(1-x)^{k-1}\times k
$$

$$
(1-x)\times S=x\times\sum\limits_{k=1}^{+\infty}(1-x)^{k-1}\times (k-1)
$$

$$
x\times S=x\times\sum\limits_{k=1}^{+\infty}(1-x)^{k-1}
$$

$$
S=\sum\limits_{k=1}^{+\infty}(1-x)^{k-1}
$$

$$
dp_{i,j}=S+x\times S\times dp_{i,j-1}
$$

$$
S=\sum\limits_{k=1}^{+\infty}(1-x)^{k-1}=\sum\limits_{k=0}^{+\infty}(1-x)^{k}
$$

$$
(1-x)\times S=\sum\limits_{k=1}^{+\infty}(1-x)^{k}
$$

$$
x\times S=1
$$

$$
S=\frac{1}{x}
$$

$$
dp_{i,j}=\frac{1}{x}+dp_{i,j-1}
$$

于是这道题就结束了。

放个代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 200010, mod = 998244353, iv2 = 499122177;

int T, n, a[N], inv[N], sqi[N];

int main (int argc, char *argv[]) {
	inv[1] = sqi[1] = 1;
	for (int i = 2; i <= 200000; ++i) {
		inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
		sqi[i] = 1ll * inv[i] * inv[i] % mod;
	}
	scanf ("%d", &T);
	while (T--) {
		scanf ("%d", &n);
		int cnt1 = n, cnt2 = 0;
		for (int i = 1; i <= n; ++i) {
			scanf ("%d", a + i);
			if (a[i]) --cnt1;
		}
		for (int i = 1; i <= cnt1; ++i) if (a[i]) ++cnt2;
		long long base = 1ll * n * (n - 1) % mod * iv2 % mod;
		long long res = 0;
		for (int i = 1; i <= cnt2; ++i) {
			res += base * sqi[i] % mod;
		}
		printf ("%lld\n", res % mod);
	}
}
```


---

## 作者：_lyx111 (赞：1)

Updated on 2022.10.27：感谢 @GaryGe 的指出，公式中 $i$ 的下标笔误打成了 $i=0$ 已修改为 $i=1$，望管理大大通过 qwq。

# CF1753C Wish I Knew How to Sort

[link](https://codeforces.com/problemset/problem/1753/C)

## 分析

前置知识：快速幂求逆元。

显然排完序后序列一定是 $00\dots 011\dots 1$，那么一定有个分界线 $cnt0$，容易知道 $cnt0$ 的值就是原数列 $a$ 中 $0$ 的个数。交换过程就是以分界线 $cnt0$，**左边的 $1$ 全部移动到右边，右边的 $0$ 全部移动到左边**。

下面单独考虑每一次操作的期望。

设：$cnt1$ 表示初始时 $cnt0$ 左边 $1$ 的个数。

设: 当前 $cnt0$ 左边有 $i$ 个 $1$，右边有 $i$ 个 $0$，交换左边的 $1$ 和右边的 $0$ 的概率为：$\frac{i^2}{C_n^2}$。（ 任选 $i,j$ 有 $c_n^2$ 种选法，而可以交换左边的 $1$ 和右边的 $0$ 的 $i,j$ 的选法有 $i^2$ 种）。由于望是概率的倒数，因此期望是：$\frac{C_n^2}{i^2}$。

那么对于总的期望只需枚举 $i(1\le i\le cnt1)$，那么总期望为：

$$\sum_{i=1}^{cnt1}\frac{C_n^2}{i^2}$$

那么套公式直接求答案即可。

## 代码

~~~cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+10,mod=998244353;
int n;
int a[MAXN];
int cnt0,cnt1; //数列中 0 的个数 cnt0，最终的 01 分界线在初始时左边的 1 的个数 cnt1 
int ans;
int ksm(int u,int v)
{
	int res=1;
	while(v)
	{
		if(v&1) res=1ll*res*u%mod;
		u=1ll*u*u%mod; v>>=1;
	}
	return res;
}
int C(int k) //求 C(k,2)=k*(k-1)/2
{
	return 1ll*k*(k-1)%mod*ksm(2,mod-2)%mod;
}
int main()
{
	int T; scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		cnt0=0;
		for(int i=1;i<=n;i++)
			if(a[i]==0) cnt0++; //统计数列中 0 的个数 cnt0
		cnt1=0;
		for(int i=1;i<=cnt0;i++)
			if(a[i]==1) cnt1++; //统计最终的 01 分界线在初始时左边的 1 的个数 cnt1 
		ans=0;
		for(int i=1;i<=cnt1;i++)
			ans=(ans+1ll*C(n)*ksm(1ll*i*i%mod,mod-2)%mod)%mod; //计算答案 
		printf("%d\n",ans);
	}
	return 0;
}
~~~

[AC记录](https://codeforces.com/contest/1753/submission/177994669)

## 写在最后

笔者水平有限，如果写的有不清楚或不对的地方望读者私信我指出，我会及时修正

---

## 作者：XenonWZH (赞：1)

[更好的阅读体验请点这](https://xenonwzh.github.io/cf-1753c/)

# 题意描述

[Codeforces 链接](https://codeforces.com/problemset/problem/1753/C)

你有一个只含 $0$ 和 $1$ 的 $n$ 位序列，你需要将这个序列排序。对于这个序列，你每次可以随机地选择两个数进行交换，求将这个序列排好序所交换次数的期望 $\mod 998244353$。

# 解题思路

本题求的是期望步数，可考虑使用 DP 解决。我们统计这个序列中有 $\text{cnt}$ 个 $0$，于是这个问题可以转化为将所有的 $0$ 移动到前 $\text{cnt}$ 位需要的步数的期望。我们设 $f_i$ 表示前 $\text{cnt}$ 位有 $i$ 个 $0$ 的情况下排好序所需要的期望步数，显然 $f_\text{cnt} = 0$。如果我们将 $f_i$ 状态变化为 $f_{i + 1}$ 状态，我们需要将前 $\text{cnt}$ 位中的一个 $1$ 和后 $\text{n - cnt}$ 位的一个 $0$ 进行交换。选出这对的概率为 $p = \frac{(\text{cnt} - i) \times (\text{cnt} - i)}{ \frac{n \times (n - 1)}{2} } = \frac{2 \times (\text{cnt} - i)^2}{n \times (n - 1)}$。于是我们可以通过期望的线性性质得到以下的状态转移方程（洛谷啥时候优化一下多行公式啊 QWQ）：

$f_i = p \times f_{i + 1} + (1 - p) \times f_i + 1$

经过计算可得 $f_i = f_{i + 1} + \frac{n \times (n - 1)}{2 \times (\text{cnt} - i)^2}$

状态转移方程的除法可以用快速幂求逆元解决。最后我们统计原序列中前 $\text{cnt}$ 项中有 $\text{now}$ 个 $0$，答案即为 $f_\text{now}$。时间复杂度为 $O(kn), k = \log 998244353$

# 代码演示

```cpp
#include <cstdio>
#include <vector>

const int MOD = 998244353;

inline long long pow(const int n, const int k) {
    long long ans = 1;
    for (long long num = n, t = k; t; num = num * num % MOD, t >>= 1) {
        if (t & 1) {
            ans = ans * num % MOD;
        }
    }
    return ans;
}

void solve() {
    int n;
    scanf("%d", &n);

    std::vector<int> a(n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    int cnt = 0, now = 0;
    for (int i = 0; i < n; i++) if (a[i] == 0) cnt++;
    for (int i = 0; i < cnt; i++) if (a[i] == 0) now++;

    std::vector<long long> f(cnt + 1);
    f[cnt] = 0;

    for (int i = cnt - 1; i >= 0; i--) {
        f[i] = (f[i + 1] + (1ll * n * (n - 1) % MOD * pow(2, MOD - 2) % MOD * pow(cnt - i, MOD - 2) % MOD * pow(cnt - i, MOD - 2) % MOD)) % MOD;
    }

    printf("%lld\n", f[now]);
}

int main() {
    int t;

    scanf("%d", &t);

    while (t--) solve();

    return 0;
}
```

---

## 作者：ningago (赞：0)

令 $m$ 表示序列里 $0$ 的个数。

那么题目就是让 $\forall i\in [1,m],a_i=0$，$\forall i\in (m,n],a_i=1$。

记 $dp_i$ 表示已经有 $i$ 个 $0$ 在 $[1,m]$ 的期望操作次数。

那么显然 $dp_m=0$。

考虑让怎么操作可以 $[1,m]$ 内 $0$ 个数变多（显然，操作不会让个数变少，所以操作一次后，个数要么 $+1$，要么不变）。

只有操作 $i\in [1,m],a_i=1,j\in (m,n],a_j=0$，才会让 $0$ 个数变多。

（$[1,m]$ 里 $1$ 的个数是 $m-i$，$(m,n]$ 里 $0$ 的个数也是 $m-i$，易证。）

否则个数不变。

有用的操作一共有 $C_n^2$ 种，所以转移方程就是：

$$dp_i=\dfrac{(m-i)^2}{C_n^2}dp_{i+1}+(1-\dfrac{(m-i)^2}{C_n^2})dp_i$$

也就是：

$$dp_i=dp_{i+1}+\dfrac{C_n^2}{(m-i)^2}$$

答案就是 $dp_k$，$k$ 表示初始时 $[1,m]$ 中 $0$ 的个数。

时间复杂度 $O(n)$（在 $O(1)$ 求逆元的情况下）。

```cpp
#include <cstdio>
#include <cstring>

#define N 200010
#define int long long
#define mod 998244353

int ksm(int a,int b)
{
	int res = 1;
	while(b)
	{
		if(b & 1)
			res = res * a % mod;
		a = a * a % mod; 
		b >>= 1;
	}
	return res;
}

int T;
int n;
int dp[N];
int a[N];
int m;

signed main()
{
	scanf("%lld",&T);
	while(T--)
	{
		m = 0;
		scanf("%lld",&n);
		for(int i = 1;i <= n;i++)
		{
			scanf("%lld",&a[i]);
			if(!a[i])
				m++; 
		} 
		int now = 0;
		for(int i = 1;i <= m;i++)
			if(!a[i])
				now++;
		dp[m] = 0;
		int C = n * (n - 1) / 2;
		C %= mod;
		for(int i = m - 1;i >= now;i--)
		{
			int t = C * ksm((m - i) * (m - i) % mod,mod - 2);
			dp[i] = dp[i + 1] + t;
			dp[i] %= mod; 
		}
		printf("%lld\n",dp[now]);
	}
	return 0;
}
```

---

## 作者：lzytag (赞：0)

## Solution
首先有一个及其显然的性质，我们最终的状态显然是前面一段 $0$，后面一段 $1$。

那我们考虑一下现在状态与最终状态的区别。

我们先来一个例子：

```
8
1 1 0 0 0 1 0 1
```

他的最终状态为

```
0 0 0 0 1 1 1 1
```
我们称最终状态为 $0$ 的位置为前半段，否则为后半段。

显然，前半段 $1$ 的个数与后半段 $0$ 的个数是一样的，设它为 $x$。

然后让我们分类讨论一下。

- 如果选到了同一半段的数，无论是否交换，显然 $x$ 不发生变化。
- 如果一个是前半段，一个是后半段，那么当且仅当选到了前半段的 $1$ 与后半段的 $0$ 才会发生交换，此时，$x$ 减少 $1$。

我们发现，$x$ 只减少不增加，一次减少只会减少 $1$，且减少 $1$ 的概率为:

$$ \frac{x^2}{n\times(n-1)\div 2}$$

所以期望为

$$\frac{n\times(n-1)}{2\times x^2}$$

于是总期望为：

$$\sum_{i=1}^x \frac{n\times(n-1)}{2\times i^2}$$

代码奉上：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
int read()
{
	int x;scanf("%d",&x);
	return x;
}
ll lread()
{
	ll x;scanf("%lld",&x);
	return x;
}
//file head over
#define Mod 998244353
#define MaxN 200005
int a[MaxN],cnt,n;
ll x;
ll qpow(ll x,ll y)
{
	ll res = 1;
	for(;y;y>>=1,x = x*x%Mod) if(y&1)res = res*x%Mod;
	return res;
}
ll ans;
void solve()
{
	x = cnt = ans = 0;
	n = read();
	for(int i = 1;i <= n;i++) a[i] = read(),cnt += 1-a[i];
	for(int i = 1;i <= cnt;i++) if(a[i] != 0) x++;
	ll y = 1ll*n*(n-1)/2;
	y%=Mod;
	for(int i = 1;i <= x;i++)
	{
		ans = (ans + y*qpow(1ll*i*i%Mod,Mod-2)%Mod)%Mod;
	}
	printf("%d\n",ans);
}
int main()
{
	int T = read();
	while(T--) solve();
   	return 0;
}
```

---

