# [ABC129F] Takahashi&#39;s Basics in Education and Learning

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc129/tasks/abc129_f

<!-- 正の整数の組 $ (L_i,\ A_i,\ B_i,\ M_i) $ が $ Q $ 個与えられます．各組について，次の質問に答えてください．-->長さ $ L $ の等差数列 $ s_0,\ s_1,\ s_2,\ ...\ ,\ s_{L-1} $ があります。

この等差数列の初項は $ A $、公差は $ B $ です。つまり、$ s_i\ =\ A\ +\ B\ \times\ i $ が成り立ちます。

この数列の各項を、先頭に $ 0 $ の無い十進法表記に直し、順につなげて読んでできる整数を考えます。たとえば、数列 $ 3,\ 7,\ 11,\ 15,\ 19 $ をつなげて読んでできる整数は $ 37111519 $ となります。この整数を $ M $ で割ったあまりはいくらでしょうか。

## 说明/提示

### 制約

- 入力はすべて整数である
- $ 1\ \leq\ L,\ A,\ B\ <\ 10^{18} $
- $ 2\ \leq\ M\ \leq\ 10^9 $
- 等差数列の要素は全て $ 10^{18} $ 未満

### Sample Explanation 1

考える等差数列は $ 3,\ 7,\ 11,\ 15,\ 19 $ なので，$ 37111519 $ を $ 10007 $ で割ったあまりである $ 5563 $ が答えです．

## 样例 #1

### 输入

```
5 3 4 10007```

### 输出

```
5563```

## 样例 #2

### 输入

```
4 8 1 1000000```

### 输出

```
891011```

## 样例 #3

### 输入

```
107 10000000000007 1000000000000007 998244353```

### 输出

```
39122908```

# 题解

## 作者：Rushroom (赞：8)


~~题目名字好长~~

### 前置芝士

> [矩阵快速幂](https://oi-wiki.org/math/matrix/#_9)

### 弱化

容易发现，如果要在 $a$ 的后面接上 $b$，则获得的数为 $a\cdot 10^{len_b}+b$（$len_b$ 表示 $b$ 的位数）。

如果 $len_b$ 固定，则问题就很简单了，所以我们考虑一个弱化版：

> 给定一个有 $n$ 项的等差数列 $s$，求 $\sum\limits_{i=1}^n s_i\cdot 10^k$

即：$len_b$ 固定的原问题。

考虑用 **矩阵** 求解。

我们令状态矩阵为：

$$\begin{bmatrix}sum\\s_i\\1\end{bmatrix}$$

其中 $sum$ 表示到目前为止的答案（不包括 $s_i$）。

那么初始矩阵就是：

$$\begin{bmatrix}0\\A\\1\end{bmatrix}$$

再考虑转移：

设转移后的矩阵为：

$$\begin{bmatrix}sum'\\s_{i+1}\\1\end{bmatrix}$$

显然，这三项可以这么表示：

$$\begin{cases}sum'=10^{k}\cdot sum+s_i\\s_{i+1}=s_i+B\\1=1\end{cases}$$

（因为每次转移都要把 $sum$ 加上 $s_i$）

写成矩阵形式就是这样：

$$\begin{bmatrix}10^k&1&0\\0&1&B\\0&0&1\end{bmatrix} \times \begin{bmatrix}sum\\s_i\\1\end{bmatrix}=\begin{bmatrix}sum'\\s_{i+1}\\1\end{bmatrix}$$

那么，计算答案就是这样：

$$\begin{bmatrix}10^k&1&0\\0&1&B\\0&0&1\end{bmatrix}^n  \times \begin{bmatrix}0\\A\\1\end{bmatrix}=\begin{bmatrix}ans\\s_{n}\\1\end{bmatrix}$$

直接输出最后矩阵第一行第一列即可。

### 原问题

回到原问题：如果 $len_b$ 不固定怎么办？

我们发现了这样一个条件：数列中的所有数均小于 $10^{18}$，也就是说，$len_b$ 最多只有 $18$ 种情况。

我们可以 **枚举 $len_b$**，算出在 $len_b=i$ 的情况下需要迭代多少次就行了。

容易发现，迭代的次数 $=\left\lceil\dfrac{10^i-a}{b}\right\rceil$。

用 **矩阵快速幂** 加速迭代，时间复杂度 $O(\log L)$。

记得每次更新 $a$ 的值。还有，开 long long。

[**Code**](https://atcoder.jp/contests/abc129/submissions/30916080)

---

## 作者：_lyx111 (赞：3)

# [ABC129F] Takahashi's Basics in Education and Learning

[link](https://atcoder.jp/contests/abc129/tasks/abc129_f)

## 分析

先考虑当等差数列中的所有项在十进制表示下长度都相同的情况，设每一项的长度都为 $len$，那么答案就是：

$$\sum_{i=1}^{L} (A+(i-1)\times B)\times 10^{(L-i)\times len}$$

考虑用矩阵快速幂来加速计算这个值。

维护这样一个矩阵：

$$\begin{bmatrix}sum\\s\\1\end{bmatrix}$$

其中，$sum$ 表示当前已经计算完的和，$s$ 表示当前正在计算的等差数列中的项的值。

那么我们要从当前矩阵计算出下一个矩阵

$$\begin{bmatrix}sum'\\s'\\1\end{bmatrix}$$

有 $sum'=sum+10^{len}\times s,s'=s+B$，也就是：

$$\begin{bmatrix}10^{len}&1&0\\0&1&B \\0&0&1\end{bmatrix}\times\begin{bmatrix}sum\\s\\1\end{bmatrix}=\begin{bmatrix}sum'\\s'\\1\end{bmatrix}$$

初始矩阵是：

$$\begin{bmatrix}0\\A\\1\end{bmatrix}$$

那么最终的结果就可以表示为：

$$\begin{bmatrix}10^{len} & 1&0 \\0&1&B \\0&0&1\end{bmatrix}^L\times\begin{bmatrix}0 \\A\\1\end{bmatrix}$$

这个矩阵的最上面的元素就是我们要的答案了。

那么现在弱化版解决了，我们来考虑原题。题中有约束说：“等差数列中的任意一项 $\le  10^{18}$”，那么只要把位数相同的数分开处理即可（只要分成 $18$ 类）。

## 代码

~~~cpp
#include <bits/stdc++.h>
using namespace std;
long long L,A,B,M;
struct mat
{
    int n,m;
	long long x[4][4];
} ans;
mat operator * (const mat &u,const mat &v)
{
	mat res;
	res.n=u.n; res.m=v.m;
	memset(res.x,0,sizeof(res.x));
	for(int i=0;i<res.n;i++)
		for(int j=0;j<res.m;j++)
       		for(int k=0;k<u.m;k++)
				res.x[i][j]=(res.x[i][j]+u.x[i][k]*v.x[k][j]%M)%M;
    return res;
}
mat ksm(mat u,long long v)
{
	mat res=u; v--;
	while(v)
	{
		if(v&1) res=res*u;
		u=u*u; v>>=1;
	}
	return res;
}
int main()
{
	scanf("%lld%lld%lld%lld",&L,&A,&B,&M);
	ans.n=3; ans.m=1;
    ans.x[0][0]=0; ans.x[1][0]=A%M; ans.x[2][0]=1;
	long long mx=1;
    for(int i=1;i<=18;i++)
	{
        mx*=10;
        if(A<mx)
		{
			long long tot=(mx-A-1)/B+1;
	        if(tot>L) tot=L;
	        L-=tot;
	        if(tot)
	        {
		        A+=tot*B;
				mat trans;
		        trans.n=trans.m=3;
		        trans.x[0][0]=mx%M; trans.x[0][1]=1; trans.x[0][2]=0;
		        trans.x[1][0]=0; trans.x[1][1]=1; trans.x[1][2]=B%M;
		        trans.x[2][0]=0; trans.x[2][1]=0; trans.x[2][2]=1;
				ans=ksm(trans,tot)*ans;
			}
		}
    }
    printf("%lld\n",ans.x[0][0]);
    return 0;
}
~~~

[AC记录](https://atcoder.jp/contests/abc129/submissions/37921686)

## 写在最后

蒟蒻很菜，如果写的有不清楚或不对的地方望读者私信我指出，我会及时修正。

---

## 作者：DegChuZm (赞：2)

### 鲜花
纪念一下第一次自己推出矩阵。

~~而且这道题为啥把我 ```long long``` 爆了啊~~

### sol
设当前这个数的长度为 $k$，$a_i$ 为第 $i$ 个数，$s_i$ 为现在组合出来的数。

然后不难整出以下的等式：

$
\begin{cases}
   s_i = a_i \times 10^k \ +\ s_{i-1}\\
   a_i= a_{i-1}\ +\ B\\
\end{cases}
$

这一坨肯定要超时，于是考虑用矩阵优化。

$
\begin{bmatrix} \ a_i，s_i，1\ \end{bmatrix}=\begin{bmatrix} \ a_{i-1}，s_{i-1}，1\ \end{bmatrix}\times\begin{bmatrix} \ 1\ ,1\ ,\ 0\ \\\ 0,10^k,0\ \\ B\ ,0\ ,1\ \end{bmatrix}
$

但是这个 $k$ 是不固定的，所以我们考虑分段处理 $k=1,k=2...$ 的情况。

PS： 注意矩乘的时候小心你的 ```long long```，别算爆了。

### code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int mod;
int t,x,y,m,edd,k;
int n,maxx;
struct dcz{
	int mt[4][4];
};
dcz muilt(dcz xx,dcz y){
	dcz z;
	memset(z.mt,0,sizeof z.mt);
	for(int i=1;i<=3;i++){
		for(int k=1;k<=3;k++){
			for(int j=1;j<=3;j++){
				z.mt[i][j]=(z.mt[i][j]+(xx.mt[i][k]%mod*y.mt[k][j]%mod)%mod)%mod;
			}
		}
	}
	return z;
}
dcz ksm(dcz &a,int b){
	dcz ans;
	memset(ans.mt,0,sizeof ans.mt);
	for(int i=1;i<=3;i++) ans.mt[i][i]=1;
	while(b){
		if(b&1) ans=muilt(ans,a);
		b>>=1;
		a=muilt(a,a);
	}
	a = ans;
	return ans;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m>>k>>mod;
	dcz sb,ans;
	memset(ans.mt,0,sizeof(ans.mt));
	ans.mt[1][1]=m,ans.mt[1][3]=1;
	int x=1;
	for(int i=1;i<=18;i++){
		x*=10;
		if(x>m){
			int cnt=(x-m-1)/k+1;
			if(cnt>n) cnt=n;
			n-=cnt;
			if(cnt){
				m+=cnt*k;
				sb.mt[1][1]=1,sb.mt[1][2]=1,sb.mt[1][3]=0;
				sb.mt[2][1]=0,sb.mt[2][2]=x%mod,sb.mt[2][3]=0;
				sb.mt[3][1]=k%mod,sb.mt[3][2]=0,sb.mt[3][3]=1;
				ksm(sb,cnt);
				ans=muilt(ans,sb);
			}
		}
	}
	cout<<ans.mt[1][2];
	return 0;
}
```

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF633H)

# 前置知识

[矩阵加速递推](https://oi-wiki.org//math/linear-algebra/matrix/#%E7%9F%A9%E9%98%B5%E5%8A%A0%E9%80%9F%E9%80%92%E6%8E%A8)

# 解法

设 $f_{i}$ 表示将 $s_{1} \sim s_{i}$ 拼起来后的值，状态转移方程形如 $f_{i}=10^{k}f_{i-1}+s_{i}$ ，其中 $k=\left\lfloor \log_{10}s_{i} \right\rfloor+1$ 。

又因为保证等差数列中的元素 $\le 10^{18}$ ，对于每个 $k \in [1,19]$ 分别进行矩阵加速递推即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
ll p;
struct Matrix
{
	ll ma[4][4];
	Matrix()
	{
		memset(ma,0,sizeof(ma));
	}
	Matrix operator * (const Matrix another)
	{
		Matrix ans;
		for(ll i=1;i<=3;i++)
		{
			for(ll j=1;j<=3;j++)
			{
				for(ll h=1;h<=3;h++)
				{
					ans.ma[i][j]=(ans.ma[i][j]+(ma[i][h]%p)*(another.ma[h][j]%p)%p)%p;
				}
			}
		}
		return ans;
	}
}f,Base;
Matrix qpow(Matrix a,ll b)
{
	Matrix ans;
	for(ll i=1;i<=3;i++)
	{
		ans.ma[i][i]=1;
	}
	while(b)
	{
		if(b&1)
		{
			ans=ans*a;
		}
		b>>=1;
		a=a*a;
	}
	return ans;
}
int main()
{
// #define Isaac
#ifdef Isaac
	freopen("in.in","r",stdin);
	freopen("out.out","w",stdout);
#endif
	ll a,b,n,cnt;
	cin>>n>>a>>b>>p;
	f.ma[1][1]=0;
	f.ma[1][2]=a;
	f.ma[1][3]=1;
	for(ull i=10;i<=1000000000000000000;i*=10)
	{
		if(a<=i)
		{
			cnt=min(n,(ll)ceil(1.0*(i-a)/b));//计算迭代次数
			n-=cnt;
			a+=cnt*b;
			if(cnt>=1)
			{
				Base.ma[1][1]=i%p;
				Base.ma[1][2]=0;
				Base.ma[1][3]=0;
				Base.ma[2][1]=1;
				Base.ma[2][2]=1;
				Base.ma[2][3]=0;
				Base.ma[3][1]=0;
				Base.ma[3][2]=b%p;
				Base.ma[3][3]=1;
				f=f*qpow(Base,cnt);
			}
		}
	}
	printf("%lld\n",f.ma[1][1]);
	return 0;
}
```

---

