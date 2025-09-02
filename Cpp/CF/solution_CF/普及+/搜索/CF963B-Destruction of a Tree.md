# Destruction of a Tree

## 题目描述

You are given a tree (a graph with $ n $ vertices and $ n-1 $ edges in which it's possible to reach any vertex from any other vertex using only its edges).

A vertex can be destroyed if this vertex has even degree. If you destroy a vertex, all edges connected to it are also deleted.

Destroy all vertices in the given tree or determine that it is impossible.

## 说明/提示

In the first example at first you have to remove the vertex with index 1 (after that, the edges (1, 2) and (1, 4) are removed), then the vertex with index 2 (and edges (2, 3) and (2, 5) are removed). After that there are no edges in the tree, so you can remove remaining vertices in any order.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF963B/9b84e98fe96447b82c6a8ccba7a9e4a5189ce14b.png)

## 样例 #1

### 输入

```
5
0 1 2 1 2
```

### 输出

```
YES
1
2
3
5
4
```

## 样例 #2

### 输入

```
4
0 1 2 3
```

### 输出

```
NO
```

# 题解

## 作者：是个妹子啦 (赞：12)

## **题意：**
每次消除度数为偶数的叶子节点以及它所有的边，问这个树能否被消除完，能消除完需要输出消除的顺序

------------

## **做法:**
处理dfs序，用栈记录，先消除dfs序大的，若先消除根节点，其叶子节点要是无法消除就wa了，所以贪心消除最靠近叶子的节点


------------

## **注意:**
注意度数为0也是偶数

------------
代码：

```cpp
#include<cstdio>
#include<stack>
#define maxn 200005
using namespace std;
int n,fa[maxn],deg[maxn],vis[maxn],head[maxn],tot;
stack<int>sta;
int ans[maxn],num;//记录答案 
struct edge{int to,next;}e[maxn<<1];
inline void add(int u,int v){e[++tot] = (edge){v,head[u]};head[u] = tot;}
inline int read(){
    int x=0; char c=std::getchar();
    while(c<'0'||c>'9')c=std::getchar();
    while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=std::getchar();}
    return x;
}
void dfs1(int x,int f){//处理dfs序 
    fa[x] = f; sta.push(x);
    for(int i = head[x];i;i = e[i].next){
        int v = e[i].to;
        if(v == f) continue;
        dfs1(v,x);
    }
}
void dfs2(int x){
    vis[x] = 1; ans[++num] = x;
    for(int i = head[x];i;i = e[i].next){
        int v = e[i].to; deg[v] --;
        if(v == fa[x] || vis[v]) continue;
        if(!(deg[v] & 1)) dfs2(v);
    }
}
int main(){
    n = read(); int v;
    for(int i = 1;i <= n;i++){
        v = read();
        if(v){
        add(i,v); add(v,i);
        ++deg[v]; ++deg[i]; 
        }
    }
    dfs1(1,-1);
    while(!sta.empty()){
        int az = sta.top();
        sta.pop();
        if(!(deg[az] & 1)) dfs2(az);
    }
    if(num == n){ puts("YES");
        for(int i = 1;i <= num;i++)
        printf("%d\n",ans[i]);
    }
    else puts("NO");
    return ~~(0^0)*(0^0);
}
```

---

## 作者：_鱼非仙_ (赞：9)

考虑 DP。设 $f(u) \in \{0, 1\}$ 表示 **删去 $u$ 时，是否 *不需要* 删除边 $(\operatorname{fa}(u), u)$**，或者说 **$\operatorname{fa}(u)$ 是否需要比 $u$ 先删去**。

若 $v \in \operatorname{son}(u)$ 且 $f(v)=1$，则删去 $u$ 时需要删去边 $(u, v)$，反之则不需要。如果 $\bigoplus\limits_{v \in \operatorname{son}(u)} f(v)=1$，即需要删去奇数条边，则为了删去点 $u$，必须连同边 $(\operatorname{fa}(u), u)$ 一起删去，也就是 **$\operatorname{fa}(u)$ 要在 $u$ 之后删**。
故自底向上的递推式为：
$$f(u)=\left( \bigoplus_{v \in \operatorname{son}(u)} f(v) \right) \oplus 1$$
其中 $\oplus$ 表示异或。
若 $\operatorname{son}(u) = \varnothing$，则 $f(u) = 1$。

若 $f(\text{root}) = 0$，则输出 NO，否则输出 YES。

考虑如何输出方案。若 $f(u) = 1$ 则意味着 **删去 $u$ 前，$\operatorname{fa}(u)$ 需要先被删去**，故连有向边 $\operatorname{fa}(u) \to u$，否则连 $u \to \operatorname{fa}(u)$。最后按照拓扑序升序输出即可。

参考代码（C++11）：
```cpp
#include <cassert>
#include <cstdio>
#include <vector>

int n, s;
int fa[200002];
std::vector<int> e[200002];
bool f[200002];
int deg[200002];

void Dfs(int pos)
{
	f[pos] = true;
	for (auto &to : e[pos]) {
		assert(to != fa[pos]);
		Dfs(to);
		f[pos] ^= f[to];
		if (f[to])
			++deg[to];
		else
			++deg[pos];
	}
}

void Print(int pos)
{
	assert(deg[pos] == 0);
	--deg[pos];
	printf("%d\n", pos);
	if (!f[pos] && --deg[fa[pos]] == 0)
		Print(fa[pos]);
	for (auto &to : e[pos])
		if (f[to] && --deg[to] == 0)
			Print(to);
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &fa[i]);
		if (fa[i] == 0)
			s = i;
		e[fa[i]].push_back(i);
	}
	Dfs(s);
	if (!f[s]) {
		puts("NO");
		return 0;
	}
	puts("YES");
	for (int i = 1; i <= n; ++i)
		if (deg[i] == 0)
			Print(i);
	return 0;
}
```

---

## 作者：SIXIANG32 (赞：7)

第 520A 祭！  
闲话少说，切入正题——  

---
看上去这道题还是很迷的，不过还是能想到一些的。  
从最低端，最简单的叶子节点开始，叶子节点度数为 $1$，必须要删除父亲节点，如果父亲节点是偶数那最好直接删，但是如果是奇数呢？还得继续往上找。  
也就是说，我们可以先从下往上搜一遍树，看到度数为偶数的点直接删除，加入答案。  
剩下的再从上到下扫一遍，看看有没有漏的节点，如果有奇数度节点，那么肯定他的儿子与父亲都不是偶数度节点或被删除（要是是偶数度节点肯定被删除啦），因此无法删除，输出 ```NO```，否则就直接删除这个节点。  
代码：  
```cpp
#include <iostream>
#include <cstring> 
#define MAXN 200000
#define QWQ cout << "QWQ" << endl;
using namespace std;
int ans[MAXN + 10], S = 0;
struct node {
	int to, next;
} gra[MAXN * 2 + 10];
int tot = 0, head[MAXN + 10], fa[MAXN + 10], du[MAXN + 10];
bool vis[MAXN + 10];
void link(int x, int y) {
	gra[++tot].to = x, gra[tot].next = head[y], head[y] = tot;
}
void del(int u) {//删除节点
	du[u] = 0, du[fa[u]]--, ans[++S] = u, vis[u] = 1;
	for(int p = head[u]; p; p = gra[p].next) {
		int v = gra[p].to;
		du[v]--;
	}
}
void dfs(int u) {//第一次遍历
	for(int p = head[u]; p; p = gra[p].next) {
		int v = gra[p].to;
		dfs(v);
	}
	if(du[u] % 2 == 0) del(u);//在回溯时更新，相当于从叶子节点爬树
}
bool flag = 0;
void dfs2(int u) {//从上往下第二次遍历
	if(!vis[u]) if(du[u] % 2 == 1) flag = 1;
	else del(u);
	for(int p = head[u]; p; p = gra[p].next) {
		int v = gra[p].to;
		dfs2(v);
	}
}
int main() {
	int n, rt; cin >> n;
	for(int p = 1; p <= n; p++) {
		cin >> fa[p]; if(!fa[p]) {rt = p; continue;}
		link(p, fa[p]), du[fa[p]]++, du[p]++; 
	}
	dfs(rt);
	dfs2(rt);
	if(flag) {
		cout << "NO" << endl;
		return 0;
	}
	else cout << "YES" << endl;
	for(int p = 1; p <= S; p++)
		cout << ans[p] << endl;
}
```

---

## 作者：_JF_ (赞：3)

## CF963B Destruction of a Tree

题目大意：有一个 $n$ 个节点的树，如果一个点有偶数条边和他相连，那么这个点就可以删去。如果这棵树可以被完全删除的话，输出每个节点依次删除的顺序。

首先，如果 $n$ 个点，由于是树，就有 $n-1$ 条边。如果 $n$ 为偶数的话，$n-1$为奇数。删边的时候会有剩余，无法满足题意，输出  ```NO```  即可。

对于 $n$ 为奇数时，我们先用一遍深搜，从叶子节点开始，在回溯的时候处理出每个节点子树大小。

在第二个深搜时，我们开始检查当前节点是否可以被删去，即当前节点的子树数量为偶数的时候，直接输出当前节点即可。否则的话继续往下搜索。

code：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
int siz[N];
vector<int> g[N];
void dfs1(int node,int fath)
{
	siz[node]=1;
	for(int i=0;i<g[node].size();i++)
	{
		int pre=g[node][i];
		if(pre==fath)
			continue;
		dfs1(pre,node);
		siz[node]+=siz[pre];
	}
}
void dfs2(int node,int fath)
{
	for(int i=0;i<g[node].size();i++)
	{
		int pre=g[node][i];
		if(pre==fath)
			continue;
		if(siz[pre]%2==0)
			dfs2(pre,node);
	}
	cout<<node<<endl;
	for(int i=0;i<g[node].size();i++)
	{
		int pre=g[node][i];
		if(pre==fath)
			continue;
		if(siz[pre]%2!=0)
			dfs2(pre,node);
	}
}
int main()
{
	int n;
	cin>>n;
	if(n%2==0)
	{
		cout<<"NO"<<endl;
		exit(0);
	}
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		if(x==0)
			continue;
		g[i].push_back(x);
		g[x].push_back(i);
	}
	dfs1(1,1);
	cout<<"YES"<<endl;
	dfs2(1,1);
}
```



---

## 作者：DEADFISH7 (赞：3)

按照这个题的题意，感觉可以把这道题的重点放在了树上有几个点上，还有一颗树————点数=边数+1

开头肯定要特判当n为偶数的时候 肯定输出“NO” ——我感觉就是因为在这个情况下，边数成为了奇数，所以按题意消边总会有剩余

如果这样想，可以延伸到每一个子树里来求

先算一遍每个子树的size即每个子树里有几个点

然后搜索每个根节点-->找子节点为根节点的子树大小-->判断：

按照题目开头的思想：要看点数的奇偶性，所以在此我们也要看一下这棵子树所包含的点即子树大小的奇偶性
（ _因为是子树，其根结点必有一天连接其根结点的parents的边，因此一颗子树的大小便可以看成其度的大小_）

若一直是偶数就继续搜索，直到是奇数就输出他的parents结点；



------------


```cpp
#include<iostream>
#include<cstdio>
#include<aIgorithm>
#include<cmath>
#include<cstring>
#include<cstdIib>
#define p 1e6+7
#define N 300000
#define mc(a,b) memset(a,b,sizeof(a))
#define close std::ios::sync_with_stdio
using namespace std;
typedef long long ln;
int n;
int o=0;
int head[N];
int size[N];
struct node
{
	int f,n,t;
}e[N*2];
void add(int f,int t)
{
	++o;
	e[o].f=f;
	e[o].t=t;
	e[o].n=head[f];
	head[f]=o;
}
void work(int u,int pre);
void dfs(int u,int pre);
int main()
{
	scanf("%d",&n);
	if(!(n%2)) 
	{
		printf("NO/n");
		return 0;
	} 
	for(int x,i=1;i<=n;i++)
	{
		scanf("%d",&x);
		if(!x) continue;
		add(x,i),add(i,x);
	}
	work(1,1);
	printf("YES/n");
	dfs(1,1);
	return 0;
}
void work(int u,int pre)
{
	size[u]=1;
	for(int i=head[u];i;i=e[i].n)
	{
		int v=e[i].t;
		if(v==pre) continue;
		work(v,u);
		size[u]+=size[v];
	}
}
void dfs(int u,int pre)
{
	for(int i=head[u];i;i=e[i].n)
	{
		int v=e[i].t;
		if(v==pre) continue;
		if(size[v]%2==0) dfs(v,u);
	}
	printf("%d\n",u);
	for(int i=head[u];i;i=e[i].n)
	{
		int v=e[i].t;
		if(v==pre) continue;
		if(size[v]%2==1) dfs(v,u);
	}
}	
```
考前发题解 RP++

---

## 作者：Lyccrius (赞：2)

叶子节点肯定不能直接删。

那么叶子的父亲就要在叶子之前删，$(fa_u, u)$ 这条边就必须由 $fa_u$ 来删。

对于一个节点 $u$，统计其到儿子节点的边 $(u, v)$ 需要由 $u$ 删掉的个数。
* 为奇数，$(fa_u, u)$ 需要由 $u$ 删除。
* 为偶数，$(fa_u, u)$ 需要由 $fa_u$ 删除。

从下往上一路统计到 $root$，如果需要由 $root$ 删除的边树为奇数，那么无解。

否则可以根据 $fa_u$ 和 $u$ 的先后关系建新图按拓扑序输出。

具体地，$f_u$ 表示 $(fa_u, u)$ 这条边是否需要由 $fa_u$ 删除，也可以表述为 $fa_u$ 是否需要在 $u$ 之前删除。

于是有：

$$f_u = (\oplus f_{son_u}) \oplus 1)$$

树形 DP 即可。

---

## 作者：Tx_Lcy (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF963B)
## 思路
首先看到这题的第一反应就是暴力拓扑排序，首先把度数为偶数的点加进去，然后暴力删边，时间复杂度 $O(n+m)$，于是就可以得到这样的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=2e5+10;
int n,qsiz[N],num[N],vis[N],fa[N];
vector<int>a[N],ans;
inline bool topo_sort(){
	queue<int>q;
	for (int i=1;i<=n;++i){
	    if (fa[i]) qsiz[i]=a[i].size()+1;
	    else qsiz[i]=a[i].size();
	    sort(a[i].begin(),a[i].end());
	    if (qsiz[i]%2==0) q.push(i);
	}
	int num=0;
	while (!q.empty()){
		int x=q.front();q.pop();
		if (qsiz[x]&1 || vis[x]) continue;
		vis[x]=1,ans.push_back(x),++num;
		if (fa[x] && a[fa[x]].size()){
			a[fa[x]].erase(lower_bound(a[fa[x]].begin(),a[fa[x]].end(),x));
	        --qsiz[fa[x]];
	        if (!(qsiz[fa[x]]&1)) q.push(fa[x]);
	    }
        for (auto v:a[x]){
			--qsiz[v];
			if (!(qsiz[v]&1)) q.push(v);
		}
		while (a[x].size()) a[x].pop_back();
	}
	return num==n;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for (int i=1;i<=n;++i){
		cin>>fa[i];
		if (fa[i]) a[fa[i]].push_back(i);
	}
	if (topo_sort()){
		cout<<"YES\n";
		for (auto i:ans) cout<<i<<'\n';
	}else cout<<"NO\n";
	return 0;
}
```

但是这个东西假掉了，有些情况会误判成 $\verb!NO!$，主要是因为拓扑的顺序是乱掉的，所以有可能明明一个节点的儿子符合条件，然而你把它的父亲删掉了，它又不符合条件了。

这样，我们可以得出一个类似于贪心的思路，先删 $\verb!Dep!$ 大的，然后再删小的，可以尽可能对这棵树的影响小。
## 代码
然后就可以得到正确的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=2e5+10;
int n,qsiz[N],num[N],vis[N],fa[N],depth[N];
vector<int>a[N],ans;
inline bool topo_sort(){
	priority_queue< pair<int,int> >q;
	for (int i=1;i<=n;++i){
	    if (fa[i]) qsiz[i]=a[i].size()+1;
	    else qsiz[i]=a[i].size();
	    sort(a[i].begin(),a[i].end());
	    if (qsiz[i]%2==0) q.push(make_pair(depth[i],i));
	}
	int num=0;
	while (!q.empty()){
		int x=q.top().second;q.pop();
		if (qsiz[x]&1 || vis[x]) continue;
		vis[x]=1,ans.push_back(x),++num;
		if (fa[x] && a[fa[x]].size()){
			a[fa[x]].erase(lower_bound(a[fa[x]].begin(),a[fa[x]].end(),x));
	        --qsiz[fa[x]];
	        if (!(qsiz[fa[x]]&1)) q.push(make_pair(depth[fa[x]],fa[x]));
	    }
        for (auto v:a[x]){
			--qsiz[v];
			if (!(qsiz[v]&1)) q.push(make_pair(depth[v],v));
		}
		while (a[x].size()) a[x].pop_back();
	}
	return num==n;
}
inline void dfs(int x,int dep){
	depth[x]=dep;
	for (auto v:a[x]) if (!depth[v]) dfs(v,dep+1);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;int root;
	for (int i=1;i<=n;++i){
		cin>>fa[i];
		if (fa[i]) a[fa[i]].push_back(i);
		else root=i;
	}
	dfs(root,1);
	if (topo_sort()){
		cout<<"YES\n";
		for (auto i:ans) cout<<i<<'\n';
	}else cout<<"NO\n";
	return 0;
}
```


---

## 作者：HllwEureka (赞：2)

简单起见，我们用“Odd树”和“Even树”表示大小为奇数/偶数的树。
首先易知原树为Even树时无解。因为每次都会删掉偶数条边而Even树有奇数条边。
当我们要删掉一棵树的时候，我们将其划分为三个部分：根，Odd子树，Even子树。对于一棵Odd树，其Odd子树必然有偶数个，那么我们可以按Even子树-根-Odd子树的删除顺序将原树变成若干个Odd树。因为删完Even子树后根剩下偶数个度数，可以删掉。
那么接下来要删掉根上有一个额外度数的Even树。一棵Even树的Odd子树必然有奇数个，那么我们依然可以按Even子树-根-Odd子树的删除顺序将原树变成若干个Odd树。因为删完Even子树后根剩下奇数个度数，加上一个额外度数就可以删掉。
...
容易知道上述过程是递归的。而由于子树的大小必然严格小于原树，所以递归会收敛到最小的Odd树（一个独立的点），最小的Even树（零个点），这两个都是可以直接删掉的。所以任意一个Odd树都可以按上述过程删掉。
```cpp
vector<int> to[N];
void edAdd(int u,int v) {if(u) to[u].push_back(v),to[v].push_back(u);}
int fa[N],siz[N];
void dfs(int u)
{
    siz[u]=1;
    for(int i=0;i<to[u].size();i++)
    {
        int v=to[u][i];
        if(v!=fa[u]) fa[v]=u,dfs(v),siz[u]+=siz[v];
    }
}
void del(int u)
{
    for(int i=0;i<to[u].size();i++)
    {
        int v=to[u][i];
        if(v!=fa[u]&&siz[v]%2==0) del(v);
    }
    printf("%d ",u);
    for(int i=0;i<to[u].size();i++)
    {
        int v=to[u][i];
        if(v!=fa[u]&&siz[v]%2==1) del(v);
    }
}
```核心代码 放上 求过


---

## 作者：大菜鸡fks (赞：1)

从根节点往上走。能删就删。

由于删了以后会影响子树内的度数。所以再次遍历子树
```cpp
#include<cstdio>
using namespace std;
inline int read(){int x=0,f=1,ch=getchar(); while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();} while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x*f;}
inline void write(int x){if (x<0) putchar('-'),x=-x; if (x>=10) write(x/10); putchar(x%10+'0');}
inline void writeln(int x){write(x); puts("");}
const int N=2e5+5;
struct edge{
	int link,next;
}e[N<<1];
int n,head[N],tot,du[N];
inline void add_edge(int u,int v){
	e[++tot]=(edge){v,head[u]}; head[u]=tot;
}
inline void insert(int u,int v){
	add_edge(u,v); add_edge(v,u);
}
inline void init(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		int u=read();
		if (u) insert(u,i),du[i]++,du[u]++;
	}
}
bool mark[N];
int ans[N],cnt;
void dfs(int u,int fa,bool flag){
	if (!flag) {
		for (int i=head[u];i;i=e[i].next){
			int v=e[i].link;
			if (v!=fa&&!mark[v]){
				dfs(v,u,0);	
			}
		}
	}
	if (du[u]%2==0){
		du[u]=0; ans[++cnt]=u; mark[u]=1;
		for (int i=head[u];i;i=e[i].next){
			int v=e[i].link; --du[v];
			if (v!=fa&&!mark[v]){
				dfs(v,u,1);
			}
		}
	}
}
inline void solve(){
	dfs(1,0,0);
	if (cnt==n){
		puts("YES");
		for (int i=1;i<=n;i++) writeln(ans[i]);
	}else{
		puts("NO");
	}
}
int main(){
	init();
	solve();
	return 0;
} 
```

---

## 作者：ldj2006 (赞：0)

# CF963B Destruction of a Tree 题解

&emsp;&emsp;[洛谷题目链接](https://www.luogu.com.cn/problem/CF963B)

&emsp;&emsp;这里提供一个较为朴素的 DP 想法。

## 题意简述

&emsp;&emsp;给定一棵树，节点个数不超过 $2 \times 10^5$，每次可以删掉度数为偶数的点。问最后能不能删完；能删完给出删除方案。

## 思路分析

&emsp;&emsp;首先可以随便选一个点作为根。

&emsp;&emsp;其次，我们考虑在一棵子树的删除情况，我们令根节点为 $u$，它的直接儿子为 $v_1,v_2 \dots v_k$。考虑根节点的删除情况，以及删除时需要参考什么东西。我们发现，根节点删除分为两种情况：1. 它的父节点被删除了，也就是这颗子树没有（根节点的）“支上去”的那条边；2. 它的父节点还没删除，我就删除根节点。此时是有“支上去”的那条边的。

&emsp;&emsp;于是，我们令 $f_{u,t} ,t \in \{0,1\}$，$f_{u,0}$ 表示**没有**“支上去”的那条边的时候，是否可以删除；$f_{u,1}$ 表示有“支上去”的那条边的时候，是否可以删除。根据定义， $f_{u,t} \in \{0,1\}$ ，即状态表示的是“不可以”或者“可以”。

&emsp;&emsp;我们考虑子树内如何合理安排删除。我们假设我们现在已经知道了所有 $v_i,(1 \le i \le k)$ 的 $f_{v_i,0}$ 和 $f_{v_i,1}$ 结果。首先，如果存在 $f_{v_i,0} = 0$ 且 $f_{v_i,1} = 0$，那么显然无论如何安排删除顺序，也不能保证删除成功。

&emsp;&emsp;接下来我们分析如何安排删除顺序。我们发现，对于 $f_{v_i,0} = 0$ 且 $f_{v_i,1} = 1$ 的子节点，应当先删掉它所在的那颗子树（因为要保留 $u$ 到 $v_i$ 的那条边的时候才能删）。对于 $f_{v_i,0} = 1$ 且 $f_{v_i,1} = 0$ 的节点，我们必须在删掉 $u$ 之后删。对于 $f_{v_i,0} = 1$ 且 $f_{v_i,1} = 1$ 的节点，随便安排。

&emsp;&emsp;然后我们考虑根节点如何删除。我们发现，如果删掉前面必须删的那些点后，根节点剩下的边是偶数条，那就删掉，然后 $f_{u,0} \gets 1$ 即可。但是这里就有一个问题，假如说我们剩奇数条边的时候，我们可以再先删掉一个 $f_{v_i,0} = 1$ 且 $f_{v_i,1} = 1$ 的节点来使得度数变成偶数。于是这里要再判断一下。

&emsp;&emsp;奇数的时候同理，注意“支上去”的边也是连在根节点上的，所以对应的，$f_{u,1} \gets 1$。

&emsp;&emsp;具体实现的时候，我们不妨把一个点的子节点按照 $f_{v_i,0} = 0$ 且 $f_{v_i,1} = 1$ 的节点在前面，$f_{v_i,0} = 1$ 且 $f_{v_i,1} = 1$ 的节点在中间，$f_{v_i,0} = 1$ 且 $f_{v_i,1} = 0$ 的节点在后面，以此来排序。

&emsp;&emsp;输出方案的时候，我们可以对于每个点，搜索对应状态（比如根节点是 1，从 $f_{1,0}$ 开始搜索），再递归下去（对于 $f_{v_i,0} = 1$ 且 $f_{v_i,1} = 1$ 的节点，我们随便钦定一个就行）。所以一共是两遍 dfs，第一遍求状态，第二遍根据状态信息推出顺序。第二遍 dfs 的时候，代码中的分类有所简化，如果不清楚，可以尝试先各类写一遍再简化合并。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = 2e5 + 5;

struct edge
{
	int v,next;
}e[N*2];

int head[N];
int cnt;

void adde(int u,int v)
{
	++cnt;
	e[cnt].v =v;
	e[cnt].next = head[u];
	head[u] = cnt;
}

int n;
bool f[N][2];
vector<int> output;

struct node
{
	int idx;
	bool ck0,ck1;
};

bool cmp1(const node xx,const node yy)
{
	if(xx.ck1 != yy.ck1)
		return xx.ck1 > yy.ck1;
	return xx.ck0 < yy.ck0;
}

vector<node> vec[N];
int deg[N];
int tdx[N];

bool dfs(int u,int fa)
{
	bool check = true;
	for(int i = head[u];i != 0;i = e[i].next)
	{
		int v = e[i].v;
		if(v != fa)
		{
			deg[u]++;
			dfs(v,u);
			if(f[v][0] == 0 && f[v][1] == 0)
			{
				check = false;
				break;
			}
			vec[u].push_back({v,f[v][0],f[v][1]});
		}
	}
	if(deg == 0)
	{
		f[u][1] = 0;
		f[u][0] = 1;
	}
	else
	{
		sort(vec[u].begin(),vec[u].end(),cmp1);
		tdx[u] = -1;
		for(int i = 0;i < vec[u].size();i++)
		{
			if(vec[u][i].ck1 == 1 && vec[u][i].ck0 == 0)
			{
				tdx[u] = i;
			}
			else 
			{
				break;
			}
		}
		bool mody = false;
		if(tdx[u]+1 < vec[u].size() && vec[u][tdx[u]+1].ck1 == 1 &&  vec[u][tdx[u]+1].ck1 == 0)
		{
			mody = true;
		}
		if((deg[u]-(tdx[u]+1))%2 == 0)
		{
			f[u][0] = 1;
			if(mody)
				f[u][1] = 1;
		}
		else
		{
			f[u][1] = 1;
			if(mody)
				f[u][0] = 1;
		}
	}
	return check;
}

void efs(int u,int st)
{
	int i = 0;
	for(;i <= tdx[u];i++)
	{
		efs(vec[u][i].idx,1);
	}
	if(st == 0)
	{
		if((deg[u]-(tdx[u]+1))%2 != 0)
		{
			efs(vec[u][i].idx,1);
			i++;
		}
	}
	else
	{
		if((deg[u]-(tdx[u]+1))%2 != 1)
		{
			efs(vec[u][i].idx,1);
			i++;
		}
	}
	output.push_back(u);
	for(;i < vec[u].size();i++)
	{
		efs(vec[u][i].idx,0);
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	for(int i = 1;i <= n;i++)
	{
		int u;
		cin >> u;
		if(u != 0)
		{
			adde(u,i);
			adde(i,u);
		}
	}
	bool res = dfs(1,0);
	if(res == 0 || f[1][0] == 0)
	{
		cout << "NO\n";
		return 0;
	}
	cout << "YES\n";
	efs(1,0);
	for(int i = 0;i < output.size();i++)
	{
		cout << output[i] << "\n";
	}
	return 0;
}
```

---

## 作者：orz_z (赞：0)

## 题目大意

给你一棵树，如果树上的节点有偶数条边与它相连，则这个节点是可删除的，删除这个节点后所有与之相连的边也将删除。

判断一棵树是否可以依次删除所有节点。

可以删除输出 `YES`,并输出依次删除的点的编号; 不可以则输出 `NO`。

## 解题思路

显然，叶子节点度数为 $1$，必须要先删除父亲节点，如果父亲节点是偶数那直接删，但是如果是奇数还得继续往上找。

也就是说，我们可以先从下往上搜一遍树，看到度数为偶数的点直接删除，加入答案。

剩下的再从上到下扫一遍，如果有奇数度节点，那么肯定他的儿子与父亲都不是偶数度节点，无法删除，输出 `NO`，否则就直接删除这个节点。

## CODE

```cpp
#include <bits/stdc++.h>

#define _ 200005

using namespace std;

inline int read()
{
    int x = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
    {
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = getchar();
    }
    return x;
}

int n, fa[_], deg[_], vis[_], head[_], tot;

stack<int> sta;

int ans[_], num;

struct edge
{
    int to, next;
} e[_ << 1];

inline void add(int u, int v)
{
    e[++tot] = {v, head[u]};
    head[u] = tot;
}

void dfs1(int x, int f)
{
    fa[x] = f;
    sta.push(x);
    for (int i = head[x]; i; i = e[i].next)
    {
        int v = e[i].to;
        if (v == f)
            continue;
        dfs1(v, x);
    }
}

void dfs2(int x)
{
    vis[x] = 1;
    ans[++num] = x;
    for (int i = head[x]; i; i = e[i].next)
    {
        int v = e[i].to;
        deg[v]--;
        if (v == fa[x] || vis[v])
            continue;
        if (!(deg[v] & 1))
            dfs2(v);
    }
}

signed main()
{
    n = read();
    int v;
    for (int i = 1; i <= n; i++)
    {
        v = read();
        if (v)
        {
            add(i, v);
            add(v, i);
            ++deg[v];
            ++deg[i];
        }
    }
    dfs1(1, -1);
    while (!sta.empty())
    {
        int az = sta.top();
        sta.pop();
        if (!(deg[az] & 1))
            dfs2(az);
    }
    if (num == n)
    {
        puts("YES");
        for (int i = 1; i <= num; i++)
            printf("%d\n", ans[i]);
    }
    else
        puts("NO");
    return 0;
}
```



---

## 作者：hexagon (赞：0)

## CF963B

### Description

给定一颗 $n$ 个点组成的树，如果一个点的度数为偶数，就可以删去这个点及其相邻的边，问能否把一棵树删完。

$1\leq n\leq 2*10^5$

### solution

容易发现，每次删去一个点，都删去了偶数条边，所以如果一棵树的点数为偶数（边数为奇数），则无法删完。

我们从树的底部入手，对于一个叶子节点 $u$（度数为1），必然是先删它的父亲 $fa$ ，再删 $u$ 自己。对于 $u$ 的父亲节点 $fa$ ，在有解的情况下，如果 $fa$ 的儿子为奇数个（度数为偶数），那么这个节点必定要先删去，因为如果 $fa$ 的父亲先被删去，那么它的度数将为奇数，且它周围的点都不能删去，那么就会无解。反之，如果 $fa$ 的儿子个数为偶数，那么这个 $fa$ 的父亲必然比 $fa$ 先被删去。

于是我们就得到了做法，记 $d[u]$ 为节点 $u$ **现在**的度数：

+ 先从下往上（从叶子节点开始），对于一个节点 $u$ ，如果 $d[u]$ 为奇数，则先保留，如果为偶数，就把它删去。
+ 再从上往下（从根节点开始），对于一个节点 $u$, 如果 $d[u]$ 为奇数，那么无解，如果为偶数，就把它删去。

### code:

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a),i##end=(b);i<=i##end;i++)
#define per(i,a,b) for(int i=(a),i##end=(b);i>=i##end;i--)
#define mem(a,b) memset(a,b,sizeof(a))
using namespace std;
const int N=200005;
int n,tag[N],p,d[N];
vector <int> G[N],ans;
inline int read(){
	int f=1,x=0;
	char ch=getchar();
	while(ch>'9'||ch<'0') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
	return f*x;
}
inline void del(int x,int fa){
	d[x]=-1,ans.push_back(x);
	if(fa) d[fa]--;
	for(auto v:G[x]) if(v^fa) d[v]--;	
}
inline void dfs1(int u,int fa){
	for(auto v:G[u]) if(v^fa) dfs1(v,u);
	if(d[u]%2==0) del(u,fa);
}
inline void dfs2(int u,int fa){
	if(d[u]>=0){
		if(d[u]%2==0) del(u,fa);
		else return p=1,void();
	}
	for(auto v:G[u]) if(v^fa) dfs2(v,u);
}
int main(){
	n=read();
	rep(i,1,n){
		int x=read();
		if(x) G[x].push_back(i),G[i].push_back(x),d[x]++,d[i]++;
	}
	if(n%2==0) return printf("NO\n"),0;
	dfs1(1,0);
	dfs2(1,0);
	if(p==1) return printf("NO\n"),0;
	printf("YES\n");
	for(auto x:ans) printf("%d\n",x);
	return 0;
}
```



---

## 作者：7KByte (赞：0)

很有意思的一道题。

我们任意指定一个根，则叶子节点不能第一个删除。

换句话说，叶子节点必须先删除它的父亲，再删除它。

然后我们忽略叶子节点，由于叶子节点的顺序固定了，所以它父亲的顺序也能固定。

所以我们定义 $f[u]$ 表示节点 $u$ 是先删自己还是先删父亲，$0$ 表示先删自己。

显然叶子节点 $=1$。

对于任何一个节点 $u$ ，不难写出方程 $f[u]=degree_u\bigoplus\limits_{v\in son_{u}} \{f[v]\}$ 。

这里的 $degree$ 指度数的奇偶性，$\bigoplus$是异或和。

那么$f[root]=1$则无解，否则我们递归输出方案。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 200005
using namespace std;
int h[N],tot,n,f[N];
struct edge{
	int to,nxt;
}e[N<<1];
void add(int x,int y){
	e[++tot].nxt=h[x];h[x]=tot;e[tot].to=y;
}
void dfs(int x,int fa){
	for(int i=h[x];i;i=e[i].nxt)if(e[i].to!=fa)dfs(e[i].to,x),f[x]^=f[e[i].to];
		f[x]^=1;
}
void calc(int x,int fa){
	for(int i=h[x];i;i=e[i].nxt)if(e[i].to!=fa&&f[e[i].to])calc(e[i].to,x);
	printf("%d\n",x);
	for(int i=h[x];i;i=e[i].nxt)if(e[i].to!=fa&&!f[e[i].to])calc(e[i].to,x);
}
int main(){
	//freopen("INPUT","r",stdin);
	scanf("%d",&n);
	rep(i,1,n){
		int x;scanf("%d",&x);
		if(x)add(x,i),add(i,x),f[i]^=1,f[x]^=1;
	}
	dfs(1,0);
	if(!f[1]){puts("NO");return 0;}
	puts("YES");calc(1,0);
	return 0;
}
```

---

