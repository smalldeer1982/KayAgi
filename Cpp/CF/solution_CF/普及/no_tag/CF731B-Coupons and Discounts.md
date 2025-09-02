# Coupons and Discounts

## 题目描述

The programming competition season has already started and it's time to train for ICPC. Sereja coaches his teams for a number of year and he knows that to get ready for the training session it's not enough to prepare only problems and editorial. As the training sessions lasts for several hours, teams become hungry. Thus, Sereja orders a number of pizzas so they can eat right after the end of the competition.

Teams plan to train for $ n $ times during $ n $ consecutive days. During the training session Sereja orders exactly one pizza for each team that is present this day. He already knows that there will be $ a_{i} $ teams on the $ i $ -th day.

There are two types of discounts in Sereja's favourite pizzeria. The first discount works if one buys two pizzas at one day, while the second is a coupon that allows to buy one pizza during two consecutive days (two pizzas in total).

As Sereja orders really a lot of pizza at this place, he is the golden client and can use the unlimited number of discounts and coupons of any type at any days.

Sereja wants to order exactly $ a_{i} $ pizzas on the $ i $ -th day while using only discounts and coupons. Note, that he will never buy more pizzas than he need for this particular day. Help him determine, whether he can buy the proper amount of pizzas each day if he is allowed to use only coupons and discounts. Note, that it's also prohibited to have any active coupons after the end of the day $ n $ .

## 说明/提示

In the first sample, Sereja can use one coupon to buy one pizza on the first and the second days, one coupon to buy pizza on the second and the third days and one discount to buy pizzas on the fourth days. This is the only way to order pizzas for this sample.

In the second sample, Sereja can't use neither the coupon nor the discount without ordering an extra pizza. Note, that it's possible that there will be no teams attending the training sessions on some days.

## 样例 #1

### 输入

```
4
1 2 1 2
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
3
1 0 1
```

### 输出

```
NO
```

# 题解

## 作者：chenyanbo123 (赞：2)

这道题我用的是逆推的思想，从最后一天往回推，不难考虑到：

（1）：当前天数所需购买的比萨数量若为奇数，显然只能由前一天购买第二种方案（即在连续的两天各购买一个披萨）而得，所以前一天的比萨数量减1；

（2）：当前天数所需购买的比萨数量若为偶数，则可以通过多次使用购买方案一，次数为（购买当天比萨数/2）次，来完成购买；

（3）：若在逆推过程中出现负数，则必然会形成浪费，输出‘NO’；

（4）：推到第一天时没有前一天，若循环到第一天的比萨数为奇数，则必然会形成浪费，输出‘NO’，若为偶数，则可按照叙述（2）的方法完成购买，输出‘YES’。

AC代码如下：
```cpp
#include<bits/stdc++.h>//万能头文件 
using namespace std;
int n; 
int a[200005];//表示每一天的比萨数量 
int main()
{
	cin>>n; 
	for(int i=1;i<=n;i++)cin>>a[i];//寻常的读入 
	for(int i=n;i>=2;i--)//循环由 n~2，a[1]判奇偶 
	{
		if(a[i]<0) //比萨数为负数时特判 
		{
			cout<<"NO";//!!不能用puts 
			return 0;
		}
		if(a[i]%2==1)a[i-1]--;//比萨数为奇数时使用第二种购买方案 
	}
	if(a[1]%2==1)cout<<"NO";//第一天比萨数为奇数时会形成浪费 
	else cout<<"YES";//为偶数时则能成功购买 
	return 0; 
}
```



---

## 作者：fuxiao (赞：1)

这道题目翻译说的比较清楚，就是他有两种购买披萨的方式，一种是两天一天买一个，一个是一天买两个。

有没有发现什么不对劲，他一买就是两个披萨欸。那么买的披萨的和就只能是偶数了，但是我们不能直接全部加起来判断，而是以 $0$ 为节点判断。我们就拿样例 $2$ 来看，第一天他买了一个披萨，而第二天却一个披萨也没买，这很显然两种组合方式都是不符合的，节点内的和是 $1$ 也是不对的，判断到这里我们就可以直接输出 ``NO`` 了，后面都不用管。如果数列里根本没有 $0$ 记得再加个特判。

最后写给出我调了一个半小时的代码：
```cpp
#include<iostream>
#include<string>
#include<cmath>
#include<math.h>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
#include<queue>
#include<stack>
#include<set>
#include<map>
#include<cstdlib>
#include<time.h>
#include<iomanip>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
int a;
int main(){
	int n,x=0;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a;
		if(a==0){//边输出边判断节点
			if(x%2==1){//如果是奇数直接输出
				cout<<"NO";
				return 0; 
			}
			x=0;//记得清零
		}
		x+=a;//加节点内的总和
	}
	if(x%2==1)cout<<"NO";//最后的特判
	else cout<<"YES";
	return 0;
}
```

---

## 作者：_Aoi_ (赞：1)

### 题意分析
有两种购买披萨的方式

1. 在同一天买一送一
1. 第一天买一个第二天送一个

不难发现都是一次性购买**两个**披萨，为了避免浪费，就需要判断每天需要的披萨数量的奇偶性。

### 奇偶性判断
- 如果这天需要的披萨数减去前一天用第 $2$ 种方式送的披萨数剩余为**偶数**（不为 $0$），那么就一次性用第 $1$ 种方式购买完

- 如果这天需要的披萨数减去前一天用第 $2$ 种方式送的披萨数剩余为**奇数**，则用第 $1$ 种方式购买能购买的披萨数，再将剩下的用第 $2$ 种方式购买

- 如果这天需要的披萨数为 $0$ 但前一天用第 $2$ 种方式送的披萨数不为 $0$，则不能满足，输出 NO

- 如果是第 N 天但前一天用第 $2$ 种方式送的披萨数不为 $0$，则不能满足，输出 NO

### 注意
在判断不满足输出后不是 break


------------

### code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200010],pizza;//pizza是前一天用第2种方式送的披萨数 
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
	{
		if(a[i]==0&&pizza==1)//需要0个披萨但送了一个,不满足 
		{
			cout<<"NO";
			return 0;
		}
		if(i==n&&(a[i]-pizza)%2==1)//最后一天但需要的披萨数为奇数,不满足 
		{
			cout<<"NO";
			return 0;
		}
		pizza=(a[i]-pizza)%2;//更新送的披萨数 
	}
	cout<<"YES";
	return 0;
}
```



求过qwq


---

## 作者：LLGZ (赞：1)

题面给的已经很清楚了

我再分析一波：

题意具体的想法是判断给的数据是否会形成浪费？

比如说第一天需要1个披萨，第二天需要0个披萨

>在第一天，如果选择第一种方法——买两个，第一天你吃不完，而第二天又不需要披萨，那么就会浪费；

>如果选择第二种方法——连续两天买一个，就更会浪费

所以无论第一种第二种，都会浪费

但这时会发现，如果0之前的披萨数量之和为奇数，无论用第一种还是第二种方法，都会形成浪费

**所以我们只要将0看作一个分割符—>0和0区间内的数字之和为偶数，就不会形成浪费；反之，就会形成浪费**

当然如果这组数据中没有0就要进行一次特判

**具体看代码**

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,a;
int flag,ans;
int main()
{
	cin>>n;//天数，也就是数据的个数
	
	for(int i=1;i<=n;i++)
	{
		cin>>a;//边输入边操作
		
		if(a==0)//如果发现分隔符0，就判断ans的奇偶
		{
			if(ans%2==1)//之前累加的数如果为奇数
			flag=1;//标记一下会形成浪费
			ans=0;//累加的清零
		}
		ans+=a;//继续累加（因为如果a==0,ans+0不会有影响，所以不再判断）
	}

	if(ans%2==1)//只是一个特判，判断数据中没有0的情况
	flag=1;
	
	if(flag==1)//最后还是普通的输出
	cout<<"NO";
	else cout<<"YES";

   return 0;
}
```


---

## 作者：DengDuck (赞：0)

在简单理解了题意之后，我们发现这是一道 **有关奇偶数** 的问题！

先标一下号：

- 套餐 $A$ 在同一天购买正好两个披萨

- 套餐 $B$ 在连续的两天各购买一个披萨

首先，最后一天只能购买套餐 $A$ ，因为只能 $n$ 天内购买， **结束后不可购买** 。

一个问题 —— 如果最后一天买的是奇数个怎么办？

显然倒数第二天应该购买套餐 $B$ ，让最后一天满足要求。

那此时我们在讨论倒数第二天，以此类推。

到了第一天，我们看看第一天是否有办法满足即可

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005];
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    for(int i=n;i>=2;i--)
    {
        if(a[i]<0)
        {
            cout<<"NO";
            return 0;
        }
        if(a[i]%2)
        {
            a[i-1]--;//前一项
        }
    }
    if(a[1]%2)cout<<"NO";
    else cout<<"YES";
    return 0;
}
```


---

## 作者：lsr1409111459 (赞：0)

### 2.CF731B Coupons and Discounts

#### 2.1 题目描述（[传送门](https://www.luogu.com.cn/problem/CF731B)）

##### 2.1.1 题目大意

你服务学校的 ICPC 队，准备给他们买 $n$ 天的披萨，第 $i$ 天买 $a_i$ 个披萨。

可惜学校没有经费，只给了你无数张优惠券。优惠券分为两种：

- 券 $a$ ：同一天买两个披萨。
- 券 $b$ ：连续两天各买一个披萨。

你有无数张优惠券，每一种每天都可以使用若干个。请问，你是否可以达成买披萨的计划。（注意，第 $n$ 天结束时，不可以有券 $b$ 的效应残留，即第 $n$ 天不允许使用券 $b$ ）。

##### 2.1.2 输入格式

第一行一个整数 $n\ (\ 1<=n<=200000)$ ，表示买披萨的天数。

第二行为 $n$ 个整数 $a_1,a_2,...,a_n\ (\ 0\leq a_i \leq 10000)$ ，表示这 $n$ 天买披萨的计划。

##### 2.1.3 输出格式

一行。如果可以达成计划，输出 ``YES``  ；否则，输出 ``NO`` 。

##### 2.1.4 样例

###### 输入 #1

```cpp
4
1 2 1 2
```

###### 输出 #1

```cpp
YES
```

###### 输入 #2

```cpp
3
1 0 1
```

###### 输出 #2

```cpp
NO
```

##### 2.1.5 样例解释

对于样例 #1 ，第一天使用一张券 $b$ ，第二天使用一张券 $b$ ，第三天什么都不用（因为前一天用过券 $b$ ），第四天使用一张券 $a$ 。

#### 2.2 解题思路

券 $a$ 一天买两个，券 $b$ 一天买一个，那就考虑每天的需求是奇数还是偶数即可。

我们称前一天用券 $b$ ，则当天会受到券 $b$ 的残留效应，即当天需要先减一。

如果当天需求为奇数，则：

- 若前一天用过券 $b$ ，当天变为偶数，全部用券 $a$ 即可。
- 否则，当天用一张券 $b$ ，剩下的用券 $a$ 即可。

如果当天需求为偶数，则：

- 若前一天用过券 $b$ ，当天变为奇数。再用一张券 $b$ ，剩下的用券 $a$ 即可。
- 否则，全部用券 $a$ 即可。

判断最后一天结束后，是否还有券 $b$ 的残留效应即可。

注意特判，如果某天需求为 $0$ ，但前一天有券 $b$ 的残留效应，也不可以。

#### 2.3 解题代码

```cpp
#include <iostream>
using namespace std;
int n,x;
bool flag=false,ans=true;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&x);
        if(x%2)flag=!flag;
        if(x==0&&flag)ans=false;
    }
    if(!ans||flag)printf("NO\n");
    else printf("YES\n");
    return 0;
}
```

#### 2.4 解题心得

英语，一生之敌。这道题被困在了冗长的题面里。题目难度不高，可以说是贪心，但更多其实是模拟？要注意的是特判，幸亏有样例 #2 ，否则必 WA 一次并调试十分钟以上。

---

## 作者：Query_Failed (赞：0)

这道题的难度其实并不是很大，由于购买方式**只有两种：**

方式一：在**同一天**购买**正好两个**披萨，

方式二：在**连续的两天各购买一个**披萨，

因此大体思路上只需要进行**奇偶性的判断**并做处理就可以了。
## 思路：
**注意：我们是按照从第一天开始一天一天处理的，所以有可能处理到第i天时，并不是题目中所给的数据，而是处理过后的。**
首先我们需要处理掉需要奇数个披萨的时候（因为如果是偶数个就可以直接采用方式一购买完），我们需要选择方式二，在当天与当天的后一天各购买一个披萨。

代码：
```cpp
if(abs(a[i]%2)==1)
{
	a[i]--;
	a[i+1]--;
}
```
不过需要注意，有可能在减小的过程中会出现负数的情况，这就会直接影响模运算的结果（使之变为负数），因此我们需要对取模的数加上**绝对值**，~~本蒟蒻就在这里错了~~ 。

当然，如果减小之后出现负数，即出现了样例二中无法分配的情况，显然是不满足题意的，就可以直接输出并终止程序了。

代码如下：
```cpp
if(a[i]<0)
{
	cout<<"NO";
	return 0;
}
```




------------

以上循环的内容结束之后，之前**所有项都会变为偶数**（即都可用方式一购买完），因此我们只需要判断一下**最后一项的奇偶性**即可。

如果最后一项是偶数则满足题意，如果是奇数则不满足题意，因为这已经是最后一天了，无法采用方式一也无法采用方式二购买完所有披萨。

## 最后附上完整代码：
```cpp
#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	int n;
	cin>>n;
	int a[n];
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
	}
	for(int i=0;i<n-1;i++)
	{
		if(abs(a[i]%2)==1)
		{
			a[i]--;
			a[i+1]--;
		}
		if(a[i]<0)
		{
			cout<<"NO";
			return 0;
		}
	}
	if(abs(a[n-1]%2)==1) cout<<"NO";
	else cout<<"YES";
	return 0;
}

```


---

