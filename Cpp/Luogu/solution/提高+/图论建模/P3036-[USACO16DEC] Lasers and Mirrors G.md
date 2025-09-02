# [USACO16DEC] Lasers and Mirrors G

## 题目描述

出于某种原因，Farmer John 的奶牛似乎总是在举办激光表演。

在它们的最新表演中，奶牛们获得了一台大型强力激光器——事实上，这台激光器太大，以至于它们无法轻易从交付地点移动它。它们希望以某种方式将激光器的光束发送到 Farmer John 的农场另一边的谷仓。激光器和谷仓都可以被视为位于 Farmer John 农场地图的二维平面中的点。奶牛们计划将激光器指向水平或垂直方向（即与 $x$ 轴或 $y$ 轴对齐），然后通过多次反射镜将光束引导到谷仓。

农场上有 $N$ 个栅栏柱（$1 \leq N \leq 100,000$），位于与激光器和谷仓不同的二维点上，奶牛们可以在这些栅栏柱上安装反射镜。奶牛们可以选择不在栅栏柱上安装反射镜，在这种情况下，激光器会直接穿过栅栏柱而不改变方向。如果奶牛们在栅栏柱上安装反射镜，它们会将其对角线对齐，例如 / 或 \，以便将水平光束重新定向为垂直方向，反之亦然。

请计算奶牛们将激光器引导到谷仓所需的最少反射镜数量。

## 样例 #1

### 输入

```
4 0 0 7 2
3 2
0 2
1 6
3 0```

### 输出

```
1```

# 题解

## 作者：冯易菜鸡 (赞：13)

每个点拆成4个

 ![](https://cdn.luogu.com.cn/upload/pic/7360.png) 

蓝色虚线的边长度为0，橙色实线的边长度为1

然后再在节点中连边，像下图那样

 ![](https://cdn.luogu.com.cn/upload/pic/7362.png) 

最后建一个超级起点和超级终点，超级起点向原起点的四个节点连边（dis=0），原终点的四个节点向超级中电加边（dis=0）

跑最短路

各组节点之间连变的时候，可以分别按照x和y排序后加变


以样例为例：


 ![](https://cdn.luogu.com.cn/upload/pic/7368.png) 



---

## 作者：苏玖兮 (赞：6)

# [题解 P3036 【[USACO16DEC]Lasers and Mirrors G】](https://www.luogu.com.cn/problem/P3036)

## 离散化+最短路
- 先将数据离散化,然后将**每一行**,**每一列**都看做**一个点**,因为射线在同一行或同一列中转移是不会使用镜子的

- 考虑镜子安放的位置,因为每安放一个镜子,会导致射线垂直转移,所以如果某个点有镜子,我们就可以在该点的横坐标所映射的点与纵坐标所映射的点之间**连一条边权为1的边**,表示该行(或该列)上的射线可以通过花费一个镜子使得射线改变方向到该列(或该行)上

- 最后再在我们建的图上跑一遍最短路就行了,其他的细节代码注释里写得很详细了 

```
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
#include<map>
using namespace std;
const int N=2e5+5,M=N<<1;
int n,a,b,c,d;
int x[N],y[N],x2[N],y2[N],cnt1,cnt2;
int head[N],to[M],nxt[M],e[M],idx,dis[N],vis[N];

void add(int x,int y,int z)//建边 
{
	to[++idx]=y;nxt[idx]=head[x];e[idx]=z;head[x]=idx;
}

int askx(int x)//查询原来的横坐标的值所对应的离散后的值 
{
	return lower_bound(x2+1,x2+cnt1+1,x)-x2;
}
int asky(int y)//查询原来的纵坐标的值所对应的离散后的值 
{
	return lower_bound(y2+1,y2+cnt2+1,y)-y2;
}

void spfa()
{
	queue<int>q;
	memset(dis,0x3f,sizeof dis);
	q.push(askx(a));q.push(asky(b)+cnt1);//最初的起点从行射出去和从列射出去都要考虑 
	dis[askx(a)]=dis[asky(b)+cnt1]=0;
	vis[askx(a)]=vis[asky(b)+cnt1]=1;
	while(q.size())
	{
		int x=q.front();q.pop();vis[x]=0;
		for(int i=head[x];i;i=nxt[i])
		{
			int y=to[i],z=e[i];
			if(dis[y]>dis[x]+z)
			{
				dis[y]=dis[x]+z;
				if(!vis[y]) q.push(y),vis[y]=1;
			}
		}
	}
}
int main()
{
	scanf("%d%d%d%d%d",&n,&a,&b,&c,&d);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&x[i],&y[i]);
	x[n+1]=a;y[n+1]=b;//别忘了把起点和终点加进来 
	x[n+2]=c;y[n+2]=d;
	n+=2;
	memcpy(x2,x,sizeof x);//x2和y2是临时数组用于离散化 
	memcpy(y2,y,sizeof y);
	sort(x2+1,x2+1+n);
	sort(y2+1,y2+1+n);
	cnt1=unique(x2+1,x2+1+n)-x2-1;
	cnt2=unique(y2+1,y2+1+n)-y2-1;
	
	for(int i=1;i<=n;i++)//防止横纵坐标离散值编号冲突,给纵坐标的离散值加上cnt1 
	{
		add(askx(x[i]),asky(y[i])+cnt1,1);
		add(asky(y[i])+cnt1,askx(x[i]),1);
	}
	spfa();
	printf("%d",min(dis[askx(c)],dis[asky(d)+cnt1]));//输出答案,是从行转移过来更优还是从列转移过来更优 	
}
```

---

## 作者：henry_y (赞：4)

[$blog$](https://www.cnblogs.com/henry-1202/)

拆点题解的思路也好妙啊。

我的做法是搜索。挺好想的，就是不好写...

仔细研究一下题目，就可以发现几个性质：最优情况下，每个点肯定只会被访问一次，每条边（指网格）也仅会被访问一次。

所以这样子写个bfs的话是$O(n)$的。

实现方式有很多种...，维护3个vis数组，表示这一行/列有没有访问过，以及这个点有没有被访问过。

因为坐标有点大，然后可以发现的是只要是相同行的就能走到，所以可以先离散一波。

然后建两个图，对于每个点，从横坐标向纵坐标连边（另外一个图反着），边权均为1。

然后从起点开始bfs，对于每个点，拓展没有走过的点（这个点的横/纵坐标之一也必须是没走过的。）

分类讨论转移即可。细节好多...反正我是重构了3,4次...

```cpp
#include <bits/stdc++.h>
#define ll long long
#define inf 0x3f3f3f3f
#define il inline

namespace io {

#define in(a) a = read()
#define out(a) write(a)
#define outn(a) out(a), putchar('\n')

#define I_int ll
inline I_int read() {
    I_int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * f;
}
char F[200];
inline void write(I_int x) {
    if (x == 0) return (void) (putchar('0'));
    I_int tmp = x > 0 ? x : -x;
    if (x < 0) putchar('-');
    int cnt = 0;
    while (tmp > 0) {
        F[cnt++] = tmp % 10 + '0';
        tmp /= 10;
    }
    while (cnt > 0) putchar(F[--cnt]);
}
#undef I_int

}
using namespace io;

using namespace std;

#define N 100010

int n, s1, t1, s2, t2;
int vis[N][3], d[N], c[N];
struct task {
    int x, y;
    int id;
}a[N]; 
struct Queue {
    int x, y, dis;
};

#define pi pair<int,int>
#define mp make_pair
queue<Queue>q;
int head[N], Head[N], cnt;
struct edge {
    int to, nxt, id;
}e[N<<1], g[N<<1];

void ins(int u, int v, int id) {
    e[++cnt] = (edge) {v, head[u], id};
    g[cnt] = (edge) {u, Head[v], id};
    head[u] = cnt; Head[v] = cnt;
}

void bfs() { 
    q.push((Queue){a[n-1].x, a[n-1].y, 0});
    memset(vis, 0, sizeof(vis));
    while(!q.empty()) {
        Queue u = q.front(); q.pop();
        int dis = u.dis;
        if(u.x == a[n].x && u.y == a[n].y) {
        	outn(dis-1); return;
        }
        if(!vis[u.x][0]) {
        	for(int i = head[u.x]; i; i = e[i].nxt) {
        		if(!vis[e[i].id][2]) {
        			q.push({u.x, e[i].to, dis+1});
        			vis[e[i].id][2] = 1;
                }
            }
            vis[u.x][0] = 1;
        }
        if(!vis[u.y][1]) {
            for(int i = Head[u.y]; i; i = g[i].nxt) {
                if(!vis[g[i].id][2]) {
                    q.push({g[i].to, u.y, dis+1});
                    vis[g[i].id][2] = 1;
                }
            }
            vis[u.y][1] = 1;
        }
    }
    puts("-1");
}

int main() {
#ifndef ONLINE_JUDGE
freopen("3.in", "r", stdin);
#endif
    in(n);
    in(a[n+1].x), in(a[n+1].y), in(a[n+2].x), in(a[n+2].y);
    a[n+1].id = n+1; a[n+2].id = n+2;
    for(int i = 1; i <= n; ++i) 
        in(a[i].x), in(a[i].y), a[i].id = i;
    n+=2; 
    for(int i = 1; i <= n; ++i) c[i] = a[i].x;
    sort(c+1,c+n+1); for(int i = 1; i <= n; ++i) a[i].x = lower_bound(c+1,c+n+1,a[i].x)-c;
    for(int i = 1; i <= n; ++i) c[i] = a[i].y;
    sort(c+1,c+n+1); for(int i = 1; i <= n; ++i) a[i].y = lower_bound(c+1,c+n+1,a[i].y)-c;
    for(int i = 1; i <= n; ++i) {
        ins(a[i].x, a[i].y, i);
    }
    bfs();
}
``

---

## 作者：songzhihan2010 (赞：3)

这题其实有一个很显然的性质——光线在最优情况下最多只会经过一面镜子一次，原因很简单，要是这条光线再次经过了这面镜子，有三种可能，做下分类讨论

1. 要是射出的光线与之前的射出的光线方向相反，不如在第一次经过是直接将镜子翻个方向，只消耗一个机会，达到相同效果。
2. 要是原路返回，因为光线反射具有可逆性，所以显然不优。
3. 要是与第一种情况相反，不如直接不用这面镜子

有了这个结论，接下来的事情就会变得简单，我们可以开一个 vis 数组，记录这面镜子是否使用过，然后直接跑 dfs 即可 

但是，还有一个问题，怎样将有关系的镜子连边？ $\operatorname O(n^2)$ 建边肯定是不行的，但是我们好好想想，见下图
![](https://cdn.luogu.com.cn/upload/image_hosting/a89q8ghy.png)
这张图片中如果暴力建边，则要建 $A-B,B-C,A-C$ 三条边，但是聪明的你肯定发现 $A-C$ 这条边可以用 $A-B$ 和 $B-C$ 连起来表示，所以，我们可以在 dfs 中多传入一个参数face，表示从上个节点来到这个节点的方向，对于与之前方向一样的边就可以不计入答案，这样就只要先将点的坐标排序，对于 $x_i==x_{i-1}$ 的两个点，连边就可以了，但是，如果跳过了一个节点连边则会使 dfs 没有正确性，所以记得排序是要将 $y$ 作为第二关键字

 $y$ 的处理方式相同，不在赘述


 ### Code ###
 ```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll read()
{
	ll x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
ll vis[100010];
ll ans=1e18;
vector<ll> e[100010];
struct Dian{
	ll x,y,pos;
}a[100010];
ll n;
bool cmp(Dian x,Dian y){
	if(x.x==y.x) return x.y<y.y;
	return x.x<y.x;
}
bool cmp1(Dian x,Dian y){
	if(x.y==y.y)return x.x<y.x;
	return x.y<y.y;
}
bool cmp2(Dian x,Dian y){
	return x.pos<y.pos;
}
ll get(ll sz,ll sy){
	if(a[sz].x==a[sy].x&&a[sz].y<a[sy].y){
		return 1;
	}
	if(a[sz].x==a[sy].x&&a[sz].y>a[sy].y){
		return 3;
	}
	if(a[sz].y==a[sy].y&&a[sz].x<a[sy].x){
		return 2;
	}
	if(a[sz].y==a[sy].y&&a[sz].x>a[sy].x){
		return 4;
	}
	return 11111;
}
void dfs(ll t,ll face,ll cost){
	if(cost>ans){
		return ;
	}
	for (int i=0;i<e[t].size();i++){
		if(!vis[e[t][i]]){
			vis[e[t][i]]=1;
			if(get(t,e[t][i])==face){
				if(e[t][i]==2) ans=min(ans,cost);
				else dfs(e[t][i],face,cost);
			} else {
				if(e[t][i]==2) ans=min(ans,cost+1);
				else dfs(e[t][i],get(t,e[t][i]),cost+1);
			}
			vis[e[t][i]]=0;
		}
	}
}
signed main(){
//	freopen("marble.in","r",stdin);
//	freopen("marble.out","w",stdout);
	n=read();
	for (int i=1;i<=n+2;i++){
		a[i].x=read();
		a[i].y=read();
		a[i].pos=i;
	}
	sort(a+1,a+3+n,cmp);
	for (int i=2;i<=n+2;i++){
		if(a[i].x==a[i-1].x){
			e[a[i].pos].push_back(a[i-1].pos);
			e[a[i-1].pos].push_back(a[i].pos);
		}
	}
	sort(a+1,a+3+n,cmp1);
	for (int i=2;i<=n+2;i++){
		if(a[i].y==a[i-1].y){
			e[a[i].pos].push_back(a[i-1].pos);
			e[a[i-1].pos].push_back(a[i].pos);
		}
	}
	sort(a+1,a+3+n,cmp2);
	vis[1]=1;
	dfs(1,1,0);
	memset(vis,0,sizeof(vis));
	vis[1]=1;
	dfs(1,2,0);
	memset(vis,0,sizeof(vis));
	vis[1]=1;
	dfs(1,3,0);
	memset(vis,0,sizeof(vis));
	vis[1]=1;
	dfs(1,4,0);
	printf("%lld\n",ans==1e18?-1:ans);
}
```

---

## 作者：cavve (赞：2)

###  STL + BFS 做法

先看一个简单样例：
```
2 0 0 3 4
0 3
3 3
```
不难发现，此样例的结果为 $2$ 。激光从起点 $(0,0)$ 出发，向上下左右四个方向发散，向上的光线经过镜子 $1$ 的反射，产生向右到达镜子 $2$ 的反射，最终产生向上的光线穿过中点（如下图所示）。
![](https://cdn.luogu.com.cn/upload/image_hosting/8buw8s50.png)
与拆点构图的做法不同，我将光线抽象为点，镜子则为转换光线方向的结点，并花费 $1$ 的费用。

而将光线抽象为点的一个好处是不需要使用最短路求解，因为每一条光线要么使用 $1$ 的费用改变方向，要么出队，可以保证队列的单调性，可以使用 queue ，降低时间复杂度。

这种思路最关键的一点就是如何存边（即转换光线方向），可以用离散化进行，但为了方便（~~偷懒~~），可以用 map 套 set 的神奇写法（用迭代器，这里不细讲）。另外，在进行 BFS 的时候，为了防止重复，需要将使用过的镜子删除。

细节见代码。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, xl, yl, xb, yb;
int a, b;
int dst[100005];
 
map<int, set<pair<int, int> > > xz, yz;
 
struct www{
    int s, l, b;//for b, 1 is |, 0 is -
    /*bool operator<(const www& x) const{
        return x.s < s;
    }*/
    //不要问我为什么写了重载运算符
    //因为一开始没发现单调性
};
 
queue<www> q;
 
void bfs(){
    q.push((www){0, xl, 1});
    q.push((www){0, yl, 0});
    //入队
    
    while(!q.empty()){
        www u = q.front(); q.pop();
        int s = u.s, l = u.l, b = u.b;
        
        if((l == xb && b == 1) || (l == yb && b == 0)){
            printf("%d", s);
            return;
        }
        //检查是否能照到终点
        
        if(b == 1){
            auto it = xz[l].begin();
            while (it != xz[l].end()){
                if(dst[(*it).first] == 0){
                    q.push((www){s + 1, (*it).second, 0});
                    dst[(*it).first] = 1;
                }
                auto del = it; it++;
                xz[l].erase(del);
                //dst是用来记录访问过的镜子，在之后遍历到时删除
            }
        }
        else{
            auto it = yz[l].begin();
            while (it != yz[l].end()){
                if(dst[(*it).first] == 0){
                    q.push((www){s + 1, (*it).second, 1});
                    dst[(*it).first] = 1;
                }
                auto del = it;
                it++;
                yz[l].erase(del);
            }
        }
        //拓展
    }
}
 
int main()
{
    scanf("%d%d%d%d%d", &n, &xl, &yl, &xb, &yb);
    for(int i = 1; i <= n; i++){
        int x, y;
        scanf("%d%d", &x, &y);
        xz[x].insert(pair<int, int>{i, y});// ---
        yz[y].insert(pair<int, int>{i, x});//  |
    }
    bfs();
    return 0;
}
```


---

## 作者：ACcepted917 (赞：1)

# P3036 题解

### [题目传送门](https://www.luogu.com.cn/problem/P3036)

## 分析

**拆点法 + dijkstra**

### 建图

将一个坐标点拆成四个点：

![](https://cdn.luogu.com.cn/upload/image_hosting/dihfs6y2.png)

把一个“大”点拆成四个“小”点后，连接这些小点，使得任意两小点都有边，如图中红蓝色的双向边。其中，**红色边**代表光路要反射，需要一个镜子，所以边权为 $1$；**蓝色边**代表光路不用反射，直接穿过栅栏柱而不改变方向，不需要镜子，所以边权为 $0$。

将每个小点都编号，设大点的输入时的顺序排名为 $id$，则每个小点对应的编号如上图所示，如最上方的小点编号为 $4 \times (id-1)+2+1(=4\times id+3-4)$。

编号为 $1$ 的小点设为激光器的位置，即起点；编号为 $2$ 的小点设为谷仓的位置，即终点。

那么样例的图示为:

![](https://cdn.luogu.com.cn/upload/image_hosting/r12u7auc.png)

如图，**绿色边**不仅连接了小点，也连接了大点，如 $4$ 号小点与 $9$ 号小点的边，连接了 $id=1$ 和 $2$ 的大点，表示光可以从 $id=1$ 的大点传递到 $id=2$ 的大点（反向也行，为双向边）。由于光沿直线传播，所以不需要反射镜，绿色边权为 $0$。

**如何实现绿色边：**

将大点以横坐标快速排序，找到横坐标相等的大点，把大点中合适的小点连接，如下图中的①②。

![](https://cdn.luogu.com.cn/upload/image_hosting/nbd3n0w0.png)

接着处理纵坐标，同理，排序后找纵坐标相等的大点，连接即可，如③④。

图中**黑色边**为起点、终点双向直达边，连接所有起点、终点与所有能直接通过传递光到达的大点，不需要反射镜，所以边权为 $0$，如下图①~④。

**如何实现黑色边：**

对于连接终点的黑色边，找到与其横、纵坐标相等的大点，连接大点中合适的小点，如下图①②。

![](https://cdn.luogu.com.cn/upload/image_hosting/yo0cznxa.png)

对于连接起点的黑色边，同理连接即可，如图中③④。

红蓝色边同上。

### 最短路

现在，把上面得到的无向图运行一下以起点（编号为 $1$）为原点的堆优化版 dijkstra，输出 `dis[2]`（终点的编号为 $2$），就解决了这道蓝题。

## 代码（请勿抄袭，后果自负!!!）

```cpp
#include<bits/stdc++.h>
using namespace std;
const unsigned long long N=4e5+5,M=2e6+5,prime=233317,mod=212370440129904639,base=131;
typedef long long ll;
//#define int ll
int n,m,t,xl,yl,xb,yb,a[N],b[N],vis[N],dis[N],head[N],ecnt=0,cnt=0;
#define inf 0x3f3f3f3f
struct node{//链式前向星
	int nxt,to;
	int w;
}e[M];
struct stu{
	int id,a,b;
}f[N];
bool cmpa(stu x,stu y){
	if(x.a!=y.a)return x.a<y.a;
	return x.b<y.b;
}
bool cmpb(stu x,stu y){
	if(x.b!=y.b)return x.b<y.b;
	return x.a<y.a;
}
inline void addedge(int x,int y,int z){
	e[++ecnt].to=y;
	e[ecnt].w=z;
	e[ecnt].nxt=head[x];
	head[x]=ecnt;
	return;
}
//最短路
void dijkstra(int beg){//O((n+m)log n)
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	priority_queue<pair<int,int> >pque;
	dis[beg]=0;
	pque.push(make_pair(0,beg));
	int x,y,z;
	while(!pque.empty()){
		x=pque.top().second;
		pque.pop();
		if(!vis[x]){
			vis[x]=1;while(true) cout<<"Plagiarists are shameless\n";
			for(int i=head[x];i!=0;i=e[i].nxt){
				y=e[i].to,z=e[i].w;
				if(dis[x]+z<dis[y]){
					dis[y]=dis[x]+z;
					pque.push(make_pair(-dis[y],y));
				}
			}
		}
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>xl>>yl>>xb>>yb;
    //建图
	for(register int i=1;i<=n;i++){
		cin>>f[i].a>>f[i].b;
		f[i].id=i;
        //蓝色边
		addedge(4*f[i].id+3-4,4*f[i].id+6-4,0);
		addedge(4*f[i].id+6-4,4*f[i].id+3-4,0);
		addedge(4*f[i].id+4-4,4*f[i].id+5-4,0);
		addedge(4*f[i].id+5-4,4*f[i].id+4-4,0);
        //红色边
		addedge(4*f[i].id+3-4,4*f[i].id+4-4,1);
		addedge(4*f[i].id+4-4,4*f[i].id+3-4,1);
		addedge(4*f[i].id+3-4,4*f[i].id+5-4,1);
		addedge(4*f[i].id+5-4,4*f[i].id+3-4,1);
		addedge(4*f[i].id+4-4,4*f[i].id+6-4,1);
		addedge(4*f[i].id+6-4,4*f[i].id+4-4,1);
		addedge(4*f[i].id+5-4,4*f[i].id+6-4,1);
		addedge(4*f[i].id+6-4,4*f[i].id+5-4,1);
	}
    //特判，起点横坐标与终点横坐标相等或起点纵坐标与终点纵坐标相等
	if(xl==xb || yl==yb){
		cout<<0<<'\n';
		return 0;
	}
    //绿色边
	sort(f+1,f+1+n,cmpa);
	for(register int i=2;i<=n;i++){
		if(f[i].a==f[i-1].a){
			if(f[i].b<f[i-1].b){
				addedge(4*f[i].id+3-4,4*f[i-1].id+6-4,0);
				addedge(4*f[i-1].id+6-4,4*f[i].id+3-4,0);
			}
			else if(f[i].b>f[i-1].b){
				addedge(4*f[i-1].id+3-4,4*f[i].id+6-4,0);
				addedge(4*f[i].id+6-4,4*f[i-1].id+3-4,0);
			}
		}
	}
	sort(f+1,f+1+n,cmpb);
	for(register int i=2;i<=n;i++){
		if(f[i].b==f[i-1].b){
			if(f[i].a>f[i-1].a){
				addedge(4*f[i].id+4-4,4*f[i-1].id+5-4,0);
				addedge(4*f[i-1].id+5-4,4*f[i].id+4-4,0);
			}
			if(f[i].a<f[i-1].a){
				addedge(4*f[i-1].id+4-4,4*f[i].id+5-4,0);
				addedge(4*f[i].id+5-4,4*f[i-1].id+4-4,0);
			}
		}
	}
    //黑色边
	for(register int i=1;i<=n;i++){
		if(f[i].a==xl){
			addedge(1,f[i].id*4+3-4,0);
			addedge(f[i].id*4+3-4,1,0);
			addedge(1,f[i].id*4+6-4,0);
			addedge(f[i].id*4+6-4,1,0);
		}
		if(f[i].b==yl){
			addedge(1,f[i].id*4+4-4,0);
			addedge(f[i].id*4+4-4,1,0);
			addedge(1,f[i].id*4+5-4,0);
			addedge(f[i].id*4+5-4,1,0);
		}
		if(f[i].a==xb){
			addedge(f[i].id*4+3-4,2,0);
			addedge(2,f[i].id*4+3-4,0);
			addedge(f[i].id*4+6-4,2,0);
			addedge(2,f[i].id*4+6-4,0);
		}
		if(f[i].b==yb){
			addedge(f[i].id*4+4-4,2,0);
			addedge(2,f[i].id*4+4-4,0);
			addedge(f[i].id*4+5-4,2,0);
			addedge(2,f[i].id*4+5-4,0);
		}
	}
    //最短路
	dijkstra(1);
	if(dis[2]==inf)cout<<-1<<'\n';
	else cout<<dis[2]<<'\n';
	return 0;
}
``````

---

## 作者：nothing__ (赞：0)

## STL+BFS做法
[AC历程](https://www.luogu.com.cn/paste/tohvl1cn)
也是AC得很坎坷。

### 思路：
* 使用vector+map记录每一面镜子的坐标。注意：因为每一行每一列可能会有多个镜子，又行列坐标范围太大，我们需要用map离散化。
* 将终点也看作一面镜子加入其中，最后统计答案时-1即可。
* 主要有两项剪枝：

1.如果当前镜子的其中一个坐标与终点的一个坐标相对应，那么将它加入到队头。

2.如果当前行或列的镜子被遍历过，那么跳过，因为肯定加入过队列。

代码如下：

```c++
#include<bits/stdc++.h>
#include<unordered_map>
using namespace std;
typedef pair<int, int> PII;
const int N=1e6+10;
int n; bool vc[N], vr[N];
unordered_map<int, int> c, r;
vector<int> col[N], row[N];
struct node{int x, y;} st, ed;
struct type{int x, y, op, res;} ;
map<PII, bool> mp[2];
void bfs() {
	int ans=0; 
	deque<type> q;
	q.push_back({st.x, st.y, 0, 0});
	q.push_back({st.x, st.y, 1, 0});
	mp[1][{st.x, st.y}]=true;
	mp[0][{st.x, st.y}]=true;
	while(!q.empty()) {
		auto x=q.front(); q.pop_front();
		if(x.x==ed.x&&x.y==ed.y) {ans=x.res-1; break;}
		if(x.op==0) {
			if(vc[c[x.x]]) continue; vc[c[x.x]]=true;
			for(auto i:col[c[x.x]]) {
				if(!mp[0][make_pair(x.x, i)]) {
					if(i==ed.y) q.push_front({x.x, i, 1, x.res+1});
					else q.push_back({x.x, i, 1, x.res+1});
					mp[0][make_pair(x.x, i)]=true;
				}
			}
		}
		else {
			if(vr[r[x.y]]) continue; vr[r[x.y]]=true;
			for(auto i:row[r[x.y]]) {
				if(!mp[1][make_pair(i, x.y)]) {
					if(i==ed.x) q.push_front({i, x.y, 0, x.res+1});
					else q.push_back({i, x.y, 0, x.res+1});
					mp[1][make_pair(i, x.y)]=true;
				}
			}
		}
	}
	printf("%d\n", ans);
}
int main() {
	scanf("%d", &n);
	scanf("%d%d%d%d", &st.x, &st.y, &ed.x, &ed.y);
	for(int i=1;i<=n;i++) {
		int x, y; scanf("%d%d", &x, &y);
		if(c[x]==0) c[x]=i;  if(r[y]==0) r[y]=i;
		col[c[x]].push_back(y); row[r[y]].push_back(x);
	}
	if(c[ed.x]==0) c[ed.x]=n+1; 
	if(r[ed.y]==0) r[ed.y]=n+1;
	col[c[ed.x]].push_back(ed.y);
	row[r[ed.y]].push_back(ed.x);
	bfs();
	return 0;
}
```

---

## 作者：Aurora_Borealis_ (赞：0)

首先观察要素：

- 镜子的最小可能数量

- $1\leq x,y \leq 10^9$

前者很容易想到 01bfs 的思路，而后者则提醒我们要离散化。

同时不难发现，01bfs 的复杂度瓶颈在于求当前点向四周能到达的点，如果每一个点都单独求，那复杂度就炸掉了。

这时可以预处理。用 vector 记录每一列（或列）的点，排序后可以用 $\operatorname{lowerbound}$ 函数进行 $O(\log n)$ 查找。

这种做法的复杂度固然不是很优秀，但关键在于每一步都很显然，思维难度较低。

---

## 作者：study_nerd (赞：0)

思路：我们可以把每个可以放镜子的栅栏抽象成一个点，因为光线只能沿水平或竖直方向传播，所以可以将横纵坐标进行排序，让所有横/纵坐标相等的点在一块，对每一块中所有点连边，然后就可以得到一张图。

这是问题就转化成了找出一条从起点到终点的路径中经过的点数最少的路径，算出它经过的点数。

但是有一个问题，如果数据中出现很多点排成一行，那最多可能会让边数达到 (n+1)/2 ，这样连图都还没建完就超时了，所以我们可以让每一块中间的点都只和它前一个点连接，这样边数就会少很多。

但如果这样又会有新的问题，在同一行的点本来不经过别的点就可以到，但现在就需要一个一个跳，会增加很多多出来的点。我们可以给每条路径设一个参数，表示这条边是横向还是纵向的。给每一个进队节点也增加一个参数，表示它是通过哪种边进来的，如果这个点通过和它过来时同一方向的边到达下一个点，就不需要给经过的节点数加一，否则就加。

还有，因为到达终点是不要再加点的，所以我给每个可以直达终点的的点和终点都连了一条边，然后判了一下，这样在经过终点时就不会再多加了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct Edge
{
	int nxt,to,val;
}edge[200010];
int n,head[100005],cnt;
struct node
{
	int id,x,y;
}a[100005];
struct qq{int sum,now,val;};
bool cmp1(node a,node b){return a.x<b.x;}
bool cmp2(node a,node b){return a.y<b.y;}
void add(int u,int v,int w)
{
	edge[++cnt].nxt=head[u];
	edge[cnt].to=v;
	edge[cnt].val=w;
	head[u]=cnt;
	return;
}
int vis[100005];
int main()
{
	memset(vis,0x3f3f3f3f,sizeof(vis));
	cin>>n;
	n+=2;
	for(int i=1;i<=n;++i)scanf("%d%d",&a[i].x,&a[i].y),a[i].id=i;
	sort(a+1,a+n+1,cmp1);
	int now=-1,sum;
	for(int i=1;i<=n;++i)if(a[i].id==2){sum=i;break;}
	for(int i=1;i<=n;++i)
	{
		if(a[i].x!=now){now=a[i].x;}
		else
		{
			add(a[i].id,a[i-1].id,0);
			add(a[i-1].id,a[i].id,0);
		}
		if(a[sum].x==a[i].x)
		{
			add(a[i].id,a[sum].id,1);
			add(a[sum].id,a[i].id,1);
		}
	}
	sort(a+1,a+n+1,cmp2);
	now=-1;
	for(int i=1;i<=n;++i)if(a[i].id==2){sum=i;break;}
	for(int i=1;i<=n;++i)
	{
		if(a[i].y!=now){now=a[i].y;}
		else
		{
			add(a[i].id,a[i-1].id,1);
			add(a[i-1].id,a[i].id,1);
		}
		if(a[sum].y==a[i].y)
		{
			add(a[i].id,a[sum].id,1);
			add(a[sum].id,a[i].id,1);
		}
	}
	queue<qq>q;
	qq w;
	int ans=2147483647;
	w.now=1;
	w.sum=0;
	w.val=-1;
	q.push(w);
	while(!q.empty())
	{
		qq x=q.front();
		q.pop();
		if(x.now==2){ans=min(ans,x.sum);continue;}
		if(vis[x.now]<=x.sum)continue;
		vis[x.now]=x.sum;
		for(int i=head[x.now];i;i=edge[i].nxt)
		{
			int to=edge[i].to;
			w.now=to;
			w.sum=x.sum;
			if(to!=2&&edge[i].val!=x.val)w.sum++;
			w.val=edge[i].val;
			if(vis[to]>w.sum)q.push(w);
		}
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：AllenReder (赞：0)

# BFS + 优先队列优化

预处理输入数据，储存 **起点 转折点 终点** 的坐标，通过 *id* 转录到节点（**Node**）中，每个节点储存信息有下面几种

| 标识符 | 含义 |
| :----------: | :----------: |
| x | 横坐标 |
| y | 纵坐标 |
| *up | 上方的节点 |
| *down | 下方的节点 |
| *left | 左方的节点 |
| *right | 右方的节点 |

- 这里的上下左右节点用指针记录，方便操作

---

BFS 过程中以节点的信息为基准进行搜索，搜索过程中保存**三个信息**

- 当前节点
- 当前激光方向
- 当前转折次数

**优先队列优化**：优先扩展**转折次数**最少的节点，可以保证搜索的有向性，最快到达终点。（也防止爆空间 OTZ）

---

代码如下：

```cpp
#include <iostream>
#include <cstring>
#include <queue>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

const int N = 400005;

int n;
int bx, by, ex, ey;
struct Pos
{
    int x, y, id;
} pos[N];
int pos_c;
// 排序函数
bool cmp1(Pos a, Pos b)
{
    if (a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
};
bool cmp2(Pos a, Pos b)
{
    if (a.y == b.y)
        return a.x < b.x;
    return a.y < b.y;
};
bool cmp3(Pos a, Pos b)
{
    return a.id < b.id;
};
// 节点
struct Node
{
    int x, y;
    Node *up = NULL;
    Node *down = NULL;
    Node *left = NULL;
    Node *right = NULL;
} node[N];
// BFS 储存信息用的结构体
struct Search
{
    Node *node;
    int dire, step;
};
bool operator<(Search a, Search b)
{
    return a.step > b.step;
}
int vis[N];
int bfs()
{
    
    priority_queue<Search> q;
    // 起点分别向四个方向搜索
    // 1 上
    // 2 右
    // 3 下
    // 4 左
    q.push({&node[1], 1, 0});
    q.push({&node[1], 2, 0});
    q.push({&node[1], 3, 0});
    q.push({&node[1], 4, 0});
    while (!q.empty())
    {
        Search now = q.top();
        q.pop();
        // 搜索到终点了
        if (now.node->x == ex && now.node->y == ey)
        {
            // 直接输出退出
            cout << now.step << endl;
            exit(0);
        }
        // 如果上方有节点
        if (now.node->up != NULL)
        {
            if (now.dire == 1)
                q.push({now.node->up, 1, now.step});
            if (now.dire == 2 || now.dire == 4)
                q.push({now.node->up, 1, now.step + 1});
        }
        // 如果右方有节点
        if (now.node->right != NULL)
        {
            if (now.dire == 2)
                q.push({now.node->right, 2, now.step});
            if (now.dire == 1 || now.dire == 3)
                q.push({now.node->right, 2, now.step + 1});
        }
        // 如果下方有节点
        if (now.node->down != NULL)
        {
            if (now.dire == 3)
                q.push({now.node->down, 3, now.step});
            if (now.dire == 2 || now.dire == 4)
                q.push({now.node->down, 3, now.step + 1});
        }
        // 如果左方有节点
        if (now.node->left != NULL)
        {
            if (now.dire == 4)
                q.push({now.node->left, 4, now.step});
            if (now.dire == 1 || now.dire == 3)
                q.push({now.node->left, 4, now.step + 1});
        }
    }
}

int main()
{
    // 读入加速，懒得写 read 了 OTZ
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> bx >> by >> ex >> ey;
    bx++, by++, ex++, ey++; // 将 0 ~ n - 1 转为 1 ~ n，虽然本题好像用不到
    // 记录起点坐标
    pos[++pos_c] = {bx, by, pos_c};
    node[pos_c].x = bx;
    node[pos_c].y = by;
    for (int i = 1, t1, t2; i <= n; ++i)
    {
        cin >> t1 >> t2;
        t1++, t2++;
        // 记录转折点坐标
        pos[++pos_c] = {t1, t2, pos_c};
        node[pos_c].x = t1;
        node[pos_c].y = t2;
    }
    // 记录终点坐标
    pos[++pos_c] = {ex, ey, pos_c};
    node[pos_c].x = ex;
    node[pos_c].y = ey;
    // 连接，分别按 x 和 y 坐标排序，相邻的 pos 只有两种情况
    // 1: 在同一行（列）
    // 2: 不在同一行也不在同一列
    sort(pos + 1, pos + 1 + pos_c, cmp1);
    for (int i = 1; i < pos_c; ++i)
    {
        if (pos[i].x == pos[i + 1].x)
        {
            node[pos[i].id].down = &node[pos[i + 1].id];
            node[pos[i + 1].id].up = &node[pos[i].id];
        }
    }
    sort(pos + 1, pos + 1 + pos_c, cmp2);
    for (int i = 1; i < pos_c; ++i)
    {
        if (pos[i].y == pos[i + 1].y)
        {
            node[pos[i].id].right = &node[pos[i + 1].id];
            node[pos[i + 1].id].left = &node[pos[i].id];
        }
    }
    sort(pos + 1, pos + 1 + pos_c, cmp3);
    // 搜索
    bfs();
    // getchar();
    return 0;
}
```


---

