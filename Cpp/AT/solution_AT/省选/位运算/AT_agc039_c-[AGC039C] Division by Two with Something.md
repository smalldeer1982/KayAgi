# [AGC039C] Division by Two with Something

## 题目描述

现在给你一个整数$N$和一个二进制数$X$，对$0 \sim X$之间的每个整数$K$在返回到其原始值之前，需要执行多少次下面的操作：

如果$K$是奇数
	
$K=(K-1) \div 2$
 
如果$K$是偶数

$K=(K \div 2)+2^{N-1}$

当 $K$ 不可能返回原始值不计入操作次数。

## 说明/提示

- $1 \le N \le 2 \times10^5$
- $0 \le X < 2^N$
- $X$是一个长度为$N$的二进制数($X$的数位不足$N$时用前导$0$补齐)
- 所有数字都是整数

例如,$K = 3$时，操作为：1，0，4，6，7，3，所以$K=3$时答案是$6$。

## 样例 #1

### 输入

```
3
111```

### 输出

```
40```

## 样例 #2

### 输入

```
6
110101```

### 输出

```
616```

## 样例 #3

### 输入

```
30
001110011011011101010111011100```

### 输出

```
549320998```

# 题解

## 作者：hard_plan (赞：15)

[题目链接](https://www.luogu.com.cn/problem/AT_agc039_c)

以下称 $k$ 的二进制数构成的串（也就是被操作的串）为原串，如果不足 $n$ 位则在前面补 $0$ 补成 $n$ 位。

首先转化操作，可以理解为将 $k$ 的最后一位取反放在开头并将 $k$ 右移一位。

我们操作一个数会进入一个循环，如

$$110101 \to 011010 \to 101101 \to 010110\to 101011\to 110101$$

而我们求的答案就是在 $[0,x]$ 中每个数所在循环的大小之和。

上面这样写可能有点不好看，那如果我们不右移呢？这样我们最终会形成一个长度为 $2n$ 的 $01$ 串，其中后 $n$ 位为原串，前 $n$ 位为原串取反后的串。

如 $110101$ 生成为 $001010110101$。那么循环内的所有数实际上就是该长度为 $2n$ 串的长度为 $n$ 的子串。

如刚才那个例子：

$$001010[110101]\\ 00101[011010]1\\ 0010[101101]01\\ 001[010110]101\\ 00[101011]0101\\ 0[010101]10101\\ [001010]110101$$

有点类似一个滑动窗口吧。这个循环长度为 $6$，所以说可能存在操作串所在循环长度为 $n$。

我们再举一个例子：

$010$ 生成 $101010$，而它所在循环是 $010\to 101\to 010$长度为 $2$，并不是 $n=3$。

原因是有子串 $1[010]10=101[010],[101]010=10[101]0$，也就是说该 $2n$ 串的循环周期小于 $2n$ 了，使得该串的子串出现重复了。

我们设 $T$ 为这个 $2n$ 串的循环最小正周期。所以有 $T\mid 2n$，而又因为这个串的前 $n$ 位是由后 $n$ 位取反而来的，不相等。因此有 $T\nmid n$。所以可以得出 $T$ 一定是偶数。

再者，画一下图就知道 $\frac{2n}{T}$ 为奇数，不然无法满足 $T\nmid n$。因为如果 $\frac{2n}{T}$ 为偶数，则一定可以将原串（也就是后 $n$ 位）分为 $\frac{2n}{2T}$ 个周期，不满足 $T\nmid n$。

因为 $T$ 是偶数，所以将每个周期拆成 $A+A'$ 两个长为 $\frac{T}{2}$ 的子串。然后有以下推导：

![](https://cdn.luogu.com.cn/upload/image_hosting/jlyhn4tn.png)

再解释一下这个图。我们将每一个周期均分成前后两部分 $A$ 和 $A'$。则最中间的周期的 $A$ 部分会在前 $n$ 位，$A'$ 部分会在后 $n$ 位。而根据这个 $2n$ 串的生成方式，这个周期的 $A'$ 取反得到了第一个周期的子串 $A$。而又因为每一个周期的 $A$ 都相等，所以得出 $A'$ 和 $A$ 可以互相通过取反得到。后 $n$ 位（原串）是由 $A'AA'...A'$ 构成的，所以后 $n$ 位可以拆分成奇数个长度为 $\frac{T}{2}$ 的子串，且相邻子串可以互相通过取反得到。

那么接下来，我们考虑如何统计答案。

首先先枚举 $T$，需要满足 $T\mid 2n$ 且 $T\nmid n$。然后记 $len=\frac{T}{2}$，所以子串 $A'$ 长度为 $len$。

但是原串有大小限制，必须在 $[0,x]$ 之间，这怎么处理呢？

我们想到如果 $A'$ 定了，那么原串就定了。而又因为 $A'$ 是在原串的开头，所以只要 $A'$ 小于输入串的前 $len$ 位，就可以原串就小于输入串。

而当 $A'$ 与输入串的前 $len$ 位相同时，因为 $A'$ 已定，所以直接将整个原串求出再与输入串比较。而这样的 $A'$ 只有一个，所以可以直接暴力判断。

我们设 $k$ 为 $A'$ 对应的二进制串转化为十进制后的值。我们直接让 $A'$ 等于输入串的前 $len$ 位从而生成出原串，然后判断原串与输入串的大小，如果原串不大于输入串，则有 $k+1$ 个 $A'$ 合法（别忘了全 $0$ 串哦）；否则有 $k$ 个 $A'$ 合法。

记  $f_i$ 为 $T=i$ 时合法的 $A'$ 的数量，$f_i$ 求法上一段已给出。

但是还可能重复。如原串长为 $3$，那么合法周期可以是 $2$ 和 $6$，会重复计算。

我们只用最小合法正周期计算答案，所以在用 $i$ 计算答案时，要枚举它的倍数 $j(j\neq i)$，让 $f_j\gets f_j-f_i$。

则最终答案为 $\sum_{T\mid 2n且T\nmid n}T\times f_T$。

通过暴力计算，合法的 $T$ 的个数不超过 $64$，所以时间复杂度能过。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e5+5,mod=998244353;
#define int long long
int n,a[N],f[N],ans,tmp[N];
int read()//快读 
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
signed main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		char w;
		cin>>w;
		if(w=='1') a[i]=1;
	}
	int cnt=0;
	for(int T=2;T<=2*n;T+=2) 
	{ 
		if(n%T==0) continue;
		if((2*n)%T) continue;//找到合法的T 
		int num=0,len=T/2;//num为合法的A'的个数 
		for(int j=1;j<=len;j++) num=(num*2+a[j])%mod,tmp[j]=a[j];
		
		//tmp为 与输入串前len位相同的A' 生成的原串 
		for(int j=len+1;j<=n;j++) tmp[j]=tmp[j-len]^1;
		bool flag=1;
		for(int j=len+1;j<=n;j++)
		{
			if(tmp[j]>a[j]){flag=0;break;}
			if(tmp[j]<a[j]) break;
		}//判断大小 
		num+=flag; //因为要包括00000...所以要改为如果小于等于就+1 
		
		f[T]=(f[T]+num)%mod;
		
		for(int j=2;T*j<=2*n;j++) f[T*j]=(f[T*j]-f[T]+mod)%mod;//容斥 
		
		ans=(ans+f[T]*T)%mod;//统计答案 
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Caro23333 (赞：9)

着实好题，思维有那么一点过程和深度，~~而且还在我能做出来的范围~~

考虑题目中给出的操作，实际上是把当前数在二进制下的最低位取反，再挪到最高位上。觉得取反这个操作有点难处理，于是可以进行转化：在原数$a$后面，接上原数按位取反的结果$\neg{a}$，得到一个数$b$，那么对$a$操作就等价于每次把$b$的最低位挪到最高位，$a$回到原状就等价于$b$回到原状。

那么显然，**操作循环节**长度$T$应该是$b$的长度，也就是$2n$的约数。更进一步，在**字符串的角度来看**，$b$应该具有长度为$T$的循环节。

然而，$T\mid 2n$并不是$T$合法（**即，有可能存在长度为$T$的操作循环节**）的充分条件。假如$T\mid n$，由于$b$具有长度为$T$的循环节，那么$b$的前$n$位和后$n$位应当是完全相同的，和$b$的构造方式矛盾。所以一定有$T\nmid n$。

实际上，$T\nmid n$且$T\mid 2n$是$T$合法的充要条件，因为我们可以进行构造：

注意到满足条件的$T$必定是一个偶数，所以把循环节前后分为两个长为$\frac{T}{2}$的段$p,q$，任意指定$p$并且令$q=\neg{p}$。

由于$T\nmid n$且$T\mid 2n$，$\frac{2n}{T}$一定是一个奇数，所以$b$的前$n$位一定形如$\overline{pqpq\dots qp}$，后$n$位一定形如$\overline{qpqp\dots pq}$，那么就满足了$b$后$n$位恰为前$n$位取反的要求。

所以我们枚举每一个合法的$T$，然后求解有多少个存在长为$T$的循环节的$b$。

在这之中，我们还需要考虑$[0,x]$的限制。令$x$的前$\frac{T}{2}$位对应的二进制数值为$s$。由于我们只需要确定$b$的前$\frac{T}{2}$位，那么只要先令这一部分与$x$的对应部分完全相同，然后构造出$b$的前$n$位，再检查是否在$[0,x]$内即可。如果是，那么当前的计算结果为$s+1$，否则为$s$。

令$f_T$为存在长为$T$的循环节的$b$的数量，发现这仍不是我们最终需要的结果：对于合法的$T_1,T_2$，如果$T_1\mid T_2$，那么$f_{T_2}$中有一部分存在长为$T_1$的循环节，那么它们对最终的答案贡献并不为$T_2$。

针对上述情况我们只需容斥即可：从小到大枚举合法的$i$，对于$i$的所有合法的倍数$j$，让$f_j$减去$f_i$。这样最终剩下的$f_T$就是最小循环节为$T$的$b$的数量。

然后我们只要统计$\sum\limits_{\textrm{T is legal}} Tf_T$即可。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define mod 998244353

using namespace std;
typedef long long ll;
const int MAXN = 400005;
int n,a[MAXN],b[MAXN];
char str[MAXN];
ll f[MAXN];
inline void solve(int x)
{
	ll res = 0;
	for(int i = 1; i<=x/2; i++)
		res = (res*2+a[i])%mod;
	res = (res+1)%mod;
	for(int i = 1, j = 0; i<=n; i += x/2, j++)
		for(int k = i; k<=i+x/2-1; k++)
			b[k] = a[k-i+1]^(j&1);
	bool flag = true;
	for(int i = 1; i<=n; i++)
	{
		if(b[i]>a[i])
			flag = false;
	    else if(b[i]<a[i])
	    	break;
	}
	if(!flag)
		res = (res+mod-1)%mod;
	f[x] = res;
}

int main()
{
	cin >> n >> str+1;
	for(int i = 1; i<=n; i++)
		a[i] = str[i]-'0';
	for(int i = 1; i<=2*n; i++)
		if(2*n%i==0&&n%i!=0)
			solve(i);
	for(int i = 1; i<=2*n; i++)
		if(2*n%i==0&&n%i!=0)
			for(int j = 2*i; j<=2*n; j += i)
				if(2*n%j==0&&n%j!=0)
					f[j] = (f[j]-f[i]+mod)%mod;
	ll ans = 0;
	for(int i = 1; i<=2*n; i++)
		ans = (ans+f[i]*i)%mod;
	cout << ans << endl;
	return 0;
}

```


---

## 作者：WeLikeStudying (赞：1)

用一种有意思的方法证明了其中的性质。
### [题意](https://www.luogu.com.cn/problem/AT_agc039_c)
对于 $0\to x$ 的每个 $n$ 位二进制数，计算如下数值的总和：将最后一个数码取反加到最前，操作多少次回到原数， $n\le 2\times 10^5$ 。

### 分析
考虑一个数码的变化本质上是在干什么，实际上，如果我们不删除最后的数，并且一直向前加数，我们会构造出一个无穷数列，以 $10011101$ 为例：
$$\cdots1001110101100010[10011101]$$
$$\cdots100111010110001[01001110]1$$
$$\cdots10011101011000[10100111]01$$
而我们每次变换只是在进行窗口滑动而已，那么我们研究这个无限数列本身的循环节即可。

设 $t_i$ 为这个无限数列的第 $i+1$ 个数，总结可得：
$$t_i=\begin{cases}\lfloor x/2^i\rfloor\bmod 2&0\le i<n\\1-t_{i-n}&i\ge n\end{cases}$$
易知 $t_{i+2n}=1-t_{i+n}=t_i$ 。

假设存在周期 $T$ 满足 $t_{i+T}=t_i$，则 $T$ 不是 $n$ 的因子，否则 $t_{i+n}=t_{i+n-T}=\cdots=t_i$ ，矛盾。

若 $T$ 为最小正周期， $T$ 为 $2n$ 的因子，此时 $t_{i+n}=\cdots=t_{i+(n\bmod T)}=1-t_i$，故 $t_{i+2(n\bmod T)}=1-t_{i+(n\bmod T)}=t_i$。

所以 $2(n\bmod T)$ 得是 $T$ 的倍数，容易发现：$2(n\bmod T)< 2T$，故 $2(n\bmod T)=T$，也就是说，原串同样满足如下式子：
$$t_i=\begin{cases}\lfloor x/2^i\rfloor\bmod 2&0\le i<\frac T2\\1-t_{i-n}&i\ge \frac T2\end{cases}$$
即原数存在 $a\overline{a}a\overline{a}a\overline{a}a\overline{a}a\overline{a}$ 一样的循环节。

故枚举 $T/2$ 设 $g(T/2)$ 为（不一定最小）周期为 $T$ 的字母个数，容易用 $O(n)$ 时间计算总个数，即构造前几位，判断是否大于 $x$。

设 $f(T/2)$ 为最小周期为 $T$ 的情况，容易发现：
$$g(n)=\sum_{d|n}f(d)$$
从小到大枚举 $d$ 的因子，即可逐个计算出 $f$，最后计算 $\sum_{d|n}2f(d)d$ 即可。

### 代码

```cpp
#include<bits/stdc++.h>
#define up(a,b,c) for(int a=b;a<=c;++a)
const int N=22e4,p=998244353;
using namespace std;
int n,f[N],res;
string x;
string rev(string x)
{
	for(char &z:x)z^='1'^'0';
	return x;
}
int g(int m)
{
	int a=0;
	up(i,0,m-1)a=(a*2+x[i]-'0')%p;
	string b=x.substr(0,m),c;
	up(i,0,n/m-1)c+=b,b=rev(b);
	return (a+(c<=x))%p;
}
int main()
{
	cin>>n>>x;
	up(i,1,n)if(n%i==0&&n%(2*i)!=0)
	{
		f[i]=(f[i]+g(i))%p;
		up(j,2,n/i)f[i*j]=(f[i*j]+p-f[i])%p;
		res=(res+2ll*i*f[i])%p;
	}
	cout<<res;
	return 0;
}
```

---

## 作者：Ether13 (赞：0)

首先考虑操作的特性。

通过手模，可以发现，两种操作本质是把最低位取反，并进行循环移位，如 $\overline{10000}0$ 操作一次会变为 $1\overline{10000}$。而操作 $N$ 次就相当于没有循环移位，且所有位都取反。那么已知操作 $N$ 次相当于将原数每一位取反，那么再操作 $N$ 次就可以将其又翻转回来，也就相当于没有翻转。所以操作数上界是 $2N$。

但是存在操作数小于 $2N$ 的数，如 $101$。其过程是：
$$
0:101\\
1:010\\
2:101\\
3:010\\
4:101\\
5:010\\
6:101\\
\vdots
$$
可以发现其操作次数为 $2$。

所以就要找到操作产生的数的最小循环节。那么前面说了，$2N$ 是其循环节，则 $cnt\mid2N$。而操作 $N$ 次是取反，不可能和原数相同，则 $cnt\nmid N$。则可以枚举每个 $cnt$，然后求在范围内的操作次数是 $cnt$ 的数的个数。

注意到 $cnt\mid2N,cnt\nmid N$ 所表示的含义是 $cnt$ 中 $2$ 的幂次比 $N$ 中 $2$ 的幂次多一。也就是说 $\frac{cnt}{2}\mid N,2\nmid \frac{2N}{cnt}$。而每操作 $cnt$ 次就和原来一样，操作 $\frac{cnt}{2}$ 次相当于原数取反。则答案为 $cnt$ 的二进制数应当形如：
$$
abab\cdots aba
$$
其中 $a$ 为一个长度为 $\frac{cnt}{2}$ 的二进制数，$a\oplus b=2^{\frac{cnt}{2}}-1$。

那么现在就好做了，枚举 $cnt$，然后找 $X$ 前 $\frac{cnt}{2}$ 位表示的数，设其为 $P$，则 $a=0\sim P-1$ 是一定可以被表示的，check 一下 $a$ 是否可以等于 $P$ 即可，当然最终还要容斥一下。复杂度 $O(\sum_{d|N,2d\nmid N}n)<O(Nd(N))$。

code：

```c++
for(int i=1;i*i<=n*2;i++){
	if((2*n)%i==0){
		int p=i;
		if(n%p!=0) d[++cnt]=p;
		if(i*i==n*2) continue;
		p=2*n/i;
		if(n%p!=0) d[++cnt]=p;
	}
}
sort(d+1,d+1+cnt);
int ans=0;
rep(i,1,cnt){
	int c=d[i]/2,p=0,fl=1;
	rep(j,1,c) p=(p*2%MOD+s[j]-'0')%MOD;
	rep(j,c+1,n){
		int a=(j-1)/c+1,b=(j-1)%c+1;
		if(a&1){
			if(s[j]==s[b]) continue;
			else if(s[j]<s[b]) fl=0;
			break;
		}
		else{
			if(s[j]!=s[b]) continue;
			else if(s[j]=='0') fl=0;
			break;
		}
	}
	f[i]=(p+fl)%MOD;
	Rep(j,1,i) if(d[i]%d[j]==0) f[i]=(f[i]+MOD-f[j])%MOD;
	ans=(ans+(ll)d[i]*f[i]%MOD)%MOD;
}
printf("%d\n",ans);
```

---

