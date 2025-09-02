# かかし

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joisc2014/tasks/joisc2014_i



# 题解

## 作者：Lynkcat (赞：8)

原题「JOISC 2014 Day3」稻草人。

发一篇不太一样的做法。

首先考虑离散化后按 $y$ 从小到大插入所有点，并且计算以当前点为右上角时有多少左下角符合条件。

![](https://cdn.luogu.com.cn/upload/image_hosting/j8j93u6m.png)

比如，我们要算以 $A$ 点为右上角时(请忽略上图中坐标轴上的点），$G,C,E,D$ 四个点符合成为左下角的条件。

也就是说，一个点 $x$ 要成为左下角，必须要在满足不存在一个点 $y$ 其在 $A$ 左下角，并且其横坐标大于 $x$ 的横坐标且纵坐标大于 $x$ 的纵坐标。

那么相当于我们要维护一个后缀的最大值序列中数的种类。

这个问题就很经典了：[楼房重建](https://www.luogu.com.cn/problem/P4198)。

我们用类似的方法维护序列的最大值，序列的答案，合并、修改类似原题。

查询的时候发现我们只需要查询一段 $x$ 前缀的答案。那么我们每次就只要先做右儿子再把所有左儿子的答案合并过去即可。

每次合并复杂度为 $O(\log n)$，时间复杂度 $O(n \log^2 n)$。

```c++
//QwQcOrZ yyds!!!
#include<bits/stdc++.h>
#define ll long long
#define F(i,a,b) for (int i=(a);i<=(b);i++)
#define R(i,a,b) for (int i=(a);i<(b);i++)
#define D(i,a,b) for (int i=(a);i>=(b);i--)
#define go(i,x) for (int i=head[x];i;i=e[i].nx)
#define mp make_pair
#define pb push_back
#define pa pair < int,int >
#define fi first
#define se second
#define re register
#define be begin()
#define en end()
#define sqr(x) ((x)*(x))
#define ret return puts("-1"),0;
#define put putchar('\n')
#define inf 1000000005
#define mod 998244353
//#define int ll
#define N 200005
using namespace std;
inline char gc(){static char buf[100000],*p1=buf,*p2=buf;return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;}
#define gc getchar
inline ll read(){char c=gc();ll su=0,f=1;for (;c<'0'||c>'9';c=gc()) if (c=='-') f=-1;for (;c>='0'&&c<='9';c=gc()) su=su*10+c-'0';return su*f;}
inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll x){write(x),putchar(' ');}
inline void writeln(ll x){write(x);putchar('\n');}
int n,b[N],mx[N<<2],len[N<<2];
ll ans;
struct node
{
	int x,y;
}a[N];
bool cmp(node x,node y)
{
	return x.y<y.y;
}
int work(int now,int k,int l,int r)
{
	if (l==r) return (mx[k]>now);
	if (mx[k]<=now) return 0;
	if (mx[k<<1|1]>now) return len[k]-len[k<<1|1]+work(now,k<<1|1,l+(r-l)/2+1,r);
	return work(now,k<<1,l,l+(r-l)/2);
}
void pushup(int k,int l,int r)
{
	mx[k]=mx[k<<1|1],len[k]=len[k<<1|1];
	len[k]+=work(mx[k],k<<1,l,l+(r-l)/2);
	mx[k]=max(mx[k],mx[k<<1]);
}
void update(int k,int l,int r,int p,int val)
{
	if (l==p&&l==r)
	{
		len[k]=1;
		mx[k]=val;
		return;
	}
	int mid=l+(r-l)/2;
	if (p<=mid) update(k<<1,l,mid,p,val);
	else update(k<<1|1,mid+1,r,p,val);
	pushup(k,l,r);
}
pa query(int k,int l,int r,int L,int p)
{
	if (L<=l&&r<=p)
	{
		return mp(len[k],mx[k]);
	}
	int mid=l+(r-l)/2;
	if (p<=mid) return query(k<<1,l,mid,L,p);
	pa res=query(k<<1|1,mid+1,r,L,p);
	res.fi+=work(res.se,k<<1,l,mid);
	res.se=max(res.se,mx[k<<1]);
	return res;
}
signed main()
{
	n=read();
	for (int i=1;i<=n;i++)
	{
		a[i].x=read(),a[i].y=read()+1;b[i]=a[i].x;
	}
	sort(b+1,b+n+1);
	for (int i=1;i<=n;i++) a[i].x=lower_bound(b+1,b+n+1,a[i].x)-b;
	sort(a+1,a+n+1,cmp);
	for (int i=1;i<=n;i++)
	{
		ans=(ans+1ll*query(1,1,n,1,a[i].x).fi);
		update(1,1,n,a[i].x,a[i].y);
	}
	writeln(ans);
}
```



---

## 作者：y3kkc (赞：5)

偏序问题，很自然想到 cdq 分治。  
先按 $y$ 排序，将点分为两部分，再按 $x$ 进行排序。  
如图将其分为上下两部分。  
![](https://cdn.luogu.com.cn/upload/image_hosting/szmilm2x.png?x-oss-process=image/resize,m_lfit,h_170,w_225)  
跟一般的偏序问题一样，我们按 $x$ 大小从左往右扫。考虑上面做右上角，下面做左下角。下半部分对上半部分的贡献。  
首先，我们暂且不考虑上半部分带来的影响，只看下半部分的。  
那么下半部分能产生贡献的点一定是按 $x$ 单调递增 $y$ 单调递减的。    

如图：  
![](https://cdn.luogu.com.cn/upload/image_hosting/zqpbhud1.png?x-oss-process=image/resize,m_lfit,h_170,w_225)  
若扫到红色点，则计算后面的贡献时几个绿色点就不能算上了，因为若黄点与绿点配对则比包含红点。所以 $y$ 大于红点 $y$ 的点及图示绿点都需排除。我们可以用单调栈来实现。记为 $st_1$。  
  
考虑到这一步还没完，可能会有上半部分的点阻碍。  
如图中加了个蓝点（我是不会承认是因为一开始画图没注意才不得不后来加的）：  

![](https://cdn.luogu.com.cn/upload/image_hosting/jft1djf8.png?x-oss-process=image/resize,m_lfit,h_170,w_225)  
很明显，原本红点跟黄点是可以配对的，但现在蓝点在他们之间。所以不能贡献了。  
怎么办呢？我们可以在统计答案时删去 $st_1$ 中不合法的点。那么这些不合法的点都是存在一个点 $k$ 使得 $x_j < x_k < x_i$ 且 $y_k < y_i$。  
感性理解一下就是 $x_j$ 小于上面所有满足 $y_k < y_i$ 中最大的 $x_k$。  
我们同样地可以用单调栈来维护满足条件的 $x_k$。  
同时，注意到 $st_1$ 中的点是按 $x$ 递增的，于是我们直接在单调栈内二分查找最后一个小于 $x_k$ 的点即可。 

---

## 作者：orz_z (赞：5)

好题。

考虑 `cdq` 分治维护偏序。

按照横坐标递增排序，再按照纵坐标递减归并。

考虑左半边和右半边的点对，对于左半边合法点 $p$，将右半边纵坐标 $\geq y_p$ 的点加入单调栈，同时维护横坐标单增。

对于左半边内部的影响，另用一个单调栈维护，横坐标递减，答案累加时二分右边栈内纵坐标小于左边栈顶纵坐标个数即可。

左边栈：$y$ 单减，$x$ 单减。

右边栈：$y$ 单减，$x$ 单增。

时间复杂度 $\mathcal O(n\log^2n)$，这里偷懒用 `sort` 导致多了个 $\log$。


```cpp
#include<bits/stdc++.h>

using namespace std;

#define int long long
typedef long long ll;

#define ha putchar(' ')
#define he putchar('\n')

inline int read()
{
	int x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9')
	{
		if (c == '-')
			f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
		x = x * 10 + c - '0', c = getchar();
	return x * f;
}

inline void write(ll x)
{
	if(x < 0)
	{
		putchar('-');
		x = -x;
	}
	if(x > 9)
		write(x / 10);
	putchar(x % 10 + '0');
}

const int _ = 2e5 + 10;

int n;

ll ans;

struct abc
{
	int x, y;
} k[_], t[_];

int t1, s1[_], t2, s2[_];

bool cmp1(abc a, abc b) {return a.x < b.x;}
bool cmp2(abc a, abc b) {return a.y > b.y;}

int erfen(int p)
{
	int l = 0, r = t2;
	while(l < r)
	{
		int mid = (l + r + 1) >> 1;
		if(k[s2[mid]].y > p) l = mid;
		else r = mid - 1;
	}
	return l;
}

void cdq(int l, int r)
{
	if(l == r) return;
	int mid = (l + r) >> 1;
	cdq(l, mid), cdq(mid + 1, r);
	sort(k + l, k + mid + 1, cmp2);
	sort(k + mid + 1, k + r + 1, cmp2);
	int j = mid + 1; t1 = t2 = 0;
	for(int i = l; i <= mid; ++i)
	{
		while(j <= r && k[i].y < k[j].y)
		{
			while(t2 && k[s2[t2]].x > k[j].x) t2--;
			s2[++t2] = j, j++;
		}
		while(t1 && k[s1[t1]].x < k[i].x) t1--;
		ans += t2;
		if(t1) ans -= erfen(k[s1[t1]].y);
		s1[++t1] = i;
	}
}

signed main()
{
	n = read();
	for(int i = 1; i <= n; ++i)
		k[i].x = read(), k[i].y = read();
	sort(k + 1, k + n + 1, cmp1);
	cdq(1, n);
	write(ans), he;
	return 0;
}

/*
10
2 1
3 0
6 3
10 2
16 4
0 8
8 12
11 14
14 11
18 10

15
*/
```


---

## 作者：_Felix (赞：4)

~~かかしかかしかかしかかしかかしかかしかかしかかしかかしかかしかかし~~


如果不用关心组成的矩形里面有没有其他稻草人，就可以直接二维数点了，可惜不行，那么我们考虑cdq分治。（我也不知道为什么是这样转化）
不妨按y分治，最后的数组是归并排序成 $x$ 升序的。

[![qyl9N4.png](https://s1.ax1x.com/2022/03/29/qyl9N4.png)](https://imgtu.com/i/qyl9N4)

如果在同一个边，那就继续分治

如果不在同一边，怎么计算？

不妨在扫右上角的点的时候统计答案。

设当前扫到的右上角的点（在上半边）是 $(x_b,y_b)$ 合法的左下角点（在下半边）是 $x_a,y_a$。

我们最后的数组是归并成 $x$ 升序的，所以我们扫到的点都是 $x$ 递增的。
一对点对受到了两种限制，上半边和下半边。

- 上半边的限制

   $x_a<x_c<x_b,y_a<y_c<y_b$ 的 $(x_a,y_a)$ 不能存在。（$a,b$ 组成的矩形中间有点）
   
   我们扫过的所有点正是 $y_a<y_c,x_c<x_b$ 的所有点（$b$ 左下的点），那么就是要求 $\forall y_c < y_b,x_a> x_c$
   
   也就是 $x_a \ge max\{x_c | y_c<y_b\}$。（图中，如果以橙点为 $b$，那么由于粉点的影响，$a$ 可以是蓝点，但不可以是绿点。）
   
   所以维护一个 $y$ 单调递增的单调栈，用于找到左边最近的（即 $x_c$ 最大） $y_c<y_b$ 就可以了。
   
- 下半边的限制

   $x_a<x_c<x_b,y_a<y_c<y_b$ 的 $(x_a,y_a)$ 不能存在。（$a,b$ 组成的矩形中间有点）
   
   我们扫过的所有点正是 $y_a<y_c,x_c<x_b$ 的所有点（$b$ 左下的点），那么就是要求 $\forall x_a<x_c,y_a>y_c$
   
   其实就是任意满足 $x_1<x_2$ 两点的，必须同时满足 $y_1>y_2$（图中，如果以紫点为 $b$，那么$a$ 可以是灰点，但不可以是绿点和蓝点。）
   
   所以维护一个 $y$ 单调递减的单调栈。栈内就是 $x$ 递增，$y$ 递减的了。

然后每次统计答案的时候，二分单调栈即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define ls(x) ((x)<<1)
#define rs(x) ((x)<<1|1)
#define fi first
#define se second
#define mkp make_pair
#define PII pair<int,int>
int read() {
    char c = getchar(); int ff = 1; int x = 0;
    while(c < '0' || c > '9') { if(c == '-') ff = -1; c = getchar(); }
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return ff * x;
}
const int N = 2e5 + 10;
int n, lshx[N], lshy[N], lenx, leny; ll ans;
struct node {
	int x, y;
	friend bool operator < (node &a, node &b) {
		return a.y < b.y;
	} 
}p[N], tmp[N];
int st1[N], st2[N];
bool cmp(int a, int b) { return p[a].x < p[b].x; }
void cdq(int l, int r) {
	
	if(l == r) return;
	int mid = (l + r) >> 1;
	cdq(l, mid); cdq(mid + 1, r);
	//st1：x单调递增，维护y单调递减。（如果该点能贡献，那么在下半部分内它右上角且横坐标x之前的地方，没点。即任意贡献点，x1<x2,y1>y2） 
	//st2: x单调递增，找左边第一个满足y'<y的，维护y单调递增。 
	int i = l, j = mid + 1, k = l - 1, top1 = 0, top2 = 0;
	while(i <= mid || j <= r) {
		if(j > r || (i <= mid && p[i].x < p[j].x)) {
			while(top1 && p[st1[top1]].y < p[i].y) top1--;
			tmp[++k] = p[i]; st1[++top1] = i; i++;
		} else {
			while(top2 && p[st2[top2]].y > p[j].y) top2--; 
			
			p[n + 1].x = p[n + 1].y = 0; if(top2) p[n + 1].x = p[st2[top2]].x;
			int pos = lower_bound(st1 + 1, st1 + top1 + 1, n + 1, cmp) - st1;
			ans += top1 - pos + 1; 
			tmp[++k] = p[j]; st2[++top2] = j; j++;
		}
	}
	for(int i = l; i <= r; i++) p[i] = tmp[i];

	return;
}
int main() {
//	freopen("ex.out", "w", stdout);
	n = read();
	for(int i = 1; i <= n; i++) {
		p[i].x = read(), p[i].y = read();
		lshx[++lenx] = p[i].x, lshy[++leny] = p[i].y;
	}
	sort(lshx + 1, lshx + lenx + 1); sort(lshy + 1, lshy + leny + 1);
	for(int i = 1; i <= n; i++) {
		p[i].x = lower_bound(lshx + 1, lshx + lenx + 1, p[i].x) - lshx;
		p[i].y = lower_bound(lshy + 1, lshy + leny + 1, p[i].y) - lshy;
	}
	sort(p + 1, p + n + 1);
	cdq(1, n);
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：djh0314 (赞：1)

### [传送门](https://www.luogu.com.cn/problem/AT_joisc2014_i)

### 题意 
有 $n$ 个节点，问有多少对节点满足一个在左下角，一个在右下角，且其中没有一个节点。

$1\le n\le 2 \times 10^5$，$0 \le X_i\le 10^9$，$0 \le Y_i\le 10^9$。      

### 分析      

我们可以先打暴力，$O(n^3)$。    
暴力枚举每个点对，再枚举第三个点，观察是否有节点在这两个节点中间。

### 优化一
显然过不了，我们紧接着可以先对于 $X_i$ 进行排序，然后用线段树维护在区间内的最大 $X$ 值。      
倘若两个点之间的 $X$ 最大值大于我们枚举的前边的点，那么说明这个点对之间有另一个点。                 
时间复杂度 $O(n^2 \log n)$。     

### 优化二(正解)

因为作者是个蒟蒻，CDQ 打的不流利，因此仍然选择了线段树。        
我们可以用线段树维护最值，同时我们还可以维护在这个 $Y$ 上方的节点所能得到的贡献。     
现在的问题又变成了我们该如何合并两个区间。    
很显然，我们的上方的区间的原有答案可以直接被我们的当前区间继承。    
而我们的下方的区间，我们则可以继承大于等于我们上方区间最大值的点数。

时间复杂度 $O(n\log^2 n)$      

[Code](https://www.luogu.com.cn/paste/nhbdal19)。

---

## 作者：Reanap (赞：1)

挺好的一道题，没那么板子。

如果不考虑矩阵内有没有其它稻草人，那么就是一道二维偏序的板子题。~~但是它有~~

那么我们考虑如何处理。首先对于一个点集$j_k$，这些点都能与$i$组成合法矩阵。那么对于所有$x_{j_p} < x_{x_q}$都有$y_{j_p} > y_{j_q}$，那么我们显然可以用CDQ分治，按$x$排序，用$y$进行CDQ，同时用单调栈维护左区间以访问过的元素，计算答案就是加上单调栈的元素个数？

一发交上去wa了。

我们再仔细考虑，在左区间我们维护了一个单调栈，进而排除了左区间元素对于$i$的遮挡，但是我们并没有屏蔽掉右区间的干扰。由于右区间不保证按照$x$递增，所以我们甚至不能用更改单调栈的方式进行处理。所以我们在计算右区间答案时维护一下对于所有$x_j < x_i,y_j < y_i$的$y$的最大值记为$f_i$，而左区间中的元素想要与$i$形成答案$y$必然大于$f_i$且处于单调栈中，由于单调栈中元素的$y$值是单调递增的，因此我们可以二分一波求取答案。

代码：

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
void read(int &x){ 
	int f=1;x=0;char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
	x*=f;
}
const int MAXN = 2e5 + 5;
int n;
struct node {
	int x , y , id;
}a[MAXN] , b[MAXN] , s1[MAXN];
bool cmp(node x , node y) {
	return x.x < y.x;
}
int t1 , f[MAXN];
long long ans;
int find(int k) {
	int l = 1 , r = t1;
	if(t1 == 0) return 0;
	while(l + 1 < r) {
		int mid = (l + r) >> 1;
		if(s1[mid].y >= k) r = mid;
		else l = mid;
	}
	if(s1[l].y >= k) return t1 - l + 1;
	else if(s1[r].y >= k) return t1 - r + 1;
	else return t1 - r;
}
void cdq(int l , int r) {
	if(l == r) return;
	int mid = (l + r) >> 1;
	cdq(l , mid);cdq(mid + 1 , r);
	int x = l , y = mid + 1 , t = 0;
	t1 = 0;
	int _max = 0;
	while(x <= mid && y <= r) {
		if(a[x].y < a[y].y) {
			b[++t] = a[x]; 
			while(t1 && s1[t1].x < a[x].x) t1 --;
			s1[++t1] = a[x];
			_max = max(a[x].y , _max);
			x ++;
		}
		else {
			b[++t] = a[y];
			ans += find(f[a[y].id]);
			f[a[y].id] = max(f[a[y].id] , _max);
			y ++;
		}
	}
	for (int i = x; i <= mid; ++i) b[++t] = a[i];
	for (int i = y; i <= r; ++i) {
		b[++t] = a[i];
		ans += find(f[a[i].id]);
		f[a[i].id] = max(f[a[i].id] , _max);
	}
	for (int i = 1; i <= t; ++i) a[i + l - 1] = b[i];
}
int main() {
	read(n);
	for (int i = 1; i <= n; ++i) read(a[i].x),read(a[i].y),a[i].id=i;
	sort(a + 1 , a + 1 + n , cmp);
	cdq(1 , n);
	printf("%lld" , ans);
	return 0;
}
```

---

## 作者：stoorz (赞：1)

这道题没有样例，可以去LOJ看：https://loj.ac/problem/2880

网上的题解都是用 cdq+单调栈 的优秀算法，但是我却看不懂这些高大尚的算法。所以就写了一个 cdq+bit+线段树 的一种常数超级大的算法。~~然后再bzoj上T飞了，LOJ跑了倒数第一，33321 ms~~

首先我们发现这个题目所求其实很像三维偏序，所以考虑用 cdq 求解。

假设我们现在处理到的区间是 $[l,r]$，我们可以对每一个点求出一个贡献区间 $[l_i,r_i]$，比如说如果这个点 $i$ 在左半边，那么列区间为 $[l_i,r_i]$，行区间为 $[x_i,mid]$ 的矩形内没有任何一个点。

举个栗子，如下图

![](https://img2018.cnblogs.com/blog/1891948/202001/1891948-20200129113523770-1898373119.png)

红色点的贡献区间就是红色+紫色的矩形的列的区间，蓝色点的贡献区间就是蓝色+紫色的矩形的列的区间。黄色、绿色的点的贡献区间就是该颜色的矩形的列的区间。

也就是说，$mid$ 左边的点的贡献区间的下限是该点的纵坐标，右边的点的贡献区间的上限是该点的纵坐标。

为什么要处理出这个贡献区间呢？因为我们发现，如果 $mid$ 左边的点 $a$ 和 $mid$ 右边的点 $b$ 满足 $y_a\in [l_b,r_b]$ 且 $y_b\in [l_a,r_a]$，那么这两个点就可以构成一个矩形且这个矩形内没有其他点。例如上图，左边的蓝点和右边的黄点均满足自己的纵坐标在对方的贡献区间内，所以以蓝点为左下角，黄点为右上角的矩形就是一个合法的矩形。

那么我们现在有两个问题需要解决：
1. 如何求出每一个点的贡献区间？
2. 如何求出哪些点的贡献区间互相包含自己的纵坐标？

一步一步来解决。

#### 1.如何求出每一个点的贡献区间？

按照 cdq 常规套路，我们把 $mid$ 左右两边的点分别按纵坐标排序。
拿左边的点为例。一个点 $x$ 会影响另一个点 $y$ 的贡献区间，当且仅当 $x$ 严格位于 $y$ 的右下角。这样的话 $y$ 的贡献区间的下限至少为 $x$ 的纵坐标。

所以对于左边的点，我们建立一棵线段树，线段树的区间 $[l,r]$ 表示横坐标在 $l\sim r$ 的点中，最大的纵坐标值。按纵坐标从小到大排完序后顺序枚举，如果现在枚举到点 $i$，此时线段树内已经插入了 $1\sim i-1$ 的点，那么就在线段树中查询 $[x_i,mid]$ 中的最大值，容易发现这个最大值就是这个点的贡献区间的下限。然后再将 $i$ 插入，继续往下计算。

这样我们就在 $O(n\log n)$ 的时间复杂度内求出了所有区间 $[l,r]$ 内的点的贡献区间。需要注意，上述例子是在 $mid$ 左侧的点的处理方式，$mid$ 右侧的点需要进行一些改变，请自行思考（不想码了qwq）。

#### 2.如何求出哪些点的贡献区间互相包含自己的纵坐标？

第一反应是莫队，但是莫队的复杂度是 $n\sqrt{n}$ 级别的，这道题 $n\leq 2\times 10^5$，再加上 cdq 的 $\log n$ 和超级大常数，显然不行。

考虑枚举左边的点，依然按照纵坐标从小到大枚举，假设现在枚举到点 $k$，我们不难用指针维护出右半部分包含点 $k$ 的点。具体的，我们将右半部分的点以及它的贡献区间复制一份到新的数组，然后将原数组按照贡献区间下限 $(l)$ 从小到大排序，复制后的数组按照贡献区间上限 $(r)$ 从小到大排序，然后维护两个指针 $i,j$ 分别扫描两个数组，对于按$l$排序的数组，如果 $a[i].l\leq a[k].y$，那么我们就把树状数组中 $a[i].r$ 的位置加一；对于按 $r$ 排序的数组，如果 $b[j].r<a[k].y$，那么我们就把树状数组中 $b[j].y$ 减一；这样下来，树状数组内为1的点就是贡献区间下限在 $k$ 的纵坐标下方，而上限不小于 $k$ 的纵坐标的点，也就是为 1 的点的贡献区间都包含了 $k$。
那么接下来只要满足 $k$ 的贡献区间包含这些点就可以了，很简单，在树状数组中查询区间 $[a[k].l,a[k].r]$ 的和即可。

这样我们就在 $O(n\log n)$ 的时间复杂度内求出了区间 $[l,r]$ 右半部分的点对左半部分的点的贡献。至此，区间 $[l,r]$ 的全部运算结束，接下来递归求解即可。

时间复杂度$O(n\log^2 n)$。常数极大。

注意要开$\rm long\ long$
# 代码
185 行，约 3.44KB。
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

const ll N=200010,Inf=1e9;
ll n,tot,ans,maxn,c[N*2];

struct node
{
	ll x,y,l,r;
}a[N],b[N];

inline bool cmp1(node x,node y)
{
	return x.x<y.x;
}

inline bool cmp2(node x,node y)
{
	return x.y<y.y;
}

inline bool cmp3(node x,node y)
{
	return x.l<y.l;
}

inline bool cmp4(node x,node y)
{
	return x.r<y.r;
}

struct BIT
{
	ll c[N];
	
	inline void add(ll x,ll val)
	{
		for (;x<=maxn;x+=x&-x)
			c[x]+=val;
	}
	
	inline ll ask(ll x)
	{
		ll ans=0;
		for (;x;x-=x&-x)
			ans+=c[x];
		return ans;
	}
	
	inline void clear(ll x)
	{
		for (;x<=maxn && c[x];x+=x&-x)
			c[x]=0;
	}
}bit;

struct Treenode
{
	ll l,r,minn,maxn;
};

struct Tree
{
	Treenode tree[N*8];
	
	inline void build(ll x,ll l,ll r)
	{
		tree[x].l=l; tree[x].r=r;
		if (l==r)
		{
			tree[x].maxn=1; tree[x].minn=maxn;
			return;
		}
		ll mid=(l+r)>>1;
		build(x*2,l,mid); build(x*2+1,mid+1,r);
		pushup(x);
	}
	
	inline void pushup(ll x)
	{
		tree[x].maxn=max(tree[x*2].maxn,tree[x*2+1].maxn);
		tree[x].minn=min(tree[x*2].minn,tree[x*2+1].minn);
	}
	
	inline void update(ll x,ll k,ll val)
	{
		if (tree[x].l==k && tree[x].r==k)
		{
			tree[x].maxn=max(tree[x].maxn,val);
			tree[x].minn=min(tree[x].minn,val);
			return;
		}
		ll mid=(tree[x].l+tree[x].r)>>1;
		if (k<=mid) update(x*2,k,val);
			else update(x*2+1,k,val);
		pushup(x);
	}
	
	inline ll ask(ll x,ll l,ll r,bool type)
	{
		if (tree[x].l==l && tree[x].r==r)
			return type ? tree[x].maxn : tree[x].minn;
		ll mid=(tree[x].l+tree[x].r)>>1;
		if (r<=mid) return ask(x*2,l,r,type);
		else if (l>mid) return ask(x*2+1,l,r,type);
		else
		{
			if (type) return max(ask(x*2,l,mid,type),ask(x*2+1,mid+1,r,type));
				else return min(ask(x*2,l,mid,type),ask(x*2+1,mid+1,r,type));
		}
	}
	
	inline void clear(ll x,ll k)
	{
		tree[x].maxn=1; tree[x].minn=n;
		if (tree[x].l==tree[x].r) return;
		ll mid=(tree[x].l+tree[x].r)>>1;
		if (k<=mid) clear(x*2,k);
			else clear(x*2+1,k);
	}
}Tree;

inline void cdq(ll l,ll r)
{
	if (l==r) return;
	ll mid=(l+r)>>1;
	cdq(l,mid); sort(a+l,a+mid+1,cmp2);
	cdq(mid+1,r); sort(a+mid+1,a+r+1,cmp2);
	for (ll i=mid;i>=l;i--)
	{
		a[i].r=Tree.ask(1,a[i].x,maxn,0); a[i].l=a[i].y+1;
		Tree.update(1,a[i].x,a[i].y);
	}
	for (ll i=mid;i>=l;i--) Tree.clear(1,a[i].x);
	for (ll i=mid+1;i<=r;i++)
	{
		a[i].l=Tree.ask(1,1,a[i].x,1); a[i].r=a[i].y-1;
		Tree.update(1,a[i].x,a[i].y);
		b[i]=a[i];
	}
	for (ll i=mid+1;i<=r;i++) Tree.clear(1,a[i].x);
	
	sort(a+mid+1,a+r+1,cmp3); sort(b+mid+1,b+r+1,cmp4);
	for (ll i=mid+1,j=mid+1,k=l;k<=mid;k++)
	{
		for (;a[j].l<=a[k].y && j<=r;j++)
			bit.add(a[j].y,1);
		for (;b[i].r<a[k].y && i<=r;i++)
			bit.add(b[i].y,-1);
		ans+=bit.ask(a[k].r)-bit.ask(a[k].l-1);
	}
	for (ll i=l;i<=r;i++)
		bit.clear(a[i].y);
}

int main()
{
	scanf("%lld",&n);
	for (ll i=1;i<=n;i++)
		scanf("%lld%lld",&a[i].x,&a[i].y);
	for (ll i=1;i<=n;i++) c[i]=a[i].x;
	sort(c+1,c+1+n);
	tot=unique(c+1,c+1+n)-c-1;
	for (ll i=1;i<=n;i++)
	{
		a[i].x=lower_bound(c+1,c+1+tot,a[i].x)-c;
		maxn=max(maxn,a[i].x);
	}
	for (ll i=1;i<=n;i++) c[i]=a[i].y;
	sort(c+1,c+1+n);
	tot=unique(c+1,c+1+n)-c-1;
	for (ll i=1;i<=n;i++)
	{
		a[i].y=lower_bound(c+1,c+1+tot,a[i].y)-c;
		maxn=max(maxn,a[i].y);
	}
	Tree.build(1,1,maxn);
	sort(a+1,a+1+n,cmp1);
	cdq(1,n);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Che_001 (赞：0)

## 题意

在一个二维平面上，给定点集 $S$，求所有满足

- $\large{x_i\lt x_j}$；
- $\large{y_i\lt y_j}$；
- $\large{\forall k\in S\cap\{i,j\}}$，有 $\large{x_k\notin[x_i,x_j],y_k\notin [y_i,y_j]}$；

的点对 $(i,j)$ 的数量。

## Solution

发现对于一个点 $i$ 而言，对答案的贡献应为在它右上方的点所形成的凸包的大小。即其右上方 $x$ 最接近于 $x_i$ 和 $y$ 最接近于 $y_i$ 的两个点之间形成的类下凸包大小。令二者分别为 $pre_i$ 和 $r_i$。

形式化地，$\forall k\in T_i$，有 $x_i\lt x_k,y_i\lt y_k$。

则 $pre_i \in T_i$，$\forall k \in T_i$，有 $\lvert x_{pre_{j}}-x_i\lvert \leq \lvert x_k-x_i\lvert $。

同样地，有 $r_i \in T_i$，$\forall k \in T_i$，有 $\lvert y_{r_{j}}-y_i\lvert \leq \lvert y_k-y_i\lvert $。

则对答案可以产生贡献的点集为 $pre_i,a_1,\cdots,a_p,r_i$，满足 $a_i\in T_i$，$x_{a_{i-1}}\lt x_{a_i}\lt x_{a_{i+1}}$，且 $y_{a_{i-1}}\lt y_{a_i}\lt y_{a_{i+1}}$。

对于每个数，单调栈维护类下凸包即可，时间复杂度为 $\mathcal{O}(n^2)$。

考虑优化，发现不必要对于每个点重新计算答案，考虑对于 $x$ 或 $y$ 区间分治并合并答案。以分治 $x$ 坐标为例，从 $y_{max}$ 向下不断枚举。对于 $[mid+1,right]$ 区间，维护一个类下凸包，每个点满足在前一个点的右下方。对于 $[left,mid]$ 区间，也维护一个类下凸包，每个点满足在前一个点的左下方，对于新加入的点 $i$，在类下凸包中的前一个点对 $i$ 对答案贡献的影响最大，即前文提到的 $pre_i$。在右区间的类下凸包中，所有 $y\ge y_{pre_{i}}$ 的点都不产生贡献了，可以在右区间的单调栈中二分找到分界。

时间复杂度为 $\mathcal{O}(n\log^2n)$，可以通过本题。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int res=0,flag=1;
	char ch=getchar();
	while(!isalnum(ch)) (ch=='-')?flag=-1:1,ch=getchar();
	while(isalnum(ch)) res=res*10+ch-'0',ch=getchar();
	return res*flag;
}
struct Stack
{
	int head;
	std::pair<int,int> val[200010];
	void push(pair<int,int> value)
	{
		val[++head]=value;
		return ;
	}
	void pop() { head--; return ; }
	pair<int,int> top() { return val[head]; }
	bool empty() { return !head; }
	void clear() { head=0; return ; }
	int solve(int pos)
	{
		int left=1,right=head,res=head+1;
		while(left<=right)
		{
			int mid=(left+right)>>1;
			if(val[mid].second<pos)
				res=mid,right=mid-1;
			else
				left=mid+1;
		}
		if(res==head+1)
			return 0;
		return head-res+1;
	}
};
struct Stack a,b;
int n;
long long ans;
void solve(int left,int right,vector<pair<int,int> > val)
{
	b.push(make_pair(0x3f3f3f3f,0x3f3f3f3f));
	if(left==right)
	{
		ans+=val.size()-1;
		return ;
	}
	int mid=(left+right)>>1;
	vector<pair<int,int> > l,r;
	l.clear(),r.clear();
	for(auto i=val.begin();i!=val.end();i++)
	{
		if(i->first<=mid)
		{
			l.push_back(*i);
			while(b.empty()==false&&b.top().first<i->first)
				b.pop();
			ans+=a.solve(b.top().second);
			b.push(*i);
		}
		if(i->first>mid)
		{
			r.push_back(*i);
			while(a.empty()==false&&a.top().first>=i->first)
				a.pop();
			a.push(*i);
		}
	}
	a.clear(),b.clear();
	if(l.size()>=1) solve(left,mid,l);
	if(r.size()>=1) solve(mid+1,right,r);
	return ;
}
int main(int argc,const char *argv[])
{
	n=read();
	int left=INT_MAX,right=0;
	vector<pair<int,int> > val;
	for(int i=1;i<=n;i++)
	{
		int x=read(),y=read();
		val.push_back(make_pair(x,y));
		left=std::min(left,x);
		right=std::max(right,x);
	}
	std::sort(val.begin(),val.end(),[](pair<int,int> a,pair<int,int> b){return (a.second==b.second)?(a.first>b.first):(a.second>b.second);});
	solve(left,right,val);
	printf("%lld\n",ans);
	return 0;
}
```



---

## 作者：Vanilla_0 (赞：0)



[博客](https://blog.csdn.net/Inovation_206/article/details/119040530)

## 思路分析
题目要求我们统计二维平面内的点所构成的不含其他点的矩形个数，因此想到 $cdq$ 分治。

我们先按照横坐标递增排序，这样就只用考虑左下角在 $[l,mid]$ ,右上角在 $[mid+1,r]$ 的矩形，在 $[l,mid]$ 和 $[mid+1,r]$ 内部的矩形可以递归处理。

然后考虑左集合 $A$ 对右集合 $B$ 的影响。枚举 $A$ 中点 $p$ 时，将B中 $y[i] \ge y[p]$ 的点加入单调栈中，同时维护 $x[i]$ 递增。

虽然 $B$ 中的点不会出现在矩形内，但还要考虑A的影响，再用一个单调栈维护 $A$ 中 $x[i]$ 递减，用  $p$ 点在 $B$ 单调栈中二分即可。

注意二分细节较多，需仔细推敲边界及 $mid$ 的取值。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,ans;
int st1[N],st2[N],tp1,tp2;
struct node{
	int x,y;
}s[N];
bool cmp1(node a,node b){return a.x<b.x;}//x从小到大 
bool cmp2(node a,node b){return a.y>b.y;}//y从大到小 
int erfen(int p)
{
	int l=0,r=tp2;//二分栈中第0-tp2个元素
	while(l<r)
	{
		int mid=(l+r+1)>>1;
		if(s[st2[mid]].y>p) l=mid;else r=mid-1;//不可能相等
	}
	return l;
}
void cdq(int l,int r)
{
	if(l==r) return;
	int mid=(l+r)>>1;
	cdq(l,mid);cdq(mid+1,r);
	sort(s+l,s+mid+1,cmp2);
	sort(s+mid+1,s+r+1,cmp2);	
	int j=mid+1;tp1=tp2=0;
	for(int i=l;i<=mid;i++)
	{
		while(j<=r&&s[i].y<s[j].y)
		{
			while(tp2&&s[st2[tp2]].x>s[j].x) tp2--;//维护x单增
			st2[++tp2]=j;j++;
		}
		while(tp1&&s[st1[tp1]].x<s[i].x) tp1--;//维护x单减
		ans+=tp2;if(tp1) ans-=erfen(s[st1[tp1]].y);//如果st1非空
		//这里不能换成lower_bound，因为我们是对结构体的其中一维二分
		st1[++tp1]=i;
	}
}
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld%lld",&s[i].x,&s[i].y);
	sort(s+1,s+1+n,cmp1);
	cdq(1,n); 
	printf("%lld\n",ans);
    return 0;
}
```
最后，友情附赠一组样例：

```cpp
Input      Output
10         15
2 1
3 0
6 3
10 2
16 4
0 8
8 12
11 14
14 11
18 10
```




---

## 作者：lemondinosaur (赞：0)

[洛谷传送门](https://www.luogu.com.cn/problem/AT1225)
[BZOJ 4237 稻草人](http://www.lydsy.com/JudgeOnline/problem.php?id=4237)

---
# 题意
在一个平面直角坐标系上给出$n$个点，

问有多少个点对$(i,j)$满足$x_i<x_j,y_i<y_j$,

而且对于$n$个点中的任意一点都不在以点$i$为左下角，

点$j$为右上角的矩形内部（不包括边界）

---
# 分析
如果没有下面的限制应该是一道二维偏序裸题，但是限制不好搞

考虑用CDQ分治，也就是倘若$[l\sim mid]$和$[mid+1\sim r]$的答案已经弄好，处理区间不同的情况

假设一开始以纵坐标升序排序，

处理完一个区间该区间就以横坐标升序排序，

那也就是能保证$[l\sim mid]$的$y$，

均不超过$[mid+1\sim r]$的$y$，

区间内部的$x$单调不降

枚举右上角的$j$，左下角可以用双指针，

那就可以确定一段左下角区间，因为区间内部$x$单调不降，

所以$[l\sim mid]$的$y$单调不升才能不互相影响，

显然可以用单调栈维护；

那怎样判断右上角有没有影响，

只要查找到$i$左边第一个比它纵坐标小的点$k$就可以了，

显然还是可以用单调栈

然后左下角单调栈可选择的范围就是$x_k\leq x_t\leq x_i$

可以用二分来求，时间复杂度$O(nlog^2n)$

注意AT1225 かかし答案需要换行 ~~（我就说我怎么WA了）~~

还是手画一张图好理解上面的抽象描述

![](https://cdn.luogu.com.cn/upload/image_hosting/pfcmdzos.png)

---
# 代码
```cpp
#include <cstdio>
#include <cctype>
#include <algorithm>
#define rr register
using namespace std;
const int N=200011;
int st2[N],st1[N],n;
long long ans;
struct rec{int x,y;}a[N],b[N];
inline signed iut(){
	rr int ans=0; rr char c=getchar();
	while (!isdigit(c)) c=getchar();
	while (isdigit(c)) ans=(ans<<3)+(ans<<1)+(c^48),c=getchar();
	return ans;
}
bool cmp(rec x,rec y){return x.y<y.y;}
inline signed divid(int l,int r,int z){//二分<z的最大值
	while (l<r){
		rr int mid=(l+r+1)>>1;
		if (a[st2[mid]].x<z) l=mid;
		    else r=mid-1;
	}
	return l;
}
inline void cdq(int l,int r){
	if (l==r) return;
	rr int mid=(l+r)>>1,T1=0,T2=0;
	cdq(l,mid),cdq(mid+1,r);
	for (rr int i=mid+1,j=l;i<=r;++i){
		while (T1&&a[i].y<a[st1[T1]].y) --T1;//右上角单调不降
		st1[++T1]=i;
		for (;a[j].x<a[i].x&&j<=mid;++j){
			while (T2&&a[j].y>a[st2[T2]].y) --T2;//左下角单调不升
			st2[++T2]=j;
		}
		if (a[st2[T2]].x>=a[st1[T1-1]].x)
			ans+=T2-divid(0,T2,a[st1[T1-1]].x);
	}
	rr int i1=l,j1=mid+1,T=0;
   //归并排序模板
	while (i1<=mid&&j1<=r)
	if (a[i1].x<=a[j1].x) b[++T]=a[i1],++i1;
	    else b[++T]=a[j1],++j1;
	while (i1<=mid) b[++T]=a[i1],++i1;
	while (j1<=r) b[++T]=a[j1],++j1;
	for (rr int i=1;i<=T;++i) a[l+i-1]=b[i];
}
signed main(){
	n=iut();
	for (rr int i=1;i<=n;++i)
	    a[i]=(rec){iut(),iut()};
	sort(a+1,a+1+n,cmp),cdq(1,n);
	return !printf("%lld\n",ans);
}
```

---

