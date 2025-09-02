# Leha and another game about graph

## 题目描述

Leha plays a computer game, where is on each level is given a connected graph with $ n $ vertices and $ m $ edges. Graph can contain multiple edges, but can not contain self loops. Each vertex has an integer $ d_{i} $ , which can be equal to $ 0 $ , $ 1 $ or $ -1 $ . To pass the level, he needs to find a «good» subset of edges of the graph or say, that it doesn't exist. Subset is called «good», if by by leaving only edges from this subset in the original graph, we obtain the following: for every vertex i, $ d_{i} $ = - 1 or it's degree modulo 2 is equal to $ d_{i} $ . Leha wants to pass the game as soon as possible and ask you to help him. In case of multiple correct answers, print any of them.

## 说明/提示

In the first sample we have single vertex without edges. It's degree is 0 and we can not get 1.

## 样例 #1

### 输入

```
1 0
1
```

### 输出

```
-1
```

## 样例 #2

### 输入

```
4 5
0 0 0 -1
1 2
2 3
3 4
1 4
2 4
```

### 输出

```
0
```

## 样例 #3

### 输入

```
2 1
1 1
1 2
```

### 输出

```
1
1
```

## 样例 #4

### 输入

```
3 3
0 -1 1
1 2
2 3
1 3
```

### 输出

```
1
2
```

# 题解

## 作者：doge233 (赞：9)

	    翻译自英文题解
	    我们通过给定的图一定联通的条件来解决这个模型。
	    我们证明如果这个子图符合要求，必须有-1的点或者所有的0,1点的度数的和为偶数。我们显然发现如果没有-1且所有点的度数为奇数一定没有解。那么我们给出所有01点和为偶数的构造解的方法。 
	    如果有-1的点我们可以调整成偶数。
	    然后我们求出随便一颗生成树，且随便找个点作为根，接着我们的问题就会变得简单很多。
	接着我们一个接着一个处理其他的点（dfs），我们用cur表示当前节点。
    1. $d_cur = 0 $ 这时我们忽略这个点和他和父亲之间的边。
    2. $d_cur = 1 $ 这时将父亲变为相反的点，并忽略当前点。
    
可以结合代码理解
```
#include <bits/stdc++.h>
using namespace std;

const int N = 3e5+10;
int n,m,cnt;
int d[N],h[N];
int ans[N<<1],tot;
bool vis[N];
struct edge{
	int to,next;
}e[N<<1];
inline void add(int from,int to){
	e[++cnt]=(edge){to,h[from]};h[from]=cnt;
}
bool dfs(int x){
	vis[x]=1;
//	cerr<<x<<endl;
	bool res=d[x];
	for(int i=h[x];i;i=e[i].next){
		int v=e[i].to;
		if(vis[v]) continue;
		if(dfs(v))
			ans[++tot]=(i+1)/2,res^=1;//cerr<< x << " " << v<< endl ;
	}
	if(d[x]==-1) res=0;
//	cerr<<x<< " " <<res<<endl;
	return res;
}

int main(){
	int be=-1,ok=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) {
		scanf("%d",d+i);
		if(d[i]==-1) be=i;
		else ok^=d[i];
	}
	int u,v;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&u,&v);
		add(u,v);add(v,u);
	}
	if(be==-1&&ok) {puts("-1");return  0 ;}
	if(be==-1) be=1;
	dfs(be);
	printf("%d\n",tot);
	sort(ans+1,ans+tot+1);
	for(int i=1;i<=tot;i++)
		printf("%d\n",ans[i]);
	return 0;
}
```
    

---

## 作者：lemonfor (赞：7)

  这道题其实并不是非常难，感觉评成黑的有点过分了惹，题意不难理解，主要是想法非常难得到QAQ
  
 ----------------------
 
 
 因为一张图里只能有偶数个奇点，所以当数据给你的奇点个数为奇数个时，需要把一个为 $-1$的点变成 $1$，假如题目没有给你 $-1$ ，那你便可以自己还给题目一个大大的 $-1$ ,跑路；

假如数据没有那么良心，那便把其他的无用的 $-1$全部改成 $0$，这个时候，我们可以选择bfs 

关于bfs有一个非常棒的方法，从一个奇点开始，然后把它所到的第一个奇点的路径全部 $Xor 1$ ,但是那样复杂度不对，过不了 $CF$的毒瘤数据.....

bfs不行，那就跑dfs咯。

~~通过生成一棵树来降低复杂度，因为没有边权，所以只要用并查集就可以了。~~

dfs遍历每一个节点，回溯时记录这个节点的所有子孙节点包括它自己的奇点个数，如果是偶数个，说明这底下可以构成图，则这个节点上方的边不需要计入答案，否则就说明这个节点以下无法构成一张图，节点上方的边就计入答案喽。代码很丑，行了啦！
```
#include<cstdio>
#define _ 0
#define N 600050
#define M 600050
#define int long long
#define drep(k ,l ,r) for(register int k = (r) ; k >= (l) ; -- k)
#define rep(k ,l ,r) for(register int k = l ; k <= r ; ++ k)
#define re register
#define INF 0x3f3f3f3f
using namespace std;
int n ,m ,tot ,head[N] ,point[N] ,odd ,u ,v;
int fa[N] ,tree[N] ,ansn;
bool vis[N] ,ans[N];
struct edge {
    int next ,to ,num;
} e[M];
int read() {
    char cc = getchar() ; int cn = 0 ,flus = 1;
    while(cc < '0' || cc > '9') {if(cc == '-') flus = - flus ; cc = getchar() ; }\
    while(cc >= '0' && cc <= '9') cn = cn * 10 + cc - '0' ,cc = getchar() ; 
    return flus * cn;
}
void add(int u ,int v ,int wi) {
    e[++tot] = (edge){head[u] , v ,wi} ,head[u] = tot;
}
int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]) ; }
bool dfs(int u) { 
    if(vis[u])return 0; 
    int res = point[u]; vis[u] = 1;
    for(int i = head[u] ; i ; i = e[i].next) if(dfs(e[i].to)) ++ansn ,ans[e[i].num] = 1,res ^= 1;
    vis[u] = 0;
    return res;
}
void print() {
    printf("%lld%c" ,ansn ,10);
    rep(i ,1 ,n) if(ans[i]) printf("%lld ",i);
}
signed main() {
    n = read() ,m = read();
    rep(i ,1 ,n) {
        point[i] = read();
        if(point[i] == 1) odd ^= 1;
    }
    rep(i ,1 ,m) fa[i] = i ;
    rep(i ,1 ,m) {
        u = read() ,v = read();
        if(find(u) != find(v)) fa[fa[u]] = fa[v] ,add(u ,v ,i) ,add(v ,u ,i);
    }
    rep(i ,1 ,n) if(point[i]==-1) {
        if(odd)odd = 0 ,point[i] = 1;
        else point[i] = 0;
    }
    if(odd) puts("-1");
    else dfs(1) ,print();
    return ~~(0^_^0);
}
```

---

## 作者：Zero_Legend (赞：6)

# 题解

## 思路

### part1:判断无解

一条边会使总度数加2，所以总度数一定是偶数。

故总度数为奇数的情况是无解的，含有-1点和总度数为偶数的情况是一定有解的。

### part2:构造方法

注意到题面上给出图一定是联通的，考虑生成树。

可以随便建一棵生成树，并在生成树上进行构造。

根据树的性质：如果对当前节点进行操作，是不会影响到子树的。

因此在保证子树所有点满足限制的时候，我们根据当前点现在的度数来决定要不要选择连他和父节点的这条边，这样就不会影响子树的答案。

这样就可以用dfs来解决了！因为是从下往上构造，所以操作是在遍历子树之后进行的。

也许有的读者会有疑问：这样构造回溯到根节点时一定是有解的吗？

可以证明，这样构造一定有解：

考虑根节点时，其子树上的点已全部满足限制（即除根结点以外的所有点皆满足限制），若此时根节点度数的奇偶性与限制不同，则总度数为奇数，与总度数为偶数的前提相矛盾，故根节点度数的奇偶性一定满足限制。

在选取根节点时有一个小技巧：当有-1的点时，令一个-1点成为根节点，其他的-1点成为0点即可。这样便可以不用考虑总度数为偶数的限制了。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
int d[N],ans[N];
bool vis[N];
struct node{
  int nex,to;
}t[2*N];
int head[N],idx=0;
int n,m,u,v;
int root=-1,sum=0;
int cnt=0;

void add(int u,int v){
  t[++idx].to=v;
  t[idx].nex=head[u];
  head[u]=idx;
}

int dfs(int now){//dfs返回的值代表当前点是否已经满足限制
  int flag=d[now];
  vis[now]=true;
  for(int i=head[now];i;i=t[i].nex){
    int y=t[i].to;
    if(vis[y]) continue;
    if(dfs(y)){//若子节点不满足限制，则需要连边
      ans[++cnt]=(i+1)/2;//连的是双向边
      flag=(1-flag);//flag记录当前点是否满足限制
    }
  }
  if(d[now]==-1) flag=0;//如果是-1就不用考虑限制了
  return flag;
}

int main(){
  cin>>n>>m;
  for(int i=1;i<=n;i++){
    cin>>d[i];
    if(d[i]==-1) root=i;
    else sum+=d[i];
  }
  for(int i=1;i<=m;i++){
    cin>>u>>v;
    add(u,v);add(v,u);
  }
  if(root==-1&&sum%2==1){cout<<-1;return 0;}//判无解
  if(root==-1) root=1;//前面提到的小trick
  int fuck=dfs(root);
  cout<<cnt<<endl;
  for(int i=1;i<=cnt;i++) cout<<ans[i]<<endl;
  return 0;
}

```



---

## 作者：万弘 (赞：3)

考虑选择一条边的影响：将两个点的度数的奇偶性分别取反。

也就是$(1,1)->(0,0),(1,0)->(0,1),(0,0)->(1,1)$

也就是度数和的变化只能是偶数。那么可推得，若有奇数个点入度需要为奇数且没有-1的点，则无法构造；否则，选一个-1把他变成1，问题规约到有偶数个入度需要为奇数的点的情况。

问题转化为，给一张图，图上有偶数个点是1,将1的点配对，并且无重边。  
这是一个经典的树上问题。假设现在在考虑$u$
- 若$u$有偶数个儿子是1，将这些1两两配对即可
- 若$u$有奇数个儿子是1，选出尽量多个两两配对，剩下的一个和$u$配对，并反转$u$的状态。

由于根（$1$）的子树中有偶数个1，所以必然存在方案。  
因此，对于有偶数个1的连通图，也必然存在方案。一个方便的做法是，选出一个生成树，在生成树上构造即可。  
时间复杂度$\mathcal O(n+m\log m),m\log m$是因为我用了map判重。
```cpp
/**********/
#define MAXN 300011
std::map<pll,bool>p;
struct edge
{
    ll v,dex,nxt;
}e[MAXN<<1|1];
ll cnt=0,last[MAXN];
void adde(ll u,ll v,ll dex)
{
    e[++cnt].v=v,e[cnt].dex=dex;
    e[cnt].nxt=last[u],last[u]=cnt;
}
ll fa[MAXN],d[MAXN],all=0,change;
bool vis[MAXN];
void dfs1(ll u)
{
    vis[u]=1;
    if(d[u]==-1)change=u;
    all+=(d[u]==1);
    for(ll i=last[u];i;i=e[i].nxt)
    {
        ll v=e[i].v;
        if(vis[v])continue;
        fa[v]=u;
        dfs1(v);
    }
}
std::vector<ll>ans;
void dfs2(ll u)
{
    for(ll i=last[u];i;i=e[i].nxt)
    {
        ll v=e[i].v;
        if(fa[v]==u)
        {
            dfs2(v);
            if(d[v]==1){ans.push_back(e[i].dex),d[u]^=1;}
        }
    }
}
int main()
{
    ll n=read(),m=read();
    for(ll i=1;i<=n;++i)d[i]=read();
    for(ll i=1;i<=m;++i)
    {
        ll u=read(),v=read();
        if(u>v)std::swap(u,v);
        if(p[pll(u,v)])continue;
        p[pll(u,v)]=1;
        adde(u,v,i),adde(v,u,i);
    }
    dfs1(1);
    if(all&1)
    {
        if(!change){puts("-1");return 0;}
        d[change]=1;
    }
    for(ll i=1;i<=n;++i)
        if(d[i]==-1)d[i]=0;
    dfs2(1);
    printf("%u\n",ans.size());
    for(auto x:ans)printf("%lld\n",x);
    return 0;
}
```

---

## 作者：TMLY114514 (赞：2)

## **CF840B Leha and another game about graph 题解**
感觉很多题解对于构造的思路讲的不够详细，因此补充一下自己的理解。

------------

首先考虑如何判断是否有解。对于一个无向图，每条边对度数的贡献为 $2$，所以如果不存在度数没有限制的点，所有点的度数和为奇数就是无解的。

存在度数没有限制的点时，可以考虑如果一条边的一个端点原先不满足自己的限制，在添加这条边时，这个点就会被满足，而它的另一个端点则可能会变得不被满足。持续加边，不被满足的点就沿着这条路径一直传播下去，直到碰到另一个原先也没有被满足的点。因为题目保证图联通，所以所有不被满足的点都可以沿着路径找到度数没有限制的点~~来平账~~，所以一定有解。

------------

接下来考虑如何构造答案。不难发现，对于一个环，从一个点出发开始加边直到回到它自己，这个过程是没有意义的。于是我们断开所有环，这时整个图就变成了一棵树。我们不妨考虑一个类似树上 dp 的思路，因为只需要满足度数的奇偶性，一个点的子树需要的度数只有 $0$ 或 $1$，这是这个点直接向子树连边可以满足的。用这样的方式建边，选择度数没有限制的点作为根节点是较优的。如果不存在这样的点，就任选一个点作为根节点。因为作为子节点被父节点满足，和作为父节点满足子节点，其实没有本质区别。

------------

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace IO{
#define ll long long
#define ischar(ch) (32<ch&&ch<127)
#define SIZE 1<<18
	char ibuf[SIZE],*is=ibuf,*it=ibuf;
#define getchar() (is==it&&(it=(is=ibuf)+fread(ibuf,1,SIZE,stdin),is==it)?EOF:*is++)
	template<typename Type>
	inline void read(Type &a){
		Type x=0;int y=0,ch=getchar();
		while(!isdigit(ch)&&(ch^EOF))y|=(ch=='-'),ch=getchar();
		while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
		a=y?-x:x;
	}
	inline void read(char &a){
		int ch=getchar();
		while(!ischar(ch)&&(ch^EOF))ch=getchar();
		a=ch;
	}
	inline void read(string &a){
		a="";char ch;
		while(!ischar(ch)&&(ch^EOF))ch=getchar();
		while(ischar(ch))a+=ch,ch=getchar();
	}
	inline void read(short &a){
		int ch=getchar();
		while(!isdigit(ch)&&(ch^EOF))ch=getchar();
		a=(ch^48);
	}
	template<typename Type>
	inline void read(Type a[]){
		Type *pos=a;
		int ch=getchar();
		while(!ischar(ch)&&(ch^EOF))ch=getchar();
		while(ischar(ch))*pos++=ch,ch=getchar();
		*pos=0;
	}
	inline void read(double &a){
		int zh=0,w=0,ch=getchar();
		double xi=0.0,x=1.0;
		while (!isdigit(ch)&&(ch^EOF))w|=ch=='-',ch=getchar();
		while(isdigit(ch))zh=(zh<<1)+(zh<<3)+(ch^48),ch=getchar();
		if(ch^'.')return void(a=w?-zh:zh);
		ch=getchar();
		while(isdigit(ch))x*=10.0,xi+=(ch^48)*1.0/x,ch=getchar();
		a=w?-zh-xi:zh+xi;
	}
	template<typename Type,typename ...Args>
	inline void read(Type &a,Args &...as){read(a);read(as...);}
	char obuf[SIZE],*op=obuf;
	inline void putch(const char &c){
		if(op-obuf==SIZE)fwrite(obuf,1,op-obuf,stdout),op=obuf;
		*op++=c;
	}
	template<typename Type>
	inline void write(Type x){
		if(x<0)putch('-'),x=-x;
		static int s[35],top;top=0;
		do s[top++]=x%10,x/=10;
		while(x);
		while(top)putch(s[--top]+'0');
	}
	int precision;
	inline void write(double x){
		ll n=1,base=10,k=precision;
		while(k)n=(k&1)?n*base:n,base*=base,k>>=1;
		x=round(x*n)/n;
		if(!x){
			putch('0'),putch('.');
			for(int i=1;i<=precision;++i)putch('0');
			return;
		}
		if(x<0)putch('-'),x=-x;
		ll y=(ll)round(x*n)%n;x=(ll)x;
		write((ll)x);putch('.');
		int s[35],top=0;
		for(;top<precision;y/=10)s[++top]=y%10;
		while(top)putch(s[top--]+'0');
	}
	inline void write(char ch){putch(ch);}
	inline void write(const char* s){for(int i=0;i<strlen(s);++i)putch(s[i]);}
	inline void write(string s){for(int i=0;i<s.size();++i)putch(s[i]);}
	template<typename Type,typename ...Args>
	inline void write(Type a,Args ...as){write(a);write(as...);}
	inline void oclear(){fwrite(obuf,1,op-obuf,stdout);}
#undef SIZE
#undef ischar
}
using namespace IO;
#define N 300010
//给定每个点的度数的奇偶性
//对于两个点加一条边，相当于度数都改变
//度数错的向度数对的连边，相当于把这个错误转移给对的点
//如果这个点和-1联通，那么一定可以改变成对的
//度数和为奇数一定是无解的

//考虑如何构造：
//对于一个环，加边是没有意义的
//所以可以当作一棵树来考虑
int n,m,d[N],sum,rt=-1,vis[N];
vector<pair<int,int>>e[N];
vector<int>ans;
#define add(u,v,i) e[u].push_back({v,i}),e[v].push_back({u,i})
inline int dfs(int u){//传回这个点的子树需要连多少边
	int res=d[u];//满足u需要连多少边
	vis[u]=1;
	for(auto i:e[u]){
		int v=i.first;
		if(vis[v])continue;
		if(dfs(v))res^=1,ans.push_back(i.second);
	}
	if(!~d[u])res=0;
	return res;
}
int main(){
	read(n,m);
	for(int i=1;i<=n;++i)read(d[i]),sum+=d[i],rt=(~d[i])?rt:i;
	for(int i=1,u,v;i<=m;++i)read(u,v),add(u,v,i);
	if(rt==-1)
		if(sum&1)return write(-1),oclear(),0;
		else rt=1;
	dfs(rt);
	write(ans.size(),'\n');
	for(int p:ans)write(p,'\n');
	oclear();
	return 0;
} 
  //马蜂毒瘤，仅供参考
```

---

## 作者：123456zmy (赞：2)

这篇题解主要讲一下证明过程，如果懒得看可以去看@lemonfor 写的题解

---
首先，对于一张图，其中度数为奇数的点的个数一定为偶数个（因为度数之和为偶数），所以就可以先判断按题目要求是否能构成一张图，顺便把 $-1$ 处理了，代码如下：
```
	//w1表示奇点个数的奇偶性，w[i]表示点的度数要求
	for(int i=1;i<=n;i++)if(w[i]==-1)
	{
		if(w1)
		{
			w1=0;
			w[i]=1;
		}
		else w[i]=0;
	}
	if(w1)
	{
		puts("-1");
		return 0;
	}
```
---
题目的要求可以转化为把所给的奇点两两连接，因为连接两点的路径只会改变两端点的度数的奇偶性，路径上其它点的奇偶性不变，所以就可以用bfs搜索出答案。

但是还有一个问题：搜出来的路径可能会把图划分为两或更多个不连通的子图，如果有子图中奇点的个数为奇数时，就会无解了，如果加上回溯，那么就会T到怀疑人生。但是如果一条边可以选多次，问题就简单很多了。

那么我们就假设每条边可以选无限次，那么如果一条边被选了两次，那么就可以把这两次选择都去掉，因为对于这条边，它的两个端点的度数都会减少 $2$，对答案是没有影响的，就可以对于边开一个标记数组，每次选择时将其中的值 $Xor1$ 就可以了。

但是这样做的复杂度是 $n \times m$ 的，还是不能通过此题。

---
因为每两对点之间只要有一条路径就可以了，所以，为了使算法更优，就可以随便提出一棵树来，然后在树上进行操作。

对于一棵子树，如果其中度数为奇数的点有奇数个，那么子树的树根到它的父节点的边一定要选，否则一定不选，原因是度数为奇数的点可以两两连接，如果有剩的点就一定需要连出去。

于是就可以用dfs来求出要选的边，然后输出。总复杂度 $ n+m $。

---
代码：（码风非常邪教，不建议学习）
```
#include<bits/stdc++.h>
using namespace std;
int n,m,u,v,w[300001],a[600001],a1[600001],a2[300001],a4[600001],a5,b[300001],ansn;
bool w1,ans[300001],vis[300001];
int find(int i){return b[i]==i?i:b[i]=find(b[i]);}
bool dfs(int i)
{
	if(vis[i])return 0;
	vis[i]=1;
	int a3=a2[i];
	bool ans1=w[i];
	while(a3)
	{
		if(dfs(a[a3]))
		{
			ans1^=1;
			++ansn;
			ans[a4[a3]]=1;
		}
		a3=a1[a3];
	}
	vis[i]=0;
	return ans1;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)b[i]=i;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&w[i]);
		if(w[i]==1)w1^=1;
	}
	for(int i=1;i<=n;i++)if(w[i]==-1)
	{
		if(w1)
		{
			w1=0;
			w[i]=1;
		}
		else w[i]=0;
	}
	if(w1)
	{
		puts("-1");
		return 0;
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		if(find(u)!=find(v))
		{
			b[b[u]]=b[v];
			a[(++a5)<<1]=v;
			a1[a5<<1]=a2[u];
			a2[u]=a5<<1;
			a[a5<<1|1]=u;
			a1[a5<<1|1]=a2[v];
			a2[v]=a5<<1|1;
			a4[a5<<1]=a4[a5<<1|1]=i;
		}
	}
	dfs(1);
	printf("%d\n",ansn);
	for(int i=1;i<=m;i++)if(ans[i])printf("%d ",i);
	return 0;
}
```


---

## 作者：Find_Yourself (赞：1)

构造题。

首先判断无解。每选一条边贡献两个度数，所以如果没有 $-1$ 的点，且度数和为奇数，那么无解。

接下来考虑构造。我们考虑从图中扣下来一棵树（dfs 树），如果度数为奇数，令 $-1$ 的点为根，否则随便选一个。

定义 $tp_i$ 表示第 $i$ 个节点是否需要与父亲连边，$0$ 表示不用，$1$ 表示用。然后对于当前点 $u$，向所有满足 $tp_v=1$ 的儿子连边，容易证明这是正确的。

因为，如果根为 $-1$ 的点，那么根怎么连都行；否则，根据反证法，如果根还需要连边，而其他节点都已连好，那么总度数为奇数，矛盾。

复杂度 $O(n)$。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
int n,m,d[N],tp[N],vis[N];
struct node{
  int v,id;
  node(int v=0,int id=0):v(v),id(id){}
};
vector<node>adj[N];
vector<int>ans;
void dfs(int u){
  int s=d[u];vis[u]=1;
  for(int i=0;i<adj[u].size();++i){
    int v=adj[u][i].v,id=adj[u][i].id;if(vis[v])continue;
    dfs(v);
    if(tp[v])s^=1,ans.push_back(id);
  }
  if(d[u]!=-1)tp[u]=s;
}
int main(){
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
  cin>>n>>m;
  int rt=1,f=0,s=0;
  for(int i=1;i<=n;++i){
    cin>>d[i];
    if(d[i]==-1)rt=f=i;
    else s^=d[i];
  }
  for(int i=1;i<=m;++i){
    int u,v;cin>>u>>v;
    adj[u].push_back(node(v,i));
    adj[v].push_back(node(u,i));
  }
  if(!f&&s)cout<<-1<<endl;
  else{
    dfs(rt);sort(ans.begin(),ans.end());
    cout<<ans.size()<<endl;
    for(int i=0;i<ans.size();++i)cout<<ans[i]<<endl;
  }
  return 0;
}

```


---

## 作者：1234567890sjx (赞：0)

猜猜题。猜不到。好愤怒。

首先一张图有如下的性质：所有点的度数的和一定是偶数。证明显然。

所以说若不存在 $-1$ 的点且所有点的度数的和是奇数，那么无解。否则一定有解。因为图连通，所以考虑构造图的任意一个生成树。然后在生成树上跑树形 dp 判断儿子结点和父亲结点之间的边是否相连即可。时间复杂度为 $O(n)$ 可以通过。但是我优秀的实现是 $O(n\log n)$ 的。

```cpp
vector<int> z[N];
map<pair<int, int>, int> mp;
int d[N], v[N], idx, vis[N];
int dfs(int u) {
    vis[u] = 1;
    int ok = d[u];
    for (auto &vv : z[u])
        if (!vis[vv])
            if (dfs(vv)) {
                v[++idx] = mp[{u, vv}];
                ok ^= 1;
            }
    return ok && d[u] != -1;
}
void run() {
    int n = read(), m = read();
    int s = 0, o = 1;
    for (int i = 1; i <= n; ++i) d[i] = read(), s += d[i], o &= (d[i] != -1);
    if (o && s % 2) cout << "-1\n";
    else {
        for (int i = 1; i <= m; ++i) {
            int x = read(), y = read();
            z[x].eb(y), z[y].eb(x);
            mp[{x, y}] = mp[{y, x}] = i;
        }
        int rt = -1;
        for (int i = 1; i <= n; ++i)
            if (d[i] == -1) rt = i;
        if (!~rt) rt = 1;
        dfs(rt);
        cout << idx << '\n';
        for (int i = 1; i <= idx; ++i) cout << v[i] << ' ';
        cout << '\n';
    }
}
```

---

## 作者：SJZ2010 (赞：0)

首先我们注意到 $d_u=-1$ 是个很特殊的条件，我们来研究一下。

经过思考我们可以发现，如果存在 $d_u=-1$，那么一定有解。与这个点相连的都可以随便连边，反正如果这个点不合要求了就往 $u$ 一连。这样子层层扩散，就可以了。

这个做法是对其余情况很有启发性的。

考虑没有 $d_u = -1$，那么我们可以先判断其是否必然无解：如果 $d$ 的异或和为 $1$，显然无解。因为无向图的度数之和一定是偶数。

然后我们有这样一个想法：先在图中拿出来一个点，不管它，考虑它周围的点。这样一层一层递归着做，应该是可以的。

明确一下这个做法，就是随便找个生成树，如果儿子中有连边的需要就连边，按照这个节点的连边情况在确定这个点是否需要父亲的连边。

这样子就必然有解，因为我们有一个点是否需要连边取决于其子树异或和的结论，这一点显然，请读者自证。那么我们已知 $d$ 的异或和为 $0$，就不可能出现根没法连边的情况。

[AC.](https://codeforces.com/contest/840/submission/278868920)

---

## 作者：hgzxwzf (赞：0)

## [CF840B](https://codeforces.com/contest/840/problem/B)
### 解题思路：
首先判断是否有答案：

如果度数为奇数的点的个数是奇数并且没有 $d$ 等于 $-1$ 的点，那么肯定无解，因为这样总度数就是一个奇数，而每条边对总度数的贡献是 $2$，总度数应该是偶数，所以这样的情况无解。

考虑如何构造一组解：

其实我们只需要找到满足条件的生成树即可，比如 dfs 树。

每个点记录一个值 $dp_i$，$dp_i$ 取 $0/1/-1$，$0$ 表示需要用到他和父亲的连边，$1$ 表示不需要，$-1$ 表示随便。

假设现在在 $u$ 点，记录一个 $sum$ 表示有几个儿子需要用到和自己的连边。

我们向下 dfs 到 $u$ 的儿子 $v$。

如果 $dp_v$ 等于 $1$，我们就把这条边放到答案里，且 $sum$ 加 $1$；

如果 $dp_v$ 等于 $-1$，那么最后 $dp_u=-1$。

如果 $u$ 不存在儿子 $v$ 满足 $dp_v=-1$，再判断 $u$ 是否需要与他父亲的那条边，利用 $sum$ 即可。

这显然可以找到一组解。

### 代码：
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>

#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=z;x>=y;x--)

using namespace std;
const int N=3e5+10;

struct edge
{
	int to,id;
};

vector<edge>e[N];
vector<int>ans;
int d[N];
bool vis[N],bo[N];

void dfs(int cur)
{
	vis[cur]=1;
	int sum=0;
	for(auto &nt: e[cur])
	{
		if(vis[nt.to]) continue;
		dfs(nt.to);
		if(bo[nt.to]==-1) bo[cur]=-1;
		else if(bo[nt.to]) ans.push_back(nt.id),sum++;
	}
	if(bo[cur]==-1) return ;
	else if((sum+1)%2==d[cur]) bo[cur]=1;
	else bo[cur]=0;
}

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	int ok=0,st=-1;
	rep(i,1,n)
	{
		scanf("%d",&d[i]);
		if(d[i]==-1) st=i,bo[i]=-1;
		else ok^=d[i];
	}
	rep(i,1,m)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].push_back((edge) {v,i});
		e[v].push_back((edge) {u,i});
	}
	if(st==-1&&ok) return puts("-1"),0;
	if(st==-1) st=1;
	dfs(st);
	printf("%d\n",(int)(ans.size()));
	for(auto &i: ans) printf("%d ",i);
	return 0;
}
```


---

## 作者：Lumos壹玖贰壹 (赞：0)

#### 简化题意
有一个联通无向图，每个点有要求：度必须是偶数、必须是奇数或无限制。
求是否能找出一个包含所有点的子图满足所有点的要求，若能，输出这个子图的边集

#### 思路
首先，看到无向连通图图上的问题，一个方向就是**建DFS生成树**。
将图中的边转化为树边和非树边，非树边对答案的影响转化为生成树上的覆盖。

然而这道题简单到甚至不用考虑非树边....

然后我们会想到**利用树的性质：子树独立**。所以可以考虑如何把一个子树内的点全部满足其条件。先递归处理$u$的所有儿子，回溯时若u已满足奇偶限制则直接回溯，否则将$(u,f(u))$选入集合，然后回溯。（这似乎是一种比较常见的树上构造方法）

显然，这样处理完后**只有根可能奇偶性不满足**。

若满足直接输出。

否则，若全局没有$-1$，则输出$-1$。

否则，随便找一个$-1$的点，记作$u$，将$u$到$root$路径上的边的选取情况取反(选变不选，不选变选)，然后输出即可。

输出可以记录每个点和它父亲的边是输入的哪一条，然后选不选

稍微卡卡常貌似是提交时的最优解，但应该很快就要被刷下去了吧~

#### Code
这里放上我丑陋的代码
```cpp
#include<bits/stdc++.h>
#define ri register int
#define ll long long
using namespace std;
const int maxn = 3e5 + 10;
int d[maxn],du[maxn],head[maxn],head1[maxn],ed[maxn],f[maxn],n,m,tot = 1,tot1;
bool chos[maxn],vis[maxn];
struct edge{
	int to,nex;
}e[maxn<<1],e1[maxn<<1];
inline void add(int u,int v){
	e[++tot] = (edge){v,head[u]};
	head[u] = tot;
}
inline int rd(){
	int res = 0,f = 0;
	char ch = getchar();
	for(;ch > '9' || ch < '0';ch = getchar()) if(ch == '-') f = 1;
	for(;ch >= '0' && ch <= '9';ch = getchar()) res = (res<<3) + (res<<1) + ch - 48;
	return f ? -res : res;
}
void dfs(int u){
	vis[u] = 1;
	for(ri i = head[u];i;i = e[i].nex){
		int v = e[i].to;
		if(vis[v]) continue;
		ed[v] = i >> 1;
		f[v] = u;
		e1[++tot1] = (edge){v,head1[u]};
		head1[u] = tot1;
		dfs(v);
	}
}
void solve(int x){
	for(ri i = head1[x];i;i = e1[i].nex) solve(e1[i].to);
	if(du[x] == d[x] || d[x] == -1 || x == 1) return;
	chos[x] = 1;
	du[x] ^= 1; du[f[x]] ^= 1;
	return;
}
void change(int x){//把x到root的边的状态全部取反
	while(x != 1){
		chos[x] ^= 1;
		du[x] ^= 1; du[f[x]] ^= 1;
		x = f[x];
	}
	return;
}
int ans[maxn],cnt = 0;
int cp = -1;
void write(int x){
	if(x > 9) write(x / 10);
	putchar(x % 10 + 48);
}
void prin(int x){
	if(x < 0) putchar('-'),x = -x;
	write(x);
}
int main(){
	n = rd(); m = rd();
	for(ri i = 1;i <= n;++i){
		d[i] = rd();
		if(!(~d[i]) && !(~cp)) cp = i;//cp -> changing positon
	}
	for(ri i = 1,u,v;i <= m;++i)
		u = rd(),v = rd(),add(u,v),add(v,u);
	dfs(1);//建树
	solve(1);//按先保证儿子满足的方式递归处理整棵树
	if(~d[1] && du[1] ^ d[1] && (~cp)) change(cp);//需要change并且可以change
	if(~d[1] && du[1] ^ d[1]){
		puts("-1");
		return 0;
	}
	for(ri i = 2;i <= n;++i)
		if(chos[i]) ans[++cnt] = ed[i];
	prin(cnt); puts("");
	for(ri i = 1;i <= cnt;++i) prin(ans[i]),putchar(' ');
	puts("");
	return 0;
}

```

~~完结撒花//QwQ///~~

---

