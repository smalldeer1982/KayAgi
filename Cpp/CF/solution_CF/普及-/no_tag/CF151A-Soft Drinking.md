# Soft Drinking

## 题目描述

This winter is so cold in Nvodsk! A group of $ n $ friends decided to buy $ k $ bottles of a soft drink called "Take-It-Light" to warm up a bit. Each bottle has $ l $ milliliters of the drink. Also they bought $ c $ limes and cut each of them into $ d $ slices. After that they found $ p $ grams of salt.

To make a toast, each friend needs $ nl $ milliliters of the drink, a slice of lime and $ np $ grams of salt. The friends want to make as many toasts as they can, provided they all drink the same amount. How many toasts can each friend make?

## 说明/提示

A comment to the first sample:

Overall the friends have $ 4*5=20 $ milliliters of the drink, it is enough to make $ 20/3=6 $ toasts. The limes are enough for $ 10*8=80 $ toasts and the salt is enough for $ 100/1=100 $ toasts. However, there are 3 friends in the group, so the answer is $ min(6,80,100)/3=2 $ .

## 样例 #1

### 输入

```
3 4 5 10 8 100 3 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5 100 10 1 19 90 4 3
```

### 输出

```
3
```

## 样例 #3

### 输入

```
10 1000 1000 25 23 1 50 1
```

### 输出

```
0
```

# 题解

## 作者：Reywmp (赞：5)

下面题解没有解释啊，怎么肥四。

当然这题比较水应该也可以看懂。

不过现在我来送上一发~~良心~~睿智题解。

我们来整理一下：

>n个小老板

>买了3种东西：柠檬，饮料和盐

>要做吐司（厨渣求解这3玩意怎么做吐司

>饮料共有K瓶，每瓶L毫升，所以一共有K×L毫升饮料

>又一共有c个柠檬，切成d片，注意：切后柠檬会分成很多小块，所以数量变多，得出共有c×d片柠檬。

>一共有p克盐。

>做吐司要求1片柠檬，np克盐，nl毫升饮料

>求出一个人最多能做多少吐司（即平均数

------------

**推导：**

- 做一个吐司要求3种材料全齐并且不少量，所以不可以将余下的材料继续做吐司。

- 那么我们在饮料能分多少个吐司，柠檬能分多少个和盐能分多少个里面选**最小值**。

- 饮料能分成K×L÷nl个，盐能分成p÷np而柠檬能分成c×d÷1则为c×d个。

- 答案即为3个中最小的除以n了，注意因为要求平均值所以除以n（不然给你n干嘛呢）。

-------------

```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cmath>
#define ll long long
//IG NB!
using namespace std;
void read(int &x)
{
	 x=0;int w=1;
	 char ch=getchar();
	 while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
	 if(ch=='-')w=-1,ch=getchar();
	 while(ch>='0'&&ch<='9')
	 {x=(x<<1)+(x<<3)+ch-48,ch=getchar();}
	 x*=w;
}
int mx(int a,int b){return a>b?a:b;}
int mn(int a,int b){return a<b?a:b;}
int n,k,l,c,d,p,nl,np;
int main()
{
    read(n);read(k);
    read(l);read(c);read(d);read(p);read(nl);read(np);
    int ans,tmp;
    tmp=mn(k*l/nl,p/np);
    ans=c*d;
    ans=mn(tmp,ans);
    printf("%d",ans/n);
    putchar('\n');
    return 0;
}
```

---

## 作者：ShineEternal (赞：4)

# 灌水区
第一发题解！！！
~~此题略水~~

------------
# 题意简叙区
给出n，k，l，c，d，p，nl，np

求出min(k*l/nl,c*d,p/np)的值

------------

# 代码区
```cpp
#include<cstdio>
#include<cmath>
using namespace std;
int main()
{
	int n,k,l,c,d,p,nl,np;
	scanf("%d%d%d%d%d%d%d%d",&n,&k,&l,&c,&d,&p,&nl,&np);
	int x=k*l/nl;
	int y=c*d;
	int z=p/np;//先求这出些，要不然太麻烦
	int ans=fmin(fmin(x,y),z);//再取最小值
	printf("%d\n",ans/n);//换行，AT后遗症
	return 0;
}
```


------------
# 祈祷区
求过，求赞

---

## 作者：KazamiHina (赞：0)

可以先算出这些材料够几份的饮料，够几份的柠檬，和够几份的盐，然后取最小值，最后除以$n$即可

$code:$

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n,k,l,c,d,p,nl,np;

int main(){
	cin>>n>>k>>l>>c>>d>>p>>nl>>np;
	l=l*k;d=d*c;//算出总共有的饮料和总共的柠檬数
	int x=l/nl;//算出份数
	int y=d;
	int z=p/np;
	cout<<min(min(x,y),z)/n;//取最小值除以n即可
	return 0; 
}
```

$qwq$

---

## 作者：TLMPEX (赞：0)

思路：这道题很简单，按题意模拟即可，主要思路见代码。

代码。
```c
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,k,l,c,d,p,nl,np,x,y,z;
	cin>>n>>k>>l>>c>>d>>p>>nl>>np;
	x=k*l/nl;//饮料能满足多少个吐司
	y=c*d;//柠檬能满足多少个吐司
	z=p/np;//盐能满足多少个吐司
	cout<<min(x,min(y,z))/n;//取三个值中的最小值除以朋友的数量
}
```


---

