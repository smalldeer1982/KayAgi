# A and B and Lecture Rooms

## 题目描述

A和B在准备参加编程比赛。

A和B学习的大学的房间由走廊连接。大学一共有$n$ 个房间，由$n-1$ 条走廊连接，房间的编号是从$1$ 到$n$ 的数字编号。

A和B在大学的某些房间里进行比赛。在每场比赛之后，他们会一起在一个房间里讨论问题。A和B希望这个讨论问题的房间到分别他们两个人比赛房间的距离相等。两个房间之间的距离指他们之间最短路的边数。

因为A和B每天都在不一样的房间里比赛，所以他们请求你告诉他们在接下来比赛的$m$ 天里可以用来讨论问题的房间有多少个？

## 样例 #1

### 输入

```
4
1 2
1 3
2 4
1
2 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4
1 2
2 3
2 4
2
1 2
1 3
```

### 输出

```
0
2
```

# 题解

## 作者：llzzxx712 (赞：60)

# 倍增LCA

[更好的阅读体验](https://www.luogu.com.cn/blog/llzzxx712/)

## 分析题目
题目的意思就是每次询问点x，y，要你求其中离它距离一样的点。

## 解题思路
首先我们可以将两个点的路径L求出，那么这条路径的中点q（如果路径长度是奇数那么就直接判定无解）**一定**是它的一个解，同时点上q**不经过L上的点**所可以到的点就是其他解

即答案是q不经过L能到达的点的数量（包括自己）

比如这棵树![](https://cdn.luogu.com.cn/upload/image_hosting/qrvho2yu.png)

点11和点17的q是节点5，那么节点5不经过17、2、7、11四个点所能到达的点就是它的答案，可以看出，在这种情况下只能到达6、8两点，加上5本身一共是3个点，很容易看出这就是答案。

### 那么怎么找到点q不经过L所能到达的点呢？

再看上面那个例子，我们可以发现这其实就是子树5的大小减去子树7的大小。而节点7是深度大的点走到q的上一步。

这样就相当于剪掉了5的父亲部分和儿子7的部分，因为到达这两个部分一定会经过节点5和7.

但刚才只是一种例子，中点q在两点LCA下方（即深度不同），那如果两个点深度相同（即中点就是LCA）呢？

我们再来回顾一下我们要做的是什么？
是要找到q不经过L可以到达的点的数量。
此时不经过i就是不经过两个点到LCA的子树。还是上面那张图，看节点8 和节点 16它们的中点就是LCA——2，除了16到2所在的子树4 和 8到2所在的子树5以外，其它的节点都是可以到的。
即 ans=全树大小 - 子树4大小 - 子树5大小

## 代码实现

回顾上面所说，我们要做的事有一下几件

1. 求出每个点的子树大小及深度
1. 判断两点深度（以便找中点、计算答案）
1. 找出两点LCA（倍增）
1. 找到中点（LCA向下走（两点深度差/2）的距离）
1. 1. 深度相同：用整个树的大小减去两个点走到中点所在的子树 
   1. 深度不同：用中点子树大小减去下方节点走到中点所在的子树
   
**求子树大小和深度**（还有求出LCA所需要的）[不清楚倍增LCA可以看这里](https://www.luogu.com.cn/blog/llzzxx712/solution-sp14932#)



```cpp
#include<cstdio>
using namespace std;
int to[200002],ne[200002],head[100002],size[100002],de[100002],anc[100002][15];
int n,tot,m;
void add(int x,int y){//邻接表存树
	to[++tot]=y,ne[tot]=head[x],head[x]=tot;
}
void dfs(int x,int fa){
	size[x]=1,de[x]=de[fa]+1,anc[x][0]=fa;//每个点的子树大小子树大小加自己，深度是它父亲深度加一,anc[ x ][i]表示x向上跳2^i步到达的点
	for(int i=1;i<14;i++) anc[x][i]=anc[anc[x][i-1]][i-1];
	for(int i=head[x];i;i=ne[i]){
		if(to[i]==fa) continue;//无根树判父亲
		dfs(to[i],x);
		size[x]+=size[to[i]];//加上它儿子的子树大小
	}
} 
```

**主程序部分**

```cpp
int main()
{  
    read(n);
    for(int i=1;i<n;i++){
    	int x,y;
    	read(x),read(y);
    	add(x,y),add(y,x);//存无根树
	}
	dfs(1,1);//从1开始遍历（反正无根树）
	read(m);
	for(int i=1;i<=m;i++){
		int x,y;
		read(x),read(y);
		getans(x,y);
	}
	return 0;
}
```
**核心部分**

```cpp
void getans(int x,int y){
	if(x==y){//特判2点一样，那就整个树都可以，即size[1]（我从1开始遍历，那么1就是根）
		printf("%d\n",size[1]);
		return;
	}
	if(de[x]==de[y]){//如果深度相同
		for(int i=14;i>=0;i--){
			if(anc[x][i]!=anc[y][i]) x=anc[x][i],y=anc[y][i];//两者都跳到LCA（中点）差一步的地方，此时x、y所在子树就是不能去的点了
		}
		printf("%d\n",size[1]-size[x]-size[y]);//用整个树的大小减一下就好了
		return;
	}
	if(de[x]<de[y]){//如果相同，先把x弄成深度深的点
		int t=x;
		x=y,y=t;
	}
	if((de[x]-de[y])&1){//判断深度差是不是奇数，如果是那么就判断无解
		printf("0\n");
		return;
	}
	int x1=x,d=(de[x]-de[y])>>1;//备份x，并求出深度差的一半（即LCA要向下跳d之后才是中点q）
	for(int i=13;i>=0;i--){
		if(de[anc[x][i]]>=de[y]) x=anc[x][i];//先把深度跳成一样（LCA的一部分）
	}
	if(x==y){//如果跳到深度一样就是LCA了（即x在y的子树中）
		d=de[x]+d;//此时x就是LCA，d被更新为中点深度（就是LCA往下走d步）（这里先求出中点深度，再由x的备份向上跳到这个深度）
		for(int i=13;i>=0;i--){
			if(de[anc[x1][i]]>d){
			    x1=anc[x1][i];
			}
		}//此时x1被跳到离中点还差一步的地方
		printf("%d\n",size[anc[x1][0]]-size[x1]);//中点子树大小减去x1子树大小
		return;
	}
	for(int i=13;i>=0;i--){
		if(anc[x][i]!=anc[y][i]) x=anc[x][i],y=anc[y][i];
	}
	d=de[x]-1+d;//直接中点深度 
	for(int i=13;i>=0;i--){
		if(de[anc[x1][i]]>d) x1=anc[x1][i];//跳到离直接中点深度差 1 的位置 
	}
	printf("%d\n",size[anc[x1][0]]-size[x1]);//同上
}
```

最后附上最优解排名第9的AC代码

```cpp
#include<cstdio>
using namespace std;
int to[200002],ne[200002],head[100002],size[100002],de[100002],anc[100002][15];
int n,tot,m;
void add(int x,int y){
	to[++tot]=y,ne[tot]=head[x],head[x]=tot;
}
void read(int &x) {
    int f = 1; x = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9')   {if (ch == '-') f = -1; ch = getchar();}
    while (ch >= '0' && ch <= '9') {x = x * 10 + ch - '0'; ch = getchar();}
    x *= f;
}
void dfs(int x,int fa){
	size[x]=1,de[x]=de[fa]+1,anc[x][0]=fa;
	for(int i=1;i<14;i++) anc[x][i]=anc[anc[x][i-1]][i-1];
	for(int i=head[x];i;i=ne[i]){
		if(to[i]==fa) continue;
		dfs(to[i],x);
		size[x]+=size[to[i]];
	}
}
void getans(int x,int y){
	if(x==y){
		printf("%d\n",size[1]);
		return;
	}
	if(de[x]==de[y]){
		for(int i=14;i>=0;i--){
			if(anc[x][i]!=anc[y][i]) x=anc[x][i],y=anc[y][i];
		}
		printf("%d\n",size[1]-size[x]-size[y]);
		return;
	}
	if(de[x]<de[y]){
		int t=x;
		x=y,y=t;
	}
	if((de[x]-de[y])&1){
		printf("0\n");
		return;
	}
	int x1=x,d=(de[x]-de[y])>>1;
	for(int i=13;i>=0;i--){
		if(de[anc[x][i]]>=de[y]) x=anc[x][i];
	}
	if(x==y){
		d=de[x]+d;
		for(int i=13;i>=0;i--){
			if(de[anc[x1][i]]>d){
			    x1=anc[x1][i];
			}
		}
		printf("%d\n",size[anc[x1][0]]-size[x1]);
		return;
	}
	for(int i=13;i>=0;i--){
		if(anc[x][i]!=anc[y][i]) x=anc[x][i],y=anc[y][i];
	}
	d=de[x]-1+d;//直接中点深度 
	for(int i=13;i>=0;i--){
		if(de[anc[x1][i]]>d) x1=anc[x1][i];//跳到离直接中点深度差 1 的位置 
	}
	printf("%d\n",size[anc[x1][0]]-size[x1]);
}
int main()
{  
    read(n);
    for(int i=1;i<n;i++){
    	int x,y;
    	read(x),read(y);
    	add(x,y),add(y,x);
	}
	dfs(1,1);
	read(m);
	for(int i=1;i<=m;i++){
		int x,y;
		read(x),read(y);
		getans(x,y);
	}
	return 0;
}
	

```

~~**蒟蒻写了3个多小时才写好，给个赞呗**~~




   




---

## 作者：Social_Zhao (赞：12)

# 题目大意

给定一棵n个点的无根树和m组询问，对于每一组询问，求出树上到某两点距离相等的点数（包含本身）。

# 本题解法

倍增（Tarjan、树剖）求LCA，再加上统计。

先随手来搓一颗树，题中说的是无根树，我们处理一下，令1为根，在倍增LCA预处理的同时求出每个点的深度和子树大小。

![](https://cdn.luogu.com.cn/upload/image_hosting/bm4s2blz.png)

那么现在开始分类讨论。

## 1. 两点重合

那么容易发现，整棵树都满足条件。

## 2. 两点不重合

这个时候我们求出两点的LCA，顺带求出两点之间的点数：

$$dis(x,y)=dep(x)-dep(lca)+dep(y)-dep(lca)+1$$

意思是：这两点之间的点数就是x到lca（不含）的点数加上y到lca（不含）的点数再加上1（lca）

### 2-1: dis(x,y)是偶数

很明显，没有解。

### 2-2: dis(x,y)是奇数

现在要找到(x,y)这条链的中点，那么首先求出中点到x和y的距离，也就是：

$$len=\lfloor dis(x,y)/2\rfloor$$

现在继续分类：

#### 2-2-1: LCA(x,y)是中点

举例：上图中满足此条件的点对有(11,12)等。

那么满足到5和7距离相等的点集就是：

$$1,2,3,4,6,8,9,10$$

可以发现，这些点都在LCA所在的那一根“**轴**”上。我们用排除法来求出点集的大小：

首先把11和12跳到LCA下方，也就是5和7，然后用总点数减去5的子树大小和7的子树大小得解。

#### 2-2-1： LCA(x,y)不是中点

距离：上图中满足此条件的点对有(3,12)等。

(3,12)这条链的中点是4，满足到3和12距离相等的点集就是：

$$4,5,6,8,9,10,11$$

可以发现，这个点集其实是4的子树除去7的子树。

我们将深度较大的点（12）向上跳len次，得到中点（4），再将它（12）向上跳len-1次，得到要除去的子树根节点（7），将他们的子树大小相减。

# 代码：

本题中，求LCA、将某个点向上跳都用倍增进行优化。

```cpp
#include<bits/stdc++.h>
using namespace std;

inline int get() {
    int x = 0, sign = 1; char c = getchar();
    while(!isdigit(c)) { if(c == '-') sign = -1; c = getchar(); }
    while(isdigit(c)) { x = x * 10 + c - '0'; c = getchar(); }
    return x * sign;
}

const int N = 1e5 + 5, E = N << 1;
struct Edge {
    int v, nxt;
} edge[E];
int head[N], k = 1;
int n, m;
int f[N][20], dep[N], size[N];

inline void addedge(int u, int v) {
	edge[++k].v = v;
	edge[k].nxt = head[u];
	head[u] = k;
}

inline void insedge(int u, int v) {
    addedge(u, v);
    addedge(v, u);
}

inline void dfs(int u, int fa) { //预处理
    dep[u] = dep[fa] + 1, size[u] = 1, f[u][0] = fa;
    for(int i = 1; i <= 19; i++) f[u][i] = f[f[u][i - 1]][i - 1];
    for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].v != fa) dfs(edge[i].v, u), size[u] += size[edge[i].v];
}

inline int LCA(int x, int y) { //求LCA
    if(dep[x] < dep[y]) swap(x, y);
    for(register int i = 19; i >= 0; i--) if(dep[f[x][i]] >= dep[y]) x = f[x][i];
    if(x == y) return x;
    for(register int i = 19; i >= 0; i--) if(f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
    return f[x][0];
}

inline int jump(int x, int len) { //将某个点向上跳
    int res = x;
    for(int i = 19; i >= 0; i--) if(dep[x] - dep[f[res][i]] <= len) res = f[res][i];
    return res;
}

int main() {
    n = get();
    for(register int i = 1; i < n; i++) {
        int u = get(), v = get();
        insedge(u, v);
    }
    dfs(1, 0);
    m = get();
    for(register int i = 1; i <= m; i++) {
        int x = get(), y = get();
        if(x == y) { printf("%d\n", size[1]); continue; } //重合
        int lca = LCA(x, y);
        int len = dep[x] + dep[y] - 2 * dep[lca] + 1; //求链的长度
        if(!(len & 1)) { printf("0\n"); continue; } //无解
        len /= 2;
        if(dep[x] - dep[lca] == len) { printf("%d\n", size[1] - size[jump(x, len - 1)] - size[jump(y, len - 1)]); continue; } //LCA是中点
        else { //LCA不是中点
            if(dep[x] < dep[y]) swap(x, y); //用数学语言来说，就是不妨设x的深度大于y的深度
            printf("%d\n", size[jump(x, len)] - size[jump(x, len - 1)]); //输出解
        }
    }
    return 0;
}
```





---

## 作者：一只书虫仔 (赞：10)

#### Description

> 给定一棵点数为 $n$ 的树，并给定 $q$ 组询问，每一组询问给出 $a,b$，求与点 $a$ 和点 $b$ 距离相等的点的个数。

#### Solution

LCA 好题，但是处理的时候会有点麻烦。

下文中 $path(a,b)$ 为点 $a$ 到点 $b$ 的路径长度，$sz_i$ 为以点 $i$ 为根的子树大小。

首先我们把问题简化一下，简化为一条链的两边为点 $a$ 与点 $b$，求有多少个点到点 $a$ 和点 $b$ 的距离相等，不难发现，当 $path(a,b) \bmod 2\ne 0$ 时，就没有满足要求的点，当 $path(a,b) \bmod 2=0$ 时，就有满足要求的点，即为中点。

那我们可以把树改成从这条链引申出若干条边形成的树，那么，不难发现，从中点引出的所有点均满足要求。所以我们分类讨论一下：

- $path(a,b) \bmod 2 \ne 0$，答案为 $0$。
- $path(a,b) \bmod 2=0$：
	- $a$ 和 $b$ 到 LCA 的距离相等：答案为 $n-sz_{f(a)}-sz_{f(b)}$，其中 $f(a),f(b)$ 定义为点 $a$ 和点 $b$ 的祖先中深度为他们 LCA 深度 + $1$ 的点。
    - $a$ 和 $b$ 到 LCA 的距离不等：中点与 $a,b$ 的距离即为 $\dfrac{path(a,b)}{2}$，中点的编号即为 $a$ 和 $b$ 中深度较大的向上爬 $\dfrac{path(a,b)}{2}$ 个点的位置，假设他为 $k$，计算 $sz_k$ 减掉 $a$ 和 $b$ 中深度较大的点所在的子树大小即可。
- $a=b$，答案为 $n$。

---

## 作者：jyz666 (赞：7)

感谢[lzx巨佬](https://www.luogu.com.cn/user/235658)提供的思路
~~我太弱了~~

# CF519E 【A and B and Lecture Rooms】

## [传送门](https://www.luogu.com.cn/problem/CF519E)

## 【理解】

树上倍增。

在树上求距离显然和LCA相关。

还要求出子树大小。
## 【思路】

为方便规定1为根。

先预处理出k倍祖先。

然后呢？

有什么方法快速统计满足条件点的个数？

没思路，先画下图看看吧。

![](https://blog-static.cnblogs.com/files/s-t-a-r-d-u-s-t/CF519Egraph.gif)

然后呢？

先询问结点5,12。

乱搞一通发现有1,3满足到5,12距离相等。

5和12的LCA是1。

然后呢？

再问一组吧，5和6。

LCA是2，答案是5。

然后呢？

再问一组：1和7。

完了好像找不到。

~~好像并没有什么规律~~

然而是有的。

这次我们选择结点9,10。考虑把图扯一下，这样就更清晰了：

![](https://blog-static.cnblogs.com/files/s-t-a-r-d-u-s-t/CF519Egraph1.gif)

树上任意两点间有且只有一条简单路径，这是众所周知~~be universally known~~的。现在图一扯我们就能发现，9,10之间的路径就是9−6−2−5−10。显然在路径上除了中点，是不可能有一个满足条件的点的。

又由于从这些不满足条件的点延伸出去的且不在路径上的点到两端点距离之差显然不会变，故像7,8这类的点也都不行了。

所以1和7没办法找到答案。因为它们的路径上没有中点。

得中点者得天下。

简而言之，答案就是与中点相连且不在路径上的点的数量。

然后呢？

怎么求？

大致思想是统计去掉所有路径上和路径上非中点延伸出的点之后剩下的点的数目。

**如果中点是LCA**

那么答案点集就是整棵树砍掉以两点为根的两棵子树。

**如果不是LCA呢？**

~~感性考虑一下~~，假设中点在LCA左边，那么以左边的点为根的那棵子树显然都要砍掉。不仅如此，从中点往上走的部分也都要砍掉。那么我们发现答案点集就是“以中点为根的子树砍掉以中点在中点到询问点的路径上的儿子为根的子树”。如4,9，中点2，2的子树为{2,5,10,11,6,9,7,8}，2的儿子6的子树为{6,7,8,9}，故答案点集为{2,5,10,11}。

然后子树大小这个东西也是可以在处理深度和祖先时一起预处理出来的。时间复杂度O(qlogn)

其余解释见注释

## AC代码

```cpp
#include<bits/stdc++.h>
#define res register int
#define maxn 500010
using namespace std;
void read(int &x) {
    int f = 1; x = 0;
    char ch = getchar();

    while (ch < '0' || ch > '9')   {if (ch == '-') f = -1; ch = getchar();}
    while (ch >= '0' && ch <= '9') {x = x * 10 + ch - '0'; ch = getchar();}
    x *= f;
}
struct node{
	int to,nxt;
}edge[maxn<<1];
int head[maxn],m,n,root,dep[maxn],fa[maxn][16],num,siz[maxn];
void add(int a,int b){edge[++num].to=b;edge[num].nxt=head[a];head[a]=num;}//存树
inline void swap(int &x,int &y){int t=x;x=y,y=t;}
void get_siz(int x,int pre,int de){//求子树大小 
	fa[x][0]=pre,dep[x]=de;siz[x]=1;
	for(int i = 1; i <= 15; i++)
        fa[x][i]=fa[fa[x][i-1]][i-1];
	for(res i=head[x];i;i=edge[i].nxt){
		int y=edge[i].to;
		if(y==pre) continue;
		get_siz(y,x,de+1);
		siz[x]+=siz[y];
	} 
} 
inline int get_pos(int x,int stp){//求x向上走stp步 
	int now=x;
	if(stp<0) return now;
	for(int i=15;i>=0;i--)//倍增法
        if((stp >> i) & 1) now = fa[now][i];
	return now;
}
inline int lca(int u,int v){//倍增求LCA 
	if(dep[u]<dep[v]) swap(u,v);
	for(res i=15;i>=0;i--){
		if(dep[fa[u][i]]>=dep[v]) u=fa[u][i];
	}
	if(u==v) return u;
	for(res i=15;i>=0;i--){
		if(fa[u][i]!=fa[v][i]) u=fa[u][i],v=fa[v][i];
	}
	return fa[u][0];
}
int main(){
	read(n);
    for(int i=1,a,b;i<n;i++){//节点数 
		read(a);read(b);
        add(a,b);add(b,a);//无向树
    }
	get_siz(1,0,1);//1为根节点
	read(m);
	for(int i=1,x,y;i<=m;i++){
		read(x),read(y);
		int z=lca(x,y);
		if(dep[x]==dep[y]){//如果两点的直接中点恰为两点的LCA（即两点深度差为0） 
			if(x==y) cout<<n<<endl;//两人在同一房间 
			else{
				int nowx=get_pos(x,dep[x]-dep[z]-1);
				int nowy=get_pos(y,dep[y]-dep[z]-1);
				printf("%d\n",n-siz[nowx]-siz[nowy]);
			}
		}
		else {//两点深度差不为0 
			int dis=dep[x]+dep[y]-2*dep[z];//两点距离
			if(dis&1) cout<<0<<endl;//两点深度差为奇数无解 
			else{
				if(dep[x]<dep[y]) swap(x,y);
				int pos=get_pos(x,dis/2);//直接中点
				int nowx=get_pos(x,dep[x]-dep[pos]-1);//找到到直接中点路径上距中点为1的点 
				printf("%d\n",siz[pos]-siz[nowx]); 
			}
		}
	}
	return 0;
}	
```


再次膜拜lzx巨佬

~~求点赞~~

---

## 作者：NXYorz (赞：3)

[题目链接](https://www.luogu.com.cn/problem/CF519E)

容易想到 $O(NM)$的暴力。
暴力做法就是枚举每一个点 $i$， 然后符合题意的 $i$ 一定满足 
$$ dep_a +dep_i - 2 \times dep_{Lca(a , i)} = dep_b + dep_i - 2 \times dep_{Lca(b , i)} $$ 
化简一下:
$$ dep_a -dep_b = 2 \times (dep_{Lca(a , i)} - dep_{Lca(b , i)}) $$ 
可以看出， $dep_a - dep_b$
必须是偶数！ 于是这里就可以特判一下。

显然在它们之间的简单路径上一定存在一个符合题意的点。

考虑一种简单的情况， $A,B$ 深度**相等**。 那么符合要求的点比他们 Lca 以及深度**小于** Lca 的
点。 即简单路径上**符合题意的点就是 Lca 本身。**

然后考虑深度不相等的情况时， 而且这个简单路径上符合题意点一定是**偏向深度深**的点。 并且剩下**所有符合题意的点**都在这个点的**子树**内(除去深度较深的点所在的子树)。
于是就可以愉快的树上倍增了。

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int N = 1e5 + 10;
int n,m,sum;
int first[N],size[N];
int dep[N],f[N][21];
struct E
{
	int next;
	int to;
	void add(int x , int y)
	{
		next = first[x];
		to = y;
		first[x] = sum;
	}
} e[N * 2];
void in(int &x)
{
	x = 0;
	char ee = getchar();
	while(ee < '0' || ee > '9') ee = getchar();
	while(ee >= '0' && ee <= '9') x = (x << 1) + (x << 3) + ee - '0' , ee
		                                  = getchar();
} inline int abs(int x)
{
	return x > 0 ? x : -x;
}
int dfs(int x , int fa)
{
	if(!x) return 0;
	dep[x] = dep[fa] + 1;
	f[x][0] = fa;
	size[x] = 1;
	for(int i = first[x]; i ; i = e[i].next)
	{
		int to = e[i].to;
		if(to == fa) continue;
		dfs(to , x);
		size[x] += size[to];
	} return size[x];
} void Dp()
{
	for(int j = 1; j <= 20; j++)
		for(int i = 1; i <= n; i++)
			f[i][j] = f[f[i][j - 1]][j - 1];
} int Lca(int x , int y)
{
	if(dep[x] < dep[y]) swap(x , y);
	for(int i = 20; i >= 0; i--)
		if(dep[f[x][i]] >= dep[y])
			x = f[x][i];
	if(x == y) return x;
	for(int i = 20; i >= 0; i--)
		if(f[x][i] && f[y][i] && f[x][i] != f[y][i])
			x = f[x][i] , y = f[y][i];
	return f[x][0];
} int LLca(int x , int y)
{
	if(dep[x] < dep[y]) swap(x , y);
	for(int i = 20; i >= 0; i--)
		if(dep[f[x][i]] >= dep[y])
			x = f[x][i];
	if(x == y) return x;
	for(int i = 20; i >= 0; i--)
		if(f[x][i] && f[y][i] && f[x][i] != f[y][i])
			x = f[x][i] , y = f[y][i];
	return size[1] - size[x] - size[y];
} void work()
{
	int a,b;
	in(a);
	in(b);
	if(a == b)
	{
		printf("%d\n",n);
		return;
	}
	if(abs(dep[a] - dep[b]) & 1)
	{
		printf("0\n");
		return;
	}
	int lca = Lca(a , b);
	if(dep[a] == dep[b])
	{
		printf("%d\n",LLca(a , b));
		return;
	} if(dep[a] > dep[b]) swap(a , b);
	int step = dep[b] - dep[a];
	step = dep[b] - step / 2 - dep[lca];
	int cnt = size[b];
	for(int i = 20; i >= 0; i--)
		if(step - (1 << i) > 0)
		{
			b = f[b][i];
			cnt += size[b] - cnt;
			step -= (1 << i);
		}
	b = f[b][0];
	printf("%d\n",size[b] - cnt);
} int main()
{
//	freopen("equal.in","r",stdin);
//	freopen("equal.out","w",stdout);
//	int size = 64<< 20;
//	char*p=(char*)malloc(size) + size;
//	__asm__("movl %0, %%esp\n" :: "r"(p) );
	in(n);
	for(int i = 1; i < n; i++)
	{
		int ui , vi;
		in(ui);
		in(vi);
		e[++sum].add(ui , vi);
		e[++sum].add(vi , ui);
	} dfs(1 , 0);
	Dp();
	in(m);
	for(int i = 1; i <= m; i++)
		work();
	return 0;
}
```

---

## 作者：superMB (赞：3)

```cpp
题目描述

A和B在准备参加编程比赛。

A和B学习的大学的房间由走廊连接。大学一共有n个房间，由n-1条走廊连接，房间的编号是从1 到n 的数字编号。

A和B在大学的某些房间里进行比赛。在每场比赛之后，他们会一起在一个房间里讨论问题。A和B希望这个讨论问题的房间到分别他们两个人比赛房间的距离相等。两个房间之间的距离指他们之间最短路的边数。

因为A和B每天都在不一样的房间里比赛，所以他们请求你告诉他们在接下来比赛的m 天里可以用来讨论问题的房间有多少个？
```

我们简化一下题意，大概就是说这儿有棵大小为n的树，再给出m次询问，每次询问中包含A,B两点，我们要找到离A,B两点距离相等的点一共有多少个。

除了这些条件，这个题还是有一个很友好的隐藏条件，那就是这棵树的根节点默认就为1号节点，就不用再去辛辛苦苦找根节点了。

那么要怎么去求得离A与B距离相等的点的个数呢？

我们就举个例子~~（是我WA了的时候cf扒的）~~

```
输入：
15
1 2
1 3
1 4
2 5
2 6
2 7
5 8
6 9
9 14
14 15
7 10
4 13
3 11
3 12
6
10 15
13 12
2 15
8 4
15 12
6 13
输出：
1
10
1
7
0
4
```

如图：

![](https://s2.ax1x.com/2019/01/06/FHmazn.png)

需要对A,B之间的距离进行分类讨论：

1.如果询问的两个点之间的距离为奇数，那么无论怎样，它们之间必然有偶数个点，不可能有点到它们的距离相等，比如图中的15号点与12号点距离为奇数，没有点到它们的距离相等。

2.如果询问的两个点之间的距离为偶数时，我们要找到A,B之间的中点，这个时候又需要分几个情况：

(1)A,B两点到他们的lca的距离不相等（包括A,B两点中其中一个点为另一个点的lca），那么我们需要找到A,B两点所在链上的中点，中点与它不包含所询问点的子树上的点都是满足条件的点，如8号点到4号点。

(2)A,B两点到他们的lca之间距离相等时，满足条件的点的个数即是整棵树的上节点的总数减去lca包含所询问两点的子树的节点个数，如12与13点。

3.A,B两点重合时，整颗树上的点到这两个点的距离都可以看做相等。

经过讨论，这个题就变成了求lca之后再略加处理的~~水~~题了

~~这个题总而言之还是很毒瘤的，因为我的写法太暴力了，所以debug了灰常久，简直无法可想~~

下main是鸡冻的代码时间~~（我是压行怪）~~：

```cpp
#include<cstdio>
#define ri register int
using namespace std;
template<typename TP>inline void read(TP&x)//数据较大，使用快读快输
{
    x=0;int f=1;char c=getchar();
    while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    x*=f;
}
template<typename TP>inline void print(TP x)
{
    if(x<0)x=-x,putchar('-');
    if(x>=10)print(x/10);
    putchar(x%10+'0');
}
struct node1{int to,nxt;}e1[200005];//链式前向星
struct node2{int to,nxt,num;}e2[200005];
int head1[200005],tot1,head2[200005],tot2;
int a[100005],b[100005]/*存点*/;
int f[100005]/*并查集所用father数组*/,ans[100005];/*询问答案*/
int dep[100005]/*每个点的深度*/,sons[100005]/*每个点的儿子个数*/,father[100005]/*每个点的上一个父亲节点*/;
bool check[100005];
inline void add1(int from,int to)//建图
{
    ++tot1;
    e1[tot1].to=to;
    e1[tot1].nxt=head1[from];
    head1[from]=tot1;
}
inline void add2(int from,int to,int num)
{
    ++tot2;
    e2[tot2].to=to;
    e2[tot2].num=num;
    e2[tot2].nxt=head2[from];
    head2[from]=tot2;
}
inline int find(int x){if(f[x]!=x)f[x]=find(f[x]);return f[x];}//Tarjan求LCA
inline void Union(int x,int y){f[x]=y;return;}
inline void Tarjan(int x,int fa,int deep)
{
    father[x]=fa,dep[x]=dep[fa]+1,sons[x]=1;//在Tarjan的过程中提前处理每个点的深度，儿子个数，上一个父亲节点
    for(ri i=head1[x];i;i=e1[i].nxt)
        if(e1[i].to!=fa)
            Tarjan(e1[i].to,x,deep+1),Union(e1[i].to,x),sons[x]+=sons[e1[i].to];
    check[x]=1;
    for(ri i=head2[x];i;i=e2[i].nxt)
        if(check[e2[i].to])
            ans[e2[i].num]=find(e2[i].to);
}
inline void work(int x,int step,int pre)//对于到LCA距离不同时的处理
{
    if(step==0)
    {
        print(sons[x]-sons[pre]),putchar('\n');
        return;
    }
    work(father[x],step-1,x);
}
inline int work2(int x,int aim)//到LCA距离相同的处理
{
    if(father[x]==aim)return sons[x];
    work2(father[x],aim);
}
int n,m,rt;
int tpa,tpb;
int main()
{
	read(n);
    for(ri i=1;i<n;++i)f[i]=i,read(tpa),read(tpb),add1(tpa,tpb),add1(tpb,tpa);
    f[n]=n,read(m);
    for(ri i=1;i<=m;++i)
        read(a[i]),read(b[i]),add2(a[i],b[i],i),add2(b[i],a[i],i);
    Tarjan(1,0,0);
    for(ri i=1;i<=m;++i)
		if(a[i]==b[i])print(sons[1]),putchar('\n');//两个点为相同点
        else if(a[i]==ans[i])//询问的第一个点是第二个点的LCA
			if((dep[b[i]]-dep[a[i]])&1)putchar('0'),putchar('\n');//距离为奇数
            else work(b[i],(dep[b[i]]-dep[a[i]])>>1,0);
        else if(b[i]==ans[i])//询问的第二个点是第一个点的LCA
        	if((dep[a[i]]-dep[b[i]])&1)putchar('0'),putchar('\n');//距离为奇数
            else work(a[i],(dep[a[i]]-dep[b[i]])>>1,0);
        else//互相不为LCA
        	if((dep[a[i]]+dep[b[i]]-(dep[ans[a[i]]]<<1))&1)putchar('0'),putchar('\n');//距离为奇数
            else
            	if(dep[a[i]]>dep[b[i]])work(a[i],(dep[a[i]]+dep[b[i]]-(dep[ans[i]]<<1))>>1,0);//中点在询问的第一个点到LCA上
                else if(dep[a[i]]<dep[b[i]])work(b[i],(dep[a[i]]+dep[b[i]]-(dep[ans[i]]<<1))>>1,0);//中点在询问的第二个点到LCA上
                else print(sons[1]-work2(a[i],ans[i])-work2(b[i],ans[i])),putchar('\n');//中点为LCA
    return 0;
}

```

---

## 作者：Diaоsi (赞：2)

## 思路：

由于树上任意两点的路径是唯一的，可以先考虑路径 $A \rightarrow B$ 上有哪些点能对答案产生贡献。

产生贡献的点为路径的中点，且该点为树的一个节点。

也就是说，只有路径 $A \rightarrow B$ 上有奇数个点时，才会有节点对答案产生贡献。

而当路径 $A \rightarrow B$ 上有偶数个点时，没有一个点能满足到 $A$ 的距离和到 $B$ 的距离相等。


------------


接下来考虑不在路径上的点，当前考虑 $A \rightarrow B$ 中点**存在**时的情况。

显然，只要一个点到 $A$ 点和 $B$ 点的路径**均包含**路径 $A \rightarrow B$ 的中点，该点就对答案产生贡献。

也就是说，当一个点到 $A$ 点和 $B$ 点的路径中**遇到的第一个路径 $A \rightarrow B$ 上的点为 $A \rightarrow B$ 中点时**，这个点就对答案产生贡献。

因为该点到 $A \rightarrow B$ 中点的路径是唯一的，而 $A \rightarrow B$ 中点到 $A$ 点和 $B$ 点距离相等，所以该点到 $A$ 点和 $B$ 点距离是相等的。

同理，当 $A \rightarrow B$ 中点**不存在**时，树上任意一个点都不对答案产生贡献，即答案为 $0$ 。


------------


接下来考虑如何计算答案。

指定 $1$ 节点为树的根。

对于树上的节点 $x$ 和 $y$ ，设：

+ $d(x)$ 表示 $x$ 的深度

+ $size(x)$ 表示以 $x$ 为根的子树的大小

+ $mid(x,y)$ 表示路径 $x \rightarrow y$ 的中点

+ $\text{lca}(x,y)$ 表示 $x$ 和 $y$ 的**最近公共祖先**

+ $\text{Son}(x)$ 表示 $x$ 的儿子集合

+ $\text{fa}(x)$ 表示 $x$ 的父节点

考虑第一种情况，当 $d(A) \neq d(B)$ 时：

此时 $A \rightarrow B$ 的中点一定在 $A,B$ 当中深度较大的那个点到 $\text{lca}(A,B)$ 的路径上，设点 $C \in A \rightarrow B $ 且 $C \in \text{Son}(mid(A,B))$。

根据题解开头的结论，由于$\text{fa}(mid(A,B)) \in A \rightarrow B $ ， $mid(A,B)$ 以上的节点均不对答案产生贡献，故答案为 $ size(mid(A,B))-size(C) $ 。

![1](https://cdn.luogu.com.cn/upload/image_hosting/novhqd8c.png)

如上图，考虑 $A=14,B=13$ ，路径 $ 14 \rightarrow 13 $ 中点为 $2$ (红色部分)，答案为 $size(2)-size(6)$ (绿色部分)。

考虑第而种情况，当 $d(A)=d(B)$ 时：

此时 $A \rightarrow B$ 的中点一定为 $\text{lca}(A,B)$ ，设点 $C,D \in A \rightarrow B $ 且 $C,D \in \text{Son}(\text{lca}(A,B))$，答案为 $n-size(C)-size(D)$ 。

![2](https://cdn.luogu.com.cn/upload/image_hosting/wa9ztjlc.png)

如上图，考虑 $A=9,B=8$ ，路径 $ 9 \rightarrow 8 $ 中点为 $2$ (红色部分)，答案为 $n-size(6)-size(5)$ (蓝色部分)。


------------


具体实现使用倍增，参考最近公共祖先的求法，不会的左转[模板](https://www.luogu.com.cn/problem/P3379)。

用一次 dfs 预处理出 $size(x)$ 和 $d(x)$ ，对于每个询问，倍增地跳到中点，然后按照上述方式计算即可。

时间复杂度: $\mathcal{O(n \log n)}$

既然你能找到这题，我相信你能瞬间做出来的。

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long N=100010,M=1000010,INF=0x3f3f3f3f;
long long head[N],ver[M],Next[M],tot;
long long n,m,t,d[N],size[N],f[N][20];
queue<long long> q;
inline long long Max(long long x,long long y){return x>y?x:y;}
inline long long Min(long long x,long long y){return x<y?x:y;}
inline void Swap(long long &x,long long &y){x^=y^=x^=y;}
void add(long long x,long long y){
	ver[++tot]=y,Next[tot]=head[x],head[x]=tot;
}
void bfs(){
	d[1]=1;
	q.push(1);
	while(q.size()){
		long long x=q.front();q.pop();
		for(long long i=head[x];i;i=Next[i]){
			long long y=ver[i];
			if(d[y])continue;
			d[y]=d[x]+1;
			f[y][0]=x;
			for(long long j=1;j<=t;j++)
				f[y][j]=f[f[y][j-1]][j-1];
			q.push(y);
		}
	}
}
void dfs(long long x,long long fa){
	size[x]=1;
	for(long long i=head[x];i;i=Next[i]){
		long long y=ver[i];
		if(y==fa)continue;
		dfs(y,x);
		size[x]+=size[y];
	}
}
long long lca(long long x,long long y){
	if(d[x]>d[y])Swap(x,y);
	for(long long i=t;i>=0;i--)
		if(d[f[y][i]]>=d[x])y=f[y][i];
	if(x==y)return x;
	for(long long i=t;i>=0;i--)
		if(f[x][i]!=f[y][i])x=f[x][i],y=f[y][i];
	return f[x][0];
}
long long query(long long x,long long y){
	return d[x]+d[y]-2*d[lca(x,y)];
}
long long findmid(long long x,long long y){
	if(query(x,y)&1)return 0;
	if(d[x]==d[y]){
		for(long long i=t;i>=0;i--)
			if(f[x][i]!=f[y][i])x=f[x][i],y=f[y][i];
		return n-size[x]-size[y];
	}
	if(d[x]>d[y])Swap(x,y);
	long long mid=d[y]-(query(x,y)>>1);
	for(long long i=t;i>=0;i--)
		if(d[f[y][i]]>mid)y=f[y][i];
	return size[f[y][0]]-size[y];
}
int main(){
	scanf("%lld",&n);
	t=(long long)(log(n)/log(2))+1;
	for(long long i=1;i<n;i++){
		long long x,y;
		scanf("%lld%lld",&x,&y);
		add(x,y),add(y,x);
	}
	scanf("%lld",&m);
	bfs();
	dfs(1,0);
	while(m--){
		long long x,y;
		scanf("%lld%lld",&x,&y);
		if(x==y){printf("%lld\n",n);continue;}
		printf("%lld\n",findmid(x,y));
	}
	return 0;
}
```



---

## 作者：registerGen (赞：2)

[更好的阅读体验](https://registergen.github.io/post/solution-cf519e/)

板题。

看到这题，首先想到求路径（设路径端点为 $u,v$，且令 $dep_u\ge dep_v$）的中点。

那么我们只需解决两个子问题：

- 如何求中点？
- 如何统计答案？

# Solution

## 如何求中点？

利用 LCA 求出 $dis=\operatorname{dis}(u,v)$，如果 $2\nmid dis$，则中点不存在，否则用树上倍增将 $u$ 向上跳 $\dfrac{dis}{2}$ 步，此时的 $u$ 就是所求中点。

## 如何统计答案？

如图：

![](https://i.loli.net/2020/11/28/nVxRZYlBPFuHeQ1.png)

红色部分即为所求。

那么怎么求呢？$siz_a-siz_b$ 即可。

但是！一种情况除外！

当 $a=\operatorname{LCA}(u,v)$ 时，如图：

![](https://i.loli.net/2020/11/28/8mtWka4SKTC7FB6.png)

此时答案为：$n-siz_b-siz_c$。

# Code

```cpp
#include<cstdio>
#include<algorithm>

const int N=1e5;
const int LOGN=17;

struct Edge{int to,nxt;}e[N*2+10];int head[N+10],tote;
inline void addEdge(int u,int v){e[++tote].to=v;e[tote].nxt=head[u];head[u]=tote;}

int n,m,fa[N+10][LOGN+5],dep[N+10],siz[N+10];

void DFS(int u,int _fa){
	fa[u][0]=_fa;
	dep[u]=dep[_fa]+1;
	siz[u]=1;
	for(int i=1;i<=LOGN;i++)
		fa[u][i]=fa[fa[u][i-1]][i-1];
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==_fa)continue;
		DFS(v,u);
		siz[u]+=siz[v];
	}
}

int LCA(int u,int v){
	if(dep[u]<dep[v])std::swap(u,v);
	for(int i=LOGN;~i;i--)
		if(dep[u]-(1<<i)>=dep[v])
			u=fa[u][i];
	if(u==v)return u;
	for(int i=LOGN;~i;i--)
		if(fa[u][i]!=fa[v][i])
			u=fa[u][i],v=fa[v][i];
	return fa[u][0];
}

int solve1(int u,int v){ // a = LCA(u, v)
	if(u==v)return n;
	for(int i=LOGN;~i;i--)
		if(fa[u][i]!=fa[v][i])
			u=fa[u][i],v=fa[v][i];
	return n-siz[u]-siz[v];
}

int solve2(int u,int v){ // otherwise
	if(dep[u]<dep[v])std::swap(u,v);
	int lca=LCA(u,v);
	int dis=dep[u]+dep[v]-2*dep[lca]; // dis(u, v)
	if(dis&1)return 0;
	dis>>=1;
	int a=u,tmp=dis;
	for(int i=LOGN;~i;i--)
		if((1<<i)<=tmp)
			a=fa[a][i],tmp-=(1<<i);
	int b=u;
	tmp=dis-1; // 这样就保证了 b 是 a 的儿子
	for(int i=LOGN;~i;i--)
		if((1<<i)<=tmp)
			b=fa[b][i],tmp-=(1<<i);
	return siz[a]-siz[b];
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		addEdge(u,v);
		addEdge(v,u);
	}
	DFS(1,0);
	scanf("%d",&m);
	while(m--){
		int u,v;
		scanf("%d%d",&u,&v);
		if(dep[u]==dep[v])printf("%d\n",solve1(u,v)); // dep[u] = dep[v] 等价于 a = LCA(u, v)
		else printf("%d\n",solve2(u,v));
	}
	return 0;
}
```

---

## 作者：_Xiuer (赞：2)

## $Lca$
很容易发现，这道题它和$lca$有关系$qwq$。  
可以想到一个暴力思路，枚举每个点$i$，求$i$与$A$和$B$的距离，统计出答案即可。  
然后我们又会发现**与A和B距离相等的点就是A和B所在链的中点i以及i为根时，除A和B所在子树外的所有节点**，当$AB$间距离是奇数时，不存在距离相等的点。  
首先我们$dfs$预处理出每个点的儿子数，当存在答案时，分为两种情况考虑：  
$1.A$和$B$在同一深度时，这种情况比较简单，他们所在链的中点就是它们的公共祖先，我们暴力地将$A$和$B$跳到公共祖先的下方设为$x,y$，那么答案就是:
$n-son[x]-son[y]-2.$  
$2.A$和$B$在不同深度时，它们的中点发生了偏移，我们找到这个中点$p$，依旧和上面一样暴力地跳到中点两旁设为$x,y$，$x$和$y$必然有一个点和$p$在同一棵子树内，我们设这个点是$x$，这时的答案为$son[p]-son[x]$。  
至于为什么答案是这两个，可以自己画个图，很容易看出来。  
注：特判$A$和$B$相同时，答案为$n$。
### $Code$
```cpp
#include<iostream>
#include<cstdio>
#define N 100010
using namespace std;
int n,m,dep[N],son[N],f[N][19];
int fir[N],nex[N*2],poi[N*2],sum;
void re(int &x)
{
	x=0;char i=getchar();
	while(i<'0'||i>'9') i=getchar();
	while(i>='0'&&i<='9') x=(x<<1)+(x<<3)+i-'0',i=getchar();
}
void ins(int x,int y)
{
	nex[++sum]=fir[x];
	poi[sum]=y;
	fir[x]=sum;
}
int dfs(int x,int fa,int deep)
{
	dep[x]=deep;
	for(int i=fir[x];i;i=nex[i])
	{
		int p=poi[i];
		if(p==fa) continue;
		f[p][0]=x;
		for(int j=1;j<=18;j++)
		f[p][j]=f[f[p][j-1]][j-1];
		son[x]+=dfs(p,x,deep+1);
	}
	return son[x]+1;
}  //--dfs预处理 
int lca(int x,int y)
{
	if(dep[x]<dep[y]) swap(x,y);
	int p=dep[x]-dep[y];
	for(int i=18;i>=0;i--) if(p&(1<<i)) x=f[x][i];
	if(x==y) return x;
	for(int i=18;i>=0;i--)
	{
		if(!f[x][i]||!f[y][i]||f[x][i]==f[y][i]) continue;
		x=f[x][i];y=f[y][i];
	}
	return f[x][0];
}  //--倍增求lca 
int main()
{
	re(n);
	int x,y;
	for(int i=1;i<n;i++)
	{
		re(x);re(y);
		ins(x,y);ins(y,x);
	}
	dfs(1,0,1);
	re(m);
	for(int i=1;i<=m;i++)
	{
		re(x);re(y);
		if(x==y)  //--特判 
		{
			printf("%d\n",n);
			continue;
		}
		int z=lca(x,y);
		if(z!=x&&z!=y)
		{
			if(dep[x]<dep[y]) swap(x,y);
			if(dep[x]!=dep[y])  //--深度不同 
			{
				int k=(dep[x]+dep[y]-dep[z]*2);
				if(k%2==1) printf("0\n");
				else
				{
					k/=2;
					k=dep[x]-k;
					z=x; //-->暴力上移 
					for(int j=18;j>=0;j--)
					{
						if(dep[f[z][j]]<=k) continue;
						z=f[z][j];
					} //<-- 暴力上移  下同 
					int h=f[z][0];
					printf("%d\n",son[h]-son[z]);
				}
			}
			else
			{
				for(int j=18;j>=0;j--)
				{
					if(dep[f[x][j]]<=dep[z]) continue;
					x=f[x][j];
					y=f[y][j];
				}
				printf("%d\n",n-son[x]-son[y]-2);
			}
		}
		else  //--深度相同 
		{
			if(dep[x]<dep[y]) swap(x,y);
			if((dep[x]-dep[y])%2==1) printf("0\n");
			else
			{
				int k=(dep[x]+dep[y])/2;
				z=x;
				for(int j=18;j>=0;j--)
				{
					if(dep[f[z][j]]<=k) continue;
					z=f[z][j];
				}
				int h=f[z][0];
				printf("%d\n",son[h]-son[z]);
			}
		}
	}
	return 0;
}



---

## 作者：Harece (赞：2)

因为蒟蒻我很弱（而且第一次发题解）所以很可能会出错，欢迎各位大佬指出。

简单分析一下题意：有m次询问，每次回答求到A与B两点距离相等的点的个数。

以下图为例，把一号节点当作根节点。

​	![](https://cdn.luogu.com.cn/upload/pic/63315.png)



特殊情况：所求点A与点B重合，那任意点到A与B的距离都相等；

一：A与B两点之间点数为偶数，无解；

二：两点之间点数为奇数时

​			情况一：当A与B深度不同且有一节点深度等于小于中点时，答案为 中点儿子数 -  包含较深节点子树节点数 + 1（因为在计数时已经把根节点算入，所以代码中没有+1）.

​										![](https://cdn.luogu.com.cn/upload/pic/63317.png)

​			情况二：A与B深度都大于中点深度，且A与B都在中点子树中。从图像可以为我们看出答案为中点子节点数 - 包含A与B的两颗子树的节点数 + 1.

​										![](https://cdn.luogu.com.cn/upload/pic/63318.png)

​				情况三：A与B深度都大于中点深度，但有一点不与中点在同一子树中。我们可以看出这与情况一相似因为路径必须经过中点的父亲节点所以答案为 中点儿子数 -  包含较深节点子树节点数 + 1。

​														![](https://cdn.luogu.com.cn/upload/pic/63319.png)



```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

const int N = 1e5 + 10;

int n, tot, s, m, A, B, k, h;
int dth[N], head[N], fa[N][24], lg[N], sum[N];

struct Edge {
	int to, nxt;
}e[N << 1];

template <typename T>
inline void read(T& x) {
	x = 0;
	char c = getchar();
	T op = 1;
	for (; c < '0' || c > '9'; c = getchar())
		if (c == '-')	op = -1;
	for (; c <= '9' && c >= '0'; c = getchar())
		x = (x << 3) + (x << 1) + c - '0';
	x *= op;
}

inline void add(int x, int y) {
	e[++tot].to = y;
	e[tot].nxt = head[x];
	head[x] = tot;
}

void dfs(int x, int fath) {
	dth[x] = dth[fath] + 1;
	fa[x][0] = fath;
	sum[x] = 1;
	for (int i = 1; i <= s; ++i)
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
	for (int i = head[x]; i; i = e[i].nxt)
		if (e[i].to != fath)	dfs(e[i].to, x), sum[x] += sum[e[i].to];
}

inline void init() {
	for (int i = 1; i <= n; ++i)
		lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
}

inline int lca(int x, int y) {
	if (dth[x] < dth[y])	swap(x, y);
	while (dth[x] > dth[y])	x = fa[x][lg[dth[x] - dth[y]] - 1];
	if (x == y)	return x;
	for (int i = lg[dth[x]] - 1; i >= 0; --i)
		if (fa[x][i] != fa[y][i])	x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}

inline int ask() {
	int z = dth[A] + dth[B] - (dth[k] << 1) - 1;
	if (dth[A] < dth[B])	swap(A, B);
	int x = A, f = A;
	for (int i = s; i >= 0; --i)
		if (dth[A] - dth[fa[x][i]] <= (z + 1) >> 1 && fa[x][i])	x = fa[x][i];//求两点路径上的中点
	for (int i = s; i >= 0; --i)
		if (dth[x] < dth[fa[f][i]] && fa[f][i]) f = fa[f][i];//找到包含较深点的子树
	if (dth[k] >= dth[B])	return	sum[x] - sum[f];//情况一
	else {
		int q = B;
		for (int i = s; i >= 0; --i)
			if (dth[x] < dth[fa[q][i]] && fa[q][i]) q = fa[q][i];
		if (fa[q][0] == k) //判断是否在同一子树内	
            return n - sum[f] - sum[q];//情况二
		else return	sum[x] - sum[f];//情况三
	}
}

int main() {
	read(n);
	init();
	s = log2(n) + 1;
	for (int i = 1; i < n; ++i) {
		int x, y;
		read(x), read(y);
		add(x, y), add(y, x);
	}
	dfs(1, 0);
	read(m);
	for (h = 1; h <= m; ++h) {
		read(A), read(B);
		if (A == B) { printf("%d\n", n); continue; }//特殊情况
		k = lca(A, B);//求LCA
		if ((dth[A] - (dth[k] << 1) + dth[B]) & 1)	printf("0\n");//两点之间点数为偶数时无解
		else printf("%d\n", ask());
	}
	return 0;
}
```

---

## 作者：hovny (赞：2)



## 解题思路

倍增$Lca$

### 分析

首先，题目中给的是一颗无根树，将无根树转换为有根树处理，随便选一个点为根即可

到两点距离相等的点，应为两点之间唯一路径上的中点以及其延伸出去的点，如果两没有中点，则必不存在答案，特判即可

然后就是找中点的问题

具体实现起来会和 $Lca$ 的位置有一定关系，所以需要求出 $x$、$y$ 两点的 $Lca$，然后算出中点的距离

这样我们就可以找出两点的中点啦，这样答案即为中点及其延伸出的点的个数

但是仍然要分情况讨论（`size[k]` 为以 $1$ 为根时 $k$ 的子树大小）：

1、中点为 $Lca$ 时，如询问 $4$、$6$ 

![](https://hovnysilence.github.io/image/CF519-1.jpg)

结果应该是手动红框框出来的辣些点，仔细研究一下，其实应该是 `size[2]-size[3]-size[5]`

也就是：中点的子树大小 $-$ 路径上与中点相邻两个点的子树大小

2、中点不为 $Lca$ ，询问的 $x$、$y$ 都不是对方的祖先时，如询问 $5$、$7$

![](https://hovnysilence.github.io/image/CF519-2.jpg)

还是手动框出来的辣个点，`ans=size[3]-size[4]`

也就是： 中点的子树大小 $-$ 与中点相邻且深度较大的点的子树大小

3、中点不为 $Lca$ ，询问的 $x$、$y$ 一方为对方的祖先时，如询问 $1$、$7$

![](https://hovnysilence.github.io/image/CF519-3.jpg)

不难发现，`ans=size[3]-size[4]`

和$2$中的结论一致，所以就讨论两种就好了

还要注意中点偏向 $x$ 还是 $y$，操作的对象是不同的

**如何求邻近点？**

由于预处理了每个点的祖先情况，因此那些邻近点可以在知道距离的情况下用倍增求

### Warning

可能存在查询的两点相同的情况，此时答案为 $0$

## Code

```cpp
#include<bits/stdc++.h>
#define rgt register
#define N 100003
using namespace std;
struct Edge{
	int to,nxt;
}b[N<<1];
int head[N],deep[N],size[N];
int n,T,dis,t,f[N][17],rx,ry,root;
inline int read() {
	rgt int s=0;
	rgt char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) s=(s<<1)+(s<<3)+c-'0',c=getchar();
	return s;
}
inline void add(rgt int x,rgt int y) {
	b[++t].to=y,b[t].nxt=head[x],head[x]=t;
	b[++t].to=x,b[t].nxt=head[y],head[y]=t;
}
inline void built(rgt int k,rgt int fa) {//处理倍增Lca
	rgt int	i,to;size[k]=1;
	deep[k]=deep[fa]+1;
	for(i=0;i<16;i++)//预处理出祖先情况
		f[k][i+1]=f[f[k][i]][i];
	for(i=head[k];i;i=b[i].nxt) {
		to=b[i].to;
		if(to==fa) continue;
		f[to][0]=k,built(to,k),size[k]+=size[to];
	}
}
inline int Lca(rgt int x,rgt int y) {//倍增求Lca
	if(deep[x]<deep[y]) swap(x,y);
	rgt int i;
	for(i=16;i>=0;i--) {
		if(deep[f[x][i]]>=deep[y])
			x=f[x][i];
		if(x==y) return x;
	}
	for(i=16;i>=0;i--)
		if(f[x][i]!=f[y][i])
			x=f[x][i],y=f[y][i];
	return f[x][0];
}
inline int getanc(rgt int res,rgt int k) {//倍增求res节点的k次祖先
	rgt int i,x;
	for(i=16,x=res;i>=0;i--)
		if(deep[res]-deep[f[x][i]]<=k)
			x=f[x][i];
	return x;
}
int main()
{
	int i,x,y;
	n=read();
	for(i=1;i<n;i++)
		x=read(),y=read(),add(x,y);
	built(1,0),T=read();
	while(T--) {
		x=read(),y=read();
		if(x==y) {printf("%d\n",n);continue;}//特判相等
		root=Lca(x,y);//求出Lca
		dis=deep[x]+deep[y]-deep[root]-deep[root];//就算两点间距离
		if(dis&1) {printf("0\n");continue;}//没有中点
        dis>>=1;//到路径中点的距离
		if(dis==deep[x]-deep[root]) {//Lca为中点的情况
			rx=getanc(x,dis-1),ry=getanc(y,dis-1);
			printf("%d\n",n-size[rx]-size[ry]);
		}
		else {
			if(dis<deep[x]-deep[root]) {//看中点偏向哪一边
				root=getanc(x,dis),rx=getanc(x,dis-1);
				printf("%d\n",size[root]-size[rx]);
			}//也就是看中点是x还是y的祖先，用dis判断比较方便
			else {
				root=getanc(y,dis),ry=getanc(y,dis-1);
				printf("%d\n",size[root]-size[ry]);
			}
		}
	}
	return 0;
}
```



---

## 作者：inexistent (赞：2)

代码以及更好的阅读效果请参见我的[博客](https://www.cnblogs.com/qixingzhi/p/9302038.html)

思路分析：

   题意：询问给出一棵无根树上任意两点a,b，求关于所有点i，\(dist(a,i) = dist(b,i)\)的点的数量。要求每一次询问在O(log n)的时间复杂度内完成。

　　由于在树上求距离，并且还要O(log n)，自然会联想到LCA。由于边权是1，那么点到根的距离就是该点的深度。这个深度可以在dfs预处理的过程中处理完成。那么两个点之间的距离就是两个点到根节点的距离减去两点的LCA到根节点距离的两倍。这个随便yy一下就好了。

　　得到a,b间的距离D以后，分类讨论。（设a的深度>=b的深度）

　　（1）若D为奇数，则一定不存在任何一个点到a,b的距离相等。因此得到0.

　　（2）若D为偶数：

 　　（一）a,b两点分别在LCA的两棵子树上。

　　　①a,b两点深度相同。此时很简单，最近的一个距离相等的点就是a,b的LCA。也很容易想到LCA的祖先也全都符合。但真的只有这些吗？LCA的祖先的其他儿子好像也满足诶……LCA的其他子树（除了a,b）好像也满足诶……因此我们得到结论，在这种情况下得到的答案应当是\(n - size[LCA的左子树] - size[LCA的右子树]\)。

　　　②深度不同。那么我们找到中间节点Mid，Mid里除有a的子树外其他子树都符合，并且Mid以上的节点都不会符合，因此答案是\(size[Mid] - size[有a的那棵子树]\)

　　　（二）a,b在同一条链上，即b就是LCA

　　　这时候和（一）①的情况简直一模一样。（想一想，为什么？）

　　因此我们要做的不过是在dfs的过程中维护好size和dep。但一直困惑我的是由a的那个子树怎么快速得到？答案其实很暴力……再倍增一遍……

代码注意点：

　　太坑了！调试了一个多小时竟然是因为LCA的预处理dfs中(1<<i)打成了i，导致TLE得莫名其妙。还是LCA板子不熟啊……

---

## 作者：Bitter_Tea (赞：1)

本题基本思路是$Lca$+**分类讨论**


~~主要是考察画图能力和想象力~~

首先我们这个题不难想到用$Lca$，毕竟是个树上的距离问题，不用$Lca$用啥。

我们通过画图发现情况比较多，这个时候就需要我们的归纳能力了。

我们进行分类讨论:

1.如果$A=B,ans$就是$n$ ,~~这个绝对坑了一部分人~~

2.如果$dep_A=dep_B$，那么$ans$就是$son_1-son_a-son_b$，$a$和$b$是它们$Lca$的子节点,$son_i$表示$i$的子树节点个数(包括本身)
如下图所示

![avator](https://cdn.luogu.com.cn/upload/image_hosting/1tb15wza.png?x-oss-process=image/resize,m_lfit,h_600,w_680)

我们要求到$4,5$距离相等的点，由于它们深度相同，符合此种情况，所以$ans=son_1-son_4-son_5=4$

3.如果$A,B$间的边数为奇数，那么$ans$就是$0$，这是很显然的。

4.如果上述情况都没有，那么就是下面这种情况了
![avator](https://cdn.luogu.com.cn/upload/image_hosting/kt1fishl.png?x-oss-process=image/resize,m_lfit,h_600,w_680)


我们需要从深度$A,B$中较大的结点向上找走$\frac{dis(A,B)}{2}$到点 $x$，走$\frac{dis(A,B)}{2}-1$到点$y$ ，$dis(A,B)$表示$A,B$两点间边个数。那么答案是$son_x-son_y$

如上图，我们要求到$5，6$距离相等的点，深度大的节点是$5$,那么点$x$为$3$，点$y$为$4$，$ans=son_3-son_4=2$

大部分都是树上倍增的操作，代码实现并不难。




$Code$

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=1e5+5,E=18;
struct D{int nxt,to;}e[N*2];
int fir[N],tot;
int f[N][19];
int n,m;
int dep[N],son[N];
void add(int x,int y)
{
	e[++tot].nxt=fir[x];
	e[tot].to=y;
	fir[x]=tot;
}
void dfs(int x,int fa,int d)
{
	son[x]=1;dep[x]=d;
	for(int i=fir[x];i;i=e[i].nxt)
	{
		int p=e[i].to;
		if(p==fa) continue;
		dfs(p,x,d+1);
		f[p][0]=x;
		son[x]+=son[p];
	}
}
void dp()
{
	for(int i=1;i<=E;i++)
	for(int j=1;j<=n;j++)
	f[j][i]=f[ f[j][i-1] ][i-1];
}
int lca(int a,int b,int z)//z=1则寻找Lca，z=0查询答案
{
	if(dep[a]<dep[b]) swap(a,b);
	int x=dep[a]-dep[b];
	if(z==1)
	{
		for(int i=E;i>=0;i--)
		if(x&(1<<i)) a=f[a][i];
		if(a==b) return a;
	}
	for(int i=E;i>=0;i--)
	{
		if(f[a][i]==f[b][i]) continue;
		a=f[a][i];b=f[b][i];
	}
	if(z==1) return f[a][0];
	if(z==0) return son[1]-son[a]-son[b];
}
int find(int x,int l)
{
	int now=0;
	for(int i=E;i>=0;i--)
	{
		if((1<<i)+now>l) continue;
		now+=(1<<i);
		x=f[x][i];
	}
	return x;
}
void solve(int x,int y)
{
	int z,l,now;
	if(x==y)            //特判是否相等，相等则输出n
	{
		printf("%d\n",n);
		return;
	}
	z=lca(x,y,1);
	if(dep[x]==dep[y]) //深度一样的情况
	{
		printf("%d\n",lca(x,y,0));
		return;
	}
	l=dep[x]+dep[y]-dep[z]*2;
	if(l%2!=0)          //如果边为奇数个，则答案为0
	{
		printf("0\n");
		return;
	}
	l>>=1;now=0;
	if(dep[x]<dep[y]) swap(x,y);
	int aim=find(x,l);          //判断深度不等的情况
	int aim_=find(x,l-1);
	printf("%d\n",son[aim]-son[aim_]);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	dfs(1,0,1);
	dp();
	scanf("%d",&m);
	while(m--)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		solve(x,y);
	}
	return 0;
}
```

---

## 作者：ccbb0530 (赞：1)

# 经典树上LCA。
[luogu原题](https://www.luogu.com.cn/problem/CF519E)阅读。

这道题简单地说就是给定树上的两个点x,y。求树上能使得到x,y距离相等的点数。
 
我们可以分类讨论。   
1. 若LCA到x和LCA到y的距离相等且x,y不是同一个点。   
 用总点数n-x这棵子树上的点数-y这棵子树上的点数=到x,y距离相等的点数。  
2. 若LCA到x和LCA到y的距离不相等,且分别为a,b。  
(1)a+b为奇数，则a-b必定为奇数(和差）。  
x,y的距离差必定同时加或减去一个偶数，永远不可能是0。  
(2)a+b为偶数，不妨假设a>b,在a上必有一点距离LCA（a-b)/2到x,y距离相等。设这个点为P，以P为根的子树结点-P到x的结点数+1=到x,y距离相等的点数。  

3. x,y是同一个点.   
树上任何一个点都成立。


上代码


```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+5;

struct Edge{
    int v,nxt;
}edge[maxn*2];

int head[maxn],tot;
void init() {
    memset(head,-1,sizeof head);
    tot = 0; //下一个等待被用的节点。  
}

void addedge(int u,int v) { //u->v ，边权为w
    edge[tot].v = v;
    edge[tot].nxt = head[u];
    head[u] = tot++;
}

int fa[maxn][20],dep[maxn],siz[maxn];
void dfs(int u,int pre) { //nlogn的预处理
    fa[u][0] = pre;
    siz[u] = 1;
    for(int i=1;i<20;i++)
        fa[u][i] = fa[fa[u][i-1]][i-1];

    dep[u] = dep[pre] + 1;
    for(int i=head[u];i!=-1;i=edge[i].nxt) {
        int v = edge[i].v;
        if(v==pre) 
			continue;
        dfs(v,u);
        siz[u] += siz[v];
    }
}

int LCA(int u,int v) {
    if(dep[u]>dep[v]) 
		swap(u,v);
    
    for(int i=19;i>=0;i--)
        if(dep[fa[v][i]] >= dep[u])  v = fa[v][i];

    if(u==v) 
		return u;
    for(int i=19;i>=0;i--) {
        if(fa[u][i]==fa[v][i]) 
			continue;
        u = fa[u][i];
        v = fa[v][i];
    }
    return fa[u][0];
}
int jump_up(int u,int k) {
    int i = 0;
    while(k) {
        if(k&1) u = fa[u][i];
        k>>=1;
        i++;
    }
    return u;
}

int n,m;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    init();
    cin>>n;
    for(int i=1;i<n;i++) {
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
    cin>>m;
    dfs(1,0); //nlogn
    while(m--) { //mlogn
        int a,b;
        cin>>a>>b;
        int lca = LCA(a,b);
        if(a==b) {
            cout<<n<<"\n";
        }
        else if(dep[a]==dep[b]) {
            int x =jump_up(a,dep[a]-dep[lca]-1);
            int y = jump_up(b,dep[b]-dep[lca]-1);
            cout<< n - siz[x] -siz[y]<<"\n";
        } else {
            int d = dep[a]+dep[b] -2*dep[lca];
            if(d&1) cout<<"0"<<"\n";       // if (d%2==1)
            else {
                if(dep[a]>dep[b]) swap(a,b);
                int y = jump_up(b,d/2-1);
                int x = fa[y][0];
                cout<<siz[x] - siz[y]<<"\n";
            }
        }
    }
    
    return 0;
}
```


---

## 作者：Lucifer_Bartholomew (赞：1)

# LCA
就是q次询问,每次对于树上两点a、b,求树上有多少个点到a和b距离相等。

因为要求树上距离,所以自然想到用LCA求。但这道题的难点不在于求距离,而在于求满足到a和b距离相等的点的特征。

我们可以分几种情况讨论:(图丑不要吐槽,最好自己画图模拟一下）

- 当a、b为同一点时,因为树上每一点到这两点的距离都相等,所以答案为整颗树的大小。

- 当a、b不同时,先求出a、b之间的距离,再分情况讨论：

>1. 已知所有边权都为1,所以当a、b间距离为奇数时,到两点距离相等的点到两点的距离不是整数,这种点不存在,答案为0。
>2. 当两点间距离为偶数时,若a到lca(a,b)的距离与b到lca(a,b)的距离相等,即lca(a,b)为满足条件的一个点时(如图),那么所有不与a或b在同一棵以lca(a,b)为根节点的子树上的点均满足条件,答案为整棵树大小减去以lca(a,b)为根节点的含a子树和含b子树的大小。![](https://cdn.luogu.com.cn/upload/pic/65162.png)
>3. 当a到lca(a,b)的距离与b到lca(a,b)的距离不相等时,那么就只有在以a、b距离中点为根节点不含a或b的子树上的点满足条件(如图),答案为以a、b距离中点为根节点不含a或b的子树大小。![](https://cdn.luogu.com.cn/upload/pic/65170.png)

另：感谢楼下题解的一组很好的hack数据,如果这组数据过了,基本上A这题就没问题了。
```cpp
输入：
15
1 2
1 3
1 4
2 5
2 6
2 7
5 8
6 9
9 14
14 15
7 10
4 13
3 11
3 12
6
10 15
13 12
2 15
8 4
15 12
6 13
输出：
1
10
1
7
0
4
```
下面是代码：
```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rr register int
#define ll long long
using namespace std;
inline int read()//文件较大推荐快读
{
	char ch=getchar();
	int f=1,x=0;
	while(ch>'9'||ch<'0')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
struct node{
	int v,next;
}e[200001];
int n,cnt,head[100001],f[100001][19],dep[100001],siz[100001];//siz[i]表示以i为根节点的子树大小
inline void add(int u,int v)//链式前向星存边
{
	e[++cnt]=(node){v,head[u]};
	head[u]=cnt;
}
inline void dfs(int u,int fa)//遍历整棵树预处理
{
	siz[u]=1;
	f[u][0]=fa;
	dep[u]=dep[fa]+1;//求深度
	int t=log2(dep[u]);
	for(rr i=1;i<=t;++i)//倍增求lca
		f[u][i]=f[f[u][i-1]][i-1];
	for(rr i=head[u];~i;i=e[i].next)
	{
		int v=e[i].v;
		if(v!=fa)
		{
			dfs(v,u);
			siz[u]+=siz[v];//统计所有儿子节点的子树大小
		}
	}
}
inline int lca(int l,int r)//lca在线算法
{
	if(dep[l]>dep[r])swap(l,r);
	int t1=log2(dep[r]);
	for(rr i=t1;~i;--i)
		if(dep[r]-dep[l]>=(1<<i))r=f[r][i];
	if(l==r)return l;
	int t=log2(dep[l]);
	for(rr i=t;~i;--i)
		if(f[l][i]!=f[r][i])
		{
			l=f[l][i];
			r=f[r][i];
		}
	return f[l][0];
}
inline int dist(int a,int b)//求a到b的距离
{
	return dep[a]+dep[b]-(dep[lca(a,b)]<<1);
}
int main()
{
	memset(head,-1,sizeof head);
	n=read();
	for(rr i=1;i<n;++i)
	{
		int x=read(),y=read();
		add(x,y);
		add(y,x);
	}
	dfs(1,1);
	int q=read();
	for(rr i=1;i<=q;++i)
	{
		int a=read(),b=read();
		if(a==b)printf("%d\n",n);//a和b为同一点的情况
		else
		{
			int d=dist(a,b);
			if(d&1)puts("0");//距离为奇数的情况
			else
			{
				d>>=1;
				if(dep[a]<dep[b])swap(a,b);//距离中点一定与a、b中深度更深的点在同一棵子树上
				int s=log2(a);
				for(rr i=s;~i;--i)//求距离中点
					if(d-(1<<i)>0)
					{
						d-=(1<<i);
						a=f[a][i];
						b=f[b][i];
					}
				if(dep[a]==dep[b])printf("%d\n",n-siz[a]-siz[b]);//lca(a,b)为中点的情况
				else printf("%d\n",siz[f[a][0]]-siz[a]);//lca(a,b)不为中点的情况
			}
		}
	}
	return 0;
}
```
~~我是蒟蒻~~

---

## 作者：MuYC (赞：0)

### 前言:

你可能需要用到的前置知识点: 倍增求 $LCA$(或者说是树上倍增？)

### 正文

#### 题目大意:

给定一棵树，以及 $m$ 个询问，每次询问的形式是给定两个点 $x,y$ ，求有多少个点 $u$ 满足 $dis(u,x) == dis(u,y)$

题目不难 ，但是要分类讨论清楚也不是那么容易。

无根树，我们假定 $1$ 号点为根即可。

下面约定概念:

$dep[x]$ 表示 $x$ 点的深度。
$siz[x]$ 表示 $x$ 为根的子树的大小。

然后我们开始分类讨论(下面假定 $dep[x] < dep[y]$ ):
+ $1$. $x = y$

输出点的个数即可。所有点均满足条件。

+ $2$.$LCA(x,y) = x$

意味着 $x$ 是 $y$ 的祖先节点。

不难发现，倘若 $x$ 到 $y$ 中间有偶数个点的话，是没有答案的，输出 $0$

倘若 $x$,$y$ 中间有奇数个点，那么答案就是 $x$ 到 $y$ 的路径的**中点** $p$ 以及 $p$ 的所有儿子（除了 $p$ 中 $y$ 所在的那一整个子树）。可以通过倍增的方法求出 $p$ 点以及 $p$ 中 $y$ 所在的那一个子树的根节点。 


+ $3.LCA(x,y) != x$ && $dep[x] == dep[y]$

这个说明 $LCA(x,y)$ 就是 $x,y$ 的路径中点，那么除了在以 $LCA(x,y)$ 为根的子树中的 $x$ 所在的子树以及 $y$ 所在的子树，其它的点都可以。

+ $4$.$LCA(x,y) != x$ && $dep[x] != dep[y]$

假若路径中有偶数个点，很显然没有答案。

假若是奇数，取**路径中点** $p$ 求子树 - $p$ 中 $y$ 所在的那一整个子树大小 大小即可。

至于具体写法的一些小 $trick$ 就放在代码里面了。

```cpp

// Problem: CF519E A and B and Lecture Rooms
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 50;
int start[MAXN] , tot = 0 , siz[MAXN] , n , parent[MAXN][20] , dep[MAXN];

struct Edge {
	int next,to;
} edge[MAXN << 1];

inline int read() {
	int x = 0 , flag = 1;
	char ch = getchar();
	for( ; ch > '9' || ch < '0' ; ch = getchar()) if(ch == '-') flag = -1;
	for( ; ch >= '0' && ch <= '9' ; ch = getchar()) x = (x << 3) + (x << 1) + ch - '0';
	return x * flag;
}

void add(int from,int to) {
	edge[++tot].next = start[from];
	edge[tot].to = to;
	start[from] = tot;
	return ;
}

int DFS(int x , int from) {//预处理Parent数组以及深度数组
	siz[x] = 1; parent[x][0] = from; dep[x] = dep[from] + 1;
	for(int i = 1 ; i <= log2(dep[x]) ; i ++) 
	parent[x][i] = parent[parent[x][i - 1]][i - 1];
	for(int i = start[x] ; i ; i = edge[i].next) {
		int to = edge[i].to;
		if(to == from) continue;
		siz[x] += DFS(to , x);
	}
	return siz[x];
}

int LCA(int x,int y) {//倍增求LCA的模板
	if(dep[x] > dep[y]) swap(x,y);
	for(int i = log2(dep[y] - dep[x]) ; i >= 0 ; i --)
		if(dep[parent[y][i]] >= dep[x]) y = parent[y][i];
	if(x == y) return x;
	for(int i = log2(dep[x]) ; i >= 0 ; i --)
	if(parent[x][i] != parent[y][i]) x = parent[x][i] , y = parent[y][i];
	return parent[x][0];
}

int GetFa(int x,int Deep) {
	//这是给定深度，然后倍增求一个距离 x 点距离为 k 的祖先 
	while(Deep) {
		int d = log2(Deep);
		x = parent[x][d];
		Deep -= (1 << d);
	}
	return x;
}

int GetLas(int x,int Fa) {
	//这是给定一个点，然后倍增求一个点所在这个点中的哪个子树（求所在子树的根）
	for(int i = log2(dep[x]) ; i >= 0 ; i --)
	if(dep[parent[x][i]] > dep[Fa]) x = parent[x][i];
	return x;
}

void solve(int x,int y) {
	if(dep[x] > dep[y]) swap(x , y);
	if(x == y) {printf("%d\n",n); return ;}
	if(LCA(x,y) == x) {
		if((dep[y] - dep[x]) & 1) {printf("%d\n",0); return ;}//这表示是偶数个点可以画图知道
		int Fa = GetFa(y,(dep[y] - dep[x]) >> 1) , son = GetFa(y , ((dep[y] - dep[x]) >> 1) - 1);//这里Fa就是中点
		printf("%d\n",siz[Fa] - siz[son]);
		return ;
	}
	int L = LCA(x,y) , Road = dep[x] + dep[y] - dep[L] * 2;//故意不+1的....
	if(dep[x] - dep[L] == dep[y] - dep[L]) {//对应情况3
		int LS,RS;
		LS = GetLas(x , L) , RS = GetLas(y , L);//分别求出所在的子树
		int Ans = 0;
		Ans = n - siz[LS] - siz[RS];
		printf("%d\n",Ans);
		return ;
	}
	if(Road & 1) {printf("%d\n",0) ; return ;} //偶数个点
	else {
		int Fa = GetFa( y , (Road >> 1)) , son = GetLas(y , Fa);
		printf("%d\n",siz[Fa] - siz[son]);//对应情况4
		return ;
	}
	return ;
}

int main() {
	n = read();
	for(int i = 1 ; i <= n - 1; i ++) {
		int u = read() , v = read();
		add(u , v) ; add(v , u);
	}
	DFS(1,0);
	int Q = read();
	while(Q --) {
		int u = read() , v = read();
		solve(u,v);
	}
	return 0;
}
```

---

