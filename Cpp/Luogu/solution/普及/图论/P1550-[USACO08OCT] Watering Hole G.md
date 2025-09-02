# [USACO08OCT] Watering Hole G

## 题目描述

Farmer John 的农场缺水了。

他决定将水引入到他的 $n$ 个农场。他准备通过挖若干井，并在各块田中修筑水道来连通各块田地以供水。在第 $i$ 号田中挖一口井需要花费 $W_i$ 元。连接 $i$ 号田与 $j$ 号田需要 $P_{i,j}$（$P_{j,i}=P_{i,j}$）元。

请求出 FJ 需要为使所有农场都与有水的农场相连或拥有水井所需要的最少钱数。

## 说明/提示

对于 $100\%$ 的数据，$1 \leq n \leq 300$，$1 \leq W_i \leq 10^5$，$0 \leq P_{i,j} \leq 10^5$。

## 样例 #1

### 输入

```
4
5
4
4
3
0 2 2 2
2 0 3 3
2 3 0 4
2 3 4 0```

### 输出

```
9```

# 题解

## 作者：Mr_QwQ (赞：139)

本题看似很难，实际上思路非常简单——如果你想通了。

首先有一个问题：图中有几个点？大部分的人会回答n个点。错了，有n+1个。

多出来的那个点在哪？关键在于你要理解每一个决策的意义。实际上，多出来的那个点是地下的~~FarmerJohn山泉~~天然矿泉水。当我们打井时，我们实际上是在往地下连边。理解了这一点，代码就没有任何难度了。

构图时，我们只需多加一个点，对于每个点i，我们连边i→n+1，边权为w\_i。然后直接跑最小生成树就没了。就没了。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
struct edge{
    int from,to,len;
    const bool operator < (edge b) const{
        return this->len>b.len;
    }
}e[100000];
priority_queue <edge> que;
int n,a[302][302],w[301],fa[302],ans;
int find(int x)
{
    if(fa[x]==x)return x;
    return fa[x]=find(fa[x]);
}
int mst()
{
    while(!que.empty()){
        edge p=que.top();
        if(find(p.from)!=find(p.to))
        {
            fa[fa[p.to]]=fa[p.from];
            ans+=p.len;
        }
        que.pop();
    }
    return ans;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&w[i]);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            scanf("%d",&a[i][j]);
            if(i!=j)que.push((edge){i,j,a[i][j]});
        }
    }
    n++;
    for(int i=1;i<n;i++){
        que.push((edge){i,n,w[i]});
        que.push((edge){n,i,w[i]});
    }
    for(int i=1;i<=n;i++)fa[i]=i;
    printf("%d",mst());
    return 0;
}
```
最后提醒一下用C++STL用惯了的同学：注意C++优先队列是从大到小排的，所以如果你想排序，一定记住把小于号定义里的运算反过来！一定！我刚才被这个坑了半天！


---

## 作者：汪鸣谦 (赞：80)

写在前面的话：再看题解之前，请你确保你已经进行了足够的思考，如果你没有，那么还是请你在好好分析分析题目。如果你会最小生成树的话，那么这一道题应该得五十分还是比较容易的

好了，我们直入主题。

先看一下题，让所有的村子全部有水，这就是最小生成树的模板题啊！！！于是，我们有了以下的想法：对于整张图，跑一边最小生成树，再决定应该在哪个点打井，最后相加得到ans，输出。

于是，得到了五十分

这是我们要想一个问题，题目里并没有说只能打一口井。如果打井的花费要小于修路的花费，那么打井就可以了。请看一组hack数据

```cpp
3
1 1 1
0 10 10
10 0 10
10 10 0

```


在这个数据里，如果按照上面的想法，应该的答案是20（最小生成树）+1（打一口井），但是，在1，2，3每一个点都打一口井，花费为3，显然是要小于刚才那个值的。这怎么办呢？难道要爆搜所有可能的打井情况？

其实这个想法比较麻烦，而且显然不好实现。在OI竞赛里，如果你觉得一种想法有些难以实现或不切实际，千万不要一条路走到黑，一定要换一个角度想一想

比如这道题，让我们回到问题的本质：让每个村庄都有水。（前方高能）

我们可以假设，所有的经都和一处水源联通。那么，我们可以把所有的村庄都和这个水源连接起来，这样，我们只要把这个水源点也看成一个村庄，让他和所有的点都或直接或间接地联通，并且让每个点之间连通，问题就解决了

这样，这个问题就转化成了一个n+1个点的最小生成树，并且每个点和水源点连接的费用就是打井的费用。

于是，样例的情况就是1号点和水源点联通，其他点与一号店联通，而我的数据就是每个点都与水源点联通。

其实就是要让水源点和每个点联通，这样水就会走进每个村子

于是，我们在建点和点的边的基础上，在建和水源点的边，然后跑一边最小生成树就可以了。（prim和kruskal都可以，但我更喜欢kruskal）

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,w[1001]={0},f[1001]={0},p[1001][1001]={0},te=0,ans=0;
struct es{
	int from,to,value;
}a[100001];
void adde(int x,int y,int z){
	++te;
	a[te].to=y;
	a[te].from=x;
	a[te].value=z;
}
bool cmp(es a,es b){return a.value<b.value;}
int find(int x){
	if(x==f[x])return x;
	else return f[x]=find(f[x]);
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>w[i],f[i]=i;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>p[i][j];
			if(i!=j)
			adde(i,j,p[i][j]);
		}
	}
	for(int i=1;i<=n;i++){
		adde(i,n+1,w[i]);
		adde(n+1,i,w[i]);
	}
	sort(a+1,a+te+1,cmp);
	for(int i=1;i<=te;i++){
		int x=find(a[i].to);
		int y=find(a[i].from);
		if(x==y)continue;
		else f[x]=y,ans+=a[i].value;
	}
	cout<<ans<<endl;
	return 0;
}
```

写在后面：这一道题我一开始也没有想到100分做法，只想到了50分，看了题解。所以如果你看了题解，那么请你一定理解透彻以后，再写一遍代码或者像我一样写一篇题解毕竟如果一味的看题解是无法取得能力上的提升的

~~您都看到这了，赞一个好吗QAQ~~

---

## 作者：雪颜 (赞：18)

这题其实就是最小生成树 基本只要想到一点就直接打模板

关键点是什么呢？ 其实很简单，就是：连接 i ,j 很好想 但是打井 我们可以看做与 0 连接

那么就非常好写了

```cpp
#include<cmath>
#include<queue>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int ML=305;
int f[ML];
struct Node{
    int l,r;
    int num;
}a[ML*ML/2];
bool comp(Node a,Node b){
    return a.num<b.num;
}
int found(int x){
    if(f[x]==-1) return x;
    return f[x]=found(f[x]);
}
void merged(int x,int y){
    f[x]=y;
    return;
}
int n;
int ans;
int main(){
    scanf("%d",&n);
    int i,j;
    int t=0;
    for(i=1;i<=n;i++){
        int x;
        scanf("%d",&x);
        a[++t].num=x;
        a[t].l=0;
        a[t].r=i;
    }
    memset(f,-1,sizeof(f));
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            int x;
            scanf("%d",&x);
            if(i>j){
                a[++t].num=x;
                a[t].l=i;
                a[t].r=j;
            }
        }
    }
    sort(a+1,a+1+t,comp);
    int x=0;
    for(i=1;i<=t;i++){
        int t1,t2;
        t1=found(a[i].l);
        t2=found(a[i].r);
        if(t1!=t2){
            merged(t1,t2);
            ++x;
            ans+=a[i].num;
        }
        if(x==n) break;
    }
    printf("%d",ans);
    return 0;
}

```

---

## 作者：ff_666 (赞：13)

每个点都被连到，显然是最小生成树。

刚开始，肯定要找个最小的井作“源点”

接下来，就是看对于未连的点i,拿来连还是自己挖——把PRIM的dst数组给为各点的代价，再正常刷不就好了吗

简短代码。。



```cpp
    #include<cstdio>
    using namespace std;
    int n,dst[305],ans,cst[305][305];bool vis[305];
    inline int read(){
        int ret=0;char ch=getchar();
        while(ch<'0'||ch>'9') ch=getchar();
        while(ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
        return ret;
    }
    int main(){
        n=read();
        for(int i=1;i<=n;i++) dst[i]=read();
        for(int i=1;i<=n;i++)
          for(int j=1;j<=n;j++) cst[i][j]=read();
        int k,min_x;
        for(int i=1;i<=n;i++){
            min_x=1<<30;
            for(int j=1;j<=n;j++)if(!vis[j]&&dst[j]<min_x) min_x=dst[j],k=j;
            ans+=min_x,vis[k]=1;
            for(int j=1;j<=n;j++)if(!vis[j]&&cst[k][j]<dst[j]) dst[j]=cst[k][j];
        }
        printf("%d\n",ans);
        return 0;
}
```

---

## 作者：Leaved_ (赞：13)

机房模拟考试题，考场上没做出来

大众思路：把打井看做与水源连接

最小生成树板子

~~话说稠密图Prim应该比Kruskal好一点~~

我用的链式前向星优化

进入正题：
```
#include <bits/stdc++.h>

using namespace std;

long long n,m,tot;
long long h[305*305*305],dis[305*305*305];
bool u[305*305*305];

struct Node {
	int to,next,w;
}e[305*305*305];

void add(int x,int y,int z) {
	++tot;
	e[tot].next=h[x];
	e[tot].to=y;
	e[tot].w=z;
	h[x]=tot;
}

void input() {
	cin>>n;
	n+=1;
	for(int i=2;i<=n;i++) {
		cin>>m;add(1,i,m);add(i,1,m);
		dis[i]=0x7777777f;
	}
	for(int i=2;i<=n;i++) {
		for(int j=2;j<=n;j++) {
			cin>>m;
			add(i,j,m);add(j,i,m);
		}
	}
}

int prim(int now) {
	long long ans=0;
	dis[now]=0;
	for(int k=1;k<=n;k++) {
		int minn=0x7777777f;
		for(int i=1;i<=n;i++) {
			if(!u[i]&&minn>dis[i]) {
				minn=dis[i];
				now=i;
			}
		}
		ans+=minn;
		u[now]=1;
		for(int i=h[now];i;i=e[i].next) {
			if(!u[e[i].to]&&dis[e[i].to]>e[i].w) {
				dis[e[i].to]=e[i].w;
			}
		}
	}
	return ans;
}

int main() {
	input();
	cout<<prim(1)<<endl;
}
```

---

## 作者：Pheasant_YQ (赞：12)


这道是我们奥赛班 模拟赛的 t2
当时想的贪心 
~~可是莫得实现~~

其实这道题 ~~用不到什么贪心~~ 就是一个最小生成树的板子。
再以后
需要考虑一个隐藏的点 就是那个打水的井
```
for (int i = 1; i <= n; ++ i){
		e [++ t].x = i;
	    e [t].y = n + 1;
	    e [t].z = w [i];
	}
```


AC代码如下

```
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 111111;
int n,m,ans,t=0,w [MAXN];
int fa [MAXN];

struct node{
	int x,y,z;
	bool operator < (const node &e1) const {
		return z < e1.z;
	} 
}e [MAXN];

int father (int x){
	if (fa [x] == x) return x;
	return fa [x] = father (fa [x]); 
}

int read(){
    int x = 0,f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
        f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
} 

int cmpt (int x,int y){
	return x<y;
}

int main(){
	n = read ();
	for (int i = 1; i <= n; i ++) w [i] = read ();
	for(int i = 1; i <= n; i ++)
	for(int j =1; j <= n; j ++){
		int p;
		p = read ();
		if (i!=j){
		   e [++ t].x = i;
		   e [t].y = j; 
		   e [t].z = p;
	    }
	}
	for (int i = 1; i <= n; ++ i){
		e [++ t].x = i;
	    e [t].y = n + 1;
	    e [t].z = w [i];
	}
	sort (e + 1, e + 1 + t);
	for (int i = 1; i <= n; i ++) fa [i] = i;
	for (int i = 1; i <= t; i ++){
		int x = e [i].x,y = e [i].y;
		int fax = father (x),fay = father (y) ;
		if (fax == fay) continue ; 
		fa [fax] = fay;
		ans += e [i].z; 
	}
	printf ("%d\n",ans);
	return 0;
}
```


---

## 作者：1jia1 (赞：7)

题解里大多都是建立一个源点再跑最小生成树，这里提供一个贪心。

将单点打井混在边里一起按价值从小到大排序，按照Kruskal的思路一个个把点/边取出。额外记录一个数组well[i]表示以i为头的集合是否打了井（即i所在连通块是否接上水源）。

当取出了一条边，先常规并查集判断两个端点所在的连通块是否是同一个。如果不在同一连通块，则再判断两个端点所在连通块是否都接上水源。如果都有，那么就不需要把它们连起来了，否则就相连。

当取出了一个点，就判断它所在连通块是否接上水源。如果没有，就在它这个地方打一口井，然后标记它的连通块接上了水源。

贪心的正确性也很显然。容易得知，一个连通块要接上水源，要么就从另一个连通块引水，要么就在连通块中某点打井。

价格从小到大排序。如果取出一条边且两端点不在同一连通块、所在连通块没有都接水时，由于其中一个连通块在以后某个时刻一定会（或者当前就已经）接上水源，那么将两个连通块相连，就能保证以最小花费为另一个接上水源的时刻更靠后的连通块引水。

这是因为，它现在没有接上水源，则只能依靠引别的连通块的水或者在自己身上打井。但是现在这些并没有发生，说明要完成这个任务必须依靠比当前取出的边花费更高的点/边，那么打通这条边就一定是使这个连通块接上水源最便宜的方法。

如果取出一个点且它所在连通块没有接上水源，那么和上述理由类似，在这个点打井一定是时它所在连通块接上水源最便宜的方法。

因此，不断按照上述方法贪心，便能得到最优解。

```cpp
#include <cstdio>
#include <algorithm>
#define N 301
using namespace std;
int n,num[N], cnt,f[N],well[N], ans=0;
struct edge{
	int to,from,val;
	inline const bool operator<(edge r)const
	{
		return val<r.val;
	}
}e[N*N<<1];
inline void adde(int u,int v,int w)
{
	e[++cnt].from=u;
	e[cnt].to=v;
	e[cnt].val=w;
	return;
}
inline int find(int x)
{
	if(f[x]==x)return x;
	else return f[x]=find(f[x]);
}
inline void merge(int x,int y,int cost)
{
	int fx=find(x),fy=find(y);
	if(fx!=fy&&(well[fx]&well[fy])!=1)//判断是否两个连通块都接上水源
	{
		if(well[fx])f[fy]=fx;//把没水源的集合接到有水源的集合上
		else f[fx]=fy;
		ans+=cost;
	}
	return;
}
inline void Kruskal()
{
	for(int i=1;i<=n;i++)f[i]=i,well[i]=0;
	for(int i=1,u,v;i<=cnt;i++)
	{
		u=e[i].from,v=e[i].to;
		if(u)//一条“边”的左端点为0表示这是个点
		{
			merge(u,v,e[i].val);
		}
		else
		{
			find(v);
			if(!well[f[v]])//如果这个点所在连通块没有井
			{
				well[f[v]]=1;//给这个连通块打井
				ans+=e[i].val;
			}
		}
	}
	return;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&num[i]),adde(0,i,num[i]);
	for(int i=1,u;i<=n;i++)for(int j=1;j<=n;j++)
	{
		scanf("%d",&u);
		if(i<j)adde(i,j,u);//强行邻接矩阵转邻接表
	}
	sort(e+1,e+cnt+1);//边点一起排序
	Kruskal();
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：_Grey (赞：5)

### [更好的阅读体验(安利我自己的博客)](https://lllinea.github.io/USACO-Watering-Hole/)

### ~~机房模拟赛10分的窝~~

### 当时想到了MST但是没有考虑太多

### ~~拿了十分~~

## 认真思考的话就发现了一个隐藏的条件就是打水的井

## 可以单独作为一个点连起来

```
for (int i = 1;i <= n;++i){
	cin >> w[i];
	add_edge(i,0,w[i]);
	add_edge(0,i,w[i]);
}
```
## MST的话我还是选择Kruskal叭(毕竟不会写Prim)

### %%%题解区写Prim的巨佬们

## 上代码
```
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <cstring>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxn = 310000;
struct node{
	int u,v,c,nxt;
}e[maxn];
int n,ans,a,w[maxn],head[maxn],cnt = 0;
int fa[maxn];
inline void add_edge(int u,int v,int c){
	e[++cnt].u = u;
	e[cnt].v = v;
	e[cnt].c = c;
	e[cnt].nxt = head[u];
	head[u] = cnt;
}
inline int find(int u){
	if (fa[u] == u)return u;
	else return fa[u] = find(fa[u]);
}
void Kruskal(){
	for (int i = 0;i <= cnt;++i){
		int fax = find (e[i].u),fay = find (e[i].v);
		if (fax == fay)continue;
		fa[fax] =fay;
		ans += e[i].c;
	}
}
bool cmp (node a,node b){
	return a.c < b.c;
}
int main(){
	cin >> n;
	for (int i = 1;i <= n;++i){
	cin >> w[i];
	add_edge(i,0,w[i]);
	add_edge(0,i,w[i]);
	}
	for (int i = 1;i <= n;++i)
		for (int j = 1;j <= n;++j){
			cin >> a;
			if (i > j)
				add_edge(i,j,a);
		}
	for (int i = 1;i <= n;++i)fa[i] = i;
	sort (e,e+cnt+1,cmp);
	Kruskal();
	cout << ans;
	return 0;
}
```


---

## 作者：派大那个星 (赞：5)

表示神犇们的代码都看不懂%%%

于是借用楼上楼下思路，~~瞎改模板~~精心调出了易懂版本

以下代码   ~~其实克鲁斯卡尔模板~~
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,e,a[110000],b[110000],w[110000],c[110000],ans,f[11000],num;
int getf(int x){if(f[x]!=x)f[x]=getf(f[x]);return f[x];}
void quick_sort(int left,int right)//手动模拟快排，写完发现可以重载（逃
{
    int i=left,j=right;
    int mid=c[(left+right)/2];
    while(i<=j)
    {
        while(c[i]<mid)
            i++;
        while(c[j]>mid)
            j--;
        if(i<=j)
        {
            int t;
			t=c[i];c[i]=c[j];c[j]=t;
			t=a[i];a[i]=a[j];a[j]=t;
			t=b[i];b[i]=b[j];b[j]=t;
            i++;
            j--;
        }
    }
    if(i<right)
        quick_sort(i,right);
    if(left<j)
        quick_sort(left,j);
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;++i) scanf("%d",&w[i]),f[i]=i;
	for(int i=1;i<=n*n;i++)
		scanf("%d",&c[i]),a[i]=(i-1)%n+1,b[i]=(i-1)/n+1;//因为完全图，就顺着矩阵读入，注意a，b数组与i的关系
	for(int i=1;i<=n;i++)
		c[i+n*n]=w[i],a[i+n*n]=i,b[i+n*n]=n+1;//添加一个点，c[n*n+1]到c[n*n+n]表示每个点到水井这个边权，a，b数组同上，表示第i条边的两端
	quick_sort(1,n*n+n);//边从大到小排序
	for(int i=1;i<=n*n+n;i++)
	{
		if(num==n)break;//num从0开始，加到n表示已是最小生成树
		if(getf(a[i])!=getf(b[i]))//并查集维护正确性
		{
			f[getf(a[i])]=getf(b[i]);
			num++;
			ans+=c[i];//累加边权
		}
	}
	printf("%d\n",ans);
}
```

---

## 作者：PrefixAMS (赞：4)

这道题其实就是将井的价钱加到边里

然后跑一遍最小生成树

~~然而我只会克鲁斯卡尔~~

粘代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int fa[1000101],w[1000100];
int ans,u,v,c,n,m,total;
inline int find(int a)
{
	if(fa[a]!=a) return fa[a]=find(fa[a]);
	else return a;
} 
struct io
{
	int u,v,c;
}e[1010010];
bool cmp(io a,io b)
{
	return a.c<b.c;
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		fa[i]=i;
	}
	for(int i=1;i<=n;i++)
	{
		cin>>w[i];
		total++;
		e[total].u=0;
		e[total].v=i;
		e[total].c=w[i];
		e[total].u=i;
		e[total].v=0;
		e[total].c=w[i];
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cin>>u;
			total++;
			e[total].u=i;
			e[total].v=j;
			e[total].c=u;
		}
		
	}
	sort(e,e+total+1,cmp);
	for(int i=0;i<=total;i++)
	{
		int r1=find(e[i].u),r2=find(e[i].v);
		if(r1!=r2)
		{
			fa[r1]=r2;
			ans+=e[i].c;
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：yjxyjx (赞：4)

emm……这道题，是一个 **最小生成树** 的题目

******

具体思路：

1. 首先，如果把这道题中的 **挖井** 的条件给去掉的话，那么这道题 **就是一道最小生成树裸题**

2. 然后，让我们考虑加了 **挖井** 的这种费用之后怎么做这道题:

*****

其实，只要将 **地** 视为一个节点来做就可以了，将地视为一个节点，将每一个牧场和井连接的费用作为边权

*****

我一开始有一种错误的思路，是这样的：

由于对地上的 **牧场** 求 **最小生成树** 会让所有的牧场连通，然后再找一口费用最小的井就好，

但是这样的话，有一种情况：

假设一口井，和其他井要连通的费用很大，但是打井的费用很小，那么在这个时候，可能就不会为这个牧场打井，导致最后的结果错误。

****

最后，AC代码：

```cpp
#include<iostream>

const int MaxN = 300 + 10;
const int INF = 0x3f3f3f3f;

int N, W[MaxN], well = INF, numEdge = 1, P[MaxN][MaxN];

struct Edge {
    int u, v, weight;
} edge[MaxN * MaxN + MaxN];

struct UnionFindSet {
    int father[MaxN];
    inline void Init(const int &__size) {
        for (int i = 1; i <= __size; ++i) father[i] = i;
    }
    inline int Find(int o) {
        return (father[o] == o) ? o : father[o] = Find(father[o]);
    }
} ufs;


inline bool cmp(const Edge &__a, const Edge &__b) {
    return __a.weight < __b.weight;
}

int Krushal() {
    int ans = 0, x = 0;
    std::sort(edge + 1, edge + numEdge + 1, cmp);
    ufs.Init(N);
    for (int i = 1; i <= numEdge; ++i) {
        int xx = ufs.Find(edge[i].u), yy = ufs.Find(edge[i].v);
        if (xx != yy) {
            ufs.father[xx] = yy;
            ++x;
            ans += edge[i].weight;
        }
        if (x == N) return ans;
    }
    return ans;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin >> N;
    for (int i = 1; i <= N; ++i) {
        std::cin >> W[i];
        edge[numEdge++].u = 0;
        edge[numEdge].v = i;
        edge[numEdge].weight = W[i];
    }
    
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            std::cin >> P[i][j];
            if (i > j) {
                numEdge++;
                edge[numEdge].u = i;
                edge[numEdge].v = j;
                edge[numEdge].weight = P[i][j];
            }
        }
    }
    int ans = Krushal();
    std::cout << ans;
    return 0;
}
```

---

## 作者：George1123 (赞：3)

[${\color{orange}\text{欢迎拜访我这个蒟蒻的博客}}$](https://www.luogu.org/blog/wzc-wwwwd/)

[P1550 【\[USACO08OCT\]打井Watering Hole】传送门](https://www.luogu.org/problem/P1550)

### 此题算法:最小生成树Prim

就是模板题

大致思路:

>1.$ $把农民John(FJ)看成一个点，他到一块田的边的权值就是那块田“挖井”要用的钱。

>2.$ $求出最小生成树权值和。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,vis[5010];
int w,p[5010][5010],ans;
struct edge{
    int to,v;
    void make(int dt,int dv){
        to=dt;
        v=dv;
    }
}now;
bool operator < (edge x,edge y){
    return x.v>y.v;
} priority_queue<edge> q;
void prim(int key){
    vis[key]=1;
    int i=n;
    while(i--){
        for(int j=0;j<=n;j++){
            if(!vis[j]&&p[key][j]<INT_MAX){
                now.make(j,p[key][j]);
                q.push(now);
            }
        } while(!q.empty()
        &&vis[q.top().to])
            q.pop();
        if(q.empty()) break;
        now=q.top();
        key=now.to;
        ans+=now.v;
        vis[key]=1;
        q.pop();
    }
} int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
    	scanf("%d",&p[0][i]);
    	p[i][0]=p[0][i];
	} for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&p[i][j]);
	prim(0);
	printf("%d\n",ans);
    return 0;
}
```
这题题解应该没人看吧，太简单了！

谢谢大家! !

---

## 作者：路人_ (赞：3)

    通过题目我们可以想到最小生成树算法（kruskal和Prim）
本蒟蒻习惯用并查集，所以用kruskal算法；
注意：本题与其他题不同之处在于：每个**点**都有他自己的权值；**解决方法**：我们可以把点的权值加到点本身；

转[并查集](https://baike.so.com/doc/6119935-6333082.html)；

**并查集的初始化**
```c
for(int i=1;i<=cnt;i++)
	{
		f[i]=i;
	}
```
**find操作**
```
int find(int x)
{
	if(x!=f[x])f[x]=find(f[x]);
	return f[x];
}
```
**合并操作**
```
void hb(int x,int y)
{
      f[find(x)]=find(y);
}
```
**核心算法kruska**

```
int Kruskal()
{
	sort(a+1,a+cnt+1,cmp);
	
	for(int i=1;i<=cnt;i++)
	{
		int x=find(a[i].x);
		int y=find(a[i].y);
		if(x!=y)
		{
			f[x]=y;
			++tot;
			ans+=a[i].w;
		}
		if(tot==n)
		break;
	}
	
	return ans;
}

```

**输入**
```
void init()
{
	cin>>n;
	
	for(int i=1;i<=n;i++)
	{
	    int w;
		cin>>w;
		a[++cnt].x=0;
		a[cnt].y=i;
		a[cnt].w=w;
	}
	
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			int w;
			cin>>w;
			if(i>j)
			{
				a[++cnt].x=i;
				a[cnt].y=j;
				a[cnt].w=w;
			}
		}
	}
	
	for(int i=1;i<=cnt;i++)
	{
		f[i]=i;
	}
	
}
```
~~废话不多说~~，上代码（逃）

**完整代码**
```
#include<bits/stdc++.h>//万能头文件 ； 
using namespace std;
int n,m,ans=0,cnt=0,tot=0,f[100010],w[100010];//定义变量和数组； 

struct node{ //结构体； 
	int x;
	int y;
	int w;
}a[500010];

bool cmp(node a,node b)//cmp函数（sort）； 
{
	return a.w<b.w;
}

int find(int x)//找祖宗 
{
	if(x!=f[x])f[x]=find(f[x]);
	return f[x];
}

void init()//输入函数 
{
	cin>>n;
	
	for(int i=1;i<=n;i++)
	{
	    int w;
		cin>>w;
		a[++cnt].x=0;
		a[cnt].y=i;
		a[cnt].w=w;
	}
	
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			int w;
			cin>>w;
			if(i>j)
			{
				a[++cnt].x=i;
				a[cnt].y=j;
				a[cnt].w=w;
			}
		}
	}
	
	for(int i=1;i<=cnt;i++)//初始化 
	{
		f[i]=i;
	}
	
}
    
int Kruskal()//核心算法 
{
	sort(a+1,a+cnt+1,cmp);//排序 
	
	for(int i=1;i<=cnt;i++)
	{
		int x=find(a[i].x);
		int y=find(a[i].y);
		if(x!=y)
		{
			f[x]=y;
			++tot;
			ans+=a[i].w;
		}
		if(tot==n)
		break;
	}
	
	return ans;
}

int main()//主函数 
{
	init();
	cout<<Kruskal()<<endl;
	return 0;
}
```
**完结**
最后安利一下我的[博客](https://www.luogu.org/blog/lwhd/)
（逃）


---

## 作者：Chicago_01 (赞：3)

## 题面（翻译有点问题，最后一句话）

农民John 决定将水引入到他的n(1<=n<=300)个牧场。他准备通过挖若

干井，并在各块田中修筑水道来连通各块田地以供水。在第i 号田中挖一口井需要花费W_i(1<=W_i<=100,000)元。连接i 号田与j 号田需要P_ij (1 <= P_ij <= 100,000 , P_ji=P_ij)元。

请求出农民John 需要为使所有农场都与有水的农场相连或拥有水井所需要的钱数。

## 题意

有n个点，每个点之间都有边权，但是每个点也有点权。

要求算出每个点都连通的情况下（但是不要求每个点的点权都算上），最小价值。

## 题解

这题很容易想到最小生成树，但是又有好多人不敢下手去写最小生成树，因为这里的每个点还有点权。

我们可以转换一下思路，把每个点的点权当成一个指向自己的边权，然后构造一棵最小生成树就好了！

## 代码

```
#include<bits/stdc++.h>
using namespace std;

const int maxx = 1e3+10;
int n,cnt = 0,fa[maxx*maxx];

struct edge{
    int u,v,w;
    bool operator < (const edge &qwq)
    {
        return w < qwq.w;
    }
}G[maxx*maxx];

inline void init()
{
    cin >> n;
    for(int i = 1;i <= n;++i)
    {
        int w;
        cin >> w;
        G[++cnt].u = 0;
        G[cnt].v = i;
        G[cnt].w = w;
    }
    for(int i = 1;i <= n;++i)
    {
        for(int j = 1;j <= n;++j)
        {
            int w;
            cin >> w;
            if(i > j)
            {
                G[++cnt].u = i;
                G[cnt].v = j;
                G[cnt].w = w;
            }
        }
    }
    for(int i = 1;i <= cnt;++i) fa[i] = i;
}    

inline int fin(int x)
{
    return fa[x] == x ? x : fa[x] = fin(fa[x]);
}

inline int kul()
{
    sort(G+1,G+cnt+1);
    int ans = 0,qwq = 0;
    
    for(int i = 1;i <= cnt;++i)
    {
        int x = fin(G[i].u),y = fin(G[i].v);
        if(x != y)
        { 
            fa[x] = y;
            ++qwq;
            ans += G[i].w;
        }
        if(qwq == n) break;
    }

    return ans;
}

int main(int argc, char const *argv[])
{
    init();
    cout << kul();
    return 0;
}
```

---

## 作者：JOHNKRAM (赞：3)

乍一看，这题就是个最小生成树。然而，可以打井似乎又否定了最小生成树。

其实，还是最小生成树。

增加一个点S，与每个点都有边相连，边权为打井的代价。

再求这个新图的最小生成树就可以了。


---

## 作者：赤霞QvQ (赞：1)

虽然这道题已经有很多巨佬写了题解，但我还是想尝试一下

翻遍题解区，用$Prim$的好像只有$1$个,还在很后面，但是这道题用$Prim$真的比$Kru$好啊！

那我写的仔细一点吧：

### 首先说说优点在哪吧：

$1.$点很少，边很多，$Prim$快！

$2.$思路$Prim$更好想

### 那么就开始讲解啦！

大家都是非常会$Prim$的人对不对！大家都懂$Prim$的对不对！大家都是神犇对不对！！！我看到人群中有部分只会$Kru$的人低下了头……

好啦，那就讲一讲$Prim$吧

$Prim$的大致思路我就不说了，大家自行前往[P3366 【模板】最小生成树的题解区（有链接）](https://www.luogu.org/problemnew/solution/P3366)，大家看第二篇，个人觉得第二篇写的比较好，但是$Prim$具体还是要去学的，掌握多种方法还是很重要的

那么比较一下$Prim$和$Kru$吧

$ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $Prim$ $ $ $ $ $ $ $ $  $ $ $ $ $ $ $ $ $ $ $ $$Kru$

时间复杂度：  $ $ $ $ $O(n^2)$  $ $ $ $ $ $ $O(m$ $lgm)$

空间复杂度：  $ $ $ $ $O(n^2)$  $ $ $ $  $ $ $ $ $ $ $ $ $ $ $O(m)$

其中，$n$为点数，$m$为边数

由此可见，在点数少的时候，用$Prim$;在边少的时候，用$Kru$

那么把标程放上来：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[5005][5005],dis[5005],n,m,u,v,w,ans;
bool used[5005];
int Prim()
{
	memset(dis,0x3f,sizeof(dis));
	memset(used,false,sizeof(used));
	dis[1]=0;
	for(int i=1;i<=n;i++)
	{
		int x=0;
		for(int j=1;j<=n;j++)
			if(used[j]==false&&(x==0||dis[x]>dis[j])) x=j;
		used[x]=true;
		ans+=dis[x];
		for(int j=1;j<=n;j++)
			if(used[j]==false)
				dis[j]=min(dis[j],a[j][x]);    //手动做标记
	}
	return ans;
}

int main()
{
	cin>>n>>m;
	memset(a,0x3f,sizeof(a));
	for(int i=1;i<=m;i++)
	{
		cin>>u>>v>>w;
		a[u][v]=a[v][u]=min(a[u][v],w);
	}
	cout<<Prim()<<endl;
	return 0;
}
```

（这个程序提交$P3366$的时候要开$O_2$才能过，原因：这道题点太多啦！！！！！！！！！！！！！！！！！！！！！！）

好了，相信你现在一脸懵：为什么要把这道题的程序放上来呢？

原因：这道题真的，只用改几个字就结束了

在我做标记的那一行，只要把自己打井的钱数加进去一起求最小值就结束了！

这就是$Prim$优于$Kru$的一个地方，$Kru$考虑边，很难受，很难想但是$Prim$就很好想到！

那么就上这道题的代码了！

```cpp
#include<bits/stdc++.h>
using namespace std;
int w[305],a[305][305],dis[305],n,ans;
bool used[305];
int Prim()
{
	memset(dis,0x3f,sizeof(dis));
	memset(used,false,sizeof(used));
	int minn=INT_MAX,st=0;
	for(int i=1;i<=n;i++)
	{
		if(minn>w[i])
		{
			minn=w[i];
			st=i;
		}
	}
	ans+=minn;
	dis[st]=0;
	for(int i=1;i<=n;i++)
	{
		int x=0;
		for(int j=1;j<=n;j++)
			if(used[j]==false&&(x==0||dis[x]>dis[j])) x=j;
		used[x]=true;
		ans+=dis[x];
		for(int j=1;j<=n;j++)
			if(used[j]==false)
				dis[j]=min(min(dis[j],a[x][j]),w[j]);    //看见没有？？Prim牛逼！
	}
	return ans;
}

int main()
{
	cin>>n;
	memset(a,0x3f,sizeof(a));
	for(int i=1;i<=n;i++) cin>>w[i];
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cin>>a[i][j];
		}
	}
	cout<<Prim()<<endl;
	return 0;
}
```

大家真的要掌握多种方法啊！万一就有数据卡爆了$Kru$怎么办（好像不大可能……）

---

## 作者：LlLlCc (赞：1)

首先，这题是一道**MST**的模板题。

为什么这么说呢？因为题目要求将所有点联通，自然而然就会想到MST，但这题有点特殊。就是可能是一个**森林**，因为每个节点是可以自己独立成为一颗树的，即可能会有**多颗最小生成树**。

求**多颗**最小生成树肯定要比求**一颗**复杂（~~其实是我不会~~），所有我们要将**多颗**转化成一颗，但怎么转呢？

森林转化为树很简单，只要在森林中建一个根，将所有子树联向这个根就将这个森林转化为一颗树了。

这题也是一样，对于每个点，向我们新建的“森林的根节点”连边，边值就是自己挖井的费用，即求N+1个节点的MST

代码：
```
#include<bits/stdc++.h>
#define maxn 305
using namespace std;
int n,fa[maxn],Q[maxn],tot,Ans,x;
struct lc{
	int x,y,z;
	bool operator <(const lc b)const{return z<b.z;}
}a[maxn*maxn];
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-f;ch=getchar();}
	while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
inline int getfa(int x){
	if (fa[x]==x) return x;
	return fa[x]=getfa(fa[x]);
}
int main(){
	n=read();
	for (int i=1;i<=n;i++) Q[i]=read(),fa[i]=i;
	for (int i=1;i<=n;i++)
	for (int j=1;j<=n;j++){
		x=read();
		if (i!=j) a[++tot].x=i,a[tot].y=j,a[tot].z=x;
    }
	for (int i=1;i<=n;i++) a[++tot].x=i,a[tot].y=n+1,a[tot].z=Q[i];
	sort(a+1,a+tot+1);
	for (int i=1;i<=tot;i++){
		int fx=getfa(a[i].x),fy=getfa(a[i].y);
		if (fx==fy) continue;
		fa[fy]=fx,Ans+=a[i].z;
	}
	printf("%d",Ans);
	return 0;
}
```


---

## 作者：Hiraeth (赞：0)

解题报告：

这条题目乍一眼看上去真的很难很难 

一点思路都没有

如果没有挖掘每一口井需要的花费，那么这条题目就变成了连接所有的点所花费的最小权值，那么问题是他每一口井还有花费，而且也不一定只挖一口井，同时井还是必须要挖的。

那么我们就要思考？

求连接一个图里面的所有节点的最小权值肯定是求这个图的最小生成树，这个肯定是毋庸置疑的，那么我们挖掘每一口的井所花费的代价是不是可以看作为该口井连有一条指向水源的边呢？

水源头我们抽象为0号节点，增加n条指向水源的边，边权值为挖井所花费的代价，那么在进行Kruskal时，要保证节点全部覆盖，那么必定有指向水源的边，即有水井被挖了。

代码如下:

```cpp
#include<bits/stdc++.h>
using namespace std;
struct p{
	int x,y,z;
}a[1000005];
int tmp,tot,n,px,py,ans,f[305];
int find(int x){
	if (x==f[x]) return x;
	return f[x]=find(f[x]);
}
bool cmp(p a,p b){
	return a.z<b.z;
}
int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) f[i]=i;
	for (int i=1;i<=n;i++){
		scanf("%d",&tmp);
		tot++;
		a[tot].x=0;
		a[tot].y=i;
		a[tot].z=tmp;
	}
	for (int i=1;i<=n;i++)	
		for (int j=1;j<=n;j++){
			scanf("%d",&tmp);
			if (i==j) continue;
			tot++;
			a[tot].x=i;
			a[tot].y=j;
			a[tot].z=tmp;
		}
	sort(a+1,a+tot+1,cmp);
	for (int i=1;i<=tot;i++){
		px=find(a[i].x);
		py=find(a[i].y);
		if (px==py) continue;
		f[px]=py;
		ans+=a[i].z;
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：万弘 (赞：0)

题目要求"使所有农场都与有水的农场相连或拥有水井所需要的钱数"

所以我们可以**设一个虚点表示井,井与每个点连边的边权就是在那个点打井的开销**,这样就使最后解得的方案是一棵树,在图中找边权和最小的树,直接跑最小生成树就行

按理说稠密图应该用Prim跑更快,然而我只会Kru
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
typedef long long ll;
#define maxn 311
#define maxm 300001

struct Edge
{
	ll u,v,w;
	bool operator <(const Edge &t)
	const
	{
		return w<t.w;
	}
}e[maxm];
ll n,m=0;
void start()
{
	scanf("%lld",&n);
	for(ll i=1;i<=n;++i)//addedge(0,i,w)
	{
		++m;
		e[m].u=0;e[m].v=i;//井的编号是0,但是n+1也可以的
		scanf("%lld",&e[m].w);
	}
	for(ll i=1;i<=n;++i)
	{
		for(ll j=1;j<=n;++j)//addedge(i,j,w)
		{
			++m;
			e[m].u=i;e[m].v=j;
			scanf("%lld",&e[m].w);
		}
	}
}

struct ufs//封装并查集(union find set)
{
	ll fa[maxn];
	void start()
	{
		for(ll i=0;i<=n;++i)fa[i]=i;//不能把0漏了
	}
	ll find(ll x)
	{
		if(fa[x]==x)return x;
		else return find(fa[x]);
	}
	bool uni(ll a,ll b)
	{
		a=find(a),b=find(b);
		if(a==b)return 0;
		fa[a]=b;
		return 1;
	}
}s;
ll Kru()
{
	std::sort(e+1,e+m+1);
	ll cnt=0,res=0;
	for(ll i=1;i<=m;++i)
	{
		if(s.uni(e[i].u,e[i].v))
		{
			++cnt;
			res+=e[i].w;
			if(cnt==n)return res;//有n+1个点,所以生成树有n条边
		}
	}
	return -1;
}
int main()
{
	start();//模块化编程
	s.start();
	printf("%lld",Kru());
	return 0;
}
```

---

## 作者：HDWR (赞：0)

本文早已发布于[Handwer's Blog](https://blog.handwer-std.top/2019-01-12/BZOJ1601/)

很显然这道题需要最小生成树

那么是不是我们生成树之后加上根节点的$w$值就可以了？

显然不！
很容易就能举出反例：

最小生成树的根节点$w_1=99999$，次小生成树的根节点$w_2=1$，两个生成树答案之差 $ans_1-ans_2=1$，那么此时选择次小生成树是更优的

那么我们就可以考虑建一个虚拟的编号为$n+1$的点，对于所有的点$i$以$w_i$为边权进行连接

最后直接跑最小生成树即可，正确性显然

# 代码实现
```cpp
/* -- Basic Headers -- */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>

/* -- STL Iterators -- */
#include <vector>
#include <string>
#include <stack>
#include <queue>

/* -- External Headers -- */
#include <map>
#include <cmath>

/* -- Defined Functions -- */
#define For(a,x,y) for (int a = x; a <= y; ++a)
#define Forw(a,x,y) for (int a = x; a < y; ++a)
#define Bak(a,y,x) for (int a = y; a >= x; --a)

namespace FastIO {
    
    inline int getint() {
        int s = 0, x = 1;
        char ch = getchar();
        while (!isdigit(ch)) {
            if (ch == '-') x = -1;
            ch = getchar();
        }
        while (isdigit(ch)) {
            s = s * 10 + ch - '0';
            ch = getchar();
        }
        return s * x;
    }
    inline void __basic_putint(int x) {
        if (x < 0) {
            x = -x;
            putchar('-');
        }
        if (x >= 10) __basic_putint(x / 10);
        putchar(x % 10 + '0');
    }
    
    inline void putint(int x, char external) {
        __basic_putint(x);
        putchar(external);
    }
}


namespace Solution {
    struct UnionFind {
        static const int MAX_SIZ = 100000 + 10;
        
        int U[MAX_SIZ];
        
        UnionFind() {
            For (i, 1, MAX_SIZ) U[i] = i;
        }
        
        int Find(int x) {
            if (U[x] == x) return U[x];
            return U[x] = Find(U[x]);
        }
        
        void Union(int x, int y) {
            int xx = Find(x);
            int yy =  Find(y);
            if (xx == yy) return;
            U[x] = y;
        }
    };
    
    struct Graph {
        static const int MAXN = 1000 + 10;
        static const int MAXM = 100000 + 10;
        
        struct Node {
            int nweight, now;
            
            Node() { nweight = now = 0; }
            
            bool operator < (const Node &that) const {
                return nweight > that.nweight;
            }
        };
        
        struct Edge {
            int now, weight, next;
            int raw_now, raw_next;
            
            bool operator < (const Edge &that) const {
                return weight < that.weight;
            }
        } edge[MAXM * 2];
        
        int head[MAXN], dis[MAXN], cnt;
        
        inline void addEdge(int prev, int next, int weight, bool isR = true) {
            if (isR) { addEdge(next, prev, weight, false); }
            edge[++cnt].now = next;
            edge[cnt].weight = weight;
            edge[cnt].next = head[prev];
            head[prev] = cnt;
            
            edge[cnt].raw_next = next;
            edge[cnt].raw_now = prev;
        }
        
        inline Node NewNode(int nowWeight, int now) {
            Node tmp;
            tmp.nweight = nowWeight;
            tmp.now = now;
            return tmp;
        }
        
        inline void SPFA() {
            memset(dis, 0x7f, sizeof(dis));
            std::priority_queue<Node> q;
            q.push(NewNode(0, 1));
            dis[1] = 0;
            while (!q.empty()) {
                Node NowNode = q.top();
                q.pop();
                int now = NowNode.now;
                for (int e = head[now]; e; e = edge[e].next) {
                    int to = edge[e].now;
                    if (dis[to] > dis[now] + edge[e].weight) {
                        dis[to] = dis[now] + edge[e].weight;
                        q.push(NewNode(dis[to], to));
                    }
                }
            }
        }
        
        inline int Kruskal() {
            int ans = 0, tot = 0;
            UnionFind u;
            std::sort(edge + 1, edge + 1 + cnt);
            for (int i = 1; i <= cnt; ++i) {
                int eu = u.Find(edge[i].raw_now);
                int ev = u.Find(edge[i].raw_next);
                if (eu == ev) continue;
                u.Union(eu, ev);
                ans += edge[i].weight;
                
                ++tot;
                if (tot == cnt - 1) break;
            }
            return ans;
        }
    } g1;
    
    int n, m;
}

signed main() {
#define HANDWER_FILE
#ifndef HANDWER_FILE
    freopen("testdata.in", "r", stdin);
    freopen("testdata.out", "w", stdout);
#endif
    using namespace Solution;
    using FastIO::getint;
    n = getint();
    For (i, 1, n) g1.addEdge(i, n + 1, getint());
    For (i, 1, n) {
        For (j, 1, n) {
            int p = getint();
            g1.addEdge(i, j, p, false);
        }
    }
    FastIO::putint(g1.Kruskal(), '\n');
    return 0;
}
```

---

## 作者：EightSixSun (赞：0)

不知道为什么都说要加个0号点啊。。。

直接kru+贪心最后再扫一遍不好吗？

比较显然的贪心+最小生成树

并查集维护的同时维护一个联通块里挖井的花费最小值，做最小生成树的时候贪心一下

如果联通（一条边）的花费加上两个联通块里挖井的最小值的较小值小于在两个联通块里挖井的花费最小值之和，那么我们就把它们联通，否则就让他们分别挖井就好了



代码

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define rep(i,l,r) for(int i=l;i<=r;++i)
#define per(i,l,r) for(int i=l;i>=r;--i)
using namespace std;
inline int read()
{
	char c;
	bool t=0;
	int a=0;
	while((c=getchar())==' '||c=='\n'||c=='\r');
	if(c=='-')
	{
		t=1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		a*=10;
		a+=(c-'0');
		c=getchar();
	}
	return a*(t?-1:1);
}
struct Edge{
	int from,to,v;
	bool operator<(const Edge &b)const
	{
		return v<b.v;
	}
}e[301*301];
int n,w[301],cnt;
int fa[301],minn[301];
bool water[301];
int find(int x)
{
	return fa[x]<0?x:(fa[x]=find(fa[x]));
}
void merge(int x,int y)
{
	x=find(x);y=find(y);
	if(fa[x]>fa[y])
	 swap(x,y);
	fa[x]+=fa[y];
	minn[x]=min(minn[x],minn[y]);
	fa[y]=x;
}
void add(const int &from,const int &to,const int &v)
{
	e[++cnt].from=from;
	e[cnt].to=to;
	e[cnt].v=v;
}
int main()
{
	//freopen("a.in","r",stdin);
	int tx,ty;
	long long ans=0;
	n=read();
	rep(i,1,n)
	 fa[i]=-1;
	rep(i,1,n)
	{
		w[i]=read();
		minn[i]=w[i];
	}
	rep(i,1,n)
	 rep(j,1,n)
	 {
		tx=read();
		if(i<j)//not have to add an edge twice
		 add(i,j,tx);
	 }
	sort(e+1,e+cnt+1);
	rep(i,1,cnt)
	{
		tx=find(e[i].from);ty=find(e[i].to);
		if(tx==ty)
		 continue;
		if(min(minn[tx],minn[ty])+e[i].v<=minn[tx]+minn[ty])//e[i].v<=minn[tx]+minn[ty])
		{
			ans+=e[i].v;
			merge(tx,ty);
		}
	}
	rep(i,1,n)
	{
		tx=find(i);
		if(!water[tx])
		{
			ans+=minn[tx];
			water[tx]=1;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：ivorLin (赞：0)

看了一下题解，感觉还是说得不细，以贴代码为主。

其实叙述明确的话，代码都无所谓了。

先假设不用打井，就是标准的**最小生成树**模板。

然而是要的。假设最小生成树的 **边权和 固定**，就**贪心**找最便宜的井。

如果只能打一口井，这题就结束了。   
~~然而这题充分体现了万恶的资本主义压榨利益的本质。~~

有时，一条边权可能大于这条边相接的点权。替换，更新答案。
$$the-end.$$

广告：[我的洛谷博客](https://www.luogu.org/blog/IvorLin/)

---

## 作者：circlegg (赞：0)

prim做法，先将打井的价格存入dis数组，找一个打井最便宜的，打个井设为原点，然后跑prim，用边权更新dis，边短就连边，井小就打井，打完把dis变0

评测记录：42ms  https://www.luogu.org/record/show?rid=2408644

···
    
    
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,dis[305],e[305][305],t,w,ans;
bool flag;
int main(){
    scanf("%d",&n);
    dis[0]=(1<<30);
    for(int i=1;i<=n;i++){
        scanf("%d",&dis[i]);
        if(dis[i]<dis[0]){//找最便宜的井设为原点 
            dis[0]=dis[i];
            t=i;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            scanf("%d",&e[i][j]);
        }
    }
    ans+=dis[0];//加上原点打井的钱 
    dis[t]=0;
    for(int j=1;j<=n;j++){//先跑一遍更新到原点是打井划算还是铺路划算 
        if(dis[j]>e[t][j]){
            dis[j]=e[t][j];
        }
    }
    for(int i=1;i<=n-1;i++){//prim部分 
        w=(1<<30);
        for(int j=1;j<=n;j++){//看到那个点最近 
            if(dis[j]<w&&dis[j]!=0){
                w=dis[j];
                t=j;
            }
        }
        ans+=w;//加上到最近的点的价格 
        dis[t]=0;
        for(int j=1;j<=n;j++){
            if(dis[j]>e[t][j]){
                dis[j]=e[t][j];//更新到每个点的价格 
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
···
```

---

## 作者：crowworks695 (赞：0)

采用的楼下前辈构造一个新点的思路~看到没有c++的最小生成树题解感到灰常不爽

思路是构建一个虚拟的点，这里将其编号为n+1，该店与原图的点的权值为该原图的点上打井的费用，然后求一遍最小生成树。

道理是这样的：如果去掉加上的这个点，求出最小生成树的图会变成一个个连通分量，而每个连通分量中都必然存在一个打了井的点，也就是说，这些互不相连连通分量之间可以看成是用打井连通的，使该图成为一个连通的图。当你选择在一个点打井时，可以看做你将该点与别的打井了的点连通了，这两个连通分量通过打井连接在了一起，因此可以新建一个点n+1，到原图中每个点的距离等于在该点打井的费用，再求最小生成树。

```cpp

#include <cstdio>
#include <algorithm>

using namespace std;

int cost[301],cnt=0,fa[301];

struct edge
{
    int u,v,w;
}e[100000];

bool cmp(edge a,edge b)
{
    return a.w<b.w;
}

int find(int x)
{
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

int main()
{
    int n,ans=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&cost[i]);
        e[++cnt].u=n+1;
        e[cnt].v=i;
        e[cnt].w=cost[i];
        fa[i]=i;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            int t;
            scanf("%d",&t);
            if(j>i)
            {
                e[++cnt].u=i;
                e[cnt].v=j;
                e[cnt].w=t;
            }
        }
    }
    sort(e+1,e+cnt+1,cmp);
    int flag=0;
    for(int i=1;i<=n;i++)
    {
        while(1)
        {
            ++flag;
            int t1=find(e[flag].u),t2=find(e[flag].v);
            if(t1==t2)continue;
            else
            {
                fa[t2]=fa[t1];
                ans+=e[flag].w;
                break;
            }
        }
    }
    printf("%d",ans);
    return 0;
} 

```

---

## 作者：ARSKB (赞：0)

首先根据数据范围。n<=300,因此可以使用O(n^3)以及以下的算法。

可以证明：只要每次找到灌水代价最小的田，总策略就一定是最小代价。因无法放图，所以这里不再详细分析。

由上，选择贪心算法。

每一片田要灌水，有两种选择：第一种是打井，第二种是引水。

先寻找当前打井代价最小的田，然后再寻找引水代价最小的田，两个最小值比较后再将代价累加。

下面给出AC代码：

```delphi

var n,i,j,k,top,min,minx,miny,sum:longint;
    w:array[0..300]of longint;
    p:array[0..300,0..300]of longint;
    b:array[1..300]of boolean;
    order:array[1..300]of integer;

begin
    readln(n);
    sum:=0;
    fillchar(b,300,false);
    for i:=1 to n do begin
        p[i,0]:=maxlongint;
    end;
    for i:=1 to n do readln(w[i]);
    for i:=1 to n do begin
        for j:=1 to n do
            read(p[i,j]);
        readln;
    end;
    w[0]:=maxlongint;
    top:=1;
    p[0,0]:=maxlongint;;
    for i:=1 to n do begin
        min:=0;
        for j:=1 to n do
            if (w[j]<w[min])and(b[j]=false) then
                min:=j;
        minx:=0;
        miny:=0;
        for j:=1 to top do
            for k:=1 to n do
                if (b[k]=false)and(order[j]<>k) then
                    if p[minx,miny]>p[k,order[j]] then begin
                        minx:=k;
                        miny:=order[j];
                    end;
        if p[minx,miny]<w[min] then
            sum:=sum+p[minx,miny]
        else begin
            sum:=sum+w[min];
            minx:=min;
        end;
        order[top]:=minx;
        inc(top);
        b[minx]:=true;
    end;
    writeln(sum);
end.

```(pascal)
代码稍微有点凌乱..凑合着看..

就是这样=-=



---

## 作者：寒鸽儿 (赞：0)

我们假定有一个结点,~~是万恶~~水力之源。所有打井可以等效为与水力之源签订协议连接。  
于是所有操作变成了连边操作,那么直接当最小生成树套prim板子即可。  
```cpp
#include <cstdio>

using namespace std;

const int N = 345, INF = 0x3f3f3f3f;
int d[N][N], dis[N], vis[N], ans = 0;
inline int min(int x, int y) { return x < y ? x : y; }

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%d", dis + i);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			scanf("%d", &d[i][j]);
	int cur = 0; dis[cur] = INF;
	for(int i = 1; i <= n; ++i) if(dis[i] < dis[cur]) cur = i;
	ans += dis[cur]; vis[cur] = 1;
	for(int i = 1; i <= n; ++i) if(!vis[i]) dis[i] = min(dis[i], d[cur][i]);
	for(int i = 1; i < n; ++i) {
		cur = 0;
		for(int i = 1; i <= n; ++i) if(!vis[i] && dis[i] < dis[cur]) cur = i;
		vis[cur] = 1; ans += dis[cur];
		for(int i = 1; i <= n; ++i) if(!vis[i]) dis[i] = min(dis[i], d[cur][i]); 
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：海纳百川 (赞：0)

就是一道最小生成树，我们设一个点，到所有井都有边相连，边权为打井的代价，求最小生成树即可



```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int a[305][305],minn,mine[305],ans,i,j,n,x,b;
int prim()
{
    for (i=1;i<=n;i++)
      mine[i]=a[1][i];
    mine[1]=0;
    for (i=1;i<n;i++)
    {
        minn=100000;
        for (j=1;j<=n;j++)
        if ((mine[j]!=0)&&(minn>mine[j]))
        {x=j;minn=mine[j];}
        ans=ans+minn;
        mine[x]=0;
        for (j=1;j<=n;j++)
        if ((mine[j]!=0)&&(a[x][j]<mine[j]))
          mine[j]=a[x][j];
    }
}
int main()
{
    cin>>n;
    for (i=1;i<=n;i++)
      for (j=1;j<=n;j++)
        a[i][j]=100000;
    for(i=1;i<=n;i++)
    {
        scanf("%d",&b);
        a[n+1][i]=a[i][n+1]=b;
    }
    for (i=1;i<=n;i++)
      for (j=1;j<=n;j++)
      {
          scanf("%d",&b);
        if(i!=j) a[i][j]=b;
      }
    n++;
    prim();
    cout<<ans;
    return 0;
}
```

---

