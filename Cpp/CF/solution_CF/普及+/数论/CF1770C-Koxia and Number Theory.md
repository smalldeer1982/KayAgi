# Koxia and Number Theory

## 题目描述

Joi has an array $ a $ of $ n $ positive integers. Koxia wants you to determine whether there exists a positive integer $ x > 0 $ such that $ \gcd(a_i+x,a_j+x)=1 $ for all $ 1 \leq i < j \leq n $ .

Here $ \gcd(y, z) $ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ y $ and $ z $ .

## 说明/提示

In the first test case, we can set $ x = 4 $ . This is valid because:

- When $ i=1 $ and $ j=2 $ , $ \gcd(a_i+x,a_j+x)=\gcd(5+4,7+4)=\gcd(9,11)=1 $ .
- When $ i=1 $ and $ j=3 $ , $ \gcd(a_i+x,a_j+x)=\gcd(5+4,10+4)=\gcd(9,14)=1 $ .
- When $ i=2 $ and $ j=3 $ , $ \gcd(a_i+x,a_j+x)=\gcd(7+4,10+4)=\gcd(11,14)=1 $ .

In the second test case, any choice of $ x $ makes $ \gcd(a_1 + x, a_2 + x) = \gcd(3+x,3+x)=3+x $ . Therefore, no such $ x $ exists.

## 样例 #1

### 输入

```
2
3
5 7 10
3
3 3 4```

### 输出

```
YES
NO```

# 题解

## 作者：abensyl (赞：10)

原题：[CF1770C Koxia and Number Theory](https://www.luogu.com.cn/problem/CF1770C)。

比赛时失误吃一罚时。

## 思路

本题目为数学题。

- 有两种情况会使构造互质数列无解。

> 第一种情况：有两个相等的数，哪怕两个数均为 $1$ 加上一个正整数后，会变成两个大于等于二的数，而这两个数的最大公约数根据性质 $\gcd(x,x)=x$，两个数的最大公因数一定大于等于二，无解，输出 `No`。

> 第二种情况：对一正整数任意数 $k(k\geq 2)$，令 $sum_i$ 为数组 $a$ 中模 $k$ 余数为 $i$ 的数的个数。那么，如果有一个 $k$ 能够使得 $sum_0$ 到 $sum_{k-1}$ 都大于等于二，那么一定无解，因为不论你加多少，总会有两个数最大公约数是 $k$ 的正整数倍，所以无解，输出 `No`。

> 在第二种情况中，很容易发现，我们只要枚举 $k\in [2,n/2]$ 即可。

剩下情况输出 `Yes`，完美结束。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int T,n;
int t[103];
int a[103][103];
void solve() {
		memset(a,0,sizeof a);
		cin>>n;
		for(int i=1;i<=n;++i){
			cin>>t[i];
			for(int j=1;j<=n;++j){
				a[j][t[i]%j]++;
			}
		}
		for(int i=1;i<=n;++i)
			for(int j=i+1;j<=n;++j)
				if(t[i]==t[j]) {
					cout<<"No\n"; //判断相等的数
					return;
				}
		for(int i=2;i<=n;++i) {
			bool flag=1; //判断余数
			for(int j=0;j<i;++j) {
				if(a[i][j]<2) { 
					flag=0;
					break;
				}
			}
			if(flag) {
					cout<<"No\n";
					return;
				}
		}
		cout<<"Yes\n";
		return;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--) solve();
	return 0;
}
```

我的 [AC记录](https://www.luogu.com.cn/record/98459035)。

---

## 作者：Alex_Wei (赞：6)

好题。

首先若 $a$ 并非两两不同则无解。

思考数据规模较小的情形，发现两奇两偶无解。研究其本质后推广至一般结论：若存在 $p$ 使得对每个 $0\leq r < p$，模 $p$ 余 $r$ 的 $a_i$ 的数量均不小于 $2$，则无解，因为 $x$ 模 $p$ 不能为 $0\sim p - 1$，这样的 $x$ 不存在。

否则，对每个质数 $p$，找到使得模 $p$ 余 $r$ 的 $a_i$ 的数量小于 $2$ 的 $r$，则可令 $x\equiv r\pmod p$，中国剩余定理保证满足同余方程组的 $x$ 存在。

根据抽屉原理，只需检查所有小于 $n$ 的质数即可。如果不想筛素数，也可检查所有数。时间复杂度 $\mathcal{O}(\frac {n ^ 2} {\log n})$ 或 $\mathcal{O}(n ^ 2)$。[代码](https://codeforces.com/contest/1770/submission/187485511)。

---

## 作者：氧少Kevin (赞：4)

## CF1770C - Koxia and Number Theory
### 题意
- 给出一个长为 $n(n\leq 100)$ 的序列 $a_i(a_i\leq 10^{18})$，是否存在一个数字 $X$，使得对于任意一对 $(a_i,a_j)$ 来说，$\gcd(a_i+X,a_j+X)=1$。

### 思路
- 首先，有重复的元素，肯定不行
- 考虑一种条件：如果有至少两个奇数，又至少有两个偶数，那么一定不行。但这只是其中一个条件，来看一组 hack 数据：
```
6
6 12 4 10 8 14
这组数字都是偶数，能通过上述的条件，但是我分别构造了 2 个模 3 为 0，1，2 的数字
X = 0 时，会导致 a1 和 a2 不互质，gcd=3；
X = 1 时，会导致 a5 和 a6 不互质，gcd=3；
X = 2 时，会导致 a3 和 a4 不互质，gcd=3；
```
- 1.通过这组数据，我们能发现这样的性质：
    - $\gcd(x,y)=3 \Leftrightarrow x\equiv y\equiv 0(\mod 3)$
    - $\gcd(x+k,y+k)=3 \Leftrightarrow x\equiv y\equiv k(\mod 3)$
- 2.我们可以把上面这组数据的情况加以推广：
    - 对于给定的序列 $a_i$，我们通过枚举 $\gcd$ 的方式来判断是否存在 $X$
    - 对于一个当前枚举的 $\gcd$ $p$，如果对于 $[0,p-1]$ 中的任何数字 $x$，若都存在至少 $2$ 个 $a_i$ 满足 $a_i\mod p = x$，则说明无论 $X$ 取何值，总存在至少两个 $a_i$ 满足 $\gcd(a_i,a_j)=p$，出现这种情况则检查不通过，答案为 $\tt{NO}$
    - 如果枚举了所有可能的 $\gcd$，并且均通过，则可以确定答案为 $\tt{YES}$
    - 枚举的 $\gcd$ 数量不多，$\frac{n}{2}$ 个即可

---

## 作者：zajasi (赞：4)

## 解题思路
观察到这道题 $n\le100$，也就是大概 $n^3$ 的复杂度，所以就放心做了。

首先，如果有两个数相同，因为 $x$ 不能取 $0$ 的缘故，所以肯定就不行了。

然后，如果某一个质数的余数中，如果每一种余数都有至少两个的话，这显然是不行的。

为什么每一种余数都有至少两个的话，这显然是不行的呢？因为此时，余数为 $0$ 的任意两个数的最大公约数肯定不是 $1$，若取任意的 $x$，都有可能将至少两个原来余数不是 $0$ 的数变为余数为 $0$，也就是最大公约数不为 $1$，自然不行。

那么这一个质数的范围是什么呢？本蒟蒻刚开始看到 $a_i$ 的范围是 $10^{18}$，于是就放弃了。后来思考到——如果某一个质数它的余数个数至少要有两个的话，也就是说 $100$ 个数中最多只能满足 $50$ 个。本蒟蒻赛中保险起见，写了 $1$ 到 $100$ 所有的质数。

于是，这道题就顺利解决啦！
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t;
int a[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};//1到100质数表
int n;
int x[101],c[101];
main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>x[i];
		}
		int f=0;
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				if(x[i]==x[j]){
					cout<<"NO\n";
					f=1;
					break;
				}
			}
			if(f==1)break;
		}//判断有没有任意两个数相等
		if(f==1)continue;
		int ff=0;
		for(int i=0;i<25;i++){
			memset(c,0,sizeof c);
			for(int j=1;j<=n;j++){
				c[x[j]%a[i]]++;//统计余数个数
			}
			f=0;
			for(int j=0;j<a[i];j++){
				if(c[j]<2){
					f=1;
					break;
				}
			}
			if(f==0){
				cout<<"NO\n";
				ff=1;
				break;
			}
		}
		if(ff==0){
			cout<<"YES\n";
		}
	}
	return 0;
}
```


---

## 作者：rui_er (赞：3)

显然，如果存在 $a_i=a_j$，则一定无解。

否则，考虑每一个质数 $k$，如果原数组每个数对 $k$ 取模后，每种余数都出现至少两次，则无解。因为此时无论如何选取 $x$，都至少有两个数是 $k$ 的倍数。

下面证明充分性。对于每一个 $k$，找到一个数 $y$ 使得对 $k$ 取模余 $y$ 的数不超过一个，那么 $x\equiv -y\pmod{k}$ 的 $x$ 均符合题意。下面考虑对同余方程组有限制的 $k$ 的个数。如果 $k\ge 10^{18}$ 即值域，此时每个余数都至多出现一次，也就是 $y$ 可以取遍 $0\sim k-1$ 的所有数，此时便不再需要考虑 $k$。因此 $k$ 有有限个，可以使用中国剩余定理解得 $x$。

另外，由于 $k > 50$ 时，要出现无解情况，则 $n\ge 2k > 100$ 已经超出了数据范围，因此判断时只需要考虑 $2\sim 50$ 的 $k$ 即可。其实只需要判断 $k$ 是质数的情况，但是合数也判了也不会出问题。

感谢 @Breakingtdasc 指出了原证明中的一处错误。

```cpp
// Problem: Koxia and Number Theory
// Contest: Codeforces
// URL: https://m2.codeforces.com/contest/1770/problem/C
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(ll x=(y);x<=(z);x++)
#define per(x,y,z) for(ll x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;
const ll N = 105;

ll T, n, a[N], cnt[N];
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

int main() {
	for(scanf("%lld", &T); T; T--) {
		scanf("%lld", &n);
		rep(i, 1, n) scanf("%lld", &a[i]);
		sort(a+1, a+1+n);
		ll m = unique(a+1, a+1+n) - a - 1;
		if(m < n) puts("NO");
		else {
			ll ok = 1;
			rep(mod, 2, 50) {
				rep(i, 0, mod-1) cnt[i] = 0;
				rep(i, 1, n) ++cnt[a[i]%mod];
				ll now = 0;
				rep(i, 0, mod-1) now |= cnt[i] <= 1;
				ok &= now;
			}
			puts(ok ? "YES" : "NO");
		}
	}
	return 0;
}
```

---

## 作者：LHQing (赞：2)

#### 思路分析

首先从奇偶性出发。发现如果有两个奇数与两个偶数同时在序列中，那么无论加上去的是奇数还是偶数，最终都会有两个数奇偶性相同，不互质。

奇偶性是 $a_i\bmod 2$ 时的情况。同理，我们可以将其推广到 $a_i\bmod k$ 时的情况。若 $b_i=a_i\bmod k$ 中 $[0,k-1]$ 均出现两次及以上，那么一定不满足要求，输出 `NO`。

因为 $k$ 个数字要出现两次以上，所以 $2k\le n$，$k$ 从 $2\sim \dfrac n2$ 枚举即可。

#### 题解代码

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxn = 1e2 + 10;

int t, n;
int a[maxn];
int b[maxn];

signed main() {
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        sort(a + 1, a + n + 1);
        bool ck = true;
        for (int i = 2; i <= n; i++) {
            if (a[i - 1] == a[i]) {
                ck = false;
                break;
            }
        }
        if (!ck) {
            puts("NO");
            continue;
        }
        for (int k = 2; k <= n / 2; k++) {
            memset(b, 0, sizeof(b));
            for (int i = 1; i <= n; i++) ++b[a[i] % k];
            bool fl = true;
            for (int i = 0; i < k; i++) {
                if (b[i] < 2) {
                    fl = false;
                    break;
                }
            }
            if (fl) {
                ck = false;
                break;
            }
        }
        puts(ck ? "YES" : "NO");
    }
    return 0;
}
```

---

## 作者：yangyang1000 (赞：2)

### UPD

感谢 [鲨齿渊虹](https://www.luogu.com.cn/user/462965) 的发现的漏洞，已修复。

### 题目大意

有一个 $a$ 数组，长度为 $n$，问存不存在 $x$，使所有的 

$$\gcd(a_i+x,a_j+x) = 1(1 \le i,j \le n)$$

本题主要考察数论。

### 思路

很容易想到大部分时间输出 $\texttt{YES}$，所以我们分析一下什么时候输出 $\texttt{NO}$。

### 什么时候输出 $\texttt{NO}$ ?

### 1. 有两个数相等。

这个很好推理，两个相等的数永远不互质。

### 2.对于 $k(2 \le k \le n)$，数列中模 $k$ 余任意数的数均不少于 $2$ 个。

此时对于任意的$x$，我们不妨设存在 $a$，$b$ 使：

$$a+x \equiv 0 \pmod k$$

$$b+x \equiv 0 \pmod k$$

所以：

$$k \mid a+x$$

$$k \mid b+x$$

也就是：

$$\gcd(a+x,b+x) \equiv 0 \pmod k$$

这样的话就得出结论：对**任意**的 $x$ ，都存在 $a$，$b$ 使 $\gcd(a+x,b+x) \ne 1$。

一共就 $n$ 个数，其实 $k$ 枚举到 $\dfrac{n}{2}$ 即可，但我为了追求稳妥，$k$ 就枚举到 $n$。

有了以上的推论，可以想到用一个数组来记录数列中模 $k$ 的余数，记得清零！

### 代码

时间复杂度：$O(Tn^2)$

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
 
long long t,n,a[105],bucket[1005];
 
int main()
{
	scanf("%lld",&t);
	for(long long o=1;o<=t;o++)
	{
		bool flag = true;
		scanf("%lld",&n);
		for(long long i=1;i<=n;i++) 
			scanf("%lld",&a[i]);
		
		for(long long i=1;i<=n;i++)
			for(long long j=1;j<i;j++)
				if(a[i] == a[j])
				{
					printf("NO\n");
					flag = false;
					i = n;
					break;
				}
		
		if(flag == false) continue;
		
		for(long long i=2;i<=n;i++)
		{
			memset(bucket,0,sizeof(bucket));
			bool flag2 = true;
			for(long long j=1;j<=n;j++)
			{
				bucket[a[j] % i]++;
			}
			for(long long j=0;j<i;j++) 
			{
				if(bucket[j] < 2)
				{
					flag2 = false;
					break;
				}
			}
			if(flag2)
			{
				flag = false;
				break;
			}
		}
 
		if(flag == false) printf("NO\n");
		else printf("YES\n");
	}
	return 0;
}
```


---

## 作者：ztlh (赞：2)

~~罚时吃到饱~~

# Solution

让我们想想什么情况下会存在**不互质**的两个数：

- 两个数相等。

- 在模某个质数 $p$ 时，若 $p$ 个**剩余类**中每个剩余类都有**至少 $2$ 个数**，则无论加上的数 $x$ 等于多少，总有同一剩余类中的两个数有公约数。

因此我们需要做的是：

1. 将数组**排序**，判断是否有相等的数，存在则输出 $\text{NO}$。

2. 开个数组存数组内所有数模某个质数的余数，统计每个剩余类的项数并判断。

那**质数的范围**呢？

由于 $n \le 100$，要使每个剩余类都有至少 $2$ 个数，这个质数一定**不超过 $50$**。

# Code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int T,n;
ll a[105];
int p[25]={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
int cnt[25][55];
int sum=15;
bool f,g;
int main(){
	scanf("%d",&T);
	while(T--){
		memset(cnt,0,sizeof(cnt));
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%lld",&a[i]);
		sort(a+1,a+n+1); f=1;
		for(int i=1;i<n;i++)
			if(a[i]==a[i+1]){ //判断相等
				f=0;
				break;
			}
		for(int i=1;i<=sum;i++){
			g=1;
			for(int j=1;j<=n;j++) cnt[i][a[j]%p[i]]++; //统计
			for(int j=0;j<p[i];j++)
				if(cnt[i][j]<2){
					g=0;
					break;
				}
			if(g){
				f=0;
				break;
			}
		}
		if(f) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```

---

## 作者：wfc284 (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF1770C)  
考虑何时不满足：  
+ $\exist a_i = a_j$；  
+ $\exist p \geqslant 2$，令 $cnt_i$ 为 $a$ 数组中对 $p$ 取余等于 $i$ 的元素个数，满足 $\forall i \in [0,p),cnt_i \geqslant 2$。  

第一种情况好判断，扫一遍即可。  
第二种情况需要解释一下：
### 为什么这种情况不符合：
$$ 令x=ap+b \ ,b\in[0,p) $$
$$ \because \forall cnt_i \geqslant 2$$  
$$ \therefore 必有a_i \equiv q_j \equiv p-b \mod p$$
$$ \therefore a_i+x \equiv a_j+x \equiv a_i+b \equiv a_j+b \equiv (p-b)+b \equiv p \equiv 0 \mod p$$
$$ 即 \gcd(a_i,a_j)=p>1，显然不符合。$$
### 如何判断：
无需把 $p$ 枚举到很大，只要到 $\left \lfloor \frac{n}{2} \right \rfloor$ 即可。因为若 $p>\left \lfloor \frac{n}{2} \right \rfloor$，则 $\Sigma cnt_i = n < 2p$，而若满足此类情况，$\forall cnt_i \geqslant 2$，即 $\Sigma cnt_i >= 2p$，不可能满足。故 $p$ 只要到$\left \lfloor \frac{n}{2} \right \rfloor$ 即可。  
### Code
```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define Linf 0x3f3f3f3f3f3f3f3f
#define re register
#define int long long
using namespace std;
const int N = 102;

int T, n, a[N];

int cnt[N];
bool check() {
	for(re int i = 1; i <= n; ++i)
		for(re int j = i+1; j <= n; ++j)
			if(a[i] == a[j]) return false;
	
	for(re int p = 2; p <= n/2; ++p) {
		memset(cnt, 0, sizeof(cnt));
		for(re int i = 1; i <= n; ++i) ++cnt[a[i] % p];
		int flag = 0;
		for(re int i = 0; i < p; ++i) 
			if(cnt[i] < 2) {
				flag = 1;
				break;
			}
		if(!flag) return false;
	}
	return true;
}

signed main() {
	cin >> T;
	while(T--) {
		cin >> n;
		for(re int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
		cout << (check()? "YES\n": "NO\n");
	}
    return 0;
}
```

---

## 作者：sgl654321 (赞：1)

### 题目大意
给定一个长度为 $n$ 的正整数序列 $a$。问是否存在一个正整数 $x$，使得每一对 $a_i,a_j(i<j)$ 满足 $\gcd(a_i+x,a_j+x)=1$。

### 解题思路
我们先观察样例。发现第二个样例中，有两个数相同，一定不存在 $x$ 了，证明显然。于是得到第一个结论：**如果 $a$ 中有两个数相同，那么一定不存在 $x$**。

接着我们开始自己造数据。例如：$n=4$，$a=\{3,5,10,12\}$。经过几番尝试之后发现也不行，因为 $a$ 序列中有两个奇数，有两个偶数。不管你的 $x$ 是奇数还是偶数，都必然存在一对数，满足 $\gcd(a_i+x,a_j+x)=2$。所以又得到一个结论：**如果 $a$ 中有两个及以上奇数和两个及以上偶数，那么一定不存在 $x$**。

再构造一组数据：$n=6$，$a=\{2,3,4,6,8,10\}$。经过几番尝试之后发现还是不行。观察到，每一次都会存在一组数使得 $\gcd(a_i+x,a_j+x)=3$。因为这个序列中，有两个数模 $3$ 余 $1$，有两个数模 $3$ 余 $2$，还有两个数是 $3$ 的倍数。所以不论你的 $x$ 模 $3$ 余 $1$，还是模 $3$ 余 $2$，还是 $3$ 的倍数都不行。所以又得到一个结论：**如果 $a$ 中有两个及以上数模 $3$ 余 $1$，两个及以上数模 $3$ 余 $2$，两个及以上数是 $3$ 的倍数，拿么 一定不存在 $x$**。

尝试了那么多，我们总发现一些结论了吧。

**提出猜想**：若序列中有两个数相同，或者对于每一个数 $k(k\ge 2)$，令所有模 $k$ 余 $i$ 的数在集合 $A_i$ 中。在 $a$ 序列中，如果满足 $A_0\sim A_{k-1}$ 所有集合的元素个数都大于等于 $2$，那么就不存在 $x$，且这是不存在 $x$ 的充分必要条件。

证明如下：**充分性**：

1. 如果有两个数相同，同上面尝试中的结论 $1$。
2. 如果对于一个数 $k$，满足 $A_0\sim A_{k-1}$ 中所有的元素个数都大于等于 $2$，那么不管你取得 $x$ 在哪一个集合中，都必然会有两个及以上的数是 $k$ 的倍数，他们的最大公因数就是 $k$。因此不存在 $x$。

**必要性**：

如果对于所有的 $k$ 都不满足这样的条件，那么我们就可以得到至少一组下面的式子。

要想使 $x$ 满足条件，则需要满足：

$$\begin{cases}
x \equiv y_1 \pmod {z_1}\\
x \equiv y_2 \pmod {z_2}\\
x\equiv y_3 \pmod {z_3}\\
\cdots\\
\end{cases}
$$

其中 $z_1,z_2,\cdots$ 分别是 $2,3,5,7,11,13$ 等质数。

现在就到了我们~~无比自豪~~的环节了。我国南宋时期伟大的数学家秦九韶，开创了“[中国剩余定理](https://oi-wiki.org/math/number-theory/crt/)”，就是解决此类问题的通法。篇幅限制，这里就不详细介绍了。

总之，对于这样的一个式子，是肯定有 $x$ 的解的。

证毕。

但是我们发现 $a_i$ 的范围很大，甚至到达了难以想象的 $10^{18}$，如果我们暴力枚举范围内的每一个质数那么铁定超时。但是我们又发现 $n$ 的范围很小，只有 $1000$。

想一想，如果要让所有的集合元素个数都大于等于 $2$，如果有 $n$ 个集合，那么元素个数就是 $2\times n$，已经超过了 $a$ 中元素个数 $n$。所以我们并不需要枚举这么多，只需要枚举到 $n$ 就可以了。如果你胆子比较大，实际上枚举到 $\dfrac{n}{2}$ 就可以了。这里直接枚举到了 $n$。

### 参考代码
本题的解题步骤：
1. 输入。
2. 枚举 $k=1\sim n$。
3. 对于 $a$ 中的每一个元素都去模一下 $k$。统计所有余数出现的次数。
4. 如果每一个余数出现次数都大于等于 $2$，那么循环终止，一定不存在 $x$。
5. 否则就肯定存在 $x$。

代码如下:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,a[100010],ji,ou,c[100010];
long long num1,num2,num3,num;
bool p;
int main(){
	cin>>t;
	while(t--){
		p=1;
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		sort(a+1,a+1+n);
		ji=0;ou=0;
		for(int i=1;i<=n-1;i++)	
			if(a[i]==a[i+1]){
				p=0;
				break; 
			}
		for(int i=1;i<=n;i++)
			if(a[i]%2==0)ou++;
			else ji++;
		if(ji>=2&&ou>=2)p=0;
		num1=0;num2=0;num3=0;
		for(int i=1;i<=n;i++)
			if(a[i]%3==1)num1++;
			else if(a[i]%3==2)num2++;
			else num3++;
		
		if(num1>=2&&num2>=2&&num3>=2)p=0; 
		for(int i=4;i<=n;i++){
			num=0;
			for(int j=0;j<=i+1;j++)
				c[j]=0;
			for(int j=1;j<=n;j++)
				c[a[j]%i]++;
			for(int j=0;j<=i-1;j++)
				if(c[j]>=2)num++;
			if(num==i){
				p=0;
				break;
			}
		}
		if(p)cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
}
```
题外话：祝大家新年快乐！

---

## 作者：Wi_Fi (赞：0)

注意到：若 $k$ 为质数，$a+x \equiv b+x \pmod k$，则无法满足题目所述结论。

因此，对于每一个质数 $k$，若存在 $a_i \equiv b_i \pmod k$，那么题目所求的 $x$ 要满足 $x \not\equiv k-a_i \% k$。

做法于是很显然：如果有两个数模 $k$ 同余，那么我们就将计数器加一（很显然 $k$ 减去余数与余数是一一对应的，方便起见直接标记余数），如果最后计数器的值恰等于 $k$，那么说明问题无解。

比如：若要求一个 $x$ 使得 $x \bmod 3 \neq 0$，$x \bmod 3 \neq 1$，$x \bmod 3 \neq 2$，那么问题显然是无解的。

需要特判一下一个显而易见的无解情况：若集合中存在两个数相同，那么不管 $x$ 为何值时，条件均不能满足，故无解。

最后还有一个无用的优化：$2$ 到 $59$ 之间的质数相乘就已经超过 $10^{18}$，因此枚举 $k$ 从 $2$ 枚举到 $59$ 即可。暴力绰绰有余。

```cpp
#include<bits/stdc++.h>

using namespace std;

long long T,i,n,cnt,a[105],sum[18][18],pri[18]={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59}; 
int main()
{
	cin>>T;
	while(T--)
	{
		int fl=0;
		memset(sum,0,sizeof sum);
		cin>>n;
		for(i=1;i<=n;i++)cin>>a[i];
		sort(a+1,a+n+1);
		for(i=1;i<n;i++)
		{
			if(a[i]==a[i+1])
			{
				fl=1;
				break;
			}
		}
		if(fl==1)
		{
			cout<<"NO\n";
			continue;
		}
		for(cnt=1;cnt<=17;cnt++)
		{
			int num=0;
			for(i=1;i<=n;i++)
			{
				sum[cnt][a[i]%pri[cnt]]++;
				if(sum[cnt][a[i]%pri[cnt]]==2)num++;
			}
			if(num==pri[cnt])
			{
				fl=1;
				cout<<"NO\n";
				break;
			}
		}
		if(fl==0)cout<<"YES\n";
	}
	return 0;
}

```


---

## 作者：Crazyouth (赞：0)

## 分析

不难发现，由于 $x>0$，所以当出现两个相同数的时候一定是 `NO`。再然后，发现对于一个数 $k$，记 $re_i$ 表示 $a$ 中模 $k$ 余 $i$ 的数的个数，若对于所有的 $0\le i<k$，都有 $re_i>1$，那么不管你加多少，必定有至少 $2$ 个 $k$ 的倍数，不互质，因此也是 `NO`。剩下的就是 `YES` 了。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
map<int,int> mp,cnt;
int a[110]; 
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		mp.clear();
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			mp[a[i]]++;
		}
		for(int i=1;i<=n;i++)
		{
			if(mp[a[i]]>1)
			{
				cout<<"NO"<<endl;
				goto E;
			}
		}
		for(int i=2;i<=n;i++)
		{
			cnt.clear();
			for(int j=1;j<=n;j++)
			{
				cnt[a[j]%i]++;
			}
			for(int j=0;j<i;j++)
			{
				if(cnt[j]<=1)
				{
					goto F;
				}
			}
			cout<<"NO"<<endl;
			goto E;
			F:;
		}
		cout<<"YES"<<endl;
		E:;
	}
	return 0;
}

---

## 作者：cosf (赞：0)

## [CF1770C](https://www.luogu.com.cn/problem/CF1770C)

一看到“中国剩余定理”，觉得好像没什么用。

确实没什么用，因为它只是用于证明正确性的。

我们先来考虑一下什么情况是一定不可能存在 $x$ 的。

从一个简单的例子出发：

$$
a = \{1, 2, 3, 4\}
$$

可以发现，无论是什么 $x$，加完之后的 $a$ 都一定会有两个偶数。

推广一下，假设存在 $i$，$\forall 0 \le j \lt i, |\{k | a_k \equiv j\pmod i\}| \ge 2$，则无论 $x$ 取多少，总会有两个数，它的 $\gcd \ge i$。

那么，如果不存在，则对于任意一个**质数** $p$，会存在一个 $j$，使得 $|\{k | a_k \equiv -j\pmod p\}|\lt 2$，则我们只需要求一个 $x$，使得 $x\equiv j\pmod p$ 即可。

这里用一下中国剩余定理，因为所有质数都是互质的，所以这样的 $x$ 一定存在。

那为什么不用考虑合数呢？这是因为，假设合数 $q = pC$，$p$ 是质数。如果连 $\gcd$ 是 $p$ 的倍数都取不到，那怎么可能去到 $\gcd$ 是 $q$ 的倍数呢？

关于我们要判断的质数 $p$ 的大小，$p \gt \frac{n}{2}$ 就完全没必要了。由抽屉原理可知，若 $p \gt \frac{n}{2}$，$|\{k | a_k \equiv -j\pmod p\}|\lt 2$ 的 $j$ 一定存在。

最终复杂度是 $O(tn^2)$，当然可以优化一下到$O(\frac{tn^2}{\ln n})$，没必要。

## 代码

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 105

using ll = long long;

int cnt[MAXN];

ll val[MAXN];

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		for (int i = 1; i <= n; i++)
		{
			cin >> val[i];
		}
		sort(val + 1, val + n + 1);
		if (unique(val + 1, val + n + 1) - val - 1 != n)
		{
			cout << "NO" << endl;
			continue;
		}
		bool e = true;
		for (int i = 2; i <= n; i++) // 这里枚举 i（文中的 p）的范围是放宽的。理论只需要 2 到 n/2 中的所有素数即可。
		{
			bool f = false;
			for (int j = 0; j < i; j++)
			{
				cnt[j] = 0;
			}
			for (int j = 1; j <= n; j++)
			{
				cnt[val[j] % i]++;
			}
			for (int j = 0; j < i; j++)
			{
				if (cnt[j] < 2)
				{
					f = true;
					break;
				}
			}
			if (f == false)
			{
				e = false;
				break;
			}
		}
		if (e)
		{
			cout << "YES" << endl;
		}
		else
		{
			cout << "NO" << endl;
		}
	}
}

```


---

## 作者：immix (赞：0)

## 题意概述
有 $n$ 个正整数的序列 $a$，问是否存在正整数 $x$，使得对原序列每个数加 $x$ 后两两互质。

## 题目分析

#### 条件1
首先，如果序列中有重复的数，不论加多少，重复的两个数一定不互质，故可以先将这种情况去除。

形式化地， $\exists 1\le i<j \le n $，使得 $a_i=a_j$，我们把其记作条件1。

#### 条件2
然后，我们对序列中的每一个数对某个大于等于 $2$ 的质数求余，并按余数分类。
我们假设序列为 $1 ,3, 4, 6, 8$，以对 $2$ 求余为例，可以列出如下表格：

| 余数 |    $a_i$    |
| :--: | :---------: |
|  $0$ | $4$ $6$ $8$ |
|  $1$ | $1$ $3$    |

可以看到，不论余数为几，都有两个以上的数。这时候，如果我们加的数为奇数，则余数为 $1$ 的数都可被 $2$ 整除，如果我们加的数为偶数，则余数为 $0$ 的数都可以被 $2$ 整除。故一定找不到一个 $x$，使所有数互质。

形式化地，定义集合为 $P=\{x|x\text{为素数}\}$， $\exists m \in P$, $\forall p \in \mathbb N,p<m$，都有 $\text{card}(\{x|x\in a_{i} \land x\bmod m=p\})\ge 2$。$\text{card}(S)$ 表示集合 $S$ 元素个数。 我们将其记作条件2。

#### 余下情况
由上文我们可以知道，任何一个满足条件1和条件2的序列一定找不到合法的 $x$，接下来，我们证明任何其他序列都存在合法的 $x$。

一个序列中任意两个数都互质，换句话说，就是不存在 $1\le i<j \le n ,m \in P $，使得 $a_i \bmod m =a_j \bmod m=0$。

既然序列不满足条件2，那么$\forall m \in P$，都存在 $k_m$，使得 $\text{card}(\{x|x\in a_{i} \land x\bmod m=k_m\})< 2$。

只要 $x$ 满足如下同余方程组

$$
\begin{cases}
x \equiv & m_1-k_{m_1} (\bmod\, m_1)\\
x \equiv &m_2-k_{m_2} (\bmod\, m_2)\\
  & \vdots\\
x \equiv &m_i-k_{m_i} (\bmod\, m_i)\\
\end{cases}$$

此时对任意 $m \in P$, 是 $m$ 的倍数的数的个数一定小于等于 $1$。所以任意数两两互质，就是一个合法解。由[中国剩余定理](https://oi-wiki.org/math/number-theory/crt/)，这样的同余方程一定有解。问题解决。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 105;

ll a[N];
int cnt[N];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        int n;
        scanf("%d",&n);
        for(int i=0;i<n;i++){
            scanf("%lld",a+i);
        }

        sort(a,a+n);
        for(int i=0;i<n-1;i++){
            if(a[i]==a[i+1]){
                goto end; // 满足了条件1
            }
        }        
        for(int i=2;i<=50;i++){ // *只需要对小于等于50的数计算余数
            memset(cnt,0,sizeof(cnt));
            for(int j=0;j<n;j++){
                cnt[a[j]%i]++;
            }
            bool ok = 0;
            for(int j=0;j<i;j++){
                if(cnt[j]<2){
                    ok = 1;
                    break;
                }
            }
            if(!ok)goto end; // 满足了条件2
        }
        // 既不满足条件1，也不满足条件2 有解
        puts("YES");continue;
        end:puts("NO");
    }
    return 0;
}
```
特别的，我们对于条件2的判定只需要对小于等于 $50$ 的数进行取余操作。因为对于大于 $50$ 的数，由于最多只有 $100$ 个数，不可能每个余数都多于两个数，条件2一定不成立。

时间复杂度 $O(n^2)$。

---

## 作者：郑朝曦zzx (赞：0)

## 题解

- 首先，如果序列有重复的数字，那么肯定不可以。

- 其次，把序列的每个数对某个常数取模，如果每个余数都有不少于两个，那么也不行。

举一个例子：

```cpp
2 4 9 11
```

这个样例的答案是 `NO`，因为我们把每个数对 $2$ 取模，得到余数数列

```cpp
0 0 1 1
```

如果我们加入的 $x$ 对 $2$ 取余余数为 $0$，那么 $\gcd(2 + x, 4 + x) > 1$

如果 $x \bmod 2 = 1$ 那么就会出现 $\gcd(9 + x, 11 + x) > 1$

综上，这个样例无解。

总结一下，只要找到一个模数，使得其每余数都会出现冲突（个数不少于 $2$）就会出现无解。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define Test int t; t = read(); while (t--)
typedef long long LL;
inline int read()
{
    char c=getchar(); int x=0, s=1;
    while(c<'0'||c>'9') { if(c=='-')s=-1;c=getchar();}
    while(c>='0'&&c<= '9') { x=(x<<3)+(x<<1)+c-'0';c=getchar();}
    return x*s;
}
inline void write(int x)
{
	if (x < 0) { putchar('-'); x *= -1; }
	int tmp[20], top = 0;
	do{ tmp[++top] = x % 10; x /= 10; } while(x);
	while (top) putchar(tmp[top--] + 48);
}
inline void fastInp()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
int n, a[110], mod[110];
bool check()
{
	n = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	sort(a + 1, a + n + 1);
	for (int i = 2; i <= n; ++i) if (a[i] == a[i - 1]) return 0;
	for (int i = 2; i <= n / 2; ++i)
	{
		memset(mod, 0, sizeof(mod));
		for (int j = 1; j <= n; ++j)
			mod[a[j] % i]++;
		int mn = 100000;
		for (int j = 0; j < i; ++j)
			mn = min(mn, mod[j]);
		if (mn >= 2) return 0;
	}
	return 1;
}
signed main()
{
	Test
	{
		if (check()) printf("YES\n");
		else printf("NO\n");
	}
    return 0;
}
```


---

## 作者：aimcf (赞：0)

结论题。

对于数 $k$ 而言，如果对于每一个 $0\sim k-1$ 的数 $p$，都存在至少两个满足 $k\bmod p=0$，那么容易发现不管 $x$ 取何值，都会出现至少两个数满足 $a_i\bmod p = 0$。

由于 $n\le 100$，并且对于一个 $p$ 至少需要 $2\times p$ 个数才可以达到上面的条件，所以只需要从 $2$ 枚举到 $50$ 即可。

---

