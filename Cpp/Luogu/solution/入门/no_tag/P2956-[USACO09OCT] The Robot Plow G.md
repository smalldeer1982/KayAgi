# [USACO09OCT] The Robot Plow G

## 题目描述

农夫约翰购买了一台新的自动耕地机器人，以将自己从日复一日犁地的繁重劳动中解脱出来。这台机器人确实能完成耕地任务，但有一个小缺点：它只能犁出各边长度均为整数的完美矩形地块。

由于约翰的田地中分布着树木和其他障碍物，他需要设定机器人犁耕多个不同的矩形区域，这些区域可能会有重叠。他很好奇，在按照各种耕地指令（每个指令通过给出矩形的左下角和右上角 x、y 坐标来描述）编程后，田地里实际被犁过的方格数量究竟有多少。

和往常一样，田地被划分为若干方格，这些方格的边与 x 轴和 y 轴平行。整块田地的宽度为 $X$ 个方格，高度为 $Y$ 个方格 $1\le X,Y \le 240)$。共有 $I$ 条耕地指令 $(1\le I \le 200)$，每条指令包含四个整数：$Xll、Yll、Xur \text{ 和 } Yur\text{ (}1 \le Xll \le Xur \le X;1 \le Yll \le Yur \le Y）$，分别表示待犁矩形的左下角和右上角坐标。机器人会犁耕区间 $(Xll \dots Xur, Yll \dots Yur)$ 内的所有田地方格——根据不同的理解方式，这个区间可能比初始设想的多一行或一列（当然，具体取决于你如何理解）。

以一块宽 6 格、高 4 格的田地为例。当约翰发出两条耕地指令（如下所示）时，田地的犁耕情况如 `*` 和 `#` 所示（通常犁过的田地看起来相同，这里用 `#` 表示最近犁过的区域）：

```
......             **....             #####. 
......  (1,1)(2,4) **....  (1,3)(5,4) #####. 
......             **....             **.... 
......             **....             **....
```
最终共有 14 个方格被犁过。

得分：25 分

## 说明/提示

正如任务示例中所示

## 样例 #1

### 输入

```
6 4 2 
1 1 2 4 
1 3 5 4 
```

### 输出

```
14 
```

# 题解

## 作者：KesdiaelKen (赞：21)

这一题还是很明显可以用差分来做的。差分的思想如果有意了解可以在网上搜寻资料，在这里简单讲一下，不做详细介绍——用O(1)的时间复杂度来表示O(N)的覆盖操作，具体见程序。

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
using namespace std;
int cf[1010][1010]={0};
int main()
{
    int n,m;
    cin>>n>>m;
    int gs;cin>>gs;
    int a,b,aa,bb;
    for(int i=0;i<gs;i++)
    {
        scanf("%d%d%d%d",&a,&b,&aa,&bb);
        for(int j=a;j<=aa;j++)//每行做一次差分
```
{//设b[i]=a[i]-a[i-1]
```cpp
            cf[j][b]++;
            cf[j][bb+1]--;//前后分别加一，减一，即可代表a的变化
        }
    }
    int sum=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cf[i][j]+=cf[i][j-1];
            if(cf[i][j])sum++;//如果已被犁到，则计数
        }
    }
    printf("%d",sum);
    return 0;
}
```

---

## 作者：little_gift (赞：18)

#貌似没有人写C++的模拟,那我来写一个#

```cpp
#include <cstdio>
using namespace std;
int n,m,k,i,x1,x2,y1,y2,i1,j1,s;
bool b[241][241];
int main()
{
    scanf("%d %d %d",&n,&m,&k); //读入大小以及指令个数
    for (i=1;i<=k;i++)
    {
        scanf("%d %d %d %d",&x1,&y1,&x2,&y2); //读入犁的长方形的坐标(由于题面中说明了x1<x2,y1<y2,所以不用比较).
        for (i1=x1;i1<=x2;i1++)
            for (j1=y1;j1<=y2;j1++) //二重循环,模拟犁田
                if (!b[i1][j1]) //如果当前格子没被犁过
                {
                    s++; //累加计数器
                    b[i1][j1]=1; //作标记
                }
    }
    printf("%d\n",s); //输出格数
}
```

---

## 作者：lumineux (赞：13)

## Pascal的题解好少啊！我来写一篇吧。

------------
### 【题意分析】
# 这题好水呀


- 暴力解决

因为这题数据很小，所以可以直接开数组覆盖，最后累加。很简单的方法，相信连新手也能掌握。

代码奉上

------------
```pascal
var
  a:array[1..240,1..240] of char;
  ans,n,m,p,x1,y1,x2,y2,i,j,k:longint;
begin
  readln(n,m,p);
  for i:=1 to p do
    begin
      readln(x1,y1,x2,y2);
      for j:=x1 to x2 do
        for k:=y1 to y2 do
          if a[j,k]<>'*' then
            a[j,k]:='*';
    end;
  for i:=1 to n do
    for j:=1 to m do
      if a[i,j]='*' then
        inc(ans);
  write(ans);
end.
```

------------
小蒟蒻的题解，大佬勿喷


---

## 作者：宵夜 (赞：10)

**Wa这个题的题解这么少的吗？** 

~~**那我就凑一波热闹吧**~~ 前面dalao的题解完全看不懂啊 我还是写一个简单易懂的题解供各位dalao参考(勿喷)

这道题其实很~~**难**~~简单

大体思路：**把每个被犁过点都标记一遍，最后再统计被标记的点就好了
**


------------
```c

c++代码附上 
#include <bits/stdc++.h> 
//头文件从来只用万能的

using namespace std;

int main(){

int p[1][1]={0},i,j,x,y,q,k,xll,yll,xur,yur,s=0;

//p数组用来标记每一个点的状态，0代表没被犁过，1代表被犁过 
//s作为计数器来计算被犁过的点的数量
//数组开1*1当然是防抄袭标志
	
    cin>>x>>y>>q;
    for(i=1;i<=q;i++){ 
        cin>>xll>>yll>>xur>>yur;
        //边输入边进行操作
        for(j=xll;j<=xur;j++)
			for(k=yll;k<=yur;k++)
				p[j][k]=1;
//把每个点都过一遍，标记被坐标包括在内的点标记一遍
//记住循环的起始条件
	} 
	for(i=1;i<=x;i++){
		for(j=1;j<=y;j++){
			if(p[i][j]==1)	s++;
            //如果这个点被标记了，计数器+1
		}
	}
	cout<<s;
    //完美结束
	return 0;
}
```


------------
是不是很容易哈哈哈 

---

## 作者：Sirius_X (赞：6)

#看题解比较少，顺便来发一个#

##这题比较水，我的做法比较简单，模拟，也相对比较易懂，但是没有什么优化，所以代码可能有点多。大佬勿喷！！！##

##以下的代码仅供大家参考##

```cpp
#include<cstdio>
bool t[250][250];//开个数组，方便记录耕田的情况。
int main(){
    int i,x,y,n,j,s=0,a,b,c,d;
    scanf("%d %d %d",&x,&y,&n);
    while(n--){在线，边读边做。
        scanf("%d %d %d %d",&a,&b,&c,&d);
        for(i=a;i<=c;i++)
            for(j=b;j<=d;j++)
                t[i][j]=1;//把处于在耕田的长方形里的面积，用“1”把全部都记录下来。
    }
    for(i=1;i<=x;i++)
        for(j=1;j<=y;j++)
            if(t[i][j]) s++;//因为是在主函数外开的数组，所以初始值都是0。是一的就s++，把耕过的田的总数给算出来
    printf("%d\n",s);//输出。
    return 0;
}

```

---

## 作者：遥望天空 (赞：5)

排版好难......
------------
```c
#include<iostream>
//比赛中一般不能使用万能头文件
using namespace std;
int main()
{
	char a[1001][1001];
	int n,m,q,w,b[1001],c[1001],d[1001],e[1001];
	cin >> n >> m >> q;
	for(int i = 1;i <= q;i ++)
	cin >> b[i] >> c[i] >> d[i] >> e[i];
	for(int r = 1;r <= q;r ++)
	   for(int i = 1;i <= m;i ++)
	      for(int j = 1;j <= n;j ++)
	        {
	        	if((i >= c[r] && i <= e[r]) && (j >= b[r] && j <= d[r]))
	        	a[i][j] = '_';//用特殊字符代替机器人耕过的方格
		    }
	int as = 0;
	for(int i = 1;i <= m;i ++)
	   for(int j = 1;j <= n;j ++)
	      if(a[i][j] == '_')
	      as ++;//累加方格数
    cout << as;//输出答案，完美结束程序
}
  
```            
------------

说实话这题不简单。
真的，感觉是普及-......

天呐题解发两遍都没过......
真的是

------------
好了
实际这道题是这样的
输入机器人耕地的左下角和右上角的坐标，
求出在范围内被更过的方格数；
我们只需要用一个字符二维数组模拟土地，
将机器人耕过的用特殊字符来代替，
最后累加特殊字符的数量就行了。


---

## 作者：HNFMS__vistonuzi (赞：4)

首先看到这道题，本蒟蒻想了想可否用暴水过。  
一看数据，哎，这么小，果断写了暴力，就过了。  
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int qwe[250][250]={0};//开数组记录犁田情况
	int a,b,c,d,e,f,g,i;
	long long ans=0;//计数器（好像可以不开long long的）
	cin>>a>>b>>c;
	for(i=1;i<=c;i++)
	{
		cin>>d>>e>>f>>g;
		for(int j=d;j<=f;j++)
		for(int k=e;k<=g;k++)
		qwe[j][k]=1;//暴力覆盖
	}
	for(int j=1;j<=a;j++)
	for(int k=1;k<=b;k++)
	if(qwe[j][k]==1)
	ans++;//暴力计数
	cout<<ans;
	return 0;//撒花
}
```

---

## 作者：阿瑞 (赞：3)

【题意分析】

这是一道模拟题，模拟平面直角坐标系上的点是否被访问。则首先建立一个平面直角坐标系(二维数组) p[250][250]，然后根据题意开始输入两点坐标，由循环来完成（x1,y1）到（x2,y2）的数组访问，其中有计数器来记录访问次数，然后输出次数。

感谢阅读，希望题解对你有一定的帮助，以下代码实现。
```c
#include<iostream>
using namespace std;

int x,y,k;//x,y坐标系大小 k访问轮数 
int x1,y1,x2,y2;//每次访问的矩形的两个点 
int p[250][250]={};//坐标系 
int he=0;//计数器 

int main()
{
	cin>>x>>y>>k;
	
	for( int i=1 ; i<=k ; i++ )
	{
		cin>>x1>>y1>>x2>>y2;
		//以下两个循环实现每次矩形的访问 
		for( int j=x1 ; j<=x2 ; j++ )
			for( int l=y1 ; l<=y2 ; l++ )
				if( p[j][l]==0 )//只将没有访问过的点访问 
				{
					p[j][l]++;
					he++;
				}
	}
	
	 
	/*
	测试平面直角坐标系访问情况 
	cout<<endl;
	for( int i=1 ; i<=x ; i++ )
	{
		for( int j=1 ; j<=y ; j++ )
		{
			cout<<p[i][j]<<" ";	
		}
		cout<<endl;
	}
	*/
	
	cout<<he;
	
	return 0;
}
```


---

## 作者：Soledad_S (赞：2)

哇，我把题解翻了一遍，大家都写的暴力膜你，还有两个巨佬写二维树状数组和一维差分的

**竟然没有人用二维差分！**

我打开这道题一看，就是二维差分，怎么才红题，顺手扫了一眼数据范围，我很不厚道地笑了出来

[这里有篇很简短的介绍差分的文章 ~~(推广自己)~~](https://www.cnblogs.com/soledadstar/p/11600711.html)

然后？就没有然后了……

```
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define y1 Sol_y1
#define y2 Sol_y2
inline int read() {
	char ch;
	int bj=1;
	while(!isdigit(ch=getchar()))
		bj=(ch=='-')?-1:1;
	int res=ch^(3<<4);
	while(isdigit(ch=getchar()))
		res=(res<<1)+(res<<3)+(ch^(3<<4));
	return res*bj;
}
void printnum(int x) {
	if(x>9)printnum(x/10);
	putchar(x%10+'0');
}
inline void print(int x,char ch) {
	if(x<0) {
		putchar('-');
		x=-x;
	}
	printnum(x);
	putchar(ch);
}
int n,K,ans,m;
int a[1005][1005];
int f[1005][1005];
int main() {
	n=read();
	m=read();
	K=read();
	int x1,y1,x2,y2;
	for(int i=1; i<=K; i++) {
		x1=read()+1;//加1避免0
		y1=read()+1;
		x2=read()+1;
		y2=read()+1;
		a[x2][y2]++;
		a[x1-1][y2]--;
		a[x2][y1-1]--;
		a[x1-1][y1-1]++;
	}
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++) {
			f[i][j]=f[i-1][j]+f[i][j-1]-f[i-1][j-1]+a[i][j];
			if(f[i][j])ans++;
		}
	print(ans,'\n');
	return 0;
}
```
[这道题同样的也是用这种方法，但是暴力膜你肯定不行咯](https://www.luogu.org/problem/P5542)

---

## 作者：dfydada⚡⚡⚡ (赞：2)

这题很简单,只要记入犁过多少位置就可以了.但是,有些地方会重复犁,可以用bool型判断掉就可以了.

我们可以用在线的方式来写,也可以用离线的方式(结果都一样).这里我用的是在线做法:

输入完x1,y1,x2,y2的坐标后就可以直接用两层循环来把bool型的二维坐标都标记起来,如果这个位置已经被标记过了就可以判断掉不用在继续标记了,因为我们要在标记的同时累加答案sum.如果把标记过的位置又走过的话就不符合题意了.最终输出sum就可以了.

```
#include<bits/stdc++.h>
//#pragma GCC optimize(2)//O2优化
using namespace std;
typedef long long ll;
typedef long double ld;
const int N=3000+10;
ll n,m,z,x1,yy,x2,y2;
ll sum;
bool b[N][N];
ll read()
{
    ll res=0,chr=getchar(),st=1;
    if(chr=='-')
    {
        st=-1;
    }
    while(!isdigit(chr)&&chr!=EOF)
    {
    	chr=getchar();
	}
    while(isdigit(chr))
    {
        res=(res*10)+(chr-'0');
        chr=getchar();
    }
    return res*st;
}
int main()
{
	n=read();
	m=read();
	z=read();
	for(int i=1;i<=z;i++)
	{
		x1=read();//在线做
		yy=read();
		x2=read();
		y2=read();
		for(int j=x1;j<=x2;j++)
		{
			for(int l=yy;l<=y2;l++)
			{
				if(!b[j][l])//这样不会重复犁同一块地
				{
					sum++;//犁过的总数,用变量记入
					b[j][l]=1;//犁过的都标记起来
				}
			}
		}
	}
//	for(int i=1;i<=n;i++)//如果不清楚那些田地被犁了,可以这样输出看看;
//	{
//		for(int j=1;j<=m;j++)
//		{
//			cout<<b[i][j]<<" ";
//		}
//		cout<<endl;
//	}
	cout<<sum;//输出犁过的总数
	return 0;
}

```


---

## 作者：DYM丶剑仙 (赞：1)

我第二次交题解，~~第一次没过~~。
这道题我自己写了个dfs。
~~~~其实我感觉自己瞎写了一个就AC了~~~~
其实不难理解，我就不写注释了，~~懒得写了~~

------------
代码
```c
#include <cstdio>
using namespace std;
int x,y,t,d[1000][1000];
int sx,sy,fx,fy,ans;
void dfs(int x,int y)
{
	if(x >= sx && x <= fx && y >= sy && y <= fy)
	{
		return;
	}
	for(int i = sy;i <= fy;i++)
	{
		for(int j = sx;j <= fx;j++)
		{
			if(d[i][j] == 0)
			{
				ans++;
			}
			d[i][j] = 1;
		}
	}
}
int main()
{
	scanf("%d%d%d",&x,&y,&t);
	for(int i = 1;i <= t;i++)
	{
		scanf("%d%d%d%d",&sx,&sy,&fx,&fy);
		dfs(x,y);
	}
	printf("%d",ans);
	return 0;
}
```


------------

求过，谢谢


---

## 作者：2017gdgzoi999 (赞：1)

## 没有人写树状数组解法那我就来写一下

这道题其实是__巨水模拟__......但是~~为了练练代码能力~~我写了树状数组的解法。

可以看到和普通的树状数组不同，改变和查询的都是二维区间，因此，只要写针对二维区间查询的树状数组即可。

### 二维树状数组的更新区间

和普通树状数组差不多，只是要用两层循环。其余基本相同。

```cpp
void update(int x, int y, int val)
// 将a[x][y]的值增加val
{
    int k;
    
    while (x <= n)
    {
        k = y; // 用个暂时变量存一下
        while (k <= m)
        {
            c[x][k] += val;
            k += lowbit(k);
        }
        x += lowbit(x);
    }
    
    return;
}
```

这题只用把$a[x][y]$的值$+1$，所以省略了参数$val$。


```cpp
void update(int x, int y)
{
    int k;
    
    while (x <= n)
    {
        k = y;
        while (k <= m)
        {
            ++c[x][k];
            k += lowbit(k);
        }
        x += lowbit(x);
    }
    
    return;
}
```

### 二维树状数组查询区间内所有元素的和

也和普通树状数组的查询区间差不多，和更新元素一样，需要两层循环。

以下为查询区间$[1, x][1, y]$的和的函数：

```cpp
int query(int x, int y)
{
    int k, res = 0;
    
    while (x)
    {
        k = y; // 依然用一个变量存
        while (k)
        {
            res += c[x][k];
            k -= lowbit(k);
        }
        x -= lowbit(x);
    }
    
    return res;
}
```

上全部代码：
```cpp
#include <iostream>
#include <cstdio>

#define SIZE 241
#define lowbit(x) (x & (-x))

using namespace std;

int c[SIZE][SIZE], n, m;
bool a[SIZE][SIZE];

void update(int x, int y) // 更新元素
{
    int k;
    
    while (x <= n)
    {
        k = y;
        while (k <= m)
        {
            ++c[x][k];
            k += lowbit(k);
        }
        x += lowbit(x);
    }
    
    return;
}

int query(int x, int y) // 查询区间所有元素的和
{
    int k, res = 0;
    
    while (x)
    {
        k = y;
        while (k)
        {
            res += c[x][k];
            k -= lowbit(k);
        }
        x -= lowbit(x);
    }
    
    return res;
}

int main(void)
{
    int k, x, y, r, c, i, j;
    
    scanf("%d%d%d", &n, &m, &k);
    while (k--)
    {
        scanf("%d%d%d%d", &x, &y, &r, &c);
        for (i = x; i <= r; ++i)
        {
            for (j = y; j <= c; ++j)
            {
                if (!a[i][j])
                {
                    a[i][j] = true;
                    update(i, j);
                }
            }
        }
    }
    
    printf("%d", query(n, m)); // 查询区间[1, n][1, m]内所有元素的总和
    
    return 0;
}
```

---

## 作者：AdzearDisjudge (赞：1)

此题暴水。

核心思想：

每次读入坐标后两重循环走一遍，计数器加一（其实直接用bool就行，但我是直接从P3397改过来的，这两题加上P1003三道题思路一致，稍加改动就能互相使用），最后从头到尾走一遍，计数器不为零（或为true）结果加一。最后输出结果即可。

AC代码：

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
int a[1001][1001]={0},m,n,s,i,j,k,x1,x2,y1,y2;   //a数组可改为bool型
int main()
{
    cin>>n>>s>>m;
    for(k=1;k<=m;++k)
    {
        cin>>x1>>y1>>x2>>y2;
        for(i=x1;i<=x2;++i)
        for(j=y1;j<=y2;++j)
        ++a[i][j];  //a为bool型就改为  a[i][j]=true;
    }
    k=0;
    for(i=1;i<=n;++i)
    for(j=1;j<=s;++j)
    if(a[i][j]!=0) //a为bool型就改为  if(a[i][j])
    ++k;
    cout<<k;
    return 0;
}
```

---

## 作者：cheliang (赞：1)

我看没有人发Pascal，所以来一个吧。

这题很简单，模拟即可，先找出长和宽坐标的最小值，然后双重循环把需要犁的地方做上标记，最后再用双重循环统计出所有犁过的方格。

```cpp
type
  arr=record
        v,z:longint;
      end;
var
 a:array[0..1000,0..1000] of 0..1;
 i,j,m,k,x,y,x1,x2,y1,y2:longint;
procedure p(var a,b:longint);
var t:longint;
begin
 if a<b then exit;
 t:=a;a:=b;b:=t;
end;
begin
 readln(y,x,k);
 fillchar(a,sizeof(a),0);
 for m:=1 to k do
  begin
   readln(x1,y1,x2,y2);
   p(x1,x2);
   p(y1,y2);
   for i:=x1 to x2 do for j:=y1 to y2 do a[j,i]:=1;
  end;
 k:=0;
 for i:=1 to x do for j:=1 to y do if a[i,j]=1 then inc(k);
 writeln(k);
end.
```

---

## 作者：飞翔 (赞：1)

#巨水模拟！

解法1：就是模拟啊，读入的时候双重循环打标记，然后扫描下就可以了。程序？！自己写！

解法2：这种方法是O(N^2)级的。

我们首先看1维的情况。

假如现在机器人犁了[2,5]，而这块（应该是条了）地有6格，那么在[2]上打+1标记，在[6]上打-1标记，最后累加标记即可。

二维的就是1维的推广而已。

详情见[我的博客](http://blog.csdn.net/qq\_31640513/article/details/52689405)

这里附上代码：

```cpp
#include<cstdio>
int f[1010][1010]={0},sum[1010][1010];
int main()
{
    int n,m,k,x1,y1,x2,y2;
    scanf("%d%d%d",&n,&m,&k);
    for (int i=1;i<=k;i++) {
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        for (int j=x1;j<=x2;j++) { f[j][y1]+=1;f[j][y2+1]-=1; }
    }
    for (int i=1;i<=n;i++) {
        int t=0;
        for (int j=1;j<=m;j++) {
            t+=f[i][j];
            sum[i][j]=t;
        }
    }
    int ans=0;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
            if (sum[i][j]!=0) ans++;
    printf("%d",ans);
    return 0;
}
```

---

## 作者：lxz_leo (赞：0)

# 这是一个USACO比较简单的题


------------
**这道题可以不用函数**


------------
~~我嫌不写显示不出我的高大上~~


------------
思路是输入（a1,a2,a3,a4）完了以后一行行检测赋值
```cpp
if(di[i][j]==0)
	{
		sum++;
	}
	di[i][j]=1;
```
如果已经被犁过就跳过如果没有（0）将犁的个数加1将这块地设定为已犁过（1）


------------
最后输出被犁的个数（sum）
### 代码如下:
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
int di[250][250];
int a1/*列*/,a2/*行*/,a3/*列*/,a4/*行*/;
int a,b,c,sum;
 void readf()//定义一个输入加返回 
{
	scanf("%d%d%d",&a,&b,&c);//输入三个变量 
	for(int i=1;i<=c;i++)//循环输入 
	{
		scanf("%d%d",&a1,&a2);
		scanf("%d%d",&a3,&a4);
		for(int i=a2;i<=a4;i++)
		for(int j=a1;j<=a3;j++)//计算赋值 
		{
			if(di[i][j]==0)
			{
				sum++;
			}
			di[i][j]=1;
		}
	}
}
int main()
{
readf();
printf("%d",sum);//输出 
return 0;
}

```
一个输入,一个计算,一个输出
简单吧
#### 附加跳回题目的链接：
[P2956](https://www.luogu.org/problem/P2956)

---

## 作者：Sicanus (赞：0)

晃一眼感觉本题挺有水平，再看一眼就发现本题是个~~巨水模拟题~~

### 解析
由于$ 240 \times 240 $的数据实在是~~太水~~，所以本题不需要高级方法，用`bool`数组存地块，再遍历每一次犁地的区间，改变对应地格的真假性，最后大遍历一次来计数就可以了。

### 代码
**写在前面：**各项`函数` `结构体` `变量` `数组`的名字都写得很清楚了，会洋文的大约都能读懂吧。新手看不懂本程序中的`register`关键字的话可以将其忽略，本蒟蒻只是习惯性卡常而已。

代码如下：

```cpp
#include <iostream>
using namespace std;

bool isPlowed[242][242] = {false};

struct Point
{
    int x;
    int y;
};

struct Square
{
    Point startPoint;
    Point endPoint;
};

inline void plow(Square s)
{
    for (register int i = s.startPoint.x; i <= s.endPoint.x; i++)
    {
        for (register int j = s.startPoint.y; j <= s.endPoint.y; j++)
        {
            isPlowed[i][j] = true;
        }
    }
}

// 这里的x, y代表的是农场宽高而不是坐标
inline int countPlowedFields(int x, int y)
{
    register int ans = 0;
    for (register int i = 1; i <= x; i++)
    {
        for (register int j = 1; j <= y; j++)
        {
            if (isPlowed[i][j] == true)
            {
                ans++;
            }
        }
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(0);	// 标准输入小卡常
    int x, y, n;
    cin >> x >> y >> n;
    Square s;
    for (register int i = 1; i <= n; i++)
    {
        cin >> s.startPoint.x >> s.startPoint.y >> s.endPoint.x >> s.endPoint.y;
        plow(s);
    }
    cout << countPlowedFields(x, y);
    return 0;
}
```

**注：**~~ANSI码风有益于身心健康~~，勿喷代码风格。

---

