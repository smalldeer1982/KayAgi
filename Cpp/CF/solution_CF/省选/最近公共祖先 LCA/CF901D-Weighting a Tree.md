# Weighting a Tree

## 题目描述

给你一个有 $n$ 个顶点与 $m$ 条边的无向图，那些顶点的编号依次为 $1$ 到 $n$。

再给你 $n$ 个整数 $C_1,C_2,\dots,C_n$，每一个数都在区间 $[-n,n]$ 之间。保证 $C_v$ 的奇偶性与顶点 $v$ 的度的奇偶性相同。一个顶点的的度是指连接到它的边数。

你需要按照下列的要求为所有边写上一个在 $[-2n^2,2n^2]$ 之间的一个重量：对于任何一个顶点 $v$，所有连接到这个顶点的边的重量和等于 $C_v$。或者，确定这是不可能达到的。

## 样例 #1

### 输入

```
3 3
2 2 2
1 2
2 3
1 3
```

### 输出

```
YES
1
1
1
```

## 样例 #2

### 输入

```
4 3
-1 0 2 1
1 2
2 3
3 4
```

### 输出

```
YES
-1
1
1
```

## 样例 #3

### 输入

```
6 6
3 5 5 5 1 5
1 4
3 2
4 3
4 5
3 5
5 6
```

### 输出

```
YES
3
5
3
-1
-3
5
```

## 样例 #4

### 输入

```
4 4
4 4 2 4
1 2
2 3
3 4
4 1
```

### 输出

```
NO```

# 题解

## 作者：ywy_c_asm (赞：11)

这题真的是个构造好题。首先我们要知道这种“点与跟他连着的所有边的关系”什么的题的套路就是**找生成树**。

我们考虑一个最简单的情况，即这个图是一棵树，那么我们可以考虑每个叶子节点，他们仅连着一条边，那么这条边的边权就必须是叶子的点权，那么我们可以删掉这个叶子与这条边，把他的父亲的点权减去边权，然后我们就等效转化到了$n-1$个点的树的情况，于是就可以用一遍$dfs$不断地自下而上的这样归纳推出每个边的边权并且修改点权。显然在有解的情况下$dfs$之后根的点权一定是0，因为他上面没有边了。

然后我们接着就把这种情况扩展到一般图上，我们要知道构造题有个套路就是很多东西的答案是对全局可以没有用的，可以直接让他们是0，我们仅仅对对全局答案有用的那些很少的一部分去求解，这样问题规模就会缩减许多，这题的主要思想大概就是这样。那么我们可以先求出一棵生成树，这样树边的答案（暂时的）就非常好求了。然后我们就想，如果现在的根的点权为0，那么其他非树边就没有必要求解了，直接保留树边的答案，并将所有非树边直接设为0那么构造出来的这个解就已经可行了。如果根不是0，那么说明我们只留着树边还是不行，必须要一些（真的就是一些吗？）非树边也参与进来，并且还要对当前树边的答案进行适当的调整。

到这里先明确一下我们现在的目标就是给一些非树边赋个边权使得根节点的点权变成0。显然非树边加进来会与树边构成环，如果要让他的边权增加1，我们在这里先考虑一下点权，他连的两个点$s,t$的点权得-1，然后再沿着这两个点往上走，到他的父亲会把父亲的点权+1，再到他爷爷会把爷爷的点权-1，然后我们发现这个和黑白染色很像，就是经过一条边之后就取个反。这会对根造成什么影响呢？那么我们就可以想到对环的奇偶性进行讨论：

1.偶环，因为我们要考虑对根的影响，这相当于是改变量不断往上移动，边移动一条边边把改变量取个反，我们就考虑$LCA(s,t)$，因为构成的环是偶环，所以$s$和$t$到$LCA$的距离的奇偶性是不同的，而开始的时候$s$和$t$改变量是相同的，所以他们对$LCA$的改变量会互为相反数，也就是说他们的改变量不断同时往上移动，移动到$LCA$相遇到一块就成了0，于是再往上就没有任何改变量了，所以构成偶环的非树边对根的点权完全没有影响，我们不用也不能管他们，直接把他们的答案都设为0。

2.奇环，根据刚才对偶环的讨论我们发现在奇环中$s$和$t$对$LCA$的改变量也是相同的，也就是说改变量变为了2倍，那么再往上改变量的绝对值始终会是原来改变量绝对值的2倍，一直到根。

那么我们发现其实只需要改变一条构成奇环的非树边的答案就行了，我们就把他连的两个点减去他的边权的增量，然后重新在生成树上进行一遍跟第一步统计树边答案一样的$dfs$把树边的答案调整一下，然后就行了。

还有可能会有人问那如何保证边权的范围合法呢？其实题目里那个范围的限制是吓唬人用的，因为每个点的点权都在$[-n,n]$内，所以不难发现我们第一遍$dfs$至多会对树边产生绝对值为$n^2$的贡献，根节点肯定也不会超过这个限制，所以那条奇环非树边也不会超限，第二遍$dfs$调整的答案贡献的绝对值也肯定不会超过$n^2$，所以并不会超过限制。

哦，对了，答案会爆$int$~~（手动滑稽~~

上代码~

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define int long long
#define abs(_o) ((_o<0)?-(_o):_o)
using namespace std;
inline int get() {//我的垃圾快读 
	int n=0;
	char c;
	while((c=getchar())||23333) {
		if(c>='0'&&c<='9')break;
		if(c=='-')goto s;
	}
	n=c-'0';
	while((c=getchar())||23333) {
		if(c>='0'&&c<='9')n=n*10+c-'0';
		else return(n);
	}
s:
	while((c=getchar())||23333) {
		if(c>='0'&&c<='9')n=n*10-c+'0';
		else return(n);
	}
}
typedef struct _b {
	int dest;
	int nxt;
	int num;
} bian;
bian memchi[200001];//边 
int gn=1;
int heads[200001],ints[100001]； //并查集 
int anss[100001]；//每条边的答案 
int ss[100001],ts[100001]；//边的端点 
int v[100001];//点权 
inline void add(int s,int t,int num) {
	memchi[gn].dest=t;
	memchi[gn].nxt=heads[s];
	memchi[gn].num=num;
	heads[s]=gn;
	gn++;
}
unsigned char col[100001];//图的染色（用来判奇偶环的） 
int que[100001];
unsigned char istree[100001];//是否为树边 
void print(int num) {//垃圾快输 
	if(num<0)putchar('-'),num=-num;
	if(num>=10)print(num/10);
	putchar(num%10+'0');
}
int find(int n) {//并查集 
	if(ints[n]==n)return(n);
	return(ints[n]=find(ints[n]));
}
void dfs(int pt,int baba) {//统计答案用的dfs 
	for(register int i=heads[pt]; i; i=memchi[i].nxt) {
		if(memchi[i].dest==baba)continue;
		dfs(memchi[i].dest,pt);
		anss[memchi[i].num]+=v[memchi[i].dest];
		v[pt]-=v[memchi[i].dest];
		v[memchi[i].dest]=0;
	}
}
int tmp[100o01];
void efs(int pt,int baba) {//这个东西，刚才说了对根节点会产生绝对值为2的改变量，但具体是+2还是-2我就用一个dfs算了一下 
	for(register int i=heads[pt]; i; i=memchi[i].nxt) {
		if(memchi[i].dest==baba)continue;
		efs(memchi[i].dest,pt);
		tmp[pt]-=tmp[memchi[i].dest];
	}
}
signed main() {
	int n=get(),m=get();
	for(register int i=1; i<=n; i++)v[i]=get(),ints[i]=i,col[i]=2;
	for(register int i=1; i<=m; i++) {
		ss[i]=get(),ts[i]=get();
		int aa=find(ss[i]),ab=find(ts[i]);
		if(aa!=ab) {//树边 
			ints[aa]=ab;
			add(ss[i],ts[i],i);
			add(ts[i],ss[i],i);
			istree[i]=1;
		}
	}
	register int head=0,tail=1;
	que[0]=1;
	col[1]=0;
	do {//对生成树进行黑白染色 
		int me=que[head];
		head++;
		for(register int i=heads[me]; i; i=memchi[i].nxt) {
			if(col[memchi[i].dest]!=2)continue;
			col[memchi[i].dest]=col[me]^1;
			que[tail]=memchi[i].dest;
			tail++;
		}
	} while(head<tail);
	dfs(1,0);
	if(abs(v[1])&1) {//根节点点权不是二的倍数，无解 
		printf("NO\n");
		return(0);
	}
	if(v[1]==0) {//根节点点权已经是0，直接令非树边为0，输出答案 
		printf("YES\n");
		for(register int i=1; i<=m; i++)print(anss[i]),putchar('\n');
		return(0);
	}
	for(register int a=1; a<=m; a++) {//找奇环非树边 
		if(istree[a])continue;
		if(col[ss[a]]!=col[ts[a]])continue;
		printf("YES\n");
		int val=v[1]/2;
		tmp[ss[a]]++;
		tmp[ts[a]]++;
		efs(1,0);
		if(tmp[1]==2) {
			v[ss[a]]-=val;
			v[ts[a]]-=val;
			anss[a]=val;
		} else {
			v[ss[a]]+=val;
			v[ts[a]]+=val;
			anss[a]=-val;
		}
		dfs(1,0);//对树边进行调整 
		for(register int i=1; i<=m; i++)print(anss[i]),putchar('\n');
		return(0);
	}
	printf("NO\n");
	return(0);
}
```


---

## 作者：SilviaLss (赞：8)

首先看到图，构造方案就根据套路想到生成树。发现从叶子开始确定，一直往上推，这样操作完后就会使得除了根节点之外的所有节点满足条件。

然后考虑非树边。显然一条非树边在树上会形成一个环，手模发现如果环上的点有偶数个那么对根节点就不会有任何影响，如果换上有奇数个点，那么如果给这条边的权值 $+1$ 就会对根会产生 $-2$ 或者 $2$ 的影响。

于是可以随便弄出一棵生成树，贪心把除了根节点的所有点都弄成满足条件后，先判断根节点当前权值与目标权值的差是否可以被 $2$ 整除，然后再去一个个处理非树边构成的环，找到奇环后就直接去更新即可。

对于更新答案的细节，我们可以先假设这个边的权值 $+1$ 对根的贡献是 $2$，那么按照这个加完权值后再重新算每个边的边权，来更新点权，如果此时根节点答案不是目标答案，那么就改变权值的正负号，重新跑一遍即可。

因为找到一个奇环后就直接输出答案了，因此复杂度 $O(n\log n)$。

并且每个点的目标答案都是 $\in[-n,n]$ 的，所以肯定不会超出限制。

[代码](https://codeforces.com/contest/901/submission/160441042)

---

## 作者：i207M (赞：6)

## 构造题，不要想的那么复杂，尝试用最简单的方法构造出呀一个接近正确的答案，然后进行尽量小的调整

如果图是一棵树，那么方案就是唯一的，直接判一下就可以了。

否则随便搞一棵生成树，先不管其他边，跑一遍。

这时根节点可能还不满足条件。

这时考虑其他的边，一条非树边会形成一个环。

如果是一个偶环，那么无论这条非树边怎么变，都不会对根节点产生影响。

否则是奇环，那么如果给这条非树边增加或减少权值，根节点会发生 2 的权值变化。

那么就可以了。

**KEY：**

具体边权的调整，发现讨论的情况很多，于是我用了一个讨巧的方法，首先根节点的权值变化一定与这条边的权值成正比例，于是先把这条边的权值设为1，跑一边，得到根节点的变化量，并算出这条边应有的权值；

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<vector>
#include<set>
#include<queue>
#include<map>
#include<cstring>
#include<string>
#include<bitset>
#include<iomanip>
using namespace std;
#define ri register int
#define il inline
#define pb push_back
#define LL long long
#define pairint pair<int,int>
#define fi first
#define se second
#define mp make_pair

namespace i207M
{

template<class T>il void in(T &x)
{
    x=0; bool f=0; char c=getchar();
    while(c<'0'||c>'9')
    {
        if(c=='-') f=1;
        c=getchar();
    }
    while(c>='0'&&c<='9') x=x*10+(c^'0'),c=getchar();
    if(f) x=-x;
}

#define N 100005
#define int LL
int v[N<<1],nx[N<<1];
int head[N],cnte=1;
il void adde(int uu,int vv)
{
	v[++cnte]=vv,nx[cnte]=head[uu],head[uu]=cnte;
}
int n,m;
int c[N];
int d[N];
int ve[N];
bool chs[N];
bool vis[N];
int dep[N];
int fa[N][17]; // max 2^16
bool q=1;
void dfs(int x,int f)
{
	vis[x]=1;
	if(q)
	{
		dep[x]=dep[f]+1;
		fa[x][0]=f;
		for(ri i=1;i<=16&&fa[x][i-1];++i)
			fa[x][i]=fa[fa[x][i-1]][i-1];
	}
	for(ri i=head[x];i;i=nx[i])
		if(!vis[v[i]])
		{
			chs[i>>1]=1;
			dfs(v[i],x);
			if(d[v[i]]!=c[v[i]])
			{
				ve[i>>1]=c[v[i]]-d[v[i]];
				d[x]+=ve[i>>1];
				d[v[i]]+=ve[i>>1];
			}
		}
}
il void gun()
{
	puts("NO");
	exit(0);
}
il void done()
{
	puts("YES");
	for(ri i=1;i<=m;++i) printf("%lld\n",ve[i]);
	exit(0);
}
int lca(int x,int y)
{
	if(dep[x]<dep[y]) swap(x,y);
	for(ri i=16;i>=0;--i)
		if(dep[fa[x][i]]>=dep[y]) x=fa[x][i];
	if(x==y) return x;
	for(ri i=16;i>=0;--i)
		if(fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
signed main()
{
#ifdef M207
	freopen("in.in","r",stdin);
#endif
	in(n),in(m);
	for(ri i=1;i<=n;++i) in(c[i]);
	for(ri i=1,a,b;i<=m;++i)
	{
		in(a),in(b);
		adde(a,b);
		adde(b,a);
	}
	dfs(1,0);
	if(d[1]==c[1]) done();
	else if((d[1]-c[1])&1) gun();
	for(ri i=1;i<=m;++i)
		if(!chs[i])
		{
			int uu=v[i<<1|1],vv=v[i<<1],f=lca(uu,vv);
			if(dep[uu]<dep[vv]) swap(uu,vv);
			int len=dep[uu]+dep[vv]-(dep[f]<<1)+1;
			if(len&1)
			{
				int rem=c[1]-d[1];
				--c[uu],--c[vv];
				q=0; memset(d,0,sizeof d);
				memset(vis,0,sizeof vis);
				dfs(1,0);
				int tmp=rem/(c[1]-d[1]-rem);
				++c[uu],++c[vv];
				ve[i]-=tmp;
				c[uu]+=tmp,c[vv]+=tmp;
				memset(d,0,sizeof d);
				memset(vis,0,sizeof vis);
				dfs(1,0);
				done();
			}
		}
	gun();
    return 0;
}




}

signed main()
{
    i207M::main();
    return 0;
}
```

---

## 作者：DegChuZm (赞：5)

CF901D
### sol
对于这种神秘图上构造，我们可以直接拍一棵生成树上去。

现在就是一棵树加上一堆非树边。

对于一棵树的情况是比较好做的（？，我们 dfs 考虑边的填法，从叶子向上填，每一层优先满足自己，差的东西靠自己上父亲的那条边补回来就行，这样只需要判 根节点 就行了。

树的话这就可以到此为止了，看 $1$ 和 $c_1$ 的差距是不是 $0$ 输出就行了。

图的话，手玩几个图的数据，会发现只有修改奇环才可以让 根节点 的重量变化（？？？，而且你给这条奇环非树边 $+1$ 会让这个重量 $+2$ 或 $-2$。

然后剩下就好做了，寻找奇环然后随便做就行了，这里推荐使用 dfs 生成树，它没有横叉边，只需要 深度 和 边的两个端点 就可以判奇环。

找到奇环过后参考了一个题解的偷懒写法，先看看加正的行不行，不行就边权取反。

下面简单说一下上面的结论：

首先环有没有包含 $1$ 都是一样的，这个比较好理解。

如果是偶环的话，这个环内部就可以通过 $+1,-1$ 自产自销，对环外是没贡献的，也就不会让 根节点 的重量变化。

如果是奇环，这个环无论怎么安排始终都会有一个二的贡献消不掉，只能顺着到 根节点 的链跑上去，最终影响根节点。

### code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,c[100001],itr[100001],fa[100001],x[100001],y[100001],dis[100001],dep[100001],head[100001],cnt;
struct dcz{
	int nex,to,val;
}a[200001];
void add(int x,int y){
	a[++cnt].nex=head[x];
	a[cnt].to=y;
	head[x]=cnt;
}
int gf(int x){
	if(x==fa[x]) return x;
	return fa[x]=gf(fa[x]);
}
void gtr(int u,int fa){
	dep[u]=dep[fa]+1;
	for(int i=head[u];i;i=a[i].nex){
		int v=a[i].to;
		if(v==fa) continue;
		if(!dep[v]) itr[(i+1)/2]=1,gtr(v,u);
	}
}
void dfs(int u,int fa){
	int val=0;
	for(int i=head[u];i;i=a[i].nex){
		int v=a[i].to;
		if(v==fa) continue;
		dfs(v,u);val+=dis[v];
	}
	dis[u]=c[u]-val;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>c[i];fa[i]=i;
	}
	for(int i=1;i<=m;i++){
		cin>>x[i]>>y[i];
		add(x[i],y[i]);
		add(y[i],x[i]);
		//还是 dfs 生成树没有横叉边录着爽。 
	}
	gtr(1,0);
	memset(head,0,sizeof head),cnt=0;
	int f=0;
	for(int i=1;i<=m;i++){
		if(itr[i]) add(x[i],y[i]),add(y[i],x[i]);
		if(!itr[i]){
			int vl=dep[x[i]]-dep[y[i]]+1;
			if(vl&1) f=i;
		}
	}
	dfs(1,0);
	if(dis[1]&1) cout<<"NO\n";
	else if(!dis[1]){
		cout<<"YES\n";
		for(int i=1;i<=m;i++){
			if(itr[i]) cout<<(dep[x[i]]>dep[y[i]]?dis[x[i]]:dis[y[i]])<<"\n";
			else cout<<0<<"\n";
		}
	}
	else if(!f) cout<<"NO\n";
	else{
		cout<<"YES\n";
		int q=dis[1]/2;
		c[x[f]]-=dis[1]/2,c[y[f]]-=dis[1]/2;
		dfs(1,0);
		if(!dis[1]){
			for(int i=1;i<=m;i++){
				if(itr[i]) cout<<(dep[x[i]]>dep[y[i]]?dis[x[i]]:dis[y[i]])<<"\n";
				else if(f==i) cout<<q<<'\n';
				else cout<<0<<"\n";
			}
		}
		else{
			c[x[f]]+=q*2,c[y[f]]+=q*2;
			dfs(1,0);
			if(!dis[1]){
				for(int i=1;i<=m;i++){
					if(itr[i]) cout<<(dep[x[i]]>dep[y[i]]?dis[x[i]]:dis[y[i]])<<"\n";
					else if(f==i) cout<<-q<<'\n';
					else cout<<0<<"\n";
				}
			}
		}
	}
	return 0;
} 
```

---

## 作者：鱼跃于渊 (赞：3)

## 解法

我们首先考虑如果给定一棵树该如何处理。  
显然叶子结点只连着一条边，所以这条边的边权一定是这个点的点权。  
而它父亲结点的点权要减去连着它儿子所有边的边权，这时连着它的边只有一条边权未定，所以把剩下的点权赋到这条边上。  
跑一遍 dfs，执行上述操作。有解当且仅当根节点最后的点权为 $0$，因为它上面再没有边了。  

考虑把这个做法扩展到一张图里，我们先找出这张图的 dfs 树，对着这棵树执行上述操作。  
而那些不在 dfs 树中的边该如何处理呢？  
如果最后根结点的点权为 $0$，那么这些边的边权统一为 $0$，因为我们只使用 dfs 树上的边就可以满足条件，这些边也就无关紧要了。  
如果不为 $0$，我们就要找出一些可以使它变为 $0$ 的非树边出来。  

考虑更改一条非树边的权值会产生什么影响，首先它可以和树边组成一个环。  
考虑它的权值会对这个环上的点产生什么影响，比如令它的边权为 $1$ 会如何？  
显然它连接的点 $u,v$ 的点权会增加 $-1$，沿着这两个点往上跳，它们的父亲结点点权会增加 $1$，它们的爷爷结点点权会增加 $-1$。  
所以每经过一条边它的影响就会取反，考虑点 $u,v$ 到了 $\operatorname{lca}(u,v)$ 汇合后的影响，不难想到这和环的奇偶性有关：  

1. 如果是偶环，那么 $u,v$ 到 $\operatorname{lca}$ 距离的奇偶性不同，所以这条边的影响到了 $\operatorname{lca}$ 处就会相互抵消，无法对根结点产生影响，所以我们还是使它的边权为 $0$。  
2. 如果是奇环，那么 $u,v$ 到 $\operatorname{lca}$ 距离的奇偶性相同，所以这条边的影响到了 $\operatorname{lca}$ 处就会翻倍，可以继续往上对根结点产生影响。  
   令这条非树边的边权为 $w$，则它对根结点产生的影响为 $2\times w$ 或 $-2\times w$，可以发现此时有解的条件是根结点的点权为偶数，否则必定无解。  
   我们可以发现其实只要修改这么一条在奇环上的非树边就可以了，它的边权为根结点的点权除以二，是正是负由 $\operatorname{lca}$ 到根距离的奇偶性决定。  
   然后再跑一遍 dfs 调整答案即可。  

这样会不会超出 $[-2\times n^2,2\times n^2]$ 的边权限制呢？  
因为每个点的点权在 $[-n,n]$ 内，所以 dfs 时边权的改变量在 $[-n^2,n^2]$ 内，调整答案时边权也在 $[-n^2,n^2]$ 内，所以不会超出限制。  

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace fisher{
#define int long long
#define per(i,a,b) for(int i=(a);i<=(b);i++)
#define rep(i,b,a) for(int i=(b);i>=(a);i--)
#define epb emplace_back
const int N=1e5+5,inf=1e18;
struct edge{
	int v,id;
	edge(int _v=0,int _id=0){
		v=_v;id=_id;
	}
};
int n,m,c[N],bw[N],dep[N];
bool in[N],vis[N];
vector <edge> e[N];
void dfs(int u,int fa){
	dep[u]=dep[fa]+1;vis[u]=1;
	for(auto x:e[u]){
		if(vis[x.v]||x.v==fa) continue;
		in[x.id]=1;dfs(x.v,u);
		bw[x.id]+=c[x.v];
		c[u]-=c[x.v];
		c[x.v]=0;
	}
}
void print(bool op){
	if(op){
		cout<<"YES\n";
		per(i,1,m) cout<<bw[i]<<'\n';
	}
	else cout<<"NO\n";
}
void main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n>>m;
	per(i,1,n) cin>>c[i];
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		e[u].epb(v,i);
		e[v].epb(u,i);
	}
	dep[0]=-1;dfs(1,0);
	if(!c[1]) return print(1);
	if(c[1]&1) return print(0);
	per(u,1,n) for(auto x:e[u]) if(!in[x.id]){
		if((dep[u]+dep[x.v])&1) continue;
		bw[x.id]=(dep[u]&1?-1:1)*c[1]/2;
		c[u]-=bw[x.id];c[x.v]-=bw[x.id];
		fill(vis+1,vis+n+1,0);
		dfs(1,0);
		return print(1);
	}
	return print(0);
}}
signed main(){
	fisher::main();	
	return 0;
}
```

---

## 作者：XL4453 (赞：2)

### $\text{Difficulty : 2700}$
---
### 解题思路：

首先想到如果是一棵树的话会非常简单，直接从叶子结点出发，依次向上推导，最后只需要判断根节点是否可行就结束了。

然后一个图的话可以理解为在这个树的基础上加上了若干边，考虑对于这些个边加上权值之后的影响。由于之前做法的限制，背离根的方向进行更改的话一定是不优的，除了根节点以外的所有点都一定是满足条件的了。只能往上变动就简单多了，对于之前答案的扰动一定是一正一负这样交替，如果新边链接到两个点到最近公共祖先的距离的奇偶性一样则该扰动会以两倍的大小继续向上影响到根节点，否则就直接抵消了。

问题的关键就在于新加入的一些形成奇环的边，这些边更改若干权值都会影响到根节点的情况，可以预见的是这些边只能造成偶数的影响，由此就可以在完成任意一棵生成树之后判断是否可行。

另一个不会在代码中体现但是需要注意到的点就是值权值的大小问题，由于每一个点权绝对值最大为 $n$，最后根节点和初始值的偏差一定不超过 $n^2+n$，$2n^2$ 的最大权值是绝对够用的。

注意开 $\text{long long}$。

---
### 代码：
```cpp
#include<cstdio>
#include<cstring>
using namespace std;
#define int long long
const int MAXN=400005;
int n,m,c[MAXN],head[MAXN],nxt[MAXN],id[MAXN],num[MAXN],f[MAXN];
int w[MAXN],dep[MAXN],T[MAXN],v[MAXN],x[MAXN],y[MAXN],tot;
void add(int x,int y,int z){
	nxt[++tot]=head[x];
	head[x]=tot;
	num[tot]=y;
	id[tot]=z;
}
void dfs(int now,int fa,int deep){
	dep[now]=deep;v[now]=1;
	int note=-1;f[now]=fa;
	for(int i=head[now];i;i=nxt[i]){
		if(num[i]==fa)note=i;
		else {
			if(v[num[i]]==0){
				T[id[i]]=1,dfs(num[i],now,deep+1);
			}
		}
	}
	if(note!=-1){
		w[id[note]]+=c[now];
		c[fa]-=c[now];
		c[now]=0;
	}
}
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)scanf("%lld",&c[i]);
	for(int i=1;i<=m;i++){
		scanf("%lld%lld",&x[i],&y[i]);
		add(x[i],y[i],i);add(y[i],x[i],i);
	}
	dfs(1,0,0);
	if(c[1]==0){
		printf("YES\n");
		for(int i=1;i<=m;i++)printf("%lld\n",w[i]);
		return 0;
	}
	if(c[1]%2==0){
		int flag=0;
		for(int i=1;i<=m;i++){
			if(T[i]==1)continue;
			if((dep[x[i]]+dep[y[i]])%2==0){
				if(dep[x[i]]%2==0)w[i]=c[1]/2;
				else w[i]=-c[1]/2;
				c[x[i]]-=w[i];c[y[i]]-=w[i];
				memset(v,0,sizeof(v));
				dfs(1,0,0);
				flag=1;
				break;
			}
		}
		if(flag){
			printf("YES\n");
			for(int i=1;i<=m;i++)printf("%lld\n",w[i]);
		}
		else{
			printf("NO\n");
		}
	}
	else printf("NO\n");
	return 0;
}
```


---

## 作者：shinkuu (赞：1)

这种题稍微联想一下类似的就差不多秒掉了。

对于这种要求一条边的权值和两个点有关的构造，找到一个欧拉回路/环类似物，将一条路径每条边的边权依次设成 $x,-x$，可能会有很好的性质。

令下面的“点权”代表所有相邻边权之和，而不是题目所给的 $c$。

对于这题，考虑像上面那样找出一个环构造会发生什么。由于相邻两条边的边权分别加上成 $x,-x$，若环长度为偶数什么都不会发生。若为奇数，容易发现其中有一个点的权值会增加 $2x$，其他什么都不会发生。

同时容易发现，若选出一条 $u$ 到 $v$ 的路径，依次将边权加上 $x,-x$，则 $u$ 的点权会加上 $x$，$v$ 的点权也会发生一些变化。

于是这个图有奇环时的做法已经很显然了：令 $u$ 为奇环上的一点，以其为根拎出一棵生成树，并用上面的方法，对于所有不为 $u$ 的点 $v$，找到 $v$ 到 $u$ 的路径，可以在树上做一个差分，将 $v$ 的点权调整，最后再用这个奇环调整 $u$ 的点权。

为什么这样是对的？首先，树上差分的部分，每条边至多被 $n$ 个点影响，所以此时边权 $w\in[-n^2,n^2]$。然后在奇数环上的调整，由于此时 $u$ 点权 $c$ 也同样有 $c\in[-n^2,n^2]$，所以奇环上的 $x\in[-\frac{n^2}{2},\frac{n^2}{2}]$，加起来的 $w\in [-2n^2,2n^2]$。由于 $c_i$ 和 $deg_i$ 奇偶性相同所以不用考虑奇偶性的问题。

至于原图为二分图的情况，首先容易发现，由于每条边连接一个左部点和一个右部点，所以左部点的点权和一定等于右部点的，否则无解。

然后想到，既然无法调整 $n-1$ 个点再调整剩下一个，那就想是否能调整 $n-2$ 个点后，再让剩下两个点一起调整。

具体地，考虑在左部点和右部点中分别选出一个，和有奇环地情况一样，先将除了这两个点之外的都调整完，然后发现，由于是二分图，所以这两个点之间的路径一定是奇数长度。若找出一条路径，将边权依次加上 $x,-x$，则这两个点的点权会同时增加 $x$。由于已经保证有解，于是这样调整一定可以调整成功。

证明和奇环的情况同理，一定也不会超过 $[-2n^2,2n^2]$。于是做完了。

code：

```cpp
int n,m,c[N],deg[N],col[N],fa[N],id[N];
ll f[N],g[N],h[N];
int fl,sx,sy,se;
bool pd[N];
int tot,head[N];
struct node{
	int to,nxt;
}e[N<<1];
il void add(int u,int v){
	e[++tot]={v,head[u]},head[u]=tot;
}
void dfs1(int u,int F){
	fa[u]=F;
	go(i,u){
		int v=e[i].to;
		if(col[v]){
			if(col[v]==col[u]){
				fl=1,sx=u,sy=v,se=(i+1)/2;
			}
			continue;
		}
		pd[(i+1)/2]=1;
		col[v]=3-col[u];
		dfs1(v,u);
	}
}
void dfs2(int u,int F){
	fa[u]=F,f[u]=c[u]-deg[u];
	go(i,u){
		int v=e[i].to;
		if(!pd[(i+1)/2]||v==F){
			continue;
		}
		id[v]=(i+1)/2;
		dfs2(v,u);
		g[(i+1)/2]+=f[v];
		f[u]-=f[v],f[v]=c[v];
	}
}
void dfs3(int u,int F,int s){
	fa[u]=F;
	if(col[u]==col[s]&&u!=s){
		h[u]+=c[u]-deg[u];
		f[u]=c[u];
	}
	go(i,u){
		int v=e[i].to;
		if(!pd[(i+1)/2]||v==F){
			continue;
		}
		id[v]=(i+1)/2;
		dfs3(v,u,s);
		g[(i+1)/2]+=h[v];
		h[u]-=h[v],h[v]=0;
	}
}
void Yorushika(){
	read(n,m);
	rep(i,1,n){
		read(c[i]);
	}
	rep(i,1,m){
		int u,v;read(u,v);
		add(u,v),add(v,u);
		deg[u]++,deg[v]++;
	}
	col[1]=1,dfs1(1,0);
	rep(i,1,n){
		f[i]=deg[i];
	}
	rep(i,1,m){
		g[i]=1;
	}
	if(fl){
		dfs2(sx,0);
		ll d=f[sx]/2,u=sy;
		while(u!=sx){
			if(col[u]==col[sx]){
				g[id[u]]-=d;
			}else{
				g[id[u]]+=d;
			}
			u=fa[u];
		}
		g[se]+=d;
	}else{
		ll x=0,y=0;
		rep(i,1,n){
			if(col[i]==1){
				x+=c[i];
			}else{
				y+=c[i];
			}
		}
		if(x!=y){
			puts("NO");
			return;
		}
		int u=1,v=0;
		rep(i,1,n){
			if(col[i]!=col[1]){
				v=i;
				break;
			}
		}
		dfs3(u,0,u);
		h[u]=0,dfs3(v,0,v);
		ll d=c[v]+h[v]-deg[v];
		while(u!=v){
			if(col[u]==col[v]){
				g[id[u]]-=d;
			}else{
				g[id[u]]+=d;
			}
			u=fa[u];
		}
	}
	puts("YES");
	rep(i,1,m){
		printf("%lld\n",g[i]);
	}
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

---

## 作者：Union_of_Britain (赞：1)

存在奇环是容易构造的。由奇偶性条件知道跑一颗奇环基环树出来从下往上构造，环上解方程就可以得到解。

不存在奇环由于数据范围不大，图是二分图，可以直接跑网络流得到方案。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=4e5+5,INF=1e18;
int n,m,c[maxn],vis[maxn],U[maxn],V[maxn],vise[maxn],res[maxn];
int pid[maxn],eid[maxn],onc[maxn];
vector<pair<int,int> > e[maxn],T[maxn];
map<pair<int,int>,int> mp;
void dfs(int u){
	vis[u]=1;
	for(auto [v,id]:e[u]){
		if(vis[v])continue;
		vise[id]=1;
		mp[{u,v}]=mp[{v,u}]=id;
		T[u].push_back({v,id});
		T[v].push_back({u,id});
		dfs(v);
	}
}
void solve(int u,int fa){
	for(auto [v,id]:T[u]){
		if(onc[v]||v==fa)continue;
		solve(v,u);res[id]=c[v];c[u]-=res[id];
	}
}
int stk[maxn];int tp=0,flg=0;
void path(int u,int fa,int t){
	stk[++tp]=u;
	if(u==t)return flg=1,void();
	for(auto [v,id]:T[u]){
		if(v==fa)continue;
		path(v,u,t);
		if(flg)return ;
	}
	--tp;
}
namespace Flow{
	struct edge{
		int u,v,c,f;
	};
	vector<edge> G;
	vector<int> e[maxn];
	queue<int> q;
	int n,s,t;
	int d[maxn],cur[maxn];
	void add_edge(int u,int v,int c){
		G.push_back({u,v,c,0});
		G.push_back({v,u,0,0});
		e[u].push_back(G.size()-2);
		e[v].push_back(G.size()-1);
	}
	bool bfs(){
		for(int i=1;i<=n;i++)d[i]=INF;
		d[s]=0;q.push(s);
		while(!q.empty()){
			int u=q.front();q.pop();
			for(auto E:e[u]){
				if(d[G[E].v]>d[u]+1&&G[E].c>G[E].f){
					d[G[E].v]=d[u]+1;
					q.push(G[E].v);
				}
			}
		}
		return d[t]<INF;
	}
	int dfs(int u,int lst){
		if(u==t||!lst)return lst;
		int flow=0,F;
		for(int &i=cur[u];i<e[u].size();i++){
			int E=e[u][i],v=G[E].v,c=G[E].c,f=G[E].f;
			if(c>f&&d[v]==d[u]+1&&(F=dfs(v,min(lst,c-f)))>0){
				G[E].f+=F,G[E^1].f-=F;
				flow+=F;lst-=F;
				if(lst==0)break;
			}
		}
		return flow;
	}
	int solve(){
		int ans=0;
		while(bfs()){
		for(int i=1;i<=n;i++)cur[i]=0;
			ans+=dfs(s,INF);
		}
		return ans;
	}
}
namespace LCA{
	int dep[maxn],son[maxn],to[maxn],sze[maxn],fa[maxn];
	void dfs1(int u,int f){
		fa[u]=f,dep[u]=dep[f]+1;
		for(auto [v,id]:T[u]){
			if(v==f)continue;
			dfs1(v,u);
			sze[u]+=sze[v];
			if(sze[v]>sze[son[u]])son[u]=v;
		}
	}
	void dfs2(int u,int t){
		to[u]=t;
		if(son[u])dfs2(son[u],t);
		for(auto [v,id]:T[u])if(v!=fa[u]&&v!=son[u])dfs2(v,v);
	}
	int LCA(int u,int v){
		while(to[u]!=to[v]){
			if(dep[to[u]]<dep[to[v]])swap(u,v);
			u=fa[to[u]];
		}
		return dep[u]<dep[v]?u:v;
	}
	int dis(int u,int v){
		return dep[u]+dep[v]-2*dep[LCA(u,v)];
	}
}
int col[maxn],deg[maxn];
void getcol(int u){
	if(col[u]==-1)col[u]=0;
	for(auto [v,id]:e[u]){
		if(col[v]==-1){
			col[v]=col[u]^1;
			getcol(v);
		}
	}
}
int d[maxn],cc[maxn];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>c[i],cc[i]=c[i];
	for(int i=1;i<=m;i++)cin>>U[i]>>V[i],e[U[i]].push_back({V[i],i}),e[V[i]].push_back({U[i],i});	
	dfs(1);LCA::dfs1(1,0);LCA::dfs2(1,1);
	int C=2*n*n;
	if(m==n-1){
		onc[1]=1;solve(1,0);
	}else{
		int pos=0;
		for(int i=1;i<=m;i++)if(!vise[i]&&LCA::dis(U[i],V[i])%2==0)pos=i;
		if(pos){
			path(U[pos],0,V[pos]);
			for(int i=1;i<=tp;i++)pid[i]=stk[i],eid[i]=mp[{pid[i],stk[i+1]}],onc[pid[i]]=1;
			eid[tp]=pos;for(int i=1;i<=tp;i++)vise[eid[i]]=1;
			for(int i=1;i<=tp;i++)solve(pid[i],0);int b=0;
			for(int i=2;i<=tp;i++)b=c[pid[i]]-b;
			res[eid[1]]=(c[pid[1]]-b)/2;for(int i=2;i<=tp;i++)res[eid[i]]=c[pid[i]]-res[eid[i-1]];
		}else{
			for(int i=1;i<=n;i++)col[i]=-1;
			getcol(1);
			Flow::n=n+2,Flow::s=n+1,Flow::t=n+2;
			for(int i=1;i<=m;i++){
				if(col[U[i]]==1)swap(U[i],V[i]);
				deg[U[i]]++,deg[V[i]]++;
				Flow::add_edge(U[i],V[i],2*C);
			}
			for(int i=1;i<=n;i++){
				if(col[i]==0)Flow::add_edge(Flow::s,i,C*deg[i]+c[i]);
				else Flow::add_edge(i,Flow::t,C*deg[i]+c[i]);
			}
			Flow::solve();
			for(int i=0;i<2*m;i+=2)res[i/2+1]=Flow::G[i].f-C;
		}
	}
	bool flg=1;
	for(int i=1;i<=m;i++)d[U[i]]+=res[i],d[V[i]]+=res[i],flg&=(-C<=res[i]&&res[i]<=C);
	for(int i=1;i<=n;i++)flg&=(d[i]==cc[i]);
	if(!flg)return cout<<"NO"<<endl,0;
	cout<<"YES"<<endl;
	for(int i=1;i<=m;i++)cout<<res[i]<<endl;
	cout<<endl;
	return 0;
}
```

---

