# 校园网络【[USACO]Network of Schools加强版】

## 题目背景

浙江省的几所 OI 强校的神犇发明了一种人工智能，可以 AC 任何题目，所以他们决定建立一个网络来共享这个软件。但是由于他们脑力劳动过多导致全身无力身体被♂掏♂空，他们来找你帮助他们。


## 题目描述

共有 $n$ 所学校 $(1 \leq n \leq 10000)$ 已知他们实现设计好的网络共 $m$ 条线路，为了保证高速，网络是单向的。现在请你告诉他们至少选几所学校作为共享软件的母机，能使每所学校都可以用上。再告诉他们至少要添加几条线路能使任意一所学校作为母机都可以使别的学校使用上软件。


## 说明/提示

~~POJ 原题。数据扩大了 $100$ 倍。~~

~~$1 \leq $ 边数 $\leq 5000000$，$1 \leq n \leq 10000$ 。~~

实际上，$1 \leq n \leq 10000$，$1\le $ 边数 $\le 50000$。

## 样例 #1

### 输入

```
5
2 0
4 0
5 0
1 0
0
```

### 输出

```
2
2```

# 题解

## 作者：「QQ红包」 (赞：22)

tarjan的模板题（嗯可以看lrj的书


-第一问：至少要给多少个学校软件，才能保证所有学校都有软件用，也就是求缩点后入度为0的点的个数（因为入度为0的话没有其他学校能传软件给它）

-第二问：使缩点后所有学校的入度和出度都大于0（这样就可以给任意学校软件，然后所有学校都能用上软件


**如果是一个强连通图需要特判。**


```cpp
/*
ID: ylx14271
PROG: schlnet
LANG: C++
*/
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<stack>
#include<cstdio>
using namespace std;
int read()
{
    char ch=getchar();
    int x=0;
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar(); 
    return x;
}
int s[20100],top;
int low[21000];//存能搜到的最早的点 
int pre[21000];//存自己的时间 
int dfs_clock; 
struct node
{
    int x,y,d;
} a[4000000];
int po[21000],m;
int n,x1;
int scc[21000],id;
int c[21000];//出度 
int r[21000];//入度 

void dfs(int u)
{
    top++;
    s[top]=u;
    low[u]=++dfs_clock; //存自己的时间和 
    pre[u]=dfs_clock; 
    for (int i=po[u];i!=0;i=a[i].d)
    {
        int v=a[i].y;//提出点 
        if (pre[v]==0)//没有扫过 
        {
            dfs(v);//扫一遍 
            low[u]=min(low[u],low[v]);//更新 
        } else
        if (scc[v]==0)//如果在别的联通块就不管了 
        {
            low[u]=min(low[u],pre[v]);
        }
    }
    int k; 
    if (pre[u]==low[u])//自己是自己的祖先（也就是扫不到时间更早的点了 
    {
        id++;
        while (1)
        {
            k=s[top];top--;
            scc[k]=id;
            if (k==u) break;
        }
    }
}
int main()
{
    freopen("schlnet.in","r",stdin);
    freopen("schlnet.out","w",stdout);
    n=read();
    for (int i=1;i<=n;i++)
    {
        x1=read();
        while (x1!=0)
        {
            m++;
            a[m].x=i;
            a[m].y=x1;
            a[m].d=po[a[m].x];
            po[a[m].x]=m;
            x1=read();
        }
    }//读入 
    for (int j=1;j<=n;j++)
    {//因为并不一定是个连通图，so 
        if (pre[j]==0) dfs(j);
    }
    for (int i=1;i<=m;i++)
    {
        if (scc[a[i].x]!=scc[a[i].y])//自己图内不管 
        {
            c[scc[a[i].x]]++;//x的出度+1 
            r[scc[a[i].y]]++;//y的入度+1 
        }
    } 
    int ans1=0;
    int ans2=0;
    for (int i=1;i<=id;i++)//统计出度入度为0的点的出现次数 
    {
        if (r[i]==0) ans1++;
        if (c[i]==0) ans2++;
    }
    ans2=max(ans2,ans1);//第二问，所有点要出度不为0而且入度不为0 
    if (id==1) ans1=1,ans2=0;//嗯要特判 
    printf("%d\n%d\n",ans1,ans2);
    return 0;
}
```

---

## 作者：Mine_King (赞：9)

这题，直接处理是很麻烦的。我们需要Tarjan缩点，然后他就变成了一个DAG。之后，我们再来看题目要我们求什么。   
（声明：下面所有提到的点啊，入度啊，出度啊，都是指在缩完点的图上的。）

第一问，可以发现其实就是求入度为0的点的个数。    
而第二问呢，就是问还要多少条边使得他成为**一个**强连通分量。而要加的边数其实就是入度为0的点的个数和出度为0的点的个数中较大的那个。    
注意，这里需要特判本来就是一个强连通分量的情况，也就是输出`1\n0`的情况。

另外在求的过程中我们不需要知道缩完点后的图长什么样，自然也就不用存图啦~

**code：**
```cpp
#include<cstdio>
#include<stack>
#define MAXN 10005
#define MAXM 5000005
using namespace std;
int n;
int index,low[MAXN],dfn[MAXN];
stack<int>s;
int f[MAXN];
int scc_cnt,scc[MAXN];
int In,Out,in[MAXN],out[MAXN];
int max(int x,int y){return x>y?x:y;}
struct graph
{
	int tot,hd[MAXN];
	int nxt[MAXM],to[MAXM];
	void add(int x,int y)
	{
		tot++;
		nxt[tot]=hd[x];
		hd[x]=tot;
		to[tot]=y;
	}
}g;
void Tarjan(int x)
{
	dfn[x]=low[x]=++index;
	s.push(x);
	f[x]=true;
	for(int i=g.hd[x];i;i=g.nxt[i])
		if(!dfn[g.to[i]])
		{
			Tarjan(g.to[i]);
			low[x]=min(low[x],low[g.to[i]]);
		}
		else if(f[g.to[i]])
			low[x]=min(low[x],dfn[g.to[i]]);
	if(dfn[x]==low[x])
	{
		scc[x]=++scc_cnt;
		while(s.top()!=x)
		{
			scc[s.top()]=scc_cnt;
			f[s.top()]=false;
			s.pop();
		}
		f[x]=false;
		s.pop();
	}
	return ;
}//板子，不多说。
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int v;
		while(scanf("%d",&v)&&v) g.add(i,v);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i]) Tarjan(i);//先做Tarjan
	for(int i=1;i<=n;i++)
		for(int j=g.hd[i];j;j=g.nxt[j])
		{
			int u=scc[i],v=scc[g.to[j]];
			if(v!=u)//不在同一个强连通分量里
			{
				in[v]++;
				out[u]++;
                //记录他们的入度和出度
			}
		}
	for(int i=1;i<=scc_cnt;i++)
	{
		if(!in[i]) In++;
		if(!out[i]) Out++;
        //分别记录入度为0的点的数量和出度为0的点的数量
	}
	printf("%d\n",In);//第一问
	if(scc_cnt==1) printf("0");
	else printf("%d",max(In,Out));
    //第二问，记得特判
	return 0;
}
```
如果你不会Tarjan或者对代码里Tarjan那部分有什么不明白的，可以看[这里](https://www.luogu.com.cn/blog/195331/tarjan)。   
顺便[安利一下](https://www.luogu.com.cn/blog/195331/)我的博客~

---

## 作者：kradcigam (赞：8)

# 前置知识：

- [强联通分量](https://blog.csdn.net/qq_46230164/article/details/105406699)

# 分析

这道题的话，我们先考虑缩点。

不会缩点的可以看一下我的[文章](https://blog.csdn.net/qq_46230164/article/details/105406699)

既然我们缩好点了，那么整张图变成了一个 $DAG$（有向无环图）

这样就好处理了。

- 对于问题 `A`

	我们发现既然这整张图是 $DAG$，那么答案显然为入度为 $0$ 的点的个数
    
- 对于问题 `B`
	我们发现这整张图是 $DAG$。我们要把它变成连通图。
    
    连通图需要满足：
    - 没有入度为 $0$ 的点
    - 没有出度为 $0$ 的点
    
    考虑入度为 $0$ 和 出度为 $0$ 的点两两匹配，则需要匹配 $\max\{ \texttt{入度为}\ 0\ \texttt{的点},\texttt{入度为}\ 1\ \texttt{的点}$ 次。
    
# 一些细节

注意缩点后只有一个点的情况，本身就是连通的，所以 问题 `B` 的答案为 $0$

```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename T>inline void read(T &FF){
	T RR=1;FF=0;char CH=getchar();
	for(;!isdigit(CH);CH=getchar())if(CH=='-')RR=-1;
	for(;isdigit(CH);CH=getchar())FF=(FF<<1)+(FF<<3)+(CH^48);
	FF*=RR;
}
template<typename T>inline void write(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar('0'+x%10);
}
const int MAXN=1e6+10,MAXM=1e6+10;
int s[MAXN],stop,dfn[MAXN],low[MAXN],scccnt,sccnum[MAXN],dfscnt,tot,he[MAXN],ne[MAXM<<1],ed[MAXM<<1],n,x,se,es,du[MAXN],ud[MAXN];
void add(int x,int y){
	ed[++tot]=y;
	ne[tot]=he[x];
	he[x]=tot;
}
inline void tarjan(int now){
	dfn[now]=low[now]=++dfscnt;
	s[stop++]=now;
	for (int i=he[now];i;i=ne[i]){
		if(!dfn[ed[i]]){
			tarjan(ed[i]);
			low[now]=min(low[now],low[ed[i]]);
		}else if(!sccnum[ed[i]]){
			low[now]=min(low[now],dfn[ed[i]]);
		}
	}
	if(dfn[now]==low[now]){
		scccnt++;
		do{
			sccnum[s[--stop]]=scccnt;
		}while(s[stop]!=now);
	}
}//tarjin的板子
int main(){
	read(n);
	for(int i=1;i<=n;i++)
		while(cin>>x&&x)add(i,x);
	for(int i=1;i<=n;i++)
		if(!dfn[i])tarjan(i);
	for(int i=1;i<=n;i++)
		for(int j=he[i];j;j=ne[j])
			if(sccnum[i]!=sccnum[ed[j]]){
				du[sccnum[ed[j]]]++;//统计
				ud[sccnum[i]]++;//统计
			}
	for(int i=1;i<=scccnt;i++){
		if(!du[i])se++;//入度为0的点
		if(!ud[i])es++;//出度为0的点
	}
	cout<<se<<endl<<(scccnt==1?0:max(se,es));//小细节
	return 0;
}
```

---

## 作者：Kwork (赞：2)

这道题的wiki编号是1999，那么这里的第一个题解就非我莫属了~~作为题目贡献者发现没人做这一题有点郁闷，话说发题解能不能把这一题顶上去？你当是贴吧啊喂~~

这题的原形是POJ的一道强连通，而且数据异常水（n<=100），所以我就决定来点猛的直接扩大100倍。反正非暴力的正解都不虚这么点数据。

题意很明显，首先我们将图强连通分解，得到每个点的强连通编号，缩点，然后我们处理缩点后每个点的in\_degree和out\_degree。

第一问很明显是让我们求出in\_degree为0的强连通分量的数量，第二问，我们可以证明，最多只需要max(in\_degree==0的数量，out\_degree==0的数量）。

---------------------------------------------------------------------------------------------------------------------------------------

```cpp
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cmath>
#include <stack>
```
----------------------------------------------------------------------------------------------------------------------------------------
using namespace std;

----------------------------------------------------------------------------------------------------------------------------------------

const int maxn=10000+5;

----------------------------------------------------------------------------------------------------------------------------------------

```cpp
vector<int>G[maxn];
stack<int>s;
int n,Index=0,cnt=0,cmp[maxn],low[maxn],dfn[maxn];
bool ins[maxn];
```
---------------------------------------------------------------------------------------------------------------------------------------


```cpp
void add_edge(int u,int v){
    G[u].push_back(v);
    return;
}
void init(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        int u=i;int v;
        while(1){
            scanf("%d",&v);
            if(v==0) break;
            add_edge(u,v);
        }
    }
    return;
}
void tarjan(int u){
    dfn[u]=low[u]=++Index;
    ins[u]=true;
    s.push(u);
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else{
            if(ins[v]){
                low[u]=min(dfn[v],low[u]);
            }
        }
    }
    if(low[u]==dfn[u]){
        cnt++;
        int i;
        do{
            i=s.top();
            s.pop();
            ins[i]=false;
            cmp[i]=cnt;
        }while(i!=u);
    }
    return;
}
void scc(){
    memset(ins,false,sizeof(ins));
    memset(low,0,sizeof(low));
    memset(dfn,0,sizeof(dfn));
    for(int i=1;i<=n;i++)
        if(!dfn[i]) tarjan(i);
    return;
}
void calc(){
    if(cnt==1){
        printf("1\n");
        printf("0\n");
        return;
    }
    int in_num[maxn],out_num[maxn],ans1=0,ans2=0;
    memset(in_num,0,sizeof(in_num));
    memset(out_num,0,sizeof(out_num));
    for(int u=1;u<=n;u++){
        for(int i=0;i<G[u].size();i++){
            int v=G[u][i];
            if(cmp[u]!=cmp[v]){
                in_num[cmp[v]]++;
                out_num[cmp[u]]++;
            }
        }
    }
    for(int i=1;i<=cnt;i++){
        if(in_num[i]==0) ans1++;
        else if(out_num[i]==0) ans2++;
    }
    ans2=max(ans2,ans1);
    printf("%d\n%d",ans1,ans2);
    return;
}
void solve(){
    scc();
    calc();
    return;
}
int main(){
    init();
    solve();
    return 0;
}
```

---

## 作者：dbodb (赞：2)

tarjan 板子
以下几个数组

```c++
din[],dout[]分别统计入度和出度
dfn[],low[]记一下时间戳，和最早达到的时间
id[]记录每个点属于哪个联通块
siz[]记录每个联通块中点的个数
scc_cnt记录联通块的个数
```
这道题
问题一的解释

所有起点都无法由别的点到达，因此每个起点必须分配一个软件，而对于其他所有点，一定存在前驱，一定能由某一个起点走到，也就是说从所有起点出发，能遍历整个图。因此只需要给所有起点各一个软件即可。

问题二的解释

设缩点后的DAG中，起点（入度为0）的集合为P,终点（出度为0）的集合为Q，分以下两种情况讨论

1.|P|<=|Q|

① 若 |P|=1，则只有一个起点，并且这个起点能走到所有点，只要将每一个终点都向这个起点连一条边，那么对于图中任意一点，都可以到达所有点，新加的边数为 |Q|。

② 若 |P|≥2，则 |Q|≥|P|≥2，此时至少存在 2个起点 p1,p2，2 个终点 q1,q2满足 p1 能走到 q1 能走到 q2。（反证法：如果不存在两个起点能走到不同的终点，则所有的起点一定只能走到同一个终点，而终点至少有两个，发生矛盾，假设不成立）。
```c++
```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 10000+20, M = N * N;
int n;
int h[N], e[M], ne[M], idx, dfn[N], low[N], timestamp, stk[N], tt, id[N], siz[N], scc_cnt, din[N], dout[N];
bool in_stk[N]; 
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;}
void tarjan(int u) {
    dfn[u] = low[u] = ++timestamp;
    stk[++tt] = u, in_stk[u] = true;
    for (int i = h[u]; ~i; i = ne[i]) {int j = e[i];
		if (!dfn[j]) {tarjan(j);low[u] = min(low[u], low[j]);}
		else if (in_stk[j]) {low[u] = min(low[u], dfn[j]);}}
    if (dfn[u] == low[u]) {++scc_cnt;int v;
        do {v = stk[tt--];in_stk[v] = false;id[v] = scc_cnt;siz[scc_cnt]++;
        } while (v != u);}
} 
int main() {
    cin >> n;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i++) {
        int t;while (cin >> t, t) add(i, t);}
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) tarjan(i);}
    for (int i = 1; i <= n; i++) {
        for (int j = h[i]; ~j; j = ne[j]) {int k = e[j];int a = id[i], b = id[k];if (a != b) dout[a]++, din[b]++;}}
    int src = 0, des = 0;
    for (int i = 1; i <= scc_cnt; i++) {
        if (!din[i]) src++;
        if (!dout[i]) des++;}
    printf("%d\n", src);
    if (scc_cnt == 1) puts("0");
    else printf("%d\n", max(src, des));
    return 0;}

```





---

## 作者：青鸟_Blue_Bird (赞：1)

### upd:  发现我的原题解和加强版题解区中的大部分题解都没有加特判，在原题处无法通过，而加强版数据~~（有点水）~~可以通过，于是特此更新题解。

[题目戳这](https://www.luogu.com.cn/problem/P2812)

## 首先考虑问题一
---------------------------------------------------

不难想到，如果有一个学校作为终端机，那么跟其处于同一个强联通中的所有学校就可以不用作为终端机了。
那么，问题一也就迎刃而解了：找到所有入度为0的缩点。因为这个学校（强联通中至少有一个学校）必须作为终端机，毕竟它收不到别的学校传来的，只能自给自足。

## 然后考虑问题二

“任意一个学校都能作为母鸡”？试想一下，任意选取一个学校作为终端，要使得其余所有学校都能收到，只能是全图联通。因此，找到出度为0的缩点的个数就ok了。（即从出度为0的点连向入度为0 的点）

### 特判：注意只有一个强联通的情况，任务2应输出 0

不废话，上代码。细节已标好

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 5000010
#define orz 0

inline int read(){
	int x = 0, s = 1;
	char c = getchar();
	while(!isdigit(c)){
		if(c == '-')s = -1;
		c = getchar();
	}
	while(isdigit(c)){
		x = (x << 1) + (x << 3) + (c ^ '0');
		c = getchar();
	}
	return x * s;
} 

struct node{
	int u, v;
	int next;
} t[N];
int f[N];//日常邻接表 

int stac[N], top = 0;
int dfn[N], scc[N], low[N];
bool vis[N];
//tarjan 板子，不多说 
int in[N], out[N];//入度出度 
int ans1 = 0, ans2 = 0;

int bian = 0;
inline void add(int u, int v){
	t[++bian].v = v;
	t[bian].u= u;
	t[bian].next = f[u];
	f[u] = bian;
	return ;
}

int cac = 0, cnt = 0;
void tarjan(int now){//有向图强联通板子 
	dfn[now] = low[now] = ++ cac;
	stac[++top] = now;
	vis[now] = 1;
	for(int i = f[now]; i;i = t[i].next){
		int v = t[i].v;
		if(!dfn[v]){
			tarjan(v);
			low[now] = min(low[now], low[v]);
		}
		else if(vis[v])low[now] = min(low[now], dfn[v]);
	}
	if(dfn[now] == low[now]){
		int cur; 
		cnt++;
		do{
			cur = stac[top--];
			vis[cur] = 0;
			scc[cur] = cnt;
		}while(cur != now);
	}
	return ;
}

int main(){
	int n = read();
	for(int i = 1;i <= n; i++){
		int x = read();
		while(x){
			add(i, x);
			x = read();
		}
	}
	for(int i = 1;i <= n;i++)
		if(!dfn[i]) tarjan(i);//注意防止有的点漏掉 
	for(int i = 1;i <= bian; i++){ //统计所有的边 
		int u = t[i].u, v = t[i].v;
		if(scc[u] != scc[v]){//如果起点和终点不在同一个缩点  （即在两个缩点的交界处的边） 
			out[scc[u]]++;
			in[scc[v]]++;
		}
		
	}
	for(int i = 1;i <= cnt; i++){
		if(!in[i])ans1++;
		if(!out[i])ans2++;//统计 
	}
	if(cnt == 1) printf("1\n0");  /*记得特判呀*/ 
	else printf("%d\n%d", ans1, max(ans1, ans2));
	return orz;         //%一下CCF求AC 
}
```



---

## 作者：王雨阳 (赞：1)

### $Description:$
一些学校连接在一个计算机网络上，学校之间存在软件支援协议，每个学校都有它应支援的学校名单（学校A支援学校B，并不表示学校B一定要支援学校A）。

当某校获得一个新软件时，无论是直接获得还是通过网络获得，该校都应立即将这个软件通过网络传送给它应支援的学校。

因此，一个新软件若想让所有学校都能使用，只需将其提供给一些学校即可。

现在请问最少需要将一个新软件直接提供给多少个学校，才能使软件能够通过网络被传送到所有学校？

最少需要添加几条新的支援关系，使得将一个新软件提供给任何一个学校，其他所有学校就都可以通过网络获得该软件？

### $Solution:$

如果A能支援B， 那么就连一条从A到B的有向边。缩点之后，就变成了一个DAG。第一问，我们可以给每个入度为0的点一个新软件。

第二问：

假设入度为$0$的点集为$P$，出度为$0$点集为$Q$。并且假设$|P| \leq |Q|$

每加一条边，最多可以减少一个入度为$0$的点与一个出度为$0$的点。所以最少需要添加$|Q|$条边。

1.如果$|P| == 1$, 那么我们可以从每一个出度为$0$的点连一条边到入度为$0$点。

2.如果$|P| > 1$, 因为$|P| \leq |Q|$, 所以$2 \leq |P| \leq |Q|$.

那么，我们一定可以从$P$ 与 $Q$ 中找到四个点$p1, p2, q1, q2$, 使得   $p_1$可以走到$q_1$, $p_2$可以走到$q_2$.

所以，可以连一条从$q_1$到$p_2$的有向边。那么$|P'| = |P| - 1, |Q'| = |Q| - 1.$可以一直这样操作，一直到$|P| == 1$, 那么一共进行了$|P| - 1$次， 此时
$|Q'| = |Q| - (|P| - 1)$, 那么就回到了情况$1$，那么一共进行了$|Q| - (|P|-1) + (|P| - 1) = |Q|$.
```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int N = 1e4 + 10, M = 5e6 + 100;
struct Edge {
	int v, w, nxt;
} e[M];

int low[N], dfn[N], stk[N], in_stk[N], id[N], timestamp, top, scc_cnt;
int head[N], cnt, n;
bool inde[N], outde[N];

void AddEdge(int u, int v) {
	e[++cnt].v = v;
	e[cnt].nxt = head[u];
	head[u] = cnt;
}

void tarjan(int u)
{
	low[u] = dfn[u] = ++ timestamp;
	in_stk[u] = true, stk[ ++ top] = u;
	for(int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].v;
		if( !dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		}
		else if( in_stk[v])
		    low[u] = min(low[u], dfn[v]);
	}
	if( low[u] == dfn[u]) {
		int y;
		scc_cnt ++;
		do {
			y = stk[top --];
			in_stk[y] = false;
			id[y] = scc_cnt;
		} while( u != y);
	}
}

int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++) {
		int v;
	//	printf("u = %d\n", i);
		while(scanf("%d", &v) && v) {
			AddEdge(i, v);
	//		printf("%d ", v);
		}
//		puts("");
	}
	for(int i = 1; i <= n; i ++)
	    if( !dfn[i])  tarjan(i);
//	for(int i = 1; i <= n; i ++)  printf("%d ", id[i]);
//	puts("");
	for(int u = 1; u <= n; u ++) {
		for(int i = head[u]; i; i = e[i].nxt) {
			int x = id[u], y = id[e[i].v];
			if( x != y) inde[y] = outde[x] = true;
		}
	}

	int in_cnt = 0, out_cnt = 0;
	for(int i = 1; i <= scc_cnt; i ++) {
		if( inde[i] == 0)  in_cnt ++;
		if( outde[i] == 0)  out_cnt ++;
	}
	printf("%d\n", in_cnt);
	if( scc_cnt == 1) puts("0");
	else printf("%d\n", max(in_cnt, out_cnt));
	return 0;
}
```


---

## 作者：jins3599 (赞：1)

$tarjan$模板题目。

## 题目大意

给定一个有向图，求：

$1.$缩点后入度为$0$的点的个数。

$2.$缩点后的$dag$上，最少加多少条边使得整个图为一个强联通分量。

## 思路

问题一还是比较好写的，缩点后统计即可。

主要是问题二，我们来分类讨论一下。

如果这个$dag$是连通的，那么我们显然可以通过从出度为零的点向入度为零的点连边来达到整个图相互连通。

怎么连？一一匹配即可，多的也无妨，连到连完的入度/出度为零的点也可以。

我们记入度为零的点有$ind$个，出度为零的点为$outd$个

答案？显然是$max(ind,outd).$

我们考虑一下这个$dag$不连通的情况。

好像是和原来的情况类似，我们可以上一个图出度为零的点向下一个图入度为零的点连边，连通之后再重复上面连通$dag$的操作即可。

答案？好像还是$max(ind,outd).$

为什么？我们先假设这个连通的$dag$上入度和出度为零的点个数相同。

我们把入度为零和出度为零的点对一一匹配之后，我们思考下面的过程。

对于一对匹配的点对，显然这两个点对构成了一个环。

当从出度为零的点走到他对应的入度为零的点时，我们又可以从这个入度为零的点走到其它出度为零的点，从而，我们又可以走到其它出度为零的点对应的入度为零的点，从而，我们就可走全这整个$dag$了。

综上，这个题目就完成了。

$code:$
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 5000005;

struct Edge {
	int to , nxt;
}e[N];

int head[N] , cnt;
void add(int u , int v ) {
	e[++ cnt].to = v;
	e[cnt].nxt = head[u];
	head[u] = cnt;
}

int tot , dfn[N] , low[N] , top , st[N] , ins[N] , idx;
int wic[N];

void Tarjan(int now) {
	dfn[now] = low[now] = ++ idx;
	ins[now] = 1; st[++ top] = now;
	for(int i = head[now] ; i ; i = e[i].nxt) {
		int v = e[i].to;
		if(!dfn[v]) {
			Tarjan(v); low[now] = min(low[now] , low[v]);
		} else if(ins[v]) low[now] = min(low[now] , dfn[v]);
	}
	if(low[now] == dfn[now]) {
		int p;
		tot ++;
		do {
			p = st[top --];
			wic[p] = tot;
			ins[p] = 0;
		}while(p != now);
	}
}

int n , ind[N] , outd[N];
int main () {
	scanf("%d" , &n);
	for(int i = 1 ;  i <= n ; ++ i) {
		while(true) {
			int x; scanf("%d" , &x);
			if(!x) break; add(i , x);
			//printf("add %d -> %d\n" , i , x);
		}
	}
	for(int i = 1 ; i <= n ; ++ i) if(!dfn[i]) Tarjan(i);
	for(int i = 1 ; i <= n ; ++ i) {
		for(int j = head[i] ; j ; j = e[j].nxt) {
			int v = e[j].to;
			if(wic[v] == wic[i]) continue;
			ind[wic[v]] ++;
			outd[wic[i]] ++;
		}
	}
	int id = 0, od = 0;
	for(int i = 1 ; i <= tot ; ++ i) {
		if(!ind[i]) id ++;
		if(!outd[i]) od ++;
	}
	if(tot == 1) {
		printf("1\n0"); return 0;
	}
	printf("%d\n%d" , id , max(id , od));
	return 0;
}
```



---

## 作者：_Scaley (赞：1)


------------
我的第一篇题解~~

~~这个题大概是不难的~~  _ (:3 」∠) _

## 题面概括

有一张有向图，给出点的数量n以及边的数量m，有两个问题：

### problem1

至少选几个点开始搜索才能使整个图都能被遍历到

### problem2

至少需要添加几条边能使整个图成为一个环？

## 题目分析

这个题的难点在于，我们不知道连接哪两座学校才能使整个图成为一个环，那么我们可以先把一些小问题完成再去看大问题（佛系）

### 一、tarjan缩点
从题目可以得知如果这个图中有环，那这个环中若有至少一个点可以被共享，整个环就可以被共享，这就可以把一个环看做成一个点，可以用tarjan缩点完成

### 二、对入度为0的点和出度为0的点进行操作


------------


#### 子问题1：入度为0的点

如果在所有入度为0的点上设母机，那么整个图都会被共享

这也是problem1的答案

然后我们可以知道，缩点后的图是一个有向无环图，每个点都有一个入度和出度，入度为0的点无法被共享，那我们要想办法让这种点入度不为0呐~肯定要连边使入度为0的点的入度不为0 ~~（好绕）~~


#### 子问题2：出度为0的点

这样的话问题又来了：如果随便找个点连接入度为0的点的话，那连接入度为0的那个点的出度是否为0？

如果出度不为0，那么从这个点出发的点就无法在这个环里，以它为母机，会有学校共享不到，所以出度为零的点也需要向外连一条边

## 分析结果

不难想到，让出度为0的点向入度为0的点连一条边

那答案就出来了：

### problem1：

入度为0的点的个数


------------



### problem2：

max（入度为0的点的数量，出度为0的点的数量）:


------------



### **注意：当只有一个点（或者强连通分量时），输出0！！！（这个可能会成为强化数据）**


------------


更详细的请见完整代码

------------


## 完整AC代码
```c
#include <iostream>
#include <cstdio>
#include <cmath>
#define MAXN 10010
using namespace std;

int vis[MAXN], head[MAXN];
int js = 0, n, m, op=0, cnt, top=0;
int sta[MAXN], low[MAXN], dfn[MAXN];
int num[MAXN], sum[MAXN], g=0, oq=0;//num[i]记录点i的序号，sum[i]记录序号为i的强连通分量的元素个数
int rd[MAXN],cd[MAXN];//记录入度和出度

struct edge{
	int v, nxt;
}e[5000010 << 1];

void addage(int u, int v){
	e[++js].v = v;
	e[js].nxt = head[u];
	head[u] = js;
}

void tarjan(int t){//tarjan缩点板子
	sta[++top] = t;
	vis[t] = 1;
	low[t] = dfn[t] = ++op;
	for (int j = head[t]; j; j = e[j].nxt){
		int v = e[j].v;
		if (!dfn[v]){
			tarjan(v);
			low[t] = min (low[t], low[v]);
		}
		else if (vis[v])
			low[t] = min (low[t], low[v]);
	}
	if (low[t] == dfn[t]){
		int f = sta[top--];
		vis[f] = 0;
		num[f] = ++g;
		sum[g]++;
		while (f != t){
			f = sta[top--];
			vis[f] = 0;
			num[f] = g;
			sum[g]++;
		}
	}
}

int main(){
	int x, y, v, ans=0, jss=0,mm;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		while (scanf("%d", &x)){
			if (x == 0) break;
			addage(i, x);
		}
	}//输入
	for (int i = 1; i <= n; i++)
		if (!dfn[i]) tarjan(i);
	for (int i = 1; i <= n; i++){
		for (int j = head[i]; j; j = e[j].nxt){
			v = e[j].v;
			if (num[i] != num[v]){
				cd[num[i]]++;//记录每个点的入度
				rd[num[v]]++;//记录每个点的出度
			}
		}
	}
	for (int i = 1;i <= g; i++){
		if (!rd[i]){
			ans++;
		}//记录入度为0的点的数量
		if (!cd[i]){
			jss++;
		}//记录出度为0的点的数量
	}
	mm=max(ans,jss);//比较
	printf("%d\n%d\n",ans,mm);
	return 0;
}
```


------------


求管理员大大让我过审吧！！\(•ㅂ•)/♥

---

## 作者：Link_Space (赞：1)

刚学完tarjan之后做到了这道题，仔细一看，这不就是一个tarjan模板大水题吗！于是本蒟蒻立刻敲出了板子，自信满满测试样例的时候发现只输出了Problem 1，还有个Problem 2，也是本题最值得思考的，首先我们想，如何才能使任意选择一个母校，其他所有学校都能够用上软件？？？其实多想一想问题就迎刃而解了，你要让一个强连通分量与其他分量相连，就只需要让他们入度或者出度都不为0即可，于是Problem 2转化为了求入度为0的分量个数和出度为0的分量个数的较大值，所以直接求就好了，最后不要忘记特判一个当所有学校在一个强连通分量时，发一个软件就好了。

以下为AC代码，近乎tarjan板子

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int head[1000000];
int ver[1000000];
int nxt[1000000];
int cnt;
int dfn[1000000];
int low[1000000];
int idx;
int belong[1000000];
int Link[1000000];
int top;
int cnsta;
bool aim[1000000];
int in[1000000];
int out[1000000];
void add(int x,int y)
{
	nxt[++cnt] = head[x];
	head[x] = cnt;
	ver[cnt] = y;
}
void tarjan(int x)
{
	Link[++top]=x;
	dfn[x] = low[x] = ++idx;
	aim[x] = 1;
	for (int i = head[x]; i;i=nxt[i])
	{
		int v0 = ver[i];
		if(!dfn[v0])
		{
			tarjan(v0);
			low[x] = min(low[x], low[v0]);
		}
		else if(aim[v0])
		{
			low[x] = min(low[x], dfn[v0]);
		}
	}
	if(dfn[x]==low[x])
	{
		int w;
		cnsta++;
		do{
			w = Link[top--];
			aim[w] = 0;
			belong[w] = cnsta;
		} while (w != x);
	}
}
int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		int b;
		while(scanf("%d",&b)&&b)
		{
			add(i, b);
		}
	}
	for (int i = 1; i <= n; i++)
	{
		if(!dfn[i])
		{
			tarjan(i);
		}
	}
	int sumin = 0;
	int sumout = 0;
	for (int i = 1; i <= n;i++)
	{
		for (int j = head[i]; j;j=nxt[j])
		{
			int v0 = ver[j];
			if(belong[v0]!=belong[i])
			{
				in[belong[v0]]++;
				out[belong[i]]++;
			}
		}
	}
	for (int i = 1; i <= cnsta;i++)
	{
		if(in[i]==0)
			sumin++;
		if(out[i]==0)
			sumout++;
	}
	if(cnsta==1)
	{
		printf("1\n0");
		return 0;
	}
	printf("%d\n%d", sumin, max(sumin, sumout));
}
```


---

## 作者：SmallTownKid (赞：0)

做法大家基本一样，我详细证明一下为什么 $A$ 任务是找入度为0的点，$B$ 任务是找出度和入度为 $0$ 的点更多的那一个。

首先分析任务 $A$ ，至少选几所学校作为共享软件的母机，能使每所学校都可以用上。

缩点之后这个图就是一个 $DAG$ ， $DAG$ 有一个性质就是要想能遍历所有点，必须从每一个入度为 $0$ 的点出发，因为入度为 $0$ 的点没有其他边可以到达它，只有从它自己开始走才能遍历到它本身。而其他入度不为 $0$ 的点一定会被其他边遍历到。

然后分析任务 $B$ ， 至少要添加几条线路能使任意一所学校作为母机都可以使别的学校使用上软件。

也就是说让这个图成为一个强连通图，很显然，把 $DAG$ 变成一个强连通图我们可以从出度为 $0$ 的点连接到入度为 $0$ 的点，因为出度为 $0$ 的点谁也访问不到，肯定不满足我们任务 $B$ 的要求，那为什么连向入度为0的点就是最优解呢？因为入度不为 $0$ 的点一定可以被这条链上入度为 $0$ 的点访问到，连接了入度为 $0$ 的点一定也可以访问到这个入度为 $0$ 的点能访问到的所有点。

特判如果这个图是一个强连通图的情况。

顺便提一句，把各种图的性质背过并且理解对于提供图论题的思路有很大帮助。

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<stack>
using namespace std;
int dfn[10010],low[10010],vis[10010],color[10010],ru[10010],chu[10010];
stack<int> s;
int tot,cnt,n;
int head[10010];
struct node{
	int nxt,to;
}edge[5000010];
int idx;
void add(int u,int v)
{
	edge[++idx].nxt=head[u];
	edge[idx].to=v;
	head[u]=idx;
}
void tarjan(int x)
{
	dfn[x]=low[x]=++cnt;
	s.push(x);
	vis[x]=1;
	for(int i=head[x];i;i=edge[i].nxt)
	{
		int v=edge[i].to;
		if(!dfn[v])
		{
			tarjan(v);
			low[x]=min(low[x],low[v]);
		}
		else if(vis[v])
		{
			low[x]=min(low[x],dfn[v]);
		}
	}
	if(low[x]==dfn[x])
	{
		tot++;//哪种颜色 
		int y;
		do
		{
			y=s.top();
			s.pop();
			vis[y]=0;
			color[y]=tot;
		}while(x!=y);
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		while(1)
		{
			int u;
			scanf("%d",&u);
			if(!u)
			break;
			add(i,u);
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(!dfn[i])
		tarjan(i);
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=head[i];j;j=edge[j].nxt)
		{
			int v=edge[j].to;
			if(color[i]!=color[v])
			{
				ru[color[v]]++;
				chu[color[i]]++;
			}
		}
	}
	int ans1=0,ans2=0;
	for(int i=1;i<=tot;i++)
	{
		if(!ru[i])
		ans1++;
		if(!chu[i])
		ans2++;
	}
	if(tot==1)
	{
		cout<<1<<endl<<0;
		return 0;
	}
	cout<<ans1<<endl<<max(ans1,ans2);
	return 0;
} 

---

## 作者：chenzida (赞：0)

题意简述：给定一个图，第一问求在这里面选几个点就可以传递使每个点都被标记，第二问求要加几条边是这个变成强连通图。

思路解析：这道题的第一问显然很容易，就是将这个图缩点之后找入度为 $0$ 的点就行了。对于这个的正确性我就不证明了，因为这道题的重点在第二问，也就是对于一个图，最少加几条边能将它变成强连通图。

首先可以发现，强连通图必须没有一个点的入度或出度为 $0$，这是显而易见的，但是怎么证明没有一个点的入度或出度为 $0$ 的有向连通图 $(DAG)$ 就是强连通图呢？首先，因为它是 $DAG$ 所以我沿着任意一个结点走，它能到达任意一个结点，因为没有一个点的入度或出度为 $0$,所以这个定理得证。

所以我们的做法就是将这个图缩点，之后算出每个点的入度和出度，然后算出入度为 $0$ 以及出度为 $0$ 的点数，取一个 $max$ 就是了。我们的连边方法就是将一个出度为 $0$ 的点连向一个入度为 $0$ 的点即可。所以直接是 $max(in,out)$ 就是了。

步骤：

$1.$ $tarjan$ 缩点并建 $DAG$。

$2.$ 统计每个点的入度和出度，记为 $rd$ 和 $cd$。

$3.$ 做问题 $1$,即统计入度为 $0$ 的点。

$4.$ 做问题 $2$,即统计 $max(rd,cd)$。

最后上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=1e4+10;
const int MR=5e6+10;
struct Edge
{
	int to,next;
}e[MR],e_[MR];
int tot=1,tot_=1;
int rd[NR],cd[NR];
int head[NR],head_[NR];
int n,m,s;
int k,l;
int dfn[NR],low[NR];
int flag[NR],stack_[NR];
int c[NR],d[NR];
int cnt=0;
inline int read()
{
    int x=0,f=1; char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return x*f;
}
void add(int x,int y)
{
	e[tot].to=y;
	e[tot].next=head[x];
	head[x]=tot++;
}
void add_(int x,int y)
{
	e_[tot].to=y;
	e_[tot].next=head[x];
	head_[x]=tot_++;
}
void tarjan(int x)
{
	dfn[x]=low[x]=++k;
	stack_[++l]=x;
	flag[x]=1;
	for(int i=head[x];i;i=e[i].next)
	{
		int y=e[i].to;
		if(!dfn[y])
		{
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(flag[y])
		{
			low[x]=min(low[x],dfn[y]);
		}
	}
	if(dfn[x]==low[x])
	{
		int y=-1e9;
		if(!c[stack_[l]])cnt++;
		while(x!=y)
		{
			y=stack_[l--];
			flag[y]=0;
			if(!c[y])
			{
				c[y]=cnt;
				d[cnt]++;
			}
			
		}
	}
} 
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)
	{
		while(1)
		{
			int x=read();
			if(x==0) break;
			add(i,x);
		}
	}
	for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
	for(int i=1;i<=n;i++)
	{
		for(int j=head[i];j;j=e[j].next)
		{
			if(c[i]!=c[e[j].to])
			{
				add_(c[i],c[e[j].to]);
				rd[c[e[j].to]]++;
				cd[c[i]]++;
			}
		}
	}
	int ans=0;
	for(int i=1;i<=cnt;i++)
	{
		if(!d[i]) continue;
		if(rd[i]==0) 
		{
			ans++;
		}
	}
	printf("%d\n",ans);
	int rd_=0,cd_=0;
	int tmp=0;
	for(int i=1;i<=cnt;i++)
	{
		if(!d[i]) continue;
		if(rd[i]==0) rd_++;
		if(cd[i]==0) cd_++; 
	}
	if(d[1]==n) 
	{
		printf("0");
		return 0;
	}
	long long ans_=max(rd_,cd_);
	printf("%lld",ans_);
	return 0;
}
```

---

## 作者：寒鸽儿 (赞：0)

考虑缩点。  
对缩点后的图：  
会变成外向树/内向树森林,或者一堆 DAG。  
对于入度为0的点需要放一个文件。  
将入度为0和出度为0的点连边为最优的构建强连通图的策略。则第二个子问题的答案为入度为0与出度为0的点数目的最大值。  
注意特判缩点后成为一个点的情况。  
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 12345, M = 5678901;

int head[N], ver[M], nex[M], my[M], tot, n;
inline void addedge(int u, int v) {
	ver[tot] = v; nex[tot] = head[u]; my[tot] = u; head[u] = tot++;
}

int sta[N], dfn[N], low[N], co[N], top, col = 1, dfs_clock = 1;
void tarjan(int cur) {
	dfn[cur] = low[cur] = dfs_clock++;
	sta[top++] = cur;
	for(int i = head[cur]; ~i; i = nex[i])
	if(!dfn[ver[i]]) {
		tarjan(ver[i]);
		low[cur] = min(low[cur], low[ver[i]]);
	} else if(!co[ver[i]]) {
		low[cur] = min(low[cur], dfn[ver[i]]);
	}
	if(dfn[cur] == low[cur]) {
		while(sta[--top] != cur)
			co[sta[top]] = col;
		co[cur] = col++;
	}
}

int ind[N], outd[N];

int main() {
	memset(head, -1, sizeof(head));
	int tmp;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		while(~scanf("%d", &tmp) && tmp)
			addedge(i, tmp);
	}
	for(int i = 1; i <= n; ++i) if(!co[i]) tarjan(i);
	for(int i = 0; i < tot; ++i) {
		if(co[my[i]] != co[ver[i]]) {
			++ind[co[ver[i]]]; ++outd[co[my[i]]];
		}
	}
	int id0 = 0, od0 = 0;
	for(int i = 1; i < col; ++i) {
		if(!ind[i]) ++id0;
		if(!outd[i]) ++od0;  
	}
	if(col == 2) {
		printf("1\n0\n");
	} else {
		printf("%d\n%d\n", id0, max(id0, od0));
	}
	return 0;
}

```

---

## 作者：lzcjoe (赞：0)

### 题面

1515：网络协议

时间限制: 1000 ms 内存限制: 10240 KB

【题目描述】

出自 IOI 1996

一些学校连接在一个计算机网络上。学校之间存在软件支援协议。每个学校都有它应支援的学校名单（学校$a$支援学校$b$，并不表示学校$b$一定支援学校$a$）。当某校获得一个新软件时，无论是直接得到还是网络得到，该校都应立即将这个软件通过网络传送给它应支援的学校。因此，一个新软件若想让所有连接在网络上的学校都能使用，只需将其提供给一些学校即可。

任务

$a$. 请编一个程序，根据学校间支援协议（各个学校的支援名单），计算最少需要将一个新软件直接提供给多少个学校，才能使软件通过网络被传送到所有学校；

$b$. 如果允许在原有支援协议上添加新的支援关系。则总可以形成一个新的协议，使得此时只需将一个新软件提供给任何一个学校，其他所有学校就都可以通过网络获得该软件。编程计算最少需要添加几条新的支援关系。

【输入】

第一行是一个正整数$n$，表示与网络连接的学校总数。随后$n$行分别表示每个学校要支援的学校，即：$i+1$行表示第$i$号学校要支援的所有学校代号，最后$0$结束。

如果一个学校不支援任何其他学校，相应行则会有一个$0$。一行中若有多个数字，数字之间以一个空格分隔。

【输出】

包含两行，第一行是一个正整数，表示任务$a$的解，第二行也是一个正整数，表示任务$b$的解。

【输入样例】

5

2 4 3 0

4 5 0

0

0

1 0

【输出样例】

1

2

【提示】

数据范围与提示:

$2≤n≤100$。

### 算法

Tarjan缩点

对于任务$a$，可以发现在缩点之后图变成了一个有向无环图，此时统计入度为$0$的强连通分量。入度为$0$意味着该强连通分量不会接受到其他强连通分量的软件，所有需要将新软件提供给这个强连通分量。所有任务$a$的答案就是缩点后入度为$0$的强连通分量的数量。

对于任务$b$，在缩点之后的图中如果有些点的入度为$0$，则若将软件发送给不是这个强连通分量内的学校就无法传递到这个学校；如果有些点的出度为$0$，则若将软件发送给这个强连通分量内的学校，则这个强连通分量外的学校无法接受（注意，此处强连通分量的数目应大于等于2），所有应该把缩点后的图变成一个不存在入度为$0$或出度为$0$的点。如果将一个出度为0的点连接一个入度为0的点，即可将这两个点的出（入）度增加。然而一次增加边最多只能使入度为0的点减少1和出度为0的点减少1，则需要增加入度为0的点的数量和出度为0的点的数量的最大值。

### 代码

```cpp
#include<cstdio>
#include<stack>
#define mini(a,b) ((a)<(b)?(a):(b))
const unsigned short int N=10005;
const unsigned int M=5000005;
unsigned short int n;
struct node
{
	unsigned short int to;
	unsigned int next;
}edge[M];
unsigned int cnt,head[N];
inline void add(unsigned short int u,unsigned short int v)
{
	cnt++;
	edge[cnt].to=v;
	edge[cnt].next=head[u];
	head[u]=cnt;
}//链式前向心存图、建边
unsigned short int dfn[N],low[N],step,num,col[N],sum[N];
std::stack<unsigned short int> s;//Tarjan数组
void tarjan(unsigned short int i)
{
	step++;
	dfn[i]=step;
	low[i]=step;
	s.push(i);
	for(unsigned int j=head[i];j!=0;j=edge[j].next)
	{
		unsigned short int k=edge[j].to;
		if(dfn[k]==0)
		{
			tarjan(k);
			low[i]=mini(low[k],low[i]);
		}
		else if(col[k]==0)
		{
			low[i]=mini(dfn[k],low[i]);
		}
	}
	if(low[i]==dfn[i])
	{
		num++;
		col[i]=num;
		sum[num]++;
		while(s.top()!=i)
		{
			sum[num]++;
			col[s.top()]=num;
			s.pop();
		}
		s.pop();
	}
}//Tarjan算法缩点
unsigned short int dui[N],duo[N],ans1,ans2;
int main()
{
	scanf("%hu",&n);
	unsigned short int d;
	for(register unsigned short int i=1;i<=n;i++)
	{
		while(true)
		{
			scanf("%hu",&d);
			if(d==0)
			{
				break;
			}
			add(i,d);
		}
	}//读入、建边
	for(register unsigned short int i=1;i<=n;i++)
	{
		if(dfn[i]==0)
		{
			tarjan(i);
		}
	}//Tarjan
	for(register unsigned short int i=1;i<=n;i++)
	{
		for(register unsigned int j=head[i];j!=0;j=edge[j].next)
		{
			if(col[i]!=col[edge[j].to])
			{
				dui[col[edge[j].to]]++;
				duo[col[i]]++;
			}
		}
	}//统计入度、出度
	for(register unsigned short int i=1;i<=num;i++)
	{
		if(dui[i]==0)
		{
			ans1++;
		}
		if(duo[i]==0)
		{
			ans2++;
		}
	}//统计答案
	if(num==1)
	{
		ans2=0;
	}//特判：当全图为一个强连通分量时，任务b的答案为0（原来算出来的为1）
	else
	{
		ans2=((ans2)>(ans1)?(ans2):(ans1));
	}//取大值
	printf("%hu\n%hu",ans1,ans2);
	return 0;
}
```

#### 运行结果

一本通OJ：（原始数据）

1515

通过 100分

测试点1: 答案正确 432KB 6MS 

测试点2: 答案正确 432KB 5MS 

测试点3: 答案正确 428KB 6MS 

测试点4: 答案正确 424KB 5MS 

测试点5: 答案正确 424KB 6MS 

测试点6: 答案正确 428KB 5MS 

测试点7: 答案正确 424KB 6MS 

测试点8: 答案正确 424KB 5MS 

测试点9: 答案正确 432KB 6MS 

测试点10: 答案正确 420KB 5MS 

测试点11: 答案正确 440KB 6MS 

洛谷：

（原始数据）

用时 30ms 内存 820.00KB

测试点信息

3ms/764.00KB 
AC #1

3ms/524.00KB 
AC #2

2ms/508.00KB 
AC #3

3ms/788.00KB 
AC #4

2ms/676.00KB 
AC #5

3ms/628.00KB 
AC #6

3ms/672.00KB 
AC #7

2ms/644.00KB 
AC #8

3ms/820.00KB 
AC #9

3ms/660.00KB 
AC #10

3ms/692.00KB 
AC #11

（增强版）

用时 39ms 内存 1.12MB

测试点信息

3ms/676.00KB 
AC #1

13ms/1.12MB 
AC #2

2ms/768.00KB 
AC #3

2ms/524.00KB 
AC #4

3ms/808.00KB 
AC #5

2ms/648.00KB 
AC #6

2ms/676.00KB 
AC #7

4ms/804.00KB 
AC #8

3ms/800.00KB 
AC #9

5ms/1.02MB 
AC #10

---

## 作者：紫薯布丁 (赞：0)

## Tarjan缩点的好题，适合Tarjan初学者

题目大意为给你一张图，让你判断至少通过几个点才能遍历整张图，以及至少需要加几条边才能使整张图变成一个大环


第一问显然我们可以通过taijan缩点使其不存在环（缩点之后的每个点一定是可以相互到达的），然后统计入度为0的点就可以了

那么第二问嘞？

我在做这道题的时候看到第二问懵了半天。

### 首先我们要了解图的一个重要性质：对于一张不存在环的图，必然存在入度为0和初度为0的点。
所以可以我们统计缩点后入度为0和初度为0的点，从出度为0的到入度为0的点连一条边

当入度>出度 显然我们需要多连（入度-初度）条边

当入度<初度 我们需要多连（初度-入度）条边

### 那么第二问的答案我们就可以推出来了max（入度为0点的个数，初度为0点的个数）

那么代码就十分简单了，跑个裸tarjan，统计入度和出度为0的点就可以啦

```cpp
#include<iostream>
#include<cstdio>
#include<stack>
#include<cstring>
#define ss 5005000 
using namespace std;
inline int read(){
	int x(0),f(1);char c(getchar());
	for(;!isdigit(c);c=getchar()) c=='-'?f=-1:1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0';
	return x*f;
}

struct oo{
   int next,to;
}e[ss*4];
int head[ss],cnt(0),cnt2(0),fr[ss],to[ss],X[ss],Y[ss],col(0),co[ss],dfn[ss],low[ss],num(0);
stack <int >q;

inline void add(int x,int y){
	e[++cnt].to=y;
	e[cnt].next=head[x];
	head[x]=cnt;
}

inline void Tarjan(int x){//标准Tarjan缩点 
	dfn[x]=low[x]=++num;
	q.push(x);
	int u=(x);
	for(register int i=head[x];i;i=e[i].next){
		int y=e[i].to;
		if(!dfn[y]) {
		   Tarjan(y);
		low[x]=min(low[x],low[y]);
	    }
	    else if(!co[y]){
	    	low[x]=min(low[x],dfn[y]);
		}
	}
	if(low[x]==dfn[x]){
		co[x]=++col;
		while(q.top()!=x){
			int po=q.top();
			q.pop();
			co[po]=col;
		}
		q.pop();
	}
}

inline void clean(){
	memset(head,0,sizeof(head));
	cnt=0;
}
main(){
    int n=read();
	for(register int i=1;i<=n;i++){
		int x=read();
		while(x){
			add(i,x);	
			X[++cnt2]=i;
		    Y[cnt2]=x;//用数组存一下入度和出度好统计 
			x=read();
		
		}
		
	}
	for(register  int i=1;i<=n;i++){
		if(!dfn[i]) Tarjan(i);
	}
//	clean();add(x,y);
//(打到这个地方的时候我还想缩点之后重建一次边，后来发现根本不需要，我还是太篛了 
	for(register int i=1;i<=cnt2;i++){
		int x=co[X[i]],y=co[Y[i]];
	//	printf("%d %d %d %d\n",X[i],co[X[i]],Y[i],co[Y[i]]); 
		if(x==y) continue;
		fr[x]++;to[y]++;
	}
	int ans1(0),ans2(0);
	for(register int i=1;i<=col;i++){
		if(!fr[i]) ans1++;
		if(!to[i]) ans2++;
	}
	printf("%d\n%d",ans2,col==1?0:max(ans1,ans2));//因为当只有一个点的时候不需要再添加母鸡，所以要特判一下 
}//然后我们就可以切掉没有强化过数据的校园网络获得双倍快乐啦 
```


---

## 作者：Drinkwater (赞：0)

来秒一发题解，在做USACO的时候顺带把这道题做了，我们用tarjan缩好点后，之后的图我们看其中的点数，就是第一问的答案，第二问就是楼下讲的INDEGREE和OUTDEGREE的max就好了

/*************************************************************************

    > Author: Drinkwater-cnyali
    > Created Time: 2017/5/16 20:16:50
************************************************************************/
















```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long LL;
#define REP(i, a, b) for(register int i = (a), i##_end_ = (b); i <= i##_end_; ++ i)
#define DREP(i, a, b) for(register int i = (a), i##_end_ = (b); i >= i##_end_; -- i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mem(a, b) memset((a), b, sizeof(a))
template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }
int read()
{
    int sum = 0, fg = 1; char c = getchar();
    while(c < '0' || c > '9') { if (c == '-') fg = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { sum = sum * 10 + c - '0'; c = getchar(); }
    return sum * fg;
}
const int maxn = 100000;
const int inf = 0x3f3f3f3f;
int n;
int be[maxn],ne[maxn],to[maxn],e;
void add(int x,int y)
{
    to[++e] = y;
    ne[e] = be[x];
    be[x] = e;
}
int vis[maxn];
int tid[maxn],low[maxn],cnt,col[maxn],stack[maxn],top,num[maxn],ff,p[maxn];
void tarjan(int x)
{
    low[x] = tid[x] = ++cnt;
    vis[x] = 1;stack[++top] = x;
    for(int i = be[x]; i; i = ne[i])
    {
        int v = to[i];
        if(!vis[v])
        {
            tarjan(v);
            low[x] = min(low[x],low[v]);
        }
        else if(vis[v])low[x] = min(low[x],tid[v]);
    }
    if(tid[x] == low[x])
    {
        vis[x] = 0;col[x] = x;
        do
        {
            col[stack[top]] = x;
            vis[stack[top]] = 0;
            top--;
        }while(stack[top+1]!=x);
    }
}
int In[maxn],Out[maxn];
void find(int x)
{
    vis[x] = 1;
    for(int i = be[x]; i ;i = ne[i])
    {
        int v = to[i];
        if(!vis[v] && col[v]!=x)
        {
            In[v]++,Out[x]++;
            find(v);
        }
    }
}
int main()
{
    n = read();
    REP(i,1,n)
    {
        int x;
        while(scanf("%d",&x)&&x)
            add(i,x);
    }
    int ans1 = 0;
/*    REP(i,1,n)
    {
        if(!vis[i])
            ans1++,dfs(i);
    }
    memset(vis,0,sizeof(vis));*/
    REP(i,1,n)
        if(!tid[i])
        {
            tarjan(i);
        }
    REP(i,1,n)if(!p[col[i]])p[col[i]] = 1,num[++ff] = col[i];
    int cnt1 = 0,cnt2 = 0;
    REP(i,1,n)
    {
        for(int j = be[i]; j; j = ne[j])
        {
            int v = to[j];
            if(col[i]!=col[v])++In[col[v]],++Out[col[i]];
        }
    }
    REP(i,1,ff)
    {
        if(In[num[i]] == 0)cnt1++;
        if(Out[num[i]] == 0)cnt2++;
    }
    if(ff == 1){puts("1");puts("0");return 0;}
    int ans2 = max(cnt1,cnt2);
    cout<<cnt1<<endl<<ans2<<endl;
    return 0;
}

```

---

