# [ARC064E] Cosmic Rays

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc064/tasks/arc064_c

$ x $$ y $ 平面があります。 すぬけ君は座標 $ (x_s,\ y_s) $ から座標 $ (x_t,\ y_t) $ まで移動しようとしています。 すぬけ君は好きな向きへ速さ $ 1 $ で動くことができます。 なお、すぬけ君は大きさのない点と見なすことにします。

平面上には $ N $ 個の円形のバリアが張ってあります。 $ i $ 番目のバリアは中心が $ (x_i,\ y_i) $ で半径が $ r_i $ です。 バリアは互いに重なっていたり、互いを含んでいたりすることがあります。

平面上の各座標について、その座標がどのバリアの内部にも含まれない場合、その座標には宇宙線が降り注いでいます。

すぬけ君は移動中にできるだけ宇宙線を浴びたくないので、宇宙線を浴びる時間が最小になるように移動します。 すぬけ君が移動中に宇宙線を浴びる時間の最小値を求めてください。

## 说明/提示

### 制約

- 入力はすべて整数である。
- $ -10^9\ <\ =\ x_s,\ y_s,\ x_t,\ y_t\ <\ =\ 10^9 $
- $ (x_s,\ y_s) $ ≠ $ (x_t,\ y_t) $
- $ 1\ <\ =N\ <\ =1,000 $
- $ -10^9\ <\ =\ x_i,\ y_i\ <\ =\ 10^9 $
- $ 1\ <\ =\ r_i\ <\ =\ 10^9 $

### Sample Explanation 1

たとえば、図のように移動すればよいです。 !\[e9c630751968b7051df5750b7ddc0e07.png\](https://atcoder.jp/img/arc064/e9c630751968b7051df5750b7ddc0e07.png)

### Sample Explanation 2

たとえば、図のように移動すればよいです。 !\[fb82f6f4df5b22cffb868ce6333277aa.png\](https://atcoder.jp/img/arc064/fb82f6f4df5b22cffb868ce6333277aa.png)

### Sample Explanation 3

たとえば、図のように移動すればよいです。 !\[d09006720c225cbe69eae3fd9c186e67.png\](https://atcoder.jp/img/arc064/d09006720c225cbe69eae3fd9c186e67.png)

## 样例 #1

### 输入

```
-2 -2 2 2
1
0 0 1```

### 输出

```
3.6568542495```

## 样例 #2

### 输入

```
-2 0 2 0
2
-1 0 2
1 0 2```

### 输出

```
0.0000000000```

## 样例 #3

### 输入

```
4 -2 -2 4
3
0 0 2
4 0 1
0 4 1```

### 输出

```
4.0000000000```

# 题解

## 作者：Noir_ (赞：4)

说实话，最初看到题目中说的“可以向任意方向移动”吓了一跳，脑中脑补了各种行走的蜿蜒曲径。。。

~~在一不小心点开标签后~~才发现，其实只是一个坑点在误导读者。

### 题目大意

最短路定义为经过的未被覆盖区域，给定起点和终点，求最短路

### 思路

##### 问题1：最短路跑什么？

首先我们要想清楚一件非常重要的性质，题目中给定的最短路只有一个条件：经过的未被覆盖的路径；

也就是说，为了尽可能的减少暴露的路径的长度，不论覆盖区域中的路径长度有多长，都要走这条路（~~所以据说输出0都可以得到35分的好成绩~~）

##### 问题2：最短路怎么跑？

解决完问题1后，第二个问题迎面而来：最短路怎么跑？

相信一定有不少人这时脑中也脑补了各种弯曲的路线，但我们转念一想：

以下这种情况，哪条路径更优？（蓝色or绿色）

![](https://pic.imgdb.cn/item/616063d42ab3f51d9156160f.jpg)

无法判断的话，可以这么理解：

我们以start为圆心，第一段蓝色线段暴露的路径为半径画圆，与黑色的圆相切与A点；

![](https://pic.imgdb.cn/item/616067332ab3f51d915e28f4.jpg)

那么第一段蓝色线段一定垂直于切线，而绿色线段与切线有一定的夹角；

所以第一段蓝色线段暴露的路径长度比绿色线段短；

同理，第二段蓝色线段暴露的路径长度也比绿色线段短，所以蓝色路比绿色路优。

至此，我们得到了一条重要的结论：**对于一个覆盖的区域来说，经过它的圆心永远比不经过圆心优**

##### 问题3：怎样转化成最短路？

其实题目隐藏了一条重要信息：**起点和终点也有覆盖范围，只不过是0**

那么我们就可以把所有点都归成一类：

```cpp
struct node{int x,y,len;}a[N];//坐标及半径
```

瞄一眼数据范围：$n\le1000$

这么小？直接点之间两两连边！

1. 点的编号？就是读入顺序，起点和终点另外加两个。

2. 边权？两个点之间的欧几里得距离减去两个点覆盖区域的半径。

3. 怎么跑？dij或spfa皆可，裸的最短路板子。

### 代码

```cpp
#include<bits/stdc++.h>
#define N 1005//点数
#define M 1000005//边数
#define inf 0x3f3f3f3f3f3f3f3f//inf开大一点，数据范围是1e9
#define endl '\n'
#define debug cerr<<__LINE__<<endl
using namespace std;
int n,m;
int xs,xt,ys,yt;
inline int read(){
	register int f=1,k=0;
	register char c=getchar();
	while(c!='-'&&(c<'0'||c>'9')) c=getchar();
	if(c=='-') f=-1,c=getchar();
	while(c>='0'&&c<='9') k=(k<<3)+(k<<1)+(c^48),c=getchar();
	return f*k;
}
inline void write(register int x){
    if(x<0) x=-x,putchar('-');
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
inline long long mul(const register int x){return 1ll*x*x;}//一定要记得开long long
inline double get_dis(int x,int y,int a,int b){return sqrt(mul(a-x)+mul(b-y));}//欧几里得距离
namespace first{//特判了一下前20%数据
	int xx,yy,len;
	inline double solve(){
		xx=read(),yy=read(),len=read();
		return min(get_dis(xs,ys,xt,yt),get_dis(xx,yy,xs,ys)+get_dis(xt,yt,xx,yy)-(len<<1));
	}
}
namespace second{
	int head[N],cnt;
	double dis[N];//欧几里得距离，用double
	bool vis[N];
	struct edge{int to,nxt;double val;}e[M<<1];//同上，double
	struct node{int x,y,len;}a[N];
	priority_queue<pair<double,int>,vector<pair<double,int> >,greater<pair<double,int> > >q;
	inline void add(register int u,register int v,register double w){
		e[++cnt].to=v;e[cnt].val=w;e[cnt].nxt=head[u];head[u]=cnt;
		e[++cnt].to=u;e[cnt].val=w;e[cnt].nxt=head[v];head[v]=cnt;
	}
	inline void dijkstra(const register int s){
		fill(dis+1,dis+n+3,inf);//因为是double类型，所以不能用memset，fill是比for循环更好的选择
		dis[s]=0;q.emplace(0,s);//即q.push(make_pair(0,s));
		while(!q.empty()){//裸的最短路板子
			const register int u=q.top().second;q.pop();
			if(!vis[u]){
				vis[u]=1;
				for(register int i=head[u];i;i=e[i].nxt){
					const register int v=e[i].to;
					if(dis[v]>dis[u]+e[i].val){
						dis[v]=dis[u]+e[i].val;
						q.emplace(dis[v],v);
					}
				}
			}
		}
	}
	inline double solve(){
		for(register int i=1;i<=n;i++) a[i].x=read(),a[i].y=read(),a[i].len=read();
		a[n+1]=(node){xs,ys,0};a[n+2]=(node){xt,yt,0};//额外把起点和终点都当成覆盖区域
		for(register int i=1;i<=n+2;i++)
		for(register int j=i+1;j<=n+2;j++) add(i,j,max(0.0,get_dis(a[i].x,a[i].y,a[j].x,a[j].y)-a[i].len-a[j].len));
		//注意这里要特判dis，如果dis<0就说明两个圆有交集，边权直接赋为0
		dijkstra(n+1);return dis[n+2];
	}
}
main(void){
    freopen("1.in","r",stdin);
	xs=read(),ys=read();
	xt=read(),yt=read();n=read();
	if(n==1) return printf("%.10lf\n",first::solve()),0;//前20%数据
	return printf("%.10lf\n",second::solve()),0;//后80%数据
    return 0;
}
```

码风较奇葩（~~压行强迫症+卡常小能手~~）

欢迎觉得做法很麻烦或有错误的巨佬来喷







---

## 作者：Accelessar (赞：2)

[AT 题面](https://atcoder.jp/contests/arc064/tasks/arc064_c) [洛谷题面](/problem/AT_arc064_c)

### 题意

在一个平面直角坐标系中，给定起点和终点，以及若干个圆。请找出从起点到终点的一条路径，使得经过的不在任一圆内的长度最小。

### 思路

先来考虑如何使一个点到一个圆的距离最小，显然路径垂直于圆的切线时该路径最短。

再将它推广到多个圆之间，发现依次连接两圆圆心所得到的路径最短。

那么本题的建边方式就是在每两个圆的圆心之间连一条边，起点与终点可看作半径为 $0$ 的圆。那么根据题意，圆 $i$ 与圆 $j$ 之间的边的边权为：

$$dis_{i,j}=\max\left(0,\sqrt{(x_i-x_j)^2+(y_i-y_j)^2}-r_i-r_j\right)$$

注意，当两圆相交时，算出的 $dis_{i,j}<0$，而这条路径暴露在圆外的长度应为 $0$，所以我们将 $dis_{i,j}$ 对 $0$ 取 $\max$。

代码实现的时候还有个坑，就是 $dis$ 数组的初始值要足够大，我试了若干个常用的 $\inf$ 值最后只有 $\text{DBL\_MAX}$ 过了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1010;
int n;
double w,dis[N];
struct Point{double x,y,r;}p[N];
struct edge{int v;double w;};
vector<edge> e[N];

inline double dist(Point a,Point b){
    return max(sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y))-a.r-b.r,0.0);
}
void dijkstra(int s){
    priority_queue<pair<double,int>> pq;
    pq.push({dis[s]=0,s});
    while(!pq.empty()){
        int u=pq.top().second;pq.pop();
        if(dis[u]==DBL_MAX)continue;
        for(auto ed:e[u])
            if(dis[ed.v]>dis[u]+ed.w)pq.push({-(dis[ed.v]=dis[u]+ed.w),ed.v});
    }
}

int main(){
    cin>>p[1].x>>p[1].y>>p[2].x>>p[2].y;p[1].r=p[2].r=0;
    cin>>n,n+=2;
    for(int i=3;i<=n;i++)cin>>p[i].x>>p[i].y>>p[i].r;
    for(int i=1;dis[i]=DBL_MAX,i<=n;i++)for(int j=i+1;j<=n;j++)
        w=dist(p[i],p[j]),e[i].push_back({j,w}),e[j].push_back({i,w});
    dijkstra(1),printf("%.10lf",dis[2]);
    return 0;
}
```

[AC 记录](https://atcoder.jp/contests/arc064/submissions/38648540)

---

## 作者：iranai (赞：1)

# **题意理解**
### 给定起点、终点和 $$n$$ 个圆，求从起点到终点的路径中不在圆中的最短距离。
## **思路**
1. 最短距离：不难发现，从一个圆到另一个圆，将两圆圆心相连时，不在圆内的距离可以达到最短，先计算出两个圆之间的距离，减去两圆半径，剩下的就是在圆外的距离。（注意是 **double** 类型）

2. 建图：先处理出每个圆之间的路径不在圆内的最短距离，然后一一连边（我这里是用的链式前向星），起点和终点要额外建！

 3. 方法：这里用的是 **dijkstra 堆优化版**。

4. 坑点（对我这个蒟蒻而言）：路径初始化时要大一些，之前因为这个我 WA 了好多次！

## **代码**
```
#include<bits/stdc++.h>
using namespace std;
double xs,ys,xt,yt;
int n;
int h[10010];
int to[20000010];
int nt[10000010];
double w[10000010];
int idx;
bool v[10010];
double d[10010];
void add(int x,int y,double z){
	to[idx]=y;
	w[idx]=z;
	nt[idx]=h[x];
	h[x]=idx;
	idx++;
}
typedef pair<double,int> PII;
priority_queue<PII,vector<PII>,greater<PII> > hp;
void dijkstra_hp(int u){//求最短路
	d[u]=0;
	hp.push((PII){0,u});
	while(hp.size()>0){
		PII top=hp.top();
		hp.pop();
		int t=top.second;
		if(!v[t]){
			v[t]=true;
			for(int i=h[t];i!=-1;i=nt[i]){
				int j=to[i];
				if(d[t]+w[i]<d[j]) d[j]=d[t]+w[i],hp.push((PII){d[j],j});
			}
		}
	}
}
struct E{//用来存储一个圆的信息
	double x;
	double y;//x,y表示该圆圆心坐标为(x,y)
	double r;//r表示该圆的半径为r
} a[10010];
int main(){
	memset(h,-1,sizeof(h));
	cin>>xs>>ys>>xt>>yt;
	a[1]=(E){xs,ys,0};//单独用1个半径为0的圆（即一个点）存储起点
	cin>>n;
	a[n+2]=(E){xt,yt,0};//额外用一个半径为0的圆（即一个点）存储终点
	for(int i=1;i<=n+2;i++) d[i]=1e18;//记得初始化大一点
	for(int i=2;i<=n+1;i++){
		double x,y,r;
		cin>>x>>y>>r;
		a[i]=(E){x,y,r};
	}
	for(int i=1;i<=n+1;i++){
		for(int j=i+1;j<=n+2;j++){
			double ww=sqrt((a[i].x-a[j].x)*(a[i].x-a[j].x)+(a[i].y-a[j].y)*(a[i].y-a[j].y))-a[i].r-a[j].r;
			if(ww<0) ww=0;//为负表示两圆相交，直接赋值为0即可
			add(i,j,ww);
			add(j,i,ww);//双向边
		}
	}
	dijkstra_hp(1);
	printf("%.10f\n",d[n+2]);
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

### 一道看似困难的简单 dijkstra 
#### 分析：   
小偷从一个遮挡物到另一个遮挡物的过程是我们需要思考的(其实楼上的dalao已经说的很清楚了)     
以小偷的站位为起点，如何最近的到达一个遮挡物？  
最近的无疑是当前点与**遮挡物圆心相连的直线**所在(这个很好理解吧？)     
但小偷只要碰到了边线就安全了，所以要**减去两圆的半径**    

于是这道题就很好做了>>>说几个细节      
1. 小偷的起点和终点需要建一个半径为 0 的园(就是个点)    
2. 算出来两点的距离减去半径后要与 0.0 取 max   
3. 记得把对应的数据类型改成 double  
4. 输出控制符："%.10lf"      
完了吗？完了 $n^{2}$ 的边完全可以存下    
#### AC code
```cpp
#include<bits/stdc++.h>
using namespace std; bool vis[3005]; double dis[3005];
struct node{ int to,next; double val; } a[2500005];
int cnt=0,st,sx,head[3005],tx,ty,n,x[1005],y[1005],r[1005]; 
inline void append(int x,int y,double z){
	a[++cnt].to=y;
	a[cnt].next=head[x];
	head[x]=cnt;
	a[cnt].val=z;
}
inline void D(int s){
	for(int i=1;i<=n+2;i++)
		dis[i]=1145141919810.0;
    dis[s]=0.0;
    priority_queue<pair<double,int>,vector<pair<double,int> >,greater<pair<double,int> > > points;
    points.push(make_pair(0,s));
    while (!points.empty()){
    	int u=points.top().second;
    	points.pop();
    	while (!vis[u]){
    		vis[u]=1;
    		for (int i=head[u];i;i=a[i].next)
    			if (!vis[a[i].to]&&dis[a[i].to]>dis[u]+a[i].val){
    				dis[a[i].to]=dis[u]+a[i].val;
    				points.push(make_pair(dis[a[i].to],a[i].to));
				}
		}
	}
}
inline double get(int a,int b,int x,int y){ return sqrt((long long)(a-x)*(a-x)+(long long)(b-y)*(b-y)); }
signed main(){
	scanf("%d%d%d%d%d",&sx,&st,&tx,&ty,&n);
	for (register int i=1;i<=n;i++)
		scanf("%d%d%d",&x[i],&y[i],&r[i]);
	x[n+1]=sx,y[n+1]=st,r[n+1]=0;
	x[n+2]=tx,y[n+2]=ty,r[n+2]=0;
	for (register int i=1;i<=n+2;i++)
		for (register int j=i+1;j<=n+2;j++){
			append(i,j,max(0.0,get(x[i],y[i],x[j],y[j])-r[i]-r[j]));
			append(j,i,max(0.0,get(x[i],y[i],x[j],y[j])-r[i]-r[j]));
		} D(n+1);
	printf("%.10lf",dis[n+2]);
	return 0;
}
```

---

## 作者：zhangjiahe__ (赞：0)

# 题意：

一个人要从 S 点走到 T 点，有一些圆形区域为安全区，剩余区域为辐射区，他想走尽可能少的辐射区，求最短要经过多长的辐射区。

# 思路：

肯定是最短路。圆之间距离如何求？设圆心距离为 $dis$，两个圆的距离就是 $dis - r_1 - r_2$。为什么不是其他的线？作一条垂直于圆心连线的圆的切线即可证明。

连边跑一遍最短路即可。

# 代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
struct node
{
    double x, y, r;
    
} p[300005];
double dist[300005];
int n;
vector <pair<double, double> > z[300005];
double dis(node a, node b)
{
    return max(0.0, sqrt(1.0*(a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)) - a.r - b.r);
}
void dijkstra(int s)
{
	dist[s]=0;
	priority_queue<pair<double,int> > h;
	h.push({0,s}); 
	while(!h.empty())
	{
		int p=h.top().second;
		h.pop();
		if(dist[p] == DBL_MAX) continue;
		for (auto j:z[p])
		{
			int q=j.first;
			double d=j.second;
			if (dist[q] > dist[p] + d)
			{
				dist[q] = dist[p] + d; 
				h.push(make_pair(-dist[q],q));
			}
		}
	}
}

int main()
{
    cin >> p[1].x >> p[1].y >> p[2].x >> p[2].y;
    p[1].r = p[2].r = 0;
	cin >> n;
	n+=2;
	for (int i = 3; i <= n; i++)
	{
		cin >> p[i].x >> p[i].y >> p[i].r;
	}
	for(int i = 1; i <= n; i++)
	{
	    dist[i] = DBL_MAX;
	    for(int j = i+1; j <= n; j++)
	    {
	        z[i].push_back({j,dis(p[i],p[j])});
	        z[j].push_back({i,dis(p[i],p[j])});
	    }
	}
	dijkstra(1);
    printf("%.10lf",dist[2]);
}
```

---

## 作者：AstaVenti_ (赞：0)

# $\mathbf{0x00}$ 启

蒟蒻的第 $\color{red}\mathbf{42}$ 篇题解。

# $\mathbf{0x01}$ 承

在平面直角坐标系中，求两点之间不在圆内的最短距离。

# $\mathbf{0x02}$ 转

可以发现是最短路，但是要怎么建边呢？建多长的边呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/l5koeg5b.png)

考虑这样一种情况：如果小偷想从 $S(x_s,y_s)$ 出发走到 $T(x_t,y_t)$，中间有一个半径为 $r$ 的圆，他应该怎么走？

根据定理“相切两圆的内公切线与两圆的连心线互相垂直”和“垂线段最短”可以得到，最短路径长度就是 $SO+OT$，其中被宇宙射线照射的距离是 $SO+OT-2r$。两个圆也是同样的道理，只不过在这其中被宇宙射线照射的距离是 $SO_1+O_1O_2-r_1-r_1$。

这样我们就可以建边了。但是还要特判一下：设 $A,B$ 两点间的距离为 $D(A,B)=\sqrt{(A_x-B_x)^2+(A_y-B_y)^2}$，如果两个圆相交，得到的距离可不是 $D(O_1,O_2)-r_1-r_2$，$D(O_1,O_2)-r_1-r_2<0$，所以建边时边的长度就应该为 $\max(0,D(O_1,O_2)-r_1-r_2)$。注意到点的数量最大只有 $1\times10^3$，因此不用担心 MLE 的问题。

其余需要注意的细节详见代码注释。

# $\mathbf{0x03}$ 合

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef double db;
int n;
db d[1003],xx1,xx2,yy1,yy2;
const db inf=1.79769313486231570e308;
//这里的 inf 一定要设为极大值，要不然可能会出问题
struct Node{
	db x,y,r;
  //存储小偷起点、终点（半径都为 0）和每个圆
}p[1003];
vector<pair<int,db> >Edge[1003];
//数据范围小，可以用邻接表存图
priority_queue<pair<db,int> >pq;
db gtds(Node a,Node b){
	return max(double(0),sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y))-a.r-b.r);
	//这里括号位置细节，千万别写错了，-a.r-b.r 不在 sqrt() 里面
}
void addedge(Node a,Node b,int a1,int b1){//加边
	Edge[a1].push_back(make_pair(b1,gtds(a,b)));
	Edge[b1].push_back(make_pair(a1,gtds(a,b)));
//	cout<<a1<<" "<<b1<<" "<<gtds(a,b)<<endl;
}
void D(){
	d[1]=0;
	pq.push(make_pair(0,1));
	while(!pq.empty()){
//		db w=pq.top().first;
		int u=pq.top().second;
		pq.pop();
		if(d[u]!=inf){
			for(auto i:Edge[u]){
				if(d[i.first]>d[u]+i.second){
          //i.first 是点，i.second 是边权
					d[i.first]=d[u]+i.second;
					pq.push(make_pair(-d[i.first],i.first));
				}	
			}
		}
	}
}
int main(){
//	cin>>xx1>>yy1>>xx2>>yy2>>n;
	cin>>p[1].x>>p[1].y>>p[2].x>>p[2].y>>n;
	p[1].r=0,p[2].r=0;
  //小偷其实就是半径为 0 的圆
	for(int i=3;i<=n+2;i++){
		cin>>p[i].x>>p[i].y>>p[i].r;
	}//这样点的数量就会多 2
	for(int i=1;i<=n+2;i++){
		d[i]=inf;
	}//初始化
	for(int i=1;i<=n+2;i++){
		for(int j=i+1;j<=n+2;j++){
			addedge(p[i],p[j],i,j);
		}
	}
	D();//板子
	cout<<fixed<<setprecision(10)<<d[2];
  //保留 10 位输出，2 号点就是终点
}

}
```

---

## 作者：Melo_DDD (赞：0)

第一篇蓝题题解，求过。

本题建议别用链式前向星，容易炸，因为数组大小是 $n^2$ 的，所以改用 vector 存图。

# 题目大意

略，还是挺清晰的。

# 题目证明

先放图：

![](https://cdn.luogu.com.cn/upload/image_hosting/b1u6l2v1.png?x-oss-process=image/resize,m_lfit,h_1700,w_2025)

既然出发点给定，那我们就不用管它了。

先考虑从圆外一点到此圆最少的圆外距离，因为垂线段最短，所以此路径一定垂直于圆的一切线，即连接点和圆心的线。

接下来我们就可以拓展到本题了，考虑小偷走到一点的最短圆外路径，显然只用考虑经过两个圆的情况（因为一个圆的就是上面那种）。蓝线连接两圆圆心和终点，绿线不经过另一圆圆心到终点，可以证明蓝线的圆外距离一定是优于绿线的。因为连接了两圆圆心，所以蓝线一定垂直于两圆的切线，即两条垂线段，而绿线不连接圆心，所以一定不垂直，那么它一定长于垂线段，是严格劣于蓝线的。

好了，那么本题做法就出来了，我们只需记录下圆心点坐标跑最短路即可。

# 题目实现

不可能有负环，考虑使用优先队列优化的迪杰特斯拉，和板子区别不大。

需要注意的有两点：

1. 两点间圆外距离，先用公式求出两点间距再减两圆半径，由于两圆可能相交，即圆外距离小于 $0$，所以要对 $0$ 取最大值。

1. 在**每两个圆**之间建**无向边**保证做法正确性。

## 代码

```cpp
#include <bits/stdc++.h>
#define db double
#define rep(i ,m ,n ,x) for (int i = (m) ;i <= (n) ;i += (x))
#define IOS ios :: sync_with_stdio(0) ;cin.tie (0) ;cout.tie (0)
using namespace std ;
const int N = 1007 ; 
int n ;
db dis[N] ;//需要开根切忌开 int
struct circle {
	db x ,y ,r ;
}p[N] ;//记录障碍物
struct edge {
	int to ;
	db val ;
};
vector <edge> e[N] ; //vector 存图
namespace kafka {//卡妈\se\se
	inline db dist (circle a ,circle b) {
		return max (0.0 ,sqrt ((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)) - a.r - b.r) ;//求圆外距离
	}
	inline void dijkstra (int x) {
		priority_queue <pair <db ,int> ,vector <pair <db ,int> > ,greater <pair <db ,int> > > q ;//优先队列
		dis[x] = 0.0 ;//起点
		q.push (make_pair (dis[x] ,x)) ;
		while (! q.empty ()) {
			int now = q.top () .second ;
			q.pop () ;
			if (dis[now] == DBL_MAX) continue ;
			for (auto nex : e[now]) {
				if (dis[nex.to] > dis[now] + nex.val) {
					dis[nex.to] = dis[now] + nex.val ;
					q.push (make_pair (dis[nex.to] ,nex.to)) ;
				}
			}
		}
	}
}
int main () {
	IOS ;
	cin >> p[1].x >> p[1].y >> p[2].x >> p[2].y ;
	p[1].r = p[2].r = 0.0 ;//起点是一个点，看做无半径的圆
	cin >> n ;
	n += 2 ;
	rep (i ,3 ,n ,1) {//前两个点分别是起点、终点，所以 n 个点从编号 3 开始存
		cin >> p[i].x >> p[i].y >> p[i].r ;
	}
	rep (i ,1 ,n ,1) {
		dis[i] = DBL_MAX ;//设为极大值，貌似只有这个能过，本人亲测
		rep (j ,i + 1 ,n ,1) {
			db far = kafka :: dist (p[i] ,p[j]) ;
			e[i].push_back ({j ,far}) ;
			e[j].push_back ({i ,far}) ;//建无向边
		}
	}
	kafka :: dijkstra (1) ;
	printf ("%.10lf\n" ,dis[2]) ;//输出终点最短路
	return 0 ;
}
```

### 看我粉福

##### 你是否承认卡芙卡的美貌举世无双？

---

## 作者：james1BadCreeper (赞：0)

考虑圆外的一点如何走到圆内的距离是最短的：很简单，将它和圆心连线即可。也就是说，我们将所有圆都看作圆心一个点，求出的距离必定是最短距离。

枚举任意两个圆和起点终点，计算出它们之间的暴露在宇宙射线中的距离，然后在这张完全图上直接暴力 Dijkstra 求出最短路即可，时间复杂度 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std; 

int n; 
double xs, ys, xt, yt, x[1005], y[1005], r[1005]; 
double d[1005][1005], f[1005]; 
bool v[1005]; 

inline double calc(double x1, double y1, double x2, double y2) {
    return hypot(x1 - x2, y1 - y2); 
}

int main(void) {
    ios::sync_with_stdio(0); 
    cin >> xs >> ys >> xt >> yt; 
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> x[i] >> y[i] >> r[i]; 
    x[0] = xs, y[0] = ys; x[n + 1] = xt; y[n + 1] = yt; 
    for (int i = 0; i <= n + 1; ++i) for (int j = i + 1; j <= n + 1; ++j)
        d[i][j] = d[j][i] = max(0.0, calc(x[i], y[i], x[j], y[j]) - r[i] - r[j]); 
    for (int i = 1; i <= n + 1; ++i) f[i] = 1e18; 
    for (int op = 1; op <= n + 1; ++op) {
        int x = -1; 
        for (int i = 0; i <= n + 1; ++i)
            if (!v[i] && (x == -1 || f[i] < f[x])) x = i; 
        v[x] = 1; 
        // cout << x << "\n"; 
        for (int i = 0; i <= n + 1; ++i)
            f[i] = min(f[i], f[x] + d[x][i]); 
    }
    // printf("%.10lf %.10lf\n", d[0][1], d[1][2]); 
    printf("%.10lf\n", f[n + 1]); 
    return 0; 
}
```

---

## 作者：DegChuZm (赞：0)

[atcoder传送门](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/2154)

经过我半个下午的不懈努力，终于 ac 了这道最短路蓝题。

下面来分析一下这道蓝题吧。

### 建边
这道题最难搞的地方就是在就是在建边上。

其实想了一下也不难得出：

一条边的边权就是两个点的**欧几里德距离**减去两个圆的半径。

起点和终点可以看成两个**半径为 0** 的圆。

点按录入的数据排就行了。

求欧几里德距离公式: $\sqrt{{(x_2-x_1)^2}+{(y_2-y_1)^2}}$。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long head[10000001],cnt,n,o,v,w,m,xx,yy,xxx,yyy,x[10000001],y[10000001],z[10000001];//数据1e9，开longlong。
double dis[10000001];//题目有点迷，1000^2是1000000没错啊，但我开10000000才能过就离谱
struct node{
	long long nex,to;
	double val;
}a[10000001];
struct dcz{
	long long u;
	double d;
	bool operator<(const dcz& jntm)const {
		return d>jntm.d;
	}
};
void add(long long x,long long y,double z){
	a[++cnt].val=z;
	a[cnt].to=y;
	a[cnt].nex=head[x];
	head[x]=cnt;
}
void dij(long long o){
	for(int i=1;i<=m+2;i++){
		dis[i]=LONG_LONG_MAX;
	}
	dis[o]=0;
	priority_queue<dcz> q;
	q.push((dcz){o,(double)0});
	while(!q.empty()){
		dcz xx=q.top();
		q.pop();
		long long u=xx.u;
		double d=xx.d;
		if(d!=dis[u])
			continue;
		for(int i=head[u];i;i=a[i].nex){
			long long v=a[i].to;
			double w=a[i].val;
			if(dis[u]+w<dis[v]){
				dis[v]=dis[u]+w;
				q.push((dcz){v,dis[v]});
			}
		}
	}
}
int main(){
	cin>>xx>>yy>>xxx>>yyy;
	cin>>m;
	x[1]=xx,y[1]=yy,z[1]=0;
	x[m+2]=xxx,y[m+2]=yyy,z[m+2]=0;
	for(int i=2;i<m+2;i++){
		cin>>x[i]>>y[i]>>z[i];
	}
	for(int i=1;i<=m+2;i++){
		for(int j=1;j<=m+2;j++){
			if(i==j)
				continue;
			xx=x[j]-x[i];
			yy=y[j]-y[i];
			double xxx=sqrt(xx*xx+yy*yy);
//			cout<<xxx<<" "<<xx<<" "<<yy<<endl;
			double ddcz=xxx-(z[i]+z[j]);
			add(i,j,max((double)0,ddcz)*1.0);
		}
	}
	dij(1);
	printf("%.10lf",dis[m+2]);
	return 0;
}
```

---

## 作者：cinis (赞：0)

不必多说，这题的核心思路是万物皆可图论。为了保险不被卡SPFA，我使用了dij来求最短路

那么如何将这些屏障化为一张图？显而易见，你在屏障里面走多少距离，绕多少弯路都不影响答案，而在屏障外在两屏障之间最短路径便是直线运动，那么便可将屏障圆心看做点，再用勾股定理求出两圆心之间的距离后减去两圆的半径，其中的最短距离便是边权。

接下来就是代码：

```cpp
#include<bits/stdc++.h>
#define LL long long
#define U unsigned
#define LD long double
bool isp(LL x){
	if(x<2)return 0;
	for(LL i=2;i<=sqrt(x);i++){
		if(x%i==0) return 0;
	}
	return 1;
}
using namespace std; 
LL M,Sx,Sy,S=1,Tx,Ty,T,m,h[6000000],n[6000000],dt[6000000],en;
double w[6000000],dis[6000000],mapp[200000][3];
struct node{
	LL id;
	double dis;
	bool operator < (const node &B) const{return dis>B.dis;}
};
void dij(){
	priority_queue<node>q;
	bool vis[6000000]={};
	memset(dis,0x7f7f7f7f,sizeof dis);
	dis[S]=0;
	q.push((node){S,0});
	while(q.size()){
		LL x=q.top().id;
		q.pop();
		if(vis[x])continue;
		vis[x]=1;
		for(LL j=h[x];j;j=n[j]){
	//cout<<n[j]<<"\n";
			LL y=dt[j];
			double ww=w[j];
			if(dis[y]<=dis[x]+ww)continue;
			dis[y]=dis[x]+ww;
			q.push((node){y,dis[y]});
		}
	}
    return ;
}
void add(LL x,LL y,double z){
	dt[++en]=y,n[en]=h[x],w[en]=z,h[x]=en;
	return ;
}
int main(){
	scanf("%lld %lld %lld %lld %lld",&Sx,&Sy,&Tx,&Ty,&M);
	mapp[1][1]=Sx;
	mapp[1][2]=Sy;//将起点当做0半径的屏障
	mapp[1][0]=0;
	mapp[2][1]=Tx;
	mapp[2][2]=Ty;//将终点当做0半径的屏障
	mapp[2][0]=0;
	for(LL i=1;i<=M;i++){
		double u,v,w;
		scanf("%lf %lf %lf",&u,&v,&w);
		mapp[i+2][1]=u;
		mapp[i+2][2]=v;
		mapp[i+2][0]=w;
	}
	for(LL i=1;i<=M+2;i++){
		for(LL j=1;j<=M+2;j++){
			if(i==j)continue;
			//printf("%lld            %lld\n",i,j);  调试
			double rx,ry;
			rx=mapp[j][1]-mapp[i][1];
			ry=mapp[j][2]-mapp[i][2];
			double rxy=sqrt(rx*rx+ry*ry);//勾股定理求之间距离
			//cout<<rx*rx<<"   "<<ry*ry<<endl;
			double tr=rxy-(mapp[i][0])-(mapp[j][0]);//圆心距离减去两半径
			tr=max(tr,(double)(0)); 
			add(i,j,tr);//这里每个点建两遍故建有向边
			//add(j,i,tr);
		}
	}
	dij();//dij一下
	printf("%.10lf",dis[2]);
	return 0;
}
```


---

## 作者：亚索s (赞：0)

对于这道水题，我也不知道为什么没有题解（可能是因为我太蒟了吧），我就来发一篇吧。

福利题意：给出两点，找出从一点到另一点的经过的非圆内区域的最小值。

### 解题思路：将所有圆变成点，点与点之间的距离等于他们圆心之间的距离减去他们的半径和，然后再用SPFA求最短路。
接下来是你们最喜欢看的东西吧，我也就不再啰嗦了。
```
#include <bits/stdc++.h>
using namespace std;
 
const int maxn = 1e3 + 20;
int vis[maxn],n;
double x[maxn],y[maxn],r[maxn],dist[maxn],mp[maxn][maxn];
 
void SPFA(int s)
{
    queue<int>q;
    for(int i = 1;i <= n;i++) dist[i] = 1e10;
    memset(vis,0,sizeof(vis));
    while(!q.empty()) q.pop();
    dist[s] = 0;
    vis[s] = 1;
    q.push(s);
 
    while(!q.empty())
    {
        int v = q.front();
        q.pop();
        vis[v] = 0;
        for(int i = 1;i <= n;i++)
        {
            if(dist[i] > dist[v] + mp[v][i])
            {
                dist[i] = dist[v] + mp[v][i];
                if(!vis[i])
                {
                    vis[i] = 1;
                    q.push(i);
                }
            }
        }
    }
}
 
int main()
{
    while(scanf("%lf%lf%lf%lf",&x[1],&y[1],&x[2],&y[2]) != EOF)
    {
        scanf("%d",&n);
        n += 2;
        r[1] = r[2] = 0;
        mp[1][2] = mp[2][1] = sqrt((x[1] - x[2]) * (x[1] - x[2]) + (y[1] - y[2]) * (y[1] - y[2]));
        for(int i = 3;i <= n;i++)
        {
            scanf("%lf%lf%lf",&x[i],&y[i],&r[i]);
        }
        for(int i = 1;i <= n;i++)
        {
            for(int j = 1;j <= n;j++)
            {
                mp[i][j] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
                mp[i][j] -= r[i] + r[j];
                if(mp[i][j] < 0)
                {
                    mp[i][j] = 0;
                }
            }
        }
        SPFA(1);
        printf("%.10f\n",dist[2]);
    }
    return 0;
}

```

---

