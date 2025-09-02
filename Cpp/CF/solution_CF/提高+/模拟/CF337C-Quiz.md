# Quiz

## 题目描述

Manao is taking part in a quiz. The quiz consists of $ n $ consecutive questions. A correct answer gives one point to the player. The game also has a counter of consecutive correct answers. When the player answers a question correctly, the number on this counter increases by 1. If the player answers a question incorrectly, the counter is reset, that is, the number on it reduces to 0. If after an answer the counter reaches the number $ k $ , then it is reset, and the player's score is doubled. Note that in this case, first 1 point is added to the player's score, and then the total score is doubled. At the beginning of the game, both the player's score and the counter of consecutive correct answers are set to zero.

Manao remembers that he has answered exactly $ m $ questions correctly. But he does not remember the order in which the questions came. He's trying to figure out what his minimum score may be. Help him and compute the remainder of the corresponding number after division by $ 1000000009 $ $ (10^{9}+9) $ .

## 说明/提示

Sample 1. Manao answered 3 questions out of 5, and his score would double for each two consecutive correct answers. If Manao had answered the first, third and fifth questions, he would have scored as much as 3 points.

Sample 2. Now Manao answered 4 questions. The minimum possible score is obtained when the only wrong answer is to the question 4.

Also note that you are asked to minimize the score and not the remainder of the score modulo $ 1000000009 $ . For example, if Manao could obtain either $ 2000000000 $ or $ 2000000020 $ points, the answer is $ 2000000000 mod 1000000009 $ , even though $ 2000000020 mod 1000000009 $ is a smaller number.

## 样例 #1

### 输入

```
5 3 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5 4 2
```

### 输出

```
6
```

# 题解

## 作者：ZMQ_Ink6556 (赞：3)

## CF337C Quiz 题解
### 解题思路
我们可以使用**贪心**的思路，先求出必须使用多少次翻倍，再尝试将每次翻倍放到尽量靠前的位置，保证每次翻倍得到的分数最少。

- 求翻倍次数：$\lfloor\frac{k}{n}\rfloor-(n-m)$。这时要注意这个值可能是负数，如果是负数或者 $0$ 就代表不需要翻倍。
- 翻倍操作：$(\text{答案}+k)\times2\to\text{答案}$，此时需要同时让 $m$ 减少 $k$。

### 错误代码 $1$
```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
long long n , m , k , ans , need;
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> k;
	if(m == 0)
	{
		cout << "0";
		return 0;
	}
	if(m == 1)
	{
		if(k == 1)
		{
			cout << "2";
		}
		else
		{
			cout << "1";
		}
		return 0;
	}
	need = max((n / k) - (n - m) , 0ll);
	while(need--)
	{
		ans = ((ans + k) * 2) % 1000000009;
		m -= k;
	}
	cout << (ans + m) % 1000000009;
	return 0;
}
```

开开心心打完代码，发现：

![TLE](https://cdn.luogu.com.cn/upload/image_hosting/oxjutclo.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

### 优化

这时是我们没有考虑极端数据对整个 **while** 循环的影响。在 $\#6$ 中，这段 **while** 要跑整整 $4\times10^8$ 次！

我们发现，经过化简后，这段循环可以成为一段求指数幂的代码，就可以非常方便的用**快速幂**求解，复杂度 $O(\log m)$。

在此放上快速幂模板:
```cpp
int ksm(int a , int b)
{
	int cnt = 1;
	while(b)
	{
		if(b % 2 == 1)
		{
			ans = (a * ans) % p;
		}
		a = (a * a) % p;
		b /= 2;
	}
	return cnt;
}
```

### 错误代码 $2$
```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
long long n , m , k , ans , need;
int ksm(int a , int b)
{
	int cnt = 1;
	while(b)
	{
		if(b % 2 == 1)
		{
			cnt = (cnt * a);
			cnt %= 1000000009;
		}
		a = (a * a) % 1000000009;
		b /= 2;
	}
	return cnt;
}
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> k;
	if(m == 0)
	{
		cout << "0";
		return 0;
	}
	if(m == 1)
	{
		if(k == 1)
		{
			cout << "2";
		}
		else
		{
			cout << "1";
		}
		return 0;
	}
	need = max((n / k) - (n - m) , 0ll);
	cout << (k * 2 * (ksm(2 , need) - 1) + m - need * k) % 1000000009;
	return 0;
}
```

结果......

![WA](https://cdn.luogu.com.cn/upload/image_hosting/ym6ezg83.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

### 重要提示

**这道题一定要开** $\texttt{long long}$**！**

### 参考代码
```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
long long n , m , k , ans , need;
long long ksm(long long a , long long b)
{
	long long cnt = 1;
	while(b)
	{
		if(b % 2 == 1)
		{
			cnt = (cnt * a);
			cnt %= 1000000009;
		}
		a = (a * a) % 1000000009;
		b /= 2;
	}
	return cnt;
}
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> k;
	if(m == 0)
	{
		cout << "0";
		return 0;
	}
	if(m == 1)
	{
		if(k == 1)
		{
			cout << "2";
		}
		else
		{
			cout << "1";
		}
		return 0;
	}
	need = max((n / k) - (n - m) , 0ll);
	cout << (k * 2 * (ksm(2 , need) - 1) + m - need * k) % 1000000009;
	return 0;
}
```
这是我有史以来写的写的最长的一篇题解，感谢浏览。

---

## 作者：WorldMachine (赞：1)

### Solution

首先求出必须翻倍的次数，为 $x=\left\lfloor\dfrac{n}{k}\right\rfloor-(n-m)$。当然这个值可能是负数或 $0$，就说明不用翻倍。

设第 $i$​ 次翻倍后的分数为 $f_i$​，则有递推式 $f_i=2(f_{i-1}+k)$​，其通项公式为 $f_i=k(2^{i+1}-2)$​，直接上快速幂即可。

最后记得加上剩下零散的分数。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int p = 1000000009;
int qpow(int a, int b) {
	int c = 1;
	while (b) {
		if (b & 1) c = (ll)c * a % p;
		a = (ll)a * a % p, b >>= 1;
	}
	return c;
}
int n, m, k, x;
int main() {
	scanf("%d%d%d", &n, &m, &k);
	x = max(n / k - n + m, 0);
	printf("%lld\n", (((ll)k * (qpow(2, x + 1) - 2) + m - x * k) % p + p) % p);
}
```

---

## 作者：Lithium_Chestnut (赞：0)

挺不错的一道题目。我们考虑贪心，首先一定是每隔一个空连着放 $k-1$ 个正确答案，看看能不能放得下。那么放不下的情况我们在一个一个空填进去。举个例子：

> $n=9,m=8,k=3$；
> 
> 先每隔一个放：`1 1 0 1 1 0 1 1 0`；
> 
> 发现只放得下 $6$ 个数，所以我们找到第一个和第二个 `0` 把他填进去，变成：`1 1 1 1 1 1 1 1 0`；
> 
> 不难发现这就是最优解。

接下来是算贡献的方案。

不难发现我们先按照每隔一个放下来的数目就是 $\dfrac{n}{k}\times (k-1)+n%k$，如果这个数 $\geq m$，那么我们直接输出 $m$ 即可。

那么下面是放不下的方案，首先由于连着 $k$ 个就会使当前贡献翻倍，那么我们不妨推一下：

> $1\times k$ 的贡献为 $2\times k=k\times 2^1$；
> 
> $2\times k$ 的贡献为 $2\times(2\times k+k)=k\times (2^1+2^2)$；
> 
> $3\times k$ 的贡献为 $2\times(2\times(2\times k+k)+k)=k\times (2^1+2^2+2^3)$。

可得到 $n\times k$ 的贡献为 $k\times (2^1+2^2+\cdots +2^{n-1}+2^n)$，根据等比数列求和公式，$2^1+2^2+\cdots +2^{n-1}+2^n=2^{n+1}-2$，所以前面部分联通的贡献就为 $k\times (2^{i+1}-2)$，其中 $i$ 为联通的区域个数。

那么最后再加上连通区域以外的答案个数 $m-i\times k$ 即可。

```cpp
#include<bits/stdc++.h>
#define Std_Maker lhm
#define ll long long
using namespace std;
const int mod=1e9+9;
ll n,m,k,sum,i,ans;
ll qpow(ll a,ll b)
{
	ll res=1;
	while(b)
	{
		if(b&1) res=res*a%mod;
		b>>=1;
		a=a*a%mod;
	}
	return res;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>k;
	sum=n/k*(k-1)+n%k;
	if(sum>=m) cout<<m;
	else
	{
		i=m-sum;
		ans+=(qpow(2,i+1)-2)*k%mod;
		ans+=m-i*k;
		cout<<ans%mod;
		return 0;
	}
	return 0;
}
```

---

## 作者：__D_A_T__ (赞：0)

## 题意

翻译很好不再赘述。

## 思路

考虑贪心。

为了使分数尽可能小，那便使翻倍次数最小，同时尽可能紧凑。因此每次连续做 $k-1$ 题避开翻倍，于是将 $k-1$ 题和一道空题看作一段，将 $n$ 道题分成 $\left\lfloor\frac{n}{k}\right\rfloor$ 段。当然，这是最理想的情况。因为每一段都需要一个空题，有可能总题数减去做题数比空题数要小，此时就必须翻倍 $\left\lfloor\frac{n}{k}\right\rfloor － (n-m)$ 次。

定义 $f(x)$ 为连续做了 $x \times k$ 道题的倍率，那么有：
$$
f(x) = \begin{cases} 0 & \quad x=0 \\ (f(x-1)+k)\times 2 & \quad \text{x>0} \end{cases}
$$

经过一定的计算可以得出 $f(x) = k \times \sum^{x}_{i=1}2^i$，通过[等比数列求和公式](https://answer.baidu.com/answer/land?params=tLnZwmflYbAUx6YXDGRrC46uesXvnoAPj8PjmnUdeT6d6JOL6Baehi%2BVBuWBcQkAYri0WDg3LYoecgGU8givvRaU3uA3ITozdrx5TvUILqkkt5z4o1Giz%2FmpDETg%2BjKW%2ByMbMSRb%2BzmCnc4eATBYwTFDGQibNSZpze7v4F3CLTljeGf9muj2bqGTPanBj4q3Su3JxXwqljXXIBRKSnr4Gw%3D%3D&from=dqa&lid=aec8d71a0013b774&word=%E7%AD%89%E6%AF%94%E6%95%B0%E5%88%97%E6%B1%82%E5%92%8C)可以化简为 $k \times 2 \times(2^x - 1)$，可以用快速幂加速。最后再加上不用翻倍的得分就好了。

这里有个小事项：需要翻倍的部分应在无需翻倍部分的前面。

什么意思呢？设翻倍部分的长度为 $l_1$，倍率为 $x$，不用翻倍部分的长度为 $l_2$，显然 $l_1 \times 2^x+l_2<(l_1+l_2)\times 2^x$。因此让需要翻倍的部分先处理完，最后再加上不用翻倍的部分输出即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long int
const int p=1e9+9;
int n,m,k,cnt,s1,s2;
int qpow(int a,int b)//快速幂 
{
	int s=1;
	while(b)
	{
		if(b&1)s=(s*a)%p;
		a=(a*a)%p,b>>=1;
	}
	return s;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m>>k;
	cnt=max(n/k-(n-m),0ll);//翻倍次数 
	s1=(k*(2*(qpow(2,cnt)-1))%p)%p;//翻倍得分 套等比数列求和公式 
	s2=m-cnt*k;//不翻倍的得分 
	cout<<(s1+s2)%p<<endl;//求和输出 
	return 0;
}
```

---

## 作者：cike_bilibili (赞：0)

# 思路
题目等价于黑白染色。

首先一定是贪心地每染 $k-1$ 个黑后空一个白，因为这样一定不会翻倍。设 $m1 = \lfloor \frac{n}{k} \rfloor \times (k-1)+(n- \lfloor \frac{n}{k}\rfloor \times k)$，当 $m\le m1$ 时，直接输出 $m$ 即可。

刚刚讨论的是不用翻倍的情况，将剩下的 $m2=m-m1$ 个黑依次插入至每 $k-1$ 个已填入黑中的空中，注意到答案是等比数列求和，使用快速幂即可。

# AC CODE
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+9;
int ans=0;
int Pow(int x,int y){
	int push=x,ans=1;
	while(y){
		if(y&1)ans=ans*push%mod;
		push=push*push%mod;
		y>>=1;
	}
	return ans;
}
signed main(){
	int n,m,k;
	cin>>n>>m>>k;
	if(m<=n/k*(k-1)+(n-n/k*k)){
		cout<<m;
		return 0;
	}
	int m1=m-n/k*(k-1)-(n-n/k*k);
	ans=k*(Pow(2,m1+1)+mod-2)%mod;
	ans+=n/k*(k-1)+(n-n/k*k)-m1*(k-1);
	cout<<ans%mod;
	return 0;
}
```

---

## 作者：QWQ_123 (赞：0)

考虑翻倍最小的次数，那么就是一直放 $k-1$ 个，直到最后放了 $k-1$ 个无法放完为止（因为每放一个 $k-1$ 就会多一个空，所以总数减去空的个数要 $\ge m$）。

然后考虑剩余连续段的价值，贪心的，那一段肯定要放到最前面，然后来找找规律：

*	若有 $k$ 个，那么分数是 $2k$。
*	若有 $2k$ 个，那么分数是 $6k$。
*	若有 $3k$ 个，那么分数是 $14k$。

我们发现，实际上对于连续 $nk$ 个，分数就是 $(2^{n+1}-2)k$，然后对于多余的一部分就直接加上即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll mod = 1e9 + 9;

ll n, m, k;

long long power(long long a, long long b) {
	long long res = 1;
	for (; b; b >>= 1, a = a * a % mod)
		if (b & 1) res = res * a % mod;
	return res;
}

int main() {
	cin >> n >> m >> k;

	ll l = 0, r = m / (k - 1);
	while (l < r) {
		ll mid = (l + r + 1) >> 1;

		if (n - mid >= m) l = mid;
		else r = mid - 1;
	}

	if (n - ((m + k - 2) / (k - 1)) + 1 >= m) {
		printf("%lld\n", m);
		return 0;
	}

	m -= l * (k - 1);
	ll t = m / k, ans = ((power(2, t + 1) - 2 + mod) % mod) * k % mod + (m % k);

	printf("%lld\n", (ans + l * (k - 1) % mod) % mod);

	return 0;
}
```

---

## 作者：XL4453 (赞：0)

### 解题思路：

考虑贪心。

能不翻倍就不翻倍，否则尽量把翻倍往前放。

所以可以先计算出一共不得不翻倍几次，一个显然的贪心策略是当有错误可以用的时候，直到就差一个就要翻倍了再用。

那么这个值的计算就需要先求出错了几个，然后再根据这个算出可以有多少题不用翻倍，这样剩下的就是没有错误的回答垫而必须翻倍的题目了。然后就能根据这个算出翻倍的次数啦。

这样算出来是：$\left\lfloor\dfrac{n-(n-m)k}{k}\right\rfloor$。需要注意的是，你算出来的这个值可能是负的，但是实际根本不可能，注意判断。

但是这个数是很大的，不能直接暴力处理，考虑再往前推一步。

发现每一次翻倍之前分数都增长了 $num$，然后翻倍，再增长，再翻倍。若设第 $i$ 次翻倍后总共的的分是 $f_i$，容易得出一个递推公式：$f_i=2(f_{i-1}+k)$（首项 $f_0=0$）。可以用矩阵快速幂处理，也可以求一个通项公式：$f_n=(2^{n+1}-2)k$ 然后直接快速幂处理。这里似乎是直接快速幂更简单一点。

最后不要忘了加上后来不翻倍题的分数。

---
### 代码：

```cpp
#include<cstdio>
#define int long long
using namespace std;
const int MOD=1e9+9;
int n,m,k,dou,ans;
int pow(int a,int b){
	int ans=1;
	while(b){
		if(b&1)ans=(ans*a)%MOD;
		a=(a*a)%MOD;
		b=b>>1;
	}
	return ans;
}
signed main(){
	scanf("%I64d%I64d%I64d",&n,&m,&k);
	if(m==0){printf("0\n");return 0;}
	dou=(n-(n-m)*k)/k;
	if(dou<0)printf("%I64d",m);
	else ans=(k*(2*(pow(2,dou)-1)%MOD)%MOD+m-dou*k)%MOD,printf("%I64d",ans);
	return 0;
}
/*
25 22 5
*/
```


---

