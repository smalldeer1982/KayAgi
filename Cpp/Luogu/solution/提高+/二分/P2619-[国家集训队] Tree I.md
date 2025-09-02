# [国家集训队] Tree I

## 题目描述

给你一个无向带权连通图，每条边是黑色或白色。让你求一棵最小权的恰好有 $need$ 条白色边的生成树。

题目保证有解。


## 说明/提示

对于 $5\%$ 的数据，$V\leq 10$。

对于另 $15\%$ 的数据，$V\leq 15$。

对于 $100\%$ 的数据，$V\leq 5\times10^4,E\leq 10^5$。

所有数据边权为 $[1,100]$ 中的正整数。


By WJMZBMR


## 样例 #1

### 输入

```
2 2 1
0 1 1 1
0 1 2 0```

### 输出

```
2```

# 题解

## 作者：Gary818 (赞：128)

### 这个题吧，说难也不难，说简单也不简单 ###  
其实题目给的很明确  
**让你求一棵最小权的恰好有need条白色边的生成树。**   
这不是明摆着要求最小生成树吗？  
刚要开始写，问题接踵而至，这个白边的数量怎么控制呢，如果多了或者少了，如何增减？ 

进入正题：
总所周知，在跑kruskal的时候，我们有这样一句代码：
```cpp
sort(e+1,e+1+m,cmp);
```
这是对边进行排序，由此可知，边权越小越靠前  
我们可以通过改变白边的权值来改变它出现的位置 


例如need=3，但是此时我的最小生成树上有4条白边，那么我可以全部加上一个数，然后某条白边突然比最小的黑边大了，我再跑kruskal，更新之后的最小生成树就会把一条大的白边扔到后边去，替换成一条黑边，那么此时白边条数就少了1，满足答案，统计答案时把加的这个数减掉就行了  

现在我们来说说怎么确定要加的这个数   
我们采取二分答案的办法，因为题目中说道边权在[1,100]所以定义l=-111,r=111,然后二分往白边上加权值，最后一定能卡出来一个合适的解  

那么问题又来了，如果说当前白边加上mid后，白边条数temp>need了，然鹅，如果加上mid+1后，temp<need了，这可咋整，难搞哟~~  

题目中说到了：保证有解，所以出现上述情况时一定有黑边==白边的边权  
so，我们只需要把一条黑边换成白边就好啦  
在白边条数temp>need时更新答案  
最终答案$ ans=sum-mid×need $

代码时间：
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int fa[1000010];
int n,m,need;
struct node{
	int s,t,v,c;//起点、终点、权值、颜色
}e[1000010];

inline bool cmp(node a,node b){//排序
	if(a.v==b.v) return a.c<b.c;
	else return a.v<b.v;
}

inline int find(int x){//并查集不会赶紧学去
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}

int sum,ans,temp;
int cnt=0;
inline void kruskal(){//板子
	sort(e+1,e+1+m,cmp);
	for(int i=1;cnt!=n-1;i++){
		int xx=find(e[i].s),yy=find(e[i].t);
		if(xx==yy) continue;
		if(xx!=yy){
			cnt++;
			fa[xx]=yy;
			if(e[i].c==0) temp++;//统计白边数量
			sum+=e[i].v;
		} 
	}
}

int main(){
	cin>>n>>m>>need;
	for(int i=1;i<=m;i++){
		cin>>e[i].s>>e[i].t>>e[i].v>>e[i].c;
		e[i].s++,e[i].t++;//注意！因为题面说0开始标号
	}
	int l=-111,r=111;//二分，初始值比100大就行
	while(l<=r){
		int mid=(l+r)>>1;
		for(int i=1;i<=m;i++)
			if(e[i].c==0)
				e[i].v+=mid;//白边加权
		for(int i=1;i<=n+1;i++)
			fa[i]=i;//初始化
		sum=0,cnt=0,temp=0;//每次要清空
		kruskal();
		if(temp>=need){
			l=mid+1;
			ans=sum-need*mid;//更新答案
		}
		else r=mid-1;
		for(int i=1;i<=m;i++)
			if(e[i].c==0)
				e[i].v-=mid;//最终要把加上的减掉
	}
	cout<<ans<<'\n';//over
	return 0;
}
```
感觉讲的挺明白了叭，不懂评论区见，溜~~~

---

## 作者：FlashHu (赞：93)

这个。。。好像至少在算法复杂度上做了一点点改进，不是完全重复吧qwq。。。求管理员大大放过qwq

给一个名词——WQS二分/带权二分/DP凸优化（当然这题不是DP）。

用来解决一种特定类型的问题：

有$n$个物品，选择每一个都会有相应的权值，需要求出强制选$need$个物品时的最大/最小权值和。

一般来说，我们求不限制个数的最大/最小权值和很容易，但在限制个数的前提下再求最值会变得有点困难。比较低效的做法是对状态再加设一个维度表示已选物品数量，然后通过DP等方法求出。

应用前提：设$g_x$为强制选$x$个物品的最大/最小权值和，如果所有的点对$(x,g_x)$在平面上能够构成一个凸包，那么可以考虑使用WQS二分。

所以说用三个名词合指它也不为过（提出者WQS，二分的量是权值增量，使用前提是凸函数）

WQS的论文[这里](http://www.tsinsen.com/resources.page)可以下载

建议食用[Creeper_LKF大佬的blog](https://www.cnblogs.com/CreeperLKF/p/9045491.html)，数形结合的分析过程已经非常完整了。

简单的来说，我们不能知道这个凸包长什么样子，但我们可以拿着一个斜率为$k$的直线去切这个凸包，相当于给每个物品附加了一个权值$k$。设直线的截距为$b$，那么选$x$个物品后总权值就会等于$b+kx$。我们通过$O(n)$的DP等方法找到最大的$b$，同时也可以求出选了的个数$x$，通过$x$与$need$的关系来调整直线斜率继续二分。

拿本题来说，选$x$条白边，可以~~写个平方DP然后~~发现$g_x$是个下凸函数。然后我们在$[-100,100]$（显然是斜率的上下界，因为更改一条边带来的权值和的更改不会超过$100$）的范围内二分$k$，之后所有白边的权值增加$k$，跑一遍Kruscal统计选了多少条白边。如果这个数量大于等于$need$就调大$k$，否则调小。

最后斜率为$mid$的直线与凸包的切点就是答案，注意从中减去$k$的影响（`ans-=mid*x`）

边界问题Creeper_LKF大佬也证明了只要在边权相等的时候优先选白边就没问题了。

写法上有一个优化：每次Kruscal的时候不用重新排序了。因为每次我们只是给所有白边整体加一个权值，所以如果我们先把白边和黑边分开排序的话，加完以后也还是有序的。每次Kruscal时只要用类似归并排序的方法$O(E)$的扫一遍就可以啦！复杂度从$O(E\log E\log 200)$降到了$O(E\log E+E\log200)$。

```cpp
#include<cstdio>
#include<algorithm>
#define RG register
#define R RG int
#define G if(++ip==iend&&fread(ip=buf,1,N,stdin))
using namespace std;
const int N=5e5+9,M=1e6+9;
char buf[N],*iend=buf+N,*ip=iend-1;
inline int in(){
	while(*ip<'-')G;
	R x=*ip&15;G;
	while(*ip>'-'){x=x*10+(*ip&15);G;}
	return x;
}
struct Edge{
	int u,v,w;bool c;
	inline bool operator<(RG Edge&x){
		return w<x.w;
	}
}e[M];
int f[N];
int getf(R x){
	return x==f[x]?x:f[x]=getf(f[x]);
}
inline bool add(R i){//尝试加边并返回是否成功
	if(getf(e[i].u)==getf(e[i].v))return 0;
	f[f[e[i].u]]=f[e[i].v];return 1;
}
int main(){
	R n=in(),mw=0,m=in(),need=in(),i,j;//mw为白边数量
	for(i=0;i<m;++i){//点和边都从0开始存了
		e[i].u=in();e[i].v=in();e[i].w=in();
		if(!(e[i].c=in()))swap(e[mw++],e[i]);//将黑白边分开
	}
	sort(e,e+mw);sort(e+mw,e+m);
	R l=-100,r=100,mid,ans;
	while(l<r){
		mid=(l+r+1)>>1;
		for(i=0;i<n;++i)f[i]=i;
		ans=i=0;j=mw;
		while(i<mw&&j<m)//类归并排序
			e[i].w+mid<=e[j].w?ans+=add(i++):add(j++);
		while(i<mw)ans+=add(i++);//白边数量统计完整
		ans<need?r=mid-1:l=mid;
	}
	mid=l;
	for(i=0;i<n;++i)f[i]=i;
	ans=i=0;j=mw;//最后算权值总和
	while(i<mw&&j<m)
		if(e[i].w+mid<=e[j].w)
			ans+=(e[i].w+mid)*add(i),++i;
		else ans+=e[j].w*add(j),++j;
	while(i<mw)ans+=(e[i].w+mid)*add(i),++i;
	while(j<m )ans+=e[j].w*add(j),++j;
	printf("%d\n",ans-need*mid);//减掉
	return 0;
}
```

---

## 作者：HDWR (赞：31)

~~年轻人的第一道国家集训队题目~~

---

如果我们不做任何处理，直接跑MST（Minimum Spanning Tree，最小生成树），结果会有三种：

- 正好跑出 $\text{Need}$ 条白边

- 白边多了

- 白边少了

第一种情况自然是最好的

剩下两种情况如何解决？

---

引起白边少的原因：黑边的边权相对较小，程序贪心地选择了更多的黑边

引起白边多的原因：白边的边权相对较小，程序贪心地选择了更多的白边

那么如果我们给白边相应地减去/加上一些边权，不就可以达成目标了？

---

考虑二分答案。

我们二分一个 $add$ 表示我们当前要给白边加上 $add$ 来达成目标

边界分别是边权最小值（-100）和边权最大值（100）

由于题面保证有答案，所以直接输出 $ ans - add \times \text{Need} $
 即可，其中 $ans$ 为（加上边权后）最小生成树的权值和
 
`Check(mid)` 怎么写？

---

我们将所有白边的边权加上$add$（即$mid$），跑一遍最小生成树，判断一下拿到的白色边数量是否大于等于要求的数量，如果是就更新一下左边界并记当前的$mid$为$tans$，否则就更新一下右边界

注意不要忘了把边权减回来

（不要在意 $tans$ 是什么意思）

---

刚才我们不是记录了一下$tans$吗，这个$tans$就相当于是一个正确的、能选出正好 $\text{Need}$ 条白边的 $add$ 值，再将所有白边的边权都加上这个 $tans$，跑一遍最小生成树即可

答案不要忘了减去加上的边权（也就是 $ \text{Need} \times tans $）

那么最后的答案就是 $ \text{Kruskal()} - \text{Need} \times tans $

# 代码实现
```cpp
#include <algorithm>
#include <iostream>
#include <cstdio>

#define FILE_IN(__fname) freopen(__fname, "r", stdin)
#define FILE_OUT(__fname) freopen(__fname, "w", stdout)
#define IMPROVE_IO() std::ios::sync_with_stdio(false)

#define WHITE 0
#define BLACK 1

using std::cin;
using std::cout;
using std::endl;
using std::max;

const int MAXV = 50000 + 10;
const int MAXE = 100000 + 10;
const int MAXW = 100;

struct Edge {
    int prev, next, weight, add;
    bool color;
    // 1 -> black, 0 -> white
    
    Edge() { prev = next = weight = color = add = 0; }
    
    bool operator < (const Edge &that) const {
        if (weight == that.weight) return color < that.color;
        return weight < that.weight;
    }
} edge[MAXE << 1];

int V, E, Need, cnt, ans;

int U[MAXV << 1];

int Find(int x) {
    if (U[x] == x) return U[x];
    return U[x] = Find(U[x]);
}

bool Union(int x, int y) {
    x = Find(x), y = Find(y);
    if (x == y) return false;
    U[x] = y;
    return true;
}

int Kruskal() {
    int whiteEdge = 0;
    for (int i = 1; i <= V; ++i) U[i] = i;
    std::sort(edge + 1, edge + 1 + E);
    int tot = 0;
    ans = 0;
    for (int i = 1; i <= E; ++i) {
        if (Union(edge[i].prev, edge[i].next)) 
            ans += edge[i].weight, ++tot, whiteEdge += (edge[i].color == WHITE);
        if (tot == V - 1) break;
    }
    return whiteEdge;
}

bool Check(int add) {
    for (int i = 1; i <= E; ++i) {
        if (edge[i].color == WHITE) edge[i].weight += add;
    }
    bool Ans = (Kruskal() >= Need);
    for (int i = 1; i <= E; ++i) {
        if (edge[i].color == WHITE) edge[i].weight -= add;
    }
    return Ans;
}

int main() {
    IMPROVE_IO();
    cin >> V >> E >> Need;
    for (int i = 1; i <= E; ++i) {
    	cin >> edge[i].prev >> edge[i].next >> edge[i].weight >> edge[i].color;
    	++edge[i].prev;
        ++edge[i].next;
    }
    int l = -MAXW, r = MAXW;
    int Run = 0;
    while (l <= r) {
        int mid = ((l + r) >> 1);
        if (Check(mid)) {
            l = mid + 1;
            Run = mid;
        } else {
            r = mid - 1;
        }
    }
    Check(Run);
    cout << ans - Need * Run << endl;
    return 0;
}

```

---

## 作者：Drinkkk (赞：27)

【参考资料】

liusu201601的博客：https://blog.csdn.net/liusu201601/

【题目描述】

给你一个无向带权连通图，每条边是黑色或白色。让你求一棵最小权的恰好有$need$条白色边的生成树。题目保证数据有解。

【输入输出格式】

- 输入格式

第一行$V,E,need$分别表示点数，边数和需要的白色边数。

接下来E行，每行有五个整数$s,t,c,col$，分别表示这边的端点(点从0开始标号)，边权，颜色(0白色1黑色)。

- 输出格式

一行表示所求生成树的边权和。

$100$分（满分）思路：

- 我会最小生成树！

- 一种错误的解法

题目要求的是一棵最小权的恰好有$need$条白色边的生成树。那我们直接选择$need$条白边，然后再选剩下的边咯。但是，这是错误的，为什么呢？请看下面的这组数据。
```
3 4 1
0 1 5 0
1 2 6 0
0 1 2 1
1 2 9 1
```

输出是8。

为什么不能够直接选择$need$条白边呢？因为如果我们选了$need$条较小的白边，那么可能会影响黑边的选择。

- 正解

1. 如果对全部边进行排序，跑最小生成树，我们可以得到最优的$ans$，但是白边不一定是$need$条；

2. 如果白边少了，说明白边整体权值比较大，所以没被选中。那我就对边都减一点权（$x$），这样的话，被选中的白边会增多。同理，如果被选白边数量大于$need$，我就给白边们都减去一个$x$。

3. 接下来，我们二分这个$x$，就可以得到（我想要的白边数量的前提下）的最小生成树。

- 一些要注意的细节

1. 黑白边同权的时候，优先选择白边。

下面上$100$分代码~

```
#include <cstdio>
struct node{ int s,t,c,col; } e[1000001];
int p1=0,p2=0,su=0,n=0,m=0,t=0,l=0;
int f[1000001];
int find(int x)
{
	if(x==f[x])
	{
		return x;
	}
	else
	{
		return f[x]=find(f[x]);
	}
}
void px(int l,int r)
{
	int x=l,y=r,mid1=e[(l+r)/2].c,mid2=e[(l+r)/2].col;
	while(x<=y)
	{
		while((e[x].c<mid1) || (e[x].c==mid1 && e[x].col<mid2))
		{
			x++;
		}
		while((e[y].c>mid1) || (e[y].c==mid1 && e[y].col>mid2))
		{
			y--;
		}
		if(x<=y)
		{
			node pt=e[x];
			e[x]=e[y];
			e[y]=pt;
			x++;
			y--;
		}
	}
	if(l<y)
	{
		px(l,y);
	}
	if(x<r)
	{
		px(x,r);
	}
}
bool check(int mid)
{
	l=0;
	for(int i=1;i<=n;i++)
	{
		f[i]=i;
	}
	for(int i=1;i<=m;i++)
	{
		if(e[i].col==0)
		{
			e[i].c+=mid;
		}
	}
	su=0;
	px(1,m);
	p1=0,p2=0;
	for(int i=1;i<=m;i++)
	{
		int tx=find(e[i].s);
		int ty=find(e[i].t);
		if(tx!=ty)
		{
			f[tx]=ty;
			p1++;
			su+=e[i].c;
			if(e[i].col==0)
			{
				p2++;
			}
			if(p1==n-1)
			{
				break;
			}
		}
	}
	for(int i=1;i<=m;i++)
	{
		if(e[i].col==0)
		{
			e[i].c-=mid;
		}
	}
	if(p2>=t)
	{
		return true;
	}
	else
	{
		return false;
	}
}
int main()
{
	scanf("%d %d %d",&n,&m,&t);
	for(int i=1;i<=m;i++)
	{
		scanf("%d %d %d %d",&e[i].s,&e[i].t,&e[i].c,&e[i].col);
		e[i].s++;
		e[i].t++;
	}
	int l=-150,r=150;
	int ans=0;
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(check(mid)==true)
		{
			ans=su-mid*t;
			l=mid+1;
		}
		else
		{
			r=mid-1;
		}
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：MloVtry (赞：14)


这是个生成树，考虑Kruskal的流程，要想白边数目满足要求就要调整白边的位置，二分一个白边权值偏移量w，每条白边的边权加上这个偏移量之后做Kruskal，并统计使用的白边数量，如果多于k，则白边需要再向后移；小于k白边需要前移，调整偏移量。

最后就可以得到答案。

~~然而我还有一个不成熟的LCT想法不过凉凉了。大概就是用堆维护一下黑边白边然后依据白边数量调整。但是凉凉了。~~

代码


```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#define N 100005
using namespace std;
struct node
{
	int u,v,l,col;
}a[N],b[N];
bool comp(node aa,node bb)
{
	return aa.l==bb.l?aa.col<bb.col:aa.l<bb.l;
}
int f[N],n,m,ned;
int get_f(int now)
{
	return now==f[now]?f[now]:f[now]=get_f(f[now]);
}

int l=-100,r=100,ans,us;
bool canit(int mid)
{
	int tot=ans=0,get=0;
	for(int i=1;i<=m;++i)
	{
		b[i]=a[i];
		if(a[i].col==0) b[i].l+=mid;
	}
	sort(b+1,b+m+1,comp);
	for(int i=1;i<=n;++i) f[i]=i;
	for(int i=1;i<=m;++i)
	{
		int u=get_f(b[i].u),v=get_f(b[i].v);
		if(u==v) continue;
		tot++;
		f[u]=v;ans+=b[i].l;
		get+=b[i].col==0;
		if(tot+1==n) break;
	}
	return get>=ned;
}
int main()
{
	scanf("%d%d%d",&n,&m,&ned);
	for(int i=1;i<=m;++i)
	scanf("%d%d%d%d",&a[i].u,&a[i].v,&a[i].l,&a[i].col),a[i].u++,a[i].v++;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(canit(mid)) l=mid+1,us=mid;
		else r=mid-1;
	}
	canit(us);
	printf("%d\n",ans-ned*us);
	return 0;
}
```

---

## 作者：zijinjun (赞：11)



> 题目描述
给你一个无向带权连通图，每条边是黑色或白色。让你求一棵最小权的恰好有need条白色边的生成树。
https://www.luogu.org/problemnew/show/P2619
输入输出格式
输入格式：
第一行V,E,need分别表示点数，边数和需要的白色边数。
输出格式：
一行表示所求生成树的边权和。
说明
0:V<=10
1,2,3:V<=15
0,..,19:V<=50000,E<=100000
所有数据边权为[1,100]中的正整数。
接下来E行
每行s,t,c,col表示这边的端点(点从0开始标号)，边权，颜色(0白色1黑色)。

首先，分析这道题，是一个关于最小生成树的问题，由于顶点数是50000，我们肯定不能用邻接矩阵，考虑邻接表。
然后，就很容易想到是要跑克鲁斯卡尔啦。

```cpp
int find(int x) {return f[x]==x?x:f[x]=find(f[x]);}

void kruskal(){
	for(int i=1;cnt!=n-1;++i){
		int r1=find(edge[i].start),r2=find(edge[i].end);
		if(r1!=r2) {
			f[find(r1)]=find(r2),cnt++;
			if(edge[i].c==0) temp++;
			    ans+=edge[i].v;
		}
	}
}

```
一个裸的克鲁斯卡尔。。。。
接下来，针对next的值首先可以想到枚举，把每个白边的权值减少一定的值，看减少多少会使最小生成树的白边数正好为need
那么，优化一下，在白边权值不断减少的过程中，白边的数量是递增的，那么满足一个单调的要求，所以，这里可以用二分，二分的正确性也可以由此证明
每次枚举一个mid的值，给每个白边的权值都加上mid，如果这时白边数大于等于need，这时候对mid的值进行减小，反之增加，每次跑一遍克鲁斯卡尔，更新ans的值（ans的值要减去增加的mid的权值）
他的细节处理是非常多的，每次跑克鲁斯卡尔之前都要进行清零（考试时候少清一个调了几百年QAQ）(捂脸）
下面附上AC代码（吐槽一波考试数据的变态，十五个点连了二十万条边）

```cpp
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>
#define FOR(i,n,m) for(int i=n;i<=m;++i)  //一个喜欢用宏定义的懒人，不用在意
#define FR(i,n,m) for(int i=bli>=m;--i)
#define OPEN(n) freopen(n".in","r",stdin); freopen(n".out","w",stdout);
using namespace std;

const int N=102000;
int f[N],n,need,e,l,r,mid,temp,ans,_ans,cnt;
struct node {int start,end,c,v;}edge[N]; 
int find(int x) {return f[x]==x?x:f[x]=find(f[x]);}
bool cmp(node a,node b) {return a.v==b.v?a.c<b.c:a.v<b.v;} //排序，按顺序，如果相同，白边在前

void kruskal(){
	mid=(l+r)>>1;
	FOR(i,1,e) {if(edge[i].c==0) edge[i].v+=mid;}
	FOR(i,1,n+1) f[i]=i;
	ans=0,temp=0,cnt=0; 	//清零
	sort(edge+1,edge+e+1,cmp); 
	for(int i=1;cnt!=n-1;++i){
		int r1=find(edge[i].start),r2=find(edge[i].end);
		if(r1!=r2) {
			f[find(r1)]=find(r2),cnt++;
			if(edge[i].c==0) temp++;
			    ans+=edge[i].v;
		}
	}
}
//克鲁斯卡尔啊啊啊

void in(){
	scanf("%d%d%d",&n,&e,&need);
	FOR(i,1,e){
		scanf("%d%d%d%d",&edge[i].start,&edge[i].end,&edge[i].v,&edge[i].c);
		edge[i].end++;
		edge[i].start++;
	}
}

void work(){
	in();
	l=-105,r=105;
	while(l<=r){
		kruskal();
		if(temp>=need) l=mid+1,_ans=ans-need*mid;
		else r=mid-1;
		FOR(i,1,e) if(edge[i].c==0) edge[i].v-=mid;
	}
	printf("%d",_ans);
}

int main(){
	
	//OPEN("tree")
	//咳咳，考试的文件名
	
	work();
	
	return 0;
}
```

这是本蒟蒻的第一篇博客，各位大佬不要笑话

---

## 作者：大菜鸡fks (赞：7)

新姿势。带权二分。

考虑二分偏移量，对每个白边都加上偏移量，然后做kruscal进行判定。

为什么这样是对的？我的理解是加上偏移量后白边 能被算入生成树的边数是单调的。并且对于所有白边加同一个权值并不会改变白边间的“优先级”——相对顺序，只会改变白边黑边之间的“优先级”。 感性的理解一下。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
inline int read(){int x=0,f=1,ch=getchar(); while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();} while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x*f;}
inline void write(int x){if (x<0) putchar('-'),x=-x; if (x>=10) write(x/10); putchar(x%10+'0');}
inline void writeln(int x){write(x); puts("");}
const int N=50005,M=100005,INF=1e9;
struct edge{
	int u,v,w,col;
}e[M];
int n,m,k;
inline void init(){
	n=read(); m=read(); k=read();
	for (int i=1;i<=m;i++){
		e[i].u=read()+1; e[i].v=read()+1; e[i].w=read(); e[i].col=read();
	}
}
int fa[N];
int getfa(int x){
	return (fa[x]==x)?x:fa[x]=getfa(fa[x]);
}
int ans;
inline bool cmp(edge A,edge B){
	return A.w<B.w||(A.w==B.w&&A.col<B.col);
}
inline bool judge(int x){
	for (int i=1;i<=n;i++){
		fa[i]=i;
	}
	for (int i=1;i<=m;i++){
		if (!e[i].col) e[i].w+=x;
	}
	sort(e+1,e+1+m,cmp); int cnt=0,res=0; ans=0;
	for (int i=1;i<=m;i++){
		int p=getfa(e[i].u),q=getfa(e[i].v);
		if (p!=q){
			fa[p]=q; cnt++; res+=(e[i].col==0); ans+=e[i].w;
			if (cnt==n-1) break;
		}
	}
	for (int i=1;i<=m;i++){
		if (!e[i].col) e[i].w-=x;
	}
	return res>=k;
}
inline void solve(){
	int l=-100,r=101;
	while (l<r){
		int mid=(l+r+1)>>1;
		if (judge(mid)) l=mid;
			else r=mid-1;
	}
	judge(l);
	writeln(ans-l*k);
}
int main(){
	init(); solve(); return 0;
}
```

---

## 作者：maomao9173 (赞：7)

[更好的阅读体验戳这。](https://www.cnblogs.com/maomao9173/p/10916587.html)

新学的科技。设$f(x)$为选$x$条白色边的时候的最小生成树权值和，那么可以猜到它应该是一个下凸函数的形式。

![](http://images.cnblogs.com/cnblogs_com/maomao9173/1317473/o_111.png)

如图，图中$x$坐标表示选的白色边条数，$y$坐标表示获得的权值，那么我们就可以把$f(x)$在这个图上大致表示出来。我们现在并不清除$x$和$y$，所以可以二分一下和这个凸函数相切直线的斜率。设这个直线为$y = kx + b$，那么对于一个固定的$x$，截距最小的时候，就是与函数相切的时候嘛，也是答案最优的时候。

我们把这个直线转化成$y - kx = b$的形式。由于不清楚会选用几条边，所以可以提前给每一条白色边都减去一个$k$，这样不管选几条边其影响都可以被直接统计。也就是说我们现在就可以忽略选几条边的问题直接去最小化截距$b$了。在最小化截距的同时我们对$y$的值和$x$的值做一个记录，这样就可以做出应该取用左区间还是右区间的判定啦。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 50000 + 5;
const int M = 100000 + 5;
#define pii pair <int, int>
#define mp(x,y) make_pair (x, y)

struct Len {
	int u, v, w, c;

	void read () {
		cin >> u >> v >> w >> c;
	}
	
	bool operator < (Len rhs) const { 
		return w == rhs.w ? c < rhs.c : w < rhs.w;
	}
}L[M];

int n, m, k, fa[N];

int find (int x) {
	return x == fa[x] ? x : fa[x] = find (fa[x]);
}

pii Kruskal () {
	for (int i = 0; i < n; ++i) fa[i] = i;
	sort (L, L + m);
	int cnt = 0, ret = 0, wht = 0;
	for (int i = 0; i < m; ++i) {
		int fu = find (L[i].u);
		int fv = find (L[i].v);
		if (fu != fv) {
			cnt += 1;
			fa[fu] = fv;
			ret += L[i].w;
			wht += L[i].c == 0;
		}
		if (cnt == m - 1) break;
	}	
	return mp (wht, ret);
} 

signed main () {
//	freopen ("data.in", "r", stdin);
	cin >> n >> m >> k;
	for (int i = 0; i < m; ++i) {
		L[i].read ();
	}
	int l = -150, r = 150, ans = 0;
	while (l < r) {
		int mid = (l + r) >> 1;
		for (int i = 0; i < m; ++i) {
			if (L[i].c == 0) { // 白色 
				L[i].w -= mid;
			}
		} 
		pii ret = Kruskal ();
//		cout << "l = " << l << " r = " << r << " mid = " << mid <<  " ret = (" << ret.first << ", " << ret.second << ")" << endl; 
		if (ret.first >= k) {
			r = mid;
			ans = ret.second + mid * k;
		} else {
			l = mid + 1;
		}
		for (int i = 0; i < m; ++i) {
			if (L[i].c == 0) {
				L[i].w += mid;
			}
		}
	}
//	cout << l << " " << r << endl;
	cout << ans << endl;
}
```

---

## 作者：pomelo_nene (赞：6)

$\ \ \ \ \ \ $个人认为这是一道好的二分题，只不过比较裸

---

## 题目分析

$\ \ \ \ \ \ $题意：

>$\ \ \ \ \ \ $让你求一棵最小权的恰好有$need$条白色边的生成树

$\ \ \ \ \ \ $也就是说让你求一棵有$need$条白边的最小生成树，求问该树的边权

## 题目解析

$\ \ \ \ \ \ $开始在模拟赛场上拿到这道题，首先考虑二分，直接二分答案，判断当前有$need$条白边的最小生成树是否边权小于我们当前的答案。   

$\ \ \ \ \ \ $但是我们发现这是不行的，因为我们无法确定当前的最小生成树有多少条边权。   

$\ \ \ \ \ \ $考虑正确性，我们发现求最小生成树的算法是$Kruskal$，我们把权值小的放在前面，我们就能够优先用到那一条边，但是这有什么用呢？

$\ \ \ \ \ \ $我们发现权值越小的，用到的机会就越大。所以说我们要确定一个优先级，使得白边在从小到大的排序中，位置不定

$\ \ \ \ \ \ $这个意思是说，我们修改白边的属性，改变它的优先级，使得采用的方法不同。

$\ \ \ \ \ \ $我们考虑改掉所有的白边权值，我们惊奇的发现它是有单调性的，我们白边越长，用到的就越少（考虑Kruskal的排序），很显然地，我们可以二分，修改白边的边权，每次进行Kruskal来判断最小生成树里面是否有$need$条白边

$\ \ \ \ \ \ $时间复杂度$\Theta(E \log E \times \log 200)$，常数其实很小

## 代码细节

- 当两条边权值相等，优先考虑白边

- 不要忘记初始化

$\ \ \ \ \ \ $代码细节详见注释

```cpp
#include<set>
#include<map>
#include<queue> 
#include<cstdio>
#include<string>
#include<iostream>
#include<algorithm>
using namespace std;
struct Edge{
	int s,t,c,col;
	bool operator <(Edge x) const
	{
		if(c==x.c)	return col<x.col;
		else	return c<x.c;//我们确定优先级，权值相等白边优先，否则权值小在前
	}
}edge[100005];
int read()
{
	int x=0;
	char c=getchar();
	while(c<'0' || c>'9')	c=getchar();
	while(c>='0' && c<='9')	x=(x<<1)+(x<<3)+(c^'0'),c=getchar();
	return x;
}//快读
int n,m,need,value,s[100005],t[100005],c[100005],col[100005],fa[50005];
void makeSet(int x){for(int i=1;i<=x;++i)	fa[i]=i;}
int findSet(int x)
{
	if(x==fa[x])	return x;
	else	return fa[x]=findSet(fa[x]);
}
bool unionSet(int x,int y)
{
	int xx=findSet(x),yy=findSet(y);
	if(xx==yy)	return false;
	fa[xx]=yy;
	return true;
}//并查集不解释，注意这里union的写法
bool check(int mid)
{
	makeSet(n);//注意makeSet
	value=0;
	int cnt=0;
	for(int i=1;i<=m;++i)
	{
		if(!col[i])	edge[i]=(Edge){s[i],t[i],c[i]+mid,col[i]};
		else	edge[i]=(Edge){s[i],t[i],c[i],col[i]};
	}//我们更改白边的权值，加上当前的二分值
	sort(edge+1,edge+1+m);
	for(int i=1;i<=m;++i)
	{
		if(unionSet(edge[i].s,edge[i].t))
		{
			value+=edge[i].c;
			if(!edge[i].col)	++cnt;
		}
	}//进行Kruskal，判断是否能选need条白边
	return cnt>=need;
}
int main(){
	// freopen("tree.in","r",stdin);
	// freopen("tree.out","w",stdout);
	n=read(),m=read(),need=read();
	for(int i=1;i<=m;++i)	s[i]=read(),t[i]=read(),c[i]=read(),col[i]=read(),++s[i],++t[i];
	int l=-105,r=105,ans=0;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid))	l=mid+1,ans=value-need*mid;
		else	r=mid-1;
	}//二分，注意更新答案
	printf("%d",ans);
	return 0;
}
```

---

## 作者：AtomAlpaca (赞：5)

## [国家集训队] Tree I 
### 题意
给出一个无向带权连通图，每条边是黑色或白色。求一棵最小权的恰好有 $need$ 条白色边的生成树。


[详情请咨询](https://www.luogu.com.cn/problem/P2619)
### 题解

凸性的证明思路和最小度限制生成树类似。首先对于每个白边 $(u, v, w)$，考虑新增一条黑边 $(u, v, +\infty)$，防止白边过少时无法得到生成树。考虑当前有 $k - 1$ 条白边的生成树，现在要强行加进去一个白边，设其权值为 $w_1$，这使得原来的生成树上多出来一个环，我们选这个环上所有黑边中权值最大的一个删掉，设其权值为 $w_2$。我们每次要选择加入后构成的环中有黑边，且权值增量 $w = w_1 - w_2$ 最小的一个白边。不难发现这两个限制随着白边的加入都是越来越紧的——第 $k$ 次未加入生成树的白边第 $k + 1$ 次可能加入了，第 $k$ 次存在的黑边第 $k + 1$ 次可能不存在。

因此如果第 $k + 1$ 次加入时的增量小于 $k$ 次，那一定可以交换 $k, k + 1$ 次的选边方案使得第 $k$ 次更优，因此加入白边后的权值增量不增，故该问题有凸性，可以用 wqs 二分解决。

于是二分一个增量，每次将所有白边权值加上这个增量，再和黑边一起跑最小生成树，根据最小生成树中白边的数量调整增量即可。

### 代码
```cpp
#include <bits/stdc++.h>

using std::cin;
using std::cout;

const int MAX = 1e5 + 5;

int n, m, k, u, v, w, c, cnt, res, ans;
int f[MAX];
struct E { int u, v, w, c; } e[MAX];

int find(int x) { if (f[x] == x) { return x; } return f[x] = find(f[x]); }
bool cmp(E a, E b) { if (a.w == b.w) { return a.c < b.c; } return a.w < b.w; }

void check(int x)
{
	res = cnt = 0;
	for (int i = 1; i <= m; ++i) { if (e[i].c == 0) { e[i].w += x; } }
	for (int i = 1; i <= n; ++i) { f[i] = i; }
	std::sort(e + 1, e + m + 1, cmp);
	for (int i = 1, tmp = 0; i <= m and tmp != n - 1; ++i)
	{
		int fu = find(e[i].u), fv = find(e[i].v);
		if (fu == fv) { continue; }
		f[fv] = fu; if (e[i].c == 0) { ++cnt; } res += e[i].w; ++tmp;
	}
	for (int i = 1; i <= m; ++i) { if (e[i].c == 0) { e[i].w -= x; } }
}

int main()
{
	cin >> n >> m >> k;
	for (int i = 1; i <= m; ++i)
	{
		cin >> u >> v >> w >> c;
		e[i] = {u + 1, v + 1, w, c};
	}
	int l = -111, r = 111, mid = 0;
	while (l <= r)
	{
		mid = (l + r) >> 1;
		check(mid);
		if (cnt < k) { r = mid - 1; } else { l = mid + 1; ans = res - k * mid; }
	}
	cout << ans;
	return 0;
}
```

---

## 作者：cirnovsky (赞：5)

## 题意简述

这个题面很友好。

## 题解

二分+最小生成树。

我们可以给每条白边加上某一个值。这样就可以使得我们求最小生成树的时候，可以控制白边选择的数量。

显然我们可以二分这个值。

下面给出单调性证明：

如果某一时刻的mid较大，使得选择的白边数量小于need，我们就相应的把mid调小，也就是令r=mid。

同理，如果某一时刻的mid较小，使得选择的白边数量大于，我们就相应的把mid调大，也就是令l=mid+1。

由上可知此题的单调性。

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int MAXN = 100000 + 5;
const int INF = 1e2 + 5;
int n, m, ans, need;
struct EdgeNode {
	int from;
	int to, val;
	int color;
} e[MAXN];

int sum, tot, white;
struct UnionFindSet{
	int fa[MAXN];

	void init(int lim) {
		for (int i = 1; i <= lim; ++i)
			fa[i] = i;
		sum = 0;
		tot = 0;
		white = 0;
	}

	int find(int x) {
		if (x ^ fa[x]) fa[x] = find(fa[x]);
		return fa[x];
	}

	void merge(int x, int y, int i) {
		x = find(x);
		y = find(y);
		if (x ^ y) {
			tot++;
			fa[x] = y;
			sum += e[i].val;
			white += (e[i].color ^ 1);
		}
	}
} ufs;

bool cmp(EdgeNode x, EdgeNode y) {
	return (x.val == y.val) ? (x.color < y.color) : (x.val < y.val);
}

void get_mst() {
	sort(e + 1, e + 1 + m, cmp);
	for (int i = 1; tot != n - 1; ++i) {
		// if (tot == n - 1) break;
		ufs.merge(e[i].from, e[i].to, i);
	}
}

void over(int x) {
	for (int i = 1; i <= m; ++i) if (e[i].color ^ 1) e[i].val -= x;
}

bool check(int x) {
	ufs.init(n + 1);
	for (int i = 1; i <= m; ++i) if (e[i].color ^ 1) e[i].val += x;
	get_mst();
	return white >= need;
}

signed main() {
	scanf("%d %d %d", &n, &m, &need);
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d %d %d", &e[i].from, &e[i].to, &e[i].val, &e[i].color);
		e[i].from++, e[i].to++;
	}
	int l = -INF, r = INF;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (check(mid)) l = mid + 1, ans = sum - mid * need;
		else r = mid;
		over(mid);
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：lzcjoe (赞：0)

### 题面

1491：Tree

时间限制: 1000 ms 内存限制: 65536 KB

【题目描述】

原题来自：2012 年国家集训队互测

给你一个无向带权连通图，每条边是黑色或白色。让你求一棵最小权的恰好有$need$条白色边的生成树。题目保证有解。

【输入】

第一行$V,E,need$分别表示点数，边数和需要的白色边数。

接下来$E$行，每行$s,t,c,col$表示这边的端点（点从$0$开始标号），边权，颜色（$0$白色，$1$黑色）。

【输出】

一行表示所求生成树的边权和。

【输入样例】

2 2 1  

0 1 1 1  

0 1 2 0

【输出样例】

2

【提示】

数据范围：

对于所有数据，$V≤5×10^4,E≤10^5$，边权为$[1,100]$中的正整数。

### 算法

Kruskal+二分

**Kruskal**

最小生成树算法，通过排序、贪心、并查集求解最小生成树

**二分**

对于本题来说，如果让白色的边加上（或减去）一个值，则在贪心算法的Kruskal中，白色边的数目必然不大于（不小于）最初的最小生成树中白色边的值，也就是说白色边的增值和白色边的数量是单调的，可以二分。

此处要二分增减的值（为$mid$），鉴于边权在$1~100$之间，可以设置上下界为$105$、$-105$，每次二分进行一次Kruskal，再检查答案，如果白色边大于等于$need$，则更新答案为$ans=sum-mid*need$（$sum$为最小生成树的边权和，$mid$是增减值），不断二分使白色边不断接近$need$，可以获得最优答案。

### 代码

```cpp
#include<cstdio>
#include<algorithm>
int v,e,need;
struct node
{
	int u,v,w,colour;
}edge[100005];
inline bool cmp(const node &A,const node &B)
{
	if(A.w==B.w)
	{
		return A.colour<B.colour;
	}
	return A.w<B.w;
}//边的结构体和比较函数
int father[50005];
int find_father(int x)
{
	if(father[x]==x)
	{
		return father[x];
	}
	father[x]=find_father(father[x]);
	return father[x];
}//并查集
int sum,white,cnt;
int main()
{
	scanf("%d%d%d",&v,&e,&need);
	for(int i=1;i<=e;i++)
	{
		scanf("%d%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w,&edge[i].colour);
		edge[i].u++;
		edge[i].v++;
	}//读入
	int l=-105,r=105,mid,ans=0;
    //二分
	while(l<=r)
	{
		mid=(l+r)>>1;
		for(int i=1;i<=e;i++)
		{
			if(edge[i].colour==0)
			{
				edge[i].w+=mid;
			}
		}//增加值
		for(int i=1;i<=v;i++)
		{
			father[i]=i;
		}/
		sum=0,white=0,cnt=0;//初始化
		std::stable_sort(edge+1,edge+e+1,cmp);//排序
		for(int i=1;i<=e;i++)
		{
			int f1=find_father(edge[i].u),f2=find_father(edge[i].v);
			if(f1!=f2)
			{
				cnt++;
				sum+=edge[i].w;
				father[f2]=f1;
				if(edge[i].colour==0)
				{
					white++;
				}
				if(cnt==v-1)
				{
					break;
				}
			}
		}//最小生成树Kruskal，并统计白色边数量
		if(white>=need)
		{
			l=mid+1;
			ans=sum-mid*need;
		}
		else
		{
			r=mid-1;
		}//更新边界值、答案
		for(int i=1;i<=e;i++)
		{
			if(edge[i].colour==0)
			{
				edge[i].w-=mid;
			}
		}//还原边权
	}
	printf("%d",ans);//输出
	return 0;
}
```

#### 运行结果

一本通OJ：

1491

通过 100分

测试点1: 答案正确 420KB 2MS 

测试点2: 答案正确 7664KB 106MS 

测试点3: 答案正确 7664KB 103MS 

测试点4: 答案正确 7656KB 104MS 

测试点5: 答案正确 7664KB 104MS 

测试点6: 答案正确 7668KB 102MS 

测试点7: 答案正确 7656KB 103MS 

测试点8: 答案正确 7668KB 102MS 

测试点9: 答案正确 7656KB 105MS 

测试点10: 答案正确 7668KB 103MS 

测试点11: 答案正确 7664KB 103MS 

测试点12: 答案正确 6156KB 92MS 

测试点13: 答案正确 6308KB 93MS 

测试点14: 答案正确 6552KB 101MS 

测试点15: 答案正确 6796KB 100MS 

测试点16: 答案正确 6892KB 100MS 

测试点17: 答案正确 7056KB 105MS 

测试点18: 答案正确 7124KB 106MS 

---

洛谷：

用时 1.68s 内存 3.25MB

测试点信息

2ms/516.00KB AC #1

3ms/668.00KB AC #2

126ms/2.88MB AC #3

3ms/800.00KB AC #4

4ms/652.00KB AC #5

5ms/816.00KB AC #6

6ms/780.00KB AC #7

7ms/816.00KB AC #8

9ms/900.00KB AC #9

122ms/2.00MB AC #10

150ms/2.40MB AC #11

133ms/2.48MB AC #12

142ms/2.45MB AC #13

147ms/2.64MB AC #14

148ms/2.62MB AC #15

150ms/2.63MB AC #16

164ms/2.91MB AC #17

166ms/3.01MB AC #18

189ms/3.25MB AC #19

3ms/652.00KB AC #20

---

