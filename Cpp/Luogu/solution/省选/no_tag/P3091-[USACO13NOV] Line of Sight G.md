# [USACO13NOV] Line of Sight G

## 题目描述

Farmer John's N cows (1 <= N <= 50,000) are located at distinct points in his two-dimensional pasture.  In the middle of the pasture is a large circular grain silo.  Cows on opposite sides of the silo cannot see each-other, since the silo blocks their view.  Please determine the number of pairs of cows that can see each-other via a direct line of sight.

The grain silo is centered at the origin (0,0) and has radius R.  No cow is located on or inside the circle corresponding to the silo, and no two cows lie on a tangent line to the silo.  The value of R is in the range 1..1,000,000, and each cow lives at a point with integer coordinates in the range -1,000,000..+1,000,000.

给定平面上的 $N$ 个点，求有多少点对能互相看见而不被以原点为圆心，$R$ 为半径的圆挡住。

题目保证不存在圆上或圆内的点，也不存在连接两点的线段为圆的切线。

$1\le N\le50000$

$1\le R\le10^6$ 

$|x|,|y|\le10^6$

## 说明/提示

There are 4 cows at positions (0,10), (0,-10), (10,0), and (-10,0).  The silo is centered at (0,0) and has radius 5.


All 6 pairs of cows can see each-other, except for the pairs situated on opposite sides of the silo: the cows at (-10,0) and (10,0) cannot see each-other, and the cows at (0,-10) and (0,10) cannot see each-other.


## 样例 #1

### 输入

```
4 5 
0 10 
0 -10 
10 0 
-10 0 
```

### 输出

```
4 
```

# 题解

## 作者：Thomasguo666 (赞：5)

# 神仙数学题

事实上，我们可以对每头牛向谷仓做切线。记第$i$头牛向谷仓做切线的两个切点在这头牛这侧所加的弧为$l_i$

那么如果第$i$头牛和第$j$头牛可以互相看到，则$l_i$和$l_j$有交点。

于是接下来我们要解决两个问题：即如何表示和计算这$n$个弧，以及如何求出这$n$个弧中有多少对弧相交。

注意到圆心在$(0,0)$处，所以我们可以用一个弧的两个端点与原点的连线与$x$轴正半轴的夹角表示这个弧。

下规定小的角度为左端点，大的角度为右端点。

我们可以先求出牛与原点的连线与$x$轴正半轴的夹角$\angle AOB$，然后再计算两个端点与原点的连线与牛与原点的连线的夹角$\angle AOC$。

![rad.PNG](https://i.loli.net/2019/04/03/5ca4b8e495fbd.png)

这样左右端点就分别为$\angle AOB \pm \angle AOC$

```cpp
db r,pi=acos(-1);
struct point
{
    db x,y;
} a[100005];
struct seg
{
    db l,r;
    bool operator < (const seg &rhs) const
    {
        return l<rhs.l;
    }
} s[200005];
point o={0,0};
db dis(point a,point b)
{
    return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
}
db angle(point a)
{
    return atan2(a.y,a.x);
}
seg get(point a)
{
    db l=dis(a,o);
    db ang=angle(a); 
    db ang2=acos(r/l);
    if (ang-ang2<0) ang+=2*pi;
    return (seg){ang-ang2,ang+ang2};
}
```



接下来就是要求有多少对弧相交。

第一步，破环为链（显然的）。

也就是对每个弧，把它的两个端点都加上$2\pi$当作一个新的弧。

第二步，把每个弧按照左端点排个序。

第三部：维护一个堆，其中堆顶元素的右端点最小。对于一段弧$l_i$

- 把堆里所有右端点比$l_i$的右端点小的弧全部弹出（因为这些弧不会再与以后的任意一个弧相交）
- 剩下的都与$l_i$相交。把答案加上堆的大小。
- 如果$i\leq n$即这个弧是原有的弧，那么就把这个弧加入堆中。

```cpp
struct cmp
{
    bool operator () (seg a,seg b)
    {
        return a.r>b.r;
    }
};
int main()
{
	n=read(),r=read();
	long long ans=0;
	for (int i=1;i<=n;i++) a[i].x=read(),a[i].y=read();
	for (int i=1;i<=n;i++) s[i]=get(a[i]);
	for (int i=1;i<=n;i++) s[i+n]=(seg){s[i].l+2*pi,s[i].r+2*pi};
	sort(s+1,s+2*n+1);
	priority_queue<seg,vector<seg>,cmp> q;
	for (int i=1;i<=2*n;i++)
	{
	    while (q.size() && q.top().r<=s[i].l) q.pop();
	    ans+=q.size();
	    if (i<=n) q.push(s[i]);
    }
    cout<<ans<<endl;
    return 0;
}
```





---

## 作者：pocafup (赞：4)

Update 8/18:

刚发完题解没两天就看到有两个xxs抄了代码，于是把代码改成函数的形式呈现

------------


对着题解理解了好一会才搞明白，这边来解释一下这题一些不容易理解的东西：

**P1:为啥要做切线**

切线定义为一条直线仅在一个点接触某个圆。

易证从圆外一点出发只会存在两条到圆的切线。

现在需要感性理解一下：当两点能互相看见时，他们的切线范围在圆上必然有重合部分。

![](https://cdn.luogu.com.cn/upload/image_hosting/skoupbh7.png?x-oss-process=image)

上图表示了三点对直径为 1 的圆所做的切线。这三点分别为 (0,2), (-1,-1),(3,1)

可以发现，图中只有 2,3 两点能够互相看见。

观察下他们的切线和圆的交点，发现如果两个点能互相看见，那么他们在圆上代表的区间一定存在包含关系。

假设把圆摊开来看作一条直线，那么这题就会变为以一个点的切线的两个端点做线段，求最终多少个区间存在包含关系。

**P2：怎么将圆转化为直线**

我们可以用角度来表示左右端点，易证在圆上角度不同位置也不同，因此我们直接把角度算出即可。

```cpp
struct Segment{
  double l,r;
  bool operator < (const Segment &oth) const{
    return l< oth.l;
  }
}seg[MAXN];

struct Node{
  double l,r;
  bool operator < (const Node &oth) const{
    return r>oth.r;
  }
};
inline void get(double x, double y){
  double l = atan2(y,x)*180.0/pi, flu = acos(k/sqrt(x*x+y*y))*180/pi;//l为当前点跟圆心产生的角度,flu为左右端点跟l产生的角度
  if (l-flu<0) l +=360.0;//先保证他非负,要不然某些角度因为tan和cos的特性会出错
  seg[++cnt] = (Segment) {l-flu,l+flu};//加两条线段,也就是两个环
  seg[++cnt] = (Segment) {l-flu+360.0,l+flu+360.0};
}
```
**P3：怎么计算答案**

在将角度变换为点之后，我们可以按左端点进行排序这些节点，然后保证其他点在左端点比他大且不超过他右端点的大小。如果存在这样的点，那么这个区间一定有重合。

由于是一个环，此做法会导致我们漏算了一部分的左区间。为了避免这种情况，我们对这个圆判断两次即可。

我们维护一个堆，记录右端点最小的点。目前点的左端点比堆上的点的右端点还大时，这个点肯定不会产生贡献。

原因很简单：由于后面的角度单调递增，假设目前线段为 [4,6]，之前线段为 [1,3]，那么在计算 4 之前我们一定已经完成计算 [1,3]。 而 [1,3] 既然跟 [4,6] 没有重合，那么当左端点继续增加时，右端点也会增加，因此他们不可能存在交点。

```cpp
inline void solve(){
  priority_queue<Node> q;
  for (int i=1;i<=2*n;i++){
    while(q.size() && seg[i].l>=q.top().r) q.pop();//不断的删边
    ans += q.size();
    if (i<=n) q.push((Node){seg[i].l,seg[i].r});//当i<=n时,我们一定在第一个环内,因此每条线段只会被加入一次
  }
}
```
说起来挺复杂，但是实现并不难(**完整代码已删，会的自然会**)

---

## 作者：hytallenxu (赞：1)

## 前言
几何好题。

## 正文
题目大意应该很容易理解，就是问有多少点对不会被圆遮挡住。

在这里我们不失一般性的设出 $A$ 和 $B$ 点，做出下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/3v0po47f.png)

容易发现，$A$ 和 $B$ 能互相看见，**当且仅当**他们在圆上的投影有相交的区域。

具体而言，我们分别从 $A$ 点和 $B$ 点往圆做切线，则他们在圆上的弧需要相交（即图中的 $P'P$ 弧）。

那问题就转换成了在圆上重叠的弧的个数。

显然，弧和其圆内的角度有关，我们只需要考虑角度即可。

$$\angle AOP = \cos^{-1}(\frac{OP}{AO}) = \arccos (\frac{r}{\sqrt{x^2+y^2}})$$
$$\angle DOA = \tan^{-1}(\frac{HA}{OH}) = \arctan (\frac{y}{x})$$

显然，
$$\angle POD = \angle DOA - \angle AOP $$

则这个点在圆上投影弧的角度范围便是：

$$[\angle POD, \angle POD + 2 \times \angle AOP] $$

注意，有可能会出现负数，所以我们要加上 $2\pi$ 补回正数。

后面就是线段重叠的板子，注意拆环的套路和答案统计的细节。

## Code
```cpp
#include <bits/stdc++.h>
#define int long long
#ifdef LOCAL
	#include "debug.h"
#else
	#define debug(...) 42
#endif
#define mkp make_pair
#define pb emplace_back
#define endl "\n"
using namespace std;
using ll = long long;
int n,r,t,cnt=0;
constexpr int maxn=1e5+10;
const double PI=acos(-1);

signed main(){
	cin.tie(nullptr)->sync_with_stdio(0);
	cin>>n>>r;
	vector<pair<double,double>> a;
	priority_queue<double,vector<double>,greater<double>> q;
	for(int i=0;i<n;i++){
		int x,y;cin>>x>>y;
		double alpha=acos(r/sqrt(1.0*x*x+y*y));
		double a0=atan2(y,x)-alpha;
		if(a0<0) a0+=2*PI;
		a.pb(mkp(a0,a0+2*alpha));
	}
	sort(a.begin(),a.end());
	for(int iters=0;iters<2;iters++){
		for(int i=0;i<n;i++){
			while(!q.empty()&&q.top()<a[i].first){
				q.pop();
			}
			if(iters==1) cnt+=q.size();
			q.push(a[i].second);
			a[i].first+=2*PI;
			a[i].second+=2*PI;
		}
	}
	cout<<cnt;
	return 0;
}
```

---

## 作者：cyq32ent (赞：1)

初中几何题。

如果两个点的视角在圆上的投影不相交，那么两点间的连线一定穿过圆，所以两点之间不能看见，如下图所示。![](https://cdn.luogu.com.cn/upload/image_hosting/qgpchkkl.png)如果两点之间能看到，那么两点之间的连线一定不穿过圆，因此两点的视角在圆上的投影一定相交。

考虑这段投影的辐角范围。显然为 $[a-b,a+b]$，其中 $a$ 为点的辐角，$b$ 为这段投影的弧度。

所以我们只需要计算环上有多少对相交的线段即可。按照套路，先拆环，然后排序，枚举线段的右端点，并二分即可。时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define S s[i].second
using namespace std;
int n,m;double r,x,y,a,b;pair<double,double>s[1<<17];
const double P=acos(-1);
int main(){
	cin>>n>>r;
	for(int i=1;i<=n;i++){
		cin>>x>>y;
    a=atan2(y,x),b=acos(r/sqrt(x*x+y*y));
		if(a-b<0)a+=2*P;
		s[i]={a-b,a+b};
	}sort(s+1,s+n+1);
	for(int i=1;i<=n;i++)s[n+i]={s[i].first+2*P,S+2*P};
	for(int i=1;i<=n;i++)m+=lower_bound(s+1,s+2*n+1,make_pair(S,S))-s-1-i;
	cout<<m<<endl;
}
```

---

## 作者：O_N_N (赞：0)

这道题要想到两个点的交线是否经过中心那个圆的充要条件就是这两个点对这个圆的两条切线所截的小边的弧是否相交，如果相交，就符合题意；如果不相交，说明两点的交线经过中间那个圆。

显然这玩意没有切线情况（见题意），所以不考虑边界情况。

如何证明呢？这里提供感性的不严谨证明，因为我们观察到两个点，如果它们可以自由活动，那么它们对应到圆的切线一定是连续的，我们固定一个点，这个点和圆构成了两条切线，显然包含圆的那部分天王老子来力，在那里放点，它都是必然和圆相交，因为直线到原点的距离同时根据逆时针和顺时针根据固定的点从原点的直线根据固定的点旋转同时增加的。又因为它们是连续的，我们又观察到两点相切圆的时候，这两个点的到原点的切线必然有一条会重合，此时它们的对应的弧线刚好相交，也就是说，我们完全可以大胆猜测弧线刚好相交一丢丢的时候，就是是否经过圆的边际条件。

至于是否在恰当的地方严格单调就交给我们严格智慧的大数学家来解决吧。

三步走，一步走建系。考虑按照经典的正弦函数的起点作为标准的原点（？这里特别说明就是平面指标坐标系的横轴的正方向），用弧度制为单位，逆时针为角度递增方向建系。

二步走排序。因此所有的弧度都可以被这个平面直角坐标系的两个距离横轴正半轴的角度来表示，考虑更小的弧度制的角度作为基本判断依据从小到大排序。

三步走二分查找。查询当前弧度前面要到第几个弧度才能不相交，由于之前已经排好序了，直接把从当前位置的索引和对应刚好大于当前弧度的另一个更大的角的弧度的更小角的索引相减的差加到答案就行了。注意不包括大于这个弧度本身的情况，故减一。

考虑弧度的更大的角大于一整圈的情况，我们直接特判，直接假设它分为了两部分，一部分更大要在一圈前找，一部分更大大到大于一圈了我们直接给它减去一圈，重复计算就行了。

难度不大，作为紫题比较水。


```cpp
#include <bits/stdc++.h>
using namespace  std;
typedef long long ll;
void p3091(){
    ll n,r;
    cin>>n>>r;
    vector<pair<double,double>> ns(n);
    for (int i = 0; i < n; i++) {
        double a, b;
        cin >> a >> b;
        double d = sqrt(a*a + b*b);
        double y = acos((double)r / d);
        double x = atan2(b, a);
        if(x < 0) x += 2 * M_PI;
        double L = x - y, R_angle = x + y;
        if(L < 0){
            L += 2 * M_PI;
            R_angle += 2 * M_PI;
        }
        ns[i] = {L, R_angle};
    }
    sort(ns.begin(),ns.end(),[](const pair<double,double>& a , const pair<double,double>& b){
        if(a.first!=b.first)return a.first<b.first;
        return a.second<b.second;
    });
    ll ans=0;
    for (int i = 0; i < n; i++) {
        auto it = upper_bound(ns.begin() + i + 1, ns.end(), ns[i].second,
                              [](double value, const pair<double,double>& p) {
                                  return value < p.first;
                              });
        ans += (it - (ns.begin() + i + 1));

        if(ns[i].second > 2 * M_PI){
            double limit = ns[i].second - 2 * M_PI;
            auto it2 = upper_bound(ns.begin(), ns.end(), limit,
                                   [](double value, const pair<double,double>& p) {
                                       return value < p.first;
                                   });
            ans += (it2 - ns.begin());
        }
    }
    cout<<ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    p3091();
    return 0;
}

```

---

## 作者：jimw (赞：0)

## 一道比较简单的的数学题
#### 朴素方法：

读题目不难想到作两条切线，进而统计符合要求的点个数。

朴素方法计算每个点与圆切线的斜率，以及任意两点间的斜率，判断是否在两切线的区间内。数据范围$1\leqslant n \leqslant 50000$，时间复杂度$O(n^2)$超时。

因此可知大概率是要用$O(n)$或者$O(nlogn)$的算法。

------------
#### 数学思想：

接下来需要一点数学思想，我们需要把点与圆的两切线作为由两切点构成的弧来存储，从具象上认知就是存储每头牛的视野盲区。作图，结论是两头牛的视野盲区若有交集，说明它们能看见彼此（~~光的反射？？？~~)

数据处理上，可以二分找到第一个左端点大于当前线段右端点的线段，时间复杂度$O(nlogn)$。而进一步分析会发现这些线段有单调性，可以用堆进行维护（**详见下**），时间复杂度下降至$O(n)$。

------------
#### 正解总结：
1. 将环化为直线 ，将$n$个数据点与圆的一对切点映射在直线上，存储这些弧（线段），与其加上$2π$后的弧（线段）（破环为链）
2. 按左端点对共2n条线段排序，顺序遍历$1$到$n$的线段，同时建堆维护**单调性**（即每次更新的临界位置是第一个左端点大于当前线段右端点的线段，故可以确保已被更新所用线段不会被后更新的线段再次使用）

 	 <单调性$O(n)$（遍历线段）+$O(n)$（清空堆）=$O(n)$>

3. 对于环上会有当前弧右端点交已被更新的弧的左侧情况，使用加上$2π$后的弧来进行统计！


------------
#### 代码：

实现起来稍微有些麻烦的就是存储上述弧，可以存储端点与$0$°夹角，需要用一些数学公式来计算。

```cpp
struct DOT{
	double x,y;
};
struct SEG{
	double l,r;
};
void cal_angel(DOT a){
	double base=atan2(a.y,a.x);//(点与圆心)线与0°的夹角 
	double dis=sqrt(a.x*a.x+a.y*a.y);//(点与圆心)连线长度 
	double delta=acos(r/dis);//切线与 ((点与圆心)连线的夹角 
	base=base-delta<0 ? base+2*pi : base;//将数学中可能为负的角度转化为正 
	pq.push((SEG){base-delta,base+delta});
	pq.push((SEG){base-delta+pi*2,base+delta+pi*2});
}
```

难以理解的话可以自行画图，学过反三角函数应该都能看懂.

其他部分比较简单，就不发了。



---

