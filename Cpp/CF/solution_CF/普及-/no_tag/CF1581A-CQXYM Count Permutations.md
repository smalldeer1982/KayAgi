# CQXYM Count Permutations

## 题目描述

CQXYM is counting permutations length of $ 2n $ .

A permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

A permutation $ p $ (length of $ 2n $ ) will be counted only if the number of $ i $ satisfying $ p_i<p_{i+1} $ is no less than $ n $ . For example:

- Permutation $ [1, 2, 3, 4] $ will count, because the number of such $ i $ that $ p_i<p_{i+1} $ equals $ 3 $ ( $ i = 1 $ , $ i = 2 $ , $ i = 3 $ ).
- Permutation $ [3, 2, 1, 4] $ won't count, because the number of such $ i $ that $ p_i<p_{i+1} $ equals $ 1 $ ( $ i = 3 $ ).

CQXYM wants you to help him to count the number of such permutations modulo $ 1000000007 $ ( $ 10^9+7 $ ).

In addition, [modulo operation](https://en.wikipedia.org/wiki/Modulo_operation) is to get the remainder. For example:

- $ 7 \mod 3=1 $ , because $ 7 = 3 \cdot 2 + 1 $ ,
- $ 15 \mod 4=3 $ , because $ 15 = 4 \cdot 3 + 3 $ .

## 说明/提示

$ n=1 $ , there is only one permutation that satisfies the condition: $ [1,2]. $

In permutation $ [1,2] $ , $ p_1<p_2 $ , and there is one $ i=1 $ satisfy the condition. Since $ 1 \geq n $ , this permutation should be counted. In permutation $ [2,1] $ , $ p_1>p_2 $ . Because $ 0<n $ , this permutation should not be counted.

 $ n=2 $ , there are $ 12 $ permutations: $ [1,2,3,4],[1,2,4,3],[1,3,2,4],[1,3,4,2],[1,4,2,3],[2,1,3,4],[2,3,1,4],[2,3,4,1],[2,4,1,3],[3,1,2,4],[3,4,1,2],[4,1,2,3]. $

## 样例 #1

### 输入

```
4
1
2
9
91234```

### 输出

```
1
12
830455698
890287984```

# 题解

## 作者：vvauted (赞：9)

**这是一道我不会但用数列瞎搞做出来的题，无严谨证明**

## Description
求长度为 $2n$ 的排列 $p$，满足：

+ $p_i <p_{i-1}(i\in[2,i])$ 的 $i$ 的个数不少于 $n$ 个
+ 排列中元素不重复，且 $p_i \in[1,2n]$

## Solution

首先写一个暴力，可得到 $n \in[1,5]$ 的 $ans$：

$$ans =\{1,12,360,20160,1814400\}$$

发现 $ans _i$ 总是 $ans_{i-1}$ 的倍数，可以求出 $\frac{ans_i}{ans_{i-1}}$ 这样一个序列 $a$）：

$$a=\{12,30,56,90\}$$

再对 $a$ 差分得到 $b$：

$$b=\{18,26,34\}$$

再次差分得到 $c$： 

$$c=\{8,8,8\}$$

发现 $c$ 中全是 $8$ ，则有：

$$b_{i} =b_{i-1} +8$$



则可以循环求得 $a,b,c$ 序列，那么 $ans$ 自然也可以求出，

又因为有多组查询，即可 $O(n)$ 算出 $ans$ 序列，每次 $O(1)$ 查询即可

注： 运算中多模
## Code

```cpp
#include <stdio.h>
#define Maxn 100005
const int mod = 1e9 + 7;
 
long long int dp[Maxn];
 
int main() {
	int n, T;
	scanf("%d", &T);
	
	dp[1] = 1;
	for(int i = 2, j = 12, k = 18; i <= 100000; ++ i, j = (k + j) % mod, k = (k + 8) % mod) {
		dp[i] = (dp[i - 1] * j) % mod;
	}
	
	while(T --) {
		scanf("%d", &n);
		printf("%lld\n", dp[n]);
	}
}

```






---

## 作者：vectorwyx (赞：2)

记一个排列的值为满足 $p_i<p_{i+1}$ 的 $i$ 的数量，考虑为什么要求排列的值 $\ge n$ 而不是 $>n$。显然一个值为 $i$ 的排列倒过来会得到一个值为 $2n-i$ 的排列，所以把所有值 $<n$ 的排列划到一个集合，值 $\ge n$ 的排列划到另一个集合，这两个集合构成双射关系，每个集合的大小为 $\frac{n!}{2}$。

代码如下（之前代码放错了，麻烦管理员大大重新审核一下qwq）：
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
#include<queue>
#include<map>
#define int ll
#define pb push_back
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define db double
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;
inline int read(){int x=0,fh=1; char ch=getchar(); while(!isdigit(ch)){if(ch=='-') fh=-1; ch=getchar();} while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0'; ch=getchar();} return x*fh;}

const int N=1e6+5,qlr=1e9+7;

void solve(){
	int n=read(),ans=1;
	fo(i,3,2*n) ans=ans*i%qlr;
	cout<<ans<<endl;
}

signed main(){
	int T=read();
	while(T--) solve(); 
	return 0;
}
/*
-------------------------------------------------
*/



```


---

## 作者：C_S_L (赞：0)

一道思维题。

首先可以打表找规律，发现答案为 $\dfrac{(2n)!}{2}\bmod10^9+7$ 。

证明如下：

为了方便，对于一个长度为 $2n$ 排列 $p$ ，令 $count(p)=\left(\sum\limits_{i=1}^{n-1}\begin{cases}1&p_i< p_{i+1}\\0&p_i> p_{i+1}\end{cases}\right)$ 。

我们设满足 $count(p)\geqslant n$ 的排列共 $x$ 个。

将这 $x$ 个数列反转。

设排列 $p$ 反转后得到的排列为 $q$ 。

显然，$count(p)+count(q)=n-1$ 。

故反转后得到的是 $x$ 个 $count(p)<n$ 的排列。显然，这些排列互不相同。

所以，在所有长度为 $2n$ 的排列 $\text\{{a_{(2n)!}}\}$ 中，$count(a_i)\geqslant n$ 的排列和 $count(a_i)<n$ 的排列是两两对应的。

所以 

$\begin{aligned}2x&=(2n)!\\x&=\dfrac{(2n)!}{2}\end{aligned}$ 

综上，在所有长度为 $2n$ 的排列 $\text\{{a_{(2n)!}}\}$ 中，满足 $count(a_i)\geqslant n$ 的排列共有 $\dfrac{(2n)!}{2}$ 个。

记得要 $\bmod10^9+7$ 。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD=(1e9)+7;
int T;
ll n;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%lld",&n);
		ll ans=1;
		for(ll i=3;i<=2*n;++i){
			ans=(ans*i)%MOD;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：phigy (赞：0)

问你有多少 $1$ 到 $2n$ 的排列满足 $a_i<a_{i+1}$ 个数 $\ge n$。

满足 $a_i<a_{i+1}$ 个数 $\ge n$ 的 $1$ 到 $2n$ 的排列个数与 满足 $a_i<a_{i+1}$ 个数 $< n$ 的 $1$ 到 $2n$ 的排列个数相同。

因为对于一个满足 $a_i<a_{i+1}$ 个数 $\ge n$ 的 $1$ 到 $2n$ 的排列 $a$，我们取 $b_i=2n-a_i+1$ 那么 $b$ 是一个满足 $a_i<a_{i+1}$ 个数 $< n$ 的 $1$ 到 $2n$。

且所有满足 $a_i<a_{i+1}$ 个数 $\ge n$ 的 $1$ 到 $2n$ 的排列与 满足 $a_i<a_{i+1}$ 个数 $< n$ 的 $1$ 到 $2n$ 的排列一一映射。

因此满足 $a_i<a_{i+1}$ 个数 $\ge n$ 的 $1$ 到 $2n$ 的排列个数就是$1$ 到 $2n$ 的排列个数的一半。

$1$ 到 $2n$ 的排列个数就是 $(2n)!$。

题目要求 $\mod 10^9+7$。

手算便可得出 $2$ 在 $\mod 10^9+7$ 下的乘法逆元是 $5\times 10^8+4$。

```cpp
#include <iostream>
 
using namespace std;
 
int mod=1000000007;
int t;
unsigned long long a[1000005];
 
int main()
{
    int i,j,k;
    a[1]=2;
    for(i=2;i<=1000000;i++)
    {
        a[i]=a[i-1]*(i*2-1)%mod*(i*2)%mod;
    }
    cin>>t;
    for(i=1;i<=t;i++)
    {
        int x;
        cin>>x;
        cout<<a[x]*500000004%mod<<endl;
    }
}
```


---

## 作者：luyiyang0830 (赞：0)

## 题目大意
给定正整数 $n$，求有多少个 $1$ 到 $2n$ 的排列满足一个数小于它后面的那个数的位数的总个数不少于 $n$。
## 思路
设该排列为 $p$，满足前一位小于后一位的位数为 $k$。我们可以令 $1$ 到 $2n$ 的排列 $q$，满足 $q_i=2n-p_i(1\le i\le 2n)$。
$$\therefore[p_i<p_{i+1}]+[q_i<q_{i+1}]=2n-1(1\le i<2n)$$
$$\therefore[q_i<q_{i+1}]=2n-k-1(1\le i<2n)$$
也就是说，排列 $p$ 和排列 $q$ 中必有一个是满足条件的，因此最后的答案就是排列总数的一半，即 $ans=\dfrac{1}{2}(2n)!$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,f[200010];
signed main(){
    f[1]=1;
    for(int i=2;i<=200000;i++) f[i]=((i<<1)-1ll)*f[i-1]%1000000007*(i<<1)%1000000007;//递推算阶乘
    cin>>t;
    while(t--){
        cin>>n;
        cout<<f[n]<<endl;//计算结果
    }
    return 0;
}
```

---

## 作者：max67 (赞：0)

## 题意

题目翻译：

给定一个长度为 $2n$ 的[排列](https://baike.baidu.com/item/%E6%8E%92%E5%88%97/7804523)。我们规定一个排列是好的当且仅当满足一下条件：

>对于排列里的每个元素 $P_i$，满足 $P_i<P_{i+1}$ 的 $i$ 数量不少于 $n$。

给你 $n$，让你统计所有长度为 $2n$ 的排列中，被称为好的的排列有多少个。答案对 $1e9+7$ 取模。

输入格式：

第一行是一个整数 $t$。表明数据的组数。

每组数据中只包含一行中一个整数 $n$。

输出格式：

对于每组数据，输出一行答案。

数据规模与约定：

 $t \ge 1$  
 
 $n \le 1e5$，$\sum n \le 2e5$
 
## 题解

结论题。


我们考虑一个排列 $P$，排列里的元素为 $P_1,P_2......P_{2n}$，他满足条件的 $i$ 数量有 $k$ 个。（其中 $k<n$）

那么我们规定一个变换：$Q_i=2n-P_i+1$。则原本不满足条件的 $i$（$P_i<P_{i+1}$）经过变化之后满足条件（$2n-P_i+1>2n-P_{i+1}+1$）。满足条件的 $i$ 也变成不满足条件的。

那么在变换之后，我们得到的排列 $Q$ 满足条件的数量有 $2n-k-1$ 个（$2n-k-1 \ge n$）。那么一个不合法的排列在进行一个变换之后会变成一个合法的排列。

我们再观察我们规定的变换 $Q_i=2n-P_i+1$，发现对于每个唯一的 $P_i$，$Q_i$ 的值也是唯一的。因为排列里的数没有重复，且排列之间互不相同。所以每个排列对应的映射也是唯一的。

所以一个不合法排列的变换是唯一的，也是满足题目条件的，所以在排列之中与这个不合法的排列的变换相同的排列有且仅有一个。

同理，一个合法的排列的变换也对应着唯一的一个不合法排列。

如此看来，合法的排列与不合法的排列个数相等。

> 假设有一个合法排列多出来。他可以经过上面的变换找到另一个不合法的排列，满足题设。那么不合法的序列没有多一个出来，与自身矛盾。

那么他们的个数就是总排列个数除以2。

然而总排列个数我们都会求，这边简单讲下原理：

>对于一个长度为 $n$ 的序列，我们有 $n$ 个元素。第一个位置可以填 $n$ 个元素中一个。第二个位置由于第一个位置填了一个元素（不能重复），所以只能填 $n-1$ 个元素。那么以此类推，根据[乘法原理](https://baike.baidu.com/item/%E4%B9%98%E6%B3%95%E5%8E%9F%E7%90%86)可得，总排列个数为：$n!$。

（感叹号表示[阶乘](https://baike.baidu.com/item/%E9%98%B6%E4%B9%98/4437932)。）

那么，答案就为$\frac{n(n-1)}{2}$。

~~写得丑丑的~~代码如下：

```

#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
const int N=2e5+1e3;
int fac[N];
signed main()
{
    int n;
    scanf("%lld",&n);
    fac[2]=1;
    for(int i=3;i<=2e5+1;i++)fac[i]=1ll*fac[i-1]*i%mod;
    while(n--)
    {
        int m;
        scanf("%lld",&m);
        printf("%lld\n",fac[m*2]%mod);
    }
    return 0;
}
```

---

