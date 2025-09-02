# QTREE2 - Query on a tree II

## 题目描述

 You are given a tree (an undirected acyclic connected graph) with **N** nodes, and edges numbered 1, 2, 3...**N**-1. Each edge has an integer value assigned to it, representing its length.

 We will ask you to perfrom some instructions of the following form:

- **DIST a b** : ask for the distance between node **a** and node **b**  
   or
- **KTH a b k** : ask for the **k**-th node on the path from node **a** to node **b**

 **Example:**  
**N** = 6   
 1 2 1 // edge connects node 1 and node 2 has cost 1   
 2 4 1   
 2 5 2   
 1 3 1   
 3 6 2   
  
 Path from node 4 to node 6 is 4 -> 2 -> 1 -> 3 -> 6   
**DIST 4 6** : answer is 5 (1 + 1 + 1 + 2 = 5)   
**KTH 4 6 4** : answer is 3 (the 4-th node on the path from node 4 to node 6 is 3)

## 样例 #1

### 输入

```
1

6
1 2 1
2 4 1
2 5 2
1 3 1
3 6 2
DIST 4 6
KTH 4 6 4
DONE```

### 输出

```
5
3```

# 题解

## 作者：lmz1 (赞：12)

## ~~LCA高级水题~~
这才发现用倍增法做简直是非常~~水题~~。。。因为求路径的第k个点可以转化成求第k个父节点，然而倍增法的原理就是根据的父节点，于是这题就很容易解决了。。 
求距离很好求。关键是求路径第k个点，显然这个点要么是u的第k个父节点，要么是v的第k个父节点，于是乎，先求一次LCA，判断是u还是v的，然后用倍增法找到那个点即可。 
代码如下：~~~~
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const int N=10010;
int head[N<<1];
int to[N<<1];
int nxt[N<<1];
int cnt=0;
int d[N];
int f[N][31];
int road[N<<1];
int dis[N];
void add(int x,int y,int z)
{
    to[cnt]=y;
    nxt[cnt]=head[x];
    road[cnt]=z;
    head[x]=cnt++;
}
void dfs(int x,int fx)
{
    d[x]=d[fx]+1;
    f[x][0]=fx;
    for(int i=1;(1<<i)<=d[x];i++)
    {
    	if(f[x][i-1]!=-1)
    	{
    		f[x][i]=f[f[x][i-1]][i-1];
        }
    }
    for(int i=head[x];i!=-1;i=nxt[i])
    {
        int aa=to[i];
        if(aa!=fx)
        {
        	dis[aa]=dis[x]+road[i];
            dfs(aa,x);
        }
    }
}
int lca(int a,int b)
{
    if(d[a]<d[b])
    {
        swap(a,b);
    }
    for(int i=30;i>=0;i--)
    {
        if(d[b]<=d[a]-(1<<i))
        {
            a=f[a][i];
        }
    }
    if(a==b)
    {
        return a;
    }
    for(int i=30;i>=0;i--)
    {
        if(f[a][i]==f[b][i])
        {
            continue;
        }
        else
        {
            a=f[a][i];
            b=f[b][i];
        }
    }
    return f[a][0];
}
int querylen(int a,int b,int k)
{
    int tt=lca(a,b);
    int bian=0;
    if((d[a]-d[tt]+1)>=k)
    {
        int ans=d[a]-k+1;
        for(int i=30;i>=0;i--)
        {
            if((1<<i)<=d[a]-ans)
            {
                a=f[a][i];
            }
        }
        return a;
    }
    else
    {
        int ans=d[tt]*2+k-d[a]-1;
        for(int i=30;i>=0;i--)
        {
            if(d[b]-(1<<i)>=ans)
            {
                b=f[b][i];
            }
        }
        return b;
    }
    
}
int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        memset(head,-1,sizeof(head));
        memset(to,0,sizeof(to));
        memset(nxt,0,sizeof(nxt));
        memset(d,0,sizeof(d));
        memset(f,-1,sizeof(f));
        memset(road,0,sizeof(road));
        memset(dis,0,sizeof(dis));
        cnt=0;
        int n,s=1;
        cin>>n;
        for(int i=1;i<n;i++)
        {
            int x,y,z;
            scanf("%d%d%d",&x,&y,&z);
            add(x,y,z);
            add(y,x,z);
        }
        dfs(s,0);
        string flag;
       	while(cin>>flag)
       	{
           	if(flag[1]=='I')
           	{
            	int a,b;
                scanf("%d%d",&a,&b);
                int tt=lca(a,b);
                printf("%d\n",dis[a]+dis[b]-2*dis[tt]);
            }
           	if(flag[1]=='T')
            {
               	int a,b,c;
               	scanf("%d%d%d",&a,&b,&c);
               	printf("%d\n",querylen(a,b,c));
            }
            if(flag[1]=='O')
                break;
        }
    }
    return 0;
}
```


---

## 作者：Eismcs (赞：10)

写在前面：由于太**弱**，希望各位大佬能来博客灌水，提出建议。


明显的$LCA$问题，用了树剖。思路是所有会~~一点~~树剖的人都能看懂的。

先不谈树剖的构造，先看问题如何解决，然后再用原来树剖思路构造并延伸。

1. 首先对于第一问，明显的$LCA$，求边权和，由于不需要修改，所以用前缀和即可（线段树的话时间有点紧，代码也太长了）。这样我们就需要在构造时维护一个前缀和，维护链上的边权和。
1. 对于第二问，还是$LCA$，但是有些棘手。可以分成两种情况，一种是从x到最近公共祖先，一种是y到最近公共祖先,再用数组记录结点编号，这就有不少细节问题了。

好了，问题都整理了一下，但貌似仍然不好写，所以要了解树剖的关键性质。

1. 假设x和y的最近公共祖先为u，那么x到u（包括u）一共有
$(deep[x]-deep[u]+1)$个点（deep为结点深度）。同理y到u也有$(deep[x]-deep[u]+1)$个点（也包括u）,这样对于第二问的许多判断起了重大作用
1. 我们每次在$dfs2$中先遍历此节点的重儿子，就是让每条链上的相邻结点的$dfs$序也是相邻的（依次递增）这样第一问的前缀和，第二问的结点编号就可以以结点$dfs$序记录。

所以接下来如何构造树剖就知道了，只是在原来基础上多了前缀和和编号数组（因为代码能力有限，又用了一个数组记录重儿子与此点相连边的序号）

代码如下，仅供参考~~因为太烂了~~
```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<queue>
#include<map> 
using namespace std;
#define re register int
inline int read(){
    int x=0,ff=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')ff=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*ff;
}
struct tree{
    int to,next,kk;
}a[20005];
int h[20005],tot;
int n,fa[20005],ss[20005],o[20005],d[20005],op[20005],s[20005];
int cnt,id[20005],as[20005],sl[20005],oo[20005];
void add(int x,int y,int z){
    a[++tot].next=h[x];a[tot].to=y;a[tot].kk=z;h[x]=tot;
}
void dfs1(int i,int la,int dp){
    fa[i]=la;d[i]=dp;s[i]=1;
    int x=-1;
    for(int j=h[i];j;j=a[j].next){
        if(a[j].to==la)continue;
        dfs1(a[j].to,i,dp+1);
        s[i]+=s[a[j].to];
        if(s[a[j].to]>x){
            x=s[a[j].to];o[i]=a[j].to;oo[i]=j;
        }
    }
}
void dfs2(int i,int tp){
    op[i]=tp;id[i]=++cnt;as[cnt]=i;
    if(!o[i])return;
    dfs2(o[i],tp);
    ss[id[i]]=ss[id[o[i]]]+a[oo[i]].kk;
    for(int j=h[i];j;j=a[j].next){
        if(a[j].to==fa[i])continue;
        sl[cnt+1]=a[j].kk;
        if(a[j].to==o[i])continue;
        dfs2(a[j].to,a[j].to);
    }
}
//上面的构造都基本是模板，略微的更改都已提到了
void lca(int x,int y){
    int ans=0;
    while(op[x]!=op[y]){
        if(d[op[x]]<d[op[y]])swap(x,y);
        ans+=sl[id[op[x]]]+ss[id[op[x]]]-ss[id[x]];x=fa[op[x]];//性质2+经典前缀和
    }
    if(d[x]>d[y])swap(x,y);
    ans+=ss[id[x]]-ss[id[y]];
    printf("%d\n",ans);
}
void find(int x,int y,int z){
    int yy=y,xx=x;
    while(op[xx]!=op[yy]){
        if(d[op[xx]]<d[op[yy]])swap(xx,yy);
        xx=fa[op[xx]];
    }
    if(d[xx]>d[yy])swap(xx,yy);
    if(d[x]-d[xx]+1>=z){
        while(1){
            if(z<=d[x]-d[op[x]]+1)break;
            z-=d[x]-d[op[x]]+1;x=fa[op[x]];
            //上面两个语句都根据性质1
        }
        printf("%d\n",as[id[x]-z+1]);//性质2
    }
    else {
        z-=d[x]-d[xx];//性质1
        int u=d[y]-d[xx]+1;//性质1
        while(1){
            if(op[y]==op[xx])break;
            if(z>u-(d[y]-d[op[y]]+1))break;
            u-=(d[y]-d[op[y]]+1);
            //上面两句也是性质1
            y=fa[op[y]];
        }
        if(op[y]==op[xx]){
            printf("%d\n",as[z-(u-(d[y]-d[xx]+1))+id[xx]-1]);//性质2
            return;
        }
        printf("%d\n",as[z-(u-(d[y]-d[op[y]]+1))+id[op[y]]-1]);//性质2
    }
}
//find过程中有一些小细节，自己画图就知道了。
signed main(){
    int t=read();
    while(t--){
    n=read();int x,y,z;
    memset(h,0,sizeof(h));tot=0;
    memset(ss,0,sizeof(ss));
    memset(s,0,sizeof(s)); 
    memset(sl,0,sizeof(sl));
    cnt=0;
    memset(fa,0,sizeof(fa));
    memset(o,0,sizeof(o));
    for(int i=1;i<n;i++){
        x=read();y=read();z=read();
        add(x,y,z);add(y,x,z);
    }
    cnt=0;dfs1(1,0,1);dfs2(1,1);
    char ch[105];
    scanf("%s",ch);
    while(ch[1]!='O'){
        if(ch[1]=='I'){
            x=read();y=read();
            lca(x,y);
        }
        else {
            x=read();y=read();z=read();
            find(x,y,z);
        }
        scanf("%s",ch);
    }}
    return 0;
}

```
此题最后的坑点是多组数据，别忘了清空记录重儿子的数组


---

## 作者：Ebola (赞：8)

### 广告：[我的博客](http://ebola.blogwo.com/)

###  扯淡

这道题整整调了我2天！

其实是一道非常水的倍增题，但我硬是要写成LCT，然后就毒瘤了。。。

最后发现原因是kth的时候没有pushdown。。。

### 题解

其实想了一下倍增，发现KTH操作有点麻烦，要先求出LCA，然后以LCA为分界点，把路径分两段去解决问题。主要是倍增这种东西没有模板，每个操作还要我自己去想就很烦。mdzz为什么要倍增？题解里面人人都写倍增，我肯定要来点刺激的

LCT嘛，暴力一点

但我是一个比较懒的人，如果保留边权的话就要加一个标记来求LCA，我显然不喜欢这样。所以我决定把边权转化为点权
所以对于每条边，我们建一个点，点权为边权，向两端的点分别连边，而原来的点则点权设为0

然后DIST询问就只要把x到y的链给提取出来，询问链上点权和

对于KTH询问，我们要再写一个平衡树的kth操作，把x到y的链提取到一颗splay上后，对这颗splay进行kth询问，注意此时不是kth(k)，而是kth(2k-1)，因为每两个原来的点中间有一个我们建的边结点

这样我们的splay就要维护两个信息：点权和、实子树大小，这些在maintain里面写一下就行了

有一点要郑重提醒：对splay进行kth操作时，一定要记得对访问到的结点进行pushdown操作！因为我们有翻转的lazy标记，如果不pushdown就会WA掉，虽然样例可以过

嗯，就这样，时间复杂度O(n log n)

细节参考代码

```cpp
#include<bits/stdc++.h>
#define ls nd[x].son[0]
#define rs nd[x].son[1]
using namespace std;

struct Node
{
    int son[2],fa;
    int sz,r;
} nd[300010];
struct Edge{int to,capa,next;} e[300010];
int h[300010],sum;
char opt[10];
int dis[30010],mul[30010][20],dep[30010];

inline void add_edge(int u,int v,int w)
{
    sum++;
    e[sum].to=v;
    e[sum].next=h[u];
    e[sum].capa=w;
    h[u]=sum;
}

void dfs(int u,int fa)
{
    for(int tmp=h[u];tmp;tmp=e[tmp].next)
    {
        if(e[tmp].to==fa) continue;
        nd[e[tmp].to].fa=u;
        nd[e[tmp].to].sz=1;
        dis[e[tmp].to]=dis[u]+e[tmp].capa;
        mul[e[tmp].to][0]=u;
        dep[e[tmp].to]=dep[u]+1;
        dfs(e[tmp].to,u);
    }
}

inline bool notroot(int x){return nd[nd[x].fa].son[0]==x||nd[nd[x].fa].son[1]==x;}
inline void pushr(int x){swap(ls,rs);nd[x].r^=1;}
inline void maintain(int x){nd[x].sz=nd[ls].sz+nd[rs].sz+1;}
inline void pushdown(int x)
{
    if(nd[x].r)
    {
        if(ls) pushr(ls);
        if(rs) pushr(rs);
        nd[x].r=0;
    }
}

inline void rotate(int x)
{
    int y=nd[x].fa,z=nd[y].fa;
    int k=(nd[y].son[1]==x),w=nd[x].son[k^1];
    if(notroot(y)) nd[z].son[nd[z].son[1]==y]=x;
    nd[x].son[k^1]=y;
    nd[y].son[k]=w;
    if(w) nd[w].fa=y;
    nd[y].fa=x;
    nd[x].fa=z;
    maintain(y);
    maintain(x);
}

void splay(int x)
{
    int y=x,z;
    stack<int> s;
    s.push(y);
    while(notroot(y)) s.push(nd[y].fa),y=nd[y].fa;
    while(!s.empty()) pushdown(s.top()),s.pop();
    while(notroot(x))
    {
        y=nd[x].fa;
        z=nd[y].fa;
        if(notroot(y)) rotate((nd[y].son[0]==x)^(nd[z].son[0]==y)?x:y);
        rotate(x);
    }
    maintain(x);
}

int kth(int x,int k)
{
	pushdown(x);
    int sz=1;
    if(ls) sz+=nd[ls].sz;
    if(k==sz) return x;
    else if(k<sz) return kth(ls,k);
    else return kth(rs,k-sz);
}

void access(int x)
{
    int y=0;
    while(x)
    {
        splay(x);
        rs=y;
        maintain(x);
        y=x;
        x=nd[x].fa;
    }
}

inline void makeroot(int x){access(x);splay(x);pushr(x);}
inline void split(int x,int y){makeroot(x);access(y);splay(y);}

void init(int n)
{
	for(int j=1;j<=14;j++)
		for(int i=1;i<=n;i++)
			mul[i][j]=mul[mul[i][j-1]][j-1];
}

int LCA(int p1,int p2)
{
	if(dep[p1]<dep[p2]) swap(p1,p2);
	for(int j=14;j>=0;j--)
		if(dep[mul[p1][j]]>=dep[p2]) p1=mul[p1][j];
	for(int j=14;j>=0;j--)
		if(mul[p1][j]!=mul[p2][j]) p1=mul[p1][j],p2=mul[p2][j];
	if(p1!=p2) p1=mul[p1][0];
	return p1;
}

void DFS(int x)
{
	if(ls) DFS(ls);
	printf("%d ",x);
	if(rs) DFS(rs);
}

int main()
{
    int t,n,a,b,c;
    for(cin>>t;t;t--)
    {
        sum=0;
        memset(h,0,sizeof(h));
        memset(nd,0,sizeof(nd));
        memset(dis,0,sizeof(dis));
        memset(mul,0,sizeof(mul));
        memset(dep,0,sizeof(dep));
        scanf("%d",&n);
        for(int i=1;i<n;i++)
        {
            scanf("%d%d%d",&a,&b,&c);
            add_edge(a,b,c);
            add_edge(b,a,c);
        }
        dfs(1,0);
        init(n);
        nd[1].sz=1;
        while(true)
        {
            scanf("%s",opt);
            if(opt[1]=='O') break;
            if(opt[0]=='D')
            {
                scanf("%d%d",&a,&b);
                int lca=LCA(a,b);
                printf("%d\n",dis[a]+dis[b]-2*dis[lca]);
            }
            else
            {
                scanf("%d%d%d",&a,&b,&c);
                split(a,b);
                printf("%d\n",kth(b,c));
            }
        }
    }
    return 0;
}

```

#### 此外，为了帮助一些想对拍又不会生成数据的同学，我把我此题的数据生成器送给大家

```cpp
#include<bits/stdc++.h>
using namespace std;

int fa[100000];
struct Edge{int to,next;} e[200010];
int h[100010],sum=0;
int dis[100010];

void add_edge(int u,int v)
{
	sum++;
	e[sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

void dfs(int u,int la)
{
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		if(e[tmp].to==la) continue;
		dis[e[tmp].to]=dis[u]+1;
		dfs(e[tmp].to,u);
	}
}

bool find(int x,int m)
{
	if(fa[x]==m) return false;
	if(fa[x]==0) return true;
	return find(fa[x],m);
}

int main()
{
	freopen("testdata.txt","w",stdout);
	srand(time(0));
	puts("1\n10000");
	for(int i=1;i<10000;i++)
	{
		int t=rand()%10000+1;
		while(!find(t,i)||t==i) t=rand()%10000+1;
		fa[i]=t;
		add_edge(i,t);
		add_edge(t,i);
		printf("%d %d %d\n",i,fa[i],rand()%100000);
	}
	for(int i=1;i<=10000;i++)
	{
		int opt=rand()%2,a=rand()%10000+1,b=rand()%10000+1;
		while(a==b) a=rand()%10000+1,b=rand()%10000+1;
		if(opt) printf("DIST %d %d\n",a,b);
		else
		{
			dis[a]=1;
			dfs(a,0);
			printf("KTH %d %d %d\n",a,b,rand()%dis[b]+1);
		}
	}
	puts("DONE");
	return 0;
}

```

---

## 作者：fa_555 (赞：6)

under 题解 [SP913](https://www.luogu.org/problem/SP913)

---

找树剖题的时候发现这题，发现用倍增很~~水~~简单，于是写了一发，发现跟现有题解还不大一样，于是写篇题解造 (bao) 福 (fu) 社会。

---

### 前置芝士

树上倍增，LCA

~~当然你也可以顺手树剖维护个 LCA 然后倍增统计答案~~

---

### 思路

*以下设 `f` 为 `u` 和 `v` 的最近公共祖先*

- 以结点 `1` 为根，套路性 dfs，并求出倍增祖先数组 `fa[][]` & 结点深度 `dep[]` & 根到每个结点的边权和 `wn[]`
  - $O(n \log n)$

- 对于每个 `DIST u v` 操作，答案显然为 `wn[u] + wn[v] - 2 * wn[f]`
  - 单次 $O( \log n)$

- 对于每个 `KTH u v k` 操作，分情况讨论。
  - 若 `dep[u] - dep[f] + 1 < k`，答案即为 `u` 的 `k` 级祖先；
  - 若 `dep[u] - dep[f] + 1 > k`，答案为 `v` 的 祖先，且为 `dep[u] + dep[v] - 2 * dep[k] + 2 - k` 级祖先。考虑 `u` 到 `v` 的路径上共有 `dep[u] + dep[v] - 2 * dep[f] + 1` 个结点，得到这个式子；
  - 若 `dep[u] - dep[f] + 1 == k`， 答案为 `f`。可特判，也可并入前两种情况处理。
  - 单次 $ O( \log n) $

总复杂度 $ O((n + q) \log n) $

---

### 变量解释与代码

~~`cin:` 重载的快读~~

`MX:` $ \lfloor \log_2 N \rfloor $

`queryt(u, v, k):` 返回 `KTH u v k` 操作的答案

*其余变量意义同 **思路** 部分*

代码 (c++11) :

``` cpp
#include<algorithm>
#include<cstdio>
#include<cstring>

struct IO {
	template<typename T>
	inline IO operator>>(T &n) {
		n=0; char c=getchar();
		while(c<'0'||c>'9') c=getchar();
		while(c>='0'&&c<='9') n=(n<<3)+(n<<1)+(c^48),c=getchar();
		return *this; // n >= 0
	}
} cin;
// 不要 iostream + using namespace std！会 CE 的！

constexpr int MX = 14;

char op[5];
int T, N, u, v, w, tot, head[10003], dep[10003], wn[10003], fa[10003][15];

struct Edge {
	int nxt, to, w;
} e[20003];

inline void addEdge(int u, int v, int w) {
	e[++tot] = {head[u], v, w};
	head[u] = tot;
}

void dfs(int u, int f) {
	// 预处理
	dep[u] = dep[f] + 1;
	fa[u][0] = f;
	for (int i = 1; (1 << i) <= dep[u]; ++i)
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	for (int i = head[u], v; i; i = e[i].nxt) {
		if ((v = e[i].to) == f) continue;
		wn[v] = wn[u] + e[i].w;
		dfs(v, u);
	}
}

int Lca(int u, int v) {
	// 倍增求 LCA
	if (dep[u] < dep[v]) std::swap(u, v);
	for (int i = MX; i >= 0; --i)
		if (dep[v] <= dep[u] - (1 << i))
			u = fa[u][i];
	if (u == v) return u;
	for (int i = MX; i >= 0; --i)
		if (fa[u][i] != fa[v][i])
			u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}

int queryt(int u, int v, int k) {
	// 分类讨论
	int f = Lca(u, v);
	if (dep[u] - dep[f] + 1 <= k) {
		// 若答案为 $v 的祖先，则转换为求 u 的祖先的情况，简化代码
		k = dep[u] + dep[v] - (dep[f] << 1) + 2 - k;
		u = v;
	}
	for (int i = MX; i >= 0; --i)
		// 倍增维护答案
		if (k >= (1 << i) + 1) {
			u = fa[u][i];
			k -= (1 << i);
		}
	return u;
}

void init() {
	// 多测不清空，爆零两行泪
	tot = wn[1] = 0;
	memset(fa, 0, sizeof fa);
	memset(head, 0, sizeof head);
	cin >> N;
	for (int i = 1; i < N; ++i) {
		cin >> u >> v >> w;
		addEdge(u, v, w);
		addEdge(v, u, w);
	}
}

int main() {
	for (cin >> T; T; --T) {
		init();
		dfs(1, 0);
		while(1) {
			scanf("%s", op);
			if (op[1] == 'O') break;
			if (op[1] == 'I') {
				cin >> u >> v;
				printf("%d\n", wn[u] + wn[v] - (wn[Lca(u, v)] << 1));
			} else {
				cin >> u >> v >> w;
				printf("%d\n", queryt(u, v, w));
			}
		}
	}
	return 0;
}


```

如果有错误或不懂的地方，请在私信或评论中告知我，**谢谢你们 qwq**


---

## 作者：liujiaxi123456 (赞：4)

## 关键词：重剖，洛谷 rank 1，树上差分，代码详细注释，警示后人
### 1. DIST:
查询 $u$ 到 $v$ 的边权和。

显然，树上差分即可：

$ans = dis_u+dis_v-2\cdot dis_{lca}$

### 2. KTH:
发现若 $u$ 和 $ans_{node}$ 在同一条链上，由于 $dfn$ 连续，可以直接由 $dfn_{id_u-k+1}$ 得到。

具体的，从 $u$ 往上跳，若 $ans_{node}$ 在同一条链上，$ans_{node} = dfn_{id_u-k+1}$。

若不在一条链上，$k' = k - (dep_u-dep_{top_u}+1)$，$u = fa_{top_u}$，直到跳到 $lca$。

若 $ans_{node}$ 在 $lca$ 到 $v$ 的链上，从 $v$ 反着跳即可。

### 警示后人：
多测清空时，记得清空 $dfn_{num}$ 的 $num$。
### code:
[洛谷 rank 1 提交记录](https://www.luogu.com.cn/record/150843957)

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn = 10005;

namespace EDGE {
	int sz, head[Maxn];
	struct Edge { int next, to, val; } edge[Maxn*2];
	inline void Add_edge(int u, int v, int w) {
		edge[++sz] = {head[u], v, w};
		head[u] = sz;
	}
} using namespace EDGE;

namespace Josh_zmf {
	
	int N, fa[Maxn], dep[Maxn], size[Maxn], dis[Maxn], dfn[Maxn], id[Maxn], son[Maxn], top[Maxn], num;

	inline void dfs1(int u, int faa) {
		fa[u] = faa, dep[u] = dep[faa]+1, size[u] = 1, son[u] = 0;
		int tmp = -1;
		for(int i=head[u], v, w; i; i=edge[i].next) {
			v = edge[i].to, w = edge[i].val;
			if(v^faa) {
				dis[v] = dis[u]+w, dfs1(v, u), size[u] += size[v];
				(size[v]>tmp ?tmp=size[v], son[u]=v :false);
			}
		}
	}

	inline void dfs2(int u, int faa) {
		top[u] = faa, dfn[id[u] = ++num] = u;
		(son[u] ?dfs2(son[u], faa) :void());
		for(int i=head[u], v; i; i=edge[i].next) {
			v = edge[i].to;
			if(v^fa[u] && v^son[u])	dfs2(v, v);
		}
	}

	inline int LCA(int u, int v) {
		while(top[u] ^ top[v])	(dep[top[u]]>dep[top[v]] ?u=fa[top[u]] :v=fa[top[v]]);
		return (dep[u]<dep[v] ?u :v);
	}

	int main() {
		int T; cin>> T;
		while(T--) {
			cin>> N;
			for(int i=1, u, v, w; i<N; i++)	cin>> u>> v>> w, Add_edge(u, v, w), Add_edge(v, u, w);
			dfs1(1, 0), dfs2(1, 1);
			string opt; int u, v, lca, k;
			while(1) {
				cin>> opt;
				if(opt == "DIST") {
					// 查询 u -> v 的边权和
					// 转化为 dis[u]+dis[v]-2*dis[lca]
					cin>> u>> v;
					lca = LCA(u, v);
					cout<< dis[u] - dis[lca] + dis[v] - dis[lca]<< '\n';
				} else if(opt == "KTH") {
					// 查询 u -> v 的第 k 个节点
					// 发现若 u 和 ans_node 在同一条链上，由于 dfn 连续，可以直接由 dfn[id[u]-k+1] 得到
					// 具体的，从 u 往上跳，若 ans_node 在同一条链上，ans_node = dfn[id[u]-k+1]
					// 若不在一条链上，k -= dep[u]-dep[top[u]]+1, u = fa[top[u]]，直到跳到 lca
					// 若 ans_node 在 lca->v 的链上，从 v 反着跳即可
					cin>> u>> v>> k;
					lca = LCA(u, v);
					if(k > dep[u]-dep[lca]+1) {
						k = dep[u]-dep[lca]+1 + dep[v]-dep[lca]+1 -k;
						swap(u, v);
					}
					while(k > dep[u]-dep[top[u]]+1) {
						k -= dep[u]-dep[top[u]]+1;
						u = fa[top[u]];
					}
					cout<< dfn[id[u]-k+1]<< '\n';
				} else {
					break; 
				}
			}
			memset(head+1, 0, N*4), sz = 0, num = 0;
		}
		return 0;
	}

}

signed main() {
	Josh_zmf::main();
	return 0;
}
```

### 结语：
点个赞再走吧 : )

---

## 作者：ADay (赞：4)

[更好的阅读体验](https://www.cnblogs.com/aday526/p/solution-sp913.html)
## 树剖解法

题解区写树剖的只有两篇，而且这两篇求 $\texttt{DIST}$ 都比较麻烦。

### 前置芝士

用重链剖分AC [LCA模板](https://www.luogu.com.cn/problem/P3379) 和 [树上k级祖先模板](https://www.luogu.com.cn/problem/P5903)。

### Solution

首先对整棵树进行树剖，即两次 $\texttt{dfs}$，但是在此过程中，需要多记录一个变量，`dist[u]`，即u节点到根节点的距离，用其父亲的 `dist` 加上边权即可，以便求 $\texttt{DIST}$。

复杂度 $\mathcal O(n)$

### DFS Code

```cpp
void dfs1(int u,int f){
    siz[u]=1;fa[u]=f;//记录子树大小、父亲
    dep[u]=dep[f]+1;//记录深度
    int maxs=-1;
    for(auto &x:e[u]){//C++11写法
        int v=x.to,w=x.w;
        if(v==f)continue;
        dist[v]=dist[u]+w;//一定不能在dfs子节点后求dist，因为这样儿子没求先求了孙子
        dfs1(v,u);
        siz[u]+=siz[v];
        if(siz[v]>maxs){
            son[u]=v;//记录重儿子
            maxs=siz[v];
        }
    }
}
void dfs2(int u,int f){
    id[u]=++tot;//记录新编号
    dfn[tot]=u;//编号映射
    top[u]=f;//记录重链的顶端
    if(!son[u])return;
    dfs2(son[u],f);
    for(auto &x:e[u]){
        int v=x.to;
        if(id[v])continue;
        dfs2(v,v);
    }
}
```

接下来是求 $\texttt{DIST}$ 了！

注意到一个性质：`real_dis(u,v)=dist[u]+dist[v]-2*dist[lca(u,v)]`

（real_dis=真实距离，待会还有相对距离）

可以用一张图来理解：

![](https://cdn.luogu.com.cn/upload/image_hosting/jm83l7ke.png)

~~没错这就是lxl的图~~

然后直接运算就完了。。。

### DIST Code

```cpp
il int lca(int u,int v){
    for(;top[u]!=top[v]&&u!=rt;u=fa[top[u]])
        if(dep[top[u]]<dep[top[v]])swap(u,v);
    return dep[u]<dep[v]?u:v;
}//见P3379
il int real_dis(int u,int v){return dist[u]+dist[v]-2*dist[lca(u,v)];}
```

最后是 $\mathcal O(\log n)$ 求 $\texttt{KTH}$

我们要用到相对距离，即假设边权为 $1$ 时的真实距离，用于求两点间节点个数。和真实距离同理，`rela_dis(u,v)=dep[u]+dep[v]-2*dep[lca(u,v)]`，此时只要判断第k个节点在LCA的左边还是右边，就能把问题转化成求u的k级祖先或者v的rela-k级祖先。

### KTH Code

```cpp
il int kth(int u,int k){
    for(;id[u]-id[top[u]]<k;u=fa[top[u]])
        k-=dep[u]-dep[top[u]]+1;
    return dfn[id[u]-k];
}//见P5903
...
scanf("%d%d%d",&x,&y,&z);z--;
int dis=rela_dis(x,y),LCA=lca(x,y);
if(rela_dis(x,LCA)>=z)printf("%d\n",kth(x,z));
else printf("%d\n",kth(y,dis-z));
```


---

## 作者：D10s (赞：4)

似乎没有树剖的题解（当然这题拿树剖写有点奇怪，没有修改，线段树直接退化成前缀和了……）。

在求KTH时先跑出lca，根据深度关系确定从哪一边往上跳。由于剖分完毕后轻重链都是一段连续的区间，所以重复上跳至答案所在的链就可以用深度直接算出来了。

```cpp
#include<cstdio>
#include<cstring>
#define N (10000+5)
struct edge{int to,nxt,val;}e[2*N];
int tot,fir[N],pa[N],dep[N],size[N],son[N],tp[N],id[N],rec[N],etv[N],s[N];
void swap(int &x,int &y) {int t=x;x=y;y=t;}
void addedge(int u,int v,int w)
{
    e[++tot].to=v;e[tot].val=w;
    e[tot].nxt=fir[u];fir[u]=tot;
}
void dfs1(int x,int pre)
{
    pa[x]=pre;dep[x]=dep[pre]+1;
    size[x]=1;son[x]=0;int mx=-1;
    for(int i=fir[x];i;i=e[i].nxt)
    if(e[i].to!=pre)
    {
        int v=e[i].to;dfs1(v,x);
        etv[v]=e[i].val;size[x]+=size[v];
        if(size[v]>mx) son[x]=v,mx=size[v];
    }
}
void dfs2(int x,int pre)
{
    tp[x]=pre;s[++tot]=etv[x];
    id[x]=tot;rec[tot]=x;
    if(!son[x]) return;dfs2(son[x],pre);
    for(int i=fir[x];i;i=e[i].nxt)
    if(e[i].to!=son[x]&&e[i].to!=pa[x]) dfs2(e[i].to,e[i].to);
}
int qpath(int u,int v)
{
    int ret=0;
    while(tp[u]!=tp[v])
    {
        if(dep[tp[u]]<dep[tp[v]]) swap(u,v);
        ret+=s[id[u]]-s[id[tp[u]]-1];
        u=pa[tp[u]];
    }
    if(dep[u]>dep[v]) swap(u,v);
    ret+=s[id[v]]-s[id[u]];
    return ret;
}
int lca(int u,int v)
{
    while(tp[u]!=tp[v])
    if(dep[tp[u]]>dep[tp[v]]) u=pa[tp[u]];else v=pa[tp[v]];
    return dep[u]<dep[v]?u:v;
}
int kth(int u,int k)
{
    while(dep[u]-k+1<dep[tp[u]]) 
        k-=dep[u]-dep[tp[u]]+1,u=pa[tp[u]];
    //注意u跳到了tp[u]的父节点，不要忘了+1
    return rec[id[u]-k+1];
}
int main()
{
    int _;scanf("%d",&_);
    while(_--)
    {
        tot=0;memset(fir,0,sizeof(fir));
        int n;scanf("%d",&n);
        for(int i=1;i<n;i++)
        {
            int x,y,z;scanf("%d%d%d",&x,&y,&z);
            addedge(x,y,z);addedge(y,x,z);
        }
        tot=0;dfs1(1,0);dfs2(1,1);
        for(int i=1;i<=tot;i++) s[i]+=s[i-1];
        while(1)
        {
            char s[5];scanf("%s",s);
            if(s[1]=='O') break;
            if(s[0]=='D')
            {
                int x,y;scanf("%d%d",&x,&y);
                printf("%d\n",qpath(x,y));
            }
            else
            {
                int x,y,k;scanf("%d%d%d",&x,&y,&k);
                int ans,z=lca(x,y);
                if(dep[x]-dep[z]+1>=k) ans=kth(x,k);
                else ans=kth(y,dep[x]+dep[y]-2*dep[z]-k+2);
                //len(x,y)=dep[x]-dep[z]+dep[y]-dep[z]+1
                printf("%d\n",ans);
            }
        }
    }
    return 0;
}
```

---

## 作者：Acee (赞：2)

这题很明显是求 lca 与树上 k 级祖先问题。

考虑长链剖分与离线 Tarjan 做到单次 $O(1)$。

求 KTH 直接看是 x 跳还是 y 跳就行了。

#### 一定要注意深度是从零开始还是一开始。

这里因为某些原因，使用长链剖分求 lca。

代码:

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include<assert.h>
#include <cstring>
#include <climits>
#include <cstdlib>
// #include <bitset>
// #include <vector>
#include <queue>
// #include <stack>
// #include <set>
// #include <map>
// #include <unordered_map>
using namespace std;
using ll = long long;
// #define int long long
namespace Main {
	const int N = 10000 + 5;
	int Test;
	int n;
	struct edge {
		int nxt, to, val;
	} e[N << 1];
	int h[N], num;
	ll dis[N];
	void addedge(int x, int y, int z) {
		e[++num].nxt = h[x];
		e[num].to = y;
		e[num].val = z;
		h[x] = num;
	}
	int lg[N], len[N], dep[N];
	int son[N], top[N];
	int fa[20][N];
	vector<int> c[N], u[N];
	void dfs1(int x, int f) {
		fa[0][x] = f;
		len[x] = dep[x] = dep[f] + 1;
		for (int i = 1; i <= lg[n]; ++i) fa[i][x] = fa[i - 1][fa[i - 1][x]];
		for (int i = h[x]; i; i = e[i].nxt) {
			int y = e[i].to;
			if (y == f) continue;
			dis[y] = dis[x] + e[i].val;
			dfs1(y, x);
			if (len[y] > len[x]) len[x] = len[y], son[x] = y;
		}
	}
	void dfs2(int x, int f) {
		top[x] = f;
		if (x == f) {
			for (int i = 0, p = x; i <= len[x] - dep[x]; ++i) {
				u[x].push_back(p), p = fa[0][p];
			}
			for (int i = 0, p = x; i <= len[x] - dep[x]; ++i) {
				c[x].push_back(p), p = son[p];
			}
		}
		if (son[x]) dfs2(son[x], f);
		for (int i = h[x]; i; i = e[i].nxt) {
			int y = e[i].to;
			if (y == fa[0][x] || y == son[x]) continue;
			dfs2(y, y);
		}
	}
	int ask(int x, int k) {
		if (!k) return x;
		x = fa[lg[k]][x];
		k -= (1 << lg[k]);
		k -= dep[x] - dep[top[x]];
		x = top[x];
		return k >= 0 ? u[x][k] : c[x][-k];
	}
	int lca(int a, int b) {
		if (dep[a] < dep[b]) swap(a, b);
		a = ask(a, dep[a] - dep[b]);
		int l = 0, r = min(dep[a], dep[b]) - 1, ans = 0;
		while (l <= r) {
			int mid = (l + r) >> 1;
			int xx = ask(a, mid), yy = ask(b, mid);
			if (xx == yy) r = mid - 1, ans = mid;
			else l = mid + 1;
		}
		return ask(a, ans);
	}
	int main() {
		ios::sync_with_stdio(false);
		cin.tie(0), cout.tie(0);
		cin >> Test;
		while (Test--) {
			cin >> n;
			memset(h, 0, sizeof(h));
			memset(dis, 0, sizeof(dis));
			memset(dep, 0, sizeof(dep));
			memset(len, 0, sizeof(len));
			num = 0;
			for (int i = 1; i <= n; ++i) {
				c[i].clear(), c[i].shrink_to_fit();
				u[i].clear(), u[i].shrink_to_fit();
			}
			for (int i = 2; i <= n; ++i) lg[i] = lg[i >> 1] + 1;
			for (int i = 1, x, y, z; i < n; ++i) {
				cin >> x >> y >> z;
				addedge(x, y, z);
				addedge(y, x, z);
			}
			dfs1(1, 0);
			dfs2(1, 1);
			string s;
			int x, y, k;
			// cout << ask(5, 2) << '\n';
			while (true) {
				cin >> s;
				if (s == "DONE") break;
				if (s[0] == 'D') {
					cin >> x >> y;
					int l = lca(x, y);
					cout << dis[x] + dis[y] - 2 * dis[l] << '\n';
				}
				else {
					cin >> x >> y >> k;
					int l = lca(x, y);
					int Len = dep[x] - dep[l];
					if (k <= Len) {
						cout << ask(x, k) << '\n';
					}
					else {
						// cout<<"QEQW\n";
						int ly = dep[y] - dep[l];
						cout << ask(y, ly - (k - Len - 1)) << '\n';
					}
				}
			}
		}
		return 0;
	}
}
signed main() {
	Main :: main();
	return 0;
}

```

---

## 作者：happybob (赞：2)

简单倍增。

前置：[树上倍增 k 级祖先](https://www.luogu.com.cn/problem/P5903)。

注意题目无修改，所以对于询问距离，直接预处理出每个点到根的距离，然后相加减去两倍 LCA 即可，非常套路。

对于第二位，先求出 $u,v$ 的 LCA，先看 $u \rightarrow lca$ 这条路径上经过的点数是否 $\geq k$，若 $\geq k$，求 $u$ 的 $k$ 级祖先即可。若点数 $<k$，从 $lca$ 开始往下遍历，可以转化为 $v$ 的多级祖先，倍增处理即可。

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

const int N = 1e4 + 5;

int fa[N][31], sum1[N], sum2[N];
vector<pair<int, int> > G[N];
int n, t;

class TreeCut
{
public:
	int fa[N], sz[N], son[N], top[N], dep[N];
	void Init(int n)
	{
		for (int i = 0; i <= n; i++)
		{
			fa[i] = sz[i] = son[i] = top[i] = dep[i] = 0;
		}
	}
	void dfs1(int u, int f)
	{
		fa[u] = f;
		dep[u] = dep[f] + 1;
		sz[u] = 1;
		for (auto j : G[u])
		{
			if (j.first != f)
			{
				dfs1(j.first, u);
				sz[u] += sz[j.first];
				if (sz[son[u]] < sz[j.first]) son[u] = j.first;
			}
		}
	}
	void dfs2(int u, int tf)
	{
		top[u] = tf;
		if (!son[u]) return;
		dfs2(son[u], tf);
		for (auto j : G[u])
		{
			if (j.first != son[u] && j.first != fa[u])
			{
				dfs2(j.first, j.first);
			}
		}
	}
	int lca(int u, int v)
	{
		while (top[u] ^ top[v])
		{
			if (dep[top[u]] < dep[top[v]])
			{
				u ^= v;
				v ^= u;
				u ^= v;
			}
			u = fa[top[u]];
		}
		if (dep[u] < dep[v]) swap(u, v);
		return v;
	}
}f;

void dfs(int u, int f, int w)
{
	fa[u][0] = f;
	sum1[u] = sum1[f] + w;
	sum2[u] = sum2[f] + 1;
	for (auto j : G[u])
	{
		if (j.first != f) dfs(j.first, u, j.second);
	}
}

void solve_fa()
{
	for (int i = 1; i <= 30; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			fa[j][i] = fa[fa[j][i - 1]][i - 1];
		}
	}
}

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cin >> t;
	while (t--)
	{
		cin >> n;
		for (int i = 1; i <= n; i++) G[i].clear();
		for (int i = 1; i < n; i++)
		{
			int u, v, w;
			cin >> u >> v >> w;
			G[u].push_back(make_pair(v, w));
			G[v].push_back(make_pair(u, w));
		}
		for (int i = 1; i <= n; i++)
		{
			for (int j = 0; j <= 30; j++) fa[i][j] = 0;
		}
		f.Init(n);
		f.dfs1(1, 0);
		f.dfs2(1, 1);
		dfs(1, 0, 0);
		solve_fa();
		string s;
		while (cin >> s && s != "DONE")
		{
			if (s[0] == 'D')
			{
				int u, v;
				cin >> u >> v;
				int lca = f.lca(u, v);
				cout << sum1[u] + sum1[v] - 2 * sum1[lca] << "\n";
			}
			else
			{
				int u, v, k;
				cin >> u >> v >> k;
				int lca = f.lca(u, v);
				int dist_of_u_and_lca = sum2[u] - sum2[lca] + 1;
				if (dist_of_u_and_lca >= k)
				{
					// 所求的点在 u 到 lca 的路径上
					int now = u, p = 0;
					k--;
					while (k)
					{
						if (k & 1)
						{
							now = fa[now][p];
						}
						k >>= 1;
						p++;
					}
					cout << now << "\n";
				}
				else
				{
					//cout << dist_of_u_and_lca << "\n";
					k -= dist_of_u_and_lca;
					int dist_of_v_and_lca = sum2[v] - sum2[lca];
					//cout << dist_of_v_and_lca << "\n";
					k = dist_of_v_and_lca - k;
					int now = v, p = 0;
					//k--;
					while (k)
					{
						if (k & 1)
						{
							now = fa[now][p];
						}
						p++;
						k >>= 1;
					}
					cout << now << "\n";
				}
			}
		}
	}
	return 0;
}
```


---

## 作者：MeowScore (赞：2)

交了二十遍才过，原因： `#define int long long` 却用 `%d` 读入……

我写树剖！~~因为我不会倍增。~~

边权和很好做，我是维护的线段树。

主要问题在路径上的第 $k$ 个点。

这里要进行分类讨论了。（下面所用的一条路径上的点的个数可以用深度算出来）

+ 起点到 LCA 路径上的点的个数不少于 $k$。那就往上一直跳，直到某次跳完就超过第 $k$ 个点了，那这次就不跳，利用重链上时间戳连续的性质计算出答案。

+ 起点到 LCA 路径上的点的个数少于 $k$。那就利用起点到 LCA 路径上的点的个数，终点到 LCA 路径上的点的个数算出从我们的答案等价于从终点开始走的第几个点。然后重复第一种情况的做法即可。

还要开一个数组记录一个时间戳所对应的点的点号。

代码：

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1000010;
int head[N],to[N*2],nex[N*2],cnt,e[N*2];
void add(int x,int y,int z){
	cnt++;
	to[cnt]=y;
	e[cnt]=z;
	nex[cnt]=head[x];
	head[x]=cnt;
}
int T,n;
int dep[N],fa[N],sz[N],son[N],tp[N],tot,dfn[N];
int t[N];//边转点初始权值
int a[N];//建立在dfn上的权值
int p[N];//该时间戳对应的点号 
void dfs1(int x,int f){
	sz[x]=1;
	dep[x]=dep[f]+1;
	fa[x]=f;
	int maxn=-1;
	for(int i=head[x];i;i=nex[i]){
		int y=to[i];
		if(y==f)
			continue;
		t[y]=e[i];
		dfs1(y,x);
		sz[x]+=sz[y];
		if(sz[y]>maxn){
			maxn=sz[y];
			son[x]=y;
		}
	}
}
void dfs2(int x,int top){
	tp[x]=top;
	tot++;
	dfn[x]=tot;
	p[tot]=x;
	a[tot]=t[x];
	if(son[x])
		dfs2(son[x],top);
	for(int i=head[x];i;i=nex[i]){
		int y=to[i];
		if(y==fa[x]||y==son[x])
			continue;
		dfs2(y,y);
	}
}
int st[N*4];
void build(int root,int l,int r){
	if(l==r){
		st[root]=a[l];
		return;
	}
	int mid=(l+r)/2;
	build(root*2,l,mid);
	build(root*2+1,mid+1,r);
	st[root]=st[root*2]+st[root*2+1];
}
int res;
int lca(int x,int y){
	while(tp[x]!=tp[y]){
		if(dep[tp[x]]<dep[tp[y]])
			swap(x,y);
		x=fa[tp[x]];
	}
	if(dep[x]<dep[y])
		return x;
	return y;
}
void ask(int root,int l,int r,int x,int y){
	if(l>=x&&r<=y){
		res+=st[root];
		return;
	}
	int mid=(l+r)/2;
	if(mid>=x)
		ask(root*2,l,mid,x,y);
	if(mid+1<=y)
		ask(root*2+1,mid+1,r,x,y);
}
signed main(){
//	freopen("QTree2.in","r",stdin);
//	freopen("QTree2.out","w",stdout);
	cin>>T;
	while(T--){
		cin>>n;
		memset(head,0,sizeof(head));
		memset(son,0,sizeof(son));
		cnt=0;
		tot=0;
		for(int i=1;i<n;i++){
			int x,y,z;
			scanf("%lld%lld%lld",&x,&y,&z);
			add(x,y,z);
			add(y,x,z);
		}
		dep[1]=0; 
		dfs1(1,1);
		dfs2(1,1);
		build(1,1,n);
		string opt;
		while(cin>>opt){
			if(opt[1]=='O')
				break;
			if(opt[0]=='D'){
				int x,y;
				res=0;
				scanf("%lld%lld",&x,&y);
				while(tp[x]!=tp[y]){
					if(dep[tp[x]]<dep[tp[y]])
						swap(x,y);
					ask(1,1,n,dfn[tp[x]],dfn[x]);
					x=fa[tp[x]];
				}
				if(x!=y){
					if(dep[x]>dep[y])
						swap(x,y);
					ask(1,1,n,dfn[x]+1,dfn[y]);
				}
				printf("%lld\n",res);
			}
			else{
				int x,y,k;
				scanf("%lld%lld%lld",&x,&y,&k);
				int xx=x,yy=y;
				int LCA=lca(x,y);
				int d=dep[x]-dep[LCA]+1;
				int ans=-1;
				if(d>=k){
					while(ans==-1){
						if(dep[xx]-dep[tp[x]]+1<k)
							x=fa[tp[x]];
						else{
							ans=p[dfn[x]-k+dep[xx]-dep[x]+1];
							break;
						}
					}
				}
				else{
					k-=d;
					k=dep[y]-dep[LCA]-k+1;
					while(ans==-1){
						if(dep[yy]-dep[tp[y]]+1<k)
							y=fa[tp[y]];
						else{
							ans=p[dfn[y]-k+dep[yy]-dep[y]+1];
							break;
						}
					}
				}
				printf("%lld\n",ans);
			}
		}
	}
	return 0;
}







```



















---

## 作者：81179332_ (赞：2)

静态询问 $u$ 到 $v$ 的距离和 $u$ 到 $v$ 的有向路径上的第 $k$ 个点是什么。

对于距离的询问，$dis_{u,v}=dep_u+dep_v-2\times dep_{lca}$。

对于第 $k$ 个点的询问，分两种情况讨论一下，若 $u$ 到 $lca$ 的路径上的点数大于或等于 $k$，那么第 $k$ 个点为 $u$ 的 $k$ 级祖先；否则第 $k$ 个点在 $lca$ 到 $v$ 的简单路径上，注意此时是从 $lca$ 到 $v$ 的第 $k$ 个点，要用 $lca$ 到 $v$ 路径上的点数减一下。

```cpp
#include<cstdio>
#include<algorithm>
#include<cctype>
#include<cstring>

using namespace std;

#define INF 1000000000
#define pprint(x) print(x),putchar(' ')
#define fprint(x) print(x),putchar('\n')

//#define getchar() (SS == TT && (TT = (SS = BB) + fread(BB,1,1 << 15,stdin),TT == SS) ? EOF : *SS++)
char BB[1 << 15],*SS = BB,*TT = BB;
inline long long read()
{
	long long x = 0;int f = 1;
	char ch = getchar();
	for(;!isdigit(ch);ch = getchar())
		if(ch == '-')
			f = -1;
	for(;isdigit(ch);ch = getchar())
		x = x * 10 + (ch ^ 48);
	return x * f;
}
void print(long long x)
{
	if(x < 0)
		putchar('-'),x = -x;
	if(x > 9)
		print(x / 10);
	putchar(x % 10 + '0');
}

const int N = 10010;

struct edge
{
	int to,nxt,w;
}e[N << 1];
int head[N],cnt;
void add(int u,int v,int w)
{
	e[++cnt].to = v,e[cnt].w = w,e[cnt].nxt = head[u];
	head[u] = cnt;
}
void add_edge(int u,int v,int w)
{
	add(u,v,w),add(v,u,w);
}

int n;
int f[N][19],dep[N],dis[N];

void dfs(int u,int fa)
{
	f[u][0] = fa,dep[u] = dep[fa] + 1;
	for(int i = head[u];i;i = e[i].nxt)
	{
		int v = e[i].to;
		if(v == fa)
			continue;
		dis[v] = dis[u] + e[i].w;
		dfs(v,u);
	}
}

int LCA(int u,int v)
{
	if(dep[u] < dep[v])
		swap(u,v);
	int h = dep[u] - dep[v];
	for(int i = 18;~i;i--)
		if(h & (1 << i))
			u = f[u][i];
	if(u == v)
		return u;
	for(int i = 18;~i;i--)
		if(f[u][i] != f[v][i])
			u = f[u][i],v = f[v][i];
	return f[u][0];
}
int KTH(int u,int k)
{
	for(int i = 19;~i;i--)
		if(k & (1 << i))
			u = f[u][i];
	return u;
}
int DIS(int u,int v)
{
	return dis[u] + dis[v] - 2 * dis[LCA(u,v)];
}

int main()
{
	int T = read();
	while(T--)
	{
		memset(head,0,sizeof(head)),cnt = 0;
		memset(dep,0,sizeof(dep)),memset(f,0,sizeof(f)),memset(dis,0,sizeof(dis));
		n = read();
		for(int i = 1;i < n;i++)
		{
			int u = read(),v = read(),w = read();
			add_edge(u,v,w);
		}
		dfs(1,0);
		for(int j = 1;j < 19;j++)
			for(int i = 1;i <= n;i++)
				f[i][j] = f[f[i][j - 1]][j - 1];
		char op[10];
		while(1)
		{
			scanf("%s",op);
			if(op[0] == 'K')
			{
				int u = read(),v = read(),k = read();
				int lca = LCA(u,v),l = dep[u] - dep[lca] + 1,r = dep[v] - dep[lca] + 1;
				if(l >= k)
					fprint(KTH(u,k - 1));
				else
					fprint(KTH(v,r - (k - l) - 1));
			}
			else if(op[1] == 'I')
				fprint(DIS(read(),read()));
			else
				break;
		}
	}
	return 0;
}
``

---

## 作者：Milthm (赞：1)

这是我的第 $99$ 道蓝捏。

拿到题你很容易想到树链剖分，但是忘了谁说过：“树链剖分谁写谁玩原神”，所以我们就想想有没有其它办法。

我们知道，有个东西叫做倍增，它对一些简单的树上问题是很有用的。观察一下这题怎么倍增解决：

第一个操作是两个点 $u,v$ 路径上的边权之和，是可以解决的。首先预处理出每个点 $i$ 到根节点之间的路径边权之和 $sum_i$，然后我们发现，如果你直接写 $sum_u+sum_v$ 的话，那会多加一段值。我们发现，到达 $u,v$ 的最近公共祖先 $lca(u,v)$ 时，上面的所有值都多加了两遍，所以答案其实是 $sum_u+sum_v-2sum_{lca(u,v)}$。最近公共祖先可以采用倍增很快的求出来。

第二个操作是 $u,v$ 路径上的第 $k$ 个点。你发现我们可以分类讨论。设 $dep_i$ 表示第 $i$ 个点的深度，如果 $dep_u-dep_{lca(u,v)}+1\gt k$，那么这个答案应该在 $u$ 至最近公共祖先这条链上，答案是 $u$ 的 $k-1$ 级祖先。否则就在最近公共祖先到 $v$ 的那条链上，你推一下式子可以得到答案是 $v$ 的第 $dep_u+dep_v-2dep_{lca(u,v)}-k+1$ 级祖先。

这个求多少级祖先很好求，同样是倍增往上跳就可以了。

时间复杂度 $O(q \log n)$。

### AC code

```cpp
#include<bits/stdc++.h>
#define N 100005
using namespace std;
int T,n,num,h[N*2],f[N],dep[N],st[N][25],sum[N];
struct edge{
	int u,v,w,nxt;
}e[N*2];
void add(int u,int v,int w){
	e[++num]={u,v,w,h[u]};h[u]=num;
}
int read(){
	char c=getchar();int ans=0;
	while(!isdigit(c))c=getchar();
	while(isdigit(c))ans=ans*10+c-'0',c=getchar();
	return ans; 
}
void dfs(int u,int fa){
	st[u][0]=f[u]=fa;dep[u]=dep[fa]+1;
	for(int i=h[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v!=fa)sum[v]=sum[u]+e[i].w,dfs(v,u);
	}
}
int lca(int u,int v){
	if(dep[v]>dep[u])swap(u,v);
	for(int i=19;i>=0;--i){
		if(dep[st[u][i]]>=dep[v])u=st[u][i];
	}
	if(u==v)return u;
	for(int i=19;i>=0;--i){
		if(st[u][i]!=st[v][i])u=st[u][i],v=st[v][i];
	}
	return st[u][0];
}
int kth(int u,int k){
	for(int i=19;i>=0;--i)if(k&(1<<i))u=st[u][i];
	return u;
}
int main(){
	T=read();
	while(T--){
		n=read();
		for(int i=1;i<=2*n;++i)h[i]=0,e[i]={0,0,0,0};num=0;
		for(int i=1;i<=n;++i){
			dep[i]=f[i]=0;
			for(int j=1;j<=20;++j)st[i][j]=0;
		}
		for(int i=1;i<n;++i){
			int u,v,w;u=read();v=read();w=read();
			add(u,v,w);add(v,u,w);
		}
		dfs(1,0);
		for(int j=1;j<=20;++j){
			for(int i=1;i<=n;++i)st[i][j]=st[st[i][j-1]][j-1];
		}
		string op;int u,v,k;
		while(cin>>op){
			if(op=="DONE")break;
			u=read();v=read();
			if(op=="DIST")printf("%d\n",sum[u]+sum[v]-2*sum[lca(u,v)]);
			else{
				k=read();
				int l=lca(u,v);
				if(dep[u]-dep[l]+1>k)printf("%d\n",kth(u,k-1));
				else printf("%d\n",kth(v,dep[u]+dep[v]-dep[l]*2-k+1));
			}
		}
	}
	return 0;
}
```




---

## 作者：vocaloid (赞：1)

$\text{LCA}$。利用倍增 $\text{LCA}$ 的思想做这题非常简单，而且这题没有修改，所以不用树链剖分。

（这大概是 $\text{QTree}$ 里唯一一道不用树剖的题目了）

首先在预处理时，照例处理 $f$ 和 $dep$ 数组，同时因为要求两点间距离，所以处理根节点到该点的距离 $dis$。对于每个 $\text{DIST}$ 询问，直接输出 $dis[u]+dis[v]-dis[lca]\times2$ 即可。

```cpp
	if(s=="DIST")
	{
		int x,y;
		scanf("%d %d",&x,&y);
		int lca=LCA(x,y);
		printf("%lld\n",dis[x]+dis[y]-dis[lca]*2);
	}
```

而 $\text{KTH}$ 询问则比较困难。首先，我们可以根据倍增 $\text{LCA}$ 的数组 $f$ 来写出一个 **查找 $u$ 的 $k$ 级祖先** 的函数，如下。

```cpp
int FindKthFather(int u,int k)
{
	for(int i=20;i>=0;i--)
	{
		int x=1<<i;
		if(k>=x)
		{
			u=f[u][i];
			k-=x;
		}
	}
	return u;
}
```

应该不难理解，不再赘述。

接下来分类考虑 $\text{KTH}$ 的两种情况，我们称 $u$ 到 $lca$ 这一段有 $L$ 个点，称 $lca$ 到 $v$ 这一段有 $R$ 个点。

首先，很明显，如果 $L≥k$ ，也就意味着我们要求的点是 $u$ 的直系祖先，但因为我们是从 $u$ 开始数的，所以我们要求的是 $u$ 的 $k-1$ 级祖先，调用上述的 `FindKthFather` 函数即可求解。

否则如果 $L<k$ ，要求的点必然是 $v$ 的直系祖先，这时求解就略复杂，我的思路是这样的：首先先算出要求的点是 $lca-v$ 这条链上的第几个，也就是从 $lca$ 往 $v$ 数第几个点是我们要求的点，这个是不难求的，$k-L+1$ 即可，然后我们再求出要求的点是 $v$ 的几级祖先即可，经过纸上推导可发现，是 $R-k$ 级祖先，这一步建议读者自己在纸上推导一下，难度较低，也不复杂，能更好加深理解。

分类讨论后的 $\text{KTH}$ 操作如下。

```cpp
	if(s=="KTH")
	{
		int x,y,k;
		scanf("%d %d %d",&x,&y,&k);
		int lca=LCA(x,y);
		int L=dep[x]-dep[lca]+1,R=dep[y]-dep[lca]+1;
		if(L>=k) printf("%d\n",FindKthFather(x,k-1));
		else
		{
			k=k-L+1;
			k=R-k;
			printf("%d\n",FindKthFather(y,k));
		}
    }
```

普通的倍增 $\text{LCA}$ 预处理不再赘述。

---

## 作者：wuyou03 (赞：1)

这题有两个操作：  
$DIST$ a b，我们直接使用倍增法求出两个点的$LCA$，预处理出树上边权前缀和，ab两点的距离就等同于$Sum[a]+Sum[b]-2\times Sum[LCA]$。  
$KTH$ a b k，求出$LCA$后分类讨论即可。  
有$2$种情况：（$Dep[x]$为点$x$的深度）  
$(1)$第$k$个点在从$a$到$LCA$的路径上（$k \leq Dep[a]-Dep[LCA]+1$），答案是a的第$k-1$个父亲，需要注意这里$k=1$的情况需要特判。  
$(2)$第$k$个点在从$b$到$LCA$的路径（不包括$LCA$）上（$k \geq Dep[a]-Dep[LCA]+2$），答案是b的第$Dep[a]+Dep[b]-2 \times Dep[LCA]+2-k$个父亲，需要注意这里$k=Dep[a]+Dep[b]-2 \times Dep[LCA]+2$的情况需要特判。  
# 这题时限较紧，建议别用vector存边
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct EDGE{int to; long long val;}edge[20005]; //这题时限较紧，建议手写链表存边
struct Data{int NODE; long long DIST;};
int T,EdgeCnt,n,A,B,C,head[10005],tail[10005],nex[20005],Dep[10005]; long long f[10005][18][2]; char cmd[10];
void AddEdge(int u,int v,int w){
    ++EdgeCnt;
    if(!head[u]) head[u]=tail[u]=EdgeCnt;
    else {nex[tail[u]]=EdgeCnt; tail[u]=EdgeCnt;}
    edge[EdgeCnt].to=v; edge[EdgeCnt].val=(long long)w;
}
void dfs(int root){
    for(int i=head[root];edge[i].to;i=nex[i])
        if(edge[i].to!=f[root][0][0]) 
            f[edge[i].to][0][0]=(long long)root,
            f[edge[i].to][0][1]=edge[i].val,
            Dep[edge[i].to]=Dep[root]+1,
            dfs(edge[i].to);
}
Data Jump(int node,int height){ //倍增法求祖先
    int Cnt=0; long long Dist=0;
    while(height){
        Dist+=f[node][Cnt+__builtin_ffs(height)-1][1];//这种写法需要考虑一些细节问题
        node=f[node][Cnt+__builtin_ffs(height)-1][0];
        Cnt+=__builtin_ffs(height);
        height>>=__builtin_ffs(height);
    }
    return (Data){node,Dist};
}
Data GetLCA(int a,int b){ //倍增法求LCA
    if(Dep[a]<Dep[b]) swap(a,b);
    int DepTmp=Dep[a]-Dep[b]; long long Dist1=0;
    if(Dep[a]!=Dep[b]){
        int Cnt=0;
        while(DepTmp){
            Dist1+=f[a][Cnt+__builtin_ffs(DepTmp)-1][1];
            a=f[a][Cnt+__builtin_ffs(DepTmp)-1][0];
            Cnt+=__builtin_ffs(DepTmp);
            DepTmp>>=__builtin_ffs(DepTmp);
        }
    }
    if(a!=b){
        int l=1,r=Dep[a]-1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(Jump(a,mid).NODE==Jump(b,mid).NODE) r=mid-1;
            else l=mid+1;
        }
        Data Tmp=Jump(a,r+1);
        return (Data){Tmp.NODE,Tmp.DIST+Dist1+Jump(b,r+1).DIST};
    }else return (Data){a,Dist1};
}
int main(){
    scanf("%d",&T);
    for(int c=0;c<T;c++){
        memset(head,0,sizeof(head));
        memset(tail,0,sizeof(tail));
        memset(nex,0,sizeof(nex));
        memset(Dep,0,sizeof(Dep));
        EdgeCnt=0;
        for(int i=0;i<20005;i++)
            edge[i].to=0,edge[i].val=(long long)0; 
        for(int i=0;i<10005;i++)
        for(int j=0;j<18;j++)
            f[i][j][0]=f[i][j][1]=0;
        scanf("%d",&n);
        for(int i=1;i<n;i++){
            scanf("%d%d%d",&A,&B,&C);
            AddEdge(A,B,C);
            AddEdge(B,A,C);
        }
        Dep[1]=1;
        dfs(1);
        for(int i=1;i<18;i++)
        for(int j=1;j<=n;j++){
            f[j][i][0]=f[f[j][i-1][0]][i-1][0]; //倍增法求点j的第2^x个父亲
            f[j][i][1]=f[j][i-1][1]+f[f[j][i-1][0]][i-1][1]; //倍增时顺便求出边权和
        }
        while(~scanf("%s",cmd)&&cmd[1]!='O'){
            if(cmd[0]=='D') {
                scanf("%d%d",&A,&B);
                printf("%lld\n",GetLCA(A,B).DIST);
            }else{
                scanf("%d%d%d",&A,&B,&C);
                if(C==1) {printf("%d\n",A);continue;} //k为a自己的特判
                int LCa=GetLCA(A,B).NODE;
                if(Dep[A]-Dep[LCa]+1>=C) printf("%d\n",Jump(A,C-1).NODE);
                else {
                    if(C==Dep[A]+Dep[B]-(Dep[LCa]<<1)+1) {printf("%d\n",B);continue;} //k为最后一个点的特判
                    printf("%d\n",Jump(B,Dep[A]+Dep[B]-(Dep[LCa]<<1)-C+1).NODE);
                }
            }
        }
        printf("\n");
    }
} 
```

---

## 作者：KSkun (赞：1)

本题解同步发布于我的博客：[[SPOJ-QTREE2]Query on a tree II 题解 | KSkun's Blog](https://ksmeow.moe/qtree2_spoj_sol/)

# 题解
求和同QTREE：[题解 SP375 【QTREE - Query on a tree】 - KSkun's Blog - 洛谷博客](https://kskun.blog.luogu.org/solution-sp375)。查k点可以考虑算一下LCA到两个儿子的距离，看看这个点在哪条链上，然后再换算成底端往上第几个点，沿重链上跳，利用DFS序算出来即可。

# 代码
```cpp
// Code by KSkun, 2018/3
#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

typedef long long LL;

inline char fgc() {
	static char buf[100000], *p1 = buf, *p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}

inline int readint() {
	register int res = 0, neg = 1;
	register char c = fgc();
	while(c < '0' || c > '9') {
		if(c == '-') neg = -1;
		c = fgc();
	}
	while(c >= '0' && c <= '9') {
		res = res * 10 + c - '0';
		c = fgc();
	}
	return res * neg;
}

inline bool isop(char c) {
	return c == 'I' || c == 'H' || c == 'O';
}

inline char readop() {
	register char c;
	while(!isop(c = fgc()));
	return c;
}

const int MAXN = 10005;

struct Edge {
	int to, w, nxt;
} gra[MAXN << 1];
int head[MAXN], tot;

int T, n, m, ut, vt, wt, kt;
char op;
int w[MAXN], fa[MAXN], siz[MAXN], son[MAXN], dfn[MAXN], ptn[MAXN], top[MAXN], dep[MAXN], cnt;

inline void dfs1(int u) {
	siz[u] = 1;
	son[u] = 0;
	for(register int i = head[u]; i; i = gra[i].nxt) {
		register int v = gra[i].to;
		if(v == fa[u]) continue;
		dep[v] = dep[u] + 1;
		fa[v] = u;
		w[v] = gra[i].w;
		dfs1(v);
		siz[u] += siz[v];
		if(siz[v] > siz[son[u]]) son[u] = v;
	}
}

inline void dfs2(int u, int tp) {
	top[u] = tp;
	dfn[u] = ++cnt;
	ptn[dfn[u]] = u;
	if(son[u]) dfs2(son[u], tp);
	for(register int i = head[u]; i; i = gra[i].nxt) {
		register int v = gra[i].to;
		if(v == son[u] || v == fa[u]) continue;
		dfs2(v, v);
	}
}

LL sgt[MAXN << 2];

inline void build(int o, int l, int r) {
	if(l == r) {
		sgt[o] = w[ptn[l]];
		return;
	}
	register int mid = (l + r) >> 1, lch = o << 1, rch = (o << 1) | 1;
	build(lch, l, mid);
	build(rch, mid + 1, r);
	sgt[o] = sgt[lch] + sgt[rch];
}

inline void modify(int o, int l, int r, int x, int v) {
	if(l == r) {
		sgt[o] = v;
		return;
	}
	register int mid = (l + r) >> 1, lch = o << 1, rch = (o << 1) | 1;
	if(x <= mid) modify(lch, l, mid, x, v);
	else modify(rch, mid + 1, r, x, v);
	sgt[o] = sgt[lch] + sgt[rch];
}

inline LL query(int o, int l, int r, int ll, int rr) {
	if(l >= ll && r <= rr) {
		return sgt[o];
	}
	register int mid = (l + r) >> 1, lch = o << 1, rch = (o << 1) | 1;
	register LL res = 0;
	if(ll <= mid) res += query(lch, l, mid, ll, rr);
	if(rr > mid) res += query(rch, mid + 1, r, ll, rr);
	return res;
}

inline LL querysum(int u, int v) {
	int tu = top[u], tv = top[v];
	register LL res = 0;
	while(tu != tv) {
		if(dep[tu] > dep[tv]) {
			std::swap(u, v);
			std::swap(tu, tv);
		}
		res += query(1, 1, n, dfn[tv], dfn[v]);
		v = fa[tv];
		tv = top[v];
	}
	if(dep[u] > dep[v]) std::swap(u, v);
	if(u != v) res += query(1, 1, n, dfn[u] + 1, dfn[v]);
	return res;
}

inline int querylca(int u, int v) {
	int tu = top[u], tv = top[v];
	while(tu != tv) {
		if(dep[tu] > dep[tv]) {
			std::swap(u, v);
			std::swap(tu, tv);
		}
		v = fa[tv];
		tv = top[v];
	}
	if(dep[u] > dep[v]) std::swap(u, v);
	return u;
}

inline int querykth(int u, int v, int k) {
	int lca = querylca(u, v), tu = top[u], tv = top[v];
	if(dep[u] - dep[lca] + 1 >= k) {
		while(dep[tu] > dep[lca]) {
			if(dep[u] - dep[tu] + 1 >= k) break;
			k -= dep[u] - dep[tu] + 1;
			u = fa[tu];
			tu = top[u];
		}
		return ptn[dfn[u] - k + 1];
	} else {
		k -= dep[u] - dep[lca] + 1;
		k = dep[v] - dep[lca] - k + 1;
		while(dep[tv] > dep[lca]) {
			if(dep[v] - dep[tv] + 1 >= k) break;
			k -= dep[v] - dep[tv] + 1;
			v = fa[tv];
			tv = top[v];
		}
		return ptn[dfn[v] - k + 1];
	}
}

inline void addedge(int u, int v, int w) {
	gra[++tot] = Edge {v, w, head[u]};
	head[u] = tot;
}

int main() {
	T = readint();
	while(T--) {
		tot = cnt = 0;
		memset(head, 0, sizeof(head));
		n = readint();
		for(int i = 1; i < n; i++) {
			ut = readint(); vt = readint(); wt = readint();
			addedge(ut, vt, wt);
			addedge(vt, ut, wt);
		}
		dfs1(1);
		dfs2(1, 1);
		build(1, 1, n);
		for(;;) {
			op = readop();
			if(op == 'O') break;
			ut = readint();
			vt = readint();
			if(op == 'I') {
				printf("%lld\n", querysum(ut, vt));
			} else {
				kt = readint();
				printf("%d\n", querykth(ut, vt, kt));
			}
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：UnfortunatelyDead (赞：0)

QTREE 的题一般都是恶心的剖剖，但是 QTREE2 其实倍增更简单。

考虑先通过倍增预处理出每个节点 $2^i$ 级别的祖先，这样可以使得 LCA 或一口气连跳 $k$ 步复杂度降为 $\log n$。

我们发现其实边权相较于其他的并不是特别好求和，于是可以考虑边转点操作。

对于这棵树我们以 $1$ 为根，于是我们对于每条边的 $(u,v)$ 都有了父亲和儿子的标签。

如果我们将边权 $w$ 归给父亲 $u$ 的话，很容易发现，$u$ 的儿子有很多个，并不能准确记录；而 $v$ 的父亲只有一个 $u$，那么 $v$ 上的值一定是不会变的。至此，边转点操作完成。

考虑求距离的 `DIST` 操作，其实就是从 $u \rightarrow lca$ 的边权和加上 $v \rightarrow lca$ 的边权和，那么我们可以通过维护 $sum$ 数组实现。

那么接下来考虑 `KTH` 操作，经过 $k$ 个点实质就是经过 $k-1$ 条边，所以下文中的 $k$ 默认是 `k-=1` 的结果，为边数。通过观察不难发现，$u \rightarrow v$ 的最短路径就是 $u \rightarrow lca$ 再 $lca \rightarrow v$。那么我们可以依次得到经过边的数量为 $a = dep_u - dep_{lca}$ 和 $b = dep_v - dep_{lca}$（不过由于 $lca$ 参与了两遍计算，需减去 $1$），那么我们对于 $k$ 的大小，如果 $k \leq a$，就是 $u$ 向上跳 $k$ 层，否则就是在后面一段路径上，就是从 $lca$ 跳下 $k - a$ 层，即 $v$ 跳上 $b - (k-a)$ 层。 

下面是娱乐性极强的代码，省略了缺省源。

```cpp
const int N = 1e4 + 19, lg = 20;
int f[lg][N], sum[N], dep[N];
vector<pii> g[N];
string getstring() {
	string ans = "";
	char c = getchar();
	while (c < 'A' || c > 'Z') c = getchar();
	while (c >= 'A' && c <= 'Z') {
		ans += c; c = getchar();
	} return ans;
}
void dfs(int u, int fa, int tot) {
	f[0][u] = fa; dep[u] = dep[fa] + 1;
	for (int i = 1; i < lg; ++i) f[i][u] = f[i-1][f[i-1][u]];
	sum[u] = tot;
	for (const auto [i, j] : g[u]) {
		if (i != fa) dfs(i, u, tot + j);
	}
}
int lca(int u, int v) {
	if (dep[u] > dep[v]) swap(u, v);
	int c = dep[v] - dep[u];
	for (int i = lg-1; ~i; --i) if (c >= (1 << i)) v = f[i][v], c -= (1 << i);
	if (u == v) return u;
	for (int i = lg-1; ~i; --i) if (f[i][u] ^ f[i][v]) u = f[i][u], v = f[i][v];
	return f[0][u];
}
void getdist(int u, int v) {
	if (dep[u] > dep[v]) swap(u, v);
	int c = dep[v] - dep[u], ans = 0;
	for (int i = lg-1; ~i; --i) if (c >= (1 << i)) ans += sum[v] - sum[f[i][v]], v = f[i][v], c -= (1 << i);
	if (u == v) return write(ans, '\n'), void();
	for (int i = lg-1; ~i; --i) if (f[i][u] ^ f[i][v]) ans += sum[u] - sum[f[i][u]] + sum[v] - sum[f[i][v]], u = f[i][u], v = f[i][v];
	write(ans + sum[u] - sum[f[0][u]] + sum[v] - sum[f[0][v]], '\n');
}
void findans(int u, int v, int k) {
	int fa = lca(u, v); --k;
	if (dep[u] - dep[fa] < k) {
		k = -dep[fa] * 2 + dep[u] + dep[v] - k;
		swap(u, v);
	}
	for (int i = lg-1; ~i; --i) if (k >= (1 << i)) u = f[i][u], k -= (1 << i);
	write(u, '\n');
}
void solve() {
	int n = read();
	for (int i = 1, u, v, w; i < n; ++i) {
		read(u, v, w);
		g[u].eb(v, w); g[v].eb(u, w);
	} dfs(1, 0, 0);
	string op;
	while ((op = getstring()) != "DONE") {
		int x, y, k;
		read(x, y);
		if (op == "DIST") {
			getdist(x, y);
		} else {
			read(k);
			findans(x, y, k);
		}
	}
}
void clear() {
	for (int i = 0; i < lg; ++i) for (int j = 0; j < N; ++j) f[i][j] = 0;
	for (int i = 0; i < N; ++i) {
		sum[i] = 0;
		g[i].clear();
	}
}
signed main() {
	int T = read();
	while (T--) solve(), clear();
	return 0;
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/SP913)

看到求路径上的边权之和，就可以想到树剖；看到求路径上第 $k$ 个点，就可以想到倍增求 LCA。

## 操作一

标准的树剖，不做过多解释。

```cpp
const int N=1e4+10;
int n,tim,a[N],dfn[N],top[N],fa[N][20],siz[N],son[N],rnk[N],dep[N];
vector<pii>g[N];
/*
tim：时间戳；
a[]：权值；
dfn[]：dfs 序；
top[]：链头；
fa[][]：倍增祖先；
siz[]：节点的子节点数量；
son[]：节点的重儿子；
rnk[]：dfs 序对应的哪个节点；
dep[]：节点深度。
*/
struct node{
	int l,r,sum;
}tr[N<<2];//线段树开 4 倍空间。
void dfs(int x,int f){
	fa[x][0]=f;
	dep[x]=dep[f]+1;
    for(int i=1;(1<<i)<=dep[x];++i)fa[x][i]=fa[fa[x][i-1]][i-1];//顺便处理倍增祖先。
	siz[x]=1;
	for(auto i:g[x]){
		if(i.se==f)continue;//不能重复走。
		a[i.se]=i.fi;//注意这个图是边权，要转化为点权。
		dfs(i.se,x);
		siz[x]+=siz[i.se];
		if(siz[son[x]]<siz[i.se])son[x]=i.se;
	}
	return ;
}
void dfs2(int x,int tp){//剖成链。
	top[x]=tp;
	dfn[x]=++tim;
	rnk[tim]=x;
	if(son[x])dfs2(son[x],tp);
	for(auto i:g[x]){
		if(i.se==fa[x][0]||i.se==son[x])continue;//不能重复走。
		dfs2(i.se,i.se);
	}
	return ;
}
void build(int i,int l,int r){//建树板子。
    tr[i].l=l;
    tr[i].r=r;
    if(l==r){
        tr[i].sum=a[rnk[l]];
        return ;
    }
    int mid=l+r>>1;
    build(i<<1,l,mid);
    build(i<<1|1,mid+1,r);
    tr[i].sum=tr[i<<1].sum+tr[i<<1|1].sum;
    return ;
}
int query(int i,int l,int r){//查询区间和板子。
    if(l<=tr[i].l&&tr[i].r<=r)return tr[i].sum;
    int mid=tr[i].l+tr[i].r>>1,res=0;
    if(l<=mid)res+=query(i<<1,l,r);
    if(mid<r)res+=query(i<<1|1,l,r);
    return res;
}
inline int lsum(int x,int y){//用 LCA 的方式求和。
    int res=0;
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]])swap(x,y);
        res+=query(1,dfn[top[x]],dfn[x]);
        x=fa[top[x]][0];
    }
    if(dep[x]>dep[y])swap(x,y);
    return res+query(1,dfn[x]+1,dfn[y]);//注意是边权化为深度大的节点的点权，所以根节点不查询，要 +1。
}
```

## 操作二

要分类讨论路径上第 $k$ 个点是在 LCA 节点的**靠近起点的子树**还是**靠近终点的子树**中。如果是后者，那么把 $k$ 转化为从终点开始数的编号，并更改起点为终点。最后用倍增法找到这个节点并输出。

```cpp
//变量名同上文。
inline int lca(int x,int y){//树剖 LCA 会快一点。
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]])swap(x,y);
        x=fa[top[x]][0];
    }
    if(dep[x]>dep[y])swap(x,y);
    return x;
}
inline int find(int x,int y,int k){
    int rt=lca(x,y);
    if(dep[x]-dep[rt]+1<=k){//如果靠近终点就转换目标节点。
        k=dep[x]+dep[y]-dep[rt]*2+2-k;
        x=y;
    }
    for(int i=15;i>=0;--i){//不断让 x 逼近目标节点。
        if(k>=(1<<i)+1){
            x=fa[x][i];
            k-=1<<i;
        }
    }
    return x;
}
```

## 简短的主函数

注意有多组测试数据，记得清空变量。

```cpp
inline void solve(){
	n=read();
	for(int i=1;i<n;++i){
		int u=read(),v=read(),w=read();
		g[u].pb({w,v});
		g[v].pb({w,u});
	}
	dfs(1,0);
	dfs2(1,1);
    build(1,1,n);
    string s;
	while(cin>>s){
		if(s=="DONE")break;
        if(s=="DIST"){//查询路径上的边权和。
            int u=read(),v=read();
            print(lsum(u,v));
        }
        else{//查询路径上第 k 个点。
            int u=read(),v=read(),k=read();
            print(find(u,v,k));
        }
        puts("");
	}
	for(int i=1;i<=n;++i){
        g[i].clear();
        top[i]=dfn[i]=rnk[i]=siz[i]=son[i]=a[i]=dep[i]=tim=0;
        for(int j=0;j<=15;++j)fa[i][j]=0;
    }
	return ;
}
```

[AC 记录](https://www.luogu.com.cn/record/149078164)

---

## 作者：_RainCappuccino_ (赞：0)

# [QTREE2 - Query on a tree II](https://www.luogu.com.cn/problem/SP913)

> $\mathtt {TAGS}$：$\mathtt{LCA}$，倍增，树上操作
>
> $\mathtt {APPRAISE}$：倍增板题。

## 前置知识

- [最近公共祖先 - OI Wiki](https://oiwiki.com/graph/lca/)
- [最近公共祖先 - 倍增算法](https://oiwiki.com/graph/lca/#%E5%80%8D%E5%A2%9E%E7%AE%97%E6%B3%95)

## 定义

由于根节点是哪一个对本题的求解并没有影响（因为树上两点的简单路径是唯一的），所以本文中默认根节点为 $1$。

- $dis_{u,v}$ 指 $u$ 到 $v$ 的唯一简单路径长度。
- $d_{u}$ 指 $u$ 到根节点的路径长度。
- $fa_{u, k}$ 指 $u$ 的第 $2 ^ k$ 个祖先。
- $dep_u$ 指 $u$ 的深度。

## First. 求 $dis_{u, v}$

**方法 1：**

因为 $u,v$ 不一定在同一颗子树上，直接求 $dis_{u, v}$ 不好求，那么我们尝试将其转化为我们好求的值 $d_u$ 和 $d_v$，通过他们得到 $dis_{u,v}$。

不妨把 $dis_{u, v}$ 拆解成 $dis_{u, lca(u,v)}$ 和 $dis_{\text{lca(u,v)},v}$，此时由于 $\text{lca(u,v)}$ 是 $u$ 的祖先，所以它一定在 $u$ 到 根节点的路径上，那么 $dis_u = d_u - d_{\text{lca(u,v)}}$，同理，$dis_v = d_v - \text{lca(u,v)}$。

所以 $dis_{u,v}$ 就化为了 $d_u + d_v - d_{\text{lca(u,v)}} \times 2$。

如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/of7rlxw6.png)

**方法 2.**
 使用倍增在 $\mathtt{LCA}$ 的过程中求出 $dis_{u,\text{lca(u,v)}}$ 和 $dis_{v, \text{lca(u,v)}}$。

 定义 $ds_{u,k}$ 为 $u$ 到其第 $2 ^ k$ 个祖先的简单路径距离（可以预处理）。

 在用倍增向上跳时，将两个点跳的距离加在一个 $tmp$ 上，最后跳至 $\mathtt{LCA}$ 后，$tmp$ 即为所求。

 这里作者使用的方便一点的方法 1。

 方法 2 在此给出代码：

 - len 即上文中的 $ds$。

 ```cpp

 void dfs(int u, int f) {
	dep[u] = dep[f] + 1, fa[u][0] = f, len[u][0] = e[u][f];
	for (int i = 1; ; i ++) {
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
		len[u][i] = len[fa[u][i - 1]][i - 1] + len[u][i - 1]; // 预处理
		if (fa[u][i] == 0) {
			k = max(k, i - 1);
			break;
		}
	}
	for (auto v : g[u]){
		if(v != f){
			dfs(v, u);
		}
	}
}
int lca(int u, int v){
	if(dep[u] < dep[v]) swap(u, v);
	int x = u, y = v;
	int lu = 0, lv = 0; // 统计两边跳的距离
	for (int i = k; i >= 0; i --){
		if(dep[fa[u][i]] >= dep[v])  lu += len[u][i], u = fa[u][i];
	}
	if(u == v) return lu + lv;
	for (int i = k; i >= 0; i --){
		if(fa[u][i] != fa[v][i]) lu += len[u][i], u = fa[u][i], lv += len[v][i], v = fa[v][i];
	}
	lu += len[u][0], lv += len[v][0];
	return lu + lv;
}
```

## Second. 求 $u$ 到 $v$ 路径上的第 $k$ 个点

这个点的位置有两种情况：

1. 在 $u$ 到 $\mathtt{LCA}$ 的路径上。
2. 在 $\mathtt{LCA}$ 到 $v$ 的路径上。

对于情况 1:

相当于求 $u$ 的第 $k - 1$ 个祖先（因为 $u$ 为第一个点）

对于情况 2：

转化一下，相当于求 $v$ 的第 $\text{路径点数 - k}$ 个祖先。

如下图蓝色路径：

![](https://cdn.luogu.com.cn/upload/image_hosting/bvv07q79.png)

接着直接将 $k$ 二进制拆分，然后用 $f_u$ 向上跳至第 $k$ 祖先即可（具体实现详见代码）。

## 时间复杂度

- 倍增预处理：$\text{O}(n \log {n})$
- $\mathtt{LCA}$：$\text{O}(\log n)$

总时间复杂度：$\text{O}(t \times (n \log {n}+ q \log n)) $

可以通过此题。


## Code

```cpp
vector< pair <int , int> > G[N];
int f[N][30];
ll dis[N];
int dep[N] , K;
void dfs(int u , int fa) { // 预处理
    dep[u] = dep[fa] + 1;
    f[u][0] = fa;
    for (int i = 1; ; i++) {
        f[u][i] = f[f[u][i - 1]][i - 1];
        if (f[u][i] == 0) {
            K = max(K , i - 1);
            break;
        }
    }
    for (auto e : G[u]) {
        int v = e.first , w = e.second;
        if (v != fa) {
            dis[v] = dis[u] + w;
            dfs(v , u);
        }
    }
}
int lca(int u , int v) { // 倍增求 LCA
    if (dep[u] < dep[v]) swap(u , v);
    for (int i = K; i >= 0; i--) {
        if (dep[f[u][i]] >= dep[v]) u = f[u][i];
    }
    if (u == v) return u;
    for (int i = K; i >= 0; i--) {
        if (f[u][i] != f[v][i]) u = f[u][i] , v = f[v][i];
    }
    return f[u][0];
}
int kth_num(int u , int v , int k) {
    int Lca = lca(u , v);
    int dul = dep[u] - dep[Lca] + 1;
    if (dep[u] - dep[Lca] + 1 >= k) { // 情况 1
        int tmp = u;
        k--; // k - 1 个祖先
        for (int i = log2(k); i >= 0; i--) { // 二进制拆分
            if ((k >> i) & 1) { // 需要跳 2^K 次
                tmp = f[tmp][i];
            }
        }
        return tmp;
    } else {// 情况 2
        k -= dep[u] - dep[Lca] + 1;
        k = dep[v] - dep[Lca] - k;
        int tmp = v;
        for (int i = log2(k); i >= 0; i--) {// 二进制拆分
            if ((k >> i) & 1) {// 需要跳 2^K 次
                tmp = f[tmp][i];
            }
        }
        return tmp;
    }
}

signed main() {
    ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 1; i < n; i++) {
            int u , v , w;
            cin >> u >> v >> w;
            G[u].push_back({ v, w });
            G[v].push_back({ u, w });
        }
        dfs(1 , 0);
        string opt;
        int u , v , k;
        while (cin >> opt) {
            if (opt == "DONE") break;
            if (opt == "DIST") {
                cin >> u >> v;
                int Lca = lca(u , v);
                cout << dis[u] + dis[v] - dis[Lca] * 2 << endl;
            } else {
                cin >> u >> v >> k;
                cout << kth_num(u , v , k) << endl;
            }
        }
        // 多测一定要清空！！！！！！
        // 本人在此 RE + WA 了三次
        for (int i = 1; i <= n; i++) G[i].clear();
        memset(f , 0 , sizeof f);
        memset(dis , 0 , sizeof dis);
        memset(dep , 0 , sizeof dep);
    }
    return 0;
}
```

---

## 作者：Zhangikun (赞：0)

## 思路：
一共要做两种询问：
- 两点简单路径的边权之和。
- 从 $x$ 到 $y$ 的路径经过的点（包括 $x$ 和 $y$）中第 $k$ 个点（这里 $x$ 到 $y$ 和 $y$ 到 $x$ 不等价）。

对于第一个询问，可以维护 $dis_i$ 表示节点 $i$ 走到根节点的边权之和，那么 $x$ 到 $y$ 的距离就等于 $dis_x+dis_y-2\times dis_{lca(x,y)}$。对于 $lca$ 我们使用**倍增法**。

对于第二个询问，假设 $dep_i$ 表示节点 $i$ 的深度，也可表示根节点到 $i$ 的路径经过的点数。那么假设 $k\le dis_x$，答案为 $x$ 向上走 $k-1$ 步到达的祖先；假设 $k>dis_y$，设 $len$ 为 $x$ 到 $y$ 路径中经过的点数（即 $dep_x+dep_y-dep_{lca(x,y)}-dep_{fa(lca(x,y))}$），问题转化为：从 $y$ 到 $x$ 的路径中第 $len-k+1$ 个点，即 $y$ 向上走 $len-k$ 步到达的祖先。

跳祖先怎么跳呢？倍增啊。
## 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int cxk=5e5+5;
vector<pair<int,int>>nbr[cxk];
int fa[cxk][30],dep[cxk],dis[cxk],n;
//-----------------------------lca板子
void dfs(int cur)
{
	for(int i=1;i<=25;i++)
		fa[cur][i]=fa[fa[cur][i-1]][i-1];
	dep[cur]=dep[fa[cur][0]]+1;
	for(auto p:nbr[cur])
	{
		int nxt=p.first,w=p.second;
		if(nxt==fa[cur][0])
			continue;
		dis[nxt]=dis[cur]+w;//维护dis
		fa[nxt][0]=cur;
		dfs(nxt);
	}
}
int lca(int x,int y)
{
	if(dep[x]<dep[y])
		swap(x,y);
	for(int i=25;i>=0;i--)
		if(dep[fa[x][i]]>=dep[y])
			x=fa[x][i];
	if(x==y)
		return x;
	for(int i=25;i>=0;i--)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
//-----------------------------
int c(int x,int k)//倍增跳祖先，表示x条k次，在help函数中参数k额外减了1
{
	for(int i=25;i>=0;i--)
		if((k>>i)&1)//这一位为1
			x=fa[x][i];//跳
	return x;
}
void help()
{
	cin>>n;
	memset(dis,0,sizeof(dis));//多测不清空，爆0见祖宗
	memset(dep,0,sizeof(dep));//多测不清空，爆0见祖宗
	memset(fa,0,sizeof(fa));//多测不清空，爆0见祖宗
	for(int i=1;i<=n;i++)
		nbr[i].clear();
	for(int i=1,x,y,w;i<n;i++)
	{
		cin>>x>>y>>w;
		nbr[x].push_back({y,w});
		nbr[y].push_back({x,w});
	}
	dfs(1);
	string s;
	for(int x,y,k;1;)
	{
		cin>>s;
		if(s=="DONE")
			return;
		cin>>x>>y;
		if(s=="DIST")
			cout<<dis[x]+dis[y]-2*dis[lca(x,y)]<<"\n";
		else
		{
			cin>>k;
			int l=lca(x,y),len=dep[x]+dep[y]-dep[l]-dep[fa[l][0]];//路径的长度 
			cout<<max(c(x,k-1),c(y,len-k))<<"\n";
		}
	}
}
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0);
	int t;
    for(cin>>t;t--;help());
}
```

---

## 作者：SrsgPrince_ (赞：0)

# QTREE2 - Query on a tree II 

题面传送门：[QTREE2 - Query on a tree II](https://www.luogu.com.cn/problem/SP913)。

建议在我的 [博客](https://www.luogu.com.cn/blog/fy123333/SP913Solution) 中查看。

## 题目分析 Hint

给定一棵 $n$ 个点的树，边具有边权。要求作以下操作：

1. `DIST a b` 询问点 $a$ 至点 $b$ 路径上的边权之和。
2. `KTH a b k` 询问点 $a$ 至点 $b$ 有向路径上的第 $k$ 个点的编号。

第一个操作是查询点权，第二个操作是查询第 $k$ 个点编号。这道题是 LCA，可以用倍增做，而且倍增做这道题很方便，但是我还是要用树剖，~~绝对不是因为怕“重复的解法”，~~ 为了练习树剖求 LCA。

## 思路 Solution

这道题用树剖做其实小题大做了，这道题树剖的有点基本没啥用。但是还是用树剖做一手，在求 $Kth$ 时先跑出 `lca()`，再决定从哪边开始往上。由于剖分完毕后轻重链都是连续的，所以重复往上至答案所在的链就可以了。代码如下。

```cpp
struct Edge {
    int des, nxt, val;
} ed[maxn << 1];
inline void swap(int &x, int &y) {
    int t = x; x = y; y = t;
}
inline void addEdge(int b, int e, int v) {
    ed[++tot].des = e; ed[tot].val = v;
    ed[tot].nxt = first[b]; first[b] = tot;
}
inline void dfs1(int x, int pre) {
    path[x] = pre; dep[x] = dep[pre] + 1;
    siz[x] = 1; son[x] = 0; int mx = -1;
    for (int i = first[x]; i; i = ed[i].nxt) {
        if (ed[i].des != pre) {
            int v = ed[i].des; dfs1(v, x);
            etv[v] = ed[i].val; siz[x] += siz[v];
            if (siz[v] > mx) son[x] = v, mx = siz[v];
        }
    }
}
inline void dfs2(int x, int pre) {
    top[x] = pre; s[++tot] = etv[x];
    id[x] = tot; rec[tot] = x;
    if (!son[x]) return;
    dfs2(son[x], pre);
    for (int i = first[x]; i; i = ed[i].nxt)
        if (ed[i].des != son[x] && ed[i].des != path[x])
            dfs2(ed[i].des, ed[i].des);
}
inline int qPath(int u, int v) {
    int ans = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        ans += s[id[u]] - s[id[top[u]] - 1];
        u = path[top[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    ans += s[id[v]] - s[id[u]];
    return ans;
}
inline int LCA(int u, int v) {
    while (top[u] != top[v])
        if (dep[top[u]] > dep[top[v]])
            u = path[top[u]];
        else v = path[top[v]];
    return dep[u] < dep[v] ? u : v;
}
inline int findKth(int u, int k) {
    while (dep[u] - k + 1 < dep[top[u]])
        k -= dep[u] - dep[top[u]] + 1, u = path[top[u]];
    return rec[id[u] - k + 1];
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int q;
    cin >> q;
    while (q--) {
        tot = 0;
        memset(first, 0, sizeof(first));
        int n; cin >> n;
        for (int i = 1; i < n; ++i) {
            int u, v, w; cin >> u >> v >> w;
            addEdge(u, v, w); addEdge(v, u, w);
        }
        tot = 0; dfs1(1, 0); dfs2(1, 1);
        for (int i = 1; i <= tot; ++i) s[i] += s[i - 1];
        while (1) {
            char s[5];
            cin >> s;
            if (s[1] == 'O') break;
            if (s[0] == 'D') {
                int x, y; cin >> x >> y;
                cout << qPath(x, y) << "\n";
            } else {
                int x, y, k; cin >> x >> y >> k;
                int res, z = LCA(x, y);
                if (dep[x] - dep[z] + 1 >= k) res = findKth(x, k);
                else res = findKth(y, dep[x] + dep[y] - 2 * dep[z] - k + 2);
                cout << res << "\n";
            }
        }
    }
    return 0;
}
```


---

## 作者：__DDDDDD__ (赞：0)

# 前言

这里提供一种 LCT ~~乱搞~~做法，速度奇慢，可能会被卡掉（目前稳居最优解倒数第一），若本题解有误请各位大佬务必指出！

# 题目分析

-  对于操作 $DIST$ $x$ $y$（动态树基本操作），维护树上各节点子树和，查询时用 split 操作切分出 $x,y$ 之间的路径，输出 $y$ 的子树和即可。这里用到了边化点思想；

-  主要问题在于操作 $KTH$ $x$ $y$ $k$，先考虑如何输出路径：

	用 split 操作切分出动态树上 $x,y$ 之间的路径后，对切分出的的子树进行分析，可以发现按一种类似先序遍历该节点 $\to$ 访问父节点的顺序即可输出原树上 $x,y$ 间的路径。

	具体来说，设当前节点为 $x$，即将回溯到的节点（从该点递推到当前节点）为 $pre$，则按如下步骤进行 DFS：
    
	1. 下推翻转懒标记（因为这个本蒟蒻调了一个小时）；
    
   1. 若左子节点不为 $pre$ 且不为空，访问左子节点；
   1. 若当前节点 $\leq n$（防止输出边化点加入的节点），则输出该节点；
   
   1. 若右子节点不为 $pre$ 且不为空，访问右子节点；
   
   1. 若父节点不为 $pre$ 且不为空，访问父节点。
   
   相关代码如下：
   ```cpp
	inline void out_path(int x,int pre){
		spread(x);//下推懒标记 
		if(c[x][0]!=pre&&c[x][0])out_path(c[x][0],x);//遍历左子节点 
		if(x<=n)cout<<x<<" ";//输出 
		if(c[x][1]!=pre&&c[x][1])out_path(c[x][1],x);//遍历右子节点 
		if(fa[x]!=pre&&fa[x])out_path(fa[x],x);//遍历父节点 
	}
	```
   按题目要求修改一下即可完成该操作。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
const int maxn=1e6+10;
inline int read(){
    re int x=0,f=1;re char ch=getchar();
    while(!isdigit(ch)&&ch!='-')ch=getchar();
    if(ch=='-')f=-1,ch=getchar();
    while(isdigit(ch))x=(x<<3)+(x<<1)+ch-48,ch=getchar();
    return x*f;
}
int n,T;
char opt[233];
struct Link_Cut_Tree{
    int c[maxn][2],fa[maxn];            //左右子节点与父节点 
    int a[maxn],v[maxn];                //单点权值与子树和 
    int rev[maxn];                      //反转懒标记 
    inline void update(int x){
        v[x]=v[c[x][0]]+v[c[x][1]]+a[x];
    }
    inline void spread(int x){
        if(rev[x]){
            rev[c[x][0]]^=1;rev[c[x][1]]^=1;
            rev[x]=0;
            swap(c[x][0],c[x][1]);
        }
    }
    inline bool isroot(int x){
        return c[fa[x]][0]!=x&&c[fa[x]][1]!=x;
    }
    inline void rotate(int x){
        int y=fa[x],z=fa[y];
        int dir=(c[y][0]==x);
        c[y][!dir]=c[x][dir];
        fa[c[x][dir]]=y;
        fa[x]=z;
        if(!isroot(y))c[z][c[z][1]==y]=x;
        c[x][dir]=y;fa[y]=x;
        update(y);update(x);
    }
    int top,st[maxn];                   //下推懒标记辅助栈 
    inline void splay(int x){
        top=1;
        st[top]=x;
        for(int i=x;!isroot(i);i=fa[i])st[++top]=fa[i];
        for(int i=top;i;i--)spread(st[i]);
        while(!isroot(x)){
            int y=fa[x],z=fa[y];
            if(!isroot(y))
                (c[z][0]==y)^(c[y][0]==x)?rotate(x):rotate(y);
            rotate(x);
        }
    }
    inline void access(int x){
        for(int t=0;x;t=x,x=fa[x]){
            splay(x);c[x][1]=t;update(x);
        }
    }
    inline void makeroot(int x){
        access(x);splay(x);rev[x]^=1;
    }
    inline void split(int x,int y){
        makeroot(x);access(y);splay(y);
    }
    inline void link(int x,int y){
        makeroot(x);
        fa[x]=y;
    }
    int rk,cnt,ans;                     //rk 存储目标排名，cnt 计数器，ans 存储答案 
    inline int kth(int x,int y,int k){  //查询排名 
        split(x,y);
        rk=k;cnt=0;
        out_path(x,0);
        return ans;
    }
    inline void out_path(int x,int pre){//修改后的 out_path 操作 
        spread(x);
        if(c[x][0]!=pre&&c[x][0])out_path(c[x][0],x);
        if(x<=n)cnt++;
        if(cnt==rk&&x<=n){
            ans=x;
            return;
        }
        if(c[x][1]!=pre&&c[x][1])out_path(c[x][1],x);
        if(fa[x]!=pre&&fa[x])out_path(fa[x],x);
    }
    inline void clear(){                //清空（真的需要这么暴力吗...？） 
        memset(c,0,sizeof(c));
        memset(fa,0,sizeof(fa));
        top=0;
        memset(st,0,sizeof(st));
        memset(v,0,sizeof(v));
        memset(rev,0,sizeof(rev));
        memset(a,0,sizeof(a));
    }
}lct;
signed main(){
    T=read();
    while(T--){
        lct.clear();
        n=read();
        for(int i=1,u,v,w;i<n;i++){
            u=read();v=read();w=read();
            lct.a[i+n]=w;               //边化点 
            lct.link(u,i+n);lct.link(i+n,v);
        }
        while(1){
            cin>>opt;
            if(opt[1]=='O')break;
            if(opt[1]=='I'){
                int x=read(),y=read();
                lct.split(x,y);
                printf("%d\n",lct.v[y]);
            }else if(opt[1]=='T'){
                int x=read(),y=read(),k=read();
                printf("%d\n",lct.kth(x,y,k));
            }
        }
        putchar('\n');                  //按题目要求输出空行 
    }
    return 0;
}
```


---

## 作者：orz_z (赞：0)


[原题传送门](https://www.luogu.com.cn/problem/SP913)

### 题目大意

给定一棵 $n$ 个点的树，边具有边权。要求作以下操作：

* `DIST`：询问点 $a$ 至点 $b$ 路径上的边权之和。

* `KTH`：询问点 $a$ 至点 $b$ 有向路径上的第 $k$ 个点的编号。

有多组测试数据，每组数据以 `DONE` 结尾。

### 解题思路

前置知识：树上差分，树上倍增，最近公共祖先。

设 $lca$ 为 $u$ 和 $v$ 的最近公共祖先。

对于每个 `DIST` 操作，答案显然为 $dis[u] + dis[v] - 2 * dis[lca]$（典型的树上边差分）。


对于每个 `KTH` 操作，分情况讨论。

* 若 $dep[u] - dep[lca] + 1 < k$，答案即为 $u$ 的 $k$ 级祖先；
* 若 $dep[u] - dep[lca] + 1 > k$，答案为 $v$ 的 $dep[u] + dep[v] - 2 * dep[k] + 2 - k$ 级祖先；
* 若 $dep[u] - dep[lca] + 1 = k$，答案为 $lca$。

时间复杂度：$O((n + q) \log n)$。

### AC CODE

笔者快读太长，不便放在这里。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define _ (int) 1e4 + 5

int T, n;

array<int, _> val;

int tot;
array<int, _> head;
array<int, _ << 1 > to, nxt, w;

array<int, _> dep;
array<array<int, 21>, _> fa;

void add(int a, int b, int c)
{
	to[++tot] = b;
	w[tot] = c;
	nxt[tot] = head[a];
	head[a] = tot;
}

void dfs(int u, int f, int d = 1)
{
	fa[u][0] = f;
	dep[u] = d;
	for(int  i = head[u]; i; i = nxt[i])
	{
		int v = to[i];
		if(v == f) continue;
		val[v] = val[u] + w[i];
		dfs(v, u, d + 1);
	}
}

int LCA(int u, int v)
{
	if(dep[u] > dep[v]) swap(u, v);
	for(int i = 20; i >= 0; --i)
		if(dep[fa[v][i]] >= dep[u])
			v = fa[v][i];
	if(u == v) return u;
	for(int i = 20; i >= 0; --i)
		if(fa[u][i] != fa[v][i])
		{
			u = fa[u][i];
			v = fa[v][i];
		}
	return fa[u][0];
}

int query(int u, int v, int k)
{
	int f = LCA(u, v);
	if (dep[u] - dep[f] + 1 <= k)
	{
		k = dep[u] + dep[v] - (dep[f] << 1) + 2 - k;
		u = v;
	}
	for (int i = 20; i >= 0; --i)
		if (k >= (1 << i) + 1)
		{
			u = fa[u][i];
			k -= (1 << i);
		}
	return u;
}

void init()
{
	tot = 0;
	head.fill(0);
	dep.fill(0);
	fa.fill({0, 0});
	val.fill(0);
}

signed main()
{
	cin >> T;
	while(T--)
	{
		init();
  		cin >> n;
		for(int i = 1; i < n; ++i)
		{
			int a, b, c;
			cin >> a >> b >> c;
			add(a, b, c);
			add(b, a, c);
		}

		dfs(1, 0);
		for(int j = 1; j <= 20; ++j)
			for(int i = 1; i <= n; ++i)
				fa[i][j] = fa[fa[i][j - 1]][j - 1];

		while(1)
		{
			char c[10];
			int x, y, z;
			scanf("%s", c);
			if(c[1] == 'O') break;
			if(c[1] == 'I')
			{
				cin >> x >> y;
				cout << val[x] + val[y] - 2 * val[LCA(x, y)] << endl;
			}
			if(c[1] == 'T')
			{
				cin >> x >> y >> z;
				cout << query(x, y, z) << endl;
			}
		}
	}
}

/*
1
6
1 2 1
2 4 1
2 5 2
1 3 1
3 6 2
DIST 4 6
KTH 4 6 4
DONE
*/
```

---

## 作者：crashed (赞：0)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.com.cn/problem/SP913)看题目。  
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;倍增的模板题。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$DIST$操作是板子。先把树有根化，然后求出每个点到根的距离$s$。设$P=LCA(A,B)$，则答案就是$s(A)+s(B)-2\times s(P)$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$KTH$操作也不难。同样设$P=LCA(A,B)$，答案点的位置只有两种可能——在$A\rightarrow P$的路径上（包括$P$）或者在$P\rightarrow B$的路径上（不包括$P$）。这个可以通过$A\rightarrow P$路径上的点的数量来判断。同时我们还可以计算答案点在所在的路径上是第几个点，于是就可以倍增找点了。  
# 代码
```cpp
#include <cmath>
#include <cstdio>

const int MAXN = 10005, MAXLOG = 15;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar(); int f = 1;
	while( s < '0' || '9' < s ){ f = 1; if( s == '-' ) f = -1; s = getchar(); }
	while( '0' <= s && s <= '9' ){ x = ( x << 3 ) + ( x << 1 ) + s - '0', s = getchar(); }
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ), x = -x; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

struct edge
{
	int to, nxt, w;
	edge() {} edge( int T, int N, int W ) { to = T, nxt = N, w = W; }
}Graph[MAXN << 1];

int f[MAXN][MAXLOG];
int head[MAXN], dep[MAXN], ps[MAXN];
int N, cnt, lg2;

void init() { ps[1] = cnt = 0; for( int i = 1 ; i <= N ; i ++ ) head[i] = 0; }
void addEdge( const int from, const int to, const int W ) { Graph[++ cnt] = edge( to, head[from], W ), head[from] = cnt; }
void balance( int &u, const int steps ) { for( int i = 0 ; ( 1 << i ) <= steps ; i ++ ) if( steps & ( 1 << i ) ) u = f[u][i]; }

void DFS( const int u, const int fa )
{
	dep[u] = dep[fa] + 1, f[u][0] = fa;
	for( int i = head[u], v ; i ; i = Graph[i].nxt )
		if( ( v = Graph[i].to ) ^ fa )
			ps[v] = ps[u] + Graph[i].w, DFS( v, u );
}

void cal()
{
	lg2 = log2( N );
	for( int j = 1 ; j <= lg2 ; j ++ )
		for( int i = 1 ; i <= N ; i ++ )
			f[i][j] = f[f[i][j - 1]][j - 1];
}

int LCA( int u, int v )
{
	if( dep[u] > dep[v] ) balance( u, dep[u] - dep[v] );
	if( dep[v] > dep[u] ) balance( v, dep[v] - dep[u] );
	if( u == v ) return u;
	for( int i = lg2 ; ~ i ; i -- ) if( f[u][i] ^ f[v][i] ) u = f[u][i], v = f[v][i];
	return f[u][0];
}

int getDis( const int u, const int v ) { return ps[u] + ps[v] - 2 * ps[LCA( u, v )]; }

int query( int u, int v, int k )
{
	int lca = LCA( u, v ), st;
	if( k <= dep[u] - dep[lca] + 1 ) st = u, k --;
	else st = v, k = dep[u] + dep[v] - 2 * dep[lca] + 1 - k;
	balance( st, k );
	return st;
}

int main()
{
	char op[10];
	int fr, to, c, T;
	read( T );
	while( T -- )
	{
		read( N ); init();
		for( int i = 1 ; i < N ; i ++ ) read( fr ), read( to ), read( c ), addEdge( fr, to, c ), addEdge( to, fr, c );
		DFS( 1, 0 ), cal();
		while( true )
		{
			scanf( "%s", op );
			if( op[1] == 'O' ) break;
			if( op[1] == 'I' ) read( fr ), read( to ), write( getDis( fr, to ) ), putchar( '\n' );
			if( op[1] == 'T' ) read( fr ), read( to ), read( c ), write( query( fr, to, c ) ), putchar( '\n' );
 		}
	}
	return 0;
}
```

---

