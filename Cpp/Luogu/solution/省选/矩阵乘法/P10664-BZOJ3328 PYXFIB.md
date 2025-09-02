# BZOJ3328 PYXFIB

## 题目描述

给定整数 $n,k,p$，要求计算下列式子对 $p$ 取模的值：

$$\sum_{i=0}^{\lfloor \frac{n}{k} \rfloor} C_n^{i\times k}\times F_{i\times k}$$

其中：
- $p$ 为质数，且 $p$ 除以 $k$ 的余数为 $1$。
- $C$ 为组合数，即 $C_m^n=\frac{n!}{m!(n-m)!}$。
- $F_n$ 为斐波那契数列，即 $F_0=1$，$F_1=1$，$F_n=F_{n-1}+F_{n-2}(n\geq 2)$。

## 说明/提示

对于 $100\%$ 的数据，保证 $1\leq n\leq 10^{18}$，$1\leq k \leq 20000$，$1\leq T\leq 20$，$1\leq p\leq 10^9$，$p$ 为质数，且 $p$ 除以 $k$ 的余数为 $1$。

## 样例 #1

### 输入

```
1
1 2 3```

### 输出

```
1```

# 题解

## 作者：Purslane (赞：7)

# Solution

单位根反演！

-------

式子有点过于不优美了，转化为：

$$
\sum_{i=0}^n [k \mid i] \dbinom{n}{i} F_i
$$

对 $[k \mid i]$ 使用单位根反演，设 $\omega$ 是一个 $k$ 次本原单位根，则

$$
\begin{aligned}
& \sum_{i=0}^n [k \mid i] \dbinom{n}{i} F_i \\
=& \sum_{i=0}^n (\dfrac{1}{k}\sum_{j=0}^{k-1} \omega^{ij}) \dbinom{n}{i} F_i \\
=& \dfrac{1}{k}\sum_{j=0}^{k-1} \sum_{i=0}^n (\omega^j)^i \dbinom{n}{i}F_i
\end{aligned}
$$

这个形式很像二项式定理。

设 $M = \left[ \begin{matrix}1 & 1\\ 1 & 0 \end{matrix} \right]$，那么 $F_i = \left[ \begin{matrix} 1&0\end{matrix} \right] (M^i \left[ \begin{matrix}1 \\ 0 \end{matrix} \right])$，所以我们本质上对每个 $j$ 求出

$$
\sum_{i=0}^n \dbinom{n}{i}(\omega^jM)^i
$$

即可。矩阵和 $I$ 相乘是有交换律的，因此可以使用二项式定理，得到 $(I + \omega^j M)^n$，容易使用矩阵快速幂优化。

---------

所以 $\omega$ 是多少？现在是模意义，我们要求 $x^k \equiv 1 \pmod p$ 的一个根，其中 $x \neq 1$。

设 $g$ 是 $p$ 的一个原根，有 $(g^{\frac{p-1}{k}})^k \equiv 1 \pmod p$，令 $\omega \equiv g^{\frac{p-1}{k}} \pmod p$ 即可。

> 由于题目保证 $k \mid p-1$，这个高次同余方程有解。

Fun Fact：我不会枚举一个数得所有质因数，看来实际 CCF 评级只有 $3$ 级。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
int T,k,p;
ll n;
vector<int> frac;
inline int qpow(int base,int d) {
	int ans=1;
	while(d) {
		if(d&1) ans=1ll*ans*base%p;
		base=1ll*base*base%p,d>>=1;
	}
	return ans;
}
inline int check_gen(const int v) {
	ffor(i,0,(int)frac.size()-1) if(qpow(v,(p-1)/frac[i])==1) return 0;
	return 1;
}
int calc_gen(void) {
	ffor(i,2,p) if(check_gen(i)) return i;	
}
struct Matrix {int v[2][2];};
Matrix operator *(Matrix A,Matrix B) {
	Matrix C; memset(C.v,0,sizeof(C.v));
	ffor(i,0,1) ffor(j,0,1) ffor(k,0,1) C.v[i][k]=(C.v[i][k]+1ll*A.v[i][j]*B.v[j][k])%p;
	return C;	
}
Matrix operator ^(Matrix A,ll n) {
	Matrix C; C.v[0][0]=C.v[1][1]=1,C.v[0][1]=C.v[1][0]=0;
	while(n) {
		if(n&1) C=C*A;
		A=A*A,n>>=1;
	}
	return C;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) {
		cin>>n>>k>>p,frac.clear();
		int v=p-1;
		ffor(i,2,v/i) if(v%i==0) {
			frac.push_back(i);
			while(v%i==0) v/=i;	
		}
		if(v>1) frac.push_back(v);
		int ans=0,g=calc_gen(),w=qpow(g,(p-1)/k);
		ffor(j,0,k-1) {
			Matrix mt;
			mt.v[0][0]=mt.v[0][1]=mt.v[1][0]=qpow(w,j),mt.v[1][1]=0;
			mt.v[0][0]++,mt.v[1][1]++;
			mt=mt^n;
			ans=(ans+mt.v[0][0])%p;
		}
		ans=1ll*ans*qpow(k,p-2)%p;
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：mEden (赞：4)

本题拥有规模非常庞大的前置知识：

> 数位 dp，卢卡斯定理，BSGS 算法或者 Cipolla 算法，费马小定理，原根存在定理，单位根反演，斐波那契数列通项公式。

好在都不是什么大科技或者怪癖的定理，但还是请查漏补缺。

第一步，我们看到以下的式子应该立即警觉起来：

$$\sum_{i=0}^{\lfloor\frac{n}{k}\rfloor}C_n^{ik}F_{ik}$$

$ik$ 被绑在一起，明摆着想让我们替换掉。新的式子即为：

$$\sum_{i=0}^n [k|i]C_n^i F_i$$

其中 $[b]$ 在 $b$ 为真时取 $1$，否则取 $0$。

第二步，我们套用一下斐波那契数列的通项公式（这里的数列索引从 $0$ 开始，比较难缠）：

$$F_i=\frac{1}{\sqrt5}(\phi^{i+1}-{\phi^{\prime}}^{i+1})$$

其中 $\phi=\frac{1}{2}(1+\sqrt5),\phi^{\prime}=\frac{1}{2}(1-\sqrt5)$。

这道题目在 $n\le 10^{18}$ 的时候还不是很可做，但是我们可以看到，$k|(p-1)$。

接下来我们引入一个科技——**单位根反演**：设 $\omega_k$ 满足 $\omega_k^k=1$ 且 $\forall 0<i<k,\omega_k^i\not=1$（乘法运算需满足结合律，且除零外的元素均存在存在乘法逆元），那么对于整数 $i$ 有：

$$[k|i]=\frac{1}{k}\sum_{t=0}^{k-1}(\omega_k^t)^i$$

而 $\omega_k^0,\omega_k^1,\dots,\omega_k^{k-1}$ 这 $k$ 个值就被称为 $k$ 次单位根，它们的 $k$ 次方都是 $1$。以下是这个定理的极其简要证明：

若 $k|i$，则 $\frac{1}{k}\sum\limits_{t=0}^{k-1}(\omega_k^t)^i=\frac{1}{k}\sum\limits_{t=0}^{k-1}(\omega_k^k)^{\frac{it}{k}}=1$。

否则 $\omega_k^i\not=1$，$\frac{1}{k}\sum\limits_{t=0}^{k-1}(\omega_k^t)^i=\frac{1}{k}\frac{(\omega_k^i)^k-1}{(\omega_k^i)-1}=0$。

而根据原根存在定理。由于 $p$ 是素数，所以我们可以找到一个整数 $g,(g,p)=1$，使得 $\forall 0<t<p-1,g^t\bmod p\not=1$，我们称之为原根。于是我们可以取 $w_k=g^{\frac{p-1}{k}}$，而其满足条件的证明极其明显。

我们能感觉到后面要利用好单位根，所以我们需要先把 $\frac{1}{2}$ 或者 $\sqrt5$ 难处理的部分特判掉——$p=2$ 或 $p=5$：

这时斐波那契数列值模 $2$ 构成的数列拥有一个长度仅为 $3$ 的循环节：$1,1,0$，模 $5$ 构成的数列拥有一个长度仅为 $20$ 的循环节。根据卢卡斯定理：

$$C_n^m\bmod p=(\prod_t C_{n_t}^{m_t})\bmod p$$

其中 $n_t,m_t$ 表示 $n,m$ 在 $p$ 进制下的第 $t$ 位。这样我们就可以使用数位 dp，设 $f_{i,j}$ 为处理前 $i$ 位，它们对应值模循环节为 $j$ 时 $\prod_{0\le t<i} C_{n_t}^{m_t}$ 的和模 $p$ 来碾平了。

判掉 $p=2$ 或 $p=5$ 后，原式即为：

$$\sum_{i=0}^n [k|i]C_n^i F_i=\frac{1}{\sqrt5}\sum_{i=0}^n\sum_{t=0}^{k-1}C_n^i(\phi^{i+1}-{\phi^{\prime}}^{i+1})(\omega_k^t)^i=\frac{1}{\sqrt5}(\phi\sum_{i=0}^n\sum_{t=0}^{k-1}C_n^i(\phi\omega_k^t)^i-\phi^{\prime}\sum_{i=0}^n\sum_{t=0}^{k-1}C_n^i(\phi^{\prime}\omega_k^t)^i)$$

$$\frac{1}{\sqrt5}(\phi\sum_{i=0}^n\sum_{t=0}^{k-1}C_n^i(\phi\omega_k^t)^i-\phi^{\prime}\sum_{i=0}^n\sum_{t=0}^{k-1}C_n^i(\phi^{\prime}\omega_k^t)^i)=\frac{1}{\sqrt5}(\phi\sum_{t=0}^{k-1}(\phi\omega_k^t+1)^n-\phi^{\prime}\sum_{t=0}^{k-1}(\phi^{\prime}\omega_k^t+1)^n)$$

这样只需要在 $5$ 是模 $p$ 的二次剩余时求出 $\sqrt5$，在是模 $p$ 的非二次剩余时使用扩域即可。

单组数据时间复杂度：

- $p=2$ 或 $p=5$ 时：你管这点微不足道的时间复杂度干嘛，我都没法写成什么有头有脸的样子。

- 其他情况：$O(\sqrt p+g_{\min}\log p\log\log p+k\log n)$。

以下是代码：

```cpp
#include<bits/stdc++.h>
#define maxm 65536
#define int long long
using namespace std;

int T,n,K,modp,G,GG,om[20005],mi,bg5,gen5,ans;
int dp[63][20],C[5][5],wcnm[20]={1,1,2,3,0,3,3,1,4,0,4,4,3,2,0,2,2,4,1,0};
vector<int>PV;unordered_map<int,int>M;

struct d5rg{
	int rel,img;d5rg(){rel=img=0;}d5rg(int R){rel=R;img=0;}d5rg(int R,int I){rel=R;img=I;}
	d5rg operator+(const d5rg&R)const{return d5rg((rel+R.rel)%modp,(img+R.img)%modp);}
	d5rg operator+(const int&R)const{return d5rg((rel+R)%modp,img%modp);}
	d5rg operator-(const d5rg&R)const{return d5rg((rel+modp-R.rel)%modp,(img+modp-R.img)%modp);}
	d5rg operator*(const int&R)const{return d5rg(rel*R%modp,img*R%modp);}
	d5rg operator*(const d5rg&R)const{return d5rg((rel*R.rel+5*img*R.img)%modp,(rel*R.img+img*R.rel)%modp);}
};

int qpow(int now,int mi){
	int cans=1;for(;mi;mi>>=1,(now*=now)%=modp)if(mi&1)(cans*=now)%=modp;
	return cans;
}

d5rg qpow(d5rg now,int mi){
	d5rg cans(1,0);for(;mi;mi>>=1,now=now*now)if(mi&1)cans=cans*now;
	return cans;
}

int BSGS(int xx){
	for(int i=0;;i++,(xx*=mi)%=modp)if(M.find(xx)!=M.end())return i*maxm+M[xx];
}

signed main(){
	cin>>T;
	for(int i=0;i<5;i++){C[i][0]=1;for(int j=1;j<5;j++)C[i][j]=(C[i-1][j-1]+C[i-1][j])%5;}
	while(T--){
		cin>>n>>K>>modp;
		if(modp==2){
			dp[0][0]=1;
			for(int o=0;o<62;o++)for(int oo=0;oo<3;oo++){
				if(n&(1ll<<o)){dp[o+1][(oo+1+(o&1))%3]^=dp[o][oo];dp[o+1][oo]^=dp[o][oo];}
				else dp[o+1][oo]^=dp[o][oo];
			}
			cout<<(dp[62][0]^dp[62][1])<<'\n';
			for(int o=0;o<=62;o++)for(int oo=0;oo<3;oo++)dp[o][oo]=0;
			continue;
		}
		if(modp==5){
			dp[0][0]=1;
			for(int o=0,cur=1;o<22;o++)for(int oo=0;oo<20;oo++){
				int tt=n/cur%5;for(int i=0;i<5;i++)(dp[o+1][(oo+(cur*i))%20]+=dp[o][oo]*C[tt][i])%=5;
			}
			int cans=0;for(int oo=0;oo<20;oo+=K)(cans+=dp[22][oo]*wcnm[oo])%=5;cout<<cans<<'\n';
			for(int o=0;o<=22;o++)for(int oo=0;oo<20;oo++)dp[o][oo]=0;
			continue;
		}
		int rem=modp-1;
		for(int i=2;i*i<=rem;i++){
			if(rem%i)continue;PV.push_back(i);while(rem%i==0)rem/=i;
		}
		if(rem>1)PV.push_back(rem);
		for(G=1;;G++){
			bool satis=1;for(auto uu:PV)satis&=(qpow(G,(modp-1)/uu)!=1);
			if(satis)break;
		}
		GG=qpow(G,(modp-1)/K);om[0]=1;for(int i=1;i<K;i++)om[i]=om[i-1]*GG%modp;
		mi=1;for(int i=0;i<maxm;i++){M[mi]=i;(mi*=G)%=modp;}mi=qpow(mi,modp-2);
		bg5=BSGS(5%modp);
		if(bg5%2==0){
			gen5=qpow(G,bg5/2);int fai=(1+gen5)*((modp+1)/2)%modp,faib=(modp+1-gen5)*((modp+1)/2)%modp,ans1=0,ans2=0;
			for(int i=0;i<K;i++){(ans1+=qpow(fai*om[i]%modp+1,n))%=modp;(ans2+=qpow(faib*om[i]%modp+1,n))%=modp;}
			ans=(ans1*fai+ans2*(modp-faib))%modp*qpow(gen5,modp-2)%modp;
		}
		else{
			d5rg fai((modp+1)/2,(modp+1)/2),faib((modp+1)/2,(modp-1)/2),ans1,ans2;
			for(int i=0;i<K;i++){ans1=(ans1+qpow(fai*om[i]+1,n));ans2=(ans2+qpow(faib*om[i]+1,n));}
			ans=(ans1*fai+ans2*faib*(modp-1)).img;
		}
		cout<<ans*qpow(K,modp-2)%modp<<'\n';PV.clear();M.clear();
	}
	return 0;
}
```

---

## 作者：xiezheyuan (赞：1)

## 简要题意

给定 $n,k,p$，计算：

$$
\sum_{i=0}^{\lfloor\frac{n}{k}\rfloor} \binom{n}{ik} \mathrm{fib}(i) \pmod{p}
$$

其中 $\mathrm{fib}(i)$ 表示 Fibonacci 数列，定义为 $\mathrm{fib}(0)=\color{red}\mathbf{1}\color{default}, \mathrm{fib}(1)=1, \mathrm{fib}(n)=\mathrm{fib}(n-1)+\mathrm{fib}(n-2)$。

$T$ 组数据，$1\leq T\leq 20,1\leq n\leq 10^{18},1\leq k\leq 2\times 10^4,1\leq p\leq 10^9,p\in\mathbb{P},k\mid p-1$。

## 思路

考虑我们如何求 Fibonacci 数列的，经典求法是矩阵快速幂：

$$
\mathrm{fib}(n)=\left(\begin{bmatrix}1&1\end{bmatrix}\cdot \begin{bmatrix}1&1\\1&0\end{bmatrix}^n\right)_{12}
$$

那么我们可以改为求：

$$
\sum_{i=0}^{\lfloor\frac{n}{k}\rfloor}\binom{n}{ik}\left(\begin{bmatrix}1&1\end{bmatrix}\cdot \begin{bmatrix}1&1\\1&0\end{bmatrix}^i\right)=\begin{bmatrix}1&1\end{bmatrix}\sum_{i=0}^{\lfloor\frac{n}{k}\rfloor} \binom{n}{ik}\begin{bmatrix}1&1\\1&0\end{bmatrix}^i
$$

接下来就是平凡的推式子了：

$$
\begin{aligned}
&\sum_{i=0}^{\lfloor\frac{n}{k}\rfloor} \binom{n}{ik}\begin{bmatrix}1&1\\1&0\end{bmatrix}^i\\
=&\sum_{i=0}^{n}\binom{n}{i}\begin{bmatrix}1&1\\1&0\end{bmatrix}^i[k\mid i]\\
=&\frac{1}{k}\sum_{i=0}^{n}\binom{n}{i}\begin{bmatrix}1&1\\1&0\end{bmatrix}^i\sum_{j=0}^{k-1} \omega_k^{ij}\\
=&\frac{1}{k}\sum_{j=0}^{k-1}\sum_{i=0}^{n}\binom{n}{i}\left(\omega_k^{j}\begin{bmatrix}1&1\\1&0\end{bmatrix}\right)^i\\
=&\frac{1}{k}\sum_{j=0}^{k-1}\left(\begin{bmatrix}1&0\\0&1\end{bmatrix}+\omega_k^{j}\begin{bmatrix}1&1\\1&0\end{bmatrix}\right)^n
\end{aligned}
$$

使用矩阵快速幂实现，时间复杂度 $O(k\log n)$。最后我们还需要找出有限域 $\mathbb{Z}/p\mathbb{Z}$ 中的本原单位根 $\omega_k$。只需要找到一个模 $p$ 意义下原根 $g$，就可以计算 $g^{\frac{p-1}{k}}$ 并用它替代 $k$ 次本原单位根。寻找原根的时间复杂度是 $O(\sqrt{p}+g_{\min}(p)\omega(p-1)\log p)$。

- 根据 [Hardy–Ramanujan Theorem](https://en.wikipedia.org/wiki/Hardy%E2%80%93Ramanujan_theorem)，$\omega(p-1)$ 平均规模为 $O(\log \log p)$，值得注意点是，最大值为 $O(\frac{\log p}{\log\log p})$。
- 如果你承认 GRH，那么根据 [Shoup, V. (1992). Searching for primitive roots in finite fields. Mathematics of Computation, 58(197), 369-380](https://www.ams.org/journals/mcom/1992-58-197/S0025-5718-1992-1106981-9/S0025-5718-1992-1106981-9.pdf) 的结果，$g_{\min}(p)\sim o(\log^6 p)$。
- [Kevin J. McGown, Jonathan P. Sorenson Computation of the least primitive root](https://arxiv.org/abs/2206.14193) 给出了当 $1\leq p\leq 10^9$ 时，$g_{\min}(p)\leq 151$。

## 代码

```cpp
#include <bits/stdc++.h>
#define _all(x) std::begin(x), std::end(x)
using std::cin, std::cout;

int mod;
int A(int x, int y){ return (x + y) >= mod ? (x + y - mod) : (x + y); }
int S(int x, int y){ return (x - y) < 0 ? (x - y + mod) : (x - y); }
int M(int x, int y){ return 1ll * x * y % mod; }
int P(int x, int y){ int ans = 1; for(;y;x=M(x,x),y>>=1) if(y & 1) ans = M(ans, x); return ans; }

template<int N>
struct matrix {
    int a[N][N], n, m;
    matrix(int n, int m) : n(n), m(m) { memset(a, 0, sizeof(a)); }
    int* operator[](int i){ return a[i]; }
    const int* operator[](int i) const { return a[i]; }
    matrix operator+(const matrix& b){
        matrix c(n, m);
        for(int i=0;i<n;i++) for(int j=0;j<m;j++) c[i][j] = A(a[i][j], b[i][j]);
        return c;
    }
    matrix operator*(int b){
        matrix c(n, m);
        for(int i=0;i<n;i++) for(int j=0;j<m;j++) c[i][j] = M(a[i][j], b);
        return c;
    }
    matrix operator*(const matrix& b){
        matrix c(n, b.m);
        for(int i=0;i<n;i++){
            for(int k=0;k<m;k++) for(int j=0;j<b.m;j++) c[i][j] = A(c[i][j], M(a[i][k], b[k][j]));
        }
        return c;
    }
    static matrix idt(int n){ matrix I(n, n); for(int i=0;i<n;i++) I[i][i] = 1; return I; }
    template<class T> matrix operator^(T x){
        matrix ans = idt(n), a = *this;
        for(;x;x>>=1,a=a*a) if(x & 1) ans = ans * a;
        return ans;
    }
};

namespace solution {
    using i64 = int64_t;
    i64 n; int k;
    std::basic_string<int> mp;
    using matrix = ::matrix<2>;
    void solve(){
        cin >> n >> k >> mod; int tmp = mod - 1, g = 2;
        for(int i=2;i*i<=tmp;i++) if(!(tmp % i)){ mp += i; while(!(tmp % i)) tmp /= i; }
        if(tmp > 1) mp += tmp;
        for(;;g++) if(std::all_of(_all(mp), [=](int x){ return P(g, (mod - 1) / x) != 1; })) break;
        matrix ret(2, 2), idt = matrix::idt(2), mat(2, 2);
        mat[0][0] = mat[0][1] = mat[1][0] = 1;
        int omega = P(g, (mod - 1) / k);
        for(int i=0;i<k;i++){
            matrix tmp = idt + mat * P(omega, i);
            ret = ret + (tmp ^ n);
        }
        cout << M(A(ret[0][1], ret[1][1]), P(k, mod - 2)) << '\n';
    }
    void clear(){ mp.clear(); }
}

signed main(){
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int T = 1; cin >> T;
    while(T--) solution::solve(), solution::clear();
    return 0;
}

// [P_10664_BZOJ_3328_PYXFIB.cpp] Think twice, code once.
// Written by xiezheyuan
```

---

