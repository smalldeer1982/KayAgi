# Gerald's Hexagon

## 题目描述

Gerald got a very curious hexagon for his birthday. The boy found out that all the angles of the hexagon are equal to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF559A/51081de61718bdab7ac2fc919b0406c7c9b3db07.png). Then he measured the length of its sides, and found that each of them is equal to an integer number of centimeters. There the properties of the hexagon ended and Gerald decided to draw on it.

He painted a few lines, parallel to the sides of the hexagon. The lines split the hexagon into regular triangles with sides of 1 centimeter. Now Gerald wonders how many triangles he has got. But there were so many of them that Gerald lost the track of his counting. Help the boy count the triangles.

## 说明/提示

This is what Gerald's hexagon looks like in the first sample:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF559A/4ab048b05b556943a01545b02118caaeb324465f.png)

And that's what it looks like in the second sample:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF559A/5870b6c24fc4fc3203a53b2587509290d8665c96.png)

## 样例 #1

### 输入

```
1 1 1 1 1 1
```

### 输出

```
6
```

## 样例 #2

### 输入

```
1 2 1 2 1 2
```

### 输出

```
13
```

# 题解

## 作者：Keroshi (赞：2)

# 题目分析  
不难想到可以把六边形的三个角补上，如下图：
![](https://cdn.luogu.com.cn/upload/image_hosting/8puf8teu.png)
而每个大三角形内的小三角形个数为 $\sum_{i=1}^{n}2n-1=n^2$。
# 代码  
```cpp
#include <bits/stdc++.h>
using namespace std;
int a1,a2,a3,a4,a5,a6;
int main(){
    scanf("%d%d%d%d%d%d",&a1,&a2,&a3,&a4,&a5,&a6);
    printf("%d",(a1+a2+a3)*(a1+a2+a3)-a1*a1-a3*a3-a5*a5);
    return 0;
}
```

---

## 作者：Colead (赞：1)

一道很好地结合了小学与初中知识的题。

个人觉得难度大约等同于普及组T1-T2 。

**先是初中部分的思路：**

大家应该都做过等角六边形给四条边求剩下两条的初中数学题，思路十分简单，补成正三角形然后利用三条边相等。

怎么补呢？在三条不相邻的边往外作3个正三角形。

那么这一题的基本思路就有了：补成一个大正三角形，然后减去三个小的。

于是我们就把这一题最大的难点：六边形形状不确定，转化成了求正三角形分割成单位小三角形个数的问题，简单多了。

下面：

**初中做法**：  求面积，大面积除以小面积

**小学做法**：  直接等差数列秒掉。

总之可以得到，边长为 $n$ 的正三角形，分割为单位小正三角形的个数为 $n^2$ .

所以代码就呼之欲出了：

```
#include<bits/stdc++.h>
using namespace std;
long long a,b,c,d,e,f;
long long sqr(long long x)//平方
{
	return x*x;
}
int main()
{
	cin>>a>>b>>c>>d>>e>>f;
	cout<<sqr(a+b+c)-sqr(a)-sqr(c)-sqr(e)<<endl;
	return 0;
}
```

（对，我承认它比今年普及第一题还短。

---

## 作者：KaguyaH (赞：1)

可以补成等边三角形。

于是可得（其中一种构造方案）：大等边三角形边长为 $a_1 + a_2 + a_3$，三个小等边三角形的边长分别为 $a_1, a_3, a_5$。

于是问题转化为如何求一个等边三角形划分成边长为 $1$ 的等边三角形的数量。

设 $S(a)$ 为边长为 $a$ 的等边三角形划分成边长为 $1$ 的等边三角形的数量，显然

$$
\begin{aligned}
&S(a)\cr
=& \sum_{i = 1}^a(a + (a - 1))\cr
=& \sum_{i = 1}^a(2a - 1)\cr
=& \frac{a((2 \times 1 - 1) + (2a - 1))}2\cr
=& \frac{2a^2}2\cr
=& a^2.\cr
\end{aligned}
$$

输出 $S(a_1 + a_2 + a_3) - S(a_1) - S(a_3) - S(a_5)$ 即可。

---

## 作者：REAL_曼巴 (赞：0)

感觉这道题有点恶评，其实橙题就顶天了。

可以证明，题目中给出的六边形，可以补成一个等边三角形。这个补指的是把三条不相邻的边延长相交。

我们可以把这个等边三角形轻松的分成小的三角形。

紧接着我们可以通过画图或者样例直接看出，假如这个等边三角形的边长为 $n$ 的话，那么他就可以分出 $n^2$ 个小的三角形。

我们不难发现，角补的部分也都是等边三角形。那么我们也可以用上面的结论推出个数。

这样题目就转化成了寻找每个大或小等变三角形的边长，之后大减小。

首先是小的三角形的边长，分别是 $a_1$ 和 $a_3$ 和 $a_5$，是不相邻的边。

其次是大三角形的边，是 $a_1+a_2+a_3$ 加起来。

好了，就可以按照上面的思路，平方之后大减小了。最后的式子见代码。

```
#include<bits/stdc++.h>
using namespace std;
int main(){
    int a,b,c,d,e,f;
	cin>>a>>b>>c>>d>>e>>f;
	cout<<(a+b+c)*(a+b+c)-a*a-c*c-e*e;
    return 0;
}
```


---

## 作者：ynxynx (赞：0)

小学数学题目

边长为$n$的正三角形,个数为$n*n$

证明:$1+3+...+(2*n-1)=(2*n-1+1)*n/2=n*n$

所以我们补三个三角形,用大减小就行了

代码:

```
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d,e,f;
int main(){
	cin>>a>>b>>c>>d>>e>>f;
	cout<<(a+b+c)*(a+b+c)-a*a-c*c-e*e;
}
```


### [记录](https://www.luogu.com.cn/record/65616069)

大佬不喜勿喷

---

## 作者：oimaster (赞：0)

因为其他题解讲的都是补成三角形的做法，然而我太菜了弄不懂，于是决定把六边形切开。

首先，我们看看六边形的 $120\degree$ 是怎么来的。我们知道等边三角形的一个角是 $60\degree$，那么显然这个六边形的每个角都是由两个等边三角形的角拼成的。由此可知，这个六边形看起来是正常的，**没有向内凹**。

接下来，让我们划分一下六边形的结构。我们把六边形分成三份。

![](https://cdn.luogu.com.cn/upload/image_hosting/u86nvaib.png)

我们很容易发现，这个奇怪的六边形分完后，我们从上到下对三部分进行编号，为 $1\sim3$，容易发现：

1. 在第一块中，每层如果上方有 $x$ 条边，那么这一层就有 $2x+1$ 个三角，同时下一层有 $x+1$ 条边。
2. 在第二块中，每层如果上方有 $x$ 条边，那么这一层就会有 $2x$ 个三角，同时下一层上方也有 $x$ 条边。
3. 在第三块中，每层上方有 $x+1$ 条边，那么下方就有 $x$ 条边，有 $2x+1$ 个三角。

那么我们枚举一下每一层的情况，累加起来不就好了？再看看数据范围，每条边小于 $1000$，那么说明**最多只有 $2\cdot1000$ 层**。

接下来，让我们看看具体怎么枚举。让我们对于每条边都做一个编号。

![](https://cdn.luogu.com.cn/upload/image_hosting/ql866iox.png)

假设第 $i$ 条边的长度为 $a_i$，下标从 $0$ 开始。

接下来，第一部分我们会发现一共有 $a_1$ 层，第一层上方的长度为 $a_0$。

然后，第二层一共有 $a_5-a_1$ 层，或者是 $a_4-a_2$ 层。任选一种求一下即可。顶部的长度就是按照第一部分的**继续保留**下来即可。

最后，第三层的层数是 $a_4$，顶部长度与第二层一样。

接下来你可能就要问了，这里是假设 $a_5>a_1$，那么如果 $a_5<a_1$ 怎么办呢？会减出来负数？如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/b7dcimb5.png)

这时候你会恍然大悟，原来无论如何翻转（水平、垂直），这个图案所包含的三角形个数是不变的。

那么我们只需要把 $a_1$ 和 $a_5$ 换一下，再把 $a_4$ 和 $a_2$ 换一下即可。

参考代码：

```cpp
#include<iostream>
using namespace std;
int main(){
	int a[6];
	for(int i=0;i<6;++i)
		cin>>a[i];
	if(a[1]>a[5]){
		swap(a[1],a[5]);
		swap(a[2],a[4]);
	}
	int last=a[0];
	int sum=0;
	for(int i=0;i<a[1];++i){
		sum+=last*2+1;
		++last;
	}
	// cout<<sum<<' '<<last<<endl;
	for(int i=a[1];i<a[5];++i)
		sum+=last*2;
	// cout<<sum<<' '<<last<<endl;
	--last;
	for(int i=0;i<a[4];++i){
		sum+=last*2+1;
		--last;
	}
	// cout<<sum<<' '<<last<<endl;
	cout<<sum<<endl;
}
```

---

