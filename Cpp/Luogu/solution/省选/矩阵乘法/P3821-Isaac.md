# Isaac

## 题目背景

居润国迷上了一款游戏《以撒的结合重生》。他已经打到了最后一关，这一关有特殊的走位技巧。

1. 居润国从时刻 $0$ 开始，要控制以撒从起点走到终点。

2. 居润国只能在第 $k$ 时刻恰好走到终点。（从一个房间走到另一个房间居润国需要花费一个单位时间，居润国手速快，不会在同一个房间停留，以撒可以在这些房间中来回走动）

3. 若房间 $u$ 和 $v$ 相连，则居润国能控制以撒通过这两个房间的通道当且仅当以撒的血量大于等于 $f(u, v)$

4. 在这些房间之间有一堆怪物在游走。

5. 居润国为了求稳，于是上网找到了一个解码器，在代码中发现这些怪物们游走的房间有固定的规律：怪物每次都会从一个房间移动到另一个房间（也需花费一个单位时间），且他们总是在几个固定的房间按照固定的顺序内游走，游走的房间个数为 $T$。

为了不在玩游戏时失误，居润国希望能够避开所有的怪物走到终点，即无伤通过最后一关，同时希望你找到居润国控制的以撒完成这个任务至少需要的血量。对编程一窍不通的他找到了你，希望寻求解决。如果要是你无法解决，那么就光明正大地告诉他： `'IMP0SSBLE!!'` 他一定不会打死你的。

## 题目描述

求居润国是否能在上述条件要求下无伤通过最后一关。如果可以，输出居润国控制的以撒最少所需的血量 $B$，否则输出 `'IMP0SSBLE!!'` 


## 说明/提示

共 $20$ 组数据。

对于 $15\%$ 的数据，$a = 0$，$k \leq 20$。

对于 $25\%$ 的数据，$a \leq 3$，$k \leq 1500$。

对于 $50\%$ 的数据，$a \leq 3$，$k \leq 10^4$。

对于 $70\%$ 的数据，$a \leq 20$，$k \leq 10^6$。

对于 $85\%$ 的数据，$a \leq 30$，$k \leq 10^8$。

对于 $100\%$ 的数据，$a \leq 30$，$k \leq 2*10^9$，$2 \leq T \leq 4$，$n \leq 50$，$m \leq 1250$。

所有输入皆在 int 范围内。

所有数据皆大于零，**可能会有重边，若一条边输入多次 则以最后一次出现的权值为准。**

## 样例 #1

### 输入

```
2 1 1 2 1
1 2 1
0
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 1 1 2 1
1 2 2
0
```

### 输出

```
2```

## 样例 #3

### 输入

```
2 1 1 2 10000001
1 2 2
0
```

### 输出

```
2```

## 样例 #4

### 输入

```
2 1 1 2 10000001
1 2 2
1
2
2 1
```

### 输出

```
2```

# 题解

## 作者：littleKtian (赞：6)

~~话说我刚开始写时还是紫题怎么写到一半就黑了~~

言归正传，设$f[t][i][j]$为$t$时刻从$i$到$j$的路径中最长边的最小值，$l[i][j]$表示房间$i$到房间$j$的通道长度（之间没有通道就算作无限大）

可以得到递推式$f[t][i][j]=min(max(f[t-1][i][u],l[u][j])|1<=u<=n)$，特别的，$f[1][i][j]=l[i][j]$，$f[k][s][t]$即为答案

因为满足结合律，所以用矩阵来优化

至于怪物的情况可以用和[这题](https://www.luogu.org/problem/P2579)类似的方法处理，把12个时刻作为一个轮回，对于每一个时刻建立一个邻接矩阵$bzjx$，若$T(1<=T<=12)$时刻房间$j$有怪物，则$bzjx[T][i][j]=$无限大，并计算前$T$个$bzjx$运算的结果，用$jx[T]$储存

设$k=p*12+q$，计算${(jx[12])}^{p}*jx[q]$($p$为0则$jx[q]即为答案$，$q$为0则直接计算${(jx[12])}^{p}$)

注意不存在路径时输出'IMP0SSBLE!!'（要输出引号且中间O为0）

时间复杂度大概$O(n^{3}logk)$~~(反正能过管那么多干嘛)~~

代码就凑合着看吧
```
#include<bits/stdc++.h>
using namespace std;
const int N=50;
const int M=12;
const long long oo=2e10;
long long bzjx[M+1][N+1][N+1],jx[M+1][N+1][N+1];
long long ans[N+1][N+1],b[N+1][N+1],l[N+1][N+1],ll[N+1][N+1];
int n,m,s,t,k,a;
void POW(int x)//矩阵
{
	if(x==1){memcpy(b,jx[M],sizeof(jx[M]));return;}
	POW(x>>1);
	memcpy(l,b,sizeof(b));
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=n;j++)
	    b[i][j]=oo;
	if(x&1)
	{
		for(int i=1;i<=n;i++)
		  for(int j=1;j<=n;j++)
		    ll[i][j]=oo;
		for(int i=1;i<=n;i++)
		  for(int j=1;j<=n;j++)
		    for(int p=1;p<=n;p++)
		      ll[i][j]=min(ll[i][j],max(l[i][p],l[p][j]));
		for(int i=1;i<=n;i++)
		  for(int j=1;j<=n;j++)
		    for(int p=1;p<=n;p++)
		      b[i][j]=min(b[i][j],max(ll[i][p],jx[M][p][j]));
	}
	else
	{
		for(int i=1;i<=n;i++)
		  for(int j=1;j<=n;j++)
		    for(int p=1;p<=n;p++)
		      b[i][j]=min(b[i][j],max(l[i][p],l[p][j]));
	}
}
int main()
{
	scanf("%d%d%d%d%d",&n,&m,&s,&t,&k);
	for(int i=1;i<=M;i++)
	  for(int j=1;j<=n;j++)
	    for(int p=1;p<=n;p++)
	      jx[i][j][p]=bzjx[i][j][p]=oo;
	while(m--)//初始化矩阵
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		for(int i=1;i<=M;i++)bzjx[i][u][v]=bzjx[i][v][u]=(long long)w;
	}
	scanf("%d",&a);
	while(a--)//处理有怪物的情况
	{
		int T;
		scanf("%d",&T);
		int ro[4];
		for(int i=0;i<T;i++)scanf("%d",ro+i);
		for(int i=1;i<=M;i++)
		  for(int j=1;j<=n;j++)
		    bzjx[i][j][ro[i%T]]=oo;
	}
	memcpy(jx[1],bzjx[1],sizeof(bzjx[1]));
	for(int i=2;i<=M;i++)
	  for(int j=1;j<=n;j++)
	    for(int p=1;p<=n;p++)
	      for(int l=1;l<=n;l++)
	        jx[i][j][p]=min(jx[i][j][p],max(jx[i-1][j][l],bzjx[i][l][p]));
	if(k/M)
	{
		POW(k/M);
		int r=k%M;
		if(r)
		{
			for(int i=1;i<=n;i++)
			  for(int j=1;j<=n;j++)
			    ans[i][j]=oo;
			for(int i=1;i<=n;i++)
			  for(int j=1;j<=n;j++)
			    for(int p=1;p<=n;p++)
				  ans[i][j]=min(ans[i][j],max(b[i][p],jx[r][p][j]));
		}//有余数，所得结果再和jx[r]进行运算得到答案
		else memcpy(ans,b,sizeof(b));//刚好除尽，将矩阵快速冥后的结果直接复制
	}
	else memcpy(ans,jx[k],sizeof(jx[k]));//不足12，直接复制
	if(ans[s][t]==oo)printf("'IMP0SSBLE!!'");
	else printf("%lld",ans[s][t]);
}
```
可能讲的不是很清楚请见谅，毕竟蒟蒻语文不好

---

## 作者：Gu_Pigeon (赞：5)

 _**关键词：二分答案，矩阵快速幂**_ 

# 这是一道比较套路的题目
如果想更容易理解这题，可以先去看 [P1948 Telephone Lines](https://www.luogu.org/problem/P1948) 和 [P2579 沼泽鳄鱼](https://www.luogu.org/problem/P2579) 两道题

然后你就会发现：

~~把上面两题加起来就好了~~

## 具体实现：

1. 二分其血量，将 边权≤血量 的边设为1，其他设为0，得到一个邻接矩阵；

2. 建完邻接矩阵后，可以想到通过矩阵快速幂求出固定步数能到达的点

3. 如果可以到达，这说明是可以在当前血量下从起点到达终点的，否则不能，更新左右端点。

（参考国家集训队论文：俞华程《矩阵乘法在信息学中的应用》）

### BUT还有一个问题！

怪物的位置会随时间变化，导致不同时间的矩阵是不一样的，那么矩阵快速幂就无法直接使用。

此时我们发现，怪物的周期T在2到4之间，由此可以看出……

对于周期为2的怪物，2单位之间后将重新回到原样；

对于周期为3的怪物，3单位之间后将重新回到原样；

对于周期为4的怪物，4单位之间后将重新回到原样；

~~这不废话吗~~

#### **重点在下面！**

在 lcm(2,3,4)=12 单位时间后，邻接矩阵将回到原样！！！

~~喵啊喵~~

因此：

- 处理出 
`tmp = map[1] * map[2] * map[3] * …… * map[11] * map[0] `
这个重复出现的矩阵

(**注意：矩阵乘法不满足交换律，所以不能改变顺序！**)

- 求出tmp^(k / 12) 的值，将余下的map[1] ~ map[(k % 12)]
乘上去，就得到了最终答案！

完了？完了。

## 时空复杂度分析：

二分答案：log(W) 虽然没有边权的范围，但是因为一定在int之内，所以这不成问题:-D

矩阵乘法：n^3 

矩阵快速幂：log(k)

时间复杂度总和：O(n^3 * log(K) * log(W)),跑得飞快

空间复杂度：O(n^2) ~~就是个矩阵嘛~~

### （伪）总结：
就这样，这道题就被切了……吗？

# 请注意！请注意！请注意！

~~本题最难的地方~~

1.无解时，输出的是IMP **0** SSBLE 而非 IMP **O** SSBLE

2.IMP0SSIBLE两边的 **感叹号 和 单引号 都不能去掉！！！**

~~（我就这样被坑了）~~

最后，上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

long long n, m, s, e, k, nfish;

struct mat
{
	long long a[51][51]; //邻接矩阵
	void unit() //构造单位矩阵
	{
		memset(a, 0, sizeof(a));
		for (long long i = 1; i <= n; i++) a[i][i] = 1;
	}
	mat operator *(const mat &b) const //矩阵乘法
	{
		mat c; memset(c.a, 0, sizeof(c.a));
		for (long long i = 1; i <= n; i++)
			for (long long k = 1; k <= n; k++)
				for (long long j = 1; j <= n; j++)
					c.a[i][j] |= a[i][k] & b.a[k][j];//只需知道两点之间是否联通，因此使用位运算
		return c;
	}
	mat operator ^(const long long &b) const //矩阵快速幂
	{
		mat t, res;
		res.unit();
		t = *this;
		long long qwq = b;
		while (qwq)
		{
			if (qwq & 1) res = res * t;
			t = t * t;
			qwq >>= 1;
		}
		return res;
	}
} tmp, ans, qaq[12], mp;

signed main()
{
	scanf("%lld%lld%lld%lld%lld", &n, &m, &s, &e, &k);
	for (long long i = 1; i <= m; i++)
	{
		long long x, y, z;
		scanf("%lld%lld%lld", &x, &y, &z);
		mp.a[x][y] = mp.a[y][x] = z;
	}
	for (long long i = 0; i < 12; i++) qaq[i] = mp;
	scanf("%lld", &nfish);
	for (long long i = 1; i <= nfish; i++)
	{
		long long t;
		scanf("%lld", &t);
		for (long long j = 0; j < t; j++)
		{
			long long x;
			scanf("%lld", &x);
			for (long long k = j; k < 12; k += t)
				for (long long o = 1; o <= n; o++)
					qaq[k].a[o][x] = 0; //得出在怪物影响下的图
		}
	}	
	long long l = -1, r = 1ll << 60;
	while (l + 1 < r) //二分答案
	{
		long long mid = (l + r) >> 1;
		tmp.unit();
		mat ouo[12]; 
		for (long long i = 0; i <= 11; i++) ouo[i] = qaq[i];
		for (long long i = 0; i < 12; i++)
			for (long long j = 1; j <= n; j++)
			 	for (long long l = 1; l <= n; l++) if (ouo[i].a[j][l]) ouo[i].a[j][l] = ouo[i].a[j][l] <= mid;
		for (long long i = 1; i < 12; i++) tmp = tmp * ouo[i];//12个单位时间为一组，处理tmp
		tmp = tmp * ouo[0];
		long long cnt = (k / 12);
		ans.unit();
		ans = ans * (tmp ^ cnt);
		for (long long i = 1; i <= k % 12; i++) ans = ans * ouo[i];//将余下的也乘上去
		if (ans.a[s][e]) r = mid; else l = mid; //判断是否能够到达
	}
	if (l > 1ll << 30) puts("'IMP0SSBLE!!'"); //无解情况
		else printf("%lld", r);
}
```
求过，求赞QwQ

---

## 作者：BDFZ_hym_AK_hym_ing (赞：4)

~~第一篇紫题题解欸！~~  
### 题目解~~毒~~：
1. 一共有 $k$ 次操作，要求从点 $s$ 开始，经过 $k$ 次操作后正好到达点 $t$。
2. 每次操作必须前往下一秒没有怪物的房间，且自身血量大于等于这条道路所需的血量。
3. 求出最小所需血量，即在所有能从 $s$ 走到 $t$ 的路径中，找出路径最大边权的最小值。
4. （接下来为**坑点**）以撒与怪物出生在同一个房间，以撒不会受伤。
5. 怪物第 $0$ 秒在输入的第一个数。
6. `'IMP0SSBLE!!'`有引号和 $0$，最好直接复制进去。
### 做法分析
注意到数据范围中 $k$ 较大， 而 $n$ 只有 $50$，那么就可以直接使用**矩阵快速幂**（不会的[来这学](https://oi-wiki.org/math/linear-algebra/matrix/)）了（吗？）。 

由于这里求的是路径最大边权的最小值，而不是以前的路径数量，所以要把 $+,\times$ 矩阵换成 $\min,\max$ 矩阵。  
即做矩阵乘法中的内层与外层，枚举 $i$ 到 $j$ 的中间点 $k$，在找到最小的路径最大边权，而 $i$ 到 $j$ 的最大边权可以取 $i$ 到 $k$ 和 $k$ 到 $j$ 路径最大边权的较大值，所以使用 $\min,\max$ 矩阵。 

所以可以使用邻接矩阵，不能通过的地方直接赋值为正无穷。  
但是本题还有一个怪物的条件（与[P2579 沼泽鳄鱼](https://www.luogu.com.cn/problem/P2579)中的食人鱼类似），再次注意到 $T$，的范围极小，仅为 $2\le T \le4$，所以以 $\operatorname{lcm}(2,3,4)=12$ 为一循环。将 $k$ 拆为 $12\times p+q$，则只需计算出 $(cs_{12})^{p}+cs_{q}$,若 $q$ 为 $0$，则直接计算 $(cs_{12})^{p}$。  

预计复杂度 $O(n^3\log k)$。
### 代码：
码前提示：抄题一时爽，棕名两行泪。  
#### 纯享版：
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long inf=0x3f3f3f3f3f3f3f3f;
struct jz{
	long long x,y;
	long long f[105][105];
	jz(){
		memset(f,0x3f,sizeof(f));
	}
	void mn(){
		memset(f,0x3f,sizeof(f));
		long long i;
		for(i=1;i<=x;i++)
		{
			f[i][i]=0;
		}
	}
};
jz mult(jz a,jz b){
	jz c;
	c.x=a.x;
	c.y=b.y;
	long long i,j,k;
	for(i=1;i<=a.x;i++)
	{
		for(k=1;k<=b.y;k++)
		{
			for(j=1;j<=a.y;j++)
			{
				c.f[i][k]=min(c.f[i][k],max(a.f[i][j],b.f[j][k]));
			}
		}
	}
	return c;
}
jz qpower(jz a,long long b){
	jz c;
	c.x=a.x;
	c.y=a.y;
	c.mn();
	while(b)
	{
		if(b&1)
		{
			c=mult(c,a);
		}
		a=mult(a,a);
		b>>=1;
	}
	return c;
}
long long n,m,s,t,k,a;
jz cs[15];
long long gw[15];
int main(){
	
	ios::sync_with_stdio(false);
	cin.tie();
	cout.tie();
	cin>>n>>m>>s>>t>>k;
	long long i,j;
	for(i=1;i<=12;i++)
	{
		cs[i].x=cs[i].y=n;
	}
	for(i=1;i<=m;i++)
	{
		long long u,v,w;
		cin>>u>>v>>w;
		for(j=1;j<=12;j++)
		{
			cs[j].f[u][v]=cs[j].f[v][u]=w;
		}
	}
	cin>>a;
	while(a--)
	{
		long long T;
		cin>>T;
		for(i=0;i<T;i++)
		{
			cin>>gw[i];
		}
		for(i=1;i<=12;i++)
		{
			for(j=1;j<=n;j++)
			{
				cs[i].f[j][gw[i%T]]=inf;
			}
		}
	}
	for(i=2;i<=12;i++)
	{
		cs[i]=mult(cs[i-1],cs[i]);
	}
	cs[12]=qpower(cs[12],k/12);
	if(k%12)
	{
		cs[12]=mult(cs[12],cs[k%12]);
	}
	if(cs[12].f[s][t]==inf)
	{
		cout<<"\'IMP0SSBLE!!\'";
		return 0;
	}
	cout<<cs[12].f[s][t];
	
	return 0;
}
```
#### 注释版：

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long inf=0x3f3f3f3f3f3f3f3f;
struct jz{
	long long x,y;
	long long f[105][105];
	jz(){
		memset(f,0x3f,sizeof(f));
	}
	void mn(){//这里是将矩阵初始化，即花费代价0从自己到自己，相当于没走 
		memset(f,0x3f,sizeof(f));
		long long i;
		for(i=1;i<=x;i++)
		{
			f[i][i]=0;
		}
	}
};
jz mult(jz a,jz b){//乘法模板
	jz c;
	c.x=a.x;
	c.y=b.y;
	long long i,j,k;
	for(i=1;i<=a.x;i++)
	{
		for(k=1;k<=b.y;k++)
		{
			for(j=1;j<=a.y;j++)
			{
				c.f[i][k]=min(c.f[i][k],max(a.f[i][j],b.f[j][k]));
			}
		}
	}
	return c;
}
jz qpower(jz a,long long b){//快速幂模板
	jz c;
	c.x=a.x;
	c.y=a.y;
	c.mn();
	while(b)
	{
		if(b&1)
		{
			c=mult(c,a);
		}
		a=mult(a,a);
		b>>=1;
	}
	return c;
}
long long n,m,s,t,k,a;
jz cs[15];
long long gw[15];
int main(){
	
	ios::sync_with_stdio(false);
	cin.tie();
	cout.tie();
	cin>>n>>m>>s>>t>>k;
	long long i,j;
	for(i=1;i<=12;i++)
	{
		cs[i].x=cs[i].y=n;
	}
	for(i=1;i<=m;i++)
	{
		long long u,v,w;
		cin>>u>>v>>w;
		for(j=1;j<=12;j++)
		{
			cs[j].f[u][v]=cs[j].f[v][u]=w;
		}
	}
	cin>>a;
	while(a--)
	{
		long long T;
		cin>>T;
		for(i=0;i<T;i++)
		{
			cin>>gw[i];
		}
		for(i=1;i<=12;i++)
		{
			for(j=1;j<=n;j++)//让所有到怪物所在点的边暂时断开 
			{
				cs[i].f[j][gw[i%T]]=inf;
			}
		}
	}
	for(i=2;i<=12;i++)
	{
		cs[i]=mult(cs[i-1],cs[i]);
	}
	cs[12]=qpower(cs[12],k/12);
	if(k%12)//没有定义cs[0]，所以这里特判 
	{
		cs[12]=mult(cs[12],cs[k%12]);
	}
	if(cs[12].f[s][t]==inf)
	{
		cout<<"\'IMP0SSBLE!!\'";
		return 0;
	}
	cout<<cs[12].f[s][t];
	
	return 0;
}
```

---

## 作者：_Kenma_ (赞：0)

# P3821 解题报告

## 前言

CSP 考炸了啊。

开始写水题自我麻痹了。

## 思路分析

首先套一个二分的壳子，二分最小生命值，如果一条边的边权小于当前二分值就可以连边。

问题在于怎样 check。

定长路径是经典矩阵乘法题。考虑使用广义矩阵乘法，$A_{i,j}$ 表示点 $i$ 和点 $j$ 的连通性，发现转移具有结合律，可以直接矩阵快速幂优化。具体转移可以参考代码。

考虑怎样处理在某些时刻某些点不能走的问题。

发现怪物游走的周期至多为 $12$，考虑将这 $12$ 个邻接矩阵都处理出来，然后整周期使用矩阵快速幂，零散部分直接乘。

发现做完了。总体复杂度 $O(n^3\log k\log v)$。

有一些细节。

## 代码实现

细节：

1. 时刻从 $0$ 开始；

2. 在给初始的 $12$ 个矩阵赋值时，注意只删去别的点到有怪物的点的边，不删除有怪物的点到别的点的边；

3. 输出无解要带引号。

```cpp

#include<bits/stdc++.h>
#define int long long
using namespace std;
const int inf=2e9+1;
int n,m,s,t,k,x,y,ans,a,num[1255],p[1255][5],h[51][51];
struct node{
	bool h[51][51];
	node(){
		memset(h,0,sizeof(h));
	}
	node operator *(const node &a)const{
		node ans;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				for(int t=1;t<=n;t++){
					ans.h[i][j]|=h[i][t]&a.h[t][j];
				}
			}
		}
		return ans;
	}
}b[14],c;
node binpow(node a,int b){
	if(b==0) return c;
	node res=binpow(a,b/2);
	if(b&1) return (res*res)*a;
	else return res*res; 
}
bool check(int mid){
	memset(b,0,sizeof(b));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(h[i][j]<=mid) b[0].h[i][j]=1;
		}
	}
	for(int i=1;i<=12;i++){
		b[i]=b[0];
	}
	for(int i=1;i<=a;i++){
		for(int j=1;j<=12;j++){
			for(int k=1;k<=n;k++){
				b[j].h[k][p[i][j%num[i]+1]]=0;
			}
		}
	}
	b[13]=c;
	for(int i=1;i<=12;i++){
		b[13]=b[13]*b[i];
	}
	b[13]=binpow(b[13],k/12);
	for(int i=1;i<=k%12;i++){
		b[13]=b[13]*b[i];
	}
	return b[13].h[s][t];
}
int find(int l,int r){
	if(l==r) return l;
	int mid=(l+r)>>1;
	if(check(mid)) return find(l,mid);
	else return find(mid+1,r); 
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>s>>t>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			h[i][j]=inf;
		}
	}
	for(int i=1;i<=n;i++){
		c.h[i][i]=1;
	}
	for(int i=1;i<=m;i++){
		cin>>x>>y;
		cin>>h[x][y];
		h[y][x]=h[x][y];
	}
	cin>>a;
	for(int i=1;i<=a;i++){
		cin>>num[i];
		for(int j=1;j<=num[i];j++){
			cin>>p[i][j]; 
		} 
	}
	ans=find(1,inf);
	if(ans==inf) cout<<"'IMP0SSBLE!!'";
	else cout<<ans;
	return 0; 
}

```

## 后记

要是 T3 放这个，是不是我能考的好一点？

NOIP2024 祝好。

---

## 作者：OldDriverTree (赞：0)

怎么又一发抢到了最优解啊/jk。

# Solution
考虑二分答案 $x$，那么就只有边权 $\le x$ 的可以通过。

~~这样就转化成了 [P2579 [ZJOI2005] 沼泽鳄鱼](https://www.luogu.com.cn/problem/P2579)，做完了~~。

求恰好走 $k$ 步是否能到达，这个显然就是矩阵加速。

但是每走一条边怪兽的位置都会发生变化，考虑怎么处理这个东西。

可以发现所有怪兽的位置只和当前时间 $\bmod 12$ 的值有关。

那么考虑建出 $12$ 张图，编号为 $0$ 到 $11$，编号为 $i$ 的图表示当前时间 $\bmod 12=i$ 时能经过的边构成的图。

这个就在原图的基础上，去掉终点是怪兽的位置的边。

设 $g_i$ 表示编号为 $i$ 的图构成的矩阵。

答案就为 $\prod\limits_{i=0}^{k-1} g_{i\bmod12}$，每 $12$ 个分成一组，这个式子就等于 $(\prod\limits_{i=0}^{11} g_i)^{\lfloor\frac k{12}\rfloor}\times\prod\limits_{i=0}^{k\bmod 12} g_i$，快速幂处理即可。

时间复杂度为 $O(n^3\log k\log m)$，把矩阵第二维压成一个 `long long` 可以做到 $O(n^2\log k\log m)$。

# Code
```c++
#include<bits/stdc++.h>
using namespace std;
const int N=50;
int n,m,S,T,k,s;
vector<int> a[30];
int G[N][N];

int read() {
	int x=0; char c=0; while (!isdigit(c) ) c=getchar();
	while (isdigit(c) ) x=(x<<3)+(x<<1)+(c&15),c=getchar();
	return x;
}
struct Matrix
{
	long long a[N];
	Matrix() { memset(a,0,sizeof a); }
	void I() { for (int i=0;i<n;i++) a[i]=1ll<<i; }
	Matrix friend operator *(Matrix a,Matrix b)
	{
		Matrix c;
		for (int i=0;i<n;i++)
			for (int k=0;k<n;k++)
				if (a.a[i]>>k&1) c.a[i]|=b.a[k];
		return c;
	}
};
struct edge {
	int x,y,z;
	bool operator <(edge o)const {
		return z<o.z;
	}
}e[1250];

bool check(int x)
{
	Matrix g[12],base,ans;
	for (int i=0;i<=x;i++) {
		for (int j=0;j<12;j++)
		g[j].a[e[i].x]|=1ll<<e[i].y,
		g[j].a[e[i].y]|=1ll<<e[i].x;
	}
	for (int i=0;i<s;i++) {
		for (int j=0;j<12;j++)
			for (int k=0;k<n;k++)
				if (g[j].a[k]>>a[i][(j+1)%a[i].size()]&1)
					g[j].a[k]^=1ll<<a[i][(j+1)%a[i].size()];
	}
	ans.I(),base.I(),x=k/12; int y=k%12;
	for (int i=0;i<12;i++) base=base*g[i];
	while (x) { if (x&1) ans=ans*base; base=base*base,x>>=1; }
	for (int i=0;i<y;i++) ans=ans*g[i];
	return ans.a[S]>>T&1;
}
int main()
{
	n=read(),m=read(),S=read()-1,T=read()-1,k=read();
	while (m--) { int x=read()-1,y=read()-1; G[x][y]=G[y][x]=read(); }
	for (int i=0;i<n;i++) for (int j=0;j<n;j++) if (G[i][j]) e[m++]={i,j,G[i][j]};
	sort(e,e+m),s=read();
	for (int i=0;i<s;i++) {
		a[i].resize(read() );
		for (int j=0;j<a[i].size();j++) a[i][j]=read()-1;
	}
	if (!check(m-1) ) return printf("'IMP0SSBLE!!'"),0;
	int l=0,r=m-1,mid; while (l<=r) mid=(l+r)>>1,check(mid)?r=mid-1:l=mid+1;
	return printf("%d",e[l].z),0;
}
```

---

## 作者：MiniLong (赞：0)

## 题意

给定一个 $n$ 个点 $m$ 条边的无向图，每条边有一个边权 $w$，经过每条边需要 $1$ 单位时间，要求从点 $s$ 走到点 $t$ 恰好 $k$ 单位时间内所经过的边的边权最大值最小，问最小是多少。此外，还周期性地有一些点不能经过，每种周期只可能为 $2,3,4$ 中的 $1$ 个，总共有 $a$ 个周期。

## 思路

这道题与 [P2579 沼泽鳄鱼](https://www.luogu.com.cn/problem/P2579) 十分类似，唯一的区别就在于边权的不同。

首先考虑没有任何点不能经过，即 $a = 0$ 的情况：

考虑使用一个邻接矩阵 $G$ 来表示这个图，其中 $G_{i,j}$ 表示点 $i$ 到点 $j$ 所经过的所有边中边权最大值最小的值。

然后考虑转移。

对于 $i$ 到 $j$，枚举中间点 $k$。因为要求最大值最小，所以 $G_{i, j} = \min(G_{i, j}, \max(G_{i, k}, G_{k,j}))$。

然后将普通的矩阵乘法改成上面的转移就好了，具体详见代码。

再考虑有点不能经过的情况：

因为周期只有 $2, 3, 4$，所以用一个长度为 $\operatorname{lcm}(2,3,4) = 12$ 的周期即可。

把 $1$ 到 $12$ 时刻的矩阵给处理出来，分别为  $G_1, G_2, G_3 \dots G_n$，令 $H = \prod\limits_{i=1}^{12} G_i$，最终的矩阵就是 $H^{k/12} \times \prod\limits_{i=1}^{k \bmod 12} G_i$。

最后记得矩阵初始值应全部为无限大，因为要取最小值。

时间复杂度为 $O(n^3 \log k)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define _rep(i, x, y) for(int i = x; i <= y; ++i)
#define _req(i, x, y) for(int i = x; i >= y; --i)
#define _rev(i, u) for(int i = head[u]; i; i = e[i].nxt)
#define pb(x) push_back(x)
#define mst(f, i) memset(f, i, sizeof f)
using namespace std;
#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif
namespace fastio{
    template<typename T> inline void read(T &t){
        T x = 0, f = 1;
        char c = getchar();
        while(!isdigit(c)){
            if(c == '-') f = -f;
            c = getchar();
        }
        while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
        t = x * f;
    }
    template<typename T, typename ... Args> inline void read(T &t, Args&... args){
        read(t);
        read(args...);
    }
    template<typename T> void write(T t){
        if(t < 0) putchar('-'), t = -t;
        if(t >= 10) write(t / 10);
        putchar(t % 10 + '0');
    }
    template<typename T, typename ... Args> void write(T t, Args... args){
        write(t), putchar(' '), write(args...);
    }
    template<typename T> void writeln(T t){
        write(t);
        puts("");
    }
    template<typename T> void writes(T t){
        write(t), putchar(' ');
    }
};
using namespace fastio;
typedef long long ll;
typedef pair<int, int> PII;
const int N = 55, inf = 0x3f3f3f3f;
int n, m, s, t, k;
int T, num, p[5];
struct matrix{
	int c[N][N];
	void clear(){
		mst(c, inf);
	}
	void output(){
		_rep(i, 1, n){
			_rep(j, 1, n) cout << setw(15) << c[i][j];
			puts("");
		}
		puts("==========");
	}
}G[13], H, A;
matrix operator*(matrix a, matrix b){
	matrix x; x.clear();
	_rep(k, 1, n){
		_rep(i, 1, n){
			_rep(j, 1, n){
				x.c[i][j] = min(x.c[i][j], max(a.c[i][k], b.c[k][j]));
			}
		}
	}
	return x;
}
matrix ksm(matrix base, int h){
	matrix res = base; h--;
	while(h){
		if(h & 1) res = res * base;
		base = base * base, h >>= 1;
	}
	return res;
}
void out(int x){
	if(x == inf) puts("'IMP0SSBLE!!'");
	else writeln(x);
}
int main(){
	G[0].clear();
	read(n, m, s, t, k);
	_rep(i, 1, m){
		int u, v, w; read(u, v, w);
		G[0].c[u][v] = G[0].c[v][u] = w;
	}
	_rep(i, 1, 12) G[i] = G[0];
	read(num);
	bool flag = !num;
	while(num--){
		read(T);
		_rep(i, 0, T - 1) read(p[i]);
		_rep(i, 1, 12){
			_rep(j, 1, n){
				G[i].c[j][p[i % T]] = inf;
			}
		}		
	}
	if(flag){
		A = ksm(G[0], k);
		out(A.c[s][t]);
		return 0;
	}
	H = G[1];
	_rep(i, 2, 12) H = H * G[i];
	A = ksm(H, k / 12), k %= 12;
	_rep(i, 1, k) A = A * G[i];
	out(A.c[s][t]);
    return 0;
}
```

---

## 作者：Ydkwia (赞：0)

~~水一波题解~~

------------

本蒟蒻是看着楼下几位大佬的题解写的，由于楼下几位大佬的题解已经写得很详细了，再次就不再细讲。

此题与[沼泽鳄鱼](https://www.luogu.org/problem/P2579)较为类似。由于2<=t<=4 , 所以每个怪物在gcd( 2 , 3 , 4 )=12周期的位置是不变的，只需预处理每12个单位时间内的矩阵mat，再快速幂mat^([k/12]),最后将答案乘上（k%12）的矩阵即可。

要注意：
1.矩阵乘法没有交换律，得先预处理Q=A[1]*A[2]*......*A[11]*A[0]，再用算出Q^[K/12]，对于剩下的，从A[1]开始乘完K%12个


2.此题的矩阵乘法略有些不同，在模板上需要进行改进，还要对矩阵进行适当的预处理。






~~主要的还是上代码~~
```cpp
#include<bits/stdc++.h>

using namespace std ;

int n , m , x , y , z , t , st , en ;

int danger[ 33 ][ 5 ] ;

struct mat 
{
	
	int num[ 55 ][ 55 ] ;

} ans , sum[ 4 ] ;

mat operator * ( const mat &a , const mat &b )
{
	
	mat ans1 ;
	
	memset( ans1.num , - 1 , sizeof( ans1.num ) ) ;
	
	for ( int i = 1 ; i <= n ; i ++ )
		for ( int j = 1 ; j <= n ; j ++ )
			for ( int k = 1 ; k <= n ; k ++ ) 
				if ( ( a.num[ i ][ k ] + 1 ) && ( b.num[ k ][ j ] + 1 ) ) 
				{
				 
					if ( ans1.num[ i ][ j ] + 1 ) ans1.num[ i ][ j ] = min( ans1.num[ i ][ j ] , max( a.num[ i ][ k ] , b.num[ k ][ j ] ) ) ;
					else ans1.num[ i ][ j ] = max( a.num[ i ][ k ] , b.num[ k ][ j ] ) ;
					
				} 
			
	return ans1 ;
	
}

int main()
{
	
	scanf( "%d%d%d%d%d" , &n , &m , &st , &en , &t ) ;
	
	memset( sum[ 0 ].num , - 1 , sizeof( sum[ 0 ].num ) ) ;
	
	memset( sum[ 1 ].num , - 1 , sizeof( sum[ 1 ].num ) ) ;
	
	memset( sum[ 2 ].num , - 1 , sizeof( sum[ 2 ].num ) ) ;
	
	memset( sum[ 3 ].num , - 1 , sizeof( sum[ 3 ].num ) ) ;
	
	memset( ans.num , - 1 , sizeof( ans.num ) ) ;

	for ( int i = 1 ; i <= m ; i ++ ) scanf( "%d%d%d" , &x , &y , &z ) , sum[ 0 ].num[ x ][ y ] = sum[ 0 ].num[ y ][ x ] = z ;
	
	scanf( "%d" , &m ) ;
	
	for ( int i = 1 ; i <= m ; i ++ ) 
	{
		
		scanf( "%d" , &danger[ i ][ 0 ] ) ;
		
		for ( int j = 1 ; j <= danger[ i ][ 0 ] ; j ++ ) scanf( "%d" , &danger[ i ][ j ] ) ;		
		
	}
	
	for ( int i = 1 ; i <= n ; i ++ ) sum[ 1 ].num[ i ][ i ] = ans.num[ i ][ i ] = 0 ;
	
	for ( int i = 1 ; i <= 12 ; i ++ )
	{
		
		sum[ 2 ] = sum[ 0 ] ;
		
		for ( int j = 1 ; j <= m ; j ++ ) 
			for ( int k = 1 ; k <= n ; k ++ ) sum[ 2 ].num[ k ][ danger[ j ][ 1 + ( i % danger[ j ][ 0 ] ) ] ] = - 1 ;
			
		sum[ 1 ] = sum[ 1 ] * sum[ 2 ] ;
		
		if ( ( i % 12 == t % 12 ) && ( t % 12 ) ) sum[ 3 ] = sum[ 1 ] ; 
				
	}
	
	m = t % 12 ;
	
	t /= 12 ;
	
	if ( t ) ans = ans * sum[ 1 ] , t -- ;
	
	while ( t )
	{
		
		if ( t % 2 ) ans = ans * sum[ 1 ] ;
		
		t >>= 1 ;
		
		sum[ 1 ] = sum[ 1 ] * sum[ 1 ] ;
		
	}
	
	if ( m ) ans = ans * sum[ 3 ] ;
	
	if ( ans.num[ st ][ en ] + 1 ) printf( "%d" , ans.num[ st ][ en ] ) ;
	else printf( "'IMP0SSBLE!!'" ) ;
	
	return 0 ;	
	
} 
 
 
 
 
 
 
 
```


---

