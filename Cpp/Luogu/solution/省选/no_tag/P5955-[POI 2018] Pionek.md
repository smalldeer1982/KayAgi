# [POI 2018] Pionek

## 题目描述

在无限大的二维平面的原点 $(0,0)$ 放置着一个棋子。你有 $n$ 条可用的移动指令，每条指令可以用一个二维整数向量表示。每条指令可以执行 $1$ 次或者不执行。棋子可以重复经过同一个点，两条指令的方向向量也可能相同。你的目标是让棋子最终离原点的**欧几里得距离**最远，请问这个最远距离是多少？

## 说明/提示

对于 $100\%$ 的数据，$n\le 2 \times 10^5$，$|x|,|y| \le 10^4$。

-----

### 样例解释：

![](https://cdn.luogu.com.cn/upload/image_hosting/aiztesh5.png)

## 样例 #1

### 输入

```
5
2 -2
-2 -2
0 2
3 1
-3 1```

### 输出

```
26```

# 题解

## 作者：shiroi (赞：3)

### Description

现有若干二维向量，你需要任选若干条二维向量使得这些向量的和长度最大。

### Solution

观察题目可以发现，只有在答案向量方向投影为正的向量才会对结果产生贡献。由此考虑枚举所有方向进行求解。

对所有向量求出极角序，可以看出选取的向量在排序后一定是连续的一段。由此可以考虑双指针的方法求解。所有向量形成一个环，因此处理时需要复制一份求解，然后双指针枚举左右端点即可得出结果。时间复杂度 $O(nlogn)$。

本题对精度有一定要求，需要注意精度问题。

```cpp
#include <bits/stdc++.h>
using namespace std;

char buf[10000001],*ptr=buf-1;

inline int read()
{
	int x=0,f=1,c=*++ptr;
	while(c<48) c=='-'&&(f=-1),c=*++ptr;
	while(c>47) x=x*10+c-'0',c=*++ptr;
	return x*f;
}

typedef long long ll;
const int MAXN = 400005;
const double pi = acos(-1);
struct Point {int x,y; double agl;} p[MAXN];
int n;

bool operator < (Point a,Point b)
{return a.agl<b.agl;}

int main(int argc, char const *argv[])
{
	fread(buf,1,sizeof(buf),stdin)[buf]=0;
	n=read();
	for(int i=1; i<=n; ++i)
	{
		p[i].x=read(); p[i].y=read();
		p[i].agl=atan2(p[i].y,p[i].x);
		(!p[i].x&&!p[i].y) &&(--i,--n);
	}
	sort(p+1,p+n+1);
	ll dx=0,dy=0,ans=0;
	for(int l=1,r=1; l<=n; ++l)
	{
		p[n+l]=(Point) {p[l].x,p[l].y,p[l].agl+2*pi};
		while(r<n+l&&p[r].agl-p[l].agl<pi+1e-10)
		{
			dx+=p[r].x; dy+=p[r++].y;
			ans=max(ans,dx*dx+dy*dy);
		}
		dx-=p[l].x; dy-=p[l].y;
		ans=max(ans,dx*dx+dy*dy);
	}
	printf("%lld\n",ans);
	return 0;
}
```







---

## 作者：ZhongYuLin (赞：2)

显然只有处于一个半平面内的向量集合才有可能成为答案。去考虑枚举半平面。考虑用一个与分割线正交的方向向量来刻画这个半平面

我们将所有的向量按辐角主值排序。设答案向量为 $\mathbf{x}$，其初始指向纵轴正方向，然后将其沿原点绕一圈。具体地，每次逆时针旋转 $\varepsilon \operatorname{rad}$，直到回到起始点。 不难发现，答案在排序后总是一段区间，于是将原序列复制一份后使用双指针，注意重复的问题。

对于区间右端点，如果当前向量与 $\mathbf{x}$ 的夹角小于等于 $\frac{1}{2}\pi$，加入。

对于区间左端点，如果当前向量与 $\mathbf{x}$ 的夹角大于 $\frac{1}{2}\pi$，删除。

然而，我们不必构造 $\mathbf{x}$ 然后借助内积，我们可以直接使用辐角主值。具体地：

$$\langle\mathbf{x},\mathbf{y}\rangle=\min(\left|\arg{\mathbf{x}}-\arg{\mathbf{y}}\right|,2\pi-\left|\arg{\mathbf{x}}-\arg{\mathbf{y}}\right|)$$

注意一下 $\varepsilon$ 的数量级和精度误差就可以了。

复杂度 $O(n\log n+\frac{1}{\varepsilon})$。

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=4e5+3;
const double PI=acos(-1),eps=1e-6;
struct Vec{
    int x,y;
    double tan;
}v[N];
int n;
double calc(double t1,double t2){return min(abs(t1-t2),2*PI-abs(t1-t2));}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>v[i].x>>v[i].y;
        if(!v[i].x&&!v[i].y){--i,--n;continue;}
        v[i].tan=atan2(v[i].y,v[i].x);
        if(v[i].tan<0)v[i].tan+=2*PI;
    }
    sort(v+1,v+1+n,[&](Vec x,Vec y){return x.tan<y.tan;});
    for(int i=1;i<=n;++i)v[i+n]=v[i];
    int l=1,r=1;double it=PI/2;ll x=0,y=0,ans=0;
    for(;it<=PI*5/2;it+=eps){
        double at=it;
        if(at>2*PI)at-=2*PI;
        while(r<=l+n-1&&calc(v[r].tan,at)*2<=PI)
            x+=v[r].x,y+=v[r].y,ans=max(ans,x*x+y*y),++r;
        while(l<r&&calc(v[l].tan,at)*2>PI)
            x-=v[l].x,y-=v[l].y,ans=max(ans,x*x+y*y),++l;
    }printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Leianha (赞：2)

## 几何+双指针

[博客阅读](https://www.cnblogs.com/wljss/p/12344129.html)

题目大意：现在有 $n$ 个向量，请你选出来一些向量使它们的和的长度最大，输出最大值的平方。

假如我们已经知道了最终向量的方向，我们要想使长度最大，就需要将所有投影在最终向量正方向上的向量都加起来。

所以我们可以按角度枚举最终向量的方向，我们需要加起来的就是一段移动的区间，我们可以用双指针来维护加起来的向量。

因为最终向量的方向有可能是给出的向量，也有可能是向量之间间隔的方向，所以每次移动指针的时候都要更新一下答案.

因为开始给出的向量不一定有序，所以我们需要先将向量排序。

```cpp
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>
#define LL long long
using namespace std;
int n;
const double PI = acos(-1);
LL sx, sy, ans;
struct data
{
	LL x, y; double ang;
	friend bool operator <(const data & a,const data & b) {return a.ang < b.ang;}
}a[400010];
int main()
{
	cin >> n;
	for(int i = 1; i <= n; ++ i)scanf("%lld%lld", &a[i].x, &a[i].y), a[i].ang = atan2(a[i].y,a[i].x);
	sort(a + 1, a + 1 + n);
	for(int i = 1; i <= n; ++ i)a[n + i].x = a[i].x, a[n + i].y = a[i].y, a[n + i].ang = a[i].ang + 2 * PI;
	for(int l = 1, r = 1; l <= n; ++ l)
	{
		while(r < n + l && a[r].ang - a[l].ang < PI)sx += a[r].x, sy += a[r].y, ans = max(ans, sx * sx + sy * sy), ++ r;
		sx -= a[l].x, sy -= a[l].y, ans = max(ans, sx * sx + sy * sy);
	}
	cout << ans;
	return 0;
}
```

---

## 作者：OIer_ACMer (赞：1)

# Solution

为方便统计，我们可以将运动方向选择后，连续选择符合条件的运动方案，毕竟根据向量性质，不同的加减方式，在选择的集合一定时，得到的结果一样。

由于我们要找距离源点最远的的运动结果，可以发现**只有在答案向量方向投影为正的向量**，才会对结果产生贡献，我们就要保证一开始的出发方案，与之后的每一次方案的夹角不会超过平角。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
struct node
{
    int x, y;
    double jiao;
} xian[1000009];
int n;
const double pi = acos(-1.0);
signed main()
{
    n = read();
    for (int i = 1; i <= n; i++)
    {
        cin >> xian[i].x >> xian[i].y;
        if (!xian[i].x && !xian[i].y)
        {
            i--;
            n--;
            continue;
        }
        xian[i].jiao = atan2(xian[i].y, xian[i].x);
    }
    sort(xian + 1, xian + n + 1, [](node a, node b) { return a.jiao < b.jiao; });
    int dx = 0, dy = 0, ans = 0;
    for (int i = 1; i <= n; i++)
    {
        xian[i + n] = xian[i];
        xian[i + n].jiao += 2 * pi;
    }
    for (int l = 1, r = 1; l <= n; l++)
    {
        while (r < n + n && xian[r].jiao - xian[l].jiao < pi + 1e-10)
        {
            dx += xian[r].x;
            dy += xian[r].y;
            r++;
            ans = max(ans, dx * dx + dy * dy);
            // cout << "ans=" << ans << endl;
        }
        dx -= xian[l].x;
        dy -= xian[l].y;
        ans = max(ans, dx * dx + dy * dy);
    }
    // double res = sqrt(ans);
    cout << ans << endl;
    return 0;
}
```

---

## 作者：WorldMachine (赞：1)

为了使答案最大，肯定只会选择在答案向量上投影为正的向量，也即选取的所有向量在同一半平面内。

于是考虑枚举半平面，这可以通过双指针实现。由于不一定要选出半平面中所有的点，因此要在移动右端点的过程中统计答案。
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 200005;
const double pi = acos(-1);
int n;
ll Sx, Sy, sx, sy, ans;
struct point { int x, y; } a[N];
double angle(point a) { return atan2(a.y, a.x); }
bool cmp(point a, point b) { return angle(a) < angle(b); }
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i].x >> a[i].y, Sx += a[i].x, Sy += a[i].y;
	sort(a + 1, a + 1 + n, cmp);
	for (int l = 1, r = 1; l <= n; l++) {
		while (r <= n && angle(a[r]) - angle(a[l]) < pi + 1e-8) sx += a[r].x, sy += a[r].y, ans = max({ans, sx * sx + sy * sy, (Sx - sx) * (Sx - sx) + (Sy - sy) * (Sy - sy)}), r++;
		sx -= a[l].x, sy -= a[l].y;
		ans = max({ans, sx * sx + sy * sy, (Sx - sx) * (Sx - sx) + (Sy - sy) * (Sy - sy)});
	}
	cout << ans;
}
```

---

## 作者：MerlinLee (赞：0)

首先，将所有向量按极角排序，则答案集合一定是连续的一段。

当答案方向确定时，则一个向量会被选入答案集合当且仅当向量在答案方向上的投影一定都是正的。

所以，两个选中向量中间隔着一个向量，则必然可以将后面所有选中向量均前移一位并使答案不劣。

其次，答案集合中不存在两个向量的极角差超过 $\pi$ 对吧。

显然需要保证的是，答案集合中任意两个向量投影不为负值，否则一定可以通过删去其中一个使答案更优。

最后，当选择的向量集合区间左端点增加时，右端点单调不减。

感性理解，答案向量的极角会在选择的向量区间中某两个相邻向量极角之间。当区间左端点增加时，答案向量的极角必然增加，故右端点不会减少。

于是，将所有向量极角排序后，对所有扫过的极角极差不超过 $\pi$ 的向量区间更新答案即可。


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=400010;
const double pi=acos(-1.);
int n;
ll ans;
struct P
{
    int x,y; double s;
    bool operator <(const P &a)const
	{ 
		return s<a.s; 
	}
    P operator +(const P &a)const
	{ 
		return (P){x+a.x,y+a.y}; 
	}
    P operator -(const P &a)const
	{ 
		return (P){x-a.x,y-a.y}; 
	}
    ll len()
	{ 
		return 1ll*x*x+1ll*y*y; 
	}
}a[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) 
	  scanf("%d%d",&a[i].x,&a[i].y),a[i].s=atan2(a[i].x,a[i].y);
    sort(a+1,a+n+1); 
	P cur=(P){0,0}; 
	int x=0;
    for(int i=1;i<=n;i++)
	  a[i+n]=a[i],a[i+n].s+=2*pi;
    for(int i=1;i<=n;i++)
	{
        while(x<n*2 and a[x+1].s-a[i].s<=pi) 
		  cur=cur+a[++x],ans=max(ans,cur.len());
        cur=cur-a[i]; ans=max(ans,cur.len());
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

