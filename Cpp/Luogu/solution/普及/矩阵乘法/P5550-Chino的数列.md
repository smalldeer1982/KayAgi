# Chino的数列

## 题目背景

没有背景

我写不出来了qwq

## 题目描述

Chino给定了 $n$ 个数 $a_1...a_n$，给定常数 $s,m$ ，她会轮流对这 $n$ 个数做 $k$ 组操作，每组操作包含以下几步：

1. $\operatorname{swap}(a_s,a_m)$（交换 $a_s,a_m$）。

2. 将 $n$ 个数都向前平移一位（第 $1$ 个移动到第 $n$ 个位置上）。

Chino 想知道，$k$ 组操作后，这 $n$ 个数分别是多少？
 
Orz yky,dyh,wjk,jjy,cxr,gsy,cpy,zcy,tyz,yy,hz,zhr,ygg

## 说明/提示

对于 $40\%$ 的数据，$1 \leq k \leq 10^7$

对于 $100\% $的数据，$1 \leq n \leq 80$，$1 \leq s,m\leq n$，$1 \leq k \leq 10^{18}$

所有数字均在 `long long` 以内

## 样例 #1

### 输入

```
4 1 2 3
1 2 3 4```

### 输出

```
1 2 3 4```

# 题解

## 作者：Leianha (赞：40)

## 矩阵加速递推

n的范围比较小，k的范围很大，我们可以考虑从n入手。

首先我们知道任何矩阵*单位矩阵都不会改变.所以对于交换操作，我们可以造出一个这样的矩阵：

除了第s、m行，其他每一行都是f[i][i]=1;第s行:f[s][m]=1;第m行:f[m][s]=1;这样我们就完成了交换操作。

对于左移操作，我们也可以造出一个这样的矩阵：

除了第n行，其他每一行都是f[i][i+1]=1;第n行:f[n][1]=1;我们的初始矩阵f[i][1]=a[i];

因为矩阵符合结合律，所以我们可以用类似快速幂的方法加速。然后就可以啦，时间复杂度O($n^3$*log(k)).

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
long long n,s,m,k;
struct jz
{
	long long c[85][85];
}f,base,lin1,lin2;
jz operator * (const jz &a,const jz &b)//矩阵重载乘号 
{
    jz lin;
    for(int i=1;i<=80;++i)
    {
        for(int j=1;j<=80;++j)
        {
            lin.c[i][j]=0;
            for(int k=1;k<=80;++k)
            {
                lin.c[i][j]+=(a.c[k][j]*b.c[i][k]);
            }
        }
    }
    return lin;
}
jz ksm(jz a,long long b)
{
    jz anss;
    memset(anss.c,0,sizeof(anss.c));
    for(int i=1;i<=n;++i)anss.c[i][i]=1;
    for(;b;b>>=1,a=a*a)
    {
        if(b&1)
        anss=a*anss;
    }
    return anss;
}
void dy(jz x)//调试用的，可以忽略
{
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=n;++j)
		cout<<x.c[i][j]<<" ";
		cout<<endl;
	}
}
int main()
{
	cin>>n>>m>>s>>k;
	for(int i=1;i<=n;++i)scanf("%lld",&f.c[i][1]);
	for(int i=1;i<=n;++i)if(i!=s&&i!=m)lin1.c[i][i]=1;
	lin1.c[s][m]=lin1.c[m][s]=1;
	for(int i=1;i<=n-1;++i)lin2.c[i][i+1]=1;
	lin2.c[n][1]=1;
	base=lin1*lin2;
	base=ksm(base,k);
	f=f*base;
	for(int i=1;i<=n;++i)printf("%lld ",f.c[i][1]);
	return 0;
}
```


---

## 作者：5k_sync_closer (赞：20)

提供一个只需要推一个转移矩阵的做法。
# 思路
$n$ 很小，$k$ 很大，考虑矩阵加速递推。为了方便叙述，下文默认 $n=4,s=1,m=2$。

设 $\{a_n\}$ 经过一组操作后变为 $\{b_n\}$。定义转移矩阵 $P$，使得 $\begin{bmatrix}a_1\cdots a_n\end{bmatrix}\times P=\begin{bmatrix}b_1\cdots b_n\end{bmatrix}$。

如果只有平移操作，转移矩阵很显然：

$$\begin{bmatrix}0&0&0&1\\1&0&0&0\\0&1&0&0\\0&0&1&0\end{bmatrix}$$

如果先平移再交换，交换第 $s$ 列与第 $m$ 列即可：

$$\begin{bmatrix}0&0&0&1\\0&1&0&0\\1&0&0&0\\0&0&1&0\end{bmatrix}$$

考虑把先交换再平移转换为先平移再交换。

记 $s',m'$ 为 $s,m$ 向前平移后的位置，则 $s'=(s+n-2)\bmod n+1,m'=(m+n-2)\bmod n+1$。

容易发现，交换第 $s'$ 列与第 $m'$ 列即可。

$n=4,s=1,m=2$ 时，$s'=4,m'=1$，转移矩阵为：

$$\begin{bmatrix}1&0&0&0\\0&0&0&1\\0&1&0&0\\0&0&1&0\end{bmatrix}$$
# 代码
```cpp
#include <cstdio>
#include <cstring>
#define F(x) for(int x = 1;x <= n;++x)
int n, s, m;long long k;
struct S
{
	long long a[100][100];S() {memset(a, 0, sizeof a);}S operator*(S b)
	{S c;F(k) F(i) F(j) c.a[i][j] += a[i][k] * b.a[k][j];return c;}
}p, q;
int main()
{
	scanf("%d%d%d%lld", &n, &s, &m, &k);
	s = (s + n - 2) % n + 1;m = (m + n - 2) % n + 1;
	for(int i = 1;i <= n;++i)
	{
		scanf("%lld", &q.a[1][i]);if(i == s) p.a[m % n + 1][i] = 1;
		else if(i == m) p.a[s % n + 1][i] = 1;else p.a[i % n + 1][i] = 1;
	}
	for(;k;k >>= 1, p = p * p) if(k & 1) q = q * p;
	for(int i = 1;i <= n;++i) printf("%lld ", q.a[1][i]);return 0;
}
```


---

## 作者：GoldenFishX (赞：17)

**算法：矩阵乘法+快速幂**

不知道矩阵乘法是什么的请自行百度

=============================分割线=============================

## 1.生成转移矩阵

### 举个栗子:
首先，假设 $n=3,s=2,m=3$

- ### 操作 $1$ (交换 $a[s]$ 和 $a[m]$ )
首先弄一个 $3\times3$ 的单位矩阵:$\begin{pmatrix}1&0&0\\0&1&0\\0&0&1\end{pmatrix}$(不知道单位矩阵是什么的点[这里](https://baike.baidu.com/item/%E5%8D%95%E4%BD%8D%E7%9F%A9%E9%98%B5/8540268?fr=aladdin)) 

	然后交换第 $2$ 列和第 $3$ 列$(s=2,m=3)$：$\begin{pmatrix}1&0&0\\0&0&1\\0&1&0\end{pmatrix}$

	这就是操作 $1$ 的转移矩阵。



------------


- ### 操作 $2$ (将 $n$ 个数都向前平移一位)

$\begin{pmatrix}0&0&1\tiny\text{(3移到1)}\\1\tiny\text{(1移到2)}&0&0\\0&1\tiny\text{(2移到3)}&0\end{pmatrix}$


------------


最后将两个矩阵相乘：$\begin{pmatrix}1&0&0\\0&0&1\\0&1&0\end{pmatrix}\times\begin{pmatrix}0&0&1\\1&0&0\\0&1&0\end{pmatrix}=\begin{pmatrix}0&0&1\\0&1&0\\1&0&0\end{pmatrix}$

就是转移矩阵啦

部分代码：

```cpp
for(int i=1;i<=n;i++)
{
	cin>>b[i];//输入
	if(i==s)//生成第一个操作的转移矩阵
	{
		a1[i][m]=1;
	}
	else if(i==m)
	{
		a1[i][s]=1;
	}
	else
	{
		a1[i][i]=1;
	}
	a2[(i)%n+1][i]=1;//生成第二个操作的转移矩阵
}
calc3();//两个转移矩阵相乘
```
=============================分割线=============================

## 2.快速幂
不知道快速幂是什么的请点[这里](https://baike.baidu.com/item/%E5%BF%AB%E9%80%9F%E5%B9%82/5500243?fr=aladdin)

代码如下：
```cpp
void power(long long k)
{
	for(;k;k>>=1)
	{
		if(k&1)
		{
			calc1();//b=a*b
		}
		calc2();//a*=a
	}
}
```
=============================分割线=============================
## 完整代码
```cpp
#inclued<bits/stdc++.h>
using namespace std;
long long a[101][101],b[101],c[101],d[101][101];
int a1[101][101],a2[101][101];//用来存操作1和操作2的转移矩阵
long long n;
void calc1()
{
	for(int i=1;i<=n;i++)
	{
		c[i]=0;
	}
	for(int j=1;j<=n;j++)
	{
		for(int k=1;k<=n;k++)
		{
			c[j]+=b[k]*a[k][j];
		}
	}
	for(int i=1;i<=n;i++)
	{
		b[i]=c[i];
	}
}
void calc2()
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			d[i][j]=0;
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			for(int k=1;k<=n;k++)
			{
				d[i][j]+=a[i][k]*a[k][j];
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			a[i][j]=d[i][j];
		}
	}
}
void calc3()
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			d[i][j]=0;
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			for(int k=1;k<=n;k++)
			{
				d[i][j]+=a1[i][k]*a2[k][j];
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			a[i][j]=d[i][j];//a为转移矩阵 
		}
	}
}
void power(long long k)
{
	for(;k;k>>=1)
	{
		if(k&1)
		{
			calc1();
		}
		calc2();
	}
}
int main() 
{
	long long s,m,k;
	cin>>n>>s>>m>>k;
	for(int i=1;i<=n;i++)//输入和构造转移矩阵
	{
		cin>>b[i];
		if(i==s)
		{
			a1[i][m]=1;
		}
		else if(i==m)
		{
			a1[i][s]=1;
		}
		else
		{
			a1[i][i]=1;
		}
		a2[(i)%n+1][i]=1;
	}
	calc3();
	power(k);
	for(int i=1;i<=n;i++)//输出
	{
		cout<<b[i]<<" ";
	}
	return 0;
}
```
温馨提示，请不要抄袭哦。

既然你都认真看完了这篇蒟蒻的题解，留个赞再走吧

## 更新日志:
2020-5-11 13:35:51 增加一些注释

---

## 作者：zh_dou (赞：9)

~~人生第一道矩乘题，一遍过~~

## 分析
对于数据范围进行分析，$n$ 很小而 $k$ 很大，可以考虑到矩阵快速幂优化递推

考虑构造一个矩阵来存储 $a$ 数组，
即：$A=\left\|a_1,a_2,\cdots,a_n\right\|$
##### 操作1
我们把数组前移一位，利用矩阵乘法的原理，可以构造出 $B_1$ 使 

$A*B_1=\left\|a_2,a_3,\cdots,a_n,a_1\right\|$

如对于样例，$B_1=\left\|\begin{array}{cc}0&0&0&1\\1&0&0&0\\0&1&0&0&\\0&0&1&0\end{array}\right\|$
##### 操作2
我们把数组交换两位，利用矩阵乘法的原理，可以构造出 $B_2$ 使 

$A*B_2=\left\|a_1,a_2,\cdots,a_{s-1},a_m,a_{s+1},\cdots,a_{m-1},a_s,a_{m+1},\cdots,a_n\right\|$

此时我们只需将单位矩阵中的两列交换即可

如对于样例，$B_2=\left\|\begin{array}{cc}0&1&0&0\\1&0&0&0\\0&0&1&0&\\0&0&0&1\end{array}\right\|$
##### 结合
根据矩阵乘法那套理论~~手玩样例~~，将 $B_1$ 和 $B_2$ 相乘即可得到 $B=B_1*B_2$

根据矩阵乘法具有结合律，我可以用快速幂加速矩阵递推，则最终结果为 $A*B^k$ 的第一行

## 代码
$\mathcal{Code:}$
```cpp
#include<map>
#include<queue>
#include<cmath>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 100010
#define int long long
#define debug cout<<__LINE__<<" "<<__FUNCTION__<<"\n"

inline int read(){
	int x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*y;
}
void put(int x){
	if(x<0) putchar('-'),x=-x;
	if(x>=10) put(x/10);
	putchar((x%10)+48);
}
int n,s,m,t;
struct Martix{
    int c[110][110];
    Martix(){memset(c,0,sizeof c);}
    friend Martix operator * (const Martix &x,const Martix &y){
	    Martix res;
		for(int i=1;i<=n;i++)//枚举矩阵1的行 
			for(int j=1;j<=n;j++)//枚举矩阵2的列
				for(int k=1;k<=n;k++)//累加 
					res.c[i][j]+=x.c[i][k]*y.c[k][j];
	    return res;
	}
}ans,a;
inline Martix ksm(Martix a,int b){
    Martix res;
    for(int i=1;i<=n;i++) res.c[i][i]=1;//记得赋单位矩阵 
    while(b){
        if(b&1) res=res*a;
        a=a*a;
        b>>=1;
    }
    return res;
}
signed main(){
// 	freopen(".in","r",stdin);
// 	freopen(".out","w",stdout);
	n=read();s=read();m=read();t=read();
    for(int i=1;i<=n;i++) ans.c[1][i]=read();
    for(int i=1;i<=n;i++){//B1 
    	a.c[i%n+1][i]=1;
    }
    swap(a.c[s],a.c[m]);//交换两列 
    //我直接将两个矩阵合并了，两种写法等价 
    ans=ans*ksm(a,t);
    for(int i=1;i<=n;i++) cout<<ans.c[1][i]<<" ";
//	fclose(stdin);
//	fclose(stdout);
    return 0;
}


```


---

## 作者：Pisces (赞：7)

这道题是真的水,我考场上用不需要矩阵快速幂的模拟都拿了最优解

其实只要直接模拟找到循环节,再模拟一遍就可以了(向前移动一位只需把第一位移到最后去即可)

$Code$:

```cpp
#include<bits/stdc++.h>
#define f(i,a,b) for(register int i(a);i<=b;++i)
using namespace std;
typedef long long ll;
inline ll read(){//快读
	ll X=0;bool d=0;char ch=0;
	while(!isdigit(ch)) d|=ch=='-',ch=getchar();
	while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
	return d?-X:X;
}
ll a[6500],b[15000];
bool t;
inline void swap(ll &x,ll &y){//交换
	x^=y^=x^=y;
}
int main(){
	int n=read(),s=read(),m=read(),k=read(),j=1;
	f(i,1,n) b[i]=a[i]=read();
	for(;j<=k;++j){//模拟找循环节
		t=0;
		swap(a[j],a[n+j]);
		swap(a[s+j],a[m+j]);
		f(i,1,n){
			if(a[i+j]!=b[i]){
				t=1; break;
			}
		}
		if(!t) break;
	}
	k%=j;
	for(j=1;j<=k;++j){//再次模拟
		swap(b[s+j-1],b[m+j-1]);
		swap(b[j],b[n+j]);
	}
	f(i,j,n+j-1) cout<<b[i]<<' ';
	return 0;
}
```

---

## 作者：YellowBean_Elsa (赞：5)

## 这题真的适合作为比赛的第一题


#### 思维难度： 普及T3
#### 代码难度： 普及T2
#### 洛谷难度： 普及+/提高

我一看，怎么可能模拟……

我再一看，矩阵加速不好用……(然而……）

我一模拟，咦好像有循环……

#### 是啊，每个数每次向前移一位，到m时变到s，对于每一个数，回到自己的初始位置所用次数相同。

数据很小，可以直接模拟来找循环节。每次操作后check即可。

（其实可能可以直接根据 s，m 的位置算出循环节，但我太弱不会搞。其实这就像PJ2018T2一样你不会用二分因为时间复杂度允许。）

不废话了，上代码吧：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,s,m;
ll k;
ll a[100],t[100];
//t是找循环节时用的临时数组  
int head=1,end;//记录序列头和序列尾 
int cycle=0;//循环节长度 
inline void add(int &x){//向前移一位 
	if(x==n)x=1;
	else x++;
}
inline void cswap(ll &a,ll &b){//手写swap（QAQ） 
	ll l=a;
	a=b;b=l;
}
inline bool check(){//判断现序列与原序列是否一样，用于找循环节 
	for(int i=1;i<=n;i++)
		if(t[i]!=a[i])return 0;
	return 1;
}
int main(){
	scanf("%d%d%d%lld",&n,&s,&m,&k);
	for(int i=1;i<=n;++i){
		scanf("%lld",&a[i]);
		t[i]=a[i];
	}
	while(++cycle){//找循环节 
		cswap(t[s],t[m]);
		add(head);add(s);add(m);
		if(check())break;
	}
	k%=cycle;//敲黑板！ 
	head=1;
	for(int i=1;i<=k;++i){
		cswap(a[s],a[m]);
		add(head);add(s);add(m);
	}
	//愉快输出 
	if(head==1)end=n;
	else end=head-1;
	for(int i=head;i!=end;add(i))
		printf("%lld ",a[i]);
	printf("%lld\n",a[end]);
	return 0;
}
```
## next time!

---

## 作者：JA_yichao (赞：4)

[**题目传送门**](https://www.luogu.com.cn/problem/P5550)

[**博客食用**](https://blog.csdn.net/Jackma_mayichao/article/details/111399886)

- # 思路

这道题是对一个数列进行操作，

然后又发现操作次数达到了惊人的 $k≤10^{18}$

所以考虑用**矩阵乘法加速**。

---
怎么转移呢？**（用 $n=3$ 的情况举例）**

首先我们知道
形如 $B=\begin{pmatrix}1 & 0&0\\0 &1&0\\0&0&1\end{pmatrix}$ 的矩阵是单位矩阵，且 $X\times B=X$。

那么将 $a_s$ 和 $a_m$ 调位就只需将单位矩阵中的s列和m列调换位置即可。

再考虑如何将n个数都向前平移一位，

和 $B$ 类似,第i列的1的行位置就是第i+1列的行位置（n除外）

那么转移矩阵就是 $C=\begin{pmatrix}0 & 0&1\\1 &0&0\\0&1&0\end{pmatrix}$
这样题目中的操作就变成了(原数列为 $A$ ) 

ANS=$A\times \underbrace{B \times C\times B\times C...B\times C}_{n}$

然后可以把 $SAB=B\times C$ 先算出来，就可以直接计算$SAB^n$ 了。

套一个**快速幂**即可，$n=3$ 可以推广到 $n=80$ 。

- # 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
long long a[101][101],b[101][101],sab[101][101];
long long ci[2][101],ans[101][101];
int n,s,m,k;
void jzcf()
{
	long long c[101][101];
	for(int i=1; i<=n; i++)
	 for(int j=1; j<=n; j++)
	    c[i][j]=0;
	for(int i=1; i<=n; i++)
	 for(int j=1; j<=n; j++)
	  for(int k=1; k<=n; k++)
	     c[i][j]=c[i][j]+a[i][k]*b[k][j];
	for(int i=1; i<=n; i++)
	 for(int j=1; j<=n; j++)
	    sab[i][j]=c[i][j]; 
}
void jzcf1()
{
	long long c[101][101];
	for(int i=1; i<=n; i++)
	 for(int j=1; j<=n; j++)
	    c[i][j]=0;
	for(int i=1; i<=n; i++)
	 for(int j=1; j<=n; j++)
	  for(int k=1; k<=n; k++)
	     c[i][j]=c[i][j]+sab[i][k]*ans[k][j];
	for(int i=1; i<=n; i++)
	 for(int j=1; j<=n; j++)
	    ans[i][j]=c[i][j];
}
void jzcf2()
{
	long long c[101][101];
	for(int i=1; i<=n; i++)
	 for(int j=1; j<=n; j++)
	    c[i][j]=0;
	for(int i=1; i<=n; i++)
	 for(int j=1; j<=n; j++)
	  for(int k=1; k<=n; k++)
	     c[i][j]=c[i][j]+sab[i][k]*sab[k][j];
	for(int i=1; i<=n; i++)
	 for(int j=1; j<=n; j++)
	    sab[i][j]=c[i][j];
}
void jzcf3()
{
	long long c[101][101];
	for(int i=1; i<=n; i++)
	 for(int j=1; j<=n; j++)
	    c[i][j]=0;
	for(int i=1; i<=1; i++)
	 for(int j=1; j<=n; j++)
	  for(int k=1; k<=n; k++)
	     c[i][j]=c[i][j]+ci[i][k]*ans[k][j];
	for(int i=1; i<=1; i++)
	 for(int j=1; j<=n; j++)
	    ci[i][j]=c[i][j];
}
void ksm(int x)
{
	for(int i=1; i<=n; i++)
	   ans[i][i]=1;
	while(x!=0)
	 {
	 	if(x&1)
	 	  jzcf1();
	 	jzcf2();
	 	x>>=1;
	 }
}
int main()
{
	cin>>n>>s>>m>>k;
	for(int i=1; i<=n; i++)
	   scanf("%lld",&ci[1][i]);
	for(int i=1; i<=n; i++)
	   a[i][i]=1;
    a[s][m]=1,a[m][s]=1,a[s][s]=0,a[m][m]=0;  //交换s和m
    for(int i=1; i<=n-1; i++)
	   b[i+1][i]=1;
	b[1][n]=1;
	jzcf();  //B*C
	ksm(k);
	jzcf3();
	for(int i=1; i<=n; i++)
	   printf("%lld ",ci[1][i]);
	return 0;
}
```


---

## 作者：　　　吾皇 (赞：4)

### 题目分析
```
一开始看到想要暴力做..看到k<=10^18果断放弃。由于操作都是相同的（s和m的值不发生改变），所以猜测会有循环，而我们要做的就是手写判断一个数列是否出现过。这里可以用map，但注意要自己定义一个结构体比较函数
```
### 代码
```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
int a[101],s,m,n,h;//由于n<=80，所以不用开很大
long long k;
struct node{
	int p[101];
	bool operator < (const node x) const{
		for(register int i=1;i<=n;i++)
		    if(p[i]!=x.p[i]) return p[i]<x.p[i];
		return false;
	}//这里随便弄一个比较函数就行，但一定要能使两个不同的序列分开
}t,x[1000001];//不知道多少次会有循环为保险起见
map<node,bool>q;//这里用map，一个序列对应一种bool值（主要不会手写）
int main(){
	scanf("%d %d %d %lld",&n,&s,&m,&k);
	for(register int i=1;i<=n;i++)scanf("%d",&a[i]);//读入，用register加一点速
	for(register int i=1;i<=k;i++){
		swap(a[s],a[m]);
		for(register int j=1;j<=n;j++) a[j-1]=a[j];
		a[n]=a[0];//进行题中所述的操作
		for(register int j=1;j<=n;j++) x[i].p[j]=t.p[j]=a[j];//将当前序列导入结构体中
		if(q[t]){//判断是否出现过
			h=k%(i-1);//求出循环节并算出是第几个
			for(register int j=1;j<=n;j++) printf("%d ",x[h].p[j]);
			return 0;//结束程序
		}
		q[t]=true;//将该序列的bool值设为true
	}
	for(register int i=1;i<=n;i++) printf("%d ",x[k].p[i]);//如果最后一次操作时才开始循环或没有进入过循环，输出当前序列
}
```

---

## 作者：Link_Cut_Y (赞：3)

本题算法：**矩阵快速幂**

------------

 - 题意：
 
 给定一个长度为 $n$ 的数列 $a$，要求进行两种操作：
 
 1. 将指定的两个数 $a_s, a_m$ 交换。
 2. 将第 $2 - n$ 个数向前移动一个，将第一个数移动到最后一个。
 
 求连续执行上面两个操作 $k$ 次后，数列的值变为多少。
 
 - 做法分析：
 
 由于 $k$ 达到了惊人的 $10^{18}$ ，所以考虑使用矩阵乘法来加速。
 
 对于题目中给定的两种操作，我们分别来讨论。
 
 1. 交换操作
 
 也就是问怎样将 $a = [a_1, a_2 \dots a_s \dots  a_m \dots a_n]$ 变成 $a = [a_1, a_2 \dots a_m \dots  a_s \dots a_n]$。
 
 考虑构造一个中间矩阵 $tmp$，使得 $a \times tmp$ 可以得到目标序列。
 
 易得，矩阵 $tmp$ 即为：除第 $s, m$ 行外，主对角线上的值为 1 （$tmp[i][i] = 1$）。第 $s$ 行第 $m$ 列和第 $m$ 行第 $s$ 列为 1
 
 2. 移动操作
 
 也就是问怎样将 $a = [a_1, a_2 \dots a_n]$ 变成 $a = [a_2\dots a_n, a_1]$。
 
 构造的中间矩阵就是：将第二行到第 $n$ 行，行数 - 1列变成一，第一行第 $n$ 列变成1，其他都是零。
 
 这样，我们只需要使用矩阵快速幂，$O(\log k)$ 的复杂度就可以算出来了。（常数有点大）。
 
 - **code**
 
```
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 82;

int n, m, s, k;
int Swap[N][N], Move[N][N], w[N];
int a[N][N];

void mul(int tar[], int a[], int b[][N])
{
	int temp[N] = {0};
	
	for (int i = 0; i < n; i ++ )
		for (int j = 0; j < n; j ++ )
			temp[i] = temp[i] + a[j] * b[j][i];
			
	memcpy(tar, temp, sizeof temp);
}

void mul(int tar[][N], int a[][N], int b[][N])
{
	int temp[N][N] = {0};
	
	for (int i = 0; i < n; i ++ )
		for (int j = 0; j < n; j ++ )
			for (int k = 0; k < n; k ++ )
				temp[i][j] = temp[i][j] + a[i][k] * b[k][j];
				
	memcpy(tar, temp, sizeof temp);
}


int main()
{
	cin >> n >> s >> m >> k;
	s -- , m -- ;
	
	for (int i = 0; i < n; i ++ ) cin >> w[i];
	
	// 创造交换矩阵 
	for (int i = 0; i < n; i ++ )
		if (i != s && i != m)
			Swap[i][i] = 1;
	Swap[s][m] = Swap[m][s] = 1;
	
	// 创造移动矩阵
	for (int i = 1; i < n; i ++ )
		Move[i][i - 1] = 1;
	Move[0][n - 1] = 1;
	
	mul(a, Swap, Move); // 这里一定要注意了！！
	
	while (k) // 矩阵快速幂
	{
		if (k & 1) mul(w, w, a);
		mul(a, a, a);
		k >>= 1;
	}
	
	for (int i = 0; i < n; i ++ )
		cout << w[i] << ' ';
		
	return 0;
}
```

---

## 作者：Treaker (赞：3)

被迫做的。

这道题发现k很大，联想log的做法，再加上这里的变换是有规律的，就考虑矩阵加速递推。

然后A了。随便手玩一下，玩出矩阵即可
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
inline int read()
{
	int x = 0 , f = 1; char ch = getchar();
	while(ch < '0' || ch > '9')	{if(ch == '-')	f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9') {x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar();}
	return x * f;
}
int n , s , m;
long long t;
struct martix
{
	int f[81][81];
	martix() {memset(f,0,sizeof f);}
}ans;
martix operator * (const martix & x,const martix & y)
{
	martix res;
	for(int k = 1;k <= n;k ++)	for(int i = 1;i <= n;i ++)	for(int j = 1;j <= n;j ++)	res.f[i][j] = res.f[i][j] + x.f[k][j] * y.f[i][k];
	return res;
}
martix ksm(long long b)
{
	martix res , tmp , js;
	for(int i = 1;i <= n;i ++)	res.f[i][i] = 1;
	for(int i = 1;i <= n;i ++)
	{
		if(i == s)	tmp.f[i][m] = 1;
		else if(i == m)	tmp.f[i][s] = 1;
		else tmp.f[i][i] = 1;
		if(i < n) js.f[i][i+1] = 1;
		else js.f[i][1] = 1;
	}
	tmp = tmp * js;
	while(b)
	{
		if(b & 1)	res = res * tmp;
		tmp = tmp * tmp;
		b >>= 1;
	}
	return res;
}
int main()
{
	n = read(); s = read(); m = read();scanf("%lld",&t);
	for(int i = 1;i <= n;i ++)	ans.f[i][1] = read();
	ans = ans * ksm(t);
	for(int i = 1;i <= n;i ++)	printf("%d ",ans.f[i][1]);
	return 0;
}

```


---

## 作者：0xFF (赞：2)

#### 题目大意


------------
给定一个长度为 $n$ 的数列 $a$，给定 $s,m,k$。

对数列进行 $k$ 次操作：

1. 将 $a_s$ 与 $a_m$ 交换
2. 将 $n$ 个数都向前平移一位

输出 $k$ 次操作后的数列 $a$。

#### 思路分析


------------
首先考虑对于这两个操作分别构建转移矩阵 $A1,A2$，答案即为 $A \cdot (A1 \cdot A2)^k$。

对于操作 $1$ 构建如下矩阵：

$\begin{bmatrix}
  0&  1&  0& 0\\
  1&  0&  0& 0\\
  0&  0&  1& 0\\
  0&  0&  0& 1
\end{bmatrix}$

其中，第 $s$ 行第 $m$ 列与第 $m$ 行第 $s$ 列都为 $1$，相应的第 $s$ 行第 $s$ 列与第 $m$ 行第 $m$ 列要设为 $0$。

对于操作 $2$ 构建如下矩阵：

$\begin{bmatrix}
  0&  0&  0& 1\\
  1&  0&  0& 0\\
  0&  1&  0& 0\\
  0&  0&  1& 0
\end{bmatrix}$

就是把单位矩阵的每一个 $1$ 都向左移动一格，这样就可以做到将整个序列中的数都向左平移一位了。

最后只需要将 $k$ 次操作后的矩阵与最开始输入的序列构建的矩阵相乘即可得到答案。

#### 代码实现


------------
```cpp
struct Matrix{
	long long c[N][N];
}A,E1,E2,base;
int n;
Matrix operator * (const Matrix &x,const Matrix &y){
	Matrix a;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			a.c[i][j] = 0;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			for(int k=1;k<=n;k++){
				a.c[i][j] += x.c[i][k] * y.c[k][j];
			}
		}
	}
	return a;
}

int main(){
	n = read();
	int s = read() , m = read() , k = read();
	for(int i=1;i<=n;i++){
		base.c[1][i] = read();
	}
	for(int i=1;i<=n;i++){
		E1.c[i][i] = A.c[i][i] = 1;
	}
	E1.c[s][m] = E1.c[m][s] = 1;
	E1.c[s][s] = E1.c[m][m] = 0;
	
	for(int i=1;i<=n;i++){
		E2.c[(i%n)+1][i] = 1;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cout<<E2.c[i][j]<<" ";
		}
		cout<<endl;
	}
	E1 = E1 * E2;
	while(k > 0){
		if(k & 1) A = A * E1;
		E1 = E1 * E1;
		k >>= 1;
	}
	base = base * A;
	for(int i=1;i<=n;i++){
		cout<<base.c[1][i]<<" ";
	}
	return 0;
}
```


---

## 作者：FjswYuzu (赞：2)

Chino的题终于加入题库啦！

---

因为$k \leq 10^{18}$，所以说这道题直接模拟是会超时的

首先我们要知道，经过一定次操作之后，一定会回到一开始的序列

我们只需要一直模拟，模拟到开始的序列的时候，我们就找到了循环节。

循环节是肯定不会超过200的，所以并不会超时

设循环节长度为$x$，则我们只需要再模拟$k \text{ }mod \text{ }x $次操作，我们就可以得到正确答案

代码奉上

```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
using namespace std;
int a[85],t[85];
bool check(int n){
	for(int i=1;i<=n;++i)	if(a[i]!=t[i])	return false;
	return true;
}//判断两个序列是否相同
int main(){
	int n,s,m,k;
	scanf("%d %d %d %d",&n,&s,&m,&k);
	for(int i=1;i<=n;++i)	scanf("%d",&a[i]),t[i]=a[i];
	int f=0;
	do
	{
		++f;
		swap(a[s],a[m]);
		for(int i=1;i<n;++i)	swap(a[i],a[i+1]);
	}while(!check(n));//模拟找循环节
	k%=f;
	for(int times=1;times<=k;++times)
	{
		swap(t[s],t[m]);
		for(int i=1;i<n;++i)	swap(t[i],t[i+1]);
	}//找到循环节进行模拟
	for(int i=1;i<=n;++i)	printf("%d ",t[i]);
	return 0;
}
```

---

## 作者：cyrxdzj (赞：1)

### 一、思路

这道题其实不需要矩阵乘法什么的，本题的操作其实会循环，一遍一遍地模拟，计算出循环节即可。

### 二、完整代码

```cpp
#include<cstdio>
using namespace std;
long long array[10000][85];//输入&计算循环节。
long long n,s,m,k,cycle=1;
//cycle表示循环节长度。
void swap(long long &a,long long &b)//交换代码。
{
	long long temp=a;
	a=b;
	b=temp;
}
bool check()//检查数组是否一致。
{
	for(int i=1;i<=n;i++)
	{
		if(array[0][i]!=array[cycle][i])
		{
			return false;
		}
	}
	return true;
}
int main()
{
	scanf("%lld%lld%lld%lld",&n,&s,&m,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&array[0][i]);
	}
	while(true)
	{
		swap(array[cycle-1][s],array[cycle-1][m]);//暂时调换。
		array[cycle][n]=array[cycle-1][1];//操作2。
		for(int i=2;i<=n;i++)
		{
			array[cycle][i-1]=array[cycle-1][i];
		}
		swap(array[cycle-1][s],array[cycle-1][m]);//一定要记得对原数组调换回来！
		if(check())
		{
			break;
		}
		else
		{
			cycle++;
		}
	}
	for(int i=1;i<=n;i++)
	{
		printf("%lld ",array[k%cycle][i]);//输出时就可以利用循环节。
	}
	printf("\n");
	return 0;//完结撒花！
}

```

By [dengzijun](https://www.luogu.com.cn/user/387836)

---

## 作者：Skies (赞：1)

~~这题机房大佬说矩阵乘法就可以水过去~~


但小菜鸡不懂，写了个简单易懂但思路，还是最优解

## 讲解 ##

DALAO:"凡是反复的操作，必有循环节"


于是乎我们就只需要找到循环节就可以了

用c数组存初始数组，然后每次较即可

## 上代码
```cpp
#include<bits/stdc++.h>
#define ull unsigned long long 
#define ll unsigned long long 
using namespace std;
const int mod=1e9+7;
#define N 110
ull n;
int p1[N],p2[N],g[N];
int num;
struct node{
	ll a[105][105];
	node(){
		memset(a,0,sizeof(a));
	}
};
node ans,st;
node operator *(const node &x,const node &y){
	node z;
	for(int i=1;i<=num;i++)
	{
		for(int j=1;j<=num;j++)
		{
			for(int r=1;r<=num;r++)
			{
				z.a[i][j]+=x.a[i][r]*y.a[r][j]%mod;
				z.a[i][j]%=mod;
			}
		}
	}
	return z;
}
ull f[110];
int main()
{
	int b,c;
	cin>>n>>b;
	for(int i=1;i<=b;i++)
	{
		scanf("%d",&p1[i]);
	}
	sort(p1+1,p1+b+1);
	b=unique(p1+1,p1+b+1)-p1-1;
	cin>>c;
	for(int i=1;i<=c;i++)
	{
		scanf("%d",&p2[i]);
	}
	sort(p2+1,p2+c+1);
	c=unique(p2+1,p2+c+1)-p2-1;
	num=1;
	for(int i=1;i<=b;i++)
	{
		int o=lower_bound(p2+1,p2+c+1,p1[i])-p2;
		if(p2[o]==p1[i])
		{
			g[num]=p1[i];
			num++;
		}
	}
	num--;
//	cout<<num<<" ";
//	for(int i=1;i<=num;i++)
//	{
//		cout<<g[i]<<" ";
//	}
	f[0]=1;
	for(int i=1;i<=g[num];i++)
	{
		for(int j=1;j<=num;j++)
		{
			if(i-g[j]>=0)
			f[i]+=f[i-g[j]];
		}
	}
	

	for(int i=1;i<=num;i++)
	{
		ans.a[1][i]=1;
		ans.a[i][1]=1;
	}
	int k=6;
	while(k--)
	{
		ans=ans*ans;
	}
	ull y=0;
	for(int i=num;i>=1;i--)
	{
		y+=ans.a[1][num-i+1]*f[g[i]];
	}
	cout<<y;
	
	
	return 0;
}
```cpp


---

## 作者：Wuyanru (赞：0)

当我第一眼看到这道题的时候，嗯，这好像就是一道暴力模拟题。

让而当我看到了数据范围，好吧，暴力超时肯定妥妥的。

其实这道题是一道矩阵快速幂的问题，对于刚学习矩阵快速幂的同学是一道很好的练习题。

如果只是用矩阵来做这道题的话，显然还是会超时，但如果使用了矩阵快速幂，那我们的时间可以说是非常宽裕了。

既然用到了矩阵快速幂，那么我们可以创建一个关于矩阵的结构体，最好重构运算符，这样能使我们在写代码时方便很多，代码如下：
```
struct mat
{
    long long m,n;
    long long a[100][100]; 
    mat operator * (mat& b)  //重构乘法运算符
    {
        mat c;
        memset(c.a,0,sizeof(c.a));
        c.m=m;
        c.n=b.n;
        for(int i=1;i<=m;i++)
            for(int j=1;j<=b.n;j++)
                for(int p=1;p<=n;p++)
                {
                    c.a[i][j]+=(a[i][p]*b.a[p][j])%1000000007;
                    c.a[i][j]%=1000000007;
                }
        return c;
    }
};
```
当然，不使用结构体也是一个选择，可以使用二维数组存下各个数字。

等等，为什么要用一个二维数组来存一个只有一行的矩阵呢？

因为两个矩阵 $ A $ 与 $ B $ 相乘的必要条件为矩阵 $ A $ 的列数等于矩阵 $ B $ 的行数，相乘的结果矩阵 $ C $ 的行数等于矩阵 $ A $ 的行数，矩阵 $ C $ 的列数等于矩阵 $ B $ 的列数。我们到时候在实现矩阵相乘的时候还需要一个 $ n \times n $ 的二维矩阵，所以我的结构体中开的是二维数组。

既然用到了矩阵快速幂，我们可以再编一个矩阵快速幂的函数。

循环实现快速幂：
```
mat mut(mat a,long long t)
{
    mat ans;
    memset(ans.a,0,sizeof(ans.a));
    ans.m=ans.n=n;
    for(int i=1;i<=n;i++)
        ans.a[i][i]=1;
    while(t)
    {
        if(t&1)
            ans=ans*a;
        a=a*a;
        t=t/2;
    }
    return ans;
}
```
递归实现快速幂：
```
mat mut(mat a,long long t)
{
    if(t==1)
        return a;
    if(t==0)
    {
        mat b;
        b.m=b.n=n;
        memset(b.a,0,sizeof(b.a));
        for(int i=1;i<=k+3;i++)
            b.a[i][i]=1;
        return b;
    }
    mat ans;
    ans.m=ans.n=3;
    memset(ans.a,0,sizeof(ans.a));
    ans=mut(a,t/2);
    ans=ans*ans;
    if(t%2==1)
        ans=ans*a;
    return ans;
}
```
那么下一个问题来了：既然用到了矩阵相乘，那么到底是哪两个矩阵在进行相乘呢？

第一个进行相乘的矩阵我们很容易知道，它就是输入中的 $ n $ 个数，所以这个矩阵是这样的：

$ \begin{vmatrix}
a_{1}  &a_{2}  &a_{3}  &\cdots  &a_{n}
\end{vmatrix} $

显然，第二个矩阵是通过另一个矩阵进行快速幂得到的。

而进行快速幂的矩阵显然也可以通过两个矩阵相乘得到。

这两个矩阵一个是用于交换两数位置的，另一个是将 $ n $ 个数进行移动的，我们可以通过两个函数分别构造出他们，代码如下：
```
void nb1(mat& num)
{
    memset(num.a,0,sizeof(num.a));
    num.m=num.n=n;
    for(int i=1;i<=num.m;i++)
        num.a[i][i]=1;
    num.a[s][s]=num.a[m][m]=0;
    num.a[s][m]=num.a[m][s]=1;
}
void nb2(mat& num)
{
    memset(num.a,0,sizeof(num.a));
    num.m=num.n=n;
    for(int i=1;i<=n;i++)
        if(i!=n)
            num.a[i+1][i]=1;
        else
            num.a[1][i]=1;
}
```
这两个矩阵构造好了，那这道题不久被我们给做出来了吗？

接下来要做的就只是快速幂、矩阵相乘和输出了。

AC代码如下：
```
#include<cstring>
#include<cstdio>
using namespace std;
struct mat
{
    long long m,n;
    long long a[100][100]; 
    mat operator * (mat& b)  //重构乘法运算符
    {
        mat c;
        memset(c.a,0,sizeof(c.a));
        c.m=m;
        c.n=b.n;
        for(int i=1;i<=m;i++)
            for(int j=1;j<=b.n;j++)
                for(int p=1;p<=n;p++)
                {
                    c.a[i][j]+=(a[i][p]*b.a[p][j])%1000000007;
                    c.a[i][j]%=1000000007;
                }
        return c;
    }
};
int n,m,s,k;
void nb1(mat& num)
{
    memset(num.a,0,sizeof(num.a));
    num.m=num.n=n;
    for(int i=1;i<=num.m;i++)
        num.a[i][i]=1;
    num.a[s][s]=num.a[m][m]=0;
    num.a[s][m]=num.a[m][s]=1;
}
void nb2(mat& num)
{
    memset(num.a,0,sizeof(num.a));
    num.m=num.n=n;
    for(int i=1;i<=n;i++)
        if(i!=n)
            num.a[i+1][i]=1;
        else
            num.a[1][i]=1;
}
mat mut(mat a,long long t)
{
    mat ans;
    memset(ans.a,0,sizeof(ans.a));
    ans.m=ans.n=n;
    for(int i=1;i<=n;i++)
    	ans.a[i][i]=1;
    while(t)
    {
        if(t&1)
            ans=ans*a;
        a=a*a;
        t=t/2;
    }
    return ans;
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&s,&k);
    mat ans,num,num1,num2;
    ans.m=1;
    ans.n=n;
    for(int i=1;i<=n;i++)
        scanf("%d",&ans.a[1][i]);
    nb1(num1);
    nb2(num2);
    num=num1*num2;
    num=mut(num,k);
    ans=ans*num;
    for(int i=1;i<=n;i++)
        printf("%d ",ans.a[1][i]);
    return 0;
}
```
感谢观看！

刚刚格式不对，重新修改了一下哈，辛苦管理员了。

---

## 作者：Sternenlicht (赞：0)

思路：

上来看到 $1 \le n \le 80$，$1 \le k \le 10^{18}$，考虑从 $n$ 入手。可用矩阵乘法存储 $a$ 数组，设初始矩阵为 $A$。

操作 $1$：交换单位矩阵中第 $s$ 列和第 $m$ 列即可。设得到的矩阵为 $X$。

操作 $2$：向前平移一位后，第 $i$ 行 列的位置就是第 $i+1$ 行 列的位置，特殊的，第 $n$ 行 列的位置是第 $1$ 行 列的位置。设得到的矩阵为 $Y$。

最终答案：因为矩阵乘法具有结合律，可用快速幂加速，$A \times (X \times Y)^k$ 的第一行即为答案。

```cpp
#include <bits/stdc++.h>
namespace IO{
	#define LL long long
	inline LL read(){
		LL x=0,f=1;char c=getchar();
		for (;!isdigit(c);c=getchar())if (c=='-')f=-1;
		for (;isdigit(c);c=getchar())x=(x<<3)+(x<<1)+(c^48);
		return x*f;
	}
	inline void write(LL x,char c='\n'){
		if (x){
			if (x<0)x=-x,putchar('-');
			char a[30];short l;
			for (l=0;x;x/=10)a[l++]=x%10^48;
			for (l--;l>=0;l--)putchar(a[l]);
		}else putchar('0');putchar(c);
	}
}using namespace IO;
using namespace std;
 
#ifndef int
#define int long long//不开long long见祖宗 
const int N = 100;
struct node{
	int a[N][N];
	node(){memset(a,0,sizeof(a));}//初始化矩阵
}A,ans;//A是初始矩阵，ans是答案矩阵
int n,s,m,k;
node operator * (const node &x,const node &y){//重载运算符 
	node res;//返回值
	for (int k=1;k<=n;k++)//矩阵乘法模板 
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++)
				res.a[i][j]=res.a[i][j]+x.a[i][k]*y.a[k][j];
	return res;//返回最终结果 
}
node ksm(node A,int b){//矩阵快速幂 
	node res;
	for (int i=1;i<=n;i++)res.a[i][i]=1;//单位矩阵
	while (b){//矩阵快速幂模板 
		if (b&1)res=res*A;//前面已经重载运算符了，这里可以直接用*
		A=A*A;b>>=1;
	} 
	return res;
}
signed main(){
	n=read(),s=read(),m=read(),k=read();
	for (int i=1;i<=n;i++)ans.a[1][i]=read();
	for (int i=1;i<=n;i++)A.a[i%n+1][i]=1;//初始化操作2单位矩阵
	swap(A.a[s],A.a[m]);//操作1，交换第s列和第m列
	ans=ans*ksm(A,k);//操作2，矩阵快速幂优化
	for (int i=1;i<=n;i++)write(ans.a[1][i],' ');//输出 
	#endif
	return 0;
}
```

---

## 作者：X_yea (赞：0)

## Solution
分析数据范围，$n$ 很小而 $k$ 很大，考虑矩阵快速幂优化递推

那么我们的目标矩阵便为：
$$F'=\begin{bmatrix}a_1&a_2&\cdots&a_n\end{bmatrix}$$
欲从上一步的状态矩阵变换乘目标矩阵，我们需构造出$n*n$的转移矩阵

一般地，转移矩阵$A$构造方法为
$$A_{i,j}=d\Leftrightarrow F'_j+=d*F_i$$
依照上述构造方法，我们可以构造出转移矩阵  
#### 对于交换操作
令
$$A_{s,m}=1,A_{m,s}=1,A_{i,i}=1(i\neq s\&\&i\neq m) $$
#### 对于移位操作
令
$$A_{i+1,i}=1,A_{1,n}=1(i<n) $$

转移矩阵的其余位均为0。

将两种操作的转移矩阵相乘即可得到最终的转移矩阵。 

再将状态矩阵与转移矩阵相乘即可得到目标矩阵。  

用矩阵快速幂搞一下就好了
## Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define clr(a) memset(a,0,sizeof(a))
#define fill(a) memset(a,0x3f,sizeof(a))
#define int long long
#define maxn 105
using namespace std;

inline int read() {
	int a=0,b=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') b=-1;c=getchar();}
	while(c>='0'&&c<='9') {a=(a<<1)+(a<<3)+c-'0';c=getchar();}
	return a*b;
}

int n,s,m,c[81],ans[81];

struct node{
	int a[81][81]; 
	node(){
		memset(a,0,sizeof a);
	}
	inline void build(){
		for(int i=1;i<=n;++i)a[i][i]=1;
	}
}mat;

node operator *(const node &x,const node &y){
	node z;
	rep(k,1,n) rep(i,1,n) rep(j,1,n)
		z.a[i][j]=z.a[i][j]+x.a[i][k]*y.a[k][j];
	return z;
}

int k;
node a1,a2,f;//三个转移矩阵

signed main(){
	n=read(),s=read(),m=read(),k=read();
	rep(i,1,n) c[i]=read();
	a1.a[s][m]=1,a1.a[m][s]=1;
	rep(i,1,n) if(i!=s&&i!=m) a1.a[i][i]=1;
	rep(i,1,n-1) a2.a[i+1][i]=1;
	a2.a[1][n]=1;
	mat=a1*a2;
	f.build();
	for(;k;k>>=1,mat=mat*mat)
		if(k&1) f=f*mat;
	rep(i,1,n){ 
		rep(j,1,n)
			ans[i]+=c[j]*f.a[j][i];
		printf("%d ",ans[i]);
	}
	return 0;
}
```

---

## 作者：MC_Launcher (赞：0)

### 矩阵快速幂的好题!

先讲点前置的知识

首先，矩阵是个好东西。

什么是矩阵呢？

矩阵顾名思义，是一个矩形的数阵，如下，是一个2×3的矩阵

| 3 | 1 | 4 |
| - | - | - |
| 5 | 2 | 9 |

#### 矩阵的运算法则

矩阵加法：当两个矩阵的行数与列数相同时，两个矩阵可以相加，相加后的矩阵的行数和列数等于原矩阵的行数和列数，每个元素则是原来两个矩阵中对应元素之和。

但是这个我们用不上，我们要用矩阵乘法，如下

矩阵乘法：当一个矩阵的行数和另一个矩阵的列数相等时两个矩阵可以相乘，即一个$n×m$的矩阵$A$可以和一个$m×q$的矩阵$B$相乘，相乘后是一个$n×q$的矩阵$C$。这个矩阵的$AC_{i,j}$是第一个矩阵的第i行的每一个元素与第二个矩阵第j行的对应每一个元素相乘后相加结果。

举个栗子

| 1 | 0 |
| -----------: | -----------: |
| 0 | 1 |
| 1 | 1 |

与

| 0 | 1 | 1 |
| -----------: | -----------: | -----------: |
| 1 | 0 | 0 |

相乘

那么新矩阵规模是2×2，下面每个元素来逐步运算。

$C_{1,1}=A_{1,1}×B_{1,1}+A_{2,1}×B_{1,2}+A_{3,1}×B_{1,3}=1$

$C_{1,2}=A_{1,2}×B_{1,1}+A_{2,2}×B_{1,2}+A_{3,2}×B_{1,3}=2$

剩下两个我就不推了(~~因为我太懒了~~)

整个矩阵如下

| 1 | 2 |
| -----------: | -----------: |
| 1 | 0 |

那么矩阵乘法有什么用呢？用C++如何实现呢

我们可以将它作为数字转换的工具

像这道题说的那样，我们可以根据题意构造出一个矩阵对数列进行乘法操作从而变换，例如

数列$[1,2,3]$想将每个数字向前移动一格，怎么办？

这里先引入一个知识点：单位矩阵

单位矩阵就是一个除了对角线是1，其他地方都是0的方阵(行数和列数相等的矩阵)，相当于乘法中的1

比方说，我们的数列$[1,2,3]$乘以它的单位矩阵

```
1 0 0
0 1 0
0 0 1

```

之后，还是它本身

那么把它往前移一位呢？

那么我们将它的单位矩阵每一列向前移一位即可，这样矩阵变成

```
0 0 1
1 0 0
0 1 0
```

乘起来就可以将我们的数列转换成$[2,3,1]$了

同样的，我们向将$A_s,A_m$交换，将单位矩阵中的两列交换即可。

矩阵乘法是符合结合律不符合交换律的，因此将得出的两个矩阵乘起来再计算k次，用初始数列乘以这个结果，答案就出来了！

构造一个转换数列的矩阵是很重要的问题

矩阵相乘代码实现

```cpp
//c++
struct _jz//矩阵结构体
{
	long long a[81][81];
};
_jz cheng(_jz a,_jz b)
{
	_jz c={};答案矩阵
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			for(int k=1;k<=n;k++)//A矩阵的第i行与B矩阵的第j列相乘(反过来也可以)
			{
				c.a[i][j]+=a.a[i][k]*b.a[k][j];
			}
		}
	}
	return c; 
}
```


#### 快速幂

知道了矩阵乘法，那么我们需要进行幂运算，C++有个自带函数`pow(a,b)`计算a的b次方，但是这个太慢且容易溢出，那么我们自己来写一个快一点的呢？

暴力算法处理如下

```cpp
int pow_1(int a,int b)
{
	int c=1;
	while(b>0)
	{
		c*=a;
		b--;
	}
	return c;
}
```

那么这个算法运行速度是$O(n)$，当题目的数据范围一旦很大的时候就会超时

有更快的吗？

有

计算$2^{10}$

暴力算法算10次

那么如果我们算$4^5$呢？

只用6次(还有一次先将$2^10$处理成$4^5$)

按照这种思路继续分解，再算下去，诶？5除不尽2？！

怎么办？那么此时我们将5变成4，再将此时的底数4乘入答案，再次进行运算

接下来变成了$16^2$

再接下来试$256^1$，此时又是奇数幂，那么我们再次将256乘入答案，接下来，指数变成0了，运算完成，结果也是1024，共运算了5次，这个算法复杂度是$O(logn)$，在数字非常大时非常有用，为什么这个算法正确？

比方说计算$3^7$

那么我们将这个指数看成二进制

`1 1 1`

现在应该部分读者已经明白了，每次指数除以二的操作其实就是在二进制下向前移一位，我们每次将底数乘2就是将指数的平方转移到底数上，这也是相当于将指数除以二(自行搜索 初二 幂运算)。

有的时候运算需要取模，那么边取模边乘即可。

矩阵快速幂与数字快速幂相同

快速幂模板

```cpp
//c++
#define mod 1000000009
int pow_2(int a,int b)
{
	int ans=1;
	while(b>0)
	{
		if(b&1)
		{
			ans*=a;
			ans%=mod;
		}
		b/=2;
		a*=a;
		a%=mod;
	}
	return ans;
}
```

那么我们整个题目的代码也出来了，如下

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,s,m,k;//如题
struct _jz//矩阵结构体
{
	long long a[81][81];
};
_jz d1,d2,d3,ans;//前移矩阵，交换矩阵，两个矩阵乘起来，以及答案矩阵（虽然是数列，但这样可以方便一些，其他的地方是0，乘了不会增加）
_jz cheng(_jz a,_jz b)//矩阵乘法
{
	_jz c={};
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			for(int k=1;k<=n;k++)
			{
				c.a[i][j]+=a.a[i][k]*b.a[k][j];
			}
		}
	}
	return c; 
}//矩阵乘法
void ksm(long long z,_jz sss)
{
	if(z==0)return;
	if(z&1)
	{
		ans=cheng(ans,sss);
	}
	sss=cheng(sss,sss);
	z/=2;
	ksm(z,sss);
 }//递归快速幂(递归快速幂第一人)
int main()
{
	cin>>n>>m>>s>>k;//输入
	for(int i=2;i<=n;i++)
	{
		d1.a[i][i-1]=1;
	}
	d1.a[1][n]=1;//构造转换矩阵
	for(int i=1;i<=n;i++)
	{
		d2.a[i][i]=1;	
	}
	d2.a[s][s]=0;
	d2.a[m][m]=0;
	d2.a[s][m]=1;
	d2.a[m][s]=1;//构造交换矩阵
	d3=cheng(d2,d1);//相乘
	for(int i=1;i<=n;i++)
	{
		cin>>ans.a[1][i];//输入
	}
	ksm(k,d3);
	for(int i=1;i<=n;i++)cout<<ans.a[1][i]<<" ";//输出
}
```

#### 题解千万条，理解第一条。无脑抄题解，棕名两行泪。

如有不足之处请指出，感谢。

---

## 作者：皮卡丘最萌 (赞：0)

这题乍一看很难，但是难度只有黄题，所以觉得一定有规律。

模拟一下就可以发现这个数列是有循环节的。

那么我们在模拟时就可以保存每一个变化后的序列，再和前面所有的序列进行比较，只要发现相同，就可以判定出现循环。

比较这里可以只与第一个比较，减少时间复杂度。

这里有一种特殊情况，就是你还没有找到规律就做完了，这时只要直接输出即可，不然等你找到循环节再输出就会WA。

PS：注意数字的范围，要开longlong或int64.

其他的东西就和红题的模拟一样了。

上代码：

```pascal
var n,x,y,k,i,t,w:longint; 
tt:int64;
a:array[0..101] of int64;
b:array[0..100001,0..101] of int64;
function pd:boolean;
var i:longint;
begin
for i:=1 to n do
  if b[1,i]<>a[i] then exit(false);       
                              //有不同就返回false
exit(true);
end;                       //这一段是和前面的序列进行比较

begin
readln(n,x,y,k);
for i:=1 to n do read(a[i]);
w:=1; 
b[1]:=a;                     //保存初始序列
while true do
  begin
  tt:=a[x]; a[x]:=a[y]; a[y]:=tt;      //交换指定位置的数
  tt:=a[1];
  for i:=1 to n-1 do a[i]:=a[i+1];
  a[n]:=tt;                           
             //将n个数都向前平移一位(第1个移动到第n个位置上)
  inc(w);
  b[w]:=a;         //保存变化后的序列
  if w-1=k then
    begin
    for i:=1 to n do write(a[i],' ');
    halt;
    end;             //还没有找到规律就做完了，直接输出即可
  if pd then                   //找到了循环节
    begin
    k:=k mod (w-1)+1;         //推出结尾是第几个
    for i:=1 to n do
      write(b[k,i],' ');          //输出结果
    halt;
    end;
  end;
end.
```


---

