# [WFOI - 02] I wanna win the race（比赛）

## 题目背景

> best is yet to come

kid 不小心进入了联机模式，他需要比他的对手更快通关才能取得胜利……

## 题目描述

kid 走进了一个场地，若干名选手在进行比赛，场地可以抽象为一个坐标系。

选手们要从 $\left(1,1\right)$ 跑到 $\left(n,n\right)$，若当前选手处在 $\left(x,y\right)$，则他们下一步可以移动到 $\left(x\pm1,y\right)$ 或 $\left(x,y\pm1\right)$，注意，他们**仅可以在第一象限活动**，即任何时候 $x>0,y>0$。

所有点最开始都是 $\texttt{A}$ 类点，主办方选择了一个三元组 $\left(a,b,c\right)$，将所有满足 $a\leq x\leq b$ 且 $y\leq c$ 的点 $\left(x,y\right)$ 变为 $\texttt{B}$ 类点，选手每经过一个 $\texttt{A}$ 类需要耗时 $1$ 秒，每经过一个 $\texttt{B}$ 类需要耗时 $2$ 秒。请注意，**起始点和终点也要纳入计算。**

kid 想要赢得这场比赛，他想知道**最少**需要多少秒能到达终点。

**请注意，在【数据范围】中有重要的约束条件。**

## 说明/提示

**【样例解释】**

下图是其中一种可行的方案，紫色点为 $\texttt{A}$ 类点，红色点为 $\texttt{B}$ 类点：

![](https://s1.ax1x.com/2022/03/06/bBvQPJ.png)

**【数据规模与约定】**

**本题采用 $\tt Subtask$ 捆绑测试。**

对于 $30\%$ 的数据，$1<a<b<n\leq 10^3，0<c\leq 10^3$。

对于 $100\%$ 的数据，$1<a<b<n\leq 10^9，0<c\leq 10^9$。

## 样例 #1

### 输入

```
5
2 4 3```

### 输出

```
9```

# 题解

## 作者：Elgo87 (赞：10)

显然我们需要尽可能避开 $\tt B$ 类点，那么就产生了这几种走法（方框里的代表  $\tt B$ 类点）：

![](https://cdn.luogu.com.cn/upload/image_hosting/7d3clhu9.png)

其中，第一、二张图是指 $c\ge n$ 时的走法，而第三张图指的是 $c<n$ 的走法。

显然没有其他更优的解法，若 $c\ge n$，则第一、二种走法取 $\min$ 即可，否则用第三种方法走即可。

代码：

```cpp
# include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n, a, b, c;
    cin >> n >> a >> b >> c;
    cout << (c >= n ? min(2*n-1 + y-x+1, 2*c+1) : 2*n-1);
    return 0;
}
```

---

## 作者：Engulf (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/P8220)

[更好的阅读体验](https://www.luogu.com.cn/blog/t-m-j-y-h-0-9/solution-p8220)

## 分析

看上去像个最短路对吧？但是 $n\le 10^9$，建图会炸掉。

可以看到题目保证了 $1<a,b<n$，也就是说：

![](https://s1.ax1x.com/2022/03/19/qEfFAO.png)

这两行是不会有 $\texttt{B}$ 类点的（不考虑 $c$ 的话）。

这就是两点间的**曼哈顿距离**。

计算很简单，$|x_1-x_2|+|y_1-y_2|$。

但是 $c$ 是个特例，它有可能 $\ge n$，就需要特判了。

当 $c\ge n$ 时，显然我们有 2 种策略：

1. 经过 $\texttt{B}$ 类点；
2. 绕过去。

![](https://s1.ax1x.com/2022/03/19/qE5mv9.png)

第一种路线：$(1,1)\rightarrow (1,5)\rightarrow (5,5)$。

第二种路线：$(1,1)\rightarrow (1,6)\rightarrow (5,6)\rightarrow (5,5)$。

显然我们对 2 种路线取最小值即可。

## 代码实现

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

inline int read(){
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch))f^=!(ch^45),ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
inline void write(int x){
	if(x<0)x=-x,putchar('-');
	if(x>=10)write(x/10);
	putchar(x%10+'0');
}
inline void writeln(int x){write(x);puts("");}

signed main(){
	int n=read(),a=read(),b=read(),c=read();
	int ans=(n-1)*2+1;
	if(c>=n){
		ans=min(n*2+b-a,2*c+1);
	}
	writeln(ans);
	return 0;
}
```

---

## 作者：Fire_Raku (赞：4)

## 题目分析：

这道题完美地诠释了，**读题**和**数据范围**是多么的重要。

我们首先看题，知道了几个重要的信息（其实出题的都标出来了）：

1. 他们仅可以在第一象限活动。
2. 任何时候 $x > 0$，$y > 0$。
3. 他们可以上下左右走。
4. 起始点终点纳入计算。

数据范围也说明了，不可能有 $a = 1$ 和 $b = n$ 的情况，也就是起始点上面没有 $B$ 类点。这就排除了很多的可能性了。于是我们有了想法：如果 $c < n$，那么直接往上走到 $(1 , n)$，再走到 $(n , n)$ 便是最优解，路上只有 $A$ 类点；如果 $c \ge n$，那么就计算这条路上的总共的用时就行了。这样做，你就可以得到[这样的结果](https://www.luogu.com.cn/record/72081928)。 

WA 的两个点是什么呢？这就是读题的重要了，题目说了可以在第一象限移动，且数据范围中 $c$ 是可以大于 $n$ 的（这就是前的 $c \ge n$ 的分类讨论），我们又有了一个大胆的想法：何不绕过 $B$ 类点，这样的秒数可能会是最小的。

![图](https://cdn.luogu.com.cn/upload/image_hosting/0ti8jyp0.png)

走法如上，蓝线为直接穿过 $B$ 类点，红线绕路，但是此图的最优解还是直接穿过去。那么答案就出来了，我们把之前的分类讨论改一改，只需要判断，当 $c \ge n$ 时，判断一下，是直接穿过 $B$ 类点的时间短，还是绕路短。代码很好写。

## Code:

```cpp
#include<cstdio>
#include<cmath>
using namespace std ;
long long n , a , b , c ; 
int main(){
	scanf("%d%d%d%d" , &n , &a , &b , &c) ; 
	if(c >= n){
		long long sum = c + n + (c - n + 1) ; //绕路的走法，当时没有化简
		long long ans = n - 1 + (b - a + 1) * 2 + (n - (b - a + 1)) ; //直接穿过 B 类点的走法，无化简
		if(sum > ans) printf("%d" , ans) ; 
		else printf("%d" , sum) ; //判断谁最小
	}
	else printf("%d" , n + n - 1) ; //当 c < n 时的走法
	return 0 ;
}
```


---

## 作者：TheSky233 (赞：3)

## Description

给定一个平面直角坐标系与 $\tt B$ 类点范围，每个 $\tt A$ 类点记 $1$ 秒，一个 $\tt B$ 类点记 $2$ 秒，求从 $(1,1)$ 走到 $(n,n)$ 的最小步数。

## Solution

一开始以为是一个搜索题，交了一发 [A*](https://www.luogu.com.cn/paste/e31imwmk) 上去，只有可怜的 $30$ 分，再看数据范围 $1 < a < b < n \leq 10^9,0 < c \leq 10^9$，于是考虑分情况讨论。

### Case 1

如图：![](https://cdn.luogu.com.cn/upload/image_hosting/m47ankl3.png)

当 $c < n$ 时，kid 可以直接从最上方绕过去（即先走到 $(1,n)$，再走到 $(n,n)$），此时的最短时间即为 $n + n - 1$。

### Case 2

如图：![](https://cdn.luogu.com.cn/upload/image_hosting/r2zbfx32.png)

当 $c \geq n$ 时，我们可以先走到 $(1,n)$，在穿过一片 $\tt B$ 类点到 $(n,n)$，此时的最短时间为 $(n+n-1)+(b-a+1)$。

于是我们兴高采烈地交上去了代码，却发现 WA #2 #18，这时就要牵扯到第三种情况。

### Case 3

如图：![](https://cdn.luogu.com.cn/upload/image_hosting/zjlxkwoq.png)

我们发现，从 $(1,n)$ 直接走到 $(n,n)$ 要经过一大批 $\tt B$ 类点，非常不优，于是就考虑从 $c$ 的上面一行（即 $(1,c+1)$）走到 $(n,c+1)$ 再绕到 $(n,n)$，此时的最小花费为 $(c+1)+(n-1)+(c-n+1)$。

最后，为了保险起见，最好开 long long！

## Code

```cpp
#include <cstdio>
#include <cmath>
#include <iostream>
#define int long long
using namespace std;

int n,m,a,b,c;

signed main(){
	cin>>n>>a>>b>>c;
	if(c<n) cout<<n+n-1;
	else cout<<min((n+n-1)+(b-a+1),(c+1)+(n-1)+(c-n+1));
	return 0;
}

```

---

## 作者：sgl654321 (赞：3)

### 题意描述
有一个矩阵，一开始每个点都是 $A$ 类点。再给定三个数 $a$，$b$，$c$，如果有一个点 $(x,y)$ 满足 $a\leq x\leq b$ 且 $0<y\leq c$ 时，他就变成了 $B$ 类点。保证所有点都在第一象限内。

kid 现在在 $(1,1)$，他要去终点 $(n,n)$。经过 $A$ 类点需要 $1$ 秒，$B$ 类点需要 $2$ 秒。问耗费的最少时间为多少。

### 解题思路
根据样例，得出 $c$ 可能不小于 $n$，但 $a$ 和 $b$ 都比 $1$ 大。所以我们分下面两种情况讨论：

若 $c<n$，很明显，先从点 $(1,1)$ 走到 $(1,n)$，再走到终点 $(n,n)$，经过的点全部都一定是 $A$ 类点，是最优方案。所以，直接输出 $2n-1$ 即可。

若 $c\ge n$，那么就有两种走法。一种是横向穿越 $B$ 类区域，还有一种是不经过 $B$ 类区域，向上越过它。

第一种走法可以描述为：先从点 $(1,1)$ 走到点 $(1,n)$，再走到终点 $(n,n)$。其中，点 $(a,n)$ 到点 $(b,n)$ 都是 $B$ 类点。所以耗时是 $2n-1+(b-a+1)=(2n+b-a)$ 秒。

第二种走法可以描述为：先从点 $(1,1)$ 走到点 $(1,c+1)$，再走到点 $(n,c+1)$，最后再向下走到终点 $(n,n)$。显然所有点都是 $A$ 类点。点 $(1,1)$ 到点 $(1,c)$ 共耗时 $c$ 秒，从点 $(1,c+1)$ 到点 $(n,c+1)$ 共耗时 $n$ 秒，从点 $(n,c)$ 到点 $(n,n)$ 共耗时 $(c-n+1)$ 秒。所以，共耗时 $c+n+(c-n+1)=(2c+1)$ 秒。

然后比较两种走法，选出其较小值即可。
### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a,b,c;
long long ans1,ans2;
int main(){
	cin>>n>>a>>b>>c;
	if(c<n){
		cout<<2*n-1<<endl;
		return 0;
	}
	ans1=2*n+b-a;
	ans2=2*c+1;
	cout<<min(ans1,ans2)<<endl;
	return 0;
}
```

---

## 作者：郑朝曦zzx (赞：2)

# 题目分析
## 题目背景
这是洛谷三月月赛的第二题，比较简单，主要考察数学知识（分类讨论）。
## 解题思路
由于 $\textit{1 < a < b < n}$ 所以必须要讨论是否竖着走要双倍代价。但是我们需要讨论是**不走回头路还是多走短的路经**，换句话说就是讨论是否有可能 **“走回头路”所花的时间比走很多“拥堵路段”** 所花的更少。
## 解题技巧
遇到这种题目可以先画出平面直角坐标系，照着图分析。这样往往会让问题变得更直观。
# 代码
```cpp
#include <cstdio>
int n, a, b, c;
int ans;
int main()
{
	scanf("%d %d %d %d", &n, &a, &b, &c);
	if (c < n) ans = 2 * n - 1;
	else
	{
		if (b - a + 1 > 2 * (c - n + 1))
			ans = c + n + (c - n + 1);
		else ans = n * 2 - 1 + (b - a + 1);
	}
	printf("%d", ans);
	return 0;
}
```


---

## 作者：Galex (赞：1)

这题恶心死我了。。。

题目说先看数据范围，我们就来看看数据范围。

- $1<a<b<n\leq 10^9$  这条没什么可说的，就是告诉我们要 $O(1)$ 解决。

仔细看第二条

- $0 < c \le 10^9$ 

你有没有发现什么猫腻。。。

没错！他居然没说 $c \le n$？！

这引出了本题的坑点：**路程中的坐标可以超过 $n \times n$ 的范围！**

也就是说，他可以绕过这个被选择的矩阵，到达终点！

知道坑点之后，代码就简单了。

如果 $n \le c$，就输出直接过去的时间和绕过去的时间的最小值。

否则，输出 $n \times  2 - 1$ 即可。

## 代码：

```cpp
#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;

int read(){
	int s = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
		s = (s << 1) + (s << 3) + (ch ^ 48), ch = getchar();
	return s * f;
}


signed main(){
	int n = read(), a = read(), b = read(), c = read();
	if (c >= n)//特判，如上文所述
		printf("%lld", min(n * 2 - 1 + b - a + 1, 2 * c + 1));
	else
		printf("%lld", n * 2 - 1);
	return 0;
} 
```


---

## 作者：hmzclimc (赞：1)

## 题意
原题传送门:

[Luogu P8220](https://www.luogu.com.cn/problem/P8220)

有一个可以被抽象为一个坐标系的场地。要从 $\left(1,1\right)$ 跑到  $\left(n,n\right)$ 。

所有点最开始都是 $\texttt{A}$ 类点，有一个三元组 $\left(a,b,c\right)$ ，将所有满足 $a\leq x\leq b$ 且 $y\leq c$ 的点 $\left(x,y\right)$ 变为 $\texttt{B}$  类点，选手每经过一个 $\texttt{A}$ 类需要耗时 $1$ 秒，每经过一个 $\texttt{B}$ 类需要耗时 $2$ 秒。

## 思路 
考虑两种情况：

![如果你看到了这行字那就请私信告诉我图挂了谢谢](https://cdn.luogu.com.cn/upload/image_hosting/xb6nqjg7.png "第一种")

![如果你看到了这行字那就请私信告诉我图挂了谢谢](https://cdn.luogu.com.cn/upload/image_hosting/f3j1qxk0.png "第二种")
 
向上，然后向右到达或者向上，绕开 $\texttt{B}$ 类点再回去。

简单的思考就可以发现这两条路的其中一条就是最短的路。

那么答案就是他们俩之间取最小值啦。

## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<string>
#include<iomanip>
using namespace std;
long long n,a,b,c;
long long l1,l2=-1,ans1,ans2;
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>a>>b>>c;
    if(c>=n){
        l1=b-a+1; 
    }
    if(c>=n){
        l2=n-1+c-n+1;  //从上面绕
    }
    ans1=2*n-1+l1; //累加答案
    ans2=l2+c+1;
    cout<<min(ans1,(l2==-1?2000000000:ans2));
    return 0;
}
```

---
~~比赛时这题还是被卡了好几遍才过的~~

谢谢观看，本人是菜鸡，如发现有问题，请指出，谢谢。

---

## 作者：Firstly (赞：1)

## **题目思路：**

首先，如果不考虑 $\texttt{A}$ 类点和 $\texttt{B}$ 类点的区别，那么从 $(1,1)$ 到 $(n,n)$ 的最小秒数是 $n+n-1$ 秒，即它的曼哈顿距离。

因为走 $\texttt{B}$ 类点不如走 $\texttt{A}$ 类点优，而 $\texttt{B}$ 类点会优先在 $x$ 值小的地方生成，所以我们会选择先走到 $(n,1)$，然后再走到 $(n,n)$。所以如果 $c<n$，那么最小秒数依旧是 $n+n-1$ 秒。

但是如果 $c\geq n$ 呢？这种情况我们可以有两种可能为最优的方案，一种是先直线走到 $(n,1)$，再直线走到 $(n,n)$，另一种情况是绕过所有 $\texttt{B}$ 类点，贴着线走。这两种方案去取较优值即可。

## **Code：**

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
long long n,a,b,c;
int main(){
    cin>>n>>a>>b>>c;
    if(c<n)cout<<n+n-1;
    else{
        long long x=n+n+b-a;
        long long y=n+n-1+2*(c-n+1);
        cout<<min(x,y);
    }return 0;
}
```


---

## 作者：InterN_NOT_FOUND (赞：1)

~~这道题的数据范围卡了我整整2h。~~

~~我整整花了2h才弄明白出题人为甚么把4个数的数据范围分开。~~

仔细观察数据范围我们可以发现，题目**没有规定** $c \le n$ ，也就是说， $c$ 可以大于 $n$。

$c < n$ 的情况，容易看出答案是 $2 \times n - 1$ 。但 $c \ge n$ 时， 我们有两种选择：直接从B类点上走过去或者从上面绕过去。不难看出直接从B类点上走过去多花费的时间为 $(b - a + 1)$ 秒，而绕过去多花费的时间为 $2 * (c - n + 1)$ 秒。那我们比较这两个值选较小的即可。

示意图：

![](https://cdn.luogu.com.cn/upload/image_hosting/p9sw0pxh.png)

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int n, a, b, c;

signed main()
{
	cin >> n >> a >> b >> c;
	cout << (n * 2 - 1 + (c >= n ? (2 * (c - n + 1) > b - a + 1 ?  b - a + 1 : 2 * (c - n + 1) ) : 0));
	return 0;
}

```


---

## 作者：xwh_Marvelous (赞：0)

这道题在月赛里算是很良心的，听说本有十二类分类最后砍到两类。~~十二类肯定会被我喷。~~

#### 30pts

暴力算法，用优先队列跑一遍广搜。

### 100pts

正解，我们可以发现，因 $c$ 的大小不同，有两种情况。

1. 当 $c<n$ 时，这时候 $\mathtt{B}$ 类点对答案没有影响，因为至少有一条路线可以绕过所有 且不用绕路，答案为 $n+n-1$。
1. 当 $c\ge n$ 时，这样有两种可能。一是绕路，答案为 $c+c+1$；另一种是直接穿过 $\mathtt{B}$ 类点，答案为 $n+n-1+(b-a+1)$。两者取最小值即可。

### AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,a,b,c;
int main(){
	cin>>n>>a>>b>>c;
	if(c<n)cout<<n+n-1;
	else cout<<min(n+n-1+(b-a+1),c+c+1);
	return 0;
}
```

~~long long 是 A 题后遗症~~

---

## 作者：eastcloud (赞：0)

## P8220 I wanna win the race 题解

### 题意简析

给出 $n$，$a$，$b$，$c$，每经过一个点耗费一秒，如果当前坐标  $(x , y)$ 满足 $ b \ge x \ge  a $，$ y \le c $ 则多耗费一秒，求从 $ ( 1 , 1 ) $ 走到 $ ( n , n ) $ 要耗费几秒。

### 题目分析

我们先看数据范围，可以得到 $ a > 1 $，也就是说地图最左边一列的点一定只需要耗费一秒，这时我们分情况讨论：
1. 当 $ c \ne n $ 时，最上面一行也一定只需耗费一秒，可得总耗时为 $ 2 * n - 1 $。
2. 当 $ c = n $ 时，由于无论我们从哪个方向走，必定会经过中间需要耗费两秒的点，答案则为情况1的结果加上 $ b - a + 1 $，但由于在这种情况下 kid 还可以到 $ n $ 的范围外绕着走，所以我们在计算答案的时候要把这种情况即 $ 2 * c + 1 $ 也考虑到。

### 代码
记得开 long long

```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#define ll long long 
using namespace std;
int main(){
	ll n,a,b,c;
	cin>>n>>a>>b>>c;
	if(c<n)cout<<2*n-1;//情况1
	else cout<<min(2*c+1,2*n+b-a);//情况2
}
```


---

## 作者：DengDuck (赞：0)

按照题意，只能走右或上

仔细观察，我们发现**一直向上，再一直向右是最优的**

为什么？

> 所有满足 $a≤x≤b$ 且 $y≤c$ 的点 $(x,y)$ 为 $\texttt{B}$ 类点

题意告诉我们，

- 上面是 $\texttt{B}$ 类点 下面一定也是

- 下面是 $\texttt{B}$ 类点 上面不一定是

所以走上面更优

但是以上做法是 $0$ 分,每个 $\texttt{subtask}$ 正好一个点    $\color{red}{\texttt{Wrong Answer}}$

还有另外一种可能，如果 $c>n$ ,有可能我们从上面跨过上面的二类点更优，

加上判断就 $\color{green}{\texttt{Accepted}}$ 了

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a,b,c,sum;
int main(){
    cin>>n>>a>>b>>c;
    sum=2*n-1; //一定要走的       
    if(c>=n)
    {
        if((c-n+1)*2<=(b-a+1))//从上面跨走
        {
            sum+=2*(c-n+1);
        }
        else
        {
            sum+=b-a+1;
        } 
        if(a==1)//加上二类点的代价
        {
            sum+=n-1;
        }
    }
    cout<<sum;
}
```

---

## 作者：Cocoly1990 (赞：0)

这不是题解，这只是**出题人**上传的一份**提示**：

![qMXI9U.png](https://s1.ax1x.com/2022/03/22/qMXI9U.png)

唯一的坑点。

---
碎碎念：不知道有没有创下月赛有史以来最高提交数。

我预料到这题会交很多发，我是没想到会这么多。

好好看看提示和讨论区，别那么早看题解，自己动手做一下，总是更好的。

---

## 作者：yinhy09 (赞：0)

## 思路讲解：

本题是一道分类讨论的数学题，主要考察分类的全面性。

本题有两种走法，第一种是直接采用最短路线，先往上，再往右；还有一种是直接从上面绕过那些 $\texttt{B}$ 类格子。

显而易见，当 $c<n$ 时，直接先往上，再往右一定最优，然而当 $c \ge n$ 时，需要从刚才的两种情况中取最优。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long read()
{
	char c;
	long long x=0;
	long long f=1;
	c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
int main(){
	long long n,a,b,c;
	n=read();a=read();b=read();c=read();
	unsigned long long ans=2*n-1;
	if(c>=n)
	{
		ans+=min(b-a+1,2*c-2*n+2);//取最优
	}
	printf("%d",ans);
	return 0;
}

```

谢谢观看~

---

## 作者：0000pnc (赞：0)

首先看题面。  
题目的大意就是从点 $(1,1)$ 走到 $(n,n)$，只能在第一象限进行活动，每次可以走到上下左右四个点。  
每经过一个点，就需要 $v_{ij}$ 时间。现在给出 $a,b,c$，对于 $a \leq x \leq b,y \leq c$，$v_{xy}=2$，其余的 $v_{ij}=1$。求最小时间。  

~~显然的结论题。~~  
这道题可以用**分类讨论**的思想。  

对于 $m \lt n$ 的情况，显然先往上走 $n-1$ 格，再往右走 $n-1$ 格是最优解，答案为 $2n-1$。  

对于 $m \geq n$ 的情况，有两种可行的方法：  
* 直接穿过 B 类点的区域。(花费：$2n-1+b-a+1=2n+b-a$)
* 向上绕过 B 类点区。(花费：$2n-1+2(c-n+1)=2c+1$)  

因此，答案就为 $\mathrm{min}(2n+b-a,2c+1)$。

下面附上 AC 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, m, l, r, ans;

ll read() {
    ll x = 0;
    int f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-') {
            f = -1;
        }
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}

int main() {
    n = read(), l = read(), r = read(), m = read();
    if (m < n) {
        ans = 2 * n - 1;
    }
    else {
        ans = min(2 * n + l - r, 2 * m + 1);
    }
    cout << ans;
    return 0;
}
```

---

## 作者：hank0402 (赞：0)

### 题目大意：

在一个坐标平面上，若点 $(x,y) $ 满足 $a\le x\le b\ \text{and}\ y\le c$，那么到达这个点要花费 $2$，否则要花费 $1$，并且只能在第一象限内活动，求从 $(1,1)$ 走到 $(n,n)$ 的最小花费，注意起点和终点的花费也要算。

### 题解：

考虑两种走到终点的方式：


分两种情况考虑：

- $c< n$ : 直接向上走到 $x=n$ 后向右走到 $y=n$. 因 $a,b$ 的数据范围，所以不会经过花费为 $2$ 的点，答案为 $n\times 2-1$.

- $c\ge n$ : 这时又有两种情况，一种是不绕路的走法，按照 $c<n$ 的走法走，这时往右走的时候多出了 $b-a+1$ 个花费较高的点，所以该走法答案为 $n\times 2-1+b-a+1$. 另外一种走法是绕过花费较高的点，先向上走到 $x=c+1$ 然后向右走到 $y=n$ 再向下走到 $x=n $ 即可，所以该走法答案为 $c + 1 + (n - 1) + c + 1 - n$. 最终的答案即两种走法答案取 $\min$ .

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define debug(a, n)\
	printf(#a ":");\
	for(int i = 1; i <= n; ++i) cout << a[i] << ' ';\
	cout << '\n';
typedef long long ll;
ll n, a, b, c;
int main() {
	scanf("%lld %lld %lld %lld", &n, &a, &b, &c);
	ll ans = n * 2 - 1;
	if(c >= n) {
		ans += (b - a + 1);
		ans = min(ans, c + 1 + (n - 1) + c + 1 - n);
	}
	printf("%lld", ans);
	return 0;
}

```

---

## 作者：哈士奇憨憨 (赞：0)

## 思路
分类讨论

当 $c<n$ 时，我们只需要一直往上走到 $(1,n)$，在从 $(1,n)$ 走到 $(n,n)$ 即可，时间为 $(2n-1)s$。

当 $c \ge n$ 时，我们可以往上走到 $(1,n)$，在从 $(1,n)$ 走到 $(n,n)$，也可以往上走到 $(1,c+1)$，在从 $(1,c+1)$ 走到 $(n,c+1)$，最后走到 $(n,n)$。由于是取最小值，所以对这两种方案求 $\min$。
## CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n, a, b, c;
int main(){
    cin >> n >> a >> b >> c;
    if(c < n){
        cout << n + n - 1;
    }else {
        cout << n + 1 + min((c + 1 - n) * 2 - 2 + n, (1 - a + b) * 2 + n - b + a - 3);
    }
    return 0;
}
```

---

## 作者：charleshe (赞：0)

这题作为赛场上的 B 题还是蛮多坑的。

首先，看数据范围（因为题目里明确说在数据范围中有重要的约束条件）：

$1 < a < b < n \leq 10^9$。

看懂了吗？这说明**起终点均不会是 B 类点！**

那么：

- 如果第 $n$ 行均为 A 类点，则 kid 需要 $2 \times n - 1$ 秒到达终点。

- 否则，kid 需要的时间为 $n + (b - a + 1) \times 2 + (n - 1 - (b - a + 1))$，这是我考场上推出的式子，凑合着看吧。

就提交了？

然后你就会 WA 两个点，再由于捆绑测试而获得 $0$ 分。

WA 的原因是：kid 可以超越场地，超越到 $n$ 行之上，直到到达 A 类点，再从另一边的 A 类点返回（考场上就是这个让我爆零了）。

因此，还需要用这种方案和原本直传 B 类点的方案进行比较，时间较小的才是正确答案。

另外：此题数据量较大，需要长整型存储。

把这些都想到了，代码就好写了。

```cpp
#include <iostream>
using namespace std;
int main(){
	long long n,a,b,c;
	cin>>n>>a>>b>>c;
	if(n>c) cout<<n*2-1;
	else{
		long long ans=min(n+(b-a+1)*2+(n-1-(b-a+1)),c+n+abs(c-n+1));
		cout<<ans;
	}
	return 0;
}
```


---

## 作者：__a__ (赞：0)

# P8220题解

## 思路

这题是一道**贪心**题。

我们先假设所有点都是 A 点。那么经过所有点的用时相等，怎么走最近呢？当然是不返回。kid 从 $(1,1)$ 走到 $(n,n)$，最短要经过 $2n-1$ 个点（包括起点和终点）。

现在，我们按照题目叙述的方式，将一些 A 点变成 B 点。可以分为以下几种情况：

- $c<n$
	
	这种情况，B 点没有穿过 Y 坐标为 $1\sim n$ 的区域，kid 可以先从 $(1,1)$ 走到 $(1,n)$，再走到 $(n,n)$，不会经过任意一个 B 点，时间最短。
    
	```cpp
	if(c<n)printf("%lld",n*2-1);
	```
	
	注意：**题目中** $n$ **的范围是** $n\le10^9$**，我们推导的公式** $2n-1$ **的数据范围是** $2n-1\leq2\times10^9-1$，超过了 `int` 的范围，要开 `long long`！

- $n\le c$
	
	这时候就又有两种办法了：
	
	1. 穿过 B 点，到达终点，
		
		**额外**耗时：$b-a+1$ 秒；
		
	2. 绕过 B 点，到达终点，
		
		**额外**耗时：$2(c-n+1)$ 秒。~~（我被这种方法的两个测试点坑了半小时）~~
	
	那么，我们要采取哪种方案呢？**怎样快，怎样走！**
	
	```cpp
	if(c>=n)printf("%lld",n*2+1+(2*(c-n+1)>b-a+1?b-a+1:2*(c-n+1)));//同样，记得开long long。
	```
这题是不是很简单？

## 完整代码

```cpp
#include<cstdio>
int n,a,b,c;
int main()
{
	scanf("%d%d%d%d",&n,&a,&b,&c);
	if(c<n)printf("%lld",n*2-1);
	else printf("%lld",n*2+1+(2*(c-n+1)>b-a+1?b-a+1:2*(c-n+1)));
	return 0;
}
```

---

## 作者：Tx_Lcy (赞：0)

## 题目分析
对于这道题目，开始我还以为是 DP ，但这个数据范围立马告诉我这是一个立即出答案的题目。仔细分析题目，我们会发现如下图所示，**红色点（B类点）总是分布在以 $x$ 轴的正半轴为底边的某个矩形中。**

![](https://cdn.luogu.com.cn/upload/image_hosting/7cn4e3hv.png)

又因为 $1<a<b$，所以函数 $y=1$ 所在的这一条直线一定不会被红色点覆盖，也就是这些点的代价都是 $1$。所以我们的路径必定要经过下图的这一条线.

![](https://cdn.luogu.com.cn/upload/image_hosting/tp1q4lp5.png)

接下来我们又要分两种情况讨论，第一种是 $c<n$，我们选择直接往右走到终点。

![](https://cdn.luogu.com.cn/upload/image_hosting/nlpydzk7.png)

还有一种就是 $c>n$ 或 $c=n$。这时我们就可以走两种，一种是直接向右走，还有一种是绕开红色点，最后我们取最优值即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/5kvv92m9.png)

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int min(int a,int b){return a>b?b:a;}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;cin>>n;
	int ans=n*2-1;
	int a,b,c;cin>>a>>b>>c;
	if (c>=n) ans+=min(2LL*(c-n+1),b-a+1LL);//第二种情况
	cout<<ans;
	return 0;
}
```


---

## 作者：liucang (赞：0)

# P8220 题解

这道题乍一看，很像 priority_queue 的 BFS 嘛。但是当你做下去，你会发现**不正常的数据范围**。

$$ 1 < a < b < n \le 10^9 $$

$$ 1 < c \le 10^9 $$

10 的 9 次方 !? 很明显要换个思路了。

首先去掉 $a,b,c$ 的限制，只看最短路花费秒数。很明显花费秒数是 $n\times2-1$ 秒。接着看 $a,b,c$ 的限制。因为 $\text{B}$ 类是长方形，首选肯定是先上到 $(1,n)$ 再右到 $(n,n)$ ，一步到位。再来看如果 $ n\le c $ 是绕过去还是直接穿过 $\text{B}$ 类。

绕过去多花费秒数：$ (c-n+1)\times2 $

穿过去多花费秒数：$ b-a+1 $

写一个 if 判断哪个更少即可。

**AcCode:**

```cpp
#include<iostream>
using namespace std;
int main(){
    long long n,a,b,c,k1=0;
    cin>>n>>a>>b>>c;
    k1=min(k1=b-a+1,(c-n+1)*2<0 ? 0 : (c-n+1)*2); 
    //上文提到判断
    //注意如果 c < n 要把负数改成 0
    cout<<n+n-1+k1;
    return 0;
}
```

非常简单。

---

## 作者：3a51_ (赞：0)

啊虽然很简单但是坑贼多。

~~比赛一开始以为这是一道天真无邪的 `BFS`~~

在下面的所有示意代码块中，`-`表示 $\texttt{B}$ 类点，`.`表示 $\texttt{A}$ 类点。

不难发现 $\texttt{B}$ 类点一定是一个长方形。

例如这样：

```
. . . . .
. . . . .
. . - - .
. . - - .
. . - - .

n=5,a=3,b=4,c=3示意代码块。
```
然后发现只要不是 $c=n$ 的情况就可以直接以最短路走到 $(n,n)$，答案是 $2 \times n-1$。

在我们仔细观察数据范围之后找到了一个坑。

$1<n<10^9$，$0<c<10^9$；

也就是说 $c$ 可能大于 $n$。

举例：

```
. . - - .
. . - - .
. . - - .
. . - - .
. . - - .

n=5,a=3,b=4,c=5示意代码块
```

所以我们需要把源代码 `c==n` 改为 `c>=n`。

这样就有 $90$ 分的好成绩了。

不过剩下那  $10$ 分在哪里呢？

仔细阅读题面，我们知道了只要在第一象限内移动都是合法的。所以没有必要只在 $n \times n$ 的正方形里面移动。

当 $c<n$ 时，出正方形反而浪费时间。

当 $c>=n$ 时，唯一可能减少时间的方案就是从 $c+1$ 行绕过去。接下来就是推式子然后比大小了。

举例：

```
  - - -
. - - - .
. - - - .
. - - - .
. - - - .
. - - - .
n=5,a=2,b=4,c=6示意代码块

 _______
| - - - |
| - - - |
| - - - .
| - - - .
| - - - .
| - - - .
n=5,a=2,b=4,c=6的一种走法
```
此时左边是 $c$，顶面与右面 $c+1$，总共 $2 \times c+1$。


所有最后就能快乐地写程序啦！

最终程序的主函数：

```cpp
	//;;;;;
	read(n,a,b,c);
	int ans=n+n-1;
	if(c>=n) ans+=b-a+1;
	if(c<n){
		write(ans);
		return 0;
	}
	int tmp=c+n;
	tmp+=c-n+1;
	int k=min(ans,tmp);
	write(k);
```

---

## 作者：Cure_Wing (赞：0)

* ### 题意
- 在第一象限中找一条路径，使从 $(1,1)$ 到 $(n,n)$ 的时间最少。
* ### 思路
- 首先我们先想一个问题，如果途中没有 $B$ 点，只有 $A$ 点，通过简单的证明可得，最短时间永远是 $2n-1$。
- 现在我们考虑有 $B$ 点的情况。
- 首先考虑最短路上没有 $B$ 点的情况，此时最短时间仍然为 $2n-1$。
- Q:这种情况满足什么条件呢？
- A:观察数据 $1<a<b<n$，可知为 $(x,1)$ 和 $(x,n)$ 的点一定没有 $B$ 点，当 $c<n$ 时，结合下图（题目原图）可证最短路仍然存在。
- ![图1](https://s1.ax1x.com/2022/03/06/bBvQPJ.png)
- 接下来我们考虑 $c>=n$ 的情况。
- 此时原先的最短路已经不存在，此时到达 $(n,n)(F)$ 应该有 $2$ 种优秀的方案（如下图所示）：
- ![第二种情况](https://cdn.luogu.com.cn/upload/image_hosting/t0f1380x.png)
- 1.横穿 $B$ 点区（如 $A-E-F$），相比原最短路增加时间 $b-a+1$。
- 2.从上方越过 $B$ 点区（如 $A-K-O-F$），相比原最短路径增加时间 $2(c-n+1)$。
- 显然易见，此时应对二者取最小值。
* ### 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,a,b,c;//不开long long见祖宗
int main(){
	scanf("%lld%lld%lld%lld",&n,&a,&b,&c);
	if(c<n) return !printf("%lld\n",(n<<1)-1);//当最短路仍然存在时
	return !printf("%lld\n",(n<<1)-1+min(b-a+1,c-n+1<<1));//当不存在时
}
```
~~这™两题全是long long......~~

---

## 作者：可爱的小于 (赞：0)

题目大意：求 kid 到点 $(n,n)$ 花费的最小时间。

思路： 

$1.$ 判断特定点是否达到 $n$ 点，否则就不需要加时间。

$2.$ 如果是就求横向活动需要时间的最小值。

代码：

```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
long long n,a,b,c;//定义
int main()
{
	cin >> n >> a >> b >> c;//输入
	if(c>=n)//判断
		cout << n+1+min((c-n+1)*2+(n-2),(b-a+1)*2+(n-(b-a)-3));//求最小值。
	else
		cout << n+n-1;//否则输出原时间
	return 0;
}
```


---

## 作者：Jorisy (赞：0)

这一题告诉了我们数据范围是有多重要。

首先，根据数据范围中 $1<a<b<n \le 10^3$ 看出，$a$ 点和 $b$ 点不会到 $n \times n$ 方块的边缘。

但是 $c$  没有约束于 $<n$。

因此存在两种情况：$c<n$ 和 $c \ge n$。

$c<n$ 很好算，就是 $2n-1$。

但对于 $c \ge n$，有两种方法去走。

一种是直接走过 B 类点，答案就是 $(2n-1)+(b-a+1)=2n+b-a$。

另一种是最容易忽略的。由于地图不是只局限于 $n \times n$，因此我们也可以选择从上方绕过，也就是 $2n-1+2(c-n+1)=2n-1+2c-2n+2=2c+1$。

两者再取最小即可。

赛时 AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
	long long n,a,b,c,ans=2e9;
	cin>>n>>a>>b>>c;
	if(c<n) ans=2*n-1;
	else ans=min(2*n-1+b-a+1,2*n-1+(c-n+1)*2);
	cout<<ans;
 	return 0;
}
```

---

## 作者：sh7adow_ (赞：0)

## 简要题意
简单模拟，求从 $(0,0)$ 到 $(n,n)$ 的最小花费时长。注意：**仅可以在第一象限活动**，所以不能经过坐标轴，只能上下或左右移动，不能斜着移动。
## 分析
我们不妨定义 $1$ 格为 $1$ 单位时间， $a,b,c,d$ 分别表示 $(n,n)$ 中的 $n$ ，**三元组 $(a,b,c)$ 中的** $a,b,c$ 。 那么经过  $\texttt{A}$ 类时花 $1$ 格，即 $1$ 单位时间。同理经过  $\texttt{B}$ 类时花 $2$ 格，即 $2$ 单位时间。

- 1. 当 $(n,n)$ 中的 $n$ 大于三元组中的 $c$ 时，那么沿着直线 $x=1$ 向上走 $a$ 格，再向右走 $a$ 格就可以了。记得去重减 $1$ 。此类记得要特判。
- 2. 当 $(n,n)$ 中的 $n$ 小于三元组中的 $c$ 时，**第一种走法**：考虑不经过**所有的 $\texttt{B}$ 类点。** 先沿着直线 $x=1$ 向上走到 $(c+1,0)$（即向上走 $d+1$ 格） ，再沿直线 $y=c+1$ 向右走 $a-1$ 格，最后再向下走 $d+1-a$ 格。**总路程为** $2\times d+1$ 格。
- 3. 当 $(n,n)$ 中的 $n$ 小于三元组中的 $c$ 时，**第二种走法**：考虑经过**在直线 $y=n$ 上的 $\texttt{B}$ 类点。** 先沿着直线 $x=1$ 向上走到 $(n,0)$（即向上走 $a-1$ 格） ，再沿直线 $y=n$ 向右走到终点  $(n,n)$ （即向右走 $a-1$ 格）。最后再加上经过 $y=n$ 上的 $\texttt{B}$ 类点多余的路程（因为原来算了一次，所以这里只要再加上一个单位即可。即加上 $c-b+1$ ）。**总路程为** $2\times a+c-b$ 格。

其中第一点先判断是否满足，然后如果不满足再判断第二点和第三点所得的路程大小，输出路程小的那个即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    long long a,b,c,d,ans1=0,ans2=0;//记得赋值
    cin>>a;
    cin>>b>>c>>d;
    ans1=2*d+1;//第一种一般情况
    ans2=a*2+c-b;//第二种一般情况
    if(d<a) cout<<a*2-1;//特殊情况
    else if(d>a&&ans1>=ans2) cout<<ans2;
    else if(d>a&&ans1<ans2) cout<<ans1;
}
```

完结撒花！

---

## 作者：ChenLingHan (赞：0)

正如题目所说：**请注意，在【数据范围】中有重要的约束条件。**

首先，数据范围 $1<a<b<n$ 以及 $0<c$ 说明了所有 $b$ 类点在一个长为 $c$，宽为 $（b-a+1）$ 的**矩形**内（且该矩形在起点和终点之间）。

其次，不难发现，我们还可以作一个以起点、终点为对角线的**正方形**（边长为 $n$）。

那么就有两种情况：

1. 矩形在正方形内部（不含边）。
2. 矩形超出了正方形（“凸”字形）。

**对于第一种情况**，显而易见，走边是最优解（向上再向左）。

**对于第二种情况**，我们有两种方案：

1. 和第一种情况一样，仍然走边（向上再向左）。
2. 绕过矩形突出来的部分，全走 $a$ 类点。

那么这两种情况的最小值即为第二种情况的最优解。

**对于以上这两种情况**，我们将时间用含 $n,a,b,c$ 的代数式表示出来即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long n,a,b,c;
	cin>>n>>a>>b>>c;
	if(c>=n) cout<<min(2*n+b-a,2*c+1);  
	else cout<<2*n-1; 
	return 0;
} 
```

---

