# [USACO11MAR] Meeting Place S

## 题目描述

Bessie and Jonell are great friends. Since Farmer John scrambles where the cows graze every day, they are sometimes quite far from each other and can't talk.

The pastures and paths on FJ's farm form a 'tree' structure.  Each pasture has exactly one distinct path to any other pasture, and each pasture (except pasture #1, the 'root') also has a single parent node.

Bessie and Jonell have decided that they will always meet at the closest pasture that that is both an ancestor of Jonell's pasture and of Bessie's pasture.

FJ created a map of his N (1 <= N <= 1,000) pastures (conveniently numbered 1..N) that tells the parent P\_i (1 <= P\_i <= N) of each pasture except pasture 1, which has no parent.

FJ has released his daily grazing schedule for the next M (1 <= M <= 1,000) days, so Bessie and Jonell are deciding where they should meet each day for gossip. On day k, Bessie is in pasture B\_k (1 <= B\_k <= N) and Jonell is in pasture J\_k (1 <= J\_k <= N).

Given a map and schedule, help Bessie and Jonell find their meeting places.

```cpp
Consider, for example, the following farm layout:

                            Pasture      Parent Pasture
             [1]           ---------    ----------------
            / | \              1              ---
           /  |  \             2               1 
         [2] [3] [6]           3               1
         /        | \          4               2
        /         |  \         5               8
      [4]        [8]  [9]      6               1
                /   \          7               8
               /     \         8               6
             [5]     [7]       9               6

Here are the meeting places that Bessie and Jonell would choose
given a six day schedule of their initial grazing locations:

              Bessie      Jonell       Meeting Place
             --------    --------     ---------------
                 2           7               1
                 4           2               2
                 1           1               1
                 4           1               1
                 7           5               8
                 9           5               6
```




## 样例 #1

### 输入

```
9 6 
1 
1 
2 
8 
1 
8 
6 
6 
2 7 
4 2 
3 3 
4 1 
7 5 
9 5 
```

### 输出

```
1 
2 
3 
1 
8 
6 
```

# 题解

## 作者：In_blue (赞：8)

~~看了很久的题解，发现大佬们的代码十分深奥，看都看不懂QWQ~~


------------
# 进入正题
	看都这题，首先就看数据范围
~~数据好水~~

于是就有了一个暴力枚举的思想:
	
    1.题目说这是一个树形结构，所以理想当然的的想到了用数组模拟建树。我们定义a[i]保存的为父节点的位置，x为父节点的位置；于是就有了a[i]=x；
    2.题目意思是让我们找出x，y的最近父节点，那么我们可以开两个bool数组bol1[],bol2[]，分别保存x的各个父节点和y的各个父节点，并使x，y相继保存它们的父节点。这是我们可以发现，当第一次x的父节点中有y时或是y的父节点中有x时，就是答案。即（bol1[y]==1||bol2[x]==1)时，输出为真的点即可；

以下是代码

```
#include<iostream>
#include<cstring>
using namespace std;
int a[1010];
int x,y;
int m,n;
int main()
{
	cin>>n>>m;
	for(int i=2;i<=n;i++)
	{
		cin>>x;
		a[i]=x;
	}
	for(int i=1;i<=m;i++)
	{
		cin>>x>>y;
		bool bol1[1010],bol2[1010];
		memset(bol1,0,sizeof(bol1));
		memset(bol2,0,sizeof(bol2));
		bol1[x]=1;
		bol2[y]=1;
		bool t=0;
		if(x!=y)
		{
			while(a[x] && a[y])
			{
				x=a[x];
				y=a[y];
				bol1[x]=1;
				bol2[y]=1;
				if(bol1[y]||bol2[x])
				{
					t=1;
					if(bol1[y])
					{
						cout<<y<<endl;
						break;
					}
					cout<<x<<endl;
					break;
				}
			}
		}
		else cout<<x<<endl,t=1;
		if(t==0)cout<<1<<endl;
	}
	return 0;
}
```

警告：不要抄代码！！！！


求过QAQ

---

## 作者：hulean (赞：7)

看上去是LCA诶（逃

> 下面整合了一下LCA的方法，最后有注明出处。

## 概念

首先是最近公共祖先的概念(什么是最近公共祖先？)：

在一棵没有环的树上，每个节点肯定有其父亲节点和祖先节点，而最近公共祖先，就是两个节点在这棵树上深度最大的公共的祖先节点。

换句话说，就是两个点在这棵树上距离最近的公共祖先节点。

所以LCA主要是用来处理当两个点仅有唯一一条确定的最短路径时的路径。

有人可能会问：那他本身或者其父亲节点是否可以作为祖先节点呢？

答案是肯定的，很简单，按照人的亲戚观念来说，你的父亲也是你的祖先，而LCA还可以将自己视为祖先节点。

举个例子吧，如下图所示4和5的最近公共祖先是2，5和3的最近公共祖先是1，2和1的最近公共祖先是1。　

![404](https://cdn.luogu.com.cn/upload/pic/62400.png)

这就是最近公共祖先的基本概念了，那么我们该如何去求这个最近公共祖先呢？

通常初学者都会想到最简单粗暴的一个办法：对于每个询问，遍历所有的点，时间复杂度为$O(n*q)$ ，很明显，n和q一般不会很小。

**怎么办办？**

**LCA其实有很多种解法，这里介绍几个**

## 一、Tarjan大法好！

什么是Tarjan(离线)算法呢？顾名思义，就是在一次遍历中把所有询问一次性解决，所以其时间复杂度是$O(n+q)$。

Tarjan算法的优点在于相对稳定，时间复杂度也比较居中，也很容易理解。

下面详细介绍一下Tarjan算法的基本思路：

1. 任选一个点为根节点，从根节点开始。

2. 遍历该点u所有子节点v，并标记这些子节点v已被访问过。

3. 若是v还有子节点，返回2，否则下一步。

4. 合并v到u上。

5. 寻找与当前点u有询问关系的点v。

6. 若是v已经被访问过了，则可以确认u和v的最近公共祖先为v被合并到的父亲节点a。

遍历的话需要用到dfs来遍历(相信来看的人都懂吧...)，至于合并，最优化的方式就是利用并查集来合并两个节点。

- 伪代码

```cpp
Tarjan(u)//marge和find为并查集合并函数和查找函数
{
    for each(u,v)    //访问所有u子节点v
    {
        Tarjan(v);        //继续往下遍历
        marge(u,v);    //合并v到u上
        标记v被访问过;
    }
    for each(u,e)    //访问所有和u有询问关系的e
    {
        如果e被访问过;
        u,e的最近公共祖先为find(e);
    }
}
```
个人感觉这样还是有很多人不太理解，所以打算模拟一遍给大家看。

假设我们有一组数据 9个节点 8条边 联通情况如下：

1--2，1--3，2--4，2--5，3--6，5--7，5--8，7--9 即下图所示的树

设我们要查找最近公共祖先的点为9--8，4--6，7--5，5--3；

设``f[]``数组为并查集的父亲节点数组，初始化``f[i]=i``，``vis[]``数组为是否访问过的数组，初始为0;　

![404](https://cdn.luogu.com.cn/upload/pic/62402.png)

下面开始**模拟过程**：

取1为**根节点**，**往下搜索**发现有两个儿子2和3；

先搜2，发现2有两个儿子4和5，先搜索4，发现4**没有子节点**，则寻找与其有关系的点；

发现6与4有关系，但是``vis[6]=0``，即6还没被搜过，所以**不操作**；

发现没有和4有询问关系的点了，**返回此前一次搜索**，更新``vis[4]=1``；

![404](https://cdn.luogu.com.cn/upload/pic/62405.png)

表示4已经被搜完，更新``f[4]=2``，继续搜5，发现5有两个儿子7和8;

先搜7，发现7有一个子节点9，搜索9，发现没有子节点，**寻找与其有关系的点**；

发现8和9有关系，但是``vis[8]=0``,即8没被搜到过，所以**不操作**；

发现**没有**和9有询问关系的点了，**返回此前一次搜**索，更新vis[9]=1；

表示9已经被搜完，更新``f[9]=7``，发现7**没有**没被搜过的子节点了，寻找与其有关系的点；

发现5和7有关系，但是``vis[5]=0``，所以**不操作**；

发现没有和7有关系的点了，返回此前一次搜索，更新``vis[7]=1``；

![404](https://cdn.luogu.com.cn/upload/pic/62406.png)

表示7已经被搜完，更新``f[7]=5``，继续搜8，发现8没有子节点，则寻找与其有关系的点；

发现9与8有关系，此时``vis[9]=1``，则他们的**最近公共祖先**为``find(9)=5``；

``(find(9)的顺序为f[9]=7-->f[7]=5-->f[5]=5 return 5;)``

发现没有与8有关系的点了，返回此前一次搜索，更新``vis[8]=1``；

表示8已经被搜完，更新``f[8]=5``，发现5**没有**没搜过的子节点了，寻找与其**有关系**的点；

![404](https://cdn.luogu.com.cn/upload/pic/62407.png)

发现7和5**有关系**，此时``vis[7]=1``，所以他们的**最近公共祖先**为``find(7)=5``；

``(find(7)的顺序为f[7]=5-->f[5]=5 return 5;)``

又发现5和3**有关系**，但是``vis[3]=0``，所以不操作，此时5的子节点全部搜完了；

返回**此前一次搜索**，更新``vis[5]=1``，表示5已经被搜完，更新``f[5]=2``；

发现2没有未被搜完的子节点，寻找与其有关系的点；

又发现没有和2有关系的点，则**此前一次搜索**，更新``vis[2]=1``；

![404](https://cdn.luogu.com.cn/upload/pic/62408.png)

表示2已经被搜完，更新f[2]=1，继续搜3，发现3有一个子节点6；

搜索6，发现6没有子节点，则寻找与6有关系的点，发现4和6**有关系**；

此时``vis[4]=1``，所以它们的**最近公共祖先**为``find(4)=1``;

``(find(4)的顺序为f[4]=2-->f[2]=2-->f[1]=1 return 1;)``

发现**没有**与6**有关系**的点了，返回**此前一次搜索**，更新``vis[6]=1``，表示6已经被**搜完**了；

![404](https://cdn.luogu.com.cn/upload/pic/62409.png)

更新``f[6]=3``，发现3没有没被搜过的子节点了，则寻找与3**有关系**的点；

发现5和3有关系，此时``vis[5]=1``，则它们的**最近公共祖先**为``find(5)=1``；

``(find(5)的顺序为f[5]=2-->f[2]=1-->f[1]=1 return 1;)``

发现没有和3有关系的点了，返回**此前一次搜索**，更新``vis[3]=``；

![404](https://cdn.luogu.com.cn/upload/pic/62410.png)

更新``f[3]=1``，发现1没有被搜过的子节点也没有有关系的点，此时可以退出整个dfs了。

经过这次dfs我们得出了所有的答案，有没有觉得很神奇呢？是否对Tarjan算法有更深层次的理解了呢？

## 二、倍增LCA

![404](https://cdn.luogu.com.cn/upload/pic/61612.png)

**何为倍增？**

所谓倍增，就是按$2$的倍数来增大，也就是跳 $1,2,4,8,16,32……$ 不过在这我们不是按从小到大跳，而是从大向小跳，即按$……32,16,8,4,2,1$来跳，如果大的跳不过去，再把它调小。这是因为从小开始跳，可能会出现“悔棋”的现象。拿 55 为例，从小向大跳，$5≠1+2+4$,所以我们还要回溯一步，然后才能得出$5=1+4$；而从大向小跳，直接可以得出$5=4+1$。这也可以拿二进制为例，$5(101)$，从高位向低位填很简单，如果填了这位之后比原数大了，那我就不填，这个过程是很好操作的。

这里以编号为17和18结点为例

$17->3$

$18->5->3$

可以看出向上跳的次数大大减小。这个算法的时间复杂度为$O(nlogn)$,已经可以满足大部分的需求。

想要实现这个算法，首先我们要记录各个点的深度和他们$2^i$级的的祖先，用数组$\rm{deep}$表示每个节点的深度，$fa[i][j]$表示节点$i$的$2^j$级祖先。 代码如下：

```cpp
inline void getdeep(int now,int father)//now表示当前节点，father表示它的父亲节点
{
	deep[now]=deep[father]+1;
	fa[now][0]=father;
	for(int i=1;(1<<i)<=deep[now];i++)
		fa[now][i]=fa[fa[now][i-1]][i-1];//这个转移可以说是算法的核心之一
						//意思是f的2^i祖先等于f的2^(i-1)祖先的2^(i-1)祖先
						//2^i=2^(i-1)+2^(i-1)
	for(int i=head[now];i;i=edge[i].next)//注意：尽量用链式前向星来存边，速度会大大提升
	{
		if(edge[i].to==father)continue;
		getdeep(edge[i].to,now);
	}
}
```

然后我们要算出log2n

```cpp
log2n=log(n)/log(2)+0.5;
```

接下来就是**倍增LCA**了，我们**先把两个点提到同一高度，再统一开始跳**。

但我们在跳的时候不能直接跳到它们的LCA，因为这可能会误判，比如$4$和$8$，在跳的时候，我们可能会认为$1$是它们的LCA，但$1$只是它们的祖先，它们的LCA其实是$3$。所以我们要跳到它们LCA的下面一层，比如$4$和$8$，我们就跳到$4$和$5$，然后输出它们的父节点，这样就不会误判了。

```cpp
inline int lca(int u,int v)
{
	int deepu=deep[u],deepv=deep[v];
	if(deepu!=deepv)//先跳到同一深度
	{
		if(deep[u]<deep[v])
		{
			swap(u,v);
			swap(deepu,deepv);
		}
		int d=deepu-deepv;
		for(int i=0;i<=log2n;i++)
			if((1<<i)&d)u=fa[u][i];
	}
	if(u==v)return u;
	for(int i=log2n;i>=0;i--)
	{
		if(deep[fa[u][i]]<=0)continue;
		if(fa[u][i]==fa[v][i])continue;
		else u=fa[u][i],v=fa[v][i];//因为我们要跳到它们LCA的下面一层，所以它们肯定不相等，如果不相等就跳过去。
	}
	return fa[u][0];
}
```
完整的求17和18的LCA的路径：

$17->10->7->3$

$18->16->8->5->3$

解释：首先，$18$要跳到和$17$深度相同，然后$18$和$17$一起向上跳，一直跳到LCA的下一层($17$是$7$，$18$是$5$)，此时LCA就是它们的父亲

总体来说就是这样了;

参考博文:https://www.cnblogs.com/jvxie/p/4854719.html
 
参考博文:https://www.luogu.org/blog/morslin/solution-p3379

# 本题代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=500000+10;
int n,m,s;
struct Node
{
	int next,to;	
}edge[MAXN*2];
int cnt;
int head[MAXN];
int deep[MAXN];
int fa[MAXN][20];
int log2n;
inline int read()
{
	int tot=0;
	char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
	{
		tot=(tot<<1)+(tot<<3)+c-'0';
		c=getchar();
	}
	return tot;
}
inline void add(int x,int y)
{
	edge[++cnt].to=y;
	edge[cnt].next=head[x];
	head[x]=cnt;
	edge[++cnt].to=x;
	edge[cnt].next=head[y];
	head[y]=cnt;
}
inline void getdeep(int now,int father)
{
	deep[now]=deep[father]+1;
	fa[now][0]=father;
	for(int i=1;(1<<i)<=deep[now];i++)
		fa[now][i]=fa[fa[now][i-1]][i-1];
	for(int i=head[now];i;i=edge[i].next)
	{
		if(edge[i].to==father)continue;
		getdeep(edge[i].to,now);
	}
}
inline int lca(int u,int v)
{
	int deepu=deep[u],deepv=deep[v];
	if(deepu!=deepv)
	{
		if(deep[u]<deep[v])
		{
			swap(u,v);
			swap(deepu,deepv);
		}
		int d=deepu-deepv;
		for(int i=0;i<=log2n;i++)
			if((1<<i)&d)u=fa[u][i];
	}
	if(u==v)return u;
	for(int i=log2n;i>=0;i--)
	{
		if(deep[fa[u][i]]<=0)continue;
		if(fa[u][i]==fa[v][i])continue;
		else u=fa[u][i],v=fa[v][i];
	}
	return fa[u][0];
}
int main()
{
	n=read();m=read();s=1;
	for(int i=2;i<=n;i++)
	{
		int x=read();
		add(x,i);
	}
	getdeep(s,0);
	log2n=log(n)/log(2)+0.5;
	for(int i=1;i<=m;i++)
		printf("%d\n",lca(read(),read()));
	return 0;
}
```

---

## 作者：StudyingFather (赞：3)

一道LCA的裸题，但这道题似乎数据很弱啊，其实O(n)的算法也可以AC本题...
```cpp
#include <stdio.h>
#include <string.h>
int fa[1005],t[1005];
int main()
{
 int n,m;
 scanf("%d%d",&n,&m);
 for(int i=2;i<=n;i++)
  scanf("%d",&fa[i]);
 for(int i=1;i<=m;i++)
 {
  memset(t,0,sizeof(t));
  int u,v;
  scanf("%d%d",&u,&v);
  int a=u,b=v;
  while(1)//向上走，记录路径
  {
   t[a]=1;
   if(a==1)break;
   a=fa[a];
  }
  while(1)
  {
   if(t[b]==1)//两者路径最早相交之处，即为最近公共祖先
   {
   	printf("%d\n",b);
   	break;
   }
   b=fa[b];
  }
 }
 return 0;
}
```

---

## 作者：45dino (赞：1)

其实求 LCA 还有一个方法，就是转化为欧拉序列上的 RMQ 问题

听起来挺复杂，其实很简单，拿样例来举例：
```
9 6 
1 
1 
2 
8 
1 
8 
6 
6  
```
把图画好，然后用dfs过一遍，经过的点的顺序（欧拉序）就是：
```
1 2 4 2 1 3 1 6 8 5 8 7 8 6 9 6 1
```
同时处理出每一个点的深度：
```
1 2 1 2 1 2 1 2 3 4 3 4 3 2 3 2 1
```
对与每一个询问，比如```9 5```，找到他们在欧拉序里面的位置，两个位置之间深度最浅的一个点必然是这两个点的 LCA 。

对于找深度最浅的点，一般都要用数据结构进行维护，但显然这道题暴力乱搞就行了。用数据结构优化的代码可以自行思考。

喜闻乐见的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int to,next;
} edge[2001];
int n,m,cnt,head[1001],dep[1001];
vector<int> dfn;
void dfs(int x)//求欧拉序和深度
{
	dfn.push_back(x);
	for(int i=head[x];i;i=edge[i].next)
	{
		dep[edge[i].to]=dep[x]+1;
		dfs(edge[i].to);
		dfn.push_back(x);
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++)
	{
		int x;
		scanf("%d",&x);
		edge[i].to=i+1;
		edge[i].next=head[x];
		head[x]=i;
	}
	dfs(1);
	while(m--)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		int s,t;
		for(int i=0;i<dfn.size();i++)
			if(dfn[i]==x)
			{
				s=i;
				break;
			}
		for(int i=0;i<dfn.size();i++)
			if(dfn[i]==y)
			{
				t=i;
				break;
			}
		if(s>t)
			swap(s,t);
		int ans,minn=1e9;
		for(int i=s;i<=t;i++)
			if(dep[dfn[i]]<minn)
			{
				minn=dep[dfn[i]];
				ans=dfn[i];
			}
		cout<<ans<<endl;
	}
}
```


---

## 作者：meisr (赞：1)

lca模板题，没有倍增怎么能行呢？虽然倍增常数大不如树链剖分快，但倍增毕竟还是比树链剖分更基础一些QwQ
```cpp
#include<ctime>
#include<iostream>
#include<algorithm>
using namespace std;
int n,m,cnt,from[1001],head[1001],next[1001],to[1001],depth[1001],lca[1001][11];
inline void add(int x,int y){from[++cnt]=x,to[cnt]=y,next[cnt]=head[x],head[x]=cnt;}
void dfs(int u){
	for(int i=head[u];i;i=next[i])
		depth[to[i]]=depth[u]+1,dfs(to[i]);
	return;
}
inline int f(int x,int y){
	if(depth[x]<depth[y]) swap(x,y);
	for(int i=10;i>=0;i--)
		if(depth[lca[x][i]]>=depth[y]) x=lca[x][i];
	if(x==y) return x;
	for(int i=10;i>=0;i--)
		if(lca[x][i]!=lca[y][i]) x=lca[x][i],y=lca[y][i];
	return lca[x][0];
}
int main(){
	freopen("s.out","w",stdout);
	cin>>n>>m; 
	for(int i=2,x;i<=n;i++) cin>>x,add(x,i),lca[i][0]=x;
	lca[1][0]=0; 
	for(int i=1;i<=10;i++) 
		for(int j=1;j<=n;j++) 
			lca[j][i]=lca[lca[j][i-1]][i-1]; 
	depth[1]=1,dfs(1); 
	while(m--){ 
		int x,y;
		cin>>x>>y;
		int ans=f(x,y);
		cout<<ans<<endl;
	}
	return 0;
}
```
另外说一句，本代码经过防抄处理，请勿ctrl c+ ctrl v QwQ

---

## 作者：Gaode_Sean (赞：0)

这是一棵树。

简化后的题意是，给你每个子节点的父亲，让你求两个点 $x,y$ 的最近公共祖先。

考虑用倍增 lca 求解，时间复杂度 $O(n \log n)$ 。

## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,dp[1001][12],head[1001],ver[2001],nxt[2001],d[1001],i,j,t,tot;
queue<int> q;
void add(int x,int y)
{
	ver[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}
void bfs(int s)
{
	q.push(s);
	d[s]=1;
	while(!q.empty()){
		int x=q.front();
		q.pop();
		for(i=head[x];i;i=nxt[i]){
			int y=ver[i];
			if(d[y]) continue;
			d[y]=d[x]+1;
			dp[y][0]=x;
			for(j=1;j<=t;j++) dp[y][j]=dp[dp[y][j-1]][j-1];
			q.push(y);
		}
	} 
}
int lca(int x,int y)
{
	if(d[x]>d[y]) swap(x,y);
	for(i=t;i>=0;i--) if(d[dp[y][i]]>=d[x]) y=dp[y][i];
	if(x==y) return x;
	for(i=t;i>=0;i--) if(dp[x][i]!=dp[y][i]) x=dp[x][i],y=dp[y][i];
	return dp[x][0];
}
int main()
{
	cin>>n>>m;
    for(int i=2;i<=n;i++){
    	int x;
    	cin>>x;
    	add(x,i);
    	add(i,x);
	}
	t=(int)(log(n)/log(2))+1;
	bfs(1);
	while(m--){
		int x,y;
		scanf("%d%d",&x,&y);
		printf("%d\n",lca(x,y));
	}
	return 0; 
}
```

---

## 作者：zhy137036 (赞：0)

[P3019](/problem/P3019)

# 题意简述

- 给你一棵树中每个结点（除根）的父结点。
- $m$ 次询问，每次询问两结点的最近共同祖先（LCA）。

# LCA 的定义

LCA 即最近共同祖先，我们要先清楚它的定义。

题目中是这么说的：

>两个结点的路径上离根结点最近的结点。

也可以这么定义：

>两个结点共同的祖先结点中，离这两个结点最近的结点。

那么这道题就是 LCA 了。

# 暴力

很容易想到的步骤：

1. dfs 求出每个点的深度。
2. 将更深的点向上一步步走到和另一个点一样深的地方。
3. 两个点一起向上走，直到祖先。

复杂度 $O(nm)$，好像可以，但是[板子题](/problem/P3379)过不去，所以要优化。

# 倍增 LCA

倍增思想在 ST 表中也用到了。如果你会 ST 表，这个应该不是问题。

既然大部分时间都用在了向上爬的过程，那预处理出每个结点的所有祖先结点不就行了？然而预处理太慢，还会爆空间，所以放弃。

解决方法是只保存部分祖先，即 $2^x(x\ge0)$ 级祖先。也就是说，一次只能爬 $2^x$ 层。

定义 $f(i,j)$ 表示 $i$ 的 $2^j$ 级祖先。定义父结点为 $1$ 级祖先。

我知道你觉得这么做很别扭，看看哪里有问题：

## 预处理

如何快速求出 $f(i,j)$ 呢？

容易得到递推式：$f(i,j)=f(f(i,j-1),j-1)$。

意思是说，$i$ 的 $4$ 级祖先就是 $i$ 的 $2$ 级祖先的 $2$ 级祖先。

有点像 dp？没错，从小到大枚举 $j$，就能快速算出。

## 向上爬

不能一步步向上爬了，那该怎么爬？

刚才说过：一次只能爬 $2^x$ 层。

那比如要爬 $10$ 层，就可以先爬 $2$ 层，再爬 $8$ 层。

但问题是我们不知道要爬几层啊。

**从大往小**

先尝试爬 $2^{10}$ 层，发现不行；

再尝试爬 $2^9$ 层，还是不行；

……

再尝试爬 $2^3$ 层，发现可以。

再尝试爬 $2^2$ 层，还是不行。

再尝试爬 $2^1$ 层，又可以了。

再尝试爬 $2^0$ 层，还是不行。

结束。

遗憾的是，我们甚至不能快速判断这个点是不是 LCA，也叫不能快速判断能否向上爬 $2^x$。但是可以判断它们的 $2^x$ 级祖先是否相同，如果相同，无论是不是 LCA，一律禁止爬；如果不同，就可以。这样显然无法到达 LCA，但是可以到 LCA 的子节点。

# 代码

```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
int n,m,fa[1010][20],deep[1010];
//fa[i][j] 即上文的 f(i,j)，deep 即深度
vector<int>son[1010];//每个点的所有子结点
void dfs(int x){//用来标记深度
	for(int i=0;i<son[x].size();i++){
		deep[son[x][i]]=deep[x]+1;//标记深度
		dfs(son[x][i]);//继续搜索
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=2;i<=n;i++){
		int x;
		scanf("%d",&x);
		fa[i][0]=x;//父结点为2^0 级祖先
		son[x].push_back(i);
	}
	for(int i=1;i<20;i++)
		for(int j=1;j<=n;j++)
			fa[j][i]=fa[fa[j][i-1]][i-1];//倍增递推
	deep[1]=1;//根节点的深度为 1
	dfs(1);//标记深度
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		if(deep[x]>deep[y])
			swap(x,y);//这样 y 一定比 x 深
		for(int i=19;deep[x]<deep[y];i--)//从大到小枚举
			if(deep[fa[y][i]]>=deep[x])//深度不能比 x 小
				y=fa[y][i];//向上爬
		if(x==y){//这时下面的方法会错
			printf("%d\n",x);
			continue;
		}
		for(int i=19;x!=y&&i>=0;i--)
			if(fa[x][i]!=fa[y][i]){//不能相等
				x=fa[x][i];
				y=fa[y][i];
			}
		printf("%d\n",fa[x][0]);//这时 x 和 y 都是 LCA 的子结点
	}
	return 0;
}
```

---

## 作者：_•́へ•́╬_ (赞：0)

LCA模板

这题n,m这么小，当然要暴力
```cpp
#include<stdio.h>
#include<vector>
#define N 1001
int n,m,f[N],dep[N];std::vector<int>e[N];
void dfs(int i){for(register int j=0;j<e[i].size();++j){dep[e[i][j]]=dep[i]+1;dfs(e[i][j]);}}//预处理dep数组
main()
{
	scanf("%d%d",&n,&m);
	for(register int i=2;i<=n;++i)
	{
		scanf("%d",f+i);//输入
		e[f[i]].push_back(i);//再存一遍从父亲到孩子的边，方便dfs
	}
	dfs(1);//预处理每个节点的深度
	for(register int x,y;m--;)
	{
		scanf("%d%d",&x,&y);//输入
		if(dep[x]<dep[y])x^=y^=x^=y;//让x的深度更深
		for(;dep[x]>dep[y];x=f[x]);//跳到同一深度
		for(;x!=y;x=f[x],y=f[y]);//跳到同一节点
		printf("%d\n",x);//输出
	}
}/*n,m到20000就不能这么做了*/
```

---

## 作者：RainFestival (赞：0)

lca模板题！！！

默认你们都会倍增求lca，不会的~~自己百度一下~~，不知道朴素算法能不能过，~~还不是我懒没试过~~

~~蒟蒻的代码没有坑~~

下面上~~代码~~！！！

```pascal
const m1=10;
var
  aa:array[0..30] of int64;
  fa,b:array[0..1005,0..1005] of longint;
  l,d:array[0..1000005] of longint;
  i,j,n,m,s,x,y:longint;
procedure dfs(u:longint;v:longint);//预处理
var i:longint;
begin
  d[u]:=d[v]+1;
  fa[u][0]:=v;
  for i:=1 to m1 do
    fa[u][i]:=fa[fa[u][i-1]][i-1];
  for i:=1 to l[u] do
    if b[u][i]<>v then
      dfs(b[u][i],u);
end;
function lca(x,y:longint):longint;//求lca
var i,p,t:longint;
begin
  //writeln;
  //writeln(x,' ',y);
  if d[x]<d[y] then
    begin
      t:=x;
      x:=y;
      y:=t;
    end;
  //writeln(x,' ',y);
  p:=d[x]-d[y];
  //writeln(p);
  for i:=m1 downto 0 do
    if aa[i]<p then
      begin
        p:=p-aa[i];
        x:=fa[x][i];
      end;
  if x=y then exit(x);
  if p=1 then x:=fa[x][0];
  //writeln(x,' ',y);
  //writeln(p);
  //writeln('---',d[x],' ',d[y]);
  for i:=m1 downto 0 do
    if fa[x][i]<>fa[y][i] then
      begin
        x:=fa[x][i];
        y:=fa[y][i];
      end;
  //writeln(x,' ',y);
  if x=y then exit(x)
         else exit(fa[x][0]);
end;
begin
  aa[0]:=1;
  for i:=1 to m1 do
    aa[i]:=aa[i-1]*2;
  //for i:=0 to m1 do
    //write(aa[i],' ');
  //writeln;
  readln(n,m);
  for i:=2 to n do
    begin
      read(x);
      inc(l[x]);
      b[x][l[x]]:=i;
    end;
  for i:=1 to n do
    for j:=1 to m1 do
      fa[i][j]:=0;
  //for i:=1 to n do
    //if f[i]=0 then s:=i;
  s:=1;
  dfs(s,0);
  //writeln('a');
 // for i:=1 to n do
    //writeln(d[i]);
  //writeln;
  //for i:=1 to n do
    //begin
      ///write(i,':');
      ///for j:=0 to m1 do
        ///write(fa[i][j],' ');
     // writeln;
    //end;
  //for i:=1 to n do
    //begin
      //write(i,':');
      //for j:=1 to l[i] do
       // write(b[i][j],' ');
     // writeln;
   // end;
  for i:=1 to m do
    begin
      read(x,y);
      writeln(lca(x,y));
    end;

end.
























```
谢谢巨佬们的观赏！！！

---

## 作者：yybyyb (赞：0)

没人写题解。。。那我写一篇

这题完全就是LCA模板题呀。。。。

LCA求法太多了，我拿来练习一下树链剖分

虽然树链剖分的复杂度和倍增是一样的

个人觉得树链剖分更好写

而且似乎常数更小

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
#define MAX 2000
inline int read()
{
    register int x=0,t=1;
    register char ch=getchar();
    while(ch!='-'&&(ch<'0'||ch>'9'))ch=getchar();
    if(ch=='-'){t=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
    return x*t;
}
struct Line
{
    int v,next;
}e[MAX*2];
int h[MAX],hson[MAX],size[MAX],top[MAX],f[MAX],dep[MAX];
int N,M,cnt=1;
inline void Add(int u,int v)
{
    e[cnt]=(Line){v,h[u]};
    h[u]=cnt++;
}
void DFS1(int u,int ff)
{
    hson[u]=0;size[u]=1;f[u]=ff;dep[u]=dep[ff]+1;
    for(int i=h[u];i;i=e[i].next)
    {
        int v=e[i].v;
        DFS1(v,u);
        if(size[v]>size[hson[u]])hson[u]=v;
        size[u]+=size[v];
    }
}
void DFS2(int u,int tp)
{
    top[u]=tp;
    if(hson[u])DFS2(hson[u],tp);
    for(int i=h[u];i;i=e[i].next)
    {
        int v=e[i].v;
        if(v==hson[u])continue;
        DFS2(v,v);
    }
}
int Query(int x,int y)
{
    int tp1=top[x],tp2=top[y];
    while(tp1!=tp2)
    {
        if(dep[tp1]<dep[tp2])
        {
            swap(tp1,tp2);
            swap(x,y);
        }
        x=f[tp1];tp1=top[x];
    }
    if(dep[x]<dep[y])swap(x,y);
    return y;
}
int main()
{
    N=read();M=read();
    for(int i=2;i<=N;++i)
    {
        int a=read();Add(a,i);
    }
    DFS1(1,0);DFS2(1,1);
    while(M--)
    {
        int x=read(),y=read();
        printf("%d\n",Query(x,y));
    }
    return 0;
}

```

---

