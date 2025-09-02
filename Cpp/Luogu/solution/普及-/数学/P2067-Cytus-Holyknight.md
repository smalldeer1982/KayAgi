# Cytus-Holyknight

## 题目背景

本人最初作

以此纪念伟大的ios、安卓、PSV平台音乐游戏《cytus》

后续将不断更新。

-------------Chapter V-1-------------

话说两位战士整天靠在一起好无聊啊，于是她们打算——玩游戏！（？）

她们就用剑画了一个十字架，然后开始抛石子，好好玩啊（？？？）

两个人每人有一个石子，当她们丢完后，正在自学数学的小蓝大叫：把他们连起来不就是一次函数吗！！

于是乎，她们就连了起来，然后她们开始计算。此时她们发现一个严重的问题——没有草稿纸！（这什么破问题= =）

由于脑补能力太低，她们只好让你来帮帮忙啦~


## 题目描述

给出图形（十字架可以视为x轴和y轴），请计算出函数解析式。


## 说明/提示

切记要分类

数据不需判错

100%的数据，3<=n<=16（够水吧）

没学过函数的自己百度


## 样例 #1

### 输入

```
3
010
111
x1x
```

### 输出

```
y=-1.0000```

# 题解

## 作者：老彩笔 (赞：10)

这题不好处理的地方就在如何判断x轴和y轴的位置，因为情况很多：

1.两个石子（即两个点）的位置没有覆盖坐标轴 


2. 两个石子里有一个覆盖了坐标轴


3.两个石子里有两个覆盖了坐标轴

………

开始我想用两个连续的1来判断：

```cpp
	if(c[i][j]=='1'&&c[i][j-1]=='1')xz=i;
	if(c[i][j]=='1'&&c[i-1][j]=='1')yz=j;
```
然后发现他死了，下面这种情况就不能判断了：

```cpp
0x0
1x1
010
```
然后我改了一下，我想用一个1加一个0来判断：

```cpp
	if(c[i][j]=='1'&&c[i-1][j]=='0')xz=i;
	if(c[i][j]=='1'&&c[i][j-1]=='0')yz=j;
```

然后他又死了，下面这种情况就死了：

```cpp
x000000
x111111
1000000
1000000
1000000
1000000
1000000
```

最后改进了一下，让他即判断左边，还判断右边，就A了：

```cpp
	if(!c1&&c[i][j]=='1'&&c[i-1][j]=='0')xz=i,c1=1;//加上两个bool判断防止重复修改
	if(!c2&&c[i][j]=='1'&&c[i][j-1]=='0')yz=j,c2=1;
	if(!c1&&c[i][j]=='0'&&c[i-1][j]=='1')xz=i-1,c1=1;
	if(!c2&&c[i][j]=='0'&&c[i][j-1]=='1')yz=j-1,c2=1;
```
输出函数的时候还需要特判两个常函数：

1.如果两个点x坐标相等那么输出x=b;

2.如果两个点y坐标相等那么输出y=b;

3.其他输出y=kx+b;

下面是代码，里面有解释：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10-48+ch;ch=getchar();}
	return x*f;
}
const int maxn=105;
char c[maxn][maxn];
int n,xz,yz;//xz是x轴，yz是y轴 
double xl,xr,yl,yr;
bool jd1;//记录是否已经找到了1个点
bool c1,c2;//分别记录是否找到了x轴和y轴 
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cin>>c[i][j];
			if(!c1&&c[i][j]=='1'&&c[i-1][j]=='0')xz=i,c1=1;//x轴 
			if(!c2&&c[i][j]=='1'&&c[i][j-1]=='0')yz=j,c2=1;//y轴 
			if(!c1&&c[i][j]=='0'&&c[i-1][j]=='1')xz=i-1,c1=1;//x轴 
			if(!c2&&c[i][j]=='0'&&c[i][j-1]=='1')yz=j-1,c2=1;//y轴 
			if(c[i][j]=='x')//找到了石子 
			{
				//如果不用一个bool变量记录也可以用数组来保存 
				if(!jd1)//如果没有找到了第一个石子 
				{	
					xl=j;
					yl=i;
					jd1=1;
				}
				else //如果已经找到了第一个石子就记录第二个 
				{
					xr=j;
					yr=i;
				}
			}
		}
	}
	//因为上面只记录了在数组里面的位置
	//这里要处理出实际位置
	//若有不懂大家可以手模一下 
	xl-=yz;
	xr-=yz;
	yl=xz-yl;
	yr=xz-yr;
	//下面是分情况讨论 
	if(xl==xr)
	{
		cout<<"x=";
		printf("%.4lf\n",xl);
		return 0;
	}
	double k,b;
	k=(yr-yl)/(xr-xl);
	cout<<"y=";
	if(k!=0)printf("%.4lfx",k);
	else
	{
		printf("%.4lf\n",yl);
		return 0;
	}
	b=yl-k*xl;
	if(b>0)cout<<'+';//如果b小于0就不用输出+ 
	if(b!=0)printf("%.4lf\n",b);
	//如果b等于0就什么也不做 
	return 0;
 } 
```










---

## 作者：Peter_Z (赞：6)

**2019.9.6 update:**

**1.之前judge函数写错了，没有考虑石头的情况qwq（感谢评论区大佬的提醒）**

**2.修改了一些注释**

**3.美化界面**

------------------------------以下为题解------------------------------

思路：模拟人计算一次函数

公式：

$\large k=\frac{y_1-y_2}{x_1-x_2}$

$b=y_1-x_1*k$

公式的推导很简单，这里就不说了

同时有很多细节需要注意，具体见代码：

```cpp
#include<iostream>
#include<stdio.h>
#include<math.h>
using namespace std;
char pic[18][18];		//输入图形 
int n,x,y;				//n表示图形大小，x和y表示原点的坐标 
inline bool judge(int x,int y) {    //判断(x,y)是否是坐标原点 
    //若这一行或这一列有一个字符不是0，
	//那么这个点一定不是原点，返回false，否则返回true 
    for(int i=1; i<=n; i++)
        if(pic[i][y]!='1' || pic[x][i]!='1')
            return false;
    return true;
}
int main() {
    int c=0;			//当前扫到几个石头 
    int st[2][2];		//两石头坐标(先用数组记录)
    bool f=0;
    cin>>n;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            cin>>pic[i][j];
            if(pic[i][j]=='x') {
                st[c][0]=j,st[c][1]=n-i+1;		//倒序记录两石头坐标 
                c++;
            }
        }
	}
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            if(judge(i,j)) {		//若是原点则记录
                x=j;
                y=n-i+1;
                f=1;
            }
        }
        if(f)    break;
    }
    double x1=st[0][0],y1=st[0][1];
    //用x1,y1,x2,y2更可读,同时用double不容易错(有除法运算且涉及小数) 
    double x2=st[1][0],y2=st[1][1];
    x1=x1-x,y1=y1-y;
    x2=x2-x,y2=y2-y;
    //由于这不是以原点建立的直角坐标系,所以需要调整坐标 
    //分类讨论：
    if(x1==x2) {        //若x坐标相等则以x=b的格式打印
        printf("x=%.4f\n",x1);
    } else if(y1==y2) {    //若y坐标相等则以y=b的格式打印
        printf("y=%.4f\n",y1);
    } else {            //否则以y=kx+b或y=kx的格式打印
        double k,b;
        k=(y1-y2)/(x1-x2);    //公式求k
        b=y1-x1*k;            //公式求b
        printf("y=");
        //注意当b<0时不能打印多余的+，当b=0时不能打印b
        if(b<0) {
            printf("%.4fx%.4f\n",k,b);
        } else if(b>0) {
            printf("%.4fx+%.4f\n",k,b);
        } else {
            printf("%.4fx\n",k);
        }
    }
    return 0;
}
```
最后给大家提供一组数据供测评qwq ：

输入：

```cpp
6
000010
000x10
x00010
111111
000010
000010
```

输出：

y=0.3333x+2.3333


---

## 作者：Blue_wonders (赞：4)

## ACc++代码(附详解)
#### 这个题几个难点已经有人说过了，我跟他基本上一个思路，他是pascal代码，我就发一下我的c++代码
[这个人思路讲的很清楚](https://www.luogu.org/blog/user19540/solution-p2067)

[我的AC代码详情](https://www.luogu.org/recordnew/show/16963013)
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[17][17],n,linea,lineb,cola,colb,x,y,xx,yy,xxx,yyy;
//n是输入;x,y是坐标原点的位置;xx,yy是第一个坐标的位置;xxx,yyy是第二个点的位置;
//lina/b记录横行的1和x的个数;cola/b是纵列的1和x的个数;
int m[2][4];//第一个是横行和纵列的标记,二维 0是记录最大行/列的标记；1是记录最大行,列里面x的个数; 2是记录最大行/列中1和x的个数 
int main(){
	cin>>n;//输入 
	char q;
	for(int i=n;i>=1;i--){//这里从最大的行开始输入，小心 
		for(int j=1;j<=n;j++){
			cin>>q;//字符串输入 
			if(q=='x'){//如果是标记的点，就记录并标记为2 
				a[i][j]=2;
				if(xx==0){//如果第一个点输入过了就输到第二个点 
					xx=j;
					yy=i;
				}
				else{
					xxx=j;
					yyy=i;
				}
			}
			else a[i][j]=q-48;//其他该是啥是啥 
		}
	}
	m[0][1]=n+1;m[0][2]=0;//将最大行的x数设超，总数设最小 
	for(int i=1;i<=n;i++){
		linea=lineb=0;//刷新 
		for(int j=1;j<=n;j++){
			if(a[i][j]==2)lineb++;//记录x的个数++ 
			if(a[i][j]==1)linea++;//记录1的个数++ 
		}
		if(linea+lineb>m[0][2]||(linea+lineb==m[0][2]&&lineb<m[0][1])){//如果发现1或x的总数变多或者总数同样多但是x变少的就进入循环 
			m[0][0]=i;//记录边 
			m[0][1]=lineb;//记录x个数 
			m[0][2]=linea+lineb;//记录总数 
		}
	}
	m[1][1]=n+1;m[1][2]=0;//同上 
	for(int i=1;i<=n;i++){
		cola=colb=0;
		for(int j=1;j<=n;j++){
			if(a[j][i]==2)colb++;
			if(a[j][i]==1)cola++;
		}
		if(cola+colb>m[1][2]||(cola+colb==m[1][2]&&colb<m[0][1])){
			m[1][0]=i;
			m[1][1]=colb;
			m[1][2]=cola+colb;
		}
	}
	y=m[0][0];x=m[1][0];//记录原点的位置(纵坐标对应的是横行，横坐标对应的是竖列 )
	xx-=x;xxx-=x;//x的位置都减去原点的坐标就是x对应坐标轴的坐标 
	yy-=y;yyy-=y;
	double k,b;//定义k和b 
	k=(yyy-yy+0.00)/(xxx-xx+0.00);//求k公式 
	b=yy-k*xx+0.00;	
	if(yy==yyy){//如果纵坐标相等的话 
		cout<<"y="<<yy<<".0000";
		return 0;
	}
	if(xx==xxx){//如果横坐标相等 
		cout<<"x="<<xx<<".0000";
		return 0;
	}
	if(b==0)printf("y=%.4fx",k);//没b就不输出 
	if(b<0)printf("y=%.4fx%.4f",k,b); 
	if(b>0)printf("y=%.4fx+%.4f",k,b);//如果b是正数会省略正好，所以要分开输出 
	return 0;
}

```
感谢大家能看我的题解！~

---

## 作者：zk1431043937 (赞：4)

WA了两次，第三次终于过了。

刚看样例的时候觉得坐标轴是完整的，然而并不是这样。。。（第一次只有60分）

于是我载了一个测试数据发现坐标轴可以不完整。

比如说：

3
0x0
1x1
010
这样的坐标轴不完整但实际上也能判断原点在哪里。

于是我又想了一个办法，统计是否有零，有零的行与列不可能是坐标轴。

但又出了bug（这次是90分），拿样例来说：

3
010
111
x1x
这里第二行和第三行都没有0，但很显然，第二行是x轴。

于是继续改进，统计0且统计1，若该行（或列）没有零，且1的个数最多则为坐标轴。

坐标轴确定，它们的交点即为原点，然后随便取两个x所在位置，通过原点算出这两个x点的坐标，就可以列方程组解出解析式。

```cpp
program p2067;
  var a:array[1..16,1..16]of char;
      i,j,n,x,y,x1,y1,x2,y2,s,t,t1,t2:longint;
      k,b:real;
begin
  readln(n);
  for i:=1 to n do
  begin
    for j:=1 to n do
    read(a[i,j]);
    readln;
  end;
  for i:=1 to n do
  begin
    s:=0;
    t:=0;
    for j:=1 to n do
    begin
      if a[i,j]='0' then inc(s);
      if a[i,j]='1' then inc(t);
    end;
    if (s=0) and (t>t1) then
    begin
      x:=i;
      t1:=t;
    end;
    s:=0;
    t:=0;
    for j:=1 to n do
    begin
      if a[j,i]='0' then inc(s);
      if a[j,i]='1' then inc(t);
    end;
    if (s=0) and (t>t2) then
    begin
      y:=i;
      t2:=t;
    end;
  end;//确定x行是横轴，y列是纵轴。
  s:=0;
  for i:=1 to n do
  begin
    for j:=1 to n do
    if (a[i,j]='x') and (s=0) then
    begin
      inc(s);
      x1:=j-y;
      y1:=x-i;
      a[i,j]:='0';
      break;
    end;
    for j:=1 to n do
    if (a[i,j]='x') and (s=1) then
    begin
      inc(s);
      x2:=j-y;
      y2:=x-i;
      a[i,j]:='0';
      break;
    end;
  end;//确定两坐标。
  if y1=y2 then
  begin
    writeln('y=',y1,'.0000');
    halt;
  end;
  if x1=x2 then
  begin
    writeln('x=',x1,'.0000');
    halt;
  end;
  k:=(y1-y2)/(x1-x2);
  b:=y1-(y1-y2)*x1/(x1-x2);
  if b=0 then writeln('y=',k:0:4,'x');
  if b>0 then writeln('y=',k:0:4,'x+',b:0:4);
  if b<0 then writeln('y=',k:0:4,'x',b:0:4);//以上为分类讨论求解析式。
end.
```

---

## 作者：陈见澍 (赞：3)

首先稍微~~吐槽~~说一下：一次函数是形如 y=kx+b (k≠0) 的函数，而 y=b 只是函数，不是一次函数， x=b 连函数都不是……

### 所以题目就是求两个 "x" 所连成直线的解析式。

所以我们就要求两个点的坐标。但求这两个点的坐标，就要找出原点的坐标。所以本题的第一个坎，就是：

### 1.找到原点
确定原点，就要找到x轴和y轴。

所以我的思路很直观：

只要在同一行找到两个（或以上）“1”，那这个就是x轴；同样，只要在同一列找到两个（或以上）“1”，那这个就是y轴。

如这个样例：
```
3
01x
x10
111
```
x轴就是第三行，y轴就是第二列

它的原点坐标就是(3,2)

（我的数组下标从1开始，即 $a_{1,1}$）

但是这两个个样例给了我一个暴击：

```
3
x11
x00
100
```
```
3
0x0
111
0x0
```

这样根本就求不出原点的横坐标！（因为原点那列只有1个1，甚至没有！）

所以我又加了一个判断：如果横坐标为0（一开始横坐标赋值为0，如果还是0，说明横坐标没变过。），那么就每列搜过去，如果不是在原点纵坐标那一行有一个1或 'x'（或1个以上），那么它就是y轴。若纵坐标为0，同理。

接下来就是第二道坎了：
### 2.求出解析式
可以分为三类：

1. x=b (x1=x2，输出x1)
2. y=b (y1=y2，输出y1)
3. y=kx+b (k≠0)

那如果是第三个怎么求解析式呢？

此处我们设解析式为y=kx+b (k≠0)，

那么把 A(x1,y1) , B(x2,y2) 代入，得：

$\begin{cases}y_1=kx_1+b\\y_2=kx_2+b\end{cases}$

解得

$\begin{cases}k=\dfrac{y_1-y_2}{x_1-x_2}\\b=y_1-\dfrac{y_1-y_2}{x_1-x_2}x_1\end{cases}$

当然，这里已经排除了 $x_1=x_2$ 这种情况（它已经在分类1里面了）。
### 3.输出

一切都是那么的顺利美好。然而我并没有注意到这句话：
#### 常数始终保留四位小数

此为何意？？

原本我以为当 k=1 时要输出 y=x ,结果只有90分。。

当然，那个样例是**y=1.0000x**。。。

那么 k=-1 应该也是同理。

还要注意b=0时不用输出0.0000，并且注意k和b都是四位小数。

下面放上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,i,j,l,ox=0,oy=0,x1,y1,x2,y2,p=0;
	char a[17][17];
	double k,b;
	cin>>n;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			cin>>a[i][j];
			if(a[i][j]=='x'&&p)
			{
				x2=j;
				y2=i;
			}
			if(a[i][j]=='x'&&!p)
			{
				x1=j;
				y1=i;
				p=1;
			}
		}
	}
	//找原点
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			if(a[i][j]=='1')
			{
				if(!ox)
				{
					for(l=1;l<=n;l++)
					{
						if(l!=i&&a[l][j]=='1')//竖着搜1
						{
							ox=j;
							break;
						}
					}
				}
				if(!oy)
				{
					for(l=1;l<=n;l++)
					{
						if(l!=j&&a[i][l]=='1')//横着搜1
						{
							oy=i;
							break;
						}
					}
				}
			}
		}
	}
	if(!ox)
	{
		for(j=1;j<=n;j++)
		{
			for(i=1;i<=n;i++)
			{
				if(i!=oy&&(a[i][j]=='1'||a[i][j]=='x'))
				{
					ox=j;
				}
			}
		}
	}
	if(!oy)
	{
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=n;j++)
			{
				if(j!=ox&&(a[i][j]=='1'||a[i][j]=='x'))
				{
					oy=i;
				}
			}
		}
	}
	x1=x1-ox;x2=x2-ox;
	y1=oy-y1;y2=oy-y2;
//	printf("O(%d,%d)\n",ox,oy);
//	printf("A(%d,%d)\n",x1,y1);
//	printf("B(%d,%d)\n",x2,y2);
	if(x1==x2)
	  printf("x=%.4lf",(double)x1);
	else
	{
		if(y1==y2)
		  printf("y=%.4lf",(double)y1);
		else
		{
			k=(y1-y2)*1.0/(x1-x2);
			b=y1-k*x1;
			printf("y=%.4lfx",k);
			if(b!=0)
			{
				if(b>0)
				  printf("+");
				printf("%.4lf",b);
			}
		}
	}
	return 0;
}
```
（如果有讲错或讲得不好得地方请大家指出，谢谢。）

---

## 作者：HeartBlock_Love (赞：1)

这道题还行，不算太难，只需摸妳即可，但对于我这个才上到全等三角形的蒟蒻，一次函数还是难了一点。

这道题就是求一次函数解析式，这道题的关键就是考虑多种情况。

1、x、y在坐标轴上，并且坐标轴无法判断

2、两个点的x值相等

下面是代码，请好好食用

```
#include <cstdio>
#include <iostream>
double ans1,ans2;
char ans[20][20];
int n,now,x[3],y[3],x1[20],y1[20];

void in() {
	std::cin>>n;
	for(int i=1;i<=n;++i) {
		std::cin>>ans[i];
		for(int j=0;j<n;++j) {
			if(ans[i][j]=='1') {
                if(x1[i]) {
                    y[0]=i;	
				}
                if(y1[j]) {
                	x[0]=j;
				}
                x1[i]++;
				y1[j]++;
            }  
		}
	}
}

void work() {
	for(int i=1;i<=n;++i) {
		for(int j=0;j<n;++j) {
			if(ans[i][j]=='x') 
				y[++now]=y[0]-i;
				x[now]=j-x[0];
			}
		}
}

void pri() {
	if(x1[y[0]]==1) {
	    printf("y=%.4lf",ans2);
		return ;
	}
	if(y1[x[0]]==1) {
	    printf("x=%.4lf",ans1);
		return ;
	}
    if(x[1]==x[2]) {
	    printf("x=%.4lf",x[1]);
		return ;
	}
	ans1=1.0*(y[1]-y[2])/(x[1]-x[2]);
    ans2=(double)y[1]-ans1*x[1];
    if(ans1==0) {
    	printf("y=%.4lf",ans2);
	}
    else {
        printf("y=%.4lfx",ans1);    
        if(ans2==0) {
            return ;	
		}
        if(ans2>0) {
        	printf("+");
		}
        printf("%.4lf",ans2);
    }
}

int main() {
	in ();
	work ();
	pri ();
    return 0;
}
```


---

