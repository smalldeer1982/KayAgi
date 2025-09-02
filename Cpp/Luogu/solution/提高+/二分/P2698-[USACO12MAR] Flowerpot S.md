# [USACO12MAR] Flowerpot S

## 题目描述

Farmer John has been having trouble making his plants grow, and needs your help to water them properly.  You are given the locations of N raindrops (1 <= N <= 100,000) in the 2D plane, where y represents vertical height of the drop, and x represents its location over a 1D number line:

 ![](https://cdn.luogu.com.cn/upload/pic/9174.png) 

Each drop falls downward (towards the x axis) at a rate of 1 unit per second.  You would like to place Farmer John's flowerpot of width W somewhere along the x axis so that the difference in time between the first raindrop to hit the flowerpot and the last raindrop to hit the flowerpot is at least some amount D (so that the flowers in the pot receive plenty of water).  A drop of water that lands just on the edge of the flowerpot counts as hitting the flowerpot. 

Given the value of D and the locations of the N raindrops, please compute the minimum possible value of W.

老板需要你帮忙浇花。给出 $N$ 滴水的坐标，$y$ 表示水滴的高度，$x$ 表示它下落到 $x$ 轴的位置。

每滴水以每秒 $1$ 个单位长度的速度下落。你需要把花盆放在 $x$ 轴上的某个位置，使得从被花盆接着的第 $1$ 滴水开始，到被花盆接着的最后 $1$ 滴水结束，之间的时间差至少为 $D$。

我们认为，只要水滴落到 $x$ 轴上，与花盆的边沿对齐，就认为被接住。给出 $N$ 滴水的坐标和 $D$ 的大小，请算出最小的花盆的宽度 $W$。

## 说明/提示

有 $4$ 滴水，$(6,3)$ ，$(2,4)$ ，$(4,10)$ ，$(12,15)$ 。水滴必须用至少 $5$ 秒时间落入花盆。花盆的宽度为 $2$ 是必须且足够的。把花盆放在 $x=4\dots6$ 的位置，它可以接到 $1$ 和 $3$ 水滴, 之间的时间差为 $10-3=7$ 满足条件。

**【数据范围】**

$40\%$ 的数据：$1 \le N \le 1000$ ，$1 \le D \le 2000$ 。

$100\%$ 的数据：$1 \le N \le 10 ^ 5$ ，$1 \le D \le 10 ^ 6$ ，$0\le x,y\le10^6$ 。

## 样例 #1

### 输入

```
4 5
6 3
2 4
4 10
12 15```

### 输出

```
2```

# 题解

## 作者：llzzxx712 (赞：82)

# P2698

 **前言：本题赞最高的那篇题解已经写得很清楚了，但本蒟蒻还是花了不少时间去理解，我决定把一些可能造成障碍的地方再解释一下**

## 题意简述

- 给出一条线段上的 n 个点，每个点有一个权值 $y_i$ ,你要找出一段区间，使区间中的 $y_{max}-y_{min}$ 大于 d 。
- 输出这个区间的长度

## 题目分析

首先看到这道题（和这道题的标签）就发现直接求解长度非常麻烦，可以二分区间长度再去判断。

但是再一想，就会发现所在的区间端点一定在水滴上。

**为什么呢？** 因为我们的花盆是要碰到水滴才可以计算答案，在水滴外面的部分就浪费了，所以区间端点一定在水滴上。

那么原问题就转化为了：给出一段数 ($y$) ，选出最短的一段，使其中的 最大值-最小值 大于 d 。

那么怎么求这一段呢？一个暴力的解法是枚举左右端点。复杂度 $O(n^2)$ ，T飞~。
另一种方法是用单调队列，这里和滑动窗口稍微有些不同。滑动窗口的区间长度是固定的，要就内部的最大（小）值；这里给出区间内部的条件，求长度。

我们可以采用一个“拉窗口”的方法，最开始左端点和右端点都在最左边。

【】

我们可以把
1. 这个右端点不断往右拉，直到满足条件

【…………】

2. 记录一下答案，然后把左端点往右拉一下

…【…………】

3. 重复一二步骤，直到右端点到达右边界

因为左右端点都只是从左边移到右边，所以复杂度是 $O(n)$ 的。

## 代码思路
这里我们不关注具体的 x 值而去记录点的编号，因为区间端点一定在水滴上。排序后编号小的 x 一定小，只在记录答案的时候通过编号查询具体 x 值。

我们用两个优先队列，一个存区间最大值，一个存区间最小值。

最外层循环拉左端点（因为要里面右端点移完再动左端点）

每次先用两个while循环更新队首,直到队首不在左端点左边（因为移动了左端点有一个点的值就不能用了）

然后第二层循环移动右端点，直到达到右边界或满足条件（最大值-最小值 > d）。

里面再用两个循环类似滑动窗口更新最大值队列和最小值队列（只要队中还有元素且新加入的元素比队尾大（维护最大值时为小）那么就队尾出队，不需要管队首出队（这是更新左端点做的事情））。

第二层循环结束后，如果满足条件就更新 $ans$ 。（$ans$要初始化成一个很大的值）。

一切结束后如果 $ans$ 还是初始值，就输出 “-1”，否则输出 $ans$ 。

## 易错点

1. 两个队首都要像滑动窗口那样设置为 1 。（表明队列中有元素）
1. 要用结构体存输入（因为要按 x 排序）
1. $ans$要初始化成一个很大的值
1. 判断是否有解
1. 更新队首要让队首不在左端点左边（用 < 而不是 <=）。

## 详细注释代码

```cpp
#include<bits/stdc++.h>
using namespace std;
void read(int &x){//快读 
	int f=1;x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') { x=x*10+ch-'0';ch=getchar();}
	x*=f;
}
#define N 100010
int n,d,ans;
struct node{
	int x,y;
}a[N];
bool cmp(node aa,node bb){
	return aa.x<bb.x;
}
int p1[N],p2[N];//我写单调队列一般用 q[] 存具体值，用 p[]存位置 
int head1,head2,tail1,tail2;//队列 1存最大值，队列 2存最小值 
int main(){
	read(n),read(d);//如题所示 
	for(int i=1;i<=n;i++){
		read(a[i].x),read(a[i].y);//结构体，因为要排序 
	}
	sort(a+1,a+1+n,cmp);//排序 
	ans=0x3f3f3f3f;
	head1=head2=1;
	for(int le=0,r=0;le<=n;le++){//最外层循环拉左端点 
		while(head1<=tail1&&p1[head1]<le) head1++;//如果队首比左端点小，那么右移
		while(head2<=tail2&&p2[head2]<le) head2++;//因为排序过了，编号小x一定小 
		while(a[p1[head1]].y-a[p2[head2]].y< d && r<n){
			r++;
			while(head1<=tail1&&a[p1[tail1]].y<a[r].y) tail1--;
			p1[++tail1]=r;
			while(head2<=tail2&&a[p2[tail2]].y>a[r].y) tail2--;
			p2[++tail2]=r;//更新两个单调队列 
		}
		if(r!=n) ans=min(ans,a[r].x-a[le].x);//满足条件 
	} 
	if(ans>=0x3f3f3f3f){//判无解 
		printf("-1");return 0;
	}
	else{
		printf("%d",ans);
	}
}

```

蒟蒻写题解不易，若对你有帮助，点个赞呗

---

## 作者：青衫白叙 (赞：46)

正如楼下dalao所说，这题就是滑动窗口。。。不过不需要二分。。

首先两个单调队列不用说。。说明一下：我的单调队列里存的是下标。。

- 条件：[l ， r] 中的最大的水滴高度减去最小的水滴高度大于等于 d

- 首先。我们枚举左端点 l ，找到第一个满足条件的右端点 r (我们要求的是 r - l 最小)，更新答案。

我们容易知道（原谅我说这种话）。。如果一个左端点 l1 对应着 右端点 r1，那么 l2 (l2 > l1) 的右端点 r2 >= r1。

需要证一下吗？？简单证一下吧。。假设 l2 有满足条件的端点 r2 < r1，那么 r2 才应该是 l1 满足条件的第一个右端点。。矛盾了。。

所以我们得出结论。。r 单调递增。。。

- 然后，就是枚举左端点 l，更新 r 的值，并且维护滑动窗口。。。

维护操作大致如下：

```cpp
        while(h1<=t1&&q1[h1]<l) ++h1;
        while(h2<=t2&&q2[h2]<l) ++h2;
```
- 然后，如果l ， r 中的最大的水滴高度减去最小的水滴高度不大于 d 的话，我们将 r 后面的元素加入队列直到满足该条件。

具体操作如下：

```cpp
         while(a[q1[h1]].y-a[q2[h2]].y < d && r < n) {
            ++r;
            while(a[q1[t1]].y < a[r].y && h1<=t1) --t1;q1[++t1]=r;
            while(a[q2[t2]].y > a[r].y && h2<=t2) --t2;q2[++t2]=r; 
        }
```
- 然后更新一下最小值就好。。。如果最小值一直没变的话。。答案就是 -1 了。。

代码如下：

```cpp
#prag\
ma GCC optimize("O3")
#include<bits/stdc++.h>
#define ri register int
#define I __inline__ __attribute((always_inline)) 
using namespace std;
I char nc(){
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
I int read1( ){
    static char c=nc();ri x,f=1;
    for(;c>'9'||c<'0';c=nc()) if(c=='-') f=-1;
    for(x=0;c<='9'&&c>='0';c=nc()) x=(x<<3)+(x<<1)+c-48;
    return x*f;
}
#define N 100005
#define read(a) a=read1()
int n,d,h1,h2,t1,t2,ans=1e9;
int q1[N],q2[N];
struct node{int x, y;}a[N];
I bool cmp(node a,node b)
{return a.x < b.x;}
int main() {
    ri l = 1, i, r;h1 = h2 = 1;
    read(n);read(d);
    for(i=1; i<=n; ++i) read(a[i].x),read(a[i].y);
    sort(a+1,a+n+1,cmp);
    for(l=1,r=0;l<=n;++l) {
        while(h1<=t1&&q1[h1]<l) ++h1;                                 // 维护滑动窗口
        while(h2<=t2&&q2[h2]<l) ++h2;
        while(a[q1[h1]].y-a[q2[h2]].y < d && r < n) {
            ++r;
            while(a[q1[t1]].y < a[r].y && h1<=t1) --t1;q1[++t1]=r;          //维护单调队列
            while(a[q2[t2]].y > a[r].y && h2<=t2) --t2;q2[++t2]=r; 
        }
        if(a[q1[h1]].y-a[q2[h2]].y >= d) ans = min(ans,a[r].x-a[l].x);       //更新答案
    }
    printf("%d",ans>=1e9?-1:ans);
    return 0;
}
```

---

## 作者：老K (赞：22)

一个显然的性质：设$f_i$表示以i为左端点时右端点的最小值，那么$f_i$单调不减。

由于$f_i$单调不减，可以这么计算$f_i$（大概是伪代码：

```C++
int s=1;
for(int i=1;i<=n;++i){
	while(s<=n && !ok(i,s))++s;
    f[i]=s;
}
```

其中ok(l,r)表示[l,r]这个区间是否满足条件。

直接算还是$O(n^2)$的。

然后我们仔细考虑这段代码：

++i？ 把i从区间去掉？

++s？ 在区间末尾加一个元素？

滑动窗口？？

没错，ok(l,r)就可以用滑动窗口维护。

当然上面的代码也可以写成这样：

```C++
int l=1,r=1;
while(r<=n){
	while(r<=n && !ok(l,r))++r;
    while(l<=r && ok(l,r)){f[l]=r;++l;}
}
```

那么这道题就做完了。

由于x坐标的范围不大，并不需要sort，直接桶排就可以了。

时间复杂度$O($值域$)$

```C++
/*
Author: CNYALI_LK
LANG: C++
PROG: 2698.cpp
Mail: cnyalilk@vip.qq.com
*/
#include<bits/stdc++.h>
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define DEBUG printf("Passing [%s] in LINE %d\n",__FUNCTION__,__LINE__)
#define Debug debug("Passing [%s] in LINE %d\n",__FUNCTION__,__LINE__)
#define all(x) x.begin(),x.end()
#define x first
#define y second
using namespace std;
const double eps=1e-8;
const double pi=acos(-1.0);
typedef long long ll;
typedef pair<int,int> pii;
template<class T>int chkmin(T &a,T b){return a>b?a=b,1:0;}
template<class T>int chkmax(T &a,T b){return a<b?a=b,1:0;}
template<class T>T sqr(T a){return a*a;}
template<class T>T mmin(T a,T b){return a<b?a:b;}
template<class T>T mmax(T a,T b){return a>b?a:b;}
template<class T>T aabs(T a){return a<0?-a:a;}
template<int *a>int cmp_a(int x,int y){return a[x]<a[y];}
#define min mmin
#define max mmax
#define abs aabs
int read(){
	int s=0,base=1;
	char c;
	while(!isdigit(c=getchar()))if(c=='-')base=-base;
	while(isdigit(c)){s=s*10+(c^48);c=getchar();}
	return s*base;
}
bool cx[1048575];
int mn[1048575],mx[1048575];
template<const function<int(int,int)> &cmp>
struct MQ{
	int s[1048575],*l,*r;	
	MQ(){l=s+1;r=s;}
	void add(int x){
		while(l<=r && cmp(x,*r))--r;
		*(++r)=x;
	}
	void del(int x){
		if(*l==x)++l;
	}
	int top(){return *l;}
};
int increase(int a,int b){return a<b;}
int decrease(int a,int b){return a>b;}
function<int(int,int)> Inc=increase;
function<int(int,int)> Dec=decrease;
MQ<Inc> inc;
MQ<Dec> dec_;
int main(){
#ifdef cnyali_lk
	freopen("2698.in","r",stdin);
	freopen("2698.out","w",stdout);
#endif
	int n,d,x,y,l,r,xmn=0x3f3f3f3f;	
	n=read();d=read();
	for(int i=0;i<=1000000;++i)mn[i]=0x3f3f3f3f,mx[i]=-0x3f3f3f3f;
	for(int i=1;i<=n;++i){
		x=read();y=read();
		chkmax(mx[x],y);
		chkmin(mn[x],y);
		cx[x]=1;
		chkmin(xmn,x);
	}
	l=xmn,r=xmn;	
	inc.add(mn[l]);
	dec_.add(mx[l]);
	int ans=0x3f3f3f3f;
	n=1000000;
	while(r<=n){
		while(r<=n && dec_.top()-inc.top()<d){++r;if(cx[r]){inc.add(mn[r]);dec_.add(mx[r]);}}
		while(l<r && dec_.top()-inc.top()>=d){if(cx[l]){inc.del(mn[l]);dec_.del(mx[l]);}++l;}
		if(r<=n)
		chkmin(ans,r-l+1);
	}
	if(ans==0x3f3f3f3f)printf("-1\n");
	else printf("%d\n",ans);
	return 0;
}


```


---

## 作者：subarude (赞：17)

## ~~为了您的身心健康$qwq$~~
## 请在认真思考后参考题解$qwq$


------------

### 由于本人十分弱，很多地方理解可能还不是很到位

### 本题解可能有很多疏漏之处，还请多多包涵

### 如果有错误欢迎指出

### 可以在评论区直接指出也可以私信

### 个人主页也有$QQ$
------------


首先可以考虑暴力

可以从小到大暴力枚举花盆的宽度，然后暴力枚举在此宽度下可以接到的水滴最大的时间差

会发生什么呢？？？

~~显然会$T$到飞起啊$qwqwq$~~

于是，我们要考虑优化
~~这不是废话吗~~

从小到大枚举花盆的宽度？

啊嘞？
$ \text {cyo\ to\ ma tte、 }$
$ \text {从小到大？？？}$

$hin$显然我们可以二分啊$qwqwq$



------------
然而

~~枚举花盆宽度 + 枚举水滴 == TLE~~

~~二分花盆宽度 + 枚举水滴 ，似乎还是不太行$qwq$~~

所以我们要考虑进一步的优化

……

这个水滴……

单调队列的性质在这里似乎很适用

那么，可以在确定区间长度以后考虑单调队列

------------


###### 单调队列不会的话可以先康一下[滑动窗口](https://www.luogu.org/problemnew/show/P1886)
###### $\text {其他dalao们的题解里好像也有其他做法可以代替这个东西}$


###### 它的题解里已经把滑动窗口解释的$hin$详细了
###### ~~我这辈子是写不出那么优秀的题解了$qwq$~~



------------


从左到右滑动正在考虑的区间

用单调队列~~的常规操作~~维护区间内的最大值和最小值

两者相减即为这个区间内最高的水滴与最低的水滴的高度差

如果在这个花盆宽度下最大的高度差大于题目所给的至少的时间差的话就表示这个宽度可以

否则即为不可以

~~麻麻再也不用担心窝TLE了~~






$jya$
就先这样吧

如果还有不理解的地方也可以加QQ交流
~~再说一遍，个人主页有哦~~











下面附上代码
有一些注释


```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>

#define maxn 100010

using namespace std;

//快读
inline int read() {
    int op = 1, a = 0;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar()) if (c == '-') op = -1;
    for (; c >= '0' && c <= '9'; c = getchar()) a = a * 10 + c - '0';
    return op * a;
}

int n, d;
struct point {int x, y;} p[maxn];//存水滴的信息（坐标）

bool cmp(point a, point b) {return a.x < b.x;} //为水滴排序

//单调队列
struct MINandMAX {
    int head, tail;
    int m[maxn], i[maxn];
    // m[] 存最大值或最小值
    // i[] 是在很多单调队列中用来存一个数在原数组中的下标
    // 在这里我存了一个水滴的 x ，用来辅助判断一个水滴是否已经不再正在考虑的区域内
} Min, Max;
// 个人更喜欢用数组

//判断花盆宽度为 t 时是否可以，1为可以，0为不可以
bool check(int t) {
    Max.head = 1, Max.tail = 0;
    Min.head = 1, Min.tail = 0;
    for (int i = 1; i <= n; i++) {
//单调队列维护y的最大值：
        for (; Max.head <= Max.tail && Max.m[Max.tail] <= p[i].y; ) Max.tail--;
        Max.m[++Max.tail] = p[i].y;
        Max.i[Max.tail] = p[i].x;
        for (; Max.i[Max.head] < Max.i[Max.tail] - t; ) Max.head++;
//单调队列维护y的最小值：
        for (; Min.head <= Min.tail && Min.m[Min.tail] >= p[i].y; ) Min.tail--;
        Min.m[++Min.tail] = p[i].y;
        Min.i[Min.tail] = p[i].x;
        for (; Min.i[Min.head] < Min.i[Min.tail] - t; ) Min.head++;

        int temp = Max.m[Max.head] - Min.m[Min.head];
        //用 temp 存一下区域内高度最大的与最小的水滴的高度差
        //即用这个区域内最大的 y 减去最小的 y
        if (temp >= d) return 1;
    }
    return 0;
}

int main() {
//按照题意读入数据
    n = read(), d = read();
    for (int i = 1; i <= n; i++) {
        p[i].x = read();
        p[i].y = read();
    }
//把水滴按照 x 来排序
    sort(p + 1, p + n + 1, cmp);
    int l = 1, r = p[n].x + 10;
    for (; l < r; ) {
        int mid = l + r >> 1;
        if (check(mid)) r = mid;
        //如果花盆宽度为 mid 时可以，就在 l..mid 区间内继续二分
        else l = mid + 1;
        //否则，在 mid + 1..r 区间内继续二分
    }
    if (l > p[n].x) cout << -1 << '\n';
    else cout << l << '\n';
    return 0;
}
//码风这么丑，能看下来辛苦了 qwq

```

#### 蒟蒻第一次发题解
~~引起不适还请轻喷~~

---

## 作者：YoungNeal (赞：16)

先安利一下自己的博客 [YoungNeal](http://www.cnblogs.com/YoungNeal/)  

虽然这题是从单调队列标签里找出来的，但是由于太菜，一直想不到怎样用单调队列解决这题。

所以蒟蒻的我用了 ST表  
先科普一下 ST表：对于一个数列，在 $O(nlogn)$ 的时间里预处理之后，用 $O(1)$ 的时间来查询区间的最值 (因为区间最值满足区间加法)
 
知道了这个再来看这道题：  
为什么二分答案就不说了，答案显然满足单调性  
怎么建表呢，我们发现，这道题要求的是区间内的最大值减去最小值，所以自然而然的想到了搞出来两个 ST表，一个维护最大值，一个维护最小值。  
然后对于每一个二分答案的 $MID$，$O(n)$ 的枚举花盆的左端点放在哪里(因为已经二分出了 $MID$，所以知道了左端点，就可以求出右端点了)，$O(1)$ 的查询最大值减去最小值是否满足题意就好了。  
还有一个要注意的是题目里坐标和编号不对应，所以数组要开到坐标那么大。

时间复杂度 $O(nlogn)$  (比楼下 $O(n)$  的单调队列慢一点)

```
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#define N 1000005

int n,d;
int maxzb;
int stmin[N][21];
int stmax[N][21];

int query(int l,int r){
	int t=log2(r-l+1);
	int maxn=std::max(stmax[l][t],stmax[r-(1<<t)+1][t]);
	int minn=std::min(stmin[l][t],stmin[r-(1<<t)+1][t]);
	return maxn-minn;
}

bool check(int x){
	for(int i=1;i<=maxzb-x;i++){
		int to=i+x;
		if(query(i,to)>=d) return 1;
	}
	return 0;
}

signed main(){
	scanf("%d%d",&n,&d);
	memset(stmin,0x3f,sizeof stmin);
	for(int x,y,i=1;i<=n;i++){
		scanf("%d%d",&x,&y); maxzb=std::max(maxzb,x);
		stmax[x][0]=std::max(stmax[x][0],y);
		stmin[x][0]=std::min(stmin[x][0],y);
	}
	int t=log2(maxzb);
	for(int j=1;j<=t;j++){
		for(int i=1;i<=maxzb-(1<<j)+1;i++){
			stmax[i][j]=std::max(stmax[i][j-1],stmax[i+(1<<j-1)][j-1]);
			stmin[i][j]=std::min(stmin[i][j-1],stmin[i+(1<<j-1)][j-1]);
		}
	}
	int l=1,r=maxzb;
	int ans=-1;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：优少 (赞：11)

说实话各位大佬的题解我是真的没太看懂，可能是蒟蒻我太菜了

那我就尽我可能把我自己的做法用**比较**易懂的方式讲一下

首先我们简化一下题意：

**要找一段区间[L,R]，使区间[L,R]内元素最大值减最小值大于等于D。**

做法：

首先~~很容易~~想到采用**二分**，分什么呢？

我们二分区间长度为mid

这个时候，**检验**就成为了我们的目标

最暴力的检验就是枚举左端点，在区间内找最大和最小，有一个max-min>=D

让我们模拟一下：

假如mid=2：

(1) [1,3]

(2) [2,4]

(3) [3 5]

(4)  .....

我们震惊的发现：[P1886 滑动窗口](https://www.luogu.org/problem/P1886)
![](https://cdn.luogu.com.cn/upload/pic/688.png)

这貌似有点相似

于是正解出现了

# 正解：

**二分区间长度**为mid，检验时用**单调队列**维护区间最大最小值，复杂度**nlogn**，更多细节见代码：

# 代码时间到：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,D,l,r;
struct WATER{
	int x,y;
}p[100010];
int ans=2100000000;
int q1[100010],q2[100010];
int p1[100010],p2[100010];
int head1=1,tail1=1,head2=1,tail2=1;
bool check(int k){
	int L=1;
	q1[1]=p[1].y;p1[1]=p[1].x;
	q2[1]=p[1].y;p2[1]=p[1].x;
	head1=1,tail1=1,head2=1,tail2=1;                   //初始化队列和head，tail 
	for(int i=2;i<=n;i++){
		while((p[i].x-p[L].x)>k) L++;                  //控制左端可以到哪 
		while(p1[head1]<p[L].x&&head1<=tail1)          //队头出队 
		      head1++;                                   
		while(p2[head2]<p[L].x&&head2<=tail2)          //队头出队 
		      head2++;
		while(q1[tail1]<=p[i].y&&head1<=tail1)         //队尾出队 
		      tail1--;
		p1[++tail1]=p[i].x;q1[tail1]=p[i].y;           //队尾入队
		while(q2[tail2]>=p[i].y&&head2<=tail2)         //队尾出队
		      tail2--;
		p2[++tail2]=p[i].x;q2[tail2]=p[i].y;           //队尾入队
		if((q1[head1]-q2[head2])>=D) return 1; 
	}
	return 0;
}
bool cmp(WATER a,WATER b){
	return a.x<b.x;
}
int main(){
	scanf("%d%d",&n,&D);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&p[i].x,&p[i].y);
	l=0,r=1000010;
	sort(p+1,p+n+1,cmp);                //按x大小由小到大排序 
	while(l<=r){                        //二分区间长度 
		int mid=(l+r)/2;
		if(check(mid)){                //检验 
			r=mid-1;
			ans=min(ans,mid);
		}
		else l=mid+1;
	}
	if(ans==2100000000) printf("-1");
	else printf("%d",ans);
	return 0;
}
```



---

## 作者：Created_equal1 (赞：8)

首先，很显然，这题的答案满足单调性。。自然想到用二分答案

然后设当前二分的答案为W，验证只需要维护一个长度为W+1的滑动窗口即可（雨滴高度的最大值和最小值）。维护滑动窗口自然是使用单调队列。


```cpp


#include <deque>
#include <cstdio>
#include <algorithm>

using namespace std;

const size_t Max_N(100050);

void Get_Val(int &Ret)
{
    Ret = 0;
    char ch;
    while ((ch = getchar()), (ch > '9' || ch < '0'))
        ;
    do
    {
        (Ret *= 10) += ch - '0';
    }
    while ((ch = getchar()), (ch >= '0' && ch <= '9'));
}

struct rain
{
    int High;
    int Location;
};
inline
bool comp(const rain &a, const rain &b)
{
    return a.Location < b.Location;
}

struct node
{
    node(const int &a = 0, const int &b = 0) : Location(a), Time(b) {}
    int Location;
    int Time;
};

int N;
int D;
rain Value[Max_N];

void init()
{
    Get_Val(N), Get_Val(D);
    for (int i = 1;i <= N;++i)
        Get_Val(Value[i].Location), Get_Val(Value[i].High);
    sort(Value + 1, Value + 1 + N, comp);
}

bool check(const int &W)
{
    int Ret(0);
    deque<node> Min, Max;
    for (int i = 1;i <= N;++i)
    {
        while (!Min.empty() && Min.back().Time >= Value[i].High)
            Min.pop_back();
        Min.push_back(node(Value[i].Location, Value[i].High));
        while (Min.front().Location < Value[i].Location - W)
            Min.pop_front();
        
        while (!Max.empty() && Max.back().Time <= Value[i].High)
            Max.pop_back();
        Max.push_back(node(Value[i].Location, Value[i].High));
        while (Max.front().Location < Value[i].Location - W)
            Max.pop_front();
        Ret = max(Ret, Max.front().Time - Min.front().Time);
    }
    return Ret >= D;
}

int main()
{
    init();
    
    int l(1), r(1000001), mid;
    if (!check(r))
    {
        printf("-1");
        return 0;
    }
    while (l < r)
    {
        mid = l + ((r - l) >> 1);
        if (check(mid))
            r = mid;
        else
            l = mid + 1;
    }
    printf("%d", l);
    
    return 0;
}

```

---

## 作者：ljc_txwd (赞：7)

  萌新第一次发布题解，如果有错误还请大佬指正2333。
  我是用单调队列做的。
  首先，我们不妨假设是一个单调递增或单调递减的队列。
  我个人先假设为单调递增的序列。
  按照横坐标顺序从小到大排个序。
  那么则有x1<x2<x3.....<xn.
  设单调递增队列为s。(横纵坐标用大写的X,Y来表示)。
  那么队列s中的元素则有
  X1<X2....<Xm，Y1<Y2<Y3.....<Ym。
  则有(当Ym-Y1>=规定值)时
  至少有一个解在其中。但是不排除{Ym-Yk>=规定值（1<k<=m）}这种情况
  因为有X1<X2....<Xm，所以Xm-Xk<Xm-X1.
  因此，我们要从s1开始找,直到Ym-Yk<规定值的时候。
  但是，又出现了一个问题：在我们维护单调递增队列的时候可能会出现一个点的坐标，我们在这里不妨把它设为（x,y）。当y<Ym时,我们会向队列中删除点来为它找到合适的位置,因此当Ym-y>=规定值时，这里的差值可能会是最小的，我们就会出现漏洞。
  为了针对这个问题，我在只是用单调递增队列的基础上加入了单调递减队列，于是问题就解决了。
  这里附上萌新的代码：
  ```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int x,y;
}a[100001];
node rise[100000],reduce[100000];
int n,fuck;
bool comp1(node x,node y)
{
	return x.x<y.x;
}
int main()
{
	cin>>n>>fuck;
	int m1=0,m2=9999999;
	for(int i=1;i<=n;++i)
	{
		cin>>a[i].x>>a[i].y;
		if(a[i].y>m1) m1=a[i].y;
		if(a[i].y<m2) m2=a[i].y;
	}
	if(m1-m2<fuck)
	{
		cout<<-1<<endl;
		return 0;
	}
	sort(a+1,a+1+n,comp1);
	int now1=0,m=9999999,now2=0;
	reduce[now2].y=9999999;
	for(int i=1;i<=n;++i)
	{
		if(a[i].y>=rise[now1].y)
		{
			rise[++now1].y=a[i].y;
			rise[now1].x=a[i].x;
		}
		else
		{
			while(a[i].y<=rise[now1].y)
			{
				now1--;
			}
			rise[++now1].x=a[i].x;
			rise[now1].y=a[i].y;
		}
		if(rise[now1].y-rise[1].y>=fuck)
		{
			for(int i=1;i<=now1;++i)
			{
				if(rise[now1].y-rise[i].y>=fuck)
				{
					if(rise[now1].x-rise[i].x<m) m=rise[now1].x-rise[i].x;
				}
				else break;
			}
		}
		if(reduce[now2].y>=a[i].y)
		{
			reduce[++now2].y=a[i].y;
			reduce[now2].x=a[i].x;
		}
		else
		{
			while(reduce[now2].y<=a[i].y)
			{
				now2--;
			}
			reduce[++now2].y=a[i].y;
			reduce[now2].x=a[i].x;
		}
		if(reduce[1].y-reduce[now2].y>=fuck)
		{
			for(int i=1;i<=now2;++i)
			{
				if(reduce[1].y-reduce[i].y>=fuck)
				{
					if(reduce[1].x-reduce[i].x<m) m=reduce[i].x-reduce[1].x;
				}
			}
		}
	}
	cout<<m<<endl;
	return 0;
}
```


萌新第一次交题解，请管理员大佬通过，2333.
谢谢。

---

## 作者：y2823774827y (赞：7)

STL大法好 

题目本质就是求一段区域内的点最大高度差满足d

1. 按高度从小到大排序
1. 每次循环先确定能进堆的最高点，然后把<=最高点的高度进堆
1. 两个优先队列,que1表i左边的点,que2表i右边的点,比较左边差
```cpp
# include<cstdio>
# include<queue>
# include<algorithm>
using namespace std;
struct node{
	int x,y;
}a[100001];
int n,d,ans=1000001;
priority_queue<int> que1;
priority_queue<int,vector<int>,greater<int> >que2;
bool sort1(node g1,node g2){
	return g1.y<g2.y;
}
inline int MIN(int g1,int g2){
	return g1<=g2?g1:g2;
}
int main(){
	scanf("%d%d",&n,&d);
	for(int i=1;i<=n;++i)
		scanf("%d%d",&a[i].x,&a[i].y);
	sort(a+1,a+1+n,sort1);//按高度排序
	int j=1;
	for(int i=2;i<=n;++i){
		int down=a[i].y-d; 
		while(a[j].y<=down){
			que1.push(a[j].x);
			++j;
		}//进堆 
		if(!que1.empty()){
		    while(que1.top()>a[i].x){
			    que2.push(que1.top());
			    que1.pop();
			    if(que1.empty()) break;
		    }
		}//
		if(!que2.empty()){
			while(que2.top()<a[i].x){
				que1.push(que2.top());
				que2.pop();
				if(que2.empty()) break;
			}
		}//
		if(!que1.empty())
			ans=MIN(ans,a[i].x-que1.top());//左边距离 
		if(!que2.empty())
		    ans=MIN(ans,que2.top()-a[i].x);//右边距离 
    }
    if(ans<1000001) printf("%d",ans);
    else printf("-1");
    return 0;
}
```

---

## 作者：米奇 (赞：4)

## 算法:**区间伸缩**+**线段树优化**

#### 时间复杂度:$O(nlogn)$

### 首先介绍一下**区间伸缩**

用两个变量$l$和$r$来枚举区间

如果$l$到$r$的区间不满足要求,$r$++

如果$l$到$r$的区间满足要求,记录答案,$l$++

#### 所以区间伸缩是$O(n)$的

如果有不会区间伸缩的可以做一下P1638逛画展

### 再来介绍一下线段树

线段树可以维护区间最大(小)值

建树$O(n)$ , 查询$O(logn)$

### 这题我们可以用区间伸缩枚举区间,用线段树来判断区间是否合法

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
    int x,y;
};
struct tr{
	int maxx,minn;
};
tr tree[4000005];
int n,m,u,v,ans,l,r;
node a[1000005];
bool cmp(node a,node b)
{
    if(a.x==b.x) return a.y<b.y;
    return a.x<b.x;
}
void build(int nod,int l,int r)//线段树建树
{ 
	if(l==r)
	{
		tree[nod].minn=a[l].y;
		tree[nod].maxx=a[l].y;
		return;
	}
	int mid=(l+r)/2;
	build(nod*2,l,mid);
	build(nod*2+1,mid+1,r);
	tree[nod].minn=min(tree[nod*2].minn,tree[nod*2+1].minn);
	tree[nod].maxx=max(tree[nod*2].maxx,tree[nod*2+1].maxx);
}
int findmaxx(int nod,int l,int r,int ll,int rr)//查询区间max
{
	if(l==ll&&r==rr) return tree[nod].maxx;
	int mid=(l+r)/2;
	if(rr<=mid) return findmaxx(nod*2,l,mid,ll,rr);
	else if(ll>mid) return findmaxx(nod*2+1,mid+1,r,ll,rr);
	else return max(findmaxx(nod*2,l,mid,ll,mid),findmaxx(nod*2+1,mid+1,r,mid+1,rr));
}
int findminn(int nod,int l,int r,int ll,int rr)//查询区间min
{
	if(l==ll&&r==rr) return tree[nod].minn;
	int mid=(l+r)/2;
	if(rr<=mid) return findminn(nod*2,l,mid,ll,rr);
	else if(ll>mid) return findminn(nod*2+1,mid+1,r,ll,rr);
	else return min(findminn(nod*2,l,mid,ll,mid),findminn(nod*2+1,mid+1,r,mid+1,rr));
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d%d",&a[i].x,&a[i].y);
    sort(a+1,a+n+1,cmp);//以x轴排序
    build(1,1,n);
    l=1;r=1;ans=100000000;
    for(int i=2;i<=n;i++)
        if(a[i].x==a[1].x)r++;//把x轴相同的点一加入
        else break;
    while(l<=r && r<=n)
 	{
        if(findmaxx(1,1,n,l,r)-findminn(1,1,n,l,r)>=m)//满足条件
        {
            if(a[r].x-a[l].x<ans) ans=a[r].x-a[l].x;//更新答案
            l++;
            if(l>n) break;//注意边界
            while(a[l].x==a[l-1].x)
			{
				l++;
				if(l>n) break;//注意边界
			} 
        }
        else{//不满足条件
            r++;
            if(r>n) break;//注意边界
            while(a[r+1].x==a[r].x)
			{
				r++;
				if(r>n) break;//注意边界
			}
        }
    }
    if(ans==100000000) cout<<-1<<endl;
    else printf("%d",ans);
    return 0;
}
```

---

## 作者：Xie_BR (赞：3)

这道题不要被蓝色的标签所误导，其实蛮好想的。。。  
## 单调队列  
# o（n）的复杂度  
首先我们创建一个结构体，表示坐标（大部分都想得到）  
其次我们需要对其排序，将横坐标x小的放在前面  
至于之后的操作，我们就一起来看看代码吧~~~  
# AC代码：  

```cpp
#include<bits/stdc++.h>
#define int long long
#define MK 10000010
using namespace std;
int n,d;

struct node
{
	int x,y;
}e[MK],f[MK];

int cmp(node a,node b)
{
	return a.x < b.x;
}

signed main()
{
	scanf("%lld%lld",&n,&d);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&e[i].x,&e[i].y);
	}
	sort(e+1,e+n+1,cmp);
	int str = 1;
	int end = 1;
	int j = 2;
	int minx = LLONG_MAX;
	f[1] = e[1];
	while(j<=n)
	{
		while((f[end].y > e[j].y) && (end>=str))
		{
			end--;
		}
		end++;
		f[end] = e[j];
		while((end>=str) && (f[end].y-f[str].y>=d))
		{
			minx = min(minx,f[end].x-f[str].x);
			str++;
		}
		j++;
	}
	if(minx==LLONG_MAX)
	{
		printf("-1\n");
	}else
	{
		printf("%lld\n",minx);
	}
	return 0;
}
```
# ：）

---

## 作者：pluszero (赞：3)

直接的单调队列，可以O(n)完成。数据很水，只需要从小到大算一次就能过，正解是要从大到小再算一次。





```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstdio>
using namespace std;
struct test
{
    int x,y;
}a[100001],f[1000001];
bool cmp(test a,test b)
{
    return a.x<b.x;
}
int main()
{
    int n,d;
    scanf("%d %d",&n,&d);
    for(int i=1;i<=n;i++) 
    {
        scanf("%d %d",&a[i].x,&a[i].y);
    }
    sort(a+1,a+1+n,cmp);
    int head=1,tail=1,j=2,minn=0X3f3f3f3f;
    f[1]=a[1];
    while(j<=n)
    {
        while((f[tail].y>a[j].y)&&(tail>=head)) tail--;
        tail++;f[tail]=a[j];
        while((tail>=head)&&(f[tail].y-f[head].y>=d))
        {
            minn=min(minn,f[tail].x-f[head].x);
            head++;
        }
        j++;
    }
    if(minn==0X3f3f3f3f) printf("-1");
    else printf("%d\n",minn);
    return 0;
}
```

---

## 作者：zeng_yirong (赞：2)

# ****二分答案+单调队列****

这题用二分答案+单调队列最合适了。

1. 输入时可以记录最值，用以确定边界与特判，排序以维护第 一关键字x坐标。

2. 二分答案，注意边界。
 
3. 关于check()函数，由于满足条件的水滴可以是左边高度大于右边，也可以是右边大于左边，所以这里维护了单调递增与递减两个单调队列，只要其中一个队列在遍历过程中满足高度差大于或等于d,即为满足条件的。
 
4.  复杂度为O(nlog(n) )

## 代码实现


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
typedef long long ll;
int q[maxn] ;//单调队列 
int n,d;
int x_min=1e6,x_max=0,h_min=1e6,h_max=0;//最值初始化 
struct node{
	int x,h;
	friend bool operator < (node a,node b){
		return a.x <b.x;
	}
}ar[maxn];
bool check(int mid){  //单调队列判断  
	memset(q,0,sizeof(q) );
	int h=1,t=0 ;
	for(int i=1;i<=n;i++){
		while(h<=t&&ar[i].x-ar[q[h]].x>mid)	h++;
		while(h<=t&&ar[i].h>ar[q[t]].h) t--;  //维护递减单调队列 
		q[++t]=i;
		if(ar[q[h]].h-ar[q[t]].h>=d)  //是否符合判断  
			return 1;
	}
	memset(q,0,sizeof(q) );
	h=1,t=0 ;
	for(int i=1;i<=n;i++){
		while(h<=t&&ar[i].x-ar[q[h]].x>mid)	h++;
		while(h<=t&&ar[i].h<ar[q[t]].h) t--;//维护递增单调队列 
		q[++t]=i;
		if(ar[q[t]].h-ar[q[h]].h>=d)  //是否符合判断 
			return 1;
	}
	return 0;
}
int main(){
	ios::sync_with_stdio(false); cin.tie(0);cout.tie(0);
	cin>>n>>d;
	for(int i=1;i<=n;i++){
		cin>>ar[i].x>>ar[i].h;
		if(ar[i].x>x_max) x_max=ar[i].x;//获取最值 
		if(ar[i].x<x_min) x_min=ar[i].x;
		if(h_min>ar[i].h) h_min=ar[i].h ;
		if(ar[i].h>h_max) h_max=ar[i].h;
	}sort(ar+1,ar+1+n );  //排序以维护第一关键字x 
	if(h_max-h_min<d) {  //是否可行特判 
		cout<<-1<<endl;
		return 0;
	}
	int low=0,high=x_max-x_min+1;  //上下边界 
	while(low<high){
		int mid=(low+high)/2;
		if(check(mid) ) high=mid;
		else low=mid+1;
	}cout<<high<<endl;
	return 0;
}
```


---

## 作者：Plozia (赞：1)

宣传博客：[link](https://blog.csdn.net/BWzhuzehao/article/details/109632180)

本题题意简单明了。

首先，题目当中 **最小** 二字，就是在提示我们使用二分。

然后，要求最大值与最小值的差，并且区间长度固定，各位能想到什么？我想到的是使用单调队列维护。

做法：
1. 首先对输入数组按照 $x$ 坐标升序排序。
2. 然后二分花盆长度，跑一次单调队列即可。

所以结束了？代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN=1e5+10;
int n,d;
struct node
{
	int x,y;
}a[MAXN];

int read()
{
	int fh=1,sum=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		sum=(sum<<3)+(sum<<1)+ch-'0';
		ch=getchar();
	}
	return sum*fh;
}

bool cmp(const node &fir,const node &sec)
{
	return fir.x<sec.x;
}

bool check(int k)
{
	deque<int>qmax,qmin;
	for(int i=1;i<=n;i++)
	{
		while(!qmax.empty()&&a[i].x-a[qmax.front()].x>k) qmax.pop_front();
		while(!qmin.empty()&&a[i].x-a[qmin.front()].x>k) qmin.pop_front();
		while(!qmax.empty()&&a[i].y>=a[qmax.back()].y) qmax.pop_back();
		while(!qmin.empty()&&a[i].y<=a[qmin.back()].y) qmin.pop_back();
		qmax.push_back(i),qmin.push_back(i);
		if(a[qmax.front()].y-a[qmin.front()].y>=d) return 1;
	}
	return 0;
}

int main()
{
	n=read();d=read();
	for(int i=1;i<=n;i++) {a[i].x=read();a[i].y=read();}
	sort(a+1,a+n+1,cmp);
	int l=1,r=1000000,ans=-1;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid))
		{
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：高天 (赞：1)

```cpp
#include<bits/stdc++.h>//万能脑袋 
using namespace std;
int n, d;
struct point {
	int x, y;
} a[100005];//自定义结构体 坐标 
struct node {
	int val, pos;
};//自定义结构体 
bool check(int w) {
	deque<node> dq;
	for(int i = 1; i <= n; i++) {
		while(dq.empty() == false && dq.back().val >= a[i].y) { //最小值
			dq.pop_back();
		}
		node cur = {a[i].y, a[i].x};
		dq.push_back(cur);
		while(dq.front().pos + w < a[i].x) {
			dq.pop_front();//弹出队首 
		}
		if(abs(a[i].y - dq.front().val) >= d)//记得取绝对值 
			return true;//满足题意，弹出 
	}
	return false;
}
bool cmp(point p1, point p2) {
	if(p1.x == p2.x)
		return p1.y < p2.y;
	return p1.x < p2.x;
}//自定义排序函数 
int main() {
	cin >> n >> d;
	int maxi = 0;
	for(int i = 1; i <= n; i++) {
		cin >> a[i].x >> a[i].y;
		maxi = max(maxi, a[i].x); //最大的横坐标
	}
	sort(a, a + n + 1, cmp); //按横坐标排序
	int left = 0, right = maxi + 1;
	while(left + 1 < right) { //二分宽度
		int mid = left + (right - left) / 2;
		if(check(mid) == true) { //能够找到两滴水的高度差大于等于d
			right = mid;
		} else {
			left = mid;
		}
	}
	if(right == maxi + 1) { //如果右边界没有移动过，说明花盆始终太小
		cout << -1;
		return 0;
	}
	cout << right;
	return 0;
}
```


---

## 作者：Bosun (赞：1)

因为答案满足单调性，所以我们可以二分答案（设为x）。

然后转化题意：按x轴排序，如果对于某个点(u,v)，(u-x~u,...)的区间内的点的极差>=d,则符合条件。求定长区间极差，即使用两个单调队列，一个单调升，一个单调降，每次将两队头取出判断即可。

清真code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100001;
int n,d;
int q1[N],q2[N];
struct node{
	int x,y;
}a[N];
int cmp(node u,node v){
	return u.x<v.x;
}
int check(int x){
	int i,j;
	memset(q1,0,sizeof(q1));
	memset(q2,0,sizeof(q2));
	int h1=1,t1=0,h2=1,t2=0;
	for(i=1;i<=n;i++){
		while(h1<=t1&&a[q1[h1]].x<a[i].x-x)h1++;
		while(h2<=t2&&a[q2[h2]].x<a[i].x-x)h2++;
		while(h1<=t1&&a[i].y<a[q1[t1]].y)t1--;
		q1[++t1]=i;
		while(h2<=t2&&a[i].y>a[q2[t2]].y)t2--;
		q2[++t2]=i;
		if(a[q2[h2]].y-a[q1[h1]].y>=d)return 1;
	}
	return 0;
}
int main(){
	int i;
	cin>>n>>d;
	for(i=1;i<=n;i++)scanf("%d%d",&a[i].x,&a[i].y);
	sort(a+1,a+n+1,cmp);
	int l=1,r=1e6,ans=-1;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	cout<<ans<<endl;
	return 0;
} 
```


---

## 作者：KKKKK_ON (赞：1)

晚上做题脑子有点糊，就只想了个主席树暴力，菜爆了

首先对 $x,y$ 离散化，然后对点按 $y$ 排序，相当于按 $y$ 坐标映射到了点$[1,n]$ 上，然后建主席树。

因为花盆放置的两端必定是节点在坐标轴上对应的点，所以，我们枚举当前的左端点是第 $i$ 个节点对应的高度 $y_i$
。每次找到 $y_i+D$ 对应的位置，记为 $l$，这一步可以用一个不减的变量往后扫即可。

那么现在要做的就是求 $[l,n]$ 区间内的点的 $x$ 坐标离当前的 $x_i$ 最近的距离。那么直接二分一下当前点在主席树上是第几大即可。

时间复杂度: $O(nlog^2(n))$ 

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
int Gcd(int a,int b){if (b == 0) return a; return Gcd(b , a%b);}
int Lcm(int a, int b){ return a/Gcd(a,b)*b;}
template <class T>
void read(T &x) {
	static char ch;
	static bool neg;
	for(ch = neg = 0; ch < '0' || '9' < ch; neg |= ch == '-', ch = getchar());
	for(x = 0; '0' <= ch && ch <= '9'; (x *= 10) += ch - '0', ch = getchar());
	x = neg ? -x : x;
}
const int maxn = 1e5 + 10;
int nodeNumber;
int n,m;
int sum[maxn<<5],lch[maxn<<5],rch[maxn<<5],root[maxn];
int xx[maxn],yy[maxn];
struct node{int x,y;} p[maxn];
int cmp(node a,node b){return a.y < b.y;};
void build(int &id,int l,int r){
    id = ++nodeNumber;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(lch[id],l,mid);
    build(rch[id],mid+1,r);
}
int modify(int pre,int l,int r,int rev){
    int now = nodeNumber++;
    lch[now] = lch[pre];rch[now] = rch[pre]; sum[now] = sum[pre] + 1;
    if (l == r) return now;
    int mid = (l + r) >> 1;
    if (rev <= mid) lch[now] = modify(lch[pre],l,mid,rev);
    else rch[now] = modify(rch[now],mid+1,r,rev);
    return now; 
}
int query(int pre,int now,int l,int r,int k){
    int ans,mid = (l + r) >> 1,x = sum[lch[now]]-sum[lch[pre]];
    if (l == r) return l;
    if (x >= k) ans = query(lch[pre],lch[now],l,mid,k);
    else ans = query(rch[pre],rch[now],mid+1,r,k-x);
    return ans;
}
int query_min(int L,int R,int len,int pos){
	if (L >= R) return INT_MAX;
	int l = 1,r = R - L + 1;
	while(l < r){
		int mid = (l + r) >> 1;
		if (query(root[L-1],root[R],1,len,mid) >= pos) r = mid;
		else l = mid + 1;
	}
	int id2 = query(root[L-1],root[R],1,len,l);
	int id1 = pos;
	int ans = abs(xx[id1]-xx[id2]);
	return ans;
}
int main(){
	int n,D;
	read(n); read(D);
	for(int i=1; i<=n; i++){
		read(p[i].x);
		read(p[i].y);
		xx[i] = p[i].x;
		yy[i] = p[i].y;
	}
	sort(p+1,p+n+1,cmp);
	sort(xx+1,xx+n+1);
	sort(yy+1,yy+n+1);
	int len1 = unique(xx+1,xx+n+1) - xx - 1;	
	int len2 = unique(yy+1,yy+n+1) - yy - 1;
	build(root[0],1,len1);
	for(int i=1; i<=n; i++){
		int pos = lower_bound(xx+1,xx+len1+1,p[i].x) - xx;
		root[i] = modify(root[i-1],1,len1,pos);
	}
	int ans = INT_MAX,l = 1;
	for(int i=1; i<=n; i++){
		while(p[l].y < p[i].y+D && l <= n) l++;
		int pos = lower_bound(xx+1,xx+len1+1,p[i].x) - xx;
		int res = query_min(l,n,len1,pos);
		ans = min(ans,res);			
	}	
	if (ans == INT_MAX) cout << -1 << endl;
	else cout << ans << endl;
	return 0;
}
```


---

## 作者：registerGen (赞：1)

# Solution

显然可以二分答案（即二分花盆宽度）。

然后我们要做的事情就是判定宽度 $k$ 是不是一个合法的宽度。

如果是合法的，只需找出一个长度为 $k$ 的区间，使得 横坐标在这个区间内的点 的 最大纵坐标减最小纵坐标 $\ge d$。否则不合法。

然后就是一个裸的滑动窗口了。

记得一开始要把所有点按横坐标从小到大排个序。

时间复杂度 $O(n\log(\max y))$。

# Code

```cpp
#include<cstdio>
#include<algorithm>
#include<deque>

const int N=1e5;

struct Point
{
	int x,y;

	inline bool operator<(const Point& rhs)const
	{
		return x<rhs.x;
	}
};

int n,d;
Point p[N+10];

inline bool check(int k)
{
	std::deque<int> qmin,qmax; // 两个单调队列
	for(int i=1;i<=n;i++)
	{
		// 以下是单调队列标准操作
		int maxx=-0x3f3f3f3f,minn=0x3f3f3f3f;
		while(!qmin.empty()&&p[qmin.back()].y>p[i].y)qmin.pop_back();
		qmin.push_back(i);
		if(p[i].x>=k)
		{
			while(!qmin.empty()&&p[qmin.front()].x<p[i].x-k)qmin.pop_front();
			minn=p[qmin.front()].y;
		}
		while(!qmax.empty()&&p[qmax.back()].y<p[i].y)qmax.pop_back();
		qmax.push_back(i);
		if(p[i].x>=k)
		{
			while(!qmax.empty()&&p[qmax.front()].x<p[i].x-k)qmax.pop_front();
			maxx=p[qmax.front()].y;
		}
		// 以上是单调队列标准操作
		if(maxx-minn>=d)return 1; // 找到了就直接返回 true
	}
	return 0; // 没找到，返回 false
}

int main()
{
	scanf("%d%d",&n,&d);
	int l=0,r=0,ans=-1;
	for(int i=1;i<=n;i++)
		scanf("%d%d",&p[i].x,&p[i].y),r=std::max(r,p[i].x);
	std::sort(p+1,p+n+1);
	while(l<=r) // 二分答案模板
	{
		int mid=(l+r)>>1;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：QMQMQM4 (赞：1)

# 题解 p2698

### 算法

单调队列加 two pointer

### 分析

题目首先应先按照x的坐标排序，把花盆看做是滑动窗口，维护区间内的最大与最小值，并用单调队列维护。

### 代码
```
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;

const int maxn = 1e6+5;
int q1[maxn],q2[maxn],p1[maxn],p2[maxn],head1,tail1,head2,tail2,n,d,ans;
//q1维护最大值，q2维护最小值
struct hp
{
	int l,r;
}a[maxn];

bool cmp(hp a,hp b)
{
	return a.l<b.l;
}

int main()
{
	ans = 0x3f3f3f;
	scanf("%d%d",&n,&d);
	for(int i = 1;i<=n;++i)
		scanf("%d %d",&a[i].l,&a[i].r);
	sort(a+1,a+1+n,cmp);
	head1 = head2 = 1;
	tail1 = tail2 = 0;
	for(int i = 1,j = 0;i<=n;++i)
	{
		while(head1<=tail1&&p1[head1]<i)
			head1 ++;
		while(head2<=tail2&&p2[head2]<i)
			head2 ++;
		while(/*head1<=tail1&&head2<=tail2&&*/q1[head1]-q2[head2]<d&&j<n)
		{
			j ++;
			while(head1<=tail1&&q1[tail1]<a[j].r)
				tail1--;
			//puts("-1");
			q1[++tail1] = a[j].r;
			p1[tail1] = j;
			while(head2<=tail2&&q2[tail2]>a[j].r)
				tail2--;
			q2[++tail2] = a[j].r;
			p2[tail2] = j;
		}
		//printf("%d %d %d %d\n",j,i,a[j].l-a[i].l+1,q1[head1]-q2[head2]);
		if(q1[head1]-q2[head2]>=d)
			ans = min(ans,a[j].l-a[i].l);
	}
	if(ans == 0x3f3f3f)
		printf("-1");
	else
		printf("%d",ans);
	return 0;
}
```










---

## 作者：Katoumegumi (赞：1)

发一篇看上去很厉害但其实没啥大不了的题解:$zkw......$

拿到这道题还是比较显然的想到了二分答案吧,因为题意也很清楚,希望求出一个最值,满足一定条件,而且这个最值是有明确的上下界的,且答案也满足单调性.

关键就是这个验证要怎么写.这个验证的写法也很好想到,就直接按他题目要求的来,求出一个区间$[l,r]$中的$max$,$min$,看他们的差是否大于$D$就行了.维护区间最小最大的方法多了去了,$RMQ$,单调队列$......$以及线段树.实际上线段树在这道题里时间复杂度有点悬,$O(Nlog^2 N)$,有接近四千万.但是你写点玄学线段树比如$zkw$就可以玄玄的卡过去了,再加个$fread$读优,快得飞起$......$

还有要注意,$zkw$时$M$(最底层叶节点个数)的值显然应该用$while(M<=1e6)M<<1$来赋值,习惯性用$n$来就爆定了$......$

(ps:注意判无解的情况啊)

$code:$
```c++
#include<stdio.h>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#define l(x) x<<1
#define r(x) x<<1|1
#define ll long long
using namespace std;

const int maxx=4*(1e6+5);
char buf[1<<20],*p1,*p2; 
inline char gc() 
{ 
//    return getchar(); 
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin))==p1?0:*p1++; 
} 

template<typename T> 
inline void read(T &x) 
{ 
    char tt; 
    while(!isdigit(tt=gc()));x=tt-'0'; 
    while(isdigit(tt=gc())) x=x*10+tt-'0'; 
}

int n,m,M=1,top,low=1e6;
int maxn[maxx],minn[maxx];

int querymax(int x,int y)
{
	int ans=-1;
	for(x+=M-1,y+=M+1;x^y^1;x>>=1,y>>=1)
	{
		if(~x&1) ans=max(ans,maxn[x^1]);
		if(y&1) ans=max(ans,maxn[y^1]);
	}
	return ans;
}

int querymin(int x,int y) {
    int ans=1e9;
    for(x+=M-1,y+=M+1; x^y^1; x>>=1,y>>=1) {
        if(~x&1) ans=min(ans,minn[x^1]);
        if(y&1) ans=min(ans,minn[y^1]);
    }
    return ans;
}

bool ok(int len)
{
	for(int l=low;l<=top;l++)
	{
		int r=l+len-1;
		if(r>top) continue;
		if(querymax(l,r)-querymin(l,r)>=m) return 1;
	}
	return 0;
}

int main(){
	memset(maxn,-1,sizeof(maxn));
	memset(minn,30,sizeof(minn));
	read(n),read(m);
	while(M<=1e6)M<<=1;
	for(int i=1;i<=n;i++)
	{
		int x,y;
		read(x),read(y);
		maxn[x+M]=max(maxn[x+M],y);
		minn[x+M]=min(minn[x+M],y);
		top=max(top,x);
		low=min(low,x);
	}
	for(int i=M-1;i>=1;i--)
	{
		maxn[i]=max(maxn[l(i)],maxn[r(i)]);
		minn[i]=min(minn[l(i)],minn[r(i)]);
	}
	int l=1,r=top;
	while(l<=r)
	{
		int mid=l+r>>1;
		if(ok(mid)) r=mid-1;
		else l=mid+1;
	}
	if(r>top-low) puts("-1");
	else printf("%d",r);
}

```


---

## 作者：magolor (赞：1)

二分答案加上单调队列，因为是1000000的xy，所以不需要离散化，代码写的略长但是比较整齐、逻辑清楚，更容易理解单调队列的工作原理。注意一下二分写法。







    
            
```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
#define MAXN 1000000
#define mid ((L+R)>>1)
int N,D,L,R,mx;
int maxt[MAXN+5], mint[MAXN+5], maxi[MAXN+5], mini[MAXN+5]; 
bool Check(int w)
{ 
    for(int i = 0, maxi_head = 0, maxi_tail = 0, mini_head = 0, mini_tail = 0; i <= mx; i++)
        if(maxt[i]+1)
        {
            while(maxi_head < maxi_tail && i-maxi[maxi_head] > w)
                maxi_head++;
            while(mini_head < mini_tail && i-mini[mini_head] > w)
                mini_head++;
            while(maxi_head < maxi_tail && maxt[i] >= maxt[maxi[maxi_tail-1]])
                maxi_tail--; 
            while(mini_head < mini_tail && mint[i] <= mint[mini[mini_tail-1]])
                mini_tail--;
            maxi[maxi_tail++] = i, mini[mini_tail++] = i;
            if(maxt[maxi[maxi_head]]-mint[mini[mini_head]] >= D)
                return true;
        }
    return false;
} 
int main()
{
    memset(maxt,-1,sizeof(maxt)), memset(mint,-1,sizeof(maxt));
    scanf("%d%d",&N,&D);
    for(int i = 1, a, b; i <= N; i++) 
    {
        scanf("%d%d",&a,&b), mx = max(mx,b);
        if(maxt[a] == -1)
            maxt[a] = mint[a] = b;
        else if(b > maxt[a])
            maxt[a] = b;
        else if(b < mint[a])
            mint[a] = b;
    }
    for(L = 1, R = mx+1; L < R; )
        if(Check(mid))
            R = mid;
        else 
            L = mid+1;
    printf("%d\n",(R==mx+1 ? -1 : R)); 
    return 0;
}

```

---

## 作者：newbie666 (赞：0)

这道题首先可以来个朴素的暴力来枚举花盆的宽度，位置，时间复杂度$O(n*x)$,

但是数据限制的原因，是$O(1e10)$，所以就是说这个方法行不通.

### 接下来，才真正的开始.
枚举花盆长度，我们不就很容易地想到二分答案吗！！！再来看一下，花盆的长度

是单调的，正好符合二分的条件，所以时间复杂度一下就变成了$log$级别，但是还

是$TLE$(无语)我们再来用单调队列来维护实现一下,如果单调队列都不会的$OIer$，就去

看一下 [滑动窗口/单调队列](https://www.luogu.com.cn/problem/P1886) 吧！

首先从左到右滑动正在的区间

用单调队列来维护区间内的最大值和最小值，再作差即可.

### 代码如下，请勿$copy$：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int SIZE=1e5+5;
struct input{
	int x,y;
};
input a[SIZE];
struct Node{
	int val,pos;
};
int n,d,max_len,ans;
inline int read(){ //快读 
	int x=0;bool t=false;char ch=getchar();
	while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
	if(ch=='-') t=true,ch=getchar();
	while(ch<='9'&&ch>='0') x=x*10+ch-48,ch=getchar();
	return t?-x:x;
}

bool cmp(input a,input b){
	if(a.x==b.x) return a.y<b.y;
	else return a.x<b.x;
}

bool check(int w){
	deque<Node> dqmin; //双端队列 
	deque<Node> dqmax;
	for(int i=1;i<=n;i++){
		
		while(!dqmin.empty()&&dqmin.back().val>=a[i].y) dqmin.pop_back(); //最小值 
		Node curmin={a[i].y,a[i].x};
		dqmin.push_back(curmin);
		while(!dqmin.empty()&&dqmin.front().pos+w<a[i].x) dqmin.pop_front();
		
		
		while(!dqmax.empty()&&dqmax.back().val<=a[i].y) dqmax.pop_back(); //最大值 
		Node curmax={a[i].y,a[i].x};
		dqmax.push_back(curmax);
		while(!dqmax.empty()&&dqmax.front().pos+w<a[i].x) dqmax.pop_front();
		
		
		if(dqmax.front().val-dqmin.front().val>=d) return true; //做差 
	}
	return false;
}
int main(){
	n=read(),d=read();
	for(int i=1;i<=n;i++){
		a[i].x=read(),a[i].y=read();
		max_len=max(max_len,a[i].x); //最大的横坐标 
	}
	
	sort(1+a,1+a+n,cmp); //按横坐标排序 
	
	int left=0,right=max_len+1;
	while(left+1<right){ //二分宽度 
		int mid=(left+right)>>1;
		if(check(mid)){ //能够找到两滴水的高度差大于等于d 
			right=mid;
		}
		else{
			left=mid;
		}
	}
	
	if(right==max_len+1){ //如果右边界没有移动过，说明花盆始终太小，所以直接输出-1 
		cout<<-1<<'\n';
		return 0;
	}
	cout<<right<<'\n';
	return 0;
}
```
不喜勿喷~~~

---

## 作者：little_cindy (赞：0)

[$\color{black}\textbf{\large 题目传送门}$](https://www.luogu.com.cn/problem/P2698)

首先，我就想到一个方法——暴力枚举

**方法一**：暴力枚举

**思路**：

首先枚举花盆的长度，再枚举花盆摆放的位置。

可是仔细一算，时间复杂度为 $O((max(x)-min(x))·n)$

而在最坏的情况下，时间复杂度为 $O(1e11)$

保证获得 $\color{white}\colorbox{purple}{\textsf{TLE}}$

果断放弃。

**方法二**：单调队列+二分答案（算法标签啊！）

**思路**：

首先我们需要知道，二分什么？

|  二分的东西  |原因|
|:-:|:-:|
|花盆摆放的位置|不行，因为并没有单调性，无法二分。并且你告诉我怎么用单调队列？|
|花盆的长度|可以，因为 $max(x)-min(x)$ 是有单调性的原因：你小号的的花盆接的到的水滴，大号的花盆肯定接的到！|

剩下的不用多想,套上单调队列标准模板,就可以了。

$\colorbox{yellowgreen}{\color{white}\textsf{AC}}$ 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,d;//n,d如题,k为窗口长度
struct Node{
	int x,y;//x,y如题
}a[1000005];
struct node{
	int dis;//高度（y）
	int num;//编号（x）
};
bool check(){
	deque<node> maxq,minq;//maxq记录最大值，minq记录最小值
	for(int i=1;i<=n;i++){
		while(!minq.empty()&&minq.back().dis>=a[i].y){//最大值
			minq.pop_back();
		}
		node cur={a[i].y,a[i].x};
		minq.push_back(cur);
		while(minq.front().num+k<a[i].x){//下面解释
			minq.pop_front();
		}
		while(!maxq.empty()&&maxq.back().dis<=a[i].y){//最小值
			maxq.pop_back();
		}
		maxq.push_back(cur);
		while(maxq.front().num+k<a[i].x){//下面解释
			maxq.pop_front();
		}
		if(maxq.front().dis-minq.front().dis>=d){//如果满足条件
			return 1;//返回1
		}
	}
	return 0;
}
bool cmp(Node a,Node b){//排序方式
	return a.x<b.x;//按x从小到大排序
}
int main(){
	cin>>n>>d;//输入
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y;
	}
	sort(a+1,a+1+n,cmp);//排序
	int l=0,r=1e6+1;//二分模板（其中的一种模板）
	while(l+1<r){
		k=(l+r)/2;
		if(check()){
			r=k;
		}
		else{
			l=k;
		}
	}
	if(r==1e6+1){//如果r没有有变化，就说明没有答案，输出-1
		cout<<-1;
		return 0;
	}
	cout<<r;//输出r
	return 0;
}
```
备注：
1. check函数里单调队列不能分开算，因为你要获取的是同一窗口的最大值。否则会$\color{white}\colorbox{red}{\textsf{WA}}$
2. 因为边缘也可以接水，所以不用 $-1$。

---

## 作者：Forever1507 (赞：0)

# [传送门](https://www.luogu.com.cn/problem/P2698)

看到题马上想到了暴力，枚举花盆长度，再枚举花盆位置，时间复杂度大概是     $O(nX)$（ $X$ 为 $X$ 轴长度），明显 $TLE$ 。

但是每一种算法都是从暴力的基础上转变过来的嘛，我们发现移动花盆的过程类似于移动窗口问题，考虑单调队列，此时时间复杂度降为 $O(n^2)$ ，仍然会 $TLE$ 。

 $1e5$ 的时间复杂度，若想通过只能考虑 $O(nlog_2n)$ ，能考虑的便是二分了，既然要二分，就要找到单调性，可以发现，若满足条件，则边长更大的也能够满足，若当前无法满足，也一定能通过增长边使得条件满足（这里先不考虑输出 $-1$ 的情况）。
 
有了思路，代码坑还是比较多的，坑点请看注释：
```
#include<bits/stdc++.h>//懒人专用万能头
using namespace std;
struct node{
	int x,y;
}a[100005];
bool cmp(node a,node b){
	if(a.x==b.x)return a.y<b.y;
	return a.x<b.x;
}
int n,d;
bool check(int x){
	deque<pair<int,int> >q1/*min*/,q2/*max*/;//懒得再弄一个struct了
	for(int i=1;i<=n;i++){
		while(!q1.empty()&&a[i].y<=q1.back().first)q1.pop_back();
		q1.push_back(make_pair(a[i].y,a[i].x));
		while(q1.front().second+x<a[i].x)q1.pop_front();//按照x轴移动，一次可能弹走多个
		while(!q2.empty()&&a[i].y>=q2.back().first)q2.pop_back();
		q2.push_back(make_pair(a[i].y,a[i].x));//位置是x轴上的值，而不是序号
		while(q2.front().second+x<a[i].x)q2.pop_front();//因为可以包含恰好水滴，不用-1
		if(q2.front().first-q1.front().first>=d)return 1;//满足条件
	}
	return 0;//若循环结束都不满足，那么当前盆长就不行
}
bool flag;
int main(){
	ios::sync_with_stdio(0);//输入输出加速
	cin>>n>>d;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y;
	}
	sort(a+1,a+1+n,cmp);//输入不一定有序，为了单调队列要sort一下
	int l=0,r=a[n].x+1;
	while(l+1<r){//二分答案
		int mid=(l+r)>>1;//小优化，位运算比'/'快
		if(check(mid))r=mid,flag=1;//flag用来特判-1,若一次都没满足就-1
		else l=mid;
	}
	if(flag)
	cout<<r;//求最小值输出right,最大值就是left
	else cout<<-1;
	return 0;
}
```
## [AC记录](https://www.luogu.com.cn/record/46122206)

---

## 作者：小馄饨 (赞：0)

蒟蒻提供一种单调栈中二分的思路，时间复杂度为 $O(n\log n)$。

先按照横坐标从小到大排序，对于每一个点（即题目中的水滴） $P$，我们考虑在 $P$ 左边的所有点中，与 $P$ 纵坐标相差不小于 $d$ 的最近的点是哪一个，并求出它们之间的距离。答案为所有点情况中的最小值。

现在来考虑这一算法的正确性。我们可以很容易地证明，如果一个花盆是最优解，那么它的两端的纵坐标一定是该区间所有点纵坐标中的最值。（否则，将不是最值的一端缩短，得到的新的花盆仍然满足条件且更优）。可以很容易证明按照上述算法找出的花盆一定包括最优解。而唯一需要担心的是我们可能求出了一种情况，它的右端点并不是最值。但是由于右端点和左端点纵坐标的差值绝对值一定小于等于最大值和最小值的差值绝对值，所以这个区间依然合法，对答案没有影响。

如何快速实现？我们可以将符合条件的点一分为二：纵坐标比 $P$ 大的和纵坐标比 $P$ 小的。建立两个单调栈，一个栈内的点纵坐标单调递减，一个单调递增。每次从单调栈中二分出满足条件的且最靠近当前点（即在栈内最上面的）点来作为花盆的左端点，维护答案。在处理完以 $P$ 为右端点的情况后，将 $P$ 入栈。

```cpp
#include <cstdio>
#include <algorithm>
#include <functional>

using std::sort;
using std::lower_bound;
using std::upper_bound;

const int MAXN = 100010;

struct water{
	int ht;
	int ps;
	inline int operator <(const water& b) const {
		return this->ps < b.ps;
	} 
}wt[MAXN];

int n, d;
int sta1[MAXN] = {0x7fffffff}, pos1[MAXN], top1;
int sta2[MAXN] = {0x80000000}, pos2[MAXN], top2;

int main() {
	scanf("%d%d", &n, &d);
	for(int i = 1; i <= n; ++i)
		scanf("%d%d", &wt[i].ps, &wt[i].ht);
	sort(wt + 1, wt + n + 1);
	int ans = 0x7f7f7f7fl;
	for(int i = 1; i <= n; ++i) {
		int p;
		p = upper_bound(sta1 + 1, sta1 + top1 + 1, wt[i].ht + d, std::greater<int>()) - sta1 - 1;
		if(p) ans = std::min(ans, wt[i].ps - pos1[p]);
		while(sta1[top1] <= wt[i].ht) top1--;
		sta1[++top1] = wt[i].ht, pos1[top1] = wt[i].ps;
		p = upper_bound(sta2 + 1, sta2 + top2 + 1, wt[i].ht - d, std::less<int>()) - sta2 - 1;
		if(p) ans = std::min(ans, wt[i].ps - pos2[p]);
		while(sta2[top2] >= wt[i].ht) top2--;
		sta2[++top2] = wt[i].ht, pos2[top2] = wt[i].ps;
	}
	if(ans != 0x7f7f7f7fl)
		printf("%d\n", ans);
	else puts("-1");
	return 0;
} 
```

---

## 作者：Santiego (赞：0)


> 存在一个长度为$x$的区间$[l,r]$，使得区间中最大值与最小值差至少为$w$，求这个最小的$x$
>
> $n\le 100000$，$w\le 1000000$

显然区间长度$x$越大，最值之差越大，满足单调性，上二分答案，问题转化为是否存在长度为$mid$的区间中最值之差至少为$w$，而这个问题可以用单调队列（滑动窗口）$O(n)$解决。

单调队列存的下标，首先判断队首是否合法（窗口大小），然后按照“比你强还比你年轻”的原则弹队尾维护队列即可。

```cpp
#include <cstdio>
#include <algorithm>
#define MAXN 100010
using namespace std;
int n,d;
struct nod{
    int x,y;
    const bool operator < (const nod &a) const{
        return x<a.x;
    }
} a[MAXN];
namespace quemx {
    int q[MAXN],head,tail;
}
namespace quemin {
    int q[MAXN],head,tail;
}
inline bool check(int wid) {
    quemx::head=1,quemx::tail=0;
    quemin::head=1,quemin::tail=0;
    for(int i=1;i<=n;++i){
        // 滑动窗口宽度
        while(quemx::head<=quemx::tail&&a[i].x-a[quemx::q[quemx::head]].x>wid) ++quemx::head;
        while(quemin::head<=quemin::tail&&a[i].x-a[quemin::q[quemin::head]].x>wid) ++quemin::head;
        // 维护单调队列
        while(quemx::head<=quemx::tail&&a[quemx::q[quemx::tail]].y<=a[i].y) --quemx::tail;
        while(quemin::head<=quemin::tail&&a[quemin::q[quemin::tail]].y>=a[i].y) --quemin::tail;
        // 入队
        quemx::q[++quemx::tail]=i;
        quemin::q[++quemin::tail]=i;
        if(a[quemx::q[quemx::head]].y-a[quemin::q[quemin::head]].y>=d) return 1;
    }
    return 0;
}
int main() {
    scanf("%d %d", &n, &d);
    int l=1,r=0;
    for(int i=1;i<=n;++i) scanf("%d%d", &a[i].x, &a[i].y), r=max(r, a[i].x);
    sort(a+1, a+1+n);
    int ans=-1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)) r=mid-1, ans=mid;
        else l=mid+1;
    }
    printf("%d\n", ans);
    return 0;
}
```




---

## 作者：mydiplomacy (赞：0)

因为$n<=10^5$，所以效率为$nlog^2n$的算法也是可以通过的。

由于花盆宽度对于时间差是单调不减的（即花盆宽度增大时，时间差要么不变要么增大），所以我们可以二分答案（花盆宽度）。

对于答案$ans_1$，考虑如何判断$ans_1$是否可行？我们使用尺取的思想，维护一个区间$[l,r]$，满足$a[r]-a[l]==ans_1$，并判断$[l,r]$是否满足条件。我们可以利用线段树维护区间$[l,r]$的最小值与最大值，如果最大值与最小值的差>=D，就说明区间$[l,r]$满足条件。所以我们可以$O(nlogn)$的效率判断$ans_1$是否可行。结合二分的复杂度，整体算法的复杂度是$O(nlog^2n)$的，可以通过此题。

具体来说，线段树维护的时候，查询最大值与最小值的代码是比较相似的（只需要判断是min还是max），所以我们可以把查询最大值和维护最小值放在一个函数写，可以减少代码量。由于不用修改，所以代码很好写，这里就不提供了。

---

## 作者：Itst (赞：0)

### ~~瞎搞题钦定~~
### 话说看到这道题的第一时间并没有想到滑动窗口，而想到了~~最近练到疯的~~数据结构$qwq$，然后就往数据结构方面想了。
### 把所有点按照$y$值从小到大$sort$之后，可以知道对于某两个相邻的雨滴$i$与$i+1$，满足$y_i-y_j\geq D$也就会满足$y_{i+1}-y_j\geq D$，而对于每一个雨滴$i$，满足$y_i-y_j\geq D$的$j$取值必定是一个区间$[1,m](m \in N)($令$ [1,0] = \varnothing $)，所以可以用尺取法找出满足$y_i-y_j\geq D$的$j$的范围，而求$min\{|x_i-x_j|\}$就是邻值查找问题，直接用$set$维护即可
### 接下来是代码环节
```
#include<bits/stdc++.h>
using namespace std;

inline int read(){
    int a = 0;
    char c = getchar();
    while(!isdigit(c))
        c = getchar();
    while(isdigit(c)){
        a = (a << 3) + (a << 1) + (c ^ '0');
        c = getchar();
    }
    return a;
}

inline int min(int a , int b){
    return a < b ? a : b;
}

struct drop{
    int time , x;
}now[100001];
set < int > s;

inline bool cmp(drop a , drop b){
    return a.time < b.time;
}

int main(){
    int dir = 1 , N = read() , D = read() , ans = 0x3f3f3f3f;
    for(int i = 1 ; i <= N ; i++){
        now[i].x = read();
        now[i].time = read();
    }
    sort(now + 1 , now + N + 1 , cmp);
    //排序
    for(int i = 1 ; i <= N && ans ; i++){
        while(now[i].time - now[dir].time >= D)
            s.insert(now[dir++].x);
        //尺取
        if(!s.empty()){
            set < int > ::iterator it = s.lower_bound(now[i].x);
            if(it == s.end())
                ans = min(ans , now[i].x - *(--it));
            else
                if(it == s.begin())
                    ans = min(ans , (*it) - now[i].x);
                else{
                    ans = min(ans , (*it) - now[i].x);
                    ans = min(ans , now[i].x - *(--it));
                }
            //邻值查找
        }
    }
    cout << (ans == 0x3f3f3f3f ? -1 : ans);
    return 0;
}
```

---

