# The Road to Berland is Paved With Good Intentions

## 题目描述

Berland has $ n $ cities, some of them are connected by bidirectional roads. For each road we know whether it is asphalted or not.

The King of Berland Valera II wants to asphalt all roads of Berland, for that he gathered a group of workers. Every day Valera chooses exactly one city and orders the crew to asphalt all roads that come from the city. The valiant crew fulfilled the King's order in a day, then workers went home.

Unfortunately, not everything is as great as Valera II would like. The main part of the group were gastarbeiters — illegal immigrants who are enthusiastic but not exactly good at understanding orders in Berlandian. Therefore, having received orders to asphalt the roads coming from some of the city, the group asphalted all non-asphalted roads coming from the city, and vice versa, took the asphalt from the roads that had it.

Upon learning of this progress, Valera II was very upset, but since it was too late to change anything, he asked you to make a program that determines whether you can in some way asphalt Berlandian roads in at most $ n $ days. Help the king.

## 样例 #1

### 输入

```
4 4
1 2 1
2 4 0
4 3 1
3 2 0
```

### 输出

```
4
3 2 1 3
```

## 样例 #2

### 输入

```
3 3
1 2 0
2 3 0
3 1 0
```

### 输出

```
Impossible
```

# 题解

## 作者：RainFestival (赞：5)

首先明确一点，每一个点改变 $k,k\ge1$ 次是没有必要的，因为可以通过改变 $0$ 或者 $1$ 次操作完成任意次操作。

所以我们将每一个点的变化次数看成一个 $0/1$ 变量。

对于每条边 $(x,y,v)$:

+ $v=0$ 时 $(x,y)=(1,0)$ 或 $(0,1)$

+ $v=1$ 时 $(x,y)=(0,0)$ 或 $(1,1)$

然后可以套用 2-sat 解决问题

代码如下：

```cpp
#include<cstdio>
#include<vector>
#include<queue>
#define o(x) (x+2*(x<=n)*n-n)
std::queue<int> q;
std::vector<int> a[200005];
int n,m,f[200005];
void add(int x,int y){a[x].push_back(y);a[y].push_back(x);}
int dfs(int v)
{
	for (int i=0;i<a[v].size();i++)
	{
		int u=a[v][i];
		if (f[u]==-1)
		{
			f[u]=1;f[o(u)]=0;
			q.push(u),q.push(o(u));
			if (!dfs(u)) return 0;
		}
		else if (f[u]==0) return 0;
	}
	return 1;
}
int twosat()
{
	for (int i=1;i<=2*n;i++) f[i]=-1;
	for (int i=1;i<=n;i++)
		if (f[i]==-1)
	    {
		    while (!q.empty()) q.pop();
    		f[i]=1,f[i+n]=0;q.push(i),q.push(i+n);
	    	if (dfs(i)) continue;
		    while (!q.empty()) f[q.front()]=-1,q.pop();
    		f[i]=0,f[i+n]=1;q.push(i),q.push(i+n);
	    	if (dfs(i+n)) continue;
		    while (!q.empty()) f[q.front()]=-1,q.pop();
	    	return 0;
    	}
	return 1;
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		int x,y,v;
		scanf("%d%d%d",&x,&y,&v);
		v?(add(x,y),add(x+n,y+n)):(add(x+n,y),add(x,y+n));
	}
	if (!twosat()) puts("Impossible");
	else
	{
		int cnt=0;
		for (int i=1;i<=n;i++) if (f[i]) ++cnt;
		printf("%d\n",cnt);
		for (int i=1;i<=n;i++) if (f[i]) printf("%d ",i);
		puts("");
	}
	return 0;
}
```


---

## 作者：water_tomato (赞：4)

## 题意

[题目链接](https://www.luogu.com.cn/problem/CF228E)

有若干个点和若干条边，每条边都为 $0$ 或 $1$ ，每次可以对一个点进行操作，与这个点相连的所有边的值都会改变（ $0$ 变为 $1$，$1$ 变为 $0$），现在寻求一种方案，使得所有边最终都变为 $1$ ，若找不到这种方案，输出 `Impossible` 。

## 解析

首先我们发现，每个点一定是只操作 $1$ 次或 $0$ 次的，因为我们如果对一个点操作 $2$ 次，则这两次操作会相互抵消，是无意义的。

接着我们发现，初值为 $0$ 的边，与之相连的点一定有且只有一个被操作过；初值为 $1$ 的边，与之相连的边一定均未被操作过或均被操作过。也就是说，与 $0$ 相连的点的操作状态是**不同**的，与 $1$ 相连的点的操作状态是**相同**的，因此我们考虑染色。

对于一条 $0$ 的边，我们将两个相邻点染成不同颜色，对于一条 $1$ 的边，我们将两个相邻点染成相同颜色，若发现染色矛盾，则输出`Impossible`。这显然可以使用 dfs 解决。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m,cnt,head[N];
int vis[N];//染色为 0 or 1
bool impossible;
struct edge{
	int to,next,color;
}e[N<<1];
inline void add(int x,int y,int co){
	e[++cnt].to=y;
	e[cnt].color=co;
	e[cnt].next=head[x];
	head[x]=cnt;
}
inline void dfs(int u,int color){
	if(impossible) return;
	vis[u]=color;
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to,flag=e[i].color;
		if(flag==0){
			if(vis[v]==3){
				dfs(v,color^1);	
			}
			else{
				if(vis[v]==vis[u]) impossible=true;	
			}
		}
		else{
			if(vis[v]==3){
				dfs(v,color);
			}
			else{
				if(vis[v]!=vis[u]) impossible=true;
			}
		}
		if(impossible) return;
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,x,y,co;i<=m;i++){
		scanf("%d%d%d",&x,&y,&co);
		add(x,y,co);add(y,x,co);
	}
	for(int i=1;i<=n;i++){
		vis[i]=3;
	}
	for(int i=1;i<=n;i++){
		if(vis[i]==3) dfs(i,0);
	}
	if(impossible){
		printf("Impossible");
		return 0;
	} 
	int ans=0;
	for(int i=1;i<=n;i++){
		if(vis[i]==0) ans++;
	}
	printf("%d\n",ans);
	for(int i=1;i<=n;i++){
		if(vis[i]==0) printf("%d ",i);
	}
	return 0;	
}
```



---

## 作者：Feyn (赞：3)

有没有一种可能，这道题可以不用 2-Sat，用种类并查集就可以解决。主要是个人感觉并查集写起来会简单得多。

稍微分析一下二者适用范围的区别：种类并查集只能维护比较简单的信息，如“$A$ 和 $B$ 在或不在同一集合”；而 2-Sat 可以维护更加复杂的信息，如“如果 $A$ 成立，那么 $B$ 就不成立”。可以看出来 2-Sat 一般是以有向边来记录限制的（比如上面那个例子就不能推出如果 $B$ 不成立那么 $A$ 就成立），而种类并查集只能维护无向边的限制，也就是说当两个物体是双向相关的时候才能使用种类并查集。

说回这道题，一个点只可能被操作零次或者一次，这就对应了两个集合。而每条边能获得的信息要么是两个点被操作次数相同，要么是操作次数不同。前者可以翻译成强制两个节点在同一集合内，后者可以翻译成不在同一集合。于是就可以用种类并查集做了。

实现上就是种类并查集的套路了，如果不会的可以左转模板区。我的代码显然复杂度不够优秀，事实上这种方法是可以做到近似线性的，但数据范围使得我懒得搞那些了。所以看看就好，仅供参考。

```cpp
int f[N],m,n;
inline int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
inline void merge(int x,int y){f[find(x)]=find(y);}

bool vis[N];
vector<int>ans;

signed main(){
	
	read(m);read(n);int x,y,v;
	for(int i=1;i<=m*2;i++)f[i]=i;
	while(n--){
		read(x);read(y);read(v);
		if(v)merge(x,y),merge(x+m,y+m);
		else merge(x,y+m),merge(x+m,y);
	}
	for(int i=1;i<=m;i++)if(find(i)==find(i+m))return printf("Impossible\n"),0;
	for(int i=1;i<=m;i++){
		if(vis[i]||vis[i+m])continue;int nowf=find(i);
		for(int j=1;j<=2*m;j++)if(find(j)==nowf)vis[j]=true,j<=m&&(ans.push_back(j),true);
	}
	printf("%d\n",ans.size());for(int i:ans)printf("%d ",i);
	
	return 0;
}
```

---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 1900}$
---
### $\text{2-sat 问题}$

$\text{2-sat}$ 问题就是给定若干布尔类型的变量和若干约束方程，要求给所有的变量赋值使得所有的方程被满足。

解决 $\text{2-sat}$ 可以采用的方法是强联通分量。为每一个变量建立两个点，一个表示真，另一个表示假。再将所有的方程写成“如果变量 $a$ 为某值，则变量 $b$ 必定为某值”的形式。例如 $a$ 或 $b$ 为真就可以写成如果 $a$ 为假，则 $b$ 一定为正，如果 $b$ 为假则 $a$ 一定为真。

然后对于有这样关系的两个点连上一条有向边，这样一个点的后继节点就可以理解为被若干条件束缚以后一旦其中的某一个取该值，则后继的所有点一定取对应的值。

那么如果发现 $a$ 取真值的点和 $a$ 取假值的点在同一个强联通分量中，就意味着无论 $a$ 如何取值都一定会和条件冲突。

而反之就可以证明一定存在至少一组解。一组可行的解是所有的变量取拓扑序小的那一个点代表的值。

这样的复杂度是 $O(n+m)$，还是很优秀的。

---
### 解题思路：

然后这个题就是一个 $\text{2-sat}$ 板子题了。

容易发现对于任意一个点而言，操作两次和没有操作的状态是完全一样的，所以可以简单地将是否操作点作为一个布尔变量。

边的限制也非常明显，如果一条边的权值是 $0$，则需要且仅需要连接两点中的一个进行操作，也就是一个点不操作意味着另一个点一定要操作，一个点操作意味着另一个一定不操作。反之如果一个点的权值是 $1$，就意味着两个点要不然都操作，要不然都不操作。直接连边就好了。


---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=4000005;
int n,m,x,y,z,head[MAXN],nxt[MAXN],num[MAXN],CNT;
int tot,dfn[MAXN],low[MAXN],st[MAXN],top,col[MAXN],col_num,dfs_num;
bool v[MAXN];
void add(int x,int y){
	nxt[++tot]=head[x];
	head[x]=tot;
	num[tot]=y;
}
void tarjan(int now){
	low[now]=dfn[now]=++dfs_num;
	st[++top]=now;
	v[now]=1;
	for(int i=head[now];i;i=nxt[i]){
		if(dfn[num[i]]==0){
			tarjan(num[i]);
			low[now]=min(low[now],low[num[i]]);
		}
		else if(v[num[i]]){
			low[now]=min(low[now],dfn[num[i]]);
		}
	}
	if(low[now]==dfn[now]){
		col_num++;
		while(st[top]!=now){
			col[st[top]]=col_num;
			v[st[top]]=0;
			top--;
		}
		col[st[top]]=col_num;
		v[st[top]]=0;
		top--;
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&x,&y,&z);
		if(z==0){
			add(x+n,y);add(y+n,x);
			add(x,y+n);add(y,x+n);
		}
		else{
			add(x+n,y+n);add(x,y);
			add(y+n,x+n);add(y,x);
		}
	}
	for(int i=1;i<=2*n;i++)
	if(dfn[i]==0)tarjan(i);
	for(int i=1;i<=n;i++)
	if(col[i]==col[i+n]){
		printf("Impossible\n");
		return 0;
	}
	for(int i=1;i<=n;i++)
	if(col[i]>col[i+n])CNT++;
	printf("%d\n",CNT);
	for(int i=1;i<=n;i++)
	if(col[i]>col[i+n])
	printf("%d ",i);
	printf("\n");
	return 0;
}
```


---

## 作者：到底几只鱼呢 (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF228E)

考虑每次染色操作，其实相当于异或，也就是说两次对同一条边的染色操作是可以抵消的。

换句话说，当原边权为 $1$ 时，我们不希望更改它，所以两边操作次数的奇偶性应相同，反之，则应相反。

那么据此建图，套用 **2-sat** 模型：

当 $w(i,j)=1$ 时，

`add(i,j),add(j,i),add(i+n,j+n),add(j+n,i+n)`

当 $w(i,j)=0$ 时，

`add(i,j+n),add(j+n,i),add(i+n,j),add(j,i+n)`

关于统计答案：

如果同一个点矛盾了，即 `scc[i]==scc[i+n]`，那么显然 `Impossible`。

如果没有，在 **2-sat** 问题中，拓扑序大的即为答案，而我们已经求出了 SCC 编号(与拓扑序为逆序)，所以 SCC 编号小的即为合法答案。

**Code：**

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace HMFS{
    const int maxn=1e5;
    basic_string<int> g[maxn];
    int n,m,dfn[maxn],sum,low[maxn],timcnt,stack[maxn],top,instack[maxn],scc[maxn];
    void tarjan(int u) {
        dfn[u]=low[u]=++timcnt;
        stack[++top]=u,instack[u]=1;
        for(int i=0;i<g[u].size();i++) {
            int v=g[u][i];
            if(!dfn[v]) tarjan(v),low[u]=min(low[u],low[v]);
            else if(instack[v]) low[u]=min(dfn[v],low[u]);
        }
        if(low[u]==dfn[u]) {
            int t;sum++;
            do{
                t=stack[top--];
                scc[t]=sum;
                instack[t]=0;
            }while(u!=t);
        }
    }
    void work() {
        cin>>n>>m;
        for(int x,y,z,i=1;i<=m;i++) {
            cin>>x>>y>>z;
            if(z==0) g[x]+=(y+n),g[y+n]+=x,g[y]+=(x+n),g[x+n]+=y;
            if(z==1) g[x]+=y,g[x+n]+=(y+n),g[y]+=x,g[y+n]+=(x+n);
        }
        for(int i=1;i<=2*n;i++) if(!dfn[i]) tarjan(i);
        for(int i=1;i<=n;i++) {
            if(scc[i]==scc[i+n]) cout<<"Impossible",exit(0);
        }
        int cnt=0;
        for(int i=1;i<=n;i++) if(scc[i]<scc[i+n]) cnt++;
        cout<<cnt<<'\n';
        for(int i=1;i<=n;i++) if(scc[i]<scc[i+n]) cout<<i<<' ';
    }
}
int main() {
    return HMFS::work(),0;
}
```

---

## 作者：hloixyh (赞：0)

本题可以不使用 2-Sat，使用拓展域并查集便能解决本题。

由于当我们在操作中有两次操作的是相同的点时，相当于没有操作（如样例 1 中有两个 3，相当于在 3 上没操作），所以在我们的答案中我们可以将点最终分为两个集合，一个是操作一次的，另一个是操作零次的。我们可以发现在同一个集合中，操作数是相同的。

有以上结论后我们可以实现一种做法：将每个点再拓展出一个点，且设这两个点操作数是不同的。然后将边读入，每一条边都可以给我们带来一些条件，使我们将所有点逐渐合并。当一条边两边分别为 $x$ 与 $y$ 且边权为 1 时，我们可以将 $x$ 与 $x$ 拓展出的点分别与 $y$ 与 $y$ 拓展出的点合并；当一条边两边分别为 $x$ 与 $y$ 且边权为 0 时，我们可以将 $x$ 与 $x$ 拓展出的点分别与 $y$ 拓展出的点与 $y$ 合并。将点通过边的条件合并完后，若出现某个点与其拓展出的点在同一集合，则没有方案可满足条件，因为这与我们的定义不符。接下来我们将这些点进行匹配，从而得到答案，对于所有原来的点（即不包括拓展出的点）在所有还没进行匹配的点中找到与自己在同一集合的点，若这个点不是拓展出的点，则需在这个点上进行一次操作。

具体细节和做法见代码。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int fa[205],n,m,ans[205],t=0;
bitset<205> v;
int fi(int x){
	if(fa[x]==x){
		return x;
	}else{
		return fa[x]=fi(fa[x]);
	}
}
void jo(int x,int y){
	int o1=fi(x),o2=fi(y);
	if(o1!=o2){
		fa[o1]=o2;
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		fa[i]=i;
		fa[i+n]=i+n;
	}
	for(int i=0;i<m;i++){
		int x,y,h;
		cin>>x>>y>>h;
		if(h==1){
			jo(x,y);
			jo(x+n,y+n);
		}else{
			jo(x,y+n);
			jo(x+n,y);
		}
	}
	for(int i=1;i<=n;i++){
		if(fi(i)==fi(i+n)){
			cout<<"Impossible";
			return 0;
		}
	}
	for(int i=1;i<=n;i++){
		if(v[i]==1||v[i+n]==1){
			continue;
		}
		for(int j=1;j<=2*n;j++){
			if(fi(j)==fi(i)){
				v[j]=1;
				if(j<=n){
					ans[t]=j;
					t++;
				}
			}
		}
	}
	cout<<t<<"\n";
	for(int i=0;i<t;i++){
		cout<<ans[i]<<" ";
	}
	return 0;
}

```

感谢阅读。

---

## 作者：Atserckcn (赞：0)

## [CF228E](https://www.luogu.com.cn/problem/CF228E) 题解

#### 题目简述

给定一个 $n$ 个点，$m$ 条边的无向图，每条边都为 $0$ 或 $1$，可以进行若干次操作，与此点相连的所有点权值取反，求一种方案使得所有边都变为 $1$。

#### 前置知识

+ 图的染色

#### 思路简述

首先明白一点：对于同一条边，操作偶数次是没有必要的！因为最终会回到初始状态。

对于任意一条边 $i$，有：

若 $v_i = 0$，则状态为 $(x_i,y_i)=(0,1)$ 或 $(x_i,y_i)=(1,0)$。

若 $v_i=1$，则状态为 $(x_i,y_i)= (0,0)$ 或 $(x_i,y_i)=(1,1)$。

然后我们就可以想到思路了。

用一个 `color` 数组来存储某个点 $x$ 是没被染色（`color[x]=-1`），还是染为黑或白色（`color[x]` 等于 $0$ 或 $1$）。

如果遇到某一条边，两个顶点颜色一样，则输出 `Impossible`，无解。

否则统计某种颜色的顶点个数，再依次输出即可。

#### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=105,M=N*(N-1)/2;
int n,m,color[N],u,v,op,cnt_ans;
struct E{
	int from,to,pre,co;
}e[M<<1];
int head[N],cnt_e;
void add(int from,int to,int co)
{
	e[++cnt_e].from=from;
	e[cnt_e].to=to;
	e[cnt_e].pre=head[from];
	e[cnt_e].co=co;
	head[from]=cnt_e;
	return;
}
void dfs(int u,int co)
{
	color[u]=co;
	for(int i=head[u];i;i=e[i].pre)
	{
		int v=e[i].to,col=e[i].co;
		if(!col)
		{
			if(color[v]==-1)
				dfs(v,co^1);
			else
			{
				if(color[v]==color[u])
				{
					printf("Impossible\n");
					exit(0);
				}
			}
		}
		else
		{
			if(color[v]==-1)
				dfs(v,co);
			else
				if(color[u]!=color[v])
					printf("Impossible\n"),exit(0); 
		}
	}
	return;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		color[i]=-1;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&u,&v,&op);
		add(u,v,op);
		add(v,u,op);
	}
	for(int i=1;i<=n;i++)
		if(color[i]==-1)
			dfs(i,0);
	for(int i=1;i<=n;i++)
		if(!color[i])
			++cnt_ans;
	printf("%d\n",cnt_ans);
	for(int i=1;i<=n;i++)
		if(!color[i])
			printf("%d ",i);
	puts("");
	return 0;
}
```

---

## 作者：maple_trees_112 (赞：0)

嗯，打一篇 2-sat 的模板题。

如果有一条边的边权是 0,就有 $[x][1]$，$[y][0]$ 或 $[x][0]$，$[y][1]$。

反之边权为 1时，则有 $[x][1]$，$[y][1]$ 或 $[x][0]$，$[y][0]$。

接下来就用 2-sat 解决问题。

代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 4000005;
int sum,dep[N],size[N],st[N],top,prim[N],bfs,dfs,n,m,x,y,z,hd[N],nxt[N],num[N],tmp;
bool v[N];
void add(int x,int y)
{
	nxt[++sum] = hd[x];
	hd[x] = sum;
	num[sum] = y;
}
void pushup(int now)
{
	size[now] = dep[now] = ++dfs;
	st[++top] = now;
	v[now] = 1;
	for(int i = hd[now];i;i = nxt[i])
	{
		if(dep[num[i]] == 0)
		{
			pushup(num[i]);
			size[now] = min(size[now],size[num[i]]);
		}
		else if(v[num[i]])
		{
			size[now] = min(size[now],dep[num[i]]);
		}
	}
	if(size[now]==dep[now])
	{
		bfs++;
		while(st[top] != now)
		{
			prim[st[top]] = bfs;
			v[st[top]] = 0;
			top--;
		}
		prim[st[top]] = bfs;
		v[st[top]] = 0;
		top--;
	}
}
int main(){
	std::cin>>n>>m;
	for(int i = 1;i <= m;i++)
    {
		std::cin>>x>>y>>z;
		if(z == 0)
        {
			add(x + n,y);
            add(y + n,x);
			add(x,y + n);
            add(y,x + n);
		}
 		else
        {
			add(x + n,y + n);
            add(x,y);
			add(y + n,x + n);
            add(y,x);
		}
	}
	for(int i = 1;i <= 2 * n;i++)
	if(dep[i] == 0)
    {
        pushup(i);
    }
	for(int i = 1;i <= n;i++)
	{
        if(prim[i]==prim[i+n])
        {
		    std::cout<<"Impossible";
            std::cout<<endl;
		    return 0;
	    }
    }
	for(int i = 1;i <= n;i++)
	{
        if(prim[i] > prim[i+n])
		{
			tmp++;
		}
    }
	std::cout<<tmp<<endl;
	for(int i = 1;i <= n;i++)
	{
		if(prim[i] > prim[i + n])
		{
			std::cout<<i<<endl;
		}
	}
	return 0;
}
```


---

## 作者：hswfwkj_ (赞：0)

首先对于这道题，有一个结论是很显然的：**每条权值为 $0$ 的边最多被修改一次，权值为 $1$ 的最多被修改最多两次** 因为你如果修改多次，那么操作就会互相抵消。那么我们接下来可以推导出这些结论；

设给定边的两个端点是 $x$ 和 $y$。
1. 当这条边的权值为 $0$ 时，要么 $x$ 被修改，要么 $y$ 被修改。
1. 当这条边的权值为 $1$ 时，要么 $x,y$ 都不做修改，要么都做修改。

如果我们把修改看作 $1$，不变看作 $0$，那么上面的结论就可以表达成如下形式：
1. 当这条边的权值为 $0$ 时，$(x,1),(y,0)$ 或 $(x,0),(y,1)$.
1. 当这条边的权值为 $1$ 时，$(x,1),(y,1)$ 或 $(x,0),(y,0)$.

看到这，我们发现对于每个节点，它的状态只有两种，那么很自然可以想到 2-SAT，接下来按照题意实现就行了。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,m,tot;
vector<int>g;
int ver[N],nxt[N],head[N];
int top,res,cnt;
int ins[N],stk[N],dfn[N],low[N],vis[N];
inline void add(int x,int y)
{
    ver[++tot]=y;
    nxt[tot]=head[x];
    head[x]=tot;
}
void tarjan(int x)
{
    vis[x]=1;
    stk[++top]=x;
    dfn[x]=low[x]=++res;
    for(int i=head[x];i;i=nxt[i])
    {
        int y=ver[i];
        if(!dfn[y])
        {
            tarjan(y);
            low[x]=min(low[x],low[y]);
        }
        else if(vis[y])low[x]=min(low[x],dfn[y]);
    }
    if(low[x]==dfn[x])
    {
        cnt++;
        while(stk[top+1]!=x)
        {
            ins[stk[top]]=cnt;
            vis[stk[top--]]=0;
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        int x,y,z;
        cin>>x>>y>>z;
        if(z==1)
        {
            add(x,y);
            add(y,x);
            add(x+n,y+n);
            add(y+n,x+n);
        }
        else
        {
            add(x,y+n);
            add(y,x+n);
            add(x+n,y);
            add(y+n,x);
        }
    }
    for(int i=1;i<=2*n;i++)
        if(!dfn[i])
           tarjan(i);
    for(int i=1;i<=n;i++)
        if(ins[i]==ins[i+n])
        {
            cout<<"Impossible\n";
            return 0;
        }
    for(int i=1;i<=n;i++)
    {
        if(ins[i]<ins[i+n])
            g.push_back(i);
    }
    cout<<g.size()<<'\n';
    for(int i=0;i<g.size();i++)
        cout<<g[i]<<' ';
    return 0;
}
```

---

## 作者：Dita (赞：0)

[题面](https://www.luogu.com.cn/problem/CF82D)

**solution**

这是一道 2-sat 的模板题 = =

- 如果一条边为 $0$，那么两个端点只能选一个。
- 如果一条边为 $1$，那么两个端点要么都选，要么都不选。

然后就可以直接上 2-sat 判断是否合法，输出方案了。

**注意是边是双向边。**

**code**

```c++
/*
work by:Ariel_
Knowledge:
Time:
*/
#include <iostream>
#include <cstring>
#include <cstdio>
#include <stack>
#include <vector>
#define ll long long
#define rg register
using namespace std;
const int MAXN = 1e5 + 5;
int read(){
    int x = 0,f = 1; char c = getchar();
    while(c < '0'||c > '9') {if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') {x = x*10 + c - '0'; c = getchar();}
    return x*f;
}
int n, m;
vector<int> G[MAXN];
int low[MAXN], dfn[MAXN], tot, scc[MAXN], cnt;
bool vis[MAXN];
stack<int> s;
void Tarjan(int x) {
   low[x] = dfn[x] = ++tot;
   s.push(x), vis[x] = 1;
   for (int i = 0; i < G[x].size(); i++) {
   	   int v = G[x][i];
   	   if (!dfn[v]) {
   	      Tarjan(v);
		  low[x] = min(low[x], low[v]);	
	   }
	   else low[x] = min(dfn[v], low[x]);
   } 
   int k;
   if(low[x] == dfn[x]) {
   	  cnt++;
   	  do{
   	    k = s.top(); s.pop();
   	    scc[k] = cnt;
	  }while(k != x);
   }
}
int main(){
   n = read(), m = read();
   for (int i = 1; i <= m; i++) {
   	  int u = read(), v = read(), w = read();
   	  if (w) {
   	  	G[u].push_back(v), G[v].push_back(u);
   	  	G[u + n].push_back(v + n), G[v + n].push_back(u + n); 
	  }  else {
	    G[u + n].push_back(v), G[v].push_back(u + n);
   	  	G[v + n].push_back(u), G[u].push_back(v + n); 
	  }
   }
   for (int i = 1; i <= (n << 1); i++) if(!dfn[i]) Tarjan(i);
   for (int i = 1; i <= n; i++) 
   	 if (scc[i] == scc[i + n]) { printf("Impossible"); return 0;}
   int step = 0;
   for (int i = 1; i <= n; i++) if(scc[i] < scc[i + n]) step++;
   printf("%d\n", step);
   for (int i = 1; i <= n; i++) if(scc[i] < scc[i + n]) printf("%d ", i);
   puts("");
   return 0;
}

```



---

