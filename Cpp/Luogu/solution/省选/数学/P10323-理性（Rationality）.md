# 理性（Rationality）

## 题目背景

数学之善，统治宇宙的根本原理 —— 理性。
****
「理性之光」伊奥，是古代精灵图形术士。已经千岁的她总能不受感情的干扰，以理性做出最优的决策。   

## 题目描述

赛时更新：请注意，对于一组确定的 $v_1,\cdots,v_n$，都可以求出 $\text{RSS}$ 的最小值。**它是关于随机变量  $v_1,\cdots,v_n$ 的一个随机变量**，将其记为 $X$，则要求的是 $\mathbb E[X]$。   
笔误改正：残差平方和的英文为 $\text{RSS}$。
****
伊奥的思绪回到了千年前的一场大战中。

她记得那场战斗中有 $n$ 个敌人，第 $i$ 个敌人在距离她 $d_i$（$d_i$ 之间互不相同）的位置上。这些敌人都带有一个**正整数**标记 $v_i$，只要以**恰好** $v_i$ 的攻击力击中它就可以将其消灭。

她只要设定一个一次函数 $f(x)=ax+b$，就能在距离她 $d_i$ 的位置放出 $f(d_i)$ 的攻击力。好在她的队友会辅助她攻击，她只用考虑确定 $a,b$ 使得 $f(x)$ 的效果最优，即最小化 $\text{RSS}$（残差平方和）：
$$\text{RSS}=\sum_{i=1}^n(f(d_i)-v_i)^2$$
当然了，这只是她的回忆。她能清晰记得每个敌人到她的距离 $d_i$，而对于 $v_i$ 她只记得满足 $l_i\leq v_i \leq r_i$。

她想知道假设每个 $v_i$ 都对应在 $[l_i,r_i]$ 范围内**均匀随机**的情况下，「$\text{RSS}$ **的最小值」的期望**。   
可以证明答案总是有理数，你只需要告诉她答案对 $998244353$ 取模的结果即可。

## 说明/提示

【样例 $1$ 解释】

此样例中有 $l_i=r_i$，即情况已经确定，只需要求出此时最优的 $a,b$ 即可。容易发现 $(1,4),(3,7),(5,10)$ 这三组数据可以用一次函数完美拟合：即 $f(x)=\dfrac 32 x+\dfrac{5}{2}$，与每个点偏差都是 $0$，故 $\text{RSS}$ 最小值的期望，也就是答案为 $0$。

【样例 $2$ 解释】

这里同样有 $l_i=r_i$。$5$ 个敌人的数据 $(d_i,v_i)$ 分别为 $(1,4),(2,5),(3,7),(4,8),(9,8)$，可以证明取
$$a=\frac{87}{194} \ , \ b=\frac{911}{194}$$
是一组使得 $\text{RSS}$ 最小的解，代入计算得
$$\text{RSS}=\sum_{i=1}^n\left( \frac{87}{194}d_i+\frac{911}{194}-v_i\right)^2=\frac{1047}{194}$$
在模 $998244353$ 意义下答案为 $488831003$。

【数据范围】

**本题采用捆绑测试。**

Subtask 1（10 pts）：$n \leq 3$；  
Subtask 2（10 pts）：$l_i=r_i$；  
Subtask 3（15 pts）：$n\le500$，$r_i\leq 500$；  
Subtask 4（15 pts）：$n\le 5000$；  
Subtask 5（20 pts）：$n\le 10^5$；  
Subtask 6（30 pts）：无特殊限制。

对于全部的数据，$2\le n \le 5\times 10^5$，$1\leq l_i \leq r_i \leq 10^8$，$1\leq d_i \leq 10^8$， $d_i<d_{i+1}$（$1\leq i <n$），并且有：
$$n\sum_{i=1}^nd_i^2 \not \equiv \left(\sum_{i=1}^nd_i \right)^2 \pmod{998244353}$$

【提示】

题目中要求出「$\text{RSS}$ 的最小值」期望值。对于离散随机变量 $X$，假设其可以取值为 $a_1,a_2,\cdots,a_n$，对应概率为 $p_1,p_2,\cdots,p_n$（$p_1+\cdots+p_n=1$），则其期望值可以定义为：
$$\mathbb E[X]=\sum_{i=1}^np_i a_i$$
对于计算有理数取模的方法，请参考[模板题](https://www.luogu.com.cn/problem/P2613)。

## 样例 #1

### 输入

```
3
1 4 4
3 7 7
5 10 10```

### 输出

```
0```

## 样例 #2

### 输入

```
5
1 4 4
2 5 5
3 7 7
4 8 8
9 8 8```

### 输出

```
488831003```

## 样例 #3

### 输入

```
5
1 1 4
2 2 5
3 3 7
4 2 8
9 3 8```

### 输出

```
884183796```

## 样例 #4

### 输入

```
10
123 1 10
234 11 14
345 10 20
456 6 6
567 20 30
678 84 90
789 1 3
8910 8 15
91011 123 129
101112 56 64```

### 输出

```
483360041```

# 题解

## 作者：__NULL1F1CAT10N__ (赞：10)

[Link](https://www.luogu.com.cn/problem/P10323)

考虑对一组固定的 $v_i$ 求 $RSS$ 最小值。

先将 $RSS$ 转换为关于 $a$ 的形式：

$RSS=\sum\limits_{i=1}^n(ad_i+b-v_i)^2=(\sum\limits_{i=1}^nd_i^2)a^2+2(\sum\limits_{i=1}^nd_i(b-v_i))a+(\sum\limits_{i=1}^n(b-v_i)^2)$

由 $n\sum\limits_{i=1}^nd_i^2\neq(\sum\limits_{i=1}^nd_i)^2$ 知 $d_i$ 不全相等，故 $\sum\limits_{i=1}^nd_i^2>0$，故此处 $a=-\frac{\sum\limits_{i=1}^nd_i(b-v_i)}{\sum\limits_{i=1}^nd_i^2}$ 取最小值。

将此时的 $RSS$ 转换为关于 $b$ 的形式：

此时 $RSS=\frac{1}{\sum\limits_{i=1}^nd_i^2}(\sum\limits_{i=1}^nd_i^2\sum\limits_{i=1}^n(b-v_i)^2-(\sum\limits_{i=1}^nd_i(b-v_i))^2)=\frac{(n\sum\limits_{i=1}^nd_i^2-(\sum\limits_{i=1}^nd_i)^2)b^2-2(\sum\limits_{i=1}^nv_i\sum\limits_{i=1}^nd_i^2-\sum\limits_{i=1}^nd_i\sum\limits_{i=1}^nd_iv_i)b+(\sum\limits_{i=1}^nd_i^2\sum\limits_{i=1}^nv_i^2-(\sum\limits_{i=1}^nd_iv_i)^2)}{\sum\limits_{i=1}^nd_i^2}$ 为一个关于 $b$ 的二次函数。

由题 $n\sum\limits_{i=1}^nd_i^2-(\sum\limits_{i=1}^nd_i)^2\neq0$ 且由柯西不等式知 $n\sum\limits_{i=1}^nd_i^2-(\sum\limits_{i=1}^nd_i)^2\ge0$。

故取 $b=\frac{\sum\limits_{i=1}^nv_i\sum\limits_{i=1}^nd_i^2-\sum\limits_{i=1}^nd_i\sum\limits_{i=1}^nd_iv_i}{n\sum\limits_{i=1}^nd_i^2-(\sum\limits_{i=1}^nd_i)^2}$ 可使 $RSS$ 最小。

此时 $RSS=-\frac{(\sum\limits_{i=1}^nv_i\sum\limits_{i=1}^nd_i^2-\sum\limits_{i=1}^nd_i\sum\limits_{i=1}^nd_iv_i)^2}{(n\sum\limits_{i=1}^nd_i^2-(\sum\limits_{i=1}^nd_i)^2)\sum\limits_{i=1}^nd_i^2}+\frac{\sum\limits_{i=1}^nd_i^2\sum\limits_{i=1}^nv_i^2-(\sum\limits_{i=1}^nd_iv_i)^2}{\sum\limits_{i=1}^nd_i^2}$。

此时的 $\mathbb{E}[RSS]$ 即为所求。

注意到 $d_i$ 固定，也就是说 $-\frac{1}{(n\sum\limits_{i=1}^nd_i^2-(\sum\limits_{i=1}^nd_i)^2)\sum\limits_{i=1}^nd_i^2}$，$\sum\limits_{i=1}^nd_i$ 和 $\sum\limits_{i=1}^nd_i^2$ 都是固定的。

即求 $\mathbb{E}[(\sum\limits_{i=1}^nv_i\sum\limits_{i=1}^nd_i^2-\sum\limits_{i=1}^nd_i\sum\limits_{i=1}^nd_iv_i)^2]$ 和 $\mathbb{E}[\sum\limits_{i=1}^nv_i^2]$ 以及 $\mathbb{E}[(\sum\limits_{i=1}^nd_iv_i)^2]$。

$\mathbb{E}[\sum\limits_{i=1}^nv_i^2]=\sum\limits_{i=1}^n\mathbb{E}[v_i^2]=\sum\limits_{i=1}^n(\frac{1}{r_i-l_i+1}\sum\limits_{j=l_i}^{r_i}j^2)=\sum\limits_{i=1}^n\frac{r_i(r_i+1)(2r_i+1)-l_i(l_i-1)(2l_i-1)}{6(r_i-l_i+1)}$。

$\mathbb{E}[(\sum\limits_{i=1}^nd_iv_i)^2]=\mathbb{E}[\sum\limits_{i=1}^nd_i^2v_i^2]+2\mathbb{E}[\sum\limits_{1\le i<j\le n}d_id_jv_iv_j]=\sum\limits_{i=1}^nd_i^2\mathbb{E}[v_i^2]+2\sum\limits_{1\le i<j\le n}d_i\mathbb{E}[v_i]d_j\mathbb{E}[v_j]=\sum\limits_{i=1}^nd_i^2\mathbb{E}[v_i^2]+(\sum\limits_{i=1}^nd_i\mathbb{E}[v_i])^2-\sum\limits_{i=1}^nd_i^2\mathbb{E}[v_i]^2$，
其中 $\mathbb{E}[v_i]=\frac{r_i(r_i+1)-l_i(l_i-1)}{2(r_i-l_i+1)}$。

$\mathbb{E}[(\sum\limits_{i=1}^nv_i\sum\limits_{i=1}^nd_i^2-\sum\limits_{i=1}^nd_i\sum\limits_{i=1}^nd_iv_i)^2]=(\sum\limits_{i=1}^nd_i^2)^2\mathbb{E}[(\sum\limits_{i=1}^nv_i)^2]+(\sum\limits_{i=1}^nd_i)^2\mathbb{E}[(\sum\limits_{i=1}^nd_iv_i)^2]-2\sum\limits_{i=1}^nd_i^2\sum\limits_{i=1}^nd_i\mathbb{E}[\sum\limits_{i=1}^nv_i\sum\limits_{i=1}^nd_iv_i]$，其中 $\mathbb{E}[(\sum\limits_{i=1}^nd_iv_i)^2]$ 已计算过，只需考虑 $\mathbb{E}[\sum\limits_{i=1}^nv_i\sum\limits_{i=1}^nd_iv_i]$ 和 $\mathbb{E}[(\sum\limits_{i=1}^nv_i)^2]$。

类似 $\mathbb{E}[(\sum\limits_{i=1}^nd_iv_i)^2]$，可以得出 $\mathbb{E}[(\sum\limits_{i=1}^nv_i)^2]=\sum\limits_{i=1}^n\mathbb{E}[v_i^2]+(\sum\limits_{i=1}^n\mathbb{E}[v_i])^2-\sum\limits_{i=1}^n\mathbb{E}[v_i]^2$，$\mathbb{E}[\sum\limits_{i=1}^nv_i\sum\limits_{i=1}^nd_iv_i]=\sum\limits_{i=1}^nd_i\mathbb{E}[v_i^2]+\sum\limits_{i=1}^n\mathbb{E}[v_i]\sum\limits_{i=1}^nd_i\mathbb{E}[v_i]-\sum\limits_{i=1}^nd_i\mathbb{E}[v_i]^2$。

最后计算出各式代入原式即可。代码有些凌乱，变量名命名可参考注释。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
int ksm(int a, int b, int p = mod) {
	int ret = 1;
	while(b) {
		if(b & 1) {
			ret = 1ll * ret * a % p;
		}
		a = 1ll * a * a % p;
		b >>= 1;
	}
	return ret;
}
int inv(int a, int p = mod) {
	return ksm(a, p - 2, p);
}
int n, d[500005], l[500005], r[500005], inv2, inv6;
int Evv[500005], Evd[500005], Etop, Sdd, Sevv, Sevd2, Sd, ESv2, ESvd2, ESvSvd, Ev[500005], SEv, SEv2, Sevdd, Sevd, Svvd, S;
/*
Evv_i = E[v_i^2]
Evd_i = E[v_id_i]=d_iE[v_i]
Ev_i = E[v_i]
下记 \sum\limits_{i=1}^n 为 Sum
Etop = E[(Sum(v)Sum(d^2)-Sum(d)Sum(vd))^2]
Sdd = Sum(d^2)
Sevv = Sum(E[v^2]) = E[Sum(v^2)]
Sevd2 = Sum(E[(vd)^2])
Sd = Sum(d)
ESv2 = E[Sum(v)^2]
ESvd2 = E[Sum(vd)^2]
ESvSvd = E[Sum(v)Sum(vd)]
SEv = Sum(E[v])
SEv2 = Sum(E[v]^2)
Sevdd = Sum(E[vd]^2)
Sevd = Sum(E[vd])
Svvd = Sum(dE[v^2])
S = Sum(E[vd]E[v])
*/
signed main() {
	cin >> n;
	inv2 = inv(2);
	inv6 = inv(6);
	for(int i = 1; i <= n; ++i) {
		cin >> d[i] >> l[i] >> r[i];
		Sdd += 1ll * d[i] * d[i] % mod;
		Sdd %= mod;
		Sd += d[i];
		Sd %= mod;
		Ev[i] = 1ll * (l[i] + r[i]) % mod * inv2 % mod;
		SEv += Ev[i];
		SEv2 += 1ll * Ev[i] * Ev[i] % mod;
		SEv %= mod;
		SEv2 %= mod;
		Evd[i] = 1ll * d[i] * (l[i] + r[i]) % mod * inv2 % mod;
		Evv[i] = 1ll * ((1ll * r[i] * (r[i] + 1) % mod * (2 * r[i] + 1) % mod - 1ll * l[i] * (l[i] - 1) % mod * (2 * l[i] - 1) % mod) + mod) * inv(r[i] - l[i] + 1) % mod * inv6 % mod;
		Sevv += Evv[i];
		Sevd += Evd[i];
		S += 1ll * Evd[i] * Ev[i] % mod;
		Sevd2 += 1ll * Evv[i] * d[i] % mod * d[i] % mod;
		Sevdd += 1ll * Evd[i] * Evd[i] % mod;
		Svvd += 1ll * Evv[i] * d[i] % mod;
		Sevv %= mod;
		Sevd %= mod;
		Sevd2 %= mod;
		Sevdd %= mod;
		Svvd %= mod;
		S %= mod;
	}
	ESv2 = ((Sevv + 1ll * SEv * SEv - SEv2) % mod + mod) % mod;
	ESvd2 = ((Sevd2 + 1ll * Sevd * Sevd - Sevdd) % mod + mod) % mod;
	ESvSvd = ((Svvd + 1ll * Sevd * SEv - S) % mod + mod) % mod;
	Etop = (1ll * ESv2 * Sdd % mod * Sdd % mod + 1ll * Sd * Sd % mod * ESvd2 % mod - 2ll * Sdd * Sd % mod * ESvSvd % mod) % mod;
	Etop = (Etop + mod) % mod;
	cout << 1ll * (1ll * Sdd * Sevv - ESvd2 - 1ll * Etop * inv((1ll * n * Sdd - 1ll * Sd * Sd) % mod) % mod + mod) % mod * inv(Sdd) % mod << endl;
	return 0;
}
```

---

## 作者：NaCly_Fish (赞：8)

首先我们考虑 $v_i$ 都已经固定的情况下，如何确定 $a,b$。  
由于 $\text{RSS}$ 必然非负，可以确定其必然存在一个最小值点（同时也是极值点）。即这一点上 $\text{RSS}$ 对 $a,b$ 的偏导数都为零，也就得到两个方程：

$$\sum_{i=1}^n(ad_i+b-v_i)d_i=0 \ , \ \sum_{i=1}^n(ad_i+b-v_i)=0$$
这是一个二元一次方程组，可以直接解出 $a,b$（其中 $\bar d$ 和 $\bar v$ 分别表示 $d,v$ 的算术平均数）：
$$\left( \sum_{i=1}^n(d_i-\bar d)^2\right)a=\sum_{i=1}^n(d_i-\bar d)(v_i-\bar v)$$
$$b=\bar v-a\bar d$$
代入答案中：
$$\min\{\text{RSS}\}=\sum_{i=1}^n(a(d_i-\bar d)-(v_i-\bar v))^2$$
尝试将平方展开：

$$\min\{\text{RSS}\}=a^2\sum_{i=1}^n(d_i-\bar d)^2-2a\sum_{i=1}^n(d_i-\bar d)(v_i-\bar v)+\sum_{i=1}^n(v_i-\bar v)^2$$
现在可以把前面解出来的 $a$ 用已知量替换掉了，这样就得到
$$\min\{\text{RSS}\}=\sum_{i=1}^n(v_i-\bar v)^2-\left( \sum_{i=1}^n(d_i -\bar d)^2\right)^{-1}\left(\sum_{i=1}^n (d_i-\bar d)(v_i-\bar v)\right)^2$$
注意 $(d_i-\bar d)$ 是常量，所以答案可以表示为 $\text{RSS}=S_1-cS_2$ 的形式。根据期望线性的性质，也就可以分开来计算。先看 $S_1$：
$$S_1=\sum_{i=1}^nv_i^2-\frac 1n\left( \sum_{i=1}^nv_i\right)^2$$
前面这个和式相对容易处理，还是利用期望线性的性质：
$$ \mathbb E\left[ \sum_{i=1}^n v_i^2\right]=\sum_{i=1}^n \mathbb E[v_i^2]=\sum_{i=1}^n \frac{1}{r_i-l_i+1}\sum_{v=l_i}^{r_i}v^2$$

利用自然数平方和的公式，可以直接 $\Theta(n)$ 计算。  

而对于 $S_2$ 只要先发现 $(d_i-\bar d)$ 之和为零，就化简为
$$S_2=\left(\sum_{i=1}^n(d_i-\bar d)v_i\right)^2$$

可以发现这剩下两部分是很类似的，都是需要计算这样的式子：

$$\mathbb E\left[ \left(\sum_{i=1}^n a_i v_i\right)^2\right]$$
（其中 $a_i$ 为给定的系数）

接下来只需要维护前 $n$ 项的 $k \ (0\leq k \leq 2)$ 次方和 $f_{n,k}$，则对于第 $n+1$ 项：
$$f_{n+1,k}=\mathbb E\left[ \left( \sum_{i=1}^{n+1} a_iv_i\right)^k\right]=\sum_{j=0}^k \binom kj f_{n,j} a_{n+1}^{k-j}\mathbb E[ v_{n+1}^{k-j}]$$
这样就可以直接递推了，$\mathbb E[v_i^j]$ 也可以直接计算出来，总时间复杂度为 $\Theta(n)$。

---

## 作者：vegetable_king (赞：5)

[可能更好的阅读体验](https://yjh965.github.io/post/p10323-li-xing-rationalityti-jie/)

初中二次函数题最有用的一集。

将 $f(x) = ax + b$ 展开，我们可以得到以下的式子：
$$
\sum_{i = 1}^n (d_i \times a + b - v_i)^2\\
$$
这个东西在 $b$ 取任意一个值的时候，都是一个关于 $a$ 的二次函数：
$$
\sum_{i = 1}^n d_i^2 a^2 + 2(b - v_i)d_i \times a + (b - v_i)^2\\
$$
这个函数的二次项始终为正数，于是当 $a$ 取对称轴时函数取到最小值：
$$
a = \frac{\sum_{i = 1}^n (v_i - b)d_i}{\sum_{i = 1}^n d_i^2}\\
\left(\sum_{i = 1}^n d_i^2\right)\left(\frac{\sum_{i = 1}^n (v_i - b)d_i}{\sum_{i = 1}^n d_i^2}\right)^2 + 2\left(\sum_{i = 1}^n (b - v_i)d_i\right)\left(\frac{\sum_{i = 1}^n (v_i - b)d_i}{\sum_{i = 1}^n d_i^2}\right) + \left(\sum_{i = 1}^n (b - v_i)^2\right)\\
\frac{(\sum_{i = 1}^n v_id_i)^2 - 2(\sum_{i = 1}^n v_id_i)(b\sum_{i = 1}^n d_i) + b^2(\sum_{i = 1}^n d_i)^2}{\sum_{i = 1}^n d_i^2} + 2\left(b \sum_{i = 1}^n d_i - \sum_{i = 1}^n v_id_i\right)\left(\frac{\sum_{i = 1}^n v_id_i - b \sum_{i = 1}^n d_i}{\sum_{i = 1}^n d_i^2}\right) + \left(\sum_{i = 1}^n b^2 - 2bv_i + v_i^2\right)\\
svd = \sum_{i = 1}^n v_id_i, sd = \sum_{i = 1}^n d_i, sd2 = \sum_{i = 1}^n d_i^2, sv = \sum_{i = 1}^n v_i, sv2 = \sum_{i = 1}^n v_i^2\\
nb^2 - 2sv \times b + sv2 - \frac{b^2 \times sd^2 - 2svd \times sd \times b + svd^2}{sd2}\\
\left(n - \frac{sd^2}{sd2}\right)b^2 + 2\left(\frac{svd \times sd}{sd2} - sv\right)b + sv2 - \frac{svd^2}{sd2}\\
$$
代入后得到了一个只与 $b$ 有关的二次函数。然后我们需要判断 $n - \frac{sd^2}{sd2}$ 的正负性，但是这是容易证明一定 $\ge 0$ 的。
$$
n - \frac{sd^2}{sd2} \ge 0\\
n \ge \frac{sd^2}{sd2}\\
nsd2 \ge sd^2\\
n\sum_{i = 1}^n d_i^2 \ge \left(\sum_{i = 1}^n d_i\right)^2\\
n\sum_{i = 1}^n d_i^2 \ge \sum_{1 \le i, j \le n} d_i d_j\\
(n - 1)\sum_{i = 1}^n d_i^2 \ge \sum_{1 \le i, j \le n, i \ne j} d_i d_j\\
\sum_{1 \le i, j \le n, i \ne j}^n d_i^2 - \sum_{1 \le i, j \le n, i \ne j} d_i d_j \ge 0\\
\sum_{1 \le i, j \le n, i \ne j}^n d_i^2 - d_i d_j \ge 0\\
\sum_{1 \le i < j \le n}^n d_i^2 + d_j ^ 2 - 2 d_i d_j \ge 0\\
$$
而对于任意两个正整数 $x, y$ 都显然有 $x^2 + y^2 \ge 2xy$（$(x - y)^2 \ge 0$），于是结论成立。又因为题目保证 $n - \frac{sd^2}{sd2} > 0$，所以不会出现除 $0$ 的情况，$b$ 取对称轴时函数取到最小值。
$$
b = \frac{sv - \frac{svd \times sd}{sd2}}{n - \frac{sd^2}{sd2}}\\
sv2 - \frac{svd^2}{sd2} - \frac{(sv - \frac{svd \times sd}{sd2})^2}{n - \frac{sd^2}{sd2}}\\
sv2 - \frac{svd^2}{sd2} - \frac{sv^2 - 2sv\frac{svd \times sd}{sd2} + \left(\frac{svd \times sd}{sd2}\right)^2}{n - \frac{sd^2}{sd2}}\\
sv2 - \frac{svd^2}{sd2} - \left(\frac{sv^2}{n - \frac{sd^2}{sd2}} - 2\frac{\frac{sd}{sd2}}{n - \frac{sd^2}{sd2}}sv \times svd + \frac{\left(\frac{sd}{sd2}\right)^2}{n - \frac{sd^2}{sd2}}svd^2\right)\\
sv2 - \frac{svd^2}{sd2} - \frac{\left(\frac{sd}{sd2}\right)^2}{n - \frac{sd^2}{sd2}}svd^2 - \frac{sv^2}{n - \frac{sd^2}{sd2}} + 2\frac{\frac{sd}{sd2}}{n - \frac{sd^2}{sd2}}sv \times svd\\
$$
于是我们得到了，对于一个固定的 $v$，代价的最小值是这么一坨东西。而 $sd, sd2$ 都是已知的，所以只需要求出 $sv2, svd^2, sv^2, sv \times svd$ 的期望即可。代入第一个 $v$ 固定的样例，虽然中间涉及到的数很大，但是最后答案是 $0$，和样例输出相符合！

具体怎么求呢？先考虑 $sv2$。根据期望的线性性，显然有：
$$
sv2 = \sum_{i = 1}^n \frac{S_2(l_i, r_i)}{r_i - l_i + 1}
$$
直接计算即可。

考虑设状态 $f_{i, 0 / 1 / 2 / 3 / 4}$ 分别表示 $sv, svd, sv^2, sv \times svd, svd^2$ 只考虑前 $i$ 项的期望，可以推导出转移方程：
$$
f_{i, 0} = f_{i - 1, 0} + \frac{l_i + r_i}2\\
f_{i, 1} = f_{i - 1, 1} + d_i\frac{l_i + r_i}2\\
f_{i, 2} = f_{i - 1, 2} + (l_i + r_i)f_{i - 1, 0} + \frac{S_2(l_i, r_i)}{r_i - l_i + 1}\\
f_{i, 3} = f_{i - 1, 3} + \frac{l_i + r_i}2f_{i - 1, 1} + d_i\frac{l_i + r_i}2f_{i - 1, 0} + d_i\frac{S_2(l_i, r_i)}{r_i - l_i + 1}\\
f_{i, 4} = f_{i - 1, 4} + d_i(l_i + r_i)f_{i - 1, 1} + d_i^2\frac{S_2(l_i, r_i)}{r_i - l_i + 1}\\
$$
然后可以 $O(n)$ 递推，但是计算逆元需要 $O(n \log mod)$。这题就做完了。

[对着式子写就能过的题，应该不会有人要代码吧？](https://www.luogu.com.cn/paste/sjn0oaq0)

---

## 作者：xieziheng (赞：3)

怒了，竟然没做出来这题。

赛时因为不会求偏导所以摆了，但显然不需要求。

先考虑对于固定 $v_i$ 后的答案是什么。

考虑 $\sum_{i=1}^{n} (ad_i+b-v_i)^2=\sum_{i=1}^{n} (ad_i+b)^2-2\sum_{i=1}^{n} (ad_i+b)v_i +\sum_{i=1}^{n} v_i^2=a^2\sum_{i=1}^{n} d_i^2+2ab\sum_{i=1}^{n} d_i+b^2n-2a\sum_{i=1}^{n} d_iv_i-2b\sum_{i=1}^{n} v_i+\sum_{i=1}^{n} v_i^2$。

记 $A=\sum_{i=1}^{n} d_i^2,B=\sum_{i=1}^{n} d_i,C=n,D=\sum_{i=1}^{n} d_iv_i,E=\sum_{i=1}^{n} v_i,F=\sum_{i=1}^{n} v_i^2$。

原式即 $Aa^2+2Bab+Cb^2-2Da-2Eb+F$。

以 $b$ 为主元，那么 $Cb^2+(2Ba-2E)b \geq - \frac {(2Ba-2E)^2} {4C}=- \frac {B^2a^2-2BEa+E^2} {C}$。

所以原式 $\geq Aa^2-2Da+F-\frac {B^2a^2-2BEa+E^2} {C}=
\frac {B^2a^2-2BEa+E^2} {C}=\frac {AC-B^2} {C}a^2+\frac {2BE-2CD} {C}a-\frac {E^2} {C} +F$。

再做一次，则原式 $\geq -\frac {(\frac {2BE-2CD} {C})^2} {4 \frac {AC-B^2} {C}}-\frac {E^2} {C} +F$

$=-\frac {(BE-CD)^2} {AC^2-B^2C}-\frac {E^2} {C} +F$

注意到 $A,B,C$ 是定值，所以只需要求出 $(BE-CD)^2,E^2,F$  的期望即可。

求 $F$ 是简单的，只需要分别求出 $v_i^2$ 的期望即可。

考虑 $(BE-CD)=\sum_{i=1}^{n} d_i \sum_{i=1}^{n} v_i-n\sum_{i=1}^{n} d_iv_i=\sum_{i=1}^{n} (B-nd_i)v_i$。

而 $B-nd_i$ 是常数，和求 $E^2$ 的期望类似。

只需要求对于定值 $a_1,\cdots,a_n$，$(\sum_{i=1}^{n} a_iv_i)^2$ 的期望即可。

这是一个经典套路，好像有一堆什么 OSU 题。

考虑 $f_{i,j}$ 表示 $(\sum_{k=1}^{i} a_kv_k)^j$ 的期望，那么把 $(\sum_{k=1}^{i} a_kv_k)^j$ 展开，就有 $f_{i,j}=\sum_{k=0}^{j} \binom{j}{k}f_{i-1,k}a_i^{j-k} \mathbb E[v_i^{j-k}]$。

这样就可以求出 $(BE-CD)^2$ 和 $E^2$ 的期望。

---

## 作者：ZhongYuLin (赞：2)

本文给出对于确定的 $v$ 的解法。后面的步骤其余题解已经是完备的了。

记 $A=\begin{bmatrix}
 x_1 & 1\\ 
 x_2 & 1\\
 \dots & \dots \\
 x_{n-1} & 1\\ 
 x_n & 1
\end{bmatrix}$，$\textbf{y}=\begin{bmatrix}
 v_1\\
 v_2\\
 \cdots \\
 v_{n-1}\\
v_n
\end{bmatrix}$，$\textbf{x}=\begin{bmatrix}
 a\\
b
\end{bmatrix}$。

依照题意，我们可以构建一个方程：

$$A\textbf{x}=\textbf{y}$$

这个方程当然是大概率没有解的。注意到题目要求，我们即是要求出一个解 $\textbf{z}$，使得 $\forall \textbf{x}$，$|A\textbf{x}-\textbf{y}|\geq |A\textbf{z}-\textbf{y}|$。

我们先考虑只有三个点的时候的情况。考虑去刻画矩阵 $A$ 的列空间。$A$ 的列空间可以理解为 $\mathbb{R}^3$ 中的一个平面，因为两个线性无关的三维向量形成了 $\mathbb{R}^3$ 中的一个平面。将 $\textbf{y}$ 视作这个 $\mathbb{R}^3$ 中的一个点。

那什么时候 $|A\textbf{z}-\textbf{y}|$ 最小呢？显然是 $A\textbf{z}-\textbf{y}$ 垂直这个平面时最小。由高中立体几何可知，$A\textbf{z}-\textbf{y}$ 垂直于 $A$ 的两个列向量，即：

$$A^\mathsf{T}(A\textbf{z}-\textbf{y})=0$$

整理有：

$$A^\mathsf{T}A\textbf{z}=A^\mathsf{T}\textbf{y}$$

类似的，可以推广至超平面。

对应到本题，即是：

$$\begin{bmatrix}
 \sum_{i=1}^{n} d_i^2 & \sum_{i=1}^{n} d_i\\
  \sum_{i=1}^{n} d_i&n
\end{bmatrix}
\begin{bmatrix}
 a\\
b
\end{bmatrix}
=
\begin{bmatrix}
 \sum_{i=1}^{n}d_iv_i\\
\sum_{i=1}^{n}v_i
\end{bmatrix}$$

第一步结束。后面的暴力推式子就行了。

---

## 作者：warzone (赞：2)

题意较长，就不放了。

-----------------------------------------------------------------

首先考虑在 $v_1,v_2,\cdots,v_n$ 确定时 $\operatorname{RSS}$ 的最小值。将

$$\mathrm{RSS}=\sum_{k=1}^n(ad_k+b-v_k)^2$$

分别对 $a,b$ 求偏导，得到其取最小值的条件

$$
\begin{cases}
	\dfrac{\partial\mathrm{RSS}}{\partial a}=\displaystyle\sum_{k=1}^n2(ad_k+b-v_k)d_k=0\\
	\dfrac{\partial\mathrm{RSS}}{\partial b}=\displaystyle\sum_{k=1}^n2(ad_k+b-v_k)=0
\end{cases}
$$

也即

$$
\begin{bmatrix}
	\displaystyle\sum_{k=1}^nd_k^2&\displaystyle\sum_{k=1}^nd_k\\
	\displaystyle\sum_{k=1}^nd_k&n\\
\end{bmatrix}{a\brack b}=
\begin{bmatrix}
\displaystyle\sum_{k=1}^nd_kv_k\\
\displaystyle\sum_{k=1}^nv_k
\end{bmatrix}
$$

该式两边同除以 $n$，得

$$
\begin{bmatrix}
	^{}\overline{d^2}&\overline{d}^{^{}}\\
	\overline{d}&1
\end{bmatrix}{a\brack b}=
\begin{bmatrix}
\overline{dv}\\\overline{v}
\end{bmatrix}
$$

解得

$$
a=\dfrac{\overline{dv}-\overline{d}\overline{v}}{\overline{d^2}-\overline{d}^2},
b=\dfrac{\overline{d^2}\overline{v}-\overline{d}^{}\overline{dv}}{\overline{d^2}-\overline{d}^2}\qquad(1)
$$

而

$$
\mathrm{RSS}=\sum_{k=1}^n(a^2d_k^2+b^2+v_k^2-2abd_k-2ad_kv_k-2bv_k)\\
=a^2\sum_{k=1}^nd_k^2+nb^2+\sum_{k=1}^nv_k^2-2ab\sum_{k=1}^nd_k-2a\sum_{k=1}^nd_kv_k-2b\sum_{k=1}^nv_k\\
=n\left(a^2\overline{d^2}+b^2+\overline{v^2}-2ab\overline{d}-2a\overline{dv}-2b\overline{v}\right)
$$

代入 $(1)$，化简得

$$
\min\mathrm{RSS}=n\left(\overline{v^2}-\overline{v}^2-\dfrac{(\overline{dv}-\overline{d}\overline{v})^2}{\overline{d^2}-\overline{d}^2}\right)
$$

----------------------------------------------------

接下来计算 $\min\mathrm{RSS}$ 的期望。由于

$$
\min\mathrm{RSS}=n\left(\dfrac{1}{n}\sum_kv_k^2-\dfrac{1}{n^2}\sum_{i,j}v_kv_j-\dfrac{\left(\displaystyle\dfrac{1}{n}\sum_{k}d_kv_k-\dfrac{1}{n}\sum_k\overline{d}v_k\right)^2}{\overline{d^2}-\overline{d}^2}\right)\\
=\sum_k v_k^2-\dfrac{1}{n}\sum_{i,j}v_iv_j-n\dfrac{\dfrac{1}{n^2}\left(\displaystyle\sum_k(d_k-\overline{d})v_k\right)^2}{\overline{d^2}-\overline{d}^2}\\
=\sum_{k}\left(1-\dfrac{1}{n}\right)v_k^2-\dfrac{1}{n}\sum_{i\not=j}v_iv_j-\dfrac{\displaystyle\sum_{i,j}(d_i-\overline{d})(d_j-\overline{d})v_iv_j}{n(\overline{d^2}-\overline{d}^2)}\\
=\sum_{k}\left(1-\dfrac{1}{n}\right)v_k^2-\dfrac{1}{n}\sum_{i\not=j}v_iv_j-\dfrac{\displaystyle\sum_{i\not=j}(d_i-\overline{d})(d_j-\overline{d})v_iv_j+\sum_k(d_k-\overline{d})^2v_k^2}{\displaystyle\sum_k(d_k-\overline{d})^2}
$$

故

$$
\mathbb{E}(\min\mathrm{RSS})=\sum_{k}\left(1-\dfrac{1}{n}\right)\mathbb{E}(v_k^2)-\dfrac{1}{n}\sum_{i\not=j}\mathbb{E}(v_i)\mathbb{E}(v_j)-\dfrac{\displaystyle\sum_{i\not=j}(d_i-\overline{d})(d_j-\overline{d})\mathbb{E}(v_i)\mathbb{E}(v_j)+\sum_k(d_k-\overline{d})^2\mathbb{E}(v_k^2)}{\displaystyle\sum_k(d_k-\overline{d})^2}\\
=\sum_{k}\left(1-\dfrac{1}{n}\right)\mathbb{E}(v_k^2)-\dfrac{1}{n}\left(\sum_{k}\mathbb{E}(v_k)\right)^2+\dfrac{1}{n}\sum_k\mathbb{E}^2(v_k)-\dfrac{\displaystyle\left(\sum_k(d_k-\overline{d})\mathbb{E}(v_k)\right)^2+\sum_k(d_k-\overline{d})^2(\mathbb{E}(v_k^2)-\mathbb{E}^2(v_k))}{\displaystyle\sum_k(d_k-\overline{d})^2}
$$

而由等差数列求和公式和平方和公式可得

$$
\mathbb{E}(v_i)=\dfrac{1}{r_i-l_i+1}\sum_{k=l_i}^{r_i}k=\dfrac{l_i+r_i}{2}\\
\mathbb{E}(v_i^2)=\dfrac{1}{r_i-l_i+1}\sum_{k=l_i}^{r_i}k^2=\dfrac{1}{6}(2r_i^2+2l_ir_i+2l_i^2+r_i-l_i)
$$

$\forall k\in[1,n]\cap\N$，计算出 $\mathbb{E}(v_i),\mathbb{E(v_i^2)}$ 后，即可计算出 $\mathbb{E}(\min\mathrm{RSS})$。

时间复杂度 $\Theta(n)$。

---------------------------

### Code（97ms,6.33MB）

```cpp
/*
this code is made by warzone
2024.4.11 16:42
*/
#include<stdio.h>
typedef unsigned long long ull;
typedef unsigned int word;
struct READ{//快读
	char c;
	inline READ(){c=getchar();}
	template<typename type>
	inline READ& operator >>(type& num){
		for(;'0'>c||c>'9';c=getchar());
		for(num=0;'0'<=c&&c<='9';c=getchar())
			num=num*10+(c-'0');
		return *this;
	}
}cin;
const word mod=998244353;
constexpr word qpow(word a,word b){
	word ans=1;
	for(;b;b>>=1){
		if(b&1) ans=1ull*ans*a%mod;
		a=1ull*a*a%mod;
	}
	return ans;
}
const word ni6=qpow(6,mod-2),ni2=qpow(2,mod-2);
word n,d[1<<19],Ev[1<<19],Ev2[1<<19];
int main(){
	cin>>n;
	const word nin=qpow(n,mod-2);
	ull _d=0;
	for(word i=1,l,r;i<=n;++i){
		cin>>d[i]>>l>>r;
		Ev[i]=1ull*ni2*(l+r)%mod;
		Ev2[i]=(2ull*r*r+2ull*l*r+2ull*l*l+r-l)%mod*ni6%mod;
		_d+=d[i];
	}
	_d=_d%mod*nin%mod;
	ull ans=0;
	for(word i=1;i<=n;++i){
		d[i]+=mod-_d;
		ans+=1ull*d[i]*Ev[i]%mod;
	}
	ans%=mod,ans=ans*ans%mod;
	ull Dd=0;
	for(word i=1;i<=n;++i){
		d[i]=1ull*d[i]*d[i]%mod,Dd+=d[i];
		ans+=(1ull*(mod-Ev[i])*Ev[i]%mod+Ev2[i])%mod*d[i]%mod;
	}
	ans=ans%mod*qpow(mod-(Dd%mod),mod-2);
	ull sumE=0;
	for(word i=1;i<=n;++i){
		ans+=(1ull+mod-nin)*Ev2[i]%mod+1ull*nin*Ev[i]%mod*Ev[i]%mod;
		sumE+=Ev[i];
	}
	sumE%=mod;
	ans=ans%mod+1ull*nin*(mod-sumE)%mod*sumE%mod;
	printf("%llu",ans%mod);
	return 0;
}
```

---

## 作者：win114514 (赞：1)

神秘题。

### 思路

$$\begin{aligned}
RSS&=\sum_{i=1}^n(f(d_i)-v_i)^2\\
&=\sum_{i=1}^n(ad_i+b-v_i)^2\\
&=\sum_{i=1}^nv^2+((-2ad_i)-2b)v+a^2d_i^2+2abd_i+b^2\\
\end{aligned}$$

设：

$$\begin{aligned}
S&=\sum_{i=1}^n d_i^2\\
T&=\sum_{i=1}^n d_i\\
U&=\sum_{i=1}^n d_iv_i\\
V&=\sum_{i=1}^n v_i\\
W&=\sum_{i=1}^n v_i^2\\
\end{aligned}$$

所以：

$$\begin{aligned}
RSS&=\sum_{i=1}^nv^2+((-2ad_i)-2b)v+a^2d_i^2+2abd_i+b^2\\
&=a^2S+2abT-2aU-2bV+nb^2+W
\end{aligned}$$

算这玩意的最值：

$$\begin{aligned}
nb^2-2bV+2abT&=nb^2+(2aT-2V)b\\
&\ge -\frac{V^2-2TVa+T^2a^2}{n}
\end{aligned}$$

那么：

$$\begin{aligned}
RSS&=a^2S-2aU-\frac{V^2-2TVa+T^2a^2}{n}+W\\
&=(S-\frac{T^2}{n})a^2+(\frac{2TV}{n}-2U)a-\frac{V^2}{n}+W\\
&\ge \frac{(SW-U^2)n-T^2W-SV^2+2TUV}{Sn-T^2}
\end{aligned}$$

发现 $S,T$ 是定值。

我们只需要算 $W,U^2,V^2,UV$ 的期望即可。

这个可以简单 dp。

### Code

```cpp
/*
  ! Though life is hard, I want it to be boiling.
  ! Created: 2024/05/03 19:51:38
*/
#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
#define int long long
#define mp(x, y) make_pair(x, y)
#define eb(...) emplace_back(__VA_ARGS__)
#define fro(i, x, y) for (int i = (x); i <= (y); i++)
#define pre(i, x, y) for (int i = (x); i >= (y); i--)
inline void JYFILE19();

typedef pair<int, int> PII;

bool ST;
const int N = 1e6 + 10;
const int mod = 998244353;

int n, m, S, T, ans, num, d[N], v[N], l[N], r[N], f[N][7];

inline int power(int x, int y) {
  int res = 1;
  while (y) {
    if (y & 1) res = res * x % mod;
    x = x * x % mod, y /= 2;
  }
  return res;
}
inline int ask1(int x) {
  return x * (x + 1) / 2 % mod;
}
inline int ask1(int l, int r) {
  return (ask1(r) - ask1(l - 1) + mod) % mod;
}
inline int ask2(int x) {
  return (__int128)x * (x + 1) * (2 * x + 1) / 6 % mod;
}
inline int ask2(int l, int r) {
  return (ask2(r) - ask2(l - 1) + mod) % mod;
}

signed main() {
  JYFILE19();
  cin >> n, num = 1;
  fro(i, 1, n) cin >> d[i] >> l[i] >> r[i];
  fro(i, 1, n) (S += d[i] * d[i]) %= mod;
  fro(i, 1, n) (T += d[i]) %= mod;
  f[0][0] = 1;
  fro(i, 1, n) {
    int A1 = ask1(l[i], r[i]);
    int A2 = ask2(l[i], r[i]);
    f[i][0] = f[i - 1][0] * (r[i] - l[i] + 1) % mod;
    f[i][1] = (f[i - 1][1] * (r[i] - l[i] + 1) + A2 * f[i - 1][0]) % mod;
    f[i][2] = (f[i - 1][2] * (r[i] - l[i] + 1) + A1 * f[i - 1][0] % mod * d[i]) % mod;
    f[i][3] = f[i - 1][3] * (r[i] - l[i] + 1) % mod;
    f[i][3] = (A1 * f[i - 1][2] % mod * d[i] + f[i][3]) % mod;
    f[i][3] = (A1 * f[i - 1][2] % mod * d[i] + f[i][3]) % mod;
    f[i][3] = (A2 * f[i - 1][0] % mod * d[i] % mod * d[i] + f[i][3]) % mod;
    f[i][4] = (f[i - 1][4] * (r[i] - l[i] + 1) + A1 * f[i - 1][0]) % mod;
    f[i][5] = f[i - 1][5] * (r[i] - l[i] + 1) % mod;
    f[i][5] = (A1 * f[i - 1][4] + f[i][5]) % mod;
    f[i][5] = (A1 * f[i - 1][4] + f[i][5]) % mod;
    f[i][5] = (A2 * f[i - 1][0] + f[i][5]) % mod;
    f[i][6] = f[i - 1][6] * (r[i] - l[i] + 1) % mod;
    f[i][6] = (A1 * f[i - 1][2] + f[i][6]) % mod;
    f[i][6] = (A1 * f[i - 1][4] % mod * d[i] + f[i][6]) % mod;
    f[i][6] = (A2 * f[i - 1][0] % mod * d[i] + f[i][6]) % mod;
  }
  (ans += (S * f[n][1] - f[n][3]) % mod * n % mod) %= mod;
  (ans -= T * T % mod * f[n][1] % mod) %= mod;
  (ans -= S * f[n][5] % mod) %= mod;
  (ans += 2 * T % mod * f[n][6] % mod) %= mod;
  num = num * (S * n % mod - T * T % mod) % mod;
  num = power(num * f[n][0] % mod, mod - 2) % mod;
  ans = (ans % mod + mod) % mod;
  num = (num % mod + mod) % mod;
  cout << ans * num % mod << "\n";
  return 0;
}

bool ED;
inline void JYFILE19() {
  // freopen("", "r", stdin);
  // freopen("", "w", stdout);
  srand(random_device{}());
  ios::sync_with_stdio(0), cin.tie(0);
  double MIB = fabs((&ED - &ST) / 1048576.), LIM = 512;
  cerr << "MEMORY: " << MIB << endl, assert(MIB <= LIM);
}
```

---

## 作者：Edward1002001 (赞：1)

~~场上因为多打了两处 ``*n`` 没调出来~~

首先我们假设直线方程是 $y=Ax+B$，考虑如何确定 $A,B$。

变形，有 $F=\sum f^2(d_i)+v_i^2-2f(d_i)v_i=A^2d_i^2+B^2+2ABd_i+v_i^2-2v_i(Ad_i+B)$

求偏导，有：
$$\frac{\partial F}{\partial A}=\sum d_i^2(2A)+2Bd_i-2v_id_i=0$$

$$\frac{\partial F}{\partial B}=\sum 2B+2Ad_i-2v_i=0$$

设 $P=\sum d_i^2,Q=\sum d_i,R=\sum v_id_i,S=\sum v_i$，那么,$2AP+2QB-2R=0,2nB+2AQ-2S=0$，解得：
$$A=\frac{nR-QS}{nP-Q^2},B=\frac{-QR+PS}{nP-Q^2}$$

注意到，$P,Q$ 都是只关于 $d$ 的量，因此本题中只有 $R,S$ 是根据随机而变化的量，我们高兴地发现，分母中全都是常量，如果分母有随机量，感觉比较难处理。

于是，我们设 $A=aR+bS,B=cR+dS$，其中 $a=\frac{n}{nP-Q^2},b=c=\frac{-Q}{nP-Q^2},d=\frac{P}{nP-Q^2}$，代入 $F$ 中，设 $X=ad_i+c,Y=bd_i+d$ 可得

$\begin{aligned}F&=\sum (X(\sum vd)+Y(\sum v)+v_i)^2\\&=\sum X^2(\sum vd)^2+2XY(\sum v)(\sum vd)+Y^2 (\sum v)^2-2Xv_i(\sum vd)-2Yv_i(\sum v)+v_i^2\end{aligned}$

展开一部分 $X$ 和 $Y$ ，有

$$F=\sum X^2(\sum vd)^2+2XY(\sum v)(\sum vd)+Y^2 (\sum v)^2-2(ad_i+c)v_i(\sum vd)-2(bd_i+d)v_i(\sum v)+v_i^2$$

那么设 $A_2=(\sum vd)^2,B_2=(\sum v)(\sum vd),C_2=(\sum v)^2,D_2=\sum v^2$，则有

$$F=((\sum X^2)-2a)A_2+((\sum 2XY)-2(b+c))B_2+((\sum Y^2)-2d)C_2+D_2$$

其中，$\sum X^2$ 之类的是有关 $d$ 的二次多项式，直接累加计算即可。

然后我们要求的就只有 $A_2,B_2,C_2,D_2$ 了，考虑期望的线性性，若用 $(\sum \text{E}v)^2$ 近似 $\text{E}(\sum v)^2$，则不同的项就为 $\sum \text{E}v^2-(\text{E}v)^2$。设

$$A=\sum \text{E}v,B=\sum (\text{E}v)^2,C=\sum \text{E}v^2,D=\sum d\text{E}v$$

$$E=\sum d(\text{E}v)^2,F=\sum d\text{E}v^2,G=\sum d^2(\text{E}v)^2,H=\sum d^2\text{E}v^2$$

则 $A_2=H+D^2-G,B_2=F+AD-E,C_2=C+A^2-B,D_2=C$，于是我们就做完了，$\sum d\text{E}v^2$ 之类的项直接用 $\frac{F_2(r_i)-F_2(l_i-1)}{r_i-l_i+1}$ 计算即可，其中 $F_2$ 是自然数平方和函数，表示 $\sum\limits_{i=1}^n i^2$。

总结：这是一道不可多得的锻炼代数变形技巧和期望性质运用的好题，

代码如下：

```cpp

#include<cstdio>
#include<algorithm>
const int N=5e5+7,mod=998244353,HF=(mod+1)/2,IV6=(mod+1)/6;
typedef long long ll;const ll Mod=mod;
struct MI
{
	int vl;MI():vl(0){}
	explicit MI(int z):vl(z){}
};
inline int _add(int x,int y){return x+y>=mod?x+y-mod:x+y;}
inline int _sub(int x,int y){return x>=y?x-y:x-y+mod;}
inline void _radd(int&x,int y){x+y>=mod?x+=y-mod:x+=y;}
inline void _rsub(int&x,int y){x>=y?x-=y:x-=y-mod;}
ll qpow(ll x,int y){ll r=1;for(;y;x=x*x%Mod,y>>=1)if(y&1)r=r*x%Mod;return r;}
inline MI operator+(MI x,MI y){return (MI)_add(x.vl,y.vl);}
inline MI operator-(MI x,MI y){return (MI)_sub(x.vl,y.vl);}
inline MI operator-(MI x){return (MI)_sub(0,x.vl);}
inline MI operator*(MI x,MI y){return (MI)((ll)x.vl*y.vl%Mod);}
inline void operator+=(MI&x,MI y){_radd(x.vl,y.vl);}
inline void operator-=(MI&x,MI y){_rsub(x.vl,y.vl);}
inline void operator*=(MI&x,MI y){x.vl=(ll)x.vl*y.vl%Mod;}
inline MI inv(MI x){return (MI)qpow(x.vl,mod-2);}
struct pii{MI x,y,z;};
inline pii operator*(pii a,MI n){return (pii){a.x*n,a.y*n,a.z*n};}
inline pii operator*(pii a,pii b){return (pii){a.x*b.x,a.x*b.y+a.y*b.x,a.y*b.y};}
MI d[N],Ls[N],Rs[N];
inline MI FS(MI x){return x*(x+MI(1))*MI(HF);}
inline MI FS2(MI x){return x*(x+MI(1))*(x+x+MI(1))*MI(IV6);}
int main()
{
	int n;scanf("%d",&n);
	MI ns=(MI)n,P,Q,aa,bb,cc,dd;
	MI A2v,B2v,C2v,D2v,A2c,B2c,C2c,D2c;
	
	MI A,B,C,D,E,F,G,H;
	for(int i=1;i<=n;++i)
	{
		scanf("%d%d%d",&d[i].vl,&Ls[i].vl,&Rs[i].vl);Ls[i]-=MI(1);
		
		P+=d[i]*d[i];Q+=d[i];
		
		MI vsm=FS(Rs[i])-FS(Ls[i]),vvsm=FS2(Rs[i])-FS2(Ls[i]),ivp=inv(MI(Rs[i]-Ls[i]));
		vsm*=ivp;vvsm*=ivp;
		
		A+=vsm;B+=vsm*vsm;C+=vvsm;
		D+=d[i]*vsm;E+=d[i]*vsm*vsm;F+=d[i]*vvsm;
		G+=d[i]*d[i]*vsm*vsm;H+=d[i]*d[i]*vvsm;
	}
	
	A2v=H+D*D-G;
	B2v=F+A*D-E;
	C2v=C+A*A-B;
	D2v=C;
	
	MI ivsab=inv(ns*P-Q*Q);
	aa=ns*ivsab;bb=cc=-Q*ivsab;dd=P*ivsab;
	pii X{cc,aa},Y{dd,bb},tmp;
	
	tmp=X*X;A2c+=tmp.z*P+tmp.y*Q+tmp.x*ns;
	tmp=X*Y*MI(2);B2c+=tmp.z*P+tmp.y*Q+tmp.x*ns;
	tmp=Y*Y;C2c+=tmp.z*P+tmp.y*Q+tmp.x*ns;
	tmp=X*-MI(2);A2c+=tmp.y;B2c+=tmp.x;
	tmp=Y*-MI(2);B2c+=tmp.y;C2c+=tmp.x;
	D2c=MI(1);
	
	
	MI ret=A2v*A2c+B2v*B2c+C2v*C2c+D2v*D2c;
	printf("%d",ret.vl);
	return 0;
}
```

---

