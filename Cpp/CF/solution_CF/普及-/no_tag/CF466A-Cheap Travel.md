# Cheap Travel

## 题目描述

Ann has recently started commuting by subway. We know that a one ride subway ticket costs $ a $ rubles. Besides, Ann found out that she can buy a special ticket for $ m $ rides (she can buy it several times). It costs $ b $ rubles. Ann did the math; she will need to use subway $ n $ times. Help Ann, tell her what is the minimum sum of money she will have to spend to make $ n $ rides?

## 说明/提示

In the first sample one of the optimal solutions is: each time buy a one ride ticket. There are other optimal solutions. For example, buy three $ m $ ride tickets.

## 样例 #1

### 输入

```
6 2 1 2
```

### 输出

```
6
```

## 样例 #2

### 输入

```
5 2 2 3
```

### 输出

```
8
```

# 题解

## 作者：封禁用户 (赞：7)

hello大家吼啊，我这个蓝名小蒟蒻又双叒叕来写题解啦！这是本蒟提交的唯一一篇翻译，当然要写篇题解纪念一下啦！

首先我们的思路当然是考虑买哪种票便宜，第一种票的价格为：

```c
n/m*b+(n%m)*a
```

第二种票的价格就不用说了，a*n搞定。

但是！但是！但是！有可能第一种票比第二种票便宜很多，买完n div m张票后，再买一张第一种票可能比第二种票要便宜，所以！

```c
n/m*b+min((n%m)*a,b)
```

这才是第二种票真正的价格！

然后，用一个min语句求较便宜的一种方案，如下：

```c
min(n/m*b+min((n%m)*a,b),a*n)
```


献上既不整齐也不美观的小破程序：

```c
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<string>

using namespace std;
int n,b,m,a;
float s;
int main()
{
    cin>>n>>m>>a>>b;
    s=b/m;
    cout<<min(n/m*b+min((n%m)*a,b),a*n);

    return 0;
}
```

小破程序没什么好抄的，抄题勿提交，提交勿抄题！

---

## 作者：xgwpp6710 (赞：3)

首先我们分析一下题目。

这道题目的情况，无非就是买0次，1次，……，n/m次可以坐m次的车票。

所以for循环即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a,b,n,m,minn=100000009,x;
	cin>>n>>m>>a>>b;
	if(n%m) x=n/m+1;
   else x=n/m;
	for(int i=1;i<=x;i++) minn=min(minn,i*b+(n-(i*m))*a);//计算
	cout<<minn;
	return 0;
}
```
但是……真的是这样吗？通过分析，我们会发现，此时n-(i\*m)可能为负数，因此这样不行。

因此我把这个错误改了，代码如下。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a,b,n,m,minn=100000009,x;
	cin>>n>>m>>a>>b;
	x=n/m;
	for(int i=1;i<=x;i++) minn=min(minn,i*b+(n-(i*m))*a);
	minn=min(minn,(x+1)*b);
	cout<<minn;
	return 0;
}
```
等等……怎么还是WA？原来，m次的车票买0张也是可以的，这把我坑了一遍。

最终……这是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a,b,n,m,minn=100000009,x;
	cin>>n>>m>>a>>b;
	x=n/m;
	for(int i=0;i<=x;i++) minn=min(minn,i*b+(n-(i*m))*a);
	minn=min(minn,(x+1)*b);
	cout<<minn;
	return 0;
}
```

---

## 作者：LucasXu80 (赞：2)

这题题解区没人用PY？令我很震惊。。。

虽然我是C党，但我不得不承认PY的一大优点：代码量少。自带高精。这能让你快速A掉一些用C++可能要写很久的题。

先来看思路。我相信绝大部分人都可以想到两种情况：

第一种 这个公司是个奸商，单程票比$m$程票还要便宜。那么我们只要将单程票价格$a$乘以趟数$n$就可以了。

第二种 $m$程票比单程票便宜，那就尽可能多地买$m$程票，再买$n$%$m$张单程票。

但是，很多人（包括我）都忽略了一种很重要的情况——没有说是恰好买$n$趟地铁的票。也就是说，在最后还剩下$n$%$m$趟的时候，说不定再买一张$m$程票比买很多张单程票总钱数更少呢。

注意，以上的“便宜”不是指总价格低，而是指的是单价低。

好了，这里思路就理清了。上代码~

```python
n,m,a,b=map(int,input().split()) #一行内输入
if a<=b/m: print(n*a) #单程票便宜
else: #m程票便宜
    x=(n%m)*a+(n//m)*b #第一种情况，剩下的零头买单程票
    y=(n//m+1)*b #第二种情况，剩下的零头再买一张m程票
    if x<y: print(x)
    else: print(y)
    #输出两个数中更小的那一个
```
PY好呀。如果你也是这样认为的，给我点个赞吧~

---

## 作者：一只大龙猫 (赞：1)

[原题传送门](https://www.luogu.com.cn/problem/CF466A)

**题意：**

- 有两种地铁票，单程票一张价格为 $a$，$m$ 程票一张价格为 $b$。

- 给定 $n,m,a,b$，求搭乘 $n$ 次地铁的最低花费。

- 数据范围：$1\leqslant n,m,a,b \leqslant1000$。

看了一下大家的题解，发现没有人用动规。我就来写一下吧。

设 $f(i)$ 为搭 $i$ 次地铁的最少花费，则易推出转移方程：

- 若 $i \geqslant m$，则 $f(i)= \min (f(i-1)+a,f(i-m)+b)$。

- 否则 $f(i)= \min (f(i-1)+a,b)$。

为什么转移方程的第二条不是 $f(i)=f(i-1)+a$？考虑最极端的情况，$b=a+1$ 且 $3\leqslant n \leqslant m$，显然此时买一张 $m$ 程票要比买 $n$ 张单程票要便宜。

综上，便不难写出代码：

```cpp
#include<iostream>
using namespace std;
int f[2000],n,m,b,a;
int main(){
	cin>>n>>m>>a>>b;
	for(int i=1;i<=n;i++){
		if(i>=m)f[i]=min(f[i-1]+a,f[i-m]+b);
		else f[i]=min(f[i-1]+a,b);
	}
	cout<<f[n];
	return 0;
}
```

---

## 作者：Happy_Dream (赞：1)

其实这道题并没有我想像的那么难，我最初看题以为是一个动态规划的题，后来发现只需要简单的模拟即可，并不用什么太难的算法，于是我就放心，12行代码就过了。

言归正传

本题思路其实也很简单，只需要简单的判断一下是买a卢布一张，可以搭一次地铁的和b卢布一张，可以搭m次地铁这两种票那种票便宜即可（~~和我爸爸一样是财迷~~）连循环都不用写。
***
首先咱们来看那种票**单价**便宜，便宜很明显，第一种票单价就是a，而第二种票单价为b/m，所以只要判断哪个低就买那个。如果第一种便宜就直接输出a×n（买n张为a元的票总价就是a×n）而第二种就稍微复杂一点，第二种票价很显然是n/m×b，但还会剩n%m次车，所以还要加上b，但这不一定是对的，因为还有第一种票呢，如果第一种票的价钱×n%m小于b，那么第一种就便宜，所以去一个最小值即可就MIN（iostream里自带的）。

好了有了概念就来敲代码吧：
***
```cpp
#include <iostream>//头文件
using namespace std;//常规
int main()//主函数
{
	int n,m,a,b;//一行四个整数：n,m,a,b，代表的数请看题意
	cin>>n>>m>>a>>b;//输入
	if(float(b/m)>=a)//判断那种便宜
	cout<<a*n;//如果第一种便宜就输出a×n
	else//其他情况
	cout<<n/m*b+min(b,n%m*a);//第二种票价怎么计算前面说了，就是n/m*b+min(b,n%m*a)，输出就行了
	return 0;//华华丽丽的结束
}
```
***
请大家在看题解前自己思考，那样才能获得真正的知识！！！祝大家一帆风顺……

---

## 作者：AllanPan (赞：0)

先来分析这道题：

**简单来说就是有两种票的选择，可以混搭，但要选最合算的那个：**
- 单程票：只能搭一次；

- 多程票：能乘多次；

- 已知：你要坐n次地铁。  

看到这题，第一反应不就应该是选出单价最便宜的吗（这是坑哦）

然后我提交了错误答案……

**我们来看看为什么不能比单价：**
- 多程票买了算的是b次，少乘了费用不退；

- 答案算出来很可能不是整数，这就不符合题意了$QAQ$。

**接下来是分析的过程：* 

总体思路：看看全买单程，混买，还是全买多程核算。

先来算单程：$a\times n$（卢布）

然后看看在全部坐完的情况下双程的价格：$\lfloor \frac{n}{m} \rfloor \times b$（卢布）

当然别忘了附加的钱，有两种：
- 选单程：设$n \equiv x (mod n)$，那么单程为$x \times a$（卢布）

- 选多程：$b$（卢布）

**取一下最小值就可以啦！**

上代码：
```c
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n,m,a,b,fee1,fee2,psfee,tot;
    scanf("%d%d%d%d",&n,&m,&a,&b);
    fee1=a*n;//全单程
    fee2=n/m*b;//整个的双程
    psfee=min((n%m)*a,b);//附加费用
    tot=min(fee2+psfee,fee1);//算一下最小值
    printf("%d",tot);
    return 0;//ac
}
```


---

## 作者：小豆子范德萨 (赞：0)

带一点点贪心的模拟题，首先确定买票策略：
- 如果单程票的单价要比多程票平均到每次的票价要便宜，那么全部买单程票
- 反之若多程票的单价要便宜时，我们又有两种策略：
  - 要尽可能多地买多程票，剩下的几次混合着买单程票
  - 全部买多程票，多出来的次数作废（不考虑这个10 3 5 1的测试点会错误）。
 
综上述，代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,a,b; 

int main()
{
	cin>>n>>m>>a>>b;
	//首先计算多程票单价 
	double v2 = (double)b/m;
	int ans = 0;
	if(a <= v2) ans = n*a;
	else {
		int num = n/m;
		int remain = n % m;		//余下要买几张单程 
		int v1 = num*b + remain*a;		//混合买 
		int v2 = ceil((double)n/m)*b;				//不混合买，全买多程票,ceil向上取整 
		if(v1 < v2) ans = v1;
		else ans = v2;
	}
	cout<<ans;
	return 0;
}
```


---

