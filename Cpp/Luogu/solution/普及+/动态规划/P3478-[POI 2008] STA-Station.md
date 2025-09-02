# [POI 2008] STA-Station

## 题目描述

给定一个 $n$ 个点的树，请求出一个结点，使得以这个结点为根时，所有结点的深度之和最大。

一个结点的深度之定义为该节点到根的简单路径上边的数量。

## 说明/提示

#### 样例 1 解释

输出 $7$ 和 $8$ 都是正确答案。

#### 数据规模与约定

对于全部的测试点，保证 $1 \leq n \leq 10^6$，$1 \leq u, v \leq n$，给出的是一棵树。

## 样例 #1

### 输入

```
8
1 4
5 6
4 5
6 7
6 8
2 4
3 4
```

### 输出

```
7
```

# 题解

## 作者：nofind (赞：85)

题意：

给出一个N个点的树,找出一个点来,以这个点为根的树时,所有点的深度之和最大。

解析：

首先暴力的做法就是对于每个点都用dfs求一遍,之后比较大小。

但是我们发现实际上对于x我们可以用它的父亲节点推出它的答案。

如图：

以5为根时：

![](https://cdn.luogu.com.cn/upload/pic/60223.png)

以4为根时：
![](https://cdn.luogu.com.cn/upload/pic/60225.png)
观察发现:4的子树(包括自己)深度都减少了1,原根5的子树的深度都增加了1。

也就是说:对于x,它的父亲是y。

f[x]=f[y]-size[x]+n-size[x].

也就是说只要求出一个点,我们就可以用它求出其他点的ans。

这个方法叫二次扫描与换根法。

注:记得开long long

code:
```
#include<bits/stdc++.h>
using namespace std;
const int maxn=1000010;
struct edge
{
	int to,nxt;
}e[maxn<<1];
int n,cnt,id;
int head[maxn];
long long ans;
long long f[maxn],dep[maxn],size[maxn];
inline void add(int u,int v)
{
	e[++cnt].nxt=head[u];
	head[u]=cnt;
	e[cnt].to=v;
}
void dfs1(int x,int fa)
{
	size[x]=1;dep[x]=dep[fa]+1;
	for(int i=head[x];i;i=e[i].nxt)
	{
		int y=e[i].to;
		if(y==fa) continue;
		dfs1(y,x);
		size[x]+=size[y];
	}
}
void dfs2(int x,int fa)
{
	for(int i=head[x];i;i=e[i].nxt)
	{
		int y=e[i].to;
		if(y==fa) continue;
		f[y]=f[x]+n-2*size[y];
		dfs2(y,x);
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}
	dfs1(1,0);
	for(int i=1;i<=n;i++) f[1]+=dep[i];
	dfs2(1,0);
	for(int i=1;i<=n;i++) if(ans<f[i]) ans=f[i],id=i;
	printf("%d",id);
	return 0;
}
```



---

## 作者：览遍千秋 (赞：35)

### 吐槽

我听英文题面说，有多组解的时候，任意输出一个即可。

结果数据是要求输出编号最小的那个。

---

很显然的一个树形动规。

设$size_k$代表$k$的孩子的个数。

设$f_k$代表$k$的结果。

考虑先令$1$为根结点，暴力求出$f_1$，在此过程中可以顺带求出整个$size$数组。

![](https://cdn.luogu.com.cn/upload/pic/26229.png)

**以样例为例**

如图，红圈内的结点个数为$size_4$，在样例中$size_4=7$，绿圈中的结点个数为$size_1$，在样例中$size_1=1$，$size$数组的定义以此类推。

当我们假设$1$号结点所联通的点为根时，在样例中，只能为$4$号结点，此时，我们已经求出$f_1=18$和整个$size$数组。

为了文章可读性起见，在这里列出有作用的：$size_1=1$，$size_4=7$

那么我们的问题就是，如何使用已知的$f_1$和$size$数组，求出$f_4$。

我们发现，当根转移到$4$号结点的时候，$size_4$所包含的全部结点的深度都减$1$了，因此根转移到$4$号结点首先要付出$size_4$的代价。

其次，我们发现，不被$size_4$所包含的其他所有结点的深度都加$1$了，因此根转移到$4$号结点可以获得$n-size_4$的收益。

整理一下：$f_4=f_1+n-2×size_4$

所以在样例中，$f_4=12$，读者可以自行画图检验。

---

推广到所有的情况下，当当前根节点为$x$，将向$k$号结点转移时，就可以计算出$f_k=f_x+n-2×size_k$

求出整个$f$数组的过程需要由递归完成。

---

**注意**

需要开``long long``

在求$f_1$的过程中只能传两个参数，所以$dep$需要用数组记录。

---

代码：

```cpp
#include<iostream>
#include<cstdio>

using namespace std;
#define maxn 2000007
#define maxn1 1000007
long long int x,y,tot,n,Head[maxn],Next[maxn],u[maxn],v[maxn];
long long int size[maxn1],f[maxn1],ans,kkk,dep[maxn1];
bool vis[maxn1],gfg[maxn1];
inline int max(int a,int b)
{
    return a>b?a:b;
}
inline void read(long long &x)
{
    int fh;
    char ch;
    x=0;
    while(ch!='-'&&(ch<'0'||ch>'9')) ch=getchar();
    if(ch=='-'){
        fh=-1;
        ch=getchar();
    }
    else fh=1;
    while(ch>='0'&&ch<='9')
    {
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }
}
inline void add()
{
    u[++tot]=x,v[tot]=y;
    Next[tot]=Head[x],Head[x]=tot;
    u[++tot]=y,v[tot]=x;
    Next[tot]=Head[y],Head[y]=tot;//建边
}
long long int dfs(int x,int root)//求f1和size
{
    int sum=0;
    vis[x]=1;
    size[x]=1;
    for(int i=Head[x];i;i=Next[i])
    {
        if(vis[v[i]]) continue;
        dep[v[i]]=dep[x]+1;
        sum+=dfs(v[i],x);
    }
    size[root]=size[root]+size[x];
    return sum+dep[x];
}
void zy(int x,int root)//转移
{
    gfg[x]=1;
    for(int i=Head[x];i;i=Next[i])
    {
        if(gfg[v[i]]) continue;
        f[v[i]]=f[x]+n-2*size[v[i]];
        if(f[v[i]]>ans)
        {
            ans=f[v[i]];
            kkk=v[i];
        }
        if(f[v[i]]==ans) kkk=min(kkk,v[i]); 
        zy(v[i],x);
    }
}
int main()
{
    read(n);
    for(register int i=1;i<n;i++)
    {
        read(x);
        read(y);
        add();
    }
    f[1]=dfs(1,0);
    gfg[1]=1;
    ans=f[1];
    kkk=1;
    zy(1,0);
    printf("%d\n",kkk);
}
```

---

## 作者：zcysky (赞：28)

如题，这是一题非常明显的树形dp，那么我们就开始根据**树形dp**的思想解决这个问题。题意是找到这棵树的一个点，使得这个点成为根时这棵树的总深度（即每个节点的深度之和）最大。那么首先我们很明显的知道，对于一棵树，任何的节点我们都可以把它看作根，那么我们完全可以假设第一个点为根，并以此求出每个节点的子树大小以及所处深度。这是非常简单的，类似于***树链剖分***的第一步dfs。

现在我们考虑，如果我们转换了这棵树的根，会发生什么情况：

如果我们吧根从x变成y，且St.**x=fa[y]**，即x是y的父亲节点（在第一次dfs的情况下），那么就非常显然了，b的子树节点全都-1，其余的都+1，这就是这一次操作对答案的影响。

但是我们大可以没有必要每次都对子树进行query，那么我们在第一次dfs的时候求出每个点的子树权值就好了，这是非常简单的、、、

代码如下：

```cpp
#include<bits/stdc++.h>
#define N 1000100
using namespace std;
typedef long long ll;
struct Edge{
    int u,v,next;
}G[2\*N];
int d[N];
int tot=0,head[4\*N];ll size[N],n,dw[N],up[N],fa[N];
void addedge(int u,int v){
    G[++tot].u=u;G[tot].v=v;G[tot].next=head[u];head[u]=tot;
    G[++tot].u=v;G[tot].v=u;G[tot].next=head[v];head[v]=tot;
}
void dfs1(int u,int f){
    size[u]=1;
    for(int i=head[u];i;i=G[i].next){
        int v=G[i].v;if(v==f)continue;
        fa[v]=u;d[v]=d[u]+1;
        dfs1(v,u);
        size[u]+=size[v];
        dw[u]+=dw[v]+size[v];
    }
}
void dfs2(int u){
    if(u>1)up[u]=up[fa[u]]+dw[fa[u]]-dw[u]-2\*1LL\*size[u]+n;
    for(int i=head[u];i;i=G[i].next){
        int v=G[i].v;if(v==fa[u])continue;
        dfs2(v);
    }
}
inline int read(){
    int f=1,x=0;char ch;
    do{ch=getchar();if(ch=='-')f=-1;}while(ch<'0'||ch>'9');
    do{x=x\*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
    return f\*x;
}
int main(){
    n=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        addedge(u,v);
    }
    dfs1(1,0);dfs2(1);ll ans=0;
    //for(int i=1;i<=n;i++)printf("%d ",up[i]);
    int num;
    for(int i=1;i<=n;i++){
        if(up[i]+dw[i]>ans)ans=up[i]+dw[i],num=i;
    }
    printf("%d\n",num);
    return 0;
}
```

---

## 作者：Huami360 (赞：16)

#这是一道比较简单的树形DP。

##我们定义f[i]表示以i为根的树的深度和

首先以1为根DFS一遍求出以每个点为根的子树的结点数，用size[i]表示以i为根的子树中结点个数。

再dfs遍历整棵树，这里用u表示当前结点，用v表示每个儿子结点，

##则有 f[v] = f[u] + n - 2 \* size[v]

实际也是很容易想的，

本来是以u为根的树，变成以儿子v为根的树，

那么v的所有结点的深度都会减1，深度和就会减少size[v]，

同样地，所有不在v的子树上的结点的深度都会+1，深度和就会加上n - size[v]，

可以自行画图证明。

另外，楼下没有提到一个细节，对于f，要开long long 存储，否则会WA掉2个点。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <stack>
#include <list>
#define rep(i,m,n) for(int i=m;i<=n;i++)
#define dop(i,m,n) for(int i=m;i>=n;i--)
#define lowbit(x) (x&(-x))
#define ll long long
#define INF 2147483647
#define Open(s) freopen(s".in","r",stdin);freopen(s".out","w",stdout);
#define Close fclose(stdin);fclose(stdout);
using namespace std;

inline int read(){
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;
}
inline void write(int x){
    if(x<0) x=-x,putchar('-');
    if(x>9) write(x/10);
    putchar(x%10+'0');
}

const int maxn=1000010;

struct Edge{
    int next, to;
}e[maxn<<1];

int head[maxn], num, n, m, id;
ll f[maxn], dep[maxn], size[maxn], ans;

inline void Add(int from,int to){
    e[++num].to=to;
    e[num].next=head[from];
    head[from]=num;
    swap(from, to);
    e[++num].to=to;
    e[num].next=head[from];
    head[from]=num;
}

inline void dfs(int u,int fa){
    size[u] = 1;
    dep[u] = dep[fa] + 1;
    for (int i=head[u];i;i=e[i].next) {
        if (e[i].to != fa){
            dfs (e[i].to, u);
            size[u] += size[e[i].to];
        }
    }
}

inline void DFS(int u,int fa){
    for (int i=head[u];i;i=e[i].next) {
        if(e[i].to != fa){
            f[e[i].to] = f[u] - (size[e[i].to]<<1) + n;
            DFS (e[i].to, u);
        }
    }
}
int main(){
    n=read();
    rep(i,2,n) Add(read(), read());
    dfs(1,1);
    rep(i,1,n) f[1]+=dep[i];
    DFS(1,1);
    rep(i,1,n) if(f[i] > ans) ans=f[i], id=i;
    write(id);
    return 0;
}
```

---

## 作者：xcxc82 (赞：14)

# P3478 [POI2008]STA-Station题解

## [原题面](https://www.luogu.com.cn/problem/P3478)

## 知识点
- 换根DP

## 大致题意
给出一个 N 个点的树,找出一个点来,以这个点为根的树时,所有点的深度之和最大

## 分析

换根DP的模板题。

如果您还不会换根DP的话,可以先去看看UltiMadow巨佬的文章:

[【日报#278】[学习笔记]换根dp](https://www.luogu.com.cn/discuss/show/47327),我一开始也是从那里学的qwq

这里我们设

- **$size[i]$为以$1$为根节点时节点$i$的子树大小**

- **$dep[i]$为以$1$为根节点时节点$i$的深度大小**

- **$dp[i]$为以$i$为根节点时深度之和的大小**

很明显,我们可以通过一遍DFS求出以$1$为根节点时的深度之和

如果一个个的去算的话

照这个数据范围,显然会T飞

这个时候就要用到换根DP了

## 换根$DP$优化

![](https://cdn.luogu.com.cn/upload/image_hosting/o5nj1c7o.png)

可以看出,当我们把根节点从1换到3时

对子节点3的贡献由两部分组成

1.**自己子树的贡献(图中的k)**

2.**父亲节点$1$的贡献**



------------

## 如何转移

- 首先是$k$,作为自己子树所产生的贡献肯定要加上

- $dp[u]$为以$u$为根节点时的深度总值,在计算时,要减去$v$的子树所产生的贡献,不然就重复计算了,同时

**在以 $u$为根时,v节点及其子树内的所有节点的深度都增加了$1$**,需要减去

**(图中红色的节点)**

合起来就是$dp[u]-(size[v]+k)$

- 除v子树外的其他节点也一样

**在以$v$为根时，除$v$节点及其子树外的其他节点的深度都增加了$1$**

**(图中蓝色的节点)**

合起来就是$(size[1]-size[v])$

得到转移方程

- $dp[v] = k+(dp[u]-(k+size[v]))+(size[1]-size[v])$





化简一下

- $dp[v] = dp[u]-2size[v]+size[1]$

转移方程推出来了,代码部分就不难实现了,两遍dfs,一次dfs统计子树内的节点对当前节点的贡献
一次dfs换根

贴个代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN  = 100010;
long long dp[MAXN],dep[MAXN],size[MAXN];
int vis[MAXN];
vector <int> son[MAXN];
int n;

void dfs1(int x){
	size[x] = 1;
    vis[x] = 1;
	for(int i=0;i<son[x].size();i++){
		int v = son[x][i];
		if(!vis[v]){
		dep[v] = dep[x] +1;
		dfs1(v);
		size[x]+=size[v];	
		}
			
	}
}
void dfs2(int x){
    vis[x] = 1;
	for(int i=0;i<son[x].size();i++){
		int v = son[x][i];
		if(!vis[v]){
		dp[v] = dp[x] +size[1] - 2*size[v];
		dfs2(v);	
		}
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		son[u].push_back(v);
		son[v].push_back(u);
	}
	dfs1(1);
	
	for(int i=1;i<=n;i++) dp[1]+=dep[i];
	
	memset(vis,0,sizeof(vis));
	dfs2(1);
	long long ans = -0x3f;
	int jd =999;
	for(int i=1;i<=n;i++){
		if(ans < dp[i]) ans = dp[i], jd = i;
	}
	cout<<jd;
}
```




---

## 作者：Always (赞：8)

都是用动规做的大佬qwq

这题其实还有一种比较简单的做法

很明显答案只可能是**树的直径**两端点的其中一个 (⊙v⊙)嗯 就是酱紫!

O(n) (~~我也不知道为什么第9个点一直T?~~)

```
//BY ALways
#pragma GCC optimize (2)
#include<bits/stdc++.h>
#define M 1000005
#define il inline
#define ll long long
#define inf 0x7f7f7f7f
#define rep(i , x , y) for(register ll i = x ; i <= y ; ++i)
#define dor(i , x , y) for(register ll i = x ; i >= y ; --i)
using namespace std ;
ll n , x , y , k , rt , maxd , pos = 1 , d[M] , ans[M] , h[M] , nex[M << 1] , to[M << 1] ;
bool vis[M] ;
il ll re(){
	ll f = 1 , r = 0 ; char ch = getchar() ;
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1 ; ch = getchar();}
	while(ch >= '0' && ch <= '9'){r = r * 10 + ch - '0' ; ch = getchar();}
	return (r *= f) ;
}
il void add(ll u , ll v){
	nex[++k] = h[u] ; to[k] = v ; h[u] = k ;
} 
il void calc(){
	memset(vis , 0 , sizeof vis) ;
	ll A = 0 ;
	rep(i , 1 , n)A += d[i] ;
	if(A > x)x = A , y = rt ;
}
il void dfs(ll u , ll fa , ll dep){
	d[u] = dep ; if(dep > maxd)maxd = dep , pos = u ;
	for(ll i = h[u] ; i ; i = nex[i]){
		ll v = to[i] ;
		if(v == fa || vis[v])continue ; vis[v] = 1 ;
		dfs(v , u , dep + 1) ;
	}
}
int main(){
	n = re() ;
	rep(i , 1 , n - 1){
		x = re() ; y = re() ;
		add(x , y) ; add(y , x) ;
	}
	x = 0 ;
	maxd = 0 ; rt = pos ; dfs(rt , rt , 0) ; calc() ;
	maxd = 0 ; rt = pos ; dfs(rt , rt , 0) ; calc() ;
	maxd = 0 ; rt = pos ; dfs(rt , rt , 0) ; calc() ; 
	printf("%d\n",y) ;
	return 0 ;
}
```

---

## 作者：Su_Zipei (赞：7)

## 题意
给出一个$N$个点的树,找出一个点来,以这个点为根的树时,所有点的深度之和最大
## 分析
看到树，还让求最大，这种可能不是贪心就是树形$DP$，贪心的话树的形状没法判断，果断放弃，那么就只能是$DP$了。

既然它让求深度之和，那么我就直接定义以$i$为根时深度和为$DP_i$，接下来就是怎么转移的问题了。如果我枚举每个点来考虑，那么还要计算它下边的子树和它上边的子树，显然是不好弄，时间复杂度可能在$O(N^2)$左右，虽然时间十秒但也不够用啊，由于$n$大到了1000000，所以这个题还是得用$O(n)$的效率，如果我以某种手段得到了$DP_1$，那么接下来的转移就好说了，每次往下找一个儿子$v$，深度减小了$siz_v$，增加了$n-siz_v$，这样就能用两个$O(n)$来完成这个题，最后在$O(n)$的统计一下答案就好。

$DP$数组要开$long long$
```
#include<cstdio>
using namespace std;
const int N=1e6+10;
struct Edge{
    int to,nxt;
}e[N<<1];
int dep[N],Head[N],len;
void Ins(int a,int b){
    e[++len].to=b;e[len].nxt=Head[a];Head[a]=len;
}
int siz[N];
long long dp[N];
void dfs(int u,int fa){
    siz[u]=1;dp[u]=dep[u];
    for(int i=Head[u];i;i=e[i].nxt){
        int v=e[i].to;
        if(v==fa)continue;
        dep[v]=dep[u]+1;
        dfs(v,u);
        siz[u]+=siz[v];
        dp[u]+=dp[v];
    }
}    
int n;
void calc(int u,int fa){
    for(int i=Head[u];i;i=e[i].nxt){
        int v=e[i].to;
        if(v==fa)continue;
        dp[v]=dp[u]-siz[v]+n-siz[v];
        calc(v,u);
    }
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        int a,b;
        scanf("%d%d",&a,&b);
        Ins(a,b);Ins(b,a);
    }
    dfs(1,0);
    calc(1,0);
    int ans=0;
    for(int i=1;i<=n;i++)
        if(dp[ans]<dp[i])ans=i;
    printf("%d\n",ans);
}
```
## 总结
转移方程题目问什么设什么先，求不出来再考虑换或者辅助一下$DP$.

---

## 作者：密期望 (赞：5)

最近考试考了这道题，但是大家都只有83分，其原因就是有三个毒瘤数据，dfs会直接炸栈，所以全是RE，所以只有改非递归才能过掉那个毒瘤数据。因此我TLE了，用了std::stack和std::queue，缺氧……

下面是我的考场代码（因为懒，不想重写）
```
#include<cstdio>
#include<stack>
#include<queue>
using std::stack;
using std::queue;
typedef long long ll;
typedef long double ld;
const int N=1000010;
void file(const char *str){
	char in[100],out[100];
	sprintf(in,"%s.in",str),sprintf(out,"%s.out",str);
	freopen(in,"r",stdin),freopen(out,"w",stdout);
}
struct L{
	int to,next;
};
L l[N<<1];
int head[N];
int lcount;
void add(int from,int to){
	l[++lcount].to=to;
	l[lcount].next=head[from];
	head[from]=lcount;
}
int root=1;
int size[N];
int f[N];
ll dis[N];
int n;
ll ans;
void dfs(){
	stack<int>s_i,s_now;
	s_now.push(root);
	s_i.push(head[root]);
	size[root]=1;
	while(!s_now.empty()){
		int &now=s_now.top(),&i=s_i.top();
		if(i){
			if(l[i].to!=f[now]){
				size[l[i].to]=1;
				s_i.push(head[l[i].to]);
				s_now.push(l[i].to);
				f[l[i].to]=now;
			}
			i=l[i].next;
			continue;
		}
		size[f[now]]+=size[now];
		dis[f[now]]+=dis[now]+size[now];
		s_now.pop();
		s_i.pop();
	}
}
void bfs(){
	queue<int>q;
	q.push(root);
	int now;
	while(!q.empty()){
		now=q.front();
		q.pop();
		if(ans<dis[now]){
			ans=dis[now];
		}
		for(int i=head[now];i;i=l[i].next){
			if(l[i].to!=f[now]){
				dis[l[i].to]=dis[now]+n-(size[l[i].to]<<1);
				q.push(l[i].to);
			}
		}
	}
}
void input(){
	scanf("%d",&n);
	int p1,p2;
	for(int i=1;i<n;i++){
		scanf("%d%d",&p1,&p2);
		add(p1,p2);
		add(p2,p1);
	}
}
void begin(){
}
void solve(){
	dfs();
	bfs();
}
void output(){
	for(int i=1;i<=n;i++){
		if(dis[i]==ans){
			printf("%d",i);
			return;
		}
	}
}
void test(){
	input();
	begin();
	solve();
	output();
}
void all(){
	file("sta");
	test();
}
int main(){
	all();
	return 0;
}

```
洛谷上时间是卡着过的(最慢点800+ms)，时间并不是很优，但是不会被1e6的链卡掉。

---

## 作者：mot1ve (赞：3)

经典的树形dp，运用到了换根法，我详细讲一下状态转移方程的推导.

首先考虑暴力，跑n遍堆优化dijkstra，时间复杂度O(n^2*log(n)) 能得50分.

正解是树形dp.

此题用到了换根法,先明确几个东西.

**n为总节点个数**

**size[x]表示x的子树的节点个数（包括自己）**

**f[x]表示以x为根节点时的其他节点到根节点距离和**

对于任意一个非根节点x，他的父亲节点为y，状态转移方程如下：

**f[x] = f[y] + (n-size[x]) - size[x];**

如何理解这个状态转移方程呢?

****1.对于不在x的子树中的节点，他们到x的距离等于他们到y的距离 +（n-size[x]）****

这个应该不难理解，每个不在x的子树中的节点，到x的距离比到y的距离多了1，一共

有(n-size[x])个节点不在x的子树中.

**2对于在x的子树中的节点，他们到x的距离等于他们到y的距离-size[x]**

这个也很好理解，每个在x的子树中的节点，到x的距离比到y的距离少了1，一共有

size[x]个节点在x的子树中.

合并，可得状态转移方程.

有了状态转移方程，代码就好写了.

1.首先选任意一个点当做根节点（我一般选1）递归求出每个子树的节点个数（包括

自己）顺便计算出其他节点到根节点的距离和.

2.再来一遍dfs进行状态转移.

不过还有一个细节要注意，在我的代码中，根节点的到根节点距离不能设为0，因为这

是个无向图，我在判断有没有往回跑的时候用的是判断v有没有被赋过值，如果设根节

点到根节点距离为0，那么会导致误判.


所以我设根节点到根节点的距离为1，其他节点到根节点的距离相应也多了1，最后减

去节点个数就行了.

~~****别忘开long long！！！****~~
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
long long size[1000010],dis[1000010],f[1000010];//f数组表示以i为根节点

的距离和,dis数组只是计算每一个点到一开始假设的根的距离，之后换根的时候就没

用了
int head[1000010];
int idx,n;
long long num;
struct node{
	int nxt,to;
}edge[2000010];
void add(int u,int v)
{
	edge[++idx].nxt=head[u];
	edge[idx].to=v;
	head[u]=idx;
}
void dfs1(int now)//递归求出每个子树的节点个数顺便计算出其他节点到根节点的距离和 
{
	size[now]=1;
	for(int i=head[now];i;i=edge[i].nxt)
	{
		int v=edge[i].to;
		if(dis[v]) continue;
		dis[v]=dis[now]+1;
		dfs1(v);
		size[now]+=size[v];
	}
}
void dfs2(int now,int fath)
{
	if(now!=1)//如果是根节点的话不能进行状态转移
	f[now]=f[fath]-size[now]+n-size[now];
	for(int i=head[now];i;i=edge[i].nxt)
	{
		int v=edge[i].to;
		if(v==fath) continue;
		dfs2(v,now);
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n-1;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	dis[1]=1;
	dfs1(1);
	for(int i=1;i<=n;i++)
	{
		num+=d[i];
	}
	num-=n;
	f[1]=num;
	dfs2(1,0);
	long long ans=0,temp;
	for(int i=1;i<=n;i++)
	{
		if(f[i]>ans)
		{
			ans=f[i];
			temp=i;
		}
	}
	printf("%lld",temp);
	return 0;
}

---

## 作者：renhr2002 (赞：3)

首先很容易发现这道题是树形DP，涉及到换根操作。就来 NaOH 一发吧。

一个比较流行的做法是：

1. 先进行一次 DFS，求出每个点的深度和子树大小；
2. 计算出 $1$ 号节点的答案；
3. 再进行一次DFS，递推求出每个点的答案。

但是，仔细分析就可以发现：我们根本不需要求出每个点的深度。原因如下：

通过简单证明可以发现：如果定义根节点的深度为 $1$，则所有点的深度之和等于所有点的子树大小之和。我们可以从贡献的角度考虑：

对于一个深度为 $k$ 的节点，它会给从它到根节点路径上的所有点子树大小提供 $1$ 的贡献，而这条路径上的点有 $k$ 个，证毕。

另外，本题并没有要求求出深度之和最大值是多少，只需要求出在哪个节点为根时取到。这样，我们可以把 $1$ 号点的 DP 值设为 $0$，再进行第二次 DFS（这条在我的解题方法中并未使用）。

这样，我们就可以只定义这些变量和数组（名称与下面的代码中相同）：

- $n$：整个树的点数；
- $siz[x]$:节点 $x$ 的子树大小；
- $dp[x]$：节点 $x$ 的DP值。

第一次 DFS 时，我们可以求出每个节点的子树大小。

第二次 DFS 时，求出每个节点的 DP 值。假设现在要把根从节点 $x$ 换到它的子节点 $t$，则 $t$ 的子树中所有节点深度都会减 $1$，其它节点都会加 $1$。这样，递推方法为：

$dp[t]=dp[x]-siz[t]+(n-siz[t])$；

即 $dp[t]=dp[x]+n-2siz[t]$。

代码如下（C++11）：

```cpp
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
using namespace std;
#define maxn 1024000
#define ll long long
char str;
int n;
struct edge
{
	int to;
	int nxt;
}nd[2*maxn];
int head[maxn],cnt;
ll siz[maxn],dp[maxn];
template<class X> inline void read(X &x)
{
	x=0;
	X f=1;
	while(!isdigit(str))
	{
		if(str=='-')
		{
			f=-1;
		}
		str=getchar();
	}
	while(isdigit(str))
	{
		x*=10;
		x+=str-'0';
		str=getchar();
	}
	x*=f;
	return;
}
void init()
{
	memset(head,-1,sizeof(head));
	cnt=1;
	return;
}
void add(int x,int y)
{
	nd[cnt].to=y;
	nd[cnt].nxt=head[x];
	head[x]=cnt++;
	return;
}
void dfs1(int x,int fa)
{
	siz[x]=1;
	for(int i=head[x];i!=-1;i=nd[i].nxt)
	{
		int t=nd[i].to;
		if(t!=fa)
		{
			dfs1(t,x);
			siz[x]+=siz[t];
		}
	}
	return;
}
void dfs2(int x,int fa)
{
	for(int i=head[x];i!=-1;i=nd[i].nxt)
	{
		int t=nd[i].to;
		if(t!=fa)
		{
			dp[t]=dp[x]+(ll)n-2*siz[t];
			dfs2(t,x);
		}
	}
	return;
}
int main()
{
	init();
	read(n);
	for(int i=1;i<n;i++)
	{
		int a,b;
		read(a),read(b);
		add(a,b);
		add(b,a);
	}
	dfs1(1,0);
	for(int i=1;i<=n;i++)
	{
		dp[1]+=siz[i];
	}
	dfs2(1,0);
	int ans=1;
	ll mx=dp[1];
	for(int i=2;i<=n;i++)
	{
		if(dp[i]>mx)
		{
			mx=dp[i];
			ans=i;
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：VioletIsMyLove (赞：1)

思考清楚之后就会特别easy,考虑1挡根节点时，计算出深度 $Dep[x]$ 和以 $x$ 为根的子树所包含的节点个数 $Num[x]$ 。

接下来计算出以 $1$ 位根时的所有深度，考虑让它的儿子挡根节点的变化，换句话来说就是在上一次计算的基础之上来计算所有节点的深度和
以 $x$ 为子树的所有节点 $Num[x]$ 个深度 $-1$ ,$N-Num[x]$ 这些节点的深度都 $+1$ 

Code:

```cpp
#include<bits/stdc++.h>
#define maxn 1000005
#define LL long long
using namespace std;
int N,Ans,cnt,Num[maxn],lnk[maxn],nxt[2*maxn],son[2*maxn],Dep[maxn];
LL F[maxn];
int read(){
    int ret=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
    while (ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
    return ret*f;
}
void add_e(int x,int y){son[++cnt]=y;nxt[cnt]=lnk[x];lnk[x]=cnt;}
void Dfs(int x,int fa){
    Num[x]=1;Dep[x]=Dep[fa]+1;
    for (int j=lnk[x];j;j=nxt[j])
      if (son[j]!=fa) Dfs(son[j],x),Num[x]+=Num[son[j]];
}
void DFS(int x,int fa){
    for (int j=lnk[x];j;j=nxt[j])
      if(son[j]!=fa){
      	F[son[j]]=F[x] - Num[son[j]] + N-Num[son[j]];//改为当前儿子节点为根，那么儿子这课子树所有节点深度-1，其余节点深度+1 
        DFS (son[j],x);
    }
}
int main(){
    N=read();
    for (int i=2;i<=N;i++){
    	int x=read(),y=read();
    	add_e(x,y),add_e(y,x);
    }
    Dfs(1,0);
    for (int i=1;i<=N;i++) F[1]+=Dep[i];
    DFS(1,0);
    LL Max=0;
    for (int i=1;i<=N;i++)
      if (F[i]>Max) Max=F[Ans=i];
    printf("%d\n",Ans);
    return 0;
}
```


---

## 作者：伟大的王夫子 (赞：1)

如果想要更好的体验，可以到[我的博客](https://www.luogu.org/blog/I-AK-IOI/)去看


本题是一个很显然的树形dp

暴力很好打，复杂度$O(n^2)$,显然会超时

先读入这棵树，可以用$vector$存边，比较方便

首先我们以$1$为根， 求出每个节点的深度，以及子树的大小。

设$f[i]$为以i为根，最大深度之和。我们现在用换根法求出每个$f[i]$

容易得出状态转移方程$\forall \, \,y \in son(x) \,\,\,\,\,f[y] = f[x] + n - 2 \times size[x]$

其中$size[x]$为$x$的子树大小，$son(x)$为$x$的儿子集合

我们简单证明一下

如图，当根从$1$换到$2$时

![](https://cdn.luogu.com.cn/upload/image_hosting/u1pvf2zx.png?x-oss-process=image)

所以当根从$x$换到儿子$y$时，深度减小的有$size[y]$个，增加得有$n-size[y]$个

$\therefore f[y] = f[x] + (n - size[y]) - size[y] = f[x] + n - 2 \times size[y]$

接着上代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
long long f[1000010], d[1000010], size[1000010];
bool v[1000010];
vector<int> e[1000010];
void dfs1(int x) {
	v[x] = 1;
	size[x] = 1;
	for (register int i = 0; i < e[x].size(); ++i) {
		int y = e[x][i];
		if (v[y]) continue;
		dfs1(y);
		v[y] = 1;
		d[y] = d[x] + 1;
		size[x] += size[y];
	}
}
void dfs2(int x) {
	v[x] = 1;
	for (register int i = 0; i < e[x].size(); ++i) {
		int y = e[x][i];
		if (v[y]) continue;
		v[y] = 1;
		f[y] = f[x] + n - 2 * size[y];
		dfs2(y);
	}
}
int main() {
	//freopen("data.out", "r", stdin);
	cin >> n;
	for (register int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs1(1);
	//cout <<  size[1] << ' ' << n << endl;
	memset(v, 0, sizeof v);
	for (register int i = 1; i <= n; ++i)
		f[1] += d[i];
	
	dfs2(1);
	long long ans = -1e9, pos;
	for (register int i = 1; i <= n; ++i)
		if (f[i] > ans) pos = i, ans = f[i];
	cout << pos;
}  
```
时间复杂度为$O(n)$,一个线性算法

请注意：必须开long long！

---

## 作者：te5555 (赞：1)

考虑从每个点转移到他的父亲节点$fa$上，则当前的距离和$sum$变化可以通过对当前树种每个点的贡献统计,考虑$u$的儿子节点,那么
$u$的子树与他自己的贡献$+1$,对于子树的补集,也就是剩余的节点,贡献$-1$.
转移方程:  
$$
dp[fa] = dp[u] +2siz[u] - n $$

那么考虑从上往下转移，移项即可得到
$$
dp[u] = dp[fa]+n-2siz[u]
$$
开始通过一次dfs预处理即可
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int res=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')res=res*10+ch-48,ch=getchar();
	return res*f;
}
const int maxn = 1000060;
int n;
int head[maxn];
int siz[maxn],cnt;
struct edge{
	int to,nxt;
}e[maxn<<1];
inline void add(int from,int to){
	e[++cnt].to=to;
	e[cnt].nxt=head[from];
	head[from]=cnt;
}
int f[maxn],dep[maxn];
void dfs(int u,int fa){	
	siz[u]=1;
	if(u!=1)dep[u]=dep[fa]+1;
	f[1]+=dep[u];
	for(register int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa)continue;
		dfs(v,u);	
		siz[u] += siz[v];
	}
}
int minu;
void dp(int u,int fa){
	if(f[minu]<=f[u])minu=u;
	for(register int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa)continue;
		f[v]=f[u]+n-siz[v]*2;
		dp(v,u);
	}
}
signed main(){
	n=read();
	f[0]=0;
	for(register int i=1,x,y;i<n;i++)
		x=read(),y=read(),add(x,y),add(y,x);
	dfs(1,0);
	dp(1,0);
	cout<<minu;
	return 0;
}
```


---

## 作者：horz (赞：1)

### 换根dp

1.一般都没有指定根，刚开始随便选一个根（1号点工具人）。

2.两次$dfs$，一次从工具人开始预处理一些东西，第二次（也是从工具人开始）换根。

3.多用于：只要确定某一个点是什么东西的时候，答案就基本确定。枚举每一个点复杂度不能承受，父亲的答案可以让儿子加以利用。

4.答案的统计合并可分子树内，子树外，子树内的一般在第一次$dfs$的过程中就得出了答案，子树外的通过换根，找父亲答案关系来得到。

#### 题意

给定一个$n$ 个点的树，请求出一个结点，使得以这个结点为根时，所有结点的深度之和最大。

#### 分析

假设$v$是$u$的子节点，

定义$dp[i]$表示以$i$为节点为根的深度和，

$dp[v] = dp[u] + (n - sz[v]) - sz[v]$。

```c++
#include <bits/stdc++.h>
using namespace std;
#define mem(a,b) memset(a,b,sizeof(a))
#define pii pair<int,int>
#define int long long
#define ll __int128_t
const int inf = 0x3f3f3f3f;
const int maxn = 1001110;
const int M = 1e9+7;
int n,m,k,ok;

int sz[maxn],d[maxn];

vector<int> v[maxn];

void dfs1(int u,int pre)		//预处理出每个节点的深度（用来求1节点的深度和），子树大小
{
    sz[u] = 1;
    d[u] = d[pre]+1;
    for(auto i : v[u])
    {   
        if(i == pre) continue;
        dfs1(i,u);
        sz[u] += sz[i];
    }
}

int dp[maxn];			//以i为根的数的节点深度和

void dfs2(int u,int pre)
{
    for(auto i : v[u])
    {
        if(i == pre) continue;
        dp[i] = dp[u] + (n - sz[i]) - sz[i]; //它的非子树节点所以深度+1，子树节点深度-1
        dfs2(i,u);
    }
}

signed main()
{
#ifdef ONLINE_JUDGE
#else
    freopen("data.in", "r", stdin);
#endif
    cin>>n;
    for(int i = 1,x,y; i < n; i++) 
    {
        cin>>x>>y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    dfs1(1,0);
    for(int i = 1; i <= n; i++) 		//求出一开始的深度和
    {
        dp[1] += sz[i];
    }
    dfs2(1,0);				//换根求解
    int root = 1,mx = 0;
    for(int i = 1; i <= n; i++) 
    {
        if(mx < dp[i])
        {
            mx = dp[i];
            root = i;
        }
    }
    cout<<root<<endl;
    return 0;
}
```



---

## 作者：LlLlCc (赞：1)

一道非常经典的**树形DP**，题意简介明了,大致为：对于给定的一颗大小为N的**无根树**，选出一个根，使**所有子节点的深度和**最大。

1. **暴力**的想法很简单，枚举每一个节点作为**根节点**，依次便利所有子节点，求出**深度和**。

   时间复杂度为N方，显然是过不去的。（题目没给出N的大小，实测**N<=1000000**)

2. 暴力过不去，自然就要想优化了。我们思考一下，各节点作为根时的深度和是否存在什么关联？

   设：以节点x最为根时，深度和为f[x]。
   
   当我们枚举到x节点的子节点son[x]作为根节点时，会发现，所有son[x]的子节点深度较x来说，都-1了。同样，x除了son[x]之外所有的子节点深度都+1了。
   
   我们只要一遍Dfs求出所有节点的深度和子树大小，再从上往下更新所有的f[x]，挑大的即可。
   
   转移方程相信大家都会推（具体见代码）：


AC代码：

```
#include<bits/stdc++.h>
#define maxn 1000005
#define ll long long
using namespace std;
int fa[maxn],S[maxn],Dep[maxn],x,y,n,lnk[maxn],nxt[maxn*2],son[maxn*2],tot,cnt;
ll f[maxn],Ans;
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-f;ch=getchar();}
	while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
inline void add(int x,int y){nxt[++tot]=lnk[x];lnk[x]=tot;son[tot]=y;}
inline void Dfs(int x,int FA){
	S[x]=1,f[x]=Dep[x]=Dep[FA]+1;
	for (int i=lnk[x];i;i=nxt[i])
	  if (son[i]!=FA){
	  	fa[son[i]]=x;Dfs(son[i],x);
		S[x]+=S[son[i]];f[x]+=f[son[i]];
	  }
}
inline void Dfs_Ans(int x){
	for (int i=lnk[x];i;i=nxt[i])
	  if (son[i]!=fa[x]){
	  	f[son[i]]=f[x]-2*S[son[i]]+n;
	  	if (f[son[i]]>Ans) cnt=son[i],Ans=f[son[i]];
	  	Dfs_Ans(son[i]);
	  }
}
int main(){
	n=read();
	for (int i=1;i<n;i++) x=read(),y=read(),add(x,y),add(y,x);
	Dfs(1,0);Ans=f[1];cnt=1;
	memset(f,0,sizeof f);
	f[1]=Ans;Dfs_Ans(1);
	printf("%d",cnt);
	return 0;
}
```


---

## 作者：feng_chengjie (赞：1)

###这是一道经典的树形DP

首先，如果确定了某个点为根节点，那么我们可以很容易地通过dfs求出$MAX_Sumdeep$，现在我们考虑如何不通过n次dfs，分别求出其他点为根节点的 $MAX_Sumdeep$?画画图你就会发现，从一个点x往他的下一级子节点v转移，就可以使得v子树上的所有点深度-1，让其他的点深度+1，因此有$f[v]=f[x]+(n-nson[v])-nson[v]$==》$f[v]=f[x]+n-2*nson[v]$，于是在预处理完f[x]后，直接可以通过一遍dfs求其他的$MAX_Sumdeep$啦。


参考代码：




```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=1e6+10;
struct point
{
    int to,nxt;
}edge[maxn<<1];
int n,head[maxn],tot=0,S[maxn],fath[maxn],deep[maxn];
long long f[maxn],ans;
inline void add(int u,int v)
{
    tot++;
    edge[tot].to=v;
    edge[tot].nxt=head[u];
    head[u]=tot;
}
inline void dfs(int x,int fa,int dep)
{
    deep[x]=dep;
    S[x]=1;
    for(int i=head[x];i;i=edge[i].nxt)
    {
        int v=edge[i].to;
        if(v!=fa)
        {
            dfs(v,x,dep+1);
            S[x]+=S[v];
        }
    }
}
inline void find(int x)
{
    for(int i=head[x];i;i=edge[i].nxt)
    {
        int v=edge[i].to;
        if(deep[v]>deep[x])
        {
            f[v]=f[x]+n-2*S[v];
            find(v);            
        }
    }
}
int main()
{
    cin>>n;
    for(int i=1;i<=n-1;i++)
    {
        int a,b;
        cin>>a>>b;
        add(a,b);
        add(b,a);
    }
    dfs(1,0,1);
    for(int i=1;i<=n;i++)    
        f[1]+=deep[i];
    find(1);
    int mark=0;
    for(int i=1;i<=n;i++)
    {
        if(ans<f[i])
        {
            ans=f[i];
            mark=i;
        }
    }    
    cout<<mark;
    return 0;
}
```

---

## 作者：EEchoyukii (赞：0)

换根dp

设 $f[i]$ 为 $i$ 为根，所有结点的深度之和。

考虑先求一遍 $f[rt]$，$rt$ 初始值为 $1$，表示 一开始的根。

并且令 $rt=1$ 时，以 $i$ 为根的子树大小为 $siz[i]$

比如说对于树上两点 $u=4,v=2$，$rt=1$ 时 $fa[u]=v$，那么此时假设已经求出 $f[v]$ 考虑如何推出 $f[u]$

![image.png](https://i.loli.net/2020/08/02/ZGIibd1lweOYFv4.png)
![image.png](https://i.loli.net/2020/08/02/zQcRaxiv3l74urZ.png)

左边数字为深度。

观察红色部分，可以发现 $rt$ 由 $v->u$时，每个节点深度 $-1$，总答案就是减 $siz[4]=siz[u]$

观察蓝色部分，可以发现 $rt$ 由 $v->u$时，每个节点深度 $+1$，总答案也就是 $siz[1]-siz[2]=n-siz[u]$

所以当 $rt$ 由 $v->u$ 时，$f[v]=f[u]+siz[u]+n-siz[u]=f[y]+n-siz[u]$

方程就搞出来了。

$code$

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define int long long 
inline int read(){
	register int x=0,f=0,ch=getchar();
	while('0'>ch||ch>'9')f^=ch=='-',ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^'0'),ch=getchar();
	return f?-x:x;
}
const int MAX=1000005;
int n,u,v;
struct E{
	int e,next;
}e[MAX<<1];
int head[MAX],cnt=1,f[MAX],ans=-1;
inline void add(int u,int v){
	e[cnt]=(E){v,head[u]};head[u]=cnt++; 
}
int siz[MAX],dep[MAX];
void dfs(int x,int fa){
	siz[x]=1;dep[x]=dep[fa]+1;
	f[1]+=dep[x];
	for(register int i=head[x];i;i=e[i].next){
		if(e[i].e!=fa){
			dfs(e[i].e,x);
			siz[x]+=siz[e[i].e];
		}
	}
}
void dfs1(int x,int fa){
	for(register int i=head[x];i;i=e[i].next){
		if(e[i].e!=fa){
			f[e[i].e]=f[x]+n-2*siz[e[i].e];
			dfs1(e[i].e,x); 
		}
	}
}
signed main(){
	n=read();
	for(register int i=1;i<n;++i){
		u=read(),v=read();
		add(u,v);add(v,u);
	}
	dep[0]=-1;
	dfs(1,0);
	dfs1(1,0);
	for(register int i=1;i<=n;++i){
		if(f[ans]<f[i])ans=i;
	}
	printf("%d\n",ans);
	return 0;
}

```



---

## 作者：HoshiuZ (赞：0)

### 思路

显然可以用二次扫描与换根法解决。

定义 $dp[root]$ 表示以 $root$ 为根的子树上的所有点的深度之和。

先以节点 $1$ 为根，预处理每个点 $i$ 的深度 $depth[i]$ 以及 以点 $i$ 为根的子树的节点个数 $cnt[i]$。

于是我们易得
$$
dp[root]=detph[root]+\sum_{v\in son(root)}dp[v]
$$
定义 $df[root]$ 表示以 $root$ 为根的**整个树**上所有点的深度之和。

对于每个点 $root$ 的子节点 $v$，可以将这整个树拆分成两部分来看：

1. 节点 $v$ 上面的部分。
2. 节点 $v$ 以及节点 $v$ 下面的部分。

第二部分在以 $v$ 为根时的深度之和是很好求的，显然为
$$
dp[v]-cnt[v]\times depth[v]
$$
第一部分就得思考思考了。不过仔细推推的话，可以推出为
$$
df[root]-\big(dp[v]-cnt[v]\times detph[root]\big)+n-cnt[v]
$$
思路可以从以 $root$ 为根的**整个树**，减去以 $v$ 为根的**子树**，剩余的部分上进行考虑。

那么
$$
df[v]= dp[v]-cnt[v]\times depth[v]+df[root]-\big(dp[v]-cnt[v]\times depth[root]\big)+n-cnt[v]
$$
$$
= cnt[v]\times\big(depth[root]-depth[v]\big)+df[root]+n-cnt[v]
$$
$$
= df[root]+n-2\times cnt[v]
$$

据此转移即可。

答案 $ans$ 即为
$$
\max_{i=1}^N df[ans]
$$
但注意多解时输出最小的节点。

### 代码

```cpp
#include<bits/stdc++.h>
#define N 1000010
#define ll long long 

using namespace std;

int n,tot=0,head[N];
ll depth[N],dp[N],cnt[N],df[N],maxn=0,ans;
struct graph{
	int v,next;
}edge[N<<1];

void add(int u,int v) {
	edge[++tot].v=v;
	edge[tot].next=head[u];
	head[u]=tot;
}

void dfs_first(int root,int f) {
	cnt[root]=1;
	depth[root]=depth[f]+1;
	dp[root]=depth[root];
	for(int i=head[root];i;i=edge[i].next) {
		int v=edge[i].v;
		if(v==f) continue;
		dfs_first(v,root);
		cnt[root]+=cnt[v];
		dp[root]+=dp[v];
	}
}

void dfs_second(int root,int f) {
	if(df[root]>maxn||(df[root]==maxn&&root<ans)) maxn=df[root],ans=root;
	for(int i=head[root];i;i=edge[i].next) {
		int v=edge[i].v;
		if(v==f) continue;
		df[v]=df[root]+n-2*cnt[v];
		dfs_second(v,root);
	}
}

int main() {
	scanf("%d",&n);
	for(int i=1;i<n;i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	
	dfs_first(1,1);
	df[1]=dp[1];
	dfs_second(1,1);
	
	printf("%lld\n",ans);
	
	return 0;
}
```



---

## 作者：L_M_ (赞：0)

这是道蛮简单的树型dp呀，为什么会是蓝题啊orz
~~但是我这个wa了四次的人为什么有脸说这个~~

题目给的是无根树，那我们可以随便选择一个点（比如1号）作为根

这样 我们可以得到 以1为根的子结点个数son_size[1]
以1为根的子结点的深度和dep_sum[1]

接下来，我们考虑如何从1号点转移其他点

考虑i的儿子j,如果我们以j为根，那么j的所有子结点（显然包括j）的深度应该+1，i号点的其他子结点（显然包括i）的深度应该-1

所以，我们可以得出转移：

j是i的儿子，那么： f[j]=f[i]+n-2*son_size[i]

好，那么这道题的大致思路就ok了，细节上的话，就是数组记得开long long，最好写一个快读，不然有几率t掉第九个点，然后dfs和dp的过程中，最好通过传入父结点作为参数的方式搜索 如果用vis数组，有可能会忘掉memset这个操作，这样就GG了

下面是代码quq
```
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1e6+10;
typedef long long ll;
inline int read()
{
  int ans=0,op=0;
  char ch=getchar();
  while(ch<'0'||ch>'9')
    {
      if(ch=='-') op=-1;
      ch=getchar();
    }
  while(ch>='0'&&ch<='9')
    {
      ans*=10;
      ans+=ch-'0';
      ch=getchar();
    }
  return ans*op;
}
int n;
ll dep[maxn];
ll dep_sum[maxn];
ll son_size[maxn];
ll f[maxn];
struct edge
{
    int to,next;
}e[maxn*2];
int fir[maxn],alloc;
void adde(int u,int v)
{
    e[++alloc].next=fir[u];
    fir[u]=alloc;
    e[alloc].to=v;
}
void dfs1(int u,int fa)
{
    son_size[u]=1;
    for(int i=fir[u];i;i=e[i].next)
    {
        int v=e[i].to;
        if(v==fa) continue;
        vis[v]=1;
        dep[v]=dep[u]+1;
        dfs1(v,u);
        son_size[u]+=son_size[v];
    }
    return;
}
void dfs2(int u,int fa)
{
    for(int i=fir[u];i;i=e[i].next)
    {
        int v=e[i].to;
        if(v==fa) continue;
        vis[v]=1;
        dfs2(v,u);
        dep_sum[u]+=dep_sum[v];
    }
}
void dp(int u,int fa)
{
    for(int i=fir[u];i;i=e[i].next)
    {
        int v=e[i].to;
        if(v==fa) continue;
        vis[v]=1;
        f[v]=max(f[v],f[u]+n-2*son_size[v]);
        dp(v,u);
    }
}
int main()
{
    n=read();
    for(int i=1;i<n;i++)
    {
        int u=read(),v=read();
        adde(u,v);
        adde(v,u);
    }
    dep[1]=1;
    dfs1(1,0);
    for(int i=1;i<=n;i++) dep_sum[i]=dep[i];
    dfs2(1,0);
    f[1]=dep_sum[1];
    dp(1,0);
    ll ans=0;
    ll maxm=0;
     for(int i=1;i<=n;i++) 
        if(f[i]>maxm)
            ans=i,maxm=f[i];
    printf("%lld",ans);
}
```

---

