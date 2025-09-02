# KNIGHTS - Knights of the Round Table

## 题目描述

### 题目大意

有 $n$ 个骑士经常举行圆桌会议，商讨大事。每次圆桌会议至少有 $3$ 个骑士参加，且相互憎恨的骑士不能坐在圆桌的相邻位置。如果发生意见分歧，则需要举手表决，因此参加会议的骑士数目必须是大于 $1$ 的奇数，以防止赞同和反对票一样多。知道骑士之间相互憎恨的关系后，请你帮忙统计有多少骑士参加不了任意一个会议。

## 说明/提示

$1\leq n \leq 10^3$，$1\leq m\leq10^6$。保证 $1\leq k_1,k_2\leq n$。

$\small{\text{Statement fixed by @Starrykiller.}}$

## 样例 #1

### 输入

```
5 5
1 4
1 5
2 5
3 4
4 5
0 0```

### 输出

```
2```

# 题解

## 作者：panyf (赞：25)

提供一篇有严谨结论证明的题解。

本题最关键的结论是：点双连通图中若包含一个奇环，则所有点都在至少一个简单奇环上。

先在图中选出最初的奇环，此时一定满足两个条件：

1.所有点都在至少一个简单奇环上；

2.任意点对 $u,v$ 间存在长为奇数的路径和长为偶数的路径。

重复以下操作：

在原图中去掉选出的所有点，原图分为若干连通块。对于任意连通块 $X$ 一定和已选出的至少两个点 $u,v$ 相连（若只与一个点相连，则这个点是割点，与点双矛盾）。

选出 $u-X-v$ 的任意一条路径（因为 $X$ 连通所以这样的路径一定存在）。若这条路径长为奇数，和 $u,v$ 间长为偶数的路径可以拼成奇环，否则和 $u,v$ 间长为奇数的路径可以拼成奇环。

对于路径上两点 $x,y$，$x-u-v-y$ 可以是长为奇数的路径和长为偶数的路径。对于路径上一点 $x$ 和之前已经选出的一点 $a$，$x-u-a$ 可以是长为奇数的路径和长为偶数的路径。因此两个条件依然满足。

重复以上操作直到所有点都被选出，结论得证。

有了结论以后本题就很简单了，先建补图，补图上 Tarjan 求点双，对于每一个点双二分图染色判断是否有奇环，不在任何一个有奇环的点双上的点都无法参加会议。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1003;
bool e[N][N],b[N],f[N],o;
int r,n,dfn[N],low[N],st[N],tp,id,ct,cl[N];
basic_string<int>dcc[N];
void tar(int x){//Tarjan求点双
	dfn[x]=low[x]=++id,st[++tp]=x;
	for(int i=1;i<=n;++i)if(e[x][i]){
		if(!dfn[i]){
			tar(i),low[x]=min(low[x],low[i]);
			if(low[i]>=dfn[x])for(dcc[++ct].clear(),dcc[ct]+=x;dcc[ct]+=st[tp],st[tp--]!=i;);
		}else low[x]=min(low[x],dfn[i]);
	}
}
void dfs(int x){//二分图染色
	for(int i=1;i<=n;++i)if(e[x][i]&&b[i]){
		if(cl[i]==2)cl[i]=!cl[x],dfs(i);
		else if(cl[i]==cl[x])o=1;
	}
}
int main(){
	int m,i,j;
	while(scanf("%d%d",&n,&m),n){
		memset(dfn+1,0,n*4),memset(f+1,1,n),id=ct=tp=0;
		for(i=1;i<=n;++i)memset(e[i]+1,1,n),e[i][i]=0;
		while(m--)scanf("%d%d",&i,&j),e[i][j]=e[j][i]=0;//建补图
		for(r=1;r<=n;++r)if(!dfn[r])tar(r);
		for(i=1;i<=ct;++i){
			for(int j:dcc[i])b[j]=1,cl[j]=2;
			o=cl[j=dcc[i][0]]=0,dfs(j);
			for(int j:dcc[i])if(b[j]=0,o)f[j]=0;
		}
		for(i=1,j=0;i<=n;++i)j+=f[i];
		printf("%d\n",j);
	}
	return 0;
}
```


---

## 作者：clockwhite (赞：12)

# [SP2878]KNIGHTS - Knights of the Round Table

## 一.前言

​	脑阔完全转不动……都不知道要干些什么，[题目链接](https://www.luogu.com.cn/problem/SP2878)

## 二.思路

​	首先它是圆桌骑士开会，所以他们开会的样子是一个环，并且避免平票需要只有奇数个人（不能一人开会）。将仇恨关系建图不好做，于是**建立补图，将可以坐在一起的骑士连边**，这样形成了一个可能的座位形状？然后去里面找**尽可能多的奇环。输出不被任何一个奇环包括的骑士。**

​	然后到这里我们会有一个结论如下：

> **对于一个点双连通分量，里面若是有一个奇环，那么该点双连通分量里面所有的点都可以被包括在奇环之中**

虽然我也不知道为什么会出现这个结论（好像写边双也可）就象征性的推导一下：

> 首先点双连通分量由一些环组成
>
> 假设在点双连通分量之中有环 a ，若 a 是奇环，那么 a 中所有点都可以开会，不影响答案
>
> 若 a 是偶环，那么将它和点双中的奇环链接成一个大奇环就可以了。

我也不知道是不是对的hhh，感性理解一下……同样我也不好解释奇环和点双的关系，硬要说的话，就是 tarjan 缩点之后不会有环，换而言之所有的环都在点双连通分量之中，由于这个结论很方便，就这么写了

​	现在需要判断一个点双里面有没有奇环。**对于一个没有奇环的图来说，他一定是一个二分图**（有了奇环就构不成二分图），转化为判断一个点双是不是二分图，使用二分图黑白染色，即将一个点周围的点全部染上相异的颜色，有冲突就不是二分图，也就是有奇环。

​	这样写就可以了。

## 三.CODE

```c++
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<fstream>
#include<cmath>
#include<cstring>
using namespace std;
int read(){
	char ch=getchar();
	int res=0,f=1;
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())res=res*10+(ch-'0');
	return res*f;
}
const int MAXN=1e6+5;
int n,m;
bool hate[1005][1005];
int head[1005],ne[MAXN],to[MAXN],tot;
void add(int x,int y){
	to[++tot]=y,ne[tot]=head[x],head[x]=tot;
}
void build(){
	for(int i=1;i<=n;++i)
		for(int j=i+1;j<=n;++j)
			if(!hate[i][j])add(i,j),add(j,i);
}
int dfn[1005],low[1005],date;
int st[1005],top,rs[1005];
bool vis[1005],fl,wdnmd[1005];
int ans;
bool check(int x,int fa){
	if(fl)return 1;
	for(int i=head[x];i;i=ne[i]){
		int v=to[i];
		if(v==fa||!vis[v])continue;
		if(rs[v]==-1){
			rs[v]=rs[x]^1;//染色
			check(v,x);
			if(fl)return 1;
		}
		else if(rs[v]!=(rs[x]^1))return (fl=1);//冲突
	}
	return 0;
}
void dfs(int x,int fa){//tarjan
	dfn[x]=low[x]=++date;
	st[++top]=x;
	for(int i=head[x];i;i=ne[i]){
		int v=to[i];
		if(!dfn[v]){
			dfs(v,x);
			low[x]=min(low[x],low[v]);
			if(low[v]>=dfn[x]){//出现点双
				int count=1;
				fl=0;
				memset(vis,0,sizeof(vis));
				memset(rs,-1,sizeof(rs));
				vis[x]=1;//将当前点双之中的全部打上标记
				rs[x]=0;
				while(st[top]!=v)vis[st[top--]]=1,count++;
				vis[v]=1,top--,count++;
				if(count>=3&&check(x,x))for(int i=1;i<=n;++i)if(vis[i])wdnmd[i]=1;
                //二分图染色
			}
		}
		else low[x]=min(low[x],dfn[v]);
	}
}
void clean(){
	memset(hate,0,sizeof(hate));
	memset(head,0,sizeof(head));
	tot=0;ans=0;
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	memset(wdnmd,0,sizeof(wdnmd));
}
int main(){
	while(1){
		n=read();m=read();
		if(n==m&&n==0)break;
		clean();//多测清空
		for(int i=1,x,y;i<=m;++i){
			x=read();y=read();
			hate[x][y]=hate[y][x]=1;
		}
		build();//建立补图
		for(int i=1;i<=n;++i)if(!dfn[i]){//可能会不连通，找点双
			memset(dfn,0,sizeof(dfn));
			memset(low,0,sizeof(low));
			date=top=0;
			dfs(i,i);
		}
		for(int i=1;i<=n;++i)ans+=(wdnmd[i]==0);//加上不被点双标记的
		printf("%d\n",ans);
	}
	return 0;
}
```



---

## 作者：灼眼的夏娜 (赞：10)

### 看到题解辣么少，当然要来一波啦！

有兴趣可以来我的博客逛逛（~~不要脸的推销~~）

## **[$blog$](https://violetnymph.blog.luogu.org/)**

好了进入正题

互相憎恨的骑士不能做到一起，这显然是满足二分图性质的

又看到一个合法的会议当且仅当不存在奇环，如果我们可以找出一些点

如果他们构成了这个非法的奇环，那他们便是答案，如何找奇环？

我们让互相不憎恨的骑士相互连边他们一定属于同一个双联通分量（dcc）,

可以自己手动画几个图看看，如果你不造神马是双联通分量，可以去问问度娘

于是现在我们只要求出所有的dcc，再利用二分图染色的思想判断它是否

为二分图，即骑士是否构成了奇环（此时它们构成的图就不是二分图了）

求双联通分量当然要请出我们的$tarjan$大神了

下面奉上我丑陋的代码（求双联通部分是借鉴[Paranoid丶离殇](https://www.luogu.org/space/show?uid=151852)dalao的）

## code

```cpp
#include<bits/stdc++.h>
#define R register

using namespace std;
const int N = 1005;
const int M = 1e6+5;
struct saber {
	int nxt,to;
}rin[M<<1];
int head[M<<1];
int low[N],dfn[N];
int c[N],vis[N],can[N];
int n,m,tot,id,cnt,now,ans;
bool hate[N][N],flag;
vector<int> dcc[N];
stack<int> s;

inline void add(int from,int to) {
	rin[++cnt].to = to;
	rin[cnt].nxt = head[from];
	head[from] = cnt;
}

inline void init() {
	memset(head,0,sizeof(head));
    memset(dfn,0,sizeof(dfn));
    memset(can,0,sizeof(can));
    memset(vis,0,sizeof(vis));
    for(R int i = 1;i <= n;++ i) dcc[i].clear();
    cnt = 1,id = ans = tot = 0;
    for(R int i = 1;i <= n;++ i)
        for(R int j = 1;j <= n;++ j)
			hate[i][j] = 0;
}

void tarjan(int x,int root) {
    dfn[x] = low[x] = ++ id;
    s.push(x);
    if(x == root && !head[x]) {
        dcc[++tot].push_back(x);
        return;
    }
    for(R int i = head[x]; i ;i = rin[i].nxt) {
        int vc = rin[i].to;
        if(!dfn[vc]) {
            tarjan(vc,root);
            low[x] = min(low[x],low[vc]);
            if(low[vc] >= dfn[x]) {
                tot ++; int k;
                do {
                    k = s.top();
                    s.pop();
                    dcc[tot].push_back(k);
                } while (k != vc);
                dcc[tot].push_back(x);
            }
        }
        else low[x] = min(low[x],dfn[vc]);
    }
}

void dfs(int x,int col) {
    c[x] = col;
    for(R int i = head[x]; i ;i = rin[i].nxt) {
        int vc = rin[i].to;
        if(vis[vc] != now) continue;
        if(c[vc] && c[vc] == col) {
            flag = 1;return;
        }
        if(!c[vc]) dfs(vc,3 - col);
    }
}

int main() {
	while(cin>>n>>m) {
		if(n == 0 && m == 0) break;
        init();
        for(R int i = 1,u,v;i <= m;++ i) {
            scanf("%d%d",&u,&v);
            if(u == v) continue;
            hate[u][v] = hate[v][u] = 1;
        }
        for(R int i = 1;i < n;++ i)
            for(R int j = i + 1;j <= n;++ j)
                if(!hate[i][j]) 
					add(i,j),add(j,i);
        for (int i = 1; i <= n; i++)
            if (!dfn[i]) tarjan(i, i);       
		for(R int i = 1;i <= tot;++ i) {
            now = i;
            for(R int j = 0;j < dcc[i].size();++ j)
                vis[dcc[i][j]] = now, c[dcc[i][j]] = 0;
            flag = false;
            if(dcc[i].size()) dfs(dcc[i][0],1);
            if(flag)
            	for(R int j = 0;j < dcc[i].size();++ j)
                    can[dcc[i][j]] = 1;
        }
        for(R int i = 1;i <= n;++ i)
            if(!can[i]) ans ++;
        printf("%d\n",ans);
    }
    return 0;
}
```


---

## 作者：hicc0305 (赞：7)

## 题目描述
有n个骑士经常举行圆桌会议，商讨大事。每次圆桌会议至少有3个骑士参加，且相互憎恨的骑士不能坐在圆桌的相邻位置。如果发生意见分歧，则需要举手表决，因此参加会议的骑士数目必须是大于1的奇数，以防止赞同和反对票一样多。知道那些骑士相互憎恨之后，你的任务是统计有多少骑士不可能参加任何一个会议。

### Input Data
包含多组数据，每组数据格式如下：
第一行为两个整数n和m（1<=n<=1000, 1<=m<=10^6）。 
以下m行每行包含两个整数k1和k2(1<=k1,k2<=n），表示骑士k1和k2相互憎恨。
输入结束标记为n=m=0

### Output Data
对于每组数据，在一行中输出一个整数，即无法参加任何会议的骑士个数。

### Input sample
5 5

1 4

1 5

2 5

3 4

4 5

0 0

### Output sample
2



------------


------------


------------

## 题解部分
本题利用二分图+双连通分量解决。首先，可以把所有相互之间不憎恨的骑士连接一条无向边，那么题目转化为在这个无向图中有多少个结点不在任何一个简单奇圈上。这里的“简单奇圈”指的是圈上顶点个数为奇数，且每个结点只会出现在一个圈中。简单圈上的点一定属于同一个双连通分量，因此需要事先找到所有的双连通分量，而二分图中是没有奇圈的，因此我们只需要关注那些不是二分图的双连通分量即可。

但是不是所有双连通分量上的点都在奇圈上呢？答案是肯定的，证明如下

假设u1,u2所在一个奇圈C上，那么必然存在2条从u1到u2的路径，而且长度为一奇一偶，如果新添加一个结点v,它的一条边连接u1,另一条边连接u2，可以发现，u1经过v到达u2的路径长度为偶数，加上原来存在的那个长度为奇数的路径，恰好构成一个新的奇圈。由此证明了所有点都在奇圈上。

所以只用求出所有点双连通分量，再判断这些点双连通分量是否为二分图，不为二分图的就是奇圈。那么这些连通分量上的点，也就是骑士都能参加会议，最后输出n减去能参加会议的骑士数量。
```cpp
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
struct Stuck
{
    int u,v;
}s[10000];
int n,m,cnt=0,tot=0,num=0,p=0;
int head[200010],nxt[200010],to[200010];
int low[1010],pre[1010],f[1010];
int no[1010][1010],odd[1010],col[1010];
vector <int> vec[1000];
void addedge(int x,int y)
{
    cnt++;
    nxt[cnt]=head[x];
    head[x]=cnt;
    to[cnt]=y;
}
void dfs(int u,int fa)//tarjan求点连通分量
{
    low[u]=pre[u]=++tot;
    for(int i=head[u];i!=-1;i=nxt[i])
    {
        int v=to[i];
        if(!pre[v])
        {
            s[++p].u=u,s[p].v=v;
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(low[v]>=pre[u])
            {
                num++;
                vec[num].clear();
                while(p)
                {
                    if(f[s[p].u]!=num) vec[num].push_back(s[p].u),f[s[p].u]=num;
                    if(f[s[p].v]!=num) vec[num].push_back(s[p].v),f[s[p].v]=num;
                    if(s[p].u==u && s[p].v==v) break;
                    p--;
                }
                p--;
            }
        }
        else if(pre[v]<pre[u] && v!=fa)
        {
            s[++p].u=u,s[p].v=v; 
            low[u]=min(low[u],pre[v]);
        }
    }
}
int half(int u,int k)//二分图染色，判断是否为二分图
{
    for(int i=head[u];i!=-1;i=nxt[i])  
    {
        int v=to[i];  
        if(f[v]!=k) continue;  
        if(col[v]==col[u]) return 0;  
        if(!col[v])  
        {  
            col[v]=3-col[u];  
            if(!half(v,k)) return 0;
        }
    }
    return 1;
}
int main()
{
    while(1)
    {
        memset(f,0,sizeof(f));
        memset(no,0,sizeof(no));
        memset(pre,0,sizeof(pre));
        memset(low,0,sizeof(low));
        memset(odd,0,sizeof(odd));
        memset(head,-1,sizeof(head));
        cnt=0,tot=0,num=0,p=0;
        scanf("%d%d",&n,&m);
        if(!n && !m) break;
        for(int i=1;i<=m;i++)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            if(!x && !y) break;
            no[x][y]=1;
            no[y][x]=1;
        }//建立原图的补图，将可以在一起的骑士连边
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
            {
                if(i==j || no[i][j]) continue;
                addedge(i,j);
            }
        for(int i=1;i<=n;i++)
            if(!pre[i]) dfs(i,0);
        for(int i=1;i<=num;i++)
        {
            memset(col,0,sizeof(col));
            for(int j=0;j<vec[i].size();j++)
                f[vec[i][j]]=i;
            col[vec[i][0]]=1;
            if(!half(vec[i][0],i))
            {//若不为二分图则都打上标记
                for(int j=0;j<vec[i].size();j++)
                    odd[vec[i][j]]=1;
            }
        }
        int ans=n;
        for(int i=1;i<=n;i++)
            if(odd[i]) ans--;
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：Yaha (赞：4)

### 点双连通分量

参考了李煜东大佬《算法竞赛进阶指南》中的思路

#### 题意：

无向图，求有多少个点不被任何奇环包含。$n\le 10^3$

#### 思路：

结合“无向图” “环” “点被环包含”这些字眼，我们也许能联想到点双连通分量。

	点双连通分量：满足点数小于2，或者任何两个点同时包含至少一个简单环中。

我们分两种情况来讨论：

- **对于两个不同的点双连通分量，不可能有奇环横跨**。

否则，大概是这个样子的：

![](https://cdn.luogu.com.cn/upload/image_hosting/2f4gav1w.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

即两个双连通分量 A 和 B ，有环 C 横跨，这时删掉图上任何一点，这个新的子图中任意两个点可互达。所以这该是一个更大的点双连通分量才对，跟点双连通分量的的“极大性”矛盾。

- **对于一个点双连通分量，若出现奇环，则这个点双连通分量中的所有点都能被至少一个奇环包含**

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/eo7mobr1.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

由于是双连通分量，环上必然存在两个点 $i$ ， $j$ ，满足有一个同时包含 $i$ ， $j$ ，$x$ 的简单环。

![](https://cdn.luogu.com.cn/upload/image_hosting/q7c1f76y.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

我们把奇环拆成两部分：奇 $+$ 偶。 $c$ 和 $d$ 必然一奇一偶。

若 $c+a+b$ 为奇环的话，$x$ 被奇环包含；

否则 $d+a+b$ 一定为奇环，$x$ 被奇环包含。

所以，我们先求点双连通分量，再求是否有奇环，若有，上面的所有点都不用被踢出去，即不计入答案。

求奇环可以用染色法。

代码：

```cpp
#include<bits/stdc++.h>

using namespace std;

const int amou=1100,M=2e6+90;

int n,m;
bool ag[amou][amou];
int nxt[M],head[amou],ver[M],cnt;
int dfn[amou],low[amou],timestamp;
int stac[amou],top;
int col[amou],v_dcc,root;
vector<int> V[amou];
int block[amou];
bool we[amou];
bool is_cut[amou];

void add(int a,int b){
	nxt[++cnt]=head[a],head[a]=cnt,ver[cnt]=b;
}

void init(){
	memset(dfn,0,sizeof dfn);
	memset(low,0,sizeof low);
	memset(head,0,sizeof head);
	memset(nxt,0,sizeof nxt);
	memset(ver,0,sizeof ver);
	for(int i=1;i<=v_dcc;i++) V[i].clear();
	memset(block,0,sizeof block);
	memset(col,0,sizeof col);
	memset(is_cut,0,sizeof is_cut);
	top=timestamp=v_dcc=0;
}

void Tarjan(int x){
	dfn[x]=low[x]=++timestamp;
	stac[++top]=x;
	int child=0;
	for(int io=head[x];io;io=nxt[io])
	{
		int v=ver[io];
		if(!dfn[v])
		{
			child++;
			Tarjan(v);
			low[x]=min(low[x],low[v]);
			if(dfn[x]<=low[v])
			{
				if(x!=root||child>1) is_cut[x]=1;
				int p;
				V[++v_dcc].push_back(x);
				do{
					p=stac[top--];
					V[v_dcc].push_back(p);
					block[p]=v_dcc;
				}while(p!=v);
			}
		}
		else low[x]=min(low[x],dfn[v]);
	}
}

bool dfs(int i,int color,int piece){
	col[i]=color;
	bool fl=0;
	for(int io=head[i];io;io=nxt[io])
	{
		int v=ver[io];
		if(block[v]!=piece) continue;
		if(!col[v])
		{
			if(dfs(v,3-color,piece))
				return true;
		}
		if(col[v]==color) return true;
	}
	return false;
}

int main(){
	while(scanf("%d%d",&n,&m),(n||m))
	{
		for(int i=1;i<=m;i++)
		{
			int a,b;
			scanf("%d%d",&a,&b);
			ag[a][b]=ag[b][a]=1;
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=i+1;j<=n;j++)
			{
				if(!ag[i][j]) add(i,j),add(j,i);
				else ag[i][j]=ag[j][i]=0;
			}
		}
		for(int i=1;i<=n;i++)
		{
			if(!dfn[i]) root=i,Tarjan(i);
		}
		for(int i=1;i<=v_dcc;i++)
		{
			for(int j=0;j<V[i].size();j++)
			{
				int x=V[i][j];
				if(is_cut[x]) block[x]=i;
				col[x]=0;
			}
			if(dfs(V[i][0],1,i))
			{
				for(int j=0;j<V[i].size();j++)
				{
					int x=V[i][j];
					we[x]=1;
				}
			}
		}
		int as=0;
		for(int i=1;i<=n;i++)
		{
			if(!we[i]) as++;
			else we[i]=0;
		}
		printf("%d\n",as);
		init();
	}
	
	return 0;
}
```



---

## 作者：chenxia25 (赞：3)

昨天看到奇数个相邻点没边的环这玩意感觉很奇怪，怎么想都没有思路。今天再一看就茅塞顿开了——建反图之后一个奇环就对应一种方案。所以 $n\leq 1000$ 的数据范围不是给的玩的。

我们知道如何判断一个图是否存在奇环——二分图染色即可。但是如何判断是否存在包含指定点的奇环呢？

首先一个点在至少一个简单环上当且仅当它所在点双大小 $\geq 3$。所以这个问题应该不弱于点双。先求出所有点双看看。

那么一个环肯定是在某个点双内部，不可能跨点双。如果一个点双通过了二分图测试，那肯定萎了；否则至少有一个奇环。奇环这东西很有趣，把它劈成两半一定变成一奇一偶；而且与之有一段公共部分的环上也一定所有点都在奇环上——如果新环是奇环那确实了，否则可以把公共部分换成原公共部分相对奇环的补集。

那很自然地引出一个猜想：如果一个点双连通图内至少有一个奇环，那么所有点都在至少一个奇环上。根据上述思想，不断地叠加环到已有的奇环上，觉得这个结论很对。但我们需要一个严谨的证明。

先考虑一个奇环。然后对任意环外点 $x$，尝试联络奇环。考虑奇环上的任意一个点 $y$，那么 $x,y$ 至少在一个环上。如果这个环跟奇环有交点，那么 $x\to y$ 两条路各取第一个交点就可以归约到上述有一段公共部分的两个环的情况。否则的话，另找一个奇环上的点 $z\neq y$ 满足存在 $x\to z$ 的不交于奇环的路径（根据点双性一定存在 $z$），尝试从它与 $x\to y$ 两条路除了端点的部分不交地走到 $x$。如果成功了，那又可以归约；如果交上了，立刻停止，此时形成了环叠环叠环，归约两次即可。

最后就对每个点双跑一下染色，失败了的话内部的点全部可行。最后数不可行的。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
const int N=2010;
int n,m,qu;
int to[N][N];
vector<int> nei[N];
int dfn[N],low[N],nowdfn;
int stk[N],top;
bool shd[N];
int col[N];
bool dfs(int x,int c=1){
	if(col[x]){
		if(col[x]==c)return true;
		return false;
	}
	col[x]=c;
	for(int i=0;i<nei[x].size();i++){
		int y=nei[x][i];
		if(shd[y]&&!dfs(y,3-c))return false;
	}
	return true;
}
bool isans[N];
void tar(int x=1,int fa=0){
	stk[top++]=x;
	dfn[x]=low[x]=++nowdfn;
	if(!fa&&nei[x].size()==0)return;
	for(int i=0;i<nei[x].size();i++){
		int y=nei[x][i];
		if(y==fa){fa=-1;continue;}
		if(!dfn[y]){
			tar(y,x),low[x]=min(low[x],low[y]);
			if(dfn[x]<=low[y]){
				vector<int> v;
				while(true){
					int z=stk[--top];
					v.pb(z);shd[z]=true;
					if(z==y)break;
				}
				v.pb(x);shd[x]=true;
				if(!dfs(x)){
					for(int j=0;j<v.size();j++)isans[v[j]]=true;
				}
				for(int j=0;j<v.size();j++)shd[v[j]]=false,col[v[j]]=0;
			}
		}
		else low[x]=min(low[x],dfn[y]);
	}
}
void mian(){//remember to make it first
	nowdfn=top=0;
	for(int i=1;i<=2*n;i++)nei[i].clear(),dfn[i]=isans[i]=0;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)to[i][j]=i!=j;
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		to[x][y]=to[y][x]=0;
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(to[i][j])nei[i].pb(j);
	for(int i=1;i<=n;i++)if(!dfn[i])tar(i);
	int ans=0;
	for(int i=1;i<=n;i++)ans+=isans[i];
	printf("%d\n",n-ans);
}
int main(){
	while(cin>>n>>m,n)mian();
	return 0;
}
```

---

## 作者：Object_ (赞：2)

**易错点：**

- 为了防止错误加边（自环，即i==j），可将加边时的第二层遍历从i+1开始，由对称性可知加边无错误.
- vector直接用[]比at()更美观.
- 对于每个dcc都要重置一次color，这是因为同一个点可能属于多个dcc.

------------
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
const int MAXN=2e3,MAXM=2e6;
struct Edge{
	int from,to,w,nxt;
}e[MAXM];
int head[MAXN],edgeCnt=1;
void addEdge(int u,int v,int w){
	e[++edgeCnt].from=u;
	e[edgeCnt].to=v;
	e[edgeCnt].w=w;
	e[edgeCnt].nxt=head[u];
	head[u]=edgeCnt;
}
int dfn[MAXN],dfnCnt=0,low[MAXN];
vector<int> dcc[MAXN];
int dccCnt=0,c[MAXN];//in which dcc
int stck[MAXN],top=0;
void tarjan(int x,int root){
	dfn[x]=low[x]=++dfnCnt;
	stck[++top]=x;
	if(x==root&&(!head[x])){
		dcc[++dccCnt].push_back(x);
		return;
	}
	for(int i=head[x];i;i=e[i].nxt){
		int nowV=e[i].to;
		if(!dfn[nowV]){
			tarjan(nowV,root);
			low[x]=min(low[x],low[nowV]);
			if(low[nowV]>=dfn[x]){
				int y;dccCnt++;
				do{
					y=stck[top--];
					dcc[dccCnt].push_back(y);
				}while(y!=nowV);
				dcc[dccCnt].push_back(x);
			}
		}else low[x]=min(low[x],dfn[nowV]);
	}
}
bool canAttend[MAXN],flag=0;
int color[MAXN];
void dfs(int x,int restColor){
	color[x]=restColor;
	for(int i=head[x];i;i=e[i].nxt){
		int nowV=e[i].to;
		if(c[nowV]!=c[x])continue;
		if(!color[nowV])dfs(nowV,3-restColor);
		else if(color[nowV]==color[x]){
			flag=1;
			return;
		}
	}
}
bool hate[MAXN][MAXN];
int n;
void init(){
	memset(head,0,sizeof(head));
	edgeCnt=1;
	memset(hate,0,sizeof(hate));
	memset(dfn,0,sizeof(dfn));
	dfnCnt=0;
	memset(low,0,sizeof(low));
	for(int i=1;i<=n;i++){
		dcc[i].clear();
	}
	dccCnt=0;
	memset(c,0,sizeof(c));
	memset(canAttend,0,sizeof(canAttend));
	top=0;
}
int main(){
	while(1){
		init();
		int m;
		scanf("%d%d",&n,&m);
		if(!n||!m)break;
		for(int i=1;i<=m;i++){
			int a,b;
			scanf("%d%d",&a,&b);
			hate[a][b]=hate[b][a]=1;
		}
		for(int i=1;i<n;i++){//
			for(int j=i+1;j<=n;j++){
				if(!hate[i][j]){
					addEdge(i,j,1);
					addEdge(j,i,1);
				}
			}
		}
		for(int i=1;i<=n;i++){
			if(!dfn[i])tarjan(i,i);
		}
		for(int i=1;i<=dccCnt;i++){
			for(int j=0;j<dcc[i].size();j++){
				c[dcc[i][j]]=i;//
				color[dcc[i][j]]=0;//
			}
			flag=0;
			dfs(dcc[i][0],1);
			if(flag){//can attend
				for(int j=0;j<dcc[i].size();j++){
					canAttend[dcc[i][j]]=1;
				}
			}
		}
		int ans=0;
		for(int i=1;i<=n;i++){
			if(!canAttend[i])ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：highscore (赞：1)

前置知识：点双，二分图判定

[不会点双的可以去这里哦](https://www.cnblogs.com/Aswert/p/14273854.html)

会了前置知识后，我们来看这道题。

首先，我们可以把不讨厌的人之间建图，就是在两个人之间连一条无向边；
那么一名骑士能参见会议的条件是，它对应的节点在一个奇环上；
所以本题就是找不被任何奇环包含的节点。

那么我们来看两个引理

1.若两个节点不在一个点双内，那么这两个节点不可能一起出席会议.


2.若两个点双内存在奇环，则这个点双中的所有点都至少有一个奇环包含；

那么这道题就可以做了，先求出点双，然后判断点双内有没有奇环即可，

AC代码
```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
const int N=1010;
const int M=1e6+7;
struct edge{
	int v,nxt;
}e[M<<1];
int n,m,cnt,rt,h,now,flag,tot,ans;
int a[N][N],st[N],head[N],g[N],c[N],dfn[N],low[N],ok[N];
vector<int> dcc[N];

void init(){
	tot=0;
	h=0;
	ans=0;
	cnt=0;
	memset(head,0,sizeof(head));
	memset(ok,0,sizeof(ok));
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	memset(g,0,sizeof(g));
	for(int i=1;i<=n;i++) dcc[i].clear();
} 

void add_edge(int u,int v){
	e[++cnt]=(edge){v,head[u]};
	head[u]=cnt;
}

void tarjan(int u){
	dfn[u]=low[u]=++tot;
	if(u==rt&&head[u]==0){
		dcc[++cnt].push_back(u);
		return;
	}
	st[++h]=u;
	for(int i=head[u];i;i=e[i].nxt){
		int to=e[i].v;
		if(!dfn[to]){
			tarjan(to);
			low[u]=min(low[u],low[to]);
			if(dfn[u]<=low[to]){
				cnt++;
				int k;
				do{
					k=st[h];h--;
					dcc[cnt].push_back(k);
				}while(k!=to);
				dcc[cnt].push_back(u);
			}
		}else low[u]=min(low[u],dfn[to]);
	}
}

void dfs(int u,int color){
	if(flag) return;
	c[u]=color;
	for(int i=head[u];i;i=e[i].nxt){
		int to=e[i].v;
		if(g[to]!=now) continue;
		if(c[to]==color){
			flag=1;
			return;
		}
		if(!c[to]) dfs(to,3-color);
	}
}


int main(){
	while(scanf("%d%d",&n,&m),(n+m)){
		init();
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				a[i][j]=0;
			}
		}
		for(int i=1;i<=m;i++){
			int x,y;
			scanf("%d%d",&x,&y);
			if(x!=y){
				a[x][y]=a[y][x]=1;
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<i;j++){
				if(!a[i][j]){
					add_edge(i,j);
					add_edge(j,i);
				}
			}
		}
		cnt=0;
		for(int i=1;i<=n;i++){
			if(!dfn[i]){
				rt=i;
				tarjan(i);
			}
		}
		for(int i=1;i<=cnt;i++){
			now=i;
			flag=0;
			for(int j=0;j<(int)dcc[i].size();j++){
				g[dcc[i][j]]=now;
				c[dcc[i][j]]=0;
			}
			dfs(dcc[i][0],1);
			if(flag){
				for(int j=0;j<(int)dcc[i].size();j++){
					ok[dcc[i][j]]=1;
				}
			}
		}
		for(int i=1;i<=n;i++){
			if(ok[i]!=1) ans++;
		}
		cout<<ans<<"\n";
	}
}
/*
5 5
1 4
1 5
2 5
3 4
4 5
5 5
1 4
1 5
2 5
3 4
4 5
0 0
*/
```

---

## 作者：fanzhengyang (赞：1)

这题真的有点恶心心 课上做1小时 课下调5小时

倒也有了更深刻的认识 更重要的居然是练习了挑错（没删调试注释的版本可以在提交列表里找hhh）给自己写的注释都详细到可以交题解了

思路：
**求补图 + tarjan求dcc(点双连通分量) + 二分图染色判定奇偶**

（三个图刚好存的方式都不一样）

几个注意点：

1. 害我一直调的低级错误（悲）：染色的时候是**dfs相邻点** 我一直循环的是dcc里的点...

2. tarjan**不考虑只包含一个点的dcc**应该是没有问题的 因为题目要求是3及以上的奇数

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
//(///▽///)~!
using namespace std;
//补图
//tarjan求双连通分量
//染色判断是否为二分图即是否存在奇环
//起始图、补图、dcc分别用邻接矩阵、邻接表、vector存
int n,m; 
bool hate[1005][1005];//存起始图 
int ok[1005];//最后用来筛查 

struct e{
	int to,next;
}edge[1005*1005];//存补图 
int cnt,head[1005];
void add(int from,int to)
{
	edge[++cnt].to=to;
	edge[cnt].next=head[from];
	head[from]=cnt;
}

vector<int> dcc[1005];//存某个dcc上的所有点 
int id[1005];//存某点所在dcc编号 在main函数里求 
int pre[1005],low[1005];
int dfsCnt;//dfs层数 
int nodeCnt;//dcc个数 
stack<int> s;//暂时存dfs到的点 发现dcc就把栈里东西加到vector里并pop 
void tarjan(int u,int dad)
{
	pre[u]=low[u]=++dfsCnt;
	s.push(u);
	/*if(dad==0&&!head[u])//这里注释掉应该没有问题
	{
		dcc[++nodeCnt].push_back(u);
		return;
	}*/
	for(int i=head[u];i;i=edge[i].next)
	{
		int v=edge[i].to;
		if(v==dad) continue;
		if(pre[v]==0)
		{
			tarjan(v,u);
			low[u]=min(low[u],low[v]);
			if(low[v]>=pre[u])
			{
				nodeCnt++;
				while(1)
				{
					int tmp=s.top(); s.pop();
					dcc[nodeCnt].push_back(tmp);
					if(tmp==v) break;
				}
				dcc[nodeCnt].push_back(u);
			}
		}
		else low[u]=min(low[u],pre[v]);
	}
}

int color[1005];//记颜色 1黑2白 
bool Half(int u)//二分图染色 若不是二分图 即有奇数个点 则返回1 
{
	for(int i=head[u];i;i=edge[i].next)//我这里写错 
	{
		int v=edge[i].to;
		if(id[v]!=id[u]) continue;//不在染色的dcc上 
		if(color[u]==color[v]) return 1;
		else if(!color[v])
		{
			color[v]=3-color[u];
			if(Half(v)) return 1; 
		}
	}
	return 0;
}

void init()
{
	cnt=0; dfsCnt=0; nodeCnt=0;
	memset(hate,0,sizeof(hate));
	memset(ok,0,sizeof(ok)); 
    memset(head,0,sizeof(head));
    memset(id,0,sizeof(id));
    memset(pre,0,sizeof(pre));
    memset(low,0,sizeof(low));
	for(int i=1;i<=n;i++) dcc[i].clear();
}

int main()
{
	while(1)
	{
		cin>>n>>m;
		if(n==0&&m==0) return 0;
		init();
		for(int i=1;i<=m;i++)
		{
			int u,v;
			cin>>u>>v;
			hate[u][v]=hate[v][u]=1; 
		}
		for(int i=1;i<=n;i++)//建立补图 
        	for(int j=1;j<=n;j++)
            	if(i!=j&&!hate[i][j])
	            	add(i,j);//这里建一个方向即可 
		for(int i=1;i<=n;i++)
			if(!pre[i]) tarjan(i,0);
		for(int i=1;i<=nodeCnt;i++)//遍历每个dcc判断是否是二分图 即是否是奇数 
		{
			for(int j=0;j<dcc[i].size();j++) id[dcc[i][j]]=i;//给dcc上所有点标记
			memset(color,0,sizeof(color));
			color[dcc[i][0]]=1;//随意选dcc上一个点作为起点 设为1
			if(Half(dcc[i][0]))
			for(int j=0;j<dcc[i].size();j++) ok[dcc[i][j]]=1;
		}
		int ans=0;
		for(int i=1;i<=n;i++)
			if(!ok[i]) ans++;
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：地表最强男人 (赞：1)

 先想一下暴力，可以把不相憎恨的所有的点都连边，即两个点不互相憎恨的话就把两个点连起来，然后暴力寻找奇环，把奇环上的点都标记起来，最后把没有被标记的点输出。但是这样把每一个奇环找出来好像比较困难，因为一个点双连通分量中可能有多个奇环，也可能没有奇环，如果都要找出来需要用很多遍dfs。不过可以推理出这样的引理：
 - 奇环是不可以被黑白染色的（即不是二分图）
 - 如果一个点双连通分量中有一个奇环，那么这个点双连通分量中所有的点都被至少一个奇环包括
对于引理1，这个不用证明（画个图就懂了），而对于引理2的证明
![](https://cdn.luogu.com.cn/upload/image_hosting/b6rmstde.png)
中间用红色标注的是奇环，而可以发现，如果一个点双连通块的两边和一个奇环相连会将奇环分成两个部分，一个部分是奇数部分（点的个数），另一个是偶数部分（点的个数）。
![](https://cdn.luogu.com.cn/upload/image_hosting/auskqn57.png)
绿色的部分是偶数的部分，蓝色是奇数部分，分别和右边的点双连通分量组成奇环和偶环，如果右边的点双连通分量是奇数个数的，那么可以和偶数部分组成奇环，如果右边的点双连通分量是偶数个数的，那么可以和奇数部分组成奇环。即一定可以凑成奇环。那么就证明完了。

回到题目，我们对于每一个点双连通分量都尝试着染色，如果不能染色，那么说明这个强连通分量中一定有奇环，然后将所有的点都标记上。最后再枚举所有的点，把所有没有被标记的点统计起来，就是答案了。
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int N=1010,M=2001000;
int n,m;
int head[N],ver[M<<1],Next[M<<1],tot;//补图，表示两个不相憎恨的点 
int dfn[N],low[N],stack[N<<1],top,cnt,num,able[N];//able代表是否能够出席 
int v[N],c[N],ans,now;//v代表属于的连通块，c代表颜色 
vector<int> dcc[N];//记录点双连通分量 
bool hate[N][N],flag;
void add(int x,int y)
{
	ver[++tot]=y;
	Next[tot]=head[x],head[x]=tot;
}
void pre()
{
	memset(head,0,sizeof(head));
	memset(hate,0,sizeof(hate));
	memset(stack,0,sizeof(stack));
	memset(v,0,sizeof(v));
	memset(dfn,0,sizeof(dfn));
	tot=0;
	memset(able,0,sizeof(able));
	top=cnt=num=0;
	memset(c,0,sizeof(c));
	for(int i=1;i<=n;i++)
		dcc[i].clear();
}
void tarjan(int x,int root)//标准的tarjan 
{
	dfn[x]=low[x]=++num;
	stack[++top]=x;
	if(x==root&&head[x]==0)
	{
		dcc[++cnt].push_back(x);
		return ;
	}
	for(int i=head[x];i;i=Next[i])                
	{
		int y=ver[i];
		if(!dfn[y])
		{
			tarjan(y,root);
			low[x]=min(low[x],low[y]);
			if(low[y]>=dfn[x])
			{
				cnt++;
				int z;
				do
				{
					z=stack[top--];
					dcc[cnt].push_back(z);
				}while(z!=y);
				dcc[cnt].push_back(x);
			}
		}
		else low[x]=min(low[x],dfn[y]);
			
	}
}
void dfs(int x,int col)//染色 
{
	c[x]=col;
	for(int i=head[x];i;i=Next[i])
	{
		int y=ver[i];
		if(v[y]!=now)//不属于连通块 
			continue;
		if(c[y]&&c[y]==col)//不能染色 
		{
			flag=1;
			return ;
		}
		if(!c[y])
			dfs(y,3-col);
	}
}
int main()
{
	cin>>n>>m;
	while(n!=0||m!=0)
	{
		pre();
		for(int i=1;i<=m;i++)
		{
			int x,y;
			cin>>x>>y;
			if(x==y)	continue;
			hate[x][y]=1;
			hate[y][x]=1;
		}
		for(int i=1;i<n;i++)
			for(int j=i+1;j<=n;j++)
				if(hate[i][j]==0)
				{
					add(i,j);
					add(j,i);
				}
		for(int i=1;i<=n;i++)
			if(!dfn[i])
				tarjan(i,i);
		for(int i=1;i<=cnt;i++)
		{
			now=i;
			for(int j=0;j<dcc[i].size();j++)
				v[dcc[i][j]]=now,c[dcc[i][j]]=0;
			flag=false;//是否有奇环 
			dfs(dcc[i][0],1);
			if(flag)
				for(int j=0;j<dcc[i].size();j++)
					able[dcc[i][j]]=1;
		}
		ans=0;
		for(int i=1;i<=n;i++)
			if(!able[i])
				ans++;
		cout<<ans<<endl;
		cin>>n>>m;
	}
	return 0;
}
```


---

