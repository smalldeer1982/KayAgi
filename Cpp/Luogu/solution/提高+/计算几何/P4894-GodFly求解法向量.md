# GodFly求解法向量

## 题目背景

“遇到函数无脑求导，遇到几何无脑建系。”是铁头娃的公共特征。

作为喜欢建系的一个铁头娃，$GodFly$经常需要计算法向量。

## 题目描述

定义平面$\alpha$内有两相交向量$\overrightarrow a=(x_1,y_1,z_1)$，$\overrightarrow b=(x_2,y_2,z_2)$，若$\overrightarrow z=(x,y,z)$为平面$\alpha$的法向量，则：

![](https://cdn.luogu.com.cn/upload/pic/30949.png)

现给出$\overrightarrow a$及$\overrightarrow b$的坐标，求出一个法向量$\overrightarrow z$，并输出其坐标。

**SPJ已更新**

## 说明/提示

**【数据范围】**

所有坐标（包括答案）均在$32$位**整数**范围内。

对于$30$%的数据，只有单组输入；

对于$100$%的数据，输入组数$<=5*10^4$，且输入的坐标均为绝对值不超过$5*10^4$的正整数；

样例数据在**data.zip\vector\**中。

**【提示】**

本题有$Special$ $Judge$，输出任意一组解即可。

## 样例 #1

### 输入

```
1 2 3 3 2 1```

### 输出

```
1 -2 1```

# 题解

## 作者：SuperJvRuo (赞：14)

这题没个题解，来补一篇。

直接输出两个向量的向量积（叉积）即可AC。

设三个轴上的单位向量分别为$i,j,k$，两个向量分别为$\vec{a}=(x_1,y_1,z_1)$和$\vec{b}=(x_2,y_2,z_2)$。向量积即为$\vec{n}=\vec{a}\times\vec{b}=\begin{vmatrix} i & j & k \\ x_1 & y_1 & z_1 \\ x_2 & y_2 & z_2 \end{vmatrix}$。

换成普通初高中生能看懂的：$\vec{n}=(y_1z_2-y_2z_1,z_1x_2-z_2x_1,x_1y_2-x_2y_1)$。

这个东西的性质之一是可以作为法向量，不信可以带进去试试。三维计算几何经常用这个性质。另一个性质是模长等于$|\vec{a}||\vec{b}|\sin<\vec{a},\vec{b}>$，也就是这两个向量形成的平行四边形的面积，二维计算几何比较常用。数学考试做立体几何的时候，别人解方程求法向量，OIer、MOer和PhOer早就用这个口算出结果了。

```
#include<cstdio>
#define LL long long

int main()
{
    LL a,b,c,d,e,f;
    while(scanf("%lld%lld%lld%lld%lld%lld",&a,&b,&c,&d,&e,&f)!=EOF)
    	printf("%lld %lld %lld\n",b*f-c*e,c*d-a*f,a*e-b*d);
    return 0;
}
```

~~是不是只有我沙雕地交了好几发才发现是多组数据~~

---

## 作者：walk_alone (赞：6)

这题如果知道方法，压根就不需要什么解方程！  
（行列式大法好，虽然并不知道怎么推导的，只是知道，我是不会告诉你这是我们数学老师教给我们的）  
令 _**a**_ =($x1$,$y1$,$z1$),_**b**_=($x2$,$y2$,$z2$),求出来的法向量为 _**c**_=($x$,$y$,$z$)  
然后每个向量并排写两遍：  
	$x1$ $y1$ $z1$ $x1$ $y1$ $z1$  
	$x2$ $y2$ $z2$ $x2$ $y2$ $z2$  
然后掐头去尾，变成这样：  
	$y1$ $z1$ $x1$ $y1$    
	$y2$ $z2$ $x2$ $y2$  
然后交叉相乘,得到  
$x$=$y1z2-y2z1$  
$y$=$z1x2-z2x1$  
$z$=$x1y2-x2y1$  
当然每个式子取相反数也可以，但要换一起换（其实这玩意好像就是向量叉积的坐标表示，右手定则定的就是它的方向）  
知道这个了就是打印结果的事了，这不用给代码了吧  
最后再为求二面角总是求错的人给点小建议：  
用这个方法求的时候，以第一个向量为始边，然后看是顺时针还是逆时针转到另一个向量的，最后右手定则判一下方向。两个向量求完之后，同向为补角，反向为该角，来确定到底二面角的余弦值是正是负。

---

## 作者：communist (赞：4)

个人感觉我的解法比官方题解好理解得多

因为是任意一个法向量嘛，不妨设$x=1$

然后解一个二元一次方程就可以解决了

但是因为要求输出三个整数

考虑我们已知$x$取值的解方程过程

原式：

$$x1*x+y1*y+z1*z=0$$

$$x2*x+y2*y+z2*z=0$$

移项得：

$$y1*y+z1*z=-x1*x$$

$$y2*y+z2*z=-x2*x$$

给上半截左右两边同乘$\frac{y2}{y1}$得

$$y2*y+\frac{y2}{y1}*z1*z=-\frac{y2}{y1}*x1*x$$

两式相减得

$$(\frac{y2*z1}{y1}-z2)*z=(x2-\frac{x1*y2}{y1})*x$$

两边同乘$y1$

$$(y2*z1-z2*y1)*z=(x2*y1-x1*y2)*x$$

$$z=\frac{x*(x2*y1-x1*y2)}{y2*z1-z2*y1}$$

然后代入$y2*y+z2*z=-x2*x$

$$y=\frac{-z2*z-x2*x}{y2}$$

我们在给$x$赋初值的时候只要能让$y,z$的解都是整数即可

我就赋为了$(y2*z1-z2*y1)*y2$

然后好像就做完了，然后就爆零了

$$z=\frac{x*(x2*y1-x1*y2)}{y2*z1-z2*y1}$$

可能$y2*z1-z2*y1$会等$0$，所以不妨和$x$直接消掉

$$z=(x2*y1-x1*y2)*y2$$

$y$那个同理

代码
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#define int long long
using namespace std;
int x1,y1,z1,x2,y2,z2,x,y,z;
signed main()
{
    while(scanf("%lld%lld%lld%lld%lld%lld",&x1,&y1,&z1,&x2,&y2,&z2)==6)
    {
        x=(y2*z1-y1*z2)*y2;
        z=(y1*x2-x1*y2)*y2;
        y=-x2*(y2*z1-y1*z2)-z2*(y1*x2-x1*y2);
        int g=__gcd(x,__gcd(y,z));
        x/=g,y/=g,z/=g;
        //这两句gcd取最小值用的，因为怕解出来爆long long
        printf("%lld %lld %lld\n",x,y,z);
    }
    return 0;
}
```

---

## 作者：Ezis (赞：3)

### 解方程大法好！

我们将题中 $x*x_1+y*y_1+z*z_1 = 0$ 称为 ① 式，

将 $x*x_2+y*y_2+z*z_2 = 0$ 称为 ② 式。

再将 ① 式乘上 $x_2$，将 ② 式乘上 $x_1$，得：

$$ \left\{
\begin{aligned}
x*x_1*x_2+y*y_1*x_2+z*z_1*x_2 = 0 \\  x*x_2*x_1+y*y_2*x_1+z*z_2*x_1 = 0 \\
\end{aligned}
\right.
$$

将 ① 减去 ②，得：

$y*(y_1*x_2-x_1*y_2)+z*(z_1*x_2-z_2*x_1) = 0$

发现，$y=p(y_1*x_2-x_1*y_2)$ 且 $z=q(z_1*x_2-z_2*x_1)$ 时，等式成立。

其中，$p=1$ , $q=1$就是一组解。

于是，这题就做完了。

注意：要特判 $x1+x2=0$ 的情况。

CODE：
```cpp
#include<iostream>
#include<stdio.h>
#include<algorithm>
using namespace std;
#define int long long
int x1,x2,y1,y2,z1,z2;
signed main(){
	while(~scanf("%lld%lld%lld%lld%lld%lld",&x1,&y1,&z1,&x2,&y2,&z2)){
		if(x1+x2==0){
			int t1=y1+y2;
			int t2=z1+z2;
			int t3=__gcd(t1,t2);
			t1/=t3;
			t2/=t3;
			int x0,y0,z0;
			y0=t2;
			z0=-t1;
			x0=0;
			printf("%lld %lld %lld\n",x0,y0,z0);
			return 0;
		}
		int t1=x2*y1-x1*y2;
		int t2=x2*z1-x1*z2;
		int t3=__gcd(t1,t2);
		if(t3==0){
			printf("1 -1 0\n");
			continue;
		}
		t1=t1/t3;
		t2=t2/t3;		//将两式化简
		int x0=0,y0=t2,z0=-t1;
		while((-y0*y1-y0*y2-z0*z1-z0*z2)%(x1+x2)!=0)
			y0+=t2,z0-=t1;
		x0=(-y0*y1-y0*y2-z0*z1-z0*z2)/(x1+x2);	//求 x0
		printf("%lld %lld %lld\n",x0,y0,z0);
	}
	return 0;
}
```


---

## 作者：Catalan1906 (赞：2)

如果没有学过向量相关知识请出门右转高中数学必修四~~~

~~当然如果你和我一样也是小学生我也不反对~~

首先说结论：$\vec{z}=(y1z2-y2z1,z1x2-z2x1,x1y2-x2y1)$

其实这个东西高中老师应该会讲……如果没上过高中的~~（就像我）~~可以看一下[向量积](https://baike.baidu.com/item/%E5%90%91%E9%87%8F%E7%A7%AF/4601007?fr=aladdin#1_3)……证明也在里面……

code:
```
#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
    int x1, x2, y1, y2, z1, z2;
    while(cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2) cout << y1 * z2 - y2 * z1 << " " << z1 * x2 - z2 * x1 << " " << x1 * y2 - x2 * y1 << endl;
    return 0;
}
```

---

## 作者：Piggy343288 (赞：1)

实际上，这是两个向量的叉积已经是其他题解说烂了的。这里只是给出一个容易记忆 $dim\le 3$ 的行列式的值的办法。  

我们以 $3$ 维行列式为例子，假设为  

$$
\begin{vmatrix}
a & b & c\\
 i & j & k\\
 o & p & q
\end{vmatrix}
$$

我们有一个神奇的方法来记忆这个行列式的求值。  
首先从左上向右下打斜线，出格的部分从左向右重新打。相同颜色的斜线代表同一条斜线的话，应该是这样子的：  

$$
\begin{vmatrix}
 {\color{red} \backslash}  a &  {\color{green} \backslash}b & {\color{purple} \backslash}c\\
 {\color{purple} \backslash}i &  {\color{red} \backslash} j & {\color{green} \backslash}k\\
 {\color{green} \backslash}o & {\color{purple} \backslash}p &  {\color{red} \backslash} q
\end{vmatrix}
$$  

我们把斜线上的数相乘再相加，得到 $ajq+bko+cip$。  

同理，我们从右向左打斜线：  

$$
\begin{vmatrix}
 {\color{red} \backslash}  a &  {\color{green} \backslash}b & {\color{purple} \backslash}c\\
 {\color{green} \backslash}i &  {\color{purple} \backslash} j & {\color{red} \backslash}k\\
 {\color{purple} \backslash}o & {\color{red} \backslash}p &  {\color{green} \backslash} q
\end{vmatrix}
$$  

同样得到 $akp+bqi+coj$。把两个式子相减即可得到答案。  

二维行列式是完全类似的。只是可惜，这个规律在更高阶的行列式并不适用。

---

## 作者：Starlight237 (赞：1)

看到大部分题解没有详细讲解答案的推导，这里补充一下。

根据三维向量叉积的定义，$a\times b$是一个垂直于a和b所构成的平面，模长为a和b所张成平行四边形面积的向量。显然，这便是所求的一个法向量。

那么如何求这个叉积呢？

如果我们设
$$PX=\det(X,a,b)$$
其中左边表示点积，右边表示列向量分别为Xab的矩阵的行列式。

手动展开则有
$$p_1=a_2b_3-a_3b_2$$
$$p_2=a_3b_1-a_1b_3$$
$$p_3=a_1b_2-a_2b_1$$
这时我们让$X=(i,j,k)$，则$P=\det(E,a,b)$。根据行列式的几何意义，这是$E=(i,j,k),a,b$所张成的平行六面体体积。事实上，由于平行六面体体积=底面积*高的性质，这个行列式就是E与$a\times b$的点积，即E，a，b的混合积。可以看到，由于是E在ab平面垂直方向上的投影，P完美地满足了叉积的所有性质。

综上所述（换用题目中所给的字母）：
$$Ans=\begin{vmatrix}i&x_1&y_1\\j&x_2&y_2\\k&x_3&y_3\end{vmatrix}$$

因此有如下代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long X1,Y1,Z1,X2,Y2,Z2;
	while(~scanf("%lld%lld%lld%lld%lld%lld",&X1,&Y1,&Z1,&X2,&Y2,&Z2))
		printf("%lld %lld %lld\n",Y1*Z2-Z1*Y2,Z1*X2-X1*Z2,X1*Y2-Y1*X2);
	return 0;
}

```

---

## 作者：yppAAA (赞：1)

题解 P4894 【GodFly求解法向量】
 本蒟蒻最近刚品尝到立体几何 
 ~~看到这道题目不禁内心发痒2333~~
 老师上课讲的平面法向量求法是 “解一个二元一次方程”
 讲真数学和OI还是有很大区别的
 在这里可以为所欲为地使用“法向量快速求法”
~~好像牵扯什么大学知识还有什么右手定则~~
蒟蒻表示真的看不懂 上面的题解也很完善
所以就直接上代码了。。。
```
#include<iostream>
#include<cstdio>
using namespace std;
#define LL long long
int main(){
	LL a,b,c,x,y,z;
	while(cin>>a>>b>>c>>x>>y>>z)
	cout<<b*z-c*y<<" "<<x*c-a*z<<" "<<a*y-x*b<<endl;
	return 0;	                        
} 
```
因为是多组数据 后面一定要加上<<endl啊
第一次发题解发现自己好菜啊啊啊啊
还需要修炼啊......

---

