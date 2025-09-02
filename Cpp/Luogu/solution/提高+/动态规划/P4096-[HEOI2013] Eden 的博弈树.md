# [HEOI2013] Eden 的博弈树

## 题目描述

对于有两个玩家的，状态透明且状态转移确定的博弈游戏，博弈树是常用的分析工具。博弈树是一棵有根树，其中的节点为游戏的状态。若节点 B 的父亲是 A，则说明状态 A 能通过一次决策转移到状态 B。每个状态都有一个唯一的决策方，即这个状态下应该由哪一方做出决策。我们规定双方在任何时候都是轮流做出决策的，即树上相邻节点的决策方总是不相同的。

在这个问题中，我们只关心两个玩家的胜负情况，且规定游戏不会出现平局。

我们称两个玩家分别为黑方和白方，其中根节点的决策方为黑方。显然每个节点只有两个状态：黑方胜和白方胜。若某内节点（即存在后继节点的节点）的决策方为黑方，则该节点为黑方胜的充要条件为它的儿子中存在黑方胜的节点，反之亦然。求解博弈树即为判明博弈树根节点的状态。

如果我们得知了所有叶节点（即无后继节点的节点）的状态，那么博弈树就很容易求解了。但是现在的情况是所有叶节点的状态均为未知的，需要进一步的计算。对于一个由叶节点构成的集合 $S$，如果 $S$ 中的节点均被判明为黑方胜，就可以断言根节点为黑方胜的话，则称 $S$ 为一个黑方胜集合。对于黑方胜集合 $S$， 如果对于任意的黑方胜集合 $S'$ 均满足 $|S| \le |S'|$（$|S|$ 表示集合 $S$ 中的元素数目）， 则称 $S$ 为一个最小黑方胜集合。同样地，也可以定义白方胜集合和最小白方胜集合。

Eden 最近在研究博弈树问题。他发现，如果一个叶节点既属于某一个最小黑方胜集合，又属于一个最小白方胜集合，那么求解这个节点的状态显然最有益于求解根节点的状态。像这样的叶节点就称之为关键叶节点。对于一棵给定的博弈树，Eden 想要知道哪些叶节点是关键叶节点。


## 说明/提示

【样例说明】

  ![](https://cdn.luogu.com.cn/upload/pic/13130.png) 

如图所示，黑色节点表示决策方为黑方的节点，反之亦然

所有的最小黑方胜集合为 $\{4, 5\}$ 和 $\{6, 7\}$。

所有的最小白方胜集合为 $\{4, 6\}$，$\{4, 7\}$，$\{5, 6\}$ 和 $\{5, 7\}$。

所以关键叶节点的集合为 $\{4, 5, 6, 7\}$。

- 对于 $30\%$ 的数据，$n \le 100$；
- 对于 $40\%$ 的数据，$n \le 1000$；
- 对于 $50\%$ 的数据，$n \le 10 ^ 4$，且树是随机生成的；
- 对于 $100\%$ 的数据，$1 \le n \le 2\times 10 ^ 5$，且对于节点 $i$（$i \ne 1$），其父节点的编号小于 $i$。


## 样例 #1

### 输入

```
7 
1 
1 
2 
2 
3 
3```

### 输出

```
4 4 0 
```

# 题解

## 作者：beretty (赞：5)

emm,一开始看这题感觉很难的样子

然后看了好久才看明白题意

看懂题意后其实做法其实并不难

就是先Dfs染一遍色

黑节点的儿子是白点，白点的儿子是黑点

然后用 f[i][j] 来表示i这个点为j方赢时最少控制的关键节点数

怎么求关键节点数目 ？

以黑方为例 ：

* 如果该点是白点，则只有其所有的儿子都是黑节点

* 如果该点是黑点，则只需要有一个儿子是黑点

最后再Dfs一遍把黑方白方的关键节点书都求出来，最后统计答案时就将黑白关键节点取个并集就好辣

```

#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cmath>
const int M = 200005 ;
const int INF = 2147483646 ;
using namespace std ;
inline int read(){
	char c = getchar() ;int x=0,w=1;
	while(c>'9'||c<'0'){ if(c=='-') w=-1; c = getchar() ;}
	while(c>='0'&&c<='9'){ x = x*10+c-'0';c = getchar() ;}
	return x*w ;
}
struct E{
	int nex,to;
}edge[M<<1];
int hea[M] , num ;
inline void add_edge(int from,int to){
	edge[++num].nex = hea[from] ; 
	edge[num].to = to ;
	hea[from] = num ;
}
int n ;
int col[M] , f[M][2] ;
bool Control[M][2] , Son[M] ;
int MinAns = INF , Ansnum , Anstot ;

void Dye(int u){
	if(!Son[u]) f[u][0] = f[u][1] = 1 ;
	for(int i=hea[u];i;i=edge[i].nex){
		int v = edge[i].to ;
		col[v] = col[u]^1 ;
		Dye(v) ;
	}
}
void Dfs(int u,int j){
	if(j == col[u] && !f[u][j] ) f[u][j] = INF ; 
	for(int i=hea[u];i;i=edge[i].nex){
		int v = edge[i].to ;
		Dfs(v,j) ;
		if(j == col[u]) f[u][j] = min(f[u][j] , f[v][j]) ;
		else f[u][j] += f[v][j] ;
	}
}
void Ldfs(int u,int j){
	int tmp = INF ;
	for(int i=hea[u];i;i=edge[i].nex){
		int v = edge[i].to ;
		if(j==col[u]) tmp = min(tmp,f[v][j]) ;
		else Ldfs(v,j) ;
	}
	if(j==col[u]&&Son[u])
	  for(int i=hea[u];i;i=edge[i].nex){
	  	int v = edge[i].to ;
	  	if(f[v][j]==tmp)
	  	  Ldfs(v,j) ;
	  }
	if(!Son[u]) Control[u][j] = 1 ;
}
int main(){
	n = read() ;
	for(int i=2;i<=n;i++){
		int x = read();
		Son[x] = 1 ;
		add_edge(x,i) ;
	}
	col[1] = 1 ;
	Dye(1) ;
	Dfs(1,1) ; Dfs(1,0) ;
	Ldfs(1,1) ; Ldfs(1,0) ;
	for(int i=1;i<=n;i++)
	  if(Control[i][0]&Control[i][1]){
	  	MinAns = min(MinAns,i) ;
	  	Ansnum++ ;
	  	Anstot ^= i ;
	  }
	printf("%d %d %d\n",MinAns,Ansnum,Anstot) ;
	return 0;
}


```

---

## 作者：是个妹子啦 (赞：2)

题意~~好裸~~好难

不过看懂题就好做了，~~这题目都把要求说出来了~~，博弈树，~~转移也都说出来了~~

直接用$sg$函数定义$dp$，求出黑白点必胜所需最少叶子节点数

决策点为黑方，最小黑方胜集合是所有儿子最小的那个

决策为白方，最小黑方胜集合为所有儿子最小黑方胜集合并集

$vector$存下所有的最优解就好了

```cpp
struct edge{int to,next;}e[N<<1]; int head[N],tot;
vector<int>ans[N];
int n,f[N][2],deg[N],num,XOR,minn = inf;
inline void add(int u,int v){
	e[++tot] = (edge){v,head[u]}; head[u] = tot;
}
void dfs(int x,int now){
	f[x][now] = inf;
	for(int i = head[x];i;i = e[i].next){
		int v = e[i].to; dfs(v,now ^ 1);
		if(f[v][now] < f[x][now]) {
			f[x][now] = f[v][now]; 
			ans[x].clear(); ans[x].push_back(v);
		} 
		else if(f[v][now] == f[x][now])
			ans[x].push_back(v);
		f[x][now ^ 1] += f[v][now ^ 1];
	}
	if(!deg[x]) f[x][now ^ 1] = f[x][now] = 1;
}
void work(int x,int now){
	if(!deg[x]) {++num, XOR ^= x, minn = min(minn,x); return;}
	int siz = ans[x].size();
	for(int i = 0;i < siz;++i) work(ans[x][i],now ^ 1);
}
int main(){
	n = read();int u;
	for(int i = 2;i <= n;++i){
		u = read();
		add(u,i); ++deg[u];
	}
	dfs(1,1); minn = inf; work(1,1);
	printf("%d %d %d",minn,num,XOR);
} 
```



---

## 作者：卖淫翁 (赞：1)

```
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=200005;
const int inf=1000000000;
int n,dep[N],cnt,last[N],f[N],tag[N];
struct edge{int to,next;}e[N];

void addedge(int u,int v)
{
    e[++cnt].to=v;e[cnt].next=last[u];last[u]=cnt;
}
void dp1(int x,int fa)
{
    dep[x]=dep[fa]+1;
    for (int i=last[x];i;i=e[i].next) dp1(e[i].to,x);
    if (!last[x]) {f[x]=1;return;}
    if (dep[x]&1)
    {
        f[x]=inf;
        for (int i=last[x];i;i=e[i].next)
            if (f[x]=min(f[x],f[e[i].to]));
    }
    else
    {
        f[x]=0;
        for (int i=last[x];i;i=e[i].next) f[x]+=f[e[i].to];
    }
}
void work1(int x)
{
    if (!last[x]) tag[x]++;
    if (dep[x]&1)
    {
        for (int i=last[x];i;i=e[i].next)
            if (f[e[i].to]==f[x]) work1(e[i].to);
    }
    else
    {
        for (int i=last[x];i;i=e[i].next) work1(e[i].to);
    }
}
void dp2(int x)
{
    for (int i=last[x];i;i=e[i].next) dp2(e[i].to);
    if (!last[x]) {f[x]=1;return;}
    if (dep[x]&1)
    {
        f[x]=0;
        for (int i=last[x];i;i=e[i].next) f[x]+=f[e[i].to];
    }
    else
    {
        f[x]=inf;
        for (int i=last[x];i;i=e[i].next)
            if (f[x]=min(f[x],f[e[i].to]));
    }
}
void work2(int x)
{
    if (!last[x]) tag[x]++;
    if (dep[x]&1)
    {
        for (int i=last[x];i;i=e[i].next) work2(e[i].to);
    }
    else
    {
        for (int i=last[x];i;i=e[i].next)
            if (f[e[i].to]==f[x]) work2(e[i].to);
    }
}
int main()
{
    scanf("%d",&n);
    for (int i=2,x;i<=n;i++) scanf("%d",&x),addedge(x,i);
    dp1(1,0);work1(1);
    dp2(1);work2(1)
    int s1=0,s2=0;
    for (int i=1;i<=n;i++) if (tag[i]==2) {printf("%d ",i);break;}
    for (int i=1;i<=n;i++) if (tag[i]==2) s1++,s2^=i;
    printf("%d %d",s1,s2);
    return 0;
   
}
```
```
题目很长，不过是道水题。 
先看黑关键点怎么求，白点同理。 
设f[i]表示点i为黑必胜时最少需要把多少叶节点染黑。 
按照深度分类转移即可。
```


---

