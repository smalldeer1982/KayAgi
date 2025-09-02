# Johnny Solving

## 题目描述

今天是星期二，这意味着 JOHNNY SOLVING 团队又有争论了：他们试图搞清楚谁是 Johnny，谁是 Solving。因此，他们请 Umnik 来帮忙。Umnik 给了他们一个连通图，这个图有 $n$ 个顶点，没有自环和重边，且每个顶点的度数至少为 $3$，同时还给了一个数 $1 \leq k \leq n$。由于 Johnny 不太聪明，他承诺能在图中找到一条长度至少为 $\frac{n}{k}$ 的简单路径。作为回应，Solving 承诺能找到 $k$ 个互不相交的简单顶点环，并且每个环都满足：

- 每个环的长度至少为 $3$。
- 每个环的长度不能被 $3$ 整除。
- 每个环中必须有一个“代表”顶点，这个顶点在所有输出的环中只属于这一环。

你需要帮助他们解决争论，也就是说，你需要为 Johnny 找到一条长度至少为 $\frac{n}{k}$ 的简单路径，或者为 Solving 找到 $k$ 个满足上述条件的环。如果没有任何一种方案，输出 $-1$。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 6 2
1 2
1 3
1 4
2 3
2 4
3 4
```

### 输出

```
PATH
4
1 2 3 4 ```

## 样例 #2

### 输入

```
10 18 2
1 2
1 3
1 4
1 5
1 6
1 7
1 8
1 9
1 10
2 3
3 4
2 4
5 6
6 7
5 7
8 9
9 10
8 10
```

### 输出

```
CYCLES
4
4 1 2 3 
4
7 1 5 6 
```

# 题解

## 作者：foreverlasting (赞：9)

[安利一波博客](https://foreverlasting1202.github.io/)

C Johnny Solving

题面：给出一张无重边的无向图（保证每个点度数大于等于3）和一个限制$k$，需要你构造以下两种情况中的一种：

1、找出一条路径长度为$n/k$。

2、找出$k$个环，使得每个环的长度大于3而且不是3的倍数，并且要求保证每个环中至少有一个点在这$k$个环里只出现一次。

做法：构造题。我整整想了两个小时，惨的一批。第一个情况很好找，先建出一棵树，然后在上面求直径就好了。第二个情况就不好搞了，首先，我们要知道如果不存在第一个情况的时候，一棵生成树的叶子结点数一定大于等于$k$。

这其实很好证明的。我们用反证法。假设少于$k$个叶子结点且没有第一种情况，则说明每一个叶子结点的深度要小于$n/k$，那么所有叶子结点到根的距离之和就会小于$n-1$了。这显然是不存在的，因为叶子结点到根的距离至少包含了每条边一次，所以就证好了。

然后对于每个叶子结点，我们可以证明的是它一定能构造出一个符合条件的环。

因为一个点度数大于等于3，那么对于一个叶子结点而言，除了它父亲以外，至少还有两个它的祖先与它有连边。如果其中一个与祖先连边构成的环长度满足不是3的倍数就可以了，因为叶子结点一定只被选一遍。否则我们把它的两个祖先和它相连的环弄出来，那个环一定满足条件。

稍微证明一下。假设叶子结点为$p$，两个祖先分别为$a$,$b$，其中$dep[a]<dep[b]$。

我们有$dep[p]-dep[a]+1$是3的倍数，$dep[p]-dep[b]+1$是3的倍数，那么$dep[b]-dep[a]+2$一定不是3的倍数（两个做差），于是就证好了。

因此就构造出来了。

code:
```cpp
//2019.1.25 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define eps 1e-10
inline int read() {
    res s=0;
    bool w=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') {
        if(ch=='-')w=1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return w?-s:s;
}
inline void _swap(res &x,res &y) {
    x^=y^=x^=y;
}
inline int _abs(const res &x) {
    return x>0?x:-x;
}
inline int _max(const res &x,const res &y) {
    return x>y?x:y;
}
inline int _min(const res &x,const res &y) {
    return x<y?x:y;
}
typedef vector<int> vec;
#define pb push_back
const int N=2.5e5+10,M=5e5+10;
namespace MAIN {
    vec leaf;
    struct E{
        int next,to;
        E() {}
        E(res next,res to):next(next),to(to) {}
    }edge[M<<1];
    int head[N],cnt;
    inline void addedge(const res &u,const res &v){
        edge[++cnt]=E(head[u],v),head[u]=cnt;
        edge[++cnt]=E(head[v],u),head[v]=cnt;
    }
    bool vis[N],lea[N];
    int fa[N],dep[N];
    int n,m,k;
    void dfs(const res &x,const res &fax,const res &depx){
        fa[x]=fax,dep[x]=depx,vis[x]=1;
        if(depx>=(n+k-1)/k){
            puts("PATH");
            printf("%d\n",depx);
            for(res i=x;i;i=fa[i])printf("%d ",i);
            puts("");
            exit(0);
        }
        for(res i=head[x];~i;i=edge[i].next){
            res tox=edge[i].to;
            if(vis[tox])continue;
            dfs(tox,x,depx+1),lea[x]=1;
        }
        if(!lea[x])leaf.pb(x);
    }
    inline bool cmp(const res &x,const res &y){
        return dep[x]<dep[y];
    }
    inline void MAIN(){
        memset(head,-1,sizeof(head));
        n=read(),m=read(),k=read();
        for(res i=1;i<=m;i++){
            res u=read(),v=read();
            addedge(u,v);
        }
        dfs(1,0,1);
        puts("CYCLES");
        for(res t=0;t<k;t++){
            res x=leaf[t];
            bool flag=0;
            vec pos;
            pos.clear();
            for(res i=head[x];~i;i=edge[i].next){
                res tox=edge[i].to;
                if(pos.size()!=2)pos.pb(tox);
                if(tox==fa[x]||(dep[x]-dep[tox]+1)%3==0)continue;
                printf("%d\n",dep[x]-dep[tox]+1);
                for(res p=x;p!=fa[tox];p=fa[p])printf("%d ",p);
                puts("");
                flag=1;
                break;
            }
            if(flag)continue;
            sort(pos.begin(),pos.end(),cmp);
            printf("%d\n",dep[pos[1]]-dep[pos[0]]+2);
            res a=pos[0],b=pos[1];
            while(fa[a]!=fa[b])printf("%d ",b),b=fa[b];
            printf("%d %d\n",b,x);
        }
    }
}
int main() {
    MAIN::MAIN();
    return 0;
}
```

---

## 作者：zac2010 (赞：4)

任取一颗 $\text{DFS}$ 树。

如果最大深度 $\geq\frac{n}{k}$，则找到了一条路径。

对于剩下的情况，我们按环去处理。钦定一个合法环中的“代表点”为 $k$ 个环中只出现过一次的点。

考虑让叶子作为环的代表点。我们寻找到了一些性质：由于树高 $<\frac{n}{k}$，故而树至少有 $k$ 个叶子，同时根据题目给出的“每个叶子度数 $\geq3$”，易得出：每个叶子至少有两条返祖边（无向图的 $\text{DFS}$ 树没有横叉边）。

此时，再尝试分析叶子 $i$ 两条返祖边 $(i,p1),(i,p2)$ 能构成的方案（假设 $p1$ 的深度 $<p1$ 的深度）。那么环的情况必定是以下三种之一：

![image](https://cdn.luogu.com.cn/upload/image_hosting/9zusgkq0.png)

分类讨论一下即可发现，三种情况中必定有一种环长不为 $3$ 的倍数。

```cpp
#include <bits/stdc++.h>
#define FL(i, a, b) for(int i = (a); i <= (b); i++)
#define FR(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
const int N = 2.5e5 + 10;
int n, m, k, tot; vector<int> e[N];
int fa[N], p1[N], p2[N], vis[N], dfn[N], dep[N];
void jump(int u, int p, int c = 0){
	printf("%d\n", dep[u] - dep[p] + 1 + (c > 0));
	if(c) printf("%d ", c);
    for(int i = u; i != fa[p]; i = fa[i]) printf("%d ", i);
}
void dfs(int u){
    dfn[u] = ++tot, dep[u] = dep[fa[u]] + 1;
    for(int &v: e[u]) if(v != fa[u]){
        if(!dfn[v]) vis[fa[v] = u] = 1, dfs(v);
        else p2[u] = (p1[u]? v : 0), p1[u] = (p1[u]? p1[u] : v);
    }
}
int main(){
    scanf("%d%d%d", &n, &m, &k);
    FL(i, 1, m){
        int u, v; scanf("%d%d", &u, &v);
        e[u].emplace_back(v), e[v].emplace_back(u);
    }
    dfs(1);
    FL(i, 1, n) if(dep[i] > (n - 1) / k){
        printf("PATH\n"), jump(i, 1);
		printf("\n"); return 0;
    }
    printf("CYCLES\n");
    FL(i, 1, n) if(!vis[i] && k-- > 0){
        if((dep[i] - dep[p1[i]]) % 3 < 2) jump(i, p1[i]);
        else if((dep[i] - dep[p2[i]]) % 3 < 2) jump(i, p2[i]);
        else{
            if(dep[p1[i]] > dep[p2[i]]) swap(p1[i], p2[i]);
            jump(p2[i], p1[i], i);
        }
        putchar('\n');
    }
    return 0;
}
```


---

## 作者：Aisaka_Taiga (赞：3)

## Q1

我们分析一下两个问题就会发现第一问是比较好判断的，因为如果我们用 DFS 求一棵生成树，看一下直径是否 $\ge \lfloor\frac{n}{k}\rfloor$ 就好了。

## Q2

第一问，如果不成立，那就说明直径是小于 $\lfloor\frac{n}{k}\rfloor$ 的，同理可以推出树的最大深度也是小于 $\lfloor\frac{n}{k}\rfloor$ 的，而题目说了保证每个点的度数大于等于 $3$，这样你是构造不出叶子节点小于 $k$ 的树的，因为如果要没有 $\ge \lfloor\frac{n}{k}\rfloor$ 的链的话，链最长为 $\lfloor\frac{n}{k}\rfloor-1=\lfloor\frac{n-k}{k}\rfloor$，那么最优的构造就是菊花图。

**这里其实是把构造出来的菊花图的中心点算了 $n$ 次，但实际上的值比 $\lfloor\frac{n-k}{k}\rfloor$ 要小，所以后面叶子节点数的结论还是成立的。**

![](https://cdn.luogu.com.cn/upload/image_hosting/d9dnjjs9.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/lmgb8q5r.png)

显然第二种更优，因为同样的叶子节点数包含了更多的点。

所以链数 $=$ 叶子节点数 $=n\times \lfloor\frac{k}{n-k}\rfloor= \lfloor \frac{n\times k}{n-k}\rfloor$，因为 $n\ge k$ 所以 $n\times k\ge k^{2}$，$n$ 一定是大于 $n-k$ 的，将 $\lfloor\frac{n}{n-k}\rfloor$ 看作一个已知数的话一定是恒大于 $1$ 的，所以这个式子的值一定是恒大于等于 $k$ 的，但由于是向下取整所以是有可能等于 $k$ 的，所以叶子节点数肯定是 $\ge k$ 的。

题目中说保证每个点度数大于等于 $3$，那么叶子节点肯定就只能是和自己上面的点连，也就是返祖边，因为没有重边所以一定有两条连在父亲节点往上的点的边，那么一定有一个环是大于 $3$ 的。也许你会问为什么一定是返祖边而不是横叉边，因为我们是按 DFS 序找的生成树，假如我们最后得到的生成树是下面的模样：

![](https://cdn.luogu.com.cn/upload/image_hosting/wuzg8wuc.png)

如果要是 $F\to E$ 有边，那么我们在 DFS 的时候 $E$ 会成为 $F$ 的子节点，也就是说在这个 DFS 生成树上是不存在横叉边的，是 DFS 序保证了剩余的两条边都是返祖边。

所以我们这样就一定至少能找出 $k$ 个环了，但是如何处理对于环的限制？

对于至少一个点在 $k$ 个环里只出现一次，我们只要对于每一个叶子节点都只计算一个环就好了，这样每一个叶子节点都是只出现了一次。

对于环的长度 $len>3$ 且 $len\bmod 3 \ne 0$，我们可以想一下，设 $dep_{i}$ 表示 $i$ 号点在生成树上的深度。

我们画个图就可以知道：

![](https://cdn.luogu.com.cn/upload/image_hosting/funjo9d4.png)

上图中以 $J$ 为叶子节点讨论有三个环：

1. $J,H,F$ 构成的环，长度为 $dep_{J}-dep_{F}+1$。

2. $J,H,F,D,B$ 构成的环，长度为 $dep_{J}-dep_{B}+1$。

3. $J,F,D,B$ 构成的环，长度为 $dep_{F}-dep_{B}+2$。

那么万一里面没有符合条件的环呢？

设当前点为 $u$，返祖边连向的祖先为 $x,y$。

如果 $dep_{u}-dep_{x}+1$ 和 $dep_{u}-dep_{y}+1$ 都为 $3$ 的倍数，那么两个式子做差可以得到 $dep_{x}-dep_{y}$ 为 $3$ 的倍数，那么加上 $2$ 肯定就不是 $3$ 的倍数了，其他两种情况也是这样，可以得出每一个叶子节点必定有一个环符合要求。

上面的推理都是基于生成树上的点的最大深度 $<\lfloor\frac{n}{k}\rfloor$ 的，所以也就是说只要生成树上的点的最大深度小于 $\lfloor\frac{n}{k}\rfloor$ 第二问就有解，所以我们可以不用求树的直径，直接在 DFS 的时候顺便处理每一个点的深度就好，最后用这个值来判断做第一问还是第二问。

code：

```cpp
#include<bits/stdc++.h>
#define N 1000100
#define M 250010
#define endl '\n'
using namespace std;
int n,m,k,cnt,head[N],cl,ye[M],dep[M],fa[M],zx[M][2],mxdep,ed;
struct sb{int u,v,next;}e[N];
inline void add(int u,int v){e[++cnt].v=v;e[cnt].next=head[u];head[u]=cnt;}
inline int read(){int x=0,f=1;char ch=getchar();while(!isdigit(ch)){f=ch!='-';ch=getchar();}while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return f?x:-x;}
inline void print(int u,int v){cout<<v<<" ";if(u==v)return ;print(u,fa[v]);}
inline void dfs(int u,int f,int dp)
{
	dep[u]=dp;
	if(dep[u]>mxdep)mxdep=dep[u],ed=u;
	fa[u]=f;
	ye[++cl]=u;
	for(int i=head[u];~i;i=e[i].next)
	{
		int v=e[i].v;
		if(v==f)continue;
		if(dep[v]){if(!zx[u][0])zx[u][0]=v;else zx[u][1]=v;continue;}
		if(ye[cl]==u)cl--;
		dfs(v,u,dp+1);
	}
}
signed main()
{
	memset(head,-1,sizeof head);
	n=read(),m=read(),k=read();
	for(int i=1;i<=m;i++)
	{
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	dfs(1,-1,1);
	if(mxdep>=n/k)
	{
		cout<<"PATH"<<endl<<mxdep<<endl;
		while(ed!=-1)cout<<ed<<" ",ed=fa[ed];
		return 0;
	}
	cout<<"CYCLES"<<endl;
	for(int i=1;i<=k;i++)
	{
		int u=ye[i],x=zx[u][0],y=zx[u][1];
		if(dep[x]>dep[y])swap(x,y);
		if((dep[u]-dep[x]+1)%3!=0)//u和x构成环 
		{
			cout<<(dep[u]-dep[x]+1)<<endl;
			print(x,u);cout<<endl;
		}
		else if((dep[u]-dep[y]+1)%3!=0)//u和y构成环 
		{
			cout<<(dep[u]-dep[y]+1)<<endl;
			print(y,u);cout<<endl;
		}
		else//x和y构成环 
		{
			cout<<(dep[y]-dep[x]+2)<<endl<<u<<" ";
			print(x,y);cout<<endl;
		}
	}
	return 0;
}
```

---

## 作者：KingPowers (赞：2)

[题目链接](https://www.luogu.com.cn/problem/CF1103C)

考虑在 dfs 树上进行构造。

如果 dfs 树上存在一个点 $u$ 满足 $dep_u\ge\lceil\frac{n}{k}\rceil$，那么直接输出从根到 $u$ 的路径，可以解决 `PATH` 问题。

如果所有结点的深度都不足 $\lceil\frac{n}{k}\rceil$，那么显然有叶子结点的个数至少为 $k$。同时题目保证了每个点的度数大于等于 $3$，因此每个叶子结点也至少会有两条返祖边。

现在我们来尝试解决 `CYCLE` 问题，考虑对每个叶子结点任取两条返祖边，利用它们构造出环。我们不妨画几张~~抽象的~~图来讨论下。

我们记 $u$ 为叶子结点，两条返祖边所指的祖先分别为 $f,gf$，如果 $u-f$ 或者 $u-gf$ 和其对应的非树边（分别对应下图的绿色和紫色部分）能够直接形成满足条件的环：

![](https://cdn.luogu.com.cn/upload/image_hosting/7880juj9.png)

那么直接选合法的那一个输出即可。

否则，我们会发现图中蓝色的部分一定也是合法的：

![](https://cdn.luogu.com.cn/upload/image_hosting/qm7xqbbh.png)

因为如果 $u-f$ 和 $u-gf$ 不合法，那么 $u$ 和 $f$ 在树上的距离以及 $u$ 和 $gf$ 在树上的距离一定模 $3$ 余 $2$，从而可以推出 $f$ 和 $gf$ 在树上的距离为 $3$ 的倍数，加上两条非树边后一定满足条件。

~~图很丑，轻喷。~~

时间复杂度：$O(n+m)$。

```cpp
int n,m,k,dep[N],fa[N];
vector<int>G[N],e[N];
bool leaf[N],vis[N];
int Ceil(int a,int b){return (a+b-1)/b;}
void dfs(int now,int f){
	dep[now]=dep[f]+1;fa[now]=f;
	bool flag=0;vis[now]=1;
	for(int to:G[now]){
		if(to==f) continue;
		if(!vis[to]) flag=1,dfs(to,now);
		else if(dep[now]>dep[to]) e[now].pb(to);
	}
	if(dep[now]>=Ceil(n,k)){
		cout<<"PATH\n"<<dep[now]<<'\n';
		while(now) cout<<now<<' ',now=fa[now];
		exit(0);
	}
	if(!flag) leaf[now]=1;
}
void print(int now){
	int f=e[now][0],gf=e[now][1];
	if(dep[f]<dep[gf]) swap(f,gf);
	if((dep[now]-dep[f]+1)%3){
		cout<<dep[now]-dep[f]+1<<'\n';
		while(now!=fa[f]) cout<<now<<' ',now=fa[now];
		cout<<'\n';
	}
	else if((dep[now]-dep[gf]+1)%3){
		cout<<dep[now]-dep[gf]+1<<'\n';
		while(now!=fa[gf]) cout<<now<<' ',now=fa[now];
		cout<<'\n';
	}
	else{
		cout<<dep[f]-dep[gf]+2<<'\n';
		cout<<now<<' ';now=f;
		while(now!=fa[gf]) cout<<now<<' ',now=fa[now];
		cout<<'\n';
	}
}
void Main(){
	cin>>n>>m>>k;
	For(i,1,m){
		int u,v;cin>>u>>v;
		G[u].pb(v);G[v].pb(u);
	}
	dfs(1,0);cout<<"CYCLES\n";
	int cnt=0;
	For(i,1,n){
		if(leaf[i]) print(i),cnt++;
		if(cnt==k) break;
	}	
}
```

---

## 作者：NBest (赞：0)

找路径很好找，我们随便跑个 dfs 树找个深度 $\ge \frac{n}{k}$ 的路径输出即可。

可是怎么找 $k$ 个长度不是 $3$ 的倍数的环呢？既然我们跑了 dfs 树，那么就没有横叉边，对于叶子节点非树边只有返祖边，然后一看这个很奇怪的条件——保证每个点度数大于等于 3，那岂不是叶子节点可以至少构成两个环？加上两个返祖边构成的环，一共有三个环？我们假设两个祖先分别是 $u,v$，叶子为 $x$，那么三个环的大小分别为 $dep_u-dep_x+1$，$dep_v-dep_x+1$，$dep_u-dep_v+2$，显然必然有至少一个不是 $3$ 的倍数。

又要求每个环至少有一个点在这 $k$ 个环里只出现一次，我们不能保证我们连上去的返祖边构成的环不包括原来的节点，但是我们可以保证让一个叶子节点只选一个环。上面已经说了每个叶子节点至少可以搞出一个合法环，那有 $k$ 个吗？

我们如果找不到路径，说明任意的 $dep_x<\frac{n}{k}$，而每个叶子节点跑到根肯定包含了所有点，也就是 $\sum_{x\in leaf} dep_x\ge n$（为链时取等），显然个数不可能小于 $k$。

所以这时我们直接找每个叶子节点的两条返祖边然后特判即可。因为每个环的大小必然不超过 $dep_x$，要输出 $k$ 个环，那么输出个数不会超过 $\sum k\times dep_x\le n$，符合题意。

## $Code$
```cpp
typedef long long ll;
const int N=250005;
int n,m,k,dep[N],fa[N];
vector<int>f[N];
bool is_leaf[N];
stack<int>S;
void dfs(int x){
    S.push(x);
    dep[x]=dep[fa[x]]+1;
    for(int y:f[x])
        if(!dep[y])fa[y]=x,is_leaf[x]=1,dfs(y);
    if(dep[x]>=n/k){
        puts("PATH");
        printf("%d\n",dep[x]);
        while(!S.empty())printf("%d ",S.top()),S.pop();
        exit(0);
    }
    S.pop();
}
int main(){
    n=read(),m=read(),k=read();
    for(int i=1,u,v;i<=m;i++)
        f[u=read()].push_back(v=read()),f[v].push_back(u);
    dfs(1);
    puts("CYCLES");
    for(int x=1,w=0;w<k&&x<=n;x++){
        if(is_leaf[x])continue;
        int u=0,v=0;
        for(int y:f[x])
            if(y==fa[x])continue;
            else if(!u)u=y;
            else if(!v)v=y;
            else break;
        if(dep[u]<dep[v])u^=v^=u^=v;
        if((dep[x]-dep[v]+1)%3!=0){
            printf("%d\n",dep[x]-dep[v]+1);
            for(int o=x;o!=fa[v];o=fa[o])printf("%d ",o);
        }else if((dep[x]-dep[u]+1)%3!=0){
            printf("%d\n",dep[x]-dep[u]+1);
            for(int o=x;o!=fa[u];o=fa[o])printf("%d ",o);
        }else{
            printf("%d\n",dep[u]-dep[v]+2);
            for(int o=u;o!=fa[v];o=fa[o])printf("%d ",o);
            printf("%d ",x);
        }
        puts("");
        w++;
    }
    return 0;
}
```

---

## 作者：happybob (赞：0)

考虑对此无向图建出 DFS 树，也就是 DFS 一次。

如果这棵树直径 $\geq \frac{n}{k}$，直接把路径找出来即可。

否则，我们找出所有叶子节点，树上必然至少有 $k$ 个叶子。由于每个。点度数大于等于 $3$，所以每个叶子必然有不小于两条返祖边。假设叶子节点为 $u$，其返祖边中任意两个点 $v,z$。由于是返祖边，显然 $u \rightarrow v$，$u \rightarrow z$，$v \rightarrow u \rightarrow z$ 都是环。我们设这三个点在 DFS 树上的深度分别为 $a,b,c$。那么，$u \rightarrow v$ 的环长度为 $a-b+1$，$u \rightarrow z$ 的环长度为 $a-c+1$，$v \rightarrow u \rightarrow z$ 的长度为 $b-c+2$。容易发现其中必然有一个不是 $3$ 的倍数。于是第一个限制满足了。

接着每个叶子节点作为那个只出现一次的点即可，就做完了。

```cpp
#pragma GCC optimize("-Ofast,fast-math,-inline")
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <set>
#include <cassert>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

const int N = 5e5 + 5;

int n, m, k;
vector<int> G[N];

int fa[N], dis[N];
bool f = 1;
int maxlen = -1, nowu = 0;
bool vv[N];

void dfs(int u, int f)
{
	vv[u] = 1;
	fa[u] = f;
	dis[u] = dis[f] + 1;
	if (dis[u] > maxlen)
	{
		maxlen = dis[u];
		nowu = u;
	}
	for (auto& j : G[u])
	{
		if (j != f && !vv[j])
		{
			dfs(j, u);
		}
	}
}

bool vis[N];
int cnt = 0;
int dep[N];
set<pair<int, int> > st;
int p = 0;

void ndfs(int u, int f)
{
	fa[u] = f;
	dep[u] = dep[f] + 1;
	vis[u] = 1;
	int c = 0;
	for (auto& j : G[u])
	{
		if (j == f) continue;
		if (!vis[j])
		{
			c++;
		}
	}
	int cc = 0;
	int X1 = 0, X2 = 0;
	for (auto& j : G[u])
	{
		if (j == f) continue;
		if (vis[j] && !c && !cc)
		{
			if (!X1) X1 = j;
			else X2 = j;
			if (st.count(make_pair(u, j))) continue;
			st.insert(make_pair(u, j));
			st.insert(make_pair(j, u));
			int len = dep[u] - dep[j] + 1;
			if (len % 3 == 0 || len < 3) continue;
			cnt++;
			cout << len << "\n";
			int ru = u;
			cc++;
			while (ru != j)
			{
				cout << ru << " ";
				ru = fa[ru];
			}
			cout << j << " ";
			cout << "\n";
			if (cnt == k)
			{
				exit(0);
			}
		}
		else if (!vis[j])
		{
			ndfs(j, u);
		}
	}
	if (!cc && !c)
	{
		if (dep[X1] < dep[X2]) swap(X1, X2);
		int len = dep[X1] - dep[X2] + 2;
		if (len % 3 != 0 && len > 3)
		{
			cout << len << "\n" << u << " ";
			int nowu = X1;
			while (nowu != X2)
			{
				cout << nowu << " ";
				nowu = fa[nowu];
			}
			cout << X2 << "\n";
			cnt++;
			if (cnt == k) exit(0);
		}
	}
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> m >> k;
	for (int i = 1; i <= m; i++)
	{
		int u, v;
		cin >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	dfs(1, 0);
	memset(vv, 0, sizeof vv);
	f = 0;
	int p = nowu;
	maxlen = -1;
	nowu = 0;
	dfs(p, 0);
	if (maxlen >= (n - 1) / k + 1)
	{
		cout << "PATH\n";
		cout << maxlen << "\n";
		while (nowu != p)
		{
			cout << nowu << " ";
			nowu = fa[nowu];
		}
		cout << p << " ";
		cout << "\n";
		return 0;
	}
	memset(dep, 0, sizeof dep);
	memset(fa, 0, sizeof fa);
	memset(vis, 0, sizeof vis);
	st.clear();
	cout << "CYCLES\n";
	ndfs(1, 0);
	return 0;
}
```


---

## 作者：wind_whisper (赞：0)

## $\text{Description}$
给出一张无重边的无向图（保证每个点度数大于等于 $3$）和一个限制 $k$，需要你构造以下两种情况中的一种：

1、找出一条路径长度为 $n/k$。

2、找出 $k$ 个环，使得每个环的长度大于 $3$ 而且不是 $3$ 的倍数，并且要求保证每个环中至少有一个点在这 $k$ 个环里只出现一次。
## $\text{Solution}$
不错的一道题。  
不难想到先建出 dfs 生成树的套路。  
然后，若直径大于 $n/k$，就已经满足条件一了。  
否则，必然有每个结点的深度不超过 $n/k$，那么叶子的数量必然不少于 $k$ 个。  
同时，每个叶子 $u$ 必然至少有两条非树返祖边。，假设分别连向 $x,y$。  
分类讨论一下一定有一个不是 $3$ 的倍数的环。  
把叶子作为代表结点即可。  
## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=5e5+100;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)) {x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}
int n,m,k;
struct node{
  int to,nxt;
}p[N<<1];
int fi[N],cnt;
inline void addline(int x,int y){
  p[++cnt]=(node){y,fi[x]};fi[x]=cnt;
  return;
}
bool vis[N],jd[N];
vector<int>v[N];
int fa[N],dep[N];
void dfs(int x,int f){
  fa[x]=f;dep[x]=dep[f]+1;vis[x]=1;
  for(int i=fi[x];~i;i=p[i].nxt){
    int to=p[i].to;
    if(to==f) continue;
    if(vis[to]){
      if(dep[to]<dep[x]) v[x].push_back(to);      
    }
    else{
      jd[x]=1;dfs(to,x);
    }
  }
  return;
}
void print(int x,int tp){
  //printf("%d\n",dep[x]-dep[tp]+1);
  while(x!=fa[tp]) printf("%d ",x),x=fa[x];
  putchar('\n');
  return;
}
inline bool ok(int o){return o>2&&o%3;}
bool bac[4];
bool pd[N];
signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  memset(fi,-1,sizeof(fi));cnt=-1;
  n=read();m=read();k=read();
  for(int i=1;i<=m;i++){
    int x=read(),y=read();
    addline(x,y);addline(y,x);
  }
  dfs(1,0);
  for(int i=1;i<=n;i++){
    if(1ll*dep[i]*k>=n){
      printf("PATH\n");
      printf("%d\n",dep[i]);
      print(i,1);return 0;
    }
  }
  printf("CYCLES\n");
  for(int i=1;i<=n&&k;i++){
    int x(0),y(0),z(0);bac[0]=bac[1]=bac[2]=0;
    if(jd[i]) continue;
    for(auto now:v[i]){
      if(pd[now]) continue;
      if(ok(dep[i]-dep[now]+1)){
	printf("%d\n",dep[i]-dep[now]+1);
	pd[i]=1;
	print(i,now);k--;break;
      }
      else if(x&&ok(abs(dep[x]-dep[now])+1+1)){
	if(dep[x]>dep[now]) swap(x,now);
	printf("%d\n%d ",dep[now]-dep[x]+1+1,i);
	print(now,x);
	pd[i]=1;k--;
	break;
      }
      else if(y&&ok(abs(dep[y]-dep[now])+1+1)){
	if(dep[y]>dep[now]) swap(y,now);
	printf("%d\n%d ",dep[now]-dep[y]+1+1,i);
	print(now,y);
	pd[i]=1;k--;
	break;
      }
      else if(z&&ok(abs(dep[z]-dep[now])+1+1)){
	if(dep[z]>dep[now]) swap(z,now);
	printf("%d\n%d ",dep[now]-dep[z]+1+1,i);
	print(now,z);
	pd[i]=1;k--;
	break;
      }
      if(!bac[dep[now]%3]){
	bac[dep[now]%3]=1;
	if(!x) x=now;
	else if(!y) y=now;
	else if(!z) z=now;
      }
    }
  }
  return 0;
}
/*

*/

```


---

## 作者：尹昱钦 (赞：0)

## 解题思路
在图上很难做这种构造题，所以一种常用的方法是求出其**生成树**。

在**生成树**上做就容易很多。

于是这个题就按照 dfs 序建立一颗生成树，记录下每个节点的返祖边。

于是第一问可以**根据树的深度判断**是否符合要求，符合的话直接输出。

若没有，则易证第二问一定成立：

因为第一问不成立，所以叶子节点数一定 $\geqslant k$，而题中保证每个节点的度数 $\geqslant3$，也就暗示了叶子节点都有 $\geqslant2$ 条返祖边。

**所以一定能从每个叶子节点找到一个符合要求的环。**

假设叶子节点 k 的两个返祖祖先为 x 和 y，则通过作差法易证：

$(dep[u]-dep[x]+1)$ 和 $(dep[u]-dep[y]+1)$ 和 $(dep[y]-dep[x]+2)$ 中至少有一个不是 $3$ 的倍数。

判断一下输出即可。
## 注意
数组一定要开够：大小为 m 的两倍！否则会在第四个点TLE。
## AC代码
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<iomanip>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=5e5+5;
int n,m,k,cnt,cnt_leaf,leaf[maxn],p[maxn],dep[maxn],fa[maxn],ancestor[maxn][105];
int maxdep,ed;
template <typename T>
inline void read(T &x)
{
    char c;
    x=0;
    int fu=1;
    c=getchar();
    while(c>57||c<48){
        if(c==45){
        	fu=-1;
        }
        c=getchar();
    }
    while(c<=57&&c>=48)
    {
        x=(x<<3)+(x<<1)+c-48;
        c=getchar();
    }
    x*=fu;
}
struct node{
	int v,next;
}e[maxn*2];
void insert(int u,int v){
	cnt++;
	e[cnt].v=v;
	e[cnt].next=p[u];
	p[u]=cnt;
}
void dfs(int u,int f,int deep){
	dep[u]=deep;
	if(dep[u]>maxdep){
		maxdep=dep[u];
		ed=u;
	}
	fa[u]=f;
	leaf[++cnt_leaf]=u;
	for(int i=p[u];i!=-1;i=e[i].next){
		int v=e[i].v;
		if(v==f) continue;
		if(dep[v]){
			ancestor[u][++ancestor[u][0]%100]=v;
			continue;
		}
		if(leaf[cnt_leaf]==u) cnt_leaf--;
		dfs(v,u,deep+1);
	}
}
void print(int u,int to){
	printf("%d ",to);
	if(u==to) return;
	print(u,fa[to]);
}
int main(){
	memset(p,-1,sizeof(p));
	read(n);
	read(m);
	read(k);
	for(int i=1;i<=m;i++){
		int u,v;
		read(u);
		read(v);
		insert(u,v);
		insert(v,u);
	} 
	dfs(1,-1,1);
	if(maxdep>=(n-1)/k+1){
		puts("PATH");
		printf("%d\n",maxdep);
		while(ed!=-1){
			printf("%d ",ed);
			ed=fa[ed];
		}
		return 0;
	}
	puts("CYCLES");
	for(int i=1;i<=k;i++){
		int u=leaf[i],x=ancestor[u][1],y=ancestor[u][2];
		if(dep[x]>dep[y]) swap(x,y);
		if((dep[u]-dep[x]+1)%3!=0){
			printf("%d\n",dep[u]-dep[x]+1);
			print(x,u);
			puts("");
		}else{
			if((dep[u]-dep[y]+1)%3!=0){
				printf("%d\n",dep[u]-dep[y]+1);
				print(y,u);
				puts("");
			}else{
				printf("%d\n%d ",dep[y]-dep[x]+2,u);
				print(x,y);
				puts("");
			}
		}
	}
    return 0;
}
```CF1103C Johnny Solving

---

