# [ARC050C] LCM 111

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc050/tasks/arc050_c



# 题解

## 作者：jianhe (赞：5)

### 前言：
9.15 校内限时训练 T1。是为数不多没有垫底的场（

这篇题解是数论做法，@[wanggk](https://www.luogu.com.cn/user/252664) 巨佬想到了与官方题解一样的矩阵做法，快来膜拜她~

### 题意：
给定三个整数 $A,B,M$。

令 $x=\overbrace{111\ldots 1}^{A\text{\tt个}},y=\overbrace{111\ldots 1}^{B\text{\tt个}}$。

求 $x,y$ 的最小公倍数对 $M$ 取模后的结果。

（题面里打成了“求 $A,B$ 的最小公倍数对 $M$ 取模后的结果”。）

### 思路：
我们知道 $[x,y]=\frac{xy}{(x,y)}$。

但数据范围很大，考虑如何缩小。

注意到对于 $x=\overbrace{111\ldots 1}^{n\text{\tt个}},y=\overbrace{111\ldots 1}^{2n\text{\tt个}}$，有 $\frac{y}{x}=1\overbrace{000\ldots 0}^{n-1\text{\tt个}}1$（是个整数）。

举个例子，$111111 \div 111 = 1001$。

那么类似于递归版快速幂的想法，把 $2n$ 大小的问题化为 $n$ 大小的问题，可以快速求出 $x$ 在模意义下的值。

于是你飞快地写出了以下代码，然后 WA $\times 2$：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll __int128
long long a,b,m;
ll x,y,ans;
ll ksm(ll a,ll b){
	ll ct=1;
	while(b){
		if(b&1) ct=(ct*a)%m;
		a=(a*a)%m;b>>=1;
	}
	return ct;
}
ll calc(ll x){//计算x个1模m的值
	if(x==1) return 1;
	ll ct=calc(x/2),res=0;
	if(x&1) res=(ksm(10,x-1)+m)%m;
	return ((((res+ct*ksm(10,x/2)%m)%m+m)%m+ct)%m+m)%m;
}
void exgcd(ll a,ll b){
	if(b==0){x=1,y=0;return;}
	exgcd(b,a%b);
	ll t=x;x=y,y=t-y*(a/b);
}
void print(ll a){
	if(a>9) print(a/10);
	cout<<(int)(a%10);
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>a>>b>>m;
	if(a==b) print(calc(a));
	else exgcd(calc(__gcd(a,b)),m),print((((calc(b)*((x%m+m)%m))%m+m)%m*calc(a))%m+m)%m;
	return 0;
}
```

为什么不能过呢？因为它不一定存在逆元。

那么计算的时候我们换一个做法。

举个例子，$111111111111 \div 111 = 1001001001$。

可以注意到除完后的数字非常有特点。

因此我们可以把除以公因数的步骤一起做，即求 $\frac{b}{(a,b)}$ 在模 $10^{(a,b)}$ 下的值，最后再乘上 $x$ 在模 $m$ 下的值。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll a,b,m,x,y,ans;
ll ksm(ll a,ll b){
	ll ct=1;
	while(b){
		if(b&1) ct=(ct*a)%m;
		a=(a*a)%m;b>>=1;
	}
	return ct;
}
ll calc(ll x,ll p){//当p=10时：计算x个1对m取模的值
	if(x==1) return 1;//当p=__gcd(a,b)时：计算除掉gcd后对m取模的值
	ll ct=calc(x/2,p),res=0;//类似于递归版快速幂
	if(x&1) res=ksm(p,x-1);
	return ((res+ct*ksm(p,x/2)%m)%m+ct)%m;//拼起来
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>a>>b>>m;
	if(a==b) cout<<calc(a,10);
	else cout<<(calc(a,10)*calc(b/__gcd(a,b),ksm(10,__gcd(a,b))))%m;
	return 0;
}
```

---

## 作者：Getaway_Car (赞：5)

## 一句话题解

转化两个大数的 $\gcd$，再用倍增求答案。

## 题意

[题目](https://www.luogu.com.cn/problem/AT_arc050_c)  

给你 $a, b, m$，其中 $1 \leq a, b \leq 10^{18}, 2 \leq m \leq 10^9$，让你求 $a$ 个 $1$ 拼接起来的数和 $b$ 个 $1$ 拼接起来的数的最小公倍数。

## 思路

我们构造一个函数 $\mathrm{one}(x)$ 表示 $x$ 个 $1$ 拼接起来，用数学语言表述就是：  

$$
\mathrm{one}(x) = \frac{10^x - 1}{9}
$$  

同时又有 $\mathrm{lcm}(a, b) = a \cdot b \div \gcd(a, b)$，那么我们要求的就转化成了：  

$$
\mathrm{one}(a) \cdot \mathrm{one}(b) \div \gcd(\mathrm{one}(a), \mathrm{one}(b))
$$  

因为 $\mathrm{one}(a)$ 与 $\mathrm{one}(b)$ 都比较好求，所以此时的问题就转移到了怎么求 $\gcd(\mathrm{one}(a), \mathrm{one}(b))$ 上来。

我们尝试感性理解一下。可以发现：  

$$
\gcd(\mathrm{one}(a), \mathrm{one}(b)) = \mathrm{one}(\gcd(a, b))
$$  

此时答案就变成了：  

$$
\mathrm{one}(a) \cdot \mathrm{one}(b) \div \mathrm{one}(\gcd(a, b))
$$  

我们把这个式子分成两组：  

$$
\mathrm{one}(a)
\\
\mathrm{one}(b) \div \mathrm{one}(\gcd(a, b))
$$  

对于每一组单独用倍增计算即可。详见代码。  

[提交记录 | 快得飞起](https://atcoder.jp/contests/arc050/submissions/57132805)  

## AC Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a, b, p, d;

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int qpow(int x, int y) { // 快速幂
    int ans = 1;
    while (y) {
        if (y & 1) ans = (ans * x) % p;
        y >>= 1;
        x = (x * x) % p;
    }
    return ans;
}

int cal(int x, int y) { // 倍增计算答案
    int now = 1, npow = qpow(10, y), ans = 0;
    while (x) {
        if (x & 1) ans = ((ans * npow) % p + now) % p;
        x >>= 1;
        now = ((now * npow) % p + now) % p;
        npow = (npow * npow) % p;
    }
    return ans;
}

void solve() {
    cin >> a >> b >> p;
    d = gcd(a, b);
    cout << cal(a, 1) * cal(b / d, d) % p << endl; // 对于第二组，gcd(a, b) 是一个循环节，一共有 b / gcd(a, b) 个循环。
    return;
}

signed main() {
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    while (T--) solve();
    return 0;
}
```

## 最后

问我为什么不推式子？如果你直接开始推式子，你会推出一个带分母的式子。有分母就要求逆元，但是本题中并未保证模数的性质，所以不能直接求逆元。

---

## 作者：wangyizhi (赞：3)

**题目传送门：**
[**洛谷**](https://www.luogu.com.cn/problem/AT_arc050_c) || 
[**AtCoder**](https://atcoder.jp/contests/arc050/tasks/arc050_c)

### 前言

简单数学题。

### ~~题意：略~~

### 题目分析

题目要我们求这两个数的 $\operatorname{lcm}$，那我们可以考虑最基本的求法：$\operatorname{lcm}(x,y)=\frac{x}{\gcd(x,y)}\cdot y$。

考虑如何求 $\gcd(x,y)$。考虑最朴素的辗转相除法，令$A>B$，有：

$$$(1+10+...+10^{A-1})-10^{A-B}(1+10+...+10^{B-1})=1+10+...+10^{A-B-1}$$$

于是我们就会发现，在我们求 $\gcd(x,y)$ 的时候，就是类似于 $A$ 和 $B$ 求 $\gcd$。

于是就可以得到：$\gcd(x,y)=1+10+...+10^{\gcd(A,B)-1}$。

接下来求 $\frac{x}{\gcd(x,y)}$。发现就是把其中的每一段 $1+10+...+10^{\gcd(A,B)-1}$ 替换成相同位上的 $1$。于是这一块就可以化成：$1+10^{\gcd(A,B)}+...+10^{\gcd(A,B)\cdot (\frac{A}{\gcd(A,B)}-1)}$。最后再把它和 $y$ 乘起来就可以了。

考虑如何计算这两个式子。发现这两的式子都可以归成 $1+B+B^2+...+B^{n-1}$ 的形式。可以倍增处理，这里就不细讲的，可以看代码。

于是这题就做完了。

## code

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
using ll=long long;
using ld=long double;
ll qpow(ll a,ll b,ll m)
{
	if(!b) return 1;
	if(b==1) return a%m;
	ll res=qpow(a,b>>1,m);
	if(b&1) return res*res%m*a%m;
	return res*res%m;
}
ll calc(ll n,ll b,ll m)
{
	ll res=0,pw=1;
	for(ll i=0,k=0;(1ll<<i)<=n;pw=(pw+pw*qpow(b,1ll<<i,m)%m)%m,i++) if(n&(1ll<<i))
		res=(res+pw*qpow(b,k,m)%m)%m,k|=(1ll<<i);
	return res;
}
int main()
{
	ll a,b,m;
	cin>>a>>b>>m;
	ll d=__gcd(a,b);
	cout<<calc(a/d,qpow(10,d,m),m)*calc(b,10,m)%m<<"\n";
	return 0;
}
```

---

## 作者：cwxcplh (赞：0)

一道比较简单的题。~~（我绝对不会告诉你这题我改了很久）~~

题目意思很简单，我就不过多解释了，我们直接进入正题。

题目要我们求 $a$ 个 $1$ 组成的数与 $b$ 个 $1$ 组成的数的最小公倍数除以 $m$ 后的余数。先不考虑多的，我们先设定一个函数 $\operatorname{change}(x)$ 表示由 $x$ 个 $1$ 组成的数，也就是这个：

$$\operatorname{change}(x)=\underbrace{111111...11}_{x\text{个}1}$$

写的更加数学化一点就是：

$$\operatorname{change}(x)=\frac{10^x-1}{9}$$

那么我们要求的答案就是：

$$\operatorname{lcm}(\operatorname{change}(a),\operatorname{change}(b))\bmod m$$

同时又有 $\operatorname{lcm}(x,y)=x\times y\div\operatorname{gcd}(x,y)$。

所以说：

$$ans=\operatorname{change}(a)\times\operatorname{change}(b)\div\operatorname{gcd}(\operatorname{change(a)},\operatorname{change(b)})\bmod m$$

但我们仔细发现：$\operatorname{gcd}(\operatorname{change}(a),\operatorname{change}(b))$ 这东西也不好求啊，如果我们能把它转化成 $a$ 和 $b$ 之间的关系就好了。

那么接下来，让我们用感性的思维去看一看这个式子，直觉告诉我们：$\operatorname{gcd}(\operatorname{change}(a),\operatorname{change}(b))=\operatorname{change}(\operatorname{gcd}(a,b))$。以下是证明过程。

**证明：** 假设 $\underbrace{1111...11}_{t\text{个}1}$ 同时是 $\underbrace{11111...11}_{a\text{个}1}$ 与 $\underbrace{111111...11}_{b\text{个}1}$ 的公因数，则：

$$\underbrace{111111...11}_{b\text{个}1}=\underbrace{1111...11}_{t\text{个}1}\times1\underbrace{000...00}_{t-1\text{个}0}1\underbrace{000...00}_{t-1\text{个}0}1...1\underbrace{000...00}_{t-1\text{个}0}1\\\underbrace{11111...11}_{a\text{个}1}=\underbrace{1111...11}_{t\text{个}1}\times1\underbrace{000...00}_{t-1\text{个}0}1\underbrace{000...00}_{t-1\text{个}0}1...1\underbrace{000...00}_{t-1\text{个}0}1$$

第一个式子中 $\underbrace{000...00}_{t-1\text{个}0}1$ 这样的循环一共有 $\frac{b}{t}$ 个，第二个式子中这样的循环则有 $\frac{a}{t}$ 个，因为要有整数个循环，所以 $\frac{b}{t}$ 和 $\frac{a}{t}$ 都是整数，所以 $t$ 是 $a,b$ 的公因数。而我们要 $\underbrace{1111...11}_{t\text{个}1}$ 最大，所以 $t$ 就要是 $a,b$ 的最大公因数，即 $t=\operatorname{gcd}(a,b)$。

由上，我们可以得到：

$$\operatorname{gcd}(\underbrace{11111...11}_{a\text{个}1},\underbrace{111111...11}_{b\text{个}1})=\underbrace{111111...11}_{t\text{个}1}=\underbrace{111111...11}_{\operatorname{gcd}(a,b)\text{个}1}$$

转化一下就成了：

$$\operatorname{gcd}(\operatorname{change}(a),\operatorname{change}(b))=\operatorname{change}(\operatorname{gcd}(a,b))$$

所以，我们得到了这样一个等式：

$$ans=\operatorname{change}(a)\times\operatorname{change}(b)\div\operatorname{change}(\operatorname{gcd}(a,b))$$

但这样我们又要算三遍 $\operatorname{change}(x)$，有没有什么办法可以优化？

这里呢我是采用了**倍分**的思想。

在上面的证明过程中，我们将 $\underbrace{111111...11}_{b\text{个}1}$ 拆成了 $\underbrace{1111...11}_{t\text{个}1}\times1\underbrace{000...00}_{t-1\text{个}0}1\underbrace{000...00}_{t-1\text{个}0}1...1\underbrace{000...00}_{t-1\text{个}0}1$，我们沿用这个思路，如果我们把 $\operatorname{change}(a)$ 归为一类，$\operatorname{change}(b)\div\operatorname{change}(\operatorname{gcd}(a,b))$ 归为一类，那我们就只需要解决后半部分值的问题就行了，后半部分又该怎么做呢？

我们将这个式子转化一下，就成了:

$$
\begin{equation}\begin{split}&\operatorname{change}(b)\div\operatorname{change}(t)\\&=\underbrace{111111...11}_{b\text{个}1}\div\underbrace{1111...11}_{t\text{个}1}\\&=1\underbrace{000...00}_{t-1\text{个}0}1\underbrace{000...00}_{t-1\text{个}0}1...1\underbrace{000...00}_{t-1\text{个}0}1\end{split}\end{equation}$$

而这又有 $\frac{b}{t}$ 个循环，因为 $t=\operatorname{gcd}(a,b)$，所以就有 $b\div\operatorname{gcd}(a,b)$ 个循环。到这，整个思路就彻底结束了。

**代码实现：**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a,b,m;
int gcd(int x,int y) {
	if(y==0) {
		return x;
	}
	return gcd(y,x%y);
}
int qpow(int x,int y) {//快速幂
	int z=1;
	while(y) {
		if(y&1) {
			z=z*x%m;
		}
		y>>=1;
		x=x*x%m;
	}
	return z;
}
int answer(int x,int y) {
	int now=1,po=qpow(10,y),ans=0;
	while(x) {
		if(x&1) {
			ans=(ans*po%m+now)%m;
		}
		x>>=1;
		now=(now*po%m+now)%m;
		po=po*po%m;
	}
	return ans;
}
signed main() {
	cin>>a>>b>>m;
	int g=gcd(a,b);
	cout<<answer(a,1)*answer(b/g,g)%m;//一共有b/g个循环，每次要乘10^g
	return 0;
}
```

---

## 作者：_Kenma_ (赞：0)

# arc050c 解题报告

## 前言

这里提供一种矩阵乘法做法。

问就是因为根本看不懂现有的一篇题解。

## 思路分析

首先因为 lcm 没什么好的性质，考虑转化为 gcd 求解。

设 $f_i$ 表示 $i$ 个 $1$ 拼接形成的数。

所以我们实际上要求 $\frac{f_a\cdot f_b}{\gcd(f_a,f_b)}$。

开始发掘性质了。

### 性质 1

$$\gcd(f_a,f_b)=f_{\gcd(a,b)}$$

考虑证明。

钦定 $a\ge b$，根据更相减损术，有：

$$\gcd(f_a,f_b)=\gcd(f_a-f_b,f_b)=\gcd(10^bf_{a-b},f_b)$$

因为 $f_b$ 不是 $2$ 或 $5$ 的因数，所以：

$$\gcd(f_a,f_b)=\gcd(f_{a-b},f_b)$$

同理可以将减法推广：

$$\gcd(f_a,f_b)=\gcd(f_{a\bmod b},f_b)$$

利用辗转相除法求到边界情况：

$$\gcd(f_a,f_b)=\gcd(f_{\gcd(a,b)},f_0)=f_{\gcd(a,b)}$$

证毕。

### 性质2

当 $b\mid a$ 时，$\frac{f_a}{f_b}$ 形如：$100\cdots0100\cdots0100\cdots01$，其中 $00\cdots01$ 周期长度为 $b$，周期个数为 $\frac{a}{b}$。

证明显然，不再赘述。

~~其实打个表也能看出来。~~

有了这两个性质，这个题就好做了。

设 $g_{i,j}$ 表示 $00\cdots01$ 的周期长度为 $i$，周期个数为 $j$，那么 $\frac{f_a\cdot f_b}{\gcd(f_a,f_b)}=g_{\gcd(a,b),\frac{a}{\gcd(a,b)}}\cdot g_{1,b}$。

然后考虑 $g$ 的递推。不难发现：

$$g_{i,j}=10^jg_{i,j-1}+1$$

这肯定可以矩阵加速。

设初始矩阵为：

$$\begin{bmatrix}
  g_{i,j}& g_{i,j-1} & 1
\end{bmatrix}$$

转移矩阵为：

$$\begin{bmatrix}
  10^i& 1& 0\\
  0& 0& 0&\\
  1& 0& 1
\end{bmatrix}$$

做完了。

总体复杂度为 $O(\log v)$。有些常数。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std; 
int x,y,mod;
struct node{
	long long h[4][4];
	node(){
		memset(h,0,sizeof(h));
	}
	node operator *(const node &a)const{
		node ans;
		for(int i=1;i<=3;i++){
			for(int j=1;j<=3;j++){
				for(int k=1;k<=3;k++){
					ans.h[i][j]=(ans.h[i][j]+h[i][k]*a.h[k][j]%mod)%mod;
				}
			}
		}
		return ans;
	}
}a,b,c;
node binpow(node a,int b){
	if(b==0) return c;
	node res=binpow(a,b/2);
	if(b&1) return (res*res)*a;
	else return res*res;
}
int qpow(int a,int b){
	if(b==0) return 1;
	int res=qpow(a,b/2);
	if(b&1) return res*res%mod*a%mod;
	else return res*res%mod;
}
int f(int x,int len,int tim){
	if(tim==1) return 1;
	if(tim==2) return qpow(10,len)+1;
	a.h[1][1]=qpow(10,len)+1;
	a.h[1][2]=1;
	a.h[1][3]=1;
	b.h[1][1]=qpow(10,len);
	b.h[1][2]=1;
	b.h[3][1]=1;
	b.h[3][3]=1;
	c.h[1][1]=1;
	c.h[2][2]=1;
	c.h[3][3]=1;
	a=a*binpow(b,tim-2);
	return a.h[1][1];
}
signed main(){
	cin>>x>>y>>mod;
	cout<<f(x,__gcd(x,y),x/__gcd(x,y))*f(y,1,y)%mod<<'\n';
	return 0;
}
```

## 后记

祝 CSP2024 rp++

---

