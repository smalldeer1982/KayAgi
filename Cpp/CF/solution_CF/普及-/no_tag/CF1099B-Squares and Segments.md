# Squares and Segments

## 题目描述

小索菲亚在四年级。今天，在几何课上，她学到了有关线段和正方形的知识。在回家的路上，她决定在雪中画n个边长为1的正方形。为了简单起见，我们假设Sofia生活在一个平面上，并且只能绘制与坐标轴平行、顶点位于整数点的长度为1的线段。

为了绘制一个段，Sofia进行如下操作。如果她想画一个端点为（x，y）和（x，y+1）垂直段。Sofia会查看是否已经有一个绘制的段，其端点为（x'，y）和（x'，y+1）。如果存在这样的段，那么Sofia将使用旧段作为指导，快速绘制新段。如果没有这样的线段，那么索菲亚就必须用尺子长时间测量一个新的线段。当索菲亚想画一个水平段时，也会发生同样的事情，但现在她才检查是否存在具有相同x，x+1坐标和不同y坐标的段。

例如，如果索菲亚需要画一个1 * 1的正方形，她必须用尺子画两段。

如果索菲亚需要画两个正方形，她必须用尺子画三段。
之后，她可以使用前三个部分作为向导绘制其余四个线段。

索菲亚很着急，所以她想尽量减少用尺子在没有向导的情况下绘制的线段数量。帮她找到这个最小数量。

## 样例 #1

### 输入

```
1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2
```

### 输出

```
3
```

## 样例 #3

### 输入

```
4
```

### 输出

```
4
```

# 题解

## 作者：UKE_Automation (赞：3)

[原题链接](https://www.luogu.com.cn/problem/CF1099B)

观察此题，发现此题就是让我们求出在某种特殊画法下，画出 $n$ 个正方形至少需要画多少次。

而这种特殊画法就是，如果你有一条长为 $1$ 的线 $l$，就可以画出以 $l$ 的一个顶点，绕着该顶点旋转 $90\degree$ 得到的一条长为 $1$ 线（可以顺时针或逆时针）。所以此题就是求至少画出多少条上面的 $l$，才能通过上面的画法，画出 $n$ 个正方形。 


现在，我们可以举一些例子进行讨论。

1. 图片如下

![](https://cdn.luogu.com.cn/upload/image_hosting/zod6vlsr.png)

观察一下，你发现了什么？

是的！当 $n$ 为完全平方数时，画出的成品就是一个边长为 $\sqrt{n}$ 的大正方形！

而我们要画的，就是这个正方形周长的一半，即 $\sqrt{n} \times 2$ 条线。

2. 图片如下

![](https://cdn.luogu.com.cn/upload/image_hosting/ks0a0k93.png)

在此处，画出的成品就是一个 $\left\lfloor\sqrt{n}\right\rfloor \times (\left\lfloor\sqrt{n}\right\rfloor+1)$ 的大正方形，并且我们要画的就只有 $\left\lfloor\sqrt{n}\right\rfloor+\left\lfloor\sqrt{n}\right\rfloor+1$ 条线。并且，当这个长方形有一点缺口（例如 $n=5$ 时），仍然可以用上面的绘制法绘制。

而这种情况必须在 $\left\lfloor\sqrt{n}\right\rfloor \times (\left\lfloor\sqrt{n}\right\rfloor+1)\geq n$ 时才能使用。

3. 图片如下

![](https://cdn.luogu.com.cn/upload/image_hosting/p5x6qdnp.png)

我们会发现，当 $n=3$ 时，上述的两种方法都不能用了，这时就要放出我们的大招，补齐。

观察可知，只要我们把右下角的那个正方形补齐，就能画出与第一种情况相同的大正方形，而题目只要求我们输出最少的红线段，因此补齐后是没有其他的情况的。

而此时，我们画出的成品就是边长为 $\left\lfloor\sqrt{n}\right\rfloor+1$ 的正方形，而我们要画的只有 $\left(\left\lfloor\sqrt{n}\right\rfloor+1\right)\times 2$ 条线。

------------
现在，所有的情况都分析完了，该怎样写代码呢？

我们发现，在分析中多次出现了 $\left\lfloor\sqrt{n}\right\rfloor$ 这个元素，所以考虑用一个变量去存，而向下取整操作，可以直接用整形变量完成，因为给整形赋浮点数时会自动向下取整。

好了最后就到了亮代码的时候了 ~~（终于！！）~~
```cpp
#include<cstdio>
#include<cmath>
using namespace std;
int n,m;
int main()
{
	scanf("%d",&n);
	m=sqrt(n);//n的平方根（向下取整） 
	if(m*m==n)//如果n是完全平方数
		printf("%d",m*2);//情况1
	else if(m*(m+1)>=n)//如果m*(m+1)大于等于n
		printf("%d",m+m+1);//情况2
	else//剩余的即是要进行补齐
		printf("%d",(m+1)*2);//情况3 
	return 0;
}
```

---

## 作者：lichenfan (赞：2)

### 思路
由基本不等式可知，要尽量品尝正方形。这与小学时求四边形周长最小的概念相同，即将两个边长分为尽可能相近的数值。比如拼成一个正方形，或者拼成边长差 $1$ 的长方形。用平方根就可以求出了。
## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int main(){
	cin>>n;
	m=sqrt(n);
	if(m*m==n){
		cout<<2*m;                 //如果n为完全平方数，那么直接造正方形 
		return 0;
	}
	if(m*(m+1)>=n){
		cout<<2*m+1;         //宽为m,长为m+1 
		return 0;
	} 
	cout<<2*m+2;            //如果两个都不行，那就拼出一个m+1的大正方形 
}

```


---

## 作者：览遍千秋 (赞：2)

本题解同步发布于[本场$\mathrm{CF}$总题解](https://www.luogu.org/blog/kaiming/CF530Div2)，欢迎来踩。

## B - Squares and Segments

显然，为了保证需要尺子画的线更少，应该尽可能把这$n$个正方形排列成一个大正方形的样子。

所以设$m= \lfloor \sqrt{n} \rfloor$，对$m$和$n$的关系进行分类讨论即可：

- $m^2=n$
    
也就是说$n$是一个完全平方数，此时答案显然为$2 \times m$

- $m \times (m+1) < n$

矩形两条边相差超过$1$，答案为$2 \times m+2$

- 其余

答案为$2 \times m + 1$

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int mian(){
    scanf("%d",&n);
    m=sqrt(n);
    if(n/m==m&&n%m==0){
    	printf("%d\n",2*m);
    	return 0;
    }
    printf("%d\n",2*m+1+(m*(m+1)<n));
    return 0;
}
```

---

## 作者：da32s1da (赞：2)

很明显，要尽量拼正方形才可以。

由不等式$a+b \ge 2\sqrt{ab}\ $得出本题答案

嗯。。。

$\sqrt{ab}\ $若不为整数呢？

考虑到$\lfloor \sqrt{ab}\rfloor^2\le ab \le \lceil \sqrt{ab}\rceil^2$，于是只要比较$ab$与$\lfloor \sqrt{ab}\rfloor\times \lceil \sqrt{ab}\rceil$的大小就好了。

```
#include<cstdio>
#include<cmath>
#include<iostream>
using namespace std;
int n,m;
int main(){
	scanf("%d",&n);
	m=sqrt(n);
	if(m*m==n)printf("%d\n",2*m);//\sqrt{ab}为整数
	else if(m*(m+1)>=n)printf("%d\n",2*m+1);//比较ab与...的大小
	else printf("%d\n",2*m+2);
}
```

---

## 作者：qwq___qaq (赞：1)

### 题意
给出一个 $n$，找出 $(a,b)$，使 $ab\ge n$ 且 $a+b$ 最小。
### 思路
不妨设 $a\le b$，则 $a\le\dfrac{n}{b}$，即 $a\le\sqrt{n}$。

也就是说，我们在 $\sqrt{n}$ 的范围内枚举 $a$，那么 $b$ 就是 $\lceil\dfrac{n}{a}\rceil$。

时间复杂度 $O(\sqrt{n})$。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans=INT_MAX;
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n/i;++i)
		ans=min(ans,(n+i-1)/i+i);
	printf("%d\n",ans);
	return 0;
}
```
另外一种思路：

由均值不等式（$a+b\ge2\sqrt{ab}$）易得 $a+b\ge2\sqrt{ab}\ge2\lceil\sqrt{n}\rceil$，所以答案为 $2\lceil\sqrt{n}\rceil$。

时间复杂度 $O(1)$。

---

## 作者：zk_y (赞：0)

这道题目让我们先来看看，题目让我们求出的是尺子在没有向导的情况下绘制的线段数量的最小值。

我们看这张图片：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1099B/c9c6f752f1413cb3b2cb7f9d9bfc51906386e984.png)

这张图标红的地方就是我们要求解的部分，所以我们很容易的就能看出来标红的地方应当是**长方形的一条长和宽**。

我们要绘制出 $n$ 个长方形。所以，我们就要使 这 $n$ 个正方形所组成的图形所在的长方形内的长和宽最小，这有点像我们小学学过的周长最短问题，那么当时，我们是怎么解决的呢 ？

我们是考虑了正方形的情况，并得出了这么一个结论：

> 在周长一定的情况下，越接近于正方形的图形的周长越小。

那这道题目也是这样。

那我们就可以按照这样一个规律来了。

如果这个 $n$ 是平方数，代表可以组成正方形，直接输出正方形的边长乘2也就是 $\sqrt n \times 2$ 就可以了。

如果 $n$ 不是平方数，但我们又要想总花费少，所以选用 $\sqrt n +(\sqrt n+1)$ 长为 $\sqrt n+1$ 宽为 $\sqrt n$ 。

如果还是不行，我们只能输出 $\sqrt n+1+\sqrt n+1$ 也就是长和宽的和，因为 $\sqrt n +(\sqrt n+1)$ 都无法满足，就只能加 $1$ 了。

代码如下：

```
#include<bits/stdc++.h>//头文件
using namespace std;
int q,n,ans;
int main(){
	scanf("%d",&n);
	q=sqrt(n);
	if(n==q*q)printf("%d",q+q);//是平方数
	else if(q*(q+1)>=n)printf("%d",q+q+1);
	else printf("%d",q+1+q+1); 
	return 0;
} 
```


---

## 作者：Terry2011 (赞：0)

# 题目分析

- 这道题目要求找到绘制的线段数量的最小数量。显然，只有长和宽无线接近才能实现。想到了什么？小学的给定面积画长方形求最小周长。
- 这样，这道题目就简单了！我们可以先向下取整获取 $\sqrt{n}$，然后进行判断这个图形是否是正方形。如果是，输出 $2\times\sqrt{n}$。否则继续判断。
- 如果长比宽长 $1$，输出 $2\times(\sqrt{n}+1)$。否则输出$2\times(\sqrt{n}+2)$。

# Code
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int main(){
	int n;//声明变量
	cin>>n;//输入
	int a=sqrt(n);//定义sqrt(n)
	if(a*a==n){//判断正方形
		cout<<2*a;
	}
	else if(a*(a+1)>=n){//长比宽长1
		cout<<2*a+1;
	}
	else{
	    cout<<2*a+2;
	}
	return 0;
}
```

---

## 作者：zwye (赞：0)

### 分析
找最接近当前数的一个数的两个因数，比如 $41$，就是 $6\times7$，就是 $6+7$ 的结果。如果按照 $41$ 来算，那么需要 $41+1=42$，如果是按照 $42$ 来算，就是 $6+7$，还有 $10$，最接近的是 $3+4$，是 $12$ 的。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    int p=sqrt(n);
    int ans=10000000,flag=0;
    if(n==1)
	{
        ans=2;
        cout<<ans<<endl;
        return 0;
    }
    if(p*p==n)ans=min(2*p,ans);
    else if(p*(p+1)>=n) ans=min(p+p+1,ans);
    else ans=min(2*(p+1),ans);
    cout<<ans<<endl;
}
```


---

## 作者：scpchangyi (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1099B)

### Solution

由于不等式 $2\sqrt{ab} \leq a+b$，可以看出必须尽量是正方形。上过小学的都知道四边形周长最小的概念，只需让边长相差尽可能小。需要用到平方根。

列举情况：

- 判断 $n$ 为完全平方数，直接造正方形。

- 其他情况，拼一个 $m+1$ 的正方形。


------------

### Code

求平方根：```sqrt(n)```。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#define int long long
using namespace std;
int n,m;
signed main()
{
	scanf("%lld%lld",&n,&m);
	m=sqrt(n);//求平方根 
	if(n==m*m){printf("%lld",m*2);return 0;}
	if(n<=(m+1)*m){printf("%lld",m*2+1);return 0;} 
	/*判断n为完全平方数，直接造正方形*/
	printf("%lld",m*2+2);
	/*其他情况，拼一个边长m+1的正方形*/
	return 0;//好习惯 
}
```

---

## 作者：cxy000 (赞：0)

首先让我们分析一下题目：

这道题实际上和给定面积画长方形求最小周长有些相似。

所以我们先定义另一个变量 $a=sqrt(n)$，然后再判断是否为正方形，如果是，直接输出 $2×m$ 即可。

然后如果一个 $a$ 和 $a+1$（$a$ 向下取整）不能画，就输出 $a+1+a+1$ 即可。（一定可以画的，因为 $a^2 \leq n \leq (a+1)^2$ ）。

## Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;
	int mm=sqrt(n);
	if(mm*mm==n){
		cout<<2*mm;
	}
	else if(mm*(mm+1)>=n){
		cout<<2*mm+1;
	}
	else cout<<2*mm+2;
	return 0;
}
```


---

## 作者：ttq012 (赞：0)

**Solution**

由于在面积相等的时候，两条边的长度的差值越小，两条边的长度的和越小，又有 $\lfloor \sqrt{n}\rfloor ^2 \le n\le \lceil \sqrt{n}\rceil ^2$，所以我们先判断是否可以用两个 $\lfloor \sqrt{n}\rfloor$ 的线段来画 $n$ 个正方形，如果不能就用一个 $\lfloor \sqrt{n}\rfloor$ 和一个 $\lfloor \sqrt{n}\rfloor + 1$ 来画，如果还是不能就用两个 $\lfloor \sqrt{n}\rfloor + 1$。由于有上面的第二条定理，所以两个 $\lfloor \sqrt{n}\rfloor + 1$ 一定能画出 $n$ 个正方形。

**Code**

```cpp
#include <bits/stdc++.h>

using namespace std;

signed main () {
    int n;
    cin >> n;
    int k = sqrt(n);
    if (k * k >= n)
        printf ("%d\n", k + k);
    else if (k * (k + 1) >= n)
        printf ("%d\n", k + k + 1);
    else
        printf ("%d\n", k + 1 + k + 1);
    return 0;
}

```

---

## 作者：DPseud (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1099B)

相信很多人看题解都是看不懂抽象的翻译，其实题意很简单：给出一个由 $n$ 个正方形组成的图形，求它最左边那条线段的长度加上最上边那条线段的长度。

看到这里，我们其实就能看出，组成的图形要么是长方形（说句闲话：无论横着来还是竖着来都是一样的），要么是正方形，要么是下图这种图形：

![](https://cdn.luogu.com.cn/upload/image_hosting/21x4ni73.png)

于是这道题便可以分成三种情况解决了：

1. $n$ 是完全平方数时，答案为 $2\sqrt{n}$。

2. $\sqrt{n}\times\sqrt{n+1}\ge n$ 且 $n$ 不是完全平方数时，答案为 $2\sqrt{n}+1$。

3. 如果两种情况都不是，答案为 $2\sqrt{n}+2$。

最后我们就可以优雅地将代码打出了（貌似最短代码？）：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	cout<<((int(sqrt(n))*int(sqrt(n))==n)?(int(sqrt(n))*2):(int(sqrt(n))*2+1+(int(sqrt(n))*(int(sqrt(n))+1)<n)));
	return 0;
}
```

完结撒花！

---

## 作者：wbs200 (赞：0)

实际上，此题的题意为：画 $n$ 个正方形，每一条边都是一个小木棍，但如果是同一行的所有竖边或同一列的所有横边只算画一次。求如果想要画 $n$ 个正方形的话需要画多少次。

那么这个题显然是个思维题和枚举题。我们可以转化一下，看一下我们所画的所有正方形的边长是多少。设行数为 $a$，列数为 $b$，那么我们可以发现：同一行竖边需要画的一共有 $a$ 组，需要画 $a$ 次；同一列的横边一共有 $b$ 组，需要画 $b$ 次。所以我们可以发现，如果我们最终画出的这个矩阵是 $a \times b$，那么我们就需要画 $a+b$ 次。我们一共想要画 $n$ 个矩阵，所以我们前提要求 $a \times b \geq n$。所以这个题就转化为了在保证 $a \times b \geq n$ 的前提下求 $a+b$ 的最小值。

这样的话我们可以使用均值不等式来解决。这里介绍另一种使用枚举的方法。我们对 $a$ 进行枚举，则 $b$ 的最小值为 $\lceil \frac{n}{a} \rceil$。这样就解决了这道题目。

```cpp
#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int ans = n + 1;
    for (int a = 1; a <= (n + a - 1) / a; a++) ans = min(ans, a + (n + a - 1) / a);
    cout << ans << endl;
    return 0;
}
```

---

