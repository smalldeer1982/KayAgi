# Spaceship Exploration

## 题目描述

在 ICPC 银河中，存在一个充满小行星的区域，进入该区域是不安全的。银河的地图用二维笛卡尔坐标系表示。该区域的形状是一个 $N$ 边的凸多边形。每个顶点编号为 $1$ 到 $N$，第 $i$ 个顶点的坐标为 $(X_i, Y_i)$。在任何时刻，你都不能处于该多边形内部；但是，接触多边形的边是安全的。

有 $Q$ 个场景（编号为 $1$ 到 $Q$）。在第 $j$ 个场景中，你需要从起点 $(A_j, B_j)$ 前往终点 $(C_j, D_j)$。你将驾驶一艘只能沿直线飞行的特殊飞船。首先，你设定飞船的方向，然后飞船会沿该方向前进。在飞行过程中，你最多只能改变一次方向。改变方向意味着你停下飞船，设定一个新方向，然后继续沿新方向前进。

对于每个场景，判断在任何时刻都不进入该区域的情况下，所需的最小飞行距离，或者报告无法到达终点。

## 说明/提示

样例输入输出 #1 说明

该样例如下图所示。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906D/3b577bd1075a31373238167ad213c432f7146baa.png)

在场景 $1$ 和 $4$ 中，你可以直接到达终点，无需改变方向。

在场景 $2$ 中，你可以先到 $(0, 2)$，然后改变方向前往终点。

在场景 $3$ 中，你可以先到 $(6, 2)$，然后改变方向前往终点。

在场景 $5$ 中，可以证明无法到达终点。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
0 2
2 0
4 0
4 4
2 4
5
6 1 6 3
2 5 0 0
3 5 3 -1
1 4 5 4
3 4 3 0```

### 输出

```
2
5.6055512755
8.48528137422
4
-1```

## 样例 #2

### 输入

```
4
-10 -9
10 -9
10 9
-10 9
2
0 10 0 -10
-10 -10 -10 -10```

### 输出

```
200.9975124224
0```

## 样例 #3

### 输入

```
8
-20 -10
10 -20
25 -15
35 -5
30 10
15 20
-25 15
-30 5
6
-15 -15 -15 20
-30 -5 30 15
25 20 -5 -20
-5 25 20 -20
-30 10 30 -10
-30 -50 50 0```

### 输出

```
59.0857761929
103.2455532034
94.7213595500
101.5640991922
164.8528137424
94.3398113206```

# 题解

## 作者：江户川·萝卜 (赞：1)

纯计算几何，思路简单，代码好写好拉板子，评绿差不多。

---

### Translation
给定一个 $n$ 个点的凸包 $C$，$q$ 次询问，每次给定 $A(x_1,y_1),B(x_2,y_2)$，找到一个点 $Z$，使得 $AZ,BZ$ 不与凸包内部有交且 $AZ+ZB$ 最小。输出这个最小值。

$n,q\le 10^5$，所有坐标绝对值 $\le 10^9$。

### Solution

首先发现一个性质，这个路径的形式只有以下几种形式：

- 线段 $AB$ 不与凸包内部有交，则即为 $AB$。这是显然的。

- 如果有交，那么就假设 $A$ 与 $C$ 的切线和 $B$ 与 $C$ 的切线交于若干个点 $P_i$，那么肯定是形如 $AP_i - P_iB$ 的折线。选其中最短的一条。

> 证明不难。

>反证法，假设存在一条路径使得 $A,B$ 其中一点连接的线段不与 $C$ 相切比上述构造出来的路径要短，那么显然能通过旋转这个线段使其与 $C$ 相切，这样的路径更短，矛盾。

那么我们就依次考虑如何实现。

### Part I

首先要求的是一个点与凸包的切线。

由于题目答辩的数据范围，我们只能考虑 $O(\log n)$ 的算法，比如二分。

这里上切线和下切线的求法本质相同，我们只讲上切线。

也就是说我们要找对于一个点来说，凸包上最右端的点，此处的“右”由叉积定义。

二维的东西颅内构想很困难，刻画一个函数 $f(x)$，对于任意 $i< j$，$f(i)>f(j)$ 当且仅当 $P_i$ 在 $P_j$ 右边，否则 $f(i)<f(j)$。

作出图像无非就两种：

![](https://cdn.luogu.com.cn/upload/image_hosting/siw8dh0k.png)

其中红点是 $ans$。

假设这幅图的左端是 $l$，右端是 $r$，中点 $m$，考察 $ans$ 在 $l \sim m$ 还是 $m+1 \sim r$。

首先我们可以通过判断 $P_l$ 是否在 $P_{l+1}$ 的右边来分辨是哪一种图的情况。

左图右图性质类似，考虑左图。

- 若 $f(m)>f(m+1)$。则 $m$ 在 $B$ 区间。

- 若 $f(m)<f(m+1)$。则 $m$ 在 $A$ 或 $C$ 区间。可以通过判断 $f(l)$ 与 $f(m)$ 的大小关系来分辨 $A$ 或 $C$。

> 这是由于整个图是一个凸包，所以不可能在转了一圈之后 $P_r$ 还在 $P_l$ 的右边。因此 $C$ 部分完全在 $l$ 左部。而 $A$ 部分显然在 $l$ 右部。

所以我们分辨出来 $m$ 在 $A,B,C$ 哪个区间了。继续分讨：

- $A$ 区间，$ans$ 在 $m+1\sim r$。

- $B,C$ 区间，$ans$ 在 $l\sim m$。

注意到我们把 $ans$ 归类到了 $B$ 区间所以这样是没问题的。

然后还有一个特殊情况就是 $ans=l$，注意每次二分开始特判。

### Part II

求两个射线的交点。这是容易的，求直线交然后判断该点是否在射线上即可。

### Part III

求一条线段（即线段 $AB$）是否与凸包内部有交。

同样还是 $O(\log n)$。考虑怎么沿用 Part I 中求出的切线。

假设切线是 $\overrightarrow{AX_1},\overrightarrow{AX_2},\overrightarrow{BY_1},\overrightarrow{BY_2}$，

那么结论是 $AB$ 与凸包内部有交当且仅当 $\overrightarrow{AB}$ 在 $\overrightarrow{AX_1}$ 和 $\overrightarrow{AX_2}$ 中间（不含两端）且 $\overrightarrow{BA}$ 在 $\overrightarrow{BY_1}$ 和 $\overrightarrow{BY_2}$ 中间（不含两端）。

这显然是必要的，考虑为什么是充分条件。

证明还是一张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/7ltez9tg.png)

$\overrightarrow{AB}$ 在范围内相当于 $X_1$ 或 $X_2$ 在绿色部分，$\overrightarrow{BA}$ 在范围内相当于 $Y_1$ 或 $Y_2$ 在蓝色部分。

若蓝色部分有点，那么 $X_1$ 或 $X_2$ 肯定不在 $B$ 右边的部分；若绿色部分有点，那么 $Y_1$ 或 $Y_2$ 就肯定不在 $A$ 左边的部分；

因此，我们说明了若满足条件，则蓝绿相交部分肯定有凸包顶点 $E$。下面对应有凸包顶点 $F$。$EF$ 显然与 $AB$ 相交。则证明完毕。

### 细节

在 Part I 和 Part II 中须全程使用 `long long` 计算，因为理论最大值在 $(2\times 10^9)^2\times2=8\times 10^{18}$。

否则可能会被类似 $x=-10^9+1\sim 10^9-1,y=-10^9\sim 10^9$ 的矩形卡精度。

然后在 Part I 部分的处理上还不够完全，需要考虑到若 $A$ 与凸包上顶点重合，则需选取该顶点前后的两个顶点作为切点，否则无法定射线的方向。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
struct vec{
    ll x,y;
    vec(ll _x=0, ll _y=0):x(_x),y(_y){}
    inline vec operator + (vec other){return vec(x+other.x,y+other.y);}
    inline vec operator - (vec other){return vec(x-other.x,y-other.y);}
    inline ll operator * (vec other){return x*other.x+y*other.y;}
    inline ll operator ^ (vec other){return x*other.y-y*other.x;}
    inline void print(){cout<<x<<' '<<y<<' ';}
};
inline db sq(db w){return w*w;}
inline db len(vec x){return sqrt(sq(x.x)+sq(x.y));}
constexpr db eps=1e-10;
int n,q;vec p[100005];
inline db cmax(db a,db b){
    if(fabs(a+1)<eps) return b;
    if(fabs(b+1)<eps) return a;
    return min(a,b);
}
inline bool chkrt(vec A,vec B,vec C){return ((B-A)^(C-A))<0;}
inline bool chkrrt(vec A,vec B,vec C){return !chkrt(A,C,B);}
struct node{
    ll x,y;int id;
    node(ll _x=0,ll _y=0,int _id=0):x(_x),y(_y),id(_id){}
    inline bool operator < (const node &other){return x==other.x?y<other.y:x<other.x;}
}z[100005];
pair<vec,vec> SolveCutPoint(vec A){
    // A.print();cout<<"-> ";
    int l=1,r=n,ans=-1;
    auto w=node(A.x,A.y,0);
    auto ww=*lower_bound(z+1,z+n+1,w);
    // cout<<ww.x<<' '<<ww.y<<' '<<ww.id<<'\n';
    if(A.x==ww.x&&A.y==ww.y){
        int k=ww.id;
        if(chkrt(A,p[k-1],p[k+1])) return make_pair(p[k+1],p[k-1]);
        else return make_pair(p[k-1],p[k+1]);
    }
    // for(int i=1;i<=n;i++) cout<<chkrt(A,p[i],p[i+1]);cout<<'\n';
    if(!chkrt(A,p[1],p[2])&&!chkrt(A,p[1],p[0])) ans=1;
    while(l<r){
        int m=l+r+1>>1;
        // cout<<l<<' '<<m<<' '<<r<<'\n';
        if(!chkrt(A,p[m],p[m+1])&&!chkrt(A,p[m],p[m-1])){ans=m;break;}
        if(chkrt(A,p[l],p[l+1])){
            if(!chkrt(A,p[m],p[m+1])) r=m-1;
            else if(chkrt(A,p[l],p[m])) l=m;
            else r=m-1;
        }
        else{
            if(chkrt(A,p[m],p[m+1])) l=m;
            else if(!chkrt(A,p[l],p[m])) l=m;
            else r=m-1;
        }
    }
    // for(int i=1;i<=n;i++) cout<<chkrrt(A,p[i],p[i+1]);cout<<'\n';
    int ansb=-1;l=1,r=n;
    if(chkrrt(A,p[1],p[2])&&chkrrt(A,p[1],p[0])) ansb=1;
    while(l<r){
        int m=l+r+1>>1;
        // cout<<l<<" "<<m<<' '<<r<<endl;
        if(chkrrt(A,p[m],p[m+1])&&chkrrt(A,p[m],p[m-1])){ansb=m;break;}
        if(!chkrt(A,p[l],p[l+1])){
            if(chkrt(A,p[m],p[m+1])) r=m-1;
            else if(!chkrt(A,p[l],p[m])) l=m;
            else r=m-1;
        }
        else{
            if(!chkrt(A,p[m],p[m+1])) l=m;
            else if(chkrt(A,p[l],p[m])) l=m;
            else r=m-1;
        }
    }
    assert(ans!=-1);
    assert(ansb!=-1);
    // p[ans].print();p[ansb].print();cout<<'\n';
    return make_pair(p[ans],p[ansb]);
}
inline int sgn(db x){
    if(fabs(x)<eps) return 0;
    if(x>0) return 1;
    return -1;
}
inline bool Mid(vec A,vec B,vec C,vec D){
    // A.print(),B.print(),C.print(),D.print();
    // cout<<(!chkrt(A,D,B))<<(!chkrt(A,C,D))<<'\n';
    return !chkrt(A,D,B)||!chkrt(A,C,D);
}
inline db Solvelen(vec Ax,vec Ay,vec Bx,vec By){
    // Ax.print();Ay.print();Bx.print();By.print();cout<<'\n';
    db Ak=(Ax.y-Ay.y)*1.0/(Ax.x-Ay.x);db Ab=Ax.y-Ax.x*Ak;
    db Bk=(Bx.y-By.y)*1.0/(Bx.x-By.x);db Bb=Bx.y-Bx.x*Bk;
    if(fabs(Ak-Bk)<eps) return -1;
    db X=(Bb-Ab)/(Ak-Bk);
    db Y=Ak*X+Ab;
    if(Ax.x==Ay.x){
        if(Bx.x==By.x) return -1;
        X=Ax.x;Y=Bk*X+Bb;
    }
    else if(Bx.x==By.x)X=Bx.x,Y=Ak*X+Ab;
    // cout<<Ak<<' '<<Ab<<' '<<Bk<<' '<<Bb<<' '<<X<<' '<<Y<<'\n';
    if(sgn(Ax.x-X)==sgn(Ay.x-Ax.x)&&fabs(Ax.x-X)>eps) return -1;
    if(sgn(Bx.x-X)==sgn(By.x-Bx.x)&&fabs(Bx.x-X)>eps) return -1;
    //vec w(X,Y);
    //Ax.print();Ay.print();Bx.print();By.print();w.print();cout<<'\n';
    return sqrt(sq(Ax.x-X)+sq(Ax.y-Y))+sqrt(sq(Bx.x-X)+sq(Bx.y-Y));
}
inline db solve(){
    vec A,B;cin>>A.x>>A.y>>B.x>>B.y;
    pair<vec,vec> p1=SolveCutPoint(A),p2=SolveCutPoint(B);
    if(Mid(A,p1.first,p1.second,B)||Mid(B,p2.first,p2.second,A)) return len(A-B);
    return cmax(cmax(Solvelen(A,p1.first,B,p2.first),Solvelen(A,p1.first,B,p2.second)),
                cmax(Solvelen(A,p1.second,B,p2.first),Solvelen(A,p1.second,B,p2.second)));
}
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n;
	for(int i=1;i<=n;i++){
		cin>>p[i].x>>p[i].y;
	}
    p[n+1]=p[1];p[0]=p[n];
    for(int i=1;i<=n;i++) z[i]=node(p[i].x,p[i].y,i);
    sort(z+1,z+n+1);
    cin>>q;while(q--){
        db ww=solve();
        printf("%.10lf\n",ww);
    }
}
```

目前在 CF 上最优解，[124ms](https://codeforces.com/contest/1906/submission/235650214)。

---

## 作者：OE_AiHAn (赞：0)

## [CF1906D](https://codeforces.com/problemset/problem/1906/D)

### 题意
给定一个 $n$ 个顶点的凸多边形，多次进行询问。每次询问给出两个不在多边形内的点 $P^1_j (A_j, B_j), P^2_j (C_j, D_j)$，问能否找到一个点 $P^3$，使线段 $P^1P^3, P^2P^3$ 不与凸多边形相交（可以相切），并求最短的 $|P^1P^3| + |P^2P^3|$。

### 解析
这题思路比较简单，但码量不小。

对于每次询问，先判断线段 $P^1P^2$ 是否与凸多边形相交，若不相交直接输出 $|P^1P^2|$ 即可；否则，可分别二分求 $P^1, P^2$ 的切线（各两条，为以 $P^1, P^2$ 为端点的射线），算出 $P^1$ 各条切线与 $P^2$ 切线的交点作为 $P^3$ 计算出 $\min\{|P^1P^3_i| + |P^2P^3_i|\}$ 作为答案，或者确认不存在这样一个交点 $P^3$。

对于二分求切线，如果点的横坐标不大于或不小于凸包上的任意点的横坐标，则把凸包分成上凸包和下凸包分别进行二分即可；否则，可按点的横坐标将凸包分割成左凸包和右凸包分别进行二分。

关于线段是否与凸多边形相交，将 $P^1, P^2$ 视作点光源，判断 $P^1$ 与 $P^2$ 光线的可见点集是否有交，若交集内有多于 1 个元素则线段不与凸包相交；或者如果交集内正好有 1 个元素点 $Z$，则可求 $\overrightarrow{P^1P^2} \times \overrightarrow{P^1Z}$ 或 $\overrightarrow{P^2P^1} \times \overrightarrow{P^2Z}$ 进行判断。

### 代码
```c++
#include <bits/stdc++.h>
#include <unordered_map>
#define LL long long
#define pii pair<int, int>
#define pll pair<LL, LL>
#define double long double
#define pdd pair<double, double>
#define eps 1e-9

using namespace std;

//直线
struct line
{
    pdd p, v;

    line(pll p, pll v)
    {
        this->p = (pdd)p;
        this->v = (pdd)v;
    }
};

pll operator + (pll l, pll r)
{
    return make_pair(l.first + r.first, l.second + r.second);
}

pll operator - (pll l, pll r)
{
    return make_pair(l.first - r.first, l.second - r.second);
}

//点乘，下同
LL dot(pll l, pll r)
{
    return l.first * r.first + l.second * r.second;
}

//叉乘，下同
LL cross(pll l, pll r)
{
    return l.first * r.second - l.second * r.first;
}

pdd operator + (pdd l, pdd r)
{
    return make_pair(l.first + r.first, l.second + r.second);
}

pdd operator - (pdd l, pdd r)
{
    return make_pair(l.first - r.first, l.second - r.second);
}

double dot(pdd l, pdd r)
{
    return l.first * r.first + l.second * r.second;
}

//求两点距离
double dis(pdd l, pdd r)
{
    return sqrt(dot(l - r, l - r));
}

double cross(pdd l, pdd r)
{
    return l.first * r.second - l.second * r.first;
}

//求直线交点
pdd getNode(line l, line r)
{
    double s1 = cross(l.v, r.p - l.p), s2 = cross(l.v, r.p + r.v - l.p);
    return make_pair((r.p.first * s2 - (r.p.first + r.v.first) * s1) / (s2 - s1), (r.p.second * s2 - (r.p.second + r.v.second) * s1) / (s2 - s1));
}

int n;
pll ps[200005], ps1[100005];
map<pll, int> mp;

//二分求切点
pair<pll, pll> getPT(pll p)
{
    pair<pll, pll> res;

    if (p.first <= ps1[1].first)
    {
        int l = mp[ps1[1]], r = mp[ps1[n]];
        if (r < l)
            r += n;
        while (l < r)
        {
            int mid = l + r >> 1;
            if (cross(ps[mid + 1] - ps[mid], ps[mid + 1] - p) < 0)
                r = mid;
            else
                l = mid + 1;
        }
        res.first = ps[l];

        l = mp[ps1[n]], r = mp[ps1[1]];
        if (r < l)
            r += n;
        while (l < r)
        {
            int mid = l + r >> 1;
            if (cross(ps[mid + 1] - ps[mid], p - ps[mid]) > 0)
                l = mid + 1;
            else
                r = mid;
        }
        res.second = ps[l];
    }
    else if (p.first >= ps1[n].first)
    {
        int l = mp[ps1[n]], r = mp[ps1[1]];
        if (r < l)
            r += n;
        while (l < r)
        {
            int mid = l + r >> 1;
            if (cross(ps[mid + 1] - ps[mid], ps[mid + 1] - p) < 0)
                r = mid;
            else
                l = mid + 1;
        }
        res.first = ps[l];

        l = mp[ps1[1]], r = mp[ps1[n]];
        if (r < l)
            r += n;
        while (l < r)
        {
            int mid = l + r >> 1;
            if (cross(ps[mid + 1] - ps[mid], p - ps[mid]) > 0)
                l = mid + 1;
            else
                r = mid;
        }
        res.second = ps[l];
    }
    else
    {
        if (cross(ps1[1] - p, p - ps1[n]) < 0 || !cross(ps1[1] - p, p - ps1[n]) && !cross(ps[mp[ps1[n]] + 1] - ps1[n], ps1[1] - ps1[n]))
        {
            int L = mp[ps1[n]], R = mp[ps1[1]];
            if (R < L)
                R += n;
            int div = lower_bound(ps + L, ps + R + 1, p, greater<pll>()) - (ps + L);

            int l = L + div, r = R;

            if (r < l)
                r += n;
            while (l < r)
            {
                int mid = l + r >> 1;
                if (cross(ps[mid + 1] - ps[mid], ps[mid + 1] - p) < 0)
                    r = mid;
                else
                    l = mid + 1;
            }
            res.first = ps[l];

            l = L, r = L + div - 1;
            if (r < l)
                r += n;
            while (l < r)
            {
                int mid = l + r >> 1;
                if (cross(ps[mid + 1] - ps[mid], p - ps[mid]) > 0)
                    l = mid + 1;
                else
                    r = mid;
            }
            res.second = ps[l];
        }
        else
        {
            int L = mp[ps1[1]], R = mp[ps1[n]];
            if (R < L)
                R += n;
            int div = lower_bound(ps + L, ps + R + 1, p) - ps - L;

            int l = L + div, r = R;
            if (r < l)
                r += n;
            while (l < r)
            {
                int mid = l + r >> 1;
                if (cross(ps[mid + 1] - ps[mid], ps[mid + 1] - p) < 0)
                    r = mid;
                else
                    l = mid + 1;
            }
            res.first = ps[l];

            l = L, r = L + div - 1;
            if (r < l)
                r += n;
            while (l < r)
            {
                int mid = l + r >> 1;
                if (cross(ps[mid + 1] - ps[mid], p - ps[mid]) > 0)
                    l = mid + 1;
                else
                    r = mid;
            }
            res.second = ps[l];
        }
    }

    return res;
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    int q;
    pll p0, p1;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> ps[i].first >> ps[i].second;
        ps1[i] = ps[n + i] = ps[i];
        mp[ps[i]] = i;
    }
    sort(ps1 + 1, ps1 + n + 1);

    cin >> q;
    while (q--)
    {
        cin >> p0.first >> p0.second >> p1.first >> p1.second;

        pair<pll, pll> res1 = getPT(p0), res2 = getPT(p1);

        double ans = 1e25; //初始值一定要开大
        int r1 = mp[res1.first], l1 = mp[res1.second], r2 = mp[res2.first], l2 = mp[res2.second];
        if (r1 < l1)
            r1 += n;
        if (r2 < l2)
            r2 += n;

        //判断线段是否与凸包相交
        if (!(l1 >= r2 || l2 >= r1))
            ans = dis(p0, p1);
        else if (l1 == r2 && cross(p0 - p1, ps[l1] - p1) >= 0)
            ans = dis(p0, p1);
        else if (l2 == r1 && cross(p1 - p0, ps[l2] - p0) >= 0)
            ans = dis(p0, p1);
        if (r1 > n && r2 <= n)
            l2 += n, r2 += n;
        else if (r2 > n && r1 <= n)
            l1 += n, r1 += n;
        if (!(l1 >= r2 || l2 >= r1))
            ans = dis(p0, p1);
        else if (l1 == r2 && cross(p0 - p1, ps[l1] - p1) >= 0)
            ans = dis(p0, p1);
        else if (l2 == r1 && cross(p1 - p0, ps[l2] - p0) >= 0)
            ans = dis(p0, p1);

        //求切线交点并计算答案
        if (cross(res1.first - p0, res2.first - p1))
        {
            pdd nd = getNode(line(p0, res1.first - p0), line(p1, res2.first - p1));
            if (dot((pdd)(res1.first - p0), nd - (pdd)p0) > eps && dot((pdd)(res2.first - p1), nd - (pdd)p1) > eps)
                ans = min(ans, dis(nd, p0) + dis(nd, p1));
        }
        if (cross(res1.first - p0, res2.second - p1))
        {
            pdd nd = getNode(line(p0, res1.first - p0), line(p1, res2.second - p1));
            if (dot((pdd)(res1.first - p0), nd - (pdd)p0) > eps && dot((pdd)(res2.second - p1), nd - (pdd)p1) > eps)
                ans = min(ans, dis(nd, p0) + dis(nd, p1));
        }
        if (cross(res1.second - p0, res2.first - p1))
        {
            pdd nd = getNode(line(p0, res1.second - p0), line(p1, res2.first - p1));
            if (dot((pdd)(res1.second - p0), nd - (pdd)p0) > eps && dot((pdd)(res2.first - p1), nd - (pdd)p1) > eps)
                ans = min(ans, dis(nd, p0) + dis(nd, p1));
        }
        if (cross(res1.second - p0, res2.second - p1))
        {
            pdd nd = getNode(line(p0, res1.second - p0), line(p1, res2.second - p1));
            if (dot((pdd)(res1.second - p0), nd - (pdd)p0) > eps && dot((pdd)(res2.second - p1), nd - (pdd)p1) > eps)
                ans = min(ans, dis(nd, p0) + dis(nd, p1));
        }

        if (ans >= 1e25)
            printf("-1\n");
        else
            printf("%.12LF\n", ans);
    }
}
```

个人写的太烂代码用了 700 多毫秒才过的 Orz

最后祝各位顺利AC。>w<

---

