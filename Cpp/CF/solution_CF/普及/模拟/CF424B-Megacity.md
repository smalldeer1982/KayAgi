# Megacity

## 题目描述

The administration of the Tomsk Region firmly believes that it's time to become a megacity (that is, get population of one million). Instead of improving the demographic situation, they decided to achieve its goal by expanding the boundaries of the city.

The city of Tomsk can be represented as point on the plane with coordinates ( $ 0 $ ; $ 0 $ ). The city is surrounded with $ n $ other locations, the $ i $ -th one has coordinates ( $ x_{i} $ , $ y_{i} $ ) with the population of $ k_{i} $ people. You can widen the city boundaries to a circle of radius $ r $ . In such case all locations inside the circle and on its border are included into the city.

Your goal is to write a program that will determine the minimum radius $ r $ , to which is necessary to expand the boundaries of Tomsk, so that it becomes a megacity.

## 样例 #1

### 输入

```
4 999998
1 1 1
2 2 1
3 3 1
2 -2 1
```

### 输出

```
2.8284271
```

## 样例 #2

### 输入

```
4 999998
1 1 2
2 2 1
3 3 1
2 -2 1
```

### 输出

```
1.4142136
```

## 样例 #3

### 输入

```
2 1
1 1 999997
2 2 1
```

### 输出

```
-1```

# 题解

## 作者：___define___ (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/CF424B)

大水题（）

## 思路

这题有一个非常开挂的公式，就是两点间距离公式。

若一个点为 $(x_1,y_1)$，另一个点为 $(x_2,y_2)$，则它们之间的距离为：

$\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$

有了这个公式，这题就显得非常简单了，直接排序，再从距离近的开始加人数，直到够 $10^6$ 为止。

![](https://cdn.luogu.com.cn/upload/image_hosting/a7j1744i.png)

## AC Code

```
#include<bits/stdc++.h>
using namespace std;
const int N=1e6;
int n,k,x[N],y[N];
struct c{
	int t;
	double z;//注意，要用double 
}a[N];
bool cmp(c x0,c y0){
	return x0.z<y0.z;//用距离为基准排序 
}
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>x[i]>>y[i]>>a[i].t;
		a[i].z=sqrt(x[i]*x[i]+y[i]*y[i]);//两点间距离公式 
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		k+=a[i].t;
		if(k>=N){
			printf("%.7lf",a[i].z);
			return 0;
		}
	}
	cout<<-1;
	return 0;
}
```

---

## 作者：NATO (赞：1)

### 题目分析：
很明显，因为本题求的是最小的半径，因此采取贪心法。将城镇按照到坐标系原点的距离（设第 $i$ 座城镇到坐标系原点的距离为 $dis_i$，则由两点之间距离公式可知：$dis_i=\sqrt{x_i^2+y_i^2}$）从小到大排序，然后循环不断给 $s$ 加上 $k_i$，如果 $s≥10^6$ 说明当前城镇到坐标系原点的距离即为最小半径，就输出当前城市距离并结束，如果枚举完了城镇都没有输出，就输出 $-1$，时间复杂度主要来自于排序，为 $O(n \log n)$。

##### 贪心正确性证明：
显而易见，按距离加城镇枚举时可以保证满足人数条件后不会出现更优解，因为满足人数限制时比该城镇距离更小的城镇人数均已计入。

#### 参考代码：
```cpp
#include<bits/stdc++.h> 
#define ll long long
#define db double
using namespace std;
struct px
{
	db jl;
	ll w;
}a[1005];
bool cmp(px a,px b)
{
	return a.jl<b.jl;
}
ll n,k;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>k;
	db x,y;
	for(ll i=1;i<=n;++i)
		cin>>x>>y>>a[i].w,a[i].jl=sqrt(x*x+y*y);//输入并计算距离
	sort(a+1,a+1+n,cmp);
	for(ll i=0;i<=n;++i)
	{
		k+=a[i].w;
		if(k>=1000000)
		{
			printf("%.7lf",a[i].jl);return 0;
		}
	}
	cout<<-1;
}
```


---

## 作者：huta0 (赞：0)

水题。

注意到要在满足条件的情况下，让其半径最小。

那么我们容易想到一种贪心做法，即第一关键字按每个点到原点的距离排序，第二关键字为该点人数。

想到这里，此题就很简单了。先按上述方法排序，最后前缀和搞一下人数就好了。

容易证明，按到原点距离遍历，此时半径扩大，圆内人数是单调递增的。那么合法的半径最小的圆一定经过某个给定的点。因为此时若找到第一个可以满足题意的点，那么，若向内缩半径 $r$，那么就不满足人数需求；向外扩半径 $r$，那么就不满足最小了呜。

代码很短啦，时复一只 log。

```cpp
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#define ai_jiang signed main()
#define rep(a,b,c) for(int a=b;a<=c;a++)
#define drep(a,b,c) for(int a=b;a>=c;a--)
#define all(a) a.begin(),a.end()
#define ll long long
using namespace std;
using poly=vector<ll>;
namespace ai {
    constexpr int N = 1e3+3;
    int n,cnt,c,top,sum[N];
    double a,b;
    pair<double,int> p[N];
}
using namespace ai;
ai_jiang {
    cin.tie(0); cout.tie(0);
    cin>>n>>cnt;
    cnt=1000000-cnt;
    rep(i,1,n) {
        cin>>a>>b>>c;
        p[++top]={sqrt(a*a+b*b),c};
    }
    sort(p+1,p+top+1,[](pair<double,int> x,pair<double,int> y){return x.first==y.first?x.second>y.second:x.first<y.first; });
    rep(i,1,top) sum[i]=sum[i-1]+p[i].second;
    rep(i,1,top) {
        if(cnt-sum[i]<=0) {
            printf("%.7lf",p[i].first);
            return 0;
        }
    }
    cout<<-1;
    return 0;
}
```

---

## 作者：lichenzhen (赞：0)

## 题目大意
题目翻译十分很简洁，可以看看原题目。

[点击查看](https://www.luogu.com.cn/problem/CF424B)

## 题目解法
这里要用到了[两点间距离公式](https://baike.baidu.com/item/%E4%B8%A4%E7%82%B9%E9%97%B4%E8%B7%9D%E7%A6%BB%E5%85%AC%E5%BC%8F/6773405)，即两点之间的距离为 $\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$，将每一个点距离原点，即 $(0,0)$ 点的距离，然后进项排序。

之后循环扫描，每次将人数加上当前点的人数，直到总人数 $\ge 10^6$，输出当前圆距原点的距离，即半径 $r$，结束程序。

循环结束，程序还没有结束，那就是说明无法画出这样的圆，直接输出 `-1`。

最后注意，半径要保留 $7$ 位小数输出。

### 参考代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct lcz{
	int x,y,k;
	double jl;
}a[1010]; 
bool cmp(lcz a,lcz b){return a.jl<b.jl;}//以距离为关键字排序
signed main(){
	int n,s;
	cin>>n>>s;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y>>a[i].k;
		a[i].jl=sqrt(a[i].x*a[i].x+a[i].y*a[i].y);//计算距离
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		s+=a[i].k;
		if(s>=1000000){
			printf("%.7lf",a[i].jl);
			return 0;
		}
	}
	cout<<-1;
} 
```


---

## 作者：Halberd_Cease (赞：0)

很显然的一道贪心。

## 题意
城市原本有 $s$ 人，此外有 $n$ 个点，第 $i$ 个点的人数为 $k_i$，坐标为 $(x_i,y_i)$，以原点为中心向外作半径为 $r$ 的圆，求最小的 $r$ 使圆内的所有点的人数和原本人数不少于 $10^6$。

## 方法
求出每个点到原点的距离 $dis_i$ 然后以此为关键字升序排序，以此将每一个 $k_i$ 加入 $s$ 中，判断 $s\ge 1,000,000$ 是否成立。如果成立就输出当前 $i$ 的 $dis_i$ 即刻，如果枚举完都没有成立就输出 $-1$。

为什么是正确的呢？按距离升序排序后，距离小的在前，这样枚举就不会出现加一个点后人数达标但是有比它更优的解（即不要这个点也够达标），因为所有比它小的点都已经加入。

## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct Point{
	int x;
	int y;
	int k;
	double dis;
}a[1010];
bool cmp(Point x,Point y)
{
	return x.dis<y.dis;
}
double make_dis(int x,int y)
{
	return sqrt(x*x+y*y);
}
int main()
{
	int n,s;
	cin>>n>>s;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].x>>a[i].y>>a[i].k;
		a[i].dis=make_dis(a[i].x,a[i].y);
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		s+=a[i].k;
		if(s>=1000000)
		{
			printf("%.12f",a[i].dis);
			return 0;
		}
	}
	cout<<-1;
	return 0;
} 
```

---

## 作者：qwq___qaq (赞：0)

### 题意
有 $n$ 个城市，第 $i$ 个城市的坐标为 $(x_i,y_i)$，有 $k_i$ 个人。现在，需要你选择一个半径 $r$，使得以原点 $(0,0)$ 为圆心，半径为 $r$ 的圆中，有不小于 $10^6$ 个人。如果可以，输出最小的半径，误差不超过 $10^{-6}$，如果不行，输出 `-1`。
### 思路
首先，要求最小半径，考虑排序，按照距离从小到大排序。

然后，我们就加上这个城市的人数，如果现在的人数大于等于 $10^6$，那么就输出这个城市到原点的距离即可。

如果没有，在最后输出 `-1` 即可。

注意判断初始人数，时间复杂度 $O(n\log n)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int qwq=1e6;
struct node{
	double x;
	int y;
	inline bool operator <(const node &t) const{
		return x<t.x;
	}
}f[1005];//定义结构体
int n,s;
inline double d(int x,int y){
	return sqrt(x*x+y*y);
}//到原点的距离
int main(){
	cin>>n>>s;
	for(int i=1,x,y,z;i<=n;i++){
		cin>>x>>y>>z;
		f[i]=node({d(x,y),z});
	}
	stable_sort(f+1,f+n+1);//排序
	for(int i=0;i<=n;++i){//从 0 开始是因为初始人数
		double x=f[i].x;
		int y=f[i].y;
		s+=y;
		if(s>=qwq){
			printf("%.7lf",x);//多保留 1 位，避免误差
			return 0;
		}
	}
	cout<<"-1"<<endl;//所有人都不够
    return 0;
}
```

---

## 作者：Fearliciz (赞：0)

### 题目翻译:

求管理大大将此翻译放到题面。

一个都市，要成为特大城市需要人口达到一百万。而快速改善人口的方法只能通过扩大城市边界来实现。一个都市 $A$ 用平面上的坐标点 $(0,0)$ 来表示。该市周围有 $n$ 个人口聚居点，第 $i$ 个点的坐标为 $(x_i,y_i)$ 人口数为 $k_i$。现将城市边界扩大到半径为 $r$ 的圆。圆圈内及其边界上的所有的人口都包括在城市中。请你编写一个程序，确定最小半径 $r$，以便使都市 $A$ 成为一个特大城市。

### 解题思路:

很容易想到将每个人口聚居点到原点的距离记录下来。

然后便知，排序后一次累加直到找到某一次大于等于大都市的人数便停止。

输出该点到原点的距离即可。

须注意，排序是按照距离排序。

### 代码:

```cpp
#include<bits/stdc++.h>
#define y1 yy1
#define X first
#define Y second

using namespace std;

const int metropolis=1000000;
pair<double,int> len[1010];
int n,nowp;
int x,y,xp;

double Euclid(int x1,int y1,int x2,int y2)
{
	return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}

int main()
{
	cin>>n>>nowp;
	for(int i=1;i<=n;i++)
	{
		cin>>x>>y>>xp;
		len[i].X=Euclid(0,0,x,y);
		len[i].Y=xp;
	}
	sort(len+1,len+1+n);
	for(int i=1;i<=n;i++)
	{
		nowp+=len[i].Y;
		if(nowp>=metropolis)
		{
			printf("%.8lf",len[i].X);
			return 0;
		}
	}
	cout<<"-1";
    return 0;
}

```


其实还是很好写的，没用结构体，直接用的 $\texttt{pair}$。

顺便说一下，[这篇题解](https://www.luogu.com.cn/blog/ztxtjz/solution-cf424b)中其实不用判断开始是否就是大都市，因为题目中已经说了，初始人数不超过百万。

---

## 作者：ztxtjz (赞：0)

## 【题意】
确定一个半径，使半径以内所有城市的人口数+Tomsk的人口数达到1e6，有解输出半径，无解输出-1。
## 【思路】
将各个城市距Tomsk的距离由小到大排序，优先加上距离近的城市的人口数，达到要求直接输出当前城市距Tomsk的距离并退出。若循环结束，则代表所有城市人数不足。
## 【代码】
```cpp
#include <cstdio>
#include <cmath>
#include <algorithm>
#define ll long long
using namespace std;
ll n,ans;
double x,y;//坐标
struct city
{
	ll s;//城市人数
	double r;//距Tomsk距离，即半径
}a[1005];
bool cmp(city l,city r)
{
	return l.r<r.r;//半径升序排序
}
int main()
{
	scanf("%lld%lld",&n,&ans);
	if(ans>=1e6)//若Tomsk人数已达到，不需扩展
	{
		printf("0");
		return 0;
	}
	for(int i=1;i<=n;i++)
		scanf("%lf%lf%lld",&x,&y,&a[i].s),a[i].r=sqrt(x*x+y*y);
	sort(a+1,a+n+1,cmp);//半径升序排序
	for(int i=1;i<=n;i++)
	{
		ans+=a[i].s;//逐个加上
		if(ans>=1e6)
		{
			printf("%.7f",a[i].r);
			return 0;
		}
	}
	printf("-1");//所有城市的人数和小于1e6
	return 0;
}
```

---

