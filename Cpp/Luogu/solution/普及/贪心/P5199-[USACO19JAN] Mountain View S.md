# [USACO19JAN] Mountain View S

## 题目背景

USACO 2019 年一月月赛银组第三题

## 题目描述

从农场里奶牛 Bessie 的牧草地向远端眺望，可以看到巍峨壮丽的山脉绵延在地平线上。山脉里由 $N$ 座山峰（$1≤N≤10^5$）。如果我们把 Bessie 的视野想象成 $xy$ 平面，那么每座山峰都是一个底边在 $x$ 轴上的三角形。山峰的两腰均与底边成 $45$ 度角，所以山峰的峰顶是一个直角。于是山峰 $i$ 可以由它的峰顶坐标 $(x_i,y_i)$ 精确描述。没有两座山峰有完全相同的峰顶坐标。

Bessie 尝试数清所有的山峰，然而由于它们几乎是相同的颜色，所以如果一座山峰的峰顶在另一座山峰的三角形区域的边界上或是内部，她就无法看清。

请求出 Bessie 能够看见的不同的山峰的峰顶的数量，也就是山峰的数量。

## 说明/提示

在这个例子中，Bessie 能够看见第一座和最后一座山峰。第二座山峰被第一座山峰掩盖了。

## 样例 #1

### 输入

```
3
4 6
7 2
2 5```

### 输出

```
2```

# 题解

## 作者：Alex_Wei (赞：46)

#### $USACO\ 19JAN\ T3\ Mountain\ View$

虽然看起来比较难，但仔细想想应该就可以找到答案了

#### 思路：

$1.$ 计算出每座山在 $x$ 轴上的左端点 $x-y$ 和右端点 $x+y$，然后按照**左端点从小到大，左端点相同右端点从大到小**的方法排序

$2.$ 从左到右遍历所有的山，**如果当前的山的右端点大于之前所有山的右端点，则答案 $+1$**

### $3.$ 为什么？分两种情况讨论

$3.1$ 当这座山的右端点不大于之前最大的右端点，那么这座山**一定能被之前右端点最大的那座山覆盖**，如图

![](https://cdn.luogu.com.cn/upload/pic/54098.png)

#### $3.2$ 当这座山的右端点大于之前最大的右端点

$3.2.1$ 在这座山之前没有能够覆盖它的山（因为这座山的右端点大于之前所有山的右端点）

#### $3.2.2$ 在这座山之后没有能够覆盖它的山（因为接下来的山要么左端点比这座山大，要么右端点比他小）

$3.2.3$ 综上，得出这座山不会被覆盖，如图

![](https://cdn.luogu.com.cn/upload/pic/54100.png)

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int l,r;
}m[100100];
int n,w,s,x,y;
int cmp(node a,node b){return a.l<b.l||(a.l==b.l&&a.r>b.r);}//排序方法
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>x>>y,m[i].l=x-y,m[i].r=x+y;//算出左右端点
	sort(m+1,m+n+1,cmp);
	for(int i=1;i<=n;i++)if(m[i].r>w)s++,w=m[i].r;//如果大于当前所有山的右端点，答案+1，更新最大右端点
	cout<<s;
	return 0;
}
```

#### 珍爱生命，远离抄袭！

如果有错误或建议欢迎在右侧->评论区指正或私信给我，谢谢！

求赞QAQ

$Update \ 2019.6.30\ \text{修改一处笔误，美化排版}$

---

## 作者：By_Ha (赞：5)

- 用了个自己的算法,目前能`rk1`,欢迎优化吊锤我.
- 好多人都用左右端点做,要计算左右端点,所以就跑的慢.虽然大头还是`sort`排序,但是架不住常数小跑的快.
- 其实这题是我们考试题,考试的时候除了我之外好像都用的别人的那种算法,~~谁让考试还有网.~~
- 那么,怎么做呢?使用单调队列(这个单调队列比较特殊,像栈,不会从队尾出队).
- 我们先将山读入,只记录`x,y`坐标,然后根据`x`坐标排序,从左到右考虑.
- 有这样几种情况(初始化答案为山的个数):
    - 这座山不被完全覆盖        -> 加入队首.
    - 这座山被完全覆盖         -> 不加入队列,答案减一.
    - 这座山完全覆盖前面的山     -> 前面的山出队,答案减一,再次检测.
- 还有些小细节代码中考虑.
- 为什么这样一定是对的呢?因为右边的山如果更高,最先覆盖的肯定是左边最靠近它的,然后才能覆盖再向左的,(注意我们这里的左边的山是已经经过处理了的).
- 复杂度,每个点进队一次,出队一次,$O(N)$,加上排序$O(NlogN)$.

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
#define Rint register int
inline int qr(){int ret=0,f=1;char ch = getchar();while(!isdigit(ch))f=ch=='-'?-1:1,ch=getchar();while(isdigit(ch))ret=ret*10+ch-'0',ch=getchar();return ret*f;}
//快读
struct MTS{
    int x,y;
    inline MTS (int a,int b){x=a,y=b;}
    inline MTS (){}
}M[100005];//存山
struct que{
    MTS q[100005];int End;
    inline void push(MTS a){q[++End] = a;}
    inline void pop(){End--;}
    inline MTS front(){return q[End];}
    inline bool empty(){return End==0;}
}q;//队列,手写快
inline bool operator < (MTS a,MTS b){return a.x<b.x;}
#define Abs(x,y) (x>y?x-y:y-x)
//求绝对值
int main() {
    q.End = 0;
    Rint N = qr();
    Rint ans = N;
    for(Rint i = 1;i<=N;++i)
        M[i].x = qr(),M[i].y = qr();
    sort(M+1,M+N+1);//排序,按山坐标从左到有,复杂度瓶颈
    for(Rint i = 1,x,y,ins;i<=N;++i){
        x = M[i].x,y = M[i].y;ins = 0;
        if(!q.empty())
            while(!q.empty()){//循环看这座山与前面的山是否覆盖
                if(Abs(q.front().y,y) < Abs(q.front().x,x)){//这座山不能与前面的山互相覆盖
                    q.push(MTS(x,y));//插入队首
                    ins = 0;//已经插入,不再插入
                    break;//退出循环
                }
                else {
                    if(q.front().y >= y) {ans--;break;}//被前面的山覆盖
                    else {ans--;q.pop();ins=1;}//覆盖前面的山
                }
            }
        else q.push(MTS(x,y));//如果队列中没有东西直接插入
        if(ins) q.push(MTS(x,y));//如果打了ins标签要插入
    }
    printf("%d",ans);//输出答案
    return 0;
}
```

---

## 作者：一只书虫仔 (赞：3)

#### Description

> 给定 $N$ 个等腰直角三角形的直角顶点坐标，求能看见多少个直角三角形（即求被覆盖了多少三角形，然后用 $N$ 去减）。

#### Solution

不难得知，知道了一个直角三角形的直角顶点坐标，就能确定这个直角三角形了。

确定两个等腰直角三角形覆盖，只需要判断他们的另外两个非直角顶点坐标形成的区间是否相互覆盖即可。

如果一个等腰直角三角形的顶点是 $(x,y)$，那么两个非直角顶点坐标为 $(x-y,0)$，$(x+y,0)$。

证明：我们从直角顶点向 $x$ 轴做垂线，不难得知，交 $x$ 轴于点 $(x,0)$。线段 $(x,0) \to (x,y)$ 把等腰直角三角形分割成了两个小的等腰直角三角形，所以两边的非直角顶点的坐标也就知道了。

所以，我们对 $N$ 个区间 $[x-y,x+y]$ 进行查找未被覆盖区间即可。

这个可以用贪心做，$O(n)$，代码就出来了。

#### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

struct line {
	int l, r;
} seg[100086];

bool cmp (line x, line y) {
	if (x.l != y.l) return x.l < y.l;
	return x.r > y.r;
}

int main () {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		seg[i].l = x - y;
		seg[i].r = x + y;
	}
	sort(seg + 1, seg + n + 1, cmp);
	int L = seg[1].l, R = seg[1].r;
	int cnt = 1;
	for (int i = 2; i <= n; i++)
		if (seg[i].r > R) {
			cnt++;
			R = seg[i].r;
		}
	printf("%d", cnt);
	return 0;
}
```

By Shuchong     
2020.10.5

---

## 作者：Rbu_nas (赞：3)

本题理解题意就很好写了，模拟思路很好想。

注意一下「山」是沿$x$轴正方向蔓延的，并不是排成一列然后站在队首观望山峰的，也就是说我们预处理一下等腰直角三角形的左端点和右端点，不要被大的山所覆盖就好了。然后由于是等腰直角三角形，计算端点也没啥好说的

![](https://cdn.luogu.com.cn/upload/pic/53256.png)

剩下的就是模拟了，加了快读跑到了rk1：

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

#define gcc getchar
template <typename T> inline void read(T&x)
{
    x=0; bool f=true; char ck=gcc();
    for( ; ck<'0'||ck>'9'; ck=gcc()) if(ck == '-') f=false;
    for( ; ck>='0'&&ck<='9'; ck=gcc()) x=(x<<1)+(x<<3)+(ck^48);
    x=f?x:-x; return ;
}

#define N 100003
int n, maxr, res;

struct Node
{
    int l, r;
    bool operator < (const Node&other) const
    {
        return (l != other.l) ? (l < other.l) : (r > other.r);
    }
    //按左端点作为关键字排序，如果一样那么只能看到大的山了
} ;

Node a[N];

int main(void)
{
    read(n);
    for(int i=1; i<=n; ++i)
    {
        int x, y; read(x), read(y);
        a[i].l=x-y, a[i].r=x+y;
        //简单的预处理，如果不是等腰直角三角形也一样作垂线用三角函数
    }
    sort(a+1, a+n+1);
    for(int i=1; i<=n; ++i)
        if(a[i].r > maxr) ++res, maxr=a[i].r;
    //每一次更新最右端点，不超过maxr的则会被大山包含    
    printf("%d", res);
    return 0;
}

```

---

## 作者：SUNCHAOYI (赞：2)

## 这道题与数学有一定的关系
**因为是等腰直角三角形，所以可以作它的中垂线，则两个底边到中垂线的距离相等**

------------

**代码如下：**
```
#include<iostream>
#include<algorithm>
using namespace std;
const int MAX=100000;
int x[MAX],y[MAX],r[MAX],l[MAX],h[MAX];
bool cmp(int a,int b)
{
	if(l[a]==l[b])//左边相同时，将右边进行比较（大的覆盖面积大） 
	{
		if(r[a]>r[b])return 1;
		else return 0;
	}
	else//否则直接比左边 （小的覆盖面积大） 
	{
		if(l[a]<l[b])return 1;
		else return 0;
	}
}
int main()
{
	int n,ans=0,maxh=-1;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>x[i]>>y[i];
		r[i]=x[i]+y[i];l[i]=x[i]-y[i];//左右边位置 
		h[i]=i;//每座山高度 
	}
	sort(h,h+n,cmp);//排序 
	for(int i=0;i<n;i++)
	{
		if(r[h[i]]>maxh)//计算当前是否能看见 
		{
			ans++;
			maxh=r[h[i]];//覆盖原值，记录最高值 
		}
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：Polarnova (赞：2)

一个很容易想到的思路是由于山是等腰三角形，考虑比较两边山脚位置来判断山是否会包含。
```cpp
#include<cstdio>
long long x[100003],y[100003],tot,n;
int main() {
	scanf("%d",&n);tot=n;
	for(int i=1;i<=n;i++) scanf("%lld%lld",&x[i],&y[i]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)if(i!=j)
			if(y[j]+x[j]>=y[i]+x[i]&&x[j]-y[j]<=x[i]-y[i]){tot--;break;}
	printf("%d",tot);
	return 0;
}
```

---

## 作者：Soledad_S (赞：1)

[无耻地安利博客](https://www.cnblogs.com/soledadstar/p/11548762.html)

~~不会推结论，单调队列万岁！~~
> 题目大意: 给出若干个等腰直角三角形的顶点，要求有多少个点没有被其他三角形覆盖

先按$x$坐标对顶点排序，单调队列维护所有未被覆盖的点，对于$i$，把它可以覆盖的点从队尾弹出(即队尾元素的左端点≥i的左端点)，执行完操作后，如果$i$未被现在的队尾覆盖就入队。

最后队内元素个数就是答案
```
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<deque>
using namespace std;
inline int read() {
	char ch;
	int bj=1;
	while(!isdigit(ch=getchar()))
		bj=(ch=='-')?-1:1;
	int res=ch^(3<<4);
	while(isdigit(ch=getchar()))
		res=(res<<1)+(res<<3)+(ch^(3<<4));
	return res*bj;
}
void printnum(int x) {
	if(x>9)printnum(x/10);
	putchar(x%10+'0');
}
inline void print(int x,char ch) {
	if(x<0) {
		putchar('-');
		x=-x;
	}
	printnum(x);
	putchar(ch);
}
int n,ans;
struct node {
	int x,y;
	inline bool operator < (node a)const {
		return x<a.x;
	}
} a[100005];
deque<int>q;
int main() {
	n=read();
	for(int i=1; i<=n; i++) {
		a[i].x=read();
		a[i].y=read();
	}
	sort(a+1,a+n+1);
	for(int i=1; i<=n; i++) {
		while(!q.empty()&&a[q.back()].x-a[q.back()].y>=a[i].x-a[i].y)q.pop_back();
		if(!q.empty()&&a[q.back()].x-a[q.back()].y<=a[i].x-a[i].y&&a[q.back()].x+a[q.back()].y>=a[i].x+a[i].y)continue;
		q.push_back(i);
	}
	print(q.size(),'\n');
	return 0;
}
```


---

## 作者：湫泷 (赞：1)

看大家都是计算左右端点的，我就想了想能不能比较高度呢？

结果发现是可以的

我们对所有山按高度从大到小排序依次枚举i作为参照，在枚举所有高度比i小的j，判断一下j是否被i遮住，如果被遮住，那么当i枚举到j时就自动跳过（所有被j遮住的山同样已经被i遮住了），并标记这座山看不见，最后枚举统计一下答案就好了

```cpp
#include<bits/stdc++.h>
#define N 100010
using namespace std;
inline int read(){
	int f=1,x=0;
	char s=getchar();
	while(s<'0'||s>'9'){
		if(s=='-'){
			f=-1;
		}
		s=getchar();
	}
	while(s>='0'&&s<='9'){
		x=x*10+s-'0';
		s=getchar();
	}
	return f*x;
}
int n,flag[N];
struct node{
	int x,y;
}a[N];
bool cmp(const node x,const node y){
	return x.y>y.y;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i].x=read(),a[i].y=read();
	}
	sort(a+1,a+1+n,cmp);//按高度排序
	for(int i=1;i<=n;i++){
		if(flag[i]==1){
			continue;
		}//如果这座山已经被别的山所遮挡，那么久不对这座山操作
		int l=a[i].x-a[i].y,r=a[i].x+a[i].y;//算出这座山的左右端点
		for(int j=i+1;j<=n;j++){
			if(a[j].x>r||a[j].x<l){
				continue;
			}//不在两端点之间的跳过
			if(a[j].x==a[i].x){
				flag[j]=1;
				continue;
			}
			int high=a[i].y-abs(a[i].x-a[j].x);//算出j山对上去能到达的高度（自己用笔画画，我实在讲不清楚）
			if(high>=a[j].y){
				flag[j]=1;
				continue;
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		if(flag[i]==0){
			ans++;
		}
	}
	printf("%d\n",ans);//输出答案
	return 0;
}
```


---

## 作者：CBD666 (赞：1)

判断一座山峰是否被遮挡其实就是看它的两个山脚所表示的区间是否被其他区间包含，用树状数组维护即可


```cpp
#include<map>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=1e5+5;
int n,ans,tot,a[N<<1],b[N<<1];
struct node {
	int l,r;
	bool operator<(const node &b) {
		if(r==b.r)return l>b.l;
		return r<b.r;
	}
} w[N];
map<int,int>d;
void add(int x) {
	for(; x<=n*2; x+=x&-x)++b[x];
}
int find(int x) {
	int ret=0;
	for(; x>0; x-=x&-x)ret+=b[x];
	return ret;
}
int main() {
	scanf("%d",&n);
	ans=n;
	for(int i=1; i<=n; ++i) {
		int x,y;
		scanf("%d%d",&x,&y);
		a[i*2-1]=w[i].l=x-y;
		a[i*2]=w[i].r=x+y;
	}
	sort(a+1,a+n*2+1);
	tot=unique(a+1,a+n*2+1)-a-1;
	for(int i=1; i<=tot; ++i)d[a[i]]=i;
	for(int i=1; i<=n; ++i)w[i].l=d[w[i].l],w[i].r=d[w[i].r];//数据1e9,离散化一下 
	sort(w+1,w+n+1);
	for(int i=n; i>=1; --i) {
		if(find(w[i].l))--ans;
		add(w[i].l);
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：Na2PtCl6 (赞：0)

差劲做法 + 玄学剪枝 (乱搞) $\rightarrow$ AC

## 分析题目 

设山峰 $a$ 的峰顶坐标为 $(x1,y1)$ , 山峰 $b$ 的峰顶坐标为 $(x2,y2)$ $(y1 \ge y2)$


$\because$ 山峰是底在 $x$ 轴上的等腰直角三角形

$\therefore$ $(x-k,y-k)$ 和 $(x+k,y-k)$ 一定在这个山峰上 

$\therefore$ 一个山峰被另一个山峰覆盖时，满足 
$x1-(y1-y2) \leq x2 \leq x1+(y1-y2))$

## 代码实现
根据上面的结论，我们就有了一个 $O(n^2)$ 的做法：

因为要保证 $(y1 \ge y2)$ ,所以我们先将点按 $y$ 坐标 从大到小排序， 然后从前往后循环每一个点 ， 并对下标大于这个点的点进行判断 ， 如果满足$x1-(y1-y2) \leq x2 \leq x1+(y1-y2))$
的点就做标记

剪枝：我们可以发现，在枚举的过程中，某些山峰总是会被多次标记，我们可以让第二层循环不枚举标记过的山峰

代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
char book[100004];
int n,res;
struct point{
	double x,y;
	bool operator < (const point &a){ return a.y<y;}
}s[100004];

int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%lf%lf",&s[i].x,&s[i].y);
	sort(s,s+n);
	for(int i=0;i<n;i++){
		if(book[i])
			continue;
		for(int j=i+1;j<n;j++){
			double k=s[i].y-s[j].y;
			if(s[j].x>=s[i].x-k&&s[j].x<=s[i].x+k)
				book[j]=1;
		}	
	}
	for(int i=0;i<n;i++)
		if(!book[i])
			++res;
	printf("%d",res);	
	return 0;
}
```

---

## 作者：Priori_Incantatem (赞：0)

首先我们必须考虑怎么求每个三角形的两个底角

显然的，因为该三角形两腰与$x$轴的夹角都为$45$度，所以两腰所在直线的斜率 $k$ 则为$1,-1$  
而我们又可以根据直角顶点求出两条直线平移的长度，也就是 $b$ 。这样，两直线解析式就求出来了，那么该三角形在$x$轴上的两个顶点坐标就是两直线与$x$轴的交点

接着，我们设每个三角形在$x$轴上的顶点的横坐标为$l,r$ $(l\le r)$，并对他们排个序，具体操作如下
```cpp
struct node{
	int l,r;
	int x,y;
	void work() //求出每个三角形的 l,r
	{
		int tmp=y-x;
		l=-tmp;
		tmp=(y+x);
		r=tmp;
	}
};
node a[Maxn];
inline bool cmp(node u,node v)
{
	if(u.l==v.l)return u.r>v.r;
	return u.l<v.l;
}
```

然后，我们枚举每一个三角形，并把它所包含的所有三角形跳过，最后统计并输出答案

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int Maxn=100000+10;
struct node{
	int l,r;
	int x,y;
	void work()
	{
		int tmp=y-x;
		l=-tmp;
		tmp=(y+x);
		r=tmp;
	}
};
node a[Maxn];
int n,ans;
inline bool cmp(node u,node v)
{
	if(u.l==v.l)return u.r>v.r;
	return u.l<v.l;
}
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("mountains.in","r",stdin);
//	freopen("mountains.out","w",stdout);
	n=read();
	for(int i=1;i<=n;++i)
	{
		a[i].x=read(),a[i].y=read();
		a[i].work();
	}
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;++i)
	{
		int j=i+1;
		while(a[i].r>=a[j].r && j<=n)++j;
		i=j-1,++ans;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：zylll (赞：0)

因为可以通过给出的坐标而算出等腰三角形的左右范围，故算出范围后，以左端点进行关键字排序，即保证形成一个左端点依次变大，当左端点相同时返回高度高的。

之后O(n)遍历，维护一个序列最小左端点和最大右端点，统计答案即可。

```
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
static const int MAXN=100050;
using namespace std;
struct node
{
    int x,y,l,r;
}p[MAXN];
int n,rl,rr,ans;
inline bool cmp(node a,node b)
{
    if(a.l==b.l) return a.y>b.y;
    return a.l<b.l;
}
inline int read()
{
    int x=0;bool sign=false;
    char alpha=0;
    while(!isdigit(alpha)) sign|=alpha=='-',alpha=getchar();
    while(isdigit(alpha)) x=(x<<1)+(x<<3)+(alpha^48),alpha=getchar();
    return sign?-x:x;
}
int main()
{
    freopen("mountains.in","r",stdin);
    freopen("mountains.out","w",stdout);
    n=read();
    for(int i=1;i<=n;i++)
    {
        p[i].x=read();p[i].y=read();
        p[i].l=p[i].x-p[i].y,p[i].r=p[i].x+p[i].y;
    }
    sort(p+1,p+n+1,cmp);
    for(int i=1;i<=n;i++)
    {
        if(p[i].l>=rl&&p[i].r<=rr) ans--;
        rl=min(rl,p[i].l),rr=max(rr,p[i].r);
    }
    printf("%d\n",ans+n);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
```

[分享一波自己的博客qwq，USACO 2019 January Contest, Silver](https://beyondlimits.site/1118.html)

---

