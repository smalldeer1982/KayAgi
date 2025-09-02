# Very simple problem

## 题目描述

你有一个凸多边形，请计算，包含平面中给定点的三角形数量及其顶点是多边形的顶点的个数。题目保证，该点不位于多边形的边和对角线上。

## 样例 #1

### 输入

```
4
5 0
0 0
0 5
5 5
1
1 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
0 0
0 5
5 0
2
1 1
10 10
```

### 输出

```
1
0
```

## 样例 #3

### 输入

```
5
7 6
6 3
4 1
1 2
2 4
4
3 3
2 3
5 5
4 2
```

### 输出

```
5
3
3
4
```

# 题解

## 作者：rEdWhitE_uMbrElla (赞：1)

好久不写几何题有些手生了呢，，，没想到竟然一次性过了。。

讲道理的话，题目中有**simple**一词的题目都不会简单。。

这道题如果我们直接计算包含的个数，本蒟蒻只能想到$O(n^3)$的解法，然后就咕咕了。。于是我们可以从反面考虑——数不包含该点的三角形。然后我们发现，如果一个三角形不包含该点，则这个三角形总有一条边把该点和三角形另一个顶点分割开了，于是我们只需要枚举线段那个分割线段，然后求三角形另一个顶点有多少种选法即可，最后用总数减一下。

上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 100005;

pair<long long, long long> a[2 * MAX_N];

inline long long dis(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3) {
    return (x2 - x1) * (y3 - y2) - (y2 - y1) * (x3 - x2);
}

inline bool in_poly(long long x, long long y, int n) {
    long long area1 = 0, area2 = 0;
    for (int i = 1; i <= n; ++ i) area1 += a[i].first * a[i + 1].second - a[i].second * a[i + 1].first;
    for (int i = 1; i <= n; ++ i) area2 += fabs(dis(x, y, a[i].first, a[i].second, a[i + 1].first, a[i + 1].second));
    return fabs(area) == area2;
}

long long C3(int x) {
    if (x < 3) return 0;
    return 1LL * x * (x - 1) * (x - 2) / 6;
}

long long C2(int x) {
    if (x < 2) return 0;
    return 1LL * x * (x - 1) / 2;
}

long long solve(long long x, long long y, int n) {
    if (!in_poly(x, y, n)) return 0;
    int j = 2; long long sum = 0;
    for (int i = 1; i <= n; ++ i) {
        for (;dis(a[i].first, a[i].second, a[j + 1].first, a[j + 1].second, x, y) < 0;++j);
        sum += C2(j - i);
    }
    return C3(n) - sum;
}

int main() {
    int n, t;
    cin >> n;
    for (int i = 1; i <= n; ++ i) cin >> a[i].first >> a[i].second;
    for (int i = 1; i < n; ++ i) a[i + n] = a[i];
    cin >> t;
    for (int i = 1; i <= t; ++ i) {
        long long x, y;
        cin >> x >> y;
        cout << solve(x, y, n) << "\n";
    }
    return 0;
}

```

---

## 作者：LOLchn0 (赞：0)

# 题目大意：
给定一个凸多边形和一些点，问你这些点被多少个三角形所包含。

# 思路：
平面内 $n$ 点任意三点不共线可组成 $n*(n-1)*(n-2)÷6$ 个三角形。

求出不包含该点的三角形个数，用总个数减去这些即可。

# 代码：
```c
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Point
{
    ll x,y;
    Point(){};
    Point(ll x,ll y):x(x),y(y){}
};
Point operator-(const Point& lhs,const Point& rhs){
    return Point(lhs.x-rhs.x,lhs.y-rhs.y);
}
ll operator*(const Point& lhs,const Point& rhs){
    return lhs.x*rhs.y - lhs.y*rhs.x; 
}
ll s[1<<20];
Point p[1<<20];
Point q;
int main()
{
    int n,m;
    ll l,r,ans;
    for(int i=2;i<(1<<20);i++){
        s[i]+=s[i-1]+i-1;
    }
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>p[i].x>>p[i].y;
        p[n+i]=p[i];
    }
    cin>>m;
    for(int i=0;i<m;i++)
    {
        cin>>q.x>>q.y;
        for(int j=0;j<n;j++)
        {
            if((p[j]-q)*(p[j+1]-q) >= 0)
            {
                printf("0\n");
                goto  NEXT    ;
            }
        }
        ans = 0;
        for(int j=0,k=0;j<n;j++)
        {
            while((p[j]-q)*(p[k]-q)<=0)
            {
                k++;
            }
            l = k-1-j;
            r = n-1-l;
            ans += s[l]+s[r];
        }
        printf("%I64d\n",1LL*n*(n-1)*(n-2)/6-ans/2);
        NEXT : continue;
    }
    return 0;
}
```


---

## 作者：Dimly_dust (赞：0)

Zuo的我开始写这道题时想到了在前天看到的，结构体什么重载的。

> ``operator +(const P &a)const``



------------

**开始切入正题：**

楼上也说了，几何题。

即求：**要求点能被多边形中选出的三角形包含的个数。** 

这个需要考虑其对立面，总数减去不包含的个数。（ps 题解真心强）

**思路：**

不包含的个数的话，以一个点$A$为初始点。

顺时针找到$B$ ，$AB$形成的直线在$p$的右侧，此时构成的三角形个数为（$A$与下面$k$个点中选$2$个构成的三角形的个数），扫一圈，就可求出不包含的。

```
#include<stdio.h>
#include<iostream>
#include<math.h>
#include<string.h>
using namespace std;
#define eps 1e-8
#define ll __int64//这个跟__int128是一个东西
int sig(double x) {return (x>eps)-(x<-eps);}
struct P
{
    double x,y;
    P(double a=0,double b=0):x(a),y(b){}
    P operator +(const P &a)const{
        return P(x+a.x,y+a.y);
    }
    P operator -(const P &a)const{
        return P(x-a.x,y-a.y);
    }
    P operator *(const double &a)const{
        return P(x*a,y*a);
    }
    P operator /(const double &a)const{
        return P(x/a,y/a);
    }
    double operator *(const P &a)const{
        return (x*a.x+y*a.y);
    }
    double operator ^(const P &a)const{
        return (x*a.y-y*a.x);
    }
};
P p[100100];
int main()
{
    ll n;
    while(scanf("%I64d",&n)!=EOF)
    {
        for(int i=0;i<n;i++)
            scanf("%lf%lf",&p[i].x,&p[i].y);
        p[n]=p[0];
        int t;
        scanf("%d",&t);
        while(t--)
        {
            P q;
            scanf("%lf%lf",&q.x,&q.y);
            int flag=0;
            for(int i=0;i<n;i++)
            {
                if(sig((p[i]-q)^(p[i+1]-q))<=0)
                    flag++;
            }
            //printf("%d\n",flag);
            if(flag!=n)
            {
                printf("0\n");
                continue;
            }
            ll num;
            ll sum=(n*(n-1)*(n-2))/6;
            int j=0;
            for(int i=0;i<n;i++)
            {
                if(i==0) num=0;
                else num=(num-1);
                while(sig((p[i]-q)^(p[j]-q))<=0)
                {
                    if(j!=i)
                    {num++;}
                    j=(j+1)%n;
                }
                //printf("%I64d  %d\n",num,j);
                sum-=(num*(num-1)/2);
            }
            printf("%I64d\n",sum);
        }
    }
    return 0;
}

```




---

