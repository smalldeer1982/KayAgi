# [CERC2016] 凸轮廓线 Convex Contour

## 题目描述

一些几何图形整齐地在一个网格图上从左往右排成一列。它们占据了连续的一段横行，每个位置恰好一个几何图形。每个图形是以下的三种之一：


1. 一个恰好充满单个格子的正方形。


2. 一个内切于单个格子的圆。


3. 一个底边与格子重合的等边三角形。


 ![](https://cdn.luogu.com.cn/upload/pic/4685.png) 

已知每个格子的边长都为 $1$，请求出这些几何图形的凸包的周长。

## 说明/提示

对于 $100\%$ 的数据，$1 \le n \le 20$。

## 样例 #1

### 输入

```
4
TSTC```

### 输出

```
9.088434417
```

# 题解

## 作者：QwQcOrZ (赞：6)

如果您渴望O(N)的优秀算法，请出门左转[Sxy_Limit](https://www.luogu.org/blog/S-X-Y/sxy-p3680)的题解；

如果您不会凸包，请先AC[二维凸包板子](https://www.luogu.org/problemnew/show/P2742)；

如果您喜爱暴力，请看本人题解；

如果您时间紧迫，请直接看下面。

----------

首先忽略**NOI/NOI+/CTSC**的难度

然后读题：给你一团边长为1的正方形、直径为1的圆、底为1的等边三角形，求凸包周长

接着思考：能否把图形化为点阵呢？然后直接求凸包？

答案是：没错，可以

但是不免会很暴力~~但是数据小的可怜~~

构造点阵的方法：

1. S（正方形），很简单，加4个点：左上 右上 左下 右下

2. T（三角形），和正方形同样简单（不过要用到勾股定理+一元一次方程算出三角形的高），加3个点：左下 右下 中间

3. C（正圆形），比较麻烦，可能有些人~~比如我~~会认为只要加圆中间最上和最下的点就够了。

# 大错特错！！！

可以试着输入：

    2
    CT

这样程序就会爆炸

为什么呢？

因为ta出现了一堆三角形+一个圆的情况，显然，三角形的顶点与圆中间最上方直接连一条线是很愚蠢的。

so，ta们的凸包上面部分就只能是一条直线加一小段圆弧

如何解决呢？

我们不能用一堆三角函数来搞出这条线的长度，因为那~~个我不会啊~~违反暴力出奇迹的原则。

也不能打表，因为~~我懒~~打这么多显然是不现实的。

自然是用最暴力的方法，把圆上的点~~几乎~~全部加到点阵里。

于是我们得出了以下结论：

     半径：r
     角度：a
     圆点坐标：(x0,y0)
     圆上任一点为：(x1,y1)
     x1=x0+r*cos(a*π/180)
     y1=y0+r*sin(a*π/180)

其中r=0.5（显然），a需要我们枚举，x0，y0也很容易知道

然后全部加进凸包就ok了

为了避免加入不必要的点，我们只加一坨三角形和一个圆中的这个圆的靠近三角形的一边加入圆上的一堆点。

然后特判两边的圆，直接跑凸包，就AC了

简单介绍一下我用的凸包：用两个单调栈，把凸包上半部分算出来，再把下半部分算出来，然后拼起来，就是整个凸包了

注意加点时重点的情况

还有就是由于凸包是自己构造的，所以就不需要sort了

详见代码：

```cp
#include<bits/stdc++.h>
#define sqr(x) x*x  //手动定义平方 
#define calc(i,j) (a[i].x!=a[j].x?(a[i].y-a[j].y)/(a[i].x-a[j].x):INT_MAX)  //计算斜率，凸包的内容 
using namespace std;
const int N=222222;  //定常数是个好习惯 
const double pi=3.1415926535;  //圆周率，背到这位就差不多了 
const double R=0.5;  //圆的半径 

struct R
{
    double x,y;
}a[N];  //存点 
int m,n=0,w[N],c[N],t1=1,t2=1,l,r;
string s;

inline void add(double x,double y)
{
    a[++n].x=x;
    a[n].y=y;
}
inline void Input_Structure()  //输入&构造，与凸包模板就差这里（重点！咚咚咚敲黑板） 
{
    scanf("%d",&m); 
    cin>>s;
    s=' '+s;  //习惯（pascal后遗症，经常忽略s[0]） 
    for (int i=1;i<=m;i++)  //找左边第一个要搞的圆 
    {
        if (s[i]=='C') l=i;
        if (s[i]!='T') break;
    }
    for (int i=m;i>0;i--)  //找右边第一个要搞的圆 
    {
        if (s[i]=='C') r=i;
        if (s[i]!='T') break;
    }
    r=r==m?0:r;  //特判最左端的圆 
    l=l==1?0:l;  //特判最右端的圆 
    for (int i=1;i<=m;i++)  //线性扫描 
    {
        if (s[i]=='S')  //正方形 
        {
            add(i,0);
            add(i,1);
            add(i+1,0);
            add(i+1,1);
        }
        if (s[i]=='T')  //三角形 
        {
            if (a[n-1].x!=i||a[n-1].y!=0) add(i,0);  //避免重点 
            add(i+0.5,sqrt(0.75));  //根据勾股定理：0.5^2+x^2=1^2 => 0.25+x^2=1 => x^2=1-0.25 => x=sqrt(1-0.25) 
            add(i+1,0);
        }
        if (s[i]=='C')  //圆 
        {
            if (l==i) for (double j=40;j>0;j-=0.001) add(i+R-R*sin(j*pi/180),R+R*cos(j*pi/180));  //如果是左端的要搞的 
            add(i+0.5,0);
            if (r==i) for (double j=0;j<40;j+=0.001) add(i+R+R*sin(j*pi/180),R+R*cos(j*pi/180));  //如果是右端的要搞的 
                 else add(i+0.5,1);  //如果不是右端要搞的点（理论上来说可以去掉） 
        }
    }
}
inline void TB1()  //计算凸包上半部分，不展开讲了，不是重点 
{
    w[1]=1;
    for (int i=2;i<=n;i++)
    {
        while (t1>1&&calc(w[t1-1],w[t1])>calc(w[t1],i)) t1--;
        w[++t1]=i;
    }
}
inline void TB2()  //计算凸包下半部分，不展开讲了，不是重点
{
    c[1]=1;
    for (int i=2;i<=n;i++)
    {
        while (t2>1&&calc(c[t2-1],c[t2])<calc(c[t2],i)) t2--;
        c[++t2]=i;
    }
}

int main()
{
    Input_Structure(); 
    TB1();
    TB2();
    double ans=0;
    for (int i=1;i<t1;i++) ans+=sqrt(sqr(fabs(a[w[i]].x-a[w[i+1]].x))+sqr(fabs(a[w[i]].y-a[w[i+1]].y)));
    for (int i=1;i<t2;i++) ans+=sqrt(sqr(fabs(a[c[i]].x-a[c[i+1]].x))+sqr(fabs(a[c[i]].y-a[c[i+1]].y)));
    if (s[1]=='C') ans=ans-1+pi/2;  //特判最左端的圆，显然凸包不是一条直线 
    if (s[m]=='C') ans=ans-1+pi/2;  //特判最右端的圆，显然凸包不是一条直线 
    printf("%.9lf\n",ans);

    return 0;
}
/*
S:正方形
C:正圆形
T:三角形
*///这是个好习惯 
```


---

## 作者：Porsche (赞：4)

这是我AC的第一道紫题，正好看到没有人发题解，就自己来一篇

```cpp
#include<bits/stdc++.h>//万能头文件。不用担心，时间不会超~
using namespace std;
char ch[20];//(1<=n<=20),只用开20位哦~
double ans;//一定要记得开double，不然凉了不要怪我~
const double pi=3.1415926535;//背过圆周率很重要~
int main()
{
	int n;
	double p=0;//p记录'S'或'C'之前三角形的数量，出现新的'S'或'C'的时候要记得清零
	int flag=0;//很少见的int类型的flag，没办法，要存三个(0代表'T',1代表'S',2代表'C')
	scanf("%d",&n);//输入这个没用的n，你会发现完全可以用一个strlen函数求出来n~
	cin>>ch;//输入这个图形串~
//	下面就要开始计算了，我先给大家来一个详细解释：
//	1.这道题里面最坑的，肯定是'T'，因为这是一个等边三角形，它的高度是sqrt(3)，这就不太好办了
//	2.'S'和'C'就要舒服很多了，因为他们的高度都是1，只不过是'C'需要计算一个圆周率而'S'直接用边长解就行了
//	3.我们会发现当一个'T'的两边都有'S'或'C'的时候并不用去管他，只需要ans加这中间三角形的数量数就行了
//	4.最难的点就在于'T'要是出现在两边，这样会很麻烦，除非整个图形都是有'T'组成的，我前面已经说过，'T'要比'S'和'C'低，这时候就需要极强的数学运算能力了
//	5.我的解题思路是把轮廓线分为好几部分：
//		(1)第一部分是底部的轮廓线，因为有'C'的存在所以我为了方便就先不计入'T'和'S'在两端的时候两头的0.5
//		(2)第二部分是两端的轮廓线，如果是'C'的话我们就只需要加一个半圆的弧长，就是pi/2，如果是'T'或'S'的话就要加上两端还没有加上的0.5和'T'的斜边1或是'S'的纵边加上上边的2
//		(3)第三部分是上面的部分，要是只有'S'和'C'就好办多了，但是横空毛坯出来了一个可恶的'T'，的确让我废了不上功夫，要是到'T'出现在两边的话如果和'S'相邻还好办一些，只需要让ans加上一个从最头起的三角形的顶点到正方形顶点的连线的长度，而如果'T'和'C'相邻的话可就麻烦了，我们需要让ans加上一个过最头起的三角形顶点做圆的切线的长度和从切点到圆的顶端的弧长
	ans+=n-1;//计算轮廓线的第一部分，因为两端分别加除去了0.5，所以ans要加的是n-1~
//  计算轮廓线的第二部分，分别找出字符串的第0位和第n-1位(最左端和最右段)
	if(ch[0]=='C')//最左端是圆的情况 
	{
		flag=2;//用flag标记
		ans+=pi/2;//ans加上半圆的弧长
	}
	if(ch[n-1]=='C')//最右段是圆的情况
		ans+=pi/2;//ans加上半圆的弧长
	if(ch[0]=='T')//最左端是三角形的情况
	{
		p+=1.0;//记录三角形数量 
		flag=0;//用flag标记 
		ans+=1.5;//ans加上三角形底边剩余0.5和斜边的1
	}
	if(ch[n-1]=='T')//最右段是三角形的情况 
		ans+=1.5;//ans加上三角形底边剩余0.5和斜边的1
	if(ch[0]=='S')//最左边是正方形的情况
	{
		flag=1;//用flag标记
		ans+=2.5;//这里的2.5有些特殊，有底边剩余的0.5和纵边的1加起来的1.5，但哟普与我后面的程序需要在这里加上正方形的上边 
	}
	if(ch[n-1]=='S')//最右边是正方形的情况
		ans+=1.5;//ans加上正方形底边剩余的0.5和纵边的1
	for(int i=1;i<n;i++)//计算轮廓线的第三部分(好多人都是扫了好几遍才扫过，因为数据只有20，所以并不会太受影响，但是数据大了会凉掉的，这里我的循环只用扫一遍，可以承受更强的数据)
	{
		if(ch[i]=='T')p+=1.0;//记录三角形数量 
		if(ch[i]=='S')//读到正方形
		{
			if(flag==1)//前一个高度为1的图形是正方形
			{
				ans+=p+1.0;//ans加上的是中间间隔的三角形数量和此正方形上边的1
				p=0;//三角形数量清零
				continue;//下面的不用跑了，优化时间复杂度
			}
			if(flag==2)//前一个高度1的图形是圆形
			{
				ans+=p+1.5;//ans加上的是中间间隔的三角形数量，圆形右半部分剩余的0.5和正方形上边的1
				p=0;
				flag=1;//转换flag标记为正方形
				continue;
			}
			if(flag==0)//前面没有正方形或者是圆形的出现
			{
				ans+=sqrt((p-0.5)*(p-0.5)+(7.0/4.0-sqrt(3)))+1.0;//利用勾股定理可以得出，斜线段的两条直角边分别是最左边三角形的顶点到正方形的距离和此垂线到正方形左上角的1-sqrt(3)/2
				p=0;
				flag=1;
				continue;
			}
		}
		if(ch[i]=='C')//读到的是圆形
		{
			if(flag==1)//前一位高度为1的图形是正方形
			{
				ans+=p+0.5;//ans加上的是中间间隔三角形的数量和圆形左半部分的0.5
				p=0;
				flag=2;
				continue;
			}
			if(flag==2)//前一位高度为1的图形是圆形
			{
				ans+=p+1.0;//ans加上的是中间间隔的三角形数量，前一个圆形右半部分的0.5和这个圆形右半部分的0.5
				p=0;
				continue;
			}
			if(flag==0)//前面没有正方形或者是圆形的出现
			{
				//以下为本题的难点，需要极强的数学运算能力
				//这一部分由切线长len1和弧长len2组成
				double x=1.0*(p),y=(sqrt(3)/2.0-0.5);
    			double z=sqrt(x*x+1.0-sqrt(3)/2.0);
    			double len1=sqrt(x*x+1.0-sqrt(3)/2.0-0.25);//利用勾股定理求出len1
    			double o=pi/2.0-atan(y/x)-acos(0.5/z);
    			double len2=0.5*o;//高中的解三角形知识
    			p=0;
    			ans+=len1+len2;//ans加上这一部分
				flag=2;
    			continue;
			}
		}
	}
	if(p!=0)//有可能结尾最后几个是三角形，这时候剩下的轮廓线还没有加上
	{
		if(flag==1)
			ans+=sqrt((p-0.5)*(p-0.5)+(7.0/4.0-sqrt(3)));
		if(flag==2)
		{
			double x=1.0*(p),y=(sqrt(3)/2.0-0.5);
    		double z=sqrt(x*x+1.0-sqrt(3)/2.0);
    		double len1=sqrt(x*x+1.0-sqrt(3)/2.0-0.25);
    		double o=pi/2.0-atan(y/x)-acos(0.5/z);
    		double len2=0.5*o;
    		ans+=len1+len2;
		}
		if(flag==0)//有可能整个字符串都由三角形组成 
			ans+=p-1.0;//ans加上中间间隔的p-2个三角形和左右两端两个三角形剩余的0.5，化简以后是p-1
	}
	cout<<fixed<<setprecision(9)<<ans;//此题为special judge，要求精度在10^-6内，为保险起见保留9位小数输出
	return 0;
}
```
拿走不谢

---

## 作者：李乐平 (赞：4)

**~~这可能是最简单的黑题了~~**

好吧，我打了3个小时才过，还是写一篇题解作为纪念吧……

首先，分析题目：这题**实际上求的是围住这些几何图形的最短曲线**

为了简便，先把常用的无理数整出来。
```cpp
double s3 = 0.8660254037844386467637231707529; 
double pi = 3.1415926535897932384626433832795; 

double p2(double n){
	return n * n;//手动定义平方……
}
```

（略过输入部分）

其后，我们需要明白，这个周长实际上包括三部分：左边、右边和中间。当然，中间是最简单的，那么我们从左边和右边开始。

1：如果左边/右边的第一个是正方形，那就好办了：
```cpp
ans += 1;
```
2：如果是圆，那也好办：
```cpp
ans += pi / 2;
```
3：最难办的当然是三角了，我的思路是将两边的三角统计出来，用变量l和r表示三角形结束的坐标；用变量nlt（number of left triangles……）和nrt表示左右两边的三角形数量（勿喷）
```cpp
int r = n - 1,l = 0;
while((sh[l] == 'T') && (l < strlen(sh))){
	l++;
	nlt++;
}
while((sh[r] == 'T') && (r > 0)){
	r--;
	nrt++;
}
```
之后判断三角形结束位置的形状，当然，如果整个数组都是三角形，那么我们直接输出就完了：
```cpp
if(l > r){
	ans = 2 * nlt + 1;
	printf("%.10lf",ans);
	return 0;
}
```
（1）：如果是正方形，那么三角形到正方形顶点到连线长度为：
```
ans += nlt + 1 + sqrt(p2(1 - s3) + p2(nlt - 0.5));
//勾股定理
```
（注：nlt + 1是三角形左边和底边的边长，连线是sqrt（那一坨））

（2）：最坑的地方来了，如果是**一坨三角形跟一个圆**怎么办呢？

我最开始天真地以为是一条直线，后来~~经过2个小时的抓脑壳~~，我终于意识到，那是**一段与圆的切线和一小段弧线**！

那么问题就迎刃而解了——根据我们优秀的高中数学知识：

l2 = αr，即可得出弧长

![](http://a4.qpic.cn/psb?/V11JmC0o1nt6R3/BwLfiI8A*HliSPIT4*umdcjxIjKcEK2377z9PmfkZTk!/b/dFMBAAAAAAAA&ek=1&kp=1&pt=0&bo=vQDSAAAAAAADF10!&tl=1&vuin=1477486313&tm=1544932800&sce=60-1-1&rf=viewer_4)
```cpp
tl = sqrt(p2(nlt) - s3 + 0.75);
al = 0.5 * (pi / 2 - atan((s3 - 0.5) / nlt) - atan(tl * 2));
ans += nlt + 1 + tl + al;
```

剩下的问题就简单了：
将ans 加上r - l，再判断两端的形状即可。
最后别忘了，三角形和圆中间还有0.5的长度没有算，加上便是。
```cpp
if(sh[l] == 'S'){
	if(sh[r] == 'S'){
		ans += 2 * (r - l + 1);   //两边都是正方形
	}
	else{
		ans += 2 * (r - l + 0.5); //正方形和圆
	}
}
else{
	if(sh[r] == 'S'){
		ans += 2 * (r - l + 0.5); //正方形和圆
	}                        
	else{
		ans += 2 * (r - l);       //两头都是圆
	}
}
if(nlt > 0 && sh[l] == 'C') //缺失的长度
	ans += 0.5;
if(nrt > 0 && sh[r] == 'C')
	ans += 0.5;
```

附完整代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
double s3 = 0.8660254037844386467637231707529; 
double pi = 3.1415926535897932384626433832795; 
double p2(double n){
	return n * n;
}
int main(){
	int n;	
	cin>>n;
	char sh[25] = {};
	getchar();
	for(int k = 0;k < n;k++){
		sh[k] = getchar();	
	}
	int r = n - 1,l = 0,nlt = 0,nrt = 0;
	double ans = 0,tl,al;
	while((sh[l] == 'T') && (l < strlen(sh))){
		l++;
		nlt++;
	}
	while((sh[r] == 'T') && (r > 0)){
		r--;
		nrt++;
	}
	if(l > r){
		ans = 2 * nlt + 1;
		printf("%.10lf",ans);
		return 0;
	}
	if(nlt != 0){
		if(sh[l] == 'S'){
			ans += nlt + 1 + sqrt(p2(1 - s3) + p2(nlt - 0.5));
		}
		else{
			tl = sqrt(p2(nlt) - s3 + 0.75);
			al = 0.5 * (pi / 2 - atan((s3 - 0.5) / nlt) - atan(tl * 2));
			ans += nlt + 1 + tl + al;
		}
	}
	else{
		if(sh[0] == 'C'){
			ans += pi / 2;
		}
		else{
			ans += 1;
		}
	}
	if(r != n - 1){
		if(sh[r] == 'S'){
			ans += nrt + 1 + sqrt(p2(1 - s3) + p2(nrt - 0.5));
		}
		else{
			tl = sqrt(p2(nrt) - s3 + 0.75);
			al = 0.5 * (pi / 2 - (atan(tl * 2) + atan((s3 - 0.5) / nrt)));
			ans += nrt + 1 + tl + al;
		}
	}
	else{
		if(sh[r] == 'C'){
			ans += pi / 2;
		}
		else{
			ans += 1;
		}
	}
	if(sh[l] == 'S'){
		if(sh[r] == 'S'){
			ans += 2 * (r - l + 1);
		}
		else{
			ans += 2 * (r - l + 0.5);
		}
	}
	else{
		if(sh[r] == 'S'){
			ans += 2 * (r - l + 0.5);
		}
		else{
			ans += 2 * (r - l);
		}
	}
	if(nlt > 0 && sh[l] == 'C')
		ans += 0.5;
	if(nrt > 0 && sh[r] == 'C')
		ans += 0.5;
	printf("%.10lf",ans);
}
```

---

## 作者：Limit (赞：4)

看到这题时，我居然无知的认为这是一道水题，~~全然不顾那紫色~~
....

~~在疯狂地提交了40遍后，我明白了....~~
这(tmd)可(hao)真(nan)水....

如果不会三角函数出门右转[DFS_BFS_DP](https://www.luogu.org/blog/61120/solution-p3680)的题解
```
uses math;
var i,j,k:longint;
      ans:extended;
      m,n:longint;
      s:ansistring;
      l,r:longint;
      p,t:extended;
      sum:extended;
function half(ch:char):extended;
begin
  if ch='S' then exit(2);
  if ch='C' then exit(pi/2);
  if ch='T' then exit(1.5);
end;
function delta(a,b:extended):extended;
var cosA,cosB,cosC,angle,c:extended;
begin
  c:=sqrt(a*a+b*b);
  cosA:=(b*b+c*c-a*a)/(2*b*c);
  angle:=arccos(cosA)/pi*180;
  exit(angle);
end;function delta2(a,b:extended):extended;
var cosA,cosB,cosC,angle,c:extended;
begin
  c:=sqrt(b*b-a*a);
  cosA:=(b*b+c*c-a*a)/(2*b*c);
  angle:=arccos(cosA)/pi*180;
  exit(angle);
end;
begin
  readln(n);
  readln(s);
  n:=length(s);
  ans:=n*2-2;
  //找第一个不是三角形
  l:=1;
  while (s[l]='T') and (l<n) do inc(l);
  r:=n;
  while (s[r]='T') and (r>1) do dec(r);
  if (l>r) then//全是三角形
  begin
    ans:=n*2+1;
    write(ans:0:9);
    exit;
  end;
  //一个从前往后，一个从后往前，只讲一个。
  if l=1 then
  ans:=ans+half(s[1])
  else
  begin
    if s[l]='C' then //三角函数还是很重要的
    begin
    sum:=delta(sqrt(3)*0.5-0.5,l-1)+delta2(sqrt((sqrt(3)*0.5-0.5)*(sqrt(3)*0.5-0.5)+(l-1)*(l-1)-0.25),
         sqrt((sqrt(3)*0.5-0.5)*(sqrt(3)*0.5-0.5)+(l-1)*(l-1)));//利用三角函数求角度
    ans:=ans+1+{切线的特点}sqrt((sqrt(3)*0.5-0.5)*(sqrt(3)*0.5-0.5)+(l-1)*(l-1)-0.25)-(l-1-0.5)+{弧长:}(90-sum)/360*pi;{注意三角函数用的是弧度}
    end
    else
    //正方形简单多了，勾股定理套一下就好了QAQ
    ans:=ans+1+sqrt((1-0.5*sqrt(3))*(1-0.5*sqrt(3))+(l-1-0.5)*(l-1-0.5))-(l-2);
  end;
  
  if r=n then
  ans:=ans+half(s[n])
  else
  begin
    if s[r]='C' then 
    begin
    sum:=delta(sqrt(3)*0.5-0.5,n-r)+delta2(sqrt((sqrt(3)*0.5-0.5)*(sqrt(3)*0.5-0.5)+(n-r)*(n-r)-0.25),
         sqrt((sqrt(3)*0.5-0.5)*(sqrt(3)*0.5-0.5)+(n-r)*(n-r)));
    ans:=ans+1+sqrt((sqrt(3)*0.5-0.5)*(sqrt(3)*0.5-0.5)+(n-r)*(n-r)-0.25)-(n-r-0.5)+(90-sum)/360*pi;
    end
    else
    ans:=ans+1+sqrt((1-0.5*sqrt(3))*(1-0.5*sqrt(3))+(n-r-0.5)*(n-r-0.5))-(n-r-1);
  end;
  write(ans:0:9);
end.//诶，AC了。
```
在第43次提交时AC....


~~因为我评了黑题，它黑了~~

附上C++，毕竟我转C了QAQ
```cpp
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cmath>
#include<string.h>
#include<algorithm>
#define For(i,f,l) for(int pd=(f<l)*1+(l<=f)*-1,i=f;i!=l+pd;i+=pd)
#define repeat for(;;){
#define until(x) if(x){break;}}
#define pi 3.1415926535
using namespace std;
int i,j,k,l,r,n;
double ans,sum,Long;
char s[100];
double Helf(char ch)
{
  if(ch=='S')return 2.0;
  if(ch=='C')return pi/2;
  if(ch=='T')return 1.5;
}
double Delta(double a,double b)
{
  double CosA,Angle,c;
  c=sqrt(a*a+b*b);
  CosA=b/c;
  Angle=acos(CosA)/pi*180;
  return Angle;
}
double Delta_2(double a,double b)
{
  double CosA,Angle,c;
  c=sqrt(b*b-a*a);
  CosA=(2*b*b-2*a*a)/(2*b*c);
  Angle=acos(CosA)/pi*180;
  return Angle;
}
int main()
{
  cin>>n;
  for(i=1;i<=n;i++)cin>>s[i];
  ans=n*2-2;
  l=1;r=n;
  while(s[l]=='T'&&l<n)l++;
  while(s[r]=='T'&&r>1)r--;
  if(l>r)
  {
  	ans=n*2+1;
    cout<<fixed<<setprecision(9)<<ans;
  	return 0;
  }
  if(l==1)
  ans+=Helf(s[1]);
  else
  {
  	Long=l-1;
  	if(s[l]=='C')
  	{
      sum=Delta(sqrt(3)*0.5-0.5,Long)+Delta_2(
      sqrt((sqrt(3)*0.5-0.5)*(sqrt(3)*0.5-0.5)+Long*Long-0.25),
      sqrt((sqrt(3)*0.5-0.5)*(sqrt(3)*0.5-0.5)+Long*Long));
      ans+=1+sqrt((sqrt(3)*0.5-0.5)*(sqrt(3)*0.5-0.5)+Long*Long-0.25)-(Long-0.5)+(90-sum)/360*pi;
    }
    else
    ans+=+1+sqrt((1-0.5*sqrt(3))*(1-0.5*sqrt(3))+(Long-0.5)*(Long-0.5))-(Long-1);
  }
  if(r==n)
  ans+=Helf(s[n]);
  else
  {
  	Long=n-r;
  	if(s[r]=='C')
  	{
      sum=Delta(sqrt(3)*0.5-0.5,Long)+Delta_2(
      sqrt((sqrt(3)*0.5-0.5)*(sqrt(3)*0.5-0.5)+Long*Long-0.25),
      sqrt((sqrt(3)*0.5-0.5)*(sqrt(3)*0.5-0.5)+Long*Long));
      ans+=1+sqrt((sqrt(3)*0.5-0.5)*(sqrt(3)*0.5-0.5)+Long*Long-0.25)-(Long-0.5)+(90-sum)/360*pi;
    }
    else
    ans+=+1+sqrt((1-0.5*sqrt(3))*(1-0.5*sqrt(3))+(Long-0.5)*(Long-0.5))-(Long-1);
  }
  cout<<fixed<<setprecision(9)<<ans;
}
```


---

