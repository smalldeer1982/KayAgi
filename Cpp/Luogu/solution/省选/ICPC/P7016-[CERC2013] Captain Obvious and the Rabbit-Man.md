# [CERC2013] Captain Obvious and the Rabbit-Man

## 题目描述

“是你，显而易见船长！”邪恶的兔子人喊道，“你来这里是为了阻止我的邪恶计划！”

“是的，是我。”显而易见船长说道。

“但是……你怎么知道我会在向日葵街 625 号？！你破解了我的邪恶代码吗？”

“我破解了。三天前，你抢劫了向日葵街 5 号的银行，第二天你炸毁了向日葵街 25 号，昨天你在 125 号制造了一场混乱。这些都是 5 的幂。而去年你用 13 的幂做了类似的事情。你似乎对斐波那契数有一种天赋，兔子人。”

“这还没完！我会学习……算术！”兔子人被拖入拘留时尖叫道，“你永远不知道会发生什么……哎哟！别碰我的耳朵，你们这些笨蛋！”

“也许吧，但现在你被捕了。”船长自豪地补充道。

不幸的是，兔子人现在确实学会了一些更高级的算术。为了理解它，让我们定义序列 $F_n$（与斐波那契序列不完全相似）：

$F_{1} = 1$，

$F_{2} = 2$，

$F_{n} = F_{n-1} + F_{n-2}$ 对于 $n \ge 3$。

兔子人将他所有以前的邪恶想法结合成一个总计划。在第 $i$ 天，他在编号为 $p(i)$ 的地方进行恶意行为，定义如下：

$p(i) = a_{1}\cdot F_{1}^{i} + a_{2}\cdot F_{2}^{i} + \cdots + a_{k}\cdot F_{k}^{i}$。

数字 $k$ 和整数系数 $a_1 , \cdots , a_k$ 是固定的。显而易见船长知道 $k$，但不知道系数。给定 $p(1), p(2), \cdots, p(k)$，帮助他确定 $p(k + 1)$。为了避免过大的数字，所有计算都在一个固定的素数 $M$ 模下进行。你可以假设 $F_1, F_2, \cdots, F_n$ 在模 $M$ 下是两两不同的。你也可以假设给定的输入总是存在唯一解。

## 说明/提示

时间限制：6 秒，内存限制：128 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
2
4 619
5 25 125 6
3 101
5 11 29
```

### 输出

```
30
83
```

# 题解

## 作者：岸芷汀兰 (赞：9)

# 一、题目：

[洛谷原题](https://www.luogu.com.cn/problem/P7016)

[codeforces原题](https://codeforces.com/gym/100299)

# 二、题目：

这道题的官方题解秀了我一脸。

设多项式
$$
\begin{aligned}
A(x)&=(x-1)(x-2)(x-3)(x-5)\cdots(x-F_k)\\
	&=x^k+b_1x^{k-1}+b_2x^{k-2}+\cdots+b_{k-1}x+b_k
\end{aligned}
$$
注意到
$$
\begin{aligned}
A(1)=1^k+b_1\times1^{k-1}+b_2\times1^{k-2}+\cdots+b_k=0\\
A(2)=2^k+b_1\times2^{k-1}+b_2\times2^{k-2}+\cdots+b_k=0\\
A(3)=3^k+b_1\times 3^{k-1}+b_2\times 3^{k-2}+\cdots +b_k=0\\
A(5)=5^k+b_1\times 5^{k-1}+b_2\times 5^{k-2}+\cdots +b_k=0\\

\end{aligned}
$$
即
$$
\forall i\in[1,k],A(F_i)=F_i^k+b_1F_i^{k-1}+b_2F_i^{k-2}+\cdots+b_k=0
$$
等式两边同时乘以 $a_iF_i$，得
$$
a_iF_iA(F_i)=a_iF_i^{k+1}+b_1a_iF_i^{k}+b_2a_iF_i^{k-1}+\cdots+b_ka_iF_i=0
$$
累加，得
$$
\sum\limits_{i=1}^kF_ia_iA(F_i)=\sum\limits_{i=1}^{k}a_iF_i^{k+1}+b_1\sum\limits_{i=1}^ka_iF_i^{k}+\cdots+b_k\sum\limits_{i=1}^ka_iF_i=0
$$
即
$$
p(k+1)+b_1p(k)+b_2p(k-1)+\cdots+b_kp(1)=0
$$
这题结束了，时间复杂度就是求出 $A(x)$ 的系数 $b$ 的时间复杂度，即 $O(k^2)$。

# 三、代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
#define FILEIN(s) freopen(s, "r", stdin)
#define FILEOUT(s) freopen(s, "w", stdout)
#define mem(s, v) memset(s, v, sizeof s)

inline int read(void) {
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
    return f * x;
}

const int MAXK = 4005;

int MOD, K;
long long f[MAXK];

struct Polynomial {
    int n;
    long long a[MAXK];
    Polynomial() { n = 0; mem(a, 0); }
    inline friend Polynomial operator *(const Polynomial &A, const Polynomial &B) {
        Polynomial res; res.n = A.n + B.n;
        for (int i = 0; i <= A.n; ++ i)
            for (int j = 0; j <= B.n; ++ j)
                (res.a[i + j] += A.a[i] * B.a[j] % MOD) %= MOD;

        return res;
    }
};

inline void prework(void) {
    f[1] = 1; f[2] = 2;
    for (int i = 3; i <= K; ++ i) f[i] = (f[i - 1] + f[i - 2]) % MOD;
}

int main() {
    int T = read();
    while (T --) {
        K = read(); MOD = read();
        prework();
        Polynomial res; res.n = 0; res.a[0] = 1;
        for (int i = 1; i <= K; ++ i) {
            Polynomial now; now.n = 1; now.a[0] = -f[i]; now.a[1] = 1;
            res = res * now;
        }
        long long ans = 0;
        for (int i = 1; i <= K; ++ i) {
            long long p = read();
            (ans += p * res.a[i - 1] % MOD) %= MOD;
        }
        ans = -ans;
        if (ans < 0) ans += MOD;
        printf("%lld\n", ans);
    }
    return 0;
}
```



---

## 作者：ix35 (赞：2)

代码写得丑，在 CF 上过不去，我懒得改了。

---

从线代角度描述问题：

$$\begin{bmatrix}F_1^1\ F_2^1\ \cdots\ F_k^1 \\ F_1^2\ F_2^2\ \cdots\ F_k^2\\ F_1^3\ F_2^3\ \cdots\ F_k^3 \\ \vdots \quad \vdots \quad \vdots \quad \vdots \end{bmatrix} \times \begin{bmatrix}a_1 \\ a_2\\ \vdots \\ a_k \end{bmatrix}=\begin{bmatrix}p_1 \\ p_2\\ p_3 \\ \vdots \end{bmatrix}$$

此时由于我们已知 $p_1,\ldots,p_k$，欲求 $p_{k+1}$，不妨直接解出 $a_1,\ldots,a_k$，就可以直接算出 $p_{k+1}$ 了。

所以我们只取矩阵的前 $k$ 行，那么我们只需要对左边那个方阵求逆，就可以通过右边算左边了。

而左边是个缺一行的范德蒙德矩阵，我们只需要进行范德蒙德矩阵的求逆即可。

https://ccjou.wordpress.com/2012/06/13/vandermonde-%E7%9F%A9%E9%99%A3%E7%9A%84%E9%80%86%E7%9F%A9%E9%99%A3%E5%85%AC%E5%BC%8F/

上面的链接给出了范德蒙德逆矩阵的公式：

$$V^{-1}_{i,j}=(-1)^{j+1}\times \Big(\sum\limits_{1\leq p_1<\ldots<p_{n-j}\leq n,p_k\ne i}\prod F_{p_k}\Big)/\Big(\prod\limits_{k\ne i} (F_k-F_i)\Big)$$

上面是用伴随矩阵和基本对称函数推的，这里不详细写一遍了。

事实上，DFT 和 IDFT 之间的关系也与这个结论有关。

回到这题，上面的分子和分母都可以通过 DP 递推求出，我们直接求完逆之后乘上右边的列向量就得到了所有 $a_i$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=4010;
int t,n,m,ans,f[MAXN],w[MAXN],v[MAXN][MAXN],lh[MAXN][MAXN],zlh[MAXN],a[MAXN];
int qpow (int a,int b,int p) {
	int res=1;
	while (b) {
		if (b&1) {res=(1ll*res*a)%p;}
		a=(1ll*a*a)%p,b>>=1;
	}
	return res;
}
int main () {
	scanf("%d",&t);
	for (int ii=1;ii<=t;ii++) {
		scanf("%d%d",&n,&m);
		for (int j=1;j<=n;j++) {scanf("%d",&w[j]);}
		f[1]=1,f[2]=2;
		for (int i=3;i<=n;i++) {f[i]=(f[i-1]+f[i-2])%m;}
		v[0][0]=1;
		for (int i=1;i<=n;i++) {
			v[i][0]=1;
			for (int j=1;j<=i;j++) {
				v[i][j]=(v[i-1][j]+(1ll*v[i-1][j-1]*f[i])%m)%m;
			}
			v[i][i+1]=0;
		}
		for (int i=0;i<=n;i++) {zlh[i]=v[n][i];}
		for (int i=1;i<=n;i++) {
			lh[i][0]=1;
			for (int j=1;j<=n;j++) {lh[i][j]=(zlh[j]-(1ll*lh[i][j-1]*f[i])%m+m)%m;}
		}
		for (int i=1;i<=n;i++) {
			int prod=1;
			for (int j=1;j<=n;j++) {
				if (j==i) {continue;}
				prod=(1ll*prod*(f[j]-f[i]+m))%m;
			}
			prod=qpow(prod,m-2,m);
			//cout << i << "  " << prod << endl;
			for (int j=1;j<=n;j++) {
				v[i][j]=(1ll*prod*lh[i][n-j])%m;
				if (j%2==0) {v[i][j]=(m-v[i][j])%m;}
				//cout << i << "  " << j << "    " << lh[i][j] << "  " << v[i][j] << endl;
			}
		}
		ans=0;
		for (int i=1;i<=n;i++) {
			a[i]=0;
			for (int j=1;j<=n;j++) {a[i]=(a[i]+(1ll*w[j]*v[i][j])%m)%m;}
			ans=(ans+(1ll*a[i]*qpow(f[i],n,m))%m)%m;
		}
		printf("%d\n",ans);
	}
	return 0;
}

```


---

## 作者：Yansuan_HCl (赞：0)

题目以 $p(n)=\sum a_iF_i^k$ 的形式给出 $p$，这是特征根方程的形式，$F_{1..k}$ 为数列 $p$ 的特征根。考虑根据递推式列出特征根方程的形式，特征根为该方程的根。于是 $\prod (X-F_i)$ 表示了这一方程，展开后将最高次项移项后可以还原出递推式的系数，从而可以递推。

```cpp
const int N = 4005;
int n; ll P; ll x[N];

struct Poly { vector<ll> v; };
Poly operator * (Poly l, Poly r) {
	Poly t; t.v.resize(l.v.size() + r.v.size());
	U (i, 0, l.v.size() - 1) U (j, 0, r.v.size() - 1)
		(t.v[i + j] += l.v[i] * r.v[j]) %= P;
	return t;
}

int main() {
	int T; rd(T);
	while (T--) {
		rd(n, P);
		x[1] = 1, x[2] = 2;
		U (i, 3, n)
			x[i] = (x[i - 1] + x[i - 2]) % P;
		Poly p; p.v.push_back(1);
		U (i, 1, n) {
			Poly q; q.v.push_back(P - x[i]); q.v.push_back(1);
			p = p * q;
		}
		ll g = 0;
		U (i, 1, n) {
			ll a; rd(a);
			(g += (P - p.v[i - 1]) * a) %= P;
		}
		cout << g << endl;
	}
}
```

---

