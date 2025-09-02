# Emblem

## 题目描述

在一个坐标平面上有 $N$ 个给定的圆心和半径的圆，和 $M$ 个给定圆心但不给定半径的圆，请问如何设置这 $M$ 个圆的半径，使得这些圆中没有两两相交或内含的两个圆。求出所有方法中，半径最小的圆的半径的最大值。

## 说明/提示

- $N,M\in[0,100]$。
- $N+M\ge 2$。
- $x_i,y_i\in[-100,100]$。（$1\le i\le N+M$）
- $r_i\in[1,100]$。（$1\le i\le N$）
- $\forall i,j\in[1,N+M]$ 且 $i\neq j$ 满足 $(x_i,y_i)\neq(x_j,y_j)$。
- $\forall i,j\in[1,N]$ 且 $i\neq j$ 满足第 $i$ 个圆与第 $j$ 个圆不相交或内含。
- $\forall i\in[1,N],j\in[N+1,M]$ 满足 $(x_j,y_j)$ 不在第 $i$ 个圆上。

## 样例 #1

### 输入

```
0 2
6 3
2 4```

### 输出

```
2.061552812808830```

## 样例 #2

### 输入

```
0 5
8 6
9 1
2 0
1 0
0 1```

### 输出

```
0.500000000000000```

## 样例 #3

### 输入

```
3 0
5 2 3
-1 0 2
2 -6 4```

### 输出

```
2.000000000000000```

## 样例 #4

### 输入

```
1 1
0 0 5
6 -3```

### 输出

```
1.708203932499369```

# 题解

## 作者：yedalong (赞：2)

## 前言

本人使用的是浮点数二分，精度有点恶心。。。\
没学过浮点数二分的同学可以[戳这里](https://blog.csdn.net/weixin_45804157/article/details/119324550)。

## 思路

读完题目后发现，它的最大值满足单调性，因此考虑二分。可是那 $M$ 个圆的半径好像不相同哎，怎么办呢？题目只是说半径最小的圆的半径最大值，因此，我们可以让所有的 $M$ 个圆都为半径最小的圆，而且这样操作是不会影响结果的，原因可以自己想一下。\
既然是二分，那 $l$ 和 $r$ 初始为多少呢？大家可以很快的想到 $l$ 为 $0$，但是 $r$ 呢？直接赋值为极大值吗？那显然是不行的。我们二分的是半径最小的圆的半径最大值，而如果超过已知半径的那些圆中的半径最小值，那二分的还是半径最小的圆吗？因此，$r$ 为已知半径的那些圆中的半径最小值。\
接着我们来讨论 check 函数怎么写。由于圆的数量很少，我们可以直接暴力两两枚举所有圆是否会出现题目中说的重叠或包含。而重叠或包含要在什么情况下才会出现呢？我们可以发现，当两圆圆中心在平面上的最小距离小于两圆半径相加时会出现，这地方比较简单，大家可以思考一下。\
精度可以开大一点，不然会出现奇奇怪怪的问题。\
这种做法可能没有其他的做法优秀，但我觉得这种做法比较好理解。\
最后放出代码。

## AC code:

```cpp
#include <bits/stdc++.h>
using namespace std;
struct circle{
    int x,y;double r;
}a[210];
int n,m;
double l,r=1000,ans,minn=101;
bool check(double x){
    for(int i = n+1;i<=n+m;i++) a[i].r=x;
    for(int i = 1;i<=n+m;i++)
        for(int j = i+1;j<=n+m;j++)
            if(sqrt((a[i].x-a[j].x)*(a[i].x-a[j].x)+(a[i].y-a[j].y)*(a[i].y-a[j].y))<a[i].r+a[j].r) return 0;
    return 1;
}
int main(){
    cin>>n>>m;
    for(int i = 1;i<=n;i++) cin>>a[i].x>>a[i].y>>a[i].r,minn=min(minn,a[i].r);
    for(int i = n+1;i<=n+m;i++) cin>>a[i].x>>a[i].y;
    r=minn;
    while(l+1e-12<=r){
        double mid=(l+r)/2;
        if(check(mid)) ans=max(ans,mid),l=mid;
        else r=mid;
    }
    printf("%.12lf",ans);
    return 0;
}
```

~~看到这里，麻烦点个赞再走吧 QWQ~~   
~~码字不易，希望管理员能给通过。~~

---

## 作者：a_little_carrot (赞：2)

写的不好，敬请谅解。

[题目传送门](https://www.luogu.com.cn/problem/AT_s8pc_5_b)

## 乱搞解法
### 思路简述
初步观察，可以 $O(n^2)$ 扫一遍，拿...夺少？没错，这题 $n+m$ 就 $200$，一眼暴力。

考虑细节。根据题意，分类讨论扫的时候两个圆的关系。
1. 两个圆已知半径，取更小值。
2. 一个圆已知半径，计算与另一个圆的距离，用这个距离减去一个圆的半径，得到另一个圆最大的半径。
3. 两个圆都未知半径，计算两圆的距离，令其平分，最大化最小值。

这里因为会枚举到所有圆互相的关系，因此肯定会枚举到最小值。

还有一个求两点距离的公式：
$$dis=(x_1-x_2)^2+(y_1-y_2)^2$$
这个公式类似勾股定理，这里不做赘述。
### 代码
```cpp
#include "bits/stdc++.h"
using namespace std ;
struct Node {double x,y,r;} ;
int n,m ;
double ans=200,x,y,r ;
vector<Node> a ;
int R() {int x;cin>>x;return x;} ;
int main()
{
	ios::sync_with_stdio(false) ;
	cin.tie(0);cout.tie(0) ;
	cin>>n>>m ;
	for(int i=1;i<=n;++i) a.push_back({R(),R(),R()}) ;
	for(int i=n+1;i<=n+m;++i) a.push_back({R(),R(),0}) ;
	for(int i=0;i<n+m;++i) for(int j=i+1;j<n+m;++j)
	{
		Node u=a[i],v=a[j] ;
		double dis=sqrt(pow(u.x-v.x,2)+pow(u.y-v.y,2)) ; // 距离
		if(u.r&&v.r) ans=min(ans,min(u.r,v.r)) ; // 情况1
		else if(u.r||v.r) ans=min(ans,dis-max(u.r,v.r)) ; // 情况2
		else ans=min(ans,dis/2) ; // 情况3
	}
	cout<<fixed<<setprecision(15)<<ans ;
	return 0 ;
}
```

---

## 作者：Hy13_xsm (赞：0)

## 前言

这一篇题解没有用任何算法，比较好理解。

## 题意概述

有 $n$ 个指定半径的圆，$m$ 个不指定半径的圆，也就是说，这 $m$ 个圆你可以随便定义它的半径。要求将不指定半径的圆赋予一个半径，并且求出满足每一个圆**不重合**的图中最小圆的半径。这个值有很多个，要求求出这些值中最大的一个，保留 $15$ 位小数输出。

## 解决问题

要解决这个问题，我们就要让圆的半径尽量大。那我们就可以想到一个极限的情况，就是两个圆**刚好**碰边，但是不重合。在这种情况下，两个圆的半径和就是两点的距离。这么想不太直观，直接把图放出来就清楚了。

![](https://cdn.luogu.com.cn/upload/image_hosting/tcw4kenj.png)

然后需要知道的是求距离的方法。这个时候就需要用到勾股定理，公式如下：

$$\sqrt{a^2+b^2}=c$$

其中，$a$ 表示直角三角形其中一条直边长度，$b$ 则是另一条直边的长度。

那这里和勾股定理有什么关系呢？注意了，这里可以构造一个直角三角形。以 $\text{x}$ 轴和 $\text{y}$ 轴位参照画它们的平行线，再找到这两条线的交点，因为 $\text{x}$ 轴和 $\text{y}$ 轴本身平行，所以这样就可以构造出一个直角三角形。设第一个圆的坐标为 $(x_1,y_1)$，第二个圆的坐标为 $(x_2,y_2)$。容易得到，$a=|x_1-x_2|,b=|y_1-y_2|$。这样一来，就求出了两条直角边的距离，然后就可以根据公式求出 $c$。

还需要思考的是，如何让圆半径 $r$ 在满足要求的前提下最大。这里需要分类讨论。

1. 如果两个圆的半径都已经确定，直接求出这里面的最小值，并且将最终答案更新成这个值。需要注意的是，不要盲目选择求 $\text{max}$，这一道题有一个前提条件，选择最小的值才能慢足所有要求。
2. 如果两个圆中其中一个确定，另一个没有确定，那么根据碰边的极限思想可以确定一下未指定半径圆的半径，然后依旧是求出两个圆半径的最小值，因为我们需要满足所有圆都不重合的条件。
3. 如果两个圆的半径均没有指定，我们就需要规定它们两个的半径。首先，让其中一个圆的半径大，另一个小，会使得最小值变得更小，所以不可取。正确的做法是将距离平分，作为它们的半径，这样不会造成答案更小，也就维护了最大值。

至于过程，双层循环枚举一下即可。经过上述过程，就可以求出题目答案。

## 参考代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
double ans=INT_MAX;
struct node{
	int x,y;
	double val;
}a[1000005];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		int x,y,z;
		cin>>x>>y>>z;
		a[i]={x,y,z};
	}
	for(int i=n+1;i<=n+m;i++)
	{
		int x,y;
		cin>>x>>y;
		a[i]={x,y,0};
	}
	for(int i=1;i<=n+m;i++)
	{
		for(int j=i+1;j<=n+m;j++)
		{
			int x=a[i].x-a[j].x,y=a[i].y-a[j].y;
			double z=sqrt(pow(x,2)+pow(y,2));//两点距离 
			if(a[i].val&&a[j].val){
				ans=min(ans,min(a[i].val,a[j].val));
				continue;
			}//两点都确定 
			if(a[i].val)ans=min(ans,???);
			else if(a[j].val)ans=min(ans,???);//其中一点不确定 
			else ans=min(ans,???);//都没有指定 
		}
	}
	cout<<fixed<<setprecision(15)<<ans;
	return 0;
}
```

为了能让大家都学懂，给核心部分挖了一些空，根据上面的讲述填入即可。

## 后记

**对管理员说**：上面的代码没有防抄袭，只是为了检验理解程度，看您给不给过了。

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_s8pc_5_b)     
## 题意
给你 $n$ 个圆和 $m$ 个点，现在让你找到一个数 $r$，并给这 $m$ 个点增加半径使其成为圆，要求半径均大于等于 $r$，并且最后所有的圆不能相交，求**所有圆**中最小半径的最大值。    
## 解法
一眼二分，虽然可以更优。    
显然我们直接令所有圆的半径为同一个值更优。所以我们二分这个值并判定圆的相交即可。    
圆的相交很好判定，只需要将两圆圆心距离和半径之和进行比较即可。    
时间复杂度 $O(nm\log w)$，$w$ 是值域。    
```cpp
//完整缺省源请见洛谷云剪贴板 jo5j6ogx
cst int N=1e2;
int n,m;
struct Circle{
	Point p;
	db r;
}a[N+10];
Point b[N+10];
db l,r=1e2,mid,ans;
il bool chk(cst Circle& a,cst Circle& b){
	Point p(a.p.x-b.p.x,a.p.y-b.p.y);
	ret dcmp(p.len()-(a.r+b.r))<0;
}
il bool check(db x){
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			if(chk(Circle{b[i],x},a[j])){
				ret 0;
			}
		}
	}
	for(int i=1;i<=m;i++){
		for(int j=i+1;j<=m;j++){
			if(chk(Circle{b[i],x},Circle(b[j],x))){
				ret 0;
			}
		}
	}
	ret 1;
}
int main(void){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	ans=1e12;
	for(int i=1;i<=n;i++){
		cin>>a[i].p.x>>a[i].p.y>>a[i].r;
		ans=_min<db>(ans,a[i].r);
	}
	if(m==0){
		cout<<fixed<<setprecision(7)<<ans<<endl;
		ret 0;
	}
	if(ans!=1e12){
		r=ans;
	}
	ans=0;
	for(int i=1;i<=m;i++){
		cin>>b[i].x>>b[i].y;
	}
	while(dcmp(r-l)>0){
		mid=(l+r)/2.0;
		if(check(mid)){
			ans=mid;
			l=mid;
		}else{
			r=mid;
		}
	}
	cout<<fixed<<setprecision(7)<<ans<<endl;
	ret 0;
}
```


---

## 作者：__delta_epsilon__ (赞：0)

### 题目大意

在一个坐标平面上有 $N$ 个给定的圆心和半径的圆，和 $M$ 个给定圆心但不给定半径的圆，请问如何设置这 $M$ 个圆的半径，使得这些圆中没有两两相交或内含的两个圆。求出所有方法中，半径最小的圆的半径的最大值。

这里，给定半径的圆的坐标和半径的下标是从 $1$ 到 $N$ 的，而没有给定半径的圆的坐标的下标是从 $N+1$ 到 $N+M$ 的。

### 思路分析

显然，半径最小的圆的半径若要最大，则可取所有的圆半径相同，因为更大半径的圆没有必要考虑。设这个半径为 $R$。

分两种情况讨论。

#### Part 1 两个不定半径的圆

对于两个圆心 $(x_1,y_1),(x_2,y_2)$，在不相交的情况下，要使半径最大，则这两个圆一定相切。又因为圆的半径相等，所以，

$$2R_0=\sqrt{(x_2-x_1)^2+(y_2-y_1)^{2}}$$

其中，$R_0$ 表示该两个圆的局部最优解。因此，

$$R_1\le R_0=\dfrac{\sqrt{(x_2-x_1)^2+(y_2-y_1)^{2}}}{2}$$

所以在所有的不定半径的圆中，

$$R_1=\min \left\{\dfrac{\sqrt{(x_i-x_j)^2+(y_i-y_j)^{2}}}{2}\right\}\qquad(i,j\in[N+1,N+M])$$

#### Part 2 一个不定半径的圆和一个定半径的圆

这两个圆还是相切的。但是这两个圆的半径不一定相等，因此，

$$R_0+r=\sqrt{(x_2-x_1)^2+(y_2-y_1)^{2}}$$

其中，$R_0$ 表示该两个圆的局部最优解，$r$ 表示给定圆的半径。因此，

$$R_2\le R_0=\sqrt{(x_2-x_1)^2+(y_2-y_1)^{2}}-r$$

所以，在这种情况下，

$$R_2=\min\left\{\sqrt{(x_i-x_j)^2+(y_i-y_j)^{2}}-r\right\}\qquad(i\in[1,N],j\in[N+1,N+M])$$

#### 总结

综上所述，

$$R=\min\left\{R_1,R_2,r_{i}\right\}\qquad(i\in[1,N])$$

其中 $R_1,R_2$ 分别表示上面求出来的两种情况的答案，$r_i$ 则表示每个给定半径的圆的半径。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int N, M;
double ans = 1e308;
// 答案初始值设置为最大值，double 的上限是 pow(2,1023)-1 ≈ 1.7e308。

struct Circle {
	double x, y, r;
} c[202]; // 用 struct 定义一个圆类型。

double dist(Circle x, Circle y) {
	return sqrt((x.x - y.x) * (x.x - y.x) + (x.y - y.y) * (x.y - y.y));
} // 求距离的函数。

signed main() {
	cin >> N >> M;
	for (int i = 1; i <= N + M; i++) {
		cin >> c[i].x >> c[i].y;
		if (i <= N) // 只有前 N 个圆需要输入半径。
			cin >> c[i].r;
	}
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= M; j++) {
			if (i == j)
				continue;
			ans = min(ans, dist(c[N + i], c[N + j]) / 2);
		}
	} // 第一种情况。
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			ans = min(ans, dist(c[i], c[N + j]) - c[i].r);
		}
	} // 第二种情况。
	for (int i = 1; i <= N; i++) {
		ans = min(ans, c[i].r);
	}
	printf("%.015lf", ans);
	// 样例里面精确了 15 位，其实精确到小数点后 6 位即可。
	return 0;
}
```

AtCoder 运行编号：43038241。

运行时间：8 ms。

---

