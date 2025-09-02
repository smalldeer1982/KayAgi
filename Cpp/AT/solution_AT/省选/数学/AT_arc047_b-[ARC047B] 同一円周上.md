# [ARC047B] 同一円周上

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc047/tasks/arc047_b

座標平面上に $ N $ 個の点があります。

これらの点は全て、$ x $ 座標 と $ y $ 座標の値が共に整数です。つまり格子点上にあります。

そのうえ、これらの点は全て、ある点 $ P $ とのマンハッタン距離が同じであることがわかっています。ここで、マンハッタン距離とは、 $ 2 $ つの点の座標がそれぞれ $ (a,\ b),\ (c,\ d) $ であるとき、 $ |\ a-c\ |\ +\ |\ b-d\ | $ で計算される距離のことです。

そして、点 $ P $ も格子点上にあります。

点 $ P $ としてあり得る点を $ 1 $ つ挙げてください。

## 说明/提示

### Sample Explanation 1

与えられた点は全て点 $ (2,\ 3) $ からのマンハッタン距離が $ 2 $ です。

### Sample Explanation 2

$ y\ ≦\ 0 $ であるような点 $ (0,\ y) $ は全て、点 $ P $ としての条件を満たします。 この場合 $ -10^9\ ≦\ y $ であるかぎり、どれを出力しても構いません。

## 样例 #1

### 输入

```
3
1 2
3 4
2 5```

### 输出

```
2 3```

## 样例 #2

### 输入

```
3
0 1
1 0
-1 0```

### 输出

```
0 -2016```

# 题解

## 作者：SamHJD (赞：1)

先将曼哈顿距离转为切比雪夫距离，原坐标系上每个点的 $(x,y)$ 变为 $(x+y,x-y)$，此时原坐标系中两点的曼哈顿距离等于新坐标系中两点横纵坐标差的最大值。

  新坐标系中与某点切比雪夫距离相等的点在以该点为中心的正方形的边上，找出该正方形即可。所有点的纵坐标的最大值即为正方形上侧的边的纵坐标，最小值即为正方形下侧的边的纵坐标，左右侧的边同理，于是可以求出正方形的四个顶点，正方形的边长为所有点纵坐标极差和横坐标极差的最大值。
  
  不过会出现正方形的一侧或多侧没有点的情况（样例一），此时四个顶点可能构成一个矩形，但是四个顶点总有一个是正确的，分别以四个顶点求出正方形的中心判断是否为合法的解即可。

```cpp
#include <bits/stdc++.h>
#define rep(i,k,n) for(int i=k;i<=n;++i)
#define per(i,n,k) for(int i=n;i>=k;--i)
using namespace std;
template<typename T>
inline void read(T &x){
	x=0;int f=1;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(c-'0');
	x*=f;
}
const int N=1e5+10,INF=0x3f3f3f3f;
int minx=INF,miny=INF,maxx=-INF,maxy=-INF,n,px[N],py[N];
void ck(int X,int Y){
    int x=(X+Y)/2,y=(X-Y)/2;
    rep(i,1,n){
        int dis=abs(x-px[i])+abs(y-py[i]);
        if(dis!=abs(x-px[1])+abs(y-py[1])) return;
    }
    printf("%d %d\n",x,y);exit(0);
}
int main(){
    read(n);
    rep(i,1,n){
        read(px[i]);read(py[i]);
        int x=px[i]+py[i],y=px[i]-py[i];
        minx=min(minx,x);miny=min(miny,y);
        maxx=max(maxx,x);maxy=max(maxy,y);
    }
    int r=max(maxx-minx,maxy-miny)/2;
    ck(minx+r,miny+r);ck(minx+r,maxy-r);ck(maxx-r,miny+r);ck(maxx-r,maxy-r);
	return 0;
}
```

---

## 作者：xukehg (赞：0)

简单题。

曼哈顿距离的图像是一个菱形，不好刻画，于是我们把它放到切比雪夫坐标系上。很明显，最中在切比雪夫坐标系上存在一个以答案为正中心且所有点均在边上的正方形。

正方形的左边界一定过 $x$ 坐标最小的点，同理可得其他四个边的位置，于是可以求出正方形的边长的一半。从四个极点寻找对应的中心并判断是否合法即可。

[记录。](https://atcoder.jp/contests/arc047/submissions/59760921)

---

## 作者：Phobia (赞：0)

首先将题目中丑陋的曼哈顿距离转成切比雪夫距离。

容易发现，所有距离某个点切比雪夫距离相等的点都在一个正方形上，而题目保证有解，因此转化后的点必然都在某一个正方形上。

考虑确定正方形的上下左右的坐标，显然，答案就是正方形中间点的坐标。

小心！这样的点至多有四个，所以还得一一 check 过去。

时间复杂度 $\Theta(n)$。

~~~cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

const int maxn = 100005;

int n;

i64 l = 1e18, r = -1e18, d = 1e18, u = -1e18, x[maxn], y[maxn];

int read()
{
	int res = 0, f = 0, ch = getchar();
	for (; !isdigit(ch); ch = getchar())
		f = (ch == '-');
	for (; isdigit(ch); ch = getchar())
		res = (res << 3) + (res << 1) + (ch & 15);
	return f ? -res : res;
}

void check(i64 nx, i64 ny)
{
	i64 ansx = (nx + ny) / 2, ansy = (nx - ny) / 2;
	i64 dis = llabs(ansx - x[1]) + llabs(ansy - y[1]);
	for (int i = 2; i <= n; ++i)
	{
		if (llabs(ansx - x[i]) + llabs(ansy - y[i]) != dis)
			return;
	}
	printf("%lld %lld\n", ansx, ansy);
	exit(0); 
}

int main()
{
	n = read();
	for (int i = 1; i <= n; ++i)
	{
		x[i] = read(), y[i] = read();
		l = min(l, x[i] + y[i]);
		r = max(r, x[i] + y[i]);
		d = min(d, x[i] - y[i]);
		u = max(u, x[i] - y[i]); 
	}
	i64 w = max(r - l, u - d) / 2; 
	check(l + w, d + w);
	check(l + w, u - w);
	check(r - w, d + w);
	check(r - w, u - w);
	return 0;
}
~~~

---

