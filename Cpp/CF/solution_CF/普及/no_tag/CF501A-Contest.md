# Contest

## 题目描述

Misha and Vasya participated in a Codeforces contest. Unfortunately, each of them solved only one problem, though successfully submitted it at the first attempt. Misha solved the problem that costs $ a $ points and Vasya solved the problem that costs $ b $ points. Besides, Misha submitted the problem $ c $ minutes after the contest started and Vasya submitted the problem $ d $ minutes after the contest started. As you know, on Codeforces the cost of a problem reduces as a round continues. That is, if you submit a problem that costs $ p $ points $ t $ minutes after the contest started, you get ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF501A/0c1954e97a47d9a6cd1567e3d0ad4f4a76ada737.png) points.

Misha and Vasya are having an argument trying to find out who got more points. Help them to find out the truth.

## 样例 #1

### 输入

```
500 1000 20 30
```

### 输出

```
Vasya
```

## 样例 #2

### 输入

```
1000 1000 1 1
```

### 输出

```
Tie
```

## 样例 #3

### 输入

```
1500 1000 176 177
```

### 输出

```
Misha
```

# 题解

## 作者：Gary88 (赞：2)

    此题应用函数和判断语句，并不难。
    代码如下：
    #include<iostream>
    #include<cstdio>
     using namespace std;
     int max(int a, int b)

    {
    
    if (a>b){ return a;}
    return b;   
    }

    int main()
   
   
    {int a,b,c,d;
    scanf("%d%d%d%d",&a,&b,&c,&d);
    int aa=a*3/10;
    int bb=a-a/250*c;
    int cc=b*3/10;
    int dd=b-b/250*d;
    if(max(aa,bb)>max(cc,dd))
    {
        printf("Misha");
    }else if(max(aa,bb)<max(cc,dd))
    {
        printf("Vasya");
    }else
    {
        printf("Tie");
    }
	return 0;
    }

---

## 作者：Provider (赞：1)

# 题意

给出a,b,c,d,表示Misha过了c分钟获得a点points,Vasya过了d分钟获得b点points.

**如果你过了t分钟获得p点points则能得到max(3*p/10,p*t/250)分.**

询问Misha的分数高还是Vasya的分数高，输出分数高的人的名字，分数相同输出"Tie".

根据题意模拟即可

# CODE
```
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int m,v;
}point1,point2,realpoint;//分数的结构体
int a,b,c,d;
int main()
{
	cin>>a>>b>>c>>d;
	point1.m=3*a/10;
	point2.m=a-a*c/250;//Misha的两个分数
	point1.v=3*b/10;
	point2.v=b-b*d/250;//Vasya的两个分数
	realpoint.m=max(point1.m,point2.m);
	realpoint.v=max(point1.v,point2.v);//根据题意求最终分数
	if(realpoint.m>realpoint.v)
	cout<<"Misha";
	else
	if(realpoint.m<realpoint.v)
	cout<<"Vasya";
	else
	cout<<"Tie";//相同输出Tie
	return 0;
}
```

---

## 作者：caibet (赞：0)

### 题意：

给出 $a,b,c,d$，已知 $f(t,p)=\max(\frac{3p}{10},p-\frac{p}{250}\times t)$，判断 $f(c,a)$ 与 $f(d,b)$ 的大小关系。

### 解法：

根据题意计算。不过，由于涉及分数，还是使用 `double` 为好。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	double a,b,c,d;
	cin>>a>>b>>c>>d;
	double x=max(a*3/10,a-a/250*c);//求出f(c,a)的值
	double y=max(b*3/10,b-b/250*d);//求出f(d,b)的值
	if(x>y) cout<<"Misha";//输出结果
	else if(x<y) cout<<"Vasya";
	else cout<<"Tie";
	return 0;
}
```


---

## 作者：_Clown_ (赞：0)

# 概述
|题号|难度|$AC$时间及记录|
| :----: | :----: | :----: |
|$\texttt{CF501A}$|$\texttt{洛谷难度:普及/提高-}$|[$\texttt{On 2021/04/02}$](https://www.luogu.com.cn/record/48852644)|
# 解析
这是一道简单题。

题意不难理解。

我们知道一个公式，是题目给我们的：

$$
s=max\{\frac{3p}{10},p-\frac{p}{250}*t\}
$$

也就是说，我们这要把 $a$，$b$，$c$，$d$ 四个数据分别代入公式即可。

注意浮点数比较大小时要写一个 $EPS$。

就是说，最好不要直接比较大小。

注意，$a$ 和 $c$ 是一组的，$b$ 和 $d$ 是一组的。
# 代码
```cpp
/*
Author:Xsmyy
Problem:CF501A
Date:2021/04/02
*/
#include<bits/stdc++.h>
#define BetterIO ios::sync_with_stdio(false)
using namespace std;
int main(void)
{
	BetterIO;
	#ifndef ONLINE_JUDGE
	freopen("SampleIN.in","r",stdin);
	#else
	#endif
	register double A,B,C,D;
	cin>>A>>B>>C>>D;
	register double X,Y;
	X=max(0.3*A,A-A/250*C);
	Y=max(0.3*B,B-B/250*D);
	if(X-Y>1e-6)cout<<"Misha"<<endl;//浮点数比较
	else if(Y-X>1e-6)cout<<"Vasya"<<endl;//浮点数比较
	else cout<<"Tie"<<endl;//浮点数比较
	return 0;
}
```

---

## 作者：666DHG (赞：0)

- ### [Blog](https://666DHG.github.io/)

此题纯模拟,按题意套公式即可

为了保险起见，我们在存两个最终得分时最好用
```double```
保留精度（虽然用
```int```
也能过）

代码如下:

```cpp
#include <bits/stdc++.h>
using namespace std;

double a,b,c,d,ans1,ans2;

int main()
  {
  	cin>>a>>b>>c>>d;
  	ans1=max(3*a/10.00,a-a*c/250.00);
  	ans2=max(3*b/10.00,b-b*d/250.00);
  	if (ans1<ans2) printf("Vasya");
  	else if (ans1==ans2) printf("Tie");
  	else if (ans1>ans2) printf("Misha");
  	return 0;
  }
```

---

