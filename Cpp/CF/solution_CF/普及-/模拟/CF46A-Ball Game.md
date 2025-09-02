# Ball Game

## 题目描述

原题意

幼儿园老师纳塔利娅帕夫洛夫娜发明了一种新的球类游戏。这场比赛不仅培养了孩子们的体格，还教会了他们如何计数。

游戏如下。孩子们围成一圈。将孩子顺时针编号为1至n的数字，并且孩子1持球

之后有n-1次投球 第i次投球将会把球从持球孩子手中传至持球孩子右边第i个孩子

比如有8个孩子 依次接到球的孩子编号是 2 4 7 3 8 ...

简洁版题意

有数列 $f$ ， $f_0 = 1$ ， $f_i=((f_{i-1}+i-1)\;mod\;n)+1$ 。输出 $f_1$ ~ $f_{n-1}$ 。

## 样例 #1

### 输入

```
10
```

### 输出

```
2 4 7 1 6 2 9 7 6
```

## 样例 #2

### 输入

```
3
```

### 输出

```
2 1
```

# 题解

## 作者：_cmh (赞：10)

本题蒟蒻甚是惊讶

怎么这题题解基本上都用数组？！

蒟蒻来提供一个新的方法

只要两个变量

我们定义n，在定义一个存储上次的数，一直更新输出即可

上代码：

```cpp
#include<iostream>//头文件 
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<string>
#include<cstdlib>
using namespace std;
int n,last;//定义 
int main(){
    cin>>n;//读入 
    last=1;//记得初始化F0 
	for(int i=1;i<n;i++){//从F1求到Fn-1 
		last=((last+i-1)%n)+1;//更新 
		cout<<last<<" ";//输出 
	} 
    return 0;//完结撒花 
}
```

## ~~无耻地~~求个赞！！

~~（蒟蒻已经逃跑了，没法和泥萌说再见了）~~

---

## 作者：GusyNight (赞：1)

```
其实这道题目很简单，
因为，题目中已经将公式告诉了我们
```
$f$ ， $f_0 = 1$ ， $f_i=((f_{i-1}+i-1)\;mod\;n)+1$ 。输出 $f_1$ ~ $f_{n-1}$

``
于是就可以写出以下公式哦~~~
``
```cpp
f[i]=(f[i-1]+i-1)%n+1;
```
```
和代码
```
```cpp
#include<bits/stdc++.h>
#define TP int
using namespace std;
inline TP read(){
    char c=getchar();
    TP x=0;
    bool f=0;
    while(!isdigit(c))f^=!(c^45),c=getchar();
    while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f)x=-x;return x;
}
int main(){
	int n=read();
	int f[n+1];
	for(int i=1;i<n;i++){
		f[i]=(f[i-1]+i-1)%n+1;
		cout<<f[i];
		cout<<" ";
	}
	return 0;
}
```
**但是，第一个点就会WA这是为什么呢？**
```cpp
这是一个很好的教训，f[0]要初始化为"1"
```
```cpp
#include<bits/stdc++.h>
#define TP int
using namespace std;
inline TP read(){
    char c=getchar();
    TP x=0;
    bool f=0;
    while(!isdigit(c))f^=!(c^45),c=getchar();
    while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f)x=-x;return x;
}
int main(){
	int n=read();
	int f[n+1];
	f[0]=1;
	for(int i=1;i<n;i++){
		f[i]=(f[i-1]+i-1)%n+1;
		cout<<f[i];
		cout<<" ";
	}
	return 0;
}
```
**所以这次告诉我们，任何时候都不要忘了初始化~~~**

---

## 作者：江山_远方 (赞：0)

作为一名~~资深~~蒟蒻，我一眼就看出这道题是一道标准的~~

水题！

咳咳，话不多说，我们来讲解一下这道题

题目的意思是这样的：

有一个数 x

第一秒，x为1

之后的i: 2~n秒，x会扩展为x+i-1

但是只要x比N大，它就必须%=n

因为小朋友只有N个

所以 我们可以得到如下代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int x;
int main()
{
	cin>>n;
	x=1;
	for(int i=2;i<=n;i++)
	{
		x=(x+i-1-1)%n+1;//凑整公式，原式为x=(x-1)%n+1,再加上之前推出的公式，即得此公式
		printf("%d ",x);
	} 
	return 0;
} 
```


---

## 作者：七夜 (赞：0)

//这道题不知道为什么写题解的人这么少，那我就来凑凑数吧

//这道题有一个坑点，就是整除的时候怎么办，如果不处理，输出零，那代码就错了

//所以必须进行处理，于是就有了本蒟蒻下面的代码（附带注释）：

```
#include<bits/stdc++.h>//偷懒专用库 
using namespace std;//绝对不可少的东西 
inline int read()
{
	char c=getchar();int x=0,f=1;
	while(c<'0'||c>'9'){if(c=='-') c=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}//此处为快读，可供借鉴，也可以忽略，换成cin或者scanf 
int n,f[100000];//n是数据范围，f用来存数 
int main()//开始主函数 
{
	n=read();//读入，可以换成cin或者scanf
	int z=1;//角标 
	f[0]=1;//题目描述 
	f[1]=1;//因为他是从第一个人开始数，不是第零个，所以要把f【1】求出来 
	while(z<n)//结束条件 
	 {
	 	z++;//角标自加 
	 	f[z]=((f[z-1]+z-1)%n);//求出此时的数 
	 	if(f[z]==0)//如果刚好整除，代表是最后一个，所以输出n，不这么做会输出零，对两个点就卡了 
	 	 cout<<n<<" ";
	 	else//其他情况直接输出 
	     cout<<f[z]<<" ";
	 }
	return 0;//完美而不失风度的结束 
}
```
//还希望能够通过

---

## 作者：applese (赞：0)

个人认为红题吧，因为规律已经出来了：

就是$f_i=((f_{i-1}+i-1)\;mod\;n)+1$

求当时的$f_i$

那么附上代码：
```
#include<bits/stdc++.h>
using namespace std;
int n;     //定义
int main()
{
	cin>>n;
	int f[n+1];  //节约空间
	f[0]=1;     //先定义第零个数组
	for(int i=1;i<n;i++)
	{
		f[i]=(f[i-1]+i-1)%n+1;   //进行递归QAQ
		cout<<f[i]<<" ";     //并输出
	}
	return 0;
}
```

是不是很简单明了QAQ如果有问题，请在**右侧**提出，蟹蟹QAQ

---

## 作者：agicy (赞：0)

# 题意

有数列 $f$ ， $f_0 = 1$ ， $f_i=((f_{i-1}+i-1)\;mod\;n)+1$ 。输出 $f_1$ ~ $f_{n-1}$ 。

来自@钟梓俊 。

## 题面源代码

```
有数列 $f$ ， $f_0 = 1$ ， $f_i=((f_{i-1}+i-1)\;mod\;n)+1$ 。输出 $f_1$ ~ $f_{n-1}$ 。
```

# 思路

很明显，照题意模拟即可。

## 细节

当$f_i\%n=0$时，应当输出$n$而不是$0$。

# 代码

代码如下。

```
#include<stdio.h>

int n;

int main(void){
	register int i,j;//用变量j来代替数列f中的元素
	scanf("%d",&n);
	for(i=j=1;i<n;i++)
		printf("%d ",((j+=i)%n?j%n:n));//当f_i\%n=0时，应当输出n而不是0
	return 0;
}
```

## [我的测评记录](https://www.luogu.org/record/show?rid=9688269)

---

