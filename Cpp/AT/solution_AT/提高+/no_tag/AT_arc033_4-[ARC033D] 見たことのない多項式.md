# [ARC033D] 見たことのない多項式

## 题目描述

高桥君有一个未知的 $N$ 次多项式 $P(x)$，只知道 $P(x)$在$x=0,1,2,3\cdots N$ 时的值。高桥君希望知道当 $x=T$ 时，多项式的值。结果对 $10^9+7$ 取模。

## 说明/提示

对于 $40 \%$ 的数据，满足 $N \leq 100$。

对于 $80 \%$ 的数据，满足 $N \leq 3000$。

对于全部 $100 \%$ 的数据，$1 \leq N \leq 10^5$, $0 \leq A_i \leq 10^9+6$, $T \leq 10^9$。

## 样例 #1

### 输入

```
2
1 3 7
3```

### 输出

```
13```

## 样例 #2

### 输入

```
5
4 16 106 484 1624 4384
1000000000```

### 输出

```
999984471```

# 题解

## 作者：whx1003 (赞：8)

这题数据其实可以加强到 $5\times10^6$ 甚至 $10^7$……

考虑使用牛顿级数将 $P(x)$ 展开：

$$
\begin{aligned}
P(x)= & \sum_{k\leq n}c_k\binom xk=\sum_{k\leq n}\binom xk\sum_{t}(-1)^{k-t}\binom kt P(t)\\
= & \sum_{t\leq n}P(t)\sum_{t\leq k\leq n}\binom xk(-1)^{k-t}\binom kt\\
 = & \sum_{t\leq n}P(t)\binom xt\sum_{t\leq k\leq n}\binom {x-t}{k-t}(-1)^{k-t}
\end{aligned}
$$

使用交错和：
$$
\begin{aligned}
= & \sum_{t\leq n}P(t)\binom xt\sum_{k\leq n-t}\binom{x-t}k(-1)^k\\
= & \sum_{t\leq n}P(t)\binom xt\binom{n-x}{n-t}\\
\end{aligned}
$$

然后使用上指标反转：
$$
\begin{aligned}
= & \sum_{t\leq n}P(t)\binom xt\binom{x-t-1}{n-t}(-1)^{n-t}\\
\end{aligned}
$$

拆成下降幂形式：
$$
\begin{aligned}
= & \sum_{t\leq n}(-1)^{n-t}P(t)\frac{x^{\underline{n+1}}}{t!(n-t)!(x-t)}
\end{aligned}
$$
这个东西是可以 $\mathcal{O}(n)$ 预处理一个前缀积和后缀积来做的。

```cpp
#include<cstdio>

typedef long long ll;
const int maxn = 1E+5 + 5;
const ll mod = 1E+9 + 7;

int n;
ll p[maxn], x;
ll pre[maxn], suf[maxn];
ll Fac[maxn], Inv[maxn];

inline ll sig(int x) { return x & 1 ? -1 : 1; }
ll fsp(ll a, ll b, ll mod = mod, ll res = 1) {
	for(a %= mod; b; a = a * a % mod, b >>= 1)
		(b & 1) && (res = res * a % mod);
	return res;
}

int main() {
	scanf("%d", &n);
	for(int i = 0; i <= n; ++i)
		scanf("%lld", &p[i]);
	scanf("%lld", &x);

	if(x <= n) return printf("%lld", p[x]), 0;
	
	Fac[0] = 1;
	for(int i = 1; i <= n; ++i)
		Fac[i] = Fac[i - 1] * i % mod;
	Inv[n] = fsp(Fac[n], mod - 2);
	for(int i = n; i >= 1; --i)
		Inv[i - 1] = Inv[i] * i % mod;
	
	pre[0] = 1, suf[n] = 1;
	for(int i = 1; i <= n; ++i) {
		pre[i] = pre[i - 1] * (x - i + 1) % mod;
		suf[n - i] = suf[n - i + 1] * (x - n + i - 1) % mod;
	}
	
	ll ans = 0;
	for(int i = 0; i <= n; ++i)
		(ans += Inv[i] * Inv[n - i] % mod * pre[i] % mod * suf[i] % mod * sig(n - i) * p[i]) %= mod;
	printf("%lld\n", (ans + mod) % mod);
}
```

---

## 作者：皎月半洒花 (赞：3)

题意大概就是给出连续的一段$x_0$和$y_0$，算出多项式$F(x)$在一个特定值$x_0'$时的值。

我们注意到$40 \%$的数据可以直接高消，列出$n+1$个方程。

同时，我们还可以用朴素的拉格朗日插值法插出$80pts$的好成绩。

而对于$100 \%$的数据，$n$是$1e5$级别的，所以考虑预处理出一些东西。

我们观察拉格朗日插值公式的一般形式：$$F(x) = \sum \limits _{i=0}^{N} y_i \cdot \prod \limits_{i \neq j} \frac{x -x_j}{x_i-x_j}$$

我们发现首先分子可以$O(n)$预处理，而分母由于$x_j$是连续的，所以$\rm{\prod \limits _{i \neq j} x_i  - x_j}= fac(i) \cdot fac(N-i) \cdot evenmark(N-i)$，其中$fac$表示求阶乘，$\rm{evenmark}$是符号函数，当$N-i$是偶数时返回$1$，否则返回$-1$。

于是我们就可以得出一个式子：

$$F(x) = \sum \limits_{i=0}^{N}{y_i \cdot}\frac{\frac{Pre}{x-i}}{fac(i) \cdot fac(N-i) \cdot evenmark(N-i)}$$其中$\frac{Pre}{x-i}$的缘由可以参考我的代码。

取模啥的就小费马搞一搞即可，最终复杂度$\Theta(n \log n)$

```cpp
inline LL expow(LL A, LL B){
	LL res = 1 ;
	while (B){
		if (B & 1) (res *= A) %= Mod ; 
		B >>= 1, (A *= A) %= Mod ;
	}
	return res % Mod ;
}
inline LL get_symbol(LL x){ return (!x ? 1 : Mod - 1) ; }
int main(){
	cin >> N ; Fac[0] = qwq = 1 ;
	for (i = 0 ; i <= N ; ++ i)
		scanf("%lld", &base[i]), (Fac[i + 1] = Fac[i] * (i + 1)) %= Mod ;
	cin >> T ; Ans = 0 ;
	if (T <= N) return printf("%lld\n", base[T]) ;
	for (i = 0 ; i <= N ; ++ i) (qwq *= (T - i + Mod)) %= Mod ;
	for (i = 0 ; i <= N ; ++ i){
		M = (N - i) & 1, _qwq = qwq * expow((T - i), Mod - 2) % Mod ;
		t = expow(Fac[i] * Fac[N - i] % Mod, Mod - 2) % Mod ; 
		t = t * (get_symbol(M) * _qwq % Mod) % Mod, t = (t * base[i]) % Mod ;
		(Ans += t)  %= Mod ;
//		cout << Ans << endl ;
	}
	printf("%lld\n", Ans) ; return 0 ;
}
```

---

