# Mr. Bender and Square

## 题目描述

Mr. Bender has a digital table of size $ n×n $ , each cell can be switched on or off. He wants the field to have at least $ c $ switched on squares. When this condition is fulfilled, Mr Bender will be happy.

We'll consider the table rows numbered from top to bottom from 1 to $ n $ , and the columns — numbered from left to right from 1 to $ n $ . Initially there is exactly one switched on cell with coordinates $ (x,y) $ ( $ x $ is the row number, $ y $ is the column number), and all other cells are switched off. Then each second we switch on the cells that are off but have the side-adjacent cells that are on.

For a cell with coordinates $ (x,y) $ the side-adjacent cells are cells with coordinates $ (x-1,y) $ , $ (x+1,y) $ , $ (x,y-1) $ , $ (x,y+1) $ .

In how many seconds will Mr. Bender get happy?

## 说明/提示

Initially the first test has one painted cell, so the answer is 0. In the second test all events will go as is shown on the figure. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF255D/b709c1aa5b91b7af907cf3f3ca10b895a1b76650.png).

## 样例 #1

### 输入

```
6 4 3 1
```

### 输出

```
0
```

## 样例 #2

### 输入

```
9 3 8 10
```

### 输出

```
2
```

# 题解

## 作者：LYR_ (赞：5)

$\text{Update}\ 2021/8/2 :$ 美化表格，修改图片，~~有重大更新~~     
$\text{Update}\ 2022/4/9 :$ 发现图片中的例子没有解释清楚，改一下

[在洛谷查看题目](https://www.luogu.com.cn/problem/CF255D)  |  [在CF查看题目](http://codeforces.com/problemset/problem/255/D)    
# 翻译 
给出一个 $n\times n$ 的正方形和一个点的坐标（$x$ , $y$），从这个点每秒可以向外扩散四个点，即 $(x+1,y)$,$(x-1,y)$,$(x,y+1)$,$(x,y-1)$ ,求需要多少秒才能大于或等于面积 $c$。
# 思路  
如果将这个点看作是在无限大的正方形上扩散，那么我们可以得出：  

| 扩散时间 | 点的数量 |
| :----------: | :----------: |
| 0 | 1 |
| 1 | 5 |
| 2 | 13 |


于是，为了得出扩散时间和点的数量的关系，设一个二次函数为 $y=ax^2+bx+c$ 。（ $x$ 为扩散时间， $y$ 为点的数量）  
将上表的数据带入二次函数就得到了一个三元一次方程，图片如下：  

![](https://cdn.luogu.com.cn/upload/image_hosting/hft8bny4.png)
 
$\therefore\ y=2x^2+2x+1$   


现在我们开始考虑边缘阻挡了的点的数量。
不难发现，在边缘以外需要减去的点组成了一个像金字塔一样的三角形（第一层有 $1$ 个，第二层有 $3$ 个 ……），图片如下：

注：黑色边框区域为题目所给定的正方形，红色边框区域为扩散出正方形的区域

![](https://cdn.luogu.com.cn/upload/image_hosting/74209em9.png)

这个图片的扩散时间为 $3$ ，蓝色区域代表点，红色边框在 $3\times 3$ 的正方形边缘外，绿色圆圈圈出的三角形即为突出部分。  
提供一下小学奥数的知识：   
$1+3+5+...+2n-1=n^2$
因此，就可以得出突出部分的点数，其他几个边也一样。


然后，你会发现突出部分有重叠，如下图绿圈部分：

![](https://cdn.luogu.com.cn/upload/image_hosting/7ty1nwh0.png)

多次画图后，发现：重叠部分是个每层点数相差1的三角形，于是就可以用高斯求和 $(1+2+3+...+n=\frac{(1+n)n}{2})$ 算出重叠部分点数。     

所以**总的点数=忽略边缘时的点数-四边突出的点数+重叠部分的点数**。   
注："+重叠部分"的点数是根据容斥原理


有了公式，就可以二分查找答案了！

# 代码
二分答案注意边界即可     
```cpp

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF=1e9+10;
ll n,x,y,c; 
int main() {
	cin>>n>>x>>y>>c;
	x--;y--;
	ll l=0,r=2*n+1,ans=INF;
	while(l<=r) {
		ll mid=(l+r)/2;
		ll s=2*mid*mid+2*mid+1; //忽略边界的点数
		if(mid-x>0) s-=(mid-x)*(mid-x); //上边突出部分
		if(mid-(n-1-x)>0) s-=(mid-(n-1-x))*(mid-(n-1-x)); //下边突出部分
		if(mid-y>0) s-=(mid-y)*(mid-y); //左边突出部分
		if(mid-(n-1-y)>0) s-=(mid-(n-1-y))*(mid-(n-1-y)); //右边突出部分
		
		if(mid-x-(n-y-1)-1>0) s+=(1+mid-x-(n-y-1)-1)*(mid-x-(n-y-1)-1)/2; //右上重叠部分
		if(mid-(n-1-x)-(n-1-y)>0) s+=(1+mid-(n-1-x)-(n-1-y)-1)*(mid-(n-1-x)-(n-1-y)-1)/2; //右下重叠部分
		if(mid-(n-1-x)-y-1>0) s+=(1+mid-(n-1-x)-y-1)*(mid-(n-1-x)-y-1)/2; //左下重叠部分
		if(mid-y-x-1>0) s+=(1+mid-y-x-1)*(mid-y-x-1)/2; //左上重叠部分

		if(s>=c) {
			r=mid-1;
			ans=min(mid,ans);
		}
		else {
			l=mid+1;
		}
	}
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：tallnut (赞：1)

挺好的一道二分加推式子题，~~非常毒瘤。~~
# 题意简述
在一个 $n \times n$ 的矩阵内做以下操作：每秒钟把每个点向上下左右各扩展一个点，但不能出边界。求至少多少秒后面积能 $\ge c$。
# 思路
## step 0
以下内容均基于：
- $x$ 和 $y$ 为原来的 $x$ 和 $y$ 减去 $1$（为了方便说）。
- 当前为第 $a$ 秒。

## step 1
我们先假设没有边界，可以自由扩展。

摆一张图供参考：

![](https://cdn.luogu.com.cn/upload/image_hosting/66plljzf.png)

其中，一个格子上的数字表示是在第几秒扩展到该点。

我们发现，第一行有 $1$ 个元素，第二行 $3$ 个，第三行 $5$ 个，第四行 $3$ 个，第五行 $1$ 个。

也就是：
$$1+3+\cdots+(2n+1)+(2n-1)+\cdots+1$$
我们可以把它拆成两个柿子：
$$1+3+\cdots+(2n+1)$$
和
$$(2n-1)+(2n-3)+\cdots+1$$
众所周知，等差数列公式为：
$$\frac{(\text{首项}+\text{末项})\times\text{项数}}{2}$$
所以第一个柿子为：
$$\frac{(1+(2n+1))\times(n+1)}{2}=n^2+2n+1$$
第二个：
$$\frac{((2n-1)+1)\times n}{2}=n^2$$
至此，我们终于推出了最终柿子：
$$2n^2+2n+1$$
## step 2
然而这显然是不够的。由于边界问题，我们需要减去“边角料”。

还是摆一张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/mbw9zsg3.png)

其中灰色的部分表示原矩形，彩色框表示不同方向的溢出。可以发现有一些重复的部分，在 step 3 中再说。

我们先研究黄色框。

如果 $a\le n$ 的话根本不会向上溢出，就不用考虑。

否则记 $a-n=b$（例如，在黄色框中 $b=3$）。第一层有 $1$ 个元素，第二层 $3$ 个，第三层 $5$ 个。同样的推导过程，
$$1+3+\cdots+(2b-1)=\frac{(1+(2b-1))\times b}{2}=b^2$$
在其他颜色的框中同理，只不过 $b$ 的柿子要变一下。
## step 3
在 step 2 的图中，我们会发现黄色和橙色框有重合部分，橙色和红色也有。这些重合的部分被减了两次，而实际上只需要减一次，所以需要把他们加回来。

在 step 2 的图中观察，可以发现重合部分是一个等腰三角形。设边长为 $b$，则面积为 $\dfrac{b\times(b+1)}{2}$。

我们先研究右上部分。则 $n=3,x=1,y=2,b=2$。~~大胆猜测+画更多图~~，可得 $b=a-n+y-x$。

同样地推理出左上、左下、右下的部分。
## step 4
套上二分模板即可。
# AC 代码
说了这么多，终于可以 AC 了。[AC 记录](https://www.luogu.com.cn/record/139578971)，代码中有注释。
```
#include <iostream>
using namespace std;
long long n,x,y,c,l,r,mid,ans;
//计算n^2
inline long long sq(long long a) { return a * a; }
//计算n(n+1)/2
inline long long tri(long long a) { return (a * (a + 1)) >> 1; }
bool check()
{
	unsigned long long area = ((mid * mid) << 1) + (mid << 1) + 1;
	//向上溢出
	if (mid > x) area -= sq(mid - x);
	//向下溢出
	if (mid + x + 1 > n) area -= sq(mid + x + 1 - n);
	//向左溢出
	if (mid > y) area -= sq(mid - y);
	//向右溢出
	if (mid + y + 1 > n) area -= sq(mid + y + 1 - n);
	//左和上的溢出部分的重叠
	if (mid > x + y + 1) area += tri(mid - x - y - 1);
	//左和下的溢出部分的重叠
	if (mid > n - x + y) area += tri(mid - n + x - y);
	//右和上的溢出部分的重叠
	if (mid > n - y + x) area += tri(mid - n + y - x);
	//右和下的溢出部分的重叠
	if (mid > (n << 1) - x - y - 1) area += tri(mid - (n << 1) + x + y + 1);
	return (area >= c);
}
int main()
{
	cin >> n >> x >> y >> c;
	x--;
	y--;
	l = 0;
	r = 1e9;
	while (l <= r)
	{
		mid = (l + r) >> 1;
		if (check())
		{
			ans = mid;
			r = mid - 1;
		}
		else l = mid + 1;
	}
	cout << ans;
}
```

---

