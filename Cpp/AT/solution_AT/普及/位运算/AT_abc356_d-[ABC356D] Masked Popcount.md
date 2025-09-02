# [ABC356D] Masked Popcount

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc356/tasks/abc356_d

整数 $ N,M $ が与えられるので、 $ \displaystyle\ \sum_{k=0}^{N} $ $ \rm{popcount} $$ (k\ \mathbin{\&amp;}\ M) $ を $ 998244353 $ で割った余りを求めてください。

ただし、 $ \mathbin{\&amp;} $ はビット単位 $ \rm{AND} $ 演算を表します。

 ビット単位 $ \rm{AND} $ 演算とは？ 非負整数 $ a $ と非負整数 $ b $ とのビット単位 $ \rm{AND} $ 演算の結果 $ x\ =\ a\ \mathbin{\&amp;}\ b $ は次のように定義されます。  
- $ x $ は全ての非負整数 $ k $ について以下の条件を満たすただ $ 1 $ つの非負整数である。
- $ a $ を $ 2 $ 進法で書き下した際の $ 2^k $ の位と $ b $ を $ 2 $ 進法で書き下した際の $ 2^k $ の位が共に $ 1 $ なら、 $ x $ を $ 2 $ 進法で書き下した際の $ 2^k $ の位は $ 1 $ である。
- そうでないとき、 $ x $ を $ 2 $ 進法で書き下した際の $ 2^k $ の位は $ 0 $ である。
 
 
 例えば $ 3=11_{(2)},\ 5=101_{(2)} $ なので、 $ 3\ \mathbin{\&amp;}\ 5\ =\ 1 $ となります。  $ \rm{popcount} $ とは？ $ \rm{popcount} $$ (x) $ は、 $ x $ を $ 2 $ 進法で書き下した際に登場する $ 1 $ の個数を表します。  
 例えば $ 13=1101_{(2)} $ なので、 $ \rm{popcount} $$ (13)\ =\ 3 $ となります。

## 说明/提示

### 制約

- $ N $ は $ 0 $ 以上 $ 2^{60} $ 未満の整数
- $ M $ は $ 0 $ 以上 $ 2^{60} $ 未満の整数
 
### Sample Explanation 1

\- $ \rm{popcount} $$ (0\mathbin{\&amp;}3)\ =\ 0 $ - $ \rm{popcount} $$ (1\mathbin{\&amp;}3)\ =\ 1 $ - $ \rm{popcount} $$ (2\mathbin{\&amp;}3)\ =\ 1 $ - $ \rm{popcount} $$ (3\mathbin{\&amp;}3)\ =\ 2 $ - $ \rm{popcount} $$ (4\mathbin{\&amp;}3)\ =\ 0 $ であり、これらの和は $ 4 $ です。

### Sample Explanation 2

$ N=0 $ である場合や $ M=0 $ である場合もあります。

### Sample Explanation 3

$ 998244353 $ で割った余りを求めることに注意してください。

## 样例 #1

### 输入

```
4 3```

### 输出

```
4```

## 样例 #2

### 输入

```
0 0```

### 输出

```
0```

## 样例 #3

### 输入

```
1152921504606846975 1152921504606846975```

### 输出

```
499791890```

# 题解

## 作者：LuukLuuk (赞：13)

# 题解：AT_abc356_d [ABC356D] Masked Popcount

#### 题目大意
原文已经很清楚了，就是输入一个 $n$，一个 $m$，按照下面的方法求和：
$$
sum = \sum_{i=0}^{n}popcount(i \,\& \,M)
$$
其中 popcount 函数用于求一个数在二进制下 $1$ 的个数。

---------------------------------
#### 题解
拿到题，我们先看数据范围：

- $1 \le N,M \le 2^{60} - 1$

看起来，数据还是蛮大的。

这种数据范围，一般考虑 $O(\log n)$ 或 $O(1)$ 的做法。这道题，就是用 $O(\log n)$ 级做法的。

首先，我们看到按位与，我们就可以知道答案是从 $0$ 到 $N$ 的所有数字在二进制下 $M$ 为 $1$ 的那一些位出现 $1$ 的次数。例如在样例一中，我们就应该统计 $0$ 到 $4$ 的所有数字的第一位和第二位的 $1$ 的个数，因为 $3$ 的二进制为 $(0011)_2$。

接下来，为了更直观的找到二进制出现的规律，我打了一个[表](https://www.luogu.com.cn/paste/8benwqbo)。

可以发现，第一位是 $0$ 和 $1$ 交替出现，第二位是两个 $0$ 和两个 $1$ 所组成的数字串循环出现，第三位是四个 $0$ 和四个 $1$ 所组成的数字反复出现。因此，我们可以看出从第 $0$ 个数到第 $N$ 个数的第 $i$ 位和是：
$$
sum_{i} = (N+1) \div (2 \times 2^i) \times 2^i + (N+1) \bmod (2 \times 2^i) -2^i
$$
其中：
- 我们称 $(N+1) \div (2 \times 2^i) \times 2^i$ 为第一项，后面的为第二项。
- 第一项是完整循环的贡献，第二项是最后那个不完整的循环贡献。
- $(N+1)$ 是因为数字是从 $1$ 开始的，而我们的计算还要考虑 $0$ 并且从 $1$ 开始编号。
- $(2 \times 2^i)$ 是因为查表我们可以发现，$2 \times 2^i$ 是一个循环，其中后 $2^i$ 个数是 $1$，例如表中数字的第三位和第四位（比较明显），这也是第一项中完整序列的个数要乘上 $2^i$，第二项中剩余数的个数要减去 $2^i$ 的原因（前面都是 $0$）。
- **注意，第一项的计算顺序不能改变，因为整数除法要向下取整；当第二项值小于 $0$ 时，第二项不算进 $sum$，因为剩下的都是 $0$！**
- 在代码中，为了简洁，我们定义 $j$ 为 $2^i$。

题解到这里就结束了，不过，**记得开 `long long`！**

完整代码：
```
#include <cstdio>
using namespace std;
#define int long long

const int mod = 998244353;
int ans;
int n, m, x; 

signed main() {
	scanf("%lld%lld", &n, &m);
	for (int i = 1; m; ++i) {
		if (m & 1) {
			int j = (1ll << (i - 1));
			ans += (((n + 1) / (2 * j)) * j);
			ans %= mod;
			x = ((n + 1) % (2 * j) - j);
			if (x > 0)	ans += x;
			ans %= mod;
		}
		m >>= 1;
	}
	printf("%lld", ans);
	return 0;
}
```
----
#### 更新
2024/6/20 去掉了多余的 $sum_i$ 求和中第二项多余的 $2^i$，感谢 dengjunhan。

---

## 作者：Harrylzh (赞：1)

## 思路

$N,M$ 都非常大，首先排除暴力判断。考虑对于 $M$ 二进制中的每一个 $1$，计算它的贡献，即 $1$ 到 $N$ 中每个数的二进制位里出现它的次数。观察发现它的出现存在规律：

| 十进制 | 二进制 |
| :----------: | :----------: |
| 0 | 000 |
| 1 | 001 |
| 2 | 010 |
| 3 | 011 |
| 4 | 100 |
| 5 | 101 |

例如倒数第二位，总是按照两个 $0$ 和两个 $1$ 交替出现。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m;
long long lowbit(long long x)
{
	return x&(-x);
}
long long ans=0;
const long long P=998244353;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(long long i=m;i;i-=lowbit(i))//枚举是一的位置
	{
		long long lt=lowbit(i);
		long long cj=0;
		cj+=(n+1)/(2*lt)*lt%P;
		cj%=P;
		if((n+1)%(2*lt)>lt)cj+=(n+1)%(2*lt)-lt;//找规律计算
		cj%=P;
		ans+=cj;
		ans%=P;//记得取模
		
	}
	cout<<ans<<"\n";
}
```

---

## 作者：刘梓轩2010 (赞：1)

# ABC-356D题解

**注:借鉴官方题解**

## 题意

给出 $n,m$ 求 $(\sum_{k=0}^{n}\operatorname{popcount}( k\& m) ) \bmod 998244353$ 。

其中 $\operatorname{popcount}(x)$ 表示 $x$ 的二进制中 $1$ 的个数。

## 思路

显然可以发现，对于第 $j$ 位，当 $k$ 与 $m$ 的第 $j$ 位为 $1$ 时，才会产生贡献。

于是，本题转化成了，对于每个满足 $m$ 的第 $j$ 位为 $1$ 的 $j$，求出 $[0,n]$ 中第 $j$ 位为 $1$ 的 $k$ 的个数。

首先，$[0,2^j-1]$ 中的数，它的第 $j$ 位一定不为 $1$。 

其次，$[2^j,2^{j+1})$ 中的数，它的第 $j$ 位一定为 $1$ 。

（可以写出二进制的形式加深理解）

因此，在 $[0,2^{j+1})$ 中，共有 $2^j$ 个满足上述要求的数。

而对于一个数 $i$，它的第 $j$ 位一定与 $i+2^{j+1}$ 一致（因为只对 $j+1$ 以及它左边的位有影响）。

因此，$[2^{j+1},2\times2^{j+1})$ 之间也有 $2^j$ 个数满足要求，以此类推。

所以，对于非负整数 $k$，在 $[0,k\times2^{j+1})$ 之间的整数中，有 $k\times 2^j $ 个数符合要求。

再来讨论剩下的不足 $2^{j+1}$ 的部分。

设 $l=n \bmod 2^{j+1}$。

则如果 $l \geq 2^j$，则 $k\times2^{j+1}+2^j$ 到 $k\times 2^{j+1}+l$ 之间共 $l-2^j+1$ 个数符合要求。

否则无贡献。

最后统计答案。

## Code
```cpp
#include <bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;
const int N=2e5+10;
const int inf=0x3f3f3f3f3f3f3f3f;
const int p=998244353;
int n,m;
int ans;
int fun(int i,int n)
{
    int p2=(1ll<<i);
    int k=n/(2*p2);
    int res=k*p2;
    int l=n%(2*p2);
    if(l>=p2) res+=(l-p2+1);
    return res%p;
}
signed main()
{
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=0;i<60;i++)
	{
	    if((1ll<<i)&m) 
	    {
	        ans+=fun(i,n);
	        ans%=p;
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：xz001 (赞：1)

一看到数据量如此大，直接数位 dp。

设立 $dp_{i,j}$ 表示在第 $i$ 位，前面是否均为最高位时的情况数。

转移时发现需要知道自第 $i$ 位往后，前面是否均为最高位的数数量，于是再设 $f_{i,j}$ 表示自第 $i$ 位往后，前面是否均为最高位的数个数。

代码如下：

```cpp
/*
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3, "Ofast", "inline")
*/
#include<bits/stdc++.h>

using namespace std;

#define re			register
#define int			long long
#define fi			first
#define se			second
#define swap(a, b) 	a ^= b, b ^= a, a ^= b
#define pb 			push_back
#define all(x)		x.begin(), x.end()
#define max(a, b)	(a > b ? a : b)
#define min(a, b)	(a < b ? a : b)
#define il			inline
#define abs(x)		((x ^ (x >> 63)) - (x >> 63))

typedef pair<int, int> PII;

const int N = 1e6 + 10;
const int M = 1e6 + 10;
const int INF = 1e18, mod = 998244353;
const double eps = 1e-6;

il int  read() { re int x = 0; re bool f = true; re char c = getchar(); while (c < 48 || c > 57) { if (c == '-') f = false; c = getchar(); } while (c >= 48 && c <= 57) x = (x << 3) + (x << 1) + c - 48, c = getchar(); return f ? x : -x; }
il void write(int x) { if (x < 0) putchar('-'), x = -x; if (x > 9) write(x / 10); putchar(x % 10 + 48); }
il void wel(int x) { write(x), putchar('\n'); }
il void wsp(int x) { write(x), putchar(' '); }

int n, m, f[105][2], dp[105][2];

int dfs (int i, int j) {
	if (i < 0) return 1;
	if (f[i][j] != -1) return f[i][j];
	int p = j ? (n >> i & 1) : 1, ans = 0;
	for (int t = 0; t <= p; ++ t )
	    ans = (ans + dfs (i - 1, j && (t == p))) % mod;
	    
	return f[i][j] = ans;
}

int Dfs (int i, int j) {
	if (i < 0) return 0;
	if (dp[i][j] != -1) return dp[i][j];
	int p = j ? (n >> i & 1) : 1, ans = 0;
	for (int t = 0; t <= p; ++ t )
	    ans = (ans + ((m >> i & 1) & t) * dfs (i - 1, j && (t == p)) % mod + Dfs (i - 1, j && (t == p))) % mod;
	    
	return dp[i][j] = ans;
} 

signed main() {
    scanf("%lld%lld", &n, &m);
	memset(f, -1, sizeof(f));
	memset(dp, -1, sizeof(dp));
	printf("%lld\n", Dfs (62, 1));
    return 0;
}


```

---

## 作者：Crazyouth (赞：1)

## 分析

赛时的非常裸思路。

注意到这题的求和可以看成是 $1\sim n$ 的 $\operatorname{popcount}$ 求和减去那些被 $m$ 消掉的部分，其中前者可以直接使用公式得到。我们观察可以知道，从 $1$ 开始的数在二进制下的第 $k$ 位（最低位为第 $0$ 位）是 $2^{k+1}$ 个 `1` 与 $2^{k+1}$ 个 `0` 交替出现，因此后者是可以计算的。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int unsigned long long
const int mod=998244353;
map<int,int> mp;
int ans=0;
int getsum(int k)
{
	if(!k) return 0;
	if(mp[k]) return mp[k];
	if(k%2==0) mp[k]=getsum(k/2)+getsum(k/2-1)+k/2;
	else mp[k]=2*getsum((k-1)/2)+(k-1)/2+1;
	mp[k]%=mod;
	return mp[k];
}
signed main()
{
	int n,m;
	cin>>n>>m;
	ans=getsum(n);
	for(int i=0;(1ll<<i)<=n;i++)
	{
		if(m>>i&1ll) continue;
		ans+=mod;
		ans-=(n/(1ll<<(i+1))*(1ll<<i))%mod;
		ans%=mod;
		ans+=mod;
		ans-=max(n%(1ll<<(i+1))-(1ll<<i)+1,0ll)%mod;
		ans%=mod;
	}
	cout<<ans%mod;
}

---

## 作者：OPEC (赞：0)

# [[ABC356D] Masked Popcount](https://www.luogu.com.cn/problem/AT_abc356_d)

这道题要观察会发现，当二进制 $m$ 的第 $i$ 位是零时，对 popcount 没有贡献。所以枚举 $m$ 的二进制为一的位数就可以了。

 $m$ 的第 $i$ 为所给出的贡献有 $m$ 的二进制第 $i$ 位前的数量乘后面能组成的数加最大限度，也就是 $(\frac{n}{2^i+1})\times 2^i +((\frac{n}{2^i})\cap\{1\})\times(n\cap\{2^i-1\}))$。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define int long long
const int N=1e6+10,M=2e6+10;
const int INF=0x3f3f3f3f3f3f3f3f;
const int P=998244353;//3221225477
int n,m,ans;
signed main()
{
	fst
	cin>>n>>m;
	n++;
	for(int i=0;i<=60;i++)
	{
		if((m>>i)&1)
		{
			ans+=((n>>(i+1))<<i)%P+((n>>i)&1)*(n&((1ll<<i)-1))%P;
			ans%=P;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

[双倍经验！！！](https://www.luogu.com.cn/problem/P4317)

注意到 $\operatorname{and}$ 的性质：当二进制位都为 $1$ 时才为 $1$，否则为 $0$。

则我们可以遍历 $m$ 的二进制位，若当前位为 $1$，则造成的贡献为 $1 \sim n$ 中该位为 $1$ 的数的个数。

直接数位 `DP` 计算即可。

时间复杂度为 $O(\log N)$。

---

## 作者：Liyunze123 (赞：0)

与运算后第 $i$ 位为 $1$，$m$ 的二进制第 $i$ 位肯定是 $1$。对 $m$ 的二进制每个为 $1$ 的第 $i$ 位，找 $n$ 以内第 $i$ 位为 $1$ 的数，累加即可。

这个查找函数，实现方法如下：

1. 我们可以发现这 $n+1$ 个数可以每 $2^i$ 个一分组，第一组二进制全是 $0$，第二组全是 $1$，以此类推。
2. 我们可以求出分组数，以及二进制是 $1$ 的组数。其实就是 $(n+1)\div2^i\div2$。这里的 $\div$ 都是向下取整。
3. 组数为奇时，不满一组的也要算上去，就是 $(n+1)\mod2^i$。

代码如下：
```
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
long long n,m,ans;
long long f(long long n,int i){
	long long s=0,t=(long long)1<<i;
	n++,s=(n/t/2%mod)*(t%mod)%mod;
	if(n/t%2==1)s+=n%t%mod;
	return s;
}
int main(){
	scanf("%lld%lld",&n,&m);
	for(int w=0;w<=60;w++)ans=(ans+(m>>w&1)*f(n,w))%998244353;
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Fantasy_Segment_Tree (赞：0)

题目大意如下。

> 给定两个数 $n$ 和 $m$，请你求出 
>$$\sum_{k = 0}^{n}\operatorname{popcount}(k \& m)$$ 
> 的值。$1 \leq n, m \leq 2^{60} - 1$.

思路是这样的。

首先，$\operatorname{popcount}$ 运算是求某一个数的二进制表达式上有多少个 $1$，而与运算是当且仅当两个数的某一位上都是 $1$ 时结果的这位数上才为 $1$。

然后发现数据范围如此之大！所以，我们不能算每个数的贡献，我们只能按位进行计算。

对于每个位来讲，只有 $m$ 的这一位上是 $1$ 结果才能是 $1$。所以，我们可以对于 $m$ 中每个为 $1$ 的位，计算在 $0$ 到 $n$ 中这一位同样为 $1$ 的数的个数。个数之和即是答案。那么怎么算呢？

对于二进制来讲，$2^x$ 这一位是 $1$ 代表这个数对 $2^{x + 1}$ 取模的结果大于等于 $2^x$。

所以，可以分成几段计算。首先，整除 $2^{x + 1}$ 的部分可以直接按照一半计算。然后，把剩下的部分中余数大于等于 $2^x$ 的部分加上就可以了。计算并把答案加上即可。

赛时思路，如果有更好的思路请留言～

代码如下。

```cpp
#include <iostream>
using namespace std;

long long x, y, f[65], p2[65], ans, mod = 998244353;

int main() {
	cin >> x >> y;
	p2[0] = 1;
	for(int i = 1; i <= 60; i++) {
		p2[i] = p2[i - 1] * 2ll;
		//cout << p2[i] << " ";
	}
	int cnt = 0;
	while(y) {
		long long d = y & 1;
		f[cnt] = d;
		y >>= 1;
		cnt++;
	}
	//cout << cnt << endl;
	for(int i = 0; i < cnt; i++) {
		if(f[i] == 1) {
			//cout << i << endl;
			long long p = p2[i + 1];
			long long t = (((x - x % p) / p) % mod * (p2[i] % mod) % mod + mod) % mod;
			ans = (ans + t);
			if(ans >= mod) ans -= mod;
			if(x % p >= p2[i]) {
				long long r = ((x % p - p2[i] + 1) % mod + mod) % mod;
				ans = (ans + r);
				if(ans >= mod) ans -= mod;
			}
		}
	} 
	cout << (ans + mod + mod) % mod;
}
```

---

