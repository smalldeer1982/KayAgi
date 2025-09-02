# [POI 2005] DWU-Double-row

## 题目描述

有 $2n$ 个士兵站成两排，他们需要被重新排列，以保证每一排里没有同样高的士兵——这样我们就说，士兵们被合理地安排了位置。 每次操作可以交换两个在同一位置（但不在同一排）的士兵。你的任务是用最少的操作来确保士兵们被合理地安排了位置。 

例如：有 $18$ 个士兵站成两排，箭头标明了重新安排士兵位置的正确方式。
![](https://cdn.luogu.org/upload/pic/14829.png)

写一个这样的程序： 读入 $n$ 与士兵的身高，以及他们最初所站的位置，确保以最小的交换（站在同一位置的不同排的士兵）的次数来合理地安排士兵的位置，输出操作数。

## 样例 #1

### 输入

```
9
2 5 5 2 7 4 7 3 9
1 6 8 4 6 3 9 1 8```

### 输出

```
3```

# 题解

## 作者：Accoty_AM (赞：14)

~~看到楼上两位大佬的题解没有证明，于是我就说两句~~

## 写在前面

做到这题时我思考了良久，看完题解后又有一种奇怪的感觉，如果你也觉得这道题有一种玄乎的感觉，不妨看一下这篇题解

## 策略

如果两个相同的数在不在同一行，给两个数所在的列的编号连一条边权为0的边

如果两个相同的数在同一行，给两个数所在的列的编号连一条边权为1的边

给每个联通块的点黑白染色（1边连接的点颜色相反，0边连接的点颜色相同），答案每次加上每个联通块黑点和白点个数的最小值（联通块是什么，请往下看）

## 证明

### 数的性质
首先我们分析这个题给出的数的性质，发现两个相同数在同一行的话，必须把一个数交换下去，那我们不妨设每一列交换后状态为黑,交换前状态为白，显然一个列要么被交换了，要么没被交换。我们连1的边说明这两列一定不在同一个状态里，连0的边说明两列一定在同一个状态里。

### 联通快性质
首先，我们只给相同的数所在的列连边，考虑所有可能有贡献的边（有贡献指不是自环的边），最多n个相同的数，所以最多n条边。每一列有两个格子，所以每一列最多连两条边，于是，联通块的性质很显然了，要么是环，要么是链。

### 染色性质
首先，如果联通块是链，那黑白染色取最小色块是非常显然的，因为交换最小需要改变的状态是最优的且一定可行的

的我们考虑环，环上唯一存在的问题就是，是否会出现奇数个权值为1的边，使两点不能匹配

我们先考虑一组不需要交换的数列，例如

		 1  2  3  4  5
 		 5  1  2  3  4
这里面的数两两相连，构成了一个边权都为0的图，接着考虑发生冲突

		 1  2  3  3  4
	  	 4  1  2  5  5
我们知道每列最多连两条边，如果这一列发生冲突，则此列剩余能连的边只剩下一条，另一列冲突同理，此时发生冲突的行里可用点减少了两个，我们又知道，如果用0边连接两个列，需要每行各取一个点，所以我们想把这冲突的两列用奇数个1边连成环是不可能的。

### 所以，这样连边后，列之间一定能形成完美的状态匹配，根据状态匹配贪心取最小即可
## 证毕
          

---

## 作者：_J_C_ (赞：5)

楼上巨佬讲得太好了%%%%%orz

蒟蒻来加一些自己的理解。

首先对于有一些士兵，他们的在哪个队伍里其实是不相干的。

如下面的例子：（括号内为编号）

1(0) 2(1) 3(2)

1(3) 2(4) 3(5)

那么很显然，其实0与1，0与2，1与2等等等等之间怎么站是一点联系都没有、相互独立的。

而0和3，1和4，2和5是有关系的（它们永远站不到同一行）

那么对于任意数据，也可能能够分出很多个联通快，使得它们间互不相干。

那么对于每个联通块，我们都取最小的、能够使得联通块满足题意的值，加起来，就是答案了。

那么怎么求联通块内的最小值呢、、

借用楼上巨佬的话%%%

```cpp
1.若相同的两个数字在同一行，第i列和第j列，则第i列和第j列中一定恰有一列需要交换，于是在点i和点j间连一条权值为1的边

2.若相同的两个数字不在同一行，在第i列和第j列，则第i列和第j列中一定要么都需要交换要么都不需要交换，于是在点i和点j间连一条权值为0的边

只需要在新图上进行二染色，使得权值为1的边两侧染色不同，权值为0的边两侧染色相同
```

那么边权的意思就是：如果边权为1，那么这个边所连接的点不应该在同一队伍里，也就是不应该是同一颜色的。

否则边权为0，那么两个点应该是同一个颜色的。

额外的，如果两个士兵站在同一列，那么这两个士兵不应该（也不可能）站在同一行里，应当连一条边为1。

于是我们对每一个联通块进行BFS黑白染色，那么对于同一行，它们的士兵的0，1值应该是一一相反的（因为同一列的士兵间有边权为1的边）

任务就成了：在一个联通块里，将权值为0（或者1，同理）的士兵换到同一行，最少需要几步？

又因为上下两行的士兵的0，1值一一相反，所以如果上面全是0或1，下面的“颜色”也就“纯”了。

那么我们只需要考虑第一行里的0、1值哪个出现的次数较小，然后交换就好了。

具体来说，如果我们有如下两行权值：

0 1 0 1 1 0 0 0 0 1 0 0 1

1 0 1 0 0 1 1 1 1 0 1 1 0

第一行中的1出现次数比第一行中0出现次数少，所以我们选择将第一行全部换为0，那么交换次数即第一行中1的出现次数，为5。

那么这样子我们就解决了一个联通块，把所有联通块的解加起来就是最后的答案了。

【虽然最后的结论很简单，代码量也不大，但是思维难度还是挺大的（毕竟蒟蒻orz orz）】

```cpp
#include <cstdio>
#include <cstdlib>

#include <queue>

#define FOR_EDGE(i, pt) for (int i(iHead[pt]); i; i = all[i].next)//遍历属于这个点的所有边

class edge
{
public:
	int to, next, len;//len即边权
}all[1123456];

int iHead[112345];

int iEnd(2);

void add(int fr, int to, int len)
{
	all[iEnd].to = to;
	all[iEnd].len = len;
	all[iEnd].next = iHead[fr];
	iHead[fr] = iEnd++;
}

bool bColored[112345];//是否被染色
int color[112345];//染的颜色，值为0，1

int n;

inline int min(int a, int b) { return a < b ? a : b; }

int bfs(int st)
{
	int clr[2] = { 0, 0 };//第一行中被染成0，1颜色的点各有多少（计数）
	std::queue<int> que;
	que.push(st);
	bColored[st] = true;
	while (!que.empty())
	{
		int now(que.front());
		que.pop();
		if (now < n)//将点的位置限制在第一行
			++clr[color[now]];
		FOR_EDGE(i, now)
		{
			if (!bColored[all[i].to])//这个点不应该被染过色，否则就是搜索回去了
			{
				bColored[all[i].to] = true;
				color[all[i].to] = color[now] ^ all[i].len;
				que.push(all[i].to);
			}
		}
	}
	return min(clr[0], clr[1]);//返回较小值为联通块的解
}



int pos[112345];//哲学建图——pos[h]表示高度为h的士兵第一次出现的行数（为了避免初始化，行数选用1，2）
int rank[112345];//哲学建图——rank[h]表示高度为h的士兵第一次出现的编号

int main()
{
	scanf("%d", &n);
	for (int i(0); i != n; ++i)
	{
		int x;
		scanf("%d", &x);
		if (pos[x])
		{
			add(rank[x], i, 1);//读入并建图（建图这种东西……见仁见智吧）
			add(i, rank[x], 1);
		}
		else
		{
			pos[x] = 1;
			rank[x] = i;
		}
	}
	for (int i(0); i != n; ++i)
	{
		int x;
		scanf("%d", &x);
		if (pos[x])
		{
			add(rank[x], i, pos[x] == 2);//读入并建图（建图这种东西……见仁见智吧）
			add(i, rank[x], pos[x] == 2);
		}
		else
		{
			pos[x] = 2;
			rank[x] = i;
		}
	}
	for (int i(0); i != n; ++i)
	{
		add(i, n + i, 1);//隐含的建图条件：同一列的两个士兵有边且边权为1
		add(n + i, i, 1);
	}
	int ans(0);
	for (int i(0); i != n; ++i)
	{
		if (!bColored[i])//如果这个联通块内有一个点被染了色，那么整个联通块都是有色的，即已经加入答案了，就跳过
			ans += bfs(i);//答案加上这个联通块的解
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：oscar (赞：4)

【POI补全计划#14 POI2005 DWU】

先说题意

有两行人，每行n个，每人有身高，每次操作可以交换同一列的两人，使得最终两行人的身高分别互不相同，保证有解

问最少交换几次

补样例解释图片

![QAQ](http://oi.edu.pl/old/html/zadania/oi12/dwu.jpg)

以下是题解

--------------------------------题解分割线-------------------------------------

也算是思维难度比较简单的一题了

考虑要使得每行身高互不相同要满足什么条件

1.若相同的两个数字在同一行，第i列和第j列，则第i列和第j列中一定恰有一列需要交换，于是在点i和点j间连一条权值为1的边

2.若相同的两个数字不在同一行，在第i列和第j列，则第i列和第j列中一定要么都需要交换要么都不需要交换，于是在点i和点j间连一条权值为0的边

只需要在新图上进行二染色，使得权值为1的边两侧染色不同，权值为0的边两侧染色相同，取每个连通块中同色的较少部分加入答案

这种东西随便dfs一下就出来了

贴代码

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int pos[100010][2];
int n,tmp0;
struct edge
{
    int v,w;
    edge *next;
}*h[50010],pool[100010];
int top;
inline void addedge(int u,int v,int w)
{
    edge *tmp=&pool[top++];tmp->v=v;tmp->w=w;tmp->next=h[u];h[u]=tmp;
    edge *pmt=&pool[top++];pmt->v=u;pmt->w=w;pmt->next=h[v];h[v]=pmt;
}
int vis[50010],col[50010],cntc[2],cnt,ans;
void dfs(int u)
{
    vis[u]=1;
    cntc[col[u]]++;
    for(edge *tmp=h[u];tmp;tmp=tmp->next)
    {
        if(!vis[tmp->v])
        {
            col[tmp->v]=col[u]^tmp->w;
            dfs(tmp->v);
        }
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&tmp0);
        if(pos[tmp0][0])pos[tmp0][1]=i;
        else pos[tmp0][0]=i;
    }
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&tmp0);
        if(pos[tmp0][0])pos[tmp0][1]=-i;
        else pos[tmp0][0]=-i;
    }
    for(int i=1;i<=100000;i++)
    {
        if(pos[i][0]&&pos[i][1])
        {
            addedge(abs(pos[i][0]),abs(pos[i][1]),!((pos[i][0]>0)^(pos[i][1]>0)));
        }
    }
    for(int i=1;i<=n;i++)
    {
        if(!vis[i])
        {
            cntc[0]=cntc[1]=0;
            dfs(i);
            ans+=min(cntc[0],cntc[1]);
        }
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：CPPfive (赞：3)

## 题目分析
不难发现，同一列的两个人最多会被交换一次（交换两次等于没有交换），所以对于每一列，其实只有两种选择：换或者不换。

然后，为了满足要求，对于列与列之间需要符合一些条件，我们可以结合前面的例子来理解。

![qwq](https://t1.picb.cc/uploads/2022/01/16/fWpZCG.png)

我们发现，对于两个相同的数字，如果它们在同一行中，那么对于他们各自所在的列而言，这两列中必须一个换而另一个不换，例如图中的第一、二列，必须有一个换掉；如果它们不在同一行中，那么两列要么都不换，要么一起换，例如图中的第二、三列，要么不换，要么一起换。

如果我们把每一列当作一个结点的话，那么对于任意两列，如果它们之间存在上述关系中的某一种，就把这两列所对应的结点连边。最终得到的图形一定是一个包含若干个连通块的无向图。对于例子里的情况，我们就可以得到下面的图：

![qwq](https://t1.picb.cc/uploads/2022/01/16/fWpwNy.png)

这些连通块之间互相不影响，因此我们单独考虑一个连通块的情况。为了说明方便，我们把一个结点换或者不换对应为这个点是黑色和白色，那么在一个连通块中，任意两个相邻的点之间都有一个关系（要么颜色不同，要么相同），所以只要确定一个点的颜色，那么就可以确定连通块中的所有点的情况。以上面的图中的最大的连通块为例，假设 $1$ 号结点是黑色，上色情况如图所示：

![qwq](https://t1.picb.cc/uploads/2022/01/16/fWpIIc.png)

由于一个结点要么染黑要么染白，所以一个连通块只有两种染色方案，我们只要在两种方案中选择白色结点（即不换的结点）较多的那一个即可。对于上面的情况，另一个染色方案如下图所示，我们可以发现第一种方案更好。

![qwq](https://t1.picb.cc/uploads/2022/01/16/fWpiOK.png)

对于每一个连通块，都可以用上面的方法得到最少的染黑个数（即最少的操作次数），因此将每个连通块中的最少的黑色结点个数相加即可得到答案。

## Code
```cpp
//洛谷P3430 

#include <bits/stdc++.h>
using namespace std;
const int MAXN=50050;
int N,h[MAXN],to[MAXN<<1],nxt[MAXN<<1],tp[MAXN<<1],tot;
int vis1[MAXN<<1],vis2[MAXN<<1];
int type[MAXN],sum[MAXN];
int ans;
inline void add(int u,int v,int t){
	to[++tot]=v,nxt[tot]=h[u],tp[tot]=t,h[u]=tot;
}

pair<int,int> get(int x){
	if(vis2[x]) return make_pair(2,vis2[x]);
	else if(vis1[x]) return make_pair(1,vis1[x]);
	else return make_pair(0,0);
}
int dfs(int x,int fa){
	sum[x]=1;
	int res=type[x]==0;
	for(int i=h[x];i;i=nxt[i]){
		if(sum[to[i]]) continue;
		type[to[i]]=type[x]^tp[i];
		res+=dfs(to[i],x);sum[x]+=sum[to[i]];
	}
	return res;
}
int sol(int x){
	type[x]=1;
	int now=dfs(x,x);
	return min(now,sum[x]-now);
}

int main()
{
	scanf("%d",&N);
	for(int i=1;i<=N;++i){
		int d;scanf("%d",&d);
		pair<int,int> temp=get(d);
		if(temp.first){
			add(i,temp.second,1),add(temp.second,i,1);
		}
		vis1[d]=i;
	}
	for(int i=1;i<=N;++i){
		int d;scanf("%d",&d);
		pair<int,int> temp=get(d);
		if(temp.first==2){
			add(i,temp.second,1),add(temp.second,i,1);
		}
		else if(temp.first==1){
			add(i,temp.second,0),add(temp.second,i,0);
		}
		vis2[d]=i;
	}
	for(int i=1;i<=N;++i){
		if(!sum[i]) ans+=sol(i);
	}
	printf("%d\n",ans);
	
	return 0;
}
```


---

## 作者：血色黄昏 (赞：3)

很好的一道染色题，思维难度感觉不到蓝，代码难度橙左右。

我们考虑相同的两个数，如果在同一行，就将他们列的编号作为顶点的边连边权为 $1$ 的边，不然连边权 $0$ 的边。

为什么要连 $1$ 边？因为如果两个数在同一行肯定有一列是要被翻转的，连 $0$ 边就说明不需要被动，对每一列的操作显然最多一次，不然和操作次数模 $2$ 时的状态是一样的，显然后者操作更少。

然后进行染色，边权为 $0$ 的两点颜色相同，为 $1$ 的染另一种颜色，每个连通块是独立的， 里面的最小翻转次数就是数量少的那种颜色个数，因为两种操作显然都能使序列符合答案，那么代码就很好写了。

我代码写的建图有点奇怪，应该有更好的理解方法，大家自行理解一下即可，代码难度并不高。


```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	register int x=0;register char ch=getchar();
	while(ch<48)ch=getchar();
	while(ch>=48)x=x*10+(ch^48),ch=getchar();
	return x;
}
struct node{
	int v, w;
};
int n, a[100010], b[100010], color[100010], pos[100010], c1, c2, ans = 0;
vector<node>l[100010];
void dfs(int u, int c)
{
	color[u] = c;//marked 
	if(c == 1)c1 ++;
	if(c == 2)c2 ++;
	for(int i = 0;i < l[u].size();i ++)
	{
		int v = l[u][i].v, w = l[u][i].w;
		if(color[v])continue;
		if(c + w <= 2)dfs(v, c + w);//注意我写的颜色是1和2，是否超过2要分类讨论 
		else dfs(v, 1);//继续染色 
	}
}
int main()
{
    n = read();
    for(int i = 1;i <= n;i ++)//读入然后建图 
    {
    	a[i] = read();
    	if(! pos[a[i]])pos[a[i]] = i;
    	else
    	{
    		l[pos[a[i]]].push_back(node{i, 1});
    		l[i].push_back(node{pos[a[i]], 1});
    		pos[a[i]] = 0x3f3f3f3f;
		}
	}
	for(int i = 1;i <= n;i ++)
    {
    	b[i] = read();
    	if(pos[b[i]] != 0x3f3f3f3f and pos[b[i]])
    	{
    		l[pos[b[i]]].push_back(node{i, 0});
    		l[i].push_back(node{pos[b[i]], 0});
    		pos[b[i]] = 0x3f3f3f3f;
		}
	}
	memset(pos, 0, sizeof(pos));
	for(int i = 1;i <= n;i ++)
    {
    	if(! pos[b[i]])pos[b[i]] = i;
    	else
    	{
    		l[pos[b[i]]].push_back(node{i, 1});
    		l[i].push_back(node{pos[b[i]], 1});
    		pos[b[i]] = 0x3f3f3f3f;
		}
	}//将同一行连1，不然连0 
	for(int i = 1;i <= n;i ++)
	{
		if(! color[i])//如果这个连通块没访问过访问 
		{
			c1 = c2 = 0;
			dfs(i, 1);
			ans += min(c1, c2);//取小的那个 
		}
	}
	cout<<ans<<endl;
    return 0;
}
```


---

## 作者：iCostalymh (赞：1)

[原文链接](https://www.cnblogs.com/voah/p/gpbt-2.html)

## [P3430 [POI2005] DWU-Double-row](https://www.luogu.com.cn/problem/P3430)

很好的一道染色题。

给两行长度为 $n$ 的序列，**每一次可以将同一列的两个数互换位置**，最后想让每一行不存在相同的两个数。

我们可以把两个相同的数所在的列连边。显然我们不可以把两个相同的数留在同一列，要交换，所以设在同一行的两列边权为 $1$，表示需要交换，设不在同一行的边权为 $0$，表示不需要交换，正确性显然，比如说：

```plain
1 2 5 6 6
2 3 3 1 5
```

给出这样一个抽象玩意，自己手建个图会发现（或者瞪眼法）肯定要把 `3 3` 和 `6 6`换到不同的行，显然有 $w(1,4)=w(1,2)=w(3,5)=0$，$w(2,3)=w(4,5)=1$（其实一个 $w$ 表示一个双向边）。如果交换第三列，那么就有 $w(2,3)=0$，$w(3,5)=1$，然后就可以交换第五列，使每一行不存在两个相同的数了。

啊这感性理解一下吧，感觉挺好理解的。

然后就是给每个点染色，设 $\operatorname{col}_ u=0$，令 $\operatorname{col}_ v=\operatorname{col}_ u\oplus w(u,v)$。要知道这个图可能出现多个连通块，最后的答案就是每个连通块的两个颜色取 $\min$ 再求和。

证明的话，画个图就知道了。

有个坑点，就是有的数可能只出现一次，从这个数出发不能和其他的列连边，所以建图的时候要注意。（为什么上面说 **连通块** 而不说 **环** 在这里也能解释了）


---

## 作者：快斗游鹿 (赞：1)

## 思路

首先，每一列最多交换一次，因为交换两次相当于没换。

那么我们考虑什么时候需要交换。如果两个数在不同行，那么两个数所在的列自然是能不交换就不交换。反之，最少也要交换一次。

直接贪心好像不太行。考虑建图然后染色。我们把不在同一行的数所在的两列连一条边权为 $0$ 的边，把在同一行的数所在的两列连一条边权为 $1$ 的边。然后染色，使边权为 $0$ 的边两端颜色相同，边权为 $1$ 的边两端颜色不同。最后统计两种颜色个数，取更小的加到答案中即可。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
const int N=4e5+5;
struct edge{
	int to,nxt,w;
}e[N<<2];
int n,a[N],fid[N],lid[N],lis[N],tot,flag[N][2],cnt,head[N],col[N],ans,suma,sumb;
int lst[N],pos[N];
bool vis[N];
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
void add(int u,int v,int w){
	e[++cnt].to=v;
	e[cnt].nxt=head[u];
	e[cnt].w=w;
	head[u]=cnt;
}
void addedge(int u,int v,int w){
	add(u,v,w);add(v,u,w);
}
void dfs(int u){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!vis[v]){
			vis[v]=1;
			if(e[i].w==0){
				col[v]=col[u];
				if(col[v]==1)suma++;
				else sumb++;
				dfs(v);
			}
			else{
				if(col[u]==1)col[v]=2,sumb++;
				else col[v]=1,suma++;
				dfs(v);
			}
		}
	}
}
int main(){
	freopen("std.in","r",stdin);
	n=read();
	for(int i=1;i<=n;i++){
		int ttt;ttt=read();
		if(lst[ttt]){
			addedge(lst[ttt],i,1);
		}
		else lst[ttt]=i,pos[ttt]=1;
	}
	for(int i=1;i<=n;i++){
		int ttt;ttt=read();
		if(lst[ttt]){
			if(pos[ttt]==1){
				addedge(lst[ttt],i,0);
			}
			else addedge(lst[ttt],i,1);
		}
		else lst[ttt]=i,pos[ttt]=2;
	}
	for(int i=1;i<=n;i++){
		suma=1,sumb=0;
		if(!vis[i])vis[i]=1,col[i]=1,dfs(i),ans+=min(suma,sumb);//,cout<<suma<<" "<<sumb<<endl;
	}
	cout<<ans;
	return 0;
}


```


---

## 作者：Tari (赞：1)

本质上来看，我们设每列最终的状态为 $f[i]=0/1$，表示 不交换/上下交换 ，我们相当于给了一些 $f[i]$ 之间的关系：  
$f[i]==f[j]$ 则 $i,j$ 之间连 $0$ 边；  
$f[i]!=f[j]$ 则 $i,j$ 之间连 $1$ 边。  

根据以上结论，我们将 在同一行的相同的两个数所在的列连 $1$ 边，表示两列的状态最终是不同的；不在同一行的两个相同的数之间连 $0$ 边，表示两列最后的状态是相同的。  

然后遍历整张图的每个连通块，进行染色。每个连通块的答案即 $\min($黑点数目$,$白点数目$)$，因为我们可以选择翻转黑点，也可以翻转白点 。
最终的答案为每个连通块的答案之和，因为连通块之间没有影响。

代码：
```cpp
#include <bits/stdc++.h>
#define R register int
using namespace std;
namespace Luitaryi {
inline int g() {
    R x = 0, f = 1;
    register char s;
    while (!isdigit(s = getchar())) f = s == '-' ? -1 : f;
    do
        x = x * 10 + (s ^ 48);
    while (isdigit(s = getchar()));
    return x * f;
}
const int N = 50010;
int n, m, cnt, ans, t1, t2, a[N], b[N], v1[N << 1], v2[N << 1];
int vr[N << 1], nxt[N << 1], fir[N << 1], w[N << 1], c[N];
inline void add(int u, int v, int ww) {
    vr[++cnt] = v, nxt[cnt] = fir[u], fir[u] = cnt, w[cnt] = ww;
    vr[++cnt] = u, nxt[cnt] = fir[v], fir[v] = cnt, w[cnt] = ww;
}
inline void dfs(int u, int C) {
    c[u] = C;
    t1 += C, t2 += (C ^ 1);
    for (R i = fir[u]; i; i = nxt[i]) {
        R v = vr[i];
        if (~c[v])
            continue;
        dfs(v, C ^ w[i]);
    }
}
inline void main() {
    n = g();
    memset(c, 0xff, sizeof c);
    for (R i = 1; i <= n; ++i) {
        a[i] = g();
        if (v1[a[i]])
            add(v1[a[i]], i, 1);
        v1[a[i]] = i;
    }
    for (R i = 1; i <= n; ++i) {
        b[i] = g();
        if (v1[b[i]])
            add(v1[b[i]], i, 0);
        if (v2[b[i]])
            add(v2[b[i]], i, 1);
        v2[b[i]] = i;
    }
    for (R i = 1; i <= n; ++i)
        if (c[i] == -1)
            t1 = 0, t2 = 0, dfs(i, 0), ans += min(t1, t2);
    printf("%d\n", ans);
}
}  // namespace Luitaryi
signed main() {
    Luitaryi::main();
    return 0;
}
```

2019.11.11

---

## 作者：Phrvth (赞：0)

## 题目简化

有 $2n$ 个数要长成两排，每一次操作都可以交换每列两个数，保证每个数最多出现两次，求最小操作数能够使每一列都没有相同的数

## 题目分析

这里写一下我的思路历程：

因为每个数最多出现两次，所以我把第一行搞定第二行就肯定可行，问题就变成了怎么把第一行调回来

这种有关系的题考虑连边，一开始想的 2-sat，也就是一个点有两种状态，一种是在第一行，一种是在第二行，但是这样会把同一列的另外一个数给忽略了，不好，所以这两个数应该是一个整体，也就是**每一列是一个整体**

剩下的就是考虑对每一列进行连边，具体的：

+ 若两个相同的数在同一列，那么将这两列连一条权值为 $1$ 的边，表示必须要交换
+ 若两个相同的数在不同列，那么将这两列连一条权值为 $0$ 的边，表示必须不能交换

发现**交换**这个名词太抽象了，我们可以把这个东西具体点

可以发现一个列就只有两种状态，也就是**交换**和**不交换**，分别对应**黑**和**白**，那么如果连了 $1$ 则表示两边颜色不一样，$0$ 的话就两边颜色一样

可以发现原图是若干个联通块，那么单独考虑一个联通块的话，那么就是一个块被分成了两部分，染黑的要操作，但是每个块都能染黑染白，所以取最小值，最后把每个联通快加起来即可，即
$$
ans=\sum \min(sum_{white},sum_{black})
$$
代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 5e4 + 7, MAXM = 1e5 + 7;

int n, x, Vis[MAXM][2], S[MAXM][2];

typedef pair < int, int > Pair;
#define fi first
#define se second
#define New(x, y) make_pair(x, y)

vector < Pair > G[MAXN];

void add(int from, int to, int v) { G[from].push_back(New(to, v)); }

int V[MAXN], Col[MAXN], tot, ans;

int dfs(int u) {
	tot ++; V[u] = 1;
	int res = Col[u] == 0;
	for (auto v : G[u]) {
		if (!V[v.fi]) {
			Col[v.fi] = Col[u] ^ v.se;
			res += dfs(v.fi);
		}
	}
	return res;
}

signed main () {
	ios :: sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	
	cin >> n;
	for (int i = 1, x; i <= n; i ++) {
		cin >> x;
		if (Vis[x][0]) Vis[x][1] = i, add(Vis[x][0], i, 1), add(i, Vis[x][0], 1);
		else Vis[x][0] = i;
	}
	for (int i = 1, x; i <= n; i ++) {
		cin >> x;
		if (Vis[x][0]) Vis[x][1] = i, add(Vis[x][0], i, 0), add(i, Vis[x][0], 0);
		else if (S[x][0]) S[x][1] = i, add(S[x][0], i, 1), add(i, S[x][0], 1);
		else S[x][0] = i;
	}
	for (int i = 1; i <= n; i ++) {
		if (!V[i]) {
			int sum = 0; tot = 0;
			sum = dfs(i);
			ans += min(sum, tot - sum);
		}
	}
	cout << ans << '\n';
	return 0;
}
```



---

## 作者：TernaryTree (赞：0)

题意：给定长为 $n$ 的序列 $a,b$，你可以选定 $m$ 个位置 $p_i$ 交换 $a_{p_i},b_{p_i}$，使得 $a$ 中不存在相同元素，$b$ 中同理。最小化 $m$。

---

看到相等，不等，二元运算。好啊，非常显然，**建图**！问题来了，怎么建图？

什么是点？把同一个位置上的 $a_i,b_i$ 看成一个点。

什么是边？考虑如果两个点的位置有相同元素则建边。怎么区分同位与异位？$0/1$ 边权！

> 也就是说，如果 $a_u=a_v$ 或 $b_u=b_v$ 则 $u,v$ 建一条边权为 $1$ 的边，否则边权为 $0$。

至此建图完成。

---

建完图了，现在怎么做？

**考虑一次操作，图有什么变化。**

对一个位置 $u$ 的 $a_u,b_u$ 交换，那么与其相连的同位变成异位，异位变成同位，也就是与其相邻的所有边边权取反。

既然最终全都不同，那么最终状态就是边权全部为 $0$。

~~瞎口胡了一下，到这里好像就可以高消做了，然而我不会也不知道对不对。/kk~~

---

于是这里有一个套路化的想法就是对于每个点**黑白染色**，钦定一个连通块上任意一个点为白色（$c_i=0$）。

- 若 $u$ 到 $v$ 的边权为 $1$ 则 $c_u\neq c_v$。

- 若 $u$ 到 $v$ 的边权为 $0$ 则 $c_u= c_v$。

这样我们对所有白色结点操作一遍，或者对所有黑色结点操作一遍都可以达到边权全部为 $0$ 的效果。

正确性证明：对于一条边，如果边权为 $1$ 那么其两个端点一定一个为 $0$ 一个为 $1$，这条边会被操作一次变成 $0$。如果边权为 $0$，则会被这条边要么不被操作要么被取反两次，还是 $0$。

所以一个连通块边权为 $0$ 的最小代价为白色结点数量与黑色结点数量的较小者。

跑 dfs 即可。

---

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e5 + 10;
const int maxv = 1e6 + 10;

struct edge { int to, next, w; };

int n, ans;
int a[maxn], b[maxn];
vector<int> p[maxv];
int head[maxn];
edge e[maxn << 2];
int cnt;

void add_edge(int u, int v, int w) {
    e[++cnt] = {v, head[u], w};
    head[u] = cnt;
}

int vis[maxn], c[2];

void dfs(int u, int f) {
    ++c[f];
    vis[u] = true;
    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].to, w = e[i].w;
        if (!vis[v]) dfs(v, f ^ w);
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    for (int i = 1; i <= n; i++) if (a[i] != b[i]) p[a[i]].push_back(i), p[b[i]].push_back(i);
    for (int i = 1; i < maxv; i++) {
        if (p[i].size() == 2) {
            int u = p[i][0], v = p[i][1], f = (a[u] == a[v] || b[u] == b[v]);
            add_edge(u, v, f), add_edge(v, u, f);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            c[0] = c[1] = 0;
            dfs(i, 0);
            ans += min(c[0], c[1]);
        }
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：aSunnyDay (赞：0)

@管理员大大：这题我没有写公式，为什么打回原因是公式没写LaTeX

这题主要是有一些限制

通过手算，我们会发现，如果某两列存在相同的数的话，那么这两列交换会有限制

具体地来说
```
1 2
3 1
```
这种情况,两列要么都不换位置,要么就都换位置。
```
1 1
2 3
```
这种情况，两列一定会有一列会换位置

我们把上面这种关系联系起来，会构成一个**不连通**的图。

但是**不连通**这件事情可以改变成:依次枚举i所在的图，如果i没有访问过,那么就把i所在的图扫一遍。

值得一提的是，一个连通的约束图(在这题里)，只要有一个节点是**已知**的(已知是否更改)，那么其他节点是否会更改就**一定**知道。

所以我们对于一张图,可以先**随机**选一个节点，枚举他是否改变。再递归下去，就可以**唯一确定一张图**，这个时候再把换的数量统计一下即可

比较完整了，我放下代码
```cpp
#include<bits/stdc++.h>
#define N 50009
using namespace std;
typedef long long ll;
ll n,f[N][2],vis[N][2],cnt=0,ans=0;
vector<ll> to[N];
vector<bool> w[N];// w means different or not
struct edge{bool type;ll id,x;}es[2*N];
bool cmp(const edge&a,const edge&b){return a.x<b.x;}
ll F(ll x,ll fa,bool now){
	vis[x][now]=1,f[x][now]=now;
	for(ll i=0,v,we;i<to[x].size();++i)
		if(!vis[v=to[x][i]][we=now^w[x][i]])
			f[x][now]+=F(v,x,we);
	return f[x][now];
}
int main(){
	cin>>n;
	for(ll i=1;i<=n;++i){
		ll a;
		cin>>a,es[++cnt]=(edge){0,i,a};
	}
	for(ll i=1;i<=n;++i){ 
		ll b;
		cin>>b,es[++cnt]=(edge){1,i,b};
	}
	sort(es+1,es+cnt+1,cmp);
	for(ll i=2;i<=cnt;++i)
		if(es[i].x==es[i-1].x){
			edge now=es[i],pre=es[i-1];
			to[now.id].push_back(pre.id);w[now.id].push_back(!(now.type^pre.type));
			to[pre.id].push_back(now.id);w[pre.id].push_back(!(now.type^pre.type));
		}
	for(ll i=1;i<=n;++i)
		if(!vis[i][0])
			ans+=min(F(i,0,0),F(i,0,1));
	cout<<ans;
	return 0;
}
```


---

