# Hongcow Builds A Nation

## 题目描述

## CF744A Hongcow Builds A Nation

给出一张 $n$ 个点， $m$ 条边的无向图，其中有$k$个点是警察局

一个稳定的图要满足以下条件：  

- 无重边
- 无自环
- 每个连通块内最多只有一个警察局

你的任务是求最多**还能**加多少条边，使得加完边后的图还能是稳定的

## 说明/提示

$1 \le k \le n \le 1000$  
$0 \le m\le 10^5$

**数据保证初始时给出的图是稳定的**  
感谢 @_Wolverine 提供的翻译

## 样例 #1

### 输入

```
4 1 2
1 3
1 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 3 1
2
1 2
1 3
2 3
```

### 输出

```
0
```

# 题解

## 作者：Atserckcn (赞：5)

## Hongcow Builds A Nation 题解

[更好的阅读体验？](https://www.cnblogs.com/Atserckcn/p/18613525)

[洛谷](https://www.luogu.com.cn/problem/CF744A)。

[Codeforces](https://codeforces.com/problemset/problem/744/A)。

### 题目描述

给定一张 $n$ 个点，$m$ 条边的无向图，有 $k$ 个点是特殊点。

每个连通块中都得保证无重边、无自环，且最多只有一个特殊点。

求最多还能加多少条边，满足以上条件。

### 思路简述

首先考虑以下有 $n$ 个点的完全图共有多少条边：

第一个点可以和剩下的 $n-1$ 个点匹配，第二个点可以和 $n-2$ 个点匹配……
$$
(n-1)+(n-2)+\cdots +2+1
\\ 
=\frac{n \cdot(n-1)}{2}
\\ 
=\frac{n^2-n}{2}
$$
因为题目中提到了**连通块**这一关键词，立马联想到用并查集来实现。

假设连通块 $x$ 与连通块 $y$ 可以合并，那么显然需要满足以下条件：

+ 连通块 $x$ 与连通块 $y$ 合起来最多只有一个特殊点。

当我们将所有内部有特殊点的连通块都合并完后，考虑无特殊点的连通块。

可以开个变量 num 统计所有无特殊点的连通块的成员数量和。

很显然，将所有无特殊点的连通块全部与连通块内节点数量**最多**的连通块合并起来最优。

那么我们就可以开个变量表示连通块内节点数量的最大值。最后全部内部无特殊点的连通块合并入最大值即可。

答案怎么统计呢？

考虑枚举所有连通块。

如果当前连通块内部没有特殊点，直接加入 num。继续访问下一个。

若当前连通块不是**目前最大**连通块，则用公式（上文提及）加入答案。

如果当前连通块大于目前最大连通块：

设当前连通块成员数量为 $x$，最大连通块成员数量为 $maxn$。

用目前最大连通块合并入当前连通块，答案加上 $\frac{maxn^2-maxn}{2}$。

更新。$maxn$ 赋值为 $x$。

注意顺序不能反。

### Code

```cpp
//wrote by Atserckcn
#include<bits/stdc++.h>
using namespace std;
#define ljl long long
const ljl N=1005,M=1e5+5;
ljl n,m,k,cnt_e,u,v,head[N],pl[N],fa[N],cnt_node[N],maxn,ans,num;
bool pol[N],vis[N];
//突然发现建边貌似并没有用，可以忽略建边的一系列操作。
struct E{
	ljl to,pre;
}e[M<<1];
void add(ljl from,ljl to)
{
	e[++cnt_e].to=to;
	e[cnt_e].pre=head[from];
	head[from]=cnt_e;
	return;
}
//并查集模板--------------------
ljl findfa(ljl x)
{
	return fa[x]==x?x:fa[x]=findfa(fa[x]);
}
void Union(ljl x,ljl y)
{
	fa[findfa(x)]=findfa(y);
	return;
}
//并查集模板--------------------
ljl getnum(ljl x)//公式
{
	return x*(x-1)/2;
}
int main(){
    //浅浅关个同步流
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>k;
	for(ljl i=1;i<=n;++i)
		fa[i]=i;//并查集的初始化
	for(ljl i=1;i<=k;++i)
	{
		cin>>pl[i];
		pol[pl[i]]=true;//标记此乃特殊点
	}
	for(ljl i=1;i<=m;++i)
	{
		cin>>u>>v;
		add(u,v);add(v,u);
		Union(u,v);//并查集的合并
	}
	for(ljl i=1;i<=n;++i)
	{
		++cnt_node[findfa(i)];//统计每个连通块内成员个数
		pol[findfa(i)] |= pol[i];//若当前节点是特殊点，那么这个连通块肯定也是
	}
	for(ljl i=1;i<=n;++i)
	{
		ljl fx=findfa(i);
		if(vis[fx]) continue;
		vis[fx]=1;
        //开始实施答案统计
		if(pol[fx])
		{
			if(cnt_node[fx]<=maxn)
				ans+=getnum(cnt_node[fx]);
			else
			{
				ans+=getnum(maxn);
				maxn=cnt_node[fx];
			}
		}
		else
			num+=cnt_node[fx];
	}
	ans+=getnum(maxn+num);
	cout<<ans-m<<'\n';
	return 0;
}
```

[AC 记录](https://codeforces.com/problemset/submission/744/296982062)。

---

## 作者：友利奈緒 (赞：3)

**一道很不错的并查集训练题**

题目大意：给n个点，m条边，k个特殊点（警察局），使得在保持每个连通块内都至多存在一个特殊点的情况下还能往图上添加多少条边

思路分析：因为要将所有点划分为好几个集合，不难想到用并查集维护每个集合，但我们如何将集合中的边数最大化呢？

当一个集合点数n为1，则最大边数为0，n=2时最大边数为1,n=3时为3....

对于n个点来说，第一个点可以和剩下的所有点，即n-1个相连，第二个点可以和n-2个，以此类推。总的边个数就是(n-1)+(n-2)+......+2+1,化简可得 $\frac{n^2-n}{2}$。因此我们可以在存边时顺便用两个数组维护一下当前集合的边数和点数，在之后再用$\frac{n^2-n}{2}$减去边数，即可求出对于这个集合来说能加多少条边。

代码如下
```cpp
for(int i=1;i<=n;i++)
	{
		if(vis[fa(i)]) continue;
		vis[fa(i)]=true;
		int t=tot[fa(i)];
		ans+=(t*t-t)/2-edge[fa(i)];//先把连通块内的边都加上 
		if(t>maxn&&police[fa(i)]) maxn=t,maxd=fa(i);
	}
```
其中police数组是为了维护每个集合是否已经有警察局存在（因为最多只能存在一个）。fa即为找祖先的函数。
tot数组存集合点数，edge是边数。vis数组记录当前连通块是否已经计算过。至于最后一行，下面会再说到。

我们将每个集合的边都最大化以后，考虑如何将集合合并。

其中有警察局的连通块不能和另外一个有警察局的合并，因此只需要将没有警察局的合并到有警察局的连通块里即可。

而要想使合并集合边数最大，不难想到与点数最多的含警察局连通块合并即可。


因此在求每一块的最大边数时，维护含警察局的一个点数最大值和对应的连通块编号，并在之后将所有能合并的连通块与其合并。维护最大值操作如下
```cpp
if(t>maxn&&police[fa(i)]) maxn=t,maxd=fa(i);
```
而对于每一次合并操作，每一个点都能和另外一个连通块的所有点相连，因此若两个点数分别为m和n，能加的边数就是m*n

合并操作如下
```cpp
for(int i=1;i<=n;i++)//将其余没有警察局的连通块都加到最大的连通块上 
	{
		if(police[fa(i)]||vis[fa(i)]) continue;
		vis[fa(i)]=1;
		ans+=tot[fa(i)]*maxn;
		maxn+=tot[fa(i)];//合并时不再需要add操作，直接维护点数和即可
	}
```

完整代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
inline int read()
{
	char ch=getchar();
	int x=0,f=1;
	while(ch>'9'||ch<'0')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
bool police[1101];//是否已存在一个警察局 
bool vis[1101];//该连通块是否处理过
int tot[1101],edge[1101];//节点总数 以及该连通图内的边数
int ans=0;//还能加的边数		
int bin[1101];
int fa(int x)
{
	while(x!=bin[x]) x=bin[x]=bin[bin[x]];
	return x;
} 
void add(int x,int y)
{
	int fx=fa(x),fy=fa(y);
	bin[fx]=fy;
}
int main()
{
	n=read();m=read();k=read();
	for(int i=1;i<=n;i++)
	bin[i]=i,tot[i]=1;
	for(int i=1;i<=k;i++)
	{
		int p=read();
		police[p]=true;
	}
	for(int i=1;i<=m;i++)
	{
		int x=read(),y=read();
		int fx=fa(x),fy=fa(y);
		int f=0;
		if(police[fa(x)]||police[fa(y)]) f=1;//若两个联通块内存在警察局，则合并到之后的连通块祖先上
		if(fx!=fy)
		{
			add(x,y);
			tot[fa(y)]+=tot[fx];
		}
		if(fx!=fy) edge[fa(x)]+=edge[fx]+1;//注意！若两点原来就在同一块中，边数都加起来会导致多加，因此要进行判断
		else edge[fa(x)]++;
		if(f==1) police[fa(x)]=true;//记录该连通块存在警察局
	}
	int maxn=-1,maxd;//分别储存最大节点数和该连通块的祖先节点
	for(int i=1;i<=n;i++)
	{
		if(vis[fa(i)]) continue;
		vis[fa(i)]=true;
		int t=tot[fa(i)];
		ans+=(t*t-t)/2-edge[fa(i)];//先把连通块内的边都加上 
		if(t>maxn&&police[fa(i)]) maxn=t,maxd=fa(i);
	}
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++)//将其余没有警察局的连通块都加到最大的连通块上 
	{
		if(police[fa(i)]||vis[fa(i)]) continue;
		vis[fa(i)]=1;
		ans+=tot[fa(i)]*maxn;
		maxn+=tot[fa(i)];
	}
	printf("%d",ans);
	return 0;
}
```
完结撒花~

---

## 作者：啊吧怪 (赞：2)


练习并查集的基础题，自评黄题。

### 题意

给出 $n$ 个点，$m$ 条边，$k$ 个特殊点的无向图，在保持每个连通块内最多一个特殊点时能增加几条边。

### 解析

既然是与连通块有关，不妨使用并查集储存连通块。

考虑将边数最大化方案性质，若一连通块合法，设该连通块中点个数为 $x$ 
那么该连通块内边数最大为 $\dfrac{n \times (n-1)}{2}$ 由此式可知若两连通块可合并，则合并后总边数一定会增加。

所以应将所有可合并的集合合并成一个连通块，并使该连通块的点数最大，所以将所有无特殊点的连通块与点数最多有特殊点的连通块合并。

在以上操作完成后，对于每个连通块计算其边数和，然后减去初始边数即为答案，具体可结合代码理解。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read()
{
	int x=0;
	char a=getchar();
	while(a<'0'||a>'9')  a=getchar();
	while(a>='0'&&a<='9') x=(x<<1)+(x<<3)+(a^48),a=getchar();
	return x;
}
//以上为快读
int n,m,k,fa[1010],sum[1010],police[1010],ans,maxx,summ;
//sum为连通块点数，police为连通块内是否有特殊点，maxx为点数最多的有特殊点的连通块，summ为无特殊点的连通块点数总和。
int find(int x)
{
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}//正常并查集操作
bool vis[1010];//特别的，记录每个连通块是否已经被操作过一次了。
int main()
{
    n=read(),m=read(),k=read();
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1,x;i<=k;i++)
    {
    	x=read();
    	police[x]=1;
    }
    for(int i=1,u,v;i<=m;i++)
    {
    	u=read(),v=read();
    	fa[find(u)]=find(v);
    }
    for(int i=1;i<=n;i++)
    {
    	sum[find(i)]++;
    	police[find(i)]|=police[i];
       //统计连通块内是否有特殊点以及点数，这些数据统计在并查集中的祖宗处。
    }
    for(int i=1,f;i<=n;i++)
	{
		f=find(i);
		if(vis[f]) continue;
		vis[f]=1;
		if(police[f]==1)
		{
//若该连通块内有特殊点，进行大小对比，若小则直接计算其总边数并计入ans，若大则计算关于maxx连通块的总边数并计入ans。
			if(sum[f]>maxx) 
			{
				ans+=maxx*(maxx-1)/2;
				maxx=sum[f];
			}
			else ans+=sum[f]*(sum[f]-1)/2;
		}
		else summ+=sum[f];//若连通块内不含特殊点将其计入summ即可。
        
	}
	maxx+=summ;合并所有无特殊点的连通块和点数最大的有特殊点的连通块。
	ans+=maxx*(maxx-1)/2;//将其算入答案中。
	cout<<ans-m;
    return 0;
}
```

---

## 作者：KaDa_Duck (赞：2)

[传送门](https://www.luogu.com.cn/problem/CF744A)

**题目大意**：
	
    n个点，m条边，k个关键点。在已有的基础上还能加几条边而且使新图满足条件。
    注意给的图一定是满足条件的！
**思路**：

	既然是一些连通块，我们不妨用并查集来维护他们。
   （对于边的一些知识，我们需要知道在一个连通块K里，有K[i]个点，能连x*(x-1)/2条边。两个连通块X,Y之间能连X[i]*Y[i]条边。）
   
   我们在用并查集可以在O(n)的时间里吧每个连通块的点数求出来，先不考虑已经连的边，即把每个连通块想成只是在个小笼子里，没有边连接。把所有的连通块都处理出来~~单个点算不算其实都一样，但是对后面有用，建议当成连通块处理~~，与此同时我们把有关键点的连通块打一个擂台找到最大的连通块。我们在这个过程中用一个数组存放没关键点的连通块。
   
   下一步，我们暴力处理每个连通块的关系，再减去m即可。~~之前处理时没考虑这些边~~。
   然后我们就愉快的A掉它了。
   
   **代码**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,maxn=-100;
int fa[2020],c[2020],len,num[2020],sum[2020],book[2020],Bit[2020];
long long ans=0;
inline int read()
{
	int Num=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1; ch=getchar();}
	while(ch>='0'&&ch<='9') {Num=(Num<<3)+(Num<<1)+ch-'0'; ch=getchar();}
	return Num*f;
}
inline int getfa(int x) {return x==fa[x]?x:fa[x]=getfa(fa[x]);}
inline void add(int x,int y) {if(getfa(x)!=getfa(y)) sum[y]+=sum[x],sum[x]=0;fa[getfa(x)]=getfa(y);}
int main()
{
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;i++) fa[i]=i,sum[i]=1;
	for(int i=1;i<=k;i++) c[i]=read();
	for(int i=1;i<=m;i++) {int x=read(),y=read();add(x,y);}
	for(int i=1;i<=k;i++) book[getfa(c[i])]=1;//注意题上说了输入的会保持稳定 
	for(int i=1;i<=n;i++) if(getfa(i)!=i) sum[getfa(i)]+=sum[i],sum[i]=0;
	for(int i=1;i<=n;i++) 
	{
		if(fa[i]==i) 
		{
			if(book[i]) maxn=max(maxn,sum[i]);
			else Bit[++len]=i;
			ans+=sum[i]*(sum[i]-1)/2;
		}
	}
	for(int i=1;i<=len;i++) 
	{
		ans+=sum[Bit[i]]*maxn;
		for(int j=i+1;j<=len;j++) ans+=sum[Bit[i]]*sum[Bit[j]];
	}	
	printf("%lld",ans-m);
	return 0;
}
```

完美撒花~

    

---

## 作者：Priori_Incantatem (赞：2)

### 题目大意

给出一张 $n$ 个点， $m$ 条边的无向图，其中有$k$个顶点是警察局  
求最多能多加多少条边，使得加完边后的图 无重边，无自环，且一个连通块里最多只有一个警察局

对于每一个连通块，我们先要让它的边数最大化：设节点数为 $x$，已有的边数为 $y$ ，则还能多加的边数就是 $\frac{x(x-1)}{2}-y$，这样就把每一个连通块边数加到极致

利用贪心的思想，将所有连通块按大小降序排列，每次合并最大的两个连通块，前提是合并后连通块内不会超过一个警察局

$Tips:$ 合并两个大小分别为 $x,y$ 的连通块，可以多加的边数为 $x\times y$

```cpp
#include<cstdio>
#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
const int Maxn=1010,inf=0x3f3f3f3f;
vector <int> e[Maxn],bin;
int f[Maxn],c[Maxn],sum[Maxn];
bool vis[Maxn];
int n,m,k,ans;
inline bool cmp(int x,int y)
{
	return c[x]>c[y];
}
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
void bfs(int s,int fa)
{
	queue <int> q;
	f[s]=fa,q.push(s);
	while(q.size())
	{
		int x=q.front();
		q.pop();
		vis[fa] |= vis[x];
		++c[fa];
		for(int i=0;i<e[x].size();++i)
		{
			int y=e[x][i];
			++sum[fa];
			if(f[y])continue;
			f[y]=fa,q.push(y);
		}
	}
	sum[fa]>>=1;
}
int main()
{
	//freopen("in.txt","r",stdin);
	n=read(),m=read(),k=read();
	for(int i=1;i<=k;++i)
	{
		int x=read();
		vis[x]=1;
	}
	
	for(int i=1;i<=m;++i)
	{
		int x=read(),y=read();
		e[x].push_back(y);
		e[y].push_back(x);
	}
	
	for(int i=1;i<=n;++i)
	{
		if(f[i]>0)continue;
		bfs(i,i);
//		printf("heehehe %d %d %d\n",f[i],c[i],sum[i]);
		ans+=(c[i]*(c[i]-1)>>1)-sum[i];
		if(f[i]==i)bin.push_back(i);
	}
	
	sort(bin.begin(),bin.end(),cmp);
	for(int i=0;i<bin.size();++i)
	{
		for(int j=i+1;j<bin.size();++j)
		{
			int x=bin[i],y=bin[j];
			
			if(vis[f[x]] && vis[f[y]])continue;
//			printf("%d %d\n",f[x],f[y]);
//			printf("%d %d\n",c[f[x]],c[f[y]]);
//			printf("%d\n",c[f[x]]*c[f[y]]);
//			puts("");
			ans+=c[f[x]]*c[f[y]];
			c[f[x]]+=c[f[y]];
			vis[f[x]] |= vis[f[y]];
			f[f[y]]=f[x];
		}
	}
	
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：jasonshen_ (赞：0)

## 题目翻译
给出一张 $n$ 个点， $m$ 条边的无向图，其中有$k$个点是警察局。

一个稳定的图要满足以下条件：  

- 无重边。
- 无自环。
- 每个连通块内最多只有一个警察局。

你的任务是求最多**还能**加多少条边，使得加完边后的图还能是稳定的。
## 思路/算法
主要是并查集、图论。

下面是关于并查集的介绍，这里只做基本介绍，本题只涉及较基础的并查集，可以看代码。


>并查集是一种用于管理元素所属集合的数据结构，实现为一个森林，其中每棵树表示一个集合，树中的节点表示对应集合中的元素。
顾名思义，并查集支持两种操作：

· 合并：合并两个元素所属集合。（合并对应的树）

· 查询：查询某个元素所属集合（查询对应的树的根节点），这可以用于判断两个元素是否属于同一集合。

更多用法可以看这里：[OI-WIKI](https://oi.wiki/ds/dsu/)。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int ans, p;
int K[100000];
int A[100000];
vector<int> v[10000];
void dfs(int n)
{
    p++;
    if (A[n] == 1)
        return;

    A[n] = 1;
    for (int i = 0; i < v[n].size(); i++)
    {
        if (A[v[n][i]] == 0)
        {
            dfs(v[n][i]);
        }
    }
}
int main()
{
    int n, i, r, m, k, a, b, c = 0, mp = 0;
    cin >> n >> m >> k;

    for (i = 0; i < k; i++)
    {
        cin >> K[i];
    }
    for (i = 0; i < m; i++)
    {
        cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }

    for (i = 0; i < k; i++)
    {
        p = 0;
        dfs(K[i]);

        ans += (p * (p - 1)) / 2;
        mp = max(mp, p);
    }

    for (i = 1; i <= n; i++)
    {
        if (A[i] == 0)
        {
            c++;
        }
    }

    ans += ((mp + c) * (mp + c - 1)) / 2 - (mp * (mp - 1)) / 2;

    cout << ans - m;
}

```

---

