# [CEOI 2005] Critical Network Lines

## 题目描述

一个通信网络包含若干个节点，以及若干条直接连接这些节点的双向**通信线路**。已知所研究的通信网络是连通的，即：任意一对节点之间都存在（若干条**通信线路**首尾相接而成的）**通信路径**。

一些节点会向所有节点（包括它自己）提供 $A$ 类型服务，还有一些节点会向所有节点（包括它自己）提供 $B$ 类型服务。一个节点可能会同时提供两种类型的服务。每个节点都必须要访问这两种服务。

当一条**通信线路**断开时，可能会出现某个节点不能访问某种服务的情况。（即：存在某个节点以及某种服务，使得不存在任何提供该类型服务，且与该节点连通的节点）我们称会造成这种情况的**通信线路**为**关键通信线路**。

你的任务是，写一个程序计算有多少条**关键通信线路**，并求出每条**关键通信线路**所连接的两个端点。

## 说明/提示

本题为 CEOI2005 D2T2，原题面请见：[Critical Network Lines](http://ceoi.inf.elte.hu/ceoi2005/download/tasks/day2/net.htm)。

感谢 @[wsyhb](https://www.luogu.com.cn/user/145355) 提供的 Special Judge！

## 样例 #1

### 输入

```
9 10 3 4
2 4 5
4 9 8 3
1 2
4 1
2 3
4 2
1 5
5 6
6 7
6 8
7 9
8 7```

### 输出

```
3
3 2
5 6
7 9```

# 题解

## 作者：小小小朋友 (赞：15)

## 思路

显然，答案肯定是割边。

tarjan 求出所有割边，在 tarjan 的 dfs 的时候维护出此节点的子树中服务 A 和服务 B 的数量。

如果此子树中并不包含服务 A 或者服务 B ，或者包含了全部服务 A 或者服务 B，那么这个点到这个子树的边即为一条关键边。

此题搬运的时候没有搬运 spj……所以这个代码暂时过不了。


## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005],b[100005],dfn[100005],low[100005],cnt,ans,tot,n,m,l,k;
vector<int> v[100005];
vector<int> ans1,ans2;
void tarjan(int u,int fa){//tarjan模板
	dfn[u]=low[u]=++tot;
	for(int nv:v[u]){//C++11语法，遍历子节点
		if(!dfn[nv]){//找到割边
			tarjan(nv,u);
			low[u]=min(low[u],low[nv]);
			if(low[nv]>dfn[u]){
				if(!a[nv]||!b[nv]||a[nv]==l||b[nv]==k){//没有A/B，或者A/B全在子树
					ans++;ans1.push_back(nv);ans2.push_back(u);
				}
			}
			a[u]+=a[nv],b[u]+=b[nv];
		}
		if(nv!=fa){
			low[u]=min(low[u],dfn[nv]);
		}
	}
}
int main(){
	cin>>n>>m>>l>>k;
	for(int i=1;i<=l;i++){int tmp;cin>>tmp;a[tmp]=1;}
	for(int i=1;i<=k;i++){int tmp;cin>>tmp;b[tmp]=1;}
	for(int i=1;i<=m;i++){
		int a,b;cin>>a>>b;
		v[a].push_back(b);v[b].push_back(a);
	}
	tarjan(1,0);
	cout<<ans<<endl;
	for(int i=0;i<ans;i++) cout<<ans1[i]<<' '<<ans2[i]<<endl;
	return 0;
}
```



---

## 作者：OldVagrant (赞：8)

## 题意
给定一个 $N$ 个点 $M$ 条边的无向连通图，$K$ 个点属于集合 $A$ ，$L$ 个点属于集合 $B$ （可能存在同一节点属于两个集合）。求有多少条边，满足去掉这些边后原图中存在若干个点与至少一个集合中的所有点都不连通，输出满足条件的边的总个数，然后输出这些边的两个端点，顺序任意。   
$1\le N\le 10^5,1\le M\le 10^6,1\le L,K\le N$。保证无自环无重边。
## Solution
由于 $K,L$ 均为正整数，所以如果去掉某条边后原图仍联通，那么该边一定不满足条件，所以满足条件的边一定属于原图的割边（桥）。但是割边不一定都满足条件，还要保证存在点与至少一个集合中所有点都不连通。   
显然去掉一条满足条件的边后，原图会分成若干个互不连通的部分，并且某一部分内部没有点属于 $A$ 或没有点属于 $B$ 。所以可以在求割边的过程中分别统计一下以每个点为根的子树中有多少个点属于 $A$ ，多少个点属于 $B$，暂且把这两个值叫做 $suma,sumb$，然后分两种情况讨论。前提为找到了一条割边 $(u,v)$。
1. 以 $v$ 为根的子树的 $suma$ 或 $sumb$ 为0，那么这条边就是满足条件的，某个集合中的所有点都在子树外，去掉这条边后其子树内所有点都无法到达该集合中任意一点。    
2. 以 $v$ 为根的子树的 $suma=K$ 或 $sumb=L$ ，那么这条边也是满足条件的，某个集合中所有点都在该子树内，去掉这条边后其子树外所有点都无法到达该集合中任意一点。

如果属于以上两种情况中的任意一种，那么就更新答案，并把该边的两个端点存储下来。更新每个点的 $suma$ 和 $sumb$ 也很好更新，dfs 回溯时统计即可。然后剩下的就是求割边的事了，用 ```tarjan``` 即可以 $O(N+M)$ 的时间复杂度求出割边，空间复杂度也为 $O(N+M)$。
## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define gc getchar
#define pc(x) putchar(x)
int suma[100001],sumb[100001],a,b,ecnt=1,n,m,ne[2000001],to[2000001],head[100001],dfn[100001],l[100001];//这里的ecnt为1，即让边的编号从2开始，由于每个双向边被拆成的两条有向边的编号一定是连续的，从2开始存便可以充分利用位运算的性质，某个边的编号异或1即为该边的反向边的编号。
int u[1000001],v[1000001],tot,cnt;
bool vis[2000001];
int read(){
	int x=0;
	char ch=gc();
	while(ch<48||ch>57) ch=gc();
	while(ch>47&&ch<58) x=x*10+ch-48,ch=gc();
	return x;
}
void write(int x){
    if(x>9) write(x/10);
    pc(x%10+48);
}
void ae(int x,int y){
	to[++ecnt]=y,ne[ecnt]=head[x],head[x]=ecnt;
}
void tarjan(int x){
	dfn[x]=l[x]=++cnt;
	for(int i=head[x];i;i=ne[i]){
		if(!vis[i]){
			vis[i]=vis[i^1]=1;//这里注意要把一条无向边拆成的两条有向边都标记一下。
			int y=to[i];
			if(!dfn[y]){
				tarjan(y),suma[x]+=suma[y],sumb[x]+=sumb[y],l[x]=min(l[x],l[y]);//dfs，回溯后更新父亲节点的信息
				if(l[y]>dfn[x]&&(suma[y]==0||sumb[y]==0||suma[y]==a||sumb[y]==b)) u[++tot]=x,v[tot]=y;//如果满足条件则更新答案并存储下来
			}else l[x]=min(l[x],dfn[y]);
		}	
	}
}
signed main(){
	n=read(),m=read(),a=read(),b=read();
	for(int i=1;i<=a;i++) suma[read()]=1;
	for(int i=1;i<=b;i++) sumb[read()]=1;
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		ae(x,y),ae(y,x);
	}tarjan(1),write(tot),pc('\n');
	for(int i=1;i<=tot;i++) write(u[i]),pc(' '),write(v[i]),pc('\n');
	return 0;
}
```



---

## 作者：人间温柔 (赞：6)

容易发现这么一个结论，**关键通信线路**构成的集合是该图桥所构成的集合的子集。即：**关键通信线路** 一定是桥，但桥不一定是 **关键通信线路**。这个结论非常重要。

求桥的方法：tarjan 算法，可参考 [P1656 炸铁路](https://www.luogu.com.cn/problem/P1656)，这是求桥的模板题，建议先将该题 AC，再来康康这题。

我们先画一张 tarjan 算法求桥的图：

![截图20221231144718.png](https://yacs-public.oss-cn-hangzhou.aliyuncs.com/image/1672469265461.png)

我们现在研究 $<u,v>$ 这条边。$<u,v>$ 是桥的充要条件是：$low[v]>dfn[u]$（tarjan 算法的基本原理，在此不多赘述）：

+ 若 $low[v]\leq dfn[u]$，则 $<u,v>$ 不是桥，根据先前得到的结论也不可能是 **关键通信线路**。可以不再考虑。
+ 若 $low[v]> dfn[u]$，则 $<u,v>$ 是桥。我们接下来再来考虑什么情况下是 **关键通信线路**。

一下论述均基于 $<u,v>$ 是桥的情况下。

$<u,v>$ 切断以后，会将图分割为两个不连通的子图：
![截图20221231145534.png](https://yacs-public.oss-cn-hangzhou.aliyuncs.com/image/1672469749748.png)

当其中某个子图（连通块）中，能够提供 $A$ 服务或者能够提供 $B$ 服务的节点个数为 $0$ 时，则这个子图就不能访问其中一种服务。那么 $<u,v>$ 就是所求的 **关键通信线路**。

所以，对于每一个节点 $i$，我们不仅要维护 $low[i]$ 和 $dfn[i]$，还需要维护 $nA[i]$ 和 $nB[i]$，分别表示以 $i$ 为根的子树（注意这里的子树是针对 dfs 树的，而不是针对整个图的）内能够提供 $A$ 服务以及 $B$ 服务的节点个数。这两个数组是能够在 tarjan 算法中一起求出来掉的。

+ 当 $v$ 所在连通块内能够提供某一类服务的节点个数为 $0$ 时，即：$nA[v]=0$ 或 $nB[v]=0$。
+ 当 $u$ 所在连通块内能够提供 $B$ 类服务的节点个数为 $0$ 时，乍一看好像不好判断。但是仔细一想，如果 $u$ 那边没有任何服务，即所有能够提供服务的节点都在 $v$ 所在连通块，也就是 $nA[v]=K$ 或 $nB[v]=L$。（$K,L$ 的意义见题面）。

所以，一条边是关键通信线路，就必须满足上面两个条件中的至少一个，再加上它一定是桥，所以所有满足 $low[v]>dfn[u]$ 且 $nA[v]=0$ 或 $nB[v]=0$ 或 $nA[v]=K$ 或 $nB[v]=L$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=100005;
const int maxm=1000005;

int n,m,K,L;
int service[maxn];
struct node{
	int fr,to,nxt;
}e[maxm<<1];
int cnt=1,head[maxn];
int time_stamp,dfn[maxn],low[maxn],nA[maxn],nB[maxn];
pair<int,int>ans[maxm];
int k;

void add_edge(int u,int v){
	cnt++;
	e[cnt].fr=u;
	e[cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}

void tarjan(int u,int from_edge){
	time_stamp++;
	dfn[u]=low[u]=time_stamp;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!dfn[v]){
			tarjan(v,i);
			low[u]=min(low[u],low[v]);
			nA[u]+=nA[v];
			nB[u]+=nB[v];
			if(low[v]>dfn[u] && ((nA[v]==0 || nA[v]==K) || (nB[v]==0 || nB[v]==L))){
				ans[++k]=make_pair(u,v);
			}
		}
		else if(i!=(from_edge^1)){
			low[u]=min(dfn[v],low[u]);
		}
	}
}

int main(){
	cin>>n>>m>>K>>L;
	for(int i=1;i<=K;i++){
		int x;
		cin>>x;
		nA[x]=1;
	}
	for(int i=1;i<=L;i++){
		int x;
		cin>>x;
		nB[x]=1;
	}
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		add_edge(u,v);
		add_edge(v,u);
	}
	tarjan(1,0);
	cout<<k<<endl;
	for(int i=1;i<=k;i++){
		cout<<ans[i].first<<" "<<ans[i].second<<endl;
	}
	return 0;
}
```

---

## 作者：BigSmall_En (赞：2)

## 题意描述

有一个无向连通图，每个点有对应的服务，分别为 $a$ 和 $b$ 或者没有或者都有。如果有一条边被断开，会有一些点不能同时连接到有服务 $a$ 和 $b$ 的点，则称这条边为关键边，求关键边的数量和每条边的起始和终止点。

## 题解

1. 明显是通过图的连通性方面考虑。如果一条边不是割边，那么即使他去掉了也是不会影响其他点的服务。则只需要考虑割边。
2. 如果这条边是割边，也不一定影响点的服务。
   - 发现对于连通块内的点，只要这个连通块里面没有 $a$ 服务**或** $b$ 服务就是关键边。即`!a[v]||!b[v]` 。
   - 发现对于连通块外的点，如果这个连通块里面有了所有的 $a$ 服务或 $b$ 服务，说明外边的点就不会有 $a$ 或 $b$ 服务了。即 `a[v]==k||b[v]==l`。
3. 那么只需要实时记录一个连通块之内的 $a$ 服务的点数和 $b$ 服务的点数即可。即 `a[u]+=a[v],b[u]+=b[v]` 。

## 代码

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=100005,M=1000006;
int n,m,k,l,ans,a[N],b[N],dfn[N],low[N],tim;
struct chainstar{
	int next,to;
}edge[M<<1];int head[N],cnt;
struct singleline{int f,t;}line[M<<1];
void addline(int u,int v){
	edge[++cnt].to=v;
	edge[cnt].next=head[u];
	head[u]=cnt;
}
void tarjan(int u,int f){
	dfn[u]=low[u]=++tim;
	for(int i=head[u],v;i;i=edge[i].next){
		v=edge[i].to;
		if(!dfn[v]){
			tarjan(v,u);
			low[u]=min(low[u],low[v]);
			if(low[v]>dfn[u]){//这是条割边
				if(!a[v]||!b[v]||a[v]==k||b[v]==l)//满足关键边条件
					{line[++ans].f=u,line[ans].t=v;}//这里是记录关键边
			}
			a[u]+=a[v],b[u]+=b[v];//更新连通块内信息
		}if(v!=f)low[u]=min(low[u],dfn[v]);
	}
}
bool cmp(singleline x,singleline y){
	if(x.f==y.f)return x.t<y.t;
	return x.f<y.f;
}
int main(){
	scanf("%d%d%d%d",&n,&m,&k,&l);
	for(int i=1,ix;i<=k;++i)
		{scanf("%d",&ix);a[ix]=1;}
	for(int i=1,ix;i<=l;++i)
		{scanf("%d",&ix);b[ix]=1;}
	for(int i=1,u,v;i<=m;++i){
		scanf("%d%d",&u,&v);
		addline(u,v);addline(v,u);
	}
	tarjan(1,0);//题目已经给定是连通图了
	sort(line+1,line+1+ans,cmp);//有SPJ了，可以不用排序
	printf("%d\n",ans);
	for(int i=1;i<=ans;++i)
		{printf("%d %d\n",line[i].f,line[i].t);}
	return 0;
}// 442ms /  22.74MB /  1.20KB C++98
```

---

## 作者：McIron233 (赞：1)

本题考查知识点是割点和桥以及对 tarjan 算法的理解。

根据题意或者根据样例，我们不难得出两个结论：

- 是关键通信线路的一定是桥，桥不一定是关键通信线路；

- 满足条件的桥一定会使有一个连通块不存在含服务 $A$ 的点或服务 $B$ 的点。

因此，在 tarjan 的过程中，为关键通信线路的边需要满足下列两个条件：

- 该边为桥；

- 在 DFS 子树里，服务 $A$ 数量为 $0$ 或 $K$，或服务 $B$ 数量为 $0$ 或 $L$。

于是这道题就解决了。

tarjan 代码如下。

```cpp
void tarjan(int u,int fa){
    dfn[u]=low[u]=++Cnt;
    for(int v:e[u]){
        if(v==fa)continue;
        if(!dfn[v]){
            tarjan(v,u);
            low[u]=min(low[u],low[v]);
            if(low[v]>dfn[u] && (!a[v] || !b[v] || a[v]==k || b[v]==l)){
                //这条边是桥，且子树中要么占据所有 A 或 B 服务，要么一个 A 或 B 服务都没有
                ans.push_back(make_pair(u,v));
            }
            a[u]+=a[v]; b[u]+=b[v];
        }else low[u]=min(low[u],dfn[v]);
    }
}
```

---

## 作者：tsqtsqtsq0309 (赞：1)

# [CEOI2005] Critical Network Lines

## 题目大意

给定一个 $N$ 个点 $M$ 条边的无向连通图，其中有 $K$ 个点属于集合 $A$，有 $L$ 个点属于集合 $B$（可能会存在一个点同时属于两个集合的情况）。求图中有多少条边满足去掉这些边中任意一条或多条边时图中存在部分点与至少一个集合中的所有点都不连通，输出满足条件的边的总数并输出这些边的两个端点。其中 $1 \le N \le 10^5$，$1 \le M \le 10^6$，$1 \le K \le N$，$1 \le L \le N$。

## 思路

题目大意中提到了“去掉任意一条或多条边时图中存在部分点与至少一个集合中的所有点都不连通”，由此可以很容易地联想到可以用 `tarjan` 求图中的割边。仔细观察可以发现这道题并不能算是裸的割边，还需要保证存在部分点与至少一个集合中的所有点都不连通。

显然去掉一条满足条件的边后，原图会分成若干个互不连通的部分，并且某一部分内部没有点属于集合 $A$ 或没有点属于 $B$。可以在求割边的过程中分别统计一下以每个点为根的子树中有多少个点属于集合 $A$，多少个点属于集合 $B$，然后再分情况进行讨论。

具体来说，对于图中的任意一点，令这一点为 $x$，则令：
$$
f(x) = \sum_{i\in son(x)}{[i\in A]}
$$
同理：
$$
g(x) = \sum_{i\in son(x)}{[i\in B]}
$$
对于答案统计，具体可以分为两种情况：

1. 如果 $f(x) = 0$ 或 $g(x) = 0$，那么这条边就是满足条件的，某个集合中的所有点都在子树外，去掉这条边后其子树内所有点都无法到达该集合中任意一点。
2. 如果 $f(x) = K$ 或 $g(x) = L$，那么这条边也是满足条件的，某个集合中所有点都在该子树内，去掉这条边后其子树外所有点都无法到达该集合中任意一点。

如果属于以上两种情况中的任意一种，那么就更新答案，并把该边的两个端点存储下来。至于每个点的子树大小直接在 `tarjan` 回溯时顺便统计一下即可。剩下的就是求割边的事了，可以考虑用 `tarjan` 求割边，总的时间复杂度为 $O(N + M)$，总的空间复杂度为 $O(N + M)$，稳过。

具体细节请看代码……

## 代码

```c++
#include <iostream>
#define MAXN 100005
#define MAXM 1000005
using namespace std;
int n, m, k, l, p, q, tot, sum;
struct edge{int from, to, nxt;}e[MAXM << 1];
int dfn[MAXN], low[MAXN], a[MAXN], b[MAXN], head[MAXN], cnt = 1;
struct node{int p, q;}ans[MAXM];
int read(){
    int t = 1, x = 0;char ch = getchar();
    while(!isdigit(ch)){if(ch == '-')t = -1;ch = getchar();}
    while(isdigit(ch)){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * t;
}
void write(int x){
    if(x < 0){putchar('-');x =-x;}
    if(x >= 10)write(x / 10);
    putchar(x % 10 ^ 48);
}
void add(int u, int v){cnt++;e[cnt].from = u;e[cnt].to = v;e[cnt].nxt = head[u];head[u] = cnt;}
void tarjan(int now, int fat){ // 运用 tarjan 求割边
    tot++;dfn[now] = tot;low[now] = tot;
    for(int i = head[now] ; i != 0 ; i = e[i].nxt){
        int v = e[i].to;
        if(dfn[v] == 0){tarjan(v, i);
            low[now] = min(low[now], low[v]);
            a[now] += a[v];b[now] += b[v]; // 更新 f(v) 和 g(v)
            if(low[v] > dfn[now] && ((a[v] == 0 || a[v] == k) || (b[v] == 0 || b[v] == l))){ // 判定割边并分情况讨论
                sum++;ans[sum].p = now;ans[sum].q = v; // 保存答案
            }
        }else if(i != (fat ^ 1)){low[now] = min(low[now], dfn[v]);}
    }
}
int main(){
    n = read();m = read();k = read();l = read();
    for(int i = 1 ; i <= k ; i ++)a[read()] = 1;
    for(int i = 1 ; i <= l ; i ++)b[read()] = 1;
    for(int i = 1 ; i <= m ; i ++){
        p = read();q = read();add(p, q);add(q, p);
    }tarjan(1, 0);write(sum);putchar('\n');
    for(int i = 1 ; i <= sum ; i ++){
        write(ans[i].p);putchar(' ');write(ans[i].q);putchar('\n');
    }return 0;
} // 完结撒花～～
```



---

## 作者：_Ch1F4N_ (赞：1)

考场上数组开大了直接 MLE 了，气。

考虑把 A,B 两种服务分开算，一个边双连通分量内的点如过有一个有服务，那么整个联通分量就都有服务。

然后按边双联通分量缩点后原图变成树，一条边是关键路线当且仅当所有服务都在它的子树内或者子树外，做一遍子树和。

具体来说，令 $sz_i$ 表示子树 $i$ 内的某种服务数量，$sum$ 为这种服务总量，若 $sz_{u} = sum$ 则边 $(u,fa_u)$ 是关键线路。

最后记得空间省着点用，血的教训。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+114;
const int maxm = 2e6+114;
int dfn[maxn],low[maxn],dfncnt;
int n,m;
int head[maxn];
int flag[maxm];
int color[maxn];
int a[maxn],b[maxn];//每个点是否提供某种服务 
int A[maxn],B[maxn];//每个边双内是否提供某种服务 
int cl;
map<int, pair<int,int> > f[maxn];//每个桥连接哪两个点 
vector<int> edge[maxn];//边双缩点完后的树存边 
int father[maxn];
struct Node{
	int v,nxt;
}e[maxm<<1];
int tot=1;
void add(int u,int v){
	e[++tot].v=v;
	e[tot].nxt=head[u];
	head[u]=tot;
}
void tanjan(int u,int lst){
	low[u]=dfn[u]=++dfncnt;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(!dfn[v]){
			tanjan(v,i);
			low[u]=min(low[u],low[v]);
			if(low[v]>dfn[u]){
				flag[i]=1;
				flag[i^1]=1;
			}
		}
		else if((i^1)!=lst) low[u]=min(low[u],dfn[v]);
	}
}
void dfs(int u){
	color[u]=cl;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(flag[i]==1||color[v]!=0) continue;
		dfs(v);
	}
}
map<int,int> mp[maxn];
int sum1,sum2;
void build(){
	for(int i=1;i<=n;i++) A[color[i]]=max(A[color[i]],a[i]);
	for(int i=1;i<=n;i++) B[color[i]]=max(B[color[i]],b[i]);
	for(int i=1;i<=cl;i++){
		sum1+=A[i];
		sum2+=B[i];
	}
	for(int u=1;u<=n;u++){
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].v;
			int U=color[u],V=color[v];
			if(U==V||mp[U][V]==1) continue;
			f[U][V]=f[V][U]=make_pair(u,v);
			mp[U][V]=mp[V][U]=1;
			edge[U].push_back(V);
			edge[V].push_back(U);
		}
	}
}
//以上是边双缩点
int sz[maxn];//子树和 
bool cut[maxn];
void dfs1(int u,int fa){
	father[u]=fa;
	sz[u]+=A[u];
	for(int v:edge[u]){
		if(v==fa) continue;
		dfs1(v,u);
		if(sz[v]==sum1) cut[v]=true;
		sz[u]+=sz[v];
	}
	if(sz[u]==0) cut[u]=true;
}
void dfs2(int u,int fa){
	father[u]=fa;
	sz[u]+=B[u];
	for(int v:edge[u]){
		if(v==fa) continue;
		dfs2(v,u);
		if(sz[v]==sum2) cut[v]=true;
		sz[u]+=sz[v];
	}
	if(sz[u]==0) cut[u]=true;
}
int K,L;
int ans;
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>K>>L;
	for(int i=1;i<=K;i++){
		int x;
		cin>>x;
		a[x]=1;
	}
	for(int i=1;i<=L;i++){
		int x;
		cin>>x;
		b[x]=1;
	}
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	for(int i=1;i<=n;i++) if(!dfn[i]) tanjan(i,0);
	for(int i=1;i<=n;i++) if(!color[i]) ++cl,dfs(i);
	build();
	dfs1(1,0);
	memset(sz,0,sizeof(sz)); 
	dfs2(1,0);
	for(int i=1;i<=cl;i++){
		if(cut[i]==true) ans++;
	}
	cout<<ans<<'\n';
	for(int i=1;i<=cl;i++){
		if(cut[i]==true){
			cout<<f[i][father[i]].first<<' '<<f[i][father[i]].second<<'\n';
		}
	}
}
/*
9 10 3 4
2 4 5
4 9 8 3
1 2
4 1
2 3
4 2
1 5
5 6
6 7
6 8
7 9
8 7
*/ 
```


---

## 作者：aaaaaaaawsl (赞：1)

### 题意

给定一张图，其中某些点可能有 A 或 B 标记，一个点可以有两个标记，求这样的边的数量和两边的端点，满足去掉这条边后存在点，它相连的其他点中不存在 A 标记的点或 B 标记的点。

### 思路

不看 A，B 标记的话，就是求割边（图中去除一条边后有点之间不连通）。在这里简述下求割边的方法。要求掌握 tarjan。不会 tarjan 的移步 [p3387](https://www.luogu.com.cn/problem/P3387)。

给出割边的定义：在一个无向连通图中,如果删去其中一条边后,连通块的数量会增多,那么我们称这条边为桥或者是割边。

tarjan 算法可以做到给予图中的每个点一个时间戳（$ dfn $），一个可向上回溯到的点的最小时间戳（$ low $）。对于某个点，它的父亲的时间戳小于它，它的儿子的时间戳大于它，所以如果某个点的儿子的 $ low $ 值大于当前点的 $ dfn $，说明他的儿子向上回溯的最早点还是在这个点的下面，所以如果删掉当前点与儿子之间的边，就会分开当前点和他的这个儿子，也找到了一条割边。

本题的变化在要求找到的边不仅是割边，还要满足分开的点中不同时包含被 A 标记和被 B 标记的点。所以我们在找到一条割边的前提下，判断分开的两个连通块中某一个连通块不含 A 标记或 B 标记或者全部的 A 标记和 B 标记都在这个块内就行。

### 代码

```

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

namespace FastIO{
	char buf[1 << 9], buf2[1 << 18], a[18], *p1 = buf, *p2 = buf;
	void read(){}
	inline int getc(){
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 9, stdin), p1 == p2) ? EOF : *p1 ++;
	}
	template <typename T>
	inline void read(T &x){
		register int f = 0;
		x = 0;
		char ch = getc();
		while(!isdigit(ch)){
			if(ch == '-') f = 1;
			ch = getc();
		}
		while(isdigit(ch)){
			x = (x << 1) + (x << 3) + (ch ^ 48);
			ch = getc();
		}
	}
}
#define read FastIO::read

const int N = 1e5 + 10;
const int M = 1e6 + 10;

int n, m, l, k;
int A[N], B[N];

int ans;
struct node{
	int a, b;
}sl[M];

int head[N], e[M << 1], Next[M << 1], idxx;
inline void add(int a, int b){
	e[++ idxx] = b; Next[idxx] = head[a]; head[a] = idxx; 
}

int idx, dfn[N], low[N], cut[N];
void tarjan(int now, int fa){
	low[now] = dfn[now] = ++ idx;
	for(int i = head[now]; i; i = Next[i]){
		int j = e[i];
		if(!dfn[j]){
			tarjan(j, now);
			low[now] = min(low[now], low[j]);
			if(low[j] > dfn[now] && (!A[j] || !B[j] || A[j] == k || B[j] == l)) sl[++ ans].a = now, sl[ans].b = j; // 一个块内A一个没有或A都在这个块内，B同理
			A[now] += A[j]; B[now] += B[j];
		}
		else if(j != fa) low[now] = min(low[now], dfn[j]);
	}
}

int main(){
	read(n); read(m); read(k); read(l);
	for(int i = 1; i <= k; ++ i){
		register int a; read(a);
		A[a] = 1;
	}
	for(int i = 1; i <= l; ++ i){
		register int a; read(a);
		B[a] = 1;
	}
	for(int i = 1; i <= m; ++ i){
		register int a, b; read(a), read(b);
		add(a, b);
		add(b, a);
	}
	for(int i = 1; i <= n; ++ i) if(!dfn[i]) tarjan(i, i);
	printf("%d\n", ans);
	for(int i = 1; i <= ans; ++ i) printf("%d %d\n", sl[i].a, sl[i].b);
}

```

~~随便卡了个最优解~~

---

## 作者：我是逍逍 (赞：1)

通过仔细读题，我们意识到答案要求的就是一种特殊的桥（割边）。我们考虑使用 $Tarjan$ 算法解决这个问题。在搜索树中，特殊的桥满足以下性质的其中一条：
 - ~~该桥是桥。~~  
 - 该桥下的子树中缺少某种“服务节点”。  
 - 所有的服务节点都聚集在该桥下的子树中。  

依据上述的推论，我们可以轻松推出统计答案的表达式。设 $a_x, b_x$ 代表以 $x$ 节点为根的子树中 $A, B$ “服务节点”的个数，$k, l$ 代表图中 $A, B$ “服务节点”的总数，如果 $x$ 与其父节点 $father_x$ 的连边 $edge$ 为桥，且满足 $a_x = 0$ 或 $b_x = 0$ 或 $a_x = k$ 或 $b_x = l$ ，则 $edge$ 是符合条件的“关键边”。  
代码如下：  
```cpp
#include <iostream>
#include <vector>

using namespace std;
const int Max = 100005;

int n, m, k, l, a[Max], b[Max], dfn[Max], low[Max], t;
vector<int> g[Max];
vector<pair<int, int>> ans;

void tarjan(int x, int fa) { // 无向图的 Tarjan 算法
    dfn[x] = low[x] = ++t;
    for (auto y: g[x])
        if (!dfn[y]) {
            tarjan(y, x);
            low[x] = min(low[x], low[y]);
            if (low[y] > dfn[x] && (!a[y] || !b[y] || a[y] == k || b[y] == l)) // 统计答案
                ans.emplace_back(x, y);
            a[x] += a[y]; // 将子树信息累加到当前节点
            b[x] += b[y];
        } else if (y != fa)
            low[x] = min(low[x], dfn[y]);
}

int main() {
    cin >> n >> m >> k >> l;
    for (int i = 1, x; i <= k; i++) {
        cin >> x;
        a[x] = 1; // 初始化服务节点
    }
    for (int i = 1, x; i <= l; i++) {
        cin >> x;
        b[x] = 1; // 初始化服务节点
    }
    for (int i = 1, x, y; i <= m; i++) {
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    tarjan(1, 0);

    cout << ans.size() << endl;
    for (auto i: ans)
        cout << i.first << " " << i.second << endl;
    return 0;
}
```


---

## 作者：SUNCHAOYI (赞：1)

这道题和求普通的割边十分相似。最开始的思路就是将 $a$ 和 $b$ 的情况分别求解，然后再进行合并，然而这样并不行。

本题的关键通信线路和割边并不是充要条件，而是充分不必要条件。有些边虽然是割边，但该边将所有点分为两部分后每部分均有 $A$ 与 $B$，因此并不是关键通信线路。以 $A$ 为例，若某条割边是关键通信线路，则必有一部分全是 $A$，另一部分没有 $A$，$B$ 同理。而统计子树中含有 $A,B$ 的结点数也十分容易，和求子树大小类似，通过递归不断累加即可。

和求普通的割边唯一不同的代码在于判断是否为特殊边时，再加上 `!a[v] || a[v] == k || !b[v] || b[v] == l` 关于 $A,B$ 数量的判断就行了。由于有 $\texttt{Special Judge}$ 的设置，在答案累加的同时直接用一个 `pair` 记录该边相邻的两个结点就行了。

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 1e5 + 5;
const int MOD = 1e9 + 7;
inline int read ();
int n,m,k,l,cnt,times,ans;
int dfn[MAX],low[MAX],a[MAX],b[MAX];
int head[MAX * 20],to[MAX * 20],nxt[MAX * 20];
pair <int,int> edge[MAX];
void add (int u,int v); 
void tarjan (int u,int fa);
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	n = read ();m = read ();k = read ();l = read ();
	for (int i = 1;i <= k;++i) a[read ()] = 1;
	for (int i = 1;i <= l;++i) b[read ()] = 1;
	for (int i = 1;i <= m;++i)
	{
		int x = read (),y = read ();
		add (x,y);add (y,x);
	} 
	tarjan (1,0);
	printf ("%d\n",ans);
	for (int i = 1;i <= ans;++i) printf ("%d %d\n",edge[i].first,edge[i].second);
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
void add (int u,int v)
{
	to[++cnt] = v;
	nxt[cnt] = head[u];
	head[u] = cnt;
}
void tarjan (int u,int fa)
{
	dfn[u] = low[u] = ++times;
	for (int i = head[u];i;i = nxt[i])
	{
		int v = to[i];
		if (!dfn[v])
		{
			tarjan (v,u);
			low[u] = min (low[u],low[v]);
			if (low[v] > dfn[u] && (!a[v] || a[v] == k || !b[v] || b[v] == l)) edge[++ans] = make_pair (u,v);//唯一不同的地方在这里
			a[u] += a[v],b[u] += b[v];//递归累加的过程
		}
		else if (v != fa) low[u] = min (low[u],dfn[v]);
	}
}
```

---

## 作者：NightmareAlita (赞：0)

## 简要题意
给你一张图，图上有两类点 $A$ 和 $B$，现在要求你找到满足下面条件的边：删除这条边后该图变为两个块，且至少有一个块中只包含 $A$ 类点或只包含 $B$ 类点。

## 策略分析
[前置芝士：割边（桥）](https://oi-wiki.org/graph/cut/#%E5%89%B2%E8%BE%B9)

我们不难看出题目想让我们求的边是图中的割边，但并非所有的割边都满足题目的条件。如下图（图中边上的数字是编号不是边权）：

 ![](https://s1.ax1x.com/2023/08/24/pPYBlad.png)

这幅图中的割边有 $1,4,5,6,8$ 五条，而符合题目条件的只有 $1,6,8$ 这三条。仔细考虑我们在深搜的时候形成的深度优先生成树的性质，我们发现，**当一个割边满足条件当且仅当它连接的一个节点在深度优先生成树中的子树内只包含一类点**（如果后面看不懂建议反复阅读体会这句话）。求割边的时候，每找到一条割边 $(u,v)$，我们就检查一下以 $v$ 为根结点的子树内 $A$ 和 $B$ 类结点各自的数量，当其中一个个数为 $0$ 或者全满，就是要求的边，打上标记并给计数的答案加一就可以了。求数量的过程，可以在 $\operatorname{dfs}$ 的时候递归计算。

## 实现
```cpp
#include <iostream>
#include <cstdio>
using namespace std;

namespace SHAWN {
    const int N = 2e6 + 7;
    // 请注意这里一定要开二倍空间，要不然会寄
    int head[N], cnt;
    struct edge { int to, next; }edge[N];
    int n, m, a, b, tim, res;
    int dfn[N], low[N], acnt[N], bcnt[N], par[N];
    // acnt[i]表示i结点子树中A类点数量，bcnt同理
    // par用来记每个结点在dfs生成树中的父亲
    bool flag[N];

    inline void add(int u, int v) {
        edge[++cnt].next = head[u];
        edge[cnt].to = v;
        head[u] = cnt;
    }

    void Tarjan(int u, int fa) {
        low[u] = dfn[u] = ++tim;
        par[u] = fa;
        for (int i = head[u]; i; i = edge[i].next) {
            int v = edge[i].to;
            if (!dfn[v]) {
                Tarjan(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] > dfn[u]) {
                    if (!acnt[v] || !bcnt[v] || acnt[v] == a || bcnt[v] == b) {
                        // A类或B类有一个为0或全满就说明符合要求
                        flag[v] = true;
                        ++res;
                        // 后来看大家的做法这里用vector套一个pair存也非常方便
                    }
                }
                acnt[u] += acnt[v]; bcnt[u] += bcnt[v];
                // 从下向上递归统计子树情况
            }
            else if (dfn[v] < dfn[u] && fa != v) {
                low[u] = min(low[u], dfn[v]);
            }
        }
    }
    int work()
    {
        cin >> n >> m >> a >> b;
        for (int i = 1, x; i <= a; ++i) { cin >> x; acnt[x] = 1; }
        for (int i = 1, x; i <= b; ++i) { cin >> x; bcnt[x] = 1; }
        // 最开始每个点的子树就是自己
        for (int i = 1, x, y; i <= m; ++i) {
            cin >> x >> y;
            add(x, y); add(y, x);
        }
        Tarjan(1, 0);
        cout << res << '\n';
        for (int i = 1; i <= n; ++i) {
            if (flag[i]) {
                cout << i << ' ' << par[i] << '\n';
            }
        }
        return 0;
    }
}

signed int main() {
    ios :: sync_with_stdio(false);
    cin.tie(nullptr);
    return SHAWN :: work();
}
```



---

## 作者：TLE_AK (赞：0)

## 题意
在无向联通图上寻找边 $S$，能断开所有 $a$ 服务的节点或所有 $b$ 服务的节点到某个节点的路径。
## 思路
我们可以得知，边 $S$ 一定为割边，因为割边才能使整个图不连通（联通时易得每个点都会有足够的服务）

但是割边不一定满足题目中的条件，我们先将样例的图造出来（字母是对应的服务）：
![](https://cdn.luogu.com.cn/upload/image_hosting/ds99w2du.png)

我们可以将样例给出的关键边中更高的那个节点的子树服务总量算一下：
![](https://cdn.luogu.com.cn/upload/image_hosting/as517r7y.png)

我们可以发现，如果一条割边去的节点的子树 `a=0||b=0`,那么这条边一定为关键边 $S$（否则不符合题意），但如果那个节点的子树 `a=k||b=l`(下图的情况）那么这条边也一定为关键边 $S$（可以将根节点改为 $2$ 或 $3$ 来转化为前面的情况）

![](https://cdn.luogu.com.cn/upload/image_hosting/ax46ihw3.png)
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

namespace acac
{
	struct edge
	{
		int to,ne,st;
	}e[2000100];
	int H[2000100];//无向边双倍
	struct node
	{
		int dfn,tag,a,b;//dfs序，low(判断割边/点用）,ab服务
	}T[100010];
	int cnt,num;
	int A[2000100];
	void add(int a,int b)//加边
	{
		cnt++;
		e[cnt].to=b;
		e[cnt].st=a;//顺便把起点记下来好输出
		e[cnt].ne=H[a];
		H[a]=cnt;
	}
	int ans,root,n,m,k,l;
	void tarjan(int u,int f)//tarjan求割边
	{
		num++;
	
		T[u].dfn=T[u].tag=num;
		
		for(int i=H[u];i;i=e[i].ne)
		{
			
			int v=e[i].to;
			
			if(!T[v].dfn)
			{					
				tarjan(v,u);
				T[u].tag=min(T[u].tag,T[v].tag);
				T[u].a+=T[v].a;//更新ab
				T[u].b+=T[v].b;
				if(T[v].tag>T[u].dfn)//是割边
				{
					if(!T[v].a||!T[v].b||T[v].a==k||T[v].b==l)//是否满足题意
					{
						ans++; //一次不会重边
						A[i]=1;
					}
				}
			}
			else if(v!=f)
			{
				T[u].tag=min(T[v].dfn,T[u].tag);
			}
		}
		
	}
	int main()
	{

			scanf("%d%d%d%d",&n,&m,&k,&l);
			for(int i=1;i<=k;i++)
			{
				int a;
				scanf("%d",&a);
				T[a].a++;	
			}
			for(int i=1;i<=l;i++)
			{
				int a;
				scanf("%d",&a);
				T[a].b++;	
			}
			for(int i=1;i<=m;i++)
			{
				int a,b;
				scanf("%d%d",&a,&b);
				add(a,b);
				add(b,a);
			}
			tarjan(1,0);
		/*	for(int i=1;i<=cnt;i++)
			{
				if(A[i])ans++;
			}*/
			cout<<ans<<'\n';
			for(int i=1;i<=cnt;i++)//注意是cnt(边数）
			{
				if(A[i])cout<<e[i].st<<" "<<e[i].to<<'\n';
				
			}
			
				
		return 0;
	}
}

int main()
{

	acac::main();
	return 0;
}

```
最后这是[图的来源](https://csacademy.com/app/graph_editor/)。

---

## 作者：NightTide (赞：0)

## PART 1: 题目大意
给定一个 $n$ 个点 $m$ 条边的无向图和两个分别包含 $k$ 和 $l$ 个点的集合 $A$ 和 $B$，求有几条边删去之后存在点与集合 $A$ 中任何一个点 或集合 $B$ 中任何一点不联通。

## PART 2: 解题思路
答案是**割边**，这是必然的。因为不是割边的边去掉也不会对联通性产生影响。

但是割边**不一定是答案要求的边**。

所以我们可以先求出割边，再判断是否符合题意。

去掉某一条割边之后，图会被分为两个互相不联通的部分。**这条割边是答案要求的边当且仅当分成的两个子图中其中一个图的所有点形成的集合不包含集合 $A$ 或 集合 $B$**

所以我们可以边找割边边统计每个子图中属于 $A$ 和属于 $B$ 的点的数量。我们跑深搜走过的边会形成一棵树，我们简称它为 `搜索树`。设 $cnta_u,cntb_u$ 分别表示搜索树上以 $u$ 为根的子树中属于 $A$ 和属于 $B$ 的点的数量。则**对于点 $u,v$ 之间的一条割边 $E$（假设 $u$ 比 $v$ 先访问到，即在搜索树上 $u$ 是 $v$ 的父亲），若满足 $cnta_v = 0$ 或 $cntb_v = 0$ 或 $cnta_v = k$ 或 $cntb_v = l$，那么 $E$ 就是符合题意的一条边**。前面的两个式子不难理解，后面的其实也很简单。删去 $E$ 后，点 $v$ 所在的连通块其实就是以 $v$ 为根的子树，而除去以 $v$ 为根的子树剩下的就是点 $u$ 所在的连通块，如果点 $u$ 所在的连通块不包含属于集合 $A$ 或 集合 $B$ 的点，那么点 $v$ 所在的连通块就包含了所有的属于集合 $A$ 或 集合 $B$ 的点。

于是满足上式的边就是我们要求的答案了。用 **Tarjan** 算法可以很轻松地求出割边，同时顺便更新 $cnta$ 和 $cntb$ 的值并判断找到的割边是否是符合题意的。

需要学习 **Tarjan** 算法的移步 [P3388 【模板】割点（割顶）](https://www.luogu.com.cn/problem/P3388) 和 [P3387 【模板】缩点](https://www.luogu.com.cn/problem/P3387)

## PART 3: Accepted CODE
```cpp
#include<bits/stdc++.h>
#define MAXN 100010
#define MAXM 1000010
using namespace std;
struct edge{
    int pre,to;
};

edge e[MAXM << 1];
int n,m,cnt = 1,times,tot_a,tot_b,tot_e,root;
int head[MAXN],dfn[MAXN],low[MAXN],cnt_a[MAXN],cnt_b[MAXN],ans[MAXN][2];
 
void add_edge(int u,int v){
    e[++cnt].pre = head[u];
    e[cnt].to = v;
    head[u] = cnt;
}
void tarjan(int now,int fa){
    dfn[now] = low[now] = ++times;
    int son = 0;
    for(int i = head[now]; i ;i = e[i].pre){
        if(!dfn[e[i].to]){
            tarjan(e[i].to,now);
            low[now] = min(low[now],low[e[i].to]);
            son++;
            if((now == root && son > 1) || (now != root && low[e[i].to] > dfn[now])){
                if(cnt_a[e[i].to] == tot_a || cnt_b[e[i].to] == tot_b || cnt_a[e[i].to] == 0 || cnt_b[e[i].to] == 0){
                    tot_e++;
                    ans[tot_e][0] = now;
                    ans[tot_e][1] = e[i].to;
                }
            }
            cnt_a[now] += cnt_a[e[i].to];
            cnt_b[now] += cnt_b[e[i].to];
        }
        if(e[i].to != fa) low[now] = min(low[now],dfn[e[i].to]);
    }
}
int main(){
    scanf("%d%d%d%d",&n,&m,&tot_a,&tot_b);
    for(int i = 1;i <= tot_a;i++){
        int p; scanf("%d",&p);
        cnt_a[p] = 1;
    }
    for(int i = 1;i <= tot_b;i++){
        int p; scanf("%d",&p);
        cnt_b[p] = 1;
    }
    for(int i = 1;i <= m;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        add_edge(u,v); add_edge(v,u);
    }
    for(int i = 1;i <= n;i++){
        if(!dfn[i]) tarjan(i,0), root = i;
    }
    printf("%d\n",tot_e);
    for(int i = 1;i <= tot_e;i++) printf("%d %d\n",ans[i][0],ans[i][1]);
    return 0;
}
```


---

## 作者：int32 (赞：0)

## $\sf Sol$

显然题目要求的边是桥。

但是是桥也不一定是关键通信线路。

当且仅当桥联通的两个连通块中**有一个连通块中的所有点都不含 $\text{A}$ 或 $\text{B}$ 服务**，这条桥是关键通信路线。

判断条件写成代码形式就是 `!A[x]||!B[x]||A[x]==numA||B[x]==numB`。

求桥用 Tarjan 即可。

## $\sf Code$

```cpp
//WC 2022 RP++!
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
const int M=1e6+10;
int n, m, k, l;
int a[N], b[N];
vector<int> g[N];
pair<int,int> ans[M];
int cnt;
int cd;
int low[N], dfn[N];
bool check(int t){return !a[t]||!b[t]||a[t]==k||b[t]==l;}
void upd(int u, int fa){a[fa]+=a[u];b[fa]+=b[u];}
void tarjan(int u, int fa){
    dfn[u]=low[u]=++cd;
    for(auto v:g[u]){
        if(!dfn[v]){
            tarjan(v,u);
            low[u]=min(low[u],low[v]);
            if(low[v]>dfn[u])
                if(check(v))
                    ans[++cnt]=make_pair(v,u);
            upd(v,u);
        }
        if(v!=fa) low[u]=min(low[u],dfn[v]);
    }
}
signed main(){
    cin>>n>>m>>k>>l;
    for(int i=1,_;i<=k;i++){
        cin>>_;
        a[_]=1;
    }
    for(int i=1,_;i<=l;i++){
        cin>>_;
        b[_]=1;
    }
    for(int i=1,U,V;i<=m;i++){
        cin>>U>>V;
        g[U].push_back(V);
        g[V].push_back(U);
    }
    tarjan(1,0);
    cout<<cnt<<'\n';
    for(int i=1;i<=cnt;i++)
        cout<<ans[i].first<<' '<<ans[i].second<<'\n';
    return 0;
}
```

---

## 作者：nomonick (赞：0)

# P7687 [CEOI2005] Critical Network Lines

## 算法分析

题面 link : [P7687](https://www.luogu.com.cn/problem/P7687)

找到现有图上的所有的满足可以把现有图分成两个联通块，且这两个联通块中存在一个中没有任何一种服务。

很明显割边是满足条件的边的必要条件，且需要同时要求满足如下子树中不包含服务 A 或服务 B ，或包含了全部服务 A 或服务 B。

那么很明显 tarjan 求一下桥即可

## code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int SIZE = (int)1e6 + 50;

inline int read()
{
	int x = 0,f = 1ll;
	char ch = getchar();
	while (ch < '0' || ch > '9')
	{
		if (ch == '-') f = -1ll;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		x = (x << 1ll) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return f * x;
}

int n,m,k,l,num_edge,tot,ans;
int serveA[SIZE],serveB[SIZE],dfn[SIZE],low[SIZE],head[SIZE];
std::pair<int,int> lines[SIZE];
struct node
{
	int to,nxt;
};
node edge[SIZE << 1];

inline void add(int u,int v)
{
	edge[++num_edge].to = v;
	edge[num_edge].nxt = head[u];
	head[u] = num_edge;
}

inline void tarjan(int u,int fa)
{
	dfn[u] = low[u] = ++tot;
	for (int i = head[u]; i; i = edge[i].nxt)
	{
		int v = edge[i].to;
		if (!dfn[v])
		{
			tarjan(v,u);
			low[u] = min(low[u],low[v]);
			if (low[v] > dfn[u] && (!serveA[v] || !serveB[v] || serveA[v] == k || serveB[v] == l)) lines[++ans] = make_pair(u,v);
			serveA[u] += serveA[v]; serveB[u] += serveB[v];
		}
		else if (v != fa) low[u] = min(low[u],low[v]);
	}
}

signed main()
{
	n = read(); m = read(); k = read(); l = read();
	for (int i = 1; i <= k; ++i) serveA[read()] = 1;
	for (int i = 1; i <= l; ++i) serveB[read()] = 1;
	for (int i = 1; i <= m; ++i)
	{
		int u = read(),v = read();
		add(u,v); add(v,u);
	}
	tarjan(1,-1); // 保证了图联通
	printf("%lld\n",ans);
	for (int i = 1; i <= ans; ++i) printf("%lld %lld\n",lines[i].first,lines[i].second);
	return 0;
}

```



---

