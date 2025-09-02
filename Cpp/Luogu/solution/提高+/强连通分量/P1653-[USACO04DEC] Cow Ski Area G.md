# [USACO04DEC] Cow Ski Area G

## 题目描述

约翰的表哥罗恩生活在科罗拉多州。他近来打算教他的奶牛们滑雪，但是奶牛们非常害羞，不敢在游人组织的度假胜地滑雪。没办法，他只好自己建滑雪场了。罗恩的雪场可以划分为 $W$ 列 $L$ 行 $(1\le W\le 500, 1\le L\le 500)$，每个方格有一个特定的高度 $H(0\le H\le 9999)$。奶牛可以在相邻方格间滑雪，而且不能由低到高滑。

为了保证任意方格可以互通，罗恩打算造一些直达缆车。缆车很强大，可以连接任意两个方格，而且是双向的。而且同一个方格也可以造多台缆车。但是缆车的建造费用贵得吓人，所以他希望造尽量少的缆车。那最少需要造多少台呢？

## 说明/提示

$1\le W,L\le 500$，$0\le H\le 9999$。

## 样例 #1

### 输入

```
9 3
1 1 1 2 2 2 1 1 1
1 2 1 2 3 2 1 2 1
1 1 1 2 2 2 1 1 1```

### 输出

```
3```

# 题解

## 作者：2021sunzishan (赞：17)

一道很不错的 tarjan 题目。
## 题目大意：
给定一个 $n \times m$ 的矩阵，每个格子都与上下左右相联通，但只有高度大于时才可以走。因此可以加一些边直接连接一些格子，不考虑高度。现在为了使整个矩阵联通，最少加几条边？

## 思路：
看到矩阵，难道非得用矩阵吗？$2$ 维转 $1$ 维呀！

洛谷上还有 $2$ 维转 $1$ 维的题目，比如 [P3073](https://www.luogu.com.cn/problem/P3073)，不错的并查集题。

实现很简单，可以走的连一条边就行了。

然后就是套用非常经典的 tarjan 模板。不会 tarjan 的先去做 [这题](https://www.luogu.com.cn/problem/P2341)。

最后统计答案的时候，要先求出每个连通块的入度和出度。如果入度或者出度为 $0$，那么显然这个连通块与其他的需要有边相连。最后输出的很显然是入度为 $0$ 和出度为 $0$ 的最大值。

当然有一种特殊情况，只有一个连通块，就直接输出 $0$。

以上就是本题的思路，下面就看代码吧！

切勿抄袭！！！

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 250005//2维转1维,所以数组大小为500*500
inline int read() {//快读，没啥好说的
	int a=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9') {
		if  (c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9') {
		a=a*10+(c-'0');
		c=getchar();
	}
	return f*a;
}
int dfn[N],low[N],col[N],vis[N],vis1[N];//tarjan所需数组
int cl,k;
stack<int>s;
int head[N],cnt;//链式前向星数组
struct edge {
	int to,next;
} edge[N*4];//记得开四倍空间哦(上下左右)
void addedge(int a,int b) {
	edge[++cnt].to=b;
	edge[cnt].next=head[a];
	head[a]=cnt;
}
int n,m,a[505][505],ru[N],chu[N],ans1,ans2;//ans1表示入度为0，ans2表示出度为0
void dfs(int u) {//tarjan标程
	dfn[u]=low[u]=++k;
	s.push(u);
	vis[u]=1;
	vis1[u]=1;
	for (int i=head[u]; i; i=edge[i].next) {
		int v=edge[i].to;
		if (vis[v]==0) {
			dfs(v);
			low[u]=min(low[u],low[v]);
		} else if(vis1[v]==1)
			low[u]=min(low[u],low[v]);
	}
	if (dfn[u]==low[u]) {
		cl++;
		while(s.top()!=u) {
			int q=s.top();
			vis1[q]=-1;
			s.pop();
			col[q]=cl;//记录连通块编号 
		}
		s.pop();
		col[u]=cl;
		vis1[u]=-1;
	}
}
void jb(int a1,int b1,int a2,int b2) {//建边,a1b1、a2b2均表示坐标
	if(a2>n||a2<1||b2>m||b2<1)return;//如果点出界了，返回
	if(a[a1][b1]<a[a2][b2])return;//如果去不了，返回
	addedge((a1-1)*m+b1,(a2-1)*m+b2);//否则建边
   //这里用点的编号建边，即在此矩阵中排第几个
}
int main() {
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	m=read(),n=read();
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			a[i][j]=read();
	for(int i=1; i<=n; i++)//2维转1维
		for(int j=1; j<=m; j++) {
			jb(i,j,i+1,j);//上
			jb(i,j,i-1,j);//下 
			jb(i,j,i,j-1);//左
			jb(i,j,i,j+1);//右
		}
	n*=m;//点的编号为1-n*m
	for (int i=1; i<=n; i++)//tarjan
		if (vis[i]==0)
			dfs(i);
	if(cl==1){//这是一种特殊情况，只有一个连通块，那么不需要另外加边
		printf("0");
		return 0;
	}
	for(int i=1; i<=n; i++)
		for(int j=head[i]; j; j=edge[j].next) {
			int u=edge[j].to;
			if(col[i]!=col[u]) {
				ru[col[u]]++;//统计连通块的入度和出度
				chu[col[i]]++;
			}
		}
	for(int i=1; i<=cl; i++) {//统计入度出度为0的个数
		if(ru[i]==0)ans1++;
		if(chu[i]==0)ans2++;
	}
	printf("%d",max(ans1,ans2));//最后输出
	return 0;
}
                       
```

## 总结：
这题要能想到 $2$ 维转 $1$ 维，并且要考虑全面，还是很好做的。

完结~


---

## 作者：One_JuRuo (赞：6)

如果把每个方格看作一个点，就是[这道题](https://www.luogu.com.cn/problem/P2746)的子任务 B 了。

## 思路

首先看到目标是保证任意方格可以互通，就可以想到应该是一道强连通分量的题，只要按照题目的要求建图，就可以得到一个有向图，那么用 tarjan 缩点后，就可以得到一个无环的有向图。

这样一个无向图，对于每个有入度有出度的点，肯定都是按照顺序走，最后是无出度的点停下，所以我们肯定需要连一些从无出度的点出发的边。

那么，对于无入度的点，如果起点不是这个点，就无法到达这个点，所以肯定也需要连一些到达这些点的边。

无出度和无入度可以连在一起，令无出度的点有 $x$ 个，无入度的点有 $y$ 个，那么答案至少都是 $\min(x,y)$。

不过需要注意的是，不是无出度和无入度的点简单两两匹配就好，实际情况需要交叉连边，因为无出度和无入度的点一定有对应关系，那么连边时应该避免连成若干个环。但是这道题只需要得出连边数量，不需要得出如何连边，所以可以不用考虑。

还有需要注意的是，如果缩完点，只剩下一个点，那么就不需要连边。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[505][505],dfn[250005],low[250005],dcnt,num,id[250005],z[250005],top,in_z[250005],e[1000005],ne[1000005],h[250005],idx=1,in[250005],out[250005],ans1,ans2;
inline void add(int a,int b){e[idx]=b,ne[idx]=h[a],h[a]=idx++;}
inline int get(int i,int j){return (i-1)*m+j;}
inline void ade(int i,int j)
{
	if(i>1)
	{
		if(a[i][j]>=a[i-1][j]) add(get(i,j),get(i-1,j));
		if(a[i][j]<=a[i-1][j]) add(get(i-1,j),get(i,j));
	}
	if(j>1)
	{
		if(a[i][j]>=a[i][j-1]) add(get(i,j),get(i,j-1));
		if(a[i][j]<=a[i][j-1]) add(get(i,j-1),get(i,j));
	}
}
void dfs(int u)
{
	dfn[u]=low[u]=++dcnt,z[++top]=u,in_z[u]=1;
	for(int i=h[u];i;i=ne[i])
		if(!dfn[e[i]]) dfs(e[i]),low[u]=min(low[u],low[e[i]]);
		else if(in_z[e[i]]) low[u]=min(low[u],dfn[e[i]]);
	if(dfn[u]==low[u])
	{
		++num;
		while(z[top+1]!=u) id[z[top]]=num,in_z[z[top--]]=0;
	}
}
int main()
{
	scanf("%d%d",&m,&n);
	for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) scanf("%d",&a[i][j]),ade(i,j);
	for(int i=1;i<=n*m;++i) if(!dfn[i]) dfs(i);
	for(int i=1;i<=n*m;++i) for(int j=h[i];j;j=ne[j]) if(id[i]!=id[e[j]]) ++in[id[e[j]]],++out[id[i]];
	for(int i=1;i<=num;++i){if(!in[i]) ++ans1;if(!out[i]) ++ans2;}
	printf("%d",(num==1)?0:max(ans1,ans2));
	return 0;
}
```

---

## 作者：billtun (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P1653)

看懂题目后，就会发现这就是一道 Tarjan 的模板题。

首先是连边，当一个点（记为 $a$）的高度大于等于周围相邻的点（上下左右共四个，记为 $b$）时，就连一条从 $a$ 到 $b$ 的边。

然后跑一遍 Tarjan。再遍历每一个强连通分量，如果他的出度为 $0$， $ans1$ 加一；如果他的入度为 $0$，$ans2$ 加一。

最后，输出 $ans1$ 与 $ans2$ 的最大值。

因为一个强连通分量里面的任意两个点都是可以互相滑到的，如果一个强连通分量入度为 $0$，即没有任何一个点可以滑到那里，就要建一条缆车；同理，如果一个强连通分量出度为 $0$，他也需要一条缆车到别的点去。

### Code:
```cpp
#include<bits/stdc++.h>
#define N 250005

using namespace std;

int n, m, h[505][505]={0};
vector<int> v[N];
int dfn[N], low[N], dfncnt=0;
int scc[N], sc=0, st[N], top=0;
int in[N]={0}, out[N]={0};
bool is_st[N];
int ans1=0, ans2=0;

void add(int x, int y){
	if(x>1 && h[x][y]>=h[x-1][y]) v[(x-1)*m+y].push_back((x-2)*m+y);
	if(x<n && h[x][y]>=h[x+1][y]) v[(x-1)*m+y].push_back(x*m+y);
	if(y>1 && h[x][y]>=h[x][y-1]) v[(x-1)*m+y].push_back((x-1)*m+y-1);
	if(y<m && h[x][y]>=h[x][y+1]) v[(x-1)*m+y].push_back((x-1)*m+y+1);
}

void Tarjan(int x){
	dfn[x]=low[x]=++dfncnt;
	st[++top]=x, is_st[x]=1;
	
	for(int i=0;i<(int)v[x].size();i++){
		int tmp=v[x][i];
		if(!dfn[tmp]) Tarjan(tmp), low[x]=min(low[x], low[tmp]);
		else if(is_st[tmp]) low[x]=min(low[x], dfn[tmp]);
	}
	
	if(dfn[x]==low[x]){
		sc++;
		while(st[top]!=x){
			scc[st[top]]=sc;
			is_st[st[top]]=0;
			top--;
		}
		scc[st[top]]=sc;
		is_st[st[top]]=0;
		top--;
	}
}

int main()
{
	cin>>m>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>h[i][j];
		}
	}
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			add(i, j);
		}
	}
	
	for(int i=1;i<=n*m;i++){
		if(!dfn[i]){
			Tarjan(i);
		}
	}
	
	for(int i=1;i<=n*m;i++){
		for(int j=0;j<(int)v[i].size();j++){
			int tmp=v[i][j];
			if(scc[i]!=scc[tmp]){
				in[scc[tmp]]++, out[scc[i]]++;
			}
		}
	}
	
	for(int i=1;i<=sc;i++){
		if(!in[i]) ans1++;
		if(!out[i]) ans2++;
	}
	
	if(sc==1) cout<<0;
	else cout<<max(ans1, ans2);
	return 0;
}
```

---

## 作者：ryf_loser (赞：3)

~~简单~~ 强连通分量 。

稍微看一下题，易知此题是在求让所有的方格都可以互相通行，这样我们就知道此题正解强连通分量和缩点。

此题先要知道强连通分量~~板子怎么写~~。

此外，我们一般不用邻接矩阵存储图，一般用链式前向星或 vector 存储图，这样此题需要二维转一维。精确来说，需要对一个格子上下左右四个方向进行连边，这样就可以转成一维了。

板子打完后，我们需要进行缩点，然后统计一下每一个强连通分量的出度和入度，然后统计出度和入度为 0 的个数取一个最大值即可。

三个重点：

1. 有一种特殊情况，所有边都连通时，无需加缆车，就直接输出 0。

2. 对于出度和入度为 0 的强连通分量个数，我们一定要加缆车。因为当一个强连通分量入度为 0 是，别的强连通分量无法进入此强连通分量，故要统计。而当一个强连通分量出度为 0 时，此强连通分量无法进入别的强连通分量，故要统计。易知最后需要取一个最大值。

3. 强连通分量必须是有向边，而此题正好是有向边。当相邻格子高度相等时，他们俩一定在一个强连通分量中，无需考虑。而高度不等时，只有从高往低连，不能从低往高连。综上是有向边。

AC CODE

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
inline int in(){
	int x=0,f=1;char c;
	c=getchar();
	while (c<'0'||c>'9'){
		if (c=='-')f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int dfn[250005],low[250005],cnt,s[250005],top,f[250005],tot,ru[250005],chu[250005];
int head[500005],id,n,m,ans1,ans2,a[505][505];
struct node{int to,nex;}w[1000005];//记得开四倍空间，上下左右都要加边
bool vis[250005];
inline void add(int x,int y,int xx,int yy){
	if (xx<1||yy<1||xx>n||yy>m||a[x][y]<a[xx][yy])return ;
	int u=(x-1)*m+y,v=(xx-1)*m+yy;//二维转一维
   	w[++id].to=v;
    w[id].nex=head[u];
    head[u]=id;
}
inline void Tarjan(int x){//Tarjan 板子
	low[x]=dfn[x]=++cnt;
	vis[x]=1;
	s[++top]=x;
	for (int i=head[x];i;i=w[i].nex){
		int y=w[i].to;
		if (!dfn[y]){
			Tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if (vis[y])low[x]=min(low[x],low[y]);
	}
	if (dfn[x]==low[x]){
		int y;tot++;
        do{
        	y=s[top--];
            f[y]=tot;
            vis[y]=0;
        }while(x!=y);
	}
}
int main(){
	m=in(),n=in();
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			a[i][j]=in();
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++){
			add(i,j,i,j-1);
			add(i,j,i,j+1);
			add(i,j,i-1,j);
			add(i,j,i+1,j);
		}
	n*=m;
	for (int i=1;i<=n;i++)if (!dfn[i])Tarjan(i);
	if (tot==1){puts("0");return 0;}//特判
	for (int i=1;i<=n;i++)
		for (int j=head[i];j;j=w[j].nex){
			int tmp=w[j].to;
			if (f[i]!=f[tmp])ru[f[i]]=1,chu[f[tmp]]=1;//统计每个强连通分量的入度和出度
		}
	for (int i=1;i<=tot;i++){//统计入度和出度为 0 的个数
		if (!ru[i])ans1++;
		if (!chu[i])ans2++;
	}
	printf ("%d",max(ans1,ans2));//取最大值
	return 0;
}

```


---

## 作者：tang_mx (赞：3)

相关内容：** Tarjan 缩点 **

一道不错的 Tarjan 缩点的题目。

### 分析

由于奶牛能向相邻的的方格之间滑雪，并且不能从低到高滑，这就有了建图的限制条件，需要判断能否满足将一个点与相邻的点建边。

建好图之后套上 Tarjan 缩点的板子，统计一下缩点之后每个点的出度和入度。

显然，我们需要将出度为 0 的点和入度为 0 的点之间建缆车，为了保证任意的点之间都能互通，建的缆车数量应该等于缩点后出度为 0 的点的个数和入度为 0 的点的个数的最大值。

### 注意
如果缩点后只有一个点，那么就不需要建缆车，这种情况需要特判。

```cpp
#include<iostream>
#include<cstdio>

using namespace std;

const int N=5e5+10,M=5e6+10;

struct Edge{
	int next,to;
}edge[M];

int n,m,num,head[N],g[550][550],in[N],out[N];
int dfn[N],low[N],st[N],scc[N],siz[N],top,cnt,idx;
bool ins[N];

void add(int u,int v){
	edge[++num].next=head[u];
	edge[num].to=v;
	head[u]=num;
}

void tarjan(int u){
	dfn[u]=low[u]=++cnt;
	ins[st[++top]=u]=true;
	for(int i=head[u];i;i=edge[i].next){
		int v=edge[i].to;
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(ins[v]){
			low[u]=min(low[u],dfn[v]);
		}
	}
	if(low[u]==dfn[u]){
		int v;idx++;
		do{
			v=st[top--];
			ins[v]=false;
			scc[v]=idx;
		}while(u!=v);
	}
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&g[i][j]);
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			if(i>1&&g[i-1][j]<=g[i][j])
				add((i-1)*n+j,(i-2)*n+j);
			if(i<m&&g[i+1][j]<=g[i][j])
				add((i-1)*n+j,i*n+j);
			if(j>1&&g[i][j-1]<=g[i][j])
				add((i-1)*n+j,(i-1)*n+j-1);
			if(j<n&&g[i][j+1]<=g[i][j])
				add((i-1)*n+j,(i-1)*n+j+1);
		}
	}
	int tot=n*m;
	for(int i=1;i<=tot;i++){
		if(!dfn[i])tarjan(i);
	}
	if(idx==1){
		printf("0");return 0;
	}
	for(int u=1;u<=tot;u++){
		for(int i=head[u];i;i=edge[i].next){
			int v=edge[i].to;
			if(scc[u]!=scc[v])
				out[scc[u]]++,in[scc[v]]++;
		}
	}
	int sum1=0,sum2=0;
	for(int i=1;i<=idx;i++){
		if(!out[i])sum1++;
		if(!in[i])sum2++;
	}
	printf("%d",max(sum1,sum2));
	return 0;
} 
```


---

## 作者：sane1981 (赞：3)

## 题目解读
**[原题传送门](https://www.luogu.com.cn/problem/P1653)**

一句话，求最少加多少条边使此无向图只有一个强连通分量。

建图应该不难想到，每个点连一条有向边到**比自己低或相等高**的点。

相等高？！说明这一些点可以互相联通，这么说把他们看成一个点，因为无论缆车装在哪个点上，都能达到相同的效果。恕我语文表达太烂，举个例子吧。

![](https://cdn.luogu.com.cn/upload/image_hosting/jf4yfiz0.png?x-oss-process=image/resize,m_lfit,h_860,w_900)

最终答案就是缩完点后入度为 $0$ 的点和出度为 $0$ 的点个数的最大值。

当然只有一个强连通分量是要特判 $0$。
## AC Code
```cpp
#include<bits/stdc++.h>
#include<vector>
#include<stack>
using namespace std;
const int dir[4][2]={{0,1},{0,-1},{-1,0},{1,0}};
const int N=250005; 
int W,L,h[505][505];
int ID(int x,int y){
	return (x-1)*L+y;
}
vector <int> E[N];
int dfn[N],low[N],col[N],colnum,dfnum;
bool ins[N],in[N],out[N];
stack <int> S;
void Tarjan(int u){
	dfn[u]=low[u]=++dfnum;
	S.push(u);ins[u]=true;
	for(int i=0;i<E[u].size();i++){
		int v=E[u][i];
		if(!dfn[v]){
			Tarjan(v);
			low[u]=min(low[v],low[u]);
		}else if(ins[v]) low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		col[u]=++colnum;
		ins[u]=false;
		while(S.top()!=u){
			col[S.top()]=colnum;
			ins[S.top()]=false;
			S.pop();
		}
		S.pop();
	}
}
int main(){
	scanf("%d%d",&L,&W);
	for(int i=1;i<=W;i++)
		for(int j=1;j<=L;j++)
			scanf("%d",&h[i][j]);
	for(int i=1;i<=W;i++)
		for(int j=1;j<=L;j++)
			for(int k=0;k<4;k++){
				int xx=dir[k][0]+i,yy=dir[k][1]+j;
				if(xx<1||xx>W||yy<1||yy>L) continue;
				if(h[i][j]>=h[xx][yy]) E[ID(i,j)].push_back(ID(xx,yy));
			}
	for(int i=1;i<=W*L;i++) if(!dfn[i]) Tarjan(i);
	for(int i=1;i<=W*L;i++)
		for(int j=0;j<E[i].size();j++)
			if(col[i]!=col[E[i][j]])
				in[col[E[i][j]]]=out[col[i]]=true;
	int ans1=0,ans2=0;
	for(int i=1;i<=colnum;i++){
		if(!in[i]) ans1++;
		if(!out[i]) ans2++;
	}
	if(colnum==1) printf("0\n");
	else printf("%d\n",max(ans1,ans2));
	return 0;
} 
```


---

## 作者：rechenz (赞：1)

# 题解
一句话：输出缩点后的出度为 $0$ 的点的个数和入度为 $0$ 的点的个数的最大值

首先对这个矩阵进行建模，如果能滑到就建一条单向边。
```cpp
for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(i>1&&a[i-1][j]<=a[i][j]){
                adding(cal(i,j),cal(i-1,j));
            }
            if(i<n&&a[i+1][j]<=a[i][j]){
                adding(cal(i,j),cal(i+1,j));
            }
            if(j>1&&a[i][j-1]<=a[i][j]){
                adding(cal(i,j),cal(i,j-1));
            }
            if(j<m&&a[i][j+1]<=a[i][j]){
                adding(cal(i,j),cal(i,j+1));
            }
        }
    }
```
然后使用 Tarjan 进行缩点，最后记录缩点后的入度和出度就可以了，答案就是出度为 $0$ 的强连通分量的个数和入度为 $0$ 的强连通分量的个数取 $\max$，最后不要忘了特判一下如果只有一个强连通分量的话就不需要建立任何一道缆车。
#### code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=250005;
int n,m,head[N],cnt,a[505][505];

struct Edge{
    int to;
    int next;
}e[4*N];

void adding(int u,int v){
    e[++cnt].to=v;
    e[cnt].next=head[u];
    head[u]=cnt;
}

int cal(int i,int j){
    return (i-1)*m+j;
}
int dfn[N],low[N],id,vis[N],is[N],tot;
stack<int> s;
void Tarjan(int x){//缩点
    dfn[x]=low[x]=++id;
    s.push(x);
    vis[x]=1;
    for(int i=head[x];i;i=e[i].next){
        int v=e[i].to;
        if(!dfn[v]){
            Tarjan(v);
            low[x]=min(low[v],low[x]);
        }else if(vis[v]){
            low[x]=min(low[x],dfn[v]);
        }
    }
    if(dfn[x]==low[x]){
        ++tot;
        while(s.top()!=x){
            int temp=s.top();
            s.pop();
            is[temp]=tot;
            vis[temp]=0;
        }
        int temp=s.top();
        s.pop();
        is[temp]=tot;
        vis[temp]=0;
    }
}
int in[N],out[N],tt1,tt2;
int main(){
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf("%d",&a[i][j]);
        }
    }
    for(int i=1;i<=n;i++){//建边
        for(int j=1;j<=m;j++){
            if(i>1&&a[i-1][j]<=a[i][j]){
                adding(cal(i,j),cal(i-1,j));
            }
            if(i<n&&a[i+1][j]<=a[i][j]){
                adding(cal(i,j),cal(i+1,j));
            }
            if(j>1&&a[i][j-1]<=a[i][j]){
                adding(cal(i,j),cal(i,j-1));
            }
            if(j<m&&a[i][j+1]<=a[i][j]){
                adding(cal(i,j),cal(i,j+1));
            }
        }
    }
    for(int i=1;i<=n*m;i++){
        if(!dfn[i]) Tarjan(i);
    }
    for(int k=1;k<=n*m;k++){//记录入度和出度
        for(int i=head[k];i;i=e[i].next){
            int v=e[i].to;
            if(is[v]!=is[k]){
                in[is[v]]++;
                out[is[k]]++;
            }
        }
    }
    for(int k=1;k<=tot;k++){
        if(!in[k]) tt1++;
        if(!out[k]) tt2++;
    }
    if(tot==1){//输出答案
        printf("0");
    }else{
        printf("%d",max(tt1,tt2));
    }
    return 0;
}
```


---

## 作者：ZBH_123 (赞：0)

## 思路：tarjan 缩点
根据题目，我们很明显可以想到，可以从高度高的点连一条有向边到高度低的点，这样题目就简化成了求至少加多少条边才能将一个有向图转化成强连通图。

建完图之后，我们就要面临这道题的难点——如何将一个有向图转化成强连通图。让我们先回顾一下强连通图的一个性质：任意两点间都有路径相连，也就是说，所有节点的出度和入度都不为 $0$。但是，如果所有节点所属的强连通分量节点个数都 $> 1$，就有可能出现这种情况：虽然所有节点的出入度都不为 $0$，但是图仍然不是强连通图。所以，我们要将强连通分量缩成一个节点，缩点后，我们就得到了一个 DAG,接下来要做的事就是“消灭”掉所有出入度为 $0$ 的点。由于连一条边就能“消灭”掉一个出度为 $0$ 的点和一个入度为 $0$ 的点，因此，假设出度为 $0$ 的点的数量为 $p$，入度为 $0$ 的点的数量为 $q$，则要连的边的数量为 $\max(p,q)$。特别的，当图本来就是一个强连通图时，$p$ 和 $q$ 都为 $1$，但是要连的边数为 $0$，所以输出时要特判一下。

附上 AC 代码：
```cpp
#include<iostream>
#include<stack>
using namespace std;
int n,m,a[501][501],cnt,s,dfn[250001],low[250001],scc[250001],in[250001],out[250001],p,q,head[250001],tot;
short vis[250001];
stack<int>st;
struct Edge{
	int to,next;
}edge[1000001];
void add(int a,int b){
	edge[++tot].to=b;
	edge[tot].next=head[a];
	head[a]=tot;
}
int getnum(int x,int y){
	return (x-1)*m+y;//二维变一维	
}
void get(int x1,int y1,int x2,int y2){
	if(x2<1||y2<1||x2>n||y2>m)//边界特判
		return;
	if(a[x1][y1]>=a[x2][y2])
		add(getnum(x1,y1),getnum(x2,y2));
}
void tarjan(int x){
	vis[x]=1,dfn[x]=low[x]=++s;
	st.push(x);
	for(int i=head[x];i;i=edge[i].next){
		if(!vis[edge[i].to]){
			tarjan(edge[i].to);
			low[x]=min(low[x],low[edge[i].to]);
		}
		else if(vis[edge[i].to]==1)
			low[x]=min(low[x],dfn[edge[i].to]);
	}
	if(dfn[x]==low[x]){
		cnt++;
		while(st.top()!=x){
			scc[st.top()]=cnt,vis[st.top()]=2;
			st.pop();
		}
		scc[x]=cnt,vis[x]=2;
		st.pop();
	}
}
int main(){
	cin>>m>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			get(i,j,i,j-1);//向四个方向建边
			get(i,j,i-1,j);
			get(i,j,i,j+1);
			get(i,j,i+1,j);
		}
	}
	for(int i=1;i<=n*m;i++)
		if(!vis[i])
			tarjan(i);
	for(int i=1;i<=n*m;i++){
		for(int j=head[i];j;j=edge[j].next){
			if(scc[i]!=scc[edge[j].to]){
				in[scc[edge[j].to]]++,out[scc[i]]++;//缩点统计出入度
			}
		}
	}
	for(int i=1;i<=cnt;i++){
		if(in[i]==0)
			p++;
		if(out[i]==0)
			q++;
	}
    if(cnt==1)
    	cout<<0;
    else
		cout<<max(p,q);
	return 0;
}
```

---

## 作者：IkunTeddy (赞：0)

# 思路分析
这个题一看就直接考虑 Tarjan 缩点，是一道非常好的 Tarjan 练手题。 虽然是一个矩形，但是只能走上下左右，只要给每个矩形中的点编号，只要能到就建一条边，这样一个矩形就变成一张图了。

这个题要求的答案就是再加几条边才能把缩完点后的图变成一个强连通图，我们想，一个强连通图中的每一个点是不是出度入度至少要为一，我们就可以统计一下，缩完点后的图中出度为零的有多少个点，入度为零的有多少个点。他们两两可以互补，剩下的就与其他点建边。所以说答案就是它们其中的最大值。

但有一个特殊情况，如果缩完点了后就只有一个点的话，就可以不用再建缆车，但是按照我们的思路就会错，所以要特判一个。~~这都是血的教训啊。~~

~~这个题应该没有蓝吧？~~
# 附上代码

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
int map[510][510];
int num[510][510];
int x2[5]={0,1,0,-1,0};//类似dfs走迷宫的方式预处理出四个方向的坐标
int y2[5]={0,0,1,0,-1};
const int maxn=1e6+10;
struct Edge{
	int v,next;
}edge[maxn];
int head[maxn],tot;
void add_edge(int u,int v){
	edge[++tot].v=v;
	edge[tot].next=head[u];
	head[u]=tot;
}
int dfn[maxn],low[maxn],vis[maxn];
stack<int>stk;
int SCC,scc[maxn];
void dfs_scc(int u){ //Tarjan求SCC
	dfn[u]=low[u]=++dfn[0];
	stk.push(u); 
	for(int i=head[u];i;i=edge[i].next){
		int v=edge[i].v;
		if(!dfn[v]){
			dfs_scc(v);
			low[u]=min(low[u],low[v]);
		}else if(vis[v]==0){
			low[u]=min(low[u],dfn[v]);
		}
	}
	if(low[u]==dfn[u]){
		SCC++;
		while(!stk.empty()){
			int x=stk.top();
			stk.pop();
			vis[x]=1;
			scc[x]=SCC;
			if(x==u)break;
		}
	}
}
vector<int>vt[maxn];
int in[maxn],out[maxn];
int main(){
	int w,l;
	cin>>w>>l;
	int n=0;
	for(int i=1;i<=l;i++){
		for(int j=1;j<=w;j++){
			cin>>map[i][j];
			num[i][j]=++n; //给每个矩形中的点编号，顺便统计节点个数
		}
	}
	for(int i=1;i<=l;i++){
		for(int j=1;j<=w;j++){
			for(int k=1;k<=4;k++){
				int dx=i+x2[k];
				int dy=j+y2[k];
				if(dx>=1&&dx<=l&&dy>=1&&dy<=w&&map[i][j]>=map[dx][dy]{//边界条件
					add_edge(num[i][j],num[dx][dy]);
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(dfn[i])continue;
		dfs_scc(i);
	}
	if(SCC==1){ //情况特判
		cout<<0;
		return 0;
	}
	for(int u=1;u<=n;u++){
		for(int i=head[u];i;i=edge[i].next){
			int v=edge[i].v;
			if(scc[u]==scc[v]){
				continue;
			}
			in[scc[v]]++;//出度，入度统计
			out[scc[u]]++;
		}
	}
	int s1=0,s2=0;	
	for(int i=1;i<=SCC;i++){
		if(out[i]==0){
			s1++;
		}else if(in[i]==0){
			s2++;
		}
	}
	cout<<max(s1,s2);

	return 0;
}//buyaochaotijie



```


---

## 作者：Leaper_lyc (赞：0)

不错的 Tarjan 缩点题。

考虑图论建模，每个格子都作为一个点，则第 $i$ 行的第 $j$ 格的编号为 $(i - 1) \times L+j$。我们将该点与上下左右相邻的格子进行连边（比该点小就连出边），这样我们会得到一张不一定联通的图。

然后跑一遍 Tarjan 模版，然后缩点，这样我们会得到一张有向无环图。

对于一个缩点后的一个“块”，若它的出度为 $0$，则可以将它连向一个没有入度的点，使图变成一个环。

对于一个缩点后的一个“块”，若它的入度为 $0$，则可以将它连向一个没有出度的点，也可以使图变成一个环。

当然，对于两个可以连起来的点，我们只要连一次边即可。

所以可以统计出度为 $0$ 的点的个数和入度为 $0$ 的点的个数，二者中的最大值即是答案。

注意要特判强连通分量数为 $1$ 的情况，此时输出 $0$ 即可。

[code](https://www.luogu.com.cn/record/122296205)

---

## 作者：1234567890sjx (赞：0)

首先肯定要缩点。把高度相同的相邻的所有的点缩成一个新的点。

然后容易发现对于新点所在的森林 $F$ 中存在入度为 $0$ 的点集 $p$ 和出度为 $0$ 的点集 $q$。

现在需要让图连通就是让点集 $p$ 和点集 $q$ 中的点进行相互的匹配。

于是答案就是 $\max(p,q)$。

---

## 作者：smyoking (赞：0)

## 题目大意

在一张图中，对于一个点，有多条出边，指向与它相连的并且海拔小于等于它的点。求最少要添加多少条边使得整个图强联通。

## 思路

 **Tarjan 缩点**。强连通图的概念是既可以通过有向边从 A 到 B，也可以通过有向边从 B 到 A，所以我们可以记录只有出边和只有入边的点取最大值（贪心思想，将这两种点两两配对）。
 
 ## Code
 
 ```cpp
//P1653 [USACO04DEC] Cow Ski Area G 
#include<bits/stdc++.h>

#define reg register

using namespace std;

inline int read() {
	int x=0,f=1;char s=getchar();
	while (s>'9'||s<'0') {
		if (s=='-') f=-f;
		s=getchar();
	}
	while (s>='0'&&s<='9') {
		x=x*10+s-'0';
		s=getchar();
	}
	return x*f;
}

const int N = 550;
const int xx[4]={-1,1,0,0};
const int yy[4]={0,0,-1,1};

int n,m,mmap[N][N],first[N*N],cnt,low[N*N],dfn[N*N],belong[N*N],in[N*N],out[N*N],tot,now;
int ans1,ans2;  //ans1 记录只有出边的点，ans2 记录只有入边的点 
stack<int>s;
bool instack[N*N];
struct edge{
	int to,nxt;
}edges[N*N*4];

int C(int i,int j) { return (i-1)*m+j; }  //将图中的坐标化成点，方便表示 

void add(int u,int v) {  //构图 
	edges[++cnt].to=v;
	edges[cnt].nxt=first[u];
	first[u]=cnt;
}

void dfs(int root) {  //缩点ing 
	dfn[root]=low[root]=++now;
	s.push(root);instack[root]=true;
	for (reg int t=first[root];t;t=edges[t].nxt) {
		int h=edges[t].to;
		if (!dfn[h]) dfs(h),low[root]=min(low[root],low[h]);
		else if (instack[h]) low[root]=min(low[root],low[h]);
	}
	if (low[root]==dfn[root]) {  //该点是强连通分量的源点(或者孤点) 
		tot++;
		while (1) {
			int h=s.top();s.pop();
			belong[h]=tot;instack[h]=false;
			if (h==root) break;
		}
	}
}

int main(){
	m=read();n=read();
	for (reg int i=1;i<=n;++i) {
		for (reg int j=1;j<=m;++j) mmap[i][j]=read();  
	}
	for (reg int i=1;i<=n;++i) {
		for (reg int j=1;j<=m;++j) {
			for (reg int f=0;f<4;++f) { 
				int to_x=i+xx[f],to_y=j+yy[f];
				if (to_x>=1&&to_x<=n&&to_y>=1&&to_y<=m&&mmap[i][j]>=mmap[to_x][to_y]) //满足条件，建边 
					add(C(i,j),C(to_x,to_y));
			}
		}
	}
	for (reg int i=1;i<=n;++i) 
		for (reg int j=1;j<=m;++j) if (!dfn[C(i,j)]) dfs(C(i,j));  //防止有节点没有遍历到 
	for (reg int i=1;i<=n;++i) {
		for (reg int j=1;j<=m;++j) {
			int root=C(i,j);
			for (reg int t=first[root];t;t=edges[t].nxt) {
				int h=edges[t].to;
				if (belong[root]==belong[h]) continue;  //这条边属于一个强连通分量里面的内边 
				out[belong[root]]++;in[belong[h]]++;  //记录缩点之后每个节点的入度和出度 
			}
		}
	}
	if (tot==1) {   //特判 
		printf("0\n");
		return 0;
	}
	for (reg int i=1;i<=tot;++i) {  //统计数量 
		if (!in[i]) ans1++;
		if (!out[i]) ans2++; 
	}
	printf("%d\n",max(ans1,ans2));  //输出最大值 
	return 0;
}
//end
```


---

## 作者：lfxxx (赞：0)

主要到互相可达这一要求。

我们知道一个强连通分量内的点一定是互相可达的，因此先将原图中的强连通分量缩成一个点。

随后我们发现，要让任意点互相可达只用考虑缩点后的图上出度或者入度为 $0$ 的点，因为其他点都可以通过往下走或者往回走到这些点。

于是我们考虑以某种方式把入度和出度为 $0$ 的点串起来，可以证明这种方案一定存在，因此答案就是两种点点数较大值。

注意特判假若只有一个强连通分量则不需要额外修建缆车。

```cpp
#include<bits/stdc++.h>
#define pos(i,j)((i-1)*m+j)
using namespace std;
const int maxn = 1e6+114;
vector<int> edge[maxn],road[maxn];
int dfn[maxn],low[maxn],vis[maxn],dfncnt;
stack<int> s;
int n,m;
int col[maxn],cl,dp[maxn];
int a[maxn];
int In[maxn],Out[maxn];
void tanjan(int u){
	dfn[u]=low[u]=++dfncnt;
	s.push(u);
	vis[u]=1;
	for(int v:edge[u]){
		if(!dfn[v]){
			tanjan(v);
			low[u]=min(low[u],low[v]);
		}	
		else if(vis[v]==1){
			low[u]=min(low[u],dfn[v]);
		}
	}
	if(low[u]==dfn[u]){
		cl++; 
		while(s.top()!=u){
			vis[s.top()]=0;
			col[s.top()]=cl;
			s.pop();
		}
		s.pop();
		//cout<<cl<<' '<<dp[cl]<<'\n';
		vis[u]=0;
		col[u]=cl;
	}
}
int ans1,ans2;
void build(){
	for(int i=1;i<=pos(n,m);i++){
		for(int nxt:edge[i]){
			int u=col[i],v=col[nxt];
			if(u==v) continue;
			In[v]++;
			Out[u]++;
		}
	}
	for(int i=1;i<=cl;i++) if(In[i]==0) ans1++;
	for(int i=1;i<=cl;i++) if(Out[i]==0) ans2++;
}
int dx[4]={0,0,-1,1};
int dy[4]={1,-1,0,0};
int main(){
ios::sync_with_stdio(0);
cin.tie(0);
cout.tie(0);
cin>>m>>n;
for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++) cin>>a[pos(i,j)];
for(int i=1;i<=n;i++){
	for(int j=1;j<=m;j++){
		for(int k=0;k<4;k++){
			int nx=i+dx[k],ny=j+dy[k];
			if(nx>=1&&nx<=n&&ny>=1&&ny<=m){
				if(a[pos(i,j)]>=a[pos(nx,ny)]){
					edge[pos(i,j)].push_back(pos(nx,ny));
				}	
			}
		}
	}
}
for(int i=1;i<=n;i++){
	for(int j=1;j<=m;j++) if(!dfn[pos(i,j)]) tanjan(pos(i,j));
}
if(cl==1){
	cout<<0;
	return 0;
}
build();
cout<<max(ans1,ans2);
return 0;
}
```


---

