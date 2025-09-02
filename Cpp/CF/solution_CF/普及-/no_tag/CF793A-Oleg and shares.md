# Oleg and shares

## 题目描述

Oleg the bank client checks share prices every day. There are $ n $ share prices he is interested in. Today he observed that each second exactly one of these prices decreases by $ k $ rubles (note that each second exactly one price changes, but at different seconds different prices can change). Prices can become negative. Oleg found this process interesting, and he asked Igor the financial analyst, what is the minimum time needed for all $ n $ prices to become equal, or it is impossible at all? Igor is busy right now, so he asked you to help Oleg. Can you answer this question?

## 说明/提示

Consider the first example.

Suppose the third price decreases in the first second and become equal $ 12 $ rubles, then the first price decreases and becomes equal $ 9 $ rubles, and in the third second the third price decreases again and becomes equal $ 9 $ rubles. In this case all prices become equal $ 9 $ rubles in $ 3 $ seconds.

There could be other possibilities, but this minimizes the time needed for all prices to become equal. Thus the answer is $ 3 $ .

In the second example we can notice that parity of first and second price is different and never changes within described process. Thus prices never can become equal.

In the third example following scenario can take place: firstly, the second price drops, then the third price, and then fourth price. It happens $ 999999999 $ times, and, since in one second only one price can drop, the whole process takes $ 999999999*3=2999999997 $ seconds. We can note that this is the minimum possible time.

## 样例 #1

### 输入

```
3 3
12 9 15
```

### 输出

```
3```

## 样例 #2

### 输入

```
2 2
10 9
```

### 输出

```
-1```

## 样例 #3

### 输入

```
4 1
1 1000000000 1000000000 1000000000
```

### 输出

```
2999999997```

# 题解

## 作者：LordLaffey (赞：4)


## 这算是一道水题了    
###### ~~橙题能不水吗~~
首先这道题的意思其实就是求股票价格**下降**多少次可以使得**价格相等**，而股票**没有上升的情况**也就奠定了这道题水的基础

>至于这道题如何做，其实只需要看**每个股票价格与最小值之间的差**

如果第$i$张股票与最便宜的股票$i_{min}$之间的差**不能被$k$整除**，就说明无论如何降价都不存在价格相等的情况

这时，可能有人会想能不能把最便宜的股票降价，使价格相等

但是这道题规定了降价的价格，如果第$i$张降价$k$元，第$i_{min}$张股票降价$k$元，这样该不可能还是不可能   

所以这道题就结束了 


最后贴一下代码
```
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;
int a[100010];

ll _min(ll a,ll b) {

    return a<b?a:b;

}

int main(){

    int n,k,Min=2147483647;
    scanf("%d%d",&n,&k);

    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        Min=_min(a[i],Min);
    }

    ll ans=0;
    for(int i=1;i<=n;i++)
    {
        int x=a[i]-Min;
        if(x%k)
        {
            printf("-1");
            return 0;
        }
        ans+=x/k;
    }
    printf("%lld",ans);

    return 0;

}
```

---

## 作者：Utilokasteinn (赞：4)

真是一道大水题，入门级别的。

先定义一个minn变量记录最小值，因为题目中股票只会降，所以每都要降到minn才可以实现，即降(a[i]-minn)/k，如果不能整除，就可以直接输出-1，结束程序。否则，ans就加上这个数。代码很简单，如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[100001],k,minn=1e9,ans;
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;minn=min(minn,a[i++]))
	    cin>>a[i];//输入a[i]，并且更新minn 
	for(int i=1;i<=n;i++)
		if((a[i]-minn)%k)cout<<-1,exit(0);//这是强制结束程序 
		//如果不能整除，就直接输出-1，结束程序 
		else ans+=(a[i]-minn)/k;//否则就加上这个数 
	cout<<ans;//输出答案 
	return 0;
}
```
谢谢观赏

---

## 作者：lrmlrm_ (赞：0)

# 题意

有 $ n $ 只股票原价$ h_i \left( \text{单位} : \text{卢布} \right) $，每次操作可将其中一只股票的价格下降 $ k $ 卢布 $ \left( \text{可降为负数} \right) $，问几次操作后可将所有股票的价格相等。如果不可以令股票的价格价格相等，则输出 $ -1 $ 。
$ \left( 1 \leq n \leq 10^5 , 1 \leq k \leq 10^9 , 1 \leq a_i \leq 10^9 \right) $

# 思路

由于题目要让所有数相等，所以要让大的数尽量靠近小的数。如果这个数与最小值的差能被 $ k $ 除尽，那么这个数变小所用的次数就是这个数与最小值的差$ \div k $所得的结果。如果除不尽，那么这个数就无法变为最小值。如果有一个数不能变为最小值，那么就要输出 $ -1 $ 。
$ \left( \text{不要问我为什么最小值不用减，就算减了也是浪费次数} \right) $

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,mi=2100000000,sum=0; 
long long a[1000010];//十年OI一场空，不开long long见祖宗。
int main(){
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		mi=min(a[i],mi);
	}
	for(int i=1;i<=n;i++){
		if((a[i]-mi)%k){sum=-1;break;}
		else sum+=(a[i]-mi)/k; 
	}
	printf("%lld",sum); 
	return 0;
}
```


---

## 作者：WinterRain208 (赞：0)

CF793A 【Oleg and shares】

### 题意分析

给你若干个整数，每次挑选一个数减去$k$，问至少减几次才能统一所有元素。

还需要判断无解。

### $SOLUTION$

求最少肯定是要把所有元素减为最小那个。

无解情况：一个元素和最小元素只差不是$k$的倍数，无解，这个元素必然不能成为那个最小的元素。

排序一遍。（也可以不排）

把每个元素与最小元素做差除以$k$，再累加就是答案。

### 时间复杂度

判断无解：$O(n)$

如果要排序$O(nlogn)$

要不然$O(n)$

总复杂度：$O(n)$

### CODE

```cpp
#include<bits/stdc++.h>
#define ll long long

using namespace std;
const int N=1e5+5;

#define F(i,j,r) for(int i=j;i<=r;++i)

int n,k;
int a[N],ans=0;

void read(){
	scanf("%d%d",&n,&k);
	F(i,1,n)scanf("%d",&a[i]);
}

void print(){
	printf("%d",ans);
	puts("");
}
int main(){
	read();
	sort(a+1,a+1+n);
	F(i,2,n)
		if((a[i]-a[i-1])%k){
			puts("-1");
			exit(0);
		}
	F(i,2,n)
		ans+=((a[i]-a[1])/k);
	print();
	return 0;
} 
```

如果有错误欢迎指出。

### 小结

本题难点在于理解题意，~~什么股票，涨跌都是唬人的kk。~~

$wtrl$

---

## 作者：Eason_AC (赞：0)

## Content
有 $n$ 支股票，第 $i$ 支股票原价为 $a_i$ 卢布。每秒钟可能会有任意一支股票的价格下降 $k$ 卢布，以至于降到负数。求所有股票的价格均变得相同所要经过的最短时间，或者这不可能。

**数据范围：$1\leqslant n\leqslant 10^5,1\leqslant k,a_i\leqslant 10^9$。**
## Solution
因为股票的价格只能够下降，因此肯定是要求最后都要降到 $n$ 支股票的价格的最小值 $x$。然后，因为每秒下降 $k$ 卢布，所以，只要有 $i$ 使得 $k\nmid a_i-x$ 那么就不可能满足题目的条件，否则，答案就是 $\sum\limits_{i=1}^n\dfrac{a_i-x}{k}[a_i\neq x]$。
## Code
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;

int a[100007];
long long ans;

int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; ++i)	scanf("%d", &a[i]);
	sort(a + 1, a + n + 1);
	for(int i = 2; i <= n; ++i) {
		if((a[i] - a[1]) % k)	return printf("-1"), 0;
		ans += (a[i] - a[1]) / k;
	}
	printf("%lld", ans);
}
```

---

## 作者：lu_fish (赞：0)

这道题还是比较水的一道橙题~~那你第一遍还没过~~。

只要先找到最小的那个数，然后分别去试能不能刚好降到最小值，如果不彳亍的话即使最小值下降也不可能了。



具体的细节就看着代码来吧**不开long long见祖宗**
```cpp
#include<iostream>
#include<algorithm>//后面的min_element要用
using namespace std;
typedef long long ll;//将longlong——>ll节约打字时间
int main(){
    ll n,k,a[100010],ans=0;
    cin>>n>>k;
    for(ll i=0;i<n;i++)cin>>a[i];
    ll minn=*min_element(a,a+n);//这里是取a数组中的最小值，与sort写法类似，唯一不同的是前面要加*
    for(ll i=0;i<n;i++){
        if((a[i]-minn)%k!=0){//发现无法到降到最小值就可以直接退出了
            cout<<-1;
            return 0;
        }
        ans+=(a[i]-minn)/k;//给答案增加下降个数
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：安子 (赞：0)

### 怎么说呢，这是一道图论题，如果没有对数学有较好思考的同学，~~难以想出代码~~。




首先可以清楚的知道，降价后的任何一支股票的价格，一定是小于等于股票中最价格

小的那一股（代码中用$minx$来表示）的，那么，我们可以先将降到这一段的时间给算

出来，相差的时间/一秒可以降价的卢布（由于是整除，可以忽略多出的）,得到：


当前这股降价的时间=$(a[i]-min(x))\div k$


接着，可以证明，如果当前值与最小值的差无法被k整除，及两股永远无法达到相同的

价值，代码中用bj来作为标记,当判断到有任意一股与$minx$的差无法被k整除，这个数

即永远无法达到相同值，即如果

  $x-y=b $ $b$%$k\neq 0$

则$x-c1\times k\neq y-c_{2}\times k$

代码如下 ~~注意防抄袭~~
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[500000];
int main()
{
  int n,i,j,k,bj=0;
  long long sum=0;
  long long ans=0;//最好定义long long ,否则...
  long long minx=0x3f3f3f3f;
  scanf("%d%d",&n,&k);
  for (i=1;i<=n;++j)  scanf("%d",&a[i]),minx=min(minx,a[i]);
  //输入，以及求出最小值
  for (i=1;i<=n;++j)
  {
  ans+=(a[i]-minx)/k;
  if ((a[i]-minx)%k!=0) bj=1;//判断这股从而达到能否经降价达到minx
  }
  if (bj=0) cout<<ans<<endl;
  else
  cout<<"-1"<<endl;//输出
  return 0;
}
```


---

