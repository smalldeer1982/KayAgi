# [USACO08JAN] Running S

## 题目描述

奶牛们打算通过锻炼来培养自己的运动细胞，作为其中的一员，贝茜选择的运动方式是每天进行 $n$ 分钟的晨跑。在每分钟的开始，贝茜会选择下一分钟是用来跑步还是休息。


贝茜的体力限制了她跑步的距离。更具体地，如果贝茜选择在第 $i$ 分钟内跑步，她可以在这一分钟内跑 $d_i$ 米，并且她的疲劳度会增加 $1$。不过，无论何时贝茜的疲劳度都不能超过 $m$。  

如果贝茜选择休息，那么她的疲劳度就会每分钟减少 $1$，但她必须休息到疲劳度恢复到 $0$ 为止。在疲劳度为 $0$ 时休息的话，疲劳度不会再变动。晨跑开始时，贝茜的疲劳度为 $0$ 。

还有，在 $n$ 分钟的锻炼结束时，贝茜的疲劳度也必须恢复到 $0$，否则她将没有足够的精力来对付这一整天中剩下的事情。

请你计算一下，贝茜最多能跑多少米。


## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$1\le n \le 10^4$，$1\le d_i \le 1000$，$1\le m \le 500$。

【样例说明】

贝茜在第 $1$ 分钟内选择跑步（跑了 $5$ 米），在第 $2$ 分钟内休息，在第 $3$ 分钟内跑步（跑了 $4$ 米），剩余的时间都用来休息。  
因为在晨跑结束时贝茜的疲劳度必须为0，所以她不能在第 $5$ 分钟内选择跑步。  
最终跑的总距离为 $9$。



## 样例 #1

### 输入

```
5 2
5
3
4
2
10
```

### 输出

```
9
```

# 题解

## 作者：今宵満月 (赞：57)

看到大家的题解都是“填表法”，在此奉上一篇独特的“刷表法”，供各位老哥参考~

状态是用f[i][j]表示，代表在第i分钟疲劳值为j时跑的最远距离。边界是f[1][0]=0, f[1][1]=d[1]。那么，~~状态转移方程~~（刘汝佳前辈曾经教导过我们，刷表法的事，能叫状态转移方程吗？）就是
```
f[i][0]=max(f[i][0], f[i-1][0]);//这一行一定一定要放在最前面，因为第三个方程只会更新到f[i+j][0]，无法继续向后更新
f[i+j][0]=max(f[i+j][0], f[i][j]);//在当前情况下休息的情况
f[i+1][j+1]=max(f[i+1][j+1], f[i][j]+d[i+1]);//在当前情况下不选择休息的情况
```
代码如下~
```cpp
#include<iostream>
#include<cstdio>
using namespace std;

int f[10510][510], n, m, d[10010];

int main() {
    scanf("%d%d", &n, &m);
    for(int i=1; i<=n; ++i) {
        scanf("%d", &d[i]);
    }
    f[1][1]=d[1];
    for(int i=1; i<=n; ++i) {
        for(int j=0; j<=min(i, m); ++j) {
            if(j==0)
                f[i][0]=max(f[i-1][0], f[i][0]);
            else
                f[i+j][0]=max(f[i+j][0], f[i][j]);
            f[i+1][j+1]=max(f[i+1][j+1], f[i][j]+d[i+1]);
        }
    }
    printf("%d", f[n][0]);
    return 0;
}
```

---

## 作者：Log_x (赞：30)

##动态规划

**【分析】**

设$f[i][j]$表示第$i$分钟疲劳值为$j$的最大距离。

根据题意有三种转移：

[1]、$f[i][0] = Max(f[i - j][j], f[i][0])$

表示第$i$分钟疲劳值为$0$则可由第$i - j$分钟疲劳值为$j$时选择休息$j$分钟转移过来。

[2]、$f[i][0] = Max(f[i - 1][0], f[i][0])$

表示疲劳值为$0$时，第$i$分钟仍可以选择休息。

[3]、$f[i][j] = Max(f[i - 1][j - 1] + D_i, f[i][j])$

表示第$i$分钟选择跑步，则疲劳值增加$1$，距离增加$D_i$

**【代码】**

```cpp
#include <iostream>
#include <cstdio>
 
using namespace std;
const int N = 1e4 + 5, M = 505;
int f[N][M], d[N], n, m;
  
inline void CkMax(int &x, const int &y) {if (x < y) x = y;}
inline int Min(const int &x, const int &y) {return x < y ? x : y;}
 
int main()
{
    scanf("%d%d", &n, &m); 
    for (int i = 1; i <= n; ++i) scanf("%d", &d[i]);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= Min(i, m); ++j)
         CkMax(f[i][0], f[i - j][j]);
        CkMax(f[i][0], f[i - 1][0]);
        for (int j = m; j >= 1; --j)
         CkMax(f[i][j], f[i - 1][j - 1] + d[i]);
    }
    printf("%d\n", f[n][0]); 
    return 0;
}
```

---

## 作者：D10s (赞：30)

dp思路前面的题解讲的都很清楚了，不过数组还可以优化到一维。

以F[i]表示从i处出发、疲劳度为零的最优值，则接下来有两种方案：

1.待在原地不走；

2.跑j分钟后再休息j分钟。

把i~i+j这一段路程用前缀和维护就好了。


```cpp
#include<cstdio>
int f[10005],s[10005];
int max(int a,int b) {return a>b?a:b;}
int main()
{
    int n,m,x;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&x),s[i]=s[i-1]+x;
    for(int i=n;i;i--)
    {
        for(int j=1;j<=m;j++)
        {
            if(2*j+i-1>n) break;
            f[i]=max(f[i],f[i+2*j]+s[i+j-1]-s[i-1]);
        }
        f[i]=max(f[i],f[i+1]);
    }
    printf("%d\n",f[1]);
    return 0;
}
}
```

---

## 作者：Miri (赞：23)

感谢@sszycss 大佬的帮助~

小芋头我的思路好像有点清奇……

解释一下状态转移方程

f[i][j]就是第is时奶牛的疲劳度是j，那么我们就可以就ta这1s是否休息进行讨论

如果休息的话，就要一休息到底，所以把疲劳度恢复成0所用的时间是i+j，恢复时走的距离是不变的，所以恢复完体力后所走的距离就是恢复体力前所走的距离。

那么状态转移方程1就出来啦：

                f[i+j][0]=max(f[i+j][0],f[i-1][j+1]);

那么如果选择走的话，就要增加1点疲劳度，第is所走的距离就应该是上f[上1s][1s的疲劳度]+这1s能走的距离

                f[i][j]=max(f[i][j],f[i-1][j-1]+pa[i]);

第三种情况，就是到了一直休息的情况，如果当前的疲劳度已经是0的话（j==0），情况可能是上1s在休息，这1s也在休息，那么

                f[i][j]=max(f[i][j],f[i-1][0]);

代码如下：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,m,pa[10001],f[10001][501];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1; i<=n; i++)
        scanf("%d",&pa[i]);
    for(int i=1; i<=n; i++)
        for(int j=m; j>=0; j--)
        {
            if(i+j<=n)  //如果在ns内不能把体力恢复为0就不符合了，舍去
                f[i+j][0]=max(f[i+j][0],f[i-1][j+1]);
            if(j==0)
                f[i][j]=max(f[i][j],f[i-1][0]);
            else
                f[i][j]=max(f[i][j],f[i-1][j-1]+pa[i]);
        }
    printf("%d",f[n][0]);
    return 0;
}
```

---

## 作者：空の軌跡 (赞：16)


~~新人题解，勿喷~~

#  算法：DP


- ###  数组说明

maxx[ ]表示当前时间的 疲劳值为0  时之前可行最大距离

qzh[ ]前缀和计算距离

-----

-  ###  第一层循环 ：循环每一分钟的选择

	从 0 开始 循环到 最后一分钟

	以此点为休息的最后一分钟，开始接下来的跑步



-----

 - ##  第二层循环 ：能在疲劳度内跑步并休息完后所达到的时刻（包含一分钟的滞留）
#### 注:

	向后推导的循环时每次递加 2

	#### 原因：
    
    若本分钟疲劳为0，若想下一分钟疲劳亦为0，则此分钟不可行动。并且与其连续两分钟疲劳度为0但是不行动，不如多走一分钟的路程并休息，这并不会影响下面的跑步，所以不行动的最多有一分钟，那一分钟则与上一分钟取最大值

	####	区间 ：

```
	j<=q+i&&j<=a 

	（q+i就是走到最大的疲劳度后并休息完的最大时间，a为总分钟数）

```

-----

- ##  状态转移方程（由本状态推导之后状态）

```cpp
	maxx[j]=max(maxx[j],maxx[i]+qzh[(j+i)/2]-qzh[i]);

	（计算最大距离）

	maxx[j+1]=max(maxx[j+1],maxx[j]);

	（此刻选择不行动，则取与上一分钟的最大距离）

```
-----
##  代码（简短的20行）
```
#include<iostream>
#include<algorithm>
using namespace std;
int s,maxx[10010],qzh[10010],a,b;
int main()
{
    cin>>a>>b;
    b=b<<1;qzh[0]=0;
    for(int i=1;i<=a;i++)
    {
        cin>>s;qzh[i]=qzh[i-1]+s;                         //求前缀和
    }
    for(int i=0;i<=a;i++)                                 //从0开始，0为跑步的起点
    for(int j=i;j<=b+i&&j<=a;j+=2)                        //递加2，判断两个数值
    {
        maxx[j]=max(maxx[j],maxx[i]+qzh[(j+i)>>1]-qzh[i]);//此刻刚休息完
        maxx[j+1]=max(maxx[j+1],maxx[j]);                 //此刻无疲劳且已滞留一分钟
    }
    cout<<maxx[a];                                        //输出结束时间的值
}
```

---

## 作者：Apro1066 (赞：10)

令$dp[i][j]$为第$i$分钟疲劳度为$j$时的最长距离。$j$的疲劳度要从$1$到$i$与$m$中取较小的一个。

我们可以分$2$种情况讨论：在疲劳度为$0$时；在疲劳度不为$0$时。

**1.当疲劳度为$0$时**

分$2$种状态，一种是当前状态（第$i$分钟疲劳度为$0$），即$dp[i][0]$；一种是上一秒疲劳度为$0$，这一秒疲劳度也为$0$的状态，即$dp[i-1][0]$。则：

$$dp[i][0]=max(dp[i][0],dp[i-1][0])$$

**2.当疲劳度不为$0$时**

前$1$秒跑的距离（此时疲劳度也少$1$）加上当前跑的距离。如果奶牛想休息，必须要一直休息到疲劳值为$0$。

如果接下来继续跑：

$$ dp[i][j]=max(dp[i][j],dp[i-1][j-1]+a[i])$$  

如果接下来想休息：

$$dp[i+j][0]=max(dp[i][j],dp[i+j][0])$$

```cpp
#include <stdio.h>
#include <iostream>
using namespace std;
int n,m,a[10001],dp[10502]/*max(i+j)=10000+500*/[1001],s;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	register int i,j;
	cin>>n>>m;
	for(i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	dp[1][0]=0;//临界条件 
	dp[1][1]=a[1];
	for(i=1;i<=n;i++)//枚举第i分钟 
	{
		dp[i][0]=max(dp[i][0],dp[i-1][0]);//情况1，疲劳度为0时 
		for(j=1;j<=min(i,m);j++)//情况2，疲劳度不为0时 
		{
			dp[i][j]=max(dp[i][j],dp[i-1][j-1]+a[i]);
			dp[i+j][0]=max(dp[i][j],dp[i+j][0]);
		}
	}
	cout<<dp[n][0]<<endl;;
	return 0;
}
```

---

## 作者：zyj_Orz (赞：9)

## DP题。

~~感觉绿题难度还是有点过了吧？~~

大致思路就是建一个二维数组dp【i】【j】表示第i分钟疲劳度为j跑的距离 

这时候就大致可以得出**动态转移方程**了，如下

------------
1.第i分钟从1至N枚举

------------
2.此时j疲劳度从1枚举至i与m中较小的一个。

------------
3.此时当第i分钟如果疲劳度想变为0，自然是选```前一秒疲劳度为0，自然这一秒疲劳度也为0的距离```或者```前j秒时跑的距离再休息j秒```中较大的一个。


------------
4.此时再次枚举j，自1枚举至m，此时dp【i】【j】则为```前1s跑的距离（此时疲劳度也少1）再加上跑这1s的距离```

------------


故状态转移方程代码如下：

```
 for(int i=1;i<=n;i++){
        for(int j=1;j<=min(i,m);j++) 
		dp[i][0]=max(dp[i][0],max(dp[i-1][0],dp[i-j][j]));
        for(int j=1;j<=m;j++) dp[i][j]=max(dp[i][j],dp[i-1][j-1]+a[i]);
    } 
```

最后输出dp【n】【0】则为正解。

------------


发现了吗？实际上代码很精简的。只要你有心，提高难度在你眼里都将是水题！


```
#include<bits/stdc++.h>
using namespace std;
int n,m,a[10002],ans,dp[10002][502];//dp[i][j]表示第i分钟疲劳度为j跑的距离 
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
	{
        for(int j=1;j<=min(i,m);j++) 
		dp[i][0]=max(dp[i][0],max(dp[i-1][0],dp[i-j][j]));
        for(int j=1;j<=m;j++) dp[i][j]=max(dp[i][j],dp[i-1][j-1]+a[i]);
    } 
    cout<<dp[n][0];
}
```

>PPS：这是@M_sea dalao給我们讲解的，深入浅出Orz

>PPPS：应该没有题解与这个相似吧？因为我们全机房都是听的M_sea dalao讲解的，所以可能机房会有与我相似的题解投上来QAQ

---

## 作者：yjxyjx (赞：4)

这道题是我点“相关题目”点出来的，~~没想到这么恶心（人工zz真™毒瘤）~~，

-----

这道题的关系有那么一些小乱，~~所以题解也会相应地有些**~~，但是，相信草稿，草稿是做题之本（手动滑稽），



设$f[i][j]$中的$i$表示：第$i$秒（在后面也会和$D[i]$中的$i$重合）;$j$表示：在第$i$秒时的疲劳值

在这个题目中，我们可以对每一秒到底是**跑步**还是**休息**进行讨论：

1. 当Bessie要休息的时候，是要一休息就**休息完剩下所有时间**的（因为：参见样例，我也是这样看懂的，~~我怎么这么毒瘤~~），所以在做的时候，**每一次**都要判断当前是否要**开始休息**直到结束，所以**把疲劳值恢复为0所需要的时间是j，加上i一定不能超过N**，然后，**恢复时走的距离是不变的**，所以，**恢复完体力后所走的距离就是恢复体力前所走的距离。**
   
   下面是相对应的dp方程：
   
   $f[i + j][0] = max(f[i + j][0], f[i - 1][j + 1])(i + j <= N)$

   p.s.1：这后面的$f[i - 1][j + 1]$为什么要$j + 1$呢？
   请仔细琢磨**恢复体力前**，也就是说（~~我胡扯的~~）：当前决定恢复体力时，体力为$j$，那么当初的体力就是$j + 1$了。
   
2.还是休息：
   
  如果到了一直休息的情况，那么如果当前的疲劳值（也就是$j$）为0的话，就可能是**上一秒在休息，这一秒也在休息**，那么：
  
  $f[i][j] = max(f[i][j], f[i - 1][0])$
  
3.~~就是我们喜闻乐见的~~跑步：
  
  第$i$秒走的距离就应该是$f[i - 1][j - 1]$（$[i - 1]$表示：**上一秒时**，$[j - 1]$表示:**疲劳值比现在少1时**（因为现在要**消耗1个点的疲劳值**）），
  
  相对应的状态转移方程是：
  
  $f[i][j]=max(f[i][j],f[i-1][j-1]+D[i])$
  
我终于讲完了所有的东西（我简直比****还毒瘤），接下来就直接上代码吧，~~累死我了qwq~~：

```
#include<bits/stdc++.h>

const int MaxN = 10000 + 100;
const int MaxM = 500 + 50;

long long N, M, D[MaxN], ans[MaxN][MaxM]; 
//这里的ans数组和上面的f是一样的
int main() {
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; ++i) scanf("%d", &D[i]);
    
    for (int i = 1; i <= N; ++i) {
    //这里不用再加物品的循环，因为i循环既代表了时间，又代表了D数组 
        for (int j = M; j >= 0; --j) {
        //我的心情告诉我要逆序（滑稽）
            if (i + j <= N) {
                ans[i + j][0] = std::max(ans[i + j][0], ans[i - 1][j + 1]);
            }
            if (j == 0) {
                ans[i][j] = std::max(ans[i][j], ans[i - 1][0]);
            } else {
                ans[i][j] = std::max(ans[i][j], ans[i - 1][j - 1] + D[i]);
            }
        }
    }
    
    printf("%d", ans[N][0]);
    return 0;
}

```
  
  



---

## 作者：zhangbubu (赞：3)

改了好久，终于把这个题做完了.....

所以说准备发一篇容易理解的题解：

题解中大部分都是用的二维，我觉得用三维更好理解一些：


**f[i][j][0/1]** 奶牛在第i分钟，疲劳值值位j时能跑的最远距离 （0表示休息，1表示运动）；


注释十分的详尽= =

```cpp
# include<iostream>
# include<cstdio>
# include<cstring>
#define ge getchar()
#define is isdigit(ch)
#define ini inline int
#define inv inline void
using namespace std;
int n,m;
int k[10001];
int f[10001][501][2];
ini read()
{
    int x=0;
    char ch=ge;
    while(!is)
    ch=ge;
    while(is)
    {
        x=x*10+ch-48;
        ch=ge;
    }
    return x;
}
int main()
{
 ****
    n=read(),m=read();
    for(int i=1;i<=n;i++)
      k[i]=read();
    for(int i=1;i<=n;i++)
      {
	  for(int j=0;j<=min(i,m);j++)
        {
            if(j) //要有疲劳值才能跑呀= = 
             f[i][j][1]=max(f[i][j][1],f[i-1][j-1][1]+k[i]/*上一分钟也在跑*/); 
             
            if (j==1) f[i][j][1]=max(f[i][j][1],f[i-1][j-1][0]+k[i]);
            // 这里是个特殊的情况 当j=1时，j-1=0，此时从 上一分钟不跑 的情况也可以转移 
			  
			  f[i][j][0]=max(f[i-1][j+1][0],f[i-1][j+1][1]);
			// 这一分钟疲劳为j时不跑，可以从 上分钟跑（也就代表从这一分钟开始休息且一直到疲劳值为0） 和 上一分钟不跑 转移 
			
			f[i][0][0]=max(f[i][0][0],max(f[i-j][j][0],f[i-j][0][0]));
			//  每次休息必须时疲劳值位0，所以在每次疲劳值为0时，可以从 之前某一疲劳值开始休息 和 之前疲劳值就已经是0 两个情况转移。
			 
        }
        
   
        
        
}
    printf("%d",f[n][0][0]);
    return 0;
}
```

 


---

## 作者：y2823774827y (赞：3)

注意点

1. 在疲劳度不为0时，只存在+或-的情况，
一旦-，疲劳度必须归0后才能继续跑（程序里体现）
1. 在疲劳度为0时，则疲劳度可以不变或+

定义dp[i][j]:第i分钟疲劳度为j时已经跑的最大距离
```cpp
# include<cstdio>
using namespace std;
int n,m; int a[10001],dp[10501][501];//10501:i(<=10000)+j(<=500)
inline int MAX(int g1,int g2){
	return g1>=g2?g1:g2;
}
inline int MIN(int g1,int g2){
	return g1<=g2?g1:g2;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
	    scanf("%d",a+i);
	for(int i=1;i<=n;++i){//第i分钟 
		dp[i][0]=MAX(dp[i][0],dp[i-1][0]);//某刻休息,dp[i][0]已有值:也可从上分钟继续休息 
	    for(int j=1;j<=MIN(i,m);++j){//缩小范围 
	        dp[i][j]=dp[i-1][j-1]+a[i];//第一点 
	        dp[i+j][0]=MAX(dp[i+j][0],dp[i][j]);//第一点 
	    }
	}
	printf("%d",dp[n][0]);
	return 0;
}/*
5 2
5
3
4
2
10
*/
```

---

## 作者：kkxhh (赞：3)

首先我们定义 **p[i][j]** 为在 **i** 时刻疲劳值为 **j** 时的最长跑步距离。可以想象，最终答案在 **p** 里的路径一定只有**右上、左下，右**三个方向，于是我们在转移的时候就轻松了很多，当 **j>0** 时 **p[i][j]** 直接由 **p[i-1][j-1]** 转移而来，而当**j=0**时则一直朝左上方向搜索找到一个最大的。需要注意的是 **p[i][0]** 除了可能从它的左上角转移过来，也可能会从它的右边，也就是 **p[i-1][0]** 转移过来，就像样例中的情况一样。那么 **p[i][0]** 有没有可能会从 **p[i-2][0]** 或者更前的位置转移过来呢？显然不会，因为这个时候你完全可以多跑几步。

代码如下

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

int n,m,d[10010],p[10010][510]={0};

inline int read(){
    int num=0,k=1; char c=getchar();
    while(c>'9' || c<'0') k=(c=='-')?-1:k,c=getchar();
    while(c>='0' && c<='9') num=(num<<3)+(num<<1)+c-'0',c=getchar();
    return num*k;
}

int main(){
    n=read(); m=read();
    for(int i=1;i<=n;i++) d[i]=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) p[i][j]=p[i-1][j-1]+d[i];
        p[i][0]=p[i-1][0];
        for(int j=i-1;j>=1 && i-j<=m;j--) p[i][0]=max(p[i][0],p[j][i-j]);
    }
    printf("%d",p[n][0]);
    return 0;
}
```

---

## 作者：drywwltu (赞：2)

本蒟蒻用dp写的只能拿90分，所以只好用记忆化爆搜过了这道题。
记忆化爆搜和dp非常像，而且可以改成dp。
下面代码
```cpp
#include <iostream>
#include <climits>
#include <cstdio>

const int N_MAX = 10000 + 1;
const int M_MAX = 1000 + 1;

int n, m, d[N_MAX],f[N_MAX][M_MAX];

int dfs(int x,int y){//常规爆搜用的是void，非常浪费，所以用int
	if(x > n - y + 1) return INT_MIN;//不合法答案 
	if(x == n + 1){
		if(!y) return 0;//合法答案，return 0不影响加法 
		return INT_MIN;
	}
	if(y + 1 <= m) f[x][y] = std::max(f[x][y],(f[x + 1][y + 1]?f[x + 1][y + 1]:dfs(x + 1,y + 1))+d[x]);//跑 
	if(y && x + y <= n + 1) f[x][y] = std::max(f[x][y],(f[x + y][0]? f[x + y][0]:dfs(x + y , 0)));//休息到底 
	else f[x][y] = std::max(f[x][y],(f[x + 1][0] ? f[x + 1][0] : dfs(x + 1,0)));//接着休息 
	return f[x][y]; 
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++){
		scanf("%d",&d[i]);
	}
	printf("%d\n",dfs(1,0));
	return 0;
}
```

---

## 作者：brealid (赞：1)

发一份思路清奇的题解

思路清奇之处：逆推法（即：解决“从哪里来”的问题）

$$f[i][j]=\begin{cases}f[i-1][j - 1]+D[i] &(j > 0)\\ \max{\{f[i-1][j],\ \max{\{f[k][i-k]}\}\}}&(j=0)\end{cases}$$

（应该比较好理解）

$i$ 表示第几分钟， $j$ 表示当前疲劳度。

然后代码应该比较容易得出。

答案即 $f[n][0]$

```cpp
/*************************************
 * @problem:      P1353 [USACO08JAN]跑步Running.
 * @user_id:      63720.
 * @user_name:    Jomoo.
 * @time:         2019-11-16.
 * @language:     C++.
 * @upload_place: Luogu.
*************************************/ 

#include <bits/stdc++.h>
using namespace std;

typedef signed char          int8;
typedef unsigned char       uint8;
typedef short                int16;
typedef unsigned short      uint16;
typedef int                  int32;
typedef unsigned            uint32;
typedef long long            int64;
typedef unsigned long long  uint64;

template <typename Int>
inline Int read()       
{
    Int flag = 1;
    char c = getchar();
    while ((!isdigit(c)) && c != '-') c = getchar();
    if (c == '-') flag = -1, c = getchar();
    Int init = c & 15;
    while (isdigit(c = getchar())) init = (init << 3) + (init << 1) + (c & 15);
	return init * flag;
}

template <typename Int>
inline Int read(char &c)       
{
    Int flag = 1;
    c = getchar();
    while ((!isdigit(c)) && c != '-') c = getchar();
    if (c == '-') flag = -1, c = getchar();
    Int init = c & 15;
    while (isdigit(c = getchar())) init = (init << 3) + (init << 1) + (c & 15);
	return init * flag;
}

template <typename Int>
inline void write(Int x)
{
    if (x < 0) putchar('-'), x = ~x + 1;
    if (x > 9) write(x / 10);
    putchar((x % 10) | 48);
}  

template <typename Int>
inline void write(Int x, char nextch)
{
    write(x);
    putchar(nextch);
}

int n, m, d[10007];
int f[10007][507] = {0};

int main()
{
    n = read<int>();
    m = read<int>();
    for (int i = 1; i <= n; i++) d[i] = read<int>();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            f[i][j] = max(f[i][j], f[i - 1][j - 1] + d[i]);
        }
        f[i][0] = f[i - 1][0];
        for (int j = 1; j < i; j++) {
            f[i][0] = max(f[i][0], f[j][i - j]);
        }
    }
    write(f[n][0]);
    return 0;
}
```

CSP-S2 2019 RP++

---

## 作者：huanghu996 (赞：1)

## 这是一个我打表想出来的办法 ##

## 实在不了解时打表就理解的

f[i][j] i表示第i分钟 j表示当前疲劳值

### 为什么要有j这个状态

首先j是一个有限状态，j可以做f的状态。

状态转移必须知道上一个状态的j。

```cpp
#include<iostream>
using namespace std;
int n,m,d[10005];
int f[10005][505];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&d[i]);
    }
    for(int i=1;i<=n;i++)
    {
        int top=min(i,m);  //这个是为了防止越界
        for(int j=0;j<=top;j++)
        {
            if(j==0) //j=0时不能由上一个状态跑到
            {
                f[i][j]=max(f[i][j],f[i-1][j]);
                for(int k=1;k<=top;k++)
                f[i][j]=max(f[i][j],f[i-k][j+k]);  //但j=0是可以由上一个状态休息到，但我不知道是哪一个状态，所以用k。
            }
            else
            {
                if(j==top)
                {
                    f[i][j]=max(f[i][j],f[i-1][j-1]+d[i]);//j=最大值时上一个状态只能是跑到j
                }
                else
                {
                    f[i][j]=max(f[i][j],f[i-1][j-1]+d[i]);;//j！=最大值时上一个状态能是跑到j
                }
            }
        }
    }
    cout<<f[n][0];//输出你要求的状态
}
```

---

## 作者：Mr_Li (赞：1)

楼上只给代码，看着太麻烦了，我给个方程：

           max{f[i-1][0],f[j][i-j]}(j<i)    j=0

f[i][j]=

           f[i-1][j-1]+d[i]                     0<j<=m

初值f[1][0]=0,f[1][1]=d[1],1<i<n.

时间复杂度O(mn).


---

## 作者：dy0607 (赞：1)

来抢沙发。。。

十分简单的动规，从后往前推

用1表示休息，0表示跑步

注意一休息就必须休息到体力恢复满

另外第n分钟不用管，只能休息

转移方程自己看，难度不大

```cpp

#include<cstdio>
#define max(x,y) (x>y?x:y)
#define For(i,j,k) for(int i=j;i<=k;i++)
#define Fori(i,j,k) for(int i=j;i>=k;i--)

const int maxn=10000+10,maxm=500+10;

int f[maxn][maxm][2],d[maxn];

int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    For(i,1,n-1)scanf("%d",&d[i]);
    Fori(i,n-1,1)
        For(j,0,m)
            if(!j){
                f[i][j][0]=max(f[i+1][j][0],f[i+1][j+1][0]+d[i]);
                f[i][j][1]=max(f[i+1][j][1],f[i][j][0]);
            }
            else if(j<=n-1-i){
                f[i][j][0]=max(f[i+1][j+1][0]+d[i],f[i+1][j-1][1]);
                f[i][j][1]=f[i+1][j-1][1];
            }
    printf("%d",f[1][0][0]); 
    return 0;
}
[\codec]


---

## 作者：ariyy (赞：0)

用$dp[i]$表示在$i$点最多跑多远并休息完毕

很容易想到维护$i$点前$2*j$段距离（因为到i点必须休息完） 即$i-2*j$到$i-j-1$跑步，$i-j$到$i-1$休息。

所以考虑前缀和维护 即如果$dp[i-2*j]+s[i-j-1]-s[i-2*j-1]$比$dp[i]$更优 即更新$dp[i]$ 

需要注意的一点是 我们只是更新了与i点相邻的2*j段距离，而存在再这之前跑步，而之后一直休息的情况比现在的状态更优，所以为了让$dp[i]$最优，在枚举完j之后 我们要让$dp[i]$与$dp[i-1]$取$max$，即第$i$个点休息，最大方案和$dp[i-1]$一样。
代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline int read()
{
    char ch=getchar();int w=1,s=0;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){s=(s<<1)+(s<<3)+ch-48;ch=getchar();}
    return s*w;
}
int n,m,a,s[10002],f[10002],i,j;//f代表在第i-1个点休息完，在第i个点准备继续跑的最优答案
int main()
{
    n=read(),m=read();
    for(i=1;i<=n;i++) a=read();s[i]=s[i-1]+a;
    for(i=1;i<=n+1;i++){
        for(j=1;j<=i/2;j++){
            if(j<=m)f[i]=max(f[i],f[i-2*j]+s[i-j-1]-s[i-2*j-1]);
        }
        f[i]=max(f[i],f[i-1]);
    }
    cout<<f[n+1];//f[n+1]代表在第n个点休息完的答案，即最终答案
}
```


---

## 作者：crashed (赞：0)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.org/problem/P1353)看题目。
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;一看就是$DP$呀。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;定义状态：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$DP(i, j)$：到第$i$分钟，疲劳值为$j$的最大跑动距离。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;转移很容易看出来。根据题意，如果当前疲劳值不为$0$，则当前必然跑动；否则枚举开始休息的时间。对于持续休息的情况，我们可以让$DP(i,0)$的初值赋为$DP(i-1, 0)$。
# 代码
```cpp
#include <cstdio>
#include <cstring>

const int MAXN = 10005, MAXM = 505;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar(); int f = 1;
	while( s < '0' || '9' < s ){ f = 1; if( s == '-' ) f = -1; s = getchar(); }
	while( '0' <= s && s <= '9' ){ x = ( x << 3 ) + ( x << 1 ) + s - '0', s = getchar(); }
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ), x = -x; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MAX( const _T a, const _T b )
{
	return a > b ? a : b;
}

template<typename _T>
_T MIN( const _T a, const _T b )
{
	return a < b ? a : b;
}

int DP[MAXN][MAXM];
int D[MAXN];
int N, M;

int main()
{
	read( N ), read( M );
	for( int i = 1 ; i <= N ; i ++ ) read( D[i] );
	memset( DP, 0xc0, sizeof( DP ) );
	DP[0][0] = 0;
	for( int i = 1 ; i <= N ; i ++ )
	{
		DP[i][0] = DP[i - 1][0];
		for( int j = 1 ; j <= i && j <= M ; j ++ )
			DP[i][0] = MAX( DP[i][0], DP[i - j][j] );
		for( int j = 1 ; j <= M ; j ++ )
			DP[i][j] = MAX( DP[i][j], DP[i - 1][j - 1] + D[i] );
	}
	write( DP[N][0] ), putchar( '\n' );
	return 0;
}
```

---

## 作者：Y_B_Y (赞：0)

由于本人过于蒟蒻,dp是不可能dp的,于是这里用了记忆化搜索

#### 记忆化搜索主要就是边界条件要处理好,不然自己都不知道怎么错的 ~~(血与泪的教训)~~

- 用jy[x][y]表示在第x分钟后与疲劳值为y时能跑的最大距离

- 其中jy[n][0]=0,jy[n][1]=0,jy[n+1][0]=0(因为当第n分钟时只能选择休息, 第n+1分钟表示已经跑完, 疲劳值必须为0, 都不会增加跑的距离)

- jy[n][2~m+1]与jy[n+1][1~m+1]都等于-100000000(表示不可以)



------------

#### 然后就是处理跑和休息了:

- 跑就搜索下一分钟,疲劳加一的情况的返回值再加上跑的距离(假设得到值为a)

- 休息的话就休息y(表示疲劳值)分钟,如果y==0就休息一分钟(用x+max(y,1)),也就是搜索分钟+max(1,y)疲劳值为零的情况的返回值(假设得到值为b)

- 在a,b中选较大值作为自己的返回值

搜到边界条件时,层层返回自己的值最后到search(1,0)再赋值给答案,输出



------------

### 完整代码:

```
#include<bits/stdc++.h>
#define search sea//因为有一个STL中的函数是search,所以下面打的是search实际上是sea(看得舒服)
using namespace std;
const int inf=100000000;
long long jy[10001][501],d[1010001],n,m,ans;//d[i]表示第i分钟跑的距离,ans为答案
long long search(int x,int y)//表示在第x分钟后与疲劳值为y时能跑的最大距离
{
	if(jy[x][y]==-1)//表示还未搜过
	{
		long long b=-inf;//inf=100000000,因为如果下面两个条件(if语句)都不满足那么jy[x][y]就为-100000000表示不可以
		if(x+max(1,y)<=n+1)  b=max(b,search(x+max(1,y),0));//休息,题目说一定要休息到0且当疲劳值为0时也可以休息所以用max(1,y);
		if(y+1<=m&&x+1<=n+1) b=max(b,search(x+1,y+1)+d[x]);//跑,x+1和上面的x+max(1,y)要小于n+1是因为可以直接跑到或休息到结束
		jy[x][y]=b;//b为休息和跑之中的较大值
	}
	return jy[x][y];//返回这个值
}
int main()
{
	cin>>n>>m;//输入总时间与最大疲劳值
	memset(jy,-1,sizeof(jy));//初始化
	jy[n][1]=0;//初始化
	jy[n+1][0]=0;//初始化
	jy[n][0]=0;//初始化
	for(int p=1;p<=2*m;p++) jy[n][p+1]=-inf,jy[n+1][p]=-inf;//初始化
	for(int p=1;p<=n;p++) cin>>d[p];//输入跑的距离
	ans=search(1,0);//从第一分钟,0疲劳开始
	cout<<ans;//输出
	return 0;
}
```



---

## 作者：sleepyNick (赞：0)

**P党的福利**

比较基础的dp，方程是比较好推的。

用dp[i,j]表示第i分钟，疲劳度为j的最大跑步距离

枚举时间i（从1到n）

1、dp[i,0]:=dp[i-1,0]    (赋初值)

2、枚举时间j(从1到m)看看休息了段时间的情况

如果i>=j,那么dp[i,0]:=max(dp[i,0],dp[i-j,j])

然后dp[i,j]:=max(dp[i,j],dp[i-1,j-1]+a[i]);

最后输出是n分钟，疲劳度为0的情况，即dp[n,0]

我觉得程序还是比较好理解的：



```cpp
uses math;
var n,m,i,j:longint;
a:array[0..100000] of longint;
f:Array[0..10000,0..500] of longint;    //习惯，不超内存时，定义尽量开大
begin
    readln(n,m);
    for i:=1 to n do
        readln(a[i]);
    for i:=1 to n do
        begin
            f[i,0]:=f[i-1,0];     //初始
            for j:=1 to m do
                begin
                    if i>=j
                        then f[i,0]:=max(f[i,0],f[i-j,j]);
                    f[i,j]:=max(f[i,j],f[i-1,j-1]+a[i]);      //浅显的方程
                end;
        end;
    writeln(f[n,0]);    //输出第n分钟0疲劳度
end.

```

---

