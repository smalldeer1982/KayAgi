# Photo of The Sky

## 题目描述

Pavel made a photo of his favourite stars in the sky. His camera takes a photo of all points of the sky that belong to some rectangle with sides parallel to the coordinate axes.

Strictly speaking, it makes a photo of all points with coordinates $ (x, y) $ , such that $ x_1 \leq x \leq x_2 $ and $ y_1 \leq y \leq y_2 $ , where $ (x_1, y_1) $ and $ (x_2, y_2) $ are coordinates of the left bottom and the right top corners of the rectangle being photographed. The area of this rectangle can be zero.

After taking the photo, Pavel wrote down coordinates of $ n $ of his favourite stars which appeared in the photo. These points are not necessarily distinct, there can be multiple stars in the same point of the sky.

Pavel has lost his camera recently and wants to buy a similar one. Specifically, he wants to know the dimensions of the photo he took earlier. Unfortunately, the photo is also lost. His notes are also of not much help; numbers are written in random order all over his notepad, so it's impossible to tell which numbers specify coordinates of which points.

Pavel asked you to help him to determine what are the possible dimensions of the photo according to his notes. As there are multiple possible answers, find the dimensions with the minimal possible area of the rectangle.

## 说明/提示

In the first sample stars in Pavel's records can be $ (1, 3) $ , $ (1, 3) $ , $ (2, 3) $ , $ (2, 4) $ . In this case, the minimal area of the rectangle, which contains all these points is $ 1 $ (rectangle with corners at $ (1, 3) $ and $ (2, 4) $ ).

## 样例 #1

### 输入

```
4
4 1 3 2 3 2 1 3
```

### 输出

```
1```

## 样例 #2

### 输入

```
3
5 8 5 5 7 5
```

### 输出

```
0```

# 题解

## 作者：MorsLin (赞：8)

作为一个蒟蒻，$\tt{CF}$止步$Div.2\;C$

这个题主要考察思维，正解代码炒鸡短……

以下大部分搬运自[官方题解](http://codeforces.com/blog/entry/60920)

---

#### 题目大意：
给你一个长度为$2n$的数组，将这个数组分为两个可重集，每个集合有$n$个元素，使得这两个集合的极差之积最小，输出这个最小值

#### 题解：
假设输入的数组为$a[2n]$，为了方便，我们把要分成的两个可重集叫做$X$和$Y$

首先肯定要$sort$一下，使得数组有序，方便操作（下文提到的数组都是有序的）

接下来就是分类讨论了：

- 第一种情况：数组a的最大值和最小值都在$X$里。那么$X$的极差就是$a[2n]-a[1]$，接下来我们要使$Y$的极差尽量小，我们就需要枚举一下每个元素$a[i]$，因为集合里要有$n$个元素，所以对于每个$a[i]$，能使$Y$的极差最小的方式就是将$a[i]$~$a[i+n-1]$全部放到$Y$里，所以$Y$的极差就是$\min(a[i+n-1]-a[i])\;i\in [2,n+1]$

 答案为 $\min((a[i+n-1]-a[i])\cdot(a[2n]-a[1]))\;i\in [2,n+1]$


- 第二种情况：最小值（$a[1]$）和最大值（$a[2n]$）分别在$X$和$Y$里。这样我们就要使$X$的最大值尽量小，$Y$的最小值尽量大，那么$X$的极差最小就为$a[n]-a[1]$，$Y$的极差最小为$a[2n]-a[n+1]$

 答案为 $(a[n]-a[1])\cdot (a[2n]-a[n+1])$

最终的答案从这两种情况中取一个最小值就好了。

时间复杂度$O(nlogn)$（也就是排序的复杂度）

最后提醒一句：**别忘了开$\mathfrak{long\;long}$**

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
int read(){
	int k=0; char c=getchar();
	for(;c<'0'||c>'9';) c=getchar();
	for(;c>='0'&&c<='9';c=getchar())
	  k=(k<<3)+(k<<1)+c-48;
	return k;
}
ll a[100010<<1],ans;
int main(){
	int n=read();
	for(int i=1;i<=n<<1;i++) a[i]=read();
	sort(a+1,a+(n<<1)+1);
	ans=(a[n]-a[1])*(a[n<<1]-a[n+1]); //第二种情况
	for(int i=2;i<=n+1;i++)  //第一种情况
		ans=min((a[n<<1]-a[1])*(a[i+n-1]-a[i]),ans);
	cout<<ans;
	return 0;
}
```

---

## 作者：Register (赞：3)

### 随便找了道CF的A题，结果是蓝色的，坑的一逼
这道题若是想不出来方法那是比黑题还难（洛谷黑

emm...不扯了，分析一下题意：

有$n$个点，拿最小的平行$xy$轴的矩形圈住，大概是这个样子的：
![](https://cdn.luogu.com.cn/upload/pic/46999.png)

那么面积就是$x$的$max-min$乘以$y$的$max-min$

给你一堆打乱的任意$x$和$y$，怎样使得乘积最小？

小学的时候学过最值原理，那个什么“和定差小积大”

那么乘积最小就要差大，即$(maxa_i-mina_i)*min(a_i-a_i)$

那么先$sort$一下就可以找到前面的部分，而$sort$能保证严格的升序，选一段连续的区间，进行枚举，就能选出后半部分

别忘了还有一种情况区间分别是$1,n$和$n+1,2n$

code:
```cpp
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
int n;
ll a[200001],ans;
int main(){
    cin>>n;
    for(int i=1;i<=(n<<1);i++) cin>>a[i];
    sort(a+1,a+(n<<1)+1);
    ans=(a[n]-a[1])*(a[n<<1]-a[n+1]);
    for(int i=1;i<n;i++) ans=min((a[n<<1]-a[1])*(a[n+i]-a[i+1]),ans);
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：yanwh1 (赞：2)

# 题目大意：
给你 $2n$ 个数，让你用这些数组成 $n$ 个点，使得一个能覆盖 $n$ 个点且平行于坐标轴的矩形面积最小。
# 思路详解：
很显然的贪心。我们只要使得这些数组成的点最大横坐标减最小横坐标的差乘上最大纵坐标减最小纵坐标的差最小即可。我们设输入的数组为 $s[2n]$，答案为 $ans$，先将 $s$ 排一下序，于是便有了以下两种情况：

- $ans=(s[n+i-1]-s[i])\times(s[n]-s[1])$。因为我们要使 $ans$ 最小，所以连续的肯定是更优的。
- $ans=(s[n]-s[1])\times(s[2 \times n]-s[n+1])$。因为这种情况不同于上面，所以特判一下。

最后将两种情况取最小值即可。
# 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rint register int
#define int long long
inline int read(){
	int x=0,y=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-'){y=-1;}c=getchar();}
	while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
	return x*y;
}inline void write(int s){
	if(s<0)s=-s,putchar('-');
	if(s>9)write(s/10);
	putchar(s%10+'0');
}const int N=2e5+5;
int s[N];
signed main(){
	int n=read();
	for(rint i=1;i<=2*n;i++)s[i]=read();
	sort(s+1,s+2*n+1);
	int ans=(s[n]-s[1])*(s[2*n]-s[n+1]);
	for(rint i=2;i<=n;i++)
		ans=min(ans,(s[2*n]-s[1])*(s[n+i-1]-s[i]));
	write(ans);
	return 0;
}
```

---

## 作者：娄口肃行 (赞：2)

- ## 题意:给定2\*n个数字和数字n,求这些数字能构成n个点(x,y坐标在这2\*n个数字内,求一个面积最小的矩形,使矩形能完全包含所有的n个点(点的x,y坐标自定,不能重复)

----

- ## 水水的一发模拟...方法:排序(从小到大),枚举长度为n的区间,这段区间作为x坐标的范围,然后将这段区间的极差值与剩下部分的极差值相乘取最大值,即为答案

----
 - **代码如下**


- ```
#include<bits/stdc++.h>
using namespace std;
long long a[1000010],n,l;
int main()
{
    cin>>n;
    n*=2;
    for (int i=1;i<=n;i++) in>>a[i];
    sort(a+1,a+n+1);
    long long x=a[n/2]-a[1],y=a[n]-a[n/2+1];
    l=1;
    long long an=x*y;
    for (int i=2;i<=n/2+1;i++)
    {
        an=min(an,(a[i+n/2-1]-a[i])*(a[n]-a[1]));
    }
    cout<<an;
}
```
----
- **注:CF比赛时不能scanf("lld",&一个变量),所以用的是cin**

---

## 作者：BX_mot (赞：1)

## 1. [题目](https://www.luogu.com.cn/problem/CF1012A)

## 2.思路：
首先：**乘积一定，两数相差越小，和的绝对值越小**。

然后就可以 sort 一下排序,查找前面部分区间，再选择一段区间再找后面部分区间。

最后 ans 要考虑 $1$，$n$，$n+1$，$2n$ 的情况。
 
## 3.代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
int n;
int a[200001],ans;
signed main(){
	cin>>n;
	for(int i=1;i<=(n<<1);i++) cin>>a[i];
	sort(a+1,a+(n<<1)+1);
	ans=(a[n]-a[1])*(a[n<<1]-a[n+1]);
	for(int i=1;i<n;i++)
	{
		ans=min((a[n<<1]-a[1])*(a[n+i]-a[i+1]),ans);
	}
	cout<<ans<<endl;
	return 0;
}

```


---

## 作者：xiaoxiaoxia (赞：0)

# Part1 证明
其实这道题就是最值原理的一个应用，和同近积大。下面来看一下证明：

设两数分别为 $x$ 和 $y$，且 $xy=2$。

因为 $x$ 和 $y$ 的两数之差的平方大于 $0$。

若想取 $min=4$，则 $x$ 和 $y$ 的两数之差的平方等于 $0$。

所以 $x=y$（得证）。

因为两数之和的平方等于一个数的平方加另一个数的平方加上 $4$，想要 $x+y$ 最小，即需要两数之和的平方最小，即需要一个数的平方加另一个数最小。

所以，由已证得 $x=y$ 时 $x+y$ 有最小值。

所以，乘积一定，两数相差越小，和的绝对值越小。
# Part2 思路部分
我们可以分类讨论一下，先用sort一下找到小的部分，然后我们连续寻找区间枚举顺便根据题意就可以选出区间的后半部分。
# Part3 代码部分
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n;
ll a[200001],ans;
int main()
{
    cin>>n;
    for(int i=1;i<=(n<<1);i++) 
	{
		cin>>a[i];
	}
    sort(a+1,a+(n<<1)+1);
    ans=(a[n]-a[1])*(a[n<<1]-a[n+1]);
    for(int i=1;i<n;i++) 
	{
		ans=min((a[n<<1]-a[1])*(a[n+i]-a[i+1]),ans);
	}
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：knsg251 (赞：0)

## 题目意思
给了 $n$ 个点的坐标，要用一个矩形框柱所有给出的点，问这个矩形的最小面积是多少。
## 题目分析
这道题我们需要用到一个小学就学过的高级公式，**和一定，差小积大**。但是本题要用的是，**和一定，差大积小**。

所以矩形的最小面积就是：$S=(maxx_i-minx_i)\times(maxy_i-miny_i)$。

其他问题就很简单了，就是输入要注意一下，横纵坐标是混在一起的。

最后提醒一下：**不开 longlong 见祖宗**。
## 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,minn;
long long a[200005];
int main(){
	cin>>n;
	n *= 2;//特别注意 
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);//输入 
	sort(a+1,a+n+1);//排序 
	minn =(a[n/2] - a[1]) * (a[n] - a[n/2 + 1]);//上面的面积公式 
	for(int i=1;i<=n/2;i++){//一定是n/2 
		if(minn > (a[n] - a[1]) * (a[n / 2 + i] - a[i + 1])){
			minn = (a[n] - a[1]) * (a[n / 2 + i] - a[i + 1]);
		}
	}
	cout<<minn;//输出
	return 0;//over
} 
```

---

