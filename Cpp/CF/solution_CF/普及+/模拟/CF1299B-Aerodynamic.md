# Aerodynamic

## 题目描述

Guy-Manuel and Thomas are going to build a polygon spaceship.

You're given a strictly convex (i. e. no three points are collinear) polygon $ P $ which is defined by coordinates of its vertices. Define $ P(x,y) $ as a polygon obtained by translating $ P $ by vector $ \overrightarrow {(x,y)} $ . The picture below depicts an example of the translation:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1299B/83c2f1baf8b89730630e4ed629298d51b68af048.png)

Define $ T $ as a set of points which is the union of all $ P(x,y) $ such that the origin $ (0,0) $ lies in $ P(x,y) $ (both strictly inside and on the boundary). There is also an equivalent definition: a point $ (x,y) $ lies in $ T $ only if there are two points $ A,B $ in $ P $ such that $ \overrightarrow {AB} = \overrightarrow {(x,y)} $ . One can prove $ T $ is a polygon too. For example, if $ P $ is a regular triangle then $ T $ is a regular hexagon. At the picture below $ P $ is drawn in black and some $ P(x,y) $ which contain the origin are drawn in colored:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1299B/7e534d615e6a5f78b53ffae5177d7d1ddaf49471.png)

The spaceship has the best aerodynamic performance if $ P $ and $ T $ are similar. Your task is to check whether the polygons $ P $ and $ T $ are [similar](https://tinyurl.com/vp5m7vl).

## 说明/提示

The following image shows the first sample: both $ P $ and $ T $ are squares. The second sample was shown in the statements.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1299B/e9bf2b6bd412db56abfa4dcfff0f19e57982f841.png)

## 样例 #1

### 输入

```
4
1 0
4 1
3 4
0 3```

### 输出

```
YES```

## 样例 #2

### 输入

```
3
100 86
50 0
150 0```

### 输出

```
nO```

## 样例 #3

### 输入

```
8
0 0
1 0
2 1
3 3
4 6
3 6
2 5
1 3```

### 输出

```
YES```

# 题解

## 作者：syksykCCC (赞：8)

致和我一样没写过计算几何的人……

前置知识：**闵可夫斯基和**

> 「闵可夫斯基和」是两个欧几里得空间的点集的和，也称为这两个空间的「膨胀集」，以德国数学家闵可夫斯基命名。点集 $A$ 与 $B$ 的闵可夫斯基和被定义为： 
$$ A+B = \{ a+b ~|~ a \in A, b \in B\} $$
> 例如，平面上有两个三角形，其坐标分别为 $A=\{(1,0),(0,1),(0,-1)\}$ 及 $B=\{(0,0),(1,1),(1,1)\}$ ，则其闵可夫斯基和为 $A + B = \{(1, 0), (2, 1), (2,1), (0, 1), (1, 2), (1, 0), (0,1), (1, 0), (1,2)\}$。

> 通俗一点，**从原点向图形 $A$ 内部的每一个点做向量，将图形 $B$ 沿每个向量移动，所有的最终位置的并便是闵可夫斯基和**（具有交换律）。

现在题目已经给了我们一个点集，就叫做 $S$ 吧。

对于 $(x, y) \in S$，我们要把它给平移到 $(0, 0)$ 去，就是要走一个 $(-x, -y)$，所有的在一起，便是 $-S$ 了。

然后我们发现，我们恰好是想要 **从原点向图形 $-S$ 内部的每一个点做向量，将图形 $S$ 沿每个向量移动，所有的最终位置的并** 这个图形，它正好就是 $S$ 与 $-S$ 的闵可夫斯基和！

然后呢，就可以爆干了。

当然这个做法不香，需要继续分析。

正常求一定是 $2n$ 条边，所以有边共线。然后我们发现，与 $S$ 相似的答案多边形，与 $S$ 的相似比恰好为 $2$！

这从样例中很容易看出来。

样例1：

![image.png](https://i.loli.net/2020/02/10/XsH9ATRoFGqD4t5.png)

样例3：

![image.png](https://i.loli.net/2020/02/11/7oqGAmHTPSgY8Fy.png)

从图中很明显可以看出来，临边相等且共线，而且它来自 **两个相邻多边形的同一条边**，而这次的平移取决于 **它对面的那条边**。

* 不重合，说明对边与它相等；
* 共线，说明对边与它平行。

所以，这题就是让我们判断，这个图形是否 **中心对称**！

于是检查对应点连线的中点是否重合就行了。

时间复杂度 $\mathcal O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
const double EPS = 1e-10;
double x[N], y[N];
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> x[i] >> y[i];
	if(n & 1) { cout << "NO\n"; return 0; }
	int mid = n >> 1;
	double px = (x[1] + x[mid + 1]) / 2.0;
	double py = (y[1] + y[mid + 1]) / 2.0;
	bool ok = true;
	for(int i = 2; i <= mid; i++)
	{
		double kx = (x[i] + x[mid + i]) / 2.0;
		double ky = (y[i] + y[mid + i]) / 2.0;
		if(fabs(px - kx) >= EPS || fabs(py - ky) >= EPS) ok = false;
	}
	if(ok) cout << "YES\n";
	else cout << "NO\n";
	return 0;
}
```

---

## 作者：lemonfor (赞：2)

~~题目比较难读懂~~

~~把点打出来之后~~可以发现是让我们找边数是偶数的中心对称图形，因为点都是按照顺序给的，所以每一组对称点的序号都相差 $n / 2$ ,即每组对称点连线的中点相同就是中心对称图形了QAQ
```cpp
#include<cstdio>
#include<algorithm>
#define _ 0
#define INF 0x3f3f3f
#define int long long
#define N 100001
#define re register
#define drep(i ,l ,r) for(re int i = (l) ; i >= (r) ; -- i)
#define rep(i ,l ,r) for(re int i = l ; i <= r ; ++ i)
using namespace std;
struct node {
    int x ,y;
} poi[N];
int _x ,_y ,n;
int read() {
    char cc = getchar() ; int cn = 0 ,flus = 1;
    while(cc < '0' || cc > '9') {if(cc == '-') flus = - flus ; cc = getchar();}
    while(cc >= '0' && cc <= '9') cn = cn * 10 + cc - '0' ,cc = getchar();
    return flus * cn;
}
signed main() {
    n = read();
    if(n & 1) {printf("NO");return ~~(0^_^0);};
    rep(i ,1 ,n) poi[i].x = read() ,poi[i].y = read();
    _x = poi[1].x + poi[n / 2 + 1].x ,_y = poi[1].y + poi[n / 2 + 1].y;
    rep(i ,1 ,n / 2) if(poi[i].x + poi[n / 2 + i].x != _x || poi[i].y + poi[n / 2 + i].y != _y) {printf("NO");return ~~(0^_^0);}
    printf("YES");
    return ~~(0^_^0);
}

```

---

## 作者：ShineEternal (赞：1)

[更好的阅读效果](https://blog.csdn.net/kkkksc03/article/details/104255317)

## description:

- 给定一个由 $n$ 个点组成的**严格**（不存在三点共线）凸多边形。

- 你要将这个图形平移 $n$ 次，每次将一个顶点与原点 $(0,0)$ 重合。

- 请判断这 $n$ 个平移后的多边形除了与原点重合的点之外的点组成的多边形是否与原图形[相似](https://tinyurl.com/vp5m7vl)。

- 在读入中，保证输入的点按逆时针顺序排列，形成严格凸多边形。

- $3\le n\le 10^5$

- translate by @[ShineEternal](https://www.luogu.com.cn/user/45475)。

## solution:

这道题我们可以发现只需判断图形是否为中心对称即可。

因为平移后拼成的大图形本质上是由小的原图形支撑起来的。

要让他们相似，就要使得本来不同的顶点相似的对应。

---

还有题目良心的给出了排好的序，直接每一组对应点的中点和第一组点的比较即可。

## code:
```cpp
#include<cstdio>
using namespace std;
double x[100005],y[100005];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lf%lf",&x[i],&y[i]);
	}
	if(n%2==1)
	{
		printf("NO\n");
		return 0;
	}
	double p1=(x[1]+x[n/2+1])/2,p2=(y[1]+y[n/2+1])/2;
	for(int i=2;i<=n/2;i++)
	{
		double p3=(x[i]+x[n/2+i])/2;
		double p4=(y[i]+y[n/2+i])/2;
		if(p3!=p1||p4!=p2)
		{
			printf("NO\n");
			return 0;
		}
	}
	printf("YES\n");
	return 0;
} 
```

---

## 作者：Mint_Flipped (赞：1)

这个题题目很啰嗦 其实就是看看所给点构成的图形是不是中心对称。

中心对称：就是图形上每对应的两个点都按一个中点对称。

那么题目就是在求这个图形每对应的两个点的对称点是不是一个点。

直接上简陋代码:
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100005][2]; //坐标
int main()
{
    int n;
    cin>>n;
    for(int i=1; i<=n; ++i)
        scanf("%d%d",&a[i][0],&a[i][1]);
    if(n>>1==1) //两两对应，故排除奇数
    {
        cout<<"NO"<<endl;
        return 0;
    }
    else
    {
        double te1=(a[1][0]+a[1+n/2][0])/2.0,te2=(a[1][1]+a[1+n/2][1])/2.0;
        for(int i=2; i<=n/2; ++i)
        {
            if(te1!=(a[i][0]+a[i+n/2][0])/2.0||te2!=(a[i][1]+a[i+n/2][1])/2.0) //比较的时候记得转换为double
            {
                cout<<"NO"<<endl;
                return 0;
            }
        }
        cout<<"YES"<<endl;
    }
    return 0;
}
```


---

