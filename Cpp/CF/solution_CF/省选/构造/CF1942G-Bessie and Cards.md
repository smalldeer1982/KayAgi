# Bessie and Cards

## 题目描述

[Second Dark Matter Battle - Pokemon Super Mystery Dungeon](https://soundcloud.com/decabat/second-dark-matter-battle?in=decabat/sets/best-of-pokemon-super-mystery)

⠀



Bessie has recently started playing a famous card game. In the game, there is only one deck of cards, consisting of $ a $ "draw $ 0 $ " cards, $ b $ "draw $ 1 $ " cards, $ c $ "draw $ 2 $ " cards, and $ 5 $ special cards. At the start of the game, all cards are in the randomly shuffled deck.

Bessie starts the game by drawing the top $ 5 $ cards of the deck. She may then play "draw $ x $ " cards from the hand to draw the next $ x $ cards from the top of the deck. Note that every card can only be played once, special cards cannot be played, and if Bessie uses a "draw $ 2 $ " card when there is only $ 1 $ card remaining in the deck, then she simply draws that remaining card. Bessie wins if she draws all $ 5 $ special cards.

Since Bessie is not very good at math problems, she wants you to find the probability that she wins, given that the deck is shuffled randomly over all $ (a + b + c + 5)! $ possible orderings. It can be shown that this answer can always be expressed as a fraction $ \frac{p}{q} $ where $ p $ and $ q $ are coprime integers. Output $ p \cdot q^{-1} $ modulo $ 998\,244\,353 $ .

## 说明/提示

In the first case, we have $ 1 $ of each type of "draw" card and $ 5 $ special cards. There are $ 30\,720 $ starting decks where Bessie will win by drawing the top $ 5 $ cards and $ 40\,320 $ starting decks in total. Thus, the probability of Bessie winning is $ \frac{30\,720}{40\,320} = \frac{16}{21} $ .

One example of a winning starting deck is, top to bottom,

1. "Special",
2. "Draw $ 1 $ ",
3. "Special",
4. "Special",
5. "Draw $ 0 $ ",
6. "Draw $ 2 $ ",
7. "Special",
8. "Special".

One example of a losing starting deck is:

1. "Special",
2. "Draw $ 1 $ ",
3. "Special",
4. "Special",
5. "Draw $ 0 $ ",
6. "Special",
7. "Special",
8. "Draw $ 2 $ ".

## 样例 #1

### 输入

```
4
1 1 1
0 0 0
5 3 7
3366 1434 1234```

### 输出

```
903173463
1
35118742
398952013```

# 题解

## 作者：Alex_Wei (赞：4)

### [CF1942G Bessie and Cards](https://www.luogu.com.cn/problem/CF1942G)

先判断一组方案是否成功。设还能抓的牌的数量为 $y$，初始为 $5$。每抓到一张 Draw $0$ 或特殊牌则 $y$ 减去 $1$，每抓到一张 Draw $2$ 则 $y$ 加上 $1$，抓到 Draw $1$ 没有任何影响。当 $y = 0$ 且没有抓到所有特殊牌时失败。将 Draw $1$ 删去不影响一组方案是否合法。考虑到最终答案要求概率而非方案数，于是令 $b = 0$，答案不变。

注意到失败的方案一定有 $y = 0$，于是我们枚举 $y$ 变为 $0$ 的时刻，将特殊牌视为 Draw $0$，算失败的方案数。

经典格路计数。枚举在第 $x$ 次抓牌时 $y$ 第一次变成 $0$，则 $x \geq 5$ 且 $x - 5$ 是偶数。考虑 $(x, y)$ 形成的相图，计算从 $(0, 5)$ 走到 $(x, 0)$，每一步只能向右上或者右下走，且之前没有碰到过 $x$ 轴的方案数。等价于从 $(0, 5)$ 走到 $(x - 1, 1)$ 且之前没有碰到过 $x$ 轴的方案数。反射容斥，等价于从 $(0, 5)$ 走到 $(x - 1, 1)$ 的方案数减去走到 $(x - 1, -1)$ 的方案数。

设 $c' = \frac {x - 5} 2$ 表示抓了多少张 Draw $2$，$a' = x - c'$ 表示抓了多少张 Draw $0$，则方案数为 $\binom {i - 1} {a' - 1} - \binom {i - 1} {a'}$。乘以任意安排 $y = 0$ 之后的贡献系数 $\binom {n - i} {a + 5 - a'}$，其中 $n$ 表示总牌数。再乘以从 $a + 5$ 张牌中选 $5$ 张特殊牌的方案数，不能全选 $y = 0$ 之前，即 $\binom {a + 5} 5 - \binom {a'} 5$。

时间复杂度 $\mathcal{O}(\min(a, c))$。

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pdi = pair<double, int>;
using pdd = pair<double, double>;
using ull = unsigned long long;

#define ppc(x) __builtin_popcount(x)
#define clz(x) __builtin_clz(x)

bool Mbe;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
//mt19937_64 rnd(1064);
int rd(int l, int r) {
  return rnd() % (r - l + 1) + l;
}

constexpr int mod = 998244353;
void addt(int &x, int y) {
  x += y, x >= mod && (x -= mod);
}
int add(int x, int y) {
  return x += y, x >= mod && (x -= mod), x;
}
int ksm(int a, ll b) {
  int s = 1;
  while(b) {
    if(b & 1) s = 1ll * s * a % mod;
    a = 1ll * a * a % mod, b >>= 1;
  }
  return s;
}

constexpr int Z = 1e6 + 5;
int fc[Z], ifc[Z], inv[Z];
int bin(int n, int m) {
  if(n < m) return 0;
  return 1ll * fc[n] * ifc[m] % mod * ifc[n - m] % mod;
}
void init_fac(int Z) {
  for(int i = fc[0] = 1; i < Z; i++) fc[i] = 1ll * fc[i - 1] * i % mod;
  ifc[Z - 1] = ksm(fc[Z - 1], mod - 2);
  for(int i = Z - 2; ~i; i--) ifc[i] = 1ll * ifc[i + 1] * (i + 1) % mod;
  for(int i = 1; i < Z; i++) inv[i] = 1ll * fc[i - 1] * ifc[i] % mod;
}

// ---------- templates above ----------

int n, A, B, C;
void solve(int T) {
  cin >> A >> B >> C, A += 5, B = 0;
  int ans = 0, n = A + C;
  for(int i = 5; i <= n; i += 2) {
    int nc = i - 5 >> 1, na = i - nc;
    if(na > A || nc > C) continue;
    int coef = 1ll * add(bin(i - 1, na - 1), mod - (i > na ? bin(i - 1, na) : 0)) * bin(n - i, A - na) % mod;
    addt(ans, 1ll * coef * add(bin(A, 5), mod - bin(na, 5)) % mod);
  }
  cout << (1 + mod - 1ll * ans * ifc[n] % mod * fc[C] % mod * fc[A - 5] % mod * 120 % mod) % mod << "\n";
}

/*
1
2 0 1
*/ 

bool Med;
signed main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  init_fac(Z);
  int T = 1;
  cin >> T;
  while(T--) solve(T);
  
  fprintf(stderr, "%.3lf ms\n", 1e3 * clock() / CLOCKS_PER_SEC);
  return 0;
}

/*
g++ a.cpp -o a -std=c++14 -O2 -DALEX_WEI
*/
```

---

## 作者：hyman00 (赞：2)

### 题意

你有 $5$ 张特殊卡，$a$ 张 0 类卡，$b$ 张 1 类卡，$c$ 张 2 类卡。

随机排成一堆后，你先从上面摸 $5$ 张卡，然后每次打出一张 $x$ 类卡，并再摸 $x$ 张卡，你不能出特殊卡。

求集齐所有特殊卡的概率，模 $998244353$。

$0\le a,b,c\le 2\times 10^5$ 

### 做法

规定同类的卡相同。

规定 $\binom{x}{y}$ 在 $x<y$ 或 $y<0$ 时等于 $0$。

首先这个问题卡的打法不重要，一拿到卡就可以打。把特殊卡当成 0 类卡，因为它们是类似的。

这个过程相当于是一开始有 $5$ 次机会，每次抽一场卡，用一次机会，在加上卡片上的数量。

因此 $b$ 是不重要的，可以直接忽略掉，问题变成抽到 0 类卡减一，2 类卡加一，要求前缀和要是正数，这和括号序列的形式很像，有类似的做法。

考虑枚举恰好抽了 $x+5$ 张 0 类，$x$ 张 2 类，或者全部抽完，重点就在于计数。

记 $f(x,y)$ 表示抽了 $x$ 张 0 类，$y$ 张 2 类，中途没有终止的方案数。

类似格路计数的方法，转化为每次向上或向右走一格，从 $(0,4)$ 走到 $(x,y+4)$，且不能跨越直线 $y=x$，不合法就相当于从 $(0,4)$ 走到 $(y+5,x-1)$，得到 $f(x,y)=\binom{x+y}{y}-\binom{x+y}{y+5}$。

对于恰好抽了 $x+5$ 张 0 类，$x$ 张 2 类的情况，最后一次必为 0 类卡，对答案的贡献是 $f(x+4,x)\times \binom{x+5}{5}\times \binom{a-x+c-x}{a-x}$，第二项是在 0 类里选择 5 个当作特殊的，第三项是后面没抽到的随便排列。

对于全抽完的情况，贡献是 $f(a+5,c)\times \binom{a+5}{5}$，是类似的。

最后加起来，除以总方案数 $\binom{a+c+5}{a,c,5}$。

复杂度 $O(n)$。

### 代码

（赛后重构）

```c++
int qp(int a,int b){
	int c=1;
	for(;b;(a*=a)%=MOD,b>>=1)if(b&1)(c*=a)%=MOD;
	re c;
}
int iv(int x){re qp(x,MOD-2);}
const int N=2000006;
int fac[N],fiv[N];
void pre(){
	fac[0]=1;
	rept(i,1,N)fac[i]=fac[i-1]*i%MOD;
	fiv[N-1]=iv(fac[N-1]);
	for(int i=N-1;i;i--)fiv[i-1]=fiv[i]*i%MOD;
}
int C(int x,int y){
	if(y<0||x<y)re 0;
	re fac[x]*fiv[y]%MOD*fiv[x-y]%MOD;
}
void run(){
	int a,b,c;
	cin>>a>>b>>c;
	int s0=a+5,s2=c,ans=0;
	int tot_c=C(s0+s2,s0)*C(s0,5)%MOD;
	for(int i=0;i<=s2&&i+5<=s0;i++)
		(ans+=(C(i+i+4,i)+MOD-C(i+i+4,i-1))%MOD*C(i+5,5)%MOD*C(s0-i-5+s2-i,s2-i))%=MOD;
	if(s0<s2+5)
		(ans+=(C(s0+s2,s0)+MOD-C(s0+s2,s2+5))%MOD*C(s0,5))%=MOD;
	cout<<ans*iv(tot_c)%MOD<<"\n";
}
```

---

## 作者：MaxBlazeResFire (赞：1)

看作 $a+b+c+5+5$ 张牌，前 $5$ 张牌是 $2$。

考虑判定一个序列是否合法。把 $2$ 看作 $1$，$1$ 看作 $0$，$0$ 和特殊牌看作 $-1$，那么一个序列合法的条件是前缀和第一次到达 $0$ 之前，所有特殊牌都出现过。不难发现直接把 $1$ 牌看作不存在即可。然后再转化一步，看作一开始只有 $4$ 张牌，然后前缀和到负数看作失败。

考虑枚举 $n$ 表示，前缀和第一次出现负数在 $2n+1$ 处。用经典容斥，方案数是 $\displaystyle\binom{2n-4}{n}-\binom{2n-4}{n+1}$，组合数计算即可。还有一种特殊情况，就是整个序列任何时刻都没有出现负数前缀和，用反射容斥重新推导一遍，此时的方案数为 $\displaystyle\binom{a-4+c}{c}-\binom{a-4+c}{a+1}$。

复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define MAXN 1000005
#define mod 998244353

int a,b,c,fac[MAXN],inv[MAXN],ifac[MAXN];

inline int C( int n , int m ){ return n >= m && n >= 0 && m >= 0 ? 1ll * fac[n] * ifac[m] % mod * ifac[n - m] % mod : 0; }

inline int fp( int x , int p ){ int res = 1; while( p ){ if( p & 1 ) res = 1ll * res * x % mod; x = 1ll * x * x % mod; p >>= 1; } return res; }

inline int reduce( int x ){ return x + ( x >> 31 & mod ); }

inline void chkadd( int &x , int k ){ x += k; if( x >= mod ) x -= mod; }

inline void solve(){
	scanf("%d%d%d",&c,&b,&a); a += 4,c += 5;
	int res = 0;
	for( int i = 4 ; i <= min( a , c ) ; i ++ )
		chkadd( res , 1ll * reduce( C( 2 * i - 4 , i ) - C( 2 * i - 4 , i + 1 ) ) % mod * C( i + 1 , 5 ) % mod * C( a + c - 2 * i - 1 , c - i - 1 ) % mod );
	if( a >= c )
		chkadd( res , 1ll * reduce( C( a + c - 4 , c ) - C( a + c - 4 , a + 1 ) ) % mod * C( c , 5 ) % mod );
	printf("%lld\n",1ll * res * fp( 1ll * C( a - 4 + c , a - 4 ) * C( c , 5 ) % mod , mod - 2 ) % mod);
}

signed main(){
	fac[0] = inv[1] = ifac[0] = 1;
	for( int i = 1 ; i < MAXN ; i ++ ) fac[i] = 1ll * fac[i - 1] * i % mod;
	for( int i = 2 ; i < MAXN ; i ++ ) inv[i] = 1ll * ( mod - mod / i ) * inv[mod % i] % mod;
	for( int i = 1 ; i < MAXN ; i ++ ) ifac[i] = 1ll * ifac[i - 1] * inv[i] % mod;
	int testcase; scanf("%d",&testcase);
	while( testcase -- ) solve();
	return 0;
}
```

---

## 作者：TianTian2008 (赞：0)

不妨将剩余抽牌数称为「体力」。我们先考虑每一种牌对「体力」的影响，「抽 0 次」和「特殊牌」使「体力」减 $1$，「抽 1 次」没有任何影响，「抽 2 次」使「体力」加 $1$。容易发现，「抽 0 次」和「特殊牌」对「体力」影响一样，所以可以把「特殊牌」也视作「抽 0 次」。而「抽 1 次」对「体力」没有影响，所以对于同一种排列其它牌的方案，随意插入「抽 1 次」并不会影响合法性，自然也不会改变概率，故我们可以完全不管「抽 1 次」。

假设最后「体力」耗尽了，若抽了 $t$ 张「抽 2 次」，则需要抽 $t+5$ 张「抽 0 次」，可以转换成一个格路计数问题：起点是 $(0,0)$，走 $2t+5$ 步，每一步 $x\leftarrow x+1,y\leftarrow y\pm1$，走到 $(2t+5,-5)$，过程中不能触碰到 $y=-5$ 这条直线。

但这样刻画是不严谨的，因为终点就在 $y=-5$ 上，也就是说最后一步是例外。具体来说，因为前面都满足 $y>-5$，所以最后一步一定是 $(2t+4,-4)\rightarrow(2t+5,-5)$，我们把最后一步拎出来单独考虑，这样不能触碰到 $y=-5$ 就没有例外了。

现在问题是走 $2t+4$ 步，走到 $(2t+4,-4)$，不能触碰到 $y=-5$。用类似卡特兰数的思路，把碰到 $y=-5$ 后的移动都上下翻转，发现不合法路径与终点为 $(2t+4,-6)$ 的路径构成双射，减掉不合法的即可。

于是我们算出了合法的卡牌排列方案，概率的话除以总方案数随便算。

还有一种情况，假设最后「体力」并未耗尽，此时一定是拿完了全部卡牌，那就只需考虑排列合法即可，思路和上面类似，就不过多赘述了。

```cpp
#include <iostream>
#include <cstdio>
#define mod 998244353
using namespace std;
typedef long long ll;
ll t,a,b,c,fac[400011],inv[400011];
ll ksm(ll x,ll y) {
	ll res=1;
	while(y) {
		if(y&1) res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
inline ll binom(ll n,ll m) {
	if(m<0) return 0;
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
void work() {
	scanf("%lld%lld%lld",&a,&b,&c);
	ll ans=0;
	for(int i=0;i<=a&&i<=c;++i) ans=(ans+(binom(i+2<<1,i)-binom(i+2<<1,i-1))*binom(a+c-(i<<1),c-i)%mod*ksm(binom(a+c+5,c),mod-2)%mod*binom(i+5,5)%mod*ksm(binom(a+5,5),mod-2))%mod;
	if(c>a) ans=(ans+(binom(a+c+5,c)-binom(a+c+5,a))*ksm(binom(a+c+5,c),mod-2))%mod;
	printf("%lld\n",(ans+mod)%mod);
}
int main() {
	fac[0]=1;
	for(int i=1;i<=400010;++i) fac[i]=fac[i-1]*i%mod;
	inv[400010]=ksm(fac[400010],mod-2);
	for(int i=400010;i>=1;--i) inv[i-1]=inv[i]*i%mod;
	scanf("%lld",&t);
	while(t--) work();
	return 0;
}
```

---

## 作者：arrow_king (赞：0)

显然可以转化为总方案数除以总情况。

考虑到得到一张牌可以立刻用技能，相当于：你初始有 $5$ 枚金币，摸一张 $+1$ 金币不变，摸一张 $+2$ 金币加一，摸一张 $+0$ 或特殊牌金币 $-1$，要求金币数量是正的。

这个问题可以被化归为格子走路问题：$+2$ 相当于向右走，$+0$ 相当于向上走。我们设 $f(x,y)$ 表示从 $(0,4)$ 走到 $(x,y+4)$ 且不穿过直线 $y=x$ 的方案数。不合法的方案等价于走到 $(y+5,x-1)$，因此方案数为 $\dbinom{x+y}y-\dbinom{x+y}{y+5}$。

对于正好选了 $x+5$ 张 $0$ 和 $x$ 张 $2$ 的情况，等价于从 $(0,4)$ 走到 $(x+4,x+4)$（因为最后一次一定是 $0$，直接去除最后一次的贡献），所以对答案的贡献是
$$
f(x+4,x)\cdot\dbinom{x+5}5\cdot\dbinom{a+c-2x}{a-x}
$$
第二项是给 $x+5$ 张 $0$ 卡里分配特殊卡，第三项是给没抽到的卡牌随意分配位置。

对于全抽完的情况，当 $a+5<c$ 时贡献是
$$
f(a+5,c)\cdot\dbinom{a+5}5
$$
最后我们给 $1$ 牌随意分配位置，方案数是 $\dbinom{a+b+c+5}{b}$。

考虑总方案数，是 $\dbinom{a+b+c+5}{a,b,c,5}$。这时候你发现 $\dbinom{a+b+c+5}b$ 约掉了，因此约分后总方案数为 $\dbinom{a+c+5}{a,c,5}$。

复杂度 $O(a+b+c)$。

```cpp
a=read(),b=read(),c=read();
ll tot=C(a+c+5,c)*C(a+5,a)%mod,ans=0;
for(ll x=0;x<=c&&x<=a;x++) ans=(ans+(C(2*x+4,x)-C(2*x+4,x-1)+mod)%mod*C(x+5,5)%mod*C(a+c-2*x,c-x)%mod)%mod;
if(a<c) ans=(ans+(C(a+c+5,a+5)-C(a+c+5,c+5)+mod)%mod*C(a+5,5)%mod)%mod;
printf("%lld\n",ans*qpow(tot,mod-2)%mod);
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/CF1942G)

**题目大意**

> 给定 $A+B+C+5$ 张卡牌：$A$ 张「抽 0 次」，$B$ 张「抽 1 次」，$C$ 张「抽 2 次」，$5$ 张特殊卡。
>
> 初始它们从堆顶到堆底随机排列。执行以下操作：首先从堆顶抽五张牌。如果抽到了「抽 $k$ 次」，则继续从堆顶抽 $k$ 张牌下来，直到抽取次数用完或者牌堆清空为止。
>
> 问有多少概率将所有特殊卡全抽到。
>
> 数据范围：$A,B,C\le 2\times 10^5$。

**思路分析**

维护一个变量 $x$ 表示剩余抽取次数，初始 $x=5$，那么三种卡牌分别代表 $+1/0/-1$，不难发现「抽 1 次」的牌不会影响 $x$。

因此「抽 1 次」的卡牌数量不影响答案，因此可以设 $B=0$，记 $a=A+5,c=C,n=a+c$。

反面考虑，枚举什么时候停止抽取，并且求出当前所有使抽取次数 $-1$ 的卡牌中，特殊卡不全部出现的方案数。

那么我们不妨设在抽取了 $i$ 张卡后 $x=0$，相当于格路计数问题，从 $(0,5)$ 出发到 $(i-1,1)$，每一步向右上或右下，期间不经过 $x=0$ 的方案数。

根据反射容斥，设 $k=\dfrac{i+5}2$ 表示 $a$ 类卡的数量，得到方案数为 $\binom {i-1}{k-1}-\binom{i-1}{k}$，然后乘一定组合系数得到答案为：
$$
\mathrm{Answer}=1-\dfrac{5!(a-5)!c!}{n!}\sum_{i=5}^n\left[\binom{i-1}{k-1}-\binom{i-1}k\right]\times\left[\binom a5-\binom k5\right]\times\binom{n-i}{a-k}
$$
时间复杂度 $\mathcal O(n\log P)$，瓶颈在预处理。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=6e5+15,MOD=998244353;
ll fac[MAXN],ifac[MAXN];
ll ksm(ll a,ll b=MOD-2,ll p=MOD) {
	ll ret=1;
	for(;b;a=a*a%p,b>>=1) if(b&1) ret=ret*a%p;
	return ret;
}
ll C(ll x,ll y) {
	if(x<0||y<0||y>x) return 0;
	return fac[x]*ifac[y]%MOD*ifac[x-y]%MOD;
}
void solve() {
	int a,b,c,n;
	scanf("%d%d%d",&a,&b,&c),a+=5,n=a+c;
	ll ans=0;
	for(int i=5,x=5;i<=n;i+=2,++x) {
		if(x>a||i-x>c) continue;
		ans=(ans+(C(i-1,x-1)-C(i-1,x))*(C(a,5)-C(x,5))%MOD*C(n-i,a-x))%MOD;
	}
	printf("%lld\n",(1+MOD-ans*ksm(C(n,a)*C(a,5)%MOD)%MOD)%MOD);
}
signed main() {
	for(int i=fac[0]=ifac[0]=1;i<MAXN;++i) ifac[i]=ksm(fac[i]=fac[i-1]*i%MOD);
	int T; scanf("%d",&T);
	while(T--) solve();
	return 0;
}

---

## 作者：tzl_Dedicatus545 (赞：0)

把问题转换成：初始你有 $5$ 次机会，每次抽到 $0$ 机会减一，抽到 $1$ 机会不变，抽到 $2$ 机会加一。

求的是概率，所以把所有 $1$ 全扔了。

不妨枚举你最终抽到了 $x+5$ 个 $0$，$x$ 个 $2$，对答案的贡献即为 $\binom{x+5}{5}$ 个当特殊牌，然后后边的随便排列，是：$\binom{a-x+c-x}{a-x}$。

要求就是：

- 结尾是 $0$
- 任意时刻，前缀 $0$ 的个数加 $5$ $\leq$ 前缀 $2$ 的个数

抽象成格路计数，随便做就行。

算的是概率，所以要除总方案数：$\dfrac{(a+c+5)!}{a!c!5!}$。

---

## 作者：未来姚班zyl (赞：0)

## 题目大意

Bessie 一个人打牌，规则如下：

牌有两类，第一类牌有三种，打出去可以让 Bessie 从牌堆顶部抓 0/1/2 张牌，第二类是特殊牌：不能打出，共 $5$ 张。

Bessie 开局时先从顶部抓 $5$ 张牌，然后一直打能打的牌直到牌堆空了或者没有能打的牌。

如果 Bessie 能够抓到所有的牌就获胜。给你第一类牌中三种牌的数量 $a,b,c$，随机打乱牌堆，求 Bessie 获胜的概率。

## 题目分析

考虑求能够获胜的方案总数。

我们发现从抓牌的角度看，特殊牌和抓 $0$ 张牌的本质相同，不妨先**忽视**其区别，即将特殊牌当成第一种牌。

这样我们有一种最基本的获胜方法：抓完所有的牌。

为了知道怎样的局面能够满足此条件，我们需要思考怎样的局面是能够继续抓牌的。

设牌堆总牌数为 $n=a+b+c+5$，牌堆的序列 $A_1,A_2,..,A_n$，其中 $A_i=k$ 表示第 $i$ 张牌是抓 $k$ 张的牌，序列 $p_i$ 表示 $A_i$ 的前缀和。所以可以抽完的充要条件为：$\forall i\in[1,n-1],p_i+5>i$。这个很好理解，左边是目前允许的抽牌数，右边是已经抽的牌数，左边大才能继续抽。

移项得 $p_i-i+5>0$。这时候聪明的小伙伴已经发现了，如果将 $i$ 当作横坐标，$p_i-i+5$ 当做纵坐标，则三类牌的效果对应着：$(x,y)\rightarrow(x+1,y-1),(x,y)\rightarrow(x+1,y),(x,y)\rightarrow (x+1,y+1)$。要求走的过程中 $y>0$，所以第二种没有意义。

很好，您已经发现了，抽完牌的充要条件相当于：[从 $(0,5)$ 走到 $(a+c,c-a)$，且中途不会触碰到 $x$ 轴的方案数。](https://zhuanlan.zhihu.com/p/31050581#%E4%B8%8D%E8%83%BD%E2%80%9C%E6%8E%A5%E8%A7%A6%E2%80%9D%E5%AF%B9%E8%A7%92%E7%BA%BF%E7%9A%84%E6%A0%BC%E8%B7%AF%E9%97%AE%E9%A2%98)

不过还有可能中途抽完了所有的特殊牌后就不能再抽了，我们枚举这个不能抽的时间点，依旧可以每次 $O(1)$ 计算。

注意一下方案数应以排列的形式计算。

复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define L x<<1
#define R L|1
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define OK Ll<=l&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N =2e5+5,M=2e6+5,inf=(1LL<<31)-1,mod=998244353;
const ll llf=1e18;
inline void add(int &a,int b){((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline int mul(int a,int b){return 1LL*a*b%mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline void red(int &a,int b){add(a,mod-b);}
inline int Red(int a,int b){return red(a,b),a;}
inline int qp(int a,int b){if(!b)return 1;int c=qp(a,b>>1);Mul(c,c);if(b&1)Mul(c,a);return c;}
inline int INV(int x){return qp(x,mod-2);}
int a,b,c,fac[M],iv[M];
inline void prep(){
	fac[0]=1;
	rep(i,1,M-5)fac[i]=mul(fac[i-1],i);
	iv[M-5]=INV(fac[M-5]);
	per(i,M-6,0)iv[i]=mul(iv[i+1],i+1);
}
inline int C(int x,int y){
	if(x<0||y<0||x<y)return 0;
	return mul(fac[x],mul(iv[y],iv[x-y]));
}
inline int F(int dx,int dy){
	if(dx%2!=dy%2)return 0;
	return C(dx,(dx+dy)/2);
}
inline int ways_(int x,int y,int X,int Y){
	return F(abs(x-X),abs(y-Y));
}
inline int G(int x,int y){
	if(y<0)return 0;
	return Red(ways_(0,5,x,y),ways_(0,5,x,-y));
}
inline void Main(){
	a=read()+5,b=read(),c=read();
	int W=mul(fac[a],mul(fac[b],fac[c]));
	int ans=mul(C(a+b+c,a+c),G(a+c,c-a+5));
	Mul(ans,W);
	rep(i,1,a+c){
		if((i+1)&1)continue;
		W=mul(C(a+b+c,a+c),mul(G(i-1,1),ways_(i,0,a+c,c-a+5)));
		int ct=(i+5)/2;
		Mul(W,mul(C(ct,5),mul(fac[5],fac[a-5])));
		Mul(W,mul(fac[b],fac[c]));
		add(ans,W);
	}
	cout <<mul(ans,iv[a+b+c])<<'\n';
}
signed main(){
	prep();
	int T=read();
	while(T--)Main(); 
	return 0;
}
```

---

