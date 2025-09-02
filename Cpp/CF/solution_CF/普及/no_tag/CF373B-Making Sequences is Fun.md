# Making Sequences is Fun

## 题目描述

We'll define $ S(n) $ for positive integer $ n $ as follows: the number of the $ n $ 's digits in the decimal base. For example, $ S(893)=3 $ , $ S(114514)=6 $ .

You want to make a consecutive integer sequence starting from number $ m $ ( $ m,m+1,... $ ). But you need to pay $ S(n)·k $ to add the number $ n $ to the sequence.

You can spend a cost up to $ w $ , and you want to make the sequence as long as possible. Write a program that tells sequence's maximum length.

## 样例 #1

### 输入

```
9 1 1
```

### 输出

```
9
```

## 样例 #2

### 输入

```
77 7 7
```

### 输出

```
7
```

## 样例 #3

### 输入

```
114 5 14
```

### 输出

```
6
```

## 样例 #4

### 输入

```
1 1 2
```

### 输出

```
0
```

# 题解

## 作者：Velix (赞：2)

简单模拟。

首先我们通过大眼观察法可得如下题意：

>你有 $w/k$ 元钱，每次添加一个数的代价为该数的位数，问从第 $m$ 个数开始最多可连续添加多少个数？

考虑一位一位往上跳。

显然，对于数位相同的数，它们的代价（即数位）是相同的，可以直接用乘法累加代价。

所以我们可以在最开始时先跳到比 $m$ 高一位，然后检测能不能跳到下一位，如果能的话就减去这一段代价并让 $m$ 往上跳直至跳不动为止。

具体实现看下代码。

记得开 long long !

### Code

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long w,m,k,x=1,y=0,z=0;
	//x是当前预计跳到的数，y是这一段数的位数，z是当前已经跳到的数
	cin>>w>>m>>k;
	z=m;
	w/=k;
	while(x<m)x*=10,y+=1;
	while(w>=x*y-z*y)//检测是否可以跳
	{
		w-=x*y-z*y;
		z=x;
		x*=10;
		y+=1;
	}
	//此时的z还需要加上w/y（即最后剩下的代价还能跳多少个数）才是最后跳到的数，并要减去最开始的m
	cout<<z+w/y-m;
}
```


---

## 作者：OcTar (赞：1)

## 题意回顾

定义数 $i$ 的位数为 $S(i)$，费用为 $k\times S(i)$。

你有 $w$ 元，依次购买 $m, m+1,m+2,\cdots$，最多能购买几个数？

## 题目分析

一眼二分题（蒟蒻是这么认为的），考虑对能购买到哪个数进行二分。

我们发现每个数的花费都乘上了个 $k$，所以直接把 $w$ 除掉 $k$ 即可。

设当前二分到了 $mid$，我们发现计算从 $m$ 到 $mid$ 的花费是不太好计算的，于是我们考虑计算从 $1$ 到 $mid$ 的花费。本题的花费与数的具体大小无关，只与位数有关，于是我们就可以用乘法来减少运算次数。

具体的：$1\sim 9$ 有 $9$ 个数的位数为 $1$，花费 $9\times1$；$10\sim 99$ 有 $90$ 个数的位数为 $2$，花费 $90\times 2$……于是我们可以用两个变量，一个每次乘以 $10$，一个每次加 $1$，相乘后累加即可。

完整代码如下：

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
#define ll long long
ll w, m, k;
ll ans;
ll calc(ll x) {
    ll res = 0;
	ll cnt = 1, d = 1;// cnt表示已经计算完的数，d表示位数 
    while (1) { 
        if (cnt * 10 > x) {
            res += (x - cnt + 1) * d;//(x - cnt + 1)为剩余的无法整体计算的部分 
            break;
        }
        //文中规律的具体体现
        res += cnt * 9 * d; 
        ++d, cnt *= 10;
    }
    return res;
}
int main() {
    cin >> w >> m >> k;
    w /= k;
    ll l = m - 1, r = 2e16;
    while (l <= r) {
        ll mid = (l + r) >> 1;
        if (calc(mid) - calc(m - 1) > w) {//计算m-1是因为m也需要购买 
            r = mid - 1;
        } else {
        	l = mid + 1;
		}
    }
    cout << l - m << endl; //答案要-m，因为计算时从1起算 
    return 0;
}
```

~~114514，恶臭。~~

---

## 作者：lhs_chris (赞：0)

# 思路
我们拿到这一题可以发现，可以使用二分查找。
```cpp
bool check(ll x)
{
	ll sum=0;
	for(int i=m;i<=m+x;i++)
	{
		sum=sum+k*h(i);
		if(sum>n)
		{
			return 0;
		}
	}
	return 1;
}
```
如果 check 函数这样写，那代码就算用了二分优化也一定会超时。那我们可以考虑如何优化 check 函数。

我们发现，每一个数字的花费只和 $k$ 与数字的位数有关。因为 $k$ 是固定的，而且一定范围之内的数字位数是相同的，那么这个范围之内的花费是全都相同的。

如果我们记当前数字 now 的位数为 num，那么这个范围就是 $now \sim 10^{num}$。那这个范围的总花费就是 $(10^{num}-now) \times num \times k$。

想到这，优化就完成了。
# 代码
```cpp
#include<bits/stdc++.h>
#include<cstring>
#include<queue>
#include<set>
#include<stack>
#include<vector>
#include<map>
#define ll unsigned long long
#define lhs printf("\n");
using namespace std;
const int N=1e5+10;
const int M=2024;
const int inf=0x3f3f3f3f;
ll n,m,k;
int num;
ll ans=-1;
//注意long long
ll power(ll a,ll b)//快速幂
{
	ll ans=1,wq=a;
	while(b)
	{
		if(b & 1)ans=ans*wq;
		wq=wq*wq;
		b>>=1;
	}
	return ans;
}
//计算数字的位数
int h(ll x)
{
	int num=0;
	while(x)
	{
		x/=10;
		num++;
	}
	return num;
}
bool check(ll x)
{
	ll sum=0;
	int num=h(m);
	ll now=m;
	while(now<=m+x)
	{
		bool flag=0;
  		ll g=power(10,num);
    //因为now到g数位全部相同，那此范围sum可以直接算
    //计算相同数位当中的最大值
		if(g<=m+x)//说明m+x不在这个范围里面，计算范围now到g
              //否则的话计算的范围是now到m+x
			sum=sum+(g-now)*num*k;
		else
			sum=sum+(m+x-now)*num*k,flag=1;

		if(sum>n)return 0;
		if(flag)
		{
			break;
		}
		now=pow(10,num);
		num++;
	}
	return 1;
}
int main()
{
	scanf("%lld%lld%lld",&n,&m,&k);
	ll l=0,r=n/k;
	while(l<=r)
	{
		ll mid=(l+r)/2;
		int k=check(mid);
		if(k)
		{
			l=mid+1;
			ans=mid;
		}
		else
		{
			r=mid-1;
		}
	}
//输出注意 %lld 不要写成 %d
	printf("%lld",ans);
	return 0;
}
/*
462 183 8
10000000000000000 1 1
10000000000000000 9999999999999999 1
*/
```

---

## 作者：wind_whisper (赞：0)

## $\text{Description}$
定义 $S(i)=i$ 的位数，如 $S(893)=3,S(114514)=6$。

数 $x$ 的费用为 $k\times S(i)$。

你有 $w$ 元钱，要从 $m$ 开始连续添加尽量多的数 $(m,m+1,m+2,\cdots)$ 组成一个序列，问这个序列最长有多长。  
$w,m\le 10^{16},k\le10^9$
## $\text{Solution}$
小清新模拟。  
可以先令 $w\gets \lfloor \dfrac{w}{k}\rfloor$ 把 $k$ 的影响去掉。  
一直往进位处跳直到不能继续跳位置，然后把剩下的个数求出来，过程中贡献加起来即可。  
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=2e6+100;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)) {x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}
int n;
ll w,m,k;
inline ll calc(ll x){
  int res(0);
  while(x) x/=10,++res;
  return res;
}
ll mi[20];
signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  mi[1]=1;
  for(int i=2;i<=18;i++) mi[i]=mi[i-1]*10;
  w=read();m=read();k=read();
  w/=k;
  ll o=calc(m),ans(0);
  while((mi[o+1]-m)*o<=w){
    ans+=mi[o+1]-m;w-=(mi[o+1]-m)*o;
    ++o;m=mi[o];
    //printf("o=%lld w=%lld ans=%lld m=%lld\n",o,w,ans,m);
  }  
  ans+=w/o;printf("%lld\n",ans);
  return 0;
}
/*
*/

```


---

