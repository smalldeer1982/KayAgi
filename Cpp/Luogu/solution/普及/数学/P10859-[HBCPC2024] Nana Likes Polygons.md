# [HBCPC2024] Nana Likes Polygons

## 题目描述

娜娜的电子宠物 MACARON 喜欢在房间里四处走动。娜娜想要创建一个有界区域，让 MACARON 可以在其中活动。

房间中的位置可以用二维坐标系表示，娜娜提供了一组顶点。娜娜喜欢多边形，现在想选择一个顶点的子集，形成一个凸多边形的端点。然而，娜娜还希望确保选择的区域不要太大。

因此，她将确定以给定顶点的子集为端点的凸多边形的最小可能面积。如果不存在这样的凸多边形，请输出 `-1`（不带引号）。

## 说明/提示

对于第一个测试用例，选择 $(2, 2), (-3, 0)$ 和 $(0, 2)$ 作为一个凸多边形的端点，其面积为 2。可以证明这是该情况下的最小面积。

对于第二个测试用例，这三个顶点无法形成凸多边形。（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
2
4
0 -1
-3 0
0 2
2 2
3
-1 -1
0 0
1 1```

### 输出

```
2
-1```

# 题解

## 作者：dc_ansan_tangmingyi (赞：14)

[题目](https://www.luogu.com.cn/problem/P10859)

## 题意：

给定 $n$ 个点，选任意 $3$ 个点，求着 $3$ 个点所形成的图形的最小面积。

## 思路：

由于 $n \le 100$ ，所以暴力枚举即可。时间复杂度 $O(n^3)$ 。

## AC CODE:

```cpp
#include<bits/stdc++.h>
using namespace std; 
double x[105] , y[105]; 
double area(double x1 , double y1 , double x2 , double y2 , double x3 , double y3){ //求面积函数
	return 0.5 * (x1 * y2 + x2 * y3 + x3 * y1 - x1 * y3 - x2 * y1 - x3 * y2); 
}
void solve(){
    int n; 
    cin >> n; 
    for(int i = 1; i <= n; i ++){
    	cin >> x[i] >> y[i]; 
    }
    
    double ans = 1e18;
    //枚举3个点
    for(int i = 1; i <= n; i ++){
    	for(int j = i + 1; j <= n; j ++){
    		for(int k = j + 1; k <= n; k ++){
    			double t = area(x[i] , y[i] , x[j] , y[j] , x[k] , y[k]); 
    			t = fabs(t); 
    			if(t <= 0.0) continue; //注意面积不能为0
    			ans = min(ans , t); 
    		}
		}
	}
    			
    if(ans == 1e18) cout << -1 << endl; 
    else cout << ans << endl;
}
int main(){
	int T; 
	cin >> T; 
	while(T --) solve(); 
	return 0; 
}
```

---

## 作者：liuChF (赞：2)

## 思路

先说结论：**要求最小的凸多边形，就是是最小三角形**。考虑反证，如果答案图形不为三角形，则一定可以将其分出若干个更小的三角形。因此 $O(n^3)$ 暴力枚举即可。

## 做法

枚举任意 $3$ 个点，$ans$ 记录面积不为 $0$ 的三角形的最小面积，则 $ans$ 即为答案。那无解的情况呢？将 $ans$ 的初始值设为极大值，若枚举完后 $ans$ 的值没有变，就说明无解（即所有的三角形面积都为 $0$，换句话说就是构不成三角形）。这样做也不用考虑选的点的重复问题。

至于面积的计算，海伦公式会有误差，其实**直接用三个点的坐标进行计算**就行了，不会的自行百度。

$$S=\frac{1}{2} (x1y2 + x2y3 + x3y1 - x1y3 - x2y1 - x3y2)$$

```cpp
#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;
const int N = 1e5 + 10;
int T, n;
double ans = INF;
struct node {
	int x, y;
} s[N];
void check(int a, int b, int c) {
	int x1 = s[a].x, x2 = s[b].x, x3 = s[c].x, y1 = s[a].y, y2 = s[b].y, y3 = s[c].y;
	double S = (x1 * y2 + x2 * y3 + x3 * y1 - x1 * y3 - x2 * y1 - x3 * y2) / 2.0;
	if (S < 0) S *= -1.0 ;
	if (S != 0) ans = min(ans, S);
}
int main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >> T;
	while (T--) {
		ans = INF;
		cin >> n;
		for (int i = 1; i <= n; i++) cin >> s[i].x >> s[i].y;
		for (int a = 1; a <= n; a++)
			for (int b = 1; b <= n; b++)
				for (int c = 1; c <= n; c++)
					check(a, b, c);
		if (ans == INF)cout << -1 << '\n';
		else cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：Vct14 (赞：2)

题意：给定 $n$ 个点，求由其中某些点组成的凸多边形的面积最小值。

首先很容易知道三角形面积最小，因为任意大于三边形选出三个顶点组成的三角形面积一定小于该多边形。

因此暴力枚举所有三角形即可。注意特判三点共线（即面积为 $0$）的情况。

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N=102;
const double M=1e18;
int x[102],y[102];

double mj(int i,int j,int k){
	return (double)abs(x[i]*y[j]-x[i]*y[k]+x[j]*y[k]-x[j]*y[i]+x[k]*y[i]-x[k]*y[j])/2.0;
} // 也可以用海伦公式

signed main(){
	int t;cin>>t;
	while(t--){
		int n;cin>>n;
		for(int i=1; i<=n; i++) cin>>x[i]>>y[i];
		double mn=M;
		for(int i=1; i<=n; i++){
			for(int j=i+1; j<=n; j++){
				for(int k=j+1; k<=n; k++){
					double s=mj(i,j,k);
					if(s==0) continue;
					if(s<mn) mn=s;
				}
			}
		}
		if(mn==M) puts("-1");
		else printf("%.6lf\n",mn);
	}
	return 0;
}
```

这里的面积公式这样证明：$\dfrac{1}{2}(x_3-x_1)(y_2-y_1)+\dfrac{1}{2}(y_3-y_1)(x_3-x_2)-\dfrac{1}{2}(x_3-x_1)(y_3-y_1)=\dfrac{1}{2}(x_3y_2-x_3y_1-x_1y_2+x_1y_1+x_3y_3-x_2y_3-x_3y_1+x_2y_1-x_3y_3+x_3y_1+x_1y_3-x_1y_1)=\dfrac{1}{2}|x_1y_2+x_2y_3+x_3y_1-x_2y_1-x_3y_2-x_1y_3|。$

---

## 作者：mysterys (赞：1)

向量大法好！
# 思路
1. 题目让你求面积最小的凸多边形，显然：三角形面积最小。所以枚举三个点。
2. 注意精度问题：如果用海伦公式会出现意外情况，所以我们需要 **向量叉积**！
3. 其实不需要检查三个点是否合法，因为不合法的点算出来的面积一定为 $0$。
# 时间复杂度
枚举三个点，所以时间复杂度：$O(T n^3 )$。
# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long double db;
const int N=105;
const db inf=1e17;
struct node{
	db x,y;
}a[N];
int n;
db ans;
inline db dis(node i,node j){
	return sqrt((i.x-j.x)*(i.x-j.x)+(i.y-j.y)*(i.y-j.y));
}
inline db S(node a,node b,node c){
	db sum=0.00;
	sum+=a.x*b.y-a.y*b.x;
	sum+=b.x*c.y-c.x*b.y;
	sum+=a.y*c.x-a.x*c.y;
	if(fabs(sum)/2==0) return inf;
	return fabs(sum)/2;
}
inline db work(int i,int j,int k){
	double b1=dis(a[i],a[j]);
	double b2=dis(a[k],a[i]);
	double b3=dis(a[j],a[k]);
	if(b1+b2>b3&&b1+b3>b2&&b2+b3>b1) {
		return S(a[i],a[j],a[k]);
	}
	return inf;
}
inline void solve(){
	for(int i=1;i<=n;i++) a[i].x=a[i].y=0.00;
	cin>>n;
	ans=inf;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j) continue;
			for(int k=1;k<=n;k++){
				if(k==i||k==j||i==j) continue;
				ans=min(ans,work(i,j,k));
			}
		}
	}
	if(ans==inf){
		cout<<-1<<endl;
	}else{
		cout<<ans<<endl;
	}
}
signed main(){
	cin.tie(nullptr)->ios::sync_with_stdio(false);
	cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--){
		solve();
	}
	return 0;
}
```

---

## 作者：Crazyouth (赞：1)

## 分析

如果我们知道三个点的坐标 $x_1,y_1,x_2,y_2,x_3,y_3$，我们可以知道以这三个点为顶点的三角形的面积 $S=|x_1y_2+x_2y_3+x_3y_1-x_1y_3-x_2y_1-x_3y_2|$。那么我们只需要枚举三个点，如果这三个点围成的三角形面积为 $0$，那么不计算此三个点，否则更新答案。如果答案始终未被更新，输出 `-1`。注意：double 为 $0$ 的判定条件是小于 $eps$，这里我取的是 $eps=10^{-8}$。

## AC Code
```
#include <bits/stdc++.h>
using namespace std;
#define int long long
const long double eps=1e-8;
long double x[110],y[110];
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		for(int i=1;i<=n;i++) cin>>x[i]>>y[i];
		if(n<=2)
		{
			cout<<-1<<'\n';
			continue;
		}
		long double ans=1e18;
		for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		for(int k=1;k<=n;k++)
		{
			long double S=0.5*(x[i]*y[j]+x[j]*y[k]+x[k]*y[i]-x[i]*y[k]-x[j]*y[i]-x[k]*y[j]);
			if(S>eps) ans=min(ans,S);
		}
		if(ans==1e18) cout<<-1<<'\n';
		else cout<<fixed<<setprecision(8)<<ans<<'\n';
	}
}

---

## 作者：__qkj__ (赞：0)

## 题目意思
给你 $n$ 对点的坐标，求最小的用这些点围成的多边形的面积。
## 解题思路
显然，三角形面积最小。

先三重循环，暴力枚举三个点。

再用欧氏距离求出两点之间距离。欧氏距离公式如下：

$$
\operatorname{dis}(a_{x,y},a_{xx,yy})=\sqrt{{(x-xx)}^2+{(y-yy)}^2}
$$

再用海伦公式求出三角形面积。公式如下：

$$
p=\dfrac{a+b+c}{2}
$$
$$
S=\sqrt{p\times(p-a)\times(p-b)\times(p-c)}
$$

若 $S=0$，则该三角形不合法，舍去。否则取最小值。

**注意：要用 `long double`！**
## Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
struct node
{
	double x,y;
}a[110];
double dis(double x,double y,double xx,double yy)
{
	return sqrt(pow(x-xx,2)+pow(y-yy,2));
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	while(t--)
	{
		double minn=1e18;
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i].x>>a[i].y;
		for(int i=1;i<=n-2;i++)
			for(int j=i+1;j<n;j++)
				for(int k=j+1;k<=n;k++)
				{
					double aa=dis(a[i].x,a[i].y,a[j].x,a[j].y);
					double b=dis(a[k].x,a[k].y,a[j].x,a[j].y);
					double c=dis(a[i].x,a[i].y,a[k].x,a[k].y);
					double p=(aa+b+c)/2;
					double s=sqrt(p*(p-aa)*(p-b)*(p-c));
					if(s>0)minn=min(minn,s);
				}
		if(minn==1e18)printf("-1\n");
		else printf("%.8Lf\n",minn);
	}
	return 0;
}
```

---

## 作者：KAqwq (赞：0)

## 插曲
昨天做题的时候由于面积计算错误吃了一发罚时，有点难受。
## 题意
给定 $n$ 个二维平面直角坐标系中凸多边形的顶点坐标，求可构成凸多边形的最小面积。
## 思路
可选定其中 $3$ 个点求三角形的面积，由小学数学可知， 三点共线时无解。考虑向量叉积求三角形面积，公式为 $S =  \lvert(x_2 - x_1) \cdot (y_3 - y_2) - (x_3 - x_2) \cdot (y_2 - y_1) \rvert$。注意到 $n \leq 100$，直接暴力枚举即可，时间复杂度 $O(n ^ 3)$，显然可以通过此题。
## code
```

#include <bits/stdc++.h>
#define N 105

typedef long long LL;
typedef double d;

inline d solve(d x1, d x2, d x3, d y1, d y2, d y3) {
	return 1.0 / 2.0 * ((x2 - x1) * (y3 - y2) - (x3 - x2) * (y2 - y1));
}

struct node {
	LL x, y;
}a[N];
int main() {
	LL T;
	std::cin >> T;
	while (T--) {
		LL n; std::cin >> n;
		for (LL i = 1; i <= n; ++i) {
			std::cin >> a[i].x >> a[i].y;
		}
		d ans = 1e9;
		for (LL i = 1; i <= n; ++i) {
			for (LL j = i + 1; j <= n; ++j) {
				for (LL k = j + 1; k <= n; ++k) {
					d res = fabs(solve(a[i].x, a[j].x, a[k].x, a[i].y, a[j].y, a[k].y));
					if (res < 1e-9) continue;
					ans = std::min(ans, res);
				}
			}
		}
		if (ans == 1e9) std::cout << -1 << '\n';
		else std::cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：luuia (赞：0)

### 题目大意

给定 $n$ 个点，求一个顶点均为给定点的面积最小的凸多边形，多测。

### Solution

我们发现满足面积最小的凸多边形一定是三角形。

考虑反证法。若面积最小的凸多边形不为三角形，则我们可以将它三角剖分，得到的三角形面积要小于原多边形面积，因此与假设矛盾。

考虑到 $n \le 100$，我们可以直接 $O(n^3)$ 枚举三角形，特判一下三点贡献的情况。如果所有点都共线，显然是不存在凸多边形的，直接输出 $-1$ 即可。

### Code

代码放在 [云剪贴板](https://www.luogu.com.cn/paste/jc6lewdp) 里了。

---

## 作者：Cyx20110930 (赞：0)

# 简要题意

平面上有一些点，问你由其中至少三个点组成的图形的面积最小是几，如果组成不了图形，输出 `-1`。

# Sol

很明显最小的一定是三角形。

感性证明：任何一个正 $n$ 边形，都可以分成一个三角形，与一个正 $n-1$ 边形，自然三角形的面积小于这个正 $n$ 边形。

所以枚举三个点，不断刷新面积最小值就行了。

# Code

注意特判三点共线！

```
#include <bits/stdc++.h>
using namespace std;
struct node{
    double x,y;
}po[1000005];
void solve(){
    double ans=0x3f;
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>po[i].x>>po[i].y;
    }
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            for(int z=j+1;z<=n;z++){
                double sum=po[j].x*po[z].y-po[z].x*po[j].y+po[i].x*po[j].y-po[j].x*po[i].y-po[i].x*po[z].y+po[z].x*po[i].y;
                sum=abs(sum);
                if (sum != 0){
                    ans=min(ans,sum/2.0);
                }
            }
        }
    }
    if (ans==0x3f){
        cout<<-1<<endl;
    }
    else{
        cout<<ans<<endl;
    }
}
int main(){
    int t;
    cin>>t;
    while(t--){
        solve();
    }
}
```

---

## 作者：Mr_ZhangLin (赞：0)

显然，三角形面积最小，因为如果选了 $4$ 个点的话可以连接一条对角线使其变成两个面积更小的三角形，更多点同理。

于是可以枚举三角形的三个顶点，代入面积公式 $s= \frac {|(x_1-x_3)(y_2-y_3)-(y_1-y_3)(x_2-x_3)|} {2}$ 即可得到答案。

code:

```cpp
#include <bits/stdc++.h>
#include <iostream>
using namespace std;
double x[105],y[105];
int main(){
	int t;
	cin>>t;
	while(t--){
		double ans=99999999;
		memset(x,0,sizeof x);
		memset(y,0,sizeof y);
		int n;
		cin>>n;
		for(int i=0;i<n;i++){
			cin>>x[i]>>y[i];
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<i;j++){
				for(int k=0;k<j;k++){
					double s=abs((x[i]-x[k])*(y[j]-y[k])-(y[i]-y[k])*(x[j]-x[k]))/2;
					if(s<ans&&s!=0)ans=s;
				}
			}
		}
		if(ans==99999999)cout<<-1<<endl;//特判，如果没有就输出-1
		else cout<<ans<<endl;
	}
}
```

复杂度 $O(N^3T)$, 可以 AC。

---

## 作者：shicj (赞：0)

# P10859 [HBCPC2024] Nana Likes Polygons 题解

## 0x00 题目大意

给出平面上一些点，求以这些点的子集为顶点组成的凸多边形的面积的最小值。

## 0x01 解题思路

易证，最终的图形一定是一个三角形（如果是更多边形，必然可以削掉一块使得面积更小）。

看到数据范围：$1\le n\le 100$，完全可以 $O(n^3)$ 枚举三角形，求最小面积。

如何求三角形面积？可以用这个公式：

$$S_{\Delta ABC}=\dfrac{|A.x\times B.y+B.x\times C.y+C.x\times A.y-A.x\times C.y-B.x\times A.y-C.x\times B.y|}{2}$$

tips：不要用海伦公式，精度会炸。

如果三角形面积为 $0$，则说明当前三个点构不成三角形，如果所有组合面积都为 $0$，则无解。

## 0x02 AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
struct point{
    double x,y;
    friend double operator - (point _1,point _2){
        return sqrt((_1.x-_2.x)*(_1.x-_2.x)+(_1.y-_2.y)*(_1.y-_2.y));
    }
}a[1001];
double SS(point A,point B,point C){
//原来打算用海伦公式，结果炸了
    double AB=A-B,AC=A-C,BC=B-C;
    double p=(AB+AC+BC)/2.0;
    //cout<<"p="<<p<<endl;
    double x=p*(p-AB)*(p-BC)*(p-AC);
    if(x<=0)return 0;
    return sqrt(x);
}
double S(point A,point B,point C){
    return 0.5*fabs(A.x*B.y+B.x*C.y+C.x*A.y-A.x*C.y-B.x*A.y-C.x*B.y);
}
void solve(){
    double ans=-1;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i].x>>a[i].y;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            for(int k=1;k<=n;k++){
                if(i==j||j==k||i==k)continue;
                if(S(a[i],a[j],a[k])!=0){
                    if(ans!=-1)
                        ans=min(ans,S(a[i],a[j],a[k]));
                    else ans=S(a[i],a[j],a[k]);
                }
            }
        }
    }
    if(ans==-1)cout<<-1<<endl;
    else printf("%.8lf\n",ans);
}
signed main(){
    int t;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
```

---

## 作者：Your_Name (赞：0)

## 思路
其实不难发现：想要面积最小的凸多边形，那么这个多边形一定是三角形。

为什么呢？

其实很好证明，我们先假设有一个不是三角形的最小面积的凸多边形，那么根据数学知识，我们一定能把这个多边形分成若干个三角形，且分成的三角形面积还一定比他小。与假设矛盾，因此，答案一定为三角形就显而易见了。

看到 $1 \leq n \leq 100$ 就直接 $O(n^3)$ 暴力枚举求解即可。注意有可能有重复点和 $n \leq 2$ 的情况，特判处理就行。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n;
struct node{
    int x, y;
    bool operator ==(node a) const{
        return a.x == x && a.y == y;//重载方便判断
    }
}d[110];
double S(node a, node b, node c){
    return 1.0 * fabs((b.x * c.y - c.x * b.y) -(a.x * c.y- c.x * a.y) + (a.x * b.y - b.x * a.y)) / 2.0;//坐标系里求面积，不清楚的可以看看其他题目
}
int main(){
    cin >> t;
    while(t --){
        memset(d, 0, sizeof d);//清不清无所谓
        double ans = 0x3f3f3f3f;//记得附初始值
        cin >> n;
        for(int i = 1; i <= n; i ++){
            cin >> d[i].x >> d[i].y;
        }
        if(n <= 2){
            printf("-1\n");
            continue;
        }//绝对不可能组成三角形
        bool fl = 0;
        for(int i = 1; i <= n; i ++){
            for(int j = 1; j <= n; j ++){
                for(int k = 1; k <= n; k ++){
                    if(i == j || i == k|| j == k || d[i] == d[j] || d[i] == d[k] || d[j] == d[k])continue;//特判相同
                    double s = S(d[i], d[j], d[k]);//算面积
                    if(s != 0){//共线的情况
                        fl = 1;
                        ans = min(ans, s);
                    }
                }
            }
        }
        if(fl)printf("%.8lf\n", ans);//注意精度问题，考场上WA了
        else printf("-1\n");
    }
    return 0;
}
```
 _完结撒花_

---

## 作者：LostKeyToReach (赞：0)

一道结论比较显然的题。

首先，我们有一个结论：选三角形必定最优。如何证明呢？首先，三角形本身就是凸多边形，其次，若有四条边以上的凸多边形，我们可以选择其中的三个点连成一个三角形，这时面积更小。因此，我们的结论是正确的。

那么，我们可以枚举三个点的坐标，用叉积计算一下三角形面积即可，时间复杂度 $O(n ^ 3)$。

参考代码如下：

```cpp
#include <bits/stdc++.h>
#define ll long long
#define int long long
#define debug(x) cerr << (#x) << '\n'
#define pii pair <int, int>
#define pb emplace_back
#define chkmin(x, y) x > y ? x = y : 0
#define chkmax(x, y) x < y ? x = y : 0
#define L(i, a, b) for (int i = (a); i <= (b); i++)
#define R(i, a, b) for (int i = (a); i >= (b); i--)
#define x first
#define y second
using namespace std;
const int P = 998244353;
vector <pii> p;
signed main() {
	int t;
	cin >> t;
	while (t--) {
		p.clear();
		int n;
		cin >> n;
		L(i, 1, n) {
			int f, s;
			cin >> f >> s;
			p.pb(f, s);
		}
	//	sort(p.begin(), p.end());
		double s = 1e18;
		L(i, 0, n - 1) {
			L(j, i + 1, n - 1) {
				L(k, j + 1, n - 1) {
					double ans = p[j].x * p[k].y - p[j].y * p[k].x;
					ans -= (p[i].x * p[k].y - p[i].y * p[k].x);
					ans += (p[i].x * p[j].y - p[i].y * p[j].x);
					ans = fabs(ans);
					if (ans != 0) chkmin(s, ans / 2.0);
				}
			}
		}
		if (n < 3 || s == 1e18) cout << -1 << '\n';
		else cout << s << '\n';
	}
}
```

---

