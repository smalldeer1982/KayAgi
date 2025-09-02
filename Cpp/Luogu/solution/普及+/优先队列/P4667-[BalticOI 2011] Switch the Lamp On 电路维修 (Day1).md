# [BalticOI 2011] Switch the Lamp On 电路维修 (Day1)

## 题目描述

Casper 正在设计电路。有一种正方形的电路元件，在它的两组相对顶点中，有一组会用导线连接起来，另一组则不会。有 $N\times M$ 个这样的元件，你想将其排列成 $N$ 行，每行 $M$ 个。 电源连接到板的左上角。灯连接到板的右下角。只有在电源和灯之间有一条电线连接的情况下，灯才会亮着。为了打开灯，任何数量的电路元件都可以转动 90°（两个方向）。

![](https://cdn.luogu.com.cn/upload/pic/1286.png)

![](https://cdn.luogu.com.cn/upload/pic/1285.png)

在上面的图片中，灯是关着的。如果右边的第二列的任何一个电路元件被旋转 90°，电源和灯都会连接，灯被打开。现在请你编写一个程序，求出最小需要多少旋转多少电路元件。

## 说明/提示

对于 $40\%$ 的数据，$1 \le N \le 4$，$1 \le M \le 5$。

对于所有数据，$1 \le N,M \le 500$。

## 样例 #1

### 输入

```
3 5
\\/\\
\\///
/\\\\```

### 输出

```
1```

# 题解

## 作者：WorldBest丶牛顿 (赞：15)

## 注意 这篇题解有四份代码，AC代码需要您们拼凑一下qwq

对于原来的电路来说，我们可以将每个顶点和它周围的点相连    
点之间存在导线的两个点连一条边权为 $0$ 的边，不存在导线的连一条边权为 $1$ 的边  
为什么这么做呢，原来有边的两个点本来就是通路的，也就不需要加边权  
原来没有边的两个点，需要将导线转一下，那转动导线的操作也就是经过一条边权为 $1$ 的边，最短路的长度加 $1$ 

这样就能将这道题转化为一个求从左上角到右下角的最短路的题目  
很明显这是一个网格图，而且时限 $150ms$ 最好不要用某个算法

我先是写了一个优先队列优化的 $Dijkstra$（开了 $O2$ 过了，不开 $80-90$ 左右）
```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;

const int INF=19260817;
int n,m,cnt,sum;
int left_up,left_down,right_up,right_down;
char f[505];
int head[1100001],d[1100001];

struct edge
{
    int next,w,v;
}e[1100001];

void add(int u,int v,int w)
{
    e[++cnt].v=v;
    e[cnt].w=w;
    e[cnt].next=head[u];
    head[u]=cnt;
}

struct node
{
    int u,d;
    bool operator<(const node& rhs) const{
        return d>rhs.d;
    }
}; //用cmp的写法wa了一个晚上之后我就再也不那么写了

void Dijkstra()
{
    sum=(m+1)*(n+1);//这是总的节点数
    priority_queue<node> q;
    for(int i=1;i<=sum;i++) d[i]=INF;
    d[1]=0;
    q.push((node){1,d[1]});
    while(!q.empty())
    {
        node x=q.top(); q.pop();
        int u=x.u;
        if(x.d!=d[u]) continue;
        for(int i=head[u];i;i=e[i].next)
        {
            int v=e[i].v,w=e[i].w;
            if(d[u]+w<d[v])
            {
                d[v]=d[u]+w;
                q.push((node){v,d[v]});
            }
        }
    }
    if(d[sum]==INF) cout<<"NO SOLUTION";
    else cout<<d[sum];
} 

int main()
{
    std::ios::sync_with_stdio(false);
    cin>>n>>m;
    for(int i=0;i<n;++i)
    {
    	cin>>f;
        for(int j=0;j<m;++j)
        {
        	left_up=(m+1)*i+j+1;
    		right_up=(m+1)*i+j+2;
    		left_down=(m+1)*(i+1)+j+1;
    		right_down=(m+1)*(i+1)+j+2;
            //处理节点编号，一条边占一个格子的话就会有四个顶点
            if(f[j]==92)//不知道转义符的我就只能写个ASCII码了
            {
               	add(left_up,right_down,0);
               	add(right_down,left_up,0);//无向图正反存一次
               	add(left_down,right_up,1);
                add(right_up,left_down,1);
           	}
            if(f[j]==47)
            {
            	add(left_down,right_up,0);
                add(right_up,left_down,0);
                add(left_up,right_down,1);
                add(right_down,left_up,1);
            }
        }
    }
    Dijkstra();
    return 0;
}
```

虽然过了，但是这种方法肯定是不完美的（毕竟开 $O2$ 才行）。  
很明显，我这个存图的方式常数太大，那我们可以改一下存图

```
void add(int u,int v,int w)
{
    e[++cnt].v=v;e[cnt].w=w;e[cnt].next=head[u];head[u]=cnt;
    e[++cnt].v=u;e[cnt].w=w;e[cnt].next=head[v],head[v]=cnt;
}//顺便也改一下，写起来更加方便了

//main函数中的存图
	for(int i=1;i<=n+1;++i)
        for(int j=1;j<=m+1;++j)
            mark[i][j]=++tot;//预处理出每个顶点的编号
    for(int i=1;i<=n;++i)
    {
    	cin>>f;
        for(int j=1;j<=m;++j)
        {
            if(f[j-1]=='/')
            {
            	add(mark[i][j],mark[i+1][j+1],1);//调整一下存图函数就方便了很多
               	add(mark[i+1][j],mark[i][j+1],0);
            }
            else
            {
               	add(mark[i][j],mark[i+1][j+1],0);
               	add(mark[i+1][j],mark[i][j+1],1);
           	}
        }
    }
```

但是这种写法还是只有 $90$ 分左右，那该怎么办呢？  
注意到 $Dijkstra$ 的堆优化中会重复加点很多次  
在 $Dijkstra$ 中，我们明明只是需要找出 $dis$ 值最小的点不是吗  

那我们就可以使用线段树来优化查询操作（只需要单点修改呢）  
只要最初将值都设为 $INF$ ，起点设为 $0$ ，线段树储存最小值，  
将走过的点也设为 $INF$ ， $Dijkstra$ 的时候判断树根的值是否等于 $INF$ ，   
如果等于的话就没有点能更新了，就做完了  
可以看一下告诉我这个方法的 @yizimi远欣 大佬的[博客](https://yizimiyuanxin.blog.luogu.org/solution-p1339-new)

```cpp
struct segment_tree
{
	int minx[1100001],tag[1100001];
	void push_up(int p)
	{
		minx[p]=min(minx[p<<1],minx[p<<1|1]);
		tag[p]=(minx[p<<1]<minx[p<<1|1])?tag[p<<1]:tag[p<<1|1];
        //minx存最小值，tag存拥有这个值的点的编号
	}
	void build(int l,int r,int p)
	{
		if(l==r)
		{
			minx[p]=d[l];
			tag[p]=l;
			return;
		}
		int mid=(l+r)>>1;
		build(l,mid,p<<1);
		build(mid+1,r,p<<1|1);
		push_up(p);
	}
	void update(int now,int l,int r,int p,int k)
	{
		if(l==r)
		{
			minx[p]=k;
			return;
		}
		int mid=(l+r)>>1;
		if(now<=mid) update(now,l,mid,p<<1,k);
		else update(now,mid+1,r,p<<1|1,k);
		push_up(p);
	}
}tree;

void Dijkstra()
{
    for(int i=2;i<=tot;i++) d[i]=INF;
    tree.build(1,tot,1);
    while(tree.minx[1]<INF)//如果线段树的树根的值为INF，那所有能找的点都找完了
    {
        int u=tree.tag[1];
        tree.update(u,1,tot,1,INF);//走过的点设为INF，相当于vis数组
        for(int i=head[u];i;i=e[i].next)
        {
            int v=e[i].v,w=e[i].w;
            if(d[v]>d[u]+w)
            {
                d[v]=d[u]+w;
                tree.update(v,1,tot,1,d[v]);//树上更新
            }
        }
    }
    if(d[tot]==INF) cout<<"NO SOLUTION";
    else cout<<d[tot];
} 
```

为什么还是过不了啊，递归线段树的常数这么大吗 $qwq$  
等一下，我们只需要单点修改，查询都不用  
那我们为什么不写一棵常数很小，代码又短的zkw线段树呢

```cpp
struct segment_tree
{
	int bit;
	int minx[1100001],tag[1100001];//真的是习惯了写sum，当成最小值看就行了
	void push_up(int n)
	{
		minx[n]=min(minx[n<<1],minx[n<<1|1]);
		tag[n]=minx[n<<1]<minx[n<<1|1]?tag[n<<1]:tag[n<<1|1];
	}
	void build(int n)
	{
		for(bit=1;bit<=n+1;bit<<=1);
		for(int i=bit+1;i<=(bit<<1)-1;++i)
		{
        	 //注意这里结束循环的条件为(bit<<1)-1，这是因为zkw线段树需要把叶子填满，
             //如果不填满的话最后就会有编号大于n的点值为0，树根始终为0，陷入死循环
			 minx[i]=i-bit==1?0:INF;//将出发点的dis值设为0
			 tag[i]=i-bit;
		}
		for(int i=bit-1;i>=1;--i)
			push_up(i);
	}
	void update(int n,int k)
	{
		for(minx[n+=bit]=k,n>>=1;n;n>>=1)
			push_up(n);
	}
}tree;
```
至此，就可以满分通关啦！

---

## 作者：NY_YN (赞：9)

### [题目传送门](https://www.luogu.org/problemnew/show/P4667)
1.方法

		双端队列BFS
2.思路

		建一个无向图，若X到Y与原有线重合，边权为0，否则为1。（要经过一次操作），然后在无向图中求从左上到右下的最短距离。
        因为边权要么0要么1，我们可以使用双端队列BFS。如果边权为0，将要到达的点加入队首，否则加队尾。
        然后就是R+C为奇数时是无解的情况。（简单证一下）
3.代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 500010;
int dis[510][510];
char g[510][510];
pair<int, int> q[MAXN * 2];
int r, c, head, tail;
inline bool check (int x, int y) 
{
	return x >= 0 && x <= r && y >= 0 && y <= c;
	}
inline void add (int x, int y, int v)
{
    if (dis[x][y] < 0 || v < dis[x][y])
    {
        dis[x][y] = v;
        if (head == tail || v > dis[q[head].first][q[head].second]) q[tail++] = make_pair(x, y);
        else q[--head] = make_pair(x, y);
    }
}
int main ()
{
       scanf("%d %d", &r, &c);
        if ((r + c) % 2)
        {
            for (int i = 0; i < r; i++) scanf("%s", g[i]);
           printf("NO SOLUTION\n");
        }
        else
        {
            for (int i = 0; i < r; i++) scanf("%s", g[i]);
            head = tail = MAXN; q[tail++] = make_pair(0, 0);
            memset(dis, -1, sizeof dis), dis[0][0] = 0;
            while (head != tail)
            {
                int cx = q[head].first, cy = q[head].second; ++head;
                if (check(cx - 1, cy - 1))
                {
                    if (g[cx - 1][cy - 1] == '\\') add(cx - 1, cy - 1, dis[cx][cy]);
                    else add(cx - 1, cy - 1, dis[cx][cy] + 1);
                }
                if (check(cx - 1, cy + 1))
                {
                    if (g[cx - 1][cy] == '/') add(cx - 1, cy + 1, dis[cx][cy]);
                    else add(cx - 1, cy + 1, dis[cx][cy] + 1);
                }
                if (check(cx + 1, cy - 1))
                {
                    if (g[cx][cy - 1] == '/') add(cx + 1, cy - 1, dis[cx][cy]);
                    else add(cx + 1, cy - 1, dis[cx][cy] + 1);
                }
                if (check(cx + 1, cy + 1))
                {
                    if (g[cx][cy] == '\\') add(cx + 1, cy + 1, dis[cx][cy]);
                    else add(cx + 1, cy + 1, dis[cx][cy] + 1);
                }
            }
            printf("%d\n", dis[r][c]);
        }
    return 0;
}
```

---

## 作者：qsmoonzh (赞：8)

大佬都用线段树qwq

我来篇手写堆优化dij的题解吧qwq

# 思路分析：
要求旋转最少的边使得能从左上角到右下角

把各个正方形的顶点看做结点，从0到(n+1)*(m+1)-1

共(n+1)*(m+1)个结点

先把题目给的边存好(暂且称作实边)

然后把实边旋转90°(\变为/，/变为\\)，成为虚边，存好

因为虚边需要旋转一次才能得到，所以一条路径要经过虚边要付出代价1

那么实边的边权为0，虚边的边权为1

然后以左上角为起点，跑dij求最短路，dis[(n+1)*(m+1)-1]即为答案

# 注意事项
本题容易超时

priority_queue常数稍大，不开O2会超时(88分左右)

那就用手写堆

(priority_queue 2510ms)(手写堆 1100ms)


------------


**空间：**

点数260000够了

边数260000<<2。边数为n\*m的四倍(题目给了n\*m条边(边权为0)，我们加了n\*m条旋转后的边权为1的边，又因为是双向边，所以再\*2)
~~我一开始边数都数错了qwq70分~~

堆和边数一样 **注意不是和点数一样**(第一份代码)



------------


i表示结点编号，v表示入堆时的dis[i] 

最多可能有4\*n\*m个点要存到堆里面，即边数

堆里面可能同时存在i相等的元素，但它们v不相等

因为dis[i]可能被多次更新(每次更新v都减小)，每次更新都要扔堆里

更新次数与边数有关，所以最多可能有4\*n\*m个点在堆里面

dij中，当一个元素a出堆时(a.v==dis[a.i])，堆中其它i=a.i的元素都没用了(因为a.v一定是最小的) 

所以dij中有 if(x.v!=dis[x.i]) continue;详见第一份代码函数dij，第二份代码不需要这行 

还有就是堆里面不能只存结点编号i而通过dis[i]来调整堆(第二份代码进行了一点处理，所以就可以了)

(因为dis[i]可能被多次更新，只存结点编号i而通过dis[i]来调整堆的话

每次dis[i]更新(若不调整相应元素的位置)可能会破坏堆的性质,若要从堆中找到i的位置，然后进行调整，就要用一个数组y记录每个结点在堆中的位置
并在结点在堆中的位置发生变化时维护y(这样每个结点对应一个元素))(详见第二份代码)

我写过只存结点编号的堆，~~导致我很长一段时间不敢手写堆，~~很久之后才知道怎么错了，所以希望大家不要重蹈覆辙qwq

还有一些注意事项看注释

# 代码

若a表示总点数，b表示总边数

**第一份代码(1100ms)**

最多b次入堆，堆中最多b个元素

时间复杂度应该是O(b*log(b))

**第二份代码(1183ms)**

用一个数组y记录每个结点在堆中的位置，y[i]表示结点i在堆中的位置

每次dis[i]更新时，调整位置为y[i]的元素在堆中的位置，而不是新添加一个元素到堆里面

最多b次入堆，堆中最多a个元素

时间复杂度应该是O(b*log(a))

而且堆的元素可以不存v，直接用dis[i]进行比较也可以(在第二份代码里面，所有结点v=dis[i])

应该和线段树优化的一样qwq

**不知道有没有搞错复杂度qwq**

**不过**

第一份代码和第二分代码耗时没什么差别

因为a,b相差不大，log(b)和log(a)没什么区别

# 第一份代码：
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

struct node {
	int to,v,next;
} e[260000<<2];//这是边
struct qwq {
	int i,v;//i表示结点编号，v表示入堆时的dis[i] 
	bool operator <(const qwq &the)const {
		return v<the.v;
	}
} dui[260000<<2],z;//这是堆，

int n,m,head[260000],dis[260000],ie,id;
char ch;
void adde(int a,int b,int c) {//数组模拟邻接表储存 
	e[++ie].next=head[a];
	e[ie].to=b;
	e[ie].v=c;
	head[a]=ie;
	return ;
}
void din(qwq p) {//扔进堆里 
	dui[++id]=p;
	int x=id;
	while(dui[x]<dui[x>>1])//向上调整，维护堆的性质 
		swap(dui[x],dui[x>>1]),x>>=1;
	return ;
}
qwq dout() {//弹出dui[1]，并返回 
	int x=1;
	qwq ans=dui[1];
	dui[1]=dui[id--];
	while(1) {
		x<<=1;//x<<=1后必然是偶数，偶数|1等价于+1 
		if(x>id) break;//防止越界 
		if(x+1<=id&&dui[x|1]<dui[x])//确定选择x还是x+1(选最小的) 
			x|=1;//dui[x|1]<dui[x]注意<符号，不能用>，因为只重载了< 
		if(dui[x]<dui[x>>1])//调整 
			swap(dui[x],dui[x>>1]);
		else break;
	}
	return ans;
}
void dij() {
	qwq x;
	memset(dis,0x3f,4*(n+1)*(m+1+1));//4*(n+1)*(m+1),4*(n+1)*(m+1+1)这样写保险一点
	dis[0]=0;
	z.i=0,z.v=0;
	din(z);
	while(id) {//id是堆内元素的个数，从1开始编号(不能从0)
		x=dout();
		if(x.v!=dis[x.i]) continue;
		//x.v==dis[x.i]表示x.i这个结点第一次出堆
		//(保证dis[x.i]最小,无法再更新，即确定起点到x.i的最短路) 
		//x.v!=dis[x.i]时x.i这个结点已经出过堆了，x.v必定大于dis[x.i]，所以跳过 
		for(int i=head[x.i]; i; i=e[i].next)
			if(dis[e[i].to]>dis[x.i]+e[i].v) {//更新dis 
				dis[e[i].to]=dis[x.i]+e[i].v;
				z.i=e[i].to,z.v=dis[e[i].to];
				din(z);//扔堆里 
			}
	}
	return ;
}
int main() {
	scanf("%d %d",&n,&m);
	for(int i=0,v,u,f; i<n; i++)
		for(int j=0; j<m; j++) {
			ch='0';//为了进入循环
			while(ch!='\\'&&ch!='/') scanf("%c",&ch);//防止读到'\n'等东西
			if(ch=='\\') f=0;//'\\'才表示 字符\ 。类似地，要输出百分号printf("%%");
			else f=1;//f确定边权 
			v=i*(m+1)+j;//左上角
			u=(i+1)*(m+1)+j+1;//右下角
			adde(v,u,f);//如果是\，那么左上角与右下角之间的边权为0，若是/则为1
			adde(u,v,f);
			v=(i+1)*(m+1)+j;//左下角
			u=i*(m+1)+j+1;//右上角
			adde(v,u,f^1);//如果是/，那么左下角与右上角之间的边权为0，若是\则为1
			adde(u,v,f^1);//0^1=1,1^1=0
		}
	dui[0].v=-1;
	dij();
	if(dis[(n+1)*(m+1)-1]==0x3f3f3f3f)//最终答案是dis[(n+1)*(m+1)-1]
		printf("NO SOLUTION");
	else printf("%d",dis[(n+1)*(m+1)-1]);
	return 0;
}
```

# 第二份代码：
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

struct node {
    int to,v,next;
} e[260000<<2];
struct qwq {
    int i,v;
    bool operator <(const qwq &the)const {
        return v<the.v;
    }
} dui[260000],z;//这里的堆最多存500*500个元素 
int n,m,head[260000],dis[260000],ie,id,y[260000];
char ch;
void adde(int a,int b,int c) {
    e[++ie].next=head[a];
    e[ie].to=b;
    e[ie].v=c;
    head[a]=ie;
    return ;
}
void dup(int x)//将堆中第x个位置向上调整 
{
    while(dui[x]<dui[x>>1])
        swap(y[dui[x].i],y[dui[x>>1].i]),swap(dui[x],dui[x>>1]),x>>=1;//维护y 
    return ;
}
void din(qwq x) {
    dui[++id]=x;
    y[x.i]=id;//
    dup(id);
    return ;
}
qwq dout() {
    int x=1;
    qwq ans=dui[1];
    y[dui[1].i]=0;//
    dui[1]=dui[id--];
    y[dui[1].i]=1;//
    while(1) {
        x<<=1;
        if(x<id&&dui[x|1]<dui[x]) x|=1;
        if(x<=id&&dui[x]<dui[x>>1])
            swap(y[dui[x].i],y[dui[x>>1].i]),swap(dui[x],dui[x>>1]);//维护y 
        else break;
    }
    return ans;
}
void dij() {
    qwq x;
    memset(dis,0x3f,4*(n+1)*(m+1+1));
    dis[0]=0;
    z.i=0,z.v=0;
    din(z);
    while(id) {
        x=dout();
        for(int i=head[x.i]; i; i=e[i].next)
            if(dis[e[i].to]>dis[x.i]+e[i].v) {
                dis[e[i].to]=dis[x.i]+e[i].v;
                if(y[e[i].to]==0) {//y[e[i].to]==0说明结点 e[i].to不在堆里 
                    z.i=e[i].to,z.v=dis[e[i].to];
                    din(z);
                }
                else {//更新调整 
                    dui[y[e[i].to]].v=dis[e[i].to];
                    dup(y[e[i].to]);//因为dui[y[e[i].to]].v变小了，所以一定是向上调整 
                }
            }
    }
    return ;
}
int main() {
	scanf("%d %d",&n,&m);
	for(int i=0,v,u,f; i<n; i++)
		for(int j=0; j<m; j++) {
			ch='0';
			while(ch!='\\'&&ch!='/') scanf("%c",&ch);
			if(ch=='\\') f=0;
			else f=1;
			v=i*(m+1)+j;
			u=(i+1)*(m+1)+j+1;
			adde(v,u,f);
			adde(u,v,f);
			v=(i+1)*(m+1)+j;
			u=i*(m+1)+j+1;
			adde(v,u,f^1);
			adde(u,v,f^1);
		}
	dui[0].v=-1;
	dij();
	if(dis[(n+1)*(m+1)-1]==0x3f3f3f3f)
		printf("NO SOLUTION");
	else printf("%d",dis[(n+1)*(m+1)-1]);
	return 0;
}
```

---

## 作者：GK0328 (赞：7)

既然没有题解，那我就来发一波吧。

其实这道题的思路是比较明显的，跑一波最短路就好了。。。

具体怎么做呢？

考虑一个方格，设左上角为（i,j）,则右上角为（i,j+1）,左下角为（i+1,j）,右下角为（i+1,j+1）。

①该方格为'\'：

可以这样看，从（i,j）到（i+1,j+1）不需要花费，建一条权值为0的边，从（i,j+1）到（i+1,j）需要花费1，建一条权值为1的边。

②该方格为'/'：

同理，从（i,j）到（i+1,j+1）需要花费1，建一条权值为1的边，从（i,j+1）到（i+1,j）不需要花费，建一条权值为0的边。

然后把坐标转换为一个数（瞎搞就行）。

完事啦。。。

时限很小，我用了线段树优化dijstra。

Pascal Code：

```cpp
var
  d,head,next,l1,l2,tree,id,wz:array[0..1000005]of longint;
  h,l,i,j,n,ll,w,v,u,oo,x,y,num:longint;
  ch:char;
function wzl(x,y:longint):longint;
begin
  exit((x-1)*(l+1)+y);
end;
procedure add(x,y,z:longint);//链式前向星
begin
  inc(num);
  l1[num]:=y;
  l2[num]:=z;
  next[num]:=head[x];
  head[x]:=num;
end;
procedure build(p,l,r:longint);//建树
var
  mid:longint;
begin
  if l=r then
  begin
    tree[p]:=d[l];
    id[p]:=l;//记录id
    wz[l]:=p;
    exit;
  end;
  mid:=(l+r) div 2;
  build(p+p,l,mid);
  build(p+p+1,mid+1,r);
  if tree[p+p]<=tree[p+p+1] then
  begin
    tree[p]:=tree[p+p];
    id[p]:=id[p+p];
  end else
  begin
    tree[p]:=tree[p+p+1];
    id[p]:=id[p+p+1];
  end;
end;
procedure change(p:longint);
begin
  if p=0 then
    exit;
  if tree[p+p]<=tree[p+p+1] then
  begin
    tree[p]:=tree[p+p];
    id[p]:=id[p+p];
  end else
  begin
    tree[p]:=tree[p+p+1];
    id[p]:=id[p+p+1];
  end;
  change(p div 2);
end;
begin
  readln(h,l);
  for i:=1 to h do
  begin
    for j:=1 to l do
    begin
      read(ch);
      case ch of//建边
        '\':begin
              x:=wzl(i,j);
              y:=wzl(i+1,j+1);
              add(x,y,0);
              add(y,x,0);
              x:=wzl(i+1,j);//wzl，坐标转换为一个数
              y:=wzl(i,j+1);
              add(x,y,1);
              add(y,x,1);
            end;
        '/':begin
              x:=wzl(i,j);
              y:=wzl(i+1,j+1);
              add(x,y,1);
              add(y,x,1);
              x:=wzl(i+1,j);
              y:=wzl(i,j+1);
              add(x,y,0);
              add(y,x,0);
            end;
      end;
    end;
    readln;
  end;
  n:=wzl(h+1,l+1);//计算终点，起点显然是1
  oo:=100000005;
  for i:=1 to n do//开始dijstra
    d[i]:=oo;
  d[1]:=0;
  build(1,1,n);
  ll:=head[1];
  while ll<>0 do//初始化，其实可以不用
  begin
    w:=l1[ll];
    v:=l2[ll];
    d[w]:=v;
    tree[wz[w]]:=v;
    change(wz[w] div 2);
    ll:=next[ll];
  end;
  for i:=2 to n do//改成while较方便
  begin
    if tree[1]=oo then//特判，防卡常
      break;
    u:=id[1];
    tree[wz[u]]:=oo;
    change(wz[u] div 2);
    ll:=head[u];
    while ll<>0 do
    begin
      w:=l1[ll];
      v:=l2[ll];
      if d[w]>d[u]+v then
      begin
        d[w]:=d[u]+v;
        tree[wz[w]]:=d[w];
        change(wz[w] div 2);
      end;
      ll:=next[ll];
    end;
  end;
  if d[n]>=oo then//输出
    writeln('NO SOLUTION') else
    writeln(d[n]);
end.
```

---

## 作者：feilongz (赞：6)

提交超多通过率超低的题，总而言之算法秒掉了，然而在图论上本人自带不初始化buff。

算法：我们把可以不旋转通过的边标记为0，需要旋转的标记为1，跑一次单源最短路，从左上到右下，易发现最短距离就是需要旋转的次数。

（我们可以看成每次要用到旋转后的边，需要耗费1的价值，最后价值总和当然就是答案。）

我们这样想，这是个图。可以数出来，节点数应当是（R+1）\*（C+1），如样例。

当然，出发点是1号点，问题是，如何表达这些节点才能让我们清楚确认右下角的坐标呢？

我的思路是建图的时候，按如下方式分配点的编号。

1  2  3  4    5  6

7  8  9  10 11 12

...当然这是样例。我们可以发现，对于每个方格，需要标记四个点，四个点坐标可以轻易求得。

这就是这部分的作用：


```cpp
                  int pos1=((i-1)*(C+1)+j);    //左上 
                int pos2=(i*(C+1)+j+1);      //右下 
                int pos3=((i-1)*(C+1)+j+1);  //右上 
                int pos4=(i*(C+1)+j);        //左下 
```
我们确定了四个点的位置，接下来就只需要连边了。（好在这道题对于内存没限制，随便开简直爽。）
如果'/'就右上到左下连边，这条边权值为0（val=0）。连边要连双向（未证实，我这么连得。）

同时也要双向的连一条从左上到右下的边，权值为1，表示旋转后的边。

如果是’\‘则反之。


图建好了，对于如此稠密的图我选择heap优化的dijkstra。不清楚其他单源能否过，但多源估计过不了。

最后答案就是1到（R+1）\*（C+1）的最短路啦。


这个巧妙的思路使得这道让人摸不着头脑的题简单明了了很多，思维清晰应该能秒出算法吧。

记住是多组数据，每次要初始化dis，vis（flag），e，pre等数组。

注意！！！！链式前向星一定要清空tot，不清空tot会有巨量内存占用（亲测几百倍内存才AC）每次清空了就会从一开始存边了。


少走弯路。

P.S.个人觉得这道题应当是NOIP提高或以上。

上代码。




   
        

        
    
        
```cpp
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define pa pair<int,int>
#define INF 2147483647
using namespace std;
priority_queue<pa,vector<pa>,greater<pa> >q;  //优先队列，heap
struct node
{
    int to;
    int val;
    int next;
}e[4*501*501];                                                 //链式前向星标准struct，大小值得注意。
int dis[501*501];
int flag[501*501];
int pre[4*501*501];
int tot=0;
void Add(int x,int y,int v)                                         //添加单向边。
{
    tot++;
    e[tot].next=pre[x];
    pre[x]=tot;
    e[tot].to=y;
    e[tot].val=v;
}
int dij(int t)                                     //t开始的堆优dij，代码不做过多注释。
{
   memset(flag,0,sizeof(flag));
   dis[t]=0;
   q.push(make_pair(dis[t],t));
   while(!q.empty())
   {
    pa now=q.top();
    q.pop();
    if(flag[now.second])
      continue;
    flag[now.second]=1;
    for(int i=pre[now.second];i;i=e[i].next)
      if(dis[now.second]+e[i].val<dis[e[i].to])
        {
            dis[e[i].to]=dis[now.second]+e[i].val;
            if(!flag[e[i].to])
              q.push(make_pair(dis[e[i].to],e[i].to));
        }
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int R,C;
        tot=0;
        memset(e,0,sizeof e);                                   //清空。
        memset(pre,0,sizeof pre);
        scanf("%d %d",&R,&C);
        for(int i=1;i<=R;++i)
        {
          char s[510];
              scanf("%s",&s);
          for(int j=1;j<=C;++j)
          {
          if(s[j-1]=='/')
              {
                  int pos1=((i-1)*(C+1)+j);    //左上 
                int pos2=(i*(C+1)+j+1);      //右下 
                int pos3=((i-1)*(C+1)+j+1);  //右上 
                int pos4=(i*(C+1)+j);        //左下 
                Add(pos1,pos2,1);                           //向四个方向加边。
                Add(pos2,pos1,1);
                Add(pos3,pos4,0);
                Add(pos4,pos3,0);
            }
          else
            {
                int pos1=((i-1)*(C+1)+j);
                int pos2=(i*(C+1)+j+1);
                int pos3=((i-1)*(C+1)+j+1);
                int pos4=(i*(C+1)+j);
                Add(pos1,pos2,0);                         //这里是“反之”
                Add(pos2,pos1,0);
                Add(pos3,pos4,1);
                Add(pos4,pos3,1);
            }
        }
       }
    for(int i=1;i<=(R+1)*(C+1);++i)
          dis[i]=INF;                                   //初始格dis数组。
      dij(1);                                                   //跑dij
//    for(int i=1;i<=24;++i)
//    {
//      printf("%d ",dis[i]);
//      if(i%6==0)
//        printf("\n");
//    }
  if(dis[(R+1)*(C+1)]==INF)                              //无解情况，没有最短路（虽然不太确定是什么情况）
    printf("NO SOLUTION\n");
   else 
     printf("%d\n",dis[(R+1)*(C+1)]);                          //输出结果。结果是到右下角的最短路。
     }   
//AC by fz
}
```

---

## 作者：LuukLuuk (赞：4)

# 题解：P10486 电路维修

题目大意：有一个 $R \times C$ 的矩阵 $s$，$s_{i,j}$ 可能是左斜线或右斜线，分别表示可以从左上走到右下，右上走到左下，你要通过尽可能少地改变 $s$ 中斜线的方向从矩阵的左上角走到右下角。

考虑广搜，枚举走到的四个方向。若不能直接走到（相应格子斜线方向不对应），要么花费 $1$ 的代价直接过去，要么通过其他路绕过去。

那怎么让任意一个点都能在被判断不可到达之前可以通过其他深度更大的路径过去呢？我们就可以手动修改搜索顺序实现，具体做法就是优先访问可以直接到达的点。

到了这一步，方法就多起来了，我们可以用优先队列实现，手动设置优先级，但因为~~原题目有双端队列的标签~~本题目每一格只有两种情况，刚好对应队列的两个开口，因此我们也可以用双端队列实现，例如我的做法：当可以直接到达，直接塞到队头，反之塞到队尾，记录的 $ans$ 加上一。

代码如下:
```c
#include <cstring>
#include <cstdio>
#include <queue>
#include <cmath>
using namespace std;

int xx[] = {1, -1, -1, 1}, yy[] = {-1, 1, -1, 1};
struct point {
	int x, y, ans;
} ;
int vis[510][510];
char s[510][510];
int n, m, t;

bool check(int x, int y) {
	if (x < 1 || n + 1 < x || y < 1 || m + 1 < y)	return 1;
	if (vis[x][y])	return 1;
}

void bfs() {
	deque<point> que;
	que.push_back({1, 1, 0});
	while (!que.empty()) {
		point now = que.front();
		que.pop_front();
		int x = now.x, y = now.y, ans = now.ans;
		if (x == n + 1 && y == m + 1) {
			printf("%d\n", ans);
			break;
		}
		if (check(x, y))	continue;
		vis[x][y] = 1;
		if (s[x][y - 1] == '/') {
			que.push_front({x + 1, y - 1, ans});
		} else {
			que.push_back({x + 1, y - 1, ans + 1});
		}
		if (s[x - 1][y] == '/') { 
			que.push_front({x - 1, y + 1, ans});
		} else {
			que.push_back({x - 1, y + 1, ans + 1});
		}
		if (s[x - 1][y - 1] == '\\') {
			que.push_front({x - 1, y - 1, ans});
		} else {
			que.push_back({x - 1, y - 1, ans + 1});
		}
		if (s[x][y] == '\\') {
			que.push_front({x + 1, y + 1, ans});
		} else {
			que.push_back({x + 1, y + 1, ans + 1});
		}
	}
} 

int main() {
	scanf("%d", &t);
	while (t--) {
		memset(s, 0, sizeof s);
		memset(vis, 0, sizeof vis);
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i) {
			scanf("%s", s[i] + 1);
		}
		bfs();
		if (abs(m - n) % 2) { 
			printf("NO SOLUTION\n");
			continue;
		}
	} 
	return 0;
}
```

---

## 作者：Wight_sl (赞：3)

# 思路：

每条电线要么需要转向，要么不需要转向，如果不用转向就能走通，不转向的情况，肯定是比转向要好的。所以如果搜索的时候先搜不转向的，再搜转向的，那速度会快很多。（使用双端队列）如果不需要转向，那就从队首入队，这样就可以先搜到，需要转向就在队尾入队，搜完了不转向的才会搜这些，出队的话就统一从队首出去即可。判断经过的电线要走的方向是否跟原图的方向一致，如果要转向，队首入队，步数加一，要不然队尾入队，步数还是原来的不变，可以使用一个二维数组去记忆化每个格子的步数，~~然后就没有然后了~~。

# 代码实现

```cpp
#include<bits/stdc++.h>
#define N 505
#define IOS ios::sync_with_stdio(false)
#define IN cin.tie(NULL)
#define OUT cout.tie(NULL)
using namespace std;
const int dx[4]={1,-1,-1,1};
const int dy[4]={1,1,-1,-1};
const int ix[4]={0,-1,-1,0};
const int iy[4]={0,0,-1,-1};
const char c[5]="\\/\\/";
deque<int> q,qu;
char a[N][N];//存图
int v[N][N],n,m,t;//记忆化数组
void BFS(){
	//初始化，因为要求最小，所以要设最大 
	for(int i=0;i<=n;i++){
		for(int j=0;j<=m;j++){
			v[i][j]=INT_MAX;
		}
	}
	q.push_back(0);
	qu.push_back(0);
	v[0][0]=0; 
	while(!q.empty()){
		int xx=q.front();
		int yy=qu.front();
		q.pop_front();
		qu.pop_front();
		for(int i=0;i<4;i++){
			int dnx=xx+dx[i];
			int dny=yy+dy[i];
			int inx=xx+ix[i];
			int iny=yy+iy[i];
			if(dnx>=0&&dnx<=n&&dny>=0&&dny<=m){//判断是否越界 
				if(c[i]!=a[inx][iny]){//需要转向 
					int t=v[xx][yy]+1;//因为需要转向，所以步数需要加一 
					if(t<v[dnx][dny]){
						q.push_back(dnx);
						qu.push_back(dny);
						v[dnx][dny]=t; 	
					}
				}
				else{//不用转向 
					int t=v[xx][yy];//因为不用转向，所以赋值即可 
					if(t<v[dnx][dny]){//同上 
						q.push_front(dnx);
						qu.push_front(dny);
						v[dnx][dny]=t;	
					}
				}
			}
		}
	}
	cout<<v[n][m]<<endl;
}
int main(){
	IOS;IN;OUT; 
	int t;
	cin>>t;
	while(t--){
		cin>>n>>m; 
		for(int i=0;i<n;i++) cin>>a[i];
		if((n+m)%2==1) cout<<"NO SOLUTION"<<endl;//判断是否能到达终点//因为沿对角线走时横纵坐标的和一定是偶数，所以只要判断一下重点横纵坐标的和是否是偶数即可。
		else BFS();
	}
	return 0;		
}

---

## 作者：Akaina (赞：3)


### 电路维修

这道题的解法是先建边，对于每一个单位正方形，将有边相连的两个对角建一条长度为0的无向边，另外两个对角建一条长度为1的无向边。然后可以跑最短路或者用**双端队列bfs**(**0-1bfs**)。

跑最短路的话要注意由于是网格图spfa会炸掉，所以要用堆优化的dijkstra( ~~不会不加堆优化的dijkstra (^_^)~~  )

因为在练习广搜，所以我用的是双端队列bfs

当我们遇到边权只有1的情况时，显然直接bfs，然后第一次访问到某个点的“时间”就是到它的最短路径

当边权同时存在1和0两种情况时，我们就可以采用双端队列bfs，也叫作0-1bfs，就是访问时，若边权为0，则把目标点v放在队首，若边权为1，则把目标点放在队尾，这样是为了使得边权为0时的目标点v先被访问。

我按照这个思路做了，但却WA了，后来我一看题解，队列里维护的居然不是点，而是边，我一直想不通为什么，找了半天也只有题解模糊地写到，然后我就自己手玩了一把，发现如果是维护点，那么有可能会出现这样的情况：显然如果边权为0，那么目标点v与点u应该处于广搜的同一层，但如果是维护点，就可能会出现点v在被点u访问到之前被下一层的点提前访问了（也就是由这一层的点通过边权为1的边得到的目标点vv访问过来（因为如果是维护点，那么就会像是一个深搜的过程，会在我把这一层访问完之前，下一层的点先把这一层的点访问了））。但如果我们是维护边的话，那么将会起到一个滞留的作用，能够留给我时间，让我先把这一层的访问完了，在访问下一层。

这是我WA掉的访问点的代码（注释掉的是我手玩搜索过程的代码）

```c++
#include <iostream>
#include <queue>
#include <deque>
#include <cstdio>
#include <cstring>
using namespace std;
#define Maxn 280000
int n,m;
deque<int>q;
int fir[Maxn],nxt[Maxn*2],vv[Maxn*2],edg[Maxn*2];
int tot=0,ans=0;
int vis[Maxn],dis[Maxn];
void add(int u,int v,int w)
{
    nxt[++tot]=fir[u];
    fir[u]=tot;
    vv[tot]=v;
    edg[tot]=w;
}
//int room[1000];
int id(int x,int y){return (x-1)*(m+1)+y;}
void bfs()
{
    memset(dis,-1,sizeof(dis));
    q.push_front(id(1,1));vis[id(1,1)]=1;dis[id(1,1)]=0;
    while(!q.empty())
    {
   //    int cnt=0;
   //     printf("q:");
    //    while(!q.empty())
     //   {
     //       room[++cnt]=q.front();q.pop_front();
     //       printf("%d ",room[cnt]);
     //   }
     //   printf("\n");
      //       for(int i=cnt;i>=1;i--)q.push_front(room[i]);
        int u=q.front();q.pop_front();
     //   printf("u=%d dis[u]=%d\n",u,dis[u]);
        for(int i=fir[u];i;i=nxt[i])
        {
           // printf("u->v: %d->%d\n",u,vv[i]);
            int v=vv[i];
            if(vis[v]==1)continue;
            vis[v]=1;
            dis[v]=dis[u]+edg[i];
            if(v==id(n+1,m+1))return;
            if(edg[i]==0)q.push_front(v);
            else q.push_back(v);
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        string str;cin>>str;
        for(int j=1;j<=m;j++)
        {
            int x1=id(i,j),x2=id(i+1,j+1),y1=id(i+1,j),y2=id(i,j+1);
            if(str[j-1]=='/')
            {
                add(x1,x2,1);add(x2,x1,1);
                add(y1,y2,0);add(y2,y1,0);
            }
            else
            {
                add(x1,x2,0);add(x2,x1,0);
                add(y1,y2,1);add(y2,y1,1);
            }
        }
    }
    bfs();
 /*           for(int i=1;i<=n+1;i++)
        for(int j=1;j<=m+1;j++)
        printf("id(%d,%d)=%d\n",i,j,id(i,j));
    for(int i=1;i<=id(n+1,m+1);i++)
        printf("dis[%d]=%d\n",i,dis[i]);
    printf("id(n+1,m+1)=%d\n",id(n+1,m+1));printf("dis[%d]=%d\n",id(n+1,m+1),dis[id(n+1,m+1)]);*/
    if(dis[id(n+1,m+1)]==-1)printf("NO SOLUTION\n");
    else printf("%d\n",dis[id(n+1,m+1)]);
    return 0;
}

```

这是正解

```c++
#include <iostream>
#include <queue>
#include <deque>
#include <cstdio>
#include <cstring>
using namespace std;
#define Maxn 2800000
int n,m;
deque<int>q;
int fir[Maxn],nxt[Maxn*4],uu[Maxn*4],vv[Maxn*4],edg[Maxn*4];
int tot=0,ans=0;
int vis[Maxn],dis[Maxn];
void add(int u,int v,int w)
{
    nxt[++tot]=fir[u];
    fir[u]=tot;
    uu[tot]=u;
    vv[tot]=v;
    edg[tot]=w;
}
int id(int x,int y){return (x-1)*(m+1)+y;}
void bfs()
{
    memset(dis,-1,sizeof(dis));
    memset(vis,0,sizeof(vis));
    q.clear();
    q.push_front(id(1,1));vis[id(1,1)]=1;dis[id(1,1)]=0;
    while(!q.empty())
    {
        int e=q.front();q.pop_front();
        int u=uu[e];int v=vv[e];
        if(vis[v]==1)continue;
        vis[v]=1;
        dis[v]=dis[u]+edg[e];
        if(v==id(n+1,m+1))return;
        for(int i=fir[v];i;i=nxt[i])
        {
            if(vis[vv[i]]==1)continue;
            if(edg[i]==0)q.push_front(i);
            else q.push_back(i);
        }
    }
}
int main()
{
    int T;scanf("%d",&T);
    while(T--)
    {
        tot=0;memset(fir,0,sizeof(fir));
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
        {
            string str;cin>>str;
            for(int j=1;j<=m;j++)
            {
                int x1=id(i,j),x2=id(i+1,j+1),y1=id(i+1,j),y2=id(i,j+1);
                if(str[j-1]=='/')
                {
                    add(x1,x2,1);add(x2,x1,1);
                    add(y1,y2,0);add(y2,y1,0);
                }
                else
                {
                    add(x1,x2,0);add(x2,x1,0);
                    add(y1,y2,1);add(y2,y1,1);
                }
            }
        }
        bfs();
        if(dis[id(n+1,m+1)]==-1)printf("NO SOLUTION\n");
        else printf("%d\n",dis[id(n+1,m+1)]);
    }
    return 0;
}

```

[个人博客](<https://www.cnblogs.com/LianQ/>)







---

## 作者：夏色祭 (赞：3)

#没有P党的题解，那我来补一发

#这题卡了我14次提交。。。最后把数组开小点就过了（玄学）

楼下大佬用的都是dij+堆，那我来说一下SPFA吧。。。

把输入的'/'‘\’看成一条边，不改变的情况下权值为0，否则为1。。。

然后用SPFA跑一遍最短路就行了。。。

注意：用来存结点的数组要开大一点。因为从一个点最多只能扩散到斜对角的四个点，所以存边的数组只要开**点的个数\*4**就行了，开**点的个数\*4**就行了。

另外就直接跑最朴素的SPFA和祈祷不要超（wei）时（diao）就行了。。。

#妖怪吧

献上丑陋的AC代码：

```cpp
const
  maxn=300000;
var
  f:array[0..15000000]of longint;
  b:array[0..maxn]of boolean;
  sum:array[0..maxn]of longint;
  a,tt:array[0..maxn,1..4]of longint;
  dis:array[0..maxn]of longint;
  n,m,tututu,i,j,h,t,x,y:longint;
  c:char;
procedure zz(x,y,z:longint);
begin
  inc(sum[x]);
  a[x,sum[x]]:=y;
  tt[x,sum[x]]:=z;
  inc(sum[y]);
  a[y,sum[y]]:=x;
  tt[y,sum[y]]:=z;
end;
begin
  readln(tututu);
  while tututu>0 do 
    begin
      dec(tututu);//纪念被废号的dalao
      fillword(sum,sizeof(sum) div 2,0);
      readln(n,m);
      for i:=1 to n do 
        begin
          for j:=1 to m do 
            begin
              read(c);
              if c='\' then
                begin
                  x:=(i-1)*(m+1)+j;
                  y:=i*(m+1)+j+1;
                  zz(x,y,0);
                  x:=(i-1)*(m+1)+j+1;
                  y:=i*(m+1)+j;
                  zz(x,y,1);
                end 
                else 
                  begin
                    x:=(i-1)*(m+1)+j+1;
                    y:=i*(m+1)+j;
                    zz(x,y,0);
                    x:=(i-1)*(m+1)+j;
                    y:=i*(m+1)+j+1;
                    zz(x,y,1);
                  end;//存边，我们把矩阵每一行连接在一起，连成一条链，那原本要用二位存储的点就可以用一个整形表示了
            end;
          readln;
        end;
      fillword(b,sizeof(b) div 2,0);
      for i:=1 to (n+1)*(m+1) do dis[i]:=666666;//初始化
      dis[1]:=0;
      h:=0; 
      t:=1;
      f[1]:=1;
      b[1]:=true;
      while h<t do
        begin
          inc(h);
          x:=f[h];
          b[x]:=false;
          for i:=1 to sum[x] do 
            if dis[x]+tt[x,i]<dis[a[x,i]] then 
              begin
                dis[a[x,i]]:=dis[x]+tt[x,i];
                if not b[a[x,i]] then 
                  begin
                    inc(t);
                    f[t]:=a[x,i];
                    b[a[x,i]]:=true;
                  end;
              end;
        end;//SPFA
      if dis[(n+1)*(m+1)]=666666 then writeln('NO SOLUTION')
        else writeln(dis[(n+1)*(m+1)]);//输出
    end;
end.
```

---

## 作者：Wminz (赞：3)

```c
#include<cstdio>
#include<iostream>
#include<vector>
#include<cstring>
#include<queue>
using namespace std;
int n,r,c;char ch;int vis[510*510];int d[510*510];
struct Edge{
    int to,w;//to记录点，w记录距离
};
vector<Edge>g[510*510];//邻接表加结构体储存边和点
deque<int>q;//双端队列优化
void spfa(int i){
    memset(d,0x3f,sizeof(d));
    memset(vis,0,sizeof(vis));
    d[i]=0;vis[i]=1;q.push_front(i);
    while(!q.empty()){
        int f1=q.front();q.pop_front();vis[f1]=0;
        if(f1==(r+1)*(c+1)+5) return;
        for(int j=0;j<g[f1].size();j++){
            Edge e=g[f1][j];
            int to=e.to,s=e.w;
            if(d[f1]+s<d[to]){
                d[to]=d[f1]+s;
                if(vis[to]==0){
                    if(!q.empty()&&d[to]<=d[q.front()]) q.push_front(to);
                    //让离着终点近且距离短的点优先进入队列
                    else q.push_back(to); 
                    vis[to]=1;
                }
            }
        }
    }
}
int main(){
    cin>>n;
    for(int k=1;k<=n;k++){
        memset(g,0,sizeof(g));
        cin>>r>>c;
        for(int i=1;i<=r;i++)
        for(int j=1;j<=c;j++){
            cin>>ch;
            int a=(i-1)*(c+1)+j;int b=(i-1)*(c+1)+j+1;
            int C=i*(c+1)+j;int d=i*(c+1)+j+1;
            if(ch=='\\'){
                g[a].push_back((Edge){d,0});g[d].push_back((Edge){a,0});
                g[b].push_back((Edge){C,1});g[C].push_back((Edge){b,1});
            }
            if(ch=='/'){
                g[a].push_back((Edge){d,1});g[d].push_back((Edge){a,1});
                g[b].push_back((Edge){C,0});g[C].push_back((Edge){b,0});
            }
        }
    	spfa(1);
    	if(d[(r+1)*(c+1)]==0x3f3f3f3f)cout<<"NO SOLUTION\n";
    	else cout<<d[(r+1)*(c+1)]<<endl;
    }
    return 0;
}
```
附~双端队列代码应用
![]((https://graph.baidu.com/resource/1014f64e9df3ee0ab4f1401553996190.jpg)

---

## 作者：zzlh (赞：3)

### 题外话 
	能用最短路写的绝对不写搜索
### 题意
	给定一张全是'\'和'/'的图，求最少需要旋转多少次标准件才能使得左上角与右下角联通，如果永远不可能联通就输出'NO SOLUTION'
### 分析
	1、可以很清晰的看出，每个'/'或者'\'都连接了两个格点，那么也就相当于这两个点之间不需要旋转即可联通，因此我们把这两个格点之间的路径长设为0
    2、对于每个小格中的另两个没有被'/'或者'\'连接的格点，只需要将'/'或者'\'旋转一下就可以使其联通，所以我们把这两个格点之间的路径长度设为1
    3、之后我们可以建成一个边权为0或1的无向图，跑一个从左上角到右下角的最短路即可
    4、值得一提的是，由于我们是用格点在建图，所以格点的序号需要做一个简单的处理。举个例子，以n=5,m=5为例，每一行就会有6个点，且行数会有6行，因此我们需要跑从1到36的最短路
### 注意事项
	建议使用堆优化的dijsktra，不然裸SPFA会T4个点
### 代码
（SPFA TLE60分）
```cpp
#include<bits/stdc++.h>
#define N 250005
using namespace std;
struct node{
	int to,nxt,w;
}e[N*4];
int cnt=0,head[N*4];
void add(int u,int v,int c){
	//cout<<u<<" "<<v<<" "<<c<<endl;
	e[++cnt].to=v;e[cnt].nxt=head[u];head[u]=cnt;e[cnt].w=c;
}
queue<int>q;
char c[505][505];
int dis[N+5];
bool vis[N+5];
void SPFA(int s){
	q.push(s);
	dis[s]=0;
	while(!q.empty()){
		int x=q.front();
		q.pop();
		vis[x]=0;
		for(int i=head[x];i;i=e[i].nxt){
			int v=e[i].to;
			if(dis[v]>dis[x]+e[i].w){
				dis[v]=dis[x]+e[i].w;
				if(!vis[v]){
					vis[v]=1;
					q.push(v);
				}
			}
		}
	}
}
void clean(){
	memset(dis,0x3f3f3f3f,sizeof(dis));
	memset(e,0,sizeof(e));
	memset(head,0,sizeof(head));
	memset(vis,0,sizeof(vis));
	cnt=0;
}
int main(){
	//freopen("3.txt","r",stdin);
	int T;
	scanf("%d",&T);
	while(T--){
		clean();
		int n,m;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>c[i][j];
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(c[i][j]=='/'){
					add((i-1)*(m+1)+j,i*(m+1)+j+1,1);
					add(i*(m+1)+j+1,(i-1)*(m+1)+j,1);
					add((i-1)*(m+1)+j+1,i*(m+1)+j,0);
					add(i*(m+1)+j,(i-1)*(m+1)+j+1,0);
				}else{
					add((i-1)*(m+1)+j,i*(m+1)+j+1,0);
					add(i*(m+1)+j+1,(i-1)*(m+1)+j,0);
					add((i-1)*(m+1)+j+1,i*(m+1)+j,1);
					add(i*(m+1)+j,(i-1)*(m+1)+j+1,1);
				}
			}
		}
		SPFA(1);
		if(dis[(n+1)*(m+1)]==0x3f3f3f3f){
			printf("NO SOLUTION\n");
			continue;
		}
		printf("%d\n",dis[(n+1)*(m+1)]);
	}
	return 0;
}
	

```
（堆优化dijsktra AC100分）
```cpp
#include<bits/stdc++.h>
#define N 250005
#define m(a,b) make_pair(a,b)
using namespace std;
struct node{
	int to,nxt,w;
}e[N*6];
int dis[N*6];
bool vis[N*6];
struct cmp{
    bool operator()(int a,int b){
        return dis[a]>dis[b];
    }
};
priority_queue< pair<int,int> > q;
int cnt=0,head[N*6];
void add(int u,int v,int c){
	//cout<<u<<" "<<v<<" "<<c<<endl;
	e[++cnt].to=v;e[cnt].nxt=head[u];head[u]=cnt;e[cnt].w=c;
}
char c[505][505];
void DIJ(int s){
    q.push(m(0,s));
    dis[s]=0;
    while(!q.empty()){
        int x=q.top().second;
        q.pop();
        if(vis[x])continue;
        vis[x]=1;
        for(int i=head[x];i;i=e[i].nxt){
            int v=e[i].to;
            if(!vis[v]&&dis[v]>dis[x]+e[i].w){
                dis[v]=dis[x]+e[i].w;
                //vis[v]=1;
                q.push(m(-dis[v],v));
            }
        }
    }
}
void clean(){
	memset(dis,0x3f3f3f3f,sizeof(dis));
	memset(e,0,sizeof(e));
	memset(head,0,sizeof(head));
	memset(vis,0,sizeof(vis));
	cnt=0;
}
int main(){
	//freopen("3.txt","r",stdin);
	int T;
	scanf("%d",&T);
	while(T--){
		clean();
		int n,m;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>c[i][j];
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(c[i][j]=='/'){
					add((i-1)*(m+1)+j,i*(m+1)+j+1,1);
					add(i*(m+1)+j+1,(i-1)*(m+1)+j,1);
					add((i-1)*(m+1)+j+1,i*(m+1)+j,0);
					add(i*(m+1)+j,(i-1)*(m+1)+j+1,0);
				}else{
					add((i-1)*(m+1)+j,i*(m+1)+j+1,0);
					add(i*(m+1)+j+1,(i-1)*(m+1)+j,0);
					add((i-1)*(m+1)+j+1,i*(m+1)+j,1);
					add(i*(m+1)+j,(i-1)*(m+1)+j+1,1);
				}
			}
		}
		DIJ(1);
		if(dis[(n+1)*(m+1)]==0x3f3f3f3f){
			printf("NO SOLUTION\n");
			continue;
		}
		printf("%d\n",dis[(n+1)*(m+1)]);
	}
	return 0;
}
	

```


    

---

## 作者：穼柗° (赞：2)

可以使用广度优先搜索（BFS）来探索所有可能的旋转组合，直到找到一种组合使得电源和发动机连通，或者确定没有解。然而，由于电路板可能非常大，直接尝试所有可能的旋转组合可能不实际。因此，我们需要一种策略来避免不必要的重复和无效搜索。

一种方法是使用广度优先搜索，但只搜索那些可以立即导致连通性改变的状态。我们可以将电路板的状态表示为一种图，其中每个节点代表一个特定的旋转组合，边代表从一个状态到另一个状态的单次旋转。我们的目标是找到从初始状态到目标状态（电源和发动机连通）的最短路径。

但是，直接表示这种图并搜索它可能是不可行的，因为它的大小可能是巨大的。相反，我们可以使用一个双向队列来存储待处理的电路板状态，并使用一个 map 来跟踪已经访问过的状态，以避免重复。

以下是解决这个问题的大致步骤：
1. 初始化电路板状态、队列和访问 map。
2. 将初始状态放入队列和 map 中。
3. 开始 BFS，直到队列为空或找到解决方案。
4. 如果队列为空但仍未找到解决方案，则输出 `NO SOLUTION`。

### Code
讲了这么多，代码就不给了

---

## 作者：Celtic (赞：2)

   很明显是一道搜索的题。

   我们可以把电路板上的每个格点(横线与竖线的交叉点)看作无向图中的结点。     
   若两个结点 $x$ 和 $y $是某个小方格的两个对角,则在 $x $与 $y$ 之间连边。若该方格中的标准件(对角线)与$ x$ 到$ y$ 的线段重合,则边权为 $0$ ;若垂直相交,则边权为 $1$  (说明需要旋转 $1$ 次才能连通)。然后,我们在这个无向图中求出从左上角到右下角的最短距离,就得到了结果。
       
   这是一个边权要么是 $0$ ,要么是 $1$ 的无向图。在这样的图上,我们可以通过双端队列广度搜索计算。算法的整体框架与一般的广度优先搜索类似，只是在每个结点上沿分支扩展时稍作改变。如果这条分支是边权为$ 0 $的边，就把沿改分支到达的新节点从队头入队；如果这条分支是边权为$ 1$ 的边，就像一般的广度优先搜索一样从队尾入队。这样一来，我们就仍然能保证任意时刻广度优先搜索队列中的结点对应的距离值都具有“两段性”和“单调性”，每个结点从队头出队时，就能得到从左上角到该结点的最短距离。
   
   因为每个结点只需要访问一次，所以算法的时间复杂度为$O(n\times m)$。
   
~~代码就自力更生吧~~

---

## 作者：lky1433223 (赞：2)

# Luogu2243电路维修
[传送门](https://www.luogu.org/problem/P2243)

[不来人家博客康康吗](https://www.cnblogs.com/Shiina-Rikka/p/11629327.html)
# 原题
找到左上角到右下角的通路。可以旋转某一个方块，代价为一。
![直接般牛客的图了](https://uploadfiles.nowcoder.com/files/20190710/314053_1562717136849_2601-1.png)
lyd书上的例题2333
# 怎么做
其实思路就是lyd的解法，写的时候有一些优化觉得挺有必要分享一下。比如三目运算符还有位运算的优化。

将这个问题转化为从左上到右下的最短路问题。若这个角需要旋转则是权值为1的路径，否则权值为0。这个时候跑最短路就可以了。

由于路径的权值很特殊，我们可以考虑使用双端队列优化。当权值为0时从队头插入，权值为1时从队尾插入。每次取队头，这样就可以保证一直在走最优解。而不需要dijkstra堆优化或者SPFA多次寻找最优解。

码代码时还有优化注释在代码里了。
# 扔代码
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace sss
{
const int MAXN = 505;
int r, c;
//下一步的方向，减少码量
const int step_x[] = {1, -1, 1, -1};
const int step_y[] = {1, -1, -1, 1};
char s[MAXN][MAXN];
int d[MAXN][MAXN];
bool v[MAXN][MAXN];
struct node
{
    int x, y;
    node() {}
    node(const int &_x, const int &_y)
    {
        x = _x, y = _y;
    }
};
//下一个点
inline node nextpoint(const node &now, const int &sp)
{
    return node(now.x + step_x[sp], now.y + step_y[sp]);
}
//路径对应的电线
inline node queryline(const node &now, const node &nxt)
{
    return node(max(now.x, nxt.x), max(now.y, nxt.y));
}
//判断是否合法
inline bool judge(const node &now, const int &sp)
{
    return now.x >= 0 && now.y >= 0 && now.x <= r && now.y <= c;
}
//bfs找最优解
inline void bfs()
{
    //多测不清空，爆零两行泪
    memset(d, 0x3f, sizeof(d));
    memset(v, 0, sizeof(v));
    deque<node> q;
    d[0][0] = 0;
    q.push_back(node(0, 0));
    while (q.size())
    {
        node now = q.front();
        q.pop_front();
        if (v[now.x][now.y])
            continue;
        v[now.x][now.y] = true;
        //四次循环找下一个位置，不用手写四次
        for (register int sp = 0; sp <= 3; ++sp)
        {
            //下一个点
            node nxt = nextpoint(now, sp);
            //对应的电线
            node lin = queryline(now, nxt);
            //合法才走
            if (judge(nxt, sp))
            {
                //这个位置使用位运算进行优化。
                int z = (s[lin.x][lin.y] == '\\') ^ (sp == 0 || sp == 1);
                if (d[nxt.x][nxt.y] > d[now.x][now.y] + z)
                {
                    d[nxt.x][nxt.y] = d[now.x][now.y] + z;
                    //三目运算符减少码量（懒）
                    z ? q.push_back(nxt) : q.push_front(nxt);
                }
            }
        }
    }
}
inline void sov()
{
    //多测不清空，爆零两行泪
    memset(s, 0, sizeof(s));
    scanf("%d %d", &r, &c);
    for (register int i = 1; i <= r; ++i)
        scanf("%s", s[i] + 1);
    bfs();
    //三目运算符减少码量（懒）
    d[r][c] == 0x3f3f3f3f ? (printf("NO SOLUTION\n")) : (printf("%d\n", d[r][c]));
}
} // namespace sss
int main()
{
    int T;
    scanf("%d", &T);
    for (register int ttt = 1; ttt <= T; ++ttt)
    {
        sss::sov();
    }
}
```

---

## 作者：Limit (赞：2)

看了眼题解，貌似没有和我的思路一样的....

所以就来写一篇题解...

首先我不会什么双向BFS也懒得写最短路...

所以，就一个BFS ~~闯遍天下~~再加上一个DFS(BFS自然也可以)记录联通快

还是先先看题：

![](https://cdn.luogu.com.cn/upload/pic/1286.png)

~~感性理解一下...貌似如(1,2),(2,1),(1,4),(4,1)都到不了~~ 虽然这个么什么用
好了，进入主题

首先，BFS是一个队列，为了保证结果的真确性，所以存当前花费的数组必须符合单调性，不然就没法达到最短路的效果了(~~开始就是没注意单调，调了2个小时~~)可以发现一个点可以直接到四个点，而到这四个点所花费的次数为1或0，所以只要当队伍中有一个点Q时，用DFS把Q可以花费0(即联通快)次就可以到达的点全部放进队列，然后，就是一个裸的BFS最短路了...

```cpp
#include<bits/stdc++.h>
using namespace std;
int queue_spend[1000000];//队列中每个位置的最少花费
int queue_x[1000000],queue_y[1000000];//队列中的点
int tail,head,N,M;
int boo[605][605];
int _map[605][605];
//注意：boo判断的是点，_map判断的是边
/*
B   C
 \ /
  A
 / \
D   E
A点存的是A这个点和A-E这条边
*/
int now_spead;//记录当前的花费
void add(int x,int y,int spend)//加入队列
{
	queue_x[++tail]=x;
	queue_y[tail]=y;
	queue_spend[tail]=spend;
	boo[x][y]=0;
}
void around(int first_x,int first_y)//向四周寻找可以不花费就可以到的点
{
	if(boo[first_x-1][first_y-1]&&_map[first_x-1][first_y-1]==0)
	//注意当坐标是减时，存边和存点都是减；加时，存边就是当前点对应的边
	{add(first_x-1,first_y-1,now_spead);around(first_x-1,first_y-1);}
	if(boo[first_x+1][first_y+1]&&_map[first_x][first_y]==0)
	{add(first_x+1,first_y+1,now_spead);around(first_x+1,first_y+1);}
	if(boo[first_x+1][first_y-1]&&_map[first_x][first_y-1]==1)
	{add(first_x+1,first_y-1,now_spead);around(first_x+1,first_y-1);}
	if(boo[first_x-1][first_y+1]&&_map[first_x-1][first_y]==1)
	{add(first_x-1,first_y+1,now_spead);around(first_x-1,first_y+1);}
}
void write(int out)//输出
{cout<<out<<endl;}
void solve()
{
	int i,j;
	for(i=0;i<=N+2;i++)//把表赋空
	for(j=0;j<=M+2;j++)
	boo[i][j]=0;
	cin>>N>>M;
	char ch;
	for(i=1;i<=N;i++)//读入
	for(j=1;j<=M;j++)
	{
		cin>>ch;
		if(ch=='/')_map[i][j]=1;//记录下边
		else _map[i][j]=0;
		//记录下点
		boo[i][j]=1;
		if(i==N)
		boo[i+1][j]=1;
		if(j==M)
		boo[i][j+1]=1;
		if(i==N&&j==M)
		boo[i+1][j+1]=1;
	}
	//队列初始化
	tail=1;
	head=0;
	boo[1][1]=0;
	now_spead=0;
	around(queue_x[1],queue_y[1]);//把一开始就可以直接到达的点放入队列，并且花费是0
	while((++head)<=tail)
	{
		if(queue_x[head]==N+1&&queue_y[head]==M+1)//找到结果
		{
			write(queue_spend[head]);
			return;
		}
		if(_map[queue_x[head]-1][queue_y[head]-1]==1&&boo[queue_x[head]-1][queue_y[head]-1])//如果这个方向行走要花费1次的话就入队，比较用0次的早入队了
		{
			add(queue_x[head]-1,queue_y[head]-1,queue_spend[head]+1);
			now_spead=queue_spend[tail];
			around(queue_x[tail],queue_y[tail]);//注意这里一定就要把拓展做掉，不然凉凉，我就是在在这里被卡了
		}
		if(_map[queue_x[head]][queue_y[head]]==1&&boo[queue_x[head]+1][queue_y[head]+1])//以下同理
		{
			add(queue_x[head]+1,queue_y[head]+1,queue_spend[head]+1);
			now_spead=queue_spend[tail];
			around(queue_x[tail],queue_y[tail]);
		}
		if(_map[queue_x[head]-1][queue_y[head]]==0&&boo[queue_x[head]-1][queue_y[head]+1])
		{
			add(queue_x[head]-1,queue_y[head]+1,queue_spend[head]+1);
			now_spead=queue_spend[tail];
			around(queue_x[tail],queue_y[tail]);
		}
		if(_map[queue_x[head]][queue_y[head]-1]==0&&boo[queue_x[head]+1][queue_y[head]-1])
		{
			add(queue_x[head]+1,queue_y[head]-1,queue_spend[head]+1);
			now_spead=queue_spend[tail];
			around(queue_x[tail],queue_y[tail]);
		}
	}
	cout<<"NO SOLUTION"<<endl;//无解
}
int main()
{
	//这里一直都不会改，就直接放在队伍中
	queue_x[1]=1;
	queue_y[1]=1;
	queue_spend[1]=0;
	int T;
	cin>>T;//进行T次操作
	int i;
	for(i=1;i<=T;i++)
	solve();
}
```

QAQ

---

## 作者：月离 (赞：2)

# 关于此题的双端队列解法
能用图做，不要用bfs，~~毕竟我不会~~

那么怎么构建这个图呢？

我们从左上点到右下点一次命名为1、2、3........

两个相互连通的点边权为一，反之为零。于是我们得到了一个图

Σ(っ °Д °;)っ那么SPFA跑一遍不就解决了吗

```cpp
void spfa(int s){
    queue<int>q;
    //memset(d,0x3f,sizeof(d));
    //memset(vis,0,sizeof(vis));
    d[s]=0;
    q.push(s);
    vis[s]=1;
    while (!q.empty()){
        int u=q.front();q.pop();
        vis[u]=0;
        for(int i=0;i<g[u].size();i++){
            int v=g[u][i].v,w=g[u][i].w;
            if(d[u]+w<d[v]){
                d[v]=d[u]+w;
                if(vis[v]==0){
                    q.push(v);
                    vis[v]=1;
                }
            }
        }
    }
}
```
然而这样并不是最优的

（以下重点）

双端队列解法才正宗

```cpp
void spfa(int s){
    deque<int>q;
    //memset(d,0x3f,sizeof(d));
    //memset(vis,0,sizeof(vis));
    d[s]=0;
    q.push_front(s);
    vis[s]=1;
    while (!q.empty()){
        int u=q.front();q.pop_front();
        vis[u]=0;
        for(int i=0;i<g[u].size();i++){
            int v=g[u][i].v,w=g[u][i].w;
            if(d[u]+w<d[v]){
                d[v]=d[u]+w;
                if(vis[v]==0){
                    if(!q.empty()&&d[v]<=d[q.front()])q.push_front(v);//此处进行优化
                    else q.push_back(v);
                    vis[v]=1;
                }
            }
        }
    }
}
```
满分

以下完整代码
```cpp
#include<iostream>
#include<cstring>
#include<vector>
#include<cstdio>
#include<deque>
using namespace std;
struct node{
    int v,w;
};
vector<node>g[1000000];
int x,y,t; 
int vis[1000000];
int d[1000000];
void spfa(int s){//平凡无奇的spfa 
    deque<int>q;//双端队列q 
    memset(d,0x3f,sizeof(d));
    memset(vis,0,sizeof(vis));
    d[s]=0;
    q.push_front(s);
    vis[s]=1;
    while (!q.empty()){
        int u=q.front();q.pop_front();
        vis[u]=0;
        for(int i=0;i<g[u].size();i++){
            int v=g[u][i].v,w=g[u][i].w;
            if(d[u]+w<d[v]){
                d[v]=d[u]+w;
                if(vis[v]==0){
                    if(!q.empty()&&d[v]<=d[q.front()])q.push_front(v);
                    else q.push_back(v);
                    vis[v]=1;
                }
            }
        }
    }
}	

int main(){
    cin>>x>>y;
    t=(x+1)*(y+1);//t号点，即最右下角的点 
    for(int i=1;i<=t;i++)g[i].clear();
    for(int i=1;i<=x;i++){
        char p[1000][1000];
        for(int j=1;j<=y;j++){
            cin>>p[i][j];	
            if(p[i][j]=='\\'){
                g[(i-1)*(y+1)+j].push_back((node){i*(y+1)+j+1,0});//此处构造图 
                g[i*(y+1)+j+1].push_back((node){(i-1)*(y+1)+j,0});
                g[(i-1)*(y+1)+j+1].push_back((node){i*(y+1)+j,1});
                g[i*(y+1)+j].push_back((node){(i-1)*(y+1)+j+1,1});
            }
            else {
                g[(i-1)*(y+1)+j].push_back((node){i*(y+1)+j+1,1});
                g[i*(y+1)+j+1].push_back((node){(i-1)*(y+1)+j,1});
                g[(i-1)*(y+1)+j+1].push_back((node){i*(y+1)+j,0});
                g[i*(y+1)+j].push_back((node){(i-1)*(y+1)+j+1,0});
            }
        }
    }
    spfa(1);
    if(d[t]==0x3f3f3f3f)cout<<"NO SOLUTION\n";//从1号点到t号点的距离 
    else cout<<d[t]<<endl;
    return 0;
}
```


---

## 作者：kxahcc (赞：2)

 这道题是一个双端队列的bfs，所以主要写如何加入双端队列（不用改变方向的放队列前边，需要的放后边，以保证最优解），以及判断增加答案就很好写了，~~但像我这么懒的人，怎么可能手写双端队列~~，于是这里引入STL——**deque**，头文件就是<deque>,~~还有bits，好像queue也有~~
 具体操作如下：(~~再也不用担心数组爆了写循环队列了呢~~)
  
####  声明：
  
####   	deque<int>q;（当然是可以放pair,struct的）
  
  
#### 加入队列前端
  	
###   	q.push_front();
  
#### 加入队列后端
  
### 　　q.push_back();
####   相应的删除操作分别为：
### 		q.pop_front()和q.pop_back();
  
 还有要注意关于这一题的一题是，我们不能是用每个格子的电路方向来搜，因为你是要对一些电路方向进行改变的，所以我们把每个格子的信息存储在
对应的格子的左上角，建立（n+1）*（n+1）的图,也就是对点来进行搜索，来判断两个点是否联通（所以跑dijkstra也是可以的）。
  
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
#include<deque>
#include<cstdio>
using namespace std;
const int N=520,M=1e5;
int T,n,m,dist[N][N],dx[4]={1,-1,1,-1},dy[4]={1,-1,-1,1};
bool vis[N][N];
char s[N][N];
struct node
{
	int x,y;
};
deque<node>que;
void add(bool f,int x,int y,int t)
{
	if(dist[x][y]<=t&&vis[x][y])return;
	vis[x][y]=1;
	dist[x][y]=t;
	node now;
	now.x=x,now.y=y;
	(!f||que.empty())?que.push_back(now):que.push_front(now);
}
void bfs()
{
	node now;
	now.x=0,now.y=0;
	que.push_back(now);
	vis[0][0]=1;
	while(!que.empty())
	{
		node w=que.front();
		que.pop_front();
		int x=w.x,y=w.y;
		int t=dist[x][y];
		for(int i=0;i<4;i++)
		{
			int xx=x+dx[i],yy=y+dy[i];
			if(xx<0||yy<0||xx>n||yy>m)continue;
			if(i==0)s[x][y]=='\\'?add(1,xx,yy,t):add(0,xx,yy,t+1);
			if(i==1)s[xx][yy]=='\\'?add(1,xx,yy,t):add(0,xx,yy,t+1);
			if(i==2)s[x][yy]=='/'?add(1,xx,yy,t):add(0,xx,yy,t+1);
			if(i==3)s[xx][y]=='/'?add(1,xx,yy,t):add(0,xx,yy,t+1);//三母压行简直不要太好用，（而且还快）
		}
	}
	printf("%d\n",dist[n][m]);
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		memset(dist,0,sizeof(dist));
		memset(vis,0,sizeof(vis));
		scanf("%d%d",&n,&m);
		for(int i=0;i<n;i++)scanf("%s",s[i]);
		if((n+m)&1)
		{
			printf("NO SOLUTION\n");
			continue;
		}
		bfs();
	}
	return 0;
}


---

## 作者：Shallowy (赞：2)

~~为什么都是线段树+Dij~~


首先每个元件只有两种状态，也就是说最多每个元件只需要转1次。


然后显然可以**最短路**，从每个点向左上、右上、左下、右下拓展。


无脑乱写了个裸的spfa结果WA飞...


再想想就能发现**在松弛的时候，dis都是在当前点的基础上+0(不加)或+1的。**


于是有了一种**双向队列(deque)**的神奇做法。


在bfs的时候，如果当前增加的距离为0(即不需要旋转)则把新点**放到队头**直接进行下一轮松弛，否则**放到队尾**。


容易看出来，这样bfs就能**保证第一次搜到目标点的时候一定是最短路**。


~~不开O2就轻松过了...~~

```cpp
//用1表示'/'，2表示'\'。每个元件左上角的坐标为其编号,(1,1)为起点,(n+1,m+1)为终点
#include <iostream>
#include <cstdio>
#include <cctype>
#include <deque>
#include <cstring>
#define il inline
#define vd void
#define rep(i,x,y) for(register int i=x;i<=y;++i)
#define drp(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;
const int Len=2333333,aa[4][2]={{-1,-1},{-1,1},{1,-1},{1,1}},ab[4]={2,1,1,2},p[4][2]={{-1,-1},{-1,0},{0,-1},{0,0}};
//aa为4个方向的位移，ab为4个元件期望的方向，p为4个元件编号的位移
char buf[Len],*p1=buf,*p2=buf,duf[Len],*q1=duf;
il char gc(); il int rd(); il vd pc(char c); il vd rt(int x); il vd flush();
int n,m,nx,ny,d,c[505][505],dis[505][505];
struct P{int x,y,d;}u;
deque <P> q;
il int Get(){char c; while((c=gc())!='/'&&c!='\\'); return c=='/'?1:2;}//注意'\'的读入
int main(){
    n=rd(),m=rd(),memset(dis,0x3f,sizeof(dis));
    rep(i,1,n) rep(j,1,m) c[i][j]=Get();
    q.push_back((P){1,1,0}),dis[1][1]=0;
    while(!q.empty()){
        u=q.front(),q.pop_front(); //front()队头,pop_front()弹出队头
        rep(i,0,3){
            nx=u.x+aa[i][0],ny=u.y+aa[i][1],d=c[u.x+p[i][0]][u.y+p[i][1]]!=ab[i]; //若方向不相等,则d=1,表示需要1步来转向
            if(nx&&ny&&nx<n+2&&ny<m+2&&dis[nx][ny]>dis[u.x][u.y]+d){
                dis[nx][ny]=dis[u.x][u.y]+d,
                d?q.push_back((P){nx,ny,dis[nx][ny]}):q.push_front((P){nx,ny,dis[nx][ny]}); //判断插入方向,push_front()插到队头,push_back()插到队尾
                if(nx==n+1&&ny==m+1) break; //这里直接break
            }
        }
        if(nx==n+1&&ny==m+1) break;
    }
    if(dis[n+1][m+1]!=0x3f3f3f3f) rt(dis[n+1][m+1]);
    else printf("NO SOLUTION");
    return flush(),0;
}//以下为读优输优

il char gc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,Len,stdin),p1==p2)?-1:*p1++;}
il int rd(){char c; int f=1;
    while(!isdigit(c=gc())&&c!='-');
    c=='-'?f=-1,c=gc():0; int x=c^48;
    while(isdigit(c=gc())) x=((x+(x<<2))<<1)+(c^48);
    return x*f;
}
il vd pc(char c){q1==duf+Len&&fwrite(q1=duf,1,Len,stdout),*q1++=c;}
il vd rt(int x){x<0?pc('-'),x=-x:0,pc((x>=10?rt(x/10),x%10:x)+48);}
il vd flush(){fwrite(duf,1,q1-duf,stdout);}
```

---

## 作者：ღ﹏ﻬ北❦栀 (赞：1)

## 双端队列BFS
这道题用到了双端队列BFS。

思路点拨：
我们可以把电路板上的每个格点（横线与竖线的交叉点）看作无像图中的结点，若两个结点x和y是某个小方格的两个对角，则在x和y之间连边，若该方格中的标准件（对角线）与x到y的线段重合，则边权为0；若垂直相交则边权为1.（说明需要旋转1次才能连通）然后，我们在这个无向图中求出左上角到右下角的最短距离，就得到了结果。
这是一个边权要么为0要么为1的无向图，在这样的图上，我们可以通过双端队列广度搜素来计算，算法的整题框架为一般的广搜类似，只是在每个结点上沿分支扩展时稍作改变，如果这条分支是边权为0的边，就把沿该分支到达的新结点从队头入队，如果这条分支是边权为1的边，就像一般的广度搜索一样从队尾入队，这样一来，我们就仍然能保证任意时刻广搜队列中的结点对应的距离值都具有“两段性”和“单调性”，每个结点从队头出列时，就能得到从左上角到该结点的最短距离。
因为每个节点都只访问了一遍，所以时间复杂度为O（R*C）
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<string.h>
using namespace std;
const int cap=500010;
int dist[510][510];
char map[510][510];
bool proc[510][510];
pair<int ,int >queue[cap*2];
int r,c,li,ri;
inline bool valid(int x,int y) {
	return x>=0&&x<=r&&y>=0&&y<=c;
}
inline void que_add(int x,int y,int v){
	if(dist[x][y]<0||v<dist[x][y]) {
		dist[x][y]=v;
		if(li==ri||v>dist[queue[li].first][queue[li].second])queue[ri++]=make_pair(x,y);
		else queue[--li]=make_pair(x,y);
	}
}
int main() {
	int kase;
	for(scanf("%d",&kase); kase; --kase)
	 {
		cin>>r>>c;
		if((r+c)%2)
		 {
			for(int i=0; i<r; i++)cin>>map[i];
			cout<<"NO SOLUTION\n";
		} 
		else {
			for(int i=0; i<r; i++)cin>>map[i];
			li=ri=cap;
			queue[ri++]=make_pair(0,0);
			memset(dist,-1,sizeof dist),dist[0][0]=0;
			memset(proc,false,sizeof proc);
			while(li!=ri) 
			{
				int cx=queue[li].first,cy=queue[li].second;
				++li;
				if(valid(cx-1,cy-1))
				 {
					if(map[cx-1][cy-1]=='\\')que_add(cx-1,cy-1,dist[cx][cy]);
					else que_add(cx-1,cy-1,dist[cx][cy]+1);
				}
				if(valid(cx-1,cy+1)) {
					if(map[cx-1][cy]=='/')que_add(cx-1,cy+1,dist[cx][cy]);
					else que_add(cx-1,cy+1,dist[cx][cy]+1);
				}
				if(valid(cx+1,cy-1)) {
					if(map[cx][cy-1]=='/')que_add(cx+1,cy-1,dist[cx][cy]);
					else que_add(cx+1,cy-1,dist[cx][cy]+1);
				}
				if(valid(cx+1,cy+1)) {
					if(map[cx][cy]=='\\')que_add(cx+1,cy+1,dist[cx][cy]);
					else que_add(cx+1,cy+1,dist[cx][cy]+1);
				}
			}
			printf("%d\n",dist[r][c]);
		}
	}
	return 0;
}
```


---

## 作者：Social_Zhao (赞：1)

我这题的思路肯定是$Heap+Dijkstra$ ~~，纵然这是一道双端队列bfs的例题~~ 。然后就有以下的要点：

一、建图：

建图的策略很简单：如果$(i,j)$是 ' \ '，那么表示从左上角走到右下角（或反之）不需要经过旋转，而从左下角走到右上角（或反之）需要经过一次旋转。所以我们从$(i,j)$到$(i+1,j+1)$建一条权为$0$的双向边，从$(i+1,j)$到$(i,j+1)$建一条权为$1$的双向边。

另一种情况同理

那么很明显这是一个没有负权的**网格图**了。我们选择$Dijkastra$。

现在又有一个新的问题，这是一个二维的图，我们不可能直接用二维的下标跑$SSSP$吧？那样太麻烦了。

于是我们考虑对这张图进行二向箔攻击：把它拍成一维的，具体：

$(x,y) \text{ -> } (c+1)*(x-1)+y; $

```cpp
int HASH(int x,int y)//不要在意函数名
{
    return (c+1)*(x-1)+y;
}
```

于是我们得到了第一份代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MaxN = 505,MaxM = 505;
const int Max_tot = MaxN * MaxM;
const int inf=0x3f3f3f3f;
priority_queue <pair<int,int> > q;
int head[Max_tot],k=1;
struct Edge {
    int to,next,dis;
}e[10*Max_tot];
char maze[MaxN][MaxM];
int dis[Max_tot],vis[Max_tot];
int r,c;
void add(int from,int to,int dis) //建边（单向）
{
    e[k].to=to;
    e[k].dis=dis;
    e[k].next=head[from];
    head[from]=k++;
}
void insert(int from,int to,int dis) //建边（双向）
{
    add(from,to,dis);
    add(to,from,dis);
}
int HASH(int x,int y) //二向箔函数
{
    return (c+1)*(x-1)+y;
}
inline void dijkstra(int st) //SSSP算法
{
    memset(dis,0x3f,sizeof(dis));
    memset(vis,0,sizeof(vis));
    dis[st]=0;
    q.push(make_pair(0,1));
    while(q.size()) {
        int minn=q.top().second;
        q.pop();
        if(vis[minn]) continue;
        vis[minn]=1;
        for(int i=head[minn];i;i=e[i].next) {
            int y=e[i].to;
            int z=e[i].dis;
            if(dis[y]>dis[minn]+z) {
                dis[y]=dis[minn]+z;
                q.push(make_pair(-dis[y],y));
            }
        }
    }
}
void BuildG() //建图
{
    for(int i=1;i<=r;i++) {
        for(int j=1;j<=c;j++) {
            if(maze[i][j]=='\\') {
                int f1=HASH(i,j);
                int t1=HASH(i+1,j+1);
                int f2=HASH(i+1,j);
                int t2=HASH(i,j+1);
                insert(f1,t1,0);
                insert(f2,t2,1); 
            }
            else if(maze[i][j]=='/') {
                int f1=HASH(i,j);
                int t1=HASH(i+1,j+1);
                int f2=HASH(i+1,j);
                int t2=HASH(i,j+1);
                insert(f1,t1,1);
                insert(f2,t2,0); 
            }
        }
    }
}
void init() //各种初始化，以及解
{
    memset(head,0,sizeof(head));
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    memset(e,0,sizeof(e));
    memset(maze,0,sizeof(maze));
    k=1;
    while(q.size()) q.pop();
    cin>>r>>c;
    for(int i=1;i<=r;i++) {
        for(int j=1;j<=c;j++) {
            cin>>maze[i][j];
        }
    }
    BuildG();
    dijkstra(1);
    if(dis[HASH(r+1,c+1)]==inf) cout<<"NO SOLUTION"<<endl;
    else cout<<dis[HASH(r+1,c+1)]<<endl;
}
int main()
{
    ios::sync_with_stdio(0);
    init(); //这里就没什么好解释的了。
}
```

二：治好懒癌

但是！！！这是一个不完美的做法。因为$STL$的常数真的是太大了。如何让我们的程序跑得更快呢？

$Ans$： ~~吸氧~~ 手写堆。

我们加上这样的代码:

```cpp
template<typename T> 
struct Priority_Queue { //这个结构体可以支持STL中priority_queue的绝大部分操作。
    T heap[100005];
    int heap_size=0;
    
    T top() {
        return heap[1]; 
    }
    
    bool empty() {
        return heap_size==0;
    }
    
    int size() {
        return heap_size;
    }
    
    void push(T x) {
        heap_size++;
        heap[heap_size]=x;
        int now=heap_size;
        while(now>1) {
            int next=now>>1;
            if(heap[now]<heap[next]) {
                swap(heap[now],heap[next]);
            }
            else return;
            now=next;
        }
        return;
    }
    
    void pop() {
        heap[1]=heap[heap_size];
        heap_size--;
        int now=1,next;
        while((now<<1)<=heap_size) {
            next=now<<1;
            if(next+1<=heap_size&&heap[next+1]<heap[next]) next++;
            if(heap[next]<heap[now]) {
                swap(heap[now],heap[next]);
            }
            else return;
            now=next;
        }
        return;
    }
};

bool operator < (pair<int,int> x,pair<int,int> y) { //这里需要重载一下运算符。
    return x.first<y.first;
}
```

然后把

```cpp
priority_queue< pair<int,int> >q;
```

改成

```cpp
Priority_Queue< pair<int,int> >q;
```

以及$Dijkstra$中的松弛（之前我们用的是大根堆，往里存相反数）

```cpp
                q.push(make_pair(-dis[y],y));
```

改成

```cpp
                q.push(make_pair(dis[y],y));
```

就可以$AC$了

---

## 作者：qwaszx (赞：1)

之前觉得这东西挺简单...结果一写才知道自己根本不会...

### 0.考虑一张无向图，其边权全为$1$

直接$BFS$扩展即可.

### 1.考虑一张无向图，其边权非负

$dijkstra$即可.最好用$zkw$线段树优化，常数比配对堆略小

顺便考虑一下$dijkstra$的原理，本质可以算一个$dp$，每次用当前最优的点更新其他点，用数据结构维护当前最优点.

### 2.考虑一张无向图，其边权为$0$或$1$

结合$0$和$1$.使用$BFS$进行扩展并维护当前最优的位置.显然扩展一个节点时边权为$0$则更优，扔到队首；否则扔到队尾.

正确性？

首先，$BFS$的队列中一定只有两种权值且差为$1$，这个可以归纳.我们一定是取小的一些，并且最多增加$1$，所以始终是差为$1$的两种权值.

然后队首元素一定不会再被更新.这个也是显然的，所以算法的正确性可以保证.

考虑一个问题.如果我把一个东西扔到了队尾，但后来它又可以被更新，怎么处理呢？仿照$dijkstra$，只需要记录一个点的真正最短路，队列里存的是某个时刻的最短路，如果它大于真正的最短路就不进行扩展.

每个点最多进队两次，复杂度$O(n)$

建议手写双端队列.$stl::deque$速度极慢.手写方法...直接把队头开够大就好了233

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define INF 1000000007
using namespace std;
const int N=3e6;
int dis[N],n,m,mm,nxt[N],fst[N];
char st[1000];
struct Edge{int v,w;}e[N];
struct Node{int id,dis;}q[N];
void ade(int u,int v,int w){e[++mm]=(Edge){v,w},nxt[mm]=fst[u],fst[u]=mm;}
void Link(int u,int v,int w){ade(u,v,w),ade(v,u,w);}
int id(int i,int j){return (i-1)*(m+1)+j;}
void bfs()
{
	int S=id(1,1);
	int head=1000000,tail=1000001;
	q[head+1]=(Node){S,0};dis[S]=0;
	while(head<tail)
	{
		int u=q[++head].id,d=q[head].dis;if(d>dis[u])continue;
		for(int i=fst[u];i;i=nxt[i])
		{
			int v=e[i].v;
			if(dis[u]+e[i].w>=dis[v])continue;
			if(e[i].w==0){q[head--]=(Node){v,dis[v]=dis[u]};}
			else q[++tail]=(Node){v,dis[v]=dis[u]+1};
		}
	}
}
void clear(int n)
{
	for(int i=1;i<=n;i++)fst[i]=0,dis[i]=INF;
	mm=0;
}
int main()
{
	int T=1;scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		clear(id(n+1,m+1));
		for(int i=1;i<=n;i++)
		{
			scanf("%s",st+1);
			for(int j=1;j<=m;j++)
				if(st[j]=='/')Link(id(i+1,j),id(i,j+1),0),Link(id(i,j),id(i+1,j+1),1);
				else Link(id(i,j),id(i+1,j+1),0),Link(id(i+1,j),id(i,j+1),1);
		}
		bfs();
		if(dis[id(n+1,m+1)]==INF)puts("NO SOLUTION");
		else printf("%d\n",dis[id(n+1,m+1)]);
	}
}
```

---

## 作者：Sym_Je (赞：1)

             P2243 电路维修   
 [ P2243 电路维修](https://www.luogu.org/problemnew/show/P2243)    
 
 这道题明显是一个bfs，就类似于迷宫问题嘛，只是多了一个维护的东西，---最短的改变次数，这样只要每个点维护一下这个值，这就要用到双端队列，就ok咯。    
 然后我们想怎么搞，首先我们可以发现，其实从一个点到另外一个点所花费的代价要么为1，要么为0，我们最好每次都从当前的最小值转移，而双端队可以维护队列的单调性。  
 我们又可以把方格转换为点，这样我们直接求从0，0--->n,m的最短路（最小花费）   
 
 若边权为1，则和正常广搜一样从队尾入队；若边权为0，则从队首入队。
 
 因为我们取出的都是当前栈中到某个点的最短路径，所以如果我们取出的值如果到另一个点的距离还为0，呢么就转移，来更新。
 
 ```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<queue>

using namespace std;

const int maxn=500001;

pair<int,int> que[2*maxn];


int t;
int li,ri;
int cap;

int n,m;

char s[501][501];

int dist[501][501];

bool check(int x,int y)
{
	return x>=0&&x<=n&&y>=0&&y<=m;
}

void add_que(int x,int y,int v)
{
	if(dist[x][y]<0||dist[x][y]>v)
	{
		dist[x][y]=v;
		if(li==ri||v>dist[que[li].first][que[li].second])
		{
			que[ri++]=make_pair(x,y);
		}
		else
		{
			que[--li]=make_pair(x,y);
		}
	}
}

int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		for(int i=0;i<n;i++)
		{
			scanf("%s",s[i]);
		}
		if((n+m)%2)
		{
			printf("NO SOLUTION\n");
			continue;
		}
		memset(dist,-1,sizeof(dist));
		dist[0][0]=0;
		li=ri=maxn;
		que[ri++]=make_pair(0,0);
		while(li!=ri)
		{
			int cx=que[li].first;
			int cy=que[li].second;
			++li;
			if(check(cx-1,cy-1))
			{
				if(s[cx-1][cy-1]=='\\')
				{
					add_que(cx-1,cy-1,dist[cx][cy]);				
				}
				else
				{
					add_que(cx-1,cy-1,dist[cx][cy]+1);
				}
			}
			if(check(cx-1,cy+1))
			{
				if(s[cx-1][cy]=='/')
				add_que(cx-1,cy+1,dist[cx][cy]);
				else
				add_que(cx-1,cy+1,dist[cx][cy]+1);
			}
			if(check(cx+1,cy+1))
			{
				if(s[cx][cy]=='\\')
				{
					add_que(cx+1,cy+1,dist[cx][cy]);
				}
				else
				{
					add_que(cx+1,cy+1,dist[cx][cy]+1);
				}
			}
			if(check(cx+1,cy-1))
			{
				if(s[cx][cy-1]=='/')
				{
					add_que(cx+1,cy-1,dist[cx][cy]);
				}
				else
				{
					add_que(cx+1,cy-1,dist[cx][cy]+1);
				}
			}
		}
		printf("%d\n",dist[n][m]);
	}
}
```
 
 

---

## 作者：远航之曲 (赞：1)

不错的一道图论

对于**每一个**正方形，我们把它的四个点都提取出来，假如两个点中有对角线，就连上边权为0的边，没有就连边权为1的边（表示需要转）。

接下来直接跑最短路就行了，我用的堆优化dij.

具体见代码


```cpp
#include <cstdio>
#include <cstring>
#include <queue>
#include <string>
#include <iostream>
#define M 4*501*501
#define N 1000*1000
#define INF 0x3f3f3f3f
using namespace std;
typedef pair<int,int> Pair;
struct node
{
    int to,value,next;
}e[M];
int tot,st[M];
int n,m;
void add(int x,int y,int z)
{
    e[++tot].to=y;
    e[tot].value=z;
    e[tot].next=st[x];
    st[x]=tot;
}
int dis[N];
bool flag[N];
priority_queue< Pair,vector<Pair>,greater<Pair> >que;
int dij(int start,int end)
{
    memset(flag,0,sizeof flag);
    dis[start]=0;
    que.push(make_pair(dis[start],start));
    while (!que.empty())
    {
        Pair now=que.top();
        que.pop();
        if (flag[now.second]) continue;
        flag[now.second]=1;
        for (int i=st[now.second];i;i=e[i].next)
            if (dis[now.second]+e[i].value<dis[e[i].to])
            {
                dis[e[i].to]=dis[now.second]+e[i].value;
                if (!flag[e[i].to]) que.push(make_pair(dis[e[i].to],e[i].to));
            }
    }
    return dis[end];
}
main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        memset(e,0,sizeof e);
        memset(st,0,sizeof st);
    int a1,a2,a3,a4;
    tot=0;
    scanf("%d %d",&n,&m);
    for (int i=1;i<=n;i++)
    {
        char s[510];
        scanf("%s",&s);
        for (int j=1;j<=m;j++)
        {
            if (s[j-1]=='/')   /*   ->  / */
            {
                int a1=(i-1)*(m+1)+j;
                int a2=i*(m+1)+j+1;
                int a3=(i-1)*(m+1)+j+1;
                int a4=i*(m+1)+j;
            //    printf("i:%d,j:%d,%d,%d,%d,%d\n",i,j,a1,a2,a3,a4);
                add(a1,a2,1);
                add(a2,a1,1);
                add(a3,a4,0);
                add(a4,a3,0);
            }
            else    /*    -> \ */
            {
                int a1=(i-1)*(m+1)+j;
                int a2=i*(m+1)+j+1;
                int a3=(i-1)*(m+1)+j+1;
                int a4=i*(m+1)+j;
            //    printf("i:%d,j:%d,%d,%d,%d,%d\n",i,j,a1,a2,a3,a4);
                add(a1,a2,0);
                add(a2,a1,0);
                add(a3,a4,1);
                add(a4,a3,1);
            }
        }
    }
    for(int i=1;i<=(n+1)*(m+1);++i)
          dis[i]=INF;
    int ans=dij(1,(n+1)*(m+1));
    if (ans==INF)
        printf("NO SOLUTION\n");
    else
        printf("%d\n",ans);
    }
}
```

---

## 作者：Dorg (赞：1)

淦，这题错的荒唐。惨！

-------------

上题：[ P2243 电路维修](https://www.luogu.org/problemnew/show/P2243)

本题怎么看都很水（只要你不用双向BFS）。

### 但是，坑爹啊！

两行回车，还能不能愉悦地getchar()了。

题解区找到一位同样如此的兄弟：
![](https://cdn.luogu.com.cn/upload/pic/40701.png )
![](https://cdn.luogu.com.cn/upload/pic/40702.png )

同是天涯沦落人呀。

JOJO，我不用getchar()了。

------------
思路如下：
1. 实际上是一个(r+1)*(c+1)的矩阵，给它们编号：

```
LL change(int x,int y){
	
	int ans=(x-1)*(m+1)+y;
	return ans;
	
}
```
2. 然后根据“/”还是“\”来连边：

```
if(dic=='/'){
	//cout<<"run1"<<endl;
	push(change(i,j),change(i+1,j+1),1);
	push(change(i+1,j+1),change(i,j),1);
	push(change(i+1,j),change(i,j+1),0);
	push(change(i,j+1),change(i+1,j),0); 
} 
else{
	//cout<<"run2"<<endl;
	push(change(i,j),change(i+1,j+1),0);
	push(change(i+1,j+1),change(i,j),0);
	push(change(i+1,j),change(i,j+1),1);
	push(change(i,j+1),change(i+1,j),1); 
} 
```
3. 愉悦地跑一遍单源最短路。（什么？你说SPFA过不了，
[出门左拐，好走不送](https://www.luogu.org/problemnew/show/P4779)。)

--------------
## CODE
```
#include<bits/stdc++.h>
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define Maxn 502
#define inf 25000000
#define LL long long

using namespace std;

inline int read(){
	
	int ans=0; int fg=1; char c=getchar();
	while(!(c<='9'&&c>='0')){ if(c=='-') fg=-1; c=getchar(); }
	while(c<='9'&&c>='0'){ ans=ans*10+c-'0'; c=getchar(); }
	return ans*fg;
}

int n,m;

LL change(int x,int y){
	
	int ans=(x-1)*(m+1)+y;
	return ans;
	
}

struct lline{
	int st,en,pre,w;
}line[Maxn*Maxn*10];
int tot=0;
int head[Maxn*Maxn];
void push(int a,int b,int c){
	tot++;
	line[tot].st=a;
	line[tot].en=b;
	line[tot].w=c;
	line[tot].pre=head[a];
	head[a]=tot;
}


LL dis[Maxn*Maxn];
int vis[Maxn*Maxn];
priority_queue< pair<int,int> > q;
LL DJ(){
    FOR(i,1,(n+1)*(m+1)){
        dis[i]=inf;
        vis[i]=0;
    }
     while(!q.empty()) q.pop();
    dis[1]=0;
    q.push(make_pair(0,1));
    while(!q.empty()){
        int x=q.top().second;
        q.pop(); 
        if(vis[x]) continue;
        vis[x]=1;
        for(int i=head[x];i;i=line[i].pre){
            int y=line[i].en; int l=line[i].w;
            if(dis[y]>dis[x]+l){
                dis[y]=dis[x]+l;
                q.push(make_pair(-dis[y],y));//懒得重载运算符
            }
        }
    }
    
//    FOR(i,1,n+1){
//    	FOR(j,1,m+1)
//    		cout<<dis[change(i,j)]<<" ";
//    	cout<<endl;
//	}
    
    return (dis[(n+1)*(m+1)]);
    
}


//queue<int> q;
//int SPFA(){
//	FOR(i,1,(n+1)*(m+1)){
//		dis[i]=inf;
//		vis[i]=0;
//	}
//    q.push(1);
//    dis[1]=0;
//    while(!q.empty()){
//        int x=q.front();
//        q.pop();
//        vis[x]=0;
//        for(int i=head[x];i;i=line[i].pre){
//            int v=line[i].en;
//            if(dis[v]>dis[x]+line[i].w){
//                dis[v]=dis[x]+line[i].w;
//                if(!vis[v]){
//                    vis[v]=1;
//                    q.push(v);
//                }
//            }
//        }
//    }
//    return (dis[(n+1)*(m+1)]);
//}

int main(){
	
	int T; cin>>T;
	
	FOR(ccc,1,T){
	
	n=read(); m=read();
	
//	for(int i=1;i<=n+1;i++){
//		for(int j=1;j<=m+1;j++)
//			cout<<change(i,j)<<" ";
//		puts("");
//	}
	
	
	memset(head,0,sizeof(head));
	memset(line,0,sizeof(line));
	tot=0;
	
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			char dic; cin>>dic;
			if(dic=='/'){
				//cout<<"run1"<<endl;
				push(change(i,j),change(i+1,j+1),1);
				push(change(i+1,j+1),change(i,j),1);
				push(change(i+1,j),change(i,j+1),0);
				push(change(i,j+1),change(i+1,j),0); 
			} 
			else{
				//cout<<"run2"<<endl;
				push(change(i,j),change(i+1,j+1),0);
				push(change(i+1,j+1),change(i,j),0);
				push(change(i+1,j),change(i,j+1),1);
				push(change(i,j+1),change(i+1,j),1); 
			} 
		}
		
	//cout<<DJ()<<endl;
	long long Ans=DJ();
	if(Ans==inf)
		cout<<"NO SOLUTION"<<endl;
	else
		cout<<Ans<<endl;
	
	}
	
	return 0;
}
```
--------------
### 题外话
留了个SPFA的代码，有好事者可以交着玩玩。

---

## 作者：__Sky__Dream__ (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/P10486)

## 解题思路
考虑**双端队列和广度优先搜索**。

首先我们把电路板上每一个格子点（交叉点）看作无向图中的节点，我们认为两个节点 $x$ 和 $y$ 是小方格的两个对角，那么如果说 $x$ 和 $y$ 的线段是 `"\"`，那么我们可以认为边权为 $0$，反之如果 $x$ 和 $y$ 线段是 `"/"`，那么我们的边权为 $1$，要旋转一次才能够连上。

现在我们得到了一张边权 $0$ 或 $1$ 的无向图，那么和普通广搜一样，我们唯一的改变就是，如果说当前新状态的边权为 $0$，那么我们就放到队头先走，因为我们要满足两端性和单调性，而为了这个单调性，如果说当前新状态边权为 $1$，那么我们就要压入到队尾。

其余详见代码。

## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define fir(i,a,b) for(int i=a;i<=b;i++)
const int N=510;
const int dxy1[4][2]= {{1,1},{-1,-1},{1,-1},{-1,1}},dxy2[4][2]= {{1,1},{0,0},{1,0},{0,1}};//两种不同走法(因为两种线路),所以要两个方向数组
struct data
{
    int x,y;
};
int t,n,m,ans=1e8,dis[N][N];
char s[N][N];
bool vis[N][N];
deque<data> q;//双端队列
int check(int x,int y)
{
    return x>=0 && x<=n && y>=0 && y<=m;//范围内
}
void bfs()
{
    vis[0][0]=1;
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));//初始化最大值
    q.push_front(data {0,0});//0开始,是因为读入的不是坐标,而是两种线路,然后你就会发现其实坐标点是要从0开始的,当然你n+1,m+1也是可以的
    dis[0][0]=0;
    while(q.size())
    {
        data now=q.front();
        q.pop_front();
        fir(i,0,3)//四种方向
        {
            int tx=now.x+dxy1[i][0],t1=now.x+dxy2[i][0];//如果是'\'
            int ty=now.y+dxy1[i][1],t2=now.y+dxy2[i][1];//如果是'/'
            int tt=(s[t1][t2] != (i<=1? '\\':'/'));//转义字符要双写,这里用到了三目运算符
            if(check(tx,ty) && dis[tx][ty]>dis[now.x][now.y]+tt)//check成功,并且当前值更加优秀
            {
                dis[tx][ty]=dis[now.x][now.y]+tt;
                if(tt)
                    q.push_back(data {tx,ty});//边权值为1
                else
                    q.push_front(data {tx,ty});//边权值为0
            }
        }
    }
}
int main()
{
    cin>>t;
    while(t--)
    {
        cin>>n>>m;
        fir(i,1,n)
        fir(j,1,m)
        cin>>s[i][j];
        bfs();
        if(dis[n][m]<1e8)//如果找到了方案
            cout<<dis[n][m]<<endl;
        else
            cout<<"NO SOLUTION"<<endl;
    }
    return 0;
}
```
拜拜！

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10486)

## 思路

双向广搜。

由于更改一定比不更改花费多，所以我们优先搜索不更改的，即把不更改的从队列头压入，更改的从队列尾压入。

读入数据后首先判断，因为每次都是横纵坐标同时移动，所以如果 $(n+m) \bmod 2=1$，那么无法走到 $(n,m)$，输出 ``NO SOLUTION``。之后我们用类似 spfa 的标记方式记录最短路（即定义一个 $dis$ 数组表示走到这个位置时的最小更改次数）。如果当前计划走的位置和图不符就更改图并从后压入队列，否则不更改并从前压入。

- 每次枚举的都是交点位置，所以在判断方格内电线走向的时候要进行转换。所有转换数组如下：

```cpp
const int ddx[]={1,-1,-1,1};//点走向。
const int ddy[]={1,1,-1,-1};
const char dc[]={'\\','/','\\','/'};//电线走向。
const int dx[]={0,-1,-1,0};//点对应方格。
const int dy[]={0,0,-1,-1};
```

## 代码

```cpp
#include<bits/stdc++.h>
#define pb push_back
#define pf push_front
#define pob pop_back
#define pof pop_front
using namespace std;
const int N=510;
int n,m,dis[N][N];
char c[N][N];
struct node{int x,y;};
deque<node>q;
const int ddx[]={1,-1,-1,1};
const int ddy[]={1,1,-1,-1};
const char dc[]={'\\','/','\\','/'};
const int dx[]={0,-1,-1,0};
const int dy[]={0,0,-1,-1};
bool inmap(int x,int y){return x>=0&&x<=n&&y>=0&&y<=m;}
signed main(){
	int T=read();
	while(T--){
		cin>>n>>m;
		for(int i=0;i<n;++i)for(int j=0;j<m;++j)cin>>c[i][j];
		if(n+m&1){
			puts("NO SOLUTION");
			continue;
		}
		for(int i=0;i<=n;++i)for(int j=0;j<=m;++j)dis[i][j]=1e9;
		q.pf({0,0});
		dis[0][0]=0;
		while(q.size()){
			node now=q.front();
			q.pof();
			for(int i=0;i<4;++i){
				int xx=dx[i]+now.x;
				int yy=dy[i]+now.y;
				int px=ddx[i]+now.x;
				int py=ddy[i]+now.y;
				if(!inmap(px,py))continue;
				if(dc[i]!=c[xx][yy]){//预计走向与图不符，改图。
					if(dis[px][py]>dis[now.x][now.y]+1){//上次走的更改次数不优，搜索。
						dis[px][py]=dis[now.x][now.y]+1;
						q.pb({px,py});
					}
				}
				else{//否则不改图。
					if(dis[px][py]>dis[now.x][now.y]){
						dis[px][py]=dis[now.x][now.y];
						q.pf({px,py});
					}
				}
			}
		}
		cout<<dis[n][m]<<"\n";
	}
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/159417085)

---

## 作者：Zekrom (赞：0)

## 标签：   
最短路广搜、双端队列广搜      
### 理解：   
对于一次旋转，我们可以理解成边权为1的边   
对于已有的线路，建立边权为0的边   
所以这道题可以转化成最短路问题   
显然最短路的解法都可以做   
但观察到时限只有150ms，并且边权只有0/1，我们考虑双端队列的广搜   
即对于边权为0的点，放队头优先扩展  
对于边权为1的点，则放队尾   
当一个点从对头取出时，就求出了起点到该点的最短路   
### 实现：  
1.对于网格上的每一点（i，j),用（m+1)*i+j表示该点，避免了结构体的使用   
### 上代码   

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<deque>
#define N 510 
using namespace std;
int n,m,T,d[N*N],head[N*N],tot; 
bool vis[N*N];
struct Edge{
	int v,next,val;
}edge[N*N*4];
inline int read(){
	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();
	}while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();
	}return x*f;
}
inline void add(int x,int y,int z){edge[++tot].v=y;edge[tot].next=head[x];edge[tot].val=z;head[x]=tot;}
void bfs(int s){
	deque<int>q;q.push_front(s);memset(vis,0,sizeof(vis));memset(d,0x3f,sizeof(d));d[s]=0;
	while(q.size()){
		int u=q.front();q.pop_front();
		if(vis[u])continue;
		vis[u]=1; 
		for(int i=head[u];i;i=edge[i].next){
			int v=edge[i].v,z=edge[i].val;
			if(z){
				d[v]=min(d[v],d[u]+1);
				q.push_back(v);
			}
			else {
				d[v]=min(d[v],d[u]);
				q.push_front(v);
			}
		}
	}
}
int main()
{
		n=read();m=read();tot=0;memset(head,0,sizeof(head));
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
			{
				char ch;cin>>ch;
				if(ch=='\\'){
					add((m+1)*(i-1)+j,(m+1)*i+j+1,0);
					add((m+1)*i+j+1,(m+1)*(i-1)+j,0);
					add((m+1)*(i-1)+j+1,(m+1)*i+j,1);
					add((m+1)*i+j,(m+1)*(i-1)+j+1,1);
				}
				else {
					add((m+1)*(i-1)+j,(m+1)*i+j+1,1);
					add((m+1)*i+j+1,(m+1)*(i-1)+j,1);
					add((m+1)*(i-1)+j+1,(m+1)*i+j,0);
					add((m+1)*i+j,(m+1)*(i-1)+j+1,0); 
				}
			} 
		bfs(1);
		if(d[(n+1)*(m+1)]==0x3f3f3f3f)printf("NO SOLUTION\n");
		else printf("%d\n",d[(n+1)*(m+1)]);
	return 0;
}
/*
1
3 5
\\\\\
\\///
/\\\\   d[3]
*/
```


---

## 作者：XY_cpp (赞：0)

[更好的阅读体验](https://www.luogu.org/blog/user53410/solution-p2243)

$N$发全WA

搞了一番后发现队列没有清空

~~我真傻,真的。我单知道……~~

双端队列搜索，建一张大图，考虑到有些边不用翻转，为了使整个队列单调，将不用翻转的边能到达的点全部加入前端。

具体过程详情请见$2^6$行代码,~~还是个整数~~

```
#include<queue>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=505;
char map[maxn][maxn];//只有map存的是符号的坐标,其它都是存格点的.
bool used[maxn][maxn];
int dx[4]={1,1,-1,-1},
    dy[4]={1,-1,1,-1};
int n,m,dis[maxn][maxn];
deque< pair<int,int> >q,empty;//二元组,分别存x和y。
bool turn(int x1,int y1,int x2,int y2)
{
    int x=map[(x1+x2)/2][(y1+y2)/2]=='/'?1:-1;//判断电线是否直接连接两个点
    return x==(y1-y2)/(x1-x2);
}
void bfs()
{
    memset(used,0,sizeof(used));
    memset(dis,0x3f3f3f3f,sizeof(dis));
    q=empty;q.push_back(make_pair(0,0));dis[0][0]=0;//清零!!!
    while(!q.empty())
    {
        int a=q.front().first,
            b=q.front().second;
        q.pop_front();used[a][b]=true;
        for(int i=0;i<4;i++)
        {
            int x=dx[i]+a,y=dy[i]+b;
            if(x<0||n<x||y<0||m<y||used[x][y])
                continue;
            if(turn(a,b,x,y))//如果电线不直接连接两个点,即代价为1
            {//就把结点按正常入队
                dis[x][y]=min(dis[x][y],dis[a][b]+1);//注意要取最小值
                q.push_back(make_pair(x,y));
            }
            else//如果电线直连,那么到(a,b),(x,y)两个点的步数是一样的
            {//换句话说,他们的层级是一样的,由于一般的广搜的队列层级是单调递增的,所以为了保证这个性质,将(x,y)从队首入队.
                dis[x][y]=min(dis[x][y],dis[a][b]);
                q.push_front(make_pair(x,y));
            }
            if(x==n&&y==m) return;
        }
    }
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        for(int i=0;i<n;i++)
            scanf("%s",map[i]);
        if((n+m)%2)//易证到达终点的曼哈顿距离是偶数
        {
            puts("NO SOLUTION");
            continue;
        }
        bfs();
        printf("%d\n",dis[n][m]);
    }
    return 0;
}
```

---

## 作者：Yukhoi (赞：0)

这道题对我相当**不友好**5555555555

~~为了写题解还得 _换_ 个浏览器~~

~~这告诉我们**搜狗浏览器**是有多坑~~

总之，正如无数题解所言，这道题就是个裸的**双端队列**最短路

然而这道题坑就坑在同一个测试点有多组数据

~~导致很容易出现以下情况：~~

~~在上一组 _**大**_ 数据测完之后再来一组 _**小**_ 数据就容易出现越界~~

~~（这告诉我们**初始化**是有多么重要 ——来自一个为初始化而贡献**七**次提交的蒟蒻）~~

另附：没有好好判定数据的时候就很容易被Linux的**双换行符**坑哦~

~~已经有**两**位被坑的前辈了~~

# 好了上面都是废话下面才是正文：

## 思路：双端队列搜索

先将字符转成数字方便判断

然后我们根据是否需要旋转，给图中相邻的格子建边，一边做一边建就好，不用预处理

建边的规则：需要旋转那么就建权值为 1 的边，否则建权值为 0 的边

很容易想到，到达终点的最短路的长度就是所求的答案

那么我们采用双端队列的宽搜来做

很明显，权值为 0 的边要优于权值为 1 的边

故，在将节点入队的时候，将权值为 0 的插入队头，权值为 1 的插入队尾

然后就是正常跑最短路

P.S.1.此题同[P4667](https://www.luogu.org/problemnew/show/P4667)，而[P4667](https://www.luogu.org/problemnew/show/P4667)由于时限的缘故~~也许~~是当前这题的加强版，所以推荐大家趁热打铁再去切一下[P4667](https://www.luogu.org/problemnew/show/P4667)。

~~我才不会说我的代码也能直接切[P4667](https://www.luogu.org/problemnew/show/P4667)呢~~，毕竟还是有一丁点小不同的，如果你不改一下下确实切不了

P.S.2.惊奇地发现[P4667](https://www.luogu.org/problemnew/show/P4667)中某大佬的思路几乎跟在下这个蒟蒻一毛一样，在下的题解不会被判抄袭吧（笑）

### 完整代码

```
#include <bits/stdc++.h>

using namespace std;

inline char Getchar() {
	static char buf[35], *p1 = buf, *p2 = buf;
	return p1 == p2
		   && (p2 = (p1 = buf) + fread(buf, 1, 5201314, stdin),
			   p1 == p2) ? EOF : *p1++;
}

template<class T_T>void in(T_T &QAQ) {
	QAQ = 0;
	int QwQ = 0;
	char TAT = Getchar();
	while (!isdigit(TAT))
		QwQ |= (TAT == '-'), TAT = Getchar();
	while (isdigit(TAT))
		QAQ = (QAQ << 1) + (QAQ << 3) + (TAT ^ 48), TAT = Getchar();
	QAQ = QwQ ? -QAQ : QAQ;
}

inline void out(int QAQ) {

	int QwQ = 0;
	char TAT[20];

	if (!QAQ) putchar('0');
	else {
		if (QAQ < 0) putchar('-'), QAQ = -QAQ;
		while (QAQ) TAT[++QwQ] = (QAQ % 10) + 48, QAQ /= 10;
		while (QwQ) putchar(TAT[QwQ--]);
	}
	puts("");

	return ;
}
//以上为伟大的读优输优 

int n, m, T;
const int dt[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
// dt 数组储存下标移动的方向 
const int val[4] = {2, 1, 1, 2};
const int pos[4][2] = {{-1, -1}, {-1, 0}, {0, -1}, {0, 0}};
// val 数组和 pos 数组用于判断下一个的电路元件方向与当前元件是否相同
// 相同则将权值记为 0，否则为 1（也可理解为是否需要旋转，是即为 1，否即为 0） 
// 具体用法详见 Solve 函数 
int nx, ny, d, mp[505][505], dis[505][505];
// nx 和 ny 存下一个电路元件的坐标
// d 即为上面说的边权，只不过这个 d 只是暂时性存储当前边的权值
// mp 数组存电路元件方向，储存规律：'/'为 1，'\'为 2
// dis 数组当然是用来存当前点到起点的最短距离（旋转次数）啊 
struct node {
	int x, y;
	// 用于存储点的坐标信息的结构体
};
deque<node> q;
// 双端队列 

// gt 函数用于处理电路图，将电路图改成 1 或 2
// 改变规律同 mp 数组的储存规律 
inline int gt() {
	register char ch;
	while ((ch = Getchar()) != '/' && ch != '\\');
	// 需要注意'\'元件的读入，应码为 '\\'，其中第一个斜杠意为取消引用，至于效果请自行百度 
	return ch == '/' ? 1 : 2; // 转换 
}

// Solve 函数才是真正的主函数，下面的“主函数”只是为了多组数据而存在 
inline void Solve() {
	in(n), in(m);
	memset(dis, 0x3f, sizeof dis);
	memset(mp, -1, sizeof mp);
	for (register int i = 1; i <= n; ++i)
		for (register int j = 1; j <= m; ++j)
			mp[i][j] = gt();
	//一大波初始化啊初始化——来自一个为了初始化贡献七次提交的蒟蒻 
	q.push_back((node) {1, 1});
	dis[1][1] = 0;
	//把起点推入队列 
	register node u;
	// u 存当前点的信息 
	while (!q.empty()) {
		u = q.front();
		q.pop_front();
		for (register int i = 0; i < 4; ++i) {
			nx = u.x + dt[i][0], ny = u.y + dt[i][1];
			// 枚举下一个元件的下标
			// 由于当前元件可能旋转过也可能没有，所以四个方向都能进行枚举 
			d = mp[u.x + pos[i][0]][u.y + pos[i][1]] != val[i];
			//边权（是否旋转）的判断 
			if (nx && ny && nx < n + 2 && ny < m + 2
					&& dis[nx][ny] > dis[u.x][u.y] + d) {
				//判断是否出界与是否可以更新距离 
				dis[nx][ny] = dis[u.x][u.y] + d;
				d ? q.push_back((node) {nx, ny}) 
				: q.push_front((node) {nx, ny});
				// 根据单调性，把边权为 0 的点放到队头，边权为 1 的点放队尾 
				if (nx == n + 1 && ny == m + 1) break;
				//这里判断一下是否到达终点 
			}
		}
		if (nx == n + 1 && ny == m + 1) break;
		//这里又可以判断一下 
	}
	if (dis[n + 1][m + 1] != 0x3f3f3f3f) out(dis[n + 1][m + 1]);
	else puts("NO SOLUTION");
	// 判断有无答案，有就输出嘛，没有的话，还是输出嘛（笑）
}

int main() {

	in(T);
	while (T--) Solve();
	//每组数据调用一次 Solve 函数 

	return 0;
}
```

---

## 作者：z3475 (赞：0)

由楼上所说,这电路图可以转化成图，题目任务就是求最短路。

但是有几个需要注意的地方

1. 电路图的点转成图上的点

2. 存图可以用邻接表,vector<int>[],但是注意到题目中一个电路图上的点最多只可以有四条边，int M[251002][5]也行。

3. 在进行bfs中时如果你的dis[]没有作bfs的状态，千万不要听lyd书上说的第一次访问优化的方法

附代码

```c++
#include <bits/stdc++.h>

using namespace std;
#define pii pair<int,int>
pii M[251002][5];
int n[251002];
inline char gc(){
	register char t=getchar();
	while (t!='\\'&&t!='/') t=getchar();
	return t;
}
#define ri register int
inline void cnt(ri from,ri to,ri v){M[from][n[from]++]=pii(to,v);}
inline void cnt2(ri from,ri to,ri v){cnt(from,to,v);cnt(to,from,v);}
int dis[251002];
int R,C,to;
inline int f(ri i,ri j){return i*C+i+j;}
bool bfs(){
	deque<int> d;
	d.push_front(0);dis[0]=0;
	while (!d.empty()){
		ri from=d.front();d.pop_front();
		if (from==to) return true;
		for (ri t=0;t<n[from];t++){
			register pii &i=M[from][t];
			if (i.second==0){
				if (dis[i.first]>dis[from]){
					dis[i.first]=dis[from];
					d.push_front(i.first);
				}
			}else{
				if (dis[i.first]>dis[from]+1){
					dis[i.first]=dis[from]+1;
					d.push_back(i.first);
				}
			}
		}
	}
	return false;
}
int main(){
	ri T;
	scanf("%d",&T);
	while (T--){
		scanf("%d%d",&R,&C);
		for (ri i=1;i<=R;i++)
			for (ri j=1;j<=C;j++)
				if (gc()=='\\'){
					cnt2(f(i,j),f(i-1,j-1),0);
					cnt2(f(i-1,j),f(i,j-1),1);
				}else{
					cnt2(f(i,j),f(i-1,j-1),1);
					cnt2(f(i-1,j),f(i,j-1),0);
				}
		memset(dis,127,sizeof(dis));
		to=f(R,C);
		if (bfs()){
			cout << dis[to] << endl;
		}else{
			cout << "NO SOLUTION" << endl;
		}
		memset(n,0,sizeof(n));
	}
}
```

---

## 作者：Sino_E (赞：0)

令旋转后的边的边权为1，不旋转为0.

一个方块不会被重复走两遍，因为这不符合最短路贪心策略。

于是建图跑最短路就行。

假设一开始方块是`\`，方块的坐标为`i,j`，那么点的坐标就从`i,j`向`i+1,j+1`连边权为0的边，`i+1,j`向`i,j+1`连边权为1的边。`/`同理。

总共有$(n+1)(m+1)$个点.起点为`0,0`，终点为`n,m`。这个应该不会很难想。

那么点数可能要破$250000$，有两种方法跑最短路：Dijkstra+Heap，或者是SPFA+SLF+LLL优化。我用的后者。由于deque常数惊人，开了O2才过....

## Code

```cpp
// Code by ajcxsu
// Problem: Network
#include<bits/stdc++.h>
using namespace std;
const int N=3e5,M=3e6;
int h[N],to[M],nexp[M],W[M],p=1;
inline void ins(int a,int b,int w) {
    nexp[p]=h[a], h[a]=p, to[p]=b, W[p]=w, p++;
}
#define dins(x,y,z) ins(x,y,z), ins(y,x,z)

int n,m;
inline int point(int x,int y) {
    return x*(m+1)+y;
}

bool S[N];
int dist[N];
int SPFA(int s,int t) {
    memset(dist,0x3f,sizeof(dist));
    dist[s]=0;
    S[s]=1;
    deque<int> qu;
    qu.push_back(s);
    int na;
    int tot=0;
    while(!qu.empty()) {
        while(dist[qu.front()]>tot/qu.size()) qu.push_back(qu.front()), qu.pop_front();
        na=qu.front(), qu.pop_front();
        tot-=dist[na];
        S[na]=0;
        for(int u=h[na];u;u=nexp[u])
            if(dist[na]+W[u]<dist[to[u]]) {
                dist[to[u]]=dist[na]+W[u];
                if(!S[to[u]]) {
                    if(qu.empty() || dist[qu.front()]>dist[to[u]]) qu.push_front(to[u]);
                    else qu.push_back(to[u]);
                    tot+=dist[to[u]];
                }
            }
    }
    return dist[t];
}

int main() {
    ios::sync_with_stdio(false);
    int T;
    cin>>T;
    while(T--) {
        memset(h,0,sizeof(h)), p=1;
        cin>>n>>m;
        char ch;
        for(int i=0;i<n;i++)
        for(int j=0;j<m;j++) {
            cin>>ch;
            if(ch=='\\') dins(point(i,j), point(i+1,j+1),0), dins(point(i+1,j), point(i,j+1),1);
            if(ch=='/') dins(point(i,j), point(i+1,j+1),1), dins(point(i+1,j), point(i,j+1),0);
        }
        int ans=SPFA(point(0,0), point(n,m));
        if(ans==0x3f3f3f3f) cout<<"NO SOLUTION"<<endl;
        else cout<<ans<<endl;
    }

    return 0;
}

```

---

## 作者：fengjunjie (赞：0)

思路同楼下神犇，但是，求最短路的时候不能用folyd，普通dijkstra，我普通dijkstra50分

还有，每次操作一定要将数组清零！！！这是代码习惯问题，好吧，我承认本蒟蒻习惯不好

这里附上代码：




```cpp
 program ex02;
type rec=record n,t,d:longint; end;
     rec2=record num,data:longint; end;
var w:array[0..5001000] of rec;
    h,d,pl:array[0..300000] of longint;
    small:array[0..300000] of rec2;
    v:array[0..300000] of boolean;
    map:array[0..501,0..501] of string[2];
    t,n,m,tot,cnt:longint;
    i:longint;
procedure init;
var i,j:longint;
    s:ansistring;
begin
  readln(n,m);
  for i:=1 to n do
  begin
    readln(s);
    for j:=1 to m do
     map[i,j]:=s[j];
  end;
  fillchar(small,sizeof(small),127);
  small[0].data:=0;
end;
procedure make(x,y,k:longint);
begin
  inc(tot);
  w[tot].n:=h[x]; h[x]:=tot; w[tot].t:=y; w[tot].d:=k;
  inc(tot);
  w[tot].n:=h[y]; h[y]:=tot; w[tot].t:=x; w[tot].d:=k;
end;
procedure pre;
var i,j:longint;
begin
  for i:=1 to n do
   for j:=1 to m do
   begin
    if map[i][j]='/' then begin make((i)*(m+1)+j,(i-1)*(m+1)+j+1,0); make((i-1)*(m+1)+j,i*(m+1)+j+1,1); end;
    if map[i][j]='\' then begin make((i)*(m+1)+j,(i-1)*(m+1)+j+1,1); make((i-1)*(m+1)+j,i*(m+1)+j+1,0); end;
   end;
end;
procedure swap(a,b:longint);
var p:rec2; q:longint;
begin
  q:=pl[small[a].num]; pl[small[a].num]:=pl[small[b].num]; pl[small[b].num]:=q;
  p:=small[a]; small[a]:=small[b]; small[b]:=p;
end;
procedure put(x:longint);
var k:longint;
begin
  if pl[x]=0 then
  begin
    inc(cnt);
    pl[x]:=cnt;
    small[cnt].num:=x;
    small[cnt].data:=d[x];
    k:=cnt;
  end
  else
  begin
    small[pl[x]].data:=d[x];
    k:=pl[x];
  end;
  while small[k].data<small[k div 2].data do
  begin
    swap(k,k div 2);
    k:=k div 2;
  end;
end;
function get:longint;
var k:longint;
begin
  get:=small[1].num;
  pl[small[cnt].num]:=1;
  small[1]:=small[cnt];
  small[cnt].data:=maxlongint;
  k:=1;  dec(cnt);
  if cnt>0 then
  while (small[k].data>small[k*2].data) or (small[k].data>small[k*2+1].data) do
  begin
    if small[k*2].data<small[k*2+1].data then
    begin
      swap(k,k*2);
      k:=k*2;
    end
    else
    begin
      swap(k,k*2+1);
      k:=(k*2+1);
    end;
  end;
end;
procedure find(x:longint);
var k:longint;
begin
  k:=h[x];
  while k>0 do
  begin
    if not v[w[k].t] then
      if w[k].d+d[x]<d[w[k].t] then
      begin
        d[w[k].t]:=w[k].d+d[x];
        put(w[k].t);
      end;
    k:=w[k].n;
  end;
end;
procedure dij(x:longint);
var i:longint;
    p,min:longint;
begin
  d[x]:=0;
  v[x]:=true;
  find(x);
  for i:=1 to (n+1)*(m+1)-1 do
  begin
    if cnt>0 then
     p:=get
    else
     break;
    v[p]:=true;
    find(p);
  end;
end;
begin
  readln(t);
  for i:=1 to t do
  begin
    fillchar(v,sizeof(v),false);
    fillchar(d,sizeof(d),127);
    fillchar(h,sizeof(h),0);
    fillchar(w,sizeof(w),0);
    fillchar(pl,sizeof(pl),0);
    cnt:=0;
    tot:=0;
    init;             //读入
    pre;            //建边
    dij(1);          //堆优dij
        if d[(n+1)*(m+1)]<=20000000 then
     writeln(d[(n+1)*(m+1)])
        else writeln('NO SOLUTION');
  end;
end.
pascal 堆神马的最讨厌了（~~~~(>_<)~~~~）
```

---

## 作者：_虹_ (赞：0)

其实并不一定要手写堆。

感谢伟大的STL造福众生。

介绍一些stl提供的~~我第一次用的~~堆操作函数。
- （以下所有end都是数组尾的下一个元素）
- 生成堆：make_heap(T* begin,T* end)，将一个无序数组组织成堆。
- 插入值：在数组尾加上插入的数值，再调用push_heap(T* begin,T* end);维护堆的性质。
- 弹出堆顶：pop_heap(T* begin,T* end);江堆顶移动到队列尾部，其他部分维持堆的性质。
- 插入弹出要求数组已经是一个堆

没了优先队列底层的vector，不吸氧，堆+dij也就ac了。

~~跑了2758ms，最大点128ms。~~
```cpp
#include <iostream>
#include <algorithm>
//#include <memory.h>
using namespace std;

const unsigned int INT_MAX=2147483647;

const int kmaxn=260000;
const int kmaxm=kmaxn<<3;
/////////////////////////////////////////////////////
struct unit
{
	int first;
	int second;
	unit():first(0),second(0){};
	unit(int f,int s):first(f),second(s){};
	const int operator<(const unit& u)const
	{
		return first>u.first;
	}
};
class p_queue
{
	unit heap[kmaxm];
	int otail;
	public:
		p_queue():otail(0){};
		unit top(){
			pop_heap(&heap[0],&heap[otail]);
			return heap[otail-1];
		}
		void pop(){otail--;//以前是优先队列写的dij，干脆就这样凑活一下，其实top里弹出要安全一些，毕竟pop_heap之后数组尾元素已经不符合堆的性质了。
		}
		void push(const unit v){
			heap[otail++]=v;
			push_heap(&heap[0],&heap[otail]);
		}
		const bool empty()const{return !otail;}
}q;

//////////////////////////////////////////////////////
struct edge
{
	int dest=0;
	long long int length=0;
	edge* next=NULL;
};
const int max_pool_size=kmaxn<<2;
edge memory_pool[max_pool_size];
int pool_otail;
edge* list[kmaxn];//链式前向星是不会写的，这辈子也不会写前向星的
int result[kmaxn];
bool hsh[kmaxn];
void relax(int p)
{
	edge* t=list[p];
	while(t)
	{
		if(result[t->dest]>result[p]+t->length)
		{
			result[t->dest]=result[p]+t->length;
			q.push(unit(result[t->dest],t->dest));
		}
		t=t->next;
	}
}
void shortest_path(const int start)
{
	for(register int i=0;i<kmaxn;++i)
		result[i]=INT_MAX;
	q.push(unit(0,start));
	result[start]=0;
	int count=0;
	int t=0;
	while(!q.empty())
	{
			t=q.top().second;
			q.pop();
			if(!hsh[t])
			{
				relax(t);
				hsh[t]=true;
			}	
	}
}
void add_edge(const int& s,const int &d,const long long int &w)
{
	if(list[s])
	{
		memory_pool[pool_otail].next=list[s];
	}
	list[s]=&memory_pool[pool_otail++];
	list[s]->dest=d;
	list[s]->length=w;
}


////////////////////////////////////////////////////
int n,m;
char ch;
int main()
{
 	ios::sync_with_stdio(false);
 	cin>>n>>m;
 	++n;
 	++m;
 	for(register int i=1;i<n;++i)
 	{
 		for(register int f=1;f<m;++f)
 		{
 			cin>>ch;
 			if(ch=='\\')
 			{
 				//map[i][m*i+f]=1;
 				add_edge(m*(i-1)+f,m*i+f+1,0);
 				add_edge(m*i+f+1,m*(i-1)+f,0);
 				add_edge(m*(i-1)+f+1,m*i+f,1);
 				add_edge(m*i+f,m*(i-1)+f+1,1);
 			}
 			else
 			{
 				add_edge(m*(i-1)+f,m*i+f+1,1);
 				add_edge(m*i+f+1,m*(i-1)+f,1);
 				add_edge(m*(i-1)+f+1,m*i+f,0);
 				add_edge(m*i+f,m*(i-1)+f+1,0);
 			}
 		}
 	}
 	shortest_path(1);
 	if(result[n*m]==INT_MAX)
 	{
 		cout<<"NO SOLUTION"<<endl;
 	}
 	else
 	{
 		cout<<result[n*m]<<endl;
 	}
 	return 0;
} 
```
本人蒟蒻，希望各位神犇指出错误QAQ。~~还希望管理员给个通过。~~

---

