# TLE - Time Limit Exceeded

## 题目描述

Given integers N (1 ≤ N ≤ 50) and M (1 ≤ M ≤ 15), compute the number of sequences a $ _{1} $ , ..., a $ _{N} $ such that:

- 0 ≤ a $ _{i} $ < 2 $ ^{M} $
- a $ _{i} $ is not divisible by c $ _{i} $ (0 < c $ _{i} $ ≤ 2 $ ^{M} $ )
- a $ _{i} $ & a $ _{i+1} $ = 0 (that is, a $ _{i} $ and a $ _{i+1} $ have no common bits in their binary representation)

## 样例 #1

### 输入

```
1
2 2
3 2```

### 输出

```
1```

# 题解

## 作者：hs_black (赞：4)

latex可能挂了, 建议到博客内查看, [戳这里](https://www.cnblogs.com/Hs-black/p/12293480.html)

## 高维前缀和

众所周知, FWT可以轻松的算出高维前缀和

本题题解:

考虑状压$dp$(~~题目都说了$2^M$那就状压了~~)因为$\%c[i]$和$\&a[i-1]$这两个操作都和具体的数值有关

$F[i][j]$表示枚举到$i$, 第$i$个数填$j$有多少种方案
$$
F[i][j] = \begin{cases} 0~~~~~~~~~~~ j~\%~c[i] ==0\\\\\displaystyle \sum_{k\&j=0} F[i-1][j]\end{cases}
$$
这样显然是不行的, 需要一点优化

转移时发现每一个合法的k都是$j \bigotimes (2^M-1)$的子集, 如果能记个子集前缀和那就再好不过了, FWT可以帮我们完成这件事, 一遍FWT_or算出子集和, 给出一份~~易于背诵~~的代码吧 [戳这里](https://www.cnblogs.com/Hs-black/p/12271681.html)

完整代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define ll long long
using namespace std;
const int P = 1000000000;
template <typename T>
void read(T &x) {
    x = 0; bool f = 0;
    char c = getchar();
    for (;!isdigit(c);c=getchar()) if (c=='-') f=1;
    for (;isdigit(c);c=getchar()) x=x*10+(c^48);
    if (f) x=-x;
}

ll ans = 0, n, m;
void FWT_or(ll *f) {
	for (int i = 1, p = 2; i < m; i <<= 1, p <<= 1) 
		for (int j = 0; j < m; j += p) 
			for (int k = 0; k < i; k++) 
				(f[i+j+k] += f[j+k]) %= P;
}

const int N = 55;
ll f[N][(1<<15) + 5], a[N];

int main() {
	int T; read(T);
	while (T--) {
		memset(f, 0, sizeof(f));
		read(n), read(m); m = 1 << m;
		for (int i = 1; i <= n; i++) read(a[i]);
		for (int i = 1; i < m; i++) 
			if (i % a[1]) f[1][i] = 1;
		FWT_or(f[1]);
		for (int i = 2; i <= n; i++) {
			for (int j = 1; j < m; j++) {
				if (j % a[i] == 0) continue;
				f[i][j] += f[i-1][(m-1)^j];
			}
			FWT_or(f[i]);
		}
		cout << f[n][m-1] << endl;
	}
	return 0;
}
```


---

## 作者：龙神哈迪斯 (赞：4)

### 放在前面的话

这是一道很好用来练习高维前缀和的入门题，思维难度低，代码难度低，很简单

### [题目大意](https://www.luogu.org/problemnew/show/SP2829)
给定$n$和n个数$c[i]$，要求构造出一串序列$a[i]$，要求

1.$a[i] \in [0,2^m)$

2.$a[i] \%c[i]!=0$

3.$a[i]$&$a[i+1]=0$

求方案数

### Sol
这$m$的范围这么小，不是摆明了给你状压用的吗？qwq

考虑$f[i][j]$表示选到第$i$个数，第$i$个数为$j$的方案数

然后显然不能直接转移，考虑作高维前缀和的方法

设$s=2^m-1$

$f[i][j]=f[i-1][j xor s] $

然后再将所有$j$状态的超集加上，这样就可以做到不重不漏了

注意:尤其是在枚举超集做前缀和时，一定要先枚举位数再枚举值，否则会像本人一样调半小时都调不出来？这是为什么呢？

因为先枚举值的话，只会修改顶多为一位的状态，也就修改个数顶多是$(m+1)$，但是先枚举位数就能包含之前修改过的若干位状态，修改个数为$2^m$，所以这才是对的(其实这也是一种套路了)

### code

然后是愉快的上代码时间

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int mod=1e9;
const int _=52;
inline int read()
{
	char ch='!';int z=1,num=0;
	while(ch!='-'&&(ch<'0'||ch>'9'))ch=getchar();
	if(ch=='-')z=-1,ch=getchar();
	while(ch<='9'&&ch>='0')num=(num<<3)+(num<<1)+ch-'0',ch=getchar();
	return z*num;
}
int n,m,f[_][(1<<15)+1],c[_];
int main()
{
	int T=read();
	while(T--)
	{
		n=read(),m=read();
		for(int i=1;i<=n;++i)c[i]=read();
		memset(f,0,sizeof(f));
		int s=1<<m,ans=0;
		for(int i=0;i<s;++i)
			if(i%c[1])f[1][i]=1;
		for(int i=2;i<=n;++i)
		{
			for(int j=0;j<s;++j)f[i][j]=f[i-1][j^(s-1)];
			for(int j=0;j<m;++j)
				for(int zt=0;zt<s;++zt)
					if(!(zt&(1<<j)))
						(f[i][zt]+=f[i][zt|(1<<j)])%=mod;
			for(int j=0;j<s;++j)
				if(!(j%c[i]))f[i][j]=0;
		}
		for(int i=0;i<s;++i)
			(ans+=f[n][i])%=mod;
		printf("%d\n",ans);
	}
	return 0;
}

```


---

## 作者：FreeTimeLove (赞：1)

## 一、题意

共有 $T$ 组数据。每组数据给定 $n,m$ 和长度为 $n$ 的数组 $c$，求长度为 $n$ 的数组 $a$ 满足：
1. $\forall i\in [1,n],a_i\in [0,2^m),a_i\bmod c_i\ne 0$
2. $\forall i\in [2,n],a_{i-1}\&a_i=0$

计算满足条件的 $a$ 的个数对 $10^9$ 取模。

$1\le T\le 10,1\le n\le 50,1\le m\le 15,c_i\in[1,2^m]$.

## 二、思路

既然涉及到位运算，我们可以考虑将 $a$ 表示为二进制。那么问题就变成了：

求长度 $len=n\times m$ 的 $01$ 串 $b$ 满足：
1. $\forall i\in[m+1,len],b[i]\&b[i-m]=0$
2. $\forall i\in[1,m],[i\times (m-1)+1,i\times m]\bmod c_{i+1}\ne0$

（$[a,b]$ 表示二进制下第 $a$ 位至第 $b$ 位所表示的数）

发现我们只需记录最后 $m$ 位即可。设 $dp[i][j]$ 表示前 $i$ 位的最后 $m$ 位状态为 $j$ 的方案数。

这里用刷表法，对于每个 $dp[i][j]$，如果 $i$ 是 $m$ 的倍数，先判断 $j$ 是否合法（$j\bmod c_i\ne0$），不合法则赋值为 $0$；
如果合法，分别转移给下一位为 $0$ 与下一位为 $1$ 的状态。

考虑如果下一位为 $0$，$b[i]\&b[i-m]$ 一定等于 $0$，直接转移；如果下一位为 $1$，需要 $b[i-m]=0$，判断 $j$ 的最高位是否为 $1$ 即可.

最终的答案为 $(\sum_{j=0}^{2^m-1}dp[len][j])\bmod10^9$。

### AC code

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
#define ll long long
#define db double
using namespace std;
const int N=1e3+5;
ll read(){
	ll ans=0,f=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')f^=(ch=='-'),ch=getchar();
	while(ch>='0'&&ch<='9')ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
	if(f)ans=-ans;
	return ans;
} 
ll mod=1e9,dp[770][33000];
int o,o2,len,n,m,T,c[60],aa[770];
int main(){
	T=read();
	while(T--){
		ll ans=0;
		n=read(),m=read();
		for(int i=1;i<=n;i++)c[i]=read();
		len=m*n;
		o=(1<<(m-1))-1;
		o2=1<<(m-1);
		memset(dp,0,sizeof dp);
		dp[0][0]=1;
		for(int i=1;i<=len;i++)aa[i]=(i%m==0);
		for(int i=0;i<len;i++){
			int x=c[i/m];
			for(int j=(1<<m)-1;j>=0;j--){
				if(aa[i]&&j%x==0){
					dp[i][j]=0;
					continue;
				}
				while(dp[i][j]>=mod)dp[i][j]-=mod;
				dp[i+1][(j&o)<<1]+=dp[i][j];//下一位为0
				dp[i+1][((j&o)<<1)+1]+=(i>=m&&(j&o2))?0:dp[i][j];//下一位为1
			}
		}
		for(int j=(1<<m)-1;j>=0;j--){
			if(j%c[n]==0)continue;
			ans+=dp[len][j];
		}
		printf("%lld\n",ans%mod);
	}
	return 0;
}
```
### $\text{The End.}$

---

## 作者：syzf2222 (赞：1)

看了一下，几篇题解都是二维数组的dp。

我这里有一维的做法，简单介绍一下，供参考。

转化条件：

$a_i$&$a_{i+1}=0$

等价于$a_i$是$2^m-1-a_{i+1}$的子集。

而利用高位前缀和，我们可以这样枚举子集求前缀和：

```
for(int i=1;i<m;i++)
	for(int j=0;j<(1<<m);j++)
		if((1<<i)&j)f[j]+=f[j^(1<<i)];
```
这段代码的意思是：

枚举每一个二进制位，加上这个维度的值。

但是此题要求的是$2^m-1-a_{i+1}$的子集和。

所以我们在求完后将其翻转，像这样：

```
for(int i=1;i<(1<<m-1);i++)
	swap(f[i],f[(1<<m)-1-i]);
```
最后，如果它不符合$a_i$%$c_i!=0$就将其制0。

像这样：
```
for(int i=0;i<(1<<m);i++)
	if(i%c[j]==0)f[i]=0;
```
那么这道题就讲完了。

具体参照代码：
```
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9;
int f[1000000];
int t,n,m,a[50];
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		for(int i=0;i<(1<<m);i++)
			f[i]=(i%a[1]!=0);
		for(int i=2;i<=n;i++){
			for(int j=0;j<m;j++)
				for(int k=0;k<(1<<m);k++)
					if((1<<j)&k)f[k]=(f[k]+f[k^(1<<j)])%mod;
			for(int j=0;j<(1<<m-1);j++)
				swap(f[j],f[(1<<m)-1-j]);
			for(int j=0;j<(1<<m);j++)
				if(j%a[i]==0)f[j]=0;
		}
		int ans=0;
		for(int i=0;i<(1<<m);i++)
			ans=(ans+f[i])%mod;
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：xh39 (赞：0)

本题解中的所有```^```为**异或**,不为幂次方。

算法:**轮廓线dp。**
## 前置算法

请按顺序学习以下算法。

0.多维数组。

1.递推。

2.动态规划。

3.位运算,状态压缩。

4.轮廓线。
## 位运算
补充本题状态转移涉及到的位运算。

将 $S$ 的第 $j$ 位(从右往左)取反的结果:$S$^$(1<<j-1)$。

判断 $S$ 的第 $j$ 位(从右往左)是否为 $1$:$S$&$(1<<j-1)$。

求$2^{i}$:$1<<i$。

($A$ 为一个条件)当 $A$ 为真时,结果为 $b$,否则结果为 $0$:$A\times b$
## 思路
设 $f[i][j][S]$ 表示选到第 $i$ 个数第 $j$ 位,轮廓线上的状态为 $S$ 的方案数。

若上一个数的状态为 $0$,则此位可以为**‎ $0$ 或 $1$**。

若上一个数的状态为 $1$,则此位**必须**为**‎ $0$‎**。

所以得出结论:**如果异于此位一定可行,而等于此位需 $0$**。

初始状态:将第$-1$行全部**看作 $0$‎** 即可。

统计答案:枚举最后一行最后一个数为 $0,1$,然后枚举状态。

状态转移,初始状态,统计答案的式子见代码。

单组数据的时间复杂度为:$O(n\times m\times2^{m})$。虽然时间被其它算法吊打,但还是能过。
```cpp
#include<iostream>
using namespace std;
long long f[53][17][50005],c[1005];
#define mod 1000000000
void Main(){
	int n,m,i,j,k,ykb;
	long long sum=0;
	cin>>n>>m;
	ykb=1<<m;
	for(i=0;i<n;i++){
		scanf("%lld",c+i);
	}
	for(i=0;i<m;i++){
		for(j=0;j<(1<<i);j++){ //初始化:i位前可以位任意数,而i位之后必须位0。
			f[0][i][j]=1;
		}
	}
	for(i=1;i<n;i++){ //dp过程。状态转移。
		for(j=0;j<ykb;j++){
			f[i][0][j]=(bool)(j%c[i-1])*(f[i-1][m-1][j^(1<<m-1)]+f[i-1][m-1][j]*!(j&(1<<m-1)))%mod;
		}
		for(j=1;j<m;j++){
			for(k=0;k<ykb;k++){
				f[i][j][k]=(f[i][j-1][k^(1<<j-1)]+!(k&(1<<j-1))*f[i][j-1][k])%mod;
			}
		}
	}
	for(i=0;i<ykb;i++){ //统计答案。
		sum=(sum+(f[n-1][m-1][i^(1<<m-1)]+f[n-1][m-1][i]*!(i&(1<<m-1)))*(bool)(i%c[n-1]))%mod;
	}
	cout<<sum<<endl;
}
int main(){
	int t,i;
	cin>>t;
	for(i=0;i<t;i++){
		Main(); 
	}
	return 0;
}
```
Happy new year!

---

