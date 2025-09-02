# [AGC040C] Neither AB nor BA

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc040/tasks/agc040_c

正の偶数 $ N $ が与えられます． `A`,`B`,`C` のみからなる長さ $ N $ の文字列 $ s $ であって，次の条件を満たすものの個数を求めてください．

- 以下の操作を繰り返すことで，$ s $ を空文字列へと変換できる．
  - $ s $ の中で連続した $ 2 $ 文字を選び，消す．ただし，選んだ $ 2 $ 文字が `AB` または `BA` であってはいけない．

例えば，$ N=4 $ のとき，`ABBC` は条件をみたします． `ABBC` →（ `BB` を消去）→ `AC` →（ `AC` を消去 ）→ 空文字列 と操作すれば良いです．

なお，答えは非常に大きくなることがあるので $ 998244353 $ で割ったあまりを求めてください．

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^7 $
- $ N $ は偶数

### Sample Explanation 1

$ s= $`AB`,`BA` 以外の文字列は条件を満たします．

## 样例 #1

### 输入

```
2```

### 输出

```
7```

## 样例 #2

### 输入

```
10```

### 输出

```
50007```

## 样例 #3

### 输入

```
1000000```

### 输出

```
210055358```

# 题解

## 作者：Soulist (赞：25)

这道题非常 nb

C 题好难啊 TAT

----

考虑 长度为$2$ 的删除。

一个联想是黑白染色。

我们对原序列进行黑白染色，那么每个删除为位置都会跨过 黑和白

考虑把黑色位置上的 $A$ 和 $B$ 翻转，$A\to B,B\to A$

那么不能删除的 AB 和 BA 其实等价于 AA 和 BB

于是原问题等价于给定一个长度为 $n$ 的由 ABC 构成的序列，不能删 AA 和 BB，求多少个序列可以删空。

只考虑 A 的话每次都能至少删除一个 A 和一个其他，于是 A 能被删空的条件等价于 A 的数量小于等于 $n/2$

对于 B 同理。

于是原题等价于给定长度为 $n$ 的序列，求 A 和 B 的出现次数均不超过 $n/2$ 的方案数。

这个问题显然可以容斥计算，超过 $n/2$ 的元素必然固定，假定为 $A$，枚举其出现次数，其他位置随便填即可。记得乘 $2$

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i )
#define re register
#define int long long
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int P = 998244353 ; 
const int N = 1e7 + 5 ;
int n, inv[N], fac[N], fp[N], Ans ;
int fpow( int x, int k ) {
	int ans = 1, base = x ;
	while( k ) {
		if( k & 1 ) ans = ans * base % P ;
		base = base * base % P, k >>= 1 ;
	} return ans ; 
}
void inc( int &x, int y ) {
	( ( x += y ) >= P ) && ( x -= P ) ;
}
int C( int x, int y ) {
	if( y > x ) return 0 ;
	return fac[x] * inv[y] % P * inv[x - y] % P ;
}
signed main()
{
	n = gi(), fp[0] = inv[0] = fac[0] = 1 ;
	rep( i, 1, n ) fac[i] = fac[i - 1] * i % P, fp[i] = fp[i - 1] * 2 % P ; 
	inv[n] = fpow( fac[n], P - 2 ) ;
	for( re int i = n; i >= 1; -- i ) inv[i - 1] = inv[i] * i % P ;
	int m = ( n / 2 ) + 1, num = 0 ;
	Ans = fpow( 3, n ) ;
	for( re int i = m; i <= n; ++ i ) {
		int dec = C( n, i ) ;
		dec = dec * fp[n - i] % P ;
		inc( num, dec ) ;
	}
	Ans = ( Ans - num * 2ll % P + P ) % P ;
	printf("%lld\n", Ans ) ;
	return 0 ;
}
```

---

## 作者：zhylj (赞：4)

先考虑只有 ``A``，``B`` 怎么算，注意到每次我们都是删一个奇一个偶，那么令奇数位置的 ``A`` 为 $1$，``B`` 为 $-1$，偶数位置的 ``A`` 为 $-1$，``B`` 为 $-1$，那么每次就是取一对 $1,-1$ 或 $-1,1$ 删除，不难发现删光的必要条件是和为 $0$，也不难发现它是充分的，因为此时总同时有 $1,-1$，所以总能删掉一对，使得总数更少，直到没有。

再加入 ``C`` 的贡献，注意到 ``C`` 相当于可以任意取 $1,-1$ 去匹配，所以如果 ``C`` 的个数 $k$ 和 ``A``，``B`` 的个数 $i,j$ 满足 $k\ge |i-j|$ 就可以。注意到 $k=N-i-j$，所以实际上相当于 $-(N-i-j)\le i-j\le N-i-j$，即为 $i,j\le \dfrac N2$。

所以答案相当于 $n$ 个数分成三组，其中两组大小都不能超过 $\dfrac N2$ 的方案数，不拿发现可以容斥，由于 $\gt\dfrac N2$ 只有至多一对，所以可以枚举最大的组，故答案为 $\displaystyle 3^N-2\sum_{i=N/2+1}^N\binom{N}{i}2^{N-i}$。

```cpp
const int N = 1e7 + 5, MOD = 998244353;

int QPow(int a, int b) {
	int ret = 1, bas = a;
	for(; b; b >>= 1, bas = 1LL * bas * bas % MOD)
		if(b & 1) ret = 1LL * ret * bas % MOD;
	return ret;
}

int fac[N], fac_inv[N], pw[N];
void Init() {
	fac[0] = 1;
	for(int i = 1; i < N; ++i) fac[i] = 1LL * fac[i - 1] * i % MOD;
	fac_inv[N - 1] = QPow(fac[N - 1], MOD - 2);
	for(int i = N - 2; ~i; --i)
		fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % MOD;
	pw[0] = 1;
	for(int i = 1; i < N; ++i) pw[i] = 1LL * pw[i - 1] * 2 % MOD;
}
int C(int x, int y) {
	if(x < y || y < 0) return 0;
	return 1LL * fac[x] * fac_inv[y] % MOD * fac_inv[x - y] % MOD;
}

int f[N];

int main() {
	int n; rd(n);
	Init();     
	int ans = 0;
	for(int i = n / 2 + 1; i <= n; ++i)
		ans = (ans + 1LL * C(n, i) * pw[n - i]) % MOD;
	ans = ans * 2 % MOD;
	ans = (QPow(3, n) - ans + MOD) % MOD;
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：Jorisy (赞：3)

利用 [Some Simple Tricks](https://www.luogu.com.cn/article/cqhi72t6) 中的 $\textbf{\textit{Trick 2}}$，将偶数位的 `A`、`B`、`C` 翻转为 `B`、`A`、`C`，就变成了删除过程中不出现 `AA` 或 `BB`。根据抽屉原理，满足要求的串中 `A` 和 `B` 的出现次数不应超过 $\dfrac n2$，然后容斥一下就有答案的式子 $3^n-\sum\limits_{i=\frac n2+1}^n\binom ni\cdot2^{n-i}$ 了。

---

## 作者：wxzzzz (赞：2)

### 思路

先考虑只有 $\tt A,B$ 的情况。

令奇数位上 ${\tt A}=1,{\tt B}=-1$，偶数位上 ${\tt A}=-1,{\tt B}=1$。

这样 $\tt AB,BA$ 被表示为 $1,1$ 或 $-1,-1$。

合法的删除操作是删除一对和为 $0$ 的相邻数对，因此只要全局和为 $0$ 就是合法字符串。

现在加入 $\tt C$，显然 $\tt C$ 可任意看作 $1,-1$。

先不加入 $\tt C$，令 $s1$ 表示序列中 $1$ 的数量，$s2$ 表示 $-1$ 的数量，则应加入 $\tt C$ 的数量 $s3$ 应满足 $s3\ge|s1-s2|$。

因为 $s3=n-s1-s2$，有：

$$\begin{aligned}
&\because n-s1-s2\ge |s1-s2|\\
&\therefore -(n-s1-s2)\le s1-s2\le n-s1-s2\\
&\therefore
	\begin{cases}
   s1\le \cfrac{n}{2}\\
   s2\le \cfrac{n}{2}
   \end{cases}
\end{aligned}$$

因此答案相当于 $n$ 个数分成三组，其中两组大小都不能超过  $\cfrac{n}{2}$ 的方案数。可以用总数减去不合法的方案数，枚举 $>\cfrac{n}{2}$ 的组的大小 $i$，其他两组任意分，方案为 $\dbinom{n}{i}2^{n-i}$，所以最终答案为 $\displaystyle 3^n-2\times\sum_{i=\frac{n}{2}+1}^n\dbinom{n}{i}2^{n-i}$。

### 代码

```cpp
#include <bits/stdc++.h>
#define MOD 998244353
using namespace std;
int n;
long long ans, fac[10000005];
long long mod(long long x) {
    return x % MOD;
}
long long qpow(int x, int k) {
    long long ret = 1, base = x;

    while (k) {
        if (k & 1)
            ret = mod(ret * base);

        base = mod(base * base);
        k >>= 1;
    }

    return ret;
}
long long C(int x, int y) {
    if (x < y)
        return 0;

    long long t = qpow(mod(fac[y] * fac[x - y]), MOD - 2);
    return mod(fac[x] * t);
}
int main() {
    cin >> n;
    fac[0] = 1;

    for (int i = 1; i <= n; i++)
        fac[i] = mod(fac[i - 1] * i);

    ans = qpow(3, n);

    for (int i = n / 2 + 1; i <= n; i++)
        ans = mod(ans - mod(2 * C(n, i) * qpow(2, n - i)));

    ans = mod(ans + MOD);
    cout << ans;
    return 0;
}
```

---

## 作者：hyman00 (赞：2)

## AT_agc040_c 题解

想学正解的请移步其他题解。

这题非常难，但是我们有 oeis。

发现样例的 `50007` 比较特别，于是在 oeis 上搜索 `7 50007`，中间是空格（如果用逗号搜不到），

于是搜到了 [A368164](https://oeis.org/A368164)，恰巧项数又正好对的上，我们猜答案就是这个数列。

oeis 上没有给出通项，但是给了生成函数：$f(t)=\sqrt{1-8t}\times\frac{1-6t}{1-9t}$ 

由于数据范围是 $10^7$，不能用 ntt 直接跑

但是，通过简单观察，发现分子分母及根号里的都是一次的，可以手动计算

根据公式：
$$
(1+x)^a\\
=\sum_{i=0}^{\inf}\frac{a(a-1)\dots(a-i+1)}{i!}x^i
$$
带入 $a=-1/2,x=-8t$ 并化简：
$$
\begin{aligned}
&(1-8t)^{-1/2}\\
=&\sum_{i=0}^{\inf}\frac{(-1/2)(-3/2)\dots(-(2i-1)/2)}{i!}(-8t)^i\\
=&\sum_{i=0}^{\inf}\frac{(-1)(-3)\dots(-(2i-1))}{i!}(-4t)^i\\
=&\sum_{i=0}^{\inf}\frac{1*3*\dots(2i-1)*4^i}{i!}t^i\\
=&\sum_{i=0}^{\inf}\frac{(2i)!*4^i}{i!i!2^i}t^i\\
=&\sum_{i=0}^{\inf}\frac{(2i)!}{(i!)^2}2^it^i\\
=&\sum_{i=0}^{\inf}\binom{2i}{i}2^it^i
\end{aligned}
$$
于是可以预处理阶乘和阶乘逆元计算。

然后考虑除 $1-9t$ 的过程，可以类比除 $1-t$，即求前缀和，从前往后执行 `a[i]+=a[i-1]*9` 即可。

最后是乘 $1-6t$，也是容易的，从后往前执行 `a[i]-=a[i-1]*6` 即可。

然后就可以输出答案了，注意 $n$ 要先除以二。

测试样例 3 发现过了，说明我们的猜测是对的。

代码

```c++
int qp(int a,int b){
	int c=1;
	for(;b;(a*=a)%=MOD,b>>=1)if(b&1)(c*=a)%=MOD;
	re c;
}
const int N=5000003;
int fac[N*2],fiv[N],a[N];
void run(){
	fac[0]=1;
	rept(i,1,N*2)fac[i]=fac[i-1]*i%MOD;
	fiv[N-1]=qp(fac[N-1],MOD-2);
	for(int i=N-1;i;i--)fiv[i-1]=fiv[i]*i%MOD;
	int c=1;
	rep(i,N){
		a[i]=c*fac[i*2]%MOD*fiv[i]%MOD*fiv[i]%MOD;
		(c*=2)%=MOD;
	}
	rept(i,1,N)(a[i]+=a[i-1]*9)%=MOD;
	for(int i=N-1;i;i--)(a[i]+=MOD-a[i-1]*6%MOD)%=MOD;
	int n;
	cin>>n;
	cout<<a[n/2]<<"\n";
}
```

---

## 作者：xukehg (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/solution/AT_agc040_c)

很明显，直接求某些字串能被消除是非常复杂的，因此我们考虑字串的总数减去不可以被消除的子串数量。

**很明显，总字串的个数为 $3 ^ n$ 个，可以使用快速幂优化到 $O(\log n)$ 的时间复杂度** 。

由于 $AB$ 和 $BA$ 是对称的，因此可以先考虑 $AB$ 。

研究样例后会发现，通常一个字串不能消除是因为有几个连续的 $AB$ 字串，

而每个 $AB$ 字串，**$B$ 的就位置是一样的** 。

**因此，可以将每个子串中的** $B$ **替换成** $A$ **且问题更变为不能删子串** $AA$ 。

**因此整个问题同等于不能删字串** $AA$ 。

现在问题就很好解决了，因为只要 $A$ 的数量大于总长度的一半，该字串就不能被消除。

我们从字符串中有 $(\dfrac{n}{2} + 1)$ 到 $n$ 个 $A$ 是有多少个字符串不能被消除。

很明显，剩下的位置无论怎么放 $B$ , $C$ 都不能被消除，且 $A$ 的放置也是无所谓的。

因此不可以消除的字符串个数为总数为：
$$ \sum_{i=\frac n 2+1}^n C_n^{i} \times 2^{n-i}$$
因为 $AA$ , $BB$ 字串是对称的，因此答案为：

$$3^n-2\times \sum_{i=\frac n 2+1}^n C_n^{i} \times 2^{n-i}$$

代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e7 + 5,mod = 998244353;

int n;
int fac[N],ifac[N];
int qpow(int a,int b) {
	int cnt = 1;
	while (b){
		if (b & 1) cnt = cnt % mod * a % mod;
		a = a % mod * a % mod;
		b >>= 1;
	}
	return cnt;
}
int C(int n,int m) {
	if (n < 0 || m < 0 || n - m < 0) return 0;
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}
int ans = 0;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	fac[0] = ifac[0] = 1;
	for (int i = 1;i <= N;i++) fac[i] = fac[i - 1] * i % mod;
	ifac[N] = qpow(fac[N],mod - 2);
	for (int i = N - 1;i >= 1;i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
	cin >> n;
	int zonghe = qpow(3,n);
	ans = 0;
	for (int i = 0;i <= n;i++){
		if (i <= n / 2) continue;//i从n / 2 + 1开始搜就可以了，这里写多余了
		ans = (ans + qpow(2,n - i) * C(n,i) % mod) % mod;
	}
	cout << (zonghe + mod - ans * 2 % mod) % mod;
}

---

## 作者：do_it_tomorrow (赞：1)

很难发现其实删除不会改变元素位置的奇偶性，所以只需要把奇数位置的 $\texttt{A}$ 和 $\texttt{B}$ 互换就行了。

那么现在就是 $\texttt{AA}$ 和 $\texttt{BB}$ 不能删除，所以只需要 $\texttt{A}$ 和 $\texttt{B}$ 的数量都不超过 $\lfloor\dfrac{n}{2}\rfloor$ 就行了。

正难则反，得到：

$$Ans=3^n-2\times \sum\limits_{i=\lfloor\frac{n}{2}\rfloor+1}^n {n\choose i}\times 2^{n-i}$$

显然，所有的方案数是 $3^n$ 因为每一个位置都有 $2$ 种方案。

然后枚举 $\texttt{A}$ 或者 $\texttt{B}$ 的数量，从 $\lfloor\dfrac{n}{2}\rfloor+1$ 开始枚举所以方案一定是无法消去的。

选择 $i$ 个位置填 $\texttt{A}$ 或者 $\texttt{B}$，其它的位置乱填就行了。

需要注意，并不需要考虑重复的情况，因为数量大于 $\lfloor\dfrac{n}{2}\rfloor+1$ 的元素肯定只有一种。

通过合理的实现，可以做到 $O(n)$。

```cpp
#include<iostream>
#define int long long
using namespace std;
const int N=1e7+5,mod=998244353;
int n,jc[N],inv[N],ans;
int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1) ans=ans*a%mod;
        a=a*a%mod,b>>=1;
    }
    return ans;
}
void init(int n){
    jc[0]=1;
    for(int i=1;i<=n;i++){
        jc[i]=jc[i-1]*i%mod;
    }
    inv[n]=ksm(jc[n]);
    for(int i=n-1;i>=0;i--){
        inv[i]=inv[i+1]*(i+1)%mod;
    }
}
int C(int n,int m){
    return jc[n]*inv[m]%mod*inv[n-m]%mod;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr),init(N-1);
    cin>>n;
    for(int i=n,p=1;i>=n/2+1;i--,p=p*2%mod){
        ans=(ans+C(n,i)*p)%mod;
    }
    cout<<((ksm(3,n)-2*ans)%mod+mod)%mod<<'\n';
    return 0;
}
```

---

## 作者：2008verser (赞：1)

太诡异了。第一发现这玩意递推不了。那就要找充要。经过一些分析又发现完全找不着头发。

观察 $A,B,C$ 数量变化。如果两个同类接触，则可以把这类的数量减二。再看所有的 $C$，可以同时将 $C$ 和与其接触的数量减一。

这时还是不能找到条件。原因在于在已知三种数量的条件下，我们并不知道每种操作是否能进行。

那么回去看题目，注意删除操作，每个元素在序列中下标奇偶性不会改变。

将奇数下标上的 $A,B$ 互相替换。（这我是真没想到！）

则不能操作的变为 $AA,BB$。立刻注意到充要条件是 $A,B$ 的数量都不超过 $n/2$。

转换后的序列显然和原来的是双射。而转换后的计数是容易的，用 $3^n$ 减去其中一种超过的即可。

**启示：留意题目中的特性。比如这道题就是奇偶性。**

[AC 链接](https://atcoder.jp/contests/agc040/submissions/60713458)

---

## 作者：Dream__Sky (赞：1)

首先发现该题有两个性质

- 删除的两个位置奇偶性相同。
- 删除后该序列其余位置奇偶性不变。
 
那我们可以把所有偶数位上的 `A`变成 `B`，`B` 变成 `A`。由于变换前和变换后的序列是一一对应的，那么问题变为，有多少个序列不能删除 `AA` 与 `BB` 还能删光。

充要条件是两种字符的数量都不能超过 $\dfrac{N}{2}$，因为每一串 `A`(或 `B`)的左端或右端都能有一个与之相删除的字符，我们可以每次在边缘删除。但是如果数量超过了 $\dfrac{N}{2}$，删到最后仍会有字母留下，无法删光。

之后用容斥计算即可，答案为 $3^n-2\sum_{i=\frac{N}{2}}^n(^N_i)2^{n-i}$。

代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MOD=998244353,N=1e7+10;
int n,ans,fac[N],inv[N];
int qpow(int base,int temp)
{
	int ans=1;
	for(;temp;temp>>=1,base=base*base%MOD)
		if(temp&1) ans=ans*base%MOD;
	return ans%MOD; 
}
void init()
{
	fac[0]=inv[0]=1;
	for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%MOD;
	inv[n]=qpow(fac[n],MOD-2);
	for(int i=n-1;i>=1;i--) inv[i]=inv[i+1]*(i+1)%MOD;
}
int G(int x,int y)
{
	return fac[x]*inv[y]%MOD*inv[x-y]%MOD;
}
signed main()
{
	cin>>n;
	init();
	for(int i=n/2+1;i<=n;i++) ans=ans+(G(n,i)*qpow(2,n-i)%MOD)%MOD;
	cout<<(qpow(3,n)%MOD+MOD-2*ans%MOD)%MOD;
	return 0;
 } 
```


---

## 作者：Doqe (赞：1)

这题有一个比较不神仙~~硬核~~的解法。考虑对 `AB` 不作转换，直接硬干。

对于 `AB` 的限制我们知道只有形如 `ABABAB` 的才会受限，即 `AB` 交错。

接着我们发现正常情况下，我们可以~~举全国之力~~将所有非 `AB` 段的都拿去和 `AB` 段对消即可。

但是有一个反例 `ABABACCABABA` ，几乎是 `AB` 却可行，而 `ABABACCBABAB` 就不行。这启发我们要对 `AB` 和 `BA` 分开（分类标准是奇数位上为 `A` 还是 `B`，具体来说，`CCABCC` 是 `AB` 段，而 `CCCABC` 却是 `BA` 段，而且单个 `A` 或 ` B` 也成段）。

同时，我们可以发现除了 `AB`，`BA`，剩下的只有 `C`，这三种类别都可以对消。

比如 `ABABCAABA`，以 `AB` 段居多（ `ABAB__ABA`，`_` 的位置不算），`CA` 对消意味着 `C` 和  `BA`  段对消，`AA` 对消意味着 `AB` 段和 `BA` 段对消。

然后我们直接枚举有多少元素属于 `AB` 或 `BA` 段，剩下的都是 `C`。

显然，`AB` 段和 `BA ` 段都不超过 $\lfloor \frac{n}2 \rfloor$，且若指定某些位置属于 `AB` 段，则填法唯一。

所以我们得出，总方案数为 $\sum^{m}_{A=0} \sum^m_{B=0}C^A_nC^B_{n-A}$，
其中 $m=\lfloor \frac{n}2 \rfloor$。

尝试化简：
$$\sum^{m}_{A=0} \sum^m_{B=0}C^A_nC^B_{n-A}$$
$$=\sum^{m}_{A=0}C^A_n \sum^m_{B=0}C^B_{n-A}$$
$$=\sum^{n}_{A=n-m}C^A_n \sum^m_{B=0}C^B_{A}$$
第二步本质就是$A \leftarrow n-A$。

那考虑求后面的那段。

令 $f_i=\sum^m_{B=0}C^B_{i}$

我们知道，$C^m_n=C^{m-1}_{n-1}+C^{m}_{n-1}$

则 
$$f_i=C^0_i+\sum^m_{B=1}(C^B_{i-1}+C^{B-1}_{i-1})$$
$$=C^0_i+2\sum^m_{B=0}C^B_{i-1}-C^0_{i-1}-C^m_{i-1}$$
$$=C^0_i+2f_{i-1}-C^0_{i-1}-C^m_{i-1}$$

发现可以递推。

于是我们直接在枚举 $A$ 的时候同时转移 $f_A$。

那么代码就显而易见了：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int P=998244353,N=1e7+10;
long long p[N],invp[N],n;
long long qpow(long long a,long long b)
{
	long long ans=1;
	while(b)
	{
		if(b&1)ans=ans*a%P;
		a=a*a%P,b>>=1;
	}
	return ans;
}
long long C(int n,int m)
{
	return p[n]*invp[m]%P*invp[n-m]%P;
}

int main()
{
	scanf("%lld",&n);
	p[0]=invp[0]=1;
	for(int i=1;i<=n;++i)
		p[i]=p[i-1]*i%P;
	invp[n]=qpow(p[n],P-2);
	for(int i=n;i;--i)
		invp[i-1]=invp[i]*i%P;
	long long ans=0;
//	for(int A=0;A<=n/2;++A)
//	{
//		long long t=0;
//		for(int B=0;B<=n/2;++B)
//			t+=C(n-A,B),(ans+=C(n,A)*C(n-A,B))%=P;
////		cout<<t<<"_"<<endl;
//	}
//	printf("%lld\n",ans);
	ans=0;
	long long s=0;
	for(int B=0;B<=n/2;++B)
		s+=C(n-n/2,B);
	s%=P;
	for(int A=n-n/2;A<=n;++A)
	{
		ans=(ans+s*C(n,A))%P;
//		cout<<s<<"_"<<endl;
		s=(s*2-C(A,0)+C(A+1,0)-C(A,n/2)+P+P)%P;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：GIFBMP (赞：1)

这题太过神仙了，所以写一篇题解来记录一下。

首先考虑只有 A,B 的情况。我们注意到题目中不能删 AB 或 BA 的限制很难处理，于是我们将奇数位的 A 变成 B，B 变成 A，易知此时新序列和原序列一一对应，那么条件就转化成了不能删掉相邻的 AA 或 BB。在序列中只有 A,B 的情况下，这个条件等价于只能删掉相邻的 AB 或 BA。于是我们考虑将此时的序列中 A 看成 $1$，B 看成 $-1$，我们可以发现，一个序列能被删空，当且仅当所有元素的和为 $0$，考虑证明：

充分性：当所有元素的和为 $0$ 时，要么序列为空，要么一定能找到一对相邻的 $1$ 和 $-1$ 删掉，删掉后所有元素的和不变，因此一定能将序列删空。

必要性：一次操作不会改变序列的元素和，由于最终状态的元素和为 $0$，因此能被删空的序列的元素和一定为 $0$。

接下来考虑 C 的情况，我们发现 C 可以看作 $1$ 或 $-1$。设 A 的数量为 $x$，B 的数量为 $y$，则 C 的数量为 $n-x-y$。由于 C 要使得元素和为 $0$，因此可以得出：$n-x-y\ge |x-y|$，即 $x+y-n\le x-y\le n-x-y$，解得 $x,y\le\dfrac{n}{2}$。那么问题转化为：将 $n$ 个数分成三组，其中两组的个数不超过 $\dfrac{n}{2}$ 的方案数。考虑容斥，答案即为：

$$3^n-2\times\sum_{i=\frac{n}{2}+1}^n C_{n}^i\times 2^{n-i}$$

时间复杂度 $\Theta(n)$。

Code:

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std ;
const int MAXN = 1e7 + 10 , mod = 998244353 ;
typedef long long ll ;
int n ;
ll qpow (ll x , ll p = mod - 2) {
	ll ret = 1 ;
	for (; p ; p >>= 1 , x = x * x % mod)
		if (p & 1) ret = ret * x % mod ;
	return ret ;
}
ll fac[MAXN] , inv[MAXN] , pw[MAXN] ; 
ll C (int x , int y) {
	return fac[x] * inv[y] % mod * inv[x - y] % mod ;
}
int main () {
	scanf ("%d" , &n) ;
	fac[0] = inv[0] = pw[0] = 1 ;
	for (int i = 1 ; i <= n ; i++) fac[i] = fac[i - 1] * i % mod , pw[i] = pw[i - 1] * 2 % mod ;
	inv[n] = qpow (fac[n]) ;
	for (int i = n - 1 ; ~i ; i--) inv[i] = inv[i + 1] * (i + 1) % mod ;
	ll ans = qpow (3 , n) , ret = 0 ;
	for (int i = n / 2 + 1 ; i <= n ; i++)
		ret = (ret + C (n , i) * pw[n - i] % mod) % mod ;
	ans = (ans - 2 * ret % mod + mod) % mod ;
	printf ("%lld\n" , ans) ;
	return 0 ;
}
```

---

## 作者：__Floze3__ (赞：0)

## 思路简述

这道题要用到一个 Trick：奇偶染色（我瞎胡的名字）。具体的，我们对于一个假想的字符串 $S$，把它偶数位上的 `A` 换成 `B`，`B` 换成 `A`，那么删除条件就转换为了：不能是两个 `A` 或 两个 `B` 一起删除。我们设 `A` 的个数为 $a$，`B` 的个数为 $b$，在不考虑 `C` 的情况下，最后会剩下 $|a - b|$ 个字符。设 `C` 的个数为 $c$，那么 $S$ 能够被完全删除的充要条件为 $c \ge |a - b|$。注意到 $c = N - a - b$，带入解得 $\max(a, b) \le \frac{N}{2}$。我们考虑容斥，计算 $a$ 或 $b$ 大于 $\frac{N}{2}$ 的字符串个数，因为同时只能满足一个条件，因此个数为 $2 \times \sum_{i = \frac{N}{2} + 1}^{N} \binom{N}{i} \times 2 ^ {N - i}$。最终答案即为 $3 ^ N - 2 \times \sum_{i = \frac{N}{2} + 1}^{N} \binom{N}{i} \times 2 ^ {N - i}$。

## 代码
[提交记录](https://atcoder.jp/contests/agc040/submissions/56454316)

---

## 作者：buowen123 (赞：0)

## 题目大意

给定偶数 $n(2 \le n \le 10^7)$，求有多少个长度为 $n$ 的由 `A`，`B`，`C` 组成的字符串 $s$，使得存在一种方案使得：

- 可以不断选择 $s$ 中任意除 `AB` 和 `BA` 外的长度为 $2$ 的子串并删除；
- 最后使得 $s$ 变为空串。

答案对 $998244353$ 取模。

## 题目解决

手搓几个样例，我们会发现：不满足要求的字符串**往往含有 `ABABAB` 这种结构。**

但是 `ABABBABA`，从中间开始消除就可以消完，`ABABCBABAB` 则不可以。

考虑这样一个字符串：

```plain
字符串:A  B  A  B  C  A  B  A  B  C  B  A  B  A
下标:  1  2  3  4  5  6  7  8  9 10 11 12 13 14
```

我们抽取 1 至 4 和 6 至 9 部分：`ABABCABAB`

把中间 `BC` 消掉：`ABAABAB`，此时两个 `A` 相邻，可以消除。

我们抽取 6 至 9 和 11 至 14 部分：`ABABCBABA`

把中间 `BC` 消掉：`ABABABA`，不能消除。

可以发现，对于前者，第一个 `ABAB` 中 `A` 在奇数位，第二个 `ABAB` 中 `A` 在偶数位；而对于后者，两个 `ABAB` 中 `A` 都在偶数位；

因此，如果两个形如 `ABAB` 的字符串**满足 `A` 的下标奇偶性相同**，才会导致**这两个字符串之间不可消除**。

那么我们将 `A` 在偶数下标的所有 `ABAB` 换成 `X`，反之换成 `Y`。

那么刚刚的字符串变为：

```plain
字符串:Y  Y  Y  Y  C  X  X  X  X  C  X  X  X  X
下标:  1  2  3  4  5  6  7  8  9 10 11 12 13 14
```

此时，只有 `XX` 和 `YY` 不可消除，因此 `X` 和 `Y` 的数量都不能超过一半。

那么为什么不超过一半是可以的呢？如果字符串只有 `C` 和 `X`，`X` 如果不超过一半，显然可以消完，`C` 和 `Y` 同理。又因为 `XY` 可以消除，所以整个字符串就能消除。

那这就好办了，统计 `X` 的数量超过一半有几种，`Y` 超过一半的数量直接乘以 $2$，最后用总数量相减即可，答案为

$$3^n-2\sum_{i=\frac n 2+1}^nC_n^{i}2^{n-i}$$

[code 戳这里。](https://www.luogu.com.cn/paste/jb12y64w)

---

