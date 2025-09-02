# [ABC178E] Dist Max

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc178/tasks/abc178_e

二次元平面上に $ N $ 個の点があり、$ i $ 番目の点の座標は $ (x_i,y_i) $ です。 同じ座標に複数の点があることもあります。 異なる二点間のマンハッタン距離として考えられる最大の値はいくつでしょうか。

ただし、二点 $ (x_i,y_i) $ と $ (x_j,y_j) $ のマンハッタン距離は $ |x_i-x_j|+|y_i-y_j| $ のことをいいます。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ x_i,y_i\ \leq\ 10^9 $
- 入力はすべて整数

### Sample Explanation 1

$ 1 $ 番目の点と $ 2 $ 番目の点のマンハッタン距離は $ |1-2|+|1-4|=4 $ で、これが最大です。

## 样例 #1

### 输入

```
3
1 1
2 4
3 2```

### 输出

```
4```

## 样例 #2

### 输入

```
2
1 1
1 1```

### 输出

```
0```

# 题解

## 作者：fish_love_cat (赞：4)

Upd：式子有个地方锅了，感谢 @[He_Jie](https://www.luogu.com.cn/user/1165951) 的提醒。

---

**前言：**

什么是[曼哈顿距离](https://baike.baidu.com/item/曼哈顿距离/743092)？

**思路：**

通过上面的链接可以知道，曼哈顿距离的公式就是 $d= | x1-x2  |+|y1-y2| $。

由上面那个公式又可以推导出，可能会出现如下四种情况：

 1. 当 $x1>x2$ 并且 $y1>y2$ 时，$d=(x1-x2)+(y1-y2)=(x1+y1)-(x2+y2)$。

 1. 当 $x1>x2$ 并且 $y1<y2$ 时，$d=(x1-x2)+(y2-y1)=(x1-y1)-(x2-y2)$。

 1. 当 $x1<x2$ 并且 $y1>y2$ 时，$d=(x2-x1)+(y1-y2)=(x2-y2)-(x1-y1)$。

 1. 当 $x1<x2$ 并且 $y1<y2$ 时，$d=(x2-x1)+(y2-y1)=(x2+y2)-(x1+y1)$。

观察上面的柿子可以发现，每一个答案都是横纵坐标想加或相减后的值的较大点减去较小点。

所以要使曼哈顿距离最大，就要让较大数尽量大，较小数尽量小。

那就把相加时的最大最小点和相减时的最大最小点求出来，然后把相减时的答案和相加时的答案去个较大值输出即可。

**代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
int mina=1000000000,minb=1000000000,maxa=-1000000000,maxb=-1000000000;//初值要大
int main(){
    int t;cin>>t;
    while(t--){
        int x,y;
        cin>>x>>y,maxa=max(maxa,x+y),maxb=max(maxb,x-y),mina=min(mina,x+y),minb=min(minb,x-y);//求点
    }
    cout<<max(maxa-mina,maxb-minb);//求答案
    return 0;
}
```

---

## 作者：qxs_ck (赞：2)

#### [原题传送门](https://www.luogu.com.cn/problem/AT_abc178_e)

### 思路：
题目要求 $N$ 个点之间最大的曼哈顿距离，判断这 $N\times N$ 个曼哈顿距离中最大的距离。

暴力判断过不了的。![](https://asset.gitblock.cn/Media?name=BAEE5420F92D6E387C3D2431B3AD6D57.png)

WA 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

long long nums[200005][2],n,max_;

int main(){
	cin>>n;
	for(int i=0;i<n;i++) cin>>nums[i][0]>>nums[i][1];
	for(int i=0;i<n;i++) for(int j=0;j<n;j++) max_=max(max_,abs(nums[i][0]-nums[j][0])+abs(nums[i][1]-nums[j][1]));
	cout<<max_;
}
```


我们得用更好的方法。

曼哈顿距离的定义是坐标系是沿线移动的距离，
![](https://asset.gitblock.cn/Media?name=4A255CAAB68DD45244D1761EA466726B.png)

距离为 $2+2=4$。

曼哈顿距离的公式是 $d=\mid x1-x2 \mid+\mid y1-y2 \mid$，可以推导出：
$$
d(x1,y1,x2,y2) = \begin{cases}
  x1>x2,y1>y2 & (x1+y1)-(x2+y2) \\
  x1>x2,y1<y2 & (x1-y1)-(x2-y2) \\
  x1<x2,y1>y2 & (x2-y2)-(x1-y1) \\
  x1<x2,y1<y2 & (x2+y2)-(x1+y1) \\
\end{cases}
$$

得出 $x+y$ 的最大值与最小值的差值或者$x-y$ 的最大值与最小值的差值是最大的曼哈顿距离，即可得出答案。

不用管 $(x1+y1)-(x2+y2)$ 和 $(x2+y2)-(x1+y1)$ 的区别，因为最大值减最小值的差值肯定为正数。
### AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

long long n,max_,a=-999999999,b=999999999,c=-999999999,d=999999999,xx,yy;

int main(){
	cin>>n;
	for(int i=0;i<n;i++){
        cin>>xx>>yy;
		a=max(a,xx+yy);
		b=min(b,xx+yy);
		c=max(c,xx-yy);
		d=min(d,xx-yy);
	}
	cout<<max(a-b,c-d);
}
```


---

## 作者：BLuemoon_ (赞：1)

[link](https://www.luogu.com.cn/problem/AT_abc178_e)

## 题意

平面直角坐标系的第一象限上有 $N$ 个点，求每两个点的曼哈顿距离的最大值。

曼哈顿距离：$(x_1,y_1)$ 和 $(x_2,y_2)$ 的曼哈顿距离是 $\lvert x_1-x_2 \rvert + \lvert y_1-y_2 \rvert$。

## 思路

不妨将坐标系顺时针旋转 $45$ 度。那么原来在 $(x,y)$ 位置的点来到了 $(x+y,x-y)$。令 $x+y=p,x-y=q$。

那么曼哈顿距离就变成了 $\max(\lvert p_1-p_2\rvert,\lvert q_1-q_2\rvert)$。

所以得到 $\max\{\lvert x_i-x_j \rvert + \lvert y_i-y_j \rvert\}=\max(\max\{p_i\}-\min\{p_i\},\max\{q_i\}-\min\{q_i\})$。

那么我们求出 $\max\{p_i\},\min\{p_i\},\max\{q_i\},\min\{q_i\}$。最后答案就出来了。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, x, y, maxx = INT_MIN, minx = INT_MAX, maxy = INT_MIN, miny = INT_MAX;

int main() {
    for (cin >> n; n; n--) {
        cin >> x >> y;
        int p = x + y, q = x - y;
        maxx = max(maxx, p), maxy = max(maxy, q);
        minx = min(minx, p), miny = min(miny, q);
    }
    cout << max(maxx - minx, maxy - miny) << '\n';
    return 0;
}
```

---

## 作者：GoodLuckCat (赞：0)

首先我们需要明白 [曼哈顿距离是什么？](https://zhuanlan.zhihu.com/p/393809007)

从这里我们可以知道曼哈顿距离指的是两个点在标准坐标系上的**绝对轴距总和**。

那已知两个点的坐标，怎么求两个点的曼哈顿距离呢？根据定义可以得出：曼哈顿距离用坐标表示就是 $|x_1-x_2|+|y_1-y_2|$。

把这个公式的所有情况枚举一下，得出结果只有两种情况：

1. 最大的 $x_i+y_i$ 减最小的 $x_i+y_i$。

2. 最大的 $x_i-y_i$ 减最小的 $x_i-y_i$。

答案就是这两种情况中最大的那一个。

因为题目要求取最大的，所以最后要用 $\max$。记得把 $a$、$b$、$c$、$d$ 都初始化。完整 C++ 代码如下：

```cpp
#include<iostream>
using namespace std;
int main()
{
    long long n,a,b,c,d,x,y;
    a=c=-999999999;b=d=-a;
    cin>>n;
    while(n--)
    {
        cin>>x>>y;
        if(x+y>a)a=x+y;
        if(x+y<b)b=x+y;
        if(x-y>c)c=x-y;
        if(x-y<d)d=x-y;
    }
    cout<<max(a-b,c-d);
}
```

---

## 作者：QWQ_jyc (赞：0)

既然题目中提到了曼哈顿距离，那让我们先来认识一下曼哈顿距离。

曼哈顿距离的定义为：用以标明两个点在标准坐标系上的**绝对轴距总和**。

类似下图的黄蓝两条线：

![](https://cdn.luogu.com.cn/upload/image_hosting/q5jop7mw.png)

公式为：

$d=|x_i-x_j|+|y_i-y_j|$

带回题目枚举后，便可以推出答案为: $\max_x{}_+{}_y-\min_x{}_+{}_y$ 或 $\max_x{}_-{}_y-\min_x{}_-{}_y$


再套入代码：

```
#include<bits/stdc++.h>
using namespace std;
long long n,s,a=-10e9,b=10e9,c=-10e9,d=10e9;
int main(){
	cin>>n;
    for(int i=1;i<=n;i++){
        long long x,y;
        cin>>x>>y;
        a=max(a,x+y);
        b=min(b,x+y);
        c=max(c,x-y);
        d=min(d,x-y);
    }
    s=max(a-b,c-d);
    cout<<s;
    return 0;
}
```


---

## 作者：nkrqzjc_zzz (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/AT_abc178_e)

------------

看到题解里还没有详细讲解**曼哈顿距离**的，本蒟蒻就来讲一讲。

首先，了解曼哈顿距离前，我们先了解一个与曼哈顿距离类似的欧几里得距离。

如下图，欧几里得距离就是**两点之间的直线距离**，也就是那根蓝色的线。

如何计算二维平面上的欧几里得距离呢？初中数学基础知识，利用勾股定理转换而来：

$d=\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$

而曼哈顿距离一般则有很多个，如下图橙色和绿色的线均是两点之间的曼哈顿距离。下面是曼哈顿距离的定义：用以标明两个点在标准坐标系上的绝对轴距总和。

计算两点之间的曼哈顿距离公式如下：

$d=|x_i-x_j|+|y_i-y_j|$

![](https://cdn.luogu.com.cn/upload/image_hosting/6axcftld.png)

理论知识学完了，我们来看问题。

要你求所有点对间的最大曼哈顿距离，所以我们可以先将曼哈顿距离公式内的情况一一枚举一遍，你就可以发现，所有的所有都与 $x_i+y_i$ 或 $x_i-y_i$ 有关。

所以简单推理就可以得到：答案就是最大的 $x_i+y_i$ 减去 最小的 $x_i+y_i$ 或者 最大的 $x_i-y_i$ 减去 最小的 $x_i-y_i$。

那么就愉快的结束了！


------------

### 代码

```
#include<bits/stdc++.h>
using namespace std;
int n,x,y,jia,jian,d_x=INT_MIN,x_x=INT_MAX,d_y=INT_MIN,x_y=INT_MAX;
//d_x为最大的xi+yi，x_x为最小的xi+yi
//d_y为最大的xi-yi，x_y为最小的xi-yi
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        scanf("%d%d",&x,&y);
        jia=x+y;
        jian=x-y;
        d_x=max(d_x,jia);
        x_x=min(x_x,jia);
        d_y=max(d_y,jian);
        x_y=min(x_y,jian);
    }
    printf("%d\n",max(d_x-x_x,d_y-x_y));
}
```

---

## 作者：zk_y (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc178_e)

这道题目让我们求出这些点的哈夫曼距离。

我们发现 $i$ 和 $j$ 是无序的，那么这里我们不妨假设 $X_i\le X_j$。

我们只针对两个点来排序就可以了：

第一种情况：$Y_i\le Y_j$，此时最大哈夫曼距离为 $X_j-X_i+Y_j-Y_i$，是 $max_{X+Y}-min_{X+Y}$。

第二种情况：$Y_i> Y_j$，此时最大哈夫曼距离为 $X_j-X_i-Y_j+Y_i$，是 $max_{X-Y}-min_{X-Y}$。

所以，我们只需要保存 $max_{X+Y}$，$min_{X+Y}$，$max_{X-Y}$，$min_{X-Y}$ 即可。

# AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=1<<30;
int n,a=-inf,b=inf,c=-inf,d=inf;
int main(){
	scanf("%d",&n);
    while(n--){
        int x,y;
        scanf("%d%d",&x,&y);
        a=max(a,x+y);
        b=min(b,x+y);
        c=max(c,x-y);
        d=min(d,x-y);
    }
    printf("%d\n",max(a-b,c-d));
    return 0;
}
```


---

## 作者：VitrelosTia (赞：0)

考虑两个点 $(x_1, y_1)$ 和 $(x_2, y_2)$，不妨设 $x_1 > x_2$，讨论 $y_1$ 和 $y_2$ 之间的关系。

当 $y_1 > y_2$ 时，他们的距离为 $x_1 - x_2 + y_1 - y_2$，由于要思考最大值，于是进一步化为 $(x_1 + y_1) - (x_2 + y_2)$，显然当 $x_1 + y_1$ 取最大，$x_2 + y_2$ 取最小时他们之间的距离最大。

当 $y_1 \le y_2$ 时，他们的距离为 $x_1 - x_2 - y_1 + y_2$，同上，进一步化为 $(x_1 + y_2) - (x_2 + y_1)$，显然当 $x_1 + y_2$ 取最大，$x_2 + y_1$ 取最小时他们之间的距离最大。

分别记录 $x_1 + y_1$ 的最大值（记为 $a$），$x_2 + y_2$ 的最小值（记为 $b$），$x_1 + y_2$ 的最大值（记为 $c$），$x_2 + y_1$ 的最小值（记为 $d$），最后算出 $\max(a - b, c - d)$ 即可。

```
void solve() {
	a = c = -INF;
	b = d =  INF;
    read(n);
    while (n--) {
    	int x, y;
    	read(x, y);
    	getmax(a, x + y);
    	getmin(b, x + y);
    	getmax(c, x - y);
    	getmin(d, x - y);
    }
    write(max(a - b, c - d));
}
```

---

## 作者：loser_seele (赞：0)

这题我尝试了平面最近点对的各种乱搞做法，但貌似没一个能过得去，如果有人乱搞过去了记得私信我。

证明过程参考官方题解。

首先一个经典的套路是看到曼哈顿距离，将整个坐标系旋转 $ 45 $ 度，得到坐标 $ (a+b,a-b) $，记为 $ w,z $，则 $ \mid x_i-x_j \mid+\mid y_i-y_j \mid=\max(\mid w_i-w_j \mid ,\mid z_i-z_j \mid )  $ 。

于是有 $ \max(\mid x_i-x_j \mid+\mid y_i-y_j \mid)=\max(\max\mid z_i-z_j\mid,\max\mid w_i-w_j \mid)=\max(\max{z_i}-\min{z_i},\max{w_i}-\min{w_i}) $。

其中 $ \max,\min $ 为前缀最大值和前缀最小值，显然前缀最小值和前缀最大值都可以 $ \mathcal{O}(1) $ 维护，所以在所有差值中取最大值即可，时间复杂度 $ \mathcal{O}(n) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
int ans=0,ansamax=-2e9,ansamin=2e9,ansbmax=-2e9,ansbmin=2e9;
int main()
{
    int n;
    cin>>n;
    while(n--)
    {
    	int x,y;
    	cin>>x>>y;
    	int a=x+y;
    	int b=x-y;
    	ansamax=max(ansamax,a);
    	ansbmax=max(ansbmax,b);
    	ansamin=min(ansamin,a);
    	ansbmin=min(ansbmin,b);
    	ans=max(ans,max(ansamax-ansamin,ansbmax-ansbmin));
    }
    cout<<ans;
}
```

update：提供一个来自别人的乱搞做法。

选取四个无穷大的顶点作为框框住所有点，计算距离框边缘最近的四个点之后答案大概率在这四个点之间，具体过程不会证明。可以通过。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace run{
int n;
const int N=2e5+10,inf=2e9+9;
int x[N],y[N];
int dist(int x1,int y1,int x2,int y2){
  int r=abs(x2-x1),c=abs(y2-y1);
  return r+c;
}
void man(){
  int c;
  cin>>c;
  int n=inf,m=-inf;
  for(int i=1;i<=c;i++)
    cin>>x[i]>>y[i];
  int x1=x[1],y1=y[1];
  int x2=x[1],y2=y[1];
  int x3=x[1],y3=y[1];
  int x4=x[1],y4=y[1];
  for(int i=1;i<=c;i++){
    int d11=dist(m,m,x1,y1);
    int d12=dist(m,n,x2,y2);
    int d13=dist(n,m,x3,y3);
    int d14=dist(n,n,x4,y4);
    int d2=dist(m,m,x[i],y[i]);
    if(d2<d11)x1=x[i],y1=y[i];
    d2=dist(m,n,x[i],y[i]);
    if(d2<d12)x2=x[i],y2=y[i];
    d2=dist(n,m,x[i],y[i]);
    if(d2<d13)x3=x[i],y3=y[i];
    d2=dist(n,n,x[i],y[i]);
    if(d2<d14)x4=x[i],y4=y[i];
  }
  pair<int,int>a[4];
  a[0]=make_pair(x1,y1);
  a[1]=make_pair(x2,y2);
  a[2]=make_pair(x3,y3);
  a[3]=make_pair(x4,y4);
  int mx=0;
  for(int i=0;i<4;i++)
    for(int j=i+1;j<4;j++)
      mx=max(mx,dist(a[i].first,a[i].second,a[j].first,a[j].second));
  cout<<mx<<'\n';
}
}
signed main(){run::man();}
```


---

## 作者：Nuclear_Fish_cyq (赞：0)

我们先考虑两个点 $(x_1, y_1)$ 和 $(x_2, y_2)$。这里为了方便起见，设 $x_1\leq x_2$。我们依照公式，可以求出它们的曼哈顿距离为 $x_1-x_2+|y_1-y_2|$。这个绝对值太难看了，不方便我们找规律，所以我们分类讨论，距离为

$$\begin{cases}
x_1-x_2+y_1-y_2  & \text{ if } y_1\geq y_2 \\
x_1-x_2+y_2-y_1  & \text{ if } y_1<y_2
\end{cases}$$

可是这个式子的结构还没有太明显，我们再整理一下：

$$\begin{cases}
(x_1+y_2)-(x_2+y_2)  & \text{ if } y_1\geq y_2 \\
(x_1-y_1)-(x_2-y_2)  & \text{ if } y_1<y_2
\end{cases}$$

这样就非常明显了。我们维护最大、最小的 $x+y$ 和最大、最小的 $x-y$，答案就是 $\max(\max_{x+y}-\min_{x+y},\max_{x-y}-\min_{x-y})$。

上代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
#define db double
#define ull unsigned long long
#define inf INT_MAX
#define linf LLONG_MAX
#define ninf INT_MIN
#define nlinf LLONG_MIN
//#define mod
//#define range
using namespace std;
int n, a, b, mxs = ninf, mxd = ninf, mns = inf, mnd = inf;

int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for(int i = 0; i < n; i++){
		cin >> a >> b;
		mxs = max(mxs, a + b);
		mxd = max(mxd, a - b);
		mns = min(mns, a + b);
		mnd = min(mnd, a - b);
	}
	cout << max(mxs - mns, mxd - mnd) << endl;
	return 0;
}
```

---

## 作者：Lyw_and_Segment_Tree (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/AT_abc178_e)
## 题意简述
> 给定 $n$ 个点，求出其中两点间最大**曼哈顿距离**。

## 开始解题！
先亮出曼哈顿距离的公式：
$$c=|x_1-x_2|+|y_1-y_2|$$  
然后对于上述式子，我们分4种情况考虑：
1. $x_1 - x_2 \ge 0 , y_1 - y_2  \ge 0$ ，则得出式子： $(x_1 + y_1) - (x_2 + y_2)$  
2. $x_1 - x_2 < 0 , y_1 - y_2  \ge 0$ ，则得出式子： $(x_2 - y_2) - (x_1 - y_1)$  
3. $ x_1-x_2 \ge 0 , y_1 - y_2 <  0$ ，则得出式子： $(x_1 - y_1) - (x_2-y_2)$   
4. $x_1 - x_2 < 0 , y_1 - y_2 < 0$ ，则得出式子： $(x_2 + y_2) - (x_1 + y_1)$ 

归纳得其最大距离应为：
$$\max(\max(x_i + y_i) - \min(x_i + y_i) , \max(x_i - y_i) - \min(x_i - y_i))$$  
由于要求最大距离，所以两点间的距离越大越好。根据上述所有结论，可得代码如下：
## AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int Min=-1e9;
int a=Min,b=-Min,c=Min,d=-Min;
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        int x,y;
        cin>>x>>y;
        a=max(a,x+y);
        b=min(b,x+y);
        c=max(c,x-y);
        d=min(d,x-y);
    }
    cout<<max(a-b,c-d)<<endl;
}
```

---

