# Jamie and Alarm Snooze

## 题目描述

Jamie loves sleeping. One day, he decides that he needs to wake up at exactly $ hh:mm $ . However, he hates waking up, so he wants to make waking up less painful by setting the alarm at a lucky time. He will then press the snooze button every $ x $ minutes until $ hh:mm $ is reached, and only then he will wake up. He wants to know what is the smallest number of times he needs to press the snooze button.

A time is considered lucky if it contains a digit ' $ 7 $ '. For example, $ 13:07 $ and $ 17:27 $ are lucky, while $ 00:48 $ and $ 21:34 $ are not lucky.

Note that it is not necessary that the time set for the alarm and the wake-up time are on the same day. It is guaranteed that there is a lucky time Jamie can set so that he can wake at $ hh:mm $ .

Formally, find the smallest possible non-negative integer $ y $ such that the time representation of the time $ x·y $ minutes before $ hh:mm $ contains the digit ' $ 7 $ '.

Jamie uses 24-hours clock, so after $ 23:59 $ comes $ 00:00 $ .

## 说明/提示

In the first sample, Jamie needs to wake up at 11:23. So, he can set his alarm at 11:17. He would press the snooze button when the alarm rings at 11:17 and at 11:20.

In the second sample, Jamie can set his alarm at exactly at 01:07 which is lucky.

## 样例 #1

### 输入

```
3
11 23
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
01 07
```

### 输出

```
0
```

# 题解

## 作者：HanPi (赞：8)

[CF916A Jamie and Alarm Snooze](https://www.luogu.com.cn/problem/CF916A)

思路:

思路1. 枚举所有可能的时间,然后计算当前时间到目标时间差几个 $\tt{x}$ 分钟取最小,但需要考虑这个时间是第几天很复杂.

思路2. 既然 $\tt{hh:mm}$ 是由幸运时间加上多个 $\tt{x}$ 分钟得到的,那么我们从 $\tt{hh:mm}$ 往回枚举,如果遇到幸运时间,那么它一定是答案时间.

- 判断:因为$\tt{0\leqslant hh<24 , 0\leqslant mm<60}$ 所以小时和分钟的十位都不可能出现 `7` 所以我们只需要判断个位即可.

$\huge\tt{Code:}$

```c
#include <stdio.h>

int x, hh, mm, ans;
int main()
{
    scanf("%d%d%d", &x, &hh, &mm);
    while (1)
    {
        if (hh % 10 == 7 || mm % 10 == 7)break;
        ans++;
        mm -= x;
        if (mm < 0)
        {
            hh--;
            mm += 60;//注意不可以直接=59,是-x不是-1
        }
        if (hh < 0)hh += 24;//不可以是=23,理由同上
    }
    printf("%d", ans);
    return 0;
}
```


---

## 作者：REAL_曼巴 (赞：1)

此题是一道模拟题。首先，先简化一下题意，就是给定一个分钟数，在给定一个时间，看看往后退多少次这样的分钟即可到达这一个有“七”时间。

这题考计时法吧。我们要有一个答案计数器，没推一次加一次，这样一直往后退分钟，注意到跨小时与跨天的情况。这样一直循环，直到我们的时间内发现了“七”即可打印答案。

小建议：在判断是否打印时，我们只需要判断各位是否为“七”哦！


```cpp
#include<iostream>
using namespace std;
int main(){
    int x,a,b,ans=0;//清0
    cin>>x>>a>>b;
    while(1){
        if(a%10==7||b%10==7){//判断是否为7
            cout<<ans;
            return 0;
        }
        ans+=1,b-=x;//将次数增加，并往后推时间
        if(b<0)a--,b+=60;//当发现分钟小于0，代表一小时过去了，从头开始一小时。
        if(a<0)a+=24;//一天过去了
    }
    return 0;
}

```



---

## 作者：_Spectator_ (赞：0)


[可能更好的食用体验](/blog/523641/CF916A) $|$ 
[题目传送门](/problem/CF916A) $|$ 
[我的其他题解](/blog/523641/#type=题解)

------------

${\large\color{#00CD00}\text{主要思路}}$

每次往前倒推 $x$ 分钟，并增加答案。然后判断是否为幸运时间，如果是，就输出答案。

具体实现方式：

- 判断当前时间是否为幸运时间。因为 $hh$ 和 $mm$ 的十位都不可能达到 $7$，所以只需判断个位是否为 $7$ 即可。如果是，退出并输出 $ans$。
- 将 $mm$ 减少 $x$，增加 $ans$。
- 如果 $mm<0$，说明过了一个小时。此时将 $hh$ 减少 $1$，同时将 $mm$ 增加 $60$。
- 如果 $hh<0$，说明过了一天。此时将 $hh$ 设为 $23$。

~~这道题有 200 多个数据点也是离谱……~~

------------

${\large\color{#00CD00}\text{完整代码}}$

```cpp
#include<bits/stdc++.h>
using namespace std;
long long x,h,m,ans;
int main()
{　
	cin>>x>>h>>m;　
	while(h%10!=7&&m%10!=7)//判断是否为幸运时间
	{　
		m-=x,ans++;//向前倒推x分钟并增加答案
		if(m<0)h--,m+=60;//过了1小时
		if(h<0)h=23;//过了1天
	}　
	cout<<ans;　
	return 0;　
}　
```

**[${\color{Black}\textbf{xt\_\_}}$](/user/523641) 温馨提示：**


${\large\color{White}\text\colorbox{#AD8800}{题解千万条，理解第一条。直接粘题解，棕名两行泪。}} $

---

## 作者：_HiKou_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF916A)

首先，如果想快速找到最近的幸运时间，最好的方法是往前逆推。

所以把分钟数每次减去 $x$ ，直到找到幸运时间。

但是如果 $x$ 很大，比如 $x=114514$ 时怎么办呢？

一个好的方法是用 while 借位，每次借位时 $m=m+60,h=h-1$，如果 $h$ 超出了范围（即变成了负数），就变成 23 ，直到 $m≥x$。

而且，十位数不可能达到 7，所以只需要判断个位数就可以啦~

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int x,h,m,ans=0;
	cin>>x;
	cin>>h>>m;
	while(h%10!=7&&m%10!=7)//判断
	{
		while(m<x)//只要小于 x 就一直借位
		{
			h--;
			if(h==-1)h=23;//超出范围就转到上一天
			m+=60;	//借位
		}
		m-=x;
		ans++;//每次按下贪睡按钮就加到答案里
	}
	cout<<ans;
	
	return 0;
}
```

---

## 作者：kkio (赞：0)

## 题意 ##

从 $hh:mm$ 往回推 ， 每次推 $x$ 分钟 , 问推多少次能推出一个包含$7$的时间。

## 思路 ##
有几点要注意的：

由于小时十位只能到$2$ , 分钟只能到$6$ ，所以不用考虑十位。

时间可以跨天，会从$0$点跳到$23$点。

枚举出来的时间一定最佳。(因为是从目标一步步枚举的)

所以, 我们用 while 循环不停枚举, 直到枚出一个"幸运时间", 即可。 

## AC 代码 ##
```cpp
#include <bits/stdc++.h>
using namespace std;
int h,m,x,ans;
int main(){
	scanf("%d%d%d",&x,&h,&m);
	while(1)//循环枚举
	{
		if(h%10==7||m%10==7)//找到了就输出
		{
			printf("%d\n",ans);
			return 0;
		}
		m-=x;
		if(m<0)//跨小时
		{
			m+=60;
			h--;
		}
		if(h<0)h+=24;//跨天
		ans++;
	}
}
```


---

## 作者：Eason_AC (赞：0)

## Content
令一个时间为幸运时间，当且仅当该时间中包含数字 $7$。

小 J 很懒，他决定在 $h$ 时 $m$ 分起床，于是他将闹钟设定在一个很幸运的时间，并通过按一次按钮以多睡 $x$ 分钟一直睡到 $h$ 时 $m$ 分，现在他想知道最少需要按多少次按钮。

**数据范围：$0\leqslant h\leqslant 23,0\leqslant m\leqslant 59$。**
## Solution
题目中问的其实就是距离 $h$ 时 $m$ 分最近的幸运时间。正着推比较难想，我们不妨从 $h$ 时 $m$ 分开始倒着推，每次倒退回去 $x$ 分钟，出现的第一个幸运时间就是我们所需要的答案。
## Code
```cpp
int x, h, m, ans;

int check(int x, int y) {
	int p = x, q = y;
	while(p) {
		if(p % 10 == 7)	return 1;
		p /= 10;
	}
	while(q) {
		if(q % 10 == 7)	return 1;
		q /= 10;
	}
	return 0;
}

int main() {
	getint(x), getint(h), getint(m);
	while(1) {
		if(check(h, m))	return writeint(ans), 0;
		m -= x;
		ans++;
		if(m < 0)	h--, m += 60;
		if(h < 0)	h += 24;
	}
	return 0;
}
```

---

## 作者：DIgnited (赞：0)

### 本题思路：用死循环慢慢模拟，每次时间向后退$x$分钟。一旦遇到lucy time就退出循环输出答案。如果遇到$mm$不够-$x$便令$hh$退60分钟给$mm$。而$hh$不够便向前推一天，即给$hh$赋值为23。

## 代码：

```cpp
//CF916A
#include<bits/stdc++.h>//万能头 
#define sc scanf//懒人神器宏定义 
#define pr printf//
using namespace std;//标准命名空间 
int main()//主函数 
{
	int x,hh,mm,s=0;//s为计数器 
	sc("%d%d%d",&x,&hh,&mm);//因为有宏定义，此处等同于scanf
	for(int i=0;;i++)//死循环，知道达成条件退出
	{
		if(hh%10==7||mm%10==7)//特判退出 
			break;//终止死循环
		if(mm-x>=0) 
		{
			s++;//神奇海螺次数加一 
			mm-=x;
		}
		else if(hh-1>=0)//没有隔天 
		{
			hh--;
			mm+=60-x;
			s++; 
		}
		else if(hh-1<0)//隔天 
			hh=23;//下一次循环再判断
	}
	pr("%d",s);//输出答案 
	return 0;
}
```


---

## 作者：LucasXu80 (赞：0)

来看一篇Python题解吧~

先来看思路。读完题目，我们明白题目其实就是**让你找出在起床时间前最接近的符合要求的幸运时间**。这里符合要求指闹铃时间与起床时间差$x$的倍数分钟。

这时候，很容易想到，从起床时间往回找是更快的，而不是从前往后找，等到时间比起床时间大了就break。

为什么呢？因为前者可以在计算的时候就标记$ans$，更快一点。

这道题的思路其实就是这样了，并不难。更为复杂的是跨天数的时间计算（如$23:59-00:00$）。

按照我们的做法（从后往前），这里的计算只涉及从后面一天回到前面一天。来看个例子吧：

$00:05$减$7$分钟等于？

我们先减分钟变成：$00:-2$。显然这是不对的。

那我们就要向小时那一位借$1$小时也就是$60$分钟。像这样：$0-1:-2+60$，也就是$-1:58$。

小时怎么是负的了？没关系，这个时候我们变成$23$时即可（$0$时往前$1$个小时是$23$时）：$23:58$

好了，现在我们把这个过程搞清楚了，那就没问题啦。上代码！

```python
import sys
x=int(input())
h,m=map(int,input().split()) #输入时分，前导0会自动舍去
ans=0 #记录答案
while 1: #无限循环，直到找到答案退出
    if h%10==7 or m%10==7: #先判断，以防原来的时间就是幸运时间
        print(ans) #满足条件就输出ans并结束程序
        sys.exit()
    ans+=1 #没有找到答案，ans+1，表示多按一次
    m-=x #往回x分钟
    if m<0: #分钟是负的
        m+=60 #借来60分钟
        h-=1 #被借走1小时
    if h<0: h=23 #小时是负的，直接变成23时
```
好了，就到这里啦。希望大家喜欢！

---

## 作者：codemap (赞：0)

一道比较简单的模拟（~~对于经常刷红题的我来说还使比较麻烦的~~）

只要考虑清楚进位就可以了

不说了上代码
```
#include<iostream>
using namespace std;
int main()
{
    int x,hh/*小时*/,mm/*分钟*/,s=0/*答案*/;
    cin>>x>>hh>>mm;
    while(1)//无限循环
    {
        if(hh%10==7||mm%10==7)//条件成立
        {
            cout<<s;
            break;
        }
        s++;//次数加一
        mm-=x;//分钟减
        while(mm<0)//分钟变负时小时减
        {
            mm+=60;
            hh--;
        }
        while(hh<0)//时间变负时新的一天（新的一天=小时+24）
            hh+=24;
    }
    return 0;//完美结束
}
```

---

