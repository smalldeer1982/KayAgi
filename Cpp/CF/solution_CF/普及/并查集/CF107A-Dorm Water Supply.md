# Dorm Water Supply

## 题目描述

给出一组 $n$ 个点，$m$ 条边的有向图，边带权。保证每个点的出度和入度最多为 $1$  
对于每一个入度为 $0$，出度为 $1$ 的点，我们在该点建一个水箱  
对于每一个入度为 $1$，出度为 $0$ 的点，我们在该点建一个水龙头

可以发现，每一个水箱对应一个唯一的水龙头，我们将每对对应的水龙头和水箱称为一个 水器组

请求出每一个水箱到他对应的水龙头的路径上的边权最小值

## 说明/提示

$1 \le n \le 1000$  
$0 \le m \le n$
边权不超过 $10^6$  
注意水龙头和水箱不能建在同一个节点上

感谢 @[_Wolverine](https://www.luogu.com.cn/user/120362) 提供的翻译

## 样例 #1

### 输入

```
3 2
1 2 10
2 3 20
```

### 输出

```
1
1 3 10
```

## 样例 #2

### 输入

```
3 3
1 2 20
2 3 10
3 1 5
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4 2
1 2 60
3 4 50
```

### 输出

```
2
1 2 60
3 4 50
```

# 题解

## 作者：开始新的记忆 (赞：3)

题目大意：给你一堆点，有向图，保证每个点最多有一个出边和一个入边，给你每条边的权值，问你每一块连通块中的起点和中点还有这条路径中最小权值是多少。

大致思路：因为每个点都只有一条出边，入边，所以我们可以遍历出每个块的头，然后一个个往后扫，每次都记录并更新这一段的最小值，复杂度On即可

```
#include<bits/stdc++.h>
using namespace std;
struct node{
	int fr,to,val;
} ans[1010];
int n,m,cnt=0,mixn=0x7fffffff,last[1010],ne[1010],co[1010];
bool vis[1010];

void dfs(int x)
{
	vis[x]=1;
	if(ne[x]==0)
	{
		ans[cnt].to=x;
		ans[cnt].val=mixn;
		return;
	}
	mixn=min(mixn,co[x]);
	dfs(ne[x]);
} 

int main()
{	cin>>n>>m;
    for(int i=1,x,y,z;i<=m;++i)
    {
    	cin>>x>>y>>z;
    	last[y]=x;
    	ne[x]=y;
    	co[x]=z;
	}
	for(int i=1;i<=n;++i)
		if(!vis[i] && last[i]==0 && co[i]!=0)
		{
			ans[cnt].fr=i;
			mixn=co[i];
			dfs(i);
			++cnt;
		}
	cout<<cnt<<endl;
	for(int i=0;i<cnt;++i)
		cout<<ans[i].fr<<' '<<ans[i].to<<' '<<ans[i].val<<endl;
    return 0;
}
```


---

## 作者：梨衣 (赞：2)

跟dalao不一样，萌新一看本题就想到了类似拓扑的思想
## 解题思路
在建边时记录每个点的入度与出度，方便判断是否是水龙头，枚举每个点，若是水龙头，则必有一水箱与其对应形成一个水器组，再以这个点一路搜索就可以记录路径上的最小边和对应水箱了。

选择用前向星建立单向边，$dfs$ 中定义两个变量 $minn$ 与 $cnt$ 记录最小值与当前边指向的点，当前点没有边时便结束 $dfs$。

需要注意:不能仅判断一点入度为 $0$ 就认为是水龙头，存在一点单独存在没有连成图的情况，所以当入度为 $0$ 且出度不为 $0$ 时才是水龙头。
## 代码如下
```cpp
#include<cstdio>
#include<iostream>
#define R register
using namespace std;
struct edge{
	int to,w;
}e[1010];
int head[1010],tot;
inline void add(R int x,R int y,R int z){
	e[++tot].to=y;
	e[tot].w=z;
	head[x]=tot;
}
int in[1010],out[1010],minn,cnt;
inline void dfs(int u){
	if(!head[u])return;
	minn=min(minn,e[head[u]].w);
	cnt=e[head[u]].to;
	dfs(e[head[u]].to);
}
int main(){
	R int n,m;
	scanf("%d%d",&n,&m);
	for(R int i=1;i<=m;i++){
		R int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		add(a,b,c);
		in[b]++;
		out[a]++;
	}
	R int ans=0;
	for(R int i=1;i<=n;i++)
		if(!in[i]&&out[i])ans++;
	printf("%d\n",ans);
	for(R int i=1;i<=n;i++){
		minn=0x3f3f3f3f;
		if(!in[i]&&out[i]){
			dfs(i);
			printf("%d %d %d\n",i,cnt,minn);	
		}
	}
	return 0;
}
```
## $2020NOIP$ $rp++$

---

## 作者：Peaky (赞：1)

按照惯例，应该先有[传送门](https://www.luogu.com.cn/problem/CF107A)。
### 题目大意
简化一下题意。  
给定 $n$ 个点和 $m$ 条边。
每一个点入度和出度最大不超过 $1$，对于每一个连通块，找到入度为零的点和出度为零的点，形成一条链，输出这条链的两端和这条链边权的最小值。
### 思路
由于入度和出度最大不超过 $1$，所以一个连通块内最多只会形成一个环切**连通块每一个点都在环内**，对于这种情况不需要考虑，因为环上每个点出度入度都是 $1$。  
剩下的连通块**一定都是链**，因为出度最大为一，所以不可能会形成树形结构。所以我们只需找到入度为 $0$ 的点从这点出发，直到找到出度为 $0$ 的点为止。
### 特殊情况
如果一个点入度出度都为零，就把它忽略掉。

### AC code
```cpp
#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
const int N=2e5+10,inf=0x3f3f3f3f,mod=1e9+7;
typedef unsigned long long ull;
typedef pair<int,int> pii;	
typedef long long ll;
/*

*/
int f[N],W[N],in[N],out[N],n,p;
int head[N],edge[N],last[N],idx,a[N],b[N],l[N],k;
void add(int u,int v,int w){
	edge[++idx]=v;
	W[idx]=w;
	last[idx]=head[u];
	head[u]=idx;
}
void dfs(int x){
	if(!out[x]){
		b[k]=x;
		if(b[k]==a[k]) k--;
		return;
	}
	for(int i=head[x];i;i=last[i]) l[k]=min(l[k],W[i]),dfs(edge[i]);
}
int main(){
	cin>>n>>p;
	for(int i=1;i<=n;i++) f[i]=i;
	while(p--){
		int u,v,w;
		cin>>u>>v>>w;
		in[v]++,out[u]++;
		add(u,v,w);
	}
	for(int i=1;i<=n;i++) if(!in[i]) a[++k]=i,l[k]=inf,dfs(i);
	cout<<k<<endl;
	for(int i=1;i<=k;i++) cout<<a[i]<<" "<<b[i]<<" "<<l[i]<<endl;
	return 0;
} 
```

---

## 作者：zhanglh (赞：1)

每个节点的入度和出度不超过 $1$，因此构成的图是若干条链和和一些出入度均为 $0$ 的节点。

根据读入建边，统计每个节点的入度，$d_u$ 表示节点 $u$ 的入度。对于节点 $u$，出边指向 $v$，则记 $g_u$ 为 $v$。这样就可以判定当前节点的出度为 $0$ 还是 $1$（$g_u$ 不为 $0$ 则出度为 $1$，反之为 $0$）。

对于入度为 $0$ 且出度不为 $0$ 的节点，其一定是水箱。统计其个数，就是水器组的个数 $k$。

找到水箱在哪个节点后，依 $g$ 数组不断顺着有向边往后搜。直到搜到第一个出度为 $0$ 的节点，该节点就一定是水龙头。搜的同时，统计一下链上边权的最小值。

```
#include <iostream>
#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 1010;

int n, m, g[N], d[N], ans, ed;
map<pair<int, int>, int> mp;
vector<int> vec;

inline void dfs(int u)
{
    if (!g[u])
    {
        ed = u;
        return;
    }
    ans = min(ans, mp[{u, g[u]}]);
    dfs(g[u]);
}

int main()
{
    scanf("%d%d", &n, &m);
    if (m == 0)
    {
        puts("0");
        return 0;
    }
    while (m -- )
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        g[a] = b, d[b] ++ ;
        mp[{a, b}] = mp[{b, a}] = c;
    }
    int cnt = 0;
    for (int i = 1; i <= n; i ++ )
        if (!d[i] && g[i] != 0)
        {
            cnt ++ ;
            vec.push_back(i);
        }
    printf("%d\n", cnt);
    for (int i = 0; i < vec.size(); i ++ )
    {
        printf("%d ", vec[i]);
        ans = 0x3f3f3f3f;
        dfs(vec[i]);
        printf("%d %d\n", ed, ans);
    }
    return 0;
}
```

---

## 作者：Eason_cyx (赞：0)

这题有蓝？？

由于水箱是入度为 $0$，出度为 $1$ 的结点，水龙头是入度为 $1$，出度为 $0$ 的结点，我们只需要找到所有水龙头，然后顺藤摸瓜向下遍历即可。因为每个点的入，出度最多为 $1$，所以遍历过程中每个点一定只会被遍历 $1$ 次，所以时间复杂度 $\Theta(n)$。

[Accepted](https://codeforces.com/contest/107/submission/275460302)

---

## 作者：Liuhy2996 (赞：0)

### 思路
从入度为零的点开始搜索，直到出度为零为止。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,y[200005],z[200005],a[200005],cnt;
int main(){
	cin>>n>>m;
	while(m--) cin>>x,cin>>y[x]>>z[x],++a[y[x]];
	for(int i=1;i<=n;++i)
		if(!a[i]&&y[i]) ++cnt;
	cout<<cnt<<endl;
	for(int i=1;i<=n;++i)
		if(!a[i]&&y[i]){
			cout<<i<<' ';
			int pos=i,mn=1e9;
			while(y[pos]) mn=min(mn,z[pos]),pos=y[pos];
			cout<<pos<<' '<<mn<<endl;
		}
	return 0;
}
```

---

## 作者：Zhuluoan (赞：0)

## 题目简述

给出一个 $n$ 个点，$m$ 条边的有向图，边带权。保证每个点的出度和入度最多为 $1$。

- 对于每一个入度为 $0$，出度为 $1$ 的点，我们在该点建一个水箱 。
- 对于每一个入度为 $1$，出度为 $0$ 的点，我们在该点建一个水龙头。

可以发现，每一个水箱对应一个唯一的水龙头，我们将每对对应的水龙头和水箱称为一个**水器组**。

请求出每一个水箱到他对应的水龙头的路径上的边权最小值。

## 题目分析

我们可以先找到每一个水箱，由于题目保证了每一个水箱对应一个唯一的水龙头，所以我们可以直接从水箱开始搜索，直到找到它所对应的水龙头，在搜索的过程中记录答案即可。

## 代码
```cpp
#include<iostream>
using namespace std;
const int N=1010;
const int M=1e6;
int n,p,a,b,d,in[N],head[N],cnt,vis[N],out[N],ans1[N],ans2[N],ans3[N],cnt1;
struct edge
{
	int to,next,value;
}e[M];
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
	    if(ch=='-')
		{
			f=-1;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
	    x=(x<<1)+(x<<3)+ch-48;
	    ch=getchar();
	}
	return x*f;
}
inline void write(int x)
{
    if(x<0)
	{
    	putchar('-');
		x=-x;
	}
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
void addedge(int u,int v,int w)
{
	e[++cnt]={v,head[u],w};
	head[u]=cnt;
	in[v]++;
	out[u]++;
}
void dfs(int now,int root,int ans)
{
	if(vis[now]) return;
	vis[now]=1;
	if(!out[now])
	{
		ans1[++cnt1]=root;
		ans2[cnt1]=now;
		ans3[cnt1]=ans;
		return;
	}
	for(int i=head[now];i;i=e[i].next)
	{
		int nxt=e[i].to;
		int w=e[i].value;
		dfs(nxt,root,min(ans,w));
	}
}
int main()
{
	n=read();
	p=read();
	for(int i=1;i<=p;i++)
	{
		a=read();
		b=read();
		d=read();
		addedge(a,b,d);
	}
	for(int i=1;i<=n;i++)
	{
		if(!in[i]&&out[i]>0)//本题的一个坑点，水箱不能是一个独立的点
		{
			dfs(i,i,999999999);
		}
	}
	write(cnt1);
	printf("\n");
	for(int i=1;i<=cnt1;i++)
	{
		printf("%d %d %d\n",ans1[i],ans2[i],ans3[i]);
	}
	return 0;
}

```

---

## 作者：fish_shit (赞：0)

根据题意得到，每个水箱只会对应唯一的一个水龙头，所以我们可以先遍历所有点，如果它是水箱的话就开始搜索它对应的水龙头，一边搜索一边记录路径上的最小边权，最后输出记录下的答案即可。

代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,p,head[2000],ecnt,in[2000],out[2000],ans[2000],ans1[2000],cnt,pos;
struct f{
	int to,next,w;
}a[2000];
void add(int u,int v,int ww){
	ecnt++;
	in[v]=1;
	out[u]=1;
	a[ecnt].next=head[u];
	a[ecnt].to=v;
	a[ecnt].w=ww;
	head[u]=ecnt;
}
void dfs(int x){//dfs搜索
	if(out[x]==0){
		cnt++;
		ans[pos]=x;
	}
	for(int i=head[x];~i;i=a[i].next){
		ans1[pos]=min(ans1[pos],a[i].w);
		dfs(a[i].to);
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	memset(head,-1,sizeof(head));
	memset(ans1,0x3f,sizeof(ans1));
	cin>>n>>p;
	for(int i=1;i<=p;i++){
		int u,v,ww;
		cin>>u>>v>>ww;
		add(u,v,ww);
	}
	for(int i=1;i<=n;i++){
		if(out[i]==1&&in[i]==0){
			pos=i;
			dfs(i);
		}
	}
	cout<<cnt<<endl;
	for(int i=1;i<=n;i++){
		if(out[i]==1&&in[i]==0){
			cout<<i<<" "<<ans[i]<<" "<<ans1[i]<<endl;
		}
	}
	return 0;
}
```


---

## 作者：黑影洞人 (赞：0)

题意：给你一个有向基环树森林或森林，如果是森林每个树都是链，如果是基环树森林，那么直接输出 $0$，求每个链的开始，结尾，最小边权。

直接统计入度，然后找到入度为 $0$，出度为 $1$ 的点，一直往下遍历，直到找到出度为 $0$ 的点为止，然后在遍历的过程中记录一下最小边权即可。

```cpp
#include<cstdio>
#include<algorithm>
#define N 1145
using namespace std;
int n,m;
int a[N],b[N],c[N],cnt;
int in[N],out[N];
int head[N],to[N],nxt[N],val[N],tot;
void add(int u,int v,int w){
	to[++tot]=v;
	nxt[tot]=head[u];
	head[u]=tot;
	val[tot]=w;
}
signed main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
		in[v]++,out[u]++;
	}
	for(int x=1;x<=n;x++){
		if(!in[x]&&out[x]){
			int y=x,z=2147483647;
			while(out[y]){
				for(int i=head[y];i;i=nxt[y])y=to[i],z=min(z,val[i]);
			}
			a[++cnt]=x,b[cnt]=y,c[cnt]=z;
		}
	}
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++)printf("%d %d %d\n",a[i],b[i],c[i]);
	return 0;
}



```


---

## 作者：SuperCowHorse (赞：0)

看到一个个 dalao 都用啥拓扑排序啊，dfs 啊，我都没想到，本蒟蒻自愧不如。~~写了老长一大串。~~

我的解法的来源是看错题了，没看到这句话：`保证每个点的出度和入度最多为 1`。

然后看到边权最小，就想到了最短路。

先使用 dijkstra 求最短路，找路径最小值，一个个比较、统计，对板子一顿魔改，就行了。

详见注释。
``` cpp
#include<bits/stdc++.h>
#define ll long long
#define do double
#define pb push_back
#define il inline
#define lowbit(x) (x&(-x))
#define sqr(x) (x*x)
using namespace std;
const int maxn=1005;
struct Queue{
	int pos,dis;
	bool operator<(const Queue &u)const{return dis<u.dis;}//重载运算符
};
struct edge{
	int v,w,next;
}e[maxn];int cnt,head[maxn];
struct node{
	int u,v,w;
}ans[maxn];int ret;
int n,m,in[maxn],ou[maxn];
int v[maxn],tot;
void add(int u,int v,int w){//链式前向星存图
	e[++cnt]=(edge){v,w,head[u]};
	head[u]=cnt;
}
int dis[maxn],fis[maxn];bool vis[maxn];//注：fis 表示路径上的最小值
node dijkstra(int s){//跑 dijkstra
	priority_queue<Queue>q;
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	memset(fis,0x3f,sizeof(fis));
	dis[s]=0;vis[s]=0;
	q.push((Queue){s,0});
	while(!q.empty()){
		Queue tmp=q.top();q.pop();
		int u=tmp.pos;
		if(vis[u]) continue;
		vis[u]=1;
		if(in[u]&&!ou[u])
			return (node){s,u,fis[u]};
		for(int i=head[u];i;i=e[i].next){
			int v=e[i].v;
			if(dis[v]>dis[u]+e[i].w){
				dis[v]=dis[u]+e[i].w;
				fis[v]=min(fis[u],e[i].w);//取最小值
				q.push((Queue){v,dis[v]});
			}
		}
	}
}
signed main(){
	scanf("%d%d",&n,&m);
	for(int i=1,u,v,w;i<=m;++i){
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
		++in[v];++ou[u];//利用拓扑的思想：判断水箱和水龙头
	}
	for(int i=1;i<=n;++i)//如果是水箱就跑 dijkstra
		if(!in[i]&&ou[i])
			v[++tot]=i;
	for(int i=1;i<=tot;++i)
		ans[++ret]=dijkstra(v[i]);//跑 dijkstra
	printf("%d\n",ret);//水器组数量
	for(int i=1;i<=ret;++i)
		printf("%d %d %d\n",ans[i].u,ans[i].v,ans[i].w);//输出
	return 0;
}
```

---

## 作者：Phoenix_chaser (赞：0)

## 两遍DFS
说实话刚看到这题，本蒟蒻以为是拓扑排序，但仔细一看题目，又一看数据范围，或许可以DFS?

我的思路就是**先跑一遍DFS记录有几条联通路**

再跑一次输出**初时的值和DFS回溯时的值**

由于 $1\le n\le1000$ 

所以我们DFS并不会超时间

上代码：

```cpp
#include<iostream>
#include<vector>
using namespace std;
int n,m,u,v,l,x,y,z,ji=0;
int r[100004],c[100004];
struct node{
	int t,v;
};
vector<node>g[112211];
void dfs(int x,int ans){
	if(c[x]==0)
	{
		cout<<x<<" ";
        cout<<ans;
		return ;
	} 
	for(int i=0;i<g[x].size();i++){
		if(ans==0)
		ans=g[x][i].v;
		if(ans!=0)
		ans=min(ans,g[x][i].v);
		dfs(g[x][i].t,ans);
	}
	
}
void dfs2(int x){
	if(c[x]==0)
	{
		ji++;
		return ;
	} 
	for(int i=0;i<g[x].size();i++)
	dfs2(g[x][i].t);
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>x>>y>>z;
		g[x].push_back((node){y,z});
		r[y]=1;
		c[x]=1;
	}
	for(int i=1;i<=n;i++)
	{	
	if(r[i]==0&&c[i]==1)	
	dfs2(i);
	}
	cout<<ji;
    cout<<"\n";
	for(int i=1;i<=n;i++)
	{
	if(r[i]==0&&c[i]==1)	
	{
        cout<<i<<" "; 
		dfs(i,0);
        cout<<"\n";
	}
	}
}
```
谢谢观看



---

## 作者：谦谦君子 (赞：0)

这题不是很难，上代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
    int u,v,d;
}a[1001];
int cnt,n,m;
int NE[1001],cost[1001],pre[1001];
bool v[1001];
void dfs(int i,int flow)
{
    v[i]=true;
    if (NE[i]==0)
    {
        a[cnt].d=flow;
        a[cnt].v=i;
        return;
    }
    int j=NE[i];
    if (cost[j]<flow&&cost[j]!=0)
    {
        dfs(j,cost[j]);
    }
    else
    {
        dfs(j,flow);
    }
}
int main()
{
    cnt=0;
    cin>>n>>m;
    for (int i=1;i<=m;i++)
    {
        int a,b,k;
        cin>>a>>b>>k;
        NE[a]=b;
        pre[b]=a;
        cost[a]=k;
    }
    for (int i=1;i<=n;i++)
    {
        if (!v[i]&&pre[i]==0&&NE[i]!=0)
        {
            a[cnt].u=i;
            dfs(i,cost[i]);
            cnt++;
        }
    }
    cout<<cnt<<endl;
    for (int i=0;i<cnt;i++)
    {
        cout<<a[i].u<<" "<<a[i].v<<" "<<a[i].d<<endl;
    }
    return 0;
}
```

---

