# Maximum in Table

## 题目描述

给定一个 $N$ * $N$ 的矩阵，令 $a_{i,j}$ 为矩阵中第i行第j列的元素，则有：
1. $a_{k,1}=a_{1,k}=1(1≤k≤N)$ 
2. $a_{i,j}=a_{i-1,j}+a_{i,j-1}(2≤i,j≤N)$ 
现请求出该矩阵中最大元素的值。

## 样例 #1

### 输入

```
1
```

### 输出

```
1```

## 样例 #2

### 输入

```
5
```

### 输出

```
70```

# 题解

## 作者：sxtm12138 (赞：6)

本题是一道不折不扣的裸题。看到这道题目，大家一定会想起另一道如出一辙的题：在一个M*N的迷宫内，只允许向右走或向上走，求出从左下角走到右上角共有几种方案。

这道题的正解思路显然是动规：由于只允许向右走或向上走，所以走到点(i,j)的方案数f[i][j]=f[i][j-1]+f[i-1][j]，从而得出走到点(n,n)的方案数。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{int n,a[11][11];//本题数据范围较小，不必开太大
 cin>>n;//读入N的值
 for(int i=1;i<=n;i++) a[1][i]=1,a[i][1]=1;//初始化
 for(int i=2;i<=n;i++)
   for(int j=2;j<=n;j++) a[i][j]=a[i-1][j]+a[i][j-1];
   //通过状态转移方程求方案数
 cout<<a[n][n];//输出点(n,n)的方案数
 return 0;
}

```

同时我还想到了另一种方法，从点(1,1)走到(n,n),需要向上走(n-1)步，向右走(n-1)步，总共(2n-2)步。而哪几步向上走，哪几步向右走是不确定的，在(2n-2)步中选取(n-1)步向右走，其他几步向上走，故总方案数为：
###  n……(2n-2)/(n-1)……*1

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{long long int n,k=1,t=1;//由于要算阶乘所以开大点，k为(n-1)……*1的值，t为n……(2n-2)的值
 cin>>n;//读入N的值
 for(int i=1;i<=n-1;i++)k*=i,t*=2*n-i-1;//本题数据范围较小，无需计算最小公约数约分
 cout<<t/k;//输出总方案数n……(2n-2)/(n-1)……*1
 return 0;
}
```

---

## 作者：打表大蒟蒻 (赞：5)

看了看题解，发现还没有用递归解的，我便来补一发。

先介绍一下递归吧。如果一个函数直接或间接地调用它自己，就叫做递归。递归需要终止条件，如果没有终止条件，那就恭喜你，显示器上会出现一大片瓦蓝瓦蓝的TLE，然后爆零。在这里，被调用的函数中的参数一定是趋向终止条件的（这不废话吗）。实际上递归是要写出表达式的,找到递归公式。此题就是一道递归的练手好题。

递归公式不必说了，题目中有，所以，递归函数的终止条件是if(n==1) 就返回1，其他情况下返回f(n-1,m)+f(n,m-1)；

代码（比别人的简洁的很多）
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm> //打死不用万能库
using namespace std;
int f(int n,int m)  //递归函数的定义（我写了n和m，实际上可以只用n）
{
	if(n==1||m==1) return 1;  //终止条件
	return f(n-1,m)+f(n,m-1);  //状态转移方程
}
int main ()
{
    int n;    
    cin>>n;  //输入
    cout<<f(n,n)<<endl; //输出
    return 0;
}
```


---

## 作者：ShineEternal (赞：4)

此题相当于告诉你递推公式的递推或说明了状态转移方程的动态规划。
```cpp
#include<cstdio>
using namespace std;
int a[15][15];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        a[i][1]=a[1][i]=1;//初始化
    }
    for(int i=2;i<=n;i++)
    {
        for(int j=2;j<=n;j++)
        {
            a[i][j]=a[i-1][j]+a[i][j-1];//跟着题目走，没错的
        }
    }
    printf("%d",a[n][n]);//很显然，累加的次数越多数越大，那自然就是右下角喽
    return 0;
}
```

---

## 作者：封禁用户 (赞：3)

我只是想说一句，这道题求的数列有一个神奇的通项公式。（似乎没有人知道）

# $f(x)=\frac{ (2*x)! }{(x!)^{2}} $

所以我们可以打出这样一个代码：

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
    long long /*a[]={1, 2, 6, 20, 70, 252, 924, 3432, 12870, 48620, 184756, 705432, 2704156, 10400600, 40116600, 155117520, 601080390, 2333606220, 9075135300, 35345263800, 137846528820, 538257874440, 2104098963720, 8233430727600, 32247603683100, 126410606437752, 495918532948104, 1946939425648112},*/;
    long long n,a1=1,a2;//打表勿看
    cin>>n;
    for(int i=1;i<=2*n;i++)
    {
        a1*=i;
        if(i==n) a2=a1;
    }
    //cout<<a[i]<<endl;
    cout<<a1/(a2*a2)<<endl;
    return 0;
}
```
如果要证明一下，也是可以的。

把要我们算的二维数组图顺时针转45度，你就会发现：似乎用牛顿二项式就证明好了。

---

## 作者：CyaNeko (赞：1)

哇，这里的大佬发了这么多的C++题解，本蒟蒻来发一个pascal题解吧  
解法就不用说了吧，题目写的清清楚楚......  
奉上代码
```pascal
var i,j,m,n,s,x:longint;
    a:array[1..10,1..10]of int64;//定义
begin
    read(n);//输入
    for i:=1 to n do
    begin
        a[1,i]:=1;
        a[i,1]:=1;
    end;//初始化
    for i:=2 to n do
        for j:=2 to n do
            a[i,j]:=a[i,j-1]+a[i-1,j];//动归
    write(a[n,n]);//输出结果
end.

```


---

## 作者：蔡俊黠 (赞：0)

为了掌握动态规划从题库里按难度升序来一题一题刷hhh...
这是一道很明显的累加题，当前【i,j】的值等于左上【i-1,j】的值加左边【i,j-1】的值，因为n<=10所以时间复杂度为n方的代码也可以秒过

**代码：**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[11][11],anss;
int main()
{
	cin>>n;
	for (int i=1;i<=n;i++)
	  for (int j=1;j<=n;j++)
	    {
	    	if (i==1||j==1) a[i][j]=1; //初始化边界 
	    	else a[i][j]=a[i-1][j]+a[i][j-1]; //转移方程 
	    	anss=max(anss,a[i][j]); //找最大值 
	    }
	cout<<anss<<endl;
	return 0;
}
```


---

## 作者：艾恩葛朗特 (赞：0)

## 状态转移方程都给你了，再没有做出来...
~~滑稽~~

第1步可以理解为将第一行和第一列赋值为1，即：
```
	for (int i=1;i<=n;i++)
	a[i][1]=1;
	for (int i=1;i<=n;i++)
	a[1][i]=1;
```
第2步就是"状态转移方程",即：
```
	for (int i=2;i<=n;i++)
	for (int j=2;j<=n;j++)
	a[i][j]=a[i-1][j]+a[i][j-1];
	pr(a[n][n]);
```
输出是“最大的”，其实稍加思考，由于第n行第n列所加的数最多，自然最大，即：
```
pr(a[n][n]);//本人加了快输，可以理解为printf("%d",a[n][n])
```
整体代码如下：
```
#include<cstdio>
#include<string>
using namespace std;

int n,a[15][15];

inline int read()//快读
{
	int x = 0, f = 1;
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar())
	if (ch == '-') f = -1;
	for (; isdigit(ch); ch = getchar())
	x = x * 10 + ch - '0';
	return x * f;
}

inline void pr(int a){//快输
    if (a){
        pr(a/10); putchar(a%10+'0');
    }
}

int main()
{
	n=read();//可替换为scanf("%d",&n);
	for (int i=1;i<=n;i++)
	a[i][1]=1;
	for (int i=1;i<=n;i++)
	a[1][i]=1;
	for (int i=2;i<=n;i++)
	for (int j=2;j<=n;j++)
	a[i][j]=a[i-1][j]+a[i][j-1];
	pr(a[n][n]);//可替换为printf("%d",a[n][n]);
	return 0;
}
```

---

## 作者：土川崇贺 (赞：0)

		最短路径数标数法，最后输出最短路径总数。
```
#include<bits/stdc++.h>//万能头文件
using namespace std;
int main()
{
    int n;
    cin>>n;
    int a[n][n];
    for(int i=0;i<n;i++)
    {
    	a[0][i]=1;
    	a[i][0]=1;
	}
	for(int i=1;i<n;i++)
	{
		for(int j=1;j<n;j++)
		{
   			a[i][j]=a[i-1][j]+a[i][j-1];
		}
	}
	cout<<a[n-1][n-1];
	return 0;//程序结束
}

```

---

## 作者：不到前10不改名 (赞：0)

//什么dp？？这就是个水递归（还就10）
```
#include<stdio.h>
int srx[101][101],n,i;
int lgx(int x,int y)
{
    if(x==1||y==1)//双重边界值
    return 1;//边界值赋为1
    return (srx[x][y]=lgx(x-1,y)+lgx(x,y-1));//这里包含了一个记忆化，不过数据水，也没什么用
}
int main()
{
    scanf("%d",&n);
    printf("%d",lgx(n,n));//srx【n】【n】就是lgx（n,n）的值
    return 0;
}
```
//所谓的dp算法
```
#include<stdio.h>
int srx[100][100],n,i,j;
int main()
{
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {srx[i][1]=1;
    srx[1][i]=1;}//处理边界原值
    for(i=2;i<=n;i++)//为1的已经处理掉了，就从2开始
    for(j=2;j<=n;j++)
    srx[i][j]=srx[i-1][j]+srx[i][j-1];//所谓的动态转移方程式233...
    printf("%d",srx[n][n]);
    return 0;
}
//qwq
```

---

## 作者：该起什么名字 (赞：0)

由于本题数据范围很小（n≤10），所以我们可以先处理一下n=10的情况。   
~~如果你像我一样画了图找规律的话，~~最大的数一定是在编号为（n，n）的格子上。
代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[20][20];
void runn()//先处理
{
	for(int i=1;i<=10;i++)
	{
		a[i][1]=1;
		a[1][i]=1;
	}//依题意，第一行和第一列全初始化为1
	for(int i=2;i<=10;i++)
		for(int j=2;j<=10;j++)
			a[i][j]=a[i-1][j]+a[i][j-1];//求出每个格子里的数值
}
int main()
{
	std::ios::sync_with_stdio(false);
	int n;
	cin>>n;
	runn();
	cout<<a[n][n]<<endl;//输出第n行第n列中的数值
	return 0;
}
```

---

## 作者：开心的猪 (赞：0)

其实。。。此题的数据范围如此之水，以至于成了洛谷不多的打表神题中的一员。。不仅可以打表，打表用的数据还可以自己手算。。。

以下是打表代码：

```
#include<bits/stdc++.h>

using namespace std;

int main()
{
	int a;
	scanf("%d", &a);
	if(a==1)
	{
		printf("1");
	}
	else if(a==2)
	{
		printf("2");
	}
	else if(a==3)
	{
		printf("6");
	}
	else if(a==4)
	{
		printf("20");
	}
	else if(a==5)
	{
		printf("70");
	}
	else if(a==6)
	{
		printf("252");
	}
	else if(a==7)
	{
		printf("924");
	}
	else if(a==8)
	{
		printf("3432");
	}
	else if(a==9)
	{
		printf("12870");
	}
	else if(a==10)
	{
		printf("48620");
	}
	return 0;
}
```
但是，这道题还有另一个解法。
经过细腻的观察，可以发现，矩阵右上方的数字永远是最大的那个，并且如果矩阵大小为n*n，那么最大的那个数就是（2n）×(2n-1)×(2n-2)×...×(n+1)÷n÷(n-1)÷(n-2)÷...÷2÷1.

这个解法可以实现时间复杂度为O（n）的算法（上面的那个是O（1）——只要如果数据范围扩大到100你能算完这些数就行了。。。当然，如果数据范围扩大到100，这个解法好像需要高精度。）

由于这样的思路实现起来如此简单，同时为了防止抄袭，就不贴代码了。

---

