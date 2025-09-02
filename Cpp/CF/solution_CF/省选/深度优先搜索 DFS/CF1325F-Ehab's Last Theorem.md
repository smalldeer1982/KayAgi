# Ehab's Last Theorem

## 题目描述

It's the year 5555. You have a graph, and you want to find a long cycle and a huge independent set, just because you can. But for now, let's just stick with finding either.

Given a connected graph with $ n $ vertices, you can choose to either:

- find an independent set that has exactly $ \lceil\sqrt{n}\rceil $ vertices.
- find a simple cycle of length at least $ \lceil\sqrt{n}\rceil $ .

An independent set is a set of vertices such that no two of them are connected by an edge. A simple cycle is a cycle that doesn't contain any vertex twice. I have a proof you can always solve one of these problems, but it's too long to fit this margin.

## 说明/提示

In the first sample:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1325F/b2563676204e09f52f20c511c849060f592c7e8a.png)

Notice that you can solve either problem, so printing the cycle $ 2-4-3-1-5-6 $ is also acceptable.

In the second sample:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1325F/c06ff7a9bc5850c43035cd15934018ee7a539903.png)

Notice that if there are multiple answers you can print any, so printing the cycle $ 2-5-6 $ , for example, is acceptable.

In the third sample:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1325F/e5b84e0ab62337c524394523ccb0de61f016a191.png)

## 样例 #1

### 输入

```
6 6
1 3
3 4
4 2
2 6
5 6
5 1```

### 输出

```
1
1 6 4```

## 样例 #2

### 输入

```
6 8
1 3
3 4
4 2
2 6
5 6
5 1
1 4
2 5```

### 输出

```
2
4
1 5 2 4```

## 样例 #3

### 输入

```
5 4
1 2
1 3
2 4
2 5```

### 输出

```
1
3 4 5```

# 题解

## 作者：Vision271 (赞：22)

### 本篇题解对解的存在性给出了严谨而完整的证明。

* 其他几篇题解大都跳过了关键步骤，所以我只好假定他们在跳过的步骤中使用了成立的证明...更不要提一些有逻辑错误的。。

* 下面是正文。

### 约定
* 定义 $sq=\lceil\sqrt{n}\rceil$。

### 简单环构造
* 首先原图保证连通、无重边、无自环。这很重要。

* 考虑建出 dfs 树，无向图下非树边显然是返祖边。

* **因为无重边，所以任意 $1$ 条返祖边一定构成一个大小至少为 $3$ 的简单环。推广可得，存在任意 $x$ 条返祖边则一定存在一个大小至少为 $x+2$ 的简单环。**

* 所以我们先在 dfs 树上尝试构造简单环。显然用栈或者深度记录一下很容易求得。

* 如果不成立，那么进行独立集构造。

### 独立集构造
* 既然不存在简单环，则不存在任意一个点有 $sq-2$ 条返祖边。换言之一个点最多有 $sq-3$ 条非树边。

* 取 dfs 树的随便一个叶节点来考察，容易证明将它拿走只会使总点数减少 $sq-3+1+1$（非树边、自己、父亲）$=sq-1=\lceil\sqrt{n}\rceil-1\leqslant \lfloor\sqrt{n}\rfloor$。

* 继续考虑取走这个点及与其相连的点之后的 dfs 树。

* 此时它可能不连通但我们无所谓，转而找一个深度最大的点。

* 容易证明该节点在当前的 dfs 树上一定没有儿子，可能有父亲，可能还有至多 $sq-3$ 条非树边，加在一起还是 $sq-3+1+1=sq-1=\lceil\sqrt{n}\rceil-1\leqslant \lfloor\sqrt{n}\rfloor$ 个点。

* 显然，上面的过程可以反复至少 $\lfloor\sqrt{n}\rfloor^2\leqslant n$ 次。
	* 如果取等，那么 $\lfloor\sqrt{n}\rfloor=\lceil\sqrt{n}\rceil$，从而我们已经取够题目要求的点数了。
    
   * 如果是 $<$，则一定至少还有 $1$ 个点，将它取上我们有 $\lfloor\sqrt{n}\rfloor+1 \geqslant \lceil\sqrt{n}\rceil$ 个点。
   
   * 从而我们给出了一种一定合法的构造方案。

### 对几种较容易想到的伪证的证伪
* 本部分无法举出反例，因为反例本来就不存在。

* 也请不要说这些证伪违背实际——解本来就是一定存在的，这里只能从这些伪证的错误假设/过弱的条件出发在形式逻辑和数学上证伪它们。

* 顺着 @ybwowen 的题解中的证明补一个看似很对的推导过程：
	* “每个节点最多只会有 $sq-2$ 个非树边，故每取一个点，只会使点数减少 $\lceil\sqrt{n}\rceil-1\leqslant \lfloor\sqrt{n}\rfloor$ 个，从而至少能取 $\lceil\sqrt{n}\rceil$ 次，即存在一个 $\lceil\sqrt{n}\rceil$ 的独立集。”
    
	* 错误。被取走的点可能有儿子节点与之相连，且一定有父节点与之相连，取一次的点数减少量下界为 $\lceil\sqrt{n}\rceil$，上界为 $n$。
    
   * 顺便一提，（我认为）每个点最多有 $sq-2$ 条非树边这一中间结论不够强，推不出结论（毕竟我是把它卡到了 $sq-3$ 才得证的，他的这个中间结论不够 specific，在放少量的互不相交的重边的图下依然成立...）。
   
   * 如果有什么能从 $sq-2$ 直接推出结论的方式请踹我一下，将我招魂过来~~膜拜~~学习。

* 顺着 @QwQcOrZ 的题解的证明：
	* “但是根据鸽巢原理...”（请自行参阅上下文。特别地，因为我实在不理解“独立集非法”是指独立集不独立还是指独立集不够大，所以我师心自用地从上下文认为是不够大）
	
   * 我认为这个是伪证。由（对应题解的）上文，我们此时构造出了一个 $< \lceil\sqrt{n}\rceil$ 的独立集，该独立集不能进一步扩大，但我认为这不能说明这个独立集中一定有至少一个点的度数 $d\geqslant \lceil\sqrt{n}\rceil-1$。
   
   * 这里鸽巢原理的运用，至少在我看来是指：
       * 如果独立集中的所有 $sq-1$ 个点都满足 $d<sq-1$（用一下我的符号不好意思），则每个点连同他自己和度数占用了至多 $sq$ 个点，从而 $\geqslant \lceil\sqrt{n}\rceil$ 的独立集一定存在，因为 $(sq-1)\times sq<n $。
       
     	* 但这显然不成立，譬如我们可以取 $n=5$，从而 $sq=3$。
        
       * 如果没有取整符号就成立。
   
   * 可能显得有点钻牛角尖，毕竟对应结论实际上在题设下成立，但对应题解似乎、并没有援引对应题设作为条件来说明这里一定成立（其实我也不知道怎么从题设出发证明这里鸽巢原理用对了...）。
   
* @MikukuOvO：
	* 我认为其中的 $\sqrt{n}$ 应为 $\lceil\sqrt{n}\rceil$。。
    
   * 从而这和 ybwowen 的思路同构，也是只卡到了 $sq-2$。
       * 其中的“父边”没有定义，我不知道算不算树上父子之间的边，如果算上他就卡对了。（$sq-2$ 条边就是一条与父亲的和 $sq-3$ 条非树返祖边）
       * 不过就算算了他还是错的，看下一条。
   
   * 而且逻辑错误，由“有 $\sqrt{n}-2$ 条父边”推出了“如果选择一个点，最多会有 $\sqrt{n}-2$ 个点无法选择”。没有考虑这个点本身。

* @Clever_Jimmy：
	* 前面基本没有在证明。看关键的“乱口胡”前面。
    
   * 因为找不到满足题意的环，等价于每个点最多连向 $q-1$ 个点，则最后一定会有大于等于 $q$ 个点（他的 $q$ 就是我的 $sq$）。
   
   * 这个“等价”是错的，对这个我甚至能举反例：菊花图。

* @ZCPB：
	* 首先这和 ybwowen 的思路同构，也只卡到了 $sq-2$。
    
   * 然后卡错了！
   
   * “对于每个点，最多与它 $\left\lceil\sqrt n\right\rceil-2$ 个祖先连边，所以，当它被选择时，最多有 $\left\lceil\sqrt n\right\rceil-2$ 个点不能选。”
   
   * 这个我们在 MikukuOvO 那里见过了，又是没有考虑本身。
   
   * 更不要提儿子的问题...我们姑且认为这里的意思是一直在拿当前叶节点吧，那就没有儿子了。
   
   * 相对的，ybwowen 的题解里把这一步跳过了，所以我只能假设他是对的。
   
* @万弘：
	* 和 ZCPB 错的一模一样，首先是和 ybwowen 同构没有卡到 $sq-3$ 条返祖边。
    
   * 当然，如果父向边包括树上那条父子边，那么卡对了。
   
   * “每个点至多有 $lim-2$ 条父向边 $\rightarrow$ 选择一个点至多导致 $lim-2$ 个点无法选择”
   
   * 好吧，这又是个没考虑那个点本身的。
   
* 为什么没有 huayucaiji？...对方认为这是小学奥数。

* 如果冒犯了，致歉。

---

## 作者：ybwowen (赞：10)

这题是一道练习dfs tree的好题目。

如果你不熟悉dfs tree的话，建议看一下CF上的[这篇博客](https://codeforces.ml/blog/entry/68138)：

这里我稍微提一下

我们可以通过一遍dfs来寻找这个图的一颗生成树。这时，所有边都可以被分为**树边**和**非树边**。 

![](https://cdn.luogu.com.cn/upload/image_hosting/z2vhimvq.png)

在这张图里面，粗的边就是树边，细的边就是非树边。

这里我们就要用到dfs树一个及其重要的性质：

> **一条非树边连接了一个点和它在生成树中的一个后代**

证明：假设我们有一条边$(u,v)$，并且现在我们dfs到了$u$。

1.如果$v$没有被访问，那么$(u,v)$就是一条树边

2.如果$v$已经被访问了，就说明要么$v$是$u$的祖先，要么$v$在$u$的一个儿子的一个子树中（因为$v$已经被访问了），也就是说$v$是$u$的后代。

证毕。

所以这题我们就可以这么干：

令$sq=\lceil \sqrt{n}\rceil$

我们先找到一个dfs tree，标记节点的深度。如果一条非树边连接的两个点的深度的差大于等于$sq-1$，那么我们已经找到一个环了，就输出它。

如果所有的非树边都不满足上个条件的话，那么每个节点最多只会有$sq-2$个非树边（因为如果有$sq-1$个的话，根据我们刚刚证明的结论，两点之间深度差至少为$sq-1$），于是我们肯定能找到一个含有$sq$个节点的点最大独立集。

具体实现代码的时候，我们不必dfs完再去找非树边，我们可以边dfs的时候就去找非树边，这样方便输出。详情见代码（~~千万不要像我一样开小空间调好久~~）：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int n,m;
namespace Graph{
	struct Node{
		int from;
		int to;
		int next;
	}edge[maxn<<1]; 
	int head[maxn],cnt=1;
	inline void add(int x,int y){
		edge[++cnt].next=head[x];
		edge[cnt].from=x;
		edge[cnt].to=y;
		head[x]=cnt;
	}
}
using namespace Graph;
int v[maxn];
int tag[maxn];
int dep[maxn];
int sq;
vector<int>ans;
vector<int>vec;
inline void dfs(int x){
	vec.push_back(x); 
	dep[x]=vec.size();
	for(int i=head[x];i!=0;i=edge[i].next){
		int k=edge[i].to;
		if(!dep[k]) dfs(k);
		else if(dep[x]-dep[k]>=sq-1){
			printf("2\n");
			printf("%d\n",dep[x]-dep[k]+1);
			for(int i=dep[k]-1;i<dep[x];i++) printf("%d ",vec[i]);
			printf("\n"); exit(0);
		}
	}
	if(!tag[x]){
		ans.push_back(x);
		for(int i=head[x];i!=0;i=edge[i].next){
			int k=edge[i].to;
			tag[k]=1;
		}
	} 
	vec.pop_back();
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int x,y; scanf("%d%d",&x,&y);
		add(x,y); add(y,x);
	}
	sq=sqrt(n-1)+1;
	dfs(1);
	printf("1\n");
	for(int i=0;i<sq;i++) printf("%d ",ans[i]);
	printf("\n"); 
	return 0;
}
```


---

## 作者：QwQcOrZ (赞：8)

提供一个不需要 dfs 生成树的新做法。

考虑构造独立集，每次选出一个度数最小的点（记其度数为 $d$），将这个点加入独立集中，删去这个点以及与这个点相邻的点，重复此过程直至图为空。

显然这样构造出的独立集的大小可能小于 $\lceil\sqrt n\rceil$。

但是根据鸽巢原理，独立集非法时选出的点中一定有至少一个的 $d\geq\lceil\sqrt n\rceil-1$，否则可以构造出合法的独立集。

那么在 $d\geq\lceil\sqrt n\rceil-1$ 时，剩下的图中每个点的度数都 $\geq\lceil\sqrt n\rceil-1$。

有引理：一张 $n$ 个点的无向简单图，若每个点的度数都不小于 $k-1$，那么这张图一定存在一个长度不小于 $k$ 的环。

也就是说，在执行构造独立集的过程中，若当前 $d\geq\lceil\sqrt n\rceil-1$，则可以用剩下的图构造出一个合法的环，否则一定可以构造出一个合法的独立集。

那么剩下的问题就是如何构造一个合法的环，如果存在构造方法那么显然引理也得到了证明。

考虑从图中的任意一个点开始遍历，每次走向一个相邻的没有遍历过的点，直到当前点每个相邻的点都被遍历为止。

这样可以拉出来一条链，显然最后一个点所有相邻的点都在链中。

记链上最后一个点为 $u$，$u$ 相邻点中离它链上距离最远的点为 $v$。

由于每个点的度数都不小于 $\lceil\sqrt n\rceil-1$，而且图中没有重边，所以 $u$ 到 $v$ 的这段链上的点数显然至少有 $\lceil\sqrt n\rceil$ 个。

那么直接把这段链上的点抠出来组成的环就能得到一个合法的环。

$\text{Code Below}$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;

int read()
{
	int s=0;
	char c=getchar(),lc='+';
	while (c<'0'||'9'<c) lc=c,c=getchar();
	while ('0'<=c&&c<='9') s=s*10+c-'0',c=getchar();
	return lc=='-'?-s:s;
}
void write(int x)
{
	if (x<0) putchar('-'),x=-x;
	if (x<10) putchar(x+'0');
	else write(x/10),putchar(x%10+'0');
}
void print(int x,char c='\n')
{
	write(x);
	putchar(c);
}
vector<int>e[N],a;
int siz[N],id[N],cnt=0,k;
bool vis[N];
priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>q;
void dfs(int now)
{
	vis[now]=1;
	id[now]=++cnt;
	a.push_back(now);
	for (int to:e[now])
	if (!vis[to]) return dfs(to);
	else if (id[to]&&cnt-id[to]+1>=k) return;
}
void solve(int n)
{
	for (int i=1;i<=n;i++) if (!vis[i]){dfs(i);break;}
	int mn=n,flag=0;
	for (int to:e[a.back()]) if (id[to]) mn=min(mn,id[to]);
	vector<int>ans;
	for (int i:a)
	{
		if (id[i]==mn) flag=1;
		if (flag) ans.push_back(i);
	}
	puts("2");
	print(ans.size());
	for (int i:ans) print(i,' ');
}

signed main(signed bangumi,char *ss1672[])
{
	(void)bangumi,(void)ss1672;
	int n=read(),m=read(); k=ceil(sqrt(n));
	for (int i=1;i<=m;i++)
	{
		int u=read(),v=read();
		e[u].push_back(v);
		e[v].push_back(u);
		siz[u]++,siz[v]++;
	}
	vector<int>ans;
	for (int i=1;i<=n;i++) q.push(make_pair(siz[i],i));
	while ((int)ans.size()<k)
	{
		int now=q.top().second; q.pop();
		if (vis[now]) continue;
		if (siz[now]>=k-1) return solve(n),0;
		vis[now]=1;
		ans.push_back(now);
		for (int to:e[now])
		if (!vis[to])
		{
			vis[to]=1;
			for (int i:e[to]) if (!vis[i]) q.push(make_pair(--siz[i],i));
		}
	}
	puts("1");
	for (int i:ans) print(i,' ');
	
	return 0;
}
```





---

## 作者：Purslane (赞：4)

# Solution

感觉题解区的老哥好猛。那我就不自量力的写个题解，大家看看伪没伪？

首先，我们生成任何一棵 DFS 树。

如果有一条**返祖边**它的跨度在 $\lceil \sqrt n \rceil-1$ 及以上，我们必定能找到一个至少为 $\lceil \sqrt n \rceil$ 的环。

否则，所有返祖边的跨度都小于等于 $\lceil \sqrt n \rceil-2$。如果没有重边，一个点最多有 $\lceil \sqrt n \rceil-2$ 条指向父亲或者指向祖先的边。

那么考虑在 DFS 树上进行后序遍历（好几年了，终于又一次用上了这个词汇）。如果一个点没有后代被放入独立集中，我们就把这个点放入独立集中。

考虑这样我们至少能找到 $\lceil \sqrt n \rceil$ 个点。否则，假设我们只找到了 $\lceil \sqrt n \rceil-1$ 个点。每个点最多导致 $\lceil \sqrt n \rceil-2$ 个点不能选。因此我们总点数应该有 $n \le (\lceil \sqrt n \rceil-1)^2$。然而 $(\lceil \sqrt n \rceil-1)^2<n$（假设 $\sqrt n$ 是整数，这个不等式成立；假设不是整数，这个不等式亦成立），就矛盾了。

所以何必那么吹毛求疵找别人的小错误呢？

~~根据个人观察，CMO 2023 好像如果你有一点小错误导致这道题寄了，就算你特别接近满分解法都只有 $6$ 分封顶。~~

代码略。

---

## 作者：huayucaiji (赞：2)

最后一道题，很有质量，是一道好的图论题。

我们定义 $sq=\lceil \sqrt n\rceil$。我们把原题中样例2的图搬过来作为举例：

![F](http://image.qingtengbc.com/2020/03/18/4d02aaca97fdd.png)

首先，我们随便以一个点作为起点进行 DFS。我们以1位起点。那么，我把DFS中经过过的边（也就是DFS树），边权为 $1$，其他为 $0$。那么原图就变成了这个样子：

![F2](http://image.qingtengbc.com/2020/03/19/56979c11e7fc4.png)

我们发现，由 $1$ 边构成的图是一棵树，虽然这个性质对我们的解题毫无用处，但这个DFS树真的是没什么用，了解就好，他对我们的思路启发是有一点作用的。我们继续讲题，现在，如果在DFS时，我们从 $u$ 出发，找到了一个点 $v$，如果之前 $v$ 已经被搜到过了，而且 $u,v$ 的在DFS树上深度差大于等于 $sq-1$，就可以找到一个长度至少为 $sq$ 的环，就可以回答第二个问题了。如果没有这样的边，那么我们一定可以回答的一个问题，具体证明很简单，这里不再赘述，应该是一个小学奥数的证明吧。


所以我们就可以快乐地写代码啦！

```cpp
//#pragma GCC optimize("Ofast","-funroll-loops","-fdelete-null-pointer-checks")
//#pragma GCC target("ssse3","sse3","sse2","sse","avx2","avx")
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int maxn=1e5+10;

int n,cnt,h[maxn],d[maxn],sq,m;
set<pair<int,int> > s;
vector<int> ans;
bool vis[maxn];

struct edge {
	int v,next;
}e[maxn<<2];

void addedge(int u,int v) {
	e[++cnt].next=h[u];
	e[cnt].v=v;
	h[u]=cnt;
} 

void dfs(int u,int father) {
	d[u]=d[father]+1;
	ans.push_back(u);
	for(int i=h[u];i;i=e[i].next) {
		int v=e[i].v;
		if(!d[v]) {
			dfs(v,u);
		}
		if(d[u]-d[v]+1>=sq) {
			printf("2\n%lld\n",d[u]-d[v]+1);
			for(int i=d[v]-1;i<d[u];i++) {
				cout<<ans[i]<<" ";
			}
			exit(0);
		}
	}
	if(!vis[u]) {
		for(int i=h[u];i;i=e[i].next) {
			vis[e[i].v]=1;
		}
	}
	ans.pop_back();
} 

signed main() {
	
	n=read(),m=read();
	sq=ceil(sqrt(n));
	for(int i=1;i<=m;i++) {
		int a=read(),b=read();
		addedge(a,b);
		addedge(b,a);
	}
	dfs(1,0);
	cout<<1<<endl;
	int tot=1;
	for(int i=1;tot<=sq;++i)  {
		if(!vis[i]) {
			printf("%d ", i);
			tot++;
		}
	}
	return 0;
}

```
#### *UPD1:感谢 @ dezhonger 指出图片错误*

---

## 作者：MikukuOvO (赞：1)

首先对于第一个问题，我们只要$dfs$出一棵树，然后判断是否存在一条非树边连接的两个点深度差$\ge \sqrt{n}-1$即可。

这里就有一个有趣的事情，如果找不到满足第一个问题的环，那么一定存在一个$\ge \sqrt{n}$的独立点集。

考虑没有重边，由于不存在一条非树边连接的两个点深度差$\ge \sqrt{n}-1$，那么一个点至多有$\sqrt{n}-2$条父边，也就是如果选择一个点，最多会有$\sqrt{n}-2$个点无法选择，不难得到一定存在一个$\ge \sqrt{n}$的独立点集。

关于找独立点集我们染个色就好了。

[$code$](https://pastebin.com/w1wGKTJ9)

---

## 作者：Clever_Jimmy (赞：1)

#### F. Ehab's Last Theorem [题目链接](https://codeforces.ml/contest/1325/problem/F)

不妨设 $q = \lceil\sqrt{n}\rceil$。

首先跑出任意一个 dfs 树，对于树中的某个点 $u$：

如果它有大于等于 $q$ 个前向边，那么就 **一定** 能找到一个长度大于等于 $q$ 的环。

否则，将它放到最大独立集中，并将它的所有邻点打上标记（表示不能取）。

如果能满足任务 $2$，找到了方案要直接 `exit(0)`，否则会 TLE。

最后没有被打标记的点即为最大独立集中的点（只能输出 **恰好** $q$ 个）。

为什么没有找不到长度大于等于 $q$ 的环一定会有最大独立集的大小大于等于 $q$？

因为找不到满足题意的环，等价于每个点最多连向 $q - 1$ 个点，则最后一定会有大于等于 $q$ 个点。（乱口胡）

[code](https://codeforces.ml/contest/1325/submission/73311347)

---

## 作者：ZeroOf149 (赞：0)

# [CF1325F Ehab's Last Theorem](https://www.luogu.com.cn/problem/CF1325F)

## 题目描述

给一个无向简单连通图 $G$，点数为 $n$。记 $S = \lceil\sqrt{n}\rceil$，找到以下两者之一：
  1. $G$ 中大小**正好**为 $S$ 的独立集；
  2. $G$ 中大小至少为 $S$ 的简单环，**并按顺序给出**。

$5 \leq n \leq 10^5, n-1 \leq m \leq 2 \times 10^5$。

## 解法说明

首先，如果 $G$ 只是一棵树，那么我们只需将其 2- 染色，就可找到一个大小至少为 $\lceil\dfrac{n}{2}\rceil$ 的独立集。由于 $\lceil\dfrac{n}{2}\rceil\geq S$，所以这种构造是可行的。

当 $G$ 不是树的时候，仿照上面的方法，我们考察 $G$ 的 dfs 生成树，由于非树边只会是返祖边，我们就可以分两种情况构造：
  - 存在两端深度差大于等于 $S - 1$ 的非树边，那么显然有大小至少为 $S$ 的简单环；
  - 上面这种边不存在，那么将所有节点按照深度模 $(S-1)$ 的值染色，由于所有非树边两端深度差小于 $S-1$，所以同色节点之间没有连边。若取被染了最多次的颜色，根据鸽巢原理，这个次数至少是 $\lceil\dfrac{n}{S-1}\rceil>\lceil\dfrac{n}{\sqrt{n}}\rceil=\lceil\sqrt{n}\rceil=S$，这意味着我们找到了大小至少为 $S$ 的独立集。

然后就做完了。时间复杂度 $\Theta(n)$。

## [代码实现](https://codeforces.com/contest/1325/submission/320732234)

```cpp
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>

constexpr int N = 1e5 + 5;

int n, m, sq, fth[N], dep[N];
std::vector<int> g[N], ans[N];

void output_cycle(int u, int v) {
  if (dep[u] < dep[v]) std::swap(u, v);
  printf("2\n%d\n", dep[u] - dep[v] + 1);
  while (u != v) {
    printf("%d ", u);
    u = fth[u];
  }
  printf("%d\n", v);
  exit(0);
}

void dfs(int u, int f) {
  dep[u] = dep[f] + 1;
  fth[u] = f;
  ans[dep[u] % (sq - 1)].push_back(u);
  for (auto&& v : g[u]) {
    if (v == f) continue;
    if (dep[v]) {
      if (dep[u] - dep[v] + 1 >= sq) output_cycle(u, v);
      continue;
    }
    dfs(v, u);
  }
}

int main() {
  scanf("%d %d", &n, &m);
  sq = (int)std::ceil(std::sqrt(n));
  for (int i = 1; i <= m; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs(1, 0);
  puts("1");
  for (int r = 0; r < sq - 1; ++r)
    if ((int)ans[r].size() >= sq) {
      for (int i = 0; i < sq; ++i) printf("%d ", ans[r][i]);
      break;
    }
}
```

---

## 作者：ka_da_Duck (赞：0)

[CF1325F Ehab's Last Theorem](https://www.luogu.com.cn/problem/CF1325F)
-

题意
-

给定一个 $n$ 个点，$m$ 条边的无向图。让你找出一个至少有 $\lceil\sqrt n\rceil$ 个点的环 **或** 正好有 $\lceil\sqrt n\rceil$ 个点的独立集。

解析
-

1. 构造环

    考虑将原图放到 DFS 树上考虑，在 DFS 树上记录每个点的深度 $\text{dep}$ 值，如果一条非树边连接的两个点 $u，v$，使得 $dep_u-dep_v+1\ge \lceil\sqrt n\rceil$，则我们在原图找到了一个至少有 $\lceil\sqrt n\rceil$ 个点的环。

    结论显而易见嘛，在树边上 u，v 这条链上至少有 $dep_u-dep_v+1$ 个节点，又因为有返祖边就形成了环。

2. 构造独立集

   如果用上述方法找不到满足条件的环，我们就只能考虑构造独立集，根据第一问的结论，运用反证法，我们就可以得到结论：

> 如果图上不存在一个至少有 $\lceil\sqrt n\rceil$ 个点的环，那么最多存在一个至少有 $\lceil\sqrt n\rceil-2$ 个点的环，即图上每个节点至多只存在 $\lceil\sqrt n\rceil-3$ 条返祖边。

  证明很简单，假设有节点存在 $\lceil\sqrt n\rceil-1$ 条返祖边，那么必然有一条返祖边所连接的点与自己就会形成一个至少有 $\lceil\sqrt n\rceil$ 个点的环，矛盾。

接下来我们就可以构造独立集了，每次我们可以选择一个节点放入独立集，并将与该点相连接的点删除，重复此操作 $\lceil\sqrt n\rceil$ 次，我们就可以得到一个 $\lceil\sqrt n\rceil$ 个点的独立集了。

这时候可能会有人有疑惑：为什么你能保证一定可以重复 $\lceil\sqrt n\rceil$ 此操作呢？

 根据上面的结论，一个节点最多只有 $\lceil\sqrt n\rceil-3$ 条返祖边，再算上该节点的父亲和自己本身，每次操作最多只会删除 $\lceil\sqrt n\rceil-1$ 个节点，所以前 $\lceil\sqrt n\rceil-1$ 次操作最多只会删除 $(\lceil\sqrt n\rceil-1)\times(\lceil\sqrt n\rceil-1)\le n$ 各节点，所以一定删不完,所以最后还能再取一次，所以能取 $\lceil\sqrt n\rceil$ 次。

做到这里整道题目就做完了，总结一下，能构造出第二问的充分条件就是构造不出第一问。

最后附上代码：

```cpp
#include <bits/stdc++.h>

using namespace std;
const int maxn = 2e5 + 10;

int n, m, k;
int dep[maxn];
bool vis[maxn];
vector<int> e[maxn], ans, st;

void dfs(int u, int fa) {
	dep[u] = dep[fa] + 1;
	st.push_back(u);
	for (auto v: e[u]) {
		if (!dep[v]) dfs(v, u);
		if (dep[u] - dep[v] + 1 >= k) {
			cout << 2 << '\n' << dep[u] - dep[v] + 1 << '\n';
			for (int i = dep[v]; i <= dep[u]; ++i) cout << st[i - 1] << ' ';
			exit(0);
		}
	}
	if (!vis[u]) {
		ans.push_back(u);
		for (auto v: e[u]) vis[v] = 1;
	}
	st.pop_back();
}

signed main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >> n >> m;
	k = sqrt(n - 1) + 1;
	for (int i = 1, u, v; i <= m; ++i) {
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1, 0);
	cout << 1 << '\n';
	for (int i = 1; i <= k; ++i) cout << ans[i - 1] << ' ';
}

```

---

## 作者：Ericby666 (赞：0)

题意：给出一个 $n$ 个点，$m$ 条边的无向图。需要找出一个**至少**有 $\left\lceil\sqrt n\right\rceil$ 个点的环**或**一个**正好有** $\left\lceil\sqrt n\right\rceil$ 个点的独立集。

第一步，先判断是否可以构造出至少有 $\left\lceil\sqrt n\right\rceil$ 个点的环。

将原图放在 dfs 树上考虑，在 dfs 树上记录节点的深度 dep。如果节点 $u$ 的一条返祖边连向节点 $v$，使得 $dep_u-dep_v+1\ge\left\lceil\sqrt n\right\rceil$，那就已经找到了一个至少有 $\left\lceil\sqrt n\right\rceil$ 个点的环。

这个结论很好证明，因为从节点 $u$ 到节点 $v$ 的这条链有 $dep_u-dep_v+1$ 个节点，且 $dep_u-dep_v+1\ge\left\lceil\sqrt n\right\rceil$，所以从节点 $u$ 到节点 $v$ 的这条链上至少有 $\left\lceil\sqrt n\right\rceil$ 个节点。又因为节点 $u$ 和节点 $v$ 之间有一条返祖边，所以形成了一个环，于是此时已经出现了一个至少有 $\left\lceil\sqrt n\right\rceil$ 个点的环了。

第二步，如果无法构造出一个至少有 $\left\lceil\sqrt n\right\rceil$ 个点的环，那就尝试构造一个正好有 $\left\lceil\sqrt n\right\rceil$ 个点的独立集。

由于不存在至少有 $\left\lceil\sqrt n\right\rceil$ 个点的环，所以每个环最多有 $\left\lceil\sqrt n\right\rceil-1$ 个点，除去每个节点和它的父亲节点，每个节点最多有 $\left\lceil\sqrt n\right\rceil-3$ 条返祖边。

构造独立集时，可以每次选中一个点，然后删除这个节点、这个节点的父亲和所有这个节点的返祖边连向的节点。

之前我们已经证明过一个节点最多有 $\left\lceil\sqrt n\right\rceil-3$ 条返祖边，再算上这个节点自己和它的父亲，每次操作最多可以删除 $\left\lceil\sqrt n\right\rceil-1$ 个节点。

这时我们可以使用反证法来证明一定可以构造出正好有 $\left\lceil\sqrt n\right\rceil$ 个点的独立集。

证明：假设无法构造出一个正好有 $\left\lceil\sqrt n\right\rceil$ 个点的独立集，即最多构造出一个有 $\left\lceil\sqrt n\right\rceil-1$ 个点的独立集。由于每次操作最多删除 $\left\lceil\sqrt n\right\rceil-1$ 个节点，所以构造出一个有 $\left\lceil\sqrt n\right\rceil-1$ 个点的独立集最多需要删除 $\left\lceil\sqrt n\right\rceil-1\times\left\lceil\sqrt n\right\rceil-1=\left\lceil\sqrt n\right\rceil^2-2\left\lceil\sqrt n\right\rceil+1$ 个节点。显然，$\left\lceil\sqrt n\right\rceil^2-2\left\lceil\sqrt n\right\rceil+1<n$，所以此时还能至少再进行一次操作，所以一定能构造出一个正好有 $\left\lceil\sqrt n\right\rceil$ 个点的独立集。证毕。

所以到了最后，我们可以总结出：只要构造不出一个至少有 $\left\lceil\sqrt n\right\rceil$ 个点的环，就一定能构造出一个正好有 $\left\lceil\sqrt n\right\rceil$ 个点的独立集。也就是说，无法构造一个至少有 $\left\lceil\sqrt n\right\rceil$ 的环是构造出一个正好有 $\left\lceil\sqrt n\right\rceil$ 个点的独立集的**充分条件**。

AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,sq,u,v,cnt,head[100005],a[100005],tot,dep[100005],b[100005],cul;
bool vis[100005];
struct node{
	int nxt,to;
}e[400005];
void add(int u,int v){
	e[++cnt]={head[u],v};
	head[u]=cnt;
}
void dfs(int u){
	a[++tot]=u;
	dep[u]=tot;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!dep[v])dfs(v);
		else if(dep[u]-dep[v]>=sq-1){
			cout<<"2\n";
			cout<<dep[u]-dep[v]+1<<'\n';
			for(int i=dep[v];i<=dep[u];i++)cout<<a[i]<<' ';
			exit(0);
		}
	}
	if(!vis[u]){
		b[++cul]=u;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			vis[v]=1;
		}
	}
	tot--;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	sq=sqrt(n-1)+1;
	for(int i=1;i<=m;i++){
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	dfs(1);
	cout<<"1\n";
	for(int i=1;i<=sq;i++)cout<<b[i]<<' ';
	return 0;
}
```

---

## 作者：万弘 (赞：0)

upd at 11/1 : 感谢 @do_while_true 指出了一个错误，已修复。

题意：给一个 $ n $ 个点的无向图（无重边、自环），要找出包含不少于 $ \lceil \sqrt n\rceil  $ 个点的简单环或独立集。  

 $ n\le 10^5,m\le 2\times 10^5 $ 
此题其实暗示一个性质：如果无向图中不存在不少于 $ \lceil \sqrt n\rceil  $ 个点的简单环，则必然存在不少于 $ \lceil \sqrt n\rceil  $ 个点的独立集。  

证明的过程也就是求解的过程。设 $ lim=\lceil \sqrt n\rceil $ 

考虑找出一个搜索树（类似`tarjan`算法的搜索树）。原图中的每个环必然包含一条父向边。在考虑点 $ u $ 的可达点 $ v $ 的时候,如果 $ v $ 没有被访问过就访问 $ v $ ,否则如果 $ v $ 是 $ u $ 的祖先，并且他们之间形成的环（包含的点数是距离+1）不少于 $ lim $ 个点，那么就是一种可行的答案。


接下来证明若无法找到，则必然存在不少于 $ lim $ 个点的独立集：

引理：这种情况下每个点至多有 $ lim-2 $ 条父向边。

证明：反证。假设某个点有超过 $ lim-2 $ 条父向边，由于图中无重边，则必然形成一个大小超过 $ lim $ 的环，与已知矛盾。证毕。

每个点至多有 $ lim-2 $ 条父向边 $ \rightarrow $ 选择一个点至多导致 $ lim-2 $ 个点无法选择 $ \rightarrow $  至少可以选出大小为 $ \lfloor n/(lim-1)\rfloor  $ 的独立集。原命题证毕。  

时间复杂度 $ \mathcal O(n+m) $ 

```cpp
#define MAXN 200011
struct Edge
{
    ll v,nxt;
}e[MAXN<<1|1];
ll cnt=0,last[MAXN];
void adde(ll u,ll v)
{
    e[++cnt].v=v;
    e[cnt].nxt=last[u],last[u]=cnt;
}

ll s[MAXN],top=0,dep[MAXN],lim,tag[MAXN];
void dfs(ll u,ll now_dep=1,ll fa=0)
{
    s[++top]=u;dep[u]=now_dep;
    for(ll i=last[u];i;i=e[i].nxt)
    {
        ll v=e[i].v;
        if(v==fa)continue;
        if(!dep[v])dfs(v,now_dep+1,u);
        else if(dep[u]-dep[v]+1>=lim)
        {
            printf("2\n%lld\n",dep[u]-dep[v]+1);
            for(ll p=dep[u]-dep[v]+1;p;--p)printf("%lld ",s[top--]);
            exit(0);
        }
    }
    if(!tag[u])
    {
        for (ll i = last[u]; i ; i=e[i].nxt)
            tag[e[i].v]=1;
    }
    --top;
}
int main()
{
    ll n=read(),m=read();
    lim=sqrt(n);
    if(lim*lim<n)++lim;
    for(ll i=1;i<=m;++i)
    {
        ll u=read(),v=read();
        adde(u,v),adde(v,u);
    }
    dfs(1);
    puts("1");
    ll u=1;
    while(lim)
    {
        while(tag[u])++u;
        printf("%lld ",u);
        ++u;
        --lim;
    }
    return 0;
}
```

---

