# New Year and Curling

## 题目描述

Carol is currently curling.

She has $ n $ disks each with radius $ r $ on the 2D plane.

Initially she has all these disks above the line $ y=10^{100} $ .

She then will slide the disks towards the line $ y=0 $ one by one in order from $ 1 $ to $ n $ .

When she slides the $ i $ -th disk, she will place its center at the point $ (x_{i},10^{100}) $ . She will then push it so the disk’s $ y $ coordinate continuously decreases, and $ x $ coordinate stays constant. The disk stops once it touches the line $ y=0 $ or it touches any previous disk. Note that once a disk stops moving, it will not move again, even if hit by another disk.

Compute the $ y $ -coordinates of centers of all the disks after all disks have been pushed.

## 说明/提示

The final positions of the disks will look as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF908C/d83c8ae09a1afba1002e3c764e58c1e7ac4abfee.png)In particular, note the position of the last disk.

## 样例 #1

### 输入

```
6 2
5 5 6 8 3 12
```

### 输出

```
2 6.0 9.87298334621 13.3370849613 12.5187346573 13.3370849613
```

# 题解

## 作者：_xbn (赞：4)

很新颖的一道题，大家拿到题面后可能有点蒙，但仔细分析后可以发现并不难想。

首先看到数据范围 $n <= 1000$，这提示我们可以暴力做。

那具体怎么暴力呢？

由于一个圆遇到之前掉落的任意一个圆后就会停止掉落，那显然他肯定碰到的是之前掉落的，横坐标距离在圆直径以内，与他相切，高度最高的圆，并且这个圆横纵坐标确定。

那要从之前的圆推到当前圆的位置，学过初二几何的应该都知道，两个圆相切，两圆心可以作为直角三角形斜边上的两点。如图：

![](https://z3.ax1x.com/2021/07/13/WEKYaq.png)

设两直角边为 $A$ 和 $B$，斜边为 $C$，我们已知 $C$ 和 $A$，那 $B$ 可以用勾股定理求出，具体为 $C^2 - A^2$，那上方圆的坐标可以求出，为 $(x(i),y(j)+B)$。

那代码实现就不难了。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 100002;
int n, m, l, r, p, t, k, ans, sum, tot, cnt, c[N], mx[N];
double db, a[N], lp, b[N];
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
	{
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while('0' <= ch && ch <= '9')
	{
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
int main()
{
	n = read(); m = read(); p = 2 * m;
	for(int i = 1; i <= n; i++)
	{
		int x = read();
		a[i] = (double)(x);
		if(i == 1) 
		{
			b[i] = (double)(m);
			continue;
		}
		b[i] = m;
		for (int j = 1; j < i; j++)
		{
			if(a[j] < a[i] - p || a[j] > a[i] + p) continue;
			db = sqrt((double)(p * p) - (a[j] - a[i]) * (a[j] - a[i]));
			b[i] = max(b[i], b[j] + db);
		}
	}
	for (int i = 1; i <= n; i++) printf("%.8f ", b[i]);
	return 0;
}
```


---

## 作者：Provider (赞：1)

第一个圆的坐标是已知的，y就等于r。

然后第二个圆x是已知的，要求y，所以只需要一个方程就可以求解，所以我们利用两点间的距离公式

![](https://cdn.luogu.com.cn/upload/image_hosting/7mlfke8h.png)

**对不起，放错了**

![](https://cdn.luogu.com.cn/upload/image_hosting/gys295tg.png)

然后把应有的数据代入

化简后变成

$y2$=$\sqrt{(2r)^2-(x1-x2)^2}+y1$

然后暴力即可

# CODE：

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=1005;
long long n,length=1;
double r,R,x1,y,ans=0;
struct node
{
    double x2,y1;
}circle[maxn];
int main()
{
    cin>>n>>r;
    R=2*r*2*r;
    for(int i=1;i<=n;i++)
    {
        cin>>x1;
        if(i==1)
        {
            cout<<fixed<<setprecision(10)<<r<<" ";
            circle[length].x2=x1;
            circle[length].y1=r;
            length++;
        }
        else
        {
        	ans=0;
            for(int j=length;j>=1;j--)
            if(fabs((x1-circle[j].x2))<=2*r)
            {
                y=circle[j].y1;
                y+=sqrt(R-(x1-circle[j].x2)*(x1-circle[j].x2));//使用公式
                ans=max(ans,y);
            }
            if(ans)
            {
                cout<<fixed<<setprecision(10)<<ans<<" ";
                circle[length].x2=x1;
                circle[length].y1=ans;
                length++;
            }
            else
            {
                cout<<fixed<<setprecision(10)<<r<<" ";
                circle[length].x2=x1;
                circle[length].y1=r;
                length++;
            }
        }
    }
    return 0;
}
```

---

## 作者：OIerZhang (赞：0)

# [CF908C New Year and Curling](https://www.luogu.com.cn/problem/CF908C)

## 思路

这就是一道数学题，代码难度不高。

由于当冰壶到达终点线或者碰到了之前掷出的冰壶，它会立刻停止滑动，那么请看下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/fk7kvj76.png)

眼熟吗？这不就是勾股定理吗？

设需要求的为 $l$，那么 $(2r)^2 = (x_1 - x_2)^2 + l^2$，则 $l = \sqrt{4r^2 - (x_1 - x_2)^2}$。

我们只需要每掷一个冰壶，循环判断该冰壶是否与当前冰壶相切即可。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int x[1005];
double y[1005];

signed main()
{
	int n, r;
	scanf("%lld%lld", &n, &r);
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld", &x[i]);
		y[i] = r;
		for (int j = 1; j < i; j++)
		{
			if (x[j] + r < x[i] - r || x[j] - r > x[i] + r)
				continue;
			double add = sqrt(4 * r * r - (x[j] - x[i]) * (x[j] - x[i]));
			y[i] = max(y[i], y[j] + add);
		}
		printf("%.8lf ", y[i]);
	}
	return 0;
}
```

---

## 作者：I_AK_IOI_and_NOI (赞：0)

## 题目大意

一些圆在 $(x_i,10^{100})$ 处开始下落，下落时碰到其它圆就停止，求这些圆最后圆心 $y$ 值。

## 答题思路

第一个掉下来的球毫无疑问：球心高度 = 半径，模拟其他球掉下来的过程。

如果球掉下来碰到其他球，那么一定是后掉下来的球在前面球的上面，最差也是相等。

(高度差) $^2=(2r)^2 - $($x$ 坐标差值) $^2$。

每掉下来一个球，就检查之前的所有球，判断是不是砸在其他球上就好了。

所以不必想麻烦，就这三三个问题：

问题一：如何判断两个圆是否接触。利用勾股定理判断。

问题二：如果接触了，那么他比接触圆的还要高多少？还是勾股定理，求出高度差。

问题三：暴力，枚举第 $i$ 个之前的所有的园即可。

勾股定理判断两个圆是否接触不再赘述，想知道的看[这里](https://wenku.baidu.com/view/6b98c993c381e53a580216fc700abb68a882ad09.html)

## 具体代码

很短……

```
#include<bits/stdc++.h>
using namespace std;
double x[1010],y[1010];
int main()
{
    double n,r;
    while(cin>>n>>r)
    {
        for(int i=0; i<n; i++)
        {
            cin>>x[i];
            y[i]=r;
            for(int j=0; j<i; j++)
            {
                double l=4*r*r-(x[i]-x[j])*(x[i]-x[j]);
                y[i]=max(y[i],y[j]+sqrt(l));
            }
            printf("%.10f ",y[i]);
        }
        puts("\n");
    }
    return 0;
}
```




---

