# Parallelogram is Back

## 题目描述

Long time ago Alex created an interesting problem about parallelogram. The input data for this problem contained four integer points on the Cartesian plane, that defined the set of vertices of some non-degenerate (positive area) parallelogram. Points not necessary were given in the order of clockwise or counterclockwise traversal.

Alex had very nice test for this problem, but is somehow happened that the last line of the input was lost and now he has only three out of four points of the original parallelogram. He remembers that test was so good that he asks you to restore it given only these three points.

## 说明/提示

If you need clarification of what parallelogram is, please check Wikipedia page:

https://en.wikipedia.org/wiki/Parallelogram

## 样例 #1

### 输入

```
0 0
1 0
0 1
```

### 输出

```
3
1 -1
-1 1
1 1
```

# 题解

## 作者：Mickey_jj (赞：5)


看到楼下的两位奆佬都用循环，蒟蒻来一发暴力（~~YiYang2006在题解里骂我，让我很不爽~~）

首先我们要知道，对于任意三角形，分别过它的三个顶点相对边做**平行线**，这三条线会产生三个交点，**而这三个点就是答案！**

（两组对边分别平行呀）


![](https://cdn.luogu.com.cn/upload/pic/61413.png)

像这个图，D，E，F就是答案。。。


问题是，怎么求呢？？(尴尬）

平行四边形有一个特点，对角线互相平分，也就是中点重合。

下面是平行四边形ABCF，我没标字母。在这个图里，A+C=B+F(指坐标）

![](https://cdn.luogu.com.cn/upload/pic/61415.png)

讲的够多了吧......

## CODE出现了！

``` cpp

#include<bits/stdc++.h>
using namespace std;
int x[5],y[5];
int main()
{
    for(int i=1;i<4;i++){
        cin>>x[i]>>y[i];
    }
    printf("%d\n",3);
    printf("%d %d\n",x[1]+x[2]-x[3],y[1]+y[2]-y[3]);
    printf("%d %d\n",x[1]+x[3]-x[2],y[1]+y[3]-y[2]);
    printf("%d %d\n",x[3]+x[2]-x[1],y[3]+y[2]-y[1]);
    return 0;
}
```


---

## 作者：泠小毒 (赞：2)

# Parallelogram is Back
输入一个平行四边形的三个顶点，输出第四个点的可能位置数量和这些位置
## 广告插入
在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/hgoi-20190508/)
## 解法
这就是简单数学推导了，初中的知识吧=-=

第四个点一定只有3种可能，都算出来就好了
## ac代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[5],b[5],suma,sumb;
int main()
{
    for(int i=1;i<=3;i++)scanf("%d%d",&a[i],&b[i]),suma+=a[i],sumb+=b[i];
    puts("3");
    for(int i=1;i<=3;i++)printf("%d %d\n",suma-2*a[i],sumb-2*b[i]);
    return 0;
}
```

---

## 作者：FCB_Yiyang2006✈ (赞：1)

# 蒟蒻这篇和下面那篇红名奆佬思路和写法差不多，但是介绍了原理
## 题解背景
这天阳光灿烂，本蒟蒻也心情大好，但看到了P2399我的题解的

评价，有许多同学的评论让我很不爽像c-x-c, Mickey_jj,

zzh_071105.于是我想：一定要发一篇题解让他们见识见识。

我幸运地找到了这一题，欣喜地发现这不就是刚在函数课上学到

的吗？（幸好我没打瞌睡），写下了这篇蒟蒻题解。

## 原理

平四性质：对角线互相平分

设四个顶点为A,B,C,D且AC,BD为对角线。

### 补充
中点求和公式：中点=两点之和/2。（不说也会）

对角线交点=（A+C)/2=(B+D)/2。

所以：A+B=C+D

上代码

```cpp
#include<bits/stdc++.h>//万能脑袋
using namespace std;
int x[4],y[4];//四个点的X坐标和Y坐标
int sx,sy;//三个点X坐标和Y坐标之和
int main()//主晗二叉树
{
	for(int i=0;i<3;i++)
	{
		cin>>x[i]>>y[i];
		sy=sy+y[i];
		sx=sx+x[i];
	}
	cout<<3<<endl;//一定是3种
	for(int i=0;i<3;i++)
	{
		cout<<sx-2*x[i]<<" "<<sy-2*y[i]<<endl;//所有和减去一个两倍=其他两个和-这个数
	}
	
	return 0;//结束了！结束了！结束了！
}
```
本蒟蒻一向
## 心地善良
这篇题解复制提交可以直接AC.

但是......

# 非紧急情况请勿使用此特殊功能！





---

## 作者：xgwpp6710 (赞：0)

看到 Mickey_jj 巨佬用的和我一样也是暴力，但我的思路和他也有一些不同。

首先应该意识到，在三个点 $A,B,C$ 组成的边中，包含了两边一对角线。比如对角线是 $AB$ ，那么要做的就是作 $CD$ 平行等于 $AB$ ，也就是 $x_c-x_d=x_a-x_b~~~~~~y_c-y_d=y_a-y_b$ 。三种对角线，三种可能。代码：
```cpp
#include<bits/stdc++.h>/
using namespace std;
int main()
{
	int x[4],y[4];
	for(int i=1;i<=3;i++) cin>>x[i]>>y[i];
	cout<<3<<endl<<x[1]+x[2]-x[3]<<" "<<y[1]+y[2]-y[3]<<endl<<x[3]+x[2]-x[1]<<" "<<y[3]+y[2]-y[1]<<endl<<x[1]+x[3]-x[2]<<" "<<y[1]+y[3]-y[2];//1 2 3对应A B C，分别是AB BC BA作为对角线。
	return 0;
}
```

---

## 作者：Eason_AC (赞：0)

## Content
给出平行四边形的三个顶点 $(x_1,y_1),(x_2,y_2),(x_3,y_3)$，求出所有可能的第四个顶点。

**数据范围：$\forall i\in[1,3],-1000\leqslant x_i,y_i\leqslant 1000$。**
## Solution
这题可以通过平行四边形的一个性质轻松搞定——**平行四边形的对角线互相平分**。

啥啥啥？你还不知道什么是平行四边形？

因为太占空间，去[这里](https://www.luogu.com.cn/paste/sig9qt1g)看吧qwq。

那么用这个有什么用呢？

我们都知道，一条线段 $AB$ 的中点计算公式是 $(\dfrac{x_A+x_B}{2},\dfrac{y_A+y_B}{2})$，那么我们来看到下面这个平行四边形：

![](https://cdn.luogu.com.cn/upload/image_hosting/lbdsqhul.png)

那么，我们通过上面这个平行四边形的性质可以得到，$AC$ 和 $BD$ 的中点是同一个点。那么我们就有：

$$\begin{cases}\dfrac{x_A+x_C}{2}=\dfrac{x_B+x_D}{2}&...(1)\\\dfrac{y_A+y_C}{2}=\dfrac{y_B+y_D}{2}&...(2)\end{cases}$$

将 $(1)$ 式和 $(2)$ 式分别都乘上 $2$可以得到：$x_A+x_C=x_B+x_D,y_A+y_C=y_B=y_D$。

所以，现在假设 $A,B,C$ 三个点为题目中的已知点，那么第四个点 $D$ 可以有以下几种：

![](https://cdn.luogu.com.cn/upload/image_hosting/1lul4nfq.png)

我们可以通过计算得到：

$D_1(x_A+x_C-x_B,y_A+y_C-y_B)$  
$D_2(x_A+x_B-x_C,y_A+y_B-y_C)$  
$D_3(x_B+x_C-x_A,y_B+y_C-y_A)$

我们可以发现，有且仅有以上这三个点符合要求。因此，满足点的个数为 $3$，坐标直接按照上面的公式输出即可（顺序可以任意）。
## Code
```cpp
#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;

int x1, y1, x2, y2, x3, y3;

int main() {
	scanf("%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &x3, &y3);
	printf("3\n%d %d\n%d %d\n%d %d", x2 + x3 - x1, y2 + y3 - y1, x1 + x3 - x2, y1 + y3 - y2, x1 + x2 - x3, y1 + y2 - y3);
}
```

---

