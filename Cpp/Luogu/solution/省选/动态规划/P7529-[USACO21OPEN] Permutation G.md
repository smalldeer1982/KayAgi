# [USACO21OPEN] Permutation G

## 题目描述

Bessie 在二维平面上有 $N$ 个最爱的不同的点，其中任意三点均不共线。对于每一个 $1\le i\le N$，第 $i$ 个点可以用两个整数 $x_i$ 和 $y_i$ 表示。

Bessie 按如下方式在这些点之间画一些线段：

- 1. 她选择这 $N$ 个点的某个排列 $p_1,p_2,\dots,p_N$ 。
- 2. 她在点 $p_1$ 和 $p_2$ 、$p_2$ 和 $p_3$、$p_3$ 和 $p_1$ 之间画上线段。
- 3. 然后依次对于从 $4$ 到 $N$ 的每个整数 $i$，对于所有 $j<i$，她从 $p_i$ 到 $p_j$ 画上一条线段，只要这条线段不与任何已经画上的线段相交（端点位置相交除外）。

Bessie 注意到对于每一个 $i$ ，她都画上了恰好三条新的线段。计算 Bessie 在第 $1$ 步可以选择的满足上述性质的排列的数量，结果对 $10^9+7$ 取模。 

## 说明/提示

#### 样例一解释

没有排列满足该性质

#### 样例二解释

所有排列均满足该性质

#### 样例解释三

一个满足该性质的排列为 $(0,0),(0,4),(4,0),(1,2),(1,1)$ 。对于这个排列，

- 首先，她在 $(0,0),(0,4)$ 和 $(4,0)$ 两两之间画上线段。
- 然后她从 $(1,2)$ 向 $(0,0)$ ，$(0,4)$ 和 $(4,0)$ 画上线段。
- 最后，她从 $(1,1)$ 向 $(1,2)$ ，$(4,0)$ 和 $(0,0)$ 画上线段。 

![](http://usaco.org/current/data/fig_permutation_gold_open21.png)

### 数据范围与约定

$3\le N \le 40$，$0\le x_i,y_i \le 10^4$

## 样例 #1

### 输入

```
4
0 0
0 4
1 1
1 2```

### 输出

```
0```

## 样例 #2

### 输入

```
4
0 0
0 4
4 0
1 1```

### 输出

```
24```

## 样例 #3

### 输入

```
5
0 0
0 4
4 0
1 1
1 2```

### 输出

```
96```

# 题解

## 作者：IamZZ (赞：12)

**G组练习总结#10**

好喜欢妙妙题！

stO **Benq** Orz

### 题目大意

Bessie 喜欢画画，现在它给你了 $n(n\leq40)$ 个点，她将按照一定的顺序去连接这些点，$0\le x_i,y_i\le 10^4$。

Bessie 会先选择一个这 $n$ 个点的排列，记为 $p_1,p_2\dots p_n$，然后按照以下的方式去操作：

首先，她会将 $p_1,p_2,p_3$ 连成一个三角形。

然后对于 $i(4\leq i\leq n)$，我们找到所有可以从 $p_i$ 看到的 $p_j(j<i)$，即连接 $p_i,p_j$ 的线段不与任何先前存在的线段相交（端点除外），连接 $(p_i,p_j)$。

Bessie 会一直这样操作下去，她限制我们，对于所有 $i(4\leq i\leq n)$，新连接的线段数**必须刚好是 3**。

现在她请我们求出所有合法的排列 $p$ 的个数，答案数对 $10^9+7$ 取模。

题目保证没有任何三个点共线。

### 解题思路

第一个操作会给我们的图一个初始的大三角形，这没什么好说的。

我们可以试着分析加入 $p_4$ 时需要满足些什么条件？先看图：

目前状况是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/09pvnipm.png)

我们分别讨论 $p_4$ 的位置，如果 $p_4$ 在三角形里面，那很好处理，条件直接满足了！跟三角形三个点分别连线，新加线段数恰好是 3。

![](https://cdn.luogu.com.cn/upload/image_hosting/3dlsiuf7.png)

当然 $p_4$ 也可以在外面，那将会带来两种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/3y8rulof.png)

在这种情况里，$p_4$ 是合法的，因为它可以看见全部三个点，并分别连线。

![](https://cdn.luogu.com.cn/upload/image_hosting/l33nvbi1.png)

如果是这种情况，$p_4$ 很遗憾看不到 $p_3$​ 导致只能加两条边，这种情况是非法的。

画出多种情况后，我们很容易看出来，所有合法的情况里，都有一个最大的三角形包含了所有的点。

此外，整个大三角形内部会被分割为一个个三角形。

对于所有的 $p_i$，加入的情况都是类似的，总结一下，若 $p_i$ 在最大三角形里面，$p_i$ 一定位于一个内接三角形，连边就好了。

否则，判断能不能形成新的大三角形包含所有点，可以，就和大三角形的三个点连边，不行，则为不合法的情况。

### 具体实现

我们先考虑最重要的操作之一，如何判断一个点是否在三角形内？

对于这个问题，我们可以判断新连边后切割出来的新的三角形的面积之和与原本三角形面积的大小关系，只有相等时点在三角形内。

三角形面积用向量处理，公式很简单：$S=\frac{|x_1(y_2-y_3)+x_2(y_3-y_1)+x_3(y_1-y_2)|}2$。

同时我们要用 $\Theta(n^4)$ 的复杂度预处理出 $w_{i,j,k}(i<j<k)$，为 $i,j,k$ 三点为最大三角形的三个顶点，在大三角形外的点的数量。

我们设 $dp_{i,j,k}(i<j<k)$ 为，$i,j,k$ 老样子，目前我们处理完了三角形外的点后的方案数。

计算答案我们可以考虑倒序处理这个问题，因为，我们发现，最终的所有点都应该被包含在一个最大的三角形里，否则答案为 0！

那我们记录下所有的三角形三元组，按照 $w$ 从小到大排序，然后依次处理答案。

初值只需要找到第一个三元组 $x,y,z$，也就是最大的三角形，$dp_{x,y,z}=1$。

现在我们考虑转移：

设现在的三角形是 $i,j,k$，找到一个 $l$，要求 $l$ 位于三角形内。

首先，$l$ 可以和 $i,j,k$ 中任意两个组合，形成三种新的三角形，假设我们选择处理 $i,j,l(i<j<l)$，记得大小关系可能会发生改变，所以要排序。

先给式子：$dp_{i,j,l}=dp_{i,j,l}+P(w_{i,j,l}-1,w_{i,j,l}-w_{i,j,k}-1)\times dp_{i,j,k}$。

其中我们定义 $P(a,b)=\frac{a!}{(a-b)!}$，自然是 $a$ 个数中选取 $b$ 个的排列方案数。

解释一下式子，我们现在要将 $i,j,l$ 外面的点提前选掉，去掉点 $k$，总共有 $w_{i,j,l}-1$ 个，而现在我们新加了 $w_{i,j,l}-w_{i,j,k}-1$ 个。

这新的 $w_{i,j,l}-w_{i,j,k}-1$ 个点可以是 $w_{i,j,l}-1$ 个点中任选的位置，所以有 $P(w_{i,j,l}-1,w_{i,j,l}-w_{i,j,k}-1)$ 种方案数，点 $k$ 一定最后选。

对于 $i,l,k$ 和 $l,j,k$ 也是一样的方法。

最后，对于一个 $i,j,k$，我们可以更新答案！

式子：$ans=ans+6\times dp_{i,j,k}\times P(n-3,n-w_{i,j,k}-3)$。

怎么说？我们定 $i,j,k$ 为 $p_1,p_2,p_3$，那首先 $i,j,k$ 可以有 6 种排列方法，其次，在 $i,j,k$ 内的点要在 $n-3$ 个点中选择位置，所以还要乘方案数。

记得取模！时间复杂度 $\Theta(n^4)$。

完结撒花(●'◡'●)

### 参考代码

```c++
#include<bits/stdc++.h>
#define fre(x) freopen(#x".in","r",stdin),freopen(#x".out","w",stdout);
typedef long long ll;
using namespace std;
const int N=51,d=1e9+7;
int n,dp[N][N][N],a[N],b[N],w[N][N][N],f,x,y,z,s[N]={1},t[N],cnt,ans,o[5];
struct tri
{
	int a,b,c;
}tr[N*N*N];
int calc(int i,int j,int k)//计算面积
{
	int v=abs(a[i]*(b[j]-b[k])+a[j]*(b[k]-b[i])+a[k]*(b[i]-b[j]));
	return v;
}
int check(int i,int j,int k,int l)//判断是否在三角新内
{
	if(calc(i,j,l)+calc(i,k,l)+calc(j,k,l)==calc(i,j,k))
	  return 1;
	return 0;
}
int quickpow(int b,int p)
{
	int w=1;
	while(p)
	{
		if(p&1)
		  w=1ll*w*b%d;
		b=1ll*b*b%d;
		p=p>>1;
	}
	return w;
}
int P(int x,int y)//排列方案数
{
	int v=1ll*s[x]*t[x-y]%d;
	return v;
}
bool cmp(tri x,tri y)
{
	return w[x.a][x.b][x.c]<w[y.a][y.b][y.c];
}
int main()
{
	int i,j,k,l;
	scanf("%d",&n);
	for(i=1;i<=n;++i)
	  scanf("%d%d",a+i,b+i),s[i]=1ll*s[i-1]*i%d;
	t[n]=quickpow(s[n],d-2);
	for(i=n;i;--i)
	  t[i-1]=1ll*t[i]*i%d;
	for(i=1;i<=n;++i)//预处理w
	{
		for(j=i+1;j<=n;++j)
		{
			for(k=j+1;k<=n;++k)
			{
				++cnt,tr[cnt]=(tri){i,j,k};
				for(l=1;l<=n;++l)
				{
					if(!check(i,j,k,l))
					  ++w[i][j][k];
				}
				if(!w[i][j][k]&&!f)
				  x=i,y=j,z=k,f=1;
			}
		}
	}
	if(!f)
	{
		printf("0");
		return 0;
	}
	sort(tr+1,tr+cnt+1,cmp);//所有
	dp[x][y][z]=1;
	for(i=1;i<=cnt;++i)
	{
		x=tr[i].a,y=tr[i].b,z=tr[i].c;
		ans=(ans+6ll*P(n-3,n-w[x][y][z]-3)*dp[x][y][z]%d)%d;//算答案
		for(j=1;j<=n;++j)
		{
			if(j!=x&&j!=y&&j!=z&&check(x,y,z,j))
			{
				for(k=1;k<=3;++k)
				{
					o[1]=x,o[2]=y,o[3]=z;
					o[k]=j;//把新点塞进去
					sort(o+1,o+4);//记得要满足大小关系
					dp[o[1]][o[2]][o[3]]=(dp[o[1]][o[2]][o[3]]+1ll*P(w[o[1]][o[2]][o[3]]-1,w[o[1]][o[2]][o[3]]-w[x][y][z]-1)*dp[x][y][z]%d)%d;//有点长的转移）
				}
			}
		}
	}
	printf("%d",ans); 
	return 0;
}
```



---

## 作者：tiger2005 (赞：11)

### 题意简述

给定 $N$ 个点，确定排列 $p$ 数量，满足将前三个点连在一起后，在之后的点中，向在排列中在它前面的点连边，有且只有三个不会和之前的线段相交，随后只保留这三条边。数据保证三点不共线。

### 分析

这道题的限制实际上只会有两种情况。我们考虑第四个点加入的情况：

第一种是第四个点在一开始的三角形内侧，此时这个点会向三个点连边，并且将三角形分成更小的三角形。在之后的点中，但凡有一个点在大三角形中间，就会落在一个小三角形内，然后分成三个更小的三角形，以此类推。

第二种是在三角形的外侧。此时这个点一定会满足一个性质：和三角形中两个点组成一个更大的三角形，其中包含了原三角形中的一个点。此时可以理解成大三角形被分割成三个小三角形，之后的情况同上。

我们发现，无论怎么样，最后的轮廓一定是一个三角形，里面被大大小小的三角形填满。考虑记录下外围三角形三个点的位置。

记录 $\operatorname{dp}[i][j][k][l]$ 表示以 $
i,j,k$ 三个点作为外围，已经计算了 $l$ 个点的排列数量。考虑转移。一种转移指内部转移。预处理出 $i,j,k$ 围着的三角形包含的点数量，就相当于在去除了 $l$ 个后任意取一个。一种是向外扩张。枚举三角形内部的一个点，并且假设之前是这个点和另外两个点围出了三角形，但是被剩下的点扩大了，这个时候直接把答案加上小三角形对应的答案即可。

具体的 $\operatorname{dp}$ 方程式不妨自己试着推一下。

注意：将 $i,j,k$ 按照有序的方式进行储存，可以将常数压缩到 $\dfrac 1 6$。如果你的代码超时了可以试着更换方式。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;
struct Point{
	double x,y;
	void init(){
		scanf("%lf%lf",&x,&y);
	}
	Point(double x=0.0,double y=0.0):x(x),y(y){}
	Point operator - (const Point p){
		return Point(x-p.x,y-p.y);
	}
	double operator * (const Point p){
		return fabs(x*p.y-y*p.x);
	}
}A[45];
inline double getArea(int i,int j,int k){
	return (A[i]-A[j])*(A[j]-A[k]);
}
inline bool inTriangle(int i,int j,int k,int x){
	return fabs(getArea(i,j,x)+getArea(j,k,x)+getArea(i,k,x)-getArea(i,j,k))<=1e-6;
}
inline void sort3(int& a,int& b,int& c){
	if(a>=b)	swap(a,b);
	if(a>=c)	swap(a,c);
	if(b>=c)	swap(b,c);
}
int N;
int hav[45][45][45];
long long dp[45][45][45][45];
const long long Md = 1e9 + 7;
int main(){
	scanf("%d",&N);
	for(int i=1;i<=N;i++)	A[i].init();
	for(int i=1;i<=N;i++)
		for(int j=i+1;j<=N;j++)
			for(int k=j+1;k<=N;k++)
				for(int l=1;l<=N;l++)
					if(l!=i && l!=j && l!=k)
						hav[i][j][k]+=inTriangle(i,j,k,l);
	for(int i=1;i<=N;i++)
		for(int j=i+1;j<=N;j++)
			for(int k=j+1;k<=N;k++)
				dp[3][i][j][k]=6;
	for(int s=4;s<=N;s++)
		for(int i=1;i<=N;i++)
			for(int j=i+1;j<=N;j++)
				for(int k=j+1;k<=N;k++){
					if(hav[i][j][k]+4>=s)
						dp[s][i][j][k]=(dp[s-1][i][j][k]*(hav[i][j][k]+4-s))%Md;
					for(int l=1;l<=N;l++)
						if(l!=i && l!=j && l!=k && inTriangle(i,j,k,l)){
							int x,y,z;
							// i j l
							x=i,y=j,z=l;
							sort3(x,y,z);
							(dp[s][i][j][k]+=dp[s-1][x][y][z])%=Md;
							// j k l
							x=j,y=k,z=l;
							sort3(x,y,z);
							(dp[s][i][j][k]+=dp[s-1][x][y][z])%=Md;
							// i k l
							x=i,y=k,z=l;
							sort3(x,y,z);
							(dp[s][i][j][k]+=dp[s-1][x][y][z])%=Md;
						}
				}
	long long ans=0;
	for(int i=1;i<=N;i++)
		for(int j=i+1;j<=N;j++)
			for(int k=j+1;k<=N;k++)
				(ans+=dp[N][i][j][k])%=Md;
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：yaoxi (赞：5)

# **USACO 2021 US Open, Gold**
## **Problem 3. Permutation (排列)**
----

### **题目描述**
有 $N$ $(3 \le N \le 40)$ 个点在二维平面上，没有任何三个点共线。对于每个 $1 \le i \le N$ , 第 $i$ 个点的位置被用两个整数 $x_i$ 和 $y_i$ $(0 \le x_i, y_i \le 10 ^ 4)$ 表示。

Bessie用下面的方式来画连接两个点的线段:

1. 选择一个 $p_1, p_2, ..., p_N$ 的排列
2. 她会用三条线段连接 $p_1$ 和 $p_2$ ,  $p_2$ 和 $p_3$ 以及  $p_3$ 和 $p_1$
3. 接着按顺序对于 $4$ 到 $N$ 之间的整数 $i$ , 她会画一条线段连接点 $p_i$ 和 $p_j$ 使得 $j < i$ 且这条线段不和之前的任何线段相交 (除了端点之外)

Bessie希望对于每个 $i$ , 她都能画 $3$ 条新的线段。请计算可行的排列数。

### **输入格式**
第一行一个整数 $N$ .

接下来的 $N$ 行，每行 $2$ 个用空格隔开的整数 $x_i$ 和 $y_i$ .

### **输出格式**
排列的数量模 $10 ^ 9 + 7$ .

### **样例输入#1**
```
4
0 0
0 4
1 1
1 2
```

### **样例输出#1**
```
0
```

### **样例输入#2**
```
4
0 0
0 4
4 0
1 1
```

### **样例输出#2**
```
24
```

### **样例输入#3**
```
5
0 0
0 4
4 0
1 1
1 2
```

### **样例输出#3**
```
96
```

### **样例解释**
一个对于点序列 $(0,0),(0,4),(4,0),(1,2),(1,1)$ 的可行方案如下。对于这个排列，
- 首先，Bessie分别连接点 $(0,0),(0,4),(4,0)$ 中的每一对
- 其次，她连接点 $(0,0),(0,4),(4,0)$ 到 $(1,2)$
- 最后，她连接点 $(1,2),(4,0),(0,0)$ 到 $(1,1)$
  
![图像](https://cdn.luogu.com.cn/upload/image_hosting/40iof04r.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

### **数据**
- 测试点 1-6  保证 $N \le 8$ .
- 测试点 7-20 无特殊要求.

供题人: Benjamin Qi

题目翻译: yaoxi-std

----
## **题解**
### **大致思路**
前 $3$ 个点必然构成三角形，因为没有三个点共线。

下面考虑第 $4$ 个点的摆放方法。如果放在三角形内部，那么必然是可以连接新的三条线段的。如果放在三角形外面，就得分情况讨论。

![](https://cdn.luogu.com.cn/upload/image_hosting/0fizen1p.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如果新的点放在如图的红色区域中的话，那么是可以连接新的三条线段的，然后构成一个新的三角形。否则这种排列不符合题目要求，就舍去。这样就可以发现，对于每个合法的排列，每次操作之后的图形都会构成一个三角形。

由于 $N$ 很小只有 $40$ , 所以我们可以考虑一个四维的 $dp$ . 令 $dp_{x,y,z,k}$ 表示当前以第 $x, y, z$ 三个点为三角形顶点，且已经用了 $k$ 个点后的排列数。

然后我们枚举下一个点 $p$ , 根据上面的推论，则转移方程为
$$dp_{x,y,z,k}=\sum_{p=1}^{n}dp_{新的p1,p2,p3,k+1} (p \ne x,y,z)$$

状态转移复杂度是 $O(n)$ 的。

初始化 $dp_{x,y,z,N}=1$ .

需要注意已经放置的个数k是否超过三角形内的点个数+3个端点，如果超过，就不能再在三角形内放置了，下一步必须放在三角形外。

最后枚举初始的三个点，求出 $\sum dp_{x,y,z,3}$ .

时间复杂度 $O(n ^ 5)$ , 空间复杂度 $O(n ^ 4)$ .

### **实现细节**

**1. 如何判断一个点在三角形内**

如果对于三角形的每一条边，这个点和这条边的对应点都在这条边的同一侧，那么这条边就在三角形内了。即对于**每一组**边 $BC$ 和其对应端点 $A$ , 若 $A$ 和 $P$ 都在 $BC$ 的同侧，那么点 $P$ 一定在三角形内。

至于如何判断两个点在线段的同侧还是异侧，就要用~~亿点点~~向量叉乘的知识（不会的自行[百度](https://www.baidu.com/s?ie=utf-8&tn=baidu&wd=%E5%90%91%E9%87%8F%E5%8F%89%E4%B9%98)）

**2. 如何判断一个点在刚刚的红色区域里**

同样，对于三角形的某个点 $A$，这个点 $P$ 和点 $C$ 在边 $AB$ 的异侧且点 $P$ 和点 $B$ 在边 $AC$ 的异侧，那么这条边就在点 $A$ 对应的红色区域里，并且更新三角形为 $\Delta PBC$。

一样是用向量的知识求的。

### **代码**
```cpp
/**
 * @file:           permutation.cpp
 * @author:         yaoxi-std
 * @description:    permutation.cpp
*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define resetIO(x) { freopen(x".in", "r", stdin); freopen(x".out", "w", stdout); }
template<class T> inline void read(T &x){
    T f = 1; x = 0; char ch = getchar();
    for( ; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -f;
    for( ; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    x *= f;
}
template<class T> inline void write(T x){
    if(x < 0) { putchar('-'); x = -x; }
    if(x > 9) write(x / 10); putchar((x % 10) ^ 48);
}
const int maxn = 41;
const int inf = 1LL << 60;
const int mod = 1e9+7;
// 向量模版
struct Vec{
    int x, y;
    Vec(){ }
    Vec(int _x, int _y) : x(_x), y(_y) { }
    Vec(pair<int, int> p) : x(p.first), y(p.second) { }
    // 向量加法
    Vec operator+(const Vec &o) const {
        return Vec(x + o.x, y + o.y);
    }
    // 向量减法
    Vec operator-(const Vec &o) const {
        return Vec(x - o.x, y - o.y);
    }
    // 向量数乘
    Vec operator*(const int k) const {
        return Vec(x * k, y * k);
    }
    // 向量点乘
    int operator*(const Vec &o) const {
        return x * o.x + y * o.y;
    }
    // 向量叉乘
    int operator^(const Vec &o) const {
        return x  * o.y - y * o.x;
    }
};
struct Line{
    Vec a, b;
    Line(){ }
    Line(Vec _a, Vec _b) : a(_a), b(_b) { }
    // 获取线段对应的向量
    Vec vector() const {
        return b - a;
    }
    // 判断两个点是否在线段的同侧
    bool side(Vec v1, Vec v2) const {
        Vec x = vector(), y = v1 - a, z = v2 - a;
        return (x ^ y) * (x ^ z) > 0;
    }
};
int n, dp[maxn][maxn][maxn][maxn];
pair<int, int> a[maxn];
// 判断点在三角形内
bool inner_triangle(int p1, int p2, int p3, int i){
    Vec v1(a[p1]), v2(a[p2]), v3(a[p3]), vi(a[i]);
    Line l1(v2, v3), l2(v1, v3), l3(v1, v2);
    // 判断点vi和v1在l1的同侧，和v2在l2的同侧以及和v3在l3的同侧
    return l1.side(v1, vi) && l2.side(v2, vi) && l3.side(v3, vi);
}
// 判断点在红色区域中，如果是则更新成新的三角形三个端点
bool outer_triangle(int &p1, int &p2, int &p3, int i){
    Vec v1(a[p1]), v2(a[p2]), v3(a[p3]), vi(a[i]);
    Line l1(v2, v3), l2(v1, v3), l3(v1, v2);
    // 判断点vi和v1在l1的异侧并且vi和v2在l2的异侧，如果符合则更新v3，下同
    if((!l1.side(v1, vi)) && (!l2.side(v2, vi))) { p3 = i; return true; }
    if((!l1.side(v1, vi)) && (!l3.side(v3, vi))) { p2 = i; return true; }
    if((!l2.side(v2, vi)) && (!l3.side(v3, vi))) { p1 = i; return true; }
    return false;
}
// 记忆化搜索(dp)，dp[p1][p2][p3][k]表示
// 以p1,p2,p3为三角形端点且已经放了k个点的方案数
int dfs(int p1, int p2, int p3, int k){
    // k=n时返回1
    if(k == n) return 1;
    // 排序三角形端点
    if(p1 > p2) swap(p1, p2);
    if(p1 > p3) swap(p1, p3);
    if(p2 > p3) swap(p2, p3);
    if(dp[p1][p2][p3][k] != -1) return dp[p1][p2][p3][k];
    // 用&引用来写记忆化会比较舒服
    int &ret = dp[p1][p2][p3][k]; ret = 0;
    // 计算三角形内点的个数，最后一起计算（算是个优化）
    int cnt_in = 0;
    for(int i=1; i<=n; i++){
        // 新的点不能和三角形端点重复
        if(p1 == i || p2 == i || p3 == i) continue;
        // 分情况讨论
        if(inner_triangle(p1, p2, p3, i)){
            // 计算三角形内点的个数
            cnt_in ++;
        }
        else{
            // 为了防止原来的p1,p2,p3被更改，这里新开了3个变量
            int tp1 = p1, tp2 = p2, tp3 = p3;
            // 判断是否在红色区域
            if(outer_triangle(tp1, tp2, tp3, i))
                (ret += dfs(tp1, tp2, tp3, k + 1)) %= mod;
        }
    }
    // 判断已经放置的个数k是否超过三角形内的点个数+3个端点，如果超过，就不能再在三角形内放置了
    if(cnt_in + 3 > k)
        (ret += (dfs(p1, p2, p3, k + 1) * (cnt_in + 3 - k))) %= mod;
    return ret;
}
signed main(){
    // 读入+初始化
    read(n);
    for(int i=1; i<=n; i++) read(a[i].first), read(a[i].second);
    memset(dp, -1, sizeof(dp));
    int ans = 0;
    // 枚举前三个点的顺序
    for(int p1=1; p1<=n; p1++){
        for(int p2=p1+1; p2<=n; p2++){
            for(int p3=p2+1; p3<=n; p3++){
                (ans += dfs(p1, p2, p3, 3)) %= mod;
            }
        }
    }
    // 因为前三个点可以任意交换位置，所以答案要乘上6
    write((ans * 6) % mod); putchar('\n');
    return 0;
}
```

---

## 作者：Eibon (赞：3)

从第四个点开始考虑，思考何时可以凑出三条边，不难发现，如果想凑出三条边，那么形成的图形依然是一个大三角形被分成许多小三角形的样子。

如果该点在原来的三角形的内侧，那么会形成新的三个小三角形。

不然在外侧，则会与原来的三角形相连，形成两个新的三角形，并构成一个大三角形。

求排列数量，考虑 dp。

因为与三角形的三个顶点有密切关系，所以加入 dp 状态中。再加上一维表示已经转移了的点的个数，即设 $dp_{p1,p2,p3,k}$。

考虑如何判断一个点在三角形内。

当三个小三角形面积加起来等于大三角形时即为。

所以维护一个函数 $S$，用于计算三角形面积。

转移外侧的点可以随意，因为外面的点一定会成为新的大三角形的顶点之一，不会被算重。

转移内侧的点时发现，你无法确定一个点是否已经被加入进来了。

同时注意转移时不能将一个点转移多次，即选了一个点之后将不能再选这个点了。

所以，我们应当将三角形中点的数量 $cnt$ 先预处理出来，贡献即为 $dp_{p1,p2,p3,k+1}\times (cnt-k+3)$。

最后，如果将 $p1$，$p2$ 和 $p3$ 从小到大排序的话，可以优化一下常数。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int maxn=40+5;
const int mod=1e9+7;
int T=1,n,ans;
int f[maxn][maxn][maxn][maxn];
struct node
{
	int x,y;
};
node a[maxn];
ld dis(node a,node b)
{
	return sqrtl((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
ld S(node A,node B,node C)
{
	ld a=dis(B,C),b=dis(A,C),c=dis(A,B);
	ld p=(a+b+c)*0.5;
	return sqrtl(p*(p-a)*(p-b)*(p-c));
}
bool check(ld x,ld y)
{
	return fabs(x-y)<1e-6;
}
int dfs(int p1,int p2,int p3,int k)
{
	if(k==n){
		return 1;
	}
	if(p1>p3){
		swap(p1,p3);
	}
	if(p2>p3){
		swap(p2,p3);
	}
	if(p1>p2){
		swap(p1,p2);
	}
	int &res=f[p1][p2][p3][k];
	if(res!=-1){
		return res;
	}
	res=0;
	int cnt=0;
	ld s=S(a[p1],a[p2],a[p3]);
	for(int i=1;i<=n;i++){
		if(i==p1||i==p2||i==p3){
			continue;
		}
		ld s1=S(a[i],a[p2],a[p3]),s2=S(a[i],a[p1],a[p3]),s3=S(a[i],a[p1],a[p2]);
		if(check(s,s1+s2+s3)){
			cnt++;
		}
		if(check(s1,s+s2+s3)){
			res=(res+dfs(i,p2,p3,k+1))%mod;
		}
		if(check(s2,s+s1+s3)){
			res=(res+dfs(i,p1,p3,k+1))%mod;
		}
		if(check(s3,s+s1+s2)){
			res=(res+dfs(i,p1,p2,k+1))%mod;
		}
	}
	if(cnt+3>k){
		res=(res+(ll)dfs(p1,p2,p3,k+1)*(cnt-k+3)%mod)%mod;
	}
	return res;
}
void solve()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d%d",&a[i].x,&a[i].y);
	}
	memset(f,-1,sizeof(f));
	for(int p1=1;p1<=n;p1++){
		for(int p2=p1+1;p2<=n;p2++){
			for(int p3=p2+1;p3<=n;p3++){
				ans=(ans+dfs(p1,p2,p3,3))%mod;
			}
		}
	}
	printf("%lld\n",(ll)ans*6%mod);
}
signed main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	//scanf("%lld",&T);
	while(T--){
		solve();
	}
	return 0;
}
//dyyyyds
```

---

## 作者：Hasinon (赞：2)

## 前言 ##
这题思路很巧，而且题解都没怎么说具体代码实现，害得我以为这是一道水题,结果却打了我一个晚上（（（  

所以我打算多讲讲本题的**点位置判断**和 **DP 转移**部分。

~~如果有大佬确实觉得本题很水，我自裁罢。~~
## 分析 ##
$N=40$ 是真的令人迷惑，~~蒟蒻考场上以来就想折半状压~~，所以我们先不管它。  

### Part 1
我们先选三个点组成一个三角形，然后尝试找一个点能和这个三角形的三点都连上边，显然这个点只有可能在四种位置。  

![](https://cdn.luogu.com.cn/upload/image_hosting/95hm3hd6.png?x-oss-process=image/resize,m_lfit,h_170,w_225)  

感谢学长 @lcrh 提供的图%%%  

即是三角形的每点两直线夹出来的区域和三角形内部。  
接下来开始分类讨论：

- 如果找到一点在内部，此时会又组成三个小三角形，一点能与新图形连上三条边，只有在这三小三角形里或者在原来的 1，2，3 区域。因为任意三点不共线，所以可以把三小三角形里转化成原来的大三角形里，即判断条件不变。

- 如果找到一点在外部且可行，那么新点会与原来的两点组成一个大三角形，被抛弃的一点被包在这个大三角形里面，和其他三点任意组合形成三个小三角形，同以上情况。

### Part 2
如何判断这个点是否可行?  

对于情况一，判断点 $A$ 是否在大三角形里面，只需要将大三角形的三点随便选两个点出来，和点 $A$ 组成三个小三角形，看这三小三角形的面积和是否与大三角形面积相等。 相等即在里面。

情况二也可以转化为情况一，枚举原三角形的三个端点，如果存在一个端点在另外两端点和点 $A$ 组成的三角形里面，即满足情况二。

### Part 3

所以我们设 DP 状态 $dp_{i,j,k,l}$ 表示最大的三角 形由编号 $i,j,k$ 三点组成且且已选 $l$ 个点。

**但对于情况一，我们发现会存在一个重复取点的问题**  

例如：  

我们用三角形 $i,j,k$ 表示由点 $i,j,k$ 组成的三角形。  
已知三角形 $1,2,3$ 中有编号 $4,5$ 两点。  
显然 $dp_{1,2,3,3}=6$ ，此时我们可以选 $4,5$ 两点进行转移。  
得到 $dp_{1,2,3,4}=2\times dp_{1,2,3,3}=12$，此时我们还可以选 $4,5$ 两点进行转移。   
得到 $dp_{1,2,3,5}=2\times dp_{1,2,3,4}=24$。  
但这样就变成了我们在定三角形后选择 $4,4$，$4,5$，$5,4$，$5,5$ 四种情况。实际上却不应该取多次相同点。  

所以，我们应该且只能预处理出在一个三角形里面有几个点，在转移的时候同三角形状态转移单独处理。  

$dp_{i,j,k,l+1}+=(num-l+3)\times dp_{i,j,k,l}$，$num$ 为三角形 $i,j,k$ 中的总点数。

情况二正常转移即可，即：
$dp_{i',j',k',l+1}+=(num-l+3)\times dp_{i,j,k,l}$，其中 $i',j',k'$ 为新三角形的三端点。

## Code
（情况二的判断写的及其阴间，真要看还是看其他人的吧）  
（为美观度删除快读)
```cpp
// By Hasinon,the juruo who's waiting for AFO life.
/*Mlm:  Tlm:*/
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define mid ((l+r)>>1)
#define FOR(i,a,b) for(int i=(a); i<=(b); ++i)
#define ROF(i,a,b) for(int i=(a); i>=(b); --i)
using namespace std;
bool hasinon;
ll time1=clock();
//
struct node{
	ll x,y;
};
const ll N=40,MOD=1e9+7;
node zb[N+10];
ll stac[5],lstac[5]; 
ll dp[N+10][N+10][N+10][N+10],hav[N+10][N+10][N+10];
//
inline ll cj(node a,node b){
//	printf("%lld %lld %lld %lld\n",a.x,a.y,b.x,b.y) ;
	return a.x*b.y-b.x*a.y;
}
ll ksm(ll a,ll b){
	ll rt=1,la=a;
	while(b){
		if(b&1) rt=rt*la%MOD;
		la=la*la%MOD;
		b>>=1;
	}
	return rt;
}
//
bool Hasinon;
void usage() {
	ll time2=clock();
	cout<<(&Hasinon-&hasinon)/1024/1024<<" Mb, "<<time2-time1<<" Ms\n";
}
int main() {
	ll n=gt();
	FOR(i,1,n){
		zb[i]=(node){gt(),gt()};
	}
	FOR(i,1,n){
		FOR(j,i+1,n){
			FOR(k,j+1,n){
				dp[i][j][k][3]=6;
			}
		}
	}
	FOR(c,3,n-1){
		FOR(i,1,n){
			stac[1]=i;
			FOR(j,i+1,n){
				stac[2]=j;
				FOR(k,j+1,n){
					stac[3]=k;
					if(!dp[i][j][k][c]) continue; 
					if(c>3&&hav[i][j][k]){
						dp[i][j][k][c+1]=(dp[i][j][k][c+1]+dp[i][j][k][c]*(hav[i][j][k]-c+3))%MOD;
					}
					FOR(l,1,n){
						bool lb=0;
						FOR(m,1,3){
							if(l==stac[m]){
								lb=1; break;
							}
						}
						if(lb) continue;
						double stot=abs(cj((node){zb[i].x-zb[l].x,zb[i].y-zb[l].y},(node){zb[j].x-zb[l].x,zb[j].y-zb[l].y}))+
						abs(cj((node){zb[j].x-zb[l].x,zb[j].y-zb[l].y},(node){zb[k].x-zb[l].x,zb[k].y-zb[l].y}))+
						abs(cj((node){zb[k].x-zb[l].x,zb[k].y-zb[l].y},(node){zb[i].x-zb[l].x,zb[i].y-zb[l].y}));
						stot/=2;
						double stri=abs(cj((node){zb[j].x-zb[i].x,zb[j].y-zb[i].y},(node){zb[k].x-zb[i].x,zb[k].y-zb[i].y}));
						stri/=2;
						if(stot==stri){
							if(c==3){
								++hav[i][j][k];
								dp[i][j][k][c+1]+=dp[i][j][k][c];
								dp[i][j][k][c+1]%=MOD;
							}
							continue;
						}
						ll to1,to2;
						FOR(mmto,1,3){
							if(mmto==1) to1=2,to2=3;
							if(mmto==2) to1=1,to2=3;
							if(mmto==3) to1=1,to2=2;
							ll t1=cj((node){zb[stac[mmto]].x-zb[l].x,zb[stac[mmto]].y-zb[l].y},(node){zb[stac[to1]].x-zb[l].x,zb[stac[to1]].y-zb[l].y});
							ll t2=cj((node){zb[stac[mmto]].x-zb[l].x,zb[stac[mmto]].y-zb[l].y},(node){zb[stac[to2]].x-zb[l].x,zb[stac[to2]].y-zb[l].y});
							ll t3=cj((node){zb[stac[to1]].x-zb[stac[to2]].x,zb[stac[to1]].y-zb[stac[to2]].y},(node){zb[stac[to1]].x-zb[l].x,zb[stac[to1]].y-zb[l].y});
							ll t4=cj((node){zb[stac[to1]].x-zb[stac[to2]].x,zb[stac[to1]].y-zb[stac[to2]].y},(node){zb[stac[to1]].x-zb[stac[mmto]].x,zb[stac[to1]].y-zb[stac[mmto]].y});
							if(t1*t2<0&&t3*t4>0){
								FOR(m,1,3) lstac[m]=stac[m];
								lstac[mmto]=l;
								sort(lstac+1,lstac+4);
								dp[lstac[1]][lstac[2]][lstac[3]][c+1]+=dp[i][j][k][c];
								dp[lstac[1]][lstac[2]][lstac[3]][c+1]%=MOD;
								break;
							}	
						}
						
					}
				}
			}
		}
	}
	ll ans=0;
	FOR(i,1,n){
		FOR(j,i+1,n) {
			FOR(k,j+1,n){
				if(!dp[i][j][k][n]) continue; 
				ans+=dp[i][j][k][n];
			}
		}
	}
	printf("%lld",ans);
}
```





---

## 作者：kcn999 (赞：2)

题目要求 $p_4,\cdots,p_n$ 每个点都要连 $3$ 条边，容易发现每次加点有两种情况。

1. 在某个三角形内添加一个点

![](https://cdn.luogu.com.cn/upload/image_hosting/gux16tvs.png)

可以发现，当我们画出一个三角形后，在这之后它内部的点无论按照什么顺序加入，都一定是合法的。

2. 在最大的三角形外添加一个点

![](https://cdn.luogu.com.cn/upload/image_hosting/f4wwhja2.png)

这种方案是合法的。

![](https://cdn.luogu.com.cn/upload/image_hosting/riylpr53.png)

这种方案是不合法的。

当我们向 $\triangle ABC$ 添加点 $P$ 时，可以发现合法的条件为 $AB \cap PC = \varnothing$ 或 $AC \cap PB = \varnothing$ 或 $BC \cap PA = \varnothing$，即存在三角形的一个端点与 $P$ 在另外两个端点所在直线的同一侧。

设 $g(i,j,k)$ 表示 $i,j,k$ 构成的三角形内部的点数（不包括 $i,j,k$），这个容易用 $O(n^4)$ 的复杂度预处理出来。

设 $f(i,j,k,c)$ 表示当前最大的三角形的端点为 $i,j,k$，且此时已经计算了 $c$ 个点的贡献。考虑到端点的顺序并不重要，这里令 $i<j<k$。

一开始枚举 $\{p_1,p_2,p_3\}=\{i,j,k\}$，显然此时 $\triangle ijk$ 内部的 $g(i,j,k)$ 个点任意顺序放都是对的，此时这些点的排列方案数为 $\mathrm{A}(n-3,g(i,j,k))$，其中 $\mathrm A$ 表示排列数。

又因为选取 $i,j,k$ 的顺序也不重要，则令

$$f(i,j,k,g(i,j,k)+3)= \mathrm A(3,3)\times\mathrm A(n-3,g(i,j,k))=6\times\mathrm A(n-3,g(i,j,k))$$

初始化之后，枚举 $x$ 然后枚举 $i,j,k$。因为 $i,j,k$ 内部的点我们已经提前算好贡献了，则只需要枚举 $i,j,k$ 外部的点，记为 $l$。

先判断 $l$ 在 $\triangle ijk$ 外部，且不在它的任意一条边所在的直线上，并且满足最前面所说的条件（存在一个端点与 $l$ 位于另外两个端点所在直线的同一侧）。如果不满足则添加 $l$ 是不合法的。

如果合法，记与 $l$ 同侧的端点为 $z$，另外两个端点为 $x,y$，则此时会产生两个新三角形 $\triangle xzl,\triangle yzl$。

![](https://cdn.luogu.com.cn/upload/image_hosting/36yx9y2v.png)

记 $x,y,l$ 排序之后的结果为 $u,v,w$，则有转移

$$\begin{aligned}&f(u,v,w,c+g(x,z,l)+g(y,z,l)+1) \\ \gets &f(u,v,w,c+g(x,z,l)+g(y,z,l)+1)+f(i,j,k,c)\times\mathrm A(n-c-1,g(x,z,l)+g(y,z,l))\end{aligned}$$

最后答案即为 $\sum_{i<j<k}f(i,j,k,n)$。

总共有 $n^4$ 个状态，每次还要枚举 $l$，则总时间复杂度是 $O(n^5)$ 的，吸氧可过。

```cpp
// O(n^5)
#include <bits/stdc++.h>
#define MAX_N (40 + 5)
#define ll long long
using namespace std;
const int mod = 1e9 + 7;
const double eps = 1e-8;
int n;
struct Node {
	int x, y;
} a[MAX_N];
int f[MAX_N][MAX_N][MAX_N][MAX_N];
int g[MAX_N][MAX_N][MAX_N];
int A[MAX_N][MAX_N];
bool Less(double a, double b) {
	return b - a > eps;
}
int Cross(Node a, Node b, Node c) {
	return (a.x - c.x) * (b.y - c.y) - (a.y - c.y) * (b.x - c.x);
}
bool SamePos(int i, int j, int x, int y) {
	return (ll)Cross(a[x], a[i], a[j]) * Cross(a[y], a[i], a[j]) > 0;
}
bool Inner(int i, int j, int k, int l) {
	return SamePos(i, j, k, l) && SamePos(i, k, j, l) && SamePos(j, k, i, l);
}
bool SameLine(int i, int j, int k) {
	return (a[i].y - a[j].y) * (a[j].x - a[k].x) == (a[j].y - a[k].y) * (a[i].x - a[j].x);
}
void Sort(int &u, int &v, int &w) {
	if (u > v) swap(u, v);
	if (u > w) swap(u, w);
	if (v > w) swap(v, w);	
}
void Get(int i, int j, int k, int l, int &u, int &v, int &w, int &cnt) {
	if (!SamePos(i, l, j, k)) u = j, v = k, w = i;
	else if (!SamePos(j, l, i, k)) u = i, v = k, w = j;
	else u = i, v = j, w = k;
	if (!SamePos(u, v, w, l) || SameLine(u, w, l) || SameLine(v, w, l)) {
		w = -1; 
		return;
	}
	i = u, j = w, k = l;
	Sort(i, j, k);
	cnt += g[i][j][k];
	i = v, j = w, k = l;
	Sort(i, j, k);
	cnt += g[i][j][k];
	w = l;
	Sort(u, v, w);
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d%d", &a[i].x, &a[i].y);
	for (int i = 0; i <= n; ++i) {
		A[i][0] = 1;
		for (int j = 1; j <= i; ++j) 
			A[i][j] = (ll)i * A[i - 1][j - 1] % mod;
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			for (int k = j + 1; k <= n; ++k) {
				for (int l = 1; l <= n; ++l) {
					if (l == i || l == j || l == k) continue;
					if (Inner(i, j, k, l)) ++g[i][j][k];
				}
				f[i][j][k][g[i][j][k] + 3] = 6ll * A[n - 3][g[i][j][k]] % mod;
			}
		}
	}
	for (int I = 3; I < n; ++I) {
		for (int i = 1; i <= n; ++i) {
			for (int j = i + 1; j <= n; ++j) {
				for (int k = j + 1; k <= n; ++k) {
					for (int l = 1; l <= n; ++l) {
						if (l == i || l == j || l == k) continue;
						if (Inner(i, j, k, l)) continue;
						int u = 0, v = 0, w = 0, cnt = 0;
						Get(i, j, k, l, u, v, w, cnt);
						if (w == -1) continue;
						f[u][v][w][I + cnt + 1] = (f[u][v][w][I + cnt + 1] + (ll)f[i][j][k][I] * A[n - I - 1][cnt]) % mod;
					}
				}
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = i + 1; j <= n; ++j)
			for (int k = j + 1; k <= n; ++k)
				ans = (ans + f[i][j][k][n]) % mod;
	printf("%d", ans);
	return 0;
}
```

然而我们发现，$c$ 这一位其实就相当于是 $\triangle ijk$ 所包含的点的个数（包括 $i,j,k$），即 $c=g(i,j,k)+3$。

所以我们可以直接去掉 $c$ 这一维，初始化的时候开 $n$ 个 `vector`，把三元组 $(i,j,k)$ 丢到第 $g(i,j,k)+3$ 个 `vector`。

然后 DP 的时候枚举每一个 `vector` 里面装着的状态即可。

总共有 $n^3$ 个状态，每次还要枚举 $l$，则总时间复杂度为 $O(n^4)$。

```cpp
// O(n^4)
#include <bits/stdc++.h>
#define MAX_N (40 + 5)
#define ll long long
#define pb emplace_back
using namespace std;
const int mod = 1e9 + 7;
const double eps = 1e-8;
int n;
struct Node {
	int x, y;
} a[MAX_N];
struct State {
	int i, j, k;
};
vector<State> s[MAX_N];
int f[MAX_N][MAX_N][MAX_N];
int g[MAX_N][MAX_N][MAX_N];
int A[MAX_N][MAX_N];
bool Less(double a, double b) {
	return b - a > eps;
}
int Cross(Node a, Node b, Node c) {
	return (a.x - c.x) * (b.y - c.y) - (a.y - c.y) * (b.x - c.x);
}
bool SamePos(int i, int j, int x, int y) {
	return (ll)Cross(a[x], a[i], a[j]) * Cross(a[y], a[i], a[j]) > 0;
}
bool Inner(int i, int j, int k, int l) {
	return SamePos(i, j, k, l) && SamePos(i, k, j, l) && SamePos(j, k, i, l);
}
bool SameLine(int i, int j, int k) {
	return (a[i].y - a[j].y) * (a[j].x - a[k].x) == (a[j].y - a[k].y) * (a[i].x - a[j].x);
}
void Sort(int &u, int &v, int &w) {
	if (u > v) swap(u, v);
	if (u > w) swap(u, w);
	if (v > w) swap(v, w);	
}
void Get(int i, int j, int k, int l, int &u, int &v, int &w, int &cnt) {
	if (!SamePos(i, l, j, k)) u = j, v = k, w = i;
	else if (!SamePos(j, l, i, k)) u = i, v = k, w = j;
	else u = i, v = j, w = k;
	if (!SamePos(u, v, w, l) || SameLine(u, w, l) || SameLine(v, w, l)) {
		w = -1; 
		return;
	}
	i = u, j = w, k = l;
	Sort(i, j, k);
	cnt += g[i][j][k];
	i = v, j = w, k = l;
	Sort(i, j, k);
	cnt += g[i][j][k];
	w = l;
	Sort(u, v, w);
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d%d", &a[i].x, &a[i].y);
	for (int i = 0; i <= n; ++i) {
		A[i][0] = 1;
		for (int j = 1; j <= i; ++j) 
			A[i][j] = (ll)i * A[i - 1][j - 1] % mod;
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			for (int k = j + 1; k <= n; ++k) {
				for (int l = 1; l <= n; ++l) {
					if (l == i || l == j || l == k) continue;
					if (Inner(i, j, k, l)) ++g[i][j][k];
				}
				f[i][j][k] = 6ll * A[n - 3][g[i][j][k]] % mod;
				s[g[i][j][k] + 3].pb((State){i, j, k});
			}
		}
	}
	for (int I = 3; I < n; ++I) {
		for (auto S : s[I]) {
			int i = S.i, j = S.j, k = S.k;
			for (int l = 1; l <= n; ++l) {
				if (l == i || l == j || l == k) continue;
				if (Inner(i, j, k, l)) continue;
				int u = 0, v = 0, w = 0, cnt = 0;
				Get(i, j, k, l, u, v, w, cnt);
				if (w == -1) continue;
				f[u][v][w] = (f[u][v][w] + (ll)f[i][j][k] * A[n - I - 1][cnt]) % mod;
			}
		}
	}
	int ans = 0;
	for (auto S : s[n]) {
		int i = S.i, j = S.j, k = S.k;
		ans = (ans + f[i][j][k]) % mod;
	}
	printf("%d", ans);
	return 0;
}
```

---

## 作者：7KByte (赞：1)

目前是最优解。

题目大意：给定平面上任意三点不共线的 $N$ 个点，需要求出满足以下条件的长度为 $N$ 的排列 $P$ 的数量。$N\le 40$ 。

- 条件：首先在给定的第$P_1,P_2,P_3$个点之间两两连边形成三角形。然后对于任何 $i>3$，如果 $j<i$ 且第 $P_i,P_j$ 个点之间连边不与之前的边相交，则连边，否则略过。排列需要满足对于任意 $i>3$ ，都需要连恰好 $3$ 条边。

很有意思的题目。

首先如果我们确定排列的前 $3$ 个点，则圈定了一个初始三角形，不难发现初始三角形内的点可以任意排列。

然后发现，存在三个点，使得所有点都在这三个点构成的三角形内，是有解的充要条件。

确定当前三角形后，有两个选择。
- 一个是选择当前三角形内的点，当前三角形不变。
-  另一个是选择当前三角形外的点，使得当前三角形扩大。

对于第二个选择，并不是所有的点都可以选，还需要判断扩大后是否是三角形。

不难发现如果是选择前后两个三角形所夹的面积中的点可以任意排列。

所以我们可以设计状态 $f[i][j][k]$，表示当前三角形为 $i,j,k$ 的方案数，然后我们枚举一个在三角形内地的点 $pt$ 转移。

但是发现这种方法连样例都过不去。。。

我们还发现可以任意排列的点甚至可以放到排列最后，也就是说当前三角形为$i,j,k$，但是仍然可以有点剩下来。

观察后发现剩下来的点不管位置如何都是等价的，所以我们改进状态为 $f[i][j][k][w]$ 表示当前三角形为 $i,j,k$，还剩下 $w$ 个点的方案数。

由于所有剩下的点是等价的，我们要乘上组合数转移。

还有一个细节就是点$O$是否在$\triangle ABC$内。

点$O$在三角形内的充要条件是 $\angle AOB+\angle BOC+\angle AOC=360^{\circ}$ 。

如何求角度呢，我们发现所有点都是整点，也就是说向量非常好求，那么$\cos \angle AOB=\dfrac{\overrightarrow{OA}\cdot \overrightarrow{OB}}{|\overrightarrow{OA}||\overrightarrow{OB}|}$ 。

转移顺序不好找，直接记忆化搜索。

乍一看时间复杂度是$\rm O(N^7)$的，实际上无用状态非常多，实际复杂度近似于$\rm O(N^4)\sim O(N^5)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 45
#define P 1000000007
using namespace std;
struct vec{
	int x,y;
	double len(){
		return sqrt(x*x+y*y);
	}
	vec(int X=0,int Y=0){x=X;y=Y;}
	int operator*(vec o){
		return x*o.x+y*o.y;
	}
};
int f[N][N][N][N],u[N][N][N],n,x[N],y[N],fac[N],C[N][N];bool flag[N][N][N];
double corn(int a,int b,int c){
	vec u(x[b]-x[a],y[b]-y[a]);
	vec v(x[c]-x[a],y[c]-y[a]);
	return acos(1.00*(u*v)/u.len()/v.len());
}
const double pi = acos (-1) , eps = 1e-8 ;
bool check(int a,int b,int c,int cen){
	return fabs(corn(cen,a,b) + corn(cen,a,c) + corn(cen,b,c)- 2 * pi) < eps;
}
void dp(int i,int j,int k){
	if(flag[i][j][k])return;
	flag[i][j][k]=1;
	rep(t,0,u[i][j][k])f[i][j][k][t]=6LL*C[u[i][j][k]][t]%P*fac[u[i][j][k]-t]%P;
	int c[3];
	rep(p,1,n)if(i!=p&&j!=p&&k!=p&&check(i,j,k,p)){
		c[0]=i;c[1]=j;c[2]=p;sort(c,c+3);dp(c[0],c[1],c[2]);
		rep(q,0,u[i][j][k]-u[c[0]][c[1]][c[2]]-1)rep(w,0,u[c[0]][c[1]][c[2]])rep(t,0,w)
			f[i][j][k][q+t]=(f[i][j][k][q+t]+1LL*f[c[0]][c[1]][c[2]][w]*fac[u[i][j][k]-u[c[0]][c[1]][c[2]]-1-q+w-t]%P*
								C[u[i][j][k]-u[c[0]][c[1]][c[2]]-1][q]%P*C[w][t])%P;
		c[0]=i;c[1]=k;c[2]=p;sort(c,c+3);dp(c[0],c[1],c[2]);
		rep(q,0,u[i][j][k]-u[c[0]][c[1]][c[2]]-1)rep(w,0,u[c[0]][c[1]][c[2]])rep(t,0,w)
			f[i][j][k][q+t]=(f[i][j][k][q+t]+1LL*f[c[0]][c[1]][c[2]][w]*fac[u[i][j][k]-u[c[0]][c[1]][c[2]]-1-q+w-t]%P*
								C[u[i][j][k]-u[c[0]][c[1]][c[2]]-1][q]%P*C[w][t])%P;
		c[0]=k;c[1]=j;c[2]=p;sort(c,c+3);dp(c[0],c[1],c[2]);
		rep(q,0,u[i][j][k]-u[c[0]][c[1]][c[2]]-1)rep(w,0,u[c[0]][c[1]][c[2]])rep(t,0,w)
			f[i][j][k][q+t]=(f[i][j][k][q+t]+1LL*f[c[0]][c[1]][c[2]][w]*fac[u[i][j][k]-u[c[0]][c[1]][c[2]]-1-q+w-t]%P*
								C[u[i][j][k]-u[c[0]][c[1]][c[2]]-1][q]%P*C[w][t])%P;
	}
}
int main(){
	C[0][0]=1;
	rep(i,1,N-5){
		C[i][0]=1;
		rep(j,1,N-5)C[i][j]=(C[i-1][j-1]+C[i-1][j])%P;
	}
	fac[0]=1;
	rep(i,1,N-5)fac[i]=1LL*fac[i-1]*i%P;
	scanf("%d",&n);
	rep(i,1,n)scanf("%d%d",&x[i],&y[i]);
	rep(i,1,n)rep(j,i+1,n)rep(k,j+1,n)rep(p,1,n)if(i!=p&&j!=p&&k!=p&&check(i,j,k,p))u[i][j][k]++;
	rep(i,1,n)rep(j,i+1,n)rep(k,j+1,n)
	rep(i,1,n)rep(j,i+1,n)rep(k,j+1,n)if(u[i][j][k]==n-3){
		dp(i,j,k);
		return printf("%d\n",f[i][j][k][0]),0;
	}
	printf("0\n");
	return 0;
}
```

---

## 作者：Φρανκ (赞：0)

题意：平面上有不共线的 $n$ 个点。求所有排列，满足 $\forall\:3<i\le n,\:p_1p_i,...,p_{i-1}p_i$ 中有且仅有三条不与任意 $p_jp_k$ 相交，其中 $j,k<i$。

核心思想：DP

解：

容易发现，前三个点构成一个三角形。若前 $i$ 个点构成一个被切分为若干个小三角形的三角形且 $p_{i+1}$ 在三角形内，则前 $i+1$ 个点亦构成一个被切分为若干个小三角形的三角形；若其在形外，其连接的三条线段只可能是连接已有大三角形的三个顶点，则前 $i+1$ 个点亦构成一个被切分为若干个小三角形的三角形。因此，由数学归纳法可证前 $i$ 个点一定构成上述图形。

考虑 DP：令 $f(p, i, j, k)$ 表示前 $p$ 个点构成的大三角形顶点为 $p_i,p_j,p_k$ 的排列数。转移有两种方式：第 $p$ 个点为 $p_i,p_j,p_k$ 其中之一或为 $\triangle p_ip_jp_k$ 中一点。对第一种情况，$\triangle p_ip_jp_k$ 中每一点 $q$ 会贡献 $f(p-1,i,j,q)+f(p-1,i,k,q)+f(p-1,j,k,q)$ 种排列数；对第二种情况，设 $\triangle p_ip_jp_k$ 内共有 $k\ge p-3$ 个点，则共产生 $(k+3-p-1)f(p-1,i,j,k)$ 的贡献。按 $p$ 转移即可。时间复杂度 $O(n^5)$。

代码：
```
#include<bits/stdc++.h>
using namespace std;
struct point
{
	double x, y;
}poi[41];
const long long mod=1000000007;
long long n, a[41][41][41][41], b[41][41][41], res;
long long pline(double x1, double y1, double x2, double y2, double x, double y)//判断点和线段关系（上、下）
{
	if(x1==x2)
	{
		if(x<x1)
			return -1;
		return 1;
	}
	if(y<y1+(x-x1)/(x2-x1)*(y2-y1))
		return -1;
	return 1;
}
bool intri(long long x, long long y, long long z, long long p)//判断点和三角形关系
{
	if(pline(poi[x].x, poi[x].y, poi[y].x, poi[y].y, poi[p].x, poi[p].y)==pline(poi[x].x, poi[x].y, poi[y].x, poi[y].y, poi[z].x, poi[z].y))
		if(pline(poi[x].x, poi[x].y, poi[z].x, poi[z].y, poi[p].x, poi[p].y)==pline(poi[x].x, poi[x].y, poi[z].x, poi[z].y, poi[y].x, poi[y].y))
			if(pline(poi[y].x, poi[y].y, poi[z].x, poi[z].y, poi[p].x, poi[p].y)==pline(poi[y].x, poi[y].y, poi[z].x, poi[z].y, poi[x].x, poi[x].y))
				return 1;
	return 0;
}
bool inang(long long x, long long y, long long z, long long p)//未使用
{
	long long t=0;
	if(pline(poi[x].x, poi[x].y, poi[y].x, poi[y].y, poi[p].x, poi[p].y)==pline(poi[x].x, poi[x].y, poi[y].x, poi[y].y, poi[z].x, poi[z].y))
		t++;
	if(pline(poi[x].x, poi[x].y, poi[z].x, poi[z].y, poi[p].x, poi[p].y)==pline(poi[x].x, poi[x].y, poi[z].x, poi[z].y, poi[y].x, poi[y].y))
		t++;
	if(pline(poi[y].x, poi[y].y, poi[z].x, poi[z].y, poi[p].x, poi[p].y)==pline(poi[y].x, poi[y].y, poi[z].x, poi[z].y, poi[x].x, poi[x].y))
		t++;
	if(t==1)
		return 1;
	return 0;
}
int main()
{
	cin>>n;
	for(int i=1; i<=n; i++)
		cin>>poi[i].x>>poi[i].y;
	for(int i=1; i<=n-2; i++)
		for(int j=i+1; j<=n-1; j++)
			for(int k=j+1; k<=n; k++)
				a[3][i][j][k]=6;//初始化
	for(int i=1; i<=n-2; i++)
		for(int j=i+1; j<=n-1; j++)
			for(int k=j+1; k<=n; k++)
				for(int p=1; p<=n; p++)
					if(p!=i && p!=j && p!=k && intri(i, j, k, p)==1)
						b[i][j][k]++;//三角形内点数量
	for(int p=4; p<=n; p++)
		for(int i=1; i<=n-2; i++)
			for(int j=i+1; j<=n-1; j++)
				for(int k=j+1; k<=n; k++)
				{
					if(b[i][j][k]+3>=p)
						a[p][i][j][k]=(a[p][i][j][k]+a[p-1][i][j][k]*(b[i][j][k]+4-p))%mod;//第二种情况
					for(int q=1; q<=n; q++)
						if(q!=i && q!=j && q!=k)
							if(intri(i, j, k, q)==1)
							{
								if(q<i)
									a[p][i][j][k]=(a[p][i][j][k]+a[p-1][q][i][j]+a[p-1][q][i][k]+a[p-1][q][j][k])%mod;
								else if(q<j)
									a[p][i][j][k]=(a[p][i][j][k]+a[p-1][i][q][j]+a[p-1][i][q][k]+a[p-1][q][j][k])%mod;
								else if(q<k)
									a[p][i][j][k]=(a[p][i][j][k]+a[p-1][i][j][q]+a[p-1][i][q][k]+a[p-1][j][q][k])%mod;
								else
									a[p][i][j][k]=(a[p][i][j][k]+a[p-1][i][j][q]+a[p-1][i][k][q]+a[p-1][j][k][q])%mod;//第一种情况
//								cout<<p<<" "<<i<<" "<<j<<" "<<k<<" "<<q<<" "<<a[p][i][j][k]<<endl;
							}
				}
	for(int i=1; i<=n-2; i++)
		for(int j=i+1; j<=n-1; j++)
			for(int k=j+1; k<=n; k++)
			{
//				cout<<n<<" "<<i<<" "<<j<<" "<<k<<" "<<a[n][i][j][k]<<endl;
				res=(res+a[n][i][j][k])%mod;//求结果
			}
	cout<<res;
    return 0;
}
```

---

