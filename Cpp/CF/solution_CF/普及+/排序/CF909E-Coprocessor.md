# Coprocessor

## 题目描述

给你 $N$ 个任务，任务从 $0$ 开始标号，有些只能用主处理器处理，另外的任务只能用副处理器处理。其中存在 $M$ 个依赖关系，如果任务 $i$ 依赖于任务 $j$，那么称 $j$ 是 $i$ 的前继任务。

主处理器和副处理器都可以一次处理很多个任务。一个任务能被处理的条件为其所有的前继任务已经被执行过了，或者前继任务和自己同时被放进同一个处理器处理。


现在给出这些依赖关系和每个任务处理要用的处理器，求副处理器最少运行了几次。保证依赖关系是一张有向无环图。

## 样例 #1

### 输入

```
4 3
0 1 0 1
0 1
1 2
2 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 3
1 1 1 0
0 1
0 2
3 0
```

### 输出

```
1
```

# 题解

## 作者：dd_d (赞：10)

## 题意
给你一张 DAG，其中含 $n$ 个点和 $m$ 条有向边。  
给定两种处理器，主处理器和副处理器以及每个点对应的处理器。  
现要你求出副处理器的最少运行次数。  
注：若要处理当前点，则此结点的前驱结点必须被处理过或与此节点一起处理。  
## Sol
题目中要求副处理器运行次数最少，那么便是要主处理器运行次数最多。  
我们考虑让主处理器全部处理完再处理副处理器。  
那么怎么求呢？  
由 DAG 我们很容易会想到拓扑排序，考虑拓扑排序。  
开一个队列，让每个无前驱即入度为零的点进队，然后就行拓扑排序的操作。  
做完主处理器判断副处理器的队列中有无点即可。  
## Code：  
```cpp
//xhxh
#include<bits/stdc++.h>
using namespace std;
struct zmh
{
	int next,to;
}edge[400001];
bool vis[200001];
int n,m,head[200001],f[200001],ans,cnt;
queue<int> q1,q2;
int read()
{
	int pos=1,num=0;
	char ch=getchar();
	while (!isdigit(ch))
	{
		if (ch=='-') pos=-1;
		ch=getchar();
	}
	while (isdigit(ch))
	{
		num=num*10+(int)(ch-'0');
		ch=getchar();
	}
	return pos*num;
}
void write(int x)
{
	if (x<0)
	{
		putchar('-');
		write(-x);
		return;
	}
	if (x>=10) write(x/10);
	putchar(x%10+'0');
}
void writesp(int x)
{
	write(x);
	putchar(' ');
}
void writeln(int x)
{
	write(x);
	putchar('\n');
}
void add(int u,int v)
{
	cnt++;
	edge[cnt].to=v;
	edge[cnt].next=head[u];
	head[u]=cnt;
}
int main()
{
	n=read(); m=read();
	for (int i=1;i<=n;i++)
		vis[i]=read();
	while (m--)
	{
		int x=read(),y=read();
		x++; y++;
		f[y]++;
		add(x,y);
	}
	for (int i=1;i<=n;i++)
	{
		if (f[i]==0)
		{
			if (vis[i]==0) q1.push(i);
			else q2.push(i);
		}
	}
	while (!q1.empty()||!q2.empty())
	{
		while (!q1.empty())
		{
			int u=q1.front();
			q1.pop();
			for (int i=head[u];i;i=edge[i].next)
			{
				int v=edge[i].to;
				f[v]--;
				if (f[v]==0)
				{
					if (vis[v]==0) q1.push(v);
					else q2.push(v); 
				}
			}
		}
		if (!q2.empty()) ans++;
		while (!q2.empty())
		{
			int u=q2.front();
			q2.pop();
			for (int i=head[u];i;i=edge[i].next)
			{
				int v=edge[i].to;
				f[v]--;
				if (f[v]==0)
				{
					if (vis[v]==0) q1.push(v);
					else q2.push(v); 
				}
			}
		}
	}
	writeln(ans);
	return 0;
}
```


---

## 作者：AKPC (赞：6)

### 思路
这道题目可以用拓扑排序做。因为副处理器要尽量少用，那就在每次跑拓扑的时候先跑能用主处理器完成的任务，主处理器能处理的搞完了，看副处理器有没有点，有的话就用一次副处理器跑任务，如此往复。

这里分别处理两种处理器的话用两个队列来维护拓扑序是比单个更好实现的。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
    int x=0;bool f=1;register char c=getchar();
    while (c<48||c>57){if(c=='-') f=0;c=getchar();}
    while (c>=48&&c<=57){x=x*10+(c^48);c=getchar();}
    return f?x:-x;
}
int n,m,a[100005],t[100005],ans;
vector<int>e[100005];
queue<int>que1,que2;
signed main(){
	n=read(),m=read();
	for (int i=1;i<=n;i++) a[i]=read();
	for (int i=1;i<=m;i++){
		int x=read()+1,y=read()+1;
		e[x].push_back(y),t[y]++;
	}
	for (int i=1;i<=n;i++){
		if (t[i]!=0) continue;
		if (a[i]==0) que1.push(i);
		else que2.push(i);
	}
	while ((!que1.empty())||(!que2.empty())){
		while (!que1.empty()){
			int u=que1.front();que1.pop();
			for (int i=0;i<(int)e[u].size();i++){
				int v=e[u][i];
				if (--t[v]==0) a[v]==0?que1.push(v):que2.push(v);
			}
		}
		if (!que2.empty()) ans++;
		while (!que2.empty()){
			int u=que2.front();que2.pop();
			for (int i=0;i<(int)e[u].size();i++){
				int v=e[u][i];
				if (--t[v]==0) a[v]==0?que1.push(v):que2.push(v);
			}
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：water_tomato (赞：6)

## 题意
大体题意如题面所示，这里要注意的是，**前继任务已经被执行过了的任务**和**前继任务被放进副处理器处理的任务**是可以一次同时处理的，这也是题面中“**或**”的含义。另外， $0$ 表示只能在主处理器中处理， $1$ 表示只能在副处理器中处理。最后千万要注意，题目中所给的关系是**前一个处理的前提是后一个被处理**了，不要搞反。

## 解析
首先题面告诉我们这是一张 DAG，很容易就会想到拓扑。再观察题面，我们发现题目要求我们尽可能少的使用副处理器，换言之，就是让我们每次尽可能先不处理需要副处理器的任务，待到不得不处理时再一次性处理，这样可以使得我们每次处理掉的需要副处理器的任务尽可能多，且使用副处理器的次数尽可能少。

这很显然就是**贪心**了。

于是我们就用拓扑排序的方法，每一次先把主处理器能够处理的任务都处理掉，处理完后，再一次性处理目前能够处理的所有需要副处理器的任务。注意，除了目前入度为 $0$ 的任务可以处理以外，在这些任务都被处理掉之后入度为 $0$ 的点满足“**前继任务被放进副处理器处理的任务**”这一条件，也是能够在同一次处理中被处理掉的。

于是代码就呼之欲出了。

## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 100005
using namespace std;
int n,m,cnt,head[N];
int a[N],ru[N],ans;
struct edge{
	int to,next;
}e[N];
inline void add(int x,int y){
	e[++cnt].to=y;
	e[cnt].next=head[x];
	head[x]=cnt;
}

queue<int> qmain,qco;

inline void topo(){
	for(int i=1;i<=n;i++){
		if(!ru[i]){
			if(!a[i]) qmain.push(i);
			else qco.push(i);
		}
	}
	while((!qmain.empty())||(!qco.empty())){
		while(!qmain.empty()){//优先处理主处理器能处理的 
			int u=qmain.front();
			qmain.pop();
			for(int i=head[u];i;i=e[i].next){
				int v=e[i].to;
				ru[v]--;
				if(!ru[v]){
					if(!a[v]) qmain.push(v);
					else qco.push(v);
				}
			}
		}
		if(!qco.empty())
			ans++;//如果需要副处理器处理的话就将处理次数+1 
		while(!qco.empty()){//一次性把所有能一起处理的任务都处理掉 
			int u=qco.front();
			qco.pop();
			for(int i=head[u];i;i=e[i].next){
				int v=e[i].to;
				ru[v]--;
				if(!ru[v]){
					if(!a[v]) qmain.push(v);
					else qco.push(v);
				}
			}
		}
	}
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=1,y,x;i<=m;i++){
		scanf("%d%d",&y,&x);//注意输入顺序与实际操作要求顺序相反 
		add(x+1,y+1);ru[y+1]++;
	}
	topo();
	printf("%d",ans);
	return 0;
}
```


---

## 作者：M_CI (赞：4)

首先，看到标签有拓扑排序，然后题面中提到任务间有依赖关系，所以必定首选拓扑排序。

因为要让副处理器处理次数尽量少，所以就要让主处理器处理次数尽量多。所以开两个队列，一个维护主处理器，另一个维护副处理器。先对主处理器拓扑排序，主处理器拓扑排序完判断维护副处理器的队列中是否还有元素，如果有，则将答案加 $1$，然后再对副处理器拓扑排序。

然后就 AC 了。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,m,ans,a[100010],in[100010];
int tot,hd[100010],to[100010],nx[100010];
queue<int> mp,sp;

void add (int x,int y) {
	to[++tot]=y;
	nx[tot]=hd[x];
	hd[x]=tot;
}

int main () {
	cin>> n>> m;
	for (int i=0;i<n;i++) cin>> a[i];
	for (int i=1;i<=m;i++) {
		int u,v;
		cin>> u>> v;
		add (v,u);
		in[u]++;
	}
	for (int i=0;i<n;i++)
		if (!in[i])
			a[i]==0? mp.push (i): sp.push (i);
	while (!mp.empty ()||!sp.empty ()) {
		while (!mp.empty ()) {
			int u=mp.front ();
			mp.pop ();
			for (int i=hd[u];i;i=nx[i]) {
				int v=to[i];
				if (!(--in[v]))
					a[v]==0? mp.push (v): sp.push (v);
			}
		}
		if (!sp.empty ()) ans++;
		while (!sp.empty ()) {
			int u=sp.front ();
			sp.pop ();
			for (int i=hd[u];i;i=nx[i]) {
				int v=to[i];
				if (!(--in[v]))
					a[v]==0? mp.push (v): sp.push (v);
			}
		}
	}
	cout<< ans;
	return 0;
}
```

---

## 作者：wjh2011 (赞：3)

由于副处理器可以一次处理多个任务，所以我们要让副处理器一次处理尽可能多的任务，才能保证处理的次数最少。

要让副处理器尽量多处理一些任务，只需让主处理器尽可能多处理任务后，再一次性处理所有副处理器可以处理的任务就行了。

由于图是一个有向无环图，所以可以想到用拓扑排序。我们用两个队列分别把主处理器和副处理器中入度为零的点放进队列里，然后直接拓扑排序就行了。
每一次如果副处理器的队列非空，$ans$ 就加一，最后的答案就是 $ans$。

**注意：输入为 $x,y$ 时，是从 $y$ 向 $x$ 连边，不是从 $x$ 向 $y$ 连边**。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 100005
int n, m, ans, in[N];
bool flag[N];
vector<int> son[N];
queue<int> q[2];
int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> flag[i];
	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		son[y].push_back(x);
		in[x]++;
	}
	for (int i = 0; i < n; i++)
		if (!in[i])
			q[flag[i]].push(i);
	while (q[0].size() || q[1].size()) {
		while (q[0].size()) {
			int x = q[0].front();
			q[0].pop();
			for (int y : son[x]) {
				in[y]--;
				if (!in[y]) q[flag[y]].push(y);
			}
		}
		if (q[1].size()) ans++;
		while (q[1].size()) {
			int x = q[1].front();
			q[1].pop();
			for (int y : son[x]) {
				in[y]--;
				if (!in[y]) q[flag[y]].push(y);
			}
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Mason123456 (赞：2)

## 题目翻译

强烈建议修改本题翻译！

### 题目描述

现在又一个项目，有 $N$ 个任务，其中存在 $M$ 个依赖关系，即只有在 $x$ 任务的前置子任务都完成的情况下再能完成任务 $x$。在所有任务中，有些任务只能在主处理器上执行，其他任务只能在协处理器，即副处理器上执行。**保证任务依赖所构成的图是有向无环图**。

对于在协处理器上执行一次程序，可以选择**任意多的**、可执行的任务执行一次程序。

要找出所需的最少协处理器调用次数。

### 输入格式

第一行有两个整数，$N, M\space(1 \le N \le 10^5, 0 \le M \le 10^5)$。

第二行有 $N$ 个 $1$ 或 $0$ 的整数 $E_i$，分别表示任务 $i$ 只能使用协处理器执行，只能使用主处理器执行。

接下来 $M$ 行分别有两个整数 $T_1, T_2 \space (T_1 \not= T_2)$，表示任务编号 $(0 \le T_1, T_2 \le N-1)$。表示 $T_2$ 依赖于 $T_1$。

### 输出格式

即所需的最少协处理器调用次数。

## 思路

有向无环图，那第一反应就是拓扑排序。

拓扑排序本质上就是处理任务之间执行的先后顺序，那这题的提示也非常明显。

假如每个主处理器和协处理器互不干涉，那答案就是：两个处理器分别做一次拓扑排序。若两个处理器互相干涉，那只需要在拓扑排序中，若子任务是需要主处理器执行的，那就添加到主处理器的队列中，否则相反。

至于为什么要区分处理：因为任务 $a$ 可能是 $b$ 的依赖，而 $a, b$ 可能不是一个处理器处理的，即任务处理依赖的图不会太规整（指任务所需的处理器），为了让两个队列区分，也为了更好的连边，就要交错入队。

再考虑答案最小。

要执行的任务是逃不掉的，~~所以其他题解里说要先执行主处理器的理由不太对~~，但是我们可以尽量多的把协处理器的前置任务都处理完，来保证一次能处理的任务尽量多。所以我们才要**先处理主处理器**。

由于一次可以执行任意多的任务，所以跑一次拓扑排序就只相当于使用了一次协处理器。

## Code

来看代码。

```cpp
while(q1.size() || q2.size()) {
	while(!q1.empty()) {// 先跑主处理器
		int u = q1.front();
		q1.pop();
		for(auto v : g[u])
			if(--indeg[v] == 0) {
				if(a[v])	q2.push(v);// 赋值操作需要分队列来区分两个处理器
				else	q1.push(v);
			}
	}
	if(q2.size())	ans++;// 可以一次处理完就直接答案+1
	while(!q2.empty()) {// 再跑协处理器
		int u = q2.front();
		q2.pop();
		for(auto v : g[u])
			if(--indeg[v] == 0) {
				if(a[v])	q2.push(v);
				else	q1.push(v);
			}
	}
}
```

完整代码。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 5;
int n, m, ans;
int a[N], indeg[N];// a[i] == 0 表示主处理器
vector<int> g[N];
queue<int> q1, q2;
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>m;
	for(int i = 1; i <= n; i++)	cin>>a[i];
	for(int _ = 1; _ <= m; _++) {
		int u, v;
		cin>>u>>v;
		v++, u++;
		g[u].push_back(v);
		indeg[v]++;
	}
	for(int i = 1; i <= n; i++)	if(indeg[i] == 0) {
			if(a[i])	q2.push(i);
			else	q1.push(i);
		}
	while(q1.size() || q2.size()) {
		while(!q1.empty()) {
			int u = q1.front();
			q1.pop();
			for(auto v : g[u])
				if(--indeg[v] == 0) {
					if(a[v])	q2.push(v);
					else	q1.push(v);
				}
		}
		if(q2.size())	ans++;
		while(!q2.empty()) {
			int u = q2.front();
			q2.pop();
			for(auto v : g[u])
				if(--indeg[v] == 0) {
					if(a[v])	q2.push(v);
					else	q1.push(v);
				}
		}
	}
	cout<<ans<<"\n";
	return 0;
}
```

## End

说实话这题是个比较板的拓扑，评绿也不过分。

---

## 作者：Styx (赞：2)

**这简直是我vp下来最简（zhi）单（zhang）的一道e题了……**
****
**题意大致是给你一堆任务，有些要用主处理器处理，有些要用副处理器处理，副处理器可以一次处理很多个任务，一个任务能被执行的条件为前继任务已经被执行过了或者前继任务和自己同时被放进副处理器处理，现在给你这些前继任务的关系和每个任务处理要用的处理器，求副处理器最少运行了几次，保证关系是一张有向无环图**

****
**咋做呢，看到这种有前继任务的，又是有向无环图，感觉肯定是DP啊！结果事实证明连DP都不用，这道题就是一道滑稽的拓扑排序。**

**基于万无一失的贪心思想，每次把所有当前能做得要用主处理器的任务都做光，那么此时能一锅端的副处理器任务肯定也是最多的，然后就按照这种思路写模拟就可以啦**

**首先建两个队列，一个放拓扑排序搜到的要用主处理器做得任务，一个放副处理器做的任务，每次先拓扑排序搜到没有能用主处理器做的任务为止，然后如果副处理器的队列里还有别的数，那么ans++，把副处理器队列里的数继续拿出来进行拓扑排序，直到所有数都被搜过为止，复杂度就是拓扑排序的复杂度，还是很优越的。**
****

**代码如下**

```cpp
#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

struct node
{
	int val,du;
} a[100010];

int n,m,vis[100010],ans;
vector<int> g[100010];

int main()
{
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++)
	{
		scanf("%d",&a[i].val);
	}
	for(int i=1; i<=m; i++)
	{
		int from,to;
		scanf("%d%d",&from,&to);
		g[to+1].push_back(from+1);
		a[from+1].du++;
	}
	queue<int> q[2];
	for(int i=1; i<=n; i++)
	{
		if(!a[i].du)
		{
			q[a[i].val].push(i);
		}
	}
	while((!q[0].empty())||(!q[1].empty()))
	{
		while(!q[0].empty())
		{
			int u=q[0].front();
			vis[u]=1;
			q[0].pop();
			for(int i=0; i<g[u].size(); i++)
			{
				if(!vis[g[u][i]])
				{
					a[g[u][i]].du--;
					if(!a[g[u][i]].du)
					{
						q[a[g[u][i]].val].push(g[u][i]);
					}
				}
			}
		}
		if(!q[1].empty())
		{
			ans++;
			while(!q[1].empty())
			{
				int u=q[1].front();
				vis[u]=1;
				q[1].pop();
				for(int i=0; i<g[u].size(); i++)
				{
					if(!vis[g[u][i]])
					{
						a[g[u][i]].du--;
						if(!a[g[u][i]].du)
						{
							q[a[g[u][i]].val].push(g[u][i]);
						}
					}
				}
			}
		}
	}
	printf("%d\n",ans);
}
```


---

## 作者：huyangmu (赞：2)

### 思路

任务有依赖关系，所以可以想到用拓扑排序处理。要使得副处理器处理的少，就要

让主处理器尽量多处理，于是先对主处理器进行拓扑排序，再对副处理器拓扑排序。

可以用两个分别表示主处理器和副处理器的的队列处理。

### AC Code

```cpp

#include <bits/stdc++.h>
#define int long long
using namespace std;
const int NR = 1e5 + 5;
int n, m, a[NR], du[NR], q1[NR], q2[NR], top1, top2, ans;
vector<int> g[NR];
void topo()
{
    int head1 = 1, head2 = 1;
    for (int i = 1; i <= n; ++i)
    {
        if (!du[i])
        {
            if (!a[i])
                q1[++top1] = i; // 入队主处理器
            else
                q2[++top2] = i; // 入队副处理器
        }
    }
    while (head1 <= top1 || head2 <= top2) // 还有任务要处理
    {
        while (head1 <= top1) // 先对主处理器做拓扑排序.减少对副处理器的使用
        {
            int tmp = q1[head1++];
            for (int i = 0; i < g[tmp].size(); ++i)
            {
                --du[g[tmp][i]];
                if (!du[g[tmp][i]])
                {
                    a[g[tmp][i]] == 0 ? q1[++top1] = g[tmp][i] : q2[++top2] = g[tmp][i];
                }
            }
        }
        ans += head2 <= top2; // 简便写法，可以写成如下形式：
        /*
        if(head2 <= top2)
            ans++;
        */
        while (head2 <= top2) //对副处理器做拓扑排序
        {
            int tmp = q2[head2++];
            for (int i = 0; i < g[tmp].size(); ++i)
            {
                --du[g[tmp][i]];
                if (!du[g[tmp][i]])
                    a[g[tmp][i]] == 0 ? q1[++top1] = g[tmp][i] : q2[++top2] = g[tmp][i];
            }
        }
    }
    return;
}
signed main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    while (m--)
    {
        int u, v;
        cin >> u >> v;
        //注意从0开始编号所以要++u,++v
        ++u;
        ++v;
        g[u].push_back(v);
        ++du[v];//统计入度
    }
    topo();//拓扑排序
    cout << ans << '\n';
    return 0;
    //愉快AC
}


---

## 作者：Dita (赞：0)

[题目	](https://www.luogu.com.cn/problem/CF909E)

> **题目大意**
>
> 一张无向图，两种处理器：主处理器，副处理器，以及每个点对应的处理器。
>
> 要求副处理器最少运行次数。

**solution**

因为是 DAG ，所以想到拓扑排序。

因为要求副处理器的最少运行次数，所以我们可以贪心的先把能处理的主处理器的任务一次性处理完，然后再处理副处理器的。

**实现：开两个队列维护两个处理器的任务就好**

**code**

```c++
/*
work by:Ariel_
Knowledge:拓扑排序
Time:O(n)
*/
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#include <algorithm>
#define int long long
#define rg register
using namespace std;
const int MAXN = 1e5 + 5; 
int read(){
    int x = 0,f = 1; char c = getchar();
    while(c < '0'||c > '9') {if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') {x = x*10 + c - '0'; c = getchar();}
    return x*f;
}
int n, m, a[MAXN], ind[MAXN], tot, ans;
queue<int>q[2];
vector<int> G[MAXN];
signed main(){
   n = read(), m = read();
   for (int i = 1; i <= n; i++) a[i] = read();
   for (int i = 1, u, v; i <= m; i++) {
   	  u = read() + 1, v = read() + 1;
   	  G[v].push_back(u), ind[u]++;
   }
   for (int i = 1; i <= n; i++) if(!ind[i]) q[a[i]].push(i);
   while(tot < n) {
   	  if (!q[0].empty()) {
   	     while(!q[0].empty()) {
   	       int u = q[0].front(); q[0].pop();
		   tot++;
		   for (int i = 0; i < G[u].size(); i++) {
		   	   int v = G[u][i];ind[v]--;
		   	   if(!ind[v]) q[a[v]].push(v);
		   }	
	     }	
	  }
	  else {
	  	ans++;
	  	while(!q[1].empty()) {
	  		int u = q[1].front(); q[1].pop();
	  		tot++;
	  		for (int i = 0; i < G[u].size(); i++) {
	  			  int v = G[u][i]; ind[v]--;
	  			  if(!ind[v]) q[a[v]].push(v);
			  }
		}
	  }
   }
   cout<<ans;
   puts("");
   return 0;
}

```



---

## 作者：Fan_Tuan (赞：0)

## 题意：

给你若干任务，有些要用主处理器处理，有些要用副处理器处理，副处理器可以一次处理很多个任务。当一个任务的前继任务完成或者自己与它的前继任务同时放入副处理器处理，这个任务可以被执行。

现在给你这些前继任务的关系和每个任务处理要用的处理器，求副处理器最少运行了几次，保证关系是一张有向无环图。

## 思路：
贪心的想，每次将当前能做的要用主处理器做的任务做完，此时能让副处理器做的任务也肯定是最多的。建两个队列，一个存当前拓扑搜到的要用主处理器处理的任务，一个放副处理器处理的任务，每次搜到没有要主处理器处理的任务为止。如果副处理器任务队列里还有数，那么 ans++，同样的对副处理器队列里的数进行拓扑。

## 代码：
```cpp
#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
#include <vector>
#define int long long
using namespace std;

inline int read() {
    int f = 0, s = 0;
    char ch = getchar();
    while (!isdigit(ch)) f |= ch == '-', ch = getchar();
    while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
    return f ? -s : s;
}

void print (int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) print (x / 10);
    putchar(x % 10 + '0');
} 

const int maxn = 1e5 + 10;
int n, m, head[maxn], du[maxn], tot, ans, num, f[maxn];

queue<int> q[2];

struct node {
    int nex, to;
}edge[maxn];

void add (int from, int to) {
    edge[++num].nex = head[from];
    edge[num].to = to;
    head[from] = num;
}

signed main() {
    n = read(), m = read();
    for (int i = 1; i <= n; i++) f[i] = read();
    for (int i = 1; i <= m; i++) {
        int u, v;
        u = read() + 1, v = read() + 1;
        add(v, u);
        du[u]++;
    }
    for (int i = 1; i <= n; i++) if (!du[i]) q[f[i]].push(i);
    while (tot < n) {
        if (!q[0].empty()) {
            while(!q[0].empty()) {
                int p = q[0].front();
                q[0].pop();
                ++tot;
                for (int i = head[p]; i; i = edge[i].nex) {
                    int to = edge[i].to;
                    du[to]--;
                    if (!du[to]) q[f[to]].push(to);
                }
            }
        }
        else {
            ans++;
            while(!q[1].empty()) {
                int p = q[1].front();
                q[1].pop();
                ++tot;
                for (int i = head[p]; i; i = edge[i].nex) {
                    int to = edge[i].to;
                    du[to]--;
                    if (!du[to]) q[f[to]].push(to);
                }
            }
        }
    }
    print(ans);
    return 0; 
}
```

---

