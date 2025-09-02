# Cow and Snacks

## 题目描述

The legendary Farmer John is throwing a huge party, and animals from all over the world are hanging out at his house. His guests are hungry, so he instructs his cow Bessie to bring out the snacks! Moo!

There are $ n $ snacks flavors, numbered with integers $ 1, 2, \ldots, n $ . Bessie has $ n $ snacks, one snack of each flavor. Every guest has exactly two favorite flavors. The procedure for eating snacks will go as follows:

- First, Bessie will line up the guests in some way.
- Then in this order, guests will approach the snacks one by one.
- Each guest in their turn will eat all remaining snacks of their favorite flavor. In case no favorite flavors are present when a guest goes up, they become very sad.

Help Bessie to minimize the number of sad guests by lining the guests in an optimal way.

## 说明/提示

In the first example, Bessie can order the guests like this: $ 3, 1, 2, 4 $ . Guest $ 3 $ goes first and eats snacks $ 1 $ and $ 4 $ . Then the guest $ 1 $ goes and eats the snack $ 2 $ only, because the snack $ 1 $ has already been eaten. Similarly, the guest $ 2 $ goes up and eats the snack $ 3 $ only. All the snacks are gone, so the guest $ 4 $ will be sad.

In the second example, one optimal ordering is $ 2, 1, 3, 5, 4 $ . All the guests will be satisfied.

## 样例 #1

### 输入

```
5 4
1 2
4 3
1 4
3 4
```

### 输出

```
1
```

## 样例 #2

### 输入

```
6 5
2 3
2 1
3 4
6 5
4 5
```

### 输出

```
0
```

# 题解

## 作者：SIGSEGV (赞：15)

因为每只动物都有2个最喜欢的点心，所以以点心为点，连接所有动物喜欢的两种点心见图。

考虑一个大小$>1$的联通块。肯定有一个动物得吃到2种点心，而总有一种排队顺序使得这个块中没有任何一头动物再吃到2种点心（比如说BFS序），那么一个大小为$c$的联通块可以满足$c-1$个动物。

设联通块个数为$C$，则高兴的动物有$n-C$个，悲伤的动物有$m-(n-C)$个。

使用$DSU$（并查集）实现。

```cpp
    #include <bits/stdc++.h>
    using namespace std;
    const int N = 100005;
    int n,kk,f[N],sz[N];
    int getf(int v) {if (f[v] != v) f[v] = getf(f[v]);return f[v];}
    int main ()
    {
        ios::sync_with_stdio(false);
        cin >> n >> kk;
        int t1,t2;
        for (int i = 1;i <= n;i++) f[i] = i;
        for (int i = 1;i <= kk;i++)
        {
            cin >> t1 >> t2;
            f[getf(t1)] = getf(t2);
        }
        int cnt = 0;
        for (int i = 1;i <= n;i++) if (f[i] == i) ++cnt;
        cout << kk - (n - cnt);
        return 0;
    }
```

---

## 作者：微香玉烛暗 (赞：8)

这道题题目的唯一作用就是掩人耳目，将人引入“图上求连通块”的歧途。（本场Div2，本班同学[mwr大佬](https://www.luogu.org/space/show?uid=235926)因死死纠缠连通图而错失D题）
为何不能直接**并查集**？

即每次将最近该头牛的$x_i$和$y_i$进行判断，如在同一集合中，答案加一；反之则合并$x_i$和$y_i$。

然后就没有了。

代码：
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N=100005;
int n,k,x,y,ans,f[N];

int find (int x) {
    return f[x]==x?x:find(f[x]);
}
//并查集基本操作：找爸爸。不会的自己上网查

int main () {
    scanf ("%d%d",&n,&k);
    for(int i=1;i<=n;i++) f[i]=i;
    //一开始，每个食物是自己的爸爸（怪怪的）
    while(k--){
        scanf ("%d%d",&x,&y);
        int r1=find(x),r2=find(y);
        if (r1!=r2)
			f[r1]=r2;
        else ans++;
        //如上述文字
    }
    printf("%d\n",ans);
    //完结撒花
	return 0;
}
```


---

## 作者：翟翟 (赞：5)

**题意：**有 $k$ 个客人，到店里买走他所喜欢的 $2$ 朵花中店内有的。而店里标号从 $1$ ~ $n$ 每种花只有一朵。可以随意调整 $k$ 个客人的顺序，使买不到花的客人数量最少。

**思路：**我们如果以每种化为一个点，以每个客人喜欢的两朵花给两朵花连一条无向边。则会出现一定数目的连通块，连通块总个数为 $ans$。对每个连通块进行分析：第一个客人买走 $2$ 朵，之后的客人每人买走 $1$ 朵，这样在一个点数为 $cnt$ 的连通块中，可以满足 $cnt-1$ 个客人。这样便可使被满足的客人最多。则最终答案就是 $k-(n-ans)=k-n+ans$。

可以用并查集来实现。


## Code
```cpp
#include<cstdio>
const int N=1e5+1; 
int n,k,x,y,f[N],ans;
inline int find(int x){//基本操作：找爸爸
	return f[x]^x?f[x]=find(f[x]):x;
}
int main(){
	scanf("%d%d",&n,&k);
	for(register int i=1;i<=n;++i)f[i]=i;//并查集基本操作
	for(register int i=0;i<k;++i){//k个客人
		scanf("%d%d",&x,&y);
		x=find(x),y=find(y),f[x]=y;//连边
	}
	for(register int i=1;i<=n;++i)
		if(f[i]==i)++ans;//统计连通块个数
	printf("%d\n",k-n+ans);
	return 0;
}
```

---

## 作者：Sqrtyz (赞：5)

### 题意

+ 有 $n$ 种零食，每种零食只有一个，编号从 $1 \sim n$ 排列。

+ 有 $m$ 位客人排序后会依次取走零食。第 $i$ 个客人有 $a_i,b_i$ 两种喜爱口味，当该其取用零食时，他会取走剩余零食中所有他的喜爱口味。

+ 安排客人们的顺序，使至少取到一种喜爱口味零食的客人数目最大化。

### 解题

看到 $n,m$，$a_i,b_i$ 是不是有熟悉的感觉？好叭，这道题其实可以转换成一个图论模型。

我们想到，第一位客人肯定把他的喜爱口味全会取走，为了让结果更优，我们希望接下来的客人的喜爱口味与之有重合，这样他就只会取走一个零食，以此类推……可以证明，这样的思路是正确的。

于是我们建一个 $n$ 个点，$m$ 条边的图。第 $m$ 条边连接 $a_i,b_i$ 两点。显然这样会形成若干个连通块。对于每一个连通块如上述处理，假设该连通块有 $x$ 个点，那么该连通块中最终有 $x-1$ 位客人可以取走零食。于是答案就变成了统计每个连通块的点数……

我直接把图建出来跑了一遍 dfs …… 另外注意最后求的答案是“悲伤的来宾”的数量。细节参见代码。

### 代码

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
 
#define Maxk 100010
#define Maxn 100010
 
using namespace std;
 
int read() {
	int x = 0,f = 1;
	char c = getchar();
	while(c < '0' || c > '9') {
		if(c == '-') f = -1;
		c = getchar();
	}
	while('0' <= c && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x * f;
}
 
int N,K;
int rest[Maxn];
 
struct Edge {
	int next,to;
}
edge[Maxk * 2];
int head[Maxn],edge_num;
 
void add_edge(int from,int to) {
	edge[++edge_num].next = head[from];
	edge[edge_num].to = to;
	head[from] = edge_num;
}
 
int vis[Maxn];
 
int dfs(int u) {
	vis[u] = 1;
	int res = 0;
	for(int i = head[u];i;i = edge[i].next) {
		int v = edge[i].to;
		if(!vis[v]) res += (dfs(v) + 1);
	}
	return res;
}
 
int main() {
	N = read(); K = read();
	int x,y;
	for(int i = 1;i <= K; i++) {
		x = read(); y = read();
		add_edge(x,y);
		add_edge(y,x);
	}
	int ans = 0;
	for(int i = 1;i <= N; i++) {
		if(!vis[i]) ans += dfs(i);
	}
	cout << K - ans;
	return 0;
}
```

---

## 作者：杨铠远 (赞：4)

将每一头牛与它喜欢的小吃连边

每一个联通的点集包含的小吃的数量为$i$

那么最多满足$i-1$头牛

因为总能找出一种方案让一头牛选两个小吃，其他的牛选一个

最后将答案相加，总牛数减这个数就是答案

```cpp
//Code by : Y-k-y
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <vector>
#include <set>
#define ll long long
const int N=1000010;
using namespace std;
inline int rnd(){
	int res=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){res=res*10+ch-'0';ch=getchar();}
	return res*f;
}
inline void wr(int x){
	if(x<0){putchar('-');x=-x;}if(x>9) wr(x/10);putchar(x%10+'0');
}
struct pp{
	int v,nxt;
}edge[N];
int head[N];
int tot,n,m,col,ans;
int co[N],tong[N];
inline void add(int u,int v){
	edge[++tot].nxt=head[u],head[u]=tot;
	edge[tot].v=v;
	edge[++tot].nxt=head[v],head[v]=tot;
	edge[tot].v=u;
}
inline void dfs(int u){
	if(u>m)tong[col]++;
	co[u]=col;
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].v;
		if(co[v])continue;
		dfs(v);
	}
}
int main(){
	cin>>n>>m;int x,y;
	for(int i=1;i<=m;i++){
		x=rnd();y=rnd();
		add(i,x+m);add(i,y+m);
	}
	for(int i=1;i<=m;i++){
		if(!co[i]){
			++col;
			dfs(i);
		}
	}
	for(int i=1;i<=col;i++){
		ans+=tong[i]-1;
	}
	wr(m-ans);
	return 0;
}

```


---

## 作者：Tenshi (赞：3)

## 分析
这题不需要其他东西，用并查集就可以了 $qwq$ 。

注意到：对于一个有 $k$ 个点的图 $G$ ，如果想要让它连通，那么**需要且仅需**在 $k$ 个点间连 $k-1$ 条边（无重边）。

更进一步说，无论连边的顺序如何，在 $k$ 个点间连 $k-1$ 条边（无重边）能够让 $G$ 连通。

那么我们一边读入边一边用并查集维护连通关系就行了：

+ 如果边的两个端点在同一联通块，贡献 $+1$
+ 否则将它们合并

绝赞超短代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2e5+5;
int f[N];
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
int main(){
	int n, m; cin>>n>>m;
	for(int i=1; i<=n; i++) f[i]=i;
	
	int res=0;
	while(m--){
		int u, v; cin>>u>>v;
		if(find(u)==find(v)) res++;
		else f[find(u)]=find(v);
	}	
	cout<<res<<endl;
	return 0;
}

```

---

## 作者：Otomachi_Una_ (赞：2)

## 题目简述

- 有 $n$ 种花，$k$ 个人。每个人都想买两种花 $a_i,b_i$。
- 这 $n$ 个人依次进入（你可以操控顺序）。一个人进去后会把他想要的花都买走。
- 至少有多少个人买不到花？
- $n,k\leq10^5$。

## 解题思路

不妨建一个无向图，边为 $(a_i,b_i)$。我们发现对于每一个连通块，第一个人必然拿走 $2$ 种，然而因为这个连通块联通，所以在后面的操作中你可以让每个人都拿走 $1$ 种。

所以说一个大小为 $u$ 的连通块会有 $u-1$ 个人买得到花。所以答案就是：$k-(n-c)$。其中 $c$ 是连通块的个数，可以通过并查集查到。

## 参考代码

```cpp
#include<iostream>
using namespace std;
const int MAXN=1e5+5;
int fa[MAXN];int n,k;
int find(int x){return (fa[x]==x)?x:fa[x]=find(fa[x]);}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		fa[i]=i;
	for(int i=1;i<=k;i++){
		int a,b;
		cin>>a>>b;
		fa[find(a)]=find(b);
	}
	int cnt=0;
	for(int i=1;i<=n;i++)
		if(fa[i]==i) cnt++;
	cout<<k-(n-cnt);
	return 0; 
}
```

---

## 作者：Skyjoy (赞：1)

其实这道题是一道很妙的猜结论+证明题

# 思路

（这里的一些名词按照英文题面的来讲）

- 我们考虑以每一种小吃为点，以每一个客人为边来给两个点之间连无向边。我们对每一个联通块进行分析。我们发现，我们既然要选**最多的客人**，那么我们就要尽量让客人吃的小吃**尽量少**。而在最优情况下，在一个联通块中，第一个客人必须吃掉2个小吃，而剩下的客人都最少吃掉1个小吃。所以在一个点数为 $n$ 的联通块中，我们选择客人数量的**理论最大值**就是 $n-1$ 。而这个理论最大值是取得到的，也非常容易构造。所以我们只需要求出图中联通块的个数 $cnt$ ，那么答案就是 $m-n+cnt$ 了！

- 联通块个数可以通过并查集查询。

# 代码

```cpp
#include<bits/stdc++.h>
#define I using
#define love namespace
#define Elaina std
I love Elaina;
const int N=100010;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x*f;
}
int n,m,x,y,fi[N],cnt;
int find(int x){
	return x==fi[x]?x:fi[x]=find(fi[x]);
}
void merge(int x,int y){
	x=find(x),y=find(y);
	if(x==y)return;
	fi[x]=y;
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)fi[i]=i;
	for(int i=1;i<=m;i++){
		x=read(),y=read();
		merge(x,y);
	}
	for(int i=1;i<=n;i++)if(i==fi[i])cnt++;
	printf("%d",m-n+cnt);
	return 0;
}
```

祝各位大神们 $NOI$ 加油！

---

## 作者：_lbw_ (赞：1)

以花为点，每个人喜欢的两种花之间建图

若找出一个连通块且节点个数大于 $1$ 且大小为 $C$，考虑这个连通块里的人的所有顺序，第一个人可以选到 $2$ 个，而 $2 \cdots C-1$ 的人只能选到一个，第 $C$ 个人不可以选

用并查集实现

```cpp
ll n,m,fa[maxn],ans;
ll find(ll tmp){return fa[tmp]==tmp?tmp:(fa[tmp]=find(fa[tmp]));}
int main(){
	n=read();m=read();
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		ll x=read(),y=read();
		if(find(x)==find(y))ans++;
		else fa[find(x)]=find(y);
	}
	cout<<ans;
    return 0;
}
```


---

## 作者：5k_sync_closer (赞：0)

考虑以零食为点建无向图，$(u,v)\in E$ 当且仅当存在一个客人喜欢零食 $u,v$。

对于其中每一个大小为 $m$ 的连通块，总能安排出一种顺序使得连通块中的零食可以满足 $m-1$ 个客人，

即第一个客人吃掉其中 $2$ 个零食，剩下 $m-2$ 个客人分别吃掉其中 $1$ 个零食。

也就是在满足 $n$ 个客人的前提下，图中每多一个连通块，就少一个能满足的客人。

并查集统计图中连通块个数 $c$，答案即为 $k - n + c$。
```cpp
#include <cstdio>
int n, k, u, v, c, f[100050];
int F(int x) {return x == f[x] ? x : f[x] = F(f[x]);}
int main()
{
	scanf("%d%d", &n, &k);for(int i = 1;i <= n;++i) f[i] = i;for(int
	i = 0;i < k;++i) scanf("%d%d", &u, &v), f[F(u)] = F(v);for(int i
	= 1;i <= n;++i) c += i == F(i);return printf("%d", k - n + c), 0;
}
```

---

## 作者：mot1ve (赞：0)

自己的一点想法，用并查集做的，分了四种情况讨论，实际只需要判断第四种情况

**我们假设一个元素>=2的集合叫做联通块**

**1**.x,y 均不在任一个联通块内，可以选，这俩都没人预定

**2**.x,y 其中有一个在一个联通块内，也可以选，因为不在联通块内的元素没人预定

****3****.x,y 都在联通块中，但所在的联通块不是一个，这种情况可以转化为第2种情况

举个例子，有4种甜点，3个客人，读入数据如下

(1,2),(3,4),(2,3)

2在(1,2)组成的联通块中，3在(2,3)组成的联通块中

1,2属于同一联通块，3,4属于同一联通块，由于我们想让沮丧的牛最少，所以我们应

该尽可能的优化顺序，使得相邻之间有一个重叠，这样不会出现一头牛吃了两种的情

况（除了第一头），也就是第2种情况，优化之后顺序为

(1,2),(2,3),(3,4),这样没有任何一头牛是沮丧的

**4**.x,y 都在同一联通块中，无论怎么优化顺序也得有一头牛什么也吃不到，

肯定得有一头牛沮丧了，ans++

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,k,ans;
int fa[100010];
int find(int x)
{
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
void unionn(int x,int y)
{
	fa[find(x)]=find(y);
} 
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		fa[i]=i;
	}
	for(int i=1;i<=k;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		int x1=find(x),y1=find(y);
		if(x1!=y1)
		unionn(x1,y1);
		else ans++;
	}
	printf("%d",ans);
	return 0;
}


---

## 作者：hater (赞：0)

模拟赛 T3 

这道题的思路如下 

暴力 —— 贪心 —— 二分图 —— DP —— 并查集 

~~窝太菜了~~ 

这道题的思路是把零食看成点 

人看成边 

那么假设联通块数量 n

我们可以找到一组边 把它们连起来 边的数量是n-1

把所有边连起来 之后 

把联通块遍历一遍 得出有Ans个奶牛可以满足 

那么反过来 就有n-Ans头奶牛不满足 

正确性 ？ 自己口胡乱举例就差不多了

```cpp
#include <bits/stdc++.h> 
#define MAX 100005 
#define R register 
using namespace std  ; 
int pre[MAX] , siz[MAX] , n , m , Ans ; 
int f ( R int x ) { return pre[x] == x ? x : pre[x] = f(pre[x]) ; }
void join( R int x , R int y ) { siz[f(x)] += siz[f(y)] ; pre[f(y)] = f(x) ; }
bool too( R int x , R int y ) { return f(x) == f(y) ; }
signed main() 
{
	R int xi , yi ; 
//	freopen( "cow.in" , "r" , stdin ) ;
	//freopen( "cow.out" , "w", stdout ) ; 
	ios::sync_with_stdio(false) ; 
	cin >> m >> n ;
	for(R int i=1; i<=m; i++)
	  pre[i] = i , siz[i] = 1 ; 
	for(R int i=1; i<=n; i++) 
	{
		cin >> xi >> yi ;
		if( !too(xi ,yi) ) 
		 join( xi , yi ) ;
	}
	for(R int i=1; i<=m; i++) 
	  if( pre[i] == i ) Ans += siz[i]-1 ;
	cout << max( 0 , n-Ans )<< endl; 
	return 0 ;
}
```



---

