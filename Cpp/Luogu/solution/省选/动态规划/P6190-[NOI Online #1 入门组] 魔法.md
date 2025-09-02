# [NOI Online #1 入门组] 魔法

## 题目描述

C 国由 $n$ 座城市与 $m$ 条有向道路组成，城市与道路都从 $1$ 开始编号，经过 $i$ 号道路需要 $t_i$ 的费用。

现在你要从 $1$ 号城市出发去 $n$ 号城市，你可以施展最多 $k$ 次魔法，使得通过下一条道路时，需要的费用变为原来的相反数，即费用从 $t_i$ 变为 $-t_i$。请你算一算，你至少要花费多少费用才能完成这次旅程。

注意：使用魔法只是改变一次的花费，而不改变一条道路自身的 $t_i$；最终的费用可以为负，并且一个城市可以经过多次（包括 $n$ 号城市）。 

## 说明/提示

#### 输入输出样例 1 解释

依次经过 $1$ 号道路、$2$ 号道路、$3$ 号道路，并在经过 $1,2$ 号道路前使用魔法。 

#### 输入输出样例 2 解释

依次经过 $1$ 号道路、$2$ 号道路、$1$ 号道路，并在两次经过 $1$ 号道路前都使用魔法。 

#### 数据规模与约定

本题共 $20$ 个测试点，各测试点信息见下表。

| 测试点编号 | $n \leq$ | $m \leq$ | $k \leq$ | 无环 |
| :----------: | :--------: | :---------: | :--------: | :----: |
| $1 \sim 2$ | $5$ | $20$ | $0$ | 不保证 |
| $3 \sim 4$ | $10$ | $20$ | $50$ | 不保证 |
| $5 \sim 6$ | $10$ | $20$ | $0$| 不保证 |
| $7 \sim 8$ | $20$ | $200$ | $50$ | 是 |
| $9 \sim 10$ | $20$ | $200$ | $0$ | 不保证 |
| $11 \sim 12$ | $100$ | $200$ | $50$ | 是 |
| $13 \sim 14$ | $100$ | $200$ | $50$ | 不保证 |
| $15 \sim 18$ | $100$ | $2500$ | $1000$ | 不保证 |
| $19 \sim 20$ | $100$ | $2500$ | $10^6$ | 不保证 |

对于【无环】一栏为“是”的测试点，保证给出的图是一张有向无环图，否则不对图的形态做任何保证。

对于全部的测试点，保证：
- $1 \leq n \leq 100$，$1 \leq m \leq 2500$，$0 \leq k \leq 10^6$。
- $1 \leq u_i, v_i \leq n$，$1 \leq t_i \leq 10^9$。
- 给出的图无重边和自环，且至少存在一条能从 $1$ 到达 $n$ 的路径。

**民间数据使用 [CYaRon](https://github.com/luogu-dev/cyaron) 在 5 分钟内生成。如果发现数据有问题，请在讨论版发帖或私信 @[StudyingFather](/user/22030)**

## 样例 #1

### 输入

```
4 3 2
1 2 5
2 3 4
3 4 1
```

### 输出

```
-8```

## 样例 #2

### 输入

```
2 2 2
1 2 10
2 1 1
```

### 输出

```
-19```

# 题解

## 作者：gaozitao1 (赞：83)

题解可能有一点长，请耐心看完~~谢谢~~

~~2020年CCF入门组测试出两个紫题，提高组都只是3个蓝题。。。~~

题目大意：有一个n个点，m条边的图，你可以使用k此魔法，使通过下一条道路时，距离变为原来的相反数，问从1到n的最小距离。

~~前置知识：dfs,Floyd,spfa(默认为大家都会qwq~~

# 30分
~~显然~~当k=0时，就是一个最短路的板子题，因为n的范围太小了，所以用Floyd就可以了。Floyd应该都会吧。。。
30分代码：
```cpp
#include<cmath>
#include<cstdio>
#include<iostream>
const short M(2501),N(101);//比规定值大1即可
const long long I(2500000000001);//无穷大为m*t（边权）+1
long long d[N][N];//d[i][j]表示从i到j的最小距离
int main()
{
	short i,j,l,m,n,u,v;
	int k,t;
	scanf("%hd%hd%d",&n,&m,&k);//输入，虽然不需要k,但是还是要输入
	for(i=1; i<=n; ++i)
		for(j=1; j<=n; ++j)
			if(i!=j)//如果i==j，d[i][j]=0
				d[i][j]=I;//否则，赋值成无穷大
	for(i=1; i<=m; ++i)
	{
		scanf("%hd%hd%d",&u,&v,&t);//输入边
		d[u][v]=t;//存边
	}
	for(l=1; l<=n; ++l)//Floyd板子（加上了一点优化）
		for(i=1; i<=n; ++i)
			if(i!=l)//如果i=l，下面的式子就变成了d[i][j]=min(d[i][j],d[i][i]+d[i][j]),而d[i][i]=0，不用做了
				for(j=1; j<=n; ++j)
					if(i!=j&&j!=l&&d[i][j]>d[i][l]+d[l][j])//同上
						d[i][j]=d[i][l]+d[l][j];
	printf("%lld",d[1][n]);//输出从1到n的最小值
	return 0;
}
```

# 50分Floyd
可以发现，当这一张图是一张有向无环图时，每一条边最多走一遍，所以一开始处理的时候可以全部记录成负数，就可以把这一部分AC了。

50分Floyd代码：
```cpp
#include<cmath>
#include<cstdio>
#include<iostream>
const short M(2501),N(101);//比规定值大1即可
const long long I(2500000000001);//无穷大为m*t（边权）+1
long long d[N][N];//d[i][j]表示从i到j的最小距离
int main()
{
	short i,j,l,m,n,u,v;
	int k,t;
	scanf("%hd%hd%d",&n,&m,&k);//输入
	for(i=1; i<=n; ++i)
		for(j=1; j<=n; ++j)
			if(i!=j)//如果i==j，d[i][j]=0
				d[i][j]=I;//否则，赋值成无穷大
	for(i=1; i<=m; ++i)
	{
		scanf("%hd%hd%d",&u,&v,&t);//输入
		if(k)//能使用魔法
			d[u][v]=-t;//使用魔法
		else//不能使用魔法
			d[u][v]=t;//不使用魔法
	}
	for(l=1; l<=n; ++l)//Floyd板子（加上了一点优化）
		for(i=1; i<=n; ++i)
			if(i!=l)//如果i=l，下面的式子就变成了d[i][j]=min(d[i][j],d[i][i]+d[i][j]),而d[i][i]=0，不用做了
				for(j=1; j<=n; ++j)
					if(i!=j&&j!=l&&d[i][j]>d[i][l]+d[l][j])//同上
						d[i][j]=d[i][l]+d[l][j];
	printf("%lld",d[1][n]);//输出从1到n的最小值
	return 0;
}
```

# 50分搜索
这一道题用搜索也可以得50分。

50分dfs代码：
```cpp
#include<cmath>
#include<cstdio>
#include<iostream>
const short M(2501),N(101);//比规定值大1即可
const long long I(2500000000001);//无穷大为m*t（边权）+1
short c,e[M],h[N],n,o[M];
int w[M];
long long a(I);//先赋值成无穷大
inline void add(short u,short v,int x)
{
	e[++c]=h[u];
	h[u]=c;
	o[c]=v;
	w[c]=x;
}//spfa建边
inline void dfs(short b,int d,long long f)//b表示当前点，d表示剩余魔法次数，f表示价值
{
	if(a<=f&&d==0)//如果价值大于最小值
		return;//直接返回
	if(b==n)//如果到终点
		if(a>f)//记录最小值
			a=f;//因为n号点可以经过好几次，所以不要return
	short i;
	for(i=h[b]; i; i=e[i]) //spfa遍历边
	{
		dfs(o[i],d,f+w[i]);//不使用魔法
		if(d>0)//可以使用魔法
			dfs(o[i],d-1,f-w[i]);
	}
}
int main()
{
	short i,m,u,v;
	int k,t;
	scanf("%hd%hd%d",&n,&m,&k);
	for(i=1; i<=m; ++i)
	{
		scanf("%hd%hd%d",&u,&v,&t);//输入
		add(u,v,t);//建边
	}
	dfs(1,k,0);
	printf("%lld",a);//输出结果
	return 0;
}
```

# 70分
这一道题也是一个dp题，可以先处理使用0次和1次魔法的情况，之后用动态规划求出使用2到k次魔法的情况。

首先是几个状态转移方程：

1   不使用魔法

d[i][j][0]=min（d[i][j][0]，d[i][l][0]+d[l][j][0]）

Floyd的状态转移方程，相信大家都会

2   使用一次魔法

d[i][j][1]=min（d[i][j][0]，d[i][j][1]）

使用魔法之后距离肯定不超过不使用魔法的距离

d[i][j][1]=min（d[i][j][1]，d[i][u[l]][0]+d[v[k]][j][0]-t[l]）

d[i][u[l]][0]表示从i到第l条边的起点的距离

d[v[k]]][j][0]表示从第l条边的终点到j的距离

d[i][u[l]][0]+d[v[k]][j][0]-t[l]表示从i到j走第l条边并在第l条边使用魔法的距离

所以原式表示不使用魔法和在第l条边使用魔法的最小距离

3   使用k次魔法

d[i][j][p]=min（d[i][j][p]，d[i][l][p-1]+d[l][j][1]）

从i到j使用p次魔法的最小距离是本身或从i到l使用p-1次魔法和从l到j使用1次魔法的最小值

为什么一个是p-1一个是1呢？

因为1已经提前求出来了，所以其中一个一定是1，而p-1在上一步也已经求出来了，所以一个是1一个是p-1，才能保证总数为p。把1和p-1的位置换过来也是可以的，因为经过循环两种情况都会做一遍

70分代码：
```cpp
#include<cmath>
#include<cstdio>
#include<iostream>
const short K(1001),M(2501),N(101);//比规定范围大1即可
const long long I(2500000000001);//规定无穷大为n*t（边权）+1即可
long long d[N][N][K];//注意开long long，K太大会MLE
//d[i][j][l]表示从i到j最多使用l吃次魔法时的最小距离
int main()
{
	short i,j,l,m,n,p,u[M],v[M];
	int k,o,t[M];
	scanf("%hd%hd%d",&n,&m,&k);//输入
	for(o=0; o<=k; ++o)
		for(i=1; i<=n; ++i)
			for(j=1; j<=n; ++j)
				d[i][j][o]=I;//初始化成最大值
	for(i=1; i<=n; ++i)
		d[i][i][0]=0;//自己到自己为0
	for(i=1; i<=m; ++i)
	{
		scanf("%hd%hd%d",&u[i],&v[i],&t[i]);//输入
		d[u[i]][v[i]][0]=t[i];
	}
	//先处理不使用魔法的情况
	for(l=1; l<=n; ++l)//Floyd板子（加上了一些小小的优化）
		for(i=1; i<=n; ++i)
			if(i!=l)//如果i=l，下面的式子就变成了d[i][j][0]=min(d[i][j][0],d[i][i][0]+a[i][j][0]),而d[i][i][0]=0，可以不用做
				for(j=1; j<=n; ++j)
					if(i!=j&&j!=l&&d[i][j][0]>d[i][l][0]+d[l][j][0])//道理同上
						d[i][j][0]=d[i][l][0]+d[l][j][0];
	//再处理使用1次魔法的情况
	for(l=1; l<=m; ++l) //枚举使用魔法的边
		for(i=1; i<=n; ++i)
			for(j=1; j<=n; ++j) //枚举两个点
			{
				if(d[i][j][0]<d[i][j][1])
					d[i][j][1]=d[i][j][0];//先记录上一次的结果
				if(d[i][j][1]>d[i][u[l]][0]+d[v[l]][j][0]-t[l])
					d[i][j][1]=d[i][u[l]][0]+d[v[l]][j][0]-t[l];//判断经过第l条使用魔法的边后距离是否变短
			}
	for(p=2; p<=k; ++p) //枚举使用几次魔法，从2开始就可以了
		for(l=1; l<=n; ++l) //枚举转折点
			for(i=1; i<=n; ++i) //枚举起点
				for(j=1; j<=n; ++j) //枚举终点
					if(d[i][j][p]>d[i][l][p-1]+d[l][j][1])
						d[i][j][p]=d[i][l][p-1]+d[l][j][1];
	//从i到j使用p次魔法的最小距离是本身或从i到l使用p-1次魔法和从l到j使用1次魔法的最小值
	printf("%lld",d[1][n][k]);//输出从1到n最多使用k次魔法的最小距离
	return 0;
}
```

# 90分
分层图做法，每一次使用魔法就往下走一层。

核心建边：

第一个循环枚举每一条边，第二个循环枚举每一层，循环中第一行表示建立每一层横着的边，第二行表示从上一层到这一层的边。

之后，再跑一边spfa就可以了。

注意！！！spfa要修改！！！

90分代码：
```cpp
#include<cmath>
#include<cstdio>
#include<iostream>
#include<queue>
using std::queue;
const short K(1001),M(2501),N(101);//比最大值大1即可
const long long I(2500000000001);//无穷大时m*t（边权）+1
//有n*k+n个点，2*m*k+m条边
int c,e[M+2*K*M],h[N+N*K],k,m,n,o[M+2*K*M],w[M+2*K*M];
long long d[N+N*K];
inline void add(int u,int v,int x)
{
	e[++c]=h[u];
	h[u]=c;
	o[c]=v;
	w[c]=x;
}//spfa建边
//spfa模板\注意，这一个spfa不需要bool数组，加上只能得到75分\这一个卡spfa的方式好奇怪
inline void spfa(short s)
{
	int i,u;
	queue<int>q;
	for(i=1; i<=n+n*k; ++i)
		d[i]=I;
	d[s]=0;
	q=queue<int>();
	q.push(s);
	while(!q.empty())
	{
		u=q.front();
		q.pop();
		for(i=h[u]; i; i=e[i])
			if(d[o[i]]>d[u]+w[i])
			{
				d[o[i]]=d[u]+w[i];
				q.push(o[i]);
			}
	}
}
int main()
{
	int i,j,u[M],v[M],t[M];
	long long a(I);//要求最小值，先赋值成最大值
	scanf("%d%d%d",&n,&m,&k);//输入
	for(i=1; i<=m; ++i)
	{
		scanf("%d%d%d",&u[i],&v[i],&t[i]);//输入
		add(u[i],v[i],t[i]);//spfa建边
	}
	for(i=1; i<=m; ++i)//建立分层图
		for(j=1; j<=k; ++j)
		{
			add(u[i]+n*j,v[i]+n*j,t[i]);//建立横着的边
			add(u[i]+n*(j-1),v[i]+n*j,-t[i]);//建立斜着的边
		}
	spfa(1);//spfa
	for(i=n; i<=n+n*k; i+=n)
		if(a>d[i])
			a=d[i];//寻找最小值，注意最小值不一定是n*k+n，必须遍历每一层的n
	printf("%lld",a);
	return 0;
}
```

# 100分
会发现，70分的dp做法无论是时间还是空间，都过不了这一道题的限制（1s，250MB）

所以要进行优化（100分做法）。

优化之前，先大概讲一下本题用到的知识：矩阵快速幂。

矩阵快速幂实质上就是快速幂和矩阵乘法的合体

## 快速幂：

众所周知，求a的b次方普通做法的时间复杂度为O（b），而快速幂的时间复杂度为O（logb）

求a的b次方普通做法可以用循环解决。考虑优化一下，如果提前算出a的平方，那么a的b次方，时间复杂度为O（b/2），如果继续算出了a的4次方、8次方、16次方等，那么就相当于对b进行了二进制拆分，时间复杂度就变成了O（logb）

~~P1226的题解中有详细的讲解~~

代码：
```cpp
inline int quickpower(int x,int y)
{
    int a(1),c(x);
    while(y)//y!=0
    {
        if(y&1)//y%2==1
            a*=c;//a=a*c
        c*=c;//c=c*c
        y>>=1;//y=y/2
    }
    return a;
}
```

## 矩阵乘法：
一个n*m的矩阵可以和一个m*o的矩阵相乘得到一个n*o的矩阵，n，m，o可以相同，m和m必须一样，两个矩阵相乘必须第一个矩阵的列和第二个矩阵的行相同。

结果矩阵的第i行第j列结果是a矩阵的第i行的每一个数乘上b矩阵的第j列的每一个数。

代码：
```cpp
struct jz
{
	int e[N][N],m,n;//n记录行，m记录列
} a,b;
jz operator*(const jz &x,const jz &y)//重载运算符
{
	short i,j,k;
	jz z;
	z.n=x.n;//记录边长
	z.m=y.m
	for(i=1; i<=z.n; ++i)
		for(j=1; j<=z.m; ++j)
			z.e[i][j]=0;//清零
	for(k=1; k<=x.m; ++k)
		for(i=1; i<=x.n; ++i)
			for(j=1; j<=y.m; ++j)
				z.e[i][j]+=x.e[i][k]*y.e[k][j];//矩阵乘法核心代码
	return z;
}
```
## 矩阵快速幂：
由矩阵乘法的定义可知，如果a*a合法，那么a的行等于a的列，所以可以快速幂的矩阵必须是方阵（行和列相等）

之后，快速幂中有一个a，初始化为1，那么矩阵快速幂中的1是什么呢？
之所以定义为1，因为任何数乘1都等于它本身，所以，一定要找到一个方阵a，使与a边长相同的矩阵乘a结果等于它本身。

这里的a是单位矩阵，只有对角线是1，其他的值都为0，这时能保证与a边长相同的矩阵乘a结果等于它本身。

之后，矩阵快速幂和快速幂基本上就差不多了。

代码：
```cpp
#include<cmath>
#include<cstdio>
#include<iostream>
const short N(101);
struct jz
{
	int e[N][N],n;//n记录边长
} a,b;
jz operator*(const jz &x,const jz &y)//重载运算符
{
	short i,j,k;
	jz z;
	z.n=x.n;//记录边长
	for(i=1; i<=z.n; ++i)
		for(j=1; j<=z.n; ++j)
			z.e[i][j]=0;//清零
	for(k=1; k<=z.n; ++k)
		for(i=1; i<=z.n; ++i)
			for(j=1; j<=z.n; ++j)
				z.e[i][j]+=x.e[i][k]*y.e[k][j];//矩阵乘法核心代码
	return z;
}
inline jz qp(jz x,int y)//求x的y次方
{
	short i,j;
	jz c,d(x);
	c.n=x.n;
	for(i=1; i<=c.n; ++i)
		for(j=1; j<=c.n; ++j)
			if(i!=j)
				c.e[i][j]=0;
			else
				c.e[i][j]=1;//定义单位矩阵
	while(y)
	{
		if(y&1)
			c=c*d;//注意，不能写成c*=d，因为重载的是*，不是*=
		d=d*d;
		y>>=1;
	}//快速幂模板
	return c;
}
int main()
{
	short c,i,j,n;
	scanf("%hd%hd",&n,&c);
	a.n=n;//记录边长
	for(i=1; i<=n; ++i)
		for(j=1; j<=n; ++j)
			scanf("%d",&a.e[i][j]);//输入
	b=qp(a,c);//求a的c次方
	for(i=1; i<=n; ++i)
	{
		for(j=1; j<=n; ++j)
			printf("%d ",b.e[i][j]);
		putchar('\n');//输出
	}
	return 0;
}
```

好了，再次回归本题的100分做法。

前面与70分做法差不多。

代码（部分）：
```cpp
#include<cmath>
#include<cstdio>
#include<iostream>
const short M(2501),N(101);//比规定范围大1即可
const long long I(2500000000001);//规定无穷大为n*t（边权）+1即可
long long d[N][N];//存不使用魔法时的距离，注意开long long
int main()
{
	short i,j,l,m,n,u[M],v[M];
	int k,t[M];
	scanf("%hd%hd%d",&n,&m,&k);
	for(i=1; i<=n; ++i)
		for(j=1; j<=n; ++j)
			if(i!=j)
				d[i][j]=I;//初始化成最大值
	for(i=1; i<=m; ++i)
	{
		scanf("%hd%hd%d",&u[i],&v[i],&t[i]);//输入
		d[u[i]][v[i]]=t[i];
	}
	//先处理不使用魔法的情况
	for(l=1; l<=n; ++l)//Floyd板子（加上了一些小小的优化）
		for(i=1; i<=n; ++i)
			if(i!=l)//如果i=l，下面的式子就变成了d[i][j]=min(d[i][j],d[i][i]+a[i][j]）,而d[i][i]=0,不用做
				for(j=1; j<=n; ++j)
					if(i!=j&&j!=l&&d[i][j]>d[i][l]+d[l][j])//道理同上
						d[i][j]=d[i][l]+d[l][j];
	if(k)//可以使用魔法
	{
		//再处理使用1次魔法的情况
		a.n=n;
		for(i=1; i<=n; ++i)
			for(j=1; j<=n; ++j)
				a.e[i][j]=d[i][j];//先存储不使用魔法的情况
		for(l=1; l<=m; ++l) //枚举使用魔法的边
			for(i=1; i<=n; ++i)
				for(j=1; j<=n; ++j) //枚举两个点
					if(a.e[i][j]>d[i][u[l]]+d[v[l]][j]-t[l])
						a.e[i][j]=d[i][u[l]]+d[v[l]][j]-t[l];//判断经过第l条使用魔法的边后距离是否变短
		//输出结果
		return 0;//结束
	}
	printf("%lld",d[1][n]);//不能使用魔法
	return 0;
}
```

通过70分做法中的状态转移方程：

d[i][j][q]=min(d[i][j][q]，d[i][k][q-1]+d[k][j][1])

其实还可以写成：

d[i][j][x+y]=min(d[i][j][x+y]，d[i][k][x]+d[k][j][y])

会发现，如果把+换成*，把min换成“求和”，那么就和矩阵乘法长得差不多了，所以可以把矩阵乘法的代码稍微改一下，求最小值：

之后，就只剩下最后一个求值部分了。

**注意，接下来的矩阵乘法是修改过的矩阵乘法，不是原本的矩阵乘法**

用70分做法，把样例1的dp数组打表后结果如下（I表示无穷大）：

不使用魔法：

0  5  9 10

I  0  4  5 

I  I  0  1

I  I  I  0

使用1次魔法：

I -5 -1  0

I  0 -4 -3

I  I  0 -1

I  I  I  0

使用两次魔法：

0 -5 -9 -8

I  0 -4 -5

I  I  0 -1

I  I  I  0

会发现，用修改过的矩阵乘法，第一个矩阵乘上第二个矩阵就是第二个矩阵，第一个矩阵乘上第二个矩阵的平方就是第三个矩阵，如果继续打表出使用三次魔法的矩阵，会发现，第一个矩阵乘上第二个矩阵的三次方就是第四个矩阵。

总结：用第一个矩阵（不使用魔法的矩阵）乘上第二个矩阵（使用1次魔法的矩阵）的k次方相当于使用k次魔法。

所以结果就是不使用魔法的矩阵乘上使用一次魔法的矩阵的k次方。

又可以发现，原来的快速幂是单位矩阵乘上矩阵的k次方，所以可以吧单位矩阵换成不使用魔法的矩阵即可

“矩阵快速幂”代码：

如果不使用矩阵快速幂，时间复杂度和70分做法相同（又一次证明了算法的正确性），但是使用矩阵快速幂，时间复杂度就可以降到O（n2m+n3logk），而logk最大为20，所以可以忽略，时间复杂度为O（n2m），空间复杂度为O（n2）。

完整满分代码：
```cpp
#include<cmath>
#include<cstdio>
#include<iostream>
const short M(2501),N(101);//比规定范围大1即可
const long long I(2500000000001);//规定无穷大为n*t（边权）+1即可
long long d[N][N];//存不使用魔法时的距离，注意开long long
struct jz
{
	short n;
	long long e[N][N];
} a;
jz operator*(const jz &x,const jz &y)//重载运算符
{
	short i,j,k;
	jz z;
	z.n=x.n;//记录结果矩阵的边长
	for(i=1; i<=z.n; ++i)
		for(j=1; j<=z.n; ++j)
			z.e[i][j]=I;//因为要求最小值，先赋值成最大值
	for(k=1; k<=z.n; ++k)
		for(i=1; i<=z.n; ++i)
			for(j=1; j<=z.n; ++j)
				if(x.e[i][k]+y.e[k][j]<z.e[i][j])
					z.e[i][j]=x.e[i][k]+y.e[k][j];//改成min
	return z;//返回
}
inline jz qp(jz x,int y)//求x的y次方
{
	short i,j;
	jz e,f(x);//f=x
	e.n=x.n;//记录边长
	for(i=1; i<=e.n; ++i)
		for(j=1; j<=e.n; ++j)
			e.e[i][j]=d[i][j];//先赋值成d矩阵
	while(y)
	{
		if(y&1)
			e=e*f;//注意，不可以写成d*=e，因为重载的运算符是*，不是*=
		f=f*f;//同上
		y>>=1;
	}//快速幂模板
	return e;
}
int main()
{
	short i,j,l,m,n,u[M],v[M];
	int k,t[M];
	scanf("%hd%hd%d",&n,&m,&k);
	for(i=1; i<=n; ++i)
		for(j=1; j<=n; ++j)
			if(i!=j)
				d[i][j]=I;//初始化成最大值
	for(i=1; i<=m; ++i)
	{
		scanf("%hd%hd%d",&u[i],&v[i],&t[i]);//输入
		d[u[i]][v[i]]=t[i];
	}
	//先处理不使用魔法的情况
	for(l=1; l<=n; ++l)//Floyd板子（加上了一些小小的优化）
		for(i=1; i<=n; ++i)
			if(i!=l)//如果i=l，下面的式子就变成了d[i][j]=min(d[i][j],d[i][i]+a[i][j]）,而d[i][i]=0,不用做
				for(j=1; j<=n; ++j)
					if(i!=j&&j!=l&&d[i][j]>d[i][l]+d[l][j])//道理同上
						d[i][j]=d[i][l]+d[l][j];
	if(k)//可以使用魔法
	{
		//再处理使用1次魔法的情况
		a.n=n;
		for(i=1; i<=n; ++i)
			for(j=1; j<=n; ++j)
				a.e[i][j]=d[i][j];//先存储不使用魔法的情况
		for(l=1; l<=m; ++l) //枚举使用魔法的边
			for(i=1; i<=n; ++i)
				for(j=1; j<=n; ++j) //枚举两个点
					if(a.e[i][j]>d[i][u[l]]+d[v[l]][j]-t[l])
						a.e[i][j]=d[i][u[l]]+d[v[l]][j]-t[l];//判断经过第l条使用魔法的边后距离是否变短
		printf("%lld",qp(a,k).e[1][n]);//输出结果
		return 0;//结束
	}
	printf("%lld",d[1][n]);//不能使用魔法
	return 0;
}
```
orz

---

## 作者：StudyingFather (赞：44)

**[更好的阅读体验](https://studyingfather.com/archives/3008)**

作为一名参加了提高组却爆炸的菜鸡，在入门组进行的时候口胡了一下这题的解法。

我们来根据 $k$ 的情况分类讨论下：

- $k=0$

非常 trivial 的情况，直接跑 Floyd 即可得出结果。

- $k=1$

考虑从 $k=0$ 的情况推 $k=1$ 的情况。

设 $f_{k,i,j}$ 表示在使用不超过 $k$ 次魔法的情况下，从 $i$ 到 $j$ 的最短路。

现在我们知道了 $f_{0,i,j}$，如何得到 $f_{1,i,j}$ 呢？

边的规模只有 $2500$，我们可以直接枚举要用魔法的边，转移时强制走这条边，求最短路。

假如边 $(u,v,w)$ 用了魔法，转移方程如下：

$$
f_{1,i,j}=\min\{f_{0,i,j},\min f_{0,i,u}+f_{0,v,j}-w\}
$$

- $k=2$

我们已经得到了 $k=1$ 的情况，如何推 $k=2$ 的情况呢？

类似于 Floyd，我们可以枚举一个中转点 $k$，$i \to k$ 最多用一次魔法，$k \to j$ 最多用一次魔法，合并起来就是最多两次魔法的答案了。

写成式子长这样：

$$
f_{2,i,j}=\min f_{1,i,k}+f_{1,k,j}
$$

如果你做过很多矩阵优化的题，会发现这个形式挺像矩阵乘法。

所不同的是：原来是若干个乘积的和相加，现在变成了若干个和取最小值。

类比一下，我们猜想这个可以用矩阵快速幂来优化转移。

- $k \gt 2$

根据 $k=2$ 的情况，我们猜想：最多用 $i$ 次魔法的结果和最多用 $j$ 次魔法的结果按照上面的转移方式合并的话，可以得到最多用 $i+j$ 次魔法的结果。

这个成立的前提是我们定义的这个矩阵运算要具有结合律，这样我们才能用快速幂来计算。

数的加法和乘法都满足结合律，从而有龟速乘和快速幂。

矩阵的乘法满足结合律，从而能用矩阵快速幂加快计算速度。

我们这个运算满足结合律吗？答案是肯定的。

~~这个可以感性理解下，严谨的证明留给各位读者练习。~~

到这里本题就得到了完美解决。

```cpp
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
struct edge
{
 int u,v,w;
}e[2505];
int n,m,k;
struct mat
{
 long long a[105][105];
 mat(int x=63)
 {
  memset(a,x,sizeof(a));
 }
 mat operator*(const mat&b)const
 {
  mat ans;
  for(int k=1;k<=n;k++)
   for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
     ans.a[i][j]=min(ans.a[i][j],a[i][k]+b.a[k][j]);
  return ans;
 }
}a;
long long f[105][105];
mat fpow(mat x,int y)
{
 mat ans;
 for(int i=1;i<=n;i++)
  for(int j=1;j<=n;j++)
   ans.a[i][j]=f[i][j];
 while(y)
 {
  if(y&1)ans=ans*x;
  x=x*x;
  y>>=1;
 }
 return ans;
}
int main()
{
 memset(f,63,sizeof(f));
 cin>>n>>m>>k;
 for(int i=1;i<=n;i++)
  f[i][i]=0;
 for(int i=1;i<=m;i++)
 {
  cin>>e[i].u>>e[i].v>>e[i].w;
  f[e[i].u][e[i].v]=e[i].w;
 }
 for(int k=1;k<=n;k++)
  for(int i=1;i<=n;i++)
   for(int j=1;j<=n;j++)
    f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
 for(int k=1;k<=m;k++)
 {
  int u=e[k].u,v=e[k].v,w=e[k].w;
  for(int i=1;i<=n;i++)
   for(int j=1;j<=n;j++)
    a.a[i][j]=min(a.a[i][j],min(f[i][j],f[i][u]+f[v][j]-w));
 }
 if(k==0)cout<<f[1][n]<<endl;
 else cout<<fpow(a,k).a[1][n]<<endl;
 return 0;
}
```

---

## 作者：gznpp (赞：22)

这题思路本身其实没那么难，但是想出来真的有点难。

首先，定义任意两点之间至多使用一次魔法的最短路为 $f_{k, i, j}$。假设我们已经求出了任意两点之间 **至多** 使用一次魔法的最短路，即为 $f_{1, i, j}$， 后面再讲怎么求这个东西。

- Q: 窝为什么要求这个？
- A: $K$ 太大了，转移次数必须小于线性。考虑把它优化至矩阵乘法。

转移方程：$f_{k, i, j} = \min_{t \in [1, n]} f_{k - 1, i, t} + f_{1, t, j}$。

人话翻译：选择一个中转点 $t$，就像求最短路时一样，前面用 $k - 1$ 次魔法，后面用 $1$ 次魔法，这些路径当中求最小值。

- Q: 为什么限定后半段只能用一次？
- A: 这个转移是一个连续的过程，假如后半段用 $p$ 次魔法，那么你完全可以在后半段转移 $p$ 次之后再来更新全局答案。
- Q: 如果我有一段路不想用魔法呢？
- A: 如果允许使用魔法 ($K > 0$)，那么任意两点间最短路必须使用魔法，因为原边权都 $> 0$；还有，令 $t \in \{i, j\}$，也就相当于没转移。

然后发现一个惊奇的事情：如果把每个 $f_k$ 看成一个矩阵，那么一次转移就是 $f_1$ 的一次自乘，把矩阵乘法中的加号换成 $\min$。

- Q: 怎么证明这个可以快速幂呢？
- A: 只需证明 两个矩阵相乘，加号换成 $\min$ 这个新运算 满足结合律，即 $(A \operatorname{opt} B) \operatorname{opt} C = A \operatorname{opt} (B \operatorname{opt} C)$。无论怎么结合，答案矩阵里面每一个元素都是由 原来的三个矩阵中相同的那几个元素 取 $\min$ 得到的。

--------------

接下来求 $f_{1, i, j}$。

$f_{0, i, j}$ 肯定都会求吧，由于点数肥肠小，一遍 Floyd 完事。只需要管强制使用魔法的情况，两者取 $\min$ 就可以了。

强制使用魔法也很简单，枚举每一条边 $(a, b)$，强制它使用魔法，且任意两点之间都要通过这条边进行转移，取 $\min$。$f_{1, i, j} = \min(f_{0, i, j}, f_{0, i, a} + f_{0, b, j} - w_{i, j})$。

--------------

做完了。

代码其实不难写，一个 Floyd 板子，加上 $f_{1, i, j}$ 转移，再加上魔改过后的矩乘板子就搞完了。但是好多数组都要赋初值为正无穷，不要漏了，并且要特判 $K = 0$ 的情况。

Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 105, maxm = 2505;
int n, m, K;
int edge[maxn][maxn];
ll dis[maxn][maxn];
int u[maxm], v[maxm];
struct matrix {
    ll m[maxn][maxn];
} f, e;

matrix mul(matrix p, matrix q) {
    matrix c;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j)
        c.m[i][j] = 0x3f3f3f3f3f3f3f; // 注意，是取 min，初值要赋正无穷
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) for (int k = 1; k <= n; ++k)  
        c.m[i][j] = min(c.m[i][j], p.m[i][k] + q.m[k][j]);
    return c;
}
matrix pwr(matrix p, int q) {
    if (!q) return e;
    if (q == 1) return p;
    matrix ret = pwr(p, q >> 1);
    if (q & 1) return mul(mul(ret, p), ret);
    else return mul(ret, ret);
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m >> K;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) {
        if (i != j) edge[i][j] = 1e9 + 9;
        f.m[i][j] = 0x3f3f3f3f3f3f3f;
    }
    for (int i = 1; i <= n; ++i) e.m[i][i] = 1;
    for (int i = 1; i <= m; ++i) {
        int t; cin >> u[i] >> v[i] >> t;
        edge[u[i]][v[i]] = t;
    }

    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j)
        dis[i][j] = edge[i][j];
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j)
            dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]); // 三行 Floyd
    if (!K) return cout << dis[1][n] << endl, 0; // 特判
    for (int k = 1; k <= m; ++k) {
        ll t = edge[u[k]][v[k]];
        for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j)
            f.m[i][j] = min(f.m[i][j], min(dis[i][j], dis[i][u[k]] + dis[v[k]][j] - t)); // f[1][i][j] 转移
    }
    matrix ans = pwr(f, K);
    return cout << ans.m[1][n] << endl, 0;
}
```

---

## 作者：mulberror (赞：14)

这题其实考察了一个小$\mathrm {trick}$。  

这个$\mathrm {trick}$我第一次见到是在做 IOI2020 国家集训队作业的时候看到的，题号是[Codeforces 576D](http://blog.chhokmah.cn/index.php/archives/29/)

> 对于一个邻接矩阵$G$，那么$G^k$表示的就是**恰好**经过$k$后的状态。

举一个比较简单的例子：  

$G$是一个简单的$01$邻接矩阵，$G(i,j)$表示的就是在一步内$i\rightarrow j$的方案数，$0$即意味着两者之间没有连边，也意味着$1$步内有$0$种到达的方案，$1$也同理。然后再在这个邻接矩阵做$k$遍矩阵乘法后，得到的$G'$中$(i,j)$就是在**恰好**走了$k$步，从$i\rightarrow j$的方案数。

**这个其实就代替了做动态规划的必要**

因为这$k$步，每一步的本质相同，只是对应的状态不同，所以我们考虑重载矩阵乘法的定义，了解过动态 DP 的读者也可以类比动态 DP。

对应到这道题，我们首先计算出一步能够得到的状态，然后用相同的转移来做矩阵快速幂即可。

时间复杂度 $O(n^3Log_2 k)$

```cpp
#define int long long
const int N = 105;
const int M = 2505;
int n, m, kk;
struct Matrix {
  int a[N][N];
  int* operator[](int i) {
    return a[i];
  }
  Matrix operator*(Matrix oth) {
    Matrix res; 
    memset(res.a, 0x3f, sizeof res.a);
    For (k, 0, n - 1) {
      For (i, 0, n - 1) {
        For (j, 0, n - 1) {
          chkmin(res[i][j], a[i][k] + oth[k][j]);
        }
      }
    } 
    return res;
  }
  friend Matrix operator^(Matrix x, int idx) {
    Matrix res = x; 
    idx--;
    for (; idx; idx >>= 1, x = x * x) {
      if (idx & 1) {
        res = res * x;
      }
    }
    return res;
  }
};
struct Path {
  int u, v, t;
} path[M];
int g[N][N];
signed main() {
  memset(g, 0x3f, sizeof g);
  read(n), read(m), read(kk);
  For (i, 0, m - 1) {
    read(path[i].u), read(path[i].v), read(path[i].t);
    path[i].u--, path[i].v--;
    g[path[i].u][path[i].v] = path[i].t;
  }
  For (i, 0, n - 1) {
    g[i][i] = 0;
  }
  For (k, 0, n - 1) {
    For (i, 0, n - 1) {
      For (j, 0, n - 1) {
        chkmin(g[i][j], g[i][k] + g[k][j]);
      }
    }
  }
  Matrix base;
  memset(base.a, 0x3f, sizeof base.a);
  For (i, 0, n - 1) {
    base[i][i] = 0;
  }
  For (i, 0, m - 1) {
    int u = path[i].u, v = path[i].v, t = path[i].t;
    For (j, 0, n - 1) {
      For (k, 0, n - 1) {
        chkmin(base[j][k], g[j][u] - t + g[v][k]);
      }
    } 
  }
  if (kk) {
    writeln((base ^ kk)[0][n - 1]);
  } else {
    writeln(g[0][n - 1]);
  }
  return 0;
}
```

---

## 作者：I_am_Accepted (赞：13)

### Preface

「我**只用矩阵快速幂**过了哎！」

「赶快写题解去吧。」

### Analysis

提供一种更简短的**单源最短路**思路。

先说结论：

$$Ans=G_{n,1}\quad G=E^n(FE^n)^k$$

设 $d_i$ 表示当前节点 $1$ 到 $i$ 的最短路，初始

$$
\begin{bmatrix}d_1\\d_2\\\vdots\\d_n\end{bmatrix}=
\begin{bmatrix}0\\+\infty\\\vdots\\+\infty\end{bmatrix}
$$

于是我们类似 Bellman-Ford 算法做**松弛操作**，设松弛后的最短路为 $d_i'$，则

$$
E\cdot
\begin{bmatrix}d_1\\d_2\\\vdots\\d_n\end{bmatrix}=
\begin{bmatrix}d_1'\\d_2'\\\vdots\\d_n'\end{bmatrix}
$$

其中 $E=\begin{bmatrix}
e_{1,1}&e_{1,2}&\cdots&e_{1,n}
\\e_{2,1}&e_{2,2}&\cdots&e_{2,n}
\\\vdots&\vdots&\ddots&\vdots
\\e_{n,1}&e_{n,2}&\cdots&e_{n,n}
\end{bmatrix}$，若 $i\to j$ 有边则 $e_{i,j}$ 为该边边权，否则为 $e_{i,j}=(+\infty)[i\ne j]$。

$[A]$ 表示若条件 $A$ 为真则值为 $1$，否则为 $0$。

**注意这里的矩阵乘法 $AB=C$ 定义为 $C_{i,j}=\min\limits_{k=1}^nA_{i,k}+B_{k,j}$（与其他题解相同），易证其结合律。**

所以

$$
E^n\cdot\begin{bmatrix}d_1\\d_2\\\vdots\\d_n\end{bmatrix}
$$

相当于做了一次 Bellman-Ford 单源最短路。由于没有负权边，此时得到的 $d_i'$ 即为 $1\to i$ 的最短路。

然后有**魔法操作**，同样可以写成矩阵的形式

$$F=\begin{bmatrix}
f_{1,1}&f_{1,2}&\cdots&f_{1,n}
\\f_{2,1}&f_{2,2}&\cdots&f_{2,n}
\\\vdots&\vdots&\ddots&\vdots
\\f_{n,1}&f_{n,2}&\cdots&f_{n,n}
\end{bmatrix}$$

$$f_{i,j}=\begin{cases}+\infty&e_{i,j}=+\infty\\-e_{i,j}&e_{i,j}\ne+\infty\end{cases}$$

在 $k$ 次**魔法操作后都要松弛**，所以最终节点 $1$ 到每个节点的最短路

$$\begin{bmatrix}d_1'\\d_2'\\\vdots\\d_n'\end{bmatrix}=G\cdot
\begin{bmatrix}0\\+\infty\\\vdots\\+\infty\end{bmatrix}
$$

$$Ans=d_n'=\min_{i=1}^n\left(G_{n,i}+(+\infty)[i>1]\right)=G_{n,1}$$

使用矩阵快速幂，时间 $O(n^3\log k)$。

### Code

```cpp
//Said no more counting dollars. We'll be counting stars.
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define For(i,j,k) for(int i=j;i<=k;i++)
#define ckmn(a,b) a=min(a,b)
#define int long long
#define N 100

const int inf=1e17;
int n,m,k;
struct matrix{
	int m[N][N];
	void clear(){For(i,0,n-1) For(j,0,n-1) m[i][j]=inf;}//零矩阵 
	void init(){For(i,0,n-1) For(j,0,n-1) m[i][j]=(i==j?0:inf);}//单位阵 
	matrix mul(matrix x){//矩阵乘法 
		matrix res;res.clear();
		For(i,0,n-1) For(j,0,n-1) For(k,0,n-1) ckmn(res.m[i][j],m[i][k]+x.m[k][j]);
		return res;
	}
}rel,mag,ans;//rel:松弛矩阵 mag:魔法+松弛矩阵 
matrix kasumi(matrix x,int y){//快速幂 
	matrix res;res.init();
	while(y){
		if(y&1) res=res.mul(x);
		y>>=1;
		x=x.mul(x);
	}
	return res;
}
signed main(){IOS;
	cin>>n>>m>>k;
	rel.init();
	mag.init();
	int x,y,z;
	For(i,1,m){
		cin>>x>>y>>z;
		x--;y--;//矩阵中从 0 开始存 
		ckmn(rel.m[y][x],z);
		ckmn(mag.m[y][x],-z);
	}
	rel=kasumi(rel,n);
	mag=mag.mul(rel);
	mag=kasumi(mag,k);
	ans=rel.mul(mag);
	cout<<ans.m[n-1][0]<<endl;
return 0;}
```

---

## 作者：OMG_wc (赞：13)

 首先用 Floyd 算法求出两两之间最短路，然后在 $m$ 条边中枚举一条边修改，得到一个矩阵 $M$ 。其中 $M_{i,j}$ 表示从 $i$ 出发到 $j$ 最多修改 $1$ 次道路费用的最短路。

重新定义矩阵乘法 $C=A\times B$ 为 $C_{i,j}=\min\limits_k\{A_{i,k}+B_{k,j}\}$，在这种定义下，$M\times M$ 就是任意点到任意点最多修改两次道路费用的最短路。那么答案显而易见，求出 $M^k$ 即可。因为该运算满足结合律，所以可以用快速幂优化。

总时间复杂度为 $O(n^3+n^2m+n^3\log k)$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL INF = 1e18;

int sz;
struct Mat {
    LL a[100][100];
    Mat operator*(const Mat &T) const {
        Mat res;
        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < sz; j++) {
                res.a[i][j] = INF;
                for (int k = 0; k < sz; k++) {
                    res.a[i][j] = min(res.a[i][j], a[i][k] + T.a[k][j]);
                }
            }
        }
        return res;
    }
    Mat operator^(LL n) const {
        Mat res, x = *this;
        for (int i = 0; i < sz; i++)
            for (int j = 0; j < sz; j++) res.a[i][j] = i == j ? 0 : INF;
        while (n) {
            if (n & 1) res = res * x;
            x = x * x;
            n >>= 1;
        }
        return res;
    }
};


LL a[100][100];
struct Edge {
    int u, v, w;
} b[2505];
int main() {
    int n, m, kk;
    scanf("%d%d%d", &n, &m, &kk);
    sz = n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = i == j ? 0 : INF;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u--;
        v--;
        b[i] = {u, v, w};
        a[u][v] = w;
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
            }
        }
    }
    if (kk == 0) return printf("%lld\n", a[0][n - 1]), 0;
    Mat T;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            T.a[i][j] = a[i][j];  // 至多修改一条边
            for (int k = 0; k < m; k++) {
                T.a[i][j] = min(T.a[i][j], a[i][b[k].u] - b[k].w + a[b[k].v][j]);
            }
        }
    }
    T = T ^ kk;
    printf("%lld\n", T.a[0][n - 1]);
    return 0;
}
```


---

## 作者：Register (赞：9)

~~提高组爆炸选手来发题解了！~~

- 前置知识：矩阵乘法、快速幂

~~跟我一起读：矩阵乘（shéng）法，你不需要知道为什么这样读~~

观察数据范围， $k$ 是 $10^6$ ，太大了，复杂度里能不带 $k$ 吗？显然不行

继续观察，只带一个 $k$ ？经过思考，你会发现最快也只能是分层图最短路

或许只能是 $\sqrt{k}$ 或者 $\log k$ 了？前者你不知道怎么根号分治或者分块而后者你很容易想到矩阵快速幂加速，因为矩阵快速幂的一个经典例题就是“不超过 $k$ 步的路径数或最短路等”

不会那个例题的自己去百度（注意这里的矩阵乘法定义有改变，从 $\sum$ 变成了 $\min$ ）

考虑魔法次数是有限制的，而不进行魔法的次数是不用刻意限制的，设计状态 $F_{i,j}$ 为 $i$ 到 $j$ 至多使用魔法一次的最短路

这个状态满足结合律，矩阵 $F$ 的 $k$ 次幂恰好就是至多使用 $k$ 次魔法的最短路

现在考虑如何求出 $F$

根据 $n=100$ 这个特征，可以想到先用 $\texttt{Floyd}$ 求出两点之间的最短路

使用一次魔法，即改变了一条边，考虑枚举每一条边，将这条边施以魔法，令 $dis_{i,j}$ 为 $i$ 到 $j$ 最短路， $val_{u,v}$ 为边 $(u,v)$ 的长度，则 $F_{i,j}=\min\left\{F_{i,j},dis_{i,u}+dis_{v,j}-val_{u,v}\right\}$ 

时间复杂度： $O(N^3+N^2M+N^3\log K)$ （跑最短路+计算 $F$ +矩阵快速幂）

代码就不贴了，没法测怕有锅~~出来丢脸~~

---

## 作者：wsyhb (赞：8)

## 前言

其实其他题解讲得很清楚了，这篇题解主要是想**讲一下如何把矩阵快速幂的初始化的时间复杂度由 $O(n^2m)$ 优化到 $O(nm)$，同时加深大家对矩阵乘法的理解**。

## 题解

还是先简单说一下题目解法：

首先要最优，显然 $k$ 次魔法要用完。（即使只剩下 $1$ 次魔法，你选一条边走出去又走回来，答案不会更差）

所以我们只需将 $k$ 段**恰好使用 $1$ 次魔法**的路径拼起来。

由于 $k \le 10^6$ 稍微有点大，但 $n \le 100$，于是 Floyd 预处理两点间距离，进一步预处理出任意两点之间恰好使用 $1$ 次魔法的最小代价，再上一个 $O(n^3 \log{k})$ 的广义矩阵快速幂即可解决。

P.S. 所谓的广义矩阵乘法，就是把普通矩阵乘法中求和（$\Sigma$）换成求最值（$\max$ 或 $\min$），乘法（$\times$）换成加法（$+$）。易证其满足普通矩阵乘法的运算律。

------------

考虑矩阵乘法应用在类似图论问题中的本质，发现就是信息的合并—— $1$ 条边的方案和另外一个 $1$ 条边的方案组合成 $2$ 条边的方案，$2$ 条边的方案又和另外一个 $2$ 条边的方案组合成 $4$ 条边的方案，以此类推。（说大白话就差不多是上面的第三段内容）

于是我们只需将 $1$ 个**不使用任何魔法**的方案，和 $k$ 个**一开始就使用一次魔法**的方案顺次拼起来即可。（如下图所示）

![](https://cdn.luogu.com.cn/upload/image_hosting/04ado98u.png)

说明：将 $1$ 到 $n$ 的（可经过重复点的）路径抽象为一条水平线，用红色和黑色分别表示使用/不使用魔法。

因此，对于每条边 $(u,v)$，我们**只需更新以 $u$ 或 $v$ 出发的方案**即可。该部分时间复杂度由 $O(n^2m)$ 降为 $O(nm)$，跑得飞快。

## 代码

``` cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
const int max_n=100+5;
const int max_m=2500+5;
int u[max_m],v[max_m],t[max_m];
long long dis[max_n][max_n],d[max_n][max_n];
const long long inf=1e18;
struct Matrix
{
	long long v[max_n][max_n];
}A,ans;
inline Matrix operator * (const Matrix &a,const Matrix &b)
{
	static Matrix res;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
		{
			res.v[i][j]=inf;
			for(int k=1;k<=n;++k)
				res.v[i][j]=min(res.v[i][j],a.v[i][k]+b.v[k][j]);
		}
	return res;
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			dis[i][j]=d[i][j]=(i==j?0:inf);
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d%d",u+i,v+i,t+i);
		dis[u[i]][v[i]]=t[i];
	}
	for(int k=1;k<=n;++k)
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			ans.v[i][j]=dis[i][j];
	for(int k=1;k<=m;++k)
		for(int i=1;i<=n;++i)
			d[u[k]][i]=min(d[u[k]][i],-t[k]+dis[v[k]][i]);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			A.v[i][j]=d[i][j];
	while(k)
	{
		if(k&1)
			ans=ans*A;
		A=A*A;
		k>>=1;
	}
	printf("%lld\n",ans.v[1][n]);
	return 0;
}
```

---

## 作者：GCC_ (赞：5)

GCC_发布的题解

这一题，我其实也是做了差不多三天才做出来的

首先，我们先读懂题：给你一个有向图，每一条边有一个对应的权值，然后你可以施展k次魔法，把某一条边的权值变为**相反值**。求1到n的最短路径。

### 这一题，我们可以先实现超时的代码，再去推AC代码。
题表面看是一道dp，但其实本质上需要对最短路的Floyd有着深刻的了解，我们首先可以发现，如果k为0，那么这其实就是一道最短路的题，问题就是在于怎么去处理这k条边。 与Floyd相同，我们设f[i][j][s]表示从i走到j，最多用了s次机会，所要的最小代价，那么我们考虑怎么转移，跟Floyd相同，我们枚举一个k做为中转点，并假设i到k的路上最多用了s-1次机会，那么k到j的路上最多用了1次机会，这样就跟Floyd的转移基本一致，但问题是这样为何是对的，其实我们从这个中转点k的不确定性就可以看出，我们一定能找到一个k，使得i到k之间最多用了s-1次机会，这样这题我们90分就有了。

### 然后，我们想想怎么优化
没错，就是**倍增思想**

我们发现，k太大时，时间和空间都会爆，于是猜想：

设f[i][j][s]代表从i走到j，最多用了**2^s**次机会，所要的最小代价。那么，我们既然可以推出f[i][j][1]，那么就可以依次推出s=2,4,8,16,32,64等等。

那么，转移式就为f[i][j][s]=min(f[i][j][s],f[i][r][s-1]+f[r][j][s-1])，r表示一个中转点。

然后，我们想想如何弄出不是2的几次方的数。例如k=37时

他的二进制为0100101，分别是第0,2,5位，那我们可以推出，f[i][j][t]=min(f[i][j][t],f[i][r][0]+f[r][j][2])，t代表某一个数，F[i][j][t’]=min(f[i][k][t]+f[k][j][5])，t'也是代表某一个数，那么f[1][n][t']就是答案。

代码（勿抄）：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long dis[105][105][505]={},u[2505]={},v[2505]={},w[2505]={},ds[105][105][505]={},sum[1005]={};
int n,m,k;
long long min(long long x,long long y)
{
	return (x<y?x:y);
}
int Read()
{
	int f=1,u,s=0;
	char ch=getchar();
	while(!(ch>='0'&&ch<='9')){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){u=ch-'0';s*=10;s+=u;ch=getchar();}
	return s*f;
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	int pk=0,kk=k;
	while(kk)
	{
		pk++;
		kk/=2;
	}
	for(int i=0;i<=n;i++)
	{
		for(int j=0;j<=n;j++)
		{
			if(i!=j)
			{
				for(int t=0;t<=pk;t++)
				{
					dis[i][j][t]=9999999999999999;
					ds[i][j][t]=9999999999999999;
				}
			}
		}
	}
	for(int i=1;i<=m;i++)
	{
		u[i]=Read(),v[i]=Read(),w[i]=Read();
		dis[u[i]][v[i]][0]=w[i];
		ds[u[i]][v[i]][0]=w[i];
	}
	for(int r=1;r<=n;r++)
	{
		for(int i=1;i<=n;i++)
		{
			if(r!=i)
			{
				for(int j=1;j<=n;j++)
				{
					if(i!=j&&r!=j)
					{
						if(ds[i][r][0]+ds[r][j][0]<ds[i][j][0])
						{
							ds[i][j][0]=ds[i][r][0]+ds[r][j][0];
						}
					}
				}
			}
		}
	}
	if(!k)
	{
		printf("%lld\n",ds[1][n][0]);
		return 0;
	}
	for(int o=1;o<=m;o++)
	{
		long long r1=u[o],r2=v[o],r3=w[o];
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				long long a=(ds[i][j][0]<ds[i][r1][0]+ds[r2][j][0]-r3?ds[i][j][0]:ds[i][r1][0]+ds[r2][j][0]-r3);
				if(a<dis[i][j][0])
				{
					dis[i][j][0]=a;
				}
			}
		}
	}
	for(int s=1;s<=pk;s++)
	{
		for(int r=1;r<=n;r++)
		{
			for(int i=1;i<=n;i++)
			{
				for(int j=1;j<=n;j++)
				{
					if(dis[i][r][s-1]+dis[r][j][s-1]<dis[i][j][s])
					{
						dis[i][j][s]=dis[i][r][s-1]+dis[r][j][s-1];
					}
				}
			}
		}
	}
	for(long long sr=1,sR=0;sr<=k;sr*=2,sR++)
	{
		if(k&sr)
		{
			sum[++sum[0]]=sR;
		}
	}
	if(sum[0]==1)
	{
		printf("%lld\n",dis[1][n][sum[1]]);
	}
	else
	{
		for(int r=1;r<=n;r++)
		{
			for(int i=1;i<=n;i++)
			{
				for(int j=1;j<=n;j++)
				{
					if(dis[i][r][sum[1]]+dis[r][j][sum[2]]<ds[i][j][1])
					{
						ds[i][j][1]=dis[i][r][sum[1]]+dis[r][j][sum[2]];
					}
				}
			}
		}
		for(int js=3;js<=sum[0];js++)
		{
			for(int r=1;r<=n;r++)
			{
				for(int i=1;i<=n;i++)
				{
					for(int j=1;j<=n;j++)
					{
						if(ds[i][r][js-2]+dis[r][j][sum[js]]<ds[i][j][js-1])//min函数时间超限
						{
							ds[i][j][js-1]=ds[i][r][js-2]+dis[r][j][sum[js]];
						}
					}
				}
			}
		}
		printf("%lld\n",ds[1][n][sum[0]-1]);
	}
	return 0;
}

```

### 此题解是为了大家方便理解 ~~没有什么结构体等的方法~~ ，所以不要抄袭

---

