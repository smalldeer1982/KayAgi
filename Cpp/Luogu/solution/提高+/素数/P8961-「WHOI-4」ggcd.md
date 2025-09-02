# 「WHOI-4」ggcd

## 题目背景

如何输入输出 `__int128`：

```cpp
__int128 read() {
  char c = getchar();
  __int128 x = 0;
  bool f = 0;
  for (; !isdigit(c); c = getchar()) f ^= !(c ^ 45);
  for (; isdigit(c); c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
  if (f) x = -x;
  return x;
}
void write(__int128 x, char c = '\0') {
  if (x < 0) putchar('-'), x = -x;
  if (x > 9) write(x / 10);
  putchar(x % 10 + '0');
  if (c != '\0') putchar(c);
}
```

## 题目描述

**本题已新增一组样例，请注意查看。**

小 Y 给了你长度为 $n$ 的数组 $y$ 以及一个正整数 $m$，保证 $0\le y_i<m$，请你构造一个同样长为 $n$ 的数组 $x$，使得：

1. $x_i$ 在 `__int128` 范围内；
2. $x_i\bmod m=y_i$；
3. $\gcd(|x_1|,\cdots,|x_n|)\bmod m$ 最大。

注意，$x_i$ **可以为负**，此时 $m\mid (x_i-y_i)$ 且 $0\le y_i<m$。 

## 说明/提示

**数据范围**

**本题采用捆绑测试。**

Subtask 1（$30$ pts）：$m$ 是素数。

Subtask 2（$70$ pts）：无特殊限制。

对于所有数据，保证 $2\le m \le10^9$，$1\le n\le10^6$。

**关于 Special Judge**

对于每个测试点：

如果你输出的格式不正确，你将会获得 $0$ 分。

如果你输出的数中有不在 `__int128` 范围的数，可能导致溢出所以你可能无法获得预期的分数。

如果你的数列 $x$ 不符合题目给定的 $y$，你将会获得 $0$ 分。

如果你的数列 $x$ 不符合你输出的 $g$，你将会获得 $0$ 分。

如果你的 $g$ 不为最大，你将会获得 $0$ 分。

否则你将获得该测试点的所有分数。

## 样例 #1

### 输入

```
1 10
4```

### 输出

```
6
-6```

## 样例 #2

### 输入

```
1 10
7```

### 输出

```
7
7```

## 样例 #3

### 输入

```
2 9
3 3```

### 输出

```
6
12 -6```

## 样例 #4

### 输入

```
10 7
1 2 3 4 5 6 0 1 2 3```

### 输出

```
6
36 30 24 18 12 6 42 -6 30 24```

# 题解

## 作者：oyoham (赞：2)

### Problem
给定长为 $n$ 的数组 $Y$ 和正整数 $m$，要构造长为 $n$ 的数组 $X$ 使得满足：  
1. $\forall 1\le i\le n,-2^{127}\le X_i\le 2^{127}-1$。  
2. $\forall 1\le i\le n,X_i \bmod m = Y_i$。  
求 $\gcd\limits_{i=1}^{n}|X_i|\bmod m$ 的最大值，并输出任意对应的数组 $X$。 
### Solution
设 $\forall 1\le i\le n,X_i = Y_i + k_i\cdot m$。

先考虑 $n=1$。  
此时答案只可能为 $Y_1$（取 $k_1\ge0$）或 $m-Y_1$（取 $k_1<0$）。比较并输出即可（可见样例 $1,2$）。

考虑 $k>1$。  
设 $g=\gcd(\gcd\limits_{i=1}^{n}Y_i,m)$，可以发现答案为 $ans=m-g$。  
证明：  
$Y_i$ 只能对 $\gcd$ 产生 $Y_i$（取 $k_i\ge0$）或 $m-Y_i$（取 $k_i<0$）的贡献。  
与 $m$ 取 $\gcd$ 是利用 $\gcd(a,b)=\gcd(a-b,b)$ 将 $\gcd(m-Y_i,Y_i)=\gcd(m,Y_i)$。

考虑构造方法：  
先特判掉 $\forall 1\le i\le n,Y_i=0$ 的构造（全输出任意 $m$ 的倍数即可）。  
随便找到一个 $p$ 使 $\exist 1\le i\le n \& i\ne p,Y_i\ne0$。对于 $i\ne p$ 时构造 $k_i=-\frac{Y_i}{g}$ 使得 $X_i=-ans\cdot\frac{Y_i}{g}$，满足 $ans|X_i$。  
此时设 $G=\gcd\limits_{1\le i\le n,i\ne p}\frac{X_i}{ans}$，考虑使 $k_p=\frac{k'\cdot ans-Y_p}{g}$ 此时有 $X_p=k_p\cdot m+Y_p=\frac{k'\cdot ans \cdot m-Y_p\cdot m + Y_p \cdot g}{g}=\frac{k'\cdot ans \cdot m+Y_p \cdot (g-m)}{g}=\frac{k'\cdot ans \cdot m-Y_p \cdot ans}{g}=ans\cdot\frac{k'\cdot m-Y_p}{g}$ 满足 $ans|X_p$，于是从 $1$ 递增枚举 $k'$（或在范围内随机 $k'$），找到一个 $\gcd(G,\frac{k'\cdot m-Y_p}{g})=1$，即可输出答案了。
### Code
```
#include<bits/stdc++.h>
using namespace std;
#define ll __int128
#define int ll
#define aF(begin,end,step,name) for(int name=begin;name<=end;name+=step)
#define oF(B,E,N) aF(B,E,1,N)
#define af(B,E,S) aF(B,E,S,i)
#define of(B,E) af(B,E,1)
#define tF(E,N) oF(1,E,N)
#define tf(E) of(1,E)
#define nF(N) tf(n,N)
#define nf() tf(n)
inline ll read(){
	ll x=0;
	short f=1;
	char c=getchar();
	while(c>57||c<48){
		if(c==45) f=-1;
		c=getchar();
	}
	while(c<58&&c>47){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
inline void write(ll x){
	if(x<0ll) putchar(45),x=~x+1;
	if(x>9ll) write(x/10);
	putchar(x%10|48);
}
int n=read(),m=read();
int a[1000005];
int f=1;
int g=m,ans=0;
void Spe(){
	int ans=read();
	if(ans<<1<m) ans=m-ans,f=-1;
	write(ans);putchar(10);write(ans*f);
	exit(0);
}
int ABS(int x){
	return x>0?x:-x;
}
int ansl[1000005];
int k[1000005];
int tagp=0;
signed main(){
	if(n==1) Spe();//特判 
	nf() a[i]=read();
	nf(){
		if(a[i]) tagp=i;
		g=__gcd(g,a[i]);
	}
	write((ans=m-g)),putchar(10);
	if(!tagp){//是否全0 
		nf()write(0),putchar(32);
		exit(0);
	}
	int AN=tagp==1?2:1,G=0;//AN为题解中的p，tagp为一个非0点，去一个不为tagp的点即可 
	nf(){//i!=p部分 
		if(i==AN)continue;
		k[i]=-a[i]/g; 
		G=__gcd(G,k[i]*m+a[i]);
	}
	int _k=1;//从1递增写法 
	k[AN]=(_k*ans-a[AN])/g;
	while(__gcd(G,k[AN]*m+a[AN])>ans) _k++,k[AN]=(_k*ans-a[AN])/g;
	/*随机写法 
	int _k=rand();
	k[AN]=(_k*ans-a[AN])/g;
	while(__gcd(G,k[AN]*m+a[AN])>ans) _k=rand(),k[AN]=(_k*ans-a[AN])/g;
	*/
	nf(){
		write(k[i]*m+a[i]);putchar(32); 
	}
	return 0;
}
```

---

