# Supercentral Point

## 题目描述

One day Vasya painted a Cartesian coordinate system on a piece of paper and marked some set of points $ (x_{1},y_{1}),(x_{2},y_{2}),...,(x_{n},y_{n}) $ . Let's define neighbors for some fixed point from the given set $ (x,y) $ :

- point $ (x',y') $ is $ (x,y) $ 's right neighbor, if $ x'&gt;x $ and $ y'=y $
- point $ (x',y') $ is $ (x,y) $ 's left neighbor, if $ x'&lt;x $ and $ y'=y $
- point $ (x',y') $ is $ (x,y) $ 's lower neighbor, if $ x'=x $ and $ y'&lt;y $
- point $ (x',y') $ is $ (x,y) $ 's upper neighbor, if $ x'=x $ and $ y'&gt;y $

We'll consider point $ (x,y) $ from the given set supercentral, if it has at least one upper, at least one lower, at least one left and at least one right neighbor among this set's points.

Vasya marked quite many points on the paper. Analyzing the picture manually is rather a challenge, so Vasya asked you to help him. Your task is to find the number of supercentral points in the given set.

## 说明/提示

In the first sample the supercentral points are only points $ (1,1) $ and $ (1,2) $ .

In the second sample there is one supercental point — point $ (0,0) $ .

## 样例 #1

### 输入

```
8
1 1
4 2
3 1
1 2
0 2
0 1
1 0
1 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
0 0
0 1
1 0
0 -1
-1 0
```

### 输出

```
1
```

# 题解

## 作者：Alex_Wei (赞：8)

水题

### 因为这道题目的数据范围只有 $n≤200$，所以我们可以放心地 $O(n^2)$暴力枚举

而且题目也提到了如何判断四个方向

具体细节见代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x[202],y[202],s;//s是最终的答案
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>x[i]>>y[i];
	for(int i=0;i<n;i++){
		int a=0,b=0,c=0,d=0;
		//a,b,c,d分别判断有没有点在点i的上，下，左，右，方
		for(int j=0;j<n;j++){
			if(x[i]<x[j]&&y[i]==y[j])//如果点j在点i的上方
				a=1;//打上标记
			if(x[i]>x[j]&&y[i]==y[j])//如果点j在点i的下方
				b=1;//打上标记
			if(y[i]>y[j]&&x[i]==x[j])//如果点j在点i的左方
				c=1;//打上标记
			if(y[i]<y[j]&&x[i]==x[j])//如果点j在点i的右方
				d=1;//打上标记
		}
		if(a&&b&&c&&d)s++;//如果四个方向都有点则答案+1
	}
	cout<<s;
	return 0;
}
```

求赞，谢谢！

---

## 作者：xiaomuyun (赞：2)

# CF165A Supercentral Point 题解
## 写在前面
看到数据范围，大家就应该知道这是一道暴力题。

[题目传送门](https://www.luogu.com.cn/problem/CF165A)
## 题目分析
### 主要思路
我们可以在输入的时候用 $\operatorname{bool}$ 数组记录每个点，然后枚举每个点，再分别从这个点的上下左右方向暴力。比如说往上走，走到第一个有点的坐标，就记录一下并退出循环，到第 $-1000$ 行为止；或者说往下走，走到第一个有点的坐标，就记录一下并退出循环，到第 $1000$ 行为止。往左往右也是一样。
### 需要注意的地方
#### 一、$|x|,|y|\le 1000$
坐标可以为负数，但是数组的下标不能为负数。所以我们可以开一个三维的 $\operatorname{bool}$ 数组，将第一个下标设为这个坐标的情况，比如说这样：

- $has_{0,i,j}$：表示坐标为 $(x,y)$ 的位置有没有点；
- $has_{1,i,j}$：表示坐标为 $(-x,y)$ 的位置有没有点；
- $has_{2,i,j}$：表示坐标为 $(x,-y)$ 的位置有没有点；
- $has_{3,i,j}$：表示坐标为 $(-x,-y)$ 的位置有没有点。

这样一来，我们就不用担心坐标为负数的点了。
#### 二、存坐标
虽然可以用 $\operatorname{bool}$ 数组来存，但是在遍历每个点的时候，还是需要轻松地得到每个点的位置的。所以我们可以用 $\operatorname{STL}$ 的 $\operatorname{pair}$ 来存，在这里本蒟蒻推荐一个更好的方法。

我们可以设一个大小为 $n×2$ 的一维数组 $a$，对于第 $i$ 个点，它的 $x$ 坐标为 $a_i$，它的 $y$ 坐标为 $a_{n+i}$。这样也是很方便的。
### 优化
不是一定要暴力搜索到 $1000$ 或 $-1000$ 为止的。其实我们可以定义四个变量：$maxx$、$maxy$、$minx$ 和 $miny$。在输入的时候就求出最大和最小的 $x$ 和 $y$，这样就可以在暴力的时候做一些优化了。
## 代码
[链接](https://www.luogu.com.cn/paste/0tl0x8jy)
## 总结
希望大家能看懂本蒟蒻的写法，离开之前希望能够点个赞，毕竟作者制作不易！

---

## 作者：Yaixy (赞：2)

# 题意及注意点

- 在一个平面直角坐标系中，给定 $n$ 个点。求有多少个点满足在它的**正**上方，**正**下方，**正**左方，**正**右方都有点。

- 这里的正上方，正下方，正左方，正右方**不一定**是指相邻的 $4$ 个点，**只要为正方向都可以**。

- ~~从数据范围来看，~~ 简单的**模拟**就可以解决。

# 思路

- 在读入过后，~~窝掐指一算~~，我们可以发现数据范围支持暴力枚举，所以可以暴力**枚举**一遍，判断每个点是否在其他 $n-1$ 个数的正上方，正下方，正左方或正右方并记录下来。

- 接下来，就只有一步了：**将记录下来的信息进行处理**，判断它的正上方，正下方，正左方，正右方是否有点，如果都有就更新计数器。

- 再想一想，其实上面所说一步在**循环枚举的结尾**就可以完成，加一个判断语句，处理一下就好了。（具体操作可以见代码qwq）

# 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int i,j,n,x[100005],y[100005],flag,flag2,flag3,flag4,ans;
void qwq(int i,int j)//枚举判断
{
	if(x[i]<x[j]&&y[i]==y[j]) flag=1;
	if(x[i]>x[j]&&y[i]==y[j]) flag2=1;
	if(x[i]==x[j]&&y[i]>y[j]) flag3=1;
	if(x[i]==x[j]&&y[i]<y[j]) flag4=1;
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for(i=1;i<=n;i++) cin>>x[i]>>y[i];
	for(i=1;i<=n;i++)
	 {
	 	flag=flag2=flag3=flag4=0;
	 	for(j=1;j<=n;j++) qwq(i,j);
if(flag==1&&flag2==1&&flag3==1&&flag4==1) ans++;
	 }
	cout<<ans;
	return 0;
}
```

撒花完结awa

---

## 作者：jxbe6666 (赞：0)

一道非常好的水题

**题目分析：** 只要有点在它的正上方，正下方，正左方，正右方。这个点就属于答案的一个。（切记是在正什么方向,不是在相邻格）。

至于如何判断方向就直接看代码吧!

$This \ is \ my  \ AC  \ Code \downarrow$  
```cpp
#include <bits/stdc++.h>
using namespace std;
int x[205], y[205], n, sum;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> x[i] >> y[i];
    }
    for (int i = 1; i <= n; i++)
    {
        int a = 0, b = 0, c = 0, d = 0; //全部为 0
        for (int j = 1; j <= n; j++)
        {
            if (x[i] < x[j] && y[i] == y[j])
                a = 1; //如果在正上方
            if (x[i] > x[j] && y[i] == y[j])
                b = 1; //如果在正下方
            if (y[i] < y[j] && x[i] == x[j])
                c = 1; //如果在正右方
            if (y[i] > y[j] && x[i] == x[j])
                d = 1; //如果在正左方
        }
        if (a && b && c && d)
            sum++; //答案 ++
    }
    cout << sum;
    return 0;
}

```
[AC](https://www.luogu.com.cn/record/64116390)

---

## 作者：Waaifu_D (赞：0)

~~水题~~

CF题的翻译还是一如既往的...直白

平面直角坐标系，初中基础知识，不再解释，其他题解已经解释的很清楚了（还画了图）

其实这题最重要的是读题，我第一次就读错了题，以为是上下左右一个格内有点才算，然后打了个DFS，成功抱零

[错误示范](https://www.luogu.com.cn/paste/dvlh013p)

正确代码↓

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans,x[210],y[210];//ans储存答案，xy分别储存坐标
int main()
{
	cin>>n;
	for(int i=1; i<=n;i++)
	{
		cin>>x[i]>>y[i];//输入
	}
	for(int i=1; i<=n;i++)
	{
		int up=0,down=0,right=0,left=0;
		for(int j=1; j<=n;j++)
		{
			if(x[i]<x[j]&&y[i]==y[j]) up++;//在正上方
			if(x[i]>x[j]&&y[i]==y[j]) down++;//在正下方
			if(y[i]>y[j]&&x[i]==x[j]) right++;//在右边
			if(y[i]<y[j]&&x[i]==x[j]) left++;//在左边
		}
		if(up&&down&&right&&left) ans++;//四个条件都满足，ans++
	}
	cout<<ans<<endl;
	return 0;
}
```
顺便说两句，如果if语句后只包含一个语句，直接写在if后会很整齐~~好看~~

---

## 作者：TRZ_2007 (赞：0)

题解 [CF165A 【Supercentral Point】](https://www.luogu.com.cn/problem/CF165A)  
# Solution  
其实这道题目非常的简单，由于 $n \le 100$ ，我们可以考虑**枚举**。  
但是怎么确定一个点的**正**上，下，左，右的方向呢？  
我们来看看这个图：  
![](https://cdn.luogu.com.cn/upload/image_hosting/na16nayk.png)  
通过观察可以知道：  
- 1：如果一个点 $(x_1,y_1)$ 在另一个点 $(x,y)$ 的**正上方**，那么可得：$x_1 > x$，$y_1 = y$。  
- 2：如果一个点 $(x_1,y_1)$ 在另一个点 $(x,y)$ 的**正下方**，那么可得：$x_1 < x$，$y_1 = y$。  
- 3:如果一个点 $(x_1,y_1)$ 在另一个点 $(x,y)$ 的**正左方**，那么可得：$x_1 = x$，$y_1 < y$。  
- 4:如果一个点 $(x_1,y_1)$ 在另一个点 $(x,y)$ 的**正右方**，那么可得：$x_1 = x$，$y_1 > y$。    


根据我们以上的推论，我们就可以敲代码了。  

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 209;

int n,a,b,c,d,ans;
int x[N],y[N];

int main() {
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) {
		scanf("%d %d",&x[i],&y[i]);
	}
	for(int i = 1;i <= n;i++) {
		a = b = c = d = 0;
		for(int j = 1;j <= n;j++) {
			if(x[i] < x[j] && y[i] == y[j]) {
				a = 1;
			}
			if(x[i] > x[j] && y[i] == y[j]) {
				b = 1;
			}
			if(x[i] == x[j] && y[i] > y[j]) {
				c = 1;
			}
			if(x[i] == x[j] && y[i] < y[j]) {
				d = 1;
			}
		}
		if(a && b && d && c) ans++;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Franka (赞：0)

### **题目**
给定n个点，求有多少个点满足在它的**正上方**，**正下方**，**正左方**，**正右方**都有点。
### **思路**
首先把样例1的图画出来：

![](https://cdn.luogu.com.cn/upload/image_hosting/vpa99m8v.png)

#### 可以发现，要求这个点是否满足要求，只需进行如下判断:

当$x$坐标和这个点的$x$坐标相等时，如果$y$坐标比这个点的y坐标大，则是上方点；

当$x$坐标和这个点的$x$坐标相等时，如果$y$坐标比这个点的y坐标小，则是下方点；

当$y$坐标和这个点的$x$坐标相等时，如果$x$坐标比这个点的x坐标大，则是右方点；

当$y$坐标和这个点的$x$坐标相等时，如果$x$坐标比这个点的x坐标小，则是左方点；

空间复杂度:$O(n)$；

时间复杂度:$O(n*4*n)$。
### **代码**
```pascal
var
 x,y:array[0..201] of longint;
 n,i,sum,j,s:longint;
begin
 readln(n);
 for i:=1 to n do readln(x[i],y[i]);
 for i:=1 to n do
  begin
   sum:=0;//sum清零
   for j:=1 to n do
    if(x[i]=x[j])and(y[i]>y[j])then//查找上面
     begin
      inc(sum);//sum加一
      break;//找到了就不必找了
     end;
   for j:=1 to n do
    if(x[i]=x[j])and(y[i]<y[j])then//查找下面
     begin
      inc(sum);
      break;//同理
     end;
   for j:=1 to n do
    if(y[i]=y[j])and(x[i]>x[j])then//查找右面
     begin
      inc(sum);
      break;
     end;
   for j:=1 to n do
    if(y[i]=y[j])and(x[i]<x[j])then//查找左面
     begin
      inc(sum);
      break;
     end;
   if sum=4 then inc(s);//读入四个方向都有，标记
  end;
 writeln(s);
end.
```


---

## 作者：luosw (赞：0)

平面直角坐标系，我们就只能使用平面直角坐标系（可以建立两个变量，放在$1$个结构体里面）去解决这个问题了。我们先来分析一下题目。

---

### 题意简述
在一个平面直角坐标系中，给定$n$个点。求有多少个点满足在它的正上方，正下方，正左方，正右方都有点。
首先我们要知道，什么叫做平面直角坐标系，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/rf68zv9i.png)

所以：**平面直角坐标系是由两个互相垂直数轴搭建的**，平面直角坐标系的点有对应的坐标，原点$O$的坐标是$(0,0)$给出的输入数据就是已知有点的坐标。

平面直角坐标系还有$4$个象限，看图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ny5dld6b.png)

好的，我们知道了平面直角坐标系的定义后，我们就可以展开题目的分析了。

---

### 题目分析

我们可以梳理一下：

- 通过结构体，一个变量表示平面直角坐标系第$x$，一个变量表示$y$。

- 当一个已知点的四周没有坐标轴或原点的时候，就不用跨开结构体的变量去判断。

- 一旦一个已知点的四周有坐标轴或原点，就要切换到另一个结构体变量去判断。

- 如果有点，我们就标记。

- 最后输出判断。

> 这里利用的是桶排序的思想

好，判断结束放代码：

---

### $Code$
```cpp


#include <iostream>
#include <cstring>
using namespace std;
#define maxn 250 
struct coordinate{
    int x,y;
}pp[maxn];
int n; 
int main(){
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>pp[i].x>>pp[i].y;
    int a,b,c,d;
    int cnt=0;
    for(int i=0;i<n;i++){
        int tx=pp[i].x;
        int ty=pp[i].y;
        a=b=c=d=0;
        for(int j=0;j<n;j++){
            if(j!=i){
            if(pp[j].x>tx and pp[j].y==ty)
                a=1;
            if(pp[j].x< tx and pp[j].y==ty)
                b=1;
            if(pp[j].x==tx and pp[j].y>ty)
                c=1;
            if(pp[j].x==tx and pp[j].y<ty)
                d=1;
            }	//一次判断每个点 
            if(a and b and c and d){
                cnt++;
                break;
            }	//八个点全部都有，计数器++ 
        }
    }
    cout<<cnt<<endl;
    return 0;
}
```



---

