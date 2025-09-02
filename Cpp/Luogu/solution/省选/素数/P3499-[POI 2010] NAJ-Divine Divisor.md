# [POI 2010] NAJ-Divine Divisor

## 题目描述

An integer ![](http://main.edu.pl/images/OI17/naj-en-tex.1.png) is given.

We say that an integer ![](http://main.edu.pl/images/OI17/naj-en-tex.2.png) is a divisor of ![](http://main.edu.pl/images/OI17/naj-en-tex.3.png) with multiplicity ![](http://main.edu.pl/images/OI17/naj-en-tex.4.png)    (![](http://main.edu.pl/images/OI17/naj-en-tex.5.png) is integer) if ![](http://main.edu.pl/images/OI17/naj-en-tex.6.png) and ![](http://main.edu.pl/images/OI17/naj-en-tex.7.png) does not divide ![](http://main.edu.pl/images/OI17/naj-en-tex.8.png).

For example, the number ![](http://main.edu.pl/images/OI17/naj-en-tex.9.png) has the following divisors:

2 with multiplicity 4, 3 with multiplicity 1, 4 with multiplicity 2, 6 with multiplicity 1, and so on.

We say that a number ![](http://main.edu.pl/images/OI17/naj-en-tex.10.png) is a  divine divisor of the number ![](http://main.edu.pl/images/OI17/naj-en-tex.11.png)    if ![](http://main.edu.pl/images/OI17/naj-en-tex.12.png) is a divisor of ![](http://main.edu.pl/images/OI17/naj-en-tex.13.png) with multiplicity ![](http://main.edu.pl/images/OI17/naj-en-tex.14.png) and ![](http://main.edu.pl/images/OI17/naj-en-tex.15.png) has no divisors    with multiplicities greater than ![](http://main.edu.pl/images/OI17/naj-en-tex.16.png).

For example, the sole divine divisor of 48 is 2 (with multiplicity 4),    and the divine divisors of 6 are: 2, 3 and 6 (each with multiplicity 1).

Your task is to determine the multiplicity of divine divisors of ![](http://main.edu.pl/images/OI17/naj-en-tex.17.png)    and the number of its divine divisors.

给定一个正整数 $m$ 以及长度为 $m$ 的正整数序列  $a$ ,同时给出  $n = \prod_{i=1}^{m}{a_i}$。你需要找出一个最大的 $k$ 使得存在一个 $d$ , $d > 1$ 并且 $d^k | n$。求这个最大的 $k$ 以及在 $k$ 最大的情况下有多少个 $d$ 满足条件。

## 说明/提示

$1\le m\le 600$，且$\forall 1\le i\le m$，有$1\le a_i\le 10^{18}$


## 样例 #1

### 输入

```
3
4 3 4```

### 输出

```
4
1```

# 题解

## 作者：skylee (赞：6)

# [POI2010]Divine Divisor
## 题目大意：
给你$m(m\le600)$个数$a_i(a_i\le10^{18})$。$n=\prod a_i$。现在要你找到一个最大的$k$使得$\exists d\ne1,d^k|n$，并求出有多少$d$满足这样的条件。

## 思路：
首先线性筛预处理出$10^6$以内的所有质数，用这些质数除$a_i$，剩下的$a_i$分为以下$4$种情况：
1. $a_i=1$，表示$a_i$的所有素数均被找出。
2. $a_i=p^2$，可以判断$\lfloor\sqrt{a_i}\rfloor$是否等于$\lceil\sqrt{a_i}\rceil$，是的话就说明这是两个$>10^6$的质数平方。
3. $a_i=p$，可以使用Miller-Rabin算法判断是否为质数。
4. $a_i=pq$，对于这样的数，可以与其它所有数求一遍$\gcd$。若$\gcd\ne1$就说明我们成功分解了它的质因数。否则虽然我们不能知道它的质因数到底是什么，但是我们可以知道它与其它数没有共同的质因数，因此我们只需要统计出现的次数，而不需要关心其具体数值。

对于每个质数，我们统计其出现次数$cnt[i]$。第一个答案就是$\max\{cnt[i]\}$。若有$k$个质数的出现次数为$\max\{cnt[i]\}$，则第二个答案就是$2^k-1$。

由$k$可能会很大，需要写高精度。

但是我们可以注意到,若不考虑$-1$，答案就是$2$的幂。用浮点数来储存不会丢失精度，且$-1$后不会发生退位。因此可以先用浮点数计算$2^k$，转成字符串，再在最后一位$-1$。

## 源代码：
```cpp
#include<map>
#include<cmath>
#include<ctime>
#include<cstdio>
#include<cctype>
#include<cstring>
#include<cstdlib>
#include<algorithm>
typedef long long int64;
typedef __int128 int128;
inline int64 getint() {
	register char ch;
	while(!isdigit(ch=getchar()));
	register int64 x=ch^'0';
	while(isdigit(ch=getchar())) x=(((x<<2)+x)<<1)+(ch^'0');
	return x;
}
const int M=601,LIM=1e6+1,P=78499;
bool vis[LIM];
int p[P],b[M];
int64 a[M];
std::map<int64,int> cnt,cnt2;
inline void sieve() {
    vis[1]=true;
    for(register int i=2;i<LIM;i++) {
        if(!vis[i]) p[++p[0]]=i;
        for(register int j=1;j<=p[0]&&i*p[j]<LIM;j++) {
            vis[i*p[j]]=true;
            if(i%p[j]==0) break;
        }
    }
}
inline int64 montgomery(int64 a,int64 k,const int64 &mod) {
	int64 ret=1;
	for(;k;k>>=1) {
		if(k&1) ret=(int128)ret*a%mod;
		a=(int128)a*a%mod;
	}
	return ret;
}
inline bool miller_rabin(const int64 &x) {
    for(register int i=0;i<5;i++) {
        const int64 a=(int64)rand()*rand()%(x-2)+2;
        if(montgomery(a,x-1,x)!=1) return false;
    }
    return true;
}
char ans[1000];
int main() {
	sieve();
	srand(time(NULL));
	const int m=getint();
	for(register int i=1;i<=m;i++) {
		a[i]=getint();
		for(register int j=1;j<=p[0]&&a[i]!=1;j++) {
			while(a[i]%p[j]==0) {
				a[i]/=p[j];
				cnt[p[j]]++;
			}
		}
		if(a[i]==1) continue;
		if(floor(sqrt(a[i]))==ceil(sqrt(a[i]))) {
			cnt[sqrt(a[i])]+=2;
			b[i]=1;
			continue;
		}
		if(miller_rabin(a[i])) {
			cnt[a[i]]++;
			b[i]=2;
			continue;
		}
	}
	for(register int i=1;i<=m;i++) {
		if(a[i]==1||b[i]) continue;
		for(register int j=1;j<=m;j++) {
			if(a[i]==a[j]||a[j]==1) continue;
			const int64 d=std::__gcd(a[i],a[j]);
			if(d==1) continue;
			cnt[d]++;
			cnt[a[i]/d]++;
			goto Next;
		}
		cnt2[a[i]]++;
		Next:;
	}
	int ans1=0,ans2=0;
	for(register std::map<int64,int>::iterator i=cnt.begin();i!=cnt.end();i++) {
		ans1=std::max(ans1,i->second);
	}
	for(register std::map<int64,int>::iterator i=cnt2.begin();i!=cnt2.end();i++) {
		ans1=std::max(ans1,i->second);
	}
	for(register std::map<int64,int>::iterator i=cnt.begin();i!=cnt.end();i++) {
		if(i->second==ans1) ans2++;
	}
	for(register std::map<int64,int>::iterator i=cnt2.begin();i!=cnt2.end();i++) {
		if(i->second==ans1) ans2+=2;
	}
	printf("%d\n",ans1);
	sprintf(ans,"%.Lf",ldexpl(1,ans2));
	ans[strlen(ans)-1]--;
	puts(ans);
	return 0;
}
```

---

## 作者：Kreado (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/P3499)

本题主要考查 [Pollard-Rho 算法](https://www.luogu.com.cn/problem/P4718)。

#### 思路

数据不是很大，所以我们可以使用 Prollard-Rho 算法分解质因数，映射到数组 $S$ 中，很明显 $k$ 的值为 $S$ 数组中出现最多的数的次数，令 $cnt$ 为在 $S$ 数组中与 $k$ 相等的数的个数，则满足条件的 $d$ 的方案数为 $2^{cnt}-1$。$2^{cnt-1}$ 可能会很大，这里需要用高精。

不考虑 $-1$ 对答案的贡献，则剩下的式子为 $2$ 的幂，可以用 `long double` 存 $2^{cnt-1}$，转成字符串在进行减 1 操作。

对于 Pollard-Rho 算法，这里浅谈一下，本质上是随机化，利用生日悖论来提高算法的正确率。随机选出两个数 $x,y$，两个数的差的绝对值有很大可能为 $N$ 的因子，即 $\gcd(\left|x-y\right|,N)>1$，时间复杂度依旧是很高，可以利用 Floyd 判圈法提升速度。

有以下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/yaihaze5.png)

这也就说明为什么算法名有一个 $\rho$ 了。

#### 贴贴代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define Auto map<ll,ll>::iterator
#define lll __int128
using namespace std;
const ll Maxn=610,inf=0x3f3f3f3f;
map<ll,ll>S;
char ans[Maxn];
namespace Math{
	inline ll mul(ll a,ll b,ll p){
		a%=p,b%=p;
		ll c=a*b-(ll)((long double)a*b/p+0.5)*p;
		return c<0?c+p:c;
	}
	inline ll ksm(ll a,ll b,ll Mod)
	{ll z=1;while(b){if(b&1)z=(lll)z*a%Mod;a=(lll)a*a%Mod;b>>=1;}return z;}
	inline ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
}
using namespace Math;
namespace Miller_Rabin{
	ll Test[11]={0,2,7,41,61};
	inline bool Prime(ll X){
		if(X<2) return false;
		ll k=0,t=X-1;
		while(1^(t&1)) t>>=1,++k;
		for(ll i=1;i<=4;i++){
			if(X==Test[i]) return true;
			ll A=ksm(Test[i],t,X),Next=A;
			for(ll j=1;j<=k;j++){
				Next=mul(A,A,X);
				if(Next==1&&A!=1&&A!=X-1) return false;
				A=Next;
			}
			if(Next!=1) return false;
		}
		return true;
	}
}
using namespace Miller_Rabin;
namespace Pollard_Rho{
	#define Rand(P) (rand()*rand()%(P)+1)
	inline ll PR(ll X,ll Y){
		ll t=0,k=1,v0=Rand(X-1),v1=v0,d,s=1;
		while(true){
			v1=(mul(v1,v1,X)+Y)%X;s=mul(s,abs(v1-v0),X);
			if(!(v1^v0)||!s) return X;
			if(++t==k){if((d=gcd(s,X))^1)return d;v0=v1;k<<=1;}	
		}
	}
	inline void solve(ll X){
		if(X<2) return ;
		if(Prime(X)){S[X]++;return ;}
		ll Y=X;while((Y=PR(X,Rand(X)))==X);
		solve(X/Y);solve(Y);
	}
}
ll m,a,ans1=-inf,cnt;
int main(){
	srand(time(0));
	scanf("%lld",&m);
	for(ll i=1;i<=m;i++) scanf("%lld",&a),Pollard_Rho::solve(a);
	for(Auto it=S.begin();it!=S.end();it++) ans1=max(ans1,it->second);
	for(Auto it=S.begin();it!=S.end();it++) cnt+=(ans1==it->second);
	printf("%lld\n",ans1);
	sprintf(ans,"%.0Lf",powl(2.0L,cnt));
	ans[strlen(ans)-1]--;
	cout<<ans;
	return 0;
}
```


---

## 作者：Leasier (赞：1)

前置芝士：[Pollard-Rho 算法](https://oi-wiki.org/math/number-theory/pollard-rho/)

考虑对每个 $a_i$ 用 Pollard-Rho 算法分解质因数，则显然 $k =$ 乘积中幂次最大的质因数的幂次，满足条件的 $d$ 即为从幂次 $= k$ 的质因数的个数任选一个**非空**子集的方案数，即：设 $cnt =$ 幂次 $= k$ 的质因数的个数，则答案为 $2^k - 1$。

如果你跟我一样懒得写高精，可以考虑用浮点数储存 $2^k$，在转换为字符串后减一。

注意需要开 long double，且字符数组至少需要开 $418$ 位（实际位数为 $417$ 位，开 $418$ 位是因为要考虑末尾的 `\0`）。最大的结果可由[这组](https://www.luogu.com.cn/paste/6nierktc)数据给出。

代码：
```cpp
#include <iostream>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>

using namespace std;

typedef long long ll;
typedef __int128 lll;

const int N = 9, M = 417 + 7, K = 1 << 7;
int test_prime[N + 7] = {0, 2, 3, 5, 7, 11, 13, 17, 19, 23};
char ans_cnt[M];
map<ll, int> mp;

inline ll quick_pow(ll x, ll p, ll mod){
	ll ans = 1;
	while (p){
		if (p & 1) ans = (lll)ans * x % mod;
		x = (lll)x * x % mod;
		p >>= 1;
	}
	return ans;
}

inline bool is_prime(ll n){
	if (n < 2) return false;
	int cnt = 0;
	ll m = n - 1, k = m;
	while (k % 2 == 0){
		k /= 2;
		cnt++;
	}
	for (register int i = 1; i <= N; i++){
		if (n == test_prime[i]) return true;
		ll a = quick_pow(test_prime[i], k, n), b = a;
		for (register int j = 1; j <= cnt; j++){
			b = (lll)b * a % n;
			if (b == 1 && a != 1 && a != m) return false;
			a = b;
		}
		if (a != 1) return false;
	}
	return true;
}

inline ll floyd(ll a, ll b, ll p){
	return ((lll)a * a % p + b) % p;
}

inline ll abs64(ll n){
	return n >= 0 ? n : -n;
}

ll gcd(ll a, ll b){
	return b == 0 ? a : gcd(b, a % b);
}

inline ll pollard_pho(ll n){
	ll x = 0, c = rand() % (n - 1) + 1;
	for (register int i = 1; ; i <<= 1){
		ll y = 1, z = x;
		for (register int j = 1; j <= i; j++){
			x = floyd(x, c, n);
			y = (lll)y * abs64(x - z) % n;
			if (j == i || j % K == 0){
				ll ans = gcd(n, y);
				if (ans > 1) return ans;
			}
		}
	}
}

void decompound(ll n){
	if (n < 2) return;
	if (is_prime(n)){
		mp[n]++;
		return;
	}
	ll factor;
	do {
		factor = pollard_pho(n);
	} while (factor == n);
	decompound(factor);
	decompound(n / factor);
}

int main(){
	int m, len, cnt = 0, ansk = 0;
	cin >> m;
	srand(time(NULL));
	for (register int i = 1; i <= m; i++){
		ll a;
		cin >> a;
		decompound(a);
	}
	for (register map<ll, int>::iterator i = mp.begin(); i != mp.end(); i++){
		ansk = max(ansk, i->second);
	}
	cout << ansk << endl;
	for (register map<ll, int>::iterator i = mp.begin(); i != mp.end(); i++){
		if (i->second == ansk) cnt++;
	}
	sprintf(&ans_cnt[1], "%.0Lf", powl(2.0L, cnt));
	len = strlen(&ans_cnt[1]);
	for (register int i = len; i >= 1; i--){
		if (ans_cnt[i] >= '1'){
			ans_cnt[i]--;
			break;
		}
		ans_cnt[i] = '9';
	}
	cout << &ans_cnt[1];
	return 0;
}
```

---

## 作者：MuYC (赞：1)

[P3499 [POI2010]NAJ-Divine Divisor](https://www.luogu.com.cn/problem/P3499)

#### 题意简述

给定一个正整数  $m$ 以及长度为  $m$ 的正整数序列 $a$ ，同时给出   $n = \prod_{i=1}^{m}{a_i}$。

你需要找出一个最大的  $k$ 使得存在一个 $d$ , $d > 1$ 并且 $d^k | n$。求这个最大的  $k$ 以及在  $k$ 最大的情况下有多少个 $d$ 满足条件。 

$m <= 600$， $1 <= a_i <= 10^{18}$

#### 思路


关于这道题目，实际上就是让我们找出出现次数最多的质因子以及跟它出现次数相同的质因子的个数（假设为 $w$），它出现的次数为 $k$ 也就是答案为 $k$ ，同时那么存在的 $d$ 的个数就是 $2^w - 1$。这毫无疑问。

然后我们现在要求出出现次数最多的质因子出现了多少次。那么很显然的 $10^{18}$ 的数据范围无法使用 $\sqrt{n}$ 级别的算法来做这一道题目。于是我们用 [Pollard Rho 和 Miller Rabin](https://www.cnblogs.com/MYCui/p/14478796.html) 算法来优化这道题目。

但是，因为 Pollard Rho 如果要去分解一个大数的所有质因子的话，倘若这个大数的质因子很多，那么 Pollard Rho 的时间复杂度将无法保证。考虑怎么优化这个过程。 

Pollard Rho 算法其实在使用的时候有一个小 $trick$，如果一个数含有很小的质因子，那么没有必要去用 Pollard Rho 算法去找这些很小的因子，反而不如直接先用暴力跑出这些小的质因子。于是定义 "很小的质因子"为小于等于 $10^6$ 的质因子 * ，对于给定的 $a_i$ ，我们先用 $10^6$ 以内的所有质数去判断一下看这个数是不是含有 $10^6$ 以内的质因子，如果有，我们就直接将其除掉，这样操作后，很容易知道剩下的质因子不超过 $2$ 个。

注：并非所有的题目都是定义为 $10^6$ 以内的质因数为“很小的质因数”，根据题目而定，这里这么定义是因为 $m$ 只有 $600$ ,而 $10^6$ 以内的质数不超过 $80000$ 个，所以可以这么定义。

然后再使用 Pollard Rho 算法进行分解质因数的话就可以通过本题。

同时 Pollard Rho 用的时候一般都要搭配 Miller Rabin 素性测试算法，具体使用见下面代码的 
fac(x) 函数里面。

另外值得注意的是，因为本题的答案中 $2^w - 1$ 可能会达到 $2^{600}$ ，所以需要手写高精度。

下面给出代码:

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long
#define ull unsigned long long
const int MAXN = 1e3;
int m, Mod;
int A[MAXN], M[25] = {0,2,3,5,7,11,13,17,19,23,31,61}; //M 即 Miller Rabin 探测底数
int book[1 << 20], Prime[1 << 20], tot = 0;
int P[MAXN << 10], cnt = 0, len = 0;
char s[114514];
map <int, int> mp;//开一个 map 来统计每个质因子出现的次数

inline ll mul(ll x,ll y,ll p){ //快速乘，防止爆long long
	ll z = (long double)x / p * y;
	ll ans = (ull)x * y - (ull)z * p;
	return (ans + p) % p;
}

int f(int x, int c, int MOD) {return (mul(x, x, Mod) + c) % MOD;} //这个是 Pollard Rho 伪随机函数
int gcd(int A, int B) {return B == 0 ? A : gcd(B, A % B);}
int Abs(int x) {return x < 0 ? -x : x;}

int quickpower(int x, int y) { 
    int ans = 1, op = x;
    while(y) {
        if(y & 1) ans = mul(ans, op, Mod);
        op = mul(op, op, Mod), op %= Mod;
        y >>= 1;
    }
    return ans;
}

bool Miller_Rabin(int x) { //Miller Rabin 素性测试模板
    Mod = x;
    for(int i = 1 ; i <= 11 ; i ++) if(M[i] == x) return 1;
    if(x % 2 == 0 || x == 1) return 0;
    int p = x - 1, r = 0;
    while(p % 2 == 0) p >>= 1, r ++;
    for(int i = 1 ; i <= 10 ; i ++) {
        int B = quickpower(M[i], p);
        for(int j = 1 ; j <= r ; j ++) {
            int K = mul(B, B, Mod);
            if(K == 1 && B != Mod - 1 && B != 1) return 0;
            B = K;
        }
        if(B != 1ll) return 0;
    }
    return 1;
}

int Pollard_Rho(int x) { // Pollard Rho 模板
    if(x == 4) return 2;
    int c = rand() % (x - 1) + 1, a = 0, b = 0, d = 1;
    for(int lim = 1; ; lim <<= 1, b = a) { //采用了倍增优化
        int S = 1;
        for(int i = 1 ; i <= lim ; i ++) {
            a = f(a, c, x);
            S = mul(S, Abs(a - b), x);  //累乘
            if(i % 127 == 0) { // 隔 127 次判一下
                d = gcd(S, x); 
                if(d > 1) return d;
            }
        }
        int d = gcd(S, x);
        if(d > 1) return d;
    }
    return x;
}

void GetPrime() { //线性筛
    for(int i = 2 ; i <= 1e6 ; i ++) {
        if(!book[i]) Prime[++ tot] = i;
        for(int j = 1 ; j <= tot && Prime[j] * i <= 1e6; j ++) {
            book[Prime[j] * i] = 1;
            if(i % Prime[j] == 0) break;
        }
    }
    return ;
}

void fac(int x) {
    if(x == 1) return ;
    if(Miller_Rabin(x)) {
        if(mp[x] == 0) P[++cnt] = x; //保证每一个质因数只进队一次，防止重复统计
        mp[x] ++;
        return ;
    }
    int p = x;
    while(p >= x) p = Pollard_Rho(x);
    int flag = Miller_Rabin(p);
    while(x % p == 0) {
        if(mp[p] == 0 && flag) P[++ cnt] = p; //防止漏掉质因子
        if(flag) mp[p] ++;
        x /= p;
    }
    fac(x);
    if(!flag) fac(p);//如果 p 是质数就没必要进行下去了，已经被丢进质因数队列中了
    return ;
}

void Times() { //高精度乘法
    int len = strlen(s + 1);
    reverse(s + 1, s + 1 + len);
    int add = 0;
    for(int i = 1 ; i <= len ; i ++) {
        int x = s[i] - '0';
        x *= 2;
        x += add; add = 0;
        if(x >= 10) add = 1, x %= 10;
        s[i] = x + '0';
    }
    if(add != 0) s[++ len] = '1';
    reverse(s + 1, s + 1 + len);
    return ;
}

signed main() {
    cin >> m;
    for(int i = 1 ; i <= m ; i ++) cin >> A[i];
    sort(A + 1, A + 1 + m);
    GetPrime();
    for(int i = 1 ; i <= m ; i ++) { //这里是再处理较小的质因数
        for(int j = 1 ; j <= tot ; j ++)
        while(A[i] % Prime[j] == 0) {
            if(mp[Prime[j]] == 0)
            P[++ cnt] = Prime[j];
            A[i] /= Prime[j];
            mp[Prime[j]] ++;
        }
    }
    for(int i = 1 ; i <= m ; i ++) fac(A[i]); //分解质因数
    sort(P + 1, P + 1 + cnt);
    int Max = 0, total = 0;
    for(int i = 1 ; i <= cnt ; i ++) Max = max(Max, mp[P[i]]);
    for(int i = 1 ; i <= cnt ; i ++) if(mp[P[i]] == Max) total ++;
    cout << Max << endl;
    s[1] = '1';
    while(total -- ) Times();
    int len = strlen(s + 1);
    int x = s[len]; x --; s[len] = char(x); // 2 的任意正整数次方末尾只可能是 2,4,8,6 直接减没有问题
    for(int i = 1 ; i <= len ; i ++) cout << s[i];
    return 0; 
}
```

---

## 作者：kczno1 (赞：1)

orz神题。

假设n=p1^a1\*p2^a2..pk^ak

假设最大的ai有num个，

则ans1=ai

ans2=2^num-1

(注意到n有可能达到10^1000多，所以ans2要用高精度)

但n是以600个10^18的a给出的，不可能根号时间分解质因数。

但这两问是可以在不彻底分解质因数的情况下得到的。

首先，将a <=10^6的质因数分解掉(只枚举全部质数，大概有78000个)，

那么剩下来的a有几种情况。

1:大质数

用miller-robin检验

2:p1\*p2,p1和p2>10^6

(1)p1=p2 用根号特判

(2)p1≠p2 留着

先把最后一种情况去重了

再用前两种情况多出来的质数，以及最后一种情况两两求gcd得到的质数

去把最后一种情况的分解一下。

那么剩下来的每个数就是一个或两个ai=重复个数的pi。

于是就有办法统计ans了。


```cpp
#include<math.h>
#include<cstdio>
#include<algorithm>
using namespace std;

#define ll long long 
#define U 1000000
#define N 605
bool vis[U+5]; 
int p[U],num,t1[U];
ll p2[U];int num2,t2[U];
ll st[N];int top;int cnt[N],del[N];//重复次数 被筛次数 

ll gcd(ll x,ll y)
{
    while (y)
    {
        ll temp=x;
        x=y;y=temp%y;
    }
    return x;
}
ll a;
ll mod(const ll &x) { return x<a?x:x-a; }
ll cheng(ll x,ll y)
{
    ll ans=0;
    while (y)
    {
        if (y&1) ans=mod(ans+x);
        x=mod(x<<1);y>>=1;
    }
    return ans;
}
ll mi(ll x,ll y)
{
    ll ans=1;
    while (y)
    {
        if (y&1) ans=cheng(ans,x);
        x=cheng(x,x);y>>=1; 
    }
    return ans;
}
bool is_prime()
{
    ll d=a-1;int s=0;
    while (!(d&1)) { d>>=1;++s; }
    
    for (int i=1;i<=10;++i)
    {
        ll x=mi(p[i],d);
        if (x==1||x==a-1) continue;
        for (int j=1;j<s;++j)
        {
            x=cheng(x,x);
            if (x==a-1) break;
        }
        if (x!=a-1) return 0;
        d=a-1>>s;
    }
    return 1;
}

int ans1=1,ans2;//ans1=max(ai) ans2存的是num 
#define W 1000000000000000000LL
//压18位
void print()
{
    static ll a[N]; 
    int i; 
    printf("%d\n",ans1);
    top=1;a[1]=1;
    while (ans2--)
    {
        for (i=1;i<=top;++i) a[i]<<=1;
        for (i=1;i<=top;++i) 
        if (a[i]>=W) {a[i]-=W;a[i+1]+=1;}
        if (a[top+1]) ++top;
    }
      --a[1];
        printf("%lld",a[top]);
        for (i=top-1;i;--i) printf("%0*lld",18,a[i]);
} 

int main()
{ freopen("1.in","r",stdin);freopen("1.out","w",stdout);
    int i,j;
    for (i=2;i<=U;++i)
    {
        if (!vis[i]) p[++num]=i;
        for (j=1;i*p[j]<=U;++j)
        {
            vis[i*p[j]]=1;
            if (!(i%p[j])) break;
        }
    }
    int n,o;
    scanf("%d",&n);
    for (o=1;o<=n;++o) 
    { scanf("%lld",&a);
      for (i=1;i<=num;++i)
      while (!(a%p[i])) { a/=p[i];++t1[i]; }
      if (a==1) continue;
      if (is_prime()) { p2[++num2]=a;continue; } 
      ll g=sqrt(a);
      if (g*g==a) { p2[++num2]=g;p2[++num2]=g;continue; }
      st[++top]=a;
    }
    
    if (top)
    {
     sort(st+1,st+top+1);
     int temp=1;cnt[1]=1;
     for (i=2;i<=top;++i)
     {
         if (st[i]!=st[temp]) st[++temp]=st[i];
         ++cnt[temp];
     }
     top=temp;
     for (i=1;i<=top;++i)
     {
        a=st[i];
        for (j=i+1;j<=top;++j)
        {
            ll g=gcd(a,st[j]);
             if (g>1) 
             { ++del[i];++del[j];
               a/=g;st[j]/=g;
             for (int k=1;k<=cnt[i]+cnt[j];++k)p2[++num2]=g; }
        }
        st[i]=a;
     }
    }
    if (num2)
    {
     sort(p2+1,p2+num2+1);
     int temp=1;t2[1]=1;
     for (i=2;i<=num2;++i)
     {
       if (p2[i]!=p2[temp]) p2[++temp]=p2[i];
       ++t2[temp];
     }
     num2=temp;
     for (o=1;o<=top;++o)
     {
        a=st[o];
        for (i=1;i<=num2;++i)  
        if (!(a%p2[i])) {a/=p2[i];t2[i]+=cnt[o];++del[o];}
     }
     for (i=1;i<=top;++i)
     if (cnt[i]>ans1) { ans1=cnt[i];ans2=2-del[i]; } else
     if (cnt[i]==ans1) ans2+=2-del[i];
     for (i=1;i<=num2;++i)
     if (t2[i]>ans1) {ans1=t2[i];ans2=1;} else
     if (t2[i]==ans1) ++ans2;
    }
    
    for (i=1;i<=num;++i)
     if (t1[i]>ans1) {ans1=t1[i];ans2=1;} else
     if (t1[i]==ans1) ++ans2;
     
    print();
}
```

---

