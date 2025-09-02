# [NWRRC 2016] Anniversary Cake

## 题目描述

两个学生，Adam 和 Anton，正在庆祝他们未通过数学逻辑考试两周年。在当地超市经过仔细挑选后，他们买了一个长方形的蛋糕，蛋糕的尺寸是整数，并且有两根蜡烛。

后来在校园里，Adam 把蜡烛插在蛋糕的不同整数点上，并把刀交给 Anton 来切蛋糕。切口应该从蛋糕边缘的整数点开始和结束，并且不能碰到蜡烛。每一块蛋糕上应该正好有一根蜡烛。请帮助 Anton 找到切口的起点和终点。

一个 $7 \times 3$ 的蛋糕和两个蜡烛放在 $(2, 2)$ 和 $(3, 2)$。

Anton 可以从 $(0, 0)$ 到 $(4, 3)$ 切开这个蛋糕。

## 说明/提示

时间限制：2 秒，内存限制：256 MB。

spj 提供者：@[shenyouran](\/user\/137367)

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
7 3 2 2 3 2 
```

### 输出

```
0 0 4 3
```

# 题解

## 作者：Doubeecat (赞：7)

> A.Anniversary Cake
> 
> 给你一个 $w\times h$ 的矩形，在矩形中有两个整点。请你找到一种方案将矩形划分成两个部分，每个部分中各有一个点。
> 
> $w,h \leq 10^9$

相对简单的构造题，大概在Div2A难度，考场上考虑比较simple所以挂了两发。

我们设两个点坐标为 $(x_1,y_1),(x_2,y_2)$ 一共有两种情况需要我们讨论，一种情况是横坐标相同，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/bfzk634m.png)

这种情况下，我们可以直接构造到两个点的最左和最右端，即 $(0,y_1),(w,y_2)$ 

第二种情况就是横坐标不同，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/03oov9kp.png)

这种情况下，我们可以直接构造到两个点的最下和最上方，即 $(x_1,0),(x_2,h)$

想出方案后代码就很好写了。

Code:

```cpp
signed main() {
    //FO(anniversary)
	read(w,h,x1,y1,x2,y2);
    if (x1 == x2) cout << 0 << " " << y1 << " " << w << " " << y2;
    else cout << x1 << " " << 0 << " " << x2 << " " << h;
	return 0;
}
```

---

## 作者：zt17 (赞：3)

# P7031 题解

## 题目简介
给定一个矩形网格，在其中选择两个整数点，现求过网格边缘任意两点的一条直线分开两点（可以理解为与两点之间的线段相交），输出直线所经过两点的坐标。

## 思考过程

这道题其实是一个分类讨论题。我们可以分三类讨论：
1. $x_a = x_b,y_a \ne y_b$
![](https://cdn.luogu.com.cn/upload/image_hosting/6miai3ra.png)
这种情况我们可以选择点 $A$ 与点 $B$ 分别在矩形两边边上的射影（没听懂没关系，看下图）并连接。
![](https://cdn.luogu.com.cn/upload/image_hosting/46msurkh.png)
（在此图中，$D$ 是 $A$ 在直线 $GH$ 上的射影。同理，$C$ 是 $B$ 在 $EF$ 上的射影。）
2. $x_a \ne x_b,y_a = y_b$
![](https://cdn.luogu.com.cn/upload/image_hosting/xqyrhrvq.png)
同上，不过这次需要取的射影是在 $EH$ 和 $FG$ 上的，不再陈述，直接给图。
![](https://cdn.luogu.com.cn/upload/image_hosting/olhyonz1.png)
3. $x_a \ne x_b,y_a \ne y_b$
![](https://cdn.luogu.com.cn/upload/image_hosting/12um2nic.png)

虽然这种情况毫无特殊可言，但是我们要记住一句话：

> 任何的特殊情况，都可以通过正常情况推出结论。反之亦然。

我们再仔细观察这幅图，发现前两类的结论都对它生效！所以我们可以任选一种进行输出。
![](https://cdn.luogu.com.cn/upload/image_hosting/7x68kaay.png)

## 完整代码
```cpp
#include <iostream>
#define IOS cin.tie(0), ios::sync_with_stdio(false)
using namespace std;
typedef unsigned long long ull;
typedef pair<int, int> pii;


int main() 
{
    IOS;
    int n,m,x1,y1,x2,y2;
	cin >> n >> m >> x1 >> y1 >> x2 >> y2;
    if (x1 == x2) cout << 0 << " " << y1 << " " << n << " " << y2;
    else cout << x1 << " " << 0 << " " << x2 << " " << m; // 这里其实偷了个懒，将第三类的输出包含到第二类了
	return 0;
}
```

最优解第一页！ ~~管理大大求过QAQ~~

---

## 作者：_zhengzachary (赞：1)

这题其很简单，用到一个数学思想——分类讨论！

其实就两种：


1. $X_1 = X_2 \longrightarrow (0,Y_1)\rightarrow (N,Y_2)$

2. $X_1 \neq X_2 \longrightarrow (X_1,0)\rightarrow(X_2,M)$


不废话了，直接上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
  int n,m,_x,_y,__x,__y;
  cin >> n >> m >> _x >> _y >> __x >> __y;
  if (_x == __x) cout << 0 << " " << _y << " " << n << " " << __y;
  else cout << _x << " " << 0 << " " << __x << " " << m;
  return 0;
}
```

---

## 作者：Rookie_t (赞：1)

Step1：根据题意定义变量。

Step2：分析题目。

这是一道构造题，有两种情况：

第 $1$ 种，这两个点的横坐标相等，也就是  $x_1 = y_1$，我们就直接输出第一点的横坐标延长到最上方和第二点的横坐标延长到最下方相连。

第 $2$ 种，这两个点的横坐标不相等，也就是  $x_1 = y_1$，我们就直接输出第一点的纵坐标延长到最左边和第二点的纵坐标延长到最右边相连。

然后根据思路写代码即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,x1,y1_,x2,y2;
signed main(){
	ios::sync_with_stdio(false);
	cin>>a>>b>>x1>>y1_>>x2>>y2;
	if(x1 == x2){
		cout<<0<<' '<<y1_<<' '<<a<<' '<<y2;
	}
	else{
		cout<<x1<<' '<<0<<' '<<x2<<' '<<b;
	}
	return 0;
}
```

---

## 作者：mbzdf (赞：1)

# P7031 题解

[传送门](https://www.luogu.com.cn/problem/P7031)

## 题目大意
> 给你一个 $n \times m$ 的矩形，在矩形中有两个整点。请你找到一种方案将矩形划分成两个部分，每个部分中各有一个点。

## 分析一下

分别讨论当两个矩形内的点横坐标相同、不同，纵坐标相同、不同的情况，可以发现有多个答案，择一输出即可。

#### 那么具体思路呢

注意，这只是其中一种方法。

当两个点横坐标相同时，如图：
```text
.......
.......
.#..#..
.......
```
我们只需要从上往下切开即可，如图：
```text
..|....
..|....
.#|.#..
..|....
```
但是当两个点聚集在一起时，无法从中间切开，如图：

![当两个点聚集在一起时，无法从中间切开](https://cdn.luogu.com.cn/upload/image_hosting/q0jlrtg7.png)

我们只需要斜着切，如图：

![我们只需要斜着切](https://cdn.luogu.com.cn/upload/image_hosting/nl54osb7.png)

理解一下，在纵坐标不同时就能这么做。

而在纵坐标相同时呢？

我们想一下，只需要把整个矩形同时旋转 $90\degree$，就能转换成横坐标相同的情况。

## AC 代码
```cpp
#include <iostream>
using namespace std;
int n, m;
int ax, ay;
int bx, by;
int main()
{
	cin >> n >> m;
	cin >> ax >> ay;
	cin >> bx >> by;
	if(a.x == b.x)
		cout << 0 << ' ' << ay << ' ' << n << ' ' << by << ' ';
	else
		cout << ax << ' ' << 0 << ' ' << bx << ' ' << m;
}
```

---

## 作者：hujingbin27 (赞：1)

## 答题思路
这题就是个构造题，可以把所有的情况分为两种。一、竖轴坐标相等，可以在第一个点的最上端和第二个点的最下端连一条线；二、竖轴坐标不相等，可以在第一个点的最左端和第二个点的最右端连一条线。
## AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a,b,c,d,e,f;
	cin>>a>>b>>c>>d>>e>>f;
	if(d==f) cout<<c<<" "<<0<<" "<<e<<" "<<b;
	else cout<<0<<" "<<d<<" "<<a<<" "<<f;
}

```

---

## 作者：FarmarJohn (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/P7031)
### 分析
一道简单到不能再简单的构造题。对于这道题，我们需要考虑两个可能：

1. 这两个点的横坐标相等，我们就需要将第一个点的最上端和第二个点的最下端相连。

2. 这两个点的横坐标不相等，我们就需要将第一个点的最左端和第二个点的最右端相连。
### 代码
```cpp
#include<cstdio>
using namespace std;
int n,m,x1,y1,x2,y2;
int main()
{
	scanf("%d%d%d%d%d%d",&n,&m,&x1,&y1,&x2,&y2);
	if(x1==x2)printf("0 %d %d %d",y1,n,y2);
	else printf("%d 0 %d %d",x1,x2,m);
	return 0;
}
```

---

## 作者：Contain_Thunder (赞：0)

## 题目简述
有一块 $n \times m$ 的长方形蛋糕。蛋糕上有两个蜡烛，分别用 $(x_1,y_1)$ 和 $(x_2,y_2)$ 表示。现在有一把刀要把蛋糕切成两半，请问切入的终点和起点在哪？
## 思路
这道题分类讨论一下就会发现两个点分为两种情况。

第一种情况是竖着切。
![](https://cdn.luogu.com.cn/upload/image_hosting/u8b2j0lf.png)
第二种情况是横着切。
![](https://cdn.luogu.com.cn/upload/image_hosting/tn5tmisu.png)
知道两种情况之后再分别处理就行了。
### code
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	cin>>n>>m>>x>>y>>xx>>yy;
    if(x==xx) cout<<0<<" "<<y<<" "<<n<<" "<<yy;
    	else cout <<x<<" "<<0<<" "<<xx<<" "<<m; 
	return 0;
}
```


---

## 作者：_little_Cabbage_ (赞：0)

# P7031 [NWRRC2016] Anniversary Cake 题解
~~[博客食用体验更佳](https://www.luogu.com.cn/blog/958804/solution-p7031)~~

这是一道构造题。

我们可以分类讨论，如果第一个蜡烛与第二个蜡烛的 $x$ 坐标相等，那么就从第二个点所在 $x$ 轴的最左边切到第一个点所在 $x$ 轴的最右边。

否则，就从第二个点所在 $y$ 轴的最上面切到第一个点所在 $y$ 轴的最下面。

AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int p=1e9+7;
int main()
{
	int w,h,ax,ay,bx,by;
	cin>>w>>h>>ax>>ay>>bx>>by;
	if(ax==bx)
	{
		cout<<0<<" "<<ay<<" "<<w<<" "<<by;
	}
	else
	{
		cout<<ax<<" "<<0<<" "<<bx<<" "<<h;
	}
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/143060814)

---

## 作者：xAlec (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P7031)

# 思路

很简单的一道构造题，因为题目保证 $ x $ 坐标或 $ y $ 坐标必相等一个，只需要判断 $ x $ 坐标，$ y $ 坐标分别相等的情况，然后直接以两点所构成的长方形的对角线切割。（以这两点的连线为斜边分别作直角三角形）

# code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,xa,xb,ya,yb;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>xa>>ya>>xb>>yb;
	if(ya==yb)
		cout<<xa<<" "<<m<<" "<<xb<<" "<<0<<endl;//y坐标相等时，切割点的坐标（竖着的对角线）
	else
		cout<<0<<" "<<ya<<" "<<n<<" "<<yb<<endl;//x坐标相等时，切割点的坐标（横着的对角线）
	return 0;
}
```


---

## 作者：liruixiong0101 (赞：0)

## P1 题意：
给你一个 $h\times w$ 的矩形，在矩形中有两个点，你可以在矩形的四条边中选两个整点，连成一条线段将矩形分为两个部分。请你找到一种方案将矩形划分成两个部分，每个部分中各有一个点。

## P2 思路：
这是一道构造题，构造题的样例的输出大概率是误导你思路的，所以我们得自己想样例的输出。  
对于样例输入我们很快会想到一种切法：$(2,0)(3,3)$。  
转化成变量即：$(a_x,0)(b_x,h)$。

---
按照上述思路写的代码为下代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int w , h , ax , bx , ay , by;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0) , cout.tie(0);
	cin >> w >> h >> ax >> ay >> bx >> by;
	cout << ax << " 0 " << bx << " " << h;
	return 0;
}
```
不出意外得到了 WA#9 的~~好~~成绩。  
<https://www.luogu.com.cn/record/110967311>

---

为什么会 WA 呢？  
我们来想一想这个样例：$w=7,h=3,a_x=3,a_y=1,b_x=3,a_y=2$。  
由于这个样例的两个点的列相同，即 $a_x=b_x$。  
对于这样的样例我们可以想到他的答案与最前面的答案类似其实就是将矩形转 $90\degree$ 就变成了原来的图，这种情况的答案如下：$(0,ay)(w,by)$。

## P3 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int w , h , ax , bx , ay , by;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0) , cout.tie(0);
	cin >> w >> h >> ax >> ay >> bx >> by;
	if(ax == bx) cout << " 0 " << ay << " " << w << " " << by;//第二种情况。
	else cout << ax << " 0 " << bx << " " << h;//第一种情况。
	return 0;
}
```
<https://www.luogu.com.cn/record/110968801>

---

