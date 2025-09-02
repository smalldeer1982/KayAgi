# Hyperdrive

## 题目描述

在遥远的星系中，有n个有人居住的行星，编号从1到n。它们彼此之间的距离很远，它们之间的通信非常困难。

直到在1号行星发明了一个超级驱动器。1号星球上建造了n-1艘宇宙飞船，并将这些船只送往其他星球以通知这一革命性的发明。

虽然这有点矛盾，但超空间被表示为简单的三维欧几里德空间。行星可以被认为是其中的固定点，并且没有两个点重合并且没有三个点位于同一直线上。在两个行星之间具有超驱动的船的沿着恒定速度的直线航行，这对于所有船只是相同的。这就是为什么超空间中的距离是用超级年中测量的（一艘带有超级驱动的船只在s年中走了s超级年的距离）。

当船到达一个星球时，行星的居民将它拆开，建造n-2艘与超级驱动器相同的船并将它们发送到其他n-2个行星（除了船到达的行星之外）。
与他们从一个行星移动到另一个行星的时间相比，制造新船的时间非常短，可以忽略不计。新船与最初发送的船完全相同：它们沿着直线轨迹以相同的恒定速度移动，并且在到达行星时执行相同的任务，即被拆卸以建造新的n-2船并将它们发送到除了船到达的行星以外的所有行星。因此，围绕银河系传播重要新闻的过程仍在继续。

然而，超级驱动器的创造者急忙传播关于他们的发明的消息，以至于他们没有完全研究当两艘船在超空间碰撞时发生的事情。如果两艘移动的船只在同一个点上，它们会引发巨大的力量爆炸，导致银河系的毁灭！

你的任务是找到从第一艘飞船发射的那一刻起银河系将继续存在的时间。

感谢@[sunson](https://www.luogu.org/space/show?uid=148016)提供的翻译

## 样例 #1

### 输入

```
4
0 0 0
0 0 1
0 1 0
1 0 0
```

### 输出

```
1.7071067812
```

# 题解

## 作者：xuchuhan (赞：2)

## Description

在 $1$ 号行星发射 $n-1$ 艘飞船，他们分别飞向 $2,3,\dots,n$ 号行星。当飞船到达目的地的行星后，那颗行星立即发出 $n-2$ 艘飞船，飞往其他行星，以此类推。

求某 $2$ 艘飞船相撞的最小时刻。

## Solution

显然，第 $1$ 轮飞船不会相撞。第 $2$ 轮飞船与第 $1$ 轮飞船不会相撞。（即从 $1$ 点出发飞到 $x$ 点的飞船再从 $x$ 点出发飞到 $y$ 点的飞船不会与从 $1$ 点出发飞到 $y$ 点的飞船相撞），因为三角形两边之和大于第三边。

但是，第 $2$ 轮飞船的两艘船就有可能相撞。

从 $1$ 点飞到 $x$ 点，准备从 $x$ 点到 $y$ 点的船一定会与从 $1$ 点飞到 $y$ 点，准备从 $y$ 点到 $x$ 点的船相撞。所以，直接枚举点 $x,y$，计算最小相撞时间即可。

显然，这两艘飞船的相撞时间为点 $1,x,y$ 组成的三角形的周长除以 $2$。

时间复杂度为 $\mathcal{O(n^2)}$。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5005;
int n;
double ans=1e18;
struct node{
	double x,y,z;
}a[N];
double Getdis(node a,node b){
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z));
	//计算欧几里得距离
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i].x>>a[i].y>>a[i].z;
	for(int i=2;i<=n;i++){
		for(int j=2;j<=n;j++){
		    //枚举2点（1点是起点，不计算在内）
			if(i==j)
				continue;
			//2点不能相同
			double t=Getdis(a[1],a[i])+Getdis(a[1],a[j])+Getdis(a[i],a[j]);
			ans=min(ans,t/2);//统计最小值
		}
	}
	printf("%.6lf",ans);
	return 0;
}
```

---

## 作者：popcoount (赞：2)

简单的思维题。。。
## 题目大意
从 $1$ 号行星发出 $n-1$ 个飞船，然后到达另一颗星球之后再发出 $n-2$ 个，...，算出某两个飞船碰撞的最早时间。
## 思路
第一波飞船肯定不会撞，第二波飞船肯定不会与第一波飞船相撞，因为三角形的两边之和一定大于第三边且题目保证三点不共线；但是第二波飞船与之后发出的飞船就可能会相撞了，所以枚举每两个发出第二代火箭的星球就好了。
## 代码

```cpp
#include <iostream>
#include <cmath>
using namespace std;
const int N = 5005, inf = 0x3f3f3f3f;
struct node {
    double x, y, z;
}a[N];
int n;
double cal(const node a, const node b) {//三维空间内两点的距离公式
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%lf%lf%lf", &a[i].x, &a[i].y, &a[i].z);
    }
    double Min = inf;
    //枚举每两个发出第二代火箭的星球
    for (int i = 2; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            Min = min(Min, cal(a[1], a[i]) + cal(a[1], a[j]) + cal(a[i], a[j]));
        }
    }
    printf("%.10lf", Min / 2.0);//因为要求相遇时间，所以需要用距离/2
    return 0;
}
```


---

## 作者：Tachibana27 (赞：1)

比较水，考察多维欧几里得距离计算


------------

> 行星可以被认为是其中的固定点，并且没有两个点重合并且没有三个点位于同一直线上。

所以第一波飞船一定不会相撞，不用考虑第一波飞船。

根据三角形不等式（两边之和大于第三边）可以发现第二波飞船必然出现相撞。

> 虽然这有点矛盾，但超空间被表示为简单的三维欧几里德空间。

所以给出三维欧几里得距离公式：$\sqrt{(x_{a}-x_{b})^{2}+(y_{a}-y_{b})^{2}+(z_{a}-z_{b})^{2}}$。

由于需要求相遇时间，答案需要 $\div 2$。

随后 $O(n^{2})$ 暴力枚举取距离的最小值保留 $6$ 位小数即可。

详见代码

[code](https://www.luogu.com.cn/paste/klqwv8nd)

---

## 作者：Vecinrix_dabreck (赞：1)

## 题意
找到两个飞船碰撞的最早时间。
## 思路
首先第一次发射消息是肯定不会有飞船碰撞的，因为题目中说了
> 行星可以被认为是其中的固定点，并且没有两个点重合并且没有三个点位于同一直线上。

所以我们再来看第二次，第二次一定会相撞，因为有三角形三边不等式（两边之和大于第三边）得知，当飞船由 1 号星球前往 2 , 3 号星球时，一定会在 F 点相遇。但又无法与到 4，5 的飞船相遇，故我们只需要寻找以 1, x, y 三点所构成的三角形周长的最小值再除以 2 即可（因为求相遇时间）。

如图：
![1](https://cdn.luogu.com.cn/upload/image_hosting/lxdsq438.png)

$PS.$ 这里涉及到了三维直角坐标系里两点的距离公式，直接给出：坐标系内两点 $a(x_a, y_a, z_a)$ 和 $b(x_b, y_b, z_b)$ 的距离为 $d=\sqrt {(x_a - x_b)^2 + (y_a - y_b)^2 + (z_a - z_b)^2}$

## Code
```cpp
#include <cstdio>
#include <cmath>
int n;
double ans=1e18,x[5005],y[5005],z[5005];
inline double min(double a,double b) {return a<b?a:b;}//手写 min 函数
inline double d(int s1,int s2) {return (double)sqrt((x[s1]-x[s2])*(x[s1]-x[s2])+(y[s1]-y[s2])*(y[s1]-y[s2])+(z[s1]-z[s2])*(z[s1]-z[s2]));}
//s1, s2两点间的距离公式
signed main() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%lf %lf %lf",&x[i],&y[i],&z[i]);
	for(int i=3;i<=n;++i) {//不要枚举 1 星球或者重复的星球！！！
		for(int j=2;j<i;++j) {
			ans=min(ans,d(i,j)+d(1,i)+d(1,j));
		}
	}
	printf("%.6lf",ans/2);//保留 6 位小数
	return 0;
}
```

---

## 作者：N_z_ (赞：1)

## 思路
1. 我们可以发现在第一次扩散消息时不会相撞，因为题目保证三点不共线。
2. 我们可以发现第二次扩散时必然会相撞，因为我们假设有 $i,j$ 两个星球。
	1. 一号星球分别扩散到 $i,j$ 号。
   2. $i,j$ 号收到消息后相互扩散。
   3. 由于三角形任意两边之和大于第三边，所以一定会相撞
3. 可以发现答案就是任意两个星球与第一个星球组成的三角形的周长 $\div 2$ 的最小值。

暴力 $n^2$ 算法即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
    int x,y,z;
}a[5001];
#define calc(q,w) (double)(sqrt((a[q].x-a[w].x)*(a[q].x-a[w].x)+(a[q].y-a[w].y)*(a[q].y-a[w].y)+(a[q].z-a[w].z)*(a[q].z-a[w].z)))
int main(){
	int n;
	cin>>n;
	for(int x=1;x<=n;x++)cin>>a[x].x>>a[x].y>>a[x].z;
	double ans=1e18;
	for(int x=2;x<=n;x++)
	for(int y=2;y<x;y++)
	ans=min(ans,calc(1,x)+calc(1,y)+calc(x,y))/*,cout<<x<<','<<y<<','<<calc(1,x)<<','<<calc(1,y)<<','<<calc(x,y)<<endl*/;
	printf("%.10lf\n",ans/2);
}
```

---

## 作者：zym20249_ (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF213A) 

## 题意
在空间中，有 $n$ 个行星，编号从 $1$ 到 $n$，行星可看作是固定点，任意两点不重合，任意三个点不共线。在 $1$ 号行星发射 $n−1$ 艘飞船，他们分别飞向 $2$ 至 $n$ 号行星。当飞船到达目的地的行星后，那颗行星立即发出 $n−2$ 艘飞船，飞往其他行星，以此类推。
飞船在两颗行星之间沿直线以恒定速度飞行，所有飞船速度相同。若两艘飞船在任意一个三维空间点相遇，则会发生爆炸，求出爆炸会发生的最早时刻。

## 思路
由于没有三点共线所以同一个球场发射的无人机永远也不会相撞，所以不需要查看第一个球场所发射的无人机。其次我们不需要枚举第二个球场与第一个球场所发射的无人机会相撞因为三个球场会构成一个三角形，而因为任意两边之和大于第三边，所以最后只需要从第三个球场开始枚举就可以了。\
这里给出三维欧几里得公式：$\sqrt{(x_a-x_b)^2+(y_a-y_b)^2+(z_a-z_b)^2}$。\
最后因为是相遇所以最后需要除以 $2$。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5010;
double ans=1e18,x[maxn],y[maxn],z[maxn];
int n;
double f(int s1,int s2) 
{
	return (double)sqrt((x[s1]-x[s2])*(x[s1]-x[s2])+(y[s1]-y[s2])*(y[s1]-y[s2])+(z[s1]-z[s2])*(z[s1]-z[s2]));
}
int main() 
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%lf%lf%lf",&x[i],&y[i],&z[i]);
	for(int i=3;i<=n;++i) 
		for(int j=2;j<i;++j) 
			ans=min(ans,f(i,j)+f(1,i)+f(1,j));
	printf("%.6lf",ans/2);
	return 0;
}
```

---

## 作者：mnlbnkk (赞：0)

# 题意
首先一号星球给每个星球都发出一个超级飞船，然后每个接收到了超级飞船的星球又向不是发出超级飞船的星球发出超级飞船，求最短的撞击事件，这可能难理解。
# 做法
首先第一轮和第二轮的不会相撞这是显然的，因为三角形不等式，即两边之和大于第三边，所以 $1$ 到 $x$，和 $1$ 到 $y$ 到 $x$ 的飞船是不可能相撞的，但是由于从 $1$ 到 $x$ 到 $y$ 的飞船是必然和 $1$ 到 $y$ 到 $x$ 的飞船相撞的，因为不存在其中一艘飞船已经到了，但另一艘还没到的情况，再加上两个飞船的飞行路径一样，自然必然相撞，为了求撞击的最短时间，去最短值就可以了，但注意需要除二。
# 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=5009;
struct node
{
	double x,y,z;
}a[N];
double n,minn=LONG_LONG_MAX;
inline double cd(node a,node b)
{
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z));
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i].x>>a[i].y>>a[i].z;
	for(int i=2;i<=n;i++)
		for(int j=2;j<=n;j++)
			if(i!=j)
				minn=min(minn,cd(a[1],a[i])+cd(a[i],a[j])+cd(a[j],a[1]));
	printf("%.10lf",minn/2);
}
```

---

## 作者：furina_yyds (赞：0)

## 题意简述
给定 $n$ 个三维直角坐标系的坐标 $x,y,z$，一开始，从 $1$ 点发射 $n-1$ 艘飞船，当到达另一颗星球之后再发出 $n-2$ 艘飞船，以此类推。
## 思路
$1$ 号行星射出飞船不会撞（题目中说的），第二波飞船不可能和第一波飞船相撞．但是第二波飞船与之后发出的飞船就会相撞了，所以枚举每两个发出第二波火箭的星球就好了。

浅算一波时间复杂度 $O(n^2)$，完全可以。

**注：本题需用[三维欧几里得距离公式](https://baike.baidu.com/item/%E6%AC%A7%E5%87%A0%E9%87%8C%E5%BE%97%E5%BA%A6%E9%87%8F/1274107?fr=ge_ala)计算距离。**

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
struct xyz {
    double x, y, z;
}a[5005];
double ans = INF;
double len(xyz a, xyz b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}
int n;
int main(){
    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> a[i].x >> a[i].y >> a[i].z;
    }
    for (int i = 2; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            ans = min(Min, len(a[1], a[i]) + len(a[1], a[j]) + len(a[i], a[j]));
        }
    }
    printf("%.10lf", ans / 2);
    return 0;
}
```

---

## 作者：YangXiaopei (赞：0)

## Solution:

显然，第一轮发出的飞船互相不会相撞。

第二轮发出的飞船不会与第一轮相撞。

假如 $a$ 号飞船是在第二轮中从 $x$ 号星球飞往 $y$ 号星球的飞船，$b$ 号飞船是在第一轮中从 $1$ 号星球飞往 $y$ 号星球的飞船。

飞船速度一样，题目又保证三个星球不共线，所以 $a$ 号飞船一定比 $b$ 号飞船晚到达 $y$ 星球，所以第二轮发出的飞船不会与第一轮相撞。

那第二轮发出的飞船就可能互相相撞了。

假如 $c$ 号飞船是在第二轮中从 $p$ 号星球飞往 $q$ 号星球的飞船，$d$ 号飞船是在第二轮中从 $q$ 号星球飞往 $p$ 号星球的飞船。

那这两艘飞船就会相撞，共走了一个三角形的距离，速度为 $1$，时间除二即可。

那只需双重循环遍历找答案即可，注意，三维空间中欧几里得距离为 $\sqrt{(x_2 - x_1) ^ 2 + (y_2 - y_1) ^ 2 + (z_2 -z_1) ^ 2}$。

## Code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, a[100005][4];
double get(int x1, int y1, int z1, int x2, int y2, int z2){
	return (double)(sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) + (z2 - z1) * (z2 - z1)));
}
double minn = 1e9;
signed main(){
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> a[i][1] >> a[i][2] >> a[i][3]; 
	}
	for(int i = 2; i <= n; i++){
		for(int j = i + 1; j <= n; j++){
			double x = get(a[i][1], a[i][2], a[i][3], a[j][1], a[j][2], a[j][3]);
			x += get(a[i][1], a[i][2], a[i][3], a[1][1], a[1][2], a[1][3]);
			x += get(a[1][1], a[1][2], a[1][3], a[j][1], a[j][2], a[j][3]);
			minn = min(minn, x);
		} 
	}
	printf("%.6lf", minn / 2);
	return 0;
}
``

---

## 作者：Scean_Tong (赞：0)

# CF44D Hyperdrive

## 题意 

在 $1$ 号行星发出 $n-1$ 个飞船，然后到达另一个行星后再发出 $n-2$  个，$\dots$，求出某两个飞船碰撞的最早时间。

## 大体思路

首先，两点间距离公式为 $d=\sqrt{(x_a-x_b)^2+(y_a-y_b)^2}$，但这是二维空间的。

所以可以推导出三维空间的两点间距离公式：

$d=\sqrt{(x_a-x_b)^2+(y_a-y_b)^2+(z_a-z_b)^2}$。

第一次发射飞船时一定不会发生碰撞，第二次发射的飞船一定会发生碰撞。题目保证三点不共线，三角形的两边之和一定大于第三边。当飞船由 $1$ 号星球前往 $2,3$ 号星球时，一定会相遇。但又无法与到 $4,5$ 的飞船相遇，故我们只需要寻找以 $1,x,y$ 三点所构成的三角形周长的最小值再除以 $2$ 即可，因为求相遇时间。

数据范围 $3 \le n \le 5000$。直接暴力枚举，时间复杂度 $\mathcal{O}(n^2)$。

##  AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
double ans=1e18,x[5005],y[5005],z[5005];
double cal(int s1,int s2) {//三维空间内两点的距离公式
	return (double)sqrt((x[s1]-x[s2])*(x[s1]-x[s2])+(y[s1]-y[s2])*(y[s1]-y[s2])+(z[s1]-z[s2])*(z[s1]-z[s2]));
}
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i){ 
		scanf("%lf %lf %lf",&x[i],&y[i],&z[i]);
	}
	for(int i=3;i<=n;++i) {//1行星发射的飞船不可能发生碰撞，所以不用枚举1行星和重复的行星
		for(int j=2;j<i;++j) {
			ans=min(ans,cal(i,j)+cal(1,i)+cal(1,j));//求出第一艘飞船发射的那一刻起银河系将继续存在的时间
		}
	}
	printf("%.6lf",ans/2);//精确到10e-6：保留小数点后6位
	return 0;
}
```

---

## 作者：nxd_oxm (赞：0)

~~水社贡ing~~
# 思路
其实只要你多想想就做出来了。

我们知道， $1$ 号星球会给 $2$ ~ $n-1$ 号星球传输飞船，而他们收到之后，又给其他星球发射。

首先，由 $1$ 号星球发射的飞船是不会撞得（三点不同线）,但后来发射的就会撞了。

比如 $1$ 给 $i$ 和 $j$ 是发射了飞船的， $i$ 和 $j$ 又会互相发射，就撞啦。

因为飞船是一个单位时间走一个单位距离，所以他们相撞的时间就是 $1,i,j$ 三点构成三角形的周长的一半。

$O(n^2)$ 枚举即可。
## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct abc{
    int x,y,z;
}mp[5001];
double minn=INT_MAX/2;
//三维两点距离公式
double lenth(int i,int j){
    return sqrt((mp[i].x-mp[j].x)*(mp[i].x-mp[j].x)+(mp[i].y-mp[j].y)*(mp[i].y-mp[j].y)+(mp[i].z-mp[j].z)*(mp[i].z-mp[j].z));
} 
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
        cin>>mp[i].x>>mp[i].y>>mp[i].z;
    }
	for(int i=2;i<=n;i++){
        for(int j=2;j<i;j++){
            //计算由1,i,j三点构成的三角形周长
	        minn=min(minn,lenth(1,i)+lenth(1,j)+lenth(i,j));
        }
    }
    cout<<fixed<<setprecision(10)<<minn/2.0;
}

```

---

## 作者：dengqingrui123 (赞：0)

[题目传送门]（https://www.luogu.com.cn/problem/CF44D)

# Step 0 三维空间两点距离

距离 $c$ = $\sqrt{(x_a - x_b)^2 + (y_a - y_b)^2 + (y_a - y_b)^2}$

代码实现：

```cpp
double d(int a,int b) { return (double)sqrt((x[a] - x[b]) * (x[a] - x[b]) + (y[a] -y [b]) * (y[a] - y[b]) + (z[a] - z[b]) * (z[a] - z[b]));}
```


# Stpe 1 解题思路

1. 第一次发射消息时必定不会撞击；
2. 第二次发射消息时**一定**会相撞；

![](https://cdn.luogu.com.cn/upload/image_hosting/ob3l4c1o.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

3. 由图可以发现答案就是除了第一个星球外的其他两颗星球与第一颗星球组成的三角形（三角体？）$\div 2$ 的最小值；
4. 考虑到 $3 \le n \le 5000$ 可以直接 $O(n^2)$ 暴力枚举；

# Step 2 AC code

```cpp
#include <bits/stdc++.h>
long long n;

double ans = 9999999,x[5005],y[5005],z[5005];

double Min(double a,double b) {return a<b?a:b;}

double d(int a,int b) { return (double)sqrt((x[a] - x[b]) * (x[a] - x[b]) + (y[a] -y [b]) * (y[a] - y[b]) + (z[a] - z[b]) * (z[a] - z[b]));}

double juli(int s1, int s2){return d(s1,s2) + d(1,s1) + d(1,s2);}

int main() {
	scanf("%lld",&n);
	for(int i = 1; i <= n; i++) scanf("%lf %lf %lf",&x[i],&y[i],&z[i]);
	for(int i = 3; i <= n; i++) 
		for(int j = 2; j < i; j++) 
			ans=Min(ans,juli(i,j));
	printf("%.6lf",ans/2);
	return 0;
}
```


---

