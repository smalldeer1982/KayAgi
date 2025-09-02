# Binary Cafe

## 题目描述

Once upon a time, Toma found himself in a binary cafe. It is a very popular and unusual place.

The cafe offers visitors $ k $ different delicious desserts. The desserts are numbered from $ 0 $ to $ k-1 $ . The cost of the $ i $ -th dessert is $ 2^i $ coins, because it is a binary cafe! Toma is willing to spend no more than $ n $ coins on tasting desserts. At the same time, he is not interested in buying any dessert more than once, because one is enough to evaluate the taste.

In how many different ways can he buy several desserts (possibly zero) for tasting?

## 说明/提示

Variants for 1st sample: {}, {1}

Variants for 2nd sample: {}, {1}

Variants for 3rd sample: {}, {1}, {2}

Variants for 4th sample: {}, {1}, {2}, {1, 2}

## 样例 #1

### 输入

```
5
1 2
2 1
2 2
10 2
179 100```

### 输出

```
2
2
3
4
180```

# 题解

## 作者：MornStar (赞：5)

# CF1840B Binary Cafe 题解

[CF题面](https://codeforces.com/problemset/problem/1840/B)
## 题目大意
给定 $n$ 和 $k$，求有多少个 $k$ 位的二进制数（可以有前导零）小于等于 $n$。

$1\le n,k\le 10^9$。
## 思路
我们知道，$k$ 位的二进制数可以表示 $[0,2^k-1]$ 之间的所有数。

所以当 $n\le 2^k-1$ 时，区间 $[0,n]$ 内的数都可以被表示出来，所以答案为 $n+1$。

否则就只能表示 $[0,2^k-1]$ 之间的数，答案为 $2^k$。

注意：当 $k \ge 30$ 时 $2^k$ 就已经超过 $10^9$，此时答案一定为 $n+1$。	
## code
```cpp
// by mornstar
// Jun/06/2023 22:52
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	cin>>T;
	while(T--){
		long long n,k;
		cin>>n>>k;
		if(k>=30||n<pow(2,k))	cout<<n+1<<endl;
		else	cout<<(int)pow(2,k)<<endl;
	}
}
```

---

## 作者：Vct14 (赞：2)

### 题目翻译

一个咖啡馆里有 $k$ 种甜点，第 $i$ 种甜点的价格为 $2^{i-1}$ 元。

现在你有 $n$ 元，若每种甜点限购一份，问你有多少种购买甜点的方式。

### 思路

如果所有的甜点都买一份，则会花费 $2^0+2^1+2^2+\cdots+2^{k-1}=2^k-1$ 元。

若 $n\ge 2^k-1$，即所有甜点都可以买，则共有 $C_{k}^1+C_{k}^2+C_{k}^3+\cdots+C_{k}^k=2^k$ 种买法。（其实因为每一份甜点都有买和不买两种状态，所以共有 $2^k$ 种买法。）

若 $n< 2^k-1$，由[此题](https://www.luogu.com.cn/problem/P1010)可得任何一个正整数都可以用 $2$ 的幂次方表示。则从花费 $0$ 元至 $n$ 元，共有 $n+1$ 种买法。

注意，因为 $k\ge30$ 时，$2^k-1\ge1073741823$，又因为 $n\le10^9$，所以必有 $2^k-1>n$。此时答案必为 $n+1$。这样判断可以防止爆 `long long`。


---

## 作者：mark0575 (赞：0)

## 思路：

我们可以计算买 $k$ 种商品最多的价钱，将其与 $n$ 进行比较。如果 $2^k-1$（买 $k$ 种商品最多的一种的价钱）比 $n$ 小，最多就可以有 $2^k$ 种方案（$0\sim 2^k-1$），否则就是 $n+1$ 种（$0\sim n$）。

## AC code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t;
signed main()
{
	cin>>t;
	while(t--)
	{
		int n,k;
		cin>>n>>k;
		if(n<=(1<<k)-1||k>=31)//防止溢出int
		{
			cout<<(n+1)<<"\n";
		}
		else
		{
			cout<<(1<<k)<<"\n";
		}
	}
	return 0;
 }

```


---

## 作者：_zzzzzzy_ (赞：0)

# 思路
分情况讨论。

- $n\le 2^k-1$ 我们可以选 $0$ 到 $n$ 中的所有数，也就是 $n+1$ 个。

- $n>2^k-1$ 我们可以选 $0$ 到 $2^k-1$ 中的所有数，也就是 $2^k$。

最后注意一下当 $k$ 大于 $30$ 时一定大于 $n$，防止溢出就直接特判了。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;
	while (T--) {
		int n, k;
		cin >> n >> k;
		if (k >= 30 || n <= (1 << k) - 1) {
			cout << n + 1 << "\n";
		}
		else {
			cout << (1 << k) << "\n";
		}
	}
	return 0;
}
```

---

## 作者：qwertim (赞：0)

# 题意
有 $k$ 种商品，编号为 $0$ 至 $k-1$，编号为 $i$ 的商品的价格为 $2^i$，问你在花的钱数不超过 $n$ 且每种商品最多买一个（可以不买所有商品）的前提下，有多少种购买商品的方式。
# 思路
因为编号为 $i$ 的商品的价格为 $2^i$，所以我们可以把每个商品的价格化成二进制：买了第 $i$ 个商品，第 $i$ 位就为 $1$。问有多少个 $k$ 位的二进制数小于等于 $n$。

这样想就很简单了。我们来分两种情况讨论。
- $n \leq 2^k-1$

可以表示 $0$ 至 $n$ 中的所有数，答案为 $n+1$。

- $n > 2^k-1$

只能表示 $0$ 至 $2^k-1$ 中的数，答案为 $2^k$。

注意：我们需要特判 $k$ 是否大于等于 $30$，因为 $2^{30}-1 = 1073741823$，而 $n \leq 10^9$，此时答案肯定为 $n+1$。这样做可以有效避免溢出的风险。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k;
int main(){
    cin>>t;
    while(t--){
        cin>>n>>k;
        if(k>=30)cout<<n+1<<endl;//特判
        else if(n<=(1<<k)-1)cout<<n+1<<endl;//第一种
        else cout<<(1<<k)<<endl;//第二种
    }
    return 0;
}
```


---

## 作者：xiazha (赞：0)

## 思路

这题分两种情况讨论即可。

1. $n\le 2^k-1$

所有二进制数都能表示，答案为 $n+1$。

2. $n>2^k-1$

只能表示 $0\sim 2^k-1$ 之间的数，答案为 $2^k$ 。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
int t;
long long n,k;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>k;
		if(n<=(int)pow(2,k)-1) cout<<n+1<<"\n";
		else cout<<(int)pow(2,k)<<"\n";
	}
	return 0;
}
```


---

## 作者：Jerry_heng (赞：0)

（一）

可以看成把一个数用二进制表示。

如果 $n\le2^k-1$ ，都可以取，输出 $n+1$。

否则可以取 $0\sim2^k-1$，输出 $2^k$。

（二）

AC 代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,k;
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld%lld",&n,&k);
		int s=1;
		for(int i=1;i<=k;i++){
			s=s*2;
			if(s>n)break;
		}
		printf("%lld\n",min(n+1,s));
	}
	return 0;
}
```

---

## 作者：XBaiC (赞：0)

### 思路

当 $ n\leq 2^k - 1$ 时，$0 \sim n$ 的所有数都可以显示出来，所以答案为 $n+1$。否则只能显示 $0 \sim 2^k - 1$ 所有的数，所以答案为 $2^k$。

### CODE

```cpp
#include<bits/stdc++.h>
int main()
{
	int T;
	scanf( "%d" , &T );
	while( T-- )
	{
		long long n , k;
		scanf( "%lld %lld" , &n , &k );
		if( n <= ( int ) pow( 2 , k ) - 1 )
		{
		    printf( "%lld \n" , n + 1 );
		}
		else
		{
		    printf( "%lld \n" , ( int ) pow( 2 , k ) );
		}
	}
	return 0;
}
```


---

## 作者：Symbolize (赞：0)

# 思路
从第 $i$ 个食物的美味度为 $2^i$ 不难发现若品尝所有的食物则总的美味度为 $2^0+2^1+\dots+2^{k-1}$，简化一下即为 $2^{k}-1$。那么如果限制美味度的 $n$ 比 $2^k-1$ 大或相等，那么选择的数量与大小都不会受限制，所以对于每个食物有选和不选两种情况，总方案数即为 $2^k$，若 $n$ 比 $2^k-1$ 小，因为每个自然数都能拆分为由若干个 $2$ 的整数次方的和的形式，所以 $0$ 至 $n$ 的任意整数都是一种方案，即 $n+1$。
# Code
下面附上 AC 代码！！！
```cpp
#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(register int i=l;i<=r;++i)
#define rep2(i,l,r) for(register int i=l;i>=r;--i)
#define debug() puts("----------")
const int N=1e5+10;
const int inf=0x3f3f3f3f;
const int inff=0x3f3f3f3f3f3f3f3f;
const double pi=acos(-1);
using namespace std;
typedef complex<int> ci;
typedef complex<double> cd;
ll t,n,k;
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return f*x;
}
inline int power(ll a,ll b)//快速幂 
{
	ll ans=1;
	while(b)
	{
		if(b&1) ans*=a;
		a*=a;
		b>>=1;
	}
	return ans;
}
inline void getans()
{
	n=read();
	k=read();
	int prod=power(2,k);
	if(k<log2(1e9)/*用log2判断是否会超过范围，不然会爆long long*/&&prod<=n) cout<<prod<<endl;//情况1 
	else cout<<n+1<<endl;//情况2 
	return;
}
int main()
{
//	#ifndef ONLINE_JUDGE
//		freopen(".in","r",stdin);
//		freopen(".out","w",stdout);
//	#endif
	t=read();
	while(t--) getans();//多测 
	return 0;//结束 
}

```

---

## 作者：Czy_Lemon (赞：0)

### 先来解释一下题意：

一个咖啡馆里有 $k$ 种甜点，甜点的编号从 $0$ 到 $k-1$，第 $i$ 种甜点的价格为 $2^{i}$，问你在花费不超过 $n$ 的情况下有多少种购买甜点的方式（注意每种甜点最多买一次）。

### 然后我们进行分析：

我们可以发现，每种买甜点的方式都可以用一个 $k$ 位的二进制数来表示。从右往左编号从 $0$ 到 $k-1$，对于第 $i$ 位如果是 $1$ 就代表买第 $i$ 种甜点，如果是 $0$ 就代表不买这种甜点，而每种方式所对应的二进制数的十进制值就正好代表了这种方式所花费的价格。

这样原问题就变成了寻找长度为 $k$ 且数值不超过 $n$ 的二进制数的数量。简单分析一下可知，一个长度为 $k$ 位的二进制数的数值能取到的区间为 $[0,2^{k}-1]$，那么当 $n \leq 2^{k}-1$ 时，从 $0$ 到 $n$ 都是可以表示出来的，答案为 $n+1$。不然的话最多就只能取最大的区间 $[0,2^{k}-1]$ 一共 $2^{k}$ 个值了。

### 以下是代码：


```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int t,n,k;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k);
		if(n<=pow(2,k)-1) printf("%d\n",n+1);
		else{
			int x=pow(2,k);
			printf("%d\n",x);
		}
	}
	return 0;
}
```

### 后记

如果对题解的内容有建议或者指正，请在在评论区里说或者私信我.

---

