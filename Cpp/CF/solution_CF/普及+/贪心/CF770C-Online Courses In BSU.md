# Online Courses In BSU

## 题目描述

Now you can take online courses in the Berland State University! Polycarp needs to pass $ k $ main online courses of his specialty to get a diploma. In total $ n $ courses are availiable for the passage.

The situation is complicated by the dependence of online courses, for each course there is a list of those that must be passed before starting this online course (the list can be empty, it means that there is no limitation).

Help Polycarp to pass the least number of courses in total to get the specialty (it means to pass all main and necessary courses). Write a program which prints the order of courses.

Polycarp passes courses consistently, he starts the next course when he finishes the previous one. Each course can't be passed more than once.

## 说明/提示

In the first test firstly you can take courses number $ 1 $ and $ 2 $ , after that you can take the course number $ 4 $ , then you can take the course number $ 5 $ , which is the main. After that you have to take only the course number $ 3 $ , which is the last not passed main course.

## 样例 #1

### 输入

```
6 2
5 3
0
0
0
2 2 1
1 4
1 5
```

### 输出

```
5
1 2 3 4 5 
```

## 样例 #2

### 输入

```
9 3
3 9 5
0
0
3 9 4 5
0
0
1 8
1 6
1 2
2 1 2
```

### 输出

```
6
1 2 9 4 5 3 
```

## 样例 #3

### 输入

```
3 3
1 2 3
1 2
1 3
1 1
```

### 输出

```
-1
```

# 题解

## 作者：WsW_ (赞：4)

提供一种较为好写的方法。  

---
### 思路
对于每一个需要通过的科目，都对其进行 dfs。  
在 dfs 中，存在以下情况：  
* 如果前置科目都已经通过了，直接通过这个科目就行。  
* 如果前置科目还没有通过，先通过前置科目，再通过这个科目。  

记得标记已通过的科目，防止重复通过。  

如何判环？  
如果某个科目被重复递归，那就说明有环。因为我们已经防止重复通过。  
另外再开一个标记记录每个科目是否被递归过就行了。  

答案输出格式比较难受，可以先将答案存入队列中，就能很方便地输出答案。  

---
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m;
int x,y;
bool vis[100003];//是否通过标记
bool vst[100003];//是否递归标记
vector<int>edg[100003];
queue<int>q;
queue<int>ans;

void pass(int t){
	if(vst[t]){//重复递归，有环
		cout<<-1;
		exit(0);
	}
	vst[t]=1;
	for(int i=0;i<edg[t].size();i++){
		if(!vis[edg[t][i]])pass(edg[t][i]);//先通过前置科目
	}
	vis[t]=1;//再通过这个科目
	ans.push(t);//按顺序存入答案
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	while(m--){
		cin>>x;
		q.push(x);
	}
	for(int i=1;i<=n;i++){
		cin>>x;
		while(x--){
			cin>>y;
			edg[i].push_back(y);
		}
	}
	while(!q.empty()){
		x=q.front();
		q.pop();
		if(!vis[x])pass(x);
	}
	cout<<ans.size()<<'\n';
	while(!ans.empty()){
		cout<<ans.front()<<' ';
		ans.pop();
	}
	return 0;
}
```

---

## 作者：dlzlj_2010 (赞：1)

看到前置科目，自然想到拓扑排序，只需要改一些细节就可以了。  
- 直接从每一个主要科目开始搜索，不是所有点都要搜索，原因显而易见。
- 搜索时遍历它的所有前置科目，如果未通过就先通过前置科目，随后通过此科目。
- 无解：如果一个科目已被访问但是未被通过，说明此点是搜索树上未被回溯的一个点，而它在回溯之前就被访问，那就一定是通过一个环返回起点，无解。
## code:
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const int N=1e5+5;
vector<int>e[N];//邻接表
int n,k;
int a[N];//关键科目
vector<int>ans;//结果
bool vis[N],passed[N];//是否被访问/通过
bool dfs(int u){//拓扑排序
	if(vis[u])return 0;//有环
	vis[u]=1;//标记为已访问
	for(auto v:e[u]){//遍历前置科目
		if(!passed[v]){//未通过
			bool f=dfs(v);//通过前置科目
			if(!f)//有环就一路返回0
				return 0;
		}
	}
	passed[u]=1,ans.push_back(u);//加入答案
	return 1;
}
signed main(){
	cin>>n>>k;
	for(int i=1;i<=k;i++){
		cin>>a[i];
	}
	for(int v=1;v<=n;v++){
		int m;
		cin>>m;
		for(int i=1;i<=m;i++){
			int u;
			cin>>u;
			e[v].push_back(u);
		}
	}
	for(int i=1;i<=k;i++){//遍历每个关键科目
		if(!passed[a[i]]){//未被通过
			bool f=dfs(a[i]);//搜索该点
			if(!f)return cout<<-1,0;//有环，输出-1
		}
	}
	cout<<ans.size()<<'\n';
	for(auto i:ans)cout<<i<<" ";
    return 0;
}
```

---

## 作者：Graph_Theory (赞：1)

一道搜索题,可以使用 DFS 爆搜。难点就在于判环。

这里如果只判断当前点是否被访问过就会出现右图被视为环的情况。

所以，在深搜的时候先访问节点再将这个点设为答案之后访问重复节点的时候，如果这个点不在答案里，那么这个点和父节点处于一个递归里。说明他们是环，则输出 `-1`。

![](https://cdn.luogu.com.cn/upload/image_hosting/adkz0fma.png)

代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
int sh[maxn],t,n,m,homo,edgesum;
vector <int> edge[maxn];
bool vis[maxn],flagof1=0,book[maxn];
int sum[maxn],sums=0;
void dfs(int now,int father)
{
	if(flagof1==1) return ;
	if(book[now]) return; 
	if(vis[now]==1)
	{
				flagof1=1;
				
				cout<<-1;
				return ;
	} 
	vis[now]=1;
	for(int i=0;i<edge[now].size();i++)
	{
		dfs(edge[now][i],now);
		if(flagof1==1) return ;
	}
	if(book[now]==0) 
	{
		book[now]=1;
		sum[++sums]=now;
	}
}
int main()
{
	cin>>n>>t;
	for(int i=1;i<=t;i++)
		cin>>sh[i];
	for(int i=1;i<=n;i++)
	{ 
		int TT;
		cin>>TT;
		while(TT--)
		{
			int v;
			cin>>v;
			edge[i].push_back(v);
		}
	}
	for(int i=1;i<=t;i++)
	{
		homo=i;
		memset(vis,0,sizeof(vis));
		if(flagof1) return 0;
		if(book[ sh[i] ]==0) dfs(sh[i],1);
	}	
	if(flagof1) return 0;
	cout<<sums<<endl;
	if(sums>=1)
	{
		for(int i=1;i<=sums;i++)
		{
			cout<<sum[i]<<" ";
		}
	}
	
	return 0;
}
```


---

## 作者：wmy_goes_to_thu (赞：1)

看到这道题，肯定要想什么情况无解，发现当环出现在你需要学的科目中，就无解，所以我们想到了构造有向图，然后求强联通分量。

的确如此，首先，把图按照科目 dfs 一下，构造新子图。然后，用 tarjan 判断是否有环。接着，如果没有环，需要用拓扑排序来找到顺序，这样就可以了！

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005],vist[100005],q[100005],deg[100005];
int dfn[200005],col[100005],low[200005],vst[200005],qa[200005],tot=0,ne=0;
vector<int>g[100005],g2[100005];
void dfs(int x)
{
	vist[x]=1;
	for(int i=0;i<g[x].size();i++)
	{
		int cu=g[x][i];
		g2[cu].push_back(x);
		deg[x]++;
		if(!vist[cu])dfs(cu);
	}
}
void tarjan(int x)
{
	vst[x]=1;
	dfn[x]=low[x]=++tot;
	qa[++ne]=x;
	for(int i=0;i<g2[x].size();i++)
	{
		int cu=g2[x][i];
		if(!dfn[cu])
		{
			tarjan(cu);
			low[x]=min(low[x],low[cu]);
		}else if(vst[cu])
		{
			low[x]=min(low[x],dfn[cu]);
		}
	}
	if(dfn[x]!=low[x])return;
	int pp;
	do
	{
		pp=qa[ne--];
		vst[pp]=0;
		col[pp]=x;
	}while(ne>0&&pp!=x);
}
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
	{
		int p;
		scanf("%d",&p);
		for(int j=1;j<=p;j++)
		{
			int af;
			scanf("%d",&af);
			g[i].push_back(af);
		}
	}
	for(int i=1;i<=m;i++)dfs(a[i]);
	for(int i=1;i<=n;i++)if(!col[i])
	{
		tot=ne=0;
		tarjan(i);
	}
	for(int i=1;i<=n;i++)if(i!=col[i])
	{
		cout<<-1<<endl;
		return 0;
	}
	int gs=0,head=0,tail=0;
	for(int i=1;i<=n;i++)if(vist[i])gs++;
	cout<<gs<<endl;
	for(int i=1;i<=n;i++)if(vist[i]&&!deg[i])q[++tail]=i;
	while(head<tail)
	{
		int pp=q[++head];
		for(int i=0;i<g2[pp].size();i++)
		{
			int cu=g2[pp][i];
			deg[cu]--;
			if(!deg[cu])q[++tail]=cu;
		}
	}
	for(int i=1;i<=tail;i++)cout<<q[i]<<" ";
	return 0;
}
```

---

## 作者：Atserckcn (赞：1)

## CF770C Online Courses In BSU 题解

[洛谷传送门](https://www.luogu.com.cn/problem/CF770C)。

[Codeforces 传送门](https://codeforces.com/contest/770/problem/C)。

### 题目简述

共有 $N$ 个科目，$M$ 个主要科目，每个科目都可能有前置科目，需完成前置科目后才可以完成此科目。求一个完成科目的顺序，使得这 $M$ 个科目都完成。

### 思路简述

虽然题目没有说若不能完成则输出 `-1`，但是通过样例 3 还是可以自己推断一下的。

那么我们就开始想想，怎么可以判断无解？

通过读题，发现题目可以转化为一个有向图，每一条边由此科目指向前置科目。

那么显然，若整张图出现了环，则肯定无解。

比如说 $A \rightarrow B,B\rightarrow C,C\rightarrow A$，就是无解。

接下来我们需要运用一个类似拓扑排序的东西（因为是要求方案嘛，很容易想到有向图的拓扑排序）。

每次遍历到一个点，都去遍历其指向的节点，并标记此点在**深搜遍历内**已被访问。注意是在深搜遍历内，不是在外边。

如果某次遍历到了之前标记过的节点，则说明存在环，直接输出 `-1`。

否则将点按照遍历顺序，依次存进答案容器中。由于是有顺序，建议使用队列。

### 代码

不会的就看代码吧，有注释。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
queue<int> q,ans;
bool vis[N],vis_dfs[N];
struct E{
	int from,to,pre;
}e[N];
int head[N],cnt_e,n,m,t,id;
void add(int from,int to)//链式前向星存图
{
	e[++cnt_e].from=from;
	e[cnt_e].to=to;
	e[cnt_e].pre=head[from];
	head[from]=cnt_e;
	return;
}
void dfs(int now)
{
	if(vis_dfs[now])//在搜索内被访问，无解
	{
		printf("-1\n");
		exit(0);
	}
	vis_dfs[now]=true;//标记，和下方区分
	for(int i=head[now];i;i=e[i].pre)//前置科目
	{
		int v=e[i].to;
		if(!vis[v])
			dfs(v);
	}
	vis[now]=true;//全局标记，和上方区分
	ans.push(now);
	return;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)//将所有重要科目存进去
	{
		scanf("%d",&t);
		q.push(t);
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&t);//连边
		while(t--)
		{
			scanf("%d",&id);
			add(i,id);
		}
	}
	while(!q.empty())
	{
		int x=q.front();//取出目前需要深搜的节点
		q.pop();
		if(!vis[x])//如果之前搜索其他节点时没被访问
			dfs(x);
	}
    //输出
	printf("%d\n",ans.size());
	while(!ans.empty())
		printf("%d ",ans.front()),ans.pop();
	putchar('\n');
	return 0;
}
```

[评测记录（Codeforces）洛谷爬虫透不进了。](https://codeforces.com/contest/770/submission/276095786)

---

## 作者：OldVagrant (赞：1)

## 题意
有 $n$ 门课程，其中 $k$ 门是主修课，只要学完所有的主修课就可以毕业。   
但在学习第 $i$ 门课程之前，要先学完给定的 $t_i$ 门前置课程。   
求最少要学习多少门课程才能毕业，并给出一种合法的方案。
## Solution
其实完全不需要什么拓扑排序，直接搜索即可，`*1500` 的题还是比较暴力的。   

首先，因为毕业只需要学完所有的主修课，那我们就可以想到一种贪心的思路，即对于每一门主修课 $a_i$，只去学 $a_i$ 的所有前置课程，$a_i$ 所有前置课程的所有前置课程，$a_i$ 所有前置课程的所有前置课程的所有前置课程......
不难发现这实际上是一个递归的过程，我们只需要设计出一个函数来模拟它。

如果并没有理解的话，请参考下面代码里的 `work` 函数。
## Code
```
#include <bits/stdc++.h>
#define debug() cout<<"Tianyi,I'm debuging."<<'\n'
#define gc getchar
#define pc(x) putchar(x)
using namespace std;
int a[100001],tot,ans[100001];
vector<int> pre[100001];
bool ok[100001],vis[100001];
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
void work(int x){
	if(ok[x]) return;//如果x已经被学完了，就可以直接return掉。
	if(vis[x]) cout<<-1,exit(0);//访问同一个点两次，意味着出现了环，而如果在work函数里遇到环的话就代表着某门主修课永远无法学习，于是无解。
	vis[x]=1;//标记一下
	for(auto j:pre[x]) work(j);//学习x之前，要先去学x的所有前置课程
	ans[++tot]=x,ok[x]=1;//学完了x的所有前置课程，现在可以学x了。
	return;
}
signed main(){
	int n=read(),k=read(),cnt=0;
	for(int i=1;i<=k;i++) a[i]=read();
	for(int i=1,m,x;i<=n;i++){
		m=read();
		while(m--) x=read(),pre[i].push_back(x);
	}for(int i=1;i<=k;i++) work(a[i]);
	write(tot),pc('\n');
	for(int i=1;i<=tot;i++) write(ans[i]),pc(' ');
	return 0;
}
```


---

## 作者：Billhqh9 (赞：0)

我的 AC 记录：[![](https://cdn.luogu.com.cn/upload/image_hosting/bwxubg34.png)](https://codeforces.com/problemset/submission/770/303341832)

看到这题时，我们看到完成一件事需要有其他事作为前提时，自然想起了拓扑排序。所以我们可以按照拓扑排序的方式先建好有向图。

但是，我们会看到这题与[普通拓扑排序](https://www.luogu.com.cn/problem/B3644)不同的一点是，他不需要把所有的事情全部做完，而是只要求做一部分。所以，我们不妨使用 DFS 来寻找必须做的每件事的前提，同时记录下答案，一定要注意判环！其实整体还是拓扑排序。如果实在不明白，最好还是加强一下拓扑排序，理解其中的原因。因为每个事不会重复算，所以最坏情况下也就把所有的点都遍历一遍，时间还是比较充裕的。（关于判环的解释附在代码后面）



### AC Code
```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>
#define pcr putchar
#define int long long//这道题数据范围比较大

using namespace std;

const int maxn = 1e5 + 5;

inline int read() {
    int num = 0, sign = 1;
    char c = getchar();
    while(c < '0' || c > '9')
        sign = (c == '-' ? -1 : sign), c = getchar();
    while(c >= '0' && c <= '9')
        num = (num << 3) + (num << 1) + c - '0', c = getchar();
    return num * sign;
}

vector<int> main_courses, ans, depends[maxn];
int ans_total = 0;
bool sf[maxn], pd[maxn];
//sf 用于判断这件事是否被做过。
//pd 用于判断是否出现环。

void get_ans(int course) {
    ++ans_total, sf[course] = pd[course] = true;
    for(int i : depends[course]) {
        if(pd[i] == true) {//如果下一个点已经在深搜搜下来的链上，则说明出现了环。
            putchar('-'), putchar('1');//输出“-1”
            exit(0);//终止程序。
        } else if(!sf[i]) {
            get_ans(i);
        }
    }
    pd[course] = false;//因为这个数组是用来判断有没有环，所以只能在当前搜的点上标记，一定要记得回溯时恢复初始状态。
    ans.push_back(course);
}

signed main() {

    int n = read(), k = read();
    for(int i = 1; i <= k; ++i)
        main_courses.push_back(read());
    for(int i = 1; i <= n; ++i)
        for(int j = read(); j--;)
            depends[i].push_back(read());

    for(int i : main_courses)
        if(!sf[i])
            get_ans(i);

    printf("%d\n", ans_total);

    for(int i : ans)
        printf("%d ", i);
    return 0;
}

```

我的代码中，比较难理解的是判环，在这里举例解释一下：
![](https://cdn.luogu.com.cn/upload/image_hosting/ufgb4viy.png)  
比如此时，按我的代码，此时只有 $1, 2, 5, 9, 6$ 这五个点在 pd 数组被打上了标记。当 $6$ 号点的下一步走向 $5$ 号点时，会发现 $5$ 号点被打了标记，于是就知道图中有环。总而言之，如果在 DFS 的过程中遇到了当前的遍历下来的链中的点，就一定出现了环，就一定无解。

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF770C)    
简单题。    
这题显然应该评黄，为啥评绿呢。
## 题意
有 $n$ 个课程，其中有 $k$ 个是必修课。   
如果想要学习课程 $i$，则需要先学习它所有的前置课程。   
现在要求给出一个合法的学习顺序，使得最后可以学完所有必修课且学习的课程最少，若无解输出 `-1`。     
## 解法
显然，无解的情况只能是构成了环，所以我们可以用拓补排序判环。     
接下来我们可以从每个必修课开始进行 dfs，走完所有它的前置课程并记录下答案即可。   
一些细节：   
- 我们判环时需要建反图。求结果时才能正向建图。   
- dfs 过程中要记录每个结点的访问情况，不能重复计数。   
- 判环时我们只需要判断必修课受不受影响就可以。如果存在环但是不影响学习必修课那么也可以忽略。   

[CODE](https://www.luogu.com.cn/paste/jnfyj4lg)

---

## 作者：Yingluosanqian (赞：0)

### 思路

如果必修课程在环内，则无解，否则有解，根据题意模拟输出即可。

### 实现

（区别于写这篇题解时已有的题解，这里给出另一种实现思路，这个思路完全基于拓扑排序）

* 建图时一个课程的前置课程指向该课程，**使用拓扑排序判环**，如果某个必修课程没有被排序，则说明它在环内，否则我们可以得到一组拓扑序。

* 建上述图的反图，然后使用优先队列，拓扑序大的先出队列。**一开始把所有的必修课程推进优先队列**，出队列时把反图中所有当前节点的子节点以及其拓扑序入队，于此同时使用一个栈，当前节点入栈（注意每个节点仅入栈一次，容易实现）并统计答案。直到队列为空（显然队列迟早为空）。

* 然后依次输出栈中节点即可。

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAXN=100050,MAXM=100050;

int n,m,head[MAXN],ind[MAXN],antihead[MAXN],vis[MAXN],vis2[MAXN],cnt=1,anticnt=1,viscnt=0;
//vis[]表示拓扑序，vis2[]表示在优先队列中是否以及出队列
int spc[MAXN];
//spc[]表示特殊点

struct EDGE{
	int to,nxt;
}edge[MAXM],antiedge[MAXM];

void add_edge(int iu,int iv,int h[],EDGE e[],int &c){
	e[++c]=(EDGE{iv,h[iu]});
	h[iu]=c;
}

struct NODE{
	int u,order;
	bool operator<(const NODE& b)const{return order<b.order;}
}top,tmp;

int main(){
	//输入 
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d",&spc[i]);
	}
	for(int i=1;i<=n;i++){
		int sum,tmp;
		scanf("%d",&sum);
		for(int j=1;j<=sum;j++){
			scanf("%d",&tmp);
			add_edge(tmp,i,head,edge,cnt);
			ind[i]++;
			add_edge(i,tmp,antihead,antiedge,anticnt);
		}
	}
	
	//判断可行性 
	bool isOK=true;
	queue<int> Q;
	priority_queue<NODE> pQ;
	for(int i=1;i<=n;i++){
		if(!ind[i]){
			Q.push(i);
		}
	}
	while(!Q.empty()){
		int u=Q.front();Q.pop();
		vis[u]=++viscnt;
		for(int i=head[u];i;i=edge[i].nxt){
			int v=edge[i].to;
			ind[v]--;
			if(!ind[v]){
				Q.push(v);
			}
		}
	}
	for(int i=1;i<=m;i++){
		tmp.u=spc[i];tmp.order=vis[spc[i]];
		pQ.push(tmp);
		if(!vis[spc[i]]){
			isOK=false;
		}
	}
	if(isOK==false){
		printf("-1");
		return 0;
	}
	
	//可行的话 
	int ans=0;
	stack<int> Stk;
	while(!pQ.empty()){
		top=pQ.top();pQ.pop();
		if(vis2[top.u]) continue;
		vis2[top.u]=1;
		Stk.push(top.u);
		ans++;
		for(int i=antihead[top.u];i;i=antiedge[i].nxt){
			int v=antiedge[i].to;
			tmp.u=v;tmp.order=vis[v];
			pQ.push(tmp);
		}
	}
	
	//输出
	printf("%d\n",ans);
	while(!Stk.empty()){
		int output=Stk.top();Stk.pop();
		printf("%d ",output);
	}
	
	return 0;
}
```


---

## 作者：hzxphy (赞：0)

## 题目描述
一共有 $N$ 个科目，其中有 $M$ 个主要科目，只要 $M$ 个主要科目都通过了，那么对应主人公就可以毕业了，也就是达成了目的。

现在有一个列表，表示要通过第 $i$ 门课程需要先通过的科目列表。现在主人公希望得到一个通过科目的顺序，使得最终他通过最少的科目使得主人公毕业。
## 思路
我们先想一下：怎样会无解？

即主修课程在环上面，相互嵌套，自然无解。

判断可以想到~~恶心的~~优秀的拓扑排序。

随后建反图跑 DFS 即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
bool book[100010],schedule[100010];
int want[100010],t[100010],in[100010];
vector<int>G[100010],G2[100010],a;
bool TopoSort(void){
    int arr[100010]={0};
    queue<int>Q;
    int tot=0,pot=0;
	for(int i=1;i<=n;i++){
		if(in[i]==0)Q.push(i);
	}
	while(!Q.empty()){
		int F=Q.front();Q.pop();
		arr[F]=++tot;
		for(auto i:G[F]){
			in[i]--;
			if(in[i]==0)Q.push(i);
		}
	}
	for(int i=1;i<=n;i++){
        if(schedule[i]&&arr[i]==0)return false;
	}
	return true;
}
void DFS(int u){
    if(book[u])return;
    for(auto i:G2[u]){
        DFS(i);
    }
    book[u]=true;
    a.push_back(u);
}
int main(){
    cin>>n>>k;
    for(int i=1;i<=k;i++){
        cin>>want[i];
        schedule[want[i]]=true;
    }
    for(int i=1;i<=n;i++){
        cin>>t[i];
        for(int j=1;j<=t[i];j++){
            int to;cin>>to;
            G[to].push_back(i);
            G2[i].push_back(to);
            in[i]++;
        }
    }
    if(!TopoSort()){
        puts("-1");
    }
    else{
        for(int i=1;i<=k;i++){
            if(!book[want[i]])DFS(want[i]);
        }
        cout<<a.size()<<'\n';
        for(int i=0;i<(int)a.size();i++){
            cout<<a[i]<<' ';
        }
    }
    return 0;
}
```

---

