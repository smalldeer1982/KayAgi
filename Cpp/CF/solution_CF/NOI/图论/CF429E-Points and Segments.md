# Points and Segments

## 题目描述

Iahub isn't well prepared on geometry problems, but he heard that this year there will be a lot of geometry problems on the IOI selection camp. Scared, Iahub locked himself in the basement and started thinking of new problems of this kind. One of them is the following.

Iahub wants to draw $ n $ distinct segments $ [l_{i},r_{i}] $ on the $ OX $ axis. He can draw each segment with either red or blue. The drawing is good if and only if the following requirement is met: for each point $ x $ of the $ OX $ axis consider all the segments that contains point $ x $ ; suppose, that $ r_{x} $ red segments and $ b_{x} $ blue segments contain point $ x $ ; for each point $ x $ inequality $ |r_{x}-b_{x}|<=1 $ must be satisfied.

A segment $ [l,r] $ contains a point $ x $ if and only if $ l<=x<=r $ .

Iahub gives you the starting and ending points of all the segments. You have to find any good drawing for him.

## 样例 #1

### 输入

```
2
0 2
2 3
```

### 输出

```
0 1
```

## 样例 #2

### 输入

```
6
1 5
1 3
3 5
2 10
11 11
12 12
```

### 输出

```
0 1 0 1 0 0
```

# 题解

## 作者：ywy_c_asm (赞：16)

（虽然不知道另一篇题解在说什么但是感觉应该和这个本质相同……吧

哦先说一下我最开始的垃圾做法：先把坐标离散化，然后对离散化之后的一段会有一个覆盖次数$cnt$，那么这一段被覆盖的红色（或者蓝色）最多会有$\lceil\frac {cnt}2\rceil$个，最少有$\lfloor\frac{cnt}2\rfloor$个，那么就是一个经典的有上下界网络流的模型，$i$向$i+1$连上下界为这个的边，然后对每个区间让$r+1$到$l$连1的边，然后就做完了，~~然而我高估了Dinic的速度T的飞起……~~

其实我们可以这样转化模型就是把红的区间看做-1，蓝的区间看做1，那么每个点必须覆盖成-1，1或者0，其实上面那个网络流的建图已经告诉我们如果一段的cnt为偶数那么一定会被覆盖成0，否则会是1或-1，这样比较麻烦，但是，如果我们往cnt为奇数的段里面强行加一个区间让他强行发挥作用然后这一段也会是0，那就好办了，我要给每个区间确定一个颜色使得覆盖在每个点的红色=蓝色，这是啥呢？我们把离散化后的坐标看做关键点，不妨就让他表示这个连续段，那么**对于每个区间从l向r连一条无向边，要做的就相当于给边定向让入度等于出度**，这不欧拉回路？并且由于每个段的cnt我们都给他强行设为了偶的所以一定是有解的，最终我们看这个区间对应的边定的向是从哪指到哪就能确定颜色了。

上代码~

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
namespace ywy {
	inline int get() {
	    int n = 0;
	    char c;
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            break;
	        if (c == '-')
	            goto s;
	    }
	    n = c - '0';
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 + c - '0';
	        else
	            return (n);
	    }
	s:
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 - c + '0';
	        else
	            return (n);
	    }
	}
	typedef struct _b {
	    int dest;
	    int nxt;
	    int id;
	    unsigned char gg;
	} bian;
	bian memchi[1000001];
	int gn = 2, heads[222222];
	inline void add(int s, int t, int id) {
	    memchi[gn].dest = t;
	    memchi[gn].id = id;
	    memchi[gn].nxt = heads[s];
	    heads[s] = gn;
	    gn++;
	}
	int dss[333333], dts[333333];
	unsigned char bv[333333];
	void dfs(int pt) {
	    bv[pt] = 1;
	    for (register int i = heads[pt]; i; heads[pt] = i = memchi[i].nxt) {
	        if (memchi[i].gg)
	            continue;
	        dss[memchi[i].id] = pt;
	        dts[memchi[i].id] = memchi[i].dest;
	        memchi[i].gg = memchi[i ^ 1].gg = 1;
	        dfs(memchi[i].dest);
	    }
	}
	int lsh[222222];
	int ls[100001], rs[100001], adds[222222], dels[222222], cnt[222222];
	void ywymain() {
	    int n = get();
	    int ptr = 1;
	    for (register int i = 1; i <= n; i++) {
	        ls[i] = lsh[ptr] = get();
	        ptr++;
	        rs[i] = lsh[ptr] = get() + 1;
	        ptr++;
	    }
	    ptr--;
	    sort(lsh + 1, lsh + 1 + ptr);
	    int newl = unique(lsh + 1, lsh + 1 + ptr) - lsh - 1;
	    for (register int i = 1; i <= n; i++) {
	        ls[i] = lower_bound(lsh + 1, lsh + 1 + newl, ls[i]) - lsh;
	        rs[i] = lower_bound(lsh + 1, lsh + 1 + newl, rs[i]) - lsh;
	        add(ls[i], rs[i], i);
	        add(rs[i], ls[i], i);
	        adds[ls[i]]++;
	        dels[rs[i]]++;
	    }
	    for (register int i = 1; i <= newl; i++) {
	        cnt[i] = cnt[i - 1] + adds[i] - dels[i];
	        if (cnt[i] & 1) {
	            add(i, i + 1, n + 1);
	            add(i + 1, i, n + 1);
	        }
	    }
	    for (register int i = 1; i <= newl; i++) {
	        if (bv[i])
	            continue;
	        dfs(i);
	    }
	    for (register int i = 1; i <= n; i++) {
	        if (dss[i] > dts[i])
	            printf("1 ");
	        else
	            printf("0 ");
	    }
	}
}
int main() {
    ywy::ywymain();
    return (0);
}
```

---

## 作者：frankchenfu (赞：16)

这是一道图论题。表面上不容易看出来，因为这道题目需要我们用到转化的思想。接下来我们考虑如何将它转化成一个图论模型。

------------

我们首先猜测如何建模。

题目要求每一个点被覆盖的线段中，红色的和蓝色的线段数量差不超过$1$，所以我们把红色边看成是$1$，蓝色边看成是$-1$，每条线段的权值是$p_i(p_i=1/-1)$，那么问题就转化成$|\displaystyle\sum p_i|\le 1$。

我们发现，$1$和$-1$是相反数，因此我们可以推断出红边和蓝边互为反向边（其实这个说法并不准确，请继续往下阅读）。那么这个边是从哪里连到哪里的呢？因为“边权”就是线段的权值，所以边就是从线段的起点连到线段的终点。

于是，我们的基本模型就出来了，那就是对于每一条线段，从线段的起点到终点连一条边，构成了一张$n$条边的**无向图**。

------------

接下来，我们考虑对这些边做什么。我们的目的是给线段确定一个串颜色，所以相当于是说我们要给这些线段定向。如何给这些线段定向呢？我们可以这么考虑：我们是让每一条线段从起点连向终点，相当于有两个独立的点集（左端点集合$L$和右端点集合$R$），集合内没有互相连边，集合之间互相有连边，所以实际上构成了一张二分图。那么我们对二分图中的边进行红蓝交替染色，直到染完所有的边为止。这样，我们就完成了定向。

------------

定向之后，我们就可以根据染色情况输出`0`或`1`。

实际上，我们并不需要初始时第一条边染什么颜色，例如`0 1 1 0 1`和`1 0 0 1 0`实际上是等价的，因此`SPJ`都会把你判为正确。

这时，我们注意到数据范围$l_i,r_i\le 10^9$（而256MB的空间储存不了$2\times 10^9$的数组），也就是说需要我们使用离散化，相当于把范围很广的一些坐标集中在$2\times n$的编号中，通过较小的编号来储存。这个在输入的时候需要特别注意。

------------

至此这道题就被我们完美地解决了。还有一道与本题思想类似的题目，希望大家可以触类旁通：[Codeforces 547D](https://www.luogu.org/problemnew/show/CF547D)。

下面我给出`cpp`代码：
```cpp
#include<cstdio>
#include<cstring>
#include<vector>
#include<map>
using namespace std;  
const int MAXN=200010;  

vector<int>p[MAXN];  
int vis[MAXN],ans[MAXN][2]; 
multimap<int,int>h;
int tot=0; 

void dfs(int x,int y)
{  
    if(vis[x]>=0)
    	return;
    else
    	vis[x]=y;
    int sz=p[x].size();
    for(int i=0;i<sz;i++)
        dfs(p[x][i],1^y);
}

int main()
{
	memset(vis,-1,sizeof(vis));
    int n;scanf("%d",&n);  
    int l,r;
    for(int i=0;i<n;i++)
    {
    	scanf("%d%d",&l,&r);
    	p[i<<1].push_back(i<<1|1);
		p[i<<1|1].push_back(i<<1);
        h.insert(make_pair(l<<1,i<<1));
		h.insert(make_pair(r<<1|1,i<<1|1));
	}
	multimap<int,int>::iterator it=h.begin();
	for(int i=0;i<n;i++)
	{
		int l=it->second;it++;
		int r=it->second;it++;
		p[l].push_back(r);p[r].push_back(l);
	}
	for(int i=0;i<n;i++)
		if(vis[i<<1]<0)
			dfs(i<<1,1);
	for(int i=0;i<n;i++)
		printf("%d ",vis[i<<1]);
    return 0;
}
```

---

## 作者：tzc_wk (赞：11)

[Codeforces 题面传送门](https://codeforces.ml/contest/429/problem/E) & [洛谷题面传送门](https://www.luogu.com.cn/problem/CF429E)

~~果然我不具备融会贯通的能力/ll~~

看到这样的设问我们可以很自然地联想到[这道题](https://www.luogu.com.cn/problem/CF547D)，具体来说我们可以通过某种方式建出一张图，然后根据”每个点度都是偶数的图必然每个连通块都存在欧拉回路“这一条件构造出原图的欧拉回路进而求解答案。因此现在问题转化为如何构建出这样一张图出来。

首先一个非常直观的想法是对于每个区间新建一个左部点，对于数轴上每一个整点新建一个右部点，然后从每个区间表示的左部点向这段区间中所有整点表示的右部点连边，这样问题可以变为，对于每个右部点，与其相连的左部点中红点与蓝点的差的绝对值 $\le 1$​，不过注意到这样一来涉及与每个点相连的点 instead of 边，这是不好直接用欧拉回路求解的，因此我们必须迟早放弃这个想法（

不难发现，如果我们将所有染成红色的视作 $+1$，染成蓝色视作 $-1$，那么一个点符合 $|r(x)-b(x)|\le 1$ 的要求当且仅当将所有覆盖它的所有线段权值之和为 $-1,0$ 或 $1$。因此问题可以转化为，有 $n$ 个区间，你要选择对于每一个区间，选择将区间中所有位置上的数 $+1$ 或者 $-1$，使得最终每个位置上的数的绝对值 $\le 1$。我们不妨先考虑一个弱化版，也就是所有点被覆盖次数恰好为偶数的情况，此时最终序列中每个数都应是 $0$。注意到这里涉及区间操作，而区间操作可以视作差分序列上的两个端点操作，也就是说对于一个区间 $[l,r]$，我们可以看作，你可以选择令 $b_l$ 加 $1$，$b_{r+1}$ 减 $1$，或者令 $b_l$ 减 $1$，$b_{r+1}$ 加 $1$，最后要使 $b$ 序列每个元素都是 $0$。我们考虑从 $l$ 向 $r+1$ 连一条边，这样如果我们选择 $(l,r+1)$ 这条边从 $l$ 指向 $r+1$ 则会使 $l$ 出度 $+1$，$r+1$ 入度 $+1$，反之会使 $l$ 入度 $+1$，$r+1$ 出度 $+1$，这样最终序列 $b$ 中所有元素都为 $0$ 就自然地被转化为，每个点入度都等于出度，这样就自然地可以欧拉回路了。跑一遍欧拉回路，然后如果 $(l_i,r_i+1)$ 这条边由 $l_i$ 指向 $r_i+1$ 则令 $i$ 的颜色为 $0$，否则令 $i$ 的颜色为 $1$。那么如果有的点覆盖次数不是偶数怎么办呢？如果 $i$ 覆盖次数为奇数，那我们就手动添加一个区间 $[i,i]$，这样所有点覆盖次数都是偶数，就可以规约为前一种情况了。

注意，由于区间长度很大，需要离散化。具体来说按照 P3643 [APIO2016]划艇 的套路，将所有区间改写成一个左闭右开的区间，然后离散化一下即可将整个数轴拆成 $\mathcal O(n)$ 个左闭右开的区间，那么显然每一个左闭右开的区间中所有点最终的权值都是一样的，因此我们只用取这个区间最左边的点作为该区间的代表点即可。

时间复杂度 $\mathcal O(n\log n)$，因为要离散化。

```cpp
const int MAXN=1e5;
int n,l[MAXN+5],r[MAXN+5],key[MAXN*2+5],cnt=0,uni[MAXN*2+5],num=0;
int d[MAXN*2+5],hd[MAXN*2+5],nxt[MAXN*6+5],to[MAXN*6+5],ec=1;
void adde(int u,int v){/*printf("adde %d %d\n",u,v);*/to[++ec]=v;nxt[ec]=hd[u];hd[u]=ec;}
int dir[MAXN*3+5],vis[MAXN*2+5],now[MAXN*2+5];
void dfs(int x){
//	printf("dfs %d\n",x);
	vis[x]=1;
	for(int &e=now[x];e;e=nxt[e]) if(!~dir[e>>1]){
		dir[e>>1]=e&1;dfs(to[e]);
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&l[i],&r[i]);++r[i];
		key[++cnt]=l[i];key[++cnt]=r[i];
	} sort(key+1,key+cnt+1);key[0]=-1;
	for(int i=1;i<=cnt;i++) if(key[i]^key[i-1]) uni[++num]=key[i];
	for(int i=1;i<=n;i++){
		l[i]=lower_bound(uni+1,uni+num+1,l[i])-uni;
		r[i]=lower_bound(uni+1,uni+num+1,r[i])-uni;
		d[l[i]]++;d[r[i]]--;adde(l[i],r[i]);adde(r[i],l[i]);
	}
	for(int i=1;i<=num;i++){
		d[i]+=d[i-1];
		if(d[i]&1) adde(i,i+1),adde(i+1,i);
	}
	memset(dir,-1,sizeof(dir));
	for(int i=1;i<=num;i++) now[i]=hd[i];
	for(int i=1;i<=num;i++) if(!vis[i]) dfs(i);
	for(int i=1;i<=n;i++) printf("%d%c",dir[i]," \n"[i==n]);
	return 0;
}
```



---

## 作者：LebronDurant (赞：8)

首先这个限制他有单点有线段，不是很整，通过轻微调整，把单点调整为一个区间，换个说法就是把端点强行定义一个偏序使得和原题限制不变，即如果位置相同，钦定左端点小于右端点。

这样的话，整条直线被划分为了$2n+1$段区间，每段区间受一些限制。发现这些区间依次向右，受影响的线段只多/少了一个。那么就是每段区间受影响的线段个数分别为奇数，偶数，奇数，偶数。那么对偶数的限制即为红色和蓝色个数必须相等，对奇数可以直接不考虑，因为相邻的两个偶数限制区间都符合题意的话，那么这个奇数区间一定符合红色和蓝色差不超过$1$。这步是真的神sto sjw orz。

接下来就考虑每次变化的两个线段，如果一个是左端点一个是右端点，那么这两条线段的颜色必须一样，否则必须不一样。按照如此限制跑个2-sat即可。时间复杂度为排序的$O(n\log n)$。

接下来证明这个方程组一定有解。每个未知数$x_i$在这个方程组里只会出现$2$次。那么把每个方程里的两个未知数连边的话一定是一堆环的形式。考虑把每个环的这些方程加起来，你会得到$0=0$，也就是说这些方程里面有一个是多余的。把随便一个去掉，给了一个限制，剩下的是一条链，按着拓扑序构造一定可以构造出解。
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
#include<vector>
#include<stack>
using namespace std;
typedef long long ll;
#define N 200002
struct node{int x,id,op;}a[N];
struct edge{int to,nxxt;}e[N<<3];
int n,tot,js,head[N<<2],cnt=2,dfn[N],low[N],f[N],cn,an;
bool inq[N];
stack<int>s;
inline void ins(int u,int v){e[cnt]=(edge){v,head[u]};head[u]=cnt++;}
inline bool cmp(node n1,node n2)
{
	if(n1.x^n2.x)return n1.x<n2.x;
	else return n1.op>n2.op;
}
void tarjan(int x)
{dfn[x]=low[x]=++cn;inq[x]=1;s.push(x);
	for(int i=head[x];i;i=e[i].nxxt)
	{int j=e[i].to;
		if(!dfn[j])tarjan(j),low[x]=min(low[x],low[j]);
		else if(inq[j])low[x]=min(low[x],dfn[j]);
	}
	if(dfn[x]==low[x])
	{an++;
		while(!s.empty()&&s.top()!=x){inq[s.top()]=0;f[s.top()]=an;s.pop();}
		inq[x]=0;f[x]=an;s.pop();
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		a[++tot]=(node){x,i,1};a[++tot]=(node){y,i,-1};
	}
	sort(a+1,a+1+tot,cmp);int su=0;
	for(int i=2;i<=tot;i+=2)
	{
		if(a[i].op!=a[i-1].op)
		{
			ins(a[i].id,a[i-1].id);ins(a[i-1].id,a[i].id);
			ins(a[i].id+n,a[i-1].id+n);ins(a[i-1].id+n,a[i].id+n);
		}
		else
		{
			ins(a[i].id,a[i-1].id+n);ins(a[i].id+n,a[i-1].id);
			ins(a[i-1].id,a[i].id+n);ins(a[i-1].id+n,a[i].id);
		}
	}
	for(int i=1;i<=2*n;i++)if(!dfn[i])tarjan(i);
	for(int i=1;i<=n;i++)printf("%d ",f[i]<f[i+n]);puts("");
}

```


---

## 作者：RainFestival (赞：4)

这个方法来自 @realskc。非常感谢 Ta。这篇文章介绍了一种使用黑白染色的解决方案。

本题所属比赛于 $2014.5$ 举办，在 $\tt codeforces$ 上评分 $3\color{red} 000$。

我们首先考虑这么一个问题：给你 $n$ 条线段，如何**判断**是否满足题目的限制条件。

对于每一个坐标位置 $x$，假设有 $s$ 条线段覆盖了这个位置，那么必须要有 $\lfloor\frac{s}{2}\rfloor$ 个某一种颜色的线段，$s-\lfloor\frac{s}{2}\rfloor$ 个另外一种颜色的线段。

对于这 $s$ 条线段，我们把其中 $2\times \lfloor\frac{s}{2}\rfloor$ 条线段构成 $\lfloor\frac{s}{2}\rfloor$ 组匹配，只需要保证每一组匹配里面两条线段颜色不同即可。

现在考虑对于所有位置 $x$ 的问题：考虑对于所有位置 $x$，动态维护这个匹配即可。

我们构造一个图 $G$：对于每一组存在过的线段 $i$ 与线段 $j$ 的匹配，连接一条 $(i,j)$ 的无向边。我们对于我们 $G$ 进行**黑白染色**，把图的染色结果做为线段染色即可。

具体如何动态维护这一匹配，我们从左向右枚举每一个坐标，然后只需要考虑添加或者删除一条线段即可。下面 $7$ 段介绍了维护流程，稍显程序化，并且比较简单。如果不想看也可以考虑略过。

我们记录当前每一条 $x$ 匹配的线段 $mat_x$。我们发现在覆盖当前位置的所有线段中最多有一条线段 $p$ 没有被匹配。如果这样的 $p$ 不存在，那么 $p=0$。

+ 对于加入一条线段 $x$，如果此时 $p=0$，那么它就成为了那一条没有匹配的线段，令 $p\leftarrow x$ 即可；如果 $p\neq 0$，那么简单的令 $x$ 和 $p$ 匹配即可，注意 $p$ 已经被匹配了，我们还需要令 $p\leftarrow 0$。

+ 对于删除一条线段 $x$，情况稍稍麻烦一点。

如果此时 $p=x$，那么 $x$ 没有被匹配。此时只需要令 $p\leftarrow 0$ 即可。

否则，$x$ 原先与 $mat_x$ 匹配。删除 $x$ 之后，$mat_x$ 就失去了匹配。以下的流程和重新加入线段 $mat_x$ 类似。~~于是以下这段话是基本上是复制上面的。~~

如果此时 $p=0$，那么 $mat_x$ 就成为了那一条没有匹配的线段，令 $p\leftarrow x$ 即可；如果 $p\neq 0$，那么简单的令 $mat_x$ 和 $p$ 匹配即可，注意 $p$ 已经被匹配了，我们还需要令 $p\leftarrow 0$。

每次我们匹配两条线段时，都要将两条线段连边。注意删除匹配的时候不要删除原先连接的边。

当处理完所有的坐标以后，我们的限制已经很完备了，只需要对我们建立的图进行二分图染色即可。

我们注意到我们没有讨论无解的情况。很遗憾，笔者不会，只能在这里写出结论：不会有无解的情况，样例也没有无解的情况。

代码如下：共计 $16$ 个测试点，总共用时 $\tt 3.21s$，内存 $\tt 28.46 MB$。代码长度 $\tt 1.60kb$。在洛谷 $56$ 发提交中排名第 $56$。

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
#include<assert.h>
#include<map>
struct edge{int x,y;};
edge f[100005];
int n,mat[100005],col[100005],now=0;
std::vector<int> a[100005],add[200005],del[200005],vec;
std::map<int,int> mp;
void addqwq(int x,int y){a[x].push_back(y);a[y].push_back(x);}
void dfs(int v,int c)
{
	col[v]=c;
	for (int i=0;i<(int)a[v].size();i++)
	{
		int u=a[v][i];
		if (col[u]!=-1) continue;
		dfs(u,1-c);
	}
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d",&f[i].x,&f[i].y);
		if (!mp[f[i].x]) vec.push_back(f[i].x),mp[f[i].x]=1;
		if (!mp[f[i].y+1]) vec.push_back(f[i].y+1),mp[f[i].y+1]=1;
	}
	std::sort(vec.begin(),vec.end());
	for (int i=0;i<(int)vec.size();i++) mp[vec[i]]=i+1;
	for (int i=1;i<=n;i++) f[i].x=mp[f[i].x],f[i].y=mp[f[i].y+1];
	for (int i=1;i<=n;i++) add[f[i].x].push_back(i),del[f[i].y].push_back(i);
	for (int i=0;i<(int)vec.size();i++) vec[i]=mp[vec[i]];
	for (int i=1;i<=n;i++) col[i]=-1;
	for (int i=0;i<(int)vec.size();i++)
	{
		int x=vec[i];
		for (int d=0;d<(int)del[x].size();d++)
		{
			int id=del[x][d];
			int k=mat[id];
			mat[id]=0;
			if (now==id) now=0;
			if (!k) continue;
			if (now)
			{
				mat[now]=k,mat[k]=now;
				addqwq(k,now);
				now=0;
			}
			else now=k,mat[now]=0;
		}
		for (int d=0;d<(int)add[x].size();d++)
		{
			int id=add[x][d];
			if (now)
			{
				mat[now]=id,mat[id]=now;
				addqwq(id,now);
				now=0;
			}
			else now=id;
		}
	}
	for (int i=1;i<=n;i++) if (col[i]==-1) dfs(i,1);
	for (int i=1;i<=n;i++) printf("%d ",col[i]);puts("");
	return 0;
}
```

感谢您的阅读。希望能帮助您。

---

## 作者：SHOHOKUKU (赞：3)

##### 传送门 
[Codeforces 429E Points and Segments](https://codeforces.com/contest/429/problem/E)
##### 题解
===upd 2023.04.13===

感谢评论区，欧拉回路的做法中，可以通过将坐标轴上相邻两点之间区间设置为一个节点，此时区间 $[l,r]$ 建图为 $l\rightarrow (r,r+1)$。此时节点 $(r,r+1)$ 仅可能作为某个区间的右端点的开界被连边，这个性质使得即使出现下述的**引入不存在的染色区间的问题**，由于非法区间染色是两个一组设置为异色，此时可以保证这样的非法区间内任一点满足题目条件。

===以下为原文===

>先贴一个最开始写的，后来觉得有误的方法：欧拉回路。

对于这类黑白染色，且存在差值绝对值不超过 $1$ 的问题，可以考虑欧拉回路求解。因为按照欧拉回路将无向图的边指定方向后，任意点的入度与出度相等；若图中存在度数为奇的点，这样的点只有偶数个，那么将其两两一组进行连边，求解欧拉回路后删边，此时，任意点的入度与出度差值的绝对值不超过 $1$。

考虑 X 轴上任意点，合法的染色方案需要满足，覆盖它的区间中，蓝色与红色的数量差不超过 $1$。将区间看作边，其染色看作对边的定向（向左或右），根据欧拉回路的性质，X 轴上任一点上，向左与向右的边数量相等。为了处理区间的边界情况（即保证区间拼接起来，可以看作是一个大区间），将其表示为左闭右开 $[l,r+1)$，对于每一个区间 $l\rightarrow r+1$ 连一条边。对于奇数度的点，按照 X 轴顺序两两一组连边；因为若需要删除的边出现覆盖，绝对差值可能大于 $1$。

建图后求解欧拉回路即可。总时间复杂度 $O(n\log n)$，瓶颈在离散化上。

上述算法的问题在于，原始的区间是左闭右闭，而为了满足区间左闭右开的性质，将 $[l,r]$ 表示为 $[l,r+1)$。此时 $(r,r+1)$ 应该与 $[l,r]$ 逻辑一致，即表示某一种区间的染色方案，但实际上 $(r,r+1)$ 并没有区间覆盖。这就导致了在 $(r,r+1)$ 中可能出现不满足条件的点。下面的样例，存在一种欧拉回路的构造，使之在 $(3,4)$ 区间内的任一点都不满足条件。

```cpp
/*
7
4 6
4 5
1 3
2 3
1 1
1 5
1 6
*/
```


**故上述欧拉回路的做法，仅在下述约束下正确：原始区间为左闭右开；或只要求在整数点上满足条件。**
```cpp
#include <bits/stdc++.h>
using namespace std;
struct edge
{
    int to, rev, id;
    bool used;
};

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);
    int N;
    cin >> N;
    vector<pair<int, int>> seg(N);
    vector<int> xs;
    for (int i = 0; i < N; ++i)
    {
        cin >> seg[i].first >> seg[i].second;
        ++seg[i].second;
        xs.push_back(seg[i].first);
        xs.push_back(seg[i].second);
    }
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    for (auto &p : seg)
    {
        p.first = lower_bound(xs.begin(), xs.end(), p.first) - xs.begin();
        p.second = lower_bound(xs.begin(), xs.end(), p.second) - xs.begin();
    }

    int V = xs.size();
    vector<vector<edge>> G(V);
    vector<int> deg(V);
    for (int i = 0; i < N; ++i)
    {
        int u = seg[i].first, v = seg[i].second;
        G[u].push_back({v, (int)G[v].size(), i, 0});
        G[v].push_back({u, (int)G[u].size() - 1, i, 0});
        ++deg[u], ++deg[v];
    }
    vector<int> odd;
    for (int v = 0; v < V; ++v)
    {
        if (deg[v] & 1)
            odd.push_back(v);
    }
    assert(((int)odd.size() & 1) == 0);
    for (int i = 0; i < (int)odd.size(); i += 2)
    {
        int u = odd[i], v = odd[i + 1];
        G[u].push_back({v, (int)G[v].size(), -1, 0});
        G[v].push_back({u, (int)G[u].size() - 1, -1, 0});
    }
    vector<int> res(N);
    vector<int> iter(V);
    function<void(int)> euler_path = [&](int v)
    {
        int n = G[v].size();
        for (int &i = iter[v]; i < n; ++i)
        {
            while (i < n && G[v][i].used)
                ++i;
            if (i == n)
                break;
            auto &e = G[v][i];
            if (e.id != -1)
                res[e.id] = e.to > v ? 1 : -1;
            e.used = G[e.to][e.rev].used = 1;
            euler_path(e.to);
        }
    };

    for (int v = 0; v < V; ++v)
        if (iter[v] == 0)
            euler_path(v);

    for (int i = 0; i < N; ++i)
        cout << max(0, res[i]) << " \n"[i + 1 == N];
    return 0;
}
```
>如下是个人认为的正解：2-SAT

为了避免歧义，题中的 $[l,r]$ 区间，下面称之为线段。

类似于扫描线的思想，将线段拆为左右端点，在 X 轴上依次向右考虑。每遇到一个端点 $x$，区间所覆盖线段数量的奇偶性改变；对于任一偶数区间，两种颜色染色数量相等。观察发现，在奇数区间，左右端点同时为线段左（或右）端点时，两个端点代表的线段所染颜色不同；反之，染色相同。定义

$$x_i\text{为真} \Leftrightarrow \text{线段}i\text{染为红色}$$ 

转化为 2-SAT 问题。

上述方法基于一个假设，各个端点坐标互不相同。若出现端点相同的坐标，考虑这样一个问题：对区间某个点 $x$ 操作 $n$ 次，操作只有 $\pm 1$ 两种，求最终 $x$ 上的值绝对值不超过 $1$ 的方案。显然之前对于奇数区间端点两两配对的方法也是可行的。

最后的问题还是关于原始线段左闭右闭的性质。对于左端点，是右连续的；对于右端点，是左连续的。即，坐标为 $x$ 的左端点，改变的区间是 $[x,\cdots)$；而右端点是 $(x,\cdots)$。故相同坐标的左端点应优先于右端点被处理。若原始的区间就是左闭右开，则不用考虑这个问题，直接按照坐标排序即可。

分解强连通分量进行求解，总时间复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
struct Node
{
    int x, d, id;
};

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);
    int N;
    cin >> N;
    vector<Node> ns;
    for (int i = 0; i < N; ++i)
    {
        int l, r;
        cin >> l >> r;
        ns.push_back({l, 1, i});
        ns.push_back({r, -1, i});
    }
    sort(ns.begin(), ns.end(), [&](auto &a, auto &b)
         {
             if (a.x != b.x)
                 return a.x < b.x;
             return a.d > b.d;
         });

    int V = N * 2;
    vector<vector<int>> G(V), rG(V);
    auto add_edge = [&](int u, int v)
    { G[u].push_back(v), rG[v].push_back(u); };

    for (int i = 0; i < V; i += 2)
    {
        auto &a = ns[i], &b = ns[i + 1];
        if (a.d == b.d)
        {
            add_edge(a.id + N, b.id);
            add_edge(b.id + N, a.id);
            add_edge(a.id, b.id + N);
            add_edge(b.id, a.id + N);
        }
        else
        {
            add_edge(a.id, b.id);
            add_edge(b.id + N, a.id + N);
            add_edge(a.id + N, b.id + N);
            add_edge(b.id, a.id);
        }
    }

    vector<int> scc(V);
    auto find_scc = [&]()
    {
        vector<bool> used(V);
        vector<int> vs;
        function<void(int)> dfs = [&](int v)
        {
            used[v] = 1;
            for (int u : G[v])
                if (!used[u])
                    dfs(u);
            vs.push_back(v);
        };
        function<void(int, int)> rdfs = [&](int v, int k)
        {
            used[v] = 1;
            scc[v] = k;
            for (int u : rG[v])
                if (!used[u])
                    rdfs(u, k);
        };
        for (int v = 0; v < V; ++v)
            if (!used[v])
                dfs(v);
        int k = 0;
        fill(used.begin(), used.end(), 0);
        for (int i = (int)vs.size() - 1; i >= 0; --i)
            if (!used[vs[i]])
                rdfs(vs[i], k++);
    };

    find_scc();
    for (int i = 0; i < N; ++i)
        cout << (scc[i] > scc[i + N] ? 1 : 0) << " \n"[i + 1 == N];
    return 0;
}
```


---

