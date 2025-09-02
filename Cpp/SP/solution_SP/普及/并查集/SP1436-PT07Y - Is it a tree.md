# PT07Y - Is it a tree

## 题目描述

有一个N个点M条边的图。 请问，该图是否为树。

## 样例 #1

### 输入

```
3 2
1 2
2 3```

### 输出

```
YES```

# 题解

## 作者：Lips (赞：4)

# 抢到题解的二血！

不知道为什么楼下大佬用的暴力搜索，蒟蒻我只能用一个并查集来水一发了。

**题目大意：** 给定一个图，问这个图是否为一棵树。

---

先普及一下树的概念：在一个图中，若顶点数量为边数$+1$且这个图中没有环，那么这个图就可以构成一棵树。

既然知道了这个，我们便要来做两个判断：

- 图中的定点数是否满足边数$+1$

- 图中是否有环

对于第一个问题，一个$if$便可以轻松解决，但对于第二种问题来说，我们可以有三种方法来判环：

- 拓扑排序

- $dfs$

- 并查集

这里，就只讲并查集的做法~~一是因为我太弱了，二是因为楼下已经写了dfs~~

---

还是先普及一下并查集的知识吧！

并查集有三种操作：

- $\operatorname{find(int\space x)}$：寻找$x$的根节点

- $\operatorname{unite(int\space x,int\space y)}$：将两个点合并到一个集合

- $\operatorname{same(int\space x,int\space y)}$：判断两个点是否在同一集合

---

知道了这些，我们便可以进一步的知道该怎么解决判环

首先，对于一条边的两个点$(u,v)$，若他们不在同一集合，也就是说，还没有构成环，那么，就把他们合并$\operatorname{unite(u,v)}$，否则，就说明他们之前已经在同一集合，而现在再连一次边，就够成了环，这时，便要将$flag$标记为$1$

结束了输入之后，便只要做个判断，如果$flag==0$且$n==m+1$，那么就说明是一棵树，输出$YES$，否则，输出$NO$

---

$Code:$

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=10010;
int n,m,par[MAXN],rankk[MAXN];
bool flag;
void init(int n)//初始化 
{
	for(register int i=1;i<=n;i++)
	{
		par[i]=i;//父亲设为自己 
		rankk[i]=0;//第i个点的高度为0 
	}
} 
int find(int x)//查找根节点 
{
	if(par[x]==x) return par[x];
	else return par[x]=find(par[x]);//路径压缩 
}
void unite(int x,int y)//合并函数 
{
	x=find(x);
	y=find(y);
	if(x==y) return;
	if(rankk[x]<rankk[y])
	{
		par[x]=y;
	}
	else
	{
		par[y]=x;
		if(rankk[x]==rankk[y]) rankk[x]++;
	}
}
bool same(int x,int y)//判断两个元素是否在同一集合 
{
	return find(x)==find(y);
}
int main()
{
	scanf("%d%d",&n,&m);
	init(n);//一定别忘初始化！ 
	for(register int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		if(!same(u,v)) unite(u,v);//如果他们不是同一祖先，就合并 
		else flag=1;//否则标记为1 
	}
	if(flag==0&&m+1==n) printf("YES\n");//判读 
	else printf("NO\n");
	return 0;//养成良好习惯 
}
```
~~这是一道橙题的难度吧~~话说看窝写的这么认真，点个赞再走吧qwq

---

## 作者：qip101 (赞：1)

### 题意：

[PT07Y - Is it a tree ](https://www.luogu.com.cn/problem/SP1436)

### Solution：

如何判断一个图是树？那么我们就想到树的定义是：一个无环图并且边数比点数少一。

后面一个条件很好判断，那么关键就是这么判断有没有环呢？

我们知道，判断环的方法一般有三种：并查集，深度优先搜索，拓扑排序。

这一题的话写并查集可能简单一点？

具体就是每次读入的两个点，如果他们已经属于一个集合，现在又连边，那么一定会产生一个环。

### Code：

```cpp
#include <bits/stdc++.h>
#define MAXN 100100
#define INF 2147483647
using namespace std;
int n,m;
int fa[MAXN];
int find(int x)
{
	if(fa[x]==x)
		return fa[x];
	return fa[x]=find(fa[x]);
}
void Union(int u,int v)
{
	if(find(u)!=find(v))
		fa[u]=v;
}
int main()
{
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
	cin >> n >> m;
	for(int i=1;i<=n;i++)
		fa[i]=i;
	for(int i=1;i<=m;i++) 
	{
		int u,v;
		cin >> u >> v;
		if(find(u)!=find(v))
			Union(u,v);
		else
		{
			cout << "NO" << endl;
			return 0;
		}
	}
	if(m==n-1)
		cout << "YES" << endl;
	return 0;
}

```


---

## 作者：DeepSkyBlue__ (赞：0)

补充一种 BFS 的做法。

这道题让我们判断一个无向图是不是树。

[OI wiki](https://oi-wiki.org/graph/tree-basic/) 上关于树的定义是：

有 $n$ 个结点，$n-1$  条边的连通无向图。

第一个关于边的条件可以在输入时直接判断。

第二个关于联通的条件可以用 BFS ，从 $1$ 开始 BFS ，如果有点没有遍历到就不是联通图了。

CODE：

```cpp
#include<bits/stdc++.h>
//#include<tr1/unordered_map> 
using namespace std;
//using namespace std::tr1;
unordered_map<int,vector<int> > adj;
queue<int>q;
bool v[200001];
void bfs(int s)//bfs
{
    q.push(s);
    v[s]=true;//源点入队
    while(!q.empty())//队列不为空
    {
        int cur=q.front();//队首元素进行扩展
        q.pop();
        for(int i=0;i<adj[cur].size();i++)
        {
            int next=adj[cur][i];
            if(!v[next])//没走过
            {
                v[next]=true;//那就走
                q.push(next);
            }
        }
    }
}
int main()
{
	int n,m;
	cin>>n>>m;
	memset(v,0,sizeof(v));
	for(int i=1;i<=m;i++) 
    {
        int x,y;
        cin>>x>>y;
        adj[x].push_back(y);//无向图两次建边
        adj[y].push_back(x);
    }
    if(n!=m+1) //边的条件不符合
	{
		cout<<"NO"<<endl;
		return 0;
	}
    bfs(1);//从1开始bfs
	for(int i=1;i<=n;i++)
		if(v[i]==0)//有点没有遍历过，不是连通图
		{
			cout<<"NO"<<endl;
			return 0;
		}
	cout<<"YES"<<endl;//边和连通图的条件都满足，是树
	return 0;
}
```


---

## 作者：SymphonyOfEuler (赞：0)

这道题是一道判断是否为树的题。我选择用并查集做。

## 思路：

并查集的几个函数先说一下:

```
int find (int a){//这个函数用来确定某个点的根
    if(father[a]==a){
        return a;
    }
    return father[a] = find(father[a]);
}
```

```
void merge(int x, int y){//这个函数用来把两个树或图拼接再一起
    father[find(x)]=find(y);
}
```

最重要的是要在main中初始化father数组

```
for (int i = 1; i <= n; ++i) {
        father[i]=i;
}
```

#### 到底什么是树？！！

树，有叶子，也有果实————得得得得得得得得得得得得得得，说的是信息学里的树！

树的最重要的性质就是它没有任何环，所以我们可以利用这一点判断这个图是否为树。

定一个布尔，初始化为false，如果有环，变为true，最后判断一下，输出。

## 代码：

```
#include <bits/stdc++.h>
using namespace std;
int father[100005];
int find (int a){
    if(father[a]==a){
        return a;
    }
    return father[a] = find(father[a]);
}
void merge(int x, int y){
    father[find(x)]=find(y);
}

int main() {
    int n,m;
    bool huan=false;
    cin>>n>>m;
    for (int i = 1; i <= n; ++i) {
        father[i]=i;
    }
    for (int i = 1; i <= m; ++i) {
        int a,b;
        cin>>a>>b;
        if(find(a)!=find(b)) merge(a,b);
        else huan=true;
    }
    if(huan==0&&m+1==n) cout<<"YES";
    else cout<<"NO";
    return 0;
}
```

$仅30行代码，我带你走天下！$

$End$



---

## 作者：songhongyi (赞：0)

题意：~~根据题目名称可知~~，我们需要判断一个**无向无权**图是否为树。  
对于不知道什么是树的，看[这个OIwiki的文档](https://oi-wiki.org/graph/tree-basic/)。  
如果一个$N$点$M$边的图是树，一定要满足的是
- $M=N-1$；
- 该图无环；
- 该图联通。 

显然，第二个和第三个条件是在满足第一个条件时相同的，原因请各位自行思考。  
对于第一个条件，我们只需要特判一下就OK了，至于第二个,我们只需要对这个图DFS一遍，如果所有点都能走到，就是联通的。  
我们用任意一个点开始DFS均可。  
我们只需要在DFS时维护一个vis数组，来记录一个点之前是否有走到过，它有这些作用。
- 判断是否能够走到所有点；
- 防止有环而死循环，如这个样例：
	```plain
	4 3
	1 2
	2 3
	3 1
	```
    
那么，DFS的伪代码如下
```text
dfs (x)
  将vis[x]设为true
  遍历所有出边的点i
      如果vis[i]为false
      	dfs(i)
```
至于存边，我使用的是`vector`，使用方法不再赘述。
那么整体的代码如下，部分细节在注释里:
```cpp
#include <iostream>
#include <vector>
using namespace std;
vector< int > edges[ 10010 ]; //建立vector容器存边
void addege( int u, int v )  //增加一条边，由于是无向图，需要建双向的边
{
    edges[ u ].push_back( v );
    edges[ v ].push_back( u );
}
bool vis[ 10010 ];  //vis数组
void dfs( int x )
{
	vis[ x ] = true;
    for ( auto i : edges[ x ] )  //C++11黑科技
    {
        if ( !vis[ i ] )  //判断是否走过，不如会无线递归
            dfs( i );
    }
}//dfs代码，如上伪代码
int main()
{
    int n, m;
    cin >> n >> m;
    if ( m != n - 1 )  //特判m!=n-1的
        cout << "NO" << endl;
        return 0;
    }
    for ( int i = 0; i < m; i++ )
    {
        int u, v;
        cin >> u >> v;
        addege( u, v );  //加边
    }
    dfs( 1 );  //从一号节点dfs
    bool flag = 1;
    for ( int i = 1; i <= n; i++ )
        flag &= vis[ i ];  //判断是否是所有点都到了
    if ( flag )
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
}
```

总之这道题对图论新手还是很好地。

---

## 作者：若如初见 (赞：0)

~~蒟蒻来写一发水题的题解~~  

### 一句话题意  

给定一个无向图，判断该图是否为树。

### 思路分析

从树的性质入手：  

1. 树是一种无向联通图；  

2. 一棵树有$n$个结点和$n-1$条边。  

思路已经呼之欲出了。首先，检验该无向图的边数和结点数是否满足上面提到的性质2。如果不满足，可以直接输出“NO”并结束程序；如果满足，则以任意结点为起点对该图进行深度优先遍历，并标记路径上的每一个点。最后检查是否所有结点都被标记过——如果存在没有遍历到的结点，输出“NO”；否则输出“YES”。  

此题很简单，上面也解释得很清楚了，代码中就不加什么注释了。  

```cpp
#include <cstdio>
#define MAXN 20005
using namespace std;
int n,m,cnt,head[MAXN];
bool vis[MAXN];
struct Edge{
	int next,to;
}edge[MAXN<<1]; //无向图，数组要开两倍大
inline void add(int u,int v){
	edge[++cnt].next=head[u];
	edge[cnt].to=v;
	head[u]=cnt;
	return;
}
void dfs(int p){
	for(int i=head[p];i;i=edge[i].next){
		int v=edge[i].to;
		if(!vis[v]){
			vis[v]=1;
			dfs(v);
		}
	}
	return;
}
int main(){
	scanf("%d %d",&n,&m);
	if(m!=n-1){
		printf("NO\n");
		return 0;
	}
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		add(u,v);
		add(v,u);
	}
	dfs(1);
	for(int i=1;i<=n;i++)
		if(!vis[i]){
			printf("NO\n");
			return 0;
		}
	printf("YES\n");
	return 0;
}
```


---

