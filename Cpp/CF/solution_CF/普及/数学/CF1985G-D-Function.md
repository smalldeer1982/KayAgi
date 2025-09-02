# D-Function

## 题目描述

Let $ D(n) $ represent the sum of digits of $ n $ . For how many integers $ n $ where $ 10^{l} \leq n < 10^{r} $ satisfy $ D(k \cdot n) = k \cdot D(n) $ ? Output the answer modulo $ 10^9+7 $ .

## 说明/提示

For the first test case, the only values of $ n $ that satisfy the condition are $ 1 $ and $ 2 $ .

For the second test case, the only values of $ n $ that satisfy the condition are $ 1 $ , $ 10 $ , and $ 11 $ .

For the third test case, all values of $ n $ between $ 10 $ inclusive and $ 100 $ exclusive satisfy the condition.

## 样例 #1

### 输入

```
6
0 1 4
0 2 7
1 2 1
1 2 3
582 74663 3
0 3 1```

### 输出

```
2
3
90
12
974995667
999```

# 题解

## 作者：BrotherCall (赞：10)

## 题意

设 $D(x)$ 为 $x$ 的各数位之和。

给定 $l,r,k$，求多少 $n$ 满足：

- $10^l \leq n < 10^r$。

- $k\cdot D(n) = D(k\cdot n)$。

## 思路 

首先满足该条件的一个充分条件是 $n \times k$ 不产生进位。

所以我们猜测这个也是它的必要条件，考虑证明。

对于单独的一位 $n_i$，若它乘 $k$ 有进位。

则 $k \cdot D(n_i) = kn_i$，$\displaystyle D(k\cdot n_i) = \frac{kn_i}{10} + (kn_i \bmod 10)$。

后者小于前者，证明：

把 $kn_i$ 表示成 $10x + y$，$x$ 为正整数，$y$ 为非负整数，且 $y < 10$。则 $D(k\cdot n_i)$ 为 $x + y$。证毕。

所以必要条件成立。

### 计算答案

这题计算答案也没那么简单，根据最高位不能填 $0$，所以最高位有 $\displaystyle \frac{9}{k}$ 种填法，其他位有 $(\displaystyle \frac{9}{k} + 1)$ 种填法。

对于 $10^i \le n < 10^{i+1}$，满足条件的情况共 $\displaystyle \frac{9}{k}\cdot (\frac{9}{k} + 1)^i$ 种。

所以对于 $10^l \le n < 10^{r}$，满足条件的情况共 $\displaystyle \frac{9}{k}\cdot \sum\limits_{i = l}^{r - 1}(\frac{9}{k} + 1)^i$ 种。

根据等比数列求和公式可得到上式等于 $\displaystyle (\frac{9}{k}+1)^l\cdot ((\frac{9}{k}+1)^{r-l} - 1)$。

这个式子用快速幂和逆元相关知识就能求出来了。

## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#define int long long
using namespace std;

const int N = 1e6 + 100;
const int mod = 1e9 + 7;
char ch[N];
int t , n , m , z , k , a[N] , b[N];

int ksm(int x,int y) {
	int res = 1;
	for(;y;y >>= 1 , x = x * x % mod) 
		if(y & 1) 
			res = res * x % mod;
	return res;
}

signed main() {
	cin >> t;
	while(t --) {
		cin >> n >> m >> k;
		int wd = (9 / k);
		int now = (((ksm(wd + 1 , m - n) - 1) % mod) + mod) % mod; 
		now = ksm(wd + 1 , n) % mod * now % mod;
		cout << now << "\n"; 
	}
	return 0;
}
```

---

## 作者：fishing_cat (赞：6)

### 思路
通过手玩，或者数学直觉，可以很快发现只有当 $n \times k$ 不发生进位，即 $n$ 的每一位乘上 $k$ 都小于 $10$ 时，才会满足 $ D(k \times n) = k \times D(n) $ 的限制。

记 $maxn$ 为在 $n$ 每一位上可以使 $n \times k$ 不进位的数字个数。

具体对 $maxn$ 的计算，可以发现大多数的 $maxn$ 就是 $\lfloor \frac{10}{k} \rfloor + 1$。为什么加一？因为不会算上 $0$。      

但很快就发现不对了，因为在 $k$ 可以被 $10$ 整除的情况下，会把乘上 $k$ 等于 $10$ 的情况也算进去。很好解决，只需要特判在 $k$ 是 $1,2,5$ 时不去加一就可以了。自然 $k \geq 10$ 时直接就输出 $0$ 了。

先考虑对于 $l$ 是 $0$ 的情况，发现就是求在一个有 $r$ 位的数上，每一位有 $maxn$ 种数可以选，可以组合出多少种数，因为 $n$ 不能位   $0$，所以有 ${maxn}^{r} - 1$ 种 $n$ 满足要求。

当 $l$ 不是 $0$ 时，可以在 $r$ 位时的答案总数上减去 $l$ 位时的总数，就剩下了满足 $ 10^{l} \leq n < 10^{r} $ 时的答案总数。

即 $ans = {maxn}^{r} - {maxn}^{l}$，注意两次的快速幂会单独取模，可能会减出负数，所以要注意用负数的取模方式。
### 代码
```cpp
#include<bits/stdc++.h>
#define ll long long

const ll mod = 1e9 + 7;
using namespace std;

ll pw(ll b, ll power) { // 快速幂
	ll res = 1;
	while (power > 0) {
		if (power & 1)
			res =(res*b) %mod;
		power >>= 1;
		b= (b*b)%mod;
	}
	return res;
}

ll t, l, r, k, ans, maxn;
// maxn ==> 有多少个数满足 D(k*n) = k*D(n)

int main() {
	scanf("%lld", &t);
	while (t--) {
		scanf("%lld%lld%lld", &l, &r, &k);
		string h = to_string(k);
		// 通过转字符串来看 k 是几位数
		if (h.size() == 1) {
			maxn = 10 / k;
			if(k != 1 && k != 2 && k != 5)
				maxn ++;
			ans = pw(maxn, r);
			ans -= pw(maxn, l);
			ans = (ans + mod)%mod;
			printf("%lld\n",ans);
		} else { // 不是一位数 直接输出0
			puts("0");
		}
	}
 	return 0;
  // 完结撒花~~~
}
```

---

## 作者：ThySecret (赞：4)

## Before

由于数的位数很大，我们用 ${\textstyle \sum_{i = 0}^{n} a_i \times 10^i}$ 来表示一个 $n + 1$ 位的数，那么 $D(num) = {\textstyle \sum_{i = 0}^{n} a_i}$​ 就是这个数的数位之和。

## Solution

敲份暴力代码不难发现以下结论：

> 对于任意的 $num \in \left [ 10^l, 10^r \right )$，当且仅当 $num \times k$ 的任意一位上没有发生进位，满足 $D(k \times num) = k \times D(num)$。

证明：因为 $D(num) = {\textstyle \sum_{i = 0}^{n} a_i}$，$k \times D(num) = {\textstyle \sum_{i = 0}^{n} a_i \times k}$。只要 $num$ 上的第 $i$ 位发生了一次进位，说明第 $i - 1$ 位上的数位减少了 $10$，而第 $i$ 位上的数位增加了 $1$，这在数值上的贡献显然为 $0$，但是对于数的位数贡献为 $-9$，由上式可知 $num \times k$ 上的任意一位要严格为 $num$ 相应位上的 $k$ 倍，因此不允许发生任何进位。

接下来考虑的事情就十分简单，每一位上满足不进位的数是固定的：$t = \left \lceil \frac{10}{k} \right \rceil$（例如 $k = 3$ 时可以填入 $0,1, 2, 3$），而对于 $num \in \left [ 0 , 10^n \right  )$，满足条件的 $num$ 的个数即为 $t^n$，快速幂计算即可。

又由于 $num$ 的范围有着左闭右开的特点，我们不难想到用类似前缀和的思路分别计算从 $0$ 到 $l$ 和 $r$ 的个数，相减即可，即：

$$
ans \left [ l, r \right ) = ans \left [ 0, r \right )  - ans \left [0, l \right )
$$

单次时间复杂度：$\mathcal{O} (\log r)$。

## Code

```c++
LL ksm(LL a, LL b)
{
    LL res = 1;
    while (b)
    {
        if (b & 1) res = a * res % mod;
        a = a * a % mod, b >>= 1;
    }
    return res % mod;
}

inline LL calc(LL x) { return ksm(times, x); }

void solve()
{
    cin >> l >> r >> k;
    times = (10 + k - 1) / k;	// 向上取整
    cout << (calc(r) - calc(l) + mod) % mod << '\n';	// 涉及减法的取模务必加模再取以防止出现负数
}

```
## Update
2024.06.25 修改了部分笔误。

---

## 作者：luckyqwq (赞：4)

# CF1985G D-Function 题解

### 大致思路：

首先我们可以设数字 $n$ 的任意一位数字为 $s$，那么 $s$ 对于 $k ⋅ D(n)$ 的贡献为 $s ⋅ k$，对 $D(n ⋅ k)$ 的贡献为 $D(s ⋅ k)$，显然只有在 $s ⋅ k < 10$ 的情况下他们的贡献才可能相等，说明整个数 $n$ 也要满足此条件，接着我们可以用 $[0, 10 ^ r]$ 的答案减去 $[0, 10 ^ l]$ 的答案，但一个个处理时间太长，我们可以把数位不足的数加上前导 $0$ 来计算，显然这是不影响答案的。

### 代码实现：

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MOD = 1e9 + 7; 
inline int read()
{
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-'){
			w = -1;
		}
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}
int f(int a,int b,int p){
	int res = 1;
	while (b > 0)
	{
		if(b & 1) res = res * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return res;
}
int T;
signed main()
{
	T = read();
	while (T --)
	{
		int l, r, k;
		l = read(), r = read(), k = read();
		cout << (f((9 / k) + 1, r, MOD) - f((9 / k) + 1, l, MOD) % MOD + MOD) % MOD << "\n"; 
	}
	return 0;
}
```

这样这道题目就完成啦！！！

---

## 作者：oyoham (赞：3)

### Problem  
[CF传送门](https://codeforces.com/contest/1985/problem/G)

给定函数 $\operatorname{D}(x)$，表示数 $x$ 各数位之和。给定区间 $[10^l,10^r)$ 与数 $k$，求区间内有多少数满足 $k\times \operatorname{D}(x)=\operatorname{D}(k\times x)$。
### solution  
可以从题目中发现  
+ 对于数据 $l=0,r=1,k=4$，答案为 $2=3^1-3^0$，其中 $3=\lfloor \frac{9}{k} \rfloor+1$。
+ 对于数据 $l=0,r=2,k=7$，答案为 $3=2^2-2^0$，其中 $2=\lfloor \frac{9}{k} \rfloor+1$。
+ 对于数据 $l=1,r=2,k=1$，答案为 $90=10^2-10^1$，其中 $10=\lfloor \frac{9}{k} \rfloor+1$。
+ 对于数据 $l=1,r=2,k=3$，答案为 $12=4^2-4^1$，其中 $4=\lfloor \frac{9}{k} \rfloor+1$。
+ 对于数据 $l=0,r=3,k=1$，答案为 $999=10^3-10^0$，其中 $10=\lfloor \frac{9}{k} \rfloor +1$。

因此，我们猜测，对于数据 $l,r,k$，有答案为 $ans=(\lfloor \frac{9}{k} \rfloor+1)^r-(\lfloor \frac{9}{k} \rfloor+1)^l$。  
### proof
若数 $x,k$ 满足 $\operatorname{D}(x\times k)=k\times \operatorname{D}(x)$，定义 $x_i$ 表示数 $x$ 十进制下第 $i$ 位，由定义可得，$0\le x_i\le 9$，则 $k\times \operatorname{D}(x)=k\times \sum_{i=1}^{\infty} x_i=\sum_{i=1}^{\infty} k\times x_i,\operatorname{D}(k\times x)=\sum_{i=1}^{\infty} (k\times x)_i$，所以有 $\forall i \ge 1,k\times x_i=(k\times x)_i$，所以 $\forall i \ge 1,k\times x_i\le 9$。  
对于区间 $[0,10^k)$，每个数位上有 $\lfloor \frac{9}{k} \rfloor +1$ 个数合法（即 $0,1,\dots,\lfloor \frac{9}{k} \rfloor$），根据乘法原理，区间内共有 $(\lfloor \frac{9}{k} \rfloor+1)^k$ 个数合法。  
所以区间 $[10^l,10^r)=[0,10^r)-[0,10^l)$，分两次快速幂即可，时间复杂度为 $O(t\log r)$。  
### code
```cpp#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll
inline ll read(){
	ll x=0;
	short f=1;
	char c=getchar();
	while(c>57||c<48){
		if(c==45) f=-1;
		c=getchar();
	}
	while(c<58&&c>47){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
inline void write(ll x){
	if(x<0ll) putchar(45),x=~x+1;
	if(x>9ll) write(x/10);
	putchar(x%10|48);
}
int T=read();
#define mod 1000000007
int fp(int a,int b){//快速幂
	int ans=1,base=a;
	while(b){
		if(b&1) ans=(ans*base)%mod;
		base=base*base%mod;
		b>>=1;
	}
	return ans;
}
signed main(){
	while(T--){
		int l=read(),r=read(),b=9/read()+1;
		write((fp(b,r)-fp(b,l)+mod)%mod);putchar(32);
	}
}
```

---

## 作者：_LSA_ (赞：3)

## 题意
令 $D(n)$ 代表 $n$ 各个数位上数字之和。求有多少个 $ 10^{l} \leq n < 10^{r}$ 满足 $D(k \cdot n) = k \cdot D(n) $？答案对 $10^9+7$ 取模。
## 分析
我们先给出一个结论：对于满足条件的 $n$，$n \cdot k$ 不会发生进位。

证明：考虑 $n$ 的每一个数位 $d$，它对 $k \cdot D(n)$ 的贡献为 $k \cdot d$，而对 $D(k \cdot n)$ 的贡献为 $D(k \cdot d)$。显然只有 $k \cdot d < 10$ 时 $k \cdot D(d) = k \cdot d$，否则 $k \cdot D(d) < k \cdot d$。所以 $n$ 的每一个数位 $d$ 都得满足 $k \cdot d < 10$，证毕。

我们用考虑 $[0,10^r)$ 的答案减去 $[0,10^l)$ 的答案。

那么这样做，$n$ 的每一位可以随便填不发生进位的任意数（我们可以把低位数看作高位数加上前导零），也就是 $[0,\lfloor \frac{9}{k} \rfloor]$，直接快速幂计算即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll read(){
    ll X = 0 ,r = 1;
    char ch = getchar();
    while(!isdigit(ch) && ch != '-') ch = getchar();
    if(ch == '-') r = -1,ch = getchar();
    while(isdigit(ch)) X = X*10+ch-'0',ch = getchar();
    return X*r;
}
const int mod = 1e9+7;
ll fpow(ll x,ll k){
	ll res = 1;
	while(k){
		if(k & 1)
			res = res*x%mod;
		x = x*x%mod;
		k >>= 1;
	}
	return res;
}
int main(){
	int T = read();
	while(T--){
		int l = read(),r = read(),k = read();
		cout << (fpow(9/k+1,r)-fpow(9/k+1,l)+mod)%mod << "\n";
	}
    return 0;
}
```

---

## 作者：ZhaoV1 (赞：1)

题目思路：经过细致的观察（观察了很久）式子 $D×(k×n)=k×D×(n)$ 和枚举 $n$，我们发现存在最小 $i$ 使得 $k×i≥10$，此时的 $i$ 就相当于咱们的进制数 $cnt$（这块很难理解，一定要模拟一下）。为什么说是进制数呢，举个例子：
```
当k = 3时, cnt = 4;
我们不妨取 l = 0,r = 3（即 n 从1~999间取得）
那么 n 能取到的数就是：
001 002 003 010 011 012 013 020 021 022 023 030
031 032 033 100 101 102 103 110 111 112 113 120
121 122 123 130 131 132 133 200 201 202 203 210
211 212 213 220 221 222 223 230 231 232 233 300
301 302 303 310 311 312 313 320 321 322 323 330
331 332 333
以上数字乘上 k 均不会进位（十进制），所以完全满足公式，这也是把 cnt 当作进制数的原因。切记，虽然看起来像是四进制数，其实去掉所有前缀零，他们还是十进制数。
```
求 $cnt$：
```cpp
	for(int i=1;i<=10;i++){//我的写法
		if(k*i >= 10){
			cnt = i;
			break;
		}
	}
```
介于我的代码较为冗长，建议参考其他题解的来替换：
```cpp
	cnt = 9/k+1;
```
由于 $n$ 是从 $10^l$ 到 $10^r-1$ 之间取得，所以我们用满足后者的 $n$ 的总数减去前者就可以得到答案啦。


AC Code
------------

```cpp
#include <bits/stdc++.h>
#define int unsigned long long
using namespace std;
const int MOD = 1e9+7;
int t,n,l,r,k,res,cnt;

signed fast_power(int base, int power){
	int ans = 1;
	while(power){
		if(power&1){
			ans = ans*base%MOD;
		}
		power /= 2;
		base = base*base%MOD;
	}
	return ans;
}

void solve(){
	res = 0;
	cin >> l >> r >> k;
	for(int i=1;i<=10;i++){//我的写法
		if(k*i >= 10){
			cnt = i;
			break;
		}
	}
	res = fast_power(cnt,r) - fast_power(cnt,l);//cnt为进制数
	cout << (res+MOD)%MOD << '\n';
}

signed main()
{	
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> t;
	while(t--){
		solve();
	}
	return 0;
}

```

补一句，由于要取模，输出答案最好写为：
```cpp
	cout << (res+MOD)%MOD << '\n';
```

---

## 作者：Engulf (赞：0)

$D(kn) = kD(n)$ 等价于 $n$ 进行 $k$ 次加法不发生进位，考虑容斥，设 $f(x)$ 表示 $[0, 10^x)$ 中满足条件的数的个数，对于每一位 $y$，都需满足 $ky \le 9$，所以 $y \in [0, \left\lfloor\dfrac{9}{k}\right\rfloor]$，每一位都是如此，根据乘法原理，$f(x) = (\left\lfloor\dfrac{9}{k}\right\rfloor + 1)^x$。最终答案就是 $f(r) - f(l)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    cin >> tt;
    while (tt--) {
        int l, r, k;
        cin >> l >> r >> k;

        const int mod = 1e9 + 7;

        auto qpow = [](int a, int b) {
            int res = 1;
            while (b) {
                if (b & 1) res = 1ll * res * a % mod;
                a = 1ll * a * a % mod;
                b >>= 1;
            }
            return res;
        };

        cout << (qpow(9 / k + 1, r) - qpow(9 / k + 1, l) + mod) % mod << "\n";
    }
    return 0;
}
```

---

## 作者：_O_v_O_ (赞：0)

设 $f(i,k)$ 为满足 $G(j)\times k=G(j\times k)$ 且 $j\in[0,i)$ 的 $j$ 的数量。

那么题目中就像让我们求 $f(r,k)-f(l,k)$。

那我们如何快速求出 $f(x,k)$ 呢？我们注意到，假设有一数 $a$，那么 $a$ 必须满足 $a\times k<10$ 才能使 $G(a)\times k=G(a\times k)$ 起效。

那么我们来变换一下上述式子，即 $a\le 10\div k$，此时 $a$ 最多为 $\lceil\frac{10}{k}\rceil$。

那么如果想令一个可以含前导零的数 $n$ 满足 $G(n)\times k=G(n\times k)$，那么必须满足 $n$ 的每一位都 $\le \lceil\frac{10}{k}\rceil$。

那么 $f(x,k)$ 就相当于求有多少个可以含前导零的 $x$ 位数 $y$ 满足 $y$ 的每一位都 $\le \lceil\frac{10}{k}\rceil$。

那么我们用排列的知识可得答案为 $(\lceil\frac{10}{k}\rceil)^x$。

那么问题的答案就是 $(\lceil\frac{10}{k}\rceil)^r-(\lceil\frac{10}{k}\rceil)^l$，用快速幂即可。

---

## 作者：tanzexiaodezhonghao (赞：0)

## 思路
很简单，对于 $n$ 的数位 $n_i$，它对 $k \times D(n)$ 为 $n_i \times k$，但通过计算可以发现，只有在 $n_i \times k \le 9$ 的情况下 $k \times D(n_i) = n \times k$，所以 $n_i \times k$ 必须小于等于 $9$。直接 $[0, 10 ^ r]-[0, 10 ^ l]$ 就可以了，计算方式见代码。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod=1e9+7; 
ll T,l,r,k;
ll qpow(ll base,ll qp){
	ll ans=1;
	while(qp>0){
		if(qp&1){ans*=base;ans%=mod;}    
		qp>>=1;
		base*=base;base%=mod;
	}
	return ans;
}
int main(){
    ios::sync_with_stdio(false);cin.tie(0);
	cin>>T;
	while(T--){
		cin>>l>>r>>k;
		cout<<(qpow((9/k)+1,r)%mod-qpow((9/k)+1,l)%mod+mod)%mod<<endl; 
	}
	return 0;
}
```

---

