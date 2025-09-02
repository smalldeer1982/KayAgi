# Notepad

## 题目描述

Nick is attracted by everything unconventional. He doesn't like decimal number system any more, and he decided to study other number systems. A number system with base $ b $ caught his attention. Before he starts studying it, he wants to write in his notepad all the numbers of length $ n $ without leading zeros in this number system. Each page in Nick's notepad has enough space for $ c $ numbers exactly. Nick writes every suitable number only once, starting with the first clean page and leaving no clean spaces. Nick never writes number $ 0 $ as he has unpleasant memories about zero divide.

Would you help Nick find out how many numbers will be written on the last page.

## 说明/提示

In both samples there are exactly $ 4 $ numbers of length $ 3 $ in binary number system. In the first sample Nick writes $ 3 $ numbers on the first page and $ 1 $ on the second page. In the second sample all the $ 4 $ numbers can be written on the first page.

## 样例 #1

### 输入

```
2 3 3
```

### 输出

```
1```

## 样例 #2

### 输入

```
2 3 4
```

### 输出

```
4```

# 题解

## 作者：stoorz (赞：9)

[$$\color{blue}\texttt{Link:蒟蒻的Blog}$$](https://blog.csdn.net/SSL_ZYC/article/details/99221982)

这道题的范围是$2\leq a\leq 10^{1000,000},1\leq n\leq 10^{1000,000},1\leq p\leq 10^9$。
 
 一个$a$进制的数字的每一位有$a$种取值，但是题目要求不能有前导0，所以第一位只有$a-1$种取值。
 
 所以满足要求的$a$进制数有$(a-1)a^{n-1}$个。
 
 所以题目要求我们求得就是
 
 $$(a-1)a^{n-1}\mod\ p$$
 
 但是当$p|(a-1)a^{n-1}$时应输出$p$。因为此时最后一页有0个字，相当于这一页没写过，也就不是最后一页了。
 
 $a,n$很大，但是$p\leq 10^9$。根据扩展欧拉定理，有$a^{n-1}\equiv a^{(n-1)\ mod\ \varphi(p)+\varphi(p)}(mod\ p)$。所以我们可以把指数用拓展欧拉定理降到$10^9$以内，然后用快速幂即可。
 
 $a$可以边读入边取模。反正$ab\ mod\ p=(a\ mod\ p)\times (b\ mod\ p)\ mod\ p$。
 
 时间复杂度$O(len)$。表示$a,n$的长度。

```cpp
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;

const int N=1000010;
char sa[N],sn[N];
ll p,a,n,phi,q,ans;
int len1,len2;
bool flag;

ll power(ll x,ll k)
{
	ll ans=1;
	for (;k;k>>=1,x=x*x%p)
		if (k&1) ans=ans*x%p;
	return ans;
}

int main()
{
	scanf("%s %s %lld",sa+1,sn+1,&p);
	phi=q=p; len1=strlen(sa+1); len2=strlen(sn+1);
	for (ll i=2;i*i<=q;i++)
		if (!(q%i))
		{
			phi=phi/i*(i-1);
			while (!(q%i)) q/=i;
		}
	if (q>1) phi=phi/q*(q-1);
	for (int i=1;i<=len1;i++)
		a=(a*10+sa[i]-48)%p;
	for (int i=len2;i>=1;i--)  //n-1
		if (sn[i]==48) sn[i]='9';
		else
		{
			sn[i]--;
			break;
		}
	for (int i=1;i<=len2;i++)
	{
		n=n*10+sn[i]-48;
 		if (n>=phi) flag=1;
		n%=phi;
	}
	if (flag) n+=phi;
	ans=((a-1)*power(a,n)%p+p)%p;  //注意这里可能为负数，所以要加p再模p，被HACK了一次
	if (ans) printf("%lld",ans);
		else printf("%lld",p);
	return 0;
}
```


---

## 作者：一扶苏一 (赞：6)

[其实点这里也不会获得更好的阅读体验](https://www.cnblogs.com/yifusuyi/p/9997009.html)

本文感谢[@burnside](https://www.luogu.org/space/show?uid=64500)神仙和[@ddosvoid](https://www.luogu.org/space/show?uid=34531)神仙的帮助审稿qwq

# Definition

$\forall~a~,~m~\in~Z^+~,~s.t.~\gcd(a,m)=1$，则一定满足$~a^{\phi(m)}~\equiv~1~(Mod~m)~$。该定理被称作欧拉定理。

# Demonstration

记$x_i$为第$i$个与$m$互质的数，则共有$\phi(m)$个$x_i$。

设$p_i~=~a~\times~x_i$

### 引理一：

$\{p_i\}$间两两模$m$不同余，$\{x_i\}$间两两模$m$不同余。

##### 证明：

先证$\{x_i\}$间两两模$m$不同余：

因为$~\forall~i~\in~[1,\phi(m)]~,~x_i~<~m~$，故

$$~x_i~Mod~m~\equiv~x_i~$$

又$~\forall~i,j~\in~[1,\phi(m)],i~\neq~j~$都有$~x_i~\neq~x_j~$。于是

$$~x_i~Mod~m~\neq~x_j~Mod~m~$$

$\{x_i\}$间两两模$m$不同余

再证$\{p_i\}$间两两模$m$不同余：

反证法，若存在一对$~i,j~\in~[1,\phi(m)]~,~i~\neq~j~,~s.t.~p_i~\equiv~p_j~(Mod~m)~$，则

$$a~\times~x_i~\equiv~a~\times~x_j~(Mod~m)$$

$$\Rightarrow~x_i~\equiv~x_j~(Mod~m)$$。

根据$\{x_i\}$间两两模$m$不同余，产生矛盾，于是$\{p_i\}$间两两模$m$不同余

##### 证毕

### 引理二：

$\forall~i~\in~[1,\phi(m)]~,~p_i~$与$m$互质。

##### 证明：

写出$m,a,x_i,p_i$的唯一分解式：

$$m~=~q_1^{c_1}~q_2^{c_2}~\dots~q_k^{c_k}$$

$$a=q_1^{d_1}~q_2^{d_2}~\dots~q_k^{d_k}$$

$$x_i~=~q_1^{e_1}~q_2^{e_2}~\dots~q_k^{e_k}$$

$$p_i~=~q_1^{e_1+d_1}~q_2^{e_2+d_2}~\dots~q_k^{e_k+d_k}$$

则$\forall~i~,~s.t.~c_i~\neq~0~$都有$d_i~=~e_i~=~0$，于是$d_i+e_i~=~0$。

于是$\forall~i~\in~[1,\phi(m)]~,~p_i~$与$m$互质。

##### 证毕

根据上述引理，可得所有$p_i$的模$m$的解的集合与$\{x_i\}$相等，于是他们的积模$m$的值也相等。

于是有

$$\prod_{i=1}^{\phi(m)}~p_i~\equiv~a^{\phi(m)}~\prod_{i=1}^{\phi(m)}~x_i~\equiv~\prod_{i=1}^{\phi(m)}~x_i~(Mod~m)$$

于是有$a^{\phi(m)}~\equiv~1~(Mod~m)$。证毕。

# Extension

对于$a$与$m$不一定互质的情况，有：

$a^c~\equiv~\begin{cases}a^{c~Mod~\phi(m)} &\gcd(a,m)~=~1 \\a^c &\gcd(a,m)~\neq~1~\land~c~<~\phi(m) \\ a^{c~Mod~\phi(m)~+~\phi(m)} &\gcd(a,m)~\neq~1~\land~c~\geq~\phi(m)\end{cases}$

# Demonstration

当$m~=~1$时显然成立，以下讨论$m~\neq~1$的情况。

对于$\gcd(a,m)~=~1~$的情况，因为$a^{\phi(m)}~\equiv~1$，所以每$\phi(m)$个$a$就相当于乘$1$。于是只需要算$c~Mod~\phi(m)$次。

对于$c~<~\phi(m)$的情况，直接爆算

下面证明第三种情况。

先证明$a$是一个质数的情况：

### 引理1：

$\forall~p~$为质数，$r~\in~Z^+$，都有$\phi(p^r)~=~(p-1)~\times~p^{r-1}$。

##### 证明：

由于$p$是一个质数，所以$~1~\sim~(p^r-1)~$中有且仅有$i~\times~p,~i~\in~(0,p^{r-1})~$与$p^r$不互质。

于是$\phi(p^r)~=~p^r~-~p^{r-1}~=~p^{r-1}~\times~(p~-~1)~$。

##### 证毕。

### 引理2：

$\forall~k~\in~Z$，$\exists~a,b,x,y~\in~Z^+~,~s.t.~x^a~\times~y^b~=~k$，都有$~a,b~\leq~\phi(k)~$。

##### 证明：

先考虑$k$为一个质数$p$的$r$次幂的情况。根据引理1有：

$\phi(k)~=~\phi(p^r)~=~(p-1)~\times~p^{r-1}$。

下面说明$(p-1)~\times~p^{r-1}~\geq~r$。

当$p=2$时：

经验证$~r=1,2,3~$时成立。当$~r>3~$时按照$r$的大小做数学归纳，可证正确性。

当$~p~>~2~$时，不等号左侧增大，右侧不变，不等式仍然成立。

考虑$k$是多个质数幂时的情况，按照质数个数做数学归纳，正确性成立。

任意组合质数，引理得证。

##### 证毕

#####  引理3：$\exists~r~\leq~c~,~s.t.~a^{\phi(m)+r}~\equiv~a^r~(Mod~m)$。

##### 证明：

令$m~=~t~\times~a^r$，其中$\gcd(t,a)=1$，$t$的存在性显然。

因为$\gcd(t,a)~=~1$，且$\phi$函数是一个积性函数，所以$\phi(t)~|~\phi(m)$。

根据欧拉定理，$a^{\phi(t)}~\equiv~1~(Mod~t)$，于是有

$$a^{\phi(m)}~\equiv~1~(Mod~t)$$

同余式同乘$a^r$，于是有

$$a^{\phi(m)+r}~\equiv~a^r~(Mod~m)$$

已经证明可以构造出这样的$r$。根据引理2，$r~\leq~\phi(m)$。又$c~\geq~\phi(m)$，于是可证构造出的$r~\leq~c$。定理得证。

##### 证毕

于是

$$a^c~\equiv~a^{c-r+r}~\equiv~a^{c-r+\phi(m)+r}~\equiv~a^{c+\phi(m)}~(Mod~m)$$

对上式做数学归纳，可得$a^c~\equiv~a^{c+k\phi(m)}~,~k~\in~Z$，需保证指数为正。

于是最小的合法的指数即为$c~Mod~\phi(m)~+~\phi(m)$。

于是有$$a^c~\equiv~a^{c~Mod~\phi(m)~+~\phi(m)}$$

当$a$是一个质数的幂次时，设$a=p^k$，则

$$a^c~\equiv~p^{ck}~\equiv~p^{ck+\phi(m)}~\equiv~p^{ck+k\phi(m)}~\equiv~(p^k)^{c+\phi(m)}~\equiv~(p^k)^{c~Mod~\phi(m)~+~\phi(m)}~~(Mod~m)$$

当$a$时多个质数次幂的乘积时，依据唯一分解定理做数学归纳，即证正确性。证毕。

# Example

[传送门](https://www.luogu.org/problemnew/show/CF17D)


## Description

你有一个本子，你要往上面写全部的长度为$n$的$b$进制数字，每一页可以写$c$个。要求所有数字必须严格不含前导$0$。求最后一页上有多少个数字

## Input

三个数，依次是进制数$b$,数字长度$n$，每一页的个数$c$。

## Output

一行一个整数代表答案

## Hint

$Forall:$

$2~\leq~b~<~10^{10^6}~,~1~\leq~n~<~10^{10^6}~,~1~\leq~c~\leq~10^9$

## Solution

考虑计数原理，第一个位置可以填$~1~\sim~(b-1)~$共$~(b-1)~$个数字，剩下的位置可以填$~0~\sim~(~b~-~1~)~$共$~b~$个数字。于是答案即为$~(b-1)~\times~b^{(n-1)}$。后面的应用扩展欧拉定理即可解决。

## Code

```cpp
#include<cstdio>
#include<cstring>
#ifdef ONLINE_JUDGE
#define putchar(a) \
puts("I am a cheater!")
#endif
#define rg register
#define ci const int
#define cl const long long

typedef long long int ll;

template <typename T>
inline void qr(T &x) {
	rg char ch=getchar(),lst=' ';
	while((ch > '9') || (ch < '0')) lst=ch,ch=getchar();
	while((ch >= '0') && (ch <= '9')) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	if(lst == '-') x=-x;
}

namespace IO {
	char buf[120];
}

template <typename T>
inline void qw(T x,const char aft,const bool pt) {
	if(x < 0) {x=-x,putchar('-');}
	rg int top=0;
	do {IO::buf[++top]=x%10+'0';} while(x/=10);
	while(top) putchar(IO::buf[top--]);
	if(pt) putchar(aft);
}

const int maxn = 1000010;

char B[maxn],N[maxn];
ll m,phi,b;

int ReadMod(char*,cl&);
int GetPhi(ll);
void MinuN();
int mpow(int,ll);
bool judge();

int main() {
	freopen("1.in","r",stdin);
	scanf("%s %s",B+1,N+1);qr(m);
	b=ReadMod(B,m);
	if(judge()) return 0;
	int k=GetPhi(m);
	MinuN();
	int n=ReadMod(N,k)+k;
	int ans=1ll*(b-1)*mpow(b,n)%m;
	ans=(ans+m)%m;
	qw(ans?ans:m,'\n',true);
	return 0;
}

int ReadMod(char *str,cl & p) {
	int l=strlen(str+1);
	ll _ret=0;
	for(rg int i=1;i<=l;++i) _ret=((_ret<<1)+(_ret<<3)+(str[i]^48))%p;
	return _ret;
}

int GetPhi(ll x) {
	ll _ret=x;
	for(ll i=2;i*i<=x;++i) if(!(x%i)) {
		_ret=_ret*(i-1)/i;
		while(!(x%i)) x/=i;
	}
	if(x != 1) _ret=_ret*(x-1)/x;
	return _ret;
}

void MinuN() {
	int l=strlen(N+1);
	--N[l];
	for(rg int i=l;i;--i) if(N[i] < '1') {
		N[i]+=10,--N[i-1];
	} else break;
	if(N[1] == '0'+10) N[1]='0';
}

int mpow(int x,ll k) {
	int _ret=1,_temp=x;
	while(k) {
		if(k&1) _ret=1ll*_ret*_temp%m;
		_temp=1ll*_temp*_temp%m;
		k>>=1;
	}
	return _ret%m;
}

bool judge() {
	int l=strlen(N+1);
	if(l >= 17) return false;
	ll _tp=0;
	for(rg int i=1;i<=l;++i) _tp=(_tp<<1)+(_tp<<3)+(N[i]^48);
	int ans=1ll*(b-1)*mpow(b,_tp-1)%m;
	ans=(ans+m)%m;
	qw(ans?ans:m,'\n',true);
	return true;
}
```

## Summary

扩展欧拉定理可以用在底数与模数不互质的情况下，将质数将至与模数同阶的大小，从而可以使用快速幂进行运算。

注：本篇内容部分证明参考该[BAJim_H的博客](https://blog.csdn.net/hzj1054689699/article/details/80693756)，在此表示衷心的感谢。

---

## 作者：Leap_Frog (赞：4)

数论好题。  

此题需要用到扩展欧拉定理、快速幂。  

首先，分析题意。  
相当于是要求数字长度为n的b进制数有多少个（带取模  

~~哇，多么简单~~

首先，放第一个位置有$b-1$种，第二个位置有$b$种，第三个也有$n$种，以此类推。然后根据乘法定理，需要的答案就是$(b-1)\times b^{n-1}$。  

~~完结撒花。。。完结个*~~

现在一脸懵逼的笔者发现了数据范围$1<b<10^{10^6},0<n<10^{10^6}$。~~然后笔者当场自闭~~  

首先，我们发现，$b$那么大其实并没有什么用，可以直接对$b$取模后再做运算。  

最令笔者自闭的是那个$0<n<10^{10^6}$。  

我们想到了一个东西，叫做扩展欧拉定理，也叫欧拉降幂公式。  

$$a^C\equiv\begin{cases}a^{C\%\phi(m)}&\gcd(a,m)=1\\a^C&\gcd(a,m)\not=1\quad AND\quad C<\phi(m)\\a^{C\%\phi(m)+\phi(m)}&\gcd(a,m)\not=1\quad AND\quad C\ge\phi(m)\end{cases}\qquad(MOD m)$$

~~打这个公式就让笔者自闭了，可见笔者的菜~~

有了这个公式，当n很大时，我们就可以把$b^{n-1}$转化成$b^{(n-1)\%\phi(P)+\phi(P)}$然后因为$\phi(P)<P\le10^9$然后就可以用快速幂来算出答案了。  

14行的代码附上
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a,n,phi,p,tmp,ans,l1,l2,fla;char s1[1000005],s2[1000005];
inline ll qpow(ll x,ll tmp) {ll r=1;for(;tmp;tmp>>=1,x=x*x%p) if(tmp&1) r=r*x%p;return r%p;}//一行快速幂
signed main()
{
	scanf("%s %s %lld",s1+1,s2+1,&p),l1=strlen(s1+1),l2=strlen(s2+1),phi=tmp=p,a=n=fla=0;//读入，然后预处理
	for(ll i=2,e=sqrt(tmp);i<=e;i++) if(tmp%i==0) {phi-=phi/i;while(tmp%i==0) tmp/=i;}//求出phi(p)
	for(ll i=1;i<=l1;i++) a=(a*10+s1[i]-'0')%p;if(tmp>1) phi-=phi/tmp;//求出b%p
	for(ll i=l2;i>=1;i--) if(s2[i]==0) s2[i]='9';else {s2[i]--;break;}//n--
	for(ll i=1;i<=l2;i++) n=n*10+s2[i]-'0',fla+=(n>=phi),n%=phi;//用刚才的欧拉定理。fla表示是C是否>=phi(m)
	return fla?n+=phi:0,ans=((a-1)*qpow(a,n)%p+p)%p,printf("%lld\n",ans?ans:p),0;//输出最后的快速幂答案
}
```
完结撒花，~~无耻求赞~~。

UPDATE :  
笔者第二天发现，昨天的代码中有一个特别**的错误。  
详情见第11行，`if(s2[i]==0)`这个明显是错的，应该是`if(s2[i]=='0')`，很抱歉，要让管理大大再次审核一遍。  

最神奇的是：这样也能**A**题？！

正确代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a,n,phi,p,tmp,ans,l1,l2,fla;char s1[1000005],s2[1000005];
inline ll qpow(ll x,ll tmp) {ll r=1;for(;tmp;tmp>>=1,x=x*x%p) if(tmp&1) r=r*x%p;return r%p;}
signed main()
{
	scanf("%s %s %lld",s1+1,s2+1,&p),l1=strlen(s1+1),l2=strlen(s2+1),phi=tmp=p,a=n=fla=0;
	for(ll i=2,e=sqrt(tmp);i<=e;i++) if(tmp%i==0) {phi-=phi/i;while(tmp%i==0) tmp/=i;}
	for(ll i=1;i<=l1;i++) a=(a*10+s1[i]-'0')%p;if(tmp>1) phi-=phi/tmp;
	for(ll i=l2;i>=1;i--) if(s2[i]=='0') s2[i]='9';else {s2[i]--;break;}
	for(ll i=1;i<=l2;i++) n=n*10+s2[i]-'0',fla+=(n>=phi),n%=phi;
	return fla?n+=phi:0,ans=((a-1)*qpow(a,n)%p+p)%p,printf("%lld\n",ans?ans:p),0;
}
```

---

## 作者：jianhe (赞：3)

### 前言：
一道比较简单的数论题。

### 题意：
求 $(b-1) b^{n-1} \bmod c$，能整除时输出 $c$。

$2 \le b < 10^{10^6},1 \le n < 10^{10^6},1 \le c \le 10^9$。

### 思路：
先求 $(b-1) \bmod c$，再求 $b^{n-1} \bmod c$，最后乘起来并取模。

显然 $(b-1) \bmod c$ 很好求。

令 $m \leftarrow n-1$，则问题就剩下求 $b^m \bmod c$。

使用扩展欧拉定理：$b^m \equiv b^{m \bmod \varphi(c)+\varphi(c)} \pmod c$。

由于 $c \le 10^9$，$m \bmod \varphi(c)$ 不会超过 $10^9$，跑快速幂即可。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll b,n,c,phi,ans1,ans2,ans;
string s1,s2;
ll getphi(ll x){
	ll ct=x;
	for(int i=2;i*i<=x;i++)
		if(!(x%i)){
			ct/=i,ct*=i-1;
			while(!(x%i)) x/=i;
		}
	if(x>1) ct/=x,ct*=x-1;
	return ct;
}
ll ksm(ll a,ll b){
	ll ct=1;
	while(b){
		if(b&1) ct=ct*a%c;
		a=a*a%c,b>>=1;
	}
	return ct;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>s1>>s2>>c;phi=getphi(c);
	for(int i=0;i<s1.size();i++) ((b*=10)+=s1[i]-'0')%=c;
	ans1=b-1;if(!~ans1) ans1=c-1;
	s2[s2.size()-1]--;//这里写麻烦了，无脑写了高精度减法
	for(int i=s2.size()-1;~i;i--)
		if(s2[i]<0) s2[i-1]--,s2[i]+=10;
		else break;
	for(int i=0;i<s2.size();i++){
		(n*=10)+=s2[i]-'0';
		if(n>=phi) (n%=phi)+=phi;//扩展欧拉定理要保证指数取模后>模数
	}
	ans2=ksm(b,n),ans=ans1*ans2%c;
	if(!ans) ans=c;
	cout<<ans;
	return 0;
}
```

---

## 作者：jiangxinyang2012 (赞：3)

由于首位不能是 $0$ ，因此首位有 $b-1$ 种可能性。其他 $n-1$ 位有 $b^{n-1}$ 种可能。因此这些数总计

$(b-1) b^{n-1}$

每页 $c$ 个数，求最后一页有多少个数，即求

$\text { ans }=(b-1) b^{n-1} \quad \bmod c$

注意到题目中 $b, n$ 都非常大，采用扩展欧拉定理进行降幂处理：


$\begin{aligned}
\text { ans } & =(b-1) b^{n-1} \bmod c \\
& =((b-1) \bmod c)(b \bmod c)^{n-1} \bmod c \\
& =\left\{\begin{array}{lll}
((b-1) \bmod c)(b \bmod c)^{(n-1)\bmod \varphi(c)} \bmod c & \operatorname{gcd}(b, c)=1 \\
((b-1) \bmod c)(b \bmod c)^{n-1} \bmod c & \operatorname{gcd}(b, c) \neq 1, n-1<\varphi(c) \\
((b-1) \bmod c)(b \bmod c)^{(n-1) \bmod \varphi(c)+\varphi(c)} \bmod c & \operatorname{gcd}(b, c)=1, n-1 \geq \varphi(c)
\end{array}\right.
\end{aligned}$

扩展欧拉定理的证明可参考 [OI wiki](https://oi-wiki.org/math/number-theory/fermat/)

最后若 $ans = 0$，则输出 $c$，否则输出 $ans$。

---

## 作者：Yyxxxxx (赞：2)

## $Description$
求：   
$$(b-1) \times b^{n-1}  \mod c$$
## $Solution$
首先为什么能转化为上式？    
对于一个 $n$ 位的 $b$ 进制数，第一位有 $b-1$ 种取法（因为不含前导零），而剩下的 $n-1$ 位每一位都有 $b$ 种取法。    
故总共有 $(b-1)\times b^{n-1}$ 个 $n$ 位 $b$ 进制数。     
接着，每一页放 $c$ 个那么最后一页就放了 $(b-1) \times b^{n-1}  \mod c$ 个。     
特别地，当 $(b-1) \times b^{n-1}  \mod c=0$ 时，最后一页放下了 $c$ 个。     

由于精度问题，我们可以在读入的时候先将 $b$ 对 $c$ 取模，再计算。     
但是复杂度还是很大，因为$n$很大。运用扩展欧拉定理可以解决，即：    
$a^b\equiv
\begin{cases}
a^{b\mod{\varphi(m)}}&\gcd(a,m)=1    \\
a^{b}&\gcd(a,m)\neq1\land b<\varphi(m)\\
a^{b\mod{\varphi(m)+\varphi(m)}} &\gcd(a,m)\neq1\land b\ge\varphi(m)
\end{cases}$
## $Code$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
const int maxn=1e6+10;
ll n=0,a=0,phi,p,tmp,lena,lenn,f=0;char s[maxn],ss[maxn];
ll qpow(ll a,ll k)
{
	ll res=1;
	while(k)
	{
		if(k&1)res=res*a%p;
		a=a*a%p;k>>=1;
	}
	return res;
}
int main()
{
	scanf("%s%s%lld",s+1,ss+1,&p);
	lena=strlen(s+1);
	lenn=strlen(ss+1);
	phi=tmp=p;a=n=0;
	for(ll i=2;i*i<=tmp;i++)
		if(tmp%i==0)
		{
			phi-=phi/i;
			while(tmp%i==0)tmp/=i;
		}
	if(tmp>1)phi-=phi/tmp;
	for(int i=1;i<=lena;i++)
		a=(a*10+s[i]-'0')%p;
	for(int i=lenn;i>=1;i--)
		if(ss[i]=='0')ss[i]='9';
		else
		{
			ss[i]--;
			break;
		}
	for(int i=1;i<=lenn;i++)
	{
		n=n*10+ss[i]-'0';
		if(n>=phi)f=1;
		n%=phi;
	}
	if(f)n+=phi;
	ll ans=((a-1)*qpow(a,n)%p+p)%p;
	if(ans==0)ans=p;
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：NOI_Winner (赞：1)

前置知识：扩展欧拉定理

不难发现，求出了 $x = (b^n - b^{n-1}) \bmod c$ 就能容易得出答案：
$$
ans = \begin{cases} c, & x = 0 \\
x, & x \neq 0\end{cases}
$$

关键在于如何求出 $x$。

我们直接将 $b$ 对 $c$ 取模，由扩展欧拉定理可知：当 $n \gt \phi(m)$ 时，$a^n \equiv a^{n \bmod \phi(m) + \phi(m)}\pmod m$，这样我们就可以将指数 $n$ 缩小到 $10^9$ 以内的范围进行计算。

代码示例：
```cpp
#include <iostream>
#include <cstring>

using namespace std;

constexpr int maxn = 1000000;
char a[maxn + 5], b[maxn + 5];
int mod;

int qpow(int x, int y)
{
    int ans = 1;
    for (; y; y >>= 1)
    {
        if (y & 1) ans = 1ll * ans * x % mod;
        x = 1ll * x * x % mod;
    }
    return ans;
}

int main()
{
    cin >> a + 1 >> b + 1 >> mod;
    int n = strlen(a + 1), m = strlen(b + 1);

    int x = 0, y = 0;
    for (int i = 1; i <= n; i++)
        x = (10ll * x + a[i] - '0') % mod;
    
    if (m <= 9)
    {
        for (int i = 1; i <= m; i++)
            y = 10 * y + b[i] - '0';
        int ans = (qpow(x, y) - qpow(x, y - 1) + mod) % mod;
        cout << (0 == ans ? mod : ans) << endl;
    }
    else
    {
        int phi = mod, t = mod;
        for (int i = 2; i * i <= t; i++)
            if (0 == t % i)
            {
                phi = phi / i * (i - 1);
                while (0 == t % i)
                    t /= i;
            }
        if (t > 1)
            phi = phi / t * (t - 1);

        for (int i = 1; i <= m; i++)
            y = (10ll * y + b[i] - '0') % phi;
        y += phi;

        int ans = qpow(x, y);
        if (--y == phi)
            y += phi;
        ans = (ans - qpow(x, y) + mod) % mod;
        cout << (0 == ans ? mod : ans) << endl;
    }

    return 0;
}
```

---

## 作者：黎明行者 (赞：1)

【分析】

先稍微吐槽一下洛谷的难度分级，这题在CF 2400Rating，为啥在洛谷是黑题？

简单分析一下题目。问题问的是最后一页纸写了几个数字，意思就是所有数字的数量对 $c$ 取模（如果结果为 $0$ 则输出 $c$）。

题目要求数字不能有前导零。所以最高位应该不等于 $0$，总共有 $b-1$ 种取值。剩下的 $n-1$ 位每一位有 $b$ 种取值，所以一共要写 $(b-1)b^{n-1}$ 个数字。

所以题目就是让求
$(b-1)b^{n-1}\bmod c$ 了（如果结果为 $0$ 则输出 $c$），用快速幂就可以秒杀此题。相信来做这道题的都能想到这一步。

所以这就是黑题的难度吗？

脱离数据范围谈算法就是耍流氓。数据范围除了 $c$ 比较小，$b$ 和 $n$ 都巨大，一般的快速幂是不够的。

dalao们都说要用拓展欧拉定理算 $b^{n-1}$。

蒟蒻表示根本没想到拓展欧拉定理~~（其实根本就不会）~~，虽然指数很大，但把快速幂算法魔改一下还是可以做的。倍增快速幂就是把指数做二进制分解，逐级倍增。既然这道题 $n$ 这么大，那就直接用数组按十进制存储，然后做一个十进制倍增快速幂就好了嘛（代码见【完整代码】部分的快速幂函数）。

虽然 $b$ 也很大，但由于结果对 $c$ 取模，可以用 $b$ 对 $c$ 取模的结果来代替原来的那个巨长无比的 $b$。

【完整代码】

```cpp
#include <bits/stdc++.h>

typedef long long ll;
const int N=1e6+6;
char bs[N],ns[N];
int ni[N];
int bl,nl;
ll ksm(ll x,int *y,int n,ll c)//魔改快速幂
{
	ll res=1;
	for (int i=n;i>=1;i--)
	{
		for (int j=1;j<=y[i];j++) res*=x,res%=c;
		ll nx=1;
		for (int j=1;j<=10;j++) nx*=x,nx%=c;
		x=nx;
	}
	return res;
}
int main()
{
	ll c,b=0;
	scanf("%s%s%lld",bs+1,ns+1,&c);
	bl=strlen(bs+1); nl=strlen(ns+1);
	for (int i=1;i<=bl;i++)//计算b MOD c
		b*=10,b+=bs[i]-'0',b%=c;
	for (int i=1;i<=nl;i++) ni[i]=ns[i]-'0';//转成int，这样会好看一些 
	ni[nl]--;
	for (int i=nl;i>=1;i--)
	{
		if (ni[i]<0) ni[i]+=10,ni[i-1]--;
		else break;
	}
	ll ans=ksm(b,ni,nl,c);
	ans*=(b-1+c)%c;
	ans%=c;
	printf("%lld\n",ans?ans:c);
	return 0;
}
```




---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2400}$
---
### 解题思路：

考虑基本问题，不考虑限制条件，对于 $n$ 个位置，每一个位置有 $b$ 中数值选择，但由于前导零是被禁止的，所以第一个位置不能为 $0$，只有 $b-1$ 中选择，总数字一共有 $(b-1)b^{n-1}$ 个，只需要对这个取模就好了。

问题就转化为了 $(b-1)b^{n-1}\bmod c$，其中 $b$ 和 $n$ 都非常大，有一车的 $0$，不能用一般的方法求解，考虑拓展欧拉定理。

定理本身是 $b\ge \phi(p)$，有 $a^b\equiv a^{b\bmod \phi(p)+\phi(p)}$，能够将指数转化到 $\phi(p)$ 同阶，也就可用快速幂求解了。基本欧拉定理和拓展欧拉定理的证明可以在[这里](https://www.luogu.com.cn/blog/JSYZCHTHOLLY/post-wei-zhuan-ti-ou-la-ding-li-ji-ta-zhan-ou-la-ding-li)查看。

---
具体操作的时候，可以先将 $b$ 和 $n$ 保存下来，将 $c$ 的欧拉函数求出来，然后在重新遍历的时候就可以在计算值的同时对 $b$ 和 $n$ 取模了。

注意取模后减一可能会出现负数，需要将结果增加 $c$ 之后再次取模。

---
### 代码：

```cpp
#include<cstdio>
#include<string>
#include<iostream>
using namespace std;
#define int long long
string s1,s2;
int p,phi,np,num1,num2,ans;
int pow(int a,int b,int MOD){
	int ans=1;
	while(b){
		if(b&1)ans=(ans*a)%MOD;
		a=(a*a)%MOD;
		b=b>>1;
	}
	return ans;
}
signed main(){
	cin>>s1>>s2;
	scanf("%I64d",&p);
	phi=p;np=p;
	for(int i=2;i*i<=np;i++){
		if(np%i==0)phi=phi/i*(i-1);
		while(np%i==0)np/=i;
	}
	if(np!=1)phi=phi/np*(np-1);
	for(int i=0;i<s1.size();i++)num1=((num1*10)%p+s1[i]-'0')%p;
	int flag=0;
	for(int i=0;i<s2.size();i++){
		num2=num2*10+s2[i]-'0';
		if(num2>=phi)flag=1;
		num2%=phi;
	}
	num2=(num2-1+phi)%phi;
	if(flag)num2+=phi;
	ans=((num1-1)*pow(num1,num2,p)%p+p)%p;
	if(ans==0)printf("%I64d\n",p);
	else printf("%I64d\n",ans);
	return 0;
}
```


---

## 作者：€€£ (赞：0)

写在前面：wssb，根本不知道有扩展欧拉定理，直接写了个10进制的快速幂艹过去了……

转化其他几位大佬已经讲得很清楚了，但是我们这道题可以不需要用扩展欧拉定理：

考虑二进制的快速幂实操意义（$a^x \times a^y=a^{x+y}$），我们其实可以得到十进制快速幂；而且这道题用十进制快速幂内存连续访问，跑的不算慢；

详见丑陋的代码：

```cpp
# include <stdio.h>
# define int long long
int a[1000010],b[1000010];
signed main()
{
	int i,j,n=0,m=0,mod,anss=1;
	char c=getchar();
	while(c>='0' && c<='9')
	{
		a[n++]=c-'0';
		c=getchar();
	}
	c=getchar();
	while(c>='0' && c<='9')
	{
		b[m++]=c-'0';
		c=getchar();
	}
	scanf("%lld",&mod);
	int x,y=0;
	for(i=0;i<n;i++)
		y=(y*10+a[i])%mod;
	anss=(y-1+mod)%mod;
	b[m-1]--;
	while(b[i]<0)
	{
		b[i]+=10;
		i--;
		b[i]--;
	}
	for(i=m-1;i>=0;i--)//十进制快速幂
	{
		for(j=1;j<=b[i];j++)
			anss=(anss*y)%mod;
		x=y;
		for(j=1;j<10;j++)
			x=(x*y)%mod;
		y=x;
	}
	if(anss==0)
		anss=mod;
	printf("%lld",anss);
	return 0;
}
```

---

## 作者：EternalEpic (赞：0)

首先，首位非零的$n$位$b$进制数有$(b-1) * b^{n - 1}$个，题目要求每一页写$c$个，求最后一页个数，那就是上式对$c$取模。

但$b$，$n$这数字有点大啊，考虑高精度，先用字符串读入处理得到$b$ $mod$ $c$。

```cpp
inline void trans(ll &x, string s, ll p) { x = 0;
	for (int i = 0; i < s.size(); i++)
		x = ((x << 1) + (x << 3) + (s[i] & 15)) % p;
}
```

那指数$n$咋办？这时我们想到了扩展欧拉定理，在底数和模数不互质时，$a^b\equiv a ^ {b mod \phi(n) + \phi(n)}\pmod{n}$。

那就好办了，也对$n$进行读入取模处理然后快速幂一下就完事了。

$\phi(c)$也可以用根号算法求一下，因为$log$远小于根号不计，所以总复杂度约为$O(\sqrt{c})$(这当然不含1e6的读入处理)

code：

```cpp
inline ll phi(ll n) {
	ll ans = n;
	for (ll i = 2; i <= sqrt(n); i++) {
		if (n % i == 0) {
			ans = ans / i * (i - 1);
			while (n % i == 0) n /= i;
		}
	} return n > 1 ? ans / n * (n - 1) : ans;
}

inline ll qpow(ll a, ll b, ll p) {
	ll ret = 1ll;
	for (; b; b >>= 1, a = a * a % p)
		if (b & 1) ret = ret * a % p;
	return ret % p;
}

inline void trans(ll &x, string s, ll p) { x = 0;
	for (int i = 0; i < s.size(); i++)
		x = ((x << 1) + (x << 3) + (s[i] & 15)) % p;
}

string s1, s2; ll b, n, c, ans = 0;

signed main(void) {
//	file("");
	readstr(s1), readstr(s2); s2[s2.size() - 1]--;
	for (int i = s2.size() - 1; i >= 1; i--)
		if (s2[i] < '0') s2[i] += 10, s2[i - 1]--;
	if (s2[0] == '0') s2.erase(s2.begin());
	read(c); trans(b, s1, c); ll Phi = phi(c);
	if (s2.size() <= 9) { n = 0;
		for (int i = 0; i < s2.size(); i++)
			n = (n << 1) + (n << 3) + (s2[i] & 15);
	} else trans(n, s2, Phi), n += Phi;
	ans = ((b - 1) * qpow(b, n, c) % c + c) % c;
	writeln(ans == 0 ? c : ans);
//	fwrite(pf, 1, o1 - pf, stdout);
	return 0;
}
```



---

