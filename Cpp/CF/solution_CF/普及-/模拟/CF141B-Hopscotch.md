# Hopscotch

## 题目描述

So nearly half of the winter is over and Maria is dreaming about summer. She's fed up with skates and sleds, she was dreaming about Hopscotch all night long. It's a very popular children's game. The game field, the court, looks as is shown in the figure (all blocks are square and are numbered from bottom to top, blocks in the same row are numbered from left to right). Let us describe the hopscotch with numbers that denote the number of squares in the row, staring from the lowest one: 1-1-2-1-2-1-2-(1-2)..., where then the period is repeated (1-2).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF141B/3cab0cfd180f2a7ceceec93813314c6b7ddd8ea0.png)The coordinate system is defined as shown in the figure. Side of all the squares are equal and have length $ a $ .

Maria is a very smart and clever girl, and she is concerned with quite serious issues: if she throws a stone into a point with coordinates $ (x,y) $ , then will she hit some square? If the answer is positive, you are also required to determine the number of the square.

It is believed that the stone has fallen into the square if it is located strictly inside it. In other words a stone that has fallen on the square border is not considered a to hit a square.

## 样例 #1

### 输入

```
1 0 0
```

### 输出

```
-1
```

## 样例 #2

### 输入

```
3 1 1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
3 0 10
```

### 输出

```
5
```

## 样例 #4

### 输入

```
3 0 7
```

### 输出

```
-1
```

## 样例 #5

### 输入

```
3 4 0
```

### 输出

```
-1
```

# 题解

## 作者：常青藤 (赞：5)

## 对于这道~~很简单的平面直角坐标系的~~题，当然是华丽丽的$O(1)$算法

### 1. 判断是否在边界上（$a|y$），是否在第一、二象限($y>0$)

### 2. 接着，判断 $y$ 是否比 $a$ 小，$x$是否在第一个正方形内
### ~~蒟蒻的~~说明图

![](https://cdn.luogu.com.cn/upload/pic/39318.png)


### 3. 将$y$减去$a$（删去第一层），$dir=\frac{y}{2a}+1$ 表示其所在的层数

### 4. 然后就可以得到当前可能位置下的个数 $bottom=(dir-1)*3+2;$ ，并把可能位置以下的层数减去

### 5. 最后再做一遍第一步的判断，然后就是华丽的输出和华丽的分割线

## 整数除整数与小数比较前请务必先 $*1.0$ ! ! !  ~~（别问我怎么知道的）~~
------------


```cpp
#include<isotream>
#include<stdio>
using namespace std;
int a,y; double x;
void wrok();
int main()
{
    cin<<a<<x<<y;
    if(y%a==0 || y<=0) printf("-1");
    else work();
    return 0;
}
void work()
{
    if(y>0 && y<a && x>-a*1.0/2 && x<a*1.0/2)
        {printf("1"); return;}
    y-=a;
    int dir=y/(2*a)+1;
    int botom=(dir-1)*3+2;
    y-=(dir-1)*2*a;
    if(y>0 && y<a)
        if(x>-a*1.0/2 && x<a*1.0/2)
        {
            printf("%d",bottom); return;
        }
    if(y>a && y<a*2)
    {
        if(x==0) {printf("-1"); return;}
        if(x>-a && x<0)
        {
            printf("%d",bottom+1); return;
        }
        else
            if(x>0 && x<a)
            {
                printf("%d",bottom+2); return;
            }
    }
    printf("-1");
}
```
最后祝~~大家~~我 $NOIP2018$ $rp++$

#### （电视机前的小朋友们，代码里的五处错误你们都找出来了吗？）

---

## 作者：makerlife (赞：2)

[洛谷题目传送门](https://www.luogu.com.cn/problem/CF141B) | [CF 原题传送门](https://codeforces.com/problemset/problem/141/B)

## 思路

~~大~~模拟 ~~（比[猪国杀](https://www.luogu.com.cn/problem/P2482)小多了）~~

开始正经起来

注：本题解所说的“层数”均为**总层数去掉一层的**，因为第一层不在循环节内。（即 $8$ 所在的那一层我们叫做第五层，而非第六层）

先看一个本蒟蒻画的~~草~~图

![](https://cdn.luogu.com.cn/upload/image_hosting/ch6m6quu.png)

这道题需要先判断很多，有很多小细节需要注意： ~~（别问我怎么知道的，看我 CF 的提交记录就知道了）~~

1. 判断坐标是不是**在第 $1$ 或第 $2$ 象限**，如果不在直接输出 $-1$。

1. 判断 $y$ 坐标是否在正方形边界上，如果不在直接输出 $-1$。

1. 特判第一层。

把以上部分预处理完毕，再来计算 $y$ 坐标在第几层上。

然后判断层数为奇数层或层数为偶数层的情况：

### 层数为偶数层

首先明确，层数为偶数层时，每一层有 $2$ 个正方形，即需要推出两个式子。

我们可以先推出在第二象限的正方形的数字：由题意得，除第一层外，每 $3$ 个正方形为一循环，那在第二象限的正方形的数字就很好推了，就是本轮循环的最后一个数字 $-1$ 再 $+1$，也就是本轮循环的最后一个数字，为：$\frac{3n}{2}$。

那在第一象限的正方形的数字就是 $\frac{3n}{2} +1$ 了。

知道了这些，还要特判一下 $x$ 坐标是否在正方形内部，如果不在直接输出 $-1$。

### 层数为奇数层

式子也很好推，即为 $\lfloor \frac{n}{2} \rfloor \times 3 +2$。

也要特判 $x$ 坐标是否在正方形内部，如果不在直接输出 $-1$。

 _如果看不明白就看看代码吧。 ~~你肯定现在已经明白了（确信）~~_ 
 

## 代码

```cpp
#include<cmath>
#include<cstdio>
#include<iostream>
using namespace std;
int a,x,y,n;//n为层数
int main()
{
	scanf("%d%d%d",&a,&x,&y);
	int n=y/a;//计算除第一层外的层数（总层数-1）
	if(y<=0)//不在第1或第2象限
	{
		printf("-1\n");
		return 0;
	}
	if(y%a==0)//y坐标在正方形边界上
	{
		printf("-1\n");
		return 0;
	}
	if(n==0)//特判第1层
	{
		if(y<a && abs(x)>=a/2.0)//如果不在正方形内
		{
			printf("-1\n");
			return 0;
		}
		else
		{
			printf("1\n");
			return 0;
		}
	}
	if(n%2==0)//为偶数层
	{
		if(abs(x)>=a || x==0)//x坐标在正方形外
		{
			printf("-1\n");
			return 0;
		}
		if(x<0)//在第2象限
		{
			printf("%d\n",3*n/2);
			return 0;
		}
		else//在第1象限
		{
			printf("%d\n",3*n/2+1);
			return 0;
		}
	}
	else//为奇数层
	{
		if(abs(x)>=a/2.0)//x坐标在正方形外
		{
			printf("-1\n");
			return 0;
		}
		printf("%d\n",n/2*3+2);
	}
	return 0;
}
```

这是本蒟蒻写的最长的一篇题解了，望管理大大通过啊

[AC Record](https://www.luogu.com.cn/record/68981745)

---

## 作者：YangXiaopei (赞：1)

## 前言：
仅供初学者，大佬勿入。
## Solution：
一个简单的模拟。

先判断是否会输出 $-1$。
* 横左标为 $a$ 的倍数。
* 纵坐标在线上。
* 不在正方体上。

这几种代码都挺简单，就不讲了。这儿主要讲讲如何找在几号积木块。
* 先找出位置在第几行。
* 再找出此行有奇数个还是偶数个。
* 然后找出此行的最后一几号。
* 最后看坐标在左还是在右（奇数个的不用判）。
* 然后输出即可。

```cpp
int b = x / a + 1;//行数
b--;
int c = 0;
if(b % 2 == 0){//此行偶数个
    c = b / 2 * 3 + 1;
    if(y < 0){//左
        cout << c - 1;
    }
    else{//右
	    cout << c;
    }
}
else{//此行奇数个
    c = b / 2 * 3 + 2;
    cout << c;
    return 0;
}
```
## 完结撒花。

---

## 作者：yzy041616 (赞：1)

[题目传送门](/problem/CF141B)

## Part.1 题目

~~自己看翻译~~

就是有很多堆积着的 $a\times a$ 的方块，这些方块有一个规律，就是如果最底下的方块算作第 $0$ 层的话，那么除了第 $0$ 层之外，奇数层都堆一个，偶数层都堆两个。然后给你一个点，让你判断这个点在不在某一个方块里，如果在，还要求出是第几个方块。

方块堆积图：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF141B/3cab0cfd180f2a7ceceec93813314c6b7ddd8ea0.png)

## Part.2 思路

首先我们发现所有的正方形覆盖的区域都满足 $y\ge 0$，所以如果 $y<0$，那就肯定不在。

其次是如果 $|x|\ge a$，那就说明这个点太靠旁边了，也不行。

然后是如果这个点在横着的某条边上，即 $y\bmod a=0$，那么肯定也不行。

剩下的，基本上都是可以的了。

之所以没有把竖的边也先拿出来排除，是因为每一层的竖着的边位置不一样，需要分类讨论。

那么就开始分类讨论吧。

先根据 $y$ 来算出层数（设层数为 $c$，则 $c=\dfrac{y}{a}$），然后再判断一下，如果是第 $0$ 层或者奇数层的话就只有一个方块，所以必须满足 $|2\times x|<a$，才在一个方块里。

那么是第几个方块呢？不难发现，奇数层时，方块编号为 $\dfrac{3(c+1)}{2}$，第 $0$ 层时，方块编号就是 $1$。所以方块的编号为 $\max(1,\dfrac{3(c+1)}{2})$。

另外一种情况，就是非零的偶数层时，有两个方块，如果 $x=0$，这个点就在方块的边线上，要去掉。方块的编号的算法在这里就不赘述，为 $\dfrac{3c}{2}+\dfrac{x+a}{a}$。

## Part.3 代码

```cpp
#include<iostream>
using namespace std;
int a,x,y;//定义三个正整数，一个叫a……
int _main(){
	if(y%a==0)return-1;
	if(y<0)return-1;
	if(abs(x)>=a)return-1;
	//以上为一开始讨论的三种不可能情况
	int c=y/a;
	if(c==0||c%2){
		if(abs(2*x)>=a)return-1;
		else return max(1,(c+1)/2*3-1);
	}
	//以上为第0层或者奇数层的情况
	if(c&&c%2==0){
		if(x==0)return-1;
		else return c/2*3+(x+a)/a;
	}
	//以上为非零偶数层的情况
}
int main(){
	cin>>a>>x>>y;
	cout<<_main();
}
```

---

## 作者：飞啾6373 (赞：1)

### 题意

给出一些格子的排列方式，再给出一个点的坐标，判断该点是否在格子里，在哪一个格子里。

### 思路

一道模拟题，用分支结构即可解决，不需要循环。

首先判断是否在横向边界上，是的话直接输出，结束程序。

接下来会有两个分支，判断所处的那一层是一格还是两格。如果是两格还需要特判中线。（判断具体哪一格在代码注释里讲解）

在每一个分支中判断一下是否在纵向边界上或格子外面即可。

小提示：编号为 $1$ 的格子不在其它格子判断的规律中，需要特判。

### 代码

↓配合注释食用

```
#include<bits/stdc++.h>//左：3q/2 右：3q/2+1 
using namespace std;
bool lucky=true;
int main()
{
	int a,x,y,q;
	cin>>a>>x>>y;
	q=y/a;//y轴上的第q个
	if(q*a==y)//在横向边界上
	{
		cout<<"-1";return 0; 
	} 
	if(q==0) 
	{
		double d=(a*1.0)/2.0;
		if(abs(x)>=d)//在竖向边界上或外面 
		{
			cout<<"-1";return 0; 
		}
		cout<<1;return 0;
	}
	if(q%2==0) 
	{
		if(x==0)//中线 
		{
			cout<<-1;return 0;
		}
		if(abs(x)>=a) //边界或外面 
		{
			cout<<-1;return 0;
		} 
		if(x<0)
		{
			cout<<3*q/2;return 0;
		}
		if(x>0)
		{
			cout<<3*q/2+1;return 0;
		}
	} 
	if(q%2==1)
	{
		double d=(a*1.0)/2.0;
		if(abs(x)>=d)//在竖向边界上或外面 
		{
			cout<<"-1";return 0; 
		}
		cout<<(q+1)/2*3-1;return 0;
	}
	cout<<-1;
	return 0;
}
```


---

## 作者：shAdomOvO (赞：1)

# 其实这就是一道数学题
## 思路：

这道题其实跟代码能力关系不大，是一道思维题，可以做到 $ O(1) $ 算法。

### 输入：

输入有三个数， $ a,x,y $ ， $ a $ 是正方形的边长。 $ x,y $ 分别是要查询的点的坐标。

### 做法：

第一步，是要计算这个点所在的层数，用来判断。即：
```cpp
m=y/a;
if(y%a!=0||y<=a)m++;//计算层数
```

同时，也不要忘了一些特判，即 $ y $ 在正方形的边上
```cpp
if(y%a==0||y==0){//y在正方形边上也不行
        cout<<-1;
        return 0;
    }
```

第二步:根据在奇偶层来计算，除第一层外，奇数层为两个，偶数层为一个。

奇数层即 $ x $ 不等于 $ 0 $ ，并且绝对值小于 $ a $ ,偶数层即 $ x $ 绝对值小于二分之一 $ a $ 。

### 小坑：
要注意如果两个数比较，一个是整数，一个是小数，要将整数乘以 $ 1.0 $ ,或除以 $ 1.0 $ 。

## 代码（请勿抄袭）：
```cpp
#include<bits/stdc++.h>
using namespace std;
float n,x;
int a,y,q=1,m;//q来判断奇偶层 
int main(){
	cin>>a>>x>>y;
	m=y/a;
	if(y%a!=0||y<=a)m++;//计算层数 
    if(y%a==0||y==0){//y在正方形边上也不行
        cout<<-1;
        return 0;
    }
	if(m==1){//第一层特判 
		if(abs(x)<float(a/2.0))cout<<"1";//在不在正方形内 
		else cout<<-1;
		return 0;
	}
	else{
		if(m & 1){//为奇数层 一层两个方块 
			if(abs(x)<a*1.0){
                if(x==0)cout<<-1;
				else if(x<0)cout<<(m-3)/2*3+3;//计算方块数，相信大家只要仔细想，自己也可以想出来，就不解释了
                else cout<<(m-3)/2*3+4;
                return 0;
			}
			else cout<<-1;
			return 0;
		}
        else{//为偶数层 一层一个方块
            if(abs(x)<float(a/2.0))cout<<(m-2)/2*3+2;
            else cout<<-1;
            return 0;
        }
	} 
}
```



---

## 作者：LiJinLin_AFO (赞：0)

# CF141B 题解

~~我的天调了半个多小时才出来~~



------------


## 正文开始

首先，我们要判断这个点可不可能在正方形里。显然，当  $\displaystyle \mid x \mid \ge n$  时，即坐标点在这些正方形的左、右侧边或左、右边，根据题意是不可能的。同时，所有正方形都在x轴以上，当  $\displaystyle y<0$  时，同样不可能。

其次，我们要判断坐标所在正方形的行数，再利用公式推导。假设正方形 $\displaystyle 1$ 所在的行为第 $\displaystyle 0$ 行， $\displaystyle 2$ 在第 $\displaystyle 1$ 行， $\displaystyle 3$ 、 $\displaystyle 4$ 在第 $\displaystyle 2$ 行，依次类推（因为方便）。

设行数  $\displaystyle c$  ，用公式  $\displaystyle c=\tfrac{y}{n}$  可以算出行数。



------------


分情况讨论：

- 第0行：如果 $\displaystyle \mid 2 \times x \mid < n$ ，就输出 $\displaystyle 1$ ，否则输出 $\displaystyle -1$ 。

- 第偶数行：如果 $\displaystyle x>0$ 且 $\displaystyle x<n$ ，说明在右边的正方形里，因为每两行都有三个正方形，所以公式： $\displaystyle 1+3 \times \tfrac{1}{2}c$ ； 如果 $\displaystyle x<0$  并且  $\displaystyle x>-1 \times n$ ，说明在左边正方形里，与上方推理类似。公式： $\displaystyle 3 \times \tfrac{1}{2}c$ ；其余情况不存在，输出 $\displaystyle -1$ 。

- 第奇数行：如果 $\displaystyle \mid 2 \times x \mid < n$ ，说明在正方形里，同样因为每两行有三个正方形，所以公式： $\displaystyle \tfrac{c+1}{2} \times 3 -1$ ，否则不存在，输出 $\displaystyle 0$ 。



------------

```cpp
#include<bits/stdc++.h>
using namespace std;
void out(){
	printf("-1");
	exit(0);
}//情况不存在的输出
int main(){
	int n,x,y;
	scanf("%d%d%d",&n,&x,&y);
	if(y%n==0||abs(x)>=n) out();//这种情况一定不存在
	int hang=y/n;
	if(!hang){
		if(abs(x*2)<n){
			putchar('1');
			return 0;
		}
		else out();
	}//第0行
	if(hang&1==1){
		if(abs(x*2)<n) printf("%d",(hang+1)/2*3-1);
		else out();
	}//奇数行
	else{
		if(x>0&&x<n) printf("%d",1+3*((hang)/2));
		else if(x<0&&x>-n) printf("%d",3*(hang/2));
		else out();
	}//偶数行
	return 0;
}
```
注：请勿抄袭！

---

## 作者：SnapYust (赞：0)

## 题目传送门

[Hopscotch](https://www.luogu.com.cn/problem/CF141B)

## 思路

水题，所以本题解通俗易懂适用于初学者观赏（欢迎纠正错误）

首先，我们可以判断出来，若：$|x|\ge a$ 或 $y\le0$，则**输出**`-1`

若 $x,y$ 满足条件的话，则进行下一步：**判断 $y$ 位于第几层**

出于方便，我们不妨先把 $a$ 设为 $1$，则每一层的高度都为 $1$

设 $y$ 处于第 $n$ 层，不难发现：$n=y$ 即：$n=\dfrac{y}{1}$

若 $a=2$，则：$n=\dfrac{y}{2}(y\bmod 2=0)$

显然，以上只适用于 $y$ 为**偶数**情况，将特殊化为一般，若 $y=5$，则 $\dfrac{y}{2}=2.5$，我们发现此时 $y$ 需要**向上取整**，即得：$n=\left\lceil\dfrac{y}{2}\right\rceil$

所以，$a$ 为任意正整数时：$n=\left\lceil\dfrac{y}{a}\right\rceil$

同时，我们还可以得出来：当 $y\bmod a=0$ 时，输出`-1`

下一步：确定**第 $n$ 层有几个什么方块**

由题意，自第二层开始按“$1,2,1,2…$”的顺序排列，设第 $n$ 层有 $k$ 个方块，不难得出：

若 $n=1$，则 $k=1$；

若 $n>1$ 且 $n\bmod 2 = 0$，则 $k=1$；

若 $n>1$ 且 $n\bmod 2 = 1$，则 $k=2$；

所以：当 $n=1$ 或 $n>1,n\bmod 2=0$ 时，若 $|x|\ge\dfrac{a}{2}$，则输出`-1`

所以当 $(n-1)\bmod2=0$ 时，第 $n$ 层 $x$轴正半轴的数字为：$m=\dfrac{3(n-1)}{2}+1$

当 $(n-1)\bmod2\ne0$ 时，第 $n$ 层 $x$轴正半轴的数字为：$m=3\left\lfloor\dfrac{(n-1)}{2}\right\rfloor+2$

然后根据 $x$ 的取值去找对应的 $m$ 即可，代码就不放了

## 总梳理

（谨慎观看）

可得：

$$
ans=\begin{cases}|x|\ge a\to-1\\y\le0\to-1\\y\bmod a=0\to-1\\n=\left\lceil\dfrac{y}{a}\right\rceil\begin{cases}n=1\begin{cases}|x|\ge\dfrac{a}{2}\to-1\\|x|<\dfrac{a}{2}\to 1\end{cases}\\n>1\begin{cases}n\bmod2=0\begin{cases}|x|\ge\dfrac{a}{2}\to-1\\|x|<\dfrac{a}{2}\to 3\left\lfloor\dfrac{(n-1)}{2}\right\rfloor+2\end{cases}\\n\bmod2=1\begin{cases}x>0\to\dfrac{3(n-1)}{2}+1\\x=0\to-1\\x<0\to\dfrac{3(n-1)}{2}\end{cases}\end{cases}\end{cases}\end{cases}
$$


---

## 作者：jasonshen_ (赞：0)

一道还算行的模拟题。

分析：
在最前面先判断会不会输出`-1`，并且进行简单的判断。

下面有三种情况：

- 横坐标（$x$）上的值 $a\mod{2}=0$。
- 纵坐标 $y = 0$。

- 不在正方体上。

这三种都是简单的判断，不再多言。

下面重点说横纵坐标在哪一个正方形。

原图：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF141B/3cab0cfd180f2a7ceceec93813314c6b7ddd8ea0.png)
第一步：寻找在第几行
![](https://cdn.luogu.com.cn/upload/image_hosting/49czxzgo.png)
第二步：判断当前行的奇偶性（$size\mod{s} = 0$ 或 $size \mod{2} = 1$）。
![](https://cdn.luogu.com.cn/upload/image_hosting/25h6dmsk.png)
第三步：然后找出此行的最后一位。

第四步：如果 $size\mod{2} = 1$，看坐标在左还是在右。

------------
----------

code
```cpp

#include <bits/stdc++.h>
using namespace std;
#define ll long long;

int main()
{

    int a, x, y;
    cin >> a >> x >> y;

    if (y == 0 || abs(x) >= a || y % a == 0)
    {
        cout << -1;
        return 0;
    }

    int level = (y / a) + 1;
    int ans;
    if (level == 1)
    {
        if (abs(x) >= (a + 1) / 2)
        {
            ans = -1;
            cout << ans;
            return 0;
        }
        else
        {
            ans = 1;
        }
        cout << ans;
        return 0;
    }

    else if (level % 2 == 1)
    {

        int odd_levels = level / 2;
        int ans = odd_levels * 2 + (odd_levels - 1) + 2;
        if (x < 0)
        {
            --ans;
        }
        if (x == 0)
        {
            ans = -1;
            cout << ans;
            return 0;
        }
        cout << ans;
        return 0;
    }
    else
    {
        int odd_levels = (level - 1) / 2;
        ans = odd_levels * 2 + (odd_levels + 1) + 1;
        if (abs(x) >= (a + 1) / 2)
        {
            ans = -1;
            cout << ans;
            return 0;
        }
        cout << ans;
        return 0;
    }

    return 0;
}


```

---

