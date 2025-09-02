# Vectors

## 题目描述

At a geometry lesson Gerald was given a task: to get vector $ B $ out of vector $ A $ . Besides, the teacher permitted him to perform the following operations with vector $ А $ :

- Turn the vector by $ 90 $ degrees clockwise.
- Add to the vector a certain vector $ C $ .

Operations could be performed in any order any number of times.

Can Gerald cope with the task?

## 样例 #1

### 输入

```
0 0
1 1
0 1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
0 0
1 1
1 1
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
0 0
1 1
2 2
```

### 输出

```
NO
```

# 题解

## 作者：Remake_ (赞：7)

~~没学过数学，爪巴了~~

我们幼儿园学过的向量旋转公式的形式为：

$x'=x\cos\vartheta+y\sin\vartheta,y'=y\cos\vartheta-x\sin\vartheta$

而在此题中，$\vartheta=90\degree$，故：

$x'=y,y'=-x$

所以:

当点不旋转时：向量等于$(x,y)$

当点旋转$90\degree$时：向量等于$(y,-x)$

当点旋转$180\degree$时：向量等于$(-x,-y)$

当点旋转$270\degree$时：向量等于$(-y,x)$

然后当点再次旋转时实际上就变成了不旋转的情况，以此类推，可以说旋转的角度呈一个长度为$4$的周期，旋转$x\degree$实质上等于旋转$x\degree\pmod{360\degree}$。

那么我们接下来设$4$个非负整数$k_1,k_2,k_3,k_4$表示$A$分别在不旋转时，旋转$90\degree$时，旋转$180\degree$时，旋转$270\degree$时加了多少次$C$，则可列出一个向量方程，即：

$(k_1C_x,k_1C_y)+(k_2C_y,-k_2C_x)+(-k_3C_x,-k_3C_y)+(-k_4C_y,k_4C_x)=(B_x-A_x,B_y-A_y)$

接下来可以把它转化成一个方程组的形式，即：

$$ \left\{
\begin{aligned}
 (k_1-k_3)C_x+(k_2-k_4)C_y=B_x-A_x\\
(k_1-k_3)C_y-(k_2-k_4)C_x=B_y-A_y
\end{aligned}
\right.
$$

那么我们考虑用整数（注意可以是负数）$a,b$来分别替换$(k_1-k_3),(k_2-k_4)$，得到了我们喜闻乐见的形式——一个二元一次方程组：

$$ \left\{
\begin{aligned}
 C_xa+C_yb=B_x-A_x\\
 C_ya-C_xb=B_y-A_y
\end{aligned}
\right.
$$

所以我们的问题就变成了这个东西有没有整数解了。

由$1$式得$a=\frac{B_x-A_x}{C_x}-\frac{C_y}{C_x}b$

将$\,a=\frac{B_x-A_x}{C_x}-\frac{C_y}{C_x}b\,$代入$2$式，得$b=\frac{B_y-A_y-\frac{C_y}{C_x}B_x+\frac{C_y}{C_x}A_x}{-(\frac{
C_y^2+C_x^2}{C_x})}$

好像非最简，化简一下得：$b=\frac{C_x(B_y-A_y)-C_y(B_x-A_x)}{-(C_y^2+C_x^2)}$

判一下$b$和$a$是不是整数即可，注意要特判分母为$0$的情况。

Tips：需要注意的一点是初始时$A$有可能已经旋转过了，所以$A$初始的时候实际上有四种情况（不旋转，旋转$90\degree$，旋转$180\degree$，旋转$270\degree$），贼™坑。

上一下代码吧QAQ：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long ax, ay, bx, by, cx, cy;
void check(long long axx, long long ayy)
{
    if (cx * cx + cy * cy == 0)
    {
        if (axx == bx && ayy == by)
        {
            cout << "YES";
            exit(0);
        }
        else
            return;
    }
    if ((cx * (by - ayy) - cy * (bx - axx)) % (cx * cx + cy * cy) != 0 || (cx * (bx - axx) + cy * (by - ayy)) % (cx * cx + cy * cy) != 0)
        return;
    cout << "YES";
    exit(0);
}
int main()
{
    cin >> ax >> ay >> bx >> by >> cx >> cy;
    check(ax, ay);
    check(ay, -ax);
    check(-ax, -ay);
    check(-ay, ax);
    cout << "NO";
}
```


---

## 作者：ncwzdlsd (赞：1)

向量水题，高一下期中考试数学大寄之后做很应景……

考虑 $\vec a=(x,y)$ 向量旋转之后只有这几种情况：$(x,y),(-y,x),(-x,-y),(y,-x)$，所以只需要每一种情况验一遍即可。

把 $\vec a$ 的变换与 $\vec c$ 的累加联系起来，通过整理向量关系，我们可以得到和如下相似的二元一次方程组：

$$
\begin{cases}
x_c p+y_c q=x_b-x_a\\
y_c p-x_c q=y_b-y_a
\end{cases}
$$

于是乎我们只需要 `check` 这个方程是否有整数解即可，注意特判 $0$ 的情况。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define x1 x11
#define x2 x22
#define y1 y11
#define y2 y22

int a,b,x1,y1,x2,y2;

bool check(int x,int y)
{
	x-=x2,y-=y2;
	int tmp=a*a+b*b;
	if(!tmp) return x==0&&y==0;
	return (a*x+b*y)%tmp==0&&(a*y-b*x)%tmp==0;
}

signed main()
{
	cin>>x1>>y1>>x2>>y2>>a>>b;
	bool flag=0;
	if(check(x1,y1)||check(-x1,-y1)||check(y1,-x1)||check(-y1,x1)) flag=1;
	printf("%s",flag?"YES":"NO");
	return 0;
}
```

---

## 作者：XL4453 (赞：0)


前置知识：向量加法， $90^\circ$ 意义下的向量旋转。

------------

题目分析：

显然是数学题。

首先发现，题目中的旋转不太好办，考虑将其转化为两个操作：旋转原来的向量 $\vec{a}$，使其在一开始可以以任意旋转后的形式出现；加上一个旋转后的 $\vec{c}$，使其可以以四种不同的形式存在。

这样转化后，将最后的向量 $\vec{b}$ 分四种情况减去旋转后的向量 $\vec{a}$ ，然后用旋转后的向量 $\vec{c}$ 来表示。这时可以发现，其实在运算中向量 $\vec{c}$ 只有两种表示形式，原向量 $\vec{c}$ 和旋转 $90^\circ$ 后的向量 $\vec{c}$ 。

然后就以向量 $\vec{c}$ 和旋转 $90^\circ$ 后的向量 $\vec{c}$ 为一组基底（显然有两向量不共线）来表示向量 $\vec{b}-\vec{a}$，若表示后的两组系数为整数，则一定可以表示，否则不行。

------------

更具体的：


设： $\vec{b}=(x_1,y_1)$，$\vec{b}-\vec{a}=(x_2,y_2)$。

则：$\vec{b'}=(-y_1,x_1)$。

欲求：$\vec{b}-\vec{a}=n\cdot\vec{b}+ m\cdot\vec{b'}$

用坐标表示为：$(x_2,y_2)=n\cdot(x_1,y_1)+ m\cdot(-y_1,x_1)$

解得：$\begin{cases}a=\dfrac{y_1y_2+x_1x_2}{x_1^2+y1^2_1}\\b=\dfrac{y_1y_2-x_1x_2}{x_1^2+y1^2_1}\end{cases}$

然后判断一下两者是否为整数即可。



------------
其中，还有一种特殊情况：向量 $\vec{c}$ 为零向量。
这种情况下只能让向量 $\vec{a}$ 旋转，看是否能和 $\vec{b}$ 重合


------------
代码：
```cpp
#include<cstdio>
using namespace std;
int abs(int a){if(a<0)return -a;return a;}
bool ans;
long long x1,x2,x3,y1,y2,y3;
void calc(long long x1,long long y1,long long x2,long long y2){
	if((x1*x2+y1*y2)%(x1*x1+y1*y1)==0&&(-x2*y1+x1*y2)%(y1*y1+x1*x1)==0)
	ans=1;
}
void check(long long axx,long long ayy){
	if (axx == x3 && ayy == y3)ans=1;
}
int main(){	
	scanf("%I64d%I64d%I64d%I64d%I64d%I64d",&x1,&y1,&x3,&y3,&x2,&y2);
	if(x2==0&&y2==0){
		check(x1, y1);
		check(y1, -x1);
 		check(-x1, -y1);
		check(-y1, x1);
		if(ans)printf("YES\n");
		else printf("NO\n");
  		return 0;
	}
	calc(x2,y2,x3-x1,y3-y1);
	calc(x2,y2,x3+x1,y3+y1);
	calc(x2,y2,x3+y1,y3-x1);
	calc(x2,y2,x3-y1,y3+x1);
	if(ans)printf("YES\n");
	else printf("NO\n");
	return 0;
}
```









---

