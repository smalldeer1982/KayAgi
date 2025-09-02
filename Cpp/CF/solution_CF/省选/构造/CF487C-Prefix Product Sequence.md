# Prefix Product Sequence

## 题目描述

Consider a sequence $ a_{1},a_{2},... ,a_{n}$ . Define its prefix product sequence ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF487C/ff8116fff58c431c0df2f0dc70c6d2a466564b92.png).

Now given $ n $ , find a permutation of $1,2,...,n$ , such that its prefix product sequence is a permutation of $0,1,...,n-1$ .

## 说明/提示

For the second sample, there are no valid sequences.

## 样例 #1

### 输入

```
7
```

### 输出

```
YES
1
4
3
6
5
2
7
```

## 样例 #2

### 输入

```
6
```

### 输出

```
NO
```

# 题解

## 作者：dfkdsmbd (赞：10)

继续抢一血，构造题都是脑洞嘤嘤嘤。

首先考虑什么时候有解，答案是当$n$为4或者是质数的时候，之所以$4$有解是因为，$4$只能被分解成$4=2·2$,其他的合数都可以被分解成两个比他小的因数，那么这样在$mod \; n$意义下就是0了，所以不可能。

那么继续考虑，$1$不能放在除了第一个地方以外的其他地方，因为放在其他的地方就会出现前缀积相等的情况，$n$只能放在最后，因为前缀积加入$n$以后在$mod \; n$意义下就是0了。

至于中间那些数，我们考虑放入$\frac{2}{1},\frac{3}{2},\frac{4}{3}……$这样的，显然他们统一减去1以后也不会在$mod \; n$意义下相等，并且这样的前缀积因为不停抵消实际上就是$2,3,4,5……$，并不会重复。

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <utility>
#include <cstdio>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <map>
#include <set>
#define ri register int
#define pi acos(-1.0)

using namespace std;

inline char gch()
{
    static char buf[100010], *h = buf, *t = buf;
    return h == t && (t = (h = buf) + fread(buf, 1, 100000, stdin), h == t) ? EOF : *h ++;
}

typedef long long lo;

typedef unsigned int uint;

template<typename inp_typ>

inline void re(inp_typ &x)
{
    x = 0;
    char a; bool b = 0;
    while(!isdigit(a = getchar()))
        b = a == '-';
    while(isdigit(a))
        x = x * 10 + a - '0', a = getchar();
    if(b == 1)
        x = - x;
}

lo n;

inline lo ksm(lo x, lo k, lo mo)
{
    lo rt = 1 % mo, a = x % mo;
    while(k)
        rt = rt * ((k & 1) ? a : 1) % mo, a = a * a % mo, k >>= 1;
    return rt;
}

int main()
{
    re(n);
    if(n == 4)
        printf("YES\n1\n3\n2\n4");
    else
    {
        bool f = 1;
        for(ri i = 2; i * i <= n; i ++)
            if(n % i == 0)
            {
                f = 0; break;
            }
        if(!f)
            printf("NO");
        else
        {
            puts("YES");
            printf("1\n");
            for(ri i = 2; i < n; i ++)
                printf("%lld\n", (lo)i * ksm(i - 1, n - 2, n) % n);
            if(n > 1)
                printf("%lld", n);
        }
    }
    system("pause");
}
```

---

## 作者：little_sun (赞：7)

### 题目描述

构造一个长度为$n$的排列，使得其前缀积在$\mod n$意义下两两不同


### 问题分析

我们发现构造这样一个序列必然有$1$放在第$1$个，$n$放在第$n$个，考虑$(n-1)!$模$n$的余数，可以证明如果$n$为大于$4$的合数，则该余数$=0$，于是无解。

现在我们考虑对于质数$n$怎么做。发现$1$到$(n-1)$都有模$n$意义下的逆元，于是我们可以构造一个序列满足它前缀积$\mod n$的余数是$1$到$n-1$，这样就是一个$ix \equiv (i+1) \mod n$，使用逆元求一下就好了

### 代码
``` cpp
# include <bits/stdc++.h>

# define R register
# define ll long long

const ll MaxN = 1e5 + 10;
ll n, tp, flag, p[MaxN];

ll check(ll x)
{
	for(ll i = 2; i * i <= x; i++)
		if(x % i == 0) return 1;
	return 0;
}

ll exgcd(ll a, ll b, ll &x, ll &y)
{
	ll g = a;
	if(b == 0) x = 1, y = 0;
	else g = exgcd(b, a % b, y, x), y -= (a / b) * x;
	return g;
}

signed main()
{
	scanf("%lld", &n);
	if(n == 1) puts("YES\n1\n");
	else if(n == 4) puts("YES\n1 3 2 4");
	else if(check(n)) puts("NO");
	else
	{
		printf("YES\n1 ");
		for(ll i = 2; i < n; i++)
		{
			ll x, y;
			exgcd(i - 1, n, x, y);
			printf("%lld ", ((x * 1ll * i) % n + n) % n);
		}
		printf("%lld\n", n);
	}
	return 0;
}
```

---

## 作者：MyukiyoMekya (赞：5)

小清新思维题，~~推式子的时候思路 bulibuli 地脱了出来~~

设 $b_i$ 为 $a_i$ 的前缀乘积，首先观察到 $a_i=n$ 的时候 $b_{i\sim n}=0$ ，所以 $a_n=n$

又观察到 $a_i=1$ 的时候 $b_{i-1}=b_i$ ，所以 $a_1=1$。

然后发现当 $n$ 是个合数的时候 $(n>4)$ ，都存在 $i\times j=n,(i\ne j,1< i,j< n)$，所以都是 `NO`。

$n\le 4$ 的时候手玩一下就好了。剩下的情况只有质数才是 `YES`，质数有超多优秀的性质。

由于我们可以求逆元，所以可以构造一个 $b_i=i$ ，那么 $a_i=b_i\times b_{i-1}^{-1}\pmod n$，首先这个 $a_i$ 一定是存在的

那么我们要证一下 $a_i$ 互不相同，即是否存在 $\dfrac i{i-1}=\dfrac j{j-1} \pmod n$，$(1<i<j\le n)$

两边同乘 $(i-1)(j-1)$ 得 $i(j-1)=j(i-1)$ ，$ij-i=ij-j$，$i=j$ ，与 $i<j$ 矛盾，所以 $a_i$ 互不相同。

当然还有一种构造方法就是找到 $n$ 的原根 $g$。

然后 $a=\{g^{(n-1)-0},g^{1},g^{(n-1)-2},g^3,g^{(n-1)-4},g^5,\cdots,n\}$ ，由原根的定义显然得到这是对的。

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
#define int long long
#define ln std::puts("")
template <class t> inline void read(t &s){s=0;
reg int f=1;reg char c=getchar();while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
while(isdigit(c))s=(s<<3)+(s<<1)+(c^48),c=getchar();s*=f;return;}
template<class t,class ...A> inline void read(t &x,A &...a){read(x);read(a...);}
template <class t> inline void write(t x){if(x<0)putchar('-'),x=-x;
int buf[21],top=0;while(x)buf[++top]=x%10,x/=10;if(!top)buf[++top]=0;
while(top)putchar(buf[top--]^'0');return;}
inline int fpow(int a,int b,int p)
{
	reg int res=1;
	for(;b;b>>=1,a=a*a%p)
		if(b&1)
			res=res*a%p;
	return res;
}
inline bool isprime(int x)
{
	if(x==1)return false;
	reg int maxi=std::sqrt(x);
	for(int i=2;i<=maxi;++i)
		if(!(x%i))
			return false;
	return true;
}
inline int GetG(int p)
{
	reg int maxi=std::sqrt(p-1);
	for(reg int g=2;g<p;++g)
	{
		reg int flg=1;
		for(int k=2;flg&&k<=maxi;++k)
			if(!((p-1)%k))
				if(fpow(g,k,p)==1||fpow(g,(p-1)/k,p)==1)
					flg=0;
		if(flg)
			return g;
	}
	return -1;
}
signed main(void)
{
	int n;read(n);
	if(n==1)return std::printf("YES\n1\n"),0;
	if(n==4)return std::printf("YES\n1\n3\n2\n4\n"),0;
	if(n==2)return std::printf("YES\n1\n2\n"),0;
	if(!isprime(n))return std::puts("NO"),0;
	reg int g=GetG(n);
	std::puts("YES");
	for(int i=0;i<n-1;++i)
		if(i&1)
			write(fpow(g,i,n)),ln;
		else
			write(fpow(g,n-i-1,n)),ln;
	write(n),ln;
	return 0;
}
```



---

## 作者：crn1 (赞：3)

这是一篇纯找规律的题解

## 题目大意
给定整数 $n\ (1\leq n\leq 10^5)$ ，求出一个长度为 $n$ 的排列，使得该排列前缀积互不相同。

## 题解
可以根据题意写出如下暴力
```cpp
#include <algorithm>
#include <cstdio>

const int N = 100005;
int a[N], b[N], c[N];

int main(void) {
	int n; scanf("%d", &n);
	for (int i = 1; i <= n; ++i) a[i] = i;
	do {
		for (int i = 0; i < n; ++i) b[i] = 0;
		int s = 1, flg = 1;
		for (int i = 1; i <= n; ++i) { // check
			s = (s * a[i]) % n;
			c[i] = s;
			if (b[s]) { flg = 0; break; }
			b[s] = 1;
		}
		if (flg) {
			puts("-----------------------------------------");
			for (int i = 1; i <= n; ++i)
				printf("%d%c", a[i], " \n"[i == n]);
			for (int i = 1; i <= n; ++i)
				printf("%d%c", c[i], " \n"[i == n]);
		}
	} while (std::next_permutation(a + 1, a + n + 1)); // 枚举排列
	return 0;
}
```

从 $1$ 开始试到 $13$，发现只有 $1,2,3,4,5,7,11,13$ 存在合法排列，由此大胆猜测，当且仅当 $n$ 为质数或 $n$ 为 $1$ 或 $4$ 时存在合法排列。

接下来研究合法排列有什么共同的特征，单从排列观察无法发现有用的信息，于是研究合法排列前缀积的共同特征，如果特征存在，求出前缀积后用逆元求出每一项。

考虑选择 $5$ 和 $7$ 作为分析对象，因为 $2$ 和 $3$ 都只有一项且长度太小，并且 $11$ 存在的合法排列过多。

以下为 $5$ 和 $7$ 对应所有合法排列及其前缀积：

$5$
```
1 2 4 3 5
1 2 3 4 0
```
和
```
1 3 4 2 5
1 3 2 4 0
```

$7$
```
1 2 5 6 3 4 7
1 2 3 4 5 6 0
```
和
```
1 3 4 6 2 5 7
1 3 5 2 4 6 0
```
和
```
1 4 3 6 5 2 7
1 4 5 2 3 6 0
```
和
```
1 5 2 6 4 3 7
1 5 3 4 2 6 0
```

在 $5$ 和 $7$ 中很容易发现两组特别的前缀积 `1 2 3 4 0` 和 `1 2 3 4 5 6 0`，由此再猜测，前缀积中第 $i$ 项为 $i\ \mathrm{mod}\ n$，写出以下程序，成功通过此题。

```cpp
#include <cstdio>

using i64 = long long;

const int N = 1e5 + 5;
int a[N];

int inv(int x, int p) {
	int res = 1, y = p - 2;
	for (; y; y /= 2, x = (i64)x * x % p)
		if (y & 1) res = (i64)res * x % p;
	return res;
}

int main(void) {
	int n; scanf("%d", &n);
	if (n == 1) return puts("YES\n1"), 0;
	if (n == 4) return puts("YES\n1\n3\n2\n4"), 0;
	for (int i = 2; i * i <= n; ++i)
		if (n % i == 0) return puts("NO"), 0;
	puts("YES\n1");
	for (int i = 1; i <= n; ++i) a[i] = i % n;
	for (int i = 2; i < n; ++i) printf("%d\n", (int)(a[i] * (i64)inv(a[i - 1], n) % n));
	printf("%d", n);
	return 0;
}
```

其实除了前缀积第 $i$ 项为 $i\ \mathrm{mod}\ n$ 以外，还有一个共同的特征，观察以下两组前缀积

```
1 3 2 4 0
1 5 3 4 2 6 0
```

第一眼看上去确实没啥特征，但是由外向内逐层观察，在 `1 3 2 4 0` 这组前缀积中，第一层为 `1 0` 由右向左从 $0$ 开始递增，第二层为 `3 4` 由右向左从 $n-1$ 开始递减。在 `1 5 3 4 2 6 0` 中此规律也成立，写出以下代码，也可成功 AC 此题。

```
#include <cstdio>

using i64 = long long;

const int N = 1e5 + 5;
int a[N];

int inv(int x, int p) {
	int res = 1, y = p - 2;
	for (; y; y /= 2, x = (i64)x * x % p)
		if (y & 1) res = (i64)res * x % p;
	return res;
}

int main(void) {
	int n; scanf("%d", &n);
	if (n == 1) return puts("YES\n1"), 0;
	if (n == 4) return puts("YES\n1\n3\n2\n4"), 0;
	for (int i = 2; i * i <= n; ++i)
		if (n % i == 0) return puts("NO"), 0;
	puts("YES\n1");
	for (int i = 0, x = -1, y = n; i < n / 2; ++i) {
		if (i & 1) a[n - i] = --y, a[i + 1] = --y;
		else a[n - i] = ++x, a[i + 1] = ++x;
	}
	a[n / 2 + 1] = n / 2 + (n / 2 & 1);
	for (int i = 2; i < n; ++i) printf("%d\n", (int)(a[i] * (i64)inv(a[i - 1], n) % n));
	printf("%d", n);
	return 0;
}
```

---

## 作者：feecle6418 (赞：3)

若 $n$ 为质数显然有解。令 $p_i=\dfrac{i}{i-1}\pmod n$，则前缀积呈现 $1,2,\dots,n-1,0$ 的形式显然符合要求。

若 $n=1$，有解 $1$。若 $n=4$，有解 $1,3,2,4$。否则，一定存在两个整数 $1<a<b<n$ 使 $n|ab$，因此 $0$ 必定出现两次，无解。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,pl[100005],prod[100005];
int Power(int x,int y,int mod){
	int r=1;
	while(y){
		if(y&1)r=1ll*r*x%mod;
		x=1ll*x*x%mod,y>>=1;
	}
	return r;
}
int main(){
	cin>>n;
	if(n==4)return puts("YES\n1 3 2 4"),0;
	for(int i=2;i*i<=n;i++)if(n%i==0)return puts("NO"),0;
	pl[1]=prod[1]=1;
	for(int i=2;i<=n;i++){
		pl[i]=1ll*Power(prod[i-1],n-2,n)*i%n;
		prod[i]=1ll*prod[i-1]*pl[i]%n;
	}
	puts("YES");
	for(int i=1;i<=n;i++)cout<<(pl[i]==0?n:pl[i])<<' ';
	cout<<endl;
    return 0;
}
```

---

## 作者：Caro23333 (赞：3)

一血没了.jpg

感觉分数的构造挺巧妙的，但这里可以提供一种其他做法。

显然当$n>4$且$n$为合数时无解，因为这时存在$p\neq q,\ p,q<n$且$pq=n$，那么只要$p,q$在排列中都出现过了，那么从这里开始前缀积序列就都是$n$的倍数了，不符题意。

如果$n$为质数一定有解吗？答案是肯定的。首先无论如何要把$n$放在最后，否则就和上面的无解情况一样不符合题意了。这时剩下$1$到$n-1$没有放，因为模数是一个质数，所以我们考虑利用原根的性质。

假设已经求出了$n$的一个原根$g$，我们只要把模$n$意义下的$g^0,g^1,\dots,g^{n-2}$排列好就ok了。这时候如果存在两个前缀积在模$n$意义下相等，等价于存在两个指数的前缀和在模$n-1$意义下相等，我们只要规避这种情况就好了。

经过思考，发现形如$[0,n-2,2,n-4,4,n-6,\dots]$（遍历$0$到$n-2$）的指数序列是满足要求的，读者不难验证。那么直接快速幂就好啦~

还有一个问题是如何求原根。据我所知，质数的原根暂没有优秀的算法，只能用看起来是$O(n^2)$的暴力来求。不过根据打表/猜测，得知$10^5$以内的质数原根都很小，所以从小到大暴力检查完全可以通过。

另外记得特判$n=1:[1]$和$n=4:[1,3,2,4]$。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;
typedef long long ll;
const int MAXN = 100005;
inline bool isPrime(int x)
{
	if(x==1)
	    return false;
	for(int i = 2; i*i<=x; i++)
	    if(x%i==0)
	        return false;
	return true;
}
int vis[MAXN];
inline int calc(int x)
{
	for(int i = 2; i<x; i++) 
    {
    	ll tmp = 1;
    	bool flag = true;
        for(int j = 0; j<x-1; j++, tmp = tmp*i%x)
        {
            if(vis[tmp]==i)
            {
                flag = false;
                break;
			}
			vis[tmp] = i;
		}
		if(flag)
		    return i;
	}
}
inline ll qpow(ll a, int b, int c)
{
	ll res = 1;
	for(; b; a = a*a%c, b >>= 1)
	    if(b&1)
	        res = res*a%c;
	return res;
}

int main()
{
    int n;
    scanf("%d",&n);
    if(n==1)
	{
        printf("YES\n1\n");
        return 0;
	}
	if(n==2)
	{
        printf("YES\n1\n2\n");
        return 0;
	}
	if(n==4)
	{
        printf("YES\n1\n3\n2\n4\n");
        return 0;
	}
	if(!isPrime(n))
    {
        printf("NO\n");
        return 0;
	}
	printf("YES\n");
	int g = calc(n);
	for(int i = 0; i<(n-1)/2; i++)
	    cout << qpow(g,2*i,n) << endl << qpow(g,n-2*(i+1),n) << endl;
	printf("%d\n",n); 
	return 0;
}

```


---

## 作者：hexu2010 (赞：1)

# CF487C Prefix Product Sequence 题解
## 题目大意
是否存在一个长度为 $n$ 的排列，使得其前缀积在 $mod\,n$ 意义下两两不同？如果没有，则输出 NO ，否则输出 YES 并给出方案。
## 解析
首先是判断到底有没有解。我们可以举几个例子来找一下规律。

| $n$ | 是否有解 | 具体方案 |
| :--: | :--: | :--- |
| 1 | 有 | 1 |
| 2 | 有 | 1 2 |
| 3 | 有 | 1 2 3 |
| 4 | 有 | 1 3 2 4 |
| 5 | 有 | 1 3 4 2 5 |
| 6 | 无 | - |
| 7 | 有 | 1 4 3 6 5 2 7 |
| 8 | 无 | - |
| 11 | 有 | 1 2 7 5 4 10 3 9 8 6 11 |

可以发现似乎与素数有关。猜想一下：当且仅当 $n$ 不为合数时有解。但是看到 $4$ 的时候，就发现错了。于是，完善一下：当且仅当 $n$ 不为合数或 $n=4$ 时有解。如何证明呢？其实把题目条件换一下就好了。

首先，$n$ 必须在第 $n$ 个，用反证法就可以证明。若 $n$ 的位置已经确定，那么前缀积的第 $n-1$ 项就是 $(n-1)!$ ，同时，前缀积的第 $n$ 项模 $n$ 的余数为 $0$ 。进而得知，当 $n \mid(n - 1)!$ 时没有方案。显然，当 $n$ 为素数时，$n \nmid (n-1)!$ 。在合数中除 $4$ 外均能整除，故命题成立。

判断完有没有解之后，就要求出方案。这里就需要**构造**。既然要求不相等，那就给定方便的前缀积。就让前缀积模 $n$ 的余数为 $1,2,3,\dots,0$ 吧。这样，可以得出最终的排列为 $1,\frac{2}{1},\frac{3}{2},\frac{4}{3},\dots,n$ 。这里，分数可以用逆元计算。由于 $n$ 除了 $4$ 外都是素数，就可以把 $n=4$ 时特判了，这样计算逆元就可以用费马小定理了。

注：费马小定理是说 $a$ 在模 $p$ 下的逆元就是 $a^{p-2}$ 模 $p$ 的逆元。

最后，分析一下时间复杂度。首先，判素数要 $O(\sqrt{n})$，然后对于每一项都求逆元，也就是快速幂（复杂度 $O(\log_2n)$），复杂度为 $O(n \log n)$ 。

## 算法流程

![](https://cdn.luogu.com.cn/upload/image_hosting/0l0d7hkk.png)

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int s = 0, w = 1;
	char ch = getchar();
	for(; ch < '0' || ch > '9'; w *= (ch == '-') ? -1 : 1, ch = getchar());
	for(; ch >= '0' && ch <= '9'; s = 10 * s + ch - '0', ch = getchar());
	return s * w;
}
const int MAXN = 100005;
int res[MAXN];
int qpow(int a, int p, int m){//快速幂
	int res = 1;
	while(p){
		if(p & 1) res = res * a % m;
		a = a * a % m;
		p >>= 1;
	}
	return res;
}
int inverse(int a, int mod){//费马小定理求逆元
	return qpow(a, mod - 2, mod) % mod;
}
bool is_prime(int n){//判断素数，用于特判
	for(int i = 2; i * i <= n; i++){
		if(n % i == 0) return false;
	}
	return true;
}
signed main(){
	int n = read();
	if(is_prime(n) == false && n != 4) {
		cout << "NO" << endl;
		return 0;
	}
	cout << "YES" << endl;
	if(n == 4){
		cout << "1\n3\n2\n4\n" << endl;
		return 0;
	}
	res[1] = 1, res[n] = n;//头尾都能确定
	for(int i = 2; i < n; i++){
		res[i] = i * inverse(i - 1, n) % n;//用逆元代替分数
	}
	for(int i = 1; i <= n; i++){
		cout << res[i] << endl;
	}
	return 0;
}
```

---

## 作者：OIerAlbedo (赞：1)

# Solution

构造题还是差不多得了。

考虑到如果 $ n>4 $ 的话，那么一定只有质数的 $ n $ 可能可以满足题目的要求。

那么我们分类讨论 $ n\le 4 $ 的情况直接暴力枚举输出即可。

但是 $ n>4 $ 的情况呢，质数，什么和质数有关，逆元？然而逆元好像就是正确的。

来一波严谨证明。

由于 $ n $ 是质数。

显然有 $ \frac{1}{x}\equiv x^{n-2} (\bmod n) $ 。

如果存在两个数的逆元相同，就是 $ \frac{1}{x}\equiv \frac{1}{y}\equiv G (\bmod n) $ 。那么显然有 $ G^{n-2}\equiv x\equiv y (\bmod n) $ 。由于 $ x,y<n $，那么只能有 $ x=y $，得证。

我们通过小学知识可以知道：
$$
\frac{1}{2}\times \frac{2}{3}\times ...\frac{n-1}{n}=\frac{1}{n}
$$
那么我们可以知道，对于每一位 $ i $，他的答案就是 $ 1-\frac{1}{i} $。由于 $ 1\sim n-1 $ 的每个数的逆元是不同的，所以这个答案也是互不相同的。

# Code

```c++
	if (n==1) {printf("YES\n1\n");return 0;}
	if (n==2) {printf("YES\n1\n2\n");return 0;}
	if (n==3) {printf("YES\n1\n2\n3\n");return 0;}
	if (n==4) {printf("YES\n1\n3\n2\n4\n");return 0;}
	if (check(n)==false) {puts("NO");return 0;}
	puts("YES");inv[1]=1;
	for (i=2;i<=n;i++) inv[i]=(n-n/i)*inv[n % i] % n;inv[n]=n;ans=1;
	printf("1\n");for (i=2;i<n;i++) printf("%lld\n",(n+1-inv[i]) % n);printf("%lld\n",n);
```



---

## 作者：Rubidium_Chloride (赞：1)

小清新构造题。

好像下面题解都没有说 $n=p^2(p\ge 3)$ 的时候为什么不行，来补一发。

事实上很简单，$1< p<2p<n$，所以至少有两个 $b_i$ 是 $\mod n$ 余 $0$ 的。

然后 $n=pq(1<p<q<n)$ 的时候，直接考虑 $p,q$ 两个数可以发现也会导致冲突。

因此仅有 $n=1,4\ \text{or}\ n\ \text{is prime}$ 的时候有解。

数据点里面塞了个 $n=1$，令我非常 /tuu。

然后 $n=4$ 的时候直接手玩 `1 3 2 4`，$n\ \text{is prime}$ 的时候考虑以下构造：$1,2\times 1^{-1}\bmod n,3\times 2^{-1}\bmod n\dots((n-1)\times (n-2)^{-1})\bmod n,n$。

发现 $b_i\bmod n$ 分别是 $1,2,3,\dots n-1,0$。

然后有 $n\ \text{is prime}$ 的条件因此可以直接上费马小定理求逆元。



## 代码

```
#include<bits/stdc++.h>
#define N 100009
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;
inline ll read() {
    ll x=0,f=1;int c=getchar();
    while(!isdigit(c)) {if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)) {x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*f;
}
ll n,a[N],pr[N],cnt;
bool vst[N];
void prime(ll n){
	for(int i=2;i<=n;i++){
		if(!vst[i]) pr[++cnt]=i;
		for(int j=1;j<=cnt&&i*pr[j]<=n;j++){
			vst[i*pr[j]]=1;
			if(i%pr[j]==0) break;
		}
	}
}
ll qpow(ll x,ll pw){
    ll ans=1;
    while(pw){
        if(pw&1) ans=ans*x,ans%=n;
        x*=x,x%=n,pw>>=1;
    }
    return ans;
}
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    prime(100000);
    n=read();
    if(n==1){printf("YES\n1\n");return 0;}
    if(n!=4&&vst[n]==1){printf("NO\n");return 0;}
    if(n==4){printf("YES\n1\n3\n2\n4");return 0;}
    printf("YES\n1\n");
    for(int i=2;i<=n-1;i++) printf("%lld\n",1ll*i*qpow(i-1,n-2)%n);
    printf("%lld",n);
    return 0;
}
```

---

## 作者：Φρανκ (赞：0)

题意：求 $1\sim n$ 的排列满足其前缀积在模 $n$ 意义下各不相同。

核心思想：构造

解：

容易发现，对于 $1$ ，可以构造排列 $1$ 满足条件。

对于所有其他正整数，它本身必定出现在排列的末尾，且它之前的所有数的积不能是它的倍数（否则会出现多于一个 $0$ ）。容易发现，只有质数和 $4$ 满足条件。

对于 $4$ ，可以构造排列 $1\: 3\: 2\: 4$ 满足条件。

对于质数，序列必然以 $1$ 开始（因为其不会改变前缀积）。构造第 $1<i\le n$ 项为 $i(i-1)^{-1}$ ，则第 $i$ 个前缀积为 $i\bmod n$ 。

又因有 $i(i-1)^{-1}=(i-1)(i-1)^{-1}+(i-1)^{-1}=(i-1)^{-1}+1$ ，故其加上第一项 $1$ 即构成完全剩余系，满足条件。

运用线性求逆元求算即可。

代码：
```
#include <bits/stdc++.h>
using namespace std;
long long n, b[100001], p[100001], flag, in[100001];
int main()
{
	cin>>n;
	if(n==1)
	{
		cout<<"YES"<<endl<<1;
		return 0;
	}//特判1
	if(n==4)
	{
		cout<<"YES"<<endl<<1<<endl<<3<<endl<<2<<endl<<4;
		return 0;
	}//特判4
	for(int i=2; i<=100000; i++)
	{
	    if(b[i]==0)
	      p[++flag]=i;
	    for(int j=1; j<=flag; j++)
		{
	      if(i*p[j]>100000) 
		  	break;
	      b[i*p[j]]=1;
	      if(i%p[j]==0)
	        break;
		}
    }//线性筛质数
    if(b[n]==1)
    {
    	cout<<"NO";
    	return 0;
	}//判断合数
    in[1]=1;
    for(int i=2; i<n; i++)
    	in[i]=(n-n/i)*in[n%i]%n;//线性求逆元
    for(int i=1; i<n; i++)
    	in[i]=in[i]*(i+1)%n;
    cout<<"YES"<<endl<<1<<endl;
    for(int i=1; i<n; i++)
    	cout<<(in[i]+n-1)%n+1<<endl;//输出
	return 0;
}
```

---

## 作者：XL4453 (赞：0)

### $\text{Difficlty : 2300}$
---
### 解题思路：

考虑一个在 $n$ 意义下满足条件的序列 $a$，显然有 $a_1=1$，$a_n=n$，且 $a_i$ 一定可以写成 $\dfrac{\prod_{j=1}^ia_j}{\prod_{j=1}^{i-1}a_j}\bmod n$ 的形式。

由于 $\prod_{j=1}^ia_j$ 互不相同，所以比 $n$ 的小的数中，最多只有一个数没有模 $n$ 意义下的逆元。而且这个没有逆元的数如果存在，就一定要放到倒数第二个数上去。

而一个数在模 $n$ 意义下有逆元的充要条件是 $\gcd(a,n) =1$，上述内容中所要求的所以比 $n$ 的小的数中有逆元的数的个数也就是 $\phi(n)$。即题目有解的一个必要条件是：要求 $\phi(n)\ge n-2$。

满足这个的显然只有 $1$，$4$ 和任意的一个质数了。证明直接套用 $\phi(n)=n\prod(1-\dfrac{1}{p_i})$，不赘述。

---
然后考虑这些已经经过筛选的数中是否全都成立，并给出构造方案。

首先将较为特殊的 $1$ 和 $4$ 单独构造，$1$ 的序列直接是 $1$，$4$ 的构造方案是 $1,3,2,4$，满足条件。

然后考虑质数的构造。由于每一个比 $n$ 小的数都有逆元，所以考虑直接用 $1,\dfrac{2}{1},\dfrac{3}{2},\dfrac{4}{3}...,\dfrac{n-1}{n-2},n$ 来进行构造。

关键就是证明前面的这些数互不相同。将这个序列中的所有数减去 $1$，得到 $0,1,\dfrac{1}{2}...,n-1$，这些数并不相等，所以加上一之后也同样不相等。	

数据范围很小，不太需要考虑复杂度的问题。


---
### 代码：

```cpp
#include<cstdio>
using namespace std;
#define int long long
int n;
int pow(int a,int b,int MOD){
	int ans=1;
	while(b){
		if(b&1)ans=(ans*a)%MOD;
		a=(a*a)%MOD;
		b=b>>1;
	}
	return ans;
}
bool check(int x){
	for(int i=2;i*i<=x;i++)
	if(x%i==0)return 0;
	return 1;
}
signed main(){
	scanf("%I64d",&n);
	if(n==4){printf("YES\n1\n3\n2\n4\n");return 0;}
	if(n==1){printf("YES\n1\n");return 0;}
	if(check(n)==0){printf("NO\n");return 0;}
	printf("YES\n1\n");
	for(int i=2;i<n;i++){
		printf("%I64d\n",i*pow(i-1,n-2,n)%n);
	}
	printf("%I64d\n",n);
	return 0;
}
```


---

## 作者：RiceFruit (赞：0)

## 题目大意

[题目传送门](https://www.luogu.com.cn/problem/CF487C)

给你一个正整数 $n$，请你构造一个长度为 $n$ 的只包含 $1\sim n$ 排列，使得前缀积在 $n$ 意义下两两不同。

## 题目分析

首先，我们可以确定：第一位一定是 $1$ （这个显然），最后一位一定是 $n$，我们可以采用反证法：

设 $n$ 填在第 $x$ （ $2\le x <n$ ）位，则 $1\sim x$ 位的积 $\bmod n$ 一定是 $0$，而第 $x+1$ 位的前缀积 $\bmod n$ 也是 $0$，不符合题意，则 $n$ 只能填在最后一位。

接下来我们考虑 $n$，如果它是一个合数，则无解( $4$ 除外)

因为 $n$ 是一个合数，则它一定能分解成 $a\times b$。我们设他们分别在第 $x$ 和第 $y$ 位。不妨设 $x<y$，则第 $y$ 位的前缀积 $\bmod n$ 一定位 $0$ （因为 $a\times b=n$ ），而第 $n$ 位的前缀积也为 $0$，不符合题意。

所以我们得出了结论：当 $n$ 为合数（除了 $4$ ），无解。

接下来我们考虑素数怎么构造。

因为我们知道第 $1$ 位的前缀积一定是 $1$，第 $n$ 位的前缀和 $\mod n$ 的值为 $0$ ，所以我们就考虑将前缀和构造成 $1,2,3,4\cdots n-1,0$ 的形式。

如果这样，我们将 $a$ 构造成 $1,\frac{2}{1},\frac{3}{2}\cdots \frac{n-1}{n-2},n$ 即可，而除号可以理解成逆元。

最后别忘记特判 $1$ 和 $4$ 的情况即可。

## CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
#define R register
#define ri register int
#define int long long
#define ull unsigned long long
#define lid (id<<1)
#define rid (id<<1|1)
void swap(int &x,int &y){int t=x;x=y;y=t;}
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
const int N=2001;
inline int read();
inline void write(int ans);
inline void put(int x,char c);
int n;
bool prime(int x){
	if(x<2)return 0;
	if(x==2)return 1;
	if(x%2==0)return 0;
	for(int i=3;i*i<=x;i+=2){
		if(x%i==0)return 0;
	}
	return 1;
}
int qow(int a,int b){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%n;
		b>>=1,a=a*a%n;
	}
	return ans;
}
signed main(){
//	ios_base::sync_with_stdio(0);
	n=read();
	if(n==1){
		cout<<"YES\n1";
		return 0;
	}
	if(n==4){
		puts("YES\n1\n3\n2\n4");
		return 0;
	}
	if(!prime(n)){
		cout<<"NO\n";
		return 0;
	}//1 2/1 3/2 4/3
	printf("YES\n1\n");
	for(int i=2;i<=n;i++){
		int x=i*qow(i-1,n-2)%n;
		if(x==0)x=n;
		printf("%lld\n",x);
	}
	return 0;
}
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x;}
inline void write(int x){if(x<0){putchar('-');x=-x;}if(x>9){write(x/10);}putchar(x % 10+'0');return;}
inline void put(int x,char c){write(x);putchar(c);return;}
```

有不理解的地方可以私信找我

---

