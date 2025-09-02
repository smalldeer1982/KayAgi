# [ABC250D] 250-like Number

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc250/tasks/abc250_d

以下の条件を満たす整数 $ k $ を「 $ 250 $ に似た数」と呼びます。

- $ k $ が素数 $ p\ <\ q $ を使って $ k=p\ \times\ q^3 $ と表される。

$ N $ 以下の「 $ 250 $ に似た数」は全部でいくつありますか？

## 说明/提示

### 制約

- $ N $ は $ 1 $ 以上 $ 10^{18} $ 以下の整数

### Sample Explanation 1

\- $ 54\ =\ 2\ \times\ 3^3 $ なので、「 $ 250 $ に似た数」です。 - $ 250\ =\ 2\ \times\ 5^3 $ なので、「 $ 250 $ に似た数」です。 $ 250 $ 以下の「 $ 250 $ に似た数」は、以上の $ 2 $ つです。

## 样例 #1

### 输入

```
250```

### 输出

```
2```

## 样例 #2

### 输入

```
1```

### 输出

```
0```

## 样例 #3

### 输入

```
123456789012345```

### 输出

```
226863```

# 题解

## 作者：I_am_kunzi (赞：5)

# AT_abc250_d 题解

### 题目大意

给你一个 $ N $ 并求出小于 $ N $ 的所有的 $ 250 $ 相似数的数量，输出这个值。给出 $ 250 $ 相似数的定义。

+ 质数 $ p $ 和 $ q $ 
+ 整数 $ k $ 满足 $ k = p \times q ^ 3 $ 
+ $ p < q $ （这一点在翻译中没有给出，希望加上）

### 题目分析

既然是质数，我就想到了线性筛等判断质数的方法，但是数据范围可是 $ 1 \le N \le 10 ^ {18} $ 呢！哪种筛法都不可能在数秒之内做到筛出这个范围内的质数，所以我们需要减小计算量。

观察下 $ 250 $ 相似数的定义，发现如果 $ q > 10 ^ 6 $ 的话，整个式子的结果就会比 $ 10 ^ {18} $ 大；又因为 $ p < q$，所以我们可以先看 $ q $ 的值，再看 $ p $ 的值；还因为 $ p $ 和 $ q $ 都是质数，那么用线性筛就足够了。

### 思路拆分 and 代码实现

+ 筛出质数
+ 判断 $ 250 $ 相似数

筛出质数的话 $ 10 ^ 6 $ 的范围可以用线性筛，不多说了，我们贴一下代码。

```cpp
bool prim[1000005]; //判断是不是质数 
int isprim[500005]; //存储质数 
int cnt;
void stringprim(unsigned long long a)
{
	//需要分情况讨论，因为最大只用筛除到 1000000 
	if(a < 1000000) //a < 1000000，那么就筛除 1 到 a 之间的质数 
	{
		prim[0] = 1; //两个特判 
		prim[1] = 1;
		for(unsigned long long i = 0 ; i <= a ; i++)
		{
			if(prim[i] == 0) //是质数 
			{ 
				isprim[++cnt] = i; //存储 
			}
			for(int j = 1 ; j <= cnt && i * isprim[j] <= a ; j++)
			{
				prim[i * isprim[j]] = 1; //构造合数并筛除它们 
				if(i % isprim[j] == 0)
				{
					break; //说明剩下的合数还会被其他数筛除，不用重复判断 
				}
			}
		}
	}
	else 
	{
		prim[0] = 1;
		prim[1] = 1;
		for(int i = 0 ; i <= 1000000 ; i++)
		{
			if(prim[i] == 0)
			{ 
				isprim[++cnt] = i;
			}
			for(int j = 1 ; j <= cnt && i * isprim[j] <= 1000000 ; j++)
			{
				prim[i * isprim[j]] = 1;
				if(i % isprim[j] == 0)
				{
					break;
				}
			}
		}
	}
}
```

下一步是判断，我们可以枚举每一个 $ q $ 再枚举每一个 $ p$，然后判断这组 $ p $ 和 $ q $ 能不能构造出符合条件的 $ 250 $ 相似数，代码如下。

```cpp
unsigned long long n;
cin >> n;
stringprim(n); //顺便把判断质数的函数的调用放在这里
unsigned long long ans = 0; //存储答案 
for(unsigned long long i = 1 ; i <= cnt ; i++) //枚举每一个 q 
{
	//枚举每一个 p ，注意有限制条件
	//限制 1 ：p < q
	//限制 2 : p * q * q * q <= n 
	for(unsigned long long j = 1 ; isprim[j] * pow(isprim[i] , 3) <= n && j < i ; j++)
	{
		ans++; //有满足情况的条件，答案累加 
	}
}
cout << ans << endl;
```

最后，组合代码！

```cpp
#include<iostream>
#include<cmath>
#include<cstring>
#include<string>
#include<cstdio>
#include<iomanip>
#include<algorithm>
#include<map>
#include<queue>
#include<vector>
using namespace std;
bool prim[1000005]; //判断是不是质数 
int isprim[500005]; //存储质数 
int cnt;
void stringprim(unsigned long long a)
{
	//需要分情况讨论，因为最大只用筛除到 1000000 
	if(a < 1000000) //a < 1000000，那么就筛除 1 到 a 之间的质数 
	{
		prim[0] = 1; //两个特判 
		prim[1] = 1;
		for(unsigned long long i = 0 ; i <= a ; i++)
		{
			if(prim[i] == 0) //是质数 
			{ 
				isprim[++cnt] = i; //存储 
			}
			for(int j = 1 ; j <= cnt && i * isprim[j] <= a ; j++)
			{
				prim[i * isprim[j]] = 1; //构造合数并筛除它们 
				if(i % isprim[j] == 0)
				{
					break; //说明剩下的合数还会被其他数筛除，不用重复判断 
				}
			}
		}
	}
	else 
	{
		prim[0] = 1;
		prim[1] = 1;
		for(int i = 0 ; i <= 1000000 ; i++)
		{
			if(prim[i] == 0)
			{ 
				isprim[++cnt] = i;
			}
			for(int j = 1 ; j <= cnt && i * isprim[j] <= 1000000 ; j++)
			{
				prim[i * isprim[j]] = 1;
				if(i % isprim[j] == 0)
				{
					break;
				}
			}
		}
	}
}
int main()
{
	unsigned long long n;
	cin >> n;
	stringprim(n);
	unsigned long long ans = 0; //存储答案 
	for(unsigned long long i = 1 ; i <= cnt ; i++) //枚举每一个 q 
	{
		//枚举每一个 p ，注意有限制条件
		//限制 1 ：p < q
		//限制 2 : p * q * q * q <= n 
		for(unsigned long long j = 1 ; isprim[j] * pow(isprim[i] , 3) <= n && j < i ; j++)
		{
			ans++; //有满足情况的条件，答案累加 
		}
	}
	cout << ans << endl;
    return 0;
}
```

顺便放上无注释版。

```cpp
#include<iostream>
#include<cmath>
#include<cstring>
#include<string>
#include<cstdio>
#include<iomanip>
#include<algorithm>
#include<map>
#include<queue>
#include<vector>
using namespace std;
bool prim[1000005];
int isprim[500005];
int cnt;
void stringprim(unsigned long long a)
{ 
	if(a < 1000000)
	{
		prim[0] = 1;
		prim[1] = 1;
		for(unsigned long long i = 0 ; i <= a ; i++)
		{
			if(prim[i] == 0)
			{ 
				isprim[++cnt] = i;
			}
			for(int j = 1 ; j <= cnt && i * isprim[j] <= a ; j++)
			{
				prim[i * isprim[j]] = 1;
				if(i % isprim[j] == 0)
				{
					break;
				}
			}
		}
	}
	else 
	{
		prim[0] = 1;
		prim[1] = 1;
		for(int i = 0 ; i <= 1000000 ; i++)
		{
			if(prim[i] == 0)
			{ 
				isprim[++cnt] = i;
			}
			for(int j = 1 ; j <= cnt && i * isprim[j] <= 1000000 ; j++)
			{
				prim[i * isprim[j]] = 1;
				if(i % isprim[j] == 0)
				{
					break;
				}
			}
		}
	}
}
int main()
{
	unsigned long long n;
	cin >> n;
	stringprim(n);
	unsigned long long ans = 0; 
	for(unsigned long long i = 1 ; i <= cnt ; i++) 
	{
		for(unsigned long long j = 1 ; isprim[j] * pow(isprim[i] , 3) <= n && j < i ; j++)
		{
			ans++; 
		}
	}
	cout << ans << endl;
	return 0;
}

```


完成了！最后放上 AC 的截图。

![abc250d ac](https://cdn.luogu.com.cn/upload/image_hosting/3fub2bte.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

---

## 作者：_GW_ (赞：3)

## 思路
观察到 $n$ 比较大，那么考虑从 $q$ 和 $p$ 下手。

看到 $k=p×q^3$ 那么 $q$ 和 $p$ 不最大就是 $10^6$ 了吗？

再次观察，$q$ 和 $p$ 还是质数，时限还是 $2$ 秒，这不枚举质数就行了吗？

此时用线性筛，筛出 $1$ 到 $10^6$ 所有质数,也就 $78498$ 个，大于 $n$ 了就退出，可以过了！

不会线性筛的左转[P3383](https://www.luogu.com.cn/problem/P3383)自行学习。

## code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+5;
bool vis[N];
vector<long long> prime;//存储质数。 
map<int,int> mp;
long long n=1e6,q,nn,ans;
int main()
{
    cin>>nn;
	vis[1]=1;	
	for(long long i=2;i<=n;i++)//线性筛模板。 
	{
		if(!vis[i])
		{
            prime.push_back(i);
        }
		for(int j=0;j<prime.size();j++)
		{
			if(prime[j]*i>n) break;
            vis[prime[j]*i]=1;
            if(i%prime[j]==0) break;
		}
    }
    for(int i=0;i<prime.size();i++)//枚举q和p。 
    {
        if(prime[i]*prime[i]*prime[i]>nn) break;//超过n了，退出。 
        for(int j=0;j<i;j++)
        {
            if(prime[i]*prime[i]*prime[i]*prime[j]>nn) break;//超过n了，退出。
            ans++;//统计答案。 
        }
    }
    cout<<ans<<endl;
    return 0;
} 
```


---

## 作者：PikachuQAQ (赞：2)

## Description

[Link](https://www.luogu.com.cn/problem/AT_abc250_d)

## Solution

首先确定质数范围。

设 $P$ 为质数集合，已知式子 $p \times q^3 = k$，$p,q \in P$，确定 $q$ 最大值为：

$$\sqrt[3]{\dfrac{10^{18}}{2}}\thickapprox 793701$$

求得在 $q$ 最大值内质数个数约为 $8000$，考虑对 $P$ 进行一个指针的双。

对于每个质数 $p$ 计算最大 $q$，设任意质数 $k$， 如果 $p < k \leq q $，则 $k$ 为最大 $q$，答案加 $p,q$ 范围内质数个数。

如果 $p \geq q$，输出答案。

## Code

```cpp
// 2023/5/19 Accept__

#include <iostream>
#include <cmath>

using namespace std;

const int kMaxN = 793710;

long long n, f, b[kMaxN], ans, maxp;
bool p[kMaxN];

void is_prime() {
    for (int i = 2; i <= maxp; i++) {
        if (!p[i]) b[f++] = i;
        for (int j = 0; j < f; j++) {
            if (i * b[j] > maxp) break;
            p[i * b[j]] = 1;
            if (!(i % b[j])) break;
        }
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n, maxp = ceil(pow(n / 2, 1 / 3.0));
    is_prime();
    for (int i = 0, j = f - 1; i < j; i++) {
        while (j >= 0 && b[i] * b[j] * b[j] * b[j] > n) {
            j--;
        }
        (i < j) && (ans += j - i);
    }
    cout << ans;

    return 0;
}
```


---

## 作者：escapist404 (赞：1)

# AT_abc250_d 250-like number Solution

## 题意简述

求不大于 $N$ 的一些数的个数，这些数分别存在素数 $p, q$（$p < q$）使得其等于 $p\cdot q^3$，$N \le {10}^{18}$。

## 题解

考虑 $p, q$ 的范围。

$$p \cdot q^3 < q^3 \le N$$

即 $p < q \le \sqrt[3]N$。

预处理 $\sqrt[3]N$ 以内的质数，每次从小到大枚举 $q$，则 $p$ 满足两个条件：

* $p \le \dfrac{N}{q^3}$
* $p < q$

每次二分即可求出对于某个 $q$ 满足条件的 $p$ 的个数。

时间复杂度 $\sqrt[3]N + \sqrt[3]N \log \sqrt[3]N = O(\sqrt[3]N \log \sqrt[3]N)$。


```cpp
#include <bits/stdc++.h>

using namespace std;

long long pri[1000005], vis[1000005], cnt, n;

void init(int n) {
    for(int i = 2; i <= n; ++i) {
        if(!vis[i]) {
            pri[cnt++] = i;
        }
        for(int j = 0; j < cnt; ++j) {
            if (1ll * i * pri[j] > n) break;
            vis[i * pri[j]] = 1;
            if (i % pri[j] == 0) {
                break;
            }
        }
    }
}
long long ans = 0;

int main()  {

    cin >> n;
    init(1000000);
    // N^{1/3} < 10^6

    for(int i = 0; i < cnt; ++i)    {

        if(n / (pri[i] * pri[i] * pri[i]) == 0)  break;
        int res_1 = upper_bound(pri, pri + cnt, n / pri[i] / pri[i] / pri[i]) - pri;
        int res_2 = lower_bound(pri, pri + cnt, pri[i]) - pri;
        ans += min(res_1, res_2);
    }

    cout << ans << endl;
}
```

---

## 作者：FReQuenter (赞：1)

## 思路

观察数据范围，我们发现，$N$ 很大，不好直接枚举。而 $K=p\times q^3$，则 $q$ 一定小于等于 $^3\sqrt{N}$，即 $p<q\leq10^6$。我们可以考虑枚举 $p$。

因为 $p$，$q$ 都是质数，所以可以先筛出所有小于 $10^6$ 的质数（埃筛或欧拉筛法都行），然后枚举 $p$，再通过一个质数前缀和来计算有多少个质数小于 $\min\{\frac{K}{q^3},q\}$，累加到答案中。

## 代码

```cpp
#include<iostream>
#define int unsigned long long
using namespace std;
bool is_prime[1000005];
int prime[1000005],sum[1000005],cnt=0;
void find_prime(){
	int n=1000000;
	for(int i=2;i<=n;i++) is_prime[i]=true;
	for(int i=2;i<=n;i++){
		if(is_prime[i]) prime[++cnt]=i;
		for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
        	is_prime[i*prime[j]]=0;
        	if(!(i%prime[j])) break;
		}
	}
  for(int i=2;i<=1000000;i++){
    sum[i]=sum[i-1];
    if(is_prime[i]) sum[i]++;
    //质数前缀和
  }
}//欧拉筛法
signed main(){
  int n,ans=0;
  cin>>n;
  find_prime();
  for(int i=1;i<=cnt&&prime[i]*prime[i]*prime[i]<=n;i++){
    int tmp=n/(prime[i]*prime[i]*prime[i]);
    tmp=min(tmp,prime[i]-1);//注意p<q
    ans+=sum[tmp];//有多少个质数小于\min\{\frac{K}{q^3},q\}
  }
  cout<<ans;
}
```

---

## 作者：_shine_ (赞：1)

## 题目大意
现在有一个数 $n$，问你有多少个满足小于 $n$ 的“与 $250$ 相似的数”。
## 思路
观察本题，不难发现，因为“与 $250$ 相似的数”是等于 $p\times q^3$ 的，最简单的办法就是筛出小于 $10^6$ 的质数，也就是筛出小于 $\log_{3}{10^{18}}$ 的质数，并枚举质数 $p$，在同时二分枚举出另一个 $q$ 是否存在即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e6+10;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
    while(ch<'0'||ch>'9'){
		if(ch=='-')w=-1;ch=getchar();
	}
    while(ch>='0'&&ch<='9'){
    	s=s*10+ch-'0';
		ch=getchar();
	}
    return s*w;
}
inline void write(int x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9)write(x/10);
    putchar(x % 10 + '0');
}
int n,ans;
int p[maxn],idx;
bool vis[maxn];
void did(int n){//筛出每一个质数
    for(int i=2;i<=n;++i){
        if(!vis[i]){
            p[idx++]=i;
    	}
        for(int j=0;p[j]*i<=n;j++){
        	vis[p[j]*i]=true;
			if(i%p[j]==0){
				break;
			}
		}
    }
}
signed main(){
	n=read();
	did(maxn-1);
	for(int i=0;i<idx;++i){//枚举每一个p
		int q=p[i];
		int k=q*q*q;
		int num=n/k;
		ans+=upper_bound(p,p+i,num)-p;//二分函数
	}
	cout << ans << endl;
	return 0;
}
```


---

## 作者：ghx0052 (赞：0)

# 思路：

我们先用线性筛筛出一定范围内的质数，因为 $N$ 的范围很大，所以我们也尽量筛多一点，最后我们枚举出 $p\times q^3$ 的值，因为这个值有可能溢出，我们可以将质数之一移向右边。

# 代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
//const int N=1e6+5;
//const int N=1e5+5;
//const int mod=1e9+7;
//const long long mod=998244353;
using namespace std;
ull prime[20000005];
int cnt;
bool isprime[20000005];
void shai(ull x)
{
    for(int i=2;i<=x;i++)
      {
        if(isprime[i])
          prime[++cnt]=i;
        for(int j=1;j<=cnt,i*prime[j]<=x;j++)
          {
            isprime[i*prime[j]]=0;
            if(i%prime[j]==0)
              break;
          }
      }
}

ull n,t;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ull sum=0;
    memset(isprime,1,sizeof(isprime));
    shai((ull)20000000);
    cin>>n;
    for(int i=1;i<=cnt;++i)
      for(int j=i+1;j<=cnt;++j)
        {
            if(prime[i]*prime[j]*prime[j]>(n/prime[j]))
              break;
          ++sum;
        }
    printf("%lld\n",sum);
}
```


---

## 作者：Zhangikun (赞：0)

## 思路：
因为要求 $p\times q^3\leq n$，所以考虑埃氏筛筛出质数，存到一个数组里面。其中 $q$ 一定小于等于 $10^6$。因为如果 $q>10^6$，而 $p$ 是质数，至少是 $2$。$n$ 最大是 $10^{18}$，所以 $2\times (10^6)^3>10^{18}$，显然，爆炸了。所以我们筛到 $10^6$。筛完后，直接 $O(size^2)$ 枚举质数，如果 $zs_i\times zs_j\leq n$ 并且 $zs_i<zs_j$，方案加 $1$（$size$ 表示筛出质数的数量，$zs_i$ 表示第 $i$ 个质数）。
## 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int prime=1e6;
bool cnt[prime+5];
int zs[prime+5];
size_t _size;//unsigned long long _size;
inline void iss()//埃氏筛
{
  cnt[1]=1;
  for(int i=2;i<=prime;i++)//由于要把所有质数全塞进数组，所以得循环到prime
  {
    if(cnt[i])continue;
    zs[++_size]=i;
    for(int j=i;i*j<=prime;j++)
    {
      cnt[i*j]=1;
    }
  }
}
int32_t main()
{
  ios::sync_with_stdio(0);
  cin.tie(0),cout.tie(0);
  int n,sum=0;
  cin>>n;
  iss();
  for(int i=1;i<=_size;i++)
  {
    const int p=zs[i];
    //枚举p
    for(int j=i+1;j<=_size&&p*pow(zs[j],3)<=n;j++)
    {
      sum++;
      //printf("%dx%d^3<=%d\n",p,zs[j],n);
    }
  }
  cout<<sum;
  return 0;
}
```


---

## 作者：__Dist__ (赞：0)

~~鄙人第一篇题解~~

### 人话翻译

给定一个整数 $ N $，问小于 $ N $ 的 $ 250 $ 的相似数有哪些？

相似数定义：若一个整数 $ k $ 满足 $ k = p × q^3 $，且 $ p < q $ 那么称 $ k $ 为“$ 250 $ 的相似数”。

### 思路分析

 $ N $ 的数据范围很大，如果要筛出 $ 1 \sim N $ 之间的每个素数，非但会超时，数组也存不下。考虑优化，既然 $ p < q $ ，那么 $ q^3 $ 一定不会超过 $ N $，所以我们只要筛出 $ 1 \sim 10^6 $ 的素数即可。
 
 最后循环判断，找到符合条件的 $ k $，增加答案数量。
 
 ### 代码时间
 
 这里我采用的埃氏筛，速度较快。
 
 埃氏筛代码：
 
 ```cpp
 bool a[1000005];
void is_prime(int n){
	a[1]=1;
	for(int i=1;i<=n;i++){
		if(a[i]==0){
			for(int j=i+i;j<=n;j+=i){
				a[j]=1;
			}
		}
	}
}
```
最后与循环判断结合起来，完成！

完整代码：

```cpp
#include<iostream>
using namespace std;
typedef unsigned long long ll;//本题数据范围极大，long long都会爆
bool a[1000005];
ll primes[1000005];
ll cnt;
ll n;
ll ans=0;
void is_prime(int n){//埃氏筛
	a[1]=1;
	for(int i=1;i<=n;i++)
		if(a[i]==0)
			for(int j=i+i;j<=n;j+=i)
				a[j]=1;
	for(int i=1;i<=n;i++)
		if(a[i]==0) primes[++cnt]=i;
}
int main(){
	cin>>n;
	is_prime(1000005);
	for(ll i=1;i<=cnt;i++){//枚举q
		//为加快速度，可以剪枝，条件如下
		//1.  p<q
		//2.  p*q*q*q<=n
		for(ll j=1;j<i/*相当于剪枝条件1*/;j++){//枚举p
			if(primes[j]*primes[i]*primes[i]*primes[i]>n) break;//剪枝条件2
			++ans;//符合就增加答案数量
		}
	}
	cout<<ans;
}
```
AC [链接](https://www.luogu.com.cn/record/110006928)。

---

## 作者：max666dong123 (赞：0)

## 题意
求出 $0\sim N$ 中有多少个数 $k$ 满足 $k=p \times  q^3 \ (p\neq q) $ 其中 $p,q$ 为质数。

注意  $\Large{p<q}$。

## 方法
首先我们知道这里面的质数绝对不可以超过 $\large{\sqrt[3]{n}}$ ，不然绝对会超过 $n$。
用欧拉筛先筛出质数，时间复杂度为 $O(n)$，用其他的筛法会有常数，有可能 ``TLE``。

筛出质数之后一个数一个数的枚举，不符合直接退出，就可以过。

其实这道题可以用**双指针**来做，时间复杂度 $O(n)$。

## 代码
```cpp
#include<bits/stdc++.h>
#define int unsigned long long
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
const int N=1e6+10;
vector<int>pr;
bool vis[N];
int n;
signed main(){
	IOS;
	cin>>n;
	int k;
	for(k=1e6;k>=1;k--){
		if(k*k*k<n){//三次方分解
			break;
		}
	}
	for(int i=2;i<=k;i++){//欧拉筛
		if(vis[i])continue;
		pr.push_back(i);
		for(int j=2;j*i<=k;j++){
			//cout<<i*j<<endl;
			vis[i*j]=1;
		}
	}
	int cnt=0;
	for(int i=0;i<pr.size();i++){//枚举
		bool f=0;
		for(int j=i+1;j<pr.size();j++){
			if(pr[i]*pr[j]*pr[j]*pr[j]<=n){
				cnt++;
				f=1;
			}
			else{
				break;
			}
		}
		if(!f)break;
	}
	cout<<cnt<<endl;
	return 0;
}


```

---

## 作者：WaterSun (赞：0)

# 思路

对于这道题，我们可以发现一个事情：我们筛质数只需要筛 $1 \sim \log_3 n$ 的部分就行了。

因为 $k = p \times q^3$，那么，我们考虑一种极端情况，$p$ 为一个很小的数，那么 $k$ 就无限接近于 $q^3$。

我们就先假设 $k = q^3$，那么可以得出 $q = \log_3 n$。然后由题目描述的条件可知 $p < q$，所以，我们筛质数只需要筛到 $\log_3 n$ 即可。

然后，我们暴力一遍即可。

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

const int N = 1e6 + 10,M = 1e5 + 10;
int n,idx,ans;
int p[M];
bool vis[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline void init(int n){//埃筛 
	for (re int i = 2;i <= n;i++){
		if (!vis[i]){
			p[++idx] = i;
			for (re int j = 1;i * j <= n;j++) vis[i * j] = true;
		}
	}
}

signed main(){
	n = read();
	int t = powl(n,1.0 / 3);
	init(t);
	for (re int i = 1;i <= idx;i++){ 
		int x = p[i] * p[i] * p[i];//也就是题目中的 q 
		for (re int j = 1;j < i;j++){//因为 p < q，所以只需要枚举 1 ~ i 即可 
			int cnt = p[j] * x;//得出 k 
			if (cnt <= n) ans++;//更新答案 
			else break;//优化 
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：luminary3 (赞：0)

### 思路

***

~~作为一个 OIer，先看看数据范围是一个好习惯。~~

一看，$n$ 是一个巨大无比的数，考虑 $p$ 和 $q$ 入手。

既然 $p$ 和 $q$ 都是质数，那么我们只需要筛出质数，最后在枚举 $p$ 和 $q$
 就可以了。
 
那这样做会不会超时呢？我们算一下 $p$ 和 $q$ 的范围：
 
$$\sqrt[3]{\dfrac{10^{18}}{2}}≈10^6$$
 
在这个范围内的质数就只有 $80000$ 个，因为我枚举的是 $q$，$q$ 是立方根级别的，最大时是 $3$ 次根号 $10^6$，不会超时。
 
## code


```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
const int N=1e6+5;
int prime[N],cnt,n;
bool vis[N];
void gpm(int x)//筛出质数
{
   	for(int i=2;i<=x;i++)//模板
	{
		if(vis[i]==false)
			prime[++cnt]=i;
		for(int j=1;j<=cnt&&i*prime[j]<=x;j++)
		{
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)
				break;
		}
	}
	return ;
}
signed main()
{
    gpm(N-1);
    int sum=0;
    cin>>n;
    for(int i=1;i<=cnt;i++)//枚举p，q
      for(int j=i+1;j<=cnt;j++)
        {
            if(prime[i]*prime[j]*prime[j]>(n/prime[j]))
              break;//如果超过n了，就退出循环
          	sum++;//统计答案
        }
    cout<<sum;//输出
    return 0;
}

```

---

