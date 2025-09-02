# Inscribed Figures

## 题目描述

The math faculty of Berland State University has suffered the sudden drop in the math skills of enrolling students. This year the highest grade on the entrance math test was 8. Out of 100! Thus, the decision was made to make the test easier.

Future students will be asked just a single question. They are given a sequence of integer numbers $ a_1, a_2, \dots, a_n $ , each number is from $ 1 $ to $ 3 $ and $ a_i \ne a_{i + 1} $ for each valid $ i $ . The $ i $ -th number represents a type of the $ i $ -th figure:

1. circle;
2. isosceles triangle with the length of height equal to the length of base;
3. square.

The figures of the given sequence are placed somewhere on a Cartesian plane in such a way that:

- $ (i + 1) $ -th figure is inscribed into the $ i $ -th one;
- each triangle base is parallel to OX;
- the triangle is oriented in such a way that the vertex opposite to its base is at the top;
- each square sides are parallel to the axes;
- for each $ i $ from $ 2 $ to $ n $ figure $ i $ has the maximum possible length of side for triangle and square and maximum radius for circle.

Note that the construction is unique for some fixed position and size of just the first figure.

The task is to calculate the number of distinct points (not necessarily with integer coordinates) where figures touch. The trick is, however, that the number is sometimes infinite. But that won't make the task difficult for you, will it?

So can you pass the math test and enroll into Berland State University?

## 说明/提示

Here are the glorious pictures for the examples. Note that the triangle is not equilateral but just isosceles with the length of height equal to the length of base. Thus it fits into a square in a unique way.

The distinct points where figures touch are marked red.

In the second example the triangle and the square touch each other for the whole segment, it contains infinite number of points.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1156A/ecd8055b09d857a1401e35aa45bd638bb2a049f0.png)

## 样例 #1

### 输入

```
3
2 1 3
```

### 输出

```
Finite
7
```

## 样例 #2

### 输入

```
3
1 2 3
```

### 输出

```
Infinite
```

# 题解

## 作者：Doubeecat (赞：3)

这题看上去第一反应：  
> 什么？平面几何？？？说好的A题呢？？？  

读完样例&打完草稿：
> 这不就是个~~xx题~~吗

回到正文，这题需要我们处理三种图形的嵌套：  
1. 圆形
2. 等腰三角形（底边等于高）
3. 正方形  

这些嵌套其实总共只有六种情况，我们分类讨论（因为文中提到不会有一样的图形嵌套）：    
1. 圆形  
	(1).圆形套三角形  
    	![圆形套三角形](https://cdn.luogu.com.cn/upload/pic/57871.png)    
        如图，这种情况的三角形三个顶点和圆相交，对答案的贡献为3  
    (2).圆形套正方形  
    	![圆形套正方形](https://cdn.luogu.com.cn/upload/pic/57872.png)    
        如图，这种情况的正方形四个顶点和圆相交，对答案的贡献为4  
        
2. 三角形    
	(1).三角形套正方形    
    	![三角形套正方形](https://cdn.luogu.com.cn/upload/pic/57869.png)   
        如图，这种情况的正方形会与三角形底边重合，所以有无限多个点  
    (2).三角形套圆形  
    	![三角形套圆形](https://cdn.luogu.com.cn/upload/pic/57870.png)  
        如图，这种情况的圆形会与三角形的三边相交，对答案的贡献（点数）为3
3. 正方形  
	(1).正方形套圆形  
    	![正方形套圆形](https://cdn.luogu.com.cn/upload/pic/57873.png)  
         如图，这种情况的圆与正方形四边相交，对答案的贡献为4  
    (2).正方形套三角形  
    	![正方形套三角形](https://cdn.luogu.com.cn/upload/pic/57874.png)   
         如图，这种情况的正方形会与三角形底边重合，所以有无限多个点  
这样我们就可以写出一份看似正常的代码了： 

```cpp
#include <cstdio>
#include <cctype>
#define MAXN 101

inline int read() {
    int a = 0,f = 1;
    char v= getchar();
    while (!isdigit(v)) {
        if (v == '-') {
            f = -1;
        }
        v = getchar();
    }
    while (isdigit(v)) {
        a = a * 10 + v- 48;
        v = getchar();
    }
    return a * f;
}

int pre[MAXN],ans;

int main() {
    int n = read();
    for (int i = 1;i <= n;++i) {
        pre[i] = read();
    }
    for (int i = 2;i <= n;++i) {
		if (pre[i-1] == 1) {
			if (pre[i] == 2) {
				ans += 3;
			}
			else {
				ans += 4;
			}
		}
		
		if (pre[i-1] == 2) {
			if (pre[i] == 1) {
				ans += 3;
			}
			else {
				printf("Infinite");
				return 0;
			}
		}
		
		if (pre[i-1] == 3) {
			if (pre[i] == 1) {
				ans += 4;
			}
			else {
				printf("Infinite");
				return 0;
			}
		}
    }
    printf("Finite\n%d",ans);
    return 0;
}
```

笔者考试时，开开心心的拿着这份代码去交了，结果是：  
WA!  
为什么？
这里有一组数据可以hack掉这份代码：

```
Input:
3
3 1 2
Output:
Finite
6
程序输出:
Finite
7
```

为什么？  
我们可以画个图
![实例](https://cdn.luogu.com.cn/upload/pic/57875.png)
很明显，在计算圆形跟正方形，三角形与圆形的时候，A点被计算了两遍，这就是问题所在！  
所以，我们要对所有形如```3 1 2```这类的数据进行特判  
加上特判的代码：

```cpp
#include <cstdio>
#include <cctype>
#include <cstdlib>
#define MAXN 101

inline int read() {
    int a = 0,f = 1;
    char v= getchar();
    while (!isdigit(v)) {
        if (v == '-') {
            f = -1;
        }
        v = getchar();
    }
    while (isdigit(v)) {
        a = a * 10 + v- 48;
        v = getchar();
    }
    return a * f;
}

int pre[MAXN],ans;

int main() {
    int n = read();
    for (int i = 1;i <= n;++i) {
        pre[i] = read();
    }
    for (int i = 2;i <= n;++i) {
        if (pre[i-2] == 3 && pre[i-1] == 1 && pre[i] == 2) {
        	ans -= 1;
		}
		
		if (pre[i-1] == 1) {
			if (pre[i] == 2) {
				ans += 3;
			}
			else {
				ans += 4;
			}
		}
		
		if (pre[i-1] == 2) {
			if (pre[i] == 1) {
				ans += 3;
			}
			else {
				printf("Infinite");
				return 0;
			}
		}
		
		if (pre[i-1] == 3) {
			if (pre[i] == 1) {
				ans += 4;
			}
			else {
				printf("Infinite");
				return 0;
			}
		}
    }
    printf("Finite\n%d",ans);
    return 0;
}
```

使用这份代码，你就可以快乐上分了

---

## 作者：oceanfish (赞：1)

## 题目分析
[原题传送门](https://www.luogu.com.cn/problem/CF1156A)

题目给定图形数 $n$ 与 $n$ 个数字，其中数字在 $1 \sim 3 $ 取值，$1$ 代表圆，$2$ 代表高与底一样长的等腰三角形，$3$ 代表正方形。输入的顺序代表从外到内嵌套的顺序，对于这些嵌套图形，除了最外面的图形以外，其他里面的图形的大小都要尽量大。题目要求输出图形与图形之间的交点，若交点无穷，输出 `Infinite`，若交点可数，则先输出 `Finite`，再在第二行输出交点数量。


------------

## 解题方法
我们不难发现，一个大嵌套图形可以分解成多个由两个图形组成的小嵌套图形。经过分析，我们发现小嵌套图形分成以下几种情况：

1. 正方形套圆形

很容易知道，它们之间的交点数为 $4$。

2. 正方形套三角形

我们发现，由于三角形的底与高一样长，所以三角形与正方形有一条边是重合的，正因为如此，它们之间的交点数有无穷个。

3. 三角形套圆形

三角形内接圆与它的交点个数为 $3$。

4. 三角形套正方形

由于正方形要尽量大，所以正方形与三角形有一段重合的部分，它们之间的交点有无穷多个。

5. 圆形套正方形

它们之间的交点数为 $4$。

6. 圆形套三角形

圆内接的三角形和圆之间的交点个数为 $3$。

枚举完了情况，我们就可以写代码了。不过有一种情况需要特判，那就是外层为正方形，中层为圆形，内层为三角形的情况，在那种嵌套图形当中，有一个点会重复计算两次，我们只要针对其进行判断即可。

代码楼上已经给出了，这里就不多赘述了。

---

## 作者：PeaceSunset (赞：1)

拿到此题时，我看了一下。原以为是图论，实则是道**模拟**的~~大水题~~。
## 思路
此题有以下几个情况：

 1 ：圆套三角形，交点有 3 个。

 2 ：圆套正方形，交点有 4 个。

 3 ：三角形套圆，交点有 3 个。

 4 ：三角形套正方形，交点有无数个。

 5 ：正方形套圆，交点有 4 个。

 6 ：正方形套三角形，交点有无数个。

至此，我们就有了下面这段代码。


```cpp
for(int i=2;i<=n;i++){
	if(a[i-1]==1){ //外面是圆的情况 
		if(a[i]==2)ans+=3;
		else ans+=4;
		}
	if(a[i-1]==2){ //外面是三角形的情况 
		if(a[i]==1)ans+=3;
		else{
			cout<<"Infinite";
			return 0;
		}
	}
	if(a[i-1]==3){ //外面是正方形的情况 
		if(a[i]==1)ans+=4;
			else{
			cout<<"Infinite";
			return 0;
		}
	}
}
```

但是有一种**特殊情况**：外层为正方形，中层为圆，里层为三角形。

在这种情况下，我们可以发现三个图像交于一点，也就是说有一个点我们**重复算了**，所以要加个特判。


------------
## 完整代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[105],ans;
int main() {
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    
    for(int i=2;i<=n;i++){
		if(a[i-1]==1){ //外面是圆的情况 
			if(a[i]==2)ans+=3;
			else ans+=4;
		}
		if(a[i-1]==2){ //外面是三角形的情况 
			if(a[i]==1)ans+=3;
			else{
				cout<<"Infinite";
				return 0;
			}
		}
		if(a[i-1]==3){ //外面是正方形的情况 
			if(a[i]==1)ans+=4;
			else {
				cout<<"Infinite";
				return 0;
			}
		}
		if(a[i-2]==3 && a[i-1]==1 && a[i]==2)ans-=1; //特判重复的点 
    }
    cout<<"Finite\n"<<ans;
    return 0;
}
```



---

## 作者：Light_az (赞：1)

### 规律题

虽然洛谷上没过，但是在 CF 上已经通过，请放心食用

------------
由题意我们知道题目让我们求交点的数量

其实我们可以根据样例图片发现

- 当是 1 和 2 组合时，有 3 个交点数

- 当是 2 和 3 组合时，有 无数个 个交点数

- 当是 1 和 3 组合时，有 4 个交点数

但是我们发现一个特殊情况，当出现 3 和 1 和 2 的组合时

三角形和正方形的交点会与圆形和正方形的交点重合，这时候答案要减 1

这篇题解最大的亮点是通过函数判断来实现了多个 `if` 语句的特判，方便迅捷

最后要注意的是防止数组下标越界，这个代码应该最短了，正解如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define Test ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr)
using namespace std;
const int N=1e7+10;
ll n,ans=0;
ll a[N];
bool check(int id){
	if(a[id-2]==3&&a[id-1]==1&&a[id]==2) ans--;//特殊情况
	if(a[id-1]+a[id]==3) ans+=3;//1和2组合
	if(a[id-1]+a[id]==4) ans+=4;//1和3组合
	if(a[id-1]+a[id]==5) return 1;//2和3组合有无数解
	return 0;
}
int main(){
	Test;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(i==1) continue;
		if(check(i)){//特判无解情况同时改变答案
			cout<<"Infinite";
			return 0;
		}
	}
	cout<<"Finite\n"<<ans;//有解输出
	return 0;
}

```


---

## 作者：Steven_lzx (赞：0)

## Solution

**模拟**，画图可以得出如下结论：

- 三角形与正方形相邻，会有重边，此时 `puts("Infinite");` 。
- 三角形与圆相邻，会出现 3 个交点。
- 正方形与圆相邻，会出现 4 个交点。

然而，$\color{red}\texttt{WA}$ 了。

我们需要注意一种特殊情况：如果 $a[i-2]=3$ 且 $a[i-1]=1$ 且 $a[i]=2$，就会有一个点被我们多算了一遍，此时计数器要减一。

## Code

```cpp
int main()
{
	int n=fastio_read();
	for(int i=1;i<=n;i++)
	{
		a[i]=fastio_read();
	}
    for(int i=2;i<=n;i++)
	{
        if(a[i-2]==3&&a[i-1]==1&&a[i]==2)
		{
        	ans--;
		}
		if(a[i-1]==1)
		{
			if(a[i]==2)
			{
				ans+=3;
			}
			else
			{
				ans+=4;
			}
		}
		else if(a[i-1]==2)
		{
			if(a[i]==1)
			{
				ans+=3;
			}
			else
			{
				puts("Infinite");
				exit(0);
			}
		}
		else if(a[i-1]==3)
		{
			if(a[i]==1)
			{
				ans+=4;
			}
			else
			{
				puts("Infinite");
				exit(0);
			}
		}
    }
    puts("Finite");
    fastio_write(ans);
    putchar('\n');
    return 0;
}
```

---

## 作者：Abeeel51 (赞：0)

#### 题目大意
给你一串数字，每个数字代表一个图形，$1$ 代表圆，$2$ 代表等边三角形，$3$ 代表正方形，问这些图形从外到内嵌套后，有多少个交点？所有图形都为最大。
#### 解题思路
考虑所有的方法，有：

$1$ 套 $2$，$1$ 套 $3$，$2$ 套 $1$，$2$ 套 $3$，$3$ 套 $1$，$3$ 套 $2$。

他们的交点数分别是：$ 3 , 4 , 3 , + \infty ,4, + \infty $。

不难发现，三角形和正方形只要相邻，直接输出 $\texttt{Infinite}$。

然而这样，第三个点就无了。那一定就是算多啦。

那有没有重合的两个点呢？

嵌套方式为：$3$ 套 $1$ 套 $2$ 会出现一个共同交点。

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/doszv4mb.png)

蓝色点有两个点重合了，特判！这个图形只有 $6$ 个交点而刚才却计算出了 $7$ 个。

#### 代码
```cpp
#include <bits/stdc++.h.>
using namespace std;
int a[105]={0};
int main(int argc, const char * argv[]) {
    // insert code here...
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    long long Count=0;
    for(int i=2;i<=n;i++){
        if(a[i]==2&&a[i-1]==1&&a[i-2]==3){
            Count--;
        }
        if(a[i]==1){
            if(a[i-1]==2){
                Count+=3;
            }else if(a[i-1]==3){
                Count+=4;
            }
        }else if(a[i]==2){
            if(a[i-1]==1){
                Count+=3;
            }else if(a[i-1]==3){
                printf("Infinite");
                return 0;
            }
        }else if(a[i]==3){
            if(a[i-1]==1){
                Count+=4;
            }else if(a[i-1]==2){
                printf("Infinite");
                return 0;
            }
        }
    }
    printf("Finite\n%lld",Count);
    return 0;
}
```


---

## 作者：Sakii (赞：0)

~~好好一场CF数据出锅导致unr也是服帖~~

~~似乎好多人漏了一个小特判的来着~~


### 当第i个是三角形时，如果第i-2个是正方形，第i-1个是圆ans应该加2而不是加3.

剩下的结论大家应该都能手玩出来的叭直接贴代码了(

~~写太丑了勿喷~~


```cpp
//≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈
//  Date : 2019.05.01 22:31:02 May Wednesday
//  Author : Sakii
//  No website temporarily
//  I'm so vegetable , QAQ..
//≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈

#include<bits/stdc++.h>
#define re register
#define il inline
#define lowbit(x) x&(-x)

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

template <class T> inline void read(T &s){
    s = 0; re char ch = getchar(); re int w = 0;
    while(!isdigit(ch)) w |= ch == '-', ch = getchar();
    while(isdigit(ch)) s = (s << 1) + (s << 3) + (ch ^ 48), ch = getchar();
    if(w) s = -s;
}

    int n, a[110],ans;

    int main() {
        read(n);
        for(int i = 1;i <= n; i++){
            read(a[i]);
        }
        for(int i = 2; i <= n; i++){
            if(a[i-1] == 2 && a[i] == 1) ans += 3;
            if(a[i-1] == 3 && a[i] == 1) ans += 4;
            if(a[i-1] == 1 && a[i] == 2) {
                if(a[i-2] == 3) ans += 2;
                else ans += 3;
            }
            if(a[i-1] == 1 && a[i] == 3) ans += 4;
            if(a[i-1]==3 && a[i] == 2) {
                cout<<"Infinite";
                printf("\n");
                return 0;
            }
            if(a[i-1]==2 && a[i] == 3) {
                cout<<"Infinite";
                printf("\n");
                return 0;
            }
        }
        cout<<"Finite";
        printf("\n");
        cout<<ans;
        return 0;
    }



```


---

## 作者：世末OIer (赞：0)

简单模拟。

对于一个三角型:如果它的上一个是正方形，那么就会有重边(inf)；如果是圆，则会有三个交点

对于一个正方形:如果它的上一个是三角形，那么就会有重边(inf)；如果是圆，则会有四个交点

对于一个圆:如果它的上一个是正方形，那么就会有四个交点；如果是三角形，则会有三个交点

特殊情况:如果a[i-2]是正方形且a[i]是三角形，则答案要减一(有一个交点重复了)

---

## 作者：wxwoo (赞：0)

[$$\color{#0e90d2}\huge{\texttt{my blog}}$$](https://wxwoo.github.io/2019/05/02/solution-cf1156a/)

******

[原题目链接](https://www.luogu.org/problemnew/show/CF1156A)

*****

PS：

这题比赛时当场出锅……

std被hack……

整场比赛最后unrated……

******

对于每两个相邻的图形，交点数是固定的

也就是说我们可以打表

```
     1   2   3
   
1    /   3   4
2    3   /  inf
3    4  inf  /
```

但是！直接打表是错误的！std就是这样被hack的！

考虑这样一组数据：

```
3
3 1 2
```

按照上面的那张表计算，答案是7

但是实际上，三角形，圆形，正方形共用了一个交点

所以答案是6

所以对于每组这样的情况，要进行特判

代码如下

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

template<typename T> inline void read(T &x)
{
	char ch=getchar();
	T f=1;
	x=0;
	while(!('0'<=ch&&ch<='9'))
	{
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while('0'<=ch&&ch<='9')
	{
		x=(x<<3)+(x<<1)+ch-48;
		ch=getchar();
	}
	x*=f;
}
int n;
long long ans;
const int inf=0x3f3f3f3f;
const int res[4][4]={0,0,0,0,
                     0,0,3,4,
                     0,3,0,inf,
                     0,4,inf,0,};//打表
int a[110];
int main()
{
	read(n);
	for(int i=1;i<=n;++i)
	{
		read(a[i]);
	}
	for(int i=2;i<=n;++i)
	{
		ans+=res[a[i-1]][a[i]];//计算交点数
	}
	for(int i=3;i<=n;++i)
	{
		if(a[i-1]==1&&a[i-2]==3&&a[i]==2)//特判特殊情况
			--ans;
	}
	if(ans>=inf)
	{
		printf("Infinite\n");
	}
	else
	{
		printf("Finite\n");
		cout<<ans;
	}
	return 0;
}

```

---

## 作者：felixshu (赞：0)

[我是传送门](https://www.luogu.com.cn/problem/CF1156A)

## 题目大意

有三种图形，编号为 $1,2,3$ 分别代表圆、底边上的高和底边的长度相同的等腰三角形和正方形。

现在给出这些图形的顺序，你要将这些图形由外到内按顺序嵌套，且除了最外面的图形以外，其他里面的图形的大小都要尽量大。 问这些图形交点的个数。（可能有无数个交点）

## 分析

这是一个模拟水题。
我们可以直接枚举每一种组合方法，然后起来就好了。

- 圆里三角形，交点有 $3$ 个。

- 三角形里圆，交点有 $3$ 个。

- 圆里正方形，交点有 $4$ 个。

- 正方形里圆，交点有 $4$ 个。

- 三角形套正方形，交点有无数个。

- 正方形套三角形，交点有无数个。

然后就特判就好了。

## 下面是 AC 代码
```
#include <bits/stdc++.h.>
using namespace std;
int a[10000],n;
long long ans;
int main() 
{
    cin>>n;
    for(int i=1;i<=n;i++)
	{
	cin>>a[i];	
	}
    for(int i=2;i<=n;i++)
    {
        if(a[i]==2&&a[i-1]==1&&a[i-2]==3)
		{
		ans--;
        }
		if(a[i]==1)
        {
            if(a[i-1]==2)
			{
			ans+=3;
			}
            else 
			{
			if(a[i-1]==3)
			{
			ans+=4;
			}
			} 
        }
        else 
		{
		if(a[i]==2)
        {
            if(a[i-1]==1)
			{
			ans+=3;
			}
            else 
			{
			if(a[i-1]==3)
            {
                cout<<"Infinite";
                return 0;
            }
			} 
			
        }
        else 
		{
		if(a[i]==3)
        {
            if(a[i-1]==1)
			{
			ans+=4;	
			}
            else 
			{
			if(a[i-1]==2)
            {
                cout<<"Infinite";
                return 0;
            }
			}
        }
        } 
		}
    }
   cout<<"Finite \n"<<ans;
    return 0;
}
```


---

## 作者：shengyeqi (赞：0)

## 题面

[题目传送门](https://www.luogu.com.cn/problem/CF1156A)

## 思路

- 圆中三，有 $3$ 个交点。

- 圆中方，有 $4$ 个交点。

- 三中圆，有 $3$ 个交点。

- 三中方，有无数个交点。

- 方中圆，有 $4$ 个交点。

- 方中三，交有无数个点。

特殊情况：方中圆中三，这时会多算一个交点，所以要减去一。

注：圆是圆形，方是正方形，三是三角形。

## 代码

```
#include <bits/stdc++.h.>
using namespace std;
const int N=1e4+10;
int a[N],n;
long long sum;
int main() 
{
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=2;i<=n;i++)
	{
        if(a[i]==2&&a[i-1]==1&&a[i-2]==3)sum--;//特殊情况 
        if(a[i]==1)
		{
            if(a[i-1]==2)sum+=3;//圆中三 
			else if(a[i-1]==3)sum+=4;//圆中方 
        }
		else if(a[i]==2)
		{
            if(a[i-1]==1)sum+=3;//三中圆 
			else if(a[i-1]==3)//三中方是有无数个 
			{
                printf("Infinite");
                return 0;
            }
        }
		else if(a[i]==3)
		{
            if(a[i-1]==1)sum+=4;//方中圆 
			else if(a[i-1]==2)//方中三也有无数个 
			{
                printf("Infinite");
                return 0;
            }
        }
    }
    printf("Finite\n%lld",sum);//输出 
    return 0;
}
```


---

