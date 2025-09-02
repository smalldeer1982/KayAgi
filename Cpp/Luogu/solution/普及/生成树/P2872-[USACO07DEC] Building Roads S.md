# [USACO07DEC] Building Roads S

## 题目描述

给定 $n$ 个点的坐标，第 $i$ 个点的坐标为 $(x_i,y_i)$，这 $n$ 个点编号为 $1$ 到 $n$。给定 $m$ 条边，第 $i$ 条边连接第 $u_i$ 个点和第 $v_i$ 个点。现在要求你添加一些边，并且能使得任意一点都可以连通其他所有点。求添加的边的总长度的最小值。

## 说明/提示

### 数据规模与约定

对于 $100\%$ 的整数，$1 \le n,m \le 1000$，$1 \le x_i,y_i \le 10^6$，$1 \le u_i,v_i \le n$。

### 说明

Translated by 一只书虫仔。

## 样例 #1

### 输入

```
4 1
1 1
3 1
2 3
4 3
1 4```

### 输出

```
4.00```

# 题解

## 作者：lzpclxf (赞：159)

每题感悟：

我一定要写这篇题解， 真的太令人智熄了！我交了7遍都不过原因竟是double的问题。一定要写篇题解来帮助和我一样可怜的孩子！

正文：
[题目](https://www.luogu.org/problem/P2872)

首先一起分析一下题目意思， 根据最后一句话使所有农场联通， 求最小和的值， 那么我们会很容易的联想到最小生成树， 是的， 正解之一就是最小生成树（然而我也只会这一个）。

但是现在有几个问题

1.我们只知道点的坐标并不知道各个点之间的距离

解决办法：循环嵌套枚举求出各个点与其后点的距离。 为什么是其后点， 就是比他编号大的点， 因为是双向边，例如从i到j会存一遍那么j从i也会再存一边， 无形之间， 就会变得更复杂

那么怎样写？

```cpp
for(int i = 1; i <= n; i++) {
		for(int j = i + 1; j <= n; j++) {
			double z = juli(i, j);
			add(i, j, z);
		}
	}
```
这样就会保证只加一次边啦！是不是恍然大悟！

2.怎样处理已知边

解决办法：在枚举完所有的边的距离之后， 在读入已知边， 这时两点之间的距离直接存为零即可， 表示从i到j的花费为零。

```cpp
for(int i = 1; i <= m; i++) {
		int x = read(), y = read();
		add(x, y, 0.0);
}
```
这里需要注意一下， 关于add函数中， **最后一个参数必须是double类型的！**

3.关于距离公式：（你们的楼主太差劲了， 专门去查的这个咋写 ， 笑）

$\sqrt{(x_1 - x_2)^2 + (y_1 - y_2)^2} $

但是必须要控制精度

否则#2 #8 #9 #10会挂掉！

别问我怎么知道的我就是知道

![](https://cdn.luogu.com.cn/upload/image_hosting/h8cjsnbo.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

所以你要改成这个亚子：
```cpp
double juli(int x, int y) {
	return (double)(sqrt((double)(E[x].x - E[y].x) * (E[x].x - E[y].x) + (double)(E[x].y - E[y].y) * (E[x].y - E[y].y)));
}
```
所以， 相应的

![](https://cdn.luogu.com.cn/upload/image_hosting/lrd2mjfd.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

好啦， 以上是便是楼主做这道题觉得可以给大家分享借鉴的地方啦！

The Last:
```cpp
#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 5000100;
int n, m, cnt, fa[N], sum;
double ans;
struct Node {
	int x, y;
}E[N];
struct node {
	int from, to;
	double w;
}e[N];
int read() {
	int s = 0, w = 1;
	char ch = getchar();
	while(!isdigit(ch)) {if(ch == '-') w = -1;ch = getchar();}
	while(isdigit(ch)) {s = s * 10 + ch - '0';ch = getchar();}
	return s * w;
}
void add(int x, int y, double z) {
	e[++cnt].from =x;
	e[cnt].to = y;
	e[cnt].w = z;
}
double jl(int x, int y) {
	return (double)(sqrt((double)(E[x].x - E[y].x) * (E[x].x - E[y].x) + (double)(E[x].y - E[y].y) * (E[x].y - E[y].y)));
}
bool cmp(node x, node y) {
	if(x.w == y.w) return x.from < y.from;
	return x.w < y.w;
}
int find(int x) {
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; i++) 
		E[i].x = read(), E[i].y = read();
	for(int i = 1; i <= n; i++) fa[i] = i;
	for(int i = 1; i <= n; i++) {
		for(int j = i + 1; j <= n; j++) {
			double z = jl(i, j);
			add(i, j, z);
		}
	}
	for(int i = 1; i <= m; i++) {
		int x = read(), y = read();
		add(x, y, 0.0);
	}
	sort(e + 1, e + 1 + cnt, cmp);
	for(int i = 1; i <= cnt; i++) {
		int fx = find(e[i].from), fy = find(e[i].to);
		if(fx != fy) {
			fa[fx] = fy;
			sum++;
			ans += e[i].w;
		}
		if(sum == n - 1) break;
	}
	printf("%.2lf\n", ans);
	return 0;
}
```
ps：你们的楼主太chao了，把图床里的图片删了， 导致题解的图片没了， 卑微...只能重新弄重新提交...（委屈

谢谢收看， 祝身体健康！






---

## 作者：Victorique (赞：28)

看了楼下两位dalao的kruskal的方法，只会用prim的本蒟蒻瑟瑟发抖。

具体说来，用prim对于这个题来说劣势不大，而且比较适合脑子转的慢的人，就是有几步比较巧妙。

代码里仔细解释：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
int x[1000001],y[1000001],b[1001],lj[10001],n,m,k,sum,h,l;
double a[1001][1001],d[10001],tot;
double js(int x1,int x2,int y1,int y2)
{
    return sqrt(pow(double(x1-x2),2)+pow(double(y1-y2),2));//这个地方必须强制double，也可以有其他写法，要不有四个点会输出-nan
}
//计算两点之间的距离。
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    cin>>x[i]>>y[i];
    for(int i=1;i<=n-1;i++)
     for(int j=i+1;j<=n;j++)
     {
         a[i][j]=a[j][i]=js(x[i],x[j],y[i],y[j]);//计算出每个点之间的距离，由于是无向图，所以可以减少循环次数。
     }
    for(int i=1;i<=m;i++)
    {
        cin>>h>>l;
        a[h][l]=a[l][h]=0;//这个地方关键，如果两城市之间有路，那么就把这两个城市之间的边的权值清零。
    }
    memset(d,0x7f,sizeof(d));
    for(int i=1;i<=n;i++)//往下是一个prim的模板，dalao可以略过。
    {
        d[i]=a[1][i];
    }
    d[1]=0;
    b[1]=1;
    for(int i=1;i<=n-1;i++)
    {
        k=0;
        for(int j=1;j<=n;j++)
        if(!b[j]&&d[j]<d[k])
        k=j;
        b[k]=1;
        for(int j=1;j<=n;j++)
        if(!b[j]&&a[j][k]<d[j])
        d[j]=a[j][k];
    }
    for(int i=1;i<=n;i++)
    {
        tot+=d[i];
    }
    printf("%.2lf",tot);//题目中没写，但是还是要保留两位。
}
```

---

## 作者：Blue_wonders (赞：23)

## kruskal算法AC
#### 这道题我A了n遍才过，为此，我特地写一篇题解让大家少走些弯路
### 各种错误
1. 对于错#2，#8，#9，#10 以及输出nan(not a number)的，看一下关于所有长度的数值是否都用double装了
2. 注意一下最后结果是不是两位小数，以及答案是不是开的double
3. kruskal算法比prim算法不管在时间复杂度和空间复杂度上都会有所增加，所以不要加一些没有用的步骤来增加时间~~我也不知到我干了啥~~
### 算法思路
这道题和[P2504 聪明的猴子](https://www.luogu.org/problemnew/show/P2504)比较像，做法基本上也差不了多少，大家可以看看

##### 这道题可以先记录距离的平方，加和的时候在开根，可以节约时间空间
1. 先对每一个点记录坐标
2. 对每两个点都进行距离运算(其实只用运算一次就够了，不管A到B还是B到A都是一样长)
3. 把已经建好的路的价值改成0
4. 进行kruskal运算(先按价值排序，然后并查集将所有点连在一棵树上，输出连起来所用的价值和)
5. 输出
### AC代码，附详解
[AC详情](https://www.luogu.org/recordnew/show/17411911)
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,q=0;
double ans=0;
int f[10001],d[10001][10001],l[10001][10001];
struct point{
int x,y;
} h[10001];
struct edge{
int s,e;
double w;
} g[1001000];
int cmd(edge a,edge b){return a.w<b.w;}
int find(int s){if(f[s]==s||f[s]==0)return f[s]=s;
    else return f[s]=find(f[s]);}
int k(){//kruskal 
    int cnt=0;//记录连接边的条数 
    for(int i=1;i<=q;i++){//对于边依次查找 
        int x=find(g[i].s);//找根节点 
        int y=find(g[i].e);
        if(x!=y){//如果两个根节点不一样，就说明两点之间不连通，所以修路，让两点联通 
            f[x]=y;
            ans+=sqrt(g[i].w);//路的距离加上，这里开根，节约时间空间 
            if(++cnt>=n-1)return ans;//return啥都一样，没用上(如果想用可以最后输出这个函数值)
        }
    }
}
int main(){
    cin>>n>>m;//输入 
    for(int i=1;i<=n;i++){//两重循环求每两个点的距离 
        cin>>h[i].x>>h[i].y;//每个点坐标输入 
        for(int j=1;j<i;j++){ 
            double u=(h[i].x-h[j].x+0.0)*(h[i].x-h[j].x+0.0)+(h[i].y-h[j].y+0.0)*(h[i].y-h[j].y+0.0);
            //这里记得开double，要不然W四个点(为啥只错4个)，求出距离的平方 
            g[++q]=(edge){i,j,u};//记录起点终点距离 
            l[i][j]=q;//记录两点之间是第几号边 
        }
    }
    for(int i=1;i<=m;i++){
        int Q,W;
        cin>>Q>>W;//输入已经修好的路 
        g[l[Q][W]].w=0.0;//L数组是求两点之间是第几条路 
        g[l[W][Q]].w=0.0;//已经修好了，所以连接不用再修 
    }
    sort(g+1,g+1+q,cmd);//排序，价值小的在前面
    k();//kruskal 
    printf("%.2lf",ans);//输出两位小数 
    return 0;
}
```
感谢大家能看我的题解!~

---

## 作者：Sshenyyyu (赞：22)

# 道路建设
找到题目呢，可以从题目上看出：为了使得所有农场连通，这是一题最小生成树模板题目。
但是，在一开始，有一些边就已经存在，那么就可以将它的权值赋为0，就可以了。
##### 贴代码，啦啦啦
```
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <cmath>
#include <iostream>
using namespace std;

const int Maxn=100001;

int n,m;
int xx[Maxn],yy[Maxn],f[Maxn],A,B;

struct node //结构体村存储边
{
	int x;
	int y;
	double val;	
}a[Maxn];

bool cmp(node a,node b)//排序，按权值从小到大，贪心思想
{
	if(a.val==b.val)
		return a.x<b.x;
	return a.val<b.val;	
}

int findr(int x)//并查集
{
	if(f[x]==x) return f[x];
	return f[x]=findr(f[x]);	
}

void merge(int x,int y)//合并
{
	f[findr(x)]=findr(y);	
}

int main()
{	
	int cnt=0;
	cin>>n>>m;
	for(int i=1; i<=n; i++)
		cin>>xx[i]>>yy[i];
	for(int i=1; i<=n; i++)//初始化，别忘了
		f[i]=i;
	for(int i=1; i<=n; i++)//枚举两两个点，存储进结构体数组，用公式算权值
		for(int j=i+1; j<=n; j++) {
			a[++cnt].x=i;
			a[cnt].y=j;
			a[cnt].val=(double)sqrt((double)(xx[i]-xx[j])*(xx[i]-xx[j])+(double)(yy[i]-yy[j])*(yy[i]-yy[j]));
		}
	for(int i=1; i<=m; i++) {//原有的边就把权值赋为0，就可以了
		cin>>A>>B;
		a[++cnt].x=A;
		a[cnt].y=B;
		a[cnt].val=0.0;
	}
	int top=0;
	double ans=0.0;
	sort(a+1,a+cnt+1,cmp);
	for(int i=1; i<=cnt; i++) {//模板，最小生成树
		if(findr(a[++top].x)!=findr(a[top].y)) {
			ans+=a[top].val;
			merge(a[top].x,a[top].y);
		}
	}
	printf("%.2lf",ans);//输出
	return 0;
}
```


---

## 作者：览遍千秋 (赞：7)

这道题很坑

---

思路：先读入所有的点，预处理出所有的边权。再读入已有的边，直接对并查集进行合并，最后跑一遍$Kruskal$就行了。

---

但是，按照这个思路，我写出了一份天然三色旗的代码_hua|ji_[传送门](https://www.luogu.org/record/show?rid=6096415)

这是那份代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define maxn 1007
struct node{
    int x,y,b;
}a[maxn];
struct bian{
    node b,e;
    double v;
}e[maxn*maxn];
int n,m,f[maxn],c,k,top;
double ans;
bool cmp(bian a,bian b)
{
    return a.v<b.v;
}
inline void distance()
{
    for(register int i=1;i<=n;i++)
        for(register int j=i+1;j<=n;j++)
            e[++top].b=a[i],e[top].e=a[j],e[top].v=sqrt((a[i].x-a[j].x)*(a[i].x-a[j].x)+(a[i].y-a[j].y)*(a[i].y-a[j].y));
}
int find(int x)
{
    return (f[x]==x) ? x : find(f[x]);
}
inline void build()
{
    for(register int i=1;i<=n;++i) f[i]=i;
}
inline void Init()
{
    scanf("%d%d",&n,&m);
    for(register int i=1;i<=n;++i) scanf("%d%d",&a[i].x,&a[i].y),a[i].b=i;
}
inline void Work()
{
    build();
    for(register int i=1;i<=m;i++)
    {
        scanf("%d%d",&c,&k);
        int q=find(c),w=find(k);
        f[w]=q;
    }
    distance();
    sort(e+1,e+top+1,cmp);
    for(register int i=1;i<=top;i++)
    {
        int q=find(e[i].b.b),w=find(e[i].e.b);
        if(q!=w)
        {
            ans+=e[i].v;
            f[q]=w;
        }
    }
    printf("%.2lf\n",ans);
}
int main()
{
    Init();
    Work();
    return 0;
}
```

---

过了一min，我意识到，是不是求距离错了，然后在$distance()$的$sqrt$中加了一个强制类型转换就A掉了。

code

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define maxn 1007
struct node{
    int x,y,b;
}a[maxn];
struct bian{
    node b,e;
    double v;
}e[maxn*maxn];
int n,m,f[maxn],c,k,top;
double ans;
bool cmp(bian a,bian b)
{
    return a.v<b.v;
}
inline void distance()
{
    for(register int i=1;i<=n;i++)
        for(register int j=i+1;j<=n;j++)
            e[++top].b=a[i],e[top].e=a[j],e[top].v=sqrt((double)(a[i].x-a[j].x)*(double)(a[i].x-a[j].x)+(double)(a[i].y-a[j].y)*(double)(a[i].y-a[j].y));
}
int find(int x)
{
    return (f[x]==x) ? x : find(f[x]);
}
inline void build()
{
    for(register int i=1;i<=n;++i) f[i]=i;
}
inline void Init()
{
    scanf("%d%d",&n,&m);
    for(register int i=1;i<=n;++i) scanf("%d%d",&a[i].x,&a[i].y),a[i].b=i;
}
inline void Work()
{
    build();
    for(register int i=1;i<=m;i++)
    {
        scanf("%d%d",&c,&k);
        int q=find(c),w=find(k);
        f[w]=q;
    }
    distance();
    sort(e+1,e+top+1,cmp);
    for(register int i=1;i<=top;i++)
    {
        int q=find(e[i].b.b),w=find(e[i].e.b);
        if(q!=w)
        {
            ans+=e[i].v;
            f[q]=w;
        }
    }
    printf("%.2lf\n",ans);
}
int main()
{
    Init();
    Work();
    return 0;
}
```

---

## 作者：SSHhh (赞：6)

这道题其实就是一个简单的最小生成树，用模板稍加改动就可以AC

大致思路是使用并查集，将边按从小到大排序后，每次询问最小的一条边的两个端点

如果这两条边不在同一个集合中，就把他们合并，ans+=边的长度。

最后用%.2Lf输出即可。

注意一点：已有的道路不用再建，所以边权是零。


下面是代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
long long x[1005],y[1005],pre[1005],tar=1;
long double ans=0;
bool have[1005][1005];//这条路是不是已有道路
struct nod
{
    int X,Y;
    long double w;//64位浮点类型防炸
}q[1000005];
bool cmp(nod i,nod j)
{
    return i.w<j.w;
}
long double cal(long long i,long long j) //d((x1,y1),(x2,y2))=sqrt((x1-x2)^2+(y1-y2)^2)
{                                        //具体可以参见初中数学 <平面直角坐标系+勾股定理>
    long long X=x[i]-x[j],Y=y[i]-y[j];
    return (long double)sqrt((long double)X*X+Y*Y);
}
//并查集算法，dalao不用看
int find(int i)//找爸爸
{
    if(pre[i]==i)    return i;
    return pre[i]=find(pre[i]);
}
void join(int a,int b)//合并
{
    if(find(a)==find(b))
        return;
    pre[find(a)]=b;
}
//并查集算法，dalao不用看
int main()
{
    memset(have,0,sizeof(have));
    long long n,m,a,b;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>x[i]>>y[i],pre[i]=i;
    for(int i=1;i<=m;i++)
    {
        cin>>a>>b;
        have[a][b]=have[b][a]=1;
        q[tar++]=(nod){a,b,0};//存储已知道路
    }
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            if(have[i][j]==0)//如果不是已知道路
                q[tar++]=(nod){i,j,cal(i,j)};//存储新建的道路
    tar--;
    sort(q+1,q+tar+1,cmp);
    //标准并查集
    for(int i=1;i<=tar;i++)
        if(find(q[i].X)!=find(q[i].Y))//如果这两条边不在同一个集合中
        {
            join(q[i].X,q[i].Y);//把他们合并
            ans+=q[i].w;//加上这条边
        }
    printf("%.2Lf",ans);//保留两位输出
    return 0;
}
```
还有一种优化算法：
读入已知道路的同时，因为边权为零，所以可以直接将其合并，不用进行存储。

```cpp
for(int i=1;i<=m;i++)
{
    cin>>a>>b;
    have[a][b]=have[b][a]=1;
    if(find(a)!=find(b))
        join(a,b);
}
```

---

## 作者：K2sen (赞：6)

# P2872

[传送门](https://www.luogu.org/problem/P2872)

## 首先

题目概括：题目让着求使所有牧场都联通.需要修建多长的路.

显然这是一道最小生成树板子题（推荐初学者做）.

## 那我就说一下kruskal吧.

Kruskal算法是一种用来查找最小生成树的算法，由Joseph Kruskal在1956年发表。

用来解决同样问题的还有Prim算法和Boruvka算法等。三种算法都是贪心算法的应用。

和Boruvka算法不同的地方是，Kruskal算法在图中存在相同权值的边时也有效。------- 来自于百度百科

### 一、基本思路
kruskal利用了一种贪心的思想，先把每一条边按照边权排一下序，利用并查集维护每一个点.

跑kruskal的时候先判断两个点是不是在一个集合里边，如果在那就说明不用再去连边了.

然后合并的时候记录边权，在搞一个记录加的边数的计数器.

大家都知道一张图如果有$n$个节点，那么最少$n-1$条边就可以吧这张图搞联通了.

那么我们就可以等到计数器的计数记到$n-1$ 的时候停止执行（已经得到正解）.

然后因为这$n-1$条边把图连成一起,那么显然$n - m$条边就可以把图分成m个部分（很好想鸭）.例题：[P1195](https://www.luogu.org/problem/P1195)

### 二、代码
```cpp
for (int i = 1; i <= cnt; i++) {
		if (father(edge[i].x) != father(edge[i].y)) {//判断是不是在一个集合中
			f++;
			unionn(edge[i].x, edge[i].y);//合并
			ans += edge[i].dis;//记录总权值
		}
		if (f == m) break;//如果做完了，那就停下啊.
	}
```

#### 此题代码及思路：
因为有一些边是一开始就有的，那么我们可以吧一开始就有的那些边都赋值成0，然后继续跑kruskal就好了.

因为给出的是坐标，那就先把坐标都存起来，然后把这些坐标依照欧几里得距离两两建边.

欧几里得距离公式：$\sqrt{((x_{1}-x_{2})*(x_{1}-x_{2}) + (y_{1}-y_{2}) * (y_{1}-y_{2}))}$

```cpp
#include <bits/stdc++.h>

#define N 1000010
#define M 2010

using namespace std;
int fath[M], n, m; bool b[M];
double px[M], py[M];
struct node {//结构体存边.
	int x, y;
	double dis;
}edge[N << 2];

int read() {
    int s = 0, f = 0; char ch = getchar();
    while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
    while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
    return f ? -s : s;
}

int father(int x) {
	if (x != fath[x]) fath[x] = father(fath[x]);//求是不是在一个集合里
	return fath[x];
}

void unionn(int x, int y) {
	int fx = father(x), fy = father(y);//合并两个集合
	fath[x] = fath[y];
}

bool cmp(node p, node q) {
	return p.dis < q.dis;//sort用品
}

int main() {
	n = read(), m = read();
	int z = n + m;//原本就有的
	for (int i = 1; i <= z; i++) fath[i] = i;
	int cnt = 0;
	for (int i = 1, x, y; i <= n; i++) {
		x = read(), y = read();
		px[i] = x, py[i] = y;//因为给出的是坐标，先把坐标存起来.
	}
	for (int i = 1; i <= n; i++) fath[i] = 1;
	for (int i = n + 1, x, y; i <= n + m; i++) {
		x = read(), y = read();
		px[i] = x, py[i] = y;
	}
	for (int i = 1; i <= n + m; i++) {
		for (int j = i + 1; j <= n + m; j++) {//开始存边
			cnt++;
			edge[cnt].x = i;
			edge[cnt].y = j;
			edge[cnt].dis = sqrt((px[i] - px[j]) * (px[i] - px[j]) + (py[i] - py[j]) * (py[i] - py[j]));
		}
	}
	sort(edge + 1, edge + cnt + 1, cmp);//给边排一下序
	int f = 0;
	double ans = 0;
	for (int i = 1; i <= cnt; i++) {//kruskal
		if (father(edge[i].x) != father(edge[i].y)) {
			f++;
			unionn(edge[i].x, edge[i].y);
			ans += edge[i].dis;
		}
		if (f == m) break;
	}
	printf("%.2lf", ans);
}
```

---

## 作者：lijiahao2017 (赞：6)

# P2872 【[USACO07DEC]道路建设Building Roads】



### 题目描述

$Farmer John had just acquired several new farms!$ 
$He wants to connect the farms with roads$ 
$so that he can travel from any farm to any other farm via a sequence of roads;$
$roads already connect some of the farms.$

$Each of the N (1 ≤ N ≤ 1,000) farms (conveniently numbered 1..N)$
$is represented by a position (Xi, Yi) on the plane (0 ≤ Xi ≤ 1,000,000; 0 ≤ Yi ≤ 1,000,000).$ 
$Given the preexisting M roads (1 ≤ M ≤ 1,000) as pairs of connected farms,$
$help Farmer John determine the smallest length of additional roads he must build to connect all his farms.$

$Farmer John$最近得到了一些新的农场，他想新修一些道路使得他的所有农场可以经过原有的或是新修的道路互达（也就是说，从任一个农场都可以经过一些首尾相连道路到达剩下的所有农场）。有些农场之间原本就有道路相连。 所有$N(1 <= N <= 1,000)$个农场（用$1..N$顺次编号）在地图上都表示为坐标为$(X_i, Y_i)$的点(0 <= X_i <= 1,000,000；0 <= Y_i <= 1,000,000)，两个农场间道路的长度自然就是代表它们的点之间的距离。现在$Farmer John$也告诉了你农场间原有的$M(1 <= M <= 1,000)$条路分别连接了哪两个农场，他希望你计算一下，为了使得所有农场连通，他所需建造道路的最小总长是多少。

### 输入输出格式

##### 输入格式：
* $Line 1: Two space-separated integers: N and M$

* $Lines 2..N+1: Two space-separated integers: Xi and Yi$

* $Lines N+2..N+M+2: Two space-separated integers:$ 
  $i and j, indicating that there is already a road connecting the farm i and farm j.$

第$1$行: $2$个用空格隔开的整数：$N$ 和 $M$

第$2..N+1$行: 第$i+1$行为$2$个用空格隔开的整数：$X_i$、$Y_i$

第$N+2..N+M+2$行: 每行用$2$个以空格隔开的整数$i$、$j$描述了一条已有的道路， 这条道路连接了农场$i$和农场$j$

##### 输出格式：
* $Line 1: Smallest length of additional roads required to connect all farms,$
  $printed without rounding to two decimal places.$
  $Be sure to calculate distances as 64-bit floating point numbers.$

输出使所有农场连通所需建设道路的最小总长，保留$2$位小数，不必做 任何额外的取整操作。为了避免精度误差，计算农场间距离及答案时 请使用$64$位实型变量

### 输入输出样例

##### 输入样例#1：
$4$ $1$

$1$ $1$

$3$ $1$

$2$ $3$

$4$ $3$

$1$ $4$
##### 输出样例#1：
$4.00$
### 说明

##### 题目简述：给出n个点的坐标,其中一些点已经连通,现在要把所有点连通,求修路的最小长度.

感谢@睿屿青衫丶 提供翻译



光阴似箭，日月如梭。

时间流逝，小菜鸡又可以和大家见面了。

这次，我来讲一道比较难的题(这只是我个人认为，对于$daolao$来说是水题。)

先看题目：

讲的是将所有点连通，要求花费最小。

一看就是最小生成树的模板题，只是有些路已经连通了。

三下五除二，干脆利落，先打出模板再根据题目需要进行修改。

## 直接讲$AC$思路：

### 1.先将已有的路连通起来

### 2.注意建边时用勾股定理，强制转化$double$类型。

### 3.将所有点连通，要加上边的值，最后保留$2$位输出。





上$AC$代码：
```cpp
#include<cstdio>//调用     scanf和printf      的库
#include<cmath>//调用     sqrt      的库
#include<algorithm>//调用     sort      的库
#include<cstdlib>//调用     exit      的库
using namespace std;
const int mx=1007;//定义mx常量
int n,m,len=0;
int f[mx];
double ans;//输出实数型
struct noda{int x,y,b;}a[mx];//点的结构体
struct nodb{noda b,e;double v;}e[mx*mx];//边的结构体
bool cmp(nodb a,nodb b) { return a.v<b.v; }//排序条件
int init()//初始化
{
    for(int i=1;i<=n;i++)f[i]=i;//一开始的老大是自己
}
int find(int x)//并查集
{
    if(f[x]==x)return x;
    else return f[x]=find(f[x]);
}
void ins()//建边，构图
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
        	if(i!=j)
        	{
        		len++;
            	e[len].b=a[i],e[len].e=a[j];
				e[len].v=sqrt((double)(a[i].x-a[j].x)*(double)(a[i].x-a[j].x)+(double)(a[i].y-a[j].y)*(double)(a[i].y-a[j].y));
                //注意勾股定理，强制转化$double$类型
        	}
		}
    }
}
void kruskal()
{
    sort(e+1,e+len+1,cmp);//排序
    //从小到大排，取最小边
    for(int i=1;i<=len;i++)
    {
        int tx=find(e[i].b.b);
		int ty=find(e[i].e.b);
        //找各自的老大
        if(tx!=ty)ans+=e[i].v,f[tx]=ty;
        //连通，并加上边的值
    }
    printf("%.2lf",ans);//输出，保留2位小数
    exit(0);//直接结束
}
int main()
{
	scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d%d",&a[i].x,&a[i].y),a[i].b=i;
    //输入
    init();//初始化
    int x,y;
    for(int i=1;i<=m;i++)
    {
        scanf("%d %d",&x,&y);
        int tx=find(x);
		int ty=find(y);
        f[tx]=ty;
    }
    //连通已有的边
    ins();//建边，构图
    kruskal();//建一棵最小生成树
    return 0;
}
```

---

## 作者：C_Cong (赞：5)

# 道路建设

 _Tips:博客内食用效果更佳 [传送门](https://dgsyrc.github.io/2019/08/16/%E6%B4%9B%E8%B0%B7%E9%A2%98%E8%A7%A3%20P2872%20%E3%80%90[USACO07DEC]%E9%81%93%E8%B7%AF%E5%BB%BA%E8%AE%BEBuilding%20Roads%E3%80%91/)_ 

####  题意：

给你$n$个农场的坐标，给出$m$条已经存在的路（连接农场$i$与农场$j$），求最少要修建多长的路才能把所有农场连接起来。

#### ~~上面的太啰嗦了，再简化一下：~~

给你$n$个节点，给出$m$条权值为0的边，每个节点彼此有一条边连接，边权值为两点的欧几里得距离，求该图的最小生成树大小。

欧几里得距离公式：$dis=\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$

------------------

 这道题我是用$Prim$做的，感觉$Prim$更好些，1000个点100条边算稀疏图吧

一定要注意在计算欧几里得距离时要在$sqrt()$里加double，不然就会卡精度WA2个点 ~~（别问我怎么知道的）~~

-----------------
### 代码解析：


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<cmath>
#define INF 20000000 //题中给出的没有那么大，但是开大点不会错
using namespace std;

struct edge
{
	double w;//边权
	int v;//终点
};

vector<edge> G[1010];//动态数组存边

int n,m,zb[1010][3],head;
bool pd[1010][1010],vis[1010];
double ans=0,f[1010];

double dis(int xa,int ya,int xb,int yb)//求欧几里得距离
{
	return sqrt((double)(xa-xb)*(xa-xb)+(double)(ya-yb)*(ya-yb));//注意此处的两个double，被卡WA了两次
}


int main()
{
	scanf("%d%d",&n,&m);
	for(int a=1;a<=n;a++)
	{
		scanf("%d%d",&zb[a][1],&zb[a][2]);//读入坐标
	}
	for(int a=1;a<=m;a++)//标记0权边
	{
		int x,y;
		scanf("%d%d",&x,&y);
		pd[x][y]=true;
		pd[y][x]=true;
	}
	for(int a=1;a<=n;a++)
	{
		for(int b=1;b<=n;b++)
		{
			if(a==b)
			{
				continue;
			}
			else
			{
				edge cmp;
				cmp.v=b;
				if(pd[a][b]==true)//如果被标记边权为0
				{
					cmp.w=0;
				}
				else
				{
					cmp.w=dis(zb[a][1],zb[a][2],zb[b][1],zb[b][2]);
				}
				G[a].push_back(cmp);//存边
			}
		}
	}
	for(int a=1;a<=n;a++)//初始化，赋极值
	{
		f[a]=INF;
	}
   //下方为Prim部分
	for(int a=0;a<G[1].size();a++)//预处理
	{
		int v=G[1][a].v;
		double w=G[1][a].w;
		f[v]=min(f[v],w);
	}
	vis[1]=true;//标记该节点已在最小生成树中
	for(int i=1;i<=n-1;i++)//n个节点，当然n-1条边
	{
		int V;
		double W=INF;//赋极值
		for(int j=1;j<=n;j++)
		{
			if(vis[j])
			{
				continue;
			}
			if(f[j]<W)
			{
				W=f[j];
				V=j;
			}
		}
		ans=ans+W;//统计最小生成树大小
		vis[V]=true;//标记该节点已在最小生成树中
		for(int a=0;a<G[V].size();a++)
		{
			int v=G[V][a].v;
			double w=G[V][a].w;
			f[v]=min(f[v],w);
		}
	}
	printf("%.2lf\n",ans);//输出
	return 0;//好习惯
}
```


---

## 作者：Hexarhy (赞：4)

这是一道比较模板的最小生成树，然额蒟蒻[调试](https://www.luogu.org/recordnew/lists?uid=80049&pid=2872&status=&sort=undefined)了很久……QAQ

> 编程五分钟，调试两小时



------------

### 思路$1$：$Prim+$堆优化$+$邻接矩阵建图

$1)$这道题目比较少题解介绍$Prim$啊。（~~不会Prim的出门右转百度等你）~~看看其他题解吧。

$2)$我们为了变得更优秀，采用堆优化，用空间换时间。效率提升是很可观的（$STL$的常数影响看$rp$了）。

$3)$对于已经修好的路，权值改为$0$就行，此时邻接矩阵就方便$O(1)$修改。注意无边权值为$-1$。

$4)$计算距离请参考【百度】或【初中数学】。

$5)$建图的时候点之间两两建边。

------------
易错点（害我调试很久的点）：

$1)$两点距离公式，在平方的时候要强转`double`

如：`sqrt((double)(x-a.x)*(double)(x-a.x)+(double)(y-a.y)*(double)(y-a.y))`

$2)$在建立堆的时候，用了$STL$，不过注意要么自己重载堆，要么`greater<pair<double,int> >`的时候，注意两个变量标识的顺序。因为堆默认是优先比较`first`的。如：

错误的：
```cpp

typedef pair<int,double> pid;
priority_queue <pid,vector<pid>,greater<pid> > q;

```


正确的：
```cpp

typedef pair<double,int> pdi;
priority_queue <pdi,vector<pdi>,greater<pdi> > q;

```

$3)$初始化$\infty$的时候别忘了是`double`类型。


------------

剩下都是细节。
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>
#include<vector>
#include<cmath>
#include<queue>
#include<climits> //冷门的头文件
using namespace std;

typedef pair<int,double> pid;
const double INF=double(INT_MAX*1.0);//要记得是double的
const int MAXN=10005;
int n,m;
double ans;
struct point
{
    int x,y;
    double operator+(const point& a)const
    {
        return sqrt((double)(x-a.x)*(double)(x-a.x)+(double)(y-a.y)*(double)(y-a.y));//计算两点距离公式，我用运算符，不用函数
    }
}a[MAXN];
double edge[MAXN][MAXN];
bool visit[MAXN],done[MAXN][MAXN];//done[][]是用来记录是否修了这条路
double dis[MAXN];

void build(void)
{
	for(int i=1;i<=n;i++)
	 for(int j=i+1;j<=n;j++)
	  if(!done[i][j])//没修
	   edge[j][i]=edge[i][j]=a[i]+a[j];//无向边
}

void input(void)
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
     for(int j=1;j<=n;j++)
      edge[i][j]=-1.0;//要记得没边就是-1
    for(int i=1;i<=n;i++)
     cin>>a[i].x>>a[i].y;
    for(int i=1;i<=m;i++)
    {
        int u,v;
        cin>>u>>v;
        done[v][u]=done[u][v]=true;
        edge[u][v]=edge[v][u]=0;//修了路就是边为0
    }
    build();
}

void prim(void)
{
    for(int i=1;i<=n;i++)
     dis[i]=INF;//别手残用memset，你懂得
    typedef pair<double,int> pdi;//上文说过注意事项
    priority_queue <pdi,vector<pdi>,greater<pdi> > q;
    q.push(pdi(0,1));
    dis[1]=0;
    int stop=0;//记录加入了几条边
    while(!q.empty() && stop<n)//模板堆优化Prim
    {
		const double distance=q.top().first;
        const int u=q.top().second;
        q.pop();
        if(visit[u])
         continue;
        visit[u]=true;
		ans+=distance;
        stop++;
        for(int v=1;v<=n;v++)
         if(edge[u][v]!=-1.0 && dis[v]>edge[u][v])
         {
         	dis[v]=edge[u][v];
         	q.push(pdi(dis[v],v));
		 }
    }
}

int main()
{
    input();
    build();
    prim();
    printf("%.2f",ans);
    return 0;
} 
```

------------


### 思路2：$Kruskal+$路径压缩

很多题解都有说，不再赘述。只说一个坑点：

> $edge$**数组一定要开的足够大！**建议$10^6$。

这就是我WA了的原因，奇怪不是RE。

其他的按照模板来也差不多了。

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
using namespace std;

const int MAXN=1010;
int n,m;
struct point
{
	int x,y;
	double operator+(const point& a)const
	{
		return double(sqrt(double(x-a.x)*double(x-a.x)+double(y-a.y)*double(y-a.y)));
	}
}a[MAXN];
struct node
{
	int from,to;
	double v;
	bool operator<(const node& a)const
	{
		return (v!=a.v)?(v<a.v):(from<a.from);
	}
}edge[MAXN*MAXN];
int f[MAXN];
double ans;
int cnt;
bool done[MAXN][MAXN];

void build(void)
{
	for(int i=1;i<=n;i++)
	 for(int j=i+1;j<=n;j++)
	  if(!done[i][j])
	   edge[++cnt]=(node){i,j,a[i]+a[j]};
}

void input(void)
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	 cin>>a[i].x>>a[i].y;
	for(int i=1;i<=m;i++)
	{
		int x,y;
		cin>>x>>y;
		done[x][y]=done[y][x]=true;
		edge[++cnt]=(node){x,y,0};
	}
	build();
}

int find(const int& x)
{
	return f[x]==x?x:f[x]=find(f[x]);
}

void kruskal(void)
{
	int stop=0;
	for(int i=1;i<=n;i++)
	 f[i]=i;
	sort(edge+1,edge+1+cnt);
	for(int i=1;i<=cnt;i++)
	{
		const int u=find(edge[i].from);
		const int v=find(edge[i].to);
		if(u==v)
		 continue;
		ans+=edge[i].v;
		f[u]=v;
		stop++;
		if(stop==n-1)
		 return;
	} 
}

int main()
{
	input();
	kruskal();
	printf("%.2f",ans);
	return 0;
}
```


------------
### 比较两种算法

#### 时间上：

$Prim$ 适合稠密图，复杂度为 $O(n^2)$，因此通常使用邻接矩阵储存；但是堆优化为 $O(nlogn)$ 。

稠密图$Prim$ 优于 $Kruskal$ ，稀疏图 $Kruskal$ 优于 $Prim$ 。

#### 空间上：

$Prim$ 适合点少边多， $Kruskal$ 适合边多点少。

> 注意：堆优化的$Prim$用空间换时间，空间要求更高。

看到下图两种方法比较：

明显堆优化的$Prim(233ms)$比$Kruskal(513ms)$快，时间只有它的一半，但$Prim(91.16MB)$消耗的内存比是$Kruskal(9.26MB)$的将近$10$倍。

![](https://cdn.luogu.com.cn/upload/pic/53479.png)
好像用这么多内存换来的时间有点得不偿失。

正是因为如此，有时大家要慎重选择两种算法，甚至普通$Prim$和堆优化的时间相差无几。

所以一般情况下$Kruskal$比较优秀，能胜任绝大多数题目的。

附上两次评测记录详情：

[堆优化的$Prim$](https://www.luogu.org/recordnew/show/17033651)

[$Kruskal$](https://www.luogu.org/recordnew/show/17031989)

---

## 作者：Nero_Claudius (赞：3)

这道题真的是令人窒息，Kruskal调了贼久一直RE，最后发现数组大小稍微少了那么一点点。（也就10倍吧。。）

言归正传，根据本人的分析（以及算法标签的提示），这是一道求最小生成树的题目，**当然要注意已经有一些路被建成了，因此他们直接标0即可。**

下面是这道题用到了的所有（全局）变量。

maxn, n, m就不解释了。

x[]和y[]是用来储存农场的坐标的，当然也可以用二维数组写，只是我懒得敲那么多字（说起来差别也不大）。

f是并查集中储存祖先的数组。

如果有不了解的并查集的可以参考这一片讲解，个人认为十分通俗易懂。 [传送门](https://www.luogu.org/blog/aaronlee/bing-zha-ji)

f1和f2是后面暂时储存有道路连接的农场的变量。

top是Kruskal主体中记录最顶层的。

cnt是记录长度的。

ans我觉得也是废话（耶，皮这一下我很开心）。

```cpp
const int maxn = 1000001;

int n, m;
int x[maxn], y[maxn], f[maxn], f1, f2;
int top = 0, cnt = 0;
double ans = 0;
```

接下来是储存两点距离的结构体，以及结构体排序。
```cpp
struct node {
    int x, y;
    double val; 
}dis[maxn];

bool cmp(node a, node b) {
    if(a.val == b.val)
        return a.x < b.x;
    return a.val < b.val;  
}
```

以及并查集模板（其中find函数使用了路径压缩）

```cpp
int find(int x) {  
    int r = x;  
    while(r != f[r]) r = f[r];  
    int i = x, j;  
    while(f[i] != r) {  
        j = f[i];  
        f[i] = r;  
        i = j;  
    }  
    return r;  
}  

void merge(int x, int y) {
	x = find(x);
	y = find(y);
	if(x != y) f[y] = x;
}
```

偶对了还有最没用的函数dt，用于求两点距离。
```cpp
double dt(int x1,int x2,int y1,int y2) {
    return sqrt(pow(double(x1 - x2), 2) + pow(double(y1 - y2), 2));
}
```

接下来果断开始主函数part。

读入数据，别忘了初始化并查集。

```cpp
cin >> n >> m;
for(int i = 1; i <= n; i++) cin >> x[i] >> y[i];
for(int i = 1; i <= n; i++) f[i] = i;
for(int i = 1; i <= n; i++)
    for(int j = i + 1; j <= n; j++) {
        dis[++cnt].x = i;
        dis[cnt].y = j;
        dis[cnt].val = dt(x[i], x[j], y[i], y[j]);
    }
for(int i = 1; i <= m; i++) {
    cin >> f1 >> f2;
    dis[++cnt].x = f1;
    dis[cnt].y = f2;
    dis[cnt].val = 0;
}
```

然后给dis排个序。

```cpp
sort(dis + 1, dis + cnt + 1, cmp);
```

最重要的部分：Kruskal模板

 _Kruskal算法将图中的每一个顶点视为一个独立的集合，首先将图中所有的边按权值大小从小到大排列，接着按顺序选择每一条边，如果这条边的两个端点不属于同一个集合，那么将它们所在的集合合并，同时将这条边加入E’。直到所有的顶点都属于同一个集合时，E’就是一颗最小生成树。_
 
                         --摘抄自《ACM国际大学生程序设计竞赛 知识与入门》

```cpp
for(int i = 1; i <= cnt; i++) {
    if(find(dis[++top].x) != find(dis[top].y)) {
        ans += dis[top].val;
        merge(dis[top].x, dis[top].y);
    }
}
```

最后，愉快的输出结果就好了，别忘了要保留两位小数。

---

## 作者：没有输入 (赞：2)

# 图论 · 最小生成树

不难看出，本题是 **最小生成树（MST）** 的模板题，主要考察对最小生成树算法的熟悉程度。

最小生成树有两种基本的算法，分别是 **克鲁斯卡尔（Kruskal）** 算法和 **普里姆(Prim)** 算法。相对而言，克鲁斯卡尔算法的适用面较普里姆更广，本题解介绍的算法也是克鲁斯卡尔算法。

### 基本思路

MST模板题。

### 步骤详解

用结构体存边，方便排序。

```cpp
struct Edge
{
	int u,v;
	double w;
} e[1000005];
```

**并查集** 模板（~~不知道的滚回去学并查集~~）

```cpp
int Find(int x)
{
	if(x==pre[x]) return x;
	return pre[x]=Find(pre[x]);
}
```

算距离（欧几里得距离）

```cpp
for(int i=1; i<n; i++)
	for(int j=i+1; j<=n; j++) e[++l].u=i,e[l].v=j,e[l].w=(double)sqrt((double)(x[i]-x[j])*(x[i]-x[j])+(double)(y[i]-y[j])*(y[i]-y[j]));
```
对于已有的道路，建造花费为0

```cpp
e[++l].u=u,e[l].v=v,e[l].w=0.0;
```

按花费从小到大排序

```cpp
sort(e+1,e+l+1,cmp);
```

克鲁斯卡尔算法

```cpp
for(int i=1; i<=l; i++)
{
	if(sum==n-1) break;
	int a=Find(e[i].u),b=Find(e[i].v);
	if(a==b) continue;
	sum++,ans+=e[i].w;
	pre[a]=Find(pre[b]);
}
```

## 标程

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,pre[1005],x[1005],y[1005],sum,l;
double ans;
struct Edge
{
	int u,v;
	double w;
} e[1000005];
bool cmp(Edge a,Edge b)
{
	return a.w<b.w;
}
int Find(int x)
{
	if(x==pre[x]) return x;
	return pre[x]=Find(pre[x]);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; i++) scanf("%d%d",&x[i],&y[i]),pre[i]=i;
	for(int i=1; i<n; i++)
		for(int j=i+1; j<=n; j++) e[++l].u=i,e[l].v=j,e[l].w=(double)sqrt((double)(x[i]-x[j])*(x[i]-x[j])+(double)(y[i]-y[j])*(y[i]-y[j]));
	for(int i=1; i<=m; i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		e[++l].u=u,e[l].v=v,e[l].w=0.0;
	}
	sort(e+1,e+l+1,cmp);
	for(int i=1; i<=l; i++)
	{
		if(sum==n-1) break;
		int a=Find(e[i].u),b=Find(e[i].v);
		if(a==b) continue;
		sum++,ans+=e[i].w;
		pre[a]=Find(pre[b]);
	}
	printf("%.2lf",ans);
	return 0;
}
```

## 最小生成树（MST）

一个有 n 个结点的连通图的生成树是原图的极小连通子图，且包含原图中的所有n 个结点，并且有保持图连通的最少的边。

最小生成树可以用kruskal（克鲁斯卡尔）算法或prim（普里姆）算法求出。

## 克鲁斯卡尔（Kruskal）算法 · 基本思路

先构造一个只含 n 个顶点、而边集为空的子图，把子图中各个顶点看成各棵树上的根结点，之后，从网的边集 E 中选取一条权值最小的边，若该条边的两个顶点分属不同的树，则将其加入子图，即把两棵树合成一棵树，反之，若该条边的两个顶点已落在同一棵树上，则不可取，而应该取下一条权值最小的边再试之。依次类推，直到森林中只有一棵树，也即子图中含有 n-1 条边为止。

------------

我是[没有输入](https://www.luogu.org/space/show?uid=154344)，我们下次再见！

---

## 作者：猪猪 (赞：2)

其实就是克鲁斯卡尔

原来连好的点预处理一下就行

真的好水QwQ












```cpp
uses math;
var f:array[1..1000] of longint;
    x,y:array[1..1000] of longint;
    a,b:array[1..999000] of longint;
    v:array[1..999000] of double;
    n,i,j,k,m,c,d,cc,dd,tot:longint; sum:double;
function find(x:longint):longint;//并查集路径压缩
    begin
        if f[x]=x then exit(x)
            else f[x]:=find(f[x]);
        exit(f[x]);
    end;
    procedure sort(l,r:longint);//按边排序
        var i,j,y:longint;    x,wjn:double;
        begin
        i:=l;
        j:=r;
        x:=v[(l+r) div 2];
        repeat
            while v[i]<x do inc(i);
            while x<v[j] do dec(j);
            if not(i>j) then
                begin
                    y:=a[i];a[i]:=a[j];a[j]:=y;
                    y:=b[i];b[i]:=b[j];b[j]:=y;
                    wjn:=v[i];v[i]:=v[j];v[j]:=wjn;
                    inc(i);
                    j:=j-1;
                end;
        until i>j;
        if l<j then sort(l,j);
        if i<r then sort(i,r);
      end;
    begin
        readln(n,m);
        for i:=1 to n do
            readln(x[i],y[i]);
                for i:=1 to n do f[i]:=i;
        for i:=1 to n do
        for j:=1 to n do
            if (i<>j) then
                begin
                    inc(tot);
                    a[tot]:=i;
                    b[tot]:=j;
                    v[tot]:=sqrt(double((x[i]-x[j]))**2+double((y[i]-y[j]))**2);
                                                    //算出各点之间的距离
                end;
        for i:=1 to m do//原来就连接的就放在同一个集合
            begin
                readln(c,d);
                cc:=find(c);dd:=find(d);
                if cc<>dd then
                    begin
                        f[cc]:=dd;
                        inc(k);
                    end;
            end;
        sort(1,tot);//排序
        for i:=1 to tot do//裸的克鲁斯卡尔
            begin
                cc:=find(a[i]);dd:=find(b[i]);
                if cc<>dd then
                    begin
                        f[cc]:=dd;
                        sum:=sum+v[i];
                        inc(k);
                    end;
                if k=n-1 then break;
            end;
        writeln(sum:0:2);
    end.

```

---

## 作者：never_see (赞：2)

看到没有C++的题解便顺手发一发。


Kruskal不用很解释，就是裸的，估计很多人卡在一个点就是后面4个


其原因是爆了数据类型，在求长度的时候一定要把x之差，y之差的平方项强行转化成double 否则会炸







```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN = 1001;
int n,m,Father[MAXN],x[MAXN],y[MAXN],Data_Size;
double Ans=0;
double Tmp;
struct Node{
    int u,v;double Dis;
    bool operator < (Node a) const {return Dis<a.Dis;}
}Data[MAXN*MAXN];//记录边，边数最多不超过n^2
int Find(int t){
    return t==Father[t]?t:Father[t]=Find(Father[t]);
```
}//并查集

double length(int a,int b){

    return sqrt((double)(x[a]-x[b])\*(x[a]-x[b])+(double)(y[a]-y[b])\*(y[a]-y[b]));

}//求长度，一定要加double


```cpp
void Ins(int u,int v,double Dis){
    Data[++Data_Size].u=u;
    Data[Data_Size].v=v;
    Data[Data_Size].Dis=Dis;
```
}//将数据添加到结构体中

    
    
```cpp
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&x[i],&y[i]);
        for(int j=1;j<i;j++)
            Ins(i,j,length(i,j));
    }
    sort(1+Data,1+Data_Size+Data);
    for(int i=1;i<=n;i++) Father[i]=i;
    for(int i=1,u,v;i<=m;i++){
        scanf("%d%d",&u,&v);
        u=Find(u);v=Find(v);Father[u]=v;
    }
    for(int i=1;i<=Data_Size;i++){//kruskal
        int u=Find(Data[i].u),v=Find(Data[i].v);
        if(u!=v){
            Father[u]=v;
            Ans+=Data[i].Dis;
        }
    }
    printf("%.2lf",Ans);
    return 0;
}
```

---

## 作者：ShineEternal (赞：1)

### [$My\ blog$](https://blog.csdn.net/kkkksc03)

## description:

在一个准备连边的图中已经连好一些边，问使图联通所需的最小价值。

## solution：

这道题和正常的最小生成树一样，只不过已经给出了一些边了。

但是如果直接把两个点连起来不怎么方便，怎么办呢？

突然发现了一个比较好的方法：

**把已经给出的边权值算做0就行了**

~~涨姿势了~~

个人认为代码写的不算太乱（虽然我是大括号换行的，值得一看）

## code:
```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
struct ben
{
	int x,y;
	double val;
}a[1000005];
int cmp(const ben &a,const ben &b)
{
	return a.val<b.val;
}
int fa[5005];
int find(int x)
{
	if(fa[x]!=x)return fa[x]=find(fa[x]);
	return fa[x];
}
double sqr(double ww)
{
	return ww*ww;
}
double x[1005],y[1005];
double d(int i,int j)
{
	return sqrt(sqr(x[i]-x[j])+sqr(y[i]-y[j]));
}
int main()
{
	int n,m,cnt=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=n;i++)
	{
		scanf("%lf%lf",&x[i],&y[i]);
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			double tmp=d(i,j);
			a[++cnt].x=i;
			a[cnt].y=j;
			a[cnt].val=tmp;
		}
	}
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		a[++cnt].x=x;
		a[cnt].y=y;
		a[cnt].val=0;
	}
	sort(a+1,a+cnt+1,cmp);
	double ans=0;
	int k=0;
	for(int i=1;i<=cnt;i++)
	{
		int x=find(a[i].x);
		int y=find(a[i].y);
		if(x!=y)
		{
			fa[y]=x;
			ans+=a[i].val;
			k++;
		}
		if(k==n-1)break;
	}
	printf("%.2lf\n",ans);
	return 0;
} 
```

---

## 作者：EarthGiao (赞：1)

## 【思路】
最小生成树 + 并查集     
在转换为double类型上面花了好久的时间    
一只忽略了这个小东西     
 
先读入数据     
将已经连接起来的点都合并起来    
如果这些就够用了    
那就输出0    
不然先预处理出所有的    
没有被连接起来的边   
一共就1000*1000个   
还可以稍加优化比如在没举的时候（详见代码）     
然后就成了1—1000累加起来那么就是跟少了哦     
将两个点和他俩算出来的距离用一个结构体存起来    
排一个序    
然后从小到大枚举跑克鲁斯卡尔就好了    

### 注意：   
一定要在求距离的时候将int转换为double    
可以用乘以一个1.0来解决       

## 【完整代码】
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm> 

using namespace std;
const int Max = 1005;
int x[Max],y[Max];
struct node
{
	int i,j;
	double v;
}a[Max * Max]; 
int father[Max * Max];

double work(int i,int j)
{
	double aa = (x[i] - x[j] * 1.0) * (x[i] - x[j] * 1.0);
	double bb = (y[i] - y[j] * 1.0) * (y[i] - y[j] * 1.0);//强制类型转换 
	return sqrt(aa + bb);
}

bool cmp(const node x,const node y)
{
	return x.v < y.v;
}

int find(int x)
{
	if(father[x] != x)father[x] = find(father[x]);
	return father[x];
}

void hebing(int x,int y)
{
	x = find(x);
	y = find(y);
	father[x] = y;
}

int main()
{
	int n,m;
	cin >> n >> m;
	for(register int i = 1;i <= n;++ i)
		father[i] = i;
	for(register int i = 1;i <= n;++ i)
		cin >> x[i] >> y[i];
	int qwq,awa;
	int js = 0;
	for(register int i = 1;i <= m;++ i)
	{
		cin >> qwq >> awa;
		if(find(qwq) != find(awa))
			hebing(qwq,awa),js ++;
		if(js == n - 1)break;
	}
	int jj = 0;
	for(register int i = 1;i <= n;++ i)
		for(register int j = i + 1;j <= n;++ j)//避免重复保证出现了1,2之后不会再出现2,1,是不是很简单？ 
			a[++ jj].i = i,a[jj].j = j,a[jj].v = work(i,j);
	sort(a + 1,a + 1 + jj,cmp);
	double ans = 0;
	for(register int i = 1;i <= jj;++ i)
	{
		if(find(a[i].i) != find(a[i].j))
			hebing(a[i].j,a[i].i),js ++,ans += a[i].v;
		if(js == n - 1)break;
	}
	printf("%.2lf\n",ans);
	return 0;
}
```

---

## 作者：doyo (赞：1)

NOIP2018后退坑的本蒟蒻，放寒假回来刷水题找自信

通读题目，这道题就是要求最小生成树，但是麻烦的是FJ自做聪明地修了几条路。

所以，把那两个点看做一个整体（缩点）不就行了吗

于是，本蒟蒻直接开始了Tarjan缩点，

当时间戳在指尖上流淌时，我蓦然回首

不对啊，一道黄题怎么可能这么麻烦。

接着检查了一下思路后发现，缩点……相当于把边权赋为0

这个操作怎么说也算巧妙吧

于是，代码如下

```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
#define db double//一堆double懒得写 
using namespace std;
const int maxm=5e5+1001;//1000个点可以连出(1000)*(999)/2条边 
const int maxn=1001;
int n,m,tot,fat[maxn];
db x[maxn],y[maxn],ans;
struct node
{
	int next;
	int to;
	db dis;
}edge[maxm];
bool cmp(node x,node y)
{
	return x.dis<y.dis;
}
inline db dist(db x1,db x2,db y1,db y2)
{//两点之间距离公式，才弃坑两个月的我一开始竟然把ABS记成了开平方 
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)); 
}
inline void addedge(int from,int to,db dis)
{
	edge[++tot].next=from;
	edge[tot].to=to;
	edge[tot].dis=dis;
}
int find(int x)//并查集 
{
	if(fat[x]==x) return x;
	fat[x]=find(fat[x]);
	return fat[x];
}
void kruskal()//kruskal最小生成树模板
{
	int f1,f2,k=0;
	for(int i=1;i<=n;i++) fat[i]=i;
	for(int i=1;i<=tot;i++)
	{
		f1=find(edge[i].next);
		f2=find(edge[i].to);
		if(f1!=f2)
		{
			fat[f1]=f2;
			ans+=edge[i].dis;
			k++;
			if(k==n-1) break;
		}
	}
}
int main()
{
	int xx,yy;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%lf%lf",&x[i],&y[i]);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&xx,&yy);
		addedge(xx,yy,0);//比较巧妙的操作 
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<i;j++)
			addedge(i,j,dist(x[i],x[j],y[i],y[j]));
	sort(edge+1,edge+tot+1,cmp);
	kruskal();
	printf("%.2f\n",ans);//注意保留两位小数 
	return 0;
}
```
做过一道操作更加巧妙的题，叫新的开始

http://ybt.ssoier.cn:8088/problem_show.php?pid=1488

想锻炼脑洞的同学可以做一做

---

## 作者：蕾姆酱QvQ (赞：1)

##### ~~为什么这么多恶意评分啊qwq，这题明明很水的说~~

### 好那么我们首先来看一下题意，题目让我们先找一边把需要建的一等公路先建出来~~（等级高就是可以为所欲为~~，然后再把剩余需要建的二等公路建出来

#### 其实我们可以用一个结构体，里面开两个dis值，分别代表一等和二等，手打两个cmp，排序之后疯狂找就好了qwq

#### 但是注意，由于题目让我们输出的是方案和最大值，而不是价钱，所以我们在跑kruskal的时候要注意把每一步的过程用一个数组保存下来，这样最后再筛一遍就能直接输出啦qwq

##### 剩下的一些过程放在代码里了qwq

### 另外，样例是错的qwq因为序号四建的应该是二等公路@lin_toto@chen_zhe

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>

using namespace std;

struct Edge1{
	int x,y,dis1,dis2,num;//dis1表示一等，dis2表示二等
}a1[100001];

int father[100001],k,m,n,maxx=0,k1=0,f[100001][2],m1=0; //f[1]表示建一等公路的序号f[0]表示二等的序号，结构体的num即可以表示

bool cmp1(Edge1 x,Edge1 y){return x.dis1<y.dis1;}//一等排序

bool cmp2(Edge1 x,Edge1 y){return x.dis2<y.dis2;}//二等排序

int find(int x)//找爹
{
	if(father[x]!=x) father[x]=find(father[x]);
	return father[x];
}

void unionn(int x,int y)//咱俩合起来了qwq！！
{
	x=find(x),y=find(y);
	father[x]=y;
}

int main()
{
	scanf("%d%d%d",&n,&k,&m);
	m--;//先减一好计算（其实是我容易忘
	for(int i=1; i<=n; i++) father[i]=i;//初始化
	for(int i=1; i<=m; i++)
	{
		int x,y,c1,c2;
		scanf("%d%d%d%d",&x,&y,&c1,&c2);
		a1[i].x=x; 
		a1[i].y=y;
		a1[i].dis1=c1;a1[i].dis2=c2;
		a1[i].num=i;//一定把序号存上
	}
	sort(a1+1,a1+m+1,cmp1);//一等先来
	for(int i=1; i<=m; i++)//标准最小生成树
	{
		if(find(a1[i].x)!=find(a1[i].y))
		{
			unionn(a1[i].x,a1[i].y);
			k1++;
			f[a1[i].num][1]=1; //保存此时你选择的边序号
		}
		if(k1==k)//行啦你建的差不多了该建点便宜的了
		{
			maxx=a1[i].dis1;
			break;
		}
	}
	k1=0;
	sort(a1+1,a1+m+1,cmp2);
	for(int i=1; i<=m; i++)//二等再跑一遍最小生成树
	{
		if(find(a1[i].x)!=find(a1[i].y))
		{
			unionn(a1[i].x,a1[i].y);
			k1++;
			f[a1[i].num][0]=1;
		}
		if(k1==n-k-1)
		{
			maxx=max(maxx,a1[i].dis2);
			break;
		}
	}
	printf("%d\n",maxx);
	for(int i=1; i<=m; i++) //找序号啦
		if(f[i][1]!=0) printf("%d 1\n",i);
		else if(f[i][0]!=0) printf("%d 2\n",i);
}				
```

---

## 作者：环日加速器 (赞：0)

最近在刷各种基础图论&&dp
# 这是一道类似于模板的最小生成树
我比较喜欢用Kruskal作图论，因为~~代码短~~

好吧，有以下几个原因：

1.Prim不加优化复杂度O(n*n),而Kruskal是(mlogm),相比较在稀疏图中Kruskal很占优势，Prim则在类似完全图中比较好，但在完全图中，Kruskal最多也只慢十几倍。

2.Prim由于是类似于Dijkstra，所以不能够处理最长路，而Kruskal可以。如下题，Kruskal就无法完成![](https://cdn.luogu.com.cn/upload/pic/71414.png )![](https://cdn.luogu.com.cn/upload/pic/71415.png )

在这题中，我们简单地用最长生成树解决

再减去总边长就是答案

## 所以这题就用Kruskal吧

备注：这题一开始我不知道为什么错了![](https://cdn.luogu.com.cn/upload/pic/71417.png)
直到看到它1. ![](https://cdn.luogu.com.cn/upload/pic/71418.png )
QAQ

```
#include<bits/stdc++.h>
using namespace std;
struct road
{
	long long x,y;
	long double val;
}a[1000009];
long long px[1009],py[1009];
bool used[1009][1009];
bool cmp(road x,road y)
{
	return x.val<y.val;
}
int f[1009];
int find(int x)
{
	if(x==f[x])return x;
	return f[x]=find(f[x]);
}
int main()
{
	int n,m,b=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%lld%lld",&px[i],&py[i]);
	for(int i=1;i<=m;i++)
	{
		long long xx,yy;
		scanf("%lld%lld",&xx,&yy);
		used[xx][yy]=1;
		used[yy][xx]=1;
		a[++b].x=xx;
		a[b].y=yy;
		a[b].val=0;
		a[++b].x=yy;
		a[b].y=xx;
		a[b].val=0;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(used[i][j])continue;
			a[++b].x=i;
			a[b].y=j;
			a[b].val=1*sqrt((px[i]-px[j])*(px[i]-px[j])+(py[i]-py[j])*(py[i]-py[j]));
		}
		f[i]=i;
	}
	sort(a+1,a+b+1,cmp);
	double ans=0;
	for(int i=1;i<=b;i++)
	{
		if(find(a[i].x)!=find(a[i].y))
		{
			f[find(a[i].x)]=find(a[i].y);
			ans+=a[i].val;
		}
	}
	printf("%.2lf",ans);
	return 0;
}
```
//为防止抄袭，改了一下代码，出精度问题不怪我

---

