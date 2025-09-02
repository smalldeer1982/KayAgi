# Connect Three

## 题目描述

The Squareland national forest is divided into equal $ 1 \times 1 $ square plots aligned with north-south and east-west directions. Each plot can be uniquely described by integer Cartesian coordinates $ (x, y) $ of its south-west corner.

Three friends, Alice, Bob, and Charlie are going to buy three distinct plots of land $ A, B, C $ in the forest. Initially, all plots in the forest (including the plots $ A, B, C $ ) are covered by trees. The friends want to visit each other, so they want to clean some of the plots from trees. After cleaning, one should be able to reach any of the plots $ A, B, C $ from any other one of those by moving through adjacent cleared plots. Two plots are adjacent if they share a side.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1085C/cf5d536458708f86bac89ca28316f7ecb522f107.png)For example, $ A=(0,0) $ , $ B=(1,1) $ , $ C=(2,2) $ . The minimal number of plots to be cleared is $ 5 $ . One of the ways to do it is shown with the gray color.Of course, the friends don't want to strain too much. Help them find out the smallest number of plots they need to clean from trees.

## 说明/提示

The first example is shown on the picture in the legend.

The second example is illustrated with the following image:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1085C/bd6dd616034b12c36a0bd287e4e6a207ec125259.png)

## 样例 #1

### 输入

```
0 0
1 1
2 2
```

### 输出

```
5
0 0
1 0
1 1
1 2
2 2
```

## 样例 #2

### 输入

```
0 0
2 0
1 1
```

### 输出

```
4
0 0
1 0
1 1
2 0
```

# 题解

## 作者：SuperBeetle (赞：4)

# 题目
给出 $A,B,C$ 三点坐标，用最短的路径把他们连起来，输出路径上经过的点。


### 解析

我们先来看一下样例（画的有点不好看，请见谅）。


![](https://cdn.luogu.com.cn/upload/image_hosting/kydk909w.png)


如果我们平移一下，以 $y$ 排序，第二个点作为标准，就可以得到下图：


![](https://cdn.luogu.com.cn/upload/image_hosting/690sbjbn.png)

### 结论


所以，我们只需要将输入数据以 $y$ 轴排序，以（以 $y$ 轴排序后的）第二个点为标准，再遍历行，如果列与其中一个点的列相等，就去算需要清理多少块地，应为 $|x - x1|$，其中 $x$ 为行，$x1$ 为当前的行。


### 代码
```cpp

#include<bits/stdc++.h>
#define io ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define int long long

const int E = 1e6 + 1;

using namespace std;

struct node {//输入的数据
	int x, y;//输入一个x和y
}a[E];

bool cmp(node a, node b) {
	return a.x < b.x;//排序规则
}

int cnt;//清理的块数

signed main() {
	io;
	cin >> a[1].y >> a[1].x >> a[2].y >> a[2].x >> a[3].y >> a[3].x;//输入(我是反着输入的)
	sort(a + 1, a + 1 + 3, cmp);//排序
	int maxy = a[3].y, miny = a[1].y, p = a[2].x, q = a[3].x;//记录遍历的位置和标准
	for (int i = miny; i <= maxy; i++) {//遍历
		cnt++;//遍历一个加一个
		if (i == a[1].y && a[1].x != p) {//判断列与第一个点的列相不相同
			if (p > a[1].x) for (int j = p - 1; j >= a[1].x; j--) cnt++;//我当时没想出来可以用减法
			else for (int j = p + 1; j <= a[1].x; j++) cnt++;//没想出来+1
		}
		if (i == a[2].y && a[2].x != p) {//判断列与第二个点的列相不相同
			if (p > a[2].x) for (int j = p - 1; j >= a[2].x; j--) cnt++;//没想出来+2
			else for (int j = p + 1; j <= a[2].x; j++) cnt++;//没想出来+3
		}
		if (i == a[3].y && a[3].x != p) {//判断列与第三个点的列相不相同
			if (p > a[3].x) for (int j = p - 1; j >= a[3].x; j--) cnt++;//没想出来+4
			else for (int j = p + 1; j <= a[3].x; j++) cnt++;//没想出来+5
		}
	}
	cout << cnt << '\n';//输出
	for (int i = miny; i <= maxy; i++) {//和前面一样,只不过上面是统计,这里是输出路径
		cout << i << ' ' << p << '\n';
		if (i == a[1].y && a[1].x != p) {
			if (p > a[1].x) for (int j = p - 1; j >= a[1].x; j--) cout << i << ' ' << j << '\n';
			else for (int j = p + 1; j <= a[1].x; j++) cout << i << ' ' << j << '\n';
		}
		if (i == a[2].y && a[2].x != p) {
			if (p > a[2].x) for (int j = p - 1; j >= a[2].x; j--) cout << i << ' ' << j << '\n';
			else for (int j = p + 1; j <= a[2].x; j++) cout << i << ' ' << j << '\n';
		}
		if (i == a[3].y && a[3].x != p) {
			if (p > a[3].x) for (int j = p - 1; j >= a[3].x; j--) cout << i << ' ' << j << '\n';
			else for (int j = p + 1; j <= a[3].x; j++) cout << i << ' ' << j << '\n';
		}
	}
	return 0;
}//完结撒花
```

---

## 作者：zym20249_ (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/CF1085C)

## 题意
有一个 $n\times m$ 的矩阵，给出了三个点 $a$，$b$，$c$，需要求这三个点之间的最短距离和，包含这三个点，求路上的所有矩阵点和总共个数。

## 题意
我们能够构造出一种几条线满足到任意两点都是最短距离，所以距离很容易就能求出来。我们只需要以 $x$ 或 $y$ 轴排序，以另一个为标准，再遍历另外一个轴，如果某个轴与其中一个点的轴相等，就是直接出距离，另外一个点就是到这条路径的最短就可以了。

---

## 作者：shiroi (赞：1)

### Description

给定网格图上 $A,B,C$ 三点坐标，用最短的路径把他们连起来，求出让三个点连通的最少网格数并输出路径上的点。



### Solution

一道构造题。

观察题目发现联通三个点的最短路径大致如下图：

![U8AK78.jpg](https://s1.ax1x.com/2020/07/12/U8AK78.jpg)

所以考虑将三个点按 $x$ 排序，过中间的点作一条竖线后其他两点向其做垂线即为最短路径。

发现这种路径的作法最优且满足题意，因此可以避免对路径的分类讨论。

实现时直接大力构造，并将路径上的点扔进set里输出即可。实现相对简单。

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read()
{
    int x=0,f=1,c=getchar();
    while(c<48) c=='-'&&(f=-1),c=getchar();
    while(c>47) x=x*10+c-'0',c=getchar();
    return x*f;
}

const int MAXN = 15;
struct Point {int x,y;} p[MAXN];
std::set<pair<int,int> > s;

bool operator <(Point a,Point b)
{return a.x>b.x;}

int main(int argc, char const *argv[])
{
    for(int i=1; i<=3; ++i)
        p[i].x=read(),p[i].y=read();
    sort(p+1,p+4);
    int maxy=max(max(p[1].y,p[2].y),p[3].y);
    int miny=min(min(p[1].y,p[2].y),p[3].y);
    int maxx=max(max(p[1].x,p[2].x),p[3].x);
    int minx=min(min(p[1].x,p[2].x),p[3].x);
    for(int i=miny; i<=maxy; i++)
        s.insert(make_pair(p[2].x,i));
    for(int i=minx; i<=p[2].x; i++)
        s.insert(make_pair(i,p[3].y));
    for(int i=p[2].x; i<=maxx; i++)
        s.insert(make_pair(i,p[1].y));
    printf("%d\n", maxx+maxy-minx-miny+1);
    for(pair<int,int> x : s)
        printf("%d %d\n", x.first,x.second);
    return 0;
}
```



---

## 作者：little_sun (赞：0)

## C. Connect Three

* 差点C没做出来退役

可以发现最优路径是曼哈顿距离上的两条路径(先竖后横，先横后竖)

将$3$个点按$x$坐标排序，枚举(排序后的)$A$->$B$的两种(先上后左，先左后上)，$B$->$C$的两种，共四种

取最小值输出即可

**Code：**

```c++
#include <bits/stdc++.h>
#define mp(i, j) std::make_pair(i, j)
#define p std::pair<int, int>
p a[4];
std::map<p, int> m1, m2, m3, m4;
void add1()
{
    for (int i = a[1].first; i <= a[2].first; i++)
        m1[mp(i, a[1].second)] = 1;
    if (a[1].second <= a[2].second)
    {
        for (int i = a[1].second; i <= a[2].second; i++)
            m1[mp(a[2].first, i)] = 1;
    }
    else
    {
        for (int i = a[1].second; i >= a[2].second; i--)
            m1[mp(a[2].first, i)] = 1;
    }
    for (int i = a[2].first; i <= a[3].first; i++)
        m1[mp(i, a[2].second)] = 1;
    if (a[2].second <= a[3].second)
    {
        for (int i = a[2].second; i <= a[3].second; i++)
            m1[mp(a[3].first, i)] = 1;
    }
    else
    {
        for (int i = a[2].second; i >= a[3].second; i--)
            m1[mp(a[3].first, i)] = 1;
    }
}
void add2()
{
    for (int i = a[1].first; i <= a[2].first; i++)
        m2[mp(i, a[1].second)] = 1;
    if (a[1].second <= a[2].second)
    {
        for (int i = a[1].second; i <= a[2].second; i++)
            m2[mp(a[2].first, i)] = 1;
    }
    else
    {
        for (int i = a[1].second; i >= a[2].second; i--)
            m2[mp(a[2].first, i)] = 1;
    }

    if (a[2].second <= a[3].second)
    {
        for (int i = a[2].second; i <= a[3].second; i++)
            m2[mp(a[2].first, i)] = 1;
    }
    else
    {
        for (int i = a[2].second; i >= a[3].second; i--)
            m2[mp(a[2].first, i)] = 1;
    }
    for (int i = a[2].first; i <= a[3].first; i++)
        m2[mp(i, a[3].second)] = 1;
}
void add3()
{

    if (a[1].second <= a[2].second)
    {
        for (int i = a[1].second; i <= a[2].second; i++)
            m3[mp(a[1].first, i)] = 1;
    }
    else
    {
        for (int i = a[1].second; i >= a[2].second; i--)
            m3[mp(a[1].first, i)] = 1;
    }
    for (int i = a[1].first; i <= a[2].first; i++)
        m3[mp(i, a[2].second)] = 1;
    if (a[2].second <= a[3].second)
    {
        for (int i = a[2].second; i <= a[3].second; i++)
            m3[mp(a[2].first, i)] = 1;
    }
    else
    {
        for (int i = a[2].second; i >= a[3].second; i--)
            m3[mp(a[2].first, i)] = 1;
    }
    for (int i = a[2].first; i <= a[3].first; i++)
        m3[mp(i, a[3].second)] = 1;
}
void add4()
{
    if (a[1].second <= a[2].second)
    {
        for (int i = a[1].second; i <= a[2].second; i++)
            m4[mp(a[1].first, i)] = 1;
    }
    else
    {
        for (int i = a[1].second; i >= a[2].second; i--)
            m4[mp(a[1].first, i)] = 1;
    }
    for (int i = a[1].first; i <= a[2].first; i++)
        m4[mp(i, a[2].second)] = 1;
    for (int i = a[2].first; i <= a[3].first; i++)
        m4[mp(i, a[2].second)] = 1;
    if (a[2].second <= a[3].second)
    {
        for (int i = a[2].second; i <= a[3].second; i++)
            m4[mp(a[3].first, i)] = 1;
    }
    else
    {
        for (int i = a[2].second; i >= a[3].second; i--)
            m4[mp(a[3].first, i)] = 1;
    }
}
inline int print(std::map<p, int> m)
{
    for (std::map<p, int>::iterator it = m.begin(); it != m.end(); it++)
        printf("%d %d\n", it->first.first, it->first.second);
}
int main()
{
    int cnt = 0;
    for (int i = 1; i <= 3; i++)
        scanf("%d%d", &a[i].first, &a[i].second);
    std::sort(a + 1, a + 3 + 1);
    add1(), add2(), add3(), add4();
    cnt = std::min(std::min(m1.size(), m2.size()), std::min(m3.size(), m4.size()));
    printf("%d\n", cnt);
    if (m1.size() == cnt)
        return 0 * print(m1);
    if (m2.size() == cnt)
        return 0 * print(m2);
    if (m3.size() == cnt)
        return 0 * print(m3);
    if (m4.size() == cnt)
        return 0 * print(m4);
    return 0;
}
```



---

