# [POI 2012] RAN-Rendezvous

## 题目描述

**译自 POI 2012 Stage 1. 「[Rendezvous](https://szkopul.edu.pl/problemset/problem/MZTXfOVnJmac175TTH5Lr9Q3/site/?key=statement)」**

给定一个有 $n$ 个顶点的有向图，每个顶点有且仅有一条出边。每次询问给出两个顶点 $a_i$ 和 $b_i$，求满足以下条件的 $x_i$ 和 $y_i$：
* 从顶点 $a_i$ 沿出边走 $x_i$ 步与从顶点 $b_i$ 沿出边走 $y_i$ 步到达的顶点相同。
* $\max(x_i, y_i)$ 最小。
* 满足以上条件的情况下 $\min(x_i, y_i)$ 最小。
* 如果以上条件没有给出一个唯一的解，则还需要满足 $x_i \ge y_i$。

如果不存在这样的 $x_i$ 和 $y_i$，则 $x_i = y_i = -1$。

## 说明/提示

对于 $40\%$ 的数据，$n \le 2000,k \le 2000$。

对于 $100\%$ 的数据，$1 \le n \le 500\ 000,1 \le k \le 500\ 000$。

## 样例 #1

### 输入

```
12 5
4 3 5 5 1 1 12 12 9 9 7 1
7 2
8 11
1 2
9 10
10 5```

### 输出

```
2 3
1 2
2 2
0 1
-1 -1```

# 题解

## 作者：lgnotus (赞：13)

## 思路
UPD:$\text{2021/7/17}$ ：把爆炸的图补上了

这题的样例给的很好，我们先把图画出来。

![](https://cdn.luogu.com.cn/upload/image_hosting/sp7ife02.png)

结合图像与题意，此图为**内向基环森林**，存在自环。下面分三种情况对两个结点 $u$、$v$ 进行讨论:

###### $\text{u}$、$\text{v}$  不在同一棵基环树上

* 此种情况对应上图结点 **9、11**，我们发现他们无论怎么走都不可能走到一起，输出 ``-1 -1``。这里提供两种方法判断两点是否在同一棵基环树上

* 利用并查集维护连通性（我刚开始也是这么做的，但是发现在统计环长的时候可以同时处理，详见下）
* 判断两个点所在树的根节点是否在同一个环上，**topu** 找环对于环上结点遍历一遍即可，同时也可处理出环长 $u$、$v$ 在同一棵基环树上且位于环上同一结点的子树内

###### $\text{u}$、$\text{v}$  在同一棵基环树上且在环上同一结点的子树内

* 此种情况对应图上结点 **11、8**，此时两结点 **LCA** 即为答案，因为基环树树剖求 **LCA** 较为麻烦，所以我们采取倍增的方式
* ~~简单口胡证明：~~
  * 如果答案非 **LCA**，则必然在 **LCA** 的祖先结点或环上结点，但这样 **x、y** 都会增加，不会使答案更优，毫无裨益。
* 建反图，对于环上结点向其子树跑 **dfs**，将每一个节点打上“属于哪个根”的标记，即可判断两个节点是否在同一棵子树

###### $\text{u}$、$\text{v}$  在同一颗基环树上且在环上**不同**结点的子树内

* 此种情况对应图上结点 **11、2** ，此时相遇点必为两点所在树的根节点（记为 **fu、fv**）其中之一，我们需要求出在其中一点相遇时的答案根据题意取最优解即可
* ~~简单口胡证明：~~
  * 同上，如果答案非 **fu** 或 **fv** 而在其中一棵子树的结点处，则不能满足 $\max(u,v)$ 最小的条件，如答案在环上结点，则 **x、y** 都会增加，毫无裨益

拓扑排序找环即可



## code

我人菜代码写的有些难看（

**必写快读！！！**

```cpp
#include<bits/stdc++.h>
#define N 500010
using namespace std;

int cnt[N],n,m,book[N],fa[N][21],de[N],len[N],book2[N],step[N],tot;
vector<int>e[N];
queue<int>q;


void dfs(int u,int f,int rt,int d){
    de[u]=d;book[u]=rt;
    for(int i=0;i<e[u].size();i++){
        int v=e[u][i];
        if(cnt[v]||v==f)continue;
        dfs(v,u,rt,d+1);
    }
}

void pre(){
for(int p=1;p<=19;p++)
    for(int i=1;i<=n;i++){    
        fa[i][p]=fa[fa[i][p-1]][p-1];
    }
}

int lca(int x,int y){
    if(de[x]<de[y])swap(x,y);
    int tmp=de[x]-de[y];
    for(int i=19;i>=0;i--)if(tmp>>i&1)x=fa[x][i];
    if(x==y)return y;
    for(int i=19;i>=0;i--){
        if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
    }
    return fa[x][0];
}

void doit(int u,int id,int az){
    if(step[u])return;
    book2[u]=id;len[id]++;step[u]=az;
    doit(fa[u][0],id,az+1);
}

bool check(int a,int b,int c,int d){
    if(max(a,b)!=max(c,d))return max(a,b)<max(c,d);
    if(min(a,b)!=min(c,d))return min(a,b)<min(c,d);
    return a>=b;
}

signed main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        int u;scanf("%d",&u);
        e[u].push_back(i);
        fa[i][0]=u;
        cnt[u]++;
    }
    for(int i=1;i<=n;i++)if(!cnt[i])q.push(i);
    while(!q.empty()){
        int u=q.front();q.pop();
        int v=fa[u][0];
        cnt[v]--;
        if(!cnt[v])q.push(v);
    }
    for(int i=1;i<=n;i++){
        if(cnt[i]){
            dfs(i,0,i,0);
            if(!step[i])doit(i,++tot,1);
        }
    }
    pre();
    while(m--){
        int u,v;scanf("%d%d",&u,&v);
        if(book2[book[u]]!=book2[book[v]]){
			cout<<-1<<' '<<-1<<endl;
		}else if(book[u]==book[v]){
            int LCA=lca(u,v);
            cout<<de[u]-de[LCA]<<' '<<de[v]-de[LCA]<<endl;
        }else{
        	int t1=book[u],t2=book[v];
            int ans1=de[u]+(step[t2]-step[t1]+len[book2[t1]])%len[book2[t1]],ans2=de[v]+(step[t1]-step[t2]+len[book2[t1]])%len[book2[t1]];
			if(check(de[u],ans2,ans1,de[v]))cout<<de[u]<<' '<<ans2<<endl;
            else cout<<ans1<<' '<<de[v]<<endl;
        }
    }
	return 0;
}
/*
10 10
2 1 10 3 4 5 6 7 8 10
1 2
*/
```



---

## 作者：轻舟XY (赞：13)

[P3533 [POI2012]RAN-Rendezvous](https://www.luogu.com.cn/problem/P3533)  

## 题解

我们以样例为例，画个图来解释一下：

[![WusFi9.png](https://z3.ax1x.com/2021/07/15/WusFi9.png)](https://imgtu.com/i/WusFi9)

很容易看出，这是一个基环树森林。

下面进行分类讨论：

1. 两点不在同一棵基环树上，如 $10$ 和 $8$，他们本来就不连通，所以无论怎么走都走不到，即为无解。
2. 两点在在同一棵基环树上的同一棵子树中，从他们的 $LCA$ 开始知道这棵子树在环上的根节点的这一段上都是符合要求的。但是因为要使得 $\max(x,y)$ 最小，所以我们只查询其 $LCA$ 即可。例如上图中的 $8$ 和 $11$，在以 $1$ 为根节点的这棵子树中，我们直接查其 $LCA$，即为 $12$。
3. 两点在同一棵基环树上但不在同一棵子树中，我们先找到这两点所在子树在环上的根节点，因为这是有向图，要么是 $x$ 走向 $y$，要么是 $y$ 走向 $x$。而在这种情况下，相遇点一定是 $x$ 的树的根节点和 $y$ 的子树的根节点之一。

对于第 $3$ 种情况的解释：

[![WsKiRO.png](https://z3.ax1x.com/2021/07/23/WsKiRO.png)](https://imgtu.com/i/WsKiRO) 

我们以 $7$ 和 $2$ 为例，它们所在子树的根节点是 $1$ 和 $5$。首先，$7$ 和 $2$ 肯定先走到 $1$ 和 $5$。

然后我们来处理环上。我们发现 $1$ 和 $5$ 之间有两条路，可以是 $1\to 5$，也可以是 $1\to 4\to 5$。我们又不傻呀，显然要选择走短的那条。

但是这个样例无法说明为什么相遇点一定是两个根节点之一，所以我再拿个图证明一下：

[![WsY86P.png](https://z3.ax1x.com/2021/07/23/WsY86P.png)](https://imgtu.com/i/WsY86P)

以 $7$ 和 $10$ 为例，它们的根节点是 $5$ 和 $3$。

考虑对环的处理。若相遇点为 $5$，则路线为 $7\to 6\to 5\gets 4\gets 3\gets 10$（即图中的粉线）；若相遇点为 $3$，则路线为 $7\to 6\to 5\to 1\to 2\to 3\gets 10$（即图中的橙线）。肉眼可见地，粉线更短。

但是如果相遇点在环上的其他地方呢？现在我们设相遇点为 $4$：

[![WsdGdK.png](https://z3.ax1x.com/2021/07/23/WsdGdK.png)](https://imgtu.com/i/WsdGdK) 

路径变成了这样！它经过了 $3$，本来可以直接在 $3$ 处相遇了，但是又向环上拐到了 $4$，从而导致路径变得更长，从而比以 $3$ 为相遇点更劣（虽然 $3$ 本身也不是最优的选择）。

由不完全归纳法，环上其他不是选定的点所在子树根节点的点（有点绕）也会走这样的冤枉路，一定不会优于以根节点作为相遇点的情况，所以不能选，不需要讨论那些情况。

## 实现

实现上有些细节需要注意：

- 出度唯一但入度可能有很多，而我们需要知道一个点可能是从哪些点走过来的，所以可通过建反边的方式找到入度的那些点。

```cpp
	for(int i=1;i<=n;i++){
		read(f[i][0]);
		add(f[i][0],i);//建反边
		du[f[i][0]]++;//入度可能有很多
	} 
```

- 不在同一棵基环树上直接无解。

```cpp
		int fax=rtcir[x],fay=rtcir[y];//找x y所在子树在环上的根节点
		int cir_fax=belong[fax],cir_fay=belong[fay];
		if(cir_fax!=cir_fay){//不在同一个基环树上 无解
			printf("-1 -1\n");
			continue;
		}
```

- 在同一棵子树中直接查 $LCA$。

```cpp
		if(fax==fay){//在同一棵子树中 直接查LCA即可
			int LCA=lca(x,y);
			printf("%d %d\n",dep[x]-dep[LCA],dep[y]-dep[LCA]);
		}
```

- 需要记录环的长度 $siz[i]$，通过 $+siz[i]$ 再 $\%siz[i]$ 的方式避免出现负数。

```cpp
		else {
			int mod1=sizcir[cir_fax],mod2=sizcir[cir_fay];
			//mod1和mod2是等价的，因为它们所在的是同一个环，环的大小当然也一样，用哪个都可以啦
			// cout<<mod1<<" "<<mod2<<"***"<<endl;
			int t1=dep[x]+(cir[fay]-cir[fax]+mod1)%mod1;
			int t2=dep[y]+(cir[fax]-cir[fay]+mod2)%mod2;
			if(cmp(dep[x],t2,t1,dep[y])) printf("%d %d\n",dep[x],t2);
			else printf("%d %d\n",t1,dep[y]);
		}
```

最后放上主函数部分的代码，求 $LCA$ 、拓扑排序等部分请结合自己的思考写出~

```cpp
signed main(){
	read(n),read(Q);
	init(n);
	for(int i=1;i<=n;i++){
		read(f[i][0]);
		add(f[i][0],i);//建反边
		du[f[i][0]]++;//入度可能有很多
	} 
	topo();
	for(int i=1;i<=n;i++){
		if(!isc[i]){
			dfs(i,0,i,0);
			if(!cir[i]) getcir(1,i,++tot);
		}
	}
	for(int j=1;j<=25;j++){
		for(int i=1;i<=n;i++){
			f[i][j]=f[f[i][j-1]][j-1];
		}
	}
	for(int i=1;i<=Q;i++) {
		read(x),read(y);
		int fax=rtcir[x],fay=rtcir[y];//找x y所在子树在环上的根节点
		int cir_fax=belong[fax],cir_fay=belong[fay];
		if(cir_fax!=cir_fay){//不在同一个基环树上 无解
			printf("-1 -1\n");
			continue;
		}
		if(fax==fay){//在同一棵子树中 直接查LCA即可
			int LCA=lca(x,y);
			printf("%d %d\n",dep[x]-dep[LCA],dep[y]-dep[LCA]);
		}
		else {
			int mod1=sizcir[cir_fax],mod2=sizcir[cir_fay];
			//mod1和mod2是等价的，因为它们所在的是同一个环，环的大小当然也一样，用哪个都可以啦
			// cout<<mod1<<" "<<mod2<<"***"<<endl;
			int t1=dep[x]+(cir[fay]-cir[fax]+mod1)%mod1;
			int t2=dep[y]+(cir[fax]-cir[fay]+mod2)%mod2;
			if(cmp(dep[x],t2,t1,dep[y])) printf("%d %d\n",dep[x],t2);
			else printf("%d %d\n",t1,dep[y]);
		}
	} 
	return 0;
}
```



---

## 作者：小塘空明 (赞：5)

很明显这张图是由多颗基环树组成的。

我们对于每颗基环树找出它的环（本人习惯拓扑，调试方便不容易出错），并对于环上每个点，在不经过环上节点的基础上，预处理出每个节点子树内节点的深度用于后面的求值。

对于每颗基环树上的环，预处理出它的长度前缀和数组s和环长数组len，用于计算环上两点的距离。

对于每个询问a、b，有三种情况。

**（1）：** 两个节点不在同一个基环树上，输出-1，-1.

**（2）：** 两个节点位于环上同一个节点的子树内，求出lca计算即可。

**（3）：** 因为这颗基环数是内向树，所以我们a走向b和b走向a这两种情况进行讨论，取较优解。

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<cstring>
#include<cmath>
#include<queue>
using namespace std;
const int size=5e5+10;
int n,m,cnt,s[size],len[size],d[size],fa[size][21],bel[size],id[size],du[size];
int tot,head[size],ver[size*2],next[size*2];
queue<int> q;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	return x*f;
}
inline bool cmp(int x1,int y1,int x2,int y2){
	if(max(x1,y1)!=max(x2,y2)) return max(x1,y1)<max(x2,y2);
	if(min(x1,y1)!=min(x2,y2)) return min(x1,y1)<min(x2,y2);
	return x1>=y1;
}
inline void add(int x,int y){
	ver[++tot]=y;next[tot]=head[x];head[x]=tot;
}
inline int lca(int x,int y){
	if(d[x]>d[y]) swap(x,y);
	for(int i=20;~i;i--){
		if(d[fa[y][i]]>=d[x]) y=fa[y][i];
	}
	if(x==y) return x;
	for(int i=20;~i;i--){
		if(fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	}
	return fa[x][0];
}
int main(){
	n=read();m=read();
	for(int i=1;i<=n;i++) fa[i][0]=read(),du[fa[i][0]]++;
	for(int j=1;(1<<j)<=n;j++){
		for(int i=1;i<=n;i++){
			fa[i][j]=fa[fa[i][j-1]][j-1];
		}
	}
	for(int i=1;i<=n;i++) if(!du[i]) q.push(i);
	while(q.size()){
		int x=q.front();q.pop();
		if((--du[fa[x][0]])==0) q.push(fa[x][0]);
	}
	for(int i=1;i<=n;i++){
		if(du[i]&&!bel[i]){
			int j;
			for(j=i,++cnt;!bel[j];j=fa[j][0]){
				bel[j]=cnt;s[j]=++len[cnt];
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(bel[i]) d[i]=0,id[i]=i,q.push(i);
		else add(fa[i][0],i);
	}
	while(q.size()){
		int x=q.front();q.pop();
		for(int i=head[x];i;i=next[i]){
			int y=ver[i];
			d[y]=d[x]+1;id[y]=id[x];q.push(y);
		}
	}
	for(int i=1;i<=m;i++){
		int a=read(),b=read();
		if(bel[id[a]]!=bel[id[b]]) printf("-1 -1\n");
		else if(id[a]==id[b]){
			int p=lca(a,b);
			printf("%d %d\n",d[a]-d[p],d[b]-d[p]);
		}
		else{
			int x1=d[a]+(s[id[b]]-s[id[a]]+len[bel[id[a]]])%len[bel[id[a]]],y1=d[b];
			int x2=d[a],y2=d[b]+(s[id[a]]-s[id[b]]+len[bel[id[b]]])%len[bel[id[b]]];
			if(cmp(x1,y1,x2,y2)) printf("%d %d\n",x1,y1);
			else printf("%d %d\n",x2,y2);
		}
	}
	return 0;
}
```


---

## 作者：TKXZ133 (赞：3)

[RAN-Rendezvous](https://www.luogu.com.cn/problem/P3533)

### 题目大意

给定 $n$ 个点，每个点有且仅有一条出边，构成一个基环树森林。  

进行若干次询问，每次给出两个点 $A,B$，求一对正整数 $x,y$，使得从 $A$ 出发沿出边走 $x$ 步与从点 $B$ 出发走 $y$ 步到达的点相同，同时还要使 $x,y$ 尽可能小。

### 思路分析

我们首先可以想到，如果 $A,B$ 不在同一颗基环树上，那么肯定无解，所以我们可以用并查集来判断是否有解。

当 $A,B$ 在同一颗基环树上时，一定有解，但仍然需要分类讨论。

对于一颗基环树：

![](https://i.328888.xyz/2023/02/01/811mA.png)

如果点 $A,B$ 在环的某一节点的同一子树中，此时的答案显然是两点到其 $\text{LCA}$ 的距离。（如图中的 $8,9$ 两点）

否则，对于不在同一子树中的两点 $A,B$，它们通过走 $x$ 步和 $y$ 步到达的共同点一定在环上，且一定是其中一点所在子树的根。（如图中的 $9,10$ 两点）

- 这是因为，如果共同点不在环上，就不满足 $\max(x,y)$ 最小；如果不是其中一点所在子树的根，就不满足 $\min(x,y)$ 最小。

所以，这时我们应比较 $A,B$ 的根到达对方所需要的距离，然后取最小值才能得到结果。（比如 $9,10$ 两点对应的 $x,y$ 的路径分别是：$9\implies6\implies2$，$10\implies5\implies1\implies2$） 

### 做法

先用并查集维护两点是否在同一基环树中以及每个点所在子树的根，再通过 $\text{dfs}$ 求出所有的环以及环的长度，询问时通过树剖求两点的 $\text{LCA}$，就可以通过预处理出的信息求出 $x,y$。

具体看代码，注释较详细。


### 代码
```
#include <bits/stdc++.h>
using namespace std;
const int N=500500;
typedef long long ll;

struct IO{//快速读写
    int read(){
        int x=0;char ch=getchar();
        while(ch<'0'||'9'<ch) ch=getchar();
        while('0'<=ch&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
        return x;
    }
    void write(ll x){
        if(x<0){x=-x;putchar('-');}
        ll k=x/10;if(k)write(k);
        putchar(x-(k<<3)-(k<<1)+'0');
    }
    void print(ll x,char ch){
        write(x);putchar(ch);
    }
}I;

struct Unionfindset{//将并查集封装了，因为有两个并查集
    int fa[N];
    void init(int n){for(int i=1;i<=n;i++) fa[i]=i;}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    void merge(int x,int y){fa[find(x)]=find(y);}
    bool same(int x,int y){return find(x)==find(y);}
}block,root;//分别维护连通块和根

int idx,cnt,n,m,in1,in2;
int to[N],nxt[N],head[N],a[N];

void add(int u,int v){idx++;to[idx]=v;nxt[idx]=head[u];head[u]=idx;}
void Swap(int &x,int &y){int t=x;x=y;y=t;}

struct Treechainsplitting{//把树剖封装了
    int dfn[N],rnk[N],top[N],dep[N],siz[N],fa[N],son[N];//常规树剖7件套
    void dfs_1(int s,int gr){
        dep[s]=dep[gr]+1;
        siz[s]=1;son[s]=-1;
        fa[s]=gr;
        for(int i=head[s];i;i=nxt[i]){
            int v=to[i];
            if(dep[v]) continue;
            dfs_1(v,s);
            siz[s]+=siz[v];
            if(son[s]==-1||siz[v]>siz[son[s]]) son[s]=v;
        }
    }
    void dfs_2(int s,int tp){
        top[s]=tp;dfn[s]=++cnt;rnk[cnt]=s;
        if(son[s]==-1) return ;
        dfs_2(son[s],tp);
        for(int i=head[s];i;i=nxt[i]){
            int v=to[i];
            if(v==fa[s]||v==son[s]) continue;
            dfs_2(v,v);
        }
    }
    int lca(int x,int y){//树剖LCA
        while(top[x]!=top[y]){
            if(dep[top[x]]<dep[top[y]]) Swap(x,y);
            x=fa[top[x]];
        }
        return dep[x]>dep[y]?y:x;
    }
}tree;

struct Loop{//把找环的过程封装了
    ll num[N],len[N],dfn[N],cur;
    //num是点所在环的标记（如果不在环上也有标记，但无意义），len表示编号为i的环的长度，dfn是环上节点的dfs序，cur是环的编号
    bool loop[N];//标记是否在环上
    void find_loop(int s){
        num[s]=++cur;int temp=a[s];
        while(!num[temp]){num[temp]=cur;temp=a[temp];}//沿路径走找环
        if(num[temp]==cur){//如果找到了环（找到了相同标记的节点）
            ll t=0;len[cur]=1;loop[temp]=1;dfn[temp]=++t;int pos=a[temp];
            //t 是在环上的 dfs 序
            while(pos!=temp){len[cur]++;loop[pos]=1;dfn[pos]=++t;pos=a[pos];}
            //再绕一圈回去，同时更新环长，dfs序
        }
    }
}loop;

int main(){
    n=I.read();m=I.read();
    block.init(n);root.init(n);
    for(int i=1;i<=n;i++){
        a[i]=I.read();//a[i]表示i的出边所到达的点
        block.merge(i,a[i]);//维护连通性
    }
    for(int i=1;i<=n;i++)
        if(!loop.num[i]) loop.find_loop(i);//找环
    for(int i=1;i<=n;i++)
        if(!loop.loop[i]){root.merge(i,a[i]);add(a[i],i);}//如果不在环上才加边，并合并
    for(int i=1;i<=n;i++)
        if(loop.loop[i]) tree.dfs_1(i,0),tree.dfs_2(i,i);//树剖
    while(m--){
        in1=I.read();in2=I.read();
        if(!block.same(in1,in2)){I.print(-1,' ');I.print(-1,'\n');continue;}//无解
        if(root.same(in1,in2)){
            int LCA=tree.lca(in1,in2);
            I.print(tree.dep[in1]-tree.dep[LCA],' ');I.print(tree.dep[in2]-tree.dep[LCA],'\n');//在同一子树上，直接得结果
            continue;
        }
        ll x=tree.dep[in1]-1,y=tree.dep[in2]-1,u=root.find(in1),v=root.find(in2),cost_x,cost_y;
        //x,y表示两点到环的距离，u,v表示两点所在子树的根，cost_x,cost_y表示两点到达对方的花费
        ll dfnu=loop.dfn[u],dfnv=loop.dfn[v];
        if(dfnu<=dfnv) cost_x=dfnv-dfnu,cost_y=loop.len[loop.num[u]]-cost_x;//dfs序作差表示一点到另一点所需走的步数，用环长减一下就是另一种走法的步数
        else cost_y=dfnu-dfnv,cost_x=loop.len[loop.num[u]]-cost_y;
        if(x+cost_x<y+cost_y||(x+cost_x==y+cost_y&&x>=y)) I.print(x+cost_x,' '),I.print(y,'\n');//为了符合 x<=y 的条件
        else I.print(x,' '),I.print(y+cost_y,'\n');
    }
    return 0;
}
```

---

## 作者：Alex_Wei (赞：3)

> [P3533 [POI2012]RAN-Rendezvous](https://www.luogu.com.cn/problem/P3533)
>
> [POI 合集](https://www.cnblogs.com/alex-wei/p/POI.html)。

定义 $i$ 的祖先表示从 $i$ 一直走出边遇到的第一个在环上的结点，这个可以通过一遍 dfs 处理得到。处在同一子树（即奇环内向树的环上每个结点拖着的 “尾巴”，是一棵树）内的询问 $x,y$ 就是树上 LCA，预处理倍增数组。

除去上一种情况，若 $x,y$ 根本不在同一棵基环树上，显然无解，否则我们先跳到 $x,y$ 的祖先 $anc_x,anc_y$，有两种选择：$anc_x$ 顺着环走到 $anc_y$，或者 $anc_y$ 顺着环走到 $anc_x$。两种方案按照规则取更优的那个即可。时间复杂度线性对数。

写起来有点码农。

```cpp
const int K = 19;
const int N = 5e5 + 5;

int lg, n, q, a[N], deg[N], dep[N], anc[N];
int cnum, vis[N], col[N], pos[N], len[N];
int find(int id) {return anc[id] == id ? id : anc[id] = find(anc[id]);}

int cnt, hd[N], nxt[N], to[N], fa[K][N];
void add(int u, int v) {nxt[++cnt] = hd[u], hd[u] = cnt, to[cnt] = v;}
void dfs(int id) {
	vis[id] = 1;
	if(--deg[a[id]]) return anc[id] = a[id], void();
	dfs(a[id]), anc[id] = anc[a[id]];
} 
void dfs2(int id) {
	fa[0][id] = a[id], dep[id] = !vis[id] ? 0 : dep[a[id]] + 1;
	for(int i = 1; i <= lg; i++) fa[i][id] = fa[i - 1][fa[i - 1][id]];
	for(int i = hd[id]; i; i = nxt[i]) dfs2(to[i]);
}
int LCA(int x, int y) {
	if(dep[x] < dep[y]) swap(x, y);
	for(int i = lg; ~i; i--) if(dep[fa[i][x]] >= dep[y]) x = fa[i][x];
	if(x == y) return x;
	for(int i = lg; ~i; i--) if(fa[i][x] != fa[i][y]) x = fa[i][x], y = fa[i][y];
	return fa[0][x];
}

void deal(int id) {
	vis[id] = 1, anc[id] = id, col[id] = cnum, pos[id] = ++len[cnum];
	if(!vis[a[id]]) deal(a[id]);
}

int main(){
	cin >> n >> q, lg = log2(n);
	for(int i = 1; i <= n; i++) a[i] = read(), deg[a[i]]++;
	for(int i = 1; i <= n; i++) if(!deg[i] && !vis[i]) dfs(i);
	for(int i = 1; i <= n; i++) if(vis[i]) add(a[i], i);
	for(int i = 1; i <= n; i++) if(!vis[i]) dfs2(i); 
	for(int i = 1; i <= n; i++) if(!vis[i]) cnum++, deal(i);
	for(int i = 1; i <= n; i++) find(i);
	for(int i = 1; i <= q; i++) {
		int a = read(), b = read();
		if(col[anc[a]] != col[anc[b]]) {puts("-1 -1"); continue;}
		if(anc[a] == anc[b]) {
			int d = LCA(a, b);
			printf("%d %d\n", dep[a] - dep[d], dep[b] - dep[d]);
		} else {
			int x = dep[a], y = dep[b]; a = anc[a], b = anc[b];
			int _x = x + (pos[a] < pos[b] ? pos[b] - pos[a] : len[col[a]] + pos[b] - pos[a]);
			int _y = y + (pos[b] < pos[a] ? pos[a] - pos[b] : len[col[b]] + pos[a] - pos[b]);
			if(max(_x, y) < max(x, _y)) printf("%d %d\n", _x, y);
			else if(max(_x, y) > max(x, _y)) printf("%d %d\n", x, _y);
			else if(min(_x, y) < min(x, _y)) printf("%d %d\n", _x, y);
			else if(min(_x, y) > min(x, _y)) printf("%d %d\n", x, _y);
			else if(_x >= y) printf("%d %d\n", _x, y);
			else assert(x >= _y), printf("%d %d\n", x, _y);
		}
	}
	return flush(), 0;
}
```

---

## 作者：ctq1999 (赞：3)

一道 基环树 + LCA + 并查集 的题目，好题。

谁帮我看看[80pts](https://www.luogu.com.cn/discuss/show/226913)的代码？/kel

~~我™调了2天还是没过。~~

## 题意简述

给定一个 $n$ 个节点的内向基环树。

有 $q$ 组询问。

每组询问形式为`a b`，求点对`x y`满足：

1. 从`a`出发走`x`步和从`b`出发走`y`步会到达同一个点

2. 在 $1$ 的基础上如果有多解，那么要求 $max(x,y)$ 最小。

3. 在 $1$ 和 $2$ 的基础上如果有多解，那么要求 $min(x,y)$ 最小。

4. 如果在 $1$、$2$、$3$ 的基础上仍有多解，那么要求 $x\geq y$。

## 题解

基环树的题，一般需要找环。

这题有多棵基环树构成。

分情况讨论：

1. $a$ 和 $b$ 不在同一颗基环树内。

2. $a$ 和 $b$在同一颗环上子树内，LCA 求解。

3. $a$ 和 $b$ 在不同的环上子树内，求出 $a$ 和 $b$ 到各自环上子树的距离后，两点需要在环上相遇。现在假设 $a$ 和 $b$ 为各自环上子树的根节点。

   * 观察样例并思考，发现环的所有边的方向相同。
  
   * 相遇方式只有两种：那么 $a$ 去 $b$ 的位置，要么 $b$ 去 $a$ 的位置

这就是这题求解的思路了，接下来解释一下实现。

情况 $1$，并查集判断。

情况 $2$，找环时，对于任何一个环上的子树，$rt[]$ 把其所有节点标为这棵树的根。那么只要判断根是否相同。

情况 $3$，找环时，对于任何一个环上的子树，遍历时记录其深度（也就是到其根节点的距离），并初始化其 LCA 用到的 $f[][]$ 数组。

对于环上子树，一般的方法是从上到下遍历，这里可以从下到上遍历，会很方便。（这里不展开介绍了，详情见代码）

## 代码

```cpp
#include <bits/stdc++.h>

#define ll long long

using namespace std;

const int MAXN = 500010;
const int MAXM = 100010;
const int MAXINT = 2147483647;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;

int n, m, k;
int ans, tot, cnt;

int ins[MAXN], vis[MAXN];
int dep[MAXN], lg[MAXN], f[MAXN][50];
int bel[MAXN];
int sum[MAXN], rt[MAXN], ult[MAXN];

inline int read() {
	int s = 0, f = 1;
	char ch = getchar();
	while ('0' > ch || ch > '9') {if (ch == '-') f = -1; ch = getchar();}
	while ('0' <= ch && ch <= '9') {s = (s << 3) + (s << 1) + ch - 48; ch = getchar();}
	return s * f;
}

int find(int x) {
	while (x != bel[x]) x = bel[x] = bel[bel[x]];
	return x;
}

void dfs(int x) {
	vis[x] = ins[x] = 1;
	int y = f[x][0];
	if (ins[y]) {
		int num = 0, v = y;
		while (1) {
			rt[v] = v;
			sum[v] = ++num;
			ins[v] = 0;
			ult[v] = x;
			if (v == x) break;
			v = f[v][0];
		}
		return;
	}
	if (!vis[y]) dfs(y);
	if (!rt[x]) {
		dep[x] = dep[y] + 1;
		rt[x] = rt[y];
		ins[x] = 0;
	}
	for (int i = 1; (1 << i) <= dep[x]; i++) {
		f[x][i] = f[f[x][i - 1]][i - 1];
	}
	return;
}

int Lca(int x, int y) {
	if (dep[x] < dep[y]) swap(x, y);
	while (dep[x] > dep[y]) {
		x = f[x][lg[dep[x] - dep[y]] - 1];
	}
	if (x == y) return x;
	for (int i = lg[dep[x]]; i >= 0; i--) {
		if (f[x][i] != f[y][i]) {
			x = f[x][i];
			y = f[y][i];
		}
	}
	return f[x][0];
}

bool check(int x1, int y1, int x2, int y2) {
	if (max(x1, y1) != max(x2, y2)) return max(x1, y1) < max(x2, y2);
	if (min(x1, y1) != min(x2, y2)) return min(x1, y1) < min(x2, y2);
	return x1 >= y1;
}

int main(){
	int T, q;
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++) {
		bel[i] = i;
		lg[i] = lg[i - 1] + ((1 << lg[i - 1]) == i);
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", &f[i][0]);
		bel[find(i)] = find(f[i][0]);
	} 
	for (int i = 1; i <= n; i++) {
		if (!vis[i]) {
			dfs(i);
		}
	}
	for (int i = 1; i <= q; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		if (find(x) != find(y)) {
			puts("-1 -1");
			continue;
		}
		if (rt[x] == rt[y]) {
			int L = Lca(x, y);
			printf("%d %d\n", dep[x] - dep[L], dep[y] - dep[L]);
			continue;
		}
		int dx, dy;
		if (sum[rt[x]] < sum[rt[y]]) {
			dx = sum[rt[y]] - sum[rt[x]];
			dy = sum[ult[rt[x]]] - dx;
		}
		else {
			dy = sum[rt[x]] - sum[rt[y]];
			dx = sum[ult[rt[x]]] - dy;
		}
		if (check(dep[x] + dx, dep[y], dep[x], dep[y] + dy)) {
			printf("%d %d\n", dep[x] + dx, dep[y]);
		}
		else {
			printf("%d %d\n", dep[x], dep[y] + dy);
		}
	}
	return 0;
}
```

> 日供一卒，功不唐捐。


---

## 作者：liunian (赞：3)

~~这题不难吧，像我这种没打过多少倍增的人都能自己想出来~~
### 思路
首先由于每个点的出度均为1，因此这张图是基环内向森林，然后不难想到每个点一定会走到一个环上。

考虑两个点相遇的情况：

情况1：两个点最后到达的不在同一个环上，直接```puts("-1 -1")```

情况2：两个点到达环上时在同一个点(x)上，可以直接把x的环外子树提出来，**就成棵树了**，立马想到求两点的LCA。

情况3：除了以上两种情况，当两个点走到环上后，由于这是“追及问题”，A走得越多，B走得就越多，因此只有可能是A不动，B走向A；或是B不动，A走向B

### 解决方案

对于情况1，直接处理每个点最后到达环的编号即可

对于情况2，处理每个点最先到达环上节点的编号，然后可以建反边，求出每个非环上节点的dep值，然后倍增求LCA即可

对于情况3，给环上每个点依次编号，环上两点之间的距离就是```(id[x]-id[y]+SZ)%SZ```**注意x到y的距离 与 y到x的距离是两码事，原因很显然，环是单向的**，还有这题的输出比较毒瘤，但理清思路应该还是比较好些的，~~就因为这个，我WA了**6遍**~~

### 代码

应该还算精简吧

```
#include<bits/stdc++.h>
#define de puts("#")
#define bug(x) cout<<#x<<" : "<<x<<endl
using namespace std;
const int maxn=5e5+5;

int read() {
	int a=0;
	char c;
	while(c=getchar(),c<48);
	do a=(a<<1)+(a<<3)+(c^48);
	while(c=getchar(),c>=48);
	return a;
}

bool a1;
int n,q,to[maxn],deg[maxn],cnt,tot,qx,qy,fa[maxn][20],ID[maxn],sz[maxn],dep[maxn],head[maxn],from[maxn],tot1;
bool bl[maxn];
queue<int>Q;
bool b1;

struct node {
	int to,nxt;
} edge[maxn<<1];

void add(int x,int y) {
	edge[++tot]=(node)<%y,head[x]%>;
	head[x]=tot;
}

void getloop(int x,int id,int step) {
	if(ID[x])return;
	ID[x]=step,sz[id]++,to[x]=id;
	getloop(fa[x][0],id,step+1);
}

int LCA(int x,int y) {
	if(dep[x]>dep[y])swap(x,y);
	int step=dep[y]-dep[x];
	for(int i=19; i>=0; i--)if(step&(1<<i))y=fa[y][i];
	if(x==y)return x;
	for(int i=19; i>=0; i--)if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}

void dfs(int x,int f,int F,int D) {
	dep[x]=D,from[x]=F;
	for(int i=head[x]; i; i=edge[i].nxt) {
		int to=edge[i].to;
		if(to==f||!bl[to])continue;
		dfs(to,x,F,D+1);
	}
}

bool pd(int x1,int y1,int x2,int y2) {
	if(std::max(x1,y1)!=std::max(x2,y2))return std::max(x1,y1)<std::max(x2,y2);
	if(std::min(x1,y1)!=std::min(x2,y2))return std::min(x1,y1)<std::min(x2,y2);
	return x1>=y1;
}

int main() {
//	printf("%fMB\n",(&b1-&a1)/1024.0/1024);
	n=read(),q=read();
	for(int i=1; i<=n; i++)fa[i][0]=read(),add(fa[i][0],i),deg[fa[i][0]]++;
	for(int i=1; i<=n; i++)if(deg[i]==0)Q.push(i);
	while(!Q.empty()) {
		int x=Q.front();
		bl[x]=1;
		Q.pop();
		if(--deg[fa[x][0]]==0)Q.push(fa[x][0]);
	}
	for(int i=1; i<=n; i++) {
		if(!bl[i]) {
			dfs(i,0,i,0);
			if(!ID[i])getloop(i,++tot1,1);
		}
	}
	for(int k=1; k<=19; k++)
		for(int x=1; x<=n; x++)
			fa[x][k]=fa[fa[x][k-1]][k-1];
	while(q--) {
		qx=read(),qy=read();
		int fx=from[qx],fy=from[qy];
		if(to[fx]!=to[fy]) {
			puts("-1 -1");
			continue;
		} else if(fx==fy) {
			int lca=LCA(qx,qy);
			printf("%d %d\n",dep[qx]-dep[lca],dep[qy]-dep[lca]);
		} else {
			int more1=dep[qx]+(ID[fy]-ID[fx]+sz[to[fx]])%sz[to[fx]],more2=dep[qy]+(ID[fx]-ID[fy]+sz[to[fx]])%sz[to[fx]];
			if(pd(dep[qx],more2,more1,dep[qy]))printf("%d %d\n",dep[qx],more2);
			else printf("%d %d\n",more1,dep[qy]);
		}
	}
	return 0;
}
```


---

## 作者：SoyTony (赞：2)

分三种情况讨论。

- 若 $a_i,b_i$ 不在同一基环树，结果为 $x_i=-1,y_i=-1$。

- 若 $a_i,b_i$ 在基环树的同一子树，那么最终位置一定是首次相遇即 $\mathrm{LCA}(a_i,b_i)$，树剖即可。

- 若 $a_i,b_i$ 在同一基环树但不在同一子树，那么相遇位置一定在环上，容易发现如果相遇位置不是 $a_i,b_i$ 在环上的祖先，那么一定是二者相遇以后又同时移动了一段距离，一定不优。因此相遇位置只可能有两个：$a_i,b_i$ 在环上的祖先。二者取更优即可。

---

## 作者：ycyaw (赞：2)

感觉我写的最麻烦。

发现是基环树森林，显然先并查集一波，不在同一集内输出$(-1\ -1)$。

否则必然有解，然后发现一个点最终肯定走到环上，把环搞出来。

处理出每个点首次走到环的那个点是哪个，为$to[i]$。

然后如果两个点$to[i]$相同，那么这两个点的答案就是这两个点的$lca$。

否则肯定要先走到环上，然后肯定是其中一个点走向另一个点，算一下就好了。

由于本人菜，代码实现较为...复杂。

$Code\ Below:$
```cpp
#include<bits/stdc++.h>
#define ts cout<<"ok"<<endl
#define ll long long
#define hh puts("")
#define pc putchar
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
using namespace std;
const int N=500005;
int n,q,fa[N],f[N],bz[N][20],vis[N],col[N],id[N],ans1,ans2;
int col_cnt,size[N],inst[N],st[N],to[N],step[N],d[N],head[N],cnt;
struct Edge{
    int v,nx;
}e[N<<1];
inline int read(){
    int ret=0,ff=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') ff=-ff;ch=getchar();}
    while(isdigit(ch)){ret=(ret<<3)+(ret<<1)+ch-'0';ch=getchar();}
    return ret*ff;
}
void write(int x){
    if(x<0){x=-x;putchar('-');}
    if(x>9) write(x/10);
    putchar(x%10+48);
}
void writeln(int x){write(x),hh;}
void add(int x,int y){
    e[++cnt].v=y;
    e[cnt].nx=head[x];
    head[x]=cnt;
}
int find(int p){
    return f[p]==p?p:f[p]=find(f[p]);
}
void uni(int x,int y){
    int tx=find(x),ty=find(y);
    if(tx!=ty) f[tx]=ty;
}
void dfs(int now,int fa){
    d[now]=d[fa]+1;
    bz[now][0]=fa;
    for(int i=head[now];i;i=e[i].nx){
        int v=e[i].v;
        if(v==fa) continue;
        dfs(v,now);
    }
}
void lca(int x,int y){
    if(d[x]>d[y]){
        for(int i=19;i>=0;i--){
            if(d[bz[x][i]]>=d[y]){
                x=bz[x][i];
                ans1+=1<<i;
            }
        }
    }
    else if(d[y]>d[x]){
        for(int i=19;i>=0;i--){
            if(d[bz[y][i]]>=d[x]){
                y=bz[y][i];
                ans2+=1<<i;
            }
        }
    }
    if(x==y) return;
    for(int i=19;i>=0;i--){
        if(bz[x][i]!=bz[y][i]){
            x=bz[x][i],y=bz[y][i];
            ans1+=1<<i,ans2+=1<<i;
        }
    }
    ans1++,ans2++;
}
int dis(int x,int y){//环上两点距离 
    return (id[x]-id[y]+size[col[x]])%size[col[x]];
}
signed main(){
    n=read(),q=read();
    for(int i=1;i<=n;i++) f[i]=i;
    for(int i=1;i<=n;i++){
        fa[i]=read();
        uni(fa[i],i);
        bz[i][0]=fa[i];
    }
    for(int i=1;i<=n;i++){//求环,这个自己想怎么写怎么写 
        if(!vis[i]){
            int now=i;
            int top=0;
            while(!vis[now]){
                st[++top]=now;
                inst[now]=1;
                vis[now]=1;
                now=fa[now];
                if(inst[now]){
                    col_cnt++;
                    int t,idd=0;
                    do{
                        t=st[top];
                        top--;
                        inst[t]=0;
                        col[t]=col_cnt;
                        size[col_cnt]++;
                        id[t]=++idd;
                    }while(t!=now);
                }
            }
            while(top){
                inst[st[top]]=0;
                top--;
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(col[i]) continue;
        add(fa[i],i);
    }
    for(int i=1;i<=n;i++)//环上每个点的子树预处理 
        if(col[i])
            dfs(i,0);
    for(int k=1;k<=19;k++)
        for(int i=1;i<=n;i++)
            bz[i][k]=bz[bz[i][k-1]][k-1];
    for(int i=1;i<=n;i++){//预处理每个点走到环上是哪个点,并且要走几步 
        if(col[i]) to[i]=i;
        else{
            int now=i;
            for(int k=19;k>=0;k--)
                if(bz[now][k]){
                    now=bz[now][k];
                    step[i]+=1<<k;
                }
            to[i]=now;
        }
    }
    while(q--){
        int x=read(),y=read();
        if(x==y){
            puts("0 0");
            continue;
        }
        int tx=find(x),ty=find(y);
        if(tx!=ty){
            puts("-1 -1");
            continue;
        }
        tx=to[x],ty=to[y];
        if(tx==ty){
            ans1=0,ans2=0;
            lca(x,y);
            write(ans1),pc(' '),writeln(ans2);
        }
        else{//按规定输出答案 
            ans1=step[x],ans2=step[y];
            int t1=max(ans1+dis(tx,ty),ans2),t2=max(ans1,ans2+dis(ty,tx));
            if(t1<t2){
                write(ans1+dis(tx,ty)),pc(' '),writeln(ans2);
            }
            else if(t1>t2){
                write(ans1),pc(' '),writeln(ans2+dis(ty,tx));
            }
            else{
                t1=min(ans1+dis(tx,ty),ans2),t2=min(ans1,ans2+dis(ty,tx));
                if(t1<t2){
                    write(ans1+dis(tx,ty)),pc(' '),writeln(ans2);
                }
                else if(t1>t2){
                    write(ans1),pc(' '),writeln(ans2+dis(ty,tx));
                }
                else{
                    write(ans1+dis(tx,ty)),pc(' '),writeln(ans2);
                }
            }
        }
    }
    return 0;
}
```


---

## 作者：kczno1 (赞：2)

翻译:

Byteasar是箭头地窖的看管人，箭头地窖是一个著名的约会地点。

这个地窖包括n个单向走廊连接的房间。

每个房间恰好有一个用箭头标记的向外的走廊。

每个走廊指向一些不一定不同的房间。

那些同意在箭头地窖碰面的互相倾恋的男女们出了名的忘记商定具体的房间，所以必然的经常不能

找到他们的约会对象。

在过去，这导致很多混乱和误会。但自从每个房间给值班的看管人配备了应急电话线，帮助倾恋的男女们

找到他们的对象成了看管人的主要工作。

看管人想到了下述的方法。

知道那些男女在哪里之后，他们告诉每个男女他们要沿着箭头标记的走廊走多少次才能见到他们的对象。

男女们显然想尽快见面--毕竟,他们来地窖是共度时间，而不是独自闲逛的！

大部分看管人乐意帮忙:他们尽自己所能给每对男女一个有效的数对，使得他们中最大值最小。

但是有些人，例如Byteasar，厌倦了这个业余的活动并因而困惑。Byteasar让你写个程序来使过程简单些。

给出地窖的描述和k对男女现在的位置，你的程序应该确定k对xi,yi使得第i对男女:男的走xi步，女的

走yi步，之后就能在一个房间碰面，max(xi,yi)是最小的，在上面的前提下，min(xi,yi)是最小的，

如果上面的环境不能确定一个唯一解，那么女士应该走较小的距离(xi>=yi)。

可能xi,yi不存在，那么让xi=yi=-1。注意多对男女可以去同一个房间。一旦男女们找到了他们的对象，

他们将乐意再次迷失在地窖里(what)...


也就是给一些基环+内向树，之后询问两点:

如果两点在一棵树里，就是问到lca的距离；

否则就是环上y->x或x->y选一个走。

(如果两点不在一个分量就输出-1)


处理每个点在环上的那个根，同时记录所在环的标准点(随便选个)，处理标准点到环上的点顺着边走的距离，

而标准点记录的是环的长度。

对每棵树再处理一下树链剖分之类。

```cpp
#include<bits/stdc++.h>

#define N 500100
int f[N],t[N],next[N]; 
int belong[N],dis[N];//所属环的标准点 标准点到它的距离 
int deep[N],top[N],rt[N];//树上的深度,也是到所属根rt的距离 

int y,X;
void dfs(int x,int dep)
{
    static int son[N],sz[N];
    rt[x]=y;belong[x]=X;
    deep[x]=dep++;sz[x]=1;
    int &c=son[x],i;
    for (i=t[x];i;i=next[i])
    {
        dfs(i,dep);
        sz[x]+=sz[i];
        if (sz[i]>sz[c]) c=i;
    }
    for (i=t[x];i;i=next[i])
     for (int j=i;j;j=son[j]) top[j]=i;
} 
int Lca(int x,int y)
{
    int fx=top[x],fy=top[y];
    while (fx!=fy)
    if (deep[fx]>deep[fy]) {x=f[fx];fx=top[x];}
    else {y=f[fy];fy=top[y];}
    return deep[x]<deep[y]?x:y;
}
void del(int x,int son)//删掉x的son儿子 
{
    if (t[x]==son) t[x]=next[son];
    else
    {
        int i;
      for (i=t[x];next[i]!=son;i=next[i]);
      next[i]=next[son];
    }
}
void go(int x)
{
    for (;!belong[x];x=f[x]) belong[x]=1;//沿着边找环 
    X=x;
    y=f[x];
    int now=0;
    del(y,x);
    for (;;)
    {
        dis[y]=++now;
        dfs(y,0);
        if (y==x) break;
        del(f[y],y);
        y=f[y];
    }
}

int main()
{
    freopen("1.in","r",stdin);
    int n,m,i,x,y;
    scanf("%d%d",&n,&m);
    for (i=1;i<=n;++i) 
    {scanf("%d",f+i);
     next[i]=t[f[i]];t[f[i]]=i;
    }
    for (i=1;i<=n;++i)
    if (!belong[i])
     go(i);
    while (m--)
    {
        scanf("%d%d",&x,&y);
        if (belong[x]!=belong[y]) puts("-1 -1");
        else
        {
            int fx=rt[x],fy=rt[y];
            if (fx==fy) 
            {
                int lca=Lca(x,y);
                printf("%d %d\n",deep[x]-deep[lca],deep[y]-deep[lca]);
            }
            else
            {
                int disx=dis[fy]-dis[fx];//dis(fx->fy)
                if (disx<0) disx+=dis[belong[x]];
                int disy=dis[belong[x]]-disx;//dis(fy->fx)
                int d1x=disx+deep[x],d1y=deep[y];
                int mx1,mn1,mx2,mn2;
                if (d1x<d1y) {mx1=d1y;mn1=d1x;}
                else {mx1=d1x;mn1=d1y;}
                int d2x=deep[x],d2y=disy+deep[y];
                if (d2x<d2y) {mx2=d2y;mn2=d2x;}
                else {mx2=d2x;mn2=d2y;}
                bool d=0;
                if (mx1<mx2) d=1; else
                if (mx1==mx2) 
                 if (mn1<mn2) d=1; else
                 if (mn1==mn2) 
                  if (d1y<=d1x) d=1;
                if (d) printf("%d %d\n",d1x,d1y);
                else  printf("%d %d\n",d2x,d2y);
            }
        }
    }
}
```

---

## 作者：Laoshan_PLUS (赞：1)

基环树典型题。

### 题意

给定一个 $n$ 个顶点的内向基环森林和 $q$ 组询问，每个询问包含两个点 $a,b$，求点对 $(x,y)$ 满足：

1. 从 $a$ 出发走 $x$ 步和从 $b$ 出发走 $y$ 步会到达同一个点。
2. 在 1 的基础上如果有多解，那么要求 $\max(x,y)$ 最小。
3. 在 1 和 2 的基础上如果有多解，那么要求 $\min(x,y)$ 最小。
4. 如果在 1、2、3 的基础上仍有多解，那么要求 $x\ge y$。

如果不存在满足条件 1 的 $(x,y)$，输出 `-1 -1`。

### 解析

仍然用基环树的惯用套路，分类讨论。

**若存在满足条件 1 的 $\boldsymbol{(x,y)}$，即从 $\boldsymbol a$ 出发走 $\boldsymbol x$ 步和从 $\boldsymbol b$ 出发走 $\boldsymbol y$ 步会到达同一个点，那么定义这个点为 $\boldsymbol{a,b}$ 两点的 “交汇点”。**

1. 若 $a,b$ 都不在一个基环树里，直接输出 `-1 -1`。
2. 若 $a,b$ 在基环树环上同一点的子树内，则此时的交汇点就是 $a,b$ 的 LCA，不难证明。
3. 否则，答案要么是 $a$ 所在子树根节点，要么是 $b$ 所在子树根节点，同样不难证明：因为环是单向的，所以只要不是在这两个根节点，都会徒增路程而没有任何效益。

那么有了思路，接下来考虑如何实现。

首先肯定是一个 DFS 判基环树，对每个点作标记，然后就可以特判掉情况 1。

其次，对于情况 2，我们需要求出两点 LCA。肯定是用倍增，所以我们需要预处理 $\textit{fa}$ 和 $\textit{dep}$ 数组，所以需要求出每棵子树根节点。根节点一定在环上，所以 DFS 判环，再对于环上每个点预处理一下即可。然后对于情况 2 就可以直接求出 LCA。

最后，对于情况 3，我们需要求出：$\textit{dep}(i)$，表示子树上的点 $i$ 到子树根节点的距离，这里我们在预处理 LCA 时已经求过；$\textit{dis}(i,j)$，表示环上 $i,j$ 两点间距离，这里我们用前缀和的思想，对每个环跑一遍即可求出。统计答案的时候按照题目所给的意思比较两种答案最后输出即可。

### 实现

```cpp
#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 5e5 + 5;
int n, q;
vector<int> g[MAXN], G[MAXN];
int tr[MAXN];
bool vis[MAXN];
int stk[MAXN], top;
bool ring[MAXN], ins[MAXN];
int len[MAXN], dis[MAXN], ist[MAXN], tot;
int dep[MAXN], fa[MAXN][21];

void isring(int u) {
    if (ins[u]) {
        ring[u] = 1;
        for (int i = top; stk[i] != u; i--) ring[stk[i]] = 1;
        return;
    }
    if (vis[u]) return;
    vis[u] = 1;
    stk[++top] = u;
    ins[u] = 1;
    for (auto v : g[u]) isring(v);
    --top;
    ins[u] = 0;
}

void getfa(int u, int fno, int uu) {
    // cout << u << '\n';
    tr[u] = uu;
    fa[u][0] = fno;
    dep[u] = dep[fno] + 1;
    for (int i = 1; i <= 20; i++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (auto v : G[u]) if (!ring[v]) getfa(v, u, uu);
}

int lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	for (int i = 20; i >= 0; i--)
		if (dep[fa[u][i]] >= dep[v])
			u = fa[u][i];
	if (u == v) return v;
	for (int i = 20; i >= 0; i--)
		if (fa[u][i] != fa[v][i]) {
			u = fa[u][i];
			v = fa[v][i];
		}
	return fa[u][0];
}

void ringlen(int u, int t, int fno) {
    if (dis[u]) return;
    ist[u] = t;
    len[t]++;
    dis[u] = dis[fno] + 1;
    for (auto v : g[u]) if (ring[v]) ringlen(v, t, u);
}

bool check(int a1, int a2, int b1, int b2) {
    if (max(a1, a2) != max(b1, b2)) return max(a1, a2) < max(b1, b2);
    if (min(a1, a2) != min(b1, b2)) return min(a1, a2) < min(b1, b2);
    return a1 >= a2;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    // freopen("ran3c.in", "r", stdin);
    // freopen("ans.out", "w", stdout);
    cin >> n >> q;
    for (int i = 1, v; i <= n; i++) {
        cin >> v;
        // if (i == v) continue;
        g[i].push_back(v);
        G[v].push_back(i);
    }
    // for (int i = 1; i <= n; i++) {
    //     cout << i << ": ";
    //     for (auto v : G[i]) cout << v << ' ';
    //     cout << '\n';
    // }
    for (int i = 1; i <= n; i++) if (!vis[i]) isring(i);
    // for (int i = 1; i <= n; i++) cout << ring[i] << '\n';
    for (int i = 1; i <= n; i++) if (ring[i]) getfa(i, 0, i);
    for (int i = 1; i <= n; i++) if (ring[i] && !dis[i]) ringlen(i, ++tot, 0);
    // cout << find(1) << ' ' << find(4) << ' ' << find(5) << '\n';
    // cout << len[ist[1]] << '\n';
    int x, y;
    while (q--) {
        cin >> x >> y;
        if (ist[tr[x]] != ist[tr[y]]) cout << "-1 -1\n";
        else if (tr[x] == tr[y]) {
            int LCA = lca(x, y);
            cout << dep[x] - dep[LCA] << ' ' << dep[y] - dep[LCA] << '\n';
        } else {
            int ans1 = dep[y] - 1 + (dis[tr[x]] - dis[tr[y]] + len[ist[tr[x]]]) % len[ist[tr[x]]];
            int ans2 = dep[x] - 1 + (dis[tr[y]] - dis[tr[x]] + len[ist[tr[x]]]) % len[ist[tr[x]]];
            // cout << dep[x] - 1 << ' ' << ans1 << ' ' << ans2 << ' ' << dep[y] - 1 << ' ';
            // cout << check(dep[x] - 1, ans1, ans2, dep[y] - 1) << '\n';
            if (check(dep[x] - 1, ans1, ans2, dep[y] - 1)) cout << dep[x] - 1 << ' ' << ans1 << '\n';
            else cout << ans2 << ' ' << dep[y] - 1 << '\n';
        }
    }

    return 0;
}
```

---

## 作者：xfrvq (赞：1)

以前的题，补个题解。

考虑思维量最低的 $\tt dfs$ 找环：首先并查集维护联通块，对于每个联通块任取一点不停跳 $fa$，直到跳到一个环，标记。

$\tt LCA$ 考虑倍增求：对于每个环上的点，走非环边必将走出一棵树，在上面维护倍增的 $fa,dep$ 数组，同时对于这棵树，对每个点维护其 **最近环上祖先**。

对询问分类讨论：

+ 不在一个联通块：不可能走到。
+ 在一个联通块但 最近环上祖先 相同：直接倍增，最后两点与其 $\tt lca$ 深度之差就是答案。
+ 在一个联通块但 最近环上祖先 不同，记录 $x,y$ 分别是 $u,v$ 的最近环上祖先，计算 $x\to y$ 和 $y\to x$ 两种跳法哪种更优即可。

代码很短了。

```cpp
#define rep(i,a,b) for(int i = (a);i <= (b);++i)
#define Rep(i,a,b) for(int i = (a);i >= (b);--i)

int n,m,fa[N],vis[N],cir[N],f[N],siz[N],ft[N][22],dep[N],anc[N];
vector<int> G[N];

int fnd(int x){ return x == f[x] ? x : f[x] = fnd(f[x]); }

void dfs(int u,int p){ anc[u] = p; for(int v : G[u]) dep[v] = dep[u] + 1,dfs(v,p); }

void init(){
	rep(i,1,n) f[i] = i;
	rep(i,1,n) f[fnd(i)] = fnd(fa[i]);
	rep(i,1,n) if(i == fnd(i)){
		int j = i; while(!vis[j]) vis[j] = 1,j = fa[j];
		int k = j,t = 0; while(!cir[k]) cir[k] = ++t,k = fa[k]; siz[i] = t;
	}
	rep(i,1,n) if(!cir[i]) ft[i][0] = fa[i],G[fa[i]].push_back(i);
	rep(j,1,20) rep(i,1,n) ft[i][j] = ft[ft[i][j - 1]][j - 1];
	rep(i,1,n) if(cir[i]) dfs(i,i);
}

void qry(int u,int v){
	if(fnd(u) != fnd(v)) return print(-1,' ',-1,'\n');
	if(anc[u] == anc[v]){
		int x = u,y = v;
		if(dep[x] < dep[y]) swap(x,y);
		Rep(i,20,0) if(dep[ft[x][i]] >= dep[y]) x = ft[x][i];
		if(x != y){
			Rep(i,20,0) if(ft[x][i] != ft[y][i]) x = ft[x][i],y = ft[y][i];
			x = ft[x][0];
		}
		return print(dep[u] - dep[x],' ',dep[v] - dep[x],'\n');
	}
	int x = anc[u],y = anc[v],a,b,c,d,s = siz[fnd(u)];
	a = c = dep[u] - dep[x],b = d = dep[v] - dep[y];
	cir[x] < cir[y] ? a += cir[y] - cir[x] : b += cir[x] - cir[y];
	cir[x] > cir[y] ? c += s - cir[x] + cir[y] : d += s - cir[y] + cir[x];
	if(max(a,b) ^ max(c,d)) max(a,b) < max(c,d) ? print(a,' ',b,'\n') : print(c,' ',d,'\n');
	else if(min(a,b) ^ min(c,d)) min(a,b) < min(c,d) ? print(a,' ',b,'\n') : print(c,' ',d,'\n');
	else { if(a >= b) print(a,' ',b,'\n'); else print(c,' ',d,'\n'); }
}
```

---

## 作者：complete_binary_tree (赞：0)

首先，对于每一个基环树，我们把基环树分为“环”和“树”的部分。

显然，对于询问，我们可以这样处理：

- 如果它们不在一个连通块内，那么无解（可以在搜基环树时用并查集保存）。

- 如果它们在基环树中一个子树中，那么套上树剖 $\text{lca}$ 的板子就行了。

  我们可以对每一个环上的节点的子树进行树剖，而不对环上的节点进行树剖，相当于在做树剖的时候环是不存在（环边都断开）的。

- 如果在基环树的不同子树中：

  我们知道，他们一定在环上相遇，所以我们需要让他们先走到环上。

  我们可以标记对于每一个点 $u$ 环上离它最近的点的位置 $top_u$。这可以在预处理树剖 $\text{lca}$ 的时候可以顺便预处理。（树剖的顶端节点放的变量名由于冲突变成了 $ttop$）

  这样就可以算出从任意一点 $u$ 走到环上的代价就是 $dep_u - dep_{top_u}$。

  当 $a,b$ 走到环上后，他们在环上有两种走法：一种 $a \to b$，另一种 $b \to a$。

  可以对环上每个节点沿着环的方向做一遍前缀和，点 $u$ 存在 $sum_u$ 中。

  此时，$a \to b$ 的代价就是 $sum_b - sum_a$（这个值有可能小于 $0$，小于 $0$ 要加上环长才是对的）。

  相对地，$b \to a$ 的代价就是环长减去 $a \to b$ 的代价。

  然后我们就可以算出两组答案，于是就可以按照题目的~~神秘~~方法求得最终答案。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;

//并查集
struct bcj {
    int fa[N];
    int find( int x ) { return fa[x] == x ? x : fa[x] = find( fa[x] ); }
    void add( int a, int b ) { fa[find( a )] = find( b ); }
    bcj() {}
    bcj( int n ) { while( n-- ) fa[n] = n; }
} bc1, bc2;

//链式前向星
struct edge { 
    int to, nxt;
    edge() {}
    edge( int to, int nxt ) : to( to ), nxt( nxt ) {}
} e[N];
int head[N], cnt;
void add( int u, int v ) { e[++cnt] = edge( v, head[u] ), head[u] = cnt; }
int n, tot, fa[N], dep[N], sum[N], id[N], cir_len[N], top[N], k, son[N], ttop[N], siz[N];
bool cir[N], vis[N], can;
vector<int> huan[N];

//搜索子树&树剖一体
void dfs( int u, const int& rt, const int& tp ) {
    siz[u] = 1; bc2.add( u, tp ); //bc2是同子树的并查集
    vis[u] = 1; bc1.add( u, rt ); top[u] = tp; //bc1是同基环树的并查集
    dep[u] = ( u == tp ? 0 : dep[fa[u]] + 1 );
    for( int i = head[u]; i; i = e[i].nxt ) {
        int v = e[i].to;
        if( cir[v] ) continue; //不能搜到环，只能往树边走
        dfs( v, rt, tp );
        siz[u] += siz[v];
        if( siz[v] > siz[son[u]] ) son[u] = v;
    }
}

//树剖的第二遍搜
void dfs2( int u, int f ) {
    ttop[u] = f;
    if( !son[u] ) return ;
    dfs2( son[u], f );
    for( int i = head[u]; i; i = e[i].nxt ) {
        int v = e[i].to;
        if( v == son[u] || cir[v] ) continue;
        dfs2( v, v );
    }
}

//预处理每一个环
void prework( int id, int rt ) {
    //找出环上一个点
    while( !vis[rt] ) vis[rt] = 1, rt = fa[rt];

    //找出环上所有点
    int i = fa[rt]; cir[rt] = 1; huan[id].push_back( rt );
    while( rt != i ) sum[fa[i]] = sum[i] + 1, huan[id].push_back( i ), cir[i] = 1, i = fa[i], bc1.add( i, rt );

    //对环上的每一个节点进行树剖和其他处理
    for( auto i : huan[id] ) dfs( i, rt, i ), dfs2( i, i ), ::id[i] = id;

    //第id个基环树的环长
    cir_len[id] = huan[id].size();
}

pair<int, int> query( int a, int b ) {
    //不在同个基环树内
    if( bc1.find( a ) != bc1.find( b ) ) return make_pair( -1, -1 );

    //在同个子树内
    if( bc2.find( a ) == bc2.find( b ) ) {
        int x = dep[a], y = dep[b];
        while( ttop[a] != ttop[b] ) {
            int ta = ttop[a], tb = ttop[b];
            if( dep[ta] > dep[tb] ) a = fa[ta];
            else b = fa[tb];
        }
        int lca = ( dep[a] > dep[b] ? b : a );
        return make_pair( x - dep[lca], y - dep[lca] );
    }

    //不在同个子树内
    //1-走到环上
    int x = dep[a], y = dep[b];
    a = top[a], b = top[b];

    //2-环上
    int len = sum[a] - sum[b];
    if( len < 0 ) len += cir_len[id[a]];
    //这里的len是b->a的代价，贡献到y上

    //减去的才是a->b的代价
    int x2 = x + cir_len[id[a]] - len, y2 = y; y += len;
    //两组答案{x,y}{x2,y2}

    //进行神秘比较
    if( max( x2, y2 ) == max( x, y ) ) {
        if( min( x2, y2 ) == min( x, y ) ) {
            return x >= y ? make_pair( x, y ) : make_pair( x2, y2 );
        }
        return min( x2, y2 ) > min( x, y ) ? make_pair( x, y ) : make_pair( x2, y2 );
    }
    return max( x2, y2 ) > max( x, y ) ? make_pair( x, y ) : make_pair( x2, y2 );
}

int main(){
    scanf( "%d%d", &n, &k );
    for( int i = 1; i <= n; ++i ) {
        scanf( "%d", &fa[i] );
        add( fa[i], i );
    }
    bc2 = bc1 = bcj( n );
    int cnt = 0;
    //预处理每一个基环树
    for( int i = 1; i <= n; ++i ) 
        if( !vis[i] )
            prework( ++cnt, i );
    while( k-- ) {
        int a, b;
        scanf( "%d%d", &a, &b );
        auto ans = query( a, b );
        printf( "%d %d\n", ans.first, ans.second );
    }
    return 0;
}
```

---

## 作者：WrongAnswer_90 (赞：0)

题目大意：给定外向树森林，每次给定两个起始点，求两个点沿边移动最少步数相遇。

$n$ 个点，$n$ 条边，并且每个点有唯一的出边，显然构成了多棵基环树，对于每个基环树分别处理：找出环上的点，因为要求支持求出任意两点距离，前缀和一下即可。

对于询问，如果在两棵不同的基环树上（具体判断使用并查集），那么一定无解。如果在一棵基环树的同一棵子树内，求 LCA 并记录一下深度即可求出，代码实现使用的倍增。对于剩下的情况，进行分讨：

![image.png](https://s2.loli.net/2023/09/09/cWNXB7HApKuRsZ2.png)

首先肯定是要花 $dep-1$ 步走到环上，接下来有两种选择：从 $top_x$ 走到 $top_y$ 或者从 $top_y$ 走到 $top_x$。具体的，我们给 $1,2,3,5$ 赋权值为 $1,2,3,4$ 红色的距离就是 $4-1=3$，蓝色的距离是 $1-4+4$ 加 $4$ 是因为正好越过了整个环。 

感觉思维难度完全到不了紫，实现稍微麻烦一点，遵循题目中的条件，判断自环等特殊情况，一定要注意判断环的方向！

```cpp
	int n,q,cnt=1,flag,tot,f[1000001],loop[1000001],val[1000001],maxn[1000001],vis[1000001],a[1000001],dis[1000001],head[1000001],to[1000001],nex[1000001],dep[1000001],fa[1000001][31],top[1000001];
	inline void add(int x,int y){to[++cnt]=y,nex[cnt]=head[x],head[x]=cnt;}
	stack<int> st;
	void dfs(int k,int from)
	{
		vis[k]=1,!flag?st.e(k),1:1;
		for(int i=head[k];i;i=nex[i])
		{
			if(i==(from^1))continue;
			if(!flag&&vis[to[i]])
			{
				while(st.top()!=to[i])loop[++tot]=st.top(),st.pop();
				loop[++tot]=st.top(),st.pop(),flag=1;
				while(!st.empty())st.pop();
			}
			if(!vis[to[i]])dfs(to[i],i);
		}
		!flag?st.pop(),1:1;
	}
	void dfs2(int k,int father)
	{
		top[k]=top[father],dep[k]=dep[father]+1,fa[k][0]=father;
		for(int i=1;i<=30;++i)fa[k][i]=fa[fa[k][i-1]][i-1];
		for(int i=head[k];i;i=nex[i])if(vis[to[i]]==1&&to[i]!=father)dfs2(to[i],k);
	}
	inline int LCA(int x,int y)
	{
		if(dep[x]>dep[y])swap(x,y);
		for(int i=30;i>=0;--i)if(dep[fa[y][i]]>=dep[x])y=fa[y][i];
		for(int i=30;i>=0;--i)if(fa[y][i]!=fa[x][i])y=fa[y][i],x=fa[x][i];
		return x==y?x:fa[x][0];
	}
	int find(int x){return x==f[x]?x:f[x]=find(f[x]);}
	inline void mian()
	{
		read(n,q);int x,y,z,lca,t,w;
		for(int i=1;i<=n;++i)f[i]=i;
		for(int i=1;i<=n;++i)read(a[i]),add(i,a[i]),add(a[i],i),f[find(a[i])]=find(i);
		for(int i=1;i<=n;++i)
		{
			if(vis[i])continue;
			flag=tot=0,dfs(i,0);
			if(a[loop[1]]!=loop[2])reverse(loop+1,loop+1+tot);
			for(int j=1;j<=tot;++j)vis[loop[j]]=2;
			for(int j=1;j<=tot;++j)maxn[loop[j]]=tot,val[loop[j]]=val[loop[j-1]]+1,top[0]=loop[j],dfs2(loop[j],0);
		}
		while(q--)
		{
			read(x,y);
			if(find(x)!=find(y)){puts("-1 -1");continue;}
			if(top[x]==top[y])lca=LCA(x,y),write(dep[x]-dep[lca]),write(dep[y]-dep[lca],'\n');
			else
			{
				z=val[top[y]]-val[top[x]];if(z<0)z+=maxn[top[x]];
				t=val[top[x]]-val[top[y]];if(t<0)t+=maxn[top[x]];
				if(max(dep[x]-1+z,dep[y]-1)< max(dep[y]-1+t,dep[x]-1)
				|| max(dep[x]-1+z,dep[y]-1)==max(dep[y]-1+t,dep[x]-1)&&min(dep[x]-1+z,dep[y]-1)< min(dep[y]-1+t,dep[x]-1)
				|| max(dep[x]-1+z,dep[y]-1)==max(dep[y]-1+t,dep[x]-1)&&min(dep[x]-1+z,dep[y]-1)==min(dep[y]-1+t,dep[x]-1)&&dep[x]-1+z>=dep[y]-1)write(dep[x]-1+z),write(dep[y]-1,'\n');
				else write(dep[x]-1),write(dep[y]-1+t,'\n');
			}
		}
	}
```

---

## 作者：Unnamed114514 (赞：0)

首先，根据题意，可以发现这是个基环森林。

我们可以对如下三种情况进行分类讨论：

- $u,v$ 不连通

此时 $u,v$ 无论走多远都不能相遇，所以答案是 `-1 -1`。

那么下面的情况都是 $u,v$ 处于同一棵基环树上的情况

- $u,v$ 的路径不经过环

令 $top_u$ 为 $u$ 一直向上走后走到的环上的点，因为 $u,v$ 之间的路径不经过环，所以 $top_u=top_v$，并且 $u,v$ 之间的路径一定在以 $top_u$ 为根的子树上，此时我们只需要对 $(u,v)$ 求解 LCA 即可。

- $u,v$ 的路径经过环

此时 $top_u\ne top_v$，那么我们无论如何都要跑到环上，令 $a=top_u,b=top_v$。

那么此时就有两种情况：第一种是 $a\rightarrow b$，第二种是 $b\rightarrow a$，那么我们只需要根据题目中的比较条件来选择即可。

时间复杂度 $O(n\log n)$，空间复杂度 $O(n)$。

---

