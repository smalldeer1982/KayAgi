# [USACO17DEC] Blocked Billboard B

## 题目描述

在漫长的挤奶过程中，奶牛 Bessie 喜欢透过谷仓的窗户盯着街对面的两块巨大的矩形广告牌，上面分别写着“Farmer Alex 的美味苜蓿”和“Farmer Greg 的优质谷物”。广告牌上这两种奶牛饲料的图片对 Bessie 来说比她农场里的草看起来美味得多。

有一天，当 Bessie 正盯着窗外时，她惊讶地看到一辆巨大的矩形卡车停在街对面。卡车的侧面有一则广告，写着“Farmer Smith 的顶级牛排”，Bessie 不太理解这则广告，但她更担心的是卡车可能会挡住她最喜欢的两块广告牌的视线。

给定两块广告牌和卡车的位置，请计算两块广告牌仍然可见的总面积。卡车可能遮挡了其中一块、两块，或者没有遮挡任何一块广告牌。

## 说明/提示

在这个例子中，第一块广告牌有 $5$ 单位面积可见，第二块广告牌有 $12$ 单位面积可见。

题目来源：Brian Dean

## 样例 #1

### 输入

```
1 2 3 5
6 0 10 4
2 1 8 3```

### 输出

```
17```

# 题解

## 作者：Alex_Wei (赞：36)

本题的数据范围可以直接模拟。

当这个方格被覆盖的时候，标记该方格左上角的点。

注意点：数据范围为 $[-1000,1000]$，模拟时注意把 $x,y$ 值都加上 $1000$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int m[2200][2200],ans,a,s,d,f;//m为该平面直角坐标系，ans为没有被覆盖的面积
int main()
{
	for(int x=1;x<4;x++){
		cin>>a>>s>>d>>f;
		for(int y=a+1000;y<d+1000;y++)//x坐标 (注意此处是 < 而不是 <= ,因为标记的是点)
			for(int z=s+1000;z<f+1000;z++){//y坐标
				if(x<3)m[y][z]++,ans++;
				if(m[y][z]&&x==3)ans--;//减去重叠部分 
			}
	}
	cout<<ans;
	return 0;
}
```

$\mathrm{Upd:2019.12.11:}$ 添加 $\mathrm{Latex}$，美化文章。

---

## 作者：litianqi2529298200 (赞：11)

    
```cpp
#include<iostream>
#include<sstream>
#include<fstream>
using namespace std;
struct Rect//设一下结构体
{
    int x1,y1,x2,y2;//设置左上，左下，右上，和右下之坐标
};
int area(Rect r)
{
    return (r.x2-r.x1)*(r.y2-r.y1);//返回面积
}
int intersect_area(Rect p,Rect q)
{
int x_overlap=max(0,min(p.x2,q.x2)-max(p.x1,q.x1));//x坐标
int y_overlap=max(0,min(p.y2,q.y2)-max(p.y1,q.y1));//y坐标
return x_overlap*y_overlap;
}
int main()
{
    ios::sync_with_stdio(false);//加速的
    Rect a,b,t;//两个广告牌和挡广告牌的车
    cin>>a.x1>>a.y1>>a.x2>>a.y2;
    cin>>b.x1>>b.y1>>b.x2>>b.y2;
    cin>>t.x1>>t.y1>>t.x2>>t.y2;/*输入3个长方形各自的坐标*/
    cout<<area(a)+area(b)-intersect_area(a,t)-intersect_area(b,t)<<'\n';//输出
    return 0;//结束
}
```

---

## 作者：info___tion (赞：8)

~~老师比赛用了这一题，感觉还不错。~~

建议大家在[博客](https://www.luogu.org/blog/info---tion/solution-p4122)里食用

------------
这一题是离散化的入门题：把3个矩形的X坐标和Y坐标分别记进两个数组$X[\ ],Y[\ ]$里面，分别排序两个数组，然后我们可以发现：

原本的矩形是这样的：（红色的矩形表示第三个矩形，蓝色绿色的矩形表示第一个和第二个矩形）

![未命名2.bmp](https://i.loli.net/2018/08/16/5b752f258891c.bmp)

离散化之后就会变成这样（画工拙劣，大家凑合着看吧$qwq$）：

![未命名.bmp](https://i.loli.net/2018/08/16/5b7530b3eaa90.bmp)

我们可以用$(X_i,Y_j),(X_{i+1},Y_{j+1})$这**两个点**来表示离散化后的图中的一个**单位矩形**（因为这些矩形已经**不可再分**）。（比如说，第6个单位矩形就可以用 $(X_2,Y_1),(X_3,Y_2)$ 来表示，希望大家能理解）

然后我们枚举$X$数组和$Y$数组中的每个坐标，再判断它们**是否在第三个矩形外面并且在第一个矩形或第二个矩形的里面**，如果满足上述条件，就把这个矩形的面积加进答案，最后输出答案即可。

具体的细节可以看代码：

```cpp
#include<stdio.h>
#include<algorithm>
using namespace std;

struct Point
{
    int x,y;

    void Read()
    {
        scanf("%d%d",&y,&x);	//本人喜欢用横坐标代表X坐标，纵坐标代表Y坐标，所以就翻转读入x和y，希望大家能理解
        return;
    }
};

struct Retangle
{
    Point lu,rd;	//lu是左上角坐标，rd是右下角坐标

    void Read()
    {
        lu.Read();
        rd.Read();

        return;
    }

    int Area()	//计算矩形的面积
    {
        return (rd.x-lu.x)*(rd.y-lu.y);
    }

}cpp,txt,ad;	//不要问我为什么把矩形的名字取得这么奇怪qwq

bool In(Retangle a,Retangle b)	//判断矩形a是否在矩形b里面
{
    return bool(a.lu.x>=b.lu.x and a.rd.x<=b.rd.x and a.lu.y>=b.lu.y and a.rd.y<=b.rd.y) ;
}

int X[10],Y[10];

int main(int argc, char const *argv[])
{
    cpp.Read();	//代码可能有点过度封装，看懂就好
    txt.Read();
    ad.Read();

	//把三个矩形的X,Y坐标存进数组
    X[1]=cpp.lu.x,Y[1]=cpp.lu.y;
    X[2]=cpp.rd.x,Y[2]=cpp.rd.y;

    X[3]=txt.lu.x,Y[3]=txt.lu.y;
    X[4]=txt.rd.x,Y[4]=txt.rd.y;

    X[5]=ad.lu.x,Y[5]=ad.lu.y;
    X[6]=ad.rd.x,Y[6]=ad.rd.y;
	
    //排序
    sort(X+1,X+6+1);
    sort(Y+1,Y+6+1);

    int ans=0;

    for(int i=1;i<6;i++)
        for(int j=1;j<6;j++)
        {
        	//枚举每个“单位矩形”
            Retangle R=(Retangle){ (Point){X[i],Y[j]},(Point){X[i+1],Y[j+1]} };

            if( !In(R,ad) and ( In(R,cpp) or In(R,txt) ) )	//如果当前单位矩形在第三个矩形外面，且在第一个矩形或第二个矩形里面，就让ans加上这个单位矩形的面积
                ans+=R.Area();
        }

    printf("%d",ans);
    
    return 0;
}
```

---

## 作者：向晚 (赞：6)

最弱的蒟蒻发第一篇题解啦！！！  
首先，由题可知，是求**未被覆盖**部分--  
所以，直接**模拟**就行了，数据不会爆~~  
上代码~
```
#include<bits/stdc++.h>
using namespace std;
int z11,z12,y11,y12;       //第一个长方形的坐标
int z21,z22,y21,y22;       //第二个长方形的坐标
int z31,z32,y31,y32;       //第三个长方形的坐标
int a[10005][10005]={0},ans;//0代表未被覆盖，1代表被第三个长方形覆盖
int main(){
    cin>>z11>>z12>>y11>>y12;
    cin>>z21>>z22>>y21>>y22;
    cin>>z31>>z32>>y31>>y32;
    for(int i=z31+1000;i<y31+1000;i++)    //要记得+1000，以免遇到负数，否则会收获到4个RE
	for(int j=z32+1000;j<y32+1000;j++)//同上
	    a[i][j]=1;
    for(int i=z11+1000;i<y11+1000;i++)    //同上
        for(int j=z12+1000;j<y12+1000;j++)//同上
	    if(a[i][j]==0) ans++;
    for(int i=z21+1000;i<y21+1000;i++)    //同上
        for(int j=z22+1000;j<y22+1000;j++)//同上
	    if(a[i][j]==0) ans++;
        cout<<ans<<endl;
	return 0;
}
```


---

## 作者：lizehan888 (赞：4)

P党福利，了解一下~~~

思路1.模拟

  按照题目描述直接用二维标志数组覆盖（类似“桶”），最后扫描一遍，累加面积。
  （注意：在平面直角坐标系中，题目给的是点的坐标，要区别于方格）
  
  极限时间复杂度大概是8e9
  
思路2.数学方法

主要思路是将1、2两个矩形面积求出，再减去1、2被3覆盖的面积

具体操作如图所示：

![](http://a2.qpic.cn/psb?/V14TRQIZ0TiWXe/DGPY.DKWphzkoE96D0CetSCeTRp8ntqkNmbsg6XAIs4!/m/dDEBAAAAAAAAnull&bo=UAKgAQAAAAADB9E!&rf=photolist&t=5)


有种情况是3没有覆盖到1或2，则求面积时注意（见代码）。
  
  时间复杂度？----O(1)！！！！！
  
------------


上代码

    var
      a:array[0..100]of longint;
      x1,x2,x3,x4,y1,y2,y3,y4,i,s1,s2,s3,s4:longint;
    function max(m,n:longint):longint;
    begin
      if m>n then exit(m) else exit(n);
    end;
    function min(m,n:longint):longint;
    begin
      if m>n then exit(n) else exit(m);
    end;
    begin    
      for i:=1 to 12 do read(a[i]);
     //核心代码如下： 
      x1:=max(a[1],a[9]);x2:=min(a[3],a[11]);
      y1:=max(a[2],a[10]);y2:=min(a[4],a[12]);
      x3:=max(a[5],a[9]);x4:=min(a[7],a[11]);
      y3:=max(a[6],a[10]);y4:=min(a[8],a[12]);
      s1:=(a[3]-a[1])*(a[4]-a[2]);
      s2:=(a[7]-a[5])*(a[8]-a[6]);
      s3:=(max(0,(x2-x1)))*(max(0,(y2-y1)));//防止3没有覆盖到1，(x2-x1)要与0比较
      s4:=(max(0,(x4-x3)))*(max(0,(y4-y3)));
      writeln(s1+s2-s3-s4);
    end.

---

## 作者：ShaeKnight (赞：3)

~~我相信第一眼看到这题目第一反应就是暴力模拟的不止我一个人~~

### 思路:

用数组模拟坐标系，因为读入坐标存在负数，所以把每个坐标读入后再加上$1000$，把前两个矩形所占的点变为$1$，后一个矩形所占的点变为$0$，最后统计在前两个矩形中仍为$1$的点。

$ \color{white}\text{其实是因为太蒻了想不出来怎么用数论解} $

### 代码实现:

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cctype>     //头文件
#define ll long long
#define fr(c,a,b) for(int c=a;c<=b;c++)
#define rf(c,a,b) for(int c=a;c>=b;c--)  //没有什么用的宏定义
const int Max=1e6;
const int Min=-1;
inline int read()
{
	int s=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){s=(s<<3)+(s<<1)+(c^48);c=getchar();}
	return s*f;
}
inline void write(int x)
{
	if(x<0){putchar('-');x=-x;}
	if(x>9)write(x/10);
	putchar(x%10+'0');
}      //快读快写
int mp[2005][2005],sum;   //定义用来模拟的数组  因为区间是在 -1000~1000之间，所以2000大小就行
int x1[3],x2[3],y1[3],y2[3];   //坐标
int main()
{
	x1[0]=read()+1000,y1[0]=read()+1000,x2[0]=read()+1000,y2[0]=read()+1000;
	fr(j,x1[0],x2[0]-1)
		fr(k,y1[0],y2[0]-1)mp[j][k]=1;
	//第一个矩形的处理
	x1[1]=read()+1000,y1[1]=read()+1000,x2[1]=read()+1000,y2[1]=read()+1000;
	fr(j,x1[1],x2[1]-1)
		fr(k,y1[1],y2[1]-1)mp[j][k]=1;
	//第二个矩形的处理
	x1[2]=read()+1000,y1[2]=read()+1000,x2[2]=read()+1000,y2[2]=read()+1000;
	fr(j,x1[2],x2[2]-1)
		fr(k,y1[2],y2[2]-1)mp[j][k]=0;
	//被遮挡的部分变成0
	fr(j,x1[0],x2[0]-1)
		fr(k,y1[0],y2[0]-1)if(mp[j][k])sum++;
	fr(j,x1[1],x2[1]-1)
		fr(k,y1[1],y2[1]-1)if(mp[j][k])sum++;
	//累加未被遮挡的部分
	write(sum);   //输出
	return 0;
}
```

### 特别提醒: 题目中所说的面积实际上是点的个数所以坐标要$-1$
~~就是因为这个-1卡了我10几分钟~~
~~还是我太蒻了~~

---

## 作者：WHJ___ (赞：1)

根据数据范围，显然可以知道一道非常简单的大模拟

对于前两个矩形，我们将它们所占的格子都涂上 1，这里注意我们涂的是 **格子** ，而不是 **点**，如果你涂的是 **点**，显然矩形会多一圈，因此我采取的方法是对有1的格子，把1这个标记打在格子的右上角上，就可以完美避免这个问题。我相信很多在座的同学样例输出 24，就是因为这个原因,导致每个矩形都多出了一圈。


过程即是:

1.将输入的前两个矩形所覆盖方格的右上角涂上标记1

2.将输入的第三个矩形所覆盖方格上单元格右上角全部清除标记

3.枚举所有的点,得出答案


数据范围 $ x,y∈[-1000,1000]$ ,而数组下标显然不能为负数(会导致RE),因此我们要对输入的点都加上 1000,这样才能防止越界.

代码如下:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e3+7;

bool a[N][N];//构建图形,全局变量默认为0 
int ans;

inline int read(){//快速读入 
	int x=0,f=1;
	char c=0;
	while(!isdigit(c=getchar()))f-=(c=='-')*2;
	while(isdigit(c)){x=(x<<1)+(x<<3)+f*(c-48);c=getchar();}
	return x;
}

signed main()
{
	register int i,j,k;
	int ld_x,ld_y;//ld_x为左下角点的x坐标,ld_y为左下角点的y坐标 
	int ru_x,ru_y;//ru_x为右上角点的x坐标,ru_y为右上角点的y坐标 
	for(k=1;k<=2;++k){//前两个矩形,输入两次 
		ld_x=read()+1000;ld_y=read()+1000;
		ru_x=read()+1000;ru_y=read()+1000;//都增加1000防止越界 
		for(i=ld_x+1;i<=ru_x;++i)
			for(j=ld_y+1;j<=ru_y;++j)//对右上角进行标记
				a[i][j]=1;//打上1的标记 
	}
	ld_x=read()+1000;ld_y=read()+1000;
	ru_x=read()+1000;ru_y=read()+1000;
	for(i=ld_x+1;i<=ru_x;++i)
		for(j=ld_y+1;j<=ru_y;++j)
			a[i][j]=0;//去除标记 
	for(i=0;i<=2000;++i)
		for(j=0;j<=2000;++j)
			ans+=a[i][j];//得出答案 
	cout<<ans;
	return 0;
}

```


(请勿抄题解,这对你没有任何帮助)


---

## 作者：鸿飞 (赞：1)

## PART1:题意
在平面直角坐标系中，有两个矩形（保证不相交），然后给出第三个矩形，求这两个矩形没有被第三个矩形遮住的部分的面积。
## PART2:思路
数据范围（-1000~1000）明显可以暴力模拟过。不过因为坐标可能为负，循环时加上1001就好了。
## PART3:代码
```cpp
#include<iostream>
using namespace std;
int a1,b1,c1,d1; 
int a2,b2,c2,d2;
int a3,b3,c3,d3;
int map[5000][5000];
int main(){
	cin >> a1 >> b1 >> c1 >> d1 ;
	cin >> a2 >> b2 >> c2 >> d2 ;
	cin >> a3 >> b3 >> c3 >> d3 ;
	int ans=0;
	for(int j=b1+1001;j<d1+1001;j++)
	{
		for(int i=a1+1001;i<c1+1001;i++)
		{
		
			map[i][j]=1;
			ans++;
		}
	}
	for(int j=b2+1001;j<d2+1001;j++)
	{
		for(int i=a2+1001;i<c2+1001;i++)
		{
			if(map[i][j]!=1)
			{
				ans++;
			}
			map[i][j]=1;	
		}
	}
	for(int j=b3+1001;j<d3+1001;j++)
	{
		for(int i=a3+1001;i<c3+1001;i++)
		{
		
			if(map[i][j]==1)
			{
				ans--;
			}
		}
	}
	cout << ans ;
	return 0;
}

```



---

## 作者：Weyne (赞：0)

**这个题第一次看还是挺难的，一定要把样例算出来，这样这个题的难度就会减小很多，简单来说就是在一个2000*2000的平面内丢三个矩形，有两个矩形一定不会相交，来算算另一个矩形的对前两个矩形的覆盖面积，总体来讲看懂题了，实现难度都不是很大**

------------
**小蒟蒻写了两种方法供大家参考**

------------
1.标点（就是先把互不相交的个矩形的坐标点标上1，另一个矩形部分标上0，最后扫描整个表把坐标点的值加起来就可以了，比较通俗易懂）
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int z[5],zs[5],y[5],ys[5],d=1000,s=0;
bool v[2010][2010];//做一个二维表，用bool因为下文只要用1，0判断，标记
int main()
{
	//freopen("billboard.in","r",stdin);//打开输入文件 只读 
	//freopen("billboard.out","w",stdout);//书写输出文件 只写 
	 
	for(int i=1;i<=3;i++)//分别输入两块广告牌，一个车的左下，右上的坐标 
	{
		cin>>z[i]>>zs[i]>>y[i]>>ys[i];//输入坐标 
		for(int j=zs[i];j<ys[i];j++)//横排扫描 
		{
			for(int k=z[i];k<y[i];k++)//竖排扫描 
			{
				if(i<3)//如果这组坐标不是车的坐标 
				{
					v[j+d][k+d]=1;//那就标记一个1 
				}
				else//如果是车的坐标 
				{
					v[j+d][k+d]=0;//那就标记一个0 
				}
			}
		}
	}
	for(int j=0;j<2000;j++)//扫描整个二维表 
	{
		for(int k=0;k<2000;k++)//扫描整个二维表 
		{
			if(v[j][k])//如果这个坐标为真也就是上文标记的1 
			{
				s++;//最终结果加一个单位 
			}
		}
	}
	cout<<s<<endl;//输出结果
	//fclose(stdin);//关闭输入 
	//fclose(stdout);//关闭输出 
	return 0; 
}

```
------------
2.函数（主要靠数学，各位大佬的数学肯定是没有问题的，就看有没有分析样例了）
```
#include<iostream>
using namespace std;
int z[5],zx[5],y[5],ys[5],s[10];
int v(int i,int j)
{
	int zl=max(z[i],z[j]);
	int yl=min(y[i],y[j]);
	if(zl>=yl) return 0;
	int xl=max(zx[i],zx[j]);
	int sl=min(ys[i],ys[j]);
	if(xl>=sl) return 0;
	return (yl-zl)*(sl-xl);
}
int main()
{
	for(int i=1;i<=3;i++)
	{
		cin>>z[i]>>zx[i]>>y[i]>>ys[i];
		s[i]=(y[i]-z[i])*(ys[i]-zx[i]);
	}
	s[4]=v(1,3);
	s[5]=v(2,3);
	s[6]=s[1]+s[2]-s[4]-s[5];
	cout<<s[6]<<endl;
	return 0;
}
```
希望小蒟蒻的题解能给你带来帮助( •̀ ω •́ )✧

---

## 作者：Snow_Dreams (赞：0)

这道题可以模拟

定义ans=abs(（x1-y1）*(x2-y2))（第三个矩形的面积）

首先判断三个矩形有没有交集，若没有，则直接输出第三个矩形的面积abs(（x1-y1）*(x2-y2))（ans）

若有交集，则减去与两个矩形的交集

再判断另外两个矩形有没有交集

如果没有，则直接输出ans

如果有，则输出ans+另外两个矩形的交集

### 为什么？

在此我讲解一下∩

以下部分资料源自百度百科：

1. 若两个集合A和B的交集为空，则说他们没有公共元素，写作：A∩B = ∅。例如集合 {1,2} 和 {3,4} 不相交，写作 {1,2} ∩ {3,4} = ∅。


2. 任何集合与空集的交集都是空集，即A∩∅=∅。


3. 更一般的，交集运算可以对多个集合同时进行。例如，集合A、B、C和D的交集为A∩B∩C∩D=A∩[B∩(C ∩D)]。交集运算满足结合律，即A∩(B∩C)=(A∩B) ∩C。


4. 最抽象的概念是任意非空集合的集合的交集。若M是一个非空集合，其元素本身也是集合，则 x 属于 M 的交集，当且仅当对任意 M 的元素 A，x 属于 A。这一概念与前述的思想相同，例如，A∩B∩C 是集合 {A,B,C} 的交集（M 何时为空的情况有时候是能够搞清楚的，请见空交集）。


这一概念的符号有时候也会变化。集合论理论家们有时用 "∩M"，有时用 "∩A∈MA"。后一种写法可以一般化为 "∩i∈IAi"，表示集合 {Ai|i ∈ I} 的交集。这里 I 非空，Ai 是一个 i 属于 I 的集合。


集合论中，设A，B是两个集合，由所有属于集合A且属于集合B的元素所组成的集合，叫做集合A与集合B的交集（intersection），记作A∩B。

---

## 作者：jujujujuruo (赞：0)

~~我一开始怀疑这道题为什么不是红题~~

然后我就成功WA了三个点。。。

之前看有的大佬用的是标记每一个点，类似于桶的做法，但这种遇到大的数据应该就不是很管用了 ~~尽管这道题的数据很水~~

本题的关键点就是找到重合矩形的左下角和右上角的点（其实其他点也可），通过比较可以发现，左下角的点的横坐标是原来矩形左下角的横坐标和覆盖矩形左下角的横坐标较大的那个，右上角的点的横坐标是原来矩形右上角的横坐标和覆盖矩形右上角的横坐标较小的那个，纵坐标同理。

我就用绝对值来计算面积的方法来做的，专门写了一个用来计算面积的函数calculate_square

附上（第一版）代码
###### 

------------
```cpp

#include<cstdio>
#include<cstdlib>
using namespace std;
int calculate_square(int x1, int y1, int x2, int y2);
int main()
{
    int x[5], y[5], x1, x2, y1, y2, s1, s2, minus_s1, minus_s2;
    scanf("%d %d %d %d", &x[1], &y[1], &x[2], &y[2]);
    scanf("%d %d %d %d", &x[3], &y[3], &x[4], &y[4]);
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    s1 = calculate_square(x[1], y[1], x[2], y[2]);
    s2 = calculate_square(x[3], y[3], x[4], y[4]);
    minus_s1 = calculate_square(max(x1,x[1]),max(y1, y[1]), min(x2,x[2]), min(y2, y[2]));
    minus_s2 = calculate_square(max(x1,x[3]),max(y1, y[3]), min(x2,x[4]), min(y2, y[4]));
    printf("%d\n", s1+s2-minus_s1-minus_s2);
    return 0;
}
int calculate_square(int x1, int y1, int x2, int y2)
{
    int x, y, s;
    x = abs(x1- x2);
    y = abs(y1- y2);
    s = x * y;
    return s;
}
```
然后我就成功WA了三个点T^T

在我~~无耻地下载了数据看看后~~认真地debug后发现可能存在覆盖矩形根本不会覆盖上原来的两个矩形的情况！这种情况怎么处理呢？

那就是！！

????????????

保证那个点就是“左下”和“右上”！！比较一下横纵坐标即可！！

具体情况看AC代码：

```cpp
#include<cstdio>
#include<cstdlib>
using namespace std;
int calculate_square(int x1, int y1, int x2, int y2);
int main()
{
    int x[5], y[5], x1, x2, y1, y2, s1, s2, minus_s1, minus_s2;
    scanf("%d %d %d %d", &x[1], &y[1], &x[2], &y[2]);
    scanf("%d %d %d %d", &x[3], &y[3], &x[4], &y[4]);
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    s1 = calculate_square(x[1], y[1], x[2], y[2]);
    s2 = calculate_square(x[3], y[3], x[4], y[4]);
    if((max(x1,x[1])<=min(x2,x[2]))&&(max(y1, y[1])<= min(y2, y[2])))
    minus_s1 = calculate_square(max(x1,x[1]),max(y1, y[1]), min(x2,x[2]), min(y2, y[2]));
    else minus_s1 = 0;
    if((max(x1,x[3])<=min(x2,x[4]))&&(max(y1, y[3])<= min(y2, y[4])))
    minus_s2 = calculate_square(max(x1,x[3]),max(y1, y[3]), min(x2,x[4]), min(y2, y[4]));
    else minus_s2 = 0;
    printf("%d\n", s1+s2-minus_s1-minus_s2);
    return 0;
}
int calculate_square(int x1, int y1, int x2, int y2)
{
    int x, y, s;
    x = abs(x1- x2);
    y = abs(y1- y2);
    s = x * y;
    return s;
}
```

写题解不易T^T 看懂的求个赞吧

也求管理员大大给过（写了两次都没过了，新的一年可怜可怜孩纸）


---

## 作者：恶灬心 (赞：0)

### 扫描线+线段树+（可有可无的离散化）

1.洛谷上似乎只有求矩形覆盖周长的，所以把这道题当作练习矩形覆盖面积了。  
2.不是标准解法，但每个点都是2ms，3ms的也是挺快的。  

#### 下面解释写法：

1. 首先，我们看到这道题，会想到一个简单容斥，用三个矩形面积和 - 三个矩形覆盖后的面积来得到两个矩形被覆盖的面积大小，然后用两个矩形的面积和 - 这个值就行。

那图来说。

![](https://cdn.luogu.com.cn/upload/image_hosting/ki9bh4q8.png)

这是样例绘制出来的图，很容易看出，我们只要求出中间这个矩形（也就是矩阵3）覆盖左右两个矩阵的面积，再用左右两个矩阵的面积减去这个值就行。

那么，这个等式的唯一难点就在于 如何快速计算三矩阵覆盖后的面积。

我们肉眼计算时，很容易就会将其分层，分成若干个小矩阵

![](https://cdn.luogu.com.cn/upload/image_hosting/el6t74cl.png)

我们用一些直线,将整幅图分解成若干个矩形。

从下向上看，每层里都可能出现若干矩形，他们的高都是两扫描线之间的间距，我们只要有办法维护当前扫描线他们的底，就可以快速计算每层中矩形的面积。

线段树就正好符合这个性质，快速实现区间插入删除，快速查询当前区间和。

值得注意的是在 扫描线$rs$和扫描线$uv$之间，我们发现明明底端是全部覆盖的情况，但矩形却被分为两个。 很明显，这条红线具有一些不同于其他线(一些)的性质，我们接下来称这根线为红线。

观察这幅图，这根红线属于中间大矩形的上端，观察其他两个大矩形的上端上方同样有这根红线的性质（指这个底上方**应该**不存在矩阵）

但是，我们在观察那根红线左右两端上方均有被矩形覆盖，证明还有因素在影响矩形出现。

一个矩形必定有上下端，且上下端性质不同，我们用 $sum$ 来统计下端覆盖比上端多的次数，如果$sum$为正，说明它可以作为底，如果$sum$为0，说明它不可以。

然后用线段树来统计长度即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
	int w=1,d=0; char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1; ch=getchar();}
	while(ch>='0'&&ch<='9') d=(d<<3)+(d<<1)+(ch^48),ch=getchar();
	return w*d;
}
const int N = 3000;
struct Edge{
	int l,r,height,flag;
	bool operator < (const Edge &b)const{
		return height<b.height;
	}
}e[20];
int tot;
map<int,bool> mp;
int rq[500],cnt;
struct Tree{
	int sum,num;
}tree[N<<2];
void add_edge(int l,int r,int height,int z)
{
	e[++tot].height=height,e[tot].l=l,e[tot].r=r,e[tot].flag=z;
}
void pushup(int rt,int l,int r)
{
	if(tree[rt].sum) 
	{
		tree[rt].num=(rq[r+1]-rq[l]);
	}
	else if(l==r) tree[rt].num=0;
	else tree[rt].num=tree[rt<<1].num+tree[rt<<1|1].num;
}
void add(int rt,int l,int r,int ll,int rr,int k)
{
	if(ll<=l&&r<=rr)
	{
		tree[rt].sum+=k;
		pushup(rt,l,r);
		return ;
	}
	int mid=(l+r)>>1;
	if(ll<=mid) add(rt<<1,l,mid,ll,rr,k);
	if(mid<rr) add(rt<<1|1,mid+1,r,ll,rr,k);
	pushup(rt,l,r);
} 
int main()
{
	long long f=0,ans=0,f2=0;
	for(register int i=1;i<=3;i++)
	{
		int x1=read(),y1=read(),x2=read(),y2=read();
		f+=(x2-x1)*(y2-y1);
		if(i<=2) f2+=(x2-x1)*(y2-y1);
		if(!mp.count(x1)) rq[++cnt]=x1,mp[x1]=1;
		if(!mp.count(x2)) rq[++cnt]=x2,mp[x2]=1;
		add_edge(x1,x2,y1,1);
		add_edge(x1,x2,y2,-1);
	}
	sort(e+1,e+1+tot);
	sort(rq+1,rq+1+cnt);
	for(register int i=1;i<=tot;i++)
	{
		int gl,gr;
		gl = lower_bound(rq+1,rq+1+cnt,e[i].l) - rq;
		gr = lower_bound(rq+1,rq+1+cnt,e[i].r) - rq;
		add(1,1,cnt,gl,gr-1,e[i].flag);
		while(e[i].height==e[i+1].height)
		{
			i++;
			gl = lower_bound(rq+1,rq+1+cnt,e[i].l) - rq;
			gr = lower_bound(rq+1,rq+1+cnt,e[i].r) - rq;
			add(1,1,cnt,gl,gr-1,e[i].flag);
		}
		ans += tree[1].num*(e[i+1].height-e[i].height); 
	}
	printf("%lld",f2-(f-ans));
	return 0;
}

```


---

## 作者：hezhijin (赞：0)

这题我是按部就班地去做的，先填充，然后进行删除，扫描后输出个数。
记住，坐标填充要加1，且要加上1000，避免出现负数值！
下面是题解：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[2005][2005]={0};
int ans,l=10000,r=10000,l1,r1;
int main()
{
    for(int i=1;i<=2;i++)
    {
        int x,x1,y1,y;
        cin>>x>>y>>x1>>y1;
        l=min(x,l);r=min(y,r);
        l1=max(x1,l1);r1=max(r1,y1);
        for(int p=x+1001;p<=x1+1000;p++)
        for(int l=y+1001;l<=y1+1000;l++)
        a[p][l]=1;
    }
    int x,x1,y,y1;
    cin>>x>>y>>x1>>y1;
    for(int i=x+1001;i<=x1+1000;i++)
    for(int j=y+1001;j<=y1+1000;j++)
    a[i][j]=0;
    for(int i=l+1001;i<=l1+1000;i++)
    for(int j=r+1001;j<=r1+1000;j++)
    if(a[i][j]==1) ans++;
    cout<<ans<<endl;
}
```

---

