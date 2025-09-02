# Playing the ball

## 题目描述

A coder cannot sit and code all day. Sometimes it is a good idea to rise from the desk, have a rest, have small talk with colleagues and even play. The coders of the F company have their favorite ball game.

Let's imagine the game on the plane with a cartesian coordinate system. The point (0, 0) contains the player who chooses an arbitrary direction and throws a ball in that direction. The ball hits the plane at distance $ d $ from the player's original position and continues flying in the same direction. After the ball hits the plane for the first time, it flies on and hits the plane again at distance $ 2·d $ from the player's original position and so on (it continue flying in the chosen direction and hitting the plane after each $ d $ units). All coders in the F company are strong, so the ball flies infinitely far away.

The plane has $ n $ circles painted on it. If a ball hits the plane and hits a circle that is painted on the plane (including its border), then the player gets one point. The ball can hit multiple circles at once and get one point for each of them (if the ball hits some circle $ x $ times during the move, the player also gets $ x $ points). Count the maximum number of points a player can get if he throws a ball in the arbitrary direction. Note that the direction may have real cooridinates.

## 样例 #1

### 输入

```
2 5
1 1 1
5 0 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 5
4 0 3
5 3 1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
1 10
20 0 10
```

### 输出

```
3
```

# 题解

## 作者：Thunder_S (赞：0)

## Solution

有一个自然且正确的想法就是求出半径为 $kd$ 的同心圆与给的圆的交点，然后排序。由于答案只会在交点处修改，那么就类似扫描线的扫一遍就可以了。

这个想法可以稍微优化一下。我们不求交点，求角度。因为 C++ 内置了三角和反三角函数。我们可以用 `atan2` 求出方位角，再用 `acos` 和余弦定理求出偏转的角度，注意处理一下超过 $2\pi$ 的角。接下来就是基础的扫描线操作。

## Code
```cpp
#include<cmath>
#include<cstdio>
#include<algorithm>
#define N 20005
#define pi 3.1415926
#define eps 1e-8
#define db double
using namespace std;
int n,d,num,ans,res;
db l[N*20],r[N*20];
struct circ{db x,y,r;}a[N];
int main()
{
    scanf("%d%d",&n,&d);
    for (int i=1;i<=n;++i)
        scanf("%lf%lf%lf",&a[i].x,&a[i].y,&a[i].r);
    for (int i=1;i<=n;++i)
    {
        db dis=sqrt(a[i].x*a[i].x+a[i].y*a[i].y);
        int st=ceil((dis-a[i].r)/d),ed=floor((dis+a[i].r)/d);
        db theta=atan2(a[i].y,a[i].x);
        if (theta<0) theta+=2*pi;
        for (int j=st;j<=ed;++j)
        {
            int x=d*j;
            db tta=acos((dis*dis+x*x-a[i].r*a[i].r)/(2*dis*x));
            db t1=theta-tta,t2=theta+tta;
            if (t2>=2*pi) t2-=2*pi,res++;
            l[++num]=t1;r[num]=t2;
        }
    }
    sort(l+1,l+num+1);sort(r+1,r+num+1);
    ans=res;
    for (int i=1,j=1;i<=num;)
    {
        db now=l[i];
        for (;i<=num&&abs(l[i]-now)<eps;++i) ++res;
        for (;j<=num&&r[j]<now;++j) --res;
        if (res>ans) ans=res; 
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：Jayun (赞：0)

## 题目大意

在平面直角坐标系中，有 $n$ 个圆。需要找到一个方向，使得从原点按该方向射出的一条射线，每隔距离 $d$ 为一个点，这些点落在圆的个数最大（同一个圆可以贡献多次）。

$n\leq2\times10^4,5\leq d\leq10.$

## 思路

考虑一个圆被以原点为圆心、半径为 $k\cdot d$ 的若干个圆交。如下图。

![Figure 1](https://cdn.luogu.com.cn/upload/image_hosting/9xybgrmt.png)

发现每一个在圆内的弧线的贡献都是 $1$，那么就把弧区间化：把每个弧与圆的两个交点与 $x$ 轴的弧度求出来（即把点转到极角坐标，取其弧度），然后差分即可。

至于弧度的求法，先用反正切求出圆心的弧度 $\alpha$，见下图：

![Figure 2](https://cdn.luogu.com.cn/upload/image_hosting/zl6tsy9r.png)

由于 $R,l,r$ 已知，显然可以用余弦定理求得 $\cos\theta=\dfrac{R^2+l^2-r^2}{2Rl}$，用反余弦就可以求 $\theta$ 了，那么弧度的区间就是 $[\alpha-\theta,\alpha+\theta]$，**注意**判断 $2\pi$ 边界情况。

## 代码

```cpp
const int N = 2e4 + 10;
const long double pi = acos(-1), eps = 1e-5;

inline ll Read() {
	ll x = 0, f = 1;
	char c = getchar();
	while (c != '-' && (c < '0' || c > '9')) c = getchar();
	if (c == '-') f = -f, c = getchar();
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + c - '0', c = getchar();
	return x * f;
}

namespace Main {
	
	int n, d, cnt;
	
	long double rL[N * 10], rR[N * 10];
	
	inline long double Abs(long double a) { return a < 0? -a: a; }
	
	inline void addRange(long double l, long double r) {
		rL[++cnt] = l, rR[cnt] = r;
	}
	
	void Work (int R, int x, int y, int r, long double alpha, long double l) {
		long double theta = acos((R * R + x * x + y * y - r * r) * 1.0 / (2 * R * l));
		if (alpha - theta < eps) {
			addRange(alpha - theta + 2 * pi, 2 * pi - eps);
			addRange(0, alpha + theta);
		} else if (2 * pi - (alpha + theta) < eps) {
			addRange(alpha - theta, 2 * pi);
			addRange(eps, alpha + theta - 2 * pi);
		} else addRange(alpha - theta, alpha + theta);
	}
	
	int main () {
		n = Read(), d = Read();
		for (int i = 1; i <= n; i++) {
			ll x = Read(), y = Read(), r = Read();
			long double l = sqrt(x * x + y * y), alpha = atan2(y, x);
			if (alpha < 0) alpha += 2 * pi;
			ll intL = ceil(l);
			int nearD = intL - intL % d;
			if (Abs(nearD + d - l) < Abs(nearD - l)) nearD += d;
			
			for (int R = nearD; Abs(R - l) <= r; R += d) {
				Work(R, x, y, r, alpha, l);
			}
			for (int R = nearD - d; Abs(R - l) <= r; R -= d) {
				Work(R, x, y, r, alpha, l);
			}
		}
		sort (rL + 1, rL + 1 + cnt);
		sort (rR + 1, rR + 1 + cnt);
		int ans = 0, tmp = 0;
		for (int i = 1, j = 1; i <= cnt && j <= cnt; ) {
			for (; rL[i] <= rR[j] && i <= cnt; i++, tmp++);
			ans = max(ans, tmp);
			for (; rR[j] <= rL[i] && j <= cnt; j++, tmp--);
		}
		printf ("%d\n", ans);
		return 0;
	}
}

int main () {
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	Main::main();
	return 0;
}
```

---

