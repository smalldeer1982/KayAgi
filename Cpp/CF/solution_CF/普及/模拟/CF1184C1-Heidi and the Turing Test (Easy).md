# Heidi and the Turing Test (Easy)

## 题目描述

The Cybermen and the Daleks have long been the Doctor's main enemies. Everyone knows that both these species enjoy destroying everything they encounter. However, a little-known fact about them is that they both also love taking Turing tests!

Heidi designed a series of increasingly difficult tasks for them to spend their time on, which would allow the Doctor enough time to save innocent lives!

The funny part is that these tasks would be very easy for a human to solve.

The first task is as follows. There are some points on the plane. All but one of them are on the boundary of an axis-aligned square (its sides are parallel to the axes). Identify that point.

## 说明/提示

In both examples, the square has four sides $ x=0 $ , $ x=2 $ , $ y=0 $ , $ y=2 $ .

## 样例 #1

### 输入

```
2
0 0
0 1
0 2
1 0
1 1
1 2
2 0
2 1
2 2
```

### 输出

```
1 1
```

## 样例 #2

### 输入

```
2
0 0
0 1
0 2
0 3
1 0
1 2
2 0
2 1
2 2
```

### 输出

```
0 3
```

# 题解

## 作者：Bai_R_X (赞：40)

## 思路
我们首先需要求出 $4$ 条边。但是如果用普通的算法来算了话，如果特殊的点在正方形外，就会错误。

于是乎我们观察题面，可以得知每条边至少有 $n$ 个点（英文原版有，洛谷翻译没有）。

其实我们也用不到这个特殊性质，因为正方形有 $4$ 个顶点，这样每条边上就至少有 $2$ 个点，而特殊点的边上（如果不与其它边重叠，重叠了话我们可以省略，已经找到边了）只有 $1$ 个点。

所以我们可以用一个桶来记录边上有多少个点，然后枚举边，如果边上点数大于 $1$ 了话，那这条边就是正方形的一条边。

最后再枚举每个点是否在边上。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,x[45],y[45],minx=INT_MAX,maxx=INT_MIN,miny=INT_MAX,maxy=INT_MIN,i,j,hx[55],hy[55];
signed main()
{
	cin>>n;
	for(i=1;i<=4*n+1;i++)
	{
		cin>>x[i]>>y[i];
		hx[x[i]]++;
		hy[y[i]]++;
	}
	for(i=0;i<=50;i++)
	{
		if(hx[i]>1)
		{
			minx=min(minx,i);
			maxx=max(maxx,i);
		}
	}
	for(i=0;i<=50;i++)
	{
		if(hy[i]>1)
		{
			miny=min(miny,i);
			maxy=max(maxy,i);
		}
	}
	for(i=1;i<=4*n+1;i++)
	{
		if((x[i]<minx||x[i]>maxx)||(y[i]<miny||y[i]>maxy||(y[i]>miny&&y[i]<maxy&&(x[i]>minx&&x[i]<maxx))))
		{
			cout<<x[i]<<" "<<y[i];
			break;
		}
	}
	return 0;
}
```

---

## 作者：MGR_P (赞：4)

步入正题：

看完题目后就迎来了一个问题：

如何判断正方形呢？

但是如果我们用朴素的算法判断的话就会判断出错,所以我们该如何判断呢？让我们先看代码：

```cpp
int n = n * 4 + 1;
for (int i = 1; i <= n; i++) {
	for (int j = 1; j <= n; j++) {
		if (i == j) continue;
		if (x[j] > maxx) maxx = x[j];
		if (y[j] > maxy) maxy = y[j];
		if (x[j] < minx) minx = x[j];
		if (y[j] < miny) miny = y[j];
	}
	if (maxx - minx != maxy - miny) continue;
}
```

首先 枚举每一个点取最大的和最小的 x 与 y 坐标,那么为什么要加上

```cpp
if (i == j) continue;
```

呢？

因为在 $ n \times 4 + 1 $ 个点中有一个不属于最大的正方形中，这个点要么在最大的正方形中要么在正方形外，在正方形中还好说，但是在正方形外呢？所以用点 i 来枚举出是哪一个点在最大的正方形外或者在最大的正方形的内部。

```cpp
if (maxx - minx != maxy - miny) continue;
```

这里则是为了判断最大的 x 与 最小的 x 的距离等不等于最大的 y 与 最小的 y 的距离。（其实就是判断是不是正方形看点 i 到底是不是在最大的正方形外或者在最大的正方形的内部因为如果枚举错了是不会形成正方形的）

然后就是判断点 i 到底是不是在最大的正方形的边界外，我们先看代码：

```cpp
bool JJ = false;
for (int j = 1; j <= n; j++) {
	if (i == j) continue;
	if (x[j] == minx || x[j] == maxx || y[j] == miny || y[j] == maxy) continue;
	JJ = true;
}
```

首先这里的：

```cpp
if (i == j) continue;
```

其实是和上文的：

```cpp
if (i == j) continue;
```

作用是一模一样的,这里我就跳过了。
上面的代码中的判断是否在最大的正方形的边界上，如果成立的话就就跳过，判断下一个点是否在最大的正方形的边界上，如果不在则 JJ == true . 那么这意味着什么呢？如果 JJ == true 就意味着点 i 没有在最大的正方形的边界上。最后让我们把以上代码组合起来组成 AC 代码：

```cpp
#include <bits/stdc++.h>
#define N 100
#define MAXN 10000000
#define MINN -1
using namespace std;
int n, x[N], y[N];
int main() {
	ios::sync_with_stdio(false);
	cin.tie();
	cout.tie();
	cin >> n;
	n = n * 4 + 1;
	for (int i = 1; i <= n; i++) cin >> x[i] >> y[i];
	for (int i = 1; i <= n; i++) {
		bool JJ = 0;
		int maxx = MINN, maxy = MINN, miny = MAXN, minx = MAXN;
		for (int j = 1; j <= n; j++) {
			if (i == j) continue;
			if (x[j] > maxx) maxx = x[j];
			if (y[j] > maxy) maxy = y[j];
			if (x[j] < minx) minx = x[j];
			if (y[j] < miny) miny = y[j];
		}
		if (maxx - minx != maxy - miny) continue;
		for (int j = 1; j <= n; j++) {
			if (i == j) continue;
			if (x[j] == minx || x[j] == maxx || y[j] == miny || y[j] == maxy) continue;
			JJ = 1;
		}
		if (!JJ) {
			cout << x[i] << " " << y[i];
			return 0;
		}
	}
	return 0;
}
```

以上就是本篇题解的所有内容，再此完结撒花 ! ! ! ✧*｡٩(ˊᗜˋ*)و✧* 。

---

## 作者：wenqinghua1001 (赞：2)

# 一道简单的题

[题目传送门](https://www.luogu.com.cn/problem/CF1184C1)

[样例解释](https://www.luogu.com.cn/paste/eqk8l26l)

这道题分为**构造**和**判断**两部分。

## 思路：

1. 输入 $n$ ，将 $n=n \times 4+1$ 。再输入第i个点的坐标。
2. 暴力枚举答案是哪一个点。
3. 如果是第 $i$ 个点，求出其他点组成的最大正方形。
4. 如果除了正方形上的点，还有超过 $1$ 个点，那么不是这个点。
5. 如果除了正方形上的点，只有 $1$ 个点，那么答案就是这个点。

## 操作：

首先，头文件+定义。


```cpp
#include<bits/stdc++.h> // 万能头。
#define int long long // 可加可不加。
using namespace std;
int x[1005],y[1005],n;
```

接着，读入。


```cpp
int main(){
    cin>>n;
    n=4*n+1;
    for(int i=1;i<=n;i++)
        cin>>x[i]>>y[i];
```

然后判断。


```cpp

    for(int i=1;i<=n;i++){
        if(check(i)==true){
            cout<<x[i]<<" "<<y[i];
            return 0;
        }
    }
    return 0;
}
```

最后写用来判断的函数。


```cpp
bool check(int q){
	int by=INT_MAX;
	int ty=INT_MIN;
	int lx=INT_MAX;
	int rx=INT_MIN;
	for(int i=1;i<=n;i++){
		if(i==q) continue;
		else{
			by=min(by,y[i]);
			ty=max(ty,y[i]);
			lx=min(lx,x[i]);
			rx=max(rx,x[i]);
		}
	}
	for(int i=1;i<=n;i++){
		if(i==q) continue;
		else{
			if(x[i]!=lx&&x[i]!=rx&&y[i]!=by&&y[i]!=ty){
				return false;
			}
		}
	}
	if(ty-by==rx-lx) return true;
	else return false;
}
```

AC code


```cpp
#include<bits/stdc++.h> //万能头。 
#define int long long //可加可不加。 
using namespace std;
int x[1005],y[1005],n;
// 定义 。 
bool check(int q){ // 判断函数 。 
	int youshang=INT_MAX; // 右上 。 
	int zuoshang=INT_MIN; // 左上 。 
	int youxia=INT_MAX; // 右下 。 
	int zuoxia=INT_MIN; // 左下 。 
	for(int i=1;i<=n;i++){
		if(i==q) continue; 
		else{
			// 如果此点不是判断的点 。 
			youshang=min(youshang,y[i]);
			zuoshang=max(zuoshang,y[i]);
			youxia=min(youxia,x[i]);
			zuoxia=max(zuoxia,x[i]);
			// 构造一个最大的正方形 。 
		}
	}
	for(int i=1;i<=n;i++){
		if(i==q) continue;
		else{
			// 如果此点不是判断的点 。 
			if(x[i]!=youxia&&x[i]!=zuoxia&&y[i]!=youshang&&y[i]!=zuoshang){
                // 如果除了正方形上的点，还有超过1个点，那么不是这个点。
				return false;
			}
		}
	}
	if(zuoshang-youshang==zuoxia-youxia) return true; // 如果是正方形 。 
	else return false; // 如果不是正方形。 
}
signed main(){
    cin>>n;
    n=4*n+1;
    for(int i=1;i<=n;i++)
        cin>>x[i]>>y[i]; //第i个点的坐标 。 
    for(int i=1;i<=n;i++){ //枚举 。 
		if(check(i)==true){ // 如果找到了 。 
			cout<<x[i]<<" "<<y[i]; // 输出 。 
			return 0; // 结束 。 
		}
	}
	return 0; // 好习惯+1 。 
}
```

> 题解千万条，理解第一条。
直接抄题解，棕名两行泪。

谢谢大家！

---

## 作者：WydnksqhbD (赞：1)

# [CF1184C1 Heidi and the Turing Test (Easy)](https://www.luogu.com.cn/problem/CF1184C1) 题解
## 思路
首先正常读入。

接下来枚举 $1$ 到 $n$，设枚举到了 $i\in[1,n]$。

那么我们需要判断剩下的几个点可不可以构成正方形。
+ 首先求 $\text{maxx},\text{maxy},\text{minx},\text{miny}$，即 $x,y$ 坐标的最大值与最小值。
+ 判断：当 $\text{maxx}-\text{minx}\ne\text{maxy}-\text{miny}$ 时，明显无法构成正方形。直接 `continue;`。
+ 否则继续枚举 $1$ 到 $n$，设枚举到了 $j\in[1,n]$。
+ 若 $i\ne j$ 且 $x_j\ne\text{maxx},x_j\ne\text{minx},y_j\ne\text{maxy},y_j\ne\text{miny}$，则这也不是一个正方形。
+ 如果还能撑下来，那肯定就是一个正方形了。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5,inf=2147483647;
int x[N],y[N];
signed main()
{
	int n;scanf("%lld",&n);n=n*4+1;
	for(int i=1;i<=n;i++)scanf("%lld%lld",&x[i],&y[i]);
	for(int i=1;i<=n;i++)
	{
		int flag=1,maxx=-inf,maxy=-inf,minx=inf,miny=inf;
		for(int j=1;j<=n;j++)if(i!=j)maxx=max(maxx,x[j]),maxy=max(maxy,y[j]),minx=min(minx,x[j]),miny=min(miny,y[j]);
		if(maxx-minx!=maxy-miny)continue;
		for(int j=1;j<=n;j++)if(i!=j&&x[j]!=maxx&&x[j]!=minx&&y[j]!=maxy&&y[j]!=miny){flag=0;break;}
		if(flag){printf("%lld %lld\n",x[i],y[i]);return 0;}
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

题意：给你一个平面直角坐标系，和其中一些点（共有 $4n+1$ 个）的坐标，你知道其中一定有一个正方形，并且这个正方形旁还有一个多余的点，现在请你把那个点找出来（注：每条边上的点不少于
$n$
个）

这一道题实实在在是一个坑，第一眼看到这个题的时候，第一反应就是找行和列上点的数量，大于等于 $n$
的就定为一条边，然而，种种特判让我防不胜防，无奈之下，放弃了这个想法。
这一种方法不行，那暴力总可以吧，数据范围这么小，我们可以枚举删除的点，再暴力判断，就可以了。
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
#define Maxn 41
struct Node{
	int x,y;
	friend bool operator <(Node p,Node q){
		if(p.x==q.x){
			return p.y<q.y;
		}
		return p.x<q.x;
	}
}a[Maxn+5];
int mn(int a,int b){
	return a<b?a:b;
}
int mx(int a,int b){
	return a>b?a:b;
}
void swp(int &a,int &b){
	int t=a;
	a=b;
	b=t;
}
int n,m;
bool cmp(Node p,Node q){
	if(p.y==q.y){
		return p.x<q.x;
	}
	return p.y<q.y;
}
int x[Maxn+5],y[Maxn+5];
bool check(){
	int mn_x=55,mn_y=55,mx_x=-1,mx_y=-1;
	for(int i=1;i<m;i++){
		mn_x=mn(mn_x,x[i]);
		mn_y=mn(mn_y,y[i]);
		mx_x=mx(mx_x,x[i]);
		mx_y=mx(mx_y,y[i]);
	}
	if(mx_x-mn_x!=mx_y-mn_y){
		return 0;
	}
	for(int i=1;i<m;i++){
		if(x[i]!=mn_x&&x[i]!=mx_x&&y[i]!=mn_y&&y[i]!=mx_y){
			return 0;
		}
	}
	return 1;
}
int main(){
	scanf("%d",&n);
	m=(n<<2)+1;
	for(int i=1;i<=(n<<2)+1;i++){
		scanf("%d%d",&a[i].x,&a[i].y);
	}
	sort(a+1,a+1+(n<<2)+1);
	for(int i=1;i<=m;i++){
		for(int j=1;j<=m;j++){
			if(i==j){
				continue;
			}
			if(j>i){
				x[j-1]=a[j].x;
				y[j-1]=a[j].y;
			}
			else{
				x[j]=a[j].x;
				y[j]=a[j].y;
			}
		}
		if(check()){
			printf("%d %d\n",a[i].x,a[i].y);
			break;
		}
	}
	return 0;
}
```


---

## 作者：enyyyyyyy (赞：1)

- 算法：
	模拟
    
- 思路：
	把输入进来的排序，在排好序的坐标中稍微枚举一下，发现 $2$ 和 $4\times  n$ 的下表为正方形左上角与右下角的坐标。再判断一下如果这个点刚好在左上角与右下角的坐标间，便不为正方形的边界上的点；如果这个点刚好在左上角与右下角的坐标外，便不为正方形的边界上的点。遇到这两种情况，直接输出即可。

- 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lint;
typedef double db;
typedef void vd;
typedef bool bl;
inline ll read() {
	ll s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
			w = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
	return s * w;
}
inline vd print(ll x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x >= 10)
		print(x / 10);
	putchar(x % 10 + '0');
	return;
}
ll x[10005],y[10005],a[10005],b[10005],n,x2,X,y2,Y;
int main(){
	n=read();
	n=4*n+1;
	for(int i=1;i<=n;i++)
        x[i]=read(),y[i]=read(),a[i]=x[i],b[i]=y[i];
    sort(1+a,1+a+n);
    sort(1+b,1+b+n);
    x2=a[2];
    X=a[n-1];
    y2=b[2];
    Y=b[n-1];
	for(int i=1;i<=n;i++)
        if((x[i]>x2&&x[i]<X&&y[i]>y2&&y[i]<Y)||(x[i]<x2||x[i]>X||y[i]<y2||y[i]>Y)){
        	print(x[i]),printf(" "),print(y[i]);
        	return 0;
    	}	
    return 0;
}
```


---

## 作者：xukuan (赞：1)

翻译请见：[https://www.luogu.org/blog/xukuan/translate-cf1184c1](https://www.luogu.org/blog/xukuan/translate-cf1184c1)

这题做法很简单，就是枚举当前点是不是独立的，然后判断剩下的是不是在一个**正方形**上

代码：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
#define INF 2147483647
using namespace std;

ll n,x[60],y[60];

inline ll read(){
	ll x=0,tmp=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') tmp=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return tmp*x;
}

int main(){
	n=read(); n=4*n+1;
	for(ll i=1; i<=n; i++){
		x[i]=read(); y[i]=read();
	}
	for(ll i=1; i<=n; i++){
		ll Minx=INF,Miny=INF,Maxx=0,Maxy=0;
		bool bo=0;
		for(ll j=1; j<=n; j++){
			if(i==j) continue;
			Minx=min(Minx,x[j]);
			Miny=min(Miny,y[j]);
			Maxx=max(Maxx,x[j]);
			Maxy=max(Maxy,y[j]);
		}
		if(Maxx-Minx!=Maxy-Miny) continue;
		for(ll j=1; j<=n; j++){
			if(i==j) continue;
			if(x[j]>=Minx&&x[j]<=Maxx&&y[j]>=Miny&&y[j]<=Maxy){
				if(x[j]==Minx||x[j]==Maxx||y[j]==Miny||y[j]==Maxy) continue;
			}
			bo=1;
		}
		if(!bo) return printf("%I64d %I64d\n",x[i],y[i])&0;
	}
	cout<<"WTF???"<<endl;
	return 0;
}
```

---

## 作者：wyc0607 (赞：0)

### 思路：

`It is guaranteed that there are at least n points on each side of the square and all 4n+1 points are distinct.`

由这句话可见共 $4 \times n + 1$ 个点，一条边上有至少 $n$ 个点。

令 $mnx,mny$ 分别为正方形的左下顶点的坐标，$mxx,mxy$ 分别为正方形的右上顶点的坐标

于是我们可以开两个桶，记录 $x$ 坐标和 $y$ 坐标出现的次数。当一个 $x$ 或 $y$ 坐标出现过 $\geq 2$ 次，就证明这可能是一条边，更新 $mnx,mny,mxx,mxy$ 。

接着，循环枚举所有的点，令循环到的这个点的坐标为 $x1,y1$ 。

- 当 $x1 < mnx $ , $x1>mxx$ , $y1<mny$ , $y1>mxy$ 即该点在正方形外时，输出坐标，退出。
- 当 $x1 > mnx $ , $x1<mxx$ , $y1>mny$ , $y1<mxy$ 即该点在正方形内时，输出坐标，退出。

### [AC记录](https://codeforces.com/problemset/submission/1184/301378526)

---

## 作者：Jerrycyx (赞：0)

CodeForces 上 [AC](https://codeforces.com/contest/1184/submission/275246046) 了但是洛谷上[一直 UKE](https://www.luogu.com.cn/record/list?pid=CF1184C1&user=545986&page=1)，我也不知道为什么，但我还是来写题解了。

## 思路

题目要求我们找出唯一不在正方形边上的点，很容易想到枚举每一个点，如果剔除这个点后剩下所有点都在正方形边上，那么这个点就是额外的那个点。

怎么检查所有点是否在同一个正方形的边上呢？我们可以记录所有点（除了被剔除的那一个）的最大 $x$ 坐标 $\max x$，最小 $x$ 坐标 $\min x$，最大 $y$ 坐标 $\max y$，最小 $y$ 坐标 $\min y$，正方形的上下边即为 $\max x$ 和 $\min x$，左右边为 $\min y$ 和 $\max y$。

如果 $\max x-\min x ≠ \max y-\min y$，那么这个图形就不是一个正方形，直接输出 `false`。

给所有的点（除被剔除的点）在坐标系上打上标记，计算在正方形边上的点的数量（即 $x=\max x$ 或 $x=\min x$ 或 $y=\max y$ 或 $y=\min y$ 的点的数量），如果其数量不等于 $4n$，则代表不是所有点都在正方形边上，判断不通过。

如果以上检测都通过，那么这个被剔除的点就是多余的点，直接输出。

## AC 代码

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int N=55,INF=0x3f3f3f3f;
int n,cnt[N];
pair<int,int> a[N];

bool flag[N][N];
bool check(int no)
{
	memset(flag,false,sizeof(flag));
	int \min x=INF,\max x=0,\min y=INF,\max y=0;
	for(int i=1;i<=n;i++)
	{
		if(i==no) continue;
		flag[a[i].first][a[i].second]=true;
		\min x=min(\min x,a[i].first),\max x=max(\max x,a[i].first);
		\min y=min(\min y,a[i].second),\max y=max(\max y,a[i].second);
	}
	if(\max x-\min x!=\max y-\min y) return false;
	int cnt=0;
	for(int i=\min x;i<=\max x;i++)
	{
		if(flag[i][\min y]) cnt++;
		if(flag[i][\max y]) cnt++;
	}
	for(int i=\min y+1;i<=\max y-1;i++)
	{
		if(flag[\min x][i]) cnt++;
		if(flag[\max x][i]) cnt++;
	}
	return cnt==n-1;
}

int main()
{
	scanf("%d",&n); n=n*4+1;
	for(int i=1;i<=n;i++)
		scanf("%d%d",&a[i].first,&a[i].second);
	for(int i=1;i<=n;i++)
		if(check(i)) printf("%d %d\n",a[i].first,a[i].second);
	return 0;
}
//CF don't ban me!
```

---

## 作者：66xyyd (赞：0)

## 题意

给定 $4n+1$ 个点的位置，其中 $4n$ 个点均在某一边与坐标轴平行的正方形的边界上，求剩下的 $1$ 个点的坐标。（其实翻译说的挺清楚的）

## 题解

在了解完题意后，我们先来看看我们的判断依据。

如果有一个正方形，四条边都与坐标轴平行，那么正方形的左下点的 $x$ 坐标是所有边上点中 $x$ 坐标最小的那个，$y$ 坐标是所有边上点中 $y$ 坐标最小的那个；右上点的 $x$ 坐标是所有边上点中 $x$ 坐标最大的那个，$y$ 坐标是所有边上点中 $y$ 坐标最大的那个。记左下点为 $min_x,min_y$，右上点为 $max_x,max_y$。

（图片挂了）

同时我们还发现，正方形的左下点 $(min_x,min_y)$ 与右上点 $(max_x,max_y)$ 的 $x$ 坐标之差和 $y$ 坐标之差相等，都是正方形的边长；所有正方形上的点 $x,y$ 中 $x$ 坐标要么是 $min_x$，要么是 $max_x$，$y$ 坐标要么是 $min_y$，要么是 $max_y$。

看到这，判断一个点集是否为某一正方形的边界（以下默认正方形的各个边平行于坐标轴）的方法其实已经出现了。首先统计点集中的四个极值 $max_x,max_y,min_x,min_y$。我们知道正方形的边长是固定的，$max_x-min_x$ 与 $max_y-min_y$ 相等。如果不是，该点集就不是任何正方形的边界。否则我们比较点集中所有点，如果有一点 $x$ 坐标或 $y$ 坐标不为极值，也不是任何正方形的边界。

接下来我们只用枚举是哪个点 $i$ 不属于正方形的边界，在循环到这个点时跳过即可。如果去掉 $i$ 之后剩下的所有点都属于正方形的边界，那么 $i$ 就是我们要找的，直接输出坐标即可。

```cpp
#include<iostream>
using namespace std;
pair<int,int> a[101];//first表示x坐标，second表示y坐标
int n;
int main(){
	cin >> n;
	n=n*4+1;//实际有4n+1点，别被坑了
	for(int i=1;i<=n;i++){
		cin >> a[i].first >> a[i].second;
	}
	for(int i=1;i<=n;i++){
		bool flag=true;//用来记录当前点集是否可构成正方形边界
		int maxx=-1,maxy=-1,minx=2147483647,miny=2147483647;
		for(int j=1;j<=n;j++){//计算四个极值（x,y极大&极小）
			if(i==j){
				continue;
			}
			maxx=max(maxx,a[j].first);
			maxy=max(maxy,a[j].second);
			minx=min(minx,a[j].first);
			miny=min(miny,a[j].second);
		}
		if(maxx-minx!=maxy-miny)	continue;//说明该点集不是任何正方形的边界，跳过此i即可
		for(int j=1;j<=n;j++){
			if(i==j)	continue;
			if(!(a[j].first==maxx || a[j].second==maxy || a[j].first==minx || a[j].second==miny)){//j不是极值，记录
				flag=false;
			}
		}
		if(flag){//可构成，i不属于正方形的边
			cout << a[i].first << ' ' << a[i].second;
			return 0;
		}
	}
	cout << "Silly CF";//这句被输出意味着数据有问题
	return 0;
}
```


---

## 作者：wei2013 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1184C1)
## 思路：
从题目中我们可知这是一个正方形，正方形的四个边都是一样，所以我们只需要在保证此时的这个是正方形，然后扫一遍，看此时的这个点是否在正方形边界上，若是不在，既是不合法，中断掉输出即可。至于怎么判断边界就不用说了吧，就是去最大和最小嘛。
## code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int x[1000005],y[1000005];
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n*4+1;i++){
		cin>>x[i]>>y[i];
	}
	for(int i=1;i<=n*4+1;i++){
		int maxx=-100,maxy=-100,minx=100,miny=100;
		bool ok=1;
		for(int j=1;j<=n*4+1;j++){
			if(i!=j){
				maxx=max(maxx,x[j]);
				maxy=max(maxy,y[j]);
				minx=min(minx,x[j]);
				miny=min(miny,y[j]);
			}
		}
		if(maxx-minx==maxy-miny){
			for(int j=1;j<=n*4+1;j++){
				if(i!=j && x[j]!=maxx && x[j]!=minx && y[j]!=maxy && y[j]!=miny){
					ok=0;
					break;
				}
			}
			if(ok){
				cout<<x[i]<<" "<<y[i]<<endl;
				return 0;
			}
		}
	}
	return 0;
}
```

---

