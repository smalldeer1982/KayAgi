# [USACO10OPEN] Triangle Counting G

## 题目描述

Bessie is standing guard duty after

the big bad wolf was spotted stalking

```cpp
cows over at Farmer Don's spread. 
Looking down from her guard tower in 
utter boredom, she's decided to 
perform intellectual exercises in 
```
order to keep awake.
After imagining the field as an X,Y

grid, she recorded the coordinates of

the N (1 <= N <= 100,000) 

conveniently numbered 1..N cows as

```cpp
X_i,Y_i (-100,000 <= X_i <= 100,000; 
-100,000 <= Y_i <= 100,000; 1 <= i <= 
N). She then mentally formed all possible triangles that could be made from subsets of the entire set of cow coordinates. She counts a triangle as 'golden' if it wholly contains the origin (0,0). The origin does not fall on the line between any pair of cows. Additionally, no cow is standing exactly on the origin. 
Given the list of cow locations, calculate the number of 'golden' triangles that contain the origin so Bessie will know if she's doing a good job. 
```
By way of example, consider 5 cows at these locations:
-5,0   0,2   11,2   -11,-6   11,-5

Below is a schematic layout of the field from Betsy's point of view:

```cpp
............|............ 
............*..........*. 
............|............ 
-------*----+------------ 
............|............ 
............|............ 
............|............ 
............|............ 
............|..........*. 
.*..........|............ 
............|............ 
```
All ten triangles below can be formed from the five points above:

By inspection, 5 of them contain the origin and hence are 'golden'.

在一只大灰狼偷偷潜入Farmer Don的牛群被群牛发现后，贝西现在不得不履行着她站岗的职责。从她的守卫塔向下瞭望简直就是一件烦透了的事情。她决定做一些开发智力的小练习，防止她睡着了。



想象牧场是一个X，Y平面的网格。她将N只奶牛标记为1…N (1 <= N <= 100,000)，每只奶牛的坐标为X\_i,Y\_i (-100,000 <= X\_i <= 100,000;-100,000 <= Y\_i <= 100,000; 1 <= i <=N)。然后她脑海里想象着所有可能由奶牛构成的三角形。如果一个三角形完全包含了原点(0,0)，那么她称这个三角形为“黄金三角形”。原点不会落在任何一对奶牛的连线上。另外，不会有奶牛在原点。

给出奶牛的坐标，计算出有多少个“黄金三角形”。


## 样例 #1

### 输入

```
5 
-5 0 
0 2 
11 2 
-11 -6 
11 -5 
```

### 输出

```
5 
```

# 题解

## 作者：xtx1092515503 (赞：9)

不需要容斥的做法。

------------

我们考虑三个点构成的三角形包含原点，当且仅当其按照逆时针排序后，两两间夹角小于 $180^\circ$。

于是我们考虑将所有点按照极角排序，对于每个三角形，我们会在其三个点中最先在序列中出现的那一个处对其加以统计。

我们考虑用two-pointers预处理出来 $far_i$ 表示对于位置 $i$ 的点，排在其后面的所有点中第一个与其夹角 $\geq 180^\circ$ 的点是哪一个。则以 $i$ 作为第一个点的所有三角形，其第二个点 $j$ 必须 $\in(i,far_i)$，第三个点 $k$ 必须 $\in[far_i,n]$。

然后我们还发现，因为 $j,k$ 的夹角也必须 $<180^\circ$，所以 $k$ 的范围实际上是 $[far_i,far_j)$。

所以我们就要求出如上文所述的 $i,j,k$ 三元组数量。即

$$\sum\limits_{i=1}^n\sum\limits_{j=i+1}^{far_i-1}\sum\limits_{k=far_i}^{far_j-1}$$

于是

$$\sum\limits_{i=1}^n\sum\limits_{j=i+1}^{far_i-1}far_j-far_i$$

所以

$$\sum\limits_{i=1}^n\Big(\sum\limits_{j=i+1}^{far_i-1}far_j\Big)-(far_i-i-1)far_i$$

然后 $far_j$ 的区间和直接前缀和一下即可简单计算上式。

时间复杂度 $O(n\log n)$，瓶颈在于排序。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const double pi=acos(-1);
ll res;
int n,far[100100];
ll sum[100100];
struct Vector{
	double x,y;
	Vector(){}
	Vector(double X,double Y){x=X,y=Y;}
	friend Vector operator +(const Vector &u,const Vector &v){return Vector(u.x+v.x,u.y+v.y);}
	friend Vector operator -(const Vector &u,const Vector &v){return Vector(u.x-v.x,u.y-v.y);}
	friend Vector operator *(const Vector &u,const double &v){return Vector(u.x*v,u.y*v);}
	friend Vector operator /(const Vector &u,const double &v){return Vector(u.x/v,u.y/v);}
	friend double operator &(const Vector &u,const Vector &v){return u.x*v.y-u.y*v.x;}//cross times
	friend double operator |(const Vector &u,const Vector &v){return u.x*v.x+u.y*v.y;}//point times
	double operator ~()const{return sqrt(x*x+y*y);}//the modulo of a vector
	double operator !()const{return atan2(y,x);}//the angle of a vector
	friend bool operator <(const Vector &u,const Vector &v){return !u<!v;}
	void read(){scanf("%lf%lf",&x,&y);}
	void print(){printf("(%lf,%lf)",x,y);}
}p[100100];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)p[i].read();
	sort(p+1,p+n+1);
	for(int i=1;i<=n;i++){
		far[i]=max(far[i-1],i);
		while(far[i]<=n&&!p[far[i]]-!p[i]<pi)far[i]++;
	}
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+far[i];
	for(int i=1;i<=n;i++)res+=sum[far[i]-1]-sum[i-1]-1ll*(far[i]-i)*far[i];
	printf("%lld\n",res);
	return 0;
}
```

---

## 作者：yzhang (赞：3)

[更好的阅读](https://www.cnblogs.com/yzhang-rp-inf/p/11160803.html)

[原题传送门](https://www.luogu.org/problemnew/show/P2992)

我们考虑进行容斥

包含原点的三角形个数=所有可能三角形的个数-不包含原点三角形的个数

对于每个点，我们会发现：将它与原点连线，在直线左边任选两点或右边任选两点与这个点构成的三角形一定是不包含原点的

对于每个点都这样计算，累加，会发现有算重复的（但不会少情况，自己画画图就民白了），所以每次只选这个点向量的半平面上的两个点

这样我们珂以对所有点进行极角排序，这样就珂以做到线性

代码中有几点要注意：1.特判点数小于3   $\quad$  2.~~long long~~

```cpp
#include <bits/stdc++.h>
#define db double
#define ll long long 
#define N 100005 
#define getchar nc
using namespace std;
inline char nc(){
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
inline int read()
{
    register int x=0,f=1;register char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
    return x*f;
}
inline void write(register ll x)
{
    if(!x)putchar('0');if(x<0)x=-x,putchar('-');
    static int sta[20];register int tot=0;
    while(x)sta[tot++]=x%10,x/=10;
    while(tot)putchar(sta[--tot]+48);
}
const db Pi=acos(-1.0);
const db eps=1e-10;
struct point{
    int x,y;
    db k;
    inline void cal()
    {
        k=atan2(y,x);
    }
    bool operator <(const point &b) const{
        return k<b.k;
    }
}p[N<<1];
int n,sum;
ll ans;
int main()
{
    n=read();
    for(register int i=1;i<=n;++i)
    {
        int x=read(),y=read();
        p[i]=(point){x,y};
        p[i].cal();
    }
    if(n==1||n==2)
    {
        puts("0");
        return 0;
    }
    ans=1ll*n*(n-1)*(n-2)/6;
    sort(p+1,p+1+n);
    for(register int i=n+1;i<=n<<1;++i)
        p[i]=p[i-n],p[i].k+=2*Pi;
    int l=0,r=0;
    for(register int i=1;i<=n;++i)
    {
        l=i+1;
        while(p[r+1].k+eps<p[i].k+Pi)
            ++r;
        ans-=1ll*(r-l+1)*(r-l)/2;
    }
    write(ans);
    return 0;
}
```

---

## 作者：Graphcity (赞：2)

我们把所有点分成 $x$ 轴上面和 $x$ 轴下面两个部分（$x$ 轴上的点分到上面），显然组成黄金三角形的三个点不可能全在上半或者全在下半，一定是一上两下或者两上一下。

先对上下两部分分别进行一次极角排序。

以两上一下为例（一上两下同理）：枚举下半部分的点，那么上半部分的两个点必然在连接它与原点的射线两边。设它的极角为 $\theta$，那么射线在 $x$ 轴上半部分的极角为 $\pi+\theta$，那么就可以二分出第一个极角比这条射线大的点 $P$。

设上半部分点数为 $s$，$P$ 的极角排名为 $k$，那么对答案的贡献就是 $(k-1)(s-k+1)$。

对每个点分别统计一次即可。时间复杂度 $O(n\log n)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/yrcupkpk.png)

```cpp
#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=1e5;
const double eps=1e-8,pi=acos(-1);

inline int fcmp(double a,double b)
{
	double c=a-b;
	return (fabs(c)<=eps)?0:(c<0)?-1:1;
} 
struct Point
{
	double x,y,ang;
	Point():x(0),y(0),ang(0){}
    Point(double X,double Y,double A):x(X),y(Y),ang(A){}
	inline double Len() {return x*x+y*y;}
}; typedef Point Vector;
bool operator<(Point a,Point b) {return a.ang<b.ang;}

int n,s[2]; ll ans;
Point P[Maxn+5],Pol[Maxn+5];
int st[Maxn+5],vis[Maxn+5],top;
Point v[2][Maxn+5];

int main()
{
    scanf("%d",&n);
	For(i,1,n) scanf("%lf%lf",&P[i].x,&P[i].y),P[i].ang=atan2(P[i].y,P[i].x);
    For(i,1,n)
    {
        if(fcmp(P[i].ang,0.0)>=0) v[0][++s[0]]=P[i];
        else v[1][++s[1]]=P[i];
    }
    sort(v[0]+1,v[0]+s[0]+1),sort(v[1]+1,v[1]+s[1]+1);
    For(i,1,s[0])
    {
        Point p=v[0][i]; double ang=p.ang-pi;
        int pos=lower_bound(v[1]+1,v[1]+s[1]+1,Point(0.0,0.0,ang))-v[1];
        ans+=1ll*(pos-1)*(s[1]-pos+1);
    }
    For(i,1,s[1])
    {
        Point p=v[1][i]; double ang=p.ang+pi;
        int pos=lower_bound(v[0]+1,v[0]+s[0]+1,Point(0.0,0.0,ang))-v[0];
        ans+=1ll*(pos-1)*(s[0]-pos+1);
    }
    printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：partychicken (赞：2)

## 计算几何

做法：

直接计算并不好做，我们考虑用总数减去不包含原点的三角形个数

统计每个点与原点连线所在直线左侧点的个数（右侧也可以），这些点任意两个都可以与基准点构成一个不包含原点的三角形。这样统计是不重不漏的，下文会给出证明

先给公式
$$ans=C_n^3-\sum C_k^2$$
其中$k$为半平面包含的点的个数，统计方法看代码。

来说一下不重不漏的证明：

考虑一个不包含原点的三角形，其三个顶点与顶点的连线分别为以下三种情况

- 另外两个顶点都在连线的左侧
- 另外两个顶点都在连线的右侧
- 另外两个顶点分别在连线两侧

因此，统计连线一侧的点即可做到不重不漏。

感觉好像没太讲明白的说。。。有问题可以私信我

代码不贴了，可以参考黄学长的 hzwer.com

---

## 作者：creation_hy (赞：1)

包含原点三角形的特性：每个点向 $O$ 连一条线，这条线会穿过另外两个点构成的直线。

那就简单了，直接容斥，枚举一个点，看有多少种方法再找两个点分别在这条线的同一边。

然后可能会重复嘛。不过把不符合的三角形三条线画出来，你会发现如果重复，也只会是一条线符合要求，一条线在另外两个点左边，一条线在另外两点右边。

那就固定一个方向就好了呀。

排序什么的可以用 $\operatorname{atan2}$。

注意要放两倍的点，因为排序后第一个点上方的一些点可能会把他算进去。直接 $a_{i+n}=a_i+2\pi$ 就好。

统计可以用双指针或者二分查找。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
const double pi = acos(-1);
int n;
struct node
{
    int x, y;
    inline bool operator<(const node &t) const
    {
        return atan2(y, x) < atan2(t.y, t.x);
    }
} a[N];
double val[N];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    if (n < 3)
    {
        cout << 0;
        return 0;
    }
    for (int i = 1; i <= n; i++)
        cin >> a[i].x >> a[i].y;
    sort(a + 1, a + 1 + n);
    ll ans = 1ll * n * (n - 1) * (n - 2) / 6;
    for (int i = 1; i <= n; i++)
        a[i + n] = a[i];
    for (int i = 1; i <= n; i++)
        val[i] = atan2(a[i].y, a[i].x), val[i + n] = val[i] + pi * 2;
    for (int i = 1, p = 1; i <= n; i++)
    {
        while (val[p] <= val[i] + pi)
            p++;
        p--;
        ans -= 1ll * (p - i) * (p - i - 1) / 2;
    }
    cout << ans;
    return 0;
}
```

---

## 作者：ACoder_ (赞：1)

计算几何+容斥

#原文

http://blog.csdn.net/fsahfgsadhsakndas/article/details/56678589

#题解

包含原点的三角形求起来貌似没什么捷径，复杂度会飚起。考虑不包含原点的三角形，我们枚举一个点，那么在它逆时针方向且小于180度的那些点中任意选两个构成的三角形（或线段）都是不过原点的。所以按极角排序，类似旋转卡壳的方法找那个最远点，当前点和最远的点(包含)中间夹着的那些点中选取两个的方案数就是答案，然后用C(n,3)减去这些数量。统计是O(N)的，排序还有一个NlogN，因此O(NlogN)是最后的复杂度。

#代码

```c++
//组合数、容斥 
#include <cstdio>
#include <algorithm>
#include <cmath>
#define eps 1e-8
#define maxn 100010
#define ll long long
using namespace std;
ll ans, N;
struct point
{
    ll x, y;
    double th;
}pt[maxn];
bool operator<(point p1, point p2){return p1.th<p2.th;}
ll operator*(point p1, point p2){return p1.x*p2.y-p2.x*p1.y;}
void input()
{
    ll i;
    scanf("%lld",&N);
    for(i=1;i<=N;i++)
        scanf("%lld%lld",&pt[i].x,&pt[i].y),pt[i].th=atan2(pt[i].y,pt[i].x);
    sort(pt+1,pt+N+1);
}
void work()
{
    ll i, j, t=0;
    ans=N*(N-1)*(N-2)/6;
    for(i=1,j=2;i<=N;i++,t--)
    {
        for(;pt[j]*pt[i]<0;j=j==N?1:j+1)t++;
        ans-=t*(t-1)/2;
    }
}
int main()
{
    input();
    work();
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：juju527 (赞：0)

### 计算几何

由于我们不太好算黄金三角型个数

我们考虑**总三角形数等于非黄金三角形数+黄金三角形数**

而总三角形数我们可以把三点共线的也算作一个三角形

最后算非黄金三角形时把三点共线算进去就能减掉了

总三角形数$n\times(n-1)\times(n-2)/6$

![](https://cdn.luogu.com.cn/upload/image_hosting/1b763vg9.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

看到上图

我们对于每一个点向原点连一条直线

由题，这条直线上没有第二个点

显然，直线左/右边的点与该点构成的三角形一定是非黄金三角形

而对于一个非黄金三角形，它一定会在自己的某个顶点与原点构成的直线的左/右边

但我们每次都算左右边会有重复

我们每次只算一边即可

而对于统计直线的某一边有多少点，我们可以极角排序

极角排序后得到点数是单调

时间复杂度$O(nlogn)$

注意点数较大，要开long long

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=100005;
struct point{
	int x,y;
	point operator -(point i)const{
		point ans;
		ans.x=x-i.x;ans.y=y-i.y;
		return ans;
	}
}a[maxn];
int read(){
	int x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x*y;
}
int cross(point p,point q){
	return p.x*q.y-q.x*p.y;
}
int position(point p){
	if(p.x>=0&&p.y>0)return 1;
	if(p.x<0&&p.y>=0)return 2;
	if(p.x<=0&&p.y<0)return 3;
	if(p.x>0&&p.y<=0)return 4;
}
bool cmp(point p,point q){
	int pos1=position(p),pos2=position(q);
	return pos1==pos2?(cross(p,q)==0?p.x<q.x:cross(p,q)>0):pos1<pos2;
}
signed main(){
	int n,ans;
	n=read();
	ans=n*(n-1)*(n-2)/6;
	for(int i=1;i<=n;i++){
		a[i].x=read();
		a[i].y=read();
	}
	sort(a+1,a+n+1,cmp);
	a[n+1]=a[1];
	int pos=1,num=0;
	for(int i=1;i<=n;i++){
		while(cross(a[i],a[pos+1])>0){
			pos=(pos==n?1:pos+1);
			num++;
		}
		ans-=num*(num-1)/2;
		num--;
	}
	printf("%lld",ans);
	return 0;
}

```

---

