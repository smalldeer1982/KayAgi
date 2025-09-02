# Tenzing and Random Real Numbers

## 题目描述

There are $ n $ uniform random real variables between 0 and 1, inclusive, which are denoted as $ x_1, x_2, \ldots, x_n $ .

Tenzing has $ m $ conditions. Each condition has the form of $ x_i+x_j\le 1 $ or $ x_i+x_j\ge 1 $ .

Tenzing wants to know the probability that all the conditions are satisfied, modulo $ 998~244~353 $ .

Formally, let $ M = 998~244~353 $ . It can be shown that the answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 \pmod{M} $ . Output the integer equal to $ p \cdot q^{-1} \bmod M $ . In other words, output the integer $ x $ that $ 0 \le x < M $ and $ x \cdot q \equiv p \pmod{M} $ .

## 说明/提示

In the first test case, the conditions are $ x_1+x_2 \le 1 $ and $ x_3+x_3\ge 1 $ , and the probability that each condition is satisfied is $ \frac 12 $ , so the probability that they are both satisfied is $ \frac 12\cdot \frac 12=\frac 14 $ , modulo $ 998~244~353 $ is equal to $ 748683265 $ .

In the second test case, the answer is $ \frac 14 $ .

In the third test case, the answer is $ \frac 1{16} $ .

In the fourth test case, the sum of all variables must equal $ 2 $ , so the probability is $ 0 $ .

## 样例 #1

### 输入

```
3 2
0 1 2
1 3 3```

### 输出

```
748683265```

## 样例 #2

### 输入

```
3 3
0 1 2
0 1 3
0 2 3```

### 输出

```
748683265```

## 样例 #3

### 输入

```
3 4
0 1 2
0 1 3
1 2 3
1 2 2```

### 输出

```
935854081```

## 样例 #4

### 输入

```
4 4
0 1 2
0 3 4
1 1 3
1 2 4```

### 输出

```
0```

## 样例 #5

### 输入

```
8 12
0 1 2
0 2 3
1 3 4
0 1 4
0 5 6
0 6 7
1 7 8
0 5 8
1 3 7
1 3 8
1 4 7
1 4 8```

### 输出

```
997687297```

# 题解

## 作者：Little09 (赞：8)

首先看限制 $x_i+x_j\le 1$，这右边有个常数的很难受，那我们定义 $y_i=x_i-0.5$，也就是 $x_i=y_i+0.5$，那么代入原式得到的是 $y_i+y_j\le 0$，其中 $y_i$ 在 $[-0.5,0.5]$ 中随机。

对于 $y_i+y_j\le 0$ 而言，不妨假设 $|y_i|\le|y_j|$，那么我们发现条件 $y_i+y_j\le 0$ 成立等价于 $y_j\le 0$。这启发我们按照 $|y_i|$ 的从小到大顺序做 DP。

我们需要求的概率，其实就是计数有多少个将 $|y_i|$ 排列的方案，并给每个 $|y_i|$ 选择一个正负号的方案，再除以 $n!2^n$。这个问题我们直接状压 DP，$dp_S$ 表示目前已考虑 $S$ 集合，转移的时候考虑当前加入的是哪个 $|y_i|$，再枚举一下正负号，检查一下前面的条件是否都满足，暴力检查是 $O(2^nn^2)$，也可以通过。稍微用位运算记录一下就是 $O(2^nn)$ 的。

```cpp
const int N=20,M=(1<<N);
int n,m; 
int g[N][N],dp[M],e[N][2];
ll ksm(ll x,ll y)
{
	ll res=1;
	while (y)
	{
		if (y&1) res=res*x%mod;
		x=x*x%mod,y>>=1;
	}
	return res;
}
void add(ll &x,ll y)
{
	x+=y;
	if (x>=mod) x-=mod;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n >> m;
	rep(i,1,m)
	{
		int tp,x,y;
		cin >> tp >> x >> y;
		x--,y--;
		e[x][tp]|=(1<<y),e[y][tp]|=(1<<x);
	}
	dp[0]=1;
	rep(i,1,(1<<n)-1)
	{
		rep(j,0,n-1)
		{
			if ((i&(1<<j))==0) continue;
			rep(k,0,1)
			{
				if (e[j][1-k]&i) continue;
				(dp[i]+=dp[i^(1<<j)])%=mod;
			}
		}
	}
	ll ans=dp[(1<<n)-1];
	rep(i,1,n) ans=ans*ksm(i,mod-2)%mod;
	ans=ans*ksm(inv2,n)%mod;
	cout << ans;
	return 0;
}

```


---

## 作者：Para (赞：8)

和 AGC020F 有点像。我们这里想要知道的是所有 $x_i,1-x_j$ 之间的相对大小关系。如果直接暴力枚举，不好刻画 $x_i$ 与 $1-x_i$ 联系。那么换一个角度来观察这个限制。我们以 $0.5$ 为界限，若限制中 $i,j$ 在 $0.5$ 同侧，那么是否满足限制和它们与 $0.5$ 的距离无关。否则只取决于它们与 $0.5$ 距离的大小关系。

假设我们先出了所有 $x_i$ 在 $0.5$ 的那一侧以及它们与 $0.5$ 距离的大小关系。这样就可以直接判断是否合法。考虑按照到 $0.5$ 的距离从小到大加入元素。假设当前加入 $i$，每一次判断 $i$ 与之前加入的数的限制是否合法。观察限制条件，以 $x_i + x_j \le 1$ 为例（$j$ 在 $i$ 之前被加入）。当 $i$ 加入左侧时一定合法，加入右侧一定不合法。

会发现之前需要记录的信息只有已经加入的元素集合。每一次新加入一个数对概率的贡献就是强制这个在某一侧的 $\frac {1} {2}$ 与第几个加入的 $\frac {1} {rk}$。时间复杂度 $O(2^nn)$。

```c++
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mp make_pair
#define inf (ll)1e9
#define pii pair <ll, ll>
#define fr first
#define se second
const ll mod = 998244353, inv2 = (mod + 1) / 2;
char buf[1 << 21], *p1 = buf, *p2 = buf;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 18, stdin), p1 == p2) ? EOF : *p1++)
inline ll read() {
	ll x = 0, f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') f = ((ch == '-') ? -1 : f), ch = getchar();
	while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	return x * f;
}
inline void write(ll x) {
	if(x < 0) x = -x, putchar('-');
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
inline ll quickmod(ll x, ll y) {
	ll Ans = 1;
	while(y) {
		if(y & 1) Ans = (1ll * Ans * x) % mod;
		x = (1ll * x * x) % mod;
		y >>= 1;
	}
	return Ans;
}
inline void Add(ll &x, ll y) {
	x += y;
	if(x >= mod) x -= mod;
}
ll n, m;
ll Ele[25], Ege[25], Inv[25];
ll f[(1<<20)+5];
int main() {
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	for(ll i = 0; i <= 20; i++) Inv[i] = quickmod(i, mod - 2);
	n = read(), m = read();
	for(ll i = 1; i <= m; i++) {
		ll op = read(), u = read() - 1, v = read() - 1;
		if(!op) Ele[u] |= (1 << v), Ele[v] |= (1 << u);
		else Ege[u] |= (1 << v), Ege[v] |= (1 << u);
	}
	f[0] = 1;
	for(ll S = 0; S < (1 << n); S++) {
		ll nc = __builtin_popcountll(S) + 1;
		for(ll i = 0; i < n; i++) {
			if(S >> i & 1) continue;
			if(!(Ege[i] & (S | (1 << i)))) Add(f[S | (1 << i)], f[S] * inv2 % mod * Inv[nc] % mod);//L
			if(!(Ele[i] & (S | (1 << i)))) Add(f[S | (1 << i)], f[S] * inv2 % mod * Inv[nc] % mod);//R
		}
	}
	write(f[(1<<n)-1]), putchar('\n');
	return 0;
}
/*
*/
```



---

## 作者：huangrenheluogu (赞：4)

to Luogu [CF1842H](https://www.luogu.com.cn/problem/CF1842H)

to Codeforces [Tenzing and Random Real Numbers](https://codeforces.com/problemset/problem/1842/H)

首先，对于在一段**连续实数集**中等概率取数字，可能取到任意一个数字，但对于一个确定的数字，可能性为 $0$。这就是第四个样例中 $x_1+x_2+x_3+x_4=2$ 就说明概率为 $0$ 的原因。就是因为 $\dfrac{1}{\inf}=0$。

根据上面的结论，我们发现，一些特殊的数据概率为 $0$。特殊的数据就比如 $x_i=x_j,i\ne j$；$x_i=0.2$；$x_i+x_j=1.2$。其实 $0.3$ 和 $0.7$ 没有什么特别的，取出来就是因为他们是一个数（而且写题解的日期是 $12$ 月 $2$ 日）。

然后我通过借助 [Little09](https://www.luogu.com.cn/user/151475) 的题解（博客不可打开）知道了这样一个 trick。

> 消去常数

把 $1$ 消掉，最好的办法就是所有 $x_i$ 减掉 $0.5$。

这样，问题就是一个关于 $0$ 的问题了，那就容易想到用绝对值比较大小了。

感觉这个思路比 Codeforces 的 [Tutorial](https://codeforces.com/blog/entry/117606) 中取的 $\min$ 函数自然很多。

因为 $x_i+x_j\ge0$ 还是 $x_i+x_j\le0$，是由绝对值大的数决定的。

因此，我们利用绝对值的相对关系，从小到大枚举数，这样就可以状压 dp 了。

很多题解讲到这里就放代码了，但是我在关于 `if((s | lim[0][i]) == s) upd(f[s | (1 << i - 1)], f[s]);` 的递推关系还是思考了会儿的，下面我来解释一下。

首先，我们需要让枚举到的 $a_i$（还没被选择）成为绝对值最大的数，那么，我们需要让与 $a_i$ 相加小于等于 $1$ 的所有数都被选了，那么 $a_i$ 就成为“绝对值最大的”，那和它有 $t=0$ 的所有条件都会被满足了。

当 $t=1$ 的时候，分析同理，我们可以得到 `if((s | lim[1][i]) == s) upd(f[s | (1 << i - 1)], f[s]);`。

完整代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 21, mod = 998244353;
int n, m, lim[2][N], t, x, y, Div = 1, f[1 << N], ans;
inline int ksm(int x, int y){
	int res = 1;
	while(y){
		if(y & 1) res = res * x % mod;
		x = x * x % mod, y >>= 1;
	}
	return res;
}
inline void upd(int &x, int y){
	x += y;
	if(x >= mod) x -= mod;
}
signed main(){
	scanf("%lld%lld", &n, &m);
	Div = ksm(2, n);
	for(int i = 1; i <= n; i++) Div = Div * i % mod;
	for(int i = 1; i <= m; i++){
		scanf("%lld%lld%lld", &t, &x, &y);
		lim[t][x] |= 1 << y - 1;
		lim[t][y] |= 1 << x - 1;
	}
	f[0] = 1;
	for(int s = 0; s < 1 << n; s++){
		for(int i = 1; i <= n; i++){
			if((s >> i - 1) & 1) continue ;
			if((s | lim[0][i]) == s) upd(f[s | (1 << i - 1)], f[s]);
			if((s | lim[1][i]) == s) upd(f[s | (1 << i - 1)], f[s]);
		}
	}
//	printf("%lld\n", f[(1 << n) - 1]);
	Div = ksm(Div, mod - 2);
	ans = Div * f[(1 << n) - 1] % mod;
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：N2MENT (赞：4)

[blog](https://www.cnblogs.com/0x0620AF/articles/CF1842H.html)

[CF1842H](https://www.luogu.com.cn/problem/CF1842H)

---

神秘的题，神必的我。

原题的条件有点不太好看，考虑把每个数的范围变为 $[-0.5, 0.5]$。

原题的要求形似 $x_i + x_j \leq 0$，注意到这个式子是否成立只需要考虑绝对值较大的数的正负，考虑从小到大加入 $x_i$。

实际上并不需要考虑相等的情况，因为在一个连续段上选出指定的数的概率是 $0$。

假如绝对值大小关系已经确定了，那么每种情况下的概率是对称的，所以只要把方案数除以 $n!2^n$ 即可。

那么直接状压，按绝对值从小到大加入元素，位运算判断这一位能否取正或者取负即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod = 998244353;
const int maxn = 22;
const int maxm = maxn * maxn + maxn;
using ll = long long;
inline ll Pow(ll a, ll b = mod - 2) {
    ll res = 1;
    while(b) {
        if(b & 1) res = res * a % mod;
        a = a * a % mod, b >>= 1;
    }
    return res;
}
inline constexpr ll bit(const ll &x) {return 1ll << x;}
int f[bit(maxn)];
int V[maxn], W[maxn];
int n, m;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> w >> u >> v;
        u--, v--;
        if((V[u] & bit(v)) && ((W[u] >> v) & 1) != w) {
            cout << 0;
            return 0;
        }
        V[u] |= bit(v);
        V[v] |= bit(u);
        W[u] |= bit(v) * w;
        W[v] |= bit(u) * w;
    }
    f[0] = 1;
    for(int sta = 1; sta < bit(n); sta++) {
        for(int u = 0; u < n; u++) {
            if(!(sta & bit(u))) continue;
            int bef = sta ^ bit(u);
            int x = (!(W[u] & sta));
            int y = ((V[u] & sta) == (W[u] & sta));
            f[sta] = (f[sta] + (x + y) * f[bef] % mod) % mod;
        }
    }
    int div = 1;
    for(int i = 1; i <= n; i++) div = (ll)div * i % mod;
    div = (ll)div * Pow(2, n) % mod;
    cout << (ll)f[bit(n) - 1] * Pow(div) % mod;
}
```

---

## 作者：蒟蒻君HJT (赞：2)

3000 分就这？

考虑把所有数字分为两类：$(0,0.5),(0.5,1)$，注意由于是连续的随机变量所以我们直接忽略 $x_i=0,0.5,1$ 和 $x_i=x_j,i\neq j$，$x_i+x_j=1$ 的情况。

将所有 $x_i$ 按照 $\min(x_i,1-x_i)$，即到两端的距离的较小值从小到大排序。然后我们给每个 $x_i$ 标上 $t_i=1/2$ 表示其小于 $0.5$ 还是大于 $0.5$。容易发现这样的 $n!\times 2^n$ 种情况是等概率出现的。那么我们只需要计数有多少种情况满足要求就可以了。

这样转化的好处是，对于某个要求 $x_i+x_j\leq 1$，要么 $t_i=t_j=1$，要么 $t_i=1,t_j=2$ 且 $x_i$ 排在 $x_j$ 的前面。我们可以统一一下这两个条件：$x_i$ 和 $x_j$ 出现在前面的那个对应的 $t_{?}=1$，$x_i+x_j\geq 1$ 也是类似的转化。

这样一来就可以设计状态进行 dp：

设 $f_{S}$ 表示已经加入排列的 $x_i$ 的集合为 $S$ 时有多少满足要求的排列。转移时枚举下一个加入的 $x_i$ 即可。

需要预处理一下 $g_{i,S}$ 表示即将加入 $i$ 时，未加入的 $x_i$ 构成集合 $S$，此时对 $i$ 的标号 $t_i$ 的要求是无，$1$，$2$ 还是既得是 $1$ 又得是 $2$（这种当然就不能再转移下去）。

时间复杂度 $\mathcal{O}(n\times 2^n)$。

code

```cpp
#include <bits/stdc++.h>
const int mod = 998244353;
inline int mul(int x, int y){
  return 1ll * x * y % mod;
}
inline int add(int x, int y){
  (x += y) >= mod ? x -= mod : true;
  return x;
}
inline int minus(int x, int y){
  (x -= y) < 0 ? x += mod : true;
  return x;
}
inline int Qpow(int x, int y){
  int r = 1;
  while(y){
    if(y & 1) r = mul(r, x);
    x = mul(x, x);
    y >>= 1;
  }
  return r;
}
inline int inv(int x){
  return Qpow(x, mod - 2);
}
int n, a[20], m[20][20], s, f[1 << 20], g[20][1 << 20], lg[1 << 20];
int main(){
  scanf("%d%d", &n, &s);
  for(int i = 0; i < n; ++i) lg[1 << i] = i;
  int flag = 1;
  for(int i = 1; i <= s; ++i){
    int t, x, y;
    scanf("%d%d%d", &t, &x, &y); ++t; --x, --y;
    if(m[x][y] && m[x][y] != t) flag = 0;
    m[x][y] = m[y][x] = t;
  }
  if(!flag){
    printf("0\n");
    return 0;
  }
  for(int i = 0; i < n; ++i){
    g[i][0] = 0;
    for(int j = 1; j < (1 << n); ++j){
      int t = (j & -j);
      g[i][j] = g[i][j ^ t] | m[i][lg[t]]; 
      //printf("%d %d : %d\n", i, j, g[i][j]);
    }
  }
  int all = (1 << n) - 1;
  f[0] = 1;
  for(int i = 0; i < (1 << n); ++i){
    for(int j = 0; j < n; ++j)
      if(!(i & (1 << j))){
        int t = g[j][all ^ i];
        if(t == 3) ;
        else if(t == 2 || t == 1) f[i ^ (1 << j)] = add(f[i ^ (1 << j)], f[i]);
        else f[i ^ (1 << j)] = add(f[i ^ (1 << j)], mul(f[i], 2));
      }
  }
  int ans = f[(1 << n) - 1];
  for(int i = 1; i <= n; ++i) ans = mul(ans, inv(i)), ans = mul(ans, inv(2));
  printf("%d\n", ans);
  return 0;
}
```


---

## 作者：monstersqwq (赞：2)

考虑枚举每个变量与 $0.5$ 的大小关系，下面记某个变量状态为 $0$ 表示其 $<0.5$，为 $1$ 表示其 $>0.5$。

枚举完之后，记状态为 $0$ 的 $x_i$ 对应的 $y_i=x_i$，为 $1$ 的对应 $y_i=1-x_i$，容易发现条件转换为了若干形似 $y_i\le y_j$ 的条件，此时我们只需要将偏序关系图建出并做一次拓扑序计数即可，但是这是 $O(n4^n)$ 的，如果将拓扑序计数与枚举相结合可以做到 $O(n3^n)$，过不去。

我们大胆猜测 $O(n3^n)$ 做法实际上并不需要记录当前拓扑序选了的点的状态，事实上确实是这样。假设现在拓扑序选了 $S$，希望加上一个 $i$，简单分类可得如果 $i$ 与 $S$ 中有 $0$ 边相连，那么 $i$ 状态必然为 $0$，如果有 $1$ 边相连则必然为 $1$，和 $S$ 中点的状态无关。那么依据此性质可以将状压的状态数降为 $O(2^n)$，单次转移可以在 $O(n)$ 或 $O(n^2)$ 的时间内完成，可以通过。

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
using namespace std;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,int> pli;
const int maxn=200005;
const ll mod=998244353;
int T;
int n,m;
int N;
int g[maxn][maxn];
ll inv[1048600],fac[1048600],ifac[1048600];
int c[1048600];
ll f[1048600];
ll C(int NN,int MM)
{
	if(NN<0||MM<0||NN<MM) return 0;
	return fac[NN]*ifac[MM]%mod*ifac[NN-MM]%mod;
}
void solve()
{
	cin>>n>>m;
	N=(1<<n);
	for(int i=1;i<=m;i++)
	{
		int t,u,v;cin>>t>>u>>v;
		t++;
		if(g[u][v]&&g[u][v]!=t)
		{
			cout<<"0\n";return;
		}
		g[u][v]=g[v][u]=t;
	}
	inv[1]=fac[1]=ifac[1]=ifac[0]=fac[0]=1;
	for(int i=2;i<=N;i++) 
	{
		inv[i]=inv[mod%i]*(mod-mod/i)%mod;
		fac[i]=fac[i-1]*i%mod;
		ifac[i]=ifac[i-1]*inv[i]%mod;
	}
	c[0]=0;
	for(int i=1;i<=N;i++) c[i]=c[i>>1]+(i&1);
	f[0]=1;
	for(int i=0;i<N;i++)
	{
		if(!f[i]) continue;
		for(int j=1;j<=n;j++) if(!(i>>(j-1)&1))
		{
			bool f1=false,f2=false;
			int t=(i|1<<(j-1));
			for(int k=1;k<=n;k++) if(t>>(k-1)&1)
			{
				if(g[j][k]==1) f1=true;
				if(g[j][k]==2) f2=true;
			}
			if(f1&&!f2||!f1&&f2) f[t]=(f[t]+f[i]*inv[2])%mod;
			if(!f1&&!f2) f[t]=(f[t]+f[i])%mod;
		}
	}
	ll ans=f[N-1];
	cout<<ans*ifac[n]%mod<<"\n";
   //made,why is it so painful
}
signed main()
{
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    //cin>>T;to apply alcohol to the testicles
    T=1;
    while(T--)
    {
    	solve();
	}
	return 0;
}
```


---

## 作者：Conan15 (赞：1)

先把求概率转化为求方案数。

考虑消去这个 $1$ 的常数，给所有数减去 $\frac{1}{2}$，于是转化为变量在 $[-\frac{1}{2},\frac{1}{2}]$ 之间随机。\
那么两条限制 $x_i + x_j \leq 1$ 和 $x_i + x_j \geq 1$ 就变成了：$x_i + x_j \leq 0, x_i + x_j \geq 0$。\
注意到一个很好的性质：$x_i + x_j$ 的正负性只和绝对值大的那个数的正负性有关。\
这意味着我们可以从小到大枚举 $|x_i|$ 加入，每次只要保证 $i$ 的限制和之前的加入状态不冲突即可。

怎么实现这个过程呢？记 $leq_i$ 表示需要在 $i$ 之前加入的点的集合。\
也就是每次枚举已经加入的集合 $S$ 和下次要加入 $i$，只要满足 $S$ 和 $leq_i$ 的交集为 $leq_i$ 就能保证 $i$ 和之前加入的数不冲突。\
这可以通过状压 DP 解决。

怎么求概率呢？用满足条件的方案数除以总情况数即可，答案为 $\frac{dp_{2^n-1}}{n!2^n}$

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 25, V = (1 << 20) + 15, mod = 998244353;
int n, m;
int leq0[N], leq1[N];
int dp[V];

int qmi(int a, int k) {
    int res = 1;
    while (k) {
        if (k & 1) res = res * 1ll * a % mod;
        a = a * 1ll * a % mod;
        k >>= 1;
    }
    return res;
}

int main() {
    scanf("%d%d", &n, &m);
    while (m--) {
        int opt, u, v; scanf("%d%d%d", &opt, &u, &v);
        if (opt == 0) leq0[u] |= (1 << v - 1), leq0[v] |= (1 << u - 1);
        else          leq1[u] |= (1 << v - 1), leq1[v] |= (1 << u - 1);
    }
    dp[0] = 1;
    for (int S = 0; S < (1 << n); S++) {
        for (int i = 1; i <= n; i++) {  //接下来放什么数
            if (S & (1 << i - 1)) continue;
            if ((S & leq0[i]) == leq0[i]) (dp[S | (1 << i - 1)] += dp[S]) %= mod;
            if ((S & leq1[i]) == leq1[i]) (dp[S | (1 << i - 1)] += dp[S]) %= mod;
        }
    }
    int inv = 1;
    for (int i = 1; i <= n; i++) inv = inv * 1ll * i % mod;
    inv = inv * 1ll * qmi(2, n) % mod;
    inv = qmi(inv, mod - 2);
    printf("%d\n", dp[(1 << n) - 1] * 1ll * inv % mod);
    return 0;
}
```

---

## 作者：BreakPlus (赞：1)

## Hint

+ 将任意两个数之和与 $1$ 作比较，启发我们对每个数以 $0.5$ 为界进行分类。我们令 $a_i = x_i - 0.5$。显然原来的限制可以转化成 $\le 0$ 或 $\ge 0$。

## Try

+ $n \le 20$ 的数据范围启示我们可以枚举 $a_i$ 的正负性，然后题目相当于对 $|a_i|$ 两两的大小约束。此时我们只需要看 $|a_i|$ 的相对大小，等价于求一个拓扑图的拓扑序个数。但是这个拓扑图很一般，这个思路看起来就没法做了。

+ 发现 $a_i$ 的正负性对连边的影响不大（改变一个 $a_i$ 只会改变其作为端点的连边），而我们每次都要面对新的拓扑图，这是这个算法的瓶颈。

+ 当然有可能这个也能做。

## Retry 

+ 及时切换入手点，我们可以直接枚举最难啃的骨头——拓扑序。而本题不允许 $n!$ 次的枚举，启发我们设计状压 DP。设 $f(S)$ 表示拓扑序的一个前缀的元素集合，即在 $S$ 内的元素对应的 $|a_i|$ 均小于下一个元素。

+ 发现一个很好的性质：若 $|a_i| < |a_j|$，如果限制 $a_i + a_j > 0$，那么等价于 $a_j >0$，与 $a_i$ 的正负性无关；如果限制 $a_i + a_j < 0$，那么等价于 $a_j<0$，同样无关 $a_i$。

+ 也就是说每次在 $S$ 中加入一个元素，我们可以立即判断该数的正负性是否已经确定，且无后效性（与 $S$ 内现有元素无关）。

+ 这样问题的性质被很好地挖掘。我们再加一维，令 $f(k,S)$，$k$ 表示当前被确定正负性的元素数量。转移是简单的。

+ 特别地，若 $a_i$ 同时被确定为正数且为负数，这个转移是行不通的。

## Code

放 $\mathcal{O}(2^nn^2)$ 过了。

```cpp
ll n,m,f[21][1048576],g[21][1048576],vis[21][21];
ll s0[21], s1[21];
void solve(){
	n=read(),m=read();
	memset(vis,-1,sizeof(vis));
	for(ll i=1;i<=m;i++){
		ll t=read(), p=read(), q=read();
		if(vis[p][q] >= 0 && vis[p][q] != t) {
			puts("0");
			return;
		}
		vis[p][q] = vis[q][p] = t;
	}
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=n;j++){
			if(vis[i][j] != -1){
				if(vis[i][j] == 0) s0[i] |= (1ll<<(j-1));
				else s1[i] |= (1ll<<(j-1));
			}
		}
	}
	f[0][0] = 1;
	for(ll i=0;i<n;i++){
		for(ll j=0;j<(1<<n);j++){
			ll x;
			if(!f[i][j]) continue;
			for(ll k=1;k<=n;k++){
				if((j>>(k-1))&1) continue;
				ll sta = j + (1<<(k-1));
				bool p = (s0[k] & sta), q = (s1[k] & sta);
				if(p && q) continue;
				_Add(f[i + (p ^ q)][sta], f[i][j]);
			}
			
		}
	}
	ll ans = 0;
	for(ll i=0;i<=n;i++)
		_Add(ans, 1ll * f[i][(1ll<<n)-1] * qpow(2, n-i) % mod);
	printf("%lld\n", 1ll * ans * qpow((mod+1)/2, n) % mod * iFac(n) % mod);
}
```

---

## 作者：Leasier (赞：1)

这也太需要脑子了吧，[Stinger](https://www.luogu.com.cn/user/361308) 送我一点可以吗 /kel

------------

直接算这个的概率相当困难，不过注意到：

- 若 $x_i + x_j \leq 1$，$x_i, x_j$ 中至少一个 $\leq \frac{1}{2}$。
- 若 $x_i + x_j \geq 1$，$x_i, x_j$ 中至少一个 $\geq \frac{1}{2}$。

考虑将所有 $x_i$ 分为 $[0, \frac{1}{2}], (\frac{1}{2}, 1]$ 两类（记其对应 $i$ 的集合为 $S_1, S_2$），则：

- $\forall p, q \in S_1, x_p + x_q \leq 1$。
- $\forall p, q \in S_2, x_p + x_q \geq 1$。

那对于 $p \in S_1, q \in S_2, x_p + x_q \leq 1$，我们应该怎么办呢？考虑拆出 $\frac{1}{2}$，有 $\frac{1}{2} - x_p \geq x_q - \frac{1}{2}$。

对于把 $\leq$ 改成 $\geq$ 的情况，同理可得 $\frac{1}{2} - x_p \leq x_q - \frac{1}{2}$。

按照 $|x_i - \frac{1}{2}|$ 的顺序依次加入每个 $i$，dp 求出顺序的方案数后除以 $2^n n!$ 即可。时间复杂度为 $O(n 2^n)$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

const int mod = 998244353, inv2 = 499122177;
int s0[27], s1[27], dp[1048577];
ll inv[27];

inline void init(int n){
	inv[0] = inv[1] = 1;
	for (register int i = 2; i <= n; i++){
		inv[i] = mod - (mod / i) * inv[mod % i] % mod;
	}
}

int main(){
	int n, m, full;
	ll ans = 0;
	scanf("%d %d", &n, &m);
	full = (1 << n) - 1;
	init(n);
	for (register int I = 1; I <= m; I++){
		int t, i, j;
		scanf("%d %d %d", &t, &i, &j);
		if (t == 0){
			s0[i] |= 1 << (j - 1);
			s0[j] |= 1 << (i - 1);
		} else {
			s1[i] |= 1 << (j - 1);
			s1[j] |= 1 << (i - 1);
		}
	}
	dp[0] = 1;
	for (register int i = 0; i < full; i++){
		for (register int j = 1; j <= n; j++){
			if (!(i >> (j - 1) & 1)){
				int x = i | (1 << (j - 1));
				if ((x & s0[j]) == 0) dp[x] = (dp[x] + dp[i]) % mod;
				if ((x & s1[j]) == 0) dp[x] = (dp[x] + dp[i]) % mod;
			}
		}
	}
	ans = dp[full];
	for (register int i = 1; i <= n; i++){
		ans = ans * inv2 % mod * inv[i] % mod;
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：tzl_Dedicatus545 (赞：1)

**Upd on 2024/07/24：增加了 dp 部分的详细描述。**

碰到实数概率就傻眼了是这样的。

首先你这个 $x_i+x_j\le 1$ 看着就很烂，考虑将 $x_i,x_j$ 与 $0.5$ 的概率进行讨论，我们不妨将所有数都减去 $0.5$，那么我们的值域就变成 $[-0.5,0.5]$ 了是吧，不妨观察 $|x_i|$ 与 $|x_j|$ 的大小关系，令 $|x_i|>|x_j|$，你发现 $x_i+x_j\leq 0$ 等价于 $x_i\leq 0$！（本人就止步于此）

接下来我们给出一个厉害的结论！（虽然群友好像都认为很常规）

对于所有 $x$，当 $x$ 的大小顺序唯一确定时，这样的大小关系所对应的所有排列的总选中概率是 $\frac{1}{n!}$，证明很简单，就是你每个数列 $a$ 都唯一对应一种大小关系（因为是实数，所以你可以认为不可能出现相等的情况），然而我注意不到，怎么回事捏？

然后就简单了，你随便 dp 一下，依次加入元素，每次 check 一遍合不合法，最后总方案除以 $n!2^n$ 就行了（$2^n$ 是因为你要钦定每个元素的符号）

$n=20$ 所以 $O(2^nn^2)$ 随便过，好像可以精细实现一下（预处理一下合法性）可以做到 $O(2^nn)$ 但没必要。 

怎么这么多人问我怎么 dp。。。

dp 就是，你按照 $|x|$ 的绝对值从大到小，依次加入元素。

注意到限制目前只在 $|x|$ 较大的一方存在了，然后你 $O(n)$ 的 check 一下 $x$ 在第 $i$ 位是否可行就好了。

为什么我不会？？？

---

## 作者：C_Pos_Princess (赞：0)

## 题解
我们看到这样的条件并不好看，于是我们把区间的限制转换为 $(0.5,0.5)$ 的限制，之后式子中 $1$ 的限制就变成 $0$ 的限制。

我们考虑最终式子的数值由绝对值大的那个数决定，所以我们求得值是按照绝对值大小求的。

例如对于 $y_i+y_j \le 0$ 这个式子，假设 $|y_i| \le |y_j|$，那么上面式子成立的条件是 $y_j\le 0$，那么我们只需要按照绝对值做统计。

之后状态压缩转移。


总共的状态，由于选出的 $n$ 个数有 $2!$ 种排列，每个数取 $0$ 或 $1$ 有 $2^n$ 种取法，所以最终答案要除以 $2!\times 2^n$。

## 主要代码

```
	for (int s = 0; s < 1 << n; s++) {
		for (int i = 1; i <= n; i++) {
			if ((s >> i - 1) & 1) continue ;	//我们枚举的是每个数的绝对值 
			if ((s | lim[0][i]) == s) {          //如果当前枚举到的状态符合这一位的限制，那就插入这个数，并按照条件加入当前这个值的符号 
				f[s | (1 << i - 1)] += f[s];
				if (f[s | (1 << i - 1)] >= mod) f[s | (1 << i - 1)] -= mod;
			}
			if ((s | lim[1][i]) == s) {
				f[s | (1 << i - 1)] += f[s];
				if (f[s | (1 << i - 1)] >= mod) f[s | (1 << i - 1)] -= mod;
			}
		}
	}
```



## 完整代码

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 21, mod = 998244353;
int n, m, lim[2][N], t, x, y, Div = 1, f[1 << N], ans;
inline int ksm(int x, int y) {
	int res = 1;
	while (y) {
		if (y & 1) res = res * x % mod;
		x = x * x % mod, y >>= 1;
	}
	return res;
}

signed main() {
	scanf("%lld%lld", &n, &m);
	Div = ksm(2, n);
	for (int i = 1; i <= n; i++) Div = Div * i % mod;
	for (int i = 1; i <= m; i++) {
		scanf("%lld%lld%lld", &t, &x, &y);
		lim[t][x] |= 1 << y - 1;
		lim[t][y] |= 1 << x - 1;
	}
	f[0] = 1;
	for (int s = 0; s < 1 << n; s++) {
		for (int i = 1; i <= n; i++) {
			if ((s >> i - 1) & 1) continue ;
			if ((s | lim[0][i]) == s) {
				f[s | (1 << i - 1)] += f[s];
				if (f[s | (1 << i - 1)] >= mod) f[s | (1 << i - 1)] -= mod;
			}
			if ((s | lim[1][i]) == s) {
				f[s | (1 << i - 1)] += f[s];
				if (f[s | (1 << i - 1)] >= mod) f[s | (1 << i - 1)] -= mod;
			}
		}
	}
	Div = ksm(Div, mod - 2);
	ans = Div * f[(1 << n) - 1] % mod;
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Galois_Field_1048576 (赞：0)

*一验丁真，鉴定为减半。*

首先，有 $x_i+x_j=1$ 条件满足的 $\{x\}$ 出现即概率为 $0$。所以我们可以 $\ge, \le$ 与 $>, <$ 混用。

设 $x'_i = x_i - \dfrac 12$。则条件化为 $x'_i + x'_j$ 与 $0$ 的大小关系。易证 $x_i'$ 的分布为在区间 $I := [-0.5, 0.5]$ 中的均匀分布。以 $x_i' + x_j' > 0$ 为例：当 $x_i'$ 同正时必然满足，当 $x_j'$ 同负时必然不满足。当 $x_i', x_j'$ 一正一负则是绝对值大的是正数时才满足。

如果对 $|x_i'|$ 与 $|x_j'|$ 的大小关系分类讨论，则 $|x_i'| > |x_j'|$ 说明此时 $x_i'$ 的正负号有决定性作用：$x_i'+x_j'$ 正 $\iff x_i'$ 正。$|x_i'| < |x_j'|$ 即是 $x_j'$ 有决定性作用。根据上述讨论，如果我们有置换 $\sigma$（$|x'_{\sigma_k}|$ 第 $k$ 小） 和每一位是否为正就可以判断条件是否被满足。

我们在中间铺陈一条结论：对于均匀分布于 $I^n$ 中的 $\{x\}$，$\sigma$ 是分布均匀的。证明：对于置换 $\tau \in S_n$，设 $T_{\tau} : I_n \to I_n, \{a_i\} \mapsto \{a_{\tau(i)}\}$，则它是保持测度（可以简单地理解为概率）的。因此，对于 $\sigma$ 确定为 $\sigma_0$ 的所有 $\{x\}$ 组成的集合 $E$（首先应当说明 $E$ 可测，但是由于它是一个多面体，显然它可测），
$$
I^n = \bigsqcup_{\sigma \in S_n} T_\sigma(E) \implies m(E) = \dfrac{1}{n!}.
$$
故 $\sigma$ 分布均匀。因此，我们可以枚举 $\sigma$，并对每条答案做 $\dfrac 1{n!}$ 的贡献。

对 $\sigma \in S_n$ 枚举我们得到一个 $\Theta(n!)$ 的做法，但是这样还不够。考虑我们一般枚举置换的时候会怎么做？状压。而且这时我们恰好有 $n \le 20$，唯一地指向了状压。设我们已经考虑了集合 $S = \{\sigma_1, \dots, \sigma_k\}$，现在要考虑集合 $S \sqcup \{m\}$，其中 $m = \sigma_{k+1}$。并考虑 $x_m'$ 的正负性。设 $f(S)$ 为将 $S$ 的元素填入 $\sigma$，同时确定每一个 $S$ 中元素的正负性，这样 $|S|! \cdot 2^{|S|}$ 种方案的方案数。状态转移大致就是枚举 $m \in S^\complement$，枚举 $x'_m$ 的正负号，判断是否与前面的条件相容（因为后面的条件 $x'_m$ 的正负号没有话语权）。按照这样转移即可。时间复杂度 $\Theta(2^n \cdot n)$。

---

## 作者：SFlyer (赞：0)

首先，$x_i\in [0,1]$，可以有两种：$x_i<0.5,x_i\ge 0.5$。因为在 $[0,1]$ 中抽出 $0.5$ 的几率为 $0$，就可以分成 $x_i<0.5,x_i> 0.5$。如果这样分，那么 $x_i,x_j<0.5\implies x_i+x_j\le 1$，$x_i,x_j>0.5\implies x_i+x_j\ge 1$。因此我们只需要考虑 $x_i<0.5,x_j>0.5$ 或者反过来的情况。为了方便起见，设 $<0.5$ 为白色的，$>0.5$ 为黑色的，默认 $x_i$ 白色，$x_j$ 黑色。

考虑一个白点和一个黑点怎么加起来 $\le 1$。几个解释是，黑色的到 $1$ 的距离比白色的值大，即 $1-x_j>x_i$。如果加起来 $\ge 1$，则 $1-x_j<x_i$。（如果 $x_i>x_j$，则反过来）所以，我们可以求出 $\min(x_i,1-x_i)$ 和 $\min(x_j,1-x_j)$ 的大小关系。我们可以小的向大的连边，形成一个图。

如果我们不考虑时间复杂度，那么我们想求出的是：

- 把 $n$ 个点黑白染色。

- 这种染色方案对应的图要是无环的，即有拓扑序。拓扑序是按照 $\min(x_i,1-x_i)$ 的从小到大排序。

这个比较难求，我们可以反之求一个拓扑序，它对应的可行的黑白染色个数，设为 $cnt$。答案就是 $\frac{cnt}{2^n\times n!}$。

设 $dp_{msk}$ 为已经固定好了 $msk$ 里面包含的数（作为 $\min(x_i,1-x_i)$ 最小的 $\texttt{popcnt}(msk)$ 个）的黑白染色方案数。怎么转移呢？我们还可以发现两个性质：

- 如果 $x_a+x_b\le 1$，则 $\min(x_a,x_b)<0.5$。也就是说，固定 $\max(x_a,x_b)$ 对应的时候，$\min$ 的已经在他前面了。

- 如果 $x_a+x_b\ge 1$，则 $\max(x_a,x_b)>0.5$。也就是说，固定 $\min(x_a,x_b)$ 对应的时候，$\max$ 的已经在他前面了。这是因为，$\max$ 的 $\min(x_i,1-x_i)$ 这个值更小。

那么，就很好转移了。具体来说，对于所有 $j\notin msk$，

- 如果所有关于 $j$ 的 $\le 1$ 的限制的另一端都确定了，$j$ 就可以是黑色。

- 如果所有关于 $j$ 的 $\ge 1$ 的限制的另一端都确定了，$j$ 就可以是白色。

时间复杂度 $\mathcal{O}(2^nn)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll mod = 998244353;

ll pw(ll x,ll y=mod-2){
	ll res=1;
	while (y){
		if (y&1){
			res=res*x%mod;
		}
		x=x*x%mod;
		y>>=1;
	}
	return res;
}

ll msk[2][20],dp[1<<20];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n,m;
	cin>>n>>m;
	ll fac=1;
	for (ll i=1; i<=n; i++){
		fac=fac*i%mod;
	}
	ll div=pw(2,n)*fac%mod;
	for (int i=1; i<=m; i++){
		ll t,a,b;
		cin>>t>>a>>b;
		a--;
		b--;
		msk[t][a]|=1<<b;
		msk[t][b]|=1<<a;
	}
	dp[0]=1;
	for (int i=0; i<(1<<n); i++){
		for (int j=0; j<n; j++){
			if (!(i>>j&1)){
				if ((msk[0][j]|i)==i){
					(dp[i^(1<<j)]+=dp[i])%=mod;
				}
				if ((msk[1][j]|i)==i){
					(dp[i^(1<<j)]+=dp[i])%=mod;
				}
			}
		}
	}
	cout<<dp[(1<<n)-1]*pw(div)%mod<<"\n";
	return 0;
}

---

