# CLOSEST - Closest Triplet

## 题目描述

### 题意
多组询问，每组询问给出二维平面上的 $n$ 个点，在这 $n$ 个点中选出3个点，使这3个点两两之间的距离的和最小，输出这个最小距离。

## 说明/提示

$3 \le n \le 3000$

$1 \le x,y \le 10^6$

## 样例 #1

### 输入

```
\n4\n1 1\n4 1\n1 5\n1000 1000\n9\n100000 200000\n200000 200000\n150000 286603\n60000 140000\n240000 140000\n150000 340000\n1 340000\n300000 340000\n150000 87087\n-1\n\n```

### 输出

```
12.000\n300000.796```

# 题解

## 作者：nr0728 (赞：28)

我们充分发扬人类智慧：

- 将所有点全部按 $x$ 坐标排序。
- 根据数学直觉，答案中的三个点在数组中肯定不会离得太远。
- 所以我们只枚举两个点，第三个点取向前的 $5$ 个点来计算答案。

这样速度快得飞起，在 $n=3000$ 时都可以在 2.5s 内卡过。

```cpp
int n;
struct node
{
	int x,y;
} a[3001];
double ans=9e18;
inline int pw(int val)
{
	return val*val;
}
inline double dist(int x,int y)
{
	return sqrt(pw(a[x].x-a[y].x)+pw(a[x].y-a[y].y));
}
signed main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	while(1)
	{
		ans=9e18;
		read(n);
		if(n==-1) return 0;
		for(int i=1;i<=n;++i) read(a[i].x),read(a[i].y);
		sort(a+1,a+n+1,[](node x,node y){return x.x<y.x;});
		for(int i=1;i<=n;++i)
			for(int j=i+1;j<=n;++j)
				for(int k=j+1;k<=min(j+5,n);++k)
					ans=min(ans,dist(i,j)+dist(j,k)+dist(i,k));
		printf("%.3lf\n",ans);
	}
	return 0;
}
```

---

## 作者：找死刑 (赞：14)

[题目传送门](https://www.luogu.com.cn/problem/SP7209)

### 题意简述

多组询问，每组询问给出二维平面上的 $n$ 个点，选出 3 个点使这 3 个点两两之间的距离的和最小，求这个最小距离和。

### 题目解法

这道题看起来与[平面最近点对](https://www.luogu.com.cn/problem/P1429)很像，只是换成了三个点两两之间的距离和。

于是我们同样考虑用分治来求解。

与平面最近点对的流程一样，先按点的 $x$ 坐标排序，然后分治。

![](https://cdn.luogu.com.cn/upload/image_hosting/xlt0ozgv.png)

现在我们已经求出了左半边与右半边的答案，考虑求跨越分界线的三个点的答案。

设左右两边的答案的较小值为 $d$ ，即新的三个点的距离和必须 $\le d$。

首先考虑三个点中相距最远的两个点满足什么条件。

若三个点不共线，则他们构成一个三角形，由于三角形两边之和大于第三边，所以最长边的长度一定 $< \frac{d}{2}$。

若三个点共线，则三个点中最长的距离为 $\frac{d}{2}$。

综上，三个点中相距最远的两个点的距离 $\le \frac{d}{2}$。

那么仿照平面最近点对的做法，将距离分界线的距离小于等于 $\frac{d}{2}$ 的点拎出来，按 $y$ 坐标排序，然后枚举 3 个点，保证最大 $y$ 坐标与最小 $y$ 坐标之差小于等于 $\frac{d}{2}$ ，用枚举到的三个点更新答案即可。

可以证明上述枚举过程是常数级别的（我太菜了不会证）。

如果是在分治过程中用快排将拎出来的点排序，则时间复杂度为 $O(n \log^2n)$，若使用归并排序，则复杂度为 $O(n \log n)$。

我使用的是归并排序。

### 代码
```cpp
#include <bits/stdc++.h>
#define maxn 200005
#define mid ((l+r)>>1)
#define oo (1e18+5)
using namespace std;
struct Vec{double x,y;};
Vec operator - (Vec a,Vec b){return (Vec){a.x-b.x,a.y-b.y};}//向量减法
double dist(Vec a){return sqrt(a.x*a.x+a.y*a.y);}//求两点间距离，用了向量减法，其实与直接求一样 
bool cmp(Vec a,Vec b){return a.x<b.x;}//按x坐标排序 
Vec p[maxn],b[maxn],v[maxn];
double solve(int l,int r)
{
    if (l==r) return oo;//分治边界 
    double X=p[mid].x;//分界线 
    double d=min(solve(l,mid),solve(mid+1,r));//分治 
    int k=l-1,num=0;
    for (int i=l,j=mid+1;i<=mid||j<=r;)//归并排序 
    {
        if (j>r||(i<=mid&&p[i].y<p[j].y))
        {
            if (fabs(p[i].x-X)<=d/2) v[++num]=p[i];//拎出符合条件的点 
            b[++k]=p[i];i++;continue;
        }
        if (fabs(p[j].x-X)<=d/2) v[++num]=p[j];//拎出符合条件的点 
        b[++k]=p[j];j++;
    }
    for (int i=l;i<=r;i++) p[i]=b[i];//归并排序 
    for (int i=1;i<num-1;i++)//枚举3个点 
        for (int j=i+1;j<num&&v[j].y-v[i].y<=d/2;j++)
            for (int k=j+1;k<=num&&v[k].y-v[i].y<=d/2;k++)
                d=min(d,dist(v[i]-v[j])+dist(v[i]-v[k])+dist(v[j]-v[k]));//更新答案 
    return d;
}
int n;
int main()
{
    while(true)
    {
        scanf("%d",&n);
        if (n==-1) break;
        for (int i=1;i<=n;i++) scanf("%lf%lf",&p[i].x,&p[i].y);
        sort(p+1,p+1+n,cmp);//按x坐标排序 
        printf("%.3lf\n",solve(1,n));
    }
    return 0;
}
```

---

## 作者：tjtdrxxz (赞：13)

题目要我们求出 $n$ 个点中两两间距离最小的 $3$ 个点，很明显，最简单的情况就是折现点在一条直线上，所以可以想到人类智慧的雏形——找几个直线，去把这些点都分到每个直线上。

好，那既然要旋转点，那我们直接全转吧！

所以人类智慧就此诞生，我们把所有点一起旋转一个角度，然后按 $x \times y$ 排序（用别的会得到高贵的红色 WA）。

其中，一个点绕原点旋转 $\alpha$ 度后他的位置是的公式是：

$$
(x \times \cos (\alpha) - y \times \sin (\alpha),x \times \sin (\alpha) + y * \cos (\alpha))
$$

注意，在 C++ 中，三角函数不是按角度计算的而是弧度，所以还要给角度乘上一个 $\pi$。

好，那么万事俱备，code:

```cpp
# include "bits/stdc++.h"
using namespace std;
int n;
struct node
{
	long double x, y;
	bool operator <(const node &other) const
	{
		return x > other.x;
	}
}a[200012];
long double ans;
long double solve (long double x1, long double y1, long double x2, long double y2)
{
	return sqrt ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
void turn (long double x)
{
	x = x / 180.0 * 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;
	for (int i = 1; i <= n; i ++)
	{
		long double tx, ty;
		tx = a[i].x * cos (x) * 1.0 - a[i].y * sin (x) * 1.0;
		ty = a[i].x * sin (x) * 1.0 + a[i].y * cos (x) * 1.0;
		a[i].x = tx;
		a[i].y = ty;
	}
	sort (1 + a, 1 + a + n/*, cmp*/);
	for (int i = 1; i <= n; i ++)
	for (int k = i + 1; k <= n; k ++)
	{
		for (int j = k + 1; j <= k + 6 and j <= n; j ++)
		{
			ans = min (ans, solve (a[i].x, a[i].y, a[j].x, a[j].y) + solve (a[i].x, a[i].y, a[k].x, a[k].y) + solve (a[j].x, a[j].y, a[k].x, a[k].y));
		}
	}
}
int main ()
{
	while (~scanf ("%d", &n))
	{
		if (n == -1) break;
		ans = 9e18;
		for (int i = 1; i <= n; i ++)
		{
			long double x, y;
			scanf ("%Lf %Lf", &x, &y);
			a[i].x = x, a[i].y = y;
		}
		turn (0);
		printf ("%.3Lf\n", ans);
	}
}
```

---

## 作者：fish_love_cat (赞：11)

我们充分发扬人类智慧：

将所有点全部绕原点旋转同一个角度，然后按 $x \times y$ 排序。

根据数学直觉，在随机旋转后，答案中的三个点在数组中肯定不会离得太远。

所以我们只取每两个点向后的 $5$ 个点来计算答案。

这样速度快得飞起，在多测并且 $n=3000$ 时都可以在 $37.47$ 秒内卡过。

---

## 作者：light_searcher (赞：1)

先把所有点按 $x$ 排序。然后对于中线左右两边的点直接分治求答案即可。接下来考虑如何跨中线合并。设左右两边得到的答案为 $d$，根据三角形两边之和大于第三边易知，如果当前三个点能够更新答案，任意两点间的距离都要小于 $\frac{d}{2}$，那么我们可以把到中线距离小于 $\frac{d}{2}$ 的点全部选出来，然后按照 $y$ 排序，然后对于每一个选出的点，枚举出另外两个点，使得最大的 $y$ 与最小的 $y$ 的差小于 $\frac{d}{2}$，同时更新 $d$，时间复杂度是 $\mathcal O(n \log^2 n)$，用归并排序可以少一个 $\log$。

至于为什么这样枚举时间复杂度是对的，我水平有限，不会严谨的证明，只能感性证明。往一个 $\frac{d}{2} \times \frac{d}{2}$ 的正方形中放一些点，使得任取三点两两之间距离的和大于等于 $d$，这样的点的个数是很少的。所以符合要求的点也是很少的，枚举就是线性的。

~~有没有大神会严谨证明啊，教教我吧！~~

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e3+5;
int n;
struct point{
	double x,y;
}a[N],b[N];
bool cmp1(point a,point b){
	if(a.x!=b.x) return a.x<b.x;
	return a.y<b.y;
}
bool cmp2(point a,point b){
	return a.y<b.y;
}
double dis(point a,point b){
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
double solve(int l,int r){
	if(l==r||l+1==r) return 1e13;
	if(l+1==r-1) return dis(a[l],a[l+1])+dis(a[l],a[r])+dis(a[r-1],a[r]);
	int mid=(l+r)/2,cnt=0;
	double d=min(solve(l,mid),solve(mid+1,r));
	for(int i=l;i<=r;i++)
		if(fabs(a[mid].x-a[i].x)<d/2) 
			b[++cnt]=a[i];
	sort(b+1,b+cnt+1,cmp2);
	for(int i=1;i<cnt-1;i++)
		for(int j=i+1;j<cnt&&b[j].y-b[i].y<d/2;j++)
			for(int k=j+1;k<=cnt&&b[k].y-b[i].y<d/2;k++)
				d=min(d,dis(b[i],b[j])+dis(b[j],b[k])+dis(b[i],b[k]));
	return d;
}
int main(){
	while(~scanf("%d",&n)&&~n){
		for(int i=1;i<=n;i++) scanf("%lf%lf",&a[i].x,&a[i].y);
		sort(a+1,a+n+1,cmp1);
		printf("%.3f\n",solve(1,n));
	}
	return 0;
}

---

## 作者：mlvx (赞：1)

### 题意

给出 $n$ 个点，选出三个，使得这三个点两两距离之和最小，求出这个距离之和。

### 分析

类似平面最近点对的做法，进行分治。一段区间内的答案即左区间、右区间，以及跨区间的答案，三者取最小值即可。

显然的，跨区间的三点必须满足其 $x$ 坐标与最中间那个点的 $x$ 坐标差小于左右区间最小值的一半。

为什么呢？

因为三角形两边之和大于第三边，所以最长边小于周长的一半。

在这些点中按 $y$ 坐标排序，就可以直接枚举三点，使得两两 $y$ 坐标之差小于左右区间最小值的一半，那么这些点就是可能可以计入答案的。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define db double
const int N=2e5+10;
int n,b[N];pair<int,int>a[N];
db dis(pair<int,int>a,pair<int,int>b){
	return sqrt(1ll*(a.first-b.first)*(a.first-b.first)+1ll*(a.second-b.second)*(a.second-b.second));
}db solve(int l,int r){
	if(r-l<=2)return r-l==2?dis(a[l],a[l+1])+dis(a[l+1],a[r])+dis(a[l],a[r]):9e18;
	int mid=l+r>>1,cnt=0;db ret=min(solve(l,mid),solve(mid+1,r));
	for(int i=l;i<=r;i++)if(abs(a[mid].first-a[i].first)<ret/2)b[++cnt]=i;
	sort(b+1,b+cnt+1,[](int x,int y){return a[x].second<a[y].second;});
	for(int i=1;i<=cnt;i++)
		for(int j=i+1;j<=cnt&&a[b[j]].second-a[b[i]].second<ret/2;j++)
			for(int k=j+1;k<=cnt&&a[b[k]].second-a[b[i]].second<ret/2;k++)
				ret=min(ret,dis(a[b[i]],a[b[j]])+dis(a[b[i]],a[b[k]])+dis(a[b[j]],a[b[k]]));
	return ret;
}int main(){
	while(cin>>n){
		if(n==-1)break;
		for(int i=1;i<=n;i++)cin>>a[i].first>>a[i].second;
		sort(a+1,a+n+1,[](pair<int,int>a,pair<int,int>b){return a.first<b.first;});
		printf("%.3lf\n",solve(1,n));
	}return 0;
}
```

---

## 作者：Fa_Nanf1204 (赞：0)

### 前置题目：
[P7883 平面最近点对（加强加强版）](https://www.luogu.com.cn/problem/P7883)。
### 分析：
依照平面最近点对的思路，我们来写这一题。

还是一样的分治思路，主要来讲一下左右两端的合并方法。首先讨论一下三点的位置关系，如果不在一条直线上，那么构成一个三角形，三角形两边之和大于第三边，所以最长的边小于当前答案除以 $2$。如果在一条直线上，则最长的边小于等于当前答案除以 $2$。所以只需要筛选小于等于当前答案除以 $2$ 的边就行了。其他方法与前置题目一样，就不过多赘述。

时间复杂度的证明与前置题目类似，只不过是多选了几个点而已，算上排序的时间复杂度，所以最后是 $O(n\log^2n)$。
### Code:

```cpp
#include<bits/stdc++.h>
#define N 3005
#define ll long long
#define D double
using namespace std;
struct node{
	ll x,y;
}e[N],L[N],R[N];
int n;
inline bool cmpx(node x,node y){
	return x.x<y.x;
}
inline bool cmpy(node x,node y){
	return x.y<y.y;
}
inline D get(node a,node b,node c){
	return sqrt(1ll*(a.x-b.x)*(a.x-b.x)+1ll*(a.y-b.y)*(a.y-b.y))+
		   sqrt(1ll*(a.x-c.x)*(a.x-c.x)+1ll*(a.y-c.y)*(a.y-c.y))+
		   sqrt(1ll*(c.x-b.x)*(c.x-b.x)+1ll*(c.y-b.y)*(c.y-b.y));
}
D solve(int l,int r){
	if(l==r or l+1==r) return 9e18;
	if(l+2==r) return get(e[l],e[l+1],e[r]);
	int mid=l+r>>1;
	D ans=min(solve(l,mid),solve(mid+1,r));
	int cntl=0;
	for(int i=l;i<=r;i++){
		if(abs(e[mid].x-e[i].x)<ans/2){
			L[++cntl]=e[i];
		}
	}
	sort(L+1,L+cntl+1,cmpy);
	for(int i=1;i<=cntl;i++){
		for(int j=i+1;j<=cntl;j++){
			if(L[j].y-L[i].y>=ans/2) break;
			for(int k=j+1;k<=cntl;k++){
				if(L[k].y-L[i].y>=ans/2 or L[k].y-L[j].y>=ans/2) break;
				ans=min(ans,get(L[i],L[j],L[k]));
			}
		}
	}
	return ans;
}
int main(){
	while(cin>>n){
		if(n==-1) return 0;
		for(int i=1;i<=n;i++){
			scanf("%lld%lld",&e[i].x,&e[i].y);
		}
		sort(e+1,e+n+1,cmpx);
		printf("%.3lf\n",solve(1,n));
	}
	return 0;
} 
```

---

## 作者：Genius_Star (赞：0)

[**或许更好的阅读体验。**](https://www.cnblogs.com/rgw2010/p/18385936)

### 思路：

仿照**平面最近点对**思路，先按照横坐标排序，考虑分治。

对于分割线 $y=X$，考虑求跨过这条线的贡献，设 $d$ 为左边和右边分治结果的最小值，则这三点中最长边的长度必须 $\le \frac{d}{2}$，不然不会比 $d$ 更优。

则我们只需要考虑横坐标到分割线的距离 $\le \frac{d}{2}$ 的贡献，将这些点找出来，再按照纵坐标进排序，这里使用归并排序的话可以降一个 $\log$，但是没必要。

然后暴力枚举这 $3$ 个点，使得三个点的 $y$ 坐标的极差 $\le \frac{d}{2}$，然后计算贡献即可。

时间复杂度为 $O(N \log^2 N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define pi pair<ll,ll>
#define pii pair<ll,pair<ll,ll>>
#define iip pair<pair<ll,ll>,ll>
#define ppii pair<pair<ll,ll>,pair<ll,ll>>
#define fi first
#define se second
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define Full(a) memset(a,0,sizeof(a))
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
#define For(i,l,r) for(int i=l;i<=r;i++)
#define _For(i,l,r) for(int i=r;i>=l;i--)
using namespace std;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const ll N=2e5+10,INF=1e18;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
struct Point{
    db x,y;
    friend bool operator==(const Point &a,const Point &b){
        return a.x==b.x&&a.y==b.y;
    }
    friend db dis(const Point &a,const Point &b){
        return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
    }
}a[N];
ll n,sum;
namespace Sub1{
    db ans=INF;
    void work(){
        For(i,1,n)
          For(j,i+1,n)
            For(k,j+1,n)
              ans=min(ans,dis(a[i],a[j])+dis(a[j],a[k])+dis(a[i],a[k]));
        printf("%.3lf\n",ans);
    }
};
namespace Sub2{
    db ans=INF;
    bool cmp(Point &a,Point &b){
        return a.x<b.x;
    }
    void work(){
        sort(a+1,a+n+1,cmp);
        For(i,1,n-2)
          ans=min(ans,dis(a[i],a[i+1])+dis(a[i+1],a[i+2])+dis(a[i],a[i+2]));
        printf("%.3lf\n",ans);
    }
};
namespace Sub3{
    ll cnt=0;
    Point b[N];
    db ans=INF;
    bool cmp1(Point &a,Point &b){
        if(a.x!=b.x)
          return a.x<b.x;
        return a.y<b.y;
    }
    bool cmp2(Point &a,Point &b){
        if(a.y!=b.y)
          return a.y<b.y;
        return a.x<b.x;
    }
    db solve(ll l,ll r){
        if(l==r)
          return INF;
        ll mid=(l+r)>>1;
        ll I=a[mid].x;
        db d=min(solve(l,mid),solve(mid+1,r));
        cnt=0;
        For(i,l,r)
          if(abs(a[i].x-I)<=d/2)
            b[++cnt]=a[i];
        sort(b+1,b+cnt+1,cmp2);
        For(i,1,cnt){
            For(j,i+1,cnt){
                if(b[j].y-b[i].y>d/2)
                  break;
                For(k,j+1,cnt){
                    if(b[k].y-b[i].y>d/2)
                      break;
                    d=min(d,dis(b[i],b[j])+dis(b[i],b[k])+dis(b[j],b[k]));
                }
            }
        }
        return d;
    }
    void work(){
        sort(a+1,a+n+1,cmp1);
        printf("%.3lf\n",solve(1,n));
    }
};
int main(){
    while(1){
        n=read();
        if(n==-1)
          break;
        For(i,1,n){
            a[i]={(db)read(),(db)read()};
            sum+=a[i].y;
        }
        if(n<=100)
          Sub1::work();
        else if(!sum)
          Sub2::work();
        else
          Sub3::work();
    }
    return 0;
}
```

---

