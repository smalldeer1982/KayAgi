# [ABC295E] Kth Number

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc295/tasks/abc295_e

$ 0 $ 以上 $ M $ 以下の整数からなる長さ $ N $ の数列 $ A=(A_1,A_2,\dots,A_N) $ があります。

今からすぬけくんが以下の操作 1, 2 を順に行います。

1. $ A_i=0 $ を満たすそれぞれの $ i $ について、$ 1 $ 以上 $ M $ 以下の整数を独立かつ一様ランダムに選び、$ A_i $ をその整数で置き換える。
2. $ A $ を昇順に並び替える。
 
すぬけくんが操作 1, 2 を行ったあとの $ A_K $ の期待値を $ \text{mod\ }\ 998244353 $ で出力してください。

  「期待値を $ \text{mod\ }\ 998244353 $ で出力」とは 求める期待値は必ず有理数となることが証明できます。 またこの問題の制約下では、その値を互いに素な $ 2 $ つの整数 $ P $, $ Q $ を用いて $ \frac{P}{Q} $ と表したとき、 $ R\ \times\ Q\ \equiv\ P\pmod{998244353} $ かつ $ 0\ \leq\ R\ \lt\ 998244353 $ を満たす整数 $ R $ がただ $ 1 $ つ存在することが証明できます。この $ R $ を出力してください。

## 说明/提示

### 制約

- $ 1\leq\ K\ \leq\ N\ \leq\ 2000 $
- $ 1\leq\ M\ \leq\ 2000 $
- $ 0\leq\ A_i\ \leq\ M $
- 入力は全て整数
 
### Sample Explanation 1

すぬけくんは操作 1 において $ A_2 $ を $ 1 $ 以上 $ 5 $ 以下の整数で置き換えます。この整数を $ x $ とすると、 - $ x=1,2 $ のとき、すぬけくんが操作 1, 2 を行ったあと $ A_2=2 $ です。 - $ x=3 $ のとき、すぬけくんが操作 1, 2 を行ったあと $ A_2=3 $ です。 - $ x=4,5 $ のとき、すぬけくんが操作 1, 2 を行ったあと $ A_2=4 $ です。 よって、$ A_2 $ の期待値は $ \frac{2+2+3+4+4}{5}=3 $ です。

### Sample Explanation 2

期待値は $ \frac{14}{9} $ です。

## 样例 #1

### 输入

```
3 5 2
2 0 4```

### 输出

```
3```

## 样例 #2

### 输入

```
2 3 1
0 0```

### 输出

```
221832080```

## 样例 #3

### 输入

```
10 20 7
6 5 0 2 0 0 0 15 0 0```

### 输出

```
617586310```

# 题解

## 作者：BigJoker (赞：10)

概率。

假设第 $k$ 大的数为 $X$，并且 $X\in[1,m]$，根据求随机变量的公式就是。

$X=\sum_{i=1}^{m}i\times P(X=i)$

这个很基本，我们需要推导一下。

$\begin{aligned}X&=\sum_{i=1}^{m}i\times P(X=i)\\&=\sum_{i=1}^{m} \sum_{j=1}^{i}P(X=i)\\&=\sum_{i=1}^{m}\sum_{j=i}^{m}P(X=j)\\&=\sum_{i=1}^{m}P(X\ge i)\end{aligned}$

发现其实算 $\ge i$ 的概率其实是很好算的。

首先枚举 $i\in[1,m]$，然后由于 $i$ 是第 $k$ 大，所以至少有 $n-k+1\ge i$，记作 $q$，确定 $a$ 中有多少个已经确定的数 $\ge i$，记作 $s$。

如果 $s\ge q$，那么证明 $P(x\ge i)=1$，答案加上 $1$ 即可；否则至少需要 $q-s$ 个 $a_i=0$ 的位置上的数来填充，那么枚举 $j\in[q-s,z]$，$z$ 表示 $a_i=0$ 的总数量。表示选择 $j$ 个数填充 $\ge i$ 的，那么它的概率可以表示为。

$$\binom{z}{j}\times \frac{(m-i+1)^j}{m^j}\times \frac{(i-1)^{z-j}}{m^{z-j}}$$

将答案累加上述值即可。

所以最后的答案为，当然式子中有概率为 $1$ 的要特判一下：

$$\sum_{i=1}^{m}\sum_{j=q-s}^{z}\binom{z}{j}\times \frac{(m-i+1)^j}{m^j}\times \frac{(i-1)^{z-j}}{m^{z-j}}$$

---

## 作者：Register_int (赞：4)

首先有经典结论 $E[x]=\sum_iP(x\ge i)$。枚举 $i$，为了保证第 $k$ 小比 $i$ 大，数列中必须要有 $n-k+1$ 个数 $\ge i$。先扣减掉数列中原先就 $\ge i$ 的数，再从 $0$ 中选即可得到答案。设还需要 $x$ 个数，共有 $y$ 个 $0$，先特判 $0$ 不够与不需要再选的情况，就可以计算出答案为：

$$\sum^y_{j=x}\binom yj\left(\dfrac{m-i+1}m\right)^j\left(\dfrac{i-1}m\right)^{y-j}$$

另外提醒下和我一样用递推的人，$i=1$ 时 $i-1$ 没有逆元。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e3 + 10;
const int mod = 998244353;

inline 
ll qpow(ll b, ll p) {
	ll res = 1;
	while (p) {
		if (p & 1) res = res * b % mod;
		b = b * b % mod, p >>= 1;
	}
	return res;
}

ll c[MAXN][MAXN];

inline 
void init(int n) {
	for (int i = 0; i <= n; i++) c[i][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
	}
}

int n, m, k, a[MAXN];

ll ans = 1, t, p, iq;

int main() {
	scanf("%d%d%d", &n, &m, &k), init(n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 2, x, y; i <= m; i++) {
		x = n - k + 1, y = 0;
		for (int j = 1; j <= n; j++) x -= a[j] >= i, y += !a[j];
		if (x > y || x < 0) { ans += x < 0; continue; }
		p = (m - i + 1) * qpow(m, mod - 2) % mod, iq = mod + 1 - p;
		t = qpow(p, x) * qpow(iq, y - x) % mod, iq = qpow(iq, mod - 2);
		for (int j = x; j <= y; j++) ans = (ans + c[y][j] * t % mod) % mod, t = t * p % mod * iq % mod;
	}
	printf("%lld", ans);
}
```

---

## 作者：K8He (赞：1)

# [[ABC295E] Kth Number](https://www.luogu.com.cn/problem/AT_abc295_e)

首先我们有经典结论：

$$
E(A_k) = \sum_{i = 1}^{m} i\times P(A_k = i) = \sum_{i = 1}^{m} P(A_k  \ge i)
$$

枚举到 $i$ 时，为了满足 $i$ 至少是第 $k$ 大，前面至少要有 $n - k + 1$ 个数垫着。但是还有一些数本来就大于等于 $i$，那么设 $l$ 为 $n - k + 1$ 减去原数组中大于等于 $i$ 的数的个数（也就是需要的 $0$ 的个数），$r$ 为原数组中 $0$ 的个数，则：

$$
P(A_k\ge i) = \sum_{j = l}^{r}\dbinom{r}{j}(\frac{m - i + 1}{m})^{j}(\frac{i - 1}{m})^{r - j} = \frac{1}{m ^ r}\sum_{j = l}^{r}\dbinom{r}{j}({m - i + 1})^{j}({i - 1})^{r - j}
$$

注意到 $l$ 可能为负数，此时应从 $0$ 开始枚举，不过这时式子可以直接二项式定理化为 $m^r$。

Code：

```cpp
const ll N = 2010, P = 998244353;
namespace SOLVE {
	ll n, m, k, im, c0, a[N], c[N][N], ans;
	inline ll rnt () {
		ll x = 0, w = 1; char c = getchar ();
		while (!isdigit (c)) { if (c == '-') w = -1; c = getchar (); }
		while (isdigit (c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getchar ();
		return x * w;
	}
	inline ll FastPow (ll a, ll b) {
		ll ans = 1;
		while (b) {
			if (b & 1) ans = ans * a % P;
			a = a * a % P, b >>= 1;
		}
		return ans;
	}
	inline void In () {
		n = rnt (), m = rnt (), k = rnt ();
		_for (i, 1, n) a[i] = rnt (), c0 += !a[i];
		im = FastPow (FastPow (m, P - 2), c0);
		return;
	}
	inline void Solve () {
		_for (i, 0, std::max (n, m)) {
			c[i][0] = 1;
			_for (j, 1, i) c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % P;
		}
		_for (i, 1, m) {
			ll cnt = 0;
			_for (j, 1, n) if (a[j] && a[j] >= i) ++cnt;
			if (n - k + 1 - cnt > c0) continue;
			if (n - k + 1 - cnt < 0) { ans = (ans + FastPow (m, c0)) % P; continue;}
			_for (j, n - k + 1 - cnt, c0) {
				ll pre = FastPow (m - i + 1, j);
				ll suf = FastPow (i - 1, c0 - j);
				ans = (ans + c[c0][j] * pre % P * suf % P) % P;
			}
		}
		return;
	}
	inline void Out () {
		printf ("%lld\n", ans % P * im % P);
		return;
	}
}
```

---

## 作者：Alarm5854 (赞：1)

题意：给一个有若干个未知元素的序列，求第 $k$ 小值的期望。

首先先对第 $k$ 小值的期望进行转换，则有：

$$
E(A_k)=\sum_{i=1}^m i\times P(A_k=i)=\sum_{i=1}^m P(A_k\ge i)
$$

第一个等式是易证的，而第二个等式其实就是相当于一个方格纸，在第 $b_j$ 列的前 $i$ 行染上了颜色，这是横向看的结果。而如果换个方向看，那么会发现你在第 $i$ 行第 $j$ 列的格子被染色当且仅当 $b_j\ge i$，否则不会被染色，得证。

有了这个转换，事情就好做了。枚举 $A_k$ 的最小可能取值 $i$，然后考虑 $0$ 的个数，记为 $t$，原序列中大于等于 $i$ 的数量为 $s$，那么先特判 $s+t\le n-k$，此时一定没有任何贡献；特判 $s>n-k$，此时不管这些 $0$ 填什么都有一定的贡献，为 $m^t$。然后，枚举有 $j$ 个 $0$ 变成了不小于 $i$ 的数，那么贡献为 $(m-i+1)^j\times (i-1)^{t-j}\times \binom{t}{j}$，其中乘上组合数是因为有多种位置可以选择，最后再除以 $m^t$ 即为答案。

预处理幂次方可以将时间复杂度降至 $O(n^2)$，假设 $n,m$ 同阶。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e3+7;
const int HgS=998244353;
void add(int& x,int y){
	x+=y;
	if(x>=HgS)
		x-=HgS;
}
int qpow(int a,int b){
	int res=1;
	while(b){
		if(b&1)
			res=1ll*res*a%HgS;
		a=1ll*a*a%HgS;
		b>>=1;
	}
	return res;
}
int n,m,k,x,mx,res,cur,c[N],p[N][N],C[N][N];
int main(){
	scanf("%d%d%d",&n,&m,&k);
	mx=max(n,m);
	for(int i=1;i<=n;++i){
		scanf("%d",&x);
		++c[x];
	}
	C[0][0]=1;
	for(int i=1;i<=mx;++i){//处理组合数
		C[i][0]=1;
		for(int j=1;j<=i;++j){
			C[i][j]=C[i-1][j];
			add(C[i][j],C[i-1][j-1]);
		}
	}
	p[0][0]=1;
	for(int i=1;i<=mx;++i){//处理幂次方
		p[i][0]=1;
		for(int j=1;j<=mx;++j)
			p[i][j]=1ll*p[i][j-1]*i%HgS;
	}
	for(int i=m;i;--i){
		cur+=c[i];
		if(cur+c[0]<=n-k)//贡献为零
			continue;
		if(cur>n-k)//所有情况都有贡献
			add(res,p[m][c[0]]);
		else{
			for(int j=1;j<=c[0];++j){
				if(cur+j<=n-k)
					continue;
				add(res,1ll*p[m-i+1][j]*p[i-1][c[0]-j]%HgS*C[c[0]][j]%HgS);
			}
		}
	}
	res=1ll*res*qpow(p[m][c[0]],HgS-2)%HgS;
	printf("%d\n",res);
	return 0;
}
```

---

