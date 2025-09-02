# [ABC309G] Ban Permutation

## 题目描述

求长为 $N(N\leq 100)$ 且满足以下条件的排列 $P=(P_1,P_2,...,P_N)$ 的个数：

- $\forall 1\leq i\leq N$，$|P_i-i|\geq X(X\leq 5)$。

## 样例 #1

### 输入

```
3 1```

### 输出

```
2```

## 样例 #2

### 输入

```
5 2```

### 输出

```
4```

## 样例 #3

### 输入

```
98 5```

### 输出

```
809422418```

# 题解

## 作者：Miraik (赞：17)

不要容斥，考虑暴力。

考虑终状态看作两边各有 $n$ 的点的二部图做完美匹配，左部的 $i$ 向右部的 $p_i$ 连边。

于是问题转化为统计这样的完美匹配二部图个数，满足每条边的两个点在坐标上的跨度要大于 $X$。

考虑沿着坐标顺着扫过去，每一对匹配在坐标更大的那个点统计。设计一个 dp 状态：$f_{i,j,s}$ 表示扫到坐标 $i$，目前已经匹配 $j$ 对点，坐标处于 $[i-X+2,i]$ 的点是否匹配的状态为 $s$。直接转移是 $O(1)$ 的，总时间复杂度 $O(n^2 4^{X-1})$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
int n,m,S,T1,T2,f[105][105][256];
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin>>n>>m; S=(1<<2*m-2)-1; f[0][0][S]=1;
	for(int i=0;i<2*m-2;i+=2) T1|=1<<i; for(int i=1;i<2*m-2;i+=2) T2|=1<<i;
	for(int i=0;i<n;i++)
		for(int j=0;j<=i;j++)
			for(int s=0;s<=S;s++){
				if(!f[i][j][s]) continue;
				int A=i-j-__builtin_popcount(S^(s&T1|T2)),B=i-j-__builtin_popcount(S^(s&T2|T1));
				f[i+1][j][s<<2&S]=(f[i+1][j][s<<2&S]+f[i][j][s])%mod;
				f[i+1][j+1][(s<<2|1)&S]=(f[i+1][j+1][(s<<2|1)&S]+1ll*B*f[i][j][s])%mod;
				f[i+1][j+1][(s<<2|2)&S]=(f[i+1][j+1][(s<<2|2)&S]+1ll*A*f[i][j][s])%mod;
				f[i+1][j+2][(s<<2|3)&S]=(f[i+1][j+2][(s<<2|3)&S]+1ll*A*B*f[i][j][s])%mod;
			}
	cout<<f[n][n][S]<<'\n';
	return 0;
}
```


---

## 作者：EuphoricStar (赞：14)

前置知识：[[ARC132C] Almost Sorted](https://www.luogu.com.cn/problem/AT_arc132_c)

看 $\ge X$ 不顺眼，怎么办呢！直接容斥！

钦定 $j$ 个位置满足 $|P_i - i| < X$，其余任意，就转化成了 [[ARC132C] Almost Sorted](https://www.luogu.com.cn/problem/AT_arc132_c)。

具体一点就是，你设 $f_{i, j, S}$ 表示前 $i$ 位有 $j$ 个位置满足 $|P_i - i| < X$，然后 $i - (X - 1) \sim i + (X - 1)$ 的覆盖情况为 $S$（状压），作用是你填 $P_i$ 时知道哪些数已经被填过了。转移讨论是否钦定 $|P_i - i| < X$ 即可，若钦定 $|P_i - i| < X$ 还要枚举 $P_i$。注意一些边界的处理。

答案是 $\sum\limits_{i = 0}^n \sum\limits_S f_{n, i, S} \times (-1)^i \times (n - i)!$，$(-1)^i$ 是容斥系数，还要乘 $(n - i)!$ 是因为除这 $i$ 个数以外的所有数可以随便排。

时间复杂度 $O(n^2 4^{X} X)$。

[code](https://atcoder.jp/contests/abc309/submissions/43406929)

---

## 作者：Tibrella (赞：5)

[更好的阅读体验](https://blog.tibrella.space/post/abc309g-solution/)

## 前置知识

- [二项式反演](https://blog.tibrella.space/post/binomial-inversion/)
- 状压 DP

## 符号约定

$\lor$ 为逻辑或，相当于 C++ 中的 `|` 运算符。  

## 题意简化

求 $n$ 的排列 $P$ 的方案数，要求 $\lvert P_i - i \rvert \geqslant X$。

## 分析

排列问题有点抽象，于是有套路：把一个排列看成 $n\times n$ 的棋盘上放车的方案——数字 $p_i$ 在 $i$ 的位置上，相当于棋盘的 $(i,p_i)$ 位置放了一个车。显然 $i,p_i$ 都不会重复，所以正确。

然后发现是个计数题，给出了**不合法**的条件，而且条件与位置相关，往二项式反演方向思考。

按照套路，设 $g_i$ 为钦定 $i$ 个数不合法，其他随便排的方案数，$f_i$ 为恰好 $i$ 个数不合法的方案数。发现每个 $g_i$ 包含 $f_j,j\in[i,n]$，然后每次选择不同的 $i$ 个数进行钦定，所以一个 $f_j$ 要算 $\binom ji$ 次。于是有：

$$
g_i=\sum_{j=i}^n f_i \binom ji
$$

脸上都写上二项式反演这五个字了，套一下式子，有：

$$
f_i = \sum_{j=i}^n(-1)^{j-i}\binom ji g_j
$$

答案即为：

$$
\begin{aligned}
ans &= f_0 \\
    &= \sum_{j=0}^n(-1)^{j-0}\binom j0 g_j \\
    &= \sum_{j=0}^n(-1)^j g_j
\end{aligned}
$$

考虑怎么求 $g_i$。

回过头来看不合法的条件：$\lvert P_i - i \rvert < X$，转化为 $P_i$ 这个棋子不能放在 $[i-X+1,i+X-1]$ 这些横行上。

发现 $X\leqslant 5$，非常小，也许可以状压？结合上面的转化，如果要状压的话，状态可以直接表示 $[i-X+1,i+X-1]$ 中不合法棋子的集合。

然后 DP 状态设计就有了（这里我们开出来一个新的 $f$ 数组）：$f_{i,j,s}$ 表示棋盘前 $i$ 行，放了 $j$ 个不合法棋子，状态为 $s$ 的方案数量。

怎么转移？假设当前是 $f_{i,j,s}$，然后分类讨论：

- 不放新的不合法棋子。
  发现这种情况下转移到 $i+1$ 时，新状态就是 $s$ 右移一位，即 $2^{-1}s$。
  为了方便，我们设这个状态为 $ns$，表示什么都不放时转移到 $i+1$ 时的状态。
  转移方程也就简单了：$f_{i,j,ns} \gets (f_{i,j,ns}+f_{i,j,s})$
- 放新的不合法棋子。
  可以枚举一下这个不合法棋子能放到的位置（就是 $[i-X+1,i+X-1]$ 区间的空位），直接转移即可。但是注意，当前要做的是向后转移，所以应当枚举的是 $ns$ 这个状态的空位。假设 $p$ 是一个空位，则有转移方程：$f_{i,j,(ns\lor 2^p)} \gets (f_{i,j,(ns\lor 2^p)}+f_{i,j,s})$。

对于 $g_i$，由于是钦定了 $i$ 个位置不合法，其他位置随便排，所以我们对 $f_{n,i,s}$ 枚举 $s$ 求和之后，还要乘一个 $(n-i)!$ 满足“剩下位置随便排列”的要求。

按照前面 $ans$ 的式子求和即可。

时间复杂度 $\operatorname\Theta(4^Xn^2)$。

Code:

```rust
use std::io;

fn valid(pos: usize, i: usize, n: usize, x: usize) -> bool {
    ((i + pos + 1 - x) <= n && (i + pos + 1 - x) > 0) as bool
}

fn main() {
    const MD: usize = 998244353;
    const N: usize = 205;
    const ST: usize = 600;
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let mut s = input.trim().split(' ');

    let n: usize = s.next().unwrap().parse().unwrap();
    let x: usize = s.next().unwrap().parse().unwrap();

    let mut f = [[[0; ST]; N]; N];

    let mxst: usize = (1 << ((x << 1) - 2 + 1)) - 1; // 区间长度本来是 (x << 1) - 2，但是还要包含 i 本身，所以 + 1

    f[0][0][0] = 1;
    for i in 1..=n {
        for j in 0..=i - 1 {
            for s in 0..=mxst {
                let ns: usize = s >> 1;
                f[i][j][ns] = (f[i][j][ns] + f[i - 1][j][s]) % MD;
                for p in 0..=(x << 1) - 2 {
                    if ((1 << p) & ns) == 0 && valid(p, i, n, x) {
                        f[i][j + 1][ns | (1 << p)] =
                            (f[i][j + 1][ns | (1 << p)] + f[i - 1][j][s]) % MD
                    }
                }
            }
        }
    }

    let mut fact = [0; N];
    fact[0] = 1;
    for i in 1..=n {
        fact[i] = fact[i - 1] * i % MD;
    }

    let mut ans: i64 = 0;
    for i in 0..=n {
        for s in 0..=mxst {
            if i & 1 == 1 {
                ans -= (f[n][i][s] * fact[n - i] % MD) as i64;
            } else {
                ans += (f[n][i][s] * fact[n - i] % MD) as i64;
            }
            ans %= MD as i64;
        }
    }
    ans = (ans % MD as i64 + MD as i64) % MD as i64;
    println!("{}", ans);
}
```

---

## 作者：Gorenstein (赞：4)

首先，众所周知地，有限制的排列计数问题可以转化为带禁止位棋盘的車的放置问题。

题目的限制是 $|P_i-i|\geqslant X$，它不便于直接求得。但因 $X\leqslant 5$，故在类似 $|P_i-i|\leqslant X$ 的限制下是易求的，因为我们有复杂度可以接受的状压。因此考虑容斥。

众所周知地，设 $r_k$ 为只取 $k$ 个車放入棋盘且全部在禁止位的方案数，那么 $r_k(n-k)!$ 就是钦定 $i$ 个車处于禁止位的方案数。我们要算出的是恰好 $0$ 个車在禁止位的方案数，它就是：

$$
\sum_{k=0}^n(-1)^kr_k(n-k)!
$$

$r_k$ 只需状压即可求出。设 $f_{i,j,S}$ 表示往前 $i$ 行的禁止位放入 $j$ 个車，第 $i$ 行状况为 $S$ 的方案数，其中 $S$ 的某一位为 $1$ 表示该位不能放置。

从第 $i$ 行扩展到 $i+1$ 行，初始状况为 $S\!>\!\!>\!1$。转移为：

$$
f_{i+1,j,S\!>\!\!>\!1}\;\longleftarrow\;f_{i+1,j,S\!>\!\!>\!1}+f_{i,j,S}
$$

再计算放置了一个車后的转移。设放了一个車后 $i+1$ 行的状态变为 $T$，则有转移：

$$
f_{i+1,j+1,T}\;\longleftarrow\;f_{i+1,j+1,T}+f_{i,j,S}
$$

最终 $r_k$ 只需对最后一行的每一种状况求和：

$$
r_k=\sum_{S\subseteq U}f_{n,k,S}
$$

最后容斥即可。至此我们解决了问题。

[***code***](https://atcoder.jp/contests/abc309/submissions/43470057)

---

## 作者：JWRuixi (赞：3)

~~/bx 龟神~~

### 题意

给定 $n,x$，求有多少排列 $\{P_n\}$ 满足对于 $\forall 1\le i\le n,|P_i-i|\ge x$。

$n\le100,x\le5$。

### 分析

你发现 $x$ 很小，小到可以状压；但是条件是大于等于，这很蠢，蠢到你想容斥。于是你考虑钦定若干个点违规，剩下随便去的方案数。

因为要考虑容斥系数，所以设计 $f_{i,j,s}$ 表示考虑到第 $i$ 个点，已经钦定了 $j$ 个，当前值域上 $[i-x+1,i+x-1]$ 有没有被选的状态为 $s$。转移直接考虑枚举当前点钦不钦定，如果钦定的话它的值选什么，转移就是 $\mathcal O(x)$ 的。

注意一下细节，$[i-x+1,i+x-1]$ 是可能超出 $[1,n]$ 的限定的，要判掉。

复杂度 $\mathcal O(n^22^{2x-1}x)$。

### Code

提交记录：<https://atcoder.jp/contests/abc309/submissions/43416632>。

---

## 作者：Polaris_Australis_ (赞：2)

不需要容斥的做法。

观察到 $X$ 很小，可以状压，但是直接做会不知道后面的数是否被选而无法转移。

考虑只从一个方向转移，若 $i>p_i$ 则在 $i$ 处统计，若 $p_i>i$ 则在 $p_i$ 处统计，设 $dp_{i,j,S_1,S_2}$ 表示前 $i$ 个数，已经配了 $j$ 对，$[i-X+2,i]$ 中已经被用作第一种情况配对的集合为 $S_1$，被用作第二种情况配对的集合为 $S_2$ 的方案数，直接转移即可。

时间复杂度 $\mathcal{O}(n^24^{X-1})$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Umekawa_Kouko{
	void main();
}
int main(){
	return Umekawa_Kouko::main(),0;
}
namespace Umekawa_Kouko{
	int n,x;
	long long dp[100][101][1<<4][1<<4];
	const int mod=998244353;
	void main(){
		cin>>n>>x;
		--x;
		dp[0][0][0][0]=1;
		int t=x;
		x=(1<<x)-1;
		for(int i=1;i<n;++i){
			for(int j=0;j<=i;++j){
				for(int k=0;k<=x;++k){
					for(int l=0;l<=x;++l){
						(dp[i][j][(k<<1)&x][(l<<1)&x]+=dp[i-1][j][k][l])%=mod;
						if(i>=t){
							(dp[i][j+1][((k<<1)|1)&x][(l<<1)&x]+=dp[i-1][j][k][l]*(i-j-(t-__builtin_popcount(l))))%=mod;
							(dp[i][j+1][(k<<1)&x][((l<<1)|1)&x]+=dp[i-1][j][k][l]*(i-j-(t-__builtin_popcount(k))))%=mod;
							(dp[i][j+2][((k<<1)|1)&x][((l<<1)|1)&x]+=dp[i-1][j][k][l]*(i-j-(t-__builtin_popcount(l)))*(i-j-(t-__builtin_popcount(k))))%=mod;
						}
					}
				}
			}
		}
		cout<<dp[n-1][n][x][x]<<'\n';
	}
}
```


---

## 作者：Genius_Star (赞：0)

### 思路：

一眼考虑容斥。

我们钦定某 $i$ 个位置不满足限制的方案数为 $f_i$，则答案显然是：

$$\sum_{i = 0}^n (-1)^i f_i$$

因为是排列，不能有重复的位置，又注意到 $X \le 5$，故考虑状压 $[i - X + 1, i + X - 1]$ 内的数是否已经被选了。

故定义 $dp_{i, j, S}$ 对于前 $i$ 次位置，选了 $j$ 个数不满足限制，且 $[i - X + 1, i + X - 1]$ 是否被使用过的状态为 $S$。

转移的时候就枚举 $i$ 这个位置填什么即可。

令 $M = 2(X - 1) + 1 = 2X-1$，则时间复杂度为 $O(M \times N^2 \times 2^{M})$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef __int128 __;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
const int N = 105, M = 513, mod = 998244353;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
int n, m, x, ans;
int fac[N], dp[N][N][M];
inline void add(int &x, int v){
	x = (x + v) % mod;
}
inline void sub(int &x, int v){
	x = (x - v + mod) % mod;
}
int main(){
	n = read(), x = read() - 1, m = 2 * x + 1;
	dp[0][0][0] = fac[0] = fac[1] = 1;
	for(int i = 2; i <= n; ++i)
	  fac[i] = 1ll * fac[i - 1] * i % mod;
	for(int i = 1; i <= n; ++i){
		dp[i][0][0] = 1;
		for(int j = 1; j <= i; ++j){
			for(int S = 0; S < (1 << m); ++S){
				for(int l = max(i - x, 1); l <= min(i + x, n); ++l){
					int now = l - i + x + 1;
					if((S >> now) & 1)
					  continue;
					add(dp[i][j][(S ^ (1 << now)) >> 1], dp[i - 1][j - 1][S]);
				}
				add(dp[i][j][S >> 1], dp[i - 1][j][S]);
			}
		}
	}
	for(int i = 0; i <= n; ++i){
		int sum = 0;
		for(int S = 0; S < (1 << m); ++S)
		  add(sum, dp[n][i][S]);
		sum = 1ll * sum * fac[n - i] % mod;
		if(i & 1)
		  sub(ans, sum);
		else
		  add(ans, sum);
	}
	write(ans);
	return 0;
}
```

---

## 作者：rzh01014 (赞：0)

# [abc309_f](https://www.luogu.com.cn/problem/AT_abc309_f)
### 题目描述
求长度为 $n$ 且满足 $|P_i-i|\geq X $ 的方案数。
### 做法
考虑容斥原理，正难则反，去计算不合法的方案数，拿总排列数去减掉不合法的情况。     
假设有若干布尔变量 $A$，表示第 $i$ 个位置是否是非法的，如果把 $A_i$ 考虑为一个集合，由并集容斥得：
$$
\begin{aligned}
\bigcup_{i=1}^{n} A_i=\sum A_i-\sum\limits_{i!=j}
A_i\cap A_j+…+(-1)^k\bigcap_{i=1}^{n} A_i
\end{aligned}
$$
每一项的值分别表示至少一个不合法、至少两个不合法……至少 $k$ 个不合法。最后用所有的情况减去所有非法情况的并即可求出答案。   
又由于对于每个 $i$，不合法的位置满足：
$$
\begin{aligned}
P_i\in[i-X+1,i+X-1]
\end{aligned}
$$
这个区间长度为 $2X-1$，最多是 $9$，故考虑状压 DP，不合法的位置 $i$ 上的取值需要在 $[i-X+1,i+X-1]$ 之间，这些数字的选取情况用二进制 $k$ 作为状态表示。（为方便计算转移，低
位表示较小的值，令 $X=X-1$，这样不合法的范围表示为：$[i-X,i+X]$）。     
由此可以定义 DP 状态，令 $dp_{i,j,k}$ 表示在前 $i$ 项中，有 $j$ 项确定不合法的方案数。    
接下来考虑状态转移：

- 如果不预先确定 $P_{i+1}$，认为该位置选取了合法的值，非法区间的选取状态从上一次转移而来，若上一次是 $k$，则此次是 $k>>1$：$dp_{i,j,\lfloor\frac{k}{2}\rfloor}=dp_{i-1,j,k}$。
- 如果预先确定 $P{i+1}=i+p$（前提：这位取的值没有被使用过，而且是排列的合法取值，$p$ 表示相对 $i$ 的偏移量，$p\in[-X,X]$，二进制的最低位表示是 $i-X$ 是否使用过）：$dp_{i,j,\lfloor\frac{k}{2}\rfloor+(1<<p+X)}+=dp_{i-1,j-1,k}$。

答案就是 $dp_{n,j,k}\times(n-j)!\times(-1)^j$ 的总和，对于所有的 $(j,k)$ 使得 $0\leq j\leq n$，$0\leq k\leq 2^{2X+1}$。   
时间复杂度为 $O(n^24^X X)$。
### code
``` cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=105,mod=998244353;
int n,x,dp[N],fac[N],f[N][N][2005],ans;
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>x;
	if(x==1) {
		dp[1]=0,dp[2]=1;
		for(int i=3; i<=n; i++) dp[i]=(dp[i-1]+dp[i-2])%mod*(i-1)%mod;
		cout<<dp[n];
		return 0;
	}
	x--;
	fac[0]=f[0][0][0]=1;
	for(int i=1;i<=n;i++) fac[i]=(fac[i-1]*i)%mod;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=i;j++){
			for(int k=0;k<1<<2*x+1;k++){
				f[i][j][k/2]=(f[i][j][k/2]+f[i-1][j][k])%mod;
				for(int p=-x;j&&p<=x;p++){
					if(i+p>=1&&i+p<=n&&!(k/2&(1<<p+x))) f[i][j][k/2+(1<<p+x)]=(f[i][j][k/2+(1<<p+x)]+f[i-1][j-1][k])%mod;
				}
			}
		}
	}
	int ans=0;
	for(int j=0;j<=n;j++){
		for(int k=0;k<1<<2*x+1;k++){
			ans=(ans+1ll*fac[n-j]*f[n][j][k]%mod*(j%2?-1:1)%mod+mod)%mod;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：DengDuck (赞：0)

首先为了表述方便，我们把问题转换成有 $n$ 个白球，有 $n$ 个黑球。

注意到 $X\leq 5$，考虑大力状压，设 $f_{i,j,k_1,k_2}$ 表示处理到第 $i$ 个位置，前面（不包括 $[i-k+1,i]$ 这一部分）有 $j$ 个白球没选，在区间 $[i-k+1,i]$  中，没有选择的白球集合是 $k_1$，没有选择的黑球集合是 $k_2$，然后直接转移即可。

为啥这样设计呢？考虑到黑球可能跟前面的白球匹配，也可能和后面的白球匹配，如果考虑后面的匹配，情况会很复杂（动态规划是无后效性的），但是你可以将这种情况试做白球匹配前面的黑球，由于前面的不可选的球是个滑动窗口，而且窗口很小，所以我们考虑状压记录信息，窗口外的点我们可以看作没啥差别的球。

为啥不用记录黑球的剩余数量呢？因为前面 $i$ 个白球和黑球数量是一样的，匹配也是一对一对匹配的，所以知道了白球的剩余数量可以推出黑球的剩余数量。

时间复杂度为 $\mathcal O(4^{X}n^2)$，预处理数字的二进制下 $1$ 的个数会好一些。

场切紫题，战斗，爽！

```cpp
#include<bits/stdc++.h>
#define LL long long
#define LF long double
#define pLL pair<LL,LL>
#define pb push_back
//#define fir first
//#define sec second
using namespace std;
//const LL inf;
const LL N=105;
const LL M=35;
const LL mod=998244353;
//const LF eps;
//const LL P;
LL n,k,f[N][N][M][M],Num[M];
void Add(LL &x,LL y)
{
	x=(x+y+mod)%mod;
}
int main()
{
	scanf("%lld%lld",&n,&k);
	if(k>=n)
	{
		puts("0");
		return 0;
	}
	LL tot=(1ll<<k)-1;
	f[k][0][tot][tot]=1;
	for(int i=0;i<=tot;i++)
	{
		for(int j=0;j<k;j++)Num[i]+=(i>>j)&1;
	}
	for(int i=k;i<=n;i++)
	{
		for(int j=0;j<=i-k;j++)
		{
			for(int k1=0;k1<=tot;k1++)
			{
				LL cnt=j+Num[k1];
				for(int k2=0;k2<=tot;k2++)
				{
					LL cnt2=cnt-Num[k2];
					LL t1=k1>>1,t2=k2>>1;
					Add(f[i+1][j+(k1&1)][t1+(1ll<<(k-1))][t2+(1ll<<(k-1))],f[i][j][k1][k2]);
					Add(f[i+1][j+(k1&1)-1][t1+(1<<(k-1))][t2],(j+(k1&1))*f[i][j][k1][k2]%mod);
					Add(f[i+1][j+(k1&1)][t1][t2+(1<<(k-1))],(cnt2+(k2&1))*f[i][j][k1][k2]%mod);
					Add(f[i+1][j+(k1&1)-1][t1][t2],(j+(k1&1))*(cnt2+(k2&1))*f[i][j][k1][k2]%mod);
				}
			}
		}
	}
	printf("%lld",f[n][0][0][0]);
	return 0;
}
//RP++
```

---

## 作者：tsqtsqtsq0309 (赞：0)

# AT_abc309_g [ABC309G] Ban Permutation

## 题目大意

求长为 $N(N\leq 100)$ 且满足以下条件的排列 $P=(P_1,P_2,\cdots,P_N)$ 的个数：

- $\forall 1\leq i\leq N$，$|P_i-i|\geq X(X\leq 5)$。

## 思路

第一眼看到这一题就知道不能够直接求（废话）。

看到大于等于一眼想到容斥和状压。可以考虑将问题转化一下，钦定 $j$ 个位置满足条件 $|P_i-i|\le X$。

具体地说，令 $f_{i,j,s}$ 表示前 $i$ 个位置中有 $j$ 个位置满足条件 $|P_i-i|\le X$，目前不合法区域选择状态为 $s$，转移的时候讨论是否满足条件即可，还有一车细节需要注意。除了这 $i$ 个位置以外其余的位置都可以随便排，所以还需要乘上 $fac_{n-i}$ 才行。

综上所述，易知答案为：
$$
\sum^{n}_{i=0}\sum_s\times(-1)^i\times(n-i)!
$$
总的时间复杂度为 $O(n^24^XX)$，应该是可以过的吧……

**记得开 long long**

**记得开 long long**

**记得开 long long**

在这里祭了不知道多久……

## 代码

```cpp
#include <iostream>
#define int long long
#define MAXN 105
#define MAXX 15
#define mod 998244353
using namespace std;
int n, x, t, ans;
int f[MAXN][MAXN][MAXX * MAXN], fac[MAXN];
signed main(){
    cin >> n >> x;fac[0] = 1;
    for(int i = 1 ; i <= n ; i ++)
        fac[i] = fac[i - 1] * i % mod;
    x--;
    f[0][0][0] = 1;
	for(int i = 1 ; i <= n ; i ++){
		for(int j = 0 ; j < i ; j ++){
			for(int s = 0 ; s < (1 << ((x << 1) + 1)) ; s ++){
				if (!f[i - 1][j][s])continue;t = (s >> 1);
				f[i][j][t] += f[i - 1][j][s];f[i][j][t] %= mod;
				for(int k = 0 ; k <= (x << 1) ; k ++){
					if ((~t) & (1 << k)){
						if (i + k - x < 1 || i + k - x > n)continue;
						f[i][j + 1][t | (1 << k)] += f[i - 1][j][s];
                        f[i][j + 1][t | (1 << k)] %= mod;
					}
				}
			}
		}
	}
	for(int i = 0 ; i <= n ; i ++){
		for(int s = 0 ; s < (1 << (x * 2 + 1)); s ++){
			t = (i & 1) ? (mod - f[n][i][s]) : f[n][i][s];
			ans = (ans + t * fac[n - i] % mod) % mod;
		}
	}
	cout << ans << endl;
    return 0;
}
```



---

