# 「yyOI R1」youyou 的军训

## 题目背景

在 youyou 的班上，身高可能是一个敏感的话题。

## 题目描述

youyou 的班上一共有 $n$ 位同学，$m$ 对朋友，第 $i$ 对朋友关系对于身高有一个敏感值 $k_i$，敏感值可能会改变。

我们定义两位同学如果互为**朋友**，那么必然存在某对关系，将两位同学**直接**相连。

我们定义两位同学如果互为**好友**，那么必然存在直接或间接的关系，将两位同学相连。

例如存在关系 $(1,2)$ 和 $(2,3)$，那么，$1$ 与 $2$ 是朋友，但 $1$ 与 $3$ 就是好友。

现在，马上就要军训了，同学们要去领军训的服装，如果一位同学领到了尺码为 $p$ 的服装，所有同学会与朋友关系敏感值小于 $p$ 的朋友断交。即对于所有的朋友关系，若其敏感值小于 $p$，那么该朋友关系就会断开。不过在下一位同学领到服装时，所有**之前**的断开的朋友关系会恢复。

由于军训领服装是一个复杂的过程，而 youyou 对此十分感兴趣，所以给出 $q$ 次操作，且一共有三种操作:

- 操作 $1$，形如 `1 x`，表示有一位同学领到尺码为 $x$ 的服装。

- 操作 $2$，形如 `2 x`，表示询问第 $x$ 位同学还有多少位好友（包括自己）。

- 操作 $3$，形如 `3 x y`，表示第 $x$ 对朋友的敏感值变为 $y$，特别地，**敏感值的相对大小不会变化$^*$**（详情见下方），同时原来已经断开的关系不会恢复。

**注意：好友跟朋友是两个概念，朋友一定是好友，但好友不一定是朋友。**

$^*$：相对大小不会变化，指对于当前所有的敏感值而言，修改后的敏感值与原来的敏感值**排名相同**。

例如，若原来所有对朋友之间敏感值是 $\{1,2,3,5,6\}$，$3$ 的排名为 $3$，因此 $3$ 只能修改为 $3,4$ 中的一个，这样才能保证排名不变，即相对大小位置不会变换。

## 说明/提示


## 样例解释 #1

如图所示，这是初始的关系图。

![](https://cdn.luogu.com.cn/upload/image_hosting/68hzm5mr.png)

第一次操作为：有一位同学领到尺码为 $26963$ 的服装，这样，图中所有的边都会断开。

下一次操作：第三对朋友即边 $(2,3)$ 的权变为 $40$。

下一次操作：询问同学 $4$ 的好友数量，因为没有任何存在的边，因此答案为 $1$。
 
## 数据范围
| 测试点编号 | $n$ | $q$ | 特殊性质 |
| :-----------: | :-----------: | :-----------: | :-----------: |
| $1,2$ | $\le 10$ | $\le 4 \times 10^5$ | 无 |
| $3$ | $\le 10^3$ | $\le 10^3$ | 无 |
| $4$ | $\le 10^5$ | $\le 4 \times 10^5$ | 没有操作 $3$ |
| $5,6$ | $\le 10^5$ | $\le 10^3$ | 无 |
| $7$ | $\le 10^5$ | $\le 4 \times 10^5$ | 没有操作 $1$ |
| $8,9,10$ | $\le 4 \times 10^5$ | $\le 4 \times 10^5$ | 无 |

用 $c_i$ 表示询问中同学领到服装尺码的大小，$e_i$ 表示修改后敏感值的大小。

对于 $100\%$ 的数据，$1 \le n,m,q,x_i,y_i \le 4  \times  10^5$，$1 \le k_i,c_i,e_i \le 1 \times 10^9$，$m\le \min\{\frac{n(n-1)}{2},4 \times 10^5\}$。

同时数据保证在任何时刻，所有对朋友关系之间的敏感值**互不相同**。

**请注意常数因子对时间和空间产生的影响。**

## 样例 #1

### 输入

```
4 3 3
1 2 156
1 4 42
2 3 0
1 26963
3 3 40
2 4```

### 输出

```
1```

## 样例 #2

### 输入

```
7 6 7
1 2 292
1 3 274
1 4 221
1 5 156
3 4 42
3 6 40
1 30
3 4 50
2 6
3 3 250
3 1 298
1 280
2 1```

### 输出

```
6
2```

# 题解

## 作者：AllenKING_RED (赞：6)

## Description

给定一个图，每次询问问将边权小于 $q$ 的边断开并询问一个点所在连通块的大小，边权可变。

## Solution

我们首先考虑暴力怎么做：

可以暴力维护询问值和边权，每次询问时暴力遍历连通块。

时间复杂度 $O(nq)$，期望得分 $30$ 分。

- 考虑测试点 $4$：

由于边权不会修改，可以考虑将询问离线。

按照边权从大到小排序，将每次询问时操作 `1` 的值也从大到小排序，每次询问时把边权大于当前操作 `1` 值的边依次加入，这样可以保证不经过边权不合法的边，再用并查集维护连通块的大小即可。

时间复杂度 $O(m \log n)$，加上其他组部分分，期望得分 $40$ 分。

- 考虑优化：

由于最大生成树的性质，所以不在最大生成树中的边对答案没有影响。

看到特殊性质，**边权的相对位置不变**，我们可以按照最大生成树的顺序建立虚点，用点权表示边权，再将虚点和边的两端连边。

此时，由于最大生成树的性质，深度浅的点的点权一定小于等于深度深的点，而修改时，我们可以直接 $O(1)$ 修改每条边对应虚点的点权。

我们可以从当前点倍增跳到自己的祖宗节点（复杂度为 $O(\log n)$），直到点权小于上次操作 `1` 的值，这时，所有该点子树中的点都一定是可以达到的，而子树外的点，必然要经过点权不合法的点，也就是经过此时断开的边才能达到。

由于新数中所有叶子节点都代表着原图中的点，所以可以得出结论：此时该点子树中叶子节点个数就是答案的值。

时间复杂度 $O(q \log n)$，期望得分 $100$ 分。

~~其实出题人自己也不知道剩下的特殊性质怎么写。~~

---

## 作者：鲤鱼江 (赞：5)

先放一个帖子：[link](https://www.luogu.com.cn/discuss/863721)。

这题有一个细节，后面再说。

首先我们发现这个题面十分抽象，所以先提取关键信息，发现没有 $3$ 操作的问题可以转化为：走边权不超过 $k$ 的边能走到多少点，其实也就是瓶颈路问题。

考虑 Kruskal 重构树，则每次能走到的点对应到重构树上刚好就是一个子树，因为 LCA 肯定是瓶颈，既然 LCA 都能走，子树内一定畅通无阻。

那这个方法对于有 $3$ 操作的该题是否有启发呢？答案是显然的。~~不然我为啥讲~~。

发现权值的相对关系始终不变，所以树的形态也一定不会变，所以每次修改边权就直接修改 LCA 的点权就行了，不过要提前判断这条边是否在 Kruskal 重构树上，否则只有 $90$ 分。

然后就牵扯到上面的帖子了，题面中说了修改边权不会是断掉的边是不会重连的，所以有些题解的代码有点问题。

具体实现 $3$ 操作的方式有很多，我在代码中选择使用 vector 进行懒删除，每次操作 $1$ 时集体下放修改。

还有就是这道题你不管操作 $3$ 也有 $90$ 分，数据很水。

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
#define fi first
#define endl '\n'
#define sec second
#define mk make_pair
#define cin Fastio :: cin
#define cout Fastio :: cout

const int B=20;
const int N=1e6+10;
typedef pair<int,int> pii;
struct edge{
	int x,y,z;
	edge(int x=0,int y=0,int z=0):x(x),y(y),z(z){;}
	bool operator <(const edge &t)const{return z>t.z;}
}a[N],b[N];
int siz[N],f[N][B+1],fa[N],ls[N],rs[N],tot,n,m,q,w[N],las,dep[N];
int root(int x){return x==fa[x]?x:fa[x]=root(fa[x]);}
vector < pii > Q;

void Kruskal(){
	sort(a+1,a+1+m);
	for(int i=1;i<=m;++i){
		int x=root(a[i].x);
		int y=root(a[i].y);
		if(x==y) continue;
		w[++tot]=a[i].z;
		fa[x]=fa[y]=tot;
		ls[tot]=x;rs[tot]=y;
	}
}

void dfs(int x,int y){
	f[x][0]=y;dep[x]=dep[y]+1;
	for(int i=1;i<=B;++i) f[x][i]=f[f[x][i-1]][i-1];
	if(x<=n) siz[x]=1;
	else {
		dfs(ls[x],x);dfs(rs[x],x);
		siz[x]=siz[ls[x]]+siz[rs[x]];
	}
}

inline int LCA(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=B;~i;--i) if(dep[f[x][i]]>=dep[y]) x=f[x][i];
	if(x==y) return x;
	for(int i=B;~i;--i) if(f[x][i]!=f[y][i]){x=f[x][i];y=f[y][i];}
	return f[x][0];
} 

inline int jump(int x){
	for(int i=B;~i;--i) if(f[x][i]&&w[f[x][i]]>=las) x=f[x][i];
	return siz[x];
}

int main(){
	cin>>n>>m>>q;tot=n;
	for(int i=1;i<=(n<<1);++i) fa[i]=i;
	for(int i=1;i<=m;++i) cin>>a[i].x>>a[i].y>>a[i].z;
	for(int i=1;i<=m;++i) b[i]=a[i];Kruskal();
	for(int i=tot;i;--i) if(!siz[i]) dfs(i,0);
	for(int i=1,opt,x,y;i<=q;++i){
		cin>>opt>>x;
		if(opt==1){for(auto i:Q) w[i.fi]=i.sec;Q.clear();las=x;}
		else if(opt==2) cout<<jump(x)<<endl;
		else {
			cin>>y;
			int lca=LCA(b[x].x,b[x].y);
			if(w[lca]!=b[x].z) continue;
			Q.emplace_back(lca,b[x].z=y);
		}
	}
	return 0;
}
//这条边有可能本来就没影响。输。 
```

---

## 作者：Madsome (赞：5)

给一篇不用倍增的题解。
## 题意
给定一个无向图，每次**在原图基础上**删去所有边权**小于 $q$** 的边，查询一个点所在联通块的大小。边权带修，但相对大小不变。
## 题解
可以发现，删完边以后最多只有 $n$ 种状态，考虑将其预处理。题目保证：所有对朋友关系之间的敏感值**互不相同**，所以可以看作每次从小到大将一条边删去，维护每个点的连通块大小。考虑其逆过程，非常巧啊，这不就是 Kruskal 算法生成**最大生成树**吗！而且题目保证：修改后的敏感值与原来的敏感值**排名相同**，所以最大生成树的**形态不会改变**。

定义 $siz_i$ 表示 $i$ 所在的连通块大小，$fa_i$ 表示 $i$ 所在的连生成树的根节点。为了方便维护连通块的大小，只需要维护 $siz_{fa_i}$ 的大小即可。每次合并时，只需修改根节点的 $siz$ 即可。

但这样还不够，空间复杂度不能接受，用可持久化数组就太过麻烦了。考虑直接将询问离线，在每次 $1$ 操作时，将当前状态要删的边数下有哪几个节点需要查询记录下来即可。对于每个 $3$ 操作，可以发现一个点的答案，**只与当前要删几条边有关**，所以直接在原数组修改即可。

时间复杂度 $\mathcal O(n \log n)$，瓶颈在排序以及二分。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int Size=(1<<20)+1;
char buf[Size],*p1=buf,*p2=buf;
char buffer[Size];
int op1=-1;
const int op2=Size-1;
inline char readchar(){
	if(p1!=p2) {
		return *p1++;
	}
	return p1==(p2=(p1=buf)+fread(buf,1,Size-1,stdin))?EOF:*p1++;
}
inline void flush(){
	fwrite(buffer,1,op1+1,stdout),op1=-1;
}
inline void writechar(const char &x) {
	if(op1==op2) flush();
	buffer[++op1]=x;
}
#ifndef ONLINE_JUDGE
#define readchar getchar
#endif
#define putchar writechar
inline int read() {
	int s=1,c=readchar(),x=0;
	while(c<=32) {
		c=readchar();
	}
	if(c=='-') {
		s=-1,c=readchar();
	}
	for(; ('0'<=c && c<='9'); c=readchar()) {
		x=x*10+c-'0';
	}
	return x*s;
}
inline void print(long long x) {
	if(x<0) {
		writechar('-'),x=-x;
	}
	char s[25];
	int n=0;
	while(x||!n) {
		s[n++]='0'+x%10,x/=10;
	}
	while(n--) {
		writechar(s[n]);
	}
}
const int N=4e5+5;
int n,m,T,i,j,rk[N],ans[N],cnt,opt,x,y,l,r,mid,len,fa[N],siz[N];
struct ed{
	int x,y,k,id;
}a[N];
struct nd{
   int id,val;
};
vector<nd>g[N];
inline bool cmp(ed x,ed y){
	return x.k>y.k;
}
inline int find(int x){
	if(x==fa[x])return x;
	return fa[x]=find(fa[x]);
}
signed main() {
    n=read();m=read();T=read();
    for(i=1;i<=m;i++){
		a[i].x=read();a[i].y=read();
		a[i].k=read();a[i].id=i;
	}
    sort(a+1,a+m+1,cmp);
	for(i=1;i<=m;i++)
	   rk[a[i].id]=i;
	int cur=m;
	for(i=1;i<=T;i++){
		opt=read();x=read();
		if(opt==1){
			l=1;r=m;
			int ans=0;
			while(l<=r){//二分出要保留几条边
				mid=l+r>>1;
				if(a[mid].k>=x){
					l=mid+1;
                    ans=mid;
				}
				else r=mid-1;
			}
			cur=ans;
		}
		else if(opt==2){
			nd tmp;
			tmp.id=++len;tmp.val=x;
            g[cur].push_back(tmp);
		}
        else a[rk[x]].k=read();
	}
    for(i=1;i<=n;i++)fa[i]=i,rk[i]=siz[i]=1;//注意，这里的rk数组用于并查集按秩合并，为了省空间用了相同的数组
	for(auto i:g[0])ans[i.id]=1;
    for(i=1;i<=m;i++){
		int fx=find(a[i].x),fy=find(a[i].y);
        if(fx!=fy){//按秩合并
		   	 if(rk[fx]<=rk[fy])fa[fy]=fx,siz[fx]+=siz[fy];
		    else fa[fy]=fx,siz[fy]+=siz[fx];
		    if(rk[fx]==rk[fy]&&fx!=fy)rk[fy]++;
        }
		for(auto j:g[i])
		   ans[j.id]=siz[find(j.val)];
	} 
	for(i=1;i<=len;i++)
	  print(ans[i]),putchar('\n');
	flush();
	return 0;
}
```

---

## 作者：SegTree (赞：3)

### 题意

一个 $n$ 点 $m$ 边的无向图，边有边权，有一个值 $w$。三种操作：

+ `1 x` 表示 $w\gets x$。

+ `2 x` 询问保留所有边权 $\ge q$ 的边后 $x$ 所在连通块大小。

+ `3 x y` 修改第 $x$ 条边边权为 $y$。

保证修改前后所有边权的排名不变。

### 题解

不难想到建出一颗 Kruskal 重构树（就是最大生成树在 Kruskal 的时候将合并两个连通块形成的新连通块与这两个连通块连边建成一颗树）。为了方便，我们将这个新连通块的点权设为连接着两个连通块的这条边的边权。

查询在建出的树上倍增跳到最高的边权 $\ge x$ 的结点，那么这棵子树内的都能到达，则答案为这颗子树的叶子结点数。

你发现修改边权排名不变就保证了 Kruskal 重构树上对应的边编号不变，所以修改能直接 $\mathcal{O}(1)$ 修改对应的点权即可。

查询 $\mathcal{O}(\log n)$ 倍增就做完了。

[代码](https://www.luogu.com.cn/paste/4ijyx6ux)。

---

## 作者：naroto2022 (赞：2)

# P9638 题解

### 题面

[原题传送门](https://www.luogu.com.cn/problem/P9638)

### 题意

给定一个 $n$ 个点 $m$ 条边的图以及 $q$ 个操作，有以下 $3$ 种情况：

- `1 x`，恢复以前所有的边，并删去 $\leqslant x$ 的所有边。
- `2 x`，询问 $x$ 包括自己的能连到的点的个数。
- `3 x w`，把第 $x$ 条边的边权改为 $w$，并且不改变这条边权值的相对排名。

### 思路

看到这道题，想到操作 `1` 的删去 $\leqslant x$ 的所有边，即留下所有 $>x$ 的所有边，而且每次改变权值都不改变相对排名，这不仅让人想到瓶颈路，于是想到 kruskal 重构树。

这道题留下所有 $>x$ 的所有边则是用 kruskal 重构树跑出最大生成树的重构树。

则到点 $x$ 的简单路径上最大边权的最小值 $>val$ 的所有点 $y$ 均在 kruskal 重构树上的某一棵子树内，且恰好为该子树的所有叶子节点。

于是这一题就可以做了，只要在重构树上统计每个点的子树的叶子节点个数就可以了，对于询问则是可以选择倍增，找到深度最浅的 $\leqslant tmp$ 的点（$tmp$ 为上一次 `1` 操作的 $x$）。

### 后记

1. 题目没有保证图是一个连通块，所以需要按照数据有多个连通块来处理。
2. 由于是在下一个操作 `1` 才能恢复上一个操作 `1` 断开的边，所以应该用一个队列把修改操作 `3` 存下来，然后每一个操作 `1` 的之后执行与之前那一个操作 `1` 之间的所有操作 `3`。不过呢，这题的数据并没有针对这个来卡，我也很失望，具体的可以参照这个[帖子](https://www.luogu.com.cn/discuss/863721)。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
//#define gc getchar
#define gc()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#define ll long long
#define pll pair<ll,ll>
using namespace std;
const int MN=1e6+5;
ll n,m,Q,tot,head[MN],idx,f[MN],fa[MN][20],val[MN],tmp,son[MN],to[MN];
queue<pll> q;
struct edge1{ll to,nxt;}e[MN];
struct edge2{ll u,v,w,id;}E[MN];
char buf[1<<23],*p1=buf,*p2=buf;
void write(ll n){if(n<0){putchar('-');write(-n);return;}if(n>9)write(n/10);putchar(n%10+'0');}
ll read(){ll x=0,f=1;char ch=gc();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=gc();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=gc();}return x*f;}
bool cmp(edge2 a, edge2 b){return a.w>b.w;}
void add(ll u, ll v){e[++tot].nxt=head[u];head[u]=tot;e[tot].to=v;}
ll find(ll x){return x==f[x]?x:f[x]=find(f[x]);}
void kruskal(){
    for(int i=1; i<=2*n; i++) f[i]=i;
    sort(E+1,E+1+m,cmp);
    for(int i=1; i<=m; i++){
        ll u=find(E[i].u),v=find(E[i].v);
        if(u==v) continue;
        val[++idx]=E[i].w;f[u]=f[v]=fa[u][0]=fa[v][0]=to[E[i].id]=idx;
        add(idx,u);add(idx,v);
        if(idx-n==n-1) break;
    }
}
void dfs(ll u){
    for(int i=1; i<20; i++) fa[u][i]=fa[fa[u][i-1]][i-1];
    if(!head[u]){son[u]=1;return;}
    for(int i=head[u]; i; i=e[i].nxt){
        ll v=e[i].to;
        dfs(v);
        son[u]+=son[v];
    }
}
ll query(ll x){
    for(int i=19; ~i; i--) if(fa[x][i]&&val[fa[x][i]]>=tmp) x=fa[x][i];
    return son[x];
}
int main(){
    //ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    idx=n=read();m=read();Q=read();
    for(int i=1; i<=m; i++) E[i].u=read(),E[i].v=read(),E[i].w=read(),E[i].id=i;
    kruskal();
    for(int i=idx; i; i--) if(!son[i]) dfs(i);
    while(Q--){
        ll op=read();
        if(op==1){
            tmp=read();
            while(!q.empty()){
                pll top=q.front();q.pop();
                val[to[top.first]]=top.second;
            }
        }
        if(op==2){ll x=read();write(query(x));putchar('\n');}
        if(op==3){ll x=read(),w=read();q.push({x,w});}
    }
    return 0;
}//250518
```

---

## 作者：Magus (赞：1)

## 题意

给定一个无向带权图，$q$ 次查询，有以下三种操作：

+ `1 x`，删去所有边权 $\leq x$ 的边，并恢复之前因为该操作而断开的所有边。
+ `2 x`，查询节点 $x$ 能到达的包括自己的点的数量。
+ `3 x y`，将第 $x$ 条边的边权修改为 $y$，该边在图中排名不变。

## 题解

记录下 $1$ 操作的 $x$，记为 $res$，因为进行完 $1$ 操作之后恢复之前因为该操作而断开的所有边，所以实际上 $2$ 操作查询的就是“节点 $x$ 只走边权大于等于 $res$ 的边能到达多少个点”，这就是 Kruskal 重构树板子呀！因为 $3$ 操作修改完后修改的边在图中排名不变，所以不影响重构树形状，直接上板子就可以了。

```cpp
#include<bits/stdc++.h>
#define FastIO ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define int long long
#define I using
#define AK namespace
#define CSPS2025 std
I AK CSPS2025;
const int maxn=8e5+10,maxm=1e3+10,mod=998244353;
int n,m,q,x,y,k,u,v,w,op,tot,res,id[maxn],arr[maxn],head[maxn],f[maxn][21],fa[maxn],sum[maxn],ans[maxn];
struct node
{
	int to,nxt,val,id;
}g[maxn];
struct edge
{
	int to,nxt;
}e[maxn];
void add(int u,int v)
{
	e[++tot].to=v;
	e[tot].nxt=head[u];
	head[u]=tot;	
}
int cmp(node x,node y)
{
	return x.val>y.val;
}
int getfa(int x)
{
	if(fa[x]==x)
	{
		return x;
	}
	return fa[x]=getfa(fa[x]);
}
void merge(int x,int y)
{
	if(x==y)
	{
		return;
	}
	fa[getfa(x)]=getfa(y);
}
void dfs(int u)
{
	for(int i=1;i<=20;i++)
	{
		f[u][i]=f[f[u][i-1]][i-1];
	}
	if(u<=n)
	{
		sum[u]=1;
		return;
	}
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(sum[v])
		{
			continue;
		}
		f[v][0]=u;
		dfs(v);
		sum[u]+=sum[v];
	}
}
int lca(int u)
{
	for(int i=20;i>=0;i--)
	{
		if(f[u][i] and ans[f[u][i]]>=res)
		{
			u=f[u][i];
		}
	}
	return u;
}
void rebuild()
{
	int cnt=n;
	sort(g+1,g+m+1,cmp);
	for(int i=1;i<=m;i++)
	{
		int U=getfa(g[i].to),V=getfa(g[i].nxt);
		if(U!=V)
		{
			fa[U]=fa[V]=++cnt;
			add(cnt,U);add(cnt,V);
			ans[cnt]=g[i].val;
			id[g[i].id]=cnt;
		}
	}
	for(int i=cnt;i;i--)
	{
		if(!sum[i])
		{
			dfs(i);
		}
	}
}
signed main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0); 
	cin>>n>>m>>q;
	for(int i=1;i<=n*2;i++)
	{
		fa[i]=i;
	}
	for(int i=1;i<=m;i++)
	{
		cin>>g[i].to>>g[i].nxt>>g[i].val;
		g[i].id=i;
	}
	rebuild();
	while(q--)
	{
		cin>>op;
		if(op==1)
		{
			cin>>res;
		}
		else if(op==2)
		{
			cin>>u;
			cout<<sum[lca(u)]<<"\n";
		}
		else if(op==3)
		{
			cin>>u>>v;
			ans[id[u]]=v;
		}
	}
	return 0;
}
```

---

## 作者：xlhl (赞：0)

## 题目大意
有一个各边边权相对大小不变，但具体值会改变的图，每次断掉边权小于 $x$ 的边，断边操作互不影响，询问一个点所在连通块的大小。

这道题题面有点长，还有几个容易理解错的点：  
1. 每次只会有一个断边操作影响图，只有在某个同学领到衣服时之前的断边操作才会撤销。
2. 改变边权并不能恢复当前被断掉的边，比如原本朋友关系的敏感值为 $10$，这对关系在某人领到 $11$ 码衣服断掉之后，把关系敏感值改为 $12$，这对关系还是不能恢复。
## 解法
如果有三位同学互为朋友，甲和乙关系敏感值为 $10$，乙和丙关系敏感值为 $20$，甲和丙关系敏感值为 $30$，那实际上甲和乙的关系就是没有用的，太容易被断掉了，而其实不在最大生成树上的边都没什么用，我们可以尝试建 Kruskal 重构树。

按最大生成树规则建重构树，因为题目说边权相对大小不变，所以树形态是不会变的。此时到点 $x$ 的路径上的边的最小权值的最大值不小于某值的点都会在某个子树内，倍增找到子树的根，只要提前数好子树内非虚点的个数就行。

边权的改变处理起来也不难了，如果要改的边不会包含在最大生成树内，对重构树没有影响。否则找到边对应的虚点，之后修改点的点权即可。但如果直接修改点权，可能改变某些之前实际上被断掉的好友关系，影响对好友关系的判断，所以要到某人又领到衣服后再修改。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e5+10;
int n,m,q,tot,op,x,y,ct,gs;
struct node{
	int x,y,z;
}a[N],cpy[N];
bool cmp(node q,node p){
	return q.z>p.z;
}
vector<int>v[N*2];
int fa[N*2],val[N*2],f[N*2][22],dep[N*2],siz[N*2],cx[N],cy[N];//记得开两倍空间!
int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
void Kruskal(){
	for(int i=1;i<=2*n;i++) fa[i]=i;
	sort(a+1,a+1+m,cmp);
	for(int i=1;i<=m;i++){
		int ax=find(a[i].x),ay=find(a[i].y);
		if(ax!=ay){
			v[++tot].push_back(ax);
			v[tot].push_back(ay);
			fa[ax]=tot,fa[ay]=tot;
			val[tot]=a[i].z;
		}
	}
}
void dfs(int u,int fa){
	f[u][0]=fa,dep[u]=dep[fa]+1,siz[u]=(u<=n);
	for(int i=0;i<=19;i++)
	  f[u][i+1]=f[f[u][i]][i];
	for(int to:v[u]) dfs(to,u),siz[u]+=siz[to];
}
int lca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=20;i>=0;i--){
		if(dep[f[x][i]]>=dep[y]) x=f[x][i];
		if(x==y) return x;
	}
	for(int i=20;i>=0;i--)
	  if(f[x][i]!=f[y][i])
	    x=f[x][i],y=f[y][i];
	return f[x][0];
}
int solve(int x){
	for(int i=20;i>=0;i--)
		if(f[x][i]&&val[f[x][i]]>=ct) x=f[x][i];
	return siz[x];
}
int main(){
	cin>>n>>m>>q,tot=n;
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].z),cpy[i]=a[i];
	Kruskal();
	for(int i=1;i<2*n;i++) if(find(i)==i) dfs(i,0);
	while(q--){
		scanf("%d%d",&op,&x);
		if(op==1){
			for(int i=1;i<=gs;i++)
			  val[cx[i]]=cy[i];
			ct=x,gs=0;
		}
		if(op==2) printf("%d\n",solve(x));
		if(op==3){
			scanf("%d",&y);
			int t=lca(cpy[x].x,cpy[x].y);
			if(val[t]==cpy[x].z)
			  cx[++gs]=t,cy[gs]=y,cpy[x].z=y;//先改掉边权，树上的点点权要留到领衣服后改
		}
	}
	return 0;
}
```

---

