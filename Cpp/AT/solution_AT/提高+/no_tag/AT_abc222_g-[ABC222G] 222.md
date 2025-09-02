# [ABC222G] 222

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc222/tasks/abc222_g

$ 2,22,222,2222,\ldots $ という数列があります。この数列の第 $ i $ 項は、全ての桁が $ 2 $ である $ i $ 桁の整数です。

この数列に初めて $ K $ の倍数が登場するのは何項目ですか？ 存在しない場合は代わりに `-1` と答えてください。

$ T $ 個のケースが与えられるので、それぞれについて答えてください。

## 说明/提示

### 制約

- $ 1\ \leq\ T\ \leq\ 200 $
- $ 1\ \leq\ K\ \leq\ 10^8 $
- 入力に含まれる値は全て整数である

### Sample Explanation 1

$ 4 $ 個のケースが与えられています。 - $ 2 $ は $ 1 $ の倍数です - $ 2,22,222,2222,22222 $ は $ 7 $ の倍数ではありませんが、$ 222222 $ は $ 7 $ の倍数です - $ 2,22,\ldots $ が $ 10 $ の倍数になることはありません

## 样例 #1

### 输入

```
4
1
7
10
999983```

### 输出

```
1
6
-1
999982```

# 题解

## 作者：high_sky (赞：8)

# AT_abc222_g [ABC222G] 222 题解分析

## 思路

### 题意转化

等价于求最小的 $x$ 使得：
$$
\frac 2 9(10^x-1)\equiv 0\pmod K
$$

### 引理部分

引理 $1$：若 $ax\equiv 0\pmod m$，那么 $x\equiv0\pmod {\frac m {\gcd(a,m)}}$。

引理 $2$：若 $\frac{x} b\equiv 0\pmod m$，那么 $x\equiv 0\pmod {bm}$。

### 变换

不难用两个**引理**转换题意为：
$$
10^x\equiv 1\pmod M
$$
其中 $x$ 是最小满足条件的数，以及：
$$
M=\left\{\begin{matrix}
\frac 9 2K  & K\equiv 0\pmod 2\\
9K  &K\equiv 1\pmod 2
\end{matrix}\right.
$$
注意到欧拉定理：
$$
a^{\varphi(m)}\equiv 1\pmod m
$$
所以：
$$
10^{\varphi(M)}\equiv 1\pmod M
$$
我们假设 $\varphi(M)=kx+b$，其中 $k,b$ 为整数。

则：
$$
10^{kx}\times10^b\equiv1\pmod M
$$
推导得：
$$
(10^x)^k\times10^b\equiv 1\pmod M
$$
由于：
$$
10^x\equiv1\pmod M
$$
故：
$$
10^b\equiv1\pmod M
$$
由于 $x$ 是最小满足条件的，所以：
$$
b=k_2x
$$
其中 $k_2$ 为整数。

- 若 $k_2=0$，则 $\varphi(M)=kx$，得到 $x\mid\varphi(M)$。
- 若 $k_2\ne0$，则 $\varphi(M)=(k+k_2)x$，得到 $x\mid\varphi(M)$。

综上所述：
$$
x\mid\varphi(M)
$$
故我们可以暴力枚举 $\varphi(M)$ 的因子求出最小满足条件的 $x$ 即可，时间复杂度为 $\mathcal{O}(\sqrt{\varphi(M)})$。

### 引理推导

**引理 $1$** 推导：

设 $d=\gcd(a,m)$，则设 $a=da',m=dm'$。

有：
$$
ax\equiv0\pmod m\Rightarrow da'x\equiv0\pmod {dm'}
$$
设 $k$ 为正整数，有：
$$
da'x=kdm'
$$
得到：
$$
a'x=km'
$$
所以：
$$
a'x\equiv0\pmod {m'}
$$
由于：
$$
\gcd(a',m')=1
$$
所以又有：
$$
x\equiv 0\pmod {m'}\Rightarrow x\equiv 0\pmod {\frac m{\gcd(a,m)}}
$$
**引理 $2$** 推导：

跟上述差不多。

首先设 $k$ 为正整数，可以得到：
$$
\frac x b=km
$$
然后就有：
$$
x=bkm
$$
所以：
$$
x\equiv 0\pmod {bm}
$$

## 代码

时间复杂度 $\mathcal{O}(T\sqrt{\varphi(M)})$，代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stdlib.h>
#include <cstring>
#include <vector>
#define int long long
#define N 100000001
#define M 5761457
using namespace std;
int T;
//bool vis[N];
//int prime[N],phi[N],cnt;
int qpow(int a,int b,int mod) {
	int res = 1;
	while(b) {
		if (b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	} 
	return res;
}
//void init(int n) {
//	phi[1] = 1;
//	for (int i = 2;i <= n;i ++) {
//		if (!vis[i]) prime[++cnt] = i,phi[i] = i - 1;
//		for (int j = 1;j <= cnt && prime[j] * i <= n;j ++) {
//			vis[prime[j] * i] = 1;
//			if (i % prime[j] == 0) {
//				phi[i * prime[j]] = prime[j] * phi[i];
//				break;
//			}
//			phi[i * prime[j]] = phi[prime[j]] * phi[i];
//		}
//	}
////	cout << cnt << endl;
////	for (int i = 1;i <= cnt;i ++) cout << prime[i] << ' ';
//}
int get_euler(int x) {
	int res = x;
	for (int i = 2;i * i <= x;i ++)
		if (x % i == 0){
			while(x % i == 0) x /= i;
			res = res / i * (i - 1);
		}
	if (x > 1) res = res / x * (x - 1);
	return res;
}
signed main(){
	//int T;
	cin >> T;
	for (;T--;) {
		int x;
		scanf("%lld",&x);
		int mod = ((x & 1) ? x * 9 : x / 2 * 9),phi = get_euler(mod),res = phi + 1;
		for (int i = 1;i * i <= phi;i ++)
			if (phi % i == 0) {
//				cout << i << ' ' << qpow(10,i,mod) << endl;
				if (qpow(10,i,mod) == 1) res = min(res,i);
				if (qpow(10,phi / i,mod) == 1) res = min(res,phi / i);
			}
		if (res == phi + 1) puts("-1");
		else printf("%lld\n",res);
	}
	return 0;
}
```
感谢管理员的审核，最后一次更改了一些细节。

---

## 作者：azaa414 (赞：3)

# 题意分析

给你一个数字 $k$，求至少由多少位 $2$ 组成的数字是 $k$ 的倍数，不存在的话就输出 ```-1```。

# 做法

对于由 $n$ 位组成的数字 $222 \dots$，我们可以进行一些转化，使得其更易表示。

不难发现，
$$
222 \dots = 2 \times 111 \dots = 2 \times \frac{999 \dots}{9}  = 2 \times \frac{10^{m}-1}{9} 
$$

由题意不难得

$$
k \mid 2 \times \frac{10^{m}-1}{9}
$$

两边同时乘以 $9$，得

$$
9k \mid 2 \times \left ( 10^{m}-1 \right )
$$

不妨令两边同时除以 $\gcd(k, 2)$，得

$$
\frac {9k}{\gcd(k, 2)} \mid \frac {2} {\gcd(k, 2)} \times \left ( 10^{m}-1 \right )
$$

分析可知，$k$ 和 $2$ 除以它们的 $\gcd$ 后，$\frac {2} {\gcd(k, 2)} $ 这一部分已经不再影响原式是否成立。

你可以理解为它们的因数已经消除了，所以上式成立可转化为以下式子成立。

$$
\frac {9k}{\gcd(k, 2)} \mid \left ( 10^{m}-1 \right )
$$

这就好看多了！

转化为同余式，有

$$
10^{m} \equiv 1 \left( mod \  \frac {9k}{\gcd(k, 2)} \right )
$$

易证得 $m$ 为 $\varphi \left ( \frac {9k}{\gcd(k, 2)} \right )$ 的因数，具体证明过程可参考 lyd 算法竞赛进阶指南。

然后求出 $\varphi \left ( \frac {9k}{\gcd(k, 2)} \right )$，再逐个枚举它的因数，找到最小的满足题意的因数，输出即可，没找到就输出 ```-1```。

# 代码

```cpp
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>
using namespace std;
#define ll __int128
#define ri register int
#define mst(x,y) memset(x, y, sizeof(x))
#define ciallo putchar('\n')
#define ilv inline void
#define ili inline int
#define ilb inline bool
#define ill inline __int128
constexpr auto N = 1000010;
static ill read();
static ilv writ(ll x);
static ilv write(ll x);
ill quick_power(ll base, ll power, ll mod)
{
    ll result = 1;
    while (power > 0)
    {
        if (power & 1)
            result = result * base % mod, result %= mod;
        base = base * base % mod;
        power >>= 1;
    }
    return result % mod;
}
ll gcd(ll a, ll b)
{
    return b ? gcd(b, a % b) : a;
}
vector <ll> s;
ill phi(ll n)
{
    ll ans = n;
    for (ll i = 2; i * i <= n; ++i)
        if (!(n % i))
        {
            ans = ans / i * (i - 1);
            while (!(n % i)) n /= i;
        }
    if (n > 1) ans = ans / n * (n - 1);
    return ans;
}
int main() {
    ll T = read();
    while (T--)
    {
        ll l = read();
        s.clear();
        ll d = gcd(2, l);
        ll n = 9 * l / d;
        if (gcd(10, n) != 1) write(-1), ciallo;
        else
        {
            ll x = phi(n);
            for (ll i = 1; i * i <= x; i++)
            {
                if (!(x % i))
                {
                    s.push_back(i);
                    if (x / i != i)
                        s.push_back(x / i);
                }
            }
            sort(s.begin(), s.end());
            for (int i = 0; i < s.size(); i++)
                if (quick_power(10, s[i], n) == 1) { write(s[i]), ciallo; break; }

        }
    }
}
static ill read()
{
    ll x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = 10 * x + c - '0';
        c = getchar();
    }
    return f * x;
}
static ilv writ(ll x)
{
    if (x < 0)
    {
        putchar('-');
        x = -x;
    }
    if (x > 9) writ(x / 10);
    putchar(x % 10 | 0x30);
    return;
}
static ilv write(ll x)
{
    writ(x); putchar(' ');
}
```

另外记得双倍经验[P10496](https://www.luogu.com.cn/problem/P10496)，别忘了开 ```__int128```，不然有可能被卡掉。

---

## 作者：LostKeyToReach (赞：3)

这道题跟 P10496 几乎一模一样。

我们把原式转换为同余方程：

$$
10^x \equiv 1 \pmod{\frac{9k}{d}}
$$

其中 $d$ 为 $\gcd(k,2)$。

然后我们再枚举 $\varphi(\frac{9k}{d})$ 的因数，用快速幂检查一下即可。

具体的证明方法可以参考我写的[这篇题解](https://www.luogu.com.cn/article/laggyqnq)。

时间复杂度 $O(\sqrt{n}\log n)$。

代码如下：
```cpp
vector <ll> t;
ll phi(ll x) {
	ll ans = x;
	for (int i = 2; i * i <= x; i++) {
		if (x % i == 0) {
			ans = ans * (i - 1) / i;
			while (x % i == 0) x /= i;
		}
	}
	if (x > 1) ans = ans * (x - 1) / x;
	return ans;
}
int main() {
	ll T;
	read(T);
	int cnt = 0;
	ll n;
	while (T--) {
		read(n);
		t.clear();
		n = 9 * n / gcd(n, 2ll);
		if (gcd(n, 10ll) != 1) {
			cout << "-1\n";
		}
		else {
			ll x = phi(n);
			for (ll i = 1; i * i <= x; i++) {
				if (x % i == 0) {
					t.push_back(i);
					if (x / i != i) {
						t.push_back(x / i);
					}
				}
			}
			sort(t.begin(), t.end());
			int i;
			for (i = 0; i < t.size(); i++) {
				if (quick_pow(10ll, t[i], n) == 1) {
					break;
				}
			}
			writeln(t[i]);
		}
	}
}
```

---

## 作者：DX3906_ourstar (赞：1)

Upd 2/12 14:00：感谢 @lcy6 和 @Statax 提供的帮助，现在修正了证明过程中的谬误，去除了代码中一个无用的步骤，更改了 LaTex，同时完善了时间复杂度的描述。

### 题外话

双倍经验：[P10496 The Luckiest Number](https://www.luogu.com.cn/problem/P10496)。

今天白天机房断网了，导致本蒟蒻只能独自死磕 P10496。写的时候实在调红温了，就顺手把证明过程用 LaTex 写在了代码后面。

很巧，看到这道双倍经验还能交题解，证明直接搬过来就行。~~只是当时写的时候精神状态不佳，看起来可能过于松散，望见谅。~~

有什么不懂的地方欢迎私信提问。

废话结束，正片开始。

### 本题的结论推导

设当 $x$ 最小时，$A_x$ 为 $ans$。

由 $ans$ 完全由 $2$ 组成知，$ans$ 可分解为 $2$ 和 $x$ 个 $1$ 组成的数的积。

而由 $x$ 个 $1$ 组成的数可以表示为 $\frac{10^x-1}{9}$（其分子为 $x$ 个 $9$ 组成的数）。

故 $ans=2 \times \frac{10^x-1}{9}$。

由题知 $k \mid ans$，故有 $9k \mid 9ans$。

将 $ans=2 \times \frac{10^x-1}{9}$ 带入，得 $9k \mid 2(10^x-1)$。

令 $m=\gcd{(k,2)}$，左右同乘 $\frac{1}{m}$，得 $\frac{9k}{m} \mid \frac{2(10^x-1)}{m}$。

变形，得 $\frac{9k}{m} \mid (10^x-1)$, 有 $10^x \equiv 1\pmod {\frac{9k}{m}}$。

则题意转化为：求方程 $10^x \equiv 1\pmod{\frac{9k}{m}}$ 的最小正整数解，其中 $m=\gcd{(2,k)}$。

由某玄学结论，$x \mid \varphi(\frac{9k}{m})$。

故可考虑枚举 $\varphi(\frac{9k}{m})$ 的因数，取最小值作为答案。此过程时间复杂度 $O(\sqrt{\varphi(\frac{9k}{m})})$。

考虑到判断过程中需要使用快速幂，总的复杂度应为 $O(\sqrt{n}\cdot \log{n})$。

### 关于上面提到的玄学结论

现在我们证明一下上面的玄学结论（参考《算法进阶指南》）。

采用反证法。假设 $a^x \equiv 1 \pmod n$ 的最小正整数解 $x_0$ 不是 $\varphi(n)$ 的约数。

设 $\varphi(n)=qx_0+r$，其中 $0<r<x_0$。

由 $a^{x_0} \equiv 1\pmod n$，有 $a^{qx_0} \equiv 1\pmod n$。

由欧拉定理，有 $a^{\varphi(n)} \equiv 1\pmod n$，故 $a^r \equiv 1 \pmod n$。

又 $x_0$ 为最小正整数解，矛盾！

故命题得证。

### 最后

有了上面的证明，代码就不难写了。需要注意的是数据类型，快读、快速幂、防爆炸乘法…… 全部都要检查，防止误开 `int` 导致爆炸，进而挂分。

除此之外，我们注意到对于 $\forall n \in \mathbb{N}$，$\varphi(n)$ 都可能计算多次。故可考虑进行记忆化，用 `unordered_map` 存储已计算的欧拉函数值。

附上无注释 [AC](https://www.luogu.com.cn/record/202730448) 代码。代码最后面的大段注释就是当时在 Dev 里手写的 P10496 的证明，懒得删了，这些证明小改一下就适用于本题。

另外别问我为什么 [WA](https://www.luogu.com.cn/record/202657358) 了一发，问就是调的时候加的 `cout<<"ans:";` 忘了注释掉了。

```
#include<iostream>
#include<unordered_map>
#define ll long long
using namespace std;

int q;
unordered_map<ll,ll>mem;

namespace OIfast{
	
	inline ll read(){
		register ll n=0,f=1;
		register char c=getchar();
		while(c<'0'||c>'9'){
			if(c=='-')f=-1;
			c=getchar();
		}
		while(c>='0'&&c<='9'){
			n=(n<<1)+(n<<3)+(c^48);
			c=getchar();
		}
		return n*f;
	}
	
	inline void print(register ll n){
		if(n<0)n=~n+1,putchar('-');
		if(n>=10)print(n/10);
		putchar(n%10^48);
		return ;
	}
	
	inline void write(register ll n,register char c){
		print(n),putchar(c);
		return ;
	}
	
}using namespace OIfast;

namespace numberTheoryTools{
	
	inline ll min(ll a,ll b){
		return a<b?a:b;
	}
	
	inline ll mul(ll a,ll b,ll mod=1e20){
		ll ans=0;
		a%=mod,b%=mod;
		while(b){
			if(b&1)ans=(ans+a)%mod;
			b>>=1;
			a=(a+a)%mod;
		}
		return ans;
	}
	
	ll qpow(ll a,ll b,ll p){
		ll ans=1;
		while(b){
			if(b&1)ans=mul(ans,a,p)%p;
			b>>=1;
			a=mul(a,a,p)%p;
		}
		return ans;
	}
	
	inline ll gcd(ll a,ll b){
		return b!=0?gcd(b,a%b):a;
	}
	
	inline bool hz(ll a,ll b){
		return gcd(a,b)==1;
	}
	
	inline ll phi(ll n){
		if(mem[n])return mem[n];
		ll ans=n;
		for(int i=2;i<=n/i;++i){
			if(n%i==0){
				ans=mul(ans/i,i-1);
				while(n%i==0)n/=i;
			}
		}
		if(n>1)ans=mul(ans/n,n-1);
		mem[n]=ans;
		return ans;
	}
	
}using namespace numberTheoryTools;

inline void work(){
	ll k=read();
	if(k==0)return ;
	ll ans=-1;
	ll m=mul(9,k)/gcd(2,k);
	if(hz(10,m)){
		ll res=phi(m);
		ans=res;
		for(int i=1;i<=res/i;++i){
			if(res%i!=0)continue;
			if(qpow(10,i,m)==1)ans=min(ans,i);
			if(qpow(10,res/i,m)==1)ans=min(ans,res/i);
		}
	}
//	cout<<"ans:";
	write(ans,'\n');
	return ;
}

signed main(){
	q=read();
	while(q--){
		work();
	}
	return 0;
}
/*

答案操作证明：

设最幸运数字为 $ans$,其长度为 $x$。

由 $ans$ 完全由 $8$ 组成知，$ans$ 可分解为 $8$ 和 $x$ 个 $1$ 组成的数的积。

而由 $x$ 个 $1$ 组成的数可以表示为 $\frac{10^x-1}{9}$（其分子为 $x$ 个 $9$ 组成的数）。

故 $ans=8 \times \frac{10^x-1}{9}$。

由题知 $L \mid ans$，故有 $9L \mid 9ans$。

将 $ans=8 \times \frac{10^x-1}{9}$ 带入，得 $9L \mid 8(10^x-1)$。

令 $m=gcd(L,8)$，左右同乘 $\frac{1}{m}$，得 $\frac{9L}{m} \mid \frac{8(10^x-1)}{gcd(L,8)}$。

变形，得 $\frac{9L}{m} \mid (10^x-1)$,有 $10^x \bmod m=1$。

则题意转化为：求方程 $10^x \bmod m=1$ 的最小正整数解，其中 $m=gcd(8,L)$。

由某玄学结论，$x \mid \phi(m)$===========后面证明。

故可考虑枚举 $\phi(m)$ 的因数，取最小值作为答案。此过程时间复杂度 $O(\sqrt{\phi(m)})$。



玄学结论证明（参考《算法进阶指南》）：

采用反证法。假设 $a^x \bmod n=1$ 的最小正整数解 $x_0$ 不是 $\phi(m)$ 的约数。

设 $\phi(n)=qx_0+r$，其中 $0<r<x_0$。

由 $a^{x_0} \bmod n=1$，有 $a{qx_0} \bmod n=1$。

由欧拉定理，有 $a^{\phi(n)} \bmod n=1$，故 $a^r \bmod n=1$。

又 $x_0$ 为最小正整数解，矛盾！

故命题得证。

*/
```

---

## 作者：Lyccrius (赞：1)

$$
\begin{aligned}
    & n \text{个} 2 \\
    = & 2 \times (n \text{个} 1) \\
    = & \frac{2}{9} \times (n \text{个} 9) \\
    = & \frac{2}{9} \times (10^n - 1) \\
    k \vert & \frac{2}{9} \times (10^n - 1) \\
    9k \vert & 2 \times (10^n - 1) \\
\end{aligned}
$$

$$
\begin{aligned}
    2 \times (10^n - 1) & \equiv 0 \pmod{9k} \\
    10^n - 1 & \equiv 0 \pmod{9k} \\
    10^n & \equiv 1 \pmod{9k}
\end{aligned}
$$

这是一个离散对数的形式，可以使用 exBSGS 求解。

请注意，由于 $a^x \equiv b \pmod p$ 中 $b = 1$，直接求解会返回 $0$。而题目要求的是最小正整数解，因此需删除特判。

```cpp
#include <iostream>
#include <map>
#include <cmath>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;
typedef std::map<lxl, lxl> mll;

int t;
lxl k;

lxl pow(lxl a, lxl b, lxl p) {
    lxl ret = 1;
    while (b) {
        if (b & 1) ret = ret * a % p;
        a = a * a % p;
        b = b / 2;
    }
    return ret;
}

lxl gcd(lxl a, lxl b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

lxl exGCD(lxl a, lxl &x, lxl b, lxl &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    lxl d = exGCD(b, y, a % b, x);
    y -= a / b * x;
    return d;
}

lxl BSGS(lxl a, lxl b, lxl p) {
    b = (b % p + p) % p;
    //if (1 % p == b % p) return 0;
    mll hash;
    lxl t = sqrt(p) + 1;
    lxl w = 1;
    for (int i = 0; i < t; i++) hash[b * w % p] = i, w = w * a % p;
    a = pow(a, t, p);
    for (int i = 1; i <= t; i++) {
        lxl x = pow(a, i, p);
        if (hash.find(x) != hash.end()) return i * t - hash[x];
    }
    return -1;
}

lxl exBSGS(lxl a, lxl b, lxl p) {
    b = (b % p + p) % p;
    //if (1 % p == b % p) return 0;
    lxl x, y;
    lxl d = exGCD(a, x, p, y);
    if (d > 1) {
        if (b % d) return -1;
        exGCD(a / d, x, p / d, y);
        return exBSGS(a, b / d * x, p / d) + 1;
    }
    return BSGS(a, b, p);
}

void mian() {
    std::cin >> k;
    if (k % 2 == 0) k /= 2;
    if (gcd(k * 9, 10) != 1) {
        std::cout << -1 << '\n';
        return;
    }
    std::cout << exBSGS(10, 1, 9 * k) << '\n';
    return;
}

int main() {
    promote();
    std::cin >> t;
    while (t--) mian();
    return 0;
}
```


---

## 作者：HirasawaYuii (赞：1)

# [ABC222G] 222 题解

[题目链接](https://www.luogu.com.cn/problem/AT_abc222_g)

## 题目大意

给定一个数字 $L$，求仅由 $2$ 组成的数字且是 $L$ 的倍数的正整数中的最小值的位数。

## 解题思路

对于由 $x$ 位 $2$ 组成的数字，可以将其表示为 $\frac{2}{9}(10^x-1)$，故原题转化为求满足 $L|\frac{2}{9}(10^x-1)$ 的正整数 $x$ 的最小值。

设 $g=\gcd(2,L)$，等式两边同时乘 $9$ 并除以 $g$ 得：$\frac{9L}{g}|(10^x-1)$，由于 $g$ 的因数仅有 $2$（或者根本没有），所以右边 $2(10^x-1)$ 除以 $g$ 后不影响原式结果。

将上式改写为同余式得 $10^x \equiv 1 \pmod {\frac{9L}{g}}$。因为若 $a,n$ 互质，满足 $a^x \equiv 1\pmod n$ 的正整数解最小为 $\phi(n)$ 的约数（证明略），所以可以直接枚举 $\frac{9L}{g}$ 的约数，每个代入进去尝试即可求出答案。

若 $\gcd(10,\frac{9L}{g}) \ne 1$，则无解。

## 复杂度分析

枚举 $\frac{9L}{g}$ 的因数需要 $O(\sqrt L)$ 的时间，内层代入尝试需要快速幂优化，所以总体复杂度为 $O(\sqrt L\log L)$。

## 代码

```c++
// Problem: [ABC222G] 222
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_abc222_g
// Memory Limit: 1 MB
// Time Limit: 2000 ms
// Date: 2025-01-19 21:30:00
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
typedef __int128 ll;
typedef unsigned long long ull;
#define mst(x, y) memset(x, y, sizeof(x))
#define pii pair<ll, ll>
#define fi first
#define se second
#define mp(x, y) make_pair(x, y)
#define pb(x) push_back(x)

ll read(){ll x = 0, f = 1;char c = getchar();while(c < '0' || c > '9'){if(c == '-') f = -1;c = getchar();}while(c >= '0' && c <= '9'){x = 10*x+c-'0';c = getchar();}return f*x;}
void writ(ll x){if(x < 0){putchar('-');x = -x;}if(x > 9) writ(x/10);putchar(x%10 | 0x30);return;}
void write(ll x){writ(x);puts("");}
void wr(ll x){writ(x);putchar(' ');}
const ll inf = 0x3f3f3f3f3f3f3f3f;

ll n, l;

ll gcd(ll x, ll y){
	if(x < y) swap(x, y);
	if(y == 0) return x;
	return gcd(y, x%y);
}
ll phi(ll x){
	ll res = x;
	for(ll i = 2;i*i <= x;i++){
		if(x%i == 0){
			res = res/i*(i-1);
			while(x%i == 0) x /= i;
		}
	}
	if(x > 1) res = res/x*(x-1);
	return res;
}
ll quick_pow(ll x, ll y, ll m){
	ll res = 1, bse = x;
	while(y){
		if(y&1) res = res*bse%m;
		bse = bse*bse%m;
		y /= 2;
	}
	return res;
}
void solve(){
	n = read();
	for(int i = 1;i <= n;i++){
		l = read();
		ll g = 9*l/gcd(9*l, 2);
		ll p = phi(g), ans = inf;
		if(gcd(10, g) != 1){
			write(-1);	
			continue;
		}
		for(ll j = 1;j*j <= p;j++){
			if(p%j) continue;
			if(quick_pow(10, j, g) == 1) ans = min(ans, j);
			if(quick_pow(10, p/j, g) == 1) ans = min(ans, p/j);
		}
		if(ans != inf) write(ans);
	}
}

signed main(){
	solve();
	return 0; 
}
```



最后不要忘了[双倍经验](https://www.luogu.com.cn/problem/P10496)

---

## 作者：block_in_mc (赞：1)

## 解题思路

由 $x$ 个 $2$ 构成的正整数为 $\dfrac{2\times(10^x-1)}{9}$，答案即为满足 $L\mid\dfrac{2\times(10^x-1)}{9}$ 的最小正整数 $x$，即

$$9L\mid2\times(10^x-1)$$

设 $d=\gcd(L,2)$，则有

$$\dfrac{9L}{d}\mid10^x-1$$

为什么呢？先考虑 $d=1$ 即 $L$ 与 $2$ 互质的情况，这时右侧的 $2$ 对这个 $9L$ 能被 $2\times(10^x-1)$ 整除没有贡献，因此可以直接删去。一般地，右侧的 $2$ 对这个式子做出了 $d$ 的贡献，因此想要删除右侧的 $2$，左侧要除以 $d$。

将其转化为同余方程即

$$10^x-1\equiv0\pmod{\dfrac{9L}{d}}$$

即

$$10^x\equiv1\pmod{\dfrac{9L}{d}}$$

只需找到满足这个式子的最小的正整数 $x$ 即可。

> 先证明一个引理：若正整数 $a,n$ 互质，则满足 $a^x\equiv1\pmod{n}$ 的最小正整数 $x_0$ 是 $\varphi(n)$ 的约数。
>
> 考虑反证法。假设满足 $a^x\equiv1\pmod{n}$ 的最小正整数 $x_0$ 不是 $\varphi(n)$ 的约数，则 $x_0$ 可以表示为 $qx_0+r$ 的形式，其中 $0<r<x_0$。
> 
> 由于 $1^q=1$，可以推出
> 
> $$(a^x)^q\equiv1\pmod{n}$$
> 
> 根据欧拉定理，又有
> 
> $$a^{\varphi(n)}\equiv1\pmod{n}$$
> 
> 两式相除可以得到
> 
> $$a^r\equiv1\pmod{n}$$
> 
> 由于 $r<x_0$，与 $x_0$ 的最小性矛盾，结论成立。

因此，我们可以从小到大枚举 $\dfrac{9L}{d}$ 的每一个因数 $x$，并通过快速幂计算 $10^x\bmod\dfrac{9L}{d}$ 的值是否为 $1$ 判断 $x$ 是否合法。

## AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll t, n, k, phi, ans;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll fpow(ll a, ll b, ll p) {
	if (b == 0) return 1;
	ll tmp = fpow(a, b / 2, p);
	if (b % 2 == 0) return tmp * tmp % p;
	else return a * (tmp * tmp % p) % p;
}
void calc(ll p) {
	phi = p;
	for (int i = 2; i * i <= p; i++) {
		if (p % i == 0) {
			while (p % i == 0) p /= i;
			phi = phi * (i - 1) / i;
		}
	}
	if (p != 1) phi = phi * (p - 1) / p;
}
int main() {
	scanf("%lld", &t);
	while (t--) {
		scanf("%lld", &n);
		if (n == 0) break;
		k = 9 * n / gcd(2, n), ans = -1;
		calc(k);
		for (int i = 1; i * i <= phi; i++)
			if (ans == -1 && phi % i == 0 && fpow(10, i, k) == 1)
				ans = i;
		int m = sqrt(phi);
		for (int i = m; i >= 1; i--) 
			if (ans == -1 && phi % i == 0 && fpow(10, phi / i, k) == 1)
				ans = phi / i;
		printf("%lld\n", ans);
	}
    return 0;
}
```

---

## 作者：fjy666 (赞：1)

题意：给定一个 $k$，求最小的 $i$ 满足 $k\mid 22......222$（共 $i$ 个 $2$）  
首先当 $2|k$ 的时候令 $k\gets \dfrac{k}{2}$，  
然后原式化为 $k\mid 11....1$。  
我们来推一推式子。

$$
\begin{aligned}
k&\mid11.......11 \\
9k&\mid 99.......99 \\
9k&\mid 10^i-1
\end{aligned}
$$

相当于求一个 $i$ 满足 $10^i\equiv1(\bmod\ 9k)$  
**Key Observation**：当 $\gcd(10,9k)\neq 1$  时，必定无解。  
证明：
> 反证法。当 $\gcd(10,9k)\neq 1$ 时  
> $\because \gcd(10, 9k)\neq1 \therefore\gcd(10^i,9k)\neq1$  
> $\therefore\gcd(10^i\bmod9k,9k)\neq1$  
> $\because 10^i=1\bmod9k \therefore\gcd(10^i\bmod9k,9k)=\gcd(9k,1)=1$  
> 矛盾！

当 $\gcd(10,9k)=1$ 时，使用 BSGS 即可。

---

## 作者：irris (赞：1)

## Preface

xf 笑转之 code code brute。

## Solution

考虑先写出「$n$ 个 $2$ 构成的十进制数字」这一结构的通项：$\frac{2}{9}(10^n - 1)$。令 $k \leftarrow 9\times k$，那么其实就是求解 $k \mid 2\times(10^n - 1)$ 的最小正整数解。

这里把 $\times 2$ 去掉：如果 $2 \mid k$，那么再令 $k \leftarrow \frac{1}{2}\times k$；于是就只需要求满足 $10^n \equiv 1 \pmod k$ 的最小正整数解。

如果 $\gcd(10, k) \neq 1$，不可能合法，否则跑 BSGS 即可。~~也可以选择枚举 $\sout{\varphi(k)}$ 的所有因子，用光速幂 check~~。

---

## 作者：AKPC (赞：0)

给出 $k$，求

$$k\mid\underbrace{22222\dots}_{\text{x times}}$$

的最小 $x$，无解输出 $-1$。

首先，因为 $\underbrace{99999\dots}_{\text{x times}}=10^x-1$，所以可以将 $\underbrace{22222\dots}_{\text{x times}}$ 转化为 $\dfrac{2}{9}\times(10^x-1)$，故式子转化为

$$k\mid\dfrac{2}{9}\times(10^x-1)$$

将 $\dfrac{1}{9}$ 移项可以变为

$$9k\mid2\times(10^x-1)$$

而可以再把式子变为

$$\dfrac{9k}{\gcd(2,k)}\mid(10^x-1)$$

对上一步的解释：分类讨论，当 $2\mid k$，则这样变化相当于把两边同时除以 $2$；当 $2\nmid k$，则这样变化相当于把右边乘的 $2$ 去掉，去掉后显然没有影响。

把这个式子转变成同余式

$$10^x\equiv1\pmod{\dfrac{9k}{\gcd(2,k)}}$$

根据欧拉定理：

>对于整数 $a$ 和正整数 $p$，如果 $\gcd(a,p)=1$，则 $a^{\operatorname{\varphi}(p)}=1\pmod p$。

可以推导得到 $x\mid\operatorname{\varphi}(\dfrac{9k}{\gcd(2,k)})$。

所以可以枚举 $\operatorname{\varphi}(\dfrac{9k}{\gcd(2,k)})$ 的所有因子 $x$ 然后判断 $10^x\equiv1\pmod{\dfrac{9k}{\gcd(2,k)}}$ 的成立与否，把成立的取个最小值即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define fr first
#define sc second
int qpow(int a,int b,int p){
	int res=1;
	while (b){
		if (b&1) res=res*a%p;
		a=a*a%p,b>>=1;
	}
	return res;
}
int getphi(int x){
    int rs=x;
    for (int i=2;i*i<=x;i++){
        if (x%i==0) rs=rs/i*(i-1);
        while (x%i==0) x/=i;
    }
    if (x>1) rs=rs/x*(x-1);
    return rs;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int T;
    cin>>T;
    while (T--){
        int k,n,ans=1e18,phi_n;
        cin>>k,n=9*k/__gcd(2ll,k);
        phi_n=getphi(n);
        for (int i=1;i*i<=phi_n;i++){
            if (phi_n%i!=0) continue;
            if (qpow(10,i,n)==1) ans=min(ans,i);
            if (qpow(10,phi_n/i,n)==1) ans=min(ans,phi_n/i);
        }
        if (ans==1e18) cout<<"-1\n";
        else cout<<ans<<'\n';
    }
    return 0;
}
```

---

## 作者：lxy0507 (赞：0)

本题关键是将问题转化为 $9n \mid 2\times(10^{k}-1)$，求 $k$ 的最小值。$\\$
在数论中我们将这样的最小的 $k$ 称为阶。由欧拉定理，在 $\gcd(10,n)=1$ 时 $n\mid10^{(\varphi (n))} -1$，那么由阶的性质知 $k\mid\varphi (9n)$。$\\$
对这个题而言，我们可以先通过 $\varphi (n)$ 的表达式计算出 $\varphi (9n)$，再对不超过 $\sqrt{\varphi(9n)}$ 的数 $m$ 依次判断其是否能整除 $\varphi (9n)$，并检查 $m$ 和 $\frac{\varphi (9n)}{m}$ 是否符合要求，找出最小的那个满足条件的即可。

---


什么？你问 $10^{k}$ 怎么算比较快？那当然是快速幂啊。[乐]


---

以下代码实现，时间复杂度 $O(T\sqrt{K}\log{K}  )$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 1000015
using namespace std;
int t;
ll pri[N],vis[N],ddd;

void get_prime(ll n){//线性筛素数
	for(int i=2;i<=n;i++){
		if(!vis[i]){
			vis[i]=i;
			pri[++ddd]=i;
		}
		for(int j=1;j<=ddd;j++){
			if(pri[j]>vis[i]||pri[j]>n/i)break;
			vis[i*pri[j]]=pri[j];
		}
	}
}

ll phi(ll x){//计算φ(x)的值
	ll ans=1;
	for(ll i=1;i<=ddd&&pri[i]<=x;i++){
		if(x%pri[i]==0){
			ans*=(pri[i]-1);
			x=x/pri[i];
		}
		while(x%pri[i]==0){
			x=x/pri[i];
			ans*=pri[i];
		}
	}
	if(x!=1){//当前面的素数筛完之后，如果剩下的不为1，则剩下的一定是个大素数，直接乘便可
		ans*=(x-1);
	}
	return ans;
}

ll ppo(ll k,ll mod){//快速幂
	ll ans=1,a=10;
	while(k){
		if(k&1){
			ans=ans*a%mod;
		}
		a=a*a%mod,k>>=1;
	}
	return ans;
}

ll get(ll n){
	ll ans=0;
	if(n%4==0||n%5==0)return -1;//先特判(n,10)≠1的情形
	while(n%2==0)n>>=1;//划归为(n,10)=1的模式
	ll m=phi(9*n);
	ll pow3=1;
	while(n%3==0){
		n=n/3;
		pow3*=3;
	}
	if(n==1){
		return pow3;
	}
	for(ll i=1;i<=sqrt(m);i++){
		if(i%pow3!=0||m%i!=0)continue;
		if(ppo(i,n)==1){
			ans=i;
			break;
		}
	}
	if(!ans){
		for(ll i=sqrt(m);i>=1;i--){//一定是从小往大，这里注意顺序
			if(m%i!=0)continue;
			if((m/i)%pow3!=0)continue;
			if(ppo(m/i,n)==1){
				ans=m/i;
				break;
			}
		}
	}
	return ans;
}

int main(){
	get_prime(N-5);//先将需要的素数筛出
	cin>>t;
	for(int i=1;i<=t;i++){
		ll n;
		cin>>n;
		cout<<get(n)<<endl;
	}
}
```

---

## 作者：wflhx2011 (赞：0)

### 前言

从[P10496](https://www.luogu.com.cn/problem/P10496)传过来的。这题除了数字变了其余都一样，所以证明也是来自蓝书。

## Solution

是 $k$ 的倍数，即对 $k$ 取余的模数为 $0$。

于是问题出在仅由数字 $2$ 构成，考虑将其换一种形式表示，不难发现 $22......22=2 \times 11......11=2 \times \frac{10^n-1}{9}$。原问题就变为求一个最小的正整数 $n$ 使  $2\times\frac{10^n-1}{9} \bmod k=0$。

出现乘方，考虑用欧拉定理，先对原式进行变形，可化为 $10^n \equiv 1 \pmod {\frac{9\times k}{\gcd(2,k)}}$。

欧拉定理：若 $a,p$ 互质，则 $a^{\phi(p)} \equiv 1 \pmod p$。于是考虑，使 $a^n \equiv 1 \pmod p$ 最小的 $n$ 是否与 $\phi(p)$ 有关系呢？

一个较为显然的思路是 $n$ 是 $\phi(p)$ 的因数，这样 $a^{\phi(p)}=a^{n^{\phi(p)/n}}$，在模 $p$ 意义下就是 $1=1^{\phi(p)/n}$。

那能否对此进行严谨证明呢？

证明（以下内容摘自李煜东《算法竞赛进阶指南》）：

反证法。假设满足 $a^n \equiv 1 \pmod p$ 的最小正整数 $n$ 不能整除 $\phi(p)$。

设 $\phi(p)=q \times n+r (0<r<n)$，因为 $a^n \equiv 1 \pmod p$，所以 $a^{q \times n} \equiv 1 \pmod p$。根据欧拉定理，$a^{\phi(p)} \equiv 1 \pmod p$，则 $a^r \equiv 1 \pmod p$。因为 $r<n$，这与 $n$ 为最小正整数解矛盾。故假设不成立，原命题成立。

证毕。

回到原题，设 $p={\frac{9\times k}{\gcd(2,k)}}$，我们就可以求出 $\phi(p)$，之后暴力枚举因数。

无解的情况显然是 $10,p$ 不互质，但也不需要特判。

时间复杂度对于一组数据是 $O(\sqrt n \log n)$。

### 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
long long euler(long long n)
{
	long long ans=n;
	for(int i=2;i*i<=n;i++)
	{
		if(n%i==0)
		{
			ans=ans/i*(i-1);
			while(n%i==0)
				n/=i;
		}
	}
	if(n>1)
		ans=ans/n*(n-1);
	return ans;
}
__int128 ksm(__int128 a,__int128 b,__int128 mo)
{
	__int128 res=1;
	while(b)
	{
		if(b&1)
			res=res*a%mo;
		a=a*a%mo;
		b>>=1;
	}
	return res%mo;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	while(t--)
	{
		long long l;
		cin>>l;
		long long ans=1e18; 
		long long d=9*l/__gcd(l,2ll);
		long long k=euler(d);
		for(long long i=1;i*i<=k;i++)
		{
			if(k%i==0)
			{
				__int128 f=ksm(10,i,d);
				if(f%d==1)
					ans=min(ans,i);
			}
			if(k%(k/i)==0)
			{
				__int128 f=ksm(10,k/i,d);
				if(f%d==1)
					ans=min(ans,k/i);
			}	
		}
		printf("%d\n",ans==1e18?-1:ans);
	} 
	return 0;
}
```

---

