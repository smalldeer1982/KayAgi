# Earn or Unlock

## 题目描述

Andrea is playing the game Tanto Cuore.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1854B/1661c88808ceec929a74ca91720280905e810592.png)He has a deck of $ n $ cards with values $ a_1, \ldots, a_n $ from top to bottom. Each card can be either locked or unlocked. Initially, only the topmost card is unlocked.

The game proceeds in turns. In each turn, Andrea chooses an unlocked card in the deck — the value written on the card is $ v $ — and performs exactly one of the following two operations:

1. Unlock the first $ v $ locked cards in the deck from the top. If there are less than $ v $ locked cards in the deck, then unlock all the locked cards.
2. Earn $ v $ victory points.

 In both cases, after performing the operation, he removes the card from the deck.The game ends when all the cards remaining in the deck are locked, or there are no more cards in the deck.

What is the maximum number of victory points Andrea can earn?

## 说明/提示

In the first sample test, the deck starts as \[unlocked, locked\]. Then, Andrea uses the first card to unlock the second card. Then he uses the second card to earn $ 2 $ victory points.

In the second sample test, Andrea can use the first card to unlock the second and the third card. Then he uses the second and the third card to earn $ 4+5=9 $ victory points.

In the third sample test, Andrea can't unlock any cards or gain any victory points with the first card.

## 样例 #1

### 输入

```
2
1 2```

### 输出

```
2```

## 样例 #2

### 输入

```
5
2 4 5 0 1```

### 输出

```
9```

## 样例 #3

### 输入

```
4
0 4 4 4```

### 输出

```
0```

# 题解

## 作者：panhongxuanyyds (赞：20)

本题有一个重要的性质：设最终包括 $1$ 号卡片总共解锁了 $k$ 张卡片，则所获得的分数就是 $\sum_{i = 1}^{k} a_i - k + 1$。

感性理解：如果将一张权值为 $x$ 的卡片用来解锁接下来的 $x$ 张卡片，那么相比于用它换取 $x$ 分，就相当于损失了 $x$ 分。因此，我们解锁了 $k - 1$ 张卡片（不包括 $1$ 号卡片），就要损失 $k - 1$ 分。

所以，我们只用判断是否存在一种方案使得恰好解锁 $k$ 张卡片即可。考虑用 bitset 加速 dp。

设 `bool` 类型的 $dp[i]$ 表示是否存在一种方案使得恰好解锁 $i$ 张卡片。初始时 $dp[1] = 1$ （因为 $1$ 号卡片初始已被解锁）。对于每一张权值为 $a_i$ 的卡片，如果存在一种方案使得恰好解锁 $j$ 张卡片，则我们可以消耗这张卡片使得恰好解锁 $j + a_i$ 张卡片。转移方程式如下：

$dp[j] = dp[j] \ \textrm{or} \ dp[j - a_i]$

直接这样写会 TLE，考虑将 `dp` 数组定义为一个 bitset，用 bitset 加速转移：

```cpp
dp = (dp | (dp << a[i]));
```

注意，做完这句语句后，要将 $dp[i]$ 设为 $0$（因为此时已经遍历过前 $i$ 张卡片了，接下来枚举的卡片已经超出了前 $i$ 张卡片的范围，此时我们只解锁了前 $i$ 张卡片，不能使用编号大于 $i$ 的卡片）。为方便查询，可以先用别的数组记录 $dp[i]$ 的值，然后将 $dp[i]$ 设为 $0$。

最后枚举解锁的卡片的数量 $k$，如果存在一种方案使得恰好解锁 $k$ 张卡片，那么将 $\sum_{i = 1}^{k} a_i - k + 1$ 与 `ans` 取最大值。

**注意， `dp` 数组要开到 $2n$ 的大小，枚举解锁的卡片的数量 $k$ 时也要枚举到 $2n$。详见代码。**（我就因为这个而 WA#7）

原因是，有可能可以解锁的卡片数量超过了 $n$。具体可以看下面这组样例。

```
2
2 114514
```

正确的输出应为 `114514`，是因为 $dp[3] = 1$，如果不枚举到 $2n$，就无法处理这种情况。

下面给出代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn = 200000;
const ll N = maxn + 10;
ll n, m, ans, a[N], s[N];
bool f[N];
bitset<N> dp;
int main() {
	scanf("%lld", &n);
	s[0] = 0;
	for (ll i = 1; i <= n; ++i) {
		scanf("%lld", &a[i]);
		s[i] = s[i - 1] + a[i];
	}
	dp[1] = 1;
	for (ll i = 1; i <= n; ++i) {
		dp = (dp | (dp << a[i]));
		f[i] = dp[i];
		dp[i] = 0;
	}
	for (ll i = n + 1; i <= 2 * n; ++i) {
		f[i] = dp[i];
		s[i] = s[i - 1];
	}
	ans = 0;
	for (ll i = 1; i <= 2 * n; ++i) {
		if (f[i]) {
			ans = max(ans, s[i] - i + 1);
		}
	}
	printf("%lld", ans);
	return 0;
}
```

蒟蒻讲的有些地方可能有点啰嗦或者不清楚，还请巨佬们谅解！

---

## 作者：Alex_Wei (赞：7)

### [CF1854B Earn or Unlock](https://www.luogu.com.cn/problem/CF1854B)

如果知道哪些前缀可以 **恰好** 被解锁，就可以用 $\sum a_i - (i - 1)$ 更新答案，因为需要花总和为 $i - 1$ 的卡解锁该前缀。

从左往右递推。如果最长的可以被解锁的前缀 $p$ 小于当前位置 $i$，则 $i$ 一定无法被解锁，退出。$p$ 初始为 $1$。

否则，对于所有解锁了 $i$ 的方案，可以再解锁前 $a_i$ 张卡。即若前缀 $j\geq i$ 可以被恰好被解锁，则前缀 $j + a_i$ 可以恰好被解锁。因为 $p\geq i$，所以令 $p\gets p + a_i$。

注意解锁的卡的数量可能大于 $n$，但显然不超过 $2n$。

用 bitset 维护背包，时间复杂度 $\mathcal{O}(\frac {n ^ 2} w)$。

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
// mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rnd(1064);
int rd(int l, int r) {return rnd() % (r - l + 1) + l;}

constexpr int mod = 1e9 + 7;
void addt(int &x, int y) {x += y, x >= mod && (x -= mod);}
int add(int x, int y) {return x += y, x >= mod && (x -= mod), x;}
int ksm(int a, int b) {
  int s = 1;
  while(b) {
    if(b & 1) s = 1ll * s * a % mod;
    a = 1ll * a * a % mod, b >>= 1;
  }
  return s;
}

constexpr int Z = 1e6 + 5;
int fc[Z], ifc[Z];
int bin(int n, int m) {
  if(n < m) return 0;
  return 1ll * fc[n] * ifc[m] % mod * ifc[n - m] % mod;
}
void init_fac(int Z) {
  for(int i = fc[0] = 1; i < Z; i++) fc[i] = 1ll * fc[i - 1] * i % mod;
  ifc[Z - 1] = ksm(fc[Z - 1], mod - 2);
  for(int i = Z - 2; ~i; i--) ifc[i] = 1ll * ifc[i + 1] * (i + 1) % mod;
}

// ---------- templates above ----------

constexpr int N = 2e5 + 5;

int n;
ll a[N], ans;
bitset<N> f;
void mian() {
  cin >> n;
  int mx = 1;
  f[1] = 1;
  for(int i = 1; i <= n; i++) {
    cin >> a[i];
    if(mx < i) break;
    f |= f << a[i], mx = min(ll(n), mx + a[i]);
    a[i] += a[i - 1];
    if(f[i]) ans = max(ans, a[i] - (i - 1)), f[i] = 0;
  }
  for(int i = n + 1; i <= n + n; i++) {
    if(f[i]) ans = max(ans, a[n] - (i - 1));
  }
  cout << ans << "\n";
}

bool Med;
int main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int T = 1;
  while(T--) mian();
  cerr << 1e3 * clock() / CLOCKS_PER_SEC << " ms\n";
  return 0;
}

```

---

## 作者：dark_moon (赞：3)

将题目分成两部分，一部分是判断有哪些解锁方案是可行的，一部分是统计答案

第一部分很经典，直接用 ```bitset``` 就可以了：

```
bitset<N> b;

...

for(int i = 1; i <= n; i ++){
	a[i] = read();
	b |= (b >> (i) << (i + a[i]));
}
```

第二部分有一个非常精妙的转换，假设现在解锁到了第 $x$ 张卡牌，那么在前面这 $x$ 张牌的数值和中，一定有 $x$ 的数值被用来了解锁卡牌而不是增加价值，那么就把前面这 $x$ 张牌的数值和减去 $x$ 就可以了：

```
int sum = 0;
int ans = 0;
for(int i = 1; i < N; i ++){
	if(i <= n)
	sum += a[i];
	if(b[i])
	ans = max(ans, sum - i + 1);
}
```

这里有一个很重要的细节需要注意，$N$ 需要开两倍的 $maxn$，因为有可能会有一个比较靠下的数解锁的卡牌数量很多，会超出 $maxn$ 的范围，这种情况就需要统计在内；但是如果比两倍的 $maxn$ 超出的还多，那么就不需要在意了，因为这时候一定有一张卡牌在所有卡牌均解锁的情况下又解锁了卡牌，一定不如增加价值来的划算。

---

## 作者：jasonliujiahua (赞：2)

# CF1854B

[题目传送门](https://www.luogu.com.cn/problem/CF1854B)
## 题意简述：
有一长度为 $n$ 的一副牌，每张牌上都有一个数字，设第 $i$ 张牌上的数字为 $a_i$。初始时，你手里只有第一张牌。对于每一张牌，你有两种选择：
- 如果剩余的牌数量 $<a_i $，则将牌摸完，否则继续往下摸 $a_i$ 张牌。摸牌完成后，这张牌会被丢弃。
- 获得 $a_i$ 的分数，并丢弃这张牌。

求你能获得的最大分数。
对于所有数据，保证 $1 \le n \le 10 ^ 5$，$0 \le a_i \le n$。
## 题目分析：
### Step 1：初步分析
显然可以发现，最后选的所有数是数列 $a$ 的一个前缀。设此时算了一个前缀 $1 \sim i$，则一定花费了 $i-1$ 的代价从 $1$ 走到 $i$，因此若算到 $i$，对答案的贡献是
$$\left (\sum_{i=1}^{i} a_i \right )-i+1$$
### Step 2：DP
然而，有一个问题是，并不是所有的区间都可以被走到，也就是说我们需要知道有哪些前缀 $1 \sim i$ 是可以走到并对答案作出贡献的。

因此考虑用 $dp$ 统计哪些前缀是合法的。$dp_i$ 表示 $1\sim i$ 是否合法，则有转移方程：
$$\forall j\ge i， dp_{j+a_i}|=dp_j$$
这里为什么是 $j \ge i$ 呢？是因为当轮到 $i$ 作为已经选出的牌的顶部时，$i$ 之前的数已经用掉了。
### Step 3：优化
可以发现这个算法的复杂度是 $O(n^2)$，大概率无法过这道题，因此可以考虑用 bitset 优化一下常数，即可通过此题。
## 参考代码：

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+10;
int n,a[maxn],ans,sum[maxn];
bitset<maxn> dp,res;
void init()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=2*n;i++) sum[i]=sum[i-1]+a[i];
}
void DP()
{
    dp[1]=1;
    for(int i=1;i<=2*n;i++)
    {
        dp=dp|(dp<<a[i]);
        res[i]=dp[i];
        dp[i]=0;
        //通过此方法可以去除i之前已经被删去的数对答案的影响
        //res记录已经确定（无法被更新）的dp值
    }
}
void output()
{
    for(int i=1;i<=2*n;i++)
        if(res[i]) ans=max(ans,sum[i]-i+1);
    cout<<ans;
}
signed main()
{
    init();
    DP();
    output();
    return 0;
}
```

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1854B)

---

# 思路：

我们很容易地可以构造一个 $n^2$ 状态的 DP：$f_{i,j}$ 表示当前在 $i$ 张牌，还可以摸 $j$ 张牌的最大分数。转移也很好转移，你考虑一眼就会。

但是我们显然要缩减复杂度，我们看到数据范围 $10^5$，想到了根号。

其实我们可以把 $j$ 这一维吃掉，如果我们将继续往下摸牌少去的牌的代价均摊到后面的 $a_i$ 张牌上，那么我们知道一个 $i$，即可求出在该点的分数。

即对于位置 $i$，对应的分数为 $\sum\limits_{j = 1}^n a_j - i + 1$。

然后现在我们的要求就变成了看到底能不能在位置 $i$ 摸到完最后一张牌。

  我们可以发现这个转移是 $n^2$ 的，但是因为状态只有 $0/1$，所以说可以使用 bitset 进行优化，让复杂度变为 $O(\frac {n^2} \omega)$。

处理的时候还有一个细节，就是计算的时候，摸牌的最后一个位置可能会到达 $2\times n$，我们只需要将 $a_{n+1\sim2n}$ 都赋值为 $0$ 即可。

代码如下：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int n,m,ans,a[N],pre[N];
bool f[N];
bitset<N>dp;
signed main(){
	cin>>n;
	pre[0]=0;
	dp[1]=1;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		pre[i]=pre[i-1]+a[i];
	}
	for(int i=1;i<=n;i++){
		dp=(dp|(dp<<a[i]));
		f[i]=dp[i];
		dp[i]=0;
	}
	for(int i=n+1;i<=2*n;i++) {
		f[i]=dp[i];
		pre[i]=pre[i-1];
	}
	ans=0;
	for(int i=1;i<=2*n;i++){
		if(f[i]){
			ans=max(ans,pre[i]-i+1);
		}
	}
	cout<<ans;
	return 0;
}
```
完结撒花~

---

## 作者：AK_heaven (赞：0)

### [CF1854B](https://www.luogu.com.cn/problem/CF1854B)

卡了我们一个小时，本身说写完以后休息会儿去吃饭的，又得被迫加班。

有些题目暴力是坑 -- shifu。

首先很设计出 $O(n^2)$ 暴力 $F_{i, j}$ 表示考虑到第 $i$ 个纸牌，解锁 $j$ 张牌最多可以获得多少价值。

考虑优化，无法优化，经过 $30$ 分钟罚坐得出的结论。

在看了 Hints 过后才发现我们忽略了一个重要性质，$ans = \max\{\sum_{i = 1}^{k} a_i - k + 1\}$，其中 $k$ 必须存在一种合法的解锁方案使得解锁卡牌恰好为 $k$。这样就变成了一个背包问题，通过 bitset 优化可以做到 $O(\frac{N^2}{w})$ 的复杂度。

---

## 作者：Xy_top (赞：0)

不算很难的一道 ``bitset`` 优化 ``DP``。

首先一眼看出一个重要的性质：如果花了某些卡片解锁了 $1\cdots x$ 号位，那么解锁卡片所花的代价就是 $x-1$，这个结论可以感性理解下。

然后就可以 ``DP`` 了，设 $f_i$ 为有没有可能解锁 $1\cdots i$，暴力转移的话对于第 $i$ 张卡片枚举 $\geq i$ 的 $j$，然后用掉 $i$ 变成 $j+a_i$。

但是是 $n^2$ 的，由于是 $01$ 状态所以可以用 ``bitset`` 进行优化然后就做完了。

代码短得惊人：

```cpp
#include <bits/stdc++.h>
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
#define int long long
using namespace std;
int n, ans, a[100005];
bitset <200005> f;
signed main () {
	cin >> n;
	For (i, 1, n) cin >> a[i];
	int mx = 1;
	f[1] = 1;
	For (i, 1, n) f |= f >> i << i << a[i];
	For (i, 1, n) a[i] += a[i - 1];
	For (i, 1, 2 * n) if (f[i]) ans = max (ans, a[min (i, n)] - i + 1);
	cout << ans;
	return 0;
}
```


---

## 作者：Hisaishi_Kanade (赞：0)

### 题外话

这下真的流汗了赛时整个群就我不会这题。

居然写了个 $n\log n$ 的后来发现有后效性的动态规划真的非常流汗。

### 题解

因为对于 unlock 的牌先开后开无所谓，所以我们钦定从上往下依次考虑。考虑如果我们在第 $x$ 张牌 unlock，然后就收手，会花费多少在 unlock 上？是 $x-1$，因为除了第 $1$ 张不需要 unlock，其他都需要花费权值。而剩下的权值，则是我们得到的！

换句话说，如果我们先处理出是否能做到刚好 unlock 到 $i$ 然后收手，我们可以通过前缀和的形式得到这种方式的收益。注意到的是，有可能 unlock 的牌超过了 $n$，由于 $a_i\le n$，所以如果某张牌 unlock 多了也不会超过 $2n$。

这个时候我们假设有 $n+1\sim 2n$ 这 $n$ 张权值为 $0$ 的牌，就可以判掉了。

我们发现这是 $n^2$ 的，然而我们在背包的部分只是想知道是否能做到恰好 unlock 到 $i$，所以可以使用 `std::bitset` 优化这个转移，做到 $O(\dfrac{n^2}\omega)$。

更具体地，`f|=f<<a[i]` 就代表了将 $f$ 左移 $a_i$ 位然后与原数组求或，可以显然的发现，对于 $f_j$，其变为 $1$ 的条件是 $f_{j}$ 原本为 $1$ 或 $f_{j-a_i}$ 为 $1$，而这正是我们的背包过程。

注意的是，在转移 $i$ 时，记录 $f_i$ 是真还是假之后就要将 $f_i$ 置为假。原因很简单，对于 $f_1\sim f_{i-1}$，只是记录了能否恰好达到，当时它们不能够 unlock $i$，所以不能用 $a_i$ 转移它们，所以置为假，使得后面不再使用他转移。对于 $i\sim n$ 的，根据从上往下 unlock 的顺序，显然 unlock 过 $i$ 了所以可以使用 $a_i$ 转移。

统计答案则是简单的，还是注意要到 $2n$。

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for(i=l; i<=r; ++i)
using namespace std;
const int N=1e5+5;
bitset<N<<1> f;
int a[N<<1];
bool rch[N<<1];
long long sum, ret; int n, i;
int main()
{
	scanf("%d", &n); rep(i, 1, n) scanf("%d", a+i);
	f[1]=true; rep(i, 1, n) {f|=f<<a[i]; if(f[i]) rch[i]=true; f[i]=false;}
	rep(i, n+1, 2*n) rch[i]=f[i];
	rep(i, 1, 2*n) {sum+=a[i]; if(rch[i]) ret=max(ret, sum-i+1);}
	printf("%lld\n", ret);
	return 0;
}
```

---

