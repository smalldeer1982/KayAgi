# [ARC116D] I Wanna Win The Game

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc116/tasks/arc116_d

整数 $ N $ , $ M $ が与えられます。 長さ $ N $ の整数列 $ A $ であって、以下の条件を満たすものの数を答えてください。

- $ 0\ \leq\ A_i\ \left(i\ =\ 1,\ 2,\ \ldots,\ N\right) $
- $ \sum_{i\ =\ 1}^{N}\ A_i\ =\ M $
- $ A_1 $ xor $ A_2 $ xor $ \cdots $ xor $ A_N\ =\ 0 $ （ここで xor はビットごとの排他的論理和を表す）

ただし、答えは非常に大きくなる場合があるので、 $ 998244353 $ で割った余りを答えてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \leq\ N\ \leq\ 5000 $
- $ 1\ \leq\ M\ \leq\ 5000 $

### Sample Explanation 1

条件を満たす数列 $ A $ として、例えば以下のようなものが考えられます。 - $ A\ =\ \left(10,\ 0,\ 10,\ 0,\ 0\right) $ - $ A\ =\ \left(1,\ 2,\ 3,\ 7,\ 7\right) $

## 样例 #1

### 输入

```
5 20```

### 输出

```
475```

## 样例 #2

### 输入

```
10 5```

### 输出

```
0```

## 样例 #3

### 输入

```
3141 2718```

### 输出

```
371899128```

# 题解

## 作者：rui_er (赞：3)

考虑如何刻画子问题。假如我们知道了最后一位有多少个 $1$，就可以把所有数右移一位，并计算出此时新的目标和。而由于 $\oplus$ 运算每一位的独立性，此时新的目标异或和依然是 $0$。因此，更小的目标和是这一问题的子问题。

基于上述观察，我们设 ${dp}_i$ 表示数列长度为 $n$，元素和为 $i$，元素异或和为 $0$ 的方案数。我们枚举最后一位 $1$ 的个数 $j$，可以得到转移方程：

$$
{dp}_i=
\begin{cases}
0,&2\nmid i\\
\sum\limits_{j=0}^{\min\{n,i\}}[2\mid j]\binom{n}{j}{dp}_{\frac{i-j}{2}},&2\mid i\\
\end{cases}
$$

初始值是 ${dp}_0=1$，答案为 ${dp}_m$。

复杂度 $\mathcal O(n^2)$（$n,m$ 视为同阶）。

```cpp
//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(ll x=(y);x<=(z);x++)
#define per(x,y,z) for(ll x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;
const ll N = 5e3+5, mod = 998244353;

ll n, m, fac[N], ifac[N], dp[N];
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}
ll C(ll x, ll y) {
	if(x < 0 || y < 0 || x < y) return 0;
	return fac[x] * ifac[y] % mod * ifac[x-y] % mod;
}

int main() {
	scanf("%lld%lld", &n, &m);
	fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
	rep(i, 2, N-1) {
		fac[i] = fac[i-1] * i % mod;
		ifac[i] = (mod - mod / i) * ifac[mod%i] % mod;
	}
	rep(i, 1, N-1) ifac[i] = ifac[i-1] * ifac[i] % mod;
	dp[0] = 1;
	for(ll i = 2; i <= m; i += 2) {
		for(ll j = 0; j <= min(n, i); j += 2) {
			dp[i] += dp[(i-j)>>1] * C(n, j) % mod;
			dp[i] %= mod;
		}
	}
	printf("%lld\n", dp[m]);
	return 0;
}
```

---

## 作者：2huk (赞：2)

## Description

给定 $n, m$，问有多少个长度为 $n$ 的序列 $a$ 满足：

- $a_i \ge 0$；
- $\sum_{i = 1}^n a_i = m$；
- $\bigoplus_{i = 1}^n a_i = 0$。

$1 \le n, m \le 5000$。

## Solution

既然 $a_i$ 的异或和为 $0$，那么就代表每一个二进制位都出现过偶数次。

设状态 $f_{i, j}$ 表示只考虑前 $i$ 个二进制位，且总和为 $j$ 的方案数。那么我们考虑枚举有多少个 $a_p$ 的第 $i$ 个二进制位为 $1$。不妨设为 $k$ 个，根据上面说的，$k$ 必须为偶数。

那么显然 $k$ 的贡献为 $f_{i - 1, j - 2^{i - 1}k}$，其中 $2^{i - 1}k$ 表示 $k$ 个第 $i$ 个二进制位的价值和。

然后转移即可。答案显然为 $f_{20, m}$（$\log m \sim 2$）。时间复杂度 $\mathcal O(nm\log m)$。

## Code

[Submission #48359227 - AtCoder Regular Contest 116](https://atcoder.jp/contests/arc116/submissions/48359227)



---

## 作者：菲斯斯夫斯基 (赞：2)

## AT_arc116_d [ARC116D] I Wanna Win The Game 题解

果然 AtCoder 还是很擅长出 dp 的，简短的题面但思路却不简单。

题意明了，不再赘述。

异或和还是一个不错的入手方向，异或有两个很重要的性质：

+ $a\oplus a=0$

+ $a\oplus 0=a$

但可惜的是，这题都用不了。

所以只能一位一位用二进制来操作和转移了。

定义 $dp_{i,j}$ 为前 $i$ 位二进制已经处理完，和为 $j$ 的方案数。

考虑怎样转移。

异或和为 $0$，那么每一位二进制出现的次数都为偶数。

所以再枚举一层 $k$，意思是这一位出现的次数为 $k$。

因为当前在操作第 $i$ 位，所以这一位的权值为 $2^i$。出现了 $k$ 次，和就为 $k\times 2^i$。

那么就很好转移了，动态转移方程：

$$\large dp_{i,j}=\sum\limits_{k=0}^{n}[2\mid k]dp_{i-1,j-k\times 2^i}\times\dbinom{n}{k}$$

注意转移时要保证 $j-k\times 2^i\ge0$。

其中 $\dbinom{n}{k}$ 为组合数，意思是在 $n$ 个数中选 $k$ 个有多少种方案，在选择的数中的第 $i$ 位为 $1$。所以还要用逆元来搞，还是比较麻烦的。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5010,mod=998244353;
int n,m;
int dp[50][N],fac[N],inv[N];
int qpow(int x,int y)
{
	int ans=1;
	while(y)
	{
		if(y%2)ans*=x,ans%=mod;
		x*=x,x%=mod,y/=2;
	}
	return ans;
}//快速幂
int C(int x,int y)
{
	return fac[x]*inv[y]%mod*inv[x-y]%mod;
}//求组合数
signed main()
{
	cin>>n>>m;
	fac[0]=inv[0]=1;
	for(int i=1;i<=n;i++)
	{
		fac[i]=fac[i-1]*i%mod;
		inv[i]=qpow(fac[i],mod-2);//求逆元
	}
	for(int j=0;j<=min(m,n);j+=2)
		dp[0][j]=C(n,j);//初始化
	for(int i=1;i<=20;i++)
		for(int j=0;j<=m;j++)
			for(int k=0;k<=n;k+=2)
				if(j-k*(1ll<<i)>=0)dp[i][j]+=dp[i-1][j-k*(1ll<<i)]*C(n,k),dp[i][j]%=mod;//转移，别忘了模
				else break;//小于0直接退出
	cout<<dp[20][m];
	return 0;
}

```

---

## 作者：Mingrui_Yang (赞：1)

## 题意

给定 $n,m$，问有多少个长度为 $n$ 的序列 $a$ 满足：

1. $0\leq a_i$
2. $\sum_{i=1}^n a_i=m$
3. $a_1\bigoplus a_2\bigoplus a_3\cdots =0$

- $1\le n,m\le 5000$

## 思路

> 看见异或，必然想到二进制位。

考虑 DP。

定义 $f_{i, j}$ 表示二进制位从高位到低位的前 $i$ 位已确定且前 $i$ 的和为 $j$ 的总方案数。   

设计状态转移方程：   
因为 $a_1\bigoplus a_2\bigoplus a_3\cdots =0$，所以对于所有的 $a$ 来说，每一位的 $1$ 的个数和一定为偶数。   
在枚举第 $i$ 位时，只需要枚举 $1$ 的个数 $k$，且 $k$ 一定为偶数，这 $k$ 个 $1$ 对总和的贡献为 $k \times 2^{i - 1}$（第 $i$ 二进制位的位权为 $2^{i - 1}$）。

所以状态转移方程为
$$
f_{i, j} = \sum_{l = 0}^{\lfloor \frac{n}{2} \rfloor} f_{i - 1, j - 2l \times 2^{i - 1}} \binom{n}{k}
$$
其中的 $2l$ 即为满足条件的 $k$。   
因为 $k$ 个 $1$ 是从 $n$ 个数的 $n$ 个第 $i$ 位中选出来的，所以乘上组合数 $\binom{n}{k}$。

## CODE

```cpp
#include <bits/stdc++.h>
#define int long long 
#define ADD(a, b) (((a) += (b)) %= Mod)
#define MUL(a, b) (((a) *= (b)) %= Mod) 
using namespace std;
const int N = 5010;
const int Mod = 998244353;
int n, m;
int f[20][N]; // m的二进制位数不会超过19 
int fact[N], infact[N]; // fact[i]表示 i!  infact[i]表示 i!的逆元 
int qmi(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) res = res * a % Mod;
		b >>= 1;
		a = a * a % Mod;
	}
	return res;
}
void init() {
	fact[0] = 1;
	for (int i = 1; i < N; i ++ ) fact[i] = fact[i - 1] * i % Mod;
	infact[N - 1] = qmi(fact[N - 1], Mod - 2);
	for (int i = N - 2; i >= 0; i -- ) infact[i] = infact[i + 1] * (i + 1) % Mod;
}
int C(int m, int n) { // 求组合数 
	if (n < 0 || m < 0 || n > m) return 0;
	return fact[m] * infact[m - n] % Mod * infact[n] % Mod;
}
signed main() {
	init(); // 处理阶乘及其逆元 
	cin >> n >> m;
	f[0][0] = 1; // 起点 
	for (int i = 1; i < 20; i ++ ) // 枚举二进制位数 
		for (int j = 0; j <= m; j ++ ) // 枚举总和 
			for (int k = 0; k <= n; k += 2) { // k为偶数 
				int w = k * (1 << (i - 1)); // k个1对总和的贡献 
				if (j >= w) ADD(f[i][j], f[i - 1][j - w] * C(n, k)); // 状态转移 
			}
	cout << f[19][m] << endl; // 输出答案 
	return 0;
}

```

---

## 作者：analysis (赞：0)

容易想到拆二进制位。

设 $f_{i,j,k}$ 为只考虑最高位到第 $i$ 位，第 $i$ 位有 $j$ 个 $1$，和为 $k$ 的方案数。

同时维护 $s_{i,k}$：

$$
s_{i,k} = \sum_{j}f_{i,j,k}
$$

就有：

$$
f_{i,j,k} = \sum_{l=0}^{n}f_{i+1,l,k - j2^i} \times \begin{pmatrix}n\\j\end{pmatrix} = s_{i+1,k-j2^i} \times \begin{pmatrix}n\\j\end{pmatrix}
$$

时间复杂度是 $O(n^2log{m})$ 的。

注意代码实现时压去第一维节省空间。

```cpp
#include <bits/stdc++.h>
#define int long long
const int mod = 998244353;
using namespace std;
int n, m;
int f[5005][5005],s[5005];
int c[5005], pw[20];
int fpow(int a, int b = mod - 2)
{
    int r = 1;
    while (b)
    {
        if (b & 1)
            r = r * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return r;
}
void clsf()
{
    for(int j=0;j<=n;j+=2)
    {
        for(int v=0;v<=m;v++)
        {
            f[j][v] = 0;
        }
    }
}
void clss()
{
    for(int v=0;v<=m;v++)s[v]=0;
}
signed main()
{
    cin >> n >> m;
    pw[0] = c[0] = 1;
    for (int i = 1; i <= 15; i++)
        pw[i] = pw[i - 1] * 2 % mod;
    for (int i = 1; i <= n; i++)
    {
        c[i] = c[i - 1] * (n - i + 1) % mod * fpow(i) % mod;
    }
    for (int j = 0,v = 0; j <= n && v <= m; j += 2,v+=pw[15])
    {
        s[v] = (s[v] + c[j]) % mod;
    }
    for (int i = 13; i >= 0; i--)
    {
        clsf();
        for(int j=0,v=0;j<=n && v<=m;j+=2,v+=pw[i+1])
        {
            for(int va=0;va<=m - v;va++)
            {
                f[j][va+v] = (f[j][va+v] + s[va] * c[j] % mod) % mod;
            }
        }
        clss();
        for(int j=0,v=0;j<=n && v<=m;j+=2,v+=pw[i+1])
        {
            for(int va=0;va<=m;va++)
            {
                s[va] = (s[va] + f[j][va]) % mod;
            }
        }
    }
    cout<<s[m];
    return 0;
}
```

---

## 作者：WaterSun (赞：0)

# 思路

因为题目与二进制有关，考虑往二进制的方向思考。定义 $dp_{i,j}$ 表示在所有的 $n$ 个数中，当前在决策对于每一个数在二进制表示下的第 $i$ 位是 $0$ 还是 $1$，且和为 $j$ 的方案数。

因为异或需要满足对于所有 $a_i$ 表示为二进制后每一位 $1$ 的个数均为偶数。所以在所有数中第 $i$ 位出现 $1$ 的数量必须是偶数。

那么，我们还可以枚举一个 $k$ 表示所有数中第 $i$ 位选 $1$ 的数量，得到状态转移方程：

$$
dp_{i,j} = \sum_{k = 0}^{j \geq k \times 2^i}(dp_{i - 1,j - k \times 2^i} \times \binom{n}{k})
$$

时间复杂度为 $\Theta(m \log^2{m})$。

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

const int N = 5010,M = 15,mod = 998244353;
int n,m;
int mul[N],inv[N];
int dp[M + 10][N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline int Add(int a,int b){
	return (a + b) % mod;
}

inline int Sub(int a,int b){
	return ((a - b) % mod + mod) % mod;
}

inline int Mul(int a,int b){
	return a * b % mod;
}

inline int exgcd(int a,int b,int &x,int &y){
	if (!b){
		x = 1;
		y = 0;
		return a;
	}
	int d = exgcd(b,a % b,y,x);
	y = y - a / b * x;
	return d;
}

inline int get_inv(int a,int p){
	int x,y;
	exgcd(a,p,x,y);
	return (x % mod + mod) % mod;
}

inline void init(){
	mul[0] = 1;
	for (re int i = 1;i <= n;i++) mul[i] = Mul(mul[i - 1],i);
	inv[n] = get_inv(mul[n],mod);
	for (re int i = n - 1;~i;i--) inv[i] = Mul(inv[i + 1],(i + 1));
}

inline int C(int n,int m){
	if (n < m) return 0;
	return Mul(mul[n],Mul(inv[m],inv[n - m]));
}

signed main(){
	n = read();
	m = read();
	init();
	for (re int i = 0;i <= m;i += 2) dp[0][i] = C(n,i);
	for (re int i = 1;i <= M;i++){
		for (re int j = 0;j <= m;j++){
			int k = 0;
			while (j >= k * (1ll << i)){
				dp[i][j] = Add(dp[i][j],Mul(dp[i - 1][j - k * (1ll << i)],C(n,k)));
				k += 2;
			}
		}
	}
	printf("%lld",dp[M][m]);
	return 0;
}
```

---

