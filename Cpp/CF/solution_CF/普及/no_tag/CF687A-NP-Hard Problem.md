# NP-Hard Problem

## 题目描述

最近，Pari和Arya对NP-Hard问题进行了一些研究，他们发现最小顶点覆盖问题非常有趣。

对于给定的图$G$，其顶点集合的子集$A$被称为此图的一个顶点覆盖，当且仅当对于图中的每条边$uv$，其都有至少一个顶点在此子集中，即$u \in A$或$v \in A$（或二者皆符合）

Pari和Arya在一场团队比赛中赢得了一个很棒的无向图作为奖励。现在他们要把它分成两份，但他们两个都想让自己的那份是这个图的一个顶点覆盖。

他们同意将他们的图给你，而你需要找到此图的两个不相交的顶点集合$A$和$B$并令$A$和$B$都是此图的一个顶点覆盖，或说明这是不可能的。图的每个顶点都应该被给予两人中的至多一人（当然你也可以自己留着）。

## 样例 #1

### 输入

```
4 2
1 2
2 3
```

### 输出

```
1
2 
2
1 3 
```

## 样例 #2

### 输入

```
3 3
1 2
2 3
1 3
```

### 输出

```
-1
```

# 题解

## 作者：Edmundino (赞：11)

这是一道考二分图的题，也就是判断二分图

首先我们先考虑算法，

二分图有三种解决方式：dfs，bfs，并查集

为了简单明了，我用dfs来解这道题

数据很大，所以我们不能用连接矩阵来解这道题

但是我们可以用vector,~~别忘了打头文件~~

```cpp
bool dfs(int x,int w)
{
	a[x]=w;//把x的点染成w
	int len=q[x].size();
	for(int i=0;i<len;i++)//dfs遍历整个图
	{
		if(a[q[x][i]]==-1)//等于-1是未染色
		{
			 if(!dfs(q[x][i],1-a[x])) return false;
		}
		else if(a[q[x][i]]==a[x]) return false; 
	}
	return true;
}

```
dfs打好，整道题就差不多打好了

先看一个标准的错误代码

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<iomanip>
#include<cmath>
#include<vector>
#include<queue>

using namespace std;

int n,m,a[100005],c[100005],d[100005],topc,topd,r,w,zs;

vector<int> q[100005];

bool dfs(int x,int w)
{
	a[x]=w;
	int len=q[x].size();
	for(int i=0;i<len;i++)
	{
		if(a[q[x][i]]==-1)
		{
			 if(!dfs(q[x][i],1-a[x])) return false;
		}
		else if(a[q[x][i]]==a[x]) return false; 
	}
	return true;
}

int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
//		cout<<1;
		cin>>r>>w;
		q[r].push_back(w);
		q[w].push_back(r);
	}
	memset(a,-1,sizeof(a));
	if(!dfs(1,0))
	{
		cout<<-1;
		return 0;
	}
	   
	
	for(int i=1;i<=n;i++)
	{
//		cout<<a[i]<<" ";
		if(a[i]==0)
		  c[++topc]=i;
		if(a[i]==1)
		  d[++topd]=i;
	}
	cout<<topc<<endl;
	for(int i=1;i<=topc;i++)
    {
    	cout<<c[i]<<" ";
	}
	cout<<endl<<topd<<endl;
	for(int i=1;i<=topd;i++)
	{
		cout<<d[i]<<" ";
	}
	return 0;
}
```
知道哪错了吗

```cpp
if(!dfs(1,0))
	{
		cout<<-1;
		return 0;
	}
```
这里，不应该写dfs（1，0）

为什么？

因为它不一定是一个连通图

如果有一种情况

![](https://cdn.luogu.com.cn/upload/image_hosting/y07baoyg.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这样，你就只遍历了1这个图

4的图便没遍历

所以我们应该这样子写

```cpp
for(int i=1;i<=n;i++)
	{
		if(a[i]==-1)
     	  if(!dfs(i,0))
	      {
		     cout<<-1;
		     return 0;
	      }
	 		
	}
  
```
最后送上AC代码

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<iomanip>
#include<cmath>
#include<vector>
#include<queue>

using namespace std;

int n,m,a[100001],c[100001],d[100001],topc=0,topd=0,r,w;

vector<int> q[100001];

bool dfs(int x,int w)
{
	a[x]=w;
	int len=q[x].size();
	for(int i=0;i<len;i++)
	{
		if(a[q[x][i]]==-1)
		{
			 if(!dfs(q[x][i],1-a[x])) return false;
		}
		else if(a[q[x][i]]==a[x]) return false; 
	}
	return true;
}

int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
//		cout<<1;
		cin>>r>>w;
		q[r].push_back(w);
		q[w].push_back(r);
	}
	memset(a,-1,sizeof(a));
	for(int i=1;i<=n;i++)
	{
		if(a[i]==-1)
     	  if(!dfs(i,0))
	      {
		     cout<<-1;
		     return 0;
	      }
	 		
	}
  
	
	for(int i=1;i<=n;i++)
	{
//		cout<<a[i]<<" ";
		if(a[i]==0)
		  c[++topc]=i;
		if(a[i]==1)
		  d[++topd]=i;
	}
	cout<<topc<<endl;
	for(int i=1;i<=topc;i++)
    {
    	cout<<c[i]<<" ";
	}
	cout<<endl<<topd<<endl;
	for(int i=1;i<=topd;i++)
	{
		cout<<d[i]<<" ";
	}
	return 0;
}
```


---

## 作者：jch123 (赞：3)

# 题意

给你一些点，问你能不能组成一个二分图。

# 思路

暴搜即可，对每个点进行染色，注意区分好颜色。用邻接表建图，细节注释里都有。


# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
vector<int> h[N],ans[3];
bool vis[N];
int book[N];
int n,m;
bool dfs(int u,int k)
{
    vis[u]=1;//标记有没有用过
    book[u]=k;//标记颜色 
    ans[k].push_back(u);//对答案贡献 
    for(auto x:h[u])
    {
        if(vis[x]==0)//没有被标记过 
        {
            if(k==1&&dfs(x,2)) return true;
            if(k==2&&dfs(x,1)) return true;
	}
        else if(vis[x]&&book[x]==k)//标记过但在一个块里面 
            return true;
    }
    return false;
}
int main()
{
    ios::sync_with_stdio(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        int a,b;
        cin>>a>>b;
        h[a].push_back(b);//建图 
        h[b].push_back(a);
    }
    for(int i=1;i<=n;i++)
    {
        if(h[i].size()>0&&vis[i]==0)//这个点与别的点相连且没有被标记 
        {
            if(dfs(i,1))//不符合 
            {
                cout<<-1;
                return 0;
            }
        }
    }
    cout<<ans[1].size()<<endl;
    for(auto x:ans[1])
    	cout<<x<<" ";
    cout<<endl;
    cout<<ans[2].size()<<endl;
    for(auto x:ans[2])
        cout<<x<<" ";
    cout<<endl;
    return 0;
}
```



---

## 作者：mot1ve (赞：2)

没有用前向星写的，蒟蒻不会vector，写了个前向星造福大家。

此题就是考察二分图的判定，我们知道，一个图如果是二分图那么它一定没有点为奇数的环。因为一个点为奇数的环中，必定有一个点的相邻点既有黑也有白，不可能符合二分图的条件。所以直接dfs染色就行。

这个样例1有问题，没有4这个点，输出应该是我这个程序的输出，亲测AC。

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,m;
struct node{
	int nxt,to;
}edge[200010];
int head[100010],color[100010];
int idx,ans1,ans2;
void add(int u,int v)
{
	edge[++idx].nxt=head[u];
	edge[idx].to=v;
	head[u]=idx;
}
int dfs(int x)
{
	for(int i=head[x];i;i=edge[i].nxt)
	{
		int v=edge[i].to;
		if(color[v]==color[x])
		{
			return 0;
		}
		if(!color[v])
		{
			color[v]=3-color[x];
			if(!dfs(v))
			{
				return 0;
			}
		}
	}
	return 1;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	for(int i=1;i<=n;i++)//染色 1，2，无色为0 
	{
		if(color[i]==0)
		{
			if(head[i]==0)
			{
				color[i]=1;
				continue;
			}
			color[i]=1;
			if(!dfs(i))
			{
				printf("-1");
				return 0;
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(color[i]==1)
		ans1++;
		if(color[i]==2)
		ans2++;
	}
	cout<<ans1<<endl;
	for(int i=1;i<=n;i++)
	{
		if(color[i]==1)
		printf("%d ",i);
	}
	cout<<endl<<ans2<<endl;
	for(int i=1;i<=n;i++)
	{
		if(color[i]==2)
		printf("%d ",i);
	}
	return 0;
} 

---

## 作者：Zenith_Yeh (赞：2)

这道题其实是二分图判定的裸题，在此我用我认为较简单的算法 $DFS$ 来判定二分图即可。

就是把 ~~CZ和面包~~ 看成两种颜色，然后进行二分图判定即可。

**上菜：**
```cpp
#include<bits/stdc++.h> 
using namespace std;
int n,m,u,v,co[100010],blk,wht;
bool vis[100010];
vector<int> a[100010];
bool dfs(int now,int color)//DFS判定。
{   vis[now]=true;co[now]=-color;
    bool ok=true;
    for(int i=0;i<a[now].size();i++)//枚举与它相连的点。
	{   if(!vis[a[now][i]])ok&=dfs(a[now][i],-color);//判定。
        else ok&=(co[now]!=co[a[now][i]]);
    }
    return ok;
}
int main()
{   scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
	{   scanf("%d%d",&u,&v);
        a[u].push_back(v);a[v].push_back(u);//加点。
    }
    for(int i=1;i<=n;i++)
	{   if(!vis[i])//DFS判定。
		{   if(!dfs(i,-1))
			{   printf("-1");
                return 0;
            }
        }
    }
    for(int i=1;i<=n;i++)if(co[i]>0)blk++;//记一下。
    wht=n-blk;printf("%d\n",blk);
    for(int i=1;i<=n;i++)
	{   if(co[i]>0)
		{   printf("%d",i);
            if(--blk)printf(" ");
        }
    }
    cout<<endl;printf("%d\n",wht);
    for(int i=1;i<=n;i++)
	{   if(co[i]<0)
		{   printf("%d",i);
            if(--wht)printf(" ");
        }
    }
    return 0;
}
```


---

## 作者：yyz1005 (赞：1)

前置知识：[带权并查集](https://blog.csdn.net/yjr3426619/article/details/82315133)

题意即判断是否为二分图。

实际上这一题的点可以分为两种（可以随意在哪一个部分的点不讨论）：

1. 在第一部分
2. 在第二部分

那么这一题非常类似于 [P2024 食物链](https://www.luogu.com.cn/problem/P2024)，本体可以将带权并查集的权值模 2，对于新的一条边需要讨论是否合法。

---
## 具体方法
使用 $fa[i]$ 表示第 $i$ 个点的祖先。

使用 $val[i]$ 表示第 $i$ 个点与祖先的关系（0 为在同一部分，1 为在不同部分）。

对于新边的处理：

1. 两点的祖先不同：直接连接，正常计算 val 数组的值。
2. 两点祖先相同：计算新的 val，若矛盾则返回值为 0。

```cpp
bool join(int x,int y){
	int fx = findf(x),fy = findf(y);
	if(fx==fy) return val[y] == (val[x]+1)%2;//特别注意这里要用==来判断图是否仍然合法。
   //具体解释：
   //y---x----fx（即 fy）
   //此时 fx=fy，
   //所以 y 到其祖先的距离为 1+val[x]，
   //假如与原本的值不同就相当于 y 与其祖先既在同一部分由在不同部分，矛盾。
	else {
		fa[fy] = fx;
		val[fy] = ((val[x]+1-val[y])%2+2)%2;
      //这里直接取模结果可能为负数，要再加 2 并除以 2.
		return true;
	}
}
```
---
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int fa[100010],val[100010];
int findf(int x){
	if(x==fa[x]) return x;
	int t = findf(fa[x]);
	val[x]+=val[fa[x]];
	val[x]%=2;
	return fa[x] = t;
}
bool join(int x,int y){
	int fx = findf(x),fy = findf(y);
	if(fx==fy) return val[y] == (val[x]+1)%2;
	else {
		fa[fy] = fx;
		val[fy] = ((val[x]+1-val[y])%2+2)%2;
		return true;
	}
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1; i <= n; i++) fa[i] = i,val[i] = 0;
	for(int i = 1; i <= m; i++){
		int a,b;
		scanf("%d%d",&a,&b);
		if(!join(a,b)){
			printf("-1");
			return 0;
		}
	}
	int k1 = 0,k2 = 0;
	for(int i = 1; i <= n; i++){
		findf(i);//更新出正确的val[i]
		if(val[i]==0) k1++;
		else k2++; 
	}
	printf("%d\n",k1);
	for(int i = 1; i <= n; i++){
		if(val[i]==0) printf("%d ",i);
	}
	printf("\n%d\n",k2);
	for(int i = 1; i <= n; i++){
		if(val[i]==1) printf("%d ",i);
	}
	return 0;
}
```

---

## 作者：Mr_QwQ (赞：1)

蒟蒻来发一篇题解，qwq……

考虑这个图的每一条边。如果两个人都需要覆盖集，那么两个点不可能同时给一个人（否则另一个人盖不到这个点了）。

所以要把原图分成两个不相交的点集，并且同一个人的两个点之间不会有边。

不就是个二分图么……

瞎dfs一遍就搞定了。

代码：
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
int n,m,u,v,co[100010],blk,wht;
bool vis[100010];
vector<int> a[100010];
bool dfs(int now,int color){
    vis[now]=true;co[now]=-color;
    bool ok=true;
    for(int i=0;i<a[now].size();i++){
        if(!vis[a[now][i]])ok&=dfs(a[now][i],-color);
        else ok&=(co[now]!=co[a[now][i]]);
    }
    return ok;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&u,&v);
        a[u].push_back(v);a[v].push_back(u);
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            if(!dfs(i,-1)){
                printf("-1");
                return 0;
            }
        }
    }
    for(int i=1;i<=n;i++)if(co[i]>0)blk++;
    wht=n-blk;printf("%d\n",blk);
    for(int i=1;i<=n;i++){
        if(co[i]>0){
            printf("%d",i);
            if(--blk)printf(" ");
        }
    }
    cout<<endl;printf("%d\n",wht);
    for(int i=1;i<=n;i++){
        if(co[i]<0){
            printf("%d",i);
            if(--wht)printf(" ");
        }
    }
    return 0;
}
```
谢谢大家……qwqqwq

---

## 作者：qfy123 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF687A)
# 前置知识
[二分图的判定](https://blog.csdn.net/weixin_45895026/article/details/105237591)
# 题意简述
给定一张 $n$ 个点 $m$ 条边的**无向图**，判定其是否构成二分图。如果构成，输出两个点集的大小与内容。

$(2\le n \le 10^5,1 \le m \le 10^5)$ 
# 实现
染色法判定二分图。通过 dfs 将点染成两种颜色，若出现一条边连接着两个已经染色的点并且它们的颜色相同，则一定不是二分图。实现细节具体见代码。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
struct E{
	int to,nxt;
}e[N<<1];
int a[N],n,m,head[N<<1],color[N],tot,vis[N],cnt1,cnt2;
void add(int x,int y){//链式前向星
	e[++tot].to = y;
	e[tot].nxt = head[x];
	head[x] = tot;
}
int dfs(int x){//染色法判定二分图
	for(int i=head[x];i;i=e[i].nxt){
		int v = e[i].to;
		if(color[v] == color[x]) return 0;
		if(!color[v]){
			color[v] = -color[x];
			if(!dfs(v)) return 0;
		}
	}
	return 1;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	for(int i=1;i<=n;i++){//注意：此题并未确保给出的图是连通图，可能会有多个连通块，因此要对每个连通块都做一次二分图判定。
		if(!color[i]){
			color[i] = 1;
			if(!dfs(i)){
				printf("-1");
				return 0;
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(color[i] == 1) cnt1++;
		else cnt2++;
	}
	printf("%d\n",cnt1);
	for(int i=1;i<=n;i++) if(color[i] == 1) printf("%d ",i);
	printf("\n%d\n",cnt2);
	for(int i=1;i<=n;i++) if(color[i] == -1) printf("%d ",i);
	return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/163272575)

---

## 作者：qwq___qaq (赞：0)

根据定义可得：对于两个子集 $A$、$B$，每条边 $(u,v)$，$u\in A$ 或 $v\in A$ 且 $u\in B$ 或 $v\in B$，也就是说，$A$、$B$ 都必须有 $u$ 或 $v$。

那么，$A$、$B$ 中不含边，也就是原图是二分图。

用 `dfs` 判断完二分图后，两个颜色块都是符合要求的子集。

但是还要注意：如果一个连通块没有边，那么这个连通块只有一个点，那么这个连通块是不必要的。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int n,m,tot1,tot2,flg[maxn],a1[maxn],a2[maxn],siz[maxn];
vector<int> G[maxn];
bool p,vis[maxn];
void dfs(int u,int x,int root){
	if(flg[u]){
		if(flg[u]!=x)
			p=1;
		return;
	}
	flg[u]=x;
	++siz[root];
	for(int i=0,len=G[u].size();i<len;++i){
		int v=G[u][i];
		dfs(v,x==1?2:1,root);
	}
}
void ask(int u){
	if(vis[u])
		return;
	vis[u]=1;
	if(flg[u]==1)
		a1[++tot1]=u;
	else if(flg[u]==2)
		a2[++tot2]=u;
	for(int i=0,len=G[u].size();i<len;++i){
		int v=G[u][i];
		ask(v);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;++i){
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int i=1;i<=n;++i)
		if(!flg[i])
			dfs(i,1,i);
	if(p){
		puts("-1");
		return 0;
	}
	for(int i=1;i<=n;++i)
		if(!vis[i]&&siz[i]>1)
			ask(i);
	printf("%d\n",tot1);
	for(int i=1;i<=tot1;++i)
		printf("%d ",a1[i]);
	puts("");
	printf("%d\n",tot2);
	for(int i=1;i<=tot2;++i)
		printf("%d ",a2[i]);
	return 0;
}
```

---

