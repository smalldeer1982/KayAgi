# [USACO08MAR] River Crossing S

## 题目描述

农夫约翰以及他的 $N(1 \le N \le 2500)$ 头奶牛打算过一条河，但他们所有的渡河工具，仅仅是一个木筏。 

由于奶牛不会划船，在整个渡河过程中，约翰必须始终在木筏上。在这个基础上，木筏上的奶牛数目每增加 $1$，FJ把木筏划到对岸就得花更多的时间。 

当约翰一个人坐在木筏上，他把木筏划到对岸需要 $M(1 \le M \le 1000)$ 分钟。当木筏搭载的奶牛数目从 $i-1$ 增加到 $i$ 时，约翰得多花 $M_i(1 \le M_i \le 1000)$ 分钟才能把木筏划过河（也就是说，船上有 $1$ 头奶牛时，约翰得花 $M+M_1$ 分钟渡河；船上有 $2$ 头奶牛时，时间就变成 $M+M_1+M_2$ 分钟。后面的以此类推）。那么，约翰最少要花多少时间，才能把所有奶牛带到对岸呢？当然，这个时间得包括约翰一个人把木筏从对岸划回来接下一批的奶牛的时间。

## 样例 #1

### 输入

```
5 10 
3 
4 
6 
100 
1 
```

### 输出

```
50 
```

# 题解

## 作者：Stella_Yan (赞：82)

这一题可以用背包的思路来做（这就是为什么这一题的标签有个背包）。

首先，设$f[\ j\ ]$表示载$j$头奶牛过河的最小时间，$sum[\ i\ ]$表示一次载$i$头奶牛过河的时间，那么状态转移方程就是：

$$f[\ j\ ]=min(f[\ j\ ],f[\ j-i\ ]+sum[\ i\ ])\text{，最后输出f[\ n\ ]}$$

这个方程是什么意思呢？

首先，$f[\ j-i\ ]+sum[\ i\ ]$就是代表少载$i$头奶牛再加上载$i$头奶牛的时间，与原来算出来的$f[\ j\ ]$比较，看一下哪一个比较少。

$i$从$1 - n$循环，$j$从$i-n$循环。

那么$sum[\ i\ ]$要怎么计算呢？我们用前缀和：

$$sum[\ i\ ]=sum[\ i-1\ ]+w[\ i\ ]\text{ (w[\ i\ ]为题目中的Mi)}$$

如果理解不来，你可以这样想：

把$i$当成完全背包的重量,$sum[\ i\ ]$当成价值，然后求最小价值。

然后每个$sum[\ i\ ]$加上$2m$，就是筏子一次来回的时间，最后输出的时候再减去$m$，因为最后一次不用划回来。

具体思路看代码：

---

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int f[10010];
int sum[10010];
int w[10010];
int m,n;
const int inf=99999999;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		f[i]=inf;//要求最小值的话，每一个f[i]都要赋值为无限大。
		cin>>w[i];
		sum[i]=sum[i-1]+w[i];//计算前缀和。
	}
	for(int i=1;i<=n;i++){
		sum[i]+=2*m;
	}//每个加上2*m
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			f[j]=min(f[j],f[j-i]+sum[i]);//方程，和背包差不多
		}
	}
	cout<<f[n]-m;//输出的时候减掉m，因为不用划回来。
	return 0;
}
```

---

题外话（如果你没时间的话，不看也没关系）：

这里附加一个$\LaTeX$公式小窍门：

在表示数组的时候，一般用
```
$f[i]$
```

$f[i]$

这样就会贴在一起，不好看。可以加一个空格（$\LaTeX$中空格是右斜杠+空格）
```
$f[\ i\ ]$
```

$f[\ i\ ]$

你还可以自行调整
```
$f[\,i\,]$
$f[\;i\;]$
```

$f[\,i\,]$

$f[\;i\;]$

当然如果你喜欢原来的样子也可以的。

或者是

```
$f_i$
```

$f_i$

---


---

## 作者：kkxhh (赞：20)

首先我们定义 **d[i]** 为运送i头牛到对岸的最小花费

然后对于每个 **d[i]** 再枚举一个分界点，试图把 **i** 头奶牛分成两趟运完

需要注意的是因为每次运送完的时候农夫是在对岸的，所以除了加上两趟分别的花费外还要再加上一个 **d[0]** （也就是农夫一个人过来的花费）

读入方面直接设 **d[i]** 的初值是一趟把奶牛全运过去的花费就好了，这样就没必要记录题目中的 **m** 了

最后直接输出 **d[n]** 就是答案

代码如下

------------

```cpp
#include <cstdio>
using namespace std;

int n,d[2510];

int read(){
    char c=getchar(); int num=0,k=1;
    while(c>'9' || c<'0') k=(c=='-')?0:k,c=getchar();
    while(c<='9' && c>='0') num=num*10+c-'0',c=getchar();
    return k?num:-num;
}//一个读入函数

int main(){
    n=read(); d[0]=read();
    for(int i=1;i<=n;i++) d[i]=d[i-1]+read();
    for(int i=2;i<=n;i++)
        for(int j=1;j<i;j++)
            d[i]=(d[i]<d[j]+d[i-j]+d[0])?d[i]:d[j]+d[i-j]+d[0];//令 d[i] 等于 d[i] 和 d[j]+d[i-j]+d[0] 中较小的一个
    printf("%d",d[n]);
    return 0;
}
```

---

## 作者：Ezio_0420 (赞：19)

# 玄学（蒟蒻）背包（内存优化）

## 边读入边处理加省一个数组（只需一个dp【】）

其实状态转移方程前几位也都写了，如果我们定义dp[i]为i头奶牛过河所需最短时间，定义time[i]数组为前i个奶牛过河所用的时间，那么自然得到f[j]=min(f[j],f[j-i]+time[j-i]+m)


------------


以上是正常思路，那么我们的循环是这个样子

```cpp
    for (int i=1;i<=n;i++){
        cin>>t;
        time[i]=time[i-1]t;
    }
    for (int i=1;i<=n;i++)
    for (int j=i;j<=n;j++){
        dp[j]=min(dp[j],dp[j-i]+time[i]+m);
    }
```
，接下来是蒟蒻的特色！重点来了！！（内存优化）
我们会发现，对于第二个循环中的内层循环，我们用到了time[i]来保存前i头奶牛过河时间，而此时外层循环正在枚举每一个i;所以说此时不会用到比time[i]下标大的time[]值,所以说可以把第一个循环省去；

```cpp
    for (int i=1;i<=n;i++){
        cin>>t;
        time[i]=time[i-1]t;
        for (int j=i;j<=n;j++){
            dp[j]=min(dp[j],dp[j-i]+time[i]+m);
            }
    }
```
进一步，我们发现此时连比time[]下标小的time值都不会用到,所以说time数组完全可以省去，变为一个变量，每次加上新读入的没头奶牛的t值！
```cpp
    #include<iostream>
    #include<algorithm>
    #include<cstdio>
    using namespace std;
    int n,m,t,time,dp[2501];
    int main(){
        cin>>n>>m;
        for(int i = 1;i<=n;i++) dp[i]=100000000;
        time=m;
        for (int i=1;i<=n;i++){
            scanf("%d",&t);
            time+=t;
                for(int j=i;j<=n;j++){
                dp[j]=min(dp[j],dp[j-i]+time+m);
            }
        }
        cout<<dp[n]-m;
        return 0;
    }
一个小小的优化，希望能帮到大家
```

---

## 作者：MY（一名蒟蒻） (赞：16)

**update:新增代码注释和完整代码，并修正一些表述。**

**如果代码缩进奇怪，请以博客界面为准。**

---
本题并不是传统意义上的背包，但用到了背包思想。

观察样例可知，运送i头奶牛过河要加上前几头奶牛的时间一起，所以我们可以**前缀和预处理**一下。

代码如下

```cpp
//此处m数组用来存储FJ+i头奶牛过河的时间
scanf("%d%d",&n,&m[0]);//FJ一个人过河的时间为m[0]（0头牛）
	for(int i=1;i<=n;i++) 
	{
		scanf("%d",&m[i]);
		m[i]+=m[i-1];//前缀和
	}
```
---
接下来就是核心的背包部分了，我们**设$f[i]$表示FJ送i头奶牛过河的最短时间**。因为本题的特殊性，我们可以直接用刚才的m数组作为DP数组使用。

我们把i头奶牛分成两批（why？因为没必要分那么多，效果是一样的）送，for循环会一直细分到最小的两批的情况。

因为FJ还要回来，所以分成两批送的时间要加上FJ回来的过河时间。

**具体请详见代码理解**
```cpp
for(int i=1;i<=n;i++)//FJ送i头奶牛过河的最短时间
		for(int j=1;j<i/*题目保证奶牛数量大于0*/;j++) m[i]=min(m[i],m[j]+m[i-j]+m[0]);//两批，加FJ回来的时间
	printf("%d",m[n]);//输出最终结果
```
---

**无注释版（注释见上）完整代码~~感觉不放也行~~**
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n,m[2510];
int main()
{
//	freopen("work.in","r",stdin);freopen("work.out","w",stdout);
	scanf("%d%d",&n,&m[0]);
	for(int i=1;i<=n;i++) 
	{
		scanf("%d",&m[i]);
		m[i]+=m[i-1];
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<i;j++) m[i]=min(m[i],m[j]+m[i-j]+m[0]);
	printf("%d",m[n]);
//	fclose(stdin);fclose(stdout);
	return 0;
}
```
~~是不是很简洁呀233，求各位评价一下马蜂。~~

### Thank you for your watching!

---

## 作者：lsroi (赞：9)

**前言：** 求**最值问题**，很容易往DP上面去想。 

知道是DP，那么状态怎么设呢？

我一开始想的是，**设f[i][j]表示前i次过河总共接了j头牛所需的最少时间**

方程显然：**f[i][j]=min{f[i-1][k]+sum[j-k]+2m}** 

其中，sum[i}为M数组的前缀和，即i头牛过河要多加的时间。k为枚举上一次过河到了哪条牛。

分析下复杂度，这个DP枚举了i，j，k，所以**时间复杂度为O(n^3)** 这显然会超时。~~（经过我的测试，这个算法可以拿到60分的好成绩）~~

那该怎么优化呢，仔细一想你会发现，我们上面设的状态有些冗余，我们并不在乎，牛究竟是第几次过的河，我们需要的是所有牛过河的最少时间，所以我们可以将第一维状态删掉。

新的状态：**设f[i]表示i头牛过河所需的最少时间**

新的方程：**f[i]=min{f[j]+sum[i-j]+2m}**

这我不用多解释吧，和上面所表示的差不多。

**满分代码如下：**
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define maxn 2505
using namespace std;
int f[maxn],sum[maxn],n,m;
int main()
{
	memset(f,0x3f,sizeof(f));
	scanf("%d%d",&n,&m);
	sum[0]=0;
	for(int i=1;i<=n;i++)
	{
	  int v;  scanf("%d",&v);
	  sum[i]=sum[i-1]+v;
	}
	f[0]=-m;
	for(int i=1;i<=n;i++){
	  for(int j=0;j<i;j++)
		f[i]=min(f[i],f[j]+sum[i-j]+2*m);
	}
	printf("%d\n",f[n]);
	return 0;
} 
```

**这是60分代码：**
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define maxn 2505
using namespace std;
int f[maxn][maxn],sum[maxn],n,m,Min;
int main()
{
    memset(f,0x3f,sizeof(f));
    scanf("%d%d",&n,&m);
    sum[0]=0;
    for(int i=1;i<=n;i++)
    {
      int v;  scanf("%d",&v);
      sum[i]=sum[i-1]+v;
      f[1][i]=m+sum[i];
    }
    f[1][0]=0;  Min=f[1][n];
    for(int i=2;i<=n;i++){
      for(int j=1;j<=n;j++)
      	for(int k=0;k<j;k++)
          f[i][j]=min(f[i][j],f[i-1][k]+sum[j-k]+2*m);
      Min=min(Min,f[i][n]);
    }
    printf("%d\n",Min);
    return 0;
} 
```

大家可以对比一下两份代码有什么不一样。

**总结：**

对于同一道题，不同的状态会直接影响算法的时间复杂度，所以在你设状态之后，发现如何优化都ac不了这道题。这时就可以**想想自己的状态有没有记录冗余的信息，如果有，那就可以重新设下状态，有奇效**。

常见：将N维状态简化成N-1或N-K维。

**-------记DP优化**

---

## 作者：DDOSvoid (赞：7)

本题正解挺简单   f[i]表示把i头牛运过岸的最短时间 f[i]=min(f[i] ,f[i-j]+w[j])

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,m,a,w[2510],max1,f[2510];
int main(){
    memset(f,10,sizeof(f));
    scanf("%d%d",&n,&m);
    w[0]=2*m;
    for(int i=1;i<=n;i++){
        scanf("%d",&a);
        w[i]=a+w[i-1];//预处理出一次运i头牛再回来所花的时间 
    }
    f[0]=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=i;j++)
            f[i]=min(f[i],f[i-j]+w[j]);
    cout<<f[n]-m;//因为最后一次不用回来，所以要减去m 
    return 0;
}
```
然而 还可以用完全背包的思路来做 ~~虽然我的代码只得了60分~~ 但思路还是可以的 ~~可能只有我这么觉得==~~

如果哪位dalao想到了完全背包能AC的代码 一定要发题解啊

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,m,a,w[2510],c[2510],max1,f[25100000];
//w[i]一次运i头牛再回来所花的时间，f[i]表示在花i的时间内最多能运多少牛 
int main(){
    scanf("%d%d",&n,&m);
    w[0]=2*m;
    for(int i=1;i<=n;i++){
        c[i]=i;//
        scanf("%d",&a);
        w[i]=a+w[i-1];
        max1=max(max1,w[i]);
    }
    for(int i=1;i<=n;i++)
        for(int j=w[i];j<=max1;j++)
            f[j]=max(f[j],f[j-w[i]]+c[i]);//完全背包的套路 
    for(int i=1;i<=max1;i++)
        if(f[i]>=n){
            cout<<i-m;
            return 0;
        }
}
```

---

## 作者：sunxiaofan (赞：4)

这个题，原先我做了好几遍，总是tle（因为本蒟蒻原来使用的是O（n^3）的暴力算法），于是，才想到了几步优化：

首先，这个题我们可以使用前缀和，用一个sum数组来储存每次载i头牛所需的时间sum【i】；其中由于不载牛时需要时间为m，所以sum【0】=m；

第二步，每次可以载任意头牛，载任意头牛可以走任意个来回，所以可以使用一个完全背包。

### 然而，问题也就出来了，每次的返程时间怎么考虑？

其实很简单，用dp【j】表示已经运过了j头牛，如果是第一次运，也就是j=0时，可以不考虑返程；而j！=0时就把返程时间加上。

### 本人的代码仍然有很大的改进空间，有许多地方比较啰嗦，但为了方便大家的理解，本蒟蒻还是决定将代码贴上，dalao不喜勿喷。

代码如下：

```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
int n,m,mi,dp[2600],sum[2600];
int main()
{         
    freopen("2904.2.in","r",stdin);
    //freopen("1.out","w",stdout);
    scanf("%d%d",&n,&m);
    sum[0]=m;
    for(int i=1;i<=n;i++)
    {
    	scanf("%d",&mi);
    	sum[i]=sum[i-1]+mi;//前缀和
    	
	}
	for(int i=1;i<=n;i++)//完全背包的状态转移方程有点啰嗦
	{
		for(int j=0;j<=n-i;j++)
		{
			if(dp[j]!=0)//不是第一次运牛，需要考虑返程
			{
				if(dp[j+i]!=0)
				{
					dp[j+i]=min(dp[j+i],dp[j]+sum[i]+m);
				}
				else dp[j+i]=dp[j]+sum[i]+m;
			}
			else if(j==0)//第一次运牛
			{
				if(dp[j+i]!=0)
				{
					dp[j+i]=min(dp[j+i],dp[j]+sum[i]);
				}
				else dp[j+i]=dp[j]+sum[i];
			}
		}
	}
	printf("%d",dp[n]);
	return 0;
}
```
### 如有不足，忘dalao不吝赐教。

---

## 作者：无心揽青丝 (赞：1)

## Simplified questions
```cpp
Flowering shrubs以及他的N(1<=N<=2,500)头奶牛打算过一条河，
他们划船过河，在整个渡河过程中，Fs必须始终在木筏上。
在这个基础上，木筏上的奶牛数目每增加1，
Fs把木筏划到对岸就得花更多的时间。 当FJ一个人坐在木筏上，
他把木筏划到对岸需要K(1<=K<=1000)分钟。当木筏搭载的奶牛数目从i-1增加到i时，Fs得多花M[i](1<=M[i]<=1000)分钟才能把木筏划过河。
那么，Fs最少要花多少时间，才能把所有奶牛带到对岸呢？
当然，这个时间得包括Fs一个人把木筏从对岸划回来接下一批的奶牛的时间。
```
## Input
```cpp
* 第1行: 2个用空格隔开的整数：N和K
* 第2..N+1行: 第i+1为1个整数：M[i]
```
## Output
```cpp
* 第1行: 输出1个整数，为Fs把所有奶牛都载过河所需的最少时间
```
## Mentality
```cpp
很简单的DP对吧，直接O(n^2)递推就行了
考虑DP
运送n头奶牛所用的最短时间=min（先送k头的最短时间+再送剩下n-k头的最短时间+m）
令dp[i]为运送i头牛的最短时间
很显然初始化dp数组即为前缀和
然后优秀的O(n^2)递推即可
```
## Key Code
```cpp
for(int i=1;i<=n;i++)
for(int j=1;j<=i;j++)
dp[i]=min(dp[i],dp[j]+dp[i-j]+m);
```
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[2550];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    dp[0]=m;
    for(int i=1;i<=n;i++)
    {
        int x;
        scanf("%d",&x);
        dp[i]=x+dp[i-1];
    }
    for(int i=1;i<=n;i++)
    for(int j=1;j<=i;j++)
        dp[i]=min(dp[i],dp[j]+dp[i-j]+m);
    printf("%d",dp[n]);
    return 0;
}
```

---

## 作者：Baker (赞：1)

     看到先前有人要完全背包的题解，我这里就来一发。
     其实我一开始思路是贪心，即加入多加如一只牛比送两次的时间要少，那么就加入，否则不加。
     信心满满提交，只有样例分……
     于是我重新思考，发现这题可以化归为这样一个完全背包问题问题：
   要送的总牛数就是背包的总大小，这里我用了一个前缀和，f[i]表示运送i头牛总共需要的时间，算进FJ自己的一来一回。那么就可以从f数组中拼出n来，剩下要做的是维护最小值。
      最终输出dp[n]-m,因为最后不需要再回去了。
       
    program river_plus;
     var i,j,k,mm,n:longint;
      dp:array[0..2500] of int64;
      m,f:array[1..2500] of int64;
    function min(a,b:int64):int64;
    begin
      if a<b then exit(a);
      exit(b);
    end;
    begin
    read(n,mm);
    for i:=1 to n do
       read(m[i]);
    f[1]:=m[1]+2*mm;
    for i:=2 to n do
      f[i]:=m[i]+f[i-1];
    dp[0]:=0;
    for i:=1 to n do dp[i]:=maxlongint;
    for i:=1 to n do
      for j:=1 to n do
        if j>=i then dp[j]:=min(dp[j-i]+f[i],dp[j]);
    write(dp[j]-mm);
    end.

```


---

## 作者：ws_fuweidong (赞：1)

其实就是一个完全背包

f[i]表示装i头牛的花费。


```cpp
f[j]=min(f[j],f[j-i]+sum[j-i]+m) (i<=j) 
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
int n,m,sum[2501];
int f[2501];
int main(){
    scanf("%d%d",&n,&m);
    sum[0]=m;
    for (int i=1,a;i<=n;i++){
        scanf("%d",&a);
        sum[i]=sum[i-1]+a;
    }
    memset(f,127,sizeof(f));
    f[0]=0;
    for (int i=1;i<=n;i++)
    for (int j=i;j<=n;j++){
        f[j]=min(f[j],f[j-i]+sum[i]+m);
    }
    printf("%d",f[n]-m);
    return 0;
}
```

---

## 作者：田阙西 (赞：1)

其实是可以用完全背包解的：

体积：牛的条数n

价值：i

价格：m_i（预处理后的）

最后直接输出f[n]，不可以取1——n中最大值

就酱

```
#include<cstdlib>
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;
int n,m;
int w[2510],f[2510];
int main()
{
	scanf("%d%d",&n,&m);
	w[0]=2*m;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&w[i]);
		w[i]+=w[i-1];
	}
	memset(f,126,sizeof(f));
	f[0]=0;
	for(int i=1;i<=n;i++)
	for(int j=i;j<=n;j++)
	f[j]=min(f[j],f[j-i]+w[i]);
	printf("%d",f[n]-m);
	return 0;
}
```

---

## 作者：gold_bread (赞：0)

#### 题目描述
Farmer John以及他的N(1 <= N <= 2,500)头奶牛打算过一条河，但他们所有的渡河工具，仅仅是一个木筏。 由于奶牛不会划船，在整个渡河过程中，FJ必须始终在木筏上。在这个基础上，木筏上的奶牛数目每增加1，FJ把木筏划到对岸就得花更多的时间。 当FJ一个人坐在木筏上，他把木筏划到对岸需要M(1 <= M <= 1000)分钟。当木筏搭载的奶牛数目从i-1增加到i时，FJ得多花M_i(1 <= M_i <= 1000)分钟才能把木筏划过河（也就是说，船上有1头奶牛时，FJ得花M+M_1分钟渡河；船上有2头奶牛时，时间就变成M+M_1+M_2分钟。后面的依此类推）。那么，FJ最少要花多少时间，才能把所有奶牛带到对岸呢？当然，这个时间得包括FJ一个人把木筏从对岸划回来接下一批的奶牛的时间。  

首先，我们可以定义dp[i]表示把i头牛送到对岸的最短时间。  

我们可以枚举最后一次运到对岸的有几头牛，设为j，然后dp方程就很好列了：  

dp[i] = min(dp[i], dp[j] + s[j] + 2 * m)  

s[j]为m[1..j]的和，即j头牛的总时间，s[j]加上FJ的时间m是划到对岸的总时间，再加上的m是FJ回来的时间。

下面上代码
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=2510;
int dp[maxn], s[maxn];
int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i=1, x; i<=n; ++i) {
        scanf("%d", &x); 
        s[i]=s[i-1]+x; //计算出s[i]
    }
    memset(dp, 0x7f, sizeof(dp)); //一开始无限大
    dp[0]=0; //0头牛需要的时间肯定是0
    for (int i=1; i<=n; ++i) 
        for (int j=1; j<=i; ++j) 
            dp[i]=min(dp[i], dp[i-j]+s[j]+2*m);
    printf("%d", dp[n]-m); //最后要减去m是因为最后一次划船不需要回来
    return 0;
}
```

---

## 作者：lizehan888 (赞：0)

For pascal党

其实就是一个01背包（你说数论也可以）。w数组累计前i个数直接送去再回来的花费。

f数组存最小花费。

易证： f[i,j]:=min(f[i],f[i-j]+w[j]);

注：本题有坑，输出\_f[n]-m\_（！！！！！！！！！！！）


```cpp
uses math;//迷之数学库
var i,a,n,j,k,m:longint;
  f,w:array[0..1000]of longint;
begin
   readln(n,m);
   fillchar(f,sizeof(f),$7f);
   w[0]:=2*m;
   for i:=1 to n do
        begin
            readln(a);  
                        //累加w[i];
        end;
  f[0]:=0;
//自己想
         f[i]:=min(f[i],f[i-j]+w[j]); 
    writeln(f[n]-m);
end.
```

---

## 作者：东林桂香 (赞：0)

这就是一个典型的动态规划题

要抓住题的细节

很容易就得出转移方程

f[i]=min(f[i],f[j]+cost[i-j]);（i>j）

代码如下：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
int f[2550],n,m;
int cost[2550];
int main()
{
    scanf("%d%d",&n,&m);
    cost[0]=2*m;
    for(int i=1;i<=n;i++)
    {
        int o;
        scanf("%d",&o);
        cost[i]=cost[i-1]+o;
    }
    memset(f,127,sizeof(f));
    for(int i=1;i<=n;i++)
    {
        f[i]=cost[i];
        for(int j=0;j<=i-1;j++)
            f[i]=min(f[i],f[j]+cost[i-j]);
    }
    printf("%d",f[n]-m);
    return 0;
}
加油共勉！！！
```

---

## 作者：Mychael (赞：0)

动态规划方法之多，为之惊叹。


帮楼下挑明来，就是区间DP

【不过完全背包也能做也是很佩服】


dp[i]表示i头牛过河的最优花费，cost[i]为累加数组，表示i头牛一起过河时的费用【注意：cost[0]=2\*M，要算上空船】


然后自然而然地想到了区间DP：

对于dp[i],寻找一个j<i，使得dp[j]+cost[i-j]最小，这样子就把状态转移方程写出来了：


**dp[i]=min(dp[j]+cost[i-j]); 【j∈[0,i-1]】**

下面是代码，用了快速读入：




```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=2505,INF=2000000000;
int dp[maxn],cost[maxn];
int read()                                  //小小的快速读入
{
    int out=0;
    char c=getchar();
    while(c<48||c>57) c=getchar();
    while(c>=48&&c<=57)
    {
        out=out*10+c-48;
        c=getchar();
    }
    return out;
}
int main()
{
    int N=read(),M=read();
    cost[0]=2*M;
    for(int i=1;i<=N;i++) cost[i]=cost[i-1]+read();          //求i头牛一起过河的花费
    dp[0]=0;
    for(int i=1;i<=N;i++)                                                 //区间DP
    {
        dp[i]=cost[i];
        for(int j=0;j<i;j++)
            dp[i]=min(dp[i],dp[j]+cost[i-j]);                        //状态转移，如上所述
    }
    cout<<dp[N]-M<<endl;                                              //最后一趟不用回去，所以减去M
    return 0;
}

```

---

## 作者：never_see (赞：0)

算法:用一个f[i]表示i头牛过河时的最优解。f[i]可以从f[j](1<=j<=i-1)转移过来，因为i头牛过河时，即使j头牛过河时加上这i-j头牛过河所需的时间。


注意：虽然看上去一样，但和楼下的是完全不一样的。


```cpp
#include<cstdio>
#include<algorithm>
#include<climits>//用于INT_MAX即int内的最大值
using namespace std;
#define MAXN 2501
int t[MAXN];
int f[MAXN];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&t[i]);//输入的时候处理一下，依题意可知,每加一头牛，时间就要加上
        t[i]+=t[i-1];//这一次和前一次的
    }
    for(int i=1;i<=n;i++)
    {
        t[i]+=2*m;//每次Fj要过河用的时间也要算到里面去
        f[i]=t[i];//初始化，便于比较直接i头过河还是先j头过河再i-j头过河好
    }
    for(int i=1;i<=n;i++)
    {
        int MIN=INT_MAX;
        for(int j=i-1;j>=1;j--)
            MIN=min(MIN,f[j]+t[i-j]);//找出最优解
        f[i]=min(f[i],MIN);
    }
    printf("%d",f[n]-m);//最后一次不要返回，所以不用Fj的一次m
    return 0;
}
```

---

