# Bear and Game

## 题目描述

Bear Limak likes watching sports on TV. He is going to watch a game today. The game lasts $ 90 $ minutes and there are no breaks.

Each minute can be either interesting or boring. If $ 15 $ consecutive minutes are boring then Limak immediately turns TV off.

You know that there will be $ n $ interesting minutes $ t_{1},t_{2},...,t_{n} $ . Your task is to calculate for how many minutes Limak will watch the game.

## 说明/提示

In the first sample, minutes $ 21,22,...,35 $ are all boring and thus Limak will turn TV off immediately after the $ 35 $ -th minute. So, he would watch the game for $ 35 $ minutes.

In the second sample, the first $ 15 $ minutes are boring.

In the third sample, there are no consecutive $ 15 $ boring minutes. So, Limak will watch the whole game.

## 样例 #1

### 输入

```
3
7 20 88
```

### 输出

```
35
```

## 样例 #2

### 输入

```
9
16 20 30 40 50 60 70 80 90
```

### 输出

```
15
```

## 样例 #3

### 输入

```
9
15 20 30 40 50 60 70 80 90
```

### 输出

```
90
```

# 题解

## 作者：江山_远方 (赞：1)

蒟蒻太弱了 只会根据题意写qwq  
本题蒟蒻采用标记的方式，用b数组来表示第i分钟是否是有趣的分钟，1为是，0为不是，然后枚举每一分钟，假如是无聊的分钟则让记录连续无聊分钟数的变量x++，否则x清零，若x>=15则输出当前的分钟数并结束程序，否则继续循环，最后假如一直看到结束，则输出90，代码如下：
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;//名字空间
int n,s,x;
int b[100];//定义
int main()
{
	cin>>n;//读入有趣分钟数
	for(int i=1;i<=n;i++)//枚举每个有趣分钟
	{
		scanf("%d",&x);//读入第i个有趣分钟的时间位置
		b[x]=1;//标记有趣分钟
	}
	x=0;//从现在开始x表示连续无聊分钟数，所以要从头做变量，清零
	for(int i=1;i<=90;i++)//枚举每一分钟
	{
		if(!b[i])x++;
		  else x=0;
		s++;
		if(x>=15)break;//此处上面讲过
	}
	cout<<s;//输出
	return 0;
}
```
AC抱回家

---

## 作者：applese (赞：1)

我有种感觉此题是红题哎qaq

此题就是输入一个数，用这个数$x+15$，如果下一个数$y$大于上一个数$x+15$,就直接输出$x+15$就好啦，但是要两个特判：
```
1.当第一个数>15时，直接退出输出15.
2.当所有的和>90时，直接退出输出90.
```

那么现在就上代码吧qaq（思路和下面的大佬略有相同）:
```
#include <iostream>

using namespace std;

int main()
{
	int n , k=15 , a;   //定义
	cin >> n;
	for(int i=1;i<=n;i++)
	{
		cin >> a;
		if(a <= k)    //当处于兴趣范围内
		k = a + 15;   //换成当时时间并+15（如果下次不在范围内直接输出
		else
		break;       //如果大于的话就退出吧
		if(k > 90)   //当超过比赛时间
		{
			k = 90;   //直接结束啦，还看什么qaq
			break;    //退出
		}
	}
	cout<<k;   //直接输出
	return 0;
}
```

---

## 作者：Snow_Dreams (赞：0)

这道题还是十分简单的

我们根据题意模拟即可

首先，我们分析一下样例

首先读入一个n，接着就读入一些数，这里可以不用数组，用一个变量即可

注意到题中说输入数据从小到大，所以，就可以依次读入

在读入的时候，我们要加几个特判

1． 若第一个数＞15，就输出15
2． 若中间数间隔＜15，就枚举下一个数
3． 若

---

## 作者：时律 (赞：0)

直接按照题目要求模拟就可。

日常水一波快读快写qwq

```
#include<bits/stdc++.h>
using namespace std;
int x[105];//x[i]表示第i分钟无不无聊(1有趣,0无聊)
int r()//快读
{
	char c=getchar();int u=0,s=1;
	while(c<'0' or c>'9'){if(c=='-') s=-1;c=getchar();}
	while(c>='0' and c<='9'){u=(u<<3)+(u<<1)+(c^48);c=getchar();}
	return u*s;
}
void p(int n)//快写
{
	if(n<0){putchar('-');n=-n;}
	if(n>9) p(n/10);
	putchar(n%10+'0');
}
int main()
{
	int a=r(),b=0;//b为计数器，代表无聊的连续时间
	for(int i=1;i<=a;i++)
		x[r()]=1;
	for(int i=1;i<=90;i++)
		if(x[i]==0)//如果无聊
		{
			b++;//无聊的连续时间++
			if(b==15)//无聊的连续时间到了15分钟
			{
				p(i);//K.O.
				return 0;
			}
		}
		else
			b=0;
	p(90);
}

```

---

## 作者：ShineEternal (赞：0)

没什么好说的，直接上代码

```
#include<cstdio>
using namespace std;
int main()
{
    int n,x,pd=0;//pd记录的是当前看到第多少分钟
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&x);
        if(pd+15<x)//如果到了15分钟还没有有趣时间，
        {
            printf("%d\n",pd+15);//只能看到这了。
            return 0;//返回吧，省着麻烦
        }
        else
        	pd=x;//否则的话直接看到那个有趣时间
    }
    if(x<=75)
    {
        printf("%d\n",x+15);
        return 0;
    }//最后一个有趣时间要是和90还差了15分钟或以上，就只能看到它加上15分钟了
    printf("90\n");//如果任何情况都不满足，那一定是看完了
    return 0;
} 
```

求过，求赞

---

