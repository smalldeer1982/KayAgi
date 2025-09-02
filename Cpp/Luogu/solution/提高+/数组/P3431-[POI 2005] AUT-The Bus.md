# [POI 2005] AUT-The Bus

## 题目描述

字节市的街道形成了一个规则的棋盘状网络——它们要么是南北方向，要么是东西方向。我们称它们为 NS 街道和 WE 街道。此外，每条街道都贯穿整个城市。每条 NS 街道与每条 WE 街道相交，反之亦然。NS 街道从最西边开始编号，从 $1$ 到 $n$。WE 街道从最南边开始编号，从 $1$ 到 $m$。每条第 $i$ 条 NS 街道与第 $j$ 条 WE 街道的交点用一对数字 $(i,j)$ 表示（$1\le i\le n$，$1\le j\le m$）。  字节市有一条公交线路，交叉点作为公交车站。公交车从 $(1,1)$ 交点开始行程，并在 $(n,m)$ 交点结束。此外，公交车只能向东和/或向北行驶。  在一些交叉点有乘客在等车。公交车司机希望选择一条路线，使他能够尽可能多地接到这些乘客。（我们假设公交车内部空间足够大，可以接收所有等待的乘客，无论选择哪条路线。）任务编写一个程序：  从标准输入读取道路网络的描述和每个交叉点等待的乘客人数，找到公交车最多能接到多少乘客，将结果写入标准输出。 

## 说明/提示

（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
8 7 11
4 3 4
6 2 4
2 3 2
5 6 1
2 5 2
1 5 5
2 1 1
3 1 1
7 7 1
7 4 2
8 6 2```

### 输出

```
11```

# 题解

## 作者：greenheadstrange (赞：13)

很容易想到O（nm）的DP但是一看m和n的范围10^9，GG

再一看k的范围10^5，便想到**离散化**一下

```cpp
//本蒟蒻是用map来离散化的，但是推荐dalao们还是用lower_bound比较好
map<int,int>mpx,mpy;
for(int i=1;i<=k;i++){
	scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].s);
	x[i]=a[i].x;
	y[i]=a[i].y;
	}	
x[0]=y[0]=1;
sort(x,x+k+1);
sort(y,y+k+1);
mpx[x[0]]=++nx;
mpy[y[0]]=++ny;	
for(int i=1;i<=k;i++){
	if(x[i]!=x[i-1])mpx[x[i]]=++nx;
	if(y[i]!=y[i-1])mpy[y[i]]=++ny;
}
for(int i=1;i<=k;i++)a[i].x=mpx[a[i].x],a[i].y=mpy[a[i].y];
```
此时的复杂度瞬间降到了O（k^2）但是只有40分，怎么办？

不要慌，先将动态转移方程写出来看看^_^

设f[i]表示走到点i的最大值

将数组a以横坐标作为第一关键字，纵坐标作为第二关键字排序后

f[i]=max(f[j])+a[i].s(其间a[j].y<=a[i].y)

亲爱的童鞋们，看到这里是不是想到了什么优化？

**树状数组**

```cpp
sort(a+1,a+k+1,cmp);
for(int i=1;i<=k;i++){		
	f[i]=ask(a[i].y)+a[i].s;	
	modify(a[i].y,f[i]);	
}	
```
下面是本蒟蒻的丑代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int A=500005;
map<int,int>mpx,mpy;
struct note{
	int x,y,s;
}a[A];
int n,m,k,ans,x[A],y[A],c[A*4],f[A],nx,ny;
bool cmp(const note&aa,const note&bb){//以横坐标作为第一关键字，纵坐标作为第二关键字排序
	return (aa.x==bb.x?aa.y<bb.y:aa.x<bb.x);
}
///////////////////////////////树状数组 
int lowbit(int x){return x&(-x);}//lowbit操作 
void modify(int x,int k){//单点修改 
	for(int i=x;i<=ny;i+=lowbit(i))c[i]=max(c[i],k);
}
int ask(int x){//区间查询 
	int maxx=0;
	for(int i=x;i;i-=lowbit(i))maxx=max(maxx,c[i]);
	return maxx;
}
///////////////////////////////
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=k;i++){
		scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].s);
		x[i]=a[i].x;
		y[i]=a[i].y;
	}
	///////////////////////////////离散化 
	x[0]=y[0]=1;
	sort(x,x+k+1);
	sort(y,y+k+1);
	mpx[x[0]]=++nx;
	mpy[y[0]]=++ny;
	for(int i=1;i<=k;i++){
		if(x[i]!=x[i-1])mpx[x[i]]=++nx;
		if(y[i]!=y[i-1])mpy[y[i]]=++ny;
	}
	for(int i=1;i<=k;i++)a[i].x=mpx[a[i].x],a[i].y=mpy[a[i].y];
	///////////////////////////////
	
	///////////////////////////////DP 
	sort(a+1,a+k+1,cmp);
	for(int i=1;i<=k;i++){		
		f[i]=ask(a[i].y)+a[i].s;	
		modify(a[i].y,f[i]);	
	}	
	for(int i=1;i<=k;i++)ans=max(ans,f[i]);
	///////////////////////////////
	printf("%d",ans);
	return 0;
}
```
结束语：这道题并不难DP+树状数组，但是本蒟蒻却毒瘤了一个小时，结果是粗心将k与n混用了，在此，本蒟蒻提醒您：

**代码千万条，细心第一条。**

**代码不规范，毒瘤两行泪。**


---

## 作者：Tethys (赞：7)

### 题意：
给定网格图上的点，求一条最大的权值的不下降的路径，输出一下最大权值

### 思路：
假设我们当前在点$(x, y)$，我们能够知道，求得当前点的最优解的话，需要找一个$\max f_{i,j}(i\leq x$且$j \leq y)$（$f$为之前求的最优解），然后用那个答案来更新， 所以我们可以想到树状数组

树状数组求最大值
```cpp
	inline int lowbit(int x){ return x & (-x);}
	void change(int x, long long val){
		while(x < N){
			tr[x] = std::max(tr[x], val);
			x += lowbit(x);
		}
	}
	inline long long query(int x){
		long long res = 0;
		for(res = std::max(res, tr[x]); (x -= lowbit(x)); res = std::max(res, tr[x]));
		return res;
	}
```

我们先按横坐标排序，使得这个点之前的点一定在它的左边（西边），然后在纵坐标上进行树状数组的操作就好了，我们在每次求点的最优解的时候直接更新答案就好了，因为可以从这个点不走剩下的点到达终点

然后求完当前点的最优解之后，更新一下当前纵坐标及以上的最优解

注：记得把纵坐标离散化，不然会很惨的（因为范围是$\leq 1e9$），我一般用$lower\_bound$来进行离散化

### 代码：
```cpp
#include<bits/stdc++.h>
const int N = 1e6 + 5;

namespace Tethys{
	inline long long read(){
		long long s = 0, f = 1; char ch;
		while(!isdigit(ch = getchar())) (ch == '-') && (f = -f);
		for(s = (ch ^ 48); isdigit(ch = getchar()); s = (s << 1) + (s << 3) + (ch ^ 48));
		return (s *= f);
	}

	long long n, m, ans, tmp;
	long long tr[N];
	int k, cnt, b[N];
	struct node{ int x, y, num;} a[N];

	bool cmp(node op, node opp){ return op.x == opp.x ? op.y < opp.y : op.x < opp.x;}
	
	inline int lowbit(int x){ return x & (-x);}
	void change(int x, long long val){
		while(x < N){
			tr[x] = std::max(tr[x], val);
			x += lowbit(x);
		}
	}
	inline long long query(int x){
		long long res = 0;
		for(res = std::max(res, tr[x]); (x -= lowbit(x)); res = std::max(res, tr[x]));
		return res;
	}

	inline int main(){
		n = read(); m = read(); k = read();
		for(int i = 1; i <= k; i ++){
			a[i].x = read(); a[i].y = read(); 
			a[i].num = read(); b[i] = a[i].y;
		}

		std::sort(a + 1, a + k + 1, cmp); std::sort(b + 1, b + k + 1);
		cnt = std::unique(b + 1, b + k + 1) - b - 1;
		
		for(int i = 1; i <= k; i ++){
			a[i].y = std::lower_bound(b + 1, b + cnt + 1, a[i].y) - b;
			ans = std::max(ans, tmp = query(a[i].y) + a[i].num);
            		//tmp是当前点的最优解
			change(a[i].y, tmp);
		}

		printf("%lld\n", ans);
		return 0;
	}
}

signed main(){ return Tethys::main();}
```

完美撒花✿✿ヽ(°▽°)ノ✿

---

## 作者：andysk (赞：5)

[Link](https://www.luogu.org/problem/P3431)

[Blog](https://tony102.xyz/index.php/2019/11/13/luogu3431-poi2005aut-the-bus/) 阅读效果更佳

### 题意

要求从 $(1,1)$ 走到 $(n, m)$ ，可以走上下左右四个方向。要求中间经过一些点，使得走过的点加起来的权值最大。



### 题解

这道题是我用来练习二维偏序的（~~只有我这个菜鸡要学二维偏序~~

但是看到题目很自然地先考虑DP。朴素地，设 $f[i]$ 表示走到第 $i$ 个点的最大值，那么我们有：$f[i] = max{f[j]+w[i]}$ ， 其中$x[j] \leq x[i]$ 且 $y[j] \leq y[i]$

那么这样DP是 $O(n^2)$ 的（这道题是 $k$ )，显然无法承受。

简单观察出：$x[j] \leq x[i]$ 且 $y[j] \leq y[i]$，这个东西基本上就是二维偏序的条件。

具体地说，假如我们现在要二维扫点（统计某个点左下方有多少个点），可以这么做：

首先对横/纵坐标排序（以纵坐标为例），现在我们已知当前坐标数组左侧的点一定纵坐标小于当前点，只需要统计横坐标小于它的即可。这个过程可以用树状数组实现。

所以这道题就变成了一个二维偏序的入门题，我们统计一个前缀并取$max$即可。

注意$x\leq y\leq10^9$ , 而实际只有 $k\leq10^5$ 个点，直接存储空间无法接受，需要离散化。

写得较为详细了，不妨点个赞？~\(≧▽≦)/~


### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int SIZE = 100000 + 5;

int n, m, k;
int c[SIZE], bit[SIZE];

struct node {
    int x, y, p;
    inline bool operator < (const node a) const {
        if (x == a.x) return y < a.y;
        return x < a.x;
    }
} a[SIZE]; 

namespace ae86 {
	const int bufl = 1 << 15;
	char buf[bufl], *s = buf, *t = buf;
	inline int fetch() {
		if (s == t) { t = (s = buf) + fread(buf, 1, bufl, stdin); if (s == t) return EOF; }
		return *s++;
	}
	inline int read() {
		int a = 0, b = 1, c = fetch();
		while (!isdigit(c))b ^= c == '-', c = fetch();
		while (isdigit(c)) a = a * 10 + c - 48, c = fetch();
		return b ? a : -a;
	}
}
using ae86::read;

inline int lowbit(int x) { return x & (-x); }

inline int Query(int x)
{
    int ans = 0;
    for ( ; x; x -= lowbit(x)) ans = std::max(ans, bit[x]);
    return ans;
}

inline void Change(int x, int val)
{
    for ( ; x <= k; x += lowbit(x)) bit[x] = std::max(bit[x], val);
}

signed main()
{
    // freopen("data.in", "r", stdin);
    // freopen("data.out", "w", stdout);
    n = read(), m = read(), k = read();
    for (int i = 1; i <= k; i++) {
        a[i].x = read(), a[i].y = read(), a[i].p = read();
        c[i] = a[i].y;
    }
    std::sort(c + 1, c + k + 1);
    m = std::unique(c + 1, c + k + 1) - c - 1;
    for (int i = 1; i <= k; i++) a[i].y = lower_bound(c + 1, c + m + 1, a[i].y) - c;
    std::sort(a + 1, a + k + 1);
    int ans = 0;
    for (int i = 1; i <= k; i++) {
        int sum = Query(a[i].y) + a[i].p;
        ans = std::max(ans, sum);
        Change(a[i].y, sum);
    }
    printf("%lld", ans);
    return 0;
}
```



---

## 作者：wlzhouzhuan (赞：3)

$Solution:$

一道典型的二维偏序题。

我们将每个坐标按$x$坐标为第一关键词，$y$坐标为第二关键字排序。

这样，坐标都有了一定的顺序，而且不会影响到影响（因为后面的点可能会利用到前面的点，但是前面的点不可能利用到后面的点），直观感受一下即可证明。

接下来，我们将$y$给离散化，将$y$收缩成$[1-k]$之间的一个数，就可以树状数组啦！

每个点对答案$res$的贡献即为$max(val[1],val[2]...val[p[i].y])+p[i].p$


该点对后面的点的影响为$val[i]=max(val[i],res),i∈[\space p[i].y,k\space]$


时间复杂度$O(nlogn)$

```cpp
#include <bits/stdc++.h>
using namespace std;

#define rep(i, l, r) for (int i = l; i <= r; i++)
#define req(i, l, r) for (int i = l; i >= r; i--)
#define For(i, l, r) rep(i, l, r - 1)

const int N = 100005;

struct Person {
	int x, y, p;
	bool operator < (const Person b) const {
		if (x != b.x) return x < b.x;
		else return y < b.y;
	}
}p[N];
int c[N], y2[N];
int n, m, k, ans;

void read(int &x) {
	x = 0; int f = 1;
	char op = getchar();
	while (!isdigit(op)) {
		if (op == '-') f = -1;
		op = getchar();
	}
	while (isdigit(op)) {
		x = 10 * x + op - '0';
		op = getchar();
	}
	x *= f;
}

int lowbit(int x) {
	return x & -x;
}

void add(int x, int ad) {
	while (x <= m) {
		c[x] = max(c[x], ad);
		x += lowbit(x);
	}
} 

int query(int x) {
	int ans = 0;
	while (x > 0) {
		ans = max(ans, c[x]);
		x -= lowbit(x);
	}
	return ans;
}

int main() {
	read(n), read(m), read(k);
	rep(i, 1, k) {
		read(p[i].x), read(p[i].y), read(p[i].p);
		y2[i] = p[i].y; 
	}
	sort(y2 + 1, y2 + k + 1);
	m = unique(y2 + 1, y2 + k + 1) - y2 - 1;

	rep(i, 1, k) p[i].y = lower_bound(y2 + 1, y2 + m + 1, p[i].y) - y2;
	sort(p + 1, p + k + 1);

	rep(i, 1, k) {
		int res = query(p[i].y) + p[i].p;
		ans = max(ans, res);
		add(p[i].y, res);
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：WanderingTrader (赞：2)

### 题目分析
看到 $n,m\le10^9$，暴力dp是不行了，先来一波**离散化**。

我们可以发现，如果点 $i$ 能从点 $j$ 进行转移，那么必须满足 $x_i\ge x_j$ 且 $y_i\ge y_j$，即 $i,j$ 满足**二维偏序**的关系。

那么我们对每个点根据先 $x$ 升序再 $y$ 升序进行排序。然后依次遍历每一个点。这时可以保证 $x_i\le x_{i+1}$，还要看 $y$。

容易写出状态转移方程：$f(i)=p(i)+\max\{f(j)|j<i\cap y_j<y_i\}$

总复杂度 $O(k^2)$。但看到 $k\le10^5$，还得继续优化。

观察 $\max\{f(j)|j<i\cap y_j<y_i\}$ 这个式子，如果我们将每一个 $y_j$ 看成一个下标，$f(j)$ 看成这个下标上的值，那么所求即为表中 $y_j$ 的**前缀最大值**，是一种特殊的动态RMQ。由于前缀的性质，我们可以用树状数组来代替线段树，大大减少了代码量，同时提高了效率。

不过 $y$ 最大可以达到 $10^9$，直接开数组开不下，怎么办？

可以用map。经实测，用map实现的树状数组可以达到90分，由于map复杂度自带一个 $\log$，所以总复杂度达到 $O(k\log^2 k)$。在常数很大的情况下，这依然会超时。

所以我们再做一次**离散化**，将复杂度降到 $O(k\log k)$。具体实现看代码。
### 代码
首先我们看一下树状数组的实现。在RSQ中，我们通常用树状数组来求前缀和，用前缀和作差来求任意区间的和。现在我们可以用同样的方法来求前缀最大值。查询代码如下：
```cpp
inline int LSB(int x){return x&-x;}
int query(int x)
{
	int ans=-inf;
	while(x)
	{
		ans=max(ans,bit[x]);
		x-=LSB(x);
	}
	return ans;
}
```
仅仅是把加法改成了max操作而已。加点操作也类似：
```cpp
void add(int x,int num)
{
	while(x<=k)
	{
		if(bit[x]>=num) return;
		bit[x]=num; 
		x+=LSB(x);
	}
}
```
这里我们加了一个小小的优化：当num不可能成为前缀最大值时，跳出循环。有点类似搜索中的**最优性剪枝**。

在我们读入数据后，先根据二位偏序的关系对所有车站进行排序：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxk=1e5+5;
const int inf=1.2e9;
int n,m,k;
struct Station {int x,y,p;} s[maxk];
bool cmp(const Station& a,const Station& b)
{
	return a.x<b.x||(a.x==b.x&&a.y<b.y); 
}
inline int read()
{
 	int x=0,f=1;
 	char c=getchar();
 	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
 	while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
 	return x*f;
}
int main()
{
	n=read();m=read();k=read();
	for(int i=1;i<=k;++i) 
	{
		s[i].x=read();
		s[i].y=read();
		s[i].p=read();
	}
	//input
	sort(s+1,s+1+k,cmp);
	//对车站排序 
	return 0;
}
```
接下来我们开一个结构体Point，放两个元素 $pos,val$ ，分别对应**排序后**各个车站的下标以及 $y$ 值。

我们对这个结构体数组根据 $val$ 值排序。然后开一个rk数组记录排名。即 $rk(pos(i))\leftarrow i$。
```cpp
int rk[maxk],bit[maxk];
struct Point {int pos,val;} id[maxk]; 
for(int i=1;i<=k;++i){id[i].pos=i;id[i].val=s[i].y;} 
sort(id+1,id+1+k,cmpId);
for(int i=1;i<=k;++i) rk[id[i].pos]=i;
```
这样，我们完成了数据的离散化，dp过程就非常简单了，树状数组的下标即为元素的rk值。
```cpp
for(int i=1;i<=k;++i)
	add(rk[i],f[i]=query(rk[i])+s[i].p);
```
那么最终的答案就是 $\max\{f(i)|1\le i\le n\}$。可以使用`max_element`。不过有一个更快的方法：$query(k)$ 就是答案。

全部代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxk=1e5+5;
const int inf=1.2e9;
int n,m,k;
int f[maxk],bit[maxk],rk[maxk];
struct Point {int pos,val;} id[maxk]; 
struct Station {int x,y,p;} s[maxk];
inline int LSB(int x){return x&-x;}
bool cmp(const Station& a,const Station& b)
{
	return a.x<b.x||(a.x==b.x&&a.y<b.y); 
} 
bool cmpId(const Point& a,const Point& b)
{
	if(a.val==b.val) return a.pos<b.pos;
	return a.val<b.val;
} 
inline int read()
{
 	int x=0,f=1;
 	char c=getchar();
 	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
 	while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
 	return x*f;
}
int query(int x)
{
	int ans=-inf;
	while(x)
	{
		ans=max(ans,bit[x]);
		x-=LSB(x);
	}
	return ans;
}
void add(int x,int num)
{
	while(x<=k)
	{
		if(bit[x]>=num) return;
		bit[x]=num; 
		x+=LSB(x);
	}
}
//BIT
int main()
{
	n=read();m=read();k=read();
	for(int i=1;i<=k;++i) 
	{
		s[i].x=read();
		s[i].y=read();
		s[i].p=read();
	}
	//input
	sort(s+1,s+1+k,cmp);
	//对车站排序 
	for(int i=1;i<=k;++i){id[i].pos=i;id[i].val=s[i].y;} 
	sort(id+1,id+1+k,cmpId);
	for(int i=1;i<=k;++i) rk[id[i].pos]=i;
	//离散化
	for(int i=1;i<=k;++i)
		add(rk[i],f[i]=query(rk[i])+s[i].p);
	//转移+加点 
	printf("%d\n",query(k));
	return 0;
}
```
$$\texttt{The End.}$$

---

## 作者：易极feng (赞：2)

### 树状数组

------------

设f[i]为前i个点中的最大值，

不难写出转移方程：

**f[i]=max(f[j])+p[i],(x[j]<=x[i]且y[j]<=y[i])**

可以发现这就是一道简单的**二维偏序问题**。

对纵坐标进行离散化后按横坐标排序，

用树状数组维护第i点前的最大值即可。

~~**欢乐无视九次方（逃）**~~

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

const int K=100005;

struct point{
	int x,y,p;
}a[K];

int n,m,k;
int cnt;//ymax after lysanization
int tree[K];

bool cmp1(point a,point b){
	return a.y<b.y;
}

bool cmp2(point a,point b){
	return (a.x==b.x)?a.y<b.y:a.x<b.x;
}

int lowbit(int x){return x&(-x);}

void add(int x,int k){for(;x<=cnt;x+=lowbit(x))tree[x]=max(tree[x],k);}

int ask(int x){int ans=-1;for(;x;x-=lowbit(x))ans=max(ans,tree[x]);return ans;}

int main(){
	int i,j;
	scanf("%d%d%d",&n,&m,&k);
	for(i=1;i<=k;i++)scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].p);
	
	sort(a+1,a+k+1,cmp1);
	int t;
	cnt=0;
	t=a[1].y,a[1].y=++cnt;
	for(i=2;i<=k;i++){
		if(a[i].y!=t)t=a[i].y,a[i].y=++cnt;
		else a[i].y=cnt;
	}
	
	sort(a+1,a+k+1,cmp2);
	
	int ans=-1;
	for(i=1;i<=k;i++){
		t=ask(a[i].y)+a[i].p;
		ans=max(t,ans);
		add(a[i].y,t);
	}
	
	printf("%d",ans);
	return 0;
}
```

---

## 作者：genshy (赞：1)



### **简化题意**：

给你一张网格图，每个点有其对应的权值，让你找出来一条横纵坐标都单调不降的路径，并最大化经过点的权值。

**分析**：

这是经典的二维数点或者二维偏序问题。

如果两维一直在变的话，我们不是很好处理，所以我们考虑对这些点排一下序，（按横纵坐标都可以）。

我一般按照横坐标来排序的。然后就变成了一维的最长不下降子序列问题。

设 $f[i]$ 表示 以 $i$ 这个高度为结尾的经过路径的最大权值。

则有转移 $f[i] = max(f[j] + a[i].w) j\leq i$

因为公交车可以延着横坐标走，所以他也可以由 $f[i]$ 转移过来。

此外还有一个要注意的点就是公交车沿着纵坐标竖着走，要先更新高度比较小的 $f$ 值，（我就在这里卡了好几回）

那我们一开始的排序就可以以横坐标为第一关键字，纵坐标为第二关键字排序，这样方便我们 $dp$。

这样的直接 $dp$ 的复杂度是 $O(n^2)$ 的，可以考虑用树状数组或者线段树维护一下。

树状数组常熟小，代码短，也比较好写，所以我一般选择树状数组。

最后的答案就是 $max(f[i])$,  另外不要忘记离散化哦。

**Code**

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long//不开long long 见祖宗·
const int N = 1e5+10;
int n,m,k,tr[N],b[N];
inline int read()
{
	int s = 0,w = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') w = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9'){s = s * 10 + ch - '0'; ch = getchar();}
	return s * w;
}
struct node
{
	int x,y,w;
}a[100010];
bool comp(node a,node b)
{
	if(a.x == b.x) return a.y < b.y;
	return a.x < b.x;
}
int lowbit(int x){ return x & -x; }
void chenge(int x,int val)
{
	for(; x <= N-5; x += lowbit(x)) tr[x] = max(tr[x],val);
}
int ask(int x)
{
	int res = 0;
	for(; x; x -= lowbit(x)) res = max(res,tr[x]);
	return res;
}
signed main()
{
	n = read(); m = read(); k = read();
	for(int i = 1; i <= k; i++)
	{
		a[i].x = read();
		a[i].y = read();
		a[i].w = read();
		b[i] = a[i].y;
	}
	sort(a+1,a+k+1,comp);//排序
	sort(b+1,b+k+1);
	int num = unique(b+1,b+k+1)-b-1;
	for(int i = 1; i <= k; i++) a[i].y = lower_bound(b+1,b+num+1,a[i].y)-b;//离散化
	for(int i = 1; i <= k; i++)
	{
		int res = ask(a[i].y);//树状数组优化dp
		chenge(a[i].y,res+a[i].w);
	}
	printf("%lld\n",ask(N-5));
	return 0;
}
```







---

## 作者：亚由亚由 (赞：1)

想要路径最短,就意味着每一步只能往右或往上走;

那么O(nm)的DP方程也就很显然了.但数据范围很痛快地否决了这个方法,所以只能从k入手;

把横坐标排序,就可以得到一个O(k^2)的方程:

f[i]=f[j]+a[i] (y[j]<=y[i])

显然可以用数据结构优化,例如离散化后树状数组/线段树...

~~我考场上脑抽想了一个splay~~

splay是不用离散化的,把纵坐标当做权值,f[j]作为一个附加值,每次对于f[i]找一个前驱,求个区间max就可以了;

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,f[100005],c,b,tot,root;
struct ll
{
	int x,y;
	int v;
}a[100005];
bool cmp(ll x,ll y){if(x.x^y.x)return x.x<y.x;return x.y<y.y;}
struct tree
{
	int ch[2];
	int f;
	int v;
	int d;
	int mx;
}t[100005];
void up(int x){t[x].mx=max(t[x].v,max(t[t[x].ch[0]].mx,t[t[x].ch[1]].mx));}
void rtt(int x)
{
	int p,qwq;
	p=t[x].f;
	qwq=(x==t[p].ch[1]);
	t[x].f=t[p].f;
	if(t[p].f)
	t[t[p].f].ch[p==t[t[p].f].ch[1]]=x;
	t[p].ch[qwq]=t[x].ch[qwq^1];
	if(t[x].ch[qwq^1])
	t[t[x].ch[qwq^1]].f=p;
	t[p].f=x;
	t[x].ch[qwq^1]=p;
	up(p);
	up(x);
}
void splay(int x,int y)
{
	int p;
	p=t[x].f;
	while(p^y)
	{
		if(!((p==t[t[p].f].ch[1])^(x==t[p].ch[1]))&&t[p].f^y)
		rtt(p);
		rtt(x);
		p=t[x].f;
	}
	if(!y)
	root=x;
}
void cr(int x,int d)
{
	int p,fa=0;
	p=root;
	if(!tot)
	{
		root=++tot;
		t[tot].d=d;
		t[tot].v=t[tot].mx=x;
	}
	while(1)
	{
		if(!p)
		{
			++tot;
			t[tot].f=fa;
			if(fa)
			t[fa].ch[d>t[fa].d]=tot;
			t[tot].d=d;
			t[tot].v=t[tot].mx=x;
			up(fa);
			break;
		}
		if(!(t[p].d^d))
		{
			t[p].v=max(t[p].v,x);
			t[p].mx=max(t[p].mx,x);
			break;
		}
		fa=p;
		p=t[p].ch[d>t[p].d];
	}
	splay(tot,0);
}
int qq(int x)
{
	int p,fa=0;
	p=root;
	while(p)
	{
		if(!(t[p].d^x))
		break;
		if(t[p].d<x)
		fa=p;
		p=t[p].ch[t[p].d<x];
	}
	if(!p)
	p=fa;
	if(p)
	splay(p,0);
	return p;
}
int main()
{
//	freopen("homework.in","r",stdin);
//	freopen("homework.out","w",stdout);
	int i,j,QAQ,an=0;
	scanf("%d%d%d",&b,&c,&n);
	for(i=1;i<=n;++i)
	scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].v);
	sort(a+1,a+n+1,cmp);
	for(i=1;i<=n;++i)
	{
		QAQ=qq(a[i].y);
		f[i]=a[i].v+max(t[QAQ].v,t[t[QAQ].ch[0]].mx);
		cr(f[i],a[i].y);
		an=max(an,f[i]);
	}
	printf("%d\n",an);
	return 0;
}
```

~~毒了一个暑假的splay终于有用了...~~

---

## 作者：kczno1 (赞：1)

O(nm)的dp很明显的吧。

dp[i][j]表示从(1,1)走到(i,j)的max。

现在我们要用跟点数相关的时间，

只用考虑存在点的dp[i][j]。

dp[i][j]能从dp[1..i][1..j]+w[i][j]转移过来。

从小到大枚举i，用树状数组维护1..j(先离散化)。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i,l,r) for(int i=l;i<=r;++i)
#define gc (c=getchar())
int read()
{
    char c;
    while(gc<'0');
    int x=c-'0';
    while(gc>='0')x=x*10+c-'0';
    return x;
}
void chmax(int &x,int y)
{
    if(x<y)x=y;
}

const int N=1e5+5;
struct point
{
    int x,y,w;
}p[N];

bool y_xiao(const point &p1,const point &p2)//const
{
    return p1.y<p2.y;
}
bool x_xiao(const point &p1,const point &p2)
{
    if(p1.x!=p2.x) return p1.x<p2.x;
    return p1.y<p2.y;
}

int c[N],top;
int qiu(int i)
{
    int ans=0;
    for(;i;i-=i&-i) chmax(ans,c[i]);
    return ans;
}
void upd(int i,int x)
{
    for(;i<=top;i+=i&-i) chmax(c[i],x);
}

int main()
{
    freopen("1.in","r",stdin);
    read();read();
    int k=read();
    rep(i,1,k) p[i]=(point){read(),read(),read()};
    
    sort(p+1,p+k+1,y_xiao);
    int now=p[1].y;top=1;
    rep(i,1,k)
    {
      if(p[i].y!=now){now=p[i].y;++top;}
      p[i].y=top;
    }
    
    sort(p+1,p+k+1,x_xiao);
    rep(i,1,k)
        upd(p[i].y,qiu(p[i].y)+p[i].w);
    printf("%d\n",qiu(top));
}
O(klogk)

```

---

## 作者：wubaiting2020 (赞：1)

# 这道题是一道比较水的dp,但是想用原来O(nm)的方法的人注意了n,m<=10^9
你空间时间受得了吗？  
但是一看k,k<=10^5  
应该是一个O(klogk)的算法  
1.首先先把x,y全部离散化  
2.可以易得直接转移会是o(k^2),所以求最大值得用数据结构优化（我用的线段树）
3.输出转移中的最大值
```cpp
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<queue>
#define ll long long
using namespace std;
const int INF=0x3f3f3f3f,MAXX=200000;
int n,m,k;
ll bj1[MAXX+5],bj2[MAXX+5];
struct node{ll x,y,num;}a[MAXX+5];
bool cmp(node x,node y){if(x.x==y.x)return x.y<y.y;return x.x<y.x;}//按y坐标排序 
struct tree{
	int l,r,maxx;
	inline void st(int a,int b,int c){l=a,r=b,maxx=c;}//封装的赋值 
}tree[MAXX*8+5];
void pushup(int k){tree[k].maxx=max(tree[k<<1].maxx,tree[k<<1|1].maxx);}
void Build(int k,int l,int r)
{
	tree[k].st(l,r,0);
	if(l==r)return;
	int mid=(l+r)>>1;
	Build(k<<1,l,mid);
	Build(k<<1|1,mid+1,r);
} 
void add(int k,int x,int v)
{
	if(tree[k].l>x||tree[k].r<x)return;
	if(x==tree[k].l&&x==tree[k].r){tree[k].maxx=max(tree[k].maxx,v);return;}
	add(k<<1,x,v);
	add(k<<1|1,x,v);
	pushup(k);
}
int ask(int k,int l,int r)
{
    if(tree[k].l>r||tree[k].r<l)return 0;
    if(l<=tree[k].l&&r>=tree[k].r)return tree[k].maxx;
    int mid=(tree[k].l+tree[k].r)>>1;
    return max(ask(k<<1,l,r),ask(k<<1|1,l,r));
}//线段树单修区查模版 
int main()
{
	scanf("%d %d %d",&n,&m,&k);
	for(int i=1;i<=k;i++)
	{
		scanf("%d %d %d",&a[i].x,&a[i].y,&a[i].num);
		bj1[i]=a[i].x;
		bj2[i]=a[i].y;
	}
	sort(bj1+1,bj1+k+1);
	sort(bj2+1,bj2+k+1);
	int m1=unique(bj1+1,bj1+k+1)-(bj1+1),m2=unique(bj2+1,bj2+k+1)-(bj2+1);
	n=bj2[m2];
	Build(1,1,n);
	for(int i=1;i<=k;i++)
	{
		a[i].x=lower_bound(bj1+1,bj1+m1+1,a[i].x)-bj1;
		a[i].y=lower_bound(bj2+1,bj2+m2+1,a[i].y)-bj2;
	}//离散化
	sort(a+1,a+k+1,cmp);//按y坐标排序 
	for(int i=1;i<=k;i++)
	{
		int x=ask(1,1,a[i].y)+a[i].num;
		add(1,a[i].y,x);//将前面的最大值转移到这个点（线段树维护） 
	}
	printf("%d",ask(1,1,n));
	return 0;
}


```


---

## 作者：derta (赞：0)

$O(k^2)$ 的 dp 还是很显然的

设 $f(i)$ 为**到达**第 $i$ 站**最多**可以接到的乘客人数

先将横坐标作为第一关键字，纵坐标作为第二关键字从小到大排序

那么则有 $f(i)= p_i+\max \limits_{1 \leqslant j < i, \ y(j) \leqslant y(i)} f(j)$

还是不好优化，**离散化**一下

令 $M(x)=\sum_{i=1}^{k}[x>y(i)]$

就有 $f(i)=p_i+\max \limits_{M(y(j)) \leqslant M(y(i))}f(j)$

然后就可以用树状数组优化了，把和改成 $\max$ 就可以了

另外，$\sum_{i=1}^{k} p_i$ 最大为 $10^6\times10^5=10^{11}$，要开 long long

$\rm{My}\;\rm{Code}$：

```cpp
#include <iostream>
#include <algorithm>
#include <map>
typedef std::map<int, int>::iterator Iter;
const int MAXK = 100005;
struct StationType {
	int x, y, price;
	
	//sort默认排序方式 
	inline bool operator < (const StationType& a) {
		if(x == a.x)
			return y < a.y;
		return x < a.x;
	}
} station[MAXK];
int n, m, k;
std::map<int, int> M; //意义见题解 
long long tree[MAXK], ans; //树状数组 

//输入一个车站 
inline std::istream& operator >> (std::istream& is, StationType& a) {
	is >> a.x >> a.y >> a.price;
	return is;
}

//树状数组常规操作  
inline int lowbit(int x)
{ return x & (-x); }

inline void equal_max(long long& x, int y)
{ if(x < y) x = y; }

long long Max(int end) { //返回long long 
	long long res = 0; //开long long 
	while(end >= 1) {
		equal_max(res, tree[end]);
		end -= lowbit(end);
	}
	return res;
}

void update(int pos, int t) {
	while(pos <= M.size()) {
		equal_max(tree[pos], t);
		pos += lowbit(pos);
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0), std::cout.tie(0);
	std::cin >> n >> m >> k;
	for(int i = 1; i <= k; ++i)
		std::cin >> station[i];
	std::sort(station + 1, station + k + 1);
	for(int i = 1; i <= k; ++i)
		M[station[i].y]; //仅创建Key，最后给value实值 
	int id = 1;
	for(Iter i = M.begin(); i != M.end(); ++i)
		i->second = id++; //按排名赋值 
	for(int i = 1; i <= k; ++i) {
		int t = M[station[i].y]; //避免反复调用，节省时间 
		long long p = Max(t) + station[i].price;
		update(t, p); //更新 
		equal_max(ans, p); //取max 
	}
	std::cout << ans;
	return 0;
}
```

---

## 作者：AmadeusSG (赞：0)

[题面](https://www.luogu.org/problemnew/show/P3431)

这道题很明显是dp

这道题很明显需要优化

因为n，m一看脑袋痛，我们自然选择k作为突破口。

数据范围k<=100000。算法复杂度应该在O（klogk）一下。

先想想，地图是二维的，要实现低时空，肯定要想办法转化为一维。

于是就给x坐标排个序，比较y坐标即可。

~~x，y这么大，不离散化说不过去。~~

那么就很轻松的推出方程f[i]=max(f[j])+stop[i].s(stop[j].y<=stop[i].y)

可以考虑数据结构优化dp。

由于本人很懒，于是就用了树状数组优化，实质上就是树状数组维护最大值max(f[j])。


代码：


```
#include<bits/stdc++.h>
using namespace std;
const int maxn=100000+5;
int n,m,k,ans,cntx,cnty;
int c[maxn],f[maxn],Xa[maxn],Ya[maxn];
map<int,int>mapx;
map<int,int>mapy;
struct Bus
{
	int x,y;
	int p;	
}stop[100005];
inline int LBT(int k)
{return k&(-k);}
inline bool cmp(Bus x,Bus y)
{
	if(x.x==y.x)return x.y<y.y;
	return x.x<y.x;
}
inline void Modify(int x,int d)
{
	for(int i=x;i<=maxn;i+=LBT(i))
		c[i]=max(c[i],d);
}
inline int Ask(int x)
{
	int ans=0;
	for(int i=x;i;i-=LBT(i))ans=max(ans,c[i]);
	return ans;
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=k;++i)
	{
		scanf("%d%d%d",&stop[i].x,&stop[i].y,&stop[i].p);
		if(!mapx[stop[i].x])
		{
			Xa[++cntx]=stop[i].x;
			//mapx[stop[i].x]=1;
		}
		if(!mapy[stop[i].y])
		{
			Ya[++cnty]=stop[i].y;
			//mapy[stop[i].y]=1;
		}
	}
	sort(Xa+1,Xa+cntx+1);
	sort(Ya+1,Ya+cnty+1);
	for(int i=1;i<=cntx;++i)mapx[Xa[i]]=i;
	for(int i=1;i<=cnty;++i)mapy[Ya[i]]=i;
	sort(stop+1,stop+k+1,cmp);
	for(int i=1;i<=k;++i)
	{
		int temp=Ask(mapy[stop[i].y]);
		f[i]=temp+stop[i].p;
		Modify(mapy[stop[i].y],f[i]);
		ans=max(ans,f[i]);
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：cold_cold (赞：0)


[安利一波博客](https://www.cnblogs.com/cold-cold/p/10014492.html)

看完题目后我很高兴，我以为这是到大水题，只不就是一个O(nm)的DP嘛，有什么难的。但当我看到数据范围1≤n≤109, 1≤m≤109, 1≤k≤105 的时候，我就笑不出来了，我立刻想到这一定是一个O(k2)的DP，通过数据结构优化为O(klogk)

我首先想到的是将整张图按照与对角线平行的线分为n+m-1层，逐层递推，但我很快发现不行，（在笛卡尔坐标系下）如两个点(2,3)和(4,2) ，点2的所在层数比点1大1，按照我的方法点2应该可以从点1转移，但实际上不行，点1不能向下走到点2

然后我就想到了最长不下降子序列的树状数组优化法，我将x排序后，将y做一个最大子序列（注：不是最长不下降子序列）不就可以了吗？考虑到1≤m≤109所以要离散化

操作起来，就是dp[i]表示，以x排序后的以第i个点为最后一个节点所能达到的最大值
转移为在1 - (i-1)中找到y值不大于第i个点y值的点，在其中取最大值再加上p[i],就是dp[i]的值，树状数组优化法较为常见，就不再赘述

实现如下：


```cpp
#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstring>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
#define lowbit(x) x&-x
using namespace std;
typedef long long ll;
inline int read()
{
    register int p(1),a(0);register char ch=getchar();
    while((ch<'0'&&ch>'9')&&ch!='-') ch=getchar();
    if(ch=='-') p=-1,ch=getchar();
    while(ch>='0'&&ch<='9') a=a*10+ch-48,ch=getchar();
    return a*p;
}
const int N=1000100;
struct node
{
    int x,y,p,hao;
    bool operator < (const node xx)const
    {
        return x==xx.x?y<xx.y:x<xx.x;
    }
}a[N];
inline int max(int x,int y){return x<y?y:x;}
int f[N],n,m,k,tt[N],maxn[N],len,ans=0,temp;
void update(int p,int x)
{
    for(int i=p;i<=len;i+=lowbit(i))
        maxn[i]=max(x,maxn[i]);
}
int query(int p)
{
    int ans=0;
    for(int i=p;i>=1;i-=lowbit(i))
        ans=max(ans,maxn[i]);
    return ans;
}
int main()
{
    n=read(),m=read(),k=read();
    for(int i=1;i<=k;++i) a[i].x=read(),a[i].y=read(),a[i].p=read();
    sort(a+1,a+1+k);
    for(int i=1;i<=k;++i) tt[i]=a[i].y;
    sort(tt+1,tt+1+k);
    len=unique(tt+1,tt+1+k)-tt-1;
    for(int i=1;i<=k;++i) a[i].hao=lower_bound(tt+1,tt+1+len,a[i].y)-tt-1;
    for(int i=1;i<=k;++i)
    {
        ans=max(ans,temp=a[i].p+query(a[i].y));
        update(a[i].y,temp);
    }
    printf("%d\n",ans);
    return 0;
}
```


---

## 作者：Nishikino_Curtis (赞：0)

DP当然是很显然了。

$f[i][j] = max_{k \le i \wedge l \le j}\{f[k][l]\} + val_{i,j}$.

题目要求横纵坐标只能递增，也就是要求我们在以当前点为右下角的矩形中查一个最大值出来转移，不过并不需要维护一个二维的最大值，我们只需要按纵坐标为第一关键字，横坐标为第二关键字排个序就行了。

这样每次Query()的时候, 出现在$[1, x_i]$范围内的最大值一定已经是之前做过的合法解.

记得把 $x$ 离散化一下.

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cctype>

using namespace std;

const int maxn = 1e+5 + 5;

class intersec
{
public:
	int x, y, v;
	intersec(){}
	~intersec(){}
	
	bool operator < (const intersec &rhs) const
	{
		return (y == rhs.y) ? (x < rhs.x) : (y < rhs.y);
	}
};
int n, m, k;
int ans, cpy[maxn], tot;
intersec p[maxn];

class SegmentTree
{
public:
	SegmentTree() {}
	~SegmentTree() {}

	void pushup (int cur)
	{
		mx[cur] = max(mx[cur << 1], mx[cur << 1|1]);
	}
	void update (int cur, int l, int r, int p, int c)
	{
		if(l == r) {mx[cur] = c; return;}
		int mid = (l + r) >> 1; 
		if(p <= mid) update(cur << 1, l, mid, p, c);
		else update(cur << 1|1, mid + 1, r, p, c);
		pushup(cur);
	}
	int query(int cur, int l, int r, int L, int R)
	{
		if(L <= l && r <= R) return mx[cur];
		int mid = (l + r) >> 1, ret = 0;
		if(L <= mid) ret = query(cur << 1, l, mid, L, R);
		if(R > mid) ret = max(ret, query(cur << 1|1, mid + 1, r, L, R));
		return ret;
	}
private:
	int mx[maxn << 2];
};

SegmentTree s;

inline int rd()
{
	register int x = 0; register char c = getchar();
	while(!isdigit(c)) c = getchar();
	while(isdigit(c)) x = x * 10 + (c ^ 48), c = getchar();
	return x;
}

int main()
{
	n = rd(); m = rd(); k = rd();
	for(int i = 1; i <= k; ++i)
	{
		p[i].x = rd(); p[i].y = rd(); p[i].v = rd();
		cpy[i] = p[i].x;
	}
	cpy[k + 1] = 0;
	sort(cpy + 1, cpy + 2 + k);
	tot = unique(cpy + 1, cpy + 2 + k) - (cpy + 1);
	sort(p + 1, p + 1 + k);
	for(int i = 1; i <= k; ++i)
	{
		p[i].x = lower_bound(cpy + 1, cpy + 1 + tot, p[i].x) - cpy;
		int ret = s.query(1, 1, tot, 1, p[i].x);
		ret += p[i].v;
		s.update(1, 1, tot, p[i].x, ret);
	}
	printf("%d\n", s.query(1, 1, tot, 1, tot));
	return 0;
}
```

---

