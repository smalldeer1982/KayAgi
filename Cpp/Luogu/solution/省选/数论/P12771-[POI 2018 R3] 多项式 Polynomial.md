# [POI 2018 R3] 多项式 Polynomial

## 题目背景

翻译来自于 [LibreOJ](https://loj.ac/p/5079)。

## 题目描述

**题目译自 [XXV Olimpiada Informatyczna — III etap](https://sio2.mimuw.edu.pl/c/oi25-3/dashboard/) [Wielomian](https://szkopul.edu.pl/problemset/problem/9JvSAnyf5d1FlPAEXEdUAtCz/statement/)**

Bajtazar 在数学课上行为不端，作为惩罚，他需计算一个具有 $n$ 个整数系数的长多项式 $W$：

$$
W(x) = a_0 + a_1 x + a_2 x^2 + \ldots + a_{n-2} x^{n-2} + a_{n-1} x^{n-1}
$$

在点 $q^1, q^2, \ldots, q^n$ 处的取值。为便于老师检查，他需先给出这些取值之和除以 $m$ 的余数，再给出各取值除以 $m$ 的余数。

Bajtazar 不仅调皮，还很懒惰，他请你帮忙，自己却跑去派对了。临走前，他提醒你：$n$ 是 $2$ 的幂，且 $q^n$ 除以 $m$ 的余数为 $1$（即 $q^n \bmod m = 1$）。他认为这些性质可大幅减少计算量。

## 说明/提示

**样例 1 解释**

多项式为 $W(x) = 3 + 2x + 2x^2 + x^3$，其在各点取值为 $W(5) = 188$，$W(5^2) = 16928$，$W(5^3) = 1984628$，$W(5^4) = 244923128$。第一行输出 $188 + 16928 + 1984628 + 244923128 = 246924872$ 除以 $13$ 的余数，即 $12$。第二行输出各取值除以 $13$ 的余数：$188 \bmod 13 = 6$，$16928 \bmod 13 = 2$，$1984628 \bmod 13 = 9$，$244923128 \bmod 13 = 8$。

**附加样例**

1. $n=8, m=10, q=3$。
2. $n=256, m=10, q=9$。
3. $n=2^{13}, m=17, q=6$。
4. $n=2^{20}, m=1114129, q=2$。

若和正确但某取值错误，程序可获得 $40\%$ 的分数，且第二行需输出 $n$ 个 $[0, m-1]$ 范围的数。

详细子任务附加限制及分值如下表所示。

| 子任务 | 附加限制 | 分值 |
| :---: | :--: | :---: |
| $1$    | $n \leq 2^{10}$          | $17$ |
| $2$    | $n \leq 2^{15}$          | $9$  |
| $3$    | $n \leq 2^{20}$          | $74$ |

## 样例 #1

### 输入

```
4 13 5
3 2 2 1```

### 输出

```
12
6 2 9 8```

# 题解

## 作者：Associate_Entropy (赞：3)

给定一个 $n$ 项多项式，$n$ 是 $2$ 的幂次，给定 $q$ 和模数 $m$，求该多项式在点 $q^1, q^2, \ldots, q^n$ 处的取值。特别的，$q^n\equiv 1\pmod m$。

## 分析
第一眼看到题目，首先想到任意模数的 [Chirp Z-Transform](https://www.luogu.com.cn/problem/P6828)，但是发现模数太任意了，可以很小，导致组合数没有逆元，遂放弃。

接着我们考虑能否利用 $q^n\equiv 1\pmod m$ 这个类似单位根的性质，需要注意的是，可能是 $q^d\equiv 1\pmod m$ 而 $d \mid n$，这时答案每 $d$ 个为一循环，我们也是每 $d$ 项算一次 $n$ 个点值并累加，然后循环 $n/d$ 次输出，即如下代码段：

```cpp
pw[0]=1;
for(int i=1;i<=n;i++)pw[i]=1ll*pw[i-1]*q%m;
for(d=1;d<=n;d<<=1)if(pw[d]==1)break;
for(int i=0;i<n;i+=d){
    work(a+i);
    for(int j=1;j<=d;j++)add(ans[j],1ll*val[j]*kpow(pw[j],i)%m);
}
int ss=0;
for(int i=1;i<=d;i++)add(ss,1ll*ans[i]*(n/d)%m);
printf("%d\n",ss);
for(int i=0;i<n;i+=d)
    for(int j=1;j<=d;j++)printf("%d ",ans[j]);
```


问题可以转化为求 $q^0, q^1, \ldots, q^{d-1}$ 处在一个 $d$ 项多项式中的值。我们假设 $q$ 是 $m$ 的 $d$ 次单位根，看看会出现什么情况。

我们回想一下普通 [fft](https://www.luogu.com.cn/problem/P3803) 在干什么事情。要想快速实现系数向点值的转化，我们将当前多项式按奇偶项分开，如 $f(x)=\sum \limits_{i=0}^{15}a_ix^i$，令 $f_0(x)=\sum \limits_{i=0}^{7}a_{2i}x^{2i}$，$f_1(x)=\sum \limits_{i=0}^{7}a_{2i+1}x^{2i}$，则 $f(x)=f_0(x^2)+xf_1(x^2)$。我们希望代入的两个自变量的平方相同（互为相反数），这样他们的函数值只有 $x$ 这个位置是相反数，并且要方便递归。

单位根就有这样的优势，$\omega_n^k=\omega_{n/2}^{k/2}$，但更重要的是，$\omega_n^k+\omega_n^{k+n/2}=0$。

但是，$q^{d/2}$ 有没有可能不是 $-1$ 呢？这将导致 $q^k+q^{k+d/2} \not \equiv 0\pmod m$。我们可以在样例中找到这样的例子，$d=2$ 时 $71^2\equiv 1\pmod {80}$ 但 $71\not \equiv -1\pmod {80}$。

不过这样就做不了了吗？ 答案是否定的。因为我们意识到，在 $f(x)=f_0(x^2)+xf_1(x^2)$ 这一步中，最关键的是让两个自变量的平方相等，而 $xf_1(x^2)$ 不一定要是相反数。对于这道题来说，$q^{d/2}$ 是否是 $-1$ 其实根本不重要，只需要 $(q^{d/2})^2$ 为 $1$ 就能保证 $q^k$ 和 $q^{k+d/2}$ 两个数的平方相等。

于是这题就顺利地做完了。

## Code
变量名和写法有所调整。


```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0;char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
	return x;
}
const int N=1<<22;
int n,m,c,mod,g,a[N],pw[N],rev[N],ans[N];
void add(int &x,int y){x+=y;if(x>=mod)x-=mod;}
int kpow(int t1,int t2){
	int res=1;
	while(t2){
		if(t2&1)res=1ll*res*t1%mod;
		t1=1ll*t1*t1%mod;t2>>=1;
	}
	return res;
}
void ntt(int *f){
	int lg=__lg(n);
	for(int i=1;i<n;i++){
		rev[i]=(rev[i>>1]>>1)|((i&1)<<lg-1);
		if(i<rev[i])swap(f[i],f[rev[i]]);
	}
	for(int x=1,y=2;y<=n;x<<=1,y<<=1){
		int z=pw[n/y];//求y次单位根
		for(int i=0;i<n;i+=y)
			for(int w=1,j=i;j<i+x;j++,w=1ll*w*z%mod){
				int p=f[j],q=1ll*w*f[j+x]%mod;
				f[j]=p+q<mod? p+q:p+q-mod;
				add(f[j+x]=1ll*pw[n>>1]*q%mod,p);
			}
	}
}
int main(){
	m=read();mod=read();c=read();
	pw[0]=1;
	for(int i=1;i<=m;i++)pw[i]=1ll*pw[i-1]*c%mod;
	for(n=1;n<=m;n<<=1)if(pw[n]==1)break;
	for(int i=0;i<m;i++)a[i]=read()%mod;
	for(int i=0;i<m;i+=n){
		ntt(a+i);
		for(int j=0;j<n;j++)add(ans[j],1ll*a[j+i]*kpow(pw[j],i)%mod);
	}
	int ss=0;
	for(int i=0;i<n;i++)add(ss,1ll*ans[i]*(m/n)%mod);
	printf("%d\n",ss);
	for(int i=0;i<m;i+=n){
		for(int j=1;j<n;j++)printf("%d ",ans[j]);
		printf("%d ",ans[0]);
	}
}
```

---

## 作者：lzyqwq (赞：0)

> - 给出 $n-1$ 次多项式 $W(x)=\sum\limits_{i=0}^{n-1}a_ix^i$。给出 $q,m$，求 $W(q),\dots,W(q^m)$ 模 $m$ 意义下的值。
> - $n$ 为 $2$ 的幂，$n\le 2^{20}$，保证 $q^n\bmod m = 1$。

你谷首杀。第一眼任意模数多点求值怎么单老哥？第二眼发现被诈骗了。

你发现这个 $q^n\bmod m=1$ 就很像原根啊，于是考虑魔改 NTT。

下文是给没学过 NTT 的选手看的。定义 $w_k=q^{\frac{n}{k}}$。不难发现 $w_k$ 满足以下性质：

- $w_{k}^{m}=w_{2k}^{2m}$。
- $w_{k}^{m+k}\bmod m=w_k^m\bmod m$。

那么如果我们要求 $W(x)$，考虑设：

$$F(x)=\sum\limits_{i=0}^{\frac{n}{2}-1}a_{2i}x^i\\G(x)=\sum\limits_{i=0}^{\frac{n}{2}-1}a_{2_i+1}x^i$$

那么 $W(x)=F\left(x^2\right)+xG\left(x^2\right)$。而我们要求的就是 $W(1),\dots,W\left(w_n^{n-1}\right)$。

设 $m\in \left[0,\dfrac{n}{2}\right)$，则有：

$$W(w_n^m)=F\left(w_n^{2m}\right)+w_n^mG\left(w_n^{2m}\right)=F\left(w_{\frac{n}{2}}^m\right)+w_n^mG\left(w_{\frac{n}{2}}^m\right)$$

以及：

$$W\left(w_n^{m+\frac{n}{2}}\right)=F\left(w_n^{2m+n}\right)+w_n^{m+\frac{n}{2}}G\left(w_n^{2m+n}\right)=F\left(w_{\frac{n}{2}}^m\right)+w_n^{m+\frac{n}{2}}G\left(w_{\frac{n}{2}}^m\right)$$

那么我们只需要计算出 $F(x),G(x)$ 在 $1,\dots,w_{\frac{n}{2}}^{\frac{n}{2}-1}$ 处的值即可。这是两个和原问题相同的子问题，递归计算即可。边界是 $n=1$，此时应该直接返回常数项。

这样空间是 $\mathcal{O}(n\log n)$。事实上学过 NTT 后容易通过位逆序优化和蝴蝶变换做到线性。不过要注意的是此处没有保证 $w_n^{\frac{n}{2}}$ 和 $-1$ 在模 $m$ 意义下相等。所以要提前算一下 $w_n^{\frac{n}{2}}$ 再代入蝴蝶变换的式子。

时间复杂度 $\mathcal{O}(n\log n)$。


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std; const int N = 1 << 21; int n, m, q, a[N], R[N], sum;
int qp(int x, int y) {
	int r = 1;
	for(; y; y >>= 1, x = x * x % m) if (y & 1) r = r * x % m; return r;
}
void I(int n) {
	for (int i = 1; i < n; ++i) {
		R[i] = R[i >> 1] >> 1; if (i & 1) R[i] |= n >> 1;
	}
}
void NTT(int *a, int n) {
	I(n); int t = qp(q, n >> 1);
	for (int i = 0; i < n; ++i) if (i < R[i]) swap(a[i], a[R[i]]);
	for (int i = 2, w, u, v, g; i <= n; i <<= 1) {
		g = qp(q, n / i);
		for (int j = 0; j < n; j += i) {
			w = 1;
			for (int k = j; k < j + (i >> 1); ++k, w = w * g % m)
				u = a[k], v = w * a[k + (i >> 1)] % m,
				a[k] = (u + v) % m, a[k + (i >> 1)] = (u + t * v) % m;
		}
	}
}
signed main() {
	cin.tie(0); cout.tie(0); ios::sync_with_stdio(0); cin >> n >> m >> q;
	for (int i = 0; i < n; ++i) cin >> a[i], a[i] %= m; NTT(a, n);
	for (int i = 0; i < n; ++i) sum = (sum + a[i]) % m; cout << sum << '\n';
	for (int i = 1; i < n; ++i) cout << a[i] << ' '; return cout << a[0], 0;
}
```

---

