# [AMPPZ2013] Bytehattan

## 题目描述

比特哈顿镇有 $n\times n$ 个格点，形成了一个网格图。一开始整张图是完整的。

有 $k$ 次操作，每次会删掉图中的一条边 $(u,v)$，你需要回答在删除这条边之后 $u$ 和 $v$ 是否仍然连通。

## 说明/提示

数据保证，$2\leq n\leq 1500$，$1\leq k\leq 2n(n-1)$，$1\leq a,b\leq n$。

## 样例 #1

### 输入

```
3 4
2 1 E 1 2 N
2 1 N 1 1 N
3 1 N 2 1 N
2 2 N 1 1 N```

### 输出

```
TAK
TAK
NIE
NIE```

# 题解

## 作者：Cecilia_qwq (赞：8)

## **对偶图+并查集**

~~截止2024.8.15，我是本题最劣解。~~

这题第一眼看到时会发现是显然的连通性问题，因为每次只需要判断两个格点是否连通，我们考虑使用并查集。

~~那我太懂了，离线+时光倒流。这还评紫？~~ 和别的题目不同，本题要求强制在线。

那怎么办？~~开摆。~~ 我们引入一种新图——对偶图。

什么是对偶图？我们可以简单理解：普通的图是以真点（我们称这种真实存在的点，也就是本题中的格点为真点）为点建图，而对偶图的独特在于，对偶图是以普通图中各个面（也就是普通的图中各个边所围成的面）为点来建图的。（可见下图，$1,2,3,4,5$ 为原图的真点，$x1,x2,x3,x4$ 为对偶图上由面转化而来的点）
![对偶图](https://cdn.luogu.com.cn/upload/image_hosting/6m660wa7.png)

注意上面的图中 $x4$ 表示的是所有除  $x1,x2,x3$ 之外的一整个大面。

接下来是关于对偶图的连边，我们将所有只有一条边相隔绝（也就是一条边的两边）的面构成的点建立虚边相连，也就是下面这张图。
![对偶图连边](https://cdn.luogu.com.cn/upload/image_hosting/wcogdjh5.png)

仔细观察这张图，我们看看能发现什么和连通性有关的结论。

这里经过不懈的观察，我们会发现，在对偶图中成环的连边很有意思，拿环 $x1,x2,x3,x4$ 来说，我们会发现，如果删去原图中与这些对偶图的边相应的真边，即 $(1,2),(1,3),(3,4),(3,5)$ 或 $(2,3),(1,3),(3,4),(3,5)$ 或将 $(3,5)$ 用 $(4,5)$ 替换。上述各组边如果被删去之后，原图也就变成了两个不连通的块。**也就是说，对偶图上成环的边所对应的原图上的真边的真边集是原图的一个割。**（这里的割就是网络流里面的割，但推广一下，也就是删去一个边集后原图若被分为两个不连通的图的话，这个边集被称为一个割）

这是一个很有用的性质，考虑把这种性质迁移到这个题目里来。发现这题的操作是只删不加，我们可以这样考虑：对于每次删边，我们将这条边在对偶图上所隔绝的两个面用并查集并起来（因为它们合成了一个面），当我们发现这条边所隔绝的两个面在删去这条边前就已经在同一集合里，那么说明，如果这条边再删去，对偶图中就会产生环，也就是说，在这次删边操作后，有一个割已经被删去了，因此原图被该割给划分成了两个块，故该边链接的两点也就不连通了。

接下来考虑这题如何把原图和对偶图建立关系，因为原图是一个 $n\times n$ 的网格图，我们可以考虑**对于每个格点，设定它所对应的面（也就是对偶图中的点）为右下的面。** 那么我们会发现，所有的面的标号最大为 $(n-1)\times (n-1)+1$ 我们可以按照这种方式建图。（见下图，为样例的图）
![建图](https://cdn.luogu.com.cn/upload/image_hosting/ocpfqlin.png)

对于这个正方形，我们左上角标号为 $(1,1)$ 右下角为 $(3,3)$ 中间每个面对应的是它左上角的那个格点。

需要注意的是，存在一些格点所对的面都是同一个大面，也就是 $5$ 号面，这些点我们会在输入的时候处理出来，具体可见代码。

最后，就是删边的过程，我们发现对于一个点 $(a,b)$ ，记它所对应的边的编号为 $id[a][b]$ 如果它要删去和 $(a+1,b)$ 之间的竖向连边，那么也就是这条边对应的左右两个面会连通，也就是 $id[a][b-1],id[a][b]$  会连通，若删去的是横向连边推导方式一样，实在不理解可以画一个图看一下。

不难发现根据上述推导，我们需要处理的格点编号是从 $(0,0)$ 开始到 $(n,n)$ 的。这里我用的是覆盖的方法，先将所有格点的对应面记成最大的面的编号 $tot$ ，然后再遍历 $(1,1)$ 到 $(n-1,n-1)$ 的格点赋值，具体可见代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e6+99;
int n,tot,q;
int id[1511][1511];
int f[N],cnt;
int find(int x){return f[x]==x ? x:f[x]=find(f[x]);}
bool last=true;
signed main(){
	scanf("%d%d",&n,&q);
	tot=(n-1)*(n-1)+1;//所有的面最多为这么多 
	for(int i=1;i<=tot;i++) f[i]=i;
	for(int i=0;i<=n;i++) for(int j=0;j<=n;j++) id[i][j]=tot;//先全部赋值为最大面tot 
	for(int i=1;i<n;i++) for(int j=1;j<n;j++) id[i][j]=++cnt;//对于存在在大正方形里面的各个小面，把这个面的编号给左上角的点。 
	while(q--){
		int x,y,xx,yy;
		char op1,op2;
		scanf("%d%d%c",&x,&y,&op1);
		scanf("%d%d%c",&xx,&yy,&op2);
		if(!last) x=xx,y=yy,op1=op2;
		if(op1=='E'){
			int fu=find(id[x][y-1]),fv=find(id[x][y]);
			if(fu==fv){
				printf("NIE\n");
				last=false;
				continue;
			}
			printf("TAK\n");
			last=true;
			f[fu]=fv;
		}
		else{
			int fu=find(id[x-1][y]),fv=find(id[x][y]);
			if(fu==fv){
				printf("NIE\n");
				last=false;
				continue;
			}
			printf("TAK\n");
			last=true;
			f[fu]=fv;
		}
	}
	return 0;
}
```

---

## 作者：Mr_罗 (赞：4)

## 题意

一张网格图，每次删一条边，并询问这条边两端的点是否仍连通。**强制在线**。

## 题解

一句话题解：转对偶，判连通。

前置知识：对偶图。

没有在线要求就可以倒着加边水过去，然而强制在线，此路不通。~~也许有什么把所有有可能删的边都加上之类的抽象做法，但是我不会。~~

考虑到题目问是否连通，若不连通则说明整张图被**割**开了。等等，割？你也许想到了两个经典结论：**最大流等于最小割；平面图最大流等于对偶图最短路。**

那它们和此题有什么关系呢？通过刚刚的结论我们知道平面图最小割等于对偶图最短路，也就是说**可以把平面图的割转化为其对偶图的路径**，那么目前没割开等价于没有路径，也就是不连通。这样就把割转化为了连通性问题。

你可以这么想：方格连通了，一些边被砍掉了，方格构成的封闭图形（把外界也看成方格）把一些点包了起来，这些顶点显然被孤立了。

然后就做完了，时间复杂度 $\mathcal O(n^2\alpha(n^2))$。

```cpp
constexpr int N = 1505, M = 2250005;
constexpr ll mod = 998244353;
int n, m, q, lt = 1;
int fa[M];

int fdrt(int i) { return i == fa[i] ? i : fa[i] = fdrt(fa[i]); }

int merge(int u, int v)
{
    if ((u = fdrt(u)) == (v = fdrt(v))) return 0;
    return fa[u] = v, 1;
}

void solve() {
    scanf("%d%d", &n, &q), m = (n - 1) * (n - 1);
    iota(fa + 1, fa + m + 2, 1); while (q--) {
        int a, b; char op[5]; scanf(lt ? "%d%d%s%*d%*d%*s" : "%*d%*d%*s%d%d%s", &a, &b, op);
        int u, v;
        if (a == n || b == n) u = m + 1;
        else u = (a - 1) * (n - 1) + b;
        if (op[0] == 'N') { if (a == 1) v = m + 1; else v = (a - 2) * (n - 1) + b; }
        else { if (b == 1) v = m + 1; else v = (a - 1) * (n - 1) + b - 1; }
        puts((lt = merge(u, v)) ? "TAK" : "NIE");
    }
}
```

---

## 作者：all_for_god (赞：2)

[P10665 \[AMPPZ2013\] Bytehattan](https://www.luogu.com.cn/problem/P10665)

## 思路

看到维护网格图（平面图）的连通性，强制在线，想到对偶图。

平面图的对偶图是指对于原图的每一块平面建立一个虚空节点。如果原图中的某条边被删去，那么就会有两个平面被连通。在形式上就是这两个平面对应的虚点间连边。

那如何判定原图上两个点是否连通呢？一个比较显然的观察是如果原图的一个连通块被虚点间的连边“包围” 了，那么这个连通块里的所有点都与这个连通块内的点不连通了。也就是虚点间的连边形成了**环**。可以画个图感受一下。

由于题目要求是**删去边后**再询问是否连通，因此如果这条边两侧的平面在这条边被删之前就是连通的，那么显然删掉这条边后虚点间的连边就将形成**环**。因此判定是否连通的条件就是删边以前这条边两侧的平面是否已经连通。

点的连通性可以用并查集维护。时间复杂度 $O(n\alpha)$。其中 $\alpha$ 是并查集的复杂度。

## code

由于是网格图，因此可以 $O(1)$ 得到边两侧的平面的序号。如果不是网格图需要预处理。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2250000+7;
int n,m,fa[N],lst=1,num;
int get(int x,int y){return x<1||y<1||x>=n||y>=n?0:(x-1)*n+y;}
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
int merge(int x,int y){x=find(x),y=find(y);if(x==y)return 0;else {fa[x]=y;return 1;}}
void work(int x,int y,char s){
	if(s=='N'){
		int u=get(x,y),v=get(x-1,y);
		lst=merge(u,v);cout<<(lst?"TAK\n":"NIE\n");
	}
	else{
		int u=get(x,y),v=get(x,y-1);
		lst=merge(u,v);cout<<(lst?"TAK\n":"NIE\n");
	}
}
signed main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;num=(n-1)*(n-1)+1;for(int i=0;i<=n*n;i++) fa[i]=i;
	for(int i=1,lx,ly,rx,ry;i<=m;i++){char sl,sr;cin>>lx>>ly>>sl>>rx>>ry>>sr;if(lst)work(lx,ly,sl);else work(rx,ry,sr);}
	return 0;
}
```

---

## 作者：Unnamed114514 (赞：1)

因为删边不好搞所以考虑转化成连边，因此考虑构造原图的对偶图，这样我们就把断边转化为合并两个块。

注意到网格图的结构非常容易建立对偶图，让每个点表示右下角的平面，最后一行和最后一列表示整个平面即可。

令这条边断开后，合并的连通块为 $a,b$（即如果是横着的边，就是上下两个连通块，否则就是左右两个连通块），那么修改的时候直接合并这两个连通块即可。

两个点不连通，那么一个点所能遍历到的点的集合一定不包含另一个点。

集合内的边不考虑，考虑集合内的点与集合外的点之间的边，这条边一定是被删掉的。

因此，不连通相当于有一个平面包围住了其中一个点。

但是此时这个圈不完整，因为还要断这条边，那么此时就是条链。

因此不连通的条件就是 $a,b$ 在同一个集合，因为并查集是树形结构，如果合并 $a,b$ 相当于加了条边，又因为原图每次删的边不一样，所以一定会多条边，就会变成基环树，从而产生环导致不连通。

---

## 作者：LastKismet (赞：0)

# Sol
直接删不好操作吧，考虑转化为连边。但是强制在线，因此无法逆转时间。

考虑这是个平面图，考虑转对偶图，不难发现现在可以连边了。

删除一条边时，就把其隔开的两面连起来即可。当两个点不连通，那么在对偶图上，其中一点周围已经绕成了一个环。这个用连通性判一下即可，并查集解决。

# Code

```cpp
const int N=1500*1500+5;

int n,k;
int fa[N];
inline void init(int n){rep(i,0,n)fa[i]=i;}
inline int find(int x){if(fa[x]!=x)fa[x]=find(fa[x]);return fa[x];}
inline void merge(int a,int b){fa[find(a)]=find(b);}
inline bool same(int a,int b){return find(a)==find(b);}

inline int id(int x,int y){
    if(x<1||x>n-1||y<1||y>n-1)return 0;
    return (x-1)*(n-1)+y;
}

inline void Main(){
    read(n,k);
    init((n-1)*(n-1));
    int ans=0;
    rep(i,1,k){
        int a,b,d,e;char c,f;read(a,b,c,d,e,f);
        auto solve=[&](int x,int y,char c){
            int a,b;
            if(c=='N')a=id(x-1,y),b=id(x,y);
            else a=id(x,y-1),b=id(x,y);
            ans=same(a,b);
            put(ans?"NIE":"TAK");
            merge(a,b);
        };
        if(ans)solve(d,e,f);
        else solve(a,b,c);
    }
}
```

---

## 作者：Ydoc770 (赞：0)

### [Luogu P10665 [AMPPZ2013] Bytehattan](https://www.luogu.com.cn/problem/P10665)

对偶图板子题。

定义**平面图**为不存在两边相交的图，这个图将平面分割为了很多部分，每个部分称为这个平面图的一个面。
现在就可以定义**对偶图**：平面图的每个面作为节点，彼此相连构成的图。

回到原题，容易看出网格图就是平面图。考虑 $n\times n$ 的网格图其对偶图初始为 $(n-1)(n-1)+1$ 个孤立的点，维护原图的对偶图，割边操作等价于在对偶图上对应两点连边。
一个重要的观察是原图两点**不连通**当且仅当两点被对偶图分隔开，也就是在连边之前这两点对应面在对偶图上**已经连通**，连边就会使对偶图形成一个环隔开原图的点。

所以原题就变成了一个在线连边，查询连通性的问题，用并查集可以简单维护。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn = 1.5e2 + 10, maxm = 2.25e6 + 10;
int n, k, u, v, out; bool lst = true;
char op1, op2;

int fa[maxm];
inline int find(int i) {return (i == fa[i]) ? i : fa[i] = find(fa[i]);}
inline bool merge() {if((u = find(u)) == (v = find(v))) return false; fa[u] = v; return true;}

int main() {
	ios :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
	
	cin >> n >> k; out = (n - 1) * (n - 1) + 1; for(int i = 1; i <= out; i++) fa[i] = i;
	for(int i = 1, a1, b1, a2, b2; i <= k; i++) {
		cin >> a1 >> b1 >> op1 >> a2 >> b2 >> op2;
		if(lst) {
			u = (a1 == n || b1 == n) ? out : (a1 - 1) * (n - 1) + b1;
			v = (op1 == 'N') ? ((a1 == 1) ? out : (a1 - 2) * (n - 1) + b1) : (b1 == 1) ? out : (a1 - 1) * (n - 1) + b1 - 1;
		}
		else {
			u = (a2 == n || b2 == n) ? out : (a2 - 1) * (n - 1) + b2;
			v = (op2 == 'N') ? ((a2 == 1) ? out : (a2 - 2) * (n - 1) + b2) : (b2 == 1) ? out : (a2 - 1) * (n - 1) + b2 - 1;
		}
		cout << ((lst = merge()) ? "TAK\n" : "NIE\n"); 
	}
	
	return 0;
} 
```

---

