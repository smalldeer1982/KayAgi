# [USACO07MAR] Monthly Expense S

## 题目描述

Farmer John is an astounding accounting wizard and has realized he might run out of money to run the farm. He has already calculated and recorded the exact amount of money (1 ≤ moneyi ≤ 10,000) that he will need to spend each day over the next N (1 ≤ N ≤ 100,000) days.

FJ wants to create a budget for a sequential set of exactly M (1 ≤ M ≤ N) fiscal periods called "fajomonths". Each of these fajomonths contains a set of 1 or more consecutive days. Every day is contained in exactly one fajomonth.

FJ's goal is to arrange the fajomonths so as to minimize the expenses of the fajomonth with the highest spending and thus determine his monthly spending limit.

给出农夫在n天中每天的花费，要求把这n天分作m组，每组的天数必然是连续的，要求分得各组的花费之和应该尽可能地小，最后输出各组花费之和中的最大值


## 说明/提示

If Farmer John schedules the months so that the first two days are a month, the third and fourth are a month, and the last three are their own months, he spends at most $500 in any month. Any other method of scheduling gives a larger minimum monthly limit.


## 样例 #1

### 输入

```
7 5
100
400
300
100
500
101
400```

### 输出

```
500```

# 题解

## 作者：s_ShotღMaki (赞：10)

看有大佬在讨论区里求助，我做了一下这个题

这题的话首先我们读题，看看是考什么的！

(读着读着题目 诶诶诶！！！这题我好像做过诶！

## [P1182](https://www.luogu.org/problemnew/show/P1182)是你，是你！！！就是你！

于是复制那题提交过的代码就秒掉了

咳咳，进入正题，本题是一个

## 二分+贪心

其实非常好做，类似一个二分的板子题，我看了一下题解，大家都是用

## 前缀和

但那样有点浪费空间呢！所以我们check函数要这个样子，每次都全扫一遍，加上跟tot比一比，如果小于就加上，最后比一比num和m就好了，如果小，那就说明是合法的！

但l一定要取所有数中最大的哦！

### 贴完整代码

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;

inline int read ()
{
    int f = 1, x = 0;
	char ch;
    do {ch = getchar (); if (ch== '-') f = -1;} while (ch < '0' || ch > '9');
    do {x = x * 10 + ch - '0'; ch = getchar ();} while (ch >= '0' && ch <= '9');
    return f * x;
}

int n, m;
int a[100005];
int l, r, mid;
int ans;

inline bool check (int hehe)
{
	int tot = 0, num = 0;
	for (int i = 1; i <= n; i ++)
	{
		if (tot + a[i] <= hehe) tot += a[i]; //如果装得下就加上
		else tot = a[i], num ++;//装不下就num++
	}
	return num >= m;
}

int main ()
{
	n = read (); m = read ();
	for (int i = 1; i <= n; i ++)
	{
		a[i] = read ();
		l = max (a[i], l);
		r += a[i];
	}
	while (l <= r) //二分板子
	{
		mid = l + r >> 1;
		if (check (mid)) l = mid + 1, ans = l;
		else r = mid - 1, ans = l;
	}
	printf ("%d\n", ans);
	return 0;
}
```
可以说是很快的辣！而且空间用的也少！

---

## 作者：zhaowangji (赞：8)

见题“要求分得各组的花费之和应该尽可能地小，最后输出各组花费之和中的最大值”，出现最大值最小（注意：不是最小值最大，一开始也理解错了，因为是开销最大的一组，其开销要最小）

考虑使用二分答案

```cpp
#include<iostream>
using namespace std;
int n,m;
int a[100007];//看题
int l,r,mid;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		l=max(l,a[i]);//预处理，最小开销至少跟花费最大的那个月一样
		r+=a[i];//最大开销可能是所有的月加起来
	}
	while(l<r){//模板
		mid=(l+r)/2;
		int sum=0,cnt=0;
        	//sum是累加当前的钱，cnt是要分成几组
		for(int i=1;i<=n;i++){
			if(sum+a[i]<=mid)//如果加上这个月的花费还比枚举到的开销小
				sum+=a[i];//那就继续加
			else sum=a[i],cnt++;//不然就要分一组出来
		}
		if(cnt>=m)l=mid+1;//可分的组数较多，说明开销还可以更大
		else r=mid;//开销太大导致分的组数少
	}
	cout<<l<<endl;//最后l即为答案
	return 0;
}
```


---

## 作者：y2823774827y (赞：6)

简单的二分
每次查询只要判断
1. 是否每天的花费都不超过now（查询的解）
1. 是否该解所需组数满足题目要求m

 上代码
```cpp
# include<cstdio>
# include<algorithm>
using namespace std;
int n,m,a[100005],l=0x7fffff,r=0,mid;
bool judge(int now){//二分模板 
	int k=now,shu=1;
	for(int i=1;i<=n;++i){
		if(a[i]>now) return false;
		else{
			if(k-a[i]<0){
			    ++shu; k=now-a[i];	
			}
			else k-=a[i];
		}
	}
	if(shu>m) return false;
	return true;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]); 
		r+=a[i]; l=min(l,a[i]);//确定数据范围 
    }
	while(true){//无限循环 
		mid=(l+r)/2; 
		if(judge(mid)) r=mid;else l=mid+1;//二分 
		if(l==r){
			printf("%d",l);//已经找到解输出 
			return 0;
		}
	}
}
```

---

## 作者：Mysterious_bird (赞：5)

一道简单的**二分答案**

题目不难理解，问$n$个数分成$m$段，并且**每段的和的最大值最小**

最大值最小，最小值最大……暴露出这题是二分答案，这也是做题时的一个小技巧，快速分辨出这题用什么方法

为了让新学二分的同学理解二分答案的思想，让我来

### 手动模拟出样例如何求出500

根据样例可得，7个数要分成五段，并且**每段连续**

左边界取7个元素中最大的一个，也就是500；（如果不是最大的一个数，根本不能分）

右边界为7个元素之和，也就是1901（最大7个数合成一段）

| 100 | 400 | 300 | 100 | 500 | 101 | 400 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |

此时$mid$为$(Left+Right)/2$，也就是1200（向下取整）

这时，判断每段和为1200是否合法

100+400+300+100=900

500+101+400=1001

只分成了两段，不合法，为了分的段数更多，需要将每段和缩小，也就是调整左边界，此时$Right$为$mid-1$，1199

继续分，$mid=(1999+500)/2=849$（任然向下取整）

100+400+300=800

100+500+101=701

400

三段，不合法，继续分

$Right=mid-1=849-1=848$

$mid=(500+848)/2=674$

100+400=500

300+100=400

500

101+400=501

四段，继续

$Right=mid-1=674-1=673$

$mid=(500+673)/2=586$

100+400=500

300+100=400

500

101+400=501

四段，继续

$Right=mid-1=586-1=585$

$mid=(500+585)/2=542$

100+400=500

300+100=400

500

101+400=501

……………

直到——$Right=500$，$Left=500$

100+400=500

300+100=400

500

101

400

这时，正好分为五段，并且每段最大值最小

~~ohhhhhhhhhhhhhhhhhhhhhhhhhhhh~~

理解了样例，开始写代码

Left=所有元素中最大的一个，Right=所有元素之和

在读入时顺便做掉
```cpp
for(int i=1;i<=N;i++)
{
    cin>>a[i];
    Left=max(Left,a[i]);
    Right+=a[i];
}
```
然后是整个代码的精髓，check函数，用来判断当前分的段数是否合法
```cpp
bool check(int mid)
{
    int total=0,cnt=0;  //total用于记录当前段之和，cnt计数
    for(int i=1;i<=N;i++)
    {
        if(total+a[i]<=mid) total+=a[i];    //如果total+a[i]还没有超过当前最大容量
        else
        {
            total=a[i]; //如果装不下了，新开一段放进去
            cnt++;  //新加一段
        }
    }
    if(cnt>=M) return true; //如果比M大，说明左边界还要调
    else return false;  //否则右边界调
}
```
### Code
```cpp
#include <iostream>
#include <cmath>
using namespace std;
int a[100010];
int Left,Right,mid;
int N,M;
bool check(int mid)
{
    int total=0,cnt=0;  //total用于记录当前段之和，cnt计数
    for(int i=1;i<=N;i++)
    {
        if(total+a[i]<=mid) total+=a[i];    //如果total+a[i]还没有超过当前最大容量
        else
        {
            total=a[i]; //如果装不下了，新开一段放进去
            cnt++;  //新加一段
        }
    }
    if(cnt>=M) return true; //如果比M大，说明左边界还要调
    else return false;  //否则右边界调
}
int main()
{
    cin>>N>>M;
    int ans=0;
    for(int i=1;i<=N;i++)
    {
        cin>>a[i];
        Left=max(Left,a[i]);    //左边界
        Right+=a[i];    //右边界
    }
    while(Left<=Right)
    {
        mid=(Left+Right)/2;
        if(check(mid)) 
        {
            Left=mid+1; //调整左边界
            ans=Left;   //答案记录为左边界
        }
        else
        {
            Right=mid-1;    //调整右边界
            ans=Left;
        }
    }
    cout<<ans<<'\n';
    return 0;
}
```
另外分享一套二分模板
```cpp
while(Left<=Right)
{
    mid=(Left+Right)/2;
    if(check(mid)) 
    {
        Left=mid+1; //调整左边界
        ans=Left;   //答案记录为左边界
    }
    else
    {
        Right=mid-1;    //调整右边界
        ans=Left;
    }
}
```
THE END.

---

## 作者：ctq1999 (赞：5)

## 前言

这是我$pj$模拟赛的$T2$的原题，但当时出题人出题人粘原题时出锅了，导致 100-->60

## 思路

前置知识：二分答案

二分每组的花费$mid$

贪心出至少要分多少组才符合当前的$mid$

若不行，则

```
l = mid + 1;
```

左端点右移，同时因为$mid$这个值不可取，还要$+1$

若可以那么更新右端点

如果看懂思路的话就可以自己写了哦，这样收获会更多

如果仅凭思路没看懂的话，可以提出建议通知我@ctq1999修改

## 代码

```cpp

#include <bits/stdc++.h>

#define MAXN 100010

using namespace std;

int n, m;
int l, r, mid;

int a[MAXN];

bool check(int x) {
	int i = 1;
	int sum = 0;
	int num = 0;
	while (i <= n) {
		if (sum + a[i] <= x) sum += a[i];
		else {
			num++;
			sum = a[i];
		}
		i++;
	}
	if (num <= m) return 1;
	else return 0;
}
//贪心判断是否可行

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		l = max(l, a[i]);
		r += a[i];
	}
   //左端点：至少比每个值大，否则怎么分
   //右端点：最多一组，也就是全部的花费
	mid = (l + r) >> 1;
	while (l + 5 < r) {
		if (check(mid)) r = mid;
		else l = mid + 1;
		mid = (l + r) >> 1;
	}
   //l + 5 < r 是避免死循环，防止怎么更新l和r一直不等
	for (int i = l; i <= r; i++) {
		if (check(i)) {
			cout << i << endl;
			return 0;
		}
      //若有i值可以，直接输出，程序结束
	}
	return 0;
}

```

> 日拱一卒，功不唐捐


---

## 作者：Parat_rooper (赞：1)

# 解题思路：
首先，我们第一眼看到这题肯定觉得这是一个最优性问题，但直接用最优性问题来解似乎太复杂，那有没有什么既可以解决这道题又十分简单有效的方法呢？

在此，向大家推荐二分答案。二分答案是一种将最优性问题转换为可行性问题的方法，运用了二分的思想，通过二分所有组和的最大值再进行校验可以很简单的解决这道题。

而校验则是使用贪心，这确实是一道很不错的贪心加二分答案板子题。

代码如下：
```cpp
#include <iostream>

using namespace std;

const int kMaxN = 1e5 + 1;

int n, m, l = 1, r, a[kMaxN];

bool check(int s) {
  int k = 0;//k记录有多少组
  for (int i = 1, sum = 0; i <= n; i++) {//sum记录组和
      sum += a[i];
      if(sum > s) {//如果超过s就加一个组
      sum = a[i];
      k++;
    }
  }
  return k < m;
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    r += a[i];
    l = max(a[i], l);//这里注意左边界要设在元素最大值上不然要在校验中判
  }
  while (l <= r) {//二分板子
    int mid = (l + r) >> 1;
    if (check(mid)) {//组比m少，更新最大值
      r = mid - 1;//最大值越小，组越多
    } else {//否则更新最小值
      l = mid + 1;//最大值越大，组越少
    }
  }
  cout << r + 1;
  return 0;
}
```


---

## 作者：Hilte (赞：1)

# 一.确定思路
这题实际上看到题意就知道最简方法就是二分。  
因为“要求分得各组的花费之和应该**尽可能地小**，最后输出各组花费之和中的**最大值**。”  
由此看出需要**较慢的枚举**或**更快的二分**。

# 二.制定处理方式
定义 $C(x)$ 代表每日将最大值设为 $x$ 元时会不会超限。  
我们需要累加每天的钱数，如果超过了 $x$ 就要增加一天。  
处理方式如下：
```cpp
#define MAXN 100000+100//N的最大值
#define min(x,y)  x<y?x:y
int N,M;//M为目标天数
int cost[MAXN];

bool C(int x)每日将最大值设为x元时会不会超限
{
    int n=1;//天数
    int tmp=0;//总钱数
    for(int s=0;s<N;s++)//枚举每一天的钱数
    {
        if(tmp+cost[s]<=x)//如果还能加的话，继续累加
            tmp+=cost[s];
        else//大于目标
        {
            n++;//天数加一
            tmp=cost[s];//从s天开始下一次累加，初始值记为cost[s]
        }
    }
    if(n>M)//如果总天数大于目标天数，不符合
		return false;
    else//否则可以
		return true;
}
```


# 三.AC代码
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
#define MAXN 100000+100//N的最大值
#define min(x,y)  x<y?x:y
int N,M;//M为目标天数
int cost[MAXN];

bool C(int x)每日将最大值设为x元时会不会超限
{
    int n=1;//天数
    int tmp=0;//总钱数
    for(int s=0;s<N;s++)//枚举每一天的钱数
    {
        if(tmp+cost[s]<=x)//如果还能加的话，继续累加
            tmp+=cost[s];
        else//大于目标
        {
            n++;//天数加一
            tmp=cost[s];//从s天开始下一次累加，初始值记为cost[s]
        }
    }
    if(n>M)//如果总天数大于目标天数，不符合
		return false;
    else//否则可以
		return true;
}


int main()
{
    while(cin>>N>>M)//有多组数据
    {
        int l=0,r=0;//二分边界变量
        for(int i=0;i<N;i++)//输入并确认二分边界
        {
            cin>>cost[i];
            r+=cost[i];
            l=max(cost[i],l);
        }
        int mid=l+(r-l)/2;
        while(l<r)//二分
        {
            if(C(mid))
		r=mid-1;
            else
                l=mid+1;
            mid=l+(r-l)/2;
        }
        cout<<mid<<endl;
    }
    return 0;
}
```


---

## 作者：Drug__Lover (赞：1)

**二分答案**

**取下界L为每天的花费的最小值**

**上界R为每天花费的和**

**不断取MID**

**用check（）判断该答案是否可行**


```cpp
int check(int maxx)
{
    int cnt=1;    //一开始的组数
    int now=0;   //一开始的和
    for(int i=1;i<=n;i++)
    {
        if(a[i]>maxx) return 0;   //如果当前这一天的费用大于此次二分的答案了，那么这个答案一定不行，直接返回0就可以了
        if(now+a[i]>maxx)   //如果当前组数中的和大于二分的值了，那就再重新开一组
        {
            cnt++;     //组数加以
            now=a[i];    //更新和
        }
        else now+=a[i];       //和小于二分的值直接加上就好
    }
    if(cnt>m) return 0;      //如果组数大于要求的组数，那么这该二分的答案太小了，就返回0，让L大一些
    return 1;      //不然就合法，返回1，看看让R小一些行不行
}
```
**因为是求最小值**

**所以答案合法的时候是减小范围，不合法就增大范围**


```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#define maxn 100010
using namespace std;
int n,m;
int a[maxn];
int l=0x7fffffff,r;
int mid;
int ans;
int check(int maxx)
{
    int cnt=1;
    int now=0;
    for(int i=1;i<=n;i++)
    {
        if(a[i]>maxx) return 0;
        if(now+a[i]>maxx)
        {
            cnt++;
            now=a[i];
        }
        else now+=a[i];
    }
    if(cnt>m) return 0;
    return 1;
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),r+=a[i],l=min(l,a[i]);
    while(l<=r)
    {
        mid=(r+l)/2;
        if(check(mid)) r=mid-1,ans=mid;
        else l=mid+1;
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：puluter (赞：1)

挺简单的二分裸题。

初始的时候把l设为0，r设为sum(a[i]的和)，然后二分check一下就可以了。

这个题和NOIP2015Day2T1跳石头几乎一模一样的做法，可以去做做那道题感受一下

时间复杂度O(nlogn)。

```cpp
#include<iostream>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define ll long long
using namespace std;
int a[100005]={0};
int n,m,sum=0;

int rd(){
    int ans=0;
    char p=getchar();
    while(p<'0'||p>'9') p=getchar();
    while(p>='0'&&p<='9') ans=ans*10+p-'0',p=getchar();
    return ans;
}

bool check(int d){
    int sumn=0,tp=m;
    rep(i,1,n){
        if(tp<0) return false;
        if(a[i]>d) return false;
        if(sumn+a[i]>d) tp--,sumn=a[i];
        else sumn+=a[i];
    }
    return true;
}

int main(){
    cin>>n>>m;
    rep(i,1,n) a[i]=rd(),sum+=a[i];
    m--;
    int l=0,r=sum,mid,t=0;
    while(l<r){
        mid=l+r>>1;
        if(check(mid)) t=mid,r=mid;
        else l=mid+1;
    }
    cout<<t;
    return 0;
}

```

---

## 作者：cyrxdzj (赞：0)

### 一、思路

本题与使用贪心算法和二分算法即可。

使用二分算法猜测答案（即每一段之和的最大值）。如果猜测值导致需要分更多段（或者分段数与 $m$ 一致），则增加答案，以分出更少段。如果猜测值导致不需要分太多段，则减少答案。

那么如何检查分段数量呢？

首先，设一个 $total$ 代表当前一段的总和，$num$ 表示分段数量。

然后，顺序遍历整个输入数组。如果 $total$ 加上数组当前元素大于猜测值，则将 $total$ 置为数组当前元素，并将 $num$ 自增 $1$。否则，将 $total$ 加上数组当前元素。

具体代码参见 `check_answer` 函数。

### 二、完整代码

```cpp
#include<cstdio>
using namespace std;
int n,m,input[100005];
int left,right;
bool check_answer(int x)//检查实际分段数是否不小于m。
{
	int total=0,num=0;
	for(int i=1;i<=n;i++)
	{
		if(total+input[i]<=x)//如果能装得下，那就尽量装下。
		{
			total+=input[i];
		}
		else//如果装不下，就再分一段。
		{
			total=input[i];
			num++;
		}
	}
	return num>=m;
}
inline int max(int a,int b)
{
	return a>b?a:b;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&input[i]);
		left=max(input[i],left);//定left和right的取值范围。
		right+=input[i];
	}
	while(left<=right)
	{
		int middle=(left+right)>>1;//二分板子。
		if(check_answer(middle))
		{
			left=middle+1;
		}
		else
		{
			right=middle-1;
		}
	}
	printf("%d\n",left);//输出。
	return 0;//完结撒花！
}

```

By [dengzijun](https://www.luogu.com.cn/user/387836)

---

## 作者：天才颓废学家 (赞：0)

# [咦？](https://www.luogu.com.cn/problem/P1182)
###### ~~双倍精盐，双倍快乐~~
话说这道重题为什么没被爆破捏？


------------

这是一篇垃圾的P党题解。
## 题意简述
FJ因为太穷，想把$n$天的开销分为$m$段(这有什么关系)，由于他好奇心很强(?)，想知道$m$段中最大值最小能达到多少。其实就是
### 数列分段!


------------

## ~~心路历程~~ 做题方法
当我拿到这道题时：看见“**大值最小能达到多少**”就腿短，这一定是**二分**题！再深入思考，啊，啊，啊~~在哪里，在哪里见过你~~~答案具有单调性，即当$n$符合要求时，$n+1$也一定符合要求。只需要二分出一个假定答案，再通过枚举所有花费来验证其即可。这道题没有什么特殊的坑点，所以接下去，我们开始


## 代码实现
### 1.二分模板
二分其实有很多种模板，但下面这种基本是通用的。
```
var
 a ba a ba a ba;
function check(x:longint):boolean;
var
 a ba a ba a ba;
begin
 a ba a ba a ba;
end;
begin
 a ba a ba a ba;
l:=0; r:=maxlongint div 3;
while l<=r do
 begin
  mid:=(l+r) div 2;
  ①if check(mid) then begin (ans:=l;) l:=mid+1; end
   else r:=mid-1
 end;
 a ba a ba a ba;
end.
```
说明：“ a ba a ba a ba;”视具体情况填写。①句后面的指针变动也可以上下互换。
### 2.$check$函数的具体编写方式
题面要求把这n天分作m组，但不一定要m组都分到，即可以有空组。所以只需从1到n枚举一遍，
```
                       /(1).小于等于mid，那么就把a[i]加进当段的和
                      /
若当前段的和加上a[i]--<
                      \
                       \(2).大于mid，则另创一组，并把组数加一，当前段的和赋为a[i]；
```
最后根据实际组数和要求组数的大小关系来判断是否符合要求。
#### 放代码！
```
function check(k:longint):boolean;
var
 i,s:longint;
 ans:int64; //防数据阴人
begin
 ans:=0; s:=1; //至少分为一组
 for i:=1 to n do
  begin
   if ans+a[i]<=k then ans:=ans+a[i] //加入当前组
    else
     begin
      ans:=a[i]; //另立门户
      inc(s);
     end;
  end;
 exit(s<=m); //前面赋0也可以，不过这里就不能有等号了
end;
```
### 3.主程序的具体编写方式
很简单，直接套模板即可。
#### 放代码！
```
var
 r:int64; //防数据阴人
 n,m,i,l,mid:longint;
 a:array[0..100100]of longint;
function check(k:longint):boolean; //验证答案是否符合要求
var
 i,s:longint;
 ans:int64;
begin
 ans:=0;s:=1;
 for i:=1 to n do
  begin
   if ans+a[i]<=k then ans:=ans+a[i]
    else
     begin
      ans:=a[i];
      inc(s);
     end;
  end;
 exit(s<=m);
end;
begin
 read(n,m);
 for i:=1 to n do
  begin
   read(a[i]);
   r:=r+a[i];
   if l<a[i] then l:=a[i]; //要是懒的话r直接赋maxlongint div 2就好，反正二分快。
  end;
 while l<=r do //二分板子
  begin
   mid:=(l+r) div 2;
   if check(mid) then r:=mid-1
    else l:=mid+1;
  end;
 writeln(l);
end.
```
~~以下wyy警告：~~

P党还是要快转C++，毕竟2022年开始CCF系列竞赛就不允许使用Pascal/C了。
###### ~~不要像我一样老顽固~~
好了，本篇题解到此就差不多结束了，不止各位巨佬是否满意，如有错误，请批评指正(づ￣3￣)づ╭❤～


更新日志
##### $2020-10-22$ A了这题发现可以写题解

##### $2020-10-23$ 提交初稿

##### $2020-10-24$ 未通过555，也对浪费管理大大时间抱歉！

##### $2020-10-25$ 二稿
%%%orz sto%%%

%%%orz sto%%%

---

## 作者：程序猿小颜 (赞：0)

## 这道题用的是二分算法，还算比较简单。
![](https://cdn.luogu.com.cn/upload/pic/62778.png)
### 二分，指的是一种可以把最大查找次数降低到log2(n)的查找算法。
### 时间复杂度只有O(log2(n))!!!
### 因此，大家以后可以多多用二分！
### （提示：数组必须有序！）
### 示例：
![](https://cdn.luogu.com.cn/upload/pic/62779.png)
## 好了，直接上代码！

------------
```
#include <bits/stdc++.h>
using namespace std;

long long n, m;
long long a[100005];

long long judge(long long x) {
    long long count = 1, s = 0;
	for (long long i = 0; i < n; i++) {
		if (a[i] > x) {
			return 0;
		}
		if (s + a[i] > x) {
			count++;
			s = 0;
		}
		s += a[i];
	}
	return count <= m;
}

int main() {
	cin >> n >> m;
	long long L = 10005, R = 0, M;
	for (long long i = 0; i < n; i++) {
		cin >> a[i];
		R += a[i];
		L = min(L, a[i]);
	}
	while (L + 1 < R) {
		M = (L + R) >> 1;
		if (judge(M)) {
			R = M;
		} else {
			L = M;
		}
	}
	cout << R;
    return 0;
}
```


---

## 作者：骆钿皓 (赞：0)

~~这是本蒟蒻的第3篇题解，希望能支持。~~

其实这道题因为数据较大，所以很快就会想到二分答案解决这道题。

不多说，上程序。

------------


```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
using namespace std;
int lo=0,ri,mid,sjuxiaojjans,n,m,a[10000005],cout1,cout2,maxx,p,d=-21000000;
bool com(int maxx1)
{
	cout1=1;
    cout2=0;
    for(int i=1;i<=n;i++)
    {
        if(a[i]>maxx1) return 0;
        if(cout2+a[i]>maxx1)//如果这个数大于花费的话，则组数++；
        {
            cout1++;//组数++；
            cout2=a[i];
        }
        else cout2+=a[i];//加上今天的花费
    }
    if(cout1>m) return 0;//如果组数超过m，这个答案不可行；
    return 1;//否则可行
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) 
	{
        scanf("%d",&a[i]);
	}
	lo=0;
	ri=1000000000;
    while(lo+1<ri)
    {
        mid=(ri+lo)/2; //二分求出花费值
        if(com(mid)) ri=mid;//判断
        else lo=mid; 
    }
    printf("%d",ri);//输出
    return 0;//完美结束
}
```


---

## 作者：封禁用户 (赞：0)

看到没有pascal的就来一个

主要就是用二分来寻找答案

其中的左右边界可定为每月开销的最大值和所有开销之和（即m=n和m=1时的情况）

再用check函数判断是否可行

**
```cpp
var i,n,m,j,l,r,ans,max,mid,sum:longint;
    a:array[0..100000] of longint;
function check(x:longint):boolean;
var i,j,k,l,cnt:longint;
begin
  cnt:=1;      j:=0;定义当答案为x时的周期数和一个fato月中的开销值
  for i:=1 to n do
    begin
      if j+a[i]<=x then inc(j,a[i])//如果开销不超过x则累加
      else begin
        inc(cnt);//如果开销超过x则进入下一个fato月
        j:=a[i];
      end;
      if cnt>m then exit(false);//如果周期数大于m就不能成立
    end;
  exit(true);
end;
begin
  readln(n,m);
  for i:=1 to n do
    begin
      readln(a[i]);
      inc(sum,a[i]);
      if a[i]>max then max:=a[i];
    end;
  l:=max;r:=sum;//左右边界定为每月开销的最大值（l）和所有开销之和（r）（即m=n和m=1时的情况
  while l<=r do
    begin
      mid:=(l+r)div 2;
      ans:=mid;
      if check(mid) then r:=mid-1 else l:=mid+1;
    end;//二分答案
  writeln(mid);
end.
**
```

---

## 作者：penghaotian (赞：0)

开始二分的上界为n天花费的总和（相当于分成1份），下界为每天花费的最大值（相当于分成n份），然后二分，每次的mid值为（上界 + 下界）/ 2，然后根据mid值遍历n天花费，对n天的花费进行累加，每当超过mid值 份数++，看看这个mid值能把n天分成几份，如果份数大于m，表示mid偏小，下界 = mid + 1，反之小于等于mid，上界 = mid - 1，然后输出最后的mid值即可，复杂度为 O(nlogM)，M约为第一次的上界。

这个花费的最大值一定介于所有值的和与所有天数中最大的哪一个。直接让l = maxday ,r = sum然后取中值，枚举，从第一天开始，如果现在的金钱大于mid,那么组数就+1这样就检查组数即可，假设是小于，说明这个mid值明显偏大。这样即可找出答案

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
int n,m,num,max1,max2,ans,l,r,mid;
int a[100001];
bool ok(int x) {
    int money=a[1];
    int zhu=1;
    max2=0;
    for (int i=2;i<=n;++i) {
        if (money+a[i]<=x) {
            money=money+a[i];
            if (money>max2) max2=money;
        } 
        else {
            zhu++;
            money=a[i];
            if (money>max2) max2=money;
        }
    }
    if (zhu<=m) return 1;
    else return 0;
}
int main() {
    //freopen("monthly-expense.in","r",stdin);
    //freopen("monthly-expense.out","w",stdout);
    cin>>n>>m;
    num=0;
    for (int i=1; i<=n; ++i) {
        cin>>a[i];
        num=num+a[i];
    }
    l=1;
    r=num;
    ans=num;
    max1=0;
    while (l<r) {
        mid=(l+r)/2;
        //cout<<mid<<endl;
        if (ok(mid)) {
            ans=mid;
            max1=max2;
            r=mid;
        } 
        else l=mid+1;
    }
    cout<<max1<<endl;
    return 0;
}
```

---

## 作者：xzyxzy (赞：0)

难得的一次过的题

这道题是典型的二分答案加贪心策略（求最大值（最大fajo月的预算）的最小值）：

先找到答案区间（在每个月的最大值和所有月的总和之间）

然后利用二分查找答案

精髓是check函数（详细过程注释已经讲明白了）

注意的是第一次查找到的解不一定是最优解，所以要定义ans来存储最优解

最后输出就好了



        
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
int n,m,a[100001];//n天,m组,a[i]表示第i天的钱 
int read()//读入优化 
{
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    int h=0;
    while(ch>='0'&&ch<='9') 
    {
        h=h*10+ch-48;
        ch=getchar();
    }
    return h;
} 
int check(int max1),q[100001];
int main()//求最大的最小值 
{
    n=read();
    m=read();
    int l=0,r=0,ans;
    for(int i=1;i<=n;i++) 
    {
        a[i]=read();
        q[i]=q[i-1]+a[i];//定义前缀和 
        l=l>a[i]?l:a[i];//答案左区间应为最大的一个月 
        r+=a[i];//答案右区间应为每个月经费之和 
    }
    while(l<=r)
    {
        int mid=(l+r)/2,k=check(mid);
        if(k==1)//如果满足条件了，就记录此时的解（此时的解一定比之前查找到的更优，因为如果查到了解，就会在数值更大的区间内寻解）
        {
            ans=mid;
            r=mid-1;//在数值更大的区间内寻解
        }
        else l=mid+1;//在数值更小的区间内寻解
    } 
    cout<<ans;
    return 0;
}
int check(int max1)//max1:一个fajo月(财政周期)的总经费的最大值 
{
    int s,f;
    int tot=1;//表示划分的财政周期数 
    for(s=1;s<=n;s=f)//枚举起始月
    {
        for(f=s+1;f<=n;f++)//枚举结束月
        {
            if(q[f]-q[s-1]<=max1) continue;//如果这个周期内总额没超过查找到的答案，就继续加上下一个月 
            else//超过了就再加一个fajo月(贪心策略) 
            {
                tot++;//新增一个fajo月 
                break;//再次枚举起始月 
            }
        } 
    } 
    if(tot<=m) return 1;//满足条件返回1
    else return 0; 
}
```

---

## 作者：PTC06 (赞：0)

裸的二分答案水题。

基本思路就是二分答案来找各组花费之和的最大值。

思路：

每次循环做如下步骤：

1.得出的mid作为可能的花费之和的最大值。

2.从1到n循环，累加花费，如果花费已经打过可能的最大值，说明要多分一组，来避免超过最大值。

3.判断如果当前的一个数就已经大于最大值了，那么就做标记。

4.最后判断组数是否大于m，如果大于则说明当前的mid太小，则low=mid+1，否则说明mid还可以小一些，则high=mid-1。

最后返回low，作为答案。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<fstream>
using namespace std;
int n,k,i,a[100005];
long long s,temp,needgroup;
bool flag;
int bSearch()
{
    int low=1;
    long long high=s;
    long long mid=0;;
    while (low<=high)
    {
        mid=(low+high)/2;
        temp=0;
        needgroup=1;
        flag=0;
        for (i=1;i<=n;i++)
        {
            if (temp+a[i]<=mid) temp+=a[i]; else
            {
                needgroup++;
                temp=a[i];
                if (temp>mid)
                {
                    flag=1;
                    break;
                }
            }
        }
        if (flag==1 || needgroup>k) low=mid+1; else high=mid-1;
    }
    return low;
}
int main()
{
    cin>>n>>k;
    for (i=1;i<=n;i++)
    {
        cin>>a[i];
        s+=a[i];
    }
    cout<<bSearch();
}
```

---

