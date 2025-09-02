# [ABC307E] Distinct Adjacent

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc307/tasks/abc307_e

$ 1 $ から $ N $ の番号がついた $ N $ 人の人が輪になってならんでいます。人 $ 1 $ の右隣には人 $ 2 $ が、人 $ 2 $ の右隣には人 $ 3 $ が、……、人 $ N $ の右隣には人 $ 1 $ がいます。

$ N $ 人の人にそれぞれ $ 0 $ 以上 $ M $ 未満の整数を $ 1 $ つずつ渡します。  
$ M^N $ 通りの渡し方のうち、どの隣り合う $ 2 $ 人が渡された数も異なるものの数を、$ 998244353 $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N,M\ \leq\ 10^6 $
- $ N,M $ は整数である

### Sample Explanation 1

人 $ 1,2,3 $ に渡す整数がそれぞれ $ (0,1,2),(0,2,1),(1,0,2),(1,2,0),(2,0,1),(2,1,0) $ のときの $ 6 $ 通りです。

### Sample Explanation 2

人 $ 1,2,3,4 $ に渡す整数がそれぞれ $ (0,1,0,1),(1,0,1,0) $ のときの $ 2 $ 通りです。

### Sample Explanation 3

$ 998244353 $ で割ったあまりを求めてください。

## 样例 #1

### 输入

```
3 3```

### 输出

```
6```

## 样例 #2

### 输入

```
4 2```

### 输出

```
2```

## 样例 #3

### 输入

```
987654 456789```

### 输出

```
778634319```

# 题解

## 作者：泥土笨笨 (赞：21)

题目中说所有的 $n$ 个字符串首尾相接形成一个环，对于环的问题比较复杂不好考虑，我们把问题简化成一个从 $1$ 到 $n$ 的链，要求链上相邻两个位置不能取相同的数字。定义一个二维的状态 $dp[i][0]$ 表示前 $i$ 个位置满足相邻位置数字不同，且第 $i$ 个位置和第一个位置用不同数字的方案数。$dp[i][1]$ 表示前 $i$ 个位置满足相邻位置数字不同，且第 $i$ 个位置和第一个位置用相同数字的方案数。当我们求出 $dp$ 数组的值以后，最终答案里面首尾不能用相同的数字，所以最终答案就在 $dp[n][0]$ 里面。

下一步考虑状态转移，首先考虑如何求 $dp[i][0]$，如果第 $i-1$ 位置用的跟开头不同，当前位置就既不能跟开头相同，也不能跟 $i-1$ 位置相同，所以只有 $m-2$ 种可选数字。如果第 $i-1$ 位置用的跟开头相同，那么当前位置只要从 $m-1$ 种跟开头不同的数字当中选一个就行了。所以有：

$$dp[i][0] = dp[i - 1][0] \times (m - 2) + dp[i - 1][1] \times (m - 1)$$

同理，对于 $dp[i][1]$，因为已经确定了当前位置要填的数字，所有 $i-1$ 位置跟开头不同的数字都可以转移过来，所以：

$$dp[i][1] = dp[i - 1][0]$$

总的复杂度 $O(n)$，可以通过本题。

代码：

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;
typedef long long ll;
const ll MAXN = 1e6 + 5;
const ll MOD = 998244353;

//dp[i][0]表示前i个位置满足相邻位置数字不同，且第i个位置和第一个位置用不同数字的方案数
//dp[i][1]表示前i个位置满足相邻位置数字不同，且第i个位置和第一个位置用相同数字的方案数
ll n, m, dp[MAXN][2];

int main() {
    cin >> n >> m;
    dp[1][1] = m;
    for (ll i = 2; i <= n; ++i) {
        dp[i][0] = (dp[i - 1][0] * (m - 2) % MOD + dp[i - 1][1] * (m - 1) % MOD) % MOD;
        dp[i][1] = dp[i - 1][0];
    }
    cout << dp[n][0] << endl;
    return 0;
}
```


---

## 作者：FLY_lai (赞：9)

### 题意

$n$ 个人站成一圈，有 $m$ 种颜色，给每个人涂一种颜色，且相邻的人不同色。求涂色方案数，答案对 $998244353$ 取模。

这么简洁的题面，一般来说要么 DP 要么数学。巧的是，这题两者皆可。

## DP 解法

先看在序列上怎么做。

定义 $dp[i][c]$ 为前 $i$ 个人站成一列，相邻两个人颜色不同，且第 $i$ 个人颜色为 $c$ 的方案数。

在环上，我们只需要多考虑一步第 $n$ 个人和第 $1$ 个人的颜色是否相同。所以我们可以枚举第一个人的颜色，跑一遍序列 dp，然后把第 $n$ 个人和第 $1$ 个人的颜色相等的情况去掉，再求和。

即 $\displaystyle \sum_{clr1=1}^{m} \sum_{clrn\ne clr1} dp[n][clrn]$。

但是这样的空间复杂度是 $O(nm)$ 的，显然会爆掉。

考虑优化状态。发现我们并不关心最后一个人是什么色，我们只关心他和第一个人的颜色是否相同。而这样定义，等我们跑完 dp，最终的答案也不用循环来求了。

改定义 $dp[i][0]$ 为前 $i$ 个人站成一圈，且第 $i$ 人的颜色与第一人不相同的方案数；$dp[i][1]$ 为前 $i$ 个人站成一圈，且第 $i$ 人的颜色与第一人相同的方案数。

转移方程也很简单：

$dp[i][0]=(m-2)dp[i-1][0]+(m-1)dp[i-1][1]$.

$dp[i][1]=dp[i-1][0]$.

答案是 $dp[n][0]$。

```
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int MOD = 998244353;

ll n, m;
ll dp[2][1000010];

int main() {
	cin >> n >> m;
	dp[1][1] = m;
	for (int i = 2; i <= n; i++) {
		dp[0][i] = ((m - 2) * dp[0][i - 1] % MOD + (m - 1) * dp[1][i - 1] % MOD) % MOD;
		dp[1][i] = dp[0][i - 1] % MOD;
	}
	cout << dp[0][n];
	return 0;
}
```

## 数学解法

这其实是一个很经典的环形染色的数学题。

我们先考虑直线染色。

$n$ 个人排成一列，有 $m$ 种颜色的方案数很好算。第一个人有 $m$ 种颜色可以选，之后 $n-1$ 人每一个人的颜色都要与左边的人不同。因此总方案数为 $m(m-1)^{n-1}$。

再推广到环形染色。

记 $i$ 人排成环，涂 $m$ 种颜色的方案数为 $a_i$。

对于 $n$ 个人直线染色的方案数，我们尝试将其对应到环上。

如果第 $1$ 个人和第 $n$ 个人的颜色不一样，那把这种直线染法头尾相接，形成一个环，得出一种 $n$ 个人的环形染色法。

如果第 $1$ 个人和第 $n$ 个人的颜色相同，头尾相接后，可以把第 $1$ 个人和第 $n$ 个合并起来，得出一种 $n-1$ 个人的环形染色法。

因此 $a_{n-1}+a_n=m(m-1)^{n-1}$。其实到这里已经可以递推了，但我们还可以更进一步。

$a_{n-1}+a_n=m(m-1)^{n-1}=(m-1)(m-1)^{n-1}+(m-1)^{n-1}=(m-1)^n+(m-1)^{n-1}$.

移项得：$a_n-(m-1)^n=-(a_{m-1}-(n-1)^{m-1})$。

1. $a_n=(m-1)^n$，而 $a_2=m(m-1)$，与之矛盾，舍；

2. 否则令 $b_n=a_n-(m-1)^n$，则 $\frac{b_n}{b_{n-1}}=-1$，为等比数列。

	则 $b_n=(-1)^{n-2}\cdot b_2=(-1)^n\cdot b_2$，代入 $b_n=a_n-(m-1)^n$。
    
    得：$a_n=(m-1)^n+(-1)^n\cdot(m-1)$。
    
那我们只需要用一个简单的快速幂就可以了。

```
#include <bits/stdc++.h>

using namespace std;
const int MOD = 998244353;

long long n, m;

long long fpow(long long a, long long b) {
	long long mul = 1;
	while (b) {
		if (b & 1)
			mul = mul * a % MOD;
		a = a * a % MOD;
		b /= 2;
	}
	return mul;
}

int main() {
	cin >> n >> m;
	cout << (fpow(m - 1, n) % MOD + ((n % 2 == 1 ? -1 : 1) * (m - 1) + MOD) % MOD) % MOD << endl;
	return 0;
}
```
    
    
    
    

---

## 作者：wizardMarshall (赞：4)

提供一种数学解法。

## 题意

给定一个长度为 $n$ 的环，每个位置可以填 $1\sim m$，求有多少种方案，满足相邻位置颜色不相同。

## 思路

- $O(n^3)$：

暴力很容易想到怎么做，用数组记录，$cnt_i$ 表示当前这一位数字为 $i$ 的方案数。假设刚开始颜色为 $1$。（这样假设，最终方案数还要乘 $m$，因为我们只是计算了其中一种方案数）

为了方便，使用滚动数组。$cnt$ 为当前需要计算的，$temp$ 为上一次的结果。当前 $cnt_i$ 自然就是加上之前的所有 **颜色不等于 $i$ 的方案**。得出：

$$cnt_i \gets \displaystyle\sum^{m}_{j=1}[j\ne i] temp_j$$

循环 $n-1$ 次后，最终答案就是：

$$m\times \displaystyle\sum^{m}_{i=1}[i\ne 1] cnt_i$$

或

$$(m\times \displaystyle\sum^{m}_{i=1} cnt_i) - cnt_1$$

----

- $O(n^2)$：

还可以进一步优化。可以先预处理 $\sum temp$，当计算 $cnt_i$ 时直接用总和减去 $temp_i$。

----

- $O(n)$：

做到这步，似乎“山穷水复疑无路”了？

别忘了，最终我们计算的是 $cnt$ 的总和，减去 $cnt_1$。能不能在之前的循环中直接维护总和呢？

我们看循环中总和的式子：

$$\displaystyle\sum^{m}_{i=1} \Big[ (\displaystyle\sum^{m}_{j=1} cnt_j) - cnt_i \Big]$$

将其拆开，得到

$$(m \times \displaystyle\sum^{m}_{i=1} cnt_i) - \displaystyle\sum^{m}_{i=1} cnt_i$$

进一步化简：

$$(m - 1) \times \displaystyle\sum^{m}_{i=1} cnt_i$$

所以，每次我们只要乘以 $m-1$，即可推出总和。

-----


但问题又来了：总和是维护好了，但最终答案还要减去 $cnt_1$ 啊，这个似乎并没有维护。

我们可以通过数列来找找规律：

```
n=1:1 0 0 
n=2:0 1 1
n=3:2 1 1
n=4:2 3 3
```

观察发现，当 $n$ 为奇数时，$cnt_1$ 比其他 $cnt_i(i \ne 1)$ 多 $1$，偶数则比其他 $cnt_i(i \ne 1)$ 少 $1$。既然有了总和，我们通过 $n$ 的奇偶性来分类讨论。

$n$ 为奇数时：

$cnt_1\gets\lfloor\dfrac{(\sum cnt)-1}{m}\rfloor$

$n$ 为偶数时：

$cnt_1\gets\lfloor\dfrac{(\sum cnt)+1}{m}\rfloor$

由此可得 $cnt_1$。

-----

有一个需要注意的点是：本题中答案很大，算数过程中要取模。使用乘法逆元，这里具体不再叙述。没有接触过乘法逆元的同学可以加以学习。

------

## 代码


```
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int inf = 998244353;
int poww(int a, int b, int c) {//快速幂
    int ans = 1;
    while (b) {
        if (b % 2) {
			ans = ans * a;
			ans %= c;
        }a *= a;
        a %= c;
        b /= 2;
    }return ans;
}
int ex(int b, int c) {//计算逆元
	return poww(b, c - 2, c);
}
signed main() {
	int n, m;
	cin >> n >> m;
	int ans = 1;
	for (int i = 2; i <= n; i++) {
		ans *= (m - 1);
		ans %= inf;
	}
	if (n % 2) {//根据n的奇偶性分类讨论
		int v = (ans - 1 + inf) % inf;
		v *= ex(m, inf);
		v %= inf;
		ans = ((((v * (m - 1) % inf)) % inf) + inf) % inf;
	}else {
		int v = (ans + 1 + inf) % inf;
		v *= ex(m, inf);
		v %= inf;
		ans = ((((v * (m - 1) % inf)) % inf) + inf) % inf;
	}
	cout << (ans * m) % inf;//由于一开始是用1作为初始答案的，这里要乘以m
    return 0;
}

```

## 闲话

本做法是笔者比赛时使用的做法，不保证最简，仅供参考，不得抄袭。

祝各位 OIer 切题愉快！

---

## 作者：xht (赞：3)

$n$ 较小时单独处理，$n$ 较大时递推，设 $f_n$ 为答案。

讨论第一个数与第 $n-2$ 个数的关系，若相同则方案数为 $(m-1)f_{n-2}$，若不同则方案数为 $(m-2)f_{n-1}$。

```cpp
int main() {
    int n, m;
    cin >> n >> m;
    if (n == 2) {
        cout << 1ll * m * (m - 1) % P << endl;
        return 0;
    }
    if (n == 3) {
        cout << 1ll * m * (m - 1) % P * (m - 2) % P << endl;
        return 0;
    }
    vector<modint> f(n + 1);
    f[2] = 1ll * m * (m - 1) % P, f[3] = 1ll * m * (m - 1) % P * (m - 2) % P;
    for (int i = 4; i <= n; i++) f[i] = f[i-2] * (m - 1) + f[i-1] * (m - 2);
    cout << f[n].x << endl;
	return 0;
}
```

---

## 作者：_sunkuangzheng_ (赞：3)

**【问题分析】**

考虑 dp。

设 $f_{n,0/1}$ 表示 $a_1 = a_n$ 和 $a_1 \ne a_n$ 的方法数，很容易得到以下的方程式：

$$f_{n,0} = f_{n-1,1}$$

$$f_{n,1} = (m-2)f_{n-1,1} + (m-1)f_{n-1,0}$$

进一步发现，我们可以省略掉 $f_{n,0}$，直接将方程写作：

$$f_{n} = (m-2)f_{n-1} + (m-1)f_{n-2}$$

这个式子可以用矩阵快速幂优化到 $\Theta(\log n)$，但对于本题 $1 \le n,m \le 10^6$ 的数据范围来说，直接采用 $\Theta(n)$ 的递推算法即可。

**【代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;
int n,m,f[2000005];
signed main(){
    cin >> n >> m;
    f[1] = m,f[2] = m*(m-1) % mod,f[3] = (m*(m-1) % mod * (m-2) % mod);
    for(int i = 4;i <= n;i ++){
    	f[i] = ((m-2) * f[i-1] + (m-1) * f[i-2]) % mod;
	}
	cout << f[n];
	return 0;
}


```



---

## 作者：吴思诚 (赞：2)

# [[ABC307E] Distinct Adjacent 题解](https://www.luogu.com.cn/problem/AT_abc307_e)

我们将圆环上有 $i$ 个人的情况的答案记为 $f(i)$。考虑有 $i+1$ 个人排成一排的情况，此时答案为 $M \times (M-1)^i$。这样的传递方式中，如果是圆环的情况且不满足条件的传递方式只有人 $i+1$ 和人 $1$ 的情况不同。因此，这两个人可以视为同一人，这样的传递方式有 $f(i)$ 种。因此，我们有 $f(i+1)=M \times (M-1)^i-f(i)$。这样就解决了这个问题。

# [代码](https://atcoder.jp/contests/abc307/submissions/43021775)



---

## 作者：incra (赞：2)

### [原题链接](https://www.luogu.com.cn/problem/AT_abc307_e)
### 题解
不难求得在不考虑 $1$ 号人和 $n$ 号人数字不同的情况下，一共有 $m\times (m-1)^{n-1}$ 种合法状态，答案为 $m\times (m-1)^{n-1}$ 减去 $1$ 号人和 $n$ 号人数字相同的情况下的合法状态数。

接下来考虑 $1$ 号人和 $n$ 号人数字相同时的合法状态数量。

令 $f_{i,0/1}$ 表示考虑从 $1$ 号人到 $i$ 号人时，$0/1$ 分别表示 $i$ 号人和 $1$ 号人的数字相同或不相同时，一共的合法状态数。

考虑状态转移方程。

对于每一个 $f_{i,0}$，它只能由 $f_{i-1,1}$ 递推而来，而 $f_{i,0}$ 表示当前的 $i$ 号人与 $1$ 号人数字相同，所以 $f_{i,0}=f_{i-1,1}$。

对于每一个 $f_{i,1}$，它有两种转移方式：

1. 由 $f_{i-1,0}$ 转移而来，此时 $i$ 号人有 $m-1$ 种选法，即 $f_{i,1}=f_{i-1,0}\times(m-1)$
2. 由 $f_{i-1,1}$ 转移而来，此时 $i$ 号人不能与 $i-1$ 号人和 $1$ 号人相同，所以方案数为 $f_{i,1}=f_{i-1,1}\times (m-2)$。

综上，可以得到 $\begin{cases}f_{i,0}=f_{i-1,1}\\f_{i,1}=f_{i-1,0}\times (m-1)+f_{i-1,1}\times (m-2)\end{cases}$ 。

同时可以知道，$1$ 号人和 $n$ 号人数字相同的合法状态数就是 $f_{n,0}$。

总结一下做法：

1. 求出不考虑 $1$ 号人和 $n$ 号人数字不同时的合法状态数，这一步可以用快速幂算。
2. 将上一个数减去 $1$ 号人和 $n$ 号人数字相同时的合法状态数，从而得到答案。

蒟蒻的做法，大佬不喜勿喷。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
using namespace std;
typedef pair <int,int> PII;
typedef long long LL;
const int N = 1000010,MOD = 998244353;
int n,m;
LL power (LL a,LL b,LL p) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
LL f[N][2];
int main () {
	cin >> n >> m;
	f[1][0] = 1;
	for (int i = 2;i <= n;i++) {
		f[i][0] = f[i - 1][1] % MOD;
		f[i][1] = (f[i - 1][0] * (m - 1) % MOD + f[i - 1][1] * (m - 2)) % MOD;
	}
	cout << (m * power (m - 1,n - 1,MOD) % MOD - m * f[n][0] % MOD + MOD) % MOD << endl;
	return 0;
}
```

---

## 作者：Arghariza (赞：1)

题意：$n$ 个不同的人排成一圈，顺序编号 $1,2,\cdots,n$，每个人有一种颜色，共 $m$ 种颜色，相邻两个人颜色不能相同，求方案数。

设 $f_i$ 表示 $i$ 个不同的人排成一圈染色的方案数。

不管 $1,n$ 的颜色是否相同，把他们从中间切开，变成 $1\to 2\to \cdots\to n$ 的链，给这条链染色，相邻两个异色的方案数显然是 $m\cdot(m-1)^{i-1}$。

但是 $1$ 和 $n$ 的颜色有可能相同，于是需要减去这样的情况。发现在上面方案中，$1,2$ 的颜色不同，$1,n$ 的颜色相同，$n-1,n$ 的颜色不同，于是把 $1,n$ 当作同一个人，方案数为 $f_{i-1}$。

所以：

$$f_i=m\cdot (m-1)^{i-1}-f_{i-1}$$

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

namespace vbzIO {
	char ibuf[(1 << 20) + 1], *iS, *iT;
	#if ONLINE_JUDGE
	#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
	#else
	#define gh() getchar()
	#endif
	#define mt make_tuple
	#define mp make_pair
	#define fi first
	#define se second
	#define pc putchar
	#define pb push_back
	#define ins insert
	#define era erase
	#define bg begin
	#define rbg rbegin
	typedef tuple<int, int, int> tu3;
	typedef pair<int, int> pi;
	inline int rd() {
		char ch = gh();
		int x = 0;
		bool t = 0;
		while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
		return t ? ~(x - 1) : x;
	}
	inline void wr(int x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			wr(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace vbzIO;

const int N = 1e6 + 100;
const int mod = 998244353;
int n, m, f[N];

int qpow(int p, int q) {
	int res = 1;
	while (q) {
		if (q & 1) res = res * p % mod;
		p = p * p % mod, q >>= 1;
	}
	return res;
}

signed main() {
	n = rd(), m = rd();
	f[2] = m * (m - 1) % mod;
	if (n == 2) wr(f[n]);
	else {
		for (int i = 3; i <= n; i++) 
			f[i] = (qpow(m - 1, i - 1) * m % mod - f[i - 1] + mod) % mod;
		wr(f[n]);
	}
	return 0;
}
```

其实还有更进一步的结论：

$$\begin{aligned}f_i&=-f_{i-1}+m(m-1)^{i-1}\\\frac{f_i}{(-1)^i}&=\frac{f_{i-1}}{(-1)^{i-1}}-m(1-m)^{i-1}\end{aligned}$$

令 $g_i=\dfrac{f_i}{(-1)^i}$：

$$\begin{aligned}g_i&=g_{i-1}-m(1-m)^{i-1}\\&=g_{i-2}-m(1-m)^{i-2}-m(1-m)^{i-1}\\&=\cdots\\&=-m(1-m)-m(1-m)^2-\cdots-m(1-m)^{i-1}\\&=-m(1-m)\left(1+(1-m)^2+(1-m)^3+\cdots+(1-m)^{i-2}\right)\\&=-m(1-m)\cdot \frac{1-(1-m)^{i-1}}{m}\\&=(m-1)+(1-m)^i\end{aligned}$$

所以：

$$\begin{aligned}f_{i}&=(-1)^ig_i\\&=(-1)^i(m-1)+(m-1)^i\end{aligned}$$

---

