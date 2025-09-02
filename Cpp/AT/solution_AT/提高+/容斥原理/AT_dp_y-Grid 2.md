# Grid 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/dp/tasks/dp_y

縦 $ H $ 行、横 $ W $ 列のグリッドがあります。 上から $ i $ 行目、左から $ j $ 列目のマスを $ (i,\ j) $ で表します。

グリッドのうち、$ N $ 個のマス $ (r_1,\ c_1),\ (r_2,\ c_2),\ \ldots,\ (r_N,\ c_N) $ は壁のマスであり、それら以外のマスはすべて空マスです。 マス $ (1,\ 1) $ および $ (H,\ W) $ は空マスであることが保証されています。

太郎君は、マス $ (1,\ 1) $ から出発し、右または下に隣り合う空マスへの移動を繰り返すことで、マス $ (H,\ W) $ まで辿り着こうとしています。

マス $ (1,\ 1) $ から $ (H,\ W) $ までの太郎君の経路は何通りでしょうか？ $ 10^9\ +\ 7 $ で割った余りを求めてください。

## 说明/提示

### 制約

- 入力はすべて整数である。
- $ 2\ \leq\ H,\ W\ \leq\ 10^5 $
- $ 1\ \leq\ N\ \leq\ 3000 $
- $ 1\ \leq\ r_i\ \leq\ H $
- $ 1\ \leq\ c_i\ \leq\ W $
- マス $ (r_i,\ c_i) $ はすべて相異なる。
- マス $ (1,\ 1) $ および $ (H,\ W) $ は空マスである。

### Sample Explanation 1

経路は次図の $ 3 $ 通りです。 !\[\](https://img.atcoder.jp/dp/grid\_1\_0\_muffet.png)

### Sample Explanation 2

経路が存在しない場合もあります。

### Sample Explanation 4

答えを $ 10^9\ +\ 7 $ で割った余りを出力することを忘れずに。

## 样例 #1

### 输入

```
3 4 2
2 2
1 4```

### 输出

```
3```

## 样例 #2

### 输入

```
5 2 2
2 1
4 2```

### 输出

```
0```

## 样例 #3

### 输入

```
5 5 4
3 1
3 5
1 3
5 3```

### 输出

```
24```

## 样例 #4

### 输入

```
100000 100000 1
50000 50000```

### 输出

```
123445622```

# 题解

## 作者：GaryH (赞：20)

# AT4546 题解

一道简单的计数题。

首先可以想到一种简单而暴力的DP方法：

计 $dp(i,j)$ 代表原地图中从 $(1,1)$ 走到 $(i,j)$ ，不经过任何障碍的方案数，那么 $dp(h,w)$ 即为答案。

但是这样无论是时间复杂度还是空间复杂度都会爆炸，所以我们需要优化不必要且繁琐的状态。

首先假设地图中没有障碍，那么这样的方案数可以用组合数算，即:

在一张无障碍的地图中，从 $(1,1)$ 走到 $(i,j)$ 的方案数为：

$\dbinom {i+j-2}{i-1}$ 

至于原因，是可以把一条路径的走法理解为，从 $i+j-2$ 次移动中选择 $i-1$ 次向下，其他的向右，而按这样选择的走就一定能到达点 $(i,j)$ 。

那如果地图中有一个障碍呢？

这样就不好用组合数直接统计了，实际上在这种情况下，直接正方向的计算并不轻松，那正难则反，我们就考虑如何把所有路径中，经过了障碍的给去掉。

于是我们来计算所有经过了障碍的路径：

设障碍的位置为 $(x,y)$ , 则经过障碍的方案数为，

从 $(1,1)$ 到 $(x,y)$ 的方案数与从  $(x,y)$ 到 $(h,w)$ 的方案数之积。

一个障碍的方案数计算出来了，那再加一个障碍呢？再加 $n$ 个障碍呢？

一种暴力的方法就是，把每个经过一个障碍的路径从总方案数里去掉，在把所有经过两个障碍的路径加回来，再把三条的删去，...... 诸如此类，用容斥的思想把答案计算出来。但这样的复杂度实在不能接受，故我们要考虑一种不会算重的计数方法，以省略掉复杂度极高的枚举和容斥。

于是我们可以计 $dp(i)$  代表从 $(1,1)$ 到第 $i$ 个障碍 $(x_i,y_i)$ ，中间不经过其他障碍的方案数。当然，我们可以令 $(h,w)$ 为第 $n+1$ 个障碍，那么答案就是 $dp(n+1)$ 。

我们发现，可以合理的利用以前计算过的方案数不重不漏地推出当前的状态，即：

$dp(i)= \tbinom {x_i+y_i-2}{x_i-1}- \sum_{j=1}^{i-1}{dp(j) \times \tbinom {x_i-x_j+y_i-y_j}{x_i-x_j}} $

看起来这个似乎很像把经过一个障碍的方案数扣掉了，就不管了？那为什么是对的呢？

实际上，这个和扣掉一个点的方法并不一样，因为 $dp(i)$  记录的是不经过任何障碍的方案数，

故上面的转移方程式中， $\sum_{j=1}^{i-1}{dp(j) \times \tbinom {x_i-x_j+y_i-y_j}{x_i-x_j}}$ 所去除掉的路径都一定是不重不漏的，因为任意一个 $j$ 对应的都是第一次经过障碍 $j$ 的方案数，而和式中任意一个小于 $j$ 的 $k$ ，$k$ 在和式中去掉的路径第一次经过的障碍都不是 $j$ ，所以一定没有被多次去除掉的路径，这就是对于上述转移方程式的正确性证明。

那么我们只要预处理出阶乘以及其逆元，从而 $O(1)$ 的计算组合数即可。

因为计算某一个 $i$ 的方案数所用的时间是 $O(n)$ 级别的，所以总复杂度是 $O(n^2)$ 的。

**Code**: 

```

const int N(3e5+10);
const int mod(1e9+7);

int n,h,w;

int dp[N];
int inv[N];
int fiv[N];

pair < int , int > p[N] ;

inline int ksm(int a,int b){
	int res=1;
	while(b){
		if(b&1)(res*=a)%=mod;
		(a*=a)%=mod,b>>=1;
	} return res%mod;
}

inline int C(int x,int y){
	return (inv[x]*fiv[y]%mod)*fiv[x-y]%mod;
}

signed main(){
	h=read(),w=read(),n=read();
	rep(i,1,n)p[i].fi=read(),p[i].se=read();
	p[n+1].fi=h,p[n+1].se=w;
	sort(p+1,p+n+1),inv[0]=fiv[0]=1;
	rep(i,1,N-10ll)inv[i]=(inv[i-1]*i)%mod,fiv[i]=ksm(inv[i],mod-2);
	dp[0]=1ll,p[0].fi=p[0].se=1;
	rep(i,1,n+1){ dp[i]=C(p[i].fi+p[i].se-2,p[i].fi-1)%mod;
	rep(j,1,i-1){
		if(p[j].fi>p[i].fi||p[j].se>p[i].se)continue;
		int XL=p[i].fi-p[j].fi,YL=p[i].se-p[j].se;
		dp[i]-=dp[j]*C(XL+YL,XL)%mod,dp[i]=(dp[i]+mod)%mod;
	} }
	cout<<dp[n+1]%mod;
	return 0;
}

```

---

## 作者：BIG_CUTE_BUG (赞：12)

[**题传**](https://www.luogu.com.cn/problem/AT_dp_y)

## 思路
升级版的杨辉三角加上乘法逆元。

显然本题不能像 Grid 1 一样递推求解，因为会炸时间和空间。那么看是否能找到一些规律，而去掉 Grid 1 中冗杂的递推。

先从最简单的情形开始。

在没有障碍的情况下，设走到点 $ (i,j) $ 的方案数为 $ sol_{i,j} $。

那么有：
$$ sol_{i,j}=sol_{i-1,j}+sol_{i,j-1} $$

而网格 $H \times W$ 的最上一行和最左一列的方案数都为一，那么有：
$$
\begin{aligned}
sol_{1,j}&=1,1 \le j \le W\\
sol_{i,1}&=1,1 \le i \le H
\end{aligned}
$$

将图一画，便是一个从杨辉三角的顶点截取的一个矩形。

因为是杨辉三角，那么有：
$$ sol_{i,j}=C^{i-1}_{i+j-2} \text{ or } C^{j-1}_{i+j-2} $$

这就是对于没有障碍情况的方案数。

接下来考虑有障碍的情况。

那么对于某一个障碍，如果它出现在了一个**原本没有障碍**的网格里，因为方案数是**沿着右下方**进行递推的，那它势必会令**它右下方的每个点**的方案数受到影响（也就是减去某个值）。

![](https://cdn.luogu.com.cn/upload/image_hosting/dykmvygu.png)

由乘法原理，对于点 $(i,j)$，这个所需减去的值应该为，**起始点到障碍**的方案数，乘上**障碍到点** $(i,j)$ 的方案数，得到的**乘积**。

而若再加入一个障碍，它对它右下的点的影响同上。但**注意**，如果它在**第一个障碍**的右下方，那它的方案数也会受到影响，也需减去**第一个障碍**所给到的影响值。

因为我们只求点 $(H,W)$ 的方案数，所以**只**用记录并递推**每个障碍点**的方案数，**途中**将**每个障碍点**给点 $(H,W)$ 的**影响值**加在一个 `ans` 里，最后将点 $(H,W)$ 在**没有障碍的网格中**的方案数，减去 `ans` 即可。

设点 $u$ 为某障碍点，点 $ v $ 为 $u_i$ 右下的障碍点集合，以上可表述为：
$$
\begin{aligned}
ans&=ans+sol_{u}\times {C_{H+W-u_x-u_y}^{H-u_x}}\\
sol_v&=sol_v- sol_u \times C_{v_x+v_y-u_x-u_y}^{v_x-u_x}
\end{aligned}
$$

其中**递推每个障碍点**的方案数时，可以按障碍点的**坐标**，**从上到下从左到右**遍历。然后每个点递推时，算出它**右下**的**每个障碍点**的方案数。这样可以保证**先算的点**不会受**后算的点**的影响。

另外，在**求组合数**的时候要**预处理**出**阶乘逆元**，算的时候用
$$ C_n^m= n! \times m!^{-1} \times (n-m)!^{-1}(\text{mod }10^9+7)$$
来 $ O(1) $ 的计算，不然会超时。(可参考 CSDN 某个大佬的文章 [link](https://blog.csdn.net/boliu147258/article/details/105758354))

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N= 1e5+ 5, mod= 1e9+ 7;
typedef long long ll;
int n, m, t, inv[N<< 1], fac[N<< 1], finv[N<< 1];
ll ans, val[3003];
struct points
{
	int x, y;
	bool operator < (const points &op) const
	{
		if(x== op.x) return y< op.y;
		return x< op.x;
	}
} p[3003];
ll C(int x, int y)//y个里选x个
{
	return (ll)fac[y]* finv[x]% mod* finv[y- x]% mod;
}
signed main()
{
	scanf("%d%d%d", &n, &m, &t);
	for(int i= 1; i<= t; i++) scanf("%d%d", &p[i].x, &p[i].y);

	//预处理阶乘和阶乘逆元
	fac[0]= fac[1]= finv[0]= finv[1]= inv[0]= inv[1]= 1;
	for(int i= 2; i<= n+ m; i++)
	{
		fac[i]= (ll)fac[i- 1]* i% mod;
		inv[i]= (ll)(mod- mod/ i)* inv[mod% i]% mod;
		finv[i]= (ll)finv[i- 1]* inv[i]% mod;
	}

	sort(p+ 1, p+ t+ 1);//排序方便遍历
	for(int i= 1; i<= t; i++) val[i]= C(p[i].x- 1, p[i].x+ p[i].y- 2);
	for(int u= 1; u<= t; u++)
	{
		ans= (val[u]* C(n- p[u].x, n+ m- p[u].x- p[u].y)% mod+ ans)% mod;
		for(int v= u+ 1; v<= t; v++)
		{
			if(p[v].y< p[u].y) continue;//如果在右下方才算，不然就跳过
			val[v]= (-C(p[v].x- p[u].x, p[v].x+ p[v].y- p[u].x- p[u].y)* val[u]% mod+ val[v])% mod;
		}
	}
	printf("%lld", (C(n- 1, n+ m- 2)- ans+ mod)% mod);
	return 0;
}
```

---

## 作者：ZolaWatle (赞：9)

### 题目大意

给定一个 $H\times W$ 的方格图，其中有 $n$ 个格子 $(x_1,y_1),(x_2,y_2),\cdots,(x_n,y_n)$ 是障碍格子，剩下的格子都代表着空地。现在从方格 $(1,1)$ 出发要走到终点 $(H,W)$，每一步只能往下或往右走且不能通过障碍格子，求一共有多少种走法。答案对 $10^9+7$ 取模。

$2\leq H,W\leq 10^5,\ 1\leq n\leq 3\times 10^3$。

### 解题思路

首先考虑当没有障碍时有多少种走法。我们设 $f_{i,j}$ 为从 $(1,1)$ 走到 $(i,j)$ 的方案数。我们发现 $f_{i,j}$ 有：

$\begin{cases} f_{1,i}&=1 \\ f_{i,1}&=1 \\ f_{i,j}&= f_{i,j-1}+f_{i-1,j} \end{cases}$

容易给出它的封闭形式 $f_{n,m} = \binom{n-1}{n+m-2}$。（$\binom{x}{y}$，即组合数 $\text{C}_y^x$）

接下来我们考虑从起点 $(1,1)$ 走到第 $i$ 个障碍的方案数（当然在这里我们假定这个位置上没有障碍）。由上面的讨论，我们有方案数 $g_i = \binom{x_i-1}{x_i+y_i-2}$。然而，这只是不考虑途中有其它障碍的情况。

我们定义障碍 $i$ 在障碍 $j$ **之前**，当且仅当 $x_i\leq x_j$ 且 $y_i\leq y_j$。显然，由于移动只有右、下两个方向，访问到 $i$ 的次序一定会在 $j$ 之前。于是我们设 $h_i$ 为从起点走到第 $i$ 个障碍，并且其间不经过其他任意障碍的方案数。我们知道，$h_i$ 的值应为 $g_i$ 再减去所有由 $(1,1)$ 经由所有 $i$ **之前**的障碍方格再最终走到第 $i$ 个障碍处的方案总和。

可以考虑使用 $\text{DP}$。设状态 $dp_i$ 表示从起点走到第 $i$ 个障碍处且途中不经过其它障碍的方案数。我们先将所有的障碍方格按照之前对于**“之前”**的定义排序，使得对于 $\forall j$ 满足 $1\leq j<i$，障碍 $j$ 在障碍 $i$ **之前**。我们考虑从障碍 $j$ 走到障碍 $i$ 的方案数，由之前的推导，将 $(x_j,y_j)$ 视作 $(1,1)$，容易得到方案数为 $\binom{x_i-x_j}{x_i-x_j+y_i-y_j}$。那么考虑上从起点到障碍 $j$ 的方案总数，由乘法原理，对于 $dp$ 数组就有以下转移：

$ dp_i = \binom{x_i-1}{x_i+y_i-2} - \sum\limits_{j=1}^{i-1}dp_j\cdot \binom{x_i-x_j}{x_i-x_j+y_i-y_j} $。

在原先 $n$ 个障碍的基础上，我们额外加入新的第 $ n+1 $ 个障碍 $(H,W)$。由于我们假设走到的障碍格子并没有障碍，而第 $n+1$ 个格子，即我们的终点，本身就不是一个障碍格子，则最终的 $dp_{n+1}$ 即为答案。

使用阶乘+逆元的方法预处理出组合数，即可做到 $\text{O}(n^2)$ 的时间复杂度。

### 完整代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define rep(i,a,b) for(int i=(a),i##end=(b);i<=i##end;++i)
#define pre(i,a,b) for(int i=(a),i##end=(b);i>=i##end;--i)
#define mem(arr,val) memset(arr,val,sizeof(arr))
#define cpy(a1,a2) memcpy(a1,a2,sizeof(a2))
using namespace std;

const int N=3e3+10,M=3e5+10;
const ll mod=1e9+7;
int H,W,n;
ll jc[M],inv[M];
struct Barrier
{
	int x,y;
	bool operator <(const Barrier &oth) const
	{
		return x==oth.x?y<oth.y:x<oth.x;
	}
}a[N];

inline int rint()
{
    int x=0,f=1; char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48); ch=getchar();}
    return x*f;
}
inline ll rll()
{
    ll x=0ll,f=1ll; char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1ll; ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48); ch=getchar();}
    return x*f;
}

inline ll ksm(ll x,ll k)
{
	ll ret=1ll;
	while(k)
	{
		if(k&1)
			ret=ret*x%mod;
		x=x*x%mod;
		k>>=1;
	}
	return ret;
}
inline ll C(ll n,ll m)  //C(n,m)
{
	return jc[n]*inv[m]%mod*inv[n-m]%mod;
}

ll dp[N];

signed main()
{
	H=rint(),W=rint(),n=rint();
	rep(i,1,n) a[i].x=rint()-1,a[i].y=rint()-1;
	a[++n]=(Barrier){H-1,W-1};
	sort(a+1,a+n+1);
	
	jc[0]=inv[0]=1ll;
	rep(i,1,M-10)
	{
		jc[i]=jc[i-1]*(1ll*i)%mod;
		inv[i]=ksm(jc[i],mod-2)%mod;
	}
	
	rep(i,1,n)
	{
		int x=a[i].x,y=a[i].y;
		dp[i]=C((ll)x+y,(ll)x);
		rep(j,1,i-1) if(a[j].x<=x&&a[j].y<=y)
		{
			int lx=x-a[j].x,ly=y-a[j].y;
			dp[i]=(dp[i]-dp[j]*C((ll)lx+ly,(ll)lx)%mod+mod)%mod;
		}
	}
	
	printf("%lld",dp[n]);
    return 0;
}
```

感谢阅读！

---

## 作者：K8He (赞：5)

# [「题解报告」Grid 2](https://www.luogu.com.cn/problem/AT_dp_y)

[DP26 题解](https://www.cnblogs.com/Keven-He/p/AtCoderDP26Problems.html)

## 思路

容斥 DP。

首先我们知道从 $(x1,y1)$ 走到 $(x2,y2)$ 的方案数为 $cnt(x1,y1,x2,y2)=\dbinom{\left|x1+y1-x2-y2\right|}{\left|x1-x2\right|}$。

（从 $(x1,y1)$ 走到 $(x2,y2)$ 必然需要 $\left|x1+y1-x2-y2\right|$ 步，在其中选出 $\left|x1-x2\right|$ 步作为向下走的方案数）

然后我们考虑一下从 $(1,1)$ 走到一个不能经过的点 $(x_i,y_i)$ 有多少种方案。答案显然不是 $cnt(1,1,x_i,y_i)$，因为路上会有不能经过的点。

那么进行一下容斥：**用总方案数减去经过不能经过的点的方案数。**

那么设 $f_i$ 表示从 $(1,1)$ 走到一个不能经过的点 $(x_i,y_i)$ 有多少种方案，则：

$$
f_i=cnt(1,1,x_i,y_i)-(\sum_{i\neq j}[x_j\le x_i][y_j\le y_i]\times cnt(x_i,y_i,x_j,y_j)\times f_j)
$$

答案显然就是：

$$
cnt(1,1,h,w)-\sum_{1\le i\le n}cnt(h,w,x_i,y_i)\times f_i
$$

时间复杂度 $O(n^2)$。

## 代码


```cpp
namespace SOLVE {
	typedef long double ldb;
	typedef long long ll;
	typedef double db;
	const ll N = 1e6 + 10, M = 1e6, P = 1e9 + 7;
	ll h, w, n, fac[N], inv[N], f[N], ans;
	class hinder {
	public:
		ll x, y;
		inline bool operator < (const hinder another) const {
			return (x == another.x) ? (y < another.y) : (x < another.x);
		}
	} hd[N];
	inline ll rnt () {
		ll x = 0, w = 1; char c = getchar ();
		while (!isdigit (c)) { if (c == '-') w = -1; c = getchar (); }
		while (isdigit (c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getchar ();
		return x * w;
	}
	inline ll FastPow (ll a, ll b) {
		ll ans = 1;
		while (b) {
			if (b & 1) ans = ans * a % P;
			a = a * a % P, b >>= 1;
		}
		return ans;
	}
	inline void Pre () {
		fac[0] = 1;
		_for (i, 1, M) fac[i] = fac[i - 1] * i % P;
		inv[M] = FastPow (fac[M], P - 2);
		for_ (i, M - 1, 0) inv[i] = inv[i + 1] * (i + 1) % P;
		return;
	}
	inline ll C (ll n, ll m) {
		if (!m) return 1;
		if (n < m) return 0;
		return fac[n] * inv[n - m] % P * inv[m] % P;
	}
	inline ll GetCnt (ll i, ll j) {
		return C (hd[i].x - hd[j].x + hd[i].y - hd[j].y, hd[i].x - hd[j].x);
	}
	inline void In () {
		h = rnt (), w = rnt (), n = rnt ();
		_for (i, 1, n) hd[i].x = rnt (), hd[i].y = rnt ();
		std::sort (hd + 1, hd + n + 1);
		hd[0].x = hd[0].y = 1, hd[n + 1].x = h, hd[n + 1].y = w;
		return;
	}
	inline void Solve () {
		_for (i, 1, n) {
			f[i] = GetCnt (i, 0);
			_for (j, 1, i - 1) {
				if (hd[j].y > hd[i].y) continue;
				f[i] = (f[i] - GetCnt (i, j) * f[j] % P + P) % P;
			}
		}
		ans = GetCnt (n + 1, 0);
		_for (j, 1, n) ans = (ans - GetCnt (n + 1, j) * f[j] % P + P) % P;
		return;
	}
	inline void Out () {
		printf ("%lld\n", ans);
		return;
	}
}
```

---

## 作者：DengDuck (赞：3)

原题变量叫做 $h,w,n$ 对应我的 $n,m,k$。

题目条件是一个障碍都不能碰，考虑转化，计算至少碰到一个障碍的方案数。

不难想到，枚举一条路径第一次碰到的障碍，求出这些方案数，从总方案数减去即可。

也就是：

$$
\text{Ans}=\operatorname{C}_{n+m-2}^{n-1}-\sum_{i=1}^kf_i\operatorname{C}_{n+m-x_i-y_i}^{n-x_i}
$$

$f_i$ 表示到达第 $i$ 个障碍的方案数。

求解 $f_i$ 考虑容斥，是类似 $\text{Ans}$ 的求解的:

$$
f_i=\operatorname{C}_{x_i+y_i-2}^{x_i-1}-\sum_{x_j\leq x_i,y_j\leq y_i}f_j\operatorname{C}_{x_i+y_i-x_j-y_j}^{x_i-x_j}
$$

直接求解即可，顺便，把 $(n,m)$ 当成第 $k+1$ 个障碍，$f_{k+1}$ 就是答案，比较好写。

时间复杂度为 $\mathcal O(k^2)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define LL long long
using namespace std;
const LL N=2e5+10;
const LL mod=1e9+7;
struct node
{
    LL x,y;
}a[N];
LL ksm(LL x,LL y)
{
    LL ans=1;
    while(y)
    {
        if(y&1)ans=ans*x%mod;
        x=x*x%mod,y>>=1;
    }
    return ans;
}
LL n,m,k,inv[N],f[N],fac[N];
LL C(LL n,LL m)
{
    return fac[n]*inv[m]%mod*inv[n-m]%mod;
}

int main()
{
    scanf("%lld%lld%lld",&n,&m,&k);
    for(int i=1;i<=k;i++)
    {
        scanf("%lld%lld",&a[i].x,&a[i].y);
    }
    a[k+1]={n,m};
    sort(a+1,a+k+1,[](node x,node y){return x.x+x.y<y.x+y.y;});
    fac[0]=1;
    for(int i=1;i<=n+m;i++)fac[i]=fac[i-1]*i%mod;
    inv[n+m]=ksm(fac[n+m],mod-2),inv[0]=1;
    for(int i=n+m-1;i>=1;i--)inv[i]=inv[i+1]*(i+1)%mod;
    for(int i=1;i<=k+1;i++)
    {
        f[i]=C(a[i].x+a[i].y-2,a[i].x-1); 
        for(int j=1;j<=i-1;j++)
        {
            if(a[j].x>a[i].x||a[j].y>a[i].y)continue;
            LL t1=a[i].x-a[j].x,t2=a[i].y-a[j].y;
            f[i]=(f[i]-f[j]*C(t1+t2,t1)%mod+mod)%mod;
        }
    }
    printf("%lld",f[k+1]);
}
```

---

## 作者：qiuweilin666 (赞：3)

本题本质是对 dp 思想的一种优化。

我们发现，这个组合数来源于将该棋盘视作一个杨辉三角，然后 dp 方案数，推出的结论满足斜杨辉三角。

那么我们恢复这个思想，由于不能用的点比较少，我们按不能用的点走。先将所有不能用的点按 $x$ 为第一关键字，$y$ 为第二关键字排序。
 
接下来我们设 $dp_{i}$ 表示从原点到 $i$ 点不经过其他不能用的点的方案数。其中枚举的所有 $i$ 点都是不能用的点（或终点），以下给出原理：

其实我们可以设 $dp_{i}$ 是所有点的方案数，但这样时空都承受不了。

但我们会发现，不能用的点是很少的，于是我们仅需讨论不能用的点即可。

因为讨论到任何一个点的方案数，都只需要这个点之前不能用的点的方案数。所以这样做是正确的。

对所有 $i$，$dp_{i}$ 的初值应当都是原点到 $i$ 的方案数（即
 $C^{x_{i}+y_{i}}_{x_{i}}$ )。

而为了不经过其他的障碍点，我们需要排除前面一些障碍点的方案。

对于每个 $i$，我们仅需枚举所有 $i$ 之前的 $j$，使 $x_{i} \ge x_{j}$ , $y_{i} \ge y_{j}$。

然后可以得出状态转移方程 $dp_{i}=dp_{i}-dp_{j} \times C^{x_{i}-x_{j}+y_{i}-y_{j}}_{x_{i}-x_{j}}$。

这里算出的就是同时至少经过 $i$，$j$ 两点的方案数。

至于会不会重叠，由于我们按 $x$，$y$ 排过序，再考虑原先的 $dp_{j}$ 都是只经过 $j$ 这一个障碍物的，所以不会有重叠。

最后贴个代码，线性筛阶乘逆元 $+$ 组合数 dp。
```cpp
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#define ll long long
#define mode 1000000007
#define maxn 200000
using namespace std;
ll inv[200005];
ll mul[200005];
void init()
{
  inv[1]=1;
  inv[0]=1;
  mul[0]=1;
  for(int i=2;i<=maxn;i++)
    {
      inv[i]=(mode-mode/i)*inv[mode%i]%mode;
    }
  for(int i=1;i<=maxn;i++)
    {
      inv[i]*=inv[i-1];
      inv[i]%=mode;
      mul[i]=mul[i-1]*i;
      mul[i]%=mode;
    }
}
int n,m,k;
struct Bad
{
  int x,y;
}p[3005];
ll dp[3005];
bool cmp(Bad a,Bad b)
{
  if(a.x==b.x)
    {
      return a.y<b.y;
    }
  return a.x<b.x;
}
ll C(int x,int y)
{
  return mul[x]%mode*inv[y]%mode*inv[x-y]%mode;
}
int main()
{
//   freopen("path.in","r",stdin);
//   freopen("path.out","w",stdout);
  scanf("%d%d%d",&n,&m,&k);
  init();
  for(int i=1;i<=k;i++)
    {
      scanf("%d%d",&p[i].x,&p[i].y);
    }
    k++;
    p[k].x=n;
	p[k].y=m;
  sort(p+1,p+k+1,cmp);
  for(int i=1;i<=k;i++)
    {
      dp[i]=C(p[i].x+p[i].y-2,p[i].x-1);
      for(int j=1;j<i;j++)
	{
	  if(p[j].x<=p[i].x&&p[j].y<=p[i].y)
	    {
	      dp[i]-=dp[j]*C(p[i].x-p[j].x+p[i].y-p[j].y,p[i].x-p[j].x)%mode;
	    }
	}
      dp[i]=(dp[i]%mode+mode)%mode;
    }
  printf("%lld\n",dp[k]);
}
```

---

## 作者：OldDriverTree (赞：2)

计数 DP 好题。

# Solution
先把不能经过的位置按 $x$ 为第一关键字，$y$ 为第二关键字排遍序。

令第 $N+1$ 个障碍物为 $(H,W)$。

考虑设 $f_i$ 表示从 $(1,1)$ 开始走，途中不经过其他障碍物，到达第 $i$ 个障碍物的方案数。

由于直接组合不好算，考虑补集转化：$f_i$ 就为 $(1,1)\rightarrow(r_i,c_i)$ 的所有方案数减去途中经过障碍物的方案数。

$(1,1)\rightarrow(r_i,c_i)$ 的所有方案数就为 $C_{r_i+c_i-2}^{r_i-1}$（一共要走 $r_i+c_i-2$ 步，选择 $r_i-1$ 步向下走）。

求经过障碍物的方案数，考虑枚举经过的第一个障碍物 $j$，方案数就为 $(1,1)$ 到 $(r_j,c_j)$ 不经过障碍物的方案数乘从这个障碍物到第 $i$ 个障碍物的所有方案数，减去的总方案数就为 $\sum f_j\times C_{r_i-r_j+c_i-r_j}^{r_i-r_j}(r_j\le r_i,c_j\le c_i)$。

状态转移方程就为 $f_i=C_{r_i+c_i-2}^{r_i-1}-\sum f_j\times C_{r_i-r_j+c_i-c_j}^{r_i-r_j}(r_j\le r_i,c_j\le c_i)$。

答案就为 $f_{N+1}$。

DP 前预处理一下阶乘，时间复杂度就为 $O(N^2+H+W)$。

# Code
```c++
#include<bits/stdc++.h>
#define P pair<int,int>
#define F first
#define S second
using namespace std;
const int mod=1e9+7;
const int N=3001,M=2e5;
int fact[M],ifact[M];
int n,m,s,V,f[N];
P a[N];

int C(int x,int y) {
	return 1ll*fact[x]*ifact[x-y]%mod*ifact[y]%mod;
}
int solve(int x,int y) {
	return C(x+y,y);
}
int power(int a,int b=mod-2)
{
	int ans=1;
	while (b) {
		if (b&1) ans=1ll*ans*a%mod;
		a=1ll*a*a%mod,b>>=1;
	}
	return ans;
}
int main()
{
	scanf("%d%d%d",&n,&m,&s),V=n+m-2;
	for (int i=0;i<s;i++) scanf("%d%d",&a[i].F,&a[i].S);
	fact[0]=1; for (int i=1;i<=V;i++) fact[i]=1ll*fact[i-1]*i%mod;
	ifact[V]=power(fact[V]); for (int i=V;i;i--) ifact[i-1]=1ll*ifact[i]*i%mod;
	sort(a,a+s),a[s]={n,m};
	
	for (int i=0;i<=s;i++) {
		f[i]=solve(a[i].F-1,a[i].S-1);
		for (int j=0;j<i;j++) if (a[j].S<=a[i].S)
		f[i]=(f[i]-1ll*f[j]*solve(a[i].F-a[j].F,a[i].S-a[j].S)%mod+mod)%mod;
	}
	printf("%d",f[s]);
	return 0;
}
```

---

## 作者：FelFa_1414666 (赞：2)

这是一道比较典型的 **dp** 结合**组合数**的题目。

[atcoder 题目传送门](https://atcoder.jp/contests/dp/tasks/dp_y) & [洛谷题目传送门](https://www.luogu.com.cn/problem/AT4546)

[更好的阅读体验](https://www.luogu.com.cn/blog/xesssb10108899/solution-at4546)

---

## Description

有一个 $H\times W$ 的网格，有 $n$ 个障碍物，坐标分别为 $(r_i,c_i)$。求从 $(1,1)$ 走到 $(n,m)$，不经过障碍物的方案数。答案对 $10^9+7$ 取模。

- $2\le H,W\le 10^5$

- $1\le n\le 3000$

- $1\le r_i\le H$

- $1\le c_i\le W$

---

## Analysis

网格的大小已经超出时空限制了，但是障碍物的数量在 3000 以下，我们考虑从障碍物入手处理。

> 设**没有障碍物**的情况下，从 $(x1,y1)$ 到 $(x2,y2)$($x1\le x2$ 且 $y1\le y2$) 的总方案数为$\operatorname F(x1,y1,x2,y2)$ 。

这个函数相当于从 $x2-x1+y2-y1$ 个步数中选 $x2-x1$ 步向下走，所以：

$$\operatorname F(x1,y1,x2,y2)=\dbinom{x2-x1+y2-y1}{x2-x1}$$

我们可以通过**递推预处理阶乘及其逆元**来算组合数。

---

## Solution

接下来回到原题。那么我们要考虑在**有障碍物**的情况下可能性少了多少，即**经过障碍物的方案有多少种**。

首先，我们将障碍物**按照 $x$ 第一关键字，$y$ 第二关键字进行升序排序**，保证转移是正确有序的。

根据障碍物的编号设计 dp 状态：

- $dp_i$ 表示从起点到第 $i$ 个障碍物，中间经过其他障碍物的方案数。

转移：

对于每一个 $dp_i$，枚举从起点到第 $i$ 个障碍物中间**第 1 个经过的障碍物**是哪个，即**在经过这个障碍物前没有经过其他障碍物**，这样方案一定不重复不遗漏。

$$dp_i=\sum\limits_{x_j\le x_i,y_j\le y_i}\Bigg(\bigg(\operatorname F\big(1,1,x_j,y_j\big)-dp_j\bigg)\times \operatorname F\big(x_j,y_j,x_i,y_i\big)\Bigg)$$

时间复杂度：$\operatorname O(n^2)$

空间复杂度：$\operatorname O(n)$

---

## Code

```c++
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pii pair<int,int>
#define mp make_pair
#define F first
#define S second
using namespace std;
const ll MOD=1e9+7;
int n,m,k;//这里由于个人习惯，H和W用n，m表示，题中n用k表示
ll fact[200005],inv[200005],finv[200005],dp[3005];//fact阶乘，inv逆元，finv阶乘的逆元
struct Wall//定义障碍物类
{
	int x,y;
	bool operator<(Wall &b)
	{
		if (x!=b.x)
			return x<b.x;
		return y<b.y;
	}
}a[3005];
ll C(int a,int b)//求组合数
{
	return fact[a]*finv[b]%MOD*finv[a-b]%MOD;
}
int main()
{
	ios::sync_with_stdio(false),cin.tie(nullptr);
	cin>>n>>m>>k;
	fact[0]=fact[1]=inv[1]=finv[0]=finv[1]=1ll;
	for(int i=2;i<=n+m;i++)
	{//递推预处理阶乘及其逆元
		fact[i]=fact[i-1]*i%MOD;
		inv[i]=(MOD-MOD/i)*inv[MOD%i]%MOD;
		finv[i]=finv[i-1]*inv[i]%MOD;
	}
	for(int i=0;i<k;i++)
	{
		cin>>a[i].x>>a[i].y;
		a[i].x--;a[i].y--;//0-base
	}
	sort(a,a+k);//排序
	a[k].x=n-1,a[k].y=m-1; //定义终点为第k个障碍物
	for(int i=1;i<=k;i++)
		for(int j=0;j<i;j++)
			if (a[j].x<=a[i].x&&a[j].y<=a[i].y)//按照公式转移
				dp[i]=(dp[i]+(C(a[j].x+a[j].y,a[j].x)+MOD-dp[j])%MOD*C(a[i].x-a[j].x+a[i].y-a[j].y,a[i].x-a[j].x)%MOD)%MOD;
	cout<<(C(n+m-2,n-1)+MOD-dp[k])%MOD<<endl;//最终答案为起点到终点总方案数-经过障碍物的方案书
	return 0;
}
```

希望题解对你有帮助！

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_dp_y)

# 前置知识

[计数 DP](https://oi-wiki.org/dp/count/) | [排列组合](https://oi-wiki.org/math/combinatorics/combination/)

# 解法

正难则反，考虑求出总方案数和至少经过一个黑色格子的方案数，二者作差即为所求。

强制增加一个黑色格子 $(h,w)$，使得存在一条至少经过一个黑色格子的路径。

如果没有“不能移动到黑色格子中”的限制，那么就是一个简单的格路计数问题，方案数为 $\dbinom{h+w-2}{h-1}$。

对黑色格子以行坐标为第一关键字，列坐标为第二关键字升序排序。

设 $f_{i}$ 表示从左上角到排序后的第 $i$ 个黑色格子的方案数，状态转移方程为 $f_{i}=\dbinom{x_{i}+y_{i}-2}{x_{i}-1}-\sum\limits_{j=1}^{i-1}[x_{i} \ge x_{j}] \times [y_{i} \ge y_{j}] \times f_{j} \times \dbinom{x_{i}-x_{j}+y_{i}-y_{j}}{x_{i}-x_{j}}$。

最终，有 $f_{n+1}$ 即为所求。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
const ll p=1000000007;
ll f[3010],inv[200010],jc[200010],jc_inv[200010];
pair<ll,ll>a[3010];
ll C(ll n,ll m,ll p)
{
    return (n>=m&&n>=0&&m>=0)?(jc[n]*jc_inv[m]%p)*jc_inv[n-m]%p:0;
}
int main()
{
    ll h,w,n,i,j;  
    cin>>h>>w>>n;
    inv[1]=1;
    jc[0]=jc_inv[0]=jc[1]=jc_inv[1]=1;
    for(i=2;i<=h+w-2;i++)
    {
        inv[i]=(p-p/i)*inv[p%i]%p;
        jc[i]=jc[i-1]*i%p;
        jc_inv[i]=jc_inv[i-1]*inv[i]%p;
    }
    for(i=1;i<=n;i++)
    {
        cin>>a[i].first>>a[i].second;
    }
    n++;
    a[n]=make_pair(h,w);
    sort(a+1,a+1+n);
    for(i=1;i<=n+1;i++)
    {
        f[i]=C(a[i].first+a[i].second-2,a[i].first-1,p);
        for(j=1;j<=i-1;j++)
        {
            if(a[j].first<=a[i].first&&a[j].second<=a[i].second)
            {
                f[i]=(f[i]-f[j]*C(a[i].first-a[j].first+a[i].second-a[j].second,a[i].first-a[j].first,p)%p+p)%p;
            }
        }
    }
    cout<<f[n]<<endl;
    return 0;
}
```

# 后记

多倍经验：[CF559C Gerald and Giant Chess](https://www.luogu.com.cn/problem/CF559C)

---

## 作者：foryou_ (赞：0)

首先我们来考虑题目的弱化版。

若地图中没有障碍，

则从 $(1,1)$ 走到 $(H,W)$ 需要 $H+W-2$ 步，

其中往右的步数为 $H-1$，

于是答案即为：

$$
C_{H-1}^{H+W-2}
$$

当存在 $1$ 个障碍 $(r,c)$ 时，

考虑用总方案数减去会到达障碍的方案数，

于是答案即为：

$$
C_{H-1}^{H+W-2}- C_{r-1}^{r+c-2} \times C_{H-r}^{H-r+W-c}
$$

当存在 $N$ 个障碍 $(r_{i},c_i)$ 时，

我们令 $dp_i$ 表示从 $(1,1)$ 走到第 $i$ 个障碍且中间无障碍时的路径方案数，

若令 $(H,W)$ 为第 $N+1$ 个障碍，则此时答案为 $dp_{N+1}$，

于是易得转移方程：

$$
dp_i=C_{r_i-1}^{r_i+c_i-2}-\sum_{j=1}^{i-1} dp_j \times C_{r_i-r_j}^{r_i-r_j+c_i-c_j}
$$

（其中 $r_i \ge r_j$ 且 $c_i \ge c_j$）

这个转移方程的意思就是将从 $(1,1)$ 到 $(r_i,c_i)$ 的总方案数

减去经过它前面任意其他障碍而到达它的路径。

注意：

- 求组合数要预处理阶乘与逆元来实现 $O(1)$ 计算。

- $(r_i,c_i)$ 要按左端点排序。

[实现](https://www.luogu.com.cn/paste/iatbgnyj)是简单的。时间复杂度 $O(N^2)$。

---

## 作者：LCat90 (赞：0)

我们考虑总方案减去经过黑格子的方案。但是普通容斥要炸上天，看到 $n$ 在 $10^3$ 级别，猜测应该是个枚举前驱的 dp。

$dp_i$ 表示从起点到 $i$ 不经过黑点的方案。枚举 $dp_j$，根据 dp 定义此时 $1\to j$ 不经过黑点，但是经过 $j$。为了避免重复，我们令此时 $1\to j$ 不经过黑点，$j\to i$ 随便走；最后用总方案数减去所有 $j$ 的贡献就可以了。

为什么这样会避免重复呢？因为 $j$ 是连续的，所以就是等价于减去了经过 1 的，不经过 1 经过 2 的，不经过 1,2 经过 3 的……或者说，$1\to j$ 的这一段都是固定并且不一样的，后面 $j\to i$ 不管怎么重复都不影响了。不错的一个**容斥**。 

给出转移方程式：

$$dp_i=C_{x_i+y_i-2}^{x_i-1}-\sum _ {j=1,x_j\le x_i,y_j\le y_i}^{i-1} dp_j\times C_{x_i+y_i-x_j-y_j}^{x_i-y_i}$$

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3e5 + 5, Mod = 1e9 + 7; 
int n, a, b, fac[N], ifac[N], dp[N];
int qkpow(int a, int b) {
	if(b == 0) return 1;
	if(b & 1) return a * qkpow(a, b - 1) % Mod;
	int t = qkpow(a, b >> 1);
	return t * t % Mod;
} 
struct node { 
	int x, y; 
	friend bool operator < (node a, node b) { 
		if(a.x == b.x) return a.y < b.y;
		return a.x < b.x; 
	}
} p[N];
int C(int n, int m) { return fac[n] * ifac[m] % Mod * ifac[n - m] % Mod; }
signed main() {	
	cin >> a >> b >> n; int m = 2 * max(a, b); fac[0] = 1;
	for(int i = 1;i <= m; ++i) fac[i] = fac[i - 1] * i % Mod; 
	ifac[m] = qkpow(fac[m], Mod - 2);
	for(int i = m - 1;i >= 0; --i) ifac[i] =  ifac[i + 1] * (i + 1) % Mod;
	for(int i = 1;i <= n; ++i) scanf("%lld %lld", &p[i].x, &p[i].y);
	p[++n] = (node){a, b};
	sort(p + 1, p + n + 1);
	for(int i = 1;i <= n; ++i) {
		dp[i] = C(p[i].x + p[i].y - 2, p[i].x - 1); // 到 i 的总路径 
		for(int j = 1;j < i; ++j) 
			if(p[j].x <= p[i].x and p[j].y <= p[i].y) 
				dp[i] = (dp[i] - dp[j] * C(p[i].x + p[i].y - p[j].x - p[j].y, p[i].x - p[j].x) % Mod + Mod) % Mod;
	}
	cout << dp[n];
	return 0;
}
```

---

## 作者：lhc0707 (赞：0)

[AtCoder题目传送门](https://atcoder.jp/contests/dp/tasks/dp_y)


## 题意

给定一个 $H \times W$ 的矩阵，并给出 $N$ 个不能走的障碍，问从点 $(1,1)$ 走到点 $(H,W)$ 共有多少种走法，对 $10^9+7$ 取模。其中，$ 2\ \leq\ H,\ W\ \leq\ 10^5 $ ,$N \leq 3000$。

## 题解

如果我们像 [本题的弱化版](https://atcoder.jp/contests/dp/tasks/dp_h) 那样暴力转移的话，空间和时间都会爆炸，观察到 $N$ 的取值较小，在可接受范围内，考虑在这 $N$ 个点上做文章。

先考虑一种特殊情况，当 $N=0$ 时，也就是没有障碍的时候，设 $dp_{i,j}$ 表示从 $(1,1)$ 到 $(i,j)$ 有多少种路径。我们可以知道：

$$
dp_{n,m}=C_{n+m-2}^{n-1}
$$

其中，$C_{a}^{b}$ 表示从 $a$ 个数中选取 $b$ 个数进行无序组合，也就是组合数。

证明：从 $(1,1)$ 走到 $(n,m)$，必然共走了 $n+m-2$ 步，其中必然有 $n-1$ 步向下，选出这 $n-1$ 步来，剩下的也就是向右走的步数。

当障碍数不为 $0$ 的时候，就不好用组合数直接统计路径条数了，正着不行反着来，我们考虑算出总共的路径条数，再减去和障碍相关的路径数量，就可以求出答案了。

具体地，我们不妨设点 $(H,W)$ 处为第 $n+1$ 个障碍，设 $F_i$ 表示从 $(1,1)$ 到第 $i$ 个点的合法路径条数。我们找到所有可以到达第 $i$ 个障碍的障碍 $j$ ，减去与 $j$ 相关的路径条数，就可以求出 $F_i$。我们可以很容易地列出转移式：

$$F_i=C_{x_i+y_i-2}^{x_i-1}-\sum _{j=1,x_j \leq x_i,y_j \leq x_j}^{n}F_j*C_{x_i-x_j+y_i-y_j-2}^{x_i-x_j-1} $$

用阶乘和逆元求出组合数，即可通过本题。

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
#define MAXN 3005
#define il inline
#define int long long
const int mod=1e9+7;
struct pos{
	int x,y;
}dat[MAXN];
bool cmp(pos a,pos b){
	if(a.x==b.x)return a.y<b.y;
	return a.x<b.x;
}
int H,W,n,F[MAXN];
int fac[200005],inv[200005];
il int qPow(int a,int k){
	int ret=1;
	for(;k;k>>=1,a=(a*a)%mod)if(k&1)ret=(ret*a)%mod;
	return ret%mod;
}
il int C(int n,int m){return fac[n]*inv[m]%mod*inv[n-m]%mod;}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>H>>W>>n;
	for(int i=1;i<=n;i++)cin>>dat[i].x>>dat[i].y; 
	dat[++n].x=H,dat[n].y=W,fac[0]=1,inv[0]=1;
	for(int i=1;i<=n;i++)dat[i].x--,dat[i].y--; 
	sort(dat+1,dat+1+n,cmp);
	for(int i=1;i<=H+W+1;i++)fac[i]=(fac[i-1]*i)%mod;
	for(int i=1;i<=H+W+1;i++)inv[i]=qPow(fac[i],mod-2)%mod;
	for(int i=1;i<=n;i++){
		int x=dat[i].x,y=dat[i].y;
		F[i]=C(x+y,x)%mod;
		for(int j=1;j<i;j++)if(dat[j].x<=x&&dat[j].y<=y){
			int lx=x-dat[j].x,ly=y-dat[j].y;
			F[i]=(F[i]-F[j]*C(lx+ly,lx)%mod+mod)%mod;
		}
	}
	cout<<F[n]<<"\n";
	return 0;
}
```
双倍经验：[CF559C](https://www.luogu.com.cn/problem/CF559C)

---

## 作者：Helloworldwuyuze (赞：0)

# AT_dp_y 题解

### 题目大意

有一个 $h\times w$ 的网格，其中有 $n$ 个障碍，只能向下或向右走，求从 $(1,1)$ 走到 $(h,w)$ 的路径条数对 $10^9+7$ 取模的结果。

### Solution

#### 无障碍

首先，对于没有障碍的一张网格，显然我们从 $(x_1,y_1)$ 走到 $(x_2,y_2)(x_2\ge x_1,y_2\ge y_1)$ 的方案数是 $\binom{x_2-x_1+y_2-y_1} {x_2-x_1}$，感性一点的理解就是我们从 $(x_1,y_1)$ 走到 $(x_2,y_2)$ 需要走 $x_2-x_1+y_2-y_1$ 步，其中一部分是向下走，一部分是向右走，而其中向下走的步数必然是 $x_2-x_1$，在 $x_2-x_1+y_2-y_1$ 步中选出 $x_2-x_1$ 步向下走就是答案。

此时，答案为 $\binom{h+w-2}{h-1}$。

#### 一个障碍

再来考虑有一个障碍的情况。

一个很自然的想法是，我们将总的路径数算出来，然后减去经过障碍节点的路径数就是答案。那么对于一个障碍 $(x,y)(x\le h, y\le w)$，经过它的路径数量就是 $\binom{x+y-2}{x-1} \times \binom{h-x+w-y}{h-x}$。

所以最终的答案就是 $\binom{h+w-2}{h-1}-\binom{x+y-2}{x-1} \times \binom{h-x+w-y}{h-x}$

#### 多个障碍

对于多个障碍，最先想到的方法就是容斥，即总得方案数减去经过一个障碍的方案数，再加上经过两个障碍的路径数，再减去经过三个障碍的路径数 $\dots$ 最终我们就可以得到答案。

但是这样容斥的代码复杂度和时间复杂度都是不允许的，因此我们换一种思路。要想在 $O(n^2)$ 的时间复杂度内计算完成，似乎只有 DP 可以通过。我们设 $f_i$ 表示只通过 $i$ 这一个障碍有多少条路径。进而很自然地想到设 $(h,w)$ 为第 $n+1$ 个障碍，那么最终的答案就是 $f_{n+1}$。

至于状态转移方程，可以将障碍按照横向高度为第一关键字，纵向高度为第二关键字进行排序，那么对于每个障碍 $(x_i,y_i)$ 只需要枚举 $j\in [1,i-1]$，对于所有 $x_i\ge x_j $ 并且 $y_i\ge y_j$ 的 $j$，减去它的贡献就可以了。

具体的：

$$f_i=\binom{x_i+y_i-2}{x_i-1}-\sum_{j=1,x_j\le x_i,y_j\le y_i}^{i-1}f_j\times \binom{x_i-x_j+y_i-y_j}{x_i-x_j}$$

时间复杂度为 $O(n^2)$。

### AC CODE

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 3e3 + 10;
const int M = 2e5 + 10;
#define endl '\n'
#define int long long
const int MOD = 1e9 + 7;

int h,w,n;
pair<int,int> obs[N]; //障碍
int fact[M],infact[M],f[N]; //fact为阶乘数组，infact为阶乘的逆元
#define fi first
#define se second

int ksm(int x,int m){
	int ans=1;
	while(m){
		if(m&1)	ans=ans*x%MOD;
		x=x*x%MOD; m>>=1;
	}
	return ans;
} //快速幂

int C(int n,int m){
	return fact[n]*infact[n-m]%MOD*infact[m]%MOD;
} //组合数

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin>>h>>w>>n;
	for(int i=1;i<=n;++i)	cin>>obs[i].fi>>obs[i].se;
	obs[n+1]=make_pair(h,w); //将(h,w)设为第n+1个障碍
	sort(obs+1,obs+2+n); //排序

	fact[0]=1;
	for(int i=1;i<M;++i)	fact[i]=fact[i-1]*i%MOD;
	infact[M-1]=ksm(fact[M-1],MOD-2); infact[0]=1;
	for(int i=M-2;i>0;--i)
    	infact[i]=infact[i+1]*(i+1)%MOD; //线性求阶乘逆元(虽然没这个必要)
    
	for(int i=1;i<=n+1;++i){
		f[i]=C(obs[i].fi+obs[i].se-2, obs[i].fi-1);
		for(int j=1;j<i;++j)
			if(obs[i].fi>=obs[j].fi&&obs[i].se>=obs[j].se)
				f[i]=(f[i]-f[j]*C(obs[i].fi+obs[i].se-obs[j].fi-obs[j].se,obs[i].fi-obs[j].fi)%MOD+MOD)%MOD; //状态转移方程
	}
	cout<<f[n+1]<<endl;
	return 0;
}
```

---

## 作者：xxx2022 (赞：0)

双倍经验 [CF559C](https://www.luogu.com.cn/problem/CF559C)

前置知识：网格图内任意两点间的路径数量。这个我们可以通过组合数的方法计算出来。假设我们从点 $(1,1)$ 走到点 $(i,j)$，在这个过程中我们的移动步数是 $|i-1+j-1|=|i+j-2|$，其中有 $|i-1|$ 步需要向下走，那么路径数量即为 $\binom{i-1}{i+j-2}$。

然后我们就可以开始做这道题了。这题显然没有什么直接计算答案的方法，所以考虑正难则反。我们计算出到 $(h,w)$ 的所有不合法路径，再用总路径减去这个不合法路径数量即可。那么不合法路径数量怎么算呢？注意到从原点到 $(x,y)$ 的路径数量是可以直接计算的，我们可以考虑对每个不能走的点计算出从原点到它的路径数量。根据乘法原理，我们可以计算出从不合法点 $(x,y)$ 到终点 $(h,w)$ 的路径数量，再乘上从原点到 $(x,y)$ 的路径数量，这样即为经过这个点的不合法路径数量。但这样显然会算重。这里我们只需枚举每个不合法点 $i$ 的左上方的不合法点 $j$，利用乘法原理将 $i$ 的答案减去 $i \rightarrow j$ 的路径数量即可。时间复杂度 $O(n^2)$。这里由于我代码里没有预处理阶乘逆元所以复杂度应该还有一个 $\log n$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
const int N=1e5+10;
inline int read(){
    int f=1,w=0;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')  f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        w=(w<<1)+(w<<3)+(c^48);
        c=getchar();
    }
    return f*w;
}
int h,w,n;
struct node{
    int x,y;
    bool operator <(const node &a)const{
        if(x==a.x)  return y<a.y;
        return x<a.x;
    }
}a[3010];
int f[N];
int fac[N*2];
int quickpow(int x,int p){
    int ans=1;
    while(p){
        if(p&1) ans=ans*x%mod;
        x=x*x%mod;
        p>>=1;
    }
    return ans;
}
void init(){
    fac[0]=1;
    for(int i=1;i<=N*2+10;i++){
        fac[i]=fac[i-1]*i%mod;
    }
}
int C(int n,int m){
    return fac[n]*quickpow(fac[m],mod-2)%mod*quickpow(fac[n-m],mod-2)%mod;
}
signed main(){
    h=read();
    w=read();
    n=read();
    init();
    for(int i=1;i<=n;i++){
        a[i].x=read();
        a[i].y=read();
    }
    a[++n].x=h,a[n].y=w;
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++){
        f[i]=C(a[i].x+a[i].y-2,a[i].x-1);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++){
            if(a[j].x<=a[i].x&&a[j].y<=a[i].y){
                f[i]-=f[j]*C(a[i].x-a[j].x+1+a[i].y-a[j].y+1-2,a[i].x-a[j].x+1-1);
                f[i]=(f[i]+mod)%mod;
            }
        }
    }
    cout<<(f[n]+mod)%mod<<endl;
    return 0;
}
```

---

## 作者：NBest (赞：0)

## 思路
盯一眼数据范围，$H,W\le10^5,n\le 3000$，那大概就是个 $O(n^2)$，做法题了，只与障碍物有关。

不难发现，从 $(a,b)\to(c,d)$，我们一定会向右走 $c-a$ 步，向下走 $d-b$ 步，只不过是顺序的差别，方案数显然为 $\binom{(c-a)+(d-b)}{c-a}$。

正难则反，考虑容斥。

我们令 $con_i$ 表示不经过其他障碍物的情况下，走到第 $i$ 个障碍物的方案数，那么很显然可以得到结果为总方案减去经过之前的障碍物走到这里的方案，具体为：

$$\large con_i=\binom{x[i]+y[i]-2}{x[i]-1}-\sum_{x[j]<=x[i]}^{y[j]<=y[i]}con_j\times\binom{x[i]-x[j]+y[i]-y[j]}{x[i]-x[j]}$$

然后就做完了。
### $Code$
```cpp
int n,m,g;
typedef long long ll;
typedef pair<int,int> PII;
PII a[3003];
const ll mod=1e9+7;
ll fac[200005],ifac[200005],con[3003],ans;
ll qpow(ll x,ll w){
    ll res=1;
    for(;w;w>>=1,x=x*x%mod)if(w&1)res=res*x%mod;
    return res;
}
void init(){
    fac[0]=1;
    for(ll i=1;i<=n+m;i++)
        fac[i]=fac[i-1]*i%mod;
    ifac[n+m]=qpow(fac[n+m],mod-2);
    for(ll i=n+m-1;~i;--i)
        ifac[i]=ifac[i+1]*(i+1)%mod;
}
inline ll C(ll x,ll y){
    return fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}
int main(){
    n=read(),m=read(),g=read();
    for(int i=1;i<=g;i++)
        a[i].first=read(),a[i].second=read();
    sort(a+1,a+1+g);
    init();
    for(int i=1;i<=g;i++){
        int x=a[i].first,y=a[i].second;
        con[i]=C(x+y-2,x-1);
        for(int j=1;j<i;j++){
            int xx=a[j].first,yy=a[j].second;
            if(xx<=x&&yy<=y){
                con[i]=(con[i]-con[j]*C(x-xx+y-yy,x-xx)%mod+mod)%mod;
            }
        }
        ans=(ans+con[i]*C(n-x+m-y,n-x)%mod)%mod;
    }
    cout<<(C(n+m-2,n-1)-ans+mod)%mod;
    return 0;
}
```

---

## 作者：Obviathy (赞：0)

## Solution：

对于常规的 $1000\times1000$ 的图，直接标数法 DP 就行，但这题的数据范围显然不行。但我们发现障碍物很少，考虑排列组合加容斥。

我们令 $dp_{i}$ 记录第一个经过的障碍物是第 $i$ 个障碍物的路径数，其中，障碍物按照坐标升序。也就是说，我们记录的是从起点走到这个障碍物，期间不经过任何障碍物的方案。

那么考虑去 $i$。

如果起点和这个点之间没有任何障碍物，那么它就有 $\dbinom{x+y}{x}$ 种选择的路径，然后我们考虑枚举所有可以影响到它的障碍物，那么对于每一个障碍物 $j$，从起点到它且不经过障碍物的方案 $dp_j$ 我们已经事先计算出来了，那么考虑从起点到 $i$ 有多少条经过 $j$ 的路径，减去即可。那么就应该是 $dp_j\times\dbinom{x_i-x_j+y_i-y_j}{x_i-x_j}$，最后都减去，可以证明是正确的。

$$dp_i = \dbinom{x+y}{x}-\sum_{j=1}^{i-1}dp_j\times\dbinom{x_i-x_j+y_i-y_j}{x_i-x_j}$$

为了简便，我们把坐标都减 $1$。另外此处求组合数需要用到阶乘线性逆元。

## AC code:

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 3e3+10,mod = 1e9+7,M = 2e5+10;
ll h,w,m,inv[M],fact[M],dp[N];
struct node{
	int x,y;
}p[N];
bool cmp(node a,node b){
	if(a.x == b.x) return a.y < b.y;
	return a.x < b.x;
} 
ll ksm(ll a,ll k){
	ll res = 1;
	while(k){
		if(k&1)res = res * a % mod;
		a = a * a % mod;
		k >>= 1;
	}
	return res;
}
void init(){
	cin >> h >> w >> m;
	h--,w--;
	for(int i = 1;i <= m;i ++){
		cin >> p[i].x >> p[i].y;
		p[i].x --,p[i].y --;	
	}
	p[++m].x = h;p[m].y = w;
	sort(p+1,p+m+1,cmp);
	fact[1] = 1;
	for(int i = 2;i <= h+w;i ++)fact[i] = fact[i-1] * i % mod;
	inv[h+w] = ksm(fact[h+w],mod-2);
	for(int i = h+w-1;i >= 1;i --)inv[i] = inv[i+1] * (i+1) % mod;
	inv[0] = 1;
}
inline ll C(ll x,ll y){return fact[x+y] * inv[x] % mod * inv[y] % mod;}
void solve(){
	for(int i = 1;i <= m;i ++){
		dp[i] = C(p[i].x,p[i].y) % mod;
		for(int j = 1;j < i;j ++)
			if(p[j].x <= p[i].x && p[j].y <= p[i].y)
				dp[i] = (dp[i] - dp[j] * C(p[i].x-p[j].x,p[i].y-p[j].y) % mod + mod) % mod;
	}	
	cout << dp[m] << endl;
}
int main(){
	init();
	solve();
	return 0;
}
```

---

## 作者：creation_hy (赞：0)

# 思路

注意到坐标的数据范围很大，显然不能直接二维 dp，于是从 $n$ 入手。

首先考虑升序排序后第一个点（即前面没有遮挡）的答案，显然，此时 $f_1 = C_{(x_1-1)+(y_1-1)}^{(x_1-1)} = C_{x_1+y_1-2}^{x_1-1}$。

接着考虑遮挡。假设排序后第 $i$ 点为 $(x_i,y_i)$，第 $j$ 点为 $(x_j,y_j)$ ，并满足 $i < j,\ x_i \le x_j,\ y_i \le y_j$。

此时遮挡组合数为 $f_i \times C^{x_j-x_i}_{x_j-x_i+y_j-y_i}$。

动态规划转移方程：
1. 初始化：$f_i = C_{(x_i-1)+(y_i-1)}^{(x_i-1)} = C_{x_i+y_i-2}^{x_i-1}$
2. 递推：（$i < j,\ x_i \le x_j,\ y_i \le y_j$） $f_j = f_j - f_i \times C^{x_j-x_i}_{x_j-x_i+y_j-y_i}$

为了防止TLE，组合数不建议暴力计算，建议使用逆元快速计算。没用过逆元的可以先做一下这道[模版题](https://www.luogu.com.cn/problem/P3811)。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
const int mod = 1e9 + 7;
int r, c, n, h[N], inv[N], f[3005];
pair<int, int> e[3005];
inline int qpow(int x, int y)
{
    int res = 1;
    while (y)
    {
        if (y & 1)
            res = 1ll * res * x % mod;
        x = 1ll * x * x % mod;
        y >>= 1;
    }
    return res;
}
void init()
{
    h[0] = inv[0] = 1;
    for (int i = 1; i < N; i++)
    {
        h[i] = 1ll * h[i - 1] * i % mod;
        inv[i] = 1ll * inv[i - 1] * qpow(i, mod - 2) % mod;
    }
}
inline int C(int x, int y)
{
    return 1ll * h[x] * inv[y] % mod * inv[x - y] % mod;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> r >> c >> n;
    for (int i = 1; i <= n; i++)
        cin >> e[i].first >> e[i].second;
    sort(e + 1, e + 1 + n);
    e[++n] = make_pair(r, c);
    init();
    for (int i = 1; i <= n; i++)
        f[i] = C(e[i].first + e[i].second - 2, e[i].first - 1);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (e[i].second <= e[j].second)
                f[j] = (f[j] - 1ll * f[i] * C(e[j].first - e[i].first + e[j].second - e[i].second, e[j].first - e[i].first) % mod + mod) % mod;
    cout << f[n];
    return 0;
}
```

---

## 作者：minxu (赞：0)

[题目](https://www.luogu.com.cn/problem/AT4546)

我们先按$x$和$y$从小到大排序

$f[i]$表示到第i个不能走的位置且不经过其他不能走的位置的方案数 这里我们把终点也看做不能走的地方

转移就是一个小容斥 先算出所有方案数 然后枚举至少没有经过前几个不能走到地方再乘上从那个点到i点的路即组合数

即$f[i]=C(a[i].x+a[i].y,a[i].x)-\sum_{j=1}^{i-1}f[j]*C(a[i].x+a[i].y-a[j].x-a[j].y,a[i].x-a[j].x)$

注意初始坐标都要减$1$因为是从$(1,1)$出发 然后预处理组合数即可 如果模数不为质数的话就需要$lucas+crt$了 即上学路线那道题 

复杂度$O(n^2)$

```
#include <bits/stdc++.h>
#define ll long long
#define int long long
using namespace std;
template <typename T>
inline void read(T &x)
{
    int f = 1;
    x = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    if (f == -1)
        x = -x;
}
const int N = 1e6 + 10;
const int mod = 1e9 + 7;
ll n, m, t, tp;
ll f[N], fac[N], inv[N], g[N];
struct node
{
    int x, y;
} a[10000];
inline bool cmp(node x, node y)
{
    if (x.x == y.x)
        return x.y < y.y;
    return x.x < y.x;
}
ll ksm(ll a, ll b)
{
    ll res = 1, base = a % mod;
    while (b)
    {
        if (b & 1)
            res = res * base % mod;
        base = base * base % mod;
        b >>= 1;
    }
    return res;
}
ll C(int n, int m)
{
    return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
ll crt(int n, int m)
{
    return C(n, m);
}
signed main()
{
    read(n), read(m), read(t);
    for (int i = 1; i <= t; ++i)
        read(a[i].x), read(a[i].y), a[i].x--, a[i].y--;
    a[++t].x = n - 1, a[t].y = m - 1;
    sort(a + 1, a + t + 1, cmp);
    fac[0] = 1;
    for (int j = 1; j <= N - 100; ++j)
        fac[j] = fac[j - 1] * j % mod;
    inv[N - 100] = ksm(fac[N - 100], mod - 2);
    for (int j = N - 100; j >= 1; --j)
        inv[j - 1] = (inv[j] * (j)) % mod;
    for (int i = 1; i <= t; ++i)
    {
        f[i] = crt(a[i].x + a[i].y, a[i].x);
        // cout << f[i] << endl;
        for (int j = 1; j < i; ++j)
        {
            if (a[j].x <= a[i].x && a[j].y <= a[i].y)
                f[i] = (f[i] - f[j] * crt(a[i].x + a[i].y - a[j].x - a[j].y, a[i].x - a[j].x) % mod + mod) % mod;
        }
    }
    cout << f[t] << endl;
    return 0;
}
```


---

