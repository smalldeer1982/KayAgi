# [COCI 2017/2018 #5] Planinarenje

## 题目描述

米尔科和斯拉夫科喜欢一起徒步旅行。米尔科喜欢山峰，而斯拉夫科喜欢山谷。因此，每次他们爬到一个山峰时，斯拉夫科决定他们要下到哪个山谷，前提是有通往该山谷的小径。同样地，在每个山谷中，米尔科决定他们要爬上哪个山峰。永远不可能直接从一个山峰爬到另一个山峰，或从一个山谷到另一个山谷。为了使徒步旅行尽可能有趣，他们从不重复访问同一个地点（无论是山峰还是山谷）。一旦他们到达一个只能通往他们之前访问过的地点的地方，他们就会叫山地救援队来接他们。如果最后一个地点是山峰，米尔科获胜；如果是山谷，斯拉夫科获胜。

显然，你已经知道你的任务是什么：如果我们假设他们两个都以最佳方式进行游戏，谁会获胜？请为所有初始山峰回答这个问题。

## 说明/提示

在占总分数 30% 的测试用例中，将满足 $1 \leq N \leq 10$ 和 $1 \leq M \leq N \cdot N$。

在额外占总分数 20% 的测试用例中，对于每两个连接的地点之间，将存在唯一的路径。换句话说，图将是一个森林。

**第二个测试用例的说明：**

从第一个山峰开始，斯拉夫科可以选择去第一个山谷，所以斯拉夫科获胜。

从第二个山峰开始，斯拉夫科可以选择去第二个山谷，之后米尔科通过选择去第四个山峰获胜。

从第三个山峰开始，没有小径，所以米尔科获胜。

从第四个山峰开始，斯拉夫科必须选择去第二个山谷，之后米尔科通过选择第二个山峰获胜。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
2 3
1 2
2 2
2 1```

### 输出

```
Slavko
Slavko```

## 样例 #2

### 输入

```
4 5
2 2
1 2
1 1
1 3
4 2```

### 输出

```
Slavko
Mirko
Mirko
Mirko```

## 样例 #3

### 输入

```
4 5
1 2
1 3
2 2
2 3
4 1```

### 输出

```
Slavko
Slavko
Mirko
Slavko```

# 题解

## 作者：Sunny郭 (赞：17)

# 题意
给定 $n$ 代表 $n$ 个山峰和山谷，给定 $m$ 代表 $m$ 条道路，给定 $m$ 条道路，第 $i$ 个山峰出发 Mirko 赢的条件：从山峰 $i$ 开始走，每次“山谷——山峰——山谷……”依次选，如果最后是山峰，就赢。

# 算法分析
由题目可知，山峰和山峰之间没有路，山谷同理，于是把山峰和山谷各自划分为一个集合的话，可以发现这是个“二分图”。

最优策略几个字容易想到是“博弈”。

再从本质出发，每次都会在两个状态（选山峰或者山谷）之间交替，所以这题是“二分图博弈”。

# 算法讲解
二分图博弈可以使用[匈牙利算法](https://www.luogu.com.cn/problem/P3386)（求最大匹配）解决。

本题目的先手：斯拉夫科( Slavko ) ——游戏开局先选山谷。
### 猜想：
如果最大匹配一定包含 $S1$（一个点），那么先手只需要一直按照匹配选点即可，所以先手必胜。

### 证明：

#### 定义：非匹配点为少了这个点也可以完成最大匹配的点。

后手不可能选到非匹配点，如果后手选到一个非匹配点，设路径为 $S_{1} \sim S_{n}$，那么把现在的匹配 $S_{1} \sim S_{n}$ 换成 $S_{2} \sim S_{n}$，匹配数不变但不包含 $S_{1}$，与最大匹配一定包含 $S_{1}$ 矛盾。（[补充讲解](https://zhuanlan.zhihu.com/p/359334008)）
### 结论：
当一个点在所有最大匹配的方案中（少了这个点无法最大匹配），那么先手必胜。
# 算法实现
先跑一遍最大匹配（我这里使用匈牙利），再从每个非最大匹配点开始使用 dfs 搜路径，并把途经的的点都标记为先手输（搜路径的通俗理解：把非匹配点与相邻的点匹配，此时最大匹配数不变，那么本来与此相邻点匹配的点是非匹配点）。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5005;
int i, j, k, n, m, l, a, b;
int h[N], p[N], v[N], ans[N];
struct ab{
	int b, n;
}d[N];
inline void cun(int a, int b){
	d[++l].b=b, d[l].n=h[a], h[a]=l;
}
int dfs(int a){
	for(int i=h[a]; i; i=d[i].n){
		int b=d[i].b;
		if(v[b]!=k&&(v[b]=k))//使用k（全局变量）来充当时间戳，避免memset耗时太多
			if(!p[b]||dfs(p[b])) return p[b]=a;//模板
	}
	return 0;
}
void sec(int a){
	ans[a]=1;//是非最大匹配中的点
	for(int i=h[a]; i; i=d[i].n){
		int b=d[i].b;
		if(~v[b]) v[b]=-1, sec(p[b]);//“~”可以判断是否-1，是-1会返回0，此处赋值为-1的原因是，避免数组初始时为0的误判
        	//找非匹配点找山峰的即可（山峰出发），所以是sec(p[b])，而不是sec(b)
	}
}
signed main(){
	scanf("%d%d", &n, &m);
	for(i=1; i<=m; ++i){
		scanf("%d%d", &a, &b);
		cun(a, b);//匈牙利算法，a和b存有向边即可
	}
	for(k=1; k<=n; ++k) if(!dfs(k)) sec(k);
   	//dfs(k)==1代表是在当前这个最大匹配中，不为1时，就要深搜找路喽~
	for(k=1; k<=n; ++k) puts(ans[k]?"Mirko":"Slavko");
	return 0;
}
```
~~（个人码风奇特）~~
## 结语
相当于是模板题？如果事先不知道此做法的话会有一点难度。

---

## 作者：Skyjoy (赞：9)

# 思路

既然这道题是个二分图，我们就会很自然地联想到有关二分图最大匹配和增广路的知识。那我们该如何思考呢？

我们观察题目要求，如果我们的起始点必然在最大匹配中，那么显然是先手必胜的。如果起始点不一定在最大匹配中的话，就会形成增广路，对手就可以沿着最大匹配走，得到必胜的状态，所以后手必胜。

所以对于这道题，我们可以使用 Dinic 先跑出最大匹配，然后枚举每个点，修改其连出去的边的流量，再跑最大匹配，看看答案是否变化。

~~然后 T 了~~

原来 Dinic 的复杂度是 $O(\sqrt{n}m)$ ，本题还要再乘上一个 $n$ ，所以炸了。

于是我们考虑匈牙利算法，因为它可以单独判断每一个点是否匹配。所以我们可以对于每一个未匹配点跑增广路，其中的每一个山峰点都不会在每一个最大匹配中出现（即不一定在最大匹配中）。记录这样的点，最后输出即可。复杂度是 $O(nm)$ ，可以通过。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5010;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x*f;
}
int n,m,x,y,vis[N],head[N],cnt,ans[N],match[N];
struct edge{
	int to,nxt;
}e[N];
void add(int u,int v){
	e[++cnt].to=v,e[cnt].nxt=head[u],head[u]=cnt;
}
int dfs1(int u){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(vis[v])continue;
		vis[v]=1;
		if(!match[v]||dfs1(match[v])){
			match[v]=u;
			return 1;
		}
	}
	return 0;
}
void dfs2(int u){//跑增广路
	ans[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(vis[v])continue;
		vis[v]=1;
		dfs2(match[v]);
	}
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		x=read(),y=read();
		add(x,y);
	}
	for(int i=1;i<=n;i++){
		memset(vis,0,sizeof(vis));
		if(dfs1(i))continue;
		memset(vis,0,sizeof(vis));
		dfs2(i);
	}
	for(int i=1;i<=n;i++)puts(!ans[i]?"Slavko":"Mirko");
	return 0;
}
```

CSP2021_RP+=inf,NOIP2021_RP+=inf;

---

## 作者：_HCl_ (赞：5)

来写一篇思路更加严谨流畅的题解。

# P4617 题解

**题意简述**

给定一个二分图。有两个人一开始在左部，斯拉科夫可以在左部选择去到右部的哪一个节点，米尔克可以在右部选择去到左部的哪一个节点。不可以重复经过一个节点。

当无路可走时，在左部则米尔克胜利，在右部则斯拉科夫胜利。两人均采取最优策略，询问从每一个左部点出发，谁获胜。

**思路引导**

由于一个点不会重复经过，所以我们不难联想到**二分图匹配**。如果沿着二分图的匹配（即交错路）走，就可以保证不经过同一个点。

先给出一个结论：**如果起始点 $H$ 一定在最大二分图匹配中，则斯拉科夫必胜，反之，米尔克胜利**。这里的“**一定**”是指所有的最大二分图匹配中都有 $H$。

再来证明一下：

首先，我们先明确，$H$ 一定在最大匹配中时，斯拉科夫就一定可以一直沿着交错路走，直到无路可走时，他们一定在右部（山谷）中。接下来我们分成几点来证明。

- 从左部的最大匹配点一定可以走到右部的最大匹配点。

这个就是匹配的定义。

- 从右部的最大匹配点要么走不了（即斯拉科夫取胜），要么只能去到左部的最大匹配点。换言之，右部的最大匹配点不能走到非匹配点。

这一点用反证法证明。

假设走的路径是 $H-P_1-P_2-\dots-P_k-T$，其中 $T$ 是左部的非匹配点，$H$ 和 $P_i$ 是匹配点。

当前的匹配是 $H-P_1,P_2-P_3,\dots,P_{k-1}-P_{k},\dots$，那么也可以进行 $P_1-P_2,P_3-P_4,\dots,P_k-T,\dots$ 的匹配。

容易注意到，在 $P_k$ 之前，两个匹配的匹配数是一样的。又由于非匹配点的存在不影响匹配数，所以在 $P_k$ 之后，两个匹配的匹配数也是一样的。（或者理解为后面的部分两个匹配都是 $P_{k+1}-P_{k+2},P_{k+3}-P_{k+4},\dots$）。

所以这两个匹配的匹配数是一样，都是最大匹配。但是后面的这个最大匹配却不包含 $H$，这与 $H$ 一定在最大匹配中相矛盾。所以原命题得证。

这样，在右部时，米尔克只能选匹配点，~~正合斯拉科夫心意~~，而每一个左部的匹配点都可以连到右部，但右部就不一定能连到左部。所以斯拉科夫必胜。充分性证毕。

接下来说明必要性。

如果 $H$ 不一定是最大匹配点，那么根据之前的讨论，后面这种匹配方式也是合法的。因为这两种匹配方式正好错位，所以换成这种匹配方式后，米尔克和斯拉科夫的处境互换。之后的讨论同理，就不赘述了。因此米尔克必胜，必要性证毕。

所以现在原问题就转化为**判断每一个点是否一定是最大匹配点**。

如果使用网络流（比较每一个点删除前后的流量）处理，复杂度是 $\mathcal{O}(nm\sqrt{n})$，显然会超时。所以考虑使用匈牙利算法。

我们通过搜索交错树来标记不一定在最大匹配中的点。

假设现在有一个匹配不上的点 $Q$ 和一个在最大匹配中的点 $P_1$，且 $Q$ 和 $P_1$ 有边相连，$P_1$ 和 $P_2$ 匹配。我们断开 $P_1$ 和 $P_2$ 的匹配，并将 $P_1$ 和 $Q$ 匹配。这样的操作不会使匹配数改变，也就是操作后的匹配还是最大匹配。这样 $P_2$ 就不在最大匹配之中了，也就说明 $P_2$ 不一定是最大匹配点。

然后我们将 $P_2$ 当做是 $Q$，继续在交错树上搜索。这样就可以标记出所有的不一定在最大匹配中的点。复杂度 $\mathcal{O}(nm)$。

给个图作为辅助理解。

![](https://cdn.luogu.com.cn/upload/image_hosting/mab3ui3p.png)

其中蓝色表示在匹配中，红色表示不在匹配中，粗线表示匹配，细线表示普通的连边。


**实现**

1. 读入，建图。
2. 对于每一个点跑匈牙利算法。
3. 如果匹配不成功，搜索交错路。
4. 输出答案。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int mat[1000001],v[100001],f[100001];
vector<int> e[100001];
bool dfs(int x,int tag){//匈牙利算法
	if(v[x]==tag)return 0;
	v[x]=tag;
	for(int i=0;i<e[x].size();++i){
		int y=e[x][i];
		if(mat[y]==0||dfs(mat[y],tag)){
			mat[y]=x;
			return 1;
		}
	}
	return 0;
}
void dfs2(int x){//搜索交错树
	f[x]=1;//标记不一定在匹配中
	for(int i=0;i<e[x].size();++i){
		int y=e[x][i];
		if(~v[y])v[y]=-1,dfs2(mat[y]);//在匹配中才去搜索
		//这个-1第一篇题解讲的很清楚了
	}
} 
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
	}
	for(int i=1;i<=n;++i)if(!dfs(i,i))dfs2(i);
	for(int i=1;i<=n;++i){
		if(f[i])cout<<"Mirko\n";
		else cout<<"Slavko\n";
	} 
	return 0;
}
```

---

## 作者：decoqwq (赞：4)

二分图博弈板子题

这一类问题基于以下几个特点，即两人参加，两组状态间可以互相转移，同组间不可，一个状态最多走一次，谁无法转移谁输

若当前出发点$x$未被匹配，则他必定转移入一个匹配点，否则会形成增广路，此时对手可以一直沿着匹配点进行转移，则先手必败

如果属于最大匹配，显然先手必胜

所以考虑先跑出最大流，然后每次我们看删除当前出发点是否改变最大匹配数，可以考虑改变该点已经流过的流量，之后在残量网络上跑最大流，如果$ans=1$即说明先手必败，反之亦然

```cpp
/*deco loves Chino*/
#include <bits/stdc++.h>
using namespace std;
int head[10010],n,m,cnt=1,s,t;
struct edge
{
	int next,to,dis;
}e[40010],e1[40010];
void add(int u,int v,int diss)
{
	e[++cnt].to=v;
	e[cnt].next=head[u];
	e[cnt].dis=diss;
	head[u]=cnt;
}
int dis[10010];
int bfs()
{
	queue<int> q;
	memset(dis,-1,sizeof(dis));
	dis[s]=0;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int i=head[u];i;i=e[i].next)
		{
			int v=e[i].to;
			if(dis[v]==-1&&e[i].dis>0)
			{
				dis[v]=dis[u]+1;
				q.push(v);
			}
		}
	}
	return dis[t]!=-1;
}
int dfs(int u,int ex)
{
	if(u==t||!ex)
	{
		return ex;
	}
	int flow=0;
	for(int i=head[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(dis[v]!=dis[u]+1||e[i].dis<=0)
		{
			continue ;
		}
		int tmp=dfs(v,min(e[i].dis,ex));
		if(!tmp)
		{
			continue ;
		}
		ex-=tmp,flow+=tmp;
		e[i].dis-=tmp,e[i^1].dis+=tmp;
		if(!ex)
		{
			break;
		}
	}
	return flow;
}
int main()
{
	//freopen("planina.in","r",stdin);
	//freopen("planina.out","w",stdout);
	cin>>n>>m;
	s=0,t=(n<<1)+1; 
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y+n,1);
		add(y+n,x,0);
	}
	for(int i=1;i<=n;i++)
	{
		add(s,i,1);
		add(i,s,0);
		add(i+n,t,1);
		add(t,i+n,0);
	}
	int ans=0;
	while(bfs())
	{
		ans+=dfs(s,0x3f3f3f3f);
	}
	memcpy(e1,e,sizeof(e));
	int fl=0;
	for(int i=1;i<=n;i++)
	{
	    if(fl)
	    {
	    	memcpy(e,e1,sizeof(e1));
	    }
		int flag=0,pos;
		for(int j=head[i];j;j=e[j].next)
		{
			int v=e[j].to;
			if(v>n&&e[j].dis==0)
			{
				flag=1;
				pos=v;
				break;
			}
		}
		if(!flag)
		{
		    fl=0;
			cout<<"Mirko"<<"\n";
		}
		else
		{
		    int tk;
			for(int j=head[pos];j;j=e[j].next)
			{
				if(e[j].to==t)
				{
				    tk=j;
					e[j].dis=1,e[j^1].dis=0;
					break;
				}
			}
			ans=0;
			while(bfs())
			{
				ans+=dfs(s,0x3f3f3f3f);
			}
			if(ans==1)
			{
			    fl=1;
				cout<<"Mirko"<<"\n";
			}
			else
			{
			    fl=0;
				cout<<"Slavko"<<"\n";
				e[tk].dis=0,e[tk^1].dis=1;
			}
		}
	}
}
```



---

## 作者：_AIR (赞：1)

这题一看就是非常典型的二分图博弈题。    

二分图博弈具有以下几个条件：    

1. 共2人参与。     

2. 博弈状态(对应节点)可分为两类，任意合法转移都是在两类状态之间转移，而不能在任意一类状态内部转移。     

3. 不可以转移到已访问状态。

4. 无法转移者输。    

## 解法：

我们把题目中的每座山峰和山谷都看作一个点进行连边，发现这会构成一个二分图。

然后先跑一遍二分图最大匹配，对于任意一座山峰对应的点 $X$ ，它只能有两种情况：

1. $X$ 不属于最大匹配的匹配点，走一步后必然会走到一个匹配点，否则如果遇到一个非匹配点就会形成一条增广路，那么就不符合最大匹配的前提。而走到一个匹配点后，可以不断沿着匹配边走，最后必然会停留在山峰集合，也就是先手必输。因为如果停留在山谷集合，依然相当于找到了一条增广路，不符合前提。
2. $X$ 属于最大匹配的匹配点，由前面可知，此时先手必胜。

如果一个点 $X$ 在所有最大匹配的方案中都属于匹配点，那么我们称 $X$ 为必胜点，此时是先手必胜。

如何判断 $X$ 是不是必胜点？

有三种判断方法：

1. 较暴力的做法，先对于原图求出最大匹配，然后删除当前结点，在进行一次匹配，若最大匹配数量减小，说明当前点是必胜点，不然就是非必胜点。这个方法的缺点很明显：慢。

2. 考虑一个点 $X$ 是必须点，相当于没有点可以取代 $X$ ，因此我们从 $X$ 开始遍历，看是否可以找到一个同侧的未匹配点，如果可以找到，则说明 $X$ 为非必须点。

3. 我们对每一个未匹配点 $X$ 递归，如果这个点 $X$ 能将其他匹配点替换掉，那么说明被替换的点都不是必胜点，打上标记即可。

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
int ans[100005];
bool used[100005];
int go[100005];
vector<int> e[200005];
bool find(int x)
{
    for(int i=0;i<e[x].size();i++)
    {
        int to=e[x][i];
        if(!used[to])
        {
            used[to]=true;
            if(!go[to]||find(go[to]))
            {
                go[to]=x;
                return true;
            }
        }
    }
    return false;
}
void dfs(int x)
{
    ans[x]=1;
    for(int i=0;i<e[x].size();i++)
    {
        int to=e[x][i];
        if(!used[to])
        {
            used[to]=true;
            dfs(go[to]);
        } 
    }
}
signed main()
{
    scanf("%lld%lld",&n,&m);
    int maxget=0;
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%lld%lld",&u,&v);
        e[u].push_back(v);
    }
    for(int i=1;i<=n;i++)
    {
        memset(used,0,sizeof(used));
        if(find(i))
        {
            maxget++;
            continue;
        }
        memset(used,0,sizeof(used));
        dfs(i);
    }
    for(int i=1;i<=n;i++)
    {
        if(ans[i])printf("Mirko\n");
        else printf("Slavko\n");
    }
}
```

---

## 作者：Lyccrius (赞：1)

视山峰为左部点，山谷为右部点。

明晰一个题目中的条件，虽然起点在山峰，但先手是以山谷为目标的 Slavko。

如果一个左部点必定在最大匹配上，那么无论后手怎么走，先手一定有一种走法，使得先手每一步走的边作为匹配边作为最大匹配，即最后走到右部点，先手胜。否则，后手一定有一种走法，使得后手每一步走的边作为匹配边构成极大匹配，其大小比最大匹配小一，最后走到左部点，后手胜。

若一个点必须在最大匹配上，则删除该点后最大匹配数减小，换言之加入该点后最大匹配数增大。

考虑匈牙利算法的匹配过程，如果一个点匹配成功，说明加入该点使得最大匹配数增大，否则加入该点无影响。当一个点匹配失败时，尝试以该点为起点跑交错路，途中经过的每个左部点均标记为非必定在最大匹配上。

```cpp
#include <iostream>

const int maxN = 5000;
const int maxM = 5000;

int n, m;
int u, v;

namespace graph {
    struct Vertex {
        int vis;
        int head;
        int match;
        int must;

        Vertex() {
            must = true;
            return;
        }
    } vertex[2 * maxN + 10];

    struct Edge {
        int head;
        int next;
    }   edge[maxM + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    bool DFS1(int u, int t) {
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (vertex[v].vis == t) continue;
            vertex[v].vis = t;
            if (vertex[v].match == 0 || DFS1(vertex[v].match, t)) {
                vertex[v].match = u;
                return true;
            }
        }
        return false;
    }

    void DFS2(int u, int t) {
        vertex[u].must = false;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (vertex[v].vis == t) continue;
            vertex[v].vis = t;
            if (vertex[v].match) DFS2(vertex[v].match, t);
        }
        return;
    }
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) std::cin >> u >> v, graph::addEdge(u, n + v);
    for (int i = 1; i <= n; i++) if (!graph::DFS1(i, i)) graph::DFS2(i, i + n);
    for (int i = 1; i <= n; i++) if (graph::vertex[i].must) std::cout << "Slavko" << '\n'; else std::cout << "Mirko" << '\n';
    return 0;
}
```

---

## 作者：DengDuck (赞：0)

可以看做是二分图博弈的板子，这里，我复制一下我之前博客中的介绍与证明。

通常此类题目给出一个矩阵，棋盘之类的东西，我们可以转换为二分图，接下来是一个博弈问题。

> 先手将点移动一步，后手再将点移动一步，一个点只能到达一次，反复操作，不可操作者败。

我们有结论：一个起点可以使先手必胜，当且仅当这个点出现在所有的最大匹配方案中。

## 结论证明

两者持续进行游戏，其路径可以看作一条增广路，由于双方决策都是最佳，我们希望增广路越长越好。

我们设增广路为 $a_1\to a_2 \to a_3 \to...\to a_n$。

有了上述铺垫，可以开始证明

必要性：

如果存在一个点不在所有的最大匹配方案中但是必胜，后手可以走其不为最大匹配的方案，直到有一个失配点 $a_{n+1}$。

如果先手还能走，那么这个失配点也一定可以再匹配，这与我们已知的最大匹配矛盾。

充分性：

如果一个点出现在所有的最大匹配方案中，后手无论怎么走，先手都可以走到其匹配点，后手一定走不到失配的点。

因为我们可以设新走到的点为 $a_{n+1}$，则我们有最大匹配方案 $a_2 \to a_3 \to...\to a_n \to a_{n+1}$。

这与这个点出现在所有的最大匹配方案中矛盾。

由此证明完成。

---

来个优雅的分割线。

知道了上述结论，这题我们怎么快速求一个点是否在所有最大匹配中其实是困难的。

之前我学的写法是，枚举所有的点，然后对于这个点强制不选它，然后对于其匹配点跑匈牙利看看能否有解。

**太不优雅了！！！是时候换个活法！！！**


考虑跑匈牙利的时候，一个点被选中就会让最大匹配变大，然后没被选中就说明最大匹配不变。

这时，我们对于这个没选的点，尝试替换掉别的匹配，如果成功替换，就说明那个点都不一定在最大匹配中，我们打上标记，然后这么递归下去做。

这样我们就优雅地解决这个问题。

```cpp
#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int N=5005;
int n,m,Ans[N],C[N],Vis[N];
vector<int>G[N]; 
int Dfs(int x)
{
	for(int i:G[x])
	{
		if(Vis[i])continue;
		Vis[i]=1;
		if(!C[i]||Dfs(C[i]))
		{
			C[i]=x;
			return 1;
		}
	}
	return 0;
}
void Dfs2(int x)
{
	Ans[x]=1;
	for(int i:G[x])
	{
		if(Vis[i])continue;
		Vis[i]=1;
		Dfs2(C[i]);
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,x,y;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		G[x].pb(y);
	}
	for(int i=1;i<=n;i++)
	{
		memset(Vis,0,sizeof(Vis));
		if(Dfs(i))continue;
		memset(Vis,0,sizeof(Vis));
		Dfs2(i);
	}
	for(int i=1;i<=n;i++)
	{
		if(Ans[i])puts("Mirko");
		else puts("Slavko");
	}
}
```

---

## 作者：huangrenheluogu (赞：0)

[P4617](https://www.luogu.com.cn/problem/P4617)。

进行二分图匹配，然后让 Mirko 沿着匹配边走？

正确性先不说，复杂度先爆炸。

但是，这个思路的方向是正确的。

用 $M$ 代表山峰，用 $V$ 代表山谷。

那么，走的路径就是 $M_1,V_1,M_2,V_2\dots,M_k,(V_k)$。如何判断是谁赢谁输呢？

如果我们要让 Slavko 胜利（他有主动权），显然不能让 Mirko 逼到不能选择的地方。容易想到开始的思路就是因为我们可以利用“匹配”保证 Slavko 总有 $M_i$ 对应的 $V_i$ 可以选择。

但是，如果 Mirko 可以从最后的 $V_k$ 走到 $M_{k+1}$，然后 Slavko 无路可走了，怎么办？

观察两个方案，一个是 $M_1,V_1,M_2,V_2\dots,M_k,V_k$，一个是 $M_1,V_1,M_2,V_2\dots,M_k,V_k,M_{k+1}$。

发现前面的方案，我们不能构造新的匹配，后面的方案，可以用 $M_i$ 和 $V_{i+1}$ 构造新的匹配。

所以，我们可以得出结论，当匹配不一定需要山峰 $(M_1)$ 的时候，从这里出发，就输了。

如果 $M_1$ 在最大匹配中，那么显然 Mirko 就不能进行上面操作了，那 Slavko 就可以顺着匹配走，然后就可以让 Mirko 无路可走，原因是 $M_1$ 总在最大匹配中，就导致不能出现上面的 $M_{k+1}$。

如果 $M_1$ 不一定在最大匹配中，那么 Slavko 是否可以换一种走法呢？

不行的。

但是，如果一边可以换，那另外一边是不是可以走得通呢？

不行。原因在于如果另外一边是恰好匹配，不能换边，那么由于 $M_1$ 已经被“锁定”到另外一边了，它显然会在二分图匹配中；反之，就会出现上面的局面。

简单来说，如果没有让 Mirko 走回来这一步，$M_1$ 必然会锁定，$M_1$ 就必须在二分图匹配中。

这是一个比较经典的问题，用网络流即可。

在残网络上跑一边 Tarjan，缩点，剩余流量为 $0$ 且边上两点不在强联通分量中，说明这条边是必须边。

这个定理蒟蒻不会证明，背下来就好了。

当然在 [TianyiLemon](https://www.luogu.com.cn/user/362346) 的题解中有证明。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 5005, inf = 1e9;
int n, m, fir[N << 1], nxt[N << 3], son[N << 3], edge[N << 3], tot = 1, x, y, S = 0, T, now[N << 1], d[N << 1], q[N << 1], h, t;
int tem, low[N << 1], dfn[N << 1], idx, cnt, to[N << 1];
bool vis[N << 1], ans[N << 1];
inline void add(int x, int y, int flow){
	nxt[++tot] = fir[x];
	fir[x] = tot;
	son[tot] = y;
	edge[tot] = flow;
}
inline void Add(int x, int y, int flow){
	add(x, y, flow);
	add(y, x, 0);
}
inline bool bfs(){
	for(int i = S; i <= T; i++) now[i] = fir[i], d[i] = 0;
	h = 0, q[t = 1] = S, d[S] = 1;
	while(h < t){
		h++;
		x = q[h];
		for(int i = fir[x]; i ; i = nxt[i]){
			if(!d[son[i]] && edge[i]){
				d[son[i]] = d[x] + 1;
				q[++t] = son[i];
				if(son[i] == T) return 1;
			}
		}
	}
	return 0;
}
inline int dinic(int x, int flow){
	if(x == T) return flow;
	int res = flow;
	for(int i = now[x]; i && res ; i = nxt[i]){
		now[x] = i;
		if(d[son[i]] == d[x] + 1 && edge[i]){
			tem = dinic(son[i], min(res, edge[i]));
			res -= tem;
			edge[i] -= tem;
			edge[i ^ 1] += tem;
		}
	}
	return flow - res;
}
inline void tarjan(int x){
	low[x] = dfn[x] = ++idx;
	vis[x] = 1;
	q[++t] = x;
	for(int i = fir[x]; i ; i = nxt[i]){
		if(edge[i]){
			if(!dfn[son[i]]){
				tarjan(son[i]);
				low[x] = min(low[x], low[son[i]]);
			}
			else if(vis[son[i]]) low[x] = min(low[x], low[son[i]]);
		}
	}
	if(low[x] == dfn[x]){
		cnt++;
		while(vis[x]){
			to[q[t]] = cnt;
			vis[q[t--]] = 0;
		}
	}
}
int main(){
	scanf("%d%d", &n, &m);
	T = 2 * n + 1;
	for(int i = 1; i <= m; i++){
		scanf("%d%d", &x, &y);
		Add(x, y + n, 1);
	}
	for(int i = 1; i <= n; i++){
		Add(0, i, 1);
		Add(i + n, T, 1);
	}
	while(bfs()){
		dinic(S, inf);
	}
	t = 0;
	for(int i = S; i <= T; i++){
		if(!dfn[i]) tarjan(i);
	}
	for(int i = fir[S]; i ; i = nxt[i]){
		if(edge[i]) continue ;
		if(to[son[i]] == to[S]) continue ;
		ans[son[i]] = 1;
	}
	for(int i = 1; i <= n; i++){
		printf(ans[i] ? "Slavko\n" : "Mirko\n");
	}
	return 0;
}
```

---

## 作者：TianyiLemon (赞：0)

**给个** $O(m\sqrt{n}) $ **的做法**。

首先问题等价于判断每个左部点是否是二分图最大匹配的必经点，证明其它题解写得很详细了，这里不再赘述。

我们仿照求解二分图最大匹配可行边必经边的思路，将跑完 Dinic 算法后的残量网络 $G_0$ 进行 SCC 缩点。

+ 定理：左部点 $u$ 是最大匹配的必经点，当且仅当 $u$ 是匹配点且 $u$ 和源点 $s$ 在 $G_0$ 中不属于同一个 SCC。

证明：我们称交替经过匹配边和非匹配边的环称为**增广环**，将交替经过匹配边和非匹配边、且长度为偶数的路径称为**半增广路**。可以证明：通过将当前求解出的最大匹配异或上若干个增广环和半增广路，可以生成所有合法的最大匹配。

改变增广环的匹配状态并不会影响点的匹配状态，而改变半增广路的匹配状态只会改变半增广路端点的匹配状态。

因此，左部点 $u$ 是必经点当且仅当 $u$ 是匹配点，且不存在以 $u$ 为端点的半增广路，也就等价于 $u$ 和 $s$ 在 $G_0$ 中不属于同一个 SCC。

上面这部分画画图就很好理解了。

代码很简单就不贴了。

---

