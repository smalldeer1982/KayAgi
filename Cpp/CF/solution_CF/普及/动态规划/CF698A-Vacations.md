# Vacations

## 题目描述

Vasya has $ n $ days of vacations! So he decided to improve his IT skills and do sport. Vasya knows the following information about each of this $ n $ days: whether that gym opened and whether a contest was carried out in the Internet on that day. For the $ i $ -th day there are four options:

1. on this day the gym is closed and the contest is not carried out;
2. on this day the gym is closed and the contest is carried out;
3. on this day the gym is open and the contest is not carried out;
4. on this day the gym is open and the contest is carried out.

On each of days Vasya can either have a rest or write the contest (if it is carried out on this day), or do sport (if the gym is open on this day).

Find the minimum number of days on which Vasya will have a rest (it means, he will not do sport and write the contest at the same time). The only limitation that Vasya has — he does not want to do the same activity on two consecutive days: it means, he will not do sport on two consecutive days, and write the contest on two consecutive days.

## 说明/提示

In the first test Vasya can write the contest on the day number 1 and do sport on the day number 3. Thus, he will have a rest for only 2 days.

In the second test Vasya should write contests on days number 1, 3, 5 and 7, in other days do sport. Thus, he will not have a rest for a single day.

In the third test Vasya can do sport either on a day number 1 or number 2. He can not do sport in two days, because it will be contrary to the his limitation. Thus, he will have a rest for only one day.

## 样例 #1

### 输入

```
4
1 3 2 0
```

### 输出

```
2
```

## 样例 #2

### 输入

```
7
1 3 3 2 1 2 3
```

### 输出

```
0
```

## 样例 #3

### 输入

```
2
2 2
```

### 输出

```
1
```

# 题解

## 作者：SqrtSecond (赞：16)

标准DP。

我们先设一个$a$数组，存放每天的状态。

因为每一天都有$3$种情况，所以我们设$dp[i][j]$为第$i$天的时候做第$j$种运动。（$j=0$为休息，$1$为比赛，$2$为健身）

则易知$dp[i][0]=\min(dp[i-1][0],dp[i-1][1],dp[i-1][2])+1$。

而如果可以做比赛，即$a[i]=1$或$3$，则$dp[i][1]=min(dp[i-1][0],dp[i-1][2])$。

同理可得，如果$a[i]=2$或$3$，则$dp[i][2]=min(dp[i-1][0],dp[i-1][1])$。

边界：$dp[0][0]=dp[0][1]=dp[0][2]=0$；

话不多说，上~~华丽的~~代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[110],dp[110][3];//0为休息，1为比赛，2为健身 
int main()
{
	memset(dp,127,sizeof(dp));//初始化
	cin>>n;
	for(int i=1;i<=n;++i)cin>>a[i];
	dp[0][0]=dp[0][1]=dp[0][2]=0;//边界
	for(int i=1;i<=n;++i)
	{
		dp[i][0]=min(min(dp[i][0],dp[i-1][0]),min(dp[i-1][1],dp[i-1][2]))+1;
		if(a[i]==1||a[i]==3)
		{
			dp[i][1]=min(dp[i-1][0],dp[i-1][2]);
		}
		if(a[i]==2||a[i]==3)
		{
			dp[i][2]=min(dp[i-1][0],dp[i-1][1]);
		}
	}//dp转移
	cout<<min(dp[n][0],min(dp[n][1],dp[n][2]));
   return 0;//华丽结束
}
```


~~写完了，逃~~

---

## 作者：fengqiao17 (赞：4)

## Solution

主要是暴力+判断。首先定义两个变量 $flag1$ 和 $flag2$，分别记录比赛、健身是否在上一天做过，以及定义统计休息天数的 $ans$。接下来每一次输入都分类讨论 $a$ 的情况：
1. $a=0$，此时没有可以做的事情，$flag0$ 和 $flag1$ 都清空为 $0$，$ans$ 累加；
2. $a=1$，此时是否打比赛取决于 $flag1$ 是否标记前一天打过比赛，打过就休息，$ans$ 累加，没打过就打比赛，$flag1$ 标记打过比赛，注意还要把 $flag2$ 设为未健身；
3. $a=2$，同上；
4. $a=4$，此时有三种情况，一是前一天打过比赛，二是前一天健过身，三是什么都没干。最后一种要注意，我们要设一个变量 $tmp$，以防出现同一天做两种事。

## Code
```cpp
//author:fengqiao17
//转载请标明地址：https://616673.blog.luogu.org/solution-cf698a
#include <bits/stdc++.h>
using namespace std;
bool flag1, flag2 , tmp;//flag1记录比赛，flag2记录健身，tmp标记
int main() {
  int n , ans = 0;//ans是休息的天数
  cin >> n;
  for (int i = 1; i <= n; i++) {
    int a;
    cin >> a;//输入
    if (a == 0) {
      ans++;
      flag1 = flag2 = 0;//前一天没有做什么，清0
    }
    if (a == 1) {
      if (flag1 == 1) {//打过比赛了
        ans++;//休息
        flag1 = 0;
      } else {
        flag1 = 1, flag2 = 0;//打比赛
      }
    }
    if (a == 2) {
      if (flag2 == 1) {//健过身了
        ans++;//休息
        flag2 = 0;
      } else {
        flag2 = 1, flag1 = 0;//健身
      }
    }
    if (a == 3) {
      if (flag1 == 1) {//打过比赛就健身
        flag1 = 0, flag2 = 1;
        tmp = 1;
      }
      if (flag2 == 1 && tmp == 0) {//健过身就打比赛，tmp记录是否进入上一个if，同一天不做两件事
        flag2 = 0, flag1 = 1;
      }
      tmp = 0;
    }
  }
  cout << ans;//撒花
  return 0;
}
```

---

## 作者：赤黒 (赞：4)

本蒟蒻第一篇题解，大佬不喜请喷QAQ~~

代码如下

```
#include <bits/stdc++.h>  //头文件
using namespace std;
int main()
{
    int n,a,ans=0;//依题设
    int flag=0,flag2=0,t=0;//辅助变量，flag测前一天有没有比赛
    //flag2测前一天有没有健身，t是当健身和比赛都可以时以免重复的
    cin>>n;  //有n天
    for(int i=1;i<=n;i++)
    {
        cin>>a;
        if(a==0)//当什么都不能干时，不就只能休息了吗？
        		//记得将flag和flag2清零
        {
            ans++;
            flag=0;
            flag2=0;
        }
        if(a==1)			//当可以比赛但不可健身时
            if(flag==1)		//如果前一天比赛了，休息一天
            {
                ans++;
                flag=0;
            }
            else			//否则记录flag=1 注意flag2要清零
            {
                flag=1;
                flag2=0;
            }
        if(a==2)			//当可以健身但不可比赛时
            if(flag2==1)	//如果前一天健身了，休息一天
            {
                ans++;
                flag2=0;
            }
            else			//否则记录flag2=1 flag=0
            {
                flag2=1;
                flag=0;
            }
        if(a==3)			//（划重点了！！）当可以比赛又可以健身时
        					//不可能休息的
        {
            if(flag==1)		//当前一天比赛了，那今天就健身
            {
                flag=0;
                flag2=1;
                t=1;
            }
            if(flag2==1&&t==0) //反之，加个t是为了不让这个条件符合
            {
                flag2=0;
                flag=1;
            }
            t=0;			//注意t每次都要清零，不然下次t还是1
        }
    }
    cout<<ans;			//结束    开心\(*^▽^*)/
    return 0;
}
```
# 求过QAQ

---

## 作者：World_Creater (赞：2)

题解区怎么清一色的 $\verb!DP!$……

提供一种分类讨论的做法。

我们令 $\verb!lday!(0/1/2)$ 为我们上一天在做什么（$0$ 为休息，$1$ 为比赛，$2$ 为健身）。

1. 如果这一天无事可做。  
显然直接令 $\verb!lday!$ 为 $0$ 并增加答案。
2. 如果这一天可以做一件事情。  
如果这一天和上一天的状态不同，那么更新状态，否则强制令这一天休息。  
为什么这样类似于贪心的策略是对的？  
如果相邻两天的状态相同，显然我们只能取其中一天，而如果我们让前面一天做事情而后面一天休息，对更加后面的日子而言，可以做的事情更多。
3. 如果这一天两件事情都可以做。  
这种情况我们继续分类讨论。  
3.1. 如果上一天做了事情，这一天直接和上一天做的不一样就可以了。  
3.2. 如果上一天没有做事情，我们假装这一天也没有做事情。  
第一条很好理解，但为什么第二条是对的？  
考虑第二种情况只可能发生在这样的区间中：  
`...0 3 3 3 3 3 3.... ` （注意第一个 $0$ 并不是原序列中的 $0$，而是指在那一天休息)。  
在这种情况下，我们可以任意钦定第一个 $3$ 做的事情，那么最后一个 $3$ 做的事情也是可以由我们决定的。  
因此这种情况下后面要做什么事情不会影响答案，因为我可以任意指定我要最后一个 $3$ 所做的事情——相当于我们在“休息”。

可能有点抽象，可以结合代码理解：
```cpp
#include<bits/stdc++.h>
using namespace std;
int lday,n,a[100005],res;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n;i++)
	{
		if(a[i]==0)
		{
			res++;
			lday=0;
		}
		if(a[i]==1)
		{
			if(lday==1)
			{
				res++;
				lday=0;
			}
			else
			{
				lday=1;
			}
		}
		if(a[i]==2)
		{
			if(lday==2)
			{
				res++;
				lday=0;
			}
			else
			{
				lday=2;
			}
		}
		if(a[i]==3)
		{
			if(lday!=0)
			{
				lday=lday==1?2:1;// 原先是0不用动，否则切换状态
			}
		}
	}
	cout<<res;
}
```


---

## 作者：Drimpossible (赞：2)

# CF698A
### 思路：
显然 $DP$ 。
### 状态：
$dp[i][0/1]$ 表示第 $i$ 天，在体育馆或打比赛的最少休息天数（ $0$ 表示体育馆， $1$ 表示打比赛）
### 方程：
当体育馆打开时，**肯定为前一天打比赛或前一天体育馆天数 $+1$** ，方程即为 $dp[i][0]=min(dp[i-1][0]+1,dp[i-1][1])$ 。

当体育馆关闭时，今天去不了体育馆，**只能休息，肯定为前一天打比赛 $+1$ 或去体育馆 $+1$** ，方程即为 $dp[i][0]=min(dp[i-1][0],dp[i-1][1])+1$ 。

同理可得，有比赛时为 $dp[i][1]=min(dp[i-1][0],dp[i-1][1]+1)$ 。

没有比赛时为 $dp[i][1]=min(dp[i-1][0],dp[i-1][1])+1$ 。
### 边界：
当第一天开放时赋为 $0$ ，不开放时即为 $1$ 。
## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=100001;
int n,a[N],dp[N][2];
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	memset(dp,0x3f3f3f3f,sizeof(dp));//取min要赋极大值
	if(a[1]==0||a[1]==1)dp[1][0]=1;//边界
	else dp[1][0]=0;
	if(a[1]==0||a[1]==2)dp[1][1]=1;
	else dp[1][1]=0;
	for(int i=2;i<=n;i++){
		if(!a[i])dp[i][0]=min(dp[i-1][1]+1,dp[i-1][0]+1),dp[i][1]=min(dp[i-1][0]+1,dp[i-1][1]+1);
		if(a[i]==1)dp[i][0]=min(dp[i-1][0],dp[i-1][1])+1,dp[i][1]=min(dp[i-1][0],dp[i-1][1]+1);
		if(a[i]==2)dp[i][0]=min(dp[i-1][0]+1,dp[i-1][1]),dp[i][1]=min(dp[i-1][0],dp[i-1][1])+1;
		if(a[i]==3)dp[i][0]=min(dp[i-1][0]+1,dp[i-1][1]),dp[i][1]=min(dp[i-1][0],dp[i-1][1]+1);
	}
	printf("%lld",min(dp[n][0],dp[n][1]));
	return 0;
}
```

---

## 作者：SevenDawns (赞：2)

## 可以考虑动态规划 

### dp[i][j]表示在i天之前本次活动是j的最小值
然后就比较简单了，看代码
```
//dp[i][j]表示在i天之前本次活动是j的最小值
//1表示打比赛 0表示运动 2表示休息 
#include <bits/stdc++.h>
using namespace std;
int n,a[1001],i,j,k,l;
int dp[1001][5];
int main()
{
	scanf("%d",&n);
	for (i=1;i<=n;i++)
	  scanf("%d",&a[i]);
	memset(dp,30,sizeof(dp));//设成极大可以表示在本种状态下无解
	if (a[1]==0)
	  dp[1][2]=1;
	if (a[1]==1)
	{
		dp[1][2]=1;
		dp[1][1]=0;
	}
	if (a[1]==2)
	{
		dp[1][2]=1;
		dp[1][0]=0;
	}
	if (a[1]==3)
	{
		dp[1][2]=1;
		dp[1][1]=0;
		dp[1][0]=0;
	}//设置初始值
	for (i=2;i<=n;i++)
	{
		if (a[i]==0)//只能休息
		{
			for (j=0;j<=2;j++)
			  dp[i][2]=min(dp[i][2],dp[i-1][j]);
			dp[i][2]++;//休息时的状态转移
		}
		if (a[i]==1)
		{
			dp[i][1]=min(dp[i-1][0],dp[i-1][2]);//打比赛时的状态转移
			for (j=0;j<=2;j++)
			  dp[i][2]=min(dp[i][2],dp[i-1][j]);
			dp[i][2]++;
		}
		if (a[i]==2)
		{
			dp[i][0]=min(dp[i-1][1],dp[i-1][2]);//运动时的状态转移
			for (j=0;j<=2;j++)
			  dp[i][2]=min(dp[i][2],dp[i-1][j]);
			dp[i][2]++;
		}
		if (a[i]==3)
		{
			dp[i][0]=min(dp[i-1][1],dp[i-1][2]);
			dp[i][1]=min(dp[i-1][0],dp[i-1][2]);
			for (j=0;j<=2;j++)
			  dp[i][2]=min(dp[i][2],dp[i-1][j]);
			dp[i][2]++;
		}
	}//如果本种情况不成立则不用转移
	printf("%d\n",min(dp[n][0],min(dp[n][1],dp[n][2])));
}
```

---

## 作者：ZXXS (赞：1)

##### 这是一道动态规划的经典新手题（建议降橙）。
## 详解：
通俗地来讲，动态规划就是保存当前最佳的状态。

动态规划的思路大致分为三步:
1. 状态数组初始化；
2. 考虑边界；
3. 思考转移方程；

### 1. 状态数组初始化：

因为这道题需要求休息的最少天数。

所以我们可以建立一个二维数组储存第 $i$ 天比赛,做运动和休息时休息的最少天数。
- 把二维数组所有的数赋上一个极大值(两层循环就行)。

### 2. 考虑边界：

考虑边界，也就是给最开始的数赋值。$dp(0,0)=dp(0,1)=dp(0,2)=0;$ （第0天什么也不做，所以都赋上0,方便转移）。
### 3. 思考转移方程：
这里的转移方程需要分类讨论。
#### 首先考虑第$i$天休息:

无论这一天有什么活动，都可以休息，所以 $dp(i,0)=\min(\min(dp(i-1,0),dp(i-1,1)),dp(i-1,2))+1;$ （找前一天休息的最少天数，再多休息一天）。
#### 第$i$天做运动：
这一天能做运动时，**不能两天做同一件事** 。$dp(i,1)=\min(dp(i-1,0)),dp(i-1,2));$
（所以从上一天休息和比赛中选择休息天数少的，不休息，不增加）。

注：这一天不能做运动时，赋上极大值 **(初始已经赋值了没必要赋了)**。
#### 第$i$天比赛同上 $dp(i,2)=\min(dp(i-1,0)),dp(i-1,1));$
**最后输出三种活动中休息天数最少的**。
### code
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
const int MAX=2147483647;//最大值
int main()
{
	int n,a[105],dp[105][3];//a[i]储存活动方案，dp[i]储存第i天的状态
   scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);
	}
	for(int i=0;i<105;++i) //赋上最大值
	{
		for(int j=0;j<3;++j)
			dp[i][j]=MAX;
	}
	dp[0][0]=dp[0][1]=dp[0][2]=0;
	for(int i=1;i<=n;++i)
	{
		dp[i][0]=min(min(dp[i-1][0],dp[i-1][1]),dp[i-1][2])+1;
		if(a[i]==1||a[i]==3)
		{
			dp[i][1]=min(dp[i-1][0],dp[i-1][2]);
		}
		if(a[i]==2||a[i]==3)
		{
			dp[i][2]=min(dp[i-1][0],dp[i-1][1]);
		}
	}
	printf("%d",min(min(dp[n][0],dp[n][1]),dp[n][2]));
   return 0;
}
```

---

## 作者：tZEROちゃん (赞：1)

考虑 dp。

我们设 $dp_{i, j}$ 表示第 $i$ 天做第 $j$ 件事 **不** 休息的最大天数，当 $j=0$，表示休息，当 $j=1$，表示参与比赛，当 $j=2$，表示去健身房。

显然有以下转移：

无论 $a_i$ 取何值，他都可以休息，所以取第 $i-1$ 天三种方式的最大值，那么有

$$dp_{i, 0} = \max(dp_{i - 1, 0}, dp_{i - 1, 1}, dp_{i -1, 2})$$

当这天有比赛，即 $a_i = 1$ 或 $a_i = 3$ 我们就可以更新 $dp_{i, 1}$，那么有

$$ dp_{i,1} = \max(dp_{i - 1,0} + 1, dp_{i - 1,2} + 1)$$

当健身房在这天营业，即 $a_i = 2$ 或 $a_i = 3$ 我们就可以更新 $dp_{i, 2}$，那么有

$$ dp_{i,1} = \max(dp_{i - 1,0} + 1, dp_{i - 1,1} + 1)$$

最后我们设 $ans = max(dp_{n, 1}, dp_{n, 2}, dp_{n, 3})$，因为题目要求最少休息的天数，所以答案是 $n-ans$。

```cpp
#include<bits/stdc++.h>
using namespace std;

// dp[i][0] -> rest
// dp[i][1] -> contest
// dp[i][2] -> gym

const int N = 110;
int a[N];
int dp[N][N];

bool contest(int x) { return (a[x] == 1 || a[x] == 3); }
bool gym(int x) { return (a[x] == 2 || a[x] == 3); }

int main() {
  int n; 
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; ++i) {
    dp[i][0] = max({dp[i - 1][0], dp[i - 1][1], dp[i - 1][2]});
    if (contest(i)) dp[i][1] = max(dp[i - 1][0] + 1, dp[i - 1][2] + 1);
    if (gym(i)) dp[i][2] = max(dp[i - 1][0] + 1, dp[i - 1][1] + 1);
    // int ans = max({dp[n][0], dp[n][1], dp[n][2]});
    // cout << n - ans << endl;
  }
  int ans = max({dp[n][0], dp[n][1], dp[n][2]});
  cout << n - ans << endl;
} 
```

---

## 作者：happybob (赞：1)

考试考到这个题，$10$ 分钟写了半天没写对，放弃了，赛后 $5$ 分钟不到切了。发现 `dp[N][3]` 写成了 `dp[3][N]`。

显然是一道 DP 裸题，设 $dp_{i,j}(j \in {\{0,1,2\}})$ 表示第 $i$ 天是休息，健身或比赛，很容易列出转移方程。具体可以看代码：

```cpp
#pragma GCC optimize("-Ofast,inline")
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

constexpr int N(1e5 + 5);

int a[N], dp[N][3], n;

int main()
{
	scanf("%d", &n);
	for (int i(1); i <= n; i++) scanf("%d", &a[i]);
	memset(dp, 0x3f, sizeof dp);
	dp[0][1] = dp[0][0] = dp[0][2] = 0;
	for (int i(1); i <= n; i++)
	{
		dp[i][0] = min({ dp[i - 1][0], dp[i - 1][1], dp[i - 1][2] }) + 1; // dp[i][0] 一定可以转移
		if (a[i] == 2 || a[i] == 3) dp[i][1] = min({ dp[i - 1][0], dp[i - 1][2] }); // 健身只有在 a[i] == 2 或 a[i] == 3 时可以转移
		if (a[i] == 1 || a[i] == 3) dp[i][2] = min({ dp[i - 1][0], dp[i - 1][1] }); // 同理
	}
	printf("%d\n", min({ dp[n][0], dp[n][1], dp[n][2] }));
	return 0;
}
```


---

## 作者：James_Brady (赞：1)

~~这人真是工作狂，好好的假期不想休息~~

好了，言归正传，先分析这道题

他每一天的选择都只受前一天选择的影响，为何不用DP

定义dp[i][j]为第i天做j活动时休息的最少天数（休息，比赛，锻炼）

如果这一天为0，那么他只能**被迫休息**（滑稽），休息天数+1

同理，若为1，可以打比赛，从前一天锻炼，休息中选一个较小值转移

为2，3时同理

代码如下，细节见注释

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int dp[1010][5],a[110],n;//1代表休息 2代表锻炼 3代表比赛
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	scanf("%d",&a[i]);
	memset(dp,0x3f,sizeof(dp));
	dp[0][1]=dp[0][2]=dp[0][3]=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i]==0)
		dp[i][1]=min(dp[i-1][1],min(dp[i-1][2],dp[i-1][3]))+1;
		if(a[i]==1)
		{
			dp[i][1]=min(dp[i-1][1],min(dp[i-1][2],dp[i-1][3]))+1;//可以做事并不代表不能休息，所以一样要转移
			dp[i][3]=min(dp[i-1][1],dp[i-1][2]);
		}
		if(a[i]==2)
		{
			dp[i][1]=min(dp[i-1][1],min(dp[i-1][2],dp[i-1][3]))+1;
			dp[i][2]=min(dp[i-1][1],dp[i-1][3]);
		}
		if(a[i]==3)
		{
			dp[i][1]=min(dp[i-1][1],min(dp[i-1][2],dp[i-1][3]))+1;
			dp[i][2]=min(dp[i-1][1],dp[i-1][3]);
			dp[i][3]=min(dp[i-1][1],dp[i-1][2]);
		}
	}
	printf("%d",min(dp[n][1],min(dp[n][2],dp[n][3])));//最后一天从三个状态中选一个最优值
	return 0;
}
```


---

## 作者：L7_56 (赞：0)

## dp题3步
### 1.状态表示
用 $ dp[i][j] $ 表示前i天当前做j活动时休息最少天数

活动有3种:休息(0),运动(1),比赛(2)

所以 $ j $ 也是三种情况0,1,2
### 2.转移方程
分三种情况:

(1).当天什么都不做:

天数应该是前一天的情况再加1

$$ dp[i][0]=\min(dp[i-1][0],dp[i-1][1],dp[i-1][2])+1 $$ 

(2).当天做运动：

天数应该是前一天的情况，但是前一天不能做运动

$$ dp[i][1]=\min(dp[i-1][0],dp[i-1][2]) $$

(3).当天比赛:

和(2)相似，把不能做运动改成不能比赛就行

$$ dp[i][2]=\min(dp[i-1][0],dp[i-1][1]) $$

(2)(3)需要判断是否可行(没有比赛或体育馆没开)
### 3.初始化
明显当 $ i=0 $ 时dp值为0 
## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define N 110
#define inf 0x7ffffff
using namespace std;

int n,x;
int sp[N],wr[N],dp[N][3];

int main(){
		scanf("%d",&n);
		for(int i=1;i<=n;++i){
			scanf("%d", &x);
			switch(x){
				case 0 : sp[i]=wr[i]=0;break;
				case 1 : sp[i]=0;wr[i]=1;break;
				case 2 : sp[i]=1;wr[i]=0;break;
				case 3 : sp[i]=wr[i]=1;break;
				default : printf("error\n");break;
			}//状态记录
			dp[i][0]=dp[i][1]=dp[i][2]=inf;//初始化成极大值
		}
		dp[0][0]=dp[0][1]=dp[0][2]=0;
		for(int i=1;i<=n;++i){
			dp[i][0]=min(dp[i-1][0],min(dp[i-1][1],dp[i-1][2]))+1;
			if(sp[i]) dp[i][1]=min(dp[i-1][0],dp[i-1][2]);
			if(wr[i]) dp[i][2]=min(dp[i-1][0],dp[i-1][1]);
		}
		printf("%d\n", min(dp[n][0],min(dp[n][1],dp[n][2])));
	}
	
	return 0;
}

```

---

