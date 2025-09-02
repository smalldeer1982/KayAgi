# Bash Plays with Functions

## 题目描述

Bash got tired on his journey to become the greatest Pokemon master. So he decides to take a break and play with functions.

Bash defines a function $ f_{0}(n) $ , which denotes the number of ways of factoring $ n $ into two factors $ p $ and $ q $ such that $ gcd(p,q)=1 $ . In other words, $ f_{0}(n) $ is the number of ordered pairs of positive integers $ (p,q) $ such that $ p·q=n $ and $ gcd(p,q)=1 $ .

But Bash felt that it was too easy to calculate this function. So he defined a series of functions, where $ f_{r+1} $ is defined as:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF757E/ba3f455e23406140b1481185211a534c2e0f9d49.png)Where $ (u,v) $ is any ordered pair of positive integers, they need not to be co-prime.

Now Bash wants to know the value of $ f_{r}(n) $ for different $ r $ and $ n $ . Since the value could be huge, he would like to know the value modulo $ 10^{9}+7 $ . Help him!

## 样例 #1

### 输入

```
5
0 30
1 25
3 65
2 5
4 48
```

### 输出

```
8
5
25
4
630
```

# 题解

## 作者：STDquantum (赞：9)

虽然已经有题解了，我就讲得详细一点，做一下对上一篇的补充吧。

把题中 $p,q$ 换成 $a,b$，因为 $p$ 一般代表质数。

首先观察 $f_0$ 的定义：满足 $a\cdot b=n$ 且 $\gcd(a,b)=1$ 的有序对 $(a,b)$ 个数。

由于 $\gcd$ 为 $1$，$a$ 与 $b$ 互质，则 $a$ 和 $b$ 没有公共的质因子。又因为 $a\cdot b=n$，所以 $a$ 和 $b$ 平分了 $n$ 的所有质因子。

由算术基本定理，有 $n=p_1^{k_1}p_2^{k_2}\cdots p_{\omega(n)}^{k_{\omega(n)}}$，其中 $p$ 是质数，$\omega(n)$ 即 $n$ 的不同质因子个数。

（$\omega(n)$ 是加性函数，即对于 $\gcd(i,j)=1$，有 $\omega(i\cdot j)=\omega(i)+\omega(j)$）。

那么对于每个 $p_i^{k_i}$，必定为 $a$ 或 $b$ 的因子。所以把这些 $p_i^{k_i}$ 分成两份（可为空），方案数即为 $2^{\omega(n)}$。

也就是说 $f_0(n)=2^{\omega(n)}$。

对于形如 $C^{f}$ 的函数，$C$ 为常数，$f$ 为加性函数，则 $C^f$ 为积性函数。因为乘法到了指数上就变成了加法。

由此可以得到 $f_0$ 为积性函数。

其取值如下（其实前两个都可以通过第三个推导出来，但是由于后文要用到，所以单列出来）：
$$
f_0(n)=\left\{\begin{array}{ll}1&n=1\\2&n=p^k,p\in{\rm prime}\\2^{\omega(n)}&n=p_1^{k_1}p_2^{k_2}\cdots p_{\omega(n)}^{k_{\omega(n)}},\forall i,p_i\in{\rm prime}\end{array}\right.
$$
然后再来看 $r\ge1$ 的情况：
$$
f_r(n)=\sum_{u\cdot v=n}\frac{f_{r-1}(u)+f_{r-1}(v)}{2}
$$
乍一看无从下手，可以尝试将其展开。

由于 $(u,v)$ 为有序数对并且不要求互质，可以令 $\displaystyle u=d,v=\frac nd$，其中 $d\mid n$。
$$
\begin{aligned}
f_r(n)&=\sum_{u\cdot v=n}\frac{f_{r-1}(u)+f_{r-1}(v)}{2}\\
&=\sum_{d\mid n}\frac{f_{r-1}(d)+f_{r-1}(\frac nd)}2
\end{aligned}
$$
又可以发现每个 $d$ 与 $\displaystyle \frac nd$ 是对称的，所以在枚举过程中被枚举了两次（对于 $\displaystyle d=\frac nd$ 也是如此，只不过是枚举一次计算了两次），于是这个式子可以进一步简化为：
$$
f_r(n)=\sum_{d\mid n}f_{r-1}(d)
$$
发现这是一个狄利克雷卷积的形式，若有 $f_{r-1}$ 为积性函数，那么 $f_r$ 就是积性函数。递归下去，$f_0$ 是积性函数，所以 $f_r$ 也为积性函数。

推出了 $f_r$ 的积性，现在考虑如何计算答案 $f_r(n)$。

只有一个质因子的时候 $f_0(p^k)=2$，因此 $f_r(p^k)$ 是和 $p$ 无关的量，于是这启发我们可以把 $r$ 与 $k$ 单独拿出来考虑。

这样考虑计算答案也是没问题的，因为 $f_r$ 是积性函数，即 $\displaystyle f_r(n)=\prod_{k=1}^{\omega(n)}f_r(p^k)$。

所以现在问题就变成了如何计算出 $f_r(p^k)$。

由定义可知 $\displaystyle f_r(p^k)=\sum_{i=0}^kf_{r-1}(p^i)$，所以我们考虑一个 DP。设 $dp_{i,j}$ 表示 $f_i(p^j)$，那么初始化就是 $dp_{i,0} = 1, dp_{0,j}=2(j\ge1)$。转移时依照上式，$\displaystyle dp_{i,j}=\sum_{x=0}^jdp_{i-1,x}$。用前缀和优化一下。

第二维大小：$20$，因为 $2^{19}\lt10^6\lt2^{20}$。

```cpp
#include <bits/stdc++.h>
using namespace std;

namespace STDquantum {

template <typename T> inline void read(T &x) {
    char ch;
    while (ch = getchar(), ch > '9' || ch < '0') {}
    x = (ch ^ 48);
    while (ch = getchar(), ch >= '0' && ch <= '9')
        x = x * 10 + (ch ^ 48);
}
template <typename T> inline void write(T x) {
    static int stk[100], top = 0;
    if (x == 0) return (void)putchar('0');
    if (x < 0) x = -x, putchar('-');
    while (x) stk[++top] = x % 10, x /= 10;
    while (top) putchar(stk[top--] + '0');
}

typedef long long ll;
const int N = 1e6 + 10, K = 20, mod = 1e9 + 7;

int low[N];
void getPrime() { // 直接筛质数分解n会T飞，所以记录n的最大质因子
    for (int i = 2; i < N; ++i) {
        if (!low[i]) {
            for (int j = i; j < N; j += i) { low[j] = i; }
        }
    }
}

int dp[N][K], sum[K] = {1}; // sum[0]是一
void init() {
    getPrime();
    for (int i = 0; i < N; ++i) { dp[i][0] = 1; }
    for (int i = 1; i < K; ++i)
        dp[0][i] = 2, sum[i] = sum[i - 1] + dp[0][i];
    for (int i = 1; i < N; ++i) {
        for (int j = 1; j < K; ++j) {
            dp[i][j] = sum[j];
            sum[j] = (sum[j - 1] + dp[i][j]) % mod; // 前缀和
        }
    }
}

int r, n, q;
ll ans = 1;
inline void main() {
    init();
    for (read(q); q--; ans = 1) {
        read(r), read(n);
        int cnt, p;
        while (n != 1) {
            cnt = 0, p = low[n];
            while (n % p == 0) ++cnt, n /= p;
            ans = ans * dp[r][cnt] % mod;
        }
        write(ans), putchar('\n');
    }
}

}    // namespace STDquantum

int main() {
#ifndef ONLINE_JUDGE
#ifdef LOCAL
    freopen("D:\\OI\\STDquantum\\test.in", "r", stdin);
    freopen("D:\\OI\\STDquantum\\test.out", "w", stdout);
#endif
#ifndef LOCAL
    freopen("CF757E_Bash_Plays_with_Functions.in", "r", stdin);
    freopen("CF757E_Bash_Plays_with_Functions.out", "w", stdout);
#endif
#endif
    STDquantum::main();
    return 0;
}
```

---

## 作者：Kelin (赞：7)

$f_r(n)=\sum_{d|n}f_{r-1}(d)$


$\Rightarrow f_r=f_{r-1}\times1$


这里$\times$表示狄利克雷卷积


然后又有$f_0(n)=2^{\sigma_0(n)}$


所以$f_0$是积性函数,所以$f_r$也是积性函数


$n=\prod p_i^{k_i} \Rightarrow f_r(n)=\prod f_r(p^{k_i})$


所以只要预处理出所有的$f_r(p^j)$就ok了


设$dp_{i,j}=f_i(p^j)=\sum_{d|p^j}f_{i-1}(p^j)=\sum_{k=0}^j f_{i-1}(p^k)=\sum_{k=0}^j dp_{i-1,k}$


前缀和优化一下就$ok$了


---

## 作者：chihik (赞：6)

根据题意进行分类讨论：

令 $\tau(n)$ 为 $n$ 的不同质因数的个数。

1. $r=0$

因为要求 $\gcd(p,q)=1$ ， 那么相同的质因数只会全部在 $p$ 或 $q$ 中。

每种不同的质因数有 $2$ 种选法，那么 $f_0(n)=2^{\tau(n)}$

可以看出，$f_0(n)$ 是一个积性函数。

2. $r\not =0$

$$f_r(n)=\sum_{u \times v=n} \frac{f_{r-1}(u)+f_{r-1}(v)}{2}$$

$$f_r(n)=\sum_{u|n} \frac{f_{r-1}(u)+f_{r-1}(\frac{n}{u})}{2}$$

$$f_r(n)=\sum_{u|n} f_{r-1}(u)$$

这是一个迪利克雷卷积的形式： $f_r =f_{r-1} * 1$ 

因为 $f_0(n)$ 是一个积性函数，那么 $f_r(n)$ 也是一个积性函数，只需要求出质数的幂的函数值即可。

$$f_r(p^w)=\sum_{d|p^w} f_{r-1}(d)$$

$$f_r(p^w)=\sum_{d=0}^w f_{r-1}(p^d)$$

$$f_r(p^w)=f_{r}(p^{w-1}) +f_{r-1}(p^w)$$

递推求解就可以了。

~~所以为什么其他题解都用了前缀和啊~~

```cpp
#include <cstdio>

const int MAXN = 1e6 , LOG = 20 , Mod = 1e9 + 7;

int Add( int x , int y ) { x += y; return x >= Mod ? x - Mod : x; }
int Sub( int x , int y ) { x -= y; return x < Mod ? x + Mod : x; }
int Mul( int x , int y ) { return 1ll * x * y % Mod; }

int prnum , prime[ MAXN + 5 ] , low[ MAXN + 5 ];
bool vis[ MAXN + 5 ];
void sieve( ) {
	low[ 1 ] = 1; vis[ 1 ] = 0;
	for( int i = 2 ; i <= MAXN ; i ++ ) {
		if( !vis[ i ] ) prime[ ++ prnum ] = i , low[ i ] = i;
		for( int j = 1 ; j <= prnum && 1ll * i * prime[ j ] <= MAXN ; j ++ ) {
			vis[ i * prime[ j ] ] = 1; low[ i * prime[ j ] ] = prime[ j ];
			if( i % prime[ j ] == 0 ) break;
		}
	}
}

int f[ MAXN + 5 ][ LOG + 1 ];
void Init( ) {
	f[ 0 ][ 0 ] = 1; //f0(1)=1
	for( int i = 1 ; i <= LOG ; i ++ ) f[ 0 ][ i ] = 2; //f0(p^k)=2
	for( int i = 1 ; i <= MAXN ; i ++ ) {
		f[ i ][ 0 ] = f[ i - 1 ][ 0 ];
		for( int j = 1 ; j <= LOG ; j ++ )
			f[ i ][ j ] = Add( f[ i ][ j ] , Add( f[ i ][ j - 1 ] , f[ i - 1 ][ j ] ) );
	}
}

int T , r , n;
int main( ) {
	sieve(); Init();
	scanf("%d",&T);
	while( T -- ) {
		scanf("%d %d",&r,&n);
		int Ans = 1;
		while( n != 1 ) {
			int p = low[ n ] , w = 0;
			for( ; n % p == 0 ; n /= p , w ++ );
			Ans = Mul( Ans , f[ r ][ w ] );
		}
		printf("%d\n", Ans );
	}
	return 0;
}
```

---

## 作者：YCS_GG (赞：3)

### CF757E Bash Plays with Functions

容易发现 $f_0(x)=\sum_{d|n}[\gcd(n,\frac{n}{d})=1]$

如果要求一个数字的约数和他“剩下的”部分互质，那么说明某个质因子全部被 $d$ 包含，所以设 $n$ 有 $m$ 种质因子，每一种选或不选就是 $2^m$

$\large f_r(n)=\sum_{uv=n}\frac{f_{r-1}(u)+f_{r-1}(v)}{2}$

考虑到每个有序对 $(u,v)$ 会被算两次并且除了个 $2$ ，那么 $f_r(n)=\sum_{d|n}f_{r-1}(d)=(f_{r-1}*1)$

$f_0(x)$ 是积性的，它的卷积也是积性的，所以可以统计质因子

$\large f_r(x)=\prod\limits_{i=1}^mf_{r}(p_i^{a_i})$

$\large f_{r}(p_i^{a_i})=\sum_{d|p_i^{a_i}}f_{r-1}(d)=\sum_{k=1}^{a_i}f_{r-1}(p_i^{k})$

发现这玩意其实和 $p_i$ 是个啥没关系，只与质因子的次数之和有关，最后的 $f_0$ 只能是 $2$

进一步的，有 $f_r(p^{a_1})=f_r(p^{a_i-1})+f_{r-1}(p^{ai})$ ，就能根据幂次递推了

小trick是可以在线性筛的时候记录每个数字的最小质因子个数，就可以在$\log$的时间复杂度内计算质因子幂次了

```cpp
#include <iostream>
using namespace std;
const int N   = 1e6;
const int mod = 1e9 + 7;
int prime[N + 10], vis[N + 10], pcnt, mindiv[N + 10];
void pre() {
    mindiv[1] = 1;
    for (int i = 2; i <= N; i++) {
        if (!vis[i]) {
            prime[++pcnt] = i;
            mindiv[i]     = i;
        }
        for (int j = 1; j <= pcnt; j++) {
            if (i * prime[j] > N) {
                break;
            }
            vis[i * prime[j]]    = 1;
            mindiv[i * prime[j]] = prime[j];
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}
int f[N + 10][25];
int main() {
    pre();
    f[0][0] = 1;
    for (int i = 1; i <= 20; i++) {
        f[0][i] = 2;
    }
    for (int i = 1; i <= N; i++) {
        f[i][0] = f[i - 1][0] % mod;
        for (int j = 1; j <= 20; j++) {
            f[i][j] = (f[i][j] + (f[i][j - 1] + f[i - 1][j]) % mod) % mod;
        }
    }
    int T;
    cin >> T;
    while (T--) {
        long long ans = 1;
        int r, n;
        scanf("%d%d", &r, &n);
        while (n != 1) {
            int d = mindiv[n], cnt = 0;
            while (n % d == 0) {
                cnt++;
                n /= d;
            }
            ans = ans * f[r][cnt] % mod;
        }
        cout << ans << endl;
    }
    return 0;
}
```



---

## 作者：run_away (赞：2)

## 题意

设 $\omega(n)$ 表示 $n$ 的质因子个数，定义
$$
\begin{equation}
	f_r(n)=\left\{
	\begin{aligned}
		&\sum\limits_{p\cdot q=n} [\gcd(p,q)=1] ,&  r=0 \\
		&\sum\limits_{u\cdot v=n} \frac{f_{r-1}(u)+f_{r-1}(v)}{2} ,& r\ge 1
	\end{aligned}
	\right.
\end{equation}
$$
给出 $q$ 个 $r,n$，求出 $f_r(n)$ 的值。

## 分析

先考虑 $r=0$ 的情况，因为 $p,q$ 互质，所以两数没有共同质因子，答案即把 $\omega(n)$ 个质因子分成两份的方案数，答案为 $2^{\omega(n)}$。

考虑 $r=1$ 的情况，由唯一分解定理，$n=p_1^{a_1}p_2^{a_2}\cdots p_k^{a_k}(p_i\in\mathbb{P})$，则 $f_1(n)=\sum\limits_{d|n}f_0(d)$，由 $f_0(d)=2^{\omega(d)}$ 为积性函数，考虑把每个 $d$ 分解成这些质因子，可得 $f_1(n)=f_1(p_1^{a_1})f_1(p_2^{a_2})\cdots f_1(p_k^{a_k})$，所以 $f_1(n)$ 也是积性函数。

当 $r>1$ 时，因为不要求分出来的两个数互质，把式子展开得 $f_r(n)=\sum f_{r-1}(p_1^{b_1}p_2^{b_2}\cdots p_k^{b_k})$，其中 $b_i\in[0,a_i]$，且所有数互不相同，那这样就是一个多项式乘法的形式，由 $f_r(p_i^{a_i})=\sum\limits_{j=0}^{a_i}f_{r-1}(p_i^{j})$，得到同上的式子，所以 $f_r(n)$ 为积性函数。

可以发现 $f_r(p_i^{a_i})$ 的值与 $p_i$ 的大小没有关系，可以递推求 $r,b_i$ 固定的函数值，因为 $n\le 10^6$，所以 $b_i<20$，可以递推预处理。

询问时用积性函数的性质把 $n$ 分解，求质因子函数值的乘积即可。但是 $\sqrt n$ 直接分解太慢了，可以先筛出 $[2,10^6]$ 的最大质因子，分解时除这个因子，统计次数，这样最多是 $O(\log n)$ 的。

复杂度 $O(20r+q\log n)$。

## Code

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
// static char buf[100],*p1=buf,*p2=buf,obuf[100],*p3=obuf;
// #define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,100,stdin),p1==p2)?EOF:*p1++
// #define putchar(x) (p3-obuf<100)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x)
mt19937_64 rnd(chrono::system_clock::now().time_since_epoch().count());
#define dbg(x) cout<<#x<<": "<<x<<"\n"
#define usetime() printf("time: %.3lfs\n",clock()*1.0/CLOCKS_PER_SEC)
inline ll read(){ll x=0,f=1;char c=getchar();while(c<48||c>57){if(c==45)f=0;c=getchar();}while(c>47&&c<58)x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?x:-x;}
inline void write(ll x){if(!x){putchar(48);putchar('\n');return;}short top=0,s[40];if(x<0)x=-x,putchar(45);while(x)s[top++]=x%10^48,x/=10;while(top--)putchar(s[top]);putchar('\n');}
namespace tobe{
    const ll maxn=1e6+5,mod=1e9+7;
	ll q,r,n,f[maxn][20],mx[maxn];
	bitset<maxn>vis;
    inline void mian(){
    	f[0][0]=1;
    	for(ll i=1;i<20;++i)f[0][i]=2;
    	for(ll i=1;i<=1e6;++i){
    		ll sum=0;
    		for(ll j=0;j<20;++j){
    			sum=(sum+f[i-1][j])%mod;
    			f[i][j]=sum;
    		}
    	}
    	for(ll i=2;i<=1e6;++i){
    		if(vis[i])continue;
    		for(ll j=i;j<=1e6;j+=i){
    			mx[j]=i,vis.set(j);
    		}
    	}
		q=read();
		while(q--){
			r=read(),n=read();
			ll ans=1;
			while(n>1){
				ll now=mx[n],cnt=0;
				while(n%now==0)++cnt,n/=now;
				ans=ans*f[r][cnt]%mod;
			}
			write(ans);
		}
    }
}
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    ll t=1;
    while(t--)tobe::mian();
    // fwrite(obuf,p3-obuf,1,stdout);
    return 0;
}
```

---

## 作者：Purslane (赞：2)

# Solution

显然，设 $t(n)$ 表示 $n$ 不同质因子的总数，则 $f_0(n)=2^{t(n)}$。

而 $f_r(n) = \sum_{d \mid n} f_{r-1}(d)$。因此 $d$ 对 $f_r(n)$ 的贡献是可以计算的。

考察 $n$ 的每个质因子 $p$，假设 $v_p(n) = \beta$，$v_p(d)=\alpha$。

首先有贡献 $2^{[\alpha \neq0]}$，表示 $f_0(d)$；其次有贡献 $\dbinom{r+(\beta-\alpha)-1}{\beta-\alpha}$，这是插板法的结果。（$d$ 每次变成它的一个倍数，最后到 $n$，路径数是等价于“$r$ 个自然数和为 $\beta-\alpha$”这个不定方程的解数）

考虑到各个质因子之间是独立的，把 $n$ 质因数分解即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e6+10,MOD=1e9+7;
int T,m=1000000,n,r,flg[MAXN];
vector<int> pr;
int pw[MAXN],lst[MAXN],f0[MAXN];
vector<pair<int,int>> divs[MAXN];
void init(int mx) {
	ffor(i,2,mx) {
		if(!flg[i]) lst[i]=i,pr.push_back(i);
		for(auto v:pr) {
			if(i*v>mx) break ;
			flg[i*v]=1,lst[i*v]=v;
			if(i%v==0) break ;
		}
	}
	f0[1]=1;
	ffor(i,2,mx) {
		int u=i;
		while(u!=1) {
			int k=lst[u],cnt=0;
			while(u%k==0) cnt++,u/=k;
			divs[i].push_back({k,cnt});
		}
		f0[i]=pw[divs[i].size()];
	}
	return ;
}
int C[MAXN+500][26];
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	pw[0]=1; ffor(i,1,100) pw[i]=pw[i-1]*2%MOD;
	init(1000000);
	ffor(i,0,m+200) {
		C[i][0]=1;
		ffor(j,1,min(25,i)) C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;	
	}
	cin>>T;
	while(T--) {
		cin>>r>>n,ans=0;
		if(r==0) {cout<<f0[n]<<'\n';continue ;}
		int ans=1;
		for(auto pr:divs[n]) {
			int cnt=pr.second,mul=0;
			ffor(i,0,cnt) mul=(mul+C[r+cnt-i-1][cnt-i])%MOD;
			mul=(mul+mul)%MOD;
			mul=(mul-C[r+cnt-1][cnt])%MOD;
			ans=(1ll*ans*mul)%MOD;
		}
		cout<<(ans%MOD+MOD)%MOD<<'\n';
	}
	return 0;
}
```

---

## 作者：wangbinfeng (赞：1)

[![](https://img.shields.io/badge/题目-CF757E_Bash_Plays_with_Functions-green)
![](https://img.shields.io/badge/难度-省选/NOI−-purple)
![](https://img.shields.io/badge/考点-数论（积性函数）-blue)
![](https://img.shields.io/badge/题型-传统题-red)](https://www.luogu.com.cn/problem/CF757E)
[![](https://img.shields.io/badge/作者-wangbinfeng(387009)-yellow)](https://www.luogu.com.cn/user/387009) 

------------

[$
\def\notew{220pt}
\def\noteh{44pt}
\def\notetitlepos{24pt}
\def\notetitleh{20pt}
\def\noteSetT#1{
  \def\notetitle{\textsf{\textbf{#1}}}
}
% 标题如果不是两字则需要调整
\def\notetitleoffest{55pt}
\def\noteWarn{
  \def\notech{\kern{-1pt}⚠\kern{2.8pt}}
  \noteSetT{warning}
  \def\notelcol{#FF9100}\def\notetcol{#FFF4E5}
}
\def\noteCite{
  \def\notech{\kern{1pt}\textbf{"}\kern{3.2pt}}
  \noteSetT{引述}
  \def\notelcol{#9E9E9E}\def\notetcol{#F5F5F5}
}
\noteCite
\def\noteinfo{}
\def\drawnote{
% 画框和阴影
\color{\notelcol}
\rule{2pt}{\noteh}
\color{\notetcol}
\rule[\notetitlepos]{\notew}{\notetitleh}
\color{#e8e8e8}\rule{0.5pt}{\noteh}
\color{#f5f5f5}\rule{0.5pt}{\noteh}
\color{#fafafa}\rule{0.5pt}{\noteh}
\kern{-\notew}\kern{-1.5pt}
\def\drawx#1#2{\color{#1}\rule[#2]{\notew}{0pt}\kern{-\notew}}
\drawx{#bfbfbf}{0pt}
\drawx{#d6d6d6}{-0.5pt}
\drawx{#ececec}{-1.0pt}
\drawx{#f8f8f8}{-1.5pt}
\color{black}
% 画标题
\raisebox{\notetitlepos}{
  \raisebox{6pt}{
    \kern{-1pt}
    \color{\notelcol}\large{\notech}
    \raisebox{1.5pt}{
      \color{#404040}\footnotesize
      \kern{-4pt}\notetitle
    }
  }
}
\kern{-\notetitleoffest}%如果在下一个行内公式写文字，则该数值只需要设为极大值即可
% 也这里在这里直接放置内容，但需要使用 raisebox
\raisebox{10pt}{
  \footnotesize
  \sf{本题解所有内容均有\KaTeX完成，如果显示出错请点击这里。}
}
}% note 结束
\noteWarn\drawnote\\
$](https://www.luogu.com/article/ow4tqd3o)


$$
\begin{aligned}
& \text{为了便于分析，题面中的\;}p,q\text{\;在本题解中分别用\;}a,b\text{\;表示。}\\
& \text{先考虑\;}r=0\text{\;的情况，由算数基本定理易得：}n=p_1^{\alpha_1}+p_2^{\alpha_2}+\cdots+p_{\sigma(n)}^{\alpha_{\sigma(n)}}\text{。} \\

& \text{令\;}a=p_1^{\beta_1}+p_2^{\beta_2}+\cdots+p_{\sigma(n)}^{\beta_{\sigma(n)}}\text{，}\\

&\text{由\;}a\cdot b=n\text{\;易得：} b=p_1^{\alpha_1-\beta_1}+p_2^{\alpha_1-\beta_2}+\cdots+p_{\sigma(n)}^{\alpha_{\sigma(n)}-\beta_{\sigma(n)}} \\

&\text{由\;}\gcd(a,b)=1{\;易得：对于\;}\forall i \in[1,\sigma(n)],\beta_i\in\{0,\alpha_i\}\\

& \text{得出，}f_0(n)=\underbrace{2\times2\times\cdots\times2}_{\sigma(n)\text{\;times}}=2^{\sigma(n)}\text{。}\\

& \text{再分析\;}r\neq0\text{\;的情况，要求：}\;f_r(n)=\sum_{u\cdot v=n}\frac{f_{r-1}(u)+f_{r-1}(v)}{2}\\

&  \begin{aligned}\text{可化为：}f_r(n) &= \sum_{d|n} \frac{f_{r-1}(d)+f_{r-1}(\frac{n}{d})}{2} \\
  &= \frac{1}{2}\sum_{d|n} \frac{f_{r-1}(d)+f_{r-1}(\frac{n}{d})+f_{r-1}(\frac{n}{d})+f_{r-1}(d)}{2} \\
  &= \sum_{d|n} \frac{4\cdot f_{r-1}(d)}{4} \\
  &= \sum_{d|n}f_{r-1}(d)
\end{aligned}\\

& \text{可发现，由\;}f_0(n)\text{\;积性函数可得\;}f_r(n)\text{\;均为积性函数。证明略，具体可百度。}\\

& \text{即要求：}f_r(n)=\prod_{k=1}^{\sigma(n)}f_r(p_k^{\alpha^k})\\

& \text{需求：}f_r(p_k^{\alpha_k})=\sum_{i=0}^{\alpha_k}f_{r-1}(p_k^i)\text{，展开求解即可，其中\;}f_1(p^\alpha)=\sum_{i=0}^{\alpha}f_0(p^i)=1+2\alpha\\
& \text{综上，本题时间复杂度仅与\;}\alpha\text{\;和\;}r\text{\;有关，时间复杂度为\;}\Theta \left(r\log n\right)\text{。}
\end{aligned}
$$

------------
$
\def\notew{200pt}
\def\noteh{44pt}
\def\notetitlepos{24pt}
\def\notetitleh{20pt}
\def\noteSetT#1{
  \def\notetitle{\textsf{\textbf{#1}}}
}
% 标题如果不是两字则需要调整
\def\notetitleoffest{37pt}
\def\noteNote{
  \def\notech{\kern{-1.5pt}✒\kern{0.5pt}}
  \noteSetT{code}
  \def\notelcol{#448AFF}\def\notetcol{#ECF3FF}
}
\def\noteCite{
  \def\notech{\kern{1pt}\textbf{"}\kern{3.2pt}}
  \noteSetT{引述}
  \def\notelcol{#9E9E9E}\def\notetcol{#F5F5F5}
}
\noteCite
\def\noteinfo{}
\def\drawnote{
% 画框和阴影
\color{\notelcol}
\rule{2pt}{\noteh}
\color{\notetcol}
\rule[\notetitlepos]{\notew}{\notetitleh}
\color{#e8e8e8}\rule{0.5pt}{\noteh}
\color{#f5f5f5}\rule{0.5pt}{\noteh}
\color{#fafafa}\rule{0.5pt}{\noteh}
\kern{-\notew}\kern{-1.5pt}
\def\drawx#1#2{\color{#1}\rule[#2]{\notew}{0pt}\kern{-\notew}}
\drawx{#bfbfbf}{0pt}
\drawx{#d6d6d6}{-0.5pt}
\drawx{#ececec}{-1.0pt}
\drawx{#f8f8f8}{-1.5pt}
\color{black}
% 画标题
\raisebox{\notetitlepos}{
  \raisebox{6pt}{
    \kern{-1pt}
    \color{\notelcol}\large{\notech}
    \raisebox{1.5pt}{
      \color{#404040}\footnotesize
      \kern{-4pt}\notetitle
    }
  }
}
\kern{-\notetitleoffest}%如果在下一个行内公式写文字，则该数值只需要设为极大值即可
% 也这里在这里直接放置内容，但需要使用 raisebox
\raisebox{10pt}{
  \footnotesize
  \sf{数学题，代码就先不放啦，具体可看其他题解。}
}
}% note 结束
\noteNote\drawnote\\
$

---

## 作者：Lu_xZ (赞：1)

题意：定义函数 $f_r(n)$：

- $f_0(n)$ 为满足 $p\cdot q=n$ 且 $\gcd(p,q)=1$ 的有序对 $(p,q)$ 个数；
- $\displaystyle f_{r + 1}(n)=\sum_{u\cdot v=n}\frac{f_{r}(u)+f_{r}(v)}{2}$。

一共 $q$ 组询问，每组询问给出 $r,n$，求 $f_r(n)$ 模 $10^9+7$ 的结果。

数据范围：$q\le10^6$,$0\le r\le10^6$,$1\le n\le10^6$。

---

对于 $n = p_1^{\alpha_1}\dots p_k^{\alpha_k}$，只有 $p = \prod\limits_{i \in S}p_i^{\alpha_i} , \ q = \prod\limits_{i \notin S}p_i^{\alpha_i}$ 时会对 $f_0(n)$ 造成贡献。

所以 $f_0(n) = 2^k = 2^{\sigma(n)}$。



对于 $(p, q) = 1$，$\{p_i\} \cap\{q_i\} = \phi$。

所以 $\sigma(pq) = \sigma(p) + \sigma(q)$。

所以 $f_0(pq) = f_0(p)\cdot f_0(q)$，于是我们证明了 $f_0$ 是积性函数。

---

现在考虑 $r \ge 1$。

注意到 $(u, v)$ 与 $(v, u)$ 都有贡献，所以 $\forall d \mid n$ 对 $f_r(n)$ 的贡献为 $2 \times \dfrac{f_{r - 1}(d)}{2}$。
$$
f_r(n) = \sum\limits_{d \mid n} f_{r - 1}(d)
$$
考虑积性函数 $f(n)$，以及函数 $g(n) = \sum\limits_{d\mid n}f(d)$。

对于 $(p, q) = 1$，有
$$
\begin{aligned}
g(p) &= \sum\limits_{d_1 \mid p} f(d_1)\\
g(q) &= \sum\limits_{d_2 \mid q} f(d_2)\\

\\
g(p) \times g(q)
&= \sum\limits_{d_1 \mid p}\sum\limits_{d_2 \mid q} f(d_1)\times f(d_2)\\
&= \sum\limits_{d_1 \mid p}\sum\limits_{d_2 \mid q} f(d_1\times d_2) \\
&= g(p\times q)
\end{aligned}
$$


所以 $g(n)$ 也是积性函数。



因为 $f_0$ 是积性函数，所以 $\forall r,  (p, q) = 1, \ f_r(p\times q) = f_r(p) \times f_r(q)$。

---

于是目标 $f_r(n) = f_r(p_1^{\alpha_1})\times \dots \times f_r(p_k^{\alpha_k})$，只需预处理 $\forall r, p, \alpha, \ \ f_r(p^{\alpha})$ 即可。



不妨从 $f_0$ 开始递推。

+ $\alpha = 0$，$f_0 = 1$。
+ $\alpha > 0$，$f_0 = 2$。

$f_0(p^{\alpha})$ 的值与 $p$ 无关。

根据递推式 $f_r(p^{\alpha}) = \sum\limits_{i = 0}^{\alpha} f_{r - 1}(p^i)$，$f_r$ 只与 $f_{r - 1}$ 有关，所以 $\forall r$，$f_r(p^{\alpha})$ 的值与 $p$ 无关。

记 $dp_{r, i} = f_r(p^i)$。
$$
\begin{aligned}
dp_{r, 0} &= 0 \\
dp_{r, i} &= \sum\limits_{j = 0}^{i}dp_{r - 1, j}
\end{aligned}
$$

[submission](https://codeforces.com/contest/757/submission/258526891)

---

## 作者：hyman00 (赞：1)

# CF757E 题解

这题 *2500 有点虚高了，其实不需要用积性函数之类的结论。

首先分析 $f_r(n)$ 是什么东西：

- $r=0$

要把 $n$ 分成互质的两数乘积，对于每种质因子，可以放第一个数或第二个数，有 $2$ 种方法。

令 $\tau(n)$ 为 $n$ 的不同质因子个数，则 $f_0(n)=2^{\tau(n)}$。

- $r>0$

$$
\begin{aligned}
f_r(n)&=\sum_{u\cdot v=n}\frac{f_{r-1}(u)+f_{r-1}(v)}{2}\\
&=\sum_{u|n}\frac{f_{r-1}(u)}{2}+\sum_{v|n}\frac{f_{r-1}(v)}{2}\\
&=\sum_{u|n}f_{r-1}(u)
\end{aligned}
$$

化简得到了这样的式子。

然后考虑计算答案：

可以看作是一开始有数 $n$，需要进行 $r$ 次操作，每次变成当前数的因数，最后得分为 $2^{\tau(n')}$，求每种操作的分数之和。

对于这样的问题，容易看出不同质因子之间的贡献是无关的，可以分开计算。

这样，设存在质数 $p$，$p^k|n,p|{k+1}\not\mid n$，它的贡献可以看作是一开始有数 $k$，需要进行 $r$ 次操作，每次变成小于等于当前数的数，最后如果是 $0$，得分为 $1$，否则是 $2$，求分数之和。

设 $g(a,b)$ 是一开始有数 $a$，需要进行 $b$ 次操作，每次变成小于等于当前数的数，总共的方案数。

则之前的贡献就是 $g(k-1,r)+g(k,r)$ （每种操作都有一个贡献，如果最后预留出一个数就再有一个贡献）。

$g(a,b)$ 用插板法计算：$g(a,b)=\binom{a+b}{b}$ 

先预处理组合数，以及 $1\sim10^6$ 的质因数分解，然后把每项贡献乘起来即可。

复杂度精细实现是 $O(n\log\log n+q\tau(n))$，反正都可过。

```c++
const int N=1000106;
int fac[N],fiv[N];
vi v[N];
void pre(){
	rept(i,2,N){
		if(!sz(v[i])){
			for(int j=i;j<N;j+=i){
				int x=0,y=j;
				while(y%i==0)y/=i,x++;
				v[j].pb(x);
			}
		}
	}
	fac[0]=1;
	rept(i,1,N)fac[i]=1ll*i*fac[i-1]%MOD;
	fiv[N-1]=qp(fac[N-1],MOD-2);
	for(int i=N-1;i;i--)fiv[i-1]=1ll*fiv[i]*i%MOD;
}
inline int f(int x,int y){
	re 1ll*fac[x+y-1]*(x+x+y)%MOD*fiv[y]%MOD*fiv[x]%MOD;
}
void run(){
	int x,y;
	cin>>x>>y;
	int res=1;
	for(int i:v[y])res=1ll*res*f(i,x)%MOD;
	cout<<res<<"\n";
}
```







---

## 作者：white_carton (赞：1)

[更好的阅读体验](https://starback24.github.io)

[题目链接](https://codeforces.com/problemset/problem/757/E)

妙妙题。

### 分析

以下 $p$ 均代表质数，$a$ 和 $b$ 表示原题中的 $p,q$。

考虑将 $n$ 分解质因数，$n=p_1^{\alpha_1}p_2^{\alpha_2}\dots p_k^{\alpha_k}$，由于 $ab=n$ 且 $\gcd\left(a,b\right)=1$，每种质数只能全部分配给 $a$ 或全部给 $b$，总分配种类就是 $2^k$，所以当 $r=0$ 时，$f_0\left(n\right)=2^k$，因此 $f_0\left(p^{\alpha}\right)=2$，特别的，$f_0(1)=1$。显然，$f_0\left(p_1p_2\right)=f_0\left(p1\right)f_0\left(p2\right)$，因此，$f_0$ 是积性函数。

考虑 $r\ge1$ 的情况，$\displaystyle f_r(n)=\sum_{u\cdot v=n}\frac{f_{r-1}(u)+f_{r-1}(v)}{2}$，显然，每个因数会被计入答案两次，因此我们可以将其化简成 $\displaystyle f_r(n)=\sum_{u\mid n}f_{r-1}(u)$，接下来证明 $f_{r-1}$ 是积性函数时，$f_{r}$ 是积性函数（会用迪利克雷卷积证明的可以跳过）。

令 $n=ab,\gcd(a,b)=1$，$\displaystyle f_r(a)=\sum_{d\mid a}f_{r-1}(d)$，$\displaystyle f_r(b)=\sum_{d\mid b}f_{r-1}(d)$，有：
$$
\displaystyle f_r(ab)=\sum_{d\mid ab}f_{r-1}(d)=\sum_{d_1d_2|ab}f_{r-1}(d_1d_2)=\sum_{\begin{aligned}d_1\mid a\\d_2\mid b\end{aligned}}f_{r-1}(d_1)f_{r-1}(d_2)=\sum_{d_1\mid a}f_{r-1}(d_1)\sum_{d_2\mid b}f_{r-1}(d_2)=f_r(a)f_r(b)
\\
\square
$$
又由于 $f_0$ 是积性函数，$f_r$ 也是积性函数，因此我们对于 $f_r(n)$ 可以质因数分解后相乘求答案。

最后的问题就是如何求出  $f_r(p^k)$，由于 $f_0(p^k)$ 的值仅与 $k$ 有关，由 $f_0$ 转移来的 $f_r$ 的值也仅与 $k$ 有关。

设 $dp_{i,j}$ 为 $r=i,k=j$ 时 $f_r(p^k)$​ 的取值。显然按照定义式可以转移。

### code

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define endl '\n'
#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f3f
#define mkp make_pair
#define pb push_back
#define fir first
#define pp pop_back
#define eps 1e-8
#define sec second
#define pii pair<int,int>
#define eb emplace_back
#define file(filename) freopen(filename".in","r",stdin);freopen(filename".out","w",stdout);
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Dor(i,a,b) for(int i=a;i>=b;i--)
//==============================================================================================
// Fast IO

template<typename T>
inline T read(){
	T f=1,c=0;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-'){
			f=-1;
		}
		ch=getchar();
	}
	while(isdigit(ch)){
		c=(c<<1)+(c<<3)+(ch^48);
		ch=getchar();
	}
	T a=f*c;
	return a;
}

//=============================================================================================
//code here
const int N=1e6+10,R=20,mod=1e9+7;
#define int long long
int t,r,n;
int dp[N][R];
int low[N];
void get(){
	For(i,2,1e6){
		if(!low[i]){
			for(int j=i;j<=1e6;j+=i){
				low[j]=i;
			}
		}
	}
}
void solve(){
	int ans=1;
	r=read<int>();
	n=read<int>();
	while(n!=1){
		int s=low[n],cnt=0;
		while(n%s==0){
			n=n/s;
			cnt++;
		}
		ans=(ans*dp[r][cnt])%mod;
	}
	printf("%lld\n",ans);
}
signed main(){
	dp[0][0]=1;
	get();
	For(i,1,19){
		dp[0][i]=2;
	}
	For(i,1,1e6){
		dp[i][0]=1;
		For(j,1,19){
			dp[i][j]=(dp[i][j-1]+dp[i-1][j])%mod;
		}
	}
	t=read<int>();
	while(t--){
		solve();
	}
}
//吾日三省吾身
//输入多而不read()乎？
//1e18而不开longlong乎？
//多测不清乎？
```

---

## 作者：Hoks (赞：0)

## 前言
找性质题，看出性质一眼喵了。

摘自[杂题选做 Part 4. dp](https://www.luogu.com.cn/training/660942)。
## 思路分析
题目给的这个定义也太冗长了，我们来手模简化下。

对于 $r=0$ 时，其实就是把 $n$ 的若干个素因子划分给 $p,q$ 这两个数。

因为每个素因子都可划给 $p$ 或者 $q$，所以 $f_0(n)=2^{\omega(n)}$。

然后我们来推 $r\not=0$ 的情况~~其实注意到这个东西是狄利克雷卷积可以直接秒~~。

首先这个式子就很唐，他的 $u,v$ 是做区分的，所以说会有 $(u,v),(v,u)$ 这样的两对。

那么那个 $\frac{1}{2}$ 就可以很轻松的去掉。

$u,v$ 本质也是相同的，合并一下就可以把式子化成：
$$f_r(n)=\sum\limits_{d|n}f_{r-1}(d)$$

这里好像是无从下手了。

这里就有比较跳跃的一步，我们可以发现 $f_r(n)$ 其实都是积性函数。

在 $r=0$ 的时候很显然，然后我们来归纳证明 $r\not=0$ 的情况。

直接考虑积性函数的定义式，假设一对 $x,y$ 满足 $(x,y)=1$。

那么我们有：
$$f_{r}(xy)=\sum\limits_{d|xy}f_{r-1}(d)=\sum\limits_{(a,b)=1,a|x,b|y}f_{r-1}(a)f_{r-1}(b)$$

然后交换求和顺序：
$$=\sum\limits_{a|x}f_{r-1}(a)\sum\limits_{b|y,(a,b)=1}f_{r-1}(b)=f_r(a)f_r(b)$$

这样就证出了上面的那个结论。

然后就是求 $f_r(p^k)$ 的问题了。

有挺多方法的，比如说你注意到 $p^k$ 的因子只有 $1,p,p^2,\dots,p^k$。

那么只把 $f_r(1),f_r(p),\dots,f_r(p^k)$ 拿出来，就会发现 $r\leftarrow r+1$ 就是在累一次前缀和。

那么我们要求 $f_r(p^k)$ 其实就是这个二维矩阵的第 $r,k+1$ 个。

方法有两种。

一种直接把序列拿出来暴力累 $r$ 次前缀和，可以做到 $O(r\log n)$。

再用多项式可以变成 $O(\log n\log r)$。

第二种就是注意到这个二维矩阵倾斜过来后其实是杨辉三角，直接组合数就好了，复杂度 $O(n)$。
## 代码
太好写的东西就不放了吧。

---

