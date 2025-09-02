# Travel Card

## 题目描述

A new innovative ticketing systems for public transport is introduced in Bytesburg. Now there is a single travel card for all transport. To make a trip a passenger scan his card and then he is charged according to the fare.

The fare is constructed in the following manner. There are three types of tickets:

1. a ticket for one trip costs $ 20 $ byteland rubles,
2. a ticket for $ 90 $ minutes costs $ 50 $ byteland rubles,
3. a ticket for one day ( $ 1440 $ minutes) costs $ 120 $ byteland rubles.

Note that a ticket for $ x $ minutes activated at time $ t $ can be used for trips started in time range from $ t $ to $ t+x-1 $ , inclusive. Assume that all trips take exactly one minute.

To simplify the choice for the passenger, the system automatically chooses the optimal tickets. After each trip starts, the system analyses all the previous trips and the current trip and chooses a set of tickets for these trips with a minimum total cost. Let the minimum total cost of tickets to cover all trips from the first to the current is $ a $ , and the total sum charged before is $ b $ . Then the system charges the passenger the sum $ a-b $ .

You have to write a program that, for given trips made by a passenger, calculates the sum the passenger is charged after each trip.

## 说明/提示

In the first example, the system works as follows: for the first and second trips it is cheaper to pay for two one-trip tickets, so each time $ 20 $ rubles is charged, after the third trip the system understands that it would be cheaper to buy a ticket for $ 90 $ minutes. This ticket costs $ 50 $ rubles, and the passenger had already paid $ 40 $ rubles, so it is necessary to charge $ 10 $ rubles only.

## 样例 #1

### 输入

```
3
10
20
30
```

### 输出

```
20
20
10
```

## 样例 #2

### 输入

```
10
13
45
46
60
103
115
126
150
256
516
```

### 输出

```
20
20
10
0
20
0
0
20
20
10
```

# 题解

## 作者：ChenZQ (赞：3)

看到大佬们都用了动态规划和二分，那我来写一篇动态规划和双指针的题解。

看到题目，像这种看上去要枚举出所有情况才行但是又会超时的题一般都是动态规划。

首先来说一下状态的转移。

题目给了三种票价。

第一种：单程票。由于只考虑了当前的旅游次数所以状态转移方程是:$dp_i = dp_{i-1} + 20$。

第二种：在 90 分钟内可以随意坐车的票。因为我们是从前往后枚举，所以根本无法知道具体能坐多少趟车，我们可以在枚举 $i$ 位置的时候往前看能做多少趟车。我们可以用双指针算法维护这个区间，以便更新状态。设 $x$ 为如果当前要购买这种门票，可以往前做多少趟车的区间的左端点。那么状态转移方程为 $dp_i = dp_{x-1} +50$。

第三种：在 1440 分钟内可以随意坐车的票。思路同上。状态转移方程为 $dp_i = dp_{x-1} + 120$。

接下来说一下指针的更新。

设两个指针分别为维护第二种票的区间和第一种票的区间。

每次发现 $a_i - a_l$ 大于 90 或 1440 的时候就让指针往后移($a$ 为每次乘车的时间，$l$ 为区间左端点),直到他们的差值小于门票的有效期位置。

那么根据上述内容，在三种门票中取最优解，输出差值，就能完美通过这题了。

### AC CODE
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int f[N],a[N]; 


signed main(){
    int n;
    cin>>n;
    f[0]=0;
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+n+1);
    int l1=1,l2=1;
    for(int i=1;i<=n;i++)
    {
	while(abs(a[i]-a[l1])>=90) l1++;//注意头尾都要更新，不然状态转移后可能有影响。
        while(abs(a[i]-a[l2])>1439) l2++;
        f[i]=f[i-1]+20;
        int x=l1;
        f[i]=min(f[i],f[x-1]+50);
        int y=l2;
        f[i]=min(f[i],f[y-1]+120);
        while(abs(a[i]-a[l1])>=90) l1++;
        while(abs(a[i]-a[l2])>1439) l2++;//注意是在时间内才能，不是差值小于或等于就好，所以更新的时候要减一。
        
    }
    for(int i=1;i<=n;i++) cout<<f[i]-f[i-1]<<endl;
}
```

---

## 作者：封禁用户 (赞：2)

设 $f_i$ 表示对于 $1\sim i$ 的所有的车至少需要花费多少元钱。

初始条件：$f_0=0$。

转移：

+ 如果购买单程票，那么 $f_i=f_{i-1}+20$。
+ 选择方案 $2$：需要找到距离当前时间超过 $90$ 分钟的中，最近的那一辆车 $x$，那么 $f_i=f_x+90$。
+ 方案 $3$：同理，需要找到距离当前时间超过 $1440$ 分钟的中，最近的那一辆车 $x$，那么 $f_i=f_x+1440$。

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;int f[N],a[N];
signed main(){
    int n;
    cin>>n;
    f[0]=0;
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++){
        f[i]=f[i-1]+20;
        int x=lower_bound(a+1,a+i+1,a[i]-89)-a-1;
        f[i]=min(f[i],f[x]+50);
        int y=lower_bound(a+1,a+i+1,a[i]-1439)-a-1;
        f[i]=min(f[i],f[y]+120);
    }
    for(int i=1;i<=n;i++)
        cout<<f[i]-f[i-1]<<'\n';
}
```



---

## 作者：OIerZhang (赞：1)

# [CF756B Travel Card](https://www.luogu.com.cn/problem/CF756B) 题解

真服了这些犇犇非要用二分和 DP 来解决这道水题，~~简直是小题大做~~

## 题意

题目翻译不是特别透彻，所以感觉很晕，我们不妨来看一看样例 1 的提示：

> 在第一个例子中，系统工作原理如下：对于第一次和第二次旅行，支付两张单程票更便宜，所以每次收取 $20$ 元，在第三次旅行后，系统发现买 $90$ 分钟票会更便宜。这张票的价格是 $50$ 元，乘客已经支付了 $40$ 元，所以仅要收费 $10$ 元。

意思是系统买票是会“反悔”的！以样例一来说，本来前两次买的是单程票，但第三次时，系统将前两次的单程票换成了 $90$ 分钟票，只用付 $10$ 元，但在这张票的有效时间中，还是一共付了 $50$ 元。

我们再梳理一下样例 2 的数据：

|时间|单程票|$90$ 分钟票|全天票|备注|
|:-:|:-:|:-:|:-:|:-|
|$13$|$\color{orangered}{20}$|$50$|$120$|单程票最优|
|$45$|$\color{orangered}{20}$|$30$|$100$|可以付 $30$ 元换 $13 \to 102$ 分钟的 $90$ 分钟票，但单程票最优|
|$46$|$20$|$\color{orangered}{10}$|$80$|可以只付 $10$ 元换 $13 \to 102$ 分钟的 $90$ 分钟票|
|$60$|$ $|$\color{orangered}{0}$|$ $|$90$ 分钟票仍有效|
|$103$|$\color{orangered}{20}$|$20$|$70$|$90$ 分钟票过期，单程票最优|
|$115$|$20$|$\color{orangered}{0}$|$50$|可以免费换 $45 \to 134$ 分钟的 $90$ 分钟票|
|$126$|$ $|$\color{orangered}{0}$|$ $|$90$ 分钟票仍有效|
|$150$|$\color{orangered}{20}$|$30$|$50$|$90$ 分钟票过期，单程票最优|
|$256$|$\color{orangered}{20}$|$50$|$30$|如果在 $150$ 分钟买 $90$ 分钟票，只能在 $150 \to 239$ 分钟使用，所以买它要全价，单程票最优|
|$516$|$20$|$50$|$\color{orangered}{10}$|可以只付 $10$ 元换 $13 \to 1452$ 分钟的全天票|

相信现在大家应该有想法了，那就进入下面的正题环节。

## 思路

### $O(n^2)$ 暴力做法

我们可以模拟一下刚刚梳理样例的过程。

1. 第一次旅行均为全价。

|时间|单程票|$90$ 分钟票|全天票|
|:-:|:-:|:-:|:-:|
|$13$|$\color{orangered}{20}$|$50$|$120$|

2. 第二次旅行前 $90$ 分钟和 $1440$ 分钟付了 $20$ 元，所以可以少付 $20$ 元。

|时间|单程票|$90$ 分钟票|全天票|
|:-:|:-:|:-:|:-:|
|$13$|$\color{orangered}{20}$|$50$|$120$|
|$45$|$\color{orangered}{20}$|$50-20=30$|$120-20=100$|

3. 同上。

|时间|单程票|$90$ 分钟票|全天票|
|:-:|:-:|:-:|:-:|
|$45$|$\color{orangered}{20}$|$30$|$100$|
|$46$|$20$|$30-20=\color{orangered}{10}$|$100-20=80$|

4. $90$ 分钟票仍有效。

|时间|单程票|$90$ 分钟票|全天票|
|:-:|:-:|:-:|:-:|
|$46$|$20$|$\color{orangered}{10}$|$80$|
|$60$|$ $|$\color{orangered}{0}$|$ $|

5. $90$ 分钟票过期，前 $90$ 分钟付了 $30$ 元，前 $1440$ 分钟付了 $50$ 元。

|时间|单程票|$90$ 分钟票|全天票|
|:-:|:-:|:-:|:-:|
|$60$|$ $|$\color{orangered}{0}$|$ $|
|$103$|$\color{orangered}{20}$|$50-30=20$|$80-10=70$|

6. 前 $90$ 分钟付了 $50$ 元，前 $1440$ 分钟付了 $70$ 元。

|时间|单程票|$90$ 分钟票|全天票|
|:-:|:-:|:-:|:-:|
|$103$|$\color{orangered}{20}$|$20$|$70$|
|$115$|$20$|$20-20=\color{orangered}{0}$|$70-20=50$|

7. $90$ 分钟票仍有效。

|时间|单程票|$90$ 分钟票|全天票|
|:-:|:-:|:-:|:-:|
|$115$|$20$|$\color{orangered}{0}$|$50$|
|$126$|$ $|$\color{orangered}{0}$|$ $|

8. 同 _5._ 思路。

|时间|单程票|$90$ 分钟票|全天票|
|:-:|:-:|:-:|:-:|
|$126$|$ $|$\color{orangered}{0}$|$ $|
|$150$|$\color{orangered}{20}$|$30$|$50$|
|$256$|$\color{orangered}{20}$|$50$|$30$|

9. 前 $1440$ 分钟付了 $110$ 元，所以全天票最优。

|时间|单程票|$90$ 分钟票|全天票|
|:-:|:-:|:-:|:-:|
|$516$|$20$|$50$|$\color{orangered}{10}$|

整个样例 2 就模拟完了，我们可以总结出以下几点：

1. 循环枚举每一次旅行。
2. 循环计算前 $90$ 和 $1440$ 分钟花了多少钱。
3. 通过 _2._ 的结果计算单程票、$90$ 分钟票和全天票的花费。
4. 找最小值并输出。

没错，就是这样简单。可是数据范围达到了 $10^5$，我们的方法的时间复杂度却达到了 $O(n^2)$，无法通过此题。这就需要介绍一下 $O(n)$ 做法了。

### $O(n)$ 正解做法

在讲解之前，我们先引入这道题：

> P2058 [NOIP2016 普及组] 海港

这道题的 AC 做法中，运用了滑动窗口。我们也可以用这种思想来 AC 这道题。

在原来的思路中，我们花了一重循环来计算已经花的钱，大大降低了程序效率。我们可以每一次都把距离这次旅行超过 $90$ 和 $1440$ 分钟的旅行移出“窗口”，顺便统计前 $90$ 和 $1440$ 分钟花了多少钱。由于每一个数据都只会进入窗口 $1$ 次，所以这种做法的时间复杂度为 $O(n)$。

这样，$O(n^2)$ 的做法就被我们优化成 $O(n)$ 了！

## 代码

珍爱账号，远离抄袭。

```cpp
#include <iostream>
#include <queue>
using namespace std;

struct node
{
	int t,price;
};

int p1=0,p2=0; // p1: Sum(q1.price), p2: Sum(q2.price)

queue <node> q1; // 90 minutes' card
queue <node> q2; // 1440 minutes' card

int main()
{
	int n,t;
	cin>>n;
	while (n--)
	{
		cin>>t;
		while (!q1.empty()&&t-q1.front().t>=90)
			p1-=q1.front().price,q1.pop();
		while (!q2.empty()&&t-q2.front().t>=1440)
			p2-=q2.front().price,q2.pop();
		int card1=20; // 1 minute's card
		int card2=max(0,50-p1); // 90 minutes' card
		int card3=max(0,120-p2); // 1440 minutes' card
		cout<<min(min(card1,card2),card3)<<endl;
		q1.push({t,min(min(card1,card2),card3)});
		q2.push({t,min(min(card1,card2),card3)});
		p1+=min(min(card1,card2),card3);
		p2+=min(min(card1,card2),card3);
	}
	return 0;
}
```

---

## 作者：ricky_lin (赞：1)

有没有可能这道题可以更加地暴力一点。

---

我们设 $f_i$ 为坐前 $i$ 次车的最少花费。

然后对于每个已经算好的 $f_i$ 进行更新，方法如下：

$$
\begin{cases}f_j \to \min(f_j,f_i+20)&j = i-1\\f_j \to \min(f_j,f_{i-1}+50)&t_j \leq t_i+89\\f_j \to \min(f_j,f_{i-1}+120)&t_j\leq t_i+1439\end{cases}
$$

时间复杂度：$O(1439n)$ ~~你考虑 $10^8$ 跑过不是很正常。~~

AC 记录（可点击查看）：

[![](https://cdn.luogu.com.cn/upload/image_hosting/ircx2k1l.png)](https://www.luogu.com.cn/record/113415692)

---

常见疑问：

- 为什么是 $f_{i-1}$ 而不是 $f_i$？

因为 $f_i$ 包含了第 $i$ 次车的车票，而第二、三种车票都是包含了 $t_i$ 这个时刻的。

如果 $f_i$ 转移时使用了第一种单程票，那么用 $f_i$ 转移就有问题，而用 $f_{i-1}$ 转移就一点问题都没有。

读者若不懂可以停下来细品。
 
- 为什么是 $+89$ 和 $+1439$？

原题中有下面英文：
> Note that a ticket for $ x $ minutes activated at time $ t $ can be used for trips started in time range from $ t $ to $ t+x-1 $ , inclusive. Assume that all trips take exactly one minute.

意思是：一张从 $t$ 时刻开始的时长为 $x$ 的票，在 $x\sim t-x+1$ 时刻有效。

所以说，第二种票的范围是 $t_i\sim t_i+89$， 第三种票同理。

---

**code：**
```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN = 2e5 + 8; 
int n;
int a[NN];
int cost[NN];
int main(){
	memset(cost,0x3f,sizeof(cost));
	scanf("%d",&n);
	cost[0] = 0;
	for(int i = 1; i <= n; ++i) scanf("%d",&a[i]);
	for(int i = 1; i <= n; ++i){
		cost[i] = min(cost[i-1] + 20,cost[i]);
		for(int j = i; a[j] <= a[i] + 89 && j <= n; ++j) cost[j] = min(cost[j],cost[i-1] + 50);
		for(int j = i; a[j] <= a[i] + 1439 && j <= n; ++j) cost[j] = min(cost[j],cost[i-1] + 120);
	}
	for(int i = 1; i <= n; ++i) printf("%d\n",cost[i]-cost[i-1]);
}
```

---

最后，再给出一种其他大部分题解做法的优化:

随着 $i$ 增加，每个方案的转移点右移，

那么可以用类似于双指针的做法做到 $O(n)$ 的复杂度。

**code：**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN = 2e5 + 8; 
int n;
int a[NN];
int cost[NN];
int main(){
	scanf("%d",&n);
	for(int i = 1; i <= n; ++i) scanf("%d",&a[i]);
	int p1 = 0,p2 = 0;
	for(int i = 1; i <= n; ++i){
		cost[i] = cost[i-1] + 20;
		while(a[p1] < a[i] - 89) ++p1;//第2种票转移点
		while(a[p2] < a[i] - 1439) ++p2;//第3种票转移点
		cost[i] = min(min(cost[i],cost[p1-1] + 50),cost[p2-1] + 120);
	}
	for(int i = 1; i <= n; ++i) printf("%d\n",cost[i]-cost[i-1]);
}
```

AC 记录（可点击查看）：

[![](https://cdn.luogu.com.cn/upload/image_hosting/7mmgvbt4.png)](https://www.luogu.com.cn/record/113424362)

---

感谢观看！

---

## 作者：ATION001 (赞：0)

## 题目描述
你想乘坐 $n$ 次汽车，你列出了一个乘车清单，上面列举了你每一次乘坐汽车是什么时候。由于你想以最少的代价完成乘车，你需要购买花钱最少的车票，车票钱数规定如下：

- 以 $20$ 元的代价乘坐一次车。
  
- 以 $50$ 元的代价在 $90$ 分钟内乘坐任意次车。

- 以 $120$ 元的代价在 $1440$ 分钟内乘坐任意次车。

注意：上面的有效时间范围是**严格小于**哦。

对于每一个 $i$，你都需要计算完成前 $i$ 次乘车需要多少钱，输出为成第 $i$ 次乘车需要的金额与完成第 $i-1$ 次乘车需要的金额差值。
## 思路
这题主要是运用动态规划，二分作为辅助工具。

首先我们考虑乘坐单程票的情况：$dp_i=dp_{i-1}+20$。直接买张单程票，也就是上一次乘车花费的钱 $+20$。

然后再考虑花费 $50$ 元的情况，可以用二分查找最小时间小于等于 $90$ 分钟的情况，这里用不着手写二分，可以使用用 `lower_bound` 函数，不知道这个函数用法的童鞋[点这里](https://blog.csdn.net/qq_63586399/article/details/136726979)，查找第一个值大于等于 $89$ 的元素 $a$，最后下标 $-1$ 就出来了。将二分出来的下标记作 $x$，$dp_i$ 的值为 $\min(dp_i,dp_x)$。

最后考虑花费 $120$ 元的情况，思路和花费 $50$ 元的类似，先二分查找第一个值大于等于 $1439$ 的元素 $a$，下标 $-1$，记作 $t$，那么 $dp_i$ 的值为 $\min(dp_i,dp_f)$。

输出的结果为 $dp_i-dp_{i-1}$，也就是输出每两个相邻时间段的差，然后就是代码啦。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,a[N],dp[N];
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		dp[i]=dp[i-1]+20;
		int x=lower_bound(a+1,a+n+1,a[i]-89)-a-1;
		dp[i]=min(dp[i],dp[x]+50);
		x=lower_bound(a+1,a+n+1,a[i]-1439)-a-1;
		dp[i]=min(dp[i],dp[x]+120);
	}
	for(int i=1;i<=n;i++){
		cout<<dp[i]-dp[i-1]<<'\n';
	}
	return 0;
}
```

---

## 作者：cqbzrjx (赞：0)

[原题链接](https://codeforces.com/problemset/problem/756/B)

# 浅谈做题做程

刚开始一看还以为是一道数学题，于是便开始~~睿智~~地打了试着调了一下。不出意外，写挂了。但是仔细看了之后，通过题意，可以发现此题其实是一道dp题

# 分析

通过推理，我们可以得知以下购买最为划算的三点。

ps:我用变量```m```来指时间。

- 当 $m \ge 1440$ 时，选择花 $120$ 元来购买 $1440min$ 的票最为划算。
- 当 $m \le 90$ 时，选择花 $50$ 元来购买 $90min$ 的票最为划算。
- 最后都不行的话，购买 $20$ 元的单程票。


# 做法

首先初始化 $dp[0] = 0$

然后就有三种转移方式

- 购买单程票时，$dp[i] = dp[i - 1] + 20$
- 购买 $90min$ 的票时，$dp[i] = dp[x - 1] + 50$，$x$ 为 $90min$ 以内最早的上个车次。
- 购买 $1440min$ 的票时，$dp[i] = dp[y - 1] + 120$，$y$ 为 $1440min$ 以内最早的上个车次。

最后再求出第 $i$ 次与第 $i - 1$ 次的花费最小值。

在求 $x$ 和 $y$ 的值时，我们可以使用```lower_bound```函数，进行查找第一个大于等于 $a[i] - 90 + 1$ 或 $a[i] - 1440 + 1$ 的数字的下标。

# AC code
```cpp
/*
CF756B Travel Card 
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10; 
int n;
int a[maxn],dp[maxn];
int main()
{
	cin>>n;
	for(int i = 1;i <= n;i++)
	{
		cin>>a[i];
	}
	dp[0] = 0;//初始化
	for(int i = 1;i <= n;i++)
	{
		int x = lower_bound(a + 1,a + i + 1,a[i] - 90 + 1) - a;//查找第一种
		int y = lower_bound(a + 1,a + i + 1,a[i] - 1440 + 1) - a;//查找第二种
		int aa = dp[x - 1] + 50;//第一种求值
		int bb = dp[y - 1] + 120;//第二种求值
		int z = dp[i - 1] + 20;//查找并求值第三种
		dp[i] = min(z,min(aa,bb));//求三种的最小值
		
	}		
	for(int i = 1;i <= n;i++)
	{
		cout<<dp[i] - dp[i - 1]<<endl;//计算输出
	}
 	return 0;
}
```

---

## 作者：__JiCanDuck__ (赞：0)

小**dp**，新手可以用来练手。
 
# 定义状态

 - 一维数组可以满足要求 $dp[i]$ 表示正在考虑已经买到第 $i$ 少要花多少钱。
 
# 状态转移

 - 要如何转移？
 1. 考虑第一种，买单程票，简单 $dp[i]=dp[i-1]+20$ 。
 1. 买 $90$ 分钟无限坐 那么，也很简单 $dp[i]=dp[u-1]+50$，其中 $u$ 是 $90$ 分钟以内的最早的车次。
 1. 买 $1440$ 分钟无限坐 那么，也很简单 $dp[i]=dp[w-1]+120$，其中 $w$ 是 $1440$ 分钟以内的最早的车次。
 
 ok！取 $\min$ 即可。
 
 问题来了，$u$ 和 $w$ 怎么求呢？ ~~总不能一个一个搜吧~~ 用二分。
 
# 边界
 
 无。
 
# AC code
 
 码风丑陋，勿喷。
 
 ```cpp
 
 #include<bits/stdc++.h>
using namespace std;
const int kMaxn=1e5+5;
int n,a[kMaxn];
int dp[kMaxn];
int main()
{
  cin>>n;
  for(int i=1;i<=n;i++){
    cin>>a[i];
    int u=lower_bound(a+1,a+i+1,a[i]-90+1)-a; //第一种
    int w=lower_bound(a+1,a+i+1,a[i]-1440+1)-a; //第二种
    dp[i]=min(dp[i-1]+20,min(dp[u-1]+50,dp[w-1]+120)); //第三种
    cout<<dp[i]-dp[i-1]<<'\n'; //算这次花的，不是总花的
 }

  return 0;
}
 ```

---

## 作者：Sol1 (赞：0)

这题显然是DP。

我们可以知道：当$90$分钟内有$\geq 3$个旅程的话则可以采用$50$元的票，当$1440$分钟内有$\geq 7$个旅程的话则可以采用$120$元的票。于是我们有DP方程：

$$dp_i=\min\{dp_{i-1}+20,dp_{pos1_i}+50,dp_{pos2_i}+120\}$$

关键问题：如何快速找到$pos1_i$和$pos2_i$。

显然我们知道$T_{i}-T_{pos1_i}<90,T_{i}-T_{pos2_i}<1440$。

于是方法明显：二分，可以采用$lower\_bound$。

注意是$<$，不是$ \leq $！！！注意读题！！！~~否则你将被样例2气死~~

注意最后还要差分一下哦~

上代码！

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
int T[100005], dp[100005], ans[100005];
int main()
{
	int N;
	scanf("%d", &N);
	for (int i = 1;i <= N;i++)
		scanf("%d", &T[i]);
	T[0] = 0xcfcfcfcf;//0xcfcfcfcf==-INF，保证T[0]不在任何旅程的90或1440分钟的范围内。
	for (int i = 1;i <= N;i++)
	{
		int pos1 = lower_bound(T, T + N + 1, T[i] - 89) - T;//二分取值
		int pos2 = lower_bound(T, T + N + 1, T[i] - 1439) - T;//这就是<和<=的问题：89和1439
		//printf("%d %d\n", pos1, pos2);
		dp[i] = dp[i - 1] + 20;
     	//pos的玄学用法……
		if (i - pos1 >= 2)
			dp[i] = min(dp[i], dp[pos1 - 1] + 50); 
		if (i - pos2 >= 5)
			dp[i] = min(dp[i], dp[pos2 - 1] + 120);
	}
   //差分得答案
	ans[1] = dp[1];
	for (int i = 2;i <= N;i++)
		ans[i] = dp[i] - dp[i - 1];
	for (int i = 1;i <= N;i++)
		printf("%d\n", ans[i]);
	return 0;
}
```

求hack~成功了有~~神秘奖励~~哦！

---

