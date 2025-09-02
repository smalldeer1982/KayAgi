# GukiZ and Binary Operations

## 题目描述

We all know that GukiZ often plays with arrays.

Now he is thinking about this problem: how many arrays $ a $ , of length $ n $ , with non-negative elements strictly less then $ 2^{l} $ meet the following condition: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF551D/a6e7bc576316f94114c2b7ddad7b1f99dc329174.png)? Here operation ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF551D/620e07dca4a112648a0a9f81b5fb9f226c4bb233.png) means bitwise AND (in Pascal it is equivalent to and, in C/C++/Java/Python it is equivalent to &), operation ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF551D/6bfd82b83489db5433e1a03d2bc0f44671a33056.png) means bitwise OR (in Pascal it is equivalent to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF551D/6bfd82b83489db5433e1a03d2bc0f44671a33056.png), in C/C++/Java/Python it is equivalent to |).

Because the answer can be quite large, calculate it modulo $ m $ . This time GukiZ hasn't come up with solution, and needs you to help him!

## 说明/提示

In the first sample, satisfying arrays are $ {1,1},{3,1},{1,3} $ .

In the second sample, only satisfying array is $ {1,1} $ .

In the third sample, satisfying arrays are $ {0,3,3},{1,3,2},{1,3,3},{2,3,1},{2,3,3},{3,3,0},{3,3,1},{3,3,2},{3,3,3} $ .

## 样例 #1

### 输入

```
2 1 2 10
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2 1 1 3
```

### 输出

```
1
```

## 样例 #3

### 输入

```
3 3 2 10
```

### 输出

```
9
```

# 题解

## 作者：Alarm5854 (赞：2)

由于这题和二进制有关，所以考虑按位计算。

如果这一位结果为 $0$，那么也就是说 $n$ 个数中，不存在连续两个位置，使得这两个数的这一位都为 $1$。

令 $f_{i,0}$ 表示第 $i$ 个数为 $0$，满足条件的个数，$f_{i,1}$ 为第 $i$ 个数为 $1$，满足条件的个数，则有：

- $f_{i,0}=f_{i-1,0}+f_{i-1,1}$
- $f_{i,1}=f_{i-1,0}$

令 $g_i=f_{i,0}$，可得 $g_i=F_{i+2}$，$F_i$ 为斐波那契数列第 $i$ 项，利用矩阵快速幂或者倍增法即可。

这里说一下倍增法如何求：

- $F_{2k}=F_k\times(2F_{k+1}-F_k)$
- $F_{2k+1}=F_{k+1}^2+F_k^2$

常数比矩阵乘法小。

至于某一位为 $1$ 的方案数呢？既然总方案数为 $2^n$，为 $0$ 的方案数为 $F_{n+2}$，那么为 $1$ 的方案数就为 $2^n-F_{n+2}$。

因为所有位都是独立的，所以用乘法原理统计答案即可。

注意 $m$ 可以等于 $1$。

```cpp
#include<ctime>
#include<cstdio>
#include<cctype>
#define ll unsigned long long
using namespace std;
ll read(){
	char c;
	ll x=0,f=1;
	while(!isdigit(c=getchar()));
	while(isdigit(c)){
		x=x*10+(c-48);
		c=getchar();
	}
	return x;
}
ll n,k,l,m,a,b,res;
struct node{
	ll x,y;
	node(ll a=0,ll b=0){
		x=a;
		y=b;
	}
};
node fib(ll n){//返回的是(F(n),F(n+1))
	if(!n)
		return node(0,1);
	node t=fib(n>>1);
	ll a=t.x*(2*t.y-t.x+m)%m;
	ll b=(t.x*t.x+t.y*t.y)%m;
	if(n&1)
		return node(b,a+b);
	return node(a,b);
}
ll p(ll n){
	if(!n)
		return 1;
	ll t=p(n>>1);
	if(n&1)
		return t*t*2%m;
	return t*t%m;
}
int main(){
	n=read();
	k=read();
	l=read();
	m=read();
	res=1%m;
	a=fib(n+2).x;
	b=(p(n)-a+m)%m;
	for(ll i=0;i<l;++i){
		if((k>>i)&1)
			res=res*b%m;
		else
			res=res*a%m;
	}
	if(l<=63&&k>>l)
		res=0;
	printf("%llu",res);
	return 0;
}
```



---

## 作者：CQ_Bob (赞：1)

## 分析

奶龙不好玩。

很显然，我们每一位是独立的。那么现在问题就转化成：求有多少个序列 $A$，其中 $A_i\in\{0,1\}$。使得 $(A_1 \& A_2) | (A_2 \& A_3)|\dots |(A_{n-1} \& A_n)=x$，有 $x\in \{0,1\}$。

考虑直接 DP。因为一旦我们有至少一个 $A_{i-1}\& A_i=1$，那么总的值就是 $1$ 了。所以定义状态函数 $f_{i,j,0/1}$ 表示前 $i$ 个数，$A_i=j$，且之前是否有相邻两个数按位与的值为 $1$。那么有转移方程：

$$
f_{i,0,0}=f_{i-1,0,0}+f_{i-1,1,0}\\
f_{i,1,0}=f_{i-1,0,0}\\
f_{i,0,1}=f_{i-1,0,1}+f_{i-1,1,1}\\
f_{i,1,1}=f_{i-1,1,0}+f_{i-1,0,1}+f_{i-1,1,1}\\
$$

这个可以直接放矩阵上，做到 $O(4^2\log n)$。具体的，有：

$$
\left[\begin{array}{c}     
f_{i-1,0,0}&f_{i-1,0,1}&f_{i-1,1,0}&f_{i-1,1,1}
\end{array}\right] \times  \left[\begin{array}{c}     
1&0&1&0\\
0&1&0&1\\
1&0&0&1\\
0&1&0&1\\
\end{array}\right]=\left[\begin{array}{c}     
f_{i,0,0}&f_{i,0,1}&f_{i,1,0}&f_{i,1,1}
\end{array}\right]
$$

然后就可以做到 $O(4^2l\log n)$ 的复杂度。

## 代码

```cpp
int n,k,l,p;
struct Matrix{
	int a[4][4];
	int n,m;
};
Matrix add(Matrix a,Matrix b){
	Matrix c;
	memset(&c,0,sizeof(c));
	c.n=a.n,c.m=b.m;
	for(re int i=0;i<c.n;++i)
	for(re int j=0;j<c.m;++j)
	for(re int k=0;k<a.m;++k) c.a[i][j]=(c.a[i][j]+a.a[i][k]*b.a[k][j]%p)%p;
	return c;
}
il Matrix Qmi(Matrix a,int b){
	Matrix ans;
	memset(&ans,0,sizeof(ans));
	ans.n=ans.m=4;
	ans.a[0][0]=ans.a[1][1]=ans.a[2][2]=ans.a[3][3]=1;
	while(b){
		if(b&1) ans=add(ans,a);
		a=add(a,a),b>>=1;
	}
	return ans;
}

il void solve(){
	n=rd,k=rd,l=rd,p=rd;
	if(l<63&&(1ll<<l)-1<k) return printf("0\n"),void(0);
	int ans=1;
	for(re int i=0;i<l;++i){
		int w=((k>>i)&1);
		Matrix u,v;
		memset(&v,0,sizeof(v));
		memset(&u,0,sizeof(u));
		u.n=1,u.m=4;
		u.a[0][0]=u.a[0][2]=1;
		v.n=4,v.m=4;
		v.a[0][0]=v.a[0][2]=v.a[1][1]=v.a[1][3]=v.a[2][0]=v.a[2][3]=v.a[3][1]=v.a[3][3]=1;
		v=Qmi(v,n-1);
		u=add(u,v);	
		if(w==0) ans=ans*(u.a[0][0]+u.a[0][2])%p;
		if(w==1) ans=ans*(u.a[0][1]+u.a[0][3])%p;
	}printf("%lld\n",ans%p);
	return ;
}
```

---

## 作者：Hoks (赞：0)

## 前言
好久没写题了，思维下滑，只能写这种简单数数了。

摘自 [杂题选做](https://www.luogu.com.cn/training/627660)。
## 思路分析
二进制相关的数数。

首先考虑每位是否独立。

不难发现在本题中二进制下的每位互相独立。

所以我们只需要考虑对于一位的情况就可以了。

因为只考虑一位所以我们的值限制在了 $0,1$，总的可能性就是 $2^n$ 种。

那按照题目中给出的运算方式，得到 $1$ 就是**至少**有两个相邻的 $1$，得到 $0$ 就是不存在任何相邻的 $1$。

**至少**不太好计算，所以我们考虑先算出 $0$ 的答案再用总方案数减掉。

对于不存在任何相邻的 $1$ 我们考虑设计 dp：$f_{i,0/1}$ 表示 $i$ 这位填 $0/1$ 的方案数。

那么转移方程式就是：
$$f_{i,0}=f_{i-1,0}+f_{i-1,1}$$
$$f_{i,1}=f_{i-1,0}$$

此外我们还有边界条件 $f_{0,0}=1$。

不难发现其实这个就是斐波那契数列。

其中 $f_{n,1}$ 为斐波那契数列的第 $n$ 项，$f_{n,0}$ 为斐波那契数列的第 $n+1$ 项。

考虑用归纳证明（下文中 $F_i$ 表示斐波那契数列第 $i$ 项）：

首先我们已经有了 $f_{0,0}=F_1$。

假设 $f_{n,1}=F_n,f_{n,0}=F_{n+1}$ 对 $n$ 成立。

那么我们有：
$$f_{n+1,1}=f_{n,0}=F_{n+1}$$
$$f_{n+1,0}=f_{n,0}+f_{n,1}=F_{n}+F_{n+1}=F_{n+2}$$
所以上述结论对 $n+1$ 也成立。

所以我们用归纳法证明了：$$\forall n\ge0,f_{n,1}=F_n,f_{n,0}=F_{n+1}$$。

那么我们的答案就是 $f_{n,0}+f_{n,1}=F_{n+2}$。

所以直接[矩阵快速幂](https://www.luogu.com.cn/problem/P1962)预处理出 $0,1$ 时的答案就行了。

最后记得判一下 $k$ 最高位比 $l$ 大的还有模数可能为 $1$ 的情况。
## 代码

```cpp
#include <bits/stdc++.h>
#define mid ((l+r)>>1)
#define ls (p<<1)
#define rs (ls|1)
#define int long long
using namespace std;
const int N=1e6+10,V=5e4+10,M=4,INF=0x3f3f3f3f,lim=19;
int n,k,l,m,ans=1;
struct matrix
{
	int a[M][M];matrix(){memset(a,0,sizeof a);}
	matrix operator*(const matrix&b) const
	{
		matrix c;
		for(int i=1;i<=2;i++) for(int j=1;j<=2;j++)
			for(int k=1;k<=2;k++) c.a[i][j]=(c.a[i][j]+a[i][k]*b.a[k][j])%m;
		return c;
	}
}op;
namespace Fast_IO
{
	static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
	#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
	inline int read()
	{
		int x(0),t(1);char fc(getchar());
		while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
		while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
		return x*t;
	}
	inline void flush(){fwrite(out,1,length,stdout);length=0;}
	inline void put(char c){if(length==9999999) flush();out[length++]=c;}
	inline void put(string s){for(char c:s) put(c);}
	inline void print(int x)
	{
		if(x<0) put('-'),x=-x;
		if(x>9) print(x/10);
		put(x%10+'0');
	}
	inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
	inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
	inline void rd(char s[],int&n)
	{
		s[++n]=getchar();
		while(chk(s[n])) s[n]=getchar();
		while(ck(s[n])) s[++n]=getchar();
		n--;
	}
}
using namespace Fast_IO;
inline matrix ksm(matrix x,int y)
{
	matrix res=x;
	while(y){if(y&1) res=res*x;x=x*x;y>>=1;}
	return res;
}
inline int ksm(int x,int y,int mod)
{
    int res=1;
    while(y){if(y&1) res=res*x%mod;x=x*x%mod;y>>=1;}
    return res;
}
inline int get(int n)
{
	op.a[1][1]=op.a[1][2]=op.a[2][1]=1;
	return ksm(op,n).a[1][1];
}
inline void solve()
{
	n=read(),k=read(),l=read(),m=read();
	if(l<=63&&k>>l) return print(0);int w1=get(n),w2=(ksm(2,n,m)-w1+m)%m;
	for(int i=0;i<l;i++) ans=ans*(((1ull<<i)&k)?(i<=l?w2:0):w1)%m;print(ans%m);
}
signed main()
{
	int T=1;
	// T=read();
	while(T--) solve();
	genshin:;flush();return 0;
}
```

---

## 作者：swiftc (赞：0)

## Solution:

我们将 k 按二进制位考虑：

设$f[i][0]$为k的二进制位第$i$位为0时这一位的方案数，$f[i][1]$为k的二进制位第$i$位为1时这一位的方案数

对于 k 的每一位，如果为 0，那么每个 $and$ 的两个数的二进制最后一位一定不能均为 1，
由此得出转移方程：

$f [ i ] [ 0 ] = f [ i - 1 ] [ 1 ] + f [ i - 1 ] [ 0 ]$ 

$f [ i ] [ 1 ] = f [ i - 1 ] [ 0 ]$


因为这两个式子联立,所以$f[i][0]$显然是斐波那契数列，所以当 k 的一个二进制位为 0 时，可以用矩阵快速幂求出斐波那契数列的第 n+1 项，即为答案

如果为 1，至少有一个 $and$ 中的两个数的二进制最后一位均为 1, 所以我们可以用总方案数减去 k 位为 0 的情况的方案数,也就是 $2 ^ n - f [ n + 1 ]$，最后乘法原理把结果乘起来即可

## CODE:

```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
int n,k,l,m;
struct node{
	int a[3][3]={{0,0,0},{0,0,0},{0,0,0}};
	node operator *(const node &t)
	{
		node tmp;
		for(int i=1;i<=2;i++)
		for(int j=1;j<=2;j++)
		{
			for(int k=1;k<=2;k++)
			{
				tmp.a[i][j]+=(a[i][k]*t.a[k][j])%m;
				tmp.a[i][j]%=m;
			}
		}
		return tmp;
	}
};
int fib(int num){
	//矩阵加速求斐波那契数列第n项
	node m,ans;
	m.a[1][1]=1;
	m.a[1][2]=1;
	m.a[2][1]=1;
    ans.a[1][1]=1;
    ans.a[2][2]=1;
	while(num){
		if(num&1){
			ans=ans*m;
		}
		m=m*m;
		num/=2;
	}
	return ans.a[1][1];
}
int count_bit(int x) {
    int bit = 0;
    if(x == 0) return 1;
    while(x) {
        bit++;
        x >>= 1;
    }
    return bit;
}
int qpow(int a,int b){
	if(b==0)return 1;
	int tmp=qpow(a,b/2);
	return b%2?tmp*tmp%m*a%m:tmp*tmp%m;
}

main(){
	int ans=1,fb,hp;
	cin>>n>>k>>l>>m;
	
	if(l<=62&&k>=(1LL<<l))
    {
    //判断结果是否为0，记得用1LL
        puts("0");
        return 0;
    }
    int bit[1000],cnt=0;
    while(k){
    	bit[++cnt]=k%2;
    	k>>=1;
       //分解二进制位
	}
	fb=fib(n+1);
	hp=(qpow(2,n)+m-fib(n+1))%m;
	for(int i=1;i<=l;i++){
		if(bit[i]==1){
			ans*=hp;
			ans%=m;
		}
		else{
			ans*=fb;
			ans%=m;
		}
	}
	printf("%llu",ans%m);//记得再%一次m,不然会WA
	return 0;
}
```


---

