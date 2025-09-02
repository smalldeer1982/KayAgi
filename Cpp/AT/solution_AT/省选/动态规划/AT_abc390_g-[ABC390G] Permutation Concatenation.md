# [ABC390G] Permutation Concatenation

## 题目描述

给定一个正整数 $N$。

对于长度为 $N$ 的正整数序列 $A = (A_1, A_2, \ldots, A_N)$，定义 $f(A)$ 为通过以下步骤得到的整数：

- 初始化空字符串 $S$。
- 按顺序对 $i = 1, 2, \ldots, N$ 执行以下操作：
  - 将 $A_i$ 视为无前导零的十进制字符串 $T$。
  - 将 $T$ 追加到 $S$ 的末尾。
- 将 $S$ 视为十进制整数，其值即为 $f(A)$。

例如，对于 $A = (1, 20, 34)$，有 $f(A) = 12034$。

考虑 $(1, 2, \ldots, N)$ 的所有 $N!$ 种排列 $P$，求所有 $f(P)$ 的总和对 $998244353$ 取模后的结果。

## 说明/提示

### 约束条件

- $1 \leq N \leq 2 \times 10^5$
- 输入的所有值均为整数

### 样例解释 1

当 $N = 3$ 时，共有 $6$ 种排列：  
$P = (1,2,3), (1,3,2), (2,1,3), (2,3,1), (3,1,2), (3,2,1)$，对应的 $f(P)$ 值分别为 $123, 132, 213, 231, 312, 321$。总和为 $123 + 132 + 213 + 231 + 312 + 321 = 1332$，因此输出 $1332$。

### 样例解释 2

注意输出结果需对 $998244353$ 取模。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3```

### 输出

```
1332```

## 样例 #2

### 输入

```
390```

### 输出

```
727611652```

## 样例 #3

### 输入

```
79223```

### 输出

```
184895744```

# 题解

## 作者：definieren (赞：7)

记 $m = \lfloor \lg n \rfloor$，$a_i = 10^{i+1}$，$b_i = \lvert [10^i, 10^{i + 1}) \cap[1, n] \cap \mathbb Z \rvert$。

不难发现，对于 $[10^i, 10^{i + 1})$ 中的数，它们的贡献系数是相同的，为：

$$
\sum_{0\le j < n} j!(n-j-1)! [x^j] \frac{\prod_{0 \le k \le m} (1+a_kx)^{b_k}}{(1+a_ix)}
$$

那么现在的问题就是要计算出：

$$
F(x) = \prod_{0 \le k \le m} (1+a_k x)^{b_k}
$$

的各项系数。

求导可得：

$$
F' = \sum_{0 \le k \le m} a_kb_k(1+a_kx)^{b_k-1} \prod_{\substack{0 \le j \le m \\ j \neq k}} (1+a_jx)^{b_j}
$$

记：

$$
G(x) = \prod_{0 \le k \le m} (1+a_kx)
$$

那么有：

$$
\begin{aligned}
F' G &= \sum_{0 \le k \le m} a_k b_k \prod_{\substack{0 \le j \le m \\ j \neq k}} (1+a_jx)\prod_{1 \le j \le m} (1+a_jx)^{b_j} \\
&= \left(\sum_{0 \le k \le m} a_k b_k \prod_{\substack{0 \le j \le m \\ j \neq k}} (1+a_jx) \right) F
\end{aligned}
$$

记前面那一坨是 $H$，那么就得到了：

$$
F'G = FH
$$

两边同时提取 $x^n$ 系数可得：

$$
\begin{aligned}
\sum_{0 \le i \le n} (i + 1) f_{i +1} g_{n - i} &= \sum_{0 \le i \le n} f_i h_{n - i} \\
(n+1)f_{n+1}g_0 &= \sum_{0 \le i \le n} f_i h_{n - i} - \sum_{0 \le i < n}(i+1)f_{i+1}g_{n-i} \\
f_{n + 1} &= \frac{1}{(n+1)g_0} \left( \sum_{0 \le i \le n} f_i h_{n - i} - \sum_{0 \le i < n}(i+1)f_{i+1}g_{n-i} \right)
\end{aligned}
$$

由于 $H$ 和 $G$ 都只有 $O(m)$ 项，右边其实只有 $O(m)$ 项，这样就能 $O(n \log n)$ 递推出 $F$ 的各项系数。

然后要算的就是：

$$
\begin{aligned}
P &= \frac{F}{(1+a_ix)} \\
\end{aligned}
$$

的各项系数，这个也可以用类似的方法得到递推式：

$$
\begin{aligned}
(1+a_ix)P &= F \\
p_n+ a_i p_{n-1} &= f_n \\
p_n &= f_n - a_ip_{n-1}
\end{aligned}
$$

可以 $O(n)$ 递推。

时间复杂度 $O(n \log n)$。

[代码](https://atcoder.jp/contests/abc390/submissions/62112226)。

---

## 作者：luanyanjia (赞：3)

这题感觉好难绷。

枚举排列的每一位，然后考虑所有数在这一位时，会对答案总和产生什么贡献。设正在考虑排列的第 $i$ 个数，十进制位数为 $j$ 的数有 $b_j$ 个，总和是 $sum_j$，我们枚举第 $i$ 个数十进制下有多少位，那么这一位答案就是：

$$ i!(n-i-1)! \times \sum_{i=1}^{6} sum_i \sum_{j=1}^{6}{\binom{b_j-[j=i]}{c_j}10^{j\times c_j}}[\sum c_j = n-i]$$

其中 $c_j$ 是位数为 $j$ 的数有多少个放在了后 $n-i$ 个，也就是垫在当前位的后面。要注意的是式子里面 $i=j$ 时，因为少一个数，$b_j$ 要减 $1$。

这里对 $c_j$ 的和做出要求，显然是一个背包问题，可以卷积解决。

设：

$$F_j(x) = \sum\limits_{i=0}^{b_j}{10^{ij}\binom{b_j}{i}x^{i}}$$

$$G_j(x) = \sum\limits_{i=0}^{b_j - 1}{10^{ij}\binom{b_j - 1}{i}x^{i}}$$

$$H_j(x) = \dfrac{\prod\limits_{i=1}^{6} F_i(x)}{F_j(x)} \times G_j(x)$$

那么上式就可以变为：

$$i!(n-i-1)! \times \sum_{i=1}^{6} sum_i [x^{n-i}]H_i(x)$$

数据范围不大，直接 NTT 随便乘就行。时间复杂度 $O(n\log^{3}{n})$，有两个以 $10$ 为底，跑得还蛮快。

别忘了 $2\times 10^5$ 有 $6$ 位。

`atcoder library` 太牛了。

```cpp
#include<bits/stdc++.h>
#include<atcoder/all>
inline void rd(){}
template<typename T,typename ...U>
inline void rd(T &x,U &...args){
    int ch=getchar();
    T f=1;x=0;
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    x*=f;rd(args...);
}
#define int long long
const int N=2e5+5,mod=998244353;
int n,fac[N],sum[10],w[N],cnt[N],inv[N];
inline int ch(int x){
	int ans=0;
	while(x)x/=10,++ans;
	return ans;
}
inline int KSM(int x,int n){
	int ans=1;
	while(n){
		if(n&1)ans=1ll*ans*x%mod;
		x=1ll*x*x%mod;
		n>>=1;
	}return ans;
}
inline int C(int n,int m){
	if(n<m)return 0;
	return 1ll*fac[n]*inv[m]%mod*inv[n-m]%mod;
}
std::vector<int> vc[7],b[7],c[7];
signed main(){
    rd(n);
    fac[0]=inv[0]=1;
    for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    for(int i=1;i<=n;i++)inv[i]=KSM(fac[i],mod-2);
    for(int i=1;i<=n;i++)w[i]=ch(i),(sum[w[i]]+=i)%=mod,cnt[w[i]]++;
    for(int i=1;i<=6;i++){
    	int now=1,bas=std::pow(10,i);
    	for(int j=0;j<=cnt[i];j++){
    		b[i].push_back(now*C(cnt[i],j)%mod);
    		c[i].push_back(now*C(cnt[i]-1,j)%mod);
    		now=now*bas%mod;
		}
		c[i].pop_back();
	}
	for(int i=1;i<=6;i++){
		vc[i].push_back(1);
		for(int j=1;j<=6;j++){
			if(j==i)vc[i]=atcoder::convolution<mod>(vc[i],c[j]);
			else vc[i]=atcoder::convolution<mod>(vc[i],b[j]);
		}
	}
	int ans=0;
    for(int i=0;i<n;i++){
    	for(int j=1;j<=6;j++){
    		if((int)vc[j].size()-1<n-i-1)continue;
    		(ans+=vc[j][n-i-1]*sum[j]%mod*fac[n-i-1]%mod*fac[i]%mod)%=mod;
		}
	}
	printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Nt_Tsumiki (赞：3)

AT 你出这种卡常场还是倒闭算了。

不错的计数练习题。

我们考虑对于相同长度的数字去统计答案，那数字 $i$ 对答案的贡献肯定是形如一个 $\sum 10^a\times b!$ 的形式，其中 $a$ 是 $i$ 在第几位，$b$ 是后面还有几个数，因为阶乘并不好拆，所以我们考虑取枚举后面数的个数，那对于 $\sum 10^a$ 我们考虑去进行 01 背包。

具体的设 $f_{i,j}$ 表示不算第 $i$ 个数前面填了 $j$ 个数的所有情况造成贡献之和，那么答案就是 $\sum_{i=1}^ni\times \sum_{j=0}^{n-1}f_{i,j}(n-j-1)!$，这样直接算是 $O(n^2\log n)$ 的我们考虑优化。

对于 01 背包问题有一个经典的套路是生成函数，那我们设生成函数 $F_i(x)=\prod_{j\ne i}(1+10^{l_j}x)$ 来表示，其中 $l_j$ 是 $j$ 在十进制意义下的长度，那么 $f_{i,n}=[x^n]F_i$。

对于 $F_i$ 的计算我们先设 $F=\prod_{i=1}^n (1+10^{l_i}x)$，不难发现 $F_i=\frac{F}{1+10^{l_i}x}$，所以不妨先来考虑算 $F$，首先因为是若干短多项式相乘所以可以分治 FFT，但是我们可以使用先 $\ln$ 在 $\exp$ 的 trick 做到 1log，具体的有：

$$
\begin{aligned}
F(x)&=\prod_{i=1}^n 1+10^{l_i}x\\
\ln F(x)&=\sum_{i=1}^n\sum_{j\ge 1}\frac{(-1)^{j+1}(10^{l_i}x)^j}{j}\\
\ln F(x)&=\sum_{i\ge 1}\frac{(-1)^{i+1}x^i}{i}\sum_{j=1}^n (10^{l_j})^i\\
F(x)&=\exp \sum_{i\ge 1}\frac{(-1)^{i+1}x^i}{i}\sum_{j=1}^n (10^{l_j})^i
\end{aligned}
$$

对于最后的那个 $\sum$ 不难发现 $10^{l_i}$ 只有本质不同的 $O(\log n)$ 段，对于每段分别计算就行，最后再 $\exp$ 回去就可以做到 1log 了。

然后对于 $F_i=\frac{F}{1+10^{l_i}x}$ 你可以暴力求逆然后做到 2log，但是回顾一下我们 $F_i$ 的含义，他是一个 01 计数背包，所以是支持撤销的，而撤销是 $O(n)$ 的，再算上最外面枚举长度的复杂度就是 $O(n\log n)$ 的。

[submission](https://atcoder.jp/contests/abc390/submissions/62111317)

---

## 作者：_fairytale_ (赞：1)

[ABC390 录播](https://www.bilibili.com/video/BV1HZfZYxEm4/?vd_source=fe2fb3ffe079f3161c3926cbf4149c2d)

记录第一道自己做出来的 poly！

不难看出答案为：

$$
\begin{aligned}
\sum_{x=1}^nx\sum_{j=0}^{n-1}(n-j-1)!j!\sum_{i_1+\dots+i_6=j}\prod_{k=1}^6{a_k\choose i_k}10^{ki_k}
\end{aligned}
$$

其中 $a_i$ 表示去掉 $x$ 后十进制位数为 $i$ 的数的数量。

意思是，我们枚举一个数 $x$，计算出它对答案的贡献，考虑在排列中放在它后面的数，统计在所有方案中它们位数的和：$j$ 表示一共放了多少个数，而 $i_1\dots i_k$ 表示每种长度的数的数量。

可以把 $x$ 按照位数分成 $6$ 组，每组后面的那一坨是一样的。

考虑一个 DP，设 $f_{p,j}$ 表示考虑了 $a_1\dots a_p$ 的数字，已经有 $i_1+\dots+i_p=j$，$j!$ 后面那个式子的总和。

转移时枚举 $t=i_p$：

$f_{p,j}=\sum_{t=0}^{a_p}f_{p-1,j-t}{a_p\choose t}10^{pt}$

发现转移是一个卷积，直接 NTT 即可。

时间复杂度 $\mathcal O(n\log^2n)$，其中第二个 $\log$ 以 $10$ 为底。

```cpp
#include<bits/stdc++.h>
#define rep(x,qwq,qaq) for(int x=(qwq);x<=(qaq);++x)
#define per(x,qwq,qaq) for(int x=(qwq);x>=(qaq);--x)
using namespace std;
#define m998 998244353
#define mod m998
template<typename Tp>
int qp(int x,Tp y) {
	assert(y>=0);
	x%=mod;
	int res=1;
	while(y) {
		if(y&1)res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return res;
}
int inv(int x) {
	return qp(x,mod-2);
}

template <int MOD>
struct modint {
	int val;
	static int norm(const int& x) {
		return x < 0 ? x + MOD : x;
	}
	static constexpr int get_mod() {
		return MOD;
	}
	modint() : val(0) {}
	modint(const int& m) : val(norm(m)) {}
	modint(const long long& m) : val(norm(m % MOD)) {}
	modint operator-() const {
		return modint(norm(-val));
	}
	bool operator==(const modint& o) {
		return val == o.val;
	}
	bool operator<(const modint& o) {
		return val < o.val;
	}
	modint& operator+=(const modint& o) {
		return val = norm(val + o.val-MOD), *this;
	}
	modint& operator-=(const modint& o) {
		return val = norm(1ll * val - o.val), *this;
	}
	modint& operator*=(const modint& o) {
		return val = static_cast<int>(1ll * val * o.val % MOD), *this;
	}
	modint& operator/=(const modint& o) {
		return *this *= o.inv();
	}
	modint& operator^=(const modint& o) {
		return val ^= o.val, *this;
	}
	modint& operator>>=(const modint& o) {
		return val >>= o.val, *this;
	}
	modint& operator<<=(const modint& o) {
		return val <<= o.val, *this;
	}
	modint operator-(const modint& o) const {
		return modint(*this) -= o;
	}
	modint operator+(const modint& o) const {
		return modint(*this) += o;
	}
	modint operator*(const modint& o) const {
		return modint(*this) *= o;
	}
	modint operator/(const modint& o) const {
		return modint(*this) /= o;
	}
	modint operator^(const modint& o) const {
		return modint(*this) ^= o;
	}
	bool operator!=(const modint& o) {
		return val != o.val;
	}
	modint operator>>(const modint& o) const {
		return modint(*this) >>= o;
	}
	modint operator<<(const modint& o) const {
		return modint(*this) <<= o;
	}
	friend std::istream& operator>>(std::istream& is, modint& a) {
		long long v;
		return is >> v, a.val = norm(v % MOD), is;
	}
	friend std::ostream& operator<<(std::ostream& os, const modint& a) {
		return os << a.val;
	}
	friend std::string tostring(const modint& a) {
		return std::to_string(a.val);
	}
	template <typename T>
	friend modint qpow(const modint a, const T& b) {
		assert(b >= 0);
		modint x = a, res = 1;
		for (T p = b; p; x *= x, p >>= 1)
			if (p & 1) res *= x;
		return res;
	}
	modint inv() const {
		return qpow(*this,MOD-2);
	}
};
using M107 = modint<1000000007>;
using M998 = modint<998244353>;

using mint = M998;

struct Combinatorics {
#define Lim 2000000
	int fac[Lim+10],invfac[Lim+10];
	Combinatorics() {
		fac[0]=invfac[0]=1;
		rep(i,1,Lim)fac[i]=1ll*fac[i-1]*i%mod;
		invfac[Lim]=inv(fac[Lim]);
		per(i,Lim-1,1)invfac[i]=1ll*invfac[i+1]*(i+1)%mod;
	}
	mint C(int n,int m) {
		if(n<m||n<0||m<0)return 0;
		return 1ll*fac[n]*invfac[m]%mod*invfac[n-m]%mod;
	}
	int A(int n,int m) {
		if(n<m||n<0||m<0)return 0;
		return 1ll*fac[n]*invfac[n-m]%mod;
	}
} comb;
const mint g=3;
void NTT(vector<mint>&f,const int N,const int op) {
	vector<int>rev(N);
	int t=__lg(N)-1;
	rep(i,0,N-1)rev[i]=(rev[i>>1]>>1)|((i&1)<<t);
	rep(i,0,N-1)if(i<rev[i])swap(f[i],f[rev[i]]);
	for(int n=2; n<=N; n<<=1) {
		mint w1=qpow(op==1?g:g.inv(),(m998-1)/n);
		for(int j=0; j<N; j+=n) {
			//[j,j+n/2)[j+n/2,j+n)
			mint wk=1;
			for(int i=j; i<j+n/2; ++i,wk*=w1) {
				mint f0=f[i],f1=wk*f[i+n/2];
				f[i]=f0+f1,f[i+n/2]=f0-f1;
			}
		}
	}
}
//------------------------------------------------------------------以上是模板
int n;
int a[10];
int lg(int x) {
	int res=0;
	do {
		++res;
		x/=10;
	} while(x);
	return res;
}
vector<mint>f[10];
bool Med;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	rep(i,1,n)++a[lg(i)];
	mint ans=0;
	int N=1;
	while(N<n)N<<=1;
	rep(i,1,6){
		f[i].resize(N);
		rep(j,0,a[i]){
			f[i][j]=comb.C(a[i],j)*qp(10,i*j);
		}
		NTT(f[i],N,1);
	}
	mint iv=(mint)1/N;
	rep(i,1,6) {
		--a[i];
		fill(f[i].begin(),f[i].end(),0);
		rep(k,0,a[i])f[i][k]=comb.C(a[i],k)*qp(10,i*k);
		NTT(f[i],N,1);
		vector<mint>F=f[1];
		rep(j,2,6)rep(p,0,N-1)F[p]*=f[j][p];
		NTT(F,N,-1);
		rep(p,0,N-1)F[p]*=iv;
		mint sum=0;
		rep(j,1,n)if(lg(j)==i)sum+=j;
		rep(j,0,n-1)ans+=F[j]*comb.fac[j]*sum*comb.fac[n-j-1];
		++a[i];
		fill(f[i].begin(),f[i].end(),0);
		rep(k,0,a[i])f[i][k]=comb.C(a[i],k)*qp(10,i*k);
		NTT(f[i],N,1);
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

大家好，我在上一场 ABC 的同位置题目提供了一个少一个量级但极其不好想的做法，于是我在这一场 ABC 这道题目写了一个极其好想但比大家都多一个 $\log$ 的做法（虽然但是，黑题难度）。

**（仅限此做法）前置知识：快速数论变换、组合计数。**

我们单独分析 $1$ 到 $n$ 中的一个整数对答案的贡献。显而易见，如果一个排列里这个整数后面的所有数字**数位数量**之和为 $x$，那么它对答案的贡献即为 $10^x$ 倍的自己。

预处理出 $[1,n]$ 的整数的数位数量（$X$ 的数位数量记为 $d_X$），以及数位数量为 $1$ 到 $6$ 且属于 $[1,n]$ 的整数数量，记为 $c_1,c_2,c_3,c_4,c_5,c_6$。

如果我们只看一个数 $X$ 的贡献，那么可以放到它后面的数字就要排除掉自己，所以**临时**将 $c_{d_X}$ 减去 $1$。

不考虑前后数字之间的顺序以及最后一步的乘 $X$ 加答案，只考虑每个数字放在 $X$ 后面还是前面，那么对于 $i,1\le i\le 6$，将 $j$ 个数位数量为 $i$ 的数字放在 $X$ 后的**方案数**为 $C_{c_i}^j$，贡献为 $10^{ij}$，于是我们计生成函数：

$$F_i(x)=\sum_{j=0}^{c_i} 10^{ij}C_{c_i}^j x^j$$

而 $[x^j]F_i(x)$ 的组合意义指的就是 $X$ 后有 $j$ 个**数位数量**为 $i$ 的数的贡献。我们把 $6$ 个生成函数卷积起来得到函数 $H(x)$，那么 $[x^j]H(x)$ 的组合意义指的也就是 $X$ 后有 $j$ 个数的贡献了。

数字 $X$ 如果后面有 $j$ 个数，那么前面就有 $n-1-j$ 个数。由于我们先前没有考虑前面的和后面的所有数之间的顺序关系，所以这一步的方案数即为 $j!(n-1-j)!$。总方案数就是：

$$\sum_{i=0}^{n-1}i!(n-1-i)![x^i]H(x)$$

算答案时别忘乘上 $X$。

接着，我们又发现 $d_X$ 最多只有 $6$，所以我们把 $c_1,c_2,c_3,c_4,c_5,c_6$ 临时减 $1$ 的情况统统预处理出来，得到总方案数后遍历 $[1,n]$ 的整数再算就是了。

时间复杂度是高贵的 $O(n\log^2 n)$，但是过了就行。

```cpp
#include<bits/stdc++.h>
#define lglg long long
#define inth __int128
using namespace std;

int n,decn[200005],num[10];lglg mi10[1200005],lins[1000005],jc[200005],njc[200005],xs[7],ans;signed R[8388608];
const lglg modp=998244353;

template<typename tnt>tnt qpow(tnt now,lglg mi,tnt M){
	tnt ans=1;
	while(mi){
		if(mi&1)ans=ans*now%M;
		mi>>=1;now=now*now%M;
	}
	return ans;
}

template<typename tnt,const tnt P,const unsigned siz>struct prime_group{
	tnt g,w[siz],lins[siz];
	prime_group(){
		vector<int>V;int rem=P-1,fst;
		for(int i=2;i*i<=rem;i++){
			if(rem%i==0){
				V.push_back(i);while(rem%i==0)rem/=i;
			}
		}
		if(rem^1)V.push_back(rem);
		g=1;
		while(1){
			bool satis=1;
			for(auto uu:V)if(qpow(g,(P-1)/uu,P)==1){
				satis=0;break;
			}
			if(satis)break;
			g++;
		}
		fst=qpow(g,(P-1)/siz,P);w[0]=1;
		for(int i=1;i<siz;i++)w[i]=w[i-1]*fst%P;
	}
};

prime_group<lglg,998244353,8388608>naotantan;

template<typename tnt,const tnt P,const unsigned maxsiz,const prime_group<tnt,P,maxsiz>*grp>struct ntt_function{
	unsigned siz;vector<tnt>a;
	ntt_function(){siz=0;}
	void append(int wsiz){while(siz<wsiz){siz++;a.push_back(0);}}
	void disappend(int wsiz){while(siz>wsiz){siz--;a.pop_back();}}
	void dissappend(){while(siz>0&&a.back()==0){siz--;a.pop_back();}}
	void autoappend(){
		int cur=1;while(cur<siz)cur<<=1;
		append(cur);
	}
	unsigned size(){return siz;}
	void clear(){disappend(0);}
	void NTT(int direction){
		autoappend();
		for(int i=0;i<siz;i++)lins[i]=a[i];
		for(int i=0;i<siz;i++){
			int targ=R[i*(8388608/siz)];
			if(i<targ)swap(lins[i],lins[targ]);
		}
		for(int dd=2,d=1;dd<=siz;dd<<=1,d<<=1){
			for(int i=0;i<siz;i+=dd){
				for(int j=0;j<d;j++){
					tnt rem=lins[i+j+d]*(grp->w[maxsiz/dd*j])%P;
					lins[i+j+d]=(lins[i+j]+P-rem)%P;lins[i+j]=(lins[i+j]+rem)%P;
				}
			}
		}
		if(direction==-1){
			tnt ni=qpow((tnt)siz,P-2,P);
			for(int o=1;o*2<siz;o++)swap(lins[o],lins[siz-o]);
			for(int o=0;o<siz;o++)lins[o]=lins[o]*ni%P;
		}
		for(int i=0;i<siz;i++)a[i]=lins[i];
	}
	ntt_function<tnt,P,maxsiz,grp>operator*(const ntt_function<tnt,P,maxsiz,grp>&R)const{
		ntt_function<tnt,P,maxsiz,grp>xx,yy;
		xx=*this;yy=R;xx.append(siz+R.siz-1);yy.append(siz+R.siz-1);
		xx.NTT(1);yy.NTT(1);
		for(int o=0;o<xx.siz;o++)xx.a[o]=xx.a[o]*yy.a[o]%P;
		xx.NTT(-1);xx.disappend(siz+R.siz-1);return xx;
	}
};

ntt_function<lglg,998244353,8388608,&naotantan>F[7],G[7],H[7];

signed main(){
	for(int i=1;i<8388608;i++)R[i]=(R[i>>1]>>1)+((i&1)<<22);
	cin>>n;for(int i=1;i<=n;i++)num[decn[i]=decn[i/10]+1]++;
	mi10[0]=1;for(int i=1;i<=1200000;i++)mi10[i]=mi10[i-1]*10%modp;
	jc[0]=1;for(int i=1;i<=n;i++)jc[i]=jc[i-1]*i%modp;
	njc[n]=qpow(jc[n],modp-2,modp);for(int i=n;i>=1;i--)njc[i-1]=njc[i]*i%modp;
	for(int i=1;i<=6;i++){F[i].append(200005);G[i].append(200005);}
	for(int i=1;i<=6;i++){
		for(int j=0;j<=num[i];j++)F[i].a[j]=jc[num[i]]*njc[num[i]-j]%modp*njc[j]%modp*mi10[i*j]%modp;
		int cur=max(0,num[i]-1);
		for(int j=0;j<=cur;j++)G[i].a[j]=jc[cur]*njc[cur-j]%modp*njc[j]%modp*mi10[i*j]%modp;
		F[i].NTT(1);G[i].NTT(1);
	}
	for(int i=1;i<=6;i++){
		H[i].append(F[i].size());
		for(int o=0;o<H[i].size();o++){
			H[i].a[o]=1;
			for(int j=1;j<=6;j++){
				if(i==j)(H[i].a[o]*=G[j].a[o])%=modp;
				else(H[i].a[o]*=F[j].a[o])%=modp;
			}
		}
		H[i].NTT(-1);
		for(int o=0;o<n;o++)(xs[i]+=H[i].a[o]*jc[o]%modp*jc[n-1-o])%=modp;
	}
	for(int i=1;i<=n;i++)(ans+=xs[decn[i]]*i)%=modp;
	cout<<ans;
	return 0;
}
```

---

## 作者：xiezheyuan (赞：0)

## 简要题意

对于一个排列 $p$，定义 $f(p)$ 表示排列的每一个数按顺序依次拼接得到的十进制数。

你需要计算对于所有长度为 $n$ 的排列 $p$ 的 $f(p)$ 之和。答案对 $998,244,353$ 取模。

$1\leq n\leq 2\times 10^5$。

## 思路

约定几个符号：

- $\lambda(x)=\lfloor\lg x\rfloor+1$ 也就是 $x$ 在十进制下的数位数。
- $\Lambda(x)=10^{\lambda(x)}$。

先拆贡献，记 $\rho(x)$ 为 $x$ 的贡献，则有：

$$
\rho(x)=\sum_{i=0}^{n-1}i!(n-i-1)!\cdot [z^i]\prod_{j\in[1,n],j\neq x} (1+\Lambda(j)z)
$$

即枚举 $x$ 为倒数第 $i+1$ 个数，然后钦定后面 $i$ 个数的选法（那么前面的选法也就随之确定了，最后注意要乘上的不是方案数而是移位贡献），最后乘上阶乘表示顺序。最后答案就是 $\sum_i i\rho(i)$。

考察：

$$
\begin{aligned}
\mathbf{F}(z)&=\prod_{i=1}^{n} (1+\Lambda(i)z)\\
&=\exp\left(\sum_{i=1}^{n}\ln(1+\Lambda(i)z)\right)\\
&=\exp\left(-\sum_{i=1}^{n}\sum_{j\geq 1} \frac{(-1)^j}{j} (\Lambda(i)z)^j\right)\\
&=\exp\left(-\sum_{j\geq 1}\frac{(-1)^j}{j}z^j\sum_{i=1}^{n}\Lambda^j(i)\right)\\
&=\exp\left(-\sum_{j\geq 1}\frac{(-1)^j}{j}z^j\sum_{i=1}^{\lambda(n)}10^{ij}\sum_{k=1}^{n}[\lambda(k)=i]\right)
\end{aligned}
$$

于是可以 $O(n\log n)$ 求出 $\mathbf{F}(z)$。

然后我们考虑原式：

$$
\rho(x)=\sum_{i=0}^{n-1}i!(n-i-1)!\cdot [z^i](\mathbf{F}(z)\cdot (1+\Lambda(x)z)^{-1})
$$

注意到自变量其实可以改为 $\lambda(x)$，于是定义 $\rho(x)=\Rho(\lambda(x))$：

$$
\Rho(x)=\sum_{i=0}^{n-1}i!(n-i-1)![z^i](\mathbf{F}(z)\cdot (1+10^xz)^{-1})
$$

于是我们只需要高效求出 $[z^i](\mathbf{F}(z)\cdot (1+10^xz)^{-1})$ 即可。

注意到 $(1+10^xz)^{-1}=\sum_{i\geq 0}(-10^x)^iz^i$，直接卷积即可。时间复杂度 $O(n\log^2 n)$。

[Submission](https://atcoder.jp/contests/abc390/submissions/64014295)。

---

## 作者：TLE_Automat (赞：0)

令 $sum_i$ 为位数为 $i$ 的所有数之和，$tot_i$ 为位数为 $i$ 的数的个数，$m$ 表示 $n$ 的位数。

令
$$
\begin{aligned}
F(x) = \prod_{i = 0}^{m} (1 + 10^{i}x)^{tot_i}
\end{aligned}
$$
考虑每一项的含义，$(1 + 10^{i}x)$ 中的 $1$ 表示下方不选这个数的贡献，$10^{i}x$ 表示下方选了这个数的贡献，$tot_i$ 作为指数代表有 $tot_i$ 个位数为 $i$ 的数可供选择。

于是可以自然地得到 $[x^j]F(x)$ 的含义为下方选了 $j$ 个数所产生的贡献之和。

考虑枚举位数为 $i$ 的数卡在中间产生的贡献：（注意我们钦定一个位数为 $i$ 的数卡在中间，所以有一个位数为 $i$ 的数不能自由选择，所以 $F(x)$ 中要少乘一项 $(1 + 10^{i}x)$）
$$
\begin{aligned}

\sum_{i = 0}^{m} sum_i \sum_{j = 1}^{n} j!(n - j - 1)![x^{j}]\frac{F(x)}{1 + 10^{i}x}

\end{aligned}
$$
注意到 $m = log_n$，所以 $i,j$ 可以暴力枚举，难点在于算出后面的多项式。

对后面的多项式取 $\ln$ 可得
$$
\begin{aligned}

\ln\frac{F(x)}{1 + 10^{i}x} = \left[\sum_{j = 0}^{m}tot_{j}\ln(1 + 10^{j}x)\right] - \ln(1 + 10^{i}x)

\end{aligned}
$$
由泰勒展开
$$
\ln(1 + x) = \sum_n(-1)^{n - 1}\frac{x^{n}}{n}
$$
故原式等于
$$
\begin{aligned}

\left[\sum_{j = 0}^{m}tot_{j}\sum_{k = 0}^{\infty}(-1)^{k}\frac{(10^{j}x)^{k}}{k}\right] - \sum_{k = 0}^{\infty}(-1)^{k}\frac{(10^{i}x)^{k}}{k}

\end{aligned}
$$
因为取 $[x^j]$ 时 $j$ 不会超过 $n$，所以 $k$ 枚举到 $n$ 即可，这个式子可以 $O(nm)$ 计算，算完了再 $\exp$ 回去即可。

这样总时间复杂度是 $O(nm^{2} + n\log n) = O(n\log^{2}n)$。

---

## 作者：analysis (赞：0)

观前提示：$3 \times 10^5$ 是 $6$ 个数，而不是 $5$ 个（不要问为什么要提示）。

* * *

考虑先求出 $len_i$ 表示长度为 $i$ 的数有多少个，以及 $s_i$ 表示长度为 $i$ 的数之和。

我们对数 $x$ 统计其造成的所有贡献，可以写出（注意 $x$ 对应的 $len$ 要减 $1$）：

$$
\sum_{\{v_i\}}(x\prod_{i=1}^{6}(10^{i})^{v_i})(\prod_{i=1}^{6}\binom{len_i}{v_i})(\sum v_i)!(n-1-\sum v_i)!
$$

稍微解释下，枚举每种数有多少个在 $x$ 之前，然后贡献就是 $(x\prod_{i=1}^{6}(10^{i})^{v_i})$，方案数就是 $(\sum v_i)!(n-1-\sum v_i)!$。

整理一下：

$$
\sum_{\{v_i\}}x(\prod_{i=1}^{6}(10^{i})^{v_i}\binom{len_i}{v_i})(\sum v_i)!(n-1-\sum v_i)!
$$

设哑元 $L(u^i)=i!(n-1-i)!$，根据线性性，原式：

$$
x\sum_{\{v_i\}}(\prod_{i=1}^{6}\binom{len_i}{v_i}(10^iu)^{v_i})\\=x\prod_{i=1}^{6}(1+10^iu)^{len_i}
$$

直接对同一类数求和，答案就是：

$$
\sum_{i=1}^{6}s_i\prod_{j=1}^{6}(1+10^ju)^{len_j-[j=i]}\\ans=\sum_{i=1}^{6}\sum_{k=0}^{n-1}s_ik!(n-1-k)![u^k]\prod_{j=1}^{6}(1+10^ju)^{len_j-[j=i]}
$$

具体求解可以先快速幂 $O(n\log^{2}{n})$ 求出，再除掉一个 $(1+10^{i}u)$，容易做到 $O(n)$。

时间复杂度就是 $O(n\log^2{n}+V(n+k)),V=6$。

---

