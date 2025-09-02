# Iterated Linear Function

## 题目描述

Consider a linear function $ f(x)=Ax+B $ . Let's define $ g^{(0)}(x)=x $ and $ g^{(n)}(x)=f(g^{(n-1)}(x)) $ for $ n&gt;0 $ . For the given integer values $ A $ , $ B $ , $ n $ and $ x $ find the value of $ g^{(n)}(x) $ modulo $ 10^{9}+7 $ .

## 样例 #1

### 输入

```
3 4 1 1
```

### 输出

```
7
```

## 样例 #2

### 输入

```
3 4 2 1
```

### 输出

```
25
```

## 样例 #3

### 输入

```
3 4 3 1
```

### 输出

```
79
```

# 题解

## 作者：Twig_K (赞：5)

### Step 0：食用前准备

------

- 知识：带数列的通项公式
- 只需要具备初一基本代数知识。
- **代码很短**，数学题，准备好足够的耐心看完推导过程。

### Step 1：题意简化

------

有一个数列 $g$ ，满足：

- $g_0=x$ ， $x$ 为给定数；
- $g_{i+1}=A\times g_i+B$ ， $A$ 和 $B$ 为给定数。

求 $g_n$ 的值，并对 $10^9+7$  取模。

### Step 2：分析

------

$g_0=x$ ， $g_1=A\times g_0+B$ ， $g_2=A\times g_1+B$ ，... ，感觉像套娃的样子。

发现每次都会先乘上一个 $A$ ，那么最后的结果猜测是与 $A^n$ 有关的东西。

那也不能让它一直套下去，得想办法求出 $g$ 的通项公式才行。

今天介绍一种求数列通项公式的方法：**待定系数法求数列通项公式**。

~~强烈推荐百度搜索“待定系数法求数列的通项公式”。~~

### Step 3：计算

-------

**Part 1**

**设**： $g_{n+1}+k=A(g_n+k)$ ， $n\in N$ .	// $n\in N$ 指的是 $n$ 属于自然数。

把上述式子拆开、移项、合并同类项**得**： $g_{n+1}=A\times g_n+(A-1)k$ .

又依题有： $g_{i+1}=A\times g_i+B$ ，两式对比**得**： $B=(A-1)k$  ，

除过去求出 $k$ 得： $k=\frac{B}{A-1}$  .	//为了让思路更加清晰，这里先不考虑 $A-1=0$ 的情况，后面会补充说明。

在一开始我们设了一个式子： $g_{n+1}+k=A(g_n+k)$ 

那么把算出来的 $k$ **代进去得**： $g_{n+1}+\frac{B}{A-1}=A(g_n+\frac{B}{A-1})$

哇！是不是有点像等比数列？

-------------------------

**Part 2**

我们**设** $h_n=g_n+\frac{B}{A-1}$ ，再对比上面最新的式子， $h$ 恰好就是公比为 $A$ 的等比数列！

**即** $h_{n+1}=A\times h_n$

由于 $h_0=g_0+\frac{B}{A-1}$  ，**那么** $h_n=A^n\times h_0=A^n\times (g_0+\frac{B}{A-1})$

所以 $h$ 的通项公式就有了，但是我们的终极目标是求 $g$ 的通项公式，那怎么办？

怎么办呢？Part 2的最开始设了 $h_n=g_n+\frac{B}{A-1}$ ，可以得出：

 $g_n=h_n-\frac{B}{A-1}=A^n\times (g_0+\frac{B}{A-1})-\frac{B}{A-1}$

再整理一下上面的式子，题目将 $g_0$ 输入为 $x$ ，顺便替换掉：  $g_n=A^n\times g_0+(A^n-1)\times \frac{B}{A-1}=A^n\times x+(A^n-1)\times \frac{B}{A-1}$

好了，$g_n$ 的通项公式就解决了，我们用了 $A$ ， $B$ ， $x$ ，来表示出了 $g_n$ 。

--------

**Part 3**

现在还有一个小问题：刚才把 $g_n$ 求出来了，那这个式子里 $A-1$ 分母等于 $0$ 怎么办？也就是 $A=1$ 怎么办？

那太好办了，如果 $A=1$ ，也就是说 $g_{i+1}=g_i+B$ ， $g$ 为等差数列。

这个时候 $g_n=g_0+n\times B$ 。

输入的时候特判一下就可以了。

```cpp
if(a==1){
	cout<<(x+n%mod*b%mod)%mod<<endl;
	return 0;
}
```

### Step 4：实现上的一些细节

------

式子求出来了，结果发现输入有亿点点大，而且这个式子是分式，也就是还要算除法。

输入较大，用上快速幂，记得及时取模。

在计算的过程中需要除以 $A-1$ ，这个时候除以 $A-1$ 就相当于乘 $A-1$ 模 $mod$ 意义下的逆元。

由于题目里要求取模的 $10^9+7$ 是质数，所以这份代码是**根据费马小定理求的逆元**，不明白的可以自行学习一下~~（具体方法：百度搜索“费马小定理求逆元”）~~。

```cpp
long long inv=pw(a-1,mod-2); //pw是快速幂的函数
```

### Step 5：完整代码

------

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long mod=1e9+7;

unsigned long long a,b,n,x;//开一下long long

long long pw(long long a,long long b)
{
	long long ans=1,base=a;
	while(b!=0){
		if(b&1!=0) ans=ans*base%mod;
		base=base*base%mod;
		b>>=1;
	}
	return ans%mod;
}

signed main()
{
	cin>>a>>b>>n>>x;
	if(a==1){
		cout<<(x+n%mod*b%mod)%mod<<endl;
		return 0;
	}
	long long inv=pw(a-1,mod-2);//求a-1的逆元
	long long power=pw(a,n);//求a的n次方
	long long ans=((power-1)*inv%mod*b%mod+x%mod*power%mod)%mod;//根据刚才的式子代入即可
	cout<<ans<<endl;
	return 0;
}
```

ps：数学不好，有问题的话尽管指正。

---

## 作者：zjinze (赞：3)

#### 前置知识：矩阵乘法。

#### 双倍经验：[P2044 [NOI2012] 随机数生成器](https://www.luogu.com.cn/problem/P2044)

#### 思路：

看一眼题目,我们可以轻易发现此题线性做法是不可取的。于是我们可以想到运用矩阵快速幂来加快递推。我们可以定义初始矩阵 $A=$ $\begin{bmatrix}
x & 1\\
\end{bmatrix}$，下一个转移的矩阵应为 $a=$ $\begin{bmatrix}
aa\times x + c & 1\\\end{bmatrix}$，则基础矩阵 $t=$ $\begin{bmatrix}
aa & 0\\
c & 1\\
\end{bmatrix}$，则最终的答案应为 $a \times t^{n}$。

此题不需要用龟速乘，但是那个双倍经验题必须要用，不然会爆 $long long$。

#### 提示：

一定要多取模！！！

#### code:

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int m=1e9+7;
int t[3][3],a[3][3],ans[3][3],aa,c,x,n,g;
int gsc(int a,int b){
	int ans=0;
	while(b){
		if(b&1)ans=(ans+a)%m;
		a+=a;
		a%=m;
		b>>=1;
	}
	return ans;
}
void work1(){
	memset(ans,0,sizeof(ans));
	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++){
			for(int k=0;k<2;k++){
				ans[i][j]=(ans[i][j]+gsc(a[i][k]%m,t[k][j]%m)%m)%m;
			}
		}
	}
	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++){
			a[i][j]=ans[i][j];
		}
	}
	memset(ans,0,sizeof(ans));
}
void work2(){
	memset(ans,0,sizeof(ans));
	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++){
			for(int k=0;k<2;k++){
				ans[i][j]=(ans[i][j]+gsc(t[i][k]%m,t[k][j]%m))%m;
			}
		}
	}
	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++){
			t[i][j]=ans[i][j];
		}
	}
	memset(ans,0,sizeof(ans));
}
void ksm(int b){
	while(b){
		if(b&1)work1();
		work2();
		b>>=1;
	}
}
signed main(){
	cin>>aa>>c>>n>>x;
	x%=m;
	t[0][0]=aa;
	t[0][1]=0;
	t[1][0]=c;
	t[1][1]=1;
	a[0][0]=x;
	a[0][1]=1;
	ksm(n);
	cout<<a[0][0];
	return 0;
}
```

---

## 作者：lgx57 (赞：2)

# CF678D Iterated Linear Function 题解
~~一道水蓝~~  

看到楼上的大佬用的是矩阵乘法，我自愧不如，于是来分享一种我认为简单一些的做法，那就是：**找规律！！！**
## 1.题意
已知 $a_{0}=x , a_{n}=Aa_{n-1}+B(n\neq0)$，求 $a_{n}$ 的值。
## 2.分析
我们可以先在草稿本上算一算前几个 $a_{i}$ 的值。  
$a_{0}=x,$  
$a_{1}=Ax_{0}+B=Ax+B,$  
$a_{2}=Ax_{1}+B=A(Ax+B)+B=A^{2}x+B(A+1),$  
$a_{3}=Ax_{2}+B=A(A^{2}x+B(A+1))+B=A^{3}x+B(A^{2}+A+1)\dots$  以此类推。  
由此，我们可以得到：
$a_{n}=A^{n}x+B(A^{n-1}+A^{n-2}+\dots+A^{2}+A+1)$  
显然，左边的 $A^{n}+B$ 很好处理，只需要用一个快速幂就可以了。  
再观察右边括号中的式子，这不是我们小学二年级就学过的等比数列求和吗？  
于是套用公式，可以得到：
$a_{n}=\begin{cases}A^{n}x+B(\frac{A^{n}-1}{A-1}),A\neq1\\x+Bn,A=1\end{cases}$，  
只需要用一下费马小定理求一下乘法逆元即可。
## 3.参考代码
仅放了代码的主体部分，快速幂等函数请各位大佬自己写。
```cpp
signed main(){
	ll();//long long
	int a,b,n,x;
	cin>>a>>b>>n>>x;
	b%=mod;
	if (a==1){
		n%=mod;
		x%=mod;
		cout<<(x+n*b)%mod;//a=1时的情况注意特判
		return 0;
	}
	a%=mod;
	int cnt=(qp(a,n)*x)%mod;
	int tmp=(ni(a-1)*(qp(a,n)-1))%mod*b%mod;
	cout<<(cnt+tmp)%mod;
	return 0;//完结撒花
}
```
## 4.注记
1.一定不要忘记考虑 $A=1$ 时的情况，~~我因为这个WA了2发~~。  
2.遇到大数的快速幂个人建议开一下 long long，不然可能会溢出。~~即使很多情况下不用开也能过。~~

---

## 作者：timmark (赞：2)

# CF678D 题解
一道比较好的矩阵乘法题。

本题有两种做法：
## 做法 1：矩阵乘法
发现是数列递推，首先想到矩阵。

我们知道，矩阵加速的方法就是用两个矩阵 $a$ 和 $b$ 的乘积得出 $b$ 的“下一个状态”$c$。

比如常规数列递推的矩阵长这样（其中 $f$ 为数列，$a$ 为系数，递推式为 $f_i=a_1\times f_{i-1}+a_2\times f_{i-2}+\cdots+a_m\times f_{i-m}$）：

$$
\left[
\begin{matrix}
a_1 & a_2 & \cdots & a_m\\
1 &  &  & \\
 & \ddots &  & \\
 &  & 1 & \\
\end{matrix}
\right]
\left[
\begin{matrix}
f_{i-1}\\
f_{i-2}\\
\vdots\\
f_{i-m}
\end{matrix}
\right]
=
\left[
\begin{matrix}
f_{i}\\
f_{i-1}\\
\vdots\\
f_{i-m+1}
\end{matrix}
\right]
$$

但是我们发现这道题除了需要变化的 $f$ 外，还有一个不需要变的常数 $B$，怎么办？

笔者一开始做这道题的时候也是卡在了这里。

我们先把后面的 $b$ 和 $c$ 写出来：

$$
b=
\left[
\begin{matrix}
f_{i-1}\\
B
\end{matrix}
\right]
c=
\left[
\begin{matrix}
f_{i}\\
B
\end{matrix}
\right]
$$

仔细观察，发现了什么？

$f_{i-1}$ 变成了新的 $f_i$，但是 $B$ 还是那个 $B$！

所以第一个矩阵就很好想了：

$$
a=
\left[
\begin{matrix}
A & 1\\
0 & 1
\end{matrix}
\right]
$$

在这种除了在 $f$ 的“内部”进行递推还有一些其他东西的序列，通常我们采用下面的思路：

- 首先在后面两个矩阵里填充递推 $f$ 直接需要的东西。
- 看一下这些东西是不是用已经有的东西能推出来的。
- 如果有些不能，就加入额外的信息，然后用已经有的把这些信息推出来。

像这样更多的案例可以参考[这里](https://www.luogu.com.cn/paste/rta88ihh)。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,A,B,x;
const ll mod=1e9+7;
void mtime(ll a[2][2],ll b[2][2],ll c[2][2],int x,int y,int z){//矩阵乘法
	ll d[2][2];
	for(int i=0;i<x;i++){
		for(int j=0;j<y;j++){
			d[i][j]=0;
			for(int k=0;k<z;k++) d[i][j]=(d[i][j]+a[i][k]*b[k][j]%mod)%mod;
		}
	}for(int i=0;i<x;i++) for(int j=0;j<y;j++) c[i][j]=d[i][j];
}void mpow(ll a[2][2],ll b){//矩阵快速幂
	ll ret[2][2]={{1,0},{0,1}};
	while(b){
		if(b & 1) mtime(ret,a,ret,2,2,2);
		mtime(a,a,a,2,2,2),b/=2;
	}a[0][0]=ret[0][0],a[0][1]=ret[0][1],a[1][0]=ret[1][0],a[1][1]=ret[1][1];
}int main(){
	cin >> A >> B >> n >> x ;
	ll a[2][2]={{A,1},{0,1}},b[2][2]={{x,0},{B,0}};
	mpow(a,n);
	mtime(a,b,b,2,1,2);
	cout << b[0][0] ;
	return 0;
}
```
## 做法 2：推式子
我们发现这个式子结构比较简单，考虑一步一步推（下文中用 $f_i$ 代表 $g^i(x)$，取模此处略）。

当 $n=1$ 时，$f_1=Ax+B$；

当 $n=2$ 时，$f_2=A\times(Ax+B)+B=A^2x+AB+B$；

当 $n=3$ 时，$f_3=A\times(A^2x+AB+B)+B=A^3x+A^2B+AB+B$；

当 $n=4$ 时，$f_4=A\times(A^3x+A^2B+AB+B)=A^4x+A^3B+A^2B+AB+B$。

发现了什么？

我们可以总结出一个通项公式：$f_n=A^nx+(A^{n-1}+A^{n-2}+\cdots+1)B$

前面这一部分好办，我们用快速幂算出。

后面这一堆怎么办？

当然，我们可以用矩阵递推。

但是有更简单的方法吗？

我们考虑使用分治。

设 $s(i)=A^i+A^{i-1}+\cdots+1$，根据 $i$ 的奇偶性分类讨论：
- 当 $i$ 为奇数时，因为 $1$ 相当于 $A_0$，所以可以分成 $A^i+A^{i-1}+\cdots+A^{(i+1)\div2}$ 和 $A^{(i-1)\div2}+\cdots+A+1$ 的两段，而前一段正好是后一段的 $A^{(i+1)\div2}$ 倍。所以 $s(i)=(A^{(i+1)\div2}+1)\times s((i-1)\div2)$；
- 当 $i$ 为偶数时，总项数为奇数，我们可以把那个 $1$ 单独拎出来，剩下的部分按照 $i$ 为奇数时处理。此时 $s(i)=(A^{i\div2}+1)\times s(i\div2)+1$。
边界为 $s(1)=A+1,s(0)=1$。

分治代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll A,B,n,x;
const ll mod=1e9+7;
ll qp(ll a,ll b){
	ll p=a,ret=1;
	while(b){
		if(b & 1) ret=ret*p%mod;
		p=p*p%mod,b/=2;
	}return ret;
}ll solve(ll n){
	if(n==0) return 1;
    if(n==1) return A+1;
	if(n%2) return (1+qp(A,n/2+1))*solve(n/2)%mod;
	else return ((1+qp(A,n/2))*(solve(n/2)-1))%mod+1;
}int main(){
	cin >> A >> B >> n >> x ;
	cout << (qp(A,n)*x%mod+solve(n-1)*B%mod)%mod ;
	return 0;
}
```
那么，这种思路用矩阵怎么实现呢？我们可以写出递推式：
$$
s(i)=s(i-1)\times A+1
$$
按照上面的思路，我们画出矩阵：
$$
\left[
\begin{matrix}
A & 1\\
0 & 1
\end{matrix}
\right]
\left[
\begin{matrix}
s(i-1)\\
A
\end{matrix}
\right]
=
\left[
\begin{matrix}
s(i)\\
A
\end{matrix}
\right]
$$
矩阵代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,A,B,x;
const ll mod=1e9+7;
ll qp(ll a,ll b){
    ll p=a,ret=1;
    while(b){
        if(b & 1) ret=ret*p%mod;
        p=p*p%mod,b/=2;
    }return ret;
}void mtime(ll a[2][2],ll b[2][2],ll c[2][2],int x,int y,int z){//矩阵乘法
	ll d[2][2];
	for(int i=0;i<x;i++){
		for(int j=0;j<y;j++){
			d[i][j]=0;
			for(int k=0;k<z;k++) d[i][j]=(d[i][j]+a[i][k]*b[k][j]%mod)%mod;
		}
	}for(int i=0;i<x;i++) for(int j=0;j<y;j++) c[i][j]=d[i][j];
}void mpow(ll a[2][2],ll b){//矩阵快速幂
	ll ret[2][2]={{1,0},{0,1}};
	while(b){
		if(b & 1) mtime(ret,a,ret,2,2,2);
		mtime(a,a,a,2,2,2),b/=2;
	}a[0][0]=ret[0][0],a[0][1]=ret[0][1],a[1][0]=ret[1][0],a[1][1]=ret[1][1];
}int main(){
	cin >> A >> B >> n >> x ;
	ll a[2][2]={{A,1},{0,1}},b[2][2]={{1,0},{1,0}};
	mpow(a,n-1);
	mtime(a,b,b,2,1,2);
	cout << (b[0][0]*B%mod+(qp(A,n)*x%mod))%mod ;
	return 0;
}
```

---

## 作者：first_fan (赞：2)

这是一道简单的递推题目，原本以为需要矩阵加速，后来经过大胆的尝试，发现并不需要 -_-||

* 题意概括：给出$a,b,n,x$，

* 函数$\sf f(x)=a*x+b$

* 函数$\sf g(n,x)=f(g(n-1,x))[1\leq n]$，其中$g(0,x)=x$。

* 求出$g(n,x)$的值。

我们直接暴力递推，从$g(0,x)$推到$g(n,x)$，发现所求即

$a^n*x+a^{n-1}*b+a^{n-2}*b+....a^0
*b$

然后我们用类似快速幂的思想以$log(n)$复杂度推一遍就得到结果了，别忘了取模。

```cpp
#include <bits/stdc++.h>
#define ri register int
#define ll long long
#define int ll
using namespace std;

int read()
{
	int num=0;
	int flg=1;
	char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')
		{
			flg=-1;
		}
		c=getchar();
	}
	while(isdigit(c))
	{
		num=(num<<1)+(num<<3)+(c^48);
		c=getchar();
	}
	return num*flg;
}

const int mod=1e9+7;

main()
{
	int a=read();
	int b=read();
	int n=read();
	int x=read();
	while(n)
	{
		if(n&1)
		{
			x=(a*x+b)%mod;
		}
		b*=(a+1);
		b%=mod;
		a*=a;
		a%=mod;
		n>>=1;
	}
	return 0&printf("%lld",x%mod);
}
```

---

## 作者：EityDawn (赞：1)

# 思路

数据范围 $10^{18}$，妥妥的矩阵快速幂加快递推。


初始 $g^0(x)=x$。

所求 $g^n(x)=Ag^{n-1}(x)+B(n≠0)$。

那我们定义初始矩阵 $K=\left [\begin{matrix} g^0(x) \\ c\end {matrix}\right ]$
，基矩阵 $
base=\left [
\begin{matrix}
  A & 1\\
  0 & 1
\end {matrix}
\right ]$。

求 $K\times base^n$ 的矩阵就可以了。

套用矩阵快速幂模板即可。

### code

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#define int long long
using namespace std;
const int N=30;
const int mod=1e9+7;
int x1,x0,t,a,c,k,g;
struct node{
	int mtx[N][N];
	inline node(){memset(mtx,0,sizeof(mtx));}
	inline node operator *(const node&a) const
	{
		node ans;
		for(int i=1;i<=2;i++)
			for(int j=1;j<=2;j++)
				for(int p=1;p<=2;p++)
					ans.mtx[i][j]=(ans.mtx[i][j]+(__int128)a.mtx[i][p]*mtx[p][j])%mod;
		return ans;
	}	
};
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	node ans,base;
	cin>>a>>c>>k>>x0;
	ans.mtx[1][1]=x0,ans.mtx[2][1]=c;
	base.mtx[2][1]=0,base.mtx[1][1]=a,base.mtx[1][2]=1,base.mtx[2][2]=1;
	while(k)
	{
		if(k&1) ans=ans*base;
		base=base*base;
		k>>=1;
	}
	cout<<ans.mtx[1][1]%mod;
	return 0;
}
```



---

## 作者：CusetVoidAldehyde (赞：0)

前置芝士：矩阵乘法。

线性递推式：$ g^{n}(x) = Ag^{n - 1}(x) + B $。

那么，可以列出以下式子：

$$ \begin{bmatrix} g^n(x) \\ B \end{bmatrix} = \textbf{A}\begin{bmatrix} g^{n - 1}(x) \\ B \end{bmatrix} $$

解得转置矩阵 $ \textbf{A} $ ：

$$ \textbf{A} = \begin{bmatrix} A & 1 \\ 0 & 1 \end{bmatrix} $$

所以：

$$ \begin{bmatrix} g^n(x) \\ B \end{bmatrix} = \textbf{A}^{n}\begin{bmatrix} g^{0}(x) \\ B \end{bmatrix} = \textbf{A}^{n}\begin{bmatrix} x \\ B \end{bmatrix} $$

奉上码风清奇代码一份：

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int m = 1e9 + 7;

ll a, b, n, L = 2, x;

inline ll read() {
    ll x = 0;
    bool f = true;
    char c = getchar();
    while (!isdigit(c)) {
        if (c == '-')
            f = false;
        c = getchar();
    }
    while (isdigit(c)) {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return f ? x : -x;
}

struct Matrix {
    ll M[3][3];
    void clear() memset(M, 0, sizeof(M)); 
    void reset() {
        clear();
        for (int i = 0; i < L; i++)
            M[i][i] = 1;
    }
    Matrix friend operator* (const Matrix &a, const Matrix &b) {
        Matrix Ans;
        Ans.clear();
        for (int i = 0; i < L; i++)
            for (int j = 0; j < L; j++)
                for (int k = 0; k < L; k++)
                    Ans.M[i][j] = (Ans.M[i][j] + a.M[i][k] * b.M[k][j]) % m;
        return Ans;
    }
};

Matrix qp(Matrix a, ll p) {
    Matrix Ans;
    Ans.reset();
    while (p) {
        if (p & 1)
            Ans = Ans * a;
        a = a * a;
        p >>= 1;
    }
    return Ans;
}

int main() {
    a = read();
    b = read();
    n = read();
    x = read();
    Matrix A;
    A.M[0][0] = a, A.M[0][1] = 1;
    A.M[1][0] = 0, A.M[1][1] = 1;
    A = qp(A, n);
    cout << (A.M[0][0] * x + A.M[0][1] * b) % m;
    return 0;
}
```

双倍经验：[P2044 随机数生成器](https://www.luogu.com.cn/problem/P2044)

---

## 作者：August44 (赞：0)

### 题意
已知：
$g^0(x)=x$

$g^{n}(x)=Ag^{n-1}(x)+B$

求$g^n(x)$ ($n\le10^{18}$)。

------------

### 分析
这道题因为 $n\le10^{18}$，所以直接递推 $\Omicron(n)$ 时间复杂度无法忍受。所以只能用矩阵加速数列计算。

令初始矩阵为 $\begin{bmatrix}g^{n-1}(x) & 1\end{bmatrix}$。

需构造一个矩阵 $base$，使得 $\begin{bmatrix}g^{n-1}(x) & 1\end{bmatrix}\times base =\begin{bmatrix}g^{n}(x) & 1\end{bmatrix}$。

由矩阵乘法的[定义](https://baike.baidu.com/item/%E7%9F%A9%E9%98%B5%E4%B9%98%E6%B3%95/5446029?fr=ge_ala)可得，$base=\begin{bmatrix}A & 0\\ B &1\end{bmatrix}$。建议验证确认一下。

接下来套用矩阵快速幂的模板从 $g^0(x)$ 求到 $g^n(x)$，并输出矩阵的第一行第一列即可，$\Omicron(w^3\log n)$ 的时间复杂度可通过此题。

------------
### 代码
```cpp
#include<iostream>
#include<cstring>
#define int long long  //不开long long见祖宗
using namespace std;
const int m=1e9+7; 
struct juzhen
{
	int x[3][3];
}aa;
int a,b,n,xc;
int mull(int a,int b)  //快速乘板子，可以不用
{
	int ans=0;
	while(b)
	{
		if(b&1)
		  ans=(ans+a)%m;
		a=(a+a)%m;
		b>>=1;
	}
	return ans;
}
juzhen mul(juzhen a,juzhen b)  //矩阵乘法
{
	juzhen c;
	memset(c.x,0,sizeof(c.x));
	for(int k=1;k<=2;k++)
	  for(int i=1;i<=2;i++)
	    for(int j=1;j<=2;j++)
	      c.x[i][j]=(c.x[i][j]+mull(a.x[i][k],b.x[k][j])%m)%m;
	return c;
}
signed main()
{
	cin>>a>>b>>n>>xc;
	if(n==0)
	  cout<<xc<<endl;
	else
	{
		juzhen ans;
		memset(ans.x,0,sizeof(ans.x));  
		ans.x[1][1]=xc;
		ans.x[1][2]=1;
		juzhen base;
		memset(base.x,0,sizeof(base.x));
		base.x[1][1]=a;
		base.x[2][1]=b;
		base.x[2][2]=1;
		while(n)   //矩阵快速幂
		{
			if(n&1)
			  ans=mul(ans,base);
			base=mul(base,base);
			n>>=1;
		}
		cout<<ans.x[1][1]<<endl;
	}
	return 0;
}
```

---

## 作者：_RainCappuccino_ (赞：0)

# CF678D Iterated Linear Function

## 题意

$f_{i,x}=A\times f_{i-1,x} + B$ 且 $f_{0,x}=x$ 求 $f_{n,x}$。

## 思路

这道题的递推关系十分清晰。但由于数据范围大（$1\le A,B,x\le 10^
9,1\le n \le 10^{18}$），所以这道题只能使用矩阵乘法加速递推。

### 矩阵的构造

我们需要构造一个矩阵 $P$，使得 $\begin{bmatrix}
  f_{0,x}& b\\
  0&0
\end{bmatrix}\times P= \begin{bmatrix}
f_{1,x}&b\\
0&0
\end{bmatrix}$。根据矩阵乘法的规则，我们可以很容易地推出 $P=\begin{bmatrix}
A&0\\
1&1\end{bmatrix}$。由于 $f_{0,x}=x$，所以要得到 $f_{n,x}$ 就可以转化为求 $\begin{bmatrix}
  x& b\\
  0&0
\end{bmatrix}\times P^n = \begin{bmatrix}
f_{n,x}&b\\
0&0
\end{bmatrix}$，使用矩阵快速幂解决。

## code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 1e9 + 7;
int m, n, x, y, a, b;
struct arr {
	int a[15][15];
	arr() {memset(a, 0, sizeof a);}
	arr operator*(const arr& B) const {//重载乘法
		arr cur;
		int r;
		for (int i = 1; i <= 2; ++i)
			for (int k = 1; k <= 2; ++k) {
				r = a[i][k];
				for (int j = 1; j <= 2; ++j)
					cur.a[i][j] += B.a[k][j] * r, cur.a[i][j] %= mod;
			}
		return cur;
	}
	arr operator^(int x) const {//重载快速幂
		arr cur, res;
		for (int i = 1; i <= 2; ++i) cur.a[i][i] = 1;
		for (int i = 1; i <= 2; ++i)
			for (int j = 1; j <= 2; ++j) res.a[i][j] = a[i][j] % mod;
		while (x) {
			if (x & 1) cur = cur * res;
			res = res * res;
			x >>= 1;
		}
		return cur;
	}
} A, F;//A对应上文中的P矩阵，F为答案矩阵
int mode(int x, int m) {return (x + m) % m;}
void init() {//初始化
	A.a[1][1] = a, A.a[1][2] = 0;
	A.a[2][1] = 1, A.a[2][2] = 1;
	F.a[1][1] = x, F.a[1][2] = b;
	F = F * (A ^ n);
}
signed main() {
	scanf("%lld%lld", &a, &b);
	scanf("%lld", &n);
	scanf("%lld", &x);
	init();
	printf("%lld", mode(F.a[1][1], mod));
	return 0;
}
```



---

## 作者：yuheng_wang080904 (赞：0)

## 题意

给定 $A$，$B$，$n$ 和 $x$。定义函数 $f(x)=Ax+B$，函数 $g^{(0)}(x)=x$ 且 $g^{(n)}(x)=f(g^{(n-1)}(x))$，一直往下递推，请你求出 $g^{(n)}(x)$ 对一个大质数 $10^9+7$ 取余后的值。

## 本人解法

~~**暴力推式子。**~~

既然 $g^{(n)}(x)$ 是一个递推的式子，我们一定可以表示出它最后的结果，于是我们列了以下算式：

$g^{(0)}(x)=x$

$g^{(1)}(x)=f(g^{(0)}(x))=f(x)=Ax+B$

$g^{(2)}(x)=f(g^{(1)}(x))=f(Ax+B)=A(Ax+B)+B=A^2x+AB+B$

$g^{(3)}(x)=f(g^{(2)}(x))=f(A^2x+AB+B)=A(A^2x+AB+B)+B=A^3x+A^2B+AB+B$

大家可以继续往下列，直到发现规律为止……

规律就是：

$g^{(n)}(x)=A^nx+A^{n-1}B+A^{n-2}B+…+AB+B$

如果我们把所有的 $A^i(1\le i \le n)$ 给算出来的话，肯定会在比较大的点上 $TLE$，那么我们可以考虑将原来的式子变形看看，你会发现有一种时间复杂度为 $O(\operatorname{log} n)$ 的算法。

对于 $n \equiv 1(\operatorname{mod} 2)$，那么这个式子一共是 $n+1$ 项，是偶数项，两两配对后你会发现：由于两项中前一项的指数与后一项的指数除以二的商是相同的，因此我们可以得到这样变换的式子：

$g^{(n)}(x)=A^nx+A^{n-1}B+A^{n-2}B+…+AB+B=(A^2)^{\frac{n-1}{2}}(Ax+B)+(A^2)^{\frac{n-3}{2}}(AB+B)+…+(AB+B)$

对于 $n \equiv 0(\operatorname{mod} 2)$ 我们可以用相似的方法两两配对后推出结论，这里就只给大家结论了：

$g^{(n)}(x)=A^nx+A^{n-1}B+A^{n-2}B+…+AB+B=(A^2)^{\frac{n}{2}}x+(A^2)^{\frac{n-2}{2}}(AB+B)+…+(AB+B)$

根据我们得出的结论就能够很快写出代码了。

## 代码1

本人代码，较为简短，看了解法讲解很快就能看懂的。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define mod 1000000007
long long a,b,n,x,ans;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>a>>b>>n>>x;
    while(n){
	if(n%2)x=(a*x+b)%mod;
	b=b*(a+1)%mod;		
        a=a*a%mod;
        n/=2;
    }
    printf("%lld",x%mod);
    return 0;
}
```


## 大神有解

**矩阵快速幂。**

大家可以自学一下矩阵乘法，然后学习大神解法。

题意是 $g^{(n)}(x)=f(g^{(n-1)}(x))=A(g^{(n-1)}(x))+B$，我们设 $g^{(i)}(x)=b_i$，那么 $b_n=Ab_{n-1}+B$。然后我们可以得到这个式子：

$\begin{bmatrix}b_n \\ 1\end{bmatrix}=\begin{bmatrix}A & B \\0 & 1\end{bmatrix}×\begin{bmatrix}b_{n-1} \\1\end{bmatrix}$

证明很简单只需要用矩阵乘法方法计算一下第二个式子就可以得到第一个式子，如下：

$\begin{bmatrix}A & B \\0 & 1\end{bmatrix}×\begin{bmatrix}b_{n-1} \\1\end{bmatrix}=\begin{bmatrix}Ab_{n-1}+B \\0b_{n-1}+1\end{bmatrix}=\begin{bmatrix}b_n \\ 1\end{bmatrix}$

然后原来的公式可以不断展开：

$\begin{bmatrix}b_n \\ 1\end{bmatrix}=\begin{bmatrix}A & B \\0 & 1\end{bmatrix}×\begin{bmatrix}b_{n-1} \\1\end{bmatrix}=\begin{bmatrix}A & B \\0 & 1\end{bmatrix}^2×\begin{bmatrix}b_{n-2} \\1\end{bmatrix}=\begin{bmatrix}A & B \\0 & 1\end{bmatrix}^3×\begin{bmatrix}b_{n-3} \\1\end{bmatrix}=…=\begin{bmatrix}A & B \\0 & 1\end{bmatrix}^n×\begin{bmatrix}1 \\1\end{bmatrix}$

对于这个结果，利用矩阵快速幂进行计算即可，具体方法见代码。

## 代码2

下面晒出大神代码，可以好好学习一下！

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int Q = 1e9 + 7;
struct Matrix {
    int n , m , a[2][2];
    Matrix (int _n = 0, int _m = 0) {
        n = _n , m = _m;
        memset(a , 0 , sizeof(a));
    }
    Matrix operator * (const Matrix &R) const {
        Matrix res(n , R.m);
        for (int i = 0 ; i < n ; ++ i) {
            for (int j = 0 ; j < m ; ++ j) {
                for (int k = 0 ; k < R.m ; ++ k) {
                    res.a[i][k] += (LL)a[i][j] * R.a[j][k] % Q;
                    res.a[i][k] %= Q;
                }
            }
        }
        return res;
    }
};

int main() {
    LL A , B , n , x;
    cin >> A >> B >> n >> x;
    Matrix I(1 , 2);
    I.a[0][0] = x , I.a[0][1] = 1;
    Matrix P(2 , 2);
    P.a[0][0] = A;
    P.a[1][0] = B;
    P.a[1][1] = 1;
    while (n) {
        if (n & 1) {
            I = I * P;
        }
        P = P * P;
        n >>= 1;
    }
    cout << I.a[0][0] << endl;
}
```


---

