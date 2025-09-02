# Beautiful Numbers

## 题目描述

Vitaly is a very weird man. He's got two favorite digits $ a $ and $ b $ . Vitaly calls a positive integer good, if the decimal representation of this integer only contains digits $ a $ and $ b $ . Vitaly calls a good number excellent, if the sum of its digits is a good number.

For example, let's say that Vitaly's favourite digits are $ 1 $ and $ 3 $ , then number $ 12 $ isn't good and numbers $ 13 $ or $ 311 $ are. Also, number $ 111 $ is excellent and number $ 11 $ isn't.

Now Vitaly is wondering, how many excellent numbers of length exactly $ n $ are there. As this number can be rather large, he asks you to count the remainder after dividing it by $ 1000000007 $ $ (10^{9}+7) $ .

A number's length is the number of digits in its decimal representation without leading zeroes.

## 样例 #1

### 输入

```
1 3 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 3 10
```

### 输出

```
165
```

# 题解

## 作者：timmark (赞：8)

# CF300C 题解

显然，一个数是否是“极好的数”，只与它的数字和有关，所以数字的顺序并不重要。

而且我们发现“极好的数”首先必须是“好数”，那么我们就可以枚举有几位是 $a$，剩下的位都是 $b$。

接下来考虑：有几种排列方式？

设这个“极好的数”有 $i$ 位为 $a$，剩下的 $n-i$ 位为 $b$。

从可重排列的角度来讲，所有排列方式总数 $=\dfrac{n!}{i!\times (n-i)!}$，也就是说整个数有 $n!$ 种排列方式，但是 $i$ 个 $a$ 和 $n-i$ 个 $b$ 在内部分别还有 $i!$ 和 $(n-i)!$ 种排列方式，所以需要将 $n!$ 除以 $i!\times (n-i)!$。

但是这个式子是不是很眼熟？这不就是组合数吗！因为对于 $n$ 位有 $i$ 位是 $a$ 的情况，我们也可以理解为在 $n$ 位中选择 $i$ 位，将其值设为 $a$，方案数即为 $C^i_n$。

所以我们只需要枚举 $i$，然后判断 $a\times i+b\times(n-i)$ 是否是“好数”，如果是则加上 $C^i_n$ 即可。

注意：这个数可以每一位都是 $a$ 或 $b$。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6,mod=1e9+7;
int n,a,b;
long long inv[1000005],fi[1000005],f[1000005],ans;
long long c(int m,int n){return ((m==n || !m) ? 1 : f[n]*fi[m]%mod*fi[n-m]%mod);}//组合数
bool judge(int n){//判断是否为好数
	while(n){
		if(n%10!=b && n%10!=a) return 0;
		n/=10;
	}return 1;
}int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> a >> b >> n ;
	inv[1]=1;
	for(int i=2;i<=N;i++) inv[i]=(-(mod/i)*inv[mod%i]%mod+mod)%mod;//线性预处理逆元
	fi[1]=f[1]=1;
	for(int i=2;i<=N;i++) fi[i]=fi[i-1]*inv[i]%mod,f[i]=f[i-1]*i%mod;//处理阶乘的逆元
	for(int i=0;i<=n;i++) if(judge(a*i+b*(n-i))) ans=(ans+c(i,n))%mod;
	cout << ans ;
	return 0;
}
```
看完点个赞吧！

---

## 作者：DennyQi (赞：7)

显然一个数字是否是`excellent`与其排列顺序无关。那我们不如默认它为aaaaabbbbbb这样有序的，然后乘上组合数得到答案。这样我们只需要暴力枚举$a$的个数，暴力判断就可以了。复杂度$O(n)$

这里求组合数，我用的是公式法。其中分母需要用费马小定理做一个乘法逆元（快速幂）。

```cpp
/*DennyQi 2019*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#define int long long
using namespace std;
const int N = 1000010;
const int P = 1e9+7;
inline int read(){
    int x(0),w(1); char c = getchar();
    while(c^'-' && (c<'0' || c>'9')) c = getchar();
    if(c=='-') w = -1, c = getchar();
    while(c>='0' && c<='9') x = (x<<3)+(x<<1)+c-'0', c = getchar(); 
    return x*w;
}
int n,a,b,ans;
int f[N];
inline bool judge(int x){
	int k;
	while(x > 0){
		k = x % 10;
		if(k!=a && k!=b) return 0;
		x /= 10;
	}
	return 1;
}
inline int inv(int k){
	int x = k, y = P-2, res = 1;
	while(y > 0){
		if(y & 1){
			res = (res * x) % P;
		}
		y /= 2;
		x = (x * x) % P;
	}
	return res;
}
inline int C(int n, int m){
	int x=1,y=1;
	x = f[n];
	y = (f[m] * f[n-m]) % P;
	y = inv(y);
	return x * y;
}
signed main(){
	freopen("file.in","r",stdin);
	a = read(), b = read(), n = read();
	f[0] = f[1] = 1;
	for(int i = 2; i <= n; ++i) f[i] = (f[i-1] * i) % P;
	for(int i = 0; i <= n; ++i){
		if(judge(a*i+b*(n-i))){
			ans = (ans + C(n,i)) % P;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：封禁用户 (赞：3)

有锅请私信我。

记 $f(a)=f(b)=1$。

$f(A)= \prod\limits _{i=1}^{|A|} f(A_i)$。

一个数 $A$ 为极好的数，当且仅当 $f(\sum\limits_{i=1}^{|A|} A_i)= 1$ 且 $f(A_i)= 1$。

其中 $|A|$ 为 $A$ 的位数，$A_i$ 为 $A$ 在第 $i$ 位上的值。

发现这个玩意和其数位上的数的排列顺序无关，举个例子：$f(\overline{ab} )= f(\overline{ba} )$。

于是考虑在 $n$ 位数下，不考虑排列顺序的情况有多少个。

设 $a$ 有 $i$ 个，那么 $b$ 有 $n-i$ 个，最后即判断 $f(a\times i+ b\times (n-i))$。

然后是考虑排列顺序的情况，这 $i$ 个 $a$ 可以在答案中任意分布，所以对答案的贡献就是 $C^{i}_{n}$。

# Code

```cpp
#include<bits/stdc++.h>
#define sd std::
#define int long long
#define il inline 
#define F(i,a,b) for(int i=(a);i<=(b);i++)
#define f(i,a,b) for(int i=(a);i>=(b);i--)
il int read(){int w=1,c=0;char ch=getchar();for(;ch>'9'||ch<'0';ch=getchar()) if(ch=='-') w=-1;for(;ch>='0'&&ch<='9';ch=getchar()) c=(c<<3)+(c<<1)+ch-48;return w*c;}
void printt(int x){if(x>9) printt(x/10);putchar(x%10+48);}
il void print(int x){if(x<0) putchar('-'),printt(-x);else printt(x);}
il void put(int x){print(x);putchar('\n');}
const int N=1e6+10,mod=1e9+7;
int a,b,n;
int g(int x)
{
	int tmp=x;
	while(tmp)
	{
		if(tmp%10!=a&&tmp%10!=b) return 0;
		tmp/=10;
	}
	return 1;
}
int jc[N],inv[N];
void prework(int n)
{
    inv[0]=jc[0]=inv[1]=1;
    F(i,1,n) jc[i]=jc[i-1]*i%mod;
    F(i,2,n) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    F(i,1,n) inv[i]=inv[i-1]*inv[i]%mod;
}
int C(int n,int m)
{
    if(n<m)return 0;
    return jc[n]*inv[m]%mod*inv[n-m]%mod;
}
il void solve()
{
	a=read(),b=read(),n=read();
	prework(n);
	int ans=0;
	F(i,0,n)//枚举a放了几个 
	{
		if(g(a*i+b*(n-i))) ans=(ans+C(n,i))%mod;
	}
	return put(ans);
}
signed main()
{
	int T=1;
//	T=read();
	while(T--) solve();
    return 0;
}
```

---

## 作者：封禁用户 (赞：3)

题意不说了。

[题目传送门](https://www.luogu.com.cn/problem/CF300C)
## **思路**
我们发现，极好的数**数位**不考虑顺序，只考虑是几个 $a$，几个 $b$。
也就是说，若 $\overline{aaabbbbb}$ 是极好的数，那么 $\overline{babababb}$ 也是极好的数。显然，我们只需要枚举有几个 $a$,几个 $b$，再对它们进行排列组合即可。

如何进行排列组合？

对 $n$ 个数进行全排列是 $n!$。但是不可能这么简单 ~~（一道蓝题哪可能这么简单）~~ 。我们知道重复的 $a$ 和重复的 $b$ 是**不用**进行全排列的。我们枚举有 $i$ 个 $a$,$(n - i)$ 个 $b$，则方案数需要除以 $i!  \times (n - i)!$。即：

$$ ans = \sum_{i = 0}^n \frac{n!}{i! \times (n - i)!}$$

发现了吗，这是组合数公式。

$$ C^i_n =  \frac{n!}{i! \times (n - i)!}$$

于是，我们就做出来了。~~（zhendema)~~

### **代码1**
```cpp
#include<iostream>
#include<cstring>
using namespace std;
#define int long long
const int N=2e2+10;
const int mod=1e9+7;
int check(int n,int a,int b){
    while(n!=0){
        int d=n%10;
        if(d!=a&&d!=b) return 0;
        n/=10;
    }
    return 1;
}
int ans;
int f(int n){
    //cout<<"4 ";
    int res=1;
    for(int i=1;i<=n;i++){
        res*=i;
        res%=mod;
    }
    return res;
}
int C(int n,int m){
    return f(m)/(f(n)*f(m-n))%mod;
}
signed main(){
    int a,b,n;
    cout<<C(2,6);
    cin>>a>>b>>n;
    for(int i=0;i<=n;i++){
        int num=a*i+b*i;
        if(check(num,a,b)){
            //cout<<"14 ";
            ans+=C(i,n)%mod;
        }
    }
    cout<<ans%mod;
}
```


你会发现：

![](https://cdn.luogu.com.cn/upload/image_hosting/6tur6hqx.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

一看，发现不对。涉及到除法阶乘，这不是**逆元+费马小定理+快速幂**吗。

[不会的看这里](https://blog.csdn.net/Krito_D_k/article/details/89060446?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522170685229416800188594752%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=170685229416800188594752&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-1-89060446-null-null.142^v99^pc_search_result_base1&utm_term=%E4%B9%98%E6%B3%95%E9%80%86%E5%85%83%E6%B1%82%E7%BB%84%E5%90%88%E6%95%B0&spm=1018.2226.3001.4187)

我们先预处理阶乘数组，再循环判断即可。

直接做出来了。

# 真·代码
```cpp
#include<iostream>
#include<cstring>
using namespace std;
#define int long long
const int N=1e6+10;
const int mod=1e9+7;
int t[N];

int ans;
//int f(int n){
//    //cout<<"4 ";
//    int res=1;
//    for(int i=1;i<=n;i++){
//        res*=i;
//        res%=mod;
//    }
//    return res;
//}
int a,b,n;

int ny(int a){
    int b=mod-2;//a模p的逆元为 x=a^(p-2)(mod p),
    int res=1;
    while(b>0){
        if(b&1) res=(res*a)%mod;
        a=(a*a)%mod;
        b>>=1;
    }
    return res%mod;
}
int C(int u,int v){//求组合数
    //if(u==v) return 1;
    //cout<<u<<' '<<v<<' ';
    //for(int i=1;i<=n;i++) cout<<t[i]<<" ";
    //cout<<endl<<endl;
    int U=t[u]%mod;
    //cout<<t[u]<<" ";
    int V=ny(t[v]*t[u-v]%mod)%mod;
    
   // cout<<U<<" "<<V<<" "<<U*V%mod<<endl;
    
    return U*V%mod;
}
int check(int n){
    while(n>0){
        int d=n%10;
        if(d!=a&&d!=b) return 0;
        n/=10;
    }
    return 1;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);//不加这三句会炸掉。
    //cout<<720*ny(48)%mod<<" ";
    cin>>a>>b>>n;
    t[0]=1;
    t[1]=1;
    for(int i=2;i<=n;i++){
        t[i]=t[i-1]*i%mod;
        //cout<<t[i]<<" ";
    }
    //cout<<inv(0)<<endl;
    //cout<<C(3,1);
    for(int i=0;i<=n;i++){
        int num=a*i+b*(n-i);
        if(check(num)){
           // cout<<"14 "<<num<<" "<<i<<" "<<endl;
            ans+=C(n,i)%mod;
            ans%=mod;
        }
    }
    cout<<ans%mod;
}
```
第一篇题解，求过。

---

## 作者：QZJ666 (赞：3)

显然,当一个整数 $\overline{abb}$为极好的数时，$ \overline{bab},\overline{bba}$ 也为极好的数，因为判断一个数是否为极好的数仅与它的位数和有关。

所以直接枚举 $a$ 的个数，设 $a$ 有 $i$ 个，则 $b$ 有 $n-i$ 个。判断这些数组成的数位数和能否满足条件，然后用排列组合求可以组成多少个数，就是在 $n$ 个数中选择 $i$ 个，也就是 $C(n,i)$，对每一个满足条件的数答案求和即可。

代码如下:
```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
ll n,m,ans,k;
const ll p=1e9+7;
ll pm(ll a,ll n,ll p){
	ll ans=1;
	a%=p;
	while(n){
		if(n%2){
			ans=ans*a%p;
		}
		a=a*a%p;
		n/=2;
	}
	return ans;
} 
ll fac[1000005];
void f(){
	fac[0]=1;
	for(int i=1;i<=1000000;i++){
		fac[i]=fac[i-1]*i%p;
	}
}
ll inv(ll x,ll p){
	return pm(x,p-2,p);
}
ll C(int n,int m,int p){
	if(m>n){
		return 0;
	}
	return (fac[n]*inv(fac[n-m]*fac[m],p))%p;
}
int Lucas(int n,int m,int p){
	if(n<m||n<0||m<0)
	return 0;
	if(m==0){
		return 1;
	}
	if(n<p){
		return C(n,m,p);
	}
	else{
		return Lucas(n/p,m/p,p)*Lucas(n%p,m%p,p);
	}
}
bool can(ll sum){
	while(sum){
		if(sum%10!=n&&sum%10!=m)return 0;
		sum=sum/10;
	}
	return 1;
}
int main(){
	scanf("%lld%lld%lld",&n,&m,&k);
	f();
	for(int i=0;i<=k;i++)
		if(can(n*i+m*(k-i)))ans+=Lucas(k,i,p),ans%=p;
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：Harrylzh (赞：2)

考虑直接枚举每一个好数，但是这样时间会炸。我们发现只要 $a$ 的个数相同的数（$b$ 的个数也肯定相同）各位之和都相同，如果各位之和是好数，那这些数都是极好的数。只需要枚举 $a$ 的个数 $i$，如果这样得到的和是好数，那把这 $C_{n}^{i}$ 个数都加在答案中。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long fac[1000000+5];
long long a,b,n;
const long long P=1e9+7;
bool judge(long long sum)//判断此数是否为好数
{
	while(sum)
   {
		long long now=sum%10;
		sum/=10;
		if(now!=a&&now!=b)
      {
			return 0;
		}
	}
	return 1;
}
long long power_mod(long long a,long long n,long long m)
{
	if(n==0) return 1;
	long long x=power_mod(a,n/2,m);
	long long ans=(long long)x*x%m;
	if(n%2==1) ans=ans*a%m;
	return ans;
}
long long gc(long long a,long long b,long long p)
{
    if(a<b) return 0;
    long long down=1,up=1;
    for(long long i=a,j=1;j<=b;j++,i--)
	 {
        up=(long long)up*i%p;
        down=(long long)down*j%p;
    }
    return (long long)up*power_mod(down,p - 2,p)%p;
}
long long lucus(long long n,long long m,long long p)
{
	if(n<p&&m<p)
   {
		return gc(n,m,p);
	}
	return lucus(n/p,m/p,p)*lucus(n%p,m%p,p)%p;
}
long long ans=0;
long long s=0;
int main()
{
	cin>>a>>b>>n;
	ans=a*n; 
	for(long long i=0;i<=n;i++)
	{
		if(judge(ans)) s=(s+lucus(n,i,P))%P;
		ans+=b-a;
	}
	cout<<s<<endl;
	return 0;
}
```

---

## 作者：hjyowl (赞：1)

### 思路

考虑枚举这个好数的和。

首先有一个上下界，即 $\max(a,b) \times n$ 和 $\min(a,b) \times n$。

然后对于这个范围内的 $i$，检验是不是好数，不是，那就退出下一个。

接下来就成了一个方程，设 $x$ 为 $a$ 的出现次数，$y$ 为 $b$ 的出现次数，方程如下：

$$x+y=n$$

$$a \times x + b \times y = i$$

对上面的方程式乘上一个 $a$，然后消元得到 $y$ 的值，然后，答案加上 $C_n^y$，也就是 $y$ 个 $b$ 可以随意排放，剩下的位置全部是 $a$。

然后就做完了。

时间复杂度：$\Theta(n)$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long N = 10000010;
long long mod = 1e9 + 7;
long long qmi(long long a,long long k){
	long long res = 1;
	while (k){
		if (k & 1){
			res = (long long)(res * a) % mod; 
		}
		a = (long long)(a * a) % mod;
		k >>= 1;
	}
	return res;
}
long long fact[N],infact[N];
long long C(long long a,long long b){
	if (b > a){
		return C(b,a);
	}
	return (fact[a] * qmi(fact[a - b],mod - 2) % mod * qmi(fact[b],mod - 2) % mod) % mod;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
	fact[0] = 1;
	for (long long i = 1; i <= N - 10; i ++ ){
		fact[i] = fact[i - 1] * i % mod;
	}
	long long a,b,n;
	cin >> a >> b >> n;
	//n*max(a,b)
	long long c = min(a,b),cc = max(a,b);
	a = c,b = cc;
	long long t = n * max(a,b);
	long long res = 0;
	for (long long i = n; i <= t; i ++ ){
		long long c = i;
		bool stt = 0;
		while (c){
			if (c % 10 != a && c % 10 != b){
				stt = 1;
			}
			c /= 10;
		}
		if (stt){
			continue;
		}
		//x+y=3
		//x+3y=5
		long long tt = i - a * n;
		long long ress = -1;
		if (tt >= 0){
			if (tt % (b - a) == 0){
				ress = tt / (b - a);
			}
		}
		if (ress > -1){
			res += C(n,ress);
			res %= mod;
		}
	}
	cout << res;
	return 0;
}

```

---

## 作者：rsy_ (赞：1)

发现如果 $a,b$ 的个数确定，就可以算出有多少种数，所以直接暴力枚举 $a$ 个数就可以了，算出数位和 $s$，直接暴力枚举，输出 $\sum \frac{n!}{(n-i)!i!}$ 就可以了。

```
#include <bits/stdc++.h>
#define lb(x) (x&-x)
#define L(i,j,k) for(int i=(j);i<=(k);++i)
#define R(i,j,k) for(int i=(j);i>=(k);--i)
#define int long long

using namespace std;
using i64 = long long;

typedef pair<int, int> pii;
typedef long long ll;
typedef unsigned long long ull;
void chmin(int &x, int c) {
	x = min(x, c);
}
void chmax(int &x, int c) {
	x = max(x, c);
}

namespace fast_IO {
#define IOSIZE 100000
	int precision = 3, POW[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
	char ibuf[IOSIZE], obuf[IOSIZE], *p1 = ibuf, *p2 = ibuf, *p3 = obuf;
#ifdef ONLINE_JUDGE
	#define getchar() ((p1==p2)and(p2=(p1=ibuf)+fread(ibuf,1,IOSIZE,stdin),p1==p2)?(EOF):(*p1++))
	#define putchar(x) ((p3==obuf+IOSIZE)&&(fwrite(obuf,p3-obuf,1,stdout),p3=obuf),*p3++=x)
	#define isdigit(ch) (ch>47&&ch<58)
	#define isspace(ch) (ch<33)
#endif
	template<typename T>inline T read() {
		T s = 0;
		int w = 1;
		char ch;
		while (ch = getchar(), !isdigit(ch) && (ch != EOF))if (ch == 45)w = -1;
		if (ch == EOF)return 0;
		while (isdigit(ch))s = s * 10 + ch - 48, ch = getchar();
		return s * w;
	} template<typename T>inline bool read(T&s) {
		s = 0;
		int w = 1;
		char ch;
		while (ch = getchar(), !isdigit(ch) && (ch != EOF))if (ch == 45)w = -1;
		if (ch == EOF)return 0;
		while (isdigit(ch))s = s * 10 + ch - 48, ch = getchar();
		return s *= w, 1;
	} inline bool read(char&s) {
		while (s = getchar(), isspace(s));
		return 1;
	} inline bool read(char*s) {
		char ch;
		while (ch = getchar(), isspace(ch));
		if (ch == EOF)return 0;
		while (!isspace(ch))*s++ = ch, ch = getchar();
		*s = '\000';
		return 1;
	} template<typename T>inline void print(T x) {
		if (x < 0)putchar(45), x = -x;
		if (x > 9)print(x / 10);
		putchar(x % 10 + 48);
	} inline void print(char x) {
		putchar(x);
	} inline void print(char*x) {
		while (*x)putchar(*x++);
	} inline void print(const char*x) {
		for (int i = 0; x[i]; i++)putchar(x[i]);
	} inline bool read(std::string&s) {
		s = "";
		char ch;
		while (ch = getchar(), isspace(ch));
		if (ch == EOF)return 0;
		while (!isspace(ch))s += ch, ch = getchar();
		return 1;
	} inline void print(std::string x) {
		for (int i = 0, n = x.size(); i < n; i++)putchar(x[i]);
	} inline bool read(bool&b) {
		char ch;
		while (ch = getchar(), isspace(ch));
		b = ch ^ 48;
		return 1;
	} inline void print(bool b) {
		putchar(b + 48);
	} inline bool read(double&x) {
		int a = 0, b = 0;
		char ch = getchar();
		bool f = 0;
		while (ch < 48 || ch > 57) {
			if (ch == 45)f = 1;
			ch = getchar();
		}
		while (47 < ch && ch < 58) {
			a = (a << 1) + (a << 3) + (ch ^ 48);
			ch = getchar();
		}
		if (ch != 46) {
			x = f ? -a : a;
			return 1;
		}
		ch = getchar();
		while (47 < ch && ch < 58) {
			b = (b << 1) + (b << 3) + (ch ^ 48), ch = getchar();
		}
		x = b;
		while (x > 1)x /= 10;
		x = f ? -a - x : a + x;
		return 1;
	} inline void print(double x) {
		if (x < 0) {
			putchar(45), x = -x;
		}
		x = round((long double)x * POW[precision]) / POW[precision], print((long long)x), putchar(46), x -= (long long)(x);
		for (int i = 1; i <= precision; i++)x *= 10, putchar(x + 48), x -= (int)x;
	} template<typename T, typename...T1>inline int read(T& a, T1&...other) {
		return read(a) + read(other...);
	} template<typename T, typename...T1>inline void print(T a, T1...other) {
		print(a), print(other...);
	} struct Fast_IO {
		~Fast_IO() {
			fwrite(obuf, p3 - obuf, 1, stdout);
		}
	} io;
	template<typename T>Fast_IO& operator>>(Fast_IO&io, T&b) {
		return read(b), io;
	} template<typename T>Fast_IO& operator<<(Fast_IO&io, T b) {
		return print(b), io;
	}
#define cout io
#define cin io
#define endl '\n'
} using namespace fast_IO;
const int maxn = 1e6 + 10, mod = 1e9+7;
int a,b,n,res,fac[maxn],infac[maxn];
int qmi(int a,int b){
	int res=1;
	while(b){
		if(b&1)res=1ll*res*a%mod;
		a=1ll*a*a%mod,b>>=1;
	}
	return res;
}

void solve() {
	cin>>a>>b>>n;
	for(int i=0;i<=n;i++){
		int j=n-i,F=0;
		int s=i*a+j*b;
		//有i个a，j个b，数位和是s
//		cout<<i<<' '<<s<<'\n';
		while(s){
			if(s%10!=a&&s%10!=b){
				F=1;break;
			}
			s/=10;
		} 
		if(F==1)continue;
//		cout<<i<<'\n';
		res+=fac[n]*infac[n-i]%mod*infac[i]%mod;
		res%=mod;
	}
	cout<<res<<'\n';
}

signed main() {
	fac[0]=infac[0]=1;
	for(int i=1;i<maxn;i++)
		fac[i]=1ll*fac[i-1]*i%mod,infac[i]=1ll*infac[i-1]*qmi(i,mod-2)%mod;
	int T = 1;
	while (T--)solve();
	return 0;
}
```

---

## 作者：OI_AKed_me (赞：1)

由题可得，一个数是否是 excellent，与其各数位顺序无关，则可枚举 $\texttt{a}$ 的个数然后 $O(\lg\ n)$ 暴力验证，最后通过组合数求解。组合数可以通过预处理阶乘、逆元从而实现 $O(1)$ 求解，不过我用的是我很久之前写的模版，并没有预处理逆元，导致每次查询需要 $O(\log\ n)$，时间复杂度略有退化，但不影响结果。

## 代码 ##
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll P(1000000007);
class Cnum{//组合数模版 
	ll a[1000005];
	public:
		ll pow(ll y,ll z,ll mod){
		    y%=mod;
			ll ans=1;
		    for(ll i=z;i;i>>=1,y=y*y%mod) if(i&1) ans=ans*y%mod;
		    return ans;
		}
		ll C(ll n,ll m,ll mod){
		    if(m>n) return 0;
		    return ((a[n]*pow(a[m],mod-2,mod))%mod*pow(a[n-m],mod-2,mod)%mod);//逆元可以预处理，不会的请自行 BDFS 
		}
		void build(const ll mod,const ll num){//预处理阶乘，这里最好也预处理一下逆元，这里不再详细说明 
			a[0]=1;
			for(int i=1;i<=num;i++) a[i]=(a[i-1]*i)%mod;
		}
}C;
ll n,a,b,ans=0;
bool check(ll x){ 
	while(x){
		ll l=x%10;
		if(l!=a&&l!=b) return 0;
		x/=10;
	}
	return 1;
}
int main(){
	cin>>a>>b>>n;
	C.build(P,n);
	for(ll i=0;i<=n;i++){//注意从 0 开始 
		if(check(a*i+b*(n-i))){
			ans=(ans+C.C(n,i,P))%P;
		}
	}
	cout<<ans<<endl;
	return 0;
}

```


---

## 作者：XL4453 (赞：1)

### 解题思路：

可以发现，一个极好的数就是一堆给定的两种数拼成然后各位上和还是一个由那两种数拼成的数。

然后就有，将一个极好的数上的各个位置的数换一些位置，这个数一定还是极好的数，也就是一个数是否是极好的数和且仅和这个数的各个位置上出现了几个 $a$ 和几个 $b$。

又由于极好的的数的各位上的数不是给定的 $a$ 就是给定的 $b$，题目中又给出了数的位数，只要知道 $a$ 有多少个就能确定 $b$ 的个数。若设 $a$ 的数量为 $i$，总共有 $n$ 位，那么就判断一下 $ai+b(n-i)$ 是否是一个好数。如果是，那么这个 $a$ 和 $b$ 的组合无论如何排列都是可行的极好的数，一共有方案数：$\dbinom{n}{i}$ 种。

---
实现的时候，可以预处理出阶乘和逆元，然后 $O(1)$ 调用。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
const long long MOD=1e9+7;
long long n,a,b,f[1000006],inv[1000006],ans;
long long pow(long long a,long long b){
	long long ans=1;
	while(b){
		if(b&1)ans=(ans*a)%MOD;
		a=(a*a)%MOD;
		b=b>>1;
	}
	return ans;
}
bool check(int num){
	while(num){
		if(num%10!=a&&num%10!=b)return 0;
		num/=10;
	}
	return 1;
}
long long C(long long n,long long m){
	return f[n]*inv[m]%MOD*inv[n-m]%MOD;
}
int main(){
	f[0]=1;
	for(int i=1;i<=1000000;i++)
	f[i]=(f[i-1]*i)%MOD;
	inv[1000000]=pow(f[1000000],MOD-2);
	for(int i=999999;i>=0;i--)
	inv[i]=(inv[i+1]*(i+1))%MOD;
	scanf("%I64d%I64d%I64d",&a,&b,&n);
	for(int i=0;i<=n;i++){
		if(check(i*a+(n-i)*b))
		ans=(ans+C(n,i))%MOD;
	}
	printf("%I64d",ans);
	return 0;
}
```


---

## 作者：peterwuyihong (赞：1)

数数不好，来做一些数学题。

题意：给定 $1\le a,b\le9$，定义一个牛逼的数为，所有数位上为 $a,b$。定义一个超级牛逼的数为，它数位和为牛逼的数。求有多少长度为 $n$ 的超级牛逼的数。

枚举出现了几个 $a$，算出几个 $b$，先判断一波和是不是牛逼的数，如果是，那么贡献就加上这么多个 $a$ 和 $b$ 能产生的所有组合，一共 $\dbinom{a+b}a$ 个，这里直接预处理组合数就行了。

```cpp
#define maxn 1000010
const int p=1e9+7;
template<class _Tp,class _tp>void add(_Tp&x,const _tp& y){((x+=y)>=p)&&(x-=p);}template<class _Tp,class _tp>_Tp Add(_Tp x,const _tp y){add(x,y);return x;}
template<class _Tp,class _tp>void sub(_Tp&x,const _tp&y){((x-=y)<0)&&(x+=p);}template<class _Tp,class _tp>_Tp Sub(_Tp x,const _tp y){sub(x,y);return x;}
template<class _Tp,class _tp>void mul(_Tp&x,const _tp&y){x=1ll*x*y%p;}template<class _Tp,class _tp>_Tp Mul(const _Tp x,const _tp y){return 1ll*x*y%p;}
template<class _Tp,class _tp>_Tp ksm(_Tp a,_tp b){_Tp ans(1);for(;b;b>>=1,mul(a,a))if(b&1)mul(ans,a);return ans;} 
template<class _Tp>_Tp div2(_Tp a){if(a&1)a+=p;return a>>1;}
int inv[maxn],jc[maxn],jcinv[maxn];
void init(int n){
	for(int i=0;i<2;i++)inv[i]=jc[i]=jcinv[i]=1;
	for(int i=2;i<=n;i++)inv[i]=Mul(p-p/i,inv[p%i]),jc[i]=Mul(jc[i-1],i),jcinv[i]=Mul(jcinv[i-1],inv[i]);
}
int _C(int n,int m){if(n<m)return 0;return Mul(jc[n],Mul(jcinv[m],jcinv[n-m]));}
template<class _Tp,class _tp>_Tp C(_Tp n,_tp m){if(!m)return 1;return Mul(_C(n%p,m%p),C(n/p,m/p));}
int a,b,n;
int ans;
bool G(int x){
	while(x){
		if(x%10!=a&&x%10!=b)return 0;
		x/=10;
	}return 1;
}
signed main(){
	cin>>a>>b>>n;
	init(n);
	rep(i,0,n)if(G(a*i+b*(n-i)))
	add(ans,_C(n,i));
	cout<<ans;
}
现在是 15:05，我看我什么时候写完。
现在是 15:10，我写完了。
```

---

## 作者：shao0320 (赞：1)

# CF300C Beautiful Numbers

组合数入门题。

先考虑暴力怎么做，考虑 $dp$ 。设 $F(i,j)$ 表示考虑到第 $i$ 位，目前选的数字总和为 $j$ 的方案数，那么每次转移枚举 $j$ 和当前位放的数字即可。

但是注意到这个 $j$ 的范围不大 (int都可以存下)，而且最后一定是 $xa+(n-x)b$ 的形式，因此可以直接枚举最后的 $x$，这样我们就保证了它是个极好的数，那现在就相当于 $n$ 个位置挑出来 $x$ 个放 $a$，组合数即可。

---

## 作者：wflhx2011 (赞：0)

# Solution

不难发现，好数与极好的数都只和构成的数有关系有关，与位数无关。

题目已经给出构成的两个数，所以这一位上如果不填 $a$ 就只能填 $b$。

咦？这不就是一道组合题目吗，答案就是 $ \begin{aligned}\sum_{i=0}^n
C_n^i\end{aligned}$。

具体求法就是 $ \begin{aligned} \sum_{i=0}^n \frac{n!}{i!\times (n-i)!}\end{aligned}$。

这里有几点注意：

1. 这样构造不一定是极好的数，所以需要检验再计入答案。

1. 组合数涉及到除法，而本题又有一个模数，所以就需要用逆元。我用的是线性递推，预处理为 $O(n)$，单次处理为 $O(1)$。不会的可以看[这里](https://www.luogu.com.cn/problem/P3811)。

之后，代码也就简洁了：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
long long inv[1000005],f[1000005],jiecheng[1000005],ans,n,a,b;
long long C(int m,int n)
{
	return ((m==n||!m)?1:jiecheng[n]*f[m]%mod*f[n-m]%mod);
}
bool judge(int n)
{
	while(n)
	{
		if(n%10!=b&&n%10!=a) 
			return 0;
		n/=10;
	}
	return 1;
}
int main()
{
	cin>>a>>b>>n;
	inv[1]=1;
	for(int i=2;i<=1e6;i++)
		inv[i]=((mod-mod/i)*inv[mod%i]%mod+mod)%mod; 
	f[1]=jiecheng[1]=1;
	for(int i=2;i<=1e6;i++) 
		f[i]=f[i-1]*inv[i]%mod,jiecheng[i]=jiecheng[i-1]*i%mod;
	for(int i=0;i<=n;i++) 
		if(judge(a*i+b*(n-i))) 
			ans=(ans+C(i,n))%mod;
	cout<<ans;
	return 0;
}
```

---

## 作者：Pentiment (赞：0)

枚举有多少个数位是 $a$，假设有 $x$ 个，那么数位之和为 $xa+(n-x)b$，判断它是否是好数就行。如果数位之和是好数，那么一共有 $\text{C}_n^x$ 个数中有 $x$ 个数位为 $a$，加到答案里即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000005, p = 1000000007;
int a, b, n, m, f[N], ans;
bool check(int x) {
	while (x) {
		if (x % 10 != a && x % 10 != b) return 0;
		x /= 10;
	}
	return 1;
}
int qpow(int a, int b) {
	int c = 1;
	while (b) {
		if (b & 1) c = (ll)c * a % p;
		a = (ll)a * a % p, b >>= 1;
	}
	return c;
}
#define inv(x) qpow(x, p - 2)
int C(int n, int m) { return (ll)f[n] * inv(f[n - m]) % p * inv(f[m]) % p; }
int main() {
	scanf("%d%d%d", &a, &b, &n);
	f[0] = 1;
	for (int i = 1; i <= n; i++) f[i] = (ll)f[i - 1] * i % p;
	for (int i = 0; i <= n; i++) {
		if (check(i * a + (n - i) * b)) ans = (ans + C(n, i)) % p;
	}
	printf("%d\n", ans);
}
```

---

## 作者：InversionShadow (赞：0)

注意到“极好的数”一定是“好数”，并且数据范围 $n\le10^6$。

那么我们就可以想到枚举 $a$ 的数量 $i$，那么 $b$ 的数量就是 $n-i$，并且可以 $\mathcal{O(}1\mathcal{)}$ 判断 $a\times i+b\times (n-i)$ 是否是好数，如果是那么表示 $i$ 个 $a$ 和 $n-i$ 个 $b$ 组成的数是“极好的数。

那怎么统计答案呢？感性理解一下：如果 $i$ 个 $a$ 和 $n-i$ 个 $b$ 可以，就是在 $n$ 个数里选了 $i$ 个数当作 $a$，方案是就是 $C_{n}^i$，计和即可。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int mod = 1e9 + 7;
const int N = 1e6 + 100;

int a, b, n, sum, fac[N];

bool check(int x, int y) {
  int p = a * x + b * y;
  while (p) {
    if (p % 10 != a && p % 10 != b) {
      return 0;
    }
    p /= 10;
  }
  return 1;
} 

int qpow(int a, int b) {
  if (!b) {
    return 1;
  }
  int tmp = qpow(a, b / 2);
  if (b & 1) {
    return tmp % mod * tmp % mod * a % mod;
  }
  return tmp % mod * tmp % mod;
}

void init() {
  fac[0] = 1;
  for (int i = 1; i <= N - 100; i++) {
    fac[i] = fac[i - 1] * i % mod;
  }
}

int C(int a, int b) {
  return fac[a] * qpow(fac[b], mod - 2) % mod * qpow(fac[a - b], mod - 2) % mod;
}

signed main() {
  init();
  cin >> a >> b >> n;
  for (int i = 0; i <= n; i++) {
    if (!check(i, n - i)) {
      continue;
    }
    (sum += C(n, i) % mod) %= mod;
  }
  cout << sum % mod << '\n';
  return 0;
}
```

---

## 作者：Link_Cut_Y (赞：0)

很显然，将“好数”的各位加起来，最多会达到 $9 \times 10 ^ 6$ 的数量级。暴力判断这个数是否是“好的”是可行的。

枚举原数中有多少位是 $a$，剩下的都填 $b$。所有数位的和容易计算。暴力判断即可。

具体地，答案即为：

$$\sum_{i = 0}^{n} \dbinom{n}{i} [a\times i + b \times (n - i) \text{\ is good}]$$

时间复杂度 $O(n \lg n)$。

```cpp
int fac[N], inv[N], ans, n, a, b;
int C(int n, int m) { return fac[n] * inv[m] % mod * inv[n - m] % mod; }
bool check(int n) {
	while (n) { if (n % 10 != a and n % 10 != b) return 0; n /= 10; } return 1;
}
signed main() {
	read(a, b, n); fac[0] = inv[0] = 1;
	rep(i, 1, n) fac[i] = fac[i - 1] * i % mod;
	inv[n] = qpow(fac[n]); dep(i, n - 1, 1) inv[i] = inv[i + 1] * (i + 1) % mod;
	rep(i, 0, n) if (check(i * a + (n - i) * b)) (ans += C(n, i)) %= mod; write('\n', ans);
}
```

---

