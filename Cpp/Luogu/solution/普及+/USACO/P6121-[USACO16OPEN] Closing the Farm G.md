# [USACO16OPEN] Closing the Farm G

## 题目背景

*本题和 [银组同名题目](/problem/P3144) 在题意上一致，唯一的不同是数据范围。*

## 题目描述

FJ 和他的奶牛们正在计划离开小镇做一次长的旅行，同时 FJ 想临时地关掉他的农场以节省一些金钱。

这个农场一共有被用 $M$ 条双向道路连接的 $N$ 个谷仓（$1 \leq N,M \leq 2 \times 10^5$）。为了关闭整个农场，FJ 计划每一次关闭掉一个谷仓。当一个谷仓被关闭了，所有的连接到这个谷仓的道路都会被关闭，而且再也不能够被使用。

FJ 现在正感兴趣于知道在每一个时间（这里的“时间”指在每一次关闭谷仓之前的时间）时他的农场是否是“全连通的”——也就是说从任意的一个开着的谷仓开始，能够到达另外的一个谷仓。注意自从某一个时间之后，可能整个农场都开始不会是“全连通的”。

## 样例 #1

### 输入

```
4 3
1 2
2 3
3 4
3
4
1
2```

### 输出

```
YES
NO
YES
YES```

# 题解

## 作者：Meteorshower_Y (赞：45)

## P6121
~~CSP前发篇题解增加一些RP~~

看到这道题，第一眼，~~思路就是跑 n 遍并查集~~，瞅了一眼数据（1≤N,M≤2×$10^5$），if I do that，I will T 的 ~~起飞~~

我觉得这道题的“[弱化版](https://www.luogu.com.cn/problem/P3144)”还是可以过得

~~虽然我没这么写~~

输入的最后n行表示农场关的顺序，那我们倒过来看（从后往前）是不是可以看成农场开的顺序（2-1-4-3）

```
T0:全开着（1 2 3 4） 
T1:关了3 （1 2 4）
T2:关了4 （1 2）
T3:关了1 （2）
T4:关了2 （-）
```
看作
```
T4:全关着（-） 
T3:开了2 （2）
T2:开了1 （1 2）
T1:开了4 （1 2 4）
T0:开了3 （1 2 3 4）
```
### 1.整体思路
也就是说我们可以从$T_{n-1}$搜索到${T_0}$时刻，每次判断加上一个点，还是否与其他点联通。
### 2.理论支持
把 $k$ 个点和并成一个联通图，  
一次合并两个点（即在两个点间加一条边），  
不重复操作（两个点已经联通的就不加了），  
我们只需要操作 $k-1$ 次（加 $k-1$ 条边）即可，  
如果说我们操作不够 $k-1$ 次（边数小于 $k-1$），  
那么这张图一定不连通。

我们需要依靠并查集来实现，  
那用并查集来解释就是所有的点是否在同一个集合，  
如果在，则联通； 反之，则不连通。
### 3.具体实现
我们用一个数组 $ f $ 来存他的祖先节点，  
开始初始化成每个点自己在一个集合，  
如果他们不在一个集合的话，并且有一条边连接他们两个，就把他，们合并起来，操作数 $+1$.  
如果当前有 $k$ 个农场是开着的，记录合并的次数，如果次数等于 $k-1$ 则```YES```;反之，则```NO```.

#### 初始化
```cpp
inline void init(){
    for(register int i=1;i<=n;i++)
        f[i]=i;
}
```
#### 链式前向星存边
```cpp
int tot,head[200010];
inline void add_edge(int from,int to){
    e[++tot].from=from;
    e[tot].to=to;
    e[tot].next=head[from];
    head[from]=tot;
…… …… ……
scanf("%d%d",&u,&v);
        add_edge(u,v);
        add_edge(v,u);
}
```
#### 并查集（路径压缩+合并）
```cpp
inline int _find(int x){
    while(x!=f[x]) x=f[x]=f[f[x]];
    return x;
…… …… ……
int fx=_find(t[i]),fy=_find(e[j].to);
if(fx!=fy)
{
	++k; //合并次数+1
	f[fx]=fy;
}
```

## 完整代码附上~

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
struct _edge{
    int from;
    int to;
    int next;
}e[400010];
int tot,head[200010],k;
bool vis[200010];                        //判断农场是否开着 
inline void add_edge(int from,int to){   //链式前向星存图
    e[++tot].from=from;
    e[tot].to=to;
    e[tot].next=head[from];
    head[from]=tot;
}
int n,m,u,v,t[200010],ans[200010],f[200010];
inline int _find(int x){            //查询+路径压缩
    while(x!=f[x]) x=f[x]=f[f[x]];
    return x;
}
inline void init(){                 //并查集初始化
    for(register int i=1;i<=n;i++)
        f[i]=i;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(register int i=1;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        add_edge(u,v);              //无向图双向存边
        add_edge(v,u);
    }
    for(register int i=1;i<=n;i++)
        scanf("%d",&t[i]);          //农场关的时间，反着看就是开的时间
    init();                         //定义了函数……记得用
    vis[t[n]]=1;                    //t_n时开了农场 t[n]，标记
    ans[n]=1;                       //只开了一个时图必定是联通的
    for(register int i=n-1;i>=1;i--) //反着搜，第i 时刻开了农场t[i]
    {
        vis[t[i]]=1;                //标记
        for(register int j=head[t[i]];j;j=e[j].next)
        {
            if(vis[e[j].to]==1)      //如果该边终点农场也开了，执行如下语句
            {
                int fx=_find(t[i]),fy=_find(e[j].to);//并查集查询
                if(fx!=fy)     //不在同一个集合的话
                {
                    ++k;       //合并次数 +1 
                    f[fx]=fy;  //合并两个集合
                }
            }
        }
        if(k==n-i) ans[i]=1;   //当前开了n-（i-1）个农场，判断是否连通，储存答案
        else ans[i]=0;
    }
    for(register int i=1;i<=n;i++)
    {
        if(ans[i]==1) printf("YES\n");  //打印答案
        else printf("NO\n");
    }
    return 0;
}

```
**若有地方没看懂可以私信我**  
**若写的不好还请大家的体谅**  
**若有错的地方还望大家指出**  
**谢谢各位的支持~**
**最后，Meteorshower_Y在这里祝福大家RP++，Score++**

---

## 作者：袁宇轩 (赞：8)

[题目传送门](https://www.luogu.com.cn/problem/P6121)

判断是否联通自然想到并查集。

但不过此题是要在图中删点，这一点用并查集来完成比较困难。

那何为并查集？当然有两大功能：合并和查找。那我们不妨把删点操作转换成合并。

就以样例为例：

```cpp
4 3
1 2
2 3
3 4
3
4
1
2
```
我们一共有4个点，然后依次要删点3、4、1、2，那么我们可以假设原本图中一个点都没有，然后依次加点2、1、4、3，并把与它相关的点连起来，查找集合的个数，如果只有一个集合，则当前全联通。

上代码，具体细节见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define For(i,j,k) for(int i=(int)(j);i<=(int)(k);i++)
#define Rep(i,j,k) for(int i=(int)(j);i>=(int)(k);i--)
inline ll read(){
	ll x=0;char ch=getchar();bool f=0;
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=1;
	for(;isdigit(ch);ch=getchar()) x=x*10+ch-'0';
	return f?-x:x;
}
void write(ll x){
	if(x<0) putchar('-'),x=-x;
	if(x>=10) write(x/10);putchar(x%10+'0');
}
void writeln(ll x){write(x);puts("");}
void writep(ll x){write(x);putchar(' ');}
int const N=200000+3;
int n,m,cnt,k,h[N<<1],fa[N<<1],a[N<<1],ans[N<<1],vis[N<<1];
struct edge{
	int to,nt;
}e[N<<1];
void add(int x,int y){//此处存边用到前向星，用vector也可以 
	e[++cnt].nt=h[x];
	e[cnt].to=y;
	h[x]=cnt;
}
int find(int x){//基本并查集路径压缩操作 
	return x==fa[x]?x:fa[x]=find(fa[x]);
}
int main(){
	n=read();m=read();
	for (int i=1;i<=n;i++) fa[i]=i;
	for (int i=1;i<=m;i++){
		int x=read(),y=read();
		add(x,y);
		add(y,x);//把边记录下来 
	}
	for (int i=1;i<=n;i++)
	  a[i]=read(),vis[a[i]]=1;//记录删掉的点 
	int sum=0;//当前图中集合个数 
	for (int i=n;i>=1;i--){//从后往前加点 
		sum++;//每次加点意味着会多出来一个独立的集合 
		int u=a[i];
		for (int j=h[u];j;j=e[j].nt){//加上与该点相关的边 
			int v=e[j].to;
			if (find(u)!=find(v) && !vis[v]) fa[find(u)]=find(v),sum--;//两个点要不同的集合，且都没有被删除，那么集合会少一个 
		}
		vis[u]=0;//将点从删掉点的集合中取出，表示该店已在图中 
		ans[i]=sum;//记录答案 
	}
	for (int i=1;i<=n;i++)
	  if (ans[i]==1) puts("YES");//判断是否全联通 
	  else puts("NO");
	return 0;
}
```


---

## 作者：AuCloud (赞：2)

# 并查集

显然暴力删边不怎么可做（吧

于是想象一下Farmer John旅行回来之后逆序地一个一个把谷仓重新开起来（？

就变成了一道裸的并查集了

最后倒序输出答案就行

~~或者直接倒着存~~

~~双倍经验[P1197 [JSOI2008]星球大战](https://www.luogu.com.cn/problem/P1197)~~

唯一的差别是一个求的是连通块个数是否为一，一个要输出连通块的个数，思路都是减边->加边

```cpp
#include <bits/stdc++.h>
using namespace std;
int used[200001], q[200001], fa[200001], ans[200001];
int head[200001], nxt[400001], to[400001], tot;
void add(int x, int y)
{
    nxt[++tot] = head[x];
    head[x] = tot;
    to[tot] = y;
}
int find(int x)
{
    if(fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}
int main()
{
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= m; i++)
    {
        int x, y;
        cin >> x >> y;
        add(x, y);
        add(y, x);
    }
    for(int i = 1; i <= n; i++)
        fa[i] = i;
    for(int i = 1; i <= n; i++)
    {
        cin >> q[i];
    }
    int sum = 0;
    for(int i = n; i >= 1; i--)
    {
        sum++;
        used[q[i]] = 1;
        int fx = find(q[i]);
        for(int j = head[q[i]]; j; j = nxt[j])
        {
            int y = to[j];
            int fy = find(y);
            if(fx != fy)
            {
                fa[fy] = fx;
                if(used[y]) sum--;
            }
        }
        if(sum == 1) ans[i] = 1;
    }
    for(int i = 1; i <= n; i++)
    {
        cout << ((ans[i] == 1) ? "YES\n" : "NO\n");
    }
    return 0;
}

```

---

## 作者：dzdolrc (赞：2)

## 算法选择
首先我们拿到题目，发现是求连通问题的，那我们首先会想到**并查集**和**tarjan**。但是由于数据范围的原因我们选用并查集（方便统计连通块个数）。


## 操作难点
对于题目中涉及的操作传统的并查集只支持合并，但是不支持删点的操作。题目中提到
```
当一个谷仓被关闭了，所有的连接到这个谷仓的道路都会被关闭，而且再也不能够被使用。
```

所以我们可以转换一下思路，将删点的操作变为**倒序加点**的操作。

例如：

```
删点：1,2,3,4

可转换为反向加点：4,3,2,1

比如我在删点1时，实际上点2,3,4还在(也就是时候我加点4,3,2时相当于删掉点1)。当我删点2时，点3,4还在（也就是时候我加点4,3时相当于删掉点1和点2)。
```
以此类推即可证明**正序删点=倒序加点**的正确性。

## 思维过程
我们可以先假设原来的图是空的，每加上一个新的点，先把连通块数加$1$。再扫描与这个点相连的所有边。如果连接的点已经被加过了（即已经在图上），那么说明这两个连通块可以合并为一个连通块，那么连通块的个数就减$1$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int M=2e5+5;
bitset <M> check,ans;
int pre[M],n,m,head[M],cnt,cl[M],sum;
struct pp{
	int to,next;
}p[M*2-5];
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
void add(int x,int y){
	p[++cnt].to=y;
	p[cnt].next=head[x];
	head[x]=cnt;
}
int f(int x){
	if(pre[x]==x) return x;
	else return pre[x]=f(pre[x]);
}
int main(){
	n=read();
	m=read();
	for(int i=1;i<=n;i++) pre[i]=i;
	for(int i=1;i<=m;i++){
		int x,y;
		x=read();
		y=read();
		add(x,y);add(y,x);//双向建边
	}
	for(int i=1;i<=n;i++) cl[i]=read();//先读入要关闭的农场
	for(int i=n;i>=1;i--){//倒序加点
		sum++;//假设多一个连通块，后面再判断是否能合并
		check[cl[i]]=1;//该点被加上（注意，这是加点操作），标记
		for(int j=head[cl[i]];j;j=p[j].next){//查看该点的边
			int l=f(cl[i]),r=f(p[j].to);//查看两点是否在同一连通块内
			if(check[p[j].to]&&l!=r){//如果能链接且在图上
				pre[l]=r;//链接
				sum--;//少一个连通块
			}
		}
		if(sum==1) ans[i]=true;//只有一个连通块，全部连通，记录答案
	}
	for(int i=1;i<=n;i++){
		if(ans[i]) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
}
```


---

## 作者：FutureThx (赞：2)

一道关于并查集非常好的练手题。
## 题意
一个无向图，给出删去点的顺序，求每次删完点图是否联通。

## 思路
首先删点我们知道要非常的麻烦，这个时候就可以使用一个十分有用的技——**反向建边**。
$ $

所谓反向建边，也就是**将正序删点（边）变为反序加点(边)** ，就比如说样例中：
```
4 3
1 2
2 3
3 4
3
4
1
2
```
样例中先后删去了 $3,4,1,2$ ,通常思路就是将关于第 $i$ 个点的所有直接联系的边删去，那我们按照上面的思路改为**将 $2,1,4,3$中第 $i$个节点的所有的直接联系并且已经被加上的点建立起来，查找联通块是否为 $1$ ,是输出 $YES$ ，否则输出 $NO$**, 其中使用**并查集**进行建立和查找联通块 ，稍稍整理一下思路，希望同学们可以借鉴思路而不是借鉴代码：
```
读入数据
将删点顺序从后往前扫:
     记录 node[i] 节点已经建立
     联通块个数加1
     扫描有关 node[i] 节点的所有边:
          如果边的另一端的节点 node[j] 已经建立:
              并查集合并 node[i] 节点与 node[j]
              联通块个数减1
     判断联通块个数是否为1:
           正假处理
输出数据
```
## 代码
```cpp
#include <cstdio>
using namespace std;
#define MAX_N_M 200001
const int treem = 30;
struct tree1{
    int father = -1;
    int node_out[treem],out_t = 0;
}node[MAX_N_M];
int built[MAX_N_M],n,m;
bool win[MAX_N_M],state[MAX_N_M];
void read();
void deal_with();
int find_father(int x);
inline int read_int();
int main(){
    read();
    deal_with();
    return 0;
}
void read(){
    n = read_int();
    m = read_int();
    for(int i = 1;i <= m;i++){
        int x,y;
        x = read_int();
        y = read_int();
        node[x].out_t++;
        node[x].node_out[node[x].out_t] = y;
        node[y].out_t++;
        node[y].node_out[node[y].out_t] = x;
    }
    for(int i = 1;i <= n;i++)
        built[i] = read_int();
}
void deal_with(){
    int Connected_num = 0;
    for(int i = n;i >= 1;i--){
        state[built[i]] = 1;
        Connected_num++;
        for(int j = 1;j <= node[built[i]].out_t;j++){
            if(state[node[built[i]].node_out[j]] == 1){
                if(find_father(built[i]) != find_father(node[built[i]].node_out[j])){
                   node[find_father(built[i])].father = find_father(node[built[i]].node_out[j]);
                   Connected_num--;
                }
            }
        }
        if(Connected_num != 1)win[i] = 1;
    }
    for(int i = 1;i <= n;i++){
        if(win[i] == 1)
          printf("NO\n");
        else
          printf("YES\n");
    }
}
int find_father(int x){
    if(node[x].father == -1)
       return x;
    return node[x].father = find_father(node[x].father);
}
inline int read_int()
{
	int X=0; bool flag=1; char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') flag=0; ch=getchar();}
	while(ch>='0'&&ch<='9') {X=(X<<1)+(X<<3)+ch-'0'; ch=getchar();}
	if(flag) return X;
	return ~(X-1);
}
```
代码易懂，大佬勿喷
## 后记
$Updata \ 2020.9.1 :$ 完成题解，求管理员通过

---

## 作者：Poetic_Rain (赞：2)

~~趁这道题还没几个人发，赶紧水一篇题解~~

首先这道题就是很正常地给你几条边，需要连起来，这么看来还是很符合并查集的。但是往后看，还要删点，这种操作并查集是很少的，不好弄。但是并查集的合并好搞啊，我们就想着把删除换位合并

其他大佬的题解也都讲了，我们倒序枚举删点的操作，相当于从后往前每次合并点，再去判断加了这个点之后是否连通。如果全部连通的话，那联通块数量为1的话，那就说明联通了；大于1的话，说明肯定有些地方被分开了

然后各位大佬都是用的链式前向星存储的边，我这个蒟蒻就用vector存边，但是考试还是最好用链式前向星，能不用STL就不用STL，虽然STL确实很香

```
#include<bits/stdc++.h>
using namespace std;
vector<int> e[200005];
int f[200005];
int m,n;
int find(int x){
	if(f[x]==x) return x;
	return f[x]=find(f[x]);
}
int merge(int x,int y){
	if(find(x)==find(y)) return 0;
	f[find(x)]=find(y);
	return 1;
}  //标准的并查集操作 
int l,r;
int del[200005]; //删除的点 
int sum; //联通块数量 
bool ok[200005]; //是否全部连通 
int main(){
	scanf("%d%d",&n,&m);
	for(register int i=1;i<=m;i++){
		scanf("%d%d",&l,&r);
		e[l].push_back(r);
		e[r].push_back(l);
	} //vector存储边，是双向存储 
	for(register int i=1;i<=n;i++) scanf("%d",&del[i]);
	for(register int i=n;i>=1;i--){ //倒序枚举删除点 
		int x=del[i];
		f[x]=x; //初始化 ，如果在之前全部初始化了，不好判断是否枚举过 
		++sum; //加一个点，联通块数量++，之后再进行操作 
		for(vector<int>::iterator it=e[x].begin();it!=e[x].end();it++){
			int y=*it;
			if(!f[y]) continue; //如果还没有加这个点，因为之前的初始化 
			sum-=merge(x,y); //如果可以连通，合并之后联通块-- 
		}
		if(sum<=1) ok[i]=true; //联通块为1的话，说明全部连通 
	}
	for(register int i=1;i<=n;i++){ //正序输出 
		if(ok[i]==true) puts("YES");
		else puts("NO");
	}
	return 0;
}
```


---

## 作者：No_wonder (赞：2)

初看这道题，我们想到这是一个图，我们要维护它是否是全联通的。

每一次去点的操作后，图的连通性都会发生改变，这么一来，我们在每一次操作后都要来维护一遍，开销过于庞大，用传统的bfs的方法会飙到$O(n^2)$，当然可能有更快的算法，不过这里不做讨论。

询问图联通的问题是很经典的，我们尝试用熟悉的冰茶姬（并查集）去做，但发现冰茶姬是做不了删除操作的。

我们开动右脑的逆向思维细胞，发现这道题可以离线处理，一共N个点删除N次，从后往前看的话其实是一个不断的加点操作，我们只需要倒序枚举然后用并查集观察图的连通性就可以。

我这里选择了记录合并次数。倒序枚举i时，我们有的点一共是n-i个。因为刚开始半个点都没有，所以当且仅当图是全联通的情况下，合并次数才会等于点数，这就是那个判断的含义。
这里如果有问题的话，可以在私信里向我提问
```cpp
	for(ri i=n;i>=1;i--)			//倒序枚举 
	{
		vis[open[i]]=1;
		int u=open[i];
		for(ri j=head[u]; j; j=e[j].next)
		if(vis[e[j].to])			//维护连通性 
		{
			int v=e[j].to;
			if(find(u)!=find(v))
			{
				sum++;				//记录合并次数 
				un(u,v);
			}
		}
		if(sum==n-i)	ans.push("YES\n");
		else			ans.push("NO\n");	
	}
```


我这里脑子抽了用了一个栈去存储答案，实际上有很大的可能会爆空间，仅做参考。

以下是AC代码

```cpp
#include<bits/stdc++.h>
#include<stack>
#define ri register int
using namespace std;
struct Edge{
	int to;
	int next;
}e[400040];
int fa[200020];
int n,m;
int head[200020],cnt;
int open[200020],vis[200020],sum;
stack <string> ans;
void add_edge(int from,int to)
{
	e[++cnt].to=to;
	e[cnt].next=head[from];
	head[from]=cnt;
}
int find(int x)
{
	return (x==fa[x])?x:fa[x]=find(fa[x]);
}
void un(int x,int y)
{
	fa[find(x)]=find(y);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(ri i=1;i<=n;i++)			//初始化冰茶姬 
	fa[i]=i;
	for(ri i=1;i<=m;i++)			//存图 
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add_edge(x,y);
		add_edge(y,x);
	}
	for(ri i=1;i<=n;i++)
	scanf("%d",&open[i]);
	for(ri i=n;i>=1;i--)			//倒序枚举 
	{
		vis[open[i]]=1;
		int u=open[i];
		for(ri j=head[u]; j; j=e[j].next)
		if(vis[e[j].to])			//维护连通性 
		{
			int v=e[j].to;
			if(find(u)!=find(v))
			{
				sum++;				//记录合并次数 
				un(u,v);
			}
		}
		if(sum==n-i)	ans.push("YES\n");
		else			ans.push("NO\n");	
	}
	while(!ans.empty())
	{
		cout<<ans.top();
		ans.pop();
	}
}
```



---

## 作者：mot1ve (赞：1)

并查集套路题，正着删边可以转化为反着加边，注意，一条道路可以通行的条件是这条边的两端点的谷仓都开着，因为只要有一个关着，这条道路就被关了。所以合并的条件是两端点谷仓都得开着。

如何判断全联通呢？我们每合并一次， $tot$ 就加一，如果 $tot=n-i$ ，也就是 $i$ 个谷仓可以构成一个连通图了，那么就满足要求了。这里因为我们是从后往前操作的，所以输出答案的时候也要倒着输出。

```
#include<bits/stdc++.h>
using namespace std;
int n,m,idx,tot;
int head[200010],t[200010],ok[200010],fa[200010];
struct node{
	int nxt,to;
}edge[400010];
vector<int> g;
void add(int u,int v)
{
	edge[++idx].nxt=head[u];
	edge[idx].to=v;
	head[u]=idx;
}
int find(int x)
{
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
    }
	for(int i=1;i<=n;i++)
	{
		fa[i]=i;
		scanf("%d",&t[i]);
	}
	for(int i=n;i>=1;i--)
	{
		ok[t[i]]=1;//开 
		for(int j=head[t[i]];j;j=edge[j].nxt)
		{
			int v=edge[j].to;
			if(ok[v])
			{
				int fx=find(t[i]);
				int fy=find(v);
				if(fx==fy)
				continue;
				fa[fx]=fy;
				tot++;
			}
		}
		if(tot==n-i)//如果当前
		g.push_back(1);
		else g.push_back(2);
	}
	reverse(g.begin(),g.end());
	for(int i=0;i<g.size();i++)
	{
		if(g[i]==1)
		puts("YES");
		else puts("NO");
	}
	return 0;
}

---

## 作者：LikC1606 (赞：1)

## 题意:
这个农场一共有被用 M条双向道路连接的 N个谷仓，题目会先输入M条双向的边，再输入这N个谷仓的关闭顺序，判断N次关闭后是否是连通图。
## 做法：
这题用并查集和链表两个数据结构，链表用来存各个点的边，并查集是用来判断所有点是不是连通的。如果一开始就存好了整个图，边删除边边判断是否连通的话比较难，我们可以用倒着来的方法来判断，题目就变成了边加点边判断，就会简单许多。
## 并查集
并查集目前我会的就是两个函数和两个数组，father[x]表示x的父节点是什么，不知道的可以看书，这里不详细介绍了。size[x]表示这个连通块的节点数量。find（x）就是求x所处的这棵树的根节点，如果x和y用find（x）后的值是一样的，那么他们就处于同一个连通块中，还有一个merge（x,y）函数，就是把x和y这两个树有一个边，那么就把他们结合，形成一个连通块，详细做法可以参考我的程序（写的不是很好，也是个新手）。
## 程序
```cpp
#include<bits/stdc++.h>
using namespace std;
int tot,head[200005],to[400010],ne[400010];
int d[200005];
int father[200005],size[200005];
int ok[200005];
void jiabian(int x,int y)
{
	++tot;
	to[tot]=y;
	ne[tot]=head[x];
	head[x]=tot;
}//链表存边，刚学会，用的还是模板 
int find(int x){return x==father[x]?x: father[x]=find(father[x]);}//find函数，用到了路径压缩，就是在寻找根节点的过程中将这个树的高度减少 
int merge(int x, int y)
{
	x=find(x);
	y=find(y);
    if(x==y) return 0;//先寻找两个节点的根节点，如果一样，那么就处于同一个连通块，就不用减少连通块的总数了 
    if(size[x] < size[y])
       father[x]=y,size[y]+=size[x];
    else father[y]=x,size[x]+=size[y];
    return 1; 
}//结合 
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	int a,b;
	for(int i=1;i<=m;++i)
	    scanf("%d%d",&a,&b),jiabian(a,b),jiabian(b,a);//双向的 
	for(int i=1;i<=n;++i)
	    scanf("%d",&d[i]);
	int k=0;//记录当前连通块的数量 
	for(int i=n;i>=1;--i)
	{
		int x=d[i];
		father[x]=x;
		size[x]=1;
		++k;
		for(int j=head[x];j;j=ne[j])
		{
			int y=to[j];
			if(!father[y]) continue;//如果这个点还没有被加入，就直接跳过 
			k -= merge(x, y); 
		}
		if(k<=1) ok[i]=1; 
	}
	for(int i=1;i<=n;++i)
		puts(ok[i]? "YES":"NO");
	return 0;
 } 
```


---

## 作者：wfycsw (赞：0)

本题其实就是一个**并查集模板题**，只是需要稍微转换一下思路。

所谓并查集，就是一个合并与查找的集合，并查集合并节点时非常容易，但是删除节点时就很复杂了！而本题中的**关闭农场**，其实就是要我们**删除节点**。于是，我们便可以同一种逆序思想：假设每个农场先**都是关闭的**（即有n个连通块），当打开一个农场时我们再**连这个农场与之前打开的农场有关的边**，这样就方便多了。如果看不懂，待会儿可以看代码。

至于连边的话，我们用链式前向星存图，用并查集判断两节点是否在一个连通块中，即**其父亲是否相同**。代码如下：

```cpp
inline int find(int x){return x==f[x]?x:f[x]=find(f[x]);}//并查集标椎函数
inline void ff(int u){//连边找父亲（find father）
	p=find(u);
	for(RI i=h[u];i;i=a[i].n){
		v=a[i].t;
		if(!b[v]){//判断此农场是否已经打开
			q=find(v);
			if(p!=q) f[q]=p,--now;//父亲不同则变为相同，连通块个数减1。
		}
	}
}
```
接着是逆序打开农场：
```cpp
for(RI i=1;i<=n;i=-~i) f[i]=i,b[i]=1;//初始化，所有农场的先关闭。
for(RI i=n;i>0;--i){
		b[gb[i]]=0;//打开此农场
		ff(gb[i]);//连边
		ans[i]=now-i+1;//答案为现存连通块数减去关闭的农场个数，因为是每一次关闭谷仓之前的连通块数量，所以要加1。
	}
```

```cpp
#include<bits/stdc++.h>
#define RI register int
using namespace std;
const int N=2e5+3;
struct wu{
	int n,t;
}a[N<<1];
int f[N],t,h[N],gb[N],ans[N],u,v,p,q,now;bool b[N];
inline int find(int x){return x==f[x]?x:f[x]=find(f[x]);}
inline void add(int u,int v){
	t=-~t;a[t].t=v;
	a[t].n=h[u];h[u]=t;
}
inline void ff(int u){
	p=find(u);
	for(RI i=h[u];i;i=a[i].n){
			v=a[i].t;
			if(!b[v]){
				q=find(v);
				if(p!=q) f[q]=p,--now;
			}
		}
}
int main(){
	RI n,m,k;
	scanf("%d%d",&n,&m);now=n;
	for(RI i=1;i<=m;i=-~i){
		scanf("%d%d",&u,&v);
		add(u,v);add(v,u);//注意是双向边
	}
	for(RI i=1;i<=n;i=-~i)
		scanf("%d",&gb[i]);
	for(RI i=1;i<=n;i=-~i) f[i]=i,b[i]=1;
	for(RI i=n;i>0;--i){
		b[gb[i]]=0;
		ff(gb[i]);
		ans[i]=now-i+1;
	}
	for(RI i=1;i<=n;i=-~i)
		puts(ans[i]==1?"YES":"NO");//全连通时连通块的个数为1
	return 0; 
}
```

---

