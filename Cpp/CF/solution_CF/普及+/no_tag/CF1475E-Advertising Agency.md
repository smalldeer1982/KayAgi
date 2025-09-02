# Advertising Agency

## 题目描述

Masha works in an advertising agency. In order to promote the new brand, she wants to conclude contracts with some bloggers. In total, Masha has connections of $ n $ different bloggers. Blogger numbered $ i $ has $ a_i $ followers.

Since Masha has a limited budget, she can only sign a contract with $ k $ different bloggers. Of course, Masha wants her ad to be seen by as many people as possible. Therefore, she must hire bloggers with the maximum total number of followers.

Help her, find the number of ways to select $ k $ bloggers so that the total number of their followers is maximum possible. Two ways are considered different if there is at least one blogger in the first way, which is not in the second way. Masha believes that all bloggers have different followers (that is, there is no follower who would follow two different bloggers).

For example, if $ n=4 $ , $ k=3 $ , $ a=[1, 3, 1, 2] $ , then Masha has two ways to select $ 3 $ bloggers with the maximum total number of followers:

- conclude contracts with bloggers with numbers $ 1 $ , $ 2 $ and $ 4 $ . In this case, the number of followers will be equal to $ a_1 + a_2 + a_4 = 6 $ .
- conclude contracts with bloggers with numbers $ 2 $ , $ 3 $ and $ 4 $ . In this case, the number of followers will be equal to $ a_2 + a_3 + a_4 = 6 $ .

Since the answer can be quite large, output it modulo $ 10^9+7 $ .

## 说明/提示

The test case is explained in the statements.

In the second test case, the following ways are valid:

- conclude contracts with bloggers with numbers $ 1 $ and $ 2 $ . In this case, the number of followers will be equal to $ a_1 + a_2 = 2 $ ;
- conclude contracts with bloggers with numbers $ 1 $ and $ 3 $ . In this case, the number of followers will be equal to $ a_1 + a_3 = 2 $ ;
- conclude contracts with bloggers with numbers $ 1 $ and $ 4 $ . In this case, the number of followers will be equal to $ a_1 + a_4 = 2 $ ;
- conclude contracts with bloggers with numbers $ 2 $ and $ 3 $ . In this case, the number of followers will be equal to $ a_2 + a_3 = 2 $ ;
- conclude contracts with bloggers with numbers $ 2 $ and $ 4 $ . In this case, the number of followers will be equal to $ a_2 + a_4 = 2 $ ;
- conclude contracts with bloggers with numbers $ 3 $ and $ 4 $ . In this case, the number of followers will be equal to $ a_3 + a_4 = 2 $ .

In the third test case, the following ways are valid:

- concludes a contract with a blogger with the number $ 2 $ . In this case, the number of followers will be equal to $ a_2 = 2 $ .

## 样例 #1

### 输入

```
3
4 3
1 3 1 2
4 2
1 1 1 1
2 1
1 2```

### 输出

```
2
6
1```

# 题解

## 作者：Carotrl (赞：4)

非常简单的E题，甚至比D还简单。

### 简单题意：

有 $n$ 个数 $a_{1,2,...n}$。要选出和最大的 $k$ 个数，请问有多少种选法。

### 大致做法：

由于数据很小，所以怎么乱搞都能过。这里只提供一种简单的想法。

要求和最大的 $k$ 个数，显然可以先对 $a$ 数组从大到小进行排序，选前 $k$ 个数即可。

为什么会出现多种情况呢？因为最后几个加进去的数可能有许多不同的选法。

然后开一个桶记录每一个数出现的个数。从大到小（由于题目保证 $1\le a_i \le n$，所以直接从 $n$ 到 $1$）遍历每一个数。如果这个数全部选进还不到 $k$ 个，就继续选。否则假设这个数一共有 $m$ 种选择方案（即这个数有 $m$ 个），但只能选 $p$ 个，显然答案为 $\tbinom{m}{p}$ 。

范围很小，杨辉三角预处理组合数即可。

### code:

```cpp
#include<cstdio>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<iostream>
#include<string>
#include<cmath>
#include<cstring>
#define N 1000000007
using namespace std;
int n,m,a[1005],t,b[1005];
long long ans=0,c[1005][1005];
bool cmp(int a,int b){
	return a>b;
}
int main(){
	scanf("%d",&t);
	for(int i=1;i<=1000;i++){
		for(int j=0;j<=i;j++){
			if(i==j||j==0)c[i][j]=1;
			else c[i][j]=(c[i-1][j-1]+c[i-1][j])%N;
		}
	}
	while(t--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		sort(a+1,a+1+n,cmp);
		memset(b,0,sizeof b);
		for(int i=1;i<=n;i++)b[a[i]]++;
		int sum=0;
		for(int i=n;i>=1;i--){
			if(sum+b[i]<m)sum+=b[i];
			else{
			    int k=m-sum;
			    k=min(k,b[i]-k);
				ans=c[b[i]][k];	
				break; 
			}
		}
		printf("%lld\n",ans);
	}
} 
```


---

## 作者：Ryo_Yamada (赞：2)

> 有 $n$ 个博主，其中第 $i$ 个有 $a_i$ 个粉丝。你需要选出 $k$ 个，使得他们的粉丝总数最多。问有多少种选法，答案对 $10^9+7$ 取模。

$1 \leq a_i \leq n$，可以记录拥有 $x$ 个粉丝的博主数量。需要总数最多一定是从大向小选。当我们发现 $cnt_x \geq k$ 时，答案即为 $C^k_{cnt_x} \mod (10^9+7)$。

P.S. 刚开始没看到数据范围导致我写了个 Lucas。。。如果有看不懂我的代码的可以移步 [P3807](https://www.luogu.com.cn/problem/P3807)。

P.P.S. 我又看错模数了，写了个 $998244353$，罚时 $+10$。。。

$\text{Code}$：

```cpp
#define W(M) while(M--)

const int N = 1005;
const int p = 1e9 + 7;

int cnt[N], k[N];
ll v[N];
 
ll Cp(ll n, ll m) {
	if(m > n) return 0;
	return ((v[n] * qpow(p - 2, v[m], p)) % p * qpow(p - 2, v[n - m], p) % p);	
}
 
ll Lucas(ll n, ll m) {
	if(!m) return 1;
	return Cp(n % p, m % p) * Lucas(n / p, m / p) % p;	
}
// 卢卡斯定理，求出 C^m_n 的值。

int main() {
	int T; cin >> T;
	v[0] = 1;
	rep(i, 1, 1000) v[i] = (v[i - 1] * i) % p;
	W(T) {
		memset(cnt, 0, sizeof cnt);
		int n, m;
		qread(n, m);
		QreadArr(k + 1, k + n + 1); //自己定义的函数，读入 k[1] 到 k[n]
		rep(i, 1, n) ++cnt[k[i]];
		per(i, n, 0) {
			if(cnt[i] >= m) {
				printf("%lld\n", Lucas(cnt[i], m));
				break;
			}
			else m -= cnt[i];
		}
	}
 	return 0;
}
```


---

## 作者：Cutest_Junior (赞：1)

## 题解 CF1475E 【Advertising Agency】

### 题意

+ $n$ 个数 $a$，求选出 $k$ 个数使其总和最大的方案数；
+ 多组数据，$n,k,a_i\le1000$，结果对 $10^9+7$ 取模。

### 做法

总和最大，显然是要让最大的 $k$ 个数被选，因为有的数出现了多次，才有了多种方案。

继续观察，设 $b$ 为 $a$ 中第 $k$ 大的数，比 $b$ 大的数必选，比 $b$ 小的数必不选，答案就是 $C_\text{a 中等于 b 的个数}^\text{k-（a 中大于 b 的数的个数）}$。

数学题。

---

Virtual participation 时把

```cpp
nth_element(arr + 1, arr + k, arr + n + 1, greater<int>());
```

打成

```cpp
nth_element(arr + 1, arr + k + 1, arr + n + 1, greater<int>());
```

当场暴毙。

### 代码

```cpp
#include <cstdio>
#include <iterator>
#include <algorithm>
 
using namespace std;
 
typedef long long ll;
 
const int mod = 1e9 + 7;
 
const int N = 1005;
 
int arr[N];
 
void exgcd(int a, int b, ll &x, ll &y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return;
	}
	exgcd(b, a % b, y, x);
	y -= a / b * x;
}
 
int inv(int a, int b = mod) {
	ll x, y;
	exgcd(a, b, x, y);
	return (x % b + b) % b;
}
 
int f(int x) {
	int ans = 1;
	for (int i = 1; i <= x; ++i) {
		ans = (ll)ans * i % mod;
	}
	return ans;
}
 
void run() {
	int n, k;
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &arr[i]);
	}
	nth_element(arr + 1, arr + k, arr + n + 1, greater<int>());
	int cnt1 = 0, cnt2 = k;
	for (int i = 1; i <= n; ++i) {
		if (arr[i] == arr[k]) {
			++cnt1;
		}
		if (arr[i] > arr[k]) {
			--cnt2;
		}
	}
//	printf("%d %d %d  ", cnt1, cnt2, f(cnt1 - cnt2));
	printf("%lld\n", (ll)f(cnt1) * inv(f(cnt2)) % mod * inv(f(cnt1 - cnt2)) % mod);
}
 
int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		run();
	}
}
```

---

## 作者：Иɔlɔ (赞：1)

看到题解里没有逆元的解法，来发一个

> 有 $n$ 个博主，其中第 $i$ 个有 $a_i$ 个粉丝。你需要选出 $k$ 个，使得他们的粉丝总数最多。问有多少种选法，答案对 $10^9+7$ 取模。

记录拥有 $x$ 个粉丝的博主数量，从 $n$ 个粉丝到 $1$ 个枚举，每次若 $cnt_i < k$ 则 $k$ 减去 $cnt_i$（全部选），否则 $C_{cnt_i}^k$ 即为答案。

相信大家都会 $C_m^n$ 的求法，但是当我们有模数的时候，就不能直接使用朴素求法了。我们有三种方法：Lucas，dp 和逆元。如果不知道什么是乘法逆元的，可以移步 [P3811](https://www.luogu.com.cn/problem/P3811)。一个数模 $p$ 意义下的乘法逆元指：假设这个数是 $x$，它的模 $p$ 意义下的是乘法逆元 $y$。那么对于任何数 $k$，$\dfrac{k}{x} \mod p = k \times y \mod p$。一种求法：$y = x^{p-2} \mod p$。

$\text{Code}$：

```cpp

inline ll qpow(ll n, ll base, ll mod = 1e18) {
	ll ret = 1;
	while(n) {
		if(n & 1) ret = ret * base % mod;
		base = base * base % mod;
		n >>= 1;
	}
	return ret % mod;
}

const int N = 1005;
const int p = 1e9 + 7;

int cnt[N], k[N];
ll ans = 1;

int main() {
	int T; cin >> T;
	W(T) { // while(T--)
		ans = 1;
		memset(cnt, 0, sizeof cnt);
		int n, m;
		qread(n, m);
		QreadArr(k + 1, k + n + 1); // 读入 k[1]~k[n]
		rep(i, 1, n) ++cnt[k[i]]; //宏定义： for(int i = 1; i <= n; i++) 
		per(i, n, 0) { //宏定义： for(int i = n; i >= 0; i--)
			if(cnt[i] >= m) {
				per(j, cnt[i], cnt[i] - m + 1) (ans *= j) %= p;
				rep(j, 2, m) (ans *= qpow(p - 2, j, p)) %= p;
				printf("%lld\n", ans);
				break;
			}
			else m -= cnt[i];
		}
	}
 	return 0;
}
```

时间复杂度 $O(Tn \log p)$。目前是最优解。

---

## 作者：冰糖鸽子 (赞：1)

~~不小心写成排列数了/dk~~

个人感觉这道题放在B或C比较好（但是这是Div 3啊这又有什么区别呢）

----

题意：

> 有一个长度为 $n$ 的数列 $a$ ，现在要从中取 $m$ 个数，求有多少种取法取出来的数的和是最大值

先看如何求最大值，很明显有一个简单贪心：将数组从大到小排序，取前 $m$ 个数，比如样例 `1 3 1 2` 中选 $3$ 个数的最大值就是 $3 + 2 + 1 = 6$

接下来看个数，考虑每种数字取几个，在上面的例子中，$3$ 和 $2$ 要全部选上（虽然两个数都只有一个），$1$ 则有一些不一样，因为 $1$ 有两个，而我们只需要选一个。

问题转化成了从 $x$ 个不同元素中选 $y$ 个，很裸的组合数，那组合数怎么求呢？题解里某个机智的大佬想到了 $\operatorname{Lucas}$ ，但我们注意到 $n$ 的总和只有 $1000$， $n^2$ 的杨辉三角递推绰绰有余。

问题差不多解决完了，剩下一点小细节例如取模，初始化这些，不再多说。

代码：

```cpp

// Problem: CF1475E Advertising Agency
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1475E
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>
using namespace std;
#define int long long
const int p=1e9+7;
#define M 1005
int T,n,m,a[M],f,cnt,c[M][M],cnt2,ans;
bool cmp(int a,int b)
{
	return a>b;
}
void Reset()
{
	cnt=cnt2=0;ans=f=1;	
}
void Re()
{
	c[0][0]=1;
	for(int i=1;i<=1000;i++)
	{
		c[i][0]=1;
		for(int j=1;j<=i;j++)
		{
			c[i][j]=c[i-1][j]+c[i-1][j-1];
			c[i][j]%=p;
		}
	}
}
signed main()
{
	cin>>T;
	Re();
	while(T--)
	{
		Reset();
		cin>>n>>m;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		sort(a+1,a+1+n,cmp);
		for(int i=1;i<=n;i++)
		{
			if(a[i]==a[m])
			{
				cnt++;
			}
			if(a[i]==a[m]&&i<=m)
			{
				cnt2++;
			}
		}
		cout<<c[cnt][cnt-cnt2]<<endl;
	}
	return 0;
}
```

---

## 作者：sochiji (赞：1)

## 题目大意

现有$n$个博主，第$i$个博主有$a_i$个粉丝，不同博主的粉丝没有重叠。广告公司要从这些博主中选择$k$个来签约，并让他们向自己的粉丝播放广告，要求收到广告的粉丝尽可能地多。

问有多少种不同的签约选法。

## 分析

题面描述中有个很重要的信息：不同博主的粉丝没有重叠。

这说明能收到广告的粉丝数为**所有签约博主的粉丝数之和**。

记签约的博主组成的集合为$S$，要使$\displaystyle \sum_{i\in S}a_i$最大化，我们需要设计贪心策略：优先签约粉丝多的博主。

### 如何计算方案数

需要计算方案数吗？是的！因为在这种贪心策略下选择方案不是唯一的！

#### 举个栗子

$n=7,\quad k=5$  
$\{a_i\}=[1,2,1,3,1,2,1]$

根据贪心策略，先选择第4个博主，这一步的选法是唯一的；  
再选择第2和第6个博主，这一步的选法也是唯一的；  
还剩下4个博主可选，他们粉丝数相同，要从中签约2个，有${4 \choose 2}=6$种选法。  
于是答案就是6。

### 一般地

1. 在程序中，设上文中的$k$为变量；
2. 计算未被选择的博主中有多少博主**并列粉丝最多且相等**，记这个数量为$c$；
3. 判断$c$与$k$的关系  
    - 若有$c\leq k$，则这一步选法唯一，令$k\leftarrow k-c$；
    - 否则有$c>k$，则这一步选法不唯一，有${c \choose k}$种选法；
4. 重复第2至3步，直到选完。

## 程序实现

1. 单个测试点中包含较多提问，可以先将组合数计算好放在数组里备用。

2. 考虑到问题的数据范围$1\leq k\leq n\leq 1000$非常小，我们可以用数组计数来实现，这样会优化上面第2步的时间复杂度至$O(1)$。

#### 代码

```c++
#include <cstdio>
#include <cstring>
using namespace std;
const int MODNUM = 1000000007;
int t;
int rec[1010];

int comb[1010][1010];

/**
 * 初始化组合数存储 
 */
void initial_comb(int max_border)
{
    comb[0][0] = 1;
    for (int i = 1; i <= max_border; i++)
    {
        comb[i][0] = 1;
        for (int j = 1; j <= i; j++)
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % MODNUM;
    }
}

int main()
{
    scanf("%d", &t);
    initial_comb(1010);
    for (int i = 1; i <= t; i++)
    {
        memset(rec, 0, sizeof(rec));
        int n, k;
        scanf("%d%d", &n, &k);
        for (int j = 1; j <= n; j++)
        {
            int tmp;
            scanf("%d", &tmp);
            rec[tmp]++;
        }
        for (int j = n; j > 0; j--)
            if (rec[j] < k)
                k -= rec[j];
            else
            {
                printf("%d\n", comb[rec[j]][k]);
                break;
            }
    }
    return 0;
}

```

---

## 作者：Untitled10032 (赞：0)

__大致思路：__

把所有输入排序，按粉丝数从大到小选取博主，若即将选取完毕时，除去已选博主，剩下粉丝数并列第一的博主数量大于剩下的名额时，才会出现多种选法，可以通过组合数计算。

设即将选取完毕时，除去已选博主，粉丝数并列第一的博主数量为 $x$，设还剩下的名额数量为 $r$。

则最后答案为 $C_x^r$。

本题数据范围较小，排序可以选择桶排（计数排序）。

```cpp
//cnt[]:存输入的桶子。
//now:从大往小考虑，现在已经选了多少个博主。
//C():组合数函数。
//k:同题目描述。
//dalta:最后还剩多少名额。

//省略了输入与处理多测的代码。（记得每次把桶子清空）

int now = 0;
for (int i = 1000; i > 0; i--) {
    if (cnt[i] == 0)    continue;
    now += cnt[i];
    if (now == k) {
        cout << "1\n";
        break;
    } else if (now > k) {
        now -= cnt[i];
        const int delta = k - now;
        cout << C(cnt[i], delta) << '\n';
        break;
    }
}
```

__组合数计算问题：__

本题时间比较充裕，可以不采用预处理等优化。

组合数的计算公式为 $C_n^m = \frac{n!}{m!(n - m)!}$，将分母部分转换为逆元，之后直接计算即可。

```cpp
//factorial():计算阶乘函数。
//inverse():计算逆元函数。
//C() 中 total 为上文中 n，selected 为上文中 m。

inline long long C(const int total, const int selected) {
    return ((long long)factorial(total) * inverse(factorial(selected) * factorial(total - selected) % MOD) % MOD + MOD) % MOD;
}
```

使用费马小定理计算逆元，$inv(x) = x^{p - 2} (mod\ p)$。乘方运算使用快速幂。

```cpp
//base:底数，exponent:指数
inline long long fastPow(long long base, int exponent) {
    long long res = 1;
    while (exponent != 0) {
        if (exponent & 1) {
            res = res * base % MOD;
            exponent ^= 1;
        }
        base = base * base % MOD;
        exponent >>= 1;
    }
    return res;
}
inline long long factorial(long long x) {
    long long res = x;
    while (--x)
        res = res * x % MOD;
    return res;
}
```

__完整代码：__

```cpp
#include <iostream>
#include <cstring>
using namespace std;
constexpr int MOD = 1e9 + 7;
int cnt[1005];
inline long long fastPow(long long base, int exponent) {
    long long res = 1;
    while (exponent != 0) {
        if (exponent & 1) {
            res = res * base % MOD;
            exponent ^= 1;
        }
        base = base * base % MOD;
        exponent >>= 1;
    }
    return res;
}
inline long long factorial(long long x) {
    long long res = x;
    while (--x)
        res = res * x % MOD;
    return res;
}
inline long long inverse(long long x) {
    return fastPow(x, MOD - 2);
}
inline long long C(const int total, const int selected) {
    return ((long long)factorial(total) * inverse(factorial(selected) * factorial(total - selected) % MOD) % MOD + MOD) % MOD;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;
    for (++t; --t;) {
        memset(cnt, 0, sizeof(cnt));
        int n, k;
        cin >> n >> k;
        for (int i = 0, tmp; i < n; i++) {
            cin >> tmp;
            cnt[tmp]++;
        }
        int now = 0;
        for (int i = 1000; i > 0; i--) {
            if (cnt[i] == 0)    continue;
            now += cnt[i];
            if (now == k) {
                cout << "1\n";
                break;
            } else if (now > k) {
                now -= cnt[i];
                const int delta = k - now;
                cout << C(cnt[i], delta) << '\n';
                break;
            }
        }
    }
    return 0;
}
```


---

## 作者：EDqwq (赞：0)

还是比较简单的题。

首先，我们可以发现一个非常重要的事情！

构成最多的粉丝总数的被选择的数，一定是不变的。

并且，有且仅有一个数，他可以从其他的同样的数里面选不同的，简单点讲，也就是其他的数都被选满了，而这个数没有被选满。

所以只有这个数，决定了整个的答案，而这个答案是多少呢？

设需要选择这种数 $x$ 个，总共有 $sum$ 个，答案就是：

$$C_{sum}^{x}$$

所以开个桶存每个数的个数，然后由于值域很小，直接从 $n$ 开始枚举值，剩下的不足这个值的个数的时候记录答案。

然后，由于这个题要算的组合数还是蛮大的，所以暴力逆元取模会炸，于是我们有一种很好的预处理方式：杨辉三角。具体组合数和杨辉三角的关系，可以百度学习。

***

```cpp
#include<bits/stdc++.h>

#define int long long
#define mem(x,y) memset(x,y,sizeof(x))
#define mod 1000000007

using namespace std;

int read(){
   int s = 0,w = 1;
   char ch = getchar();
   while(ch < '0' || ch > '9'){if(ch == '-')w = -1;ch = getchar();}
   while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
   return s * w;
}

int t;
int n,m;
int a[1000010];
int all;
int cnt[1010];
int ans = 1;
int dp[1010][1010];

bool cmp(int x,int y){
	return x > y;
}

signed main(){
	for(int i = 0;i <= 1000;i ++){
        for(int j = 0;j <= i;j ++){
            if(j == 0 || i == j)dp[i][j] = 1;
            else dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % mod;
        }
    }
    dp[0][0]=0;
	cin>>t;
	while(t --){
		ans = 1;
		mem(cnt,0);
		n = read(),m = read();
		for(int i = 1;i <= n;i ++)a[i] = read(),cnt[a[i]] ++;
		for(int i = n;i >= 1;i --){
			if(!cnt[i])continue;
			if(m - cnt[i] > 0)m -= cnt[i];
			else {
				ans = dp[cnt[i]][m];
				break;
			}
		}
		cout<<ans<<endl;
	}
}
```

---

## 作者：KSToki (赞：0)

# 题目大意
有 $n$ 个数，从中选出 $k$ 个使它们的和最大，问方案数，对 $10^9+7$ 取模。
# 题目分析
显然选择前 $k$ 大的数，不同的方案仅仅是其中最小的那个数的区别。设这个数为 $x$，那么如果共有 $a$ 需要 $b$ 个 $x$，答案就为 $C(a,b)$。

由于 $n$ 很小，随便怎么搞都可以，这里提供一种较通用的解法。先 `sort` 一遍是显然的，然后对 $a[n-k+1]$ 进行 `lower_bound` 和 `upper_bound`，这样我们直接可以解决 $a$ 在 `long long` 范围内的。用快速幂求逆元，组合数直接求即可，复杂度 $O(nlogn)$，常数小，CF的机子又快，$n$ 甚至可以开到 $10^6$。

预处理组合数没多大必要，复杂度是 $O(n^2+nlogn)$。但是如果没有 $\sum n$ 的限制，就可以通过预处理、开桶和 `nth_element` 达到 $O(n^2+Tn)$ 的复杂度。这带个 log 也不好卡。
# 代码
代码用第一种方式实现。
```cpp
#include<bits/stdc++.h>
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define LL __int128
#define db double
using namespace std;
#define pii pair<int,int>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first.first
#define se first.second
#define th second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define inf (0x7fffffff)
#define INF (1e18)
#define eps (1e-8)
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int T,n,k,a[1001];
const int Mod=1e9+7;
I int ksm(int x,int y)
{
	int res=1;
	while(y)
	{
		if(y&1)
			res=(ll)res*x%Mod;
		x=(ll)x*x%Mod;
		y>>=1;
	}
	return res;
}
I int C(int x,int y)
{
	int res=1;
	for(R int i=x;i>x-y;--i)
		res=(ll)res*i%Mod;
	for(R int i=y;i;--i)
		res=(ll)res*ksm(i,Mod-2)%Mod;
	return res;
}
int main()
{
    T=read();
    while(T--)
    {
    	n=read();
    	k=read();
    	for(R int i=1;i<=n;++i)
    		a[i]=read();
    	sort(a+1,a+n+1);
    	int pos=n-k+1;
    	int pos1=lower_bound(a+1,a+n+1,a[pos])-a,pos2=upper_bound(a+1,a+n+1,a[pos])-a;
    	putint(C(pos2-pos1,pos2-pos));
	}
    return 0;
}
```


---

## 作者：do_while_true (赞：0)

# [E](https://codeforces.com/contest/1475/problem/E)

### $\mathcal{Translate}$

给定长度为 $n$ 的序列 $a$，选出 $k$ 个数使得他们的和最大，求一共有多少种选择方案。对 $10^9+7$ 取模。

$1\leq k\leq n\leq 1000,1\leq a_i\leq n$

### $\mathcal{Solution}$

从大到小选肯定是更优的，那么可能变换的只有选到的最小的那个，也就是第 $k$ 大的数，计第 $k$ 大的数共有 $cnt$ 个，前 $(k-1)$ 大的数共有 $sum$ 个。

根据组合数学基本知识可得方案数为 $C_{cnt}^{k-sum}$

### [$\mathcal{Code}$](https://codeforces.com/contest/1475/submission/105837368)

---

