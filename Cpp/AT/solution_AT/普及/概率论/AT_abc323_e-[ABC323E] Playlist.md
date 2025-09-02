# [ABC323E] Playlist

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc323/tasks/abc323_e

高橋君は $ N $ 曲からなるプレイリストを持っています。 曲 $ i $ $ (1\ \leq\ i\ \leq\ N) $ の長さは $ T_i $ 秒です。  
高橋君は時刻 $ 0 $ にプレイリストのランダム再生を開始しました。

ランダム再生では、$ N $ 曲の中から等確率で $ 1 $ つを選びその曲を最後まで再生することが繰り返されます。 ここで、曲の再生は休みなく行われ、$ 1 $ つの曲が終わったらすぐに次に選ばれた曲が始まります。 また、同じ曲が連続して選ばれる事もあります。

時刻 $ 0 $ から $ (X+0.5) $ 秒後に曲 $ 1 $ が再生されている確率を $ \text{mod}998244353 $ で求めてください。

確率 $ \text{mod\ }\ 998244353 $ の定義この問題で求める確率は必ず有理数になることが証明できます。 また、この問題の制約下では、求める確率を既約分数 $ \frac{y}{x} $ で表したときに $ x $ が $ 998244353 $ で割り切れないことが保証されます。

このとき $ xz\ \equiv\ y\ \pmod{998244353} $ を満たすような $ 0 $ 以上 $ 998244352 $ 以下の整数 $ z $ が一意に定まります。この $ z $ を答えてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\leq\ 10^3 $
- $ 0\ \leq\ X\leq\ 10^4 $
- $ 1\ \leq\ T_i\leq\ 10^4 $
- 入力はすべて整数

### Sample Explanation 1

時刻 $ 0 $ から $ 6.5 $ 秒後に曲 $ 1 $ が流れているパターンとしてあり得るのは、 - 曲 $ 1 $ $ \to $ 曲 $ 1 $ $ \to $ 曲 $ 1 $ - 曲 $ 2 $ $ \to $ 曲 $ 1 $ - 曲 $ 3 $ $ \to $ 曲 $ 1 $ の順で音楽が再生された場合であり、これらのいずれかが起こる確率は $ \frac{7}{27} $ となります。 $ 369720131\times\ 27\equiv\ 7\ \pmod{998244353} $ であるため、$ 369720131 $ を出力します。

### Sample Explanation 2

時刻 $ 0 $ から $ 0.5 $ 秒後には最初に再生された曲が再生されているため、求める確率は $ \frac{1}{5} $ となります。 同じ長さの異なる曲が存在することがあることに注意してください。

## 样例 #1

### 输入

```
3 6
3 5 6```

### 输出

```
369720131```

## 样例 #2

### 输入

```
5 0
1 2 1 2 1```

### 输出

```
598946612```

## 样例 #3

### 输入

```
5 10000
1 2 3 4 5```

### 输出

```
586965467```

# 题解

## 作者：梦应归于何处 (赞：8)

### 题目大意

小 $T$ 的歌单中有 $N$ 首歌曲。歌曲 $i$ 时长 $T_i$ 分钟 $(1 \le i \le N)$。在时刻 $0$ 小 $T$ 开始以随机方式播放它的歌曲。随机播放规则如下：

等概率的 $N$ 首歌曲中的一首，然后播完这首歌。歌曲是连续播放的，一首歌播完，另一首歌立即播放。同一首歌可以连续播放多次。请你求出在时刻 $(X + 0.5)$ 歌曲 $1$ 正在播放的概率，答案对 $998244353$ 取模。

### 思路

考虑动态规划，设计状态，$f_i$ 表示时刻 $i$ 正好结束播出某首歌的总概率。所以 $f_i \rightarrow f_i+f_{i-t_j} (1\le j \le N,t_j \le i)$。

最后的答案就是 $f_{x-t_1+1}+f_{x-t_1+2}+\dots + f_x$。

为什么呢？

因为第一首歌的播放时间为 $f_1$ 所以在 $x-t_1+1$ 到 $x$ 之间都行，把左端点和右端点都加上 $t_1$ 左端点就变成了 $x+1$，右端点就变成了 $x+t_1$。
### 代码

~~~cpp
#include <bits/stdc++.h>
#define db double
#define ll long long
#define ex exit(0)
#define endl "\n"
#define inl inline
#define null NULL
#define pb(a) push_back(a)
using namespace std;
ll f[20000], t[20000];
ll mod = 998244353;
ll qp(ll x, ll y) {
	ll ret = 1;
	while (y) {
		if (y & 1) {
			ret *= x;
			ret %= mod;
		}
		x *= x;
		x %= mod;
		y >>= 1;
	}
	return ret % mod;
}
int main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ll n, x;
	cin >> n >> x;
	for (int i = 1; i <= n; i++) {
		cin >> t[i];
	}
	f[0] = 1;
	ll ni = qp(n, mod - 2);
	for (int i = 0; i <= x; i++) {
		for (int j = 1; j <= n; j++) {
			if(i>=t[j]){
				f[i] = (f[i] + f[i-t[j]] * ni) % mod;
			}
		}
	}
	ll ans = 0;
	for (int i = max(0ll, x - t[1] + 1); i <= x; i++) {
		ans = (ans + f[i]) % mod;
	}
	cout << ans*ni % mod;
	return 0;
}
~~~

---

## 作者：无钩七不改名 (赞：5)

由于是随机播放，每次切歌播放每首歌的概率都相同，为 $\frac{1}{n}$。设 $p_i$ 表示在时间 $i$ 切歌的概率，那么歌曲 $x$ 在时间 $i$ 开始播放的概率就为 $p_i\times\frac{1}{n}$。

对于 $p_i$ 有 $p_i=\sum p_{i-t_j}\times\frac{1}{n}$，其中 $t_j\le i$。意思是在 $p_{i-t_j}$ 切歌时播放歌曲 $j$ 的概率之和，因为此时刚好一首歌播放完切歌。

题目要求歌曲 $1$ 在时间 $x+0.5$ 时播放的概率，那么可以转换为在时间 $j(\max(0,x-t_1+1)\le j \le x)$ 时切歌并播放歌曲 $1$ 的概率即可。



---

## 作者：xiaomuyun (赞：4)

我的 dp 实现比其他题解都暴力一点，因为菜，以及赛时懒得优化空间。

## 思路分析

考虑 dp。

设 $f_{i,j}$ 表示在 $j$ 时刻，刚刚放完 $i$ 的概率。

废话不多说，状态转移方程为：

$$
f_{i,j}=\dfrac{1}{n}\sum\limits_{k=1}^nf_{k,j-t_i}
$$

这是背包的变种，应该不难理解。这首歌放的是 $i$，上一首可以放任意一首，但是上一首放完时间一定是 $j-t_i$。所以可得此方程。

最终的答案即为：

$$
\text{ans}=\sum\limits_{i=x+1}^{x+t_1}f_{1,i}
$$

注意到暴力转移的时间复杂度是 $\mathcal{O}(n^3)$ 的。考虑用一个数组 $sum$ 维护每个时刻放完任何歌的概率之和，也就是说，$sum_j$ 维护的是 $\sum\limits_{i=1}^nf_{i,j}$。

然后就可以直接开始敲代码了。

## 代码实现

是考场代码。加了一点注释。

```cpp
// Problem: E - Playlist
// URL: https://atcoder.jp/contests/abc323/tasks/abc323_e
// Start Time: 2023-10-07 20:00:35
// 
// Powered by CP Editor (https://cpeditor.org)

#include<algorithm>
#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<queue>
using namespace std;
#define inf 0x3f3f3f3f
#define inff 0x3f3f3f3f3f3f3f3f
#define mod 998244353
#define int long long
const int maxn=1e3+2,maxv=1e4+2;
int n,x,t[maxn],f[maxn][maxv*2],inv,sum[maxv*2],res;//i end to get j
inline int ksm(int a,int p){
	int ret=1;
	while(p){
		if(p&1) ret=ret*a%mod;
		a=a*a%mod,p>>=1;
	}
	return ret;
}
signed main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>x;
	inv=ksm(n,mod-2);//预处理逆元
	for(int i=1;i<=n;++i) cin>>t[i];
	sum[0]=1;
	for(int j=1;j<=x+t[1];++j){//注意循环边界，因为题目只是需要我们在 x+0.5 的时刻正在播放，而不是放完
		for(int i=1;i<=n;++i){
			if(j-t[i]<0) continue;
			f[i][j]=(f[i][j]+sum[j-t[i]]*inv)%mod;//状态转移
			sum[j]=(sum[j]+f[i][j])%mod;//同时更新 sum 数组
		}
		if(j>x) res=(res+f[1][j])%mod;
	}
	cout<<res<<'\n';
	return 0;
}
```

---

## 作者：yydfj (赞：2)

这是本蒟蒻第四十次写的题解，如有错误点请好心指出！

## 问题简述

有 $n$ 首歌，你将在第 $0$ 秒随机播放第 $i$ 首歌并持续播放 $a_i$ 秒，其中每首歌被播放的概率是相等的，问在第 $X+0.5$ 秒时，**正在播放**的歌曲是第 $1$ 首歌的概率是多少。

## 解法综述

一眼概率 dp 题，设 $f_{i,j}$ 表示在第 $i$ 秒时，**开始播放**的歌曲是第 $j$ 首歌的概率，记 $ni$ 为 $n$ 的逆元，初始化 $f_{0,i}=ni$，则转移方程为：

$$
f_{i,j}=\sum_{k=1}^n f_{i-a_k,k} \times ni
$$

注意到如果根据上面的转移方程直接枚举 $i,j,k$，时间复杂度为 $O(n^2 X)$。考虑怎么优化，发现可以先预处理出 $\sum_{j=1}^n f_{i-a_j,j} \times ni$ 的值，将其记为 $g$，再带入上面的转移方程进行转移，则时间复杂度为 $O(nX)$。

那么如何统计答案？既然是问在第 $X+0.5$ 秒时，**正在播放**的歌曲是第 $1$ 首歌的概率，那么只需要将从第 $\max(0,X-a_1+1)$ 秒到第 $X$ 秒内，**开始播放**的歌曲是第 $1$ 首歌的概率相加，得出来的结果就是答案，即：

$$
ans=\sum_{i=\max(0,X-a_1+1)}^X f_{i,1}
$$

## 代码描述

```cpp
#include<iostream>
using namespace std;
typedef long long ll;
const ll mod=998244353;
ll n,X,a[1005],f[10005][1005],ans;
ll ksm(ll x,ll y)
{
    ll res=1;
    while(y)
    {
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}
int main()
{
    cin>>n>>X;
    ll ni=ksm(n,mod-2);//求n的逆元
    for(int i=1;i<=n;i++) cin>>a[i],f[0][i]=ni;
    for(int i=0;i<=X;i++)
    {
        ll g=0;
        for(int j=1;j<=n;j++)
        if(i-a[j]>=0) g=(g+f[i-a[j]][j]*ni)%mod;//预处理
        for(int j=1;j<=n;j++)
        if(!f[i][j]) f[i][j]=g%mod;//方程转移
    }
    for(int i=max(0ll,X-a[1]+1);i<=X;i++) ans=(ans+f[i][1])%mod;//统计答案
    cout<<ans;
    return 0;
}
```

---

## 作者：Genius_Star (赞：2)

### 题意：

你有 $n$ 首歌，第 $i$ 首歌的播放时间为 $T_i$，从时间 $0$ 开始，每次随机播放一首歌曲，放完立马播放随机的下一首歌曲，可以重复，问在 $(X+0.5)$ 时间时播放第 $1$ 首歌的概率。

### 思路：

~~我的概率最差了……~~

首先发现这个 $X$ 的值很小只有 $10^4$，所以以时间为单位。

考虑动态规划算法，设 $dp_i$ 表示在时间 $i$ 时结束播放的歌曲的概率，那么答案应该是 $(\sum\limits_{i=X-T_1+1}^{x} dp_i) \times n^{-1}$，其中 $n^{-1}$ 表示 $n$ 的逆元。

解释一下，在 $X-T_1+1 \sim X$ 之间结束的歌曲，只要接着放 $1$ 号歌曲，那么在时间 $X+0.5$ 是肯定可以放出来的，所以求出总概率，然后在乘上一个放 $1$ 号歌的概率，即 $\frac{1}{n}$，因为要取模，所以要求逆元。

然后想一下状态转移的方程，因为每种歌曲都可以无限播放，有点儿像完全背包，即：

$$dp_{i+a_j} \to dp_{i+a_j}+dp_i \times n^{-1}$$

其中 $i$ 为我们枚举的时间轴，$j$ 为当前枚举的第 $j$ 首歌，意思是当前这个时间 $i$ 加上这首歌的时间 $a_j$ 的概率，相当于在这个时间 $i$ 结尾的概率乘上选择第 $j$ 首歌的概率。

时间复杂度为：$O(n \times X)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll M=40040,N=1010,mod=998244353;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,x,ans=0;
ll a[N],dp[M];
ll qpow(ll a,ll b){
	ll ans=1;
	while(b){
		if(b&1ll)
		  ans=(ans*a)%mod;
		a=(a*a)%mod;
		b>>=1ll;
	}
	return ans;
}
int main(){
	dp[0]=1;
	n=read(),x=read();
	for(int i=1;i<=n;i++)
	  a[i]=read();
	for(int i=0;i<=x;i++)
	  for(int j=1;j<=n;j++)
        dp[i+a[j]]=(dp[i+a[j]]+(dp[i]*qpow(n,mod-2)%mod))%mod;
	for(int i=max((x-a[1]+1),0ll);i<=x;i++)
	  ans=(ans+dp[i])%mod;
	write((ans*qpow(n,mod-2))%mod);
	return 0;
}
```


---

## 作者：not_clever_syl (赞：1)

> 题目大意：

> 有 $n$ 首曲子，第 $i$ 首曲子播放需要 $t_i$ 秒。

> 从第 $0$ 秒开始不间断地随机播放歌曲，问第 $X+0.5$ 秒时正在播放歌曲 $1$ 的概率

> $2 \leq n \leq 10^3, 0 \leq x \leq 10^4$

直接算比较困难，但是可以发现第 $X+0.5$ 秒时如果正在播放歌曲 $1$，那上一首歌结束的时间 $t$ 满足 $x-t_1 < t \leq x$。

那么可以考虑对歌曲结束时间进行 dp。

设 $f_i$ 表示第 $i$ 秒刚好播放完上一首歌的概率。

易得：

$f_0 = 1$

$f_i = \frac{1}{n}\sum\limits_{j=1}^n{f_{i-t_j}[i-t_j \geq 0]}$

意思是枚举上一首歌播的是哪首，则 $f_i$ 可以由 $f_{i-t_j}$ 转移。

答案即为 $\frac{1}{n}\sum\limits_{i=x-t_1+1}^{x}f_i$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define MOD 998244353
#define int long long
int n,x;
long long qpow(long long n,long long m){
	long long ans=1;
	while(m){
		if(m&1)ans=ans*n%MOD;
		n=n*n%MOD;
		m>>=1;
	}
	return ans;
}
long long f[200005],t[100005];
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>x;
	for(int i=1;i<=n;++i)cin>>t[i];
	f[0]=1;
	long long inv=qpow(n,MOD-2);//预处理 1/n 的模意义下的值
	for(int i=1;i<=x;++i){
		for(int j=1;j<=n;++j){
			if(i-t[j]>=0){
				f[i]+=f[i-t[j]];
			}
		}
		f[i]=(f[i]%MOD)*inv%MOD;
	}
	long long ans=0;
	for(int i=max(x-t[1]+1,0ll);i<=x;++i)ans+=f[i];//求答案
	ans=(ans%MOD)*inv%MOD;
	cout<<ans;
}
```

---

## 作者：incra (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/AT_abc323_e)
### 题解
考虑 DP。

设 $f_{i,j}$ 表示在第 $i$ 时刻刚刚放完第 $j$ 首歌的概率。

对于每一首歌 $t_k$，$f_{i,k}=\displaystyle\sum_{j=1}^{m} f_{i-t_k,j}$。

对于答案枚举最后播放第 $1$ 首歌的概率和即可。
### 代码
```cpp
#include <bits/stdc++.h>
#define x first
#define y second
#define pb push_back
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,-1,0,0},dy[] = {0,0,1,-1};
bool LAST = false;
istream& operator >> (istream& in,char* s) {
    if (LAST) return in;
	char ch = cin.get ();
	while ((isspace (ch) || ch == '\n') && ch != EOF) ch = cin.get ();
	int n = 0;
	while (!(isspace (ch) || ch == '\n') && ch != EOF) s[n++] = ch,ch = cin.get ();
	s[n] = '\0';
	if (ch == EOF) LAST = true;
	return in;
}
template <typename T1,typename T2> bool tomax (T1 &x,T2 y) {
	if (y > x) return x = y,true;
	return false;
}
template <typename T1,typename T2> bool tomin (T1 &x,T2 y) {
	if (y < x) return x = y,true;
	return false;
}
const int N = 1010,M = 20010,MOD = 998244353;
int n,m;
int t[N];
LL f[M][N];
LL sum[M];
LL power (LL a,LL b,LL p) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
int main () {
	cin >> n >> m;
	for (int i = 1;i <= n;i++) cin >> t[i];
	f[0][1] = sum[0] = 1;
	for (int i = 1;i <= m + t[1];i++) {
		for (int j = 1;j <= n;j++) {
			if (i - t[j] >= 0) f[i][j] = (f[i][j] + sum[i - t[j]] * power (n,MOD - 2,MOD)) % MOD;
		}
		for (int j = 1;j <= n;j++) sum[i] = (sum[i] + f[i][j]) % MOD;
	}
	LL ans = 0;
	for (int i = m + 1;i <= m + t[1];i++) ans = (ans + f[i][1]) % MOD;
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Halberd_Cease (赞：0)

题意：有 $N$ 首歌，每一首歌时长 $T_i$，歌曲随机播放，可以和上一首相同，求第 $(X+0.5)$ 秒时播放的歌是第一首的概率对 $998244353$ 取模的值。

---

简单的概率 DP。

状态就设 $dp_i$ 表示第 $i$ 秒歌曲刚好放完，即可以开启下一首歌的概率。

考虑转移，对于每一个 $dp_i$，因为随机放下一首歌的概率是相等的，因此有 $dp_{i+T_i}=dp_{i+T_j}+\frac{1}{n}dp_i$，其中 $j$ 表示当前随机第 $j$ 首歌。

统计答案，将 $dp_{X-T_1+1}$ 到 $dp_X$ 的值累加起来，乘上 $\frac{1}{n}$ 就是最终的答案。

对 $998244353$ 取模，只需要求出 $n$ 的逆元，当 $\frac{1}{n}$ 去乘就可以了，在计算过程中记得及时取模。

[code](https://atcoder.jp/contests/abc323/submissions/46349559)


---

## 作者：hellolin (赞：0)

# ABC323E Playlist 题解

建议前往 [note.hellolin.cf](https://note.hellolin.cf/solutions/abc323e/) 获得更好的阅读体验！


如果第一首歌在 $(X+0.5)$ 这个时间播放，那么他可能的开始时间 $s$ 满足 $s\in [X-t_1+1, X] \cap \N$。所以说，我们计算的答案就是在这个时间区间内，第一首歌开始播放的概率之和。

然后我们考虑 dp，设 $f_i$ 是在 $i$ 时间开始播放某首歌的概率，$f_0=0$。

转移比较显然了，若当前状态为 $f_i$（也就是某首歌从 $i$ 这个时间刚开始播放），设这首歌时长为 $l$，那么这首歌将会在 $l+x$ 这个时间结束，并立即随机播放另一首歌（每一首歌播放的概率是 $\frac{1}{n}$），伪代码如下：

$$
\begin{array}{ll}
1 & \textbf{Procedure } \text{Transfer.} \\
2 & \qquad f_0\gets 1 \\
3 & \qquad \textbf{For } i\coloneqq 0\textbf{ To } X \\
4 & \qquad\qquad \textbf{For } j\coloneqq 1\textbf{ To } n \\
5 & \qquad\qquad\qquad f_{i+t_j}\gets f_{i+t_j} + f_i\times \frac{1}{n}
\end{array}
$$

这里注意也可能有其他状态转移到 $f_{i+t_j}$，所以我们要累加。

答案就是我们第一段说的 $\sum\limits_{i=X-t_1+1}^{X}f_i$。

注意要特判掉 $X < t_1$ 的情况（显然这种情况下答案是 $\frac{1}{n}$）。

``` cpp
constexpr int N = 5e4 + 114;
using mint = atcoder::modint998244353;
int n, x, t[N];
mint p, ans, dp[N];
void solve() {
    std::cin >> n >> x;
    p = (mint) 1 / (mint) n;
    rep(i, n) std::cin >> t[i];
    if (t[1] > x) {
        std::cout << p.val() << '\n';
        return;
    }

    dp[0] = 1;
    rep(i, 0, x) {
        rep(j, n)
            dp[t[j] + i] += p * dp[i];
    }
    rep(i, x - t[1] + 1, x)
        ans += dp[i];
    ans *= p;
    std::cout << ans.val() << '\n';
}
```

---

