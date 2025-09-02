# Pursuit For Artifacts

## 题目描述

Johnny is playing a well-known computer game. The game are in some country, where the player can freely travel, pass quests and gain an experience.

In that country there are $ n $ islands and $ m $ bridges between them, so you can travel from any island to any other. In the middle of some bridges are lying ancient powerful artifacts. Johnny is not interested in artifacts, but he can get some money by selling some artifact.

At the start Johnny is in the island $ a $ and the artifact-dealer is in the island $ b $ (possibly they are on the same island). Johnny wants to find some artifact, come to the dealer and sell it. The only difficulty is that bridges are too old and destroying right after passing over them. Johnnie's character can't swim, fly and teleport, so the problem became too difficult.

Note that Johnny can't pass the half of the bridge, collect the artifact and return to the same island.

Determine if Johnny can find some artifact and sell it.

## 样例 #1

### 输入

```
6 7
1 2 0
2 3 0
3 1 0
3 4 1
4 5 0
5 6 0
6 4 0
1 6
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
5 4
1 2 0
2 3 0
3 4 0
2 5 1
1 4
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
5 6
1 2 0
2 3 0
3 1 0
3 4 0
4 5 1
5 3 0
1 2
```

### 输出

```
YES
```

# 题解

## 作者：He_Ren (赞：9)

每条边最多经过1次

不难想到，一个环上如果有一条边为$1$，那么这个环上所有点对都是符合条件的

所以可以缩点（边双），缩点后的每个点，如果其中有一条为$1$的边，那么就把这个点的权值赋值为$1$

然后这个图就变成了一棵树

然后问题就变成了：给定树上两个点，询问他们之间的路径，是否有点或边的权值为$1$

这里我选择用$O(n)$的dfs解决

总复杂度$O(n+m)$

```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<stack>
const int MAXN = 3e5 + 5;
const int MAXM = 3e5 + 5;
using namespace std;

inline void chk_min(int &a,int b){ if(a>b) a=b;}

struct Edge
{
	int next,from,to,w;
}e[MAXM*2];
int head[MAXN],etot=0;
inline void add(int u,int v,int w)
{
	++etot;
	e[etot]=(Edge){ head[u],u,v,w};
	head[u] = etot;
}

stack<int> s;
int dfn[MAXN],low[MAXN],cnt=0;
bool vis[MAXN];
int clr[MAXN],ccnt=0;
void tarjan(int u,int fa)
{
	dfn[u]=low[u]=++cnt;
	s.push(u); vis[u]=1;
	for(int i=head[u]; i; i=e[i].next)
	{
		int v=e[i].to;
		if(v==fa) continue;
		if(!dfn[v])
		{
			tarjan(v,u);
			chk_min(low[u],low[v]);
		}
		else if(vis[v]) chk_min(low[u], low[v]);
	}
	
	if(dfn[u]==low[u])
	{
		clr[u]=++ccnt;
		while(s.top()!=u)
		{
			clr[s.top()]=ccnt;
			vis[s.top()]=0;
			s.pop();
		}
		s.pop(); vis[u]=0;
	}
}

bool can[MAXN];

int to;
bool pas[MAXN];
void dfs(int u,bool f)
{
	if(can[u]) f=1;
	if(u==to)
	{
		if(f) printf("YES");
		else printf("NO");
		exit(0);
	}
	pas[u]=1;
	for(int i=head[u]; i; i=e[i].next)
	{
		int v=e[i].to;
		if(!pas[v]) dfs(v,f|e[i].w);
	}
}

int main(void)
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1; i<=m; ++i)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w); add(v,u,w);
	}
	tarjan(1,0);
	for(int i=1; i<=etot; i+=2)
	{
		if(clr[e[i].from] == clr[e[i].to] && e[i].w)
		{
			can[clr[e[i].from]]=1;
		}
	}
	
	//for(int i=1; i<=n; ++i) printf("clr[%d]: %d\n",i,clr[i]);
	
	memset(head,0,sizeof(head));
	etot=0;
	for(int i=1; i<=m*2; ++i)
	{
		if(clr[e[i].from] != clr[e[i].to])
		{
			add(clr[e[i].from],clr[e[i].to],e[i].w);
		}
	}
	
	int start;
	scanf("%d%d",&start,&to);
	start=clr[start]; to=clr[to];
	dfs(start,0);
	return 0;
}
```


---

## 作者：hxhhxh (赞：4)

## 大意

给定一个简单联通无向图，边有边权（$ 0 $ 或 $ 1 $），每一条边只能经过 $ 1 $ 次，求能不能从 $ a $ 走到 $ b $，且经过一条边权为 $ 1 $ 的边。

## 思路

对于一个边双连通分量（后简称边双），如果其中有一条边权值为 $ 1 $，那只要能经过这个边双就一定可以经过那个边权为 $ 1 $ 的边。

将原图缩点，图变成一个树。从 $ a $ 往 $ b $ 走，只要经过一个有宝藏的边双就能够找到宝藏，答案为`YES`，否则答案为`NO`。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a,b,dfn[300005],low[300005],cnt,fa[300005];
bool ans[300005];
struct edge{
	int end;
	bool v;
};
vector<edge>e[300005];
bool asa;
void dfs(int x,bool vis){
	low[x]=dfn[x]=++cnt;
	bool t=false;
	if(x==b&&vis) asa=true;
	for(int i=0;i<e[x].size();i++){
		int to=e[x][i].end;
		if(to==fa[x]) continue;
		if(dfn[to]==0){
			fa[to]=x;
			dfs(to,vis||e[x][i].v);
			low[x]=min(low[to],low[x]);
			if(e[x][i].v&&low[to]<=dfn[x]) t=true;
		}
		else{
			low[x]=min(dfn[to],low[x]);
			if(e[x][i].v&&dfn[to]<=dfn[x]) t=true;
		}
	}
	ans[low[x]]|=(t||ans[dfn[x]]);
}
int main(){
	cin>>n>>m;
	for(int i=1,x,y,z;i<=m;i++){
		scanf("%d %d %d",&x,&y,&z);
		e[x].push_back((edge){y,z});
		e[y].push_back((edge){x,z});
	}
	cin>>a>>b;
	dfs(a,false);
	if(asa) cout<<"YES"<<endl;
	else{
		while(b){
			if(ans[dfn[b]]){
				cout<<"YES"<<endl;
				return 0;
			}
			b=fa[b];
		}
		cout<<"NO"<<endl;
	}
	return 0;
}
```

---

## 作者：wyl_AC (赞：2)

缩点+LCA板题，一眼缩点

边双联通缩点，因为每个边双中的边都可以都可以经过，如果有1那么这个点的权值是1，否则是0。

然后就是一棵树了，可用LCA求两点之间树上路径，本来准备线段树或st表，但这道紫题色不符实，只求一次，所以我选择暴力爬山~~这也算LCA？~~

上代码
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
#include<stack>
#include<cstring>
using namespace std;
#define LL long long
#define M 1000005
#define N 20
#define lowbit(i) (i&(-i))
#define Mod 1000000007
#define IMax 0x7fffffffffffffff 
void read(LL &x){
	x=0;char c=getchar();LL f=1;
	while(c<'0'||c>'9'){
		if(c=='-')
			f=-f;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-'0';
		c=getchar();
	}
	x*=f;
	return ;
}
void print(LL x){
	if(x<10){
		putchar(x+'0');
		return ;
	}
	print(x/10);
	putchar(x%10+'0');
}
void write(LL x){
	if(x<0)
		x=-x,putchar('-');
	print(x);
}
LL maxt(LL a,LL b){
	return a<b?b:a;
}
LL mint(LL a,LL b){
	return a<b?a:b;
}
struct node{
	LL v,id;
	node(LL V,LL Id){
		v=V,id=Id;
	}
};
stack<LL>q,r;
vector<node>R[M],G[M];
vector<LL>E[M];
LL n,m,dfn[M],low[M],cnt,w[M],s[M],bel[M],f[M],e[M],dep[M],col;
void tarjan(LL u,LL fa){
	q.push(u);
	dfn[u]=low[u]=++cnt;
	for(int i=0;i<R[u].size();i++){
		LL v=R[u][i].v,id=R[u][i].id;
		if(v==fa)
			continue;
		r.push(id);
		if(!dfn[v]){
			tarjan(v,u);
			low[u]=mint(low[u],low[v]);
			if(low[v]>dfn[u]){
				++col;
				while(r.top()!=id){
					if(w[r.top()])
						s[col]=1;
					r.pop();
				}	
				r.pop();
				while(q.top()!=v){
					bel[q.top()]=col;
					E[col].push_back(q.top());
					q.pop();
				}
				bel[v]=col;
				E[col].push_back(v);
				q.pop();
			}
		}else
			low[u]=mint(low[u],dfn[v]);
	}
	if(fa==-1){
		++col;
		while(!r.empty()){
			if(w[r.top()])
				s[col]=1;
				r.pop();
		}	
		while(!q.empty()){
			bel[q.top()]=col;
			E[col].push_back(q.top());
			q.pop();
		}
	}
}
void dfs(LL u,LL fa){
	f[u]=fa;
	dep[u]=dep[fa]+1;
	for(int i=0;i<G[u].size();i++){
		LL v=G[u][i].v,id=G[u][i].id;
		if(v==fa)
			continue;
		e[v]=id;
		dfs(v,u);
	}
}
int main(){
	read(n),read(m);
	for(int i=1;i<=m;i++){
		LL u,v;
		read(u),read(v),read(w[i]);
		R[u].push_back(node(v,i));
		R[v].push_back(node(u,i));
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			tarjan(i,-1);
	for(int i=1;i<=col;i++)
		for(int j=0;j<E[i].size();j++){
			LL u=E[i][j];
			for(int k=0;k<R[u].size();k++){
				LL v=R[u][k].v,id=R[u][k].id;
				if(bel[u]!=bel[v])
					G[bel[u]].push_back(node(bel[v],id));
			}
		}
	dfs(1,1);
	LL a,b;
	bool fl=0;
	read(a),read(b);
	a=bel[a],b=bel[b];
	if(dep[a]<dep[b])
		swap(a,b);
	while(dep[a]>dep[b]){
		if(w[e[a]]||s[a])
			fl=1;
		a=f[a];
	}
	while(a!=b){
		if(w[e[a]]||w[e[b]]||s[a]||s[b])
			fl=1;
		a=f[a];
		b=f[b];
	}
	if(s[a])
		fl=1;
	if(fl)
		puts("YES");
	else
		puts("NO");
}
 
```


---

## 作者：青鸟_Blue_Bird (赞：1)

[题目戳这](https://www.luogu.com.cn/problem/CF652E)

这是一道很好的练习强联通的题目。
首先，从题中可以看到，题目的要求就是要我们求出从起点到终点是否可以经过flag = 1 的边。
由于是无向图，且要求很多，直接暴力dfs会很凌乱。

那么，我们就想到一个思路：能不能尽量把这张图缩小，标记转为点，最好成为一条一条链呢？

## tarjan的缩点！！

没错，对于一个环，可以想到，只要这个环中有一条边flag = 1，那么所有的点我们都可以通过falg = 1的边到达（因为这是环）。所以，不妨进行tarjan缩点，只要这个缩点中有一条边falg = 1，我们就把这个缩点打上tag。

再一想，经过缩点之后，原来十分凌乱的图就变成了一棵树。到达终点的路线也就只有固定一条了。这里我选择dfs。

思路大体就是这样，总时间复杂度O(M + N)

话不多说，具体细节操作标记在代码里面了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 500010
#define isdigit(c) ((c)>='0'&&(c)<='9')

inline int read(){
	int x = 0,s = 1;
	char c = getchar();
	while(!isdigit(c)){
		if(c == '-') s = -1;
		c = getchar();
	} 
	while(isdigit(c)){
		x = (x << 1) + (x << 3) + (c ^ '0');
		c = getchar();
	}
	return x * s;
}

int n, m;
struct node{
	int u, v, flag;
	int next;
} t[N << 1]; 
int f[N];//日常邻接表 

int s, ht;//起点， 终点 
int dfn[N], low[N], scc[N]; //scc即为缩点后每个缩点的编号 
stack <int> stac;//缩点用的
bool vis[N];//一个点是否被经过 


int bian = 0;
void add(int u, int v, int flag){
	bian++;
	t[bian].u = u;
	t[bian].v = v;
	t[bian].flag = flag;
	t[bian].next = f[u];
	f[u] = bian;
	return ;
}

int cnt = 0, cac;//cac为强联通的数量 
void tarjan(int now, int fa){//无向图的tarjan强联通 板子 
	dfn[now] = low[now] = ++cnt;
	vis[now] = 1;
	stac.push(now);
	for(int i = f[now]; i;i = t[i].next){
		int v = t[i].v;
		if(v != fa){
			if(!dfn[v]){
				tarjan(v, now);
				low[now] = min(low[now], low[v]);
			}
			else if(vis[v])low[now] = min(low[now], low[v]);
		}
	}
	if(dfn[now] == low[now]){
		int cur;
		cac++;
		do{
			cur = stac.top();
			stac.pop();
			scc[cur] = cac;
			vis[cur] = 0;
		}while(cur != now);
	}
	return ;
}

bool tong[N]; //tong为每个缩点被打上的标记，即上文所说的，是否包含flag = 1的边 
void dfs(int now, bool flag){
	if(tong[now])flag = 1;//这个缩点标记为1的话，记下来 
	if(now == scc[ht]){
		if(flag)puts("YES");//搜到终点，没什么好说的 
		else puts("NO");
		return ;
	}
	for(int i = f[now]; i;i = t[i].next){
		int v = t[i].v, u = t[i].u;
		if(!vis[v]){
			vis[v] = 1;
			dfs(v, flag | t[i].flag);//这里要注意不要漏掉了缩点与缩点之间的边的 flag 
		}	
	}
	return ;
}

int main(){
	n = read(), m = read();
	for(int i = 1;i <= m; i++){
		int x = read(), y = read(), tag = read();
		add(x, y, tag);add(y, x, tag);
	}
	s = read() , ht = read();
	tarjan(1, 0);
	for(int i = 1;i <= bian; i += 2){
		if(scc[t[i].u] == scc[t[i].v] && t[i].flag){
			tong[scc[t[i].u]] = 1;//为强联通分量中的边，且flag = 1 
		}
	}
	memset(f, 0, sizeof(f));//重复利用 
	bian = 0;
	memset(vis, 0, sizeof(vis));
	for(int i = 1;i <= m << 1; i++){
		int u = t[i].u, v = t[i].v;
		if(scc[u] != scc[v]){
			add(scc[u], scc[v], t[i].flag);//不同缩点之间的连边，需要保留。flag不能改 
		}
	}
	vis[scc[s]] = 1;
	dfs(scc[s], 0);//dfs的都是缩点，这点不要忘了 
	return 0;
}
```

总的来说，码量中等，是道练习强联通的好题（不过为什么做得人这么少呢）


---

## 作者：Forever1507 (赞：0)

看到“每条边只能通过一次”脑海中闪现割边（）

考虑一个弱化版本：如果这两个点在同一个边双连通分量（不会的可以去板子题看看）里的话，显然只要有权为 $1$ 的边就有解，因为我一定可以强行走到那条边然后换一条路过去。

任意一个无向图可视作若干边双组成的**树**（树边是割边），所以我们可以把每个边双打标记记录有没有权为 $1$ 的边，只要有，且我经过了这个边双就一定有解（如上）。

然后直接搜过去（简单路径唯一），顺路判一下割边的权值是不是 $1$，只要经过了是 $1$ 的边双或边（包括起点和终点）就有解，反之无解。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int tot,n,m,dfn[400005],d[400005],dp[400005][21],low[400005],sum,ans,scc[400005];
struct node{
	int first,second,w;
};
vector<node>nbr[400005],_nbr[400005];
bool vis[400005],_vis[300005];
void tarjan(int x,int edge){
	dfn[x]=low[x]=++tot;//割边
	for(int i=0;i<nbr[x].size();++i){
		int to=nbr[x][i].first;
		if(nbr[x][i].second==edge)continue;//不能反复走边
		if(!dfn[to]){
			tarjan(to,nbr[x][i].second);
			low[x]=min(low[x],low[to]);
			if(low[to]>dfn[x]){
				vis[nbr[x][i].second]=1;
				++ans;
			}
		}
		else low[x]=min(low[x],dfn[to]);
	}
	return;
}
bool flag[300005];
int a,b;
void dfs(int cur,int fa){
	scc[cur]=sum;
	for(int i=0;i<nbr[cur].size();++i){
		int to=nbr[cur][i].first;//划分边双，不走割边
		if(_vis[to]||vis[nbr[cur][i].second])continue;
//		if(nbr[cur][i].w==1)flag[sum]=1,cout<<sum<<'\n';
		_vis[to]=1;
		dfs(to,cur);
	}
	return;
}
void find(int x,int fa,bool opt){
	opt|=flag[x];
	if(x==scc[b]){//有即有解
		if(opt==1)cout<<"YES";
		else cout<<"NO";
		exit(0);
	}
	for(auto to:_nbr[x]){
		if(to.first==fa)continue;
		find(to.first,x,(bool)(opt|(to.w)));
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;++i){
		int u,v,w;
		cin>>u>>v>>w;
		nbr[u].push_back({v,i,w});
		nbr[v].push_back({u,i,w});
	}
	cin>>a>>b;
	for(int i=1;i<=n;++i)if(!dfn[i])tarjan(i,0);
	for(int i=1;i<=n;++i)if(!_vis[i])++sum,dfs(i,0);
	for(int i=1;i<=n;++i){
		for(int j=0;j<nbr[i].size();++j){
			if(vis[nbr[i][j].second]){
				_nbr[scc[i]].push_back({scc[nbr[i][j].first],i,nbr[i][j].w});
			}
			else{
				if(nbr[i][j].w==1)flag[scc[i]]=1;
			}
		}
	}
//	cout<<scc[a]<<' '<<scc[b]<<' '<<flag[1]<<' '<<flag[2]<<'\n';
	find(scc[a],0,flag[scc[a]]);
	return 0;
}
```


---

## 作者：yzh_Error404 (赞：0)

首先有一个显而易见的结论：如果当前路径经过一个环，且环上有一条边权为 $1$ 的边，那么这条路径一定是含 $1$ 的。

设想一下，若当前经过一个环，那么入环的点和出环的点一定将这个环分割成两部分，而这条边权为 $1$ 的边一定处于两部分中的一个，直接向这一部分走即可。

所以可以将所有含边权为 $1$ 的边的环缩点（因为是无向图，而且处理的是边，所以是边双连通分量）。

缩完点之后一定是一个无环图，直接跑 dfs 找有没有含边权 $1$ 的边即可。

代码实现：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=6e5+5;
struct node
{
	int to,nxt,len;
}e[MAXN],e_[MAXN];
int head[MAXN],cnt=1;
int head_[MAXN],cnt_=1;
int chu[MAXN];
inline void add(int x,int y,int z)
{
	e[++cnt].to=y;
	e[cnt].nxt=head[x];
	e[cnt].len=z;
	head[x]=cnt;
}
inline void add_(int x,int y,int z)
{
	e_[++cnt_].to=y;
	e_[cnt_].nxt=head_[x];
	e_[cnt_].len=z;
	head_[x]=cnt_;
}
int n,m;
int dfn[MAXN],low[MAXN],now;
int scc[MAXN],sum;
int x[MAXN],y[MAXN],z[MAXN];
bitset<MAXN>cut;
inline void tarjan(int x,int las)
{
	low[x]=dfn[x]=++now;
	for(register int i=head[x];i;i=e[i].nxt)
	{
		int y=e[i].to;
		if(!dfn[y])
		{
			tarjan(y,i);
			low[x]=min(low[x],low[y]);
			if(low[y]>dfn[x])cut[i]=cut[i^1]=1;
		}
		else if(i!=(las^1))low[x]=min(low[x],dfn[y]);
	}
}
inline void dfs(int x)
{
	scc[x]=sum;
	for(register int i=head[x];i;i=e[i].nxt)
	{
		int y=e[i].to;
		if(scc[y]||cut[i])continue;
		dfs(y);
	}
}
int a,b;
bitset<MAXN>don;
bitset<MAXN>vis;
inline bool dfs(int x,bool flag)
{
    if(don[x])flag=1;
    if(x==b)
    {
        if(flag)puts("YES");
        else puts("NO");
        exit(0);
    }
    vis[x]=1;
    for(register int i=head_[x];i;i=e_[i].nxt)
    {
        int y=e_[i].to,z=e_[i].len;
        if(!vis[y])
        {
            if(z)dfs(y,1);
            else dfs(y,0);
        }
    }
}
int main()
{
	scanf("%d%d",&n,&m);
	for(register int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&x[i],&y[i],&z[i]);
		add(x[i],y[i],z[i]);
		add(y[i],x[i],z[i]);
	}
	for(register int i=1;i<=n;i++)
		if(!dfn[i])tarjan(i,0);
	for(register int i=1;i<=n;i++)
		if(!scc[i])sum++,dfs(i);
	for(register int i=1;i<=cnt;i++)
	{
		if(scc[x[i]]!=scc[y[i]])
		{
			add_(scc[x[i]],scc[y[i]],z[i]);
			add_(scc[y[i]],scc[x[i]],z[i]);
		}
		if(scc[x[i]]==scc[y[i]]&&z[i]==1)don[scc[x[i]]]=1;
	}
	scanf("%d%d",&a,&b);
	a=scc[a],b=scc[b];
	dfs(a,0);
	return 0;
}
```

---

## 作者：little_cindy (赞：0)

## 思路
因为在一个环上存在一条边权值为 $1$，经过这个环一定可以走过一条权值为 $1$ 的边，所以我们只需要把每个 E-DCC 合并即可。

缩点后的每个点，如果其中存在一条权值为 $1$ 的边，就把点权变为 $1$。

合并后这个图就变为了一棵树，直接使用 dfs 解决就好了。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+5,maxm=6e5+5;
int n,m;
struct node{
	int nxt,from,to,w;
}edge[maxm];
int head[maxn],tot;
stack<int> s;
int dfn[maxn],low[maxn],id,st,e;
int edcc[maxn],cnt;
bool vis[maxn],viss[maxn],vis2[maxn];
void add(int u,int v,int w){
	tot++;
	edge[tot].from=u;
	edge[tot].to=v;
	edge[tot].w=w;
	edge[tot].nxt=head[u];
	head[u]=tot;
}
void tarjan(int u,int fa){
	dfn[u]=low[u]=++id;
	s.push(u);
	vis[u]=1;
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].to;
		if(v==fa){
			continue;
		}
		if(!dfn[v]){
			tarjan(v,u);
			low[u]=min(low[u],low[v]);
		}
		else if(vis[v]){
			low[u]=min(low[u], low[v]);
		}
	}
	if(dfn[u]==low[u]){
		edcc[u]=++cnt;
		while(s.top()!=u){
			edcc[s.top()]=cnt;
			vis[s.top()]=0;
			s.pop();
		}
		s.pop();
		vis[u]=0;
	}
}
void dfs(int u,bool pos){
	if(viss[u]){
		pos=1;	
	}
	if(u==e){
		if(pos){
			printf("YES");	
		}
		else{
			printf("NO");
		}
		exit(0);
	}
	vis2[u]=1;
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].to;
		if(!vis2[v]){
			dfs(v,pos|edge[i].w);
		}
	}
}
int main(void){
	cin>>n>>m;
	for(int i=1; i<=m; ++i){
		int u,v,w;
		cin>>u>>v>>w;
		add(u,v,w);
		add(v,u,w);
	}
	cin>>st>>e;
	tarjan(1,0);
	for(int i=1;i<=tot;i+=2){
		if(edcc[edge[i].from]==edcc[edge[i].to]&&edge[i].w){
			viss[edcc[edge[i].from]]=1;
		}
	}
	memset(head,0,sizeof(head));
	tot=0;
	for(int i=1;i<=m*2;++i){
		if(edcc[edge[i].from]!=edcc[edge[i].to]){
			add(edcc[edge[i].from],edcc[edge[i].to],edge[i].w);
		}
	}
	st=edcc[st];
	e=edcc[e];
	dfs(st,0);
	return 0;
}
```

---

