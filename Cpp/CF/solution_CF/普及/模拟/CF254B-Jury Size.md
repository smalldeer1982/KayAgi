# Jury Size

## 题目描述

In 2013, the writers of Berland State University should prepare problems for $ n $ Olympiads. We will assume that the Olympiads are numbered with consecutive integers from 1 to $ n $ . For each Olympiad we know how many members of the jury must be involved in its preparation, as well as the time required to prepare the problems for her. Namely, the Olympiad number $ i $ should be prepared by $ p_{i} $ people for $ t_{i} $ days, the preparation for the Olympiad should be a continuous period of time and end exactly one day before the Olympiad. On the day of the Olympiad the juries who have prepared it, already do not work on it.

For example, if the Olympiad is held on December 9th and the preparation takes 7 people and 6 days, all seven members of the jury will work on the problems of the Olympiad from December, 3rd to December, 8th (the jury members won't be working on the problems of this Olympiad on December 9th, that is, some of them can start preparing problems for some other Olympiad). And if the Olympiad is held on November 3rd and requires 5 days of training, the members of the jury will work from October 29th to November 2nd.

In order not to overload the jury the following rule was introduced: one member of the jury can not work on the same day on the tasks for different Olympiads. Write a program that determines what the minimum number of people must be part of the jury so that all Olympiads could be prepared in time.

## 样例 #1

### 输入

```
2
5 23 1 2
3 13 2 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
12 9 2 1
12 8 1 3
12 8 2 2
```

### 输出

```
3
```

## 样例 #3

### 输入

```
1
1 10 1 13
```

### 输出

```
1
```

# 题解

## 作者：NEO_bone (赞：4)



[题目链接](https://www.luogu.com.cn/problem/CF254B)  
十分简单的一道题，但也有一些~~使人崩溃~~小小的坑点，数据太弱，线段树什么的都不需要！

由于比赛的跨年举办，我们至少需要将数组右移 $100$ 位。  
处理后，只需要对每个操作进行暴力更改就好啦！  
具体的写法是将月份换算成天数，存入数组，根据每次询问只需要向前推相应的天数，将上相应的人数，最后遍历这一年取最大值。

### code
```cpp
#include <math.h>
#include <stdio.h>
#define max(a,b) (a>b)?(a):(b)
int n,f[566],a,b,c,d,maxn;
int k[13]={0,0,31,59,90,120,151,181,212,243,273,304,334};
int main()//QAQ
{
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    scanf("%d",&n);
    while(n--)
    {
        scanf("%d",&a);//举办的月份
        scanf("%d",&b);//举办的具体时间
        scanf("%d",&c);//需要多少人
        scanf("%d",&d);//指从d天前就该开始准备了！
        d--;
        int l=k[a]+b-d+100;//将数据处理，防止数组越界
        int r=k[a]+b+100;
        // cout<<l<<' '<<r<<' '<<c<<endl;
        for(int i=l;i<=r;i++)
        f[i]+=c;
    }
    for(int i=101;i<=465;i++)//循环便捷问题参照18，19行
    maxn=max(maxn,f[i]);
    printf("%d",maxn);//do not copy this code
    return 0;
}
```

---

## 作者：Breath_of_the_Wild (赞：0)

题意：在一个平年中，共有 $n$ 个活动，给定活动开始（月份，日期），这个活动需要的人数，以及需要提前准备的时间，求最少需要多少人。

思路：把日期转化为数字（即改为一年中第几天的形式），记录每天的人数，并求最大值。

注意：由于活动可能跨年举行，因此记录的每天的人数至少要多开 $100$ 天。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int days[]={0,31,59,90,120,151,181,212,243,273,304,334,365};
/*a[i]:前 i 月共有多少天，相当于月天数的前缀和*/
int n,ans=0,res[666],mon,dy,pep,tim,a,b; 
int main(){
	cin>>n;
	while(n--){
		cin>>mon>>dy>>pep>>tim;
		tim--;
		b=days[mon]+dy+100,a=b-tim;//加一百：跨年
		for(int i=a;i<=b;i++){
			res[i]+=pep;
			ans=max(ans,res[i]);//每日打擂台求最多人数
		}
	}
	cout<<ans;
	return 0;
}

---

## 作者：guozhe6241 (赞：0)

# 题目传送门

[CF254B](https://www.luogu.com.cn/problem/CF254B)

# 思路

这题的思路就是枚举每一天看一下需要多少人，因为一个人不会用两个人的额，所以我们只需要把每天需要的人数取最大值就可以了。

ps：这题要开大空间，否则会 WA 。

# 代码

```cpp
#include<bit/stdc++.h>
using namespace std;
int n,m,d,p,time;
int ans;
int k[13]={0,0,31,59,90,120,151,181,212,243,273,304,334};
int t[1005];
void solve(int m,int d,int p,int time){
	int st=k[m]+d-time+101;
	int la=k[m]+d+100;
	for(int j=st;j<=la;j++){
		t[j]+=p;
	}
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>m>>d>>p>>time;
		solve(m,d,p,time);
	}
	for(int i=101;i<=465;i++){
		ans=max(ans,t[i]);
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：nominater (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/CF254B)

## 思路：
先将月份全部转换为天数，用 $l$ 代表比赛的初始时间，用 $r$ 表示比赛的结束时间，将 $l$ 和 $r$ 看作在一条数轴上的两个点。$person$ 即为 $l$ 和 $r$ 两者之间的元素个数。视 $l$ 和 $r$ 为一个集合的区间，对 $l$ 和 $r$ 的并集的所有元素进行 $\max$ 比较，得出的即为答案 $maxn$。  
## 代码

```Plain Text
#include <bits/stdc++.h>
using namespace std;
const int N = 1e2 + 10;
int n, month[N], day[N], person[N], con[N], f[11450];
int l, r;
int d[13] = {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
int maxn;
int main()
{
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    cin >> n; // 比赛次数
    for (int i = 1; i <= n; i++)
    {
        cin >> month[i] >> day[i] >> person[i] >> con[i];
        l = d[month[i]] + day[i] - con[i] + 101;
        //last
        r= d[month[i]] + day[i] + 100;
        //begin
        f[r+1]-=person[i],f[l]+=person[i];
    }
    for (int i = 1; i <= 465; i++) 
    {
        f[i] += f[i - 1];
    }
    for (int i = 101; i <= 465; i++)
    {
        maxn = max(maxn, f[i]);
    }
    cout<<maxn;
    
    return 0;
}
```











---

## 作者：metrixgo_caozhendi (赞：0)

题意抽象成求多个区间重叠在一起时，最大的数是多少。这里我们可以把每一个输入统统换成天数，将准备区间（也就是开始时间减去持续时间）加上所需人数。最后找到所需人数最大的天数，即为所求。

注意到可能会在去年准备，所以加上一个大于 $100$ 的数可以有效地避免问题。数据很小，所以随便搞搞都可以过。

$13$ 行极简代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int i,j,n,yue,tian,ren,chixu,maxn,days[14]={0,0,31,59,90,120,151,181,212,243,273,304,334,365};
int ans[1005];
int main()
{cin>>n;
    for(i=1;i<=n;i++){
        cin>>yue>>tian>>ren>>chixu;
        for(j=days[yue]-chixu+1+tian;j<=days[yue]+tian;j++) ans[j+400]+=ren;
    }//输入数据，将时间转化为天数
    for(i=401;i<=750;i++) maxn=max(maxn,ans[i]);
    cout<<maxn;
    return 0;}
```

---

## 作者：封禁用户 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF254B)

# First 题意

可能翻译的不太好，大家理解有点问题，我来补充一下。

先输入一个 $n$。

再输入 $n$ 行，每行输入四个变量，分别是月份，日期，人数，时间。

比如输入如下。
```
1
12 8 2 5
```

指的是从 $12$ 月 $3$ 日到 $12$ 月 $8$ 日需要 $2$ 人。

求至少要几个人。

# Second 暴力

首先注意，人是可以重复利用的，所以问题其实就是求几个区间的最大值。

例如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/98a7nbhp.png)

红色部分是区间，红色数字是人数，绿色区间是人数和最多的区间。

那么我们就有了一个思路。

因为 $n \le 100$，区间长度 $\le 365$，所以可以用桶来记录每个日期所需的人数，然后取桶中的最大值。

设 $w$ 为最长区间的区间长，那么时间复杂度是 $O(nw+w)$ 的。

注意，区间左端点可能是负数，所以要 $+100$ 再用桶记录。

还有，记得开 `freopen`，~~鬼知道我因为这个 WA 了几次呀~~。

# Third 优化

虽然上面的时间复杂度可以通过，但是还有更优的方法。

### 差分

使用差分，就可以在 $O(n+w)$ 的时间复杂度内求解了。

# Fourth Code

暴力 Code

```cpp
#include <math.h>
#include <stdio.h>
using namespace std;
inline int max(int a, int b){
	return  a > b ? a : b;
}
int n, mon, day, peo, tim, t[5005], ans;
int k[13] = {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
int main(){
	freopen ("input.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++){
		scanf ("%d %d %d %d", &mon, &day, &peo, &tim);
		int st = k[mon] + day - tim + 101;
		int la = k[mon] + day + 100;//计算左右端点
		for (int j = st; j <= la; j++) t[j] += peo;//暴力增加
	}
	for (int i = 101; i <= 465; i++) ans = max(ans, t[i]);//求解
	printf ("%d", ans);
	return 0;
}
```

优化后 

```cpp
#include <math.h>
#include <stdio.h>
using namespace std;
inline int max(int a, int b){
	return  a > b ? a : b;
}
int n, mon, day, peo, tim, t[5005], ans;
int k[13] = {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
int main(){
	freopen ("input.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++){
		scanf ("%d %d %d %d", &mon, &day, &peo, &tim);
		int st = k[mon] + day - tim + 101;
		int la = k[mon] + day + 100;
		t[la + 1] -= peo, t[st] += peo;//差分
	}
	for (int i = 1; i <= 465; i++) t[i] += t[i - 1];//前缀和
	for (int i = 101; i <= 465; i++) ans = max(ans, t[i]);
	printf ("%d", ans);
	return 0;
}
```

---

