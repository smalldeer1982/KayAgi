# Buses Between Cities

## 题目描述

A 市和 B 市之间有公交车行驶，第一班是早上 $\text{5:00}$ ，最后一班不迟于 $\text{23:59}$ 开出。

从 A 市出发的公共汽车每隔 $a$ 分钟发车，到 B 市需 $t_a$ 分钟，从 B 市出发的公共汽车每隔 $b$ 分钟发一辆车，到 A 市需 $t_b$ 分钟。

司机 Simon 为了增加工作的乐趣，数了数在他的行程途中向他驶来的公交车，但 Simon 没有计算他在起点和终点遇到的公共汽车。

给定 Simon 从 A 城到 B 城的时间，计算 Simon 将会见到的公共汽车的数量。

## 样例 #1

### 输入

```
10 30
10 35
05:20
```

### 输出

```
5
```

## 样例 #2

### 输入

```
60 120
24 100
13:00
```

### 输出

```
9
```

# 题解

## 作者：1qaz234Q (赞：3)

### 题意简述
输入从 A 市出发的公交车的发车间隔时间 $a$ 和到 B 市需要的时间 $t_a$，再输入从 B 市出发的公交车的发车间隔时间 $b$ 和到 A 市需要的时间 $t_b$，最后输入 Simon 出发的时间，格式为 $hh:mm$。第一辆公交车早上 $5:00$ 出发，最后一辆不迟于晚上 $11:59$ 开出。求出 Simon 从 A 市到 B 市见到的公交车数量，不用计算他在起点和终点遇到的公交车。
### 题目分析
把 Simon 的出发时间转换为分钟，方便计算。早上 $5:00$ 就是 $300$ 分钟，晚上 $11:59$ 就是 $1439$ 分钟，晚上 $12:00$ 就是 $1440$ 分钟。

判断向 Simon 驶来的公交车中第一辆的出发时间是否为 $5:00$。如果是，那么向他驶来的第一辆公交车就是第一辆。否则计算是第几辆，向他驶来的第一辆公交车是第 $\left\lfloor\dfrac{c-t_b-300}{b}\right\rfloor+2$ 辆。

然后计算他遇到的最后一辆公交车是第几辆，向他驶来的最后一辆公交车是第 $\left\lceil\dfrac{\min(\min(c+t_a,1440),1439+t_b)}{b}\right\rceil$ 辆。$\min(c+t_a,1440)$ 表示 Simon 到 B 市的时间。

最后计算 Simon 在路上遇到的公交车的数量。

时间复杂度为 $O(1)$。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a,ta,b,tb,h,m;
	cin>>a>>ta>>b>>tb;
	scanf("%d:%d",&h,&m);
	int c=h*60+m;//把时间转换为分钟
	int d;//途中向 Simon 驶来的公交车中第一辆是第几辆
	if(c-tb<300){//如果途中向他驶来的公交车中第一辆出发时间是早上 5:00
		d=1;
	}
	else{
		d=(c-tb-300)/b+2;//计算他遇到的第一辆公交车是第几辆
	}
	int e=ceil(1.0*(min(min(c+ta,1440),1439+tb)-300)/b);//计算途中向他驶来的公交车中最后一辆是第几辆
	int ans=e-d+1;//计算 Simon 在路上遇到的公交车的数量
	cout<<ans;
}
```


---

## 作者：_byta (赞：3)

一道模拟题。

为了简化问题，我把题目中读入的小时全部转化为分钟来处理。那早上 5 点就是第 300 分钟，晚上 12 点就是第 1440 分钟。

接下来我们模拟他的开车过程，可以发现当从 B 地开过来的车只要中途有时间在他的行车范围内，答案就可以加加因此我们只要枚举 B 第的每一辆车即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,x,y,h,m;
int main()
{    
    scanf("%d%d%d%d%d:%d",&a,&x,&b,&y,&h,&m);
    m+=h*60;
    h=0;
    a=300;
    while(a<m+x&&a<1440)
	{
        if(a+y>m)h++;
        a+=b;
    }
    printf("%d",h);
}

```




---

## 作者：Zq_water (赞：1)

本蒟蒻的第一篇题解，若有不足的地方，请多多指教，谢谢。

**题目大意**

~~自己看(逃~~ 

[题目传送门](https://www.luogu.com.cn/problem/CF665A)

**题目思路**

我们是用模拟的方法，~~主要是不会推公式~~。

先将时间转化成分钟：早上 $5$ 点也就是这一天的第 $300$ 分钟，而晚上 $12$ 点就是第 $1440$ 分钟，出发时间 $time$ 为 $ hh\times60+mm $。

模拟开车过程，保证每辆车出发的时间都在司机这这辆车的时间范围内，即 $[time,time+t_a)$。

**还有**(敲黑板)，最后一班不迟于晚上 $11:59$ 开出，所以要判断。

**代码**
```cpp
#include <cstdio>
using namespace std;
int a,ta,b,tb,h,m,t,time,cnt;
int main(){
	scanf("%d %d",&a,&ta);
	scanf("%d %d",&b,&tb);
	scanf("%d:%d",&h,&m);
	time=h*60+m;//计算时间
	t=300;
	while(t<time+ta&&t<1440){
		if(t+tb>time) cnt++;
		t+=b;
	}
	printf("%d",cnt);
	return 0;
} 
```

---

## 作者：Pink_Cut_Tree (赞：1)

### 解题思路

我们将读入的小时、分钟全部转化为分钟处理，这样简便一些。

举例：早上 `5:00` 表示为第 $300$ 分钟。

模拟开车过程，发现当从 B 地开过来的车在路上的时间时间与这位司机在路上的时间重合，两辆车就会相遇，就可以将答案加 $1$。因此我们只要枚举 B 地开过来的每一辆车即可。

### 代码

```cpp
#include<iostream>
#include<cstdio> //scanf的头文件
using namespace std;
int main(){
	int a,b,x,y,hh,mm;
	scanf("%d%d%d%d%d:%d",&a,&x,&b,&y,&hh,&mm); //因为要读入一个冒号，用scanf更好
	mm+=hh*60;
    int ans=0;
    a=300;
    while(a<mm+x&&a<1440){
        if(a+y>mm){
        	ans++;
		}
        a+=b;
    }
	cout<<ans; 
return 0;
}
```


---

## 作者：zsh_haha (赞：1)

### 题目简化

求出司机 Simon 的车在行驶时遇到的**从 $B$ 市到 $A$ 市**的车的数量。

### 细节注意

- 观察样例就可以知道，Simon 的车并不是按 $A$ 市的发车时间出发，也就是说，Simon 可以随时出发。

- 这一点很重要，注意，这里的 $11:59$ 是指**晚上** $11:59$，而不是中午 $11:59$（血的教训）。

- 注意，Simon 没有计算他在起点和终点遇到的公共汽车,意思就是说，在他出发时，刚好有车到站，或者在他到站时，刚好有车出站，他都**不会**记录。

### 思路讲解

我们把 $5:00$ 记作 $0$，晚上 $11:59$ 记作 $1139$；

并且把一切时间化为以“分钟”为单位；

模拟从 $0$ 到 Simon 的车到站时的时刻；

只要有车的出发时间在 Simon 的车的到站时间之前，那么这辆车必定会相遇，好好想一想，是不是这样。

### 通过代码

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a,b,ta,tb,h,m,sum=0;
	cin>>a>>ta>>b>>tb;
	scanf("%d:%d",&h,&m);
	int now=h*60+m-300;
	for(int i=0;i<1140&&i<now+ta;i+=b){
		if(i+tb>now){
			sum++;
		}
	}
	cout<<sum;
	return 0; 
}
```


### ~~AC证明~~
![](https://cdn.luogu.com.cn/upload/image_hosting/9o0nvhgj.png)

---

## 作者：zwy__ (赞：1)

### 题意
 A 和 B 市之间，有公交车行驶，第一班是早上五点，最后一半不晚于晚上十一点五十九分。从 A 市出发的公交车每过 $a$ 分钟开出一班，并且到 B 市需要 $t_a$ 分钟。从 B 市出发的公交车每过 $b$ 分钟开出一班，并且到 A 市需要 $t_b$ 分钟。现在，给出你司机从 A 市去 B 市的时间，计算这位司机在路上能遇到多少辆公交车。
### 思路
这道题比较简单，根据题目要求模拟即可。题目中的时间我会转换成分钟。
+ 由于题目中出现小时和分钟两种单位，所以我们要先装换单位，方便我们计算。
+ 保证每辆车出发的时间都在司机这这辆车的时间范围内，这个范围是 $hh \times 60+mm$ 到 $hh \times 60+mm+t_a$。
+ 每一班车最晚都不会超过晚上十一点五十九分，要进行判断。

梳理出了这些要求，就可以做这道题了。
### 代码
[保证代码正确](https://codeforces.com/problemset/submission/665/199784061)
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,ta,b,tb,hh,mm,t,sum;
char ch;
int main()
{    
    cin>>a>>ta>>b>>tb>>hh>>ch>>mm;
    mm+=hh*60;
    t=300;
    while(t<mm+ta&&t<=1439)
    {
    	if(t+tb>mm)sum++;
    	t+=b;
	}
	cout<<sum;
    return 0;
}
```

---

## 作者：hanyuchen2019 (赞：0)

## 小学生发题解 第15弹 CF665A

[更好的阅读体验](https://www.luogu.com.cn/blog/277757/solution-cf665a)

一道有点坑的模拟题。

### part 0 注意

1. 如果你WA on #4：看一看你计算的时间，有没有可能超过 $23:59$。

2. 如果你在样例1输出 $6$：请读题。
```
Simon没有计算他在起点和终点遇到的公共汽车。
```

---
### part 1 预处理

为了方便计算，我们把所有的时间都转换成分钟，如 

$6:30 \Longrightarrow 6\times60+30=390 \text分$

---
### part 2 思路

参考[柳卡图](https://baike.baidu.com/item/%E6%9F%B3%E5%8D%A1%E5%9B%BE/1644806?fr=aladdin)，可以更深刻的理解这一部分。

我们可以从 $5:00$ 开始，依次判断每一辆从B城到A城的车，如果 Simon 到达B城**之前**这辆车已经发车（要求1），并且 Simon 发车时这辆车**尚未**到达（要求2），就意味着这两辆车会相遇。

---

### part 3 Code
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
	int a,ta,b,tb,h,m,start,end,nt,ans=0;
	cin>>a>>ta>>b>>tb;
	scanf("%d:%d",&h,&m);
	nt=60*5;                //指当前判断的车的发车时间
	start=h*60+m;           //Simon 的发车时间
	end=min(start+ta,24*60);//Simon 到达B城的时间（不能超过23:59）
	while(nt<end)//要求1
	{
		if(nt+tb>start)//要求2
			ans++;
		nt+=b;//枚举下一辆车
	}
	cout<<ans;
 	return 0;
}
```
谢谢您的观看，Bye~

---

