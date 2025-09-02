# Number into Sequence

## 题目描述

You are given an integer $ n $ ( $ n > 1 $ ).

Your task is to find a sequence of integers $ a_1, a_2, \ldots, a_k $ such that:

- each $ a_i $ is strictly greater than $ 1 $ ;
- $ a_1 \cdot a_2 \cdot \ldots \cdot a_k = n $ (i. e. the product of this sequence is $ n $ );
- $ a_{i + 1} $ is divisible by $ a_i $ for each $ i $ from $ 1 $ to $ k-1 $ ;
- $ k $ is the maximum possible (i. e. the length of this sequence is the maximum possible).

If there are several such sequences, any of them is acceptable. It can be proven that at least one valid sequence always exists for any integer $ n > 1 $ .

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
4
2
360
4999999937
4998207083```

### 输出

```
1
2 
3
2 2 90 
1
4999999937 
1
4998207083```

# 题解

## 作者：wind_seeker (赞：10)

题目中要找一个数列满足乘积为 $n$ 的最长数列

首先我们想到的应该是 **分解质因数**。

由于 $n$ 最大为 $10^{10}$，所以我们可以线性筛 $10^5$ 内所有的质数。

```cpp
void work(int n){
	for(int i=2; i<=n; i++){
		if(numlist[i]==false){
			prime[++cnt] = i ;
			for(int j=i; i*j<=n; j++)
				numlist[i*j] = true;
		}
	}
	return;
}
```
然后我们举一个例子（$n=360$）

$360=2* 2* 2* 3* 3* 5$

因为前面的数要被后面所有的数整除，所以前面的数的每一个因数后面的必须都有

那么这个数列可以为

$2,2* 3,2* 3* 5$ 即为$2,6,30$

$2,2,2* 3* 3* 5$ 即为$2,2,90$

我们看后面的这一个数列， $k$ 就是最多因数的个数，而这一列就是把出现最多的因数输出 $k-1$ 个，然后再将最后剩余的一个与其他所有的因数搭配，满足了所有的情况。

这样我们就可以先找到最多的一个因数，然后 $k=\text{它的个数}$，之后输出 $k-1$ 个这个数，最后输出其他所有因数相乘（即为 $n$ 除以前面所有输出因数）。

当然，如果 $k=0$（没有小于 $n$ 的因数），则输出 $n$ 。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int maxn,k,n,t,ans;
bool numlist[100000001];
int prime[20000001], cnt;
void work(int n){
	for(int i=2; i<=n; i++){
		if(numlist[i]==false){
			prime[++cnt] = i ;
			for(int j=i; i*j<=n; j++)
				numlist[i*j] = true;
		}
	}
	return;
}
signed main()
{
	work(1000000);
	cin>>t;
	while(t--)
	{
		k=0;
		maxn=0;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			if(prime[i]>sqrt(n))
			break;
			int sum=0;
			int m=n;
			while(m%prime[i]==0)
			{
				sum++;
				m/=prime[i];
			}
			if(sum>k)
			{
				k=sum;
				maxn=prime[i];
				ans=m;
			}	
		}
		if(k==0)
			cout<<1<<endl<<n<<endl;
		else
		{
			cout<<k<<endl;
			for(int i=1;i<k;i++)
				cout<<maxn<<" ";
			cout<<ans*maxn<<endl;
		}
	}
	return 0;
}
```





---

## 作者：Blunt_Feeling (赞：7)

## CF1454D Number into Sequence 题解

由于 $n$ 最大为 $10^{10}$，所以可以考虑将 $n$ 分解质因数，因为 $n$ 最大的质因数不会超过 $\sqrt n$，$n$ 的质因数的个数不会太大。想到分解质因数后，由于 $\prod \limits_{i=1} ^k a_i=n$，所以对于每一个 $a_i$，都是 $n$ 的一部分质因数的乘积。

那么如何让 $k$ 尽可能的大呢？我们可以考虑吧 $n$ 的质因数分成尽可能多的组数。题目中说，
>$a_{i+1}$ is divisible by $a_i$ for each $i$ from $1$ to $k-1$.

所以得出一个重要的结论：

**对于每一个 $i$，$a_{i+1}$ 必包含 $a_i$ 的所有质因数。** 因此，假设 $a_i=2$，那么对于所有大于 $1$ 的 $i$，它对应的 $a_i$ 都有一个质因数是 $2$。

所以，问题就转化为，**统计 $n$ 的所有质因数中，出现最多的质因数出现的次数。**

当然，想要最快地把 $n$ 分解质因数，我用了线性筛质数。

### Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
int T,n,k,cnt=0,prime[50000]; //cnt为10^5范围内质数的个数
bool is_prime[100050];
void get_prime() //线性筛质数
{
	memset(is_prime,true,sizeof(is_prime));
	is_prime[0]=is_prime[1]=false;
	For(i,2,100050)
	{
		if(is_prime[i])
			prime[++cnt]=i;
		for(int j=1;j<=cnt&&i*prime[j]<=100050;j++)
		{
			is_prime[i*prime[j]]=false;
			if(i%prime[j]==0)
				break;
		}
	}
}
signed main()
{
	cin>>T;
	get_prime();
	while(T--)
	{
		cin>>n; int nn=n;
		int ans=0,csp; //csp为出现次数最多的质因数
		For(i,1,cnt) //枚举每一个质数是不是n的质因数
		{
			int tot=0;
			while(n%prime[i]==0)
			{
				tot++;
				n/=prime[i];
			}
			if(ans<tot)
			{
				ans=tot;
				csp=prime[i];
			}
		}
		cout<<max(ans,1ll)<<endl; //ans如果是0，就说明n是质数，此时输出n就行了
		int ji=1; //出现次数对多的质因数的乘积
		For(i,1,ans-1) printf("%lld ",csp),ji*=csp;
		printf("%lld\n",nn/ji); //一个小小的构造技巧
	}
	return 0;
}
```


---

## 作者：dapingguo8 (赞：2)

### 题意

给定一个正整数 $n$ ，构造一个长度为 $m$ 的不降序列 $A$ ，使得：

- $A_i \ge 2$。

- $\prod\limits_{i=1}^m A_i=n$。

- $\forall i:1\le i <m$ 有 $A_i | A_{i+1}$，即$A_{i+1}$可以被$A_i$整除。

求一种构造方式使得$m$最大。

$2\le n \le 10^{10}$

### Solution

- 将 $n$ 表示为 $p_1^{k_1}p_2^{k_2}\ldots p_s^{k_s}$ 的方式，其中 $p$ 为质数， $k$ 为正整数，则答案不会超过 $\max\limits _{1\le i \le s} k_i$ 。

#### 证明：

因为 $A_i\ge2$ 且 $A_{i+1}$ 可以被 $A_{i}$ 整除，所以 $A$ 中每个数必须被某个大于 $1$ 的数整除。假设 $m$ 大于 $\max\limits _{1\le i \le s} k_i$，

不妨设 $A_1$ 可以被质数 $P$ 整除，因为 $n$ 中包含质因数$P$的个数$K\le \max\limits _{1\le i \le s} k_i$ ，所以 $K< m$。因此在$A_2,A_3,\ldots,A_m$中必然存在某个元素不可被$P$整除，即不可被$A_1$整除，与原条件矛盾。

因此，答案 $m$ 不会超过$\max\limits _{1\le i \le s} k_i$，

#### 解法

观察到$A$为不降序列，假设$\max\limits _{1\le i \le s} k_i=K$ 对应质数为 $P$，则可得$n$可以被$P^{K}$整除。

我们可以构造长度为 $ k$ 的如下序列：

$$P,P,P,\ldots,P, \frac{nP}{P^{K}}$$

它们的乘积为 $P\times P \times \ldots \times \frac{nP}{P^{k}}=P^{K-1}\times \frac{n}{P^{K-1}} = n$，符合要求。

它们均可以被$P$整除，符合要求。

因为$\frac{n}{P^K}\ge 1$，所以$\frac{nP}{P^{K}}\ge P$，符合序列不降的要求。

此时的$m=\max\limits _{1\le i \le s} k_i$，因此答案为最优。

时间复杂度$O(\sqrt n\times \log s)$（使用`map`）或$O(\sqrt n)$
（数组统计）。$s$为$n$的质因数个数。
### Solution
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		long long n;
		cin>>n;
		map<long long ,int>mp;
		long long temp=n;
		long long ind=0;
		for(long long i=2;i*i<=n;i++){
			while(temp%i==0){
				temp/=i;
				mp[i]++;
				if(mp[ind]<mp[i])ind=i;
			}
		}
		if(temp>1){
			mp[temp]++;
			if(mp[ind]<mp[temp])ind=temp;
		}
 		cout<<mp[ind]<<endl;
		for(int i=1;i<mp[ind];i++){
			cout<<ind<<' ';
			n/=ind;
		}
		cout<<n<<endl;   
	}
}
```

---

## 作者：fls233666 (赞：1)

根据题干进一步考虑最终得到的数列中数字的性质。

首先注意到最终数列中的数字满足： $\prod_{i=1}^{k}a_i=n$

分析得出：**最终数列中的数字都是 $n$ 的因数。**

回到题干，我们注意到一个很奇怪的要求： $\forall i \in [2,n] : a_i \  \bmod \  a_{i-1} = 0$

由这个要求，首先可以推断出的是 $a_{i-1} \le a_i$ 。因为如果 $a_{i-1} > a_i$ 则必然有 $a_i \  \bmod  \  a_{i-1} = a_i$ 又因为有要求 $\forall i \in a , i>1 $ 所以显然不存在 $a_{i-1} > a_i$ 。那么得出**最终的数列一定的单调不下降子序列。**

把上述两个结论放在一起看，再结合题目中最终序列的长度最长这一要求，我们发现，显然当 $\forall i \in [2,n-1] : a_i \  = \  a_{i-1}$ 时答案更优。

我们知道，对于任意正整数 $n$ 可以质因数分解得到 $n = p_1^{c_1} \times p_2^{c_2} \times p_3^{c_3} \times ... \times p_m^{c_m}$ 的形式。由上述结论，我们得出： **我们要找到最大的 $c_i$ 以及对应的 $p_i$ 然后用 $p_i$ 填充数列的前 $c_i-1$ 项，最后一项则是 $ \frac {n}{p_i^{c_i-1}}$ 。** 这样得出的数列就是最长数列。

那么我们只要用 $O(\sqrt n)$ 的时间找到 $n$ 的质因数分解中 $c_i$ 最大的 $p_i$ 即可。注意对于质数的情况要特判即可。

代码如下：

```cpp
#include<iostream>
#include<cstdio>
#define ll long long
#define rgt register ll
using namespace std;

ll n,mxcnt,mxd,td,tcnt;

int main(){
	int test;
	scanf("%d",&test);
	while(test--){
		scanf("%lld",&n);
		mxd=n; mxcnt=0;
     //先假设 n 为质数
        
		for(rgt i=2;i*i<=n;i++){
			if(n%i==0){  //找到一个因数
				td=n;
				tcnt=0;
				while(td%i==0){  //尝试分解
					td/=i;
					tcnt++;
				}
				if(tcnt>mxcnt){  //更新答案
					mxcnt=tcnt-1;
					mxd=i;
				}
			}
		}
        
		printf("%lld\n",mxcnt+1);  //输出序列长度
		for(rgt i=1;i<=mxcnt;i++){
			printf("%lld ",mxd);  //输出拆得的质因数 Pi
			n/=mxd;
		}
		printf("%lld\n",n);  //输出 n/pi^(ci-1)
	}
	return 0;
}

```



---

## 作者：胖头鱼学员 (赞：1)

# CF1454D

[CF传送门](http://codeforces.com/problemset/problem/1454/D)
[洛谷传送门](https://www.luogu.com.cn/problem/CF1454D)

## $QuestionMeaning$

给你一个$n$，构造一个长为$k$的序列$a$，满足：
$$1. \forall x \in a : x > 1$$
$$2. \forall i \in [2,k] : a_i \mod a_{i-1} = 0$$
$$3. \prod_{i=1}^{k} a_i = n$$

求$k_{max}$和与其对应的序列$a$。

## $Solution$

~~一道ex数学题~~

考虑质因数分解：

将$n$表示成下列形式：
$$
\prod_{i = 1}^{n}p_i^{k_i}
$$

则发现若$a_i = a_{i-1}$时，也满足上述式子，那么问题就被转化为求最大的$p_i$使得：
$$
\forall i \ne j, j \in [1,k] : k_i > k_j
$$

## $Code$
```
#include <iostream>
#include <vector>
#define int long long

using namespace std;

const int kMaxN = 1e10;
const int kMaxNsqrt = 1e5 + 1;

bool pb[kMaxNsqrt];
int m, p[kMaxNsqrt];

void Calc() {
  for (int i = 2ll; i < kMaxNsqrt; ++i) {
    if (!pb[i]) {
      p[++m] = i;
      for (int j = i; j < kMaxNsqrt; j += i) {
        pb[j] = 1;
      }
    }
  }
}

int T, n, k, x, sum, ans, mul;

void solve() {
  scanf("%lld", &n);
  x = n;
  ans = k = 0;
  for (int i = 1; i <= m; i++) {
    sum = 0;
    while (!(n % p[i])) {
      sum++;
      n /= p[i];
    }
    if (ans < sum) {
      k = p[i];
      ans = sum;
    }
  }
  mul = 1;
  printf("%lld\n", max(ans, 1ll));
  for (int i = 1; i < ans; ++i) {
    printf("%lld ", k);
    mul *= k;
  }
  printf("%lld\n", x / mul);
}

signed main() {
  Calc();
  scanf("%lld", &T);
  while (T--) {
    solve();
  }
  return 0;
}
```

---

## 作者：yzy1 (赞：1)

题目大意
---

共 $t (t\le 5000)$ 组数据,
对于每组数据输入一个整数 $n (2 \le n \le 10^{10})$
请构造一个长度为 $k$ 的数列 $a$, 满足以下条件:

- $\forall i \in a : i > 1$;
- $\prod_{i=1}^k a_i = n$;
- $\forall i \in [2,k] : a_i \bmod a_{i-1} = 0$ ;
- $k$ 尽可能大;

对于每组数据第一行输出一个整数 $k$,
第二行输出 $k$ 个整数 $a_i$, 如果有多个数列满足条件任意输出一个.

做法
--

通过分析样例可得, 最优的数列一定形如
"$k - 1$ 个相同的质数 $x$ + 一个数 $\dfrac{n}{x ^{k-1}}$".

那么这个问题就变成了, 找出一个数量最多的质因子 $x$,
输出 $k-1$ 个 $x$ 和 $\dfrac{n}{x ^{k-1}}$.

由于这题的 $n$ 最大可以到 $10^{10}$,
我们可以先打出一个 $1 \sim \sqrt{10^{10}}$ 的质数表,
然后对于每个 $n$ 枚举质数表里的所有质数, 看看能被整除几次, 
选择一个整除次数最多的质数输出即可.

时间复杂度: $\mathcal O(t \sqrt{N})$.

Code
---

```cpp
bool isPrime[100007];
std::vector<int> primes;
// 打出 1-1e5 的质数表, 放入 `primes` 中
void Pre() {
  int n = (int)1e5;
  for (int i = 2; i <= n; i++) {
    isPrime[i] = true;
  }
  for (int i = 2; i * i <= n; i++) {
    if (isPrime[i]) {
      for (int j = 2 * i; j < n; j += i) isPrime[j] = false;
    }
  }
  for (int i = 1; i <= n; i++) {
    if (isPrime[i]) {
      primes.push_back(i);
    }
  }
}

int t, sum, id;
ll n;

// 判断 x 能整除 n 几次, 并更新最大值
void count(int x) {
  ll w = n;
  int cnt = 0; // 能整除的次数
  while (w % x == 0) {
    ++cnt;
    w /= x;
  }
  if (cnt > sum) {
    sum = cnt;
    id = x;
  }
}

int main() {
  Pre(); // 预处理
  scanf("%d", &t);
  while (t--) {
    bool fl = false; // 判断 n 是不是合数
    sum = 0;
    scanf("%lld", &n);
    for (int x : primes) {
      if (n % x == 0) {
        fl = true;
        count(x);
      }
    }
    if (!fl) {
      // 如果 n 是质数, 则直接输出它自己即可
      puts("1");
      printf("%lld\n", n);
      continue;
    }
    printf("%d\n", sum);
    for (int i = 1; i < sum; ++i) {
      printf("%d ", id);
      n /= id;
    }
    printf("%lld\n", n);
  }
  return 0;
}
```

---

## 作者：烛木 (赞：1)

### 题意

给定一个数 $n$ ，将此数拆成元素个数为 $len$ 的数列，令元素之积为 $n$ ，使得对于元素 $a_i (2 \le i \le n)$ 满足 $a_{i-1} \mid a_i $ ，求 $len$ 的最大值和当 $len$ 最大时的这个数列。

### 思路

枚举$k (2 \le k \le  \sqrt n ,k \mid n)$  ，则对于每一个 $k$ :

$$len=n \div k-1 $$   

而此数列为:

$$k,k,...,k,n \mod k \cdot  k$$

然后求 $len$ 的最大值和其对应的数列即可。

### code

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
using namespace std;
#define int long long
int t,n,ansk,ansd;
signed main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld",&n);
		ansk=ansd=0;
		for(int i=2;i<=sqrt(n);i++)
		{
			if(n%i==0) 
			{
				int d=i,k=0,e=n;
				while(e%d==0&&e/d%d==0)
				{
					e/=d;
					++k;
				}
				if(k>ansk)
				{
					ansk=k;
					ansd=d;
				}
			}
		}
		if(!ansd)
		{
			printf("1\n%lld\n",n);
			continue;
		}
		printf("%lld\n",ansk+1);
		while(ansk--) 
		{
			printf("%lld ",ansd);
			n/=ansd;
		}
		printf("%lld\n",n);
	}
	return 0;
}
```


---

## 作者：houpingze (赞：0)

提供一个简洁好写好想常数小的解法（）

目前是最优解

这题我第一次想到的解法大概是： $O(\sqrt{n})$ 枚举 $n$ 的质因数，对于找到的第一个质因数 $i$ ，我们设 $x$ 为满足 $n \mod i^x =0 $ 的最大正整数，然后答案就可以按照以下方式构造：

$$ \begin{matrix}\underbrace{i\ ,\ i\ ,\ i\ ,\ i}\\x-1\end{matrix} \dots ,\ \frac{n}{i^{x-1}} $$

前半部分的 $i$ 有 $x-1$ 个，这样做是为了保证最后一个数字可以被 $i$ 整除。

但是这样显然是错误的，我们可以看一下这个样例：

```
1
108
```

手算可以发现答案是：

$$3\ 3\ 12$$

但是按照我们上面流程的计算，答案是这样子的：

$$2\ 54$$

挂了。

问题出在哪？

**第一个找到的质因数，不一定是个数最多的。**

那我们可以简单地改一下：对于每个质因数 $i\ (i \in[2,\sqrt{n}])$ , 设 $x$ 为满足 $n \mod i^x =0 $ 的最大正整数，找到 $x$ 最大的质因数 ，并把这个质因数（也就是 $i$ ） 记录下来，最后直接按照上文所说的方法构造即可。

---

