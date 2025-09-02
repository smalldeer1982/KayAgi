# White, Black and White Again

## 题目描述

Polycarpus is sure that his life fits the description: "first there is a white stripe, then a black one, then a white one again". So, Polycarpus is sure that this rule is going to fulfill during the next $ n $ days. Polycarpus knows that he is in for $ w $ good events and $ b $ not-so-good events. At least one event is going to take place during each day. As each day is unequivocally characterizes as a part of a white or a black stripe, then each day is going to have events of the same type only (ether good or not-so-good).

What is the number of distinct ways this scenario can develop over the next $ n $ days if Polycarpus is in for a white stripe (a stripe that has good events only, the stripe's length is at least 1 day), the a black stripe (a stripe that has not-so-good events only, the stripe's length is at least 1 day) and a white stripe again (a stripe that has good events only, the stripe's length is at least 1 day). Each of $ n $ days will belong to one of the three stripes only.

Note that even the events of the same type are distinct from each other. Even if some events occur on the same day, they go in some order (there are no simultaneous events).

Write a code that prints the number of possible configurations to sort the events into days. See the samples for clarifications on which scenarios should be considered distinct. Print the answer modulo $ 1000000009 $ $ (10^{9}+9) $ .

## 说明/提示

We'll represent the good events by numbers starting from 1 and the not-so-good events — by letters starting from 'a'. Vertical lines separate days.

In the first sample the possible ways are: "1|a|2" and "2|a|1". In the second sample the possible ways are: "1|a|b|2", "2|a|b|1", "1|b|a|2" and "2|b|a|1". In the third sample the possible ways are: "1|ab|2", "2|ab|1", "1|ba|2" and "2|ba|1".

## 样例 #1

### 输入

```
3 2 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 2 2
```

### 输出

```
4
```

## 样例 #3

### 输入

```
3 2 2
```

### 输出

```
4
```

# 题解

## 作者：傅思维666 (赞：3)


## 题解：

~~2019.10.16模拟赛爆氮T1~~

~~题面翻译来发第一篇题解...~~

首先拿到这道题手推了几组数据。然后灵光一闪：有没有可能是这些事件的发生顺序和到底发生在哪天并没有关系？就是说：我只需要把$w$件好事和$b$件坏事排成一排，保证$b$件坏事全在中间，两头都有好事即可。

但是这样绝对是不行的，因为我们把这些事件拆分成很多天（当然是满足题意的拆分方法），就是很多种方案。

但是这样的一个思路却为我们打开了一个突破口：在这样一个前面是一堆好事、中间夹了一堆坏事、最后又是一堆好事的序列中，我们只需要“往里添几个分隔板”，表示天数的差异，再进行统计即可。

隆重介绍：排列组合常用切题法：隔板法。

高中数学的排列组合会讲到，但是本蒟蒻并没有学.....简单介绍一下，排成一行的$n$件事，我们需要在其中的$n-1$个“缝隙”中，填入$m$个隔板，这样就把整个序列划分成了$m+1$个部分。

那么，我们有多少种合法的添入隔板的方法，就有多少种可能的天数划分方法。至于每天的事件发生顺序有所不同，我们只需要把天数划分方法乘上$w!\times b!$即可。（全排列公式）

于是，我们得到了一个组合数的公式：将$n$件事中填入$m$个隔板（分成了$m+1$个部分），方式有：(种)
$$
C_{n-1}^{m}=\frac{(n-1)!}{m!(n-m-1)!}
$$
于是这道题就变成了一道组合数取模的题。

不要忘了最后要乘两个阶乘。因为数据范围已经给出，所以我们只需要考虑预处理出阶乘数组即可。

当然，也要顺道处理出乘法逆元的数组（除法取模要用）。



思路比较容易得出，但是不太容易理顺及证明正确性。而且代码的实现（取模）细节比较多，%……*&

代码如下：

```cpp
#include<cstdio>
#define ll long long
#define mod 1000000009
using namespace std;
const int maxn=4001;
int fac[maxn],inv[maxn];
int n,w,b,ans;
void init_fact()
{
    fac[0]=1;
    for(int i=1;i<=maxn;i++)
        fac[i]=(ll)i*fac[i-1]%mod;
}
void init_inv()
{
    inv[0]=1;inv[1]=1;
    for(int i=2;i<=maxn;i++)
        inv[i]=mod-(ll)(mod/i)*inv[mod%i]%mod;
    for(int i=1;i<=maxn;i++)
        inv[i]=(ll)inv[i-1]*inv[i]%mod;
}
int calc(int n,int m)
{
    return (ll)fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int main()
{
    init_fact();
    init_inv();
    scanf("%d%d%d",&n,&w,&b);
    for(int i=1;i<=b;i++)
        if(n-i>=2 && n-i<=w)
            ans=((ll)ans+(ll)(n-i-1)*calc(b-1,i-1)%mod*calc(w-1,n-i-1)%mod)%mod;
    ans=(ll)((ll)ans*fac[w]%mod*fac[b]%mod)%mod;
    printf("%d",ans);
    return 0;
}
```



---

## 作者：littleseven (赞：3)

# CF 306C White, Black and White Again

**题目链接：**[洛谷 CF306C White, Black and White Again](https://www.luogu.org/problem/CF306C)	[CF306C White, Black and White Again](http://codeforces.com/problemset/problem/306/C)

**算法标签:**  `组合数学`

## 题解：

**组合数（隔板法）**

校内模拟赛的一到考试题，考场上并不知道隔板法（擦汗.jpg）

我们首先可能得出一个必须要求的东西：$m$件事在$n$天内做完有多少种方法。[$m$可能$\gt$n]

那么就需要**隔板法**。

>隔板法：
>
>我们考虑有$n$个小球，那么这$n$个小球之间就会有$n-1$个缝隙。我们在这$n-1$个缝隙中选出来$m$个位置放入隔板，这样就会把这$n$个小球分成$m$份，即$f(n, m) = C^{m-1}_{n-1}$。
>
>显然在这道题里适用，我们可以用$f(n,m)$直接表示$m$天内做$n$件事的方案数。

然后我们就可以预处理出整个$f[~]$数组，当然也需要提前处理出阶乘和每一个阶乘的逆元（费马小定理）。

*补充：为什么要预处理逆元而不是用的时候直接处理？？？*

*在下面的代码里可以发现我们处理$f[~]$数组的时候是$n^2$的，所以我们就要处理$4000 \times 4000$c次，但是如果预处理的话只需要4000次即可*

之后我们再考虑之后怎么做。我们发现一定是 **好事情-坏事情-好事情** 的顺序出现，可以看做是在好事情之间穿插进去坏事情，并且坏事情一定都是一起发生的。

 那么对于这个问题就变成了：

- 先求出$i$天发生$b$件坏事的方案数。
- 再求出$(n-i)$天发生$w$件好事的方案数。
- 在好事的所有方案中我们可以选择任意一个位置插入所有坏事，这样就一共有$(n-i-1)$种插入坏事的方法
- 最终答案就是$\sum f[n-i][w] * f[i][b] * (n-i-1)$

计算结果输出即可。

## AC代码

```cpp
#include <bits/stdc++.h>

#define setI(x) freopen(x".in", "r", stdin);

#define setO(x) freopen(x".out", "w", stdout);

#define setIO(x) setI(x) setO(x)

using namespace std;

typedef long long ll;

const ll mod = 1e9 + 9;

const int N = 4040;

int n, w, b;

ll fac[N], f[N][N], inv[N];   

ll qpow(ll x, ll p) {
	ll res = 1ll;
	while (p) {
		if (p & 1) {
			res = (res * x) % mod;
		}
		x = (x * x) % mod;
		p >>= 1;
	}
	return res;
}

ll INV(ll k) {
	return qpow(k, mod - 2);
}

ll calc(int x, int y) {
	return fac[x] * inv[y] % mod * inv[x - y] % mod;
}

void init() {
	fac[0] = 1ll;
	inv[0]=1ll;    
	for (int i = 1; i < N; i ++ ) {
		fac[i] = (fac[i - 1] * 1ll * i) % mod;
		inv[i] = INV(fac[i]);     
	}
}

int main() {
	// setIO("count")
	scanf("%d%d%d", &n, &w, &b);
	init();
	for (int i = 1; i <= n; i ++ ) {
		for (int j = i; j < N; j ++ ) {
			f[i][j] = (fac[j] * calc(j - 1, i - 1)) % mod;
		}
	}
	ll ans = 0;
	for (int i = 1; i < n - 1; i ++ ) {
		ans = (ans + f[n - i][w] * f[i][b] % mod * (1ll * n - 1ll * i - 1ll) % mod) % mod;
	}
	cout << ans << endl;
	return 0;
}
```



---

## 作者：JQ6561 (赞：1)

### 【CF306C】题解

这是一道不错的**组合数学**题

虽然数据范围给的是$O(n^2)$的，但我这里来发一篇$O(n)$的题解

首先发现，**坏天**一定是全部连在一起且位居中间的，因此可以想到枚举**坏天**的数量，即**坏事情**被分成的段数$x$，当我们知道了**坏天**的数量，**好天**的数量自然也就可以表示为$n-x$了。

因为每一个**好天和坏天**都不同

又因为**好事情和坏事情**都是**单独进行排列**的（不会掺和在一起）

因此，**好事情**的排列方法和**坏事情**的排列方法分别为$A\binom ww=w!$和$A\binom bb=b!$种

应用**插板法**进行相应数量的分段

**好天**单独排列的方案数为$w!C\binom {n-x-1}{w-1}$

**坏天**单独排列的方案数为$b!C\binom {x-1}{b-1}$

将两种天的情况结合起来，考虑到**好天**需要被分成两部分，一部分在**坏天**前，一部分在**坏天**后，因此答案还要乘上$n-x$拆分成有序自然数对$(a,n-x-a)$的方案数$n-x-1$

因此，对于每一个枚举的$x$，答案贡献为$w!C\binom {n-x-1}{w-1}*b!C\binom {x-1}{b-1}*(n-x-1)$

最终答案即为$\Sigma w!C\binom {n-x-1}{w-1}*b!C\binom {x-1}{b-1}*(n-x-1)$

需要注意枚举边界，组合数和阶乘可以$O(n)$预处理！

$code:$
~~~cpp
#include<bits/stdc++.h>
using namespace std;
long long mod=1000000009;
int a,b,c;
long long d[4009];
long long cny[4009];
long long ny[4009];
long long ksm(long long x,long long y){
	if(y==0){
		return 1;
	}
	if(y==1){
		return x;
	}
	if(y&1){
		return (ksm(x,y-1)*x)%mod;
	}else{
		long long p=ksm(x,y>>1);
		return (p*p)%mod;
	}
}
void qny(){
	cny[0]=1;
	for(int i=1;i<=4005;i++){
		cny[i]=(cny[i-1]*i)%mod;
	}
	ny[4005]=ksm(cny[4005],mod-2);
	for(int i=4004;i>=1;i--){
		ny[i]=(ny[i+1]*(i+1))%mod; 
	}
}
long long C(long long x,long long y){
    if(x==y){
		return 1;
	}
	if(y>x){
		return 0;
	}
	if(x==0){
		return 0;
	}
	if(y==0){
		return 1;
	}
	return ((cny[x]*ny[x-y])%mod*ny[y])%mod;
}
int main(){
	cin>>a>>c>>b;
	qny();
	long long ans=0;
	for(int i=1;i<=min(a-2,b);i++){
		long long an=(cny[b]*C(b-1,i-1))%mod;
		an=(((an*cny[c])%mod*C(c-1,a-i-1)%mod)*(a-i-1))%mod;
		ans=(ans+an)%mod;
	}
	cout<<ans;
	return 0;
}
~~~

不要直接抄袭此代码，直接抄袭可能会导致您获得棕名

---

## 作者：辰星凌 (赞：1)

# **【题解】White, Black and White Again [CF306C]**

[$\mathcal{My}\ \mathcal{Blog}$](https://www.cnblogs.com/Xing-Ling/p/12453851.html)

传送门：[$\text{White, Black and White Again}$](https://www.luogu.com.cn/problem/CF306C) [$\text{[CF306C]}$](http://codeforces.com/contest/306/problem/C)

## **【题目描述】**

有 $n$ 个盒子排成一行，$w$ 个互不相同的好球，$b$ 个互不相同的坏球，现要将球全部放入盒子中，并满足从左到右依次为：若干好球、若干坏球、若干好球。每个盒子只能放一种类型的球且盒子不能为空。

## **【分析】**

考虑最 $naive$ 的想法：依次枚举放好球的盒子数量 $i$ 。

将坏球视作一个整体，可以插在好球的中间，有 $i-1$ 种方案。

将 $w$ 个好球划分到 $i$ 个盒子中，相当于一个插板问题，有 $C_{w-1}^{i-1}$ 种方案，坏球同理，将 $b$ 个坏球划分到 $b-i$ 个盒子中，有 $C_{b-1}^{n-i-1}$ 种方案。

最后再乘上 $w!$ 以及 $b!$，则答案为 $w!b!\sum_{i=2}^{n-1}(i-1)C_{w-1}^{i-1}C_{b-1}^{n-i-1}$ 。

时间复杂度为 $O(n\log{n})$ 或者 $O(n)$，已经可以轻松跑过了，现在考虑能不能优化。

先推一波柿子:

$$ans=w!b!\sum_{i=2}^{n-1}(i-1)C_{w-1}^{i-1}C_{b-1}^{n-i-1}$$

由 $mC_{n}^{m}=nC_{n-1}^{m-1}$ 得：

$$ans=w!b!(w-1)\sum_{i=2}^{n-1}C_{w-2}^{i-2}C_{b-1}^{n-i-1}$$

改变 $i$ 的枚举方式得：

$$ans=w!b!(w-1)\sum_{i=0}^{n-3}C_{w-2}^{i}C_{b-1}^{n-3-i}$$

由范德蒙德卷积 $\sum_{i=0}^{k} C_{n}^{i} C_{m}^{k-i}=C_{n+m}^{k}$ 得：

$$ans=w!b!(w-1)C_{w+b-3}^{n-3}$$

现在查询变成 $O(1)$ 或者 $O(\log{n})$ 了。

那么这个式子又应该如何理解呢？

由于球的排列方式一定是 “好...好....坏...坏...好...好”，考虑直接将 $w+b$ 个球分配到 $n$ 个盒子中，即在 $w+b-1$ 个空隙中插入 $n-1$ 块板子。但由于好坏球之间必定会有 $2$ 块固定的板子（由好坏球个数决定，在一次询问中球数是已知的），所以相当于在 $w+b-3$ 个空隙中插入 $n-3$ 块板子，方案数为 $C_{w+b-3}^{n-3}$ 。由于坏球的位置依旧不确定，所以要乘上 $w-1$。最后再乘以 $w!b!$ 即为答案。

注意模数别看错了，是 $10^9+9$ 不是 $10^9+7$，$\text{CF}$ 总喜欢搞一些近似模数来坑你。

## **【Code】**

```cpp
#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=4003,P=1e9+9;
int n,w,b,jc[N<<1];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline int mi(Re x,Re k){
    Re s=1;
    while(k){
        if(k&1)s=(LL)s*x%P;
        x=(LL)x*x%P,k>>=1;
    }
    return s;
}
inline int inv(Re x){return x==0?1:mi(x,P-2);}
inline int C(Re m,Re n){return (LL)jc[n]*inv(jc[n-m])%P*inv(jc[m])%P;}
int main(){
//  freopen("123.txt","r",stdin);
    in(n),in(w),in(b),jc[0]=1;
    for(Re i=1;i<=w+b;++i)jc[i]=(LL)jc[i-1]*i%P;
//  Re ans=0;
//  for(Re i=max(n-b,2);i<=n-1&&i<=w;++i)
//      (ans+=(LL)C(i-1,w-1)*C(n-i-1,b-1)%P*(i-1)%P)%=P;
//  printf("%d\n",(LL)ans*jc[w]%P*jc[b]%P);
    printf("%d\n",(LL)C(n-3,w+b-3)*(w-1)%P*jc[w]%P*jc[b]%P);
}
```


---

## 作者：rsy_ (赞：0)

直接暴力枚举黑和白的分界点，答案就是 $C_{w+b-3}^{n-3}\sum[i,j\operatorname{\;is\;legal}
]\times i!j!$ 直接 $\mathcal O(n^2)$ 暴力算即可。

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
const int maxn = 3e5 + 10, mod = 1000000009;
int n,w,b,fac[maxn],infac[maxn];
int C(int a,int b){
	if(a<b)return 0;
	return 1ll*fac[a]*infac[a-b]%mod*1ll*infac[b]%mod;
}
int qmi(int a,int b){
	int res=1;
	while(b){
		if(b&1)res=1ll*res*a%mod;
		a=1ll*a*a%mod,b>>=1;
	}
	return res;
}
int res=0;

void solve() {
	cin>>n>>w>>b;
	for(int i=1;i<w+b-1;i++){
		for(int j=i+1;j<w+b;j++){
			int s1=i,s2=w+b-j;
			int I=s1+s2,J=w+b-s1-s2;
			if(I>w||J>b)continue;
//			cout<<s1<<' '<<w+b-s1-s2<<' '<<s2<<'\n';
			res+=1ll*fac[I]*fac[J]%mod;
			res%=mod;
		}
	}
//	cout<<res<<'\n';
	cout<<1ll*res*C(w+b-3,n-3)%mod<<'\n';
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

## 作者：WorldMachine (赞：0)

### $\mathcal O(n)-\mathcal O(n)$ 做法

考场上本来打的是这个做法，数组越界了，我的编译器居然不给我报 RE……qwq

假设有 $x$ 天发生坏事，剩下 $n-x$ 天发生好事。

先不考虑好事和坏事的位置关系。

好事自由排列和选择天数，根据隔板法，方案数为：
$$
w!\binom{n-x-1}{w-1}
$$
同理，坏事的方案数为：
$$
b!\binom{x-1}{b-1}
$$
然后中间坏事还可以插 $n-x-1$ 个空，因此答案为：
$$
w!b!(n-x-1)\binom{n-x-1}{w-1}\binom{x-1}{b-1}
$$
然后一定要注意循环边界！！！不然在 CF 上会给你显示 WA……

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 4005, p = 1000000009;
int n, w, b, f[N], inv[N], ans;
int qpow(int a, int b) {
	int c = 1;
	while (b) {
		if (b & 1) c = (ll)c * a % p;
		a = (ll)a * a % p, b >>= 1;
	}
	return c;
}
int C(int n, int m) {
	if (n < m) return 0;
	return (ll)f[n] * inv[n - m] % p * inv[m] % p;
}
void init() {
	f[0] = inv[0] = 1;
	for (int i = 1; i <= 4000; i++) f[i] = (ll)f[i - 1] * i % p;
	inv[4000] = qpow(f[4000], p - 2);
	for (int i = 3999; i >= 1; i--) inv[i] = (ll)inv[i + 1] * (i + 1) % p;
}
int main() {
	scanf("%d%d%d", &n, &w, &b);
	init();
	for (int i = 1; i <= min(n - 2, b); i++) {
		ans = (ans + (ll)f[b] * C(b - 1, i - 1) % p * f[w] % p * C(w - 1, n - i - 1) % p * (n - i - 1)) % p;
	}
	printf("%d\n", ans);
}
```

### $\mathcal O(n)-\mathcal O(1)$ 做法

首先让好事坏事各自随便排列，方案数为 $w!b!$。

随后分配天数。一共有 $w+b-1$ 个空位，但是好事和坏事之间一定会有 $2$ 个空位，所以就是在 $w+b-3$ 个空位里插入 $n-3$ 个隔板，方案数为 $\text{C}_{w+b-3}^{n-3}$。

但是坏事插在哪还没确定呢，还要再乘上 $w-1$。因此答案为：
$$
w!b!(w-1)\binom{w+b-3}{n-3}
$$
至于利用范德蒙德卷积的推导，已经有巨佬写了，这里就不写啦（逃

---

## 作者：xqh07 (赞：0)

一道优秀的**组合数学**题。数据范围允许 $O(n^2)$ ，但实际上可以 $O(n)$ 过。

首先，通读题意后可发现：**坏天连续存在于中间，好天分居两侧**。又因为坏的事件总数是固定的，我们不难想到**枚举坏天的天数**，并通过插板法分别求出坏事件和好事件的分配方式，最后通过加乘原理统计。

**插板法**：设有 $n$ 个小球，放入 $m$ 个不同的箱子里 （箱子不能为空），则可视为在小球两两之间的 $n-1$ 个空隙中插入 $m-1$ 个隔板，总方案数为 $\binom{n-1}{m-1} $。


具体地，设坏天的天数为 $l$，则应用插板法，坏事件的分配方案数为：$\binom{b-1}{l-1} \times b!$（坏事件内部有 $b!$ 种排序方式）。

此时好天的天数为 $n-l$，同样应用插板法，好事件的分配方案数为 $\binom{w-1}{n-l-1} \times w!$。

~~对于每一个 $l$，将两种事件的方案数乘起来求和，就得到了答案。~~

还没有结束！

前面说过，好天分居坏天的两侧。我们此时只是确定了好事件对应好天的总体分配方式，然而还没有满足**分段**这一要求。所以，还需在好事件分配方案数中乘上 $n-l-1$ (可作为分隔天的数量）。

不难证明，在坏天时长与好天分隔日期都确定的情况下，该算法满足不重不漏原则。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 1e9 + 9;
int n, m, w, b, f[12005], res, ans, liv;
int quickpow(int x, int y)
{
	int res = 1;
	while(y)
	{
		if(y & 1) res = res * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return res;
}
int C(int n, int m)
{
	if(n < m) return 0;
	else if(n == m || m == 0) return 1;
	return f[n] * quickpow(f[m], mod - 2) % mod * quickpow(f[n - m], mod - 2) % mod;
}
signed main()
{
	scanf("%lld%lld%lld", &n, &w, &b);
	f[0] = 1;
	for(int i = 1; i <= 12000; i++) f[i] = f[i - 1] * i % mod;  
	for(int l = 1; l <= n - 2; l++)
	{
		res = C(b - 1, l - 1) * f[b] % mod;
		liv = C(w - 1, n - l - 1) * (n - l - 1) % mod * f[w] % mod;
		ans = (ans + res * liv % mod) % mod;
	}
	printf("%lld\n", ans);
	return 0;
}

```


---

## 作者：Toothless03 (赞：0)

来~~水~~一篇 $O(n)$ 的题解，这是一道不戳的组合数学题

“坏天“一定是在中间的，所以我们可以先将“坏天”插到”好天“中。所以我们可以枚举“好天”的个数 $i$，对于 $w$ 个“好天”，可以使用《插板法》计算出对于每一种“好天”的排列方式共有 $C_{w-1}^{i-1}$ 种方式，“坏天”有 $n-i$ 个，对于每种“坏天”的排列方式，共有 $C_{b-1}^{n-i-1}$ 种插入方式，而“坏天”有 $i-1$ 个空可以插入，所以可以算出来，如果有 $i$ 个“好天”，辣么每种好天和坏天的排列就都有 $C_{w-1}^{i-1}\times(i-1)\times C_{b-1}^{n-i-1}$，最终的答案就是 $\displaystyle \sum_{i=2}^{n-1}{b!\times w!\times C_{w-1}^{i-1}\times(i-1)\times C_{b-1}^{n-i-1}}=b!\times w!\times \sum_{i=2}^{n-1}{C_{w-1}^{i-1}\times(i-1)\times C_{b-1}^{n-i-1}}$ 种方式。

我们可以发现柿子中的组合数只涉及 $C_{w-1}^{i}$ 和 $C_{b-1}^{i}$，可以 $O(n)$ 预处理！！！$C_y^x=C_y^{x-1}\times (y-x+1) \div x$ 而其中的 $\div x$ 也可以 $O(n)$ 预处理！！！在膜 $p$ 意义下 $inv[i]=inv[p \bmod i]\times(p-p/i)$。

贴一下 $AC$ 代码
```cpp
int C1[4010]/*C[w-1][]*/, C2[4010]/*C[b-1][]*/;
int inv[4010];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, w, b;
	cin >> n >> w >> b;
	inv[1] = 1;
	for (int i = 2; i <= 4000; i++)
		inv[i] = inv[mod % i] * (mod - mod / i) % mod;
	C1[0] = C1[w - 1] = 1;
	for (int i = 1, k1 = w - 1, k2 = 1; i < w - 1; i++, k1--, k2++)
		C1[i] = ((C1[i - 1] * k1) % mod * inv[k2]) % mod;
	C2[0] = C2[b - 1] = 1;
	for (int i = 1, k1 = b - 1, k2 = 1; i < b - 1; i++, k1--, k2++)
		C2[i] = ((C2[i - 1] * k1) % mod * inv[k2]) % mod;
	int ans = 0;
	for (int i = 2; i < n; i++) {
		int j = n - i;
		ans = (ans + ((C1[i - 1] * (i - 1)) % mod * C2[j - 1]) % mod) % mod;
	}
	int k1 = 1;
	for (int i = 1; i <= w; i++)
		k1 = (k1 * i) % mod;
	int k2 = 1;
	for (int i = 1; i <= b; i++)
		k2 = (k2 * i) % mod;
	ans = (ans * k1) % mod;
	ans = (ans * k2) % mod;
	cout << ans << endl;
	return 0;
}
```

---

## 作者：shiranui (赞：0)

作为一只优秀的废物居然以为好事 / 坏事可以不做完。。。

## 题目大意

有 $a$ 种好事，$b$ 种坏事，试求将这 $a$ $+$ $b$ 种事件分成到 $n$ 天内发生（每天只能发生好事或坏事中的一种），并按 “好事 - 坏事 - 好事” 方式排列的方案数（模 $10^9 + 9$）。

## 数据范围

$3 ≤ n ≤ 4000$

$2 ≤ a ≤ 4000$

$1 ≤ b ≤ 4000$

保证 $a + b ≥ n$

## 思路

将好事和坏事类分别考虑，枚举有几天发生坏事。

设这 $n$ 天中有 $x$ ( $1$ $≤$ $x$ $≤$ $min$ ( $n$ $-$ $2$, $b$ ) )天发生了坏事，那么剩下的 ( $n$ - $x$ ) 天就发生了好事。

先考虑坏事。

一共有 $b$ 种坏事，要分成 $x$ 组，就有相当于在 $b - 1$ 个空中插 $x - 1$ 个板，共 $C_{b-1}^{x-1}$ 种方法。由于这些坏事两两不同，所以还要乘上一个排列数。

那么 $x$ 天内做完坏事就有 $C_{b-1}^{x-1}\times A_b^b$ 种方案。

如果将前后两段好事拼起来，那么就和发生坏事是一样的情况，即 $C_{a-1}^{n-x-1} \times A_a^a$。

~~作为一只蒟蒻我想到这就开写了。~~

为什么会挂？因为前后两段是分开的，而我并没有考虑到。（~~如此显然的问题我花了半个小时才找出来~~）

所以要在这 $n-x-1$ 个板中选出一个，以此将好事分成前后两段。

综上，推出式子：

$\sum_{x=1}^{min(n-2,b)}{C_{b-1}^{x-1}\times A_b^b\times C_{a-1}^{n-x-1}\times A_a^a\times (n-x-1)} $

~~又臭又长~~。

不要忘记取模。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
inline int read() {
	int s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9'){if (ch == '-') w = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') s = (s << 3) + (s << 1) + (ch ^ 48), ch = getchar();
	return s * w;
}
const int mod = 1e9 + 9;
int n, a, b;
ll A[4010], c[4010][4010];
void C(int x, int y) { // x 中取 y 个 
	if (c[x][y]) return;
	if (y == 0) {c[x][y] = 1; return;}
	if (y == 1) {c[x][y] = x; return;}
	if (y > x - y) {C(x, x - y); c[x][y] = c[x][x - y];	return;} 
	C(x - 1, y), C(x - 1, y - 1);
	c[x][y] = (c[x - 1][y] + c[x - 1][y - 1]) % mod;
	return;
}
ll ans;
int main() {
	A[1] = 1;
	for (int i = 2; i <= 4000; i++) A[i] = (A[i - 1] * i) % mod;
	c[0][0] = 1;
	for (int i = 1; i <= 4000; i++) c[0][i] = c[i][0] = 1, c[i][1] = i;
	for (int i = 1; i <= 4000; i++)
		for (int j = 2; j <= i; j++) 
			if (!c[i][j]) C(i, j);
	n = read(), a = read(), b = read();
	for (int x = 1; x <= min(n - 2, b); x++) {
		ll bad = c[b - 1][x - 1] * A[b] % mod, good = c[a - 1][n - x - 1] * A[a] % mod * (n - x - 1) % mod;
		ans = (ans + bad * good % mod) % mod;
	}
	printf("%lld\n", ans);
	return 0;
}
```

~~代码十分的丑陋（大小写并用的也就我了）~~。

这个 $c$ 数组算是一个记忆化，反正数据范围也不大，预处理一下，后面调用也方便。（还不会因为递归层数太多爆栈）

~~至于为什么不写其他大佬的那种，因为本蒟蒻不会。~~

$A$ 数组记的是阶乘。

---

## 作者：mydcwfy (赞：0)

## 1. 题意

给出 $n$ 天，以及**互不相同**的 $w$ 件好事、$b$ 件坏事，每天只能出现好事、坏事中的一种，要求发生的顺序为 好事 - 坏事 - 好事 的情况的方案数，答案对 $10^9+9$ 取模。

## 2. 思路

首先，**互不相同**可以直接转化为**相同**，也就是我们可以现将答案算出来，然后乘上 $w!\cdot b!$ 即可。

我们再来想如果处理相同的。

我们发现，当好事的总天数一定的时候，前面有多少个、后面有多少个其实是不影响答案的，因为前面不管有多少个，其实都是一样的。

所以，我们可以统计 好事 - 坏事 的情况，然后对于每一个好事天数一定的，我们将一些好事的天放在坏事后面，就可以满足答案了。

答案将会乘上好事的天数减 1。

现在思路已经比较明显了：我们直接暴力枚举好事的天数 $x$，那么坏事的天数就是 $n-x$。

然后，我们发现，要将 $w$ 个好事放入 $x$ 天，每天至少一个，所以方案数就为 $\binom{w-1}{x-1}$。

坏事同理。

预处理组合数可以用 $O(n)$ 预处理阶乘及其逆元，不过没必要，直接 $O(n^2)$ 就可以了。

## 3. Code

注意要处理两倍的大小。

```cpp
int main()
{
    init();
    cin >> n >> w >> b;
    int ans = 0;
    for (int gday = 1; gday < n; ++ gday)//枚举好事的天数
        ans = (ans + (gday - 1ll) * C[w - 1][gday - 1] % Mod * C[b - 1][n - gday - 1] % Mod) % Mod;
    cout << 1ll * ans * fact[w] % Mod * fact[b] % Mod << endl;
    return 0;
}
```

---

