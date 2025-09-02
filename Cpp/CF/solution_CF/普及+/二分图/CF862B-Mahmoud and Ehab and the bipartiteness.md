# Mahmoud and Ehab and the bipartiteness

## 题目描述

Mahmoud and Ehab continue their adventures! As everybody in the evil land knows, Dr. Evil likes bipartite graphs, especially trees.

A tree is a connected acyclic graph. A bipartite graph is a graph, whose vertices can be partitioned into $ 2 $ sets in such a way, that for each edge $ (u,v) $ that belongs to the graph, $ u $ and $ v $ belong to different sets. You can find more formal definitions of a tree and a bipartite graph in the notes section below.

Dr. Evil gave Mahmoud and Ehab a tree consisting of $ n $ nodes and asked them to add edges to it in such a way, that the graph is still bipartite. Besides, after adding these edges the graph should be simple (doesn't contain loops or multiple edges). What is the maximum number of edges they can add?

A loop is an edge, which connects a node with itself. Graph doesn't contain multiple edges when for each pair of nodes there is no more than one edge between them. A cycle and a loop aren't the same .

## 说明/提示

Tree definition: <a>https://en.wikipedia.org/wiki/Tree\_(graph\_theory)</a>

Bipartite graph definition: [https://en.wikipedia.org/wiki/Bipartite\_graph](https://en.wikipedia.org/wiki/Bipartite_graph)

In the first test case the only edge that can be added in such a way, that graph won't contain loops or multiple edges is $ (2,3) $ , but adding this edge will make the graph non-bipartite so the answer is 0.

In the second test case Mahmoud and Ehab can add edges $ (1,4) $ and $ (2,5) $ .

## 样例 #1

### 输入

```
3
1 2
1 3
```

### 输出

```
0
```

## 样例 #2

### 输入

```
5
1 2
2 3
3 4
4 5
```

### 输出

```
2
```

# 题解

## 作者：Hamer_sans (赞：11)

# CF862B的题解

### 题目大意

给定 $n$ 个点，输入 $n-1$ 条边，求如果这张图要构成二分图，最少要加多少条边。

### 什么是二分图？

二分图就是一种特殊的图，这张图中的节点可以分为两个集合，并且在同一集合内的节点没有边，也就是说要想从一个节点走到另一个在同一集合的节点，走的边的数量是偶数，如图这就是一张二分图，$t_{1}$，$t_{2}$，$t_{3}$，$t_{4}$ 属于一个集合，并且在这个集合内的节点之间都没有边。

![](https://cdn.luogu.com.cn/upload/image_hosting/6lz7q52k.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

### 思路与分析

好了，说完什么事二分图了，那就来讲讲思路。具体思路就是把这个图当成一张二分图用染色法把两个节点的集合分开，我们用 $cnt_{1}$ 表示集合 $1$ 节点的数量，$cnt_{2}$ 表示集合 $2$ 节点的数量，那么边的数量就为 $cnt_{1} * cnt_{2}$，所以我们求的答案就是构成二分图最少需要的边的数量减去题目中已给出的边的数量，也就是 $cnt_{1} * cnt_{2} - (n - 1)$。

注意事项，记住一定要开 `long long` ，不然会炸，俗话说的好啊，十年 oi 一场空，不开 `long long` ......

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long // 一定要开 long long
inline long long read(){ // 快读优化
	int sum=0,h=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') h=-1;ch=getchar();}
	while(isdigit(ch)) sum=sum*10+ch-'0',ch=getchar();
	return sum*h;
}
const int N=2e5+5; // 因为要建双向边，所以空间要开两倍
int color[N];
int n;
int cnt[3]; // 储存两个集合的节点数量
int ver[N],head[N],ne[N],tot;
void add(int x,int y){ // 邻接表储存
	ver[++tot]=y;
	ne[tot]=head[x];
	head[x]=tot;
	return;
}
void dfs(int x,int pos){ // 染色法区分节点
	color[x]=pos;
	++cnt[pos];
	for(register int i=head[x];i;i=ne[i]){
		int y=ver[i];
		if(!color[y]) dfs(y,3-pos);
	}
	return;
}
signed main(){
	n=read();
	for(register int i=1;i<n;++i){
		int x,y;
		x=read(),y=read();
		add(x,y);
		add(y,x);
	}
	dfs(1,1);
	printf("%lld",cnt[1]*cnt[2]-n+1);
	return 0;
}
```
蒟蒻写题解不易，求点赞。

---

## 作者：SuperJvRuo (赞：5)

标题就告诉我们，这是一道二分图。所以先dfs一遍进行二分图染色。

![](https://cdn.luogu.com.cn/upload/pic/14831.png)

连接所有的黑白点对需要$cnt[black]*cnt[white]$条边，而树上共有$n-1$条边，因此答案为：

$$cnt[black]*cnt[white]-n+1$$

35行无压行AC代码
```
#include<cstdio>
struct Edge
{
	int to,next;
}edge[200005];
int first[100005],size;
void AddEdge(int u,int v)
{
	edge[++size]=(Edge){v,first[u]};
	first[u]=size;
}
int color[100005];
long long cnt[3];
void dfs(int point,int c)
{
	color[point]=c;
	++cnt[c];
	for(int i=first[point];i;i=edge[i].next)
		if(!color[edge[i].to])
			dfs(edge[i].to,c==1?2:1);
}
int main()
{
	int n,u,v;
	scanf("%d",&n);
	for(int i=1;i<n;++i)
	{
		scanf("%d%d",&u,&v);
		AddEdge(u,v);
		AddEdge(v,u);
	}
	dfs(1,1);
	printf("%lld",cnt[1]*cnt[2]-n+1);
	return 0;
}
```

---

## 作者：轻绘 (赞：2)

**是一道二分图模板**

# 概念
[二分图](https://baike.baidu.com/item/%E4%BA%8C%E5%88%86%E5%9B%BE/9089095?fr=aladdin)

但是本题的二分图要求是 [完全二分图](https://baike.baidu.com/item/%E5%AE%8C%E5%85%A8%E4%BA%8C%E5%88%86%E5%9B%BE)

就是要将一张图中的所有点划分成两个点集，并且同个点集中的点之间互不相连，而任意一个点与另外的一个子集中所有点都要有连边。

# 思路

算出现在的二分图有几条边，再算出一共需要几条边。

减一减，便是要加的边数。

# 实现

用 $dfs$ 进行遍历，分别数出两个点集中点的个数。

将第一个点放入 $A$ 点集中，根据二分图性质，所有与该点相连的点都放入 $B$ 点集中，以此类推，将所有点分好。

设 $A$ 中有 $a$ 个点 那么 $B$ 中一定是 $n-a$ 个点（共有 $n$ 个点）。

总边数为： $ a*(n-a)$

原有边数： $ n-1 $

答案即为： $ a*(n-a)-n+1 $

# 代码

```
#include<bits/stdc++.h>
#define int long long
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')	f=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar(); 
	}
	return x*f;
}
int h[200000],nex[200000],v[200000],tot;
inline void add(int x,int y){
	nex[++tot]=h[x];
	h[x]=tot;
	v[tot]=y;
}
using namespace std;
int n,ans; 
bool used[200000];//记录第i个点放入哪个集当中
inline void dfs(int now,int fa){
	for(int i=h[now];i;i=nex[i]){
		if(v[i]==fa)	continue;
		used[v[i]]=!used[now];//相互有连边的点在不同点集中
		dfs(v[i],now);
	}
}
signed main(){
	n=read();
	for(int i=1;i<=n-1;++i){
		int x=read(),y=read();
		add(x,y),add(y,x);
	}
	used[1]=1;
	dfs(1,1);
	for(int i=1;i<=n;++i)
		if(used[i]==1)	ans++;
	printf("%lld",ans*(n-ans)-n+1);
	return 0;
} 
```


---

## 作者：Edmundino (赞：1)

毫无疑问，这是一道考图论的题目

首先我们来分析一下题目

题目说：给的图一定是一棵树（也就是给你一个二分图）

树来按照二分图来分了话，是可以分为两部分

即奇数层为一部分，计点数为a，偶数层为另一部分，计点数为b

那么此时二分图最多边便为那两个部分的点一一对应，共有a*b个边

原来树是有（n-1）条边

所以最多就可以添加ab-（n-1）=ab-n+1条边

其实题目就让你求给出的树可以分为多少层

所以就用dfs遍历树就可以啦！

最后送上AC代码
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<iomanip>
#include<cmath>
#include<vector>

using namespace std;

const int N=100050;

int n,father[N]={-1},q[N],g;

long long sa,sb;

vector<int> z[N];

void dfs(int s,int d,int e)
{
   if(e==1)
   {
   	sa++;
   }
   else
   {
   	 sb++;
   }
   for(int i=0;i<z[d].size();i++)
   {
   	if(s==z[d][i]) continue;
   	dfs(d,z[d][i],1-e);
   }
}

int main()
{
	cin>>n;
	for(int i=1;i<=n-1;i++)
	{
		int a,b;
		cin>>a>>b;
		father[b]=a;
		z[a].push_back(b);
		z[b].push_back(a);
	}
	dfs(0,1,0);
	cout<<sa*sb-n+1;
	return 0;
}
```


---

## 作者：partychicken (赞：1)

**楼下大佬dfs，我来一发bfs**

这道题很明显的二分图染色，然后 _black*white-n+1_

附上代码（二分图部分是从封锁阳光大学copy的，有冗余部分请dalao们原谅）

```
#include<iostream>
#include<cstring>
#include<vector>
#include<queue>

#define int long long

using namespace std;

vector <int>  edge[1000010];
queue <int> que;
int vis[1000010],ans[2],col[1000010];
int n,m,ansn,aa,bb,flag;

void bfs(int x)
{
    while(!que.empty())
    {
        int tmp=que.front();
        que.pop();
        vis[tmp]=1;
        for(int i=0;i<edge[tmp].size();i++)
        {
            int nowp=edge[tmp][i];
            if(col[nowp]==col[tmp]) 
            {
                ans[0]=-1;
                ans[1]=-1;
                return;
            }  
            if(!vis[nowp])
            {
                que.push(nowp);
                col[nowp]=(col[tmp]+1)%2;
                ans[col[nowp]]++;
            }
        }
    }
}

void scan()
{
    cin>>n;
    for(int i=1;i<n;i++)
    {
        cin>>aa>>bb;
        edge[aa].push_back(bb);
        edge[bb].push_back(aa);
    }
    memset(col,-1,sizeof(col));
}

void solve()
{
    for(int i=1;i<=n;i++)
    {
        if(vis[i]!=1)  
        {
            ans[0]=1;
            ans[1]=0;
            col[i]=0;
            que.push(i);
            bfs(i);
            if(ans[0]==-1)
            {
                break;
            }
            ansn+=ans[0]*ans[1]-n+1;
        }
    }
    cout<<ansn;
}

main()
{
    scan();
    solve();
}
```


---

## 作者：_Revenge_ (赞：0)

### 题目简化和分析：

这是一道较为经典的二分图染色题。    

[二分图的基本概念](https://baike.baidu.com/item/%E4%BA%8C%E5%88%86%E5%9B%BE/9089095?fr=aladdin)

但这题让我们求得是完全二分图。  

[什么是完全二分图](https://baike.baidu.com/item/%E5%AE%8C%E5%85%A8%E4%BA%8C%E5%88%86%E5%9B%BE/10074098?fr=aladdin)

$cnt_{1}$ 表示染成颜色种类为 $1$ 的个数。   
$cnt_{2}$ 表示染成颜色种类为 $2$ 的个数。      

因为是完全二分图所以它的节点个数为：  

$$ cnt_{1} \times cnt_{2} $$   

我们已经有题目给出的 $n$  个点，所以答案为：  

$$ cnt_{1} \times cnt_{2} -n+1 $$    

> 注意不开 long long 见祖宗。

### Solution:

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int long long
const int N=1e5+50;

int n;


struct edge{
	int to,next;
}e[N<<1];
int head[N<<1],cnt;
void add_edge(int u,int v){
	++cnt;
	e[cnt].to=v;
	e[cnt].next=head[u];
	head[u]=cnt;
}
int res[3],col[N<<1];
void dfs(int n,int c){
	col[n]=c;
	res[c]++;
	for(int i=head[n];i;i=e[i].next){
		int y=e[i].to;
		if(!col[y]){
			dfs(y,3-c);
		}
	}
}
signed main()
{
	scanf("%d",&n);
	for(int i=1;i<n;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs(1,1);
	printf("%lld\n",res[1]*res[2]-n+1);
}
```

---

## 作者：happybob (赞：0)

二分图染色好题。

一开始给定的是一个连通图。$n$ 个点 $n - 1$ 条边的连通图一定是一棵树，而一棵树不存在奇数环，显然是二分图。

既然是二分图，必然可以黑白染色。对于每一个白点，都可以和其他每一个黑点连边。全部连完之后总共有 $c1 \times c2$ 条边，$c1, c2$ 分别表示黑点白点数量，能加的边数为 $c1 \times c2 - (n - 1)$。

---

## 作者：BreakPlus (赞：0)

题面中的“二分图”的概念说得不太直观（虽然这也是官方的定义），这里就简单说一下：如果能把一个图中的所有点黑白染色，任意一条边所连接的两个点颜色不同，那么这个图就是个“二分图”。

一棵树一定是个二分图。为什么呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/rjkn53bl.png)

如图，我们将根节点染成黑色（图中点外面的圈是粗的就是黑色，细的就是白色），接着把其儿子染成白色，儿子的儿子们染成黑色……只要该节点与其儿子颜色不同，就一定可以满足条件，因为父亲节点与其颜色也是不同的。

我们在一棵树上，加边而不能加点。对于已有的边，连接的两个点已经注定了颜色，不能再改了，我们只能在这棵已经染好色的树上加边，显然只能将颜色不同的两个点相连。先忽略现有的边，我们一共可以连黑色点的数量与白色点的数量之乘积，再把这个数减掉原有的边的数量 $(n-1)$ 即可。

现在的问题就是怎么染色了，这个还是比较好做，把每个点的深度求出，将其 $\bmod \ 2 $ 就是它的颜色。

Code(C++):

```cpp
// ========================================
//  Author: BreakPlus
//  Email: breakplus@foxmail.com
//  Blog: www.luogu.com.cn/blog/BreakPlus/
// ========================================
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long ll;
#define rint register int
inline int read(){
    int x=0,f=1; char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=-1; ch=getchar();}
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return x*f;
}
const int maxn=100010;
int n,u,v,dep[maxn],cnt1,cnt2,head[maxn],tot;
struct Edge{
	int to,nxt;
}edge[maxn<<1];
inline void add(int u,int v){
	edge[++tot].to=v;
	edge[tot].nxt=head[u];
	head[u]=tot;
}
inline void dfs(int u,int fa,int d){
	dep[u]=d;
	for(rint i=head[u];i;i=edge[i].nxt){
		int v=edge[i].to;
		if(v==fa) continue;
		dfs(v,u,d+1);
	}
}
int main(){
	n=read();
	for(rint i=1;i<n;i++) u=read(),v=read(),add(u,v),add(v,u);
	dfs(1,0,0);
	for(rint i=1;i<=n;i++)
		if(dep[i]%2) cnt1++;
		else cnt2++;
	printf("%lld\n",1ll*cnt1*cnt2-1ll*(n-1));
	return 0;
}

```

---

## 作者：huangxianghui (赞：0)

这里首先点明一个概念：二分图（~~不过我相信会来做这道题的都知道了~~）
### 二分图：将图分成两部分，各部分之间没有连线，两部分之间每一对点都有连线
一图胜千言，上图

![](https://cdn.luogu.com.cn/upload/image_hosting/p6k4tfzd.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如图可见，两个粗黑圈将点分成两部分，红线表示两部分之间的连点（但各部分之间的点无连线），这种图我们称之二分图

### 二分图建立方式

很明显，一条边连接的两点一定分属于两个不同的部分，从任意一个点开始，将一个点染成黑色，与它直接相连的染成白色……如此下去，再将颜色相同的放在一起，即可得到一个二分图

```
q.push(1),num[1]=1;//队列存储+染色
	while (!q.empty())//循环
	{
		int x=q.front();
		q.pop();
		f(i,0,v[x].size()-1)//愿意用邻接表的就换一下
		{
			if (!num[v[x][i]]) num[v[x][i]]=((num[x]==1)?2:1),q.push(v[x][i]);//染成不同的颜色
		}
	}
```


## Solution

回到这道题

要把一棵树改成满足二分图的性质，我们只需要把树按二分图的方式染色，再看看两部分之间有多少边没连，即是最大数量添加边

```
#include<bits/stdc++.h>
#define ll long long
#define f(i,a,b) for (ll i=a;i<=b;i++)
#define fx(i,a,b) for (ll i=a;i>=b;i--)
using namespace std;
const int maxn=1e5+10;
ll n,v1=1,v2;
int num[maxn];
vector<int> v[maxn];
inline ll read()
{
	ll l=0,f=1;
	char c;
	while (!isdigit(c=getchar())) if (c=='-') f=-1;
	while (isdigit(c)) l=(l<<3)+(l<<1)+(c^48),c=getchar();
	return l*f;
}
queue<int> q;
signed main()
{
	n=read();
	f(i,1,n-1)
	{
		int a1=read(),a2=read();
		v[a1].push_back(a2),v[a2].push_back(a1);
	}
	q.push(1),num[1]=1;
	while (!q.empty())
	{
		int x=q.front();
		q.pop();
		f(i,0,v[x].size()-1)
		{
			if (!num[v[x][i]])
			{
				num[v[x][i]]=((num[x]==1)?2:1),q.push(v[x][i]);
				if (num[v[x][i]]==1) v1++;
				else v2++;
			}
		}
	}
	cout<<v1*v2-n+1;
	return 0;
}
```


---

## 作者：StupidSeven (赞：0)

## Subject
[题目传送门](https://www.luogu.com.cn/problem/CF862B)

## Analysis
给你一个二分图。连接两个点集的边需要$ size[a] \times size[b] $，然后我们有$ n-1 $条边，剩下的边就是$ size[a] \times size[b]-n+1 $，染色就好了。

## Code
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
#define M 1000010
#define int long long 
inline int Readint(void){
	int s=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){s=s*10+c-48;c=getchar();}
	return s*f;
}
struct Node{
	int u,v,idx;
}Edge[M];
int n,u,v;
int head[M],cnt;
int belong[M],size[M],idx;
void addEdge(int u,int v){
	Edge[++cnt]=(Node){head[u],v};
	head[u]=cnt;
	return;
}
void Dfs(int u,int idx){
	belong[u]=idx;
	size[idx]++;
	for(int i=head[u];i;i=Edge[i].u){
		int v=Edge[i].v;
		if(belong[v]==-1)
			Dfs(v,!idx);
	}
	return;
}
signed main(void){
	n=Readint();
	memset(belong,-1,sizeof belong);
	for(int i=1;i<n;i++){
		u=Readint();v=Readint();
		addEdge(u,v);
		addEdge(v,u);
	}
	Dfs(1,1);
	printf("%lld\n",size[0]*size[1]-n+1);
	return 0;
}
```
~~谢谢朋友们！~~

---

