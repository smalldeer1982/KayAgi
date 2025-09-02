# PLEASE

## 题目描述

正如我们所知道的，Barney的工作是"PLEASE"并且ta工作时不需要做太多事情。这就是ta开始玩"cups and key"的原因。在这个游戏中有三个完全相同的杯子从左到右排成一行。最初，通往Barney心房的钥匙在中间的杯子下面

游戏总共有$n$个回合，每个回合中，Barney等概率地选择两侧杯子的其中一个与中间的杯子交换位置，钥匙始终在原来的杯子中

游戏结束后，Barney要求一位女装大佬（就是你）答出钥匙在中间杯子中的概率

由于回合非常多，ta给了你一个数组`a[k]`，$n=\prod_{i=1}^k a_i$

最后的答案化为形如`p/q`的最简分数形式后，分子分母同对$1e9+7$取模

## 样例 #1

### 输入

```
1
2
```

### 输出

```
1/2
```

## 样例 #2

### 输入

```
3
1 1 1
```

### 输出

```
0/1
```

# 题解

## 作者：Falashiro (赞：7)

小清新推式子题，除快速幂外不需要任何算法。

定义 $1$ 为有钥匙的杯子，$0$ 为无钥匙的杯子，则有 $100,010,001$ 三种状态。

画出树状图：

![](https://cdn.luogu.com.cn/upload/image_hosting/mgqb6mth.png)

第 $n$ 次移动后的答案为该层中状态为 $010$ 的节点个数除以该层总节点个数，设第 $n$ 次操作这一层中状态为 $010$ 的节点个数为 $A_n$，设第 $n$ 次移动后的答案为 $ans_n$，则 $ans_n=\dfrac{A_n}{2^n}$，得到 $A_n=ans_n\times2^n$。

每个 $010$ 节点的子节点中显然没有 $010$ 节点，每个非 $010$ 节点的子节点中有一个 $010$ 节点。

第 $n$ 次操作这一层中非 $010$ 节点的个数为 $2^n-A_n$，每个非 $010$ 节点对 $A_{n+1}$ 有 $1$ 的贡献，所以 $A_{n+1}=2^n-A_n$。

得到递推式：$ans_{n+1}=\dfrac{A_{n+1}}{2^{n+1}}=\dfrac{2^n-A_n}{2^{n+1}}=\dfrac{2^n-ans_n\times2^n}{2^{n+1}}=\dfrac{1-ans_n}{2}=-\dfrac{ans_n}{2}+\dfrac{1}{2}$。

从而得到：$-\dfrac{1}{2}(ans_n-\dfrac{1}{3})=ans_{n+1}-\dfrac{1}{3}$

设 $B_i=ans_i-\dfrac{1}{3}$，则 $B_{n+1}=-\dfrac{1}{2}B_n$，

$ans_1=0$，$B_1=ans_1-\dfrac{1}{3}=-\dfrac{1}{3}$，

$B$ 数列为等比数列，$B_1=-\dfrac{1}{3}$，得到通项公式：$B_n=(-\dfrac{1}{3})\times(-\dfrac{1}{2})^{n-1}$，

则 $ans_n=B_n+\dfrac{1}{3}=(-\dfrac{1}{3})\times(-\dfrac{1}{2})^{n-1}+\dfrac{1}{3}$。

当 $n$ 为奇数时，$ans_n=-\dfrac{1}{3}\times\dfrac{1}{2^{n-1}}+\dfrac{1}{3}=\dfrac{2^{n-1}-1}{3\times2^{n-1}}$，

题目要求将分数化为最简分数，显然分子不是 $2$ 的倍数，

设 $n=2t+1$（$t$ 为正整数），$2^{2}\equiv1\pmod{3}$，可得 $2^{2t}\equiv1\pmod{3}$，$2^{n-1}-1\equiv0\pmod{3}$，所以此时分子是 $3$ 的倍数。

即 $ans_n=\dfrac{(2^{n-1}-1)\div3}{2^{n-1}}$，此时为最简分数形式。

当 $n$ 为偶数时，$ans_n=\dfrac{1}{3}\times\dfrac{1}{2^{n-1}}+\dfrac{1}{3}=\dfrac{2^{n-1}+1}{3\times2^{n-1}}$，

显然分子不是 $2$ 的倍数，

设 $n=2t$（$t$ 为正整数），$2^{2}\equiv1\pmod{3}$，可得 $2^{2t-2}\equiv1\pmod{3}$，$2^{n-2}\equiv1\pmod{3}$，$2^{n-1}\equiv2\pmod{3}$，$2^{n-1}+1\equiv0\pmod{3}$，所以此时分子是 $3$ 的倍数。

即 $ans_n=\dfrac{(2^{n-1}+1)\div3}{2^{n-1}}$，此时为最简分数形式。

$n=\prod\limits_{i=1}^{k}a_i$，$2^n=(((2^{a_1})^{a_2})^{\dots})^{a_k}$。

快速幂 $+$ 逆元计算即可。

$\text{code}$：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){
	int w=0,f=1;
	char c=' ';
	while(c<'0'||c>'9')c=getchar(),f=c=='-'?-1:f;
	while(c>='0'&&c<='9')w=w*10+c-48,c=getchar();
	return w*f;
}
const int mod=1e9+7;
int pown(int x,int y){
	int res=1,ans=x;
	while(y){
		if(y&1)res=res*ans%mod;
		ans=ans*ans%mod;
		y>>=1;
	}
	return res;
}
signed main(){
	int n=read(),x,y=2;
	bool flag=0;
	for(int i=1;i<=n;i++)
		x=read(),flag=x%2?flag:1,y=pown(y,x)%mod;
	y=y*pown(2,mod-2)%mod;
	if(flag)printf("%lld/%lld",(y+1)*pown(3,mod-2)%mod,y);
	else printf("%lld/%lld",(y-1+mod)*pown(3,mod-2)%mod,y);
	return 0;
}
```

---

## 作者：syzf2222 (赞：2)

简单的数列求通项题+整除分析。

考虑设$f_i$为$i$局之后在中间的概率，$g_i$为在两侧的概率。

只有可能从两侧到中间，故为$f_i=\frac12g_{i-1}$。

可能原来在一侧而翻转了另一侧，也有可能原来在中间，$g_i=f_{i-1}+\frac12g_{i-1}$。

将$f_i$带入$g_i$，有$g_i=f_{i-1}+f_i$，将$g_{i-1}$带入$f_i$，有$2f_i=f_{i-1}+f_{i-2}$。

其特征根方程$2x^2-x-1=0$，解得$x_1=1,x_2=-\frac12$。

设$f_n=a\times1^n+b\times(-\frac12)^n$，已有$f_0=1$，$f_1=0$。

带入，解得$a=\frac13$，$b=\frac23$，则原式为$f_i=\frac13+\frac23\times(-\frac12)^i$。

考虑将$f_i$写成$\frac13\times\frac{2^{i-1}-(-1)^{i-1}}{2^{i-1}}$的形式，思考$2^p-(-1)^p$与3的整除关系。

1.若$p=2k+1$，则$3|2^p+1=(1+2)(2^{p-1}-2^{p-2}+……+1)$

2.若$p=2k$，则$3|2^p-1=\sum\limits_{i=0}^{2k-1}2^i=(1+2)(2^0+2^2+……+2^{2k-2})$

故最终答案为$\frac{\frac13\times(2^{n-1}-(-1)^{n-1})}{2^{n-1}}$，那个$\frac13$直接求3的逆元就好。

注意，指数应对$\varphi(mod)=mod-1$取模。

代码放上，仅供参考：
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e5+10;
const int mod=1e9+7;
const int inv3=333333336;
int n,a[maxn];
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
inline int ksm(int x,int y){
	int res=1;
	while(y){
		if(y&1)res=res*x%mod;
		x=(x*x)%mod;y>>=1;
	}
	return res;
}
signed main(){
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read()%(mod-1);
	int res=1;
	for(int i=1;i<=n;i++)
		res=res*a[i]%(mod-1);
	if(!res)res=mod-1;
	int up=1,down=1;
	down=ksm(2,res-1);
	up=down+((res&1)?-1:1);
	up=up*inv3%mod;
	printf("%lld/%lld\n",up,down);
	return 0;
}

```
深深地感到自己的弱小。

---

## 作者：是个汉子 (赞：2)

### Solution

我们用 $a_i$ 表示第 $i$ 次在中间的概率， $b_i$ 为不在中间的概率。

~~随便递推一下~~，可以得到 $a_i=\frac12b_{i-1},b_i=1-a_i=1-\frac12b_{i-1}$ 

~~再用一些关于数列的基础知识随便瞎搞~~，可知 $b_i-\frac23=-\frac12(b_{i-1}-\frac23)\Rightarrow b_n=(-\frac12)^n(b_0-\frac23)+\frac23$ 

所以， $a_n=1-b_n=\frac{2^n+2*(-1)^n}{3*2^n}=\frac{2^{n-1}+(-1)^n}{3*2^{n-1}}$ 



现在分类讨论：

- 当 $n-1$ 为奇数时， $2^{n-1}+1=(2+1)(2^{n-2}-2^{n-3}+2^{n-4}...+1)$ 
- 当 $n-1$ 为偶数时，$2^{n-1}-1=2^{2^x}-1=(4-1)(2^{2^{x-1}}+2^{2^{x-2}}...+1)$ 

说明上下能同时除以 $3$ ：$a_n=\frac{2^{n-1}+(-1)^n/3}{2^{n-1}}$ ，此时已是最简，用快速幂+逆元输出即可。

### 代码

```c++
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define int long long

using namespace std;
const int mod=1e9+7;
int n,x,y=2;
bool flag;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
    return x*f;
}

int fpow(int x,int y){
    int res=1,base=x;
    while(y){
        if(y&1) res=res*base%mod;
        base=base*base%mod;
        y>>=1;
    }
    return res;
}

signed main(){
    n=read();
    for(int i=1;i<=n;i++) x=read(),flag=x%2?flag:1,y=fpow(y,x);
    y=y*fpow(2,mod-2)%mod;
    if(flag) printf("%lld/%lld",(y+1)*fpow(3,mod-2)%mod,y);
    else printf("%lld/%lld",(y-1+mod)*fpow(3,mod-2)%mod,y);
    return 0;
}
```



---

## 作者：PrincessQi (赞：2)

介绍一些关于数列的处理技巧。

首先，设 $a_i$ 表示 $i$ 次操作后钥匙在中间的概率。

则 $i$ 次操作后钥匙在旁边的概率为 $1-a_i$ 。

则 $i+1$ 次操作后钥匙由旁边移到中间的概率为 $(1-a_i)\times \frac12=\frac12-\frac12a_i$。

又因为 $i+1$ 次操作后钥匙由中间到中间（即保持在中间不动）的概率为 $0$（因为若钥匙之前在中间，则这次操作后就必须移到旁边去，则不可能保持在中间）。

则 $i+1$ 次操作后钥匙在中间的概率为 $\frac12-\frac12a_i=a_{i+1}$。

这样，我们就得到了 $a_i$ 的递推式：

$$\frac12-\frac12a_i=a_{i+1}$$

那么，怎么处理这个数列呢？

这里介绍几种方法。

### 第一种：我会矩阵快速幂！

的确，矩阵快速幂是OI中处理数列最常见的方法。

易知，$a_0=1$（一次操作都没进行钥匙当然就在中间了）。

构造矩阵$[a_i\times 2^i\ \ \ \ 2^i]$。

对于 $[a_i\times 2^i\ \ \ \ 2^i]$ ，有

$$[a_i\times 2^i\ \ \ \ 2^i]\times \begin{bmatrix}-1&0\\1&2\end{bmatrix}=[a_{i+1}\times 2^{i+1}\ \ \ \ 2^{i+1}]$$

矩阵快速幂即可。

### 第二种：我会推柿子！

有时候，对于矩阵快速幂不太好处理的情况（就比如这题，这题的矩阵不是很显然），我们可以直接推出他的通项公式。

易知，$a_0=1$（一次操作都没进行钥匙当然就在中间了）。

现在让我们把柿子搬下来：

$$\frac12-\frac12a_i=a_{i+1}$$

然后我介绍一下对于形如

$$a_{i+1}=p\cdot a_i+q$$

的柿子的处理方法。

首先，使用待定系数法，假设我们有 $k$，使

$$a_{i+1}+k=p\cdot (a_i+k)$$

成立。

则将上面那个柿子整理一下，得到

$$a_{i+1}=p\cdot a_i+(p-1)\cdot k$$

则有

$$(p-1)\cdot k=q$$

解得

$$k=\frac q{p-1}$$

将$k=\frac q{p-1}$带入$a_{i+1}+k=p\cdot (a_i+k)$，得

$$a_{i+1}+\frac q{p-1}=p\cdot (a_i+\frac q{p-1})$$

则有

$$a_{n}+\frac q{p-1}=p^n\cdot (a_0+\frac q{p-1})$$

则

$$a_{n}=p^n\cdot (a_0+\frac q{p-1})-\frac q{p-1}$$

再回到这个题。

将$p=-\frac12,q=\frac12,a_0=1$ 代入上式，得

$$a_{n}=(-\frac12)^n\cdot \frac23+\frac13$$

这个题基本就做完了。

### 第三种：我会OEIS！

（显然OI考试是没有网的，所以这种方法还是慎用）

根据第一种方法，$a_i\cdot 2^i$ 是一个整数，则手算 $a_i\cdot 2^i$ 的前七项 $1,0,2,2,6,10,22$ 丢进OEIS，发现这个数列是A078008，于是就没什么好说的了。

---

## 作者：Adove (赞：1)

矩阵快速幂+扩展欧拉定理

对于一个矩阵$A$，我们有$A^n \equiv A^{n\% \phi(m)+\phi(m)}(\%m)$

经过简单的列举或推导可得

设目前进行了$x$轮，$f(x)$为分子，$g(x)$为分母

则有$f(x)=g(x-1)-f(x-1),g(x)=2g(x-1)$

由此及首项可得$x>1$时概率的分子一直是奇数，分母一直为2的幂

而$x=1$时分子为0，分母为1

即分子与分母恒互质

由此可得转移矩阵

$$A=\begin{bmatrix} -1 & 1 \\ 0 & 2 \end{bmatrix}$$

初始矩阵

$$B=\begin{bmatrix} 0 \\ 1 \end{bmatrix}$$

设
$A^{n-1} \times B=\begin{bmatrix} p \\ q \end{bmatrix}$

则`p/q`为所求

该算法时间复杂度为$\Theta(k)$，是本题的理论复杂度下限。

```cpp
#include"cstdio"
#include"cstring"
#include"iostream"
#include"algorithm"
using namespace std;

const int MOD=1e9+7;
const int siz=5;

int n;
long long v=1;
struct Matrix{
	long long v[siz][siz];
	int x,y;

	void clear(){memset(v,0,sizeof(v));x=y=0;}
	void Mmul(Matrix a,Matrix b)
	{
		clear();
		x=a.x,y=b.y;int c=a.y;
		for(int i=1;i<=x;++i){
			for(int j=1;j<=y;++j){
				for(int k=1;k<=c;++k){
					v[i][j]+=a.v[i][k]*b.v[k][j]%MOD;
					v[i][j]=(v[i][j]%MOD+MOD)%MOD;
				}
			}
		}return;
	}

	Matrix Mpw(Matrix a,long long b)
	{
		Matrix x;x.clear();x.x=x.y=a.x;
		for(int i=1;i<=a.x;++i) x.v[i][i]=1;
		while(b){
			if(b&1) x.Mmul(x,a);
			b>>=1;a.Mmul(a,a);
		}return x;
	}
	
	void write()
	{
		for(int i=1;i<=x;++i){
			for(int j=1;j<=y;++j){
				printf("%lld ",v[i][j]);
			}puts("");
		}puts("");
		return;
	}
}A,B;

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i){long long x;scanf("%lld",&x);v=(x%(MOD-1)*v)%(MOD-1);}
	v+=MOD-1;
	A.x=A.y=2;B.x=2,B.y=1;
	A.v[1][1]=-1,A.v[1][2]=1,A.v[2][2]=2;
	B.v[2][1]=1;
	A=A.Mpw(A,v-1);B.Mmul(A,B);
	printf("%lld/%lld\n",B.v[1][1],B.v[2][1]);
	return 0;
}
```



---

## 作者：Aw顿顿 (赞：0)

一道很轻量级的推式子题，适合在被工业冲昏了头脑的时候调剂一下。

不妨设 $a_i$ 为第 $i$ 次移动后在中间的概率，而 $b_i$ 则表示不在中间的概率。

显然，他们之间可以转移，首先知道 $a_i+b_i=1$，然后考虑从 $i-1$ 到 $i$ 进行计算。

从 $b_{i-1}$ 进行转移，有一半的几率会转移到 $a_i$，且 $a_{i-1}$ 肯定是不能转移成 $a_i$，因为实际上 $a_{i-1}$ 的操作是把中间的钥匙转移到边上。那么就得到 $a_i=\frac{1}{2}b_{i-1}$。

接下来考虑硬推。

$$b_i=1-a_i=1-\dfrac{1}{2}b_{i-1}$$

所以如果有高中数学基础应该不难处理：

$$b_i-\dfrac{2}{3}=1-\dfrac{1}{2}b_{i-1}-\dfrac{2}{3}=\dfrac{1}{3}-\dfrac{1}{2}b_{i-1}$$

实际上，为了让其呈现出 $b_x-\frac{2}{3}$ 的形式，我们可以提出公因式进行处理：

$$-\dfrac{1}{2}\left(b_{i-1}-\dfrac{2}{3}\right)$$

然后就可以一次次递归求解，极其容易得到：

$$b_n-\dfrac{2}{3}=\left(-\dfrac{1}{2}\right)^n\left(b_0-\dfrac{2}{3}\right)$$

代回去就得到：

$$a_n=1-b_n=\dfrac{2^n+2\cdot(-1)^n}{3\cdot 2^n}=\dfrac{2^{n-1}+(-1)^n}{3\cdot2^{n-1}}$$

显然用快速幂实现即可，分类讨论，除法用逆元处理，注意下负数先加上 $10^9+7$ 再取模的问题。

```cpp
#include<bits/stdc++.h>
#define mod 1000000007
#define int long long
using namespace std;
int ksm(int b,int p){
    int s=1;b%=mod;
    while(p){
        if(p&1)s=s*b%mod;
        b=b*b%mod;p>>=1;
    }return s;
}int n,x,s=2,f=0;
int inv2=ksm(2,mod-2),inv3=ksm(3,mod-2);
signed main(){
    scanf("%lld",&n);
    for(register int i=1;i<=n;i++){
        scanf("%lld",&x);
        if(x%2==0)f=1;
        s=ksm(s,x)%mod;
    }s=s*inv2%mod;
	if(f)cout<<(s+1)*inv3%mod<<'/'<<s<<endl;
	else cout<<(s-1+mod)*inv3%mod<<'/'<<s<<endl;
	return 0;
}
```



---

## 作者：xixiup (赞：0)

## 推销博客

[$\mathcal{\color{Red}\colorbox{Black}{MY \  BLOG}}$](https://www.luogu.com.cn/blog/Manvski/)

## 思路分享

~~（你绝对想不到这篇题解的思路框架是初中数学）~~

根据初中数学的思想，我们遇到概率问题时可以考虑画一个状态树。

设一个三元组 $\left( a_1,a_2,a_3 \right)$ 表示当前状态为 $\left( a_1,a_2,a_3 \right)$，若 $a_i=0$ 则表示这个杯子没有钥匙，为 $1$ 表示有钥匙。根据题意，显然 $a_0+a_1+a_2=1$。

然后我们就可以画出状态树：

![](https://cdn.luogu.com.cn/upload/image_hosting/2koalxq9.png)

我们可以发现，这个状态数是一棵二叉树。

让我们考虑二叉树每一个节点的子结点：

1. 节点 $(0,1,0)$ 的子结点有 $0$ 个子结点是 $(0,1,0)$

2. 节点 $(1,0,0)$ 的子结点有 $1$ 个子结点是 $(0,1,0)$

3. 节点 $(0,0,1)$ 的子结点有 $1$ 个子结点是 $(0,1,0)$

这样有什么用呢？

由于树的根节点是初始状态，所以我们设其为第 $0$ 层，然后我们考虑设 $x_i$ 表示树的第 $i$ 层的节点 $(0,1,0)$ 的个数，就可以得到公式：$x_i=2^{i-1}-x_{i-1}$。

然后我们就可以求出答案：

$$
ans_i=\dfrac{x_i}{2^{i}}=\dfrac{2^{i-1}-x_{i-1}}{2^{i}}=\dfrac{2^{i-1}-ans_{i-1}\times 2^{i-1}}{2^i}=\dfrac{1-ans_{i-1}}{2}=-\dfrac{1}{2}ans_{i-1}+\dfrac{1}{2}
$$

从而得到：

$$
ans_i-\dfrac{1}{3}=-\dfrac{1}{2}\left(ans_{i-1}-\dfrac{1}{3}\right)
$$

最后就可以得到：

$$
ans_n=-\dfrac{1}{3}\times\left(-\dfrac{1}{2}\right)^{n-1}+\dfrac{1}{3}
$$

这时候我们就需要分考讨论

当 $n$ 为偶数时：

$$
ans_n=\dfrac{2^{n-1}+1}{2^{n-1}\times3}=\dfrac{\dfrac{\left(2^{n-1}+1\right)}{3}}{2^{n-1}}
$$

当 $n$ 为奇数时：

$$
ans_n=\dfrac{2^{n-1}-1}{2^{n-1}\times3}=\dfrac{\dfrac{\left(2^{n-1}-1\right)}{3}}{2^{n-1}}
$$

然后实现就很简单了。

## 代码展示

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int Mod=1e9+7;
int n,a,b,parity;
int power(int x,int y){
	int ans=1;
	while(y){
		if(y&1){
			ans*=x;
			ans%=Mod;
		}
		x*=x;
		x%=Mod;
		y>>=1;
	}
	return ans;
}
signed main(){
	cin>>n;
	b=2;
	for(int i=1;i<=n;i++){
		scanf("%lld",&a);
		b=power(b,a);
		parity=(parity)|(a%2ll==0ll);
	}
	b=b*power(2,Mod-2)%Mod;
	if(parity==1){
		printf("%lld/%lld",((b+1)*power(3,Mod-2))%Mod,b);
	}
	else{
		printf("%lld/%lld",((b-1+Mod)*power(3,Mod-2))%Mod,b);
	}
	return 0;
}

```


---

