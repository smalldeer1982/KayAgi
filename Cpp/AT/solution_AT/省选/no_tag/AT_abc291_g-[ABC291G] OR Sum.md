# [ABC291G] OR Sum

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc291/tasks/abc291_g

長さ $ N $ の数列 $ A=(A_0,A_1,\ldots,A_{N-1}) $ と $ B=(B_0,B_1,\ldots,B_{N-1}) $ が与えられます。  
 また、高橋君は数列 $ A $ に対して、次の操作を好きな回数 ( $ 0 $ 回でもよい) 行う事ができます。

- $ A $ を $ 1 $ つ左にシフトする、すなわち、$ A $ を、$ A'_i=A_{(i+1)\%\ N} $ で定義される $ A' $ で置き換える。ただし、$ x\%\ N $ で、$ x $ を $ N $ で割った余りを表す。
 
高橋君の目的は $ \displaystyle\sum_{i=0}^{N-1}\ (A_i|B_i) $ を最大化することです。ただし、$ x|y $ で $ x $ と $ y $ のビット毎の論理和(bitwise OR)を表します。

$ \displaystyle\sum_{i=0}^{N-1}\ (A_i|B_i) $ の値としてあり得る最大の値を求めてください。

  ビット毎の論理和(bitwise OR)とは $ 1 $ ビットの数字 ($ 0 $ または $ 1 $) の組に対して下の表で定義される演算を**論理和**（またはOR演算）といいます。  
 ビット毎に論理和を適用する演算を**ビット毎の論理和（bitwise OR）**といいます。     $ x $  $ y $  $ x|y $     $ 0 $ $ 0 $ $ 0 $   $ 0 $ $ 1 $ $ 1 $   $ 1 $ $ 0 $ $ 1 $   $ 1 $ $ 1 $ $ 1 $   論理和ではビット $ x $, $ y $ の少なくとも一方が $ 1 $ の場合に結果が $ 1 $ となります。 逆に言うと、共に $ 0 $ の場合のみ結果が $ 0 $ となります。

##### 具体例

 ```
0110 | 0101 = 0111
```

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 5\times\ 10^5 $
- $ 0\leq\ A_i,B_i\ \leq\ 31 $
- 入力はすべて整数
 
### Sample Explanation 1

高橋君が一度も操作を行わなかった時、$ A $ は $ (0,1,3) $ のままであり、$ \displaystyle\sum_{i=0}^{N-1}\ (A_i|B_i)=(0|0)+(1|2)+(3|3)=0+3+3=6 $, 高橋君が $ 1 $ 回操作を行った時、$ A=(1,3,0) $ となり、$ \displaystyle\sum_{i=0}^{N-1}\ (A_i|B_i)=(1|0)+(3|2)+(0|3)=1+3+3=7 $, 高橋君が $ 2 $ 回操作を行った時、$ A=(3,0,1) $ となり、$ \displaystyle\sum_{i=0}^{N-1}\ (A_i|B_i)=(3|0)+(0|2)+(1|3)=3+2+3=8 $ となります。$ 3 $ 回以上操作を行った時、 $ A $ は上記のいずれかの形になるため、$ \displaystyle\sum_{i=0}^{N-1}\ (A_i|B_i) $ の最大値は $ 8 $ であり、$ 8 $ を出力します。

### Sample Explanation 2

最大となるのは高橋君が $ 3 $ 回操作を行った時であり、この時 $ A=(4,3,1,6,1) $ となり、 $ \displaystyle\sum_{i=0}^{N-1}\ (A_i|B_i)=(4|0)+(3|6)+(1|4)+(6|0)+(1|1)=4+7+5+6+1=23 $ となります。

## 样例 #1

### 输入

```
3
0 1 3
0 2 3```

### 输出

```
8```

## 样例 #2

### 输入

```
5
1 6 1 4 3
0 6 4 0 1```

### 输出

```
23```

# 题解

## 作者：CrTsIr400 (赞：5)

## [ABC291G OR Sum](https://atcoder.jp/contests/abc291/tasks/abc291_g)

题意：有两个长度为 $N$ 的序列 $A,B$，可以给 $A$ 序列向左循环移动若干位，求 $\sum (A_i|B_i)$ 的最大值。$N\le 5\times 10^5$ 而 $0\le A_i,B_i\le 31$。

题解：发现 `or` 操作有点点困难，那么我们就把两个序列取反，然后求 `and` 的最小值。

尝试形式化枚举每个移动数量的过程，比如枚举一个移位 $j$，再枚举一个 $i$ 计算答案。

这种位数特别少的题，就先枚举二进制位 $k$，对于每一位分别处理。设 $a,b$ 分别为序列 $A,B$ 的第 $k$ 位取反。

然后就是两个 `0/1` 序列合并操作，我们需要求出一个答案数组 $c$，$c_j=\sum a_i\times b_{(i+j)\% n}$。

我们可以把 $b$ 复制一遍，去掉取模 $n$，问题就变成了求 $c_j=\sum a_i\times b_{i+j}$。

这个形式还不是我们熟悉的形式，我们应该熟悉的形式是 $c_{i+j}=\sum a_i\times b_j$。

怎么办呢？拿 $k$ 替换 $(i+j)$，问题就变成了 $c_{k-i}=\sum a_i\times b_k$。

左边式子 $i$ 符号负的不好看，问题就变成了 $c_{k+i}=\sum a_{-i}\times b_k$。

右边下标为负数的很不好看，因为我们需要存储 $a$ 数组，所以把 $a$ 数组反转得到 $a'$ 了，就是原来的存储 $a_{-i}$ 的数组右移 $n-1$ 位。

令 $p=n-1-i$，原式= $c_{k+p}=\sum a'_{p}\times b_k$。由上可知，多项式实际的值只有 $[n-1,2n-2]$ 的这 $n$ 位才有效。

发现就是多项式的形式，直接卷积即可。

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#include<atcoder/all>
using namespace std;
typedef int I;
I main(){I n;
	scanf("%d",&n);
	vector<I>a(n),b(n),c(n),d(n<<1),e,f(n);
	for(I i=0;i<n;++i)scanf("%d",&a[i]);
	for(I i=0;i<n;++i)scanf("%d",&b[i]);
	for(I k=0;k<5;++k){
		for(I i=0;i<n;++i)d[i]=(~b[i]>>k)&1,d[i+n]=d[i],c[n-1-i]=(~a[i]>>k)&1;
		e=atcoder::convolution(c,d);
		for(I i=0;i<n;++i)f[i]+=(n-e[i+n-1])<<k;}
	printf("%d\n",*max_element(f.begin(),f.end()));
	return 0;
}
```

## 

---

## 作者：porse114514 (赞：2)

## [AT_abc291_g [ABC291G] OR Sum](https://www.luogu.com.cn/problem/AT_abc291_g) 题解

一看到**字符串匹配**问题，就不由得想到了 **FFT**。

题目要求的其实是这个东西：
$$\large\max^{n-1}_{k=0}\sum^{n+k-1}_{i=k}A_i|B_{i-k}$$
由于多位的按位或不能变为加减乘除的形式，所以考虑**拆位**；又因为 $A_i$，$B_i$ 均小于等于 $31$，所以最多有 $5$ 位，再加上 8s 的时间与 1GB 的内存，所以这样能过。

拆位，得：
$$\large\max^{n-1}_{k=0}\sum^{n+k-1}_{i=k}\sum^4_{j=0}A_{i,\,j}|B_{i-k,\,j}$$

又因为 $x|y=x+y-xy=x(1-y)+y$，所以原式可化简为：
$$\large\max^{n-1}_{k=0}\sum^{n+k-1}_{i=k}\sum^4_{j=0}A_{i,\,j}(1-B_{i-k,j})+B_{i-k,\,j}$$
令 $B^{'}_{i,\,j}=1-B_{i,\,j}$，则原式可化简为：
$$\large\max^{n-1}_{k=0}\sum^{n+k-1}_{i=k}\sum^4_{j=0}A_{i,\,j}B^{'}_{i-k,\,j}+B_{i-k,\,j}$$
我们发现：
$$\sum^{n+k-1}_{i=k}\sum^4_{j=0}B_{i-k,\,j}$$
是定值，值为 $B$ 中所有元素二进制中 $1$ 的位数之和，令其为 $sum$，则原式可化简为：
$$\large sum+\large\max^{n-1}_{k=0}\sum^{n+k-1}_{i=k}\sum^4_{j=0}A_{i,\,j}B^{'}_{i-k,\,j}$$
又因为多项式乘法中，$h_i$ 的系数为 ：$\sum^{i}_{j=1}f_j\text{ × }g_{i-j}$，所以我们要让原式中的两个下标的和为定值，不难想到将 $B^{'}$ 翻转一下。

令 $B^{''}=B^{'}_{n-i-1,\,j}$，则 $B^{'}=B^{''}_{n-i-1,\,j}$，所以原式可化简为：
$$\large sum+\large\max^{n-1}_{k=0}\sum^{n+k-1}_{i=k}\sum^4_{j=0}A_{i,\,j}B^{''}_{n-i+k-1,\,j}$$
此时，$\text{max}$ 里的值就为 $A\times B$ 的第 $n+k-1$ 位，就可以用 FFT 切了。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = (1 << 22) + 10;//要开到这，不然可能会RE 
const double pi = acos(-1);//反三角函数 
struct z{
	double a,b;
	z operator + (z other)
	{
		return {this -> a + other.a,this -> b + other.b};
	}
	z operator - (z other)
	{
		return {this -> a - other.a,this -> b - other.b};
	}
	z operator * (z other)
	{
		return {this -> a * other.a - this -> b * other.b,this -> a * other.b + this -> b * other.a};
	}//重载运算符 
}A[maxn][5],B[maxn][5],B_[maxn][5],B__[maxn][5],H[maxn][5];//一个下划线代表一个'，例如B_就是前面推导过程中的B' 
int n,a[maxn],b[maxn],sum,ans,maxx = 0,len = 1;
void FFT(z f[maxn][5],int l,int op,int j)
{
	if(l == 1) return ;//判边界 
	z A0[l >> 1][5],A1[l >> 1][5];
	for(int i = 0;i < l;i++)//奇偶拆分 
	{
		if(i & 1) A1[i >> 1][j] = f[i][j];
		else A0[i >> 1][j] = f[i][j];
	}
	FFT(A0,l >> 1,op,j);
	FFT(A1,l >> 1,op,j);//递归 
	z w = {1,0},wk = {cos(2.0 * pi / l),op * sin(2.0 * pi / l)};//不要忘记乘op 
	for(int i = 0;i < (l >> 1);i++,w = w * wk)
	{
		f[i][j] = A0[i][j] + w * A1[i][j];
		f[i + (l >> 1)][j] = A0[i][j] - w * A1[i][j];//O1赋值另一半 
	}
	return ;
}
int main()
{
	cin >> n;
	for(int i = 0;i < n;i++)
	{
		cin >> a[i];
	}
	for(int i = n;i < 2 * n;i++)
	{
		a[i] = a[i - n];
	}
	for(int i = 0;i < 2 * n;i++)
	{
		A[i][0].a = a[i] % 2;
		a[i] >>= 1;
		A[i][1].a = a[i] % 2;
		a[i] >>= 1;
		A[i][2].a = a[i] % 2;
		a[i] >>= 1;
		A[i][3].a = a[i] % 2;
		a[i] >>= 1;
		A[i][4].a = a[i] % 2;
	}
	for(int i = 0;i < n;i++)
	{
		cin >> b[i];
		B[i][0].a = b[i] % 2;
		sum += B[i][0].a;
		b[i] >>= 1;
		B[i][1].a = b[i] % 2;
		sum += ((int)(B[i][1].a + 0.5) << 1);
		b[i] >>= 1;
		B[i][2].a = b[i] % 2;
		sum += ((int)(B[i][2].a + 0.5) << 2);
		b[i] >>= 1;
		B[i][3].a = b[i] % 2;
		sum += ((int)(B[i][3].a + 0.5) << 3);
		b[i] >>= 1;
		B[i][4].a = b[i] % 2;
		sum += ((int)(B[i][4].a + 0.5) << 4);
	}
	for(int i = 0;i < n;i++)
	{
		for(int j = 0;j < 5;j++)
		{
			B_[i][j].a = 1 - B[i][j].a;
		}
	}
	for(int i = 0;i < n;i++)
	{
		for(int j = 0;j < 5;j++)
		{
			B__[i][j].a = B_[n - i - 1][j].a;
		}
	}
	while(len <= 3 * n - 1) len <<= 1;
	//以上为初始化 
	for(int i = 0;i < 5;i++)
	{
		FFT(A,len,1,i);
		FFT(B__,len,1,i);//求单位根点值 
	}
	for(int i = 0;i < len;i++)
	{
		for(int j = 0;j < 5;j++)
		{
			H[i][j] = A[i][j] * B__[i][j]; 
		}
	}
	for(int i = 0;i < 5;i++) FFT(H,len,-1,i);//逆运算 
	for(int i = 0;i < len;i++)
	{
		for(int j = 0;j < 5;j++)
		{
			H[i][j].a = ((int)(H[i][j].a / len + 0.5)) * (1 << j);//千万不要忘了乘(1 << j)，拆位之后还要合并 
		}
	}
	for(int k = 0;k < n;k++)
	{
		ans = 0;
		for(int j = 0;j < 5;j++)
		{
			ans += (H[n + k - 1][j].a + 0.5);
		}
		maxx = max(maxx,ans);//求值 
	}
	cout << maxx + sum << '\n';//又切一道紫 
	return 0;
}
```

---

## 作者：__D_A_T__ (赞：1)

## 前言

这是一道练 FFT 的好题。

# 题意

在这里不赘述。

# 做法

由于有循环位移操作，将 A 序列复制一遍粘在原来的 A 序列后边，那答案便变成了 $\max\sum_{i=0}^{N-1}\left(A_{i+j}\mid B_i\right)\left(0\le j<N\right)$

考虑将 A 序列反转，一眼瞪出卷积形式，考虑 FFT。

由于任意两个数 $x,y$ 有 $x\mid y=x+y-xy$，考虑将 A 序列和 B 序列拆位，按位累加算贡献输出最大值。

# 代码

```cpp
//题解区里都是ATcoder自带的FFT,那我就手写一个吧 
#include<bits/stdc++.h>
using namespace std;
const double pi=acos(-1);
int n,m,len,inv,ans,s;
int a[4000005],b[4000005],c[4000005],rev[4000005];
complex<double>f[4000005],g[4000005],h[4000005];
void fft(complex<double>f[],int len,int opt)//板子 
{
	for(int i=0;i<len;i++)
		if(i<rev[i])swap(f[i],f[rev[i]]);
	for(int tl=2;tl<=len;tl*=2)
	{
		complex<double>gen(cos(2*pi/tl),sin(2*pi/tl)*opt);
		for(int i=0;i<len;i+=tl)
		{
			complex<double>k(1,0);
			for(int j=i;j<i+tl/2;j++,k*=gen)
			{
				complex<double>x=f[j],y=k*f[j+tl/2];
				f[j]=(x+y),f[j+tl/2]=(x-y);
			}
		}
	}
}
signed main()
{
	cin>>n,len=1;
	while(len<=2*n)len*=2;
	for(int i=0;i<n;i++)cin>>a[i],s+=a[i];
	for(int i=0;i<n;i++)cin>>b[i],s+=b[i];
	for (int i=1;i<len;i++)
        rev[i]=rev[i/2]/2+(i%2?len/2:0);
	for(int j=0;j<5;j++)//由于A[i]和B[i]<=31即2^5-1，所以这里只用枚举到5就好了 
	{
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
		for(int i=0;i<n;i++)
		{// ↓ 依次取出A[i]和B[i]的第j位
			f[n+i]=f[i]=(((a[i]>>j)&1));
			g[n-i-1]=(((b[i]>>j)&1));//逆序存放 
		}
		fft(f,len,1),fft(g,len,1);
		for(int i=0;i<len;i++)
			h[i]=f[i]*g[i];
		fft(h,len,-1);
		for(int i=0;i<n;i++)
			c[i]+=(int)(h[n+i-1].real()/len+0.5)<<j;
//				   ↑	计算贡献，累加即可 
	}
	for(int i=0;i<n;i++)
		ans=max(ans,s-c[i]);//取最大值 
	cout<<ans<<endl;//输出 
	return 0;
}
```

---

## 作者：Presentation_Emitter (赞：1)

题意：给出两个长 $N$ 的数列 $A,B$，现在可以对 $A$ 做任意次循环移位，求 $\displaystyle\sum_{i=0}^{N-1}\ (A_i|B_i)$ 的最大值。

首先将 $A$ 进行一个复制然后接在 $A$ 后面，然后答案即为 $\displaystyle\max_{k=0}^{N-1}\{\sum_{i=0}^{N-1}\ (A_{i+k}|B_i)\}$，之后将 $A$ 反序，于是就形成了一个卷积的形式。

但是我们发现这个卷积里有或运算，于是考虑拆位，对于每一位 $a_i,b_i$，有 $a_i|b_i=a_i+b_i-a_ib_i$，然后把贡献累加即可。

Code:

```cpp
int n,f[ntt_siz+5],g[ntt_siz+5],a[500005],b[500005],ans[500005];
int main()
{
	n=rd();int s=0;
	for(int i=1;i<=n;++i)s+=(a[i]=rd());
	for(int i=1;i<=n;++i)s+=(b[i]=rd());
	int l=1;while((1<<l)<n+n)++l;
	init(1<<l);
	for(int c=0;c<5;++c)
	{
		clr(f,1<<l);clr(g,1<<l);
		for(int i=0;i<n;++i)f[i]=f[i+n]=((a[n-i]>>c)&1),g[i]=((b[i+1]>>c)&1);
		mul(f,g,1<<l);//卷积
		for(int i=0;i<n;++i)ans[i]+=f[i+n-1]<<c;
	}
	int aa=-1;
	for(int i=0;i<n;++i)tomax(aa,s-ans[i]);
	prt(aa);
	ret 0;
}
```

---

## 作者：cancan123456 (赞：0)

no convolution/oh

考虑将 $b_i$ 倍长，然后然后将 $a_i$ 放在下面，一开始 $a_0$ 对准 $b_0$，最后 $a_0$ 对准 $b_{n-1}$，我们令 $a_0$ 对准 $b_d$ 的时刻为时刻 $d$。

考虑将 $a_i\mid b_i$ 的贡献放到 $b_i$ 上来计算，不失一般性地，考虑 $b_j(0\le j<n)$ 会对什么时刻造成什么贡献，考虑拆位，现在考虑第 $k$ 位的贡献，显然，会与 $b_j$ 进行或运算的只有 $a_j(d=0),a_{j-1}(d=1),\dots,a_0(d=j)$，其中有且仅有 $a,b$ 第 $k$ 位都是 $0$ 的情况不造成贡献，也就是说，我们考虑计算或为 $0$ 的情况，发现这是一个卷积形式，于是 FFT 优化即可，代码：

```cpp
#include <cstdio>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
const int N = 500000;
int max(int a, int b) {
	return a > b ? a : b;
}
int main() {
	int n;
	scanf("%d", &n);
	vector < int > a(n), b(n), c(n), d(2 * n), e(n), f;
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	for (int i = 0; i < n; i++) {
		scanf("%d", &b[i]);
	}
	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < n; i++) {
			d[i] = ((a[i] >> j) & 1) ^ 1;
			d[n + i] = d[i];
			e[n - i - 1] = ((b[i] >> j) & 1) ^ 1;
		}
		f = convolution(d, e);
		for (int i = 0; i < n; i++) {
			c[i] += (n - f[n + i - 1]) << j;
		}
	}
	int ans = 0;
	for (int i = 0; i < n; i++) {
		ans = max(ans, c[i]);
	}
	printf("%d", ans);
	return 0;
}
```

---

