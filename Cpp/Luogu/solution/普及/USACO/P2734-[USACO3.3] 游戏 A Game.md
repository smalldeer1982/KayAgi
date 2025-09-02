# [USACO3.3] 游戏 A Game

## 题目背景

有如下一个双人游戏：$N (2 \leq N \leq 100)$ 个正整数的序列放在一个游戏平台上，游戏由玩家 $1$ 开始，两人轮流从序列的任意一端取一个数，取数后该数字被去掉并累加到本玩家的得分中，当数取尽时，游戏结束。以最终得分多者为胜。

## 题目描述

编一个执行最优策略的程序，最优策略就是使玩家在与最好的对手对弈时，能得到的在当前情况下最大的可能的总分的策略。你的程序要始终为第二位玩家执行最优策略。

## 说明/提示

题目翻译来自 NOCOW。

USACO Training Section 3.3

## 样例 #1

### 输入

```
6 
4 7 2 9 5 2```

### 输出

```
18 11```

# 题解

## 作者：「QQ红包」 (赞：59)

题解by：redbag

经典的区间型动态规划的题。

状态只有2种：从左边拿和从右边拿。

假设当前状态a1,a2,a3,a4,a5，如果第一个人选最左边的，则问题转化为四个数a2,a3,a4,a5，然后第二个人先选，由于题目说第二个人方案也最优，所以选的也是最优方案，即f[i+1][j]；先选右边同理。

f[i][j]表示i~j区间段第一个人选的最优方案。

所以dp转移方程为：f[i][j]=max{ sum[i+1][j]-f[i+1][j]+a[i](先选左边，i~j区间段的数字和减去另一个玩家的得分即为自己的得分。)，sum[i][j-1]-f[i][j-1]+a[j](先选右边) }

sum[i][j]其实就等于sum[1][j]-sum[1][i-1],于是我们用一个s数组，s[i]表示前1~i个数的和，就好了。

所以dp转移方程也可写成f[i][j]=max((s[j]-s[i-1])-f[i+1][j],(s[j]-s[i-1])-f[i][j-1]);

根据dp转移方程我们可以发现，要得到状态f[i][j],必须要得到状态f[i+1][j]和f[i][j-1]。然后我们就可以写出程序了。

 
还是很快的。

```cpp
USER: lanxuan yi [ylx14271]
TASK: game1
LANG: C++

Compiling...
Compile: OK

Executing...
   Test 1: TEST OK [0.000 secs, 4220 KB]
   Test 2: TEST OK [0.000 secs, 4220 KB]
   Test 3: TEST OK [0.000 secs, 4220 KB]
   Test 4: TEST OK [0.000 secs, 4220 KB]
   Test 5: TEST OK [0.000 secs, 4220 KB]
   Test 6: TEST OK [0.000 secs, 4220 KB]
   Test 7: TEST OK [0.000 secs, 4220 KB]
   Test 8: TEST OK [0.000 secs, 4220 KB]
   Test 9: TEST OK [0.000 secs, 4220 KB]
   Test 10: TEST OK [0.000 secs, 4220 KB]
   Test 11: TEST OK [0.000 secs, 4220 KB]
   Test 12: TEST OK [0.000 secs, 4220 KB]
   Test 13: TEST OK [0.000 secs, 4220 KB]
   Test 14: TEST OK [0.000 secs, 4220 KB]
   Test 15: TEST OK [0.000 secs, 4220 KB]
   Test 16: TEST OK [0.000 secs, 4220 KB]

All tests OK.

```
```cpp
/*
ID: ylx14271
PROG: game1
LANG: C++     
*/
#include<set>  
#include<map>  
#include<list>  
#include<queue>  
#include<stack>  
#include<string>  
#include<math.h>  
#include<time.h>  
#include<vector>  
#include<bitset>  
#include<memory>  
#include<utility>  
#include<stdio.h>  
#include<sstream>  
#include<iostream>  
#include<stdlib.h>  
#include<string.h>  
#include<algorithm> 
#define LL unsigned long long   
using namespace std;
int n,i,j; 
int a[101];//存数
int f[101][101];
//f[i][j]表示取i~j这个区间段player1最高得分 
int s[101];//s[i]表示a[1]~a[i]的和  
int main() 
{
    freopen("game1.in","r",stdin);
    freopen("game1.out","w",stdout);
    scanf("%d",&n);
    for (i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);//读入 s
        s[i]=s[i-1]+a[i];//求和 
        f[i][i]=a[i];//初始化 
    }
    //表示a[i]~a[j]的和的方法：s[j]-s[i-1]
    for (i=n-1;i>=1;i--)
        for (j=i+1;j<=n;j++)
            f[i][j]=max((s[j]-s[i-1])-f[i+1][j],
            (s[j]-s[i-1])-f[i][j-1]);
    printf("%d %d\n",f[1][n],s[n]-f[1][n]);
    return 0;
}
```

---

## 作者：Kinandra (赞：21)

看了好像都是DP的做法, 我发一个贪心的做法, 目前还不会证明, 欢迎大家一起讨论证明(或**证伪**).

考虑剩$3$个数$a_1, a_2, a_3$且$a_2>a_1,a_2>a_3$, 那么先手能比后手多取到$a_1+a_3-a_2$, 我们于是我们将形如$a_i>a_{i+1}, a_i>a_{i-1}$的缩成一个数$a_{i+1}+a_{i-1}-a_i$,**反复操作**直到$\exists j,s.t.\forall i<j,a_{i+1}< a_i$且$\forall i>j,a_{i-1}< a_{i}$,即函数变为以$j$为谷值点的**单谷函数**.

时间容易用栈做到$\mathcal O(n)$.

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
int read();
int n;
int st[1000005], top;
long long sum = 0;
int main() {
    n = read();
    for (int i = 1; i <= n; ++i) {
        int x = read();
        sum += x;
        st[++top] = x;
        while (top >= 3 && st[top - 1] >= st[top] && st[top - 1] >= st[top - 2])
            st[top - 2] = -(st[top - 1] - st[top] - st[top - 2]), top -= 2;
    }
    int l = 1, r = top;
    long long res = 0;
    while (l <= r) {
        if (st[l] > st[r])
            res += st[l++];
        else
            res += st[r--];
        if (l > r) break;
        if (st[l] > st[r])
            res -= st[l++];
        else
            res -= st[r--];
    }
    printf("%lld %lld\n", (res + sum) / 2, (sum - res) / 2);
    return 0;
}
int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (!isdigit(c)) f = (c == '-') ? -1 : f, c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    return x * f;
}
```


---

## 作者：KellyFrog (赞：12)

~~为什么我的动态转移方程和各位大佬都不大一样呢QAQ~~

## [传送门](https://www.luogu.org/problem/P2734)

## 一点思路
### 思路一：min-max博弈树
~~其实是因为博弈论才刷这道题的Orz~~

因为在玩家2的回合，玩家2取什么数字，玩家1是拿不到分的，所以从下往上，第1，3，5......奇数个标上分，偶数标0分

从上往下递归，刚开始是分成左右两边，分别表示取左边和右边，同时标上num数组的数值

上一步完成后，从下往上，偶数个（从1开始算层数）都标成0

然后用min-max的标准程序完美的AC这道题

![这课博弈树像这样](https://cdn.luogu.com.cn/upload/image_hosting/8gx3wdzd.png)

......直到你看了一眼数据（这么小的数据应该DFS都能过）

这样的时间复杂度就是 O($2^{n-1}$)，我甚至都能够想象看到这道题的同学对我TLE的嘲讽之情
### 思路二（正解）在博弈树基础上的~~毒~~(d)~~品~~(p)
很明显，根据博弈论的思想，你的对手想给你更少的分，这样他就可以拿到更多的分数了（因为分数总和就那么多，给你少了给他就多了）

这题我就运用了min-max的想法

另外，这道题显然要用区间DP来保证答案的最优性

#### 1. 确定状态

我们用```dp[i][j]```来表示在区间```{i,j}```内玩家1能取到的最大值

#### 2. 状态转移方程
根据我们上边的结论，玩家2肯定选玩家1得分最小的方案，因为这样在区间内在总是相等的情况下玩家2能够拿到的分数就更高

所以这个方程应该写成

```cpp
dp[i][j]=max(
  ????+上一个状态区间玩家2执行完最优策略的结果,
  ????+上一个状态区间玩家2执行完最优策略的结果
);
```
我们知道，这个区间最后取的要么是```i```，要么是```j```

玩家1选```i```时，获得分数```num[i]```

玩家2原来走完后的区间为```:{i+1,j}```

玩家1选```j```时，获得分数```num[j]```

玩家2原来走完后的区间为```:{i,j-1}```

玩家2最优策略是，他在区间```{p,q}```当中，取走第```p```个或者第```q```个，让你的得分尽量少，所以，他肯定选最小的值（指上个状态）

玩家2取走第```p```个，则上一个状态为区间```{p+1,q}```

同理，取走第```q```个，则上一个状态为区间```{p,q-1}```

注意，因为这里玩家2无论选什么你都是拿不到分的，所以，对于玩家二的区间，应有

```cpp
对于玩家2：
dp[p][q]=min(dp[p+1][q],dp[p][q-1]);
```

所以我们把转移方程补全，就需要为玩家2执行最优策略，把上边的区间```{p,q}```换成```{i+1,j}```和```{i,j-1}```，填入上边的式子

得到完整的转移方程：

```cpp
dp[i][j]=max(
  num[i]+min(dp[i+1][j-1],dp[i+2][j]),
  num[j]+min(dp[i+1][j-1],dp[i][j-1])
 );
```
#### 3. 边界条件与初始化
我们有区间dp一贯的初始化：
```dp[i][i]=num[i];```

#### 4. 你以为这就完了吗？？

通过观察状态转方程我们不难发现：
有```i+2```项，要想让```i+2```已知，我们需要用到一些~~玄学方法~~技巧

1. ```i```倒着跑：这样```i+2```就是已知的了，另外，因为```i```倒着跑了，所以```j```是要跟他反方向跑的，所以```j```应该正着跑
2. 初始化：看到那个```'+2'```了吗？我们需要手动模拟一层！！！这样```'+2'```才会是已知的

   对于这个，因为```i```是要倒着跑的，所以最开始打出来的表应该是这样的（显然是玩家1选，因为这是第一轮，所以取大）：
   ```cpp
   1 3 0 0 0
   0 3 5 0 0
   0 0 5 5 0
   0 0 0 2 7
   0 0 0 0 7
   ```
   初始化程序段：
   ```cpp
   for(int i = 1; i < n + 1; i++) {
     dp[i][i] = num[i];
     sum += num[i];
   }
   for(int i = 2; i < n + 1; i++) {
     dp[i-1][i] = max(dp[i][i], dp[i-1][i-1]);
   }
   ```
3. 十分特别无比重要的东西：因为是对手先走，你在为对手执行最优策略，最后除了输出```dp[1][n]```以外，还要输出```sum-dp[1][n]```

## 丑陋的程序

（居然一遍AC了？？？！！！）

说一句，这是用emacs写的，缩进可能跟Dev和GUIDE有点区别

```cpp
#include <iostream>
#include <fstream>

using namespace std;

int dp[110][110];
int n;
int num[110];
int sum;

void ParseIn() {
  cin >> n;
  for(int i = 1; i < n + 1; i++) {
    cin >> num[i];
  }
}

void DP() {
  for(int i = 1; i < n + 1; i++) {
  	//初始化
    dp[i][i] = num[i];
    sum += num[i];
  }
  for(int i = 2; i < n + 1; i++) {
    //手动模拟第二层dp矩阵 
    dp[i-1][i] = max(dp[i][i], dp[i-1][i-1]);
  }
  for(int i = n - 2; i > 0; i--) {
  	//i要倒着跑 
    for(int j = i; j < n + 1; j++) {
   	  //j要正着跑 
      dp[i][j] = max(
        num[i] + min(dp[i+1][j-1], dp[i+2][j]), 
        num[j] + min(dp[i][j-2], dp[i+1][j-1])
      );//转移方程 
    }
  }
}

void Core() {
  DP();
}

void WriteOut() {
  cout << dp[1][n] << ' ' << sum - dp[1][n] << endl;
}

int main() {
  ParseIn();
  Core();
  WriteOut();
  return 0;
}
```
弱弱的说一句，为什么大佬们都在用前缀和啊。。

还有管理员。。。

蒟蒻表示害怕

还有，这篇已经十天了还没消息

---

## 作者：yummy (赞：12)

这题居然长得和[我的题目](https://www.luogu.org/problemnew/show/U73314)如此的相似，我太厉害了！

题解里都是区间DP，而且状态定义雷同，我就发一个状态定义不同的方法。

---
这种定义方法是，f[i][j]=起点为i，长度为j时，先手分数-后手分数的最大值。(请注意这里的长度=终点-起点，也就意味着终点在i+j）

那么就有2种情况：
- 从左边取，f[i][j]=a[i]-f[i+1][j-1]
- 从右边取，f[i][j]=a[i+j]-f[i][j-1]

因此我们就可以写了。

---
所以这样的改变有什么用吗？

我们发现，如果我们采用这样的状态定义，每次只会用到上一级的结果，于是我们就可以进行滚动数组优化。

这点优化在本题中是看不出来的，但是在我出的题目里就有明显的表现。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,dp[205][2],a[205],tot=0;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        dp[i][0]=a[i];
        tot+=a[i];//tot记录和
    }
    for(int i=1;i<n;i++)//长度枚举
    {
        for(int j=1;j+i<=n;j++)//起点枚举
        {
            dp[j][i&1]=max(a[j+i]-dp[j][1-(i&1)],a[j]-dp[j+1][1-(i&1)]);
        }
    }
    printf("%d %d",(tot+dp[1][1-(n&1)])>>1,(tot-dp[1][1-n&1])>>1);//小学奥数的和差问题
    return 0;
}
```

---

## 作者：Celebrate (赞：11)

这一道题一开始用了贪心来做，后来发现这样是不可以的，因

为两个人都不只看眼前，他们深谋远虑，所以只能将空间从少

往多的推，于是我们定义f数组记录玩家1在这个区间里面最多

能拿多少分，然后就可以dp了

顺便用si记录1一直加到i的值

i-j（i<j)的值就是：s[j]-s[i-1]

dp公式：

f[i][j]=max(s[j]-s[i-1]-f[i][j-1],s[j]-s[i-1]-f[i+1][j]);

第一个意思是说：

1拿了最右边的，那么2肯定会拿i到j-1的最大值了，剩下的就是1得了

第二个意思是说：

1拿了最左边的，那么2肯定会拿i+1到j的最大值了，剩下的就是1得了

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t;
int s[210],f[210][210];
int main()
{
	int i,j;scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&t);
		s[i]=s[i-1]+t;//记录 
		f[i][i]=t;//初始化 
	}
	//本来这里想i从1到n的
	//但是需要求1-n的最大值，那样可能行不通 
	for(i=n-1;i>=1;i--)
		for(j=i+1;j<=n;j++)
			f[i][j]=max((s[j]-s[i-1])-f[i][j-1],
						(s[j]-s[i-1])-f[i+1][j]);
	printf("%d %d\n",f[1][n],s[n]-f[1][n]);//1拿完了，剩下的就是2的了 
	return 0;
}
```

---

## 作者：Forever丶CIL (赞：10)

序列 sl[] 4 7 2 9 5 2

考虑用f[i][j]来表示在i,j这段区间内先手能获得的最大分数;

那么后手在先手最优方案走法下,按最优方案走的最大分数就是

i,j这个区间总分数减去f[i][j].

那么,我们可以先处理出长度为一的区间,再处理长度为二的,

再三,再四......以此类推,

怎么处理呢? 想,对于先手，他每次可以从左端取数,也可以从右端取数

这里只分析左端的情况, 右端的大家脑补一下233和左端一样

当我们要求f[k][l]的时候,且此时我们先手要取的是sl[k],那么,

用k,l中后手的分加sl[k],就是现在先手的分,这里要注意为什么是后手;

因为我们在这里总把正要进行操作的人看为先手,所以每走一步,先后手互换

左端右端都这样操作,取MAX就好了
例:

| 4 | 7 | 2 | 9 | 5 | 2 |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
|  |  | k | k+1 | l |  |


    f[k+1][l]=7->f[k][l]=2+9+5-7+7=16



------------


```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int n,sum=0;
int sl[1010];
int f[1001][1010];
void ini()
{
    for(int i=1;i<=n;i++)
    {
        f[i][i]=sl[i]-sl[i-1];   //一点初始化，对于长度为一的区间先手得分自然就是这样啦； 
    }
}
void dp()
{
    for(int i=2;i<=n;i++)
    {
        int l;
        for(int k=1;k<=n-i+1;k++)
        {
            l=k+i-1;
            f[k][l]=max(sl[l]-sl[k]-f[k+1][l]+sl[k]-sl[k-1],sl[l-1]-sl[k-1]-f[k][l-1]+sl[l]-sl[l-1]);
		}//求值过程，上面讲了，自己在领悟一霎233
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&sl[i]);
        sl[i]+=sl[i-1]; //求了个前缀和，方便计算一点 
    }
    ini();
    dp();
    printf("%d %d",f[1][n],sl[n]-f[1][n]);
    return 0;
}
```


------------

rp++

---

## 作者：pxy1118 (赞：5)

## 这题使用记忆化搜索是很容易理解的
用~~E~~**DFS**暴力枚举来判断每个Player ~~Alice and Bob~~是取第一项还是最后一项

见蒟蒻滴code：

------------

```cpp
#include <bits/stdc++.h>
#define N 210
using namespace std;
int n;
int d[N],f[N][N],s[N];
inline int dfs(int l,int r){
	if(f[l][r])return f[l][r];//算过的不用再算了
	if(l>r)return 0;
	if(l==r)return d[l];
	f[l][r]=max(s[r]-s[l]-dfs(l+1,r)+d[l],s[r-1]-s[l-1]-dfs(l,r-1)+d[r]);
    //此时之前的 “先手” 变为了剩余序列的 “后手” ，前缀和上场，一波乱搞
    //PS：只有聪明的人看得懂乱搞是什么意思 qwq
	return f[l][r];
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>d[i];
		s[i]=s[i-1]+d[i];//计算前缀和
	}
	int x=dfs(1,n);//Player1 的最大分数
	cout<<x<<" "<<s[n]-x/*Player2 的分数*/<<endl;
	return 0;
}
```

------------
# ~~This code is too easy to copy.~~

---

## 作者：Watermatter (赞：4)

来一发短的代码。。。
这个题和[P3004](https://www.luogu.org/problemnew/show/P3004)还是很像的（~~双倍经验~~）。

这题其实是一个区间dp，然而区间dp的标配是一个二维数组，第一维和第二维分别代表枚举该区间的权值。当然这题二维妥妥的可以通过，那么P3004的内存只有64MB，我们可以想办法优化。

不难发现，二维数组的第二维其实可以在读入的时候就可以用前缀和来优化，直接省去第二维，就连32MB都跑得过。。。

下面放出代码，供大家好好理解。
```cpp
#include<bits/stdc++.h>
using namespace std;
int f[5001],s[5001];
int n;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	scanf("%d",&f[i]),s[i]=s[i-1]+f[i];
	for(int len=2;len<=n;len++)
		for(int i=1;i<=n-len+1;i++)
			{
				int j=i+len-1;
				int tot=s[j]-s[i-1];
				f[i]=tot-min(f[i+1],f[i]);
			}
	printf("%d %d\n",f[1],s[n]-f[1]);
	return 0;
}/*如果是P3004就直接printf("%d\n",f[1]);*/
```

不要抄袭代码哦~

---

## 作者：LikC1606 (赞：3)

### 题意
给出长为n的序列，有两个人，轮流拿最左边或最右边的，且两个人的拿法的是最优的，写一个程序，判断第一个人和第二个人分别能拿到的的最大值。
### 做法
这道题的内存足够大，我们可以用动态规划，数组f [ i ] [ j ]表示从i到j这一段序列先手的比后手的多拿多少分。因为只能拿最右边的和最左边的，所以只要递推这两种情况后取最大值即可。
### 代码
```cpp
/*
ID: liuzhen26
TASK: game1
LANG: C++                 
*/
#include<bits/stdc++.h>
using namespace std;
int n;
int a[205];
int f[205][205];//f[i][j]表示从 i 到 j 这段序列先手比后手大的值 
int main()
{
	freopen("game1.in","r",stdin);
	freopen("game1.out","w",stdout);
	scanf("%d",&n);
	int s = 0;
	for(int i=1;i<=n;++i)
	    scanf("%d",&a[i]), f[i][i] = a[i], s+=a[i];//记录 
	for(int l=2;l<=n;++l)
	{
	    for(int i=1;i+l-1<=n;++i)
	    {
	    	int j = i+l-1;
	    	f[i][j] = max(a[i]-f[i+1][j], a[j]-f[i][j-1]);//递推，求最大值 
		}
	}
	printf("%d %d\n", (s+f[1][n])/2, (s-f[1][n])/2);//两个人的值 
	return 0;
}
```


---

## 作者：y11034822 (赞：2)

我想在这里讲一下我对这条动态转移方程的理解。

f[i][j]表示在区间[i,j]内按规则取数，先手的人能取的最大值。当然之后取的人一定是聪明的。

s[i][j]表示区间[i,j]内所有数的和

我们可以得出动态转移方程：

f[i][j]=max(s[i][j]-f[i+1][j],s[i][j]-f[i][j-1])

s[i][j]-f[i+1][j]

表示我们取了a[i],然后我们就变成了后手。而我们的对手成了先手。

我们的对手是很聪明的，所以他会取最优的。

那在我们这次操作之后直到游戏结束，他取得的数的和就一定是f[i+1][j]

剩下来的数的和就是s[i+1][j]-f[i+1][j]

再加上我们之前取的数a[i]就是s[i][j]-f[i+1][j]

当我们取a[j]时同理。

(第一篇题解)


---

## 作者：Ofnoname (赞：1)

详细一点解释一下搜索算法。

首先，“你的程序要始终为第二位玩家执行最优策略”这句话并没有意义，因为你始终要为双方都执行最优策略才符合题意。

对于任意一个局面$[L,R]$，显然只有取左端点和取右端点两种情况。

此时局面变为$[L+1,R]$或$[L,R-1]$且轮到另一个人。

由于不断向下搜索时一直为当前玩家寻找最优策略。所以下一步搜索$[L+1,R]$时结果其实是另一个玩家的最优策略。所以先手能在$[L+1,R]$中得到的最大值其实是$[L+1,R]$的和减去深搜的结果再加上我选的左端点。即$S_R-S_L-DFS(L+1,R)+d_L$，搜右边同理。

同一个区间，搜索多次的结果是固定的，所以用记忆化可以大幅提高效率。

```cpp
#include <bits/stdc++.h>
#define MAX 100+1
using namespace std;

int N,d[MAX],S[MAX],f[MAX][MAX];//f数组即用于记忆化搜索

inline int max(const int &a,const int &b){return a>b ? a : b;}

int DFS(const int L,const int R)
{
	if (L == R) return d[L];
	if (!f[L][R])
		f[L][R] = max(S[R]-S[L]-DFS(L+1,R)+d[L],S[R-1]-S[L-1]-DFS(L,R-1)+d[R]);
    //L~R的最大值就是L+1~R的总和减去后手在L+1~R的最大值加上左端点（右端同理）。
	return f[L][R];
}

int main()
{
	scanf("%d",&N);
	for (register int i=1; i<=N; i++)
		scanf("%d",d+i), S[i] = S[i-1] + d[i];//输入并计算前缀和
	printf("%d %d\n",DFS(1,N),S[N] - DFS(1,N));//总数减去先手的值就是后手的值
}

```

---

## 作者：柏木由纪AKB48 (赞：0)

三维状态的记忆化搜索，时间复杂度o(n^2)，总状态数2*n^2个

速度可观，但是思维难度基本为零

                            f[a][b][0,1]
                        
先看这个状态，代表的是我来玩一个子游戏，我是先手(0),还是后手(1)

可以类比sg函数的转移，从

                             f[a][b][0]
转移到

                         f[a+1][b][1]+v[a]
                         f[a][b-1][1]+v[b]

因为对手肯定也是极其聪明的，多以我们在当前是后手的情况下当然也要帮对手选择最好的决策（就和自己一样就好了）

推荐对应相似练习题: P1512 伊甸园日历游戏　

下面上代码
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,vis[102][102][2],f[102][102][2],a[102];   
int dfs(int l,int r,int con){
	if(vis[l][r][con]) return f[l][r][con];
	if(l==r){
		vis[l][r][0]=vis[l][r][1]=1;
		f[l][r][0]=a[l];
	    return f[l][r][con];
	}
	if(con==1){
		int t1=dfs(l,r-1,1)+a[r],t2=dfs(l+1,r,1)+a[l];
		vis[l][r][1]=1;
		if(t1>t2) return f[l][r][1]=dfs(l,r-1,0);
		else return f[l][r][1]=dfs(l+1,r,0);
	}
	int ans=max(dfs(l,r-1,con^1)+a[r],dfs(l+1,r,con^1)+a[l]);
	vis[l][r][con]=1;return f[l][r][con]=ans;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	printf("%d %d\n",dfs(1,n,0),dfs(1,n,1));
	return 0;
}
```


---

## 作者：vinvor (赞：0)

当你在i到j中取了i之后，那么你就只能在i+1到j中作为后手取值，故你所能取得的值为i+1到j的和减去作为先手所取得的最大值；

初始化f[i][i]=sum[i][i]=a[i];

状态转移方程:

f[i][j]=max(a[i]+sum[i+1][j]-f[i+1][j]， a[j]+sum[i][j-1]-f[i][j-1]);

f[i][j]表示在从第i个数到第j个数里先手能取得的最大值;

a[i]表示第i个数的值;

sum[i][j]表示在从第i个数到第j个数的和;

下附代码：

```cpp
#include<bits/stdc++.h>
#define MAXN 201
using namespace std;
long n,ori,ans,ans2;
long F[MAXN][MAXN],num[MAXN];
inline long max(long a,long b)
{
    return a>b?a:b;
}
long get_S(long a,long b)
{
    long p=0;
    for (long i=a;i<=b;i++)
        p+=num[i];
    return p;
}
long get_F(long i,long j)
{
    if (F[i+1][j]==ori)
        F[i+1][j]=get_F(i+1,j);
    if (F[i][j-1]==ori)
        F[i][j-1]=get_F(i,j-1);
    return max(num[i]+get_S(i+1,j)-F[i+1][j],num[j]+get_S(i,j-1)-F[i][j-1]);
}
void init()
{
    long i;
    cin >> n;
    memset(F,0xF,sizeof(F));
    ori=F[0][0];
    for (i=1;i<=n;i++)
    {
        cin >> num[i];
        F[i][i]=num[i];
    }
}
void print()
{
    cout << ans << ' ' << ans2 << endl;
}
int main()
{
    init();
    ans=get_F(1,n);
    ans2=get_S(1,n)-ans;
    print();
    return 0;
}
```

---

## 作者：BLMontgomery (赞：0)

灵活熟练的运用记忆化搜索可以大大降低思维难度；另外也不用太担心时间的问题，我这题0ms通过，没有比我快的了

![]( ![](https://cdn.luogu.com.cn/upload/pic/5163.png) )

我用dp[i][j]用于记录某人（无论是谁）进行当前序列[i,j]的操作时能得到的最大得分，在dfs时传递三个参数：l,r,b；

l表示当前序列的左端点，r表示当前序列的右端点，b表示是谁应对当前的局面（0表示第一个人，1表示第二个人）

另需一个结构体：

```cpp
struct node
{
     int p0,p1;
};
```
用于dfs的两个返回值：玩家p0,p1在此局面且在此人的操作下分别获得的得分
在用s[1~n]记录一下序列的前缀和，后面会有用的

那么我们有两种状态转移dp[l][r]=max( dfs(l+1,r,!b).pb + a[l] , dfs(l,r-1,!b).pb + a[r] );（注：这里的pb指此局面如果是b玩家行动，那么我们使用下一个局面中玩家b得到的得分来得到此局面b玩家的得分（因为dfs返回值是一个结构体））

由于每次局面都通过它子局面中的最优者得到，因此每个人都是"很聪明地"进行决策

边界条件:(l==r) 则返回对给操作当前局面的人a[l]的得分，另一个人0的得分

因此剩下的就比较好解决了，代码如下：（如果仍有不太懂的地方可以私信我）


    
```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
using namespace std;
int a[110],n;
int s[110];
int dp[150][150];
struct node
{
    int p0,p1;
};
node dfs(int l,int r,bool b)
{
    if(l==r)
    {
        if(b) return (node){0,a[l]};
        else return (node){a[l],0};
    }
    if(dp[l][r])//搜过了
    {
        if(b)
        {
            return (node){s[r]-s[l-1]-dp[l][r],dp[l][r]};
        }
        else 
        {
            return (node){dp[l][r],s[r]-s[l-1]-dp[l][r]};
        }
    }
    if(b)
    {
        dp[l][r]=max(dfs(l+1,r,0).p1+a[l],dfs(l,r-1,0).p1+a[r]);
        return (node){s[r]-s[l-1]-dp[l][r],dp[l][r]};
    }
    else 
    {
        dp[l][r]=max(dfs(l+1,r,1).p0+a[l],dfs(l,r-1,1).p0+a[r]);
        return (node){dp[l][r],s[r]-s[l-1]-dp[l][r]};
    }
}
int main()
{
    int i,j,k;
    scanf("%d",&n);
    for(i=1;i<=n;++i) scanf("%d",&a[i]),s[i]=s[i-1]+a[i];
    node m=dfs(1,n,0);
    printf("%d %d",m.p0,m.p1);
    return 0;
}
```
/\*
6
4 7 2 9 5 2

\*/

---

