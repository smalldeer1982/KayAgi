# [ABC064C] Colorful Leaderboard

## 题目描述

(ABC064 Task - C) 

## 多彩排行榜



在AtCoder中，参加比赛的人名字会变成一种颜色，对应于该人的评级如下：

```
Rating 1 - 399：灰名  
Rating 400 - 799：棕名  
Rating 800 - 1199：绿名  
Rating 1200 - 1599：青名  
Rating 1600 - 1999：蓝名  
Rating 2000 - 2399：黄名  
Rating 2400 - 2799：橙名  
Rating 2800 - 3199：红名  
```
除了上述之外，Rating 为 3200 及以上的人可以自由地选择 TA 的颜色，可以是上面八种颜色中的一种颜色。
目前，有 $N$ 个用户参加过 AtCoder 的比赛，第i个用户的评分是 $a_i$。
查找用户的不同颜色的最小和最大可能数量。



在AtCoder中，参加比赛的人名字会变成一种颜色，对应于该人的评级如下：


Rating 1 - 399：灰名  
Rating 400 - 799：棕名  
Rating 800 - 1199：绿名  
Rating 1200 - 1599：青名  
Rating 1600 - 1999：蓝名  
Rating 2000 - 2399：黄名  
Rating 2400 - 2799：橙名  
Rating 2800 - 3199：红名  

除了上述之外，Rating 为 3200 及以上的人可以自由地选择 TA 的颜色，可以是上面八种颜色中的一种颜色。
目前，有 $N$ 个用户参加过 AtCoder 的比赛，第i个用户的评分是 $a_i$。
查找用户的不同颜色的最小和最大可能数量。

## 说明/提示

$1≤n≤100$  
$1≤a_i≤4800$  
$a_i$ 是一个整数。

## Markdown 源码
```
(ABC064 Task - C) 

## 多彩排行榜



$1≤n≤100$  
$1≤a_i≤4800$  
$a_i$ 是一个整数。


```

## 样例 #1

### 输入

```
4
2100 2500 2700 2700```

### 输出

```
2 2```

## 样例 #2

### 输入

```
5
1100 1900 2800 3200 3200```

### 输出

```
3 5```

## 样例 #3

### 输入

```
20
800 810 820 830 840 850 860 870 880 890 900 910 920 930 940 950 960 970 980 990```

### 输出

```
1 1```

# 题解

## 作者：brealid (赞：2)

目测 $\color{white}\colorbox{#f1c40f}{普及/提高-}$ 难度。



### 思路

将 9 种可能的等级存储在数组里，则 min 值为分数为 0 ~ 3199 的颜色种类个数，max 值为 min 值加上分数 >3200 的人数。

### 特判  

若分数为 0 ~ 3199 的颜色种类个数为 0，分数 >3200 的人数大于 1，则min 值为 1，max 值为分数 >3200 的人数


### 代码

```
#include <stdio.h>

int getBlock(int rating)
{
    if (rating < 400) return 1;
    else if (rating < 800) return 2;
    else if (rating < 1200) return 3;
    else if (rating < 1600) return 4;
    else if (rating < 2000) return 5;
    else if (rating < 2400) return 6;
    else if (rating < 2800) return 7;
    else if (rating < 3200) return 8;
    else return 0;
}

int min(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

int main()
{
    int n, t, block[9] = {0};
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &t);
        block[getBlock(t)]++;
    }
    int res = 0;
    for (int i = 1; i <= 8; i++) {
        if (block[i] != 0) res++;
    }
    if (res != 0)
        printf("%d %d", res, res + block[0]);
    else 
        printf("%d %d", 1, block[0]);
}
```

---

## 作者：Green_Bird (赞：1)

## 解法：简单模拟
~~目测并没有绿题水平~~

**然而**  

简单的背后隐藏的是坑：  
**rating>=3200的神仙实际上可以$\color{red}\text{随意变色（不只是八种颜色）}$**  ~~orz~~  
所以也就不用考虑rating>=3200神仙的数量是否超过8人  

知道这一点后就好做了  ：  
- 只有人rating<3200时  正常统计即可  

- 当有人rating<3200时且有人rating>=3200时
```
   Max+=(rating>=3200)的人数;
```

- 当没有人rating<3200时且有人rating>=3200时
```
  Min=1,Max=(rating>=3200)的人数
```
**最后贴上我丑陋的代码：**
```cpp
#include<bits/stdc++.h>
using namespace std;
int minn,maxx;
map<string,int>a;
string s[8]={"hui","zong","lv","qing","lan","huang","cheng","hong"}; 
int main()
{
	int n;
	bool v1=false; //标记是否有人rating>=3200
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		if(x<400)
		{
			a["hui"]++;
			continue;
		}
		if(x<800)
		{
			a["zong"]++;
			continue;
		}
		if(x<1200)
		{
			a["lv"]++;
			continue;
		}
		if(x<1600)
		{
			a["qing"]++;
			continue;
		}
		if(x<2000)
		{
			a["lan"]++;
			continue;
		}
		if(x<2400)
		{
			a["huang"]++;
			continue;
		}
		if(x<2800)
		{
			a["cheng"]++;
			continue;
		}
		if(x<3200)
		{
			a["hong"]++;
			continue;
		}
		if(x>3199)
		{
			a["tql"]++;
			v1=true;
			continue;
		}
	}
	for(int i=0;i<=7;i++)
	{
		if(a[s[i]]!=0) minn++,maxx++;
	}
	if(v1==true&&minn>0)         //当有人rating<3200时且有人rating>=3200时
	  maxx+=a["tql"];
	if(v1==true&&minn==0)        //当没有人rating<3200时且有人rating>=3200时
	  minn=1,maxx=a["tql"];
	cout<<minn<<" "<<maxx<<endl;
	return 0;
}
```

---

## 作者：666DHG (赞：1)

题是挺简单的，但就是有许多坑点：

1. 要换行
2. 分数大于3200的人可以变成**任何颜色**（比如说屎名或紫名），即意味着```maxn=ans+temp```
而不是
```maxn=min(ans+temp,9)```
3. 特别地，当0到3199分没有人时，最小和最大值都是分数大于等于3200的人数（就在这里WA了许久QwQ）

代码很简单，大家应该都能看得懂

完整代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;

bool a[10];
int n,x,ans,temp;

int main()
  {
  	scanf("%d",&n);
  	while (n--) // 技巧，在读入时回手来统计人数，包括0-3199的蒟蒻与大于等于3200的dalao
  	  {
  	  	scanf("%d",&x);
  	  	if (x<400&&!a[1]) a[1]=true,ans++;
  	  	if (x>=400&&x<800&&!a[2]) a[2]=true,ans++;
  	  	if (x>=800&&x<1200&&!a[3]) a[3]=true,ans++;
  	  	if (x>=1200&&x<1600&&!a[4]) a[4]=true,ans++;
  	  	if (x>=1600&&x<2000&&!a[5]) a[5]=true,ans++;
  	  	if (x>=2000&&x<2400&&!a[6]) a[6]=true,ans++;
  	  	if (x>=2400&&x<2800&&!a[7]) a[7]=true,ans++;
  	  	if (x>=2800&&x<3200&&!a[8]) a[8]=true,ans++;
  	  	if (x>=3200) temp++;
	  }
  	printf("%d %d\n",max(ans,1),ans+temp);
  	return 0;
  }
```

---

