# [AHOI2017初中组] cover

## 题目背景

以下为不影响题意的简化版题目。

## 题目描述

一个 $n\times n$ 的网格图（标号由 $1$ 开始）上有 $m$ 个探测器，每个探测器有个探测半径 $r$ ，问这 $n\times n$ 个点中有多少个点能被探测到。

## 说明/提示

$1\le n,m\le 100$

## 样例 #1

### 输入

```
5 2 1
3 3
4 2```

### 输出

```
8```

# 题解

## 作者：神犇大佬 (赞：581)

### 这道题~~很~~~~强~~很蒻
#### 补充两点距离公式：已知A(x1,y1),B(x2,y2）
### 则**AB=sqrt(pow(abs(x1-x2))+pow(abs(y1-y2)))**
#### 敲黑板，记笔记！！！！

                       **------核心代码分割线-----**

```cpp
for(int i=1;i<=n;i++)
{
    for(int j=1;j<=n;j++)
    {
        double r1=sqrt((x-i)*(x-i)+(y-j)*(y-j));//求出探测器与目标点的距离
        if(r1<=r)//判断距离
        {
            a[i][j]=1;//标记目标点
        }
    }
}

```
### 思路：
##### 1.全部搜索
##### 2.每一次搜索都判断目标点与探测器的距离
##### 3.if判断距离与r
##### 4.标记目标点
##### 5.整合输出

### P.S.
##### 1.sum=0
##### 2.a[i][j]=1
##### 3.double r1=sqrt((x-i)*(x-i)+(y-j)*(y-j))
				-----华丽的分割线------
#### 扔下代码~~走人~~
```cpp
#include<bits/stdc++.h>//不建议用这道题的万能头等同于#include<cmath>+#include<iostream>
using namespace std;
int a[105][105]={0};
int n,m,r,sum=0;
int x,y;
int main()
{
    cin>>n>>m>>r;
    for(int i=1;i<=m;i++)
    {
        cin>>x>>y;//不建议一起输入完在进行计算，可以边计算边输入，这样效率更高。
        a[x][y]=1;//标记目标点
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                double r1=sqrt((x-i)*(x-i)+(y-j)*(y-j));//求出探测器与目标点的距离
                if(r1<=r)//判断距离
                {
                    a[i][j]=1;//标记目标点
                }
            }
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(a[i][j]==1)//循环符合条件的目标点
            {
                sum++;
            }
        }
    }
    cout<<sum;帅气的输出
    return 0;
}
```

				------谢谢观看------
### 最后的最后
##### 请大家留下一个赞再走！
##### 打字不易，留赞再走！
##### 欢迎大佬挑刺，欢迎萌新提问！

---

## 作者：Atmizz (赞：71)

# 基本思路：

这个题是较为简单的，可以使用搜索做，我用的是初中的数学知识点——两点之间的距离公式，普及一下。


------------
![两点之间距离公式图](https://p.ssl.qhimg.com/t01ed5cd17267ae24fb.png)
（图片源自网络，为什么呢，因为我懒啊！）


------------
好，那么怎么计算呢？很简单，就是这样->
```cpp
dis=sqrt((x-i)*(x-i)+(y-j)*(y-j));
```
既然这样，我们就可以枚举每一个点，看每一个点到这个探测器的直线距离->
```cpp
for(int i=1;i<=n;i++) {//开始枚举各个点 
			for(int j=1;j<=n;j++) {
				dis=sqrt((x-i)*(x-i)+(y-j)*(y-j));//两点之间的距离公式！！初中就学到了，应该都会吧。 
				if(dis<=r)//到这里的距离小于扫射的距离 
					map[i][j]=1;//那么就标记 
			}
		}
```
比比了这么多，上完整代码->
```cpp
#include<iostream>//不推荐使用万能头，会和某些变量名冲突 例如map数组 
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;//申请命名空间 
int n,m,r,ans=0;//对应着n*n大小的方阵，m个探测器，r的扫描半径，最终的答案 
int x,y;//输入探测器的坐标 
double dis;//点到探测器的距离 
bool map[1001][1001]={0};//初始化为0，1表示可以被扫到的点 
int main()
{
	scanf("%d%d%d",&n,&m,&r);//输入 
	for(int k=1;k<=m;k++) {
		scanf("%d%d",&x,&y);//输入点的坐标 
		map[x][y]=1;//探测仪肯定可以被扫到 
		for(int i=1;i<=n;i++) {//开始枚举各个点 
			for(int j=1;j<=n;j++) {
				dis=sqrt((x-i)*(x-i)+(y-j)*(y-j));//两点之间的距离公式！！初中就学到了，应该都会吧。 
				if(dis<=r)//到这里的距离小于扫射的距离 
					map[i][j]=1;//那么就标记 
			}
		}
	}
	for(int i=1;i<=n;i++) {//看每一个点 
			for(int j=1;j<=n;j++) {
				if(map[i][j]==1)//可以被扫到 
					ans++;//计数器加加 
			}
	}
	printf("%d",ans);//完美输出答案 
	return 0;//完美の结束 
}
```
# 求过！！！
## 感谢观看！

---

## 作者：Misaka_Azusa (赞：40)

这个题的思路完全就是暴力....

直接用两点距离公式跟半径比较就ok了。


    
    
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
int x[10001],y[10001];
bool a[10001][10001];
int m,n,r;
int main()
{
    cin>>n>>m>>r;
    int ans=0;
    for(int i1=1;i1<=m;i1++)
    {cin>>x[i1]>>y[i1];
    {for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    {
        double o1=sqrt((x[i1]-i)*(x[i1]-i)+(y[i1]-j)*(y[i1]-j)); //两点距离公式
        if(o1<=r) a[i][j]=true;
    } 
    }
    }
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    if(a[i][j]==1) ans++;
    cout<<ans;
    return 0;
}____
```

---

## 作者：alpq010815 (赞：28)

用把每个圆分成一个个长条，差分，统计多少个零，能过洛谷夏令营n=5000的题










```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
using namespace std;
int n,m,r,f[5001][5001],ans;
int check(int x,int r)
{
    return (int)sqrt((double)(r*r-x*x));
}
int main()
{
    scanf("%d%d%d",&n,&m,&r);
        for(int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        for(int j=0;j<=r;j++)
        {
            int k=check(j,r);
            int x1=min(x+k,n);
            int y1=min(y+j,n);
            int x2=max(x-k,1);
            int y2=max(y-j,1); 
                f[y1][x2]+=1;
                f[y1][x1+1]-=1;
                if(j!=0)
            {
                f[y2][x2]+=1;
                f[y2][x1+1]-=1;
            }   
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++) 
        {
            f[i][j]+=f[i][j-1];
            if(!f[i][j])
                ans++;
        }
    }
    printf("%d",n*n-ans);
    return 0;
}
```

---

## 作者：Arcturus1350 (赞：20)

本题的大致思路就是搜索。

将矩阵初始化成false。先把灯塔标记。在搜一遍灯塔能照到的点并标记。最后搜一遍找被灯塔标记的个数。

详细解释见题解。

题解走起。

```cpp
#include<bits/stdc++.h>
using namespace std;
bool a[1001][1001];                                  //数组开的有点大哈，开到200就足够了。不过想要标记，就要是bool型的。
int main()
{
    int n,m,r,sum=0;                                 //sum为后面用的计数器。
    int j=0,k=0,i=0;
    int x,y;                                           //i,j,k,x,y作为控制循环次数的东东。
    cin>>n>>m>>r;                                    //输入数据
    for(i=0;i<m;i++)                                 //第一遍标记###看好括号###
    {
        cin>>j>>k;                                   //对于每一个灯塔的坐标进行输入
        a[j-1][k-1]=1;                               //标记灯塔位置
                                                     /*这里要说一点，灯塔坐标给的和数组定义的不太一样。
                                                       数组的0是第一位。而灯塔的坐标是从1开始的，所以要将坐减一。
                                                       我第一次就是这么被坑的。*/
        for(x=0;x<n;x++)                             //第一次搜索开始
        {   for(y=0;y<n;y++)
            {
              if((x-j+1)*(x-j+1)+(y-k+1)*(y-k+1)<=r*r)//圆的方程：(x-a)²+(y-b)²=r²
              {
                  a[x][y]=1;                         //标记被搜到的。
              }
            }
        }                                            //说实话这个括号和上面“第二次搜索开始“后面的都不用加。
                                                     //为了清楚，我现在加上了。
    }                                                //好了，现在搜完第一次了
                                                     //开始统计。第二次搜索，并计数
    for(i=0;i<n;i++)                                 //全图走一遍。
    {   for(j=0;j<n;j++)
        {
            if(a[i][j]==1)
            {
                sum++;
            }
        }   
    }
    cout<<sum;                                       //输出
    return 0;                                        //程序拜拜。
}
```

---

## 作者：Sooke (赞：19)

这道题只需要**完全暴力**即可，主要思路是：

1.先定义一个模拟方格图的二位数组变量，为了储存方格图上的一点有没有查找过，注意要**大一点**，不然A不了……（具体原因不明）

2.每输入一个探测器的点，就双重循环查看能不能找到可以探测的地方，另外为了减小时间复杂度，建议不要全图探测，在以探测器为重心边长为 2 \* r 的矩形内查找就行了（因为在这个矩形内画最大的圆恰好是探测器的探测范围）。

3.避免探测器探测同一个地方，查找过的点赋值**真**，此外把能探测的点加一，否则默认就是假。

4.最后输出答案就行了

具体代码如下：

```cpp
#include <iostream>
using namespace std;
int main()
{
    bool map[201][201];
    //定义模拟方格图
    int a,b,n,m,r,s=0;
    cin >> n >> m >> r;
    for(int i=1;i <= m;i++)
    {
        cin >> a >> b;
        for(int x=a-r;x <= a+r;x++)
        for(int y=b-r;y <= b+r;y++)
        if(x >= 1 && x <= n && y >= 1 && y <= n)
        if(map[x][y] == false && (a-x)*(a-x)+(b-y)*(b-y) <= r*r)
        map[x][y]=true,s++;
        //程序核心部分，上面解释过了
    }
    cout << s;
    return 0;
} 
```

---

## 作者：半仙胡小桃 (赞：13)

其实是个水题蛤。

我们使用差分的思想，对能够覆盖到的地方进行差分，最后看一下那个位置值为1，即为覆盖的点

怎么样确定区间呢，勾股定理啊。

我们枚举lenY（纵坐标距离圆心的距离），通过lenX^2+lenY^2=r^2计算lenX即可，然后进行差分









```cpp
#include <cstdio>
#include <iostream>
#include <map>
#include <cmath>
using namespace std;
int f[5001][5001];
int main()
{
    int n,m,r;
    scanf("%d%d%d",&n,&m,&r);
    for(int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        for(int j=max(1,y-r);j<=min(n,y+r);j++)
         {
            int len1=y-j;
            len1*=len1;
            int len2=sqrt((double)(r*r)-len1);
            int x1=max(1,x-len2),x2=min(n,x+len2);
            f[j][x1]+=1,f[j][x2+1]-=1;
         }
    }
    int ans=0;
    for(int i=1;i<=n;i++)
     for(int j=1;j<=n;j++)
      {
        f[i][j]+=f[i][j-1];
        if(f[i][j]) ans++;
      }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：Peter_Z (赞：12)

设一矩阵保存是否被扫到，对于每个探测器，若矩阵中某点到此探测器距离小于r，则标记在矩阵中。

其实这样的方法还可以优化，由于半径为r的圆能放进边长为2r的正方形中，所以在(x-r)到(x+r)区间内搜索即可。

但不知道为什么我这样即使加了边界判断大于0也会RE，改成对整个矩阵扫描就AC了……

--------------------------------------------------------------------------------------------------------------------------

代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
bool a[121][121];
int main() {
    int n,m,r,x,y,ans=0;
    scanf("%d %d %d",&n,&m,&r);
    while(m--) {
        scanf("%d %d",&x,&y);
        for(register int j=1; j<=n; j++)
            for(register int k=1; k<=n; k++)
                if((x-j)*(x-j)+(y-k)*(y-k)<=r*r)
                    a[j][k]=true;
    }
    for(register int i=1; i<=n; i++)
        for(register int j=1; j<=n; j++)
            if(a[i][j]) ans++;
    printf("%d",ans);
    return 0;
}

```

---

## 作者：Grace_White (赞：4)

### 本蒟蒻在入门区翻找时，无意间寻找到了这个超级大水题。。。

### 想做这题就只需要知道如何求两点之间的距离

### 所以在这里，我就来说说如何求两点之间的距离

### 首先，现将两点的距离求出来,然后利用勾股定理

### 就可以求出两点的距离：*sqrt((x-x1)(x-x1)+(y-y1)(y-y1))*

### 回到正题，这道题目其实很简单，只要每个点枚举过来

### 判断与探测器的距离是否小于探测器的半径

### 如果小于，则记录下来

### 最后统计可以探测到的数量

### 废话不说了直接上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,p,i,j,x,y,sum;
bool a[101][101];
int main()
{
	scanf("%d%d%d",&n,&m,&p);
	for (i=1;i<=m;i++)
	  {
	  	scanf("%d%d",&x,&y);
	  	for (j=1;j<=n;j++)
	  	  for (k=1;k<=n;k++)//枚举
	  	    if (sqrt((x-j)*(x-j)+(y-k)*(y-k))<=p)//判断
	  	      a[j][k]=true;//记录
	  }
	for (j=1;j<=n;j++)
	  for (k=1;k<=n;k++)
	    if (a[j][k])
	      sum=sum+1;//累加
	printf("%d\n",sum);
	return 0;
}
```


---

## 作者：beng (赞：4)

# 水题……

既然是水题，也就没有多考虑就做了，可能时空复杂度不是最低的，但也不想管那么多了。（谁叫它数据范围那么小）

我的思路，**直接读一个坐标就枚举网格图，有被探测器覆盖的点（不重复）就计数加1**。

————————分割不完全的分割线————————

以下是pascal代码：

```cpp
var n,m,i,j,k,l,r,x,y:longint;
b:array[1..100,1..100]of boolean;
begin
  readln(n,m,r);
  for k:=1 to m do
  begin
    readln(x,y);//读入坐标
    for i:=1 to n do
    for j:=1 to n do//枚举每个点
    if (abs(i-x)*abs(i-x)+abs(j-y)*abs(j-y)<=r*r)and(not b[i,j]) then//看那个点与探测器的距离是否在探测范围之内（且不重复）
    begin
      b[i,j]:=true;
      inc(l);//计数加一
    end;
  end;
  writeln(l);
end.
```

---

## 作者：F_S_R_M (赞：3)

###### 这个题还可以吧
# 思路：

------------

1、输入，坐标都赋值为1

2、_**枚举**_ 每个点是否在范围之内，如果在范围内就赋值为2

3、进行for循环，循环每一个坐标，坐标的值如果是2，计数器就+1

4、输出计数器的值

（这个范围就是重中之重了，最核心的部分就是这个范围，如果知道范围如何求的话，那就ok了）


------------

# 两点之间距离公式：


------------

设A的坐标为（$x_1$，$y_1$），B的坐标为（$x_2$，$y_2$）

设A、B间距离为$d_{AB}$

设$\Delta x=x_1-x_2,\Delta y=y_1-y_2$

#### 那么

####   _$d_{AB}=\sqrt{{\Delta x^2}+{\Delta y^2}}$_


------------

### 代码核心（其他的想怎么写就怎么写）
```cpp
for(int k=1;k<=m;k++)
	{
		for(int i=1; i<=n; i++) 
		{
			for(int j=1; j<=n; j++) 
			{
				double tot=sqrt((x[k]-i)*(x[k]-i)+(y[k]-j)*(y[k]-j));//sqrt库：cmath
				if(tot<=r)  a[i][j]='2';
			}
		}
	}

```

### 总代码（虽然有一点点长，但是只要知道核心代码，其他的想怎么打就怎么打）：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#include<cmath>
using namespace std;
char a[110][110];
int x[1000],y[1000];

int main() {
	int n,m,num=0;
	double r;
	cin>>n>>m>>r;				//输入 
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			a[i][j]='0';
	for(int i=1; i<=m; i++) {
		cin>>x[i]>>y[i];
		a[x[i]][y[i]]='1';    //输入全都赋值成1 
	}
	for(int k=1;k<=m;k++)
	{
		for(int i=1; i<=n; i++) 
		{
			for(int j=1; j<=n; j++) 		//三层for循环枚举
			{
				double tot=sqrt((x[k]-i)*(x[k]-i)+(y[k]-j)*(y[k]-j));
				if(tot<=r)  a[i][j]='2';		//如果他在这个范围内就赋值为2 
			}
		}
	}
	
	for(int i=1; i<=n; i++) 
	{
		for(int j=1; j<=n; j++)  	//进行for循环，循环每个坐标
		{
			if(a[i][j]=='2') 
			{
				num++;		//如果为2 计数器就+1 
			}
		}
	}
	cout<<num<<endl;			//输出计数器的数值 
	return 0;					//完美结束  perfect 
}
```




---

## 作者：Surpersolo (赞：3)

```cpp
#include<bits/stdc++.h>
using namespace std;
bool a[1001][1001];                                  //数组开的有点大哈，开到200就足够了。不过想要标记，就要是bool型的。
int main()
{
    int n,m,r,sum=0;                                 //sum为后面用的计数器。
    int j=0,k=0,i=0;
    int x,y;                                           //i,j,k,x,y作为控制循环次数的东东。
    cin>>n>>m>>r;                                    //输入数据
    for(i=0;i<m;i++)                                 //第一遍标记###看好括号###
    {
        cin>>j>>k;                                   //对于每一个灯塔的坐标进行输入
        a[j-1][k-1]=1;                               //标记灯塔位置
                                                     /*这里要说一点，灯塔坐标给的和数组定义的不太一样。
                                                       数组的0是第一位。而灯塔的坐标是从1开始的，所以要将坐减一。
                                                       我第一次就是这么被坑的。*/
        for(x=0;x<n;x++)                             //第一次搜索开始
        {   for(y=0;y<n;y++)
            {
              if((x-j+1)*(x-j+1)+(y-k+1)*(y-k+1)<=r*r)//圆的方程：(x-a)²+(y-b)²=r²
              {
                  a[x][y]=1;                         //标记被搜到的。
              }
            }
        }                                            //说实话这个括号和上面“第二次搜索开始“后面的都不用加。
                                                     //为了清楚，我现在加上了。
    }                                                //好了，现在搜完第一次了
                                                     //开始统计。第二次搜索，并计数
    for(i=0;i<n;i++)                                 //全图走一遍。
    {   for(j=0;j<n;j++)
        {
            if(a[i][j]==1)
            {
                sum++;
            }
        }   
    }
    cout<<sum;                                       //输出
    return 0;                                        //程序拜拜。
}
```


---

## 作者：Bring (赞：2)

[更好的阅读体验请点这里](https://www.cnblogs.com/BrianPeng/p/12178151.html)

~~（这不是暴力就可以了吗）~~

当然正解就是暴力，所以假设$n,m,r\leqslant 1000$，再看看这道题

这道题就是典型的区间修改（将可以覆盖的地方$+1$）与单次查询（最后问$>0$的有几个）

于是以行为单位差分，每一次修改相当于对每一行的元素做区间修改

但是每一行被修改的位置和长度互不相同，具体取决于半径$r$和行号$i$到圆心所在行号$y$的距离（$|i-y|$）

假设存在$e_{0..r}$数组，$e_i$表示斜边为$r$，对边为$i$的直角三角形的邻边长度的整数部分，即$e_i=\lfloor\sqrt{r^2-i^2}\rfloor$

那么对于第$i$行，如果圆心是$(x,y)$，半径为$r$，覆盖的区间就是$[max(1,x-e_{|i-y|}),min(n,x+e_{|i-y|})]$**（可别忘了处理边界）**

最后是如何计算$e$数组

~~（当然可以直接使用sqrt()）~~

但是注意到$e$数组具有不上升单调性，可以使用一种类似递推的方法做，保证计算$O(n)$~~（虽然说其实完全没有必要啦）~~

具体做法就请大家自己想啦~~（其实是本蒟蒻太懒了）~~，上代码

```cpp
//This program is written by Brian Peng.
#pragma GCC optimize("Ofast","inline","-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
using namespace std;
#define Rd(a) (a=read())
#define Gc(a) (a=getchar())
#define Pc(a) putchar(a)
inline int read(){
	register int x;register char c(getchar());register bool k;
	while(!isdigit(c)&&c^'-')if(Gc(c)==EOF)exit(0);
	if(c^'-')k=1,x=c&15;else k=x=0;
	while(isdigit(Gc(c)))x=(x<<1)+(x<<3)+(c&15);
	return k?x:-x;
}
void wr(register int a){
	if(a<0)Pc('-'),a=-a;
	if(a<=9)Pc(a|'0');
	else wr(a/10),Pc((a%10)|'0');
}
signed const INF(0x3f3f3f3f),NINF(0xc3c3c3c3);
long long const LINF(0x3f3f3f3f3f3f3f3fLL),LNINF(0xc3c3c3c3c3c3c3c3LL);
#define Ps Pc(' ')
#define Pe Pc('\n')
#define Frn0(i,a,b) for(register int i(a);i<(b);++i)
#define Frn1(i,a,b) for(register int i(a);i<=(b);++i)
#define Frn_(i,a,b) for(register int i(a);i>=(b);--i)
#define Mst(a,b) memset(a,b,sizeof(a))
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
#define N (110)
int n,m,r,a[N][N],e[N],x,y,ans;
signed main(){
	Rd(n),Rd(m),*e=Rd(r);
	Frn1(i,1,r){e[i]=e[i-1];while(e[i]*e[i]+i*i>r*r)--e[i];}
	while(m--){
		Rd(x),Rd(y);
		Frn1(i,max(1,y-r),min(n,y+r)){
			++a[max(1,x-e[abs(i-y)])][i];
			--a[min(n,x+e[abs(i-y)])+1][i];
		}
	}
	Frn1(i,1,n)Frn1(j,1,n)if(a[i][j]+=a[i-1][j])++ans;
	wr(ans),exit(0);
}
```

（个人认为如果$n,m,r\leqslant 1000$，这道题至少上绿）

---

## 作者：zhenghaishu (赞：1)


以样例1中的数据为例，共有5 * 5个格子。有两个探测器A和B，探测距离为1个格子。

A能探测到的点为它本身、两个绿色的点、两个黑色的点。B能探测到的点为它本身、两个绿色的点、两个紫色的点。

注意，两个黑色的点既能被A探测到，也能被B探测到，只能算一次，不要重复计算。
所以总共有8个点能被探测到：俩黑色点、俩紫色点、俩绿色点、点A、点B。

其他的点都不能被探测到，比如C点与B点的距离是2，不能被B探测到；C点与A点的距离是根号2，也不能被A探测到。

![在这里插入图片描述](https://img-blog.csdnimg.cn/202002241128432.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2hhaXNodV96aGVuZw==,size_16,color_FFFFFF,t_70) 

算法的思路是把所有的点都枚举一遍，点与探测器的距离可以用勾股定理算出。AC代码如下 ：
```
#include <iostream>
using namespace std;

struct detector //探测器
{
    int x;      //行坐标
    int y;      //列坐标
};

int main()
{
    int n, m, r;
    cin >> n >> m >> r;
    detector det[m + 1]; 
    for(int i = 1; i <= m; i++)
    {
        cin >> det[i].x >> det[i].y;
    }

    int cnt = 0;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            for(int k = 1; k <= m; k++)
            {
                if((i - det[k].x) * (i - det[k].x) + (j - det[k].y) * (j - det[k].y) <= r * r)
                {
                    cnt++;
                    break;  //只要被任意一个点探测到，就要退出循环，不退出会导致计算重复
                }
            }
        }
    }

    cout << cnt;
    return 0;
}
```


---

## 作者：RED_Singer (赞：1)

**这是我第一次发题解,希望多多关照**

我先枚举每个探测器,再枚举每个点离探测器的距离 代码如下:
```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<iomanip>
#include<string>
using namespace std;
bool a[101][101]={0}; 
int main()
{
	int n,m,r,x,y,ans=0;
	cin>>n>>m>>r;
	for(int i=1;i<=m;++i) 
	{
		cin>>x>>y;
		for(int j=1;j<=n;++j)
			for(int k=1;k<=n;++k)//枚举指标
				if(sqrt((x-j)*(x-j)+(y-k)*(y-k))<=r)//计算距离
						a[j][k]=1;
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(a[i][j])++ans;//累加数量
	cout<<ans;
	return 0;
}

```


---

## 作者：PC_DOS (赞：1)

这道题目的数据量并不大，只需要一个一个点枚举然后看一看有没有哪个探测器可以覆盖它即可。

代码:

```cpp
#include <iostream> //输入输出库
#include <cmath> //数学库
#include <algorithm> //算法库头文件
#include <vector> //动态数组头文件
using namespace std;
struct POINT{ //定义一个结构体，存放点的坐标
    double dPointX; //横坐标
    double dPointY; //纵坐标
};
double GetDistace(POINT Point1, POINT Point2){ //求两点间距离的函数
    return sqrt((Point1.dPointX - Point2.dPointX)*(Point1.dPointX - Point2.dPointX) + (Point1.dPointY - Point2.dPointY)*(Point1.dPointY - Point2.dPointY)); //两点间距离公式D(X1,X2,Y1,Y2)=(X1-X2)^2+(Y1-Y2)^2
}
int main(){
    ios::sync_with_stdio(false); //关闭CIN和STDIO的同步关系，加快输入输出速度
    long n, m, r,i,j,k,nCount=0; //n,m,r意义同题设，i,j,k为循环变量，nCount-计数器
    vector<POINT> arrDetectors; //坐标列表，用了动态数组
    POINT tmp; //临时变量
    cin >> n >> m >> r; //输入,m,r
    for (i = 0; i <= m - 1; ++i){ //输入坐标的循环
        cin >> tmp.dPointX >> tmp.dPointY; //读入坐标
        arrDetectors.push_back(tmp); //将坐标放入动态数组
    }
    for (i = 0; i <= n - 1; ++i){ //遍历每一个点
        for (j = 0; j <= n - 1; ++j){
            tmp.dPointX = i + 1; //生成横坐标
            tmp.dPointY = j + 1; //生成纵坐标
            for (k = 0; k <= m - 1; ++k){ //遍历每一个探测器
                if (GetDistace(tmp, arrDetectors[k]) <= r){ //如果在探测范围
                    ++nCount; //计数器加一
                    break; //跳出循环，防止重复计数
                }
            }
        }
    }
    cout << nCount; //输出
    return 0; //结束
}
```

---

## 作者：SLYZ_0120 (赞：1)

蒟蒻的第三篇题解……不知道能不能通过题解……


下面进入正题：

1<=m,n<=100,也就是数据规模其实是非常小的，可以读入以后暴力将整个n×n的矩阵扫一遍，每个点对应利用勾股定理求出与每一个检测的东东的距离（不要开平方直接判断r×r因为可能导致精度???其实不一定的因为这道题的数据大概不会因为这个而wa），如果距离在半径以内就进行判断，如果这个点没有扫过就ans++，然后把这个点标记为1，最后输出答案就可以了。

ps：输入的每一个点都要记得标记为1且ans++，这里的输入数据可能会重复要记得判重……不然就80了，惨痛的回忆……

ps：附上勾股定理——a^2 + b^2 = c^2，虽然不知道有什么用

下面附上代码，不要直接复制可能会爆0哟～


```cpp
//大大的防伪标志
#include<bits/stdc++.h>//万能头文件没毛病
using namespace std;
struct p{ // 我是用自定义变量数组存放读入的检测器的坐标
    int x, y;
}b[101];
int a[101][101] = {0},ans; // 数据规模要注意
double l ;
int main(){
    int n , m , r;
    scanf("%d %d %d",&n,&m,&r);
    for(int i = 1;i<=m;i++){
        scanf("%d %d",&b[i].x,&b[i].y);
        if(a[b[i].x][b[i].y] == 0){
            a[b[i].x][b[i].y] = 1; // 打标记～
        ans ++;} // 读入要判重不然会80分
        }        
    for(int i = 1;i<=n;i++)
        for(int j = 1;j<=n;j++)
            for(int k = 1;k<=m;k++){
                l = (i - b[k].y)*(i-b[k].y) + (j - b[k].y)*(j - b[k].y); // 勾股定理 ，此行有坑小心谨慎
                if(r*r >= l)  //判断这个点是否在扫描范围之内
                    if(a[i][j] == 0){ // 判断这个点有没有扫过
                        a[i][j] = 1; // 标记
                        ans ++; 
                    }
            }
    printf("%d",ans);//大功告成输出吧～
    return 0;
}
```

---

## 作者：倾城ファン恋 (赞：1)

这题就是考察对象归纳：


1.距离坐标公式（在初中会学到）


2.圆的性质（半径啊，直径等等）


3.坐标系的应用


4.模拟算法即可


首先读入（没话说），然后将每个点扫描一遍（记住：千万别以为探测半径只有1，那你只有40分）


最后用数组存一下是否可行（类似于记忆化搜索之类的），输出答案即可，以下为代码部分，供参考，谢谢！


```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
int map[205][205];
int main()
{
    int a,b,n,m,r,ans=0;
    cin>>n>>m>>r;
    for(int i=1;i<=m;i++)//读入
    {
        cin>>a>>b;
        for(int x=a-r;x<=a+r;x++)//穷举每一个点
        {
            for(int y=b-r;y<=b+r;y++)//穷举每一个点
            {
                if(x>=1&&x<=n&&y>=1&&y<=n)//如果在方格范围内
                {
                    if(map[x][y]==0&&sqrt((a-x)*(a-x)+(b-y)*(b-y))<=r)//如果在探测器范围内
                    {
                        map[x][y]=1;//设为标记过(类似于记忆化)
                        ans++;//计数器增加
                    }
                }
            }
        }
    }
    cout<<ans<<endl;//输出结果
    return 0;
}
```

---

## 作者：合451518 (赞：1)

特别水的题目。。。

直接开一个a[]数组达标记，每次读入探测器的坐标之后可以全盘扫描，利用距离公式求两点之间的距离。只要<=r就将它置为1.

最后开一个ans，往里面相加即可。


```cpp
var
 n,m,i,r,x,y,j,k,ans:longint;
 a:array[1..100,1..100] of 0..1;
begin
 readln(n,m,r);
 fillchar(a,sizeof(a),0);
 for i:=1 to m do begin
  readln(x,y);
  for j:=1 to n do
   for k:=1 to n do
    if sqrt(sqr(j-x)+sqr(k-y))<=r then a[j,k]:=1;
 end;
 ans:=0;
 for i:=1 to n do
  for j:=1 to n do inc(ans,a[i,j]);
 write(ans);
end.
```

---

## 作者：AdzearDisjudge (赞：1)

这题可以反过来想，如果一个点可以被探测，那么它一定满足和某个（至少一个）探测器距离小于r，也就是说，距离的平方小于r^2（方便用勾股定理）。

所以枚举每一个点，再枚举每一个探测器，如果满足就打标记并跳出。


**注意：探测器本身能被探测到。**


```cpp
#include<bits/stdc++.h>
#define rep(i,a,n) for(register int i=a;i<=n;++i)
#define per(i,a,n) for(register int i=a;i>=n;--i)
#define elif else if
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
inline int read()
{
    int f=1,x=0;
    char ch;
    do
    {
        ch=getchar();
        if(ch=='-')
        f=-1;
    }
    while(ch<'0'||ch>'9');
    do
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    while(ch>='0'&&ch<='9');
    return f*x;
}
bool s[101][101]={false};
ll n,m,r,t;
struct sc
{
    ll x,y;
}
a[101];
int main()
{
    t=0;
    n=read();
    m=read();
    r=read();
    r=r*r;
    rep(i,1,m)
    {
        a[i].x=read();
        a[i].y=read();
        s[a[i].x][a[i].y]=true;
    }
    rep(i,1,n)
    {
        rep(j,1,n)
        {
            if(s[i][j])
            continue;
            rep(k,1,m)
            {
                if(abs(a[k].x-i)*abs(a[k].x-i)+abs(a[k].y-j)*abs(a[k].y-j)<=r)
                {
                    s[i][j]=true;
                    break;
                }
            }
        }
    }
    rep(i,1,n)
    rep(j,1,n)
    if(s[i][j])
    ++t;
    cout<<t;
    return 0;
}
```

---

## 作者：yz0414 (赞：0)

这题思路就是读入x和y，i和j循环，如果(sqr(abs(i-x))+sqr(abs(j-y))<=r*r),就说明在范围内，就可以把当前这个点赋成true，循环做一遍，如果f[i,j]是true就加1，最后输出。

祝大家AC愉快。

代码：

```pascal
var n,m,i,j,k,sum,r,x,y:longint;
    f:array[1..100,1..100]of boolean;
begin
   readln(n,m,r);
   for k:=1 to m do
     begin
        readln(x,y);
        for i:=1 to n do
          for j:=1 to n do
            if (sqr(abs(i-x))+sqr(abs(j-y))<=r*r) then
             f[i,j]:=true;
     end;
   for i:=1 to n do
     for j:=1 to n do
       if f[i,j] then inc(sum);
   writeln(sum);
end.
```


---

## 作者：Sinwind (赞：0)

------------

# 思路

1. 开始之前：
- 两点(x1,y1),(x2,y2)之间的距离**s =√((x1 - x2) ^ 2 + (y1 - y2) ^ 2)**。
- 注意：探测器的坐标(x,y)，**1 <= x <= 100，1 <= y <= 100**，因此二维数组points应该为points[101][101]。
- PS：答主因为写成points[100][100]，结果有测试点内存越界，没过。

2. 读取网格图的边长n，探测器的个数m，探测器的半径r；

3. 循环将points初始化为0，表示未被探测到；

4. 循环m次读取探测器的坐标(x,y)；
- 每次循环遍历points，若(k,j)与(x,y)的距离小于r **（(k - x) ^ 2+ (j - y) ^ 2<= r ^ 2）**，则points[j][k]=1，表示被探测到；
- 例如：
	- (k,j) = (2,3)，(x,y) = (3,3)，r = 1；
    - (k - x) ^ 2+ (j - y) ^ 2 = 1，r ^ 2 = 1，(k - x) ^ 2+ (j - y) ^ 2= r ^ 2；
    - points[3,2]=1。

5. 遍历points，统计能被探测到的点(为1)的个数count，并输出。
------------

# 代码

```c
#include <stdio.h>
#include <math.h>

int main(void)
{
	int points[101][101];	//网格图，0-不能被探测到，1-能被探测到
	int n;			//网格图的边长
	int m;			//探测器的个数
	int r;			//探测器的半径
	int count = 0;		//能探测到的点的个数

	scanf("%d %d %d", &n, &m, &r);
	//网格图初始化
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			points[i][j] = 0;
		}
	}
	for (int i = 0; i < m; i++)
	{
		int x, y;	//探测器的坐标(x,y)
		scanf("%d %d", &x, &y);
		
		for (int j = 1; j <= n; j++)
		{
			for (int k = 1; k <= n; k++)
			{

				if ((k - x) * (k - x) + (j - y) * (j - y) <= r * r)
				{
					points[j][k] = 1;
				}
			}
		}

	}

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (points[i][j] == 1)
			{
				count++;
			}
		}
	}

	printf("%d\n", count);

	return 0;
}
```



---

## 作者：slzxhry (赞：0)

#这是一道水题

摘要
先把能探测到点标记一下。然后在所有点中枚举，看有没有被标记，如果被标记累加器加1。


详细步骤：


1. 在所以的点中判断是否能探测到（跟据条件每个探测器有个探测半径r）即判断(abs(点的横坐标-探测器的横坐标)的平方+abs(点的纵坐标-探测器的纵坐标)的平方<=探测半径r)。


2. 如果是则标价该点。


3.在所有点中枚举（1..n,1..n)，看有没有被标记，如果被标记累加器加1。


4.完成。


附上代码：


```cpp
var n,m,i,j,k,sum,r,x,y:longint;
f:array[1..100,1..100]of boolean;
begin
readln(n,m,r);
for k:=1 to m do
begin
readln(x,y);
for i:=1 to n do
for j:=1 to n do
begin
if (abs(i-x)*abs(i-x)+abs(j-y)*abs(j-y)<=r*r) then
f[i,j]:=true;
end;
end;
for i:=1 to n do
for j:=1 to n do
if f[i,j] then
inc(sum);
writeln(sum);
end.
```
##我的博客：http://wp.me/p9ioEI-1q


---

## 作者：XiChZ (赞：0)

这里pascal模拟代码（暴力）

解释应该比较详尽了

就是循环，循环，判定，判定~

-----------------------------------------




```cpp
var n,m,r:longint; //n,m,r为题目中的函数
    i,j,k:longint; //i,j,k是pascal和其他语言中常用来循环的变量名称
    x,y:longint; //x,y是储存每一组探测器的坐标变量
    ans:longint; //储存答案的变量
    b:array[1..100,1..100]of 0..1; //一个判断数组，用来存储一个点是否被重复判定计算
procedure input; //初始输入，输入n,m,r
begin
    readln(n,m,r);
end;
function check(x,y,i,j:longint):boolean; //判断函数，判断一个点能否被探测到
begin
    if (abs(j-x)*abs(j-x)+abs(k-y)*abs(k-y)<=r*r) {首先先判断在不在探测器范围内} and (b[j,k]=0) {再判断该点有没有重复} then 
        exit(true) //如果符合条件返回真
    else exit(false); //反之返回假
end;
begin
  input; //输入
  ans:=0; //初始化答案变量
  fillchar(b,sizeof(b),0); //初始化判断数组
  for i:=1 to m do //循环，一共有m组探测器，就循环m遍
  begin
    readln(x,y); //输入这一组的探测器坐标
    for j:=1 to n do
    for k:=1 to n do //把整个矩阵循环一遍
    if (check(x,y,i,j)=true) then //使用判断函数判断，如果返回真就代表着符合返件
    begin
      b[j,k]:=1; //首先先将判断数组从0变成1，那么如果下一次check函数check这个点的时候就会发现不符合条件，返回假，也就不会重复计算
      ans:=ans+1; //答案+1
    end;
  end;
  writeln(ans); //输出最后的答案
end.
```

---

