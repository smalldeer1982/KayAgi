# Product of Arithmetic Progression

## 题目描述

[problemUrl]: https://atcoder.jp/contests/m-solutions2019/tasks/m_solutions2019_e

以下のような、$ n $ 項からなる等差数列を考えます。

- $ x,\ x\ +\ d,\ x\ +\ 2d,\ \ldots,\ x\ +\ (n-1)d $

この数列のすべての項の積はいくつでしょうか？ その積を $ 1,000,003 $ で割った余りを計算してください。

この形式の問いが $ Q $ 個与えられます。 $ i $ 個目の問いでは、$ x\ =\ x_i,\ d\ =\ d_i,\ n\ =\ n_i $ の場合の答えを計算してください。

## 说明/提示

### 制約

- $ 1\ \leq\ Q\ \leq\ 10^5 $
- $ 0\ \leq\ x_i,\ d_i\ \leq\ 1,000,002 $
- $ 1\ \leq\ n_i\ \leq\ 10^9 $
- 入力中の値はすべて整数である。

### Sample Explanation 1

最初のクエリに対し、答えは $ 7\ \times\ 9\ \times\ 11\ \times\ 13\ =\ 9009 $ です。 積を $ 1,000,003 $ で割った余りを求めることをお忘れなく。

## 样例 #1

### 输入

```
2
7 2 4
12345 67890 2019```

### 输出

```
9009
916936```

# 题解

## 作者：DE_aemmprty (赞：7)

[题目链接](https://www.luogu.com.cn/problem/AT_m_solutions2019_e)

感觉很有必要做一下脑筋题预防埃尔默兹海默症。

首先发现 $d = 0$ 时题目直接退化成 $x^n$。

然后考虑等差序列模一个质数一定会有周期，于是 $n \geq 1000003$ 时答案为 $0$。

尝试考虑 $d = 1$。发现所有数都是连续的，容易联想到阶乘相除，也就是 $\frac{(x + n - 1)!}{(x - 1)!}$。

扩展到更一般的情况，我们直接自信对原式除以 $d^n$！于是每个 $x + i \times d$ 都变成 $\frac{x + i \times d}{d} = \frac{x}{d} + i$。这样原式变成 $\begin{cases}x' = \frac{x}{d}\\d' = 1\\n'=n\end{cases}$ 的情况，所以答案为 $\frac{(\frac{x}{d}+n-1)!}{(\frac{x}{d} - 1)!} \times d^n$。

惊奇的发现我们信息学有逆元！于是 $\frac{x}{d}$ 可以被视为整数处理。

以下为代码：

```cpp
void solve() {
    x = read(), d = read(), n = read();
    if (d == 0) {
        cout << ksm(x, n % (mod - 1)) << '\n';
        return ;
    }
    if (n >= mod) {
        cout << 0 << '\n';
        return ;
    }
    (x *= ksm(d, mod - 2)) %= mod;
    long long ans = fac[x + n - 1] * (!x ? 1 : ksm(fac[x - 1], mod - 2)) % mod * ksm(d, n) % mod;
    cout << ans << '\n';
}
```

---

## 作者：huangrenheluogu (赞：2)

脑筋急转弯。

首先需要发现 $1000003$ 是一个素数，不妨记 $p=1000003$。

首先，如果 $d=0$，显然是可以快速幂计算的。

因为 $\forall i\in[1,p-1],\gcd(p,i)=1$，所以 $\forall x\in[0,p-1]$，$x$ 可以表示为 $kd,0\le k\lt p,k\in\mathbb{N}$ 的形式。于是，问题转化为 $\prod\limits_{i=0}^{n-1}(k+i)d$ 的形式。发现对于 $k+n\ge p$ 乘积中至少有为 $0$ 的项，因此答案为 $0$。所以对于答案不为 $0$ 的情况，满足 $n\lt p$，可以处理 $i!$ 来做。

由于是模拟赛的原题，所以代码里变量名略有不同，且有 freopen。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 1e6 + 3, N = mod + 5;
int T, d, n, a, tmp = 1, fac[N];
inline int ksm(int x, int y){
    int res = 1;
    while(y){
        if(y & 1) res = res * x % mod;
        x = x * x % mod, y >>= 1;
    }
    return res;
}
inline int solve(){
    if(d % mod == 0){
        return ksm(a, n);
    }
    a = a * ksm(d, mod - 2) % mod;
    if(a == 0 || a + n > mod) return 0;
    return fac[a + n - 1] * ksm(fac[a - 1], mod - 2) % mod * ksm(d, n) % mod;
}
signed main(){
    // freopen("sequence.in", "r", stdin);
    // freopen("sequence.out", "w", stdout);
    fac[0] = 1;
    for(int i = 1; i < mod; i++) fac[i] = fac[i - 1] * i % mod;
    scanf("%lld", &T);
    while(T--){
        scanf("%lld%lld%lld", &a, &d, &n);
        printf("%lld\n", solve());
    }
    return 0;
}
```

---

## 作者：Red_river (赞：1)

### 题目分析
题目大意就是化简一个式子，所以在这里就不再展开叙述。对于 $\prod\limits_{i=0}^{n-1} (x+i\times d) \bmod 1000003$ 中，我们可以很容易的发现如下几种情况：

- 对于 $d=0$ 的时候，$id=0$，所以答案就变为 $x^n$ 了。
- 对于一般情况，我们自然会想到逆元。于是原式可以化简成 $d^n \times \prod\limits_{i=0}^{n-1} (x \div d + i) \bmod 1000003$。于是可以预处理逆元和阶乘以及快速幂，再按公式计算就行了。

具体可以参考代码及注释理解。
### CODE
```cpp
#include<bits/stdc++.h>
#define ll long long
#define wh(x) write(x),putchar('\n')
#define N 10000005

using namespace std;
ll n,m,k,jk,ans,sum,num,cnt,tot;
ll inv[N],f[N];

void read(ll &x)
{
	x=0;ll ff=1;
	char ch=getchar();
	while (ch<'0'||ch>'9')
	{
		if(ch=='-') ff=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	x*=ff;return;
}

void write(ll x)
{
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
	return;
}

ll ksm(ll x,ll y){
	ll z=1;while(y){
		if(y&1) z*=x,z%=m;
		x=x*x%m,y>>=1;
	}
	return z%m;
}

int main()
{
	read(n);m=1000003;ll x,y,z;f[0]=1;inv[m-1]=m-1;
	for(ll i=1;i<m;i++) f[i]=f[i-1]*i%m;//计算阶乘
	for(int i=m-2;i>=0;i--)	inv[i]=inv[i+1]*(i+1)%m;//逆元
	while(n--){
		read(x),read(y),read(z);
		if(y==0) wh(ksm(x,z));//特判
		else{
			k=0;k=x*ksm(y,m-2)%m;//y的逆元
			if(z+k-1>=m) wh(0);//大于模数直接为0
			else wh(f[z+k-1]*inv[k-1]%m*ksm(y,z)%m);//公式
		}
	}
	return 0;
}
```

---

## 作者：liuhongyang123 (赞：1)

### 告知
这题很水，纯考思维。
# 题意
题目翻译讲的很清楚了。
# 解法
拆式子。

> $\prod\limits_{i = 0}^{n - 1} (x + i \times d) \bmod 1000003$
>
> $=\prod\limits_{i = 0}^{n - 1} d(\frac{x}{d} + i) \bmod 1000003$
>
> $=d^n\prod\limits_{i = 0}^{n - 1} (\frac{x}{d} + i) \bmod 1000003$

好了，拆完了，拆成这个样子的好处就是 $d^n$ 可以 $O(1)$ 求，那么我们就考虑如何快速求 $\prod\limits_{i = 0}^{n - 1} (\frac{x}{d} + i) \bmod 1000003$。

我们不妨把式子展开。
> $\prod\limits_{i = 0}^{n - 1} (\frac{x}{d} + i) \bmod 1000003$
>
> $=\frac{x}{d}(\frac{x}{d}+1)(\frac{x}{d}+2)\cdots(\frac{x}{d}+n-1)$

那我们发现是不是一个公差为 $1$ 的乘法序列吗。那答案是不是就是**从 $1$ 到 $\frac{x}{d}+n-1$ 的积除以从 $1$ 到 $\frac{x}{d}-1$的积**。不理解的可以试着带入一些数感受一下。

# Code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll MAXN=1e7+5;
ll T,d,n,a,P[MAXN],MOD;
ll ksm(ll A,ll B) {
	ll Ans=1;
	while(B){
		if(B&1) Ans=Ans*A%MOD;
		A=A*A%MOD;
		B>>=1;
	}
	return Ans;
}
int main(){
	freopen("story.in","r",stdin);
	freopen("story.out","w",stdout);
	scanf("%lld%lld",&T,&MOD);
	P[0]=1;
	for(ll i=1;i<MOD;i++) P[i]=P[i-1]*i%MOD;
	while(T--) {
		scanf("%lld%lld%lld", &a,&d,&n);
		if(!(d%MOD)) printf("%lld\n",ksm(a,n));
		else{
			a=a*ksm(d,MOD-2)%MOD;
			if(!a||a+n>MOD) puts("0");
			else printf("%lld\n",P[a+n-1]*ksm(P[a-1],MOD-2)%MOD*ksm(d,n)%MOD);
		}
	}
	return 0;
}
```

---

## 作者：yzx3195 (赞：1)

# 题目大意
每次输入三个数 $x,d,n$，求 $\prod\limits_{i = 0}^{n - 1} (x + i \times d) \bmod 1000003$。

# 这题诈骗
先特判 $d=0$，考虑到 $d=1$ 时，原数列为等差数列，而原数列为等差数列时十分好做，用阶乘推一下，答案即为 $\frac{(x+n-1)!}{(x-1)!}$。

那我们考虑 $d > 1$ 时，考虑将原数列中的 $d$ 化为 $1$ 那我们再用 $d=1$ 时的算法去做即可。

$$ \prod\limits_{i = 0}^{n - 1} (x + i \times d)  =d^n\prod_{i=0}^{n-1} \frac{x}{d}+i $$

如此我们便将 $d$ 化成了 $1$。

答案便是 $d^n\times \frac{(\frac{x}{d}+n-1)!}{(\frac{x}{d}-1)!}$。其中 $\frac{x}{d}$ 用逆元即可。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;

const long long mod = 1000003;

long long T;

long long n, a, d;

unordered_map <long long, long long> fac;

long long bin_pow(long long a, long long b)
{
	long long res = 1;
	while(b)
	{
		if(b & 1)
			res = res * a % mod;
		 a = a * a % mod;
		 b >>= 1ll;
	}
	return res % mod; 
}

int main()
{
	scanf("%lld", &T);
	
	fac[0] = 1;
	
	for(register long long i = 1; i <= mod; i++)
	{
		fac[i] = fac[i - 1] * i % mod;
	}
	
	while(T--)
	{
		scanf("%lld%lld%lld", &a, &d ,&n);
		if(!a)
		{
			puts("0");
			continue;
		}
		long long ans = 0; 
		if(d % mod == 0)
		{
			ans = bin_pow(a, n) % mod;
			ans %= mod;
		}
		else 
		{
			long long A = a * bin_pow(d, mod - 2) % mod;
			if(!A)
			{
				ans = 0;
			}
			else
				ans = fac[A + n - 1] * bin_pow(fac[A - 1], mod - 2) % mod * bin_pow(d, n) % mod;
		}
		printf("%lld", ans);		 
		puts("");
	}
	
	return 0;
}
```

---

## 作者：lwwwb_555 (赞：1)

简要题意：一个等差数列，给定首项，公差和项数，求整个数列的积。

我们考虑当公差为 $1$ 的时候，只需要预处理一下阶乘和逆元就好了。

我们再来考虑当公差不是 $1$ 的时候，我们可以把整个数列先除以公差，这样这个数列的公差就是 $1$ 了，最后再乘上公差的项数次方就可以了。

那么如果有些项除以公差以后不是整数怎么办呢？我们可以把它们用逆元化成整数，这样所有的问题就都可以解决了。

注意特判一下公差为 $0$ 和某一项再模 $p$ 意义下是否为 $0$ 就可以了。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
long long fac[10000005],inv[10000005],p=1000003,n,a,d;
long long quick_pow(long long x,long long t){
	long long res=1;
	while(t){
		if(t&1) res*=x,res%=p;
		x*=x,x%=p,t>>=1;
	}
	return res;
}//快速幂
int read(){
	int res=0,f=1;
	char c=getchar();
	while(!isdigit(c)){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(isdigit(c)){
		res=(res<<3)+(res<<1)+c-'0';
		c=getchar();
	}
	return res*f;
}//快读
int main(){
	t=read();
	fac[0]=1;
	for(int i=1;i<=p;i++) fac[i]=fac[i-1]*(long long)i%p;//预处理阶乘
	inv[p-1]=quick_pow(fac[p-1],p-2);
	for(int i=p-2;i>=0;i--) inv[i]=inv[i+1]*(long long)(i+1)%p;//预处理逆元
	while(t--){
		a=read(),d=read(),n=read();
		if(d==0){
			printf("%lld\n",quick_pow(a,n));
			continue;
		}//特判公差为0的情况
		a=a*quick_pow(d,p-2)%p;
		if(a+n-1>=p){
			printf("0\n");
			continue;
		}//特判等差数列中是否有某一项再模p意义下为0
		printf("%lld\n",quick_pow(d,n)*fac[a+n-1]%p*inv[a-1]%p);//直接计算答案
	}
	return 0;
} 
```

---

## 作者：鲤鱼江 (赞：1)

脑经急转弯题，被出题人搬到了模拟赛。

一句话题意就是等差数列求积后模质数，发现模数比较小，但是测很多组，猜测标答是跟模数大小有关的预处理，然后 $O(\log n)$ 或 $O(1)$ 回答。

略微思考发现项数肯定不超过模数，否则答案肯定为 $0$，先判掉，但是仍然不好做，又发现公差等于 $1$ 时很好算。

于是想到先将整个式子先除以 $d$，变成 $d^n\prod\limits_0^{n-1}(\frac{a}{d}+i)$，考虑是模质数意义下，所以 $d$ 不是模数的整倍数时，$\frac{a}{d}$ 肯定存在。

于是将式子转化为了连乘的形式，很轻松能预处理，但是有一些神经细节，为了求稳多判了一些细节。

```cpp
#include<bits/stdc++.h>

using namespace std;

namespace Fread {
	const int SIZE=1<<21;char buf[SIZE],*S,*T;
	inline char getchar() {if(S==T){T=(S=buf)+fread(buf,1,SIZE,stdin);if(S==T)return '\n';}return *S++;}
}
namespace Fwrite {
	const int SIZE=1<<21;
	char buf[SIZE],*S=buf,*T=buf+SIZE;
	inline void flush(){fwrite(buf,1,S-buf,stdout);S=buf;}
	inline void putchar(char c){*S++=c;if(S==T)flush();}
	struct POPOSSIBLE{~POPOSSIBLE(){flush();}}ztr;
}
#define getchar Fread :: getchar
#define putchar Fwrite :: putchar
namespace Fastio{
	struct Reader{
	    template<typename T>
    	Reader& operator >> (T& x) {
        	char c=getchar();T f=1;
        	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}x=0;
        	while(c>='0'&&c<='9'){x=x*10+(c-'0');c=getchar();}x*=f;
	        return *this;
    	}
	    Reader(){}
	}cin;
	struct Writer{
	    template<typename T>
	    Writer& operator << (T x) {
	        if(x==0){putchar('0');return *this;}
	        if(x<0){putchar('-');x=-x;}
	        static int sta[45];int top=0;
	        while(x){sta[++top]=x%10;x/=10;}
	        while(top){putchar(sta[top]+'0');--top;}
	        return *this;
    	}
    	Writer& operator << (char c) {putchar(c);return *this;}
    	Writer& operator << (const char* str){int cur=0;while(str[cur])putchar(str[cur++]);return *this;}
    	Writer(){}
	}cout;
}
#define endl '\n'
#define int long long
#define cin Fastio :: cin
#define cout Fastio :: cout

const int mod=1000003;
struct modint {
    int val;
    static int norm(const int& x) { return x < 0 ? x + mod : x; }
    static constexpr int get_mod() { return mod; }
    modint inv() const {
        int a = val, b = mod, u = 1, v = 0, t;
        while (b > 0) t = a / b, swap(a -= t * b, b), swap(u -= t * v, v);
        return modint(u);
    }
    modint() : val(0) {}
    modint(const long long& m) : val(norm(m % mod)) {}
    modint operator-() const { return modint(norm(-val)); }
    bool operator==(const modint& o) { return val == o.val; }
    bool operator<(const modint& o) { return val < o.val; }
    modint& operator+=(const modint& o) { return val = (1ll * val + o.val) % mod, *this; }
    modint& operator-=(const modint& o) { return val = norm(1ll * val - o.val), *this; }
    modint& operator*=(const modint& o) { return val = static_cast<int>(1ll * val * o.val % mod), *this; }
    modint& operator/=(const modint& o) { return *this *= o.inv(); }
    modint& operator^=(const modint& o) { return val ^= o.val, *this; }
    modint& operator>>=(const modint& o) { return val >>= o.val, *this; }
    modint& operator<<=(const modint& o) { return val <<= o.val, *this; }
    modint operator-(const modint& o) const { return modint(*this) -= o; }
    modint operator+(const modint& o) const { return modint(*this) += o; }
    modint operator*(const modint& o) const { return modint(*this) *= o; }
    modint operator/(const modint& o) const { return modint(*this) /= o; }
    modint operator^(const modint& o) const { return modint(*this) ^= o; }
    modint operator>>(const modint& o) const { return modint(*this) >>= o; }
    modint operator<<(const modint& o) const { return modint(*this) <<= o; }
    friend std::ostream& operator<<(std::ostream& os, const modint& a) { return os << a.val; }
};

const int N=1e6+10;
int T,n,d,a;
modint frac[N],inv[N],res;

void init(){
	frac[0]=inv[0]=1;
	for(int i=1;i<N;++i) frac[i]=frac[i-1]*i;
	for(int i=N-2;i;--i) inv[i]=frac[i].inv();
}

inline modint expow(modint x,int y){
	modint res=1;
	for(;y;y>>=1){
		if(y&1)res*=x;
		x*=x;
	}
	return res;
}
signed main(){
	cin>>T;init();
	while(T--){
		cin>>a>>d>>n;a%=mod;d%=mod;
		if(!d) cout<<expow(a,n).val<<endl;
		else {
			int tmp=(modint(a)/d).val;
			int st=(tmp+n-1),ed=tmp-1;
			if(st-ed>=mod||(st%mod<ed%mod)||!a) cout<<"0\n";
			else cout<<(expow(d,n)*frac[st%mod]*inv[ed%mod]).val<<endl;
			if(!expow(d,n).val) return 1;
		}
	}
	return 0;
}
```

---

## 作者：wujingfey (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_m_solutions2019_e)

## 题意

$T$ 组数据和模数 $p$，每组给 $a,d,n$，求 $\prod_{i=0}^{n-1}(a+i\times d) \mod 1000003$。

### 题解

发现公差 $d\not =1$ 的时候很难处理，但 $d=1$ 时就是个阶乘，所以我们暴力把 $d$ 提取出来，公式转化成 

$$d^n\prod_{i=0}^{n-1}(\frac{a}{d}+i)$$

$\frac{a}{d}$ 转化成逆元，然后题目就转化成求一段连续的数的乘积。预处理出 $pre_i$ 表示 $i$ 的阶乘，然后可以 $O(1)$ 或 $O(\log_2n)$ 算了。

### CODE
记得特判 $d=0$。
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e7+7,p=1000003;
int T,a,d,n,pre[N];
int qp(int x,int k){
	int res=1,base=x;
	while(k){
		if(k&1) res=res*base%p;
		base=base*base%p;
		k>>=1;
	}
	return res%p;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>T; pre[0]=1,pre[1]=1;
	for(int i=2;i<=p;i++){
		pre[i]=pre[i-1]*i%p;//p之后的mod就都为0了 
	}
	while(T--){
		cin>>a>>d>>n;
		if(d==0) cout<<qp(a,n)<<'\n';//特判d==0 
		else{
			int x1=a*qp(d,p-2)%p;
			int x2=pre[(x1+n-1)%p];
			if(x1+n-1>=p){//大于p后的pre就=0了 
				cout<<"0\n";
				continue;
			}
			int x3=pre[(x1-1)%p];
			cout<<qp(d,n) * (x2 * qp(x3,p-2) %p) %p<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：superl61 (赞：0)

非常魔幻的一道数学题。

令 $a = k \times d$， 则 $a + i\times d = (k + i)\times d$。则有

$$
\prod_{i = 0}^{n-1}(a + i\times d) = \prod_{i = 0}^{n-1}(k + i) \times d^n = \frac{(n - 1 + k)!}{(k - 1)!} \times d ^ n
$$
预处理阶乘和逆元即可。

~~~cpp
#include<bits/stdc++.h>
#define F(i,l,r) for(int i(l);i <= (r);++i)
#define G(i,r,l) for(int i(r);i >= (l);--i)
using namespace std;
using ll = long long;
char buf[100], *p1=buf, *p2=buf, obuf[5000000], *o = obuf;
inline int gc(){ return (p1==p2)&&(p2=(p1=buf)+fread(buf,1,100,stdin),p1==p2)?EOF:*p1++;}
inline int rd(){
	int x = 0; char ch;
	while(!isdigit(ch = gc()));
	do x = (x << 3) + (x << 1) + (ch ^ 48); while(isdigit(ch = gc()));
	return x;
}
inline void write(int x){
	if(x > 9) write(x / 10);
	*o ++= (x%10 + 48);
}
const int N = 1e7 + 5;
int n, a, d, mod, T;
ll fac[N], invf[N];
int quickmod(ll x, int y){
	ll ret = 1; while(y){
		if(y & 1) ret = (ret * x) % mod;
		x = (x * x) % mod;
		y >>= 1;
	} return ret;
}
int solve(int a, int d, int n){
	if(!a) return 0;
	if(!d) return quickmod(a, n);
	int st = a * invf[d] % mod * fac[d - 1] % mod;
	if( n - 1 + st >= mod) return 0;
	return fac[n - 1 + st] * invf[st - 1] % mod * quickmod(d, n) % mod;
}
void init(){
	fac[0] = 1; F(i, 1, mod - 1) fac[i] = fac[i - 1] * i % mod;
	invf[mod - 1] = quickmod(fac[mod - 1], mod -2);
	G(i, mod - 2, 0) invf[i] = invf[i + 1] * (i + 1) % mod;
}
signed main(){
//	freopen("story.in","r",stdin); freopen("story.out","w",stdout);
	T = rd(), mod = 1000003,init();
	while(T--){
		a = rd(), d = rd(), n = rd();
		write(solve(a, d, n));
		*o++='\n';
	} return fwrite(obuf, o - obuf, 1, stdout), fflush(0), 0;
}
~~~

---

## 作者：strcmp (赞：0)

神金急转弯题目，被出题人搬到了模拟赛。

zr ab 班十连测 day6 T1 原题。

zr 那题 $d,\,x$ 加强到了 $10^9$，但事实上并没有强化题目。

---

注意到模数不大且是质数，不然它严格不弱于 [P5282](https://www.luogu.com.cn/problem/P5282)，就做不了了。

如果 $d = 1$ 我们可以预处理阶乘。具体的，容易发现答案就是 $\left(\frac{x + d - 1}{x - 1}\right)! = (x+d-1)^{\underline d}$，我们 OI 中有乘法逆元，预处理一下阶乘就做完了。

$d$ 有 $10^9$，怎么预处理阶乘？模数 $p$ 很小所以阶乘在 $\ge p$ 的时候全是 $0$，特判一下就行了。

如果 $d \ne 1$ 呢？我们发现全部提一个 $d$ 出来，$\prod\limits_{i = 0}^{n - 1} (x + i \times d) = d^n(\frac{x}{d}+i)$，$\frac{x}{d}$ 可以乘法逆元直接算出，就变成了 $d = 1$ 的情况，直接做就完了。

时间复杂度 $\Theta(T \log p + n)$，可以通过。

```cpp
#include <bits/stdc++.h>
#define X first
#define Y second
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define pb push_back
using namespace std;
typedef long long int ll;
using pii = pair<int, int>;
constexpr int maxn = 2e6 + 10, B = 323, mod = 1000003;
const ll inf = 1145141919810520LL;
inline ll ksm(ll a, ll b = mod - 2) {
	if (a < 0) return 1;
	ll ls = 1;
	while (b) {
		if (b & 1) ls = ls * a % mod;
		a = a * a % mod; b >>= 1;
	} 	
	return ls;
}
ll a, d, n, fac[maxn]; int T;
int main() {
	scanf("%d", &T); fac[0] = 1;
	for (int i = 1; i <= mod; i++) fac[i] = fac[i - 1] * i % mod;
	while (T--) {	
		scanf("%lld%lld%lld", &a, &d, &n); a %= mod; d %= mod;
		if (a == 0) puts("0");
		else if (d == 0) printf("%lld\n", ksm(a, n));
		else {
			ll w = a * ksm(d) % mod;
			if (w + n - 1 >= mod) puts("0");
			else {
				ll ans = ksm(d, n) * fac[w + n - 1] % mod * ksm(fac[w - 1 < 0 ? 0 : w - 1]) % mod;
				printf("%lld\n", ans);
			}
		}
	}
	return 0;
}
```

---

## 作者：DengDuck (赞：0)

诈骗题，深金细节给我送走了。

首先容易发现根据抽屉原理 $n\geq p$ 时答案是 $0$。

但是，你先不要发现！如果 $d\equiv 0\pmod p$，那么你变化了吗？如变，这时每一项都是一样的，应该求一个快速幂。

我就这个挂了，呜呜呜。

然后处理好之后我们再特判 $n\geq p$ 的情况，对于剩下情况，保证了 $n$ 不会太大。

然后我们可以求一下 $a\equiv xd\pmod p$ 的解，然后原式就变成 $i\in[0,n-1]$ 的 $(x+i)d$ 的连乘，然后这个 $d$ 显然可以提出来变成一个 $d^n$。

剩下部分显然是连续的自然数连乘，考虑预处理阶乘然后除掉前面的部分，就做完了。

---

## 作者：XYQ_102 (赞：0)

如果 $d=0$，则答案为 $x^n$；

如果 $d\neq0$，都除上一个 $d$，可发现是一段连续的数相乘，可以用前缀乘积的一个除另一个，特判 $x=0$ 和 $\frac{x}{d}+n-1\geq P$ 的情况，最后再乘上 $d^n$ 即可。
## Code
```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define pii pair<int,int>
#define mp make_pair
#define pb push_back
#define space putchar(' ')
#define enter putchar('\n')
#define eps 1e-10
#define MAXN 10005
#define ba 47
//#define ivorysi
using namespace std;
typedef long long int64;
typedef unsigned int u32;
typedef double db;
template<class T>
void read(T &res) {
    res = 0;T f = 1;char c = getchar();
    while(c < '0' || c > '9') {
    	if(c == '-') f = -1;
    	c = getchar();
    }
    while(c >= '0' && c <= '9') {
    	res = res * 10 +c - '0';
    	c = getchar();
    }
    res *= f;
}
template<class T>
void out(T x) {
    if(x < 0) {x = -x;putchar('-');}
    if(x >= 10) {
    	out(x / 10);
    }
    putchar('0' + x % 10);
}
const int MOD = 1000003;

int pre[MOD + 5];
int mul(int a,int b) {
    return 1LL * a * b % MOD;
}
int inc(int a,int b) {
    return a + b >= MOD ? a + b - MOD : a + b;
}
int fpow(int x,int c) {
    int res = 1,t = x;
    while(c) {
        if(c & 1) res = mul(res,t);
        t = mul(t,t);
        c >>= 1;
    }
    return res;
}
void Solve() {
    pre[0] = 1;
    for(int i = 1 ; i < MOD ; ++i) pre[i] = mul(pre[i - 1],i);
    int Q,x,d,n;
    read(Q);
    for(int i = 1 ; i <= Q ; ++i) {
        read(x);read(d);read(n);
        if(d == 0) {out(fpow(x,n));enter;continue;}
        x = mul(x,fpow(d,MOD - 2));
        if(x + n - 1 >= MOD || x == 0) {puts("0");continue;}
        int res = mul(pre[x + n - 1],fpow(pre[x - 1],MOD - 2));
        res = mul(res,fpow(d,n));
        out(res);enter;
    }
}
int main() {
#ifdef ivorysi
    freopen("f1.in","r",stdin);
#endif
    Solve();
    return 0;
}
```

---

## 作者：wurzang (赞：0)


- ## Part 1 前言

	这题是个脑筋急转弯题，[周指导](https://www.zhou-jk.cn/)一眼就秒掉了，我没有脑筋所以不会做，只好来复读一下周指导的做法

- ## Part 2 题解

	题意：求 $\prod_{i=0}^{n-1} (x+id) \mod 1000003$，$n \leq 10^9$
    
    考虑 $d=1$ 怎么做
    
    $d=1$ 时即 $\frac{(x+n-1)!}{(x-1)!}$，注意到 $n \ge 10^6+3$ 时 $n!=1$，所以可以直接 $\mathcal{O}(mod)$ 预处理然后做。
    
    接着考虑$d \not = 1$ 的时候怎么做
    
    把上式整体除 $d$ 再把答案乘上 $d^n$，于是跟 $d=1$ 的情况相同。
    
    [code](https://atcoder.jp/contests/m-solutions2019/submissions/16968276)

---

