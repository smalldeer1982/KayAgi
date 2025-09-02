# PolandBall and Forest

## 题目描述

PolandBall lives in a forest with his family. There are some trees in the forest. Trees are undirected acyclic graphs with $ k $ vertices and $ k-1 $ edges, where $ k $ is some integer. Note that one vertex is a valid tree.

There is exactly one relative living in each vertex of each tree, they have unique ids from $ 1 $ to $ n $ . For each Ball $ i $ we know the id of its most distant relative living on the same tree. If there are several such vertices, we only know the value of the one with smallest id among those.

How many trees are there in the forest?

## 说明/提示

In the first sample testcase, possible forest is: 1-2 3-4-5.

There are $ 2 $ trees overall.

In the second sample testcase, the only possible graph is one vertex and no edges. Therefore, there is only one tree.

## 样例 #1

### 输入

```
5
2 1 5 3 3```

### 输出

```
2```

## 样例 #2

### 输入

```
1
1
```

### 输出

```
1```

# 题解

## 作者：xiaomuyun (赞：6)

# CF755C PolandBall and Forest 题解
[题目传送门](https://www.luogu.com.cn/problem/CF755C)
## 题目分析
题目说得很清楚了：并查集。求的是集合的数量。因此我们需要在所有节点的根中去重，这里本蒟蒻献上另外一种去重方法：C++ 中的 $\operatorname{set}$。因为 $\operatorname{set}$ 可以自动给里面的元素去重，所以可以将所有节点的根加入 $\operatorname{set}$ 后，求出它的大小并输出即可。

也不必多说什么了，上代码。
## code
```cpp
#include<cstdio>
#include<set>

using namespace std;

int n,fa[10001],ra[10001];
set<int> ans;//STL大法好

void Init(){
	for(int i=1;i<=n;++i) fa[i]=i;
}

int find(int u){
	if(u==fa[u]) return u;
	return fa[u]=find(fa[u]);
}

void join(int u,int v){
	int fu=find(u),fv=find(v);
	if(fu==fv) return ;
	if(ra[fu]>ra[fv]){
		fa[fv]=fu;
	} else {
		fa[fu]=fv;
	}
	return ;
}

int main(){
	scanf("%d",&n);
	Init();
	for(int i=1,f;i<=n;++i){
		scanf("%d",&f);
		join(i,f);//合并集合
	}
	for(int i=1;i<=n;++i) ans.insert(find(i));//加入set
	printf("%d\n",ans.size());
	return 0;
}
```
## 在最后的最后
点个赞吧，制作不易！

---

## 作者：BLX32M_10 (赞：2)

## 题意

给你一张图，每个点的父亲节点。求这张图中连通块的个数。



## 题解

考虑求连通块，直接用并查集解决。

如果你还不知道什么是并查集，请看[这里](https://zhuanlan.zhihu.com/p/93647900/)

相信大家已经了解到并查集，那么下面讲解一下并查集求连通块

~~本人画工很烂，大佬勿喷~~

拿下面的图举例：

![](https://cdn.luogu.com.cn/upload/image_hosting/3kp1zsgl.png)

这是 $3$ 个元素并查集的初始状态，共有 $3$ 个连通块。

接下来，将 $1$ 的父节点设为 $2$：

![](https://cdn.luogu.com.cn/upload/image_hosting/iz25l6ao.png)

我们可以发现，连通块的数量减少了一个。

会不会是每加一个，连通块的数量就减少一个呢？

容易举出反例，初始状态：

![](https://cdn.luogu.com.cn/upload/image_hosting/11p6cab4.png)

此时连通块数量为 $2$，然后将 $1$ 的父节点设为 $4$：

![](https://cdn.luogu.com.cn/upload/image_hosting/7sz0423l.png)

此时的连通块数量仍然为 $2$。

经过测试，我们能够发现并查集的合并操作中如果新指向的元素的根节点与原来的根节点相等，

那么，这个合并操作不能减少连通块的数量。

正好，**这个特性与并查集中合并操作的优化一模一样**，

并且适当的合并操作能够减少时间复杂度（如果没有秩优化的话时间复杂度是 $\mathcal{O}(n \log n)$），

所以在合并操作内部加上减少连通块的条件，就能解决此题了！

$30$ 行 AC 代码：

```cpp
#include <cstdio>
int fa[10005], ans, fx, fy, n, x;
void init()
{
	for (int i = 1; i <= n; i++)
		fa[i] = i;
}
int find(int x)
{
    return x == fa[x] ? x : (fa[x] = find(fa[x]));
}
void merge(int x, int y)
{
	fx = find(x), fy = find(y);
	if (fx != fy)
		fa[fy] = fx, ans--;
}
int main()
{
	scanf("%d", &n);
	ans = n;
	init();
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x);
		merge(i, x);
	}
	printf("%d", ans);
	return 0;
}
```

---

## 作者：_byta (赞：2)

用并查集维护连通块，初始每个节点的祖先都设为自己，之后每读入一个节点的父节点，就把两个点所在的连通块合并。

最后只要统计有多少个祖先节点互相独立即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 100002;
int n, m, k, p, ans, sum, t, tot, cnt, a[N], b[N], c[N], d[N], f[N];
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while(!isdigit(ch))
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(isdigit(ch))
    {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
int find(int x)
{
    if(f[x] == x) return x;
    return f[x] = find(f[x]);
}
int main()
{
    n = read();
    
    for(int i = 1; i <= n; i++)
    {
        f[i] = i;
    }
    for(int i = 1; i <= n; i++)
    {
        int x = read();
        int y = find(x), z = find(i);
        if(y != z) f[y] = z;
    }
    for(int i = 1; i <= n; i++)
    {
        if(!b[find(i)]) 
        {
            ans++;
            b[find(i)] = 1;
        }
    }
    cout << ans << endl;
    return 0;
}
```


---

## 作者：Vector_ (赞：2)

## 题目大意

对于一张有$n$个点的无向图，每个点都连接着另一个点，求这张无向图中的连通块个数。$(1$<=$n$<=$10^4)$

## 题目算法

看到无向图求连通块，很自然地想到并查集。

并查集$（Union-Find Set）$：一个维护点之间连通性的数据结构，每个连通块都有一个代表元素，可以是该连通块的任意元素。在一开始，每个点都是自己所在连通块的代表元素。并查集的基本操作有三个。

1. 寻找一个点所在连通块的代表元素。

一直寻找这个点的连通块代表，直到这个点的连通块代表是它自己。

```cpp
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
```

这里展示的是带有路径压缩的版本，即每次寻找时把中途经过的点直接连到连通块的代表上，以缩短下次寻找时的路径长度。

2. 判断两个点是否处于同一连通块。

判断两个点所在的连通块代表是否为一个即可。

```cpp
find(x)==find(y)
```
3. 合并两个点所在的连通块。

先判断两点是否本就在同一连通块中，是则忽略，否则将一个点的连通块代表的连通块代表设置为另一个点的连通块代表即可。

```cpp
void un(int x,int y){if(find(x)==find(y)) return;f[find(y)]=find(x);}
```

注意到每次合并后连通块个数会$-1$, 一开始的连通块个数为$n$，借此可以统计最终连通块的个数。

带路径压缩的并查集时间复杂度为$O(nα(n))($其中$α(n)$为反阿克曼函数，增长很慢，可以近似视为常数$)$，可以通过本题。

## $AC$代码$(C++)$

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int f[10010],cnt;
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}//寻找点的连通块代表元素
void un(int x,int y){if(find(x)==find(y)) return;f[find(y)]=find(x);cnt--;}//合并两点所在的连通块
//合并成功则连通块个数-1
int main()
{
	int n;
	cin>>n;
	cnt=n;//初始化连通块个数
	for(int i=1;i<=n;i++) f[i]=i;//初始化并查集
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		un(i,x);//尝试合并，成功则减少连通块个数
	}
	cout<<cnt<<endl;
	return 0;
}
```

---

## 作者：Y2y7m (赞：1)

翻译已经说的很明白了，求连通块数量。

一般的求连通块数量有两种方案: 搜索或并查集。

**首先我们来看搜索**

应为这个图上的边权是有向边。

所以我们不知道从那个点开始搜才能到达这个连通块的所有点。

因此：**搜索不可取**。

**接下来我们来看并查集**

每次把两个点直接并查集并在一块即可

最后我们看有哪些节点的根就是自己就行了

代码：

```cpp
#include <bits/stdc++.h>

using namespace std;
int root[10010];
int getroot(int x)//路径压缩
{
	if(root[x]==x)
		return x;
	return root[x]=getroot(root[x]);
}
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
		root[i]=i;
	int x;
	for(int i=1;i<=n;i++)
	{
		cin>>x;
		root[getroot(i)]=getroot(x);
	}
	int cnt=0;
	for(int i=1;i<=n;i++)
		if(root[i]==i)
			cnt++;
	cout<<cnt<<endl;
	return 0;
}

```


---

## 作者：Jsxts_ (赞：1)

# 题解 CF755C

[传送门](https://www.luogu.com.cn/problem/CF755C)

## 题意

给定一张图，第 $i$ 个数表示这个点的父亲为 $i$，求这个图的连通块个数。

## 题解

这道题非常简单，我们可以用两种方法做。一种是并查集，一种是深搜。

用并查集的话，就把节点 $x$ 与它的父亲加进一个集合，最后统计集合数量。

用深搜，就对父亲连完边后从一个未被访问的点遍历到其他点，最后统计未被访问的点的个数。加上快读就跑到了最优解。

并查集代码 $(302ms)$ ：

```cpp
#include <bits/stdc++.h>
using namespace std;
int fa[100010];
int find(int x) {//并查集模板--找父亲 
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
void join(int x,int y) {//合并 
	int fx = find(x),fy = find(y);
	if (fx != fy) fa[fx] = fy;
}
int main() {
	int n;
	scanf("%d",&n);
	for (int i = 1;i <= n;i ++ ) {//初始化并查集 
		fa[i] = i;
	}
	for (int i = 1;i <= n;i ++ ) {
		int x;
		scanf("%d",&x);
		join(x,i);
	}
	int cnt = 0;
	for (int i = 1;i <= n;i ++ ) cnt += fa[i] == i;//如果节点i的父亲是它本身，就是它所在集合中的祖先 
	printf("%d",cnt);
	return 0;
}
```

深搜代码 $(210ms)$ :

```cpp
#include <bits/stdc++.h>
using namespace std;
struct edge {
	int v,nxt;
}ed[20010];//前向星建边 
int vis[10010],head[10010],cnt;
void add(int u,int v) {
	ed[++cnt] = (edge){v,head[u]};
	head[u] = cnt;
}
inline int read() {//快读
	register int s = 0;
	register char ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) s = (s << 3) + (s << 1) + ch - '0',ch = getchar();
	return s;
}
void dfs(int x) {
	vis[x] = 1;
	for (int i = head[x];i;i = ed[i].nxt) {
		if (!vis[ed[i].v]) dfs(ed[i].v);
	}
}
int main() {
	int n = read();
	for (int i = 1;i <= n;i ++ ) {
		int x = read();
		add(x,i), add(i,x);//向父亲连边 
	}
	int cnt = 0;
	for (int i = 1;i <= n;i ++ ) {
		if (!vis[i]) dfs(i),cnt ++;//深搜可以遍历完一个连通块 
	}
	printf("%d",cnt);
	return 0;
}
```


---

## 作者：Eason_AC (赞：1)

## Content
给定无向图的 $n$ 个点的父亲节点，求无向图的联通块个数。

**数据范围：$1\leqslant n\leqslant 10^4$。**
## Solution
并查集模板题。

我们将在当前节点和它的父亲节点连在一起，然后看不同的祖先节点的个数即可。

没学过并查集的同学建议先去做 [P3367 【模板】并查集](https://www.luogu.com.cn/problem/P3367)。
## Code
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;

int n, a[10007], f[10007], vis[10007], ans;

int getfa(int x) {
	return (x == f[x]) ? x : f[x] = getfa(f[x]);
}
void unionn(int x, int y) {
	x = getfa(x), y = getfa(y);
	if(x != y) f[x] = y;
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) f[i] = i;
	for(int i = 1; i <= n; ++i) {
		int x;
		scanf("%d", &x);
		unionn(x, i);
	}
	for(int i = 1; i <= n; ++i)
		if(!vis[getfa(i)]) ans++, vis[getfa(i)] = 1;
	printf("%d", ans);
	return 0;
}

```

---

## 作者：_Revenge_ (赞：0)

### 题目简化和分析：  

这题不用说怎么分析了吧，这一看就是个并查集求连通分量个数的经典模板。    

我们需要将 $i$ 和 $p_i$ 进行合并。  

遍历每个 $i$ 与 $i+1$ 是否属于同一个集合。   

- 属于不管。  
- 不属于贡献增加，并合并。    

注意范围！  
### Solution:

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
#define int long long
const int N=1e4+50;
const int mod=1e9+7;
int t,n;
int p[N],a[N];
int find(int x){
	if(x!=p[x]) return p[x]=find(p[x]);
	return p[x]; 
}
signed main()
{
		scanf("%lld",&n);
		for(int i=1;i<=n;++i) p[i]=i;		
		for(int i=1;i<=n;++i){
			scanf("%lld",&a[i]);
			int fx=find(i),fy=find(a[i]);
			if(fx!=fy){
				p[fx]=fy;
			}
		}
		int ans=1;
		for(int i=1;i<n;++i){
			int fx=find(i),fy=find(i+1);
			if(fx!=fy){
				ans++;
				p[fx]=fy;
			}
		}
		printf("%lld\n",ans);
}
```

---

## 作者：fengxiaoyi (赞：0)

### 修改日志

- 2022.8.4：对算法进一步描述。

- 2022.8.5：更改 $\LaTeX$ 的写法，将 AC 的 $\LaTeX$ 去处。

### 思路
这题，只需要将输入的数据建成无向图就好了。

对于每个未访问的点，将 $ans+1$，然后遍历一遍他的儿子。

如果儿子节点已经访问过了，那直接通过。

否则，将儿子节点标记为已访问，然后遍历儿子的儿子节点。

最终输出 $ans$ 即可。

### AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,num,f[20010],nxt[20010],to[20010],ans;
bool b[10010];
void dfs(int u){
	b[u]=1;
	for(int i=f[u];i;i=nxt[i]){
		if(b[to[i]]){
			continue;
		}
		dfs(to[i]);
	}
}
void add(int a,int b){
	to[++num]=b;
	nxt[num]=f[a];
	f[a]=num;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		int fa;
		cin>>fa;
		add(fa,i);
	}
	for(int i=1;i<=n;i++){
		if(!b[i]){
			ans++;
			dfs(i);
		}
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：linyinuo2008 (赞：0)

这道题其实评黄有点高，大概就是一道并查集的模板题。

# 一、题目大意

就是给你一章图，求连通块个数。

# 二、算法理解

我们在此可以使用并查集的算法，把所有位于同一个的连通块内所有点的父亲设为同一个。之后仅需要查找两个节点的父亲值是否相同就可以判断它们是否在一个连通块内。

关于更多并查集的问题以及应用来[这里](https://www.jianshu.com/p/f0bbd1935433)。

# 三、代码

```cpp
#include <iostream>
#include <cstring>
#include <algorithm> 
using namespace std;

const int NR=10005;

int fa[NR],n;

int getfa(int k)
{
	if(fa[k]==k)
		return k;
	return fa[k]=getfa(fa[k]);
}

void merge(int p,int q)
{
	p=getfa(p);
	q=getfa(q);
	fa[p]=q;
}

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		fa[i]=i;
	for(int i=1;i<=n;i++)
	{
		int p;
		cin>>p;
		merge(i,p);
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		if(getfa(i)==i)
			ans++;
	cout<<ans;
	return 0;
} 
```
**若有错误，欢迎指出！**

---

## 作者：GeChang (赞：0)

# 题解 CF755C 【PolandBall and Forest】

似乎没有人来发~~又臭又长又慢的~~BFS？我就来水一篇qwq

## 1.分析
翻译里的“父亲节点”太误导了，实际题目中是一张**无向图**。。。

首先，由于`n`个点之间只有`n`条边，用邻接表存妥妥的 $\color{RoyalBlue}\text{MLE}$ ，所以我们可以用 `vector` 存图。

其次对于读入数据处理，不用刻意判断重边的情况，因为边的数量本来就不多，对程序效率影响不大。

最后`cnt`和`vis`数组一定要初始化，~~不然会卡一些迷惑的`bug`。~~
## 2.代码
不吸氧`424ms`，吸氧还™`424ms`。。。


```cpp
#include<bits/stdc++.h> //万能头妙啊
#define ll long long //个人习惯
using namespace std;
ll n,x,cnt;
bool vis[100010]; //标记数组
vector<ll> v[100010]; //vector存图
queue<ll> q;
void bfs(ll k) //广搜
{
	vis[k]=true;
	q.push(k); //进队列
	while(!q.empty())
	{
		ll cur=q.front();
		q.pop(); //出队
		for(ll i=0;i<v[cur].size();i++) //遍历与之相连的所有点
		{
			if(vis[v[cur][i]]==true) continue; //走过了就不走了
			vis[v[cur][i]]=true; //标记
			q.push(v[cur][i]); //进队
		}
	}
	return;
}
int main()
{
	cin>>n;
	for(ll i=1;i<=n;i++)
	{
		cin>>x;
		v[x].push_back(i); //建图
		v[i].push_back(x);
	}
	for(ll i=1;i<=n;i++)
	{
		if(vis[i]==true) continue; //统计过了
		bfs(i);
		cnt++; //数目+1
	}
	cout<<cnt<<endl; //输出
	return 0; //结束+求通过qwq
}
```
# 莫抄袭，没了AC记录，空悲切！



---

