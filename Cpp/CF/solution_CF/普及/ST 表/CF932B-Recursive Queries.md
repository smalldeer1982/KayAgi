# Recursive Queries

## 题目描述

Let us define two functions $ f $ and $ g $ on positive integer numbers.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF932B/5ea922a7608f7b43dbb7e14356bf3e8277d2c765.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF932B/c3f9cee55fe0b74363392f2f9845da5254de38c3.png)

You need to process $ Q $ queries. In each query, you will be given three integers $ l $ , $ r $ and $ k $ . You need to print the number of integers $ x $ between $ l $ and $ r $ inclusive, such that $ g(x)=k $ .

## 说明/提示

In the first example:

- $ g(33)=9 $ as $ g(33)=g(3×3)=g(9)=9 $
- $ g(47)=g(48)=g(60)=g(61)=6 $
- There are no such integers between $ 47 $ and $ 55 $ .
- $ g(4)=g(14)=g(22)=g(27)=g(39)=g(40)=g(41)=g(58)=4 $

## 样例 #1

### 输入

```
4
22 73 9
45 64 6
47 55 7
2 62 4
```

### 输出

```
1
4
0
8
```

## 样例 #2

### 输入

```
4
82 94 6
56 67 4
28 59 9
39 74 4
```

### 输出

```
3
1
1
5
```

# 题解

## 作者：A_grasser (赞：4)

## 更新

修改了题意简化的内容错误。

## 题意简化

求函数 $g(l)$ 到 $g(r)$ 这段区间数值为 $k$ 的值数量。

## 需要注意的地方

1. 需要用比暴力更好的方法做这道题。

## 解法分析

### 一级解法

暴力，难想，过不了，就不细说了。

### 二级解法

函数 $g(x)$ 和 $f(x)$ 没有什么可优化的地方，那就优化输出模块，我们就引入新的算法：预处理与前缀和。

#### 前置知识：预处理与前缀和（可直接跳过）

##### 预处理

跟打表有点像，无非是一个由程序得出结果，一个是自己算出来写进程序里。

---

##### 前缀和

顾名思义，就是算前缀的总和。

举个例子，输入一串数，要你输出区间范围的值。用普通枚举就是 $O(r-l+1)$ 的级别。但你想一想，如果能记录 $1$ 至 $l$ 和 $1$ 至 $r$ 的总和，那么每次询问就是 $sum[r]-sum[l-1]$ 这个结果，这样就可以实现 $O(1)$ 查询，高效无比。

因为它要计算开始到特定值的总和，所以要搭配预处理使用。

#### 知识讲解完毕

回到问题，我们先进行预处理操作：

```cpp
sum[0][0]=1;
for(int i=1;i<=1000001;i++){//预处理要做到最大值 
	for(int j=0;j<=9;j++){//g()只能在10以内（不包括10） 
		if(j==g(i)) sum[i][j]=sum[i-1][j]+1;//如果相等，加上去 
		else sum[i][j]=sum[i-1][j];//把以前的结果复制过来 
	}
}
```
做完预处理，就可以轻松地写输出部分了：

```cpp
for(int i=1;i<=q;i++){
   	int l,r,k;//题意
   	scanf("%d %d %d",&l,&r,&k);
   	printf("%d\n",sum[r][k]-sum[l-1][k]);//输出l~r的结果
}
```
没想到吧，一道黄题主体部分如此简单，只要补上函数与输入就过了。

最后说一句，我比较推荐万能头文件，这样可以省去很多不必要的麻烦。

## 完整代码

```cpp
//已通过 
#include<bits/stdc++.h>
//万能头文件 
using namespace std;
int q;
int sum[1000009][15];
int g(int x){//题意 
	if(x<10) return x;
	//f函数 
	int res=1;
	while(x!=0){
    	if((x%10)!=0) res*=(x%10);//是乘积，并且不为零（我挂在这里过） 
    	x/=10;
	}
	return g(res);
}
int main(){
	cin>>q;
	sum[0][0]=1;
	for(int i=1;i<=1000001;i++){//预处理要做到最大值 
		for(int j=0;j<=9;j++){//g()只能在10以内（不包括10） 
			if(j==g(i)) sum[i][j]=sum[i-1][j]+1;//如果相等，加上去 
			else sum[i][j]=sum[i-1][j];//把以前的结果复制过来 
		}
	}
	for(int i=1;i<=q;i++){
    	int l,r,k;//题意 
    	scanf("%d %d %d",&l,&r,&k);
    	printf("%d\n",sum[r][k]-sum[l-1][k]);//输出l~r的结果
	}
	return 0;
}
```

---

## 作者：CrTsIr400 (赞：1)

## 1.主思路

预处理一下，用**朴素递归**把 $1$ 到 $10^6$ 的数据的 $g(i)$ 求出来。然后设 $s$ 为**前缀和数组**，$s_{i_j}$ 表示**前 $i$ 个数 存在 $g(x) $ 为 $j$ 的个数之和。其中 $1 \leq x \leq i$。**

如何转移呢？

```cpp
for(i=1 ... 1e6)
 x=g(i)
 for(j=0 ... 9)
  if(j==x)s[i][j]=s[i-1][j]+1
  else s[i][j]=s[i-1][j]+1
```


## 2.记忆化搜索

举个例子:

$g(1919810)=g(648)=g(192)=g(18)=g(8)$

我们就可以**很容易**地造出这样一个数和 $g(1919810)$ **相同**。

$g(9981110)=g(648)=g(192)=g(18)=g(8)$

发现没有？$g(1919810)$ 和 $g(9981110)$ 除了第一个参数**不同**，其他的数**都被重复计算了**！

所以可以**新建一个数组** $G$ ，**里面的 $G_i$ 代表每个 $g(i)$ 的值。**就是这样的**并查集思想**，可以使得原本常数不大的$g$函数变成$O(1)$！
经测试，对于$10^6$以内的数，未加优化的代码递归深度高达$8$层，而加了**记忆化**的代码递归深度**只有$2$层**！

### 上代码！

```cpp
#pragma GCC optimize(3,"Ofast","inline")
#include<bits/stdc++.h>
#define inf ((1<<30)-1)
#define linf ((1<<62)ll-1)
#define LL long long
#define F(i,a,b,c) for(register int i=(a);(b);i=(c))
#define Fu(i,a,b) for(register int i=(a);i<=(b);++i)
#define Fd(i,a,b) for(register int i=(a);i>=(b);--i)
#define Fn(i,a) for(register int i=las[(a)];i;i=nex[i])
int Fl,Pn,SI=100;char mch='\n',ch,Bf[21];
template<typename t>void in(t&a){a=0;ch=getchar();Fl=1;while((ch<'0')||(ch>'9'))Fl=(ch=='-')?-Fl:Fl,ch=getchar();while((ch>='0')&&(ch<='9'))a=a*10+ch-'0',ch=getchar();a*=Fl;}
template<typename t>void out(t a){if(a<0)putchar('-'),a=-a;if(a==0)putchar('0');while(a)Bf[++Pn]=a%10+'0',a/=10;while(Pn)putchar(Bf[Pn]),--Pn;putchar(mch);}
template<typename t,typename ...ARGS>void in(t&a,ARGS&...args){in(a);in(args...);}
template<typename t,typename ...ARGS>void out(t a,ARGS... args){out(a);out(args...);}
using namespace std;
inline int f(int x)
{
	int ans=1;while(x){if(x%10)ans*=x%10;x/=10;}
	return ans;
}
int G[1000001];
inline int g(int x)
{
	if(G[x])return G[x];
	if(x>=10)return G[x]=g(f(x));
	return G[x]=x; 
}
int s[1000001][10],n,l,r,k,x;
int main()
{
	in(n);
	Fu(i,1,1000000)
	{
		x=g(i);
		Fu(j,0,9)s[i][j]=s[i-1][j];
		++s[i][x];
	}
	Fu(i,1,n)in(l,r,k),out(s[r][k]-s[l-1][k]);
	return 0;
}
```



---

## 作者：Tiago (赞：0)

## Solution

注意到如果 $Q$ 次询问每次都去算一遍会超时。

发现 $l$ 和 $r$ 很小，考虑预处理，同时注意到 $k$ 最大不会超过 $9$，所以定义 $c_{i,j}$ 为 $1$ 到 $i$ 中 $g_i$ 为 $k$ 的个数，预处理所有的 $c$ 即可。

明显不会超时。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define For(i,a,b) for(int i=(a);i<=(b);i++)
#define FOR(i,a,b) for(int i=(a);i>=(b);i--)
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)

const int N=1e6;
int l,r,k,f[N+4],g[N+4],c[N+4][11];
int pow(int x,int y)
{
	int s=x;
	For(i,2,y)s*=x;
	return s;
}
void solve()
{
	cin>>l>>r>>k;
	cout<<c[r][k]-c[l-1][k]<<"\n";
}
void init()
{
	f[0]=g[0]=1;
	For(i,1,9)f[i]=g[i]=i;
	For(w,2,6)
		For(i,pow(10,w-1),pow(10,w)-1)
		{
			f[i]=f[i%pow(10,w-1)]*(i/pow(10,w-1));
			g[i]=g[f[i]];
		}
	f[N]=f[N%pow(10,5)]*(N/pow(10,5));
	g[N]=g[f[N]];
	For(k,1,9)
		For(i,1,N)
			if(g[i]==k)c[i][k]=c[i-1][k]+1;
				else c[i][k]=c[i-1][k];
}
int main()
{
	IOS;
	init();
	// For(i,1,20)cout<<f[i]<<" ";cout<<"\n";For(i,1,20)cout<<g[i]<<" ";cout<<"\n";
	int Q;cin>>Q;
	while(Q--)solve();

	return 0;
}
```


---

## 作者：fengxiaoyi (赞：0)

### 思路

这题只要先预处理出 $1\thicksim i$ 中 $g(i)=k$ 的个数，由于 $k$ 和 $r_{max}$ 都很小，所以空间不会炸。

#### 那怎么预处理呢？

其实只要对每个 $i$ 暴力求一遍 $g(i)$，再统计入答案即可。

代码如下：
```cpp
for(int i=1;i<=1000000;i++){
	int k=i;
    //求g(i)
	while(k>=10){
		int l=1;
		while(k){
			if(k%10!=0) l*=k%10;
			k/=10;
		}
		k=l;
	}
	for(int j=1;j<=9;j++){
		if(j==k) sum[i][j]=sum[i-1][j]+1;
		else sum[i][j]=sum[i-1][j];
	}
}
```

其中 $sum_{i,j}$ 表示 $1\thicksim i$ 中 $g(i)=k$ 的个数。

#### 统计答案

统计答案就很简单了，对于每组询问，输出 $sum\lbrack r\rbrack\lbrack k\rbrack-sum\lbrack l-1\rbrack\lbrack k\rbrack$（前缀和思想）

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int q,sum[1000010][10]; 
int main(){
	for(int i=1;i<=1000000;i++){
		int k=i;
		while(k>=10){
			int l=1;
			while(k){
				if(k%10!=0) l*=k%10;
				k/=10;
			}
			k=l;
		}
		for(int j=1;j<=9;j++){
			if(j==k) sum[i][j]=sum[i-1][j]+1;
			else sum[i][j]=sum[i-1][j];
		}
	}
	scanf("%d",&q);
	for(int i=1;i<=q;i++){
		int l,r,k;
		scanf("%d%d%d",&l,&r,&k);
		printf("%d\n",sum[r][k]-sum[l-1][k]);
	}
	return 0;
}
```

---

## 作者：RNTBW (赞：0)

### 序
这年头能让我一次 AC 的黄题已经不多了...
## 题意
设 $f(x)$ 表示 $x$ 中非零的位数积。

定义一个函数 $g(x)$：

- 当 $x \leqslant 9$ 时 $g(x)=x$；

- 当 $x > 9$ 时 $g(x)=g(f(x))$。

给定三个数 $l,r,k$，求对于 $i \in [l,r]$，$g(i)=k$ 的 $i$ 的个数。

- $1 \leqslant l \leqslant r \leqslant 10^6$，$1 \leqslant k \leqslant 9$。
## 思路
容易想到，可以用递归解决 $g$ 函数。

但是，有两个问题：

1. 怎么处理 $10^6$ 的数据？

2. 怎么在 $[l,r]$ 的区间内求个数？ 

对于第一个问题，我们可以用记忆化解决。

对于第二个问题呢？

我们想，线性求区间内数据是什么数据结构？

**前缀和！**

所以我们可以开一个二维数组 $w[i][j]$ 表示对于 $k \in [1,i]$，$g(k)=j$ 的 $i$ 的个数。 

那怎么转移呢？

很明显，对于每一个 $j$，我们从 1 到 $10^6$ 执行 ``for`` 循环，当遇到 $g(i)=j$ 的情况时就将 $w[i][j]$ 加一，代表在 $[1,i]$ 范围内又多了一个 $g(i)=j$ 的 $i$。

最后按照前缀和的方法减一下就好了。
## 正确代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define mx 1000001
int g[mx],w[mx][10];
int t,n,i,j,k,s;
int f(int x)
{
	int s=1;
	while(x) s*=(x%10==0 ? 1:x%10),x/=10;
	return s;//求位数积
}
int dfs(int x)
{
	if(g[x])return g[x];//记忆化
	if(x<10)return g[x]=x;
	return g[x]=g[f(x)];
}
int main()
{
	for(i=1;i<mx;i++) dfs(i);
	for(j=1;j<=9;j++)//容易想到，g(i)一定<10
	{
		for(i=1;i<mx;i++) w[i][j]=w[i-1][j]+(g[i]==j ? 1:0);
        //前缀和
	}
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d%d",&k,&s,&n);
		printf("%d\n",w[s][n]-w[k-1][n]);//输出
	}
	return 0;
}
```


---

## 作者：dormantbs (赞：0)

首先,我们可以先写个暴力,打出1到1e6的g(n)的值,会发现每个g(n)都在\[0,9\]  
中取值,也就是说计算g(n)的时间复杂度几乎可以认为是常数级别的。  

然后有多组询问，如果对于每组询问都去计算一遍，那将会是极其浪费的，最坏  
情况会使复杂度达到O(qn) (这里认为g(n)的计算为常数时间),所以我们也很容易  
可以想到预处理出g(n)值出现次数的前缀和，因为g(n) 的值只有10种情况,所以  
空间复杂度是可以保证的。  
  
然后每次询问就可以O(1)回答了。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
int f(int x){
	int ans=1;
	while(x){
		int a=x%10;
		if(a) ans*=a;
		x/=10;	
	} 
	return ans;
}
int g(int x){
	if(x<10) return x;
	return g(f(x));
}
const int N=1e6;
int c[10][N+5];
int main(){
	int q,l,r,k;
	scanf("%d\n",&q);
	c[0][0]=1;
	for(int i=1;i<=N;++i){
		int x=g(i);
		for(int j=0;j<10;++j)
			if(j==x) c[j][i]=c[j][i-1]+1;
			else c[j][i]=c[j][i-1];
	}
	while(q--){
		scanf("%d%d%d",&l,&r,&k);
		if(l==0) printf("%d\n",c[k][r]);
		else printf("%d\n",c[k][r]-c[k][l-1]);
	}
}
```

---

