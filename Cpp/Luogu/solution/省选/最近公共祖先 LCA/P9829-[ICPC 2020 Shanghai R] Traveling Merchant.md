# [ICPC 2020 Shanghai R] Traveling Merchant

## 题目描述

劳伦斯先生是一位在不同城市转售商品的旅行商人。基本地，为了赚钱，他需要以低价买进商品，再以高价卖出。现在请你为他规划一条可以一直盈利的旅行路线。

简单地说，假设有 $n$ 座城市，标号为 $0$ 到 $n-1$ ，以及 $m$ 条连接特定两座城市的路，劳伦斯先生可以通过这些路到访每座城市。最初劳伦斯先生位于第 $0$ 座城市，并且对于城市 $i$ 都有一个起始价格 $c_i$ 。根据市场规律，当他从城市 $i$ 来到相邻的城市 $j$ 时（当且仅当城市 $i$ 与城市 $j$ 之间有路径相连时，才称 $i$ 与 $j$ 为相邻城市），城市 $i$ 的价格状况会发生变化（高价会变成低价，低价也可能变成高价）。而因为一些原因（比如商品的新鲜程度，旅行费用，税务等），他**必须**：

- 从城市 $0$ 出发并在城市 $0$ 购买一些商品。保证城市 $0$ 的起始价格很**低**。
- 每当他到达一座城市后，他**必须**售卖**或**购买一些商品。
- 若他在城市 $i$ 购买了商品，他就必须去一座与 $i$ 相邻且价格 $c_j$ **高于** $c_i$ 的城市 $j$ ，并在那里卖掉手中来自城市 $i$ 的商品。
- 若他在城市 $i$ 售卖了商品，他就必须去一座与 $i$ 相邻且价格 $c_j$ **低于** $c_i$ 的城市 $j$，并在那里购买一些商品。


因此，最终路径会始终重复 ``低价购入`` 和 ``高价卖出`` 。

一条无尽的盈利路线由无尽的城市序列 $p_0,p_1 \dots$ 组成。其中，城市 $p_i$ 与城市 $p_{p+1}$ 之间有路径相连，$p_0 = 0$，且价格高低是交替循环的，也就是说当 $k \ge 0$ 时，城市 $p_{2k}$ 的价格 $c_{p_{2k}} = \text{Low}$ (要在这个城市购买商品) 而相邻城市 $p_{2k+1}$ 的价格 $c_{p_{2k+1}} = \text{Hign}$ (要在这个城市卖出商品)。

**注意**：$c_{p_i}$ 是 **到达** 城市 $p_i$ 时的价格，而当他第二次到达城市 $p_i$ 时，这个价格可能会因为市场规律而变化。

你需要写一个程序，判断是否有这样一条永远盈利的路径存在。

## 样例 #1

### 输入

```
2
4 4
LHLH
0 1
1 2
1 3
2 3
3 3
LHH
0 1
0 2
1 2```

### 输出

```
yes
no```

# 题解

## 作者：鲤鱼江 (赞：9)

题被出到了模拟赛，顺手写一篇题解。

我们将 $H$ 和 $L$ 当做黑白两种颜色，两个端点颜色不同的边叫做异色边，否则叫做同色边。

不难发现一个环可以一直走下去的当且仅当：这个环上有且仅有一条同色边且同色边连接的两个点中有一个可以用作起点。

信息量可能有点大，一条一条解释。

1. 是一个环：显然，因为你肯定不能往回走。
2. 有一条同色边：因为离开一个点后会使其颜色反转，所以相当于将与该点相连的所有边的状态改变，所以如果没有同色边，最后便无法回到起点。
3. 仅有一条同色边：只有在返回起点时需要用到同色边，其他同色边走了不优。
4. 有一个作为起点：如上分析都建立在起点是同色边端点上的，若起点不是同色边端点，则说明我们走到其中一个同色边端点时就无法回溯到另一个端点（否则与这些点形成环相矛盾，直接回溯肯定会使一些点未被遍历到）。

综上便是本题用到的所有性质，我们来思考究竟怎么维护。

因为恰好一条同色边的条件很苛刻，所以可以先把异色边加入，再枚举同色边，若同色边的两个端点在异色边的生成子图上连通，则前三条性质都满足了，我们只需要对第四条性质进行判定。

不难发现问题等价与 $1$ 号节点能否在不经过环上节点的情况下到达同色边的一个端点，此时可以考虑点双。

点双的性质之一：对于任意互异三点 $x$、$y$、$z$，存在一条 $x\to z$ 的路径不经过 $y$。

所以点双的想到应是很自然的，然后以一为根遍历一下园方树，判一下子树即可，细节不多。

```cpp
#include<bits/stdc++.h>

using namespace std;

namespace Fread {
	const int SIZE=1<<21;char buf[SIZE],*S,*T;
	inline char getchar() {if(S==T){T=(S=buf)+fread(buf,1,SIZE,stdin);if(S==T)return '\n';}return *S++;}
}
namespace Fwrite {
	const int SIZE=1<<21;
	char buf[SIZE],*S=buf,*T=buf+SIZE;
	inline void flush(){fwrite(buf,1,S-buf,stdout);S=buf;}
	inline void putchar(char c){*S++=c;if(S==T)flush();}
	struct POPOSSIBLE{~POPOSSIBLE(){flush();}}ztr;
}
#define getchar Fread :: getchar
#define putchar Fwrite :: putchar
namespace Fastio{
	struct Reader{
	    template<typename T>
    	Reader& operator >> (T& x) {
        	char c=getchar();T f=1;
        	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}x=0;
        	while(c>='0'&&c<='9'){x=x*10+(c-'0');c=getchar();}x*=f;
	        return *this;
    	}
	    Reader& operator >> (char& c) {c=getchar();while(c==' '||c=='\n')c=getchar();return *this;}
	    Reader(){}
	}cin;
	struct Writer{
	    template<typename T>
	    Writer& operator << (T x) {
	        if(x==0){putchar('0');return *this;}
	        if(x<0){putchar('-');x=-x;}
	        static int sta[45];int top=0;
	        while(x){sta[++top]=x%10;x/=10;}
	        while(top){putchar(sta[top]+'0');--top;}
	        return *this;
    	}
    	Writer& operator << (char c) {putchar(c);return *this;}
    	Writer& operator << (const char* str){int cur=0;while(str[cur])putchar(str[cur++]);return *this;}
    	Writer(){}
	}cout;
}
#define endl '\n'
#define cin Fastio :: cin
#define cout Fastio :: cout

const int N=6e5+10;
struct edge{
	int to,ne;
	edge(int to=0,int ne=0):
		to(to),ne(ne){;}
}a[N<<1];
int h[N],cnt,n,m,bel[N],flag[N],tot,stk[N],Top,dfn[N],T,col[N];
int X[N],Y[N],f[N],root[N],low[N],idx,dep[N],id[N],IDX,siz[N];
vector < int > v[N];vector < int > p[N];char in;

/*
	1.图不一定连通，所以树也不一定连通。
	2.tot的初值
*/

void clear(){
	for(int i=1;i<=m;++i) X[i]=Y[i]=0;
	for(int i=1;i<=tot;++i){
		h[i]=bel[i]=flag[i]=stk[i]=dfn[i]=root[i]=low[i]=dep[i]=col[i]=0;
		v[i].clear();p[i].clear();
	}
	for(int i=1;i<=cnt;++i) a[i]=edge();
	cnt=tot=Top=idx=0;
}

inline void add(const int x,const int y){a[++cnt]=edge(y,h[x]);h[x]=cnt;}

void tarjan(const int x,int rt){
	dfn[x]=low[x]=++idx;stk[++Top]=x;
	if(x==rt&&v[x].empty()){--Top;p[++tot].emplace_back(x);if(!flag[x]) bel[x]=tot;return ;}
	int ct=0,tmp;
	for(int i:v[x]){
		if(!dfn[i]){
			tarjan(i,rt);
			low[x]=min(low[x],low[i]);
			if(low[i]>=dfn[x]){
				++ct;if(x!=rt||ct>1) flag[x]=1,bel[x]=0;++tot;
				if(!flag[x]) bel[x]=tot;
				p[tot].emplace_back(x);
				while(stk[Top+1]!=i){
					tmp=stk[Top--];
					p[tot].emplace_back(tmp);
					if(!flag[tmp]) bel[tmp]=tot;
				}
			}
		}else low[x]=min(low[x],dfn[i]);
	}
}

inline int In(const int x,const int y){return id[y]<=id[x]&&id[x]<=id[y]+siz[y]-1;}
void dfs(int x,int y,int rt){
	id[x]=++IDX;f[x]=y;root[x]=rt;dep[x]=dep[y]+1;siz[x]=1;
	for(int i=h[x];i;i=a[i].ne) if(a[i].to!=y) dfs(a[i].to,x,rt),siz[x]+=siz[a[i].to];
}

int main(){
	freopen("travel.in","r",stdin);
	freopen("travel.out","w",stdout);
	cin>>T;
	while(T--){
		cin>>n>>m;tot=n;int fg=0;
		for(int i=1;i<=n;++i){cin>>in;col[i]=(in=='H');}
		for(int i=1;i<=m;++i){
			cin>>X[i]>>Y[i];
			if(col[X[i]]!=col[Y[i]]){
				v[X[i]].emplace_back(Y[i]);
				v[Y[i]].emplace_back(X[i]);
			}
		}
		tarjan(1,1);
		for(int i=n+1;i<=tot;++i) for(auto j:p[i]) if(flag[j]){add(j,i);add(i,j);}
		for(int i=1;i<=n;++i) if(flag[i]) bel[i]=i;
		dfs(bel[1],0,bel[1]);
		for(int i=1;i<=m;++i){
			if(col[X[i]]!=col[Y[i]]) continue;
			if(X[i]==Y[i]) continue;
			int x=bel[X[i]],y=bel[Y[i]];
			if(root[x]!=bel[1]||root[y]!=bel[1]) continue;
    		if(flag[x]&&x!=1) x=f[x];
    		if(flag[y]&&y!=1) y=f[y];
			if((fg|=In(x,y)||In(y,x))) break;
		}
		cout<<(fg?"yes\n":"no\n");
		clear();
	}
	return 0;
}
```

---

## 作者：George_Plover (赞：6)



### Update (2023)

偶然发现这场居然在洛谷重现了，那正好是时候祭出这篇 3 年前的题解了！

### 题意：

​		在一张有 $n$ 个点 $m$ 条边 $(n,m\leq 2\times10^5)$ 的简单图上，每个点有一个状态 $c_i$ 。状态只有两种，不妨令状态为 0 或 1 。

​		0 号节点的状态一定是 0。现在旅行商行要从 0 号节点开始，不断走，他的路径必须是 010101 交错的。此外，每当他离开一个节点，该节点状态会立刻取反。题目问，他是否能找到一种方案，可以无限走下去。输出 yes 和 no。



### 分析：

​		说实话，赛场上，我是看到题目名称非常经典，才决定看看这道题的……

#### 第一步思考：

​		商人想要无限制走下去，那么他的路径必须成环。考虑他第一次成环的时候。也就是假设他当前在 $u$ ，将要走向 $v$ ，而 $v$ 是一个已经到达过一次的点。如果 $u$ 能够走上 $v$ ，考虑到 $v$ 已经被反转一次了，因此必然在原图上满足 $c_v=v_u$ ，也就是 $u,v$ 同色。然后，他就可以从 $v$ 继续沿着第一次走过的路走下去了，并且不断沿着这个环无止境走下去。

​		也就是说，一旦成环，就能无限制走下去。

​		这个环，一定是一个奇环，而且必然满足这样的性质：通过走颜色交错的路径能够先到达 $v$，然后 $v$ 继续走交错路径到达 $u$，$c_u=c_v$ 且 $u,v$ 之间存在连边，那么在 $(u,v)$ 处，就可以成环。

​		所以就是要判断是否存在上述的这个结构。

​		例如下图中，能够从 0 走交错路到 2；2 走交错路到 6；然后 2，6 同色，就能够走上环。这时存在满足题意的路径：$[0,1,(2,7,10,12,9,11,6)^{\infin} ]$

![](https://cdn.luogu.com.cn/upload/image_hosting/836wip0h.png)

#### 第二步思考：

​		成环的关键是一条连接同色点的边。那么可以考虑先从原图 $G$ 导出所有连接异色点的边，得到一张子图 $H$。然后考虑加入连接同色点的边，看看能否构成满足题意的路径。可以看到，对于上面的图，导出所有异色连边就是下面的样子（同色连边淡化掉，假装没有）

![](https://cdn.luogu.com.cn/upload/image_hosting/ind9boso.png)

​		那么问题就变得清晰了。对于每条连接同色点的边 $(u,v)$ ，我们需要知道，在图 $H$ 上，是否存在一条从 $0$ 到 $u$ 再到 $v$ 的简单路径（或者从 $0$ 到 $v$ 再到 $u$ 的简单路径）。

​		如果存在某一条连接同色点的边 $(u,v)$ ，满足在 $H$ 上存在这样的路径，那么答案就是 yes，否则就是 no。

​		如何判断是否存在这样的简单路径呢？

​		我们发现，将图 $H$ 求出点双连通分量后，可以构造“分量-割点”树 $T$。如下图：(大的圆表示点双分量，小圆表示割点)

![](https://cdn.luogu.com.cn/upload/image_hosting/yqbm9iw5.png)

​		如果说存在某一条连接同色点的边 $(u,v)$，$u$ ,$v$ 分别在 $T$ 上对应的点为 $U,V$，如果 $U,V$ 在 $T$ 上存在祖孙关系，那么在 $H$ 上就存在上面所说的简单路径。



#### 算法流程：

​		先把异色连边取出，得到图 $H$，跑Tarjan求点双，根据点双包含的割点，构造“分量-割点”树 $T$。接下来遍历原来的同色连边。对于同色连边的 $u,v$，分别在 $T$ 中所属分量 $U=belong(u),V=belong(v)$，如果 $U,V$ 在 $T$ 上具有祖孙关系（求 LCA，看 LCA 是不是 $U,V$ 中的某一个）,那么输出 yes。如果遍历的同色连边都没有成功，就输出 no。

​		（对于 $u$ 或者 $v$ 是割点的情况，令其 belong() 是 $T$ 上它的父亲节点代表的分量就可以了）

#### 关于正确性

要点在于证明点双分量中任何三个不同的点 A、B、C，存在一条 A->B->C 且不重复经过点的路径。（证明有空补上）



#### 一点感悟：

​		2020 年暑假最后一场校内积分赛，有一道题决胜，就是一道点双建树求 LCA 的题目（HDU4338）。此前我从来没有写过点双。当时我最后也没有调出来。那时候很沮丧，明明是个板子的题，但我却因为从来没写过，就自己建了个错误的模型。

​		但是那天之后我就死磕了一下那道题，在 HDU 交了 20 多发，终于找到了细节 bug，还写了一篇[博客](https://www.luogu.com.cn/blog/George-Plover/hdu-4338simple-path-dian-shuang-lian-tong-fen-liang)来记录这道题。

​		到这里，形成了呼应。若当时我没有花一下午加一晚上去调试那道题目，那我在 ICPC 的赛场上，也就会和暑假末的积分赛一样，死也调不出这道 K 题了。

​		正是因为 3 个多月前的自己不屈不挠把那道题目弄明白了，才造就了我，在赛场上，最后 25 分钟时的幡然醒悟，把挂了 8 发的 K 题，重构一下，改对了。

​		谨以此题解感谢过去努力的自己。



#### 比赛时的 AC 代码：

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define MAXN 1020000

using namespace std;
int T,n,m;
char c[MAXN];
struct Edge{
	int l,r;
}e[MAXN];
int tot,pre[MAXN],lin[MAXN*10],to[MAXN*10];
int dfn[MAXN],low[MAXN],stk[MAXN],top;
int siz[MAXN],dep[MAXN],up[MAXN],fa[MAXN],son[MAXN];
int belong[MAXN];
bool vis[MAXN];
vector<int> dcc[MAXN];
int cnt,num;
bool cut[MAXN];
void init()
{
	tot=top=cnt=num=0;
	for(int i=1;i<=3*n+3;i++)
	{
		dcc[i].clear();
		dfn[i]=low[i]=fa[i]=dep[i]=up[i]=son[i]=belong[i]=pre[i]=0;
		vis[i]=0;
		cut[i]=0;
	}
}
void add(int x,int y)
{
	tot++;lin[tot]=pre[x];pre[x]=tot;to[tot]=y;
}

void Tarjan(int x,int root)
{
	dfn[x]=low[x]=++num;
	stk[++top]=x;
	if(x==root && pre[x]==0)
	{
		++cnt;
		dcc[++cnt].push_back(x);
		if(!cut[x])
			belong[x]=cnt;
		return;;
	}
	int flag=0;
	for(int i=pre[x];i;i=lin[i])
	{
		int v=to[i];
		if(!dfn[v])
		{
			Tarjan(v,root);
			low[x]=min(low[x],low[v]);
			if(low[v]>=dfn[x])
			{
				flag++;
				if(x!=root || flag>1)cut[x]=true;
				cnt++;
				int z;
				do
				{
					z=stk[top--];
					dcc[cnt].push_back(z);
					if(!cut[z])
						belong[z]=cnt;
				}while(z!=v);
				dcc[cnt].push_back(x);
				if(!cut[x])
						belong[x]=cnt;
			}
		}
		else low[x]=min(low[x],dfn[v]);
	}
}

void dfs(int x)
{
	vis[x]=1;
	siz[x]=1;
	for(int i=pre[x];i;i=lin[i])
	{
		int v=to[i];
		if(v!=fa[x] && !vis[v])
		{
			fa[v]=x;
			dep[v]=dep[x]+1;
			dfs(v);
			siz[x]+=siz[v];
			if(siz[v]>siz[son[x]])
				son[x]=v;
		}
	}
}
void dfs2(int x)
{
	vis[x]=1;
	if(x==son[fa[x]])
		up[x]=up[fa[x]];
	else
		up[x]=x;
		
	for(int i=pre[x];i;i=lin[i])
	{
		int v=to[i];
		if(v!=fa[x] && !vis[v])
			dfs2(v);
	}
}
int lca(int x,int y)
{
	while(up[x]!=up[y])
	{
		if(dep[up[x]]<dep[up[y]])
		{
			int t=x;x=y;y=t;
		}
		x=fa[up[x]];
	}
	return dep[x]>dep[y]?y:x;
}

inline int val(int x)
{
	if(cut[x])return n+n+x;
	return belong[x]+n;
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
    	
    	scanf("%d%d",&n,&m);
    	init();
    	
    	scanf("%s",c+1);
    	for(int i=1;i<=m;i++)
    	{
    		scanf("%d%d",&e[i].l,&e[i].r);
    		e[i].l++;e[i].r++;
    		if(c[e[i].l]!=c[e[i].r])
    		{
    			add(e[i].l,e[i].r);
    			add(e[i].r,e[i].l);
    		}
    	}
    	
    	Tarjan(1,1);
    	for(int i=1;i<=cnt;i++)
    	{
    		for(int j=0;j<dcc[i].size();j++)
    		{
    			if(cut[dcc[i][j]])
    			{
    				add(val(dcc[i][j]),i+n);
    				add(i+n,val(dcc[i][j]));
    			}
    		}
    	}
    	
    	dfs(val(1));//cout<<"!";
    	for(int i=1;i<=3*n+3;i++)vis[i]=0;
    	dfs2(val(1));
    	
    	bool flag=0;
    	
    	for(int i=1;i<=m&&!flag;i++)
    	{
    		if(c[e[i].l]==c[e[i].r])
    		{
    			if(!dfn[e[i].l] || !dfn[e[i].r])continue;
    			int u=val(e[i].l),v=val(e[i].r);
    			if(cut[e[i].l] && e[i].l!=1)u=fa[u];
    			if(cut[e[i].r] && e[i].r!=1)v=fa[v];
    			int LCA=lca(u,v);
    			
    			if(u==LCA||v==LCA)
    			{
    				flag=1;
    			}
    		}
    	}
    	if(flag)
    		printf("yes\n");
    	else
    		printf("no\n");
    }
    return 0;
}

```













---

## 作者：RiceFruit (赞：2)

糖丸了，赛场上 `Tarjan` 没调出来

## 思路

考虑你走的路径，不妨设 $(u,v)$ 为第一次走到重复的点的边，然后我们一直走这个环即可满足条件。那么 $1-u$ 的路径必然都是异色边，于是原问题等价于：给你一张无向图，再给你若干条边 $(u,v)$，判断是否存在一条简单路径满足从 $1$ 到 $u$ 再到 $v$，接下来给出做法。

## 做法

结论：设 $w$ 为 $u$ 和 $v$ 的 `lca` **的父节点**，那么结论就是 $u$ 和 $w$ 属于同一个点双，正确性读者自证不难。

但是有一个小问题，就是 $w$ 正好是 $u$ 这个点双的上割点，所以还要特判 $w$ 正好为 $u$ 点双的割点的情况。

## 代码

有点丑，不放了

---

## 作者：chen_zhe (赞：1)

以下内容转载自官方题解：

观察发现，一旦能走到一个已经访问过的点，则可以模仿这个点之后，上一次使用的路径并无限重复。这样的路径在最开始的图中，是一条 $L$ 和 $H$ 相间的路径，并且路径的最后一个点和路径中的某一个同色（同 $L$ 或同 $H$）点有边。

使用异色边（原图中连接 $H$ 和 $L$ 的边）建图，对于每条同色边 $(u,v)$ 检查是否存在 $0\to u\to v$ 或 $0\to v\to u$ 的简单路径，如果有则存在一条上述的无限重复路径。设 $u$ 和 $v$ 在 dfs 树中的 lca 为 $w$（不妨假设 $w$ 不为 $u$ 或 $v$），存在这样的路径等价于 $u$（或 $v$）和 $w$ 在同一个点双连通分量内。

---

## 作者：hlsnqdmz (赞：0)

## 前言
这道题的题解不多，而且贴代码的只有一半，而且贴代码的题解的代码也并没有那么好懂，导致我花了一个上午才 AC 了这道题，所以想写一篇相对好懂的题解，防止有人像我一样花费了过多的时间完成这道题。
## 正式开始
稍微吐槽这个题干，明明可以直接说明的经过后翻转颜色，却非要说所谓的价格状况会发生变化，还用了 `可能` 的字眼。简述一下题意：有 $n$ 个点，编号从 $0\sim n-1$，每个点是黑色或者白色，求问如何找到一个环，从环上一个点 $u$ 可以只走异色边（即白色点到黑色点或黑色点到白色点的边）到达环上的点 $v$，$v$ 到 $u$ 有一条同色边（即白色点到白色点或黑色点到黑色点）到达点 $u$，环上有且只有这样一条同色边，且从 0 号点可以只走非环上异色边到点 $u$，这么说看起来有些麻烦，不过应该算是准确的（但愿）。

来说一下这么描述的原因：
1. 一个环：因为你从白点到黑点，白点会变成黑点，导致你无法回头。
2. 只走异色边，如题干所示。
3. 有且只有一条同色边：这个环应除了一条同色边其他都是异色边，同色边是为了返回环上的出发点（并不指 0 号点，当然有的时候环上的出发点是 0 号点），白点走过后变成黑点，就需要一个白点返回这个黑点，这就是同色边的用处，这样我们才有一条无限盈利的道路。
4. 0 号点可以只走非环上的异色边到环上出发点（即点 $u$）：因为从 0 号点出发，你要到出发点才能开始走无限盈利的道路。而非环上的是因为环上一部分走了，无法再走，而继续往前走就只有同色边可走了。

既然已经明确要找的情况的特征，现在的问题就是怎么去精准无误的找到它。我们知道，环上只需要一条同色边，找到满足这个条件的情况条件苛刻，而其他全是异色边的情况或许更好寻找。我们可以想一下，如果异色边全部连上，然后一条条枚举同色边或许更好做。所以我们可以先把异色边全部连上，然后逐一枚举同色边，判断其是否可行。

现在就是如何保证 0 号点可以只走非环上异色边到环上出发点且同色边两端可以只走异色边到达对方，而同色边两端都可以作为出发点，所以只要其中一个满足条件我们就找到满足题意的路径。我们知道，连上异色边的图上与 0 号点相连的点都是 0 号点只走异色边到达的点，只要同色边两端（设为 $u$ 和 $v$）两点都与 0 号点相连就满足条件。而不走环上的点我们可以通过求 LCA 来解决，当前只当 $u$、$v$ 两点的 LCA 是 $u$ 或 $v$ 时，条件才满足，我们可以画图分析：

该图说明为什么 0 号点只能走非环上异色边：
![](https://cdn.luogu.com.cn/upload/image_hosting/nb503hlv.png)

我们看红线走到 $u$ 点，不能返回了但是也不能走同色边，所以无法满足条件，或许有人会认为假如还有别的异色边可以让 $u$ 到 $v$ 呢，那么原来走的边也不是这个环上的边，顺带一提： ~~好丑的图。~~

而两个端点有一个是 LCA 的原因也可以知道了：这样才不会走到环上的边：
![](https://cdn.luogu.com.cn/upload/image_hosting/ntsvuk4a.png)

相信大家都看得出来这里的问题，原题中给出的是图，而求 LCA 的是树，而这个问题就要请到圆方树了，它是处理这些问题的好手，不会的可以先去做一下[铁人两项](https://www.luogu.com.cn/problem/P4630)和[战略游戏](https://www.luogu.com.cn/problem/P4606)。通过圆方树的板子，我们可以将由异色边连起来的图转化成树，然后逐一枚举同色边，其他题解的圆方树板子感觉有些复杂。

而求 LCA 又出现问题了看，可能 $u$ 和 $v$ 是非割点的圆点，这样满足条件但是 LCA 却是它们其中一个连接的方点，而这个问题只要求 LCA 和判断时用的 $u$ 和 $v$ 都是它们连接的方点，而作为割点的圆点就变为作为它父亲的方点，我们发现所有圆点变为的方点都是它的父亲，树剖求 LCA 就行了，另外记得特判 $u$ 或 $v$ 等于 1 的情况（为了方便写代码，我们把所有点的编号都加了 1）。当然也有建完树后没有在点 1 的子树上的点，对于这种直接跳过就行了。

最后谈一嘴清空的问题，这里用 `memset` 会超时，所以有 `for` 循环情况，另外清空是清空所有圆点和方点的数据，只清空 $1\sim n$ 会爆栈。

最后附上丑陋马蜂的代码：
```
//Just Sayori
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#define ll long long
#define rnt register int
#define gr getchar
#define pr putchar
#define N 200005
#define M 1000000007
using namespace std;

inline ll read()
{
    ll x = 0, f = 1;
    char ch = gr();
    while (ch < '0' || ch > '9')
        ch == '-' ? f = -1, ch = gr() : ch = gr();
    while (ch >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + (ch ^ 48), ch = gr();
    return x * f;
}

inline void write(ll x)
{
    static int sta[39], top = 0;
    if (x < 0)
        pr('-'), x = -x;
    do
        sta[++top] = x % 10, x /= 10;
    while (x);
    while (top)
        pr(sta[top--] ^ 48);
}

struct Edge
{
    struct edge
    {
        int v, next;
    } e[N << 2];
    int head[N << 1], cnt;
    inline void tdd(int u, int v)
    {
        e[++cnt] = {v, head[u]}, head[u] = cnt;
        e[++cnt] = {u, head[v]}, head[v] = cnt;
    }
} g, t;
int n, m, tp, bcc, cnt, lca;
int dfn[N], low[N], stack[N];
int u[N], v[N], fa[N << 1], sz[N << 1], top[N << 1], bson[N << 1], deep[N << 1];
bool a[N << 1];

void tarjan(int u)
{
    dfn[u] = low[u] = ++cnt;
    stack[++tp] = u;
    for (rnt i = g.head[u]; i; i = g.e[i].next)
    {
        int v = g.e[i].v;
        if (!dfn[v])
        {
            tarjan(v), low[u] = min(low[u], low[v]);
            if (dfn[u] == low[v])
            {
                bcc++;
                while (stack[tp + 1] != v)
                    t.tdd(bcc, stack[tp--]);
                t.tdd(bcc, u );
            }
        }
        else
            low[u] = min(low[u], dfn[v]);
    }
}

void dfs1(int u, int f)
{
    fa[u] = f, sz[u] = 1;
    deep[u] = deep[f] + 1;
    for (rnt i = t.head[u]; i; i = t.e[i].next)
    {
        int v = t.e[i].v;
        if (v == f)
            continue;
        dfs1(v, u);
        sz[u] += sz[v];
        if (sz[v] > sz[bson[u]])
            bson[u] = v;
    }
}

void dfs2(int u, int tp)
{
    top[u] = tp;
    if (!bson[u])
        return;
    dfs2(bson[u], tp);
    for (rnt i = t.head[u]; i; i = t.e[i].next)
    {
        int v = t.e[i].v;
        if (v == fa[u] || v == bson[u])
            continue;
        dfs2(v, v);
    }
}

int get_lca(int u, int v)
{
    while (top[u] != top[v])
    {
        if (deep[top[u]] < deep[top[v]])
            swap(u, v);
        u = fa[top[u]];
    }
    if (deep[u] > deep[v])
        swap(u, v);
    return u;
}

int main()
{
    int time = read();
    cin.tie(0);
    while (time--)
    {
        char ch;
        bool f = 0;
        bcc = n = read(), m = read();
        for (rnt i = 1; i <= n; i++)
            cin >> ch, a[i] = (ch == 'H');
        for (rnt i = 1; i <= m; i++)
        {
            u[i] = read() + 1, v[i] = read() + 1;
            if (a[u[i]] != a[v[i]])
                g.tdd(u[i], v[i]);
        }
        tarjan(1), dfs1(1, 0), dfs2(1, 1);//这里只用处理点 1 的子树
        for (rnt i = 1; i <= m; i++)
        {
            int x = u[i], y = v[i];
            if (a[x] != a[y])
                continue;
            if (!dfn[x] || !dfn[y])//不是点 1 的子树直接跳过
                continue;
            if (x == 1 || y == 1)//特判 1 的情况
            {
                f = 1;
                break;
            }
            x = fa[x];
            y = fa[y];
            lca = get_lca(x, y);
            if (lca == x || lca == y)
            {
                f = 1;
                break;
            }
        }
        if (!f)
            puts("no");
        else
            puts("yes");
        for (rnt i = 1; i <= bcc; i++)//这里要清空 1~bcc 的数据，手写栈也清空
            dfn[i] = 0, bson[i] = 0, stack[i] = 0, g.head[i] = 0, t.head[i] = 0;
        tp = cnt = g.cnt = t.cnt = 0;
    }
    return 0;
}
```

### 感谢您的观看！

---

