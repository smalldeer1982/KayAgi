# [USACO01OPEN] Earthquake

## 题目描述

一场地震把约翰家的牧场摧毁了， 坚强的约翰决心重建家园。 约翰已经重建了 $n$ 个牧场，现在他希望能修建一些道路把它们连接起来。研究地形之后，约翰发现可供修建的道路有 $m$ 条。碰巧的是，奶牛们最近也成立一个工程队，专门从事修复道路。而然，奶牛们很有经济头脑，如果无利可图，它们是不会干的。

奶牛们关注的是挣钱速度，即总利润和总施工时间的比值。约翰和奶牛达成了协议，奶牛负责修建道路，将所有牧场连通，而约翰需要支付 $f$ 元。每条道路都有自己的施工时间和建造成本。连接两个相同的牧场的道路可能有多条。保证所有的牧场必定是可连通的，不过也有可能一些道路的建造成本之和会超过 $f$。  

请帮助奶牛们选择修复哪些道路，才能使单位时间的利润最大？


## 说明/提示

#### 样例输入输出 1 解释

奶牛们可以选择连通最后四条道路，则总时间为 $16$，总成本为 $83$，所以单位利润为 $\dfrac{17}{16}=1.0625$。

#### 数据规模与约定

对于 $100\%$ 的数据，保证
- $1 \leq n \leq 400$，$1 \leq m \leq 10000$，$1 \leq f \leq 2 \times 10^9$。
- $1 \leq u_i,v_i \leq n$，$1 \leq c_i,t_i \leq 2 \times 10^9$。

## 样例 #1

### 输入

```
5 5 100
1 2 20 5
1 3 20 5
1 4 20 5
1 5 20 5
2 3 23 1```

### 输出

```
1.0625```

# 题解

## 作者：ustze (赞：17)

这是一个01分数规划的入门题(>_>)  
设所选的点集为S，考虑二分答案$$mid\le\frac{F-\sum_{i\in S}Ci}{\sum_{i\in S}Ti}$$
移項得 $$F-\sum_{i\in S}(mid*Ti+Ci)\ge 0$$
将边重新赋权为$-mid*Ti-Ci$，做一遍最大生成树就好了，$F+sum\ge0$就说明答案可以更大  
具体细节见代码
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=805,M=20005;
const double eps=1e-6;
int n,m,F,fa[N];
bool vis[N];
struct edge{
    int u,v,c,t;double w;
}a[M];

int findf(int x)
{
    if(fa[x]==x) return fa[x];
    return fa[x]=findf(fa[x]);
}
bool cmp(edge x,edge y){return x.w>y.w;}
bool check(double r)
{
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1;i<=m;i++) a[i].w=-a[i].c-r*a[i].t;
    sort(a+1,a+m+1,cmp);
    int num=0;double sum=F;
    for(int i=1;i<=m;i++) {
        if(num==n-1) break;
        int x=findf(a[i].u),y=findf(a[i].v);
        if(x!=y) {
            num++,fa[x]=y;
            sum+=a[i].w;
        }
    }
    return sum>=0;
}

int main()
{
    scanf("%d%d%d",&n,&m,&F);
    for(int i=1;i<=m;i++)
        scanf("%d%d%d%d",&a[i].u,&a[i].v,&a[i].c,&a[i].t);
    
    double l=0,r=1e9,mid;
    while(l+eps<r)
    {
        mid=(l+r)/2;
        if(check(mid)) l=mid;
        else r=mid;
    }
    printf("%.4lf\n",r);
    return 0;
}

```

---

## 作者：灯芯糕 (赞：16)

## $solution:$

 	这题其实牵扯到了一种普遍的二分答案的方法，与[HNOI2009 最小圈](https://www.luogu.org/problemnew/show/P3199) 一样有许多的共同点。因为这些题要求我们输出的ans都是针对权值总和不断计算而来的。本题就是个经典例题（二分答案求最优比率生成树），经典因为我们可以直接通过题意看出它要求我们输出的**最终答案**实际上就是：

### $ans= \frac{F-\sum{v_i} \quad (i\in S)}{\sum{t_i}\quad (i\in S)} $

（其中**S为我们最终所选择的最优生成树的边权的集合**）我们将这个式子转换一下，可以得到：

### $F=ans*\sum{t_i}+\sum{v_i}$

### $F=\sum{ans*t_i+v_i}\quad _{(i\in S)}$

注：这一点我们一定要清楚：此时等式右边就是生成树（只不过；树边权变成了$ans*t_i+v_i$）

​	上述式子中我们的ans就是我们最终要输出的最优比率，这个ans是我们可以二分得到的！因为答案具有单调性，当然这个需要我们进一步证明：首先，因为ans是**最优**比率，那么我们可以知道，对于图上的任意一个生成树的边的集合K，一定有：$\frac{F-\sum{v_i} \quad (i\in K)}{\sum{t_i}\quad (i\in K)}\leq ans $ （根据上述方式转化得：$F\leq \sum{ans*t_i+v_i}\quad {(i\in K)}$）只有当我们的集合K取到最优的生成树时也就是**K=S**的时候，这个式子才会是等式！然后我们来证明二分的正确性：当我们二分求ans的时候，对于我们当前的比率x，一定有这三种情况：

### $1.$ $x>ans$ ：

当我们比率为ans时：$F\leq \sum{ans*t_i+v_i}\quad {(i\in K )}$

现在我们的比率x比ans还大！那我们的肯定有：$F< \sum{x*t_i+v_i}\quad {(i\in K)}$

### $2.$ $x=ans$ ：

我已经说过了：$F\leq\sum{ans*t_i+v_i}\quad {(i\in K)}$

### $3.$ $x<ans$ ：

这个时候我们发现我们不能确认$F$ 和  $\sum{ans*t_i+v_i}\quad {(i\in K)}$ 的大小关系了！因为我们的K是任意生成树的边的集合，此时我们小于等于大于都有可能，但也正是如此，我们可以证明**一定存在一个生成树边的集合**满足$F>\sum{x*t_i+v_i}\quad {(i\in S)}$因为就拿我们ans情况下的最优边集S，因为 $F=\sum{ans*t_i+v_i}\quad {(i\in S)}$ 此时我们的$x<ans$ 所以$F>\sum{x*t_i+v_i}\quad {(i\in S)}$

**如何二分（为什么用最小生成树）：**

那我们证明了上面这个东西有什么用呢？根据上述三个关系的特性（就是那三个不等式），我们发现当我们将x带进去后，只要求得最小的 $\sum{ans*t_i+v_i}\quad {(i\in K)}$ 我们就可以直接判断出x和ans的关系了！

我们将最小的$\sum{ans*t_i+v_i}\quad {(i\in K)}$ 看做min 

1. 若$F<min$，则必有$F< \sum{x*t_i+v_i}\quad {(i\in K)}$ 这不就是第一种情况吗？x必然大于ans
2. 若$F=min$，则必有$F  \leq \sum{x*t_i+v_i}\quad {(i\in K)}$ 这不就是第二种情况吗？x必然等于ans
3. 若$F>min$，则x必然不大于也不等于ans，那不就是小于ans吗？（上面证过了若x<ans，则必存在一个K$F>\sum{x*t_i+v_i}\quad {(i\in K)}$）

那我们如何求最小的$\sum{x*t_i+v_i}\quad {(i\in K)}$ 呢？ 这就是求最小生成树嘛（只不过；树边权变成了$ans*t_i+v_i$，我们每一次都重新排个序就行了）！

总复杂度：$O(m *logm*log(r-l+1))$

## $code:$

```cpp
//耗时 41ms 内存 1036KB
#include<iostream>
#include<cstdio>
#include<iomanip>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<vector>
#include<queue>
#include<map>
#include<set>

#define ll long long
#define db double
#define rg register int

using namespace std;

const db cha=1e-9;

struct su{
	int x,y,v,t;db k;
}a[10005];

int n,m,f;
int s[405];

inline int qr(){
	char ch;
	while((ch=getchar())<'0'||ch>'9');
	int res=ch^48;
	while((ch=getchar())>='0'&&ch<='9')
		res=res*10+(ch^48);
	return res;
}

inline bool cmp(su x,su y){return x.k<y.k;}

inline int get(int x){
	if(s[x]==x)return x;
	return s[x]=get(s[x]);
}

inline bool check(db x){
	db res=0;
	for(rg i=1;i<=n;++i)s[i]=i;//并查集
	for(rg i=1;i<=m;++i)
		a[i].k=x*a[i].t+(db)a[i].v;//更新边权
	sort(a+1,a+m+1,cmp);//kruskal求最小生成树
	for(rg i=1;i<=m;++i)
		if(get(a[i].x)!=get(a[i].y))
			res+=a[i].k,s[get(a[i].x)]=get(a[i].y);//求新边权的总和
	return f>res?0:1;
}

int main(){
	freopen("quake.in","r",stdin);
	freopen("quake.out","w",stdout);
	n=qr(),m=qr(),f=qr();
	for(rg i=1;i<=m;++i)
		a[i]=su{qr(),qr(),qr(),qr()};
	if(check(0))puts("0.0000"),exit(0);//特判
	db l=0,r=1e14,mid;
	while(r-l>cha){//二分答案
		mid=(l+r)/2;
		if(check(mid))r=mid-cha;
		else l=mid+cha;
	}printf("%.4lf",l);
	return 0;
}

```



---

## 作者：dyc2022 (赞：3)

问题描述：求 $\max \dfrac{C}{T}$，其中 $C$ 是利润，$T$ 是时间。

由于我们要求的是通过修路把所有的牧场联通，那么修最少的路的情况，就是**形成一个生成树**。

根据题目的信息，以下 $c_i$ 表示第 $i$ 条路得成本， $t_i$ 表示修第 $i$ 条道路的时间。设数组 $\{s\}$ 中的元素 $s_i$ 表示对于图的一刻生成树，要不要选第 $i$ 条边。$(\forall x \in \{s\}) \in \{0,1\}$。

则：

$$C = f - \sum^{n}_{i=1} s_ic_i$$

$$V = \sum^{n}_{i=1} s_it_i$$

设：

$$\dfrac{f - \sum^{n}_{i=1} s_ic_i}{\sum^{n}_{i=1} s_it_i} \ge x$$

得：

$$f - \sum^{n}_{i=1} s_ic_i\ge x\sum^{n}_{i=1} s_it_i$$

移项：

$$f\ge x\sum^{n}_{i=1} s_it_i + \sum^{n}_{i=1} s_ic_i$$

$$\sum^{n}_{i=1} s_i(xt_i+c_i) \le x$$

于是，我们就发现这是一个在第 $i$ 条边的权值为 $xt_i+c_i$ 的图上求最小生成树。

我们要最大化 $x$，可以用二分查找（二分答案）来解决问题。具体操作方法为定义一个 `check(double x)` 函数，先将第 $i$ 条边的权值变成 $xt_i+c_i$，然后选择使用 kruscal 算法求最小生成树。如果最小生成树的权值之和小于等于 $x$，说明这个 $x$ 是可行的。否则就不可行。

最后，警钟长鸣：注意精度！！！

AC 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 402
#define M 11200
#define EPS 1e-10
using namespace std;
struct edge{int u,v;double c,t;}old[M];
struct Node{int u,v;double w;}e[M];
bool operator <(Node x,Node y){return x.w<y.w;}
int fath[N],n,m;
double f,l,r,mid;
void init()
{
	for(int i=1;i<=n;i++)fath[i]=i;
}
int find(int k)
{
	if(fath[k]==k)return k;
	else return find(fath[k]);
}
int un(int k1,int k2)
{
	fath[find(k1)]=find(k2);
}
double kruscal()
{
	init();
	sort(e+1,e+1+m);
	int cnt=0;
	double ret=0;
	for(int i=1;cnt<n-1;i++)
	{
		int nowu=e[i].u,nowv=e[i].v;
		if(find(nowu)==find(nowv))continue;
		un(nowu,nowv);
		ret+=e[i].w;
		cnt++;
	}
	return ret;
}
int check(double x)
{
	for(int i=1;i<=m;i++)e[i]=(Node){old[i].u,old[i].v,old[i].t*x+old[i].c};
	return kruscal()<=f;
}
main()
{
	scanf("%lld%lld%lf",&n,&m,&f);
	for(int i=1;i<=m;i++)
		scanf("%lld%lld%lf%lf",&old[i].u,&old[i].v,&old[i].c,&old[i].t);
	r=0x3f3f3f3f;
	while(r-l>=EPS)
	{
		mid=(l+r)/2;
		if(check(mid))l=mid;
		else r=mid;
	}
	printf("%.4lf",l);
	return 0;
}
```

另：建议添加标签“分数规划”。

---

## 作者：Rachel_in (赞：3)

01分数规划基础题，[学习地址](http://www.cnblogs.com/perseawe/archive/2012/05/03/01fsgh.html)

所谓的01分数规划问题就是指这样的一类问题，给出一些物品，每个物品有两种属性，物体可以选或不选，求最后两种属性之和相比的最大值或最小值。

对于本题我们需要求得就是：

$$max\frac {F-\sum C_x}{\sum T_x}$$

其中，$C_x$和$T_x$表示的是选择的边的成本和时间。

我们设最终的答案为$Ans$,则有:
$$\frac {F-\sum C_x}{\sum T_x}=Ans$$
$$F-\sum C_x-\sum T_x*Ans=0$$

我们的目标就是最大化Ans的值,可以二分。

二分答案，接下来的问题就是在于如何判断是否能够取得到

对与每个$Mid<=Ans$,它们都是可以取到的，也就是:

$$F-\sum C_x-\sum T_x*Mid \ge0$$

倘若$Mid>Ans$,它们永远也取不到，也就是
$$F-\sum C_x-\sum T_x*Mid \lt0$$

我们发现可以用这个式子来判断$Mid$合不合法。我们将原先的边权变为$\sum C_x+\sum T_x*Mid$,然后跑一遍最小生成树就可以了。至于为什么是最小生成树，是因为我们需要找到最小的一组$\sum C_x+\sum T_x*Mid$，使减数尽量小从而尽可能满足两式相减大于等于0这个条件

**代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int res=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9'){res=(res<<3)+(res<<1)+ch-'0';ch=getchar();}
	return res*f;
}
const int N=405;
const int M=10005;
int n,m,f,fa[N];
const double eps=1e-8;
double l,r,mid;
struct node1{
	int u,v,c,t;
}a[M];
struct node2{
	int u,v;
	double x;
}g[M];
bool cmp(node2 x,node2 y){
	return x.x<y.x;
}
int find(int x){
	if(fa[x]==x) return x;
	else return fa[x]=find(fa[x]);
}
bool check(double x){
	for(int i=1;i<=m;i++)
		g[i].u=a[i].u,g[i].v=a[i].v,g[i].x=(double)a[i].c+(double)a[i].t*x;//边的新权值
	for(int i=1;i<=n;i++) fa[i]=i;
	sort(g+1,g+m+1,cmp);
	double res=0;
	int cnt=0;
	for(int i=1;i<=m;i++){//最小生成树
		int xx=find(g[i].u),yy=find(g[i].v);
		if(xx!=yy){
			cnt++;
			res+=g[i].x;	
			fa[xx]=yy;
			if(cnt==n-1) break;
		}		
	}
	return ((double)f-res)>=0.0;	//判断是否满足条件
}
int main(){
	n=read();m=read();f=read();
	for(int i=1;i<=m;i++)
		a[i].u=read(),a[i].v=read(),a[i].c=read(),a[i].t=read();
	l=0.0;r=1e12;	
	while(r-l>=eps){
		mid=(l+r)/2;
		if(check(mid)) l=mid;
		else r=mid;
	}			
	printf("%.4lf",l);
}
```


---

## 作者：Luciylove (赞：1)

2021/3/13 upd:修改一个错误的链接

01分数规划。

和最优比率生成树比较相似。

设选了的边集为$S$,答案为$k$则有:

### $k\leq \frac{f-\sum_{i \in S}c_i}{\sum_{i \in S}t_i}$

移项得:

### $f-\sum_{i \in S}{c_i-k*t_i} \ge 0$

我们发现：

对于$k$的取值$k_1$和$k_2$,当$k_1 > k_2$时，$k_1$满足上面的式子大于0时，$k_2$肯定可以满足。

所以答案有**单调性**。

我们将边权按照式子里赋值为$c_i-k*t_i$.

显然我们想要使得上面的式子有关$k$的部分的值更小，且让选出来的图联通，那么我们就使用**最小生成树**即可。

对于答案$k$,因为有单调性，所以直接二分即可。

时间复杂度:$O(n\log^2_2n)$.

[代码](https://www.luogu.com.cn/paste/zvfqdc0o)

另外，还有一道与图论结合的题目:

[这个](https://www.luogu.com.cn/problem/P3199)

一看:最小均值环。

按照刚才的套路，令新边权$p=val-k$,$val$为原来的边权，$k$为答案。

用SPFA判负环，若有负环，则代表有平均值小于$k$的环，我们按照二分上套路即可。

[代码](https://www.luogu.com.cn/paste/ve7erk9j)

大概就到这里了...

---

## 作者：太阳骑士 (赞：1)

我们设答案为 $k$ ，则有
$$\frac{f-\sum{c_i}}{\sum{t_i}}=k$$
移项得
$$f-(\sum{c_i}+k*\sum{t_i})=0$$
也就是
$$f-\sum{(c_i+k*t_i)}=0$$
我们设
$$f(k)=f-\sum(c_i+k*t_i)$$
当 $f(k)>0$ 时，则有比 $k$ 更好的答案；当 $f(k)=0$ 时， $k$ 一定是最优解；而当 $f(k)<0$ 时， 答案要小于 $k$ 。

所以我们可以二分枚举 $k$ 值，设 $v_i=c_i+k*t_i$ ，每条边按 $v$ 从小到大排序，每次用 `Kruskal` 求出最小生成树，计算 $\sum{v_i}$ ，判断其是否小于等于 $f$ 即可。

代码

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 401
#define M 10003
#define eps 1e-7
#define il inline
#define re register
#define tie0 cin.tie(0),cout.tie(0)
#define fastio ios::sync_with_stdio(false)
#define File(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout)
using namespace std;
typedef long long ll;

template <typename T> inline void read(T &x) {
	T f = 1; x = 0; char c;
    for (c = getchar(); !isdigit(c); c = getchar()) if (c == '-') f = -1;
    for ( ; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
    x *= f;
}

struct edge {
	int u, v, c, t;
	double w;
	friend bool operator < (edge x, edge y) { return x.w < y.w; }
} e[M];

int n, m, f, cnt;
int fa[N];

int find(int x) { return fa[x] == x ? x : find(fa[x]); }

double Kruskal() {
	double res = 0; cnt = 0;
	sort(e + 1, e + 1 + m);
	for (int i = 1; i <= n; ++i) fa[i] = i;
	for (int i = 1; i <= m; ++i) {
		int f1 = find(e[i].u), f2 = find(e[i].v);
		if (f1 == f2) continue;
		fa[f2] = f1; res += e[i].w;
		if (++cnt == n - 1) break;
	}
	return res;
}

bool check(double t) {
	for (int i = 1; i <= m; ++i) e[i].w = e[i].c + e[i].t * t;
	return Kruskal() <= (double)f;
}

int main() {
	int u, v, c, t;
	read(n), read(m), read(f);
	for (int i = 1; i <= m; ++i)
		read(e[i].u), read(e[i].v), read(e[i].c), read(e[i].t);
	double l = 0, r = 1000000000.0;
	while (r - l > eps) {
		double mid = (l + r) / 2.0;
		if (check(mid)) l = mid;
		else r = mid;
	}
	printf("%.4lf", l);
	return 0;
}
```

---

## 作者：龙翔凤翥 (赞：1)

### 考试题目，思路二分加最小生成树．
1 .　依题可得：设利润为Ｗ，则w=（给的工资Ｆ－ｃ的总和）再除以t的总和，易知ｗ单调递减，由此可想到二分答案．

２.　然后在跑最小生成树，以$c_ia+ t_i\times x$为边权值建树
#### 详情见代码
##  Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define RN register int
#define ll long long
#define sign 1e7
inline int read()
{
    int k=1;int x=0;
    char c=getchar();
    while ((c<'0'||c>'9')&&c!='-')c=getchar();
    if(c=='-')
		k=-1,c=getchar();
    while(c>='0'&&c<='9')
		x=x*10+c-'0',c=getchar();
    return k*x;
}
struct edge{
	int x;
	int y;
	int v;
	int t;
	double jia;//边权值
}p[10001];
int n,m,f;
int fa[10001];
inline int find(int x)//并查集查找
{
    if(fa[x]!=x)
        fa[x]=find(fa[x]);
    return fa[x];
}
inline void un(int x,int y)//并查集合并
{
	int xx=find(x);
	int yy=find(y);
	if(xx!=yy)
		fa[xx]=yy;
}
inline double cmp(edge x,edge y)//以边权值排序，建立最小生成树
{
	return x.jia<y.jia;
}
inline int part(ll midd)
{
	for(RN i=1;i<=m;i++)
		{
			p[i].jia=midd/sign*p[i].t+p[i].v;
		}
	sort(p+1,p+m+1,cmp);
	for(RN i=1;i<=n;i++)
		fa[i]=i;
		double k=(double)f;
	int x=1;
	for(RN i=2;i<=n;i++)//最小生成树
	  {
		  while(x<=m&&find(p[x].x)==find(p[x].y))//是否在一个集合里
			  x++;
		  un(p[x].x,p[x].y), k-=p[x].jia;
		  //cout<<k<<endl;
		  if(k<0)//二分的这个利润Ｗ小了
			  return 0;
	  }
	return 1;
}
int main()
{
	//freopen("quake.in", "r", stdin);
	//freopen("quake.out", "w", stdout);
	n=read(),m=read(),f=read();
	for(RN i=1;i<=m;i++)
		{
			p[i].x=read(),p[i].y=read(),p[i].v=read(),p[i].t=read();
		}
	if(!part(0))//如果利润为０都大了，那肯定没利润了qwq
		{
			printf("0.0000\n");
			return 0;
		}
	ll mid,l=0,r=2e15;
	while(l<r)//大范围二分
		{
			mid=(l+r)>>1;
			if(part(mid+1))
				l=mid+1;
			else
				r=mid;
		}
	printf("%.4lf\n",l/(double)sign);
	return 0;
}


```

---

## 作者：_____hyj_____ (赞：0)

Earthquake 题解
------------
 $01$ 分数规划： 
##### 假定我们已经得到了答案 $ans$ ，
那么就有 $ans=( F - \sum_{} c_i )/ \sum_{} t_i $ ,所以 $F=\sum(ans \times  t_i) + c_i $ .要求 $ans$ 最大, $ F $ 为定值, $ c_i $ 表示修建道路的成本, $ t_i $ 表示道路修建所需要的时间.

此时我们就是要让我们的程序去寻找这个符合条件且单位时间的利润最大的  $ ans $ 是多少，那就应当在一定范围类去尝试不同的值看是不是最优答案.

同时若此时 $ x \geq ans$ ,则有 $F \leq \sum (ans \times t_i \;) + c_i $ ,若此时   $ x<ans $ ,则有 $ F > \sum (ans \times  t_i) + c_i $ ,发现满足单调性，那么自然会想到去二分案 $ ans $ 的值 $ x $ ,后通过 $ F $ 和 $\sum (ans \times t_i \;) + c_i $  的大小情况可以不断缩小二分范围。

如何让单位时间的利润最大呢？
 $ ans = ( F - \sum_{} c_i )/ \sum_{} t_i $ ， $ F $ 为定值,我们发现随  $ \sum_{}c_i $ 的增大,$ ans $ 会减小，随 $ \sum_{} t_i $ 的增大, $ ans $ 会减小,所以要 $ ans $ 最大我们应让 $ \sum_{} c_i ,\sum_{} t_i $ 均小。

于是我们每次枚举出的 $ x $ ，应当让跑一个最小生成树，只需将边权设置为 $ x \times t_i + c_i $ ，然后将跑出来的结果与 $ F $ 比较来不断缩小二分范围，直到得到答案即可。

------------

代码：
```
#include<bits/stdc++.h>
#define re register
#define in inline
#define ll long long
#define inf 0x3f3f3f3f
#define max(a,b) a>b?a:b
#define min(a,b) a<b?a:b
#define me(a) memset(a,0,sizeof(a))
#define For(i,a,n) for(re int (i)=(a);(i)<=(n);(i)++)
#define Bor(i,n,a) for(re int (i)=(n);(i)>=(a);(i)--)
using namespace std;
const int N=10001;
const double eps=1e-6;
ll n,m,f;
int fa[N];
struct jt{
	ll u,v,c,t;
	double w;
}a[N];
in bool cmp(jt a,jt b)
{
	return a.w<b.w;  
}
in int find(int x)
{
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
in ll qread()
{
	re ll s=0,w=1;
	re char ch;
	ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch))
	{
		s=(s<<3)+(s<<1)+(ch^48); 
		ch=getchar();
	}
	return s*w;
}
in bool check(double x)
{
	double res=0;
	For(i,1,n)fa[i]=i;
	For(i,1,m)a[i].w=x*a[i].t+(double)a[i].c;
	sort(a+1,a+m+1,cmp);
	For(i,1,m)
	{
	if(find(a[i].u)!=find(a[i].v))	
	{
		res+=a[i].w;fa[find(a[i].u)]=find(a[i].v);
	}
	}
	return f>res?0:1;
}
int main()
{
	n=qread(),m=qread(),f=qread();
	For(i,1,m)a[i].u=qread(),a[i].v=qread(),a[i].c=qread(),a[i].t=qread();	 
	double l=0,r=1e12,mid;
	while(r-l>eps)
	{
		mid=(l+r)/2;
		if(check(mid))
		{
		r=mid-eps;
		}
		else
		{
		l=mid+eps;	
		}
	}
	if(l<0)
	{
		printf("0.0000");return 0;
	}
	printf("%.4lf",l);
	return 0;
}
 /*
5 6 100 
1 2 1  1
1 2 20 5 
1 3 20 5 
1 4 20 5 
1 5 20 5 
2 3 23 1 
*/
```


------------




---

## 作者：Error_666 (赞：0)

## 洛谷 P4951 [USACO 2001 OPEN]地震

### 题目：
- [链接](https://www.luogu.org/problem/P4951)

### 题解：
- 首先答案：ans=(F-成本之和)/时间之和

- 移一下项：ans*时间之和+成本之和=F

- 写得好看一点：$ans * \sum T{i} + \sum Ci = F$

- 显然，右边是一个定值，左边是一个增函数。ans越大，这一坨的值越大

- 那么我们可以二分ans，如果左边这一坨值>F，说明ans要减小，反之要增大

- 那么怎么算这一坨的值呢？也就是选哪些边呢？

- 相信你已经看出来了，将边权重新定义为ans * ti + ci。跑最小生成树

- 为什么要跑最小生成树？而不是最大？

- 因为我们要让左边这一坨的值尽量小，这样ans才能尽量大

- 搞定。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define N 40005
#define M 1000005
#define eps (1e-8)
using namespace std;

struct E{int u,v;double w;}e[M];
int n,m;
double f;
int u[N],v[N],fat[N];
double c[N],t[N];

int read()
{
    int x=0;char c=getchar();
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x;
}

bool cmp(E x,E y) {return x.w<y.w;}
int getFat(int x) {
    if(fat[x]==x) return x;
    return fat[x]=getFat(fat[x]);
}

bool check(double mid)
{
    for(int i=1;i<=n;i++) fat[i]=i;
    for(int i=1;i<=m;i++) {
        e[i].w=mid*t[i]+c[i];
        e[i].u=u[i],e[i].v=v[i];
    }
    sort(e+1,e+1+m,cmp);
    double sum=0;
    for(int i=1,cnt=0;i<=m;i++) {
        int fu=getFat(e[i].u),fv=getFat(e[i].v);
        if(fu!=fv) fat[fu]=fv,cnt++,sum+=e[i].w;
        if(cnt==n-1) return sum>=f;
    }
}

int main()
{
    cin>>n>>m>>f;
    for(int i=1;i<=m;i++) {
        u[i]=read(),v[i]=read();
        c[i]=read(),t[i]=read();
    }
    double l=0,r=1e12,ans;
    while(r-l>eps) {
        double mid=(l+r)/2;
        if(check(mid)) r=mid,ans=mid;
        else l=mid;
    }
    printf("%.4lf",ans);
    return 0;
}

```


---

## 作者：LemonChay (赞：0)

开始我做这道题目的时候，受到了坐在我边上的**dalao**的启发，于是我用了贪心来做这道题目。

**如何贪心？**

我们看到，要比例更大，我们就需要利润更大(花费更小)，时间更小。我们将两者相加一下，再排个序，再**Kruskal算法**走一波，这样我们就可以得到70分了。

#### 但是要注意一下，在遇到某些和相等但是时间和花费不相同的边，我们要优先排花费更小的，再排时间更小的。

看看程序吧：

```
#include<bits/stdc++.h>
using namespace std;
int n,m,f[401],sum;
long long e,ans1,ans2;
struct node
{
	int u,v;
	long long pj,t,c;
}dl[10001];
////////////////////////////////////////////
inline int find(int k)
{
	if(f[k]==k)
	{
		return k;
	}
	return find(f[k]);
}
/////////////////////////////////////////////
bool cmp(node a,node b)//改变一下快排的规则
{
	return a.pj<b.pj||(a.pj==b.pj&&a.c<b.c);
}
//////////////////////////////////////////////
inline long long getint()//习惯性快速读取
{
	long long dmxy=0;
	int demaxiya=1;
	char ch;
	while(ch=getchar())
	{
		if((ch>='0'&&ch<='9')||ch=='-')
		{
			break;
		}
	}
	if(ch=='-')
	{
		demaxiya=-1;
		ch=getchar();
	}
	do
	{
		if(ch>'9'||ch<'0')
		{
			break;
		}
		dmxy=dmxy*10+int(ch-'0');
	}while(ch=getchar());
	return dmxy*demaxiya;
}
//////////////////////////////////////////
void ct(long long a,long long b)
{
	double x=a,y=b,z=e,k=(z-y)/x;
	if(k<=0)
	{
		cout<<"0.0000";
	}
	else
	{
		printf("%0.4f",k);
	}
	return;
}
///////////////////////////////////////////
void read()
{
	n=getint(),m=getint(),e=getint();
	for(int i=1;i<=n;i++)//初始化并查集
	{
		f[i]=i;
	}
	for(int i=1;i<=m;i++)
	{	
    		dl[i].u=getint(),dl[i].v=getint(),dl[i].c=getint(),dl[i].t=getint();
		dl[i].pj=dl[i].c+dl[i].t;//总和累加
	}
	sort(dl+1,dl+m+1,cmp);
	return;
}
////////////////////////////////////////////
void work()
{
	for(int i=1;i<=m;i++)//Kruskal算法
	{
		int a=find(dl[i].u),b=find(dl[i].v);
		if(a==b)
		{
			continue;
		}
		ans1+=dl[i].t;
		ans2+=dl[i].c;
		f[a]=b;
		if(++sum==n-1)
		{
			break;
		}
	
	ct(ans1,ans2);
	return;
}
//////////////////////////////////////////////
int main()
{
	read();
    work();
	return 0;//好习惯
}
```

不知到Kruskal算法的右转度娘：[Kruskal算法](https://baike.baidu.com/item/克鲁斯卡尔算法/4455899?fr=aladdin)

**不想AC的oier不是好oier ——鲁迅** (鲁迅：和我有什么关系？)

假如我还不知道这道题目要用二分答案，咋办？

不用着急（~~你怎么不问问神奇海螺~~）,一步一步地来看。~~一般~~你在分析的时候都会得到一个这样的式子：r=(f-all(c))÷all(t)（all就是总和的意思）,对吧,当然，这是对于你选的边来说的。然后我们根据小学学的知识，式子左右交换，分配律，可以得到一个变式：(t1*r+t2*r+...+tn-1*r)+(c1+c2+...+cn-1)=f。
可以看到，这里的关键就是r了，那么我们就~~情不自禁~~地想到要枚举r，如何枚举？**当然就是二分答案啦!**

那么我们就这么做，每次二分一个r，带入到所有的边中，然后再生成一棵最小生成树，如果你得到的最小生成树的总的利润是一个正数，那么说明再右半部分有更大的利润，否则我们只能往左边移动。

二分的思路出来了，先自己做着，做到不懂的地方自己思考一下，实在不行再来看代码吧。

## 来，上代码：

```
#include<bits/stdc++.h>
using namespace std;
const double eps=1e-6;
int n,m,f,h[10001];
struct edge
{
    int u,v,c,t;
	double pj;
}dl[10001];
//////////////////////////////////////////////
int findf(int x)
{
    if(h[x]==x) return h[x];
    return h[x]=findf(h[x]);
}
//////////////////////////////////////////////
bool cmp(edge a,edge b){return a.pj>b.pj;}
//////////////////////////////////////////////
bool check(double r)
{
    for(int i=1;i<=n;i++) h[i]=i;//并查集初始化
    for(int i=1;i<=m;i++) dl[i].pj=-dl[i].c-r*dl[i].t;//上面讲解过了。但是这里还是要说一下为什么是-dl[i].c。如果你继续往下读代码，你就会发现sum的值应该是要不断变小的，这里只是做了一个方便变小的处理。
    sort(dl+1,dl+m+1,cmp);
    int num=0;double sum=f;//num表示加入树的边的数量，sum表示剩余的利润
    for(int i=1;i<=m;i++) //Kruskal算法
	{
        if(num==n-1) break;
        int x=findf(dl[i].u),y=findf(dl[i].v);
        if(x!=y) 
		{
            num++,h[x]=y;
            sum+=dl[i].pj;//上面解释了
        }
    }
    return sum>=0;
}
//////////////////////////////////////////////
int main()
{
    cin>>n>>m>>f;
    for(int i=1;i<=m;i++)cin>>dl[i].u>>dl[i].v>>dl[i].c>>dl[i].t;
    double l=0,r=1e9,mid;
    while(l+eps<r)
    {
        mid=(l+r)/2;
        if(check(mid)) l=mid;
        else r=mid;
    }
    printf("%.4lf\n",r);
    return 0;
}
```

### 注意：程序不保证与题解上所说分数相等，也不保证不编译错误，他们的作用只是让你明白思路

---

## 作者：Peter0701 (赞：0)

### **二分答案好题！**
这题虽然年代久远（2001），但是USACO出题者的智慧~~duliu~~确实让我们惊叹。

题意是说给出一张无向图，每条边有一个时间 $ t $ 和一个花费 $ c $ ，另给出酬劳 $ f $ ，求平均时间的利润。

不妨设平均时间的利润为 $ ans $ ，则 $ ans = \frac{ f - \sum{ c_i } }{ \sum{ t_i } }$ 。对式子进行变换易得 $ f - \sum{ c_i } - ans * \sum{ t_i } = 0 $ 。

令函数 $ f ( ans ) = f - \sum{ c_i } - ans * \sum{ t_i } $ ，显然 $ f ( ans ) $ 是具有单调性的，在本题范围内单调递减。

因此，我们可以采用二分答案的做法来解决这道题目，对 $ ans $ 进行二分。

当然，二分答案的精髓永远是 $ check $ 函数。本题中为了检验答案的合法性，由前面的式子不妨将每条边的权值设定为 $ c_i + ans * t_i $ ,通过跑一遍 $ Kruskal $ 很容易算出$ \sum{ c_i } + ans * \sum{ t_i } $ ，若 $ f $ 小于该值则答案过小，反之答案过大。

至此，本题结束！其余细节见下方代码。有疑问和指正评论区见，谢谢观看！

扩展阅读：[最优比率生成树](https://www.jianshu.com/p/d40a740a527e)

本题代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int ret=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0')
	{
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		ret=(ret<<1)+(ret<<3)+ch-'0';
		ch=getchar();
	}
	return ret*f;
}
int n,m,f,fa[405];
long long mid,l,r=2e15;
struct Edge
{
	int x;
	int y;
	int c;
	int t;
	double w;
}edge[10005];
inline bool cmp(Edge a,Edge b)
{
	return a.w<b.w;
}
inline int find(int x)
{
	if(fa[x]==x)
		return x;
	return fa[x]=find(fa[x]);
}
inline bool check(long long mid)
{
    for(register int i=1;i<=m;i++)
		edge[i].w=mid/(3e6+0.0)*edge[i].t+edge[i].c;
    int tmp=1;
    sort(edge+1,edge+m+1,cmp);
	for(register int i=1;i<=n;i++)
		fa[i]=i;
    double k=f+1e-12;
    for(register int i=2;i<=n;i++)
	{
        while(tmp<=m&&find(edge[tmp].x)==find(edge[tmp].y))
			tmp++;
        fa[find(edge[tmp].x)]=find(edge[tmp].y),k-=edge[tmp].w;
        if(k<0)
			return false;
    }
	return true;
}
int main()
{
    n=read();
	m=read();
	f=read();
    for(register int i=1;i<=m;i++)
	{
		edge[i].x=read();
		edge[i].y=read();
		edge[i].c=read();
		edge[i].t=read();
	}
    if(!check(0))
	{
		printf("0.0000\n");
		return 0;
	}
    while(l<r)
	{
        mid=(l+r)>>1;
        if(check(mid+1))
			l=mid+1;
        else
			r=mid;
    }
	printf("%0.4lf\n",l/(3e6+0.0));
    return 0;
}
```

---

