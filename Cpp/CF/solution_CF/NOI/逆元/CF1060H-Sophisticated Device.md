# Sophisticated Device

## 题目描述

给你两个正整数 $d$ 和 $p$，$p$ 是质数。

你还有一个神奇的机器，有很多个格子，每个格子有一个 0 到 $p-1$ 的整数。它还支持两种操作：求和与求 $d$ 次幂。 **结果都对 $p$ 取模。**

这些格子编号分别为 $1,2,3,\ldots,5000$，一开始第一、二个格子分别存储 $x,y(0\leq x,y\leq p-1)$，其余格子存储 1。

你不能直接访问格子里面的变量，你也**不知道** $x,y$ 为多少（但你知道它们分别存在前两格）。你应该使用给定的指令编写程序，让一个格子里面出现 $xy\mod p$。你的程序必须可以应对任何可能的 $x,y$。

加法指令把两个格子里面的数之和放进第三个格子。这个指令形如 `+ e1 e2 to`，用途是将第 $e1$ 格与第 $e2$ 格之和放入第 $to$ 格。$e1,e2,to$ 可以相等。

第二个指令将一个格子里的数的 $d$ 次幂放进另一个格子。这个指令形如 `^ e to`，用途是将第 $e$ 格数字的 $d$ 次幂放入第 $to$ 格。$e,to$可以相等，这时第 $e$ 格的数字将被覆盖。

最后一个指令返回答案。这个指令形如 `f target`，用途是表示第 $target$ 格就是所求的 $xy\mod p$。这之后不应有任何指令。

编写程序求出 $xy\mod p$。指令总数不应超过 5000 条，包括返回答案的指令在内。

保证有解。

## 说明/提示

本题**没有样例**。下面是个例子。注意这不是任何一个数据的解，仅仅为了说明格式。

```text
+ 1 1 3
^ 3 3
+ 3 2 2
+ 3 2 3
^ 3 1
f 1
```


|步骤  |格1  |格2  |格3  |
| :-----------: | :-----------: | :-----------: | :-----------: |
|最初  |$x$  |$y$  |$1$  |
|`+ 1 1 3`|$x$  |$y$  |$2x$  |
|`^3 3`  |$x$  |$y$  |$(2x)^d$  |
|`+3 2 2`  |$x$  |$y+(2x)^d$  |$(2x)^d$  |
|`+ 3 2 3`  |$x$  |$y+(2x)^d$  |$y+2*(2x)^d$  |
|`^ 3 1`  |$(y+2*(2x)^d)^d$  |$y+(2x)^d$  |$y+2*(2x)^d$  |

# 题解

## 作者：破壁人五号 (赞：12)

[自己博客的广告](https://wallbreaker5th.github.io/2018/%E9%A2%98%E8%A7%A3-CF1060H-Sophisticated%20Device/)，若以后有修改多半只写在自己博客中。

[题目链接](https://www.luogu.org/problemnew/show/CF1060H)

这道题实在是毒瘤。~~以及洛谷上的翻译其实是我翻的，质量跟机翻差不多。~~

首先我们确定求出 $xy$ 的整体思路——$xy=\frac{(x+y)^2-x^2-y^2}{2}$。

这个思路不难想到：我们能够比较容易实现的两个操作数的运算只有加、减，于是我们将运算转换为加、减与只有一个操作数的平方、除以 2。关键在于如何实现这些运算。

### 前置技能

- 快速幂/乘

- 高斯消元

- exgcd 求乘法逆元

- 少量数学知识

- 大量耐心

我们先考虑几个简单的运算：

## 0

在求解过程中，有一个数字 0 是很方便的，利用 `+ zero zero x` 就可以清空一格。

在这里需要用到快（慢？）速乘，实现：

```cpp
int f=p-1;
while(f){
    if(f&1ll){
        cout<<"+ "<<4998<<" "<<zero<<" "<<zero<<endl;
    }
    cout<<"+ "<<4998<<" "<<4998<<" "<<4998<<endl;
    f/=2;
}
//zero=4999
```

这样 `zero` 格就有了一个常数 0。

## 乘以常数

同样是快速乘。要注意的是，**每次必须清空所需格子**。

```cpp
int getmulti(int a,int b,int q){
    b=(b%p+p)%p;
    int ans=(q?q:++tot);
    int x=++tot;
    while(b){
        if(b&1ll){
            cout<<"+ "<<x<<" "<<ans<<" "<<ans<<endl;
        }
        cout<<"+ "<<x<<" "<<x<<" "<<x<<endl;
        b/=2;
    }
    return ans;
}
//如果有 q ，答案存在 q 当中。返回结果所在格子。
```

## 减法

$a-b=a+(p-1)b$

```cpp
int jian(int a,int b){
    b=getmulti(b,p-1);
    ++tot;
    cout<<"+ "<<a<<" "<<b<<" "<<tot<<endl;
    return tot;
}
```

## 除以常数

即乘以其逆元。

---

下面是重头戏：

# 求一个数的平方

很明显，$x^2$ 并不能通过 $x^d$ 直接求出。

我们考虑将 $x^2$ 表达为 $a_0(x+0)^d+a_1(x+1)^d+\dots +a_d(x+d)^d$

将它展开，再按 $x$ 合并同类项，得：

$x^2=C_d^0(a_0+a_1+\dots +a_d)x^d+$

$C_d^1(a_0\times0^1+a_1\times1^1+\dots a_d\times d^1)x^{d-1}+$

$\dots$

$C_d^d(a_0\times0^d+a_1\times1^d+\dots +a_d\times d^d)x^0$

显然我们要求 $x^2$ 项的系数为 1，其余为 0。于是我们可以列出线性方程组，通过高斯消元求出 $a_0,a_1,\dots ,a_d$。

```cpp
c[1][1]=1;
for(int i=1;i<=d+1;i++){
    for(int j=1;j<=i;j++){
        if(i==1&&j==1)continue;
        c[i][j]=c[i-1][j]+c[i-1][j-1];
    }
}
for(int i=0;i<=d;i++){
    int q=1;
    for(int j=0;j<=d;j++){
        a[j][i]=c[d+1][j+1]*q%p;
        q*=i;
        q%=p;
    }
}
a[d-2][d+1]=1;
for(int i=0;i<=d;i++){
    bool ok=false;
    int j=0;
    for(;j<=d;j++){
        if(a[j][i]&&!u[j]){
            ok=true;
            u[j]=true;
            break;
        }
    }
    double orz=a[j][i];
    for(int k=0;k<=d+1;k++){
        a[j][k]*=getinv(orz,1,p);
        a[j][k]%=p;
    }
    for(int k=0;k<=d;k++){
        if(k==j)continue;
        orz=a[k][i]*=getinv(a[j][i],1,p);
        for(int l=0;l<=d+1;l++){
            a[k][l]-=orz*a[j][l];
            a[k][l]=(a[k][l]%p+p)%p;
        }
    }
}
```
实际求的时候，只需要用公式 $x^2=a_0(x+0)^d+a_1(x+1)^d+\dots +a_d(x+d)^d$ 耐心算就可以了。

```cpp
int getpow2(int x){
    int q=++tot;
    cout<<"+ "<<x<<" "<<zero<<" "<<q<<endl;
    int sum=++tot;
    cout<<"+ "<<zero<<" "<<zero<<" "<<sum<<endl;
    int po=++tot;
    int mul=++tot;
    for(int i=0;i<=d;i++){
        cout<<"^ "<<q<<" "<<po<<endl;
        getmulti(po,a[i][d+1],mul);
        cout<<"+ "<<mul<<" "<<sum<<" "<<sum<<endl;
        cout<<"+ "<<q<<" "<<4997<<" "<<q<<endl;
    }
    return sum;
}
```

最后就将这些 simple 的操作联合起来：

```cpp
int x2=getpow2(1);
int y2=getpow2(2);
int q=jian(xysum2,x2);
jian(q,y2);
int ans=getmulti(tot,getinv(2,1,p));
cout<<"f "<<ans<<endl;
```

完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int getint(){
    int ans=0,f=1;
    char c=getchar();
    while(c>'9'||c<'0'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        ans=ans*10+c-'0';
        c=getchar();
    }
    return ans*f;
}

const int inf=19260817;
int extgcd(int a,int b,int& x,int& y){
    if(b){
        int r=extgcd(b,a%b,y,x);
        y-=x*(a/b); return r;
    } else { x=1; y=0; return a; }
}
int getinv(int a,int b,int M){
    int x,y,r=extgcd(a,M,x,y);
    if(b%r) return -1; else x=(x+M)%M*b/r;
    return x%(M/r);
} 

int tot=2,zero=4999;
int d,p;
int getinv(int x){
    int inv=getinv(d,p-2,p);
    ++tot;
    cout<<"^ "<<x<<" "<<tot<<endl;
    for(int i=0;i<inv-1;i++){
        cout<<"^ "<<tot<<" "<<tot<<endl;
    }
    return tot;
}

int a[20][20],c[20][20];

int getpow2(int x);
int getmulti(int a,int b,int q=0);
int jian(int a,int b);

int getpow2(int x){
    int q=++tot;
    cout<<"+ "<<x<<" "<<zero<<" "<<q<<endl;
    int sum=++tot;
    cout<<"+ "<<zero<<" "<<zero<<" "<<sum<<endl;
    int po=++tot;
    int mul=++tot;
    for(int i=0;i<=d;i++){
        cout<<"^ "<<q<<" "<<po<<endl;
        getmulti(po,a[i][d+1],mul);
        cout<<"+ "<<mul<<" "<<sum<<" "<<sum<<endl;
        cout<<"+ "<<q<<" "<<4997<<" "<<q<<endl;
    }
    return sum;
}

int getmulti(int a,int b,int q){
    b=(b%p+p)%p;
    int ans=(q?q:++tot);
    cout<<"+ "<<zero<<" "<<zero<<" "<<ans<<endl;
    int x=++tot;
    cout<<"+ "<<zero<<" "<<a<<" "<<x<<endl;
    while(b){
        if(b&1ll){
            cout<<"+ "<<x<<" "<<ans<<" "<<ans<<endl;
        }
        cout<<"+ "<<x<<" "<<x<<" "<<x<<endl;
        b/=2;
    }
    return ans;
}

int jian(int a,int b){
    b=getmulti(b,p-1);
    ++tot;
    cout<<"+ "<<a<<" "<<b<<" "<<tot<<endl;
    return tot;
}
bool u[20];
signed main(){
    d=getint(),p=getint();

    c[1][1]=1;
    for(int i=1;i<=d+1;i++){
        for(int j=1;j<=i;j++){
            if(i==1&&j==1)continue;
            c[i][j]=c[i-1][j]+c[i-1][j-1];
        }
    }

    for(int i=0;i<=d;i++){
        int q=1;
        for(int j=0;j<=d;j++){
            a[j][i]=c[d+1][j+1]*q%p;
            q*=i;
            q%=p;
        }
    }
    a[d-2][d+1]=1;
    for(int i=0;i<=d;i++){
        bool ok=false;
        int j=0;
        for(;j<=d;j++){
            if(a[j][i]&&!u[j]){
                ok=true;
                u[j]=true;
                break;
            }
        }
        double orz=a[j][i];
        for(int k=0;k<=d+1;k++){
            a[j][k]*=getinv(orz,1,p);
            a[j][k]%=p;
        }
        for(int k=0;k<=d;k++){
            if(k==j)continue;
            orz=a[k][i]*=getinv(a[j][i],1,p);
            for(int l=0;l<=d+1;l++){
                a[k][l]-=orz*a[j][l];
                a[k][l]=(a[k][l]%p+p)%p;
            }
        }
    }
    int f=p-1;
    while(f){
        if(f&1ll){
            cout<<"+ "<<4998<<" "<<zero<<" "<<zero<<endl;
        }
        cout<<"+ "<<4998<<" "<<4998<<" "<<4998<<endl;
        f/=2;
    }
    cout<<"+ "<<1<<" "<<2<<" "<<(++tot)<<endl;
    int xysum2=getpow2(tot);
    
    int x2=getpow2(1);
    int y2=getpow2(2);
    int q=jian(xysum2,x2);
    jian(q,y2);
    int ans=getmulti(tot,getinv(2,1,p));
    cout<<"f "<<ans<<endl;

    return 0;
}
```

---

## 作者：NotTogawaButSakiko (赞：4)

# CF1060H Sophisticated Device 
## 前言
主体思路借鉴于[@破壁人五号](https://www.luogu.com.cn/user/37676)的题解，菜鸡在此之上做了一些小改动和优化（？），并且感谢同机房大佬[@Surround_By_Gugugu](https://www.luogu.com.cn/user/154970)提供的优化思路。%%%%%%%

[题目传送门](https://www.luogu.com.cn/problem/CF1060H)


## Step 1 转化

我们只能进行两个操作：加法和 $d$ 次幂。而我们要求的是 $xy(mod\ p)$。我们自然而然地想到**龟速乘**，但显然龟速乘无法适用于两个未知量相乘。似乎已经无处下手了。

我们再来看看我们要求的式子，面对如此熟悉的式子，很自然我们就能想到它能转化成 $\frac{(x + y) ^ 2 - x^2 - y^2}{2}$ ，并且这个式子满足对称性，所以问题就转化为了如何构造指令，使得 $\frac{(x + y) ^ 2 - x^2 - y^2}{2}$ 出现在其中一个格子里。

## Step 2 乘法
龟速乘。

## Step 3 减法
$a +(p-1)b ≡ a-b(mod\ p)$

## Step 4 除法
乘法逆元。楼上用的是扩欧求逆元，但 $p$ 给定的是质数，显然可以用费马小定理求逆元。

## Step 5 平方
思路来自于[@破壁人五号](https://www.luogu.com.cn/user/37676)。

当无法直接求出一个数的幂时，我们考虑构造一个多项式来求解。~~也就是瞎凑~~

我们将 $x^2$ 用 $\Sigma^d_{i=0} a_i(x+i)^{d - i}$ 来表示，展开后即为
$$x^2=\Sigma^d_{i=0} C(d,i)x^{d-i}\Sigma^d_{j = 0}a_jj^i$$
显然，对于 $x^i(i \ne 2)$ 项时，我们要使 $C(d,i)\Sigma^d_{j = 0}a_jj^i$ 为 0（此时可以顺便把 $C(d,i)$ 约掉），而对于二次项时为1。我们便可以推出一个 $d+1$ 项线性方程组，用高斯消元求解即可。

## Step 6 “0”
其实不用非要求0，但是求0后可以更快并且更清晰地构造代码。

加 $p-1$ 次1即可。

## AC Code

```cpp
//CF1060H
//构造+高斯消元+逆元 
#include <bits/stdc++.h>
#define ll long long
#define re register
using namespace std;
inline ll read(){//快读 
	ll s = 0, w = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') w = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9'){s = (s << 1) + (s << 3) + (ch ^ 48); ch = getchar();}
	return s * w;
}
ll d, p, a[15][15], tot = 2, m[15];
void zero(){	//在5000位存0 
	ll b = p - 1;
	while(b){
		if(b & 1)	printf("+ 5000 4999 5000\n");
		printf("+ 4999 4999 4999\n");
		b >>= 1;
	}
}
ll quickpow(ll x, ll y){	//快速幂
	ll ans = 1;
	while(y){
		if(y & 1)	ans = ans * x % p;
		x = x * x % p;
		y >>= 1;
	}
	return ans % p;
}
void guass(){ //高斯-约旦消元 
//约旦消元对于高斯消元的优点在于不用回带。高斯消元解完后为一个上三角行列式，约旦消元解完后为对角型行列式。
	for(re ll i = 0; i <= d; i++){
		for(re ll j = 0; j <= d; j++){
            a[i][j] = quickpow(j, i);
            if(i == d - 2)	a[i][j] = a[i][j] * d  * (d - 1) / 2 % p;
        }       
		if(i == d - 2)	a[i][d + 1] = 1;
		else	a[i][d + 1] = 0;
	}
	for(re ll i = 0; i <= d; i++){
		ll mmax = i;
		for(re ll j = i + 1; j <= d; j++)	if(fabs(a[j][i]) > fabs(a[mmax][i]))	mmax = j;
		for(re ll j = 0; j <= d + 1; j++)	swap(a[i][j], a[mmax][j]);
		for(re ll j = 0; j <= d; j++){
			if(j == i)	continue;
			double b = a[j][i] * quickpow(a[i][i], p - 2) % p;
			for(ll k = 0; k <= d + 1; k++){
				a[j][k] -= a[i][k] * b;
				a[j][k] = (a[j][k] % p + p) % p;
			}
		}
	}
	for(re ll i = 0; i <= d; i++)	m[i + 1] = a[i][d + 1] * quickpow(a[i][i], p - 2) % p;//将解存入数组
}
ll multi(ll x, ll y){//乘法 
	ll b = y % p;	
	ll a = ++tot;
	ll ans = ++tot;
	printf("+ 5000 5000 %lld\n", ans);
	printf("+ 5000 %lld %lld\n", x, a);
	while(b){
		if(b & 1)	printf("+ %lld %lld %lld\n", a, ans, ans);
		printf("+ %lld %lld %lld\n", a, a, a);
		b >>= 1;
	}
	return ans;
} 
ll getpow(ll x){//平方 
	ll a = ++tot;
	ll b = ++tot;
	ll ans = ++tot;
	printf("+ 5000 %lld %lld\n", x, a);
	printf("+ 5000 5000 %lld\n", b);
	printf("+ 5000 5000 %lld\n", ans);
	for(re ll i = 1; i <= d + 1; i++){
		printf("+ %lld %lld %lld\n", a, b, ++tot);
		printf("^ %lld %lld\n", tot, tot + 1);
		tot++;
		ll tmp = multi(tot, m[i]);
		printf("+ 4998 %lld %lld\n", b, b);
		printf("+ %lld %lld %lld\n", ans, tmp, ans);
	}
	return ans;
}
ll Minus(ll a, ll b){//减法 
	b = multi(b, p - 1);
	ll ans = ++tot;
	printf("+ %lld %lld %lld\n", a, b, ans);
	return ans;
}
int main(){
	d = read(), p = read();
	zero();	guass();	
	printf("+ 1 2 %lld\n", ++tot);
	ll xplusy2 = getpow(tot), x2 = getpow(1), y2 = getpow(2);
	ll fz = Minus(Minus(xplusy2, x2), y2);
	ll ans = multi(fz, quickpow(2, p - 2));
	printf("f %lld", ans);
	return 0;
}
```


---

## 作者：MatrixGroup (赞：2)

## 链接

[$\KaTeX$ 版本](https://www.luogu.com.cn/paste/y8cm501c)

[视频题解](https://www.bilibili.com/video/BV1PG4y197z1/)

## 前言

第一个 \*3300，还是独立做出来的，很感动啊。于是现在补了这个一个题解。

## 题目大意

有长度为 $5000$ 的数组 $a$，$a_1=s$，$a_2=t$，$a_3$ 至 $a_{5000}$ 均为 $1$。

给定质数 $p$ 和正整数 $d$，你需要做不超过 $5000$ 次形如以下的操作：

1. $\boxed{\texttt{+ x y z}}$ 表示 $a_z\gets (a_x+a_y)\bmod p$。
2. $\boxed{{\texttt{\^ }\texttt{ x y}}}$ 表示 $a_y\gets a_x^d\bmod p$。
3. $\boxed{\texttt{f x}}$ 表示报告 $a_x=st\bmod p$。

你不需要保证 $x\neq y,x\neq z$ 或是 $y\neq z$。

你需要保证恰好有一次 $3$ 操作，并且它之后没有任何操作。

你不知道 $s,t$ 的值，你需要保证对于所有 $0\le s,t< p$ 都正确。

$2\le d\le 10,d<p\le10^9+9$。

## 题目解法


我们使用**自底而上**、**从特殊到一般**的做题策略。

### 自底而上

我们考虑如何实现一些基本操作。我们如何实现 $a_y\gets a_x\times c$？

事实上，我们可以使用快速幂的思想用 $\log$ 次操作来完成这一目标。注意到没有 $a_y\gets a_x$ 的操作，所以要预留几个数做加法。

参考实现：

```cpp
void multiplied_by(int x,int y,int c)//啥也没有时期的乘法
{
	c=(c%p+p)%p;
	if(c==0) c=p;
	if(c==1) c=p+1;
	if(c==2) c=p+2;
	c-=3;//没有赋值操作，所以要预留 3 个
	int temp_1=G(-1);
	int temp_2=G(-2);
	add_to(x,x,temp_2);
	add_to(x,x,temp_1);
	if(c&1) add_to(x,temp_1,temp_1);
	c>>=1;
	while(1)//快速幂
	{
		if(c&1) add_to(temp_2,temp_1,temp_1);
		c>>=1;
		if(c)add_to(temp_2,temp_2,temp_2);
		else break;
	}
	add_to(x,temp_1,y);
}
```

但是这样实在是有一点繁琐，因为它十分常用。我们可以用它先进行一些预处理：

```cpp
void init()//预处理常数
{
	multiplied_by(const_0,const_0,0);
	for(int i=2;i<=25;++i)add_to(const_1,const_v[i-1],const_v[i]);
	multiply_by(const_v[1],neg_v[1],p-1);
	for(int i=2;i<=25;++i)add_to(neg_v[1],neg_v[i-1],neg_v[i]);
}
```

这样就可以对常用的乘法减少一些操作次数：

```cpp
void multiply_by(int x,int y,int c)//预处理之后的乘法
{
	c=(c%p+p)%p;
	if(c==0){add_to(const_0,const_0,y);return;}
	if(c==1){add_to(const_0,x,y);return;}
	if(c==2){add_to(x,x,y);return;}
	if(c==3){int temp=G(-1);add_to(x,x,temp);add_to(x,temp,y);return;}
	if(c==4){add_to(x,x,y);add_to(y,y,y);return;}
	if(c==5){int temp=G(-1);add_to(x,x,temp);add_to(x,temp,y);add_to(y,temp,y);return;}
	//小数据特判
	int temp_1=G(-1);
	int temp_2=G(-2);
	add_to(x,const_0,temp_2);
	add_to(const_0,const_0,temp_1);
	if(c&1) add_to(x,temp_1,temp_1);
	c>>=1;
	while(c)
	{
		add_to(temp_2,temp_2,temp_2);
		if(c&1) add_to(temp_2,temp_1,temp_1);
		c>>=1;
	}
	add_to(temp_1,const_0,y);
}
```

还有一个常用操作是 $a_y\gets a_x+c$。我们考虑 $a_y\gets a_x+1\times c$ 即可。

```cpp
void add_by(int x,int y,int c)
{
	int temp_1=G(-114);c=(c%p+p)%p;
	if(c<=25){add_to(x,const_v[c],y);return;}
	if(p-c<=25){add_to(x,neg_v[p-c],y);return;}
	//小数据特判
	multiply_by(const_1,temp_1,c);
	add_to(x,temp_1,y);
}
```

### 从特殊到一般

我们考虑 $d=2$ 的情形。显然地，$xy=\dfrac{(x+y)^2-x^2-y^2}{2}$，减法可以使用乘 $p-1$ 实现，除以二可以使用乘 $2$ 的乘法逆元实现。

我们考虑扩展这个想法，但是 $xy=\dfrac{(x+y)^3-x^3-y^3}{3(x+y)}$ **是不行的**，因为你**无法**求一个**非常数**的逆元。

于是考虑是否可以在 $d>2$ 的情况下求出一个数的平方。根据**二项式定理**，

$$(x+a)^d=\sum\limits_{i=0}^d\binom{d}{i}x^ia^{n-i}$$

这里面**存在** $x^2$ 项。

我们使用**高斯消元**可以求出 $c_i$ 使得：

$$x^2=\sum\limits_{i=0}^d c_i(x+i)^d$$

于是我们就可以使用 $d+1$ 次 $\log $ 次数的乘法来**求出一个数的平方**，然后调用三次即可。

实现精细的话，显然不会超过 $5000$ 次操作。

关于为什么一定可以凑出来，你可以把表打出来，发现分母上的数都不会大于 $d$，这也是 $d<p$ 这个条件的**目的**。有**非打表**证明方法欢迎私信作者。

## 代码实现

注意到我们**知道** $x^1$ 和 $x^0$ 的值，所以可以少列两个方程。

```cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
int d,p;
int G(int v){if(v>=0) return v+1;return v+5001;}//随便拿一个没用的变量
const int const_1=133;//常数 1
const int const_0=139;//常数 0
const int const_v[26]={const_0,const_1,114,115,116,117,118,119,25,26,27,28,29,30,31,32,33,34,35,36,101,102,103,104,105,106};//常数i
const int neg_v[26]={const_0,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,256,257};//常数-i
ll qkpw(ll a,ll b,ll m){ll ret=1;while(b){if(b&1)ret=ret*a%m;a=a*a%m;b>>=1;}return ret;}//快速幂
int inv(ll x){return int(qkpw(x%p,p-2ll,p-0ll));}//计算逆元
void add_to(int x,int y,int z){cout<<"+ "<<x<<" "<<y<<" "<<z<<endl;}//操作 1
void pow_to(int x,int y){cout<<"^ "<<x<<" "<<y<<endl;}//操作 2
void multiplied_by(int x,int y,int c)//啥也没有时期的乘法
{
	//见上文
}
void multiply_by(int x,int y,int c)//预处理之后的乘法
{
	//见上文
}
void add_by(int x,int y,int c)
{
	//见上文
}
int cof[14][14],temp[14],value[14];
int binom[144][144];
void row_multiply(int v,int c)
{
	if(c==1) return;
	for(int i=0;i<=d;++i)
	cof[v][i]=(cof[v][i]*1ll*c)%p;
	value[v]=1ll*value[v]*c%p;
}
void row_add(int u,int v,int c)
{
	if(c==0) return; 
	for(int i=0;i<=d;++i)
	cof[v][i]=(cof[v][i]+cof[u][i]*1ll*c)%p;
	value[v]=(value[v]+value[u]*1ll*c)%p;
}
//初等行变换
void get_squared(int x,int y)// 计算平方
{
	int temp_1=G(-333),temp_2=G(-64);multiply_by(temp_2,temp_2,0);for(int i=0;i<=d-2;++i) temp[i]=G(-4-i);//拿一些临时变量
	binom[0][0]=1;for(int i=1;i<=142;++i){binom[i][0]=binom[i][i]=1;for(int j=1;j<i;++j){binom[i][j]=(binom[i-1][j]+binom[i-1][j-1])%p;}}//组合数
	for(int i=0;i<=d-2;++i)//预处理系数和值
	{
		add_by(x,temp_1,i);pow_to(temp_1,temp[i]);
		int cur=1;
		for(int j=d;j>=0;--j)
		{
			if(j>=2)
			{
				cof[i][j-2]=1ll*cur*binom[d][j]%p;
			}
			else
			{
				int v=1ll*cur*binom[d][j]%p;
				if(j==1)
				{
					multiply_by(x,temp_1,(p-v)%p);
					add_to(temp[i],temp_1,temp[i]);
				}
				else
				{
					add_by(temp[i],temp[i],(p-v)%p);
				}
			}
			cur=1ll*cur*i%p;
		}
		value[i]=(i==0);//平方要消到 1，其它 0
	}
	for(int i=0;i<=d-2;++i) for(int j=0;j<i;++j) swap(cof[i][j],cof[j][i]);//自己推一下式子，就能理解了
	for(int i=0;i<=d-2;++i)//消元
	{
		row_multiply(i,inv(cof[i][d-2-i]));
		for(int j=i+1;j<=d-2;++j)
		{
			row_add(i,j,(p-cof[j][d-2-i])%p);
		}
	}
	for(int i=d-2;i>=0;--i)//消元
	{
		for(int j=0;j<i;++j)
		{
			row_add(i,j,(p-cof[j][d-2-i])%p);
		}
	}
	for(int i=d-2;i>=0;--i)//得出结果
	{
		multiply_by(temp[i],temp[i],value[d-2-i]);
		add_to(temp_2,temp[i],temp_2);
	}
	add_by(temp_2,y,0);
}
void init()//预处理常数
{
	multiplied_by(const_0,const_0,0);
	for(int i=2;i<=25;++i)add_to(const_1,const_v[i-1],const_v[i]);
	multiply_by(const_v[1],neg_v[1],p-1);
	for(int i=2;i<=25;++i)add_to(neg_v[1],neg_v[i-1],neg_v[i]);
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin>>d>>p;
	init();
	get_squared(G(0),G(2));
	get_squared(G(1),G(3));
	add_to(G(0),G(1),G(4));
	get_squared(G(4),G(5));
	multiply_by(G(2),G(2),p-1);
	multiply_by(G(3),G(3),p-1);
	add_to(G(2),G(3),G(6));
	add_to(G(5),G(6),G(7));
	multiply_by(G(7),G(7),(p+1)/2);
	cout<<"f "<<G(7)<<endl;
    //d=2 的解法
	return 0;
}
```

---

## 作者：happybob (赞：0)

注意到 $xy = \dfrac{(x+y)^2-x^2-y^2}{2}$。

首先可以龟速乘算出 $x \times y$，其中 $x$ 是某个格子而 $y$ 是常数。

另一方面，也可以算出 $x-y$ 的结果，其中 $x$ 和 $y$ 都是格子，因为 $x+(p-1)y \equiv x-y \pmod p$，所以先让 $y$ 乘以 $p-1$ 后加上 $x$ 即可。

难的是怎么算 $x^2$。

$d=2$ 时很容易，$d>2$ 时，考虑到我们只能算 $x^d$，所以我们希望能求出一组 $a$ 使得 $x^2 = \sum \limits_{i=0}^d a_i(x+i)^d$，将后面的东西二项式展开，可以列出一个线性方程组，对方程组高斯消元，打表发现 $d \leq 10$ 时方程组必然有解，于是直接用 $a$ 计算即可。

下面的除以 $2$ 直接乘以 $2$ 的逆元即可。

注意到过程中你可能还需要求出某个格子使得其值为 $0$，也就是你需要将某个格子加上 $p-1$，这个东西直接对 $p-1$ 拆位做即可。

次数应该是很松的，我的实现不超过 $3000$ 次。

参考实现：


```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <array>
#include <vector>
#include <set>
#include <map>
#include <tuple>
#include <utility>
using namespace std;

constexpr int N = 30;

using ll = long long;

ll MOD;
array<ll, N> fac, ifac;
array<array<ll, N>, N> mt, rmt;
array<ll, N> val;

inline ll qpow(ll a, ll b)
{
	ll res = 1ll, base = a;
	while (b)
	{
		if (b & 1) res = res * base % MOD;
		base = base * base % MOD;
		b >>= 1ll;
	}
	return res;
}

int d;
int zero_pos, one_pos, temp, temp2, temp3, tmp5;
int xpos = 1, ypos = 2;

inline void add(int x, int y, int z)
{
	cout << "+ " << x << " " << y << " " << z << "\n";
}

inline void reset0(int x)
{
	cout << "+ " << zero_pos << " " << zero_pos << " " << x << "\n";
}

inline void reset1(int x)
{
	cout << "+ " << one_pos << " " << zero_pos << " " << x << "\n";
}

inline void mul(int x, ll y, int pos)
{
	reset0(pos);
	if (y == 0)
	{
		return;
	}
	else if (y == 1)
	{
		add(x, zero_pos, pos);
	}
	else
	{
		add(x, zero_pos, tmp5);
		reset0(x);
		while (y)
		{
			if (y & 1) add(x, tmp5, x);
			add(tmp5, tmp5, tmp5);
			y >>= 1;
		}
		add(x, zero_pos, pos);
	}
}

inline ll binom(int n, int m)
{
	return fac[n] * ifac[m] % MOD * ifac[n - m] % MOD;
}

inline void gauss()
{
	for (int j = 0; j <= d; j++)
	{
		for (int i = j; i <= d; i++)
		{
			if (mt[i][j])
			{
				swap(mt[i], mt[j]);
				break;
			}
		}
		for (int i = j + 1; i <= d; i++)
		{
			if (!mt[i][j]) continue;
			ll val = mt[i][j] * qpow(mt[j][j], MOD - 2ll) % MOD;
			for (int x = 0; x <= d + 1; x++)
			{
				mt[i][x] = (mt[i][x] - mt[j][x] * val % MOD + MOD) % MOD;
			}
		}
	}
	for (int i = d; i >= 0; i--)
	{
		val[i] = mt[i][d + 1];
		for (int j = i + 1; j <= d; j++)
		{
			val[i] = (val[i] - val[j] * mt[i][j] % MOD + MOD) % MOD;
		}
		val[i] = val[i] * qpow(mt[i][i], MOD - 2ll) % MOD;
	}
}

inline void square(int x)
{
	if (d == 2)
	{
		cout << "^ " << x << " " << x << "\n";
		return;
	}
	reset0(temp2);
	add(x, temp2, temp2);
	reset0(x);
	for (int i = 0; i <= d; i++)
	{
		reset0(temp);
		add(temp2, zero_pos, temp);
		for (int j = 1; j <= i; j++) add(temp, one_pos, temp);
		cout << "^ " << temp << " " << temp << "\n";
		mul(temp, val[i], temp3);
		add(x, temp3, x);
	}
}

inline void minuus(int a, int b)
{
	mul(b, MOD - 1, temp2);
	add(a, temp2, a);
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> d >> MOD;
	fac[0] = 1ll;
	for (int i = 1; i <= d; i++) fac[i] = fac[i - 1] * i % MOD;
	ifac[d] = qpow(fac[d], MOD - 2ll);
	for (int i = d - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;
	int now = 4997;
	zero_pos = 5000;
	one_pos = 4555;
	temp = 4998;
	temp2 = 3666;
	temp3 = 1145;
	tmp5 = 1737;
	for (int i = 31; i >= 0; i--)
	{
		if (((MOD - 1) >> i) & 1)
		{
			for (int j = 0; j < i; j++) add(now, now, now);
			add(now, zero_pos, zero_pos);
			now--;
		}
	}
	for (int i = now + 1; i <= 4997; i++) reset1(i);
	for (int j = 0; j <= d; j++)
	{
		for (int i = 0; i <= d; i++)
		{
			mt[j][i] = binom(d, j) * qpow(i, d - j) % MOD;
		}
		mt[j][d + 1] = (j == 2 ? 1 : 0);
	}
	gauss();
	add(1, 2, 3);
	// 3: x + y
	square(3);
	square(1);
	square(2);
	minuus(3, 1);
	minuus(3, 2);
	mul(3, qpow(2ll, MOD - 2ll), temp2);
	cout << "f " << temp2 << "\n";
	return 0;
}
```

---

