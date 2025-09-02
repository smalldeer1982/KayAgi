# Dima and Hares

## 题目描述

Dima liked the present he got from Inna very much. He liked the present he got from Seryozha even more.

Dima felt so grateful to Inna about the present that he decided to buy her $ n $ hares. Inna was very happy. She lined up the hares in a row, numbered them from 1 to $ n $ from left to right and started feeding them with carrots. Inna was determined to feed each hare exactly once. But in what order should she feed them?

Inna noticed that each hare radiates joy when she feeds it. And the joy of the specific hare depends on whether Inna fed its adjacent hares before feeding it. Inna knows how much joy a hare radiates if it eats when either both of his adjacent hares are hungry, or one of the adjacent hares is full (that is, has been fed), or both of the adjacent hares are full. Please note that hares number 1 and $ n $ don't have a left and a right-adjacent hare correspondingly, so they can never have two full adjacent hares.

Help Inna maximize the total joy the hares radiate. :)

## 样例 #1

### 输入

```
4
1 2 3 4
4 3 2 1
0 1 1 0
```

### 输出

```
13
```

## 样例 #2

### 输入

```
7
8 5 7 6 1 8 9
2 7 9 5 4 3 1
2 3 3 4 1 1 3
```

### 输出

```
44
```

## 样例 #3

### 输入

```
3
1 1 1
1 2 1
1 1 1
```

### 输出

```
4
```

# 题解

## 作者：littleseven (赞：12)

# CF 358D Dima and Hares

**题目链接：**[洛谷 CF 358D Dima and Hares](https://www.luogu.org/problem/CF358D)	[CF 358D Dima and Hares](http://codeforces.com/problemset/problem/358/D)

**算法标签:**  `DP`、`思维`

## 题目描述：

$N$个物品排成一排,按照一定顺序将所有物品都拿走，如果拿走某个物品时相邻两个物品都没有被拿过，那么得到的价值为$a_i$；如果相邻的两个物品有一个被拿过（左右无所谓），那么得到的价值为$b_i$；如果相邻的两个物品都被拿走了，那么对应价值为$c_i$。问能够获得的最高价值为多少。



## 题解：

**DP**

看到题之后，第一反应就是贪心或者DP。仔细看一看，果断pass掉贪心的想法。

之后我们会发现这道题的DP有一些很难逾越的坑（导致我第一份代码写了140行还假了…………）：

- 每一个点的决策会改变前后两点的答案，前后两点的决策也会影响到当前点的答案
- 第一个点和最后一个点只能选择$a$或者$b$。

对于第一个问题，我们就要考虑如何**搞方程**才能满足这个条件。

如果每次都考虑当前点为中间点的话，的确很直接，很清晰，但是怎么同时对前后更改，（如果前后更改还会涉及到其它点的更改），这显然是实现不了的。

那么我们更换思路，考虑每一次遍历到的当前点是三个点中的最后一个，上图理解：

![CF 358D Dima and Hares p1.png](https://i.loli.net/2019/10/21/R9huD2L5A7iOovp.png)

这样我们可以搞出来一个**DP状态**：

> $dp[i][1]$表示先选择$i - 1$， 后选择$i$，可以得到的前$i - 1$的最大答案。
>
> $dp[i][0]$表示先选择$i$，后选择$i-1$可以得到前$i - 1$的最大答案。

那么转移方程：

$dp[i][1] = max(dp[i - 1][1] + b[i-1], dp[i - 1][0] + a[i-1])$

$dp[i][0] = max(dp[i - 1][1] + c[i-1], dp[i - 1][0] + b[i-1])$

上图理解：

![CF 358D Dima and Hares p2.png](https://i.loli.net/2019/10/21/VS76bvCl2QYcWwt.png)

这样第一个问题就解决了，那么怎么解决第二个问题：$1$号点和$n$号点。

首先因为每次取最大值，不妨设所有的$dp[~][~]~=~-inf$。

之后对于第一个点，由于它前边没有点，所以一定会先取这个点：$dp[1][0]=0$

对于最后一个点，由于他后边没有点，那么我们假设后边有一个点（由于状态当中$dp[i]$存放的是$1 \sim i-1$的答案），并且对于这个多出来的点来说，一定是先取$(n+1)-1$这个点，所以在第$n$个点的答案自然就是$dp[n+1][1]$

现在状态有了，初值有了，转移方程有了，答案也有了，直接写dp就解决了。

## AC代码

```cpp
#include <bits/stdc++.h>

using namespace std;

#define setI(x) freopen(x".in", "r", stdin);

#define setO(x) freopen(x".out", "w", stdout);

#define setIO(x) setI(x) setO(x);

const int N = 100100;

typedef long long ll;

int n, a[N], b[N], c[N];

ll dp[N][2];

void rd() {
	for (int i = 1; i <= n; i ++ ) {
		scanf("%d", &a[i]);
	}
	for (int i = 1; i <= n; i ++ ) {
		scanf("%d", &b[i]);
	}
	for (int i = 1; i <= n; i ++ ) {
		scanf("%d", &c[i]);
	}
}

int main() {
	// setIO("cow");
	scanf("%d", &n);
	rd();
	memset(dp, -0x3f, sizeof dp);
	dp[1][0] = 0;
	for (int i = 2; i <= n + 1; i ++ ) {
		dp[i][0] = max(dp[i - 1][0] + b[i - 1], dp[i - 1][1] + c[i - 1]);
		dp[i][1] = max(dp[i - 1][0] + a[i - 1], dp[i - 1][1] + b[i - 1]);
	}
	cout << dp[n + 1][1] << endl;
	return 0;
}
```



---

## 作者：Tyyyyyy (赞：3)

# 题目大意
现有一堆兔子（可看做一排物品），要给每只兔子喂食。

当两边的兔子均没有被喂食过，兔子会释放出$a_i$的快乐值；

当两边的兔子有且仅有一边被喂食过，兔子会释放$b_i$的快乐值；

当两边的兔子均被喂食过，兔子会释放$c_i$的快乐值。

现在请你输出一个数：兔子能释放的最大快乐值和。
# 题目分析
容易想到$dp$来解决这个问题，但是若仔细地分析，会发现一个问题：

**每只兔子释放快乐值的多少受两边兔子的影响，而每只兔子又会影响两边的兔子。**

显然一维数组是不行的，那么我们再思考一下：

对于每只兔子，设其编号为$i$，可得到一个模型，包括第$i-1$，第$i$和第$i+1$只兔子。

不妨将其转化为第$i-2$，第$i-1$，和第$i$只兔子。

我们可以定义$dp[i][0]$表示先喂第$i$只兔子所能得到的最大值，$dp[i][1]$表示先喂第$i-1$只兔子所能得到的最大值。

同时由于一只兔子有多个参数，不妨定义一个结构体来存储数据。

容易得到转移方程：

$dp[i][1]=max(dp[i-1][1]+t[i-1].b,dp[i-1][0]+t[i-1].a)$

$dp[i][0]=max(dp[i-1][1]+t[i-1].c,dp[i-1][0]+t[i-1].b)$

但要注意：对于最后一只兔子，没有“两边均被喂食过”的情况，因此我们要枚举到$n+1$来解决这个问题。

最后注意$dp$数组要初始化为一个极小值。

AC代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<iomanip>
#include<cmath>
#include<queue>
#include<algorithm>
using namespace std;
const int inf=1e7;
int n,dp[3100][2];
struct thing
{
	int a,b,c;
}t[3100];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&t[i].a);
	for(int i=1;i<=n;i++)scanf("%d",&t[i].b);
	for(int i=1;i<=n;i++)scanf("%d",&t[i].c);
	for(int i=1;i<=3001;i++)dp[i][0]=dp[i][1]=-inf;
	dp[1][0]=0;
	for(int i=2;i<=n+1;i++)
	{
		dp[i][1]=max(dp[i-1][1]+t[i-1].b,dp[i-1][0]+t[i-1].a);
		dp[i][0]=max(dp[i-1][1]+t[i-1].c,dp[i-1][0]+t[i-1].b);
	}
	printf("%d",dp[n+1][1]);
	return 0;
}
```

---

## 作者：WorldMachine (赞：2)

有点意思的 dp。

发现这里 $i$ 要考虑的后效性和 $i-1$ 与 $i+1$ 都有关，因此考虑**在 $i$ 处决策 $i-1$**。

设 $f_{i,0/1}$ 表示 $i$ 在 $i-1$ 前面或后面取的最大收益。有转移方程：
$$
\begin{aligned}
f_{i,0}&=\max(f_{i+1,1}+a_i,f_{i+1,0}+b_i)\\
f_{i,1}&=\max(f_{i+1,1}+b_i,f_{i+1,0}+c_i)
\end{aligned}
$$
注意初始化 $f_{n+1,0}=-\infty$，如果不初始化的话可能会使 $n$ 一开始会有两个相邻的取过的物品。

---

## 作者：傅思维666 (赞：2)


## 题解：

~~（2019.10.21模拟赛爆蛋场）~~

一道非常好的DP。

我给它起了个名字：**双重DP**。

我们在初步分析题意的基础上，可以发现，这个物品的选择与否与左右两个物品有关系。

也就是说，针对于每个物品，决策不仅有选和不选两种，而且和选择的顺序有关系。

对于这种问题，我们采用这种办法：

开两重DP数组，其中$dp[i] [0]$表示前$i-1$件物品在先**留下$i-1$这件物品**的最大价值。

同理：$dp[i] [1]$表示前$i-1$件物品在**取走$i-1$这件物品**的最大价值。

那么我们设计出了以下的动态转移方程：
$$
dp[i][0]=max(dp[i-1][0]+b[i-1],dp[i-1][1]+c[i-1]);
$$

$$
dp[i][1]=max(dp[i-1][0]+a[i-1],dp[i-1][1]+b[i-1]);
$$

我们着重解释这个状态转移方程：

（先上张图）

![](https://img2018.cnblogs.com/blog/1738131/201910/1738131-20191021193720789-1114823891.png)



现在，我们对$i$件物品进行决策，我们分别对其进行两重$DP$。那么，第一个状态转移方程（关于$dp[i][0]$的）种涉及到了$dp[i-1][0/1]$，根据我们对状态的定义。这个$dp[i-1][0/1]$涉及到了第$i-2$件物品，那么，我们就恍然大悟了：为什么我们状态定义的是前$i-1$件物品的最大价值？因为虽然方程设置的是$dp[i]$，但我们其实是在对$i-1$这个点进行状态上的决策。

在第一个状态转移方程中，实际上max()函数中的两个分量的第一个分量就是表示：取走物品顺序为：$i\to i-1\to i-2$，易知，此时的$i-1$物品对答案的贡献价值应该是$b[i-1]$（因为$i$被取走了，而$i-2$仍然留着）。同理，第二个分量的意义就是：取走物品顺序为：$i-2\to i\to i-1$ ，而答案就应该加上$c[i-1]$。

第二个状态转移方程同理。

最后在统计答案的时候，一定要记住，你的状态定义的是前$i-1$个物品的价值，并没有把最后的物品加上。所以我们输出的时候其实还要进行一次决策。

### 总结：

$DP$算法的重要性在算法竞赛中不言而喻。而弄明白各种$DP$题型的状态和转移方程设计技巧更是重中之重。对于每一道$DP$题目，都要好好想一想自己在这道题目中学到了什么。对于这道题，我们可以从中学习到对于多种状态决策的$DP$的设计方式。并结合图例发现了$DP$决策过程中，物品选择顺序在状态转移方程中的体现。我想，能获得这些收获，这道题的意义才不仅仅是一个虚弱无力的$AC$吧。

代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=3005;
char *p1,*p2,buf[100000];
#define nc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
int read()
{
	int x=0,f=1;
	char ch=nc();
	while(ch<48){if(ch=='-')f=-1;ch=nc();}
	while(ch>47)	x=(((x<<2)+x)<<1)+ch-48,ch=nc();
	return x*f;
}
int n;
int a[maxn],b[maxn],c[maxn];
int dp[maxn][3];
//dp[i][0]表示前i-1的价值（先留下i-1）
//dp[i][1]表示前i-1的价值（先取走i-1）
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=1;i<=n;i++)
		b[i]=read();
	for(int i=1;i<=n;i++)
		c[i]=read();
	if(n==1)
	{
		printf("%d",a[1]);
		return 0;
	}
	dp[2][0]=b[1];
	dp[2][1]=a[1];
	for(int i=3;i<=n;i++)
	{
		dp[i][0]=max(dp[i-1][0]+b[i-1],dp[i-1][1]+c[i-1]);
		dp[i][1]=max(dp[i-1][0]+a[i-1],dp[i-1][1]+b[i-1]);
	}
	printf("%d",max(dp[n][0]+a[n],dp[n][1]+b[n]));
	return 0;
}
```

---

## 作者：Ganshuaige (赞：2)

# dp
dp方程就容易得出

dp[i][1]表示先选i-1前i-1能获得的最大值

dp[i][0]表示先选i前i-1能获得的最大值

dp[i][0]=max(dp[i-1][1]+c[i-1],dp[i-1][0]+b[i-1]);

dp[i][1]=max(dp[i-1][0]+a[i-1],dp[i-1][1]+b[i-1]);

```
#include<iostream>
#include<cstring>
#include<cstdio>

const int inf = 0x3f3f3f3f;
const int Maxn = 3005;
using namespace std;

int n;
int a[Maxn],b[Maxn],c[Maxn];

int read(){
	int x=0,f=1;
	char s=getchar();
	while(s<'0'||s>'9'){
		if(s=='-')
			f=-1;
		s=getchar();
	}
	while(s>='0'&&s<='9'){
		x=x*10+s-'0';
		s=getchar();
	}
	return x*f;
}

int dp[Maxn][5];
//前i-1个能获得的最大值 
//dp[i][0]先选i 
//dp[i][1]先选i-1 

//a[i]都没取
//b[i]取了一个
//c[i]都取了 

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=1;i<=n;i++)
		b[i]=read();
	for(int i=1;i<=n;i++)
		c[i]=read();
	memset(dp,-inf,sizeof(dp));
	dp[1][0]=0;
	for(int i=2;i<=n+1;i++){
		dp[i][0]=max(dp[i-1][1]+c[i-1],dp[i-1][0]+b[i-1]);
		dp[i][1]=max(dp[i-1][0]+a[i-1],dp[i-1][1]+b[i-1]);
	}
	printf("%d",dp[n+1][1]);
}//

```


---

## 作者：naroto2022 (赞：1)

# CF358D 题解

### 题面

[原题传送门](https://www.luogu.com.cn/problem/CF358D)

### 思路

挺好的一道 DP 题。

首先分析题目会发现这道题的 DP 有点特殊：每一个点的状态会与前后两道题的状态相互影响与改变。

而观察到，一个点 $i$ 的状态均可以表示成如下两种情况。

1. 先选第 $i+1$ 个物品，再取第 $i$ 个物品。（取物品的操作并不一定是相邻的，只是第 $i$ 个物品在取了第 $i+1$ 个物品后取的。）
2. 先选第 $i$ 个物品，再选第 $i+1$ 个物品。（取物品的操作并不一定是相邻的，只是第 $i+1$ 个物品在取了第 $i$ 个物品后取的。）

于是很容易想到可以设一个二维的 $dp$ 数组：$dp[i][2]$。

1. $dp[i][0]$ 表示先取第 $i+1$ 个物品获得的前 $i$ 个物品的最大值。
2. $dp[i][1]$ 表示后取第 $i+1$ 个物品获得的前 $i$ 个物品的最大值。

接下来就开始推递推方程。

对于一个 $dp[i][0]$，是先取第 $i+1$ 个物品，后取第 $i$ 个物品，这个时候只要讨论 $dp[i-1]$ 的两种状态即可。

1. 对于 $dp[i-1][0]$ 是先取第 $i$ 个物品，后取第 $i-1$ 个物品，此时取第 $i$ 个物品的时候，相邻的两个物品有一个被拿过，所以得到的价值为 $b[i]$。
2. 对于 $dp[i-1][1]$ 是先取第 $i-1$ 个物品，后取第 $i$ 哥物品，此时取第 $i$ 个物品的时候，相邻的两个物品都被拿过，所以得到的价值为 $c[i]$。

因此 $dp[i][0]=\max(dp[i-1][0]+b[i],dp[i-1][1]+c[i])$。

对于一个 $dp[i][1]$，是先取第 $i$ 个物品，后取第 $i+1$ 个物品，这个时候一样的讨论 $dp[i-1]$ 的两种状态即可。

1. 对于 $dp[i-1][0]$ 是先取第 $i$ 个物品，后取第 $i-1$ 个物品，此时取第 $i$ 个物品的时候，相邻的两个物品都没有被拿过，所以得到的价值为 $a[i]$。
2. 对于 $dp[i-1][1]$ 是先取第 $i-1$ 个物品，后取第 $i$ 哥物品，此时取第 $i$ 个物品的时候，相邻的两个物品有一个被拿过，所以得到的价值为 $b[i]$。

因此 $dp[i][1]=\max(dp[i-1][0]+a[i],dp[i-1][1]+b[i])$。

故我们就可以线性求出 $dp$ 数组了。

接下来，题目询问获得的最大价值，注意到第 $n$ 个物品只可能是先取第 $n$ 个物品，后取第 $n+1$ 个物品，因为不存在第 $n+1$ 个物品。

故答案为 $dp[n][1]$。

注意，一开始要初始化，给 $dp$ 赋值成一个极小值（我因为没做这个，WA 过。）。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define INF 0x7fffffff/2
using namespace std;
const int MN=3005;
long long n,a[MN],b[MN],c[MN],dp[MN][2];
//dp[i][0] 表示先取第 i+1 个物品获得的前 i 个物品的最大值。 
//dp[i][1] 表示后取第 i+1 个物品获得的前 i 个物品的最大值。 
int main(){
	scanf("%lld",&n);
	for(int i=1; i<=n; i++) scanf("%lld",&a[i]);
	for(int i=1; i<=n; i++) scanf("%lld",&b[i]);
	for(int i=1; i<=n; i++) scanf("%lld",&c[i]);
	for(int i=0; i<=n; i++) for(int j=0; j<=n; j++) dp[i][j]=-INF;
	dp[0][0]=0;
	for(int i=1; i<=n; i++){
		dp[i][0]=max(dp[i-1][0]+b[i],dp[i-1][1]+c[i]);
		dp[i][1]=max(dp[i-1][0]+a[i],dp[i-1][1]+b[i]);
	}
	printf("%lld",dp[n][1]);
	return 0;
} 
```

---

## 作者：_Aoi_ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF358D)
### 思路
第一眼看了想到的是**DP**（~~毕竟老师把这道题放到DP专栏里了~~）

这道题的DP不是普通的DP，而是“双重DP”，每一个点和它前后两点的选择会互相影响。

那么一维数组肯定不行，必须定义二维数组或几个一维数组：

每一个物品都有自己的编号 $i$,它前后的物品的编号就为 $i-1$和 $i+1$。

我们可以将它们三个物品的编号依次往前移一位，看作是$i-2$,$i-1$与$i$。

用$dp_{i,0}$表示编号为$i-1$的物品还没有背取过所得的最大值，$dp_{i,1}$表示编号为$i-1$的物品已经被取过了所得的最大值。

```cpp
dp[i][0]=max(dp[i-1][0]+b[i-1],dp[i-1][1]+c[i-1]);
```
前者取的顺序为：$i$ $\rightarrow$ $i-1$ $\rightarrow$ $i-2$

后者取的顺序为：$i-2$ $\rightarrow$ $i$ $\rightarrow$ $i-1$

```cpp
dp[i][1]=max(dp[i-1][0]+a[i-1],dp[i-1][1]+b[i-1]);
```
前者取的顺序为：$i-1$ $\rightarrow$ $i$ $\rightarrow$ $i-2$

后者取的顺序为：$i-2$ $\rightarrow$ $i-1$ $\rightarrow$ $i$

最后注意一点：第1个和第n个没有两边的物品，所以第一个单独处理，循环要循环到n+1。

code：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,a[10001],b[10001],c[10001],dp[10001][2];
int main()
{
	memset(dp,128,sizeof(dp));//将DP初始化为最小值 
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
		cin>>b[i];
	for(int i=1;i<=n;i++)
		cin>>c[i];
	dp[1][0]=0;//单独处理 
	for(int i=2;i<=n+1;i++)//从2至n+1 
	{
		/*DP方程式*/ 
		dp[i][0]=max(dp[i-1][0]+b[i-1],dp[i-1][1]+c[i-1]);
		dp[i][1]=max(dp[i-1][0]+a[i-1],dp[i-1][1]+b[i-1]);
	}
	cout<<dp[n+1][1];//输出 
	return 0;
}
```

---

## 作者：觞羰涙 (赞：1)

# 比较好理解的dp
## 题意：一堆兔子 喂某一只时其获得的快乐值有三种，分为两边的兔子都喂过，其中一只喂过，都没喂，求喂完的最大快乐值
```cpp
	read(n);//dp[i][1/0] 1:比前一个先喂 0:比前一个后喂 
	for(int i=1;i<=n;i++)read(a[i]);// 两边都饿 
	for(int i=1;i<=n;i++)read(b[i]);// 有一个饿 
	for(int i=1;i<=n;i++)read(c[i]);// 两边不饿 
	dp[0][0]=-inf;//dp时增加的是(i-1)那只兔子的快乐值 如下
	for(int i=1;i<=n;i++)
	{
		dp[i][1]=max(dp[i-1][0]+c[i],dp[i-1][1]+b[i]);
		dp[i][0]=max(dp[i-1][1]+a[i],dp[i-1][0]+b[i]);
	}
	printf("%d",dp[n][0]);//max(dp[n][1],dp[n][0])是错的!
```

---

