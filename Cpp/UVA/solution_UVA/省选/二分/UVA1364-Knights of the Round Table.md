# Knights of the Round Table

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4110

[PDF](https://uva.onlinejudge.org/external/13/p1364.pdf)

# 题解

## 作者：mayike (赞：7)

### [题目传送门](https://www.luogu.com.cn/problem/UVA1364)

### [双倍经验](https://www.luogu.com.cn/problem/SP2878)

------------
## 注意

本题解侧重于证明。

# 题意

**可以是多次会议，优先强调这一点**。每次会议，在 $n$ 个骑士中选出**奇数个**围成一个**圈**，要求相邻二人**非互相憎恨**关系。输入中会给出 $m$ 组互相憎恨关系。

# 思路

做过[此题](https://www.luogu.com.cn/problem/P3452)的朋友很快会发现这题是可以建补图的，换言之起始思路是大同的。那我们就先建个补图：
```cpp
bool A[N][N];
vector<int>e[N];
for(int i=1;i<=m;i++){
			int x,y;
			scanf("%d%d",&x,&y);
			A[x][y]=A[y][x]=1;
		}
		for(int i=1;i<=n;i++)
		    for(int j=i+1;j<=n;j++)
			    if(!A[i][j])e[i].push_back(j),e[j].push_back(i);
```
可以保证的是互相憎恨的人是没有直接连边的。此时形成多个点双。
```cpp
void tarjan(int u,int fa){
	int son=0;
	dfn[u]=low[u]=++num;
	stk[++top]=u;
	for(int v:e[u]){
		if(v==fa)continue;
		if(!dfn[v]){
			son++;
		    tarjan(v,u);
		    low[u]=min_(low[u],low[v]);
		    if(low[v]>=dfn[u]){
		    	f[++sum].push_back(u);
		    	while(stk[top+1]!=v)f[sum].push_back(stk[top--]);
			}
		}else low[u]=min_(low[u],dfn[v]);
	}if(fa==0&&son==0)f[++sum].push_back(u);
}
int main(){
for(int i=1;i<=n;i++)
		    if(!dfn[i])tarjan(i,0);
   return 0;
   }
```
再想一下转换后的图和题意，会发现若有骑士可以参加会议，那就是在多个点双里找一个点双，这个点双里有一个奇数个人围的环，暂且叫奇圈，圈中就有那个骑士。

那么问题就转换到如何在一个点双里找奇圈了。~~手贱的我点开标签，发现是二分图~~

论二分图和奇圈的关系，那是有的。对于任一二分图，一定不存在有奇圈的，为何？那就反证一下。

**证明**：设一个二分图里有奇圈：$v_1,v_2,v_3 \dots v_{2k-1}$，$k$ 为正整数。任意相邻两点有边相连，且 $v_1,v_{2k-1}$ 有一条邻边。设 $v_1$ 属于 $V_x$ 集合，依次类推 $v_2$ 属于 $V_y$，$v_3$ 属于 $V_x$。可知奇数编号属于 $V_x$ 集合，偶数编号属于 $V_y$ 集合。即 $v_{2k-1}$ 属于 $V_x$ 集合，但这不满足二分图。因为 $v_1,v_{2k-1}$ 属于同集合且有边相连。**故反证成立，二分图无奇圈。**

于是乎**一个非二分图的点双是一定有奇圈的。**

**证明**：参考点双性质：任意两点至少存在两条点不重复的路径。那么，这两条路径会形成一个环，整个点双会形成多个环。反证：若都是偶环，即偶圈，那就是一个二分图了。反之，一定是有奇圈的。

**最后一点**，也是**最易**推的一点，就是对于一个非二分图的点双里，每个点都处于一个奇圈里。这点是在题目的**可以是多次会议**的特殊性质下满足的，这样骑士开了会还可以再开，但能参会人数只会增长或不变。

**证明**：考虑最坏情况，只有一个奇圈，周围都是偶圈。但相邻偶圈与奇圈明显是可以组成更大的奇圈的。首先，重合部分可以划到奇圈，是可以满足开会。其次，把重合部分减去，形成一个圈，设原奇圈，原偶圈，重合部分分别有 $a,b,c$ 人，则合并后圈人数为 $a+b-2c$ 为奇数人，恰为一个环，即奇圈。所以按此方式，偶圈和原奇圈里的人都可以参加会议。以此类推，整个点双都可以被合并。故结论成立：**对于一个非二分图的点双里，每个点都处于一个奇圈里。**

所以，只要一个点双不是二分图，那么整个点双的骑士都可以参加**过**会议。**不限会议数真的是此方法的前提。**

那么，就按这个思路敲代码啦：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e3+5;
int n,m,dfn[N],low[N],stk[N],color[N],bb[N],top,num,sum,A[N][N],vis[N];
vector<int>e[N],f[N];
int min_(int x,int y){
	return x>y?y:x;
}
void tarjan(int u,int fa){
	int son=0;
	dfn[u]=low[u]=++num;
	stk[++top]=u;
	for(int v:e[u]){
		if(v==fa)continue;
		if(!dfn[v]){
			son++;
		    tarjan(v,u);
		    low[u]=min_(low[u],low[v]);
		    if(low[v]>=dfn[u]){
		    	f[++sum].push_back(u);
		    	while(stk[top+1]!=v)f[sum].push_back(stk[top--]);
			}
		}else low[u]=min_(low[u],dfn[v]);
	}if(fa==0&&son==0)f[++sum].push_back(u);
}
bool et(int u,int fa){//二分图
	for(int v:e[u]){
		if(bb[v]!=fa)continue;
		if(color[u]==color[v])return 0;
		if(!color[v]){
			color[v]=3-color[u];
			if(!et(v,fa))return 0;
		}
	}return 1;
}
int main(){
	while(~scanf("%d%d",&n,&m)&&n&&m){
		num=sum=top=0;
		memset(A,0,sizeof A);
		memset(dfn,0,sizeof dfn);
		memset(low,0,sizeof low);
		memset(vis,0,sizeof vis);
		memset(bb,0,sizeof bb);//一定去重！！！
		for(int i=1;i<=n;i++)e[i].clear(),f[i].clear();
		for(int i=1;i<=m;i++){
			int x,y;
			scanf("%d%d",&x,&y);
			A[x][y]=A[y][x]=1;
		}
		for(int i=1;i<=n;i++)
		    for(int j=i+1;j<=n;j++)
			    if(!A[i][j])e[i].push_back(j),e[j].push_back(i);
		for(int i=1;i<=n;i++)
		    if(!dfn[i])tarjan(i,0);
		for(int i=1;i<=sum;i++){
			memset(color,0,sizeof color);
			for(int j:f[i])bb[j]=i;//确定团队
			int u=f[i][0];
			color[u]=1;//确立起点与颜色
			if(!et(u,i))
			    for(int j:f[i])vis[j]=1;
		}
		int ans=0;
		for(int i=1;i<=n;i++)ans+=(!vis[i]);
		printf("%d\n",ans);
	}
	return 0; 
}
```

---

## 作者：jdsb (赞：5)

## 题意
有$n$个骑士，要从中选出一些骑士围成一个环，要求环中的骑士数量为奇数且不能只有一个人，再给定$m$对关系$(u,v)$，表示$u$和$v$不能相邻坐，求出不能围成环的骑士人数。

## 分析
1. 用题目给出的憎恨关系构建出图$G$，然后再构造出图$G$的补图，补图中的边$(u,v)$就表示$u$和$v$可以相邻。

2. 接下来用$Tarjan$求出图中的点双联通分量，每个点双联通分量中的点就处在环中。

3. 要判断每个点是否处于奇环中，就要知道下面两条定理:

$\ \ \ $ $(1)$如果一个点双联通分量中存在奇环，那么这个点双联通分量中的点都处在至少一个奇环中。

$\ \ \ $ $(2)$如果一个双连通分量含有奇环，则他必定不是一个二分图。反过来也成立。

$\ \ \ $ 证明$1$：设图中的两个点$u$，$v$在一个奇环中，则一定存在两条路径从$u$到$v$，一条路径上的点数为奇数，另一条路径上的点数为偶数，此时再来一个新点$x$,将它分别连向$u$和$v$，则这时$x$点和原来那条有偶数个点的路径又能构成一个奇环，证毕。

$\ \ \ $ 证明$2$：设二分图中两边的点集为$X$，$Y$，由于二分图的定义，同一点集内没有连边，设我们最初的点在$X$集合内，则这个环如果存在，环上的点必定是$X_1$，$Y_1$，$X_2$，$Y_2$···，所以环上的点为偶数个，不是奇环，所以存在奇环的点双联通分量不是二分图。反之，如果一个点双联通分量里没有二分图，说明这个图里有环而且不是偶环，那么就只可能是奇环，证毕。

4. 要判断一张图是否是二分图，就要用交叉染色法，初始时每个点是是无色，用$-1$表示，然后在$bfs$遍历时染色，当前点$x$为颜色为$0$时，则相邻点$y$为1，否则为$y$的颜色为$0$，如果发现$y$已经被染色且和点$x$的颜色相同，就说明这个图不是二分图。

5. 综合上述分析，我们对原图的补图进行$Tarjan$求点双联通分量，在找到一个点双联通分量后判断这个点双联通分量是否是二分图，如果不是，就将这个联通分量的点打个标记，最后统计没被标记的点就是答案。

## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<cmath>
using namespace std;
int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') f=-1;c=getchar();};
	while(c>='0'&&c<='9')
	{
		x=(x<<3)+(x<<1)+(c^48);
		c=getchar();
	}
	return x*f;
}
const int N=2e3+5,M=2e6+5;
struct edge
{
	int y,next;
}e[M];
int cnt,first[N];
void add(int x,int y)
{
	e[++cnt]={y,first[x]};
	first[x]=cnt;
}
int n,m,a[N][N],col[N],mark[N];
bool check(int s)
{
	memset(col,-1,sizeof(col));
	int tot=0;
	for(int i=1;i<=n;i++) tot+=mark[i];
	if(tot<3) return 1;
	queue<int>q;
	q.push(s);
	col[s]=0;
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=first[x];i;i=e[i].next)
		{
			int y=e[i].y;
			if(!mark[y]) continue;
			if(col[x]==col[y]) return 0;
			if(col[y]==-1)
			{
				col[y]=1-col[x];
				q.push(y);
			}
		}
	}
	return 1;
}
int dfn[N],low[N],tim,st[N],odd[N],top;
void tarjan(int x,int fa)
{
	dfn[x]=low[x]=++tim;
	st[++top]=x;
	for(int i=first[x];i;i=e[i].next)
	{
		int y=e[i].y;
		if(y==fa) continue;
		if(!dfn[y])
		{
			tarjan(y,x);
			low[x]=min(low[x],low[y]);
			if(dfn[x]<=low[y])
			{
				memset(mark,0,sizeof(mark));
				int z;
				do
				{
					z=st[top--];
					mark[z]=1;
				}
				while(z!=y);
				mark[x]=1;
				if(check(x)==0)
					for(int j=1;j<=n;j++)
						if(mark[j])
							odd[j]=1;
			}
		}
		else low[x]=min(low[x],dfn[y]);
	}
}
void init()
{
	cnt=top=tim=0;
	for(int i=1;i<=n;i++) first[i]=odd[i]=low[i]=dfn[i]=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			a[i][j]=0;
}
int main()
{
	while(scanf("%d%d",&n,&m)&&(n+m))
	{
		init();
		for(int i=1;i<=m;i++)
		{
			int x,y;
			x=read(),y=read();
			a[x][y]=a[y][x]=1;
		}
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
				if(!a[i][j])
				{
					add(i,j);
					add(j,i);
				}
		for(int i=1;i<=n;i++)
			if(!dfn[i])
				tarjan(i,0);
		int ans=0;
		for(int i=1;i<=n;i++)
			if(!odd[i])
				ans++;
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：PCCP (赞：2)

# UVA-1364

### 前情提要：

相信很多同学已经看过之前的题解了，也都知道了本题的解法，这里我们来看看为什么要建补图，或者说为什么补图会更简单。

### 正文：
 
题目描述很清楚，给定了一些**互相**仇视的关系，这告诉我们这是一个无向图。

有点同学很快啊，看到互相排斥的关系，就想到连通，想到二分图的最大独立集问题。但是互相仇视的骑士**只是**不能坐在**相邻**的位置，并非一定不能共同出席，他们是可以坐在不相邻的两个位置上的。那么你如果用最大独立集去做，他就会排斥掉不相邻的情况。

所以啊，我们要想到，事物存在对立的这一面，就一定要存在对立的那一面。我们可以建立他的补图，用“连通”去维护“连通”（可以连在一起坐）。这样互相排斥的两个骑士也可以通过间接的连接联系在一起。

随后，用 Tarjan 去求出补图里的 v-DCC，判定每一个强连通分量里面是否存在奇环，没有奇环，这个强连通分量里的骑士就不可以参加任何会议。详细的证明在其他题解里已经有了，我就不赘述了。

有的小伙伴又要问为什么是找奇环呢？有这个疑问的朋友请再读一遍题，人数为奇数才可以开会，一个点在奇环里，那这一整个奇环的骑士就可以单独~~开个席~~。

又有同学会说，为什么不是找到一个最大的奇环，其他的就不可以参加呢？还是请看题意，会议是可以召开多次的。

这种变通灵活的题目看到要怎么入手呢？只有多做，多积累不同的做法和小技巧。量变引起质变，尽管这种变化对于不同的人是有不同的最低限度的，但是不去积累是永远不可能质变的。

最后注意一点，不算重边自环。

代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<stack>
#include<queue> 
#include<vector>
#include<set>
#include<stdlib.h>
using namespace std;
const int N=1e3+10;
const int M=1e6+10;
int n,m,ans;
int he[N],ne[M<<1],to[M<<1],tot=1;
bool rs[N][N];
void addedge(int x,int y){
	to[++tot]=y;
	ne[tot]=he[x];
	he[x]=tot;
}
int dfo[N],low[N],yes[N],cnt=0,sdcccnt=0,clo[N];
stack <int> q;
set <int> sdcc[N];
void tarjan(int now,int fa){
	int son=0;
	dfo[now]=low[now]=++cnt;
	q.push(now);
	for(int i=he[now];i;i=ne[i]){
		int v=to[i];
		++son;
		if(!dfo[v]){
			tarjan(v,now);
			low[now]=min(low[now],low[v]);
			if(dfo[now]<=low[v]){
				int p;
				++sdcccnt;
				do{
					p=q.top();
					sdcc[sdcccnt].insert(p);
					q.pop();
				}
				while(p!=v);
				sdcc[sdcccnt].insert(now);
			}
		}
		else {
			low[now]=min(low[now],dfo[v]);
		} 
	}
	if(son==0&&fa==0){
		sdcc[++sdcccnt].insert(now);
	}
}
bool dfs(int x,int fa,int num,int c){
	clo[x]=c;
	for(int i=he[x];i;i=ne[i]){
		int v=to[i];
		if(sdcc[num].count(v)<=0){
			continue;
		}
		else if(!clo[v]){
			if(dfs(v,x,num,c^1)==false){
				return false;
			}
		}
		else if(clo[v]==c){
			return false;
		}
	}
	return true;
}
bool st[N];
int main(){
	while(scanf("%d%d",&n,&m)&&n!=0){
		ans=cnt=sdcccnt=0,tot=1;
		memset(he,0,sizeof he);
		memset(ne,0,sizeof ne);
		memset(to,0,sizeof to);
		memset(low,0,sizeof low);
		memset(dfo,0,sizeof dfo);
		memset(st,0,sizeof st);
		memset(clo,0,sizeof clo);
		memset(yes,0,sizeof yes);
		memset(rs,0,sizeof rs);
		while(q.size()){
			q.pop();
		}
		int x,y;
		for(int i=1;i<=m;i++){
			scanf("%d%d",&x,&y);
			rs[x][y]=rs[y][x]=true;
		}
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				if(rs[i][j]==false){
					addedge(i,j);
					addedge(j,i);
				}
			}
		}
		for(int i=1;i<=n;i++){
			if(!dfo[i]){
				tarjan(i,0);
			}
		}
		set <int>::iterator it;
		for(int i=1;i<=sdcccnt;i++){
			x=*sdcc[i].begin();
			if(dfs(x,0,i,2)==false){
				for(it=sdcc[i].begin();it!=sdcc[i].end();it++){
					st[*it]=true;
				}
			}
			for(it=sdcc[i].begin();it!=sdcc[i].end();it++){
				clo[*it]=0;
			}
			sdcc[i].clear();
		}
		for(int i=1;i<=n;i++){
			if(!st[i]){
				ans++;
			}
		}
		printf("%d\n",ans);
	}
}
```


---

## 作者：lihaozhe (赞：2)

以骑士为结点建立无向图，两个骑士间存在边表示两个骑士可以相邻（用邻接矩阵存图，初始化全为1，读入一对憎恨关系就删去一条边即可），则题意变为求图中不在任何奇环（结点数为奇数的环）中的点的数量。

一个环上的点一定属于一个双连通分量（两两都有两条路径可达）

那么什么时候双连通分量中没有奇环呢？

显然，当双连通分量是二分图的时候，图中没有奇环，因为从一个点出发回到该点一定要经过偶数条边。

即**非二分图的双连通分量一定含有奇环**

那么，非二分图的双连通分量的每个点是否都在奇环中呢？

假设v,u1,u2属于同一个双连通分量，且已知u1,u2在奇环上。求证：v也在奇环上



因为u1,u2在奇环上，所以u1,u2在环上的两条路径一条长度为奇数，一条长度为偶数。故无论u1-v-u2的长度为奇数或偶数都可以以v,u1,u2构造一个奇圈

所以我们得到**非二分图的双连通分量中的每个点都在奇环上**

那么我们的任务就转换为**求无向图中是二分图的双连通分量中点的个数**

 

有了上面的分析，代码实现就很简单了

```cpp
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
using namespace std;
#define re register int
int graph[1001][1001];//邻接矩阵 
int dfn[1001],dfs_clock,n,m,stack[1001],top,ans,queue[1001],left,right,color[1001];
int bccno[1001],bcc_cnt,tot;//各个点bcc编号、当前bcc编号、bcc结点数目 
bool odd[1001];//每个点是否在奇圈上 
int read()
{
	int f=0,x=0;
	char c=getchar();
	while(!isdigit(c))
	{
		f=f|c=='-';
		c=getchar();
	}
	while(isdigit(c))
	{
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x;
}
bool bipartite(int x)//二分图判定 
{
	memset(color,0,sizeof(color));
	left=right=1;
	queue[1]=x;
	color[x]=1;
	while(right>=left)
	{
		int u=queue[left++];
		for(re v=1;v<=n;v++)
			if(graph[u][v]&&bccno[v]==bcc_cnt)
			{
				if(color[v]==color[u])
					return false;
				else if(!color[v])
				{
					queue[++right]=v;
					color[v]=3^color[u];
				}
			}
	}
	return true;
}
int tarjan(int u,int fa)//求双连通分量 
{
	int lowu=dfn[u]=++dfs_clock;
	for(re v=1;v<=n;v++)
		if(graph[u][v])
		{
			if(!dfn[v])
			{
				stack[++top]=v;
				int lowv=tarjan(v,u);
				lowu=min(lowu,lowv);
				if(lowv>=dfn[u])
				{
					tot=0;
					bcc_cnt++;
					while(stack[top]!=v)
					{
						tot++;
						bccno[stack[top--]]=bcc_cnt;
					}
					tot+=2;
					bccno[stack[top--]]=bccno[u]=bcc_cnt;//割点不出栈 
					if(!bipartite(u))//不是二分图，则此BCC中的点均在奇圈上 
						for(re i=1;i<=n;i++)
							if(bccno[i]==bcc_cnt)
								odd[i]=true;
				}
			}
			else if(v!=fa)
				lowu=min(lowu,dfn[v]);
		}
	return lowu;
}
void reset()
{
	memset(bccno,0,sizeof(bccno));
	memset(dfn,0,sizeof(dfn));
	memset(odd,0,sizeof(odd)); 
	dfs_clock=bcc_cnt=ans=top=0;
	for(re i=1;i<=n;i++)
		for(re j=1;j<=n;j++)
			graph[i][j]=1;
	for(re i=1;i<=n;i++)
		graph[i][i]=0;
}
int main()
{
	while((n=read())&&(m=read()))
	{
		reset();
		while(m--)
		{
			int u=read(),v=read();
			graph[u][v]=graph[v][u]=0;
		}
		for(re i=1;i<=n;i++)
			if(!dfn[i])
			{
				stack[++top]=i;
				tarjan(i,i);
			}
		for(re i=1;i<=n;i++)
			if(!odd[i])
				ans++;
		printf("%d\n",ans);
	}
	return 0;
}

```

---

## 作者：Yoimiyamwf (赞：1)

# 题目大意
若干骑士之间有若干憎恨关系，互相憎恨的骑士在同一圆桌会议中不能坐在相邻位置，每次会议人数必须为不小于 3 的奇数，问有多少个骑士不能参加任何会议。

# 分析
要求剔除不符合条件的点，容易想到根据憎恨关系建图，然后用 tarjan 算法求点双连通分量。

由于直接在基于憎恨关系的原图中求不符合条件的点较为困难，于是考虑建反图，在所有可以坐在一起的骑士之间连边。

这样转化之后，一个骑士可以参加至少一个会议，等价于其对应的点属于反图中的至少一个奇数环。

于是，该问题便被转化为“给定一张无向图，求其反图中不属于任何奇数环的点数”。

奇数环可以先求点双连通分量，然后在每个分量内部用染色法判断，在染色的过程中如果出现冲突，则说明该分量是一个奇数环。最后只需用总点数减去符合条件的点数，即为最终答案。

需要注意的一点是，不能直接用总点数减去奇数环分量的大小，因为割点可能同时属于多个分量，故应先标记所有符合条件的点，最后一起统计答案。

# 代码
```cpp
#include <bits/stdc++.h>
#define in inline
#define rint register int
#define r(a) runtimerror(a)
#define w(a) wronganswer(a)
#define wl(a) wronganswer(a);putchar('\n')
#define ws(a) wronganswer(a);putchar(' ')
using namespace std;
typedef long long ll;
stack <int> s;
bool ban[1010][1010],can[1010],psv[1010];
int tot,head[1010],n,m,u,v,dcnt,dfn[1010],low[1010],col[1010],ans,tmp;
vector <int> dcc[1010];
template <typename t> void wronganswer(t a){
	if(a<0) putchar('-'),a=-a;
	if(a>9) wronganswer(a/10);
	putchar(a%10^48);
}
template <typename t> in void runtimerror(t &a){
	char ch=getchar();
	t x=1,f=0;
	while(!isdigit(ch)){
		if(ch=='-') x=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		f=(f<<3)+(f<<1)+(ch^48);
		ch=getchar();
	}
	a=x*f;
}
struct Edge{
	int to,nex;
}edge[1000010];
in void add_edge(int from,int to){
	edge[++tot]=(Edge){to,head[from]};
	head[from]=tot;
}
bool dfs(int id){
	for(rint i=head[id];i;i=edge[i].nex){
		if(!can[edge[i].to]) continue;
		if(col[edge[i].to]){
			if(col[edge[i].to]==col[id]) return false;
		}else{
			col[edge[i].to]=3-col[id];
			if(!dfs(edge[i].to)) return false;
		}
	}
	return true;
}
void tarjan(int id){
	dfn[id]=low[id]=++tmp;
	s.push(id);
	for(rint i=head[id];i;i=edge[i].nex){
		if(!dfn[edge[i].to]){
			tarjan(edge[i].to);
			low[id]=min(low[id],low[edge[i].to]);
			if(low[edge[i].to]>=dfn[id]){
				int x;
				dcnt++;
				do{
					x=s.top();
					dcc[dcnt].push_back(x);
					s.pop();
				}while(x!=edge[i].to);
				dcc[dcnt].push_back(id);
			}
		}else low[id]=min(low[id],dfn[edge[i].to]);
	}
}
in void clear(){
	memset(ban,0,sizeof(ban));
	memset(psv,0,sizeof(psv));
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	memset(col,0,sizeof(col));
	memset(dcc,0,sizeof(dcc));
	memset(head,0,sizeof(head));
	tmp=dcnt=tot=0;
}
int main(){
	while(r(n),r(m),n||m){
		clear();
		ans=n;
		for(rint i=1;i<=m;i++){
			r(u),r(v);
			ban[u][v]=ban[v][u]=true;
		}
		for(rint i=1;i<=n;i++){
			for(rint j=i+1;j<=n;j++){
				if(!ban[i][j]){
					add_edge(i,j);
					add_edge(j,i);
				}
			}
		}
		for(rint i=1;i<=n;i++){
			if(!dfn[i]) tarjan(i);
		}
		for(rint i=1;i<=dcnt;i++){
			int sz=dcc[i].size();
			memset(can,0,sizeof(can));
			for(rint j=0;j<sz;j++){
				can[dcc[i][j]]=true,col[dcc[i][j]]=0;
			}
			col[dcc[i][0]]=1;
			if(!dfs(dcc[i][0])){
				for(rint j=0;j<sz;j++){
					psv[dcc[i][j]]=true;
				}
			}
		}
		for(rint i=1;i<=n;i++){
			if(psv[i]) ans--;
		}
		wl(ans);
	}
	return 0;
}
```


---

## 作者：carp_oier (赞：1)

# advertisement

这位靓仔，你既然都来看我的题解了，为什么不来[我的博客](https://www.cnblogs.com/carp-oier/p/17730505.html)看呢。

# prologue

相信很多人都感觉这个题不就是求一下这个二分图的最大独立集嘛，有什么难的，（劈里啪啦、库里跨啦、叮里哐啷）好，不对，好好好，题解！

# analysis

这个题目实际上并不是一个完整的最大独立集问题，因为在这个题里面，是可以有相互仇恨的骑士的，只要不让他们二人坐成同桌就行。

那么我们就不如从正面来解决这个题。

首先，建立这个 **憎恨** 关系的 **补图** 从而得到一张 **友善** 关系图，这个时候肯定会形成环，我们进行下一步的思考。

之后，用 **tarjan** 将每个图所成一个点，之后对于每一个内部点数大于等于三的 **V-DCC** 进行判断内部是不是 **奇环**（题目中有描述，每次会议只能是奇数个人），如果这个环内部的数量不是奇数，那么这环内部的骑士就不能参与会议，属于要被除名的人。

对于判断每一个环是不是奇环，我们可以用 **染色法**，如果发生 **冲突** 则代表内部是合法的，如果成功染色，则是 **非法** 的。

同时还有一个重要结论~~虽然我不知道为什么重要，大佬说是就是~~：**点双连通图中若包含一个奇环，则所有点都在至少一个简单奇环上。**

至于证明过程，大家可以前往巨佬的[博客](https://www.luogu.com.cn/blog/221955/solution-sp2878)查看。

# CODE TIME
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rl register ll

const ll N = 1010;

ll n, m;

ll dfn[N], low[N], top, timestamp, ans, tmp[N];

ll stk[N], dcc_cnt, dcc_size[N], col[N], root, now;

bool g[N][N], val[N], in_dcc[N], flag;

vector<ll> dcc[N];

inline void dfs(ll u, ll c)
{
	if(flag) return ;
	col[u] = c;
	for(rl i=1; i <= n; ++ i) if(g[u][i])
	{
		if(tmp[i] != now) continue;
		if(col[i]) if(col[i] == c) { flag = 1; return ;}
		if(!col[i]) dfs(i, 3 - c);
	}
}

inline void tarjan(ll u)
{
	stk[ ++ top] = u;
	dfn[u] = low[u] = ++ timestamp;
	
	for(rl v=1; v <= n; ++ v)
	{
		if(!g[u][v]) continue;
		if(!dfn[v])
		{
			tarjan(v), low[u] = min(low[u], low[v]);
			if(low[v] >= dfn[u])
			{
				dcc_cnt ++ ;
				ll ele;
				do {
					ele = stk[top -- ];
					dcc[dcc_cnt].push_back(ele), dcc_size[dcc_cnt] ++ ;
				} while(ele != v);
				dcc[dcc_cnt].push_back(u), dcc_size[dcc_cnt] ++;
			}
		}
		else low[u] = min(low[u], dfn[v]);
	}
}

inline void clean()
{
	for(rl i=1; i <= dcc_cnt; ++ i) dcc[i].clear();
	top = timestamp = dcc_cnt = ans = 0;
	memset(dcc_size, 0, sizeof dcc_size), memset(dfn, 0, sizeof dfn), memset(tmp, 0, sizeof tmp);
	memset(g, 0, sizeof g), memset(col, 0, sizeof col), memset(val, 0, sizeof val);
}

int main()
{
	while(cin >> n >> m, n)
	{
		clean();
		for(rl i=1; i <= n; ++ i) g[i][i] = 1;
		for(rl i=1; i <= m; ++ i)
		{
			ll a, b;
			cin >> a >> b;
			g[a][b] = g[b][a] = true;
		}
		
		for(rl i=1; i <= n; ++ i)
			for(rl j=1; j <= n; ++ j)
				g[i][j] ^= 1;
				
		for(root = 1; root <= n; ++ root)
			if(!dfn[root])
				tarjan(root);
		
		for(rl i=1; i <= dcc_cnt; ++ i)
		{
			now = i, flag = 0;
			for(rl j : dcc[i]) tmp[j] = now, col[j] = 0;
			dfs(dcc[i][0], 1);
			if(flag)
				for(rl j : dcc[i])
					val[j] = true;
		}
		
		for(rl i=1; i <= n; ++ i) ans += val[i];
			
		cout << n - ans << endl;
	}
	return 0;
}
```

---

## 作者：highscore (赞：1)

前置知识：点双，二分图判定

[不会点双的可以去这里哦](https://www.cnblogs.com/Aswert/p/14273854.html)

会了前置知识后，我们来看这道题。

首先，我们可以把不讨厌的人之间建图，就是在两个人之间连一条无向边；
那么一名骑士能参见会议的条件是，它对应的节点在一个奇环上；
所以本题就是找不被任何奇环包含的节点。

那么我们来看两个引理

1.若两个节点不在一个点双内，那么这两个节点不可能一起出席会议.


2.若两个点双内存在奇环，则这个点双中的所有点都至少有一个奇环包含；

那么这道题就可以做了，先求出点双，然后判断点双内有没有奇环即可，

AC代码
```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
const int N=1010;
const int M=1e6+7;
struct edge{
	int v,nxt;
}e[M<<1];
int n,m,cnt,rt,h,now,flag,tot,ans;
int a[N][N],st[N],head[N],g[N],c[N],dfn[N],low[N],ok[N];
vector<int> dcc[N];

void init(){
	tot=0;
	h=0;
	ans=0;
	cnt=0;
	memset(head,0,sizeof(head));
	memset(ok,0,sizeof(ok));
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	memset(g,0,sizeof(g));
	for(int i=1;i<=n;i++) dcc[i].clear();
} 

void add_edge(int u,int v){
	e[++cnt]=(edge){v,head[u]};
	head[u]=cnt;
}

void tarjan(int u){
	dfn[u]=low[u]=++tot;
	if(u==rt&&head[u]==0){
		dcc[++cnt].push_back(u);
		return;
	}
	st[++h]=u;
	for(int i=head[u];i;i=e[i].nxt){
		int to=e[i].v;
		if(!dfn[to]){
			tarjan(to);
			low[u]=min(low[u],low[to]);
			if(dfn[u]<=low[to]){
				cnt++;
				int k;
				do{
					k=st[h];h--;
					dcc[cnt].push_back(k);
				}while(k!=to);
				dcc[cnt].push_back(u);
			}
		}else low[u]=min(low[u],dfn[to]);
	}
}

void dfs(int u,int color){
	if(flag) return;
	c[u]=color;
	for(int i=head[u];i;i=e[i].nxt){
		int to=e[i].v;
		if(g[to]!=now) continue;
		if(c[to]==color){
			flag=1;
			return;
		}
		if(!c[to]) dfs(to,3-color);
	}
}


int main(){
	while(scanf("%d%d",&n,&m),(n+m)){
		init();
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				a[i][j]=0;
			}
		}
		for(int i=1;i<=m;i++){
			int x,y;
			scanf("%d%d",&x,&y);
			if(x!=y){
				a[x][y]=a[y][x]=1;
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<i;j++){
				if(!a[i][j]){
					add_edge(i,j);
					add_edge(j,i);
				}
			}
		}
		cnt=0;
		for(int i=1;i<=n;i++){
			if(!dfn[i]){
				rt=i;
				tarjan(i);
			}
		}
		for(int i=1;i<=cnt;i++){
			now=i;
			flag=0;
			for(int j=0;j<(int)dcc[i].size();j++){
				g[dcc[i][j]]=now;
				c[dcc[i][j]]=0;
			}
			dfs(dcc[i][0],1);
			if(flag){
				for(int j=0;j<(int)dcc[i].size();j++){
					ok[dcc[i][j]]=1;
				}
			}
		}
		for(int i=1;i<=n;i++){
			if(ok[i]!=1) ans++;
		}
		cout<<ans<<"\n";
	}
}
/*
5 5
1 4
1 5
2 5
3 4
4 5
5 5
1 4
1 5
2 5
3 4
4 5
0 0
*/
```




































---

## 作者：封禁用户 (赞：1)

## adv.
这题同POJ 2942双倍经验，~~(要是Luogu也能交POJ就好了)~~

个人博客同步：http://www.cinema000.xyz/1500.ruby

## 分析
其实这个问题简化后就是求不在任何一个简单奇圈上的结点个数。
解法：对于每个连通分量的每个双连通分量B，如果它不是二分图，则标记B中结点在奇圈上。
算理：二分图没有奇圈
## 代码
```cpp
//
//  main.cpp
//  UVa 1364
//
//  Created by Louis Cinema on 2018/8/8.
//  Copyright © 2018年 Cinema Media Group. All rights reserved.
//

#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstring>
const int MAXN = 1000 + 6;
struct Edge{int u,v;Edge(int u,int v){this -> u = u;this -> v = v;}Edge(){}};

int pre[MAXN],BCCNo[MAXN],dfsClock,BCCCnt;
bool isCut[MAXN];
std::vector<int> G[MAXN],BCC[MAXN];
std::stack<Edge> S;
int dfs(int u,int fa){
    int lowU = pre[u] = ++dfsClock,child = 0;
    for(int i = 0;i < G[u].size();i++){
        int v = G[u][i];
        Edge e(u,v);
        if(!pre[v]){
            S.push(e);
            child++;
            int lowV = dfs(v, u);
            lowU = std::min(lowU,lowV);
            if(lowV >= pre[u]){
                isCut[u] = true;
                BCCCnt++;BCC[BCCCnt].clear();
                while (true) {
                    Edge x = S.top();S.pop();
                    if(BCCNo[x.u] != BCCCnt) BCC[BCCCnt].push_back(x.u),BCCNo[x.u] = BCCCnt;
                    if(BCCNo[x.v] != BCCCnt) BCC[BCCCnt].push_back(x.v),BCCNo[x.v] = BCCCnt;
                    if(x.u == u && x.v == v) break;
                }
            }
        }else if(pre[v] < pre[u] && v != fa){
            S.push(e);
            lowU = std::min(lowU,pre[v]);
        }
    }
    if(fa < 0 && child == 1) isCut[u] = false;
    return lowU;
}
void findBCC(int n){
    memset(pre, 0, sizeof(pre));
    memset(isCut, false, sizeof(isCut));
    memset(BCCNo, 0, sizeof(BCCNo));
    dfsClock = BCCCnt = 0;
    for(int i = 0;i < n;i++) if(!pre[i]) dfs(i, -1);
}

int odd[MAXN],color[MAXN];
bool isBG(int u,int b){
    for(int i = 0;i < G[u].size();i++){
        int v = G[u][i];if(BCCNo[v] != b) continue;
        if(color[v] == color[u]) return false;
        if(!color[v]){
            color[v] = 3 - color[u];
            if(!isBG(v, b)) return false;
        }
    }
    return true;
}
int A[MAXN][MAXN];

int main(int argc, const char * argv[]) {
    int n,m;
    while (scanf("%d %d",&n,&m) == 2 && n) {
        for(int i = 0;i < n;i++) G[i].clear();
        memset(A,0,sizeof(A));
        for(int i = 0;i < m;i++){
            int u,v;scanf("%d %d",&u,&v);u--,v--;
            A[u][v] = A[v][u] = true;
        }
        for (int u = 0; u < n; u++) for(int v = u + 1;v < n;v++) if(!A[u][v]) G[u].push_back(v),G[v].push_back(u);
        findBCC(n);
        memset(odd, 0, sizeof(odd));
        for(int i = 1;i <= BCCCnt;i++){
            memset(color, 0, sizeof(color));
            for(int j = 0;j < BCC[i].size();j++) BCCNo[BCC[i][j]] = i;
            int u = BCC[i][0];
            color[u] = 1;
            if(!isBG(u,i)) for(int j = 0;j < BCC[i].size();j++) odd[BCC[i][j]] = 1;
        }
        int ans = n;
        for(int i = 0;i < n;i++) if(odd[i]) ans--;
        printf("%d\n",ans);
    }
    
    return 0;
}

```

---

## 作者：Yaha (赞：1)

### 点双连通分量

参考了李煜东大佬《算法竞赛进阶指南》中的思路

#### 题意：

无向图，求有多少个点不被任何奇环包含。$n\le 10^3$

#### 思路：

结合“无向图” “环” “点被环包含”这些字眼，我们也许能联想到点双连通分量。

	点双连通分量：满足点数小于2，或者任何两个点同时包含至少一个简单环中。

我们分两种情况来讨论：

- **对于两个不同的点双连通分量，不可能有奇环横跨**。

否则，大概是这个样子的：

![](https://cdn.luogu.com.cn/upload/image_hosting/2f4gav1w.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

即两个双连通分量 A 和 B ，有环 C 横跨，这时删掉图上任何一点，这个新的子图中任意两个点可互达。所以这该是一个更大的点双连通分量才对，跟点双连通分量的的“极大性”矛盾。

- **对于一个点双连通分量，若出现奇环，则这个点双连通分量中的所有点都能被至少一个奇环包含**

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/eo7mobr1.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

由于是双连通分量，环上必然存在两个点 $i$ ， $j$ ，满足有一个同时包含 $i$ ， $j$ ，$x$ 的简单环。

![](https://cdn.luogu.com.cn/upload/image_hosting/q7c1f76y.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

我们把奇环拆成两部分：奇 $+$ 偶。 $c$ 和 $d$ 必然一奇一偶。

若 $c+a+b$ 为奇环的话，$x$ 被奇环包含；

否则 $d+a+b$ 一定为奇环，$x$ 被奇环包含。

所以，我们先求点双连通分量，再求是否有奇环，若有，上面的所有点都不用被踢出去，即不计入答案。

求奇环可以用染色法。

代码：

```cpp
#include<bits/stdc++.h>

using namespace std;

const int amou=1100,M=2e6+90;

int n,m;
bool ag[amou][amou];
int nxt[M],head[amou],ver[M],cnt;
int dfn[amou],low[amou],timestamp;
int stac[amou],top;
int col[amou],v_dcc,root;
vector<int> V[amou];
int block[amou];
bool we[amou];
bool is_cut[amou];

void add(int a,int b){
	nxt[++cnt]=head[a],head[a]=cnt,ver[cnt]=b;
}

void init(){
	memset(dfn,0,sizeof dfn);
	memset(low,0,sizeof low);
	memset(head,0,sizeof head);
	memset(nxt,0,sizeof nxt);
	memset(ver,0,sizeof ver);
	for(int i=1;i<=v_dcc;i++) V[i].clear();
	memset(block,0,sizeof block);
	memset(col,0,sizeof col);
	memset(is_cut,0,sizeof is_cut);
	top=timestamp=v_dcc=0;
}

void Tarjan(int x){
	dfn[x]=low[x]=++timestamp;
	stac[++top]=x;
	int child=0;
	for(int io=head[x];io;io=nxt[io])
	{
		int v=ver[io];
		if(!dfn[v])
		{
			child++;
			Tarjan(v);
			low[x]=min(low[x],low[v]);
			if(dfn[x]<=low[v])
			{
				if(x!=root||child>1) is_cut[x]=1;
				int p;
				V[++v_dcc].push_back(x);
				do{
					p=stac[top--];
					V[v_dcc].push_back(p);
					block[p]=v_dcc;
				}while(p!=v);
			}
		}
		else low[x]=min(low[x],dfn[v]);
	}
}

bool dfs(int i,int color,int piece){
	col[i]=color;
	bool fl=0;
	for(int io=head[i];io;io=nxt[io])
	{
		int v=ver[io];
		if(block[v]!=piece) continue;
		if(!col[v])
		{
			if(dfs(v,3-color,piece))
				return true;
		}
		if(col[v]==color) return true;
	}
	return false;
}

int main(){
	while(scanf("%d%d",&n,&m),(n||m))
	{
		for(int i=1;i<=m;i++)
		{
			int a,b;
			scanf("%d%d",&a,&b);
			ag[a][b]=ag[b][a]=1;
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=i+1;j<=n;j++)
			{
				if(!ag[i][j]) add(i,j),add(j,i);
				else ag[i][j]=ag[j][i]=0;
			}
		}
		for(int i=1;i<=n;i++)
		{
			if(!dfn[i]) root=i,Tarjan(i);
		}
		for(int i=1;i<=v_dcc;i++)
		{
			for(int j=0;j<V[i].size();j++)
			{
				int x=V[i][j];
				if(is_cut[x]) block[x]=i;
				col[x]=0;
			}
			if(dfs(V[i][0],1,i))
			{
				for(int j=0;j<V[i].size();j++)
				{
					int x=V[i][j];
					we[x]=1;
				}
			}
		}
		int as=0;
		for(int i=1;i<=n;i++)
		{
			if(!we[i]) as++;
			else we[i]=0;
		}
		printf("%d\n",as);
		init();
	}
	
	return 0;
}
```



---

