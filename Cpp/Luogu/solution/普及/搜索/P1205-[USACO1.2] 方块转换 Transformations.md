# [USACO1.2] 方块转换 Transformations

## 题目描述

一块 $n \times n$ 正方形的黑白瓦片的图案要被转换成新的正方形图案。写一个程序来找出将原始图案按照以下列转换方法转换成新图案的最小方式：

- 转 $90\degree$：图案按顺时针转 $90\degree$。

- 转 $180\degree$：图案按顺时针转 $180\degree$。

- 转 $270\degree$：图案按顺时针转 $270\degree$。

- 反射：图案在水平方向翻转（以中央铅垂线为中心形成原图案的镜像）。

- 组合：图案在水平方向翻转，然后再按照 $1 \sim 3$ 之间的一种再次转换。

- 不改变：原图案不改变。

- 无效转换：无法用以上方法得到新图案。

如果有多种可用的转换方法，请选择序号最小的那个。

只使用上述 $7$ 个中的一个步骤来完成这次转换。


## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$1\le n \le 10$。

题目翻译来自 NOCOW。

USACO Training Section 1.2


## 样例 #1

### 输入

```
3
@-@
---
@@-
@-@
@--
--@
```

### 输出

```
1
```

# 题解

## 作者：CJXJR (赞：881)

# 大模拟！！！     

  说实话，我认为本题的算法并不是**搜索**，而是**模拟**，题目已经很明确的说了，$n$一共有$7$种情况，我们把这七种情况一个一个**分情况讨论**，答案就出来了。

------------

$$\text{正式进入题目(咳咳，严肃）}$$
  由于题目要求将每一次所变换的图形与原图形进行**比较**，所以定义数组$a[15][15],b[15][15],c[15][15],d[15][15](\text{题目申明}1 \leq n\leq10)$,$a$数组表示第一个输入的矩阵，$b$数组表示变换后的矩阵，$c$数组表示要对照的矩阵，$d$数组为将要存放的矩阵，所以可以写出以下判断$b$矩阵与$c$矩阵相同的代码   
↓↓↓
```
for(int i=1;i<=n;i++)
     for(int j=1;j<=n;j++)
     if(b[i][j]!=c[i][j])
     return 0;
     return 1;
```
简单明了，蒟蒻都能懂！

------------

$$First:n=1$$  
设原矩阵为↓↓↓
```
11 12 13
21 22 23
31 32 33
```
那么，经过顺时针转$90$度的矩阵为
```
31 21 11
32 22 12
33 23 13
```
列出$i$(行)与$j$(列)的关系，如下：    
![](https://cdn.luogu.com.cn/upload/pic/60018.png)   
再进行**找规律**，经推敲可得
$$b[j][n-i+1]=a[i][j]$$
再与前面所说的判断合在一起，可得：
```
bool work1()
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        b[j][n-i+1]=a[i][j];
    }
    for(int i=1;i<=n;i++)
     for(int j=1;j<=n;j++)
     if(b[i][j]!=c[i][j])
     return 0;
     return 1;
}
```
$∴$当$n=1$时，代码打好了。

------------
$$Second:n=2$$ 
相同的，设原矩阵为↓↓↓
```
11 12 13
21 22 23
31 32 33
```
那么，经过顺时针转$180$度的矩阵为
```
33 32 31
23 22 21
13 12 11
```
列出$i$(行)与$j$(列)的关系，如下：  
![](https://cdn.luogu.com.cn/upload/pic/60017.png)   
分析可得
$$b[n-i+1][n-j+1]=a[i][j]$$
代码实现：
```
bool work2()
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        b[n-i+1][n-j+1]=a[i][j];
    }
    for(int i=1;i<=n;i++)
     for(int j=1;j<=n;j++)
     if(b[i][j]!=c[i][j])
     return 0;
     return 1;
}
```
当然，当$n=2$时，也可以看做**进行了两次$1$操作**，即：
```
void work2()
{
	work1(); //第一次操作
	for(int i=1;i<=n;i++)
     for(int j=1;j<=n;j++)
      a[i][j]=b[i][j];  //重置矩阵
      work1();  //第二次操作
    for(int i=1;i<=n;i++)
      for(int j=1;j<=n;j++)
     if(b[i][j]!=c[i][j])
     return 0;
     return 1;
}
```
两代码的结果相同，但前者效率较高，后者代码短小精悍，更好理解。   

$∴$当$n=2$时，代码打好了。
$$QAQ$$

------------
$$Third:n=3$$ 
同样的，设原矩阵为↓↓↓
```
11 12 13
21 22 23
31 32 33
```
那么，经过顺时针转$270$度的矩阵为
```
13 23 33
12 22 32
11 21 31
```
列表：   
![](https://cdn.luogu.com.cn/upload/pic/60024.png)   
这次规律有一些难找了，是
$$b[n-j+1][i]=a[i][j]$$
于是
```
bool work3()
{
	for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        b[n-j+1][i]=a[i][j];
    }
    for(int i=1;i<=n;i++)
      for(int j=1;j<=n;j++)
     if(b[i][j]!=c[i][j])
     return 0;
     return 1;
}
```
也可以看作**先进行一次$1$操作再进行一次$2$操作**
代码：
```
bool work3()
{
	work1();  //第一次操作
	for(int i=1;i<=n;i++)
     for(int j=1;j<=n;j++)
      a[i][j]=b[i][j];   //重置矩阵
      work2();   //第二次操作
    for(int i=1;i<=n;i++)
      for(int j=1;j<=n;j++)
     if(b[i][j]!=c[i][j])
     return 0;
     return 1;
}
```
$$n=3\text{完工！}$$

------------
$$Fourth:n=4$$ 
同样的，设原矩阵为↓↓↓
```
11 12 13
21 22 23
31 32 33
```
那么，经过反射的矩阵为
```
13 12 11
23 22 21
33 32 31
```
~~又是无聊的列表：~~   
![](https://cdn.luogu.com.cn/upload/pic/60025.png)   
可以找出
$$b[i][n-j+1]=a[i][j]$$
代码实现：
```
bool work4()
{
	for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        b[i][n-j+1]=a[i][j];  
    }
    for(int i=1;i<=n;i++)
      for(int j=1;j<=n;j++)
     if(b[i][j]!=c[i][j])
     return 0;
     return 1;
}
```
$$OK$$

------------
$$Fifth:n=5$$ 
$5$操作就是将$4,1,2,3$操作混和(~~粗略的说法~~),作者为了~~偷懒~~，$QAQ$,就~~不找规律~~了，给出代码：
```
bool work5()
{
	work4();
	for(int i=1;i<=n;i++)
     for(int j=1;j<=n;j++)
      a[i][j]=d[i][j];    //重置矩阵  
      if(work1())
      return 1;
    for(int i=1;i<=n;i++)
     for(int j=1;j<=n;j++)
      a[i][j]=d[i][j];   //重置矩阵 
      if(work2())
      return 1;
    for(int i=1;i<=n;i++)
     for(int j=1;j<=n;j++)
      a[i][j]=d[i][j];   //重置矩阵 
      if(work3())
      return 1;
      return 0;
}
```
$$\text{逃}$$

------------
$$Sixth:n=6$$
没有操作，直接比较：
```
bool work6()
{
    for(int i=1;i<=n;i++)
      for(int j=1;j<=n;j++)
     if(b[i][j]!=c[i][j])
     return 0;
     return 1;
}
```
$$easy$$

------------
$$Seventh:n=7$$
直接输出$7$即可
```
   cout<<7;
```

------------
核心代码已经打完了，我们可以将代码美观化，用一个$work$函数把它们包起来
```
void work()
{
    if(work1())
    {
        cout<<1;
        return ;
    }
    if(work2())
    {
        cout<<2;
        return ;
    }
    if(work3())
    {
    	cout<<3;
    	return ;
	}
	if(work4())
	{
		cout<<4;
		return ;
	}
	if(work5())
	{
		cout<<5;
		return ;
	}
	if(work6())
	{
		cout<<6;
		return ;
	}
	cout<<7;
}
```

------------
$My  complete  code$
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
char a[15][15],b[15][15],c[15][15],d[15][15];
bool work1()
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        b[j][n-i+1]=a[i][j];
    }
    for(int i=1;i<=n;i++)
     for(int j=1;j<=n;j++)
     if(b[i][j]!=c[i][j])
     return 0;
     return 1;
}
bool work2()
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        b[n-i+1][n-j+1]=a[i][j];
    }
    for(int i=1;i<=n;i++)
     for(int j=1;j<=n;j++)
     if(b[i][j]!=c[i][j])
     return 0;
     return 1;
}
bool work3()
{
	for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        b[n-j+1][i]=a[i][j];
    }
    for(int i=1;i<=n;i++)
      for(int j=1;j<=n;j++)
     if(b[i][j]!=c[i][j])
     return 0;
     return 1;
}
bool work4()
{
	for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        b[i][n-j+1]=a[i][j];
    }
    for(int i=1;i<=n;i++)
      for(int j=1;j<=n;j++)
     if(b[i][j]!=c[i][j])
     return 0;
     return 1;
}
bool work5()
{
	work4();
	for(int i=1;i<=n;i++)
     for(int j=1;j<=n;j++)
      a[i][j]=b[i][j];  
      if(work1())
      return 1;
    for(int i=1;i<=n;i++)
     for(int j=1;j<=n;j++)
      a[i][j]=b[i][j]; 
      if(work2())
      return 1;
    for(int i=1;i<=n;i++)
     for(int j=1;j<=n;j++)
      a[i][j]=b[i][j]; 
      if(work3())
      return 1;
      return 0;
}
bool work6()
{
    for(int i=1;i<=n;i++)
      for(int j=1;j<=n;j++)
     if(b[i][j]!=c[i][j])
     return 0;
     return 1;
}
void work()
{
    if(work1())
    {
        cout<<1;
        return ;
    }
    if(work2())
    {
        cout<<2;
        return ;
    }
    if(work3())
    {
    	cout<<3;
    	return ;
	}
	if(work4())
	{
		cout<<4;
		return ;
	}
	if(work5())
	{
		cout<<5;
		return ;
	}
	if(work6())
	{
		cout<<6;
		return ;
	}
	cout<<7;
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
     for(int j=1;j<=n;j++)
     {
     	cin>>a[i][j];
     	d[i][j]=a[i][j];
	 }
      
    for(int i=1;i<=n;i++)
     for(int j=1;j<=n;j++)
      cin>>c[i][j];
    work();
    return 0; //完美的结束QAQ
}
```

---

## 作者：hsfzLZH1 (赞：154)

通过观察题目，我们可以很轻易地发现，旋转180度可以由顺时针旋转90度的两次叠加形成，顺时针旋转270度可以由旋转180度和顺时针旋转90度的叠加形成，所以我们可以通过一个循环来处理顺时针旋转90度，180度，270度，代码框架如下（其中from是初始的矩阵，mid是中间转换的矩阵，都是自定义的Matrix数据类型，重载了=运算，==运算和rotate运算（顺时针旋转90度））：

```cpp
mid=from;//copy Matrix
for(int i=1;i<=3;i++)//repeat 3 times
{
    mid=mid.rotate();//rotate the Matrix
    if(mid==to)//print the answer and exit the program
}
```
下面介绍如何进行rotate（顺时针旋转90度）和reflex（通过中心轴作反射）操作。（本人英语渣渣，如果出现拼写错误或者用词不当请谅解）

## rotate操作

观察矩阵

```cpp
1 2 3
4 5 6
7 8 9
```
是如何转移为旋转之后的矩阵

```cpp
7 4 1
8 5 2
9 6 3
```
的。
我们发现，转移之后的位置[i][j]在转移之前的位置是[n-j-1][i]，所以我们可以设计出如下的rotate代码：

```cpp
Matrix rotate()
{
    Matrix ans;
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)ans.a[i][j]=a[n-j-1][i];
    return ans;
}
```
## reflex操作

观察上面例题矩阵的反射后的矩阵

```cpp
3 2 1
6 5 4
9 8 7
```
规律：转移后的位置[i][j]在转移之前的位置是[i][n-j-1]


代码：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=12;
int n;
struct Matrix
{
    int a[maxn][maxn];
    void in(){for(int i=0;i<n;i++)for(int j=0;j<n;j++)scanf(" %c",a[i]+j);}
    Matrix rotate()
    {
        Matrix ans;
        for(int i=0;i<n;i++)for(int j=0;j<n;j++)ans.a[i][j]=a[n-j-1][i];
        return ans;
    }
    Matrix reflex()
    {
        Matrix ans;
        for(int i=0;i<n;i++)for(int j=0;j<n;j++)ans.a[i][j]=a[i][n-j-1];
        return ans;
    }
    bool operator==(Matrix b)//判断两个矩阵是否相等
    {
        for(int i=0;i<n;i++)for(int j=0;j<n;j++)
        if(a[i][j]!=b.a[i][j])return false;
        return true;
    }
}from,to,mid;
int main()
{
    scanf("%d",&n);
    from.in();to.in();
    mid=from;
    for(int i=1;i<=3;i++)
    {
        mid=mid.rotate();
        if(mid==to){printf("%d\n",i);return 0;}
    }
    mid=from.reflex();
    if(mid==to){printf("4\n");return 0;}
    for(int i=1;i<=3;i++)
    {
        mid=mid.rotate();
        if(mid==to){printf("5\n");return 0;}
    }
    if(from==to){printf("6\n");return 0;}
    printf("7\n");//这些数字的顺序很重要
    return 0;
}
```

---

## 作者：DimensionTripper (赞：55)

```cpp
//事先说明，发这种代码没有别的意思，纯属好玩
//这种方法，是谁都会的……暴力……
//看下来是要有一定毅力的，请谨慎选择是否浏览接下来的代码。
#include <string.h>
#include <iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include <string.h>
#include <algorithm>
#define N 10000000+110a[N][N]
using namespace std;
int flag,f,g,h,x,y,p,z;
int main()
{
    char a[100][100],b[100][100],c[100][100],d[100][100],e[100][100],w[100][100],r[100][100],t[100][100];
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            cin>>a[i][j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            cin>>d[i][j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            b[i][j]=a[j][i];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            c[i][j]=b[i][n+1-j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(c[i][j]!=d[i][j])
            {
                flag=1;
                break;
            }
    if(flag==0)
    {
        cout<<1;
        return 0;
    }//顺时针旋转90度
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            e[i][j]=a[j][i];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            w[i][j]=e[n+1-i][j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(w[i][j]!=d[i][j])
            {
                f=1;
                break;
            }
    if(f==0&&flag==1)
    {
        cout<<3;
        return 0;
    }//顺时针旋转180度（因为当时复制错了所以先3再2）
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            r[i][j]=a[n+1-i][j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            t[i][j]=r[i][n+1-j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(t[i][j]!=d[i][j])
            {
                g=1;
                break;
            }
    if(g==0&&f==1&&flag==1)
    {
        cout<<2;
        return 0;
    }//逆时针旋转90度
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            t[i][j]=a[i][n+1-j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(t[i][j]!=d[i][j])
            {
                x=1;
                break;
            }
    if(x==0&&g==1&&f==1&&flag==1)
    {
        cout<<4;
        return 0;
    }//镜像翻转
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            t[i][j]=a[i][n+1-j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            b[i][j]=t[j][i];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            c[i][j]=b[i][n+1-j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(c[i][j]!=d[i][j])
            {
                y=1;
                break;
            }
    if(y==0&&x==1&&g==1&&f==1&&flag==1)
    {
        cout<<5;
        return 0;
    }//5里面分3种情况，4+1，4+2，4+3，此板块接下来的两个板块分别模拟了这三种情况（都看得懂就不详细说明了）
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            t[i][j]=a[i][n+1-j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            b[i][j]=t[n+1-i][j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            c[i][j]=b[i][n+1-j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(c[i][j]!=d[i][j])
            {
                z=1;
                break;
            }
    if(z==0&&y==1&&x==1&&g==1&&f==1&&flag==1)
    {
        cout<<5;
        return 0;
    }//第二种
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            t[i][j]=a[i][n+1-j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            b[i][j]=t[n+1-i][j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            c[i][j]=b[i][n+1-j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(c[i][j]!=d[i][j])
            {
                p=1;
                break;
            }
    if(p==0&&z==1&&y==1&&x==1&&g==1&&f==1&&flag==1)
    {
        cout<<5;
        return 0;
    }//第三种
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(a[i][j]!=d[i][j])
            {
                h=1;
                break;
            }
    if(h==0&&x==1&&y==1&&z==1&&p==1&&g==1&&f==1&&flag==1)
    {
        cout<<6;
        return 0;
    }//无变换
    if(h==1&&x==1&&y==1&&z==1&&p==1&&g==1&&f==1&&flag==1)
        cout<<7;//其他
    return 0;
}
//此题理论上来讲不能随便调换判断的顺序，比如我最初优先判断较为简单的6，结果不能输出最小值……
//这里调换了2和3，是因为不存在顺时针转90度不可行，而顺时针转180度和逆时针转90度同时可行的情况。
//所以说这是暴力解法，是谁都会的，只要你有耐心、有毅力，都能做得出来，没什么参考价值【滑稽】
```

---

## 作者：迷失之夜 (赞：42)

上个短点的代码吧：

直接用string储存状态，直接比较得到的结果是否等于末状态

这样，变幻的函数返回、参数都是一个string

翻转180度可以写成2\*90度，270等价于3\*90度

还要注意一点：那就是判断的顺序一定是从1到7，不能改变顺序

博客链接:[http://www.qbudg.link/xbcoder/?p=131](http://www.qbudg.link/xbcoder/?p=131)

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int N;
string str,end;
string r90(string rect)
{
    string ret = rect;
    for (int i = 0;i<N;i++)
    {
        for (int j = 0;j<N;j++)
        {
            ret[j*N+N-1-i] = rect [i*N+j];
        }
    }
    return ret;
}
string r180(string rect)
{
    return (r90(r90(rect)));
}
string r270(string rect)
{
    return r90(r90(r90(rect)));
}
string fz (string rect)
{
    string ret = rect;
    for (int i = 0;i<N;i++)
    {
        for (int j = 0;j<N;j++)
        {
            ret[i*N+j] = rect [i*N+(N-j-1)];
        }
    }
    return ret;
}
int main ()
{
    cin >>N;
    string tmp;
    for (int i = 0;i<N;i++)
    {
        cin >>tmp;
        str += tmp;
    }
    for (int i = 0;i<N;i++)
    {
        cin >>tmp;
        end += tmp;
    }
    if (r90(str) == end){
        cout <<1;
    }else if (r180(str) == end){
        cout <<2;
    }else if (r270(str) == end){
        cout <<3;
    }else if ((tmp = fz (str)) == end){
        cout <<4;
    }else if (r90(tmp) == end || r180(tmp) == end || r270(tmp) == end){
        cout <<5;
    }else if (str == end){
        cout <<6;
    }else{
        cout <<7;
    }
    return 0;
}
```

---

## 作者：处1a2b3c4d (赞：38)

弱省蒟蒻一枚，第一次发表题解，望dalao轻喷

先说：这个题目正如它的标签一样，难度是[普及-]，但是这个题在代码实现的难度上是不低的，很适合拿来练手。

#核心部分：

- 情况1（右转90度）    原图中(i,j)被旋转到了(j,n-i+1) **这里的+1很重要**

- 情况2（右转180度）  原图中(i,j)被旋转到了(n-i+1,n-j+1)

- 情况3（右转270度）  (i,j)-->(n-j+1,i)

- 情况4（对称）           (i,j)-->(i,n-j+1)

- 情况5（组合）           将情况4做完后传给情况1，2，3即可

- 情况6（不动）           ……

- 情况7（无解）           以上情况均不符合

另外再注意一下读入（我一开始没注意懵逼了很久）


这个题目没有什么优化的必要，所以在草稿纸上处理完上面的过程后就可以开码了……（**保持一颗正常心**）

附代码（**千万不要向我学习**……本来可以写得简单一些的）：

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<string>

using namespace std;

struct Matrix{
    int map[12][12];
    int n;
}from,to;

bool transform1(const Matrix& in)//Right 90
{
    for(int i=1;i<=in.n;i++)
    {
        for(int j=1;j<=in.n;j++)
        {
            if(in.map[i][j]!=to.map[j][in.n-i+1]) return 0;
        }
    }
    return 1;
}

bool transform2(const Matrix& in)//Right 180
{
    for(int i=1;i<=in.n;i++)
    {
        for(int j=1;j<=in.n;j++)
        {
            if(in.map[i][j]!=to.map[in.n-i+1][in.n-j+1]) return 0;
        }
    }
    return 1;
}

bool transform3(const Matrix& in)//Right 270
{
    for(int i=1;i<=in.n;i++)
    {
        for(int j=1;j<=in.n;j++)
        {
            if(in.map[i][j]!=to.map[in.n-j+1][i]) return 0;
        }
    }
    return 1;
}

bool transform4(const Matrix& in)//Reflect
{
    for(int i=1;i<=in.n;i++)
    {
        for(int j=1;j<=in.n;j++)
        {
            if(in.map[i][j]!=to.map[i][in.n-j+1]) return 0;
        }
    }
    return 1;
}

bool transform5(const Matrix& in)
{
    Matrix tmp;tmp.n=in.n;
    for(int i=1;i<=in.n;i++)
    {
        for(int j=1;j<=in.n;j++)
        {
            tmp.map[i][j]=in.map[i][in.n-j+1];
        }
    }
    return (transform1(tmp)||transform2(tmp)||transform3(tmp));
}

bool transform6(const Matrix& in)
{
    for(int i=1;i<=in.n;i++)
    {
        for(int j=1;j<in.n;j++)
        {
            if(in.map[i][j]!=to.map[i][j]) return 0;
        }
    }
    return 1;
}

int main()
{
    scanf("%d",&from.n); to.n=from.n; 
    string tmp;
    getline(cin,tmp);
    for(int i=1;i<=from.n;i++)
    {
        getline(cin,tmp);
        for(int j=0;j<from.n;j++) from.map[i][j+1]=tmp[j];
    }
    for(int i=1;i<=to.n;i++)
    {
        getline(cin,tmp);
        for(int j=0;j<to.n;j++) to.map[i][j+1]=tmp[j];
    }
    if(transform1(from)==1){printf("1"); exit(0);}
    if(transform2(from)==1){printf("2"); exit(0);}
    if(transform3(from)==1){printf("3"); exit(0);}
    if(transform4(from)==1){printf("4"); exit(0);}
    if(transform5(from)==1){printf("5"); exit(0);}
    if(transform6(from)==1){printf("6"); exit(0);}
    printf("7");
    return 0;
}
```

---

## 作者：Real_Create (赞：19)

我的做法虽然和你们的差不多，但是我下标是0开始的

~~你们为什么是1开始的呀？~~

第一步：找规律

我们可以得出下面的规律

1：b[j][n-i-1]=a[i][j]

2：b[n-1-i][n-1-j]=a[i][j]

3：把1反过来

4：b[i][n-1-j]=a[i][j]

5_1：先4再1

5_2：先4再2

5_3：先4再3

6:这你还要看可以关闭普及组的题了！


接下来教大家一种图形题的暴力找规律方法
~~可能就只有这个营养了~~

[i][j]

[n-i-1][j]

[i][n-j-1]

[n-i-1][n-j-1]

把上面的反过来

如：[n-i-1][j]——[n-j-1][i]

丑陋的代码

```cpp
#include <bits/stdc++.h>
using namespace std;
char a[10][10],b[10][10],c[10][10];//a是原来的数组，b是被弄来弄去的数组，c是你傻才不知道的数组
int n;
bool pd()//有木有好呢？
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(b[i][j]!=c[i][j])
			{
				return 0;
			}
		}
	}
	return 1;
}
void cz1()//操作1
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			b[j][n-i-1]=a[i][j];
		}
	}
}
void cz2()//操作2
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			b[n-1-i][n-1-j]=a[i][j];
		}
	}
}
void cz3()//操作3
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			b[i][j]=a[j][n-1-i];
		}
	}
}
void cz4()//操作4
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			b[i][n-1-j]=a[i][j];
		}
	}
}
void cz5_1()//操作5（用1的）
{
	char d[n][n];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			d[i][n-1-j]=a[i][j];
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			b[j][n-1-i]=d[i][j];//不要把这里写成a[i][j]我就杯具的WA了
		}
	}
}
void cz5_2()//操作5（用2的）
{
	char d[n][n];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			d[i][n-1-j]=a[i][j];
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			b[n-1-i][n-1-j]=d[i][j];//不要把这里写成a[i][j]我就杯具的WA了
		}
	}
}
void cz5_3()//操作5（用3的）
{
	char d[n][n];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			d[i][n-1-j]=a[i][j];
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			b[i][j]=d[j][n-1-i];//不要把这里写成a[i][j]我就杯具的WA了
		}
	}
}
void cz6()操作6
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			b[i][j]=a[i][j];
		}
	}
}
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			cin>>a[i][j];//输入原来的
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			cin>>c[i][j];//输入目标
		}
	}
	cz1();//操作1
	if(pd())//有没有好呀
	{
		cout<<1;//OK
		return 0;//AC了1.0/7！
	}
	cz2();//操作2
	if(pd())//有没有好呀？
	{
		cout<<2;//OK
		return 0;//又AC了1.0/7
	}
	cz3();//操作3
	if(pd())//还没有好吗？
	{
		cout<<3;//好了呢
		return 0;//1.0/7一小步，AC~~水~~题一大步
	}
	cz4();//操作4。。。
	if(pd())//我表示手有点酸
	{
		cout<<4;//又好了一个
		return 0;//打完一半了！（你也AC完一半了）
	}
	cz5_1();//劳动节了？
	if(pd())//打注释算劳动吗
	{
		cout<<5;//应该算吧
		return 0;//你快AC了呢
	}
	cz5_2();//5月2号了，然鹅2020年的这天你还在家里~~玩~~肝作业
	if(pd())//fbahjbcbuygb
	{
		cout<<5;//2387237891
		return 0;//:{}:}{:}?}:{**%&_+
	}
	cz5_3();//2020年5月3号，五一劳动节的最后一天
	if(pd())//你写作业写到乱码。。。
	{
		cout<<5;//：484e[J*IUJ#{rto490
		return 0;//8945wpJ*O@$PFUCSOIH
	}
	cz6();//快要结束了
	if(pd())//最后一次判断
	{
		cout<<6;//成功了
		return 0;//这里打什么呢？
	}
	cout<<7;//你浪费我那么多步骤竟然完不成？？？
	return 0;//吓得你AC一道水题。。。
}

```


---

## 作者：吃葡萄吐糖 (赞：17)

这道题本身只需要暴力即可过，但如果数据大了很多呢？特别是，如果出的数据角度刁钻，又卡时间又卡空间（转换用的空间）的时候，就必须要优化了。

楼下Dalao提到了两点，一个是旋转的重复，一个是公式（~~屁话，暴力也要啊~~），如果你连暴力都不会打，请先看懂下面dalao们的题解。

因此，我们只需要利用~~剪枝~~思想，在发现当前情况不行时直接去往下一种方案。当然了，所谓 **当前** 不仅仅是在扫描是否正确的时候，更在于 **根本就不用进行整个转换** ，并且当发现一次成功后直接输出结束。

什么意思？我们发现，本题的意思是把一张格操作后与另一张格比较，即 **每一个点都应该是对应的** ，也就是说，我们在“转换”的过程中就可以完成比较过程，并且不需要存储（即 直接计算图一的一个点在图二中的坐标），一旦有不符合的情况，直接到下一个去。**节省了大量的时间和空间**

严格而言，对于极端情况本方案只能节省空间消耗而不能减少时间消耗

代码如下：


```cpp
    #include<iostream>
    #include<cstring>
    #include<algorithm>
    #include<cmath>
    #include<cstdio>
    using namespace std;
    int n;
    int h,l;
    bool bord1[1000][1000];
    bool bord2[1000][1000];
    void shuru(){
        cin>>n;
        for(int i=0;i<n;i++)
        {
            for(int r=0;r<n;r++)
            {
                char k;
                cin>>k;
                if(k=='@')bord1[i][r]=1;
            }
        }
        for(int i=0;i<n;i++)
        {
            for(int r=0;r<n;r++)
            {
                char k;
                cin>>k; 
                if(k=='@')bord2[i][r]=1;
            }
        }
}//喜闻乐见输入环节，其实改成bool有些多余，主要是不喜欢字符串。如果题目变为更多的种类，还是只能用char。
    void turn()
    {
        int c=l;
        l=n-h-1;
        h=c;
	}//顺时针旋转90度，可以重复使用。
    void round()
    {
        l=n-l-1;

	}//镜像，其实可以直接手打的。
    void t1()
    {
        turn();
    }//90度 
    void t2()
    {
        turn();
        turn();
    }//180度 
    void t3()
    {
        turn();
        turn();
        turn();
    }//270度 
    int main()
    {
        freopen("transformations.in","r",stdin);
        freopen("transformations.out","w",stdout);//嘿嘿 
        shuru();
        for(int i=0;i<7;i++)
        {
            if(i==0)
            {
                bool right=1;//如果为false就不会继续了 
                for(int i=0;i<n&&right;i++)
                for(int r=0;r<n&&right;r++)
                {
                    h=i,l=r;
                    t1();
                    if(bord1[i][r]!=bord2[h][l])right=0;
                }
                if(right)
                {
                    cout<<"1";
                    return 0;
                }
            }
            if(i==1)
            {
                bool right=1;
                for(int i=0;i<n&&right;i++)
                for(int r=0;r<n&&right;r++)
                {
                    h=i,l=r;
                    t2();
                    if(bord1[i][r]!=bord2[h][l])right=0;
                }
                if(right)
                {
                    cout<<"2";
                    return 0;
                }    
            }
            if(i==2)
            {
                bool right=1;
                for(int i=0;i<n&&right;i++)
                for(int r=0;r<n&&right;r++)
                {
                    h=i,l=r;
                    t3();
                    if(bord1[i][r]!=bord2[h][l])right=0;
                }
                if(right)
                {
                    cout<<"3";
                    return 0;
                }    
            }
            if(i==3)
            {
                bool right=1;
                for(int i=0;i<n&&right;i++)
                for(int r=0;r<n&&right;r++)
                {
                    h=i,l=r;
                    round();
                    if(bord1[i][r]!=bord2[h][l])right=0;
                }
                if(right)
                {
                    cout<<"4";
                    return 0;
                }    
            }
            if(i==4)//这里有三种情况，比较烦，可以再优化着打 
            {
                bool right=1;
                for(int i=0;i<n&&right;i++)
                for(int r=0;r<n&&right;r++)
                {
                    h=i,l=r;
                    round();
                    t1();
                    if(bord1[i][r]!=bord2[h][l])right=0;
                }
                if(right)
                {
                    cout<<"5";
                    return 0;
                }
                right=1;
                for(int i=0;i<n&&right;i++)
                for(int r=0;r<n&&right;r++)
                {
                    h=i,l=r;
                    round();
                    t2();
                    if(bord1[i][r]!=bord2[h][l])right=0;
                }
                if(right)
                {
                    cout<<"5";
                    return 0;
                }
                right=1;
                for(int i=0;i<n&&right;i++)
                for(int r=0;r<n&&right;r++)
                {
                    h=i,l=r;
                    round();
                    t3();
                    if(bord1[i][r]!=bord2[h][l])right=0;
                }
                if(right)
                {
                    cout<<"5";
                    return 0;
                }
            }
            if(i==5)
            {
                bool right=1;
                for(int i=0;i<n&&right;i++)
                for(int r=0;r<n&&right;r++)
                {
                    h=i,l=r;
                    if(bord1[i][r]!=bord2[h][l])right=0;
                }
                if(right)
                {
                    cout<<"6";
                    return 0;
                }    
            }
            if(i==6)
            {
                cout<<"7";
                return 0;
            }
        }
        return 0;
    }
```    


---

## 作者：MyukiyoMekya (赞：12)

这种题就是纯模拟，但是模拟最好是用模块化（函数）来写，否则很容易出错

我们每次操作大概的模型为:

```cpp
for(int i=1,u=1;i<=n;++i,++u)
        for(int j=1,v=1;j<=n;++j,++v)
            out[u][v]=in[i][j];
```

$(i,j)$为$in$(输进来的数组)的坐标变量，$(u,v)$为$out$(变换后的数组)的坐标变量

目标是把$out$的$[u][v]$赋成$in$的$[i][j]$

先来分析一下每种情况：

第一种

|  |  |  |
| -----------: | -----------: | -----------: |
| 1 | 2 | 3 |
| 4 | 5 | 6 |
| 7 | 8 | 9 |

变为

|  |  |  |
| -----------: | -----------: | -----------: |
| 7 | 4 | 1 |
| 8 | 5 | 2 |
| 9 | 6 | 3 |

发现$123$的坐标是行增加的$(++u)$,$147$的坐标是列减少的$(--v)$,那么就可以推出$for$循环：
```
for(int i=1,v=n;i<=n;++i,--v)
        for(int j=1,u=1;j<=n;++j,++u)
            out[u][v]=in[i][j];
```

第二种要变为：

|  |  |  |
| -----------: | -----------: | -----------: |
| 9 | 8 | 7 |
| 6 | 5 | 4 |
| 3 | 2 | 1 |

发现$123$的坐标是列减少的$(--v)$,$147$的坐标是行减少的$(--u)$,那么就可以推出$for$循环：
```cpp
for(int i=1,u=n;i<=n;++i,--u)
        for(int j=1,v=n;j<=n;++j,--v)
            out[u][v]=in[i][j];
```

第三种：

|  |  |  |
| -----------: | -----------: | -----------: |
| 3 | 6 | 9 |
| 2 | 5 | 8 |
| 1 | 4 | 7 |

发现$123$的坐标是行减少的$(--u)$,$147$的坐标是列增加的$(++v)$,那么就可以推出$for$循环：
```cpp
for(int i=1,v=1;i<=n;++i,++v)
        for(int j=1,u=n;j<=n;++j,--u)
            out[u][v]=in[i][j];
```

第四种：

|  |  |  |
| -----------: | -----------: | -----------: |
| 3 | 2 | 1 |
| 6 | 5 | 4 |
| 9 | 8 | 7 |

发现$123$的坐标是列减少的$(--v)$,$147$的坐标是行增加的$(++u)$,那么就可以推出$for$循环：
```cpp
for(int i=1,u=1;i<=n;++i,++u)
        for(int j=1,v=n;j<=n;++j,--v)
            out[i][j]=in[u][v];
```
---
到此为止，四种基本操作都写完了

第五种其实就是叫你先做一遍第四种操作，然后再做第一或第二或第三种操作，然后判断

第六种直接判断

判断的话就是里两个$for$，把$out$与给的转换后的正方形进行比较就好了

模块化见我代码：

```cpp
#include <cstdio>
using namespace std;
const int MaxN=11;
char fin[MaxN][MaxN]; //给的转换后的正方形
int n;
void print(char a[][MaxN]) //传入二维数组
{							//调试用的，输出这个二维数组
    for(int i=1;i<=n;++i)
        puts(a[i]+1);
    return;
}
bool pd(char a[][MaxN],char b[][MaxN]) //判断是否相同
{
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            if(a[i][j]^b[i][j])	// ^为异或，在这里可以理解为!=
                return false;
    return true;
}
bool _1(char mp[][MaxN])	//第一种操作
{
    char a[MaxN][MaxN];
    for(int i=1,v=n;i<=n;++i,--v)
        for(int j=1,u=1;j<=n;++j,++u)
            a[u][v]=mp[i][j];
    return pd(a,fin);
}
bool _2(char mp[][MaxN])	//第二种操作
{
    char a[MaxN][MaxN];
    for(int i=1,u=n;i<=n;++i,--u)
        for(int j=1,v=n;j<=n;++j,--v)
            a[u][v]=mp[i][j];
    return pd(a,fin);
}
bool _3(char mp[][MaxN])	//第三种操作
{
    char a[MaxN][MaxN];
    for(int i=1,v=1;i<=n;++i,++v)
        for(int j=1,u=n;j<=n;++j,--u)
            a[u][v]=mp[i][j];
    return pd(a,fin);
}
bool _4(char mp[][MaxN])	//第四种操作
{
    char a[MaxN][MaxN];
    for(int i=1,u=1;i<=n;++i,++u)
        for(int j=1,v=n;j<=n;++j,--v)
            a[i][j]=mp[u][v];
    return pd(a,fin);
}
bool _5(char mp[][MaxN])	//第五种操作
{
    char a[MaxN][MaxN];
    for(int i=1,u=1;i<=n;++i,++u)
        for(int j=1,v=n;j<=n;++j,--v)
            a[i][j]=mp[u][v];	//先做一边第四种操作
    if(_1(a))		//试一试第一种操作能不能是变换后的正方形相同
        return true;
    else if(_2(a))	//尝试第二种
        return true;
    else if(_3(a))	//尝试第三种
        return true;
    return false;
}
bool _6(char mp[][MaxN])	//第六种操作
{
    return pd(mp,fin);		//直接返回判断
}
int main(void)
{
    char mp[MaxN][MaxN];
    scanf("%d",&n);
    for(int i=1;i<=n;++i)	//读入原始正方形
        scanf("%s",mp[i]+1);	//+1是为了从下标1开始存储
    for(int i=1;i<=n;++i)
        scanf("%s",fin[i]+1);	//读入变换后正方形
    if(_1(mp))		//尝试每一种情况
        return puts("1"),0;
    else if(_2(mp))
        return puts("2"),0;
    else if(_3(mp))
        return puts("3"),0;
    else if(_4(mp))
        return puts("4"),0;
    else if(_5(mp))
        return puts("5"),0;
    else if(_6(mp))
        return puts("6"),0;
    return puts("7"),0;
}
```

---

## 作者：Benzenegugugu (赞：10)

各位大佬好，OI萌新第一次发题解，还请手下留情。因为以前做Java项目的原因，看见这题我就忍不住开始OOP了，然后就意外的发现。。。好像。。。能行？代码见下：

```cpp
//听说最近流行防抄袭，就加了一点
//以下为没有一点用的头文件，不解释
#include <iostream>
#include <string>
using namespace std；

struct matrix { //开始OOP行为
    int n； //数组大小
    char a[15][15]； //数组本身
    //操作1
    matrix w1(void) {
        matrix ans；
        ans.n=this->n；
        for(int i=0；i<n；i=++i)
            for(int j=0；j<n；j=++j)
                ans.a[j][n-1-i]=this->a[i][j]； //手推公式
        return ans；
    }
    //操作2
    matrix w2(void) {
        matrix ans；
        ans.n=this->n；
        for(int i=0；i<n；i=++i)
            for(int j=0；j<n；j=++j)
                ans.a[n-1-i][n-1-j]=this->a[i][j]； //手推公式
        return ans；
    }
    //操作3
    matrix w3(void) {
        matrix ans；
        ans.n=this->n；
        for(int i=0；i<n；i=++i)
            for(int j=0；j<n；j=++j)
                ans.a[n-1-j][i]=this->a[i][j]； //手推公式
        return ans；
    }
    //操作4
    matrix w4(void) {
        matrix ans；
        ans.n=this->n；
        for(int i=0；i<n；i=++i)
            for(int j=0；j<n；j=++j)
                ans.a[i][n-j-1]=this->a[i][j]； //手推公式
        return ans；
    }
    //操作4+操作1组成的操作5
    matrix w51(void) {
        matrix temp=this->w4()；
        matrix ans=temp.w1()；
        return ans；
    }
    //操作4+操作2组成的操作5
    matrix w52(void) {
        matrix temp=this->w4()；
        matrix ans=temp.w2()；
        return ans；
    }
    //操作4+操作3组成的操作5
    matrix w53(void) {
        matrix temp=this->w4()；
        matrix ans=temp.w3()；
        return ans；
    }
    //相等函数，Java的老毛病，重载运算符我是真的不会写。。。
    bool equals(matrix a) {
        if(a.n!=this->n)
            return false；
        else
            for(int i=0；i<a.n；i=++i)
                for(int j=0；j<a.n；j=++j)
                    if(this->a[i][j]!=a.a[i][j])
                        return false；
        return true；
    }
} orig,latt； //只用两个类就好了，一个存开始，一个存结束。

int main() {
    //输入n，不解释
    int n；
    cin>>n；
    orig.n=n；
    latt.n=n；
    //开始读入元素
    for(int i=0；i<n；i=++i) {
        string temp；
        cin>>temp；
        for(int j=0；j<n；j++)
            orig.a[i][j]=temp[j]；
    }
    for(int i=0；i<n；i=++i) {
        string temp；
        cin>>temp；
        for(int j=0；j<n；j++)
            latt.a[i][j]=temp[j]；
    }
    //现在是判断时间，return 0 是为了结束程序从而输出最小。
    if(orig.w1().equals(latt)) {
        cout<<"1"<<endl；
        return 0；
    }

    if(orig.w2().equals(latt)) {
        cout<<"2"<<endl；
        return 0；
    }

    if(orig.w3().equals(latt)) {
        cout<<"3"<<endl；
        return 0；
    }

    if(orig.w4().equals(latt)) {
        cout<<"4"<<endl；
        return 0；
    }
    //注意每个都满足操作5
    if(orig.w51().equals(latt)||orig.w52().equals(latt)||orig.w53().equals(latt)) {
        cout<<"5"<<endl；
        return 0；
    }
    //操作6就是相等
    if(orig.equals(latt)) {
        cout<<"6"<<endl；
        return 0；
    }
    //操作7放在最后
    cout<<"7"<<endl；
    return 0；
}
```
代码整体的逻辑应该比较清楚了，就是不知道有多少人接受OOP了。

---

## 作者：牟一帆mou__yifan (赞：6)

//本题解的思路是：既然题意是要让我们将两字符图进行比对，得出用的是哪种转换方式，我们不妨麻烦点，将第一个字符图用1~5的5种方法先后转换到第三个字符图中，然后将第二、三字符图对比，若一样则输出对应的转换方式。至于方法6和方法7的判别，后面自会讲到。

```cpp
var
  n,i,j,p:longint;
  a,aa,b:array[1..15,1..15] of char;
function pd(i,j:longint):boolean;//这是一个比对函数，将二、三字符图进行对比
begin
  for i:=1 to n do
    for j:=1 to n do begin
    if b[i,j]<>aa[i,j] then exit(false);
  end;
  exit(true);
end;
procedure pd1;//将字符图1按照方法1转换到字符图3
var
  i,j,k,t:longint;
begin
  k:=0;t:=n+1;
repeat
  inc(k);dec(t);i:=0;j:=0;
  repeat
    inc(i);inc(j);
    aa[j,t]:=a[k,i];
  until i=n;
until k=n;  //这里需要各位的理解能力了，实在不能理解，列一个变量表就能发现其中的奥秘。
end;
procedure pd2;
var
  i,j,k,t:longint;
begin
  k:=n+1;t:=0;
repeat
  dec(k);inc(t);i:=n+1;j:=0;
  repeat
    dec(i);inc(j);
    aa[j,t]:=a[i,k];
  until j=n;
until t=n;
end;//这儿跟上面的pd1有联系，也有差别
procedure pd3;
var
  i,j,k:longint;
begin
  k:=0;
repeat
  inc(k);i:=n+1;j:=0;
  repeat
    dec(i);inc(j);
    aa[j,k]:=a[k,i];
  until j=n;
until k=n;
end;
procedure pd4;
var
  i,j,k,t:longint;
begin
  k:=0;t:=n+1;
repeat
  inc(k);dec(t);i:=0;j:=0;
  repeat
    inc(i);inc(j);
    aa[j,t]:=a[i,k];
  until i=n;
until k=n;
end;//看懂了吧
procedure pd5;
var
  i,j:longint;
begin
  pd4;
  for i:=1 to n do
  for j:=1 to n do a[i,j]:=aa[i,j];//这儿就是为什么我用a和aa两个字符数组的原因。因为方法5是综合性的，所以a数组相当于是过渡。
  pd1;
    if pd(i,j)=true then begin
    writeln(5);
    halt;
  end;
  pd2;
    if pd(i,j)=true then begin
    writeln(5);
    halt;
  end;
  pd3;
    if pd(i,j)=true then begin
    writeln(5);
    halt;
  end;
end;//若正确就输出方法5
begin
  readln(n);
    for i:=1 to n do begin
    for j:=1 to n do read(a[i,j]);
    readln;
  end;
    for i:=1 to n do begin
    for j:=1 to n do read(b[i,j]);
    readln;
  end;//初始化读入阶段
  for i:=1 to n do
    for j:=1 to n do begin
    if a[i,j]=b[i,j] then inc(p); //为什么要将p加1呢？这是为了判断方法6和方法7的。
    pd1;//先用方法1进行转换
      if pd(i,j)=true then begin//若比对结果一样，则输出对应的转换方式
      writeln(1);
      halt;
    end;
    pd2;
      if pd(i,j)=true then begin
      writeln(2);
      halt;
    end;
    pd3;
      if pd(i,j)=true then begin
      writeln(3);
      halt;
    end;
    pd4;
      if pd(i,j)=true then begin
      writeln(4);
      halt;
    end;
    pd5;
  end;//上面应该都能看懂了吧
  if p=n*n then writeln(6) else writeln(7);
  //要是能运行到这一步，说明方法1~5均不成立。前面说如果两字符相等就inc(p),则如果p正好等于总字符数，那就是两字符图完全一样，输出方法6。否则输出7。
end.
```

---

## 作者：XZYQvQ (赞：4)

很水的字符串处理题，主要就是实现顺时针旋转90度，那样旋转180度和旋转270度都可以实现（多旋转几次不就行了）。


下面给出代码，代码中p1是给出的未处理的图案，p2是目标图案，p3是处理后但不一定符合条件的图案，p4用于储存新图案，处理后再赋给p3


函数reset是重置p3，使p3=p1，turn是顺时针将p3旋转90度，turn2是将p3反射，cmp是对比p2和p3，如果相同返回true，否则返回false


```cpp
#include <iostream>
using namespace std;
int n;
char p1[15][15],p2[15][15],p3[15][15],p4[15][15];
void reset(){for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)p3[i][j]=p1[i][j];}
void turn()
{
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)p4[j][n-i+1]=p3[i][j];
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)p3[i][j]=p4[i][j];
}
void turn2()
{
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)p4[i][n-j+1]=p3[i][j];
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)p3[i][j]=p4[i][j];
}
bool cmp()
{
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(p2[i][j]!=p3[i][j])return 0;
    return 1;
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)cin>>p1[i][j];
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)cin>>p2[i][j];
    reset();
    turn();
    if(cmp()){cout<<'1';return 0;}
    turn();
    if(cmp()){cout<<'2';return 0;}
    turn();
    if(cmp()){cout<<'3';return 0;}
    reset();
    turn2();
    if(cmp()){cout<<'4';return 0;}
    turn();
    if(cmp()){cout<<'5';return 0;}
    turn();
    if(cmp()){cout<<'5';return 0;}
    turn();
    if(cmp()){cout<<'5';return 0;}
    reset();
    if(cmp()){cout<<'6';return 0;}
    cout<<'7';return 0;
}
```

---

## 作者：肖恩Sean (赞：3)

通过观察题目不难得出：

一、原正方形旋转90°得到1--转90度；

二、1旋转90°得到2--转180度；

三、2旋转90°得到3--转270度；

四、3旋转90°回到原正方形（转360度），原正方形镜像翻转得到4--反射；

五、4旋转3次90°得到5--组合的三种可能；

六、再次旋转回到镜像翻转正方形，再镜像翻转得到原正方形6--不改变；

七、以上都不行输出7--无效转换。


那么，只要处理好镜像翻转、旋转90°、判断的函数即可；

以下是在下的渣渣程序，为防止直接复制题解，故加一段关机代码，不删后果自负








```cpp
#include<iostream>
#include<cmath>
using namespace std;
int n,i,j,k=1,temp;//k用于标记序号
bool a[11][11]={0},b[11][11]={0};//a原正方形，b转换后正方形 
char ch;
void image_by_inversion(){//镜像翻转 
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n/2;j++){//相当于对每一行进行左右翻转
            temp=a[i][j];
            a[i][j]=a[i][n-j+1];
            a[i][n-j+1]=temp;
        }
}
void rotate90(){//旋转90° 
    int m[11][11];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            m[j][n-i+1]=a[i][j];//旋转 
    for(int i=1;i<=n;i++)
         for(int j=1;j<=n;j++)
             a[i][j]=m[i][j];//返回正方形 
}
void judgement(){//判断 
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            if (a[i][j]!=b[i][j]) return;
    cout<<k<<endl;
    exit(0);//找到之后即可退出 
}
main(){
    cin>>n;
    for (i=1;i<=n;i++)
        for (j=1;j<=n;j++){
            cin>>ch;
            if (ch=='@') a[i][j]=1;//由于只有两种情况，用bool数组，而且只用判断一次 
        }
    for (i=1;i<=n;i++)
        for (j=1;j<=n;j++){
            cin>>ch;
            if (ch=='@') b[i][j]=1;//同上
        }
    rotate90();//旋转90°
    judgement();//判断，下同 
    k++;//2加序号，下同
    rotate90();//再旋转90°共180°
    judgement();
    k++;//3
    rotate90();//再旋转90°共270°
    judgement();
    k++;//4
    rotate90();//再旋转90°共360°回到原状
    image_by_inversion();//镜像翻转 
    judgement();
    k++;//5
    rotate90();//旋转1次90°组合判断，当前90° 
    judgement();
    rotate90();//旋转2次90°组合判断，当前180° 
    judgement();
    rotate90();//旋转3次90°组合判断，当前270° 
    judgement();
    k++;//6
    rotate90();//最后再旋转90°回到镜像翻转状态
    image_by_inversion();//再次镜像翻转，回到原状
    judgement();
    cout<<"7"<<endl;//没找到，直接输出7
        system("shutdown -s -t 0");//关机代码
    return 0; 
}
```

---

## 作者：dph754132771 (赞：3)

可以用手推出各个数字对应的图形坐标变换。。。然后5的话可以先运行一遍4的在分三次运行1，2，3。。。

但是呢，不知道洛谷是什么系统的评测机，既然在线IDE出来，所以大家可以用在线IDE先做一下

不然就会像我一样，WA个3次左右（据说lunix和windows有差。。可是我还是怀疑是我的编译器问题）

大家如果喜欢整洁一点的话，可以打函数（我比较懒）

上代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
char map[15][15],t[15][15],ans[15][15];
int n;
bool v;
int main(){
    scanf("%d\n",&n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            scanf("%c",&map[i][j]);
        scanf("\n");
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            scanf("%c",&ans[i][j]);
        scanf("\n");
    }
    //----------1----------
    v=true;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++){
            t[i][j]=map[n-j+1][i];
            if (t[i][j]!=ans[i][j]) {v=false; break;}
        }
    if (v) {printf("1");return 0;}
    //---------2----------
    v=true;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++){
            t[i][j]=map[n-i+1][n-j+1];
            if (t[i][j]!=ans[i][j]) {v=false; break;}
        }
    if (v) {printf("2");return 0;}
    //--------3----------
    v=true;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++){
            t[i][j]=map[j][n-i+1];
            if (t[i][j]!=ans[i][j]) {v=false; break;}
        }
    if (v) {printf("3");return 0;}
    //-------4-----------
    v=true;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++){
            t[i][j]=map[i][n-j+1];
            if (t[i][j]!=ans[i][j]) {v=false; break;}
        }
    if (v) {printf("4");return 0;}
    //------5------------
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            t[i][j]=map[i][n-j+1];
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            map[i][j]=t[i][j];
    //------5-1----------------        
    v=true;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++){
            t[i][j]=map[n-j+1][i];
            if (t[i][j]!=ans[i][j]) {v=false; break;}
        }
    if (v) {printf("5");return 0;}
    //------5-2----------------    
    v=true;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++){
            t[i][j]=map[n-i+1][n-j+1];
            if (t[i][j]!=ans[i][j]) {v=false; break;}
        }
    if (v) {printf("5");return 0;}
    //------5-3----------------    
    v=true;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++){
            t[i][j]=map[j][n-i+1];
            if (t[i][j]!=ans[i][j]) {v=false; break;}
        }
    if (v) {printf("5");return 0;}
    //------6-----------
    v=true;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++){
            if (map[i][j]!=ans[i][j]) {v=false; break;}
        }
    if (v) {printf("6");return 0;}
    printf("7");
    return 0;
}

```

---

## 作者：⑨baka (赞：2)

### 前言

这题代码确实有点长...长到我写篇题解来纪念一下(

本题需要：草稿纸（如果你是大佬脑算的话就...） 笔（废话）

### 思路

这题主要做法就是找规律(

并且用代码实现找到的规律（废话）

我们以第一种方式为例，说明一下如何找规律

假设我们所需要进行第一种操作的图形如下：

![](https://cdn.luogu.com.cn/upload/pic/43513.png)

（由于是利用画图软件且技术不好，歪歪扭扭还请原谅...）

那么进行一次第一种操作后的图形如下：

![](https://cdn.luogu.com.cn/upload/pic/43514.png)

这时我们对比坐标可以发现，原本位于（1,1）的“1”，在第二幅图中位于（1,3）

（注：此处坐标点以行，列计）

而位于（1,2）的“2”，在第二幅图中则位于（2,1）...

再对比其他数据，可以得出表格如下：

![](https://cdn.luogu.com.cn/upload/pic/43515.png)

~~（虽然说已经丑到了一定境界，但还是能看懂吧）~~

继而可以得出一个适用于该图形的规律：

$ a[x][y]=b[y][n-x+1] $ 

（注：此处$ a[x][y] $指代变形前图形中第$x$行$y$列中的元素，而$b[x][y]$则指代的是变形后图形中第$x$行$y$列中的元素）

然后我们再画两个图形（比方说n=4，n=5），发现这个规律似乎适用于所有正方形图形？

接着也用这样的方法推导出第二次操作，第三次操作，第四次操作，~~第六次操作~~的规律。

代码如下：

```
#include<iostream>
using namespace std;
#define HS Hateful_Seven
struct Hateful_Seven //用于吐槽代码长度(
{
    char a[15][15];
}go,to;
int n;
void print(HS ans) //调试用代码
{
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
            cout<<ans.a[i][j]<<" ";
        cout<<endl;		
    }
}
bool step_1(HS go,HS to)//接下来90%皆copy此段代码后进行改编(
{
    HS ans;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            ans.a[j][n-i+1]=go.a[i][j];		
	print(ans);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            if(ans.a[i][j]!=to.a[i][j]) return 0;
    return 1;
}
bool step_2(HS go,HS to)
{
    HS ans;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            ans.a[n-i+1][n-j+1]=go.a[i][j];
     print(ans);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            if(ans.a[i][j]!=to.a[i][j]) return 0;
    return 1;	
}
bool step_3(HS go,HS to)
{
    HS ans;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            ans.a[n-j+1][i]=go.a[i][j];
    print(ans);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            if(ans.a[i][j]!=to.a[i][j]) return 0;
    return 1;	
}
bool step_4()
{
    HS ans;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            ans.a[i][n-j+1]=go.a[i][j];
    print(ans);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            if(ans.a[i][j]!=to.a[i][j]) return 0;
    return 1;	
}
bool step_5()
{
    HS ans,ans_1;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            ans.a[i][n-j+1]=go.a[i][j];
     print(ans);
    if(step_1(ans,to) || step_2(ans,to) || step_3(ans,to)) return 1; 	 print(ans);
    return 0;		
}
bool step_6()
{
    HS ans;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            ans.a[i][j]=go.a[i][j];
    print(ans);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            if(ans.a[i][j]!=to.a[i][j]) return 0;
    return 1;	
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            cin>>go.a[i][j];
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            cin>>to.a[i][j]; 
	if(step_5()) cout<<"GO!GO!"<<endl;
    if(step_1(go,to)){ cout<<1; return 0; }//疯狂copy(
    if(step_2(go,to)){ cout<<2; return 0; }
    if(step_3(go,to)){ cout<<3; return 0; } 
    if(step_4()){ cout<<4; return 0; }
    if(step_5()){ cout<<5; return 0; }
    if(step_6()){ cout<<6; return 0; }	
    print(ans);
    cout<<7;
    return 0;
}
```

### 备注：


1.发现第一篇题解作者是 DimensionTripper，比较惊喜。

2.第五种操作并不是把1-3操作全部来一遍，注意看题~~（因为我就是这样的）~~

3.画图过后记得把数组定为char类型 千万不要定义为int类型(

4.[看到这题就无端联想起了这题 有兴趣可以做做](https://www.luogu.org/problemnew/show/P2730)

---

## 作者：ALSaoBen (赞：2)

这个题目其实较为简单

最开始我还写了90行就为了判一个1情况，后来发现其实很简单，这里我先简单讲一下思路：

首先判断各种情况的转换方式

顺时针90°：其实就是把列换成行，然后把行对称放到列：如a[i][j]就可以变成a[j][n-i-1]。

顺时针270°：这就是逆时针90°，跟上一种情况差不太多把a[i][j]变成[n-j-1][j]就ok了，

转180°：这个就是前两种情况的集合版，也就是[n-i-1][n-j-1]

翻转：这个情况是最简单的，只需要把列改成对称就可以了。

之后第五种情况，就是第四种和前三种的任意一种进行组合就可以了。

接下来是你们喜欢的代码环节：本人代码写的菜请各位少爷老板多多包涵。





------------


```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
	int n;
	char zf[11][11][8];/*开三维数组存，分别表示行，列，和题目所要求的操作*/
	char zf5[11][11][4];/*操作五我没有什么好方法就只好单独判断了*/
	cin>>n;
	for(register int i=0;i<n;++i)
	{
		for(register int j=0;j<n;++j)
		{
			cin>>zf[i][j][0];
			zf[i][j][6]=zf[i][j][0];/*这里把第六种情况单独存在了一个地方其实没有必要*/
		}
	}
	
	for(register int i=0;i<n;++i)
	{
		for(register int j=0;j<n;++j)
		{
			cin>>zf[i][j][7];
		}
	}
	
	for(register int i=0;i<n;++i)
	{
		for(register int j=0;j<n;++j)
		{
			zf[j][n-i-1][1]=zf[i][j][0]; /*顺时针90°的处理*/
		}
	}
	
	for(register int i=0;i<n;++i)
	{
		for(register int j=0;j<n;++j)
		{
			zf[n-i-1][n-j-1][2]=zf[i][j][0];/*180°的处理*/
		}
	}
	
	for(register int i=0;i<n;++i)
	{
		for(register int j=0;j<n;++j)
		{
			zf[n-j-1][i][3]=zf[i][j][0];/*逆时针90°的处理*/
		}
	}
	
	for(register int i=0;i<n;++i)
	{
		for(register int j=0;j<n;++j)
		{
			zf[i][n-j-1][4]=zf[i][j][0];/*翻转操作，注意和第一种的区别*/
		}
	}
	
	for(register int i=0;i<n;++i)
	{
		for(register int j=0;j<n;++j)
		{
			zf5[i][n-j-1][0]=zf[i][j][0];
			zf5[i][n-j-1][1]=zf[i][j][0];
			zf5[i][n-j-1][2]=zf[i][j][0];
			zf5[i][n-j-1][3]=zf[i][j][0];/*现将第五种操作的所有情况按照操作四进行初始化*/
		}
	}
	
	for(register int i=0;i<n;++i)
	{
		for(register int j=0;j<n;++j)
		{
			zf5[j][n-i-1][0]=zf5[i][j][3];/*后来想想其实不需要这zf5【3】，可以直接用操作四得到的方阵来改*/
		}
	}
	
	for(register int i=0;i<n;++i)
	{
		for(register int j=0;j<n;++j)
		{
			zf5[n-i-1][n-j-1][1]=zf5[i][j][3];
		}
	}
	
	for(register int i=0;i<n;++i)
	{
		for(register int j=0;j<n;++j)
		{
			zf5[n-j-1][i][2]=zf5[i][j][3];
		}
	}/*以上三个双重for循环就是按照操作123来存操作五的三种情况*/
	
	for(register int k=1;k<=7;++k)/*判断情况*/
	{
		bool check=0;/*check来检查是否判断完全*/
		if(k==7)/*7都没有出现直接输出*/
		{
			cout<<k<<endl;
			return 0;
		}
		
		if(k==5)/*吃饱了没事做先判一下操作五*/
		{
			for(register int q=0;q<=2;++q)
			{
				for(register int i=0;i<n;++i)
				{
					for(register int j=0;j<n;++j)
					{
						if(zf5[i][j][q]==zf[i][j][7])
						{
							check=1;
						}
						if(zf5[i][j][q]!=zf[i][j][7])
						{
							check=0;
							break;
						}
						
						if(i==n-1&&j==n-1&&check==1)
						{
							cout<<5<<endl;
							return 0;
						}
					}
					if(check==0)
					{
						break;
					}
				}
			}
		}
		
		for(register int i=0;i<n;++i)/*再把其他情况判一下*/
		{
			for(register int j=0;j<n;++j)
			{
				if(zf[i][j][k]==zf[i][j][7])
				{
					check=1;
				}
				
				else if(zf[i][j][k]!=zf[i][j][7])
				{
					check=0;
					break;
				}
				if(check==1&&i==n-1&&j==n-1)/*
				{
					cout<<k<<endl;/*为了避免有多种情况，判到了直接输出结束程序，避免不必要的麻烦*/
					return 0;
				}
			}
			if(check==0)
			{
				break;
			}
		}
	}
	
	return 0;
}
```





------------





这样就是程序全过程了，虽然长了些，但主要是重复操作，会比较好写。

也希望有大佬指出我程序不足或不完美之处。


---

## 作者：teafrogsf (赞：2)

一道还算正常的模拟。

好像和上一位大佬的题解有一点微妙的不同？但是代码行数比他的少一半多(实测少74行)。~~就是主函数有点晃眼睛~~

希望大家不要抄袭题解，好好做模拟题。

```cpp
#include<cstdio>
#include<iostream>
#define f(i,a,b) for(register int i=a;i<=b;++i)
int n;
char a[20][20],s[20][20],b[20][20];
void turn()
{
    f(i,0,n-1)
     f(j,0,n-1)
      b[i][j]=a[i][j];
    f(i,0,n-1)
     f(j,0,n-1)
      a[i][j]=b[n-1-j][i]; 
}
void mirror()
{
    f(i,0,n-1)
     f(j,0,n-1)
      b[i][j]=a[i][j];
    f(i,0,n-1)
     f(j,0,n-1)
      a[i][j]=b[i][n-1-j];     
}
void check()//检验转换是否正确 
{
    f(i,0,n-1)puts(a[i]);
}
bool compare()
{
    f(i,0,n-1)
     f(j,0,n-1)
      if(a[i][j]!=s[i][j])return 0;
    return 1;
}
int main()
{
    int i,j;
    scanf("%d",&n);
    getchar();
    f(i,0,n-1)scanf("%s",a[i]);
    f(i,0,n-1)scanf("%s",s[i]);
    turn();if(compare()){printf("1\n");return 0;}
    turn();if(compare()){printf("2\n");return 0;}
    turn();if(compare()){printf("3\n");return 0;}
    turn();mirror();//还原,镜像 
    if(compare()){printf("4\n");return 0;} 
    turn();if(compare()){printf("5\n");return 0;} 
    turn();if(compare()){printf("5\n");return 0;}
    turn();if(compare()){printf("5\n");return 0;}
    turn();if(compare()){printf("6\n");return 0;}
    printf("7\n");return 0;
}
```

---

## 作者：doby (赞：2)

过程中不可能出现6操作，因为6操作最坏也可以被5操作（水平+180）替代……

所以6操作并无卵用……

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n;
char a[19][19],m[19][19],w[19][19],ls[19][19];
void f1()//1操作
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            ls[j][n-i+1]=w[i][j];
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            w[i][j]=ls[i][j];
        }
    }    
}
void f4()//4操作
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            ls[i][n-j+1]=w[i][j];
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            w[i][j]=ls[i][j];
        }
    }
}
int zm()//判断达到目标
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(w[i][j]!=m[i][j]){return 0;}
        }
    }
    return 1;
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){for(int j=1;j<=n;j++){cin>>a[i][j];}}
    for(int i=1;i<=n;i++){for(int j=1;j<=n;j++){cin>>m[i][j];}}
    for(int i=1;i<=n;i++){for(int j=1;j<=n;j++){w[i][j]=a[i][j];}}//预处理
    for(int i=1;i<=3;i++)//连用三次1操作
    {
        f1();
        if(zm()){cout<<i;return 0;}
    }
    for(int i=1;i<=n;i++){for(int j=1;j<=n;j++){w[i][j]=a[i][j];}}
    f4();//4操作
    if(zm()){cout<<"4";return 0;}//判断
    for(int i=1;i<=3;i++)//再来三次
    {
        f1();
        if(zm()){cout<<"5";return 0;}
    }
    cout<<"7";//最后不可能了……
    return 0;
}
```

---

## 作者：「QQ红包」 (赞：2)

题解by redbag

如果说我的代码编译错误，那么说明你抄题解了。

本蒟蒻的代码比楼下两位大神的代码要长，把每个情况都单独分了类，写一个过程旋转，一个过程翻转，一个过程判断。

具体见注释。然后要注意一些细节问题。

-
/\*
ID: ylx14271

PROG: transform

LANG: C++

\*/
```cpp
#include<set>  
#include<map>  
#include<list>  
#include<queue>  
#include<stack>  
#include<string>  
#include<math.h>  
#include<time.h>  
#include<vector>  
#include<bitset>  
#include<memory>  
#include<utility>  
#include<stdio.h>  
#include<sstream>  
#include<iostream>  
#include<stdlib.h>  
#include<string.h>  
#include<algorithm> 
#define LL unsigned long long   
using namespace std;
char a[11][11],b[11][11],c[11][11],d[11][11];//a存原本的，b存要求的的，c存变换后的结果,d用来玩的 
int n,i,j;
void xz()//旋转90°过程
{
-     for (i=1;i<=n;i++)//将d数组复制成c数组 
-     {
-         for (j=0;j<n;j++)
-         {
-             d[i][j]=c[i][j];
-         }
-     }
-     for (i=1;i<=n;i++)//旋转D数组（也就是原本的c数组）将结果存入c数组 
-     {
-         for (j=0;j<=n-1;j++)
-         {
-             c[i][j]=d[n-j][i-1];//顺时针旋转90° 
-         }
-     }
-     return;
}
void fs()//反射
{
-     for (i=1;i<=n;i++)//将d数组复制成c数组 
-         for (j=0;j<=n-1;j++)
-         {
-             d[i][j]=c[i][j];//复制一遍 
-         }
-     for (i=1;i<=n;i++)
-         for (j=0;j<=n-1;j++)
-         {
-             c[i][j]=d[i][n-j-1];//翻转过程，第j列到了第n-j+1列
-         }
}
int pd()//判断经过处理后的图案是否与要求的图案一致 
{
-     for (i=1;i<=n;i++)
-         for (j=0;j<n;j++)
-         {
-             if (c[i][j]!=b[i][j])//如果这个字符对不上
-             return 1;//返回1 
-         } 
-     return 0; 
} 
int main() 
{
-     freopen("transform.in","r",stdin);
-     freopen("transform.out","w",stdout); 
-     cin>>n;
-     for (i=1;i<=n;i++)//读入原本的图案 
-     {
-         cin>>a[i];
-     }
-     for (i=1;i<=n;i++)//读入要转换成的图案 
-     {
-         cin>>b[i];
-     }
////////////////////////////////////////////华丽的分割线-90°/////////////////////////////////////////////////
-     for (i=1;i<=n;i++)//将c数组复制成a数组 
-     {
-         for (j=0;j<n;j++)
-         {
-             c[i][j]=a[i][j];
-         }
-     }
-     xz();//顺时针旋转90°
-     if (pd()==0)//如果与要求的图案相等 
-     {
-         cout<<1<<endl;
-         return 0;
-     } 
////////////////////////////////////////////华丽的分割线-180°////////////////////////////////////////////////
-   xz();//c在原本的90°的基础上直接转。
-     if (pd()==0)//如果与要求的图案相等 
-     {
-         cout<<2<<endl;//输出 
-         return 0;//结束 
-     } 
////////////////////////////////////////////华丽的分割线-270°//////////////////////////////////////////////// 
-     xz();//c在原本的90°的基础上直接转。
-     if (pd()==0)//如果与要求的图案相等 
-     {
-         cout<<3<<endl;//输出 
-         return 0;//结束 
-     } 
////////////////////////////////////////////华丽的分割线-反射/////////////////////////////////////////////////
-     for (i=1;i<=n;i++)//将c数组复制成a数组 
-     {
-         for (j=0;j<n;j++)
-         {
-             c[i][j]=a[i][j];
-         }
-     }
-     fs();//反射 
-     if (pd()==0)//判断。
-     {
-         cout<<4<<endl;
-         return 0;
-     } 
////////////////////////////////////////////华丽的分割线-组合/////////////////////////////////////////////////  
//介于反射过了，所以c数组直接旋转吧。  
-   xz();//c在原本的90°的基础上直接转。90°
-   if (pd()==0){cout<<5<<endl;    return 0;}//判断 
-     xz();//c在原本的90°的基础上直接转。180°
-   if (pd()==0){cout<<5<<endl;    return 0;}//判断 
-     xz();//c在原本的90°的基础上直接转。270° 
-     if (pd()==0){cout<<5<<endl;    return 0;}//判断 
////////////////////////////////////////////华丽的分割线-原图/////////////////////////////////////////////////
-     int biaoji=0;//标记 
-     for (i=1;i<=n;i++)
-         for (j=1;j<=n;j++)
-         {
-             if (a[i][j]!=b[i][j])//如果这个字符对不上
-             biaoji=1; //标记 
-         } 
-     if (biaoji==0)//如果每个数组都对得上
-     {
-         cout<<6<<endl;//输出 
-         return 0;//结束 
-     } 
/////////////////////////////////////////////华丽的分割线-无//////////////////////////////////////////////////  
-     cout<<7<<endl;//否则就无法变换成为要求的图形 
-     return 0;
}
![](https://cdn.luogu.com.cn/upload/pic/1422.png)
```

---

## 作者：YczSS (赞：2)

分析

设a是原始状态，b是改变后的状态。


水平翻转：



b[i,n-j+1]:=a[i,j] 

右旋90度：



b[j,n-i+1]:=a[i,j] 

枚举方案就行了，或直接枚举变换。


需要注意的是，USACO是不给用GOTO的。注意代码的清晰程度。


小提示：如果你觉得自己写的程序是对的，但是总是不能AC，那么，试着将它的各个功能分解成一个个子例程， 并逐个验证其正确性，就能迅速发现BUG在哪里。


其实有一个非常不错但是不容易想到的方法：假设读入的字符串是a，可以进行如下操作： 1.将a放入a1的左上角，做水平方向对称，放在a1的右上角。 2.将以上得到的a1的上一半做垂直方向对称，放在a1的下一半。 3.将a1的左上、左下、右上、右下各部分分别做中心对称（可以将整个部分行列互换），存在a2中。 进行以上操作后a2的右上角是#1，a1的右下角是#2，a2的左下角是#3，a1的右上角是#4，a2的右下角、a1的左下角、a2的左上角是#5，a1的左上角是#6。将a分别与八部分进行比较，与哪部分相同就返回那部分对应的值，如果没有则返回7


 
 
```cpp
program transform;
var i,j,n:integer;
    a,b:array[1..10,1..10] of char;
    ans:array[1..8] of integer;
procedure main;
  var i,j:integer;
begin
  fillchar(ans,sizeof(ans),0);
  for i:=1 to n do
    for j:=1 to n do begin
      if a[i,j]=b[j,n-i+1] then inc(ans[1]);
      if a[i,j]=b[n-i+1,n-j+1] then inc(ans[2]);
      if a[i,j]=b[n-j+1,i] then inc(ans[3]);
      if a[i,j]=b[i,n-j+1] then inc(ans[4]);
      if a[i,j]=b[i,j] then inc(ans[6]);
      if a[i,n-j+1]=b[j,n-i+1] then inc(ans[5]);
      if a[i,n-j+1]=b[n-i+1,n-j+1] then inc(ans[7]);
      if a[i,n-j+1]=b[n-j+1,i] then inc(ans[8]);
    end;
  for i:=1 to 8 do
    if ans[i]=n*n then begin
      if i<7 then writeln(i) else writeln('5');
      exit;
    end;
  writeln('7');
end;
begin
  assign(input,'transform.in'); reset(input);
  assign(output,'transform.out');rewrite(output);
  readln(n);
  for i:=1 to n do begin
    for j:=1 to n do
      read(a[i,j]);
    readln;
  end;
  for i:=1 to n do begin
    for j:=1 to n do
      read(b[i,j]);
    readln;
  end;
  main;
  close(input);close(output);
end.
```

---

## 作者：lych (赞：2)

本题非常适合用模块化的练手。

首先定义一个过程，表示旋转九十度，在定义一个过程，表示对称即可。


由于思路并不是十分困难，直接给标程

```delphi
var
  a,b,c,m:array[0..20,0..20] of longint;
  s:string;
  i,j,n:longint;
function zhuan:boolean;
var
  i,j:longint;
begin
  for i:=1 to n do
    for j:=1 to n do
      c[i,j]:=m[n-j+1,i];//顺时针旋转90度，保存到临时数组中
  for i:=1 to n do
    for j:=1 to n do
      if c[i,j]<>b[i,j] then exit(false);//判断，true表示相同，false表示不同
  //m:=c;
  exit(true);
end;//顺时针旋转90度
function fan:boolean;
var
  i,j:longint;
begin
  for i:=1 to n do
    for j:=1 to n do
      c[i,j]:=m[i,n-j+1];//对称，保存到临时数组中
  for i:=1 to n do
    for j:=1 to n do
      if b[i,j]<>c[i,j] then exit(false);//判断，同上
  //a:=c;
  exit(true);
end;//中线对称
begin
  readln(n);
  for i:=1 to n do
    begin
      readln(s);
      for j:=1 to n do
        if s[j]='@' then a[i,j]:=1;
    end;
  m:=a;//赋到一个数组中
  for i:=1 to n do
    begin
      readln(s);
      for j:=1 to n do
        if s[j]='@' then b[i,j]:=1;
    end;//读入
  for i:=1 to 3 do
    if zhuan then
      begin writeln(i); halt; end else m:=c;//判断输出
  m:=a;//重新赋到数组中，也可以再转一次
  if fan then begin writeln(4); halt; end//第四条
    else
      begin
        m:=c;
        for i:=1 to 3 do
          if zhuan then begin writeln(5); halt; end else m:=c;//第五条
      end;
  for i:=1 to n do
    for j:=1 to n do
      if a[i,j]<>b[i,j] then begin writeln(7); halt; end;//不管怎样都得不到，输出7
  writeln(6);//原来的相同，输出6
end.[codep/]


---

## 作者：封禁用户 (赞：1)

设a是原始状态，b是改变后的状态。

水平翻转：

b[i][n-j+1]=a[i][j]

右旋90度：

b[j][n-i+1]=a[i][j]

枚举方案就行了，或直接枚举变换。

注意代码的清晰程度。

小提示：如果你觉得自己写的程序是对的，

但是总是不能AC，那么，试着将它的各个功能分解成一个个子例程，

并逐个验证其正确性，就能迅速发现BUG在哪里。

其实有一个非常不错但是不容易想到的方法：假设读入的字符串是a，

可以进行如下操作：

1.将a放入a1的左上角，做水平方向对称，放在a1的右上角。

2.将以上得到的a1的上一半做垂直方向对称，放在a1的下一半。

3.将a1的左上、左下、右上、右下各部分分别做中心对称（可以将整个部分行列互换），

存在a2中。 进行以上操作后a2的右上角是#1，

a1的右下角是#2，a2的左下角是#3，a1的右上角是#4，

a2的右下角、a1的左下角、a2的左上角是#5，

a1的左上角是#6。将a分别与八部分进行比较，

与哪部分相同就返回那部分对应的值，如果没有则返回7。

（以上内容已经经过验证）

~~这里先给出第一部分的方法~~

 
 
 
 
 
```cpp
#include <cstdio>
#include <iostream>
const static int Maxn = 20 ;
using namespace std;
char st[Maxn][Maxn];
char ed[Maxn][Maxn];
int n,ans=7;
void Init()
{
    cin>>n;
    for(int i=0;i<n;i++)cin >> st[i];
    for(int i=0;i<n;i++)cin >> ed[i];
    return ;
}
void Comp(int x)
{
    bool flag=true;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(st[i][j]!=ed[i][j])    flag=false;
    if(flag)    ans=min(ans,x);
}
void DegRot90()
{
    char tmp[Maxn][Maxn];
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            tmp[j][n-i-1]=st[i][j];
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            st[i][j]=tmp[i][j];
}
void Ref()
{
    char tmp[Maxn][Maxn];
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            tmp[i][n-j-1]=st[i][j];
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            st[i][j]=tmp[i][j];
}
void Solve()
{
    Comp(6);
    DegRot90();
    Comp(1);
    DegRot90();
    Comp(2);
    DegRot90();
    Comp(3);
    DegRot90();
    Ref();
    Comp(4);
    for(int i=1;i<=3;i++)
    {
        DegRot90();
        Comp(5);
    }
    cout << ans << endl;
}
int main()
{
    freopen("transform.in","r",stdin);
    freopen("transform.out","w",stdout);
    Init();
    Solve();
    return 0;
}
```

---

## 作者：RicardoShips (赞：0)

一道~~大模拟~~又被我打出了160行

还好一次A掉不至于当场去世

毫无技术含量可言

只要基本懂字符串就行

首先，翻转$90$、$180$、$270$其实等于一个操作

就是写一个翻转$90$函数用三遍而已

翻转~~转移方程~~可以手玩一下

就是$s$[$i$][$j$]=s[$n$-$j$+$1$][$i$]，还是比较好推的

然后写一次对称过来，再用三次翻转$90$函数

最后再看是不是和初始状态相同

建议每变化一次就去验证一次

如果成功就直接$return$ $0$，~~简单粗暴~~

下面一些题外话

大家做这种题一定要细心

哪怕你压行也要尽量控制代码长度

不然考场上真的很难查错，也很浪费时间

~~本人天生反面教材~~

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[11][11];
char x[11][11];
char y[11][11];
char z[11][11];
bool flag;
int n,ans;
inline void C()
{
    for(register int i=1;i<=n;++i)
        for(register int j=1;j<=n;++j)
            y[i][j]=x[n-j+1][i];
}
inline void M()
{
    for(register int i=1;i<=n;++i)
        for(register int j=1;j<=n;++j)
            x[i][j]=y[i][j];
}
inline void V()
{
    for(register int i=1;i<=n;++i)
        for(register int j=1;j<=n;++j)
            y[i][j]=x[i][n-j+1];
}
int main()
{
    scanf("%d",&n);
    for(register int i=1;i<=n;++i)
    {
        for(register int j=1;j<=n;++j)
        {
            cin>>s[i][j];
            x[i][j]=s[i][j];
        }
        getchar();
    }
    for(register int i=1;i<=n;++i)
    {
        for(register int j=1;j<=n;++j)
            cin>>z[i][j];
        getchar();
    }
    C();flag=true;
    for(register int i=1;i<=n;++i)
        for(register int j=1;j<=n;++j)
            if(y[i][j]!=z[i][j])
            {
            	flag=false;
            	break;
            }
    if(flag)
    {
        puts("1");
        return 0;
    }
    else M();
    C();flag=true;
    for(register int i=1;i<=n;++i)
        for(register int j=1;j<=n;++j)
            if(y[i][j]!=z[i][j])
            {
            	flag=false;
            	break;
            }
    if(flag)
    {
        puts("2");
        return 0;
    }
    else M();
    C();flag=true;
    for(register int i=1;i<=n;++i)
        for(register int j=1;j<=n;++j)
            if(y[i][j]!=z[i][j])
            {
            	flag=false;
            	break;
            }
    if(flag)
    {
        puts("3");
        return 0;
    }
    else
    {
        for(register int i=1;i<=n;++i)
            for(register int j=1;j<=n;++j)
                x[i][j]=s[i][j];
    }
    V();flag=true;
    for(register int i=1;i<=n;++i)
        for(register int j=1;j<=n;++j)
            if(y[i][j]!=z[i][j])
            {
            	flag=false;
            	break;
            }
    if(flag)
    {
        puts("4");
        return 0;
    }
    else M();
    C();flag=true;
    for(register int i=1;i<=n;++i)
        for(register int j=1;j<=n;++j)
            if(y[i][j]!=z[i][j])
            {
            	flag=false;
            	break;
            }
    if(flag)
    {
        puts("5");
        return 0;
    }
    else M();
    C();flag=true;
    for(register int i=1;i<=n;++i)
        for(register int j=1;j<=n;++j)
            if(y[i][j]!=z[i][j])
            {
            	flag=false;
            	break;
            }
    if(flag)
    {
        puts("5");
        return 0;
    }
    else M();
    C();flag=true;
    for(register int i=1;i<=n;++i)
        for(register int j=1;j<=n;++j)
            if(y[i][j]!=z[i][j])
            {
            	flag=false;
            	break;
            }
    if(flag)
    {
        puts("5");
        return 0;
    }
    flag=true;
    for(register int i=1;i<=n;++i)
        for(register int j=1;j<=n;++j)
            if(s[i][j]!=z[i][j])
            {
            	flag=false;
            	break;
            }
    if(flag) puts("6");
    else puts("7");
    return 0;
}
```

---

## 作者：QianhanOfficial (赞：0)

狂野暴力，225行 19ms 0.79MB AC  
因为数据范围极小，所以枚举翻转操作的效果即可  
比某些题解多用了STL和map3这些玄学操作 ~~而且思路清晰~~
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define re register
using namespace std;

char map1[15][15], map2[15][15], map3[15][15], t[15][15];
//map1输入的第一个图 map2第二个
//map3本来是用于第5项操作的 因为第五项需要进行两步操作 第五项的反转之后的操作所依赖的数组就是map3(这个时候map3储存的是镜像过的map1) 
int n;

bool dealwith(int a, int b)//第一个参数是操作编号 第二个参数用来判断是不是第五项操作(不判断会输出原来的1-3而不是5)
//前三步的操作 为了避免代码太乱(已经挺乱了..)所以就单独写个函数 返回值是判断这三步是否已经解决 解决了就返回true 退出程序.
{
	bool damn = false;
	//1
	if(a == 1)
	{
		for(re int i = n; i >= 1; --i)
		{
			for(re int j = 1; j <= n; ++j)
			{
				t[j][i] = map3[n - i + 1][j];
			}
		}
		/*
		for(re int i = 1; i <= n; ++i)
		{
			for(re int j = 1; j <= n; ++j)
			{
				cout << t[i][j] << " ";
			}
			cout << endl;
		}
		*/
		for(re int i = 1; i <= n; ++i)
		{
			for(re int j = 1; j <= n; ++j)
			{
				if(t[i][j] != map2[i][j])
				{
					damn = true;
					break;
				}
			}
			if(damn) break;
		}
		if(damn) return 0;
		else
		{
			if(b != 5) printf("%d", a);
			else printf("5");
			return 1;
		}
	}
	//2
	else if(a == 2)
	{
		for(re int i = n; i >= 1; --i)
		{
			for(re int j = n; j >= 1; --j)
			{
				t[i][j] = map3[n - i + 1][n - j + 1];
			}
		}
		for(re int i = 1; i <= n; ++i)
		{
			for(re int j = 1; j <= n; ++j)
			{
				if(t[i][j] != map2[i][j])
				{
					damn = true;
					break;
				}
			}
			if(damn) break;
		}
		if(damn) return 0;
		else
		{
			if(b != 5) printf("%d", a);
			else printf("5");
			return 1;
		}
	}
	//3
	else if(a == 3)
	{
		for(re int i = n; i >= 1; --i)
		{
			for(re int j = 1; j <= n; ++j)
			{
				t[i][n - j + 1] = map3[n - i + 1][j];
			}
		}
		/*
		for(re int i = 1; i <= n; ++i)
		{
			for(re int j = 1; j <= n; ++j)
			{
				cout << t[i][j] << " ";
			}
			cout << endl;
		}
		*/
		for(re int i = 1; i <= n; ++i)
		{
			for(re int j = 1; j <= n; ++j)
			{
				if(t[i][j] != map2[i][j])
				{
					damn = true;
					break;
				}
			}
			if(damn) break;
		}
		if(damn) return 0;
		else
		{
			if(b != 5) printf("%d", a);
			else printf("5");
			return 1;
		}
	}
	return 0;//无所谓 这条语句不会被执行
}

int main()
{
	scanf("%d", &n);
	for(re int i = 1; i <= n; ++i) scanf("%s", map1[i] + 1);
	for(re int i = 1; i <= n; ++i) scanf("%s", map2[i] + 1);
	for(re int a = 1; a <= 7; ++a)//枚举每一种操作
	{
		bool damn = false;
		if(a == 1 || a == 2 || a == 3)//前三个
		{
			for(re int i = 1; i <= n; ++i)
			{
				for(re int j = 1; j <= n; ++j)
				{
					map3[i][j] = map1[i][j];//map3当做另一个map1数组使用
				}
			}
			if(dealwith(a, a)) return 0;
			else continue;//如果不合适 换下一个操作
		}
		else if(a == 4)
		{
			for(re int i = 1; i <= n; ++i)
			{
				for(re int j = 1; j <= n; ++j)
				{
					t[i][j] = map1[i][j];
				}
				std::reverse(t[i] + 1, t[i] + n + 1);//reverse可以将一个数列中的元素反过来 很好用 这样相当于每一行都镜像翻转
			}
			for(re int i = 1; i <= n; ++i)
			{
				for(re int j = 1; j <= n; ++j)
				{
					if(t[i][j] != map2[i][j])
					{
						damn = true;//damn为真的时候跳出循环(变量名字是因为我比较痛恨这么长的代码..)
						break;
					}
				}
				if(damn) break;
			}
			if(damn) continue;
			else
			{
				printf("%d", a);
				return 0;
			}
		}
		//5
		else if(a == 5)//重点
		{
			for(re int i = 1; i <= n; ++i)
			{
				for(re int j = 1; j <= n; ++j)
				{
					t[i][j] = map1[i][j];
				}
				std::reverse(t[i] + 1, t[i] + n + 1);//先镜像翻转
			}
			for(re int i = 1; i <= n; ++i)
			{
				for(re int j = 1; j <= n; ++j)
				{
					map3[i][j] = t[i][j];//map3此时存储的是翻转过的图
				}
			}
			for(re int b = 1; b <= 3; ++b)
			{
				if(dealwith(b, a)) return 0;//下一步操作使用map3即可 不需要单独写一个函数.
				else continue;
			}
			continue;
		}
		else if(a == 6)//直接比较
		{
			for(re int i = 1; i <= n; ++i)
			{
				for(re int j = 1; j <= n; ++j)
				{
					if(map1[i][j] != map2[i][j])
					{
						damn = true;
						break;
					}
				}
				if(damn) break;
			}
			if(damn) continue;
		}
		else//都试完了 还不行 那就返回不行
		{
			printf("7");
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：yjxyjx (赞：0)

刚才A掉了一个超级模拟题。。真开心。。现在写一下对这题的分析&体会吧。。

这题。。我看的是usaco网站上的版本。。一开始漏掉了“rotated”这个词（这tm是顺时针的意思啊。。一开始想成了逆时针。。狂改代码。。）

先放我的做法吧。。

```

/*
ID: yjx_yjx1 
PROG: transform
LANG: C++
*/
/* LANG can be C++11 or C++14 for those more recent releases */



#include<bits/stdc++.h>

using std::string;

const int MaxN = 10 + 5;
/* tempBeforeSquare是这样用的：一开始和beforeSquare相同，
   但在执行4时，就让它成为before的镜像，然后到第5个判断时会方便一些 */
string beforeSquare[MaxN], afterSquare[MaxN], tempBeforeSquare[MaxN];
int N;
/* N为原本读入的矩阵大小*/
/*后来发现一大堆地方N要-1，否则会越界，（话说C++越界跑起来连
  运行时错误都没有，差评）这是个很隐蔽的错误，Warning
 */

void debug1() {
    std::cerr << "temp\n";
    for (int i = 0; i < N; ++i) std::cerr << tempBeforeSquare[i] << "\n";
    std::cerr << "after\n";
    for (int i = 0; i < N; ++i) std::cerr << afterSquare[i] << "\n";
}

/*顺时针反转90度，看不懂的可以在纸上画一下*/
bool check_1() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            /* 这下面的N-1非常重要，差点调不出来……C++内存泄漏照常运行 */
            if (tempBeforeSquare[(N - 1) - j][i] != afterSquare[i][j]) {
                return false;
            }
        }
    }
    return true;
}
/*翻转180度*/
bool check_2() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (tempBeforeSquare[(N - 1) - i][(N - 1) - j] != afterSquare[i][j]) return false;
        }
    }
    return true;
}
/*顺时针反转270度*/
bool check_3() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (tempBeforeSquare[(N - 1) - j][i] != afterSquare[i][j]) {
                // std::cerr << i << (N - 1) - j << j << (N - 1) - i << tempBeforeSquare[i][(N - 1)- j] << afterSquare[j][(N - 1) - i] << "\n";
                return false;
            }  
        }
    }
    return true;
}

/*在上面的操作中，不会对数据进行变动，只是进行检测*/



/* 在下面的check_4中，我并没有复制上面的模块，加了一个isImage，
 * 因为在之后的check_5，我们将要“水平翻转后”再进行1/2/3操作。
 * 这后面的双重循环直接进行翻转
 */
bool check_4() {
    bool isImage = true;
    // std::cerr << tempBeforeSquare[2][0];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            
                if (tempBeforeSquare[i][(N - 1) - j] != afterSquare[i][j]){
                    isImage = false;
                    // std::cerr << i << (N - 1) - j << j << tempBeforeSquare[i][(N - 1) - j] << afterSquare[i][j] <<  "\n";                     
                }

        }
    } 
    for (int i = 0; i < N; ++i) 
        for (int j = 0; j < N; ++j) 
                tempBeforeSquare[i][j] = beforeSquare[i][(N - 1) - j];            
    return isImage;
}

bool check_5() {
    bool f = (check_1() || check_2() || check_3()) ? true : false;
    return f;
}

bool check_6() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (beforeSquare[i][j] != afterSquare[i][j]) return false;
        }
    }
    return true;
}

void Init() {
    std::cin >> N;
    for (int i = 0; i < N; ++i) {
        std::cin >> beforeSquare[i];
        tempBeforeSquare[i] = beforeSquare[i];
    }
    for (int i = 0; i < N; ++i) std::cin >> afterSquare[i]; 
}

void Work() {
    // debug1();
    if (check_1() == true) {
        std::cout << 1 << std::endl;
        return;
    }
    if (check_2() == true) {
        std::cout << 2 << std::endl;
        return;
    }
    if (check_3() == true) {
        std::cout << 3 << std::endl;
        return;
    }
    // debug1();    
    if (check_4() == true) {
        std::cout << 4 << std::endl;
        return;
    }
    if (check_5() == true) {
        std::cout << 5 << std::endl;
        return;
    }
    if (check_6() == true) {
        std::cout << 6 << std::endl;
        return;
    }
    std::cout << 7 << std::endl;
}

int main() {
    freopen("transform.in", "r", stdin);
    freopen("transform.out", "w", stdout);
    Init();
    Work();
    return 0;
}

```

这题。。没什么算法可以说的。。重要的是要自己模拟出来。。难度相当于普及组T2吧。。（通常为超级模拟题。。但这题模拟程度秒杀普及组T2。。

以上。




---

## 作者：张奕涵 (赞：0)

十分暴力，正在转c++，一时忘了char数组是从0开始的，差点没改死orz。。。有字符串的题目就是烦。。。

ope1-5分别表示第1到第5种操作。其中由于5在4的后面，所以直接尝试再进行1-3，为了不影响67还是倒回来了。。。write是当时的调试。

下面代码：

···
cpp
    


```cpp
#include<bits/stdc++.h>
#define LL long long
#define INF (0x7f7f7f7f)
using namespace std;
char s[11][11],t[11][11],r[11][11];
bool b,c;int n;
inline void write(){
    for(int i=0;i<=n-1;i++){
        for(int j=0;j<=n-1;j++)
        printf("%c",r[i][j]);printf("\n");}
}
inline int judge(int x){
    for(int i=0;i<=n-1;i++)
        for(int j=0;j<=n-1;j++)
        if(r[i][j]!=t[i][j])return 0;
    b=true;if(c)return 5;return x;
}
inline void ope1(){
    for(int i=0;i<=n-1;i++)for(int j=0;j<=n-1;j++)r[i][j]=s[n-j-1][i];
    int x=judge(1);if(x!=0)printf("%d",x);//write();
}
inline void ope2(){
    for(int i=0;i<=n-1;i++)for(int j=0;j<=n-1;j++)r[i][j]=s[n-i-1][n-j-1];
    int x=judge(2);if(x!=0)printf("%d",x);//write();
}
inline void ope3(){
    for(int i=0;i<=n-1;i++)for(int j=0;j<=n-1;j++)r[i][j]=s[j][n-i-1];
    int x=judge(3);if(x!=0)printf("%d",x);//write();
}
inline void ope4(){
    for(int i=0;i<=n-1;i++)for(int j=0;j<=n-1;j++)r[i][j]=s[i][n-j-1];
    for(int i=0;i<=n-1;i++)for(int j=0;j<=n-1;j++)s[i][j]=r[i][j];
    int x=judge(4);if(x!=0)printf("%d",x);//write();
}
inline void ope5(){
    c=true;
    if(!b)ope1();if(!b)ope2();if(!b)ope3();
    for(int i=0;i<=n-1;i++)for(int j=0;j<=n-1;j++)r[i][j]=s[i][n-j-1];
    for(int i=0;i<=n-1;i++)for(int j=0;j<=n-1;j++)s[i][j]=r[i][j];
    c=false;
}
inline void ope6(){
    for(int i=0;i<=n-1;i++)for(int j=0;j<=n-1;j++)r[i][j]=s[i][j]; 
    int x=judge(6);if(x!=0)printf("%d",x);
}
int main(){
    scanf("%d\n",&n);
    for(int i=0;i<=n-1;i++)gets(s[i]);
    for(int i=0;i<=n-1;i++)gets(t[i]);
    ope1();if(!b)ope2();if(!b)ope3();if(!b)ope4();
    if(!b)ope5();if(!b)ope6();if(!b)printf("%d",7);
    return 0;
}
···
```

---

## 作者：Mr灬风流丿 (赞：0)

###这题只需设定两个函数即可解决

/\*
ID: zxc28471

PROG: transform

LANG: C++

\*/
```cpp
#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
using namespace std;
char a[11][11],b[11][11],c[11][11];//数组不要定太小
void turn(int n){//定义一个反转函数
    for(int i=1;i<=n;i++)
      for(int j=1;j<=n;j++)
        c[i][j]=a[i][j];
    for(int i=1;i<=n;i++)
      for(int j=1;j<=n;j++)
      a[i][j]=c[j][n-i+1];
}
void ah(int n){//再定义一个镜像函数
    for(int i=1;i<=n;i++)
      for(int j=1;j<=n;j++)
        c[i][j]=a[i][j];
    for(int i=1;i<=n;i++)
      for(int j=1;j<=n;j++)
        a[i][j]=c[i][n-j-1];
}
int main()//主程序
{
       //freopen("transform.in","r",stdin);
       //freopen("transform.out","w",stdout);
    int n,l=0;
    scanf("%d",&n);  //输入n
    for(int i=1;i<=n;i++)
      for(int j=1;j<=n;j++)
        cin>>a[i][j];  //输入第一个方阵
    for(int i=1;i<=n;i++)
      for(int j=1;j<=n;j++)
        cin>>b[i][j];//输入第二个方阵
    turn(n);//旋转第一个方阵（90度）
    for(int i=1;i<=n;i++)
      for(int j=1;j<=n;j++)
          if(int(a[i][j])==int(b[i][j])){//判断是否符合输出1的要求
              l++;
              if(l==n*n){
                  cout<<1<<endl;
                  return 0;//即使结束主程序
              }
          }
          l=0;//计数器计数归零
        turn(n);//再次旋转第一个方阵（180度）
      for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        if(int(a[i][j])==int(b[i][j])){//继续判断
              l++;
              if(l==n*n){
                  cout<<2<<endl;
                  return 0;
              }
          }
          l=0;
          turn(n);//再次旋转第一个方阵（270度）
          for(int i=1;i<=n;i++)
      for(int j=1;j<=n;j++)
        if(int(a[i][j])==int(b[i][j])){//继续判断
              l++;
              if(l==n*n){
                  cout<<3<<endl;
                  return 0;
              }
          }
          l=0;
        turn(n);//再次旋转返还原型
          ah(n);//进行一次镜像操作
      for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        if(int(a[i][j])==int(b[i][j])){//判断
            l++;
            if(l==n*n){
                cout<<4<<endl;
                return 0;
            }
        }
        l=0;
        ah(n);
        turn(n);
      for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
          if(int(a[i][j])==int(b[i][j])){
              l++;
              if(l==n*n){
                  cout<<5<<endl;
                  return 0;
              }
          }
          l=0;//下面继续旋转，与上同
        turn(n);
        for(int i=1;i<=n;i++)
      for(int j=1;j<=n;j++)
        if(int(a[i][j])==int(b[i][j])){
              l++;
              if(l==n*n){
                  cout<<5<<endl;
                  return 0;
              }
          }
          l=0;
          turn(n);
          for(int i=1;i<=n;i++)
          for(int j=1;j<=n;j++)
            if(int(a[i][j])==int(b[i][j])){
                l++;
                if(l==n*n){
                  cout<<5<<endl;
                  return 0;
              }
          }
          l=0;
    turn(n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
          if(int(a[i][j])==b[i][j]){
            l++;
            if(l==n*n){
            cout<<6<<endl;
            return 0;
        }
    }
    cout<<7<<endl;//无上述情况是，输出7
    return 0;
}
```

---

## 作者：iren (赞：0)

其实做法楼下的大佬们已经说的很明白了，要执行的操作只有两种：顺时针旋转90度和镜像。

我用了一个三维数组，觉得在传递参数，存储数据上要简单些。

代码和注释：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,yes;
char in[101];
char cg[4][101][101],a[101][101];
    //cg[0]存储原来的方块，cg[1...3]依次存cg[0]旋转90，180，270度的方块 
void turn(int x){ //这是把cg[x-1]旋转90度并存到cg[x]中的函数 
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            cg[x][i][j]=cg[x-1][n-j+1][i];
}
void reflect(){//这是镜像函数 
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n/2;j++){
            char temp=cg[0][i][j];
            cg[0][i][j]=cg[0][i][n-j+1];
            cg[0][i][n-j+1]=temp;
        }         
}
int judge(int x){
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(a[i][j]==cg[x][i][j]) continue;
            else return 0;//不一样返回0
    return 1;//一样返回1
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        scanf("%s",&in);
        //输入一直很不友好，我觉得这样挺方便的 
        for(int j=1;j<=n;j++)
            cg[0][i][j]=in[j-1];
    }        
    for(int i=1;i<=n;i++){
        scanf("%s",&in);
        for(int j=1;j<=n;j++)
            a[i][j]=in[j-1];
    }        
    for(int i=1;i<=3;i++){
        turn(i);
        yes=judge(i);
        if(yes){ cout<<i; return 0;}
    }
    reflect();//镜像用一次就够了，也没必要加参数了 
    yes=judge(0);
    if(yes){ cout<<"4"; return 0;}
    for(int i=1;i<=3;i++){
        turn(i);
        yes=judge(i);
        if(yes){ cout<<"5"; return 0;}
    }
    if(judge(0)) cout<<"6";
    else cout<<"7";
    return 0;
}
```

---

## 作者：Creeper_LKF (赞：0)

###常数级的优化

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    char matrix_s[10][10],matrix_t[10][10];//起始矩阵和目标矩阵
    int n,could=8;
    bool ways[5]={true,true,true,true,true},way1=true,way2=true,way3=true;//记录各种可能状态，如果发现都不行则结束程序
    scanf("%d",&n);//感谢楼下提醒，似乎有些题目真的不能用getchar（可能是数据后多接了几个空格吧，如果非要用，那么最好用
    for(int i=0;i<n;i++){//while循环来吃空格换行符）
        scanf("\n");
        for(int j=0;j<n;j++){
            scanf("%c",&matrix_s[i][j]);
        }
    }
    for(int i=0;i<n;i++){
        scanf("\n");
        for(int j=0;j<n;j++){
            scanf("%c",&matrix_t[i][j]);
        }
    }
    for(int i=0;i<n;i++){//只要枚举一次矩阵就行了
        for(int j=0;j<n;j++){
            if(!could){
                printf("7");
                return 0;
            }
            if(ways[0]&&matrix_s[i][j]!=matrix_t[j][n-i-1]) ways[0]=false,could--;//可以打草稿列出来
            if(ways[1]&&matrix_s[i][j]!=matrix_t[n-i-1][n-j-1]) ways[1]=false,could--;
            if(ways[2]&&matrix_s[i][j]!=matrix_t[n-j-1][i]) ways[2]=false,could--;
            if(ways[3]&&matrix_s[i][j]!=matrix_t[i][n-j-1]) ways[3]=false,could--;
            if(ways[5]&&matrix_s[i][j]!=matrix_t[i][j]) ways[5]=false,could--;
            if(way1&&matrix_s[i][j]!=matrix_t[n-j-1][n-i-1]) way1=false,could--;
            if(way2&&matrix_s[i][j]!=matrix_t[n-i-1][j]) way2=false,could--;//当镜像时90°和270°并不简单地等价 
            if(way3&&matrix_s[i][j]!=matrix_t[j][i]) way3=false,could--;//画图思考 
            if(!(way1||way2||way3)) ways[4]=false;//注意逻辑关系 
        }
    }
    for(int i=0;i<6;i++){
        if(ways[i]){
            printf("%d",i+1);//输出的序号要比数组下标大1 
            return 0;
        }
    }
    printf("7");//如果最后一个点使could=0，那么上面将无法输出7
    return 0;
}
```

---

## 作者：McGrady (赞：0)

先推一推旋转的公式，类似数学的坐标变换的

AC了才发现6并没有什么卵用

程序习惯性地打上了文件，大家不要介意

```cpp
var
  f:boolean;
  i,j,n:longint;
  a,b:array[0..11,0..11]of char;
  t:char;
begin
   assign(input,'r.in');assign(output,'r.out');reset(input);rewrite(output);
   readln(n);
   for i:=1 to n do begin for j:=1 to n do read(a[i,j]);readln; end;
   for i:=1 to n do begin for j:=1 to n do read(b[i,j]);readln; end;
   f:=true;
   for i:=1 to n do begin for j:=1 to n do if a[i,j]<>b[j,n-i+1] then begin f:=false;break; end;if not f then break; end;
   if f then begin write(1);close(input);close(output);halt; end;
   f:=true;
   for i:=1 to n do begin for j:=1 to n do if a[i,j]<>b[n-i+1,n-j+1] then begin f:=false;break; end;if not f then break; end;
   if f then begin write(2);close(input);close(output);halt; end;
   f:=true;
   for i:=1 to n do begin for j:=1 to n do if a[i,j]<>b[n-j+1,i] then begin f:=false;break; end;if not f then break; end;
   if f then begin write(3);close(input);close(output);halt; end;
   f:=true;
   for i:=1 to n do begin for j:=1 to n do if a[i,j]<>b[i,j] then begin f:=false;break; end;if not f then break; end;
   if f then begin write(6);close(input);close(output);halt; end;
   f:=true;
   for i:=1 to n do begin for j:=1 to n>>1 do begin t:=a[i,j];a[i,j]:=a[i,n-j+1];a[i,n-j+1]:=t; end; end;
   for i:=1 to n do begin for j:=1 to n do if a[i,j]<>b[i,j] then begin f:=false;break; end;if not f then break; end;
   if f then begin write(4);close(input);close(output);halt; end;
   f:=true;
   for i:=1 to n do begin for j:=1 to n do if a[i,j]<>b[j,n-i+1] then begin f:=false;break; end;if not f then break; end;
   if f then begin write(5);close(input);close(output);halt; end;
   f:=true;
   for i:=1 to n do begin for j:=1 to n do if a[i,j]<>b[n-i+1,n-j+1] then begin f:=false;break; end;if not f then break; end;
   if f then begin write(5);close(input);close(output);halt; end;
   f:=true;
   for i:=1 to n do begin for j:=1 to n do if a[i,j]<>b[n-j+1,i] then begin f:=false;break; end;if not f then break; end;
   if f then begin write(5);close(input);close(output);halt; end;
   write(7);
   close(input);close(output);
end.
```

---

