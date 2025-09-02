# Fish Graph

## 题目描述

You are given a simple undirected graph with $ n $ nodes and $ m $ edges. Note that the graph is not necessarily connected. The nodes are labeled from $ 1 $ to $ n $ .

We define a graph to be a Fish Graph if it contains a simple cycle with a special node $ u $ belonging to the cycle. Apart from the edges in the cycle, the graph should have exactly $ 2 $ extra edges. Both edges should connect to node $ u $ , but they should not be connected to any other node of the cycle.

Determine if the graph contains a subgraph that is a Fish Graph, and if so, find any such subgraph.

In this problem, we define a subgraph as a graph obtained by taking any subset of the edges of the original graph.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1817B/42544cf8ec1f14b2230b1ad03e5be53025170222.png) Visualization of example 1. The red edges form one possible subgraph that is a Fish Graph.

## 说明/提示

In the first example, a possible valid subgraph contains the cycle $ 1 \rightarrow 2 \rightarrow 3 \rightarrow 4 \rightarrow 1 $ . The special node of this cycle is node $ 4 $ . The two extra edges $ 4 - 5 $ and $ 4 - 6 $ are both connected to $ 4 $ , completing the Fish Graph.

In the second example, a possible valid subgraph contains the cycle $ 1 \rightarrow 3 \rightarrow 4 \rightarrow 1 $ . The special node of this cycle is node $ 3 $ . The two extra edges $ 3 - 2 $ and $ 3 - 5 $ are both connected to $ 3 $ , completing the Fish Graph.

In the last example, it can be proven that there is no valid subgraph.

## 样例 #1

### 输入

```
3
7 8
1 2
2 3
3 4
4 1
4 5
4 6
4 2
6 7
7 7
6 7
1 2
2 3
3 4
4 1
1 3
3 5
4 4
1 3
3 4
4 1
1 2```

### 输出

```
YES
6
5 4
6 4
4 3
1 4
2 1
3 2
YES
5
5 3
2 3
3 1
4 3
1 4
NO```

# 题解

## 作者：ran_qwq (赞：13)

[CF 传送门](https://codeforces.com/problemset/problem/1817/B)

给你一个 $n$ 个点 $m$ 条边的图，求找出任意一个子图，满足以下条件，或报告无解：

- 存在且仅存在一个环。

- 环上有且仅有一个特殊的点，这个点有且仅有两条连向不在环上的点的边。

多组数据，$\sum n,\sum m\le2000$。

---

先枚举那个特殊的点 $x$。

如果一个点入度小于 $4$，就不能作为特殊点。

接着从 $x$ 出发 dfs 找环，用栈记录当前的路径。

如果第二遍搜到了 $x$，说明找到了环。

再枚举与 $x$ 相连的点 $v$，如果有至少两个点不在找的环里，就可以输出答案了。

---
特别注意：找到了环不一定满足条件，可能没有两个与 $x$ 相连且不在环内的点。这个蒟蒻在这里 WA 了三四次。

![](https://cdn.luogu.com.cn/upload/image_hosting/374oc0h5.png)

如图，如果当前 $x=1$，你找到了 $1,2,3,4$ 的环，与 $1$ 相连且不在环内的点只有 $5$ 一个。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2010,INF=0x3f3f3f3f;
int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
void Write(int x){if(x<0){putchar('-'),Write(-x);return;}if(x<10){putchar(x+'0');return;}Write(x/10),putchar(x%10+'0');}
void write(int x,char *s){Write(x),printf("%s",s);}
int n,m,id,fg,top,to[N<<1],ne[N<<1],head[N],deg[N],st[N],vis[N],col[N];
void add(int x,int y) {to[++id]=y,ne[id]=head[x],head[x]=id;}
void dfs(int u,int fa,int rt)
{
	if(fg) return;
	st[++top]=u,vis[u]=1;
	for(int i=head[u];i&&!fg;i=ne[i])
	{
		int v=to[i];
		if(v==fa) continue;
		if(v==rt&&fa!=rt)
		{
			memset(col,0,sizeof col);
			for(int i=1;i<=top;i++) col[st[i]]=1;
			int cnt=0;
			for(int j=head[rt];j&&cnt<2;j=ne[j])
				if(!col[to[j]]) cnt++;
			if(cnt<2) continue;
			puts("YES"),write(top+2,"\n");
			for(int i=top;i>1;i--) write(st[i]," "),write(st[i-1],"\n");
			write(rt," "),write(u,"\n"),cnt=0;
			for(int j=head[rt];j&&cnt<2;j=ne[j])
				if(!col[to[j]]) write(rt," "),write(to[j],"\n"),cnt++;
			fg=1;return;
		}
		if(!vis[v]) dfs(v,u,rt);
	}
	top--;
}
void solve()
{
	n=read(),m=read(),id=fg=0,memset(head,0,sizeof head),memset(deg,0,sizeof deg);
	for(int x,y;m--;) x=read(),y=read(),add(x,y),add(y,x),deg[x]++,deg[y]++;
	for(int i=1;i<=n&&!fg;i++)
	{
		if(deg[i]<4) continue;
		memset(vis,0,sizeof vis),dfs(i,0,i),top=0;
	}
	if(!fg) puts("NO");
}
signed main()
{
	int T=read();
	while(T--) solve();
}
```

---

## 作者：Alex_Wei (赞：6)

#### [CF1817B Fish Graph](https://www.luogu.com.cn/problem/CF1817B)

枚举 $u$，显然 $u$ 的度数不小于 $4$。如果我们找到了经过 $u$ 的环，考虑环上与 $u$ 相邻两点 $x, y$，加入 $u$ 的两条非 $x, y$ 出边 $a, b$。

且慢，万一 $a, b$ 也在环上怎么办？调整成环 $a \to u \to b \rightsquigarrow a$，然后加入 $(u, x)$ 和 $(u, y)$ 即可。

如何找经过 $u$ 的环？这就是套路的积累了。

从 $u$ 的所有出边开始 BFS，记录每个点是由哪个 $u$ 的邻居达到的，设为 $f_i$。BFS 时，若遇到边 $(i, j)$ 满足 $f_i \neq f_j$，则存在环 $u\to f_i\rightsquigarrow i \to j \rightsquigarrow f_j \to u$。为输出方案，记录每个点在 BFS 树上的父亲 $fr_i$。

然后我们发现，因为执行的是 BFS，所以找到的环的长度一定最小，也就是说，对于一开始的思路，$a, b$ 不可能在环上，皆大欢喜。

时间复杂度 $\mathcal{O}(nm)$。[代码](https://codeforces.com/contest/1817/submission/204385503)。

直接找一个点双里的 $u$ 即可做到 $\mathcal{O}(n)$。

---

## 作者：FFTotoro (赞：5)

本题可以使用**深度优先搜索**算法。

首先可以尝试寻找那个度数不小于 $4$ 的特殊结点，确定该结点后，用深度优先搜索找该点所在的环。

具体地，开始时选择“特殊结点”的邻接点中随便一个结点开始找环，搜索中对于每一个点，遍历除了它的前驱的所有临接点。若再次搜到起始点（即“特殊结点”），就把环上所有边记下来返回。

最后输出这些记下来的边，然后从连接特殊结点的其他边中随便选 $2$ 条出来输出即可完成要求。

如果所有的度数不小于 $4$ 的结点都不满足条件，就报告无解。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> g[2001],c,f;
bool b[2001];
int d[2001];
void dfs(int s,int e,int x){
  c.emplace_back(x),b[x]=true; // 搜索到该点，打上标记
  if(x==e){f=c; return;} // 记下环上的所有结点
  for(int i:g[x])
    if(!b[i]&&(s!=x||i!=e)){
      dfs(s,e,i); // 尝试搜索邻接点
      if(!f.empty())return;
    }
  c.pop_back(); // 该结点不可行
}
int main(){
  ios::sync_with_stdio(false);
  int t; cin>>t;
  while(t--){
    int n,m; cin>>n>>m; bool w=false;
    for(int i=1;i<=n;i++)g[i].clear(),b[i]=d[i]=0;
    for(int i=1;i<=m;i++){
      int u,v; cin>>u>>v;
      g[u].emplace_back(v);
      g[v].emplace_back(u);
      d[u]++,d[v]++; // 记录度数
    }
  for(int i=1;i<=n;i++)
    if(d[i]>=4&&!w)
      for(int j:g[i]){ // 随便选择它的一个邻接点并开始找环
        c.clear(),f.clear();
        memset(b,0,sizeof(b)); // 记得清空标记数组
        if(dfs(i,j,i);!f.empty()){
          vector<pair<int,int> > r;
          for(int i=0;i<f.size();i++)
            r.emplace_back(f[i],f[(i+1)%f.size()]);
          int c=0;
          for(int j:g[i]){
            if(c>1)break;
            if(find(f.begin(),f.end(),j)==f.end())
              c++,r.emplace_back(i,j);
          } // 从其他结点中选取 2 个
          if(c<2)continue;
          cout<<"Yes\n"<<r.size()<<'\n';
          for(auto [u,v]:r)cout<<u<<' '<<v<<'\n';
          w=true; break;
        }
      }
    if(!w)cout<<"No\n"; // 无解情况
  }
  return 0;
}
```

---

## 作者：LIUGUANG_noi (赞：3)

### [传送门](https://www.luogu.com.cn/problem/CF1817B)

A 掉这题分三步：

**1.找到关键节点**，此处指度数大于等于 $4$ 的节点，由于它的特殊性质，我们可以把它作为切入点。

**2.找到经过关键节点的环**，这也是整个代码中的关键。

在这里我选择用 BFS 判环，步骤如下：

首先将与关键节点相连的节点入队，每个点打上不同的标记。

之后 BFS 的过程中，新节点都要从递推到它的节点继承标记。

若找到一个将要递推的新节点已经被标记，同时此标记不同于递推到它的节点的标记，那么就找到了一个环。

**3.答案统计**
在此通过模拟链表的方式记录 BFS 时的路径。

若找到一个环，就在逐步回退至关键节点的途中记录经过的每一条边。

还要记得加上两个“小鱼尾巴”边。

此题结。

附：**我的代码**

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){//快读
	int x=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
int t,n,m,u[200005],v[200005],d[200005];//读入部分，u、v记录一条边，d记录度数
struct E{
	int to,nxt;
}e[400005];
int h[200005],cnt,f,vis[200005];//vis就是标记数组
void add(int x,int y){
	e[++cnt].to=y;
	e[cnt].nxt=h[x];
	h[x]=cnt;
}

struct G{
	int u,v;
}g[200005];//存答案
int cnt2,pre[200005];//pre模拟链表用于统计答案
void doi(int x,int u,int v){//统计答案函数
	g[++cnt2]=G{u,v};
	while(pre[u]!=x){
		g[++cnt2]=G{pre[u],u};
		u=pre[u];
	}
	while(pre[v]!=x){
		g[++cnt2]=G{pre[v],v};
		v=pre[v];
	}
	int num=0;
	g[++cnt2]=G{x,u};
	g[++cnt2]=G{x,v};
	for(int i=h[x];i;i=e[i].nxt){
		int y=e[i].to;
		if(y==u||y==v)continue;
		
		g[++cnt2]=G{x,y};
		num++;
		if(num==2)break; 
	}
	return;
}
void bfs(int x){
	queue<pair<int,int> >q;
	memset(vis,0,sizeof vis);
	vis[x]=1;
	for(int i=h[x];i;i=e[i].nxt){//将与关键节点相连的节点入队并标记
		int y=e[i].to;
		q.push(make_pair(y,y));
		pre[y]=x;
		vis[y]=y;
	}
	while(!q.empty()){
		int p=q.front().first,l=q.front().second;//l为标记
		q.pop();
		for(int i=h[p];i;i=e[i].nxt){
			int y=e[i].to;
			if(y==x||y==pre[p])continue;
			if(vis[y]&&vis[y]!=vis[p]){
				doi(x,p,y);
				f=1;
				return;
			}	
			if(vis[y])continue;
			vis[y]=l;
			pre[y]=p;
			q.push(make_pair(y,l));
		}
	}
}
void qk(){//多测清空
	memset(d,0,sizeof d);
	memset(e,0,sizeof e);
	memset(h,0,sizeof h);
	cnt=0;
	cnt2=0;
	memset(g,0,sizeof g);
	memset(pre,0,sizeof pre);
}
void solve(){
	n=read();m=read();

	for(int i=1;i<=m;i++){
		u[i]=read();v[i]=read();
		add(u[i],v[i]);add(v[i],u[i]);
		d[u[i]]++;d[v[i]]++;
	}
	f=0;
	for(int i=1;i<=n;i++){
		if(d[i]>=4&&!f){
			bfs(i);
		}
		if(f){//答案输出
			puts("Yes");
			cout<<cnt2<<endl;
			for(int i=1;i<=cnt2;i++){
				cout<<g[i].u<<' '<<g[i].v<<endl;
			}
			return;
		}
	}
	if(!f)puts("No");
	return;
}
signed main(){
	t=read();
	while(t--){
		qk();
		solve();
	}
	return 0;
}

```



---

## 作者：movefast (赞：2)

我是乐子。

赛时没看到 $\sum m \le 2000$ ，傻傻地提供一个 $O(n+m)$ 做法。

首先看到可能存在多个环，我们先把整张图的边双求出来。

然后我们思考什么时候一定有解。

首先假设这个特殊点为 $u$ ，肯定要 $d_u \ge 4$（ $d$ 是度数）。

然后考虑与 $u$ 相连的点 $v$ ，如果存在 $v$ 与 $u$ 在同一个边双内，那么一定有解，否则无解。

因为边双是能从 $u$ 出发，不经过重边回到 $u$ 的，也就满足了他所说的一个环，再另外随意添加两条边。

但这样可能有问题，因为忽略了还有正好 $2$ 条边，每一条边连向一个**环外**的结点 。

那我们只需要从 $v$ 出发，走到任意一个与 $u$ 相连的点时立刻返回，这样其他与 $u$ 相连的点就都在环外了。

****

代码很丑很长，如果你要的话就给你吧。

```cpp
#include <bits/stdc++.h>
typedef long long ll;
typedef double db;
using namespace std;

const int N=2005;
int T,n,m;
int du[N],bz[N],p[N];
int st[N],nx[N*2],to[N*2],tt;

void add(int u,int v)
{
	to[++tt]=v,nx[tt]=st[u],st[u]=tt;
}

int tarq[N];
int tarcnt,dfn[N],low[N];
void tar(int u,int fab)
{
	tarq[++tarq[0]]=u;
	low[u]=dfn[u]=++tarcnt;
	for(int i=st[u];i;i=nx[i])
	{
		if(i==fab) continue;
		int v=to[i];
		if(!dfn[v]) tar(v,i^1);
		low[u]=min(low[u],low[v]);
	}
	if(low[u]==dfn[u])
	{
		do{
			int x=tarq[tarq[0]];
			bz[x]=u;
		}while(tarq[tarq[0]--]!=u);
	}
}
int bz2[N];
int ansq[N*2][2],ansqlen,bzu[N],kkp;
bool dg2(int u,int p1,int s1)
{
	bz2[u]=1;
	for(int i=st[u];i;i=nx[i])
	{
		int v=to[i];
		if(bz2[v]) continue;
		if(bz[v]!=bz[p1]) continue;
		if(v==s1) continue;
		
		if(bzu[v]){
			ansq[++ansqlen][0]=u;
			ansq[ansqlen][1]=v;
			kkp=v;
			return 1;
		}
		if(dg2(v,p1,s1)) 
		{
			ansq[++ansqlen][0]=u;
			ansq[ansqlen][1]=v;
			return 1;
		}
	}
	return 0;
}

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		
		for(int i=1;i<=tt;i++) nx[i]=0;
		tt=1;
		tarcnt=0;
		for(int i=1;i<=n;i++) bz[i]=st[i]=du[i]=low[i]=dfn[i]=0;
		
		for(int i=1;i<=m;i++)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			add(u,v);
			add(v,u);
			du[u]++,du[v]++;
		}
		
		for(int i=1;i<=n;i++)
			if(!dfn[i]) tar(i,0);
		
		int flag=0;
		for(int i=1;i<=n;i++)
		{
			if(du[i]>=4)
			{
				p[0]=0;
				int y=-1;
				for(int j=st[i];j;j=nx[j])
				{
					int v=to[j];
					p[++p[0]]=v;
					if(bz[v]==bz[i]) y=v;
				}
				if(y==-1) continue;
				
				for(int j=1;j<=n;j++) bzu[j]=bz2[j]=0;
				for(int j=st[i];j;j=nx[j])
				{
					int v=to[j];
					bzu[v]=1;
				}
				
				kkp=-1;
				ansqlen=0;
				dg2(y,y,i);
				
				ansq[++ansqlen][0]=i;
				ansq[ansqlen][1]=y;
				ansq[++ansqlen][0]=i;
				ansq[ansqlen][1]=kkp;
				
				int cnt=0;
				for(int j=1;j<=p[0];j++)
				{
					if(p[j]!=kkp && p[j]!=y)
					{
						ansq[++ansqlen][0]=i;
						ansq[ansqlen][1]=p[j];
						cnt++;
						if(cnt==2) break;
					}
				}
				
				puts("YES");
				printf("%d\n",ansqlen);
				for(int g=1;g<=ansqlen;g++)
					printf("%d %d\n",ansq[g][0],ansq[g][1]);
				flag=1;
				goto here;
			}
		}
		here:
		if(!flag) puts("NO");
	}
	return 0;
}
```

赛时因为脑抽，觉得一个边双内都是有边的，打了个对拍啥也没拍出来，结束后最后看 cf 的错误详情才发现，浪费我 2h 。

---

## 作者：ZXZ_ (赞：2)

# 题解：CF1817B Fish Graph

## 题意：
给出一个无向图，求出其的任意一个子图满足存在有且只有一个环，且环上存在有且只有一个特殊点满足与两个不再环内的点相连。

## 做法：

注意到 $1 \leq n,m \leq2000$ ，我们可以考虑一个 $O(nm)$ 的暴力算法。

先枚举环上的特殊点是哪个，要满足其度数要大于等于四，然后再从这个点出发去找环。也就是在深搜的过程中，如果发现回到了初始点那么就找到了一个环。

找到后要记得再判断一次特殊点还满不满足要求，找到就输出然后退出即可。如果程序超时可以尝试在一次找环的过程中，之前找过的点就标记起来不再遍历。枚举另一个特殊点时将标记清空即可。

## 代码
```cpp
#include<bits/stdc++.h>
#define N 2005
using namespace std;
int n,m,T,tot,head[N],in[N],sta[N],top;
struct node{int nxt,to;}e[N<<1];
template<typename type>
inline void read(type &x){
    x=0;static bool flag(0);char ch=getchar();
    while(!isdigit(ch)) flag=ch=='-',ch=getchar();
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    flag?x=-x:0;
}
template<typename type>
inline void write(type x,bool mode=1){
    x<0?x=-x,putchar('-'):0;static short Stack[50],top(0);
    do Stack[++top]=x%10,x/=10; while(x);
    while(top) putchar(Stack[top--]|48);
    mode?putchar('\n'):putchar(' ');
}
inline void add(int u,int v){
    e[++tot].nxt=head[u];
    e[tot].to=v;
    head[u]=tot;
}
bool flag=false,vis[N],vis1[N];
void DFS(int x,int fa){
    vis[x]=true;
    vis1[x]=true;
    if(flag)return;
    for(int i=head[x];i&&!flag;i=e[i].nxt)
        if(e[i].to!=fa){
            if(e[i].to==sta[1]){
                int cnt=0,w1,w2;
                for(int j=head[sta[1]];j;j=e[j].nxt)
                    if(!vis[e[j].to]){
                        cnt++;
                        if(cnt==1)w1=e[j].to;
                        else if(cnt==2){
                            w2=e[j].to;
                            break;
                        }
                    }
                if(cnt==2){
                    puts("YES");
                    write(top+2);write(sta[1],0);write(sta[top]);
                    for(int j=1;j<top;j++)
                        write(sta[j],0),write(sta[j+1]);
                    write(sta[1],0),write(w1);
                    write(sta[1],0),write(w2);
                    flag=1;
                    return;
                }
            }else if(!vis1[e[i].to]){
                sta[++top]=e[i].to;
                DFS(e[i].to,x);
                top--;
            }
        }
    vis[x]=false;
}
int main(){
    read(T);
    while(T--){
        read(n),read(m);
        tot=0,flag=0;
        memset(head,0,sizeof head);
        memset(in,0,sizeof in);
        memset(vis,0,sizeof vis);
        for(int i=1;i<=m;i++){
            int u,v;
            read(u),read(v);
            in[u]++,in[v]++;
            add(u,v);
            add(v,u);
        }
        for(int i=1;i<=n;i++)
            if(in[i]>=4){
                top=0;
                sta[++top]=i;
                for(int j=1;j<=n;j++)
                    vis[j]=vis1[j]=0;
                DFS(i,0);
            }
        if(!flag)puts("NO");
    }
}
```

---

## 作者：Red_river (赞：2)

### 题目大意
定义了一个鱼图，求是否存在并输出环和两点的边。
### 题意分析
直接暴力，但是需要加一点点小优化，具体如下：
1. 环的检测：我们首先需要在图中找到一个环，如果遇到了一个已经访问过的节点，**并且该节点不是**当前路径的父节点，就形成了一个环。
2. 检查环的特殊节点：鱼图的要求是环中的某个节点，除了参与环的连接，还必须有**两条指向环外**的边。
3. 遍历所有可能的环：环的起始节点可能是任意的，因此我们需要遍历所有节点，尝试从每个节点出发找到一个环，并判断该环是否符合鱼图的要求。同时由于是环，所以这个点必须有**被四个点连接**。
具体可参考代码及注释理解。
### CODE
```cpp
#include<bits/stdc++.h>
#define wk(x) write(x),putchar(' ')
#define wh(x) write(x),putchar('\n')
#define ll long long
#define ull unsigned long long
#define ri register int
#define INF 2147483647
#define mod 998244353
#define N 50005
#define NO printf("No\n")
#define YES printf("Yes\n")

using namespace std;
int n,m,k,jk,ans,sum,num,cnt,tot;
int head[N],dis[N],vis[N],wis[N],f[N];

void read(int &x)
{
	x=0;int ff=1;char ty;
	ty=getchar();
	while(!(ty>='0'&&ty<='9'))
	{
		if(ty=='-') ff=-1;
		ty=getchar();
	}
	while(ty>='0'&&ty<='9')
		x=(x<<3)+(x<<1)+ty-'0',ty=getchar();
	x*=ff;return;
}

void write(int x){
	if(x==0){
		putchar('0');
		return;
	}
	if(x<0){
		x=-x;
		putchar('-');
	}
	char asd[201];int ip=0;
	while(x) asd[++ip]=x%10+'0',x/=10;
	for(int i=ip;i>=1;i--) putchar(asd[i]);
	return;
}

struct lenovo{
	int to,nxt,val;
}v[N*2];

void add(int x,int y)
{
	v[++cnt].to=y;
	v[cnt].nxt=head[x];
	head[x]=cnt;
}

void dfs(int x,int y,int z){
	if(tot) return;f[++num]=x;vis[x]=1;//加入堆中。
	for(int i=head[x];i&&!tot;i=v[i].nxt){
		int u=v[i].to;if(u==y) continue;
		if(u==z&&y!=z){//到达原点。
			memset(dis,0,sizeof dis);int pop=0;//初始化。
			for(int j=1;j<=num;j++) dis[f[j]]=1;//标记堆中的元素。
			for(int j=head[z];j&&pop<2;j=v[j].nxt)
				if(!dis[v[j].to]) pop++;//取另外两点。
			if(pop<2) continue;//不符合条件就退出。
			YES;wh(num+2);//输出答案。
			for(int j=num;j>1;j--) wk(f[j]),wh(f[j-1]);
			wk(z),wh(x);pop=0;
			for(int j=head[z];j&&pop<2;j=v[j].nxt)
				if(!dis[v[j].to]) wk(z),wh(v[j].to),pop++;
			tot=1;return;
		}if(!vis[u]) dfs(u,x,z);//继续遍历。
	}num--;//弹出堆顶。
}

signed main()
{
	read(jk);while(jk--){
		read(n),read(m);int x,y;cnt=0;
		memset(head,0,sizeof head);//记得初始化。
		memset(wis,0,sizeof wis);
		for(int i=1;i<=m;i++){
			read(x),read(y);
			add(x,y),add(y,x);
			wis[x]++,wis[y]++;//将出度和入度加一。
		}tot=0;
		for(int i=1;i<=n&&!tot;i++){
			if(wis[i]<4) continue;//一定不可能是。
			memset(vis,0,sizeof vis);
			dfs(i,0,i);num=0;//暴力。
		}
		if(!tot) NO;//无解的情况。
	}
	return 0;
}
```

---

## 作者：huhaoming2011 (赞：2)

## Fish Graph 题解

### 题目大意

给出一个无向图，寻找有无子图符合由一个环加两条连在环上同一点的边组成。

### 正解

看到数据有 $n,m \leq 2000$。

大胆猜测时间复杂度为 $O(n^2)$。

首先想到枚举那个环中多两条边的点（此处有优化：若点所连的边数小于 $4$ 可以跳过），然后跑图找环，用栈记录路径。找到环后，对枚举的点进行判断：是否还有两个相连的点不在环内，然后统计答案。

建议跑图不要重复，即标记不标回 $0$，否则会时间超限。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e3+100;
int n,m,bz[MAXN],hd[MAXN],cnt,ans[MAXN],lena,p[30];
struct Edge {
	int nxt,to;
} G[MAXN<<1];
struct Stack {
	int len,z[MAXN];
	void init()
	{
		len=0;
		return ;
	}
	int top()
	{
		return z[len];
	}
	void pop()
	{
		--len;
		return ;
	}
	void push(int x)
	{
		z[++len]=x;
		return ;
	}
	int size()
	{
		return len;
	}
} st;
void add(int u,int v)
{
	G[++cnt]={hd[u],v};
	hd[u]=cnt;
}
bitset<MAXN> vis,vis2;
void dfs(int x,int ff,int fa)
{
	if(lena)
		return ;
	vis[x]=1;
	st.push(x);
	for(int i=hd[x];i;i=G[i].nxt)
	{
		int v=G[i].to;
		if(lena)
			return ;
		if(lena or v==fa)
			continue ;
		if(v==ff)
		{
			for(int i=1;i<=n;i++)
				vis2[i]=0;
			for(int i=1;i<=st.len;i++)
			{
				vis2[st.z[i]]=1;
			}
			int sum=0;
			for(int j=hd[ff];j;j=G[j].nxt)
			{
				int g=G[j].to;
				if(!vis2[g])
				{
					++sum;
					p[sum]=g;
				}
				if(sum>=2)
					break;
			}
			if(sum<2)
				continue ;
			lena=0;
			ans[++lena]=v;
			while(st.size())
			{
				ans[++lena]=st.top();
				st.pop();
			}
			return ;
		}
		if(vis[v])
			continue ;
		dfs(v,ff,x);
	}
    st.pop();
}
signed main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		cnt=lena=0;
		scanf("%d %d",&n,&m);
		for(int i=1;i<=n;i++)
			hd[i]=bz[i]=0;
		for(int i=1;i<=m;i++)
			G[i]={0,0};
		for(int i=1;i<=m;i++)
		{
			int u,v;
			scanf("%d %d",&u,&v);
			add(u,v),add(v,u);
			++bz[u],++bz[v];
		}
		int d=0;
		for(int i=1;i<=n;i++)
		{
			if(bz[i]<4)
				continue ;
			for(int j=1;j<=n;j++)
				vis[j]=0;
			st.init();
			dfs(i,i,0);
			d=i;
			if(lena)
				break;
		}
		if(!lena)
			puts("NO");
		else
		{
			puts("YES");
			printf("%d\n",lena+1);
			for(int i=2;i<=lena;i++)
				printf("%d %d\n",ans[i],ans[i-1]);
			printf("%d %d\n%d %d\n",d,p[1],d,p[2]);
		}
	}
	return 0;
}
```

---

## 作者：luogu_gza (赞：2)

本题解复杂度 $O(nm)$。

发现，这是一个“暴力”！

考虑枚举度数大于 $4$ 的点，然后钦定其为特殊点。

接着，直接找特殊点在内的某一个环，然后考虑寻找两条不在环内的边。

然后就……做完了……

还是有一些细节的，这里给一组良心数据。

```
1
7 8
7 4
4 6
6 5
5 7
7 1
7 2
2 3
4 3
```

1. 提前 `return` 的时候一定要记得把变量顺便回溯了。

2. 一定一定要考虑特殊点不在你找的环里面的情况。

[$\color{blue}\texttt{AC\ record}$](https://codeforces.com/contest/1817/submission/207050918)

$\color{green}\texttt{ACcode:}$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define MT int TTT=R;while(TTT--)
#define pc putchar
#define R read()
#define fo(i,a,b) for(register int i=a;i<=b;i++)
#define rep(i,a,b) for(register int i=a;i>=b;i--)
#define m1(a,b) memset(a,b,sizeof a)
int read()
{
    int x=0;
    char ch=getchar();
    bool f=0;
    while(!isdigit(ch)){if(ch=='-') f=1;ch=getchar();}
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    if(f) x=-x;
    return x;                                       
}
template<typename T> inline void write(T x)
{
    if(x<0)
    {
        pc('-');
        x=-x;
    }
    if(x>9) write(x/10);
    pc(x%10+'0');
}
const int N=2010,M=4010;
int n,m;
int h[N],e[M],ne[M],idx;
int deg[N];
bool st[N],has_ans;
int top,stk[N],St;
vector<pair<int,int> > v;
void add(int a,int b)
{
    e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}
void dfs(int u,int fa)
{
    stk[++top]=u,st[u]=1;//加入栈，方便找环
    for(int i=h[u];~i;i=ne[i])
    {
        int j=e[i];
        if(j!=fa)
        {
            if(st[j])//如果接下来搜索的点在环内
            {
                if(j==St)//如果枚举的特殊点在环内（重点）
                {
                    fo(i,1,top) v.push_back({stk[i],stk[i==1?top:i-1]});//找到一种可行解，先把环放进去
                    int cnt=0;
                    for(int I=h[St];~I;I=ne[I])
                    {
                        int J=e[I];
                        if(!st[J])
                        {
                            cnt++;
                            v.push_back({St,J});
                        }
                        if(cnt==2) break;
                    }//放两条边
                    if(cnt==2) has_ans=1;//有答案了！
                    else v.clear();//边不够，回溯。
                    top--,st[u]=0;//记得弹出栈！
                    return;
                }
                top--,st[u]=0;//记得弹出栈！
                return;
            }
            dfs(j,u);
            if(has_ans)
            {
                top--,st[u]=0;//记得弹出栈！
                return;
            }
        }
    }
    st[u]=0,top--;//记得弹出栈！
}
signed main(){
    MT
    {
        m1(h,-1),m1(e,0),m1(ne,0),idx=0;
        m1(deg,0),m1(st,0),top=0;
        v.clear();//多测不清空，爆零两行泪
        n=R,m=R;
        fo(i,1,m)
        {
            int u=R,v=R;
            add(v,u),add(u,v);
            deg[u]++,deg[v]++;//记录deg
        }
        has_ans=0;
        for(St=1;St<=n;St++) if(deg[St]>=4)//寻找一个deg>=4的点
        {
            m1(st,0),top=0;//数组不清空，爆零两行泪
            dfs(St,-1);//进行dfs
            if(has_ans) break;//如果有答案了直接干掉，否则会降低效率
        }
        if(!has_ans) puts("NO");
        else
        {
            puts("YES");
            write(v.size()),puts("");
            for(auto i:v) write(i.first),pc(' '),write(i.second),puts("");
        }//输出一下解
    }
}
```

---

### 后话

听说有 $O(n+m)$ 的做法，我去学习了一下。

似乎是考虑找最小环，这一点可以通过广搜来解决，过程中可以直接放弃掉很多本来需要枚举的点。

我还有一个想法，就是考虑删去度数为 $1$ 的点，然后在删去度数为 $1$ 的点，类似于“拓扑排序”。

然后在剩下的点上找环，那么需要枚举的点的数量大大减小。

---

## 作者：honglan0301 (赞：2)

## 题目分析

$O(n+m)$ 做法，数据范围为什么没开大点。

发现题意就是说让你找一个环，满足环上存在一个点 $u$，向环外连了至少两条边。于是贪心地考虑，我们只需要试图让这个点向环内的连边尽量少。容易发现至少要有两条，而只要找出一个极小环就能取到两条，于是边双缩点之后判断是否有在环上且度数 $\geq 4$ 的点即可，从该点开始找一个极小环再任意找两条边便满足题目要求。

## 代码

赛时代码很丑。

```cpp
/*
  author: PEKKA_l  
  Sexy_goodier _ xiaoqing
 */
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define int long long

int t,n,m,u,v,dfn[2005],low[2005],vis[2005],stk[2005],cntd,top,flag[2005],cnts,sz[2005];
vector <int> e[2005];

void dfs(int x,int fat)
{
	dfn[x]=low[x]=++cntd; stk[++top]=x; vis[x]=1;
	for(auto i:e[x])
	{
		if(i==fat) continue;
		if(!dfn[i]) {dfs(i,x); low[x]=min(low[x],low[i]);}
		else if(vis[i]) {low[x]=min(low[x],dfn[i]);}
	}
	if(dfn[x]==low[x])
	{
		cnts++;
		while(1)
		{
			int nw=stk[top--]; flag[nw]=cnts; sz[cnts]++; vis[nw]=0; if(nw==x) break;
		}
	}
}
void tarjan()
{
	for(int i=1;i<=n;i++) if(!dfn[i]) dfs(i,i);
}

int zt[2005],hn[2005],cnth,us[2005],ss[2005];
bool dfs2(int x,int bf,int to)
{
	if(x==to&&zt[x]==1) return 1;
	if(zt[x]) return 0; zt[x]=1;
	for(auto i:e[x])
	{
		if(i==bf) continue;
		if(dfs2(i,x,to))
		{
			hn[++cnth]=i; return 1;
		}
	}
	return 0;
}
void solve(int x)
{
	for(int i=1;i<=n;i++) zt[i]=hn[i]=us[i]=ss[i]=0; cnth=0;
	dfs2(x,x,x); for(auto i:e[x]) ss[i]=1;
	int num=0;
	for(int i=3;i<=cnth;i++)
	{
		if(ss[hn[i]]) {num=i; break;}
	}
	for(int i=2;i<=num;i++) us[hn[i]]=1;
	cout<<num+2<<endl; hn[num+1]=x;
	for(int i=2;i<=num+1;i++) cout<<hn[i-1]<<" "<<hn[i]<<endl;
	int cntt=0;
	for(auto i:e[x])
	{
		if(!us[i]) {cntt++; cout<<x<<" "<<i<<endl;}
		if(cntt==2) break;
	}
}

signed main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>m; for(int i=1;i<=n;i++) e[i].clear(); cntd=cnts=top=0;
		for(int i=1;i<=n;i++) dfn[i]=low[i]=vis[i]=stk[i]=flag[i]=sz[i]=0;
		for(int i=1;i<=m;i++) {cin>>u>>v; e[u].pb(v); e[v].pb(u);}
		tarjan(); bool ok=0;
		for(int i=1;i<=n;i++)
		{
			if(e[i].size()>=4&&sz[flag[i]]>=3)
			{
				cout<<"YES"<<endl; ok=1; solve(i);
				break;
			}
		}
		if(!ok) cout<<"NO"<<endl;
	}
}
```


---

## 作者：ZLCT (赞：0)

# CF1817B Fish Graph
## 题目翻译
给定一个无向图，求是否存在一个环满足环上某一个点有两条不与环上节点相连的边，如果有还要输出方案。
## solution
首先观察条件不难把目标子图转化为一个环加两条边，这两条边必须连在环上一点。那么我们完全可以枚举这个点。\
接下来考虑什么时候合法。首先由于连向环和两个点需要 $4$ 条边，所以度数小于 $4$ 的点我们不需要考虑。\
而对于其他点 $u$ 我们可以暴力 dfs 出每个经过 $u$ 的简单环，假设 $u$ 与环外节点的连边大于等于两条，则一定可以找到一个满足条件的子图。\
如何输出呢？\
对于与环外节点的连边，随便输出两条即可，而环内节点由于 dfs 是有序的，所以可以维护一个栈表示当前路径内的节点，按照栈的顺序输出即可。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2666;
int n,m,S;
bool flag,vis[N],used[N];
vector<int>G[N];
stack<int>stk;
void clear(){
    for(int i=1;i<=n;++i){
        G[i].clear();
    }
    memset(used,0,sizeof(bool)*(n+5));
    flag=0;
}
void dfs(int u,int from){
    if(vis[u])return;
    if(flag)return;
    vis[u]=1;
    stk.push(u);
    used[u]=1;
    for(int v:G[u]){
        if(v==from)continue;
        if(v==S){
            int cnt=0;
            for(int to:G[S]){
                if(!used[to])cnt++;
            }
            if(cnt<2)continue;
            cnt=0;
            cout<<"YES\n";
            cout<<stk.size()+2<<'\n';
            for(int to:G[S]){
                if(!used[to]){
                    cout<<S<<' '<<to<<'\n';
                    cnt++;
                }
                if(cnt>=2)break;
            }
            cout<<S<<' '<<u<<'\n';
            int st=u;stk.pop();
            while(!stk.empty()){
                cout<<st<<' '<<stk.top()<<'\n';
                st=stk.top();stk.pop();
            }
            flag=1;
            return;
        }
        dfs(v,u);
        if(flag)return;
    }
    stk.pop();
    used[u]=0;
    return;
}
void solve(){
    clear();
    cin>>n>>m;
    for(int i=1;i<=m;++i){
        int u,v;cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for(int i=1;i<=n;++i){
        if(G[i].size()<4)continue;
        S=i;
        while(!stk.empty())stk.pop();
        memset(vis,0,sizeof(vis));
        dfs(S,S);
        if(flag)return;
    }
    if(!flag){
        cout<<"NO\n";
    }
    return;
}
signed main(){
    int T;cin>>T;
    while(T--)solve();
    return 0;
}
```

---

## 作者：Walrus (赞：0)

首先「鱼图」的定义是某个**环上的点**又连接了**另外两个不在环上的点**构成的图。

这里给出一个示例：
![](https://cdn.luogu.com.cn/upload/image_hosting/lh4o4crf.png)

看这幅图可以观察到点 3 处于环上并且连接了另外两个不在环上的点 5 和 6，所以这是一张「鱼图」。

发现点 3 比较特殊，一种想法是枚举题目中所说的「特殊点」，先找环，然后判断与这个「特殊点」相连的边（边上的另一端）是否有大于等于 2 个点不在此环上，若是则此点作为「特殊点」可构成鱼图。

由于输出边的时候要遍历整个环，而在搜索时记录环的方法就是用栈，又因为 STL 的栈遍历又很麻烦，所以推荐手写栈。

还有一个小优化，在遍历「特殊点」时，看到样例图，可以发现若此点作为「特殊点」可构成「鱼图」，则整张「鱼图」至少有 4 个点与此「特殊点」相连，所以入度小于 4 的点肯定不会作为「特殊点」。

```cpp
void dfs(int x, int fa, int rt) {
	if(flag) return;//理所应当的优化
	st[++top] = x; vis[x] = 1;
	for(auto y : e[x]) {
		if(y == fa) continue;
		if(y == rt && fa != rt) {
			rep(i, 1, n) col[i] = 0;
			rep(i, 1, top) col[st[i]] = 1;
			int cnt = 0;
			for(auto f : e[rt]) if(!col[f]) ++cnt;
			if(cnt < 2 || flag) continue;
			cout << "YES\n" << top + 2 << '\n';
			pre(i, top, 2) cout << st[i] << ' ' << st[i - 1] << '\n';
			cout << rt << ' ' << x << '\n';
			cnt = 0;
			for(auto f : e[rt]) if(!col[f] && cnt < 2) cout << rt << ' ' << f << '\n', ++cnt;
			flag = 1;
			return;
		}
		if(!vis[y] && !flag) dfs(y, x, rt);
	}
	--top; 
}
```

---

## 作者：yshpdyt (赞：0)

## 题意
给定一张无向图，求任意一个满足以下条件的子图：
- 只包含一个环。
- 环上只存在一个**特殊点**，在与其相连的四个点中，两个点不在环上，两个点在环上。


就像一条鱼一样（所以称该子图为鱼图）：
![](https://cdn.luogu.com.cn/upload/image_hosting/74bojl1f.png)
通俗的讲，就是找到一个环，再在这个环上找到一个符合条件的特殊点。

## Sol

考虑到一个图有很多环，一个环上的点可能有很多，找到环后再枚举所有环上点进行判断，会进行大量冗余计算。于是先找到特殊点，再找包含该点的环。

考虑如何找到特殊点。比较显而易见的是，根据特殊点的要求，一个点的度数小于 4 是不可能符合题意的（特殊点在鱼图中度数为 4 ），反之**度数大于等于 4 的点可以作为特殊点**。

流程大概是这样的：
1. 找到符合条件的点，并以这个点作为起点跑 dfs 找环。
2. 搜索同时用栈记录路径。
3. 如果找到环，判断特殊点是否有两个相连点不在环上。
4. 找到鱼图后，鱼图点数就是 $\text{栈的大小} +2$，输出时取两个相邻的在一起输出，再补上特殊点的两个不在环内的相邻点。

这样直接写过不去。


## 玄学优化
找到一个方案后，可以直接结束算法。

于是对预备特殊点的遍历顺序以及题目数据会影响运行时间，尝试找到一种合适的遍历方式。

进行试验得出结论:
- 正序枚举所有点，过去 $24$ 个点。
- 倒序枚举所有点，过去 $17$ 个点。
- 加边时符合条件的入栈后枚举栈，过去 $14$ 个点。

或者还有其他遍历方法，这里提供一种跑到飞快的。

在找到环后要判断特殊点是否有两个相连点是否在环上，则此时度数大的点比度数小的点更有可能符合条件（例如 $15$ 个点选 $2$ 个 和 $5$ 个点选 $2$ 个相比前者更可能满足条件）。

于是，我们可以从度数大的点开始枚举，这里用了优先队列，跑了
$\text{15ms}$，算上并列的情况可以排到第三，~~遥遥领先（虽然一车并列的~~。

有解的话大概搜索两三次就行了。

## Code
~~夹带私货（逃。~~

```
#include<bits/stdc++.h>
#define ll int
#define N 4005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
namespace MYINPUT{
    const int S=(1<<20)+5;char B[S],*H=B,*T=B;
    inline char gc(){if(H==T) T=(H=B)+fread(B,1,S,stdin);return H==T?EOF:*H++;}
    inline ll fr(){ll x=0;bool fh=0;char ch=gc();while(ch<'0'||ch>'9'){if(ch=='-') fh=1;ch=gc();}while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=gc();}return fh?-x:x;}
}using MYINPUT::fr;//super cxk fast read

bool bel[N];
vector<ll> v[N];
ll n,m,d[N];
ll q[N],top;

bool dfs(ll x,ll fa,ll genshin){//根shin
    q[++top]=x;//顺带统计路径
    bel[x]=1;//并且标记在环上
    for(auto y:v[x]){
        if(y!=fa&&y==genshin){//下一个点是特殊点，找到环了
            ll cnt=0,a=0,b=0;
            for(auto i:v[genshin]){
                if(!bel[i]) a=b,b=i,cnt++;//只需要两个不在环里的点，统计前两个就行了
                if(cnt>=2){
                    puts("YES");
                    cout<<top+2<<endl;
                    ll lt=genshin;
                    while(top){
                        cout<<lt<<" "<<q[top]<<endl;
                        lt=q[top--];
                        bel[lt]=0;
                    }
                    cout<<genshin<<" "<<a<<endl;
                    cout<<genshin<<" "<<b<<endl;
                    return 1;
                }
            }
        }
        if(y==fa||bel[y])continue;//只需要一个环，不要走除了特殊点以外 已经经过的点
        if(dfs(y,x,genshin))return 1;
        bel[y]=0;
        top--;
    }
    return 0;
}
priority_queue<pair<ll,ll> > qt;
void sol(){
    //多测不清空，亲人两行泪
    //多测忘记换行，出门直达天堂
    for(int i=1;i<=n;i++){
        if(!qt.empty())qt.pop();
        v[i].clear();
        bel[i]=d[i]=0;
    }
    n=fr(),m=fr();
    while(m--){
        ll x=fr(),y=fr();
        v[x].push_back(y);
        v[y].push_back(x);
        d[x]++;
        d[y]++;
    }
    for(int i=1;i<=n;i++)if(d[i]>=4)qt.push({d[i],i});//奇怪的优化方法
    while(!qt.empty()){
        top=0;
        ll t=qt.top().se;
        qt.pop();
        if(dfs(t,0,t))return ;
    }
    puts("NO");
}
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    ll T;
    T=fr();
    while(T--)sol();
    return 0;
}
```




---

