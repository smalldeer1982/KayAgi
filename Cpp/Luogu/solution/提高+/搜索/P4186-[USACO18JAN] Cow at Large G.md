# [USACO18JAN] Cow at Large G

## 题目描述

最后，Bessie 被迫去了一个远方的农场。这个农场包含 $N$ 个谷仓（$2 \le N \le 10^5$）和 $N-1$ 条连接两个谷仓的双向隧道，所以每两个谷仓之间都有唯一的路径。每个只与一条隧道相连的谷仓都是农场的出口。当早晨来临的时候，Bessie 将在某个谷仓露面，然后试图到达一个出口。

但当 Bessie 露面的时候，她的位置就会暴露。一些农民在那时将从不同的出口谷仓出发尝试抓住 Bessie。农民和 Bessie 的移动速度相同（在每个单位时间内，每个农民都可以从一个谷仓移动到相邻的一个谷仓，同时 Bessie 也可以这么做）。农民们和 Bessie 总是知道对方在哪里。如果在任意时刻，某个农民和 Bessie 处于同一个谷仓或在穿过同一个隧道，农民就可以抓住 Bessie。反过来，如果 Bessie 在农民们抓住她之前到达一个出口谷仓，Bessie 就可以逃走。

Bessie 不确定她成功的机会，这取决于被雇佣的农民的数量。给定 Bessie 露面的谷仓K，帮助 Bessie 确定为了抓住她所需要的农民的最小数量。假定农民们会自己选择最佳的方案来安排他们出发的出口谷仓。

## 样例 #1

### 输入

```
7 1
1 2
1 3
3 4
3 5
4 6
5 7```

### 输出

```
3```

# 题解

## 作者：Mr_罗 (赞：20)

## $Part 0$：前言

这是本蒟蒻的第一篇题解，求赞 & 求管理员大大通过 $\text{QAQ}$ 

## $Part 1$：读题

题目要求：Bessie 在一棵根为 $K$ 号节点的树根上，要求在叶子节点上放置农民并最小化农民数量（农民可移动），使和农民速度相同的 Bessie 在不接触到农民的前提下无法走到任意一个叶子节点。~~真简洁~~

## $Part 2$：初步理清思路

### 思路一：硬怼！

就像 [大佬 @bessie_goes_moo 的思路](https://www.luogu.com.cn/blog/125322/solution-p4186) 那样，直接模拟题意。

预计时间复杂度：$\text{O}(ans \times n)$

最大时间复杂度：$\text{O}(n^2)$

~~好像能被卡掉（雾~~

### 思路二：正解

就是给**每一个**叶子节点放一个农民，让他们和 Bessie 一起走，看看 Bessie 能**遇到**几个人。

这里借用一下 @llzzxx712 大佬的图 ~~（我懒得画）~~：

![](https://cdn.luogu.com.cn/upload/image_hosting/qrvho2yu.png)

我们先给每个叶子节点安排一个农民：

（橙点为农民）

![](https://cdn.luogu.com.cn/upload/image_hosting/m8q6qvau.png)

然后让农民一直往上走，直到遇到 ~~会影分身的~~ Bessie，这里就是他们能控制的点：

（红点为农民可控制的点）

![](https://cdn.luogu.com.cn/upload/image_hosting/dij1ucb7.png)

然后开始 ```dfs```，让 Bessie 开始走。Bessie 遇到了两个红点，说明只需要两个农民就可以锁住 Bessie 了（在节点 $9 \ (10)$ 和节点 $17$ ）。

同理，我们也可以模拟一下样例。鉴于篇幅有限，我放在了 [云剪贴板](https://www.luogu.com.cn/paste/1yllm232) 里面，大家可自行观看。

## $Part 3$：深入思考，获得代码思路

大概思路一有，代码的思路也就出来了：在每一个被农民控制的点做一个标记，再遍历整棵树，遇到标记就 $\text{ans}$ 加一。最后输出 $\text{ans}$ 即可。

## $Part 4$：代码

这里我提供 $3$ 种不同的标记实现方式：

1. 在第一遍遍历的时候记录下每个结点的父亲节点，再单独从每个叶子节点向上反，做标记。


2. 在第一遍遍历的时候用一个栈记录路径，每次找到叶子节点就在 $($栈顶的位置 $\times \ \dfrac{1}{2}$ $)$ 处的节点做标记。


3. 在第一遍遍历的时候记录一个 $\text{down}$ 数组表示离这里最近的叶子节点的距离。在第二遍遍历的时候，如果当前的深度 $\ge$ 当前节点的 $\text{down}$ 值，就算遇到了标记。


------------

方式 $1$ 的代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

int n, k, a, b, l, fa[100001], dep[100001] = {-1}, ans;
bool leaf[100001], flag[100001];
vector<int> tree[100001];

void dfs1 (int i, int fr)
{
	leaf[i] = 1;
	fa[i] = fr;
	dep[i] = dep[fr] + 1;
	for (int k = 0; k < tree[i].size(); k++)
	{
		int now = tree[i][k];
		if (now != fr)
		{
			leaf[i] = 0;
			dfs1 (now, i);
		}
	}
}

void dfs2 (int i, int fr)
{
	if (flag[i])
	{
		ans++;
		return;
	}
	for (int k = 0; k < tree[i].size(); k++)
	{
		int now = tree[i][k];
		if (now != fr)
			dfs2 (now, i);
	}
}


int main()
{
	cin >> n >> k;
	fa[k] = 0;
	for (int i = 1; i < n; i++)
	{
		cin >> a >> b;
		tree[a].push_back (b);
		tree[b].push_back (a);
	}
	dfs1 (k, 0);
	for (int i = 1; i <= n; i++)
	{
		if (leaf[i])
		{
			int dis = i;
			for (int j = 1; j <= dep[i] / 2; j++)
				dis = fa[dis];
			flag[dis] = 1;
		}
	}
	dfs2 (k, 0);
	cout << ans;
	return 0;
}
```

[提交记录](https://www.luogu.com.cn/record/54107030)


------------

方式 $2$ 的代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

int n, k, a, b, l, st[100001], top, fa[100001], dep[100001] = {-1}, ans;
bool leaf[100001], flag[100001];
vector<int> tree[100001];

void dfs1 (int i, int fr)
{
	st[++top] = i;
	if (tree[i].size() == 1)
	{
		flag[st[top / 2 + 1]] = 1;
		top--;
		return;
	}
	for (int k = 0; k < tree[i].size(); k++)
	{
		int now = tree[i][k];
		if (now != fr)
			dfs1 (now, i);
	}
	top--;
}

void dfs2 (int i, int fr)
{
	if (flag[i])
	{
		ans++;
		return;
	}
	for (int k = 0; k < tree[i].size(); k++)
	{
		int now = tree[i][k];
		if (now != fr)
			dfs2 (now, i);
	}
}


int main()
{
	cin >> n >> k;
	fa[k] = 0;
	for (int i = 1; i < n; i++)
	{
		cin >> a >> b;
		tree[a].push_back (b);
		tree[b].push_back (a);
	}
	dfs1 (k, 0);
	dfs2 (k, 0);
	cout << ans;
	return 0;
}
```

[提交记录](https://www.luogu.com.cn/record/58808893)


------------

方案 $3$ 的代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

int n, k, a, b, down[100001], ans;
vector<int> tree[100001];

void dfs1 (int i, int fr)
{
	down[i] = 0x7fffffff;
	if (tree[i].size() == 1)
		down[i] = 0;
	
	for (int k = 0; k < tree[i].size(); k++)
	{
		int now = tree[i][k];
		if (now != fr)
		{
			dfs1 (now, i);
			down[i] = min (down[now] + 1, down[i]);
		}
	}
}

void dfs2 (int i, int fr, int deep)
{
	if (deep >= down[i])
	{
		ans++;
		return;
	}
	for (int k = 0; k < tree[i].size(); k++)
	{
		int now = tree[i][k];
		if (now != fr)
			dfs2 (now, i, deep + 1);
	}
}


int main()
{
	cin >> n >> k;
	for (int i = 1; i < n; i++)
	{
		cin >> a >> b;
		tree[a].push_back (b);
		tree[b].push_back (a);
	}
	dfs1 (k, 0);
	dfs2 (k, 0, 0);
	cout << ans;
	return 0;
}
```

[提交记录](https://www.luogu.com.cn/record/54256878)


------------

**完结撒花~~~**

---

## 作者：llzzxx712 (赞：17)

# P1486

[传送门](https://www.luogu.com.cn/problem/P4186)

## 题目分析
先来看样例
![](https://cdn.luogu.com.cn/upload/image_hosting/fvc2x3yg.png)

我们可以看到，我们需要在2、6、7三个节点上放村民才可以堵住Bessie。

**那么变一下呢？**

如果去掉节点7，那么我们就只需要在节点2、5上放村民就可以了。再看，需要的村民数从三个变成两个的关键点在哪里？**对，在节点3。**，变化后我们在5节点放村民，就可以占据这个点，就不需要在4上面放村民了。而因为他们的速度相同，决定是否可以占据节点3的关键就是以节点3为根的子树中深度最小的叶节点。

这时候我们需要自己构造更强力的数据来验证我们的猜想。（样例太水了）

![](https://cdn.luogu.com.cn/upload/image_hosting/qrvho2yu.png)

这张图我们可以看到只要在节点9（或10）和节点17放村民就可以了。

**如果去掉节点17呢？**

那么我们就需要在节点9、16、6放村民了。因为这个时候以2为根的子树深度最小的叶节点的深度从2变成了3（根节点深度为0）。

### 那如何分析子树中深度最小的叶节点深度够不够小呢？

我们看到，我们关注叶节点深度是为了看它能不能在Bessie从根节点到达该子树的根之前（或同时）到达子树的根。

也就是说，最浅叶节点到 子树根 的距离应该小于等于 树根 到 子树根的距离。只要满足了这一点，该子树就可以只放一个村民。否则我们就要继续去考虑这个子树的各个子树。

## 实现思路
邻接表存无向图，把k当成树根，每个点记录它的深度、以它为树根的子树中的最浅叶节点深度。这可以通过一次 dfs 求出。

然后再进行一次 dfs，对于一个子树，如果它的 最浅叶节点 到 子树根 的距离小于等于 树根 到 子树根的距离。那么就把答案 +1 （因为只要在最浅叶节点那放一个村民就可以了）。否则就分别求这个子树的若干个子树，并将答案累加（无法占据子树根节点，需要每条路连的子树都有村民堵上）。

## 易错点
- 根节点深度应该设为0，不然判断距离的时候可能会出错。

## 代码

内带详细注释。

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define N 100002
using namespace std;
void read(int &x) {
    int f = 1; x = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9')   {if (ch == '-') f = -1; ch = getchar();}
    while (ch >= '0' && ch <= '9') {x = x * 10 + ch - '0'; ch = getchar();}
    x *= f;
}
int n,k,tot,ans;//n,k如题目所示 
int to[N*2],ne[N*2],head[N],de[N],smin[N];//de存深度，smin[ i ]代表以 i 为根的子树的最浅叶节点深度 
void add(int x,int y){//领接表 
	to[++tot]=y,ne[tot]=head[x],head[x]=tot;
}
void dfs(int x,int fa){//第一次dfs求 de[]、smin[] 
	de[x]=de[fa]+1;
	int minn=de[x];//如果它是叶节点，那么以它为根的子树的最浅叶节点深度就是它自己 
	for(int i=head[x];i;i=ne[i]){
		int y=to[i];
		if(y==fa) continue;
		dfs(y,x);
		if(minn==de[x]) minn=smin[y];//它不是叶节点，将minn替换 
		else minn=min(minn,smin[y]);//从它的各个儿子中选出最小的 smin 即为它的 smin 
	}
	smin[x]=minn;//更新它的 smin 
}
void dfs2(int x,int fa){
	if(smin[x]<=de[x]*2){//最浅叶节点深度小于等于该节点深度的两倍 等价于 最浅叶节点 到 子树根 的距离小于等于 树根 到 子树根的距离 
		ans++;
		return;
	}
	for(int i=head[x];i;i=ne[i]){//否则求分别若干个子树 
		int y=to[i];
		if(y==fa) continue;
		dfs2(y,x);
	}
}
int main()
{
	cin>>n>>k;
	for(int i=1;i<n;i++){
		int x,y;
		read(x),read(y);
		add(x,y),add(y,x);
	}
	de[k]=-1;//这样就可以让根节点深度为 0 了 
	dfs(k,k);
	dfs2(k,k);
	cout<<ans;
	return 0;
}

```

~~**这篇题解写了本蒟蒻两个小时，给个赞呗**~~

---

## 作者：Parabola (赞：9)

### Part.0 题外话

奶牛题又开始被恶意评分了...

不过我认为还是一道很棒的题

如果没有人跟我说这题$O(N)$的话我可能会在二分这个死胡同里出不来

~~石上三年~~


------------

### Part1.思路

题面很简单，问Bessie从根节点出发，需要最少多少个FarmerJohn从叶子节点出发才能抓住Bessie，Bessie走到根节点就算赢。

然后首先这么想，如果把每个叶子节点都放一个农夫，那Bessie绝对死翘翘。换句话来说答案不会超过叶子节点的数量。

那哪些叶子节点能够省农夫呢？

如果农夫往上爬，每爬一步，那么以农夫现在所在的点为根节点的子树一定是被封锁死了（因为Bessie想要往这个子树走的话必然经过农夫。）

但如果Bessie已经在这个子树里了呢？

那最开始的那个农夫就指望不上了，只能放新农夫了（追及问题）

换句话来说，我们把当农夫走到$u$时，若以$u$为根的子树不可能存在Bessie，则记$u$能够被农夫控制。

接着有一个定理，如果$u$能被控制，那么$u$的整棵子树都能被控制（这是什么废话）。

那么我们只有对于所有满足“$u$能够被一个农夫控制，且$u$的父节点不能被农夫控制”的这种$u$放上一个农夫就好了。

题目就是求这种$u$的个数。

那节点$u$能够被控制，会有什么式子呢？

就是Bessie到$u$所花的单位时间比农夫到$u$的大（可以取等号，因为这个时候取等号的话Bessie和农夫刚好碰头，Bessie会被抓，也就是被控制）。

即$dep[u] - 1 >= nd[u] - dep[u] $

$dep[u]$代表$u$的深度，$nd[u]$代表以$u$为根的子树中，深度最浅的那个叶子节点的深度。

然后第一次$dfs$算出这两个数组再跑一次$dfs$就好啦。

------------

### Part3. Code

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;

const int MAXN = 100000 + 5;

int n , m , rt , f[MAXN] , nd[MAXN] , dep[MAXN];

vector <int> G[MAXN];

void add(int u , int v) {G[u].push_back(v);}

int dfs(int u , int fa) {
	f[u] = fa;
	dep[u] = dep[fa] + 1;
	bool leafy = true;
	for(int i = 0 , v ; i < (int)G[u].size() ; ++i) {
		if((v = G[u][i]) == fa) continue;
		nd[u] = min(dfs(v , u) , nd[u]);
		leafy = false;
	}
	if(leafy) return nd[u] = dep[u];
	return nd[u];
}

int dfs2(int u) {
	if(2 * dep[u] > nd[u]) return 1;
	int res = 0;
	for(int i = 0 , v ; i < (int)G[u].size() ; ++i) {
		if((v = G[u][i]) == f[u]) continue;
		res += dfs2(v); 
	}
	return res;
}

int main() {
	memset(nd , 0x3f , sizeof nd);
	scanf("%d %d" , &n , &rt);
	for(int i = 1 , u , v ; i < n ; ++i) {
		scanf("%d %d" , &u , &v);
		add(u , v) , add(v , u);
	}
	dfs(rt , 0); 
	printf("%d\n" , dfs2(rt));
	return 0;
}
```


---

## 作者：曹老师 (赞：8)

**知识点：DFS**

~~就是一个劲儿的深搜啊~~

介绍几个数组的作用：

dis：当作临时数组 diso：求根到每一个位置的距离 dist：求每一个点的最近的叶节点

再介绍dfs中参数p：

0：处理根到每个节点的距离 1：距离每个点的最近叶的距离 2：找答案
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue> 
#define MAXN 100005
#define LL long long
#define INF 2147483647
#define MOD 1000000007
#define free(s) freopen("s.txt","r",stdin);
#define lowbit(x) ((x&(-x))) 
using namespace std;
const int L=1e5+5;
int n,k,dis[L],ans,diso[L],dist[L];
vector<int>w[L];
void dfs(int o,int fa,int p)
{
	for(int i=0;i<w[o].size();i++)
	{
		int v=w[o][i];
		if(v==fa)
			continue;
		if(p==0)
		{
			diso[v]=diso[o]+1;
			dfs(v,o,0);
		}
		if(p==1)
		{
			dis[v]=dis[o]+1;
			if(w[v].size()==1)
			{
				dist[o]=min(dist[o],1);
				dist[v]=0;
			}
			else
			{
				dfs(v,o,1);
				dist[o]=min(dist[v]+1,dist[o]);
			}
		}
		if(p==2)
		{
			if(diso[v]>=dist[v])
				ans++;
			else
				dfs(v,o,2);
		}
	}
}
int main()
{
	memset(dis,0x3f,sizeof(dis));
	memset(dist,0x3f,sizeof(dist));
	scanf("%d%d",&n,&k);
	for(int i=1;i<n;i++)
	{
		int t1,t2;
		scanf("%d%d",&t1,&t2);
		w[t1].push_back(t2);
		w[t2].push_back(t1);
	}
	dfs(k,0,0);
	dis[k]=0;
	dfs(k,0,1);
	dfs(k,0,2);
	printf("%d",ans);
	return 0;
}
```

---

## 作者：communist (赞：6)

思路是覆盖子树，我们发现，农民想截住牛的最优策略是不断向上来尽可能地覆盖更大的子树

我们想要尽早地覆盖一个子树，一个显然的贪心是在这个子树中选取深度最小的一个放农民

如果我们在一个点放置了农民，那么其他点也会被覆盖，所有这个农民能够覆盖的叶子都不需要再放农民了

抽象出来，对于每个叶节点，都有一个深度，我们把叶节点按深度排序，然后每次选取深度最浅的点打标记，然后枚举每个点，把这个点能覆盖的点全部删去

那么我们怎样支持这样一种操作呢，我们可以用一个$set$，每次取出$s.begin$，考虑它是否能够覆盖点$x$，能够覆盖的前提是$d[begin]-d[lca]<=d[lca]$，即农民比奶牛先或同时走到$lca$

复杂度我不会证，如果有大佬看到可以帮忙证一下

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<set>
using namespace std;
const int maxn=1e5+10,lg=18;
struct edge{
	int next,to;
}e[maxn*2];
struct node{
	int d,id;
};
int n,k,head[maxn],cnt,ans,d[maxn],deg[maxn],sk[maxn][20];
set<node>s;
bool operator <(const node &x,const node &y)
{
	return x.d==y.d?x.id<y.id:x.d<y.d;
}
void add(int x,int y)
{
	e[++cnt].next=head[x];
	e[cnt].to=y;
	head[x]=cnt;
}
void make(int x,int pre)
{
	sk[x][0]=pre,d[x]=d[pre]+1;
	if(deg[x]==1)
		s.insert((node){d[x],x});
	for(int v,i=head[x];i;i=e[i].next)
		if((v=e[i].to)!=pre)
			make(v,x);
}
void equals(int &x,int h)
{
	for(int i=0;h;i++)
	{
		if(h&1)
			x=sk[x][i];
		h>>=1;
	}
}
int lca(int x,int y)
{
	if(d[x]<d[y])
		swap(x,y);
	equals(x,d[x]-d[y]);
	if(x==y)
		return x;
	for(int i=lg;i>=0;i--)
		if(sk[x][i]!=sk[y][i])
			x=sk[x][i],y=sk[y][i];
	return sk[x][0];
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int x,y,i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y),add(y,x);
		deg[x]++,deg[y]++;
	}
	if(deg[k]==1)
	{
		printf("1\n");
		return 0;
	}
	d[0]=-1;
	make(k,0);
	for(int i=1;i<=lg;i++)
		for(int j=1;j<=n;j++)
			sk[j][i]=sk[sk[j][i-1]][i-1];
	while(!s.empty())
	{
		node u=*s.begin();
		ans++;
		s.erase(s.begin());
		for(set<node>::iterator it=s.begin();it!=s.end();)
		{
			node tmp=*it;
			it++;
			if(d[u.id]<=2*d[lca(u.id,tmp.id)])
				s.erase(tmp);
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：bellmanford (赞：4)

```cpp
/*
当我们将奶牛的出发点作为树的顶点时
农民的出发点就是树的叶子节点
到顶点的路径只有一条
所以只需要将每一个叶子节点到顶点的路径对半分
得到从这个叶子节点出发抓到奶牛时的节点 
然后dfs 
*/
#include<iostream>
#include<cstdio>
using namespace std;
const int M=1e5+5;
int n,k,tot=0,ans=0,fa[M],cc[M],zx[M],dis[M],first1[M],first[M];//dis[i]表示i节点到顶点的距离 
bool vis[M];
struct Edge1{//正常建树 
	int nxt,to;
}e1[M<<1];
struct Edge{//建立简化版的树 
	int nxt,to,val;
}e[M<<1];

int read(){
	int x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*y;
}

void add1(int x,int y){
	tot++;
	e1[tot].nxt=first1[x];
	first1[x]=tot;
	e1[tot].to=y;
}

void add(int x,int y,int z){
	tot++;
	e[tot].nxt=first[x];
	first[x]=tot;
	e[tot].to=y;
	e[tot].val=z;
}

void build(int u,int f1,int f2,int t){
	int son=0;
	for(int i=first1[u];i;i=e1[i].nxt) if(e1[i].to!=f1) son++;
	if(son==0){
		cc[0]++;
		cc[cc[0]]=u;
	}
	if(son>1||son==0){
		fa[u]=f2;
		add(u,f2,t);
		add(f2,u,t);
	}
	for(int i=first1[u];i;i=e1[i].nxt){
		int v=e1[i].to;
		if(v!=f1){
			if(son>1){
				build(v,u,u,1);
			}
			else{
				build(v,u,f2,t+1);
			}
		}
	}
}

void check(int u,int f,int t){
	dis[u]=t;
	for(int i=first[u];i;i=e[i].nxt){
		int v=e[i].to,w=e[i].val;
		if(v!=f){
//			printf("%d --> %d : %d\n",u,v,w);
			check(v,u,t+w);
		}
	}
}

void make_zx(int u,int jl,int yl){
	if(jl<(dis[u]-dis[fa[u]])){
		zx[yl]=u;
		vis[u]=1;
	}
	else{
		make_zx(fa[u],jl-(dis[u]-dis[fa[u]]),yl);
	}
}

void find_ans(int u,int f){
	if(vis[u]==1){
		ans++;
		return;
	}
	for(int i=first[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=f){
			find_ans(v,u);
		}
	}
}

int main(){
	n=read(),k=read();
	for(int i=1;i<=n-1;i++){
		int a=read(),b=read();
		add1(a,b);
		add1(b,a);
	}
	tot=0;
	build(k,0,0,1);
	check(k,0,0);
	for(int i=1;i<=cc[0];i++){
		make_zx(cc[i],dis[cc[i]]/2,cc[i]);
//		printf("%d --> %d dis:%d\n",cc[i],zx[cc[i]],dis[cc[i]]);
	}
	find_ans(k,0);
	printf("%d\n",ans);
}
```


---

## 作者：DQYdqy (赞：3)

题意很简单，就是求让root无法走到其叶子节点的最少人数

问题就在于如何放卫兵

在深入研究后，我们就可以发现，每一个卫兵能够完全锁死所在子树，当且仅当**deep[i]>=deep[j]-deep[i](j表示卫兵所放位置，i是当前访问的节点，j是以i为根节点的子树中deep最浅的没有子节点的节点）**，（不懂的可以画下图，~~然而我也是在大佬的讲解之下搞懂的~~）有了这个结论之后，我们就可以开始做这道题了
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,root,cnt,ans,head[1000001],deep[100001];
int f[1000001];
bool v[1000001];
struct Edge{
    int nxt,to;
}tree[1000001];
void add(int a,int b)
{
    tree[++cnt].nxt=head[a];
    tree[cnt].to=b;
    head[a]=cnt;
}
void put_deep(int x,int dep)
{
    v[x]=true;
    deep[x]=dep;
    for(int i=head[x];i;i=tree[i].nxt)
    {
        int j=tree[i].to;
        if(!v[j])
        put_deep(j,dep+1);
    }
}
int dfs(int x)
{
    v[x]=false;
    int re=2147483647;
    for(int i=head[x];i;i=tree[i].nxt)
    {
        int zs=0;
        int j=tree[i].to;
        if(v[j]){
            zs=dfs(j);
            re=min(re,zs);
        }
    }
    if(re==2147483647)re=0;
    f[x]=re;
//	printf("%d %d\n",x,re);
    return re+1;
}
void find_ans(int x)
{	
    v[x]=true;
    if(f[x]<=deep[x]){
        ans++;
        return;
    }//如果符合，就放卫兵
    for(int i=head[x];i;i=tree[i].nxt)
    {
        int j=tree[i].to;
        if(!v[j])find_ans(j);
    }//否则，就继续往下搜
}
int main()
{
    scanf("%d%d",&n,&root);
    for(int i=1;i<n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        add(x,y);
        add(y,x);
    }
    put_deep(root,0);//预处理deep
    dfs(root);//预处理出每一个节点的deep[i]-deep[j]
    find_ans(root);
    printf("%d",ans);
    return 0;
}
```

---

## 作者：zjjws (赞：2)

Bessie 从 $k$ 出发，很明显是建一颗以 $k$ 为根的子树。

以下将视角转换到农民，目的是保护谷仓，防止 Bessie 跑到谷仓里。

对于下面的**安全**的理解：对于一种安排策略，若 Bessie 不可能经过某点（因为 Bessie 也知道农民的位置），则称这个点是安全的。也就是说，只要 Bessie 经过了这个点，它就一定会被抓。

而我们需要一种安排方案，使得根节点 $k$ 是安全的。

对于两个根节点 $x,y$，满足 $deep_x<deep_y$ （在树中的深度），设 $z=\operatorname {lca}(x,y)$。

若有 $deep_x-deep_z\le deep_z$ （农民从 $x$ 出发可以比 Bessie 更先到达 $z$ 或者同时到达），则 $y$ 是无用的谷仓，农民和 Bessie 都不用去管它（因为如果 $x$ 能被保护的话， $y$ 也一定能被保护）。

反之，则从 $x$ 出发的农民不能保护 $y$ 谷仓，$x$ 和 $y$ 彼此独立。

---

那么，对于树上任意一点 $z$，把以 $z$ 为根的子树中最浅的叶子节点称作 $x$。

若 $|x\to z|\le |root\to z|$（理解为向量大小比较，和前面的那个 $deep$ 加减是一个意思），则我们可以安排一个农民在 $x$ 使得子树 $z$ 安全。

否则呢？我们只需要让 $\forall u\to z$ 满足所有以 $u$ 为根的子树安全，那么 $z$ 就是安全的。

代码实现也是很简单的。

~~我当时补文化课作业，考试没时间了，五分钟敲的~~

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAX=1e5+3;
struct milk
{
    int to,next;
}a[MAX<<1];
int h[MAX];
int f[MAX];
bool vit[MAX];
int deep[MAX];
int m_d[MAX];
int nam;
int n,k;
inline void add(int x,int y){a[++nam].to=y;a[nam].next=h[x];h[x]=nam;}
inline void dfs(int x)
{
    m_d[x]=0x3f3f3f3f;
    vit[x]=true;
    bool bj=false;
    for(int i=h[x];i>0;i=a[i].next)
    if(!vit[a[i].to])
    {
        bj=true;
        deep[a[i].to]=deep[x]+1;
        dfs(a[i].to);
        m_d[x]=min(m_d[x],m_d[a[i].to]);
        f[x]+=f[a[i].to];
    }
    if(!bj)m_d[x]=deep[x];
    if(m_d[x]-deep[x]<=deep[x])f[x]=1;
    return;
}
LL rin()
{
    LL s=0;
    char c=getchar();
    bool bj=0;
    for(;(c>'9'||c<'0')&&c!='-';c=getchar());
    if(c=='-')c=getchar(),bj=true;
    for(;c>='0'&&c<='9';c=getchar())s=(s<<1)+(s<<3)+(c^'0');
    if(bj)return -s;
    return s;
}
int main()
{
    int i,j;
    n=rin();k=rin();
    int x,y;
    for(i=1;i<n;i++)x=rin(),y=rin(),add(x,y),add(y,x);
    dfs(k);
    printf("%d",f[k]);
    return 0;
}
```


---

## 作者：AuCloud (赞：1)

~~经典的树上问题///~~

考虑对于每个节点有一个牛到它的最短时间和农民到它的最短时间

对于每一棵子树只需要一个农民，当且仅当农民到它的根的最短时间小于牛到它的最短时间

（或者说，若农民到某一个节点的最短时间小于牛到它的最短时间，则当前节点与它的子树只需要一个农民）

否则应该在它的儿子上重新寻找其他节点更新答案

**↑这两句话是关键中的关键，请理解后再继续向下看**

而农民到某一节点的最短时间即为此节点子树上最浅的叶子到自己的距离，牛到它的最短时间显然是深度

考虑三次dfs，第一次维护深度`dep`，第二次维护子树上最浅的叶子到自己的距离`dis`，第三次统计答案

~~也许可以把2、3次合在一起~~

```cpp
#include <bits/stdc++.h>
using namespace std;
int dep[100001], head[100001], nxt[200001], to[200001], dis[200001], fa[100001], tot, ans;
void add(int x, int y)
{
    nxt[++tot] = head[x];
    head[x] = tot;
    to[tot] = y;
}
void dfs1(int x, int from, int dp)
{
    dep[x] = dp;
    fa[x] = from;
    for(int i = head[x]; i; i = nxt[i])
    {
        int y = to[i];
        if(y != from)
        {
            dfs1(y, x, dp + 1);
        }
    }
}
void dfs2(int x)
{
    bool fl = 0;
    for(int i = head[x]; i; i = nxt[i])
    {
        int y = to[i];
        if(y != fa[x])
        {
            fl = 1;
            dfs2(y);
            dis[x] = min(dis[x], dis[y] + 1);
        }
    }
    if(!fl) dis[x] = 0;
}
void dfs3(int x)
{
    for(int i = head[x]; i; i = nxt[i])
    {
        int y = to[i];
        if(y != fa[x])
        {
            if(dep[y] >= dis[y]) ans++;
            else dfs3(y);
        }
    }
}
int main()
{
    int n, rt;
    cin >> n >> rt;
    for(int i = 1; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        add(x, y);
        add(y, x);
    }
    memset(dis, 0x3f, sizeof(dis));
    dfs1(rt, 0, 0);
    dfs2(rt);
    dfs3(rt);
    cout << ans;
    return 0;
}

```

---

## 作者：EgLund (赞：0)

树形dp好题。

首先先变成有根树。

首先考虑最坏的情况：每一个出口都放一个看守，这样牛怎么也进不去。所以答案一定 $\le n-1$。

但是有一些看守就是可用可不用的。

但是看守是会动的，只要看守封锁住了一个节点，这个子树就被堵住了。

但是，如果牛已经溜进子树，这个看守就失宠了，只能换。

我们让一个最快的看守来，也需要 $upp\_son_i - dep_i$ 单位时间。

我们让它 $\le dep_i-1$（-1是因为 $dep_k = 1$），这样的节点个数就是最少的看守个数。

我们可以一遍dp预处理，再一遍dp求解。

Code：
```
#include<bits/stdc++.h>
using namespace std;

int n,k,fa[100005],upp_son[100005],dep[100005];
vector<int> g[100005];

int pre(int u,int f)
{
	fa[u]=f;dep[u]=dep[f]+1;
	bool isexit=1;
	for(int i=0;i<g[u].size();i++)
	{
		int v=g[u][i];
		if(v==f)continue;
		upp_son[u]=min(pre(v,u),upp_son[u]);
		isexit=0;
	}
	if(isexit)upp_son[u]=dep[u];
	return upp_son[u];
}

int sol(int u)
{
	if(2*dep[u]>upp_son[u])return 1;
	int ret=0;
	for(int i=0;i<g[u].size();i++)
	{
		int v=g[u][i];
		if(v==fa[u])continue;
		ret+=sol(v);
	}
	return ret;
}

int main()
{
	memset(upp_son,0x7f,sizeof(upp_son));
	cin>>n>>k;
	for(int i=1;i<n;i++)
	{
		int u,v;cin>>u>>v;
		g[u].push_back(v);g[v].push_back(u);
	}
	pre(k,0);cout<<sol(k);
}
```

---

## 作者：bessie_goes_moo (赞：0)

楼上众神仙写的都是正解，我的是在模拟赛瞎糊弄的（~~隔了一年前打的，今天又刷到了，然鹅我还是很菜，写的如下玄学算法~~）

大致思路就是让bessie向叶子跑，如果跑出去了在那里放个守卫重来一次，所以复杂度是O(Ans*N)的，但实际跑出来还是个玄学时效

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100005;
int Q[maxn],son[2*maxn],lnk[maxn],nxt[2*maxn],ANS[maxn],s,du[maxn],tot,n;
bool vis[maxn],Bissie[maxn];
inline int read(){
	int red=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){ if(ch=='-') f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9') red=red*10+ch-48,ch=getchar();
	return red*f;
}
void add_e(int x,int y){
    son[++tot]=y,nxt[tot]=lnk[x],lnk[x]=tot,du[y]++;
}
void BFS(){
	memset(vis,0,sizeof vis);
	int hed=0,til=0;
	for(int i=1;i<=ANS[0];i++) Q[++til]=ANS[i],Bissie[ANS[i]]=0,vis[ANS[i]]=1;
	Q[++til]=s,vis[s]=1,Bissie[s]=1;
	while(hed<til){
		int x=Q[++hed];
		for(int j=lnk[x];j;j=nxt[j])
	    if(!vis[son[j]]){ 
	    	if(du[son[j]]==1&&Bissie[x]){
			    ANS[++ANS[0]]=son[j];BFS();return;
			}
	    	vis[son[j]]=1,Q[++til]=son[j],Bissie[son[j]]=Bissie[x];
	    }
	}
}
int main(){
	freopen("atlarge.in","r",stdin);
	freopen("atlarge.out","w",stdout);
	n=read(),s=read();
	for(int i=1;i<n;i++){int x=read(),y=read();add_e(x,y),add_e(y,x);}
	if(du[s]==1){ANS[++ANS[0]]=s;}
	BFS();
	printf("%d\n",ANS[0]);
	return 0;
}
```


---

## 作者：Patrickpwq (赞：0)

我是用树形DP做的 设dp[i]表示在i点的子树放多少个守卫

显然 有方程

if (mind[i]-(depth[i]-1)<=depth[i]) (其中mind表示i的子树内的叶子节点最浅的深度) dp[i]=1 即守卫可以抓到这个人

else dp[i]=Sigma{dp[i.son]}
```cpp
#include<bits/stdc++.h>
const int N=100005;
using namespace std;
template<class T>
inline void read(T &x)
{
	x=0;
	static char ch=getchar();
	while(!isdigit(ch))	ch=getchar();
	while(isdigit(ch))	x=x*10+ch-'0',ch=getchar();
}
int n,root;
struct Edge
{
	int to,next;
}edge[2*N];
int first[N],tot;
inline void addedge(int x,int y)
{
	tot++;
	edge[tot].to=y; edge[tot].next=first[x]; first[x]=tot;
}
int depth[N],mind[N],son[N],dp[N];	//dp[i]:在i点的子树放多少个守卫 
void dfs1(int now,int fa)
{
	son[now]=1;
	depth[now]=depth[fa]+1;
	for(int u=first[now];u;u=edge[u].next)
	{
		int vis=edge[u].to;
		if(vis==fa)	continue;
		dfs1(vis,now);
		son[now]+=son[vis];
	}
}
void dfs2(int now,int fa)
{
	if(son[now]==1)	
	{
		mind[now]=depth[now];
		return;
	}
	for(int u=first[now];u;u=edge[u].next)
	{
		int vis=edge[u].to;
		if(vis==fa)	continue;
		dfs2(vis,now);
		mind[now]=min(mind[now],mind[vis]);
	}
}
void dfs3(int now,int fa)
{
	if(son[now]==1)
	{
		dp[now]=1;
		return; 
	}
	bool flag=0;
	for(int u=first[now];u;u=edge[u].next)
	{
		int vis=edge[u].to;
		if(vis==fa)	continue;
		dfs3(vis,now);
		int ti=depth[now]-1;	//走了多深就走了多久
		int h=mind[now]-ti;	//最屌的守卫的位置 
		if(h<=depth[now])	flag=1;
	}
	if(flag)	dp[now]=1;
	else
	{
		for(int u=first[now];u;u=edge[u].next)
		{
			int vis=edge[u].to;
			if(vis==fa)		continue;
			dp[now]+=dp[vis];
		}
	}
}
int main()
{
	cin>>n>>root;
	for(int i=1,u,v;i<=n-1;i++)
	{
		read(u); read(v);
		addedge(u,v); addedge(v,u);
	}
	memset(mind,0x3f,sizeof(mind));
	dfs1(root,0);
	dfs2(root,0);	
	dfs3(root,0);
	cout<<dp[root];
	return 0; 
}
```

---

## 作者：elijahqi (赞：0)

http://www.elijahqi.win/2018/02/02/luogu4186-usaco18jancow-at-large-g/
http://blog.csdn.net/elijahqi/article/details/79243189
题目描述

Cornered at last, Bessie has gone to ground in a remote farm. The farm consists of

NN

N barns (

2≤N≤1052 \leq N \leq 10^5

2≤N≤105 ) and

N−1N-1

N−1 bidirectional tunnels between barns, so that there is a unique path between every pair of barns. Every barn which has only one tunnel is an exit. When morning comes, Bessie will surface at some barn and attempt to reach an exit.

But the moment Bessie surfaces, the law will be able to pinpoint her location. Some farmers will then start at various exit barns, and attempt to catch Bessie. The farmers move at the same speed as Bessie (so in each time step, each farmer can move from one barn to an adjacent barn). The farmers know where Bessie is at all times, and Bessie knows where the farmers are at all times. The farmers catch Bessie if at any instant a farmer is in the same barn as Bessie, or crossing the same tunnel as Bessie. Conversely, Bessie escapes if she reaches an exit barn before any farms catch her.

Bessie is unsure about her chances of success, which depends on the number of farmers that the law is able to deploy. Given that Bessie surfaces at barn

KK

K , help Bessie determine the minimum number of farmers who would be needed to catch Bessie, assuming that the farmers distribute themselves optimally among the exit barns.
输入输出格式

输入格式：

The first line of the input contains

NN

N and

KK

K . Each of the following

N−1N-1

N−1 lines specify two integers, each in the range

1…N1 \ldots N

1…N , describing a tunnel between two barns.

输出格式：

Please output the minimum number of farmers needed to ensure catching Bessie.
输入输出样例

输入样例#1： 复制

7 1
1 2
1 3
3 4
3 5
4 6
5 7

输出样例#1： 复制

3

题意：求给定一个点 使得他无法走到叶子节点我需要在叶子节点上安排的最小人数 并且我叶子节点上的人可以走动 但和牛的走动速度一样  尝试画图之后可以发现如果我这个节点控制的叶子节点最近的那个走到这里比bessy走到这里还要近说明我这里放一个即可 如果不行说明我需要递归下去去做 使得可以被封死 那么显然变成了一个子问题就树形dp搞一下 一遍dfs维护最小值 还有距离 比较下直接更新答案即可
```
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110000
using namespace std;
inline char gc(){
    static char now[1<<16],*S,*T;
    if (T==S){T=(S=now)+fread(now,1,1<<16,stdin);if (T==S) return EOF;}
    return *S++;
}
inline int read(){
    int x=0,f=1;char ch=gc();
    while(ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=gc();}
    while(ch<='9'&&ch>='0') x=x*10+ch-'0',ch=gc();
    return x*f;
}
struct node{
    int y,next;
}data[N<<1];
int n,k,ans,dp[N],min1[N],dis[N],num,h[N];
inline void dfs(int x,int fa){
    int tmp=0,nm=0;
    for (int i=h[x];i;i=data[i].next){
        int y=data[i].y;if (y==fa) continue;++nm;dis[y]=dis[x]+1;dfs(y,x);tmp+=dp[y];
    }if (!nm) min1[x]=0;min1[fa]=min(min1[fa],min1[x]+1);if(dis[x]>=min1[x]) dp[x]=1;else dp[x]=tmp;
}
int main(){
//	freopen("atlarge.in","r",stdin);
//	freopen("atlarge.out","w",stdout);
    n=read();k=read();memset(min1,0x3f,sizeof(min1));
    for (int i=1;i<n;++i){
        int x=read(),y=read();
        data[++num].y=y;data[num].next=h[x];h[x]=num;
        data[++num].y=x;data[num].next=h[y];h[y]=num;
    }
    for (int i=h[k];i;i=data[i].next){
        int y=data[i].y;dis[y]=1;dfs(y,k);ans+=dp[y];
    }printf("%d\n",ans);
    return 0;
}

```

---

