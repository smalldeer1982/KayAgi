# Odd Subrectangles

## 题目描述

[problemUrl]: https://atcoder.jp/contests/yahoo-procon2019-qual/tasks/yahoo_procon2019_qual_e

$ N $ 行 $ M $ 列のマス目があります。 各マスには $ 0 $ または $ 1 $ の整数が書かれていて、上から $ i $ 行目、左から $ j $ 列目に書かれている整数は $ a_{ij} $ です。

行の部分集合 $ A $ と列の部分集合 $ B $ の組 $ 2^{N+M} $ 通りのうち、以下の条件を満たすものの個数を $ 998244353 $ で割ったあまりを求めてください。

- $ A $ に属する行と $ B $ に属する列の交わりに属する $ |A||B| $ 個のマスに書かれた整数の総和が奇数である

## 说明/提示

### 制約

- $ 1\ \leq\ N,M\ \leq\ 300 $
- $ 0\ \leq\ a_{i,j}\ \leq\ 1(1\leq\ i\leq\ N,1\leq\ j\leq\ M) $
- 入力はすべて整数である

### Sample Explanation 1

例えば、$ A $ として $ 1 $ 行目のみを選び、$ B $ として $ 1,2 $ 列目を選んだとき、その交わりに属するマスに書かれた整数の和は $ 0+1=1 $ になります。

## 样例 #1

### 输入

```
2 2
0 1
1 0```

### 输出

```
6```

## 样例 #2

### 输入

```
2 3
0 0 0
0 1 0```

### 输出

```
8```

# 题解

## 作者：irris (赞：7)

本篇题解最早在 2023-01-01 提交并通过，今天（2024-11-25）修改了一些表述。

## Description

给出 $n\times m$ 的 $\verb!01!$ 矩阵，选择若干行和若干列，求有多少种选法满足选择的行列交点的异或和为 $1$。

$1 \leq n, m \leq 300$。

## Solution

看到异或想到[线性基](https://www.luogu.com.cn/problem/P3812)。

我们不妨考虑一个经典问题：给定 $n$ 个数，问你有多少个子集满足异或和为 $0$。

这个题我们是这么做的：先给这 $n$ 个数建线性基，然后答案就是 $2^{n-\text{线性基的大小}}$。证明：线性基外的元素任选，选择一些线性基内的元素调整成 $0$。这是根据线性基和异或的定义来的。

这个 $0$ 当然可以换成任何数，只要能被异或出来就行。

---

回到本题。

我们先从选择若干行下手。答案只可能和每一列分别异或起来有关。那么我们看异或后的结果。因为异或完也只有 $0, 1$，所以线性基的大小肯定是 $1$。那么看 $1$ 能否被线性基表示，就是问这个线性基里面元素是 $0$ 还是 $1$。

你一拍大腿，是 $0$ 不就相当于这堆数全 $0$ 吗！剩下的其他所有组合都有 $2^{m-1}$ 种选法（列的线性基的大小 $=1$）。

至于异或起来全 $0$ 行的个数......等等我们怎么又回到这个问题了？

所以做完了，答案是 $(2^n - 2^{cnt})\times 2^{m-1}$，其中 $cnt$ 是 **把每一行看做一个 $\bm m$ 位二进制数** 得到的线性基大小。

时间复杂度 $\mathcal O(\dfrac{n^2m}{w})$。

---

## 作者：Lynkcat (赞：3)

注意到一件事，我们选取一些行异或起来后得到一个结果，如果这个结果不是每列都是 $0$ 的话我们可以挑出任意一个为 $1$ 的列先不去选它，然后别的列随便选 $2^{m-1}$ 种方案，最后用这一列来调整成奇数。

所以说现在只要求异或出来为全 $0$ 的方案数就行了。典中典问题了，直接线性基就行了。

复杂度 $O(\frac{n^3}{w})$。

```c++
// Lynkcat.
// Problem: E - Odd Subrectangles
// URL: https://atcoder.jp/contests/yahoo-procon2019-qual/tasks/yahoo_procon2019_qual_e
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// -----------------------------------------------

//我耳朵瞎掉拉~~
#include<bits/stdc++.h>
#define poly vector<int>
#define IOS ios::sync_with_stdio(false)
#define ll long long
#define mp make_pair
#define mt make_tuple
#define pa pair < int,int >
#define fi first
#define se second
#define inf 1e18
#define mod 998244353
#define int ll
#define N 305
using namespace std;
int n,m;
bitset<305>b[N],f[N];
int cnt;
int quickPower(int x,int y)
{
	int res=1;
	while (y)
	{
		if(y&1)res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
void BellaKira()
{
	cin>>n>>m;
	for (int i=1;i<=n;i++)
	{
		for (int j=0;j<m;j++)
		{
			int x;
			cin>>x;
			b[i][j]=x;
		}
	}
	for (int i=1;i<=n;i++)
		for (int j=m-1;j>=0;j--)
			if (b[i][j])
			{
				if (f[j][j])
				{
					b[i]^=f[j];
					continue;
				}
				f[j][j]=b[i][j];
				cnt++;
				break;
			}
	cout<<(quickPower(2,n)-quickPower(2,n-cnt)+mod)%mod*quickPower(2,m-1)%mod<<endl;
			
}
signed main()
{
	int T=1;
	while (T--)
	{
		BellaKira();
	}
}
```



---

## 作者：under_the_time (赞：2)

## 题意

> 给定一个 $n\times m$ 的 $\texttt{01}$ 矩阵 $A$，现在你要选出若干行与若干列，这些行与列会产生若干个交点，设这些交点的集合为 $S=\{(x_1,y_1),(x_2,y_2),\cdots,(x_k,y_k)\}$，求有多少种选法使得 $\sum_{i=1}^k A_{x_iy_i}\bmod2=1$ 即交点权值和为奇数，答案对 $998244353$ 取模。
>
> $1\le n,m\le 300$。

## 题解

首先，权值和为奇数相当于权值异或和为 $1$。考虑这样一件事情：我们钦定了若干行 $l_1,l_2,\cdots,l_p$，如果存在一个 $q$，满足第 $q$ 列上第 $l_1,l_2,\cdots,l_p$ 行的权值异或和为 $1$，那么有一种选择的方案是：先不选第 $q$ 列，其他列随便选，若选完后发现交点异或和是 $0$，则选第 $q$ 列使异或和变为 $1$，否则不选。显然这个选择方案囊括所有合法情况，此时对答案的贡献为 $2^{m-1}$。

若找不到这样一个 $q$ 呢？显然此时对答案无贡献。不妨考虑把每一行从左到右看成一个二进制数，那么不存在这个 $q$，当且仅当所有选中的行对应的二进制数的异或和为 $0$。

这个问题等价于，给你 $n$ 个数，要你求所有异或和为 $0$ 的子集的数量。考虑线性基，先把所有数插进去，设此时线性基大小为 $k$，那么答案就是 $2^{n-k}$。原理和上面选列的方案差不多，考虑线性基外元素任选，得到一个异或和，再把这个异或和拿到线性基里选数异或成 $0$，由线性基定义可知一定选的出来。

综上，答案为 $(2^n-2^{n-k})\times 2^{m-1}$。我们需要一个可以处理 $2000$ 位二进制数的线性基，大力 bitset 即可通过，时间复杂度 $O\left(\cfrac{nm^2}w\right)$。

## 代码

```cpp
#include <bits/stdc++.h>
bool MemoryST; using namespace std;
#define ll long long
#define mk make_pair
#define open(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout)
#define abs(x) (((x) > (0)) ? (x) : (-(x)))
#define lowbit(x) ((x) & (-(x)))
#define lson l, mid, rt << 1
#define rson mid + 1, r, rt << 1 | 1
#define BCNT __builtin_popcount
#define cost_time (1e3 * clock() / CLOCKS_PER_SEC) << "ms"
#define cost_space (abs(&MemoryST - &MemoryED) / 1024.0 / 1024.0) << "MB"
const int inf = 0x3f3f3f3f; 
const ll linf = 1e18; 
mt19937 rnd(random_device{}());
template<typename T> void chkmax(T& x, T y) { x = max(x, y); }
template<typename T> void chkmin(T& x, T y) { x = min(x, y); }
const int maxn = 2005, P = 998244353;
namespace ModOptions_normal {
    int add(int x, int y) { return (x + y) % P; } void addto(int &x, int y) { (x += y) %= P; }
    int mul(int x, int y) { return 1ll * x * y % P; } void multo(int &x, int y) { x = mul(x, y); }
    int qp(int x, int y) {
        int res = 1; for (; y; y >>= 1, multo(x, x))
            if (y & 1) multo(res, x);
        return res;
    } int divv(int x, int y) { return 1ll * x * qp(y, P - 2) % P; } void divto(int &x, int y) { x = divv(x, y); } 
    int sub(int x, int y) { return (x + P - y) % P; } void subto(int &x, int y) { x = sub(x, y); }
} using namespace ModOptions_normal;
int n, m, a[maxn][maxn];
namespace LinearBasis {
    bitset<maxn> b[maxn], cur;
    int siz = 0;
    void insert(int p) {
        for (int i = 1; i <= m; i ++)
            cur[i] = a[p][i];
        for (int i = 1; i <= m; i ++) if (cur[i]) {
            if (!b[i][i]) return siz ++, b[i] = cur, void(0);
            cur ^= b[i];
        }
    }
} using namespace LinearBasis;
bool MemoryED; int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= m; j ++)
            scanf("%d", &a[i][j]);
        insert(i);
    } printf("%d\n", mul(sub(qp(2, n), qp(2, n - siz)), qp(2, m - 1)));
    return 0;
}
```

---

## 作者：rizynvu (赞：2)

[我的博客](https://www.cnblogs.com/rizynvu/p/18331138)。

首先对于 $0 / 1$ 和为奇数，转化为异或为 $1$ 来考虑。

考虑如果已经确定了行的选取，又该如何计数。  
考虑对于每一列，都处理好在对应行的位置的异或值。  
然后记 $\operatorname{c}_0, \operatorname{c}_1$ 表示列异或值为 $0 / 1$ 的数量。  

知道了 $\operatorname{c}_0, \operatorname{c}_1$ 之后，就可以直接根据 $\operatorname{c}_0, \operatorname{c}_1$ 来计数了。  
首先对于 $0$ 来说随便选都行，方案数就为 $2^{\operatorname{c}_0}$。  
对于 $1$ 来说就要求选的数量为奇数个，因为当 $n\ge 1$ 时，$\sum\limits_{i = 0}^n (-1)^i\binom{n}{i} = 0$，说明当 $n\ge 1$ 时 $\sum\limits_{0\le i\le n, i \bmod 2 = 1} \binom{n}{i} = 2^{n - 1}$，于是可以知道这部分的数量为 $\begin{cases}2^{\operatorname{c_1} - 1} & \operatorname{c_1}\ge 1\\ 0 & \operatorname{c_1} = 0\end{cases}$。  
两部分相乘，就知道最后的方案数为 $\begin{cases}2^{m - 1} & \operatorname{c_1}\ge 1 \\ 0 & \operatorname{c}_1 = 0\end{cases}$。

那么就可以去容斥，计数选择行的方案数使得每一列对应异或出来都为 $0$（$\operatorname{c}_1 = 0$）。

这部分是好算的。  
考虑异或线性基，方案数就为 $2^{z}$（$z$ 为自由元个数）。  
证明考虑每个自由元都对应着一种不相同的线性组合方式，不管怎样组合得到的方案都不一样。

可以用 `bitset` 优化线性基。

时间复杂度 $\mathcal{O}(\frac{nm^2}{\omega})$。

```cpp
#include<bits/stdc++.h>
using ll = long long;
constexpr ll mod = 998244353;
inline ll qpow(ll b, ll a = 2, ll v = 1) {
   while (b) b & 1 && ((v *= a) %= mod), b >>= 1, (a *= a) %= mod;
   return v;
}
const int maxn = 3e2 + 10;
std::bitset<maxn> a, w[maxn];
int main() {
   int n, m; scanf("%d%d", &n, &m);
   ll tot = 1;
   for (int T = 1; T <= n; T++) {
      for (int i = 1, x; i <= m; i++)
         scanf("%d", &x), a.set(i, x);
      int f = 1;
      for (int i = 1; i <= m; i++) {
         if (! a[i]) continue;
         if (! w[i][i]) {
            f = 0, w[i] = a;
            break;
         }
         a ^= w[i];
      }
      if (f)
         (tot <<= 1) %= mod;
   }
   printf("%lld\n", (qpow(n) - tot + mod) * qpow(m - 1) % mod);
   return 0;
}
```

---

## 作者：oyoham (赞：1)

### Problem  
给定 $n \times m$ 的 $01$ 矩阵，选定一些行列，使相交部分的和为奇数，问有多少种选法。
### Solution
考虑将题目转化，相交部分的和为奇数可转化为相交部分的异或和为 $1$。  
考虑已经确定选择某些行，对应的每一列的异或值均为 $0$ 或 $1$，此时，若所有列都没有 $1$，则无论怎么选异或和均为 $0$，则方案数为 $0$，若有至少一个 $1$，则先枚举其他 $m-1$ 列选不选，则通过这列来调整异或和，这样，我们就把问题转化成求**异或起来存在一列不为 $\bm{0}$ 的行的选择方案数**乘上 $2^{m-1}$。  
求异或起来存在一列不为 $0$ 的行的选择方案数可以将每一行的数看作一个二进制的数，就变成要求找选择多少个数异或起来不为零，我们对行做线性基，线性基有个性质是异或为 $0$ 的个数为二的长度减线性基大小次方，设行的线性基大小为 $x$，则最终答案为 $2^{m-1}\times\left(2^{n}-2^{x}\right)$。
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll __int128
#define int ll
inline ll read(){
	ll x=0;
	short f=1;
	char c=getchar();
	while(c>57||c<48){
		if(c==45) f=-1;
		c=getchar();
	}
	while(c<58&&c>47){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
inline void write(ll x){
	if(x<0ll) putchar(45),x=~x+1;
	if(x>9ll) write(x/10);
	putchar(x%10|48);
}
#define mod 998244353
int n=read(),m=read();
bitset<320>l[320],a;
int fp(int x){
	int ans=(1ll<<(x&31))%mod,base=(1ll<<32)%mod;
	x>>=5;
	while(x){
		if(x&1) (ans*=base)%=mod;
		(base*=base)%=mod;
		x>>=1;
	}
	return ans;
}
signed main(){
	int S=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a.set(j,read());
		}
		for(int j=1;j<=m;j++){
			if(a[j]){
				if(!l[j][j]){
					l[j]=a;
					break;
				}
				a^=l[j];
			}
			if(j==m) S++;
		}
	} 
	write((fp(n)-fp(S)+mod)%mod*fp(m-1)%mod);
}
```

---

## 作者：喵仔牛奶 (赞：0)

怎么题解全是线性基，来点高消做法。

# Solution

> 性质：对矩阵进行初等变换（模 $2$ 意义下），答案不变。

- 交换不用说。
- 一行加上另一行相当于异或两行。记 $x,y$ 是原来两行的 $1$ 个数，$y'$ 是两行异或后的 $1$ 个数，容易发现 $y'\equiv x+y\pmod 2$，证明就是异或只会减少成对的 $1$。那么原来选了两行，就把第一行删掉；只选了第二行，就加入第一行。方案一一对应，答案不变。
- 一列加上另一列同理。

我们直接用高消消成对角线，记消完剩下 $r$ 个 $1$，答案就是：
$$2^{n+m-2r}\sum_{i=1}^{r}[i\bmod2=1]\binom{r}{i}3^{r-i}$$

左边的 $2^{n+m-2r}$ 是为 $0$ 的行列，随便选；右边枚举选中的 $1$ 的个数 $i$，从 $r$ 个中选出 $1$ 个，剩下 $r-i$ 个 $1$ 只有不是行列同时选就行了，方案为 $3^{r-i}$。

用 bitset 优化，时间复杂度 $\mathcal{O}(\dfrac{n^2m}{\omega})$。

# Code

```cpp
namespace Milkcat {
	using namespace Math;
    typedef long long LL;
    typedef pair<LL, LL> pii;
    const int N = 305, mod = 998244353;
    typedef Mint<mod> MI;
    int n, m, x; MI ans;
	bitset<N> A[N];
	Combinations<MI> C;
    int main() {
		cin >> n >> m, C.init(n + m);
		REP(i, 1, n) REP(j, 1, m)
			cin >> x, A[i][j] = x;
		int r = 0;
		REP(k, 1, m) {
			int t = 0;
			REP(i, r + 1, n)
				if (A[i][k]) t = i;
			if (!t) continue;
			r ++, swap(A[r], A[t]);
			REP(i, 1, n)
				if (i != r && A[i][k]) A[i] ^= A[r];
		}
		REP(i, 0, r)
			if (i & 1) ans += C(r, i) * qpow((MI)3, r - i);
		cout << ans * qpow((MI)2, n + m - r * 2) << '\n';
        return 0;
    }
}
```

---

## 作者：封禁用户 (赞：0)

考虑选出了行，有多少列满足。

　　把每一行的 $01$ 序列看成一个二进制数，如果选出的行的异或起来是 $0$，那么说明不论怎么选列的集合，都不能是奇数。如果异或起来不是 $0$，那么选列的方案数是 $2m-1$。

　　于是考虑多少种行的选法，使得异或起来不是 $0$，线性基求出基的大小，设为 $cnt$，那么 $2n-cnt$
就是异或和为 $0$ 的方案数，用总的减去，就是异或和不是 $0$ 的方案数。

```bitset``` 优化：
```
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cmath>
#include<cctype>
#include<set>
#include<queue>
#include<vector>
#include<map>
#include<bitset>
using namespace std;
typedef long long LL;

inline int read() {
    int x=0,f=1;char ch=getchar();for(;!isdigit(ch);ch=getchar())if(ch=='-')f=-1;
    for(;isdigit(ch);ch=getchar())x=x*10+ch-'0';return x*f;
}

const int N = 305, mod = 998244353;
bitset<N>a[N], b[N];

int ksm(int a,int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = 1ll * res * a % mod;
        a = 1ll * a * a % mod;
        b >>= 1;
    }
    return res;
}

int main() {
    int n = read(), m = read(), cnt = 0;
    for (int i = 1; i <= n; ++i) 
        for (int j = 1; j <= m; ++j) a[i][j] = read();
    for (int i = 1; i <= n; ++i) 
        for (int j = 1; j <= m; ++j) 
            if (a[i][j]) {
                if (!b[j][j]) { 
                    b[j] = a[i];
                    cnt ++;
                    break;
                }
                else {
                    a[i] ^= b[j];
                }
            }
    cout << 1ll * (ksm(2, n) - ksm(2, n - cnt) + mod) % mod * ksm(2, m - 1) % mod;
    return 0;
}
```

---

## 作者：StarRain3 (赞：0)

蒟蒻第一道自己想出来的省选题。

这题的方法十分巧妙。

这题是一个矩阵，因此可以将和的奇偶性看成是异或和，是 $1$ 的就选出。通过杨辉三角的性质，选奇数行与偶数行确定的方案数是能求出来的，显然 $2^{m-1}$ 是最合理的，但是如果 $a$ 不是一个正整数，那么就不合法了，到了这里，我们自然而然就想到了[线性基](https://oi-wiki.org/math/linear-algebra/basis/)，我们直接选取线性基的结论，在线性基里选取任意子集的异或和，都是为 $0$ 的，最后二进制还可以优化一下，详细看代码：
```
#include <bits/stdc++.h>
using namespace std;
const int MaXN = 305;
const int MOD = 998244353
int n, m;
bitset < MaXN + 10 > a[MaXN + 10], b[MaXN + 10];//二进制优化

int read() {//快读模板
	int x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')
			f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x * f;
}

int pow_(int a, int b) {//快速幂
	int res = 1;
	while (b) {
		if (b & 1)
			res = (1LL * res * a) % MOD;
		a = (1LL * a * a) % MOD;
		b >>= 1;
	}
	return res;
}
int res;
int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			a[i][j] = (read() == 1);//01矩阵
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (a[i][j]) {//偶数列
				if (b[j][j])
					a[i] ^= b[j];
				else {//奇数列
					b[j] = a[i];
					r++;
					break;
				}
			}
	cout<<(pow_(2, n + m - 1) - pow_(2, n - r + m - 1) + MOD) % MOD<<endl;//根据杨辉三角，推出公式，用快速幂维护一下
}

```

---

