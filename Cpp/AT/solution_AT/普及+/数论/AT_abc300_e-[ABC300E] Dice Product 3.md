# [ABC300E] Dice Product 3

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc300/tasks/abc300_e

あなたは $ 1 $ 以上 $ 6 $ 以下の整数が等確率で出るサイコロと整数 $ 1 $ を持っています。  
 あなたは持っている整数が $ N $ 未満である間、次の操作を繰り返します。

- サイコロを振り、出た目を $ x $ とする。持っている整数に $ x $ を掛ける。
 
全ての操作を終了した時に、持っている整数が $ N $ に一致する確率を $ \text{mod\ }998244353 $ で求めてください。

   確率 $ \text{mod\ }998244353 $ とは？ 求める確率は必ず有理数となることが証明できます。 またこの問題の制約下では、その値を互いに素な $ 2 $ つの整数 $ P $, $ Q $ を用いて $ \frac{P}{Q} $ と表したとき、$ R\ \times\ Q\ \equiv\ P\pmod{998244353} $ かつ $ 0\ \leq\ R\ \lt\ 998244353 $ を満たす整数 $ R $ がただ一つ存在することが証明できます。この $ R $ を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^{18} $
- $ N $ は整数
 
### Sample Explanation 1

操作が終了するまでの手順としてあり得る一例を挙げると次のようになります。 - はじめ, 持っている整数は $ 1 $ である。 - サイコロを振り, $ 2 $ が出る。持っている整数は $ 1\ \times\ 2\ =\ 2 $ になる。 - サイコロを振り, $ 4 $ が出る。持っている整数は $ 2\ \times\ 4\ =\ 8 $ になる。 - 持っている整数が $ 6 $ 以上になったので操作を終了する。 操作がこのように進んだ場合、操作後に持っている整数は $ 8 $ であり $ N\ =\ 6 $ に一致しません。 操作後に持っている整数が $ 6 $ である確率は $ \frac{7}{25} $ です。 $ 239578645\ \times\ 25\ \equiv\ 7\ \pmod{998244353} $ より、 $ 239578645 $ を出力してください。

### Sample Explanation 2

どのような目が出ても、操作後に持っている整数が $ 7 $ になることはありません。

## 样例 #1

### 输入

```
6```

### 输出

```
239578645```

## 样例 #2

### 输入

```
7```

### 输出

```
0```

## 样例 #3

### 输入

```
300```

### 输出

```
183676961```

## 样例 #4

### 输入

```
979552051200000000```

### 输出

```
812376310```

# 题解

## 作者：Xy_top (赞：9)

概率期望题先推式子。

很简单的，设 $f(x)$ 为最终得到 $x$ 的概率，$f(n)=\frac{1}{6}\cdot (f(n)+f(\frac{n}{2})+f(\frac{n}{3})+f(\frac{n}{4})+f(\frac{n}{5})+f(\frac{n}{6}))$，$n$ 不能整除就特判一下。

这时貌似进入了无限递归式，很简单，我们把 $f(n)$ 移过去就行了，整理得到：$f(n)=\frac{1}{5}\cdot (f(\frac{n}{2})+f(\frac{n}{3})+f(\frac{n}{4})+f(\frac{n}{5})+f(\frac{n}{6}))$，接着就有了暴力代码：（还需要算个逆元，另外边界 $f(1)=1$）

```cpp
#include <iostream>
#define int long long
using namespace std;
const long long mod = 998244353;
long long n, inv;
long long q_pow (long long x, long long y) {
	if (y == 0) return 1;
	if (y & 1) return x * q_pow (x * x % mod, y >> 1) % mod;
	return q_pow (x * x % mod, y >> 1);
}
int f (long long x) {
	if (x == 1) return 1;
	int ret = 0;
	if (x % 2 == 0) ret += f (x / 2);
	if (x % 3 == 0) ret += f (x / 3);
	if (x % 4 == 0) ret += f (x / 4);
	if (x % 5 == 0) ret += f (x / 5);
	if (x % 6 == 0) ret += f (x / 6);
	return ret % mod * inv % mod;
}
signed main () {
	inv = q_pow (5, mod - 2);
	cin >> n;
	cout << f (n) % mod;
	return 0;
}
```

TLE 了咋办？~~凉拌炒鸡蛋好吃又好看~~加个记忆化就行了。遍历到的数字全部是 $n$ 的因数，一个数的因数不可能太多，于是这题就解决了。

代码：

```cpp
#include <map>
#include <iostream>
#define int long long
using namespace std;
const long long mod = 998244353;
long long n, inv;
map <int, int> m;
map <int, bool> u;
long long q_pow (long long x, long long y) {
	if (y == 0) return 1;
	if (y & 1) return x * q_pow (x * x % mod, y >> 1) % mod;
	return q_pow (x * x % mod, y >> 1);
}
int f (long long x) {
	if (u[x]) return m[x];
	u[x] = true;
	int ret = 0;
	if (x % 2 == 0) ret += f(x / 2);
	if (x % 3 == 0) ret += f (x / 3);
	if (x % 4 == 0) ret += f (x / 4);
	if (x % 5 == 0) ret += f (x / 5);
	if (x % 6 == 0) ret += f (x / 6);
	m[x] = ret % mod * inv % mod;
	return m[x];
}
signed main () {
	m[1] = 1;
	u[1] = true;
	inv = q_pow (5, mod - 2);//费马小定理计算逆元。
	cin >> n;
	cout << f (n);
	return 0;
}
```


---

## 作者：FFTotoro (赞：8)

## 前言

赛时通过快速切这个题小号 $5$ 场上青 /oh。

## 解法

本题需要使用**记忆化搜索**算法。

令 $p(x)$ 为骰子转到 $x$ 的概率，考虑 $p(x)$ 怎么由更小的状态转移而来：

- 首先，$p_1=1$，因为整数一开始就是 $1$；骰子显示 $1$ 时对答案并没有实质上的影响，可以忽略；

- 如果 $x\equiv0\pmod2$，那么有可能骰子上一次投到 $2$；即有 $\dfrac{1}{5}$ 的概率 $\dfrac{x}{2}$ 转化为 $x$；

- 如果 $x\equiv0\pmod3$，那么有可能骰子上一次投到 $3$；即有 $\dfrac{1}{5}$ 的概率 $\dfrac{x}{3}$ 转化为 $x$；

  $\vdots$
  
- 如果 $x\equiv0\pmod6$，那么有可能骰子上一次投到 $6$；即有 $\dfrac{1}{5}$ 的概率 $\dfrac{x}{6}$ 转化为 $x$；

所以，我们有：

$$
p(x)=
\begin{cases}
1&x=1\\
\frac{\sum\limits_{i=2}^6p(\frac{x}{i})[x\equiv0\pmod i]}{5}&\mathrm{otherwise}
\end{cases}
$$

转移过程用一个 `map` 记录一下即可。

放代码：

```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
const int mod=998244353;
int qpow(int a,int b){
  int r=1;
  while(b){
    if(b&1)r=r%mod*a%mod;
    a=a%mod*a%mod; b>>=1;
  }
  return r;
}
int inv(int x){return qpow(x,mod-2);}
map<int,int> m;
int f(int n){
  if(m[n])return m[n];
  for(int i=2;i<=6;i++)
    if(!(n%i))(m[n]+=f(n/i)*inv(5)%mod)%=mod;
  return m[n];
}
main(){
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int n; cin>>n; m[1]=1; int x=n;
  while(x>1)x/=2; while(x>1)x/=3; while(x>1)x/=5;
  if(x>1)cout<<"0\n";
  else cout<<f(n)<<endl;
  return 0;
}
```

---

## 作者：ForgotDream_CHN (赞：2)

[在我的博客园中查看](https://www.cnblogs.com/forgot-dream/p/17369028.html)

## 题意

初始一个整数为 $1$，你有一个可以等概率地掷出 $1$ 至 $6$ 这六个数值的骰子，再给定一个整数 $N$，当初始给出的整数严格小于 $N$ 时，重复以下操作：

+ 掷一次骰子，将初始给出的整数乘上你掷出来的数字。

求出最终得到 $N$ 的概率模上 $998244353$ 的值。

## 思路

先判无解。由于骰子只能掷出 $1$ 至 $6$ 的值，而 $[1, 6]$ 中共有三个质数 $2$，$3$ 与 $5$，因此如果一个整数能由以上操作得到，则其一定能被分解为 $2^{a}3^{b}5^{c}$ 的形式，否则无论如何也不能得到。

我们令 $P(x)$ 为当前数为 $x$ 时，最终得到 $N$ 的概率。不难得到当当前得到的数字已经比 $N$ 还大时，得到 $N$ 的概率为 $0$，而当 $x = N$，即我们已得到 $N$ 时，概率为 $1$。而当当前数字比 $N$ 小时，根据题意，需要再掷一次骰子并将当前得到的数乘上投出来的数。于是我们可以写出如下的方程：

$$
P(x) = 
\begin{cases}
0 & x \gt N \\
1 & x = N \\
\frac{P(x) + P(2x) + P(3x) + P(4x) + P(5x) + P(6x)}{6} & x \lt N
\end{cases}
$$

第三种情况的式子有点怪，两边都有 $P(x)$，因此我们考虑移项：

$$
\begin{aligned}
P(x) &= \frac{P(x)}{6} + \frac{P(2x) + P(3x) + P(4x) + P(5x) + P(6x)}{6} \\
\frac{5P(x)}{6} &= \frac{P(2x) + P(3x) + P(4x) + P(5x) + P(6x)}{6} \\
P(x) &= \frac{P(2x) + P(3x) + P(4x) + P(5x) + P(6x)}{5}
\end{aligned}
$$

然后就做完了，由于这个式子显然没有后效性，因此我们可以记忆化，但是由于要模上 $998244353$，因此不能使用普通的数组，而是要用 `map` 状物来保存计算值。

## 代码

使用了 AtCoder 官方黑科技 `atcoder_library`，用于简化逆元计算。这个代码写得还是有点复杂，其实还有很多地方可以简化。

```cpp
#include <atcoder/modint.hpp>
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  i64 n;
  std::cin >> n;

  i64 copy = n;
  std::vector<int> factor(6);
  for (auto i : {5, 3, 2}) {
    while (copy % i == 0) {
      copy /= i;
      factor[i]++;
    }
    if (copy == 1) {
      break;
    }
  }

  if (copy != 1) {
    std::cout << 0 << "\n";
    return 0;
  }

  std::map<i64, atcoder::modint998244353> mp;

  std::function<atcoder::modint998244353(i64)> dfs = [&](i64 cur) -> atcoder::modint998244353 {
    if (cur == n) {
      return 1;
    } else if (cur > n) {
      return 0;
    } else if (mp.count(cur)) {
      return mp[cur];
    }

    atcoder::modint998244353 res = 0;
    for (int i = 2; i <= 6; i++) {
      res += dfs(i * cur) / 6;
    }

    return mp[cur] = res * atcoder::modint998244353(6) / atcoder::modint998244353(5);
  };

  std::cout << dfs(1).val() << "\n";

  return 0;
}
```

---

## 作者：c20231020 (赞：2)

### 题目链接
[luogu](https://www.luogu.com.cn/problem/AT_abc300_e)

[atcoder](https://atcoder.jp/contests/abc300/tasks/abc300_e)

### 题目大意

你有一个整数 $1$ 和一个等概率显示 $1 \sim 6$ 的整数的骰子。当你的整数严格小于 $N$ 时，你重复下面的操作： 

+ 投这个骰子。如果它显示的是 $x$，就用你的整数乘以 $x$。

找出你的整数最后是 $N$ 的概率，模 $998244353$。

$1 \le N \le 10^{18}$

### 思路

不管是由样例观察或者是一些推导都可以发现：骰子显示 $1$ 时对概率没有影响。（我不会推，wtcl）于是，可以把骰子等价于只等概率显示 $2 \sim 6$ 五个数。

因为最后的结果是 $2 \sim 6$ 乘起来的，所以最后的答案有解当且仅当 $N$ 没有除 $2,3,5$ 以外的质因数。于是我们可以对 $N$ 质因数分解，如果存在其他质因数就无解。

若有解，设 $N=2^a 3^b 5^c$。设 $dp_{i,j,k}$ 表示当前的结果为 $2^i 3^j 5^k$ 的概率。由 $2 \sim 6$ 的质因数可以推得转移方程。最后的答案就是 $dp_{a,b,c}$。

$O(\log^3 n)$（三个质因数）。

#### code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define mod 998244353
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define N 100010
ll n,m,a,b,c,g,dp[100][100][100];
ll qpow(ll a,ll b){
	ll res=1;
	for(;b;b>>=1,a=a*a%mod)if(b&1)res=res*a%mod;
	return res;
}
void solve(){
	cin>>n;m=n;
	while(!(m&1))m>>=1,++a;
	while(m%3==0)m/=3,++b;
	while(m%5==0)m/=5,++c;
	if(m!=1){//含有除 2,3,5 以外的质因数，无解
		cout<<0;
		return;
	}
	g=qpow(5,mod-2);//预处理 5 的逆元
	dp[0][0][0]=1;
	For(i,0,a)For(j,0,b)For(k,0,c){
		(dp[i+1][j][k]+=dp[i][j][k]*g)%=mod;//2
		(dp[i+2][j][k]+=dp[i][j][k]*g)%=mod;//4
		(dp[i+1][j+1][k]+=dp[i][j][k]*g)%=mod;//6
		(dp[i][j+1][k]+=dp[i][j][k]*g)%=mod;//3
		(dp[i][j][k+1]+=dp[i][j][k]*g)%=mod;//5
	}
	cout<<dp[a][b][c];
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int t=1;
	while(t--)solve();
	return 0;
}
```

---

## 作者：Register_int (赞：2)

直接考虑朴素的概率 dp。设结果为 $n$ 的概率为 $f_n$，则有：

$$f_n=\dfrac16\left(f_{n/1}+f_{n/2}+f_{n/3}+f_{n/4}+f_{n/5}+f_{n/6}\right)$$

发现里面还有一个 $f_n$，移项得到：

$$f_n=\dfrac15\left(f_{n/2}+f_{n/3}+f_{n/4}+f_{n/5}+f_{n/6}\right)$$

我们就得到了一个 $O(n)$ 的动归转移。然而，有许多状态根本没用，可以考虑进行记忆化。实际上的状态数只有 $\dfrac13\log^3n$ 左右，可以通过。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e6 + 10;
const int mod = 998244353;
const int inv = 598946612;

unordered_map<ll, ll> dp;

int cnt;

inline 
ll dfs(ll n) {
	if (dp.count(n)) return dp[n]; ll ans = 0; cnt++;
	for (int i = 2; i <= 6; i++) if (n % i == 0) ans = (ans + dfs(n / i)) % mod;
	return dp[n] = ans * inv % mod;
}

ll n;

int main() {
	scanf("%lld", &n), dp[1] = 1;
	printf("%lld", dfs(n));
}
```

---

## 作者：Hell0_W0rld (赞：2)

# [ABC300E](https://atcoder.jp/contests/abc300/tasks/abc300_e) Solution

## 题目大意
有 $x=1$，每一次投骰子等概率投出 $1\sim 6$，并令 $x\to x\times c$，其中 $c$ 为投出的点数，求最终 $x=n$ 的概率。
## 题解
我们令 $f_x$ 为投到 $x$ 的点数。初始 $f_1=1$，目标 $f_n$。

有一种递推方式是 $\forall c\in [1,6],\frac{f_i}{6}\to f_{i\times c}$，显然因为 $n$ 太大我们不能这样。

那我们只能用另一种方法了：枚举上一次投到什么：$f_i=\frac{\sum^6_{k=1}f_{\frac{i}{k}}}{6}$。

但是，如果 $\frac{i}{k}$ 为分数，不用考虑。

接着我们发现，按照这个式子递推，$f_i$ 还要依赖 $f_i$ 转移，显然我们需要继续推一次。

我们发现在等式右侧，$f_i$ 的系数为 $\frac{1}{6}$，所以，

+ 两边同时减去 $\frac{f_i}{6}$，得到等式：$\frac{5\times f_i}{6}=\frac{\sum^6_{k=2}f_{\frac{i}{k}}}{6}$。
+ 两边同时乘 $\frac{5}{6}$，得到等式：$f_i=\frac{\sum^6_{k=2}f_{\frac{i}{k}}}{5}$。

综上，我们用 `map` 记忆化一下，就 $\texttt{AC}$ 了。

[code](https://atcoder.jp/contests/abc300/submissions/41038634)

---

## 作者：SJH__qwq (赞：1)

$\color{cyan}\texttt{Difficulty : 1354}$

考虑 dp。

设 $f_i$ 表示当前显示为 $i$ 的概率。

容易发现 $f_i$ 可以从 $f_{\frac{i}{x}}$ 推导过来，当且仅当 $1\le x\le 6$ 并且 $i\bmod x=0$，所以有 $f_i=\frac{f_i+f_{\frac{i}{2}}+f_\frac{i}{3}+f_\frac{i}{4}+f_\frac{i}{5}+f_\frac{i}{6}}{6}$。

然后发现里面还有一个 $f_i$，把她给提取出来，得到  $f_i=\frac{f_{\frac{i}{2}}+f_\frac{i}{3}+f_\frac{i}{4}+f_\frac{i}{5}+f_\frac{i}{6}}{5}$。

于是得到了 $O(n)$ 的做法。

但是 $n\le 10^{18}$。

然后发现如果 $n=6$，那么 $i=4$，$i=5$ 的状态都是无关紧要的。

实际上对于一个数 $n$ 设 $d(n)$ 是 $n$ 的因数数量，那么有用的状态的数量是小于等于 $d(n)$ 的。并且在 $n$ 很大的时候，有用的状态的数量远远小于 $d(n)$。

所以直接搜即可。

[Code](https://atcoder.jp/contests/abc300/submissions/41162103)

---

## 作者：Sk_sync_opener (赞：1)

定义 $f(x)$ 为 $x$ 的期望。

不难发现 $f(x)=\dfrac{f(x)+f(2x)+f(3x)+f(4x)+f(5x)+f(6x)}{6}$

移项，得 $f(x)=\dfrac{f(2x)+f(3x)+f(4x)+f(5x)+f(6x)}{5}$

整个方程中，所以唯一需要计算的逆元是 $5$，$5$ 对 $998244353$ 的逆元是 $598946612$。

于是设计 dp，根据上述的信息，可得转移方程 $dp_i=598946612\times (dp_{2i}+dp_{3i}+dp_{4i}+dp_{5i}+dp_{6i})$

由于正常的 dp 变成了 $O(n)$，所以换成记忆化搜索即可，注意要用 `map`。

由于质因子只有 $2,3,5$，所以复杂度为 $O(\log^3 n)$，显然可过。

---

## 作者：incra (赞：1)

### [题目链接](https://www.luogu.com.cn/problem/AT_abc300_e)
### 题解
本题解参考官方题解。

设 $f(x)$ 为结果得到 $x$ 的概率。

依题意，不难推出 $f(x)=\dfrac{1}{6}(f(x)+f(2x)+f(3x)+f(4x)+f(5x)+f(6x))$。

通过移项得到 $\dfrac{5}{6}f(x)=\dfrac{1}{6}(f(2x)+f(3x)+f(4x)+f(5x)+f(6x))$。

$\therefore f(x)=\dfrac{1}{5}(f(2x)+f(3x)+f(4x)+f(5x)+f(6x))$。

由于这里的除法除数只有 $5$，所以我们可以提前计算出 $5$ 模 $998244353$  的逆元。

**时间复杂度：** 

由于计算的数只有 $N=2^x3^y5^z$ 且满足 $N\le n$，我们可以得到：$\begin{cases}0\le x \le \log_2(10^{18})<60\\0\le y \le \log_3(10^{18})<38\\0\le z \le \log_5(10^{18})<26\\\end{cases}$

所以时间复杂度大约是 $60\times38\times26=59280$，足以通过此题。

记得用记搜来加速哦。
### 代码
```cpp
#include <iostream>
#include <unordered_map>
using namespace std;
typedef long long LL;
const int MOD = 998244353,inv5 = 598946612;
LL n;
unordered_map <LL,LL> mp;
LL dp (LL x) {
	if (x >= n) return x == n ? 1 : 0;
	if (mp.count (x)) return mp[x];
	LL ans = 0;
	for (int i = 2;i <= 6;i++) ans = (ans + dp (x * i)) % MOD;
	return mp[x] = ans * inv5 % MOD;
}
int main () {
	cin >> n;
	cout << dp (1) << endl;
	return 0;
}
```

---

