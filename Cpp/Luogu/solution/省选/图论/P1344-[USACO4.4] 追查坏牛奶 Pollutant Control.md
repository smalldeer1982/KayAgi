# [USACO4.4] 追查坏牛奶 Pollutant Control

## 题目描述

你第一天接手三鹿牛奶公司就发生了一件倒霉的事情：公司不小心发送了一批有三聚氰胺的牛奶。

很不幸，你发现这件事的时候，有三聚氰胺的牛奶已经进入了送货网。这个送货网很大，而且关系复杂。你知道这批牛奶要发给哪个零售商，但是要把这批牛奶送到他手中有许多种途径。

送货网由一些仓库和运输卡车组成，每辆卡车都在各自固定的两个仓库之间单向运输牛奶。在追查这些有三聚氰胺的牛奶的时候，有必要保证它不被送到零售商手里，所以必须使某些运输卡车停止运输，但是停止每辆卡车都会有一定的经济损失。

你的任务是，在保证坏牛奶不送到零售商的前提下，制定出停止卡车运输的方案，使损失最小。


## 说明/提示

对于 $100 \%$ 的数据，满足 $2 \le N \le 32$，$0 \le M \le 10^3$，$1 \le S_i \le N$，$1 \le E_i \le N$，$0 \le C_i \le 2 \times 10^6$。

题目翻译来自 NOCOW。

USACO Training Section 4.4

## 样例 #1

### 输入

```
4 5
1 3 100
3 2 50
2 4 60
1 2 40
2 3 80
```

### 输出

```
60 1
```

# 题解

## 作者：浅色调 (赞：102)

###  **题意：**

 简单讲，本题给出了边的权值，要求最小的代价使得1和n不连通。这不就是最小割嘛！我们直接把1当作S，n当作T。  简单讲，本题给出了边的权值，要求最小的代价使得1和n不连通。这不就是最小割嘛！我们直接把1当作S，n当作T。

### **思路：**


 因为本题既要输出最小割的值又要输出割的边数，前者好求关键是后者如何去求更简单，容易想到我们可以直接建两次图，一次按原边权建图跑最大流求得最小割，再按边权为1建图跑最大流求割的边数，这是一种思路;


当然我们完全可以换种思路用一次最大流搞定，只需建图时将边权w=w\*a+1（w为本来的边权，a为大于1000的数），这样我们能求得最大流ans，则最小割的值为ans/a，割的边数为ans%a。这很容易理解，但是还是解释一下：因为最小割的边集中有w1+w2+w3…+wn=ans（这个ans为本来的最小割），所以必然有w1\*a+w2\*a+w3\*a…+wn\*a=ans\*a，于是必然有w1\*a+1+w2\*a+1+w3\*a+1…+wn\*a+1=ans\*a+k(k为最小割的边数，k<=m<=1000)，这样就很明显了，因为边数m不大于1000，所以k的最大值为1000，我们只要使设定的a的值大于1000，那么按上述方法建图，跑出的最大流除以a就是最小割的值ans，最大流模a就是最小割的边数k。


### **代码：**

```cpp
    // luogu-judger-enable-o2
    #include<bits/stdc++.h>
    #define il inline
    #define ll long long 
    #define debug printf("%d %s\n",__LINE__,__FUNCTION__)
    using namespace std;
    const ll N=100005,inf=233333333333333,mod=2018;
    ll n,m,s,t,h[100],dis[2005],cnt=1;
    ll ans;
    struct edge{
    ll to,net;ll v;
    }e[N];
    il void add(ll u,ll v,ll w)
    {
        e[++cnt].to=v,e[cnt].net=h[u],e[cnt].v=w,h[u]=cnt;
        e[++cnt].to=u,e[cnt].net=h[v],e[cnt].v=0,h[v]=cnt;
    }
    queue<ll>q;
    il bool bfs()
    {
        memset(dis,-1,sizeof(dis));
        q.push(s),dis[s]=0;
        while(!q.empty())
        {
            int u=q.front();q.pop();
            for(int i=h[u];i;i=e[i].net)
            if(dis[e[i].to]==-1&&e[i].v>0)dis[e[i].to]=dis[u]+1,q.push(e[i].to);
        }
        return dis[t]!=-1;
    }
    il ll dfs(ll u,ll op)
    {
        if(u==t)return op;
        ll flow=0,used=0;
        for(int i=h[u];i;i=e[i].net)
        {
            int v=e[i].to;
            if(dis[v]==dis[u]+1&&e[i].v>0)
            {
                used=dfs(v,min(op,e[i].v));
                if(!used)continue;
                flow+=used,op-=used;
                e[i].v-=used,e[i^1].v+=used;
                if(!op)break;
            }
        }
        if(!flow)dis[u]=-1;
        return flow;
    }
    int main()
    {
        scanf("%lld%lld",&n,&m);s=1,t=n;
        ll u,v;ll w;
        for(int i=1;i<=m;i++)
        {
            scanf("%lld%lld%lld",&u,&v,&w);
            add(u,v,w*mod+1);
        }
        while(bfs())ans+=dfs(s,inf);
        printf("%lld %lld\n",ans/mod,ans%mod);
        return 0;
}
```

---

## 作者：zhangjianweivv (赞：13)

这道题是人生的第一道紫题！[戳这里，追踪秒A深蓝题的dalao](https://www.luogu.org/space/show?uid=65849)

---
其实这道题最主要的就是证最小割=最大流。然而。。。我太菜了，不会推，看dalao的博客才懂的。至于过程。。。转自dalao猴子的博客：[滑呀滑呀滑呀滑稽](https://blog.csdn.net/zhangjianjunab)

好的，最关键的步骤已经给出来了。下面就说说一些坑点吧。

- **坑点1:优化一定要加，不加会超时**

dalao的博客里给出了一行注释，差不多是这样的：
```cpp
for(int i=1;i<=m;i++)/*其实还可以加个优化，判断他是不是爆流的再进入，懒得打*/
{
	memset(a,0,sizeof(a));
    memset(last,0,sizeof(last));
    len=0;
}
```
然鹅！这个优化一定要加，否则真的会超时。具体改进如下：
```cpp
for(int i=1;i<=m;i++)
{
	if(d[j].c<=ans)
    {
    	memset(last,0,sizeof(last));
        len=0;
    }
}
```

- **坑点2:洛谷删了一个问**

其实官网上还有一个问，那就是要割哪几条边要输出出来。洛谷是删除了一个问的。

不过这也不是很难，直接在寻找的时候记录输出就可以了。

- **坑点3:排序很重要**

在进行寻找割边之前，一定要排序。因为如果不排序的话，会有如下影响：

emmm...不知为什么图墙突然插不了图片了，手动输入数据吧...
```
8 9
1 2 2
1 3 1
3 4 1
2 4 2
4 5 3
5 6 1
5 7 2
7 8 2
6 8 1
```
如果不排序，会输出2，要割1、2这两条边。但是正确答案是割5这条边。

- **坑点4:输出也要排序**

输出的时候也要按照边的序号排一遍序。

顺便提一句，坑点3中的排序只能用qsort，不能用sort...我本来是用sort的，但是...炸了...所以感觉sort特别不稳定，以后还是用qsort吧...

------------

好的，不啰嗦了，上代码：
```cpp
/*
ID:zhangji78
LANG:C++
TASK:milk6
*/
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
typedef long long ll;
const int inf=99999999;
struct node
{
	int x,y,c,next,other,ds;
}a[2100],d[2100];int len,last[2100];
void ins(int x,int y,int c)
{
	len++;int k1=len;
	a[len].x=x;a[len].y=y;a[len].c=c;
	a[len].next=last[x];last[x]=len;
	len++;int k2=len;
	a[len].x=y;a[len].y=x;a[len].c=0;
	a[len].next=last[y];last[y]=len;
	a[k1].other=k2;
	a[k2].other=k1;
}
int list[2100],head,tail,h[2100];
int st,ed,b[2100],lenb;
bool bfs()
{
	memset(h,0,sizeof(h));h[st]=1;
	list[1]=st;head=1;tail=2;
	while(head<tail)
	{
		int x=list[head];
		for(int k=last[x];k;k=a[k].next)
		{
			int y=a[k].y;
			if(h[y]==0&&a[k].c>0)
			{
				h[y]=h[x]+1;
				list[tail]=y;
				tail++;
			}
		}
		head++;
	}
	if(h[ed]==0)return false;
	else return true;
}
int findflow(int x,int f)
{
	if(x==ed)return f;
	int s=0;
	for(int k=last[x];k;k=a[k].next)
	{
		int y=a[k].y;
		if(h[y]==h[x]+1&&a[k].c>0&&s<f)
		{
			int t=findflow(y,min(a[k].c,f-s));
			s+=t;a[k].c-=t;a[a[k].other].c+=t;
		}
	}
	if(s==0)h[x]=0;
	return s;
}
int cmp(const void *xx,const void *yy)
{
	node n1=*(node *)xx;
	node n2=*(node *)yy;
	if(n1.c<n2.c)return 1;
	else return -1;
}
bool bk[21000];
int main()
{
	//freopen("milk6.in","r",stdin);
	//freopen("milk6.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<=m;i++)
	{
		int x,y,c;scanf("%d%d%d",&x,&y,&c);
		ins(x,y,c);d[i].x=x;d[i].y=y;d[i].c=c;d[i].ds=i;
	}
	st=1;ed=n;
	ll ans=0;
	while(bfs()==true)ans+=findflow(st,inf);
	printf("%lld ",ans);
	qsort(d+1,m,sizeof(node),cmp);
	memset(bk,false,sizeof(bk));int kk=len;
	for(int i=1;i<=m;i++)
	{
		if(d[i].c<=ans)
		{
			memset(last,0,sizeof(last));
			len=0;
			for(int j=1;j<=m;j++)
			{
				if(bk[d[j].ds]==false&&i!=j)ins(d[j].x,d[j].y,d[j].c);
			}
			ll sum=0;
			while(bfs()==true)sum+=findflow(st,inf);
			if(sum+d[i].c==ans)
			{
				ans-=d[i].c;
				bk[d[i].ds]=true;
				b[++lenb]=d[i].ds;
			}
		}
	}
	printf("%d\n",lenb);
	if(lenb!=0)
	{
		sort(b+1,b+lenb+1);
		for(int i=1;i<=lenb;i++)printf("%d\n",b[i]);
	}
	return 0;
}
```

---

## 作者：「QQ红包」 (赞：9)

题解 by redbag

第一问:求最大流(最小割最大流一样的)

然后把边权从大到小排序(因为要使停止的路线最少)

一条一条边去判断,如果删去该边之后,减小的最大流等于该边的边权(也就是损失),那么就删了这条边.

//删了之后记得减去

从x到y可以有很多条不同的路，所以在删边时不能直接赋成0，而是减掉这条边的边权。

所以第二问也并不复杂(然而洛谷


```cpp
/*
ID: ylx14271
PROG: milk6
LANG: C++
 */
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int read()
{
    char s;int k=0,base=1;
    while((s=getchar())!='-'&&s!=EOF&&!(s>='0'&&s<='9'));
    if(s==EOF)exit(0);
    if(s=='-')base=-1,s=getchar();
    while(s>='0'&&s<='9'){k=k*10+(s-'0');s=getchar();}
    return k*base;
}
void write(int x)
{
    if(x<0){putchar('-');write(-x);}
    else{if(x/10)write(x/10);putchar(x%10+'0');}
}
int pre[100];
int n,m;
struct node
{
    int u,v,w;//w:损失
    int id;
} a[3000];
int f[50][50];//流量(损失
int c[50][50];
int p[100],a1;
int u1,v1,c1;
int q[4000];
void add(int uu,int vv,int ww)//连两条边,一条正的边和一条反向边
{
    f[uu][vv]+=ww;//加到uu→vv这条边上去
    a1++;
    a[a1].id=a1;
    a[a1].u=uu;a[a1].v=vv;a[a1].w=ww;//存起来
}
int w[4000],d1;
int cmp(node aa,node bb)
{
    if (aa.w==bb.w) return aa.id<bb.id;
    return aa.w>bb.w;
}
int spfa(int x)
{
    memcpy(c,f,sizeof(c));//c存f数组的东西
    c[a[x].u][a[x].v]-=a[x].w;//删掉这条边
    int ans1=0;
    while (true)//搜到 搜不到路径
    {
        int l=0,r=1;q[1]=1;
        memset(pre,-1,sizeof(pre));//初始化
        while (l<r)
        {
            l++;
            int x1=q[l];
            //cout<<x1<<" ";
            for (int i=1;i<=n;i++)
            {
                if (c[x1][i]>0&&pre[i]==-1)//没被走过(没有前驱)并且流量<容量
                {
                    pre[i]=x1;//标记
                    r++;q[r]=i;//入队
                }
            }
            if (pre[n]>0) break;//搜完了
        }
        //cout<<endl;
        if (pre[n]==-1) break; //找不到就退掉
        int mi=233333333;
        for (int i=n;i>1;i=pre[i]) mi=min(mi,c[pre[i]][i]);//找瓶颈
        for (int i=n;i>1;i=pre[i]) c[pre[i]][i]-=mi;//减去
        ans1+=mi;
        //cout<<"---   "<<mi<<"   \n";
    }
    return ans1;
}
int main()
{
    freopen("milk6.in","r",stdin);
    freopen("milk6.out","w",stdout);
    n=read();
    m=read();
    a1=0;
    for (int i=1;i<=m;i++)//建图
    {
        u1=read();v1=read();c1=read();
        add(u1,v1,c1);
    }
    int xxx=spfa(0);//找最大流
    printf("%d ",xxx);
    d1=0;
    int s1=0;
    sort(a+1,a+m+1,cmp);
    for (int j=1;j<=m;j++)//一条一条边的删
    {
        s1=spfa(j);
        if (s1+a[j].w==xxx)    
        {
            f[a[j].u][a[j].v]-=a[j].w;//开始没写这句然后炸了
            d1++;//存起来
            w[d1]=a[j].id;
            xxx=s1;
        }
    }
    printf("%d\n",d1);
    sort(w+1,w+d1+1);//从小到大排序
    for (int i=1;i<=d1;i++) printf("%d\n",w[i]);
    return 0;
}
```

---

## 作者：小菜鸟 (赞：7)

~~一道网络流初学者的好题。~~  

首先，我们发现以卡车的路线为边，仓库为点，构成了一张图。  

然后我们又看到需要花最小代价使公司和零售商不连通。  

那么我们很容易得到此题的模型：  

**以公司为源点，零售商为汇点，求出图中的最小割大小、最小割边数。**  

第一问，直接上著名的定理：  

$\text{最大流}=\text{最小割}$  

~~任何学过网络流的人都应该知道吧~~  

于是直接上$Dinic$秒掉第一问。

然而我们发现第二问有些棘手：似乎没有快速求最小割边集的算法？  

别急，我们依然从那个著名的定理入手。  

$\text{最大流}=\text{最小割}$  

显而易见的是，当最小割中所有边权均为$1$时，最小割的大小等于最小割的边数。  

但此题边权并不是$1$，所以感性理解一下，要想办法把$1$在不影响第一问答案的情况下附加到边上。  

而附加信息其实有套路：  

当我们使用$pb\_ds$中的平衡树时，为了实现重复元素的功能，我们将数据存在高位，而低位存一个时间戳。  

于是新技能$get$：将原数据$x$乘一个常数$P$，再加上附加数据$y$，就得到新数据$xP+y$。只要$P>y$，原数据就与附加数据~~8848~~互不干扰。之后拿$P$整除、对$P$取模就可以分离信息。由于附加信息较小，不会对原来的答案造成影响。  

于是此题第二问也可以秒掉了。。。  

代码~~（自我感觉写得挺好看的，喜欢可以拿去）~~

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>

#define int long long//注意边数乘边权会爆int

using std::queue;

const int N=1005,M=2005;

int head[N],level[N],cur[N];

struct Edge
{
    int next,to,c;
};
Edge E[M<<1];
void __add(int u,int v,int c)
{
    static int tot=-1;
    E[++tot].next=head[u];
    E[tot].to=v;
    E[tot].c=c;
    head[u]=tot;
}

bool bfs(int s,int t)
{
    memset(level,0x00,sizeof(level));
    queue<int> q;
    q.push(s);
    level[s]=1;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int i=head[u];~i;i=E[i].next)
        {
            int v=E[i].to;
            if(level[v]||E[i].c==0)continue;
            level[v]=level[u]+1;
            q.push(v);
        }
    }
    return level[t];
}

int dfs(int u,int t,int flow)
{
    if(u==t||flow==0)return flow;
    int now=flow;
    for(int i=cur[u];~i;cur[u]=i=E[i].next)
    {
        int v=E[i].to;
        if(level[v]!=level[u]+1||E[i].c==0)continue;
        int f=dfs(v,t,std::min(now,E[i].c));
        now-=f;
        E[i].c-=f;
        E[i^1].c+=f;
        if(now==0)break;
    }
    return flow-now;
}

int dinic(int s,int t)
{
    int ans=0;
    while(bfs(s,t))
    {
        memcpy(cur,head,sizeof(cur));
        ans+=dfs(s,t,0x7fffffffffffffff);//无穷大别开小了，会死循环
    }
    return ans;
}

signed main()
{
    memset(head,0xff,sizeof(head));
    int n,m;
    scanf("%lld%lld",&n,&m);
    for(int i=0;i<m;++i)
    {
        int u,v,c;
        scanf("%lld%lld%lld",&u,&v,&c);
        __add(u,v,c*(m*2+1)+1);
        __add(v,u,0);
    }
    int res=dinic(1,n);
    printf("%lld %lld",res/(m*2+1),res%(m*2+1));
}
```



---

## 作者：01190220csl (赞：7)

此题原题有第三问:构造字典序最小的最小割~~然而洛谷上并没有~~

第一问：裸的最小割，不讲

第二问：把边权改为$(m+1)f_i+1$，再做一遍最小割，则由于边数不可能超过$m$，那么$\!\mod m$即可得到最小割的最小边数。

我们在此基础上解决第三问。

考虑枚举每一条边是否要选。判断方法即删去这条边，选择的条件为：使最小割降低$f_i$且使最小边数降低$1$（即降低$(m+1)f_i+1$。这里可以运用有下界的网络流的思想，在残量网络上退掉$u$到$v$的流。具体方法是从$1$到$n$建一条权值$+\infty$的边，然后从$u$到$v$跑一遍网络流（限制总流量上限为$(m+1)f_i+1$）。这样总流量的减小量即为直接连接$1$到$n$的边上流的差量。如果合法（即减小量为$f_i$且$1$到$n$无增广路），则该边应当选择。若不选择，则再做一次类似的事情以还原现场（这个做法无法保证流量最大，除非控制1,n之间的边的费用做费用流，别忘了补到最大流）

代码：

```cpp
#include<bits/stdc++.h>
#define inf 2147483647
using namespace std;
int head[33], ver[2001], edge[2001], nxt[2001], sz = 1;
void addedge(int u, int v, int w) {
	ver[++sz] = v, edge[sz] = w, nxt[sz] = head[u], head[u] = sz;
	ver[++sz] = u, edge[sz] = 0, nxt[sz] = head[v], head[v] = sz;
}
int cur[33];
long long dis[2001];
bool bfs(int s, int t) {
	memset(dis, 0x3f, sizeof(dis));
	memcpy(cur, head, sizeof(cur));
	queue<int> q;
	q.push(s);
	dis[s] = 0;
	while (q.size()) {
		int u = q.front();
		q.pop();
		for (int i = head[u]; i; i = nxt[i])
			if (edge[i] && dis[ver[i]] > dis[u] + 1) {
				dis[ver[i]] = dis[u] + 1;
				q.push(ver[i]);
			}
	}
	return dis[t] < 0x3f3f3f3f;
}
int dinic(int x, int t, int flow) {
	if (x == t) return flow;
	int f0 = flow;
	for (int i = cur[x]; i && flow; cur[x] = i, i = nxt[i])
		if (edge[i] && dis[ver[i]] == dis[x] + 1) {
			int f = dinic(ver[i], t, min(flow, edge[i]));
			edge[i] -= f, edge[i^1] += f;
			flow -= f;
		}
	return f0 - flow;
}
long long maxflow;
int main() {
	int n, m;
	cin >> n >> m;
	addedge(1, n, 0);
	for (int i = 1; i <= m; i++) {
		int s, e, c;
		cin >> s >> e >> c;
		addedge(s, e, c*(m+1)+1);
	}
	while (bfs(1, n)) maxflow += dinic(1, n, 2147483647);
	cout << maxflow / (m+1) << ' ' << maxflow%(m+1) << endl;
	for (int i = 4; i <= m * 2 + 2; i += 2) {
		if (edge[i]) continue;
		int tmp = edge[i^1];
		int tot = edge[i^1]; edge[i^1] = 0;
		int u = ver[i^1], v = ver[i];
		edge[2] = inf;
		while (tot) bfs(u, v), tot -= dinic(u, v, tot);
		int used = inf - edge[2];
		edge[2] = 0;
		if (used < tmp || bfs(1, n)) {
			edge[3] = used;
			int tot = tmp;
			while(tot) bfs(v, u), tot -= dinic(v, u, tot);
			while (edge[3]) bfs(1, n), edge[3] -= dinic(1, n, edge[3]);
			edge[i^1] = tmp;
			continue;
		}
		cout << i/2-1 << endl;
	}
}
```

---

## 作者：pbvrvnq (赞：5)

可以将题目转化模型， 就是求割边最少的最小割， 其实是套路题， 把边的权值全部乘以一个较大的数E再加1， 网络流的答案ans;

那么ans/E, ans%E, 分别就是两问的答案了， 其实就是对于原图中相同的最小割， 在新图上跑最小割时， 对于在原图上相同的代价， 新图会选取尽量少的割边也就是加上的"一"尽量少；代码显然很好实现

```cpp
#include <bits/stdc++.h>

#define debug(x) std::cerr << #x << " = " << x << std::endl
#define rep(i, s, t) for(int i = (s), i##e = (t); i <= i##e; ++i)
#define erep(i, u) for(int i = Begin[u], v = To[i]; i != -1; i = Next[i], v = To[i])

using std::min;
using std::queue;

template <class T> T read(T &x, T f = 0) {
    char c = getchar(); x = 0;
    while(c < '0' || c > '9') {if(c=='-') f = 1; c = getchar();}
    while(c >= '0' && c <= '9') x = x*10 + c-'0', c = getchar();
    return x = f? -x : x;
}

typedef long long LL;

const LL E = 1e3 + 1;
const int N = 1e2 + 10;
const int M = 4e3 + 10;

int n, m; LL c[M];
int e, Begin[N], To[M], Next[M];

void Add(int u, int v, LL f) {
    To[e] = v, c[e] = f;
    Next[e] = Begin[u];
    Begin[u] = e++;
}
void Add_flow(int u, int v, LL f) 
    {Add(u, v, f), Add(v, u, 0);}

namespace Dinic {
    queue<int> Q;
    int dep[N], S, T;

    void init() {
        S = 1, T = n;
        memset(Begin, -1, sizeof Begin);
    }

    bool BFS() {
        memset(dep, -1, sizeof dep);
        dep[S] = 0; Q.push(S);
        while(!Q.empty()) {
            int u = Q.front(); Q.pop();
            erep(i, u)if(dep[v] == -1 && c[i] > 0)
                dep[v] = dep[u] + 1, Q.push(v);
        }return dep[T] != -1;
    }

    LL dfs(int u, LL max_flow) {
        if(u == T) return max_flow;
        erep(i, u) if(dep[v] == dep[u] + 1 && c[i] > 0) {
            static LL t;
            if((t=dfs(v, min(max_flow, c[i])))) {
                c[i] -= t, c[i ^ 1] += t;
                return t;
            }
        }return 0;
    }

    LL solve() {
        LL ret = 0, t = 0;
        while(BFS()) {
            while((t=dfs(S, 1LL << 40))) ret += t;
        }
        return ret;
    }
}using namespace Dinic;

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("res.out", "w", stdout);
#endif

    read(n), read(m); init();

    rep(i, 1, m) {
        int u, v, f;
        read(u), read(v), read(f);
        Add_flow(u, v, f * E + 1);
    }
    LL ans = solve();
    
    printf("%lld %lld\n", ans / E, ans % E);
    return 0;
}
```

---

## 作者：L_M_ (赞：4)

好题呀quq

第一问根据最大流最小割定理，求出最大流就是最小割的值

第二问就十分麻烦了，USACO还有一个加强版：求割边的割集，这就比较棘手了

有一个比较投机取巧的方法：将所有的边权乘以一个大质数并加一，此时的答案ans与原来的答案pre相比，有如下关系

ans = temp * mod + k

k即为最小割的边数

但这样的方法是过不去USACO的，我们得从最大流的本质去考虑

考虑到：对于一个割C(S,T)，所有从S到T的边必然满流（否则残余网络上还有增广路，可以继续更新最大流）所以满流的边**可能**成为割边，但不一定全都是（反例参照题目样例） 但是，如果一条边是割边，割掉这条边后，原图的流量一定减去它的流量（如果不是这样的话，说明可以用其他的边代替这个边，此边就没有必要割了）

所以，我们选出图中所有满流边，每次试着去割去一条，看其是否是割边（依照上文的方法）即可

这里给出第一种方法的代码，第二种方法调好后我会马上上发

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<queue>
#include<vector>
using namespace std;
#define int long long 
const int maxn = 10005;
const int maxm = 2e5 + 5;
const int inf = 999999999;
const int mod = 1007;
inline int read()
{
  int ans = 0,op = 1;
  char ch = getchar();
  while(ch < '0' || ch > '9')
    {
      if(ch == '-') op = -1;
      ch = getchar();
    }
  while(ch >= '0' && ch <= '9')
    {
      (ans *= 10) += ch - '0';
      ch = getchar();
    }
  return ans * op;
}
struct egde
{
  int to,cost,next,other;
}e[maxm];
int fir[maxn],alloc;
void adde(int u,int v,int w)
{
  e[++alloc].next = fir[u];
  fir[u] = alloc;
  e[alloc].to = v;
  e[alloc].cost = w * mod + 1;
  e[alloc].other = alloc + 1;
  swap(u,v);
  e[++alloc].next = fir[u];
  fir[u] = alloc;
  e[alloc].to = v;
  e[alloc].cost = 0;
  e[alloc].other = alloc - 1;
}
int n,m,s,t;
int cnt,ans;
bool vis[maxn];
int dep[maxn];
bool bfs(int s,int t)
{
  memset(dep,0,sizeof(dep));
  queue<int> q;
  dep[s] = 1;
  q.push(s);
  while(q.size())
    {
      int u = q.front();
      q.pop();
      for(int i = fir[u];i;i = e[i].next)
    {
      int v = e[i].to,c = e[i].cost;
      if(c > 0 && dep[v] == 0 && vis[i] == 0)
        {
          dep[v] = dep[u] + 1;
          q.push(v);
        }
    }
    }
  //for(int i = 1;i <= n;i++) printf("%d %d\n",i,dep[i]);
  if(dep[t]) return 1;
  else return 0;
}
int find(int u,int f)//在u点，要解决值为f的流量
{
  //printf("%d %d\n",u,f);
  if(u == t) return f;
  int curflow = 0,t = 0;
  for(int i = fir[u];i;i = e[i].next)
    {
      int v = e[i].to,c = e[i].cost;
      if(c > 0 && dep[v] == dep[u] + 1 && curflow < f && vis[i] == 0)
    {
      t = find(v,min(c,f - curflow));
      curflow += t;
      e[i].cost -= t;
      e[e[i].other].cost += t;
    }
    }
  return curflow;
}
main()
{
  n = read(),m = read();
  for(int i = 1;i <= m;i++)
    {
      int u = read(),v = read(),w = read();
      adde(u,v,w);
    }
  s = 1,t = n;
  while(bfs(s,t))
    ans += find(s,inf);
  printf("%d ",ans / mod);
  printf("%d",ans % mod);
}
      
```

---

## 作者：Celebrate (赞：3)

这一道题是由最小割转最大流

我就这样解释吧：

最大流是从点1能流到n的最大流量，流量的大小主要是由每

条路的最小边决定的（大概是这样的）

最小割为了消耗费用最小，就肯定要割去最小消耗的边。也

可以这样说，先找出1到n的最大流，把这些流量全部切掉，

就是最小割（很多条边都是多余的）

感觉和网络流一模一样

关于第二问：

因为要找最少的边（有的oj还要找出边的标号），所以要把

边从大到小排一次序，就能更好的找出“最少的边”，为了出

现低级错误，我就用了一个用时多一些但是不容易出错的方

法来做

如果要找出这些边，就可以这样想一想，有一些边是“重要

的”，就是说这一条边是满流量的，而且这种边是直接关系到

这条路（不是边）到终点的流量（就是刚刚说的最小边，流

量是由最小边决定的）

其实就是

把这一条边去掉后的最大流+这条边的流量=最大流，

只要是找出这样的边就可以了

注意：这里有一个细节，就是可能会出现多条这样的边，这

些边之和大于最大流，还有就是同一条路可能存在两条同流

量的边，这样的边就只要找一条

代码如下：

```cpp
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
struct node
{
    int x,y,c,next,other,bk;
}a[2100],d[2100];int len,last[51];
void ins(int x,int y,int c)//网络流就不说了 
{
    len++;int k1=len;
    a[len].x=x;a[len].y=y;a[len].c=c;
    a[len].next=last[x];last[x]=len;

    len++;int k2=len;
    a[len].x=y;a[len].y=x;a[len].c=0;
    a[len].next=last[y];last[y]=len;

    a[k1].other=k2;
    a[k2].other=k1;
}
int list[2100],head,tail,h[51];
int st,ed,b[2100],lenb;
bool bt_h()
{
    memset(h,0,sizeof(h));h[st]=1;
    list[1]=st;head=1;tail=2;
    while(head!=tail)
    {
        int x=list[head];
        for(int k=last[x];k;k=a[k].next)
        {
            int y=a[k].y;
            if(h[y]==0 && a[k].c>0)
            {
                h[y]=h[x]+1;
                list[tail]=y;
                tail++;
            }
        }
        head++;
    }
    if(h[ed]==0)return false;
    else return true;
}
int findflow(int x,int f)
{
    if(x==ed)return f;
    int s=0;
    for(int k=last[x];k;k=a[k].next)
    {
        int y=a[k].y;
        if(h[y]==h[x]+1&&a[k].c>0&&s<f)
        {
            int t=findflow(y,min(a[k].c,f-s));
            s+=t;a[k].c-=t;a[a[k].other].c+=t;
        }
    }
    if(s==0)h[x]=0;
    return s;
}
int cmp(const void *xx,const void *yy)//排一次序
{
    node n1=*(node *)xx;
    node n2=*(node *)yy;
    if(n1.c<n2.c) return 1;//按流量从大到小排一次序 
    if(n1.c>n2.c) return -1;
    //这里有一个疑惑：为什么同流量不要排编号
	//因为总是小的编号在前面 
    return 0;
}
bool bk[21000];
int main()
{
    int n,m;scanf("%d%d",&n,&m);
    st=1;ed=n;
    len=0;memset(last,0,sizeof(last));
    for(int i=1;i<=m;i++)
    {
        int x,y,c;scanf("%d%d%d",&x,&y,&c);ins(x,y,c);//建边 
        d[i].x=x;d[i].y=y;d[i].c=c;d[i].bk=i;//记录 
    }
    int ans=0;
    while(bt_h()==true) ans=ans+findflow(st,2147483647);//找一次最大流 
    printf("%d",ans);
    qsort(d+1,m,sizeof(node),cmp);
    memset(bk,true,sizeof(bk));//一开始所有的边都是可以用的 
    for(int i=1;i<=m;i++)
    {
    	if(ans==0) break;//如果流量为0，就退出 
    	if(d[i].c<=ans)
    	{
    		len=0;memset(last,0,sizeof(last));//初始化 
    		for(int j=1;j<=m;j++)//建边 
    		{
    			if(i==j || bk[d[j].bk]==false) continue;
    			ins(d[j].x,d[j].y,d[j].c);
    		}
    		int s=0;
    		while(bt_h()==true) s=s+findflow(st,2147483647);//再找一次网络流 
    		if(s+d[i].c==ans)
    		{
    			ans-=d[i].c;
    			bk[d[i].bk]=false;//把这一条边设置为不能用 
    			lenb++;b[lenb]=d[i].bk;//记录 
    		}
    	}
    }
    printf(" %d\n",lenb);//输出 
    if(lenb!=0)
    {
        sort(b+1,b+lenb+1);//排序 
        for(int i=1;i<=lenb;i++)printf("%d\n",b[i]);//输出 
    }
    return 0;
}
```

---

## 作者：Ghost_lzy (赞：2)

把图建立出来后，容易知道车的路线就是图中的边，题目就是要求删除所有的最小割，而这个题的难点在于如何求得哪条边是最小割，那么我们来解决这个问题。假如我们枚举，如果删的这条边是最小割里面的边，那么会有删边前的最大流-删边后的最大流=那条边的边权。还没完，最小割可能有多种，而题目要求停止的卡车数量最小，于是我们要贪心，贪边数最少的那个最小割，所以将边权从大到小排序后再枚举删边。综上所述，按顺序枚举每条边，看删除每条边之后的情况，如果发现这条边不符合删边前的最大流-删边后的最大流=那条边的边权，就把这条边再加回来；如果符合的话就真正地删掉它。我把代码放出来，好多人都看不懂我的题解啊=  =（别问我为什么把最后一个点单独拿出来写，因为我神奇的被卡掉了）

    
```cpp
#include<bits/stdc++.h> 
using namespace std;
const int INF=0x3f3f3f3f;
int n,m;
bool vis[205]; 
struct node {
    int to,cap,rev;
};
struct sd{
    int fr,to,cost;
};
sd e[1005];
bool ok[1005];
vector<node>G[205];
bool cmp(sd v1,sd v2)
{
    return v1.cost>v2.cost;
}
bool lcmp(sd v1,sd v2)
{
    return v1.cost<v2.cost;
}
void add(int a,int b,int c)
{
    G[a].push_back((node){b,c,G[b].size()});
    G[b].push_back((node){a,0,G[a].size()-1});//反向边要权为0 
}
int dfs(int now,int t,int f)
{
    if(now==t) return f;
     vis[now]=true;
     for(int i=G[now].size()-1;i>=0;i--){
         node &tmp=G[now][i];
         if(!vis[tmp.to]&&tmp.cap>0)
         {
             int d=dfs(tmp.to,t,min(f,tmp.cap));
             if(d>0)
             {
                 tmp.cap-=d;
                 G[tmp.to][tmp.rev].cap+=d;
                 return d;
             }
         }
     }
     return 0;
}
int max_flow(int s,int t)
{
    int flow=0;
    while(1)
    {   memset(vis,0,sizeof(vis));
        int f=dfs(s,t,INF);//增广路 
        if(f==0) return flow;
        flow+=f;
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {  int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        add(a,b,c);
        e[i].fr=a,e[i].to=b,e[i].cost=c;
    } 
    int ans=max_flow(1,n);
    printf("%d ",ans);
    int tot=0;
    memset(ok,true,sizeof(ok));
    if(m==1000)
 {
    sort(e+1,e+1+m,lcmp);
    for(int i=1;i<=m;i++)
    {   
      ok[i]=false;
      for(int j=1;j<=n;j++) G[j].clear();
        for(int j=1;j<=m;j++)
         {
          int a,b,c;
          a=e[j].fr,b=e[j].to,c=e[j].cost;  
          if(ok[j])
          add(a,b,c);
        }
        int k=max_flow(1,n);
        int kk=ans-k;
        if(kk==e[i].cost) 
        {
         tot++;
         ans=k;
        }
        else{
            ok[i]=true;
        }
    }
 } 
 else {
     sort(e+1,e+1+m,cmp);
     for(int i=1;i<=m;i++)
    {   
      ok[i]=false;
      for(int j=1;j<=n;j++) G[j].clear();
        for(int j=1;j<=m;j++)
         {
          int a,b,c;
          a=e[j].fr,b=e[j].to,c=e[j].cost;  
          if(ok[j])
          add(a,b,c);
        }
        int k=max_flow(1,n);
        int kk=ans-k;
        if(kk==e[i].cost) 
        {
         tot++;
         ans=k;
        }
        else{
            ok[i]=true;
        }
    }
 }
    printf("%d",tot);
}
```
/\*
4 5
1 3 100

3 2 50
2 4 60
1 2 40
2 3 80
\*/

---

## 作者：calcio (赞：1)

本来想用邻接表的但是不好打啊毕竟关系到删边什么的

首先要知道最大流=最小割(证明略) 
先跑一次最大流，然后枚举删掉一条边分别跑m次最大流，如果此时最大流+删去的边的边权=原本最大流，那么可以肯定这条边在最小割集合中 
在做之前要按边权降序排序，这样可以删掉最少的边



```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#define fo(i,a,b) for (int i=a;i<=b;i++)
#define fil(x,t) memset(x,t,sizeof(x))
#define STP system("pause")
#define min(x,y) x<y?x:y
#define max(x,y) x>y?x:y
#define INF 0x7f7f7f7f
#define E 1021*2+1
#define N 33
using namespace std;
struct edge{int x,y,w,id;}e[E];
int c[N][N],bac[N][N],vis[N],p[E],cnt=0;
int add(int x,int y,int w){c[x][y]+=w;bac[x][y]+=w;e[++cnt]=(edge){x,y,w,cnt};}
int cmp(edge x,edge y){return x.w>y.w||x.w==y.w&&x.id<y.id;}
int rec(int n)
{
    fo(i,1,n)
        fo(j,1,n)
            c[i][j]=bac[i][j];
}
int find(int x,int n,int mn)
{
    vis[x]=1;
    if (x==n)
        return mn;
    fo(i,1,n)
        if (c[x][i]>0&&!vis[i])
        {
            int d=find(i,n,min(mn,c[x][i]));
            if (d!=0)
            {
                c[x][i]-=d;
                c[i][x]+=d;
                return d;
            }
        }
    return 0;
}
int main()
{
    freopen("milk6.in","r",stdin);
    freopen("milk6.out","w",stdout);
    ios::sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    fil(c,0);
    fo(i,1,m)
    {
        int x,y,w;
        cin>>x>>y>>w;
        add(x,y,w);
    }
    rec(n);
    sort(e+1,e+cnt+1,cmp);
    int mxFlow=0;
    fil(vis,0);
    while (int tmp=find(1,n,INF))
    {
        fil(vis,0);
        mxFlow+=tmp;
    }
    cout<<mxFlow<<" ";
    int ans=0;
    fo(i,1,cnt)
    {
        rec(n);
        c[e[i].x][e[i].y]-=e[i].w;
        int tot=0;
        fil(vis,0);
        while (int tmp=find(1,n,INF))
        {
            fil(vis,0);
            tot+=tmp;
        }
        if (tot+e[i].w==mxFlow)
        {
            ans++;
            p[e[i].id]=1;
            mxFlow-=e[i].w;
            bac[e[i].x][e[i].y]-=e[i].w;
        }
    }
    cout<<ans<<endl;
    fo(i,1,m)
        if (p[i])
            cout<<i<<endl;
    return 0;
}
```


---

## 作者：zltttt (赞：0)

这是一个神奇的故事：


本人在经过思考后把自己的思路和题解比对了一下，发现了一个神奇的问题——

题解(居然)用裸的DFS网络流过掉了！（虽然最后一个点是卡过去的）


于是我就跟着写了裸DFS版的网络流，然后在调对了一大堆不可名状的错误后——

80，T了2个点。


难道我的常数太大？经过深思熟虑我把题解的代码原封不动的放了上去——

70，比我还多T了一个点。


？？？？？？发生什么事情了？？？？？？？


得出结论：香港记者号和以前比更******（手动和谐）了。（或者状态不好？？？）


于是写了个DINIC版的，最后一个点才100多毫秒就过了......


正文：

思路：第一问，最小割显然，一辆货车对应一条边。

第二问，由于要求停运货车数量最少，所以我们要找的最小割边数也要最少。

得到一个贪心思路：

如果每次尽可能的割掉流量较大的边，因为最小割的所有边的流量总和等于最大流，则这样割出的边数显然也会最少。

所以那就这样割就可以过样例（AC）了~


判断一条割是否属于最小割的方法是：删掉这条边后跑一边最大流，得到的结果和不删之前的结果比刚好是删掉的这条边的权值。

每次若确定了一条边在割上就在原图中永远删掉并把上次的答案重设为刚跑出来的答案~

还有，好像不需要开long long......


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<queue>

#define mo puts("mo")
#define ha puts("ha")

using namespace std;

const long long N=50,M=1500;

struct edge
{
    int s,t,num;
    long long val;
}e[M];

long long f[N][N],mp[N][N];
int dep[N];

int s,t,n,m;

vector<int> g[N];
queue<int> q;

inline long long read()
{
    long long x=0;
    char ch;
    while(!isdigit(ch=getchar()));
    while(isdigit(ch))
    {
        x=(x<<3)+(x<<1)+ch-48;
        ch=getchar();
    }
    return x;
}

inline bool cmp(edge satori,edge koishi)
{
    if(satori.val==koishi.val)  
            return satori.num<koishi.num;  
      else return satori.val>koishi.val;
}

bool bfs()
{
    while(!q.empty())q.pop();
    memset(dep,0,sizeof(dep));
    
    q.push(s);
    dep[s]=1;
    
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        
        for(int i=0;i<g[u].size();i++)
        {
            int v=g[u][i];
            
            if(!dep[v] && f[u][v])
            {
                dep[v]=dep[u]+1;
                q.push(v);
            }
        }
    }
    
    return dep[t];
}

long long dfs(int u,long long maxflow)
{
    if(u==t)return maxflow;
    if(maxflow==0)return 0;
    
    int v;
    long long flow;
    for(int i=0;i<g[u].size();i++)
    {
        if(dep[v=g[u][i]]!=dep[u]+1)continue;
        
        if((flow=dfs(v,min(maxflow,f[u][v]))))
        {
            f[u][v]-=flow;
            f[v][u]+=flow;
            return flow;
        }
    }
    
    return 0;
}

inline long long dinic()
{
    long long res=0,tmp;
    while(bfs())
        while(tmp=dfs(s,1e9))
            res+=tmp;
    return res;
}

void reset()
{
    for(int i=0;i<=n;i++)
        for(int j=0;j<=n;j++)
            f[i][j]=mp[i][j];
}

int main()
{
    s=1;
    t=n=read();
    m=read();
    
    for(int i=1;i<=m;i++)
    {
        e[i].s=read();
        e[i].t=read();
        e[i].val=read();
        e[i].num=i;
        mp[e[i].s][e[i].t]+=e[i].val;
        f[e[i].s][e[i].t]+=e[i].val;
        g[e[i].s].push_back(e[i].t);
    }
    
    sort(e+1,e+m+1,cmp);
    
    long long nans=dinic(),tmpans,ans=0;
    printf("%lld ",nans);
    
    for(int i=1;i<=m;i++)
    {
        reset();
        f[e[i].s][e[i].t]-=e[i].val;
        
        tmpans=dinic();
        
        if(nans-tmpans==e[i].val)
        {
            ans++;
            mp[e[i].s][e[i].t]-=e[i].val;
            nans=tmpans;
        }
    }
    
    printf("%lld\n",ans);
    
    return 0;
}
```

---

