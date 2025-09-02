# [USACO09DEC] Dizzy Cows G

## 题目描述

The cows have taken to racing each other around the farm but they get very dizzy when running in circles, and everyone knows that dizzy cows don't produce any milk. Farmer John wants to convert all of the two-way cow paths in the farm to one-way paths in order to eliminate any 'cycles' and prevent the cows from getting dizzy.  A 'cycle' enables a cow to traverse one or more cow paths and arrive back at her starting point, thus completing a loop or circle.

The farm comprises N pastures (1 <= N <= 100,000) conveniently numbered 1..N. M1 (1 <= M1 <= 100,000) one-way cow paths and M2 two-way cow paths (1 <= M2 <= 100,000) connect the pastures. No path directly connects a pasture to itself, although multiple paths might connect two different pastures. A cow may or may not be able to travel between any two given pastures by following a sequence of cow paths.

Your job is to assign a direction to the two-way cow paths such that the entire farm (ultimately with only one-way paths) has no cycles. That is, there should be no sequence of one-way cow paths which leads back to its starting position. The existing one-way cow paths do not form a cycle and should be left as they are.

One-way cow paths run from pasture A\_i (1 <= A\_i <= N) to pasture B\_i (1 <= B\_i <= N). Two-way cow paths connect pastures X\_i (1 <= X\_i <= N) and Y\_i (1 <= Y\_i <= N).

Consider this example:

```cpp
1-->2 
|  /| 
| / | 
|/  | 
3<--4 
```
The cow paths between pastures 1 and 3, 2 and 3, and 2 and 4 are two-way paths. One-way paths connect 1 to 2 and also 4 to 3. One valid way to convert the two-way paths into one-way paths in such a way that there are no cycles would be to direct them from 1 to 3, from 2 to 3, and from 3 to 4:

```cpp
1-->2 
|  /| 
| / | 
vL  v 
3<--4 
```


## 样例 #1

### 输入

```
4 2 3
1 2
4 3
1 3
4 2
3 2
```

### 输出

```
1 3
4 2
2 3```

# 题解

## 作者：小年轻w (赞：22)

这题可以用拓扑排序，我们可以这样加边，先按拓扑排序，把入度为0 的加入 队列，（这题无向边入度不加），遍历他的所有边，如果碰到一条他连出去的无向边 并且这条无向边还没有被标记过，那么直接标记一下，这样做就一定能保证无环，如果最终所有的点里面还有点没有入队过，说明这些点在环中，则说明没有可行的方案，直接输出 -1。




```cpp
#include <stdio.h>
#include<iostream>
#include <algorithm>
using namespace std ;
const int maxn = 1000016,maxe = 3000000 ;
struct node{
    int to,pre,val,from;
}e[maxe];
int x,y,n,e1,e2,cnt,num,h,t ;
int into[maxn],q[maxn],head[maxn] ;
inline void addedge(int x,int y,int w) 
{
    e[++cnt].to = y;e[cnt].from=x;
    e[cnt].pre = head[x] ;
    e[cnt].val=w; 
    head[x] =cnt;
}
int main(){
    scanf("%d%d%d",&n,&e1,&e2) ;
    for(int i=1;i<=e1;i++) {
        scanf("%d%d",&x,&y) ;
        addedge(x,y,0);into[y]++;
    } 
    for(int i=1;i<=n;i++) 
        if(into[i]==0) q[++t]=i;
    if(cnt%2==0) cnt++;
    for(int i=1;i<=e2;i++){
        scanf("%d%d",&x,&y);
        addedge(x,y,1);
        addedge(y,x,1);
    }
    while(h<t) {
        int u=q[++h] ; 
        for(int i=head[u];i;i=e[i].pre) {
            if(e[i].val==0) {
                into[e[i].to]--; 
                if(into[e[i].to]==0) q[++t]=e[i].to;
            } 
         }
         for(int i=head[u];i;i=e[i].pre)
             if(e[i].val==1) e[i^1].val=2;
     }
    for(int i=1;i<=cnt;i++)
        if(e[i].val==1) printf("%d %d\n",e[i].from,e[i].to);
    return 0 ;
}

```

---

## 作者：Hehe_0 (赞：15)



### [传送门](https://www.luogu.com.cn/problem/P2017)
 [USACO09DEC]Dizzy Cows G
######  ~~bike曾说过：‘我们要熟练运用STL’~~
 
 看到这个有向边无向边，和无环，很容易想到拓扑排序。
 
 **这题可以考虑用dfs和bfs去写**  
 


 拓扑排序，记录编号，然后无向边的顺序按排序后序号的大小确定方向

------------

##  详细看代码注释
 




//此处存边是用vector，可邻接表。。。
bfs策略：  
如果是有向边，去记录他的入度... 
 将所有入度为零的点记入容器  
 在后面每个边的指向的入度--，当点的入度又为0时，再次入队。  
 这样也就可以使联通的遍历了。
 ```cpp
#include<bits/stdc++.h>
//bfs 版 
using namespace std;
int n,p1,p2;
vector<int >a[100010];
int in[100010];//记录该点的入度 
int p,w,cnt;
queue<int> q;//其实这里只是需要一个容器，stack也可（大概 
int t[100001];//记录位置 

int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>p1>>p2;
	
	for(int i=0;i<p1;i++)
	{//输入有向边
		cin>>p>>w;
		in[w]++;//将指向的点入度++ 
		a[p].push_back(w);//加入 
	}
	for(int i=1;i<=n;i++)	
	{
		if(in[i]==0)//若入度为零 
		q.push(i);//将其放入容器 
	}
	
	while(q.size()>0)
	{
		int x=q.front();
		q.pop();
		t[x]=cnt++;//放位置 
		for(int i=0;i<a[x].size();i++)
		{
			in[a[x][i]]--;
			//将此点的边指向的点的入度-- 
			if(in[a[x][i]]==0)//若入度为零 
			q.push(a[x][i]);//将其入队 
		}
		
	}
	for(int i=0;i<p2;i++)
	{
		cin>>p>>w;
		if(t[p]<t[w])//观察位置 
		cout<<p<<" "<<w<<endl;
		else
		cout<<w<<" "<<p<<endl;
	}
	
	return 0;
}
```


------------
dfs主要进行编号，但是以单纯以一个点无法全遍历。  

注意：这样所求的序是反的。



```cpp
#include<bits/stdc++.h>
//dfs 版 
using namespace std;
int n,p1,p,q,w;
vector<int >a[100011];//我们可以去用vector存边 
bool v[100011];//记录是否搜过 
int t[100011],cnt;
//如果 某个点想 
void dfs(int x) 
{ 
	for(int i=0;i<a[x].size();i++)
	{ 
		if(!v[a[x][i]])//如果没入容器 
		dfs(a[x][i]);//以他为下个起点 
	}
	v[x]=1;//标记，走过 
	t[x]=cnt;//编号 
	cnt++;
	return ; 
}

int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>p1>>p2;
	for(int i=0;i<p1;i++)
	{
		cin>>q>>w;
		a[q].push_back(w);//边 
	}
	for (int i=1;i<=n;i++) 
	{//多次，一次dfs很有可能走不完 
		if(!v[i]) //如果没走过 
			dfs(i);
	}
	
	for(int i=0;i<p2;i++)
	{
	cin>>q>>w;	//因为 dfs求的是倒序 
		if (t[q]>t[w])//所以这里和bfs不同 
			cout<<q <<" "<<w<<endl;
		 else 
			cout<<w <<" "<<q<<endl;
	}
	return 0;
}
```
[关于拓扑排序](https://oi-wiki.org/graph/topo/)  
[关于vector](https://oi-wiki.org/lang/csl/sequence-container/)  
dfs求拓扑序的板子
```cpp
vector<int> G[MAXN];  // vector 实现的邻接表
int c[MAXN];          // 标志数组
vector<int> topo;     // 拓扑排序后的节点

bool dfs(int u) {
  c[u] = -1;
  for (int v : G[u]) {
    if (c[v] < 0)
      return false;
    else if (!c[v])
      if (!dfs(v)) return false;
  }
  c[u] = 1;
  topo.push_back(u);
  return true;
}

bool toposort() {
  topo.clear();
  memset(c, 0, sizeof(c));
  for (int u = 0; u < n; u++)
    if (!c[u])
      if (!dfs(u)) return false;
  reverse(topo.begin(), topo.end());
  return true;
}
```


---

## 作者：Zxsoul (赞：6)

**思路**

dfs完成**拓扑排序**，拓扑这个东西核心就是排序，排什么序呢，将无向图变成一个有向无环图（DAG），这个就是题目的要求吗，双边就不跑，只跑单边，把拓扑序找到，再依次判断方向

对于拓扑序来说，dfs后深度越浅的点，拓扑序越大，然后只讲大的指向小的，就不会形成环了

```c
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;

const int A = 1e7+10;
const int B = 1e6+10;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

inline int read() {
  char c = getchar();
  int x = 0, f = 1;
  for ( ; !isdigit(c); c = getchar()) if (c == '-') f = -1;
  for ( ; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
  return x * f;
}

struct node{int v,nxt,T,tem;}e[B];
int head[B],cnt,n,m,fa[B],p1,p2,vis[B],t[B];
void modify(int u,int v,int type,int opt)
{
	e[++cnt].nxt=head[u];
	e[cnt].v=v;
	e[cnt].T=type;
	e[cnt].tem=opt; 
	head[u]=cnt;
}
int a[B],b[B],pj,root[B];
void per(int u)
{
	for (int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if (vis[v]) continue;
		per(v);
	}
	vis[u]=1;
	t[u]=pj++;
	return;
}
int main()
{
	int x,y,js=0;
	n=read(),p1=read(),p2=read();
	for (int i=1;i<=p1;i++)
	{
		x=read(),y=read();
		modify(x,y,1,0);
	}
	for (int i=1;i<=n;i++)
	{
		if (!vis[i]) per(i);
	}
	for (int i=1;i<=p2;i++)
	{
		x=read(),y=read();
		if (t[x]>t[y])
		printf("%d %d\n",x,y);
		else 
		printf("%d %d\n",y,x);
	}
	
}
```

---

## 作者：小手冰凉 (赞：6)

这个号的第一发题解



先拓扑排序按有向边排序，记录序号，然后无向边的顺序按排序后序号的大小定向



```cpp
#include<bits/stdc++.h>
using namespace std;
struct edg{
    int x,y,next;
};
queue<int>q;
edg e[1000000];
int d[100000],l[1000000],t[1000000];
int maxn=0,cnt=0;
void add(int x,int y)
{
    e[++maxn]=(edg){x,y,l[x]};
    l[x]=maxn;
}
void topsort()
{
    while(!q.empty()){
        int now=q.front(); q.pop();
        for(int i=l[now];i;i=e[i].next)
            if(!(--d[e[i].y])){
                q.push(e[i].y);
                t[e[i].y]=++cnt;
            }
    }
}
int main()
{    
//    freopen("dizzy.in","r",stdin);
//    freopen("dizzy.out","w",stdout);
    int n,m1,m2;
    scanf("%d%d%d",&n,&m1,&m2);
    for (int i=1;i<=m1;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        add(x,y);
        ++d[y];
    }
    for (int i=1;i<=n;i++)
        if (!d[i]){
            q.push(i);
            t[i]=++cnt;
        }
    topsort();
    for(int i=1;i<=m2;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        if(t[x]<t[y])printf("%d %d\n",x,y);
        else printf("%d %d\n",y,x);
    }
    return 0;
}
```

---

## 作者：XL4453 (赞：2)

### 解题思路：

先考虑没有有向边的情况，可以直接给所有的点一个不重的权值，让所有的权值大的点给序号小的点连边，这样所有的点只能走到比其权值小的点，不存在环，且所有的边都一定能被定向。

如果其中多了若干的有向边，也就是要求如果存在一条有向边 $u$ 连向 $v$，$u$ 的权值一定要比 $v$ 的大。对于这样的情况，可以先只保留有向边，进行图的拓扑排序就能得到这样的一个权值序列。

复杂度 $O(n)$。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
const int MAXN=200005;
int n,m1,m2,head[MAXN],nxt[MAXN],num[MAXN],tot,x,y,d[MAXN],val[MAXN],cnt;
int q[MAXN],l,r;
void add(int x,int y){
	nxt[++tot]=head[x];
	head[x]=tot;
	num[tot]=y;
}
int main(){
	scanf("%d%d%d",&n,&m1,&m2);
	for(int i=1;i<=m1;i++){
		scanf("%d%d",&x,&y);
		add(x,y);
		d[y]++;
	}
	l=1;
	for(int i=1;i<=n;i++)
	if(d[i]==0)q[++r]=i;
	while(l<=r){
		int now=q[l];
		val[now]=++cnt;
		for(int i=head[now];i;i=nxt[i]){
			d[num[i]]--;
			if(d[num[i]]==0)q[++r]=num[i];
		}
		l++;
	}
	for(int i=1;i<=m2;i++){
		scanf("%d%d",&x,&y);
		if(val[x]<val[y])printf("%d %d\n",x,y);
		else printf("%d %d\n",y,x);
	}
	return 0;
}
```




---

## 作者：the_Death (赞：2)

前言，我有一[广（博）告（客）](https://www.cnblogs.com/gengyf/)，大佬点开看看吧，o(*////▽////*)q

------------

首先，看见有向边无环，我就想到了拓扑排序~~才不是看了讨论之后才知道的~~
拓扑排序是什么，相信大家都知道了，我就不在说了，不知道了，我帮你[百度](https://baike.baidu.com/item/拓扑排序/5223807?fr=aladdin)啊


------------
   我们可以知道一个性质：拓扑序在后面的点（例如a)和拓扑序在后面的点（例如b），连一条从b到a，就会形成环如下图
   
   （他老是挂，就看[网盘&&密码：gyhv](https://pan.baidu.com/s/1_Nf2pmjqZTd8WIH8AR-Dxw)QAQ，真是抱歉啊）
   
   所以，按题目要求，我们要避免成环，所以要在后面读入无向边时，去判断他们的拓扑序。为了方便的处理无向边，我们规定如果读入边a,b，则这条边就是a指向b，如果这条边的指向破坏拓扑序的话，就要改变指向，即变为由b指向a
   
   样例说明
   
   (我的样例说明也挂了，嘤嘤嘤(っ °Д °;)っ，所以还是请大家这张图也去看[网盘&&密码：x6r9](https://pan.baidu.com/s/1FKQvq8eMezkVQaSAxk7tVQ)真的对不起）
   

------------

   然后是愉悦的代码时间
   ```cpp
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
const int MAXN=100001;
int tot,a,b,n,p1,p2,cnt;int top[MAXN];
//top是拓扑排序后每个数的编号 
int head[MAXN],ver[MAXN],nxt[MAXN],deg[MAXN];//存图 
void add(int x,int y){
    ver[++tot]=y;nxt[tot]=head[x];
    head[x]=tot;deg[y]++;
}
void topsort(){//拓扑排序 
    queue<int> q;
    for(register int i=1;i<=n;i++)
        if(deg[i]==0) q.push(i),top[i]=++cnt;
    while(q.size()){
        int x=q.front();q.pop();
        for(register int i=head[x];i;i=nxt[i]){
            int y=ver[i];
            if(!(--deg[y])) q.push(y),top[y]=++cnt;
        }
    }
}
int main(){
    scanf("%d%d%d",&n,&p1,&p2);
    for(register int i=1;i<=p1;i++)
        scanf("%d%d",&a,&b),add(a,b);
    topsort();
    for(register int i=1;i<=p2;i++){
        scanf("%d%d",&a,&b);
        if(top[a]>top[b]) printf("%d %d\n",b,a);
        //如果在原本拓扑排序中a的序列在b后面，强行连一条从a到b的边，会有环 
        else printf("%d %d\n",a,b);
    }
    return 0;
}
```
最后的国际惯例：thankyou for your attention

---

## 作者：违规用户名U56916 (赞：2)

随机跳到这题，莫名其妙的一个思路，然后就莫名其妙的蓝题AC+1了

~\(≧▽≦)/~啦啦啦

我的思路大体是这样的，如果一个有向图没有环，那么一定可以进行拓扑排序

所以我们去想拓扑

对于原来的图，我们根据有向边统计入度，然后根据这个入度进行拓扑排序

不断的拿出拓扑排序队列里的点，拿出连上它的边，如果这个边是有向边，那么我们就安安心心的toposort~~英文名高大上~~

如果是无向边，那么就规定上它的方向就是这个队列拿出来的点指向这无向边的另一点，然后记得把这个无向边标记上，不要让它再拿出来！！！

因为拓扑排序的原因，所以我们这样的结果一定是正确的

具体标记无向边等等做法，且请客官看AC代码

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
int fr[100010],to[400010],nex[400010],tl;
int Fr[100010],To[400010];
bool fl[400010],vis[400010];
int sy[400010];
void add(int x,int y,bool f){
	to[++tl]=y;nex[tl]=fr[x];fr[x]=tl;fl[tl]=f;
}
int du[100010],cnt;
int n,p1,p2,x,y;
queue<int> q;
int main(){
	scanf("%d%d%d",&n,&p1,&p2);
	for(int i=1;i<=p1;i++){
		scanf("%d%d",&x,&y);
		add(x,y,false);
		du[y]++;
	}
	for(int i=1;i<=p2;i++){
		scanf("%d%d",&x,&y);
		add(x,y,true);add(y,x,true);
		sy[tl]=sy[tl-1]=++cnt;//这个数组便于记录无向边的信息
	}
	for(int i=1;i<=n;i++) if(!du[i]) q.push(i);
	while(!q.empty()){
		int x=q.front();
		q.pop();
		for(int i=fr[x];i;i=nex[i]){
			if(!fl[i]){
				if((--du[to[i]])==0) q.push(to[i]);
			}
			else{
				if(vis[sy[i]]) continue;//多好用
				vis[sy[i]]=true;
				Fr[sy[i]]=x;
				To[sy[i]]=to[i];
			}
		}
	}
	for(int i=1;i<=cnt;i++) printf("%d %d\n",Fr[i],To[i]);
	return 0;
}
```

这道题真的没有spj(⊙_⊙)？~~什么叫常规方法~~

---

## 作者：Sora1336 (赞：1)

### 题目描述

给定一个图，有有向边有无向边。现要求你给每个无向边赋予一个方向，使整个图变为一个有向无环图。

### 解法

观察到有向无环图这个字眼，我们很容易想到拓扑排序。在拓扑排序后，所有的有向边的性质就是都为由拓扑序小的点指向拓扑序大的点。

那么我们分离出有向边，对这些有向边进行拓扑排序。让无向边中拓扑序小的指向大的再输出。这就相当于分了一个层。肯定要向深度小的向深度大的指。这是一个非常直观的想法。

### 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;
const int maxn = 2e5 + 5;

int n, m1, m2, d[maxn];
int q1[maxn], q2[maxn], q0[maxn], c[maxn];
vector<int> e[maxn];
vector<int> l;

bool topsort() {
	queue<int> q;
	for(int i = 1; i <= n; i ++) 
		if(d[i] == 0) q.push(i);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		l.push_back(u);
		for(auto v : e[u]) {
			if(-- d[v] == 0) {
				q.push(v);
			}
		}
	}
	bool chk = 1;
	for(int i = 1; i <= n; i ++)
		chk &= (d[i] == 0);
	return chk;
}

void solve() {
	scanf("%d%d%d", &n, &m1, &m2);
	for(int i = 1; i <= n; i ++)
		e[i].clear(), d[i] = 0;
	l.clear();
	for(int i = 1, op, u, v; i <= m1; i ++) {
		scanf("%d%d",&u, &v);
		e[u].push_back(v), d[v] ++;
		q1[i] = u, q2[i] = v;
	}
	for(int i = m1 + 1, op, u, v; i <= m1 + m2; i ++) {
		scanf("%d%d", &u, &v);
		q1[i] = u, q2[i] = v;
	}
	if(!topsort()) cout << "NO" << endl;
	else {
		int i = 0;
		for(auto w : l) {
			i ++;
			c[w] = i;
		}
		for(int i = m1 + 1; i <= m1 + m2; i ++) {
			if(c[q1[i]] < c[q2[i]])
				cout << q1[i] << ' ' << q2[i] << endl;
			else 
				cout << q2[i] << ' ' << q1[i] << endl;
		}
	}
	// puts("");
}

int main() {
	int t;
	t = 1;
	while(t --) solve();
}
```

---

## 作者：LJ07 (赞：1)

## 题目简述
[题目传送门](https://www.luogu.com.cn/problem/P2017)

给定一个 $n$ 个点 $p1$ 条边的有向无环图，再给出 $p2$ 条无向边。

输出一个无向边定向方案使得该图仍为有向无环图。

## 思路简述

能连边 $u$ $\rightarrow$ $v$ 的前提是没有路径使得 $v$ 可以到 $u$ 。

容易想到拓扑排序，并记录点的入队时间 $ti[]$。

发现一个性质：若 $ti[u] \lt ti[v]$ , 则一定不存在一条路径使得 $v$ 可以到 $u$ 。

所以对于每一条无向边，出队时间早的点向出队晚的点连边即可。

## 丑陋の代码

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int init() {
	char c;
	while (!isdigit(c = getchar()));
	int x(c ^ 48);
	while (isdigit(c = getchar())) x = x * 10 + (c ^ 48);
	return x;
}
int n, p1, p2, head[100005], in[100005], id[100005], cnt, tot;
struct Edge {int to, nxt;}e[100005];
void add(int v, int u) {
	e[++tot] = (Edge) {v, head[u]};
	head[u] = tot, ++in[v];
}
int main() {
	n = init(), p1 = init(), p2 = init();
	for (int i(1); i <= p1; ++i) add(init(), init());
	queue<int> q;
	for (int i(1); i <= n; ++i)
		if (!in[i]) q.push(i);
	while (q.size()) {
		int u(q.front()); q.pop(); id[u] = ++cnt;
		for (int i(head[u]); i; i = e[i].nxt) 
			if (!--in[e[i].to]) q.push(e[i].to);
	}
	for (int i(1); i <= p2; ++i) {
		int u(init()), v(init());
		if (id[u] > id[v]) swap(u, v);
		printf("%d %d\n", u, v);
	}
	return 0;
}
```

~~这么水的蓝题应该没人做吧~~

---

## 作者：_edge_ (赞：1)

这题目就很奇怪(?

首先一看题面，~~(DAG? topu_sort 我来了！)~~，它让你把一张图的无向边改为有向边，然后使得整张图没有环。

那么思路是这样的，首先做一遍 topu_sort 然后把那些没用的节点全部删掉。

然后对于某一个节点，若它没有有向边的入度，强制把它入度制为 $0$，然后对它后面的无向边连接的节点更新，顺便记录一下答案。

然后可以用一个很神奇的暴力，若没有可以更新的节点就退出。 (因为我怕可能会有枚举到最后，删掉一些有向边之后会有新的可被选入入度强制制 $0$ 的节点)

因为题目保证有向边无环，所以肯定会有一次完成删除的。

最终统计答案的时候离线一下 (题目要求按顺序输出)

于是就愉快地 AC 了。

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
const int INF=2e5+5;
int n,m,m1,in[INF],head[INF],tot,ans[INF],ans1[INF],vis[INF];
queue <int> q;
struct _node_edge {
        int to_,next_,kk,fl;
} edge[INF*5];
void add_edge(int x,int y,int flag,int kk) {
        edge[++tot]=(_node_edge){y,head[x],kk,flag};
        head[x]=tot; in[y]++; if (!flag) vis[y]++; return;
}
void topu_sort(){
        for (int i=1; i<=n; i++) if (!in[i]) q.push(i);
        while (q.size()) {
                int xx=q.front(); q.pop();
                for (int i=head[xx]; i; i=edge[i].next_) {
                        if (!in[edge[i].to_]) continue;
                        if (edge[i].fl) {ans[edge[i].kk]=xx; ans1[edge[i].kk]=edge[i].to_;}
                        vis[edge[i].to_]-=(!edge[i].fl);
                        if (!--in[edge[i].to_]) q.push(edge[i].to_);
                }
        }
        return;
}
void topu_sort1(int x){
        q.push(x);
        while (q.size()) {
                int xx=q.front(); q.pop();
                for (int i=head[xx]; i; i=edge[i].next_) {
                        if (!in[edge[i].to_]) continue;
                        if (edge[i].fl) {ans[edge[i].kk]=xx; ans1[edge[i].kk]=edge[i].to_;}//cout<<xx<<" "<<edge[i].to_<<"\n";
                        vis[edge[i].to_]-=(!edge[i].fl);
                        if (!--in[edge[i].to_]) { q.push(edge[i].to_);}
                }
        }
        return;
}
signed main()
{
        // freopen("P2017_2.in","r",stdin);
        // freopen("ans.out","w",stdout);
        scanf("%d %d %d",&n,&m,&m1);
        for (int i=1; i<=m; i++) {
                int x=0,y=0; scanf("%d %d",&x,&y);
                add_edge(x,y,0,i);
        }
        for (int j=1; j<=m1; j++) {
                int x=0,y=0; scanf("%d %d",&x,&y);
                add_edge(y,x,1,j); add_edge(x,y,1,j);
        }
        topu_sort();
        int flag1=false;
        while (!flag1) {
                flag1=true;
                for (int i=1; i<=n; i++) {
                        if (!in[i] || vis[i]) continue;
                        in[i]=0;  topu_sort1(i); flag1=false;
                }
        }
        for (int i=1; i<=m1; i++) cout<<ans[i]<<" "<<ans1[i]<<"\n";
        return 0;
}

```


---

## 作者：Christopher_Yan (赞：1)

#### 解题思路
刚看到这个题的时候，按直觉写了个假拓扑，于是WA成了10分，接着我才发现自己原来对拓扑排序的理解还是不够到位。仔细考虑了拓扑的本质后，发现这个题纯属考验思维，其实直接按拓扑排序将走过的无向边染色即可。

感性认知：
假设你加入边$e[i]$的时候形成了一个环，那么说明$e[i].v$一定有一条出边经过数个点后达到了$e[i].u$，并且此时$e[i]$还没有被染色。这一定是不可能的，因为我们在做的是拓扑排序，而拓扑的过程不会出现环！既然现在走到了$e[i].u$，那么说明拓扑序更靠前的$e[i].v$已经被走过了，而走到$e[i].v$时，$e[i]$一定会被染色。所以假设不成立。

#### AC代码
```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cctype>
#include <queue>

using namespace std;

const int N = 3e5;

int n, m1, m2, A, B, ec = -1;
int a[N], b[N], vis[N], ind[N], f[N];

struct Edge
{
	int u, v, w, nxt;
}e[N << 1];

inline void Addedge(int a, int b, int c)
{
	++ec;
	e[ec].u = a;
	e[ec].v = b;
	e[ec].w = c;
	e[ec].nxt = f[a];
	f[a] = ec;
}

inline void read(int &x)
{
	int k = 1; x = 0;
	char c = getchar();
	while (!isdigit(c))
		if (c == '-') c = getchar(), k = -1;
		else c = getchar();
	while (isdigit(c))
		x = (x << 1) + (x << 3) + (c ^ 48),
		c = getchar();
	x *= k;
}

queue <int> q;

void topsort(void)
{
	while (!q.empty())
	{
		int cur = q.front(); q.pop();
		for (int i = f[cur]; i != -1; i = e[i].nxt)
		{
			if (e[i].w == 1 && e[i ^ 1].w != -1)
				{ e[i].w = -1; continue; }
			ind[e[i].v]--;
			if (ind[e[i].v] == 0) 
				q.push(e[i].v), vis[e[i].v] = 1;
		}
	}
	while (!q.empty()) q.pop();
}

int main()
{
	memset(f, -1, sizeof(f));
	read(n), read(m1), read(m2);
	for (int i = 1; i <= m1; ++i)
		read(a[i]), read(b[i]);
	for (int i = 1; i <= m2; ++i)
		read(A), read(B), Addedge(A, B, 1), Addedge(B, A, 1);
	for (int i = 1; i <= m1; ++i)
		Addedge(a[i], b[i], 0), ++ind[b[i]];
	for (int i = 1; i <= n; ++i)
		if (ind[i] == 0) 
			q.push(i), vis[i] = 1;
	topsort();
	for (int i = 0; i <= ec; ++i)
		if (e[i].w == -1)
			printf("%d %d\n", e[i].u, e[i].v);
	return 0;
}
```

---

## 作者：Azuree (赞：0)

[查看原题请戳这里](https://www.luogu.org/problemnew/show/P2017 "查看原题请戳这里")
# 每错，这是一道拓扑排序的题。
### 为什么这么说呢？
因为拓扑排序的前提要求是进行排序的图必须是DAG。我们在看这道题的要求，就会发现，当你把所有双向边改成单向边以后，这个图就一定是一个DAG，否则一定无解。
### 呢么，我们该怎么进行拓扑排序呢？
首先，对于给出的有向边，我们按照正常的拓扑排序的方式进行排序即可。
对于无向边，我们要双向连边，但是不更新入度。每当我们在拓扑排序是遍历到一条没有被处理过的双向边时，只需要把这条边的起点记录为当前正在遍历的节点即可。~~（想一想，为什么）·~
附一下代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define INF 0x7fffffff
#define ll long long

using namespace std;

struct Edge{
	int from,to,next,del;
}edge[2000005];

int t,a,b,n,p1,p2,head,tail,que[100001],d[100001],k[100001]; 

void add(int x,int y,int pd)
{
	edge[++t].to = y;
	edge[t].from = x;
	edge[t].next = d[x];
	d[x] = t;
	edge[t].del = pd;
}

int main()
{
	scanf("%d%d%d",&n,&p1,&p2);
	for( int i = 1; i <= p1; i++)
	{
		scanf("%d%d",&a,&b);
		add(a,b,0);
		k[b] ++;
	}
	if(t % 2 == 0) t++;
	for( int i = 1; i <= n; i++)
		if(k[i] == 0) que[++tail] = i;
	for( int i = 1; i <= p2; i++)
	{
		scanf("%d%d",&a,&b);
		add(a,b,1);
		add(b,a,1);
	}
	while(head < tail)
	{
		head++;
		int u = que[head];
		for( int i = d[u]; i; i = edge[i].next)
		{
			if(edge[i].del == 0)
			{
				k[edge[i].to] --;
                if(k[edge[i].to] == 0) que[++tail] = edge[i].to;
			}
			else
			if(edge[i].del == 1) edge[i^1].del = 2;
		}
	}
	for( int i = 1;i <= t; i++)
		if(edge[i].del == 1)
			printf("%d %d\n",edge[i].from,edge[i].to); 
	return 0;
}
```

---

