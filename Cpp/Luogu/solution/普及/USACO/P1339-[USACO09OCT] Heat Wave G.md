# [USACO09OCT] Heat Wave G

## 题目描述

有一个 $n$ 个点 $m$ 条边的无向图，请求出从 $s$ 到 $t$ 的最短路长度。

## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$1\le n \le 2500$，$1\le m \le 6200$，$1\le w \le 1000$。

【样例说明】   
$5 \to 6 \to 1 \to 4$ 为最短路，长度为 $3+1+3 = 7$。



## 样例 #1

### 输入

```
7 11 5 4
2 4 2
1 4 3
7 2 2
3 4 3
5 7 5
7 3 3
6 1 1
6 3 4
2 4 3
5 6 3
7 2 1```

### 输出

```
7```

# 题解

## 作者：yizimi远欣 (赞：87)

### Dijkstra + 线段树解法

最近集训一位大佬给我讲了一个奇妙的Dijkstra优化方法，他告诉我线段树可以代替优先队列来优化Dijkstra。

**我第一个感觉是眼睛一亮**

于是我认真的听完了他讲的方法。

Dijkstra算法周围的大佬已经讲的十分的漂亮了，我觉得我再插一嘴就是多余。所以我就着重讲一下用线段树的优化。

首先考虑我们当时要用优先队列做什么。

是不是就是维护的dis[]数组的最小值以及它的终点？

具体操作？

不就是要我们向优先队列里放入一个dis和终点，然后每次松弛都出队一组，再进行更新？

那么这道题在这里就变成了一个简单的线段树问题。（逃

不过线段树有个性质：不能删点。那该怎么进行那个要求我们出队的操作？

我们可以考虑：如果我们把那个要出队的一组数中dis修改为INF，那么我们只要线段树里有数，就一定取不到INF，就不会用到这组数了，也就相当于出队了。如果我们在最开始初始化（建树）时就只留一个dis为0的s（起点编号），其余都变成INF，那么我们插入一组数时直接单点修改不就好啦？

如何判断队列为空？我们如果队列中只有INF，也就是没有真实要用的数据，队列就是空的了。

这里只需要一个单点修改的一个线段树就好啦。

### 代码实现
```cpp
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
using namespace std;
#define go(i, j, n, k) for (int i = j; i <= n; i += k)
#define fo(i, j, n, k) for (int i = j; i >= n; i -= k)
#define rep(i, x) for (int i = h[x]; i; i = e[i].nxt)
#define mn 100010
#define mm 200020
#define inf 2147483647
#define ll long long
#define ld long double
#define fi first
#define se second
#define root 1, n, 1
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define bson l, r, rt
inline int read(){
    int f = 1, x = 0;char ch = getchar();
    while (ch > '9' || ch < '0'){if (ch == '-')f = -f;ch = getchar();}
    while (ch >= '0' && ch <= '9'){x = x * 10 + ch - '0';ch = getchar();}
    return x * f;
}
inline void write(int x){
    if (x < 0)putchar('-'),x = -x;
    if (x > 9)write(x / 10);
    putchar(x % 10 + '0');
}
//This is AC head above...
struct node{
    int v, nxt, w;
} e[mm << 1];
int h[mn], p;
inline void add(int a,int b,int c){
    e[++p].nxt = h[a];
    h[a] = p;
    e[p].v = b;
    e[p].w = c;
}
int dis[mn];
int n, m, s, t;
struct tree{
    int minw, minv;
};
struct SegmentTree{
    tree z[mn << 2];
    inline void update(int rt){
        z[rt].minw = min(z[rt << 1].minw, z[rt << 1 | 1].minw);//维护区间最小值
        z[rt].minv = (z[rt << 1].minw < z[rt << 1 | 1].minw) ? z[rt << 1].minv : z[rt << 1 | 1].minv;//维护区间最小值位置
    }
    inline void build(int l,int r,int rt){//建树
        if(l==r){
            z[rt].minw = l == s ? 0 : inf;//我们可以直接建树时把s的点设置为0
            z[rt].minv = l;//记录最小值位置，方便修改
            return;
        }
        int m = (l + r) >> 1;
        build(lson);
        build(rson);
        update(rt);
    }
    inline void modify(int l,int r,int rt,int now,int v){//单点修改
        if(l==r){
            z[rt].minw = v;
            return;
        }
        int m = (l + r) >> 1;
        if(now<=m)
            modify(lson, now, v);
        else
            modify(rson, now, v);
        update(rt);
    }
} tr;
inline void Dij(){//Dijkstra的核心部分
    go(i,1,n,1){
        dis[i] = inf;
    }//初始化dis
    dis[s] = 0;
    while(tr.z[1].minw < inf){//这里就是判断是否为空
        int x = tr.z[1].minv;//取整个线段树中最小的点
        tr.modify(root, x, inf);//单点修改最小的点为inf
        rep(i,x){
            int v = e[i].v;
            if(dis[v] > dis[x] + e[i].w){
                dis[v] = dis[x] + e[i].w;
                tr.modify(root, v, dis[x] + e[i].w);//这里就是类似入队操作
            }
        }
    }
}
int main(){
    n = read(), m = read(), s = read(), t=read();
    go(i,1,m,1){
        int x = read(), y = read(), v = read();
        add(x, y, v);
        add(y, x, v);//这个一定记住，无向图要正反两条边QAQ
    }
    tr.build(root);//建树
    Dij();//Dijkstra
    cout << dis[t];
    return 0;
}

```

### 这样似乎要比priority_queue优化快一些

#### 第十一次写题解，希望可以给想优化Dijkstra的同学一个新思路

---

## 作者：yizimi远欣 (赞：42)

## 不会SPFA的同学们看过来

##### 既然dalao们都在打SPFA，~~我也不会SPFA~~，所以写个Dijkstra的题解。

首先提醒那些~~和我一样~~感觉自己的代码对，刚从[P3371 【模板】单源最短路径（弱化版）](https://www.luogu.org/problemnew/show/P3371)过来的同学。

## 这个题的边是无向图！！！

~~听到[大佬](https://www.luogu.org/space/show?uid=50926)说是模板题，我就从P3371直接过来交上了，然后WA掉9个点，，，我改了好长时间，，，才发现QAQ~~

还有很多大佬告诉我这是一道练SPFA的好题，的确，数据说得过，似乎也没人卡QAQ，但是我觉得那Dijkstra会更方便一些。

其实真的就是道模板题

我在这里细讲一下Dijkstra做法（包括堆优化方法）

### 1.Dijkstra无优化版

实际上Dijkstra的思想和Floyd的部分思想是一样的，有用到了一个神奇的东西：松弛操作

		if(map[i][j]>map[i][k]+map[k][j])
    		map[i][j]=map[i][k]+map[k][j];
        
QAQ？？？完了？？？

完了。这就是Dijkstra与Floyd的核心思想，Dijkstra就是把时间复杂度降低，范围缩小而已。

（相信都学过Dijkstra）

想必大家也都知道有一个操作，就是寻找最近的点，我们在写的时候是O(n)的。。。

不觉得太慢了吗？？？

于是我们有了~~~~

### 2.Dijkstra + 堆优化

不要觉得堆优化十分高大上，实际上只优化了一些最简单而又最费时间的操作。

大家还记得优先队列吗？？？（堆也行）

		#include<queue>
    	priority_queue<int> que;
    
就是这个东西，可以O(logn)的找到最近的点了QAQ

具体操作看代码吧！QAQ

## 代码

### 链式前向星存图(无优化的找不到了，这个只有带堆优化的QAQ，想看无优化的向下翻)：

```cpp
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
using namespace std;
#define go(i, j, n, k) for (int i = j; i <= n; i += k)
#define fo(i, j, n, k) for (int i = j; i >= n; i -= k)
#define rep(i, x) for (int i = h[x]; i; i = e[i].nxt)
#define mn 100010
#define inf 1 << 30
#define ll long long
#define ld long double
#define fi first
#define se second
#define root 1, n, 1
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
inline int read(){
    int f = 1, x = 0;char ch = getchar();
    while (ch > '9' || ch < '0'){if (ch == '-')f = -f;ch = getchar();}
    while (ch >= '0' && ch <= '9'){x = x * 10 + ch - '0';ch = getchar();}
    return x * f;
}
inline void write(int x){
    if (x < 0)putchar('-');x = -x;
    if (x > 9)write(x / 10);
    putchar(x % 10 + '0');
}
//This is AC head above...
struct edge{
    int v, nxt, w;
} e[mn<<1];
int h[mn],p;
inline void add(int a,int b,int c){
    p++;
    e[p].nxt = h[a];
    h[a] = p;
    e[p].v = b;
    e[p].w = c;
}
struct node{
    int u,v;
    bool operator <(const node &b) const{
        return u > b.u;
    }
};
/*
bool operator <(const node &a,const node &b) {
        return a.u > b.u;
};
*/
int n, m, s, t;
int dis[mn];
priority_queue<node> q;
inline void Dij(int s){
    go(i, 0, n, 1)
        dis[i] = inf;
    dis[s] = 0;
    node o;
    o.u = 0;
    o.v = s;
    q.push(o);
    while (q.size()){
        int u = q.top().v;
        int d = q.top().u;
        q.pop();
        if(d!=dis[u])
            continue;
        rep(i,u){
            int v = e[i].v;
            int w = e[i].w;
            if (dis[v] > dis[u] + w){
                dis[v] = dis[u] + w;
                node p;
                p.u = dis[v], p.v = v;
                q.push(p);
            }
        }
    }
}
int main(){
    n=read(),m=read(),s=read(),t=read();
    go(i,1,m,1){
        int u = read(), v = read(), w = read();
        add(u, v, w);
        add(v, u, w);
    }
    Dij(s);
    cout << dis[t];
    cout << "\n";
    return 0;
}
```

### vector暴力存图法（和链式前向星没啥区别，这个包括无优化和有优化的）

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
#include<queue>
#include<vector>
using namespace std;
#define go(i,j,n,k) for(register int i=j;i<=n;i+=k)
#define fo(i,j,n,k) for(register int i=j;i>=n;i-=k)
#define mn 110
#define inf 1<<30
#define root 1,n,1
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
#define ll long long
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')f=-f;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

const int kN = 100000+10;
const int INF = 2147483647;

int s, n, m, k;
int d[kN];
vector<pair<int, int> > G[kN];

bool vis[kN];
void dijkstra_naive(int s) {
    for (int i = 0; i <= n; i++) d[i] = INF;

    d[s] = 0;

    for (int i = 1; i <= n; i++) {
        // find min u, s.t. d[u] < d[i] for all i that vis[i] = false
        int u = -1;
        for (int j = 1; j <= n; j++) if (!vis[j]) {
            if (u == -1 || d[j] < d[u]) {
                u = j;
            }
        }

        if (u == -1 || d[u] >= INF) break;
        vis[u] = true;
        for (int j = 0; j < G[u].size(); j++) {
            int v = G[u][j].first;
            int w = G[u][j].second;
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
            }
        }
    }
}

void dijkstra(int s) {
    for (int i = 0; i <= n; i++) d[i] = INF;

    d[s] = 0;
    priority_queue<pair<int, int> > q;
    q.push(make_pair(0, s));

    while (q.size()) {
        int u = q.top().second;
        q.pop();

        for (int i = 0; i < G[u].size(); i++) {
            int v = G[u][i].first;
            int w = G[u][i].second;
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                q.push(make_pair(-d[v], v));
            }
        }
    }
}

int main() {
    n = read();
    m = read();
    s = read();
    t = read();
    go(i,1,m,1){
        int u=read(), v=read(), w=read();
        pair<int, int> p;   
        p.first = v;    
        p.second = w;
        G[u].push_back(p) ;
        p.first = u;    
        p.second = w;
        G[v].push_back(p) ;
    }
    dijkstra_naive(s);
    //dijkstra(s);
    cout << d[t];
}
```

如果有同学想要板子之类的东西，可以看我的博客QAQ，有部分模板代码QAQ

[就是这里啦](https://yizimiyuanxin.blog.luogu.org/post-ji-ben-suan-zhi-ding-ge-tai-suan-fa-shuo-ju-jie-gou-mu-ban)

#### 第六次发题解，希望可以帮助那些一直10分的同学

---

## 作者：Parabola (赞：37)

刚学Ford

翻了半天的题解

竟然没有一个c++的Ford

可能dalao都去用SPFA了（好像是加了一个队列优化。反正我不会QAQ

于是为了对以后像我这样的蒟蒻有好一点

我打算发一个Ford的题解

关于Ford的思想我就略微讲下吧

首先
松弛是最重要的

那我们先考虑一条边

用dis[i]存到i的最短距离

初始化时将dis[i]全部存为INF

u[i],v[i],w[i]代表u[i]到v[i]的距离为w[i]

则会有下面这个式子

    if(dis[v[i]]>dis[u[i]]+w[i])

        dis[v[i]]=dis[u[i]]+w[i];

而这是处理有向图的

所以对于这道无向图的题

我们还需要一次。

    if(dis[u[i]]>dis[v[i]]+w[i])

        dis[u[i]]=dis[v[i]]+w[i];

那么一共有n条边的话

就要对n条边进行松弛

如果我们把上述记为一次松弛的话

那么我们一共就要进行总点数-1次松弛

因为两点之间的最短路径最多就包括总点数-1条边

恩
思路讲完了

那我就贴代码了

有一点点注释。


```cpp
    #include<iostream>
    using namespace std;
    const int MAXN=6200+5;
    const int INF=2e9;
    int u[MAXN],w[MAXN],v[MAXN],dis[2501],s,e,m,n;
    bool check;//这个变量可以让我们进行略微的优化
    int main()
    {
        cin>>m>>n>>s>>e;//m个点，n条边
        for(int i=1;i<=n;i++)
            cin>>u[i]>>v[i]>>w[i];
        for(int i=1;i<=m;i++)
            dis[i]=INF;
        dis[s]=0;//到起点的最短距离为0
        m--;//一共进行m-1次松弛，可以优化时间
        for(int j=1;j<=m;j++)
        {
            check=true;//每一次松弛将这个变量都给true
            for(int i=1;i<=n;i++)
            {
                if(dis[v[i]]>dis[u[i]]+w[i])
                {
                    dis[v[i]]=dis[u[i]]+w[i];
                    check=false;
                }
                if(dis[u[i]]>dis[v[i]]+w[i])
                {
                    dis[u[i]]=dis[v[i]]+w[i];
                    check=false;
```
}//如果dis在松弛中没有发生变化，直接结束（因为已经求出了最短路径啊）
```cpp
            }                
            if(check)    break;
        }    
        cout<<dis[e];//输出
}
```

---

## 作者：扬皓2006 (赞：24)

这题吧 就是简单的最短路（此篇题解以堆优化的Dijkstra为解法）

不了解最短路各种算法的同学请左转[这里](https://www.luogu.org/blog/20160614dbdaw/p3371-mu-ban-dan-yuan-zui-duan-lu-jing-ruo-hua-ban-ti-xie)

好了现在贴代码:
```
#include<bits/stdc++.h>//万能头
using namespace std;
int hea[620001],tot,d[600021],v[620001];
int n,m,s,e;
priority_queue< pair<int,int> > q;//一维为距离相反数（变！小根堆），第二维为节点编号 
struct Edge{
	int next,to,dis;
}edge[620001];//邻接表存图
void add(int x,int y,int z)
{
	edge[++tot].next=hea[x];
	edge[tot].to=y;
	edge[tot].dis=z;
	hea[x]=tot;
}//插入一条从x到y，边权为z的边
int main()
{
	scanf("%d%d%d%d",&n,&m,&s,&e);
	for(int i=1;i<=m;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
		add(y,x,z);//无向图双向存边
	}
	memset(d,0x3f,sizeof(d));//重置
	memset(v,0,sizeof(v));//重置
	d[s]=0;q.push(make_pair(0,s));//入堆
	while(!q.empty())//
	{
		int x=q.top().second;q.pop();//取出堆顶
		if(v[x]) continue;
		v[x]=1;
		for(int i=hea[x];i;i=edge[i].next)//扫描出边
		{
			int y=edge[i].to;
			if(d[y]>d[x]+edge[i].dis)
			{
				d[y]=d[x]+edge[i].dis;
				q.push(make_pair(-d[y],y));
			}//松弛操作
		}
	} 
	printf("%d",d[e]); 
	return 0; 
}
```
希望大家都能学会最短路的算法，也希望管理大大能通过这篇题解

---

## 作者：_自动AC机_ (赞：24)

### 看着神犇们都在用SPFA、Ford、Dijkstra等等高难度算法,
### 本蒟蒻也只好上传一个Floyd来凑数.
### 下面是一些关于Floyd的介绍：
------------
通过Floyd计算图G=(V,E)中各个顶点的最短路径时，需要引入两个矩阵，矩阵S中的元素a[i][j]表示顶点i(第i个顶点)到顶点j(第j个顶点)的距离。矩阵P中的元素b[i][j]，表示顶点i到顶点j经过了b[i][j]记录的值所表示的顶点。

假设图G中顶点个数为N，则需要对矩阵D和矩阵P进行N次更新。初始时，矩阵D中顶点a[i][j]的距离为顶点i到顶点j的权值；如果i和j不相邻，则a[i][j]=∞，矩阵P的值为顶点b[i][j]的j的值。 接下来开始，对矩阵D进行N次更新。第1次更新时，如果”a[i][j]的距离” > “a[i][0]+a[0][j]”(a[i][0]+a[0][j]表示”i与j之间经过第1个顶点的距离”)，则更新a[i][j]为”a[i][0]+a[0][j]”,更新b[i][j]=b[i][0]。 同理，第k次更新时，如果”a[i][j]的距离” > “a[i][k-1]+a[k-1][j]”，则更新a[i][j]为”a[i][k-1]+a[k-1][j]”,b[i][j]=b[i][k-1]。更新N次之后，就能求出最短路了呢！

------------
Floyd介绍结束.下面是代码,代码里有解释.

```cpp
#include <iostream>
#include <cstring>
using namespace std;
int c,t,ts,te,ti,dis[2501],f[2501][2501],fi,d;
bool flag[2501]= {0};
int main() {
    cin>>t>>c>>ts>>te;
    memset(f,9999999,sizeof(f));	//先把每个距离设为假想无穷大
    for(int i=1; i<=c; i++) {
        cin>>fi>>ti>>d;
        f[fi][ti]=f[ti][fi]=d;		//由于这是无向图,所以需要对称一下
    }
    for(int i=1; i<=t; i++) dis[i]=f[ts][i];
    flag[ts]=true;
    for(int i=1; i<t; i++) {
        int minl=9999999,k=0;
        for(int j=1; j<=t; j++)
            if(!flag[j]&&dis[j]<minl)	//Floyd模板代码
                minl=dis[j],k=j;
        if(k==0) break;
        flag[k]=true;
        for(int j=1; j<=t; j++)
            if(dis[k]+f[k][j]<dis[j])	//还是个模板
                dis[j]=dis[k]+f[k][j];
    }
    cout<<dis[te];
}
```
 _(码字不容易,求管理员通过)_ 

---

## 作者：LRL65 (赞：16)

这是一道**最短路径**的模板题。

下面提供这么几个算法：


------------

Bellman:

暴力，如果顶点数为V，那么执行v-1次，每次遍历所有边，做松弛操作，时间复杂度为O(VE)

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define INF 1<<30;
int n;
int dis[2501],cnt;
struct edge
{
	int x,y,w;
}Edge[20005];
void add(int x,int y,int z){
	Edge[cnt].x=x;
	Edge[cnt].y=y;
	Edge[cnt++].w=z;
}
void bellman(){
	int flag=1,i,j;
	for(j=0;j<n-1&&flag;j++){//做n-1次
		flag=0;
		for(i=0;i<cnt;i++) {
			int u=Edge[i].x,v=Edge[i].y,w=Edge[i].w;
			if(dis[u]+w<dis[v]) {//松弛
				flag=1;
				dis[v]=dis[u]+w;
			}
		}
	}
}
int main(){
	int c,s,e,x,y,z;
	cin>>n>>c>>s>>e;
	for(int i=1;i<=n;i++)dis[i]=INF;
	cnt=dis[s]=0;
	for(int i=1;i<=c;i++) {
		cin>>x>>y>>z;
		add(x,y,z);
		add(y,x,z);
	}
	bellman();
	printf("%d\n",dis[e]);
}
```


------------
Dijkstra+堆优化：
	
1. 初始化，与起点距离全部改成INF，起点设为0
2. 找与这个点距离最近的点（这步可用堆优化）
3. 用找到的点做松弛
4. 标记这个点，一直循环

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2505;
#define INF 1e9
vector<pair<int,int> >e[maxn];
int d[maxn];
void dijkstra(int s){
	priority_queue<pair<int,int> >q;//大根堆
	d[s]=0;
	q.push(make_pair(-d[s],s));
	while(!q.empty()){
		int now=q.top().second;
		q.pop();
		for(int i=0;i<e[now].size();i++) {
			int v=e[now][i].first;
			if(d[v]>d[now]+e[now][i].second) {//松弛
				d[v]=d[now]+e[now][i].second;
				q.push(make_pair(-d[v],v));
			}
		}
	}
}
int main() {
	int n,m,s,t;
	scanf("%d%d%d%d",&n,&m,&s,&t);
	for(int i=0;i<maxn;i++)e[i].clear(),d[i]=INF;
	for(int i=1;i<=m;i++) {//建图
		int u,v,d;
		scanf("%d%d%d",&u,&v,&d);
		e[u].push_back(make_pair(v,d));
		e[v].push_back(make_pair(u,d));
	}
	dijkstra(s);
	printf("%d\n",d[t]);
	return 0;
}
```


------------
还有个SPFA，是Bellman的优化，因为不稳定，这里就不讲了。

最后记得点赞，谢谢！


---

## 作者：lian_sama (赞：8)

这题我采用了两种算法：

1.堆优化的dijkstra

[dij传送门](https://baike.baidu.com/item/%E8%BF%AA%E6%9D%B0%E6%96%AF%E7%89%B9%E6%8B%89%E7%AE%97%E6%B3%95/4049057?fromtitle=Dijkstra%E7%AE%97%E6%B3%95&fromid=215612&fr=aladdin)

2.SPFA

[SPFA传送门](https://baike.baidu.com/item/SPFA%E7%AE%97%E6%B3%95/8297411?fromtitle=SPFA&fromid=11018124&fr=aladdin)

两种算法的时间复杂度如下：

1.O((n+m)logn)

2.O(me)

这是一道适合新人的单源最短路的题。

# Dijkstra

```cpp
//1339
#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
int const N=100001,INF=1e9;
int tot,n,m,s,t,f[N],
target[N],prev[N],last[N],v[N],vis[N];
struct node{
    int id,dis;
    bool operator < (const node &a) const{
        return a.dis<dis;
    }
};
void add(int a, int b, int c){
    target[++tot]=b; 
    prev[tot]=last[a]; 
    v[tot]=c;          
    last[a]=tot;       
}
int main(){
    int a,b,c;
    priority_queue<node> qu;
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for (int i=1;i<=m;i++){ 
        scanf("%d%d%d",&a,&b,&c);
        add(a,b,c);
        add(b,a,c); 
    }
    for (int i=1;i<=n;i++) f[i]=INF; 
    f[s]=0; 
    qu.push(node{s,f[s]});
    while (!qu.empty()){
        int x=qu.top().id,ptr=last[x];  
        qu.pop();
        if(x==t) break;
        if(vis[x]) continue;
        vis[x]=1;
        while (ptr){ 
            int y=target[ptr]; 
            if (!vis[y]&&f[x]+v[ptr]<f[y]){ 
                f[y]=f[x]+v[ptr];
                qu.push(node{y,f[y]});
            }
            ptr=prev[ptr]; 
        }
    }
    printf("%d\n",f[t]);
    return 0;
}
```

# SPFA

```cpp
//spfa
#include <cstdio>
#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
int const N=100001,INF=1e9;
int tot,n,m,s,t,f[N],
target[N],prev[N],last[N],v[N];
void add(int a, int b, int c){
    target[++tot]=b; 
    prev[tot]=last[a]; 
    last[a]=tot;      
    v[tot]=c;         
}
int main(){
    int a,b,c;
    queue<int> qu;
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for (int i=1;i<=m;i++){ 
        scanf("%d%d%d",&a,&b,&c);
        add(a,b,c);
        add(b,a,c); 
    }
    for (int i=1;i<=n;i++) f[i]=INF; 
    
    f[s]=0; 
    qu.push(s);
    while (qu.size()){
        int x=qu.front(),ptr=last[x];  
        qu.pop();
        while (ptr){ 
            int y=target[ptr]; 
            if (f[x]+v[ptr]<f[y]){ 
                f[y]=f[x]+v[ptr];
                qu.push(y); 
            }
            ptr=prev[ptr]; 
        }
    }
    printf("%d\n",f[t]);
    return 0;
}
```



---

## 作者：lemondinosaur (赞：7)

# 前言
实际上这道题就是一道单源最短路径的题目，当然还是有很多方法的，就比如SPFA,dijkstra(标准，堆优化)等等，然而当我看到dalao线段树的题解的时候，只剩下了Orz，现在就来讲一下我的思路吧！

---
# 思路
这次我依然不走寻常路，用的是dijkstra+zkw线段树优化，这份代码是这周日写的，所以说还是比较神奇的,主要思想就是维护最小值，然而我的思路是这样的，首先先在叶子节点处更新dis的最小值以及dis最小值的位置，具体可以表现在![](https://cdn.luogu.com.cn/upload/pic/43528.png)
时间复杂度大概是$O(n)$的，然后删除该点的时候需要单点修改，在松弛操作完成后还要进行修改，总的来说时间复杂度是$O(n+elogn)$

---
# 代码(25ms不加O2)(还是比较慢的)
```cpp
#include <cstdio>
#include <cctype>
#include <algorithm>
#define rr register
using namespace std;
const int inf=707406378;
struct node{int y,w,next;}e[12501];
int n,m,s,t,bas=1,k=1,ls[2511],w[8201],p[8201],dis[2511];
inline signed iut(){
    rr int ans=0; rr char c=getchar();
    while (!isdigit(c)) c=getchar();
    while (isdigit(c)) ans=(ans<<3)+(ans<<1)+c-48,c=getchar();
    return ans;
}
inline void add(int x,int y,int w){e[++k]=(node){y,w,ls[x]}; ls[x]=k;}
inline void update(int x){
    w[x]=(w[x<<1]<w[x<<1|1])?w[x<<1]:w[x<<1|1];//取左子右子最小值
    p[x]=(w[x<<1]>w[x<<1|1])?p[x<<1|1]:p[x<<1];//实时更新编号
}
signed main(){
    n=iut(); m=iut(); s=iut(); t=iut();
    for (rr int i=1;i<=m;++i){
        rr int x=iut(),y=iut(),w=iut();
        add(x,y,w); add(y,x,w);
    }
    while ((bas<<=1)<n+2);//由于区间修改需要扩张，所以实际上空间要多1位，总之应在2^x>n的范围内
    fill(w+1,w+2+(bas<<1),inf); fill(dis+1,dis+1+n,inf);//全部初始话位一个很大的值
    fill(p+1,p+2+(bas<<1),inf); w[s+bas-1]=dis[s]=0;//那么
    for (rr int i=0;i<n;++i) p[bas+i]=i+1;//输入编号
    for (rr int i=bas-1;i;--i) update(i);//记住bas表示的是当为满二叉树时除最后一层的个数+1，所以说要减掉1
    while (w[1]<inf){//也就是说都没有访问过
        rr int x=p[1],y=p[1]+bas-1; w[y]=inf;
        for (y>>=1;y;y>>=1) update(y);//删除现在的最小点
        for (rr int i=ls[x];i;i=e[i].next)
        if (dis[e[i].y]>dis[x]+e[i].w){//这一段长的挺像SPFA的
            dis[e[i].y]=dis[x]+e[i].w; rr int t=e[i].y+bas-1;
            for (w[t]=dis[e[i].y],t>>=1;t;t>>=1) update(t);//松弛操作后新到达的节点插入zkw线段树中
        }
    }
    return !printf("%d",dis[t]);//输出s到t的距离
}
```

---

## 作者：ytfiqpl (赞：4)

~~好像没人发Python题解~~

~~本人因为NOIP2018没过已AFO，闲着无聊开始学Python~~

核心算法：Dijkstra（裸的完全能过，毕竟是模板题）

开始假设所有点到起始点的距离都是inf（dis[]=inf），然后遍历与起始点连接的所有点，找出e[s][i]最短的然后转移原点到，来一波松弛。

最后输出dis[t]即可。

```python
n,m,s,t=map(int,input().split())
conn=[[99999999999 for i in range(n+2)]for i in range(n+2)]
dis=[99999999999 for i in range(n+2)]
vis=[0 for i in range(n+2)]
for i in range(m):
    a,b,c=map(int,input().split())
    conn[a][b]=conn[b][a]=c
dis[s]=0
for i in range(1,n+1):
    minv=99999999999
    minn=0
    for j in range(1,n+1):
        if vis[j]==0 and dis[j]<=minv:
            minn=j
            minv=dis[j]
    vis[minn]=1
    for j in range(1,n+1):
        if dis[j]>dis[minn]+conn[minn][j]:
            dis[j]=dis[minn]+conn[minn][j]
print(dis[t])

```
注意是Python3 ! ~~Python2的玩家别被带坏了！~~

---

## 作者：_xcc_ (赞：4)

这是标准的最短路径问题。

无向图！无向图！无向图！

重要的事情说三遍！

```cpp
#include<iostream>
#include<cstring>
using namespace std;  
int i,j,k,s,t,n,m,f[2501][2501],c[2501],x,y,z,minn,maxx=10e8;
bool b[2501];
int main()  
{    
    cin>>n>>m>>s>>t;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            f[i][j]=10e7;               //邻接矩阵初始化。
        }
    }
    for(i=1;i<=m;i++)
    {
        cin>>x>>y>>z;
        f[x][y]=z;
        f[y][x]=z;
    }                                  //数据读入邻接矩阵。注意无向图！
      //然后就是标准的Dijkstra最短路径算法了……
    for(i=1;i<=n;i++)
    {
        c[i]=f[s][i];
    }
    memset(b,false,sizeof(b));
    b[s]=true;
    c[s]=0;
    for(i=1;i<=n-1;i++)
    {
        minn=maxx;
        k=0;
        for(j=1;j<=n;j++)
        {
            if((!b[j])&&(c[j]<minn)){
                minn=c[j];
                k=j;
            }
        }
        if(k==0) break;
        b[k]=true;
        for(j=1;j<=n;j++)
        {
            if(c[k]+f[k][j]<c[j]) c[j]=c[k]+f[k][j];
        }
    }
    cout<<c[t];       //输出最小费用
    return 0;  
}
```

---

## 作者：Arcturus1350 (赞：3)

这道题纯属是一个裸的SPFA；

建议先把模板AC之后再做。

[P3371](https://www.luogu.org/problemnew/show/P3371 "P3371")

只需要做一些手脚，就是在加边的时候加一个双向边就好。

然后再第一次加点的时候

[SPFA模板](https://www.luogu.org/blog/suqingnian/dan-yuan-zui-duan-lu-spfa-suan-fa)

看不懂模板的出门左转度娘。

推荐下面一片讲解：

[友链](http://www.360doc.com/content/13/1208/22/14357424\_335569176.shtml)

所以说，直接上代码。

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<queue>
using namespace std;
struct data{
    int v;int next;
    int value;
}edge[500010];//临界链表存变
int cnt;
int alist[10010];
void add(int u,int v,int value)
{
    edge[++cnt].v=v;
    edge[cnt].value=value;
    edge[cnt].next=alist[u];
    alist[u]=cnt;
    return ;
}//加边
queue<int> q;
bool ins[10010];
int d[10010];
void spfa(int x)//跑一边SPFA，原理在上面
{
    d[x]=0;
    q.push(x);
    ins[x]=true;
    while(!q.empty())
    {
        int now=q.front();
        q.pop();ins[now]=false;
        int next=alist[now];
        while(next)
        {
            int v=edge[next].v;
            int value=edge[next].value;
            if(d[v]>d[now]+value)
            {
                d[v]=d[now]+value;
                if(!ins[v])
                {
                    q.push(v);
                    ins[v]=true;
                }
            }
            next=edge[next].next;
        }
    }
    return ;
}
int m,n,s,e;
int main()
{
    scanf("%d%d%d%d",&m,&n,&s,&e);//输入
    for(int i=1;i<=n;i++)
    {
        int u,v,value;
        scanf("%d%d%d",&u,&v,&value);
        add(u,v,value);//加边
        add(v,u,value);//反向边
    }
    for(int i=0;i<=m;i++)
        d[i]=0x3f3f3f3f;//初始化
    spfa(s);//跑SPFA
    printf("%d",d[e]);//输出
    return 0;//程序拜拜
}
```

---

## 作者：Zenurik (赞：2)

~~其实这道题就是SPFA的板子，我这种蒟蒻为什么浪费十几次的提交次数写堆优化的Dijkstra呢~~

本蒟蒻看楼下的大佬们写的题解没有几个堆优化的Dijkstra的，有的也全是对我这种蒟蒻十分不友好的运算符重载......

那本蒟蒻就来发个没有运算符重载的堆优化Dijkstra吧！

(代码丑陋请见谅)

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#define MAXN 10001
#define MAXM 500001

using namespace std;

int dis[MAXN], head[MAXN], edge[MAXM], ver[MAXM], next[MAXM], n, m, tot, s, e;
bool vis[MAXN];//记录访问 
priority_queue<pair<int,int> > heap;
//pair的第一维存储dis的相反数(利用相反数来实现小根堆，从而避免了运算符重载)，第二维存储节点编号 
 
void add_edge(int x, int y, int z) {//数组模拟邻接表 
    ver[++tot] = y, edge[tot] = z, next[tot] = head[x], head[x] = tot;
}

void heap_dijkstra() {//求最短路 
	memset(dis,0x3f,sizeof(dis));
    memset(vis,0,sizeof(vis));
    dis[s] = 0; heap.push(make_pair(0,s));//起始节点最短路为0，编号为s 
    while(heap.size()) {
        int x = heap.top().second;/*取堆顶节点编号*/ heap.pop();
        if(vis[x]) continue;
        vis[x] = 1;
        for(int i = head[x]; i; i = next[i]) {//邻接表遍历 
            int y = ver[i], z = edge[i];
            if(dis[y] > dis[x] + z) {//更新当前最短路 
                dis[y] = dis[x] + z;
                heap.push(make_pair(-dis[y],y));//将新的二元组插入堆 
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> m >> s >> e;
    for(int i = 1; i <= m; i++) {//构建邻接表 
        int x, y, z;
        cin >> x >> y >> z;
        add_edge(x, y, z);
        add_edge(y, x, z);//注意是无向图，插入两次 
    }
    heap_dijkstra();
    cout << dis[e];
    return 0;
}
```

---

## 作者：little_gift (赞：2)

# 单源最短路径，SPFA，就不详细讲解了，带来普通与pb\_ds两个版本 #

**听说这题是某些人的练手题，我就来一发题解(其实这是从某题复制过来的)**

**不过这题的数据范围吓到我了...**



## 这是正常版本 ##





```cpp
#include <bits/stdc++.h> //万能头文件 
using namespace std;
struct Edge
{
    int nxt, to, val;
}a[3125000]; //奇怪的struct 
int fir[5000], d[5000], b[5000];
int n, m, u, v, w, cnt, s, e;
queue < int > q;
int read_int() //快读 
{
    int x, f = 1;
    char ch;
    while (ch = getchar(), ch < 48 || ch > 57)
        if (ch == '-') f = -f;
    x = ch - 48;
    while (ch = getchar(), ch >= 48 && ch <= 57)
        x = x * 10 + ch - 48;
    return x * f;
}
void write_int(int x) //快输(反正我这么叫) 
{  
    if (x == 0)
    {
        putchar('0');
        return;
    }
    int num = 0;
    char c[11];
    while (x)
        c[++num] = x % 10 + 48, x /= 10;
    while (num)
        putchar(c[num--]);
}
int add_edge(int u, int v, int w) //添加一条边 
{
    a[++cnt].to = v;
    a[cnt].val = w;
    a[cnt].nxt = fir[u];
    fir[u] = cnt;
}
int main()
{
    n = read_int();
    m = read_int();
    s = read_int();
    e = read_int();
    for (int i = 1; i <= m; ++i)
    {
        u = read_int();
        v = read_int();
        w = read_int();
        add_edge(u, v, w);
        add_edge(v, u, w); //无向边 
    }
    for (int i = 1; i <= n; ++i)
        d[i] = 0x7fffffff; //maxlongint初始化 
    q.push(s);
    b[s] = 1; //入队 
    d[s] = 0; 
    while (!q.empty()) //如果队列不为空 
    {
        u = q.front();
        q.pop(); //出队
        b[u] = 0; //原来漏了这句，不断80 
        for (int i = fir[u]; i; i = a[i].nxt)
            if (d[u] + a[i].val < d[a[i].to]) //relax条件判断 
            {
                d[a[i].to] = d[u] + a[i].val;
                if (!b[a[i].to]) //入队 
                {
                    q.push(a[i].to);
                    b[a[i].to] = 1;
                }
            }
    }
    write_int(d[e]);
}
```
## 下面是pb\_ds版本(用法基本一样,相同的就不写了) ##



```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp> //pb_ds的priority_queue头文件 
using namespace std;
struct Edge
{
    int nxt, to, val;
}a[3125000];
int fir[5000], d[5000], b[5000];
int n, m, u, v, w, cnt, s, e;
struct comp
{
    __inline__ __attribute((always_inline)) bool operator()(int a, int b)
    {
        return d[a] > d[b];
    }
}; //比较器,用于pb_ds的priority_queue 
__gnu_pbds::priority_queue < int, comp > q; //__gnu_pbds是pb_ds的命名空间
int read_int()
{
    int x, f = 1;
    char ch;
    while (ch = getchar(), ch < 48 || ch > 57)
        if (ch == '-') f = -f;
    x = ch - 48;
    while (ch = getchar(), ch >= 48 && ch <= 57)
        x = x * 10 + ch - 48;
    return x * f;
}
void write_int(int x)  
{  
    if (x == 0)
    {
        putchar('0');
        return;
    }
    int num = 0;
    char c[11];
    while (x)
        c[++num] = x % 10 + 48, x /= 10;
    while (num)
        putchar(c[num--]);
}
int add_edge(int u, int v, int w)
{
    a[++cnt].to = v;
    a[cnt].val = w;
    a[cnt].nxt = fir[u];
    fir[u] = cnt;
}
int main()
{
    n = read_int();
    m = read_int();
    s = read_int();
    e = read_int();
    for (int i = 1; i <= m; ++i)
    {
        u = read_int();
        v = read_int();
        w = read_int();
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    for (int i = 1; i <= n; ++i)
        d[i] = 0x7fffffff;
    q.push(s);
    b[s] = 1;
    d[s] = 0;
    while (!q.empty())
    {
        u = q.top();
        q.pop();
        b[u] = 0;
        for (int i = fir[u]; i; i = a[i].nxt)
            if (d[u] + a[i].val < d[a[i].to])
            {
                d[a[i].to] = d[u] + a[i].val;
                if (!b[a[i].to])
                {
                    q.push(a[i].to);
                    b[a[i].to] = 1;
                }
            }
    }
    write_int(d[e]);
}
```

---

## 作者：richardchen (赞：2)

此题是SPFA算法的模板题，注意无向图边要存2次。

下面介绍两种实现方法，开始：

1.用vector实现邻接表（直接复制粘贴会CE的）

```cpp
#include<cstdio>
#include<vector>
#define inf 0x7F
#define max_point 10000
using namespace std;
int dis[max_point],t,c,ts,te,rs,re,ci,cur;
bool in_queue[max_point];
struct Paris{
    int to,len;//实现邻接表的结构体 
};
vector<Paris>graph[max_point];//邻接表 
queue<int>q;
void addedge(int start,int dest,int length)//加边 
{
    graph[start].push_back((Paris){dest,length});
}
int main()
{
    scanf("%d%d%d%d",&t,&c,&ts,&te);
    for(int i=1;i<=c;i++)
    {
        scanf("%d%d%d",&rs,&re,&ci);
        addedge(rs,re,ci);//无向图加两次！！
        addedge(re,rs,ci);
    }
    memset(dis,inf,sizeof(dis));//初始化 
    dis[ts]=0;
    q.push(ts);//起点入队 
    in_queue[ts]=true;
    while(!q.empty())
    {
        cur=q.front();
        q.pop();
        in_queue[cur]=false;
        for(vector<Paris>::iterator i=graph[cur].begin();i!=graph[cur].end();i++)
```
/\*又长又丑的迭代器遍历\*/
```cpp
        {
            if(dis[cur]+i->len<dis[i->to])
            {
                dis[i->to]=dis[cur]+i->len;//relax 
                if(!in_queue[i->to])
                {
                    q.push(i->to);
                    in_queue[i->to]=true;
                } 
            }
        }
    }
    printf("%d",dis[te]);
    return 0;
}
```
2.链式前向星（这个我也不是特别理解。。。当初看到不少dalao写
链式前向星，我也决定学一下，结果懵了。。。）

```cpp
#include<cstdio>
#include<queue>
#define M 5000
#define Inf 0x3f
using namespace std;
int t,c,ts,te,rs,re,cur,ci,cnt=0,dis[M],head[M];
bool inq[M];
struct Tokyo{
    int to,val,Next;//这个next和head我也不是很理解 
}edge[3125000];
queue<int>q;
void add_edge(int from,int dest,int len)//加边 
{
    edge[++cnt].to=dest;
    edge[cnt].val=len;
    edge[cnt].Next=head[from];
    head[from]=cnt;
}
int main()
{
    scanf("%d%d%d%d",&t,&c,&ts,&te);
    for(int i=1;i<=c;i++)
    {
        scanf("%d%d%d",&rs,&re,&ci);
        add_edge(rs,re,ci);
        add_edge(re,rs,ci);
    }
    for(int i=1;i<=t;i++)
        dis[i]=0x7fffffff;//初始化 
    q.push(ts);//起点入队 
    dis[ts]=0;
    inq[ts]=true;
    while(!q.empty())
    {
        cur=q.front();
        q.pop();
        inq[cur]=false;
        for(int i=head[cur];i;i=edge[i].Next)
        {
            if(dis[cur]+edge[i].val<dis[edge[i].to])
            {
                dis[edge[i].to]=dis[cur]+edge[i].val;
                if(!inq[edge[i].to]) q.push(edge[i].to),inq[edge[i].to]=true;
            }
        }
    }
    printf("%d",dis[te]);
    return 0;
}
```

---

## 作者：ExBritainia (赞：1)

先膜拜一下大佬们

（蒟蒻Britainia第一次发题解，管理员dalao们请见谅

对于我这个图论渣渣，也就只能发一个Dijkstra+堆优化的题解了w=0=w

首先，这个代码的核心部分

```cpp
int v=e[i].v,w=e[i].w;
if(d[u]+w<d[v]){
     d[v]=d[u]+w;
     q.push((node){v,d[v]});
}
```
其实就是从起点到一个点的最短路+这个点到其一个相邻的点的距离如果小于这个点现在的最短路则更新，入队。

具体操作请看代码

```cpp
#include <bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
    int X=0,w=1; char c=getchar();
    while (c<'0'||c>'9') { if (c=='-') w=-1; c=getchar(); }
    while (c>='0'&&c<='9') X=(X<<3)+(X<<1)+c-'0',c=getchar();
    return X*w;
}
struct Edge { int v,w,nxt;};Edge e[500010];int head[100010],cnt=0;
inline void addEdge(int u,int v,int w) {
    e[++cnt].v=v;e[cnt].w=w;
    e[cnt].nxt=head[u];head[u]=cnt;
}
int n,m,s1,s2;int d[100010];
struct node {
    int u,d;
    bool operator <(const node& rhs) const {
        return d>rhs.d;//因为是优先队列所以要重载 
    }
};
inline void Dijkstra() {
    for (re int i=1;i<=n;i++) d[i]=2147483647;
    d[s1]=0;priority_queue<node> q;q.push((node){s1,0});//优先队列 
    while (!q.empty()) {
        node fr=q.top(); q.pop();int u=fr.u,di=fr.d;if (di!=d[u]) continue;
        for (re int i=head[u];i;i=e[i].nxt) {
            int v=e[i].v,w=e[i].w;
            if(d[u]+w<d[v]){
                d[v]=d[u]+w;q.push((node){v,d[v]});
            }
        }
    }
}

int main() {
    n=read(),m=read(),s1=read(),s2=read();
    for (re int i=1;i<=m;i++) {
        int x=read(),y=read(),z=read();
        addEdge(x,y,z);addEdge(y,x,z);//存边 
    }
    Dijkstra();printf("%d\n",d[s2]);
    return 0;
}
```
好啦，这就是正解啦


------------

下面来一篇纯属娱乐的非正解。

最近走在路上突发奇想说kruskal+dfs可不可以做最短路。

（几秒之内就被否决掉了

当然我还是写了这样一个代码，结果

# 60pts!!!

评测记录：

https://www.luogu.org/recordnew/show/19190157

```cpp
#include<bits/stdc++.h>
using namespace std;
struct Edge{int u,v,w;}edge[500005];bool f[10005];
int n,m,s1,s2,fa[10005],cnt,d[10005];
vector<pair<int,int> > g[10005];
bool cmp(Edge x,Edge y){return x.w<y.w;}
int find(int x){while(x!=fa[x]) x=fa[x]=fa[fa[x]];return x;}
void dfs(int x,int d){
	f[x]=1;for(int i=0;i<g[x].size();i++){
		if(f[g[x][i].first]) continue;
        f[g[x][i].first]=1;
		d[g[x][i].first]=g[x][i].second+d;
        dfs(g[x][i].first,g[x][i].second+d);
	}
}
int main( ){
	cin>>n>>m>>s1>>s2;for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=m;i++) cin>>edge[i].u>>edge[i].v>>edge[i].w;
	sort(edge+1,edge+1+m,cmp);
        int eu,ev;memset(f,0,sizeof(f)); 
	for(int i=1;i<=m;i++){
		eu=find(edge[i].u);ev=find(edge[i].v);
		if(eu==ev) continue;fa[eu]=ev;cnt++;
		g[edge[i].u].push_back(make_pair(edge[i].v,edge[i].w));
		g[edge[i].v].push_back(make_pair(edge[i].u,edge[i].w));
		if(cnt==n-1) break;
	}
	dfs(s1,0);cout<<d[s2]<<endl;return 0;
}
```



---

## 作者：skyipeng (赞：1)

本菜鸟参考《挑战程序设计》上的经典代码写的模版，包括dijkstra、bellmanFord、spfa。实测都在50MS以内，分享给大家。神牛勿喷。




```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> P;
const int N = 2505;
int head[N], cnt;
struct road{
    int to, nxt, val;
}e[12405];
struct edge{
    int from, to, val;
}edges[12405];
void add(int a, int b, int v){
    cnt++;
    e[cnt].to = b;
    e[cnt].nxt = head[a];
    e[cnt].val = v;
    head[a] = cnt;
}
int d[N], INF = 0x3f3f3f3f;
int dijkstra(int a, int b)
{
    priority_queue<P, vector<P>, greater<P> > que;
    memset(d, INF, sizeof(d));
    d[a] = 0;
    que.push(P(0, a));
    while(!que.empty()){
        P p = que.top();
        que.pop();
        if(d[p.second] < p.first) continue;
        for(int i = head[p.second]; i != 0; i = e[i].nxt){
            if(e[i].val + p.first < d[e[i].to])
            {
                d[e[i].to] = e[i].val + p.first;
                que.push(P(d[e[i].to], e[i].to));
            }
        }
    }
    return d[b];
}
int C;
int bellmanFord(int a, int b)
{
    memset(d, INF, sizeof(d));
    d[a] = 0;
    while(true){
        bool update = false;
        for(int i = 0; i < 2 * C; i++)
        {
            if(d[edges[i].from] + edges[i].val < d[edges[i].to])
            {
                d[edges[i].to] = d[edges[i].from] + edges[i].val;
                update = true;
            }
        }
        if(!update) break;
    }
    return d[b];
}
bool vis[N];
int spfa(int a, int b)
{
    memset(d, INF, sizeof(d));
    memset(vis, 0, sizeof(vis));
    queue<int> que;
    que.push(a);
    d[a] = 0;
    vis[a] = true;
    while(!que.empty()){
        int u = que.front();
        que.pop();
        vis[u] = false;
        for(int i = head[u]; i != 0; i = e[i].nxt){
            if(d[u] + e[i].val < d[e[i].to]){
                d[e[i].to] = d[u] + e[i].val;
                if(!vis[e[i].to]){
                    vis[e[i].to] = true;
                    que.push(e[i].to);
                }
            }
        }
    }
    return d[b];
}
int main()
{
    int T, Ts, Te;
    cin>>T>>C>>Ts>>Te;
    for(int i = 0; i < C; i++){
        int s, e, v;
        cin>>s>>e>>v;
        add(s, e, v);
        add(e, s, v);
        edges[2 * i].from = s;
        edges[2 * i].to = e;
        edges[2 * i].val = v;
        edges[2 * i + 1].from = e;
        edges[2 * i + 1].to = s;
        edges[2 * i + 1].val = v;
    }
    //cout<<dijkstra(Ts, Te)<<endl;
    //cout<<bellmanFord(Ts, Te)<<endl;
    cout<<spfa(Ts, Te)<<endl;
    return 0;
}
```


---

## 作者：cccly (赞：1)

最短路！最短路！最短路！重要的事情说三遍！

先讲解一下输入数据：

7 11 5 4 //t个城镇, c条道路, Ts（起点）, Te（终点）

2 4 2 //城镇rs到城镇re费用ci。

1 4 3
7 2 2
3 4 3
5 7 5
7 3 3
6 1 1
6 3 4
2 4 3
5 6 3
7 2 1
输出数据：

7 //5->6->1->4 (3 + 1 + 3)

解题思路是：

首先要初始定义所有数组&结构体（简单的不用说了吧），

然后从ts开始bfs一下，更新每个点最短的路最后输出te，2333就AC啦！


代码如下：


```cpp
    #include<cstdio>
    #include<cstring>
    int a[6500],b[6500];
    bool c[6500];
    int u[20005],v[20005],w[20005],nst[20005];
    int dl[10001];
    int n,m,s,e,len=0;
    int main()
    {
        int i,j;
        scanf("%d%d%d%d",&n,&m,&s,&e);
        for(i=1;i<=m;i++)
        {
            len++;
            scanf("%d%d%d",&u[len],&v[len],&w[len]);
            nst[len]=b[u[len]];
            b[u[len]]=len;
            len++;
            u[len]=v[len-1],v[len]=u[len-1],w[len]=w[len-1];
            nst[len]=b[u[len]];
            b[u[len]]=len;
        }
        for(i=1;i<=n;i++) a[i]=999999999;
        dl[1]=s; c[s]=1; a[s]=0;
        int h=0,t=1;
        while(h!=t)
        {
            h++;
            if(h>10000) h=1;
            for(int k=b[dl[h]];k;k=nst[k])
            {
                if(a[v[k]]>a[u[k]]+w[k])
                {
                    a[v[k]]=a[u[k]]+w[k];
                    if(!c[v[k]])
                    {
                        t++;
                        if(t>10000) t=1;
                        dl[t]=v[k];
                        c[v[k]]=1;
                    }
                }
            }
            c[dl[h]]=0;
        }
        printf("%d\n",a[e]);
        return 0;
}
```

---

## 作者：qq924675986 (赞：1)

好久没写图论了， 看到这题吐了， 注意是无向图。。。 看到这数据再吐了一遍。。。还是贴上我丑陋的spfa代码吧。。。

```cpp
    #include <cstdio>  
    #include <cstdlib>  
    #include <queue>  
    #include <vector>  
    #include <iostream>  
    #define MAXE 6210  
    #define MAXN 2510  
    const int INF = ~0U>>1;  
    using namespace std;  
    struct Edge{  
        int w, to;  
    };  
    int d[MAXN],vis[MAXN];  
    vector <Edge> E;  
    vector <int> N[MAXN];  
    void Add(int from, int to, int w){  
        E.push_back((Edge){w, to});  
        N[from].push_back(E.size()-1);  
    }  
    queue <int> q;  
    int n;  
    int spfa(int st, int en){  
        for(int i=1; i<=n; i++) d[i] = (i == st) ? 0 : INF;  
        vis[st] = 1;  
        q.push(st);  
        while(!q.empty()){  
            int t = q.front();  
            //cout << t << endl;  
            q.pop();  
            vis[t] = 0;  
            for(int i=0; i<=N[t].size()-1; i++){  
                if(d[E[N[t][i]].to] > d[t] + E[N[t][i]].w){  
                    d[E[N[t][i]].to] = d[t] + E[N[t][i]].w;  
                    if(!vis[E[N[t][i]].to]){  
                        vis[E[N[t][i]].to] = 1;  
                        q.push(E[N[t][i]].to);  
                    }  
                }  
            }  
        }  
        return d[en];  
    }  
    int main(){  
        int m, st, en;  
        scanf("%d%d%d%d", &n, &m, &st, &en);  
        for(int i=1; i<=m; i++){  
            int x, y, z;  
            scanf("%d%d%d", &x, &y, &z);  
            Add(x, y, z);  
            Add(y, x, z);  
        }  
        printf("%d\n", spfa(st, en));  
        return 0;  
}
```

---

## 作者：R_a_v_e_n (赞：1)

作为一个追求极致效率的人，发一个最长用时8ms的dijkstra代码

我的说明不是怎么用dijkstra，而是怎么优化，不知道dijkstra什么原理的主动楼下寻找或者问度娘

思路很简单，用一个struct存每条边的信息，起点（这个其实可以不要），终点和长度，再用一个vector[i]存以第i个点为起点的边的编号，这样可以减少搜索邻接矩阵的时间，对稀疏图还是挺实用的；

在然后用pair存起点到每个点的距离（用pair比struct方便，因为它自带排序方式，不用自己定义，可以直接扔进优先队列里），pair[i].first存距离，初始为infinite，pair[i].second存点的编号，就是i（哈？再存一遍i有什么用？这自然是有用的了。还有一定要把距离存在.first里，不然排序要出拐），起点初始化后就全部塞到priority-queue（记得改排序方式）里；

找到优先队列的top就可以通过.second找到距离最近的点，做标记后弹掉，更新pair后直接把新pair压进优先队列中，不用管之前同一个点已经压进去的距离（因为优先队列没有办法更新里面的数据，反正一个点新压进去的距离肯定比旧的短，而且因为做了标记，在优先队列队首找到已经找过的点直接弹掉就好了），找到终点后结束就行了。

下面是代码（题目数据范围有毒，害我Re了两次）

···
```cpp
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cstdio>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
const int infinite=1<<30;
int t,c,s,e;
int x,y,z,p,q;
struct edge
{
    int start,finish,lenth;
}way[100000];
bool a=true,b[100000];
pair<int,int> dis[100000];
vector<int> point[100000];
priority_queue<pair<int,int>,vector< pair<int,int> >,greater< pair<int,int> > > k;
int main()
{
    cin>>t>>c>>s>>e;
    for(int i=0;i<c;i++)
    {
        p=2*i,q=2*i+1;
        cin>>way[p].start>>way[p].finish>>way[p].lenth;
        way[q].start=way[p].finish;
        way[q].finish=way[p].start;
        way[q].lenth=way[p].lenth;
        point[way[p].start].push_back(p);
        point[way[q].start].push_back(q);
    }
    for(int i=1;i<=t;i++)
    {
        dis[i].first=infinite;
        dis[i].second=i;
        k.push(dis[i]);
    }
    dis[s].first=0;
    k.push(dis[s]);
    while(!b[e])
    {
        ///a=true;
        while(/*a*/true)
        {
            x=k.top().second;
            if(b[x])
            {
                k.pop();
            }
            else
            {
                k.pop();
                b[x]=true;
                /*a=false*/break;
            }
        }
        for(int i=point[x].size()-1;i>=0;i--)
        {
            if(!b[way[point[x][i]].finish]&&dis[way[point[x][i]].finish].first>dis[x].first+way[point[x][i]].lenth)
            {
                dis[way[point[x][i]].finish].first=dis[x].first+way[point[x][i]].lenth;
                k.push(dis[way[point[x][i]].finish]);
            }
        }
    }
    cout<<dis[e].first;
}
···
```

---

## 作者：转身、已陌路 (赞：1)

这道题是一个纯裸的迪杰斯特拉算法  就是读入到时候你要判断一下如果重复的时候要保留下那个最小的

不多说了  直接上代码：



```cpp
#include<bits/stdc++.h>
using namespace std;
int a[2510][2510];
int d[2510];
bool f[2510];
int t,c,ts,te;
void dijkstra(int st)//迪杰斯特拉算法   纯裸的 
{
    for (int i=1;i<=t;i++)  d[i]=a[st][i];
    memset(f,false,sizeof(f));
    f[st]=true;d[st]=0;
    for (int i=1;i<=t;i++)
    {
        int min=1000000000,k=0;
        for (int j=1;j<=t;j++)
        if ((!f[j])&&(d[j]<min)) 
        {min=d[j];k=j;}//找到目前集合2的最短距离 
        if (k==0)  return; // 已经找不到了 
        f[k]=true; //转到集合一 
        for (int j=1;j<=t;j++) //三角形迭代更新 最短距离 
           { if ((!f[j])&&(d[k]+a[k][j]<d[j]))   
             d[j]=d[k]+a[k][j];     }
    }
}
int main()
{
    cin>>t>>c>>ts>>te;
    int x,y,z;
    memset(a,10,sizeof(a));
    for (int i=1;i<=c;i++)
    {
        cin>>x>>y>>z;
        if (a[x][y]&&a[x][y]>z) {a[x][y]=z;a[y][x]=z;}//判断重复的情况 
        if (!a[x][y]) {a[x][y]=z;a[y][x]=z;}
    }
dijkstra(ts);//起点 
cout<<d[te];//终点 
    return 0;
}
```

---

## 作者：二元长天笑 (赞：1)

这道题，天笑第一眼看上去就是一个模板的最短路，然后高兴的用Floyed打了一遍，结果发现数据过大，一下就爆了。于是天笑就用了**迪杰斯科拉**，虽然用这个算法的题解很多，但是在这里天笑要给大家介绍一个非常好用的东西，特别是这种输入数据特别多的题目，就可以用到这个**读入优化**，天笑亲身试验过，它的的效率比**cin**和**scanf**都要快，原理就是字符串的操作，具体附上代码：

```cpp
inline int get() 
{ 
    int a=0; 
    char s=getchar(); 
    while(s<'0'||s>'9') 
        s=getchar(); 
    while(s>='0'&&s<='9') 
        a=(a<<3)+(a<<1)+(s^'0'),s=getchar(); 
    return a; 
}
```
接着就回归本题吧，这道题因为数据很大，用Floyed时间复杂度O（N^3）肯定爆炸，又因为这道题只需要求单源最短路径，于是乎，用迪杰斯科拉或bellman-ford或SPFA都是不错的选择，于是我选择了迪杰斯科拉，附上代码：

```cpp
#include<iostream> 
#include<cstring> 
using namespace std; 
int t,c,ts,te,f[2501][2501],a[2501],minn,rs,re,ci; 
bool b[2501]; 
inline int get()   //读入优化
{ 
    int a=0; 
    char s=getchar(); 
    while(s<'0'||s>'9') 
        s=getchar(); 
    while(s>='0'&&s<='9') 
        a=(a<<3)+(a<<1)+(s^'0'),s=getchar(); 
    return a; 
}
int main() 
{ 
    t=get(),c=get(),ts=get(),te=get();
    memset(f,0x7f,sizeof(f));   //memset 最大只能赋到0x7f，也就是255这个样子，再大的话就会变成一个巨小的数
    for(int i=1;i<=c;i++) 
    { 
            rs=get(),re=get();
        f[rs][re]=f[re][rs]=get(); 
    } 
    for(int i=1;i<=t;i++) 
        a[i]=f[ts][i]; 
    memset(b,false,sizeof(b)); 
    b[ts]=true,a[ts]=0; 
    for(int i=1,k=0;i<t;i++) //迪杰斯科拉
    {
        minn=0x7f;
        for(int j=1;j<=t;j++)
            if(!b[j]&&a[j]<minn)
            {
                minn=a[j];
                k=j;
            }
        if(k==0)
            break;
        b[k]=true; 
        for(int j=1;j<=t;j++) 
            if(a[k]+f[k][j]<a[j]) 
                a[j]=a[k]+f[k][j]; 
    } 
    cout<<a[te]<<endl; 
} 
```

---

## 作者：Lee02 (赞：0)

## ~~Dijkstra~~DJ算法+队优化

我是在学完DJ算法后才来的：[DJ大法好！](https://www.luogu.org/problem/P4779)

### 如果没有学过DJ的话，可以大概看一下DJ（堆优化版）的过程
1.**初始化**：dis全设为无穷远，之后dis[ts]=0,vis全为0;

2.**输入**：使用邻接表进行存边操作（如果不懂邻接表的请自行百度）

3.**DJ**：

   **3.1** 取队首：然后依次遍历与它相连的点，然后松弛（将这些点的距离最小值更新），并将未曾vis的点加入队中
   
   **循环操作**直至队列空

第一眼看到这道题之后，第一反应：这就是道DJ的模板题。但是定睛一看，这个图它是**无向图**！！！

在愣了1s后，想到，不过就是把建**边过程再来一次吗**...

然后，就没有然后了...

上代码！

```cpp
#include<bits/stdc++.h>
#define maxn 100010
#define maxm 500010 //当你看到这个最大值后你就会知道，我真的是把代码复制过来的...
using namespace std;
inline int read()
{
	int x=0;char ch=getchar();
	while(ch>'9'||ch<'0') ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-48,ch=getchar();
	return x;
}//快读保平安

struct Edge{
	int to,next,dis;
}edge[maxm];//邻接表存边
struct node{
	int dis,pos;
	bool operator < (const node &x)const
	{
		return x.dis<dis;
	}
};//存点
priority_queue<node> q;//堆优化
int n,m,s,cnt=0,t;
int dis[maxn],vis[maxn],head[maxn];

void add_edge(int u,int v,int d)
{
	edge[++cnt].to=v;
	edge[cnt].dis=d;
	edge[cnt].next=head[u];
	head[u]=cnt;
}
void dj()
{
	dis[s]=0;
	q.push((node){0,s});
	while(!q.empty())
	{
		node tmp=q.top();
		q.pop();
		int x=tmp.pos,d=tmp.dis;
		if(vis[x]) continue;
		vis[x]=1;
		for(int i=head[x];i;i=edge[i].next)
		{
			int y=edge[i].to;
			if(dis[y]>dis[x]+edge[i].dis)
			{
				dis[y]=dis[x]+edge[i].dis;
				if(!vis[y])
				q.push((node){dis[y],y});
			}
		}
	}
}//DJ过程，完 全 一 致
int main ()
{
	n=read();m=read();s=read();t=read();
	for(int i=1;i<=n;i++) dis[i]=0x7fffffff;//初始化为无穷远
	for(int i=1;i<=m;i++)
	{
		int frm=read(),to=read(),dis=read();
		add_edge(frm,to,dis);
		add_edge(to,frm,dis);//两次建边即可
	}
	dj();
	cout<<dis[t]<<endl;//输出最终距离
	return 0;
}
```


---

## 作者：从不再见 (赞：0)

#### 本蒟蒻好不容易学到dijkstra，出来冒冒泡。
这个题相对于最短路来说就是一个 _板子题_，直接套模板A掉这题，由于该题比较简单，我也就不再赘述，上**代码** 。
```
//本来写的是原版的dijkstra，但是有点手痒，用上了堆优化。 
#include<bits/stdc++.h>
using namespace std;
int n,m,s,e,dis[2510],vertex[2510][2510];//dis[i]表示原点到点i的最短距离，vertex[i][j]表示从i到j的距离 
vector<int> nb[2510];//邻居数，相当于谁与谁是连通的 
struct node{	// 自定义优先队列 
	int id;
	int dirt;
	bool operator<(const node &next) const{
		return dirt>next.dirt;
	}
};
void dijkstra(int start){	//dijkstra优化后算法 
	priority_queue<node> pq;
	for(int i=1;i<=n;i++){//初始化 
		dis[i]=1e9;
	}
	dis[start]=0;
	node cur;	//将初始点入队 
	cur.id=start;
	cur.dirt=dis[start];
	pq.push(cur);
	while(!pq.empty()){	//仿dijkstra，队首就是距离原点最近的点 
		int u=pq.top().id;//取出队首 
		pq.pop();//弹出 
		for(int i=0;i<=nb[u].size()-1;i++){		//循环与自己相邻的点，松弛dis数组 
			int v=nb[u][i];
			if(dis[u]+vertex[u][v]<dis[v]){	//将有可能成为最近点的点入队 
				dis[v]=dis[u]+vertex[u][v];
				node next;
				next.id=v;
				next.dirt=dis[v];
				pq.push(next);
			}
		}
	}
}
int main()
{
	cin>>n>>m>>s>>e;//n个点，m条边，s为起点，e为终点 
	for(int i=1;i<=m;i++){
		int a,b,c;
		cin>>a>>b>>c;
		vertex[a][b]=vertex[b][a]=c;
		nb[a].push_back(b);//表示a与b连通 
		nb[b].push_back(a);
	}
	dijkstra(s);
	cout<<dis[e];//输出结果 
	return 0;
}

```
望大家都能明白，早点A掉这题

---

## 作者：localhost (赞：0)

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define ll int
#define mx 2501
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
#define fur(i,x,y) for(i=x;i<=y;i++)
#define fdr(i,x,y) for(i=x;i>=y;i--)
#define Fur(i,x,y) for(ll i=x;i<=y;i++)
#define Fdr(x,y) for(ll i=x;i>=y;i--)
#define in2(x,y) in(x);in(y)
#define in3(x,y,z) in2(x,y);in(z)
#define in4(a,b,c,d) in2(a,b);in2(c,d)
#define clr(x,y) memset(x,y,sizeof(x))
using namespace std;
inline void in(ll &x){x=0;char c;bool f=0;while((c=getchar())>'9'||c<'0')if(c=='-')f=!f;x=c-48;while((c=getchar())<='9'&&c>='0')x=x*10+c-48;if(f)x=-x;}
inline void out(ll x){if(x<0){putchar('-');x=-x;}if(x>9)out(x/10);putchar(x%10+48);}
inline void outn(ll x){out(x);printf("\n");}
struct edge{ll nxt,to,w;}e[12401];//注意：要定义边数的两遍，因为这是无向图，一条无向边相当于两条有向边
ll n,m,s,end,cnt=1;
ll head[mx],d[mx],q[mx*2];//队列要定大一点，负责可能re
bool v[mx];//记录某个点有没有在队列里
inline void add(ll x,ll y,ll w){e[cnt].to=y;e[cnt].w=w;e[cnt].nxt=head[x];head[x]=cnt++;}//邻接表
inline ll spfa(){//核心
    ll h=0,t=1,x,y,i;
    fur(i,1,n)d[i]=2333333;//初始化
    q[h]=s;d[s]=0;v[s]=1;
    while(h<t){
        x=q[h++];v[x]=0;
        for(i=head[x];i;i=e[i].nxt){
            y=e[i].to;
            if(d[x]+e[i].w<d[y]){
                d[y]=d[x]+e[i].w;
                if(!v[y]){q[t++]=y;v[y]=1;}
            }
        }
    }
    return d[end];
}
int main(){
    in4(n,m,s,end);//读入点数，边数，起点，终点
    ll x,y,w;
    Fur(i,1,m){in3(x,y,w);add(x,y,w);add(y,x,w);}//构图
    outn(spfa());//spfa(核心)
}
```
/\*

\*/



---

## 作者：Lohetion (赞：0)

最短路径的板子题。

之前都是写SPFA，最近听说被卡的很厉害，决定写写dijkstra的板子；

显然是要用堆优化的。

但手写堆比较麻烦，而且考虑到今年noip可能开O2；

所以用优先队列来代替。

对于每一个加入队列的节点，我们考虑用pair来存。

当然写结构体也可以，但是pair可以更加的方便。




```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int ,int > pa;
int tot=0,n,m,ts,te,fir[5000],dis[5000];
struct Edge{
    int u,v,nxt,w;
}e[100000];
void addedge(int x,int y,int w)
{
    e[++tot].u=x;
    e[tot].v=y;
    e[tot].w=w;
    e[tot].nxt=fir[x];
    fir[x]=tot;
}
void dijkstra()
{
    priority_queue<pa,vector<pa >,greater<pa> >     q;
    q.push(make_pair(ts,0));
    for(int i=1;i<=n;i++)
      dis[i]=100001938;
    dis[ts]=0;  
    while(!q.empty())
    {
        int now=q.top().first;
        int val=q.top().second;
        q.pop();
        for(int i=fir[now];i;i=e[i].nxt)
        {
            int to=e[i].v;
            if(dis[to]>val+e[i].w)
            {
                dis[to]=val+e[i].w;
                q.push(make_pair(to,dis[to]));
            }
        }
    }
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&ts,&te);
    int x,y,w;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&x,&y,&w);
        addedge(x,y,w);
        addedge(y,x,w);
    }
    dijkstra();
    printf("%d",dis[te]);
    return 0;
}
```

---

## 作者：晓曦315 (赞：0)

这道图论，首先是无向图，我用了邻接矩阵存储，然后还要考虑权值覆盖的问题，因为它输入的时候除了起点和终点外地每个城镇由两条双向道路连向至少两个其它地城镇，可能有多个权值。然后我用了dijkstra算法求最短路就ok了。floyed会超时。


```cpp
#include<bits/stdc++.h>
using namespace std;
int t,c,tc,te,x,y,z,a[2505][2505],d[2505];
void dijkstra(int st)
{
    bool b[2505]={};
    for (int i=1;i<=t;++i)
    d[i]=a[st][i];
    b[st]=true;
    d[st]=0;
    for (int i=1;i<=t-1;++i)
    {
        int min_=2000000000,k=0;
        for (int j=1;j<=t;++j)
        if ((!b[j])&&d[j]<min_)
        {
            min_=d[j];
            k=j;
        }
        if (k==0) return;
        b[k]=true;
        for (int j=1;j<=t;++j)
        if ((!b[j])&&d[k]+a[k][j]<d[j]) d[j]=d[k]+a[k][j];
    }
}//dijkstra算法 
int main()
{
    cin>>t>>c>>tc>>te;
    memset(a,10,sizeof(a));//a数组初始一个很大的值 
    for (int i=1;i<=c;++i)
    {
        cin>>x>>y>>z;
        a[x][y]=min(a[x][y],z);
        a[y][x]=min(a[y][x],z);//这两句是要考虑权值覆盖的问题 
    }
    dijkstra(tc);//起点 
    cout<<d[te];//终点 
    return 0;
}
```

---

## 作者：panzheng1999 (赞：0)

嗯。。。反正就是个dijkstra的模板题，我就写个堆优化吧（虽然看这个样子不优化也能过），嘛，也就多几行，又快有好懂，为什么不写呢（STL吼啊）

直接看吧233







```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;
long long int dist[5010];
int  T,C,Ts,Te;
struct stu
{
    int to;
    int dis;
    friend bool operator <(const stu& a,const stu& b)
    {
        return a.dis>b.dis;//一个反向的优先队列（叫大♂根堆还是小根堆来着）
    }
};
priority_queue <stu> q;//写作（优先）队列其名为（忘啦什嘛）堆
vector <stu> v[5010];
void add(int x,int y,int c)
{
    stu temp;
    temp.to=y;
    temp.dis=c;
    v[x].push_back(temp);
}
bool vis[5010];
void dijkstra()
{
    memset(vis,true,sizeof(vis));
    dist[Ts]=0;
    for(int i=0;i<v[Ts].size();i++)//这里其实可以只放一个Ts到Ts距离为零的。。。
    {
        q.push(v[Ts][i]);
    }
    stu temp;
    while(!q.empty())
    {
        temp=q.top();
        q.pop();
        if(vis[temp.to]==false) continue;
        vis[temp.to]=false;
        dist[temp.to]=temp.dis;//最顶部的一定是最优解,看下面一行注释就明白了
        for(int i=0;i<v[temp.to].size();i++)
        {
            stu ex_temp=v[temp.to][i];
            if(vis[ex_temp.to]==true)
            {                                                                         
                ex_temp.dis+=temp.dis;//最优加当前等于经过此路径的最优解（大概就是这个意思)
                q.push(ex_temp);
            }
        }
    }
}
int main()
{
    cin>>T>>C>>Ts>>Te;
    int x,y,c;
    for(int i=1;i<=C;i++)
    {
        cin>>x>>y>>c;
        add(x,y,c);//注意这里是双向边哦_ ;)
        add(y,x,c);//注意这里是双向边哦_ ;)
    }
    dijkstra();
    cout<<dist[Te]<<endl;
    return 0;
}
priority_queue <stu> q;
vector <stu> v[5010];
void add(int x,int y,int c)
{
    stu temp;
    temp.to=y;
    temp.dis=c;
    v[x].push_back(temp);
}
bool vis[5010];
void dijkstra()
{
    memset(vis,true,sizeof(vis));
    dist[Ts]=0;
    for(int i=0;i<v[Ts].size();i++)
    {
        q.push(v[Ts][i]);
    }
    stu temp;
    while(!q.empty())
    {
        temp=q.top();
        q.pop();
        if(vis[temp.to]==false) continue;
        vis[temp.to]=false;
        dist[temp.to]=temp.dis;
        for(int i=0;i<v[temp.to].size();i++)
        {
            stu ex_temp=v[temp.to][i];
            if(vis[ex_temp.to]==true)
            {
                ex_temp.dis+=temp.dis;
                q.push(ex_temp);
            }
        }
    }
}
int main()
{
    cin>>T>>C>>Ts>>Te;
    int x,y,c;
    for(int i=1;i<=C;i++)
    {
        cin>>x>>y>>c;
        add(x,y,c);
        add(y,x,c);
    }
    dijkstra();
    cout<<dist[Te]<<endl;
    return 0;
}
```

---

## 作者：ForwarDer (赞：0)

稀罕产品：\_STL邻接表的SPFA\_。

程序中SPFA函数有较为详细的注释，可以与数组模拟链式比较。

所有点都是**0ms**它有力地证明了**vector并不慢**。


这题本身：

可以说是没有思维复杂度，最短距离模板题。

存图->求最短距离->输出到指定点最短距离

就是这么简单。


附上带注释的c++代码。




```cpp
#include <bits/stdc++.h>
#define MAXV 2505
#define INF 0x3fffffff
using namespace std;
struct Node
{
    int v ,w;
    Node() {}
    Node(int _v ,int _w) : v(_v) ,w(_w) {}          //这种储存方式可以简便地添加一条边
};
vector<Node> G[MAXV];                            //STL的邻接表
int d[MAXV] ,num[MAXV] ,n ,m ,s ,e ,x ,y ,z;
bool inq[MAXV];
bool spfa(int s);
int main()
{
    scanf("%d%d%d%d" ,&n ,&m ,&s ,&e);
    for(int i=1 ;i<=m ;i++) {
        scanf("%d%d%d" ,&x ,&y ,&z);
        G[x].push_back(Node(y ,z));
        G[y].push_back(Node(x ,z));                        //构建无向图（双向路径）
    }
    if(spfa(s)) printf("%d\n" ,d[e]);                        //输出s->e最短距离
    return 0;
}
bool spfa(int s)
{
    memset(inq ,false ,sizeof(inq));
    memset(num ,0 ,sizeof(num));
    fill(d ,d+MAXV ,INF);
    queue<int> q;
    q.push(s);  inq[s]=true;    num[s]++;                   //首先将源点入队
    d[s]=0;                                             //源点距离设为0
    while(!q.empty()) {
        int u=q.front();    q.pop();    inq[u]=false;             //取出队头顶点等待拓展
        for(int k=0 ;k<G[u].size() ;k++) {
            int v=G[u][k].v ,w=G[u][k].w;
            if(d[u]+w<d[v]) {
                d[v]=d[u]+w;            //看看u->v这条边是否可以优化（称 松弛操作）
                if(!inq[v]) {
                    q.push(v);  inq[v]=true;    num[v]++;   //v不在队列中，则v入队
                    if(num[v]>n-1)  return false;  //判断是否有源点可达负环存在，有，则返回false
                }
            }
        }
    }
    return true;                                          //没有，返回true                           
}
```

---

## 作者：早右昕 (赞：0)

我不知道为何大佬们总说**朴素Dijkstra**会**TLE**,反正我是一遍过了(溜)

Dijk核心语句:

```cpp
int Dijkstra()
{
    for (int i = 1; i <= n; i++) Dist[i] = e[S][i];//将初始值赋予Dist
    Dist[S] = 0, Book[S] = true;//标记Dist[S]为确定值
    int pos = 0, Temp = 1<<30, Kace = n - 1;
    while (Kace--)//最多进行Kace次
    {
        for (int i = 1; i <= n; i++)//找到最小的估计距离值的下标
            if (!Book[i] && Dist[i] < Temp)
                Temp = Dist[i], pos = i;
        if (!pos) break;//没找到(我觉得这句没用)
        Book[pos] = true;//标记为确定值,因为Ta不可能再小了
        for (int j = 1; j <= n; j++)//朴素的松弛操作
            if (Dist[j] > Dist[pos] + e[pos][j])
                Dist[j] = Dist[pos] + e[pos][j];
        Temp = 1 << 30, pos = 0;
    }
    return Dist[T];
}
```
基本上就没有啦,全代码请见 [?](http://www.cnblogs.com/InfoEoR/p/7353539.html)


---

## 作者：刘备 (赞：0)

SPFA模板题，实际上只要把模板拿过来改一下存储和输出就能过

代码如下：

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#define N 2505
#define M 20005
#define INF 0x7f7f7f7f
using namespace std;
int dis[N],fst[N];
bool inq[N];
int u[M],v[M],w[M],nst[M];
int dl[10001];
int n,m,s,e,cnt=0;
//fst、nst为邻接表，u、v、w分别是每一条边的起点、终点、权值，inq标记点是否在队列中
int main()
{
    int i,j;
    scanf("%d%d%d%d",&n,&m,&s,&e);
    for(i=1;i<=m;i++) //双向存储
    {
        cnt++;
        scanf("%d%d%d",&u[cnt],&v[cnt],&w[cnt]);
        nst[cnt]=fst[u[cnt]];
        fst[u[cnt]]=cnt;
        cnt++;
        u[cnt]=v[cnt-1],v[cnt]=u[cnt-1],w[cnt]=w[cnt-1];
        nst[cnt]=fst[u[cnt]];
        fst[u[cnt]]=cnt;
    }
    for(i=1;i<=n;i++) dis[i]=INF;
    dl[1]=s; inq[s]=1; dis[s]=0;
    int h=0,t=1;
    while(h!=t)//SPFA
    {
        h++;
        if(h>10000) h=1;
        for(int k=fst[dl[h]];k;k=nst[k])
        {
            if(dis[v[k]]>dis[u[k]]+w[k])
            {
                dis[v[k]]=dis[u[k]]+w[k];
                if(!inq[v[k]])
                {
                    t++;
                    if(t>10000) t=1;
                    dl[t]=v[k];
                    inq[v[k]]=1;
                }
            }
        }
        inq[dl[h]]=0;
    }
    printf("%d\n",dis[e]);
    return 0;
}
```

---

## 作者：jiaangk (赞：0)

其实写一个heap太慢了，所以用优先队列来跑一个Dijkstra，效率爆炸

```cpp
#include<cstdio>
#include<queue>
#include<algorithm> 
using namespace std;
typedef pair<int,int> P;//pair有两个元素，一个是.first,一个是.second可以储存两个元素，这里用来储存点的标号和路径长度
int n,m,u[100000],v[100000],w[100000],f[250000],nnext[250000],d[120000]; 
void dijkstra(int s)
{
    priority_queue<P,vector<P>,greater<P> > q;
    fill(d,d+n+1,0x3f3f3f3f);
    d[s]=0;
    q.push(P(0,s));
    while(!q.empty())
    {
        P p=q.top(); q.pop();
        int vv=p.second;
        if(d[vv]<p.first) continue;//如果优先队列记录的比当前的大那肯定不会得到更小的路径
        for(int i=f[vv];i!=0;i=nnext[i])
        {
            if(d[v[i]]>p.first+w[i])
            {
                d[v[i]]=p.first+w[i];
                q.push(P(d[v[i]],v[i]));
            }
        }
    }
}
int main()
{
    int k,b;
    scanf("%d%d%d%d",&n,&m,&k,&b);
    fill(f,f+n+1,0);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&u[i*2],&v[i*2],&w[i*2]);
        u[i*2-1]=v[i*2];
        v[i*2-1]=u[i*2];
        w[i*2-1]=w[i*2];
        nnext[i*2]=f[u[i*2]];
        f[u[i*2]]=i*2;
        nnext[i*2-1]=f[u[i*2-1]];
        f[u[i*2-1]]=i*2-1;
    }
    dijkstra(k);
    printf("%d",d[b]);
    return 0;
}
```

---

## 作者：doby (赞：0)

这里其实可以用SPFA……

Floyd自从我看到数据范围后再也不想用了……

```cpp
#include<cstdio>
#include<cstdlib>
#include<vector>
#include<cstring>
#include<queue>
using namespace std;
typedef vector<int>vec;
vec map[2509],val[2509];
int n,m,s,t,dis[2509],flag[2509],a,b,v,tt,tmp;
queue<int>q;
void init()//输入
{
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&a,&b,&v);
        map[a].push_back(b);
        val[a].push_back(v);
        map[b].push_back(a);
        val[b].push_back(v);
    }
}
void SPFA()//SPFA……
{
    for(int i=1;i<=n;i++){dis[i]=23333333,flag[i]=0;}//初始化
    dis[s]=0,flag[s]=1;
    q.push(s);//第一个点
    while(!q.empty())
    {
        tt=q.front();
        q.pop();
        flag[tt]=0;
        for(int i=0;i<map[tt].size();i++)
        {
            tmp=dis[tt]+val[tt][i];
            if(tmp<dis[map[tt][i]])
            {
                dis[map[tt][i]]=tmp;
                if(!flag[map[tt][i]])
                {
                    q.push(map[tt][i]);
                    flag[map[tt][i]]=1;
                }
            }
        }
    }
    printf("%d",dis[t]);//输出
    return;
}
int main()
{
    init();
    SPFA();
    return 0;
}
```

---

## 作者：小黑 (赞：0)

bellman-ford代码

赤果果的最短路径=\_=注意是无向图就行了


```delphi
const
  inf=6500;
var
  u,v,w:array[1..13000] of integer;
  dis:array[1..2600] of integer;
  t,c,ts,te,rs,re,ci,i:longint;
  f:boolean;
begin
  read(t,c,ts,te);
  for i:=1 to c do
    begin
      read(rs,re,ci);
      u[i]:=rs;v[i]:=re;w[i]:=ci;
      u[i+c]:=re;v[i+c]:=rs;w[i+c]:=ci;
    end;
  
  for i:=1 to t do dis[i]:=inf;
  dis[ts]:=0;
  f:=true;
  while f do
    begin
      f:=false;
      for i:=1 to c*2 do
        if dis[u[i]]+w[i]<dis[v[i]] then
          begin
            f:=true;
            dis[v[i]]:=dis[u[i]]+w[i];
          end;
    end;

  writeln(dis[te]);
end.
```

---

## 作者：gryql (赞：0)

一道极好的用来练最短路的题，给出SPFA算法的标准程序，注释详尽



```delphi

const maxp=10000;//最大节点数

var p,c,s,t:longint;//p:节点数；c:边数；s：起点；t：终点
    a,b:array[1..maxp,0..maxp] of longint;
    //a[x,y]表示x,y边的权；
    //b[x,c]表示与x边相连的第c条边的另一个节点；
    //b[x,0]表示和结点x有多少条边相连；
    d:array[1..maxp] of longint;//队列
    v:array[1..maxp] of boolean;//是否入队标记
    f:array[1..maxp] of longint;//第i个点到起点的最短路
    head,tail:longint;//队尾队首指针

procedure init;
var i,x,y,z:longint;
begin
    read(p,c,s,t);
    for i:=1 to c do
        begin
            readln(x,y,z);//x,y为两个点，z为权值
            inc(b[x,0]);
            b[x,b[x,0]]:=y;
            a[x,y]:=z;
            inc(b[y,0]);
            b[y,b[y,0]]:=x;
            a[y,x]:=z;
        end;
end;

procedure spfa(s:longint);
var i,j,now,sum:longint;
begin
    fillchar(d,sizeof(d),0);
    fillchar(v,sizeof(v),false);
    for i:=1 to p do f[i]:=maxint;
    f[s]:=0;//不要忘了这一句：起点到起点自身的距离为零！
    v[s]:=true;
    d[1]:=s;
    head:=1;
    tail:=1;
    while head<=tail do//队列不空
        begin
            now:=d[head];//取队首元素
            for i:=1 to b[now,0] do//把和对首相连的边全部扫描一遍
                if f[b[now,i]]>f[now]+a[now,b[now,i]] then
//如果和now相连的第i个点（阿尔法点）到起点的最短路还要小于到now节点的最短路与从now结点到阿尔法点的距离则更新
                    begin
                        f[b[now,i]]:=f[now]+a[now,b[now,i]];
                        if not (v[b[now,i]]) then
                            begin
                                inc(tail);
                                d[tail]:=b[now,i];
                                v[b[now,i]]:=true;
                            end;
                    end;
              v[now]:=false;//松弛结点
              inc(head);//出队
        end;
end;

begin
    init;
    spfa(s);
    writeln(f[t]);
end.

```

---

## 作者：jxpxcsh (赞：0)

BELLMAN-FORD算法在这里给出。dijkstra和spfa被用得较广泛，就不贴了。

```delphi

var d:array[1..2500]of longint;
  l:array[1..6200,1..3]of longint;
  st,en,v,e,i,j:longint;
begin
  readln(v,e,st,en);
  for i:=1 to v do d[i]:=9999999;
  d[st]:=0;
  for i:=1 to e do
      readln(l[i,1],l[i,2],l[i,3]);
  for i:=1 to v-1 do
    for j:=1 to e do
      begin
        if(d[l[j,1]]+l[j,3])<d[l[j,2]]then d[l[j,2]]:=d[l[j,1]]+l[j,3];
        if(d[l[j,2]]+l[j,3])<d[l[j,1]]then d[l[j,1]]:=d[l[j,2]]+l[j,3];
      end;//松弛操作
  writeln(d[en]);
  readln;
end.

```

---

## 作者：DaCong (赞：0)

最近在练习SPFA，这道题目刚刚好。

先说一下我被坑掉的点：

1. 这是无向图，所以邻接表要开两倍。

2. 貌似我写得不是很好，在加上读入优化前会 TLE 最后一个点。我估计如果我的队列实现用数组写，反而会快一点（上次一道题目用了 map 被

TLE 了两个点）。

下面是代码，请不要直接复制。


```cpp
#include <cstdio>
#include <queue>
#define INF 2147483647
using namespace std;

const int maxn = 6300;

struct edge{
    int u, v, w;
}a[maxn*2];

int n, m, s, e, cnt = 0, head[maxn], dis[maxn], vis[maxn];
queue<int> q;

void addEdge(int u, int v, int w){
    a[++cnt].u = v;
    a[cnt].v = head[u];
    head[u] = cnt;
    a[cnt].w = w;
} //邻接表

void readint(int& num){ //可耻的读入优化
    char ch = getchar();
    num = 0;
    if(ch=='-'){
        ch=getchar();
        while(ch-'0'<10&&ch-'0'>=0){
            num = (num<<1) + (num<<3) - ch + '0';
            ch = getchar();
        }
        return;
    }
    while(ch-'0'<10&&ch-'0'>=0){
        num = (num<<1) + (num<<3) + ch - '0';
        ch = getchar();
    }
    return;
}

int main(){
    readint(n); readint(m); readint(s); readint(e);
    int u, v, w;
    for(int i = 1; i <= m; i++){
        readint(u); readint(v); readint(w);
        addEdge(u, v, w);
        addEdge(v, u, w);
    }//建图
    for(int i = 1; i <= n; i++) dis[i] = INF;
    q.push(s); dis[s] = 0; vis[s] = 1;//SPFA初始化
    while(!q.empty()){//SPFA
        int u = q.front(); q.pop();
        vis[u] = 0;
        for(int i = head[u]; i; i = a[i].v)
            if(dis[a[i].u] > dis[u] + a[i].w){
                dis[a[i].u] = dis[u] + a[i].w;
                if(!vis[a[i].u]){
                    q.push(a[i].u);
                    vis[a[i].u] = 1;
                }
            }
    }
    printf("%d", dis[e]);
    return 0;
}
```
本人是蒟蒻，如果代码有写得不好的地方，还请各位大佬指出。


---

