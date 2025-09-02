# [AGC034F] RNG and XOR

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc034/tasks/agc034_f

すぬけくんはある乱数生成器を手に入れました。 この乱数生成器は、$ 0 $ 以上 $ 2^N-1 $ 以下の整数を生成します。 それぞれの整数を生成する確率は、整数列 $ A_0,A_1,\cdots,A_{2^N-1} $ によって表され、 整数 $ i $ ($ 0\ \leq\ i\ \leq\ 2^N-1 $) が生成される確率は $ A_i\ /\ S $ です。 ただしここで $ S\ =\ \sum_{i=0}^{2^N-1}\ A_i $ とします。 また、乱数生成は毎回独立に行われます。

すぬけくんは整数 $ X $ を持っています。 今、$ X=0 $ です。 すぬけくんは、次の操作を好きなだけ行うことが出来ます。

- 乱数生成器で一つの整数 $ v $ を生成する。そして、$ X $ を $ X\ \oplus\ v $ で置き換える。 ただしここで、$ \oplus $ はビットごとの排他的論理和を表す。

それぞれの整数 $ i $ ($ 0\ \leq\ i\ \leq\ 2^N-1 $) について、$ X $ を $ i $ にするために必要な操作の回数の期待値を求めてください。 ただし、期待値は mod $ 998244353 $ で出力してください。 より正確には、期待値が既約分数 $ P/Q $ で表されるとき、 $ R\ \times\ Q\ \equiv\ P\ \mod\ 998244353,\ 0\ \leq\ R\ <\ 998244353 $ を満たす整数 $ R $ が一意に定まるので、その $ R $ を出力してください。

なお、すべての $ i $ について、$ X $ を $ i $ にするために必要な操作の回数の期待値が有理数として存在し、 さらに mod $ 998244353 $ での整数表現が定義できることが問題の制約から証明できます。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 18 $
- $ 1\ \leq\ A_i\ \leq\ 1000 $
- 入力される値はすべて整数である。

### Sample Explanation 1

$ 0 $ 回操作をした段階で $ X=0 $ なので、$ X $ を $ 0 $ にするのに必要な操作回数の期待値は $ 0 $ です。 また、どの状態から操作しても、操作後の $ X $ の値はそれぞれ $ 1/4 $ の確率で $ 0,1,2,3 $ になります。 よって、$ X $ を $ 1,2,3 $ にするのに必要な操作回数の期待値はいずれも $ 4 $ です。

### Sample Explanation 2

$ X $ を $ 0,1,2,3 $ にするのに必要な操作回数の期待値は、それぞれ $ 0,7/2,4,7/2 $ です。

## 样例 #1

### 输入

```
2
1 1 1 1```

### 输出

```
0
4
4
4```

## 样例 #2

### 输入

```
2
1 2 1 2```

### 输出

```
0
499122180
4
499122180```

## 样例 #3

### 输入

```
4
337 780 799 10 796 875 331 223 941 67 148 483 390 565 116 355```

### 输出

```
0
468683018
635850749
96019779
657074071
24757563
745107950
665159588
551278361
143136064
557841197
185790407
988018173
247117461
129098626
789682908```

# 题解

## 作者：Soulist (赞：12)

解法似乎和 [ZJOI2019 开关] 一模一样...

---

我们先列出高斯消元的方程，然后考虑集合幂级数：

$$\begin{aligned}
&f_i = 1+\sum_{j\oplus k=i} f_j\cdot p_k
\\& \textrm{FWT}(F(x))=\textrm{FWT}(\sum_k x^k)+ \textrm{FWT}(F(x))\cdot \textrm{FWT}(P(x))+\textrm{FWT}(c)
\\& \textrm{FWT}(F(x))_i=\textrm{FWT}(G(x))_i+\textrm{FWT}(F(x))_i\cdot \textrm{FWT}(P(x))_i+c
\end{aligned}$$

我们先考虑求出具体的 $c$，考虑 $f_i$ 的取值，应该有：

$$\textrm{FWT}(F(x))_i=\frac{\textrm{FWT}(G(x))_i+c}{1-\textrm{FWT}(P(x))_i}$$

然后我们考虑 $i=0$ 时，此时 $\textrm{FWT}(P(x))_0=\sum p_i=1$，所以此时有 $\textrm{FWT}(F(x))_0\cdot 0=\textrm{FWT}(G(x))_0+c$

于是有：

$$c=-\textrm{FWT}(G(x))_0=-2^n$$

于是对于 $i\ne 0$ 的部分，我们有：

$$\textrm{FWT}(F(x))_i=\frac{-2^n}{1-\textrm{FWT}(P(x))_i}$$

我们进行暴力集合幂级数求逆，对于 $i=0$ 的部分，利用定义式导出恒等式求解即可。

复杂度为 $\mathcal O((n+\log w)\cdot 2^n)$

---

## 作者：云浅知处 (赞：8)

$f_i$ 表示得到 $i$ 的最小操作次数，那么有
$$
f_0=0\\
f_i=1+\sum_{j}p_jf_{i\text{ xor }j}=1+\sum_{x\text{ xor }y=i}p_xf_y\quad(i\neq 0)
$$
所以有 $(f\star p)_i=f_i-1\quad(i\neq 0)$，现在已知 $p$ 要解 $f$；其中 $\star$ 表示异或卷积。

当然可以高消，但复杂度 $O(2^{3n})$。

我们发现这个形式就很像 FWT，但是 $f_0$ 不满足这个条件，不能直接求逆。

考虑 $(f\star p)_0$ 是啥，我们发现由于 $\sum p_i=1$，必然有 $\sum f_i=\sum (f\star p)_i$，于是应当有
$$
(f\star p)_0=f_0+\sum_{i\neq 0}f_i-(f\star p)_i=f_0+2^N-1
$$
于是我们有这个方程：
$$
(f_0,f_1,\cdots,f_{2^N-1})\star(p_0,p_1,\cdots,p_{2^N-1})=(f_0+2^N-1,f_1-1,\cdots,f_{2^N-1}-1)
$$
我们发现方程的两边都有 $f$，没办法直接求逆。但是只要令 $p_0\leftarrow p_0-1$ 就有
$$
(f_0,f_1,\cdots,f_{2^N-1})\star(p_0-1,p_1,\cdots,p_{2^N-1})=(2^N-1,-1,\cdots,-1)
$$
此时看上去可以直接 FWT 求逆，但注意这个式子会得到 $\text{FWT}(f)_0\times 0=0$，无法得到 $\text{FWT}(f)_0$ 的真实值。解决方案是任取一个值作为 $\text{FWT}(f)_0$，我们发现如果他和真实的 $\text{FWT}(f)_0$ 的偏差是 $\Delta$，那么 IFWT 回去之后每个值 $f_i$ 都会变成 $f_i+\frac{\Delta}{2^N}$。再结合 $f_0=0$ 即可得到 $\Delta$ 的值，从而解得所有 $f_i$ 的真实值。

时间复杂度 $O(N2^N)$。

```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

const int mod=998244353;
int ksm(int x,int y,int p=mod){
	int ans=1;
	for(int i=y;i;i>>=1,x=1ll*x*x%p)if(i&1)ans=1ll*ans*x%p;
	return ans%p;
}
int inv(int x,int p=mod){return ksm(x,p-2,p)%p;}
int randint(int l,int r){return rand()*rand()%(r-l+1)+l;}
void add(int &x,int v){x+=v;if(x>=mod)x-=mod;}
void Mod(int &x){if(x>=mod)x-=mod;}

const int N=18;

vector<int>p,f;
void FWT(vector<int>&A,int k,int tag){
	for(int i=0;i<k;i++){
		for(int S=0;S<(1<<k);S++){
			if(S&(1<<i))continue;
			int x=A[S],y=A[S^(1<<i)];
			Mod(A[S]=x+y),Mod(A[S^(1<<i)]=x+mod-y);
		}
	}
	if(tag==-1){
		int iv=inv(1<<k);
		for(int S=0;S<(1<<k);S++)A[S]=1ll*A[S]*iv%mod;
	}
}

signed main(void){

#ifdef YUNQIAN
	freopen("in.in","r",stdin);
#endif

	int sum=0,n=read();f.resize(1<<n),p.resize(1<<n);
	for(int i=0;i<(1<<n);i++)p[i]=read(),add(sum,p[i]);sum=inv(sum);
	for(int i=0;i<(1<<n);i++)p[i]=1ll*p[i]*sum%mod;add(p[0],mod-1);
	FWT(p,n,1);
	f[0]=(1<<n)-1;for(int i=1;i<(1<<n);i++)f[i]=mod-1;
	FWT(f,n,1);
	for(int i=0;i<(1<<n);i++)f[i]=1ll*f[i]*inv(p[i])%mod;
	FWT(f,n,-1);
	for(int i=1;i<(1<<n);i++)add(f[i],mod-f[0]);f[0]=0;
	for(int i=0;i<(1<<n);i++)cout<<f[i]<<'\n';

	return 0;
}
```

---

## 作者：Kinandra (赞：8)

标签: 集合幂级数, FWT.

定义集合幂级数的乘法为异或卷积, $\oplus$ 表示异或.

设 $p_i=\frac {A_i}{\sum_{j=0}^{2^n-1} A_j}$ , $e_i$ 表示 $0$ 变成 $i$ 的期望步数(显然也等于 $i$ 变成 $0$ 的期望步数).

易知: $e_i=\begin{cases}0,&i=0\\1+\sum_{j=0}^{2^n-1}e_{i\oplus j}\times p_j,&i\neq0\end{cases}$

设 $E,P$ 分别为 $e,p$ 的集合幂级数, 定义 $S(E)$ 表示集合幂级数 $E$ 所有系数的和.

则有 $E*P+I=E+c$ (记为 $(1)$ 式), 其中 $I$ 为全 $1$ 的幂级数, $c$ 为修正 $e_0$ 的常数.

根据 $(1)$ 式, 有 $S(E)\times S(P)+S(I)=S(E)+c$ , 由于 $S(P)=1$ , 所以 $c=S(I)=2^n$.

变形 $(1)$ 式得 $E*(P-1)=2^n-I$ , 所以 $FWT(E)_i\times FWT(P-1)_i=FWT(2^n-I)_i$.

易知当 $i\neq 0$ 时, $FWT(P-1)_i\neq 0$, 故 $FWT(E)_i=\frac {FWT(2^n-I)_i}{FWT(P-1)_i}$ .

对 $FWT(E)_0$ 待定系数, 利用 $E_0=0$ 求解即可.

时间复杂度 $\mathcal O(n\times2^n)$. 

```cpp
#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
int read();
int M(int x) { return x >= mod ? x - mod : x; }
void Add(int& x, int y) { (x += y) >= mod ? x -= mod : x; }
int n, len, sp;
int fsp(long long bs, int p) {
    int rt = 1;
    while (p) {
        if (p & 1) rt = bs * rt % mod;
        bs = bs * bs % mod, p >>= 1;
    }
    return rt;
}

struct Poly {
    int x[300005];
    int& operator[](int p) { return x[p]; }
    void fwt(int len) {
        for (int l = 2; l <= len; l <<= 1)
            for (int i = 0, m = l >> 1; i < len; i += l)
                for (int j = i, t; j < i + m; ++j)
                    t = x[j + m], x[j + m] = M(x[j] - t + mod), Add(x[j], t);
    }
    void ifwt(int len) {
        fwt(len);
        int ny = fsp(len, mod - 2);
        for (int i = 0; i < len; ++i) x[i] = 1ll * x[i] * ny % mod;
    }
} E, P, S;

int main() {
    n = read(), len = 1 << n;
    for (int i = 0; i < len; ++i) sp += (P[i] = read());
    sp = fsp(sp, mod - 2);
    for (int i = 0; i < len; ++i) P[i] = 1ll * P[i] * sp % mod;
    (--P[0]) < 0 ? P[0] += mod : 0, S[0] = len - 1;
    for (int i = 1; i < len; ++i) S[i] = mod - 1;
    P.fwt(len), S.fwt(len);
    for (int i = 1; i < len; ++i) E[i] = 1ll * S[i] * fsp(P[i], mod - 2) % mod;
    E.ifwt(len);
    int x = mod - E[0];
    for (int i = 0; i < len; ++i) printf("%d\n", M(x + E[i]));

    return 0;
}
const int _SIZE = 1 << 22;
char ibuf[_SIZE], *iS = ibuf, *iT = ibuf;
#define gc                                                         \
    (iS == iT ? iT = ((iS = ibuf) + fread(ibuf, 1, _SIZE, stdin)), \
     (iS == iT ? EOF : *iS++) : *iS++)
int read() {
    int x = 0, f = 1;
    char c = gc;
    while (!isdigit(c)) f = (c == '-') ? -1 : f, c = gc;
    while (isdigit(c)) x = x * 10 + c - '0', c = gc;
    return x * f;
}
```



---

## 作者：ZigZagKmp (赞：8)

本文同步于我的 [cnblog](https://www.cnblogs.com/ZigZagKmp/p/14383479.html)

## 题意简述
给定 $n$ 和 $2^n$ 个数，初始有一个数$x=0$，每次操作有一定概率选中 $i$ ，并将 $x$ 变成 $x\ \mathrm{xor}\ i$ ，问将 $x$ 第一次变为某个数的期望操作次数。

$n\le 18$。

## 算法分析
设 $E(i)$ 表示 $x$ 第一次从 $0$ 变为 $i$ 的期望步数。

不难得到如下 $2^n$ 个方程：
$$E(0)=0$$
$$E(i)=1+\sum_{j \ \mathrm{xor}\ k=i}a_j\cdot E(k)\ ,\ i\neq 0$$

这个形式是比较标准的 `FWT` 形式，考虑把 $E(i)$ 写成生成函数：

$$E=I+E*A$$

（注：此处的乘号表示的是广义乘法，本题中对应 `xor` 卷积）

但这个式子对常数项等细节处理并不正确，当我们把两边的所有系数相加，会发现 $0=2^n$。

因此实际上是这样的：

$$E+2^n=I+E*A$$

即

$$E=\frac{I-2^n}{1-A}$$

这样在 `FWT` 后点值可以直接相除，即可解决。

最后还有一个问题，把上面求出的 $E$ 进行 `IFWT` 后会发现可能不满足 $E(0)=0$ ，考虑回到最原始的式子：

$$E(i)=1+\sum_{j \ \mathrm{xor}\ k=i}a_j\cdot E(k)\ ,\ i\neq 0$$

因为 $\sum a_i=1$ ，所以对所有 $E(i)$ 同时加上一个常数 $t$ 不影响正确性，即可调整。

时间复杂度 $O(n2^n)$ 。

## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 1000005
#define maxm 2000005
#define inf 0x3f3f3f3f
#define int long long
#define mod 998244353
#define local
void file(string s){freopen((s+".in").c_str(),"r",stdin);freopen((s+".out").c_str(),"w",stdout);}
template <typename Tp> void read(Tp &x){
	int fh=1;char c=getchar();x=0;
	while(c>'9'||c<'0'){if(c=='-'){fh=-1;}c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c&15);c=getchar();}x*=fh;
}
int ksm(int b,int p,int Mod=mod){int ret=1;while(p){if(p&1)ret=1ll*ret*b%Mod;b=1ll*b*b%Mod;p>>=1;}return ret;}
int n,m;
int a[maxn],b[maxn],e[maxn];
void fwt(int *f,int typ){
	for(int len=1;len<n;len<<=1){
		for(int i=0;i<n;i+=(len<<1)){
			for(int j=0;j<len;++j){
				int l=f[i+j],r=f[i+j+len];
				f[i+j]=(l+r)%mod;
				f[i+j+len]=(l-r+mod)%mod;
			}
		}
	}
	if(typ==-1){
		int NN=ksm(n,mod-2);
		for(int i=0;i<n;++i)f[i]=1ll*f[i]*NN%mod;
	}
}
signed main(){
	int sm=0;
	read(n);n=(1<<n);
	for(int i=0;i<n;++i)read(a[i]),sm=(sm+a[i])%mod;
	sm=ksm(sm,mod-2);
	for(int i=0;i<n;++i)a[i]=1ll*a[i]*sm%mod;
	a[0]=(a[0]-1+mod)%mod;//处理出 1-A
	for(int i=0;i<n;++i)b[i]=(mod-1);
	b[0]=(b[0]+n+mod)%mod;//处理出 I-2^n
	fwt(a,1);fwt(b,1);
	for(int i=0;i<n;++i)e[i]=1ll*b[i]*ksm(a[i],mod-2)%mod;//直接点值相除
	fwt(e,-1);
	for(int i=0;i<n;++i)printf("%lld\n",(e[i]-e[0]+mod)%mod);//调整
	return 0;
}
```

---

## 作者：1saunoya (赞：5)

emmmm....soulist 的做法。


假设

$f_x$ 为 $x$ 到 0 的期望步数。

不难得到 $n$ 个方程。

$f_i = 1+ \sum_{j\ xor\ k = i}{f_j \times p_k}$。


$FWT(F) = FWT(\sum x^k) + FWT(F) \times FWT(p) + FWT(C)$

${FWT(F)}[i] = FWT(\sum x^k)[i] + FWT(F)[i] \times FWT(p)[i] + C$。

（当一个 $x^0 = C$ 时，所有的 $x^i = C$）

然后我们根据定义 $f_0 = 0$ 来解出来 $C$。

然后 $FWT(F)$ 就可以计算出来，IFWT 一下，就知道 $F$ 了，然后根据 $f_0 = 0$，整体偏移就能过了。

```cpp
#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
constexpr int P = 998244353;
int power(int x, int y) {
	int r = 1;
	while (y) {
		if (y & 1) {
			r = (i64)r * x % P;
		}
		x = (i64)x * x % P;
		y /= 2;
	}
	return r;
}
void fwt(std::vector<int> &f) {
	int l = 1;
	while (l < (int)f.size()) {
		l *= 2;
	}
	if (f.size() != l)
		f.resize(l);
	for (int len = 1; len < l; len *= 2) {
		for (int i = 0; i < l; i += len * 2) {
			for (int j = 0; j < len; j++) {
				int x = f[i + j], y = f[i + j + len];
				int t = x + y;
				if (t >= P) {
					t -= P;
				}
				f[i + j] = t;
				t = x - y;
				if (t < 0) {
					t += P;
				}
				f[i + j + len] = t;
			}
		}
	}
}
const int inv2 = power(2, P - 2);
void ifwt(std::vector<int> &f) {
	int l = 1;
	while (l < (int)f.size()) {
		l *= 2;
	}
	if (f.size() != l)
		f.resize(l);
	for (int len = 1; len < l; len *= 2) {
		for (int i = 0; i < l; i += len * 2) {
			for (int j = 0; j < len; j++) {
				int x = f[i + j], y = f[i + j + len];
				int t = x + y;
				if (t >= P) {
					t -= P;
				}
				f[i + j] = (i64)t * inv2 % P;
				t = x - y;
				if (t < 0) {
					t += P;
				}
				f[i + j + len] = (i64)t * inv2 % P;
			}
		}
	}
}
std::vector<int> mul(std::vector<int> f, std::vector<int> g) {
	assert(f.size() == g.size());
	std::vector<int> h(f.size(), 0);
	fwt(f);
	fwt(g);
	for (int i = 0; i < (int)f.size(); i++) {
		h[i] = (i64)f[i] * g[i] % P;
	}
	ifwt(h);
	return h;
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n;
	std::cin >> n;
	std::vector<int> p(1 << n);
	for (int i = 0; i < 1 << n; i++) {
		std::cin >> p[i];
	}
	int t = std::accumulate(p.begin(), p.end(), 0);
	int invt = power(t, P - 2);
	for (int i = 0; i < 1 << n; i++) {
		p[i] = (i64)p[i] * invt % P;
	}
	std::vector<int> g(1 << n, 0);
	for (auto &i : g) ++i;
	fwt(p);
	fwt(g);
	int c = P - g[0];
	std::vector<int> f(1 << n);
	for (int i = 0; i < 1 << n; i++) {
		f[i] = (i64)(g[i] + c) * power(P + 1 - p[i], P - 2) % P;
	}
	ifwt(f);
	int delta = f[0];
	for (int i = 0; i < 1 << n; i++) {
		f[i] -= delta;
		if (f[i] < 0) {
			f[i] += P;
		}
		std::cout << f[i] << "\n";
	}
	return 0;
}
```

---

## 作者：tzc_wk (赞：4)

upd on 2021.6.24：修了个 typo

[Atcoder 题面传送门](https://atcoder.jp/contests/agc034/tasks/agc034_f) & [洛谷题面传送门](https://www.luogu.com.cn/problem/AT4996)

tsc 考试前 A 的题了，结果到现在才写这篇题解……为了 2mol 我已经~~一周~~没碰键盘了，现在 2mol 结束算是可以~~短暂的春天~~ 短暂地卷一会儿 OI 了（（

~~u1s1 写这篇题解的时候我连题都快忘了。。。~~

首先设 $b_i=\dfrac{A_i}{\sum\limits_{j=0}^{2^n-1}A_j}$，其次碰到这种期望类的题目我们考虑套路地设 $p_i$ 表示异或得到 $i$ 的概率，那么有 $p_i=\sum\limits_{j=0}^{2^n-1}p_jb_{i\oplus j}+1$，$p_0=0$。这个状态定义是存在后效性的，而高斯消元 $8^n$ 又显然会超时，因此考虑从这个转移式本身入手进行优化。注意到这个转移式长得有点像异或卷积，因此考虑用异或卷积的形式将这个式子写出来，即 $p=p\times b+I$，其中 $\forall i,I_i=1$，异常好理解。

不过事实上这个式子是有个 bug 的，$p_0=0$，而将 $p_0$ 带到右边去就不一定等于 $0$ 了，也就是说左边实际上要加上一个常数 $X$，即 $p+X=p\times b+I(X\in\mathbb{R})$（事实上很多生成函数的题也需要注意常数项的问题，比如说斐波那契数列，这里就不再赘述了）。怎么求这个 $X$ 的值呢？这里又是一个套路，将左边每一项都变成它的系数和，相当于多项式里的令 $x=1$，那么可以得到 $(\sum\limits_{i=0}^{2^n-1}p_i)+X=(\sum\limits_{i=0}^{2^n-1}p_i)\times (\sum\limits_{i=0}^{2^n-1}b_i)+(\sum\limits_{i=0}^{2^n-1}I_i)$，而显然 $\sum\limits_{i=0}^{2^n-1}b_i=1$，故 $X=\sum\limits_{i=0}^{2^n-1}I_i=2^n$，因此 $p+2^n=p\times b+I$，简单移个项可得 $2^n-I=p\times(b-1)$，故 $p=\dfrac{2^n-I}{b-1}$，把上下两个幂级数 FWTxor 一下相除再 FWTxor 回去即可得到 $p$。

还有一个小问题，就是在求逆元的时候有可能会出现分母为 $0$ 的情况。事实上，由于 $A_i\le 1000$，因此从所有 $b_i$ 中任意选出一些出来它们的分子分母都 $<998244353$，记 $F=\text{FWT}(b-1)$，那么必然有 $F_i\le 0(i\ne 0)$，而 $F_0=-1+\sum\limits_{i=0}^{2^n-1}b_i=0$，因此出错的只可能是 $F_0$。不过这个问题很好解决，我们已知 $p_0=0$，而显然对于一个幂级数 $F$ FWTxor 后得到的幂级数 $G$，常数项上加上一个常数 $C$ 对于 $F$ 的作用效果就是每一项都加上 $C$，因此我们只需输出 $p_i-p_0$ 即可。

```cpp
const int MAXP=1<<18;
const int MOD=998244353;
int qpow(int x,int e=MOD-2){
	int ret=1;
	for(;e;e>>=1,x=1ll*x*x%MOD) if(e&1) ret=1ll*ret*x%MOD;
	return ret;
}
int n,a[MAXP+5],b[MAXP+5],c[MAXP+5];
void FWTxor(int *a,int len,int type){
	for(int i=2;i<=len;i<<=1)
		for(int j=0;j<len;j+=i)
			for(int k=0;k<(i>>1);k++){
				int X=a[j+k],Y=a[(i>>1)+j+k];
				a[j+k]=1ll*(X+Y)*type%MOD;
				a[(i>>1)+j+k]=1ll*(X-Y+MOD)*type%MOD;
			}
}
int main(){
	scanf("%d",&n);n=1<<n;int sum=0;
	for(int i=0;i<n;i++) scanf("%d",&a[i]),sum+=a[i];sum=qpow(sum);
	for(int i=0;i<n;i++) a[i]=1ll*a[i]*sum%MOD;a[0]=(a[0]-1+MOD)%MOD;
	for(int i=0;i<n;i++) b[i]=MOD-1;b[0]=(b[0]+n)%MOD;
	FWTxor(a,n,1);FWTxor(b,n,1);
	for(int i=0;i<n;i++) c[i]=1ll*b[i]*qpow(a[i])%MOD;
	FWTxor(c,n,MOD+1>>1);
	for(int i=0;i<n;i++) printf("%d\n",(c[i]-c[0]+MOD)%MOD);
	return 0;
}
```



---

## 作者：xht (赞：4)

## [RNG and XOR](https://atcoder.jp/contests/agc034/tasks/agc034_f)

### 题意

- 给定 $n$ 和 $a_{0\dots 2^n-1}$。
- 有一个初始为 $0$ 的变量 $x$。
- 每次操作会将 $x$ 以 $\frac {a_i}{\sum_{j=0}^{2^n-1}a_j}$ 的概率异或上 $i$。
- 求对于 $i \in [0,2^n-1]$，$x$ 第一次变成 $i$ 的期望操作次数。
- $n \le 18$，$a_i \le 10^3$，答案对 $998244353$ 取模。

### 题解

为了方便，将 $a_i$ 视为 $\frac {a_i}{\sum_{j=0}^{2^n-1}a_j}$。

设 $x_i$ 为 $i$ 第一次变成 $0$ 的期望操作次数，显然 $x_i$ 也是 $0$ 第一次变成 $i$ 的期望操作次数。

有转移：
$$
x_i =
\begin{cases}
0 & i = 0 \\\\
\sum_{j=0}^{2^n-1} a_jx_{i\operatorname{xor}j} + 1 & i \ne 0
\end{cases}
$$
即异或卷积：
$$
(x_0,x_1,\cdots,x_{2^n-1})\operatorname{xor}(p_0,p_1,\cdots,p_{2^n-1}) = (c,x_1-1,x_2-1,\cdots,x_{2^n-1}-1)
$$
其中 $c$ 为一个常数。

注意到显然异或卷积 $(p_0,p_1,\cdots,p_{2^n-1})$ 后总和不变，因此 $c = x_0+2^n-1$，即：
$$
(x_0,x_1,\cdots,x_{2^n-1})\operatorname{xor}(p_0,p_1,\cdots,p_{2^n-1}) = (x_0+2^n-1,x_1-1,x_2-1,\cdots,x_{2^n-1}-1)
$$
注意到如果将 $p_0$ 减 $1$，那么右边第 $i$ 项会减去 $x_i$，正好把右边的未知项删掉了，即：
$$
(x_0,x_1,\cdots,x_{2^n-1})\operatorname{xor}(p_0-1,p_1,\cdots,p_{2^n-1}) = (2^n-1,-1,-1,\cdots,-1)
$$
这时异或卷积中的三项有两项都已知了，那么剩下的一项可以直接 FWT 求出。

然而会发现求出的答案不对，问题出在这样的异或卷积是有不只一组解的，对每个 $x_i$ 都加上 $k$ 之后式子依然成立。

又注意到 $x_0 = 0$，因此我们把求出来的每一项都减去 $x_0$ 就是我们要的答案。

时间复杂度 $\mathcal O(n2^n)$。

### 代码

```cpp
const int N = 1 << 18 | 1;
int n;
modint a[N], b[N], s;

inline void XOR(modint *f, modint x) {
	for (int o = 2, k = 1; o <= n; o <<= 1, k <<= 1)
		for (int i = 0; i < n; i += o)
			for (int j = 0; j < k; j++) {
				modint p = f[i+j] * x, q = f[i+j+k] * x;
				f[i+j] = p + q, f[i+j+k] = p - q;
			}
}

int main() {
	rd(n), n = 1 << n;
	for (int i = 0; i < n; i++) rd(a[i]), b[i] = P - 1, s += a[i];
	modint vs = 1 / s;
	for (int i = 0; i < n; i++) a[i] *= vs;
	a[0] -= 1, b[0] = n - 1;
	XOR(a, 1), XOR(b, 1);
	for (int i = 0; i < n; i++) b[i] /= a[i];
	XOR(b, (modint)1 / 2);
	for (int i = 0; i < n; i++) print(b[i] - b[0]);
	return 0;
}
```

---

## 作者：zdd0342 (赞：3)

## [AGC034F] RNG and XOR

考虑 $dp$ 转移。

设 $p_i=\frac{A_i}{\sum A}$ 表示异或 $i$ 的概率。

定义 $f_i$ 表示走到 $i$ 的期望步数，有初始状态 $f_0=0$。

转移：
$$
f_i=1+\sum_{j=0}^{2^n-1}f_{i \operatorname{xor} j}\times p_{j}
$$
发现形如异或卷积。

即为：$(f_0,f_1,\dots,f_{2^n-1})\times (p_0,p_1,\dots,p_{2^n-1})=(C,f_{1}-1,f_{2}-1,\dots,f_{2^n-1}-1)$。

因为 $f_0=0$，不是 $fwt$ 的形式，考虑解出 $C$。

考虑卷积前后的每一项系数之和。左侧式子写成：
$$
\sum_{i=0}^{2^n-1}\sum_{j\operatorname{xor}k=i}f_jp_k
$$
由于每一对 $j,k$ 都能够被计算一次，所以可以改写为：
$$
\sum_{j=0}^{2^n-1}\sum_{k=0}^{2^n-1}f_jp_k\\
=(\sum_{j=0}^{2^n-1}f_j)(\sum_{k=0}^{2^n-1}p_k)\\
$$
由于 $\sum p_k=1$，所以左边的系数和为 $\sum f_j$。

右边的系数之和显然容易计算。所以有等式：
$$
\sum_{j=0}^{2^n-1}f_j=C+\sum_{j=1}^{2^n-1}(f_j-1)\\
\sum_{j=0}^{2^n-1}f_j=C-(2^n-1)+\sum_{j=1}^{2^n-1}f_j\\
C=(2^n-1)+f_0\\
$$
现在卷积的形式好看了。

即：$(f_0,f_1,\dots,f_{2^n-1})\times (p_0,p_1,\dots,p_{2^n-1})=(f_0+2^n-1,f_{1}-1,f_{2}-1,\dots,f_{2^n-1}-1)$。

右边的 $f$ 不好计算，考虑卷积过程中减去。

发现把 $p_0\leftarrow p_0-1$，右边每一项都将减去 $f_i$。

即：$(f_0,f_1,\dots,f_{2^n-1})\times (p_0-1,p_1,\dots,p_{2^n-1})=(2^n-1,-1,-1,\dots,-1)$。

显然：
$$
(f_0,f_1,\dots,f_{2^n-1})=\frac{(2^n-1,-1,-1,\dots,-1)}{(p_0-1,p_1,\dots,p_{2^n-1})}
$$
但是还有一个问题：对于 $f_0$，最后求出来不一定的是 $0$。

怎么办？观察转移式，发现若 $f_0$ 增加 $\Delta$，那么对于任意 $i$，$f_i$ 都只能增加 $\Delta$ 才能合法。

所以答案直接输出 $f_i-f_0$ 即可。

---

## 作者：zzw4257 (赞：2)

我们本来有期望dp如下
$$
f_S=\begin{cases}0&S=\varnothing\\\displaystyle \sum_{T\subseteq U}f_Tp_{S\oplus T}+1&S\neq \varnothing\end{cases}
$$
转成异或卷积下幂级数形式
$$
\begin{aligned}
F(x)&=F(x)\times P(x)+I(x)-2^{n}x^{\varnothing}
\\F(x)\times(1-P(x))&=I(x)-2^{n}x^{\varnothing}
\end{aligned}
$$

再 $\bold {FWT}$

$$
\widehat F(x)=\frac{2^n(x^{\varnothing}-I(x))}{I(x)-\widehat P(x)}
$$

最后对所有 $S\neq \varnothing$ 对 $\widehat F(x)$ 提取 $[x^S]$ 得 $\frac{2^n}{[x^S]\widehat P(x)-1}$​

再利用 $\widehat {(\hat F(x))}=2^nF(x)$ 得 $\displaystyle [x^\varnothing]\widehat F(x)=-\sum_{S\neq \varnothing\vee S\subseteq U}[x^S]\widehat F(x)$

再 $\bold{IFWT}$ 一次即可

```cpp
int main(void){
	int i,sum=0;scanf("%d",&n),S=1<<n;for(i=0;i<S;++i)scanf("%d",p+i),A(sum,p[i]);
	for(i=0;i<S;++i)p[i]=1ll*p[i]*qpow(sum,mod-2)%mod;
	FWT(p,1);for(sum=0,i=1;i<S;++i)A(sum,f[i]=1ll*S*qpow(p[i]-1,mod-2)%mod);*f=mod-sum;
	FWT(f,-1);
	for(i=0;i<S;++i)printf("%d\n",f[i]);
	return 0;
}

```

---

## 作者：yshpdyt (赞：1)

## 题意
给定一个长度为 $2^n$ 的下标从 $0$ 开始的数组 $A$。

有一个初始为 $0$ 的变量 $x$，不断操作，每次操作以 $\dfrac {A_i}{\sum_{j=0}^{2^n-1} A_j}$ 的概率将 $x$ 变成 $x\oplus i$。

求 $x$ 第一次变成 $i\in[0,2^n)$ 的期望操作次数。

$n\leqslant 18$。

## Sol
令 $n=2^n$，$f_i$ 表示第一次变成 $i$ 的期望次数，$b_i=\frac{A_i}{\sum A_j}$。

显然有转移 $f_i=1+\sum\limits_{j=0}^{n-1} b_jf_{i\oplus j}$，特别的，$f_0=0$。

写出集合幂级数，以下卷积为异或卷积：


$$
\begin{align*}
 F(x)&=\sum\limits_{i=0}^{n-1} f_ix^{i}\\&=f_0+\sum\limits_{i=1}^{n-1} \left(1+\sum\limits_{j=0}^{n-1} b_jf_{i\oplus j}\right)x^{i}\\&=\sum\limits_{i=1}^{n-1}x^i+\sum\limits_{i=1}^{n-1} \left(\sum\limits_{j=0}^{n-1} b_jf_{i\oplus j}\right)x^{i}\\&=\sum\limits_{i=1}^{n-1}x^i+\sum\limits_{i=0}^{n-1} \left(\sum\limits_{j=0}^{n-1} b_jf_{i\oplus j}\right)x^{i}-\sum\limits_{j=0}^{n-1} b_jf_{j}\\&=\sum\limits_{i=1}^{n-1}x^i+\left(\sum\limits_{i=0}^{n-1}b_jx^j\right)\times \left(\sum\limits_{i=0}^{n-1}f_ix^i\right)-\sum\limits_{j=0}^{n-1} b_jf_{j}
\end{align*}
$$

发现右边是常数，可以带入 $x=1$ 求解。

$$\begin{align*}
F(1)&=n-1+\left(\sum\limits_{i=0}^{n-1}b_j\right)\times \left(\sum\limits_{i=0}^{n-1}f_i\right)-\sum\limits_{j=0}^{n-1} b_jf_{j}\\&=n-1+\sum\limits_{i=0}^{n-1}f_i-\sum\limits_{j=0}^{n-1} b_jf_{j}\\&=\sum\limits_{i=0}^{n-1} f_i
\end{align*}
$$

所以后面那一坨 $\sum\limits_{j=0}^{n-1} b_jf_{j}=n-1$。

如果记 $I(x)=\sum\limits_{i=0}^{n-1} x^i=1+\sum\limits_{i=1}^{n-1} x^i$，$G(x)=\sum\limits_{i=0}^{n-1} b_ix^i$。

于是发现有这样一个式子: 
$$
\begin{align*}
 F(x)&=\sum\limits_{i=1}^{n-1}x^i+\left(\sum\limits_{i=0}^{n-1}b_jx^j\right)\times\left(\sum\limits_{i=0}^{n-1}f_ix^i\right)-\sum\limits_{j=0}^{n-1} b_jf_{j}\\&=I(x)-1 +F(x)\times G(x)-(n-1)\\&=I(x) +F(x)\times G(x)-n
\end{align*}
$$
简单移项得：
$$F=\frac{n-I}{G-1}$$

由于这是集合幂级数，只需要上下两个式子分别 FWT，点除后 IFWT 即可。

但是最终 $f_0$ 可能不为 $0$，由于:
$$1+\sum\limits_{j=0}^{n-1} b_j(f_{i\oplus j}+t)=1+\sum\limits_{j=0}^{n-1} b_jt+\sum\limits_{j=0}^{n-1} b_jf_{i\oplus j}=1+t+\sum\limits_{j=0}^{n-1} b_jf_{i\oplus j}=f_i+t$$

所以同时增加一个数不影响答案，产生这种差异的原因可能是我们没有初始化 $f_0=0$，会产生多组答案，只需要整体偏移，输出 $f_i-f_0$ 即为答案。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 2000005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=998244353;
const ll inf=1e18;
const double eps=1e-6;
ll n,a[N];
namespace fwt{
    #define poly vector<ll>
    ll fpow(ll x,ll y){
        ll res=1;
        while(y){
            if(y&1)res=res*x%mod;
            x=x*x%mod;
            y>>=1;
        }
        return res;
    }
    void add(ll &x,ll y){
        x=(x%mod+y%mod+mod+mod)%mod;
    }
    void wxor(poly &a,ll type){
        if(type==-1)type=fpow(2,mod-2);
        ll n=a.size();
        for(int o=2;o<=n;o<<=1){
            int k=o>>1;
            for(int i=0;i<n;i+=o){
                for(int j=0;j<k;j++){
                    ll l=a[i+j],r=a[i+j+k];
                    a[i+j]=(l+r)*type%mod;
                    a[i+j+k]=(l-r+mod)*type%mod;
                }
            }
        }
    }
    void mul(poly &a,poly &b){
        ll n=a.size();
        for(int i=0;i<n;i++)a[i]=a[i]*b[i]%mod;
    }
    void inv(poly &a){
        ll n=a.size();
        for(int i=0;i<n;i++)a[i]=fpow(a[i],mod-2);
    }
}using namespace fwt;
poly F,G;
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    cin>>n;
    n=(1ll<<n);
    ll sum=0;
    F.resize(n);
    G.resize(n);
    for(int i=0;i<n;i++){
        cin>>F[i];
        sum=(sum+F[i])%mod;
    }
    sum=fpow(sum,mod-2);
    for(int i=0;i<n;i++){
        F[i]=F[i]*sum%mod;
        G[i]=mod-1;
    }
    F[0]=(F[0]-1+mod)%mod;
    G[0]=n-1;
    wxor(G,1),wxor(F,1),inv(F);
    mul(G,F),wxor(G,-1);
    for(auto y:G)cout<<(y-G[0]+mod)%mod<<endl;
    return 0;
}
```

---

## 作者：do_while_true (赞：1)

$f_i$ 为变成 $i$ 的期望步数，那么 $f_0=0$，$f_i=1+\sum_{j=0}^{2^n-1}f_j\cdot p_{i\oplus j}$，理解为从 $i$ 走到 $0$ 的期望步数即可。

尝试用集合幂级数描述这个东西，如果不管 $f_0$ 那么就是 $F=F\times P+I$，其中乘法定义为异或卷积，$I=\{1,1,\cdots\}$，但 $p$ 总和为 $1$ 所以 $F$ 系数和与 $F\times P$ 系数和应该相等，所以应为 $F=F\times P+I-2^n$，那么 $F=(I-2^n)/(1-P)$．

如果直接 $[x^i]FWT(F)=[x^i](I-2^n)/[x^i](1-P)$，主要问题在于 $[x^0]FWT(1-P)=0$（所有概率和为 1），所以无法正确得到 $[x^0]FWT(F)$ 的值。

但考虑将 $[x^0]FWT(F)$ 增加 $k$ 相当于给 $[x^i]F$ 增加 $\frac{1}{2^n}(-1)^{|0\& i|}k$，也就是整体加一个常数，那么按照之前的式子求出来的东西，每一位都减去 $[x^0]$ 的值即可完成修正。

```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<random>
#include<assert.h>
#define pb emplace_back
#define mp make_pair
#define fi first
#define se second
#define dbg(x) cerr<<"In Line "<< __LINE__<<" the "<<#x<<" = "<<x<<'\n'
#define dpi(x,y) cerr<<"In Line "<<__LINE__<<" the "<<#x<<" = "<<x<<" ; "<<"the "<<#y<<" = "<<y<<'\n'
#define DE(fmt,...) fprintf(stderr, "Line %d : " fmt "\n",__LINE__,##__VA_ARGS__)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int>pii;
typedef pair<ll,int>pli;
typedef pair<ll,ll>pll;
typedef pair<int,ll>pil;
typedef vector<int>vi;
typedef vector<ll>vll;
typedef vector<pii>vpii;
typedef vector<pll>vpll;
template<typename T>T cmax(T &x, T y){return x=x>y?x:y;}
template<typename T>T cmin(T &x, T y){return x=x<y?x:y;}
template<typename T>
T &read(T &r){
	r=0;bool w=0;char ch=getchar();
	while(ch<'0'||ch>'9')w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9')r=r*10+(ch^48),ch=getchar();
	return r=w?-r:r;
}
template<typename T1,typename... T2>
void read(T1 &x,T2& ...y){read(x);read(y...);}
const int mod=998244353;
inline void cadd(int &x,int y){x=(x+y>=mod)?(x+y-mod):(x+y);}
inline void cdel(int &x,int y){x=(x-y<0)?(x-y+mod):(x-y);}
inline int add(int x,int y){return (x+y>=mod)?(x+y-mod):(x+y);}
inline int del(int x,int y){return (x-y<0)?(x-y+mod):(x-y);}
int qpow(int x,int y){
	int s=1;
	while(y){
		if(y&1)s=1ll*s*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return s;
}
const int N=(1<<18)+10;
inline int all(int x){return (1<<x)-1;}
inline int bit(int x){return 1<<x;}
void FWT(int *f,int n){
	for(int i=0;i<n;i++)
		for(int S=0;S<(1<<n);S++)
			if(!(bit(i)&S)){
				int u=f[S],v=f[S^bit(i)];
				f[S]=add(u,v);f[S^bit(i)]=del(u,v);
			}
}
void IFWT(int *f,int n){
	for(int i=0;i<n;i++)
		for(int S=0;S<(1<<n);S++)
			if(!(bit(i)&S)){
				int u=f[S],v=f[S^bit(i)];
				f[S]=499122177ll*add(u,v)%mod;f[S^bit(i)]=499122177ll*del(u,v)%mod;
			}
}
int n;
int p[N],f[N],sum;
signed main(){
	#ifdef do_while_true
//		assert(freopen("data.in","r",stdin));
//		assert(freopen("data.out","w",stdout));
	#endif
	read(n);
	for(int i=0;i<(1<<n);i++){
		cadd(sum,read(p[i]));
		f[i]=1;
	}
	sum=qpow(sum,mod-2);
	for(int i=0;i<(1<<n);i++)p[i]=del(0,1ll*p[i]*sum%mod);
	cadd(p[0],1);
	FWT(p,n);
	cdel(f[0],qpow(2,n));
	FWT(f,n);
	for(int i=0;i<(1<<n);i++)
		f[i]=1ll*f[i]*qpow(p[i],mod-2)%mod;
	IFWT(f,n);
	for(int i=0;i<(1<<n);i++)cout << del(f[i],f[0]) << '\n';
    #ifdef do_while_true
//		cerr<<'\n'<<"Time:"<<1.0*clock()/CLOCKS_PER_SEC*1000<<" ms"<<'\n';
	#endif
	return 0;
}
```

---

## 作者：UKE_Automation (赞：1)

### AGC034F RNG and XOR

[$\text{Link}$](https://atcoder.jp/contests/agc034/tasks/agc034_e)

首先这道题我们有一个最基本的转移方程，设 $f(i)$ 表示操作出 $i$ 的期望步数，则有：
$$
\begin{cases}
f(0)=0\\
f(i)=\sum f(j)\times p_{i\oplus j}+1
\end{cases}
$$
下面这个转移的形式比较像位运算卷积，我们给它改写成一般形式：
$$
f(i)=\sum_{j\oplus k=i} f(j)\times p_k+1
$$
考虑将转移写成集合幂级数的形式，令 $f,p$ 的集合幂级数分别为 $F,P$，则有：
$$
F=F* P+I
$$
注意这里的 $*$ 指的是异或卷积，$I$ 为单位幂级数。这个式子看上去非常正确，但是实则不然，观察后可以发现，由于 $P$ 的系数之和为 $1$，所以等式右边比左边多出来了一个 $I$ 的 $2^n$ 的系数和。因此我们要在左边加上一个常数项 $2^n$，所以有：
$$
F+2^n=F*P+I
$$
移项后可得 $F*(1-P)=I-2^n$，直接做一次 FWT 即可得到：
$$
\begin{aligned}
&\text{FWT}(F)_i\times\text{FWT}(1-P)_i=\text{FWT}(I-2^n)_i\\
\Rightarrow&\text{FWT}(F)_i=\dfrac{\text{FWT}(I-2^n)_i}{\text{FWT}(1-P)_i}
\end{aligned}
$$
那么我们对 $1-P$ 和 $I-2^n$ 分别做 FWT，将点值相除得到 $\text{FWT}(F)$，然后再做一次 IFWT 即可得到正确的 $F$。

最后还有一个小问题，我们最后求出的 $F$ 还是可能不满足 $f(0)=0$，不过容易发现，我们将所有 $f$ 同时减去一个值不会影响结果，所以我们输出 $f(i)-f(0)$ 就是答案。复杂度是 $O(n2^n)$。

```cpp
#include <bits/stdc++.h>
#define il inline

using namespace std;

const int Maxn = (1 << 18);
const int Inf = 2e9;
const int Mod = 998244353;
il int Add(int x, int y) {return x + y >= Mod ? x + y - Mod: x + y;} il void pls(int &x, int y) {x = Add(x, y);}
il int Del(int x, int y) {return x - y < 0 ? x - y + Mod : x - y;} il void sub(int &x, int y) {x = Del(x, y);}
il int qpow(int a, int b, int P = Mod) {int res = 1; for(; b; a = 1ll * a * a % P, b >>= 1) if(b & 1) res = 1ll * res * a % P; return res;}
il int Inv(int a) {return qpow(a, Mod - 2);}
template <typename T> il void chkmax(T &x, T y) {x = (x >= y ? x : y);}
template <typename T> il void chkmin(T &x, T y) {x = (x <= y ? x : y);}
template <typename T>
il void read(T &x) {
	x = 0; char ch = getchar(); bool flg = 0;
	for(; ch < '0' || ch > '9'; ch = getchar()) flg = (ch == '-');
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	flg ? x = -x : 0;
}
template <typename T>
il void write(T x, bool typ = 1) {
	static short Stk[50], Top = 0;
	x < 0 ? putchar('-'), x = -x : 0;
	do Stk[++Top] = x % 10, x /= 10; while(x);
	while(Top) putchar(Stk[Top--] | 48);
	typ ? putchar('\n') : putchar(' ');
}
il void IOS() {ios::sync_with_stdio(0); cin.tie(0), cout.tie(0);}
il void File() {freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);}
bool Beg;

int n, a[Maxn];
int p[Maxn];
void FWT(int *a, int typ) {
	for(int h = 1; h < n; h <<= 1) {
		for(int i = 0; i < n; i += (h << 1)) {
			for(int j = 0; j < h; j++) {
				int x = a[i + j], y = a[i + j + h];
				a[i + j] = Add(x, y);
				a[i + j + h] = Del(x, y);
			}
		}
	}
	if(typ == -1) {
		int iv = Inv(n);
		for(int i = 0; i < n; i++) a[i] = 1ll * a[i] * iv % Mod;
	}
}
int b[Maxn];

bool End;
il void Usd() {cerr << (&Beg - &End) / 1024.0 / 1024.0 << "MB " << (double)clock() * 1000.0 / CLOCKS_PER_SEC << "ms\n"; }
int main() {
	read(n); n = (1 << n); int sm = 0;
	for(int i = 0; i < n; i++) read(p[i]), pls(sm, p[i]);
	for(int i = 0; i < n; i++) p[i] = 1ll * p[i] * Inv(sm) % Mod;
	a[0] = 1, b[0] = Mod - n;
	for(int i = 0; i < n; i++) sub(a[i], p[i]), pls(b[i], 1);
	FWT(a, 1), FWT(b, 1);
	for(int i = 0; i < n; i++) a[i] = 1ll * b[i] * Inv(a[i]) % Mod;
	FWT(a, -1);
	for(int i = 0; i < n; i++) write(Del(a[i], a[0]));
    Usd();
	return 0;
}

```

---

## 作者：hhhqx (赞：0)

如果你也是数学小白，不妨来看看这篇题解（因为我就是数学小白）。

---
博客园：https://www.cnblogs.com/huangqixuan/articles/18608743#%E7%BB%83%E4%B9%A05-agc034f-rng-and-xor

设 $p_i = \frac{a_i}{\sum\limits_{j=0}^{2^n-1}{a_j}}$。

设 $f_i$ 表示 $0$ 变为 $i$ 的期望步数。有 $2^n - 1$ 个方程 $f_i = 1 + \sum\limits_{x \oplus y = i}{f_x \times p_y}$。（注意对于 $f_0$ 不存在方程，因为直接 $f_0 = 0$）

显然可以高斯消元，但是需要更高效的算法：

- $IFWT(FWT(F)) = IFWT(FWT(\{ 1,1,\cdots ,1\})) + IFWT(FWT(F) \cdot FWT(P)) + IFWT(FWT(\{ c,0,0,\cdots ,0\}))$。（其中 $c$ 是一个常数，用来使得 $f_0=0$）
- $FWT(F) = FWT(\{ 1,1,\cdots ,1\})) + FWT(F) \cdot FWT(P) + FWT(\{ c,0,0,\cdots ,0\})$。（这一步依据 $FWT(A+B) = FWT(A) + FWT(B)$）
- $FWT(F)_i = FWT(\{ 1,1,\cdots ,1\}))_i + FWT(F)_i \cdot FWT(P)_i + c$。（最后为什么只有 $c$ 了呢？因为 $FWT(\{ c,0,0,\cdots ,0\})_i=c$）
- $FWT(F)_i = \frac{FWT(\{ 1,1,\cdots ,1\}))_i + c}{1 - FWT(P)_i}$。

先来看看 $i=0$（**推导过程主要是依据 $FWT(A)_0 = \sum{A_i}$**）：

- $FWT(F)_0 = \frac{2^n + c}{1 - 1}$。（显然 $FWT(\{ 1,1,\cdots ,1\}))_0 = 2^n，FWT(P)_0=\sum{p_i}=1$）
- 先倒退一步 $(1 - 1)FWT(F)_0 = 2^n + c$。
- 得 $c=-2^n$！

所以对于 $i > 0$ 直接 $FWT(F)_i = \frac{FWT(\{ 1,1,\cdots ,1\}))_i - 2^n}{1 - FWT(P)_i}$ 就算出来了。

可是还需要得到 $FWT(F)_0$ 才可以 $IFWT$ 回去，算不出 $FWT(F)_0$ 怎么办？

- **待定系数法**。
- 暂且设 $FWT(F)_0 = 0$ 去进行 $IFWT$，最后得出 $F_0$ 并让所有 $F_i$ 都减去 $F_0$ 即可。（依据 FWT 和 IFWT 都是线性变换）

最后赠送一个不完全二倍经验：https://www.luogu.com.cn/problem/P5326 & https://www.luogu.com.cn/article/26ltg2h8

```cpp
#include <bits/stdc++.h>

using namespace std;
using LL = long long;

const int MAXN = (1ll << 18) + 3;
const LL mod = 998244353, i2 = 499122177;

LL qpow(LL A, LL B){
	LL ret = 1;
	while(B > 0){
		if(B & 1) ret = ret * A % mod;
		A = A * A % mod, B >>= 1;
	}
	return ret;
}

int n;
LL p[MAXN];

vector<LL> FWT(vector<LL> A){
	// {{1,1}, {1,-1}}
	for(int len = 1; len < n; len <<= 1){
		for(int i = 0; i < n; i += len + len){
			for(int j = i; j < i + len; j++){
				LL tmp = A[j];
				A[j] = (A[j] + A[j + len]) % mod, A[j + len] = (tmp - A[j + len] + mod) % mod;
			}
		}
	}
	return A;
}
vector<LL> IFWT(vector<LL> A){
	// {{0.5,0,5}, {0.5,-0.5}}
	for(int len = 1; len < n; len <<= 1){
		for(int i = 0; i < n; i += len + len){
			for(int j = i; j < i + len; j++){
				LL tmp = A[j];
				A[j] = (A[j] + A[j + len]) % mod, A[j + len] = (tmp - A[j + len] + mod) % mod;
				A[j] = A[j] * i2 % mod, A[j + len] = A[j + len] * i2 % mod;
			}
		}
	}
	return A;
}

int main(){ 
  ios::sync_with_stdio(0), cin.tie(0);
	cin >> n, n = (1ll << n);
	for(int i = 0; i < n; i++) cin >> p[i], p[n] = (p[n] + p[i]);
	p[n] = qpow(p[n], mod - 2);
	for(int i = 0; i < n; i++) p[i] = p[i] * p[n] % mod;
	vector<LL> A, B;
	for(int i = 0; i < n; i++) A.push_back(p[i]), B.push_back(1);
	A = FWT(A), B = FWT(B);
	vector<LL> F; F.push_back(0);
	for(int i = 1; i < n; i++) F.push_back((B[i] - n + mod) % mod * qpow((1 - A[i] + mod) % mod, mod - 2) % mod);
	
	F = IFWT(F);
	for(int i = 0; i < n; i++){
		cout << (F[i] - F[0] + mod) % mod << "\n";
	}
	return 0;
}
```

---

## 作者：elbissoPtImaerD (赞：0)

不妨设 $f_i$ 为 $i$ 到 $0$ 的期望次数。有：

$$f_i = \begin{cases}
\sum\limits_{j} f_jp_{i \oplus j} + 1 & (i>0) \\ 
0 & (i=0) \\ 
\end{cases}$$

定义常量函数 $I(i)=[i>0]$，考虑异或卷积 $*$，则 $f' = f * p + I$，其中 $f'_i = f_i (i>0)$。

考虑求出 $f'_0$。注意到异或卷积性质：$\sum\limits_i (f * p)_i = \sum\limits_i \sum\limits_j f_j p _ {i \oplus j} = \sum\limits_j f_j \sum\limits_i p _{i\oplus j} = \sum\limits_j f_j \sum\limits_i p_i = \sum\limits_j f_j$，以及 $\forall i>0, f_i = (f * p) _ i + 1$。容易得到 $f'_0 = f_0 + \sum\limits _{i>0} f_i - (f * p)_i = f_0 + 2^n - 1$。

于是对卷积方程进行修正：$f + 2^n - 1 = f * p + I$。解得：$(1 - p) * f = I - 2^n + 1$。异或卷积意义下求逆是简单的，只需考虑 FWT 后对应点值相除即可。

遗憾的是：$\operatorname{FWT}(1-p)_ 0 = 1 - \sum\limits_i(-1)^0p_i = 0$；欣慰的是：$\operatorname{FWT}(1-p)_ i = 1 - \sum\limits_j(-1)^{|i \cap j|}p_j > 1 - \sum\limits_j p_j = 0$。解决方案是随便取 $\operatorname{FWT}(f)_0$，然后记 $\operatorname{IFWT}$ 得到的 $f_0$ 是 $\Delta$，则 $\operatorname{FWT}(f)_0$ 应该减掉 $2^n \Delta$ 才是正确的，于是可以用正确的再 $\operatorname{IFWT}$ 一遍即可。

---

## 作者：隔壁泞2的如心 (赞：0)

你说得对，但是我不会集合幂级数、也忘了概率 dp……

但是可以指望着绝对靠谱的生成函数：设 $[x^i]F_k(x)$ 为第 $i$ 次操作后原变量为 $k$ 的概率，$[x^i]G_k(x)$ 第 $i$ 次操作后原变量第一次变为 $k$ 的概率，它们都有无限项，显然 $G_k(x)=\dfrac{F_k(x)}{F_0(x)}$，而我们所求的就是 $G'_k(1)$。

$F_k(x)$ 的每一项系数都可以通过 FWT 求出，观察一下 FWT 数组的形式，你会发现每个 $F_k(x)$ 都是下列形式（$f$ 是 FWT 数组）：

$$2^{-n}(\dfrac{1}{1-x} \pm \dfrac{1}{1-f_1x} \pm \dfrac{1}{1-f_2x} \pm ...)$$

给分式上下同乘 $2^n(1-x)$，那么 $G'_k(1)$ 直接就可以表示成一堆 $\dfrac{2}{1-f_i}$ 的和，用 FWT 就可以直接全部算出。

代码和别人的都一样，就不放了（

---

## 作者：Edward1002001 (赞：0)

### 题解：AGC34F RNG and XOR
#### 炫酷形式幂级数魔术——只要形式对了就行

我们考虑按 [ZJOI2019] 开关类似的方式处理，但是我们直接处理生成函数，而不是答案。

令 $F=[x^S]\frac{1}{1-uA},G=[x^0]\frac{1}{1-uA}$，故有 $Ans=\frac{\partial(\frac{F}{G})}{\partial u} \big|_{u=1}=\frac{F'(1)G(1)-G'(1)F(1)}{G^2(1)}$。

这是因为 $F(u)$ 是到达 $S$ 状态的概率生成函数，而 $G(u)$ 是走若干步回返的概率生成函数，所以 $\frac{F}{G}$ 是第一次到达 $S$ 状态时间的概率生成函数。

然后我们考虑如何计算。于是 $F_S(1)=\text{IFWT}_S(\frac{1}{1-A})$，$G(1)=F_0(1)$，$F_S'(1)=\text{IFWT}_S(\frac{A}{(1-A)^2})$，$G'(1)=F_0'(1)$。

这时我们发现了一个比较麻烦的事情，就是这个 $\frac{1}{1-A}$ 的常数项是 $0$ 的倒数，没有办法算了。但是不要慌张，我们注意到常数项 `IFWT` 后会简单地均分到每一项上，因此我们令 $\Delta$ 为一个无穷大量，设 $\text{IFWT}(\frac{1}{1-A})=\sum_S (\Delta/2^n+f_S) x^S,\text{IFWT}(\frac{A}{(1-A)^2})=\sum_S (\Delta^2/2^n+h_S) x^S$，之所以是 $\Delta^2$ 是因为在 $0$ 下标处分母有两个零因式乘起来了，而分子位置是 $1$。

于是：

$$
\begin{aligned}
Ans_i&=\frac{F'(1)G(1)-G'(1)F(1)}{G^2(1)} \\
&=\frac{(\Delta^2/2^n+h_i)(\Delta/2^n+f_0)-(\Delta/2^n+f_i)(\Delta^2/2^n+h_0)}{(\Delta/2^n+f_0)^2} \\
&=\frac{\Delta^2(f_0-f_i)/2^n+O(\Delta)}{\Delta^2/4^n+O(\Delta)} \\
&=2^n(f_0-f_i)
\end{aligned}
$$

因此，我们直接做 `FWT` 后将每个非零下标的值 $x$ 变为 $x^{-1}$，并将零坐标置零，再做一遍 `FWT`（因为 `IFWT` 再乘 $2^n$ 等价于 `FWT`）后输出答案即可。~~怎么样，是不是很炫酷~~

参考代码：

```cpp
#include<cstdio>
#include<utility>
const int N=1<<18,mod=998244353;typedef long long ll;const ll Mod=mod;
ll qpow(ll x,int y){ll r=1;for(;y;x=x*x%Mod,y>>=1)if(y&1)r=r*x%Mod;return r;}
inline int add(int x,int y){return x+y>=mod?x+y-mod:x+y;}
inline int sub(int x,int y){return x>=y?x-y:x-y+mod;}
void FWT(int*a,int L)
{
	for(int i=1;i<L;i<<=1)for(int j=0;j<L;++j)if(i&j)
		a[j]=sub(std::exchange(a[i^j],add(a[i^j],a[j])),a[j]);
}
int f[N];
int main()
{
	int n,sum=0;scanf("%d",&n);for(int i=0;i<(1<<n);++i)scanf("%d",f+i),sum+=f[i];
	ll invs=qpow(sum,mod-2);for(int i=0;i<(1<<n);++i)f[i]=f[i]*invs%Mod;
	FWT(f,1<<n);for(int i=0;i<(1<<n);++i)f[i]=qpow(mod+1-f[i],mod-2);
	FWT(f,1<<n);for(int i=0;i<(1<<n);++i)printf("%d\n",sub(f[0],f[i]));
	return 0;
}
```

---

## 作者：Piggy343288 (赞：0)

FWT 入门题，很适合我这样的蒟蒻。  

首先我们可以轻松的根据转移条件写出来一个优美的函数 $T(i)=1+\sum_{j\oplus k=i}a_kT(j)$，边界为 $T(0)=0$。  

这个方程属于转移带环的 DP，处理方法一般是高斯消元，在这道题里会 T 飞。  

但是我们又注意到后边是一个美丽的异或卷积，因此可以考虑用 FWT 优化转移。根据卷积我们推导 $T=I+T\oplus A$，其中函数 $A$ 代表题目所给的序列。但是这样显然右边多了一个 $2^n$，所以 $T+2^n=I+T\oplus A$，然后根据广义乘法的运算法则，我们认为 $T=\frac{I-2^n}{1-A}$，因此可以直接上下分别 FWT 然后点值相除。  

核心代码如下：  
```cpp
signed main()
{
    cin >> n;
    n = (1 << n);
    long long sum = 0;
    for (int i = 0; i < n; i++)
        cin >> a[i], sum += a[i];
    sum %= mod;
    sum = qpow(sum, mod - 2);
    for (int i = 0; i < n; i++)
        a[i] = 1ll * a[i] * sum % mod;
    a[0] = (a[0] - 1 + mod) % mod;
    b[0] = n - 1;
    for (int i = 1; i < n; i++)
        b[i] = mod - 1;
    fwt(a, 1), fwt(b, 1);
    for (int i = 0; i < n; i++)
        a[i] = 1ll * b[i] * qpow(a[i], mod - 2) % mod;
    fwt(a, -1);
    for (int i = 0; i < n; i++)
        printf("%d\n", (a[i] - a[0] + mod) % mod);
}
```

---

