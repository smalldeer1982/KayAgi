# Malek Dance Club

## 题目描述

As a tradition, every year before IOI all the members of Natalia Fan Club are invited to Malek Dance Club to have a fun night together. Malek Dance Club has $ 2^{n} $ members and coincidentally Natalia Fan Club also has $ 2^{n} $ members. Each member of MDC is assigned a unique id $ i $ from $ 0 $ to $ 2^{n}-1 $ . The same holds for each member of NFC.

One of the parts of this tradition is one by one dance, where each member of MDC dances with a member of NFC. A dance pair is a pair of numbers $ (a,b) $ such that member $ a $ from MDC dances with member $ b $ from NFC.

The complexity of a pairs' assignment is the number of pairs of dancing pairs $ (a,b) $ and $ (c,d) $ such that $ a&lt;c $ and $ b&gt;d $ .

You are given a binary number of length $ n $ named $ x $ . We know that member $ i $ from MDC dances with member ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF319A/99db469180d6ab11deff381b4df066112345cbb1.png) from NFC. Your task is to calculate the complexity of this assignment modulo $ 1000000007 $ $ (10^{9}+7) $ .

Expression ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF319A/a0b0fe9e9428287337c0277ea02ca07fcf0a01a7.png) denotes applying «XOR» to numbers $ x $ and $ y $ . This operation exists in all modern programming languages, for example, in C++ and Java it denotes as «^», in Pascal — «xor».

## 样例 #1

### 输入

```
11
```

### 输出

```
6
```

## 样例 #2

### 输入

```
01
```

### 输出

```
2
```

## 样例 #3

### 输入

```
1
```

### 输出

```
1
```

# 题解

## 作者：HanPi (赞：1)

[**CF319A Malek Dance Club**](https://www.luogu.com.cn/problem/CF319A)

---
* Update 8/26
添加更详细的解释
---

在这里提供一种递推/递归做法。

观察题目，发现给出的 `x` 是以二进制形式的，不难想到把 $1$ ~ $2^n-1$ 用二进制表示出来：

```
---|-----
   |
 0 | ...
   |
---|-----
   |
 1 | ...
   |
---|-----
```

可以发现，在这 $2^n$ 个数中，前 $2^{n-1}$ 个数的首位均为 $0$，后 $2^{n-1}$ 个数的首位均为 $1$。

由异或的规则可以得出以下结论：

1. 当 $x$ 首位为 $0$ 时，原先首位为 $0$ 的仍为 $0$，首位为 $1$ 的仍为 $1$，因此 $1$~$2^n-1$ 中的逆序对的数量等于 $1$~$2^{n-1}-1$ 中的逆序对数量加上 $2^{n-1}$~$2^n-1$ 中的逆序对数量之和。又因为这些数是从小到大依次排列且差为 $1$ ，所以在不看首位的情况下这两部分是一样的，这表明这两部分在异或后的逆序对数是相等的，在计算时可以直接计算一部分然后乘二。
2. 当 $x$ 首位为 $1$ 时，原先首位是 $0$ 的会变成 $1$，首位是 $1$ 的会变成 $0$。显而易见的，异或后前一半的数一定会大于后一半。这恰好满足了逆序对的要求，因此该情况除了包含同 情况一 一样的逆序对外，还会新产生 $2^{n-1}\times2^{n-1}=2^{2\times(n-1)}$ 对逆序对（乘法原理）。

综上，如果设序列 $0,1,2,...,2^n-1$ 对 $n$ 位二进制 $x$ 异或后的逆序对数量为 $f(n,x)$，$x$ 剔除首位后为 $g(x)$，首位为 $h(x)$。

那么有：
$f(n,x)=\begin{cases}0&n=1\text{ 且 }x=0\\1&n=1\text{ 且 }x=1\\2\times f(n-1,g(x))&h(x)=0\\2^{2\times(n-1)}+2\times f(n-1,g(x))&h(x)=1\end{cases}$

实际上，由于我们读入的就是 $x$ 的二进制形式，我们可以在递归/递推时很方便的用当前处理到的 $x$ 的位置来推出 $f(n,x)$ 所需要的 $n,g(x)$ 和 $h(x)$ 。

由于数据规模较小，使用递归、递推均可，在这里提供递归版的代码。

```
#include <stdio.h>
#include <string.h>
unsigned long long p2[200];
char x[200];
int len;
const unsigned long long MOD=1e9+7;
unsigned long long func(int pos)
{
    // 传入当前 x 的首位位置可以推出当前的 n=len-pos
    if(pos==len-1)
    {
    	// n==1
        return x[pos]=='1';
    }
    if(x[pos]=='0')
    {
        return ((func(pos+1)%MOD)*2)%MOD;
    }
    return (p2[2*(len-pos-1)]+((func(pos+1)%MOD)*2)%MOD)%MOD;
}
int main()
{
    p2[0]=1;
    scanf("%s",&x);
    len=strlen(x);
    for(int i=1;i<=len*2;++i)
        p2[i]=(p2[i-1]*2)%MOD; // 预处理 2 的幂
    printf("%llu",func(0));
    return 0;
}

```

---

## 作者：NusGhy (赞：1)

### 题意简述



给你一个$n$位的二进制串$x$，要求将$0$ 至 $2^n-1$的数全部异或上$x$，求新产生的数列中逆序对的个数。


------------

### 思路
   


#### 暴力
$n≤100$，如果全部异或上$x$，再求逆序对，时间复杂度为$O(2^n×n)$，很明显是不可行的。
#### 正解
我们先来观察一下能形成逆序对的的一对数的特征。  
  
假设给定的$x$是这样的：
![](https://cdn.luogu.com.cn/upload/image_hosting/7l5mv8dc.png)
然后下面是一对异或上$x$之后会产生逆序对的数$a, b$。   
  
原本：
![](https://cdn.luogu.com.cn/upload/image_hosting/3oow3t1k.png)
异或后
![](https://cdn.luogu.com.cn/upload/image_hosting/7j7tjeva.png)  
为什么会产生逆序对呢？    
  
容易发现，**原本第四位上的数，$a$是$0$，$b$是$1$，在异或上$x$在第四位上的$1$后，$a$变成了$1$，$b$变成了$0$。**
  
**由此我们可以总结出能产生逆序对的一对数$(a, b)$的特征：**   
（将数从左至右给每个数位编上$1$至$n$的编号）

- 第$1$至$i - 1$位完全一致  
- 第$i$位上，$x$为$1$，$a$为$0$，$b$为$1$。
  
由于有第一条性质的存在，每对数所对应的$i$都至多只有$1$个。  
如果枚举每个$i$，可以做到不重不漏地找出每个逆序对。
  
对于每个 $i$ ( $x$ 的第 $i$ 位为 $1$)，分三步确定总共有多少对逆序对。  
  
  1、对于第$1$至$i - 1$位，要求两个数在这些位置上的数完全一致，所以每一位上的数有两种可能，总共的方案数为$2^{i-1}$种。 
    
  2、对于第$i$位，只有一种可能。
    
  3、对于第$i + 1$至$n$位，不做要求，每个数分别有$2^{n - (i + 1) + 1}$种可能，所以总共有$4^{n - i}$种可能。
  
所以，每个$i$ ( $x$ 的第 $i$ 位为 $1$) 能够产生的逆序对总共有 $2^{i-1}×4^{n - i}$ 个。
  
根据加法原理，只需要把每个$i$的贡献累加到答案里即可。

---
  
### 实现

完整代码如下：
```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const ll mod = 1000000007;

string x;
ll ans, n;

ll powmod(ll x, ll y, ll mod)
{
	if(y == 1) return x % mod;
	if(y == 0) return 1 % mod;
	ll next = powmod(x, y / 2, mod);
	if(y % 2) return ((x * next) % mod * next) % mod;
	else return (next * next) % mod;
}

int main()
{
    cin>>x;
	n = x.length();
	x = "?" + x;
    //使x从下标1开始。
	for(int i = 1; i < x.length(); i ++)
	{
		if(x[i] == '1')
		{
			ans += powmod(2, i - 1, mod) * powmod(4, n - i, mod);
            //注意此处不能用cmath库里的pow函数，会爆long long，需要手写快速幂或者预处理出2的1至100次幂取模后的值。
			ans %= mod;
		}
	}
	cout<<ans<<endl;
	//system("pause");
    return 0;
}
```
---
#### Thank you for watching!

---

## 作者：yanxu_cn (赞：0)

## 做法

思维题。

注意到显然每一位是什么对其他位的答案贡献无影响。

又发现字符 `0` 对答案无影响，故直接考虑 `1` 的贡献就可以了。

> 我们记与串 $x$ 长度相等且全为 `0` 的串为基准串，显然基准串最后生成的数列是单调的；记串 $x$ 长度为 $n$。

考虑字符 `1`。我们注意到，如果从低到高第 $i$ 位（记最低位是第 $0$ 位）是 `1` 的话，就相当于是将基准串中 $2^{n-i-1}$ 组的前 $2^{i}$ 个数与后面相邻的 $2^{i}$ 个数整体交换了一下位置。运用逆序对芝士可知，对于每一组，我们要交换的次数为 $\displaystyle \frac {2^{i}\times2^{i}}{2}$ 即 $2^{2i-1}$ 次。故这个字符 `1` 的总贡献为 $2^{n+i-2}$。

由于输入是从高到低输入的，所以输入的第 $j$ 位（记首位为第 $0$ 位）对应上文所说的第 $n-i-1$ 位。输入串的第 $j$ 位如果是 `1` 则贡献为 $2^{2n-j-1}$。

Tips：实现 $2$ 的乘方时，就算使用 `unsigned __int128` 这个类也不过可以存储 $2^{128}$ 以内的数据，对于此时指数最高为 $200$ 的情况位运算无能为力。但是由于指数量级并不大，我们可以预处理出乘方。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr long long mod=1e9+7;
int dat[300];
void init()
{
	dat[0]=1;
	for(int i=1;i<=200;i++)
	dat[i]=dat[i-1]*2%mod;
}
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	string s;
	init();
	long long ans=0,n;
	cin>>s;
	n=s.length();
	for(int i=0;i<n;i++)
	{
		if(s[i]=='1')
		{
			ans+=dat[(n<<1)-i-2];
			ans%=mod;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Leap_Frog (赞：0)

考虑从高往低考虑每一位的贡献。  

如果当前位是 0，那么对逆序对没有贡献。  

然后我们考虑 1 的贡献。  

```
       /
      /
     /
    /
   /
  /
 /
/
```

假设有一个串为 `111`，我们手模。  
发现第一个 1 之后会把它变成这样

```
   /
  /
 /
/
       /
      /
     /
    /
```
多了 $2^{n-1}\times2^{n-1}\times 2^{0}$ 个逆序对。  
前两个 $2^{n-1}$ 代表的是被移动的长度，后面那个下一步就知道是干什么用的了。  

```
 /
/
   /
  /
     /
    /
       /
      /
```
相比刚才，我们多了的逆序对是 $4^{n-2}\times2^{1}$ 个。  
后面的 $2^1$ 形象理解就是上上图中有多少段。  

所以如果第 $i$ 位为 $1$ 那么就会贡献 $2^{n\times2-i-1}$。  
直接暴力统计即可，我直接搞了个快速幂。  
```cpp
//愿你有一天能和你重要的人重逢。
#include<bits/stdc++.h>
using namespace std;const int P=1000000007;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<'0'||c>'9';c=getchar()) if(!(c^45)) f=1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	if(f) x=-x;
}
int n,r;char c[105];
inline int ksm(int x,int q) {int r=1;for(;q;q>>=1,x=1ll*x*x%P) if(q&1) r=1ll*r*x%P;return r;}
int main()
{
	scanf("%s",c+1),n=strlen(c+1),r=0;
	for(int i=1;i<=n;i++) if(c[i]&1) r=(r+1ll*ksm(2,n+n-i-1))%P;
	return printf("%d\n",r),0;
}
```

---

