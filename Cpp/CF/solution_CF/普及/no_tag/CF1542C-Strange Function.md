# Strange Function

## 题目描述

Let $ f(i) $ denote the minimum positive integer $ x $ such that $ x $ is not a divisor of $ i $ .

Compute $ \sum_{i=1}^n f(i) $ modulo $ 10^9+7 $ . In other words, compute $ f(1)+f(2)+\dots+f(n) $ modulo $ 10^9+7 $ .

## 说明/提示

In the fourth test case $ n=4 $ , so $ ans=f(1)+f(2)+f(3)+f(4) $ .

- $ 1 $ is a divisor of $ 1 $ but $ 2 $ isn't, so $ 2 $ is the minimum positive integer that isn't a divisor of $ 1 $ . Thus, $ f(1)=2 $ .
- $ 1 $ and $ 2 $ are divisors of $ 2 $ but $ 3 $ isn't, so $ 3 $ is the minimum positive integer that isn't a divisor of $ 2 $ . Thus, $ f(2)=3 $ .
- $ 1 $ is a divisor of $ 3 $ but $ 2 $ isn't, so $ 2 $ is the minimum positive integer that isn't a divisor of $ 3 $ . Thus, $ f(3)=2 $ .
- $ 1 $ and $ 2 $ are divisors of $ 4 $ but $ 3 $ isn't, so $ 3 $ is the minimum positive integer that isn't a divisor of $ 4 $ . Thus, $ f(4)=3 $ .

Therefore, $ ans=f(1)+f(2)+f(3)+f(4)=2+3+2+3=10 $ .

## 样例 #1

### 输入

```
6
1
2
3
4
10
10000000000000000```

### 输出

```
2
5
7
10
26
366580019```

# 题解

## 作者：云浅知处 (赞：19)

> 设 $f(n)$ 为最小的满足 $d\nmid n$ 的正整数 $d$，求 $\sum_{i=1}^nf(i)$ 的值。

个人认为这题算是一道比较有趣的题qwq。

我们注意到

$$
f(i)=k\iff \operatorname{lcm}(1,2,\cdots,k-1)|i,k\nmid i
$$

因此这个 $f$ 的值域其实是非常小的，要知道 lcm 的增长至少是指数级的qwq

方便起见，我们记

$$
L_i=\operatorname{lcm}(1,2,\cdots,i)
$$

那么，对于 $i=1,2,\cdots,n$，满足 $L_{k-1}\mid i$ 的共有 $\left\lfloor\dfrac{i}{L_{k-1}}\right\rfloor$ 个。

在这些 $i$ 中，满足 $k\mid i$ 的有 $\left\lfloor\dfrac{i}{L_k}\right\rfloor$ 个。

所以，对每个 $k$，满足 $L_{k-1}\mid i,k\nmid i$ 的 $i$ 共有 $\left\lfloor\dfrac{i}{L_{k-1}}\right\rfloor-\left\lfloor\dfrac{i}{L_k}\right\rfloor$ 个。

因此，

$$
\sum_{i=1}^nf(i)=\sum_{L_i\leqslant n}i\cdot\left(\left\lfloor\dfrac{i}{L_{k-1}}\right\rfloor-\left\lfloor\dfrac{i}{L_k}\right\rfloor\right)
$$

这样，预处理 $L_i$，我们就做到了 $O(n\log n)$ 预处理 $O(\log n)$ 单次查询。

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdlib>

#define int long long
const int mod=1e9+7;

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

int ksm(int y,int z,int p){
    y%=p;int ans=1;
    for(int i=z;i;i>>=1,y=y*y%p)if(i&1)ans=ans*y%p;
    return ans%p;
}

int inv(int x,int p){return ksm(x,p-2,p)%p;}

int f[105];

int gcd(int x,int y){return (y==0)?(x):(gcd(y,x%y));}
int lcm(int x,int y){return (x/gcd(x,y))*y;}

void init(){
    f[0]=f[1]=1;
    for(int i=2;i<=100;i++)f[i]=lcm(f[i-1],i);
}

int t,n;

signed main(void){

    init();
    cin>>t;
    while(t--){
        cin>>n;
        int ans=0;
        for(int i=1;f[i]<=n;i++)ans=(ans+(i+1)*(((n/f[i])-(n/f[i+1]))))%mod;
        cout<<ans<<endl;
    }

    return 0;
}
```

---

## 作者：VinstaG173 (赞：13)

感觉这场整个数学场，这题是其中的代表作（雾

首先很容易想到对每个 $x$ 计算 $f(i)=x$ 的 $i$ 个数。

显然有若 $f(i)=x$ 则 $i \bmod{\operatorname{lcm}(1,2,\dots,x-1)}=0$ 且 $i \bmod{\operatorname{lcm}(1,2,\dots,x)} \neq 0$。由容斥原理，这样的 $i$ 有 $\dfrac{n}{\operatorname{lcm}(1,2,\dots,x-1)}-\dfrac{n}{\operatorname{lcm}(1,2,\dots,x)}$ 个。

然后就只要处理出前缀 $\operatorname{lcm}$ 就可以了。由于这个 $n$ 只有 $10^{16}$，大概处理到 $41$ 就可以了。

Code:
```cpp
#include<cstdio>
#define rg register
#define ll long long
const int ntf=1e9+7;
int t,i;
ll n,res;
ll lcm[47];
inline ll gcd(ll a,ll b)
{
	while(b^=a^=b^=a%=b);
	return a;
}
int main()
{
	scanf(" %d",&t);
	lcm[1]=1;
	while(t--)
	{
		scanf(" %lld",&n);res=0;
		for(i=2;;++i)
		{
			lcm[i]=i/gcd(lcm[i-1],i)*lcm[i-1];
			res=(res+i*(n/lcm[i-1]-n/lcm[i]))%ntf;
			if(lcm[i]>n)break;
		}
		printf("%lld\n",res);
	}
	return 0;
}
```

---

## 作者：ZCETHAN (赞：9)

## Before all
唉又没有时间打 CF，只好事后自己做了。。。
## 题目大意
定义一个函数 $f(i)$ 表示不为 $i$ 的因子的最小正整数，比如 $f(1)=2,f(2)=3,f(4)=3$。现给出一个 $n(n\le 10^{16})$，求 $\sum_{i=1}^{n}f(i)$ 的值 $\operatorname{mod} 10^9+7$。
## Solution
从简单开始思考，显然，所有的奇数的 $f(i)$ 都是 $2$。所以我们来考虑偶数。

偶数必然有因子 $1,2$，所以我们暂且认为偶数的 $f(i)=3$。为了接下来分析方便起见，我将偶数及其函数值打成一张表：
|$i$|$2$|$4$|$6$|$8$|$10$|$12$|$14$|$16$|$18$|$\dots$|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|$f(i)$|$3$|$3$|$4$|$3$|$3$|$5$|$3$|$3$|$4$|$\dots$|
不难看出，每 $6$ 个会出现一个 $4$，每 $12$ 个会出现一个 $5$……

那么这个 $6$ 和 $12$ 是哪里来的呢？

我们不妨把 $f(i)=3$ 的偶数表示为 $2$，除此以外的因子都比 $3$ 大的形式。那么 $6$ 就是 $2\times 3$，除此以外因子都比 $4$ 大……

所以，我们可以先打表来算这个每一个 $f(i)$ 的出现周期。我们需要保证这个值是包含因子 $1, 2, \dots, [f(i)-1]$ 的最小值，设 $f(i)-1$ 的周期为 $s$，那么这个值只需要在 $s$ 的基础上使得它能够被 $f(i)-1$ 整除，所以就是 $f(i)-1$ 和 $s$ 的最小公倍数。

最后统计答案的时候，遍历每个 $f(i)$ 的周期，由于我们是逐一考虑 $f(i)$ 的，所以每次只要加上 $\left\lfloor\dfrac{n}{s}\right\rfloor$ 即可。
## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define inf (1<<30)
#define INF (1ll<<60)
using namespace std;
const ll MAXN=1e16;
const ll MOD=1e9+7;
ll top[110];
void solve(){
	ll n;
	scanf("%lld",&n);
	ll ans=n*2%MOD;//加上奇数的值，并先把偶数的 3 加上 2
	ans=(ans+n/2)%MOD;//先钦定所有偶数都是 3，由于上一行中已经加了 2，所以这里每个偶数只要 +1
	for(int i=4;top[i]<=n;i++){
		ans=(ans+n/top[i])%MOD;
		//同理，我已经加了小 1 的值，所以这里每次只需要增加 1 就行
	}
	printf("%lld\n",ans);
}
ll gcd(ll x,ll y){return x%y==0?y:gcd(y,x%y);}
int main()
{
	for(ll i=4,cur=2;cur<=MAXN;i++){
		ll g=gcd(i-1,cur);
		cur=cur*(i-1)/g;
		top[i]=cur;
	}//打表，top[i] 表示 f(x)=i 的周期
	int T;
	for(scanf("%d",&T);T--;)
		solve();
	return 0;
}
/*

*/
```

---

## 作者：code_hunter (赞：6)

刚调完，比赛正好结束（上分失败）的选手来水题解了！

## 分析 & 解法
首先函数 $f(n)$ 非常特别。通过计算机可以证明，当 $ 1\leq n\leq 10^{16}$ 时，$2\leq f(n) \leq 41$.事实上，若 $f(n)\geq42$ , 则 
$n\leq 
\operatorname{lcm}_{x=1}^{42}x=219060189739591200
$
与 $ 1\leq n\leq 10^{16}$ 相矛盾。

考虑使用筛法，将 i 从 2 枚举 到 41 ， 筛去当前所有数中非 i 的倍数并更新 ans 即可。具体地，当 i = k 时，当前所有未被筛去的都是 $\operatorname{lcm}_{x=1}^{k-1}x$ 的倍数,令 
$lc = \operatorname{lcm}_{x=1}^{k-1}x$ , 则显然 不整除$\operatorname{gcd}(lc , k)$ 的数均已被筛去，那么只需在已完成筛的基础上再筛一次 $\frac{k}{\operatorname{gcd}(lc , k)}$ 即可。
## 代码（欢迎 hack）
```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

#define For(i,a,b) for(int i = a ; i <= b ; i ++)
#define FoR(i,a,b) for(int i = a ; i >= b ; i --)
typedef long long ll;
typedef double dl;
ll MAX(ll x , ll y) {return (x > y) ? x : y;}
ll MIN(ll x , ll y) {return (x < y) ? x : y;}

const int MAXN = 537;
const ll MO = 1e9 + 7;

using namespace std;

inline int Read() {
	register int x = 0;
	bool flag = false;
	register char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
			flag = true;
		ch = getchar();
	}
	if (flag) {
	    while ('0' <= ch && ch <= '9') {
	   		 x = x * 10 - ch + '0';
			 ch = getchar();
	    }
	}
	else {
        while ('0' <= ch && ch <= '9') {
	   		 x = x * 10 + ch - '0';
			 ch = getchar();
	    }
	}
	return x;
}

ll gcd(ll a , ll b) {
	return b ? gcd(b , a % b) : a;
}

int T;
ll N , ans , lc;
void work() {
	ans = 0;
	scanf ("%lld" , &N);
	ans = 0;
	lc = 1;
	for (ll i = 1 ; ; i ++) {
		if (N <= 0)
			break;
		ll u = i / gcd(lc , i);
		ans += (N - N / u) * i;
		N /= u;
		lc *= u;
	}
	printf ("%lld\n" , ans % MO);
}

int main() {
	T = Read();
	while (T --)
		work();
	return 0;
}
```


---

## 作者：MatrixCascade (赞：5)

貌似也是套路题。~~话说感觉这场比赛 BC 都比 D 思维难度高~~

设 $g_x$ 为 $lcm_{(1,2,...,x)}$，则如果一个数能被 $g_{i}$ 整除并且不能被 $g_{i+1}$ 整除，那么 $f_{x}=i+1$。

我们设 $dp_i$ 表示能被 $g_i$ 整除且不能被 $g_{i+1}$ 整除的数，注意到 $g_{41}>10^{16}$，因此只需要求 $dp_{1\to40}$ 即可。

考虑容斥，$dp_i$ 显然是能被 $g_{i}$ 整除的所有数的数量-能被$g_{i+1\to40}$整除的数，前者等于 $\frac{n}{g_i}$，后者可以从 $40\to1$倒着扫，记录一个后缀和，就可以每次 $O(1)$ 解决

时间复杂度 $O(40T)$

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define int long long
#define up(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define down(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
using namespace std;
int n, m, k;
int read()
{
    int s = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        s = s * 10 + ch - '0';
        ch = getchar();
    }
    return s * f;
}
const int mod=1e9+7;
int f[50];
int dp[50];
signed main()
{
	int T=read();
	f[1]=1;
	up(i,2,41)
	{
		f[i]=1ll*i/__gcd(i,f[i-1])*f[i-1];
	}
	while(T--)
	{
		n=read();
		up(i,1,41)
		{
			dp[i]=(n/f[i])%mod;
		}
		int ans=0;
		int nw=0;
		down(i,41,1)
		{
			dp[i]-=nw;
			nw+=dp[i];
			nw%=mod;
			dp[i]+=mod;
			dp[i]%=mod;
			ans+=dp[i]*(i+1)%mod;
			ans%=mod;
		}
		cout<<ans<<endl;
	}
}

```


---

## 作者：SpeedStar (赞：5)

### 算法分析

注意到，$f(k) = x$ 意味着 $1, 2, \cdots, x - 1$ 都是 $k$ 的因子，所以我们可以得到 ${\rm lcm}(1, \cdots, x - 1) \mid k$，而 $x \nmid k$，那么在 $f(1) \sim f(n)$ 中使得 $f(k) = x$ 的 $k$ 的个数是 $\lfloor \frac{n}{{\rm lcm}(1, \cdots, x - 1)}\rfloor - \lfloor \frac{n}{{\rm lcm}(1, \cdots, x)}\rfloor$。
然后计算不同的 $f(k)$ 对答案的贡献即可。

#### C++ 代码
```
#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (n); ++i)

using std::cin;
using std::cout;
using std::istream;
using std::ostream;
using std::vector;
using ll = long long;

// const int mod = 998244353;
const int mod = 1000000007;
struct mint {
    ll x;
    mint(ll x=0):x((x%mod+mod)%mod) {}
    mint operator-() const {
        return mint(-x);
    }
    mint& operator+=(const mint a) {
        if ((x += a.x) >= mod) x -= mod;
        return *this;
    }
    mint& operator-=(const mint a) {
        if ((x += mod-a.x) >= mod) x -= mod;
        return *this;
    }
    mint& operator*=(const mint a) {
        (x *= a.x) %= mod;
        return *this;
    }
    mint operator+(const mint a) const {
        return mint(*this) += a;
    }
    mint operator-(const mint a) const {
        return mint(*this) -= a;
    }
    mint operator*(const mint a) const {
        return mint(*this) *= a;
    }
    mint pow(ll t) const {
        if (!t) return 1;
        mint a = pow(t>>1);
        a *= a;
        if (t&1) a *= *this;
        return a;
    }

    // for prime mod
    mint inv() const {
        return pow(mod-2);
    }
    mint& operator/=(const mint a) {
        return *this *= a.inv();
    }
    mint operator/(const mint a) const {
        return mint(*this) /= a;
    }
};
istream& operator>>(istream& is, mint& a) {
    return is >> a.x;
}
ostream& operator<<(ostream& os, const mint& a) {
    return os << a.x;
}

int main() {
	int t;
	cin >> t;
	
	while (t--) {
		ll n;
		cin >> n;
		vector<ll> a(2, 1);
		while (a.back() <= n) {
			ll next = std::lcm(a.back(), a.size());
			a.push_back(next);
		}
		mint ans;
		for (auto x : a) ans += n / x;
		cout << ans << '\n';
	}
	
	return 0;
}
```

---

## 作者：Refined_heart (赞：2)

首先观察到，对于奇数， $2$ 就是它们的 $f$ 值。

考虑将 $2$ 提出来，发现剩下的数又组成了一个 $1\to len$ 的公差为 $1$ 的数列。

这启示我们类似的解题方法：能不能这样递归分治计算答案呢？

对数据打表，发现 $f$ 很小，而且全部都是质数的次幂。

所以我们只需要对前 $60$ 个左右的质数次幂进行计算就足以。

关于质因子次幂的证明：


>考虑已经计算过了前 $i$ 个 $f,$ 那么它们消去的因数应该是它们的**最小公倍数**。 

>那么新加进去的一个答案 $f'$ 如果有贡献，那必然不能包含于之前的最小公倍数。

>所以它一定是某质数的次幂。

那么我们可以线性筛一下质数之后，计算答案。

考虑每次加入的一个数 $f'$ 有多少贡献：首先需要把之前去掉的因数除去，而它对最小公倍数的贡献应该是它所属于的质数次幂的底数。

设 $f'=p_i^{a}.$ 因为之前已经去掉了它对应质数的 $a-1$ 次幂，所以这里要以 $p$ 来计算个数，计算答案用 $f'.$ 

~~晚上就因为这里写炸了导致没写出来~~

到这里为止就可以做到 $O(\log v)$ 级别计算答案了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
inline int read()
{
	int s = 0 , w = 1 ;
	char ch = getchar ( ) ;
	while ( ! isdigit ( ch ) )
	{
		if ( ch == '-' ) w = -1 ;
		ch = getchar ( ) ;
	}
	while ( isdigit ( ch ) )
		s = s * 10 + ch - 48 , ch = getchar ( ) ;
	return w * s ;
}
int T;
typedef long long ll;
map<ll,int>mp;
ll p[100000],cnt;
ll n;
int vis[100010];
vector<ll>v;
ll gcd(ll a,ll b){return !b?a:gcd(b,a%b);}
inline ll Max(ll a,ll b){return a>b?a:b;}
void solve(ll x){
	ll Lcm=1;
	ll ans=0;
	for(int i=0;i<62;++i){
		if(Lcm>1e16)break;
		ll cnt=x/mp[v[i]];
		ll len=x-cnt;
		ans+=len*v[i];
		ans%=mod;
//		cout<<mp[i]<<" "<<len<<endl;
		Lcm=Lcm*v[i]/gcd(Lcm,v[i]);
		x=n/Lcm;
	}
	cout<<ans<<endl;
}
signed main(){
	T=read();
	for(register int i=2;i<=50000;++i){
		if(i!=2&&i!=3&&(i+1)%6!=0&&(i-1)%6!=0)continue; 
		if(!vis[i])p[++cnt]=i;
		for(register int j=1;j<=cnt&&i*p[j]<=50000;++j){
			vis[i*p[j]]=1;
			if(i%p[j]==0)break;
		}
	}
	for(int i=1;i<=cnt;++i){
		ll pw=p[i];
		for(int j=1;j<=20;++j){
			if(pw>1000000000000000ll)break;
			mp[pw]=p[i];
			v.push_back(pw),pw=pw*p[i];
		}
	}
	sort(v.begin(),v.end());
//	for(int i=0;i<70;++i)cout<<v[i]<<" ";
	while(T--){
		cin>>n;
		solve(n);
	}
	return 0;
} 
/*
6
1
2
3
4
10
10000000000000000
*/
```

---

## 作者：Aehnuwx (赞：2)

以下令 $[\alpha_1,\alpha_2,\cdots,\alpha_n]=\operatorname{lcm}(\alpha_1,\alpha_2,\cdots,\alpha_n)$

----------

对于一个数 $n$，显然 $\forall i\in [1,f(n)),i\mid n$

所以 $[1,2,\cdots,f(n)-1]\mid n$

打表可以发现，$[1,2,\cdots,41]<1e16,[1,2,\cdots,42]>1e16$

所以我们可以先预处理 $[1],[1,2],\cdots,[1,2,\cdots,41]$

对于一个数 $n$，易得对于 $i\in [1,n]$，满足 $[1,2,\cdots,i]\mid n$ 且 $[1,2,\cdots,i+1]\nmid n$ 的数的数量为 $a_i=\lfloor n/[1,2,\cdots,i]\rfloor-\lfloor n/[1,2,\cdots,i+1]\rfloor$

则有且仅有 $a_i$ 个 $i$ 满足 $f(i)=i+1$

所以答案即为 $\sum\limits_{i=1}^n a_i\cdot f(i)=\sum\limits_{i=1}^n a_i(i+1)$

代码：

```cpp
#include<cstdio>
#include<cstring>

using namespace std;

#define int long long
const int M=1e9+7;
int gcd(int a,int b){
	return !b?a:gcd(b,a%b);
}

int lcm(int a,int b){
	return a*b/gcd(a,b);
}

signed main(){
  int t=1; scanf("%lld",&t);
  int d[43];
  d[0]=1;
  int i;
  for(i=1;i<=41;i++) d[i]=lcm(d[i-1],i);
	int a[43],b[43];
  while(t--){
  	memset(b,0,sizeof b);
  	int n;
		scanf("%lld",&n);
		for(i=1;i<=41;i++){
			if(n<d[i]) break;
			b[i]=n/d[i];
		}
		for(int j=1;j<i;j++) a[j]=b[j]-b[j+1];
		int ans=0;
		for(int j=1;j<i;j++){
			ans=(ans+a[j]*(j+1))%M;
		}
		printf("%lld\n",ans);
  }
  return 0;
}
```



---

## 作者：lndjy (赞：1)

首先观察到，$f(i)$ 很小。因为 $f(i)=j$ 需要 $f(i)$ 模 $1$ 到 $j-1$ 的所有数都为零，即 $f(i)\equiv0\pmod{\operatorname{lcm}(1,2,...j-1)}$。而 $\operatorname{lcm}(1,2,...j)$ 是增长非常快的，所以 $f(i)$ 很小。

考虑枚举 $f(i)$ 的值计算这个值有多少次。

若目前的 $f(i)=j$，那么 $f(i)\equiv0\pmod{\operatorname{lcm}(1,2,...j-1)}$ 且 $f(i)\bmod j\neq 0$ 的个数即为出现次数。

一个简单的容斥，出现次数为 $f(i)\equiv0\pmod{\operatorname{lcm}(1,2,...j-1)}$ 的个数减去 $f(i)\equiv0\pmod{\operatorname{lcm}(1,2,...j)}$ 的个数。$a\bmod b=0$ 的个数就是 $\frac{a}{b}$。

```cpp
#include<iostream>
#define int long long
using namespace std;
const int p=1e9+7;
int gcd(int a,int b)
{
	if(b==0) return a;
	return gcd(b,a%b);
}
signed main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int n;
		cin>>n;
		int now=1,ans=0;
		for(int i=2;;i++)
		{
			ans+=i*(n/now-n/(now*i/gcd(now,i)))%p;
			ans=ans%p;
			now=now*i/gcd(now,i);
			if(now>n) break;
		}	
		cout<<ans%p<<endl;
	}
	return 0;
}
```


---

## 作者：feicheng (赞：0)

## $\mathtt{Description}$

定义函数 $f(x)$ 为最小的不是 $x$ 的因数的数。

求 $\sum_{x = 1}^nf(x)$ 对 $10^9 + 7$ 取模的结果

$1\leq n\leq10^{16}$

## $\mathtt{Solution}$

发现大多数的 $f$ 值都是相同的，这引导我们使用筛法。

由于 $\max f(x) = 41$，所以我们可以直接枚举 $f(x)$ 的值，筛去所有不是 $f(x)$ 的倍数的数。在枚举 $f(x)=k$ 时，所有的 

$$\text{LCM} = \text{lcm}(1,2,\cdots,k-1)$$ 

的倍数已经筛掉了，所以我们只需要筛 $\dfrac {k} {\gcd(\text{LCM},k)}$ 即可。


---

