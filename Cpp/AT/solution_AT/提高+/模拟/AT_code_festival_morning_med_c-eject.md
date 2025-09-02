# eject

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2014-morning-middle/tasks/code_festival_morning_med_c

一人暮らしをしている amylase さんは、夏に帰宅したとき部屋が暑くてつらい思いをしていました。 amylase さんは、帰宅した時にすでに部屋を涼しい状態にするために、家の外からエアコンを ON にしたいと考えました。

そこで、PC の CD トレイの前にエアコンのスイッチを置くことで CD トレイを開閉するたびにスイッチを押す装置を制作しました。 これにより、CD トレイを遠隔操作によって開閉することで、離れた場所からエアコンの ON と OFF を切り替えられるようになりました。

このエアコンのスイッチは初期状態が OFF であり、$ 1 $ 回スイッチを押すたびにエアコンの OFF と ON が切り替わります。

しかし amylase さんは小学校の図画工作で成績 $ 1 $ をもらうほど不器用だったので、CD トレイを $ 1 $ 回開閉しても確率 $ p $ でしかスイッチが押せないことがわかりました。

ヤケになった amylase さんは CD トレイを $ n $ 回開閉しました。

このとき、最終的にエアコンが ON になっている確率を求めてください。

## 说明/提示

### Sample Explanation 2

極端な入力に対して誤差が出ないように注意しましょう。

## 样例 #1

### 输入

```
0.3 1```

### 输出

```
0.3```

## 样例 #2

### 输入

```
0.0000000001 10000000000```

### 输出

```
0.432332358362```

# 题解

## 作者：Ryan_Adam (赞：2)

## 题解：AT_code_festival_morning_med_c eject
最优解祭。
### Tag
数学，递推。
### Solution
考虑先构造一下 $\text{dp}$ 式子。

我们设 $f_i$ 为按 $i$ 次开关灯为亮的概率，则显然有：
$$f_i=f_{i-1}\times(1-p)+(1-f_{i-1})\times p$$
化简后得到：
$$f_i=p+f_{i-1}\times(1-2p)$$

对于一个数列 $a$，如果我们知道了它满足 $a_n=k\times a_{n-1}+t$，可以构造一个数 $\lambda$ 使得 $a_n+\lambda=k(a_{n-1}+\lambda)$，设 $b_n=a_{n}+\lambda$，显然数列 $b$ 是等比数列，公比为 $k$，$b_n=\lambda$，所以 $b_n=\lambda\times k^{n}$，所以 $a_n=\lambda\times k^{n}-\lambda$。

下面考虑 $\lambda$ 怎么构造。因为 $a_n+\lambda=k(a_{n-1}+\lambda)$，化简得 $a_n=ka_{n-1}+(k-1)\lambda$，而 $a_n=ka_{n-1}+t$，所以 $(k-1)\lambda=t$，$\lambda=\dfrac{t}{k-1}$。

接下来回到原题，发现形式是一模一样的，$k$ 即为 $1-2p$，$t$ 即为 $p$，所以：
$$\lambda=\dfrac{p}{(1-2p)-1}=-\dfrac{1}{2}$$
套刚才推的式子得到：
$$a_n=-\dfrac{1}{2}(1-2p)^n+\dfrac{1}{2}$$
直接快速幂计算即可，复杂度 $\mathcal{O(\log n)}$。
### Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
double p;
int n;

double qpow(double a,int b)
{
    double res=1;
    for(;b;b>>=1)
    {
        if(b&1)res*=a;
        a*=a;
    }
    return res;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>p>>n;
    cout<<setprecision(10)<<-0.5*qpow(1-2*p,n)+0.5<<endl;
    return 0;
}
```

---

## 作者：chroneZ (赞：2)

## 形式化题意

有一个初始状态为 OFF 的开关（开关状态有 OFF/ON 两种），每次操作有 $p$ 的概率改变开关状态，求 $n$ 次操作后开关状态为 ON 的概率。

$n,p$ 为给定常数，其中 $1\leq n \leq 10^{18}$，**小数** $p\in [0,1]$。

## Sol

很容易想到一种 $dp$，设 $dp_{i,0/1}$ 表示进行了 $i$ 次操作后开关状态为关/开的概率。

分类第 $i$ 次操作有没有改变开关状态，则转移是显然的：

- $dp_{i,0}=dp_{i-1,1}\times p + dp_{i-1,0}\times (1-p)$

- $dp_{i,1}=dp_{i-1,0}\times p + dp_{i-1,1}\times (1-p)$

当然由于 $dp_{i,0}+dp_{i,1}$ 必定为 $1$，所以这里 $0/1$ 这一维可以省去。

重新定义 $dp_i$ 表示进行了 $i$ 次操作后开关状态为开的概率。

由上述推导可知 $dp_i=(1-dp_{i-1})\times p + dp_{i-1}\times (1-p)=(1-2p)dp_{i-1}+p$ 

直接转移是 $O(n)$ 的，但是我们观察上面那个式子，这不就是我们熟悉的 $a_n=ka_{n-1}+b$ 的数列通项嘛！

最终得到 $dp_n=\dfrac{1-(1-2p)^n}{2}$，直接计算即可。

```cpp
long double t=pow(1-2*p,n);
cout<<setprecision(15)<<fixed<<(1-t)/2;
```

---

## 作者：AzusidNya (赞：0)

#### AT_code_festival_morning_med_c

随机跳题跳到的。认为是显然没有蓝的简单概率题。

设 $p_i$ 表示经过了 $i$ 次操作后灯是开的的概率，初始值 $p_0 = 0$。

考虑怎么转移。要在第 $i$ 次操作后灯是开的，那么在第 $i - 1$ 次操作后如果灯是关的一定要通过这次操作以 $P$ 的概率把灯打开，否则就要以 $(1 - P)$ 的概率不改变灯的状态。

然后就可以写出递推式并进行一个简单的化简。
$$
\begin {aligned}
p_i &= P(1 - p_{i - 1}) + (1 - P)p_{i - 1}\\
&= (1 - 2P)p_{i - 1} + P
\end {aligned}
$$
注意到递推式的形式是 $f(n) = af(n - 1) + b$，这种递推式可以用待定系数法解出通项。可以设 $f(n) = Aa^n + B$ 然后待定系数，将 $Aa^n + B$ 代入 $f(0), f(1)$ 中就可以解出递推式了，求解比较工业化。

这里 $a = (1 - 2P), b = P, f(0) = 0, f(1) = P$，直接待定系数。

解得 $A = -\frac 12, B = \frac 12$，代入原递推式得到：
$$
p_i = \frac{1 - (1 - 2P) ^ i}{2}
$$
直接用 pow 算就行了。

```cpp
#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include<cmath>
#define int long long
using namespace std;
namespace azus{
	int n;
	long double u;
	int main(){
		cin >> u >> n;
		long double ql = pow(1.0 - 2.0 * u, n);
		cout.precision(10);
		cout << 0.5 * (1.0 - ql);
		return 0;
	}
}
signed main(){
	//ios::sync_with_stdio(0);
	//cin.tie(0), cout.tie(0);
	int T = 1;
	while(T --)
		azus::main();
	return 0;
}
```

---

## 作者：StayAlone (赞：0)


考虑分治。设 $solve(n)$ 表示 $n$ 次操作后，使得灯的状态反转的概率。

设 $p_1 = solve(\lfloor \frac{n}{2}\rfloor),p_2=1-p_1$。

- 当 $n$ 为偶数时，分成长度均为 $\frac{n}{2}$ 的两段：$[1,\frac{n}{2}]$ 和 $[\frac{n}{2}+1,n]$。要么第一段状态反转且第二段状态不反转，要么第一段状态不反转且第二段状态反转。这两种情况的概率都是 $p_1\times p_2$，所以答案就是 $2\times p_1\times p_2$；
- 当 $n$ 为奇数时，分成三段：$[1,\lfloor\frac{n}{2}\rfloor]$，$[\lfloor\frac{n}{2}\rfloor+1,n-1]$ 和 $[n,n]$，长度分别为 $\lfloor\frac{n}{2}\rfloor$，$\lfloor\frac{n}{2}\rfloor$ 和 $1$。想要状态反转，有这些情况：反转，不反转，不反转；不反转，反转，反转；不反转，不反转，反转；反转，反转，反转。其中第一种情况和第二种情况的答案都是 $p_1\times p_2\times (1-p)$，第三种情况的答案是 $p_2\times p_2\times p$，第四种情况的答案是 $p_1\times p_1\times p$。最终答案就是 $2\times p_1\times p_2\times (1-p) + p_2\times p_2\times p + p_1\times p_1\times p$。

边界显然是 $n=1$ 时，答案为 $p$。

时间复杂度 $\mathcal O(\log n)$。

[AC code record](https://www.luogu.com.cn/record/108770777)

```cpp
typedef long double ldb;
ldb p; ll n;

il ldb solve(ll n) {
	if (n == 1) return p;
	ldb p1 = solve(n / 2), p2 = 1 - p1;
	if (n & 1)
		return p1 * p2 * (1 - p) * 2 + p2 * p2 * p + p1 * p1 * p;
	return p1 * p2 * 2;
}

int main() {
	scanf("%Lf%lld", &p, &n);
	printf("%.15Lf", solve(n));
	rout;
}
```

---

