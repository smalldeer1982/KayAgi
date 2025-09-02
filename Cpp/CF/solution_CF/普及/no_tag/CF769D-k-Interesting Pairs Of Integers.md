# k-Interesting Pairs Of Integers

## 题目描述

Vasya has the sequence consisting of $ n $ integers. Vasya consider the pair of integers $ x $ and $ y $ k-interesting, if their binary representation differs from each other exactly in $ k $ bits. For example, if $ k=2 $ , the pair of integers $ x=5 $ and $ y=3 $ is k-interesting, because their binary representation $ x $ =101 and $ y $ =011 differs exactly in two bits.

Vasya wants to know how many pairs of indexes ( $ i $ , $ j $ ) are in his sequence so that $ i&lt;j $ and the pair of integers $ a_{i} $ and $ a_{j} $ is k-interesting. Your task is to help Vasya and determine this number.

## 说明/提示

In the first test there are 4 k-interesting pairs:

- ( $ 1 $ , $ 3 $ ),
- ( $ 1 $ , $ 4 $ ),
- ( $ 2 $ , $ 3 $ ),
- ( $ 2 $ , $ 4 $ ).

In the second test $ k=0 $ . Consequently, integers in any k-interesting pair should be equal to themselves. Thus, for the second test there are 6 k-interesting pairs:

- ( $ 1 $ , $ 5 $ ),
- ( $ 1 $ , $ 6 $ ),
- ( $ 2 $ , $ 3 $ ),
- ( $ 2 $ , $ 4 $ ),
- ( $ 3 $ , $ 4 $ ),
- ( $ 5 $ , $ 6 $ ).

## 样例 #1

### 输入

```
4 1
0 3 2 1
```

### 输出

```
4
```

## 样例 #2

### 输入

```
6 0
200 100 100 100 200 200
```

### 输出

```
6
```

# 题解

## 作者：Lian_zy (赞：2)

# 0 题目传送门

[点我传送](https://www.luogu.com.cn/problem/CF769D)

# 1 题目分析
$n \le 10^5$，暴力肯定不行。

回顾一下我们学习的知识，如果 $x ⊕ y = z$，那么必然有 $y ⊕ z = x$ 和 $x ⊕ z = y$。

我们可以打出 $1 \to 2^{14}$
 中所有二进制数中 $1$ 的个数为 $k$ 的数的表，代码如下：
 
``` cpp
for (int i = 0; i <= 16384; i++) { //16384=2^14
	if (check(i) ^ k) continue; //x^y 等价于 x!=y
	ok[++cnt] = i;
}
```

其中 `check()` 函数为求二进制数中 $1$ 的个数的函数，复杂度为 $log(n)$。


维护每一个数出现的次数，使用 $a_1,a_2 \dots $ 储存。

根据 $x ⊕ y = z$ 时 $x ⊕ z = y$ 的原理可以写出如下代码：

``` cpp

for (int i = 1; i <= n; i++) {
	scanf("%lld", &x);
	for (int j = 1; j <= cnt; j++) ans += a[x ^ ok[j]]; //看有多少个 y 满足 x ^ y = ok[j]
	a[x]++; //出现次数 +1
}
```

# 2 代码时间

~~莫抄袭，没了 AC 记录，空悲切。~~

``` cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 1e5 + 10;
long long n, x, k, ans, cnt, a[maxn], ok[maxn];
int check(int x) {
	int cnt = 0;
	for (; x; cnt++) x -= x & -x;
	return cnt;
}
int main() {
	scanf("%lld %lld", &n, &k);
	for (int i = 0; i <= 16384; i++) {
		if (check(i) ^ k) continue;
		ok[++cnt] = i;
	}
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &x);
		for (int j = 1; j <= cnt; j++) ans += a[x ^ ok[j]];
		a[x]++;
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：DPair (赞：1)

## 【翻译】
$Vasya$ 有一个有$n$个整数的序列。

$Vasya$ 认为一对数$x,y$是$k-interesting$的, 当且仅当这两个数二进制下相同位上数字不同的位子数为$k$。例如, 如果 $k = 2$, 那么两个数 $x=5$ ，$y=3$ 是 $k-interesting$的, 因为它们的二进制$x=101$，$y =011$正好有两个字符位不同。

$Vasya$ 想知道她的序列中，有多少对数是$k-interesting$的。给你这个序列，问有多少对数是$k-interesting$的。

数据范围应该看得懂吧。。。
## 【思路】
由于我们要得到两个数二进制之后不同的位数，我们可以考虑异或处理$k-interesting$，如果$x$和$y$的异或结果的二进制中有$k$个$1$，这两个数就是$k-interesting$的。

于是，我们只要处理出数据范围内有多少个数的二进制有$k$个$1$，计算机打表就行。然后建立一个$count$数组，记录这个数目前出现过几次。

由于如果
$$a~xor~b = c$$
那么有
$$a~xor~c=b$$
和
$$b~xor~c=a$$

那么就好做了，对于每一个输入的数，与打出来含有$k$个$1$的数的表里的每一个数异或一下，然后在$ans$上累加这个数之前出现过几次，最后输出$ans$就$AC$了。

## 【注意】
由于数字比较大，$ans$要开$long~long$（血与泪的教训）。

由于异或结果可能比较大，$count$要开$2^{15}$左右。

## 【代码】
```cpp
#include <bits/stdc++.h>
using namespace std;
template <typename T>
inline void read(T &x)//快读
{
    char c;
    x = 0;
    int fu = 1;
    c = getchar();
    while(c > 57 || c < 48)
    {
        if(c == 45)
        {
            fu = -1;
        }
        c = getchar();
    }
    while(c <= 57 && c >= 48)
    {
        x = (x << 3) + (x << 1) + c - 48;
        c = getchar();
    }
    x *= fu;
}
template <typename T>
inline void fprint(T x)//快输（没什么用）
{
    if(x < 0)
    {
        putchar(45);
        x = -x;
    }
    if(x > 9)
    {
        fprint(x / 10);
    }
    putchar(x % 10 + 48);
}
int n, tot, k;
long long ans;
int num[1000010];
int ct[100010];
int main()
{
    read(n);
    read(k);
    for (register int i = 0;i <= (1 << 14);i ++)//打表模板
    {
        if(__builtin_popcount(i) == k)//__builtin_popcount，一个玄学函数，可以查看这个数的二进制中有几个1
        {
            tot ++;
            num[tot] = i;
        }
    }
    for (register int i = 1;i <= n;i ++)
    {
        int xx;
        read(xx);//读入一个数
        for (register int j = 1;j <= tot;j ++)
        {
            ans += ct[xx ^ num[j]];//累加（小心炸数组RE）
        }
        ct[xx] ++;//累加
    }
    fprint(ans);//输出
    return 0;//结束
}
```

---

## 作者：Robin_kool (赞：0)

### 题意：
$n$ 数中任意选出两个数 $x,y$ ，使得 $x \oplus y$ 转为二进制 $1$ 的数量正好为 $k$ ，求总方案数。


------------

前置芝士：对于 $x,y,z$，若 $x \oplus y = z$，那么有  $x \oplus z = y$，$y \oplus z = x$ 。

显然可以预处理出所有数异或的范围内，转成二进制满足上述条件的所有数，当然也可以用神秘函数，其他题解提到了。


对于每个读入的 $a_i(1 \leq i \leq n)$，都和处理出的所有数异或一遍，维护每一个 $a_j(1 \leq j < i)$ 出现的次数，根据上述异或的性质，$ans$ 累加异或值当前出现的次数。

不难看出，这样满足两两组合的性质，即每两对数**选且仅选** $1$ 次。

具体讲解看代码:

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N  = 2e5 + 10;
ll n, k, cnt, ans, a[N], b[N];
inline ll read(){
	ll x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * m;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
inline bool check(int x){
	int sum = 0;
	while(x) sum += (x % 2), x >>= 1;//处理部分，可用STL代替
	return sum == k;
}
signed main(){
	//freopen("CF769D.in", "r", stdin);
	//freopen("CF769D.out", "w", stdout);
    n = read(), k = read();
    for(int i = 0; i <= (1 << 14); ++ i) {
    	if(check(i)) a[++ cnt] = i;//因为k<=14所以只需要枚举到2^14，注意考虑0
	}
	for(int i = 1; i <= n; ++ i){
		ll x = read();
		for(int j = 1; j <= cnt; ++ j){
			ans += b[x ^ a[j]];//计算贡献
		}
		++ b[x];//储存之前的所有数
	}
	write(ans);
	return 0;
}

```


---

## 作者：COsm0s (赞：0)

显然，原问题等价于求 $x,y$ 二进制中异或值为 $1$ 的位数。

这一部分可以采用 STL `__builtin_popcount()` 实现，即 `__builtin_popcount(x ^ y)`，关于此函数请参照 [Link](https://oi.wiki/math/bit/#%E5%86%85%E5%BB%BA%E5%87%BD%E6%95%B0)。

然后注意到 $n \leq 10^4$，暴力枚举 $i,j$ 即可。

复杂度 $\Theta(n^2)$。

注意 `long long`。

```cpp
#include <bits/stdc++.h>
#define REP(i, l, r) for (int i = (l); i <= (r); ++ i)
#define DOW(i, r, l) for (int i = (r); i >= (l); -- i)
#define int long long
#define pii pair<int, int>
#define MPR make_pair
#define L first
#define R second
using namespace std;
namespace Cosmos {
	const int N = 1e5 + 5, inf = 1e9, mod = 998244353;
	const double PI = acos(-1);
	int cnt[N];
	int main() {
		int n, m, x, ans = 0;
		cin >> n >> m;
		REP(i, 1, n) cin >> x, cnt[x] ++;
		REP(i, 0, 1e4) {
			if(!cnt[i]) continue;
			REP(j, i, 1e4) {
				if(!cnt[j]) continue;
				if(__builtin_popcount(i ^ j) != m) continue;
				if(i == j) ans += cnt[i] * (cnt[i] - 1) >> 1;
				else ans += cnt[i] * cnt[j];
			}
		}
		cout << ans << '\n';
		return 0;
	}
}
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	int T = 1;
//	cin >> T;
	while (T --) Cosmos::main();
	return 0;
}
```


---

## 作者：first_fan (赞：0)

这道题的意思是说：给$n$个数，问这$n$个数中任选两个组成数对$(u,v)$，其中满足$u$与$v$的二进制下不同的位数一共有$k$位的有多少对。

首先，二进制下位数不同的个数，我们可以使用$\sf bitcount(u\ xor\ v)$实现，即统计$u$和$v$的异或值二进制下$1$的个数，若恰好有$k$个则满足条件。

通俗易懂一点，即求

$$\sf\sum_{i=1}^{n}\sum_{j=i+1}^{n}(bitcount(a[i]\ xor\ a[j])==k)$$

观察到数据1e4，我们考虑暴力枚举，最坏时间复杂度`即所有数都选上，当然这是不可能的`O(1e8)。我们发现可以开个桶，记录每个数出现的次数，由于本题中两个数值相同的数不算做一个，根据乘法原理，我们直接计算`满足条件的a[i]出现的次数与a[j]出现的次数的乘积`累加到答案里即可。

由于题目数据过小，此处就没有在序列数组中枚举，而是在1e4中直接枚举，看是否在序列中出现过，请勿吐槽-_-||

```cpp
#include <bits/stdc++.h>
#define ri register int
#define ll long long
using namespace std;

int read()
{
	int num=0;
	int flg=1;
	char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')
		{
			flg=-1;
		}
		c=getchar();
	}
	while(isdigit(c))
	{
		num=(num<<1)+(num<<3)+(c^48);
		c=getchar();
	}
	return num*flg;
}

const int maxn=1e6+7;

int f[maxn];

int main()
{
	int n=read();
	int m=read();
	for(ri i=1; i<=n; i++)
	{
		int x=read();
		f[x]++;
	}
	ll cnt=0;
	if(!m)
	{
		for(ri i=1;i<=maxn;i++)
		{
			cnt+=f[i]*(f[i]-1)/2;
		}
		return 0&printf("%lld",cnt);
	}//全组合
	for(ri i=1;i<=maxn;i++)
	{
		if(!f[i])
		{
			continue;
		}
		for(ri j=1;j<=maxn;j++)
		{
			if(!f[j])
			{
				continue;
			}
			ll Xor=i^j;
			int res=0;
			while(Xor)
			{
				res+=Xor%2;
				Xor>>=1;
			}
			if(res==m)
			{
				cnt+=f[i]*f[j];
			}//组合
		}
	}
	return 0&printf("%lld",cnt);
}
```

---

