# Cheaterius's Problem

## 题目描述

Cheaterius is a famous in all the Berland astrologist, magician and wizard, and he also is a liar and a cheater. One of his latest inventions is Cheaterius' amulets! They bring luck and wealth, but are rather expensive. Cheaterius makes them himself. The technology of their making is kept secret. But we know that throughout long nights Cheaterius glues together domino pairs with super glue to get squares $ 2×2 $ which are the Cheaterius' magic amulets!

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF51A/5f1914bbdaa36d78b7400d8ccae8395b8432e5c5.png)That's what one of Cheaterius's amulets looks likeAfter a hard night Cheaterius made $ n $ amulets. Everyone of them represents a square $ 2×2 $ , every quarter contains 1 to 6 dots. Now he wants sort them into piles, every pile must contain similar amulets. Two amulets are called similar if they can be rotated by 90, 180 or 270 degrees so that the following condition is met: the numbers of dots in the corresponding quarters should be the same. It is forbidden to turn over the amulets.

Write a program that by the given amulets will find the number of piles on Cheaterius' desk.

## 样例 #1

### 输入

```
4
31
23
**
31
23
**
13
32
**
32
13
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4
51
26
**
54
35
**
25
61
**
45
53
```

### 输出

```
2
```

# 题解

## 作者：Ba_creeper (赞：4)

## CF51A Cheaterius's Problem 题解

#### 题目分析

这道题是一个很不错的锻炼代码能力的题，主要思路是模拟。

每一张牌都是 $2\times2$ 的大小。而且如果两张牌通过旋转能重合就是同一张牌，我们可以模拟这一过程。

因为题目中是依次输入每一张牌，所以我们可以采用边读边操作的方法。此题的读入操作是个大工程。

为了方便读入，我们可以用 char 形式的字符读入，读入之后转成 int 类型。然后把 $a,b,c,d$ 与 $f$ 数组中的数相比较。如果它们是相同的牌，则让总牌数+1；否则就把这四个数存入 $f$ 数组，代表多了一张不同的牌。

存储每一张牌，我们可以采用三维数组 `f[i][j][k]` 来存储，其中 $k$ 表示不同的牌的张数。 我们设左上角的牌为 $a$ ，右上角的牌为 $b$ ，左下角为 $c$ ，右下角为 $d$ 。则有：

![](https://cdn.luogu.com.cn/upload/image_hosting/85jt2h14.png)

读入操作代码：

```c++
char x;
cin>>x>>x; //读入星号
cin>>ch1>>ch2;
cin>>ch3>>ch4;
int a=ch1-'0',b=ch2-'0'; // char 转 int 
int c=ch3-'0',d=ch4-'0';
f[1][1][1]=a; //存入 f 数组
f[1][2][1]=b;
f[2][1][1]=c;
f[2][2][1]=d;
```

核心部分是枚举出所有是一张牌的情况。我们可以依次旋转90度枚举即可。操作过程如下图所示：

![旋转后的所有可能情况](https://cdn.luogu.com.cn/upload/image_hosting/ct5qkoe7.png)

代码表示所有可能情况：

```cpp
if(a==f[1][1][j] && b==f[1][2][j] && c==f[2][1][j] && d==f[2][2][j])
if(c==f[1][1][j] && a==f[1][2][j] && d==f[2][1][j] && b==f[2][2][j])
if(d==f[1][1][j] && c==f[1][2][j] && b==f[2][1][j] && a==f[2][2][j])
if(b==f[1][1][j] && d==f[1][2][j] && a==f[2][1][j] && c==f[2][2][j])
```

最后输出 $f$ 数组中的 $k$ 即可。

#### 代码

```c++
#include<iostream>
#include<cstdio>
using namespace std;
int f[3][3][1003];
int main()
{
	int n;
	char ch1,ch2,ch3,ch4;
	
	//下面单独读入第一组数据，因为第一组数据上面没有星号
	cin>>n;
	cin>>ch1>>ch2;
	cin>>ch3>>ch4;
	f[1][1][1]=ch1-'0'; // char 转 int 存入
	f[1][2][1]=ch2-'0';
	f[2][1][1]=ch3-'0';
	f[2][2][1]=ch4-'0';
	
	int k=1; // k 代表不同的牌的张数 
	for(int i=2;i<=n;++i) // 从第2张牌继续读入 
	{
		bool ok=0; //临时 bool 数组，用来判断两张牌是不是相同的 
		char x;
		cin>>x>>x;
		cin>>ch1>>ch2;
		cin>>ch3>>ch4;
		int a=ch1-'0';
		int b=ch2-'0';
		int c=ch3-'0';
		int d=ch4-'0';
		
		for(int j=1;j<=k;++j) //在每张不同的牌之间枚举，看看此牌和之前的牌是不是相同 
		{
			if(a==f[1][1][j] && b==f[1][2][j] && c==f[2][1][j] && d==f[2][2][j])
			{
				ok=1; //完全相同的情况
				break;//如果和之前的牌相同，则可以跳出循环，继续读入下一组数据
			}
			if(c==f[1][1][j] && a==f[1][2][j] && d==f[2][1][j] && b==f[2][2][j])
			{
				ok=1; //顺时针旋转90度
				break;//同上
			}
			if(d==f[1][1][j] && c==f[1][2][j] && b==f[2][1][j] && a==f[2][2][j])
			{
				ok=1;//顺时针旋转180度
				break;//同上
			}
			if(b==f[1][1][j] && d==f[1][2][j] && a==f[2][1][j] && c==f[2][2][j])
			{
				ok=1;//顺时针旋转270度
				break;//同上
			}
		}
		if(ok==0) //如果这张牌和前面的各不相同，那么把这张牌存入 f 数组 
		{
			f[1][1][++k]=ch1-'0';
			f[1][2][k]=ch2-'0';
			f[2][1][k]=ch3-'0';
			f[2][2][k]=ch4-'0';
		}
	}
	printf("%d\n",k); //最后输出不同的牌的张数 
}
```

[提交记录](https://www.luogu.com.cn/record/37135530)

题解到此结束，希望大家看完思路自己模拟着打一遍，杜绝抄袭哦~

---

## 作者：MeowScore (赞：2)

## 题目大意
给定 $n$ 张 $2\times2$ 的牌，每张牌旋转 $90$ 度或 $180$ 度或 $270$ 度可得到它的另外三种状态，牌不能翻转，问最后有几张不同的牌。


------------
## 解决问题
看一下 $n$ 的数据范围，$1000$，还蛮小的，考虑把每一种状态压成一个四位数，放到桶里！对于一张 $2\times2$ 的牌，按照四个数的读入顺序依次作为该状态四位数的千、百、十、个位。毕竟最大最大的四位数也只可能是 $9999$，桶没问题。

![](https://cdn.luogu.com.cn/upload/image_hosting/ww1jqnf3.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如图，对于第一个格子，它的四种状态对应的四个四位数分别为：
$$1000a+100b+10c+d$$
$$1000c+100a+10d+b$$
$$1000d+100c+10b+a$$
$$1000b+100d+10a+c$$

换言之，这四个四位数指的是同一张牌。

代码中，如果发现桶里存在该张牌可能达到的任一状态，那就什么都不用做，否则，随便挑一个四位数标记为 $1$ 即可。


------------
## 上代码
```
#include<bits/stdc++.h>
using namespace std;
int t[10010];
int f(int a,int b,int c,int d){//生成四位数 
	return 1000*a+100*b+10*c+d;
}
int main(){
	int n;
	cin>>n;
	int maxn=-1;
	char c1,c2;
	for(int i=1;i<=n;i++){
		char aa,bb,cc,dd;
		cin>>aa>>bb>>cc>>dd;
		int a=int(aa)-'0';//化字符为数字 
		int b=int(bb)-'0';
		int c=int(cc)-'0';
		int d=int(dd)-'0';
		int p1,p2,p3,p4;
		if(i!=n)
			cin>>c1>>c2;
		p1=f(a,b,c,d);//得出四种状态 
		p2=f(c,a,d,b);
		p3=f(d,c,b,a);
		p4=f(b,d,a,c);
		if(!t[p1]&&!t[p2]&&!t[p3]&&!t[p4])//若任何一种状态都未标记，说明这是一种新牌 
			t[p1]=1,maxn=max(maxn,p1);//我挑的第一个四位数标记为1。同时记录一下最大的四位数 
	}
	int ans=0;
	for(int i=1;i<=maxn;i++)
		ans+=t[i];
	cout<<ans;
	return 0;
}
```


---

## 作者：Accepted_Z (赞：1)

[题目链接](https://www.luogu.org/problemnew/show/CF51A)

[我的博客](https://www.luogu.org/blog/hhhh123/)
### 分析
这题是个大模拟，采用边读边处理的方法要高效些。首先把输入定义为 char 型，输入后在转为 int 型。又因为这个方块可以翻转的，所以只要每读入一个就把它的四种状态都标记一下就好了(我为了简便，用的是四维数组，当然还有更优的方法)。

以下为转换图示：

![](https://cdn.luogu.com.cn/upload/pic/56054.png)

### 代码
```cpp
#include <bits/stdc++.h>//推荐使用万能头 
using namespace std;
int n,t,w,x,y,z,f[8][8][8][8];//n与题意相同，t是答案的个数
//wxyz是每次输入的值转为int型，f数组用来标记 
char a,b,c,d,e;//abcd是每次输入的4个数，e用来输入'*' 
int main()
{
    cin>>n;//输入n的值 
    for(int i=1;i<=n;i++)//执行n次循环，边读边处理 
    {
    	cin>>a>>b>>c>>d;//输入4个数的值 
    	if(i!=n) cin>>e>>e;//如果不到结尾，就要输入'*' 
    	w=a-'0';x=b-'0';
    	y=c-'0';z=d-'0';//把char型转为int型 
    	if(f[w][x][y][z]==0)//如果这种情况还没有出现过 
    	{
    		t++;//将答案个数加一 
    		f[w][x][y][z]=1;
    		f[x][z][w][y]=1;
    		f[z][y][x][w]=1;
    		f[y][w][z][x]=1;//标记这种情况的4种不同状态已经存在 
    	}
    }
    cout<<t;//输出答案的个数 
    return 0;//RT
}

```


---

## 作者：codemap (赞：1)

一道代码量较多的简单题

主要就是将每一块分离成四个数字，然后比较，最后输出不同的

这里比较的函数就不说了，代码里会讲，主要说一下如何判断有多少个不同的

做一个两层循环，第一层i从1到n-1，第二层j从i+1到n

若第i个和第j个相同（用比较函数），如果相同就把f[j]（bool数组）置反

这样可以做到每一类只有第一个没有置反，这样统计就很简单了

不说了上我~~冗长而丑陋~~的代码
```c
#include<iostream>
using namespace std;
bool same(int a,int b,int c,int d,int e,int f,int g,int h)//比较函数
{
    if(a==e&&b==f&&c==g&&d==h)//两个一样
        return 1;
    if(a==f&&b==h&&c==e&&d==g)//旋转90°
        return 1;
    if(a==h&&b==g&&c==f&&d==e)//旋转180°
        return 1;
    if(a==g&&b==e&&c==h&&d==f)//旋转270°
        return 1;
    return 0;
}
int main()
{
    int a[1001],b[1001],c[1001],d[1001],t=0,x,y;
    int n,i,j;
    string s;//后面有用
    bool f[1001]={};
    cin>>n;
    for(i=1;i<n;i++)
    {
        cin>>x>>y>>s;//s是分割用的"**"
        a[i]=x/10;//分离，第一行第一个
        b[i]=x%10;//第一行第二个
        c[i]=y/10;//第二行第一个
        d[i]=y%10;//第二行第二个
    }
    //最后一个独立输出
    cin>>x>>y;
    a[n]=x/10;
    b[n]=x%10;
    c[n]=y/10;
    d[n]=y%10;
    for(i=1;i<n;i++)
    {
        for(j=i+1;j<=n;j++)
            if(same(a[i],b[i],c[i],d[i],a[j],b[j],c[j],d[j]))//比较
                f[j]=1;//将后一个置反
    }
    for(i=1;i<=n;i++)
        if(!f[i])//如果没有被置反
            t++;//计数器++
    cout<<t;//输出
    return 0;//结束
}
```

---

