# Andrew and Taxi

## 题目描述

Andrew 更喜欢打车而不是使用其他交通工具，但最近大多数出租车司机行为不端。为了赚更多的钱，出租车司机开始绕圈行驶。Andrew 所在城市的道路是单向的，并且人们不一定能够从一个地方到达另一个地方，但与狡猾的出租车司机相比，这些都不算什么。

市长决定改变某些道路的方向，这样出租车司机就无法无限制地增加行程费用。更正式地说，如果出租车司机在某个路口出发，在进行非零次行驶后，他将无法再次回到该路口。

需要交通管理员来改变道路的行驶方向。对于每条道路，已知需要多少名交通管理员才能将其方向反转。允许逐条道路地改变方向，也就是说，每个交通管理员可以参与反转两条或更多的道路。

你需要计算完成该任务所需雇佣的最少交通管理员数量，以及需要反转方向的道路列表。

## 说明/提示

在第一个样例中，有两个简单环：$1 \rightarrow 5 \rightarrow 2 \rightarrow 1$ 和 $2 \rightarrow 3 \rightarrow 4 \rightarrow 5 \rightarrow 2$。一个交通管理员只能反转道路 $2 \rightarrow 1$，但无法单独破坏第二个环。两个交通管理员可以分别反转道路 $2 \rightarrow 1$ 和 $2 \rightarrow 3$，这样就能满足条件。

在第二个样例中，一个交通管理员无法破坏环 $1 \rightarrow 3 \rightarrow 2 \rightarrow 1$。通过三个交通管理员，我们可以例如反转道路 $1 \rightarrow 3$、$2 \rightarrow 4$、$1 \rightarrow 5$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5 6
2 1 1
5 2 6
2 3 2
3 4 3
4 5 5
1 5 4
```

### 输出

```
2 2
1 3 ```

## 样例 #2

### 输入

```
5 7
2 1 5
3 2 3
1 3 3
2 4 1
4 3 5
5 4 1
1 5 3
```

### 输出

```
3 3
3 4 7 ```

# 题解

## 作者：YBaggio (赞：12)

## 题目意思
给你一个 $n$ 个点，$m$ 条边的有向图，每一个边有一个权值。现在你可以修改任意条边的方向，使得原图变为有向无环图。求修改的边的最大值最小时的方案。
## 思路
看到最大值最小便很容易想到二分答案（即修改的边中的最大值），我们将这个二分的数设为 $mid$。那么很明显，图中的边会被分为两大类：
1. **权值大于 $mid$ 的边**。
2. **权值小于等于 $mid$ 的边**。

### 需要解决的问题：
**prob1**:对于第一类边我们显然是无法修改方向的，如果存在一个环且换上全是一类边。则这个 $mid$ 显然无法让原图变成有向无环图。

**prob2**:对于第二类边我们可以改变其方向，直接统计有哪些需要改变方向的边即可。

于是我们十分欣喜的发现，这两个问题都可以用拓扑排序来解决。对于prob1，我们可以将原图的二类边去掉，然后跑拓扑排序判环。对于prob2，我们在prob1的拓扑排序中顺便记录拓扑序，如果出现一个二类边是由拓扑序在后面的点指向拓扑序在前面的点，就说明这条边构成了环，将这条边记录下来即可。

## AT LAST 上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
vector<int>g[maxn];//邻接表
vector<int>ans;//记录方案
int n,m,rd[maxn],f[maxn],u[maxn],v[maxn],dist[maxn];
//u表示一条边的起点，v表示一条边的终点,dist表示一条边的权值
//rd表示一个点的入度，f表示一个点在新图中的拓扑序
bool check(int x){
	for(int i=1;i<=n;i++){rd[i]=0;g[i].clear();}
	for(int i=1;i<=m;i++){//建图(即只保留一类边) 
		if(dist[i]<=x)continue;//把边权大于二分答案的边建图 
		g[u[i]].push_back(v[i]);
		rd[v[i]]++;
	} 
	queue<int>q;int cnt=0;
	for(int i=1;i<=n;i++){if(rd[i]==0)q.push(i);} 
	while(!q.empty()){//拓扑排序
		int p=q.front();f[p]=++cnt;q.pop(); 
		for(int i=0;i<g[p].size();i++){
			int y=g[p][i];
			if(--rd[y]==0)q.push(y); 
		}	
	}
	if(cnt!=n)return 0;//判断是有环 
	ans.clear();//记录方案（即需要换方向的二类边）
	for(int i=1;i<=m;i++){
		if(dist[i]<=x&&f[u[i]]>f[v[i]])ans.push_back(i);
	}//                            如果从topo序大的点
	//					     	   指向topo序小的点则会产生环 
	//                             需要颠倒过来
	return 1;
} 
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&u[i],&v[i],&dist[i]);//将边的信息用三元组存下来 
	} 
	int l=0,k,r=1e9+10,mid=(l+r)>>1;
	while(l<=r){          //二分颠倒过来的路径的最大值 
		mid=(l+r)>>1; 	
		if(check(mid)){  //合法，记录答案 
			k=mid;//即最小的最大值
			r=mid-1;//这里不break是因为要找到跟小的k	
		}else l=mid+1;
	} 
	printf("%d %d\n",k,ans.size());
	for(int i=0;i<ans.size();i++){
		printf("%d ",ans[i]);
	}	 
	printf("\n");
	return 0;
}
```


---

## 作者：_sys (赞：10)

首先我们发现，本题具有可二分性。若花费$x$可以完成，$x+1$也一定可以完成。
那么判断是否可行，可以把二分得到的$mid$作为下限，仅连接边权大于等于$mid$的边，如果这样的图有环，那么向上二分，否则向下。这样的正确性显然，因为如果图是一个$DAG$，那么剩下的边始终从拓扑序小的向大的连，这样就不会出现环。
可以发现输出方案的思路也是如此。

时间复杂度$O(n\log Maxi)$

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int Maxn=100005;
int n,m,head[Maxn],cnt,maxi,ct[Maxn],dfn[Maxn],ans[Maxn],tot,vis[Maxn];
struct edg
{
	int nxt,to,w;
}edge[Maxn];
void add(int x,int y,int w)
{
	edge[++cnt]=(edg){head[x],y,w};
	head[x]=cnt;
}
int lim; 
bool dfs(int u,int id)
{
	vis[u]=-1;
	for(int i=head[u];i;i=edge[i].nxt)
	{
		int to=edge[i].to;
		if(edge[i].w<=lim) continue;
		if(vis[to]!=-1&&vis[to]) continue;
		if(vis[to]==-1||dfs(to,id)) return true;
	}
	vis[u]=id;
	return false;
}
bool in[Maxn];
void work(int x)
{
	queue <int> Qu;
	int c=0;
	for(int i=1;i<=m;i++)
		if(edge[i].w>lim)
			ct[edge[i].to]++;
	for(int i=1;i<=n;i++)
		if(!ct[i]) Qu.push(i),in[i]=true;
	while(!Qu.empty())
	{
		int u=Qu.front();
		Qu.pop();
		dfn[u]=++c;
		for(int i=head[u];i;i=edge[i].nxt)
		{
			int to=edge[i].to;
			if(edge[i].w>lim)
			{
				ct[to]--;
				if(!ct[to]&&!dfn[to]&&!in[to]) in[to]=true,Qu.push(to);
			}
		}
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int x,y,w;
		scanf("%d%d%d",&x,&y,&w);
		add(x,y,w);
		maxi=max(maxi,w);
	}
	int lt=0,rt=maxi;
	while(lt+1<=rt)
	{
		int mid=(lt+rt)/2;
		lim=mid;
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=n;i++)
			if(!vis[i]&&dfs(i,i))
			{
				lt=mid+1;
				goto A;
			}
		rt=mid;
		A:;
	}
	lim=lt;
	work(lt);
	for(int u=1;u<=n;u++)
		for(int i=head[u];i;i=edge[i].nxt)
		{
			int to=edge[i].to;
			if(edge[i].w<=lt)
				if(dfn[to]<dfn[u]) ans[++tot]=i;
		}
	printf("%d %d\n",lt,tot);
	for(int i=1;i<=tot;i++) printf("%d ",ans[i]); 
	return 0;
}
		
```

---

## 作者：LlLlCc (赞：5)

~~第一篇紫题题解~~

题意十分简洁，大概就是叫你改变边的方向使有向图中没有环。



------------

事实证明，带有“最大值中求最小的”或者“最小值中求最大的”，这一类题目，往往都是用二分来枚举答案的。这题也是一样。


------------

先想一个问题，如果我们可以改变所有边权小于等于X的边，使有向图无环。那么改变所有边权小于等于X+1的边，能不能使有向图无环呢？答案是肯定的，因为小于等于X的所有边肯定也是小于等于X+1的。

想通了这个问题，我们再往二分上想（二分就不用解释了吧，~~我就不信刷紫题的有人不会二分~~）



------------
我们现在已经枚举了最大值，那我们要怎么去check这个值是否能是无向图无环呢？

判断有没有环，我们首选的就是拓扑了（~~我不会说我只会拓扑的~~）

[不会拓扑的看这](https://blog.csdn.net/qq_41713256/article/details/80805338)

因为我们枚举的是改变的边的最大值，所以边权小于我们所枚举的值的边直接跳过。看看所有边权大于等于我们枚举的值的边能不能练成一个环就行了。

拓扑的核心代码：

```
for (int i=1;i<=n;i++)
	for (int j=lnk[i];j;j=nxt[j]){
		if (w[j]<=mid) continue;
		T_in[son[j]]++;       //记录入度
	}
	for (int i=1;i<=n;i++) if (!T_in[i]) Q[++til]=i;  //记录入度为0的节点
	while (hed<til){
		hed++;Id[Q[hed]]=++tot;vis[Q[hed]]=1;
		for (int i=lnk[Q[hed]];i;i=nxt[i]){
			if (w[i]<=mid) continue;
			T_in[son[i]]--;if (!T_in[son[i]]) Q[++til]=son[i];
		}
	}
	for (int i=1;i<=n;i++) if (!vis[i]) return 0;
```



------------

现在，我们已经知道了所该边的最大值了，还有一个问题要求，要改哪些边呢？

这个问题呢，我们只要搞懂拓扑排序的原理即可。

拓扑是记录节点的顺序的，所以我们只要给每个节点标记一下他出现的时间戳，再看看他所有的儿子节点有没有比他更早出现的，如果有，那么这个边就是要改的，纪录一下就好。

完整代码：

```
#include<bits/stdc++.h>
#define maxn 1000005
using namespace std;
int n,m,x,y,z,lnk[maxn],id[maxn],Id[maxn],nxt[maxn],L,R,mid,Q[maxn],tot,top,T_in[maxn],w[maxn],ans,son[maxn],cnt,Ans[maxn];
bool vis[maxn];
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-f;ch=getchar();}
	while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
inline void add(int x,int y,int z,int k){nxt[++tot]=lnk[x];lnk[x]=tot;w[tot]=z;son[tot]=y;id[tot]=k;}
inline bool check(int x){
	memset(T_in,0,sizeof T_in);
	memset(vis,0,sizeof vis);
	tot=0;int hed=0,til=0;
	for (int i=1;i<=n;i++)
	for (int j=lnk[i];j;j=nxt[j]){
		if (w[j]<=mid) continue;
		T_in[son[j]]++;
	}
	for (int i=1;i<=n;i++) if (!T_in[i]) Q[++til]=i;
	while (hed<til){
		hed++;Id[Q[hed]]=++tot;vis[Q[hed]]=1;
		for (int i=lnk[Q[hed]];i;i=nxt[i]){
			if (w[i]<=mid) continue;
			T_in[son[i]]--;if (!T_in[son[i]]) Q[++til]=son[i];
		}
	}
	for (int i=1;i<=n;i++) if (!vis[i]) return 0;
	cnt=0;
	for (int i=1;i<=n;++i)
    for (int j=lnk[i];j;j=nxt[j]) if (Id[son[j]]<Id[i]&&w[j]<=mid) Ans[++cnt]=id[j];
	return 1;
}
int main(){
	n=read(),m=read();
	for (int i=1;i<=m;i++){
		x=read(),y=read(),z=read();
		add(x,y,z,i);R=max(R,z);
	}
	while (L<=R){
		mid=L+R>>1;
		if (check(mid)) ans=mid,R=mid-1;
		else L=mid+1;
	}
	printf("%d %d\n",ans,cnt);
	sort(Ans+1,Ans+cnt+1);
	for (int i=1;i<=cnt;i++) printf("%d ",Ans[i]);
	return 0;
}
```

---

## 作者：Paranoid丶离殇 (赞：4)

### **题目描述**

给定一个有向图，改变其中某些边的方向，它将成为一个有向无环图。

现在求一个改变边方向的方案，使得所选边边权的最大值最小。

##  输入格式

点数n，边数m，接下来是m条有向边

##  **输出格式**

第一行输出两个值，一个所选边权最小值和边数k

接下来一行k个编号，表示那些边需要反向

**输入样例**

```
5 6
2 1 1
5 2 6
2 3 2
3 4 3
4 5 5
1 5 4


5 7
2 1 5
3 2 3
1 3 3
2 4 1
4 3 5
5 4 1
1 5 3
```

**输出样例**

```
2 2
1 3 

3 3
3 4 7 
```

**题解：**

每次取到一个 mid ，只保留长度大于 mid 的边
①对于比mid大的边，不能改变方向，于是直接加入图中
②然后只需看看有没有环就行了，因为比mid小的边我们可以任意更改

dfs判环，若有环，说明 ans>mid ，否则 ans≤mid
可以用拓扑排序做
因为它只让最大值最小，并没有说改变边的数量最小，所以小的边随便改
考虑输出方案
我们在拓扑排序的时候记一下每个点的拓扑序
考虑一条边x到y，如果x的拓扑序大于y，显然可能成环（不是一定成环）
但是如果x的拓扑序小于y，一定不会成环
题目有不限制改边数量，我们就将其反向即可

 

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
const int N = 1e5 + 5;
int n, m, maxl = 0, indeg[N], b[N], t;
int head[N], edge[N], leng[N], nxt[N], from[N];
vector<int> ans;
bool v[N], w[N];
queue<int> q;
void add(int x, int y, int z, int i) {
    edge[i] = y;
    leng[i] = z;
    nxt[i] = head[x];
    head[x] = i;
    from[i] = x;
}
bool dfs(int x, int now) {
    v[x] = 1; w[x] = 1;
    for (int i = head[x]; i; i = nxt[i]) {
        int y = edge[i], z = leng[i];
        if (z <= now) continue;
        if (w[y] || !dfs(y, now)) return 0;
    }
    w[x] = 0;
    return 1;
}

inline bool check(int now) {
    memset(v, 0, sizeof(v));
    memset(w, 0, sizeof(w));
    for (int i = 1; i <= n; i++)
        if (!v[i] && !dfs(i, now)) return 0;
    return 1;
}
void topsort(int now) {
    for (int i = 1; i <= n; i++)
        if (!indeg[i]) q.push(i);
    while (q.size()) {
        int x = q.front();
        q.pop();
        b[x] = ++t;
        for (int i = head[x]; i; i = nxt[i]) {
            int y = edge[i], z = leng[i];
            if (z > now && !--indeg[y]) q.push(y);
        }
    }
}

int work(int now) {
    for (int i = 1; i <= m; i++) {
        int y = edge[i], z = leng[i];
        if (z > now) ++indeg[y];
    }
    topsort(now);
    for (int i = 1; i <= n; i++)
        if (!b[i]) b[i] = ++t;
    for (int i = 1; i <= m; i++) {
        int x = from[i], y = edge[i], z = leng[i];
        if (z <= now && b[x] > b[y]) ans.push_back(i);
    }
    return ans.size();
}
int main() {
    cin >> n >> m;
    for (int i = 1, x, y, z; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &z);
        add(x, y, z, i); maxl = max(maxl, z);
    }
    int l = 0, r = maxl;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    cout << l << " " << work(l) << endl;
    for (int i = 0; i < ans.size(); i++) printf("%d ", ans[i]);
    return 0;
}
```

---

## 作者：serverkiller (赞：4)

来自小蒟蒻的一篇题解QwQ

其实这题可以从头到尾都使用拓扑排序。

首先是要求最大边权的最小值，明显是二分找答案。接着对于大于mid的边进行拓扑排序，如果拓扑排序失败，证明有环，便l=mid+1。如果成功，就更新答案。

最后输出的时候不要忘记空格 ~~（我白WA了好几次）~~

这个程序来自@whql
```cpp
#include<bits/stdc++.h>
using namespace std;
int vis[100005],head[100005],nxt[200005],pnt[200005],weight[200005],steins[200005];
int in[100005],E=0,id[100005];
int cg[100005],k=0,ansk,anscg[100005];
int n,m,maxn=0;
queue<int>q;
void add_edge(int a,int b,int c,int kkk)
{
	pnt[E]=b;
	nxt[E]=head[a];
	weight[E]=c;
	steins[E]=kkk;
	head[a]=E++;
}
bool check(int mid)
{
	int kc=0;
	memset(in,0,sizeof(in));
	memset(vis,0,sizeof(vis));
	memset(id,0,sizeof(id));
	k=0;
	for(int i=1;i<=n;++i)
	{
		for(int j=head[i];j!=-1;j=nxt[j])
		{
			if(weight[j]<=mid)continue;
			int v=pnt[j];
			++in[v];
		}
	}
	for(int i=1;i<=n;++i)
	{
		if(!in[i])
		{
			q.push(i);
		}
	}
	while(!q.empty())
	{
		int now=q.front();
		vis[now]=1;
		id[now]=++kc;
		q.pop();
		for(int i=head[now];i!=-1;i=nxt[i])
		{
			if(weight[i]<=mid)continue;
			int v=pnt[i];
			--in[v];
			if(!in[v])
			{
				q.push(v);
			}
		}
	}
	for(int i=1;i<=n;++i)
	{
		if(vis[i]==0)return 0;
	}
	for(int i=1;i<=n;++i)
	{
		for(int j=head[i];j!=-1;j=nxt[j])
		{
			if(weight[j]>mid)continue;
			int v=pnt[j];
			if(id[v]<id[i])
			{
				cg[++k]=steins[j];
			}
		}
	}
	return 1;
}
int main()
{
	memset(head,-1,sizeof(head));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		add_edge(a,b,c,i);
		maxn=max(maxn,c);
	}
	int l=0,r=maxn,ans=0;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid))
		{
			r=mid-1;
			ans=mid;
			ansk=k;
			for(int i=1;i<=ansk;++i)anscg[i]=cg[i];
		}
		else
		{
			l=mid+1;
		}
	}
	sort(anscg+1,anscg+ansk+1);
	printf("%d %d\n",ans,ansk);
	for(int i=1;i<=ansk;++i)printf("%d ",anscg[i]);
	return 0;
}
```
经过精简：
```cpp
#include<bits/stdc++.h>
using namespace std;
int head[100005],nxt[200005],pnt[200005],weight[200005],steins[200005];
int in[100005],E=0,id[100005];
int cg[100005],k=0;
int n,m;
queue<int>q;
void add_edge(int a,int b,int c,int kkk)
{
    pnt[E]=b;
    nxt[E]=head[a];
    weight[E]=c;
    steins[E]=kkk;
    head[a]=E++;
}
bool check(int mid)
{
    int kc=0;
    memset(in,0,sizeof(in));
    memset(id,0,sizeof(id));
    for(int i=1;i<=n;++i)
    {
        for(int j=head[i];j!=-1;j=nxt[j])
        {
            if(weight[j]<=mid)continue;
            int v=pnt[j];
            ++in[v];
        }
    }
    for(int i=1;i<=n;++i)
    {
        if(!in[i])
        {
            q.push(i);
        }
    }
    int cnt = 0;
    while(!q.empty())
    {
        int now=q.front();
        id[now]=++kc;
        cnt++
        q.pop();
        for(int i=head[now];i!=-1;i=nxt[i])
        {
            if(weight[i]<=mid)continue;
            int v=pnt[i];
            --in[v];
            if(!in[v])
            {
                q.push(v);
            }
        }
    }
    if (cnt != n) return 0;
    k = 0;
    for(int i=1;i<=n;++i)
    {
        for(int j=head[i];j!=-1;j=nxt[j])
        {
            if(weight[j]>mid)continue;
            int v=pnt[j];
            if(id[v]<id[i])
            {
                cg[++k]=steins[j];
            }
        }
    }
    return 1;
}
int main()
{
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    int r = 0;
    for(int i=1;i<=m;++i)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        add_edge(a,b,c,i);
        r=max(r,c);
    }
    int l=0,ans=0;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(check(mid))
        {
            r=mid-1;
            ans=mid;
        }
        else
        {
            l=mid+1;
        }
    }
    sort(cg+1,cg+k+1);
    printf("%d %d\n",ans,k);
    for(int i=1;i<=k;++i)printf("%d ",cg[i]);
    return 0;
}
```

---

## 作者：xixike (赞：3)

[博客食用更佳](https://www.cnblogs.com/xixike/p/15496715.html)

# Description

> [洛谷传送门](https://www.luogu.com.cn/problem/CF1100E)

# Solution

看到**最大值最小**这样的字眼，自然想到**二分答案**。

我们二分所选边权的最大权值，那么比这个值大的边都不能反向，小于等于它的边都可以选择反向。

设当前二分到的权值为 $mid$，我们不用去管**小于等于** $mid$ 的边（总有方法让它形成不了环），所以我们把**大于** $mid$ 的边全都加进去，利用拓扑排序来判断是否有负环。

具体方法：把进队的点的个数统计出来为 $sum$，判断是否等于 $n$。

- 若 $sum < n$，有环。

- 若 $sum = n$，无环。

符合条件的情况下我们就该找哪些边需要反向了。

由于题目中并没有最小化反向边的数量之类的要求，所以我们可以把所有会造成环的边全部反向。

那么有哪些边会形成环呢？

还是拓扑排序，当我们对大于 $mid$ 的边所形成的图进行拓扑排序时，记录一下它在拓扑序中的位置，即拓扑序。

假设有 $x$，$y$ 两点，且拓扑序 $dfn_y < dfn_x$，此时如果有一条从 $x$ 连到 $y$ 的边，那么这条边就会形成负环，就要给它反向。

所以在合法的 $mid$ 下遍历一遍所有的边，判一下拓扑序即可，注意边权要小于等于 $mid$。

# Code

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

const int N = 1e5 + 10;
struct node{
    int u, v, w, nxt;
}edge[N];
int head[N], tot;
int n, m, tim;
bool vis[N], t[N];
int in[N], dfn[N];
int ans[N], cnt;

inline void add(int x, int y, int z){
    edge[++tot] = (node){x, y, z, head[x]};
    head[x] = tot;
}

inline int topo(int now){
    int sum = 0;
    queue <int> q;
    for(int i = 1; i <= n; ++i)
        if(!in[i]) q.push(i);
    while(!q.empty()){
        int x = q.front();
        q.pop();
        sum++, dfn[x] = ++tim;
        for(int i = head[x]; i; i = edge[i].nxt){
            int y = edge[i].v;
            if(edge[i].w <= now) continue;
            if(!(--in[y])) q.push(y);
        }
    }
    return sum >= n;
}

inline bool check(int now){
    memset(in, 0, sizeof(in));
    memset(dfn, 0, sizeof(dfn));
    tim = 0;
    for(int i = 1; i <= m; ++i)
        if(edge[i].w > now) in[edge[i].v]++;
    if(!topo(now)) return 0;
    cnt = 0;
    for(int i = 1; i <= n; ++i)
        if(!dfn[i]) dfn[i] = ++tim;
    for(int i = 1; i <= m; ++i){
        int u = edge[i].u, v = edge[i].v;
        if(edge[i].w <= now && dfn[u] > dfn[v])
            ans[++cnt] = i;
    }
    return 1;
}

int main(){
    int l = 0, r = 0, maxs = 0;
    scanf("%d%d", &n, &m);
    for(int i = 1, u, v, w; i <= m; ++i){
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w);
        r = max(r, w);
    }
    while(l <= r){
        int mid = (l + r) >> 1;
        if(check(mid)) maxs = mid, r = mid - 1;
        else l = mid + 1;
    }
    printf("%d %d\n", maxs, cnt);
    sort(ans + 1, ans + 1 + cnt);
    for(int i = 1; i <= cnt; ++i)
        printf("%d ", ans[i]);
    puts("");
    return 0;
}
```



# End

---

## 作者：pikabi (赞：3)

**题意**：给定一个有向图，改变其中某些边的方向，它将成为一个有向无环图。现在求一个改变边方向的方案，使得所选边边权的最大值最小。



------------


**输出**：边权的最小值，被反向的边的个数及编号。


------------


**Solution**：只要二分把每一条边和预期的 $val$ 个controllers 作比较，只让大于它的边联通，判断有无环即可（该部分的正确性其他题解已经讲得很清楚了，此不再赘述）。最后用拓扑判断是否使这些边反向即可。但是关于每次判断边是否遍历过，我发现每一篇题解都用 memset 来归零，这样如果范围过大不免导致被卡。所以我们可以采用 $tot$ 作为第 $tot$ 次二分时的标记，如果 $pre_{p} \not= tot$ ,就代表这一次没有经历过。同时，我们可以通过 $vis_{to}$ 的非 0 来判断其有无环。（别忘了清零哦！）这样，我们就省去了每次 memset 的损耗了。



------------
**more**：如果想要追求极致的话可以尝试离散化取值。（~~我因为太懒就懒得弄了~~）

code-->

```cpp
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cctype>
#include <cstring>
#define PT 520

using namespace std;

struct node{
	int to, nxt, v;
}e[1000005];

queue <int> que;

int n, m, head[1000005], cnt, l, r, vis[1000005], pre[1000005], tot;
int sum, ans[1000005], ppp, minn = 1023456789, dfn[1000005], id[1000005];

inline void add(int from, int to, int v){
	e[++cnt].nxt = head[from];
	head[from] = cnt;
	e[cnt].to = to;
	e[cnt].v = v;
}

inline int dfs(int p, int val){
	pre[p] = tot;
	vis[p] = 1;
	for(int i = head[p]; i; i = e[i].nxt ){
		if(e[i].v > val){
			if(pre[e[i].to] == tot && !vis[e[i].to ]){
				continue;
			}
			if((pre[e[i].to ] == tot && vis[e[i].to ]) || dfs(e[i].to , val)) return 1;
		}
	}
	vis[p] = 0;
	return 0;
}

inline void work(int val){
	for(int i = 1; i <= m; i++)
	if(e[i].v > val) dfn[e[i].to ]++;
	for(int i = 1; i <= n; i++)
	if(!dfn[i]) que.push(i);
	while(!que.empty()){
		int u = que.front();
		que.pop();
		id[u] = ++sum;
		for(int i = head[u]; i; i = e[i].nxt ){
			if(e[i].v > val){
				dfn[e[i].to ]--;
				if(!dfn[e[i].to ]) que.push(e[i].to );
			}
		}
	}
}

int read()        
{        
    int s = 0, f = 1;        
    char ch = getchar();        
    while(!isdigit(ch)) {        
        if(ch == '-') f = -1;        
        ch = getchar();        
    }        
    while(isdigit(ch)) {        
        s = s * 10 + ch - '0';        
        ch = getchar();        
    }        
    return s * f;        
}        

int main(){
	n = read(), m = read();
	for(int i = 1; i <= m; i++){
		int x = read(), y = read(), z = read();
		add(x, y, z);
		r = max(r, z);
	}
	l = 0;
	int fl;
	while(l < r){
		fl = 0;
		tot++;
		sum = 0;
		int mid = (l + r) >> 1;
		for(int i = 1; i <= n; i++){
			if(pre[i] != tot && dfs(i, mid)){
					fl = 1;
					break; 
			}
		}
		if(!fl){
			r = mid;
		}
		else {
			l = mid + 1;
		}
	}
	printf("%d ",r);
	sum = 0;
	work(r);
	for(int i = 1; i <= n; i++){
		for(int j = head[i]; j; j = e[j].nxt ){
			if(e[j].v <= r){
				if(id[e[j].to ] < id[i]){
					ans[++ppp] = j;
				}
			}
		}
	}
	printf("%d\n",ppp);
	sort(ans + 1, ans + ppp + 1);
	for(int i = 1; i <= ppp; i++)
	printf("%d ",ans[i]);
	return 0;
} 
```

完结撒 fā ✿✿ヽ(°▽°)ノ✿


---

## 作者：fzj2007 (赞：2)

看到了最大值最小，考虑二分最大的边权。

如果最大的边权 $k$ 使得图中不存在环，则 $x(x \ge k)$ 也一定可以使得图中不存在环。

即满足二分的性质。下面考虑如何 $\text{check}$ 边权为 $k$ 是否合法。

首先给出一个结论：

> 对于一条边，把他删掉和将他反向是等价的。

证明：

1. 如果出现了一条边出现在两个不同向的环中（即不管如何标向都会出现环，例如下图中的最粗边），可以发现去掉这条边依然存在一个环。

![](https://cdn.luogu.com.cn/upload/image_hosting/pupgfxo9.png)

2. 若不存在 $1$ 中的情况，则一定可以通过调整方向使得所在环消失。

这样，只需要再权值大于 $k$ 的边上查询是否有环即可。

考虑这个问题，可以使用拓扑排序解决。如果拓扑序中存在所有点，则一定不存在环。否则一定存在环。

输出方案时，对于一条边 $x,y$，若存在一条边 $(x,y)$，当 $\text{dfn}_y<\text{dfn}_x$ 时，意味着 $y$ 先被遍历。若此时加上边 $(x,y)$，则可能出现环。故此时应将边 $(x,y)$ 反向。

代码：
```
#include<bits/stdc++.h>
using namespace std;
namespace IO{
    template<typename T>inline void read(T &x){
        x=0;
        char ch=getchar();
        bool flag=0;
        while(ch<'0'||ch>'9') flag=flag||(ch=='-'),ch=getchar();
        while(ch>='0'&&ch<='9') x=x*10+(ch^'0'),ch=getchar();
        if(ch!='.'){
            x=flag?-x:x;
            return;
        }
        double Base=0.1;
        while(ch<'0'||ch>'9') ch=getchar();
        while(ch>='0'&&ch<='9') x=x+Base*(ch^'0'),Base/=10.0,ch=getchar();
        x=flag?-x:x;
    }
    template<typename T>void prt(T x){
        if(x>9) prt(x/10);
        putchar(x%10+'0');
    }
    template<typename T>inline void put(char ch,T x){
        if(x<0) putchar('-'),x=-x;
        prt(x);
        putchar(ch);
    }
    const int DM[10]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
    inline void putd(char ch,double x,int w){
        if(x<0) putchar('-'),x=-x;
        if(!w){
            put(ch,(int)(x+0.5));
            return;
        }
        int prex=(int)x;
        x-=(int)x;
        x*=DM[w];
        x+=0.5;
        int nowx=(int)x,now=0;
        if(nowx>=DM[w]) nowx=0,prex++;
        put('.',prex);
        int xx=nowx;
        if(!xx) now=1;
        else while(xx) xx/=10,now++;
        now=w-now;
        while(now--) putchar('0');
        put(ch,nowx);
    }
    inline void putstr(string s){
        for(int i=0;i<s.length();i++) putchar(s[i]);
    }
}
using namespace IO;
#define N 100005
int n,m,head[N],cnt,l=0,r,ans,deg[N],st[N],tp,dfn[N];
struct edge{
	int v,nxt,val;
}e[N<<1];
inline void add(int u,int v,int w){
	e[++cnt]=(edge){v,head[u],w},head[u]=cnt,r=max(r,w);
}
int q[N];
inline bool check(int k){
	memset(deg,0,sizeof(deg));
	int hh=1,tt=0,idx=0;
	for(int i=1;i<=cnt;i++)
		if(e[i].val>k) deg[e[i].v]++;
	for(int i=1;i<=n;i++)
		if(!deg[i]) q[++tt]=i;
	while(hh<=tt){
		int x=q[hh++];
		dfn[x]=++idx;
		for(int i=head[x];i;i=e[i].nxt){
			int v=e[i].v;
			if(e[i].val<=k) continue;
			if(!--deg[v]) q[++tt]=v;
		}
	}
	for(int i=1;i<=n;i++)
		if(deg[i]) return 0;
	tp=0;
	for(int x=1;x<=n;x++)
		for(int i=head[x];i;i=e[i].nxt){
			int v=e[i].v;
			if(e[i].val>k) continue;
			if(dfn[x]>dfn[v]) st[++tp]=i;
		}
	return 1; 
}
int main(){
	read(n),read(m);
	for(int i=1,u,v,w;i<=m;i++) read(u),read(v),read(w),add(u,v,w); 
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	put(' ',ans),put('\n',tp);
	sort(st+1,st+tp+1);
	for(int i=1;i<=tp;i++) put(' ',st[i]);
	return 0;
}

```


---

## 作者：wwlw (赞：1)

2020.11.3

[Link](https://www.luogu.com.cn/problem/CF1100E)
----------

### 题目描述
给定一个有向图，改变其中某些边的方向，它将成为一个有向无环图。现在求一个改变边方向的方案，使得所选边边权的最大值最小。

### 解法
容易发现对于一条边，把其删去和把其反向其实是等价的。若不翻转之前，这条边仅处于一个简单环里，那么反过来之后一定不会组成新环。若反过来之后组成了一个新的环，那么不看这条边原图里一定构成了另一个环（画图）。所以对于反向操作直接不走它即可。

若选定了一条边其权值为 $v_i$，那么权值小于等于 $v_i$ 的边都可删可不删，就没有约束条件。若选最大的边，那么所有边都可删可不删，一定可以满足要求。而若选择最小的边，只有最小的边能删，约束条件很强。容易发现这是由单调性的，而边权限制在 $10^9$ 内，可以直接进行二分了。而对于每次二分，不走权值小于等于 $mid$ 的边，判断是否有环即可，可用 $tarjan$ 或拓扑排序。

对于第二问，需要求一种具体方案，只能用拓扑。先 $check$ 一下 $ans$，把最后的图建出来，此时一定是没有环的，那么这一定是一个 $DAG$。对它进行一遍拓扑，求出拓扑序。枚举原图中每条有向边 $u\to v$，若 $u$ 的拓扑序比 $v$ 的大，说明 $v$ 要比 $u$ 先被更新，所以这条边一定要反过来。

```cpp
#include<stdio.h>
#include<string.h>
#define N 200007
#define M 300007

inline int read(){
    int x=0; bool flag=1; char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')flag=0;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-48;c=getchar();}
    return flag? x:-x;
}

struct E{
    int next,to;
}e[M];
int head[N],cnt=0;

inline void add(int id,int to){
    e[++cnt]=(E){head[id],to};
    head[id]=cnt;
}

int X[M],Y[M],D[M];
int n,m,dep[N],in[N],sta[N],top=0;
bool check(int lim){
    memset(in,0,sizeof(in));
    memset(head,0,sizeof(head));
    cnt=0,top=0;
    int timer=0;
    for(int i=1;i<=m;i++)
        if(D[i]>lim) add(X[i],Y[i]),in[Y[i]]++;
    for(int i=1;i<=n;i++)
        if(!in[i]) sta[++top]=i,dep[i]=++timer;
    while(top){
        int u=sta[top--];
        for(int i=head[u];i;i=e[i].next){
            int v=e[i].to;
            if(--in[v]) continue;
            sta[++top]=v,dep[v]=++timer;
        }
    }
    for(int i=1;i<=n;i++)
        if(in[i]) return 0;
    return 1;
}

int main(){
//    freopen("pestc.in","r",stdin);
//    freopen("pestc.out","w",stdout);
    n=read(),m=read();
    int l=0,r=0,ans;
    for(int i=1;i<=m;i++){
        X[i]=read(),Y[i]=read(),D[i]=read();
        if(D[i]>r) r=D[i];
    }
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)) ans=mid,r=mid-1;
        else l=mid+1;
    }
    printf("%d",ans);
    check(ans);
    int ret=0;
    for(int i=1;i<=m;i++)
        if(D[i]<=ans&&dep[X[i]]>dep[Y[i]]) ret++;
    printf(" %d\n",ret);
    for(int i=1;i<=m;i++)
        if(D[i]<=ans&&dep[X[i]]>dep[Y[i]])
            printf("%d ",i);
} 
```

---

## 作者：FiraCode (赞：1)

## 题解思路：
样例：

![](https://cdn.luogu.com.cn/upload/image_hosting/b1c2sunk.png)

前置知识：

>图中无环的条件是什么？

>就是一个点无法走一圈回到自己，他就无环。

>那么有一个算法：topsort（拓扑排序）

>topsort 就会给每个节点一个拓扑值

>图例：

>![](https://cdn.luogu.com.cn/upload/image_hosting/jp7ph9rm.png)

>若一个图有环，那么他就没有拓扑序，因为他所有的点的入度都 $\ne 0$。

>若一个点有一个起点终点 $\langle u , v\rangle$，若 $top_{u} < top_{v}$，那么这个图就是无环的。

>或拓扑排序不能让他的入度为 $0$，那么他就是有环的。

### 然后我们来看一下这个题怎么做：

首先他让我们求最大值最小，那么根据经验应该是二分答案。

然后我们就上那方面上想。

把他得到的权值设成 $mid \longrightarrow$ 图中改变方向的边的权值最大值。

我们设 $w$ 为某个点的权值。

我们就先二分答案：
>$w\le mid$ 不加进图，就相当于把他删掉。

>$w > mid$ 按原样加进图。

判定：

>若我们把 $\le mid$ 的边都删掉，他还是有环，那么就是删的边数太少了，那么把删边数的多一点。

>若没有环了，就让答案的权值小一点。

若我们求出来了一个 $mid \longrightarrow$ 保证图中无环

$w \le mid$ 我们就把他看作无向边。

那么我们要反转那些边呢？？

拓扑排序出来的数组 $top$，若 $top_{u} > top_{v}$ 那么我们就反转这条边。


[AC CODE](https://codeforces.com/contest/1100/submission/155561184)

码字不易，求赞！

---

## 作者：jins3599 (赞：0)

蛮有趣的一道二分答案。

首先题目已经把单调性很明显的写出来了，于是我们的重点放在了如何`check`答案上面。

首先，我们要二分这个最大边权时不用质疑的，但是反转边真的是太棘手了。如何解决？

我们首先考虑无法达成的情况，也就是说，图中一定会存在一条小于等于$mid$边，无论如何反转，永远都会出现环。

什么情况下会出现这种情况？（绕口令hhh

显然就是删去这条边后的原图中本来就有环！即使这条边在环中也不会对环产生任何影响！

于是思路就清晰了，我们每次二分答案后删去所有小于等于mid的边，然后用dfs找环即可。

输出答案呢？我们二分完答案之后，对新图进行一次拓扑排序（就是把小于等于答案的边删去），于是我们再对小于等于答案的所有边进行检查，如果某一条边的起点的拓扑序大于终点的拓扑序，那么这条边一定要被反转，否则就会成环。

然后这道题就又被切掉了，皆大欢喜。

```cpp
#include <bits/stdc++.h>
#define il inline 
using namespace std;

const int N = 1e5 + 10;

int head[N] , cnt;
struct Edge {
	int w ,  from, to , nxt;
}e[N << 1];

il void add(int u , int v , int w) {
	e[++ cnt].to = v;
	e[cnt].from = u;
	e[cnt].w = w;
	e[cnt].nxt = head[u];
	head[u] = cnt;
} 

int l = 0 , r , ans , flag , n , m;
bool vis[N];

void dfs(int now , int lim) {
	if(flag) return;
	vis[now] = 1;
	for(int i = head[now] ; i ; i = e[i].nxt) {
		int v = e[i].to , w = e[i].w;
		if(w <= lim) continue;
		if(vis[v] == 1) {flag = 1; return;}
		dfs(v , lim); 
	}
	vis[now] = 0;
}

bool check(int x) {
	memset(vis , 0 , sizeof(vis));
	flag = 0;
	for(int i = 1 ; i <= n ; i++) if(!vis[i]) {
		dfs(i , x); if(flag) return false;
	}
	return true;
}

int tot , edge[N] , ind[N] , dep[N];
void toposort() {
	for(int i = 1 ; i <= n ; i ++) {
		for(int j = head[i] ; j ; j = e[j].nxt) {
			int v = e[j].to , w = e[j].w;
			if(w <= ans) continue;
			ind[v] ++;
		}
	}
	queue <int> q;
	int p = 0;
	for(int i = 1 ; i <= n ;i ++) if(!ind[i]) q.push(i);
	while(! q.empty()) {
		int now = q.front(); q.pop();
		dep[now] = ++ p;
		for(int i = head[now] ; i ; i = e[i].nxt) {
			int v = e[i].to , w = e[i].w;
			if(w <= ans) continue;
			if(!--ind[v]) q.push(v) ;
		} 
	}
	for(int i = 1 ; i <= n ; i ++ ) if(!dep[i]) dep[i] = p + 1;
	for(int i = 1 ; i <= cnt ;i ++) {
		if(e[i].w <= ans) {
			if(dep[e[i].from] > dep[e[i].to]) edge[++ tot] = i;
		}
	}
}

int main () {
	scanf("%d %d" , &n, &m);
	while(m --) {
		int u , v , w;
		scanf("%d %d %d" , &u,&v,&w);
		add(u,v,w); r = max(r ,  w);
	}
	while(l <= r) {
		int mid = (l + r) >> 1;
 		if(check(mid)) ans = mid , r = mid - 1;
		else l = mid + 1;
	}
	toposort();
	printf("%d %d\n" , ans , tot);
	for(int i = 1 ; i <= tot ; i ++) printf("%d " , edge[i]);
 	return 0;
}

```

---

## 作者：_lxy_ (赞：0)

### 题意

⼀个有向图，改变⼀些边的⽅向，使得图中没有环，求使得所选边边权最大值最⼩的⽅案。

### 分析

如果边权最大值小的可行，那最大值更大的也一定可行。因此可以二分边权最大值，每次把边权比最大值大的加入图中，如果没有环，那把所有没加的边的方向都改成拓扑序的方向就一定可以满足，如果有环说明不可行。二分出来最小的最大值后，重新建图，把所有与拓扑序相反的边反转方向即可。

### 代码

```cpp
#include <bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
inline void qread(){}template<class T1,class ...T2>
inline void qread(T1 &a,T2&... b)
{
    register T1 x=0;register bool f=false;char ch=getchar();
    while(ch<'0') f|=(ch=='-'),ch=getchar();
    while(ch>='0') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    x=(f?-x:x);a=x;qread(b...);
}
template<class T1,class T2>inline T1 qmax(const T1 &x,const T2 &y){return x>y?x:y;}
template<class T1,class T2>inline T1 qmin(const T1 &x,const T2 &y){return x<y?x:y;}
const int MAXN=1e5+7;
int n,m,head[MAXN];
struct Edge
{
    int to,nxt,dis,id;
    Edge(){;}Edge(int _to,int _dis,int _nxt,int _id):to(_to),dis(_dis),nxt(_nxt),id(_id){}
};vector<Edge>edge;
void add_edge(int u,int v,int w,int id){edge.push_back(Edge(v,w,head[u],id));head[u]=edge.size()-1;}
int in[MAXN],ans=2139062143;
vector<int>topo;
int topo_sort()
{
    topo.clear();int i;queue<int>q;
    for(i=1;i<=n;i++) if(!in[i]) q.push(i);
    while(!q.empty())
    {
        int u=q.front();q.pop();topo.push_back(u);
        for(i=head[u];i!=-1;i=edge[i].nxt) if(!(--in[edge[i].to])) q.push(edge[i].to);
    }
    return topo.size();
}
int x[MAXN],y[MAXN],z[MAXN];
void make(int mid) // 建图
{
    edge.clear();mem(head,-1);mem(in,0);
    for(int i=0;i<m;i++)
        if(z[i]>mid) add_edge(x[i],y[i],z[i],i+1),in[y[i]]++;
}
bool check(int mid)
{
    make(mid);
    return topo_sort()==n; // 如果topo数组中包含所有点，说明没有环
}
int mp[MAXN];set<int>ans1;
int main()
{
    qread(n,m);int i,j;
    int l=0,r=0;
    for(i=0;i<m;i++) qread(x[i],y[i],z[i]),r=qmax(r,z[i]); // 输入时将二分的上限定为最大边权
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(check(mid)) r=mid-1,ans=qmin(ans,mid);
        else l=mid+1;
    }
    check(ans);
    for(int i=0;i<topo.size();i++) mp[topo[i]]=i; // 记录每个点在拓扑序中的位置
    make(0); // 重建图，加入每条边
    for(i=1;i<=n;i++)
        for(j=head[i];j!=-1;j=edge[j].nxt)
            if(mp[i]>mp[edge[j].to]) ans1.insert(edge[j].id); // 该边方向与拓扑序相反
    printf("%d %d\n",ans,ans1.size());
    for(auto i:ans1) printf("%d ",i);
    return 0;
}
```




---

