# Prime-Factor Prime

## 题目描述

[problemUrl]: https://atcoder.jp/contests/jag2017autumn/tasks/jag2017autumn_c



# 题解

## 作者：阿丑 (赞：4)

##### update: 更改了一点错误/kk

[原题传送门](https://www.luogu.com.cn/problem/AT3680)

#### 前置知识：

质数筛法（埃氏筛/欧拉筛）。

#### 题意：

- 设正整数 $x$ 的质因数分解式为 $x=\prod\limits_{i=1}^k p_i^{\alpha_i}$。定义 $f(x)=\sum\limits_{i=1}^k\alpha_i$。

- 给出 $l,r$，求对所有 $i\in[l,r]$，有多少 $f(i)$ 是质数。

- $1\le l\le r\le10^9$，$0\le r-l<10^6$。

#### 分析：

注意到 $r-l<10^6$，这意味着可以枚举 $l$ 到 $r$ 的所有数；但是如果对一个数暴力分解质因数，需要 $O((r-l)\sqrt r)$ 的复杂度，无法忍受。注意到一个数的质因数个数最多有 $\log_2r$ 个，如果可以直接枚举出质因数，复杂度就是 $[l,r]$ 中所有数的质因数个数之和，即 $O((r-l)\log r)$，可以接受。

考虑对于每一个质数 $p$，枚举 $[l,r]$ 中所有能被它整除的数，并计算对应的 $\alpha$。

这样解决了计算 $f(i)$ 的时间复杂度，但最大的质数是 $10^9$ 的级别，无法使用质数筛筛出。我们可以使用质因数分解中的一个常见技巧，只分解 $\sqrt r$ 以内的质数。这样，对于 $[l,r]$ 内的每个数，最多只会剩下一个质因数没有被筛出。我们只需要计算每个数的因子有没有被筛完，若没有，则说明还有且仅还有一个因子。

---

#### 思路：

1. 筛出 $\sqrt r$ 以内的质数并枚举 $[l,r]$ 中能被整除的数，计算对应的幂。

2. 对于没有被筛出的质因数，扫一遍 $[l,r]$ 即可得到。

---

#### 枚举能被整除的数

对于一个质数 $p$，当然不能枚举所有 $[l,r]$ 中的数，应该直接枚举它的倍数。这里用到了一个小技巧：$[l,r]$ 中第一个能被 $p$ 整除的数（如果有）是 $(\lfloor\frac{l-1}p\rfloor+1)\times p$。

细节上，因为 $10^9$ 存不下，所以对于每一个 $[l,r]$ 的数都减去了一个 $l$ 来存储。

```cpp
//val 表示 i 除以所有已分解质因数后还剩多少
for(int j=(l-1)/p+1; j*p<=r; ++j) while(val[j*p-l]%p==0) val[j*p-l]/=p, ++f[j*p-l];
```

---

事实上，因为只需要筛 $\sqrt r$ 以内的质数，所以不需要使用线性筛，直接埃氏筛即可。

#### 完整代码：

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for(register int i=l; i<=r; ++i)
#define rrep(i, r, l) for(register int i=r; i>=l; --i)
#define ll long long
#define il inline
using namespace std;
il int read() {
	int res=0; bool k=0; char c; do if((c=getchar())=='-') k=1; while(c<'0' || c>'9');
	while(c>='0' && c<='9') res=(res<<1)+(res<<3)+(c^48), c=getchar(); return k?-res:res;
}
const int mS=1e6+100, mN=32000;
int l, r, f[mS], val[mS];
bool vis[mN];
il void init(int x) {
	vis[0]=vis[1]=1;
	rep(i, 2, x) if(!vis[i]) {
		for(int j=i; i*j<=x; ++j) vis[i*j]=1;
		for(int j=(l-1)/i+1; j*i<=r; ++j) while(val[j*i-l]%i==0) val[j*i-l]/=i, ++f[j*i-l];
	}
}

int ans;
int main() {
	l=read(), r=read();
	rep(i, l, r) val[i-l]=i;
	init(31633);	//即 sqrt(10^9) 
	rep(i, l, r) {
		if(val[i-l]>1) ++f[i-l];	//检查是否被筛完，如果没筛完则 ++f[i]
		if(!vis[f[i-l]]) ++ans;
		//如果 f[i] 是质数，++ans
		//因为 f[i] 是 log i 级别的，所以一定被筛过 
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：Lazy_crush (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_jag2017autumn_c)
### AT_jag2017autumn_c Prime-Factor Prime=素数筛的引用
-  分析题意，首先通过欧拉筛将所有素数筛一遍。
```cpp
isprime[0]=isprime[1]=false;
for(ll i=2;i<=N;i++) isprime[i]=true;
//初始化
for(ll i=2;i<=N;i++){
    if(isprime[i]) cnt++,prime[cnt]=i;
    for(ll j=1;j<=cnt;j++){
        if(prime[j]*i>N) break;
        isprime[i*prime[j]]=false;
        if(i%prime[j]==0) break;
    }//欧拉筛
}//isprime表示i是否为素数，prime按顺序存储N以内的素数
```
- 再用一个函数模拟题目中的 $f(x)$ 函数。

```cpp
bool check(int n){
    int sum=0;
    for(ll i=1;i<=cnt;i++){
    	if(prime[i]*prime[i]>n) break;
        while(n%prime[i]==0) n/=prime[i],sum++;
        //sum即为f(x)
	}
	if(n>1) return isprime[sum+1];
    return isprime[sum];
  //记得特判
}
```
- 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=5e4;
int l,r,prime[N+5],ans,cnt;
bool isprime[N+5];
bool check(int n){
    int sum=0;
    for(ll i=1;i<=cnt;i++){
    	if(prime[i]*prime[i]>n) break;
        while(n%prime[i]==0) n/=prime[i],sum++;
	}
	if(n>1) return isprime[sum+1];
    return isprime[sum];
}
int main(){
    cin>>l>>r;
	isprime[0]=isprime[1]=false;
	for(ll i=2;i<=N;i++) isprime[i]=true;
    for(ll i=2;i<=N;i++){
        if(isprime[i]) cnt++,prime[cnt]=i;
        for(ll j=1;j<=cnt;j++){
        	if(prime[j]*i>N) break;
            isprime[i*prime[j]]=false;
            if(i%prime[j]==0) break;
        }
    }
    for(int i=l;i<=r;i++) ans+=check(i);
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Rose_Melody (赞：1)

## Solution 题解：Prime-Factor Prime
[题目传送门](https://www.luogu.com.cn/problem/AT_jag2017autumn_c)

### 题目分析

**前置知识：欧拉筛（不会的点[这里](https://oi-wiki.org/math/number-theory/sieve/)）**

一个简单的欧拉筛应用。

题目中定义一个数的质因数分解式为：

$$\alpha = \prod_{i = 1}^{k}{p_{i}^{a_{i}}}，f(x) = \sum_{i = 1}^{k}{a_{i}}$$

给定区间 $[l,r]$，求使得 $f(i)$ 为素数的 $i$ 的个数。

先筛出 $1$ 至 $\sqrt{r}$ 中的素数，对于每个 $i$，对不超过 $i$ 的质数都分解掉，$f(x)$ 同时累加。若 $i$ 还是大于 $1$，则 $f(x)$ 加一。判断 $f(x)$ 是否为质数即可。 

### AC Code 


```cpp
#include <bits/stdc++.h>
#define int long long 
#define double long double 
using namespace std;
const int N =  31650; //大于 1e9 ^ 1/2 ;
int l , r , p[N] , cnt = 0 , ans = 0 ;
bool v[N] ;
void prime(){// Euler筛
	v[0] = v[1] = 0 ;
	for(int i = 2;i <= N;i ++){
		v[i] = true ;
	}
	for(int i = 2;i <= N;i ++){
		if(! v[i]) continue ;
		p[++ cnt] = i ;
		for(int j = i * i;j <= N;j += i){
			v[j] = 0 ;
		}
	}
} 
bool check(int x){//依题意模拟
	int ret = 0 ;
	for(int i = 1;i <= cnt;i ++){
		if(p[i] * p[i] > x) break ;
		while(x % p[i] == 0){
			x /= p[i] ;
			ret ++;
		}
	}
	if(x > 1) return v[ret + 1] ;
	return v[ret] ;
}
signed main()
{
//	freopen(".in" , "r" , stdin);
//	freopen(".out" , "w" , stdout); 
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0); 
	cin >> l >> r ;
	prime() ;
	for(int i = l ;i <= r;i ++){
		ans += check(i) ;
	}
	cout << ans << '\n' ;
	return 0;
}
```

---

## 作者：skyskyCCC (赞：1)

## 前言。
这道题怎么没有数据范围，这个真的十分重要。

本题的范围是 $1\leq l,r\leq 10^9$ 且他们的差不大于 $10^6$ 同时保证不小于 $0$ 即可以重叠。看到这个数据范围，我们就知道爆搜或者普通的质数筛都没有办法突破数据范围。
## 分析。
有一种很常见的优化方法：只处理所有 $\leq\sqrt{n}$ 的所有质数。如果一个数分解完之后还有剩余，则剩下的那个一定是一个质数。具体的分析网上应该有详细的解释。这里给出一种反证的方法：

我们不妨将这个结论看做：需要证明任意一个大于 $\sqrt{n}$ 的数的质因数只有一个大于 $\sqrt{n}$。反证的方法如下：我们假设如果存在至少至少存在两个大于 $\sqrt{n}$ 的数，那么它们相乘肯定大于 $n$ 这与我们的公理相违背，所以则这两个数肯定有其中一个不是 $n$ 的质因数。从而我们的假设不成立。得证。

所以只会有一个大于 $\sqrt{n}$ 的数存在。显然我们可以从这个质数出发，遍历整个区间。但是显然这样时间复杂度极高，所以优化。考虑枚举质数的倍数。因为枚举质数的倍数肯定可以再次从原来的数的基础上才凑出一个质数相乘，此时看看是不是符合题意即可。

综上所述，我们设当前的质数为 $prim_i$ 则开始枚举的地方为 $\left\lfloor\dfrac{l+prim_i-1}{prim_i}\right\rfloor\times prim_i$。

上式中的 $-1$ 就是去掉它自己。

代码如下，仅供参考：
```
#include<iostream>
using namespace std;
const int lim=31633;//10^9开根。 
long long l,r;
long long ans,sum;
long long pr[1000005],vis[1000005],a[1000005],count[1000005];
template <typename T> void read(T &x){
	x = 0;
	bool f = 0;
	char c = getchar();
	while (c < '0' || c > '9') f |= c == '-', c = getchar();
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	if (f) x = -x;
}
template <typename T> void write(T x){
	if (x < 0) putchar('-'), x = -x;
	if (x < 10) putchar(x + '0');
	else write(x / 10), putchar(x % 10 + '0');
}
void init(){
    vis[0]=vis[1]=1;
    for(int i=2;i<=lim;i++){
        if(!vis[i]){
            pr[++sum]=i;
            for(int j=i+i;j<=lim;j+=i){
			    vis[j]=1;
			}
        }
    }
}
int main(){
	read(l);read(r);
    //cin>>l>>r;
    init();
    for(int i=l;i<=r;i++){
        count[i-l]=i;
    }
    for(int i=1;i<=sum;i++){
        for(int j=(l+pr[i]-1)/pr[i]*pr[i];j<=r;j+=pr[i]){
            while(count[j-l]%pr[i]==0){
				a[j-l]++;
				count[j-l]/=pr[i];
			}
        }
    }
    for(int i=l;i<=r;i++){
        if(count[i-l]>1){
			a[i-l]++;
		}
        if(!vis[a[i-l]]){
			ans++;
		}
    }
    write(ans);
    cout<<"\n";
    return 0;
}
```
如果这个题可以设置部分分的话，那么对于小于 $\sqrt{n}$ 的数据大可以模拟爆搜一下。显然更快。
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：RAND_MAX (赞：0)

### 题意简述
设一个正整数的质因数分解为 $\prod\limits_{i=1}^k p_i^{c_i}$，则 $f(x)=\sum\limits_{i=1}^kc_i$。求 $l$ 到 $r$ 中有多少个数 $x$ 满足 $f(x)$ 是质数。

### 思路
观察数据范围发现 $l,r$ 很大且 $r-l$ 很小，那么启发我们正解可能是进行预处理之后判断 $l$ 到 $r$ 中每一个是否满足条件。

我们注意到一个数 $x$ 至多有一个大于 $\sqrt x$ 的质因数，那么我们考虑筛出小于等于 $\sqrt r$ 的质数。对于每一个质数筛出 $l$ 到 $r$ 中每个数含有该质因子的个数并剔除这个数所有该质因子。筛完若存在数 $x\ne 1$，则说明 $x$ 有大于 $\sqrt x$ 的因子，只需将答案加一，最后对于每个数 $x$ 判断 $f(x)$ 是否是质数即可。

由于一个数质因数个数是 $\log$ 级别的，所以最大的 $f(x)$ 不会超过 $\log r$，可以沿用上面的质数筛判断 $f(x)$ 是否是质数。
### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define R read()
using namespace std;
int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0')
	{
		if(c=='-')
		{
			f=-1;
		}
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+c-48;
		c=getchar();
	}
	return x*f;
}
void write(int x)
{
	static int st[35],top=0;
	if(x<0)
	{
		x=-x;
		putchar('-');
	}
	do
	{
		st[top++]=x%10;
		x/=10;
	}while(x);
	while(top)
	{
		putchar(st[--top]+48);
	}
	puts("");
}
int num[10001000];
bool isp[20000010];
vector<int>p;
void pre(int n)
{
	isp[1]=isp[0]=1;
	for(int i=2;i<=n;i++)
	{
		if(!isp[i])
		{
			p.push_back(i);
		}
		for(int j:p)
		{
			if(i*j>n)
			{
				break;
			}
			isp[i*j]=1;
			if(i%j==0)
			{ 
				break;
			}
		}
	}
}
int l,r,ans,sum[1000010],kkk,nnnnn;
bool vis[1000010];
signed main()
{
	l=R,r=R;
	for(int i=l;i<=r;i++)
	{
		num[i-l+1]=i;
	}
	pre(sqrt(r));
	for(int i:p)
	{
		for(int j=(l-1)/i+1;j<=r/i;j++)
		{
			nnnnn=0;
			while(num[i*j-l+1]%i==0)
			{
				num[i*j-l+1]/=i,nnnnn++;
			}
			sum[i*j-l+1]+=(nnnnn);
		}
	}
	for(int i=1;i<=r-l+1;i++)
	{
		if(!isp[sum[i]+(num[i]!=1)])
		{
			ans++;
		}
	}
	write(ans);
	return 0;
}
```

---

## 作者：e4fsrc2e4fsrc2 (赞：0)

## [Prime-Factor Prime](https://www.luogu.com.cn/problem/AT_jag2017autumn_c)
## 题意
给定数 $l,r(l,r\le 10^9,0\le r-l\le10^6)$，求在 $[l,r]$ 这段区间内，有多少个数质因数的个数为质数。
## 思路分析
考虑使用暴力预处理出在 $\sqrt{10^9}$ 以内的质数，然后对于每个在 $[l,r]$ 区间内的数暴力枚举其质因子个数，最后判断这个质因子个数是否为质数即可。

时间复杂度 $O((r-l)\omega)$，其中 $\omega$ 表示 $\sqrt{10^9}$ 以内的质数个数 ~~，虽然看上去会超时，但可以通过此题~~。
## [AC 代码](https://atcoder.jp/contests/jag2017autumn/submissions/48709600)


---

