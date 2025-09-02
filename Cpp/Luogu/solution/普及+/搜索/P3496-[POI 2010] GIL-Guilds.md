# [POI 2010] GIL-Guilds

## 题目描述

King Byteasar faces a serious matter.

Two competing trade organisations, The Tailors Guild and The Sewers Guild asked,    at the same time, for permissions to open their offices in each town of the kingdom.

There are ![](http://main.edu.pl/images/OI17/gil-en-tex.1.png) towns in Byteotia.

Some of them are connected with bidirectional roads.

Each of the guilds postulate that every town should:

have an office of the guild, or           be directly connected to another town that does.

The king, however, suspects foul play. He fears that if there is just a single    town holding the offices of both guilds, it could lead to a clothing cartel.

For this reason he asks your help.


给一张无向图，要求你用黑白灰给点染色，且满足对于任意一个黑点，至少有一个白点和他相邻；对于任意一个白点，至少有一个黑点与他相邻，对于任意一个灰点，至少同时有一个黑点和白点和灰点与他相邻，问能否成功


## 说明/提示

题目spj贡献者@mengbierr

## 样例 #1

### 输入

```
7 8
1 2
3 4
5 4
6 4
7 4
5 6
5 7
6 7```

### 输出

```
TAK
K
S
K
S
K
K
N```

# 题解

## 作者：dingcx (赞：35)

这道题标签是广搜，于是我就用深搜来做。

~~不要问我为什么快考CSP了还来发题解~~
## 思路
首先看题：白点或黑点都只需要旁边有一个另一种颜色的点就行了，而灰色不一样，它需要一白一黑。显然，灰色要求更多，也就更难处理，那么，就**不涂它**了吧。

一个点白点或黑点，只要有点与它相连，这两个点颜色相反，就可以满足。而如果一个点不与其他任何点连通，不管涂不涂灰色，都无法满足。也就是说，在任何情况，都可以**不涂灰色**。

世界一下子清静了许多：只有黑点和白点。那么，对于每一个连通图，**都搜一遍**，第一个点记为白点，后面每搜到一个点，都**涂上与前一个点相反的颜色**，如果涂过就不涂了。而如果有一个连通图只有一个点，那么**一定不行**，输出$NIE$就好了。
## 细节
有的细节还是有必要提一下。

在读入边的时候，把这个边**两个端点都标记一下**，这样只要有没标记到的点，一定是单独的，即无法完成。

建边时，要用**邻接表优化**空间，不然会超空间。

深搜时，一定要**没有搜到**（新的连通图）再继续搜，不然绝对超时。
## 技巧
这里的技巧就是如何把代码写的更简单（~~更短~~）
### 判断是否搜过
开一个整型的$color$数组，值为$0$表示未染色（未遍历），$1$表示白色，$2$表示黑色。

判断只需要$color[i]==0$
### 求相反颜色
求相反颜色方法：$color[i]$%$2+1$（$1$直接变$2$，$2$直接变$1$）。
## 代码
相信没有多少人喜欢上面的一通分析吧，那么，你们喜欢的代码来了——
```cpp
#include<cstdio>
using namespace std;
const int MAXN=200010,MAXM=1000010;//注意边数要乘2
int h[MAXN],color[MAXN],tot=0;//h为邻接表中的head，tot为总边数
bool vis[MAXN];//记录是否有连接
struct Edge{//边的结构体
	int v;
	int next;//next记录这条边在邻接表中指向同端点的另一条边
}e[MAXM];
void addEdge(int u,int v){//建边
	tot++;
	e[tot].v=v;
	e[tot].next=h[u],h[u]=tot;
}
void dfs(int u){//深搜，u为原节点，保证已染色
	for(int k=h[u];k;k=e[k].next){//邻接表查找
		int v=e[k].v;
		color[v]=color[u]%2+1;//公式
	}
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	while(m--){
		int uu,vv;
		scanf("%d%d",&uu,&vv);
		vis[uu]=1,vis[vv]=1;//记录
		addEdge(uu,vv);addEdge(vv,uu);//建边
	}
	for(int i=1;i<=n;i++)//判断是否不行
	    if(!vis[i]){
	    	printf("NIE\n");//输出
	    	return 0;//返回
		}
	printf("TAK\n");//直接输出
	for(int i=1;i<=n;i++)//每个点都搜一遍
		if(!color[i]){//没搜过
			color[i]=1;//先设为白点
			dfs(i);//开搜
		}
	for(int i=1;i<=n;i++){//输出
		if(color[i]==1) printf("K\n");
		else printf("S\n");
	}
	return 0;//华丽结束
}
```
在CSP前写一篇题解也不容易，别忘了点个赞！

---

## 作者：first_fan (赞：10)

> ### 这是一个非黑即白的世界。

想必各位都看过题目了，首先翻译下题意：

> ### 给一幅无向图，你可以对其每个点染色，要求白黑必须挨着，灰色必须和黑白挨着，问能否染色以及染色方案。

我们可以考虑到，灰色点必然可以被黑白交替的模式代替，所以我们只要黑白染色就好，灰色可以请出去了。怎么染色？要把每个点都要染到？还要交替染？

我们立即想到一个点的入度越少越好，因为这样一个点对于其周围点的影响最小。入度最小？如果图连通，我们可以把它降为1——$\color{red}\sf\large\text{生成树}$恰好满足这一性质。

`图不连通呢？`题上可是说了，如果不能成功染色，那么输出`NIE`退出就好，另外我们可以想到，联通的图一定是可以完成染色的，所以可以大胆输出`TAK`

那么！我们再回头看一眼题目，就是这样的：

> ### 给一幅无向图，找出里面的生成树，对其上的每个点黑白交替染色，问图是否连通，若连通则输出每个点的颜色(有SPJ)

是否很明了了？献上一份代码（附简注），此处我用的是常规存图+dfs染色。

```cpp
//在这个图中的生成树上染色就好，白黑交替染
#include <bits/stdc++.h>
#define ri register int
#define ll long long
using namespace std;
int read()
{
	int num=0;
	int flg=1;
	char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')
		{
			flg=-1;
		}
		c=getchar();
	}
	while(isdigit(c))
	{
		num=(num<<1)+(num<<3)+(c^48);
		c=getchar();
	}
	return num*flg;
}
const int maxn=1e6+7;
struct edge
{
	int to;
	int nex;
} e[maxn];

int cnt=0;
int head[maxn];
void add(int u,int v)
{
	e[++cnt].to=v;
	e[cnt].nex=head[u];
	head[u]=cnt;
}

bool col[maxn];
//非黑即白
bool vis[maxn];
//这个vis[]要用两次：
//第一次：用来排查图中是否存在孤立点
//第二次：用来记录该点是否上色
void dfs(int nd,bool cur)
//当前的点，当前的颜色(黑/白)
//灰色太尖酸了，不必参加染色。
{
	vis[nd]=true;
	col[nd]=cur;
	for(ri i=head[nd]; i; i=e[i].nex)
	{
		int to=e[i].to;
		if(!vis[to])
		{
			dfs(to,!cur);
		}
	}
}

int main()
{
	int n=read();
	int m=read();
	for(ri i=1; i<=m; i++)
	{
		int u=read();
		int v=read();
		vis[u]=vis[v]=true;//不是孤立点
		add(u,v);
		add(v,u);
	}
	for(ri i=1; i<=n; i++)
	{
		if(!vis[i])
		{
			//显然，有一个点孤立，不可能全部连上。
			return 0&(int)printf("NIE");
		}
	}
	//能到这里，就说明一定可以连通.
	puts("TAK");
	fill(vis+1,vis+n+1,0);
	//清空，准备记录是否上色
	for(ri i=1; i<=n; i++)
	{
		if(!vis[i])
		{
			dfs(i,0);
		}
	}
	for(ri i=1; i<=n; i++)
	{
		if(col[i]==0)
		{
			puts("K");
		}
		else
		{
			puts("S");
		}
	}
}
```

回顾一下：这道题我们首先排除掉了`不可能存在的情况`，或者说存在了亦可以被代替的情况（因为`SPJ`）；随后我们找到了`树上染色`是最优的情况，解决问题。

---

## 作者：kkxhh (赞：6)

虽然黑白灰点的设定看起来很高端，但根据描述，黑点旁边只需要有一个白点，白点边只需要有一个黑点，于是直接交替染色就行了~~（灰点：？？？）~~

因为每个点边上都至少得有一个点，所以在连边的时候打个标记就能判断是否需要输出NIE了

实现方面直接bfs跑一遍就行了

程序如下

~~比较懒用的vector存边所以常数比较大，不过反正过了就行了~~

```cpp
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

queue<int> q;
vector<int> e[200010];
int n,m,a,b,c[200010]={0},mark[200010]={0},ok=1;

void bfs(int x){
    mark[x]=1;
    for(vector<int>::iterator it=e[x].begin();it!=e[x].end();it++){
        int j=*it;
        c[j]=c[x]^1; q.push(j); mark[j]=1;
    }
    while(!q.empty()){
        int i=q.front(); q.pop();
        for(vector<int>::iterator it=e[i].begin();it!=e[i].end();it++){
            int j=*it;
            if(!mark[j]) {c[j]=c[i]^1; q.push(j); mark[j]=1;}
        }
    }
}

int main() {
    scanf("%d %d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d %d",&a,&b);
        if(a==b) continue;
        e[a].push_back(b); e[b].push_back(a);
        mark[a]=mark[b]=1;
    }
    for(int i=1;i<=n && ok;i++) if(!mark[i]) ok=0;
    if(!ok) printf("NIE");
    else{
        printf("TAK\n");
        memset(mark,0,sizeof(mark));
        for(int i=1;i<=n;i++) if(!mark[i]) bfs(i);
        for(int i=1;i<=n;i++)
            if(c[i]) printf("K\n");
            else printf("S\n");
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：4)

你只需要将每个连通块求任意一个生成树，因为生成树是二分图，我们在这个生成树上进行二分图染色，显然这一定是满足题目要求的。

顺便说一句这个生成树可以直接拿并查集跑出来……大家有兴趣可以去做一下另一个POI水题P3465，跟这个差不多

如果不能满足条件怎么样？其实就是存在一个给谁都不连边的孤立的点就是NIE了……

还有树上的黑白染色得拿bfs跑出来……不然会爆栈……点挺多的

代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
char buf[100000000];int ptr=0;
inline char get_char(){
	ptr++;return(buf[ptr-1]);
}
#define getchar get_char
inline int get(){
	int n;char c;while((c=getchar())||1)if(c>='0'&&c<='9')break;
	n=c-'0';while((c=getchar())||1){
		if(c>='0'&&c<='9')n=n*10+c-'0';
		else return(n);
	}
}
unsigned char col[200001];//染色
int ints[200001];//并查集维护连通块
int find(int n){
	if(ints[n]==n)return(n);
	return(ints[n]=find(ints[n]));
}
unsigned char bv[500001];//这条边是不是树边
typedef struct _b{
	int dest;int next;int num;
}bian;bian memchi[1100001];int gn=1;int heads[200001];
unsigned char bj[200001]; //点是否连边
inline void add(int s,int t,int num){memchi[gn].dest=t;
	memchi[gn].num=num;memchi[gn].next=heads[s];heads[s]=gn;gn++;
}
int que[10000000];
char cjr[3]={'A','K','S'};
int opp[3]={0,2,1};
inline void bfs(int s){//bfs跑黑白染色
	register int head=0,tail=1;que[0]=s;
	do{
		int me=que[head];head++;
		for(register int i=heads[me];i;i=memchi[i].next){
			if(!bv[memchi[i].num])continue;
			if(col[memchi[i].dest])continue;
			col[memchi[i].dest]=opp[col[me]];
			que[tail]=memchi[i].dest;tail++;
		}哈哈哈您别想抄代码
	}while(head<tail);
}
int main(){
	fread(buf,1,100000000,stdin);
	int n=get(),m=get();
	for(register int i=1;i<=n;i++)ints[i]=i;
	for(register int i=1;i<=m;i++){
		int s=get(),t=get();add(s,t,i);add(t,s,i);
		int sa=find(s),sb=find(t);bj[s]=1;bj[t]=1;
		if(sa!=sb){
			ints[sa]=sb;bv[i]=1;
		}
	}
	for(register int i=1;i<=n;i++){
		if(!bj[i]){
			printf("NIE\n");return(0);//有孤立点则NIE
		}
		if(ints[i]==i){
			col[i]=1;bfs(i);//黑白染色
		}
	}
	printf("TAK\n");
	for(register int i=1;i<=n;i++){
		putchar(cjr[col[i]]);putchar('\n');
	}
	return(0);
}
```

---

## 作者：happy_dengziyue (赞：2)

### 1 思路

##### 大体思路

这道题可以用枚举解决。

不得不说，灰色点的要求太高了，那就不涂它了。

显然，如果有一个连通块仅有一个点，那么整张图不可能满足要求。

否则，必有一种满足要求的点。

我们枚举每一个点，如果它还没被涂色，就把它涂成白色，把与之相邻的所有的点（无论它是否被涂色），将其涂成黑色。

可以证明，这样做后，一定满足要求。为什么呢？

##### 思路证明

很明显，如果枚举到一个点没涂色，将其涂成白色，又将所有与之相邻的点涂成黑色后，这些点必定满足要求。

考虑一下与之相连的点的原始颜色。

如果原来没涂色，就不需要在意它所相连的点。那些点都满足要求了。

如果是黑色，那更不用管了，涂了等于没涂。

而且，它也不可能是白色，不然“没涂色的点”早涂黑色了。

综上，这个算法是正确的。

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
#define max_n 200000
#define max_m 1000000
int n;
int m;
bool ap[max_n+2];
struct E{
	int v,nx;
}e[max_m+2];
int ei=0;
int fir[max_n+2];
int col[max_n+2];
inline void addedge(int u,int v){
	e[++ei]=(E){v,fir[u]}; fir[u]=ei;
}
void dfs(int u){
	for(int i=fir[u],v;i;i=e[i].nx){
		v=e[i].v;
		col[v]=3-col[u];
	}
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("P3496_1.in","r",stdin);
	freopen("P3496_1.out","w",stdout);
	#endif
	scanf("%d%d",&n,&m);
	memset(ap,0,sizeof(ap));
	memset(fir,0,sizeof(fir));
	for(int i=1,u,v;i<=m;++i){
		scanf("%d%d",&u,&v);
		ap[u]=true;
		ap[v]=true;
		addedge(u,v);
		addedge(v,u);
	}
	for(int i=1;i<=n;++i){
		if(!ap[i]){
			puts("NIE");
			return 0;
		}
	}
	memset(col,0,sizeof(col));
	for(int i=1;i<=n;++i){
		if(!col[i]){
			col[i]=1;
			dfs(i);
		}
	}
	puts("TAK");
	for(int i=1;i<=n;++i){
		if(col[i]==1)puts("K");
		else puts("S");
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/58887826)

By **dengziyue**

---

## 作者：风人 (赞：2)

## 一道优雅的bfs题 

题目链接：[P3496](https://www.luogu.com.cn/problem/P3496)

大概读一下题，黑块旁要有白块，白块旁要有黑块，而灰块旁既要有白又要有黑。那么很容易发现，当满足灰块的条件时，此时必然可以使用黑或白来填充，于是我们可以只考虑黑白而舍掉灰块。

---

既然白块旁有黑，黑块旁有白，那么只要图中存在孤立点，无解；反之则有解。我们可以在存边时记录每个点是否到达来判断是否有解。

vector存边：
```cpp
bool done[200005];	//这一步该数组用于是否存到该点
vector<int> a[200005];	//存储边的vector 
vector<int>::iterator it;
int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= m;i ++){		//存边过程 
		int x,y;
		scanf("%d%d",&x,&y);
		if(x!=y){
			a[x].push_back(y);
			a[y].push_back(x);
			done[x]=done[y]=1;	//记录存到了这个点
		}	
	}
	
	bool sure = 1;
	for(int i=1; i<=n && sure ;i++)
		if(!done[i]) sure = 0;  //查询是否有解
	if (sure) cout << "TAK\n"; 	//不存在孤立点
	else {cout << "NIE";return 0;}		// 存在孤立点 结束程序
```

---

到这里我们完成了存边和是否有解的查询，下来该染色了。要求是黑的旁边要有白，白的旁边要有黑，于是我们可以把每一个点与他相邻的且没被搜到的点染成与它颜色不一样的即可。

bfs实现：
```cpp
int c[200005]; //记录颜色
void bfs(int); //声明bfs函数 
queue<int> b; //bfs队列	
void bfs(int k){
    done[k]=1; 
    b.push(k);
    while(!b.empty()){
        int i=b.front(); b.pop();
        for(it=a[i].begin();it!=a[i].end();it++){
            int x=*it;
            if(!done[x]) {
			     c[x]=c[i]^1;  //使用异或来染不同颜色
			     b.push(x); 
			     done[x]=1;
			  }
         }
     }    
}
```    	
但是由于图可能不完全联通，所以不能只调用一次bfs函数，要每一个没有搜到的点都进行一次bfs即可。

---

完整代码如下：
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int n,m;	//n,m如题
bool done[200005];	//是否搜到过 
int c[200005];
void bfs(int); //声明bfs函数 
vector<int> a[200005];	//存储边的vector 
vector<int>::iterator it;
queue<int> b;

int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= m;i ++){		//存边过程 
		int x,y;
		scanf("%d%d",&x,&y);
		if(x!=y){
			a[x].push_back(y);
			a[y].push_back(x);
			done[x]=done[y]=1;	
		}	
	}
	
	bool sure = 1;
	for(int i=1; i<=n && sure ;i++)
		if(!done[i]) sure = 0;
	if (sure) cout << "TAK\n"; 	//不存在孤立点
	else {cout << "NIE";return 0;}		// 存在孤立点 结束程序
	//存完边，进行bfs
	memset(done,0,sizeof(done));
	for(int i=1;i<=n; i++) 
		if(!done[i]) bfs(i); //多次调用bfs
	for(int i=1;i<=n;i++){
        if(c[i]) printf("K\n");
        else printf("S\n");
    }
    return 0;
}

void bfs(int k){
    done[k]=1;
    b.push(k);
    while(!b.empty()){
        int i=b.front(); b.pop();
        for(it=a[i].begin();it!=a[i].end();it++){
            int x=*it;
            if(!done[x]) {
			     c[x]=c[i]^1; 
			     b.push(x); 
			     done[x]=1;
			 }
        }
    }    
}
```    	

---

## 作者：谦谦君子 (赞：2)


### 不难发现如果两个点是联通的，那么两个点都会满足条件。
### （因为发现这个点不涂色是不划算的，只要两个点涂上不同的颜色即可）
### 所以任务变为图中是否有孤立的点,随便怎么判一下即可。

代码就不写了~~（主要是不想复制过来）~~，大家可以好好想一下

---

## 作者：cryozwq (赞：1)

这篇文章主要是对一些结论的说明（？

# 分析
首先，这道题有三种颜色——这非常讨厌，考虑到这里面最复杂的是灰色，我们就先来讨论它，当有一个灰点时大概是这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/i6btvq4o.png)

这个涂色方案的成立其实隐含了一个条件：图上的黑点和白点一定和另外一个点连接**并且这个点的颜色正好和其相反**（换句话说，黑点一定连了一个白点，白点一定连了一个黑点），既然是这样，那其实灰点的存在与否没有意义，换成任意颜色都是成立的，所以我们可以知道：**假如存在合法的方案，则一定存在一种方案不使用灰色**。

于是我们只去考虑黑色和白色就行了。

接下来我们分联通快讨论，设一个联通块有 $n_i$ 个节点。

当 $n_i =1$ 的时候，是无论如何都没有合法方案的。

当 $n_i \neq 1$ 的时候，比较有趣。

首先我们知道联通块的边数**至少为**  $n_i - 1$，也就是树。那么我们就先来讨论树：

- 根节点与叶子节点的度为 $1$。
- 其它节点度均大于 $1$。

那么显然，这棵树有合法染色方案，只需要黑白交替的染。

那么无论边数怎么增加，这个方案都成立。

也就是说，对于任意一个联通块，只要 $n_i \neq 1$，则一定有合法方案。**且黑白交替的染一定是合法方案**。

这道题就思考完了，具体细节见代码。

# 代码
写的很丑，仅供参考。
```cpp
#include<bits/stdc++.h>
#define maxn 2000000
using namespace std;
int head[10000005],cnt,n,color[10000005];
struct Edge{
	int u,v,next;
}e[50000005];
bool flag=0;
struct Node{
	int w,now;
	inline bool operator <(const Node &x)const
	{
		return w>x.w;
	} 
}; 
inline void add(int u,int v)
{
    e[++cnt].u=u;
    e[cnt].v=v;
    e[cnt].next=head[u];
    head[u]=cnt;
}  
bool vis[maxn];
long long d[maxn];
void BFS_color(int num,int Color){	
	color[num]=Color;
	queue<int>q;
	q.push(num);
	vis[num]=1;
	while(q.size()){
		int top=q.front();
		q.pop(); 
		vis[top]=1;
		for(int i=head[top];i;i=e[i].next){
			int tv=e[i].v;
			if(color[tv]==0){
				color[tv]=3-color[top];
				if(!vis[tv])
				q.push(tv);
			}
		}
	}
}
int main()
{
	long long m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		d[v]++;
		d[u]++;
		add(v,u);
		add(u,v);
	}
	for(int i=1;i<=n;i++){
		if(vis[i]==0){
			if(d[i]==0){
				puts("NIE");
				return 0;
			}
			BFS_color(i,1);
		}
	}
	puts("TAK");
	for(int i=1;i<=n;i++){
		if(color[i]==1)
		puts("K");
		else
		puts("S");
	}
    return 0;
}
```

---

## 作者：Light_az (赞：0)

首先是警示后人，由于这道题目太毒瘤，导致 `vector` 遍历竟然超内存，因此我只能使用我不太收悉的链式前向星了，不会的可以点[这里](https://blog.csdn.net/sugarbliss/article/details/86495945?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522167939020616800182774115%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=167939020616800182774115&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-86495945-null-null.142^v74^control_1,201^v4^add_ask,239^v2^insert_chatgpt&utm_term=%E9%93%BE%E5%BC%8F%E5%89%8D%E5%90%91%E6%98%9F&spm=1018.2226.3001.4187)。

根据题意我们发现这是无向图，而且由于不同颜色的点的不同性质和要求，所以我们要想清楚如何涂色。对此最简单的思路是不涂灰色点，因为太麻烦了，两端必须是白色和黑色点，所以我们假设一个没有颜色的点的颜色为白色，对于距离它是偶数的点也涂成白色，那么没有涂的点一定是黑色，直接输出结果即可，当有任意一个点没有被一条边连接，那么此情况一定无解，输出 `NIE` 即可。

## Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define F(i,j,n) for(int i=j;i<=n;i++)
#define Tr(v,e) for(int v:e)
#define D double
#define ps push_back
#define Test ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr)
using namespace std;
const int N=2e6+10,NN=1e4+10;
ll n,m,k,x,y,u,v,w,cnt=0,ans=0,t=0,l,r,len,T;
ll mini=INT_MAX,maxi=0,Mod;
string s1,s2;
vector<int> tr[N];
map<int,int> mp;
ll c[N],head[N];
struct Node{
	ll to,next;
}edge[N];
void add(ll u,ll v){
	cnt++;
    edge[cnt].to=v;
    edge[cnt].next=head[u];
    head[u]=cnt;
}
void dfs(ll id){//链式前向星
	for(int i=head[id];i;i=edge[i].next){//遍历边
		v=edge[i].to;
		c[v]=c[id]%2+1;//距离为偶数的染色成白色
	}
}
int main(){
    Test;
	cin>>n>>m;
	F(i,1,m){
		cin>>u>>v;
		add(u,v);//链式前向星建边
		add(v,u)
;		mp[u]=mp[v]=1;//标记
	} 
	F(i,1,n) if(!mp[i]){//有点无出现
		cout<<"NIE";
		return 0;
	}	
	cout<<"TAK\n";
	F(i,1,n) if(!c[i]) c[i]=1,dfs(i);//假设为白色
	F(i,1,n) if(c[i]==1) cout<<"K\n"; else cout<<"S\n";//输出白黑色
	
	return 0;
}
```




---

## 作者：JiaY19 (赞：0)

一道广搜+深搜。

#### 大致思路

我们发现如果去涂灰色，整个思路就会非常复杂。

再一看，诶，有SPJ。

那我们就~~不涂灰色吧~~。

只考虑涂**白色和黑色**。

先用深搜将每个连通块中的点放入队列中。

再用一遍广搜来进行涂色。

#### 关于正确性

我们可以知道，如果用一个点是单独的，那么他就一定是错误的，无法染色。

那么至于其他的联通块，我们发现，它是一定可以黑白染色的。

所以仅需要一个记录度数的数组，来判断是否能涂色。

#### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n , m , cnt , v[200010] , v1[200010] , du[200010] , head[200010] , colo[200010];

struct edge
{
    int to , nxt;
}e[1000010];

int read(){
    int s = 0 , f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        s = s * 10 + ch - '0';
        ch = getchar();
    }
    return s * f;
}

void add(int x , int y)
{
    e[++cnt] = (edge){y , head[x]};
    head[x] = cnt;
}

void dfs(int now)
{
    v[now] = 1;
    for(int i = head[now];i;i = e[i].nxt) if(v[e[i].to] == 0) dfs(e[i].to);
    return;
}

int main()
{
    n = read() , m = read();
    for(int i = 1;i <= m;i++)
    {
        int x = read() , y = read();
        add(x , y) , add(y , x);
        du[x]++ , du[y]++;
    }
    for(int i = 1;i <= n;i++)
        if(du[i] == 0)
        {
            cout << "NIE";
            return 0;
        }
    cout << "TAK" << endl;
    queue<int> q;
    for(int i = 1;i <= n;i++)
    {
        if(v[i] == 0) q.push(i) , dfs(i) , colo[i] = 1 , v1[i] = 1;
    }
    while(q.empty() == false)
    {
        int x = q.front(); q.pop();
        for(int i = head[x];i;i = e[i].nxt)
        {
            int y = e[i].to;
            if(v1[y]) continue;
            else
            {
                if(colo[x] == 1) colo[y] = 2;
                else colo[y] = 1;
                v1[y] = 1;
                q.push(y);
            }
        }
    }
    for(int i = 1;i <= n;i++)
    {
        if(colo[i] == 1) cout << "K" << endl;
        else cout << "S" << endl;
    }
    
    return 0;
}
```

完结撒花

---

