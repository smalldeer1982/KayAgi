# Polo the Penguin and Houses

## 题目描述

Little penguin Polo loves his home village. The village has $ n $ houses, indexed by integers from 1 to $ n $ . Each house has a plaque containing an integer, the $ i $ -th house has a plaque containing integer $ p_{i} $ ( $ 1<=p_{i}<=n $ ).

Little penguin Polo loves walking around this village. The walk looks like that. First he stands by a house number $ x $ . Then he goes to the house whose number is written on the plaque of house $ x $ (that is, to house $ p_{x} $ ), then he goes to the house whose number is written on the plaque of house $ p_{x} $ (that is, to house $ p_{px} $ ), and so on.

We know that:

1. When the penguin starts walking from any house indexed from 1 to $ k $ , inclusive, he can walk to house number 1.
2. When the penguin starts walking from any house indexed from $ k+1 $ to $ n $ , inclusive, he definitely cannot walk to house number 1.
3. When the penguin starts walking from house number 1, he can get back to house number 1 after some non-zero number of walks from a house to a house.

You need to find the number of ways you may write the numbers on the houses' plaques so as to fulfill the three above described conditions. Print the remainder after dividing this number by $ 1000000007 $ $ (10^{9}+7) $ .

## 样例 #1

### 输入

```
5 2
```

### 输出

```
54
```

## 样例 #2

### 输入

```
7 4
```

### 输出

```
1728
```

# 题解

## 作者：ztxtjz (赞：2)

## 【题意】
有$n$个点，每个点通向另一个点（未知），现在有两个要求：

$1$.从$1$到$k$的任意一点出发可以走到$1$点

$2$.从$k+1$到$n$的任意一点出发走不到$1$点

问满足条件有多少种方案。
## 【思路】
**分类讨论**

①$1$到$k$上的点

数学不好只能手动模拟，举几个例子找规律。

Ⅰ $k=1$,一种方案

$1→1$

Ⅱ $k=2$，两种方案

$1→1,2→1$

$1→2,2→1$

Ⅲ $k=3$，九种方案

$1→1,2→1,3→1$

$1→1,2→1,3→2$

$1→1,2→3,3→1$

$1→2,2→1,3→1$

$1→2,2→3,3→1$

$1→2,2→1,3→2$

$1→3,2→1,3→1$

$1→3,2→1,3→2$

$1→3,2→3,3→1$


找规律可知，方案数为$k^{k-1}$。

②$k+1$到$n$上的点

任意一点无法走到$1$，则这些点可以指向$k+1$到$n$上的任意一点，于是有每个点有$n-k$个选择，方案数为$(n-k)^{n-k}$。

所以总方案数为两方案数乘积，为$k^{k-1}*(n-k)^{n-k}$。

考虑到数据较大，使用快速幂。
## 【代码】
```cpp
#include <cstdio>
#define ll long long
ll n,k,mod=1e9+7;
inline ll fpow(ll x,ll n)
{
    ll ret=1;
    for(;n;n>>=1,x=x*x%mod) if(n&1) ret=ret*x%mod;
    return ret;
}
int main()
{
	scanf("%lld%lld",&n,&k);
	printf("%lld",(fpow(k,k-1)*fpow(n-k,n-k))%mod);
	return 0;
}
```

---

## 作者：mxjz666 (赞：1)

**本题可以分为两种情况的乘积：**

对于 $1$ 到 $k$ 号点。他的答案是 $k^{k-1}$ 种方案。

对于 $k+1$ 到 $n$ 号点，他的答案是
 $(n-k)^{n-k}$ 种方案。
 
 再根据乘法原理，得出最终答案为 $k^{k-1}\times(n-k)^{n-k}$ 。

本题可用快速幂实现。
### 简单的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
int ksm(int a,int b){
	int c=1;
	for(;b;b>>=1){
		if(b&1){
			c=c*a%mod;
		}
		a=a*a%mod;
	}
	return c;
}
signed main(){
	int n,k;
	scanf("%lld%lld",&n,&k);
	printf("%lld",ksm(k,k-1)*ksm(n-k,n-k)%mod);
	return 0;
}
```

---

## 作者：orpg (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/CF288B)
### 题目梗概
题目给你 $n$ 个点，有给你一个正整数 $k$。使得 $1 \sim k$ 任意一点都可以到达 $1$。$k+1 \sim n$ 的点都不能到 $1$。
### 题意分析
对于 $1 \sim k$ 的区间而言不难发现这里的种类数就是 $k^{k-1}$（数学较弱的同学可以手模数据）。

对于 $k+1 \sim n$ 的区间，因为这其中的任意数都不能到 $1$，所以他们都不能到 $1 \sim k$，则方案数就是 ${(n-k)}^{n-k}$。

根据小学的乘法原理，总方案数就是 $k^{k-1} \times {(n-k)}^{n-k}$。
### 上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,k,mod=1e9+7;
ll ksm(ll a,ll b){
	ll ans=1;
	while(b){
		if(b&1) ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans%mod;
}//快速幂
main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
	cin>>n>>k;
    ll ans=ksm(k,k-1)*ksm(n-k,n-k)%mod;
	cout<<ans<<'\n';
	return 0;
}

```


---

## 作者：ademik (赞：0)

#### 题意 :
有 $n$ 个点，每个点有一条出边。
要求前 $k$ 个点能走到 $1$ 号点，其他点不能走到 $1$ 号点，问方案数。

#### 分析 :

_这道题应该是考察语文阅读能力吧_  

首先强调一点:点上的编号可以相同，也就是说，你可以将所有点都指向一个节点。
本题实际上是要让前 $k$ 个点形成一个基环树(内向树)，而其他点随意组合，只要保证不指向前 k 个节点即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/ake8w6mv.png)

对于前 $k$ 个节点，每个点因为必须连接 $1$ 号节点，所以每个点一共有 $k − 1$ 个其它的节点可以选择，所以前 $k$ 个节点可能有 $k ^ {k − 1}$ 种可能。
  
采用递推的方式也可以得出结论。
> $k = 2$ 方案数为 2   
> $k = 3$ 方案数为 9   
> $k = 4$ 方案数为 64  
> 猜测方案数应为 $k ^{k - 1}$

对于后 k 个点，每个点的值就可以是 $[k + 1, n]$ 中的任意值，所以方案数为 $(n - k) ^{(n - k)}$。 

故而答案为 $(n - k) ^{(n - k)} + k ^ {k - 1}$ 。  
由于 $1 \le n \le 10^{18}$，故而用快速幂处理即可。

#### Code :

```cpp
using namespace std;
typedef unsigned long long i64;
const int N = 1e5 + 50, Mod = 1e9 + 7;
i64 n, ki, ans, p;
i64 xxx(i64 x, i64 y) // 龟速乘
{
	i64 now = 0;
	while(y) {
		if(y & 1) now = (now + x) % Mod;
		x = (x + x) % Mod;
		y >>= 1;
	}
	return now;
}
i64 qpow(i64 x, i64 k)
{
	i64 now = 1;
	while(k) {
		if(k & 1) now = xxx(now, x);
		x = xxx(x, x);
		k >>= 1;
	}
	return now;
}
int main()
{
	ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >>n >>ki;
	ans = qpow(ki, ki - 1);
	(ans *= qpow(n - ki, n - ki)) %= Mod;
	cout <<ans;
	return 0;
}
```

---

## 作者：Milthm (赞：0)

## CF288B 题解

### 题目解法

拿到题目，可以用分类讨论的方法来做。

首先，对于 $1∼k$ 号节点，一共有 $k$ 个点，每个点因为必须连接 $1$ 号节点，所以每个点一共有 $k-1$ 个其它的节点可以选择，所以 $1∼k$ 号节点可能有 $k^{k-1}$ 种可能。

接下来，对于 $(k+1)∼n$ 号节点，一共有 $n-k$ 个节点，每个点有 $n-k$ 种选择，所以一共有 $(n-k)^{n-k}$ 种可能。

根据乘法原理，两数相乘，就是最后的结果。

### AC代码

注释不加了，大家都能看懂。

```cpp
#include<iostream>
#define int long long
using namespace std;
int n,k,ans=1,mod=1e9+7,cnt=1;
signed main(){
    cin>>n>>k;
    for(int i=1;i<k;i++)ans=ans*k%mod;
    for(int i=1;i<=(n-k);i++)cnt=cnt*(n-k)%mod;
    cout<<ans*cnt%mod;
    return 0;
}
```


---

## 作者：AC_love (赞：0)

找规律即可。

首先看前一半 $1 \sim k$ 这一部分的答案。

显然每个点都可以和另外 $k - 1$ 个点相连，而一共有 $k$ 个点，因此方案数为 $k^{k - 1}$。

再来看后一半，不难发现每个点可以和后 $n - k$ 个点中任意一个点相连，因此方案数为 $(n - k)^{n - k}$。

不难发现答案就是 $k^{k - 1} \times (n - k)^{n - k}$。

然后代码实现就很简单了。

[点我查看代码](https://codeforces.com/contest/289/submission/233749643)

---

