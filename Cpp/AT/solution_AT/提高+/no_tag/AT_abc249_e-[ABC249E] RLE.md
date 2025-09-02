# [ABC249E] RLE

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc249/tasks/abc249_e

英小文字のみからなる文字列 $ X $ に対し、以下の手続きによって文字列を得ることを考えます。

- $ X $ を異なる文字が隣り合っている部分で分割する。
- 分割した各文字列 $ Y $ に対して、$ Y $ を $ Y $ を構成する文字と $ Y $ の長さを繋げた文字列に置き換える。
- 元の順番を保ったまま、置き換えた文字列をすべて繋げる。

例えば、`aaabbcccc` の場合、`aaa`,`bb`,`cccc` に分けられ、それぞれを `a3`,`b2`,`c4` に置き換え、その順番のまま繋げることにより `a3b2c4` を得ます。また、`aaaaaaaaaa` の場合、`a10` になります。

長さ $ N $ の英小文字のみからなる文字列 $ S $ のうち、上記の手続きによって得られた文字列 $ T $ との長さを比べたとき、$ T $ の方が短いものの個数を $ P $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- $ 1\ \le\ N\ \le\ 3000 $
- $ 10^8\ \le\ P\ \le\ 10^9 $
- $ N,P $ は整数
- $ P $ は素数

### Sample Explanation 1

$ 1,2,3 $ 文字目が全て等しい文字列のみが条件を満たします。 例えば、`aaa` は `a3` となり条件を満たしますが、`abc` は `a1b1c1` となり条件を満たしません。

### Sample Explanation 2

`aa` → `a2` のように、長さが等しいものは条件を満たさないことに注意してください。

### Sample Explanation 3

`aaabb` や `aaaaa` などが条件を満たします。

### Sample Explanation 4

条件を満たす文字列の個数を $ P $ で割ったあまりを求めてください。

## 样例 #1

### 输入

```
3 998244353```

### 输出

```
26```

## 样例 #2

### 输入

```
2 998244353```

### 输出

```
0```

## 样例 #3

### 输入

```
5 998244353```

### 输出

```
2626```

## 样例 #4

### 输入

```
3000 924844033```

### 输出

```
607425699```

# 题解

## 作者：uid_310801 (赞：1)

设 $dp_{i,j}$ 表示考虑前 $i$ 个字符压缩后长度为 $j$ 的方案数，转移时，枚举最靠后的连续段的长度，并钦定之前的一个字符与当前字符不同。

可以得到显然的转移式子：

$$dp_{i,j}=\sum_{k<i}dp_{k,j-\log_{10}(i-k)-1}\times 25$$

初值是 $dp_{0,0}=1$。

但是第一个字符可以填的种类数并不是 $25$ 种，所以我们需要将最终答案乘上 $\frac{26}{25}$。

直接做是 $O(n^3)$ 的，考虑把 $\log_{10}(i-k)$ 相同的放在一起，就能使用前缀和优化了。

小细节：求前缀和时可以单独写一个函数来计算，就不用担心溢出的事情了。

时间复杂度 $O(n^2\log_{10}n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define deb(x) cerr<<"Line: "<<__LINE__<<", val= "<<x<<"; \n"
typedef long long ll;
#define pii pair<ll,ll>
#define mp make_pair
#define fi first
#define se second
/* 
dp[i][j]表示前i个数长度为j的方案数
dp[i][j]=sum(k<i)dp[k][j-1-log10(i-k)]*25
*/
const ll N=3e3+10;
ll mod;
ll qpow(ll a,ll b){
	ll ans=1,base=a;
	while(b){
		if(b&1)	ans=ans*base%mod;
		base=base*base%mod;
		b>>=1;
	}
	return ans;
}
ll n,ans;
ll dp[N][N],sum[N][N],p[10];
ll get(ll l,ll r,ll k){//求前缀和时可以单独写一个函数来计算，就不用担心溢出的事情了。
	if(l>r||r<0||k<0)	return 0;
	if(l<=0)	return sum[r][k];
	return (sum[r][k]-sum[l-1][k]+mod)%mod;
}
signed main(){
	p[0]=1;
	for(int i=1;i<10;i++)	p[i]=p[i-1]*10;
	scanf("%lld %lld",&n,&mod);
	sum[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<n;j++){
			for(int k=1;k<=4;k++){
				(dp[i][j]+=get(i-p[k]+1,i-p[k-1],j-k-1)*25)%=mod;
			}
			sum[i][j]=(sum[i-1][j]+dp[i][j])%mod;
			if(i==n)	(ans+=dp[i][j])%=mod;
		}
	}
	printf("%lld\n",ans*26%mod*qpow(25,mod-2)%mod);
	return 0;
}
/*
exSample:
---------
:elpmaSxe
     */
```


---

## 作者：ran_qwq (赞：0)

约定 $L(x)=\log_{10}x+1$。

首先考虑一个 $O(n^3|\Sigma|^2)$ 的 dp：$dp_{i,j,c}$ 表示原串前 $i$ 个字符对应新串前 $j$ 个字符，且当前段字符为 $c$。转移枚举当前段的起点 $k$ 和上一段字符 $d$，有状态转移方程

$$dp_{i,j,c}\rightarrow dp_{i,j,c}+dp_{k-1,j-L(i-k+1),d}\cdot[c\ne d]$$

还要考虑字符是什么太唐了，字符是什么不影响结果，只用保证相邻段字符不同就可以了。所以转移系数为 $25+[k=1]$，即

$$dp_{i,j}\rightarrow dp_{i,j}+dp_{k-1,j-L(i-k+1))}\cdot(25+[k=1])$$

注意到 $L(i-k+1)$ 很小，范围为 $1\sim4$，所以可以枚举第二维而不是第一维，求出对应的第一维范围，用前缀和优化 dp。

---

## 作者：WaterSun (赞：0)

# 思路

定义 $dp_{i,j}$ 表示在前 $i$ 位原字符串，压缩为 $j$ 位的方案数。

不难得出状态转移方程：

$$
dp_{i,j} = \sum_{k = 1}^{i}(25 \times dp_{k,j - \lfloor \log_{10}k \rfloor - 1})
$$

这样搞是 $\Theta(n^3)$ 的，所以考虑优化。

不难发现 $\log_{10}k$ 是很小的，所以考虑来枚举 $k$，得到新的状态转移方程：

$$
dp_{i,j} = 25 \times (\sum_{k = 0}^{\lfloor \log_{10}k \rfloor}\sum_{p = i - 10^k + 1
}^{i - 10^{k - 1}}dp_{p,p - k - 1})
$$

然后最后的那个 $\sum$ 可以用前缀和优化一下，时间复杂度为 $\Theta(n^2\log_{10}n)$。

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

const int N = 3010;
int n,mod,ans;
int pt[] = {1,10,100,1000,10000};
int dp[N][N],s[N][N];

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

inline int sum(int l,int r,int k){
	if (l > r || r < 0 || k < 0) return 0;
	if (l <= 0) return s[r][k];
	return ((s[r][k] - s[l - 1][k]) % mod + mod) % mod;
}

signed main(){
	n = read();
	mod = read();
	dp[0][0] = s[0][0] = 1;
	for (re int i = 1;i <= n;i++){
		for (re int j = 0;j < n;j++){
			for (re int k = 1;k <= 4;k++) dp[i][j] = (dp[i][j] + sum(i - pt[k] + 1,i - pt[k - 1],j - k - 1) * 25) % mod;
			s[i][j] = (s[i - 1][j] + dp[i][j]) % mod;
		}
	}
	for (re int i = 0;i < n;i++) ans = (ans + dp[n][i]) % mod;
	printf("%lld",ans * get_inv(25,mod) % mod * 26 % mod);
	return 0;
}
```

---

## 作者：Tsawke (赞：0)

# [[ABC249E] RLE](https://www.luogu.com.cn/problem/AT_abc249_e) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC249E)

## 题面

给定一种字符串压缩算法：对于连续的相同字母，会压缩成 该字母 + 出现次数 的形式，例如 `aaabbcccc` 会被压缩成 `a3b2c4`，`aaaaaaaaaa` 会被压缩成 `a10`。

字符集为英文小写字母，给定 $ n, p $，求对于所有长度为 $ n $ 的字符串，有多少满足压缩后的字符串长度严格小于原字符串。对 $ p $ 取模。保证 $ p $ 为质数。

## Solution

DP 比价显然。考虑状态，设 $ dp(i, j) $ 表示考虑前 $ i $ 个字符，压缩后长度为 $ j $ 的方案数。

考虑转移，显然对于某个状态的 $ i $ 可以从前面所有长度小于它的 $ k $ 转移而来，并且钦定 $ [k, i] $ 是相同的，且与 $ k - 1 $ 不同。所以转移的时候还需要考虑那一段压缩后的长度，也就是 $ \log_{10} $。显然有：
$$
dp(i, j) = \sum_{k = 1}^{i}dp(k - 1, j - \log_{10}^{i - k + 1} - 1) \times 25
$$
这个东西显然是可以前缀和优化的，注意因为第二维的状态，所以要按照 $ \log_{10}^{i - k + 1} $ 做，最后的复杂度 $ O(n^3) \longrightarrow O(n^2 \log n) $，且 $ \log $ 是以 $ 10 $ 为底的，可以通过。

然后这里我们要注意 $ dp(1, x) $ 的时候这个东西是可以取到 $ 26 $ 个字符的，而不是 $ 25 $，所以这里有个小 trick，因为是模意义下的且模数为质数，所以可以直接求个逆元然后令 $ dp(0, 0) = \dfrac{26}{25} \bmod{p} $，这样转移的时候就可以直接按照柿子无脑写了，当然在具体实现的时候，还是推荐直接初始化 $ dp(i, \log_{10}^i) $，这样虽然会使代码略显冗长，但是也会更直观，好调。

这里还有两个易错点，一个是注意枚举状态的时候应为 $ j \le n $ 而非 $ j \lt i $，因为 $ j \ge i $ 的虽然在当前是不合法的，但是转移到后面之后会因被压缩而变得合法，所以也需要记录。

另一个易错点是中间我们会需要求一次 $ \log $，这个东西因为数据范围较小，建议直接枚举手写，不过如果非要像我一样用浮点运算，建议直接用库里的 `log10`，如果一定要用换底做的话记得用 `long double`，我最开始写的 `#define log10(x) (int(log((double)x) / log(10.0)) + 1)`，然后这个东西因为精度问题会出现 $ \operatorname{log10}(1000) = 3 $，找了好久才发现是这个的问题。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

#define log10_(x) (int(logl((ld)x) / logl((ld)10.0)) + 1)

template < typename T = int >
inline T read(void);

int N, MOD;
ll ans(0);
ll dp[3100][3100];
ll sum[3100][3100];
int pow10[5] = {1, 10, 100, 1000, 10000};

int main(){
    N = read(), MOD = read();
    for(int i = 1; i <= N; ++i){
        dp[i][(int)log10(i) + 2] = 26;
        for(int j = 1; j <= N; ++j){
            for(int len = 0; len <= 3; ++len)
                if(i >= pow10[len] && j - 2 - len > 0)
                    (dp[i][j] += ((sum[i - pow10[len]][j - 2 - len] - sum[max(i - pow10[len + 1], 0)][j - 2 - len] + MOD) % MOD * 25ll % MOD)) %= MOD;
            sum[i][j] = (sum[i - 1][j] + dp[i][j]) % MOD;
        }
    }
    for(int i = 1; i < N; ++i)(ans += dp[N][i]) %= MOD;
    printf("%lld\n", ans);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2022_11_30 初稿

---

## 作者：wcyQwQ (赞：0)

设 $f_{i, j}$ 为前 $i$ 位压缩后长度为 $j$ 的方案数，枚举最后一段极长连续段 $[k, i]$ 可得转移方程
$$
f_{i, j} = \sum_{k = 1}^i 25 \cdot f_{k - 1, j - \lfloor{\log_{10}(i - k + 1)}\rfloor - 2}
$$
初始化为 $f_{i, \lfloor\log_{10} i\rfloor + 2} = 26$。这样直接写是 $O(n ^ 3)$ 的。但是我们发现 $\lfloor{\log_{10}(i - k + 1)}\rfloor$ 的值域很小，所以我们考虑枚举这个东西，这样转移方程就变为
$$
f_{i, j} = 25\sum_{k = 0}^{\lfloor\log_{10} i\rfloor}\sum_{l = i - 10^{k + 1} + 1}^{i - 10^k} f_{l, j - k - 2}
$$
第二个和式用前缀和维护即可，时间复杂度 $O(n^2\log_{10}{n})$。[Code](https://atcoder.jp/contests/abc249/submissions/42872858)

---

