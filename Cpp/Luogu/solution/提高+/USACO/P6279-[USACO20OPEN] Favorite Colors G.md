# [USACO20OPEN] Favorite Colors G

## 题目描述

Farmer John 的 $N$ 头奶牛每头都有一种最喜欢的颜色。奶牛们的编号为 $1\ldots N$，每种颜色也可以用 $1\ldots N$ 中的一个整数表示。  
存在 $M$ 对奶牛 $(a,b)$，奶牛 $b$ 仰慕奶牛 $a$。有可能 $a=b$，此时一头奶牛仰慕她自己。对于任意颜色 $c$，如果奶牛 $x$ 和 $y$ 都仰慕一头喜欢颜色 $c$ 的奶牛，那么 $x$ 和 $y$ 喜欢的颜色相同。

给定这些信息，求一种奶牛喜欢颜色的分配方案，使得每头奶牛最喜欢的颜色中不同颜色的数量最大。由于存在多种符合这一性质的分配方案，输出字典序最小的（这意味着你应当依次最小化分配给奶牛 $1 \ldots N$ 的颜色）。

## 说明/提示

#### 样例解释：

在下图中，用粗边框圆表示的是最喜欢颜色 $1$ 的奶牛。

![](https://cdn.luogu.com.cn/upload/image_hosting/iratxzf8.png)

-----

对于 $100\%$ 的数据，$1\le N,M\le 2\times 10^5$。

共 $10$ 个测试点，其中 $1$ 为样例，其余性质如下：
 
测试点 $2\sim 3$ 满足 $N,M\le 10^3$。  
测试点 $4\sim 10$ 没有额外限制。

-----

出题人：William Lin，Benjamin Qi

## 样例 #1

### 输入

```
9 12
1 2
4 2
5 8
4 6
6 9
2 9
8 7
8 3
7 1
9 4
3 5
3 4```

### 输出

```
1
2
3
1
1
2
3
2
3```

# 题解

## 作者：lzqy_ (赞：30)

看到题解里有些地方没有详细讲到，这里来补一发。

## 题意简化

（这道题我读了好久才看懂…）

每个奶牛都有自己喜欢的颜色。其中，如果奶牛 $A$ 和奶牛 $B$ 都仰慕一头喜欢颜色 $c$ 的奶牛，那么它们喜欢的颜色需要相同。

在以上条件下，找到一种奶牛喜欢颜色的分配方案，可以让奶牛喜欢的颜色尽量不相同，输出字典序最小的答案。

## 算法分析

根据【样例分析】的启发，我们可以考虑连一幅图：

![](https://cdn.luogu.com.cn/upload/image_hosting/mdecyr62.png)

然后我们首先可以发现，同一个点所连接的所有点的颜色都必须相同。

比如 $3$ 号节点连接了 $5,4$ 号节点，那么按照要求，$4,5$ 号奶牛的颜色必须都是一样的。因此，我们可以考虑将它们合并。

这样做的目的是保证每一个节点中所含的奶牛都必须是同样的一个颜色，这样，当结束时，有多少个点集，就至少有多少个颜色集合。

于是我们合并 $4,5$ 号节点：

![](https://cdn.luogu.com.cn/upload/image_hosting/6xjjjp70.png)

以此类推，不断合并成：

![](https://cdn.luogu.com.cn/upload/image_hosting/1garaimf.png)

到这一步的时候，可以发现，每一个点最多向外连一个点，也就是说，每个点的出度 $<2$。因此，不再有新的点一定要变成同一种颜色了，所以结束合并过程，$1,4,5$ 一种颜色，$3,7,9$ 一种颜色，$2,6,8$ 一种颜色。

## 算法实现

那么，合并的过程怎么实现呢？

我们可以用类似并查集的方式来做。

对于每一个点，我们都可以将其想象成一棵有根树（只是思维上的，不是实现），并且深度 $≤2$（根节点深度为 $1$）。当要合并两个点的时候，我们只需要将一个节点的根节点和其子节点都加到另一棵树根节点下就可以了。

举个例子，比如我们要把左边的节点合并到右边的节点：

![](https://cdn.luogu.com.cn/upload/image_hosting/bkp3v67i.png)

那么新的节点就会变成：

![](https://cdn.luogu.com.cn/upload/image_hosting/e58bbo6r.png)

这便是合并方法了。

## 启发式合并

**然而**

掐指一算，发现时间复杂度极限可以达到 $O(n^2)$，应该是过不了的。

于是考虑一种玄学的操作——启发式合并！

其实就是当我们要合并两个节点的时候，考虑哪个节点所包含的奶牛数少，就合并过去哪个节点。

比如上文的例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/bkp3v67i.png)

我们就应该将右边的节点并到左边的节点里，这样便可以更快进行合并。

~~没有了，简单吧~~

这个时候可能有人就有疑惑了，这不只是一种卡常的手段吗？为什么就能通过这道题呢？

这个算法最令人惊叹的就是，它的时间复杂度是严格 $O(nlogn)$！

感兴趣的同学可以看以下的证明（不一定要掌握）：

考虑计算每一个奶牛最多会被合并几次（如果每一头奶牛合并次数都小于等于 $logn$，那么总时间复杂度就 是 $O(nlogn)$）。如果 $h$ 号奶牛要从大小为 $x$ 的节点并入大小为 $y$ 的节点，那么必有 $x≥y$，则合并后节点的大小 $x+y≥2y$。也就是说，一头奶牛所在的节点进过一次合并之后，奶牛所在节点的大小一定会至少乘 $2$，因此，一头奶牛最多被合并 $logn$ 次。

**证毕。**

~~很神奇吧~~

## 代码实现

以上只是算法分析，代码上还是有很多细节的。看注释吧：

```cpp

#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int maxn=200002;
inline int read()
{
    register int x=0;
    register char c=getchar();
    for(;!(c>='0'&&c<='9');c=getchar());
    for(;c>='0'&&c<='9';c=getchar())
        x=(x<<1)+(x<<3)+c-'0';
    return x;
}
int n,m;
vector<int>v[maxn];//存边
vector<int>son[maxn];
//son[i]:若i号奶牛是其所在节点的（那棵树的）根节点，
//那么存储所在节点的（那棵树的）所有节点
queue<int>q;
int fa[maxn];//fa[i]:i号奶牛所在节点的（那棵树的）根节点
int Vis[maxn],ans[maxn];
void hb(int x,int y)
{
	x=fa[x],y=fa[y];//对根节点进行操作
	if(son[x].size()<son[y].size())//启发式合并核心代码
		x^=y,y^=x,x^=y;
	for(register int i=0;i<v[y].size();i++)
		v[x].pb(v[y][i]);//合并
	for(register int i=0;i<son[y].size();i++)
		fa[son[y][i]]=x,son[x].pb(son[y][i]);//合并
	if(v[x].size()>1)
      //如果仰慕的奶牛超过一头，需要合并，入队列 
		q.push(x);
}

int main()
{
	register int x,y,t,ru;
    n=read(),m=read();
    for(register int i=1;i<=m;i++)
    	x=read(),y=read(),v[x].pb(y);
   	for(register int i=1;i<=n;i++)
	{
		fa[i]=i;//一开始每个奶牛所在节点的根节点都是它自己
		if(v[i].size()>1)
     //如果有超过一头奶牛仰慕当前奶牛，那么需要合并，加入队列
   		q.push(i);
   		son[i].pb(i);
      //一开始每个奶牛都是所在节点的根节点节点，且节点中必定有这头奶牛（废话）
	}   	
   	while(!q.empty())
   	{
   		t=q.front(),q.pop();
	   	while(v[t].size()>1)
	   	{
	   		ru=v[t][1],x=v[t][0],v[t].erase(v[t].begin());
	   		if(fa[ru]!=fa[x])
         //如果不是同一节点中的奶牛再合并，防止计算重复
				hb(ru,x);
		}
   	}
   	register int col=0;
   	for(register int i=1;i<=n;i++)
   	{
   		if(Vis[fa[i]]==0)
   			Vis[fa[i]]=++col;
   		cout<<Vis[fa[i]]<<endl;
   	}
    return 0;
}
```

---

## 作者：never_AK (赞：8)

## 前言

这份题解是目前的洛谷最优解：

它代码短，跑的快，空间小，并且前置知识只是**扩展域并查集**。

## 题意概括

一共 $n$ 头奶牛，每头奶牛喜欢一种颜色，存在 $m$ 个关系，$(A,B)$ 表示 $B$ 仰慕 $A$，如果两个奶牛仰慕**喜欢同一种颜色的奶牛**，两个仰慕者喜欢颜色相同。

最大化颜色的数量。

## 简单思路分析

这道题的困扰是怎么处理颜色相同的性质。

那么我们从简到繁，先考虑最朴素的颜色限制情况。

存在关系 $(A,B)$ $(A,C)$：那么此时 $color_B = color_C$。

也就是说，只要两个点仰慕同一个点，那么这两个点颜色相同。

那么，我们如果把两个颜色相同的点之间连一条边，那么最后颜色数量就是连通块数量。

但是问题是如果存在关系 $(A,B)$ 我们不能直接将 $A$ 和 $B$ 之间连边，因为 $A$ 和 $B$ 颜色不一定相同。

这个时候就可以使用**拓展域并查集**了(令 $X'$ 表示  $X$ 的拓展)。

我们将 $B$ 和 $A'$ 连边，这样就解决了 $A$ 和 $B$ 不一定同色的问题，同时这种方法也解决了自己仰慕自己的情况。

## 思路升级

但是，题目的限制不是同一个点，而是同色，怎么办？

其实也不难想。

**只要当我们把 $A$ 与 $B$ 连通的同时，顺便把 $A'$ 和 $B'$ 连通**。

这样不断做下去，就可以保证正确了。

## 复杂度证明

这样子看似暴力的连通方法，会不会超时呢？

显然不会，最开始最多 $2n$ 个点，也就意味着我们的连接操作最多进行 $2n - 1$ 次，时间上是 $O(n\timesα)$，基本可以说是 $O(n)$。

## 代码展示(简洁的45行)
~~~cpp
#include<bits/stdc++.h> 
using namespace std;
const int N = 2e5 + 10,inf = 1e9;
int n,m,tot;
int col[N],f[N << 1];
int p[N];
int find(int x){
	if(x == f[x])return x;
	return f[x] = find(f[x]);
}
void merge(int x,int y){
	int boss_x = find(x);
	int boss_y = find(y);
	if(boss_x == boss_y)return ;
	if(boss_x <= n)swap(boss_x,boss_y);//交换，保证用较小的取更新
	f[boss_x] = boss_y;
	if(boss_x <= n && boss_y <= n){//这里一定要先合并再递归，不然递归的时候会破坏当前merge
		merge(boss_x + n,boss_y + n);
	}
	return ;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n >> m;
	for(int i = 1;i <= 2 * n;i++){
		f[i] = i;
	}
	while(m--){
		int x,y;
		cin >> x >> y;
		merge(x + n,y);
	}
	for(int i = 1;i <= n;i++){ //序号小的先，保证字典序
		int id = find(i);
		if(p[id] == 0){
			p[id] = ++tot;
		}
		col[i] = p[id];
	}
	for(int i = 1;i <= n;i++){
		cout<<col[i]<<'\n';
	}
	return 0;
}
~~~

---

## 作者：c2020HXW (赞：8)

看到其他题解都使用了vector存边和启发式合并

我来提供一种相较而言更简单的实现方法

简单描述一下算法：
1. 从1~n遍历所有点，将这些点的后继节点合并;
2. 从1~n遍历所有点，将它和和它最终属于同一个点的染上同一个颜色cur，然后++cur;

我们使用并查集维护节点合并，因为合并后每个点只会有一个后继节点（我们每步会把所有的后继节点合成一个点），想到在每个节点并查集的祖先处维护这个后继的编号，开一个数组存即可。

合并两个节点其实就是对应合并由它和它的后继构成的两条链

封装一个函数，大概像这样：
```cpp
void Merge(int x,int y){
		x=getroot(x),y=getroot(y),fa[x]=y;	  //并查集
		if(!son[y]||!son[x])son[y]=son[x]|son[y];
			//若原来没有后继需要继承
		else if(son[x]^son[y])Merge(son[x],son[y]);
			//继续合并两个后继
	}
}
```

因为每个节点最多被合并一次，并查集同时加上按秩合并和路径压缩优化后，总复杂度会是$O(n*\alpha(n))$也就是$O(n)$的。

贴一下完整代码，目前是你谷最优解
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
#define int unsigned int
const int Mxdt=3<<20,Maxx=1<<18;
char *pi,bif[Mxdt],*po,bof[Mxdt];
#define Rd()\
	res=0;while(*pi<'0')++pi;\
	while(*pi>='0')res=(res*10)+(*pi++^48);
void print(int x){
	if(x>9)print(x/10);
	*++po=x%10^48;
}
int n,m,h[Maxx],nx[Maxx],to[Maxx],sn[Maxx],sz[Maxx],prt[Maxx],cl[Maxx];
int gf(int x){return prt[x]==x?x:prt[x]=gf(prt[x]);}
void Merge(int x,int y){
	if((x=gf(x))^(y=gf(y))){
		if(sz[x]>sz[y])swap(x,y);
		sz[prt[x]=y]+=sz[x];
		if(!sn[y]||!sn[x])sn[y]=sn[x]|sn[y];
		else if(sn[x]^sn[y])Merge(sn[x],sn[y]);
	}
}
signed main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	fread(pi=bif,Mxdt,1,stdin),po=bof-1;
	char bj;int x,res;Rd()n=res;Rd()m=res;
	for(int i=1;i<=n;++i)prt[sz[i]=i]=i;
	for(int i=1,x;i<=m;++i){
		Rd()nx[i]=h[x=res];
		Rd()to[h[x]=i]=res;
	}
	for(int i=1;i<=n;++i){
		bj=0,x=gf(i);
		for(int j=h[i];j;j=nx[j])bj|=gf(to[j])==x;
		//特判会把儿子合上自己的情况
		if(!bj)x=sn[x]?sn[x]:(sn[x]=to[h[i]]);
		//如果原来没有后继，维护一下
		else if(sn[x])prt[sn[x]=gf(sn[x])]=x,sn[x]=sn[sn[x]];
		//Update:2020.9.28，此时应该合上自己和自己在链上的儿子 
		for(int j=h[i];j;j=nx[j])Merge(to[j],x);
	}
	int cnt=0;
	for(int i=1;i<=n;++i)if(!cl[gf(i)])cl[prt[i]]=++cnt;
	for(int i=1;i<=n;++i)print(cl[gf(i)]),*++po='\n';
	return fwrite(bof,po-bof+1,1,stdout),0;
}
/*
Hack:
5 5
2 5
2 3
5 3
2 4
3 1
*/ 
```

Update:2020.9.28

感谢 @传奇英雄 指出的错误。我的代码里在特判把儿子合上自己时判错了一点情况，更正在代码里有体现


---

## 作者：pocafup (赞：7)

赛前没学过启发式合并，刚刚补了下，来发篇题解。

不要以为启发式是什么高级的东西，其实他通俗来说就是假设某一个节点有超过两条边，就将这两条边所指向的点进行合并。

合并操作其实就是暴力将某个点的所有儿子传给另一个节点，然后更新这个节点的父亲，这样以后这个节点就不会再访问到了（思路==并查集）

有人（比如我）珂能会不理解：这样合并不会被卡成 $O(n^2)$ 的吗？

启发式的妙点在于，当我们合并两个点时，我们一定取那个边数少的进行合并。

```
if (son[s].size()>son[f].size()) swap(f,s);
for (int v : son[s]){fa[v] = f;son[f].push_back(v);}
```

对于这题，我们先进行输入，然后暴力枚举节点，找出邻边数大于 $1$ 的所有节点并放入队列，然后再合并每个队列中的点的邻边所对应的点（好绕）。

~~什么，让我说人话？~~

好吧，我们来分析下样例（

首先，下图圈起来的节点表示一开始有两条出边或以上的节点。

![](https://cdn.luogu.com.cn/upload/image_hosting/41u3x5hp.png?x-oss-process=image/resize,m_lfit,h_250,w_340)

假设我们先操作点 $3$，那么我们会合并点 $4，5$，也就是下面这个图。

![](https://cdn.luogu.com.cn/upload/image_hosting/9zykz2yn.png?x-oss-process=image/resize,m_lfit,h_250,w_340)

然后我们继续操作点四，得到以下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/n8ky07iv.png?x-oss-process=image/resize,m_lfit,h_250,w_340)

~~好丑~~

之后就不一一列举了，但最后会发现操作后的图能够保证牛之间不会矛盾。

字典序怎么办？当然是从小到大枚举，如果某个节点的父节点未有编号，就让他用一个新的编号，否则用回父节点的旧编号。

代码如下
```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
queue<int> q;
const int MAXN = 2e5+5;
const int MAXM = 3e5+5;
namespace Union_Find{
  int n,m,k,a,b,c,fa[MAXN],tot,head[MAXN];
  vector<int> adj[MAXN],son[MAXN];
  inline void solve();
  inline void Union(int f, int s){
    f = fa[f], s = fa[s];
    if (son[s].size()>son[f].size()) swap(f,s);//启发式的操作
    for (int v : son[s]){fa[v] = f;son[f].push_back(v);}//继承子节点
    for (int v : adj[s]) adj[f].push_back(v);//继承子节点的边
    if (adj[f].size()>1) q.push(f);//如果他的边数小于2，那么这个节点无法进行合并操作，也就不需要放入队列。
  }
}
int group[MAXN],cnt;
#define lst adj[qf].size()-1
inline void Union_Find::solve(){
  cin >> n >> m;
  for (int i=1;i<=m;i++){
    cin >> a >> b;
    adj[a].push_back(b);
  }
  for (int i=1;i<=n;i++){
    fa[i] = i;//自己的父亲是自己（
    son[i].push_back(i);//自己的儿子有自己
    if (adj[i].size()>1) q.push(i);//能更否
  }
  while(!q.empty()){
    int qf = q.front(); q.pop();
    while(adj[qf].size()>1){
      int last = adj[qf][lst]; adj[qf].pop_back();
      if (fa[last]!=fa[adj[qf][lst]]) Union(last,adj[qf][lst]);//如果不在同一集合
    }
  }
  for (int i=1;i<=n;i++){
    if (!group[fa[i]]) group[fa[i]] = ++cnt;//新建编号
    cout << group[fa[i]] << endl;//输出
  }
}
void setIO(string name) {
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
	ios_base::sync_with_stdio(0);
}
signed main(){
  Union_Find::solve();
}
```


---

## 作者：hhhyyyfff (赞：4)

- 题意简述：  
  有 $N\ (1 \le N \le 2 \times 10^5)$ 头牛，$M\ (1 \le M \le 2 \times 10^5)$ 对仰慕关系 $(a,b)$（$b$ 仰慕 $a$），每头牛喜欢一种颜色，若牛 $a$ 和 $b$ 都仰慕喜欢颜色 $c$ 的牛，则牛 $a$ 和 $b$ 喜欢同种颜色，求这些牛最多喜欢几种不同颜色，输出字典序最小的方案。

- 前置知识：并查集，启发式合并

- 代码片段：

``` plain
Dfs(x)
  root <- u that has an edge (x,u)
	For Edge(x,i)
		root <- Merge(root, i)
	Delete(For Edge(x, i))
	Make(Edge(x, root))
	Dfs(root)
Main()
	For i in [1,n]
		Dfs(i)
```

- 算法分析 $O(N \log N)$：  
  将喜欢同种颜色的牛放进一个集合，则仰慕集合内的牛的牛在同一集合。  
  **代码片段**种的操作，若两头牛仰慕同一集合内的牛，则放进一个集合，合并两头牛。对每头牛进行此操作，每个更改的集合也进行此操作。所有操作结束后满足题目要求，因为一定要合并已经合并（不存在仰慕统一集合内的牛的两头牛，属于不同集合），没有合并不需要合并的两个集合。  
  点的合并可以用**并查集**实现，最多 $N$ 次，但是还要把点**连出**的边也一起合并。这里可以使用**启发式合并**，将边数少的合并到多的。这样就能把时间复杂度降到总和 $O(N \log N)$，将合并过程看作树，具体证明类似于**树上启发式合并**。

- 代码：

``` cpp
#include <cstdio>
#include <vector>

using namespace std;

vector<int> e[200010];
int N, M, x, y, cnt, f[200010], ans[200010];

int gf(int x) { return x == f[x] ? x : f[x] = gf(f[x]); }

void dfs(int x) {
    //printf("%d\n", x);
    int l = e[x].size();
    if (l < 2) return;
    vector<int> tmp(e[x]);
    e[x].clear();
    int root = gf(tmp[0]);
    for (int i = 1; i < l; ++i) {
        int y = gf(tmp[i]);
        if (root != y)
            if (e[root].size() >= e[y].size()) {
                for (int j : e[y]) e[root].push_back(j);
                f[y] = root;
            } else {
                for (int j : e[root]) e[y].push_back(j);
                root = f[root] = y;
            }
    }
    e[x].push_back(root);
    dfs(root);
}

int main() {
  freopen("fcolor.in", "r", stdin);
  freopen("fcolor.out", "w", stdout);
  scanf("%d%d", &N, &M);
  while (M--) {
    scanf("%d%d", &x, &y);
    e[x].push_back(y);
  }
  for (int i = 1; i <= N; ++i) f[i] = i;
  for (int i = 1; i <= N; ++i) dfs(i);
  for (int i = 1; i <= N; ++i) {
      int x = gf(i);
      if (ans[x] == 0) ans[x] = ++cnt;
      printf("%d\n", ans[x]);
  }
  return 0;
}
```

---

## 作者：传奇英雄 (赞：4)

Update:2020/9/30 改了下图，现在应该好多了。

本题有2篇C++11题解，唯一一个C++的好像还有些问题。这里提供一篇C++的题解。

注意：本题数据很水，部分错误代码可以通过！[hack](https://www.luogu.com.cn/discuss/show/259653)

这个题不是死题，应该是有解法的。

个人感觉合并链是不太可行的，树上启发式合并才是正解。（详见其他题解，就不多说了）

根据题意我们可以得出：1个点的所有儿子颜色相同，那么他的所有孙子（儿子的儿子）颜色也相同。所以我们合并这个点的所有儿子节点。（将其他儿子的儿子全都连在某个儿子上），为了使复杂度达到O(n log n)，我们数量小的合并到数量大的上面。（即：将儿子数量小的儿子的儿子合并到儿子数量大的儿子上）

![正常的数据](https://cdn.luogu.com.cn/upload/image_hosting/yz287yge.png)

对于这个数据：由于节点1，所以2,3颜色一样，那么4,5,6,7颜色都相同。那么我们加入边（3,4），删掉边（2,4）。即：将4号节点合并到3号节点上。因为3号节点的儿子多，为了减少复杂度，我们将2号节点的儿子合并到3号节点上（只需要改1个），而不是将3号节点的儿子合并到2号节点上（这样就需要改3个了，不够优秀）。

但是我们需要考虑一些特殊情况：

in
```cpp
4 5
1 2
2 3
2 4
3 4
4 1
```

out

```cpp
1
1
1
1
```

![hack](https://cdn.luogu.com.cn/upload/image_hosting/8264nx87.png)

这个数据是一个类似于自环的情况，由于节点2，那么3和4颜色相同，那么就是自己仰慕自己，那么1,2,3,4应该颜色均相同才对。（这个数据可能可以卡掉合并链的做法）

然后我还自己造了一个数据：

in

```cpp
6 6
1 2
1 3
2 3
2 4
4 5
5 6
```
out

```cpp
1
2
2
2
2
2

```
![hack](https://cdn.luogu.com.cn/upload/image_hosting/lvsb0s5t.png)

这也是一个类似于自环的情况。我们发现：只要有一个节点自己仰慕自己的情况，那么这个节点的后代显然都是和这个节点颜色一样的。

这里参考了[网上的代码](https://blog.csdn.net/tianyizhicheng/article/details/107289805)

在我的代码中，如果要将k合并到b上，那么我们将f[k]（并查集中的祖先）合并到f[b]上。这样就可以解决这种类似自环而自己仰慕自己的情况。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int g=200005;
int n,m,a,b,k,f[g],c[g],cnt;
vector<int> x[g];//vector便于加边删边

int ff(int t)//查找祖先
{
	if(f[t]==t)
		return t;
	return f[t]=ff(f[t]);
}

void dfs(int t)
{
	b=x[t][0];
	a=x[b].size();
	for(int i=1;i<x[t].size();i++)
		if(int(x[x[t][i]].size())>a)//合并到儿子最多的点上
		{
			b=x[t][i];
			a=x[b].size();
		}
	b=ff(b);
	for(int i=0;i<x[t].size();i++)
	{
		k=ff(x[t][i]);//t的一个儿子k
		if(k!=b)//合并k和b
		{
			f[k]=b;
			for(int j=int(x[k].size())-1;j>=0;j--)//将k的儿子全都改成b的儿子
				x[b].push_back(x[k][j]);
			x[k].clear();
		}
	}
	x[t].clear();
	x[t].push_back(b);
	if(x[b].size()>1)
		dfs(b);
}

int main()
{
	//freopen("in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		x[a].push_back(b);
	}
	for(int i=1;i<=n;i++)//并查集初始化
		f[i]=i;
	for(int i=1;i<=n;i++)
		if(x[i].size()>1)
			dfs(i);
	for(int i=1;i<=n;i++)
	{
		if(!c[ff(i)])//按字典序编号
			c[f[i]]=++cnt;
		printf("%d\n",c[f[i]]);
	}
	return 0;
}
```


---

## 作者：DYYqwq (赞：3)

考虑到如果一头奶牛同时喜欢上了许多头奶牛（这么渣？），那被它喜欢的这些奶牛只能是一个颜色的。

于是我们可以把这些被喜欢的奶牛合并成块。直到一个块变得专一，不再同时喜欢两个块，换句话说，每个块的出度 $\le 1$。

这样块的数量就是我们的最大颜色数量。因为我们并不强制要求不同块中的奶牛喜欢同一种颜色。

但是我们发现如果直接无脑合并 $O(n^2)$ 的复杂度直接飞起来。

于是考虑使用启发式合并。直接按秩合并，哪坨少把这坨合并到多的那坨里。

完事了。启发式合并的复杂度很优秀，总体复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n , m , fa[200010] , col[200010];
vector<int> v[200010] , son[200010];
queue<int> q;
void merge(int x , int y)
{
	x = fa[x] , y = fa[y];
	if(son[x].size() < son[y].size()) x ^= y , y ^= x , x ^= y;
	for(int i = 0 ; i < v[y].size() ; i ++) v[x].push_back(v[y][i]);
	for(int i = 0 ; i < son[y].size() ; i ++) fa[son[y][i]] = x , son[x].push_back(son[y][i]);
	if(v[x].size() > 1) q.push(x);
}
int main()
{
	scanf("%d%d" , &n , &m);
	for(int i = 1 ; i <= m ; i ++)
	{
		int uu , vv;
		scanf("%d%d" , &uu , &vv);
		v[uu].push_back(vv);
	}
	for(int i = 1 ; i <= n ; i ++)
	{
		fa[i] = i;
		if(v[i].size() > 1) q.push(i);
		son[i].push_back(i);
	}
	while(!q.empty())
	{
		int tmp = q.front();
		q.pop();
		while(v[tmp].size() > 1)
		{
			int x = v[tmp][0] , y = v[tmp][1];
			v[tmp].erase(v[tmp].begin());
			if(fa[x] != fa[y]) merge(x , y);
		}
	}
	int num = 0;
	for(int i = 1 ; i <= n ; i ++)
	{
		if(col[fa[i]] == 0) col[fa[i]] = ++ num;
		printf("%d\n" , col[fa[i]]);
	}
	return 0;
}
```

---

## 作者：DengDuck (赞：2)

这题的思路非常容易，就是不停缩点，把颜色一样的点缩成一个点，或者说就是合并。

但是我认为这题不适合并查集，为什么呢？

首先，我们肯定的是并查集肯定是可以的，我一开始写的也是并查集。

但是，并查集通常有两个玩法：

一个是维护连通块，表示这些东西都一样，缩点通常解决这个，使用的是普通并查集。

一个是维护一些关系，像这题就是要维护崇拜的关系，我们用带权并查集。

那么这题两种都要，用并查集略显麻烦。

所以暴力维护连通块就比较好。

因为暴力维护连通块，连通块本身可以记录有哪些节点，合并的时候也合并这个信息，然后崇拜的连边关系可以再额外合并。

这样信息就简洁的合并了，而且十分好写。

结合启发式合并，可以做到 $\mathcal O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define LF long double
#define pLL pair<LL,LL>
#define fir first
#define sec second
#define pb push_back
using namespace std;
const LL N=6e5+5;
LL n,m,sz[N],fa[N],col[N],vis[N],tot;
vector<LL>hav[N],v[N];
queue<LL>q;
void merge(LL x,LL y)
{
	x=fa[x],y=fa[y];
	if(hav[x].size()<hav[y].size())swap(x,y);
	for(LL i:v[y])
	{
		v[x].pb(i);
	}
	for(LL i:hav[y])
	{
		fa[i]=x,hav[x].pb(i);
	}
	if(v[x].size()>1)q.push(x);
}

int main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++)
	{	
		LL x,y;
		scanf("%lld%lld",&x,&y);
		v[x].pb(y);
	}
	for(int i=1;i<=n;i++)
	{
		fa[i]=i;
		if(v[i].size()>1)q.push(i);
		hav[i].pb(i);
	}
	while(!q.empty())
	{
		LL x=q.front();
		q.pop();
		while(v[x].size()>1)
		{
			LL X=v[x][0],Y=v[x][1];
			v[x].erase(v[x].begin());
			if(fa[X]!=fa[Y])merge(X,Y);
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(!col[fa[i]])col[fa[i]]=++tot;
		printf("%lld\n",col[fa[i]]);
	}
}
```

---

## 作者：Eterna (赞：1)

一开始没看懂题呀，后来感觉也没那么难。

多只奶牛同时仰慕同一只奶牛，那这些奶牛颜色一定相同。奶牛的颜色和这只奶牛喜欢的颜色是无关的。

比如输入数据是：


```
5 6
2 1
1 3
2 3
4 3
5 2
5 3
```

她变成图是这样的，方向为被仰慕：

![](https://cdn.luogu.com.cn/upload/image_hosting/jory6xoq.png)

那么因为 $5$ 同时被 $2,3$ 仰慕，所以 $2,3$ 颜色相同。又因为 $2$ 同时被 $1,3$ 仰慕，所以 $1,3$ 颜色相同。因此得到 $1,2,3$ 是相同的颜色。

$4,5$ 只有被仰慕而不仰慕其他奶牛，为了使颜色尽可能多，我们分别给他们分两个与 $1,2,3$ 不同的颜色即可。

故输出：


```
1
1
1
2
3
```

注意到这是一个颜色合并的过程，考虑暴力实现复杂度会到 $O(n^2)$，是过不了的。

考虑启发式合并，每个颜色都是一个奶牛组成的集合，设要合并集合 $a,b$，不管我们将 $a$ 合并到 $b$，还是将 $b$ 合并到 $a$ 都是本质相同的，但是我们合并的操作次数是合并到另一个集合的那个集合的大小。如果我们将小的集合合并到大的集合，我们就可以少许多操作次数。

这种看似乱搞的做法事实上复杂度是 $O(n \log n)$，因为每次合并奶牛所在的集合大小至少翻倍，故一头奶牛最多被合并 $\log n$ 次。

---

## 作者：koobee (赞：1)

P6279

首先考虑建边。如果 $b$ 仰慕 $a$，就从 $a$ 往 $b$ 建一条边，这样写代码会方便很多。

可以用一个类似拓扑排序的算法，再结合并查集。可以先将每个点视为一个单独的集合，一开先将出度大于 $1$ 的点放入队列。每次取出队首，枚举它的后继，如果它的后继至少有 $2$ 个，就把他的后继所对应的集合合并为一个大集合（用启发式合并）。最后，如果这个新集合的出度大于 $1$，就把新集合放入队列。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
int n, m, c[N], f[N], cnt, col[N];
queue<int> q;
vector<int> v[N];
int find(int x){
	if(f[x] == x) return x;
	return f[x] = find(f[x]);
}
int merge(int x, int y){
	x = find(x); y = find(y);
	if(v[x].size() > v[y].size()) swap(x, y);
	for(int i : v[x]) v[y].push_back(i);
	v[x].clear();
	f[x] = y;
	return y;
}
int main(){
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin>>n>>m;
	for(int i = 1; i <= n; i++) f[i] = i;
	for(int i = 1; i <= m; i++){
		int a, b;
		cin>>a>>b;
		v[a].push_back(b);
	}
	for(int i = 1; i <= n; i++)
		if(v[i].size() > 1) q.push(i);
	while(!q.empty()){
		int t = q.front();
		q.pop();
		int now = v[t][0];
		for(int i = 1; i < v[t].size(); i++){
			int x = v[t][i];
			if(find(now) == find(x)) continue;
			now = merge(now, x);
		}
		v[t].clear();
		v[t].push_back(now);
		if(v[f[now]].size() > 1) q.push(f[now]);
	}
	for(int i = 1; i <= n; i++){
		if(col[find(i)] == 0) col[find(i)] = ++cnt;
		cout<<col[find(i)]<<"\n";
	}
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

### 题面
从前从前，有一群牛有各自颜色并崇拜一群牛，规定崇拜同一颜色的牛的牛为一种颜色。给出崇拜关系，让你最大化牛颜色种数。

### 思路
显然的并查集，对于一个牛，我们把崇拜他的所有牛合并到他的祖先上，最后剩下几组就是几个颜色，显然的 $O(n^2)$ 做法。然后加一个启发式合并，就可以把它简化到 $O(n\log{n})$，给个小证明：

当 $x$ 合并到 $y$ 时 $x<y$，$y$ 大小将大于 $2 \times x$，以此类推，当我们把他们合并到大小小于等于 $n$ 时，数被合并的次数会严格小于等于 $\log{n}$。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long 
#define Maxn 200005 
using namespace std;
vector<int> q[Maxn];
bool vis[Maxn];
int f[Maxn],dis[Maxn];
int find(int x) {
    if(f[x]==x)return x;
    return f[x]=find(f[x]);
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++) {
        int u,v;
        cin>>u>>v;
        q[u].push_back(v);
    } queue<int> Q;
    for(int i=1;i<=n;i++) {
        f[i]=i;
        if(q[i].size()>1)
            vis[i]=true,
            Q.push(i);
    }
    while(!Q.empty()) {
        int i=Q.front();Q.pop();
        while(q[i].size()>1) {
            int u=find(q[i][q[i].size()-1]);
            int v=find(q[i][q[i].size()-2]);
            q[i].pop_back();
            if(u == v)continue;
            if(q[u].size()<q[v].size())
                swap(u,v);
            f[v]=u;
            for(int k:q[v])
                q[u].push_back(k);
            if(q[u].size()>1&&!vis[u])
                Q.push(u),vis[u]=true;
        } vis[i]=false;
    } int ans=0;
    for(int i=1;i<=n;i++) {
        int fx=find(i);
        if(!dis[fx])dis[fx]=++ans;
        cout<<dis[fx]<<"\n";
    }
    return 0;
}
```

---

## 作者：Usada_Pekora (赞：0)

这题的做法其实很暴力，就是使用并查集维护连通块（缩点）。

先来想想为什么这么做：

同一奶牛只能喜欢一个颜色，奶牛喜欢的颜色跟仰慕对象的喜欢颜色一样，那么一只奶牛与仰慕该奶牛的奶牛喜欢的是同一颜色。

当出现一只奶牛仰慕多只奶牛时，把两个连通块合并起来即可。

但是由于本题数据较大，所以要用按秩合并。

按秩合并的思想是每一次合并都把节点向深度 （高度） 大的节点上进行合并。

按秩合并代码：
```cpp
inline void merge(int x,int y){
	x=getfa(x),y=getfa(y);
	if(x==y)return;
	if(dep[x]<dep[y])fa[x]=y;
	else{
	fa[y]=x;
	if(dep[x]==dep[y])dep[x]++;
   }
}
```

 AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 200005
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1; c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48); c=getchar();}
	return x*f;
}
vector<int>G[N];
int n,m,fa[N],c[N];
inline int getfa(int x){
	return fa[x]==0?x:fa[x]=getfa(fa[x]);
}
inline void dfs(int u){
    if(G[u].size()<2) return;
    int x=getfa(G[u][0]);
    for(int i=1;i<G[u].size();i++){
        int y=getfa(G[u][i]);
        if(x==y)continue;
        if(fa[x]<=fa[y]){
            fa[x]+=fa[y];
            fa[y]=x;
            for(int j=0;j<G[y].size();j++)
                G[x].push_back(G[y][j]);
            G[y].clear();
        }
        else{
            fa[y]+=fa[x];
            fa[x]=y;
            for(int j=0;j<G[x].size();j++)
                G[y].push_back(G[x][j]);
            G[x].clear();
            x=y;
        }
    }
    G[u].clear();
    G[u].push_back(x);
    dfs(x);
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		G[u].push_back(v);
	}
	for(int i=1;i<=n;i++)
		dfs(i);
	int cnt=0;
	for(int i=1;i<=n;i++){
		int fi=getfa(i);
		if(!c[fi]) c[fi]=++cnt;
		printf("%d\n",c[fi]);
	}
	return 0;
}
```



---

