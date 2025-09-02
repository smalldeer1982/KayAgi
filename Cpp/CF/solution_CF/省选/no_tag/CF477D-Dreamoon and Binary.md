# Dreamoon and Binary

## 题目描述

Dreamoon saw a large integer $ x $ written on the ground and wants to print its binary form out. Dreamoon has accomplished the part of turning $ x $ into its binary format. Now he is going to print it in the following manner.

He has an integer $ n=0 $ and can only perform the following two operations in any order for unlimited times each:

1. Print n in binary form without leading zeros, each print will append to the right of previous prints.
2. Increase n by 1.

Let's define an ideal sequence as a sequence of operations that can successfully print binary representation of $ x $ without leading zeros and ends with a print operation (i.e. operation 1). Dreamoon wants to know how many different ideal sequences are there and the length (in operations) of the shortest ideal sequence.

The answers might be large so please print them modulo 1000000007 ( $ 10^{9}+7 $ ).

Let's define the string representation of an ideal sequence as a string of '1' and '2' where the $ i $ -th character in the string matches the $ i $ -th operation performed. Two ideal sequences are called different if their string representations are different.

## 说明/提示

For the first sample, the shortest and the only ideal sequence is «222221» of length $ 6 $ .

For the second sample, there are three ideal sequences «21211», «212222222221», «222222222222222222222222221». Among them the shortest one has length $ 5 $ .

## 样例 #1

### 输入

```
101
```

### 输出

```
1
6
```

## 样例 #2

### 输入

```
11010
```

### 输出

```
3
5
```

# 题解

## 作者：Acfboy (赞：7)

首先很容易想到这样一个 dp 来计算方案数。

$f_{i, j}$ 表示前 $i$ 个最后一次断在 $j$ 的方案数。转移显然是

$$
f_{i, j} = \sum_{j-(i-j+1) \le k \le j} f_{j-1, k} 
$$

注意前面一个等号的时候要特判两串东西是否相同。

现在的复杂度是 $O(n^3)$ 的，因为枚举 $k$ 和判断相同都需要一维。容易想到可以前缀和优化，判相同可以 LCP 预处理，然后你就愉快地  $O(n^2)$ 了。

然后想想第二问，乍一看很不可做，毕竟取了模，怎么比大小呢。第二问的答案相当于 $k+v$，$v$ 是最后一段，$k$ 是分段数。

注意到 $2^{17} > 5000$ 而 $k$ 最多是 $5000$，所以最后一段分在 $n-16$ 以前的肯定不如之后优，因为 $v$ 增加的超过了 $k$ 的最大值，那么就枚举最后 $17$ 个直接比就行，甚至不会爆 `int`。

~~这为什么评 2700 啊，吓死人了~~ 虽然这样，我还是没有想到最后一个性质，因为觉得差别会比较大，所以用 $\log$ 值代替没有问题，就用 $\log$ 比大小了，同样可以通过此题。~~但是 OI 赛制没注意空间炸了~~

```cpp
#include <iostream>
#include <cstring>
#include <cmath>
#define double long double 
constexpr int N = 5005, P = 10'0000'0007, INF = 0x3f3f3f3f;
char s[N];
int n, pw[N], val[N], f[N][N], mg[N][N], g[N][N], lcp[N][N]; 
int gv(int l, int r) { return (1ll*val[r]-1ll*val[l-1]*pw[r-l+1]%P+P) % P; }
bool check(int p, int q, int len) {
	int sp = p-len+1, sq = q-len+1, ans = 0;
	ans = lcp[sp][sq];
	if (ans >= len) return true;
	return s[sp+ans] < s[sq+ans];
}
signed main() {
	std::cin >> (s+1), n = strlen(s+1);
	pw[0] = 1;
	for (int i = 1; i <= n; i++) 
		pw[i] = pw[i-1] * 2 % P;
	for (int i = 1; i <= n; i++)
		val[i] = (val[i-1] * 2 % P + (s[i]-'0')) % P;
	
	for (int i = n; i >= 1; i--)
		for (int j = n; j >= 1; j--) 
			if (s[j] == s[i]) lcp[i][j] = lcp[i+1][j+1] + 1;
			else lcp[i][j] = 0;
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			if (j == 1) { f[i][j] = 1; g[i][j] = 1; continue; }
			if (s[j] == '0') { f[i][j] = f[i][j-1]; g[i][j] = INF; continue; }
			int l = i-j+1;
			f[i][j] = (f[i][j] + f[j-1][j-1] - f[j-1][std::max(j-l, 0)] + P) % P;
			g[i][j] = mg[j-1][std::min(std::max(j-l+1, 1), j-1)] + 1;
			if (j-1 >= l && s[j-l] != '0' && check(j-1, i, l)) 
				f[i][j] = (1ll*f[i][j] + f[j-1][j-l]-f[j-1][j-l-1]+P) % P, g[i][j] = std::min(g[i][j], g[j-1][j-l]+1);
			f[i][j] = (f[i][j-1] + f[i][j]) % P; 
		}
		mg[i][i] = g[i][i];
		for (int j = i-1; j >= 1; j--)
			mg[i][j] = std::min(mg[i][j+1], g[i][j]);
	}
	std::cout << f[n][n] << '\n';	
	
	double an = 1e20; int ans = 0;
	for (int i = 1; i <= n; i++) {
		if ((f[n][i]-f[n][i-1]+P)%P == 0) continue;
		int cnt = g[n][i];
		double gr = 0, p = 1;
		for (int j = i; j <= n; j++, p *= 0.5)
			if (s[j] == '1') gr = gr + p;
		double cur = log10(gr)+log10(2)*(n-i+1);
		if (n-i+1 <= 30) cur = cur + log10((double)cnt/(gr*(1<<(n-i)))+1);
		if (cur < an) an = cur, ans = (gv(i, n) + cnt) % P;
	} 
	std::cout << ans;
}

```

---

## 作者：JWRuixi (赞：2)

~~我调了好久啊，因为一个小失误.....~~

- 题意

有一个初始为 $0$ 的二进制数 $s$，你可以打印 $s$ 或让 $s$ 加 $1$。

问打印出 $t$（不含前导 $0$ ）的方案数和最小操作次数模 $1000000007$。

$t \le 2^{5000}$。

- 分析

合法方案即为将 $s$ 划分成若干不含前导 $0$ 的段，段从前往后不降，操作次数即为段数加上最后一段大小。

所以想到 dp，分为计算方案数和计算最小次数，设 $f_{i,j}$ 为前 $i$ 位，上一次断在 $j$ 的答案。显然都可以从前面小于它的串转移，即：

$$f_{i,j} \leftarrow f_{j-1,k}[s_{k,j-1}\le s_{j,i}]$$ 

比较为字典序，$s_{l,r}$，为字符串 $s$ 区间 $[l,r]$ 这个子串。

显然用 exkmp 预处理可以支持 $O(1)$ 比较，再加上用前缀和维护，代码中的 $f$ 为方案数前缀和，$g$ 为最小段数，$h$ 为最小段数的前缀和。

难点在于如何处理最小操作数，不难发现每一步要么分段，要么加一，所以总答案是段数加上最后一段大小。

但是问题在于，最后一段可能很大，无法比较。实际上最大段数 $5000\le 2^{13}$，所以只用枚举后 $14$ 位即可，本人枚举了后 $16$ 位。注意如果最后 $14$ 位中没有合法位置则要继续向前找到第一个合法的位置。

总时间复杂度 $O(n^2)$。

- code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 5005;
const long long mod = 1e9 + 7, inf = 0x3f3f3f3f;
int n, p[maxn][maxn], h[maxn][maxn], g[maxn][maxn];
long long ans, f[maxn][maxn];
char s[maxn];

struct node {
	int l, r;
	inline bool operator < (const node &rhs) const{
		int t = p[l][rhs.l];
		if (t >= r - l + 1 || t >= rhs.r - rhs.l + 1) return r - l <= rhs.r - rhs.l;
		else return s[l + t] <= s[rhs.l + t];
	}
};

signed main () {
	scanf("%s", s + 1), n = strlen(s + 1);
	for (int i = n; i; i--)
		for (int j = n; j; j--)
			p[i][j] = (s[i] == s[j]) ? p[i + 1][j + 1] + 1 : 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			if (j == 1) {
				f[i][j] = 1;
				continue;
			}
			if (s[j] == '0') {
				f[i][j] = f[i][j - 1];
				continue;
			}
			int l = i - j + 1;
			f[i][j] = 1ll * (f[i][j] + f[j - 1][j - 1] - f[j - 1][max(0, j - l)] + mod) % mod;
			if (j - 1 >= l && s[j - l] == '1' && (node){j - l, j - 1} < (node){j, i}) f[i][j] = 1ll * (f[i][j] + f[j - 1][j - l] - f[j - 1][j - l - 1] + mod) % mod;
			f[i][j] = 1ll * (f[i][j] + f[i][j - 1]) % mod;
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			if (j == 1) {
				g[i][j] = 1;
				continue;
			}
			if (s[j] == '0') {
				g[i][j] = inf;
				continue;
			}
			int l = i - j + 1;
			g[i][j] = h[j - 1][min(max(j - l + 1, 1), j - 1)] + 1;
			if (j - 1 >= l && s[j - l] == '1' && (node){j - l, j - 1} < (node){j, i}) g[i][j] = min(g[i][j], g[j - 1][j - l] + 1);
		}
		h[i][i] = g[i][i];
		for (int j = i - 1; j; j--) h[i][j] = min(h[i][j + 1], g[i][j]);
	}
	ans = 1e18;
	long long cur = 0, coe = 1;
	for (int i = n; i >= max(1, n - 16); i--, coe *= 2ll) {
		cur += coe * (s[i] - '0');
		if ((f[n][i] - f[n][i - 1] + mod) % mod == 0) continue;
		if (s[i] == '1') ans = min(ans, cur + 1ll * g[n][i]);
	}
	cur = 0, coe = 1;
	for (int i = n; i; i--, coe = coe * 2 % mod) {
		cur = (cur + coe * (s[i] - '0') % mod) % mod;
		if ((f[n][i] - f[n][i - 1] + mod) % mod == 0) continue;
		ans = min(ans, 1ll * (g[n][i] + cur) % mod);
		break;
	}
	printf("%lld\n%lld", f[n][n], ans);
}
```

---

## 作者：Purslane (赞：1)

# Solution

唐题，我是不是有想复杂了。

很容易发现，如果我们进行了 $k$ 次操作 $1$，且最后我们的变量是 $n$，付出的代价就是 $n+k$。

使用平凡的前缀和优化 $\rm DP$ 可以计算出 $k$ 和 $cnt$ 数组。

注意到 $n$ 是 $\texttt S$ 的一个后缀，所以相邻的 $n$ 之间至少是两倍关系。因此当 $n$ 在二进制下长度超过 $13$ 的时候，肯定是越短的越好——不同的 $k$ 的差异的最大值是 $| \texttt S |$，因此不需要写高精度。

代码：

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=5000+10,MOD=1e9+7;
int n,dp[MAXN][MAXN],cnt[MAXN][MAXN];
int lcp[MAXN][MAXN],pre[MAXN],pw[MAXN];
string S;
int calc_val(int l,int r) {return ((pre[r]-1ll*pre[l-1]*pw[r-l+1])%MOD+MOD)%MOD;}
int compare(int l1,int r1,int l2,int r2) { //相等返回 0；前者大返回 1；後者大返回 -1 
	if(r1-l1+1!=r2-l2+1) return r1-l1+1>r2-l2+1?1:-1;
	return (lcp[l1][l2]>=r1-l1+1)?0:(S[l1+lcp[l1][l2]]>S[l2+lcp[l1][l2]]?1:-1);
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	memset(dp,0x3f,sizeof(dp));
	cin>>S,n=S.size(),S="&"+S,dp[0][0]=0,cnt[0][0]=1,pw[0]=1;
	ffor(i,1,n) cnt[0][i]=1,dp[0][i]=0;
	ffor(i,1,n) pw[i]=pw[i-1]*2%MOD,pre[i]=(pre[i-1]*2+S[i]-'0')%MOD;
	roff(i,n,1) roff(j,n,1) lcp[i][j]=(S[i]==S[j])?lcp[i+1][j+1]+1:0;	
	int tval=-1;
	ffor(i,1,n) {
		ffor(j,1,i) if(S[i-j+1]=='1') {
			int st=j;
			if(j+j<=i&&compare(i-j-j+1,i-j,i-j+1,i)==1) st--;
			dp[i][j]=dp[i-j][st]+1,cnt[i][j]=cnt[i-j][st];
		}
		if(i==n) {
			int sum=0,flg=0;
			ffor(j,1,min(13,n)) if(cnt[i][j]) flg=1;
			if(flg) {
				int tans=0; tval=INT_MAX;
				ffor(j,1,min(13,n)) tval=min(tval,dp[n][j]+calc_val(n-j+1,n));
			}
			else ffor(j,1,n) if(cnt[i][j]) {tval=(dp[n][j]+calc_val(n-j+1,n))%MOD;break;}
		}
		ffor(j,1,n) dp[i][j]=min(dp[i][j],dp[i][j-1]),cnt[i][j]=(cnt[i][j]+cnt[i][j-1])%MOD;
	}
	cout<<cnt[n][n]<<'\n'<<tval;
	return 0;
}
```

---

