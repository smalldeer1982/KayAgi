# Hidden Fortress

## 题目描述

This is an interactive problem!

As part of your contribution in the Great Bubble War, you have been tasked with finding the newly built enemy fortress. The world you live in is a giant $ 10^9 \times 10^9 $ grid, with squares having both coordinates between $ 1 $ and $ 10^9 $ .

You know that the enemy base has the shape of a rectangle, with the sides parallel to the sides of the grid. The people of your world are extremely scared of being at the edge of the world, so you know that the base doesn't contain any of the squares on the edges of the grid (the $ x $ or $ y $ coordinate being $ 1 $ or $ 10^9 $ ).

To help you locate the base, you have been given a device that you can place in any square of the grid, and it will tell you the manhattan distance to the closest square of the base. The manhattan distance from square $ (a, b) $ to square $ (p, q) $ is calculated as $ |a−p|+|b−q| $ . If you try to place the device inside the enemy base, you will be captured by the enemy. Because of this, you need to make sure to never place the device inside the enemy base.

Unfortunately, the device is powered by a battery and you can't recharge it. This means that you can use the device at most $ 40 $ times.

## 样例 #1

### 输入

```
1
1
2
1```

### 输出

```
? 2 2
? 5 5
? 4 7
? 1 5
! 2 3 4 5```

# 题解

## 作者：shi_kan (赞：11)

提供一个 $4$ 次询问的简单做法（被 $40$ 次限制忽悠了）：

首先我们设区域离各边界的距离为 $u,d,l,r$，那么询问三个角得到 $ul,ur,dl$。

![](https://cdn.luogu.com.cn/upload/image_hosting/c5rodc3g.png)

然后观察到询问函数 $ask(1,x)$ 是一个特殊的倒梯形（理解意思就行），且斜边角度为 $45 \degree$，如下图：


![](https://cdn.luogu.com.cn/upload/image_hosting/6v0xbgof.png)

那么我们只要试着找到两个返回值相等的询问 $(1,ql),(1,qr)$，令 $mid = \frac{ql + qr}{2}$，$ask(1,mid)$ 就一定在区域正上方，返回 $u$ 的值。

![](https://cdn.luogu.com.cn/upload/image_hosting/6dxys9qj.png)

找一对 $<ql,qr>$ 不难，利用 $ul$ 与 $ur$ 的差值即可，即:

 $$ql = 1,qr = 10^9 + ul - ur$$
 
![](https://cdn.luogu.com.cn/upload/image_hosting/e96j3iyf.png)

最后根据 $ul,ur,dl$ 与 $u$ 分别算出 $d,l,r$ 即可。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define lim 1000000000ll
int ask(int x,int y)
{
    int res;
    cout<<"? "<<x<<" "<<y<<endl;
    cin>>res;
    return res;
}
void work()
{
    int ul = ask(1,1),ur = ask(1,lim),dl = ask(lim,1);
    int u = ask(1,(1 + lim + ul - ur) / 2),r = ur - u,l = ul - u,d = dl - l;
    cout<<"! "<<1 + u<<" "<<1 + l<<" "<<lim - d<<" "<<lim - r<<endl;
}
signed main()
{
    ios::sync_with_stdio(false);

    work();

    return 0;
}
```


---

## 作者：xh39 (赞：2)

先发一篇通过 $7$ 次询问获得答案的方法。感觉还能优化。以后想到了新算法再更新。

基础:平面直角坐标系(否则题目都看不懂)，有基本的几何知识(本题需要用到等腰直角三角形和矩形(长方形)的性质)。学完了整数(int)的定义和输入(cin/scanf)输出(cout/printf)。

为方便题解叙述，有些地方将会用到函数。
## 题目大意

有一个矩形，四条边都平行于坐标轴。其中任意一点的范围都在开区间 $(1,10^9)$ 范围内。且顶点为整点。

每次询问可以选择一个矩形外的整点并得知与矩形的最近曼哈顿距离(即只走平行于坐标轴的路线到达矩形)。

最多用 $40$ 次询问猜出矩形。选择的点的 $x,y$ 值应均在闭区间 $[1,10^9]$ 内。

## $12$ 次询问
先假设边界在 $[0,10^9]$ 。最后询问出来的结果加一即可。

**(保证询问合法)** 只能选取矩形外的点，而它的坐标范围又是开区间。取不到 $0$ 和 $10^9$，那么选取这些地方一定不会选在矩形内。

先考虑查询出矩形底端的 $y$ 轴。

先来看一张图,图中的下边界就是 $x$ 轴。红色数字表示它与矩形的距离。

![](https://cdn.luogu.com.cn/upload/image_hosting/oxrxaz8s.png)

可以发现,距离一定是由三段斜率分别为 $-1,0,1$ 的一次函数构成。形如下图:

![](https://cdn.luogu.com.cn/upload/image_hosting/lsrcnwp5.png)

证明过程不难,列式子推就可以了。

**(求出底端距离)** 发现下面那一段平(斜率为 $0$)的就是矩形底端到 $x$ 轴的距离。现在只要**找出底端线段上的一个整点**就可以通过一次询问知道矩形底端到 $x$ 轴的距离。

找单峰函数的底端需要用到三分。但是会TLE(后续还需要进行其它询问)。

**(寻找函数特殊规律)** 发现这个函数的第一段和第三段斜率是一样的。因此**将其延长，交点的 $x$ 坐标一定是它们终点 $x$ 坐标的平均值。**(如下图)

![](https://cdn.luogu.com.cn/upload/image_hosting/rfmdki4t.png)

现在的问题就是如何找到这个平均值。

**(调整到同一水平高度)** 任意的两点,如果水平高度相同，那么它们 $x$ 坐标的平均值恰好就是我们要求的平均值。可以用等腰直角三角形的一些性质来证明。

由于斜率已知,我们很容易根据 $y$ 坐标差值算出 $x$ 坐标差值，从而得到 $x$ 坐标，算它们的平均数就很容易了。如下图:

![](https://cdn.luogu.com.cn/upload/image_hosting/ryu7f462.png)

如果平均值不是整数，那么它向上取整或向下取整都是可以的。

为保证每次查询的两个点一定分别在第一段和第三段，那么第一个点选为 $(0,0)$，第二个点选为 $(0,10^{9})$。

然后查询左端距 $y$ 轴的距离，上端到边界(直线 $y=10^9$ )，右端到边界(直线 $x=10^9$)

## $8$ 次询问
其实这个比 $12$ 次还好实现些。

**(避免重复询问)** 发现有$(0,0),(0,10^9),(10^9,0),(10^9,10^9)$ 这 $4$ 个点实际上重复询问了一次。所以可以一开始就询问这 $4$ 个点来实现预处理。

代码:
```cpp
#include<iostream>
#include<cmath>
using namespace std;
#define N 1000000000 //表示边界10^9
int Q(int x,int y){ //处理一次询问。
	int ans;
	cout<<"? "<<x<<" "<<y<<endl;
	cin>>ans;
	return ans;
}
int main(){
	int ans0,ans1,ans2,ans3,disl,disr,disd,disu;
	ans0=Q(1,N); //预处理4个角。
	ans1=Q(N,N);
	ans2=Q(1,1);
	ans3=Q(N,1);
	disd=Q((N-(ans3-ans2)+1)/2,1); //求出底端距离。
	disl=Q(1,(N-(ans0-ans2)+1)/2); //求出左端距离。
	disu=Q((N-(ans1-ans0)+1)/2,N); //求出顶端距离。
	disr=Q(N,(N-(ans1-ans3)+1)/2); //求出右端距离。
	cout<<"! "<<disl+1<<" "<<disd+1<<" "<<N-disr<<" "<<N-disu<<endl; //disl和disd要加一。因为在本篇题解中左边界和下边界是被认作是0。
	return 0;
}
```
## $7$ 次询问
以上算法足以通过本题。但还是可以继续优化。

由于矩形平行于坐标轴，所以如果一个点在底端一定存在一个 $x$ 轴与它相同的点在顶端。如下图:

![](https://cdn.luogu.com.cn/upload/image_hosting/l5cc7d3d.png)

同理,如果一个点在左端一定存在一个 $y$ 轴与它相同的点在右端。

因此可以将代码改为(仅展示核心代码):
```cpp
	disd=Q((N-(ans3-ans2)+1)/2,1);
	disl=Q(1,(N-(ans0-ans2)+1)/2);
	disu=Q((N-(ans3-ans2)+1)/2,N);
	disr=Q(N,(N-(ans0-ans2)+1)/2);
```
现在不需要用到 ```ans1``` 了。所以就少了一次询问。

---

## 作者：ziyistudy (赞：1)

看到很多是用二分的解法，这题其实可以这用 **$4$** 次查询得到结果。

我们只需要用两次查询就可以找到地方基地矩阵的一条边的中点。

先询问 $d1=query(1,1)$ 和 $d2=query(1,10^9)$。

就可以求出 $y_m=\frac{1+10^9+d1-d2}{2}$。

之后再询问 $d3=query(10^9,1)$ 和 $d4=query(1,y_m)$。

那么我们就可以算出答案。

- $sx=1+d4$
- $sy=1+d1-d4$
- $ex=10^9-d3+d1-d4$
- $ey=10^9-d2+d4$

不理解的可以手退一下，会发现一些边抵消之后就是答案。

---

## 作者：FjswYuzu (赞：0)

注意到边界上不能为基地格，我们定义一个函数 $f(x)$ 表示点 $(1,x)$ 到基地的最短曼哈顿距离，发现这个函数有一段是单调递减，满足 $f(x) - f(x-1) = -1$，然后又有一段满足 $f(x)=f(x-1)$（可能有），然后又有一段满足 $f(x) - f(x-1) = 1$。当然我们不需要管这些，因为我们知道了有一段单调递减，并且这个折点一定是基地的边界所在。根据 $f(x) - f(x-1) = -1$，即 $f(1) - f(x) = x-1$ 的性质，直接二分就可以找到这个点。

然后用 $(1,10^9),(10^9,10^9)$ 两次查询就可以确定基地了。

```cpp
#include<bits/stdc++.h>
#define F fflush(stdout)
using namespace std;
int main(){
	int L,R;
	puts("? 1 1");
	F;
	scanf("%d",&L);
	puts("? 1 1000000000");
	F;
	scanf("%d",&R);
	int l=1,r=1000000000,pos=1,dis=0;
	while(l<=r)
	{	
		int mid=(l+r)>>1;
		int x;
		printf("? 1 %d\n",mid),F;
		scanf("%d",&x);
		if(mid-1==L-x)	pos=mid,dis=x,l=mid+1;
		else	r=mid-1;
	}
	int xp,yp,xq,yq;
	xp=1+dis;
	yp=pos;
	R-=dis;
	yq=1000000000-R;
	printf("? 1000000000 %d\n",yq),F;
	int x;
	scanf("%d",&x);
	xq=1000000000-x;
	printf("! %d %d %d %d\n",xp,yp,xq,yq),F;
	return 0;
}
```

---

