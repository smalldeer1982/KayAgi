# Shaass and Lights

## 题目描述

There are $ n $ lights aligned in a row. These lights are numbered $ 1 $ to $ n $ from left to right. Initially some of the lights are switched on. Shaass wants to switch all the lights on. At each step he can switch a light on (this light should be switched off at that moment) if there's at least one adjacent light which is already switched on.

He knows the initial state of lights and he's wondering how many different ways there exist to switch all the lights on. Please find the required number of ways modulo $ 1000000007 (10^{9}+7) $ .

## 样例 #1

### 输入

```
3 1
1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4 2
1 4
```

### 输出

```
2
```

## 样例 #3

### 输入

```
11 2
4 8
```

### 输出

```
6720
```

# 题解

## 作者：RedreamMer (赞：4)

[$\Large\texttt{CF294C}$](https://www.luogu.com.cn/problem/CF294C)

[$\tiny\texttt{In my cnblogs}$](https://www.cnblogs.com/RedreamMer/p/14076452.html)

吐槽一句：真的是恶评，还有数据范围完全可以开到 $1e5$ 的。

做法：推式子

## 题意

不作赘述。

## 思路

+ 首先分别计算对于所有灯将这条线段所围成的每条线段的点灯方法，因为每条线段上要点的灯的个数一定，但是可以由左端点向右也可以从右端点向左（除了起始和结尾的两条线段），点灯的交错重复构成了一段序列。

	则我们要求的便可以简化为：在一段序列上涂色，两种颜色，则涂色方案便是 $2^{len}$ 。
   
   但是这是错的，当两边的灯点到只剩一个灯时，点下一个灯对于从左还是从右来说都是一样的，所以方案是 $2^{len-1}$。
   
+ （其实这是个经典问题）因为每段线段点灯的步骤互不干扰。

	先考虑两段区间 $A$ ， $B$ 一共的点亮方案，一种点亮 $A$ 区间的方案可以对应一种点亮 $B$ 区间的方案，首先的方案数便是 $calc_A\times calc_B$ ，其次，**合起来的每一种点亮方案**可以是 $A$ ， $B$ 区间交织起来，并且是**任意**交织，所以**合起来每一种方案**对应了 $C(len_A+len_B,len_A)$ 种方案，相乘便是两个区间一起点亮的方案数，扩展到第三个区间也是如此。
    
预处理出阶乘和逆元，通过 $\texttt{O(1)}$ 算组合数。

时间复杂度 $\texttt{O(NlogN)}$ （排序复杂度）。

注意特判开头的区间和结尾的区间，还有两盏灯之间没有灯可以点亮的情况。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

 #define int long long
 const int N = 1000;
 const int mod = 1e9+7;
inline int read()
{
    int s = 0;
    register bool neg = 0;
    register char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        neg |= (c == '-');
    for (; c >= '0' && c <= '9'; s = s * 10 + (c ^ 48), c = getchar())
        ;
    s = (neg ? -s : s);
    return s;
}

int a,b,fac[N+10],inv[N+10],power[N+10],s[N+10];

inline void init() {
	fac[0]=fac[1]=inv[0]=inv[1]=power[0]=1;
	for(int i=2;i<=N;i++) fac[i]=fac[i-1]*i%mod,inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	for(int i=1;i<=N;i++) inv[i]=inv[i-1]*inv[i]%mod,power[i]=power[i-1]*2%mod;
}

inline int C(int n,int m) {
	return fac[n]*inv[n-m]%mod*inv[m]%mod;
}

signed main()
{
//	freopen("in.txt","r",stdin);
	init();
	a=read();
	b=read();
	int pre=0,sum=0,ans=1,x=0;
	for(int i=1;i<=b;i++) s[i]=read();
	sort(s+1,s+b+1);
	for(int i=1;i<=b;i++) {
		x=s[i];
		sum+=x-pre-1;
		if(pre!=0&&pre<x-1) ans=(ans*C(sum,x-pre-1)%mod*(power[x-pre-2]))%mod;
		pre=x;
	}
	sum+=a-pre;
	ans=(ans*C(sum,a-x))%mod;
	printf("%lld",ans);
    return 0;
}
```

---

## 作者：RockyYue (赞：4)

# 解题思路

好水的紫题，感觉是黄 or 绿。

在以下的推导中，另 $l$ 为目前区间长度，$k$ 为目前区间中已点亮的灯的个数。

我们分三类讨论。

1. 对于正常情况，选择灯的方法有 $C_l^k$ 种，对于每种方法都可以从区间中选出若干个 $k'=0$ 的区间（$k'=l$ 的区间不需要处理）用 第二类的方法处理。

2. 对于 $k=0$ 的情况，我们只能从两端向中间点，每次可以点左边也可以点右边，中心点不需要选择，所有共有 $2^{l-1}$ 种方法。

3. 对于区间一段是端点的情况，我们只能从有亮灯的地方往另一端点，$1$ 种。

# 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1005, P = 1e9 + 7;
ll a[N], C[N][N];
void init_C() {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j <= i; ++j) {
			if (i == 0 || j == 0 || i == j) {
				C[i][j] = 1;
			} else {
				C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % P;
			}
		}
	}
}
ll qpow(ll x, ll y) {
	ll res = 1;
	while (y) {
		if (y & 1) {
			res = res * x % P;
		}
		x = x * x % P;
		y >>= 1;
	}
	return res;
}
int main() {
	ios :: sync_with_stdio(0);
	init_C();
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		cin >> a[i];
	}
	sort(a + 1, a + m + 1);
	ll res = 1;
	int k = n - m;
	for (int i = 1; i < m; ++i) {
		int l = a[i + 1] - a[i] - 1;
		if (!l) {
			continue;
		}
		res = res * C[k][l] % P * qpow(2, l - 1) % P;
		k -= l;
	}
	res = res * C[k][a[1] - 1] % P;
	cout << res << '\n';
	return 0;
}

```

Good Good 贺题，Day Day Up！！

---

## 作者：StillEmpty (赞：4)

**良心超细题解qwq**

$m$ 个已点亮的灯将序列分成 $m+1$ 段，以 $[1, m+1]$ 给每段编号。我们每次只能点亮一段最左边的灯或者最右边的灯。（有两个例外：最左边的段只能点亮最右边的灯，最右边的段只能点亮最左边的灯。）

我们要操作 $n-m$ 次，也就是给出一个长为 $n-m$ 的操作序列 $op$，按顺序依次操作 $op_i$（$1 \le i \le n-m$）。$op$ 中的每项都是一种操作，即点亮的段的编号与点亮的灯在该段最左还是最右。

例如，对于输入：
```
7 2
2 5
```
我们可以进行操作 $2l$(点亮第 $2$ 段最左边的灯)，则第 $3$ 个灯被点亮。
$op$ 可以为 $2l, 2r, 1r, 3l, 3l$。

我们先不考虑每次取左还是取右的，只考虑每次取得是第几段（这样刚才那个 $op$ 就变成了 $2, 2, 1, 3, 3$），那有多少种可能？

我们称第 $i$ 段的长度为 $l_i$，则总情况数为：
$$
\frac{(n-m)!}{\prod_{i=1}^{m+1}{l_i!}}
$$

这个肯定看得懂吧！

如果这看不懂，你这么理解：把 $op$ 全排列（即 $(n-m)!$ 种不同情况），因为有 $l_i$ 个数是完全一样的，所以可以将所有排列分成 $l_i!$ 组，组都是完全一样的。所以要除以上 $l_i!$。

然后每个的操作，可以为左也可以为右，所以每次都有 $2$ 种操作方式。**但是最后一次只有一种取法！！！让你点亮一盏灯，有几种点法？！**

综上，答案是
$$
\frac{(n-m)!}{\prod_{i=1}^{m+1}{l_i!}}\prod_{i=1}^{m+1}{2^{l_i-1}}
$$

可以用[乘法逆元](https://www.luogu.com.cn/problem/P3811)在模的意义下将除法转为乘法，在此不赘述。不过值得注意的是，由于 $10^9+5$ 并不是质数，所以无法通过费马小定理求出 $l_i!$ 在模 $10^9+7$ 意义下的乘法逆元，所以应该预处理 $l_i!$ 的逆元：
$$
(x!)^{-1} \equiv [(x-1)!]^{-1}x^{-1}\pmod{10^9+7}
$$

参考代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e3, MOD = 1e9+7;
int n, m, ans;
int pos[N+2]; // 每个灯的位置
int inv[N+1]; // 乘法逆元
int invfac[N+1]; // i! 的逆元
int two[N+1]; // 2^i;

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; ++i) scanf("%d", &pos[i]);

    sort(pos+1, pos+m+1);

    inv[1] = 1;
    for(int i = 2; i <= n; ++i) {
        inv[i] = ((long long)(MOD-MOD/i)*inv[MOD%i])%MOD;
    }

    invfac[1] = 1;
    for(int i = 2; i <= n; ++i) invfac[i] = ((long long)invfac[i-1]*inv[i])%MOD;

    two[0] = 1;
    for(int i = 1; i <= n; ++i) two[i] = (two[i-1]<<1)%MOD;

    ans = 1;
    for(int i = 2; i <= n-m; ++i) ans = ((long long)ans*i)%MOD;

    pos[m+1] = n+1;
    for(int i = 0; i <= m; ++i) {
        int l = pos[i+1]-pos[i]-1;
        if(l <= 0) continue;
        if(i > 0 && i < m) ans = ((long long)ans*two[l-1])%MOD;
        ans = ((long long)ans*invfac[l])%MOD;
    }

    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：Zelotz (赞：2)

对于给定的 $m$ 个点，将整个序列分为了 $m+1$ 段，我们可以先将每一段看作同一个类型，同一个类型间不同的顺序看作同一种。那么显然，答案即为可重集的排列数。

设 $\{S=n_1 \cdot a_1,n_2\cdot a_2,...,n_k \cdot a_k \}$ 表示由 $n_i$ 个 $a_i$ 组成的集合。那么此集合的排列数为 $\dfrac{(\sum\limits_{i=1}^n n_i)!}{\prod\limits_{i=1}^n n_i!}$。

再来看每一个相同类型的内部方案数。显然，对于非最左和最右的一段，每次我可以选择左右最后选择的两个端点的相邻点，设该相同类型的长度为 $len$，则方案数为 $2^{len-1}$。对前面的方案数相乘即可。

```
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define R(i, l, r) for (int i = (l); i <= (r); ++i)
#define int ll
const int N = 2000 + 5, P = 1e9 + 7;
int n, m, ans = 1;
int a[N], pw[N], jc[N];
int qpow(int a, int b)
{
    int res = 1, base = a;
    while (b)
    {
        if (b & 1) res = res * base % P;
        base = base * base % P;
        b >>= 1;
    }
    return res;
}
signed main()
{
    cin >> n >> m;
    pw[0] = jc[0] = 1;
    R(i, 1, n) pw[i] = pw[i - 1] * 2 % P, jc[i] = jc[i - 1] * i % P;
    // 将每个段看成同一种类型 方案即为可重集排列数
    // 再单独看每一个段的方案数 只需要看中间段，每次有两种选择
    R(i, 1, m) cin >> a[i];
    sort(a + 1, a + m + 1);
    int t = n - m;
    R(i, 1, t) (ans *= i) %= P;
    ans *= qpow(jc[a[1] - 1], P - 2); ans %= P;
    ans *= qpow(jc[n - a[m]], P - 2); ans %= P;
    R(i, 2, m)
    {
        int len = a[i] - a[i - 1] - 1;
        if (len) (ans *= pw[len - 1]) %= P;
        (ans *= qpow(jc[len], P - 2)) %= P;
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：xqh07 (赞：2)

考虑容斥，从总方案数中除去不合法方案数。

## 预处理：

设点亮的灯数组为 $a_i$，且 $a_0=1$，$a_{m+1}=n+1$。

记 $b_i=a_i-a_{i-1}-1$，$ans_i$ 表示第 $a_{i-1}+1$ 到第 $a_{i}-1$ 号灯的点亮方案数（不同区间方案数相互独立）。

不难发现，$ans_1= ans_{m+1}=1$，$\forall i\in \left [ 2 ,m\right ]$，$ans_i=2^{b_{i}-1}$（除了最后一盏灯点亮方案唯一，每次点灯都可以从左或右点）。

## 计数：

忽略一切约束条件，总方案数为 $(n-m)!$。

然而，对于每个 $b_{i}!$ 种排列，都只有 $ans_{i}$ 种是合法的。

因此，$res=(n-m)! \times \prod_{i=1}^{m} \frac{ans_i}{b_i!}$。

## Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 1e9 + 7;
int n, m, res, a[1005], b[1005], f[1005], g[1005];	
int qpow(int x, int y)
{
	int res = 1;
	while(y)
	{
		if(y & 1) res = res * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return res;
}
signed main()
{
	scanf("%lld%lld", &n, &m);
	for(int i = 1; i <= m; i++)
		scanf("%lld", &a[i]);
	sort(a + 1, a + m + 1);
	for(int i = 1; i <= m; i++)
		b[i] = a[i] - a[i - 1] - 1;
	b[m + 1] = n - a[m];
	if(m == n)
	{
		printf("1\n");
		return 0;
	}
	f[0] = g[0] = 1;
	for(int i = 1; i <= n; i++) f[i] = f[i - 1] * i % mod; 
	for(int i = 1; i <= n; i++) g[i] = g[i - 1] * 2 % mod;
	res = f[n - m] * qpow(f[b[1]], mod - 2) % mod * qpow(f[b[m + 1]], mod - 2) % mod;
	for(int i = 2; i <= m; i++)
		if(b[i])
			res = res * qpow(f[b[i]], mod - 2) % mod * g[b[i] - 1] % mod;
	
	printf("%lld\n", res);
	return 0;
}

```


---

## 作者：lx_zjk (赞：1)

这道题 组合数学好题

首先对于区间$[a[i], a[i + 1]]$和$[1, a[1]], [a[m], n]$ 我们分开讨论

对于每个区间顺序只有$2^d$个$d = a[i] - a[i-1] - 2$ 可以画图考虑 如果只选当前区间 要么 选左端点要么选右端点 不断缩短区间长度 直到区间长度为1时只能选他

然后前导和后缀 因为选择他们的顺序是固定的 选了 $i$ 才能选 $i - 1$ 所以他们对答案的贡献只有$c[num][a[1] - 1]$ $num$表示剩下的数

核心代码

```cpp
	ll num = n - m, ans = 1;
	for (int i = 2; i <= m; i ++ ) {
		int d = a[i] - a[i - 1] - 1;
		if (d)
			ans = ans * c[num][d] % mod * qpow (2, d - 1) % mod;
		else 
			ans = ans * c[num][d] % mod;
		num -= d;
	}
	ans = ans * c[num][a[1] - 1] % mod;
	num -= a[1] - 1;
	ans = ans * c[num][n - a[m]] % mod;
```

---

## 作者：Erica_N_Contina (赞：1)

## 思路

首先我们可以把这 $n$ 盏灯拆分开来。我们以已经点亮了的灯为分界线，那么我们就可以把所有没有点亮的灯划分为若干个不相邻的区间，每个区间中都是没有被点亮的灯。

那么我们现在来考虑一个区间的情况：

### 单区间

下面我们用 $a_i$ 来表示每个灯的情况，$1$ 表示点亮了。

对于区间 $[l,r]$，我们知道 $a_l\sim a_r=0,a_{l-1}=a_{r+1}=1$，那么我们就只有两种点亮灯的方式：在左边扩展，或者在右边扩展。我们可以交替进行上面的两种操作，现在的问题是我们应该怎么样计算出使用上面两种操作填满这个区间的方案数。

我们把在左边扩展记为 `L`，在右边扩展记为 `R` 那么现在的问题就转化为了求**用字符 `L`，`R`** **填满长度为 $r-l+1$** **的字符串的方案数量**。那么每个位置我们有两种情况，所以方案数量就是 $2^{r-l+1}$。但是我们注意到，在原题（即点亮灯的问题）中当我们点亮了 $r-l$ 个灯后，最后一个没有点亮的灯的左右都是已经点亮的灯。此时无论我们选择在左边扩展，或者在右边扩展，都是点亮该盏灯，所以这其实是一种情况。所以方案数量应该为 $2^{r-l}$，即**用字符 `L`，`R`** **填满长度为 $r-l$** **的字符串的方案数量**

### 区间交错

为了方便，我们先只考虑两边都有点亮了的灯的区间，即不考虑两端的区间。

回到本题。本题是由多个上述区间组成的，每次操作我们都可以选择任意一个区间进行操作。那么我们怎么样来处理这个问题呢？

是不是不好想？

其实非常简单啦：

**思路 1**

我们把区间用 $1\sim k$ 编号，那么每个区间的操作就变成了 `iL` 和 `iR`，其中 $i$ 是区间编号。例如第 $3$ 个区间的操作就是 `3L`，`3R`。那么我们的方案数就是用 $1L,1R,\sim,kL,kR$ 这些字符填满长度为 $\sum\limits_{i=1}^k r_i-l_i $ 的字符串的情况数。特别地，对于每个 $i$，`iL`，`iR` 的个数和是固定的。

所以我们可以从前往后枚举每个区间，然后对于这个区间 $i$，我们枚举 `iL` 的个数（我们记为 $c_{iL}$ 好了），那么填 `iL` 的方案数就是 $C_{(\sum r_i-l_i)-cnt}^{c_{iL}}$，其中 $cnt$ 是以前已经填了的字符的个数。浅浅说一下，填 `iR` 的方案和填 `iR` 的方案是组合的，所以我们需要把他们相乘。枚举 `iL` 的个数时的方案是并列的，我们需要把他们相加。

**思路 2**

我们先不考虑 `L`，`R`，我们只保留 $i$，那么我们现在就是要用 $r_i-l_i$ 个 $i,i\in[1,k]$ 填满长度为 $\sum\limits_{i=1}^k r_i-l_i+1$ 的字符串的情况数（注意这里不是 $\sum\limits_{i=1}^k r_i-l_i$ 了！），就是 $\frac{(\sum\limits_{i=1}^k r_i-l_i+1)!}{\prod_{i=1}^{k}{(r_i-l_i+1)!}}$。把 `L`，`R` 加上，那么就是再乘上 $\prod_{i=1}^{k}2^{r_i-l_i}$（注意这里就是 $r_i-l_i$ 了）。

## 代码

```C++
/*
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define mp make_pair
#define pii pair<int,int>

///----///
#define rd read()
inline int read() {
    int xx = 0, ff = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            ff = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') xx = xx * 10 + (ch - '0'), ch = getchar();
    return xx * ff;
}
inline void write(int out) {
    if (out < 0)
        putchar('-'), out = -out;
    if (out > 9)
        write(out / 10);
    putchar(out % 10 + '0');
}

///----///
const int N = 1e3 + 5;
const int M = 1e7 + 5;
const int MOD = 1e9 + 7;
const double eps=1e-7;

int n, m, ans=1;
int pos[N],inv[N],fac[N],pow2[N]; 

void init(){
	inv[1] = 1;
    for(int i = 2; i <= n; ++i)inv[i] = ((MOD-MOD/i)*inv[MOD%i])%MOD;
    fac[1] = 1;
    for(int i = 2; i <= n; ++i) fac[i] = (fac[i-1]*inv[i])%MOD;
    pow2[0] = 1;
    for(int i = 1; i <= n; ++i) pow2[i] = (pow2[i-1]<<1)%MOD;
}

signed main() {
    n=rd;m=rd;
	init();
    for(int i = 1; i <= m; ++i)pos[i]=rd;
    sort(pos+1, pos+m+1);

    pos[m+1] = n+1;
    for(int i = 0; i <= m; ++i) {
        int l = pos[i+1]-pos[i]-1;
        if(l <= 0) continue;
        if(i > 0 && i < m) ans = (ans*pow2[l-1])%MOD;//中间区间的放法
        ans = (ans*fac[l])%MOD;
    }
	for(int i = 2; i <= n-m; ++i) ans = (ans*i)%MOD;//L,R的方案
	cout<<ans<<endl;
    return 0;
}
```




---

## 作者：nanatsuhi (赞：1)

恶评题。 个人的评分是绿。

由于其他的题解我没看懂~~还不是因为你理解力太差~~，所以写了一篇自认为相当好理解的题解。

首先，我们将题目所描述的灯泡问题抽象如下：

> 在有$n$个元素的01序列中，$m$个元素的值为$1$，每次操作可以将一个与值为$1$的元素相邻的值为$0$的元素赋值为$1$，求将所有元素变为$1$的有序方案数。

首先忽略题目的数据范围，将它当作一道简单的数学题去看待。（顺带一提，这样的简单排列组合在小学聪明题中相当常见）

其实就是一些$1$把一堆$0$分成了很多块，然后叫你算一点东西。~~不负责任的态度~~

那么，可以将这道题分成两个部分来考虑：

1. 某块在操作序列中的位置

一块一块算。

第一块的情况：在总长度为$n-m$的操作序列中，选出当前块所含元素数量（设为$l_1$）的位置，并把当前块所含元素按一定的顺序放入操作序列。

这是一个非常简单的组合问题，与“从$n-m$个小球里面挑出$l_1$个”是完全一样的。答案是$A_1=C^{l_1}_{n-m}$。

其实接下来的块也差不多。只是操作序列的所剩下的位置越来越少，因为有很多位置已经被之前的块占据了。第$i$块的方案数应该如下：

$A_i=C^{l_i}_{n-m-\sum^{i-1}_{j=1} l_j}$~~太臃肿了~~

根据乘法原理，方案数等于$\prod A_i$。

还有一种算法在其他的题解里已经讲得比较清楚。

2. 单块内部的操作顺序

单块其实有两种：一种是两端各有一个$1$的，还有一种是只有一端有$1$，另一端是由于到了序列的头尾而被迫结束的。

对于前者，可以这样考虑：

每一次操作，本质上就是将块的两端的$0$变成$1$。所以，这可以理解成一个选择问题：每次可以选择在块的左端或者是右端把$0$变成$1$。特殊地，当只剩下最后一块时，左端和右端是一样的。

所以，对于第$i$块，答案是$2^{l_{i}-1}$。

综合来看，总的结果是$\prod A_i\cdot 2^{l_{i}-1}$。

---

但这道题目的难度完全不在上面的数学内容上！而是在：

1. 组合数取模

2. 代码细节

组合数由于带有除法，不能直接取模，但是可以利用乘法逆元（类似于取倒数）达到化乘为除的效果。

所以这道题目的难度应该与乘法逆元相当。

至于少量的细节，可以参考代码。（但还是推荐自己调试）

Code:
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 1e9 + 7, maxn = 1e3 + 5;
int n, m, ans, num;
int frat[maxn], fratinv[maxn], pow2[maxn], temp;
vector<int> l;
void exgcd(int a, int b, int &x, int &y)
{
    if (!b)
        x = 1, y = 0;
    else
        exgcd(b, a % b, y, x), y -= a / b * x;
}
void init()
{
    frat[0] = 1, pow2[0] = 1;
    for (int i = 1; i < maxn; ++i)
        frat[i] = frat[i - 1] * i % mod;
    for (int i = 0; i < maxn; ++i)
        exgcd(frat[i], mod, fratinv[i], temp), fratinv[i] = (fratinv[i] % mod + mod) % mod;
        //这里使用的是O(nlogn)的求阶乘逆元，实际上可以很轻松的O(n)解决。
    for (int i = 1; i < maxn; ++i)
        pow2[i] = pow2[i - 1] * 2 % mod;
}
int C(int n, int m) { return ((frat[n] * fratinv[m] % mod + mod) % mod * fratinv[n - m] % mod + mod) % mod; }
signed main()
{
    init();
    scanf("%lld%lld", &n, &m);
    for (int i = 1, x; i <= m; ++i)
    {
        scanf("%lld", &x);
        l.push_back(x);
    }
    sort(l.begin(), l.end());
    num = n - m;
    ans = C(num, l[0] - 1), num -= l[0] - 1;
    for (int i = 1, len; i < m; ++i)
    {
        len = l[i] - l[i - 1] - 1;
        ans = (ans * C(num, len) % mod + mod) % mod, num -= len;
        if (len)
            ans = (ans * pow2[len - 1] % mod + mod) % mod;
    }
    printf("%lld", ans);
    return 0;
}
```

---

## 作者：枫林晚 (赞：0)

### 题目大意：
有n盏灯，(0<=n<=1000),有m盏已经点亮，每次只能点亮与已经点亮的灯相邻的灯，求总方案数，答案对1e9+7取模

第一行：两个整数n,m表示灯的总数和已点亮的灯的数目 第二行m个数，表示已点亮的灯的编号

### 分析：

我们可以借助已经被点亮的灯作为分界点，找到若干个长度不为0的开区间。

对于两边都有开着的灯的区间，我们点亮它每次可以点亮最左边一盏或者最右边一盏，而最后一盏灯只有一种方法，所以点亮长度为len的区间的方案数为：2^(len-1)

特别地，对于两端的区间（一边有灯开着，一边是边界（1或者n）），只有一种方案数（顺着一路点下去）

根据乘法原理，可以先计算出ans*=2^(len2-1)2^(len-2-1)...2^(len(cnt-1)-1)注意开始的时候是i=2，最后一段是i=cnt-1；（最初最末两端算上是没有意义的）

但是由于点灯的时候可以交叉在每个区间内点灯，所以这样的ans还是少了很多。

所以我们重新这样考虑：
考虑将每个区间内考虑成颜色相同的len个球，不同区间球的颜色不同。每一个排列可以当做是一个指令，不同的合法的指令是不同的方案数。

容易知道最初的方案数为：（n-m）！我们将它处理成多重集合的排列，(n-m)!/len1!len2!...lencnt!。这样保证了每个区间内的同一种颜色的球的“单纯相对顺序”（只是这些球之间交换顺序）变化都算作是一种方案。

但是一个区间内，并不是一种方案，对于len的球数，可以有2^(len-1)种合法排列，利用乘法原理再将它们相乘，就可以得出正确的答案。

(需要：快速幂，乘方的乘法逆元）
附代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define int long long
using namespace std;
const int mod=1e9+7;
const int N=1005;
int n,m;
int len[N];//区间长度;
ll fac[N];//阶乘;
ll ifac[N];//阶乘逆元;
ll qm(int x,int y)
{
	ll base=x;
	ll ans=1;
	while(y)
	{
		if(y&1) ans=(ans*base)%mod;
		base=(base*base)%mod;
		y>>=1;
	}
	return ans%mod;
}//快速幂 
int cnt;
ll anss=1;
int h[N];
signed main()
{
	scanf("%lld%lld",&n,&m);
	int last=0;
	int x;
	for(int i=1;i<=m;i++)
	{scanf("%lld",&h[i]);}
	sort(h+1,h+m+1);//注意，编号可能不是单调的。 
	len[++cnt]=h[1]-last-1;
	for(int i=2;i<=m;i++)
	{
		if(h[i]-h[i-1]>1) len[++cnt]=h[i]-h[i-1]-1;
	}
	len[++cnt]=n-h[m];
	for(int i=2;i<=cnt-1;i++)
	 anss=(anss*qm(2,len[i]-1))%mod;//先处理2^len 
	fac[0]=1;
	ifac[0]=1;
	for(int i=1;i<=n-m;i++)
	 fac[i]=(fac[i-1]*i)%mod;//阶乘 
	ifac[n-m]=qm(fac[n-m],mod-2)%mod;//费马小定理先算n-m 
	for(int i=n-m-1;i>=1;i--)
	 ifac[i]=(ifac[i+1]*(i+1))%mod;//递推算阶乘逆元 
	anss=(anss*fac[n-m])%mod;
	for(int i=1;i<=cnt;i++)
	 anss=(anss*ifac[len[i]])%mod;//多重集合排列处理 
	printf("%lld",anss%mod);
	return 0;
}
```

还有一种组合数学的思想，

就是利用乘法原理，每次乘上：在每次剩余的位置放上len个数的方案数。

友链：
https://blog.csdn.net/qq_38538733/article/details/76409237




---

