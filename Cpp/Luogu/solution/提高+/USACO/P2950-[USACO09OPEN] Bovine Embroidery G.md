# [USACO09OPEN] Bovine Embroidery G

## 题目描述

Bessie has taken up the detailed art of bovine embroidery. Cows embroider a cloth mounted in a circular hoop of integer radius d (1 <= d <= 50,000). They sew N (2 <= N <= 50,000) threads, each in a straight line from one point on the edge of the hoop to another point on the edge of the hoop (no two embroidered points share a location on the hoop's edge).

Being mathematically inclined, Bessie knows a formula of the form ax + by + c = 0 for each straight line piece of thread. Conveniently, a, b, and c are integers (-1,000,000 <= a <= 1,000,000; -1,000,000 <= b <= 1,000,000; -1,000,000 <= c <= 1,000,000). Even more

conveniently, no two threads coincide exactly.

Perhaps less conveniently, Bessie knows that her set of formula coefficients also includes a number of formulae for threads that do not appear to pass inside the hoop's circle. She regrets this greatly.

The origin (0,0) is in the precise middle of the hoop, so all points on the hoop's edge are distance d from the origin. At least one of the coefficients a and b is non-zero for each thread's formula.

Bovine embroidery is more highly regarded when the number of thread intersections is maximized. Help Bessie: count the number of pairs of threads that intersect on the cloth (i.e., within distance d of the origin). Note that if three threads happen to coincide at the same point, that would be three pairs of intersections. Four threads at the same point -> six pairs of intersections, etc.

Bessie学会了刺绣这种精细的工作。牛们在一片半径为d(1 <= d <= 50000)的圆形布上绣花. 它们一共绣了N (2 <= N <= 50000)条直线，每条直线连接布的边缘上的两个点(没有两条线通过边上同一个点)。

作为一只热爱数学的牛，Bessie 知道每条线的公式, ax + by + c = 0. a, b, 和 c 为整数(-1000000 <= a <= 1000000; -1000000 <= b <= 1000000; -1000000 <= c <= 1000000).没有两条线完全重合。

不幸的是, 一部分线不通过圆布的内部. 原点(0,0)在布的正中央, 所有边上的点离原点距离为d. 每条线的公式满足至少a,b中的一个非零. 对于牛来说，刺绣作品中线的交点越多，便越有价值。帮助Bessie计算在圆中相交的线的对数，也就是说交点与原点的距离小于d。注意如果三条线在圆内同一点相交,这算3对线。4线共点->6对线.


## 说明/提示

The two lines are x=0 and y=0. 

The two lines intersect at (0,0), which is clearly with 1 of the origin. 



## 样例 #1

### 输入

```
2 1 
1 0 0 
0 1 0 
```

### 输出

```
1 
```

# 题解

## 作者：fy0123 (赞：3)

emmmm先%一下楼下。

然后这个题目还是挺巧妙的，考察转化思想。

由于不能暴力枚举两条直线，我们考虑怎样的情况会使得两条直线相交于圆内。

发现只有这种情况：两条线与圆的4个交点相间排列。

如图：

 ![](https://cdn.luogu.com.cn/upload/pic/11494.png) 

于是把圆拉成线段后就可以转化为线段上的问题。

至于接下来怎么做，我们将圆拉成一条直线以后，把直线与圆的交点标记出来，发现上面有很多对点（就是某条直线与圆的两个交点）。然后假如把每一对点都连起来，会发现相当于求有交集的区间对数。具体可以手动模拟一下。

然后我们需要快速求出这个有交集的区间对数，这个可以用树状数组维护。

代码什么的见我的blog：[链接](http://blog.csdn.net/bestfy/article/details/78700881)


---

## 作者：thmyl (赞：2)

[http://www.cnblogs.com/thmyl/p/7352721.html](http://www.cnblogs.com/thmyl/p/7352721.html)



```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define N 100010
int n,num,c[N],vis[N];
long long ans,d;
const double eps=1e-9;
struct node{
    double ct;
    int id;
}p[N];
bool cmp(node x,node y){
    return x.ct-y.ct>eps;
}
int lowbit(int x){return x&(-x);}
void update(int p,int x){
    while(p<=2*n){
        c[p]+=x;
        p+=lowbit(p);
    }
}
long long query(int p){
    long long sum=0;
    while(p){
        sum+=c[p];
        p-=lowbit(p);
    }
    return sum;
}
int main(){
    //freopen("Cola.txt","r",stdin);
    scanf("%d%lld",&n,&d);
    long long a,b,c;
    for(int i=1;i<=n;i++){
        scanf("%lld%lld%lld",&a,&b,&c);
        //cin>>a>>b>>c;
        if(c*c<d*d*(a*a+b*b)){
            double tmp=a*a+b*b,tmp2=sqrt(d*d*tmp-c*c);
            double x1=(a*c+b*tmp2)/tmp;
            double x2=(a*c-b*tmp2)/tmp;
            double y1=(b*c-a*tmp2)/tmp;
            double y2=(b*c+a*tmp2)/tmp;
            p[++num].ct=atan2(y1,x1);p[num].id=i;
            p[++num].ct=atan2(y2,x2);p[num].id=i;
        }
    }
    sort(p+1,p+1+num,cmp);
    for(int i=1;i<=num;i++){
        if(vis[p[i].id]){
            ans+=query(i)-query(vis[p[i].id]);
            update(vis[p[i].id],-1);
        }
        else {
            vis[p[i].id]=i;
            update(i,1);
        }
    }
    printf("%lld",ans);
    return 0;
}
100分
```

---

## 作者：Chenyichen0420 (赞：1)

## 题意

在平面当中，有一个以原点为圆心的圆，半径为 $d$。还有 $n$ 条直线，每条直线的解析式已给出。问有几对直线相交且交点在圆内？

## 思路分析

分两步，先将圆上的问题化为在线段上的问题。再考虑求解。

我们将这个圆从纵轴负半轴切开，展平成为一条线段，并将那些直线原本在其中的部分保留，并和这个圆一起拉伸（自行脑补），原本相交的一对线段显然在被拉伸后变为两个相交的区间。这时候，我们就将原问题转化为了相交的区间的对数问题。

这也是难点，不过代码中有推式子的过程，这里就不详讲了。

剩下的就简单了，用树状数组统计一下重叠区间对数就好了。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, d, cnt, ans; double a, b, c, x2v, x1v, x0v, xa, ya, xb, yb, delta;
vector<pair<double, double>>v; vector<double> vl;double lnp, rnp;
inline double linepos(const double xp, const double yp) {
	return (yp < 0 ? -1 : 1) * (d + xp);
}
struct tree_array {
	int vl[100005];
	inline int que(int ps) {
		int tmp = 0;
		while (ps) tmp += vl[ps], ps -= (ps & -ps);
		return tmp;
	}
	inline void add(int ps) {
		while (ps <= n * 2) vl[ps]++, ps += (ps & -ps);
	}
}qr;
signed main() {
	ios::sync_with_stdio(0);
	cin >> n >> d;
	for (int i = 1; i <= n; ++i) {
		cin >> a >> b >> c;
		//ax+by+c=0
		//x^2+y^2=d^2
		/*
		specialize if a=0 or b=0
		so y=-(ax+c)/b
		so x^2+((ax+c)^2)/(b^2)=d^2
		so x^2+(a^2*x^2+2acx+c^2)/(b^2)=d^2
		so ((a^2+b^2)/(b^2))*x^2+(2ac/(b^2))*x+(c^2-(b^2)*(d^2))/(b^2)=0
		because b*b!=0
		so (a^2+b^2)*x^2+2ac*x+c^2-b^2*d^2=0
		*/
		if (a == 0) {
			//by+c=0 => y=-c/b
			ya = yb = -c / b;
			delta = d * d - ya * ya;
			if (delta < 0) continue;
			xa = sqrt(delta); xb = -sqrt(delta);
		}
		else if (b == 0) {
			//ax+c=0 => x=-c/a
			xa = xb = -c / a;
			delta = d * d - xa * xa;
			if (delta < 0) continue;
			ya = sqrt(delta); yb = -sqrt(delta);
		}
		else {
			x2v = (a * a + b * b), x1v = (2 * a * c),
				x0v = (c * c - b * b * d * d);
			delta = x1v * x1v - 4 * x2v * x0v;
			if (delta < 0) continue;
			//x1=(-x1v+sqrt(delta))/2a,x2=(-x1v-sqrt(delta))/2a
			xa = (-x1v + sqrt(delta)) / (2 * x2v), xb = (-x1v - sqrt(delta)) / (2 * x2v);
			ya = -(a * xa + c) / b, yb = -(a * xb + c) / b;
		}
		lnp = linepos(xa, ya); rnp = linepos(xb, yb);
		if (lnp > rnp) swap(lnp, rnp);
		v.push_back(make_pair(lnp, rnp));
		vl.push_back(lnp);
		vl.push_back(rnp);
	}
	sort(v.begin(), v.end()); sort(vl.begin(), vl.end());
	for (int i = 0; i ^ v.size(); ++i) {
		int lp = lower_bound(vl.begin(), vl.end(), v[i].first) - vl.begin(),
			rp = lower_bound(vl.begin(), vl.end(), v[i].second) - vl.begin();
		ans += qr.que(rp + 1) - qr.que(lp); qr.add(rp + 1);
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：EricWan (赞：0)

详细的题解，有很多可学习的连接：

## STEP 1

处理“线”是不是在圆内，这需要一定[数学技巧](http://www.help315.com.cn/shuxue/2020/0503/6291.html)。

## STEP 2

处理完了线之后大概会变成：

![如果看不见就是图炸了](https://cdn.luogu.com.cn/upload/image_hosting/vz71rq18.png)

之后我们把它展开为一个 $2\times n$ 的数组，两个相同的数字一定会组成一个线段（废话），以这个线段中出现且仅出现两次的数为下标的线肯定可以与以这个线段两端的数为下标的线相交。转化后就和[这题](https://www.luogu.com.cn/problem/T370904)一样了。

## STEP 3

维护区间内只出现一次的数的个数可以参考[这题](https://www.luogu.com.cn/problem/P3582)，扫描时，将最后一次的某个数标为 1，倒数第二次出现的一个数标为 -1，我们用树状数组维护就可以了。

---

## 作者：3a51_ (赞：0)

题解区全是树状数组，这里提一下我们同学想到的一个神奇做法。

前面的其他题解讲得很清楚了，这里直接说一下变成线段之后怎么做。

因为每个数出现了 $2$ 次，所以设 $i$ 这个数出现第一次的位置为 $p1_i$，第二次的位置为 $p2_i$，此时只需求出满足 $1\le i,j\le n$ 且 $p1_i<p1_j,p2_i<p2_j$ 的数对 $(i,j)$ 的数量即可。

考虑正难则反，求出 $1\le i,j\le n$ 且 $p1_i<p1_j,p2_i>p2_j$ 的数量 和 $1\le i,j\le n$ 且 $p1_i< p2_i< p1_j$ 的数量即可。

后一种比较好求，扫一遍，记录一下当前已经出现了两次的数字就可以 $O(n)$ 求出。

接下来算前一种的数量。不妨把 $p1,p2$ 放到一个结构体里去，然后按照 $p1$ 排序。此时 $\forall(i,j)\;\; i <j$，$p1_i<p1_j$ 就天然满足了。那么，接下来要计算的就是 $i<j$ 且 $p2_i>p2_j$ 的数量，不难看出就是求一下逆序对，归并排序做一遍就好了。

注意这里有个细节，因为归并排序求逆序对是需要排序数组的，然而我们的结构体已经按照 $p1$ 排好序了，所以你需要单独把 $p2$ 拎出来再做。

最后用 $n(n-1)$ 减一下答案就做完了，时间复杂度 $O(n \log n)$。

---

## 作者：SimonSu (赞：0)

[思路来自已发布的大佬%% 进行了具体的解释]
题目要求交点的个数我们画个图来看一下
![图片说明](https://uploadfiles.nowcoder.com/images/20190806/978569483_1565100923976_F7F0BBDB094D0B83D7561FC5EC2130D7 "图片标题") 

那么我们可以发现当我们固定某一点为起点在圆周上进行枚举

两条线有交点的条件是 两条线的端点是插着的 

就用上面那个图以圆在X负半轴的交点为起点 黄色和绿色线的端点是插着的 而黄色与红色的没有 所以你就可以发现我刚刚说的是有道理的 

所以我们就可以用树状数组（其他你喜欢的也可以）进行维护

之前在通过推道公式求出两个端点的坐标就可以了 （代码中有详细过程）

然后就是化曲为直 我是先将X上下半轴分开 再分别按从小到大和从大到小排

```
#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<queue>
#include<stack>
#include<cmath>
#define LL long long
using namespace std;
inline void read(LL &x){
	x=0;LL f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-') f=-1;c=getchar();	}
	while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
	x*=f;
}
struct node{
	double x,y;
	LL num;
}e[100050];
LL n;
double a,b,c,d;
inline double Y(double X)
{
	return (double)(-a*X-c)*1.0/b;
}
inline LL cmpy(node a,node b)
{
	return a.y < b.y;
}
inline LL cmpu(node a,node b)
{
	return a.x>b.x;
}
inline LL cmpd(node a,node b)
{
	return a.x<b.x;
}
inline LL lowbite(LL k)
{
	return k&(-k);
}
LL N;
LL tr[100500];
inline void add(LL pos,LL v)
{
	for(LL i=pos;i<=N;i+=lowbite(i))
	{
		tr[i]+=v;
	}
}
inline LL query(LL pos)
{
	LL res=0;
	for(LL i=pos;i>0;i-=lowbite(i))
	{
		res+=tr[i];
	}
	return res;
}
LL v[50010];
int main()
{
	read(n);
	scanf("%lf",&d);
	N=n*2;
	LL k=0;
	for(LL TT=1;TT<=n;TT++)
	{
		scanf("%lf",&a);
		scanf("%lf",&b);
		scanf("%lf",&c);
		//ax+by+c=0;
		//x*x+y*y=d*d
		//y=(-ax-c)/b
		//x*x+(ax*ax+2*a*c*x+c*c)/b*b = d*d
		//x*x*b*b + a*a*x*x + 2*a*c*x = d*d*b*b - c*c
		//(a*a+b*b)*x*x + 2*a*c*x = d*d*b*b - c*c
		//(a*a+b*b)*x*x + 2*a*c*x +(c*c - d*d*b*b) = 0
		if(a==0)
		{
			//by+c=0
			e[TT*2-1].y = (-c)*1.0/b;
			e[TT*2-1].x = sqrt(d*d-e[TT*2-1].y);
			e[TT*2-1].num = TT;
			e[TT*2].y = (-c)*1.0/b;
			e[TT*2].num = TT;
			e[TT*2].x = -sqrt(d*d-e[TT*2].y);
			if(e[TT*2-1].y < 0) k++;
			if(e[TT*2].y < 0) k++;
			continue;
		}
		if(b==0)
		{
			//ax+c=0 
			e[TT*2-1].x = (-c)*1.0/a;
			e[TT*2-1].y = sqrt(d*d-e[TT*2-1].x);
			e[TT*2-1].num = TT;
			
			e[TT*2].x = (-c)*1.0/a;
			e[TT*2].y = -sqrt(d*d-e[TT*2].x);
			e[TT*2].num = TT;
			if(e[TT*2-1].y < 0) k++;
			if(e[TT*2].y < 0) k++;
			continue;
		}
		LL A=a*a+b*b;
		LL B=2*a*c;
		LL C=c*c-d*d*b*b;
		LL delta=B*B-4*A*C;
		if(delta<=0) continue;
		
		e[TT*2-1].x = (-B+sqrt(delta))*1.0/(2*A);
		e[TT*2-1].y = Y(e[TT*2-1].x);
		e[TT*2-1].num = TT; 
		
		if(e[TT*2-1].y < 0) k++;
		
		e[TT*2].x = (-B-sqrt(delta))*1.0/(2*A);
		e[TT*2].y = Y(e[TT*2].x);
		e[TT*2].num = TT; 

		if(e[TT*2].y < 0) k++;
	}
	stable_sort(e+1,e+1+n*2,cmpy);
	
//	for(LL i=1;i<=N;i++)
//	cout<<e[i].x<<"  "<<e[i].y <<" " <<e[i].num<<" Y1Y"<<endl;
//    cout<<endl;
    
	stable_sort(e+1,e+1+k,cmpd);
	
//	for(LL i=1;i<=N;i++)
//	cout<<e[i].x<<"  "<<e[i].y <<" " <<e[i].num<<" Y2Y"<<endl;
//    cout<<endl;
    
	stable_sort(e+1+k,e+1+n*2,cmpu);
	LL ans=0;
	for(LL i=1;i<=N;i++)
	{
//		cout<<e[i].x<<"  "<<e[i].y <<" " <<e[i].num<<" YYY"<<endl;
        if(e[i].num == 0) continue;
//		cout<<v[e[i].num]<<endl;
		if(v[e[i].num]==0)
		{
			v[e[i].num]=i;
			add(i,1);
		}
		else
		{
//			cout<<query(i)<<" "<<query(v[e[i].num])<<endl;
			LL tmp=(query(i)-query(v[e[i].num]));
			add(v[e[i].num],-1);
//			if(tmp<=0) continue;
			ans+=tmp;
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

