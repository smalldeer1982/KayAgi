# [USACO5.3] 校园网Network of Schools

## 题目描述

有一些学校会向其他学校分享软件，即如果这个学校得到了软件，那么在分享列表中的学校也会得到软件。注意这种关系是单向的，即如果 $a$ 在 $b$ 的列表中，那么 $b$ 不一定在 $a$ 的列表中。

现在，你需要向其中一些学校下发新软件。为了节约下发软件的成本，你需要回答以下两个问题。

1. 至少需要向几个学校下发新软件，可以使得所有学校均获得新软件。
2. 定义一次扩展为在某个学校的分享列表中增加一个学校。至少需要进行几次扩展，才可以使得无论对哪个学校**仅下发一次软件**就可以使得所有学校获得新软件。

两个问题相互独立。

## 说明/提示

$2 \le N \le 100$。

题目翻译来自 NOCOW。

USACO Training Section 5.3

## 样例 #1

### 输入

```
5
2 4 3 0
4 5 0
0
0
1 0```

### 输出

```
1
2```

# 题解

## 作者：Ametsuji_akiya (赞：134)

CAUTION！本篇目的在于纠正所有题解里的错误之处，可能有不妥之处，欢迎补充完善。

------------

缩点。

第一问简单，求一下无入度点个数即可。

第二问简化后问题是给一张DAG求最少添加几条边使得DAG变成一个SCC。首先所有中间点（有入度有出度）肯定直接顺着走到无出度点，所以肯定是无出度点连向无入度点。

把无入度点作为点集S，把无出度点作为点集T。

二分图连边表示S点（入度为零）可以走到T点（出度为零），然后先暴力匹配，表示每一个$S_i$尽可能走一个互不相同的$T_i$点，然后所有匹配边从$T_i$向下一个匹配的$S_{i+1}$连一条边，表示从$S_i\to T_i\to S_{i+1}$，如此往复，最终将最后一个$T_k$连向开始时的$S_1$，此时形成一个环，是SCC。然后剩下的没被选上的是不连通的。如果是$S_i$点表明他所有可以走到的$T$都被其他$S$走过去了，$T$也是一样，能走到他的$S$都走到其他点$T$了，于是就把每一对未匹配的$T$向$S$连一下边，最后如果还剩下来就随便连了。这样，会发现左右两侧的点就都被连上了一条边。所以最少连边数量是$\max(|S|,|T|)$。如果要求方案的话就用这个二分图的匹配就行了，~~如果数据大了呢？再见~~

注意：上述证明结论的方法我翻阅了绝大部分网络题解，发现讲的都比较随便，都是“无出度点和无入度点随便两两匹配，直到每个点都有出度入度就是SCC了”。

错误在于：1.并不是随便选无出度点和无入度点的。hack！

```
n=4  m=3
1 3
1 2
4 3
```

2.并不是每个点都有入度和出度就是SCC了，可能是两个环通过一个有向边相连什么的。

所以我认为大部分题解的证明和构造答案方法都是错的。

当然我并没有就认为我的一定是对的。如果有谁可以推翻我的改正说法，欢迎爆踩指正。

代码什么的。。网上满天飞了。就不放了

---

## 作者：_Lemon_ (赞：111)

一个比较简单的tarjian缩点，因为一个强连通分块里面可以互相到达，那么可以当成一个点处理。

任务A：

需要求最多在多少学校发送新软件，其实就是求缩点后入度为0的个数(如果入度不为0就可以从其他学校传过来)

任务B:

求入度为0的点数与出度为0的点的较大值。




```cpp
#include<bits/stdc++.h>
using namespace std;
int n,head[10005],cnt=0,col=0,sum;
int top=1,sta[10005],color[10005],tim[10005],low[10005],ins[10005];//color记录染色后点的颜色。
int in[10005],out[10005];//in和out分别是入度和出度。
struct net
{
     int to,next;
}e[1000000];
void add(int x,int y)
{
    cnt++;
    e[cnt].to=y;
    e[cnt].next=head[x];
    head[x]=cnt;
}
void tarjian(int x)//常规缩点
{
    sum++;
    tim[x]=low[x]=sum;
    sta[top]=x;
    top++;
    ins[x]=1;
    for(int w=head[x];w!=0;w=e[w].next)
    {
         if(ins[e[w].to]==0)
          {
                tarjian(e[w].to);
                low[x]=min(low[x],low[e[w].to]);
          }
         else if(ins[e[w].to]==1)
                low[x]=min(low[x],tim[e[w].to]);
    }
    if(tim[x]==low[x])
    {
        col++;
        do
        {
            top--;
            color[sta[top]]=col;
            ins[sta[top]]=-1;
        }while(sta[top]!=x);
    }
    return ;
}
int hym[1000000][3];
int main()
{
     int i,k=0;
     cin>>n;
     for(i=1;i<=n;i++)
     {
       int x;
       cin>>x;
       while(x!=0)
       {
              k++;
              add(i,x);
       hym[k][1]=i;
           hym[k][2]=x;//记下边，方便之后统计入度和出度。
           scanf("%d",&x);
       }
     }
     for(i=1;i<=n;i++)
         if(!ins[i]) tarjian(i);
     for(i=1;i<=k;i++)
         if(color[hym[i][1]]!=color[hym[i][2]])//同种颜色不需要统计，不同颜色更改出度和入度。
           {
                 out[color[hym[i][1]]]++;
                 in[color[hym[i][2]]]++;
           }
     int ans1=0,ans2=0;
     for(i=1;i<=col;i++)
     {
         //cout<<in[i]<<' '<<out[i]<<endl;
         if(in[i]==0)  ans1++;
         if(out[i]==0) ans2++;
     }
     if(col==1) cout<<1<<endl<<0;
     else
        cout<<ans1<<endl<<max(ans1,ans2);
     return 0;
}
```

---

## 作者：天南地北 (赞：46)

简化题意：

$A$任务：接受新软件副本的最少学校数目

$B$任务：计算最少需要增加几个扩展，使得不论我们给哪个学校发送新软件，它都会到达其余所有的学校

我们可以通过题目的样例来构图找一下思路：(图丑，请见谅)

![](https://cdn.luogu.com.cn/upload/image_hosting/u9km9dwq.png)

如图，这就是几个学校的分发列表，我们只是通过一条条有向边来指向了它分发列表中的一个个节点

***
我们首先来解决一下$A$任务:

对于任何一个节点，要不然就是从**指向它的节点收到新软件**，然后通过自己的分发列表再分发出去；要不然就是**自己接受新软件副本**，并通过自己的分发列表再分发出去。

$Q:$那我们如何计算最少学校数目？

$A:$我们先在上面的图做缩点：

![](https://cdn.luogu.com.cn/upload/image_hosting/vvsaj2c7.png)

你会发现，我们只要在$1,2,5$这个缩点里面的任意一个点分发新软件副本，就可以保证所有学校都能够收到别的学校发送过来的软件副本。而$1,2,5$这个缩点，它的特征——出度为$0$，即为判断$A$任务的判断条件

综上所述，**$A$任务：找出度为$0$的缩点个数。**

***
接下来我们解决$B$任务。

既然不论我们给哪个学校发送新软件，它都会到达其余所有的学校，所以：**我们需要使得这个图成为一个强连通分量！**

![](https://cdn.luogu.com.cn/upload/image_hosting/vvsaj2c7.png)

还是用上面那个图来说明一下：

我们既然要把上面那个图成为一个强连通分量，我们需要作出$3->$$(1,2,5)$这一条边，以及$4->$$(1,2,5)$这一条边。

那我们可不可以这样想：

既然要把使得这个图成为一个强连通分量，那么对于一个强连通分量来说，每个节点出入度不应该为$0$，应该至少为$1$,他们才能够形成强连通分量，所以就是找出入度为$0$的节点的个数，然后比较最大值即可。

注意：如果原图就是一个强连通分量，我们并不需要给它加边，即为$0$.

综上所述,**$B$任务:找出入度为$0$的节点的个数，然后比较最大值，（原图是一个强连通分量就为$0$）**
***
所以：
- **$A$任务：找出度为$0$的缩点个数。**
- **$B$任务:找出入度为$0$的节点的个数，然后比较最大值**

那么对于这两个任务，我们需要先建图，跑$Tarjan$,找到缩点，然后计算缩点的出入度，分任务回答即可。

参考程序：
```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
#pragma G++ optimize (2)//O2优化
using namespace std;
const int N=100+10;
int n;
int cnt,top,col;
vector<int>G[N];
int dfn[N],low[N],st[N],color[N],col_s[N];
int rd[N],cd[N];
void Tarjan(int u)//跑Tarjan
{
  dfn[u]=low[u]=++cnt;
  st[++top]=u;
  for(int i=0; i<G[u].size(); ++i)
  {
    int v=G[u][i];
    if(!dfn[v])
    {
      Tarjan(v);
      low[u]= min(low[u], low[v]);
    }
    else if(!color[v]) 
    low[u]= min(low[u], dfn[v]);
  }
  if(low[u]==dfn[u])
  {
    color[u]=++col;
    while(st[top]!=u)
    {
      color[st[top]]=col; 
      top--;
    }
    top--; 
  }
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		while(x!=0)
		{
			G[i].push_back(x);//建立边
			cin>>x;
		}
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])Tarjan(i);
	for(int u=1;u<=n;u++)
	{
		for(int j=0;j<G[u].size();j++)
		{
			int v=G[u][j];
			if(color[u]!=color[v])
			rd[color[v]]++,cd[color[u]]++;//计算缩点的出入度
		}
	}
	int Aans=0,Bans=0;
	for(int i=1;i<=col;i++)
	{
		if(rd[i]==0)Aans++;
		if(cd[i]==0)Bans++;//计算各个任务的答案
	}
	cout<<Aans<<endl;
	if(col==1)cout<<0;//整个图本身为强连通分量,并不需要加边
	else cout<<max(Aans,Bans);
}
```


---

## 作者：s223568907 (赞：26)

看到大佬们都是tarjan，蒟蒻还不会，只好想别的办法了......

对于这张图，由于数据范围很小，所以可以先用floyed求传递闭包，

然后缩点，如果缩点后只有一个点，则答案为1，0；

否则对于第一问，如果缩点后某一点的入度为0，则它肯定要一份软件，如果不为0，则一定可以从别的点获得软件，

而对于下一个问题，缩点后，对每个出度为0的点，需拓展一条出边，

对每个入度为0的点，需拓展一条入边，则可以完成条件。

所以为了拓展的边更少，可以从出度为0的点向入度为0的点拓展边。

所以所需最少的拓展数即出度为0的点数和入度为0的点数的较大者。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[110][110]={0},l[110][110]={0},n;
int in[110]={0},out[110]={0},team[110]={0};
int ins=0,outs=0,sum=0;
inline void init()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        int t;
        scanf("%d",&t);
        while(t>0)
        {
            a[i][t]=l[i][t]=1;
            in[t]++;//需要记录入度和出度
            out[i]++;
            scanf("%d",&t);
        }
    }
    return;
}

inline void floyed()
{
    for(int k=1;k<=n;k++)
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    a[i][j]=a[i][j]||(a[i][k]&&a[k][j]);
    return;
}

inline void work()
{
    memset(team,-1,sizeof(team));
    for(int i=1;i<=n;i++)
    {
        if(team[i]==-1)//如果i点未涂色 
        team[i]=i;//涂色 
        else
        {
            in[team[i]]+=in[i];//i所属的强联通分量入度加上i的入度 
            out[team[i]]+=out[i];//出度同理 
        }
        for(int j=1;j<=n;j++)//这里每个点都要搜一遍 
        if(a[i][j]&&a[j][i])//如果i,j属于同一强联通分量 
        {
            team[j]=team[i];//涂色 
            if(l[i][j])//如果i,j直接有边相连 
            {
                in[team[i]]--;//i所属的强联通分量入度-1
                out[team[i]]--;//出度同理 
            }
        }
    }
    return;
}

inline void print()
{
    for(int i=1;i<=n;i++)
    if(team[i]==i)//搜索缩点后的各个点 
    {
        sum++;//强连通分量数 
        if(in[i]==0)ins++;//入度为0的点数 
        if(out[i]==0)outs++;//出度为0的点数 
    }
    if(sum==1)printf("1\n0");//如果只有一个强联通分量 
    else printf("%d\n%d",ins,max(ins,outs));
    return;
}

int main()
{
    init();
    floyed();
    work();
    print();
    return 0;
}
```

---

## 作者：沉辰 (赞：23)

Tarjan +强连通分量+缩点

在缩点后的图中，因为要找最少的提供者，即就是入度为0

的点，统计一下。

对于第二问，即是第一问的升级版，仔细思考一下，从一个点出发可以

便利到所有的点，那就是只有出发点的入度为0，就想办法

把其他点的入度编程1（因为是“至少”），

。。。。。。。。

反着建边，那么出度为0的点就变成了入度为0的点，此时要求

只有一个入度为0的点，联想上面所说，很容易想到第二问的答案

就是max{入度为0的点的个数，出度为0的点的个数}；

然后输出答案即可（注意强连通分量为一的特殊情况，需要特判）

因为tarjan各人的写法不同，所以不贴代码了。加油。(✿◡‿◡)


---

## 作者：crh1272336175 (赞：21)

# 强连通分量+缩点+拓扑DP

## 分析

$Tarjan$ 缩点将原图转化成$DAG$，统计每个强连通分量的出度入度，起点数量为 $src$，终点数量为$des$。对于一个强连通分量，其中只要有一所学校获得新软件那么整个分量都能获得。

## 问题一

### 结论

只要把软件给所有起点即可，答案为起点个数 $src$。

### 证明

所有起点都无法由别的点到达，因此每个起点必须分配一个软件，而对于其他所有点，一定存在前驱，一定能由某一个起点走到，也就是说从所有起点出发，能遍历整个图。因此只需要给所有起点各一个软件即可。

## 问题二

### 结论

若 $cnt=1$（只有一个强连通分量),则不需要连新的边，答案为$0$。

若 $cnt>1$，则答案为 $max(src,des)$。

### 证明
结论 1 正确性显然，下面证明结论 2。

设缩点后的 DAG 中，起点（入度为 0）的集合为 P，终点（出度为 0）的集合为 Q。分以下两种情况讨论：

#### 1.$|P|≤|Q|$

① 若$ |P|=1$，则只有一个起点，并且这个起点能走到所有点，只要将每一个终点都向这个起点连一条边，那么对于图中任意一点，都可以到达所有点，新加的边数为 $|Q|$。

② 若 $|P|≥2$，则 $|Q|≥|P|≥2$，此时至少存在 2 个起点 $p1,p2$，2 个终点 $q1,q2$，满足 $p1$能走到 $q1$，$p2$ 能走到$q2$。（反证法：如果不存在两个起点能走到不同的终点，则所有的起点一定只能走到同一个终点，而终点至少有两个，发生矛盾，假设不成立）

那么我们可以从$ q1$向$p2$新连一条边，那么此时起点和终点的个数都会减少一个（$p2$不再是起点,$q1$不再是终点），因此只要以这种方式，连接新边 $|P|−1$条，则 $|P'|=1$，而 $|Q'|=|Q|−(|P|−1)$，由 ① 得，当$ |P'|=1$时，需要再连 $|Q'|$条新边，那么总添加的新边数量为 $|P|$−$1$+$|Q|$−($|P|$−1)=$|Q|$

#### 2.$|Q|≤|P|$
与情况 11 对称，此时答案为 $|P|$。

综上所述，$scc_cnt>1$ 时，问题二的答案为$ max(|P|,|Q|)$即 $max(src,des)$)。

AC代码:
```cpp
#include<bits/stdc++.h>
#pragma GCC opitimize(2)
using namespace std;
const int N=1e5+5;
namespace Read
{
    inline int read()
    {
        int s=0,f=1; char ch=getchar();
        while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
        while(isdigit(ch)) s=s*10+(ch^48),ch=getchar();
        return s*f;
    }
    inline void write(int x)
    {
        if(x<0) putchar('-'),x=-x;
        if(x>9) write(x/10);
        putchar(x%10+'0');
    }
}using namespace Read;
namespace Gragh
{
	int n,m,tot=0;
	int head[N],Next[N<<1],des[N<<1];
	inline void add(int a,int b)
	{
		Next[++tot]=head[a]; des[tot]=b; 
		head[a]=tot;
	}
}using namespace Gragh;
namespace Tarjan
{
	int num=0,cnt=0;
	int low[N],dfn[N],ins[N],c[N];
	stack<int> stk;
	vector<int> scc[N];
	void tarjan(int x)
	{
		low[x]=dfn[x]=++num;
		stk.push(x); ins[x]=1;
		for(int i=head[x]; i; i=Next[i])
		{
			int y=des[i];
			if(!dfn[y])
			{
				tarjan(y);
				low[x]=min(low[x],low[y]);
			} 
			else if(ins[y]) low[x]=min(low[x],dfn[y]);
		}
		if(dfn[x]==low[x])
		{
			int y; cnt++;
			do
			{
				y=stk.top(); stk.pop(); ins[y]=0;
				c[y]=cnt; scc[cnt].push_back(y);
			}while(y!=x);
		}
	}
}using namespace Tarjan;
namespace ContractionPoint
{
	int tot2=0;
	int head2[N],Next2[N<<1],des2[N<<1],in[N],out[N];
	inline void add2(int a,int b)
	{
		Next2[++tot2]=head2[a]; des2[tot2]=b; 
		head2[a]=tot2; in[b]++; out[a]++; 
	}
}using namespace ContractionPoint;  
int main()
{
	n=read();
	for(int i=1; i<=n; i++)
	{
		while(true)
		{
			int x=read();
			if(!x) break;
			add(i,x);
		}
	} 
	for(int i=1; i<=n; i++)
	    if(!dfn[i]) tarjan(i);
	for(int x=1; x<=n; x++)
	    for(int i=head[x]; i; i=Next[i])
		{
			int y=des[i];
			if(c[x]!=c[y]) add2(c[x],c[y]);
		} 
	int ans1=0,ans2=0;
	for(int i=1; i<=cnt; i++)
	    if(in[i]==0) ans1++;
	for(int i=1; i<=cnt; i++)
	    if(out[i]==0) ans2++;
	ans2=max(ans2,ans1);
	if(cnt==1) ans2=0;
	write(ans1),puts(""),write(ans2);
	return 0;
}
```
注：本题解非原创，转载自https://www.acwing.com/solution/content/4663/



---

## 作者：sukimo (赞：11)

思路比较经典，先用tarjan算法缩点得到一个DAG。第一个子任务只需统计DAG中入度为$0$的点的个数即为答案，因为如果某点入度为$0$，则只能自己先接收新软件；不为$0$，则可以由其他学校分发。第二个问题稍微复杂一点，如果该DAG已经强连通，则结果为$0$，很显然；否则将入度为$0$的点数设为$x$，出度为$0$的点数设为$y$，则结果为$max\{x,y\}$。为什么呢？首先，一个强连通图必须保证不含出度和入度为$0$的点，否则不符合定义；所以说我们要把这$x+y$个点进行连接。然后一个出度为$0$的点可以和一个入度为$0$的点连一条边，这样就互补了，且尽量最少。但是很明显，有$\mid x-y\mid$个点无法互补，这样就把它们任意和其他点连边，最终结果正是$max\{x,y\}$。

代码：

```
#include<bits/stdc++.h>
using namespace std;
stack<int>stk;bool in_stk[105],flag=1;int n,edge_cnt,ind,in[105],out[105],low[105],mark[105],fir[105],order[105];struct STR{int next,to;}edge[10005];
void add(int u,int v){
	edge[++edge_cnt].next=fir[u];fir[u]=edge_cnt;edge[edge_cnt].to=v;
}
void tarjan(int x){
	order[x]=low[x]=++ind;in_stk[x]=1;stk.push(x);
	for(int i=fir[x];i;i=edge[i].next)
		if(!order[edge[i].to]){
			tarjan(edge[i].to);low[x]=min(low[x],low[edge[i].to]);
		}
		else if(in_stk[edge[i].to])low[x]=min(low[x],order[edge[i].to]);
    if(order[x]==low[x]){
    	int rem,node_cnt=0;
    	do{
    		rem=stk.top();node_cnt++;mark[rem]=x;in_stk[rem]=0;stk.pop();
    	}while(rem!=x);
    	if(node_cnt==n)flag=0;
    }
}
int main(){
	int in_0=0,out_0=0;scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int v;;){scanf("%d",&v);if(!v)break;add(i,v);}
	for(int i=1;i<=n;i++)if(!order[i])tarjan(i);
	for(int i=1;i<=n;i++)
		for(int j=fir[i];j;j=edge[j].next)
			if(mark[i]!=mark[edge[j].to]){out[mark[i]]++;in[mark[edge[j].to]]++;}
	for(int i=1;i<=n;i++)
		if(mark[i]==i){if(!in[i])in_0++;if(!out[i])out_0++;}
	printf("%d\n%d",in_0,flag?max(in_0,out_0):0);
	return 0;
}
```


---

## 作者：w_x_c_q (赞：11)

**题解：Tarjan模板题
		链式前向星建边
		跑Tarjan找强连通分量将其缩成一个点
		不过不用连新的边了，枚举每一条边，若这条边的两个端点分属于不同的强连通分量，则u所在的强连通分量缩成的点的出度加一，v所在的强联通分量缩成的点的入度加一；
		对于子问题A：我们统计缩点之后的点中，入度为零的点有多少个，即为答案；
		对于子问题B：我们的目的是将整个图凑成强联通，那么统计入读和出度的最小值，即为答案；
**
```cpp
#include<iostream>
#include<cstdio>
#define cq(i,s,n) for(int i=s;i<=n;i++)
using namespace std;
#define N 10020
int n;
int x;
int num,top,col;
int in[N],out[N];
int dfn[N],low[N];
int belong[N]; 
int sumin,sumout,tot,sz;
int st[N];
struct node{
	int nxt,to;
}edge[N];
int head[N],dis[N],vis[N], fr[N];
void add(int from,int to){
	edge[++num].nxt=head[from];
	edge[num].to=to;
	fr[num] = from;
//	edge[num].dis=dis;
	head[from]=num;
}
void Tarjan(int u){
	dfn[u]=low[u]=++tot;
	st[++top]=u;
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].to;
//		if(u == 1 && v == 3) cout<<"fuck\n";
		if(!dfn[v]){
			Tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(!belong[v]){
			low[u]=min(low[u],dfn[v]);
		}
	}
	if(low[u]==dfn[u]){
		belong[u]=++col;
		while(st[top]!=u){
			belong[st[top]]=col;
			top--;
		}
		top--;
//		cout<<u<<"---"<<belong[u]<<endl;
	}
}
int main(){
	scanf("%d",&n);
	cq(i,1,n){
		scanf("%d",&x);
		while(x!=0){
			add(i,x);
			scanf("%d",&x);
		}
	}
 
	cq(i,1,n){
		if(!dfn[i])Tarjan(i);
	}
//	cout<<belong[3]<<endl;
	for(int i=n;i>=1;i--){
		for(int j=head[i];j;j=edge[j].nxt){
			int v=edge[j].to;
			if(belong[i]!=belong[v]){
				
				out[belong[i]]++;
				in[belong[v]]++;
			}
		}
	}
//	for(int i = 1; i <= num; ++ i) {
//		int x = belong[fr[i]], y = belong[edge[i].to];
//		if(x == y) continue;
//		cout<<x<<' '<<y<<endl; 
//		in[y] ++;
//		out[x] ++;
//	}
	cq(i,1,col){
		sumin+=(in[i]==0?1:0);
//		cout<<in[i]<<endl;
		sumout+=(out[i]==0?1:0);
	}
	if(col==1){
		printf("1\n0");
		return 0;
	}
	printf("%d\n%d",sumin,max(sumin,sumout));
	return 0;
}


```

---

## 作者：「QQ红包」 (赞：9)

tarjan的模板题（嗯可以看lrj的书

- 第一问：至少要给多少个学校软件，才能保证所有学校都有软件用，也就是求缩点后入度为0的点的个数（因为入度为0的话没有其他学校能传软件给它）

- 第二问：使缩点后所有学校的入度和出度都大于0（这样就可以给任意学校软件，然后所有学校都能用上软件

**如果是一个强连通图需要特判。**

```cpp
/*
ID: ylx14271
PROG: schlnet
LANG: C++
*/
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<stack>
#include<cstdio>
using namespace std;
int read()
{
    char ch=getchar();
    int x=0;
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar(); 
    return x;
}
int s[20100],top;
int low[21000];//存能搜到的最早的点 
int pre[21000];//存自己的时间 
int dfs_clock; 
struct node
{
    int x,y,d;
} a[4000000];
int po[21000],m;
int n,x1;
int scc[21000],id;
int c[21000];//出度 
int r[21000];//入度 

void dfs(int u)
{
    top++;
    s[top]=u;
    low[u]=++dfs_clock; //存自己的时间和 
    pre[u]=dfs_clock; 
    for (int i=po[u];i!=0;i=a[i].d)
    {
        int v=a[i].y;//提出点 
        if (pre[v]==0)//没有扫过 
        {
            dfs(v);//扫一遍 
            low[u]=min(low[u],low[v]);//更新 
        } else
        if (scc[v]==0)//如果在别的联通块就不管了 
        {
            low[u]=min(low[u],pre[v]);
        }
    }
    int k; 
    if (pre[u]==low[u])//自己是自己的祖先（也就是扫不到时间更早的点了 
    {
        id++;
        while (1)
        {
            k=s[top];top--;
            scc[k]=id;
            if (k==u) break;
        }
    }
}
int main()
{
    freopen("schlnet.in","r",stdin);
    freopen("schlnet.out","w",stdout);
    n=read();
    for (int i=1;i<=n;i++)
    {
        x1=read();
        while (x1!=0)
        {
            m++;
            a[m].x=i;
            a[m].y=x1;
            a[m].d=po[a[m].x];
            po[a[m].x]=m;
            x1=read();
        }
    }//读入 
    for (int j=1;j<=n;j++)
    {//因为并不一定是个连通图，so 
        if (pre[j]==0) dfs(j);
    }
    for (int i=1;i<=m;i++)
    {
        if (scc[a[i].x]!=scc[a[i].y])//自己图内不管 
        {
            c[scc[a[i].x]]++;//x的出度+1 
            r[scc[a[i].y]]++;//y的入度+1 
        }
    } 
    int ans1=0;
    int ans2=0;
    for (int i=1;i<=id;i++)//统计出度入度为0的点的出现次数 
    {
        if (r[i]==0) ans1++;
        if (c[i]==0) ans2++;
    }
    ans2=max(ans2,ans1);//第二问，所有点要出度不为0而且入度不为0 
    if (id==1) ans1=1,ans2=0;//嗯要特判 
    printf("%d\n%d\n",ans1,ans2);
    return 0;
}
```

---

## 作者：kradcigam (赞：4)

## 之前的bug现已修复

# 前置知识：

- [强联通分量](https://blog.csdn.net/qq_46230164/article/details/105406699)

# 分析

这道题的话，我们先考虑缩点。

不会缩点的可以看一下我的[文章](https://blog.csdn.net/qq_46230164/article/details/105406699)

既然我们缩好点了，那么整张图变成了一个 $DAG$（有向无环图）

这样就好处理了。

- 对于问题 `A`

	我们发现既然这整张图是 $DAG$，那么答案显然为入度为 $0$ 的点的个数
    
- 对于问题 `B`
	我们发现这整张图是 $DAG$。我们要把它变成连通图。
    
    连通图需要满足：
    - 没有入度为 $0$ 的点
    - 没有出度为 $0$ 的点
    
    考虑入度为 $0$ 和 出度为 $0$ 的点两两匹配，则需要匹配 $\max\{ \texttt{入度为}\ 0\ \texttt{的点},\texttt{入度为}\ 1\ \texttt{的点}$ 次。
    
# 一些细节

注意缩点后只有一个点的情况，本身就是连通的，所以 问题 `B` 的答案为 $0$

```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename T>inline void read(T &FF){
	T RR=1;FF=0;char CH=getchar();
	for(;!isdigit(CH);CH=getchar())if(CH=='-')RR=-1;
	for(;isdigit(CH);CH=getchar())FF=(FF<<1)+(FF<<3)+(CH^48);
	FF*=RR;
}
template<typename T>inline void write(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar('0'+x%10);
}
const int MAXN=1e6+10,MAXM=1e6+10;
int s[MAXN],stop,dfn[MAXN],low[MAXN],scccnt,sccnum[MAXN],dfscnt,tot,he[MAXN],ne[MAXM<<1],ed[MAXM<<1],n,x,se,es,du[MAXN],ud[MAXN];
void add(int x,int y){
	ed[++tot]=y;
	ne[tot]=he[x];
	he[x]=tot;
}
inline void tarjan(int now){
	dfn[now]=low[now]=++dfscnt;
	s[stop++]=now;
	for (int i=he[now];i;i=ne[i]){
		if(!dfn[ed[i]]){
			tarjan(ed[i]);
			low[now]=min(low[now],low[ed[i]]);
		}else if(!sccnum[ed[i]]){
			low[now]=min(low[now],dfn[ed[i]]);
		}
	}
	if(dfn[now]==low[now]){
		scccnt++;
		do{
			sccnum[s[--stop]]=scccnt;
		}while(s[stop]!=now);
	}
}//tarjin的板子
int main(){
	read(n);
	for(int i=1;i<=n;i++)
		while(cin>>x&&x)add(i,x);
	for(int i=1;i<=n;i++)
		if(!dfn[i])tarjan(i);
	for(int i=1;i<=n;i++)
		for(int j=he[i];j;j=ne[j])
			if(sccnum[i]!=sccnum[ed[j]]){
				du[sccnum[ed[j]]]++;//统计
				ud[sccnum[i]]++;//统计
			}
	for(int i=1;i<=scccnt;i++){
		if(!du[i])se++;//入度为0的点
		if(!ud[i])es++;//出度为0的点
	}
	cout<<se<<endl<<(scccnt==1?0:max(se,es));//小细节
	return 0;
}
```

---

## 作者：bellmanford (赞：2)

先进行缩点，得到一个DAG（有向无环图）

可以知道：

1.入度为零的点为传入点

2.出度为零的点和入度为零的点的最大值为应连的边


对于1： 

由于入度为零，其他的学校无法将信息传递过去

所以只能从这个点开始传递

当所有传递点的入度都是零时，数目最小


对于2：

因为题目要求从每一个点都可以传递到所有点

所以是将这个DAG转变为一个强连通分量

所以转变后的图没有入度为零和出度为零的点

所以将目前出度为零和入度为零的点两两配对

多余的随便连其他点

答案便为出度为零的点和入度为零的点的最大值

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int M=100005;
int n,tot,num=0,top=0,cnt=0,first[M];
int in[M],out[M],sd[M],stack[M],dfn[M],low[M];
bool instack[M];
struct Edge1{
	int nxt,to,from;
}e[M<<1];

void add(int x,int y){
	tot++;
	e[tot].nxt=first[x];
	first[x]=tot;
	e[tot].to=y;
	e[tot].from=x;
}

void tarjan(int u){
	dfn[u]=low[u]=++num;
	stack[++top]=u;
	instack[u]=1;
	for(int i=first[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(instack[v]) low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		cnt++;
		while(1){
			int v=stack[top--];
			sd[v]=u;
			instack[v]=0;
			if(u==v) break;
		}
	}
}

int main(){
//	freopen("testdata.in","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int x;
		while(1){
			scanf("%d",&x);
			if(x==0) break;
			add(i,x);
		}
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i]){
			tarjan(i);
		}
	}
	for(int i=1;i<=tot;i++){
		int x=sd[e[i].from],y=sd[e[i].to];
		if(x!=y){
			out[x]++;
			in[y]++;
		}
	}
	int ans1=0,ans2=0;
	for(int i=1;i<=n;i++){
		if(sd[i]==i){
			if(in[i]==0) ans1++;
			if(out[i]==0) ans2++;
		}
	}
	if(cnt==1) printf("1\n0\n");
	else printf("%d\n%d\n",ans1,max(ans1,ans2));
}
```


---

## 作者：多多良假伞 (赞：2)

## P2746 [USACO5.3]校园网Network of Schools
 
[题目链接](https://www.luogu.org/problemnew/show/P2746)
 
 

## 题目描述

一些学校连入一个电脑网络。那些学校已订立了协议：每个学校都会给其它的一些学校分发软件（称作“接受学校”）。注意即使 B 在 A 学校的分发列表中， A 也不一定在 B 学校的列表中。

你要写一个程序计算，根据协议，为了让网络中所有的学校都用上新软件，必须接受新软件副本的最少学校数目（子任务 A）。更进一步，我们想要确定通过给任意一个学校发送新软件，这个软件就会分发到网络中的所有学校。为了完成这个任务，我们可能必须扩展接收学校列表，使其加入新成员。计算最少需要增加几个扩展，使得不论我们给哪个学校发送新软件，它都会到达其余所有的学校（子任务 B）。一个扩展就是在一个学校的接收学校列表中引入一个新成员。



## 输入输出格式

### 输入格式：

输入文件的第一行包括一个整数 N：网络中的学校数目（2 <= N <= 100）。学校用前 N 个正整数标识。

接下来 N 行中每行都表示一个接收学校列表（分发列表）。第 i+1 行包括学校 i 的接收学校的标识符。每个列表用 0 结束。空列表只用一个 0 表示。

### 输出格式：

你的程序应该在输出文件中输出两行。

第一行应该包括一个正整数：子任务 A 的解。

第二行应该包括子任务 B 的解。

## 题解

题目给出一张有向图

我们可以考虑使用Tarjan算法求强连通分量，进行缩点，将一个强连通分量（即几个互相能达到的学校）缩为一个点，对缩点后的图统计入度$(inDegree)$和出度$(outDegree)$。

对于子任务 $\mathrm A$

> 根据协议，为了让网络中所有的学校都用上新软件，必须接受新软件副本的最少学校数目

可以理解为求入度为$0$的强连通分量的个数

对于子任务 $\mathrm B$

> 计算最少需要增加几个扩展，使得不论我们给哪个学校发送新软件，它都会到达其余所有的学校。

可以理解为将整张图形成一张强连通图。

那么可以考虑将出度为$0$的强连通分量连向入度为$0$的强连通分量，则至少需要形成$\mathrm{max}(ansIn,ansOut)$条边($ansIn$为入度为$0$的强连通分量的个数，$ansOut$为出度为$0$的强连通分量的个数)

想到这里，这道题我们基本就分析结束了

但是有一点需要注意一下，如果给出的图本来就是一张强连通图，那么按照之前的思路，子任务$B$得到的答案就是$\mathrm{max}(1,1)$，即$1$，这显然是不对的，这时候我们就需要特判一下。

```cpp
	if(clnum==1)//对于强连通图进行特判
        printf("%d\n%d",ansIn,0);
    else
        printf("%d\n%d",ansIn,max(ansIn,ansOut));
```


#### 以下是完整代码

```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<stack>
using namespace std;

template<class T>inline void read(T &x){
    T f=1;x=0;char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-') f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=x*10+c-'0';
        c=getchar();
    }
    x*=f;
}
const int maxn=105;
struct node{
    int next;
    int to;
}edge[10010];
int n,cnt,ti,clnum,ansIn,ansOut;
int head[maxn],sum[maxn],inDegree[maxn],outDegree[maxn];
int dfn[maxn],low[maxn],color[maxn];
bool vis[maxn];
stack<int>sa;

inline void add(int u,int v){//链式前向星存图
    edge[++cnt].next=head[u];
    edge[cnt].to=v;
    head[u]=cnt;
}

void tarjan(int now){//个人感觉是比较正常的tarjan写法
    dfn[now]=low[now]=++ti;
    sa.push(now);vis[now]=true;
    for(int i=head[now];i;i=edge[i].next){
        int j=edge[i].to;
        if(!dfn[j]) tarjan(j),low[now]=min(low[now],low[j]);
        else if(vis[j]) low[now]=min(low[now],dfn[j]);
    }
    if(dfn[now]==low[now]){
        ++clnum;
        while(now!=sa.top()){
            int t=sa.top();
            sa.pop();vis[t]=false;
            color[t]=clnum;++sum[clnum];
        }
        sa.pop();vis[now]=false;
        color[now]=clnum;++sum[clnum];//染色(求强连通分量)
    }
}

int main(){
    read(n);
    for(int i=1;i<=n;++i){
        while(1){
            int k;read(k);
            if(k==0) break;
            add(i,k);
        }
    }
    for(int i=1;i<=n;++i)
        if(!dfn[i])
            tarjan(i);
    for(int u=1;u<=n;++u){//遍历,统计出度入度
        for(int i=head[u];i;i=edge[i].next){
            if(color[u]!=color[edge[i].to]){
                ++outDegree[color[u]];
                ++inDegree[color[edge[i].to]];
            }//注意 统计的是强连通分量的出度入度,不要统计成原图的出度入度
        }
    }
    for(int i=1;i<=clnum;++i){
        if(!inDegree[i]) ++ansIn;
        if(!outDegree[i]) ++ansOut;
    }
    if(clnum==1)//对于强连通图进行特判
        printf("%d\n%d",ansIn,0);
    else
        printf("%d\n%d",ansIn,max(ansIn,ansOut));
    return 0;
}
```

---

## 作者：M_PI (赞：2)

这题和2812校园网络是一样的。

楼上用的是Kosaraju，那我就来个Tarjan吧。

首先对图缩点，再分别统计缩点后的图中入度和出度为0的点数。对于任务A，我们只需要输出入度为0的点数——因为我们从这些点开始走就能走遍整个图，即满足任务A。对于任务B，如果出度为0的点更多，我们只要把所有出度为0的点连到入度为0的点上即可。如果入度为0的点更多，那么就要把一些多出来的入度为0的点连进图——即输出max(入度为0的点数,出度为0的点数)。需要注意的是当整个图缩为一个点的情况。此时不用额外连边。

'''cpp



```cpp
#include<cstdio>
#include<stack>
#include<algorithm>
#include<vector>
using namespace std;
int n,m,lowlink[101],pre[101],sccno[101],dep,scc,in[101],out[101],inc,outc;
stack<int> s;
vector<int> g[101];
void dfs(int u){
    pre[u]=lowlink[u]=++dep;
    s.push(u);
    for(int i=0;i<g[u].size();++i){
        int v=g[u][i];
        if(!pre[v]){
            dfs(v);
            lowlink[u]=min(lowlink[u],lowlink[v]);
        }
        else if(!sccno[v])lowlink[u]=min(lowlink[u],pre[v]);
    }
    if(lowlink[u]==pre[u]){
        ++scc;
        while(1){
            int x=s.top();s.pop();
            sccno[x]=scc;
            if(x==u)break;
        }
    }
}
int main(){
    int i,j;
    scanf("%d",&n);
    for(i=1;i<=n;++i)
        for(scanf("%d",&j);j;scanf("%d",&j))
            g[i].push_back(j);
    for(i=1;i<=n;++i)   if(!pre[i]) dfs(i);
    for(i=1;i<=n;++i)
        for(j=0;j<g[i].size();++j){
            int v=g[i][j];
            if(sccno[i]!=sccno[v]){
                ++in[sccno[v]];
                ++out[sccno[i]];
            }
        }
    for(i=1;i<=scc;++i){
        inc+=in[i]==0?1:0;
        outc+=out[i]==0?1:0;
    }
    if(scc==1)  puts("1\n0");
    else printf("%d\n%d\n",inc,max(inc,outc));
    return 0;
} 
'''
```

---

## 作者：eternal (赞：2)

这是一道收缩强连通分量的题。


该题描述的是一个有向图。我们都知道，在一个有向图强连通分量中从任意一个顶点开始，可以到达强连通分量的每个顶点。由此可以把该题中所有强连通分量收缩成分别一个顶点，则入度为0的顶点就是最少要接受新软件副本的学校。


第二问就是，问至少添加多少条边，才能使原图强连通。也就问在收缩后的图至少添加多少条边，才能使之强连通。


可以知道，当存在一个顶点入度为0或者出度为0的时候，该图一定不是强连通的。为了使添加的边最少，则应该把入度为0顶点和出度为0的顶点每个顶点添加1条边，使图中不存在入度为0顶点和出度为0的顶点。


当入度为0的顶点多于出度为0的顶点，则应添加的边数应为入度为0的顶点的个数。当出度为0的顶点多于出入度为0的顶点，则应添加的边数应为出度为0的顶点的个数。


这样就可以解决问题了。但是不要忘了还有特殊的情况，当原图本身就是强连通分量时，收缩成一个顶点，该顶点入度和出度都为0，但第一问应为1，第二问应为0。


求强连通分量，我用的两遍深搜的Kosaraju算法，时间复杂度为O(n)。把找到的每个强连通分量收缩为一的顶点，组成新图。设r(x)为x所在的强连同分量的代表节点，如果原图中存在边e(x,y)，那么新图中有边e(r(x),r(y)) 。然后根据点的邻接关系统计出度和入度即可。







```cpp
#include <bits/stdc++.h>
#define MAXN 101
#define max(x,y) ((x)>(y)?x:y)
using namespace std;
int N,M;
int adjl[MAXN][MAXN],fdjl[MAXN][MAXN];
bool vis[MAXN],dis[MAXN][MAXN];
int belong[MAXN],ind[MAXN],oud[MAXN],i0,o0;
void init()
{
    int t,i;
    cin >> N;
    for (i=1;i<=N;i++)
    {
        cin >> t;
        while (t)
        {
            adjl[i][ ++adjl[i][0] ]=t;
            fdjl[t][ ++fdjl[t][0] ]=i;
            cin >> t;
        }
    }
}
void dfs(int i)
{
    int j,k;
    vis[i]=true;
    for (k=1;k<=adjl[i][0];k++)
    {
        j=adjl[i][k];
        if (!vis[j])
            dfs(j);
    }
}
void fdfs(int i)
{
    int j,k;
    belong[i]=M;
    for (k=1;k<=fdjl[i][0];k++)
    {
        j=fdjl[i][k];
        if (vis[j] && !belong[j])
            fdfs(j);
    }
}
void solve()
{
    int i,j,k;
    for (i=1;i<=N;i++)
    {
        if (!belong[i])
        {
            dfs(i);
            M++;
            fdfs(i);
            memset(vis,0,sizeof(vis));
        }
    }
    for (i=1;i<=N;i++)
    {
        for (k=1;k<=adjl[i][0];k++)
        {
            j=adjl[i][k];
            dis[belong[i]][belong[j]]=true;
        }
    }
    for (i=1;i<=M;i++)
    {
        for (j=1;j<=M;j++)
        {
            if (i!=j && dis[i][j])
            {
                oud[i]++;
                ind[j]++;
            }
        }
    }
    for (i=1;i<=M;i++)
    {
        if (ind[i]==0)
            i0++;
        if (oud[i]==0)
            o0++;
    }
}
void print()
{
    if (M==1)
        cout << 1 << endl << 0 << endl;
    else
    {
        cout << i0 << endl;
        cout << max(i0,o0) << endl;
    }
}
int main()
{
    init();
    solve();
    print();
    return 0;
}
```

---

## 作者：山蛙or山兔 (赞：1)

首先进行缩点，缩点之后是有向无环图G：

子任务A：

易证：就是选择G中无入度的所有点，类似拓扑排序。

子任务B：

设G中入度为0的点有n个，出度为0的点有m个，假设n<m;

则可知（n+m）的点集中有至少n条不形成环的有向边，由此，可证至多再加m条边，使得（n+m）的点集形成一个环。（每次从一个有向边的末尾连到另一个有向边的开头就行，同时保证每个点出度和入度都为1）

又因为这至少n条有向边共享n个点，所以无法使得形成环所需边减少，所以可证至少要再加m条。

同理，n>m也是一样的，所以答案就是max(n,m);

代码如下：
```cpp
#include <iostream>
#include <cstring>
#include <stack>
#include <vector>
#define maxn 110

using namespace std;

int n,m,pre[maxn],low[maxn],bcc[maxn],dfs_clock,bcc_cnt;
vector<int> brr[maxn];
int ans1,ans2,out[maxn],in[maxn];
stack<int> S;

struct edge
{
	int u,v,next,last;
}arr[maxn*maxn];

int front[maxn],sz=0;

void add(int a,int b)
{
	arr[++sz].u=a;
	arr[sz].v=b;
	arr[sz].next=front[a];
	front[a]=sz;
}

void dfs(int u) // pre不变，low为能到达的最之前的编号 
{
	low[u]=pre[u]=++dfs_clock;
	S.push(u);
	for (int i=front[u];i!=-1;i=arr[i].next)
	{
		int v=arr[i].v;
		if (!pre[v])
		{
			dfs(v);
			low[u]=min(low[u],low[v]);
		} 
		else if (bcc[v]==-1)
		{
			low[u]=min(low[u],pre[v]);	
		}
	}
	if (pre[u]==low[u])
	{
		++bcc_cnt;
		int x;
		do
		{
			x=S.top();S.pop();
			bcc[x]=bcc_cnt;
		} while (x!=u);
	}
}

int main()
{
	cin >> n;
	memset(front,-1,sizeof(front));
	memset(bcc,-1,sizeof(bcc));
	memset(pre,0,sizeof(pre));
	for (int i=1;i<=n;i++)
	{
		int x;
		while (cin >> x,x)
		{
			brr[i].push_back(x);
			add(i,x);
		}
	}
	ans1=ans2=dfs_clock=bcc_cnt=0;
	for (int i=1;i<=n;i++) if (!pre[i]) dfs(i);
	memset(out,0,sizeof(out));
	memset(in,0,sizeof(in));
	for (int i=1;i<=n;i++)
	{
		for (int j=0;j<brr[i].size();j++)
		{
			int u=bcc[i],v=bcc[brr[i][j]];
			if (u!=v) // 重边不影响答案 
			{
				out[u]++;
				in[v]++;
			}
		}
	} 
	
	for (int i=1;i<=bcc_cnt;i++)
	{
		if (in[i]==0) ans1++;
		if (out[i]==0) ans2++;
	}
	cout << ans1 << endl;
	if (bcc_cnt==1) cout << 0 << endl;
	else cout << max(ans1,ans2) << endl;
}

```


---

## 作者：黄汝鹏 (赞：1)

对于这道题，最好的方法是

# 缩点+出入度统计

### 仅此而已！！！

下面开始我们的解题之路：这道题的意思是给你n种关系，对于子问题A，就是一给简单的缩点在进行入度统计，这个相信大家没有什么难度，算法实现：

### Tarjan缩点+入度统计

对于子问题B，首先我们可以画图来想一下，假设入度为0的点有a个，出度为0的点有b个，我们可以先将其一一配对，若相等，则所用边数为a(b)，若a>b，则先将b个a点与之配对，用了B条边，则还剩(a-b)个点，这些点又随便找些点瞎乱连，也用了(a-b)条边，∴总共用了(a-b+b)==a条边，同理可证若b>a用b条边——

### ∴可以总结出，取**max(a,b)**

∴算法实现，在统计入度时一并把出度统计，在遍历一遍计数出入度，愉快输出

下面实战(上代码) 
```cpp
#include<iostream>
#include<cstdio>
#include<bits/stdc++.h>
using namespace std;
int n,m,u,v,w,num,cnt,top,col;
int h[1000+10][5],in[1000+10];
int co[1000+10],low[1000+10],st[1000+10],out[1000+10];
int d[1000+10],head[1000+10],dfn[1000+10],de[1000+10];
struct node{
	int from,to,next;
}e[10000+10];
void add(int from,int to)
{
	num++;
	e[num].to=to;
	e[num].from=from;
	e[num].next=head[from];
	head[from]=num;
}
void Tarjan(int u)//缩点模板
{
	dfn[u]=low[u]=++cnt;
	st[++top]=u;
	for(int i=head[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(!dfn[v])
		{
			Tarjan(v);
		    low[u]=min(low[u],low[v]);
		}
		else if(!co[v])
		         low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u])
	{
		co[u]=++col;
		while(st[top]!=u)
		{
			co[st[top]]=col;
			--top;
		}
		--top;
	}
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>u;
		while(u!=0)
		{
			add(i,u);
			cin>>u;
		}
	}
	for(int i=1;i<=n;i++) if(!dfn[i]) Tarjan(i);
	for(int i=1;i<=n;i++)
	    for(int j=head[i];j;j=e[j].next)
	    if(co[i]!=co[e[j].to])
	    {
	    	in[co[e[j].to]]++;//同进出入度
	    	out[co[i]]++;
	    }
	int ans=0,ans2=0;
	for(int i=1;i<=col;i++)
	{
		if(in[i]==0) ans++;
		if(out[i]==0) ans2++; //计数
	}
	if(col==1) cout<<1<<endl<<0;
	else cout<<ans<<endl<<max(ans,ans2)<<endl;//愉快输出
	return 0;
} 
```

望管理大大通过

今天是九九重阳，在这我祝愿天下老人每天开心，身体健康

---

## 作者：George1123 (赞：1)

[${\color{orange}\text{欢迎拜访我这个蒟蒻的博客}}$](https://www.luogu.org/blog/wzc-wwwwd/)

[P2746 【\[USACO5.3\]校园网Network of Schools】](https://www.luogu.org/problem/P2746)

### 此题算法:tarjan缩点

    题目描述很难懂，就是第i+1行输入与第i个点有单向边的点，以0结尾。问:1.至少标记几个节点才能使每个节点都能被有标记的节点走到;2.至少加几条有向边才能使整个图强连通。

大致思路:

>1.$ $输入边并用邻接表存。

>2.$ $tarjan缩点。

>※$ $特判:若所有点强连通

>3.$ $输出$0$入度的强连通分量数

![](https://s2.ax1x.com/2019/10/03/u0QIiR.jpg)

>4.$ $输出$0$入度和出度的强连通分量数的最大值

![](https://s2.ax1x.com/2019/10/03/u0l3mF.jpg)


## 以下是代码+注释

```cpp
/*
   o---o
o-/-----\-o
  (__^u^)  ---
  \  \/o/     \
  /  /o \     It's truly nice.
 /__/\o__\    The problem is to hard to a juruo 
   |/ |/      which named Wendigo!
*/
#include <bits/stdc++.h>
using namespace std;
const int N=110;
struct edge{
	int adj,nex;
}e[N*N];
int n,a,ans1,ans2;
int top,g[N];
void add(int x,int y){
	e[++top]=(edge){
		y,g[x]
	}; g[x]=top; //邻接表存边
} int cnt,ind,dfn[N],low[N];
int col[N],rud[N],cud[N];
bool in[N];
stack<int> st;
void tarjan(int x){ //tarjan缩点
	dfn[x]=low[x]=++ind;
	in[x]=1; st.push(x);
	for(int i=g[x];i;i=e[i].nex){
		int to=e[i].adj;
		if(!dfn[to]){
			tarjan(to);
			low[x]=min(low[x],low[to]);
		}  else if(in[to])
			low[x]=min(low[x],dfn[to]);
	} if(dfn[x]==low[x]){
		cnt++; int tmp=0;
		while(tmp!=x){
			tmp=st.top(); st.pop();
			col[tmp]=cnt;
			in[tmp]=0;
		}
	}
} int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a);
		while(a!=0){
			add(i,a);
			scanf("%d",&a);
		}
	} for(int i=1;i<=n;i++)
		if(!dfn[i])
			tarjan(i);
	if(cnt==1){ //特判
		printf("1\n0\n");
		return 0;
	} for(int i=1;i<=n;i++)
		for(int j=g[i];j;j=e[j].nex){
			int to=e[j].adj;
			if(col[i]!=col[to])
				rud[col[to]]++;
			cud[col[i]]++;
		}
	for(int i=1;i<=cnt;i++){
		ans1+=(!rud[i]);
		ans2+=(!cud[i]);
	} printf("%d\n",ans1);
	printf("%d\n",max(ans1,ans2)); //输出答案
	return 0;
}
```

看完后可以想想为什么要特判。

谢谢大家! !


---

## 作者：Paranoid丶离殇 (赞：1)

## **题目描述**

一些学校连入一个电脑网络。那些学校已订立了协议：每个学校都会给其它的一些学校分发软件（称作“接受学校”）。注意即使 B 在 A 学校的分发列表中， A 也不一定在 B 学校的列表中。

你要写一个程序计算，根据协议，为了让网络中所有的学校都用上新软件，必须接受新软件副本的最少学校数目（子任务   A）。更进一步，我们想要确定通过给任意一个学校发送新软件，这个软件就会分发到网络中的所有学校。为了完成这个任务，我们可能必须扩展接收学校列表，使其加入新成员。计算最少需要增加几个扩展，使得不论我们给哪个学校发送新软件，它都会到达其余所有的学校（子任务  B）。一个扩展就是在一个学校的接收学校列表中引入一个新成员。

**输入格式：**

输入文件的第一行包括一个整数 N：网络中的学校数目（2 <= N <= 100）。学校用前 N 个正整数标识。

接下来 N 行中每行都表示一个接收学校列表（分发列表）。第 i+1 行包括学校 i 的接收学校的标识符。每个列表用 0 结束。空列表只用一个 0 表示。

 **输出格式：**

你的程序应该在输出文件中输出两行。

第一行应该包括一个正整数：子任务 A 的解。

第二行应该包括子任务 B 的解。

**输入样例：**

```
5
2 4 3 0
4 5 0
0
0
1 0
```

**输出样例：**

```
1
2
```

## **说明**

题目翻译来自NOCOW。

USACO Training Section 5.3

**题解：**

**缩点后入度为0的点不可被提供软件；**

**则 任务A 即为 求缩点后入度为0的个数；**

**则入度为0的点必须要被提供新的软件；**

**但出度若 > 0， 则可形成新的入度为0的点；**

**则 任务B 即为 求入度为0的点数与出度为0的点的较大值；**

 

```cpp
#include <iostream>
#include <cstdio>
#include <stack>
using namespace std;
const int N = 1e2 + 5;
int n, ru[N], chu[N];
struct edge { int to, nxt; } e[10000];
int c, head[N];
void add(int from, int to) {
    e[++ c].to = to;
    e[c].nxt = head[from];
    head[from] = c;
}
stack <int> s;
int dfn[N], low[N], tot, scc, tar[N];
void tarjan(int x) {
    dfn[x] = low[x] = ++ tot;
    s.push(x);
    for(int i = head[x]; i ;i = e[i].nxt) {
        int to = e[i].to;
        if(! dfn[to]) {
            tarjan(to);
            low[x] = min(low[x], low[to]);
        }
        else if(! tar[to])
            low[x] = min(low[x], dfn[to]);
    }
    if(dfn[x] == low[x]) {
        scc ++;
        while(1) {
            int y = s.top(); s.pop();
            tar[y] = scc;
            if(y == x) break;
        };
    }
}
int main() {
    cin >> n;
    for(int i = 1, x;i <= n;i ++) {
        cin >> x;
        while( x ) add(i, x), cin >> x;
    }
    for(int i = 1;i <= n;i ++) if(! low[i]) tarjan(i);
    for(int x = 1;x <= n;x ++) {
        for(int i = head[x]; i ;i = e[i].nxt) {
            int y = e[i].to;
            if(tar[x] == tar[y]) continue;
            ru[tar[y]] ++, chu[tar[x]] ++;
        }
    }
    int inc = 0, outc = 0;
    for(int i = 1;i <= scc;i ++) {
        inc += ru[i] == 0 ? 1 : 0;
        outc += chu[i] == 0 ? 1 : 0;
    }
    if(scc == 1) cout << "1\n0" << endl;
    else cout << inc << endl << max(inc, outc) << endl;
    return 0;
}
```



---

## 作者：Christopher_Yan (赞：1)

安利博客：[点击这里食用效果更佳](http://39.106.169.220/?p=274)

#### 解题思路
一眼Tarjan缩点：

第一问就过于水了，缩完点后，输出入度为0的点的个数即可。

第二问略微麻烦，考虑出度为零的点是一定不合法的，想让它合法，最有效率的一种方法就是让他连到一个入度为零的点上，而且如果有选择的余地的话，尽量让他连到一个走不到它的入度为0的点上，如果都能走到它那随便连也没问题。
当然入度为零的点多于出度为零的点的话也是不合法的，那就找一个出度为零（可以重复）的点连过去就好了。

设入度为零的点有$cnt1$个，出度为零的有$cnt2$个。

则答案为：$max(cnt1, cnt2)$

#### AC代码
```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cctype>
#include <cmath>

using namespace std;

const int N = 1020;

int n, ec = -1, a, b, id = 0, top, cur, ans = 0, color = 0, cnt;
int siz[N], dfn[N], f[N], low[N], stk[N], in[N], vis[N], col[N], out[N];

struct Edge
{
	int u, v, nxt;
}e[N << 2];

inline void Addedge(int a, int b)
{
	++ec;
	e[ec].u = a;
	e[ec].v = b;
	e[ec].nxt = f[a];
	f[a] = ec;
}

inline void read(int &x)
{
	int k = 1; x = 0;
	char c = getchar();
	while (!isdigit(c)) 
		if (c == '-') c = getchar(), k = -1;
		else c = getchar();
	while (isdigit(c))
		x = (x << 1) + (x << 3) + (c ^ 48),
		c = getchar();
	x *= k;
}

void Tarjan(int u)
{
	dfn[u] = low[u] = ++id;
	stk[++top] = u, vis[u] = 1;
	for (int i = f[u]; i != -1; i = e[i].nxt)
		if (!dfn[e[i].v])
			Tarjan(e[i].v), low[u] = min(low[u], low[e[i].v]);
		else if (vis[e[i].v])
			low[u] = min(low[u], dfn[e[i].v]);
	if (dfn[u] == low[u])
	{
		++color;
		do
		{
			cur = stk[top--];
			vis[cur] = 0;
			++siz[color];
			col[cur] = color;
		}while (cur != u);
	}
}

signed main()
{
	read(n);
	memset(f, -1, sizeof(f));
	for (int i = 1; i <= n; ++i)
		while (true)
		{
			read(b);
			if (!b) break;
			Addedge(i, b);
		}
	for (int i = 1; i <= n; ++i)
		if (!dfn[i]) 
			Tarjan(i);
	for (int i = 0; i <= ec; ++i)
		if (col[e[i].u] != col[e[i].v])
			++in[col[e[i].v]], ++out[col[e[i].u]];
	for (int i = 1; i <= color; ++i)
	{
		if (!in[i]) ++ans;
		if (!out[i]) ++cnt;
	}
	printf("%d\n%d", ans, color == 1 ? 0 : max(cnt, ans));
	return 0;
}
```

---

## 作者：Celebrate (赞：1)

这一道题就用强连通算法来做，没学的赶紧去学一下，我是在caioj.cn1148学的

第一问:

缩点以后入度为0的点的个数（不是连通分量的数量），入度不为0的点可以通过别的点

第二问：

缩点后入度为0的点和不为0的点的最大值(把这些点连成一个环肯定是最小的，看怎么连环）

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
    int x,y,next;
}a[11000];int len,last[110];//最短路的边 
int tp,sta[110];bool v[110];//sta表示栈，v表示点i是否在栈里面 
int id,cnt,belong[110],dfn[110],low[110];//belong表示点i的属于强连通分量的离散编号，dfn表示这个点什么时候被找到是的（这个点的编号），low表示这个集合中老大的编号 
int into[110],out[110];
inline void ins(int x,int y)//建边就不说了 
{
    len++;
    a[len].x=x;a[len].y=y;
    a[len].next=last[x];last[x]=len;
}
void dfs(int x)//强连通 
{
    tp++;sta[tp]=x;//先放进栈里面 
    dfn[x]=low[x]=++id;v[x]=true;//首先自己当老大 
    for(int k=last[x];k;k=a[k].next)//访问亲朋好友 
    {
        int y=a[k].y;
        if(dfn[y]==0)//如果这个点没有被找过 
        {
            dfs(y);//找一次那个点 
            low[x]=min(low[x],low[y]);//用它的编号来更新自己的编号 
        }
        else
        {
            if(v[y]==true) low[x]=min(low[x],dfn[y]);//如果是在栈里面就直接更新，不在栈里面说明以前已经被找过了 
        }
    }
    if(low[x]==dfn[x])//如果自己是这个强连通分量的老大 
    {
        int i;cnt++;//增加一个分量 
        do
        {
            i=sta[tp--];//弹出栈 
            v[i]=false;//不在栈里面 
            belong[i]=cnt;//记录一下 
        }while(i!=x);//只有把自己和自己上面的弹掉就可以了 
    }
}
int main()
{
    int n,m;scanf("%d",&n);
    for(int x=1;x<=n;x++)//初始化即输入 
    {
        int y;
        while(scanf("%d",&y)!=EOF)
        {
        	if(y==0) break;
        	ins(x,y);
        }
    }
    memset(v,false,sizeof(v));
    for(int i=1;i<=n;i++)//找一次所有的点 
    {
    	//tp=0;这一句不用是因为在do里面栈会自己tp--，所以不用写 
        if(dfn[i]==0)//如果没有找过 
            dfs(i);
    }
    if(cnt==1)//如果只有一个集合就要特判一次 
    {
    	printf("1\n0\n");
    	return 0;
    }
    for(int i=1;i<=len;i++)//枚举所有的边 
    {
    	int tx=belong[a[i].x],ty=belong[a[i].y];
    	if(tx!=ty)//如果两点不属于同一个分量 
    	{
    		into[ty]++;out[tx]++;
    	}
    }
    int ans1,ans2;ans1=ans2=0;
    for(int i=1;i<=cnt;i++)
    {
    	if(into[i]==0) ans1++;//计算入度和出度为0的点的个数 
    	if(out[i]==0) ans2++;
    }
    printf("%d\n%d\n",ans1,max(ans1,ans2));//输出 
    return 0;
}
```

---

## 作者：CrayonDing (赞：1)

Tarjan缩点 对缩点后新图扫每个强连通块的入度出度

对于子任务A 求需要给多少个学校发软件 即为求有多少个入度为0的点 因为对于对于每个入度不为0的点一定可以从一个其他点走到

对于子任务B 求入度为0的点个数与出度为0的点个数的最大值 需要添多少条边才能形成使所有点都可以被某个点到达 所以对于每个出度为0的点 需要拓展一条出边 对于每个入度为0的点 需要拓展一条入边 为了减少拓展边数 可以将所有出度为0的点拓展出边到某个入度为0的点的上 最后答案即为 max（入度为0点数，出度为0点数）

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<stack>
#include<algorithm>
using namespace std;
const int maxn = 105;
int T,dfn[maxn],low[maxn],id[maxn],scc,vis[maxn];
int head[maxn],num_edge,n;
int rd[maxn],cd[maxn];
struct node{
    int next;
    int to;
}edge[maxn*maxn];
stack<int> st;

void add_edge(int from,int to){
    num_edge++;
    edge[num_edge].next=head[from];
    edge[num_edge].to=to;
    head[from]=num_edge;
}

void tarjan(int s){
    dfn[s]=low[s]=++T;
    vis[s]=true;
    st.push(s);
    for(int i=head[s];i!=0;i=edge[i].next){
        int to=edge[i].to;
        if(!dfn[to]){
            tarjan(to);
            low[s]=min(low[s],low[to]);
        }else if(vis[to]){
            low[s]=min(low[s],dfn[to]);
        }
    }
    if(low[s]==dfn[s]){
        scc++;
        int u;
        do{
            u=st.top();
            vis[u]=false;
            st.pop();
            id[u]=scc;
        }while(u!=s);
    }
    return;
}

int main(){
    cin>>n;
    int a;
    for(int i=1;i<=n;i++){
        for(;;){
            cin>>a;
            if(a==0)break;
            add_edge(i,a);
        }
    }//读图 
    
    for(int i=1;i<=n;i++){
        if(!dfn[i])tarjan(i);
    }//tarjan缩点
    
    memset(vis,false,sizeof vis);
    
    for(int i=1;i<=n;i++){
        for(int k=head[i];k!=0;k=edge[k].next){
            if(id[i]!=id[edge[k].to]){
                vis[id[i]]=true;
                cd[id[i]]++;
                rd[id[edge[k].to]]++;
            }
        }
    }
    int ans1=0;
    int ans2=0;
    for(int i=1;i<=scc;i++){
        if(rd[i]==0)ans1++;
        if(cd[i]==0)ans2++;
    }
    cout<<ans1<<endl;
    if(scc==1)cout<<0<<endl;
    else cout<<max(ans1,ans2)<<endl;
    
} 
```

---

## 作者：gyh20 (赞：1)

## tarjan缩点然后数联通块。

先把所有无论怎么传递都能互相到达的学校缩成一个点。最后就会将点数减少。

对于子任务A：我们考虑，如果一个联通块的入度不为0，那么它一定可以由其它联通块分发到达。所以只用分发给入度为0的联通块，即子任务A的解为缩点后入度为0的联通块个数。

对于子任务B：我们考虑，因为是对任意点分发所以不能存在任何入度或出度为0的联通块（从其他点开始无法达到入度为0得点，从出度为0的点出发无法到达其它点)。一条从A到B的边会给A增加一个出度，为B增加一个入度。即每增加一条边就会增加一个出度和入度。所以我们只需要求入度为0和出度为0的点的最大值。

代码如下：
```c
#pragma GCC optimize(200000)
#include<iostream>
#include<cstdio>
#include<stack>
#include<cstring>
#include<algorithm>
using namespace std;
stack <int> s;
struct edge {
	int next,to;
} e[10005];
int head[10005],a[10005],b[10005],bl[10005],rd[10005],c,cd[10005],d,f,g,h[102][102],n,cnt,num,dfn[10005],low[10005],m,m1,m2;
bool vis[10005];
void bu(int x,int y) {
	e[++cnt].next=head[x];
	e[cnt].to=y;
	head[x]=cnt;
}
void tj(int u) {

	vis[u]=1;
	dfn[u]=low[u]=++num;
	s.push(u);
	for(int i=head[u]; i; i=e[i].next) {
		if(!dfn[e[i].to]) {
			tj(e[i].to);
			if(low[e[i].to]<low[u])low[u]=low[e[i].to];
		} else if(vis[e[i].to]) {
			if(dfn[e[i].to]<low[u])low[u]=dfn[e[i].to];
		}
	}
	if(dfn[u]==low[u]) {
		++n;
		int v,p=0;
		m1=0x7fffffff;
		do {
			v=s.top();
			s.pop();
			bl[v]=n;
			vis[v]=0;
		} while(u!=v);
	}
}

int main() {
	scanf("%d",&c);
	for(int i=1; i<=c; i++) {
		while(scanf("%d",&f)) {
			if(f==0)break;
			bu(i,f);
		}
	}
	for(int i=1; i<=c; i++) {
		if(!dfn[i])tj(i);
	}
	for(int i=1; i<=c; i++) {
		for(int j=head[i]; j; j=e[j].next) {
			if(bl[i]!=bl[e[j].to]) {
				h[bl[i]][bl[e[j].to]]=1;
				rd[bl[e[j].to]]++;
				cd[bl[i]]++;
			}
		}
	}
	if(n==1){
		cout<<1<<endl<<0;
		return 0;
	}
	for(int i=1; i<=n;i++){
		if(rd[i]==0)f++;
		if(cd[i]==0)g++;
	}cout<<f<<endl<<max(f,g);
                                                
	}
```


---

## 作者：灰白骨 (赞：1)

```cpp
#include <bits/stdc++.h>
using namespace std;
int ditu[101][101],ditu2[101][101];
//ditu为输入的图,ditu2为缩完点后的图 
int low[101],dnf[101];//dnf为次序编号(在DFS中该节点被搜索的次序)
//low为祖宗 (为i或i的子树能够追溯到的最早的栈中节点的次序号)
//当DFN[i]==LOW[i]时，为i或i的子树可以构成一个强连通分量。
int team[101];//所有点属于哪个组 
int stindex=0,tmindex=0;//索引号(在所有点中的序号)//tm为强连通的总数量 
int n;
stack<int>st;
int indegree[101];//保存每个节点的入度
int outdegree[101];//保存每个节点的出度
int tarjan(int f)
{
    stindex++;//序号++ 
    low[f] = stindex;
    dnf[f] = stindex;
    st.push(f);//放入第f个点 
    int i,x;
    for(i=1;i<=n;i++)
    {
        if(ditu[f][i]==0) continue;//一但不连通就跳过 
        if(dnf[i]==0)//一但还没有jarjan过 
        {
            tarjan(i);
            low[f] = min(low[f],low[i]);//----------- 
        }else
        {
            if(team[i]==0)//一但还没有所属组 
            {
                low[f] = min(low[f],dnf[i]);// ------------- 
            }			
        }
    }
    if(low[f]==dnf[f])//一但可以构成一个强连通分量
    {
        tmindex++;//强连通分量个数++ (组数++)
        while(1)
        {
            x = st.top();//去除 
            st.pop();//删除 
            team[x] = tmindex;//更改x点的所属组; 
            if(x==f)//一但取到最后一个 
            {
                break;
            }
        }
    }
}
int dotarjan()//调用 
{
    int i;
    for(i=1;i<=n;i++)
    {
        if(dnf[i]==0)//一但还没有分组 
        {
            tarjan(i);
        }
    }
}
//所有都是从I到J而不是从J到I; 
int main()
{
    cin>>n;
    int i,j,x,l,k;
    for(i=1;i<=n;i++)
    {
        while(1) 
        {
            scanf("%d",&x);
            if(x==0) 
            {
                break;
            }
            ditu[i][x] =1;//i到x右一条路; 
        }
    }
    //以上输入; 
    dotarjan();//调用 
    if(tmindex==1)//一但全部为一体 
    {
        printf("1\n0");
        return 0;
    }
    for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			if(ditu[i][j]==0)continue;//一但没有路就continue; 
			if(team[i]==team[j])continue;//一但属于同一组就continue; 
			if(ditu2[team[i]][team[j]]==0)//一但还没有赋值 
			{
				ditu2[team[i]][team[j]] = 1;//把缩完点后的图赋值给ditu2; 
				indegree[team[j]]++;//属于第j组的点的入度++； 
				outdegree[team[i]]++;//属于第i组的点的入度++； 
			}
		}
	} 
	int icount=0,ocount=0;
	for(i=1;i<=tmindex;i++)
	{
		if(indegree[i]==0) icount++;//如果是根节点(入度为0)，入度的计次++； 
		if(outdegree[i]==0) ocount++;//如果出度为0，出度的计次++； 
	}
    printf("%d\n%d",icount,max(icount,ocount));//输出入度的计次与  入度和出度的最大值； 
    return 0;
} 
```

---

## 作者：fnoi15azhengbm (赞：0)

一道tarjan题目,首先看到题目不难想到使用这个方法（蒟蒻在此不多说明），缩点后计算入度为零的点的个数，和出度为零的点的个数。第一问所求就是入度为零的点的个数（入度为零即为必须传递的点），第二问就是求入度出度为零的点的最值（没有入初度为零的点即为强联通）。在其中注意特判只有一个点的情况。
以下是蒟蒻的代码，仅供参考
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1100;
struct node{
	int x,y,next;
};
node data[N*N];
int x,op,low[N],sta[N],dfn[N],cnt,poi[N],h[N],ans,a[N],n,num,ru[N],ch[N],ru1,ch1;
bool fl[N],fl1[N],fl2[N][N];
void dfs1(int x){
	low[x]=dfn[x]=++cnt;
	fl[x]=1;
	op++;
	sta[op]=x;
	fl1[x]=0;
	for(int j=h[x];j!=-1;j=data[j].next){
		int yy=data[j].y;
		if(!fl[yy]){
			dfs1(yy);
			low[x]=min(low[yy],low[x]);
		}else{
			if(!fl1[yy]){
				low[x]=min(low[x],dfn[yy]);
			}
		}
	}
	if(dfn[x]==low[x]){
		++ans;
		int yy;
		do{
			yy=sta[op];
			fl1[yy]=1;
			a[yy]=ans;
			op--;
		}while(x!=yy);
	}
}
int main(){
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	scanf("%d",&n);
	memset(h,-1,sizeof h);
	memset(fl,false,sizeof fl);
	memset(fl1,true,sizeof fl1);
	for(int i=1;i<=n;++i){
		while(1){
			scanf("%d",&x);
			if(x==0)break;
			data[++num].x=i;
			data[num].y=x;
			data[num].next=h[i];
			h[i]=num;
		}
	}
	for(int i=1;i<=n;++i){
		if(!fl[i])dfs1(i);
	}
	if(ans==1){
		printf("1\n0\n");
		return 0;
	}
//	for(int i=1;i<=n;++i){
//		printf("%d:%d\n",i,a[i]);
//	}
	memset(fl2,1,sizeof fl2);
	for(int i=1;i<=n;++i){
		for(int j=h[i];j!=-1;j=data[j].next){
			int yy=data[j].y;
			if(fl2[a[i]][a[yy]] && a[i]!=a[yy]){
				fl2[a[i]][a[yy]]=0;
				ru[a[yy]]++;
				ch[a[i]]++;
			}
		}
	}
	ru1=0;
	ch1=0;
	for(int i=1;i<=ans;++i){
		if(!ru[i])ru1++;
//		printf("%d ",ru[i]);
		if(!ch[i])ch1++;
//		printf("%d ",ch[i]);
	}
	printf("%d\n",ru1);
	printf("%d\n",max(ru1,ch1));
	return 0;
}
```


---

## 作者：寒鸽儿 (赞：0)

考虑缩点。  
对缩点后的图：  
会变成外向树/内向树森林,或者DAG。  
对于入度为0的点需要放一个文件。  
将入度为0和出度为0的点连边为最优的构建强连通图的策略。则第二个子问题的答案为入度为0与出度为0的点数目的最大值。  
注意特判缩点后成为一个点的情况。  
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 123, M = N*N;
int head[N], ver[M], nex[M], my[M], tot;
inline void addedge(int u, int v) {
	ver[tot] = v; nex[tot] = head[u]; my[tot] = u; head[u] = tot++;
}

int dfn[N], low[N], cl[N], sta[N], num[N], ind[N], outd[N], col = 1, dfs_clock = 1, top = 0;
void dfs(int cur) {
	dfn[cur] = low[cur] = dfs_clock++;
	sta[top++] = cur;
	for(int i = head[cur]; ~i; i = nex[i]) {
		if(!dfn[ver[i]]) {
			dfs(ver[i]);
			low[cur] = min(low[cur], low[ver[i]]); 
		} else if(!cl[ver[i]]) {
			low[cur] = min(low[cur], dfn[ver[i]]);
		}
	}
	if(dfn[cur] == low[cur]) {
		--top;
		while(sta[top] != cur) {
			++num[col];
			cl[sta[top]] = col;
			--top;
		}
		cl[cur] = col;
		++num[col];
		++col;
	}
}

int main() {
	memset(head, -1, sizeof(head));
	int n, tmp;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &tmp);
		while(tmp) {
			addedge(i, tmp);
			scanf("%d", &tmp);
		}
	}
	for(int i = 1; i <= n; ++i) if(!dfn[i]) dfs(i);
	for(int i = 0; i < tot; ++i) {
		if(cl[my[i]] != cl[ver[i]]) {
			++ind[cl[ver[i]]]; ++outd[cl[my[i]]];
		}
	}
	if(col == 2) {
		printf("1\n0\n");
		return 0;
	}
	int ans1 = 0, ans2 = 0;
	for(int i = 1; i < col; ++i) {
		if(!ind[i]) ++ans1;
		if(!outd[i]) ++ans2;
	}
	ans2 = max(ans1, ans2);  
	printf("%d\n%d\n", ans1, ans2);
	return 0;
}
```

---

## 作者：ShuYuMo (赞：0)

# 写在前面

`Tarjan`缩点经典问题，证明其他题解已经泛滥了。。。我写一写我自己想法。

# 技巧（KEYS）

 - 任务A：入读为$0$的点的个数
 - 任务B: 求入度为$0$的点数与出度为0的点的个数的最大值值。

> 缩完点之后，可以使用`set`去除重复的边，进行重新建图。`QAQ` 好方便！

# 注意

需要注意缩完点之后，只剩下一个点的情况`QAQ`不判断会`WA`一个点

```cpp
/*!
 * FileName: luogu-2746.cpp
 * This Problem is on luogu. The ID of the problem is 2746. 
 * Copyright(c) 2019 Shu_Yu_Mo
 * MIT Licensed
 * Luogu: https://www.luogu.org/space/show?uid=44615
 * Github: https://github.com/oldsuold/
 * Gitee: https://gitee.com/Shu_Yu_Mo/
 * These words were created by an amazing tool on 2019-08-13 21:37:29 written by Shu_Yu_Mo.
 */
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstring>
#include<iostream>
#include<cmath>
#include<stack>
#include<set>
#include<algorithm>
#define inf 0x7fffffff
using namespace std;
const int _N = 110;
const int _M = _N * _N;
inline int read()
{
    char c = getchar(); int sign = 1; int x = 0;
    while(c > '9' || c < '0') { if(c=='-')sign = -1; c = getchar(); } 
    while(c <= '9' && c >= '0') { x *= 10; x += c - '0'; c = getchar(); }
    return x * sign;
}
int head[_N];
struct edges{
	int node;
	int nxt;
}edge[_M];
int tot = 0;
void add(int u, int v)
{
	edge[++tot].nxt = head[u];
	head[u] = tot;
	edge[tot].node = v;
}
int n;
int dfn[_N];
int low[_N];
int dfnClock = 0;
int scc[_N];
int sccCnt = 0;
stack <int> S;
void tarjan(int now)
{
	low[now] = dfn[now] = ++dfnClock;
	S.push(now);
	for(register int i = head[now];i;i = edge[i].nxt)
	{
		int exNode = edge[i].node;
		if(dfn[exNode] == 0)
		{
			tarjan(exNode);
			low[now] = min(low[now], low[exNode]);
		}
		else if(scc[exNode] == 0)
			low[now] = min(low[now], dfn[exNode]);
	}
	if(low[now] == dfn[now])
	{
		sccCnt ++;
		while(true)
		{
			scc[S.top()] = sccCnt;
			if(S.top() == now)
			{
				S.pop();
				break;
			}
			S.pop();
		}
	}
}
int outd[_N];
int ind[_N];
int main()
{
	n = read();
	for(register int i = 1;i <= n;i++)
	{
		int tmp;
		while(true)
		{
			tmp = read();
			if(tmp == 0) break;
			add(i, tmp);
		}
	}
	for(register int i = 1;i <= n;i++)
		if(dfn[i] == 0)
			tarjan(i);
	set<pair<int,int> > S;
	for(register int i = 1;i <= n;i++)
	{
		for(register int j = head[i];j;j = edge[j].nxt)
		{
			int exNode = edge[j].node;
			if(scc[i] != scc[exNode])
				S.insert(make_pair(scc[i], scc[exNode]));
		}
	}
	
	for(set<pair<int, int > >::iterator i = S.begin();i != S.end();i++)
	{
		outd[(*i).first] ++;
		ind[(*i).second] ++;
	}
	int ans1 = 0;
	int ans2 = 0;
	for(register int i = 1;i <= sccCnt;i++)
	{
		if(ind[i] == 0)
			ans1 ++;
		if(outd[i] == 0)
			ans2 ++;
	}
	printf("%d\n%d\n", ans1, sccCnt == 1 ? 0 : max(ans1, ans2)) ;
    return 0;
}
```

---

## 作者：七里 (赞：0)

## **题目描述**

一些学校连入一个电脑网络。那些学校已订立了协议：每个学校都会给其它的一些学校分发软件（称作“接受学校”）。注意即使 B 在 A 学校的分发列表中， A 也不一定在 B 学校的列表中。

你要写一个程序计算，根据协议，为了让网络中所有的学校都用上新软件，必须接受新软件副本的最少学校数目（子任务 A）。更进一步，我们想要确定通过给任意一个学校发送新软件，这个软件就会分发到网络中的所有学校。为了完成这个任务，我们可能必须扩展接收学校列表，使其加入新成员。计算最少需要增加几个扩展，使得不论我们给哪个学校发送新软件，它都会到达其余所有的学校（子任务 B）。一个扩展就是在一个学校的接收学校列表中引入一个新成员。

## **输入格式**

输入文件的第一行包括一个整数 N：网络中的学校数目（2 <= N <= 100）。学校用前 N 个正整数标识。

接下来 N 行中每行都表示一个接收学校列表（分发列表）。第 i+1 行包括学校 i 的接收学校的标识符。每个列表用 0 结束。空列表只用一个 0 表示。

## **输出格式**

你的程序应该在输出文件中输出两行。

第一行应该包括一个正整数：子任务 A 的解。

第二行应该包括子任务 B 的解。

## **详解**
用Tarjan缩点

强联通分量：在单向边的图中，任意一个点都能到达任意一个点。

任务Ａ就是入度为零的点的个数（如果只有一个强联通分量则直接输出　１　０　）~~无需解释~~

任务Ｂ就是入度为零的点和出度为零的点的最大值

任务Ｂ是要达到添加关系，使得整张图是一个强联通分量（不知道我说的对不对）

因为是缩点之后，对于１个强联通分量不需要多加关系，对于剩余情况：

- 出度为零的点大于入度为零的点

在每一个出度为零的点，都添加关系到入度为零的点

- 入度为零的点大于出度为零的点
在每一个入度为零的点引一个关系来自出度为零的点

## **代码如下：**
```
#include<bits/stdc++.h>
#define regin register int
using namespace std;
int n;
int tot=1,head[120],ver[20000],nex[20000];
inline void add(int a,int b)
{
	ver[++tot]=b;nex[tot]=head[a];head[a]=tot;
}
int in[120],out[120],ma1,ma2;
int cnt,num,top,dfn[120],low[120],ins[120],c[120];
int stac[20000];
void tarjan(int x)
{
	dfn[x]=low[x]=++num;
	ins[x]=1;stac[top++]=x;
	for(regin i=head[x];i;i=nex[i])
	{
		int y=ver[i];
		if(!dfn[ver[i]])
		{
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(ins[y]!=0) low[x]=min(low[x],dfn[y]);
	}
	/*
	if(dfn[x]==low[x])
	{
		cnt++;
		while(x!=stac[top])
		{
			c[stac[top]]=cnt;
			top--;
		}
		top--;
		c[x]=cnt;
	}*/
	if(dfn[x]==low[x])
	{
		cnt++;
		do
		{
			ins[stac[--top]]=0;
			c[stac[top]]=cnt;
		}while(stac[top]!=x);
	}
}
int to,hc[120],ne[20000],ve[20000];
void ad(int a,int b)
{
	ve[++to]=b;ne[b]=hc[a];hc[a]=to;
}
int main ()
{
	scanf("%d",&n);
	for(regin i=1;i<=n;i++)
	{
		int x;
		for(;;)
		{
			scanf("%d",&x);
			if(x==i) continue;
			if(x==0) break;
			add(i,x);
		}
	}
	for(regin i=1;i<=n;i++)
	{
		if(!dfn[i]) tarjan(i);
	}
	for(regin i=1;i<=n;i++)
	{
		for(regin j=head[i];j;j=nex[j])
		{
			if(c[i]==c[ver[j]]) continue;
			else in[c[ver[j]]]++,out[c[i]]++;
		}
	}
	for(regin i=1;i<=cnt;i++)
	{
		if(in[i]==0) ma1++;
		if(out[i]==0) ma2++;
	}
	if(cnt==1) printf("1\n0\n");
	else printf("%d\n%d\n",ma1==0?1:ma1,max(ma1,ma2));
	return 0;
}
```


---

## 作者：Minakami_Yuki (赞：0)

~~`for(register int j = 1; j <= n; i++)`~~

Farmer John太屑了

# 题目链接

[P2746 [USACO5.3]校园网Network of Schools](<https://www.luogu.org/problemnew/show/P2746>)

# 题意简述

给你一张图，~~你得看出来题目让你~~找出**入度为0**的强连通分量的个数以及它与**出度为0**的强连通分量的个数较大者

# 解题思想

先来解读一下为什么要向题意简述那样做：

## 第一问

要想分发给更多的学校，必须从入度为0的点开始分发。

不妨**考虑一个入度不为0的点**：
对于一个**入度不为0**的点，我们总能从**可以抵达它的点**开始分发，这样接收数量显然更优。

## 第二问

要使原图**强连通**，则构造后的图**不存在**入度**与**出度为0的点。我们仅需求出两者中的**数量较大**者，

可以通过**较小者**向其连**较大数量的边**使原图不存在入度与出度为0的点，此时原图强连通。

具体实现就是缩点后统计一下每个节点的**度**就行了。

# 参考代码

```cpp
#include <cstdio>
#include <cctype>

namespace FastIO {
    inline int read() {
        char ch = getchar(); int r = 0, w = 1;
        while(!isdigit(ch)) {if(ch == '-') w = -1; ch = getchar();}
        while(isdigit(ch)) {r = r * 10 + ch - '0'; ch = getchar();}
        return r * w;
    }
    void _write(int x) {
        if(x < 0) putchar('-'), x = -x;
        if(x > 9) _write(x / 10);
        putchar(x % 10 + '0');
    }
    inline void write(int x) {
        _write(x);
        puts("");
    }
}

const int N = 110;
const int M = N * N;

using namespace FastIO;

template <typename T> T max(T a, T b) {return a > b ? a : b;}
template <typename T> T min(T a, T b) {return a < b ? a : b;}

template <typename T>
class stack {
    private:
        int stop;
        T s[N << 1];
    public:
        stack() {stop = 0;}
        inline bool empty() {return !stop;}
        inline void push(T x) {s[++stop] = x;}
        inline void pop() {if(!empty()) stop--;}
        inline T top() {return s[stop];}
};

stack <int> s;

int head[N], ver[M], nxt[M], scc[N], dfn[N], low[N];
int in[N], out[N];
int idx, cnt, ans1, ans2, n, tot;
bool v[N];

inline void add(int x, int y) {
    ver[++cnt] = y, nxt[cnt] = head[x], head[x] = cnt;
}

void tarjan(int x) {
    dfn[x] = low[x] = ++idx;
    v[x] = 1;
    s.push(x);
    for(register int i = head[x]; i; i = nxt[i]) {
        int y = ver[i];
        if(!dfn[y]) {
            tarjan(y);
            low[x] = min(low[x], low[y]);
        }
        else if(v[y]) {
            low[x] = min(low[x], dfn[y]);
        }
    }
    if(dfn[x] == low[x]) {
        tot++;
        while(s.top()) {
            int y = s.top();
            s.pop();
            v[y] = 0;
            scc[y] = tot;
            if(x == y) break;
        }
    }
}

int main() {
    n = read();
    for(register int i = 1; i <= n; i++) {
        int x = read();
        while(x != 0) add(i, x), x = read();
    }
    for(register int i = 1; i <= n; i++) {
        if(!dfn[i]) tarjan(i);
    }
    for(register int i = n; i >= 1; i--) {
        for(register int j = head[i]; j; j = nxt[j]) {
            if(scc[i] != scc[ver[j]]) {
                in[scc[ver[j]]]++;
                out[scc[i]]++;
            }
        }
    }
    for(register int i = 1; i <= tot; i++) {
        if(in[i] == 0) ans1++;
        if(out[i] == 0) ans2++;
    }
    if(tot == 1) {
        puts("1");
        puts("0");
        return 0;
    }
    write(ans1);
    write(max(ans1, ans2));
    return 0;
}
```



---

