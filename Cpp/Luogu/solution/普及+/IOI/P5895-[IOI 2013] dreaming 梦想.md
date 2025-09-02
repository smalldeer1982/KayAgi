# [IOI 2013] dreaming 梦想

## 题目描述

天地之初，IOI 尚在遥远的梦想之中。

Serpent(水蛇) 生活的地方有 $N$ 个水坑，编号为 $0，\cdots，N - 1$，有 $M$ 条双向小路连接
这些水坑。每两个水坑之间至多有一条路径（路径包含一条或多条小路）相互连接，有些水坑之间根本无法互通(即 $M ≤ N-1$ )。Serpent 走过每条小路需要一个固定的天数，不同的小路需要的天数可能不同。

Serpent 的朋友袋鼠希望新修 $N - M - 1$ 条小路，让Serpent 可以在任何两个水坑间游走。袋鼠可以在任意两个水坑之间修路，Serpent 通过每条新路的时间都是 $L$ 天。

袋鼠希望找到一种修路方式使得修路之后 Serpent 在每两个水坑之间游走的最长时间最短。

**举例说明**

![](https://cdn.luogu.com.cn/upload/image_hosting/3ahroenu.png)


上图中有 $12$ 个水坑 $8$ 条小路 ($N = 12 , M = 8$)。假如 $L = 2$，即 Serpent 通过任何一条新路都需要 $2$ 天。那么，袋鼠可以修建 $3$ 条新路：
- 水坑 $1$ 和水坑 $2$ 之间；
- 水坑 $1$ 和水坑 $6$ 之间；
- 水坑 $4$ 和水坑 $10$ 之间。

![](https://cdn.luogu.com.cn/upload/image_hosting/udp17aas.png)

上图显示了修路后的最终状态。从水坑 $0$ 走到水坑 $11$ 的时间最长，需要 $18$ 天。这是最佳结果，无论袋鼠如何选择修路方式，总会存在一些水坑对，Serpent 需要 $18$ 天或者更长时间从其中一个走到另一个。

## 说明/提示

对于 $100\%$ 的数据，$1 \le N \le 10^5$，$0 \le M \le N-1$，$0 \le A[i],B[i] \le N-1$，$1 \le T[i] \le 10^4$，$1 \le L \le 10^4$。

## 样例 #1

### 输入

```
12 8 2
0 8 4
8 2 2
2 7 4
5 11 3
5 1 7
1 3 1
1 9 5
10 6 3
```

### 输出

```
18
```

# 题解

## 作者：Y25t (赞：3)

**我居然切了一道IOI题！**

------------

由于题目要使最长路径最短，于是很容易想到贪心策略：

**每棵树和其它树连边的点一定是这棵树上能走到的最远距离最短的的点**~~（由于本人语文水平太菜，这句话有点绕 qwq )~~

如果我们把上述的最短距离称作半径 $r$，$1,2,3...$ 是树按照 $r$ 排序后的。那么最后链接成的树应该长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/cx3clmxo.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

那么最后的答案只有三种情况：

1、原树的最长直径

2、$r_1+r_2+l$

3、$r_2+r_3+l*2$

求个 $max$ 就好了~~~

至于树的半径和直径怎么求。注意到树上离某个点最远的点一定是树的直径的某个端点，于是就可以 $O(n)$ dfs求出。

/*

注意每次dfs前清空数组不能用memset，不然效率会被卡到 $O(n^2)$

我就因为这个T了好久，以为是常数问题，于是代码中加了很多无用的卡常操作，导致它跑的特别快。。。

*/

以下代码：

```cpp
#include<cstdio>
#include<algorithm>
#define Int register int
#define N 100005

inline void rd(int &x){
	x=0;char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^'0'),c=getchar();
}

int n,m,l;

int hd[N],_hd;
struct edge{
	int v,w,nxt;
}e[N<<1];
inline void addedge(int u,int v,int w){
	e[++_hd]=(edge){v,w,hd[u]};
	hd[u]=_hd;
}

bool flg;//为了卡常 
int q[N],_q;

int dis[2][N];
bool vis[N];
inline void dfs(Int u,Int fa,Int opt){
	if(!flg)
		q[++_q]=u;
	vis[u]=1;
	for(Int i=hd[u];i;i=e[i].nxt){
		Int v=e[i].v,w=e[i].w;
		if(v==fa)
			continue;
		dis[opt][v]=dis[opt][u]+w;
		dfs(v,u,opt);
	}
}

inline int fnd(Int u){
	for(Int i=1;i<=_q;i++){
		Int v=q[i];
		dis[0][q[i]]=0;
	}//这里千万不能用memset 
	dfs(u,0,0);
	flg=1;
	Int res=u;
	for(Int i=1;i<=_q;i++){
		Int v=q[i];
		if(dis[0][v]>dis[0][res])
			res=v;
	}
	return res;
}

int r1,r2,r3,ans,cnt;//r1、r2、r3为前三大的半径，ans一开始为最长直径（第一种情况），cnt表示原来有几棵树 
inline void sol(Int u){
	cnt++;
	flg=_q=0;
	dfs(fnd(fnd(u)),0,1);//最里面的fnd返回的是直径的一个端点，第二个fnd更新dis[0]，返回另一个端点，dfs更新dis[1] 
	Int r=1e9;
	for(Int i=1;i<=_q;i++){
		Int v=q[i],disv=std::max(dis[0][v],dis[1][v]);
		r=std::min(r,disv);//更新当前树的半径 
		ans=std::max(ans,disv);//更新最大直径 
	}
	if(r>r1){
		r3=r2;
		r2=r1;
		r1=r;
	}
	else if(r>r2){
		r3=r2;
		r2=r;
	}
	else if(r>r3)
		r3=r;
}

int main(){
	rd(n),rd(m),rd(l);
	for(Int i=1;i<=m;i++){
		Int u,v,w;
		rd(u),rd(v),rd(w);
		addedge(++u,++v,w);
		addedge(v,u,w);
	}
	for(Int i=1;i<=n;i++)
		if(!vis[i])
			sol(i);
	if(cnt>1)
		ans=std::max(ans,r1+r2+l);//第二种情况 
	if(cnt>2)
		ans=std::max(ans,r2+r3+(l<<1));//第三种情况 
	printf("%d\n",ans);

    #define w 0
    return ~~('0')?(0^w^0):(0*w*0);
} 
```


---

## 作者：Dehydration (赞：2)

### 前言：

这是本神(jun)犇(ruo)第一个 IOI 题目，为了庆祝，打算写一波题解。

本文参考了[这篇文章](https://www.cnblogs.com/si-rui-yang/p/10143596.html)，本人认为思路清晰，代码易懂。

[洛谷 P5895 [IOI2013] dreaming 梦想](https://www.luogu.com.cn/problem/P5895)。

### 思路：

我们首先将水坑想象成树，此题便成了给你一棵含有 $n$ 个节点的有边权森林，问每次连边将会用 $L$ 的代价，问你若此图通过加边成为树时的最小直径。

我们可以发现若两棵树要是在合并连接的点一定与树的中心有关。树的中心指对于当i为根时，子树上权值和最大的最小。

为什么，应为树的直径的情况只有单独一棵树，两棵树和在一起的，且那时要是合并就是的是树的中心。

所以会发现其实应该如果说要把树建完以后会发现是一个菊花树，且根为权重最大的联通块的根。因为若是小的当根的话那么就会多算了一颗树，所以最多只需要算两颗即可。

所以说我们每次处理好中心到叶子节点的最大距离是多少，然后就可以直接去计算答案了。

并且为什么最多只要算到联通块个数 $\le 3$ 呢，因为刚才说了这是一颗菊花图，所以我们最多有用的其实是两颗子树。

### 代码详解：

首先是链式前向星，这个算法节约了空间也节约了时间，在此就不细讲，要细看[这个](https://blog.csdn.net/chengqiuming/article/details/125356996)。

#### 代码:
```
//我爱压行
struct node{
    int u,v,w,nex;
}x[N<<1];
int cnt,head[N],n,m,l;
void add(int u,int v,int w){
    x[cnt].u=u,x[cnt].v=v,x[cnt].w=w,x[cnt].nex=head[u],head[u]=cnt++;
}//其中add就是连边，连一个 u->v 权值为 w 的边

```

然后是两遍 dfs ,上面已经详细讲解了思路，就不做解释了。

#### 代码：

```
//-------------first one---------------
void dfs1(int f,int fath){
    vis[f]=1;
    for(int i=head[f];i!=-1;i=x[i].nex){
        if(x[i].v==fath) continue;
        dfs1(x[i].v,f);
        if(dp[x[i].v][0]+x[i].w>=dp[f][0]){dp[f][1]=dp[f][0];dp[f][0]=dp[x[i].v][0]+x[i].w,son[f]=x[i].v;}
        else if(dp[x[i].v][0]+x[i].w>dp[f][1]){dp[f][1]=dp[x[i].v][0]+x[i].w;}
    }
    return;
}
//--------------second one-------------
void dfs2(int f,int fath,int Dis){
    if(Dis>dp[f][0]){
        dp[f][1]=dp[f][0];dp[f][0]=Dis;son[f]=fath;
    }
    else if(Dis>dp[f][1]){dp[f][1]=Dis;}
    ans=max(ans,dp[f][0]);k=min(k,dp[f][0]);
    for(int i=head[f];i!=-1;i=x[i].nex){
        if(x[i].v==fath) continue;
        if(son[f]==x[i].v) dfs2(x[i].v,f,dp[f][1]+x[i].w);
        else dfs2(x[i].v,f,dp[f][0]+x[i].w);
    }
}
```
然后就可以愉快地 [$\color{GREEN}AC $](https://www.luogu.com.cn/paste/1743f8cv) 了！

---

## 作者：liangyanbang (赞：1)

[P5895 [IOI2013] dreaming 梦想](https://www.luogu.com.cn/problem/P5895)
#### 约定
**树的中心**是以它为整棵树的根时，从该根到每个叶子节点的最长路径最短的节点。记这个最大值为 $d_i$。

#### 分析
题目所求即将一个森林用权值为 $l$ 的边连成一棵树，使得这棵树的直径最短。

考虑贪心。首先有一个结论：如果需要一条边连在一棵树上，那么一定连在该树的中心上。因为如果选择与边相连的节点不是树的中心，那么从这条边的另一端点到最远的节点的路径一定会更长。

拓展一下就能想到连接边的方案：以**一棵树的中心**为根节点，向**其他树的中心**连出一条边，最后形成的树的直径最短。而且根节点所在的树满足 $d_i$ 最大。

假设已经找出来 $d_a、d_b$ 和 $d_c$ 是前三个最大的值（$d_b$ 和 $d_c$ 可能不存在，这时假设它们为一个极小的值），$D$ 为所有树的直径的最大值，如果以 $a$ 的中心为根节点，那么最后连通形成的树的直径为：

$$max\{D,d_a+d_b+l,d_b+d_c+2*l\}$$

而如果以 $b$ 的中心为根节点，那么最后树的直径为：

$$max\{D,d_a+d_b+l,d_a+d_c+2*l\}$$

显然以 $a$ 的中心为根节点是最优的。第一个式子即为所求，两次 DFS 就可以了。时间复杂度为 $O(n)$。

#### 代码

```cpp
#include <iostream>
#include <vector>
using namespace std;
typedef pair<int,int> P;
const int N=1e5+5,inf=1e9;
int n,m,l,d1[N],d2[N];bool vis1[N],vis2[N];
vector<P> a[N];
int dfs1(int u){
	// 求出直径和一个端点 
	int v,x,p=u,q;vis1[u]=1;
	for (int i=0;i<a[u].size();++i){
		v=a[u][i].first;
		x=a[u][i].second;
		if (vis1[v])continue;
		d1[v]=d1[u]+x;
		q=dfs1(v);if (d1[q]>d1[p])p=q;
	}
	return p;
}
int dfs2(int u,int dep){
	// 求 di
	int v,x,p=inf,q;vis2[u]=1;
	if (dep==-1){
		for (int i=0;i<a[u].size();++i){
			v=a[u][i].first;
			x=a[u][i].second;
			if (vis2[v])continue;
			dfs2(v,-1);
			d2[u]=max(d2[u],d2[v]+x);
		}
		vis2[u]=0;
		return 0;
	}
	for (int i=0;i<a[u].size();++i){
		v=a[u][i].first;
		x=a[u][i].second;
		if (vis2[v])continue;
		if (d2[v]+x==d2[u]) q=dfs2(v,dep+x);
		else q=dfs2(v,max(dep,d2[u])+x);
		p=min(p,q);d2[u]=max(d2[u],d2[v]+x);
	}
	return min(p,max(dep,d2[u]));
}
int solve(int x){
	int u=dfs1(x);dfs2(u,-1);
	return dfs2(u,0);
}
int ma[4]; // 保存前三个最大值 
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>m>>l;
	int x,y,z;
	for (int i=1;i<=m;++i){
		cin>>x>>y>>z;
		a[x].push_back({y,z});
		a[y].push_back({x,z});
	}
	ma[0]=ma[1]=ma[2]=-inf;
	for (int i=0;i<n;++i){
		if (vis1[i])continue;
		ma[3]=solve(i);
		for (int j=2;j>=0&&ma[j]<ma[j+1];--j)
			swap(ma[j],ma[j+1]);
	}
	x=0;for (int i=0;i<n;++i)x=max(x,d2[i]); //直径 
	cout<<max(x,max(ma[0]+ma[1]+l,ma[1]+ma[2]+2*l));
	return 0;
}
```

---

