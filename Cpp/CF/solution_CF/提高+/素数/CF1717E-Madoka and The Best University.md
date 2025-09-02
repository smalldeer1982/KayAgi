# Madoka and The Best University

## 题目描述

Madoka wants to enter to "Novosibirsk State University", but in the entrance exam she came across a very difficult task:

Given an integer $ n $ , it is required to calculate $ \sum{\operatorname{lcm}(c, \gcd(a, b))} $ , for all triples of positive integers $ (a, b, c) $ , where $ a + b + c = n $ .

In this problem $ \gcd(x, y) $ denotes the [greatest common divisor](https://en.wikipedia.org/wiki/Greatest_common_divisor) of $ x $ and $ y $ , and $ \operatorname{lcm}(x, y) $ denotes the [least common multiple](https://en.wikipedia.org/wiki/Least_common_multiple) of $ x $ and $ y $ .

Solve this problem for Madoka and help her to enter to the best university!

## 说明/提示

In the first example, there is only one suitable triple $ (1, 1, 1) $ . So the answer is $ \operatorname{lcm}(1, \gcd(1, 1)) = \operatorname{lcm}(1, 1) = 1 $ .

In the second example, $ \operatorname{lcm}(1, \gcd(3, 1)) + \operatorname{lcm}(1, \gcd(2, 2)) + \operatorname{lcm}(1, \gcd(1, 3)) + \operatorname{lcm}(2, \gcd(2, 1)) + \operatorname{lcm}(2, \gcd(1, 2)) + \operatorname{lcm}(3, \gcd(1, 1)) = \operatorname{lcm}(1, 1) + \operatorname{lcm}(1, 2) + \operatorname{lcm}(1, 1) + \operatorname{lcm}(2, 1) + \operatorname{lcm}(2, 1) + \operatorname{lcm}(3, 1) = 1 + 2 + 1 + 2 + 2 + 3 = 11 $

## 样例 #1

### 输入

```
3```

### 输出

```
1```

## 样例 #2

### 输入

```
5```

### 输出

```
11```

## 样例 #3

### 输入

```
69228```

### 输出

```
778304278```

# 题解

## 作者：Hovery (赞：13)

# Problem

[Madoka and The Best University](https://www.luogu.com.cn/problem/CF1717E)

# Sol

先枚举 $\gcd$，再枚举 $a + b$ 是 $\gcd$ 的几倍。

>这里讲一下为什么枚举 $\gcd$ 。

>首先，枚举 $\gcd$ 可以枚举 $a + b$ 的值，这样也确定了 $c$ 的值，并且也可以计算出答案。

设是 $x$ 倍，那么问题就变成了将 $x$ 分成两个数，使得这两个数互质。（因为两个数的 $\gcd$ 必须是枚举的那个数）

（下文的 $a$，$b$与上面不同）

考虑一个数 $q$ ，另一个数是 $x - q$。

如果 $q$ 和 $x$ 不互质。

设 $\gcd(q,x) = p$。

就有 $q = a \times p,x = b\times p $。

由于 $q$ 比 $x$ 小，$a$ 必然小于 $b$。

所以 $x - q = (a - b) \times p$ 。

那么就不满足 $q$ 与 $x - q$ 互质。

所以 $q$ 只能与 $x$ 互质。

那么我们就要求出与 $x$ 互质的有多少个数，这个东西可以用[欧拉函数](https://oi-wiki.org/math/number-theory/euler/)做。

# Code

```
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define pb push_back
using namespace std;

void read(int &x)
{
	char ch;
	int w = x = 0;
	ch = getchar();
	for (;!isdigit(ch);ch = getchar())
	w ^= (ch == 45);
	for (;isdigit(ch);ch = getchar())
	x = x * 10 + (ch ^ 48);
	x = w ? -x : x;
}

const int mod = 1e9 + 7;

int n, f[200000], ans, vis[200000], sum[200000], cnt, p[200000];

void make_prime()
{
	vis[1] = 1;
	for (int i = 2; i < n; i++)
	{
		if (!vis[i])
		{
			p[++cnt] = i;
			sum[i] = i - 1;
		}
		for (int j = 1; j <= cnt && p[j] * i < n; j++)
		{
			vis[p[j] * i] = 1;
			if (i % p[j] == 0)
			{
				sum[i * p[j]] = sum[i] * p[j];
				break;
			}
			sum[i * p[j]] = sum[i] * (p[j] - 1);
		}
	}
}

void solve()
{
	cin >> n;
	make_prime();
	for (int i = 1;i < n;i++)
	{
		for (int j = 2;j * i < n;j++)
		{
			int c = n - i * j, lcm = (c / __gcd(c, i) * i) % mod;
			(ans += sum[j] * lcm % mod) %= mod;
		}
	}
    cout << ans << endl;
}

signed main()
{
	IOS;
	int t = 1;
	// cin >> t;
	while (t--)
	{
		solve();
	}
}
```

---

## 作者：I_am_Accepted (赞：9)

真正的 $O(n)$ 线性做法。

先来 dirty work：
$$
\begin{aligned}
&\sum_{c=1}^{n-2}\sum_{a=1}^{n-c-1}\text{lcm}(c,\gcd(a,n-c-a))
\\=& \sum_{c=1}^{n-2}\sum_{a=1}^{n-c-1}\text{lcm}(c,\gcd(a,n-c))
\\=& \sum_{c=1}^{n-2}\sum_{d=1}^{n}\sum_{a=1}^{n-c-1}[\gcd(a,n-c)=d]\text{lcm}(c,d)
\\=& \sum_{c=1}^{n-2}\sum_{d=1}^{n}[d|n-c]\text{lcm}(c,d)\sum_{a=1}^{\lfloor\frac{n-c-1}{d}\rfloor}[\gcd(a,\frac{n-c}{d})=1]
\\=& \sum_{c=1}^{n-2}\sum_{d=1}^{n}[d|n-c]\text{lcm}(c,d)\varphi(\frac{n-c}{d})[\frac{n-c}{d}>1]
\\=& \sum_{c=2}^{n}\sum_{d=1}^{n}[d|c]\text{lcm}(n-c,d)\varphi(\frac{c}{d})[\frac{c}{d}>1]
\\=& \sum_{d=1}^{n}\sum_{c=2}^{\lfloor\frac{n}{d}\rfloor}\text{lcm}(n-cd,d)\varphi(c)
\\=& \sum_{c=2}^{n}\varphi(c)\sum_{d=1}^{\lfloor\frac{n}{c}\rfloor}\text{lcm}(n-cd,d)
\\=& \sum_{i=2}^{n}\varphi(i)\sum_{j=1}^{\lfloor\frac{n}{i}\rfloor}\frac{j(n-ij)}{\gcd(n-ij,j)}
\\=& \sum_{i=2}^{n}\varphi(i)\left(\sum_{j=1}^{\lfloor\frac{n}{i}\rfloor}\text{lcm}(n,j)-i\sum_{j=1}^{\lfloor\frac{n}{i}\rfloor}\frac{j^2}{\gcd(n,j)}\right)
\end{aligned}
$$
不妨设
$$
S(x)=\sum_{i=1}^{x}\text{lcm}(n,i)\quad T(x)=\sum_{i=1}^{x}\frac{i^2}{\gcd(n,i)}
$$
则最终结果为
$$
\sum_{i=2}^{n}\varphi(i)\left(S(\lfloor\frac{n}{i}\rfloor)-i\cdot T(\lfloor\frac{n}{i}\rfloor)\right)
$$

先线性筛出 $\varphi(x),mp(x)$（$mp$ 为最小素因子），就可以线性求出 $\gcd(n,x),S(x),T(x)$，再 $O(n)$ 求得最终答案。

```cpp
/*
* Author: ShaoJia
* Last Modified time: 2022-09-03 12:26:17
* Motto: We'int be counting stars.
*/
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define For(i,j,k) for(int i=(j),i##_=(k);i<=i##_;i++)
#define Rof(i,j,k) for(int i=(j),i##_=(k);i>=i##_;i--)
#define int long long
const int mod=1e9+7;
inline int pw(int x,int y){int r=1;while(y){if(y&1)r=r*x%mod;x=x*x%mod;y>>=1;}return r;}
#define N 100010
int s[N],t[N],phi[N],n,g[N],mp[N],f[N],ivf[N],p[N],pt=0;
bool vis[N];
signed main(){ios::sync_with_stdio(false),cin.tie(nullptr);
	cin>>n;
	f[0]=1; For(i,1,n) f[i]=f[i-1]*i%mod;
	ivf[n]=pw(f[n],mod-2); Rof(i,n,1) ivf[i-1]=ivf[i]*i%mod;
	phi[1]=1;
	int x;
	For(i,2,n){
		if(!vis[i]){
			p[++pt]=i;
			phi[i]=i-1;
			mp[i]=i;
		}
		For(j,1,pt){
			x=p[j];
			if(i*x>n) break;
			vis[i*x]=1;
			mp[i*x]=x;
			if(i%x){
				phi[i*x]=phi[i]*(x-1);
			}else{
				phi[i*x]=phi[i]*x;
				break;
			}
		}
	}
	g[1]=1;
	For(i,2,n){
		g[i]=g[i/mp[i]];
		if(n%(g[i]*mp[i])==0) g[i]*=mp[i];
	}
	For(i,1,n) s[i]=(s[i-1]+n/g[i]*i)%mod;
	For(i,1,n) t[i]=(t[i-1]+i*i%mod*ivf[g[i]]%mod*f[g[i]-1])%mod;
	int ans=0;
	For(i,2,n) (ans+=(s[n/i]-i%mod*t[n/i]%mod+mod)%mod*phi[i])%=mod;
	cout<<ans<<endl;
return 0;}
```

---

## 作者：Eafoo (赞：8)

首先化式子：

$$
\begin{aligned}
 & \sum \operatorname{lcm}(c, \gcd(a, b)) \\
= & \sum \frac{c \cdot \gcd(a, b)}{\gcd(c, \gcd(a, b))} \\
= & \sum \frac{c \cdot \gcd(a, b)}{\gcd(a, b, c)} \\
= & \sum \frac{(n - a - b) \cdot \gcd(a, b)}{\gcd(a, b, n - a - b)} \\
= & \sum \frac{(n - a - b) \cdot \gcd(a, b)}{\gcd(a, b, n)} \\
\end{aligned}
$$

设 $s = a + b$，$d = \gcd(a, b)$，则显然有 $d|s$。

我们尝试从 $1$ 到 $n$ 枚举 $d$，再枚举 $d$ 的倍数作为 $s$，这一部分的复杂度为 $O(n \log n)$。

此时我们发现只需要算出 $\gcd(a, b) = d$ 且 $a + b = s$ 的 $a$ 与 $b$ 的合法方案数即可。

设 $a' = \frac{a}{d}$， $b' = \frac{b}{d}$，$s' = \frac{s}{d}$，则方案数可表示为：

$$
\begin{aligned}
& \sum_{a' = 1}^{s'} [\gcd(a', b') = 1] \\
= & \sum_{a' = 1}^{s'} [\gcd(a', s' - a') = 1] \\
= & \sum_{a' = 1}^{s'} [\gcd(a', s') = 1] \\
= & φ(s') = φ(\frac{s}{d})
\end{aligned}
$$

因此当枚举一个 $s$ 和 $d$ 时，它们对答案的贡献为：

$$\frac{(n - s) \cdot d}{\gcd(n, d)} \cdot φ(\frac{s}{d})$$

注意取值范围 $d \in [1, n]$，$s \in [2d, \lfloor\frac{n}{d}\rfloor \cdot d]$ 且 $s | d$，线性欧拉筛求欧拉函数即可。

```cpp
#include <bits/stdc++.h>
#define ff fflush(stdout)
#define fop(x, l, r) for (int x = l; x <= r; ++x)
#define pof(x, r, l) for (int x = r; x >= l; --x)
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
int read() {
    int x = 0; char c; bool f = 0;
    while (!isdigit(c = getchar())) if (c == '-') f = 1;
    do x = (x << 1) + (x << 3) + (c ^ 48); while (isdigit(c = getchar()));
    return f ? -x : x;
}

const int maxn = 1e5 + 3;

int phi[maxn], prime[maxn], cnt;
bool vis[maxn];

void Euler(int n) {
    phi[1] = 1;
    fop(i, 2, n) {
        if (!vis[i]) prime[++cnt] = i, phi[i] = i - 1;
        for (int j = 1; j <= cnt && i * prime[j] <= n; ++j) {
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) { phi[i * prime[j]] = phi[i] * prime[j]; break; }
            phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        }
    }
}

signed main() {
    int n = read();
    Euler(n);
    int ans = 0;
    fop(d, 1, n) for (int s = 2 * d; s <= n; s += d) {
        ans += (n - s) * d / __gcd(n, d) * phi[s / d] % mod;
        if (ans >= mod) ans -= mod;
    }
    printf("%d\n", ans);
}
```


---

## 作者：Resolute_Faith (赞：3)

看见三元组不难先思考可不可以枚举其中的一个数。观察到 $c$ 比较特殊，所以我们不妨用 $i$ 枚举 $c$，接下来思考 $\gcd(a,b)$ 应该如何处理。

显然相同的 $\gcd(a,b)$ 得到的答案也相同，所以可以试着求出每一种 $\gcd(a,b)$ 的方案数。接下来考虑 $\gcd(a,b)$ 究竟有多少种，如果 $a,b$ 互质，那么 $\gcd(a,b)=1$；如果不互质，则设 $p=\gcd(a,b)$，有 $a+b=n-i=kp$，也就是说 $\gcd(a,b)$ 一定会是 $n-i$ 的每个因数。

将问题转化为求 $\operatorname{lcm}(i,k)\times t$，其中 $k$ 表示 $n-i$ 的每个因数，这是可以在 $\mathcal{O}(n\sqrt{n})$ 内完成的任务。这样枚举因数只会枚举一半，但是另一半可以同时处理。但现在问题来到解决 $t$ 上。

$t$ 的意思是满足 $x+y=\dfrac{n-i}{k}$ 且 $\gcd(x,y)=1$ 的方案数。我们单独处理这个问题，用 $d$ 代换 $\dfrac{n-i}{k}$，直接找 $x+y=d$ 且 $\gcd(x,y)=1$ 的规律即可。如果 $x$ 与 $y$ 满足 $\gcd(x,y)\neq 1$，那么 $\exists k$ 使得 $d=k\gcd(x,y)$（乘法分配律）。对于一种 $\gcd(x,y)$，满足 $p\gcd(x,y)+q\gcd(x,y)=d$ 的一定都不符合条件，所以对于任意的 $j$，如果 $\gcd(j,d)\neq 1$，则 $(j,d-j)$ 一定不符合条件。

发现了吗，$x+y=d$ 且 $\gcd(x,y)=1$ 的答案其实就是 $\varphi(d)$，这个玩意可以用线筛提前预处理，并且 $\mathcal{O}(1)$ 得到答案。求欧拉函数的方式不细说了，大家可以去看 [P2158 [SDOI2008] 仪仗队](https://www.luogu.com.cn/problem/P2158)。

经过上面的思考后可以得到以下柿子：

$$
ans=\sum\limits_{i=1}^{n-2}\sum\limits_{j\mid n-i}^{j^2\leqslant n-i}\left[\operatorname{lcm}(i,j)\times\varphi\left(\dfrac{n-i}{j}\right)+\operatorname{lcm}\left(i,\dfrac{n-i}{j}\right)\times\varphi(j)\times[j^2\neq n-i\;\text{and}\;j\neq 1]\right]
$$

可以轻松求解，$\operatorname{lcm}$ 可以用 $\dfrac{ab}{\gcd(a,b)}$ 的方式解决，可以在此基础上使用逆元，欧拉函数线筛解决，总时间复杂度应该是 $\mathcal{O}(n\sqrt{n}\log n)$，可以通过。

```cpp
//E
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int phi[N];
void euler(int x){
    for(register int i=2;i<=x;i++) phi[i]=0;
    phi[1]=1;
    for(register int i=2;i<=x;i++){
        if(phi[i]==0){
            for(register int j=i;j<=x;j+=i){
                if(phi[j]==0) phi[j]=j;
                phi[j]=phi[j]/i*(i-1);
            }
        }
    }
}
int lcm(int a,int b){return a/(__gcd(a,b))*b;}
signed main(){
    int n=read(),ans=0;
    euler(n);
    for(register int i=1;i<=n-2;i++){
        int j=n-i;
        for(register int k=1;k*k<=j;k++){
            if(j%k==0){
                int a=k;
                int b=j/k;
                ans=(ans+(lcm(i,a)%mod*phi[b]%mod)%mod)%mod;
                if(k*k!=j&&k!=1) ans=(ans+(lcm(i,b)%mod*phi[a]%mod)%mod)%mod;
            }
        }
    }
    printf("%lld",ans);
}
```

---

## 作者：DaiRuiChen007 (赞：2)

# CF1717E 题解

2022.09.08 更新了一处笔误

## 思路分析

$$
\begin{aligned}
\text{Answer}
&=\sum_{c=1}^{n-1} \sum_{a=1}^{n-c-1} \operatorname{lcm}(c,\gcd(a,n-a-c))\\
&=\sum_{c=1}^{n-1} \sum_{a=1}^{n-c-1} \operatorname{lcm}(c,\gcd(a,n-c))\\
&=\sum_{c=1}^{n-1} \sum_{d\mid n-c}^{d\neq n-c} \operatorname{lcm}(c,d)\sum_{a=1}^{n-c-1} \left[\gcd\left(a,\dfrac{n-c}d\right)=1\right]\\
&=\sum_{c=1}^{n-1} \sum_{d\mid n-c}^{d\neq n-c} \operatorname{lcm}(c,d)\varphi\left(\dfrac {n-c}{d}\right)
\end{aligned}
$$

直接计算，复杂度 $\Theta(n\log n)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
const int MAXN=1e5+1,MOD=1e9+7;
using namespace std;
int phi[MAXN];
bool tag[MAXN];
vector <int> p,factor[MAXN];
inline int lcm(int a,int b) { return a/__gcd(a,b)*b; }
inline void init() {
	phi[1]=0;
	for(int i=2;i<MAXN;++i) {
		if(!tag[i]) p.push_back(i),phi[i]=i-1;
		for(int x:p)  {
			if(x*i>=MAXN) break;
			tag[x*i]=true;
			if(i%x==0) {
				phi[x*i]=x*phi[i];
				break;
			} else phi[x*i]=(x-1)*phi[i];
		}
	}
	for(int i=1;i<MAXN;++i) {
		for(int j=i;j<MAXN;j+=i) {
			factor[j].push_back(i);
		} 
	}
} 
signed main() {
	init(); 
	int n,res=0;
	scanf("%lld",&n);
	for(int i=1;i<=n-2;++i) {
		int x=n-i;
		for(int d:factor[x]) res=(lcm(i,d)%MOD*phi[x/d]%MOD+res)%MOD;
	}
	printf("%lld\n",res);
	return 0;
}
```



---

## 作者：whhsteven (赞：1)

枚举 $a + b$，则 $c = n - (a + b)$。

$\gcd(a, b)$ 一定是 $a + b$ 的因数，所以接下来枚举 $a + b$ 的每一个因数，计算其作为 $\gcd(a, b)$ 的贡献。

易见，$d | (a + b)$ 作为 $\gcd(a, b)$ 对答案的贡献次数，为满足 $a^\prime \perp b^\prime$ 且 $a^\prime + b^\prime = \frac{a + b}{d}$ 的有序正整数对 $(a^\prime, b^\prime)$ 的数目。

由更相减损术可知 $\gcd(a + b, b) = \gcd(a, b)$，故 $\gcd\left(\frac{a + b}{d}, b^\prime\right) = \gcd(a^\prime + b^\prime, b^\prime) = \gcd(a^\prime, b^\prime) = 1$。由此可知，有序正整数对 $(a^\prime, b^\prime)$ 满足 $a^\prime \perp b^\prime$ 且 $a^\prime + b^\prime = \frac{a + b}{d}$，当且仅当 $\frac{a + b}{d} \perp b^\prime$ 且 $a^\prime + b^\prime = \frac{a + b}{d}$。

从而，这样的正整数对数目，即为小于 $\frac{a + b}{d}$ 且与之互质的正整数数目。易见这就是 $1$ 处取值修改为 $0$ 的欧拉函数在 $\frac{a + b}{d}$ 处的值。

定义

$$f(n) = \begin{cases}0 & (n=1) \\ \varphi(n) & (n \not= 1)\end{cases}$$

$f$ 可以用筛法预处理出来。

则最终我们有

$$\sum_{a+b+c=n}\operatorname{lcm}(c,\gcd(a,b)) = \sum_{s=2}^{n-1}\sum_{d|s}f\left(\frac{s}{d}\right)\operatorname{lcm}(n-s,d)$$

若用枚举范围内每一个因数的所有倍数的方式预处理出每一个数的所有因数，时间复杂度为 $O(n\log n)$；若直接 $O(\sqrt n)$ 枚举因数，则时间复杂度为 $O(n\sqrt n)$。均可以通过。

---

## 作者：SUNCHAOYI (赞：1)

看到题目，有三个变量，首先想到消参。由辗转相减法可知 $\gcd (a,b) = \gcd (a,a + b)$，又因为 $a + b + c = n$，所以 $a + b = n - c$，即 $\gcd (a,b) = \gcd (a,n - c)$。

令 $g = \gcd (a,n - c)$，将题目所求进行转化，则有 $\sum \mathrm{lcm} (c,\gcd (a,b)) = \sum \mathrm{lcm} (c,\gcd (a,n - c))$。枚举 $c,g$，不难发现答案与 $a$ 的大小无直接联系，只与符合条件的 $a$ 的个数有关。由 $\gcd$ 的定义可知，$\gcd (\frac{a}{g},\frac{n - c}{g}) = 1$，也就是说符合条件的 $a$  满足 $\frac{a}{g}\perp\frac{n - c}{g}$，不难想到欧拉函数 $\varphi(x)$ 表示与 $x$ 互质的数的个数。于是答案就变为 $\sum \limits_{g \mid n - c}\mathrm{lcm} (c,g) \times \varphi(\frac{n - c}{g})$，预处理欧拉函数便可解决问题。

但是在编写代码的时候还需要注意一些细节，$a,b,c$ 都是正整数，所以枚举的时候 $c \in [1,n - 2]$，枚举因数的时候要满足 $a < n - c = a + b$，所以 $a = 1$ 的时候 $\frac{n - c}{a}$ 应该舍去。

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 1e5 + 5;
const int MOD = 1e9 + 7;
inline int read ();
int n,cnt,ans,p[MAX],phi[MAX],flag[MAX];
int gcd (int x,int y) {return (!y) ? x : gcd (y,x % y);}
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	n = read ();
	phi[1] = 1;
	for (int i = 2;i <= n;++i)
	{
		if (!flag[i]) p[++cnt] = i,phi[i] = i - 1;
		for (int j = 1;j <= cnt;++j)
		{
			if (i * p[j] > n) break;
			flag[i * p[j]] = 1;
			if (i % p[j] == 0) 
			{
				phi[i * p[j]] = phi[i] * p[j];
				break;
			}
			phi[i * p[j]] = phi[i] * (p[j] - 1);
		}
	}
	for (int i = 1;i <= n - 2;++i)
	{
		int k = n - i;
		for (int j = 1;j * j <= k;++j)
		{
			if (k % j != 0) continue;
			ans += 1ll * i * j / gcd (i,j) * phi[k / j] % MOD;
			ans %= MOD;
			if (j != 1 && k / j != j) ans += 1ll * i * k / j / gcd (i,k / j) * phi[j] % MOD,ans %= MOD;
		}
	}
	printf ("%d\n",ans);
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}

```

---

## 作者：fast_photon (赞：1)

Upd 2020/9/5 18:18 修改 $\phi$ 为 $\varphi$，添加为何理论更快实际更慢的叙述

**0. 前言**  
赛后十秒钟AC此题...  
（据说是因为System test结束了才能继续提交，所以评测记录是今天早上的，代码是赛后十秒钟写完的...）  
本次篇幅较长而且我自己读着都劝退，就把一些证明和叙述部分分开来，证明一般是证明上面离得最近的一个结论，如果这个结论自己会证可以直接跳过。  
附加的一些解释说明也会分离出来。  
先说一下， $x\in\mathbb{Z}$ 等价于 $x$ 是整数。

**1. 分析**  
首先我们都知道 $O(n^2\log n)$ 暴力非常好写，枚举 $c$，枚举 $b$，计算 $a$，然后代入求值加和即可。  
我们现在需要的只是把当 $c$ 固定的时候算出每一个总和即可。  
如果 $c$ 固定了，那么因为 $a+b+c=n$，所以 $a+b$ 也固定了。为了方便记为 $s$。再把 $\gcd(a,b)$ 记为 $d$。  
如果我们直接计算，难度会比较大，而且也无法汇总到式子 $\operatorname{lcm}(c, d)$ 里。  
那么什么样的 $\operatorname{lcm}(c, d)$ 可以合并计算呢？  
此时 $c$ 是固定的，所以答案是：$d$ 相同的几个式子。  
不那么显然但是可得 $d$ 是 $s$ 的因数。
>我们假设 $a=dx$，$b=dy$，那么可得 $s=d(x+y)$，显然 $x+y$ 是整数，那么可得 $d$ 是 $s$ 的因数。  
那就是枚举 $d\le \sqrt s$，然后可得 $d$ 和 $s\div d$ 分别是两个 $s$ 的因数。  

**注意：可能会存在 $s=d^2$ 的情况，不要重复计算**  
对于一个 $d$ 我们现在只需要在 $c$ 固定的情况下算两个东西： $\operatorname{lcm}(c,d)$ 和满足 $x+y=s\div d$ 并且 $\gcd(x, y)=1$ 的对数。  
显然，如果一对数 $x,y$ 满足上面的两个条件，那么 $dx+dy+c=n$。第二个条件的存在意义在于可以去除 $\gcd(a,b)$ 是 $d$ 的倍数的情况。否则会出现在枚举到 $d=1$ 的时候计算所有 $d=2,d=3\dots$ 的情况，而且计算结果是错误的。  

这个有序数对个数占用了我半小时，还是在大神同学的点拨下才会的...  
先上结论：$x+y=s\div d$ 的对数等于 $\varphi(s/d)$  
>其中 $\varphi(x)$ 表示满足 $1\le y\le x$，$y\in\mathbb{Z}$，$\gcd(x,y)=1$ 的 $y$ 的个数。即 $x$ 以内与 $x$ 互质的正整数个数。  

如何计算 $\varphi$ 这里不再赘述，线性筛或者逐个计算都可以  
补充一下对数等于 $\varphi$ 的证明。  
>对于一个数 $1\le x\le n$，$x\in\mathbb{Z}$，如果 $\gcd(x,n)=1$，那么 $\gcd(x,n-x)=1$。即 $y=n-x$。
>> 如果 $\gcd(x,n)=d$，那么设 $x=x_0d$，$n=n_0d$，$\gcd(x,n-x)=\gcd(x_0d,(n_0-x_0)d)=d$。  

>$(x,y)$ 满足 $\gcd(x,y)=1,x+y=n$ 对应到 $\gcd(x,n)=1$ 也是对的，证明同理设 $d$，不作赘述。  

那么我们就有一个很开心的结论：对于所有 $c=c_0,d=d_0$ 的情况，满足这一部分的总和是 $\operatorname{lcm}(c_0,d_0)\times\varphi((n-c_0)\div d)$。因为每一种情况对答案的贡献都是 $\operatorname{lcm}(c_0,d_0)$，而 $\varphi$ 函数求出的对数就是可能的情况数。  

那就对于所有情况求个和就行了。  
时间复杂度：  
预处理欧拉函数 $O(n)$  
枚举 $c_0$ $O(n)$  
枚举 $d_0$ $O(\sqrt n)$  
计算 $\operatorname{lcm}$ $O(\log n)$  
总时间复杂度 $O(n+n\sqrt n\log n)$   
当 $n=10^5$ 时，这个数是 $525342950.157$，也就是 $5e8$ 是可以卡过去的（事实证明只跑了不到 200ms）
当然还有理论更快的写法，分解质因数然后直接遍历每一个因数，但是问题就在于，在CF上这种做法不开O2跑了811ms 开了O2跑了826ms ~~，令我无法理解，大神可以在评论区解答一下为啥理论更快的做法更慢~~。现在我懂了，是因为
>代码里分解质因数那部分每个数分解都要遍历所有质数造成的时间浪费

的缘故。理论上可以加上 `p[i] * p[i] <= x` 的循环条件，跳出大循环之后将 $n$ 的剩余值（如果不为 1 ） 作为最后的一个质数通过映射找到下标并将底数下标和指数（此处为 $1$）写到 `pairvec` 里面。
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#define maxn 100005
#define mod 1000000007

using namespace std;

long long lcm(long long a, long long b) {
	return a / __gcd(a, b) % mod * b % mod;
}

struct pairvec {
	vector<int> p, q;//底数和指数 
};

long long n, ans, p[maxn], pn, phi[maxn];
bool up[maxn];

pairvec func1(int x) {//分解质因数，可以用到筛欧拉函数的副产物质数表 
	pairvec res;
	int i = 0;
	while(x > 1 && i < pn) {
		int cnt = 0;
		while(i < pn && x % p[i] != 0) i++;//找到下一个n的质因数
		while(i < pn && x % p[i] == 0) cnt++, x /= p[i];
		res.p.push_back(i);
		res.q.push_back(cnt);
	}
	return res;
}

vector<int> func2(pairvec f, vector<int> g) {
	vector<int> res;
	int cnt = 0;
	int xum = 1;//当前的因数
	while(cnt != 1) {
		res.push_back(xum);
		for(int i = 0; i < g.size(); i++) {
			if(g[i] == f.q[i]) {
				g[i] = 0;
				for(int j = 0; j < f.q[i]; j++) xum /= p[f.p[i]];
				if(i == g.size() - 1) cnt = 1;
			}
			else {
				g[i]++;
				xum *= p[f.p[i]];
				break;
			}
		}
	}
	return res;
}

int main() {
	cin >> n;
	for(int i = 2; i <= n; i++) {
		if(!up[i]) {
			p[pn++] = i;
			phi[i] = i - 1;
		}
		for(int j = 0; j < pn && i * p[j] <= n; j++) {
			up[i * p[j]] = 1;
			if(i % p[j] == 0) {
				phi[i * p[j]] = phi[i] * p[j] % mod;
				break;
			}
			phi[i * p[j]] = phi[i] * (p[j] - 1) % mod;
		}
	}
	for(int c = 1; c <= n - 2; c++) {
		int s = n - c;
		//直接枚举因数写法 
		pairvec v = func1(s);//分解质因数 
		vector<int> g;
		for(int i = 0; i < v.p.size(); i++) g.push_back(0);//放入足够多的0凑位数 ;
		g = func2(v, g);
		for(int i = 0; i < g.size(); i++) {
			if(s / g[i] > 1) {
				ans += phi[s / g[i]] * lcm(c, g[i]) % mod;//基础计算方式类似
				ans %= mod;
			}
		}
		//*/
		/* //Osqrt(n)枚举写法 
		for(int d = 1; d * d <= s; d++) {
			if(s % d == 0) {
				if(s / d > 1) {
					ans += (phi[s / d]) * lcm(c, d) % mod;
					ans %= mod;
				}
				if(d * d != s && d > 1) {
					ans += (phi[d]) * lcm(c, s / d) % mod;
					ans %= mod;
				}
			}
		}
		//*/
	} 
	cout << ans << endl;
}
```

---

## 作者：氧少Kevin (赞：0)

## CF1717E - Madoka and The Best University
### 题意
给出 $n(1\leq n\leq 10^5)$，求：
$$\sum_{a+b+c=n} \text{lcm}(c,\gcd(a,b))$$

### 思路

#### 错误思路
很容易想到将原式化成：$\frac{c\cdot \gcd(a,b)}{\gcd(a,b,c)}$，
但是接下来无从下手。

#### 正确思路

不难看出：

$$a=k_a\cdot \gcd(a,b)$$
$$b=k_b\cdot \gcd(a,b)$$
$$a+b=(k_a+k_b)\cdot \gcd(a,b)$$
$$c=n-(a+b)$$
$$\gcd(k_a,k_b)=1$$

枚举 $\gcd(a,b)$ 和 $(k_a+k_b)$，自然得到了 $a+b$ 和 $c$。

所以，原式 $=\text{lcm}(c,\gcd(a,b))\cdot cnt$，其中，$cnt=$ 满足 $\gcd(k_a,k_b)=1$ 的 $(k_a,k_b)$ 的对数。

$\gcd(k_a,k_b)=\gcd(k_a+k_b,k_a)=1$

在每次枚举 $(k_a+k_b)$ 之后，$cnt$ 就相当于满足与 $(k_a+k_b)$ 互质，并且小于 $(k_a+k_b)$ 的 $k_a$ 的数量。

使用欧拉函数即可求解。

> 求满足 $\gcd(a,b)=1$ 且 $a+b\leq x$ 的 $(a,b)$ 的数量，可以将原式化成 $\gcd(a+b,a)=1$，然后用欧拉函数求合法的 $a$ 的数量，这自然也是 $(a,b)$ 的数量。

---

## 作者：NotTogawaButSakiko (赞：0)

题意：给定一个正整数 $n$，对于所有满足 $a+b+c=n$ 的三元组 $(a,b,c)$，要求计算 $\sum{\operatorname{lcm}(c, \gcd(a, b))}$。

Sol：暴力枚举 $c$,将 $\gcd(a,b)$ 转化为 $\gcd(a,a + b)$ 即 $\gcd(a, n - c)$。
        
按照套路将 $\sum{\operatorname{lcm}(c, \gcd(a,n - c))}$ 转化为 $\sum{\operatorname{lcm}(c, d)[\gcd(a, n - c) = d]}$。

而 $\gcd(a, n - c) = d$ 的个数即 $\gcd(a / d, (n - c) / d) = 1$ 的个数，即 $\varphi{(n-c)/d}$。

线性筛欧拉函数求解即可。

---

## 作者：MZAutomata (赞：0)

可以自然地想到枚举三元组中的元素进而计数。

发现当 $\gcd(a,b)$ 与 $a+b$ 的值均已确定时，任意一组 $ \operatorname{lcm}(c,\gcd(a,b))$ 的值也是确定的，于是我们可以考虑枚举 $\gcd(a,b)$ 及使得 $\gcd(a,b)\cdot d=a+b$ 的 $d$ （若枚举 $a+b$，则确定 $\gcd(a,b)$ 所需的时间复杂度难以承受）。

于是对于每一组 $\gcd(a,b)$ 和 $d$，我们的问题变为：令 $d=p+q$，统计有多少组 $p$，$q$ 使得 $\gcd(p,q)=1$ 成立。

考虑再单独枚举 $p$ 的值并得到 $q$，若二者既约则累计进答案。但是这样的做法无法在时限内给出答案，于是我们可以想到：若 $d$ 与 $p$ 既约，则 $p$ 与 $q$ 一定既约（因为 $\gcd(p,q)=\gcd(p,d-p)=\gcd(d,p)=1$），那么预处理在不大于 $d$ 的数中与 $d$ 既约的数的个数，即 $\varphi(d)$ 的值即可。

### Code
```cpp
#include<cstdio>
#include<algorithm>
const int mod(1e9+7);
int pr[100005];
long long ph[100005];
bool vis[100005];
int main()
{
	int n,tot(0),k,l,i,j;
	long long ans(0);
	scanf("%d",&n);
	for(i=2,ph[1]=1;i<=n;i++)
	{
		if(!vis[i])ph[pr[++tot]=i]=i-1;
		for(j=1;j<=tot&&pr[j]*i<=n;j++)
		{
			vis[pr[j]*i]=true;
			if(i%pr[j]==0){ph[pr[j]*i]=ph[i]*pr[j];break;}
			ph[pr[j]*i]=ph[i]*(pr[j]-1);
		}
	}
	for(i=1;i<n;i++)
	  for(j=2;j*i<n;j++)
		k=n-i*j,l=k*i/std::__gcd(i,k),
		(ans+=l*ph[j])%=mod;
	printf("%lld",ans);
	return ~~(0-0);
}
```


---

## 作者：ttq012 (赞：0)

[CSDN](https://blog.csdn.net/lxylluvio/article/details/126677171?spm=1001.2014.3001.5501)

题意：给定 $n$，求所有三元组 $(a,b,c)$ 满足 $a+b+c=n$ 的 $\operatorname{lcm}(\gcd(a,b),c)$ 的和。

思想：

第一层循环枚举 $\gcd(a,b)$ 的值。

然后枚举 $a+b$ 的值。

容易发现，$a + b$ 的值一定是 $k\times \gcd (a,b)$，$k\in N^*$。

也就是说，$(a,b)$ 的取值方法一共有 $\varphi(\lfloor\frac{n-c}{\gcd(a,b)}\rfloor)$ 种，所以考虑进行类似于埃式筛法的算法，每一次更新的时候将答案加上 $\operatorname{lcm}(\gcd(a,b),c)\times \varphi(\lfloor\frac{n-c} {\gcd(a,b)}\rfloor)$ 即可。

```cpp
// 这回只花了45min就打完了。
// 真好。记得多手造几组。最好有暴力对拍。

#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 2e5 + 10, mod = 1e9 + 7;
int phi[N]; // debug 这个地方要开 long long
bool not_prime[N];
int cnt, primes[N], n, ans = 0;

void sieve()
{
  phi[1] = 1;
  for (int i = 2; i < N; i ++)
  {
    if (!not_prime[i])
    {
      primes[++ cnt] = i;
      phi[i] = i - 1;
    }
    for (int j = 1; i * primes[j] < N; j ++)
    {
      not_prime[i * primes[j]] = true; // debug i*primes[j] --> j*primes[j]
      if (i % primes[j])
        phi[i * primes[j]] = phi[i] * (primes[j] - 1);
      else
      {
        phi[i * primes[j]] = phi[i] * primes[j];
        break;
      }
    }
  }
}

signed main()
{
  cin >> n;
  sieve();
  for (int i = 1; i < n; i ++)
    for (int j = 2 * i; j < n; j += i) // debug =n 的话没有法子选了
      (ans += phi[j / i] * lcm(i, n - j) % mod) %= mod;
  cout << ans << '\n';
  return 0;
}

// 足下千里，移步换景，寰宇纷呈万花筒

```

---

## 作者：bruhify (赞：0)

为什么只有我拿着个枚举 $\text{gcd}$ 的套路硬往这道题上套...... 不过赛时推出来了，也算是个思维复杂度可以接受的做法吧，并且枚举 $\text{gcd}$ 的思路在推式子题里也比较常见。

## Problem:

给定$n$，求 $\sum_{a+b+c=n} \text{lcm}(c,\text{gcd}(a,b))$。$1 \leq n \leq 10^5$。

## Editorial:

看到 $\text{lcm}$ 和 $\text{gcd}$ 立刻想到枚举 $d=\text{gcd}(a,b)$。设 $p=\frac{a}{d}, q=\frac{b}{d}$，原式转化为 $\sum_{d=1}^{n}\sum_{d(p+q) <n} \text{lcm}(n-d(p+q),d)$，其中 $\text{gcd}(p,q)=1$。（后面所有共同提到 $p,q$ 的式子里都有 $\text{gcd}(p,q)=1$）

考虑 $\text{lcm}(x,y)=\frac{xy}{\text{gcd}(x,y)}$，那么 $\text{lcm}(n-d(p+q),d)=\frac{nd-d^2(p+q)}{\text{gcd}(n-d(p+q),d)}=\frac{nd-d^2(p+q)}{\text{gcd}(n,d)}=\text{lcm}(n,d)-\frac{d^2}{\text{gcd}(n,d)}(p+q)$。

原式 $=\sum_{d=1}^{n}\sum_{p+q\leq \lceil{\frac{n}{d}}\rceil-1}\text{lcm}(n,d)-\frac{d^2}{\text{gcd}(n,d)}(p+q)$。设 $f[n]$ 为互质的数 $i,j$ 之和 $\leq n$ 的方案数（实际上就是上式的第二层循环），$g[n]$ 为所有这样的 $i+j$ 之和，则原式 $=\sum_{d=1}^{n} \text{lcm}(n,d) \cdot f[\lceil{\frac{n}{d}}\rceil-1]-\frac{d^2}{\text{gcd}(n,d)} \cdot g[\lceil{\frac{n}{d}}\rceil-1]$。只要可以快速预处理出 $f,g$，问题就解决了。

对于 $f$，首先考虑他的差分序列 $f'[x]$，表示互质的数 $i,j$ 之和 $= x$ 的方案数，即 $f'[x]=\sum_{i=1}^{x-1}[\text{gcd}(i,x-i)=1]=\sum_{i=1}^{x-1}[\text{gcd}(i,x)=1]=\varphi(x)$。因此，$f$ 实际上就是 $\varphi$ 函数的前缀和。

类似地，考虑 $g$ 的差分序列 $g'[x]$，表示所有互质的数 $i,j$ 之和 $= x$ 的 $i+j$ 之和。然而对于每一个满足上述条件的$(i,j)$， $i+j=x$ 啊...... 所以，所有满足条件的 $i+j$ 之和实际上就是他们的方案数乘上 $x$，$g'[x]=f'[x]\cdot x$，$g$ 也可以预处理出来了。

## Code:

实际的代码十分简单，筛出来 $\varphi$ 函数后按式子算就好了。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=1e9+7;

int n;

int primes[100005],pcnt;

bool Composite[100005];

ll phi[100005],phis[100005];

ll f[100005],g[100005];

void Sieve() {
	Composite[1]=1;
	for(int i=2;i<=n;i++) {
		if(!Composite[i]) {
			primes[++pcnt]=i;
			phi[i]=i-1;
		}
		for(int j=1;j<=pcnt && i*primes[j]<=n;j++) {
			Composite[i*primes[j]]=1;
			if(i%primes[j]==0) {
				phi[i*primes[j]]=phi[i]*primes[j];
				break;
			}
			phi[i*primes[j]]=phi[i]*phi[primes[j]];
		}
	}
}

ll gcd(ll a,ll b) {
	if(b==0) {
		return a;
	}
	return gcd(b,a%b);
}

ll lcm(ll a,ll b) {
	return a/gcd(a,b)*b;
}

ll ans=0;

int main() {
	scanf("%d",&n);
	Sieve();
	for(int i=1;i<=n;i++) {
		phis[i]=phi[i]*i;
		f[i]=(f[i-1]+phi[i])%mod;
		g[i]=(g[i-1]+phis[i])%mod;
	}
	for(ll i=1;i<=n;i++) {
		ans+=lcm(i,n)%mod*f[(n+i-1)/i-1]%mod;
		ans-=(i*i/gcd(n,i))%mod*g[(n+i-1)/i-1]%mod;
		ans=(ans%mod+mod)%mod;
	}
	printf("%lld",ans);
	return 0;
}
```



题外话：赛时过题顺序ABECD... 果然还是做不来思维题呢。



---

