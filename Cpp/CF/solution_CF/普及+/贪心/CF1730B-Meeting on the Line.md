# Meeting on the Line

## 题目描述

$ n $ people live on the coordinate line, the $ i $ -th one lives at the point $ x_i $ ( $ 1 \le i \le n $ ). They want to choose a position $ x_0 $ to meet. The $ i $ -th person will spend $ |x_i - x_0| $ minutes to get to the meeting place. Also, the $ i $ -th person needs $ t_i $ minutes to get dressed, so in total he or she needs $ t_i + |x_i - x_0| $ minutes.

Here $ |y| $ denotes the absolute value of $ y $ .

These people ask you to find a position $ x_0 $ that minimizes the time in which all $ n $ people can gather at the meeting place.

## 说明/提示

- In the $ 1 $ -st test case there is one person, so it is efficient to choose his or her position for the meeting place. Then he or she will get to it in $ 3 $ minutes, that he or she need to get dressed.
- In the $ 2 $ -nd test case there are $ 2 $ people who don't need time to get dressed. Each of them needs one minute to get to position $ 2 $ .
- In the $ 5 $ -th test case the $ 1 $ -st person needs $ 4 $ minutes to get to position $ 1 $ ( $ 4 $ minutes to get dressed and $ 0 $ minutes on the way); the $ 2 $ -nd person needs $ 2 $ minutes to get to position $ 1 $ ( $ 1 $ minute to get dressed and $ 1 $ minute on the way); the $ 3 $ -rd person needs $ 4 $ minutes to get to position $ 1 $ ( $ 2 $ minutes to get dressed and $ 2 $ minutes on the way).

## 样例 #1

### 输入

```
7
1
0
3
2
3 1
0 0
2
1 4
0 0
3
1 2 3
0 0 0
3
1 2 3
4 1 2
3
3 3 3
5 3 3
6
5 4 7 2 10 4
3 2 5 1 4 6```

### 输出

```
0
2
2.5
2
1
3
6```

# 题解

## 作者：abensyl (赞：15)

原题：[CF1730B Meeting on the Line](https://www.luogu.com.cn/problem/CF1730B)

## 思路

我的思路有些与众不同，是一个模拟+贪心。

我们先找出穿衣服时间最长的人，记录他的位置，我们知道，其他所有人穿衣服都比与他快，或者是一样快（废话）。

当这个人在穿衣服的时候，让其他所有人穿好衣服后向他所在的地方走，这样当他穿好的时候，大家都靠近他了。

而当他穿好衣服的时候，有可能还有人没有到达他的位置，于是，我们再次统计所有人的位置，如果现在位置最靠前的人在 $s_1$ 处，现在位置最靠后的人在 $s_2$ 处，则直接让所有人去 $s_1+s_2\over 2$ 处即可。

于是，我们计算出的答案为 $$\max\limits_{i=1}^{n}\{t_i\}+{s_1+s_2\over 2}$$

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+4;
int x[N];
int t[N];
void solve() {
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",x+i);
	int goal=0;
	int up=-1;
	for(int i=1;i<=n;++i) {
		scanf("%d",t+i);
		if(t[i]>up) up=t[i],goal=x[i];
	}
	int ne=goal,fa=goal;
	for(int i=1;i<=n;++i) {
		if(x[i]<goal) x[i]=min(x[i]+(up-t[i]),goal);
		else if(x[i]>goal) x[i]=max(x[i]-(up-t[i]),goal);
		if(x[i]>fa) fa=x[i];
		else if(x[i]<ne) ne=x[i];
	}
	printf("%lf\n",(fa+ne)/2.);
}
int main() {
  int T;
	scanf("%d",&T);
  while(T--) solve();
  return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/90112384)


---

## 作者：隐仞Mrsu (赞：13)

~~首先，这是个能用三种或以上的方法写出来，但却让我T了十发的好题~~

# 浅浅理解一下题意

设第 $i$ 个人到达 $x_0$ 的时间为 $T_i$，由题可知：
$T_i=t_i+\vert x_i-x_0 \vert$。

要求出一个最优解 $x_0$，使得 $\max\{T_1,T_2,\dots,T_n\}$ 最小。


**遇见了 “ 最大值最小 ” 这种字眼，基本可以考虑分治了。**

~~然鹅，我写了一个**三分算法**，然后愉快地超时了~~

# 浅浅分析一下思路


## 贪心

### 引理
$\vert a-b \vert = \max\{a-b,b-a\}$

由绝对值的性质可以易证。

### 复杂问题简单化

如果每个人都不用穿衣服，即穿衣服的时间 $t_i=0$ ，那么每个人的到达时间就是 $T_i=\vert x_i-x_0 \vert$ 了，也就是该人所在坐标到 $x_0$ 的距离。此时有 $\max\limits_{i=1}^n\{\vert x_i-x_0 \vert\}$。

于是乎，最优解的 $x_0$ 就是最左边的坐标和最右边的坐标的中点，这样就能保证最远距离的最小化啦~

### 深入の推导
现在我们考虑 $t_i\neq 0$。

题目要我们求出 $\max\{T_1,T_2,\dots,T_n\}$ 最小时，对应的 $x_0$。那么不妨展开上式，得到 $\max\limits_{i=1}^n\{t_i+\vert x_i-x_0 \vert\}$。

由引理可把每一项拆成两项，有 $\max\limits_{i=1}^n\{t_i+x_i-x_0,t_i+x_0-x_i\}$。

稍微移一下项，有 $\max\limits_{i=1}^n\{(x_i+t_i)-x_0,x_0-(x_i-t_i)\}$。

通过观察我们发现，如果我们抛弃掉原来的 $x_i$ 的点，新建两个点，坐标分别为 $x_i+t_i$ 和 $x_i-t_i$，那么问题就转换为上文的简单情况了。

由于是 $(x_i+t_i)-x_0$，则新点 $x_i+t_i$ 是在 $x_0$ 右边的；由于是 $x_0-(x_i-t_i)$，则新点 $x_i-t_i$ 是在 $x_0$ 左边的。

在上文的简单情况中，最左边的坐标和最右边的坐标的中点对应的 $x_0$ 就是答案。因此，只需要找出 $x_i+t_i$ 的最大值，以及 $x_i-t_i$ 的最小值，求两值的平均数，就是答案啦！

### 代码
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 500005;
const int inf = 0x3f3f3f3f;
LL _,n,a[N],t[N],mn,mx;
void work(){
	cin>>n;
	for(LL i=1;i<=n;i++){
		cin>>a[i];
	}
	for(LL i=1;i<=n;i++){
		cin>>t[i];
	}
	mx=-inf,mn=inf;
	for(LL i=1;i<=n;i++){
		mn=min(mn,a[i]-t[i]);
		mx=max(mx,a[i]+t[i]);
	}
	double res=(mn+mx)*1.0/2.0;
	printf("%.6lf\n",res);
}
int main(){
	ios::sync_with_stdio(false);
	cin>>_;
	while(_--){
		work();
	}
}
```

## 三分
三分算法的适用条件是：给出 $N$ 个函数，保证在范围内存在一点 $x$，使得左边界到 $x$ 上单调增，$x$ 到右边界上单调减。

可以用三分求出 $\max\{f_1(x),f_2(x),\dots,f_n(x)\}$ 取最小时，对应 $x$ 的值。

三分的原理详见 [P1883 函数](https://www.luogu.com.cn/problem/P1883)。

我们发现绝对值函数 $T_i=t_i+\vert x_i-x_0 \vert$ 是满足该三分算法对应的条件的，于是我们对 $x_0$ 进行三分从而得到答案。

### 代码

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N =200005;
const double eps=1e-7;
LL _,n,a[N],t[N];
inline double f(double x,LL i){
	return (fabs(a[i]-x)+t[i]);
}
double check(double x){
	double res=f(x,1);
	for(LL i=2;i<=n;i++){
		res=max(res,f(x,i));
	}
	return res;
}
void work(){
	double m1,m2,l=0,r=0x3f3f3f3f;
	while(r-l>eps){
		m1=l+(r-l)/3.0;
		m2=r-(r-l)/3.0;
		if(check(m1)>check(m2)){
			l=m1;
            	//如果m1对应的函数最大值比m2对应的值要大，
            	//则说明左边界l需要“收收味”。
		}
		else{
			r=m2;
           	//如果m2对应的函数最大值比m1对应的值要大，
           	//则说明右边界r需要“收收味”。
		}
	}
	printf("%.7lf\n",l);
}
int main(){
	ios::sync_with_stdio(false);
	cin>>_;
	while(_--){
		cin>>n;
		for(LL i=1;i<=n;i++){
			cin>>a[i];
		}
		for(LL i=1;i<=n;i++){
			cin>>t[i];
		}
		work();
	}
}
```
## 二分
对 $x_0$ 进行二分，对于每个 $x_0$ ，判断其左手边的人到达 $x_0$ 花费的最大时间，和其右手边的人到达 $x_0$ 花费的最大时间，哪个更大。

如果右边更大，就说明左手边的点到 $x_0$ 更快，而右手边的点到 $x_0$ 更慢，因此要让 $x_0$ 与右手边的点的距离更近，从而让节约右边的点到 $x_0$ 的时间。

所以下一步要往其右区间继续二分；反之同理。

### 代码

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 1e5+6;
const double eps = 1e-7;
LL _,n,a[N],t[N];
bool check(double x){
	double L=0,R=0;
	for(LL i=1;i<=n;i++){
		if(a[i]<x){
			L=max(L,x-a[i]+t[i]);
		}
		else{
			R=max(R,a[i]-x+t[i]);
		}
	}
	return R>=L;
}
void work(){
	cin>>n;
	LL mx=0;
	for(LL i=1;i<=n;i++){
		cin>>a[i];
		mx=max(mx,a[i]);
	}
	for(LL i=1;i<=n;i++){
		cin>>t[i];
	}
	double l=0,r=mx;
	while(r-l>eps){
		double mid=(l+r)/2.0;
		if(check(mid)){
			l=mid;
		}
		else{
			r=mid;
		}
	}
	printf("%.7lf\n",r);
}
int main(){
	ios::sync_with_stdio(false);
	cin>>_;
	while(_--){
		work();
	}
}
```
# 最后再说说坑点

### 时间效率
最开始取精度为 $10^{-8}$，然后就一直超时，最后改 $10^{-7}$ 就对了。

### 输出

```cpp
cout<<r<<'\n';//错误示范
```

用上面的方法，可能会将浮点数按科学计数法输出，导致答案错误。

---

## 作者：GalwayGirl (赞：9)

这估计是我迄今为止打过的 Div2 最难的 B 题了，C 题也好坑，~~两个题卡了我一个小时多。~~

## Solution
题目中很明显的特征就是求最大值最小，看起来很二分的亚子，没想到我根本就不知道怎么 check。

条条大路通罗马，让我们再观察一下其他特征，发现是要绝对值最小，脑海里浮现出初中仅存的知识：两点之间距离。如果能把题目中的 $t_i$ 放入绝对值中就好了，那就先这么去转化。

$\begin{cases}∣x_i-t_i-x_0∣(x_i<x_0)\\∣x_i+t_i-x_0∣(x_i\geq x_0)\end{cases}$

只看公式脑壳晕，让我们把它画到图上去。

![](https://cdn.luogu.com.cn/upload/image_hosting/x3oadufb.png)

这样就能清楚地看明白，当 $x_i\geq x_0$ 时，值就为 $x_i-t_i$ 到 $x_0$ 的距离，否则，值就为 $x_i+t_i$ 到 $x_0$ 的距离，这是对于每一个 $x_i$ 的，题目中说要取最大，那么就考虑极端情况，看下面的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/pgdkbuxk.png)

假设此时的 $x_1-t_1$ 为值域最小，$x_2+t_2$ 为值域最大。此时可能是最大的的值为 $x_0-(x_1-t_1)$ 和 $x_2+t_2-x_0$，此时 $x_0$ 取 $(x_1-t_1)$ 和 $(x_2+t_2)$ 的中点值最小，所以答案为 $(x_2+t_2+x_1-t_1)/2$。

最后见代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+100;
long long T,n,x[N],t[N];
void solve(){
    scanf("%lld",&n);
    long long min_=1e18,max_=-1e18;
    for(int i=1;i<=n;i++)scanf("%lld",&x[i]);
    for(int i=1;i<=n;i++)scanf("%lld",&t[i]);
    for(int i=1;i<=n;i++){         
        min_=min(min_,x[i]-t[i]);
        max_=max(max_,x[i]+t[i]);
    }                         
    printf("%.6lf\n",(min_+max_)*1.0/2);
}
int main(){
    scanf("%lld",&T);
    while(T--)solve();
    return 0;
}
```


---

## 作者：江户川·萝卜 (赞：6)

给定一个长为 $n$ 的序列 $x$ 和 $t$，请你求出一个 $x_0$，使得 $\max\limits_{i=1}^{n}\{t_i+|a_i-a_0|\}$ 最小化。

看到这是最小化最大值的形式，考虑二分最大值，求一下对于每个 $x_i$ 的合法区间的区间交是不是空集即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int x[100005],t[100005];
int res,n; 
bool check(int d){
	int l=0,r=4e8;
	for(int i=1;i<=n;i++){
		int dt=d-t[i];
		l=max(l,x[i]-dt);
		r=min(r,x[i]+dt);
	}
	if(l<=r){
		res=l;return 1;
	}
	return 0;
}
int main(){
	int T;cin>>T;
	while(T--){
		res=0;
		cin>>n;
		for(int i=1;i<=n;i++) cin>>x[i],x[i]*=2;
		for(int i=1;i<=n;i++) cin>>t[i],t[i]*=2;
		int l=*max_element(t+1,t+n+1),r=4e8;
		while(l<r){
			int mid=l+r>>1;
			if(check(mid)) r=mid;
			else l=mid+1;
		}
		printf("%.6lf\n",(double)res/2.0);
	}
}
```

---

## 作者：Larryyu (赞：4)

## _Description_
给定 $n$ 个人的坐标 $a_1,a_2\dots a_n$ 以及他们准备的时间 $t_1,t_2\dots,t_n$，请找出一个点，使得所有人到这个点的用时的最大值最小。

第 $i$ 个人到 $b$ 的用时为 $\left\vert a_i-b\right\vert+t_i$。
## _Solution_
绝对值的几何意义。

将 $t_i$ 转变为距离，分类讨论：
- $a_i<b$，则原式变为 $\left\vert a_i-t_i-b\right\vert$；
- $a_i\ge b$，则原式变为 $\left\vert a_i+t_i-b\right\vert$；

由于 $b$ 不确定，所以 $a_i+t_i$ 和 $a_i-t_i$ 都放一个点。

最后求最小坐标和最大坐标的中间值即可。
## _Code_
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int t;
int n;
ll a[100100];
ll maxn,minn;
ll read(){
    ll x=0,f=1;
    char ch;
    ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }
    return x*f;
}
int main(){
	t=read();
    while(t--){
        maxn=-10;
        minn=1e12;
        n=read();
        for(int i=1;i<=n;i++){
            a[i]=read();
        }
        for(int i=1;i<=n;i++){
            ll x;
            x=read();
            minn=min(minn,a[i]+x);  //求最大最小坐标
            maxn=max(maxn,a[i]+x);
            minn=min(minn,a[i]-x);
            maxn=max(maxn,a[i]-x);
        }
        printf("%.6f\n",(minn+maxn)/2.0);  //题目要求小数点后6位
    }
    return 0;
}

```
 #### _完结撒花！！_

---

## 作者：skyskyCCC (赞：3)

## 前言。
一道山东复赛补赛原题。
## 分析。
我们可以发现如果考虑坐标并且让化妆时间算为这个人在此坐标待的时间，会很难处理，因为你不知道让先化好妆的人往哪边走。

所以考虑另外一种思路。

我们可以将化妆时间看做这个人在数轴上走了几步，即这个人用 $t_i$ 的时间化妆，其实就是多走了 $t_i$ 步。

那在右边的人如果将他们的化妆时间看做向左多走了 $t_i$ 步，我们发现会出现重复和越位现象，不可取，即在右边的人只能把 $t_i$ 看作他往右走了 $t_i$ 步。

同理，在左边的人只能把 $t_i$ 看作他往左走了 $t_i$ 步。

所以我们就可以找到在转化后最右边的人和最左边的人，这时时间最优，因为中间的人肯定比他们先到地点。

那数轴上的这些人的最大距离就是最右边的人的左边减去最左边的人的左边的绝对值。因为他们是同时出发的，所以所用时间就是这个距离的一半。

代码如下，仅供参考：
```
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int T,n,a[100005],t[100005];
int main(){
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        for(int i=1;i<=n;i++) cin>>t[i];
        int minn=0x3f3f3f3f,maxx=-0x3f3f3f3f;
        for(int i=1;i<=n;i++){
            minn=min(minn,a[i]-t[i]);
            maxx=max(maxx,a[i]+t[i]);
        }
        minn+=maxx;
        if(minn&1){
            printf("%.1lf\n",minn/2.0);
        }
        else{
            cout<<minn/2<<"\n";
        }
    }
    return 0;
}
```
## 后记。
考场上想出正确思路，但是因为最大值开小了，痛失 $20$ 分。

大家如有疑问，请在评论区提出，我会尽力解答的。

---

## 作者：FreedomKing (赞：3)

### 题目大意

给你数轴上的 $n$ 个点，每个点初始的位置为 $x_i$，对于每个点需要等待 $t_i$ 秒才能开始移动，求数轴上一点 $k$ 使这 $n$ 个点到达的时间最短。

### 思路

首先 $1\le t_i\le 10^8$ 的数据范围直接排除了二分的可能性，那肯定就要从 $n$ 个节点下手了。

不难发现，我们可以把 $t_i$ 视作 $a_i$ 从离点 $k$ 距离为 $\left|k-t_i\right|$ 的地方出发，如图。

![](https://cdn.luogu.com.cn/upload/image_hosting/hjkgcwj2.png)

这样就可以把问题转换为寻找 $2n$ 个点相距最远的两个点的中点了。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
int a[N],n,m,t,k,maxn,minn;
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		minn=2147483647;
		maxn=-2147483648;
		for(int i=1;i<=n;i++){
			cin>>m;
			maxn=max(maxn,a[i]+m);
			minn=min(minn,a[i]-m);
		}
		double x=(maxn+minn)/2.0;
		if(floor(x)==x) cout<<(int)(x)<<'\n';
		else printf("%.1f\n",x);
	}
	return 0;
}
```

顺带一提，SD 2022 普及补考竟然用这道原题，原题大赛 bct 传统艺能了属于是。

---

## 作者：Shameimaru_Aya (赞：2)

首先是最简单的情况，如果所有人同时出发，使集合时间最短的位置是**左右两端的人的位置的中点**。

然后加上等待时间。假设集合位置在第 $i$ 个人和第 $i+1$ 个人中间时，将前 $i$ 个人往左移动他们的等待时间，将之后的人往右移动。这样问题就转化为了简单情况。

赞美前缀。$\Theta(n)$ 算出前 $i$ 个人往左移动后的最左端和后 $n-i+1$ 个人往右移动后的最右端。这两个值的平均值就是这一段算出的**理想位置**。

注意下理想位置可能超出第 $i$ 个人和第 $i+1$ 个人的范围。

code：

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
const int maxn=1e5+50;
struct node{
	long double x,t;
}a[maxn];
bool cmp(node a,node b)
{
	return a.x<b.x;
}
long double abs(long double k)
{
	return (k<0)?(-k):(k);
}
long double qz[maxn],hz[maxn];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i].x;
		for(int i=1;i<=n;i++)cin>>a[i].t;
		sort(a+1,a+n+1,cmp);
		
		qz[0]=1e17;
		for(int i=1;i<=n;i++)qz[i]=min(a[i].x-a[i].t,qz[i-1]);
		for(int i=1;i<=n;i++)qz[0]=min(qz[0],a[i].x+a[i].t);
		
		hz[n+1]=-1e17;
		for(int i=n;i>=1;i--)hz[i]=max(a[i].x+a[i].t,hz[i+1]);
		for(int i=1;i<=n;i++)hz[n+1]=max(hz[n+1],a[i].x-a[i].t);
		
		a[0].x=-1e17;a[n+1].x=1e17; 
		long double ms=1e17,s=-1;
		for(int i=0;i<=n;i++)
		{
			long double pos=(hz[i+1]+qz[i])/2;
			long double l=a[i].x,r=a[i+1].x;
			if(r<=pos)pos=r;
			if(pos<=l)pos=l;
			if(ms>max(abs(hz[i+1]-pos),abs(pos-qz[i])))
			{
				s=pos,ms=max(abs(hz[i+1]-pos),abs(pos-qz[i]));
			}
		}
		printf("%Lf\n",s);
	}
}
```


---

## 作者：Lagerent (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1730B)

考虑 $t$ 均为 $0$ 的情况。

取最左边点和最右边点的平均值就行。可以证明，不在这个点上的话，答案一定会变大。

再来考虑一般情况。

我们思考，加上了 $t$ 实际上对全局的影响是导致每个人的**出发起始时间不一样**。然而 $t$ 均为 $0$ 时所有人都是同时出发的。那么我们有没有办法可以将它转化为出发时间一样呢？

显然是有的。因为穿衣时间会使总共的用时变长，那么我们可以**将第 $i$ 个点的起始坐标向远离 $x_0$ 的位置移动 $t_i$ 个单位**，他的用时就等价于在移动后的点上直接走向 $x_0$ 的用时。对于每个点都这样处理一遍，那么这个问题就等价于 $t$ 均为 $0$ 的情况了。

但是我们在求解时不能确定 $x_0$ 的位置，该如何判断是往左还是往右移呢？

我们可以**都移**。移反的那个点会**拉近**我们与 $x_0$ 之间的距离，但是我们在统计答案的时候求的是最大值，所以这个点就不会对答案产生贡献。

于是此题就被优雅地解决掉了。

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rep(a, b, c) for(int (a) = (b); (a) <= (c); ++ (a))
#define per(a, b, c) for(int (a) = (b); (a) >= (c); -- (a))
using namespace std;

const int N = 2e5 + 10;

int x[N], T, n;

int main() {
	scanf("%d", &T);
	while(T -- ) {
		scanf("%d", &n);
		rep(i, 1, n) scanf("%d", &x[i]);
		int maxn = 0, minn = 1e8;
		rep(i, 1, n) {
			int t;
			scanf("%d", &t);
			maxn = max(maxn, x[i] + t);
			minn = min(minn, x[i] - t);
		}
		double t = (double)1.0 * (maxn + minn) / 2;
		if(t == maxn + minn >> 1) printf("%d\n", maxn + minn >> 1);
		else printf("%d.5\n", maxn + minn >> 1);
	}
	return 0;
}
```

---

## 作者：ImNot6Dora (赞：1)

话说沙东补考真是可以，已经找到两道洛谷原题了。。。
# 正文
考场上没想到方法，考完试出来和另一个同学聊了聊，突然想到了一种奇怪的做法。

正解貌似是二分，但是这道题明显也可以用贪心啊！！！

我们首先标记出打扮用时时间最长的那个人，那么剩下的人在打扮完之后就向他走去，当那个人打扮完之后，我们再从头扫一遍所有人的位置，找出最左和最右的两个人，那么最终的地点就是这两个人的中点（因为无论如何这两个人用的时间总比其他人远，所以这样能让两端的人走的最快）！~~（考试的时候怎么没想出来，考砸了）。~~

所以说，这道题其实可以降到黄甚至是橙的吗。。。
# AC C++ CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int t;//打扮时间 
	int x;//初始位置 
}a[100010];
int main(){
	int t;
	cin>>t;
	while(t--){
		memset(a,0,sizeof(a));//数组不清空，亲人两行泪 
		int n,s=-1,k;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i].x;
		}
		for(int i=1;i<=n;i++){
			cin>>a[i].t;
			if(a[i].t>s){//找出换衣服时间最长的人 
				s=a[i].t;//标记打扮用的时间和位置 
				k=a[i].x;
			}
		}
		for(int i=1;i<=n;i++){
			if(a[i].x==k)continue; 
			int opt=s;
			if(opt>a[i].t)opt-=a[i].t; 
			else continue;
			if(opt>=abs(a[i].x-k))a[i].x=k;//如果能在换衣服最慢的人之前走到他那里，就标记新位置
			else if(a[i].x<k)a[i].x+=opt;//否则，还剩下多少时间就能走多远 
			else a[i].x-=opt;//注意区分左右 
		}
		s=100000010,k=-1;
		for(int i=1;i<=n;i++){
			if(a[i].x<s)s=a[i].x;//重新扫一遍所有人的位置，找出最左的和最右的人 
			if(a[i].x>k)k=a[i].x;
		}
		if((s+k)%2==0)cout<<(s+k)/2<<'\n';//能整除就直接输出 
		else cout<<fixed<<setprecision(1)<<(s+k)/2.0<<'\n';//不能整除就保留一位 
	}
	return 0;
}

```
By ImNot6Dora

---

## 作者：eggegg185 (赞：1)

从山东J补赛过来的，感谢CCF的馈赠（喜

首先，这个化妆时间很难弄，但是如果说能归到距离里就好了，显然我们发现，多花了 $t_i$ 秒化妆，其实就是多走了 $t_i$ 步，也就是家在宴会地点右边的官员的家往右移 $t_i$ 步，左边的左移 $t_i$ 步。我们肯定要找**转化后**最左边的官员（位置在 $\min\{a_i-t_i\}$ ）和最右边的官员（位置在 $\max\{a_i+t_i\}$ ），这两个官员中间的官员肯定要比他们先到，不然肯定不优。所以时间就是 $\max\{a_0-\min\{a_i-t_i\},\max\{a_i+t_i\}-a_0\}$ 。显然取 $a_0 = \frac{\max\{a_i+t_i\} + \min\{a_i-t_i\}}2$ 最优，答案为 $\frac{\max\{a_i+t_i\} + \min\{a_i-t_i\}}2$ 。

$\text{Code:}$
```cpp
#include <iostream>
#include <iomanip>
using namespace std;
int n,a[114514],t[114514];
int main() {
	int T;
	cin >> T;
	while(T--) {
		cin >> n;
		for(int i = 1; i <= n; i++) {
			cin >> a[i];
		}
		for(int i = 1; i <= n; i++) {
			cin >> t[i];
		}
		int mi = 99999999+1;
		int mx = -mi;
		for(int i = 1; i <= n; i++) {
			mi = min(mi,a[i]-t[i]);
			mx = max(mx,a[i]+t[i]);
		}
		mi += mx;
		if(mi & 1) {
			cout << fixed << setprecision(1) << mi/2.0 << endl;
		} else {
			cout << mi/2 << endl;
		}
	}
	return 0;
}
```

---

## 作者：许多 (赞：0)

首先想到，如果没有 $t$，那这道题很好做，最大值加最小值除以二即可。

我们考虑把 $t$ 看做距离，如果 $x_0$ 在 $x_i$ 右侧，即将 $x_i-t_i$ 看为新 $x_i$，在左侧同理。

我们就把 $x_i$ 看成两个点，一个是 $x_i-t_i$，一个是 $x_i+t_i$。

那么处理完之后答案就是最大值加最小值除以二。

我们设 $x_i-t_i$ 为最小值，$x_j+t_j$ 为最大值，但当 $i=j$ 时怎么处理呢？

我们发现，无论 $x_0$ 在 $x_i$ 右侧还是左侧，时间都绝对 $>t_i$，但如果 $x_0=x_i$，时间便 $=t_i$，即是 $(x_i+t_i+x_i-t_i)/2=x_i$。

# 代码

 ```cpp
#include<bits/stdc++.h>
#include<cstdio>
#define N 200000
#define LL long long
inline LL read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*f;
}
using namespace std;
LL T,n,x[N],t[N],l,r;
int main(){
    T=read();
    while(T--){
        n=read();l=1000000000;r=-l;
        for(int i=1;i<=n;i++)
            x[i]=read();
        for(int i=1;i<=n;i++){
            t[i]=read();
            l=min(l,x[i]-t[i]);//最左
            r=max(r,x[i]+t[i]);//最右
        }
        printf("%.6lf\n",(l+r)*1.0/2);
    }
    return 0;
}
```


---

## 作者：tZEROちゃん (赞：0)

如果 $t_i=0$，那就是一个经典题目，结论就是取最大点坐标和最小点坐标的平均数。

但是 $t_i\neq 0$，考虑转化上述问题。显而易见的，我们可以把一个人拆成两个人，一个在 $x_i-t_i$ 的位置，一个在 $t_i-x_i$ 的位置。然后就按照上述问题解决方案解决即可。时间复杂度 $O(n)$。

考虑证明，设取点 $y$，$x_i\le y$，那么这个人需要用 $t_i+y-x_i$ 的时间，当我们把他拆开之后，这两个人分别需要 $y-x_i+t_i$ 的时间和 $y-x_i-t_i$ 的时间，可以容易发现第一个人与原来的是一致的，而第二个一定是小于原来的值的，因此这两个人的最大值还是原来的不变。$y< x_i$ 也可以用这种类似的方法证明。

本题同样存在时间复杂度 $O(n\log n)$ 的二分解法。各位可以自行思考或参考官方题解。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i, l, r) for(auto i = (l); i <= (r); ++i)
#define per(i, r, l) for(auto i = (r); i >= (l); --i)
#define _rep(i, l, r) for(auto i = (l); i < (r); ++i)
#define _per(i, r, l) for(auto i = (r); i > (l); --i)
#define pb push_back

const int N = 1e5 + 10;
int x[N];

void solve() {
  int n; cin >> n;
  int mx = 0, mn = 0x3f3f3f3f;
  rep (i, 1, n) cin >> x[i];
  rep (i, 1, n) {
    int t; cin >> t;
    int x1 = x[i] + t, x2 = x[i] - t;
    mx = max({mx, x1, x2});
    mn = min({mn, x1, x2});
  }
  cout << ((mx + mn) >> 1) << (((mx + mn) & 1) ? ".5\n" : "\n");
} 

int main() {
  int q; cin >> q;
  while (q--) solve();
}
```

---

