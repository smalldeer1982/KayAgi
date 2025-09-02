# Berland and the Shortest Paths

## 题目描述

Berland 有 $n$ 座城市。一些城市通过道路连接。所有道路都是双向的。每条道路连接两个不同的城市。一对城市之间至多有一条道路。城市从 $1$ 到 $n$ 编号。

众所周知，从首都（编号为 $1$ 的城市），您可以沿着道路移动并到达任何其他城市。

Berland 的总统计划改善该国的道路网。预算足以修复 $n-1$ 道路。总统计划选择 $n-1$ 条道路，要求：

- 从首都出发沿着这 $n-1$ 条道路走可以到达其他所有的城市。
- 如果 $d_i$ 表示首都到 $i$ 号城市所需经过的路的条数，沿着选择的 n-1 条路走所得的 $d_1$+$d_2$+・・・+$d_n$ 应是最小的。

换句话说，这 $n-1$ 条道路的应该保持国家的连通性，并且使从城市 $1$ 到所有城市的距离的总和最小（你只能使用被选择的 $n-1$ 道路）。

总统命令有关部门准备 $k$ 个可能的选择，选择的 $n-1$ 条道路同时满足以上两个条件。

编写一个程序，找到 $k$ 种可能的方法来选择道路进行维修。如果少于 $k$ 种选法，则程序应输出所有可能的有效方式来选择道路。

## 样例 #1

### 输入

```
4 4 3
1 2
2 3
1 4
4 3
```

### 输出

```
2
1110
1011
```

## 样例 #2

### 输入

```
4 6 3
1 2
2 3
1 4
4 3
2 4
1 3
```

### 输出

```
1
101001
```

## 样例 #3

### 输入

```
5 6 2
1 2
1 3
2 4
2 5
3 4
3 5
```

### 输出

```
2
111100
110110
```

# 题解

## 作者：xixiup (赞：15)

#### 引入算法

（已经学会最短路径树的同学们可以跳过这一部分）

对于这道题，我们要先引入一个概念：最短路径树。

最短路径树是一个图的生成树，该树有一个原点s，使得对于每个节点，都有对于其任何一个节点$i$，都有在原图中s到i的最短路等于在该树中$s$到$i$的距离，而在满足上述条件后，要求使得树的边权和最小。

具体地讲，就是对于任意$i$都有$ans_i=dis_i$，其中$ans_i$表示原图中原点到i的最短路径的长度，$dis_i$为在该最短路径树中原点到$i$的距离。

这道题看似和最小生成树有着千丝万缕的关系，但是其实与最小生成树没有什么关系。

可以思考，最短路径树要求满足的首要条件是最短路，而边权和最小只是在满足首要条件下，达到的最优情况，故可以考虑$dijkstra$算法。

考虑$dijkstra$可知，该算法是由一个集合不断往里面加入节点，从而得到从某一个节点出发到所有节点的最短路，这个过程中共往里面加入了$n-1$个节点，对于每一个节点都是由一条边拉进来的，故其实运行$dijkstra$时就无形的形成了一棵树，且这棵树的性质满足我们第一点中的性质。$dijkstra$模板参考如下：

```cpp
priority_queue<pair<int,int> >q;//使用堆维护当前最小值
memset(ans,0x7f,sizeof(ans));
ans[s]=0,in[s]=1;
q.push(make_pair(0,s));//加入源点
while(!q.empty()){
	int x=q.top.second;
	q.pop();
	in[x]=0;//松弛节点x
	for(int i=bg[x];i;i=ne[i]){
		int y=to[i];
		if(ans[x]+le[i]<ans[y]){
			ans[y]=ans[x]+le[i];//更新答案
			if(in[y]==0){
				q.push(make_pair(-ans[y],y));
				in[y]=1;//in数组很重要，防止多次将一个点加入堆中
			}
		}
	}
}
```

那么现在需要考虑第二个问题：如何使权值和最小？

考虑如下这个图

![](https://cdn.luogu.com.cn/upload/image_hosting/ox667d9t.png)

假如$1$为源点，点$1,2,3$已经在集合中，那么对于点$4$，有两条最短路径可供选择：路径$1-3-4$与路径$1-2-4$，对于已在集合中的点来说，两条路径对这个集合中的答案没有影响，而无论是哪一条路径，点$5$都可由点$4$拓展来，且权值都为$4$。

所以对于每一个点，其无论选择哪一条边，只要使得到源点的距离最小，对其他点都是没有影响的，所以应选最短的一条边。

这就是整个算法，下面看代码：

（具体参考[CF545E Paths and Trees](https://www.luogu.com.cn/problem/CF545E)）

```cpp
//ed[i]表示从集合到点i的所有满足dijkstra要求的边中最短的一条的编号
//nu[i]表示这一条边的编号，用于记录整个生成树
priority_queue<pai<int,int> >q;
memset(ans,0x7f,sizeof(ans));
q.push(make_pair(0,s));
ans[s]=0;in[s]=1;
while(!q.empty()){
	int x=q.top().second;
	q.pop();
	in[x]=0;
	for(int i=bg[x];i;i=ne[i]){//前面部分同上面的代码
		int y=to[i];
		if(ans[x]+le[i]==ans[y]&&le[ed[y]]>le[i]){
			ed[y]=i;//如果距离相等，则选较短一边
		}
		if(ans[x]+le[i]<ans[y]){
			ed[y]=i;//距离较短则直接更新
			ans[y]=ans[x]+le[i];
			if(in[y]==0){
				in[y]=1;
				q.push(make_pair(-ans[y],y));
			}
		}
	}
}
```

最后统计则有如下代码：

```cpp
int sum=0;//sum记录最小的边权和
for(int i=1;i<=n;i++){
	if(i==s){
		continue;
	}
	sum+=le[ed[i]];
}
cout<<sum<<"\n";
for(int i=1;i<=n;i++){
	if(i==s){
		continue;
	}
	printf("%lld ",nu[ed[i]]);//输出每一个节点对应的边
}
```


#### 解题思路

阅读题意可知，此题就是要求求最短路径树的方案数，此时可以思考，若对于每一条被拓展的边，我们都可以将其连入点集中所有最小边都记录下来，则处理答案时即可枚举每一个点，将其对应的边枚举一次，由于每条边只会由一个节点记录，即时间复杂度为$O(m)$，不会$TLE$。

但是如果使用链式前向星存图则会造成严重的不方便，因为你需要开两组链式前向星，对于正常写法来说有严重的不舒服，而开$n^2$的数组则有大约$1.5×10^5$MB，会严重$MLE$，所以推荐使用vector存边

而最后统计答案则可以使用大法师$（dfs）$算法，简洁易懂，方便编写。

还有一点值得注意，就是该题边权为1，所以可将$dijkstra$改为$bfs$，优化一个$log_n$的时间复杂度。

```cpp
queue<int>q;
void bfs(){
	memset(ans,0x7f,sizeof(ans));
	q.push(1);//从一号节点开始
	ans[1]=0;in[1]=1;
	while(!q.empty()){
		int x=q.front();
		q.pop();
		if(in[x]==1){
			continue;
		}
		in[x]=1;
		for(int i=bg[x];i;i=ne[i]){
			int y=to[i];
			if(ans[x]+1==ans[y]){
				//把所有可以将点y拉进树中的边加入vector
				v[y].push_back(nu[i]);
			}
			if(ans[x]+1<ans[y]){
				v[y].clear();//前面的边不满足第一条性质，需要删掉
				v[y].push_back(nu[i]);
				ans[y]=ans[x]+1;
				q.push(y);
			}
		}
	}
}
```

然后就是输出方案的$dfs$了

```cpp
void dfs(int x){//这里要注意，x是从2开始的
	//因为1号节点是原点，并没有对应边
	if(x>n){
		t++;
		for(int i=1;i<=m;i++){
			printf("%lld",pd[i]);
		}
		cout<<"\n";
		if(t>=e){//如果方案数达到要求直接结束
			exit(0);
		}
		return;
	}
	for(int i=0;i<v[x].size();i++){//枚举每一条对应边
		if(pd[v[x][i]]==1){
			continue;
		}
		pd[v[x][i]]=1;
		dfs(x+1);
		pd[v[x][i]]=0;
	}
}
```



---

## 作者：LawrenceSivan (赞：12)

# CF1005F Berland and the Shortest Paths

updated：在和同机房同学讨论时发现了一组极其诡异的数据，于是增加了部分说明。
## 前言

最近在做最短路径树的题目，于是刷到了这个。

感觉还是挺有意思的。

## 最短路径树

关于最短路径树的概念介绍以及基本求法，可以看看我的[这一篇题解](https://www.luogu.com.cn/blog/LawrenceSivan/cf545e-paths-and-trees-zui-duan-lu-jing-shu-post)，就不再赘述了，这里主要说一下这道题的做法。

## 本题思路

首先大家都知道，最短路径树并不一定是唯一的。

当出现了很多条距离相等的最短路的时候，这些都可以成为最短路径树上的边。

于是我们只需要在记录前驱的时候记录一下都有哪些相等的路径可以扩展出这个节点就可以了。

这些都会对结果产生贡献。

根据乘法原理，对于每个点，我们直接把前驱个数乘起来，得到的就是总方案数。

$tot$ 千万别忘记赋值成 $1$。

```cpp
inline bool check_k(){
	for(re int i=2;i<=n;i++){
		if(tot*vec[i].size()>k){
			return 0;	
		}
		else tot*=vec[i].size();
	}
	return 1;
}
```

这里需要极其注意一点！

这里千万不能写成这样：

```cpp
for (int i = 2; i <= n; i++) {
	ans *= vec[i].size();
}
printf("%lld\n", min(ans, k));
```

这一题有一个极其诡异的数据 #26,它会导致 $ans$ 在某一次执行乘法的时候直接溢出，并且十分诡异的是，他会直接变成 $0$，这就导致剩下的 $ans$ 一直都是 $0$，然后最后取 min 的时候就会输出 $0$。

~~在此谴责毒瘤hack者~~

然后可怜的同机房 wiki 同学调了半天才搞出这个诡异的玩意。

所以一定要及时判断，不能全都执行完毕乘法才判断。

## 细节问题：

关于存图：

前向星存图是没问题的。

问题在于对于每一个节点，都要维护一个前驱集合。

然后直接空间就 $O(n^2)$。

然后要是再开一个静态数组那可能就死的比较惨。

于是考虑用 `std::vector` 来存储前驱集合。

关于最短路径树求法：

>如果 $d_i$ 表示首都到 $i$ 号城市所需经过的路的条数，沿着选择的 $n-1$ 条路走所得的 $d_1+d_2+\cdots+d_n$ 应是最小的。

于是这题就有了边权都是 $1$ 的极其优美的性质。

于是对于边权都是 $1$ 的情况，我们就完全没有必要去跑 Dijkstra 了，直接广搜就行。

复杂度直接掉一个 $\log$。

$O((n+m)\log n->O(n+m)$

```cpp
inline void bfs(int s){
	queue <int> q;
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0;
	q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();
		if(vis[u])continue;
		vis[u]=true;
		for(re int i=head[u];i;i=nxt[i]){
			int v=to[i];
			if(dis[v]>=dis[u]+1){
				dis[v]=dis[u]+1;
				vec[v].push_back(i);
				q.push(v);
			}
		}
	}
}
```

关于输出答案：

因为我们记录并保留了每个节点的所有前驱，所以直接 dfs 枚举一下就行了。

多于 $k$ 个直接结束程序就行。

```cpp
void dfs(int step){
	if(step==n+1){
		for(re int i=1;i<=m;i++){
			printf("%d",vis[i]);
		}
		puts("");
		Case++;
		if(Case>=k){//多于k个，结束
			exit(0);
		}
		return;
	}
	for(re int i=0;i<vec[step].size();i++){
		vis[(vec[step][i]+1)/2]=1;
		dfs(step+1);
		vis[(vec[step][i]+1)/2]=0;
	}
}
```
这里说一下，为什么是 $(vec[step][i]+1)/2$，因为存的是双向边，导致双向边有了不同的 $id$，于是我们只取一半。 

## CODE:

```cpp

//#define LawrenceSivan

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define re register
const int maxn=2e5+5;
#define INF 0x3f3f3f3f

int n,m,k;

int head[maxn],nxt[maxn<<1],to[maxn<<1],cnt;

inline void add(int u,int v){
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
}

int dis[maxn];

vector <int> vec[maxn];

bool vis[maxn];//这个数组可以两用，在bfs里用来判断点来没来过，在dfs中用于输出答案

ll tot=1;//千万别忘记赋值成 1

inline void bfs(int s){
	queue <int> q;
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0;
	q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();
		if(vis[u])continue;
		vis[u]=true;
		for(re int i=head[u];i;i=nxt[i]){
			int v=to[i];
			if(dis[v]>=dis[u]+1){
				dis[v]=dis[u]+1;
				vec[v].push_back(i);
				q.push(v);
			}
		}
	}
}
inline bool check_k(){
	for(re int i=2;i<=n;i++){
		if(tot*vec[i].size()>k){
			return 0;	
		}
		else tot*=vec[i].size();
	}
	return 1;
}

int Case;

void dfs(int step){
	if(step==n+1){
		for(re int i=1;i<=m;i++){
			printf("%d",vis[i]);
		}
		puts("");
		Case++;
		if(Case>=k){
			exit(0);
		}
		return;
	}
	for(re int i=0;i<vec[step].size();i++){//枚举
		vis[(vec[step][i]+1)/2]=1;
		dfs(step+1);
		vis[(vec[step][i]+1)/2]=0;
	}
	
}

inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
    return x*f;
}

int main(){
#ifdef LawrenceSivan
    freopen("aa.in","r",stdin);
    freopen("aa.out","w",stdout);
#endif
	n=read();m=read();k=read();
	for(re int i=1,u,v;i<=m;i++){
		u=read(),v=read();
		add(u,v);
		add(v,u);
	}
	
	bfs(1);
	memset(vis,0,sizeof(vis));
    
	printf("%lld\n",check_k()?tot:k);
	dfs(2);//从2开始，1没有边。

	return 0;
}
```

---

## 作者：leozhang (赞：5)

这题不错...

首先，不难看到他想让你求出的是最短路树

然后，考虑到所有边权均为1，所以可以采用bfs直接生成最短路树

至于方案的储存，可以在加边的时候同时记录边的编号，然后对每个点维护一个能转移他的最短路的边的编号的集合，这样总的方案数就是所有的集合大小的乘积

然后用dfs在每个集合中选一个元素输出即可

```cpp
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
struct Edge
{
    int next;
    int to;
    int num;
}edge[400005];
int head[200005];
int dep[200005];
vector <int> v[200005];
int used[200005];
int cnt=1;
int n,m,k;
void init()
{
    memset(head,-1,sizeof(head));
    cnt=1;
}
void add(int l,int r,int v)
{
    edge[cnt].next=head[l];
    edge[cnt].to=r;
    edge[cnt].num=v;
    head[l]=cnt++;
}
void bfs(int rt)
{
    queue <int> M;
    M.push(rt);
    dep[rt]=0;
    while(!M.empty())
    {
        int u=M.front();
        M.pop();
        for(int i=head[u];i!=-1;i=edge[i].next)
        {
            int to=edge[i].to;
            if(!dep[to])
            {
                dep[to]=dep[u]+1;
                v[to].push_back(edge[i].num);
                M.push(to);
            }else if(dep[to]==dep[u]+1)
            {
                v[to].push_back(edge[i].num);
            }
        }
    }
}
int cct=0,tot=1;
void dfs(int dep)
{
    if(dep==n+1)
    {
        for(int i=1;i<=m;i++)
        {
            printf("%d",used[i]);
        }
        printf("\n");
        cct++;
        if(cct==tot)
        {
            exit(0);
        }
        return;
    }
    for(int i=0;i<v[dep].size();i++)
    {
        used[v[dep][i]]=1;
        dfs(dep+1);
        used[v[dep][i]]=0;
    }
}
inline int read()
{
    int f=1,x=0;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int main()
{
    n=read(),m=read(),k=read();
    init();
    for(int i=1;i<=m;i++)
    {
        int x=read(),y=read();
        add(x,y,i);
        add(y,x,i);
    }
    bfs(1);
    for(int i=2;i<=n;i++)
    {
        if((long long)tot*v[i].size()>k)
        {
            tot=k;
            break;
        }else
        {
            tot*=v[i].size();
        }
    }
    printf("%d\n",tot);
    dfs(2);
    return 0;
}
```

---

## 作者：tommymio (赞：3)

首先可以看出符合题目中两个条件的一定是最短路径树，但最短路径树显然不唯一。

我们对于点 $u$ 维护一个可能成为一棵最短路径树上的边的边集 $E_u$，形式化的说有 $E_u=\{v\to u:v\in V,dis_u=dis_v+1\}$，其中 $dis_u$ 为 $1\to u$ 的最短路。

可以证明从每个 $u\neq 1$ 的 $E_u$ 中取一条边构成的 $n-1$ 个点的图一定是一个连通图，并且进一步我们还可以证明它是一棵最短路径树。读者可以尝试使用归纳证明法自行证明。

于是我们可以爆搜方案，方案数也可以算出来：

$$
ans=\prod_{u\neq 1} |E_u|
$$



---

## 作者：Miko35 (赞：2)

这里补充一下关于 “为什么求的是最短路径树” 和 “解法的正确性” 两个问题的证明。

## 最短路径树

考虑一个连通无向图 $G$，一个以顶点 $v$ 为根节点的最短路径树 $T$ 是图 $G$ 满足下列条件的生成树：树 $T$ 中从根节点 $v$ 到其它顶点 $u$ 的路径距离，在图 $G$ 中是从 $v$ 到 $u$ 的最短路径距离。

对于此题来讲，以 $1$ 为根的最短路径树便是原图满足以下条件的生成树：该树上从 $1$ 到任意点的路径长与原图这两点间的最短路相等。

可以理解为，将原图删去某些边，只留下一棵树，使得从 $1$ 到其他点的最短路长度不变。

## 为什么求的是最短路径树

引理：对于无向正权连通图，最短路径树一定是存在的。

证明：考虑 Dij 算法的过程，就是每次扩展一个距离最小的点更新最短路。类比于 Prim 算法，如果点 $u$ 此时由点 $v$ 更新过来，那么就相当于将 $u$ 加入进目前的生成树里面来，也就是将 $u,v$ 连边。所以跑 Dij 的过程实际上就是像 Prim 一样将生成树由起点一步步扩展，最终得到的是最短路径树。

此题对这个生成树的限制是最短路之和最小，也就是我们要证明“若此生成树最短路之和最小的，那么它是 SPT”。

考虑去证明它的逆否命题“若此生成树不是 SPT，则其最短路之和不是最小的”。

考虑最短路径树的定义，对于任意一个生成树，记 $d_v$ 为树上从 $1$ 到 $v$ 的距离，$dis_v$ 为原图 $1$ 到 $v$ 的最短路，有 $d_v\geq dis_v$。而此生成树不是最短路径树，则必然存在一个 $v$ 使得 $d_v\neq dis_v$，也就是 $d_v > dis_v$，而 $\sum_{u\neq v}d_u \geq \sum_{u\neq v}dis_u$，所以 $\sum d > \sum dis$，最短路之和不是最小的，证毕。所以这题求的是 SPT。

## 解法及其证明

先说解法:

对于每个点 $i$ 都维护一个边的集合 $S_i$。

对于点 $u$ 和一条权值为 $w$ 的边 $(u,v)$，记 $dis_i$ 为起点到 $i$ 最短路，若 $dis_u=dis_v+w$，则将这条边加入 $S_u$。

最后对于除起点外的每个点 $u$，在 $S_u$ 中任选一条边。这些边所组成的生成树一定是一棵 SPT。

---

证明：先证明它的形态是一棵树。

由于它是一个 $n-1$ 条边的边集，所以只需要证明它是联通的即可，即它覆盖了所有的点。对于除起点外的任意一个点 $u$，由于最短路径树必然存在，所以它一定有父节点 $v$，且 $dis_v=dis_u-w<dis_u$。若 $v=1$，则 $u$ 显然与 $1$ 联通；反之，则有 $dis_v>0=dis_1$，则递归到 $v$ 的父亲 $v_2$ 有 $dis_{v_{2}}<dis_v$，一直递归下去，若当前节点的 $dis$ 不为 $0$ 则可以不断减小，一定可以递归到出发点，所以 $u$ 与出发点联通。所以任取两点 $u,v$，有 $u$ 与 $1$ 联通且 $1$ 与 $v$ 联通，证毕。

然后每个点的最短路与原图相等，考虑用归纳法。任取一个点 $u$，若从 $1$ 到 $u$ 的父节点上的路径上的所有点都满足此性质，又因为 $d_u=d_{fa_u}+w=dis_{fa_u}+w=dis_u$，所以 $u$ 也满足此性质。又因为根节点 $1$ 有 $d_1=dis_1=0$，所以所有点满足此性质。

这个结论如果用一句话解释大概是，一个点在 SPT 中的父节点是在原图跑 Dij 过程中能够更新它的点中的任意一个。

利用这个结论也是可以解决 SPT 计数的问题的，也就是将所有的集合大小乘起来。

## 代码

1k 左右，大概只有一个 Dij，个人认为非常好写。

```cpp
#include<bits/stdc++.h>
#define rgi register int
typedef long long ll;
using namespace std;
inline void read(){}template <typename T,typename... Ts> inline void read(T& A,Ts&... As){
	T x=0,f=1;char ch=getchar();
	while(!(ch&16)){if(ch=='-')f=-1;ch=getchar();}
	while(ch&16)x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	A=x*f,read(As...);
}
const int N=200010;
int n,m,u,v,to;
struct node{int id,d;};
bool operator<(node a,node b){return a.d>b.d;}
int e[N],d[N],vis[N];
vector<int>a[N],ch[N];
priority_queue<node>q;
ll k,res=1;
void dfs(rgi x){
	if(x>n){
		for(rgi i=1;i<=m;++i)putchar((e[i]<0)+'0');
		return puts(""),void(--k);
	}
	for(rgi to:ch[x]){
		if(!k)return;
		e[to]=~e[to],dfs(x+1),e[to]=~e[to];
	}
}
int main(){
	read(n,m,k);
	for(rgi i=1;i<=m;++i){
		read(u,v),e[i]=u^v;
		a[u].push_back(i),a[v].push_back(i);
	}
	memset(d,127,sizeof d);
	d[1]=0,q.push(node{1,0});
	while(!q.empty()){
		int x=q.top().id;
		q.pop();
		if(vis[x])continue;
		vis[x]=1;
		for(rgi i:a[x]){
			if(d[to=e[i]^x]>d[x]+1){
				d[to]=d[x]+1;
				if(!vis[to])q.push(node{to,d[to]});
			}
		}
	}
	for(rgi i=1;i<=n;++i){
		for(rgi j:a[i])if(d[to=e[j]^i]==d[i]+1)ch[to].push_back(j);
	}
	for(rgi i=2;i<=n;++i){
		res*=(ll)ch[i].size();
		if(res>k)break;
	}
	k=min(res,k),cout<<k<<'\n',dfs(2);
	return 0;
}
```



---

## 作者：_棉花糖_ (赞：2)

翻译一下（笔者人工翻译，非机翻），之后就是最短路树的问题啦，代码&分析来自@leozhang
[leozhang的题解](https://www.luogu.org/blog/leozhang/solution-cf1005f)

### 题目描述

Berland里有n个城市，被道路连接。每条路都是双向的，它们连接着两个不同的城市，两个城市中最多只有一条路。城市的编号为1-n。

从首都（编号为1）出发，沿着这些路你能到达任意一个城市。

Berland的总统计划改善一下国家的交通网，预算足够修建n-1条路。总统想选择这n-1条路：
1、沿着这n-1条路，可以从首都到任何一个城市；
2、如果从首都到城市i需要走$d_{i}$条路，那么在这n-1条路中，$d_{1}$+$d_{2}$+……+$d_{n}$最小。

换句话说，这n-1条路应该能连接整个国家，并且从首都（city 1）到所有城市的距离最短（你只能选择n-1条路）。

总统指示外交部准备选择n-1条路的k种可能，使上面两个条件都能得到满足。请你写一个程序，找出这k种可能（如果少于k种方法，则输出所有满足条件的有效途径）。

### 输入格式

第一行包括3个整数，n,m,和k。
n是城市的数量，m是道路的数量，k是选项的数量。
其中2≤n≤$2\times10^{5}$,n-1≤m≤$2\times10^{5}$,1≤k≤$2\times10^{5}$，保证$m\times k$≤$10^{6}$;

下面m行每行两个整数$a_{i}$,$b_{i}$，表示第i条道路连接的城市数量。两个城市之间最多有一条路。给定的一组道路可以从首都到达任何城市。
其中1≤$a_{i}$,$b_{i}$≤n,且$a_{i} \neq b_{i}$

### 输出格式

第一行打印方法数t(1≤t≤k)。回想一下，您需要找到k个不同的选项；如果少于k个，则需要找到所有可能的不同有效选项。

在下面的t行中，打印选项，每行一个，将选项打印为长度为m的字符串。如果选项中包含第j条道路，则其中第j个字符等于“1”；如果不包含道路，则打印为“0”。道路应根据其输入顺序进行编号。选项可以按任意顺序打印。t个选项应不同。

因为$m\times k$≤$10^{6}$，所以t条线路的总长度不会超过$10^{6}$

如果有几个答案，输出其中任何一个。



### 分析

~~这题不错...~~

首先，不难看到他想让你求出的是最短路树

然后，考虑到所有边权均为1，所以可以采用bfs直接生成最短路树

至于方案的储存，可以在加边的时候同时记录边的编号，然后对每个点维护一个能转移他的最短路的边的编号的集合，这样总的方案数就是所有的集合大小的乘积

然后用dfs在每个集合中选一个元素输出即可

```cpp
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
struct Edge
{
    int next;
    int to;
    int num;
}edge[400005];
int head[200005];
int dep[200005];
vector <int> v[200005];
int used[200005];
int cnt=1;
int n,m,k;
void init()
{
    memset(head,-1,sizeof(head));
    cnt=1;
}
void add(int l,int r,int v)
{
    edge[cnt].next=head[l];
    edge[cnt].to=r;
    edge[cnt].num=v;
    head[l]=cnt++;
}
void bfs(int rt)
{
    queue <int> M;
    M.push(rt);
    dep[rt]=0;
    while(!M.empty())
    {
        int u=M.front();
        M.pop();
        for(int i=head[u];i!=-1;i=edge[i].next)
        {
            int to=edge[i].to;
            if(!dep[to])
            {
                dep[to]=dep[u]+1;
                v[to].push_back(edge[i].num);
                M.push(to);
            }else if(dep[to]==dep[u]+1)
            {
                v[to].push_back(edge[i].num);
            }
        }
    }
}
int cct=0,tot=1;
void dfs(int dep)
{
    if(dep==n+1)
    {
        for(int i=1;i<=m;i++)
        {
            printf("%d",used[i]);
        }
        printf("\n");
        cct++;
        if(cct==tot)
        {
            exit(0);
        }
        return;
    }
    for(int i=0;i<v[dep].size();i++)
    {
        used[v[dep][i]]=1;
        dfs(dep+1);
        used[v[dep][i]]=0;
    }
}
inline int read()
{
    int f=1,x=0;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int main()
{
    n=read(),m=read(),k=read();
    init();
    for(int i=1;i<=m;i++)
    {
        int x=read(),y=read();
        add(x,y,i);
        add(y,x,i);
    }
    bfs(1);
    for(int i=2;i<=n;i++)
    {
        if((long long)tot*v[i].size()>k)
        {
            tot=k;
            break;
        }else
        {
            tot*=v[i].size();
        }
    }
    printf("%d\n",tot);
    dfs(2);
    return 0;
}
```

最后声明，翻译非机翻，为笔者人工翻译，分析&代码来自[leozhang的题解](luogu.org/blog/leozhang/solution-cf1005f)



---

## 作者：lfxxx (赞：1)

注意到我们要最小化最短路之和，所以考虑建出 **最短路树** 具体来说就是将每个节点的最短路上的前驱作为父亲，具体来说假若 $dis_{j} + 1 = dis_{i}$ 那么 $j$ 可以作 $i$ 的父亲，那么先 BFS 一遍求出最短路，在 DFS 枚举每个节点可能的父亲即可，时间复杂度是 $O(n + m \times k)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+114;
int n,m;
int dis[maxn];
int vis[maxn];
vector<int> edge[maxn];
map< pair<int,int> ,int> f;
inline void add(int u,int v,int pos){
edge[u].push_back(v);
f[make_pair(u,v)] = pos;
}
void bfs(){
    for(int i=1;i<=n;i++) dis[i]=INT_MAX;
    queue<int> q;
    q.push(1);
    dis[1]=0;
    while(q.size()>0){
        int s=q.front();
        q.pop();
        if(vis[s]==1) continue;
        vis[s]=1;
        for(int nxt:edge[s]){
            dis[nxt]=min(dis[nxt],dis[s]+1);
            q.push(nxt);
        }
    }
}
int answer[maxn];
vector<int> output[maxn];
int tot,k;
void dfs(int pos){
    if(pos>n){
        tot++;
        output[tot].push_back(0);
        for(int i=1;i<=m;i++)
            output[tot].push_back(answer[i]);
        return ;
    } 
    for(int lst:edge[pos]){
        if(dis[lst]==dis[pos]-1){
            answer[f[make_pair(lst,pos)]]=1;
            dfs(pos+1);
            answer[f[make_pair(lst,pos)]]=0;
            if(tot>=k) return ;
        }
    }
}
int main(){
cin>>n>>m>>k;
for(int i=1;i<=m;i++){
int u,v;
cin>>u>>v;
add(u,v,i);
add(v,u,i);
}
bfs();
dfs(2);
cout<<tot<<'\n';
for(int i=1;i<=tot;i++){
    for(int j=1;j<=m;j++) cout<<output[i][j];
    cout<<'\n';
}
}
```


---

## 作者：Andrew82 (赞：1)

**analysis**

这道题是用最短路树（图）做的

要证明(理解)最短路树（图）就是本题的合法答案的话，有下面两种方式

- 假设我们现在有随机的一个方案（n-1条边），那么对于每一个点i，如果它的$d_i$在用方案里n-1条边的时候不是最小值的话说明还可以更改路径使得$d_i$更小,而最短路树(图)上面的每个点的$d_i$都是最小的,因此总和$\sum d_i$也是最小的


- 假设最短路树所给出的方案不是最小的,那么假设有另一个树A使得A给出的方案最小,那么必然有某一点i使得A中的$d_i$小于最短路树中的$d_i$这与最短路树的定义矛盾


于是先求出最短路树(其实本题中求出的是最短路图(一个DAG),因为最短路树在本题中是不唯一的)

而本题要求输出的是方案总数和具体方案,实质上就是在最短路图中求选择n-1条边的方案数和具体方案,那么根据乘法原理,方案数=$\prod_{u\in[1,n]} fa[u].size()$(fa[u].size(),u的可选父节点的个数),输出方案数也就是枚举每一个点的可选边然后打标记罢了


**code**


```cpp
#include<bits/stdc++.h>
using namespace std;
#define loop(i,start,end) for(int i=start;i<=end;++i)
#define anti_loop(i,start,end) for(register int i=start;i>=end;--i)
#define clean(arry,num) memset(arry,num,sizeof(arry))
#define ll long long
template<typename T>void read(T &x){
	x=0;char r=getchar();T neg=1;
	while(r>'9'||r<'0'){if(r=='-')neg=-1;r=getchar();}
	while(r>='0'&&r<='9'){x=(x<<1)+(x<<3)+r-'0';r=getchar();}
	x*=neg;
}
int n,m,k;
const int maxn=2e5+10;
const int maxm=2e5+10;
const int maxk=1e5+10;
struct node{
	int e;
	int w;
	int id;
	int nxt;
}edge[maxm<<1];
int head[maxn];
int cnt=0;
inline void addl(int u,int v,int id){
	edge[cnt].e=v;
	edge[cnt].w=1;
	edge[cnt].id=id;
	edge[cnt].nxt=head[u];
	head[u]=cnt++;
}
struct point{
	int pos;
	int w;
	point():pos(0),w(0){}
	point(int pos,int w):pos(pos),w(w){}
	friend bool operator<(point a,point b){
		return a.w>b.w;
	}
};
priority_queue<point>q;
int dis[maxn];
int f[maxn];
vector<int>vec[maxn];
inline void dijkstra(int S){
	clean(dis,0x3f);
	dis[S]=0;
	q.push(point(S,0));
	while(q.empty()==false){
		int f=q.top().pos;
		q.pop();
		for(int i=head[f];i!=-1;i=edge[i].nxt){
			int v=edge[i].e;
			if(dis[v]>dis[f]+edge[i].w){
				vec[v].push_back(edge[i].id);
				dis[v]=dis[f]+edge[i].w;
				q.push(point(v,dis[v]));
			}
			else if(dis[v]==dis[f]+edge[i].w)
				vec[v].push_back(edge[i].id);
		}
	}
}
int usd[maxm];
int tot=1;
int num=0;
void dfs(int dep){
	if(dep==n+1){
        for(int i=1;i<=m;i++){
            printf("%d",usd[i]);
        }
        printf("\n");
        num++;
        if(num==tot){
            exit(0);
        }
        return;
    }
    for(int i=0;i<vec[dep].size();i++){
        usd[vec[dep][i]]=1;
        dfs(dep+1);
        usd[vec[dep][i]]=0;
    }
}
int main(){
	clean(head,-1);
	clean(usd,0);
	read(n);
	read(m);
	read(k);
	loop(i,1,m){
		int ai,bi;
		read(ai);
		read(bi);
		addl(ai,bi,i);
		addl(bi,ai,i);
	}
	dijkstra(1);
	loop(i,2,n){
		tot*=vec[i].size();
		if(tot>=k){
			tot=k;
			break;
		}
	}
	printf("%d\n",tot);
	dfs(2);
	return 0;
}
```


---

## 作者：FReQuenter (赞：0)

前置知识：[最短路径树](https://www.baidu.com/s?ie=utf-8&f=8&rsv_bp=1&tn=49055317_56_hao_pg&wd=%E6%9C%80%E7%9F%AD%E8%B7%AF%E5%BE%84%E6%A0%91&oq=%25E6%259C%2580%25E7%259F%25AD%25E8%25B7%25AF%25E6%25A0%2591&rsv_pq=fbe258320002c433&rsv_t=b655aZZN0sjZ%2FFSl5XujiaTjZEa9K9mtSzita%2FxXZKclBLDuHURZSMhTEqQJMdvbjl9MkS19k0Sk&rqlang=cn&rsv_dl=tb&rsv_enter=1&rsv_sug3=10&rsv_sug1=9&rsv_sug7=100&rsv_sug2=0&rsv_btype=t&inputT=3476&rsv_sug4=4149)。

题目要求保留的每一条边使得原图中到达每一个点的最短路径不变，就是最短路径树的模板。

所以先建出最短路径树。由于边权都是 $1$，不需要使用 dijkstra，可以直接 bfs。

考虑如何求一共有多少可能的方案。我们记录每一个点被在最短路上的所有前驱，每个点前驱数量的乘积就是答案。输出时可以通过 dfs 来输出具体方案。注意乘法中大于 $k$ 时要及时退出。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k,cnt,ans=1,dist[1000005];
vector<int> gv[1000005],pre[1000005];
bool vis[1000005];
map<pair<int,int>,int> mp;
void bfs(){
	queue<int> q;
	q.push(1);
	while(!q.empty()){
		int p=q.front();
		q.pop();
		for(auto nx:gv[p]){
			if(!dist[nx]){
				pre[nx].push_back(mp[{p,nx}]);
				q.push(nx);
				dist[nx]=dist[p]+1;
			}
			else if(dist[nx]==dist[p]+1){
				pre[nx].push_back(mp[{p,nx}]);
			}
		}
	}
}
void dfs(int now){
	if(now==n){
		for(int i=1;i<=m;i++) cout<<vis[i];
		cnt++;
		if(cnt==ans) exit(0);
		cout<<'\n';
		return;
	}
	for(auto nx:pre[now+1]){
		vis[nx]=1;
		dfs(now+1);
		vis[nx]=0;
	}
}
signed main(){
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		gv[x].push_back(y);
		gv[y].push_back(x);
		mp[{x,y}]=i,mp[{y,x}]=i;
	}
	bfs();
	for(int i=2;i<=n;i++){
		if(pre[i].size()) ans*=pre[i].size();
		if(ans>k){
			ans=k;
			break;
		}
	}
	cout<<ans<<'\n';
	dfs(1);
}
```

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2100}$
---
### 解题思路：

问题分为两个部分，如何求出最小路径生成树以及如何进行方案数的计数。

对于前者，不考虑本题的特殊性质，一种比较一般的方法是用 $\text{Dijkstra}$ 跑一遍，将任意一条可以进行更新的边作为加入的边。特殊地，如果要求总边权最小，需要将最短的一条路加入。

而这道题目所有的边权都为 $1$，所以可以直接使用 $\text{BFS}$ 进行路径的统计，将所有的能够更新的边全都统计下来。在这些被统计的边里，每一个点任意选择一条边都可以作为一种可行的方案。

根据乘法原理，可以得到最后的总方案数为 $\prod_{i=1}^ncnt_i$，最后直接使用一个 $\text{DFS}$ 进行一个方案的输出就行了。

---
### 代码：

```cpp
#include<cstdio>
#include<queue>
using namespace std;
const int MAXN=400005;
int n,m,k,head[MAXN],nxt[MAXN],num[MAXN],head1[MAXN],nxt1[MAXN],num1[MAXN],x,y,tot,tot1,dis[MAXN],cnt[MAXN];
int vis[MAXN],id[MAXN],book[MAXN],ans_cnt,flag;
queue <int> q;
void add(int x,int y){
	nxt[++tot]=head[x];
	head[x]=tot;
	num[tot]=y;
}
void add1(int x,int y,int ID){
	cnt[x]++;
	nxt1[++tot1]=head1[x];
	head1[x]=tot1;
	num1[tot1]=y;
	id[tot1]=ID;
}
void bfs(int S){
	q.push(S);
	for(int i=1;i<=n;i++)dis[i]=2147483647;
	dis[1]=0;vis[1]=1;
	while(!q.empty()){
		int now=q.front();
		q.pop();
		for(int i=head[now];i;i=nxt[i]){
			if(dis[now]+1<=dis[num[i]]){
				dis[num[i]]=dis[now]+1;
				add1(num[i],now,(i+1)/2);
				if(vis[num[i]]==0){
					vis[num[i]]=1;
					q.push(num[i]);
				}
			}
		}
	}
}
int calc(){
	int now=1;
	cnt[1]=1;
	for(int i=1;i<=n;i++){
		if(now>=k)return k;
		now*=cnt[i];
	}
	return now;
}
void dfs(int now){
	if(flag)return;
	if(now==n+1){
		for(int i=1;i<=m;i++)printf("%d",book[i]);
		printf("\n");
		ans_cnt++;
		if(ans_cnt==k)flag=1;
		return;
	}
	for(int i=head1[now];i;i=nxt1[i]){
		book[id[i]]=1;
		dfs(now+1);
		if(flag)return;
		book[id[i]]=0;
	}
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	bfs(1);
	printf("%d\n",calc());
	dfs(2);
	return 0;
}
```


---

## 作者：Phartial (赞：0)

首先不难发现，如果一条边不在 $1$ 号点到其余任意点的最短路上面，则一定不可能被选。

那么可以考虑先使用 BFS 求出 $1$ 号点到其他点的最短路，然后枚举每条边，如果这条边在最短路上，那么加入结果边集，然后直接从 $2$ 号点开始爆搜即可求出答案，由于题目要求最多只要求出 $k$ 条，所以时间复杂度是 $O(m+k)$ 的。

```cpp
#include <iostream>
#include <vector>
// #define TIME

using namespace std;
using LL = long long;
using Pll = pair<LL, LL>;

const int kN = 2e5 + 1;
using S = string;

int n, m, k, d[kN], q[kN], h = 1, t;
vector<Pll> e[kN];
vector<int> p[kN];
vector<S> v;
S s;

void R(int x, int _d) {
  if (d[x] > _d) {
    d[x] = _d, q[++t] = x;
  }
}
void D(int x) {
  if (v.size() >= k) {
    return;
  }
  if (x > n) {
    v.push_back(s);
    return;
  }
  for (int i : p[x]) {
    s[i - 1] = '1', D(x + 1), s[i - 1] = '0';
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> m >> k;
  for (int i = 1, x, y; i <= m; ++i) {
    cin >> x >> y;
    e[x].push_back({i, y}), e[y].push_back({i, x});
  }
  fill(d + 1, d + n + 1, 1 << 30);
  for (R(1, 0); h <= t; ++h) {
    int x = q[h];
    for (auto i : e[x]) {
      R(i.second, d[x] + 1);
    }
  }
  for (int i = 2; i <= n; ++i) {
    for (auto j : e[i]) {
      if (d[j.second] + 1 == d[i]) {
        p[i].push_back(j.first);
      }
    }
  }
  s = string(m, '0'), D(2);
  cout << v.size() << endl;
  for (auto &&i : v) {
    cout << i << endl;
  }
#ifdef TIME
  fprintf(stderr, "\nTIME: %dms", clock());
#endif
  return 0;
}
```

---

## 作者：OIerAlbedo (赞：0)

# 题意
求出有多少最短路径树，若小于$ K $则输出方案总数，大于$ K $输出$ K $，再输出方案。

# 基本思路

我们先求出一棵最短路径树，我的做法是从$ 1 $开始求出到其他点所会经过的边，在进行标记，这个方法的正确性我也不会证，但就是过了。之后就是暴力替换，算出每一条树边可以替换成哪几条边，再替换即可。

# 正题
### 如何找可以换的边
我们先算出每一点的深度，记为$ f[i] $,然后对于树点,我们去找深度与其的父亲相同且不是树点的点，那么连接这两个点的边就是一条备用边，因为如果深度是一样的，那么以这个点为根的子树内的所有点的深度是不会变的，而这棵树的父亲及祖先节点显然可证不会变。
### 如何替换
看到许多题解用DFS，我自愧不如，我是运用类似进制加法的方法，先把最后一条树边替换，如果回到了最开始那条树边，则在前面一条树边做如此操作。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct hxz{
	int x,y;
};
hxz h[2000000];
long long f[2000000],e1[2000000],e2[2000000],e3[2000000],father2[2000000],father1[2000000],a[2000000],b[2000000],c[2000000],d[2000000];
bool e[2000000];
bool u[2000000];
int K,now[2000000],rit[2000000],uu[2000000],a1[2000000],b1[2000000],d1[2000000];
priority_queue< pair<long long ,int> , vector< pair<long long ,int> > ,greater< pair<long long ,int> > > q;
long long cnt1,num[2000000],ans,j,t,w,x,y,z,cnt,sum,n,m,k,i;
bool cmp(hxz a,hxz b)
{
	return (a.x<b.x);
}
void sc(int x)
{
	if (e[father2[x]]) return;
	e[father2[x]]=true;
	sc(father1[x]);
}
void add(int x,int y,int z)
{
	cnt++;a[cnt]=y;b[cnt]=d[x];c[cnt]=z;d[x]=cnt;
}
void add1(int x,int y)
{
	cnt1++;a1[cnt1]=y;b1[cnt1]=d1[x];d1[x]=cnt1;
}
void sc(int x,int fa)
{
	f[x]=1;
	for (int i=d[x];i;i=b[i])
	    if (a[i]!=fa)
	        {
	        	sc(a[i],x);
	        	h[c[i]].x=f[a[i]];h[c[i]].y=c[i];
	        	f[x]+=f[a[i]];
			}
}
int main()
{
	cin>>n>>m>>K;
	for (i=1;i<=m;i++)
	     {
	     	cin>>x>>y;z=1;
	     	e1[i]=x;e2[i]=y;e3[i]=z;
	     	add(x,y,z);add(y,x,z);
		 }
	for (i=1;i<=n;i++) f[i]=100000000000000000;
	q.push(make_pair(0,1));f[1]=0;
	while (!(q.empty()))
	     {
	     	x=q.top().second;q.pop();
	     	if (u[x]) continue;u[x]=true;
	     	for (i=d[x];i;i=b[i])
	     	    if (f[a[i]]>f[x]+c[i])
	     	        {
	     	        	f[a[i]]=f[x]+c[i];
	     	        	father1[a[i]]=x;father2[a[i]]=(i-1)/2+1;
	     	        	q.push(make_pair(f[a[i]],a[i]));
					 }
		 }
	ans=1;
	for (i=2;i<=n;i++)
	     {
	     	j=i;
	     	while (j!=1)
	     	    {
	     	    	if (e[father2[j]]) break;
	     	    	e[father2[j]]=true;
	     	    	j=father1[j];
				 }
		 }
	
	w=1;
	for (i=1;i<=m;i++)
	    {
	    	num[i]=1;
	    if (e[i])
	        {
	        	uu[i]=1;
	        	if (f[e1[i]]<f[e2[i]])
	        	     {
	        	     	sum=1;rit[i]=i;
	        	     	for (j=d[e2[i]];j;j=b[j])
	        	     	      if ((f[a[j]]==f[e1[i]])&(e[(j-1)/2+1]==false))
	        	     	          {
	        	     	          	num[i]++;
	        	     	          	add1(e2[i],(j-1)/2+1);sum++;
								   }
						now[i]=d1[e2[i]];
						if (ans<=K) ans=ans*sum;
					 }
				else
				    {
				    	sum=1;rit[i]=i;
	        	     	for (j=d[e1[i]];j;j=b[j])
	        	     	      if ((f[a[j]]==f[e2[i]])&(e[(j-1)/2+1]==false))
	        	     	          {
	        	     	          	num[i]++;
	        	     	          	add1(e1[i],(j-1)/2+1);sum++;
								   }
					    now[i]=d1[e1[i]];
						if (ans<=K)
						   ans=ans*sum;
						
					}
			}
	    }
	if (K>ans) K=ans;
	printf("%d\n",K);
	for (;K;K--)
	     {
	     	for (i=1;i<=m;i++) printf("%d",uu[i]);
	     	printf("\n");
	     	bool flag;
	     	i=m;flag=false;
	     	while (1)
	     	    {
	     	    	if (flag) break;
	     	    	if (e[i]==false) 
	     	    	    {
	     	    	    	i--;continue;
						 }
	     	    	if (i<=0) break;
	     	    	if (f[e1[i]]<f[e2[i]])
	     	    	    {
	     	    	    	x=a1[now[i]];
	     	    	    	if (x==0)
	     	    	    	    {
	     	    	    	    	uu[rit[i]]=0;uu[i]=1;
	     	    	    	    	rit[i]=i;now[i]=d1[e2[i]];i--;
								 }
							else
							    {
							    	uu[rit[i]]=0;uu[x]=1;
							    	rit[i]=x;
							    	now[i]=b1[now[i]];flag=true;break;
								}
						 }
					else
					   {
					   	x=a1[now[i]];
	     	    	    	if (x==0)
	     	    	    	    {
	     	    	    	    	uu[rit[i]]=0;uu[i]=1;
	     	    	    	    	rit[i]=i;now[i]=d1[e1[i]];i--;
								 }
							else
							    {
							    	uu[rit[i]]=0;uu[x]=1;
							    	rit[i]=x;
							    	now[i]=b1[now[i]];flag=true;break;
								}
					   }
				 }
		 }
	return 0;
}
```


---

