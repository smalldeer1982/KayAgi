# [ABC212H] Nim Counting

## 题目描述

给定两个数 $N,K$，以及一个长度为 $K$ 的整数数组 $(A_1,A_2,\cdots, A_K)$。

两个人玩 [Nim 游戏](https://www.luogu.com.cn/problem/P2197)。

现在通过以下方式生成一个游戏：

> 任意选择一个 $1\le M\le N$，$M$ 表示石子堆数。
> 
> 对于每一堆，其石子数是 $A$ 中任意一个数。

对于 $\sum_{i=1}^N K^i$ 种游戏，求先手获胜的游戏数，答案对 $998244353$ 取模。

## 说明/提示

- $1\le N\le 2\times 10^5$

- $1\le A_i,K<2^{16}$。

- $A_i$ 两两不同。

### 样例 $1$ 解释

总共有 $6$ 种可能的游戏 $(1),(2),(1,2),(2,1),(1,1),(2,2)$。

其中先手赢的是 $(1),(2),(1,2),(2,1)$,一共 $4$ 种情况。


$\textsf{\textbf{Translated by @\color{5eb95e}nr0728}}.$

## 样例 #1

### 输入

```
2 2
1 2```

### 输出

```
4```

## 样例 #2

### 输入

```
100 3
3 5 7```

### 输出

```
112184936```

# 题解

## 作者：ZnPdCo (赞：6)

根据玩 Nim 游戏的经验，可以发现先手获胜当且仅当 $\bigoplus_{i=0}^n A_i\neq 0$。

所以我们定义 dp 式子 $f_{i,j}$ 表示有 $i$ 个石堆，且石堆异或和为 $j$ 的获胜方案数，有：
$$
f_{i-1,j}\to \sum_{k=1}^Kf_{i,j\oplus a_k}
$$

答案就是 $\sum_{i=1}^n\sum_{j\neq0} f_{i,j}$。

直接转移是朴素的，发现上面的式子刚好是 FWT 异或操作，也就是：
$$
f_{i,j}=\sum_{k\oplus x=j} f_{i-1,k}a_x
$$
我们定义 $a$ 是一个全是 $1$ 的数组即可。

同时，我们发现其实不需要真的进行 $n$ 次卷积，其实只需要将 FWT 变换过之后的结果 $A$，求出 $A+A^2+A^3+\cdots+A^n$ 即可。

上面的可以通过等比数列求和公式计算。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define P 998244353
const ll K = 1 << 20; 
ll n, k, ans;
ll f[K];
void FWT(ll *a, ll type) {
	for(ll x = 2; x <= K; x <<= 1) {
		ll k = x >> 1;
		for(ll i = 0; i < K; i += x) {
			for(ll j = 0; j < k; j ++) {
				(a[i + j] += a[i + j + k]) %= P;
				(a[i + j + k] = a[i + j] - 2 * a[i + j + k]) %= P;
				(a[i + j] *= type) %= P;
				(a[i + j + k] *= type) %= P;
			}
		}
	}
}
ll qpow(ll x, ll y) {
	if(y == 0) return 1;
	if(y % 2 == 1) return x * qpow(x, y - 1) % P;
	ll tmp = qpow(x, y / 2);
	return tmp * tmp % P;
}
int main() {
	scanf("%lld %lld", &n, &k);
	for(ll i = 1; i <= k; i ++) {
		ll x;
		scanf("%lld", &x);
		f[x] ++;
	}
	FWT(f, 1);
	for(ll i = 0; i < K; i ++) {
		if(f[i] == 1) f[i] = n;
		else {
			f[i] = f[i] * (qpow(f[i], n) - 1) % P * qpow(f[i] - 1, P - 2) % P;
		}
	}
	FWT(f, 499122177);
	for(ll i = 1; i < K; i ++) {
		(ans += f[i]) %= P;
	}
	printf("%lld", (ans % P + P) % P);
}
```

---

## 作者：zac2010 (赞：5)

题目本质就是对一个多项式 $F$ 进行等比数列求和得到 $G$（$F_i$ 表示 $i$ 在序列 $A$ 中的出现次数），求 $G$ 所有下标 $>0$ 的位置的权值和。

显然，$M$ 固定就可以直接做了。但 $M$ 不固定，所以我们只能暴力枚举 $M$ 并进行 $N$ 次 FWT 卷积。复杂度显然不满足需求。

容易想到一个经典的套路就是，我们可以直接对点值进行操作。于是我们 FWT 完后对所有点值进行等比数列求和，再 IFWT 回去就行了。

值得一提的是，在实现对点值的等比数列求和时，需特判点值为 $1$ 的情况。

```cpp
#include <bits/stdc++.h>
#define FL(i, a, b) for(int i = (a); i <= (b); ++i)
#define FR(i, a, b) for(int i = (a); i >= (b); --i)
using namespace std;
typedef long long ll;
constexpr int N = 1 << 16 + 10;
constexpr ll mod = 998244353, inv2 = (mod + 1) >> 1;
int n = 1 << 16, m, k; ll ans, a[N];
ll Pow(ll a, ll b){
    ll ans = 1;
    while(b){
        if(b & 1) (ans *= a) %= mod;
        (a *= a) %= mod, b >>= 1;
    }
    return ans;
}
void FWT_xor(ll f[], ll x = 1){
    for(int b = 2, k = 1; b <= n; b <<= 1, k <<= 1){
        for(int i = 0; i < n; i += b){
            for(int j = 0; j < k; ++j){
                f[i + j] += f[i + j + k];
                f[i + j + k] = f[i + j] - f[i + j + k] * 2 % mod + mod;
                (f[i + j] *= x) %= mod, (f[i + j + k] *= x) %= mod;
            }
        }
    }
}
int main(){
    scanf("%d%d", &k, &m);
    FL(i, 1, m){int x; scanf("%d", &x), ++a[x];}
    FWT_xor(a);
    FL(i, 0, n - 1){
        if(a[i] == 1) a[i] = k;
        else a[i] = ((Pow(a[i], k + 1) + mod - 1) * Pow(a[i] + mod - 1, mod - 2) + mod - 1) % mod;
    }
    FWT_xor(a, inv2);
    FL(i, 1, n - 1) ans += a[i];
    printf("%lld\n", (ans % mod + mod) % mod);
    return 0;
}
```


---

## 作者：云浅知处 (赞：5)

只需要最终的序列满足所有数的异或和不为 $0$。

设 $f(x)=\sum_{i=1}^Kx^{A_i}$，题目即求 

$$
\sum_{w>0}[x^w]\sum_{i=1}^N\left(f(x)\right)^i
$$
其中 $x^a\times x^b=x^{a\text{ xor }b}$。

注意到 FWT 具有线性性，因此算出 $\text{FWT}(f)$ 然后对每一项 $x\leftarrow \sum_{i=1}^Nx^i$ 再 IFWT 即可。

时间复杂度 $O(K\log K+K\log N)$。

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
	int ans=1;x%=p;
	for(int i=y;i;i>>=1,x=1ll*x*x%p)if(i&1)ans=1ll*ans*x%p;
	return ans%p;
}
int inv(int x,int p=mod){return ksm(x,p-2,p)%p;}
int randint(int l,int r){return rand()*rand()%(r-l+1)+l;}
void add(int &x,int v){x+=v;if(x>=mod)x-=mod;}
void Mod(int &x){if(x>=mod)x-=mod;}

const int N=1e5+5;
int n,k,a[N];
vector<int>f;

void FWT(vector<int>&A,int k,int tag){
	for(int i=0;i<k;i++){
		for(int S=0;S<(1<<k);S++){
			if(!(S&(1<<i)))continue;
			int x=A[S^(1<<i)],y=A[S];
			Mod(A[S^(1<<i)]=x+y),Mod(A[S]=x+mod-y);
		}
	}
	if(tag==-1){
		int iv=inv(1<<k);
		for(int S=0;S<(1<<k);S++)A[S]=1ll*A[S]*iv%mod;
	}
}

const int D=16;

signed main(void){

#ifdef YUNQIAN
	freopen("in.in","r",stdin);
#endif

	n=read(),k=read();f.resize(1<<D);
	for(int i=1;i<=k;i++)f[read()]++;
	FWT(f,D,1);
	for(int i=0;i<(1<<D);i++){
		if(f[i]==1){f[i]=n;continue;}
		f[i]=1ll*(ksm(f[i],n+1)+mod-1)*inv(f[i]+mod-1)%mod;
		add(f[i],mod-1);
	}
	FWT(f,D,-1);int ans=0;
	for(int i=1;i<(1<<D);i++)add(ans,f[i]);
	cout<<ans<<endl;

	return 0;
}
```

---

## 作者：Wuming_Shi (赞：3)

（蒟蒻自认为写得还是比较清楚的/kel）

我们知道，Nim 游戏中，先手必胜当且仅当所有石子数的异或和不为 $0$。于是容易想到 dp。

设 $f_{i,j}$ 表示选 $i$ 堆石子时异或和为 $j$ 的总方案数。初始化  $f_{1,j}$ 为原数组中值为 $j$ 的个数。答案是所有 $j\ne0$ 的 $f_{i,j}$ 之和。

转移显然：

$$ f_{i,j} = \sum_{k \oplus x = j} f_{i-1,k}  \, c_x $$
其中 $c_x$ 为值为 $x$ 的个数，即 $f_{1,x}$。那么：

$$ f_{i,j} = \sum_ {k \oplus x = j} f_{i-1, k} \times f_{1,x} $$

发现这是 FWT 的形式： $f_{i-1}$ 与 $f_1$ 通过异或卷积得到 $f_i$。也就是：

$$ \text{FWT}(f_i) = \text{FWT}(f_{i-1}) \times \text{FWT}(f_1) $$
其中 $\times$ 为对应位置相乘。

进而：

$$ \text{FWT}(f_i) = \text{FWT}^{i}(f_1) $$

所以答案就是：
$$ 
\begin{aligned}
&\sum_{i=1}^{n} \text{IFWT} (\text{FWT}(f_i))  \\
= &\sum_{i=1}^{n} \text{IFWT}(\text{FWT}^{i}(f_1)) 
\end{aligned}
$$

发现需要进行 $n$ 次卷积，时间复杂度太高。

我们知道 FWT 具有线性性，所以它等于：

$$ \text{IFWT}(\sum_{i=1}^{n} \text{FWT}^{i}(f_1) ) $$

所以我们可以先进行一次 FWT， 然后使用等比数列求和算出括号里的东西，最后 IFWT 回去统计答案即可。注意算等比数列的时候要特判值为 $1$ 的情况。

---

## 作者：demonlover923 (赞：3)

Nim 游戏的结论是 $a_1\oplus a_2 \oplus \dots \oplus a_m \not= 0$ 则先手必胜.

这题实际上就是, 我们可以根据 $a$ 数组得到一个集合幂级数, $F(x)=\sum\limits_{i=1}^{n}{x^{a_i}}$.

然后我们需要计算 $[x^{\varnothing}]\sum\limits_{i=1}^{n}{F^i}$ , 计算先手必胜和先手必败是一个道理, 考虑怎么计算 $F^k$ , 直接对 $F$ 做 $FWT$ , 然后把每一项 $k$ 次方再 $IFWT$ 回去.

又有 $FWT(A+B)=FWT(A)+FWT(B)$ , 所以如果要计算 $F^u+F^v$ , 就先对 $F$ 做 $FWT$ 再对每一项算出其 $u$ 次方加 $v$ 次方, 在 $IFWT$ 回去.

回到原题就是每一项变成 $F\dfrac{1-F^n}{1-F}$ , 时间复杂度 $\mathcal{O}(n\log{v}+v\log{v})$.

---

## 作者：xhhhh36 (赞：2)

[传送门](https://www.luogu.com.cn/problem/AT_abc212_h)

由于先手获胜要求所有石子的异或和不为 $0$，所以可以考虑用当前所有石子的异或和进行 dp。设 $dp_{i,j}$ 表示选出了 $i$ 堆石子时，异或和为 $j$ 的方案数，最开始 $dp_{1,j}$ 为 $a$ 数组中值为 $j$ 的数的个数。设 $V$ 为 $a$ 数组中的数进行异或能够得到的最大值，因为 $a_i < 2^{16}$，所以 $V=2^{16}-1$。那么转移方程为：
$$dp_{i,j}=\sum_{k=1}^{K} dp_{i-1,j\oplus a_{k}}$$
那么最终的答案即为 $\sum_{i=1}^{N} \sum_{j=1}^{V} dp_{i,j}$。直接转移是 $O(N^2K)$ 的，考虑优化。可以发现上面的 dp 式子每次用 $i$ 去更新 $i+1$ 时相当于让 $dp_{i+1}$ 等 $dp_i$ 和 $dp_1$ 的异或卷积，那么我们就可以使用 FWT 进行优化卷积，每次将 $dp_i$ 和 $dp_1$ 分别做一次 FWT 然后乘起来，再 IFWT 变回去。但是这种做法的时间复杂度为 $N^2\log V$，还需要优化。

在上面的做法中，对 $dp_i$ 有大量 FWT 和 IFWT 操作。由于 FWT 满足线性性，即 $FWT[A+B]=FWT[A]+FWT[B]$ 和 $FWT[c\cdot A]=c\cdot FWT[A]$，那么我们就可以将那些多余的 FWT 和 IFWT 省去，只用在一次 FWT 之后直接用现在得到的数组进行运算，最后再 IFWT 回去。具体的，设 $dp_{1,j}$ FWT 后的结果为 $b_{j}$，那么 $dp_{n,j}$ 就等于 ${b_{j}}^n$ 进行 IFWT 的结果。由于最终要求 $\sum_{i=1}^{N} \sum_{j=1}^{V} dp_{i,j}$。所以要让 $b_j+{b_j}^2+ \dots+{b_j}^n =b_j \frac{{b_j}^n-1}{b_j-1} \to b_j$（等比数列求和）然后将 $b$ 数组进行 IFWT，最后答案即为 $\sum_{i=1}^{V} b_i$，时间复杂度为 $O(N\log V)$。
# AC code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1<<16,mod=998244353;
void xorfwt(int a[],int n,int type){
	for (int len=2;len<=n;len*=2)
		for (int i=0;i<n;i+=len)
			for (int j=0;j<len/2;j++){
				int x=a[i+j],y=a[i+j+len/2];
				a[i+j]=(x+y)*type%mod;a[i+j+len/2]=(x-y+mod)*type%mod;
			}
}
int pw(int x,int a){int ans=1;
	while (a){
		if (a&1) ans=(ans*x)%mod;
		x=(x*x)%mod;a>>=1;
	}return ans;
}
int inv(int x){
	return pw(x,mod-2);
}
int n,a[N],k,x;
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>k;
	for (int i=1;i<=k;i++) cin>>x,a[x]++;
	xorfwt(a,N,1);
	for (int i=0;i<N;i++){
		if (a[i]==1) a[i]=n;
		else a[i]=a[i]*(pw(a[i],n)-1)%mod*inv(a[i]-1)%mod;
	}xorfwt(a,N,inv(2));x=0;
	for (int i=1;i<N;i++) x=(x+a[i])%mod;cout<<x<<endl;	
	return 0;
}
```

---

## 作者：FLAMEs_ (赞：2)

**“一定，一定要去刻画问题的本质，问题让你求什么你就刻画什么。”**

受用。

---

设 $dp_{i,st}$ 表示前 $i$ 堆石子，异或和为 $st$ 时的方案数量。

容易写出一个转移：

$$
dp_{i,st}=\sum_{j=1}^{k}dp_{i-1,st \oplus a_j}
$$

其中，$\oplus$ 代表按位 $\text{xor}$。

不难发现，这是一个卷积的形式。更具体的，从 $i-1$ 转移到 $i$ 的过程便是一次卷积的过程。

故我们可以把所有的 $dp_{0,a_j}$ 设为 $1$，先进行一次 $\text{FWT}$。

由于 $\text{FWT}$ 的线性性，直接对 $\text{FWT}(f)$ 当中的每个值都变为其 $n$ 次幂，这就相当于是 $n$ 次卷积。再做一次 $\text{IFWT}$，便可以求得 $n$ 为固定值时的答案。

第一次做的时候，我的思路就卡在了这。但是这离正解也不远了。

事实上，$\text{FWT}$ **具有线性性** 这一重要性质启示我们直接对点值进行操作即可。

对于 $i$ 堆石子的答案，其点值应当变为原来的 $i$ 次幂。所有答案累加，相当于是一个等比数列求和的过程。累加后 $\text{IFWT}$ 即可获取答案。


总的时间复杂度为 $O(K \log K + K \log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int M = (1 << 18) + 5, Mod = 998244353, inv2 = 499122177;
int n, k, m = (1 << 16), o[M], Ans;
void Add(int& x, int y) {x += y; if(x >= Mod) x -= Mod;}
int quick_pow(int a, int p) {
	int res = 1;
	for(; p; res = res * (p & 1 ? a : 1) % Mod, a = a * a % Mod, p >>= 1);
	return res;
}
inline int calc(int p) {
	if(p == 0) return 0; if(p == 1) return n;
	return ((quick_pow(p, n + 1) - 1 + Mod) % Mod * quick_pow((p - 1 + Mod) % Mod, Mod - 2) % Mod + Mod - 1) % Mod;
}
void FWTxor(int* f, int cs) {
	for(int Len = 1; Len < m; Len <<= 1) {
		for(int i = 0; i < m; i += (Len << 1)) {
			for(int j = 0; j < Len; ++ j) {
				int x = f[i + j], y = f[i + j + Len];
				f[i + j] = (x + y) % Mod, f[i + j + Len] = (x - y + Mod) % Mod;
				if(cs == -1) f[i + j] = f[i + j] * inv2 % Mod, f[i + j + Len] = f[i + j + Len] * inv2 % Mod;
			}
		}
	}
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> k;
	for(int i = 1, x; i <= k; ++ i) cin >> x, o[x] = 1;
	FWTxor(o, 1); for(int i = 0; i < m; ++ i) o[i] = calc(o[i]); FWTxor(o, -1);
	for(int i = 1; i < m; ++ i) Add(Ans, o[i]); cout << Ans;
	return 0;
}
```

---

## 作者：Nightingale_OI (赞：2)

## AT_abc212_h

### 大意

给定 $N$ 和大小为 $K$ 的集合 $S=\{A_i\}$。

Nim 游戏每堆石子数构成的数组 $a_n$ 需要满足 $1\leq n\leq N,\forall_{1\leq i\leq n}a_i\in S$。

对于 $\sum_{i=1}^NK^i$ 种游戏，求先手必胜的游戏数，答案对 $998244353$ 取模。

### 思路

尝试用多项式 $f$ 表示最后异或和为 $x$ 的有 $f_x$ 种方案。

令 $F_{A_i}=1$，求：

$$\sum_{i=1}^nF^i\text{（异或卷积）}$$

知道 $F^k$ 和 $G_k=\sum_{i=1}^kF^i$，不难算出 $F^{2k}=F^k\times F^k$ 和 $G_{2k}=G_k+F^k\times G_k$。

用快速幂做即可，时间复杂度 ${\rm O}(V\log n\log V)$，如果最后再逆卷积可以做到 ${\rm O}(V\log n+V\log V)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
int n,m,s,l;
const int mo=998244353;
const int m2=499122177;
inline int Add(int x,int y){return (x+y>=mo?x+y-mo:x+y);}
inline int Mul(int&x,int y){x=x*y%mo;} 
int ksm(int x,int p=mo-2){
	if(!p)return 1;
	int y=ksm(x,p/2);y=y*y%mo;
	return p&1?x*y%mo:y;
}
struct prts{
	#define h(a,b,c,d) for(register int a=b;a<c;a+=d)
	vector<int>a;
	inline void clear(){a.clear();}
	inline int size()const{return a.size();}
	inline prts flash()const{vector<int>r;int n=a.size();while(!a[n-1])--n;h(i,0,n,1)r.push_back(a[i]);return (prts){r};}
	inline prts resize(int n)const{vector<int>f=a;while(f.size()<=n)f.push_back(0);return (prts){f};}
	inline prts XOR(int n,int x=1)const{
		vector<int>f=resize(n).a;
		for(int o=2,k=1;o<=n;o<<=1,k<<=1){
			for(int i=0;i<n;i+=o){
				for(int j=0;j<k;j++){
					f[i+j]=Add(f[i+j],f[i+j+k]);
					f[i+j+k]=Add(f[i+j],mo-Add(f[i+j+k],f[i+j+k])); 
					Mul(f[i+j],x);Mul(f[i+j+k],x);
				}
			}
		}
		return (prts){f};
	}
	inline prts operator+(const prts& b)const{int n=size(),m=b.size();prts c;c.clear();c=c.resize(max(n,m));h(i,0,n,1)c.a[i]=(c.a[i]+a[i])%mo;h(i,0,m,1)c.a[i]=(c.a[i]+b.a[i])%mo;return c;}
	inline prts operator*(const prts& b)const{
		int n=2;
		while(n<max(a.size(),b.a.size())*2)n*=2;
		prts c=XOR(n),d=b.XOR(n);
		h(i,0,n,1)c.a[i]=c.a[i]*d.a[i]%mo;
		return c.XOR(n,m2);
	}
	inline int&operator[](int x){while(a.size()<=x)a.push_back(0);return a[x];}
	#undef h
};
struct seg{prts all,r;}; 
seg ksm(prts x,int p){
	if(p==1)return (seg){x,x};
	seg mid=ksm(x,p/2),now;
	now.all=mid.all+mid.r*mid.all;
	now.r=mid.r*mid.r;
	if(p&1)now.all=now.all+(now.r=now.r*x);
	return (seg){now.all.flash(),now.r.flash()};
}
signed main(){
	cin>>n>>m;
	prts a;s=1;
	f(i,1,n)l=(l+(s=s*m%mo))%mo;
	f(i,1,m)scanf("%lld",&s),a[s]=1;
	printf("%lld\n",(l+mo-ksm(a,n).all[0])%mo);
	return 0;
}
```

---

## 作者：Genius_Star (赞：1)

[**或许更好的阅读体验。**](https://www.cnblogs.com/rgw2010/p/18631656)

### FWT 的线性性质：

例如（其中 $A_i$ 是一个序列）：

$$\sum_{i = 1}^n FWT(A_i) = FWT(\sum_{i = 1}^n A_i)$$

证明很容易，因为 FWT 是一个线性的变换，即：

$$FWT(A_i)_k = \sum_{j = 0}^{n - 1} f(k, j) A_{i, j}$$

故有：

$$\begin{aligned} \sum_{i = 1}^m FWT(A_i)_k &= \sum_{i = 1}^m \sum_{j = 0}^{n - 1} f(k, j) A_{i, j} \\ &= \sum_{j = 0}^{n - 1} f(k, j) \left(\sum_{i = 1}^m A_{i, j} \right)\\ &= FWT(\sum_{i = 1}^m A_i)_k \end{aligned}$$

同样 $IFWT$ 也可以这样。

这个性质很有用，有些题目明明需要卷多次，根据这个性质其实只需要最后统一计算一次即可。

### 例题：

### [[ABC212H] Nim Counting](https://www.luogu.com.cn/problem/AT_abc212_h)

令 $f_{i, j}$ 表示使用 $i$ 堆式子时异或和为 $j$ 的方案数。

那么初始有 $f_{1, a_i} \gets f_{1, a_i} + 1$。

转移即：

$$f_i = f_{i - 1} \oplus f_1$$

即异或卷积。

直接暴力卷 $n$ 次肯定是不行的，直接考虑 FWT 变换，有：

$$FWT(f_i) = FWT(f_{i - 1}) FWT(f_1)$$

注意这是按位乘，故有：

$$FWT(f_i) = FWT^i(f_1)$$

故所有这 $n$ 次卷积的和是：

$$\sum_{i = 1}^n IFWT(FWT^i(f_1))$$

由于具有线性性质，直接把 $IFWT$ 提出来：

$$IFWT(\sum_{i = 1}^n FWT^i(f_1))$$

考虑如何求：

$$\left( \sum_{i = 1}^n FWT^i(f_1)\right)_k = \sum_{i = 1}^n FWT(f_1)_k^i = \frac{FWT(f_1)_k(FWT(f_1)_k^n - 1)}{FWT(f_1)_k - 1}$$

注意当 $FWT(f_1)_k = 1$ 时要特判一下。

直接快速幂算逆元即可，最后再做一次 $IFWT$，时间复杂度为 $O(K \log K)$。

### 完整代码：

```cpp
 #include<bits/stdc++.h>
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define popcnt(x) __builtin_popcount(x)
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
using namespace std;
typedef __int128 __;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 2e5 + 10, mod = 998244353;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
namespace FWT{
	int inv2 = (mod + 1) >> 1;
	int pa[N], pb[N];
	inline void go(int *A, int *B, int n){
		for(int i = 0; i < n; ++i){
			pa[i] = A[i];
			pb[i] = B[i];
		}
	}
	inline void back(int *A, int *B, int n){
		for(int i = 0; i < n; ++i){
			A[i] = pa[i];
			B[i] = pb[i];
		}
	}
	inline void FWT_or(int *A, int n){
		for(int i = 1; i < n; i <<= 1)
		  for(int j = 0; j < n; j += (i << 1))
		    for(int k = 0; k < i; ++k)
		      A[i + j + k] = (A[i + j + k] + A[j + k]) % mod;
	}
	inline void IFWT_or(int *A, int n){
		for(int i = 1; i < n; i <<= 1)
		  for(int j = 0; j < n; j += (i << 1))
		    for(int k = 0; k < i; ++k)
		      A[i + j + k] = (A[i + j + k] + mod - A[j + k]) % mod;
	}
	inline void FWT_or(int *A, int *B, int n, int *ans, bool f = 0){
		if(f)
		  go(A, B, n);
		FWT_or(A, n), FWT_or(B, n);
		for(int i = 0; i < n; ++i)
		  ans[i] = 1ll * A[i] * B[i] % mod;
		IFWT_or(ans, n);
		if(f)
		  back(A, B, n);
	}
	inline void FWT_and(int *A, int n){
		for(int i = 1; i < n; i <<= 1)
		  for(int j = 0; j < n; j += (i << 1))
		    for(int k = 0; k < i; ++k)
		      A[j + k] = (A[j + k] + A[i + j + k]) % mod;
	}
	inline void IFWT_and(int *A, int n){
		for(int i = 1; i < n; i <<= 1)
		  for(int j = 0; j < n; j += (i << 1))
		    for(int k = 0; k < i; ++k)
		      A[j + k] = (A[j + k] + mod - A[i + j + k]) % mod;
	}
	inline void FWT_and(int *A, int *B, int n, int *ans, bool f = 0){
		if(f)
		  go(A, B, n);
		FWT_and(A, n), FWT_and(B, n);
		for(int i = 0; i < n; ++i)
		  ans[i] = 1ll * A[i] * B[i] % mod;
		IFWT_and(ans, n);
		if(f)
		  back(A, B, n);
	}
	inline void FWT_xor(int *A, int n){
		for(int i = 1; i < n; i <<= 1){
			for(int j = 0; j < n; j += (i << 1)){
				for(int k = 0; k < i; ++k){
					int x = A[j + k], y = A[i + j + k];
					A[j + k] = (x + y) % mod;
					A[i + j + k] = (x - y + mod) % mod;
				}
			}
		}
	}
	inline void IFWT_xor(int *A, int n){
		for(int i = 1; i < n; i <<= 1){
			for(int j = 0; j < n; j += (i << 1)){
				for(int k = 0; k < i; ++k){
					int x = A[j + k], y = A[i + j + k];
					A[j + k] = 1ll * (x + y) % mod * inv2 % mod;
					A[i + j + k] = 1ll * (x - y + mod) % mod * inv2 % mod;
				}
			}
		}
	}
	inline void FWT_xor(int *A, int *B, int n, int *ans, bool f = 0){
		if(f)
		  go(A, B, n);
		FWT_xor(A, n), FWT_xor(B, n);
		for(int i = 0; i < n; ++i)
		  ans[i] = 1ll * A[i] * B[i] % mod;
		IFWT_xor(ans, n);
		if(f)
		  back(A, B, n);
	}
};
int n, k, x, Max, base = 1, ans;
int f[N];
inline int qpow(int a, int b){
	int ans = 1;
	while(b){
		if(b & 1)
		  ans = 1ll * ans * a % mod;
		a = 1ll * a * a % mod;
		b >>= 1;
	}
	return ans;
}
bool End;
int main(){
	n = read(), k = read();
	while(k--){
		x = read();
		++f[x];
		Max = max(Max, x);
	}
	while(base <= Max)
	  base <<= 1;
	FWT::FWT_xor(f, base);
	for(int i = 0; i < base; ++i){
		if(f[i] != 1)
		  f[i] = 1ll * f[i] * (qpow(f[i], n) - 1) % mod * qpow(f[i] - 1, mod - 2) % mod;
		else
		  f[i] = n;
	}
	FWT::IFWT_xor(f, base);
	for(int i = 1; i < base; ++i)
	  ans = (ans + f[i]) % mod;
	write(ans);
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：WorldMachine (赞：0)

晚自习做不动杂题选做来颓这个，是不是太颓废了一点？？？

写一下式子，异或和为 $s$ 的方案数为：
$$
\sum_{i=1}^n[x^s]\left(\sum_{j=1}^kx^{a_k}\right)^i
$$
当然这里乘法是 xor 卷积，使用 FWT。

FWT 是线性的，意味着我们可以先 FWT 之后对每个点值操作然后再 IFWT 回去，这里我们将 $f_i\leftarrow\sum\limits_{j=1}^nf_i^j$。

等比数列求和的时候特判 $f_i=1$ 的情况，不要因为这个像我一样和第二个样例大眼瞪小眼……
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 200005, M = 1 << 16, p = 998244353;
int n, k, f[M];
int qpow(int a, int b) {
	int c = 1;
	while (b) {
		if (b & 1) c = (ll)c * a % p;
		a = (ll)a * a % p, b >>= 1;
	}
	return c;
}
void XOR(int f[], int x) {
	for (int h = 2, k = 1; h <= M; h <<= 1, k <<= 1) {
		for (int i = 0; i < M; i += h) {
			for (int j = 0; j < k; j++) {
				f[i + j] = (f[i + j] + f[i + j + k]) % p;
				f[i + j + k] = ((ll)f[i + j] - f[i + j + k] * 2 + p * 2) % p;
				f[i + j] = (ll)f[i + j] * x % p, f[i + j + k] = (ll)f[i + j + k] * x % p;
			}
		}
	}
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> k;
	for (int i = 1, a; i <= k; i++) cin >> a, f[a]++;
	XOR(f, 1);
	for (int i = 0; i < M; i++) {
		f[i] = f[i] == 1 ? n : ((ll)qpow(f[i], n + 1) - f[i] + p) % p * qpow(f[i] - 1, p - 2) % p;
	}
	XOR(f, (p - 1) >> 1);
	int ans = 0;
	for (int i = 1; i < M; i++) ans = (ans + f[i]) % p;
	cout << ans;
}
/*
FWT 好题
写一下式子发现答案就是 F 的一个等比数列求和，只不过这里乘法是 XOR 卷积
FWT 是线性的，意味着我们可以先 FWT 之后对每个点值操作然后再 IFWT 回去
等比数列特判 f[i] = 1
*/
```

---

## 作者：tder (赞：0)

You can view the [English version](https://www.luogu.com/article/1i9fkz0b/) of this solution.

考虑一个朴素 dp，$f_{i,j}$ 表示选了 $i$ 个异或和为 $j$ 的方案数。有转移：

$$
f_{i,j}\gets\sum f_{i-1,j\oplus A_k}\cdot f_{1,A_k}
$$

特别的，$f_{1,j}\gets\sum[A_k=j]$。复杂度 $\mathcal{O}(N\cdot K\cdot V)$。

考虑优化。令 $p(j)=f_{1,j}$，$q(j)=f_{i-1,j}$，$g(j)=f_{i,j}$，则有：

$$
g(x)=\sum_{a\oplus b=x} p(x)\cdot q(x)
$$

容易发现，这就是一个 xor 卷积，即 $g=p*q$。因此，当 $i=n$ 时，有 $g=q^n$。复杂度 $\mathcal{O}(K\cdot V\log V)$，瓶颈在于要做 $K$ 次 FWT。

考虑优化。所求即为：

$$
\begin{aligned}
\text{ans}&=\sum_{i=1}^K\sum_{j=1}^{V-1}{q_j}^i \\
&=\sum_{j=1}^{V-1}\sum_{i=1}^K{q_j}^i
\end{aligned}
$$

本题的关键点在于，FWT 具有「线性性」，即其满足 $\text{FWT}(X+Y)=\text{FWT}(X)+\text{FWT}(Y)$，且 $\text{FWT}(a\cdot X)=a\cdot\text{FWT}(X)$。故根据等比数列求和公式，有：

$$
\sum_{i=1}^K{q_j}^i=\frac{{q_j}^N-1}{q_j-1}\cdot q_j
$$

答案即为：

$$
\begin{aligned}
\text{ans}&=\sum_{j=1}^{V-1}\sum_{i=1}^K{q_j}^i \\
&=\sum_{j=1}^{V-1}\frac{{q_j}^K-1}{q_j-1}\cdot q_j
\end{aligned}
$$

如此一来，只用做一次 FWT 即可。复杂度 $\mathcal{O}(V\log V)$。

---

