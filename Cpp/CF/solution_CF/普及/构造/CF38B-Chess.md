# Chess

## 题目描述

在一个大小8×8的国际象棋的棋盘有车和马两个棋子，保证一个棋子无法吃掉另一个。
    请把另一个马放在棋盘上,使得三个棋子都无法吃掉另一个。棋子只能放在一个空的地方。

## 样例 #1

### 输入

```
a1
b2
```

### 输出

```
44
```

## 样例 #2

### 输入

```
a8
d4
```

### 输出

```
38
```

# 题解

## 作者：hensier (赞：3)

关于$Chess$的题目真是越来越多，日新月异。最经典的莫过于$8$皇后，乃至$n$皇后，而本题也非常值得练习（~~居然是黄题难度~~）。

话不多说，我们先来分析一下样例$1$：

![](https://cdn.luogu.com.cn/upload/image_hosting/5pxlwbvy.png)

对于样例$1$，我们先将车放在$a1$，把马放在$b2$。根据上图，我们可以发现，车控制着它所在的行和列（除非中间有棋子阻挡，事实上任何车都是如此）。而在本题中，如果车和马位于同行或同列，就直接输出$0$并退出程序。而马则能“走日”，因此它可以控制$8$个格子（除非超出棋盘边界）。但是，由于第三个放置的棋子为马，因此对于马吃马的现象就不需考虑，而对于马吃车的情况还需要注意——图中用橙色的$X$表示（这里马不能位于$b3,c2$，否则会有$Nxa1$）

样例$2$的图如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/52um9vy5.png)

对于样例$2$，我们放置棋子之后，用上述的符号表示占领情况——车依然占领它所在的行、列，而马这次把$8$个格子都占领了。我们可以发现，$b6,c7$是不可以放置马的，因为这样就会有$Nxa8$。

对于程序的思路，我们先设置一个马的走向常量，即马每一次的走法可以是：（用$(a,b)$表示向上$a$单位，向右$b$单位）

$(-2,-1),(-1,-2),(-2,1),(-1,2),(1,-2),(2,-1),(2,1),(1,2)$

简单来说，就是马可以向上$±1$，向右$±2$或者向上$±2$，向右$±1$。还需注意的是，国际象棋中没有“蹩马腿”一说，因此这大大简化了操作难度。

而输入之后，我们可以直接进行如下基本判断：

①如果马和车位于同行或者同列，输出0并直接退出程序

②如果车所在格子被马控制，输出0并直接退出程序

有了①的特判，就不可能出现“挡子”的现象——除非新加入的马被车所控制。

该题对于马的位置的枚举，可以暴力$[a,h],[1,8]$枚举，因为这样时间复杂度也不高。当然，在循环过程中，只要出现与车同行同列就直接用$continue$语句直接跳过该次循环。

我们可以设置一个$bool$二维数组来保存对应位置是否可以放马，最后再进行统计。

等了好久，你们最喜欢的$AC$代码终于来了：

```cpp
#include<cstdio>
int N[2][8]={{-1,-2,-2,-1,1,2,2,1},{-2,-1,1,2,-2,-1,1,2}},ry,ny,rx,nx,i,j,k,s;
//rx,ry保存车的坐标，nx,ny为马的坐标，N[][]为马的位置增量坐标，i、j、k为循环使用，s保存可放马的格子数量
bool a[9][9];//bool数组的用途，上面已经说过
int main()
{
    scanf("%c%d\n%c%d",&rx,&ry,&nx,&ny);//把整型变量直接当字符输入（强制转换）
    rx-='a'-1;
    nx-='a'-1;//把输进来的字符进行操作，让它变成整型（例如：a-->1，h-->8）
    if(rx==nx||ry==ny)
    {
        printf("0");
        return 0;
    }//特判——上文已提及
    for(i=1;i<9;i++)
    {
        for(j=1;j<9;j++)
        {
            if((i==rx&&j==ry)||(i==nx&&j==ny))continue;
            if(i==rx||j==ry)continue;//特判——上文已提及
            a[i][j]=1;//初始来说，这个坐标的bool值为真
            for(k=0;k<8;k++)//对马的占领格子进行讨论
            {
                if(i+N[0][k]<1||i+N[0][k]>8||j+N[1][k]<1||j+N[1][k]>8)continue;//超出边界就跳过该次循环
                if(i+N[0][k]==rx&&j+N[1][k]==ry)//如果能够使得Nx{rx}{ry}，就直接标记为0，跳过该次循环（国象大佬勿喷）
                {
                    a[i][j]=0;
                    break;
                }
                if(i+N[0][k]==nx&&j+N[1][k]==ny)//同理可得，如果能马吃马，就标记为0
                {
                    a[i][j]=0;
                    break;
                }
            }
        }
    }
    for(i=1;i<9;i++)for(j=1;j<9;j++)if(a[i][j])s++;//计算出值为真的数量
    printf("%d",s);//完美输出
}
```

---

## 作者：Tenshi (赞：3)

[CF原题传送门](https://codeforces.com/problemset/problem/38/B)

[洛谷题面传送门](https://www.luogu.com.cn/problem/CF38B)

[我的博客传送门](https://www.luogu.com.cn/blog/HinanawiTenshi/)

#  分析：
 
 考虑到枚举放置马的位置需要很麻烦地判断是否会攻击到其他两个棋子，我们可以从另一个角度考察问题：**放置的马在哪里可以吃到车，那么就可以将这样的位置也看作为车的控制点。**

这样一来，就只需要将车，以及第一个马的控制点标记上就可以了。
（值得注意的是，车马本身的位置也是一个控制点）

用方向数组控制一下~~走位~~代码会清晰qwq：
```cpp
int dx[]={-2,-2,-1,-1, 1, 1, 2, 2};
int dy[]={-1, 1,-2, 2,-2, 2,-1, 1};
```
**下面就是核心了（标记控制点）：**

```cpp
//车 
	mp[x1][y1]=true;
	for(int i=1;i<=8;i++)
		mp[x1][i]=mp[i][y1]=true;
		
	for(int i=0;i<8;i++){
		int kx1=x1+dx[i];
		int ky1=y1+dy[i];
		if(kx1<1||kx1>8||ky1<1||ky1>8)continue;//如果越界就继续枚举方向
		
		mp[kx1][ky1]=true;
	}
	
	//马 
	mp[x2][y2]=true;
	for(int i=0;i<8;i++){
		int kx2=x2+dx[i];
		int ky2=y2+dy[i];
		if(kx2<1||kx2>8||ky2<1||ky2>8)continue;//如果越界就继续枚举方向
		
		mp[kx2][ky2]=true;
	} 
	
```
最后统计一下答案就结束了qwq

### 完整code：
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
bool mp[10][10];
int dx[]={-2,-2,-1,-1, 1, 1, 2, 2};
int dy[]={-1, 1,-2, 2,-2, 2,-1, 1};
int main(){
	char ch1,ch2;
	int y1,y2;
	cin>>ch1>>y1;
	cin>>ch2>>y2;
	
	int x1,x2;
	x1=ch1-'a'+1;
	x2=ch2-'a'+1;
	
	//车 
	mp[x1][y1]=true;
	for(int i=1;i<=8;i++)
		mp[x1][i]=mp[i][y1]=true;
		
	for(int i=0;i<8;i++){
		int kx1=x1+dx[i];
		int ky1=y1+dy[i];
		if(kx1<1||kx1>8||ky1<1||ky1>8)continue;
		
		mp[kx1][ky1]=true;
	}
	
	//马 
	mp[x2][y2]=true;
	for(int i=0;i<8;i++){
		int kx2=x2+dx[i];
		int ky2=y2+dy[i];
		if(kx2<1||kx2>8||ky2<1||ky2>8)continue;
		
		mp[kx2][ky2]=true;
	} 
	
	int res=0;
	for(int i=1;i<=8;i++)
		for(int j=1;j<=8;j++)
			if(!mp[i][j]) res++;
			
	cout<<res;
	return 0;
}
```


---

## 作者：CrTsIr400 (赞：3)

#### ~~超长题解预警信号~~
## 此题正解：循环，非暴力（8 * 8）
## 循环枚举一下每个点
## 看看是否吃到别的点或者是被吃
## 如果两个都不是的话，直接sum++
## 下面请看代码：
### 1.输入
### 输入简单，直接`getchar`就好。
### 代码：

```cpp
char c=getchar();
pos1x=c-'a'+1;
c=getchar();
pos1y=c-'0';
getchar();
c=getchar();
pos2x=c-'a'+1;
c=getchar();
pos2y=c-'0';
```

### 2.车的位置
### ~~暴力出奇迹~~模拟
### 代码：

```cpp
void car()
{
	int x,y;
	x=pos1x,y=pos1y;
	mark(x,y);
	while(x>=1)x--,mark(x,y);	
	x=pos1x,y=pos1y;
	while(x<=8)x++,mark(x,y);	
	x=pos1x,y=pos1y;
	while(y>=1)y--,mark(x,y);	
	x=pos1x,y=pos1y;
	while(y<=8)y++,mark(x,y);
}
```

### 3.马的位置
### 判断一下即可（标记位置的时候。）
### 标记马周围8个格子
### 代码：

```cpp
void horse()
{
	int x=pos2x,y=pos2y;
	mark(x,y);
	mark(x-1,y-2);
	mark(x-1,y+2);
	mark(x-2,y-1);
	mark(x-2,y+1);
	mark(x+1,y-2);
	mark(x+1,y+2);
	mark(x+2,y-1);
	mark(x+2,y+1);
}
```

### 4.~~重头戏~~骑士的位置
### 和马的位置判断代码一模一样，只是坐标变了
### 具体看代码：

```cpp
void kni()
{
	int x=pos1x,y=pos1y;
	mark(x-1,y-2);
	mark(x-1,y+2);
	mark(x-2,y-1);
	mark(x-2,y+1);
	mark(x+1,y-2);
	mark(x+1,y+2);
	mark(x+2,y-1);
	mark(x+2,y+1);
}
```

### 5.~~真正的重头戏~~能否放置的~~伪dfs~~
### 判断即可（每个位置看看是否为0）
### ~~不给代码（逃~~


### 6.~~没了~~其实还有输出
### 直接输出sum


## 7.完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
bool a[9][9];int pos1x,pos1y,pos2x,pos2y,sum;
void mark(int x,int y)
{
	if(x>=1&&y>=1&&x<=8&&y<=8)
	a[x][y]=1;
}
void car()
{
	int x,y;
	x=pos1x,y=pos1y;
	mark(x,y);
	while(x>=1)x--,mark(x,y);	
	x=pos1x,y=pos1y;
	while(x<=8)x++,mark(x,y);	
	x=pos1x,y=pos1y;
	while(y>=1)y--,mark(x,y);	
	x=pos1x,y=pos1y;
	while(y<=8)y++,mark(x,y);
}
void horse()
{
	int x=pos2x,y=pos2y;
	mark(x,y);
	mark(x-1,y-2);
	mark(x-1,y+2);
	mark(x-2,y-1);
	mark(x-2,y+1);
	mark(x+1,y-2);
	mark(x+1,y+2);
	mark(x+2,y-1);
	mark(x+2,y+1);
}
void kni()
{
	int x=pos1x,y=pos1y;
	mark(x-1,y-2);
	mark(x-1,y+2);
	mark(x-2,y-1);
	mark(x-2,y+1);
	mark(x+1,y-2);
	mark(x+1,y+2);
	mark(x+2,y-1);
	mark(x+2,y+1);
}
void dfs()
{
	for(int i=1;i<=8;i++)
	for(int j=1;j<=8;j++)
	if(a[i][j]==0)sum++;
} 
void input()
{
	char c=getchar();
	pos1x=c-'a'+1;
	c=getchar();
	pos1y=c-'0';
	getchar();
	c=getchar();
	pos2x=c-'a'+1;
	c=getchar();
	pos2y=c-'0';
	car();
	horse();
	kni();
	dfs();
	printf("%d",sum);
}
int main()
{
	input();
	return 0;
}
```
## 完结撒花qwq

---

## 作者：666DHG (赞：2)

- ### [Blog](https://666DHG.github.io/)

$\texttt{极小的数据范围}+\texttt{本人十分弱}+\texttt{简单易懂的题意}=\texttt{暴力}$

思路：

标记不可以放的位置，再最后扫一遍就是答案了

代码与解释如下:

```cpp
#include <bits/stdc++.h>
using namespace std;

char k;
bool cannot[10][10];
int x,y,ans,nx,ny,dx[8]={-2,-1,1,2,2,1,-1,-2},dy[8]={-1,-2,-2,-1,1,2,2,1};

int main()
  {
  	//读入车 
	cin>>k>>y;
  	x=k-'a'+1;
  	for (int i=1;i<=8;i++) cannot[x][i]=true; //把它所在的那一行全部标记 
  	for (int i=1;i<=8;i++) cannot[i][y]=true; //把它所在的那一列全部标记 
  	for (int i=0;i<8;i++) //（注释1） 
  	  {
  	  	nx=x+dx[i];
  	  	ny=y+dy[i];
  	  	if (nx>=1&&ny>=1&&nx<=8&&ny<=8) cannot[nx][ny]=true;
	  }
	//读入马
  	cin>>k>>y;
  	x=k-'a'+1;
  	for (int i=0;i<8;i++) //标记马的8个方位
  	  {
  	  	nx=x+dx[i];
  	  	ny=y+dy[i];
  	  	if (nx>=1&&ny>=1&&nx<=8&&ny<=8) cannot[nx][ny]=true; //越界判断 
	  }
	for (int i=1;i<=8;i++) for (int j=1;j<=8;j++) if (!cannot[i][j]) ans++; //假如没有被标记就说明可以放 
	cout<<ans-1; //（注释2）
	return 0;
  }
```

注释1：

因为我们需要判断：

- 固定车$\text{ }\textsf{VS}\text{ }$固定马（不用，因为题目已经保证了不会出现这种情况）

- 固定车$\text{ }\textsf{VS}\text{ }$放置马 

- 固定马$\text{ }\textsf{VS}\text{ }$放置马（已经解决）

那么我们该如何判断固定车$\text{ }\textsf{VS}\text{ }$放置马呢

让我们**把固定车当作马来走**，并把它能走到的地方做个标记，即

![](https://cdn.luogu.com.cn/upload/image_hosting/zp8ei9ss.png)

如果把放置马放在被标记的地方，那么固定车就会被它吃掉，所以标记这里为不可放置

这其实**跟判断马的方式是一样的**

注释2：

让我们看回固定马$\text{ }\textsf{VS}\text{ }$放置马的这段代码

```cpp
cin>>k>>y;
x=k-'a'+1;
for (int i=0;i<8;i++)
  {
    nx=x+dx[i];
    ny=y+dy[i];
    if (nx>=1&&ny>=1&&nx<=8&&ny<=8) cannot[nx][ny]=true;
  }
```

是不是少了点什么？

没错，就是因为我们**只标记了固定马能走到的8个点**，却**没有标记固定马本身的位置**，所以下面这样也是对的

```cpp
cin>>k>>y;
x=k-'a'+1;
cannot[x][y]=true;

//...

cout<<ans;
```

~~感觉挺简单的，连编译器都没跑就一次AC了~~

---

## 作者：infinities (赞：2)

这题纯粹就是个暴力的~~好~~题，因为数据不大，就让我们可以使用暴力做法。

思路：

1.输入行列之后处理为数字

2.再暴力枚举每个点

3.判断马在这个点上能否吃到别人或被吃

4.如果为false，计数器加一

5.最后输出总数

6.然后……然后没有然后了。


-----------------------------分割线-----------------------------


这里列几个需要略微注意的点：

这题其实不难，看懂题就能做。

要注意车所在的行和列是不能放马的。

枚举一下每个点的横纵坐标加十几个判断就行。

行和列对应不对应并不重要,即x,y,x1,y3,x2,y2可以一起混淆。

CODE:
```cpp
#include<bits/stdc++.h>//不包含所有库的万能头
using namespace std;
int sz(char a){//一些处理（楼上和我好像一样？！）
         if(a=='a')return 1;
         //如果y0或yo为‘a’，返回1
    else if(a=='b')return 2;//以下都和上面同理
    else if(a=='c')return 3;
    else if(a=='d')return 4;
    else if(a=='e')return 5;
    else if(a=='f')return 6;
    else if(a=='g')return 7;
    else if(a=='h')return 8;//一直同理
    //return 0;
}
int x1,x2,y3,y2,ans;
//不知道为什么我一用y1做坐标就编译出错，只好改用y3了，造成不便敬请谅解
//其中y2,y3是经处理的坐标的一部分（我也不知道它是行还是列，不好意思）
int main(){
    char yo,y0;//最初的坐标的一部分
    cin>>yo>>x1>>y0>>x2;//输入
    y3=sz(yo);
    y2=sz(y0);//处理一下，变成数字好判断
    for(int x=1;x<=8;x++){
        for(int y=1;y<=8;y++){//开始暴力枚举每个点
            if(x==x1&&y==y3)continue;else
            if(x==x2&&y==y2)continue;else//保证马的所在地为空
            if(x-2==x1&&y-1==y3)continue;else
            if(x+2==x1&&y-1==y3)continue;else
            if(x-2==x1&&y+1==y3)continue;else
            if(x+2==x1&&y+1==y3)continue;else
            if(x-1==x1&&y-2==y3)continue;else
            if(x+1==x1&&y-2==y3)continue;else
            if(x-1==x1&&y+2==y3)continue;else
            if(x+1==x1&&y+2==y3)continue;else//关于y3（y1）的暴力判断
            if(x-2==x2&&y-1==y2)continue;else
            if(x+2==x2&&y-1==y2)continue;else
            if(x-2==x2&&y+1==y2)continue;else
            if(x+2==x2&&y+1==y2)continue;else
            if(x-1==x2&&y-2==y2)continue;else
            if(x+1==x2&&y-2==y2)continue;else
            if(x-1==x2&&y+2==y2)continue;else
            //关于y2的暴力判断
            if(x+1==x2&&y+2==y2)continue;else
            //以上统统是暴力判断棋子能否互相吃到
            if(x==x1||y==y3)continue;else
            //车的行列的暴力判断
            ans++;
            //如果和其他棋子打不到也看不着，计数器就++（表示我们又多了一个避难位置！！！）
        }
    }cout<<ans<<"\n";
    //输出总数，换行可以不加
    return 0;
    //代码丑，码风毒瘤，别介意
}
```
又及：本方法对空间要求很小，但是假设棋盘边长为n,则复杂度为O（n^2），在数据很大时会TLE。

---

## 作者：封禁用户 (赞：1)

这题可以用一个bool的二维数组来储存是否可以放棋子。但是烦人的就是如果你直接用放马的位置构建八个位置，额，RE。但是没有人愿意打八个if语句。算上放的马不能吃车，16个if语句。烦死人了。其实我们可以用一个check函数来进行处理。第0行和第0列是不会影响我们判断的，所以这样写个check函数↓↓↓
```
int check(int g)
{
	if(g<0)
	return 0;
	if(g>8)
	return 0; 
	else
	return g;
}
```
前面两个if语句的作用是如果越界了就可以直接把他变的位置丢到第0列或者第0行。

然后之后的工作就是还要打8个语句。其实for语句就可以了↓↓↓
```
for(int i=1;i<=4;i++)
		for(int j=1;j<=4;j++)
		{
			if(abs(x[i])+abs(x[j])==3)
			{
				chess[check(k+x[i])][check(n+x[j])]=false;
			}
		 } 
```
说了这么多，正宗代码终于来了↓↓↓
```
#include <bits/stdc++.h>
using namespace std;
int x[5]={0,2,-2,1,-1};
int ans=0,n,k,p=0;
char c;
bool chess[10][10];
int check(int g)
{
	if(g<0)
	return 0;
	if(g>8)
	return 0; 
	else
	return g;
}
int main()
{
	memset(chess,true,sizeof chess); 
	
	cin>>c>>n;
	k=c-'a'+1;
	for(int i=1;i<=8;i++)
	chess[k][i]=false;
	for(int i=1;i<=8;i++)
	chess[i][n]=false;
	for(int i=1;i<=4;i++)
		for(int j=1;j<=4;j++)
		{
			if(abs(x[i])+abs(x[j])==3)
			{
				chess[check(k+x[i])][check(n+x[j])]=false;
			}
		 } 
	
	cin>>c>>n;//c代表行，n代表列 
	k=c-'a'+1;
	chess[k][n]=false;
	for(int i=1;i<=4;i++)
		for(int j=1;j<=4;j++)
		{
			if(abs(x[i])+abs(x[j])==3)
			{
				chess[check(k+x[i])][check(n+x[j])]=false;
			}
		 } 
	for(int i=1;i<=8;i++)
		for(int j=1;j<=8;j++)
		{
			if(chess[i][j]==true)
			ans++;
		 } 
	cout<<ans;
	return 0;
}
```


---

## 作者：EuphoricStar (赞：0)

此题就是一个简单的模拟，根本达不到黄题的难度。

大致思路：

一开始读入车和马的坐标，然后将车所在的行与列全部标记为 $1$。

接着遍历马可能走到的 $8$ 个坐标，如果没有越界，将它标记为 $1$。

这样就完了吗？不是的，我们还需要考虑放置的马吃掉车的情况。

于是遍历新马如果要吃掉车就要放置到的 $8$ 个坐标，如果没有越界，将它标记为 $1$。

最后遍历整个棋盘，如果某个点为 $0$（即没有标记过），`++ans`。

最后输出 $ans$ 即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int dx[] = {1, 1, 2, 2, -1, -1, -2, -2};
const int dy[] = {2, -2, 1, -1, 2, -2, 1, -1};
string a, b;
bool vis[10][10];
int ax, ay, bx, by, ans;

int main() {
    ios::sync_with_stdio(0);
    cin >> a >> b;
    ax = a[0] - 'a' + 1;
    ay = a[1] - '0';
    bx = b[0] - 'a' + 1;
    by = b[1] - '0';
    vis[ax][ay] = 1;
    vis[bx][by] = 1;
    for (int i = 1; i < 9; ++i) {
        vis[i][ay] = 1;
    }
    for (int i = 1; i < 9; ++i) {
        vis[ax][i] = 1;
    }
    for (int i = 0; i < 8; ++i) {
        int nx = bx + dx[i], ny = by + dy[i];
        if (nx < 1 || nx > 8 || ny < 1 || ny > 8) {
            continue;
        }
        vis[nx][ny] = 1;
    }
    for (int i = 0; i < 8; ++i) {
        int nx = ax + dx[i], ny = ay + dy[i];
        if (nx < 1 || nx > 8 || ny < 1 || ny > 8) {
            continue;
        }
        vis[nx][ny] = 1;
    }
    for (int i = 1; i < 9; ++i) {
        for (int j = 1; j < 9; ++j) {
            if (!vis[i][j]) ++ans;
        }
    }
    cout << ans;
    return 0;
}
```


---

## 作者：Fool_Fish (赞：0)

我们这样想：首先我们知道在国际象棋中马是没有蹩脚的，所以一个马$_1$能吃到马$_2$意味着马$_2$也能吃到马$_1$，换句话说，在判断加入的马不能吃到车的条件就是把这个车看成是马，这个马能控制的位置就是不能放马的

那么最后不就简单了吗

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
bool maze[10][10];
void tag(int x,int y){
	if(x>=1&&y>=1&&x<=8&&y<=8){
		maze[x][y]=true;
	}
}
void car(int x,int y){
	tag(x,y);
	for(int i=1;i<=8;i++){
		tag(i,y);
	}
	for(int j=1;j<=8;j++){
		tag(x,j);
	}
}
void horse(int x,int y){
	tag(x,y);
	tag(x-1,y-2);
	tag(x-1,y+2);
	tag(x-2,y-1);
	tag(x-2,y+1);
	tag(x+1,y-2);
	tag(x+1,y+2);
	tag(x+2,y-1);
	tag(x+2,y+1);
}
int main(){
	char s1[5],s2[5];
	scanf("%s",s1+1);
	scanf("%s",s2+1);
	int x1,x2,y1,y2; 
	x1=s1[1]-'a'+1;
	x2=s2[1]-'a'+1;
	y1=s1[2]-'0';
	y2=s2[2]-'0';
	car(x1,y1);
	horse(x1,y1);
	horse(x2,y2);
	int ans=0;
	for(int i=1;i<=8;i++){
		for(int j=1;j<=8;j++){
			if(!maze[i][j]){
				ans++;
			}
		}
	}
	printf("%d",ans);
return 0;
}
```

---

## 作者：fjy666 (赞：0)

## CF38B Chess 题解
题目链接：[CF38B Chess](https://www.luogu.com.cn/problem/CF38B)  
这是一道模拟题。题目想让我们找到一个地方放马（国际象棋中），使得三枚棋子不能**相互攻击**。
这题的注意点：  
1. 输入是以**小写字母+数字**输入的
2. 在处理小写字母时直接用$(input)-'a'$得到的是$0\sim7$
3. 不仅要判车、马攻击新马，还要判**马会不会攻击车**、
**两个马的位置会不会重合**

知道了这些，这道题就可以A了！  
下面放上代码

------------
```cpp
#include <iostream>
using namespace std;
int r1,r2,cnt;
int c1,c2;
char p1,p2;
int a1,a2;
int mov1[]={-2,-1, 1, 2,2,1,-1,-2};
int mov2[]={-1,-2,-2,-1,1,2, 2, 1};
bool isv(int x,int y)
{
	for(int i=0;i<8;++i)
		if(((x+mov1[i]==r1)&&(y+mov2[i]==c1))||((x+mov1[i]==r2)&&(y+mov2[i]==c2)))
			return false;
	if(x==r1||y==c1||((x==r2)&&(y==c2)))
		return false;
	return true;
}
int main()
{
	cin>>p1>>a1>>p2>>a2;
	c1=p1-'a';c2=p2-'a';
	r1=a1-1;r2=a2-1;
	for(int n1=0;n1<8;++n1)
		for(int n2=0;n2<8;++n2)
			if(isv(n1,n2))
				++cnt;
	//扫描所有点
    cout<<cnt;
	return 0;
}

```
注
1. `isv`函数中先判断了新马会不会攻击老马、车（间接保证了老马不会攻击新马），再判断车会不会攻击新马、新马和老马的位置会不会重合
1. 代码里的坐标从$(0,0)$开始，到$(7,7)$结束

---

## 作者：BB2655 (赞：0)

**构造一个二维数组，存放整个棋盘的情况。**

第一次输入车的坐标，车所在的行和列不能放棋子。因为要放的是马，所以把车当作马，车的攻击范围均不能放棋子。

第二次的方法和第一次相同。

最后判断棋盘上的情况即可：

```cpp
#include<bits/stdc++.h>
using namespace std;

int f(char a)  //判断字母代表的行数
{
    if(a=='a')  return 1;
    else if(a=='b')  return 2;
    else if(a=='c')  return 3;
    else if(a=='d')  return 4;
    else if(a=='e')  return 5;
    else if(a=='f')  return 6;
    else if(a=='g')  return 7;
    else if(a=='h')  return 8;
    return 0;
}

int main()
{
    int a[9][9];
    for(int i=0;i<9;i++)
      for(int j=0;j<9;j++)
        a[i][j]=0;  //构造棋盘
    char c1,c2;
    cin>>c1>>c2;  //第一次车的情况
    int p1=f(c1),p2=c2-'0';  //车的坐标
    //if语句为马
    if(p1>2&&p2>1)  a[p1-2][p2-1]=1;
    if(p1>1&&p2>2)  a[p1-1][p2-2]=1;
    if(p1>2&&p2<8)  a[p1-2][p2+1]=1;
    if(p1>1&&p2<7)  a[p1-1][p2+2]=1;
    if(p1<7&&p2>1)  a[p1+2][p2-1]=1;
    if(p1<7&&p2<8)  a[p1+2][p2+1]=1;
    if(p1<8&&p2>2)  a[p1+1][p2-2]=1;
    if(p1<8&&p2<7)  a[p1+1][p2+2]=1;
    //for语句为车
    for(int i=1;i<9;i++)  a[f(c1)][i]=1;
    for(int i=1;i<9;i++)  a[i][c2-'0']=1;
    cin>>c1>>c2;
    p1=f(c1); p2=c2-'0';
    a[p1][p2]=1;
    //同理为车
    if(p1>2&&p2>1)  a[p1-2][p2-1]=1;
    if(p1>1&&p2>2)  a[p1-1][p2-2]=1;
    if(p1>2&&p2<8)  a[p1-2][p2+1]=1;
    if(p1>1&&p2<7)  a[p1-1][p2+2]=1;
    if(p1<7&&p2>1)  a[p1+2][p2-1]=1;
    if(p1<7&&p2<8)  a[p1+2][p2+1]=1;
    if(p1<8&&p2>2)  a[p1+1][p2-2]=1;
    if(p1<8&&p2<7)  a[p1+1][p2+2]=1;
    //最后观察情况
    int h=0;
    for(int i=1;i<9;i++)
    {
        for(int j=1;j<9;j++)
        {
            if(a[i][j]==0)  h++;
        }
    }
    cout<<h;
    return;
}
```

---

